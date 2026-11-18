#!/usr/bin/env python3
"""Replace compiled Faust externals in Max patches by ``faustgen~`` boxes.

This is the reverse of :mod:`faustgen2max`.  A patch that uses externals built
by ``faust2max6`` (``<name>~.mxo`` bundles) is rewritten so that every box of
such an external becomes a ``faustgen~`` box carrying the same Faust program:
the patch then needs the faustgen package instead of the compiled bundles.

``faust2max6`` stores its inputs in each bundle, in ``Contents/Resources`` (at
the top of the bundle for older versions), unless ``-nosrc`` was given:

* ``<name>.dsp``, the original program;
* ``<name>-exp.dsp``, the program expanded by Faust, which is self-contained
  (all the libraries it uses are inlined);
* ``<name>.cpp``, the generated code, whose header gives the compilation
  options and whose DSP class gives the number of audio inputs and outputs.

For every box whose class is one of these externals, the converter:

1. sets the text to ``faustgen~ <name>``, or ``mc.faustgen~ <name>`` when the
   external was compiled with ``faust2max6 -mc``.  That option is not a Faust
   option and is not in the ``.cpp`` header: it is read from the binary, where
   only a multichannel build creates a ``multichannelsignal`` outlet.  The
   argument names the faustgen factory, so all the boxes of one external share
   one compiled program;
2. stores the program in ``sourcecode``/``sourcecode_size``, the expanded one
   by default, or the original one with ``--source original`` (its libraries
   are then found through ``--library-path``, stored as ``library_path<N>``);
3. stores the options of the external that change the generated code
   (``-double``, ``-es``, ``-mcd``, ``-mdd``, ``-ct``, ``-ftz``...) as
   ``compile_option<N>``; the options that only concern the C++ external
   (``-a``, ``-lang``, ``-cn``, ``-i``...) are dropped;
4. records the class it replaces in the box's ``annotation`` attribute, which
   a script can read with ``getboxattr("annotation")``: ``faustgen~`` keeps
   it, while it resets the scripting name of its box when it is created;
5. keeps the box id, geometry, other attributes and every patch cord.  The
   inlets and outlets of ``faustgen~`` come in the same order as those of a
   ``faust2max6`` external: audio, then the control outlet, then MIDI.

The patches are read and written with py2max.  Two of its saving behaviours
would change boxes the conversion does not touch: it fills in
``numinlets``/``numoutlets`` on boxes that have none, and it rewrites the
``outlettype`` of subpatcher boxes from their ``inlet``/``outlet`` objects
(``multichannelsignal`` becomes ``""``).  Both are switched off here, so that
an unconverted box is written back as it was read.

Inputs are never modified unless ``--in-place`` is given.  The converted
patches are written under ``--output-dir`` at the same relative paths, with a
``max2faustgen.json`` manifest.  ``--analyze`` prints the decisions as JSON
without writing anything.

The module exposes :func:`read_external`, :func:`find_externals`,
:func:`convert_patch` and :func:`check_sources` for programmatic use; the
command-line entry point is :func:`main`.
"""

from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Sequence, Tuple


# Use an installed py2max when available, otherwise the source checkout shipped
# next to this tool in the Faust repository (see faustgen2max.py).
try:
    from py2max import Box, Patcher
except (ImportError, ModuleNotFoundError):
    sys.path.insert(0, str(Path(__file__).resolve().parent / "py2max"))
    sys.modules.pop("py2max", None)
    from py2max import Box, Patcher

# Keep the declared ports of subpatcher boxes as they are in the file.
Box._sync_subpatcher_ports = lambda self: None


MANIFEST = "max2faustgen.json"
FAUSTGEN_VERSION = "1.87"
SKIPPED_DIRECTORIES = {".git", "node_modules"}

# Options of a faust2max6 compilation that change the generated code, with
# their number of values.  They become faustgen~ compile options.
KEPT_OPTIONS = {
    "-double": 0, "-single": 0, "-quad": 0, "-fx": 0,
    "-es": 1, "-mcd": 1, "-mdd": 1, "-mdy": 1, "-ct": 1, "-ftz": 1, "-dlt": 1,
    "-mem": 0, "-vec": 0, "-vs": 1, "-lv": 1, "-fun": 0, "-dfs": 0, "-scal": 0,
    "-nvi": 0, "-fm": 1,
}
# Options that only concern the C++ external, or that faustgen~ sets itself.
DROPPED_OPTIONS = {
    "-a": 1, "-lang": 1, "-cn": 1, "-i": 0, "-fpga-mem-th": 1, "-I": 1, "-A": 1,
    "-o": 1, "-uim": 0, "-json": 0, "-svg": 0,
}


class ConversionError(RuntimeError):
    """A patch cannot be converted without losing information."""


# --------------------------------------------------------------------------
# Externals
# --------------------------------------------------------------------------

@dataclass
class External:
    """A faust2max6 external and what faustgen~ needs to replace it."""

    name: str                    # Max class without its '~'
    bundle: Path
    original: str                # <name>.dsp
    expanded: str                # <name>-exp.dsp
    options: List[str]           # kept compile options
    inputs: int
    outputs: int
    multichannel: Optional[bool] = None   # compiled with -mc; None: no binary
    used_in: List[str] = field(default_factory=list)

    @property
    def max_class(self) -> str:
        return f"{self.name}~"

    def source(self, kind: str) -> str:
        return self.expanded if kind == "expanded" else self.original

    def public_dict(self, kind: str) -> Dict[str, Any]:
        source = self.source(kind).encode("utf-8")
        return {
            "name": self.max_class,
            "bundle": str(self.bundle),
            "inputs": self.inputs,
            "outputs": self.outputs,
            "multichannel": self.multichannel,
            "compile_options": self.options,
            "source": kind,
            "source_bytes": len(source),
            "source_sha256": hashlib.sha256(source).hexdigest(),
            "used_in": self.used_in,
        }


def parse_options(line: str, where: Path) -> List[str]:
    """Keep the code-changing options of a 'Compilation options:' line."""

    tokens = line.split()
    kept: List[str] = []
    i = 0
    while i < len(tokens):
        token = tokens[i]
        if token in KEPT_OPTIONS:
            count = KEPT_OPTIONS[token]
            kept.extend(tokens[i:i + 1 + count])
            i += 1 + count
        elif token in DROPPED_OPTIONS:
            i += 1 + DROPPED_OPTIONS[token]
        else:
            raise ConversionError(f"{where}: option de compilation inconnue {token!r}")
    return kept


def read_external(bundle: Path) -> External:
    """Read the programs, options and audio inputs/outputs of one .mxo bundle.

    A bundle compiled with ``-nosrc`` has no sources and cannot be converted.
    """

    if not bundle.name.endswith("~.mxo"):
        raise ConversionError(f"{bundle}: pas un external <nom>~.mxo")
    name = bundle.name[: -len("~.mxo")]
    suffixes = (("dsp", ".dsp"), ("exp", "-exp.dsp"), ("cpp", ".cpp"))
    # faust2max6 puts the sources in Contents/Resources; older versions put
    # them at the top of the bundle.
    for folder in (bundle / "Contents" / "Resources", bundle):
        paths = {kind: folder / f"{name}{suffix}" for kind, suffix in suffixes}
        missing = [path.name for path in paths.values() if not path.is_file()]
        if not missing:
            break
    else:
        raise ConversionError(f"{bundle}: sources absentes ({', '.join(missing)}), "
                              "external compilé avec -nosrc ?")
    code = paths["cpp"].read_text(encoding="utf-8", errors="replace")
    match = re.search(r"Compilation options:\s*(.*)", code)
    if not match:
        raise ConversionError(f"{paths['cpp']}: ligne 'Compilation options' introuvable")
    options = parse_options(match.group(1), paths["cpp"])

    # The DSP class generated by Faust returns constants; the wrapper classes
    # of the architecture forward the counts of another object.
    ins = set(re.findall(r"int getNumInputs\(\)\s*\{\s*return\s+(\d+);", code))
    outs = set(re.findall(r"int getNumOutputs\(\)\s*\{\s*return\s+(\d+);", code))
    if len(ins) != 1 or len(outs) != 1:
        raise ConversionError(f"{paths['cpp']}: entrées/sorties ambiguës {ins} {outs}")
    return External(
        name=name,
        bundle=bundle.resolve(),
        original=paths["dsp"].read_text(encoding="utf-8"),
        expanded=paths["exp"].read_text(encoding="utf-8"),
        options=options,
        inputs=int(ins.pop()),
        outputs=int(outs.pop()),
        multichannel=compiled_multichannel(bundle, name),
    )


def compiled_multichannel(bundle: Path, name: str) -> Optional[bool]:
    """Tell whether faust2max6 compiled the bundle with -mc, from its binary.

    -mc is not a Faust option: faust2max6 compiles the architecture with
    -DMC_VERSION, so it does not appear in the options of the .cpp.  Only the
    code compiled with MC_VERSION creates a "multichannelsignal" outlet.
    Returns None when the bundle has no binary to look at.
    """

    macos = bundle / "Contents" / "MacOS"
    main = macos / f"{name}~"
    binaries = [main] if main.is_file() else sorted(
        p for p in macos.glob("*") if p.is_file()) if macos.is_dir() else []
    if not binaries:
        return None
    return any(b"multichannelsignal" in p.read_bytes() for p in binaries)


def find_externals(directories: Iterable[Path]) -> Dict[str, External]:
    """Index the ``*~.mxo`` bundles of directories, searched recursively."""

    externals: Dict[str, External] = {}
    for directory in directories:
        for root, subdirs, _ in os.walk(directory):
            bundles = sorted(d for d in subdirs if d.endswith("~.mxo"))
            subdirs[:] = sorted(d for d in subdirs
                                if d not in SKIPPED_DIRECTORIES and not d.endswith(".mxo"))
            for name in bundles:
                external = read_external(Path(root) / name)
                previous = externals.get(external.max_class)
                if previous and previous.bundle != external.bundle:
                    raise ConversionError(f"{external.max_class} trouvé deux fois : "
                                          f"{previous.bundle} et {external.bundle}")
                externals[external.max_class] = external
    return externals


def check_sources(externals: Iterable[External], faust: str, kind: str = "expanded",
                  library_paths: Sequence[Path] = (), jobs: int = 4) -> int:
    """Compile every program with the options it will have in faustgen~.

    Returns the number of programs compiled; raises ConversionError with the
    compiler's messages when one fails.
    """

    externals = list(externals)

    def compile_one(external: External) -> Optional[str]:
        with tempfile.TemporaryDirectory(prefix="max2faustgen-") as temporary:
            dsp = Path(temporary) / f"{external.name}.dsp"
            dsp.write_text(external.source(kind), encoding="utf-8")
            includes = [arg for path in library_paths for arg in ("-I", str(path))]
            command = [faust, *includes, *external.options, "-lang", "cpp", str(dsp),
                       "-o", str(Path(temporary) / "out.cpp")]
            result = subprocess.run(command, capture_output=True, text=True)
            if result.returncode != 0:
                return f"{external.max_class}: {' '.join(command)}\n{result.stderr.strip()}"
        return None

    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, jobs)) as pool:
        errors = [error for error in pool.map(compile_one, externals) if error]
    if errors:
        raise ConversionError("échec de compilation :\n" + "\n\n".join(errors))
    return len(externals)


# --------------------------------------------------------------------------
# Patches
# --------------------------------------------------------------------------

def _walk_boxes(patcher: Any, location: str = "root") -> Iterable[Tuple[Any, Any, str]]:
    """Yield (owner patcher, box, location) for every box, subpatchers included."""

    for box in patcher._boxes:
        here = f"{location}/{box.id}"
        yield patcher, box, here
        if box.subpatcher is not None:
            yield from _walk_boxes(box.subpatcher, here)


def _drop_added_defaults(patcher: Any, saved: Dict[str, Any]) -> None:
    """Remove the numinlets/numoutlets py2max gives to boxes saved without them."""

    for box, entry in zip(patcher._boxes, saved.get("boxes", [])):
        saved_box = entry.get("box", {})
        for key in ("numinlets", "numoutlets"):
            if key not in saved_box and key in box.__dict__:
                del box.__dict__[key]
        if box.subpatcher is not None and "patcher" in saved_box:
            _drop_added_defaults(box.subpatcher, saved_box["patcher"])


def load_patch(path: Path) -> Any:
    """Load a patch with py2max so that saving it gives back the same JSON."""

    saved = json.loads(path.read_text(encoding="utf-8"))
    patcher = Patcher.from_file(path)
    _drop_added_defaults(patcher, saved["patcher"])
    return patcher


@dataclass
class Options:
    """Conversion choices shared by every box."""

    source: str = "expanded"                       # or "original"
    library_paths: List[str] = field(default_factory=list)
    extra_options: List[str] = field(default_factory=list)
    factory_name: bool = True
    annotation: bool = True


def multichannel_box(box: Any, external: External) -> Tuple[bool, List[str]]:
    """Decide between faustgen~ and mc.faustgen~ for one box.

    The external's binary decides.  The outlet types saved in the box, when
    there are any, only confirm it; they decide when there is no binary.
    """

    types = box.__dict__.get("outlettype") or []
    saved = (types[0] == "multichannelsignal") if types else None
    if external.multichannel is None:
        return bool(saved), ["pas de binaire dans l'external : "
                             + ("mc.faustgen~" if saved else "faustgen~")
                             + " choisi d'après la boîte"]
    if saved is not None and saved != external.multichannel:
        state = "multicanal" if external.multichannel else "non multicanal"
        return external.multichannel, [f"l'external est {state} mais la boîte "
                                       "a été sauvegardée autrement : le binaire décide"]
    return external.multichannel, []


def to_faustgen(box: Any, external: External, options: Options,
                multichannel: Optional[bool] = None) -> List[str]:
    """Rewrite one external box as a faustgen~ box, in place; return warnings."""

    warnings: List[str] = []
    if multichannel is None:
        multichannel, warnings = multichannel_box(box, external)
    attributes = box.__dict__
    faustgen = "mc.faustgen~" if multichannel else "faustgen~"
    attributes["text"] = f"{faustgen} {external.name}" if options.factory_name else faustgen
    if options.annotation:
        if attributes.get("annotation"):
            warnings.append(f"annotation existante conservée ({attributes['annotation']!r})")
        else:
            attributes["annotation"] = external.max_class
    if multichannel:
        attributes["numinlets"] = 1
        attributes["numoutlets"] = 3
        attributes["outlettype"] = ["multichannelsignal", "", ""]
    else:
        attributes["numinlets"] = max(1, external.inputs)
        attributes["numoutlets"] = external.outputs + 2
        attributes["outlettype"] = ["signal"] * external.outputs + ["", ""]
    attributes["version"] = FAUSTGEN_VERSION
    for i, path in enumerate(options.library_paths):
        attributes[f"library_path{i}"] = path
    for i, option in enumerate(external.options + options.extra_options):
        attributes[f"compile_option{i}"] = option
    source = external.source(options.source)
    attributes["sourcecode_size"] = len(source.encode("utf-8"))
    attributes["sourcecode"] = source
    return warnings


def convert_patch(path: Path, externals: Dict[str, External], options: Options,
                  output: Optional[Path] = None, label: Optional[str] = None
                  ) -> Tuple[List[Dict[str, Any]], List[str]]:
    """Convert the external boxes of one patch.

    Writes the result to ``output`` when it is given and something was
    converted; returns the converted boxes and the warnings.
    """

    patcher = load_patch(path)
    label = label or str(path)
    converted: List[Dict[str, Any]] = []
    warnings: List[str] = []
    for owner, box, location in _walk_boxes(patcher):
        text = box.__dict__.get("text")
        if getattr(box, "maxclass", None) != "newobj" or not isinstance(text, str):
            continue
        words = text.split()
        if not words or words[0] not in externals:
            continue
        external = externals[words[0]]
        where = f"{label}:{location}"
        if len(words) > 1:
            raise ConversionError(f"{where}: arguments sans équivalent faustgen~ {text!r}")
        if box.__dict__.get("varname"):
            warnings.append(f"{where}: le nom de script {box.varname!r} "
                            "sera remplacé par faustgen~ à sa création")
        multichannel, notes = multichannel_box(box, external)
        audio_outlets = 1 if multichannel else external.outputs
        for line in owner._lines:
            if line.src == box.id and line.source[1] >= audio_outlets:
                warnings.append(f"{where}: cordon depuis l'outlet {line.source[1]}, "
                                f"l'external n'a que {audio_outlets} sortie(s) audio")
        if multichannel:
            for line in owner._lines:
                if line.dst == box.id and line.destination[1] > 0:
                    warnings.append(f"{where}: cordon vers l'inlet {line.destination[1]}, "
                                    "l'external multicanal n'a qu'un inlet")
        notes += to_faustgen(box, external, options, multichannel)
        warnings.extend(f"{where}: {note}" for note in notes)
        external.used_in.append(where)
        converted.append({"box": location, "external": external.max_class})

    if converted:
        replaced = {f"{record['external']}.mxo" for record in converted}
        cache = getattr(patcher, "dependency_cache", None)
        if isinstance(cache, list):
            patcher.dependency_cache = [
                item for item in cache
                if not (isinstance(item, dict) and item.get("name") in replaced)]
        if output is not None:
            output.parent.mkdir(parents=True, exist_ok=True)
            patcher.save_as(output)
    return converted, warnings


# --------------------------------------------------------------------------
# Command line
# --------------------------------------------------------------------------

def collect_patches(inputs: Sequence[str]) -> List[Tuple[Path, Path]]:
    """Expand inputs to (patch, root) pairs; root anchors the relative path."""

    found: List[Tuple[Path, Path]] = []
    for raw in inputs:
        path = Path(raw).expanduser().resolve()
        if path.is_dir():
            for directory, subdirs, files in os.walk(path):
                subdirs[:] = sorted(d for d in subdirs if d not in SKIPPED_DIRECTORIES
                                    and not d.endswith(".mxo"))
                found.extend((Path(directory) / f, path)
                             for f in sorted(files) if f.endswith(".maxpat"))
        elif path.is_file() and path.suffix.lower() == ".maxpat":
            found.append((path, path.parent))
        else:
            raise ConversionError(f"entrée .maxpat introuvable: {path}")
    unique: Dict[Path, Path] = {}
    for patch, root in found:
        unique.setdefault(patch, root)
    return list(unique.items())


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Remplace les externals faust2max6 de patches Max par des faustgen~.")
    parser.add_argument("inputs", nargs="+",
                        help="patch(es) .maxpat ou répertoire(s), parcourus récursivement")
    parser.add_argument("-E", "--externals", action="append", default=[], metavar="REP",
                        help="répertoire où chercher les <nom>~.mxo, récursivement "
                             "(répétable ; défaut : les entrées et le dossier des patches)")
    destination = parser.add_mutually_exclusive_group()
    destination.add_argument("-o", "--output-dir", metavar="REP",
                             help="écrit les patches convertis sous REP, aux mêmes chemins "
                                  "relatifs, avec le manifeste " + MANIFEST)
    destination.add_argument("--in-place", action="store_true",
                             help="réécrit les patches d'entrée (à utiliser sur une copie)")
    destination.add_argument("--analyze", action="store_true",
                             help="imprime l'analyse JSON sans rien écrire")
    parser.add_argument("--source", choices=("expanded", "original"), default="expanded",
                        help="programme placé dans faustgen~ : le -exp.dsp autonome "
                             "(défaut) ou le .dsp d'origine")
    parser.add_argument("-L", "--library-path", action="append", default=[], metavar="REP",
                        help="chemin de bibliothèques Faust enregistré dans chaque "
                             "faustgen~ (répétable, utile avec --source original)")
    parser.add_argument("--compile-option", action="append", default=[], metavar="ARG",
                        help="option faustgen~ ajoutée à toutes les boîtes, répétable "
                             "(forme --compile-option=-vec pour une valeur en -)")
    parser.add_argument("--no-factory-name", action="store_true",
                        help="ne pas nommer la factory faustgen~ d'après l'external")
    parser.add_argument("--no-annotation", action="store_true",
                        help="ne pas noter la classe remplacée dans l'annotation de la boîte")
    parser.add_argument("--check", metavar="FAUST",
                        help="compile d'abord chaque programme avec ce compilateur Faust")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4,
                        help="compilations simultanées pour --check")
    parser.add_argument("--force", action="store_true",
                        help="écrase les patches déjà présents dans --output-dir")
    return parser


def main(argv: Optional[Sequence[str]] = None) -> int:
    """Run the converter; 0 on success, 1 when nothing to convert, 2 on error."""

    args = build_parser().parse_args(argv)
    try:
        if not (args.output_dir or args.in_place or args.analyze):
            raise ConversionError("choisir --output-dir, --in-place ou --analyze")
        patches = collect_patches(args.inputs)
        if not patches:
            raise ConversionError("aucun patch .maxpat trouvé")

        searched = [Path(p).expanduser().resolve() for p in args.externals]
        if not searched:
            searched = sorted({root for _, root in patches})
        externals = find_externals(searched)
        if not externals:
            raise ConversionError("aucun external <nom>~.mxo trouvé dans "
                                  + ", ".join(map(str, searched)))
        options = Options(
            source=args.source,
            library_paths=[str(Path(p).expanduser().resolve()) for p in args.library_path],
            extra_options=list(args.compile_option),
            factory_name=not args.no_factory_name,
            annotation=not args.no_annotation,
        )

        output_dir = Path(args.output_dir).expanduser().resolve() if args.output_dir else None
        targets: Dict[Path, Optional[Path]] = {}
        for patch, root in patches:
            if output_dir is not None:
                target = output_dir / patch.relative_to(root)
                if target in targets.values():
                    raise ConversionError(f"deux entrées donnent la même sortie: {target}")
                if target.resolve() == patch:
                    raise ConversionError("--output-dir ne doit pas réécrire les entrées "
                                          "(utiliser --in-place)")
                targets[patch] = target
            else:
                targets[patch] = patch if args.in_place else None

        if args.check:
            # Only the externals that a patch uses need to compile.
            used = {}
            for patch in targets:
                for _, box, _ in _walk_boxes(load_patch(patch)):
                    text = box.__dict__.get("text")
                    if isinstance(text, str) and text.split()[:1] and text.split()[0] in externals:
                        used[text.split()[0]] = externals[text.split()[0]]
            count = check_sources(used.values(), args.check, args.source,
                                  [Path(p) for p in options.library_paths], args.jobs)
            print(f"{count} programme(s) compilé(s) sans erreur par {args.check}")

        records: Dict[str, List[Dict[str, Any]]] = {}
        warnings: List[str] = []
        for patch, target in targets.items():
            if target is not None and target != patch and target.exists() and not args.force:
                raise ConversionError(f"sortie déjà existante: {target}; utiliser --force")
        for patch, target in targets.items():
            converted, notes = convert_patch(patch, externals, options, target, str(patch))
            warnings.extend(notes)
            if converted:
                records[str(patch)] = converted

        used_externals = [e for e in externals.values() if e.used_in]
        report = {
            "inputs": [str(Path(i).expanduser().resolve()) for i in args.inputs],
            "faustgen_version": FAUSTGEN_VERSION,
            "options": {"source": options.source, "library_paths": options.library_paths,
                        "extra_compile_options": options.extra_options,
                        "factory_name": options.factory_name,
                        "annotation": options.annotation},
            "externals": [e.public_dict(options.source) for e in used_externals],
            "unused_externals": sorted(e.max_class for e in externals.values()
                                       if not e.used_in),
            "patches": records,
            "warnings": warnings,
        }
        if args.analyze:
            print(json.dumps(report, indent=2, ensure_ascii=False))
            return 0 if records else 1

        boxes = sum(len(v) for v in records.values())
        print(f"{boxes} boîte(s) convertie(s) dans {len(records)} patch(es), "
              f"{len(used_externals)} external(s) remplacé(s)")
        for note in warnings:
            print(f"attention: {note}", file=sys.stderr)
        if output_dir is not None:
            output_dir.mkdir(parents=True, exist_ok=True)
            manifest = output_dir / MANIFEST
            manifest.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n",
                                encoding="utf-8")
            print(f"manifeste: {manifest}")
        return 0 if records else 1
    except (ConversionError, OSError, json.JSONDecodeError) as error:
        print(f"erreur: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
