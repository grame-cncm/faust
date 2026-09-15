#!/usr/bin/env python3
"""Convert ``faustgen~`` prototype patches to compiled Max externals.

The converter reads one or more ``.maxpat`` files with :mod:`py2max`, walks the
complete patcher hierarchy, extracts the Faust program stored in every
``faustgen~`` or ``mc.faustgen~`` box's ``sourcecode`` property, and invokes
``faust2max6`` for each distinct source/build-configuration pair.  It then
replaces each generator box with the corresponding compiled object while
preserving its id, geometry, scripting name, attributes, and patch cords.

Build options are inferred from the patch where possible: ``mc.faustgen~``
selects multichannel output, the faustgen outlet layout and connected messages
can enable MIDI or OSC, Faust's ``soundfile`` primitive enables soundfile
support, and ``declare nvoices`` or a constant ``polyphony N`` message selects
polyphony.  Command-line options can override these decisions.

The input patch is never modified.  Conversion produces a sibling
``<patch>-compiled`` directory by default, containing the rewritten patch,
extracted ``.dsp`` sources, ``.mxo`` bundles, and a JSON manifest.  Analysis
mode reports the same decisions as JSON without writing or compiling anything.

The module also exposes :func:`analyze_patch` and :func:`convert_patch` for
programmatic use.  The command-line entry point is :func:`main`.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import asdict, dataclass, field
from pathlib import Path
from typing import Any, Callable, Dict, Iterable, List, Mapping, Optional, Sequence, Tuple


# Use an installed py2max when available, otherwise use the source checkout
# shipped next to this tool in the Faust repository.
try:
    from py2max import Box, Patcher
except (ImportError, ModuleNotFoundError):
    sys.path.insert(0, str(Path(__file__).resolve().parent / "py2max"))
    # Running the script from architecture/max-msp can first discover the
    # adjacent checkout directory as an empty namespace package.  Discard that
    # partial import before resolving the actual py2max/py2max package.
    sys.modules.pop("py2max", None)
    from py2max import Box, Patcher


FAUSTGEN_CLASSES = {"faustgen~", "mc.faustgen~"}
FAUSTGEN_ONLY_MESSAGES = {
    "compileoptions",
    "librarypath",
    "read",
    "write",
}
FAUSTGEN_STATE_KEYS = {
    "machinecode",
    "machinecode_size",
    "sample_format",
    "serial_number",
    "sourcecode",
    "sourcecode_size",
    "version",
}


class ConversionError(RuntimeError):
    """A patch cannot be converted without losing required information."""


@dataclass
class FaustgenInfo:
    """Analysis and conversion state for one faustgen box.

    ``location`` is a stable slash-separated path made from Max box ids, rooted
    at ``root``.  ``index`` is the one-based discovery order and can also be
    used as a command-line selector.  ``source`` and the private ``patcher`` and
    ``box`` references are deliberately omitted from the public manifest.
    """

    index: int
    location: str
    object_id: str
    varname: Optional[str]
    faustgen_class: str
    source: Optional[str]
    incoming_messages: List[str]
    is_mc: bool
    midi: bool
    osc: bool
    soundfile: bool
    nvoices: Optional[int]
    warnings: List[str] = field(default_factory=list)
    external_name: Optional[str] = None
    compile_args: List[str] = field(default_factory=list)
    patcher: Any = field(default=None, repr=False)
    box: Any = field(default=None, repr=False)

    def public_dict(self) -> Dict[str, Any]:
        """Return the JSON-safe analysis record written to reports/manifests.

        Faust source text is represented by its byte-independent SHA-256 hash
        and character count so analysis output remains compact and does not
        duplicate potentially large programs.
        """

        result = asdict(self)
        result.pop("patcher", None)
        result.pop("box", None)
        result["source_length"] = len(self.source) if self.source is not None else 0
        result["source_sha256"] = (
            hashlib.sha256(self.source.encode("utf-8")).hexdigest()
            if self.source is not None
            else None
        )
        result.pop("source", None)
        return result


@dataclass
class CompilationUnit:
    """A source/configuration pair compiled once and shared by matching boxes.

    ``objects`` contains all boxes rewritten to use this unit.  ``include_dirs``
    records directories exposed to Faust with ``-A`` during compilation.
    """

    name: str
    source: str
    source_path: Path
    args: List[str]
    include_dirs: List[Path]
    objects: List[FaustgenInfo]


def _object_class(text: Any) -> Optional[str]:
    """Return the faustgen class named by a Max object-box text, if any."""

    if not isinstance(text, str):
        return None
    words = text.strip().split()
    return words[0] if words and words[0] in FAUSTGEN_CLASSES else None


def _walk_patchers(patcher: Any, location: str = "root") -> Iterable[Tuple[Any, Box, str]]:
    """Yield every box together with its owning patcher and stable location."""

    for box in patcher._boxes:
        box_location = f"{location}/{box.id}"
        yield patcher, box, box_location
        if box.subpatcher is not None:
            yield from _walk_patchers(box.subpatcher, box_location)


def _incoming_texts(patcher: Any, box: Box) -> List[str]:
    """Return text from every box directly connected to ``box``'s inputs."""

    texts: List[str] = []
    for line in patcher._lines:
        if line.dst != box.id:
            continue
        source = patcher._objects.get(line.src)
        text = source.text if source is not None else ""
        if isinstance(text, str) and text:
            texts.append(text)
    return texts


def _parse_assignments(values: Sequence[str], option: str) -> Dict[str, str]:
    """Parse repeated ``SELECTOR=VALUE`` arguments or raise ConversionError."""

    assignments: Dict[str, str] = {}
    for value in values:
        if "=" not in value:
            raise ConversionError(f"{option} attend SELECTEUR=VALEUR, reçu: {value!r}")
        selector, assigned = value.split("=", 1)
        if not selector or not assigned:
            raise ConversionError(f"{option} attend SELECTEUR=VALEUR, reçu: {value!r}")
        assignments[selector] = assigned
    return assignments


def _select_override(
    assignments: Mapping[str, str], index: int, location: str, box: Box
) -> Optional[str]:
    """Resolve an override by location, id, scripting name, or one-based index.

    Multiple selectors may identify the same box, but they must all assign the
    same value.  Conflicting matches are rejected to keep conversion explicit.
    """

    selectors = (location, str(box.id), str(getattr(box, "varname", "")), str(index))
    matches = [assignments[item] for item in selectors if item and item in assignments]
    if len(set(matches)) > 1:
        raise ConversionError(f"surcharges contradictoires pour {location}: {matches}")
    return matches[0] if matches else None


def _declared_name(source: str) -> Optional[str]:
    """Extract the first ``declare name`` metadata value from Faust source."""

    match = re.search(r'\bdeclare\s+name\s+"([^"]+)"\s*;', source)
    return match.group(1).strip() if match else None


def _declared_nvoices(source: str) -> Optional[int]:
    """Extract an integer ``declare nvoices`` value from Faust source."""

    match = re.search(r'\bdeclare\s+nvoices\s+"?(\d+)"?\s*;', source)
    return int(match.group(1)) if match else None


def _message_nvoices(messages: Sequence[str]) -> Optional[int]:
    """Return the last constant voice count from ``polyphony N`` messages."""

    values = []
    for message in messages:
        match = re.fullmatch(r"\s*polyphony\s+(\d+)\s*", message)
        if match:
            values.append(int(match.group(1)))
    return values[-1] if values else None


def _safe_name(value: str) -> str:
    """Convert arbitrary text to a portable C++/Max external base name."""

    # Faust's -cn value must be a C++ identifier; ASCII also makes the Max
    # bundle and object names portable.
    name = value.encode("ascii", errors="ignore").decode("ascii")
    name = re.sub(r"[^A-Za-z0-9_]+", "_", name).strip("_").lower()
    if not name:
        name = "faust_dsp"
    if not re.match(r"[A-Za-z_]", name):
        name = "dsp_" + name
    return name[:80]


def _name_base(info: FaustgenInfo, patch_path: Path, count: int) -> str:
    """Choose a default external name from Faust metadata, varname, or patch."""

    if info.source:
        declared = _declared_name(info.source)
        if declared:
            return _safe_name(declared)
    varname = info.varname or ""
    if varname and not re.fullmatch(r"faustgen-\d+", varname):
        return _safe_name(varname)
    stem = re.sub(r"^faustgen[-_]", "", patch_path.stem, flags=re.IGNORECASE)
    suffix = f"_{info.object_id}" if count > 1 else ""
    return _safe_name(stem + suffix)


def _is_midi(
    source: str,
    messages: Sequence[str],
    nvoices: Optional[int],
    outlet_types: Sequence[Any],
) -> bool:
    """Infer whether a box requires faust2max6 MIDI support.

    Evidence is, in priority-neutral order, the faustgen MIDI outlet topology,
    polyphony, Faust ``[midi:...]`` metadata, or an incoming MIDI/MPE message.
    """

    # faustgen~ exposes a control outlet followed by a MIDI outlet.  Preserve
    # that topology even when the patch does not currently connect MIDI boxes.
    if len(outlet_types) >= 2 and list(outlet_types[-2:]) == ["", ""]:
        return True
    if nvoices is not None or re.search(r"\[\s*midi\s*:", source, re.IGNORECASE):
        return True
    for text in messages:
        head = text.strip().split(" ", 1)[0]
        if head in {"midievent", "midiformat", "midiparse", "mpeformat", "mpeparse"}:
            return True
    return False


def analyze_patch(
    patch_path: Path,
    name_overrides: Optional[Mapping[str, str]] = None,
    midi_mode: str = "auto",
    osc_mode: str = "auto",
    soundfile_mode: str = "auto",
    nvoices_override: Optional[int] = None,
    compiler_args: Sequence[str] = (),
) -> Tuple[Any, List[FaustgenInfo]]:
    """Analyze a patch and return its py2max model plus faustgen records.

    Args:
        patch_path: Existing ``.maxpat`` file to load.
        name_overrides: External names keyed by nested location, box id,
            scripting name, or one-based occurrence number.
        midi_mode: ``auto``, ``always``, or ``never``.
        osc_mode: ``auto``, ``always``, or ``never``.
        soundfile_mode: ``auto``, ``always``, or ``never``.
        nvoices_override: Global voice count replacing inferred counts.
        compiler_args: Extra arguments appended to every faust2max6 command.

    Returns:
        A pair containing the mutable root :class:`Patcher` and one
        :class:`FaustgenInfo` per matching box, including nested patchers.

    Notes:
        This function performs no compilation and writes no files.  Missing
        ``sourcecode`` is recorded as ``None`` and rejected later by
        :func:`convert_patch`.
    """

    patch_path = patch_path.resolve()
    patcher = Patcher.from_file(patch_path)
    name_overrides = name_overrides or {}
    raw: List[FaustgenInfo] = []

    candidates = [item for item in _walk_patchers(patcher) if _object_class(item[1].text)]
    for index, (owner, box, location) in enumerate(candidates, start=1):
        klass = _object_class(box.text)
        assert klass is not None
        incoming = _incoming_texts(owner, box)
        warnings: List[str] = []
        embedded = getattr(box, "sourcecode", None)
        source = embedded if isinstance(embedded, str) and embedded.strip() else None

        declared_voices = _declared_nvoices(source) if source else None
        message_voices = _message_nvoices(incoming)
        nvoices = nvoices_override or declared_voices or message_voices
        if message_voices and declared_voices and message_voices != declared_voices:
            warnings.append(
                f"polyphony {message_voices} diffère de declare nvoices {declared_voices}; "
                "l'external démarre avec la métadonnée declare et le message reste libre de la modifier"
            )

        outlet_types = getattr(box, "outlettype", [])
        inferred_midi = _is_midi(source or "", incoming, nvoices, outlet_types)
        midi = midi_mode == "always" or (midi_mode == "auto" and inferred_midi)
        inferred_osc = any(text.strip().startswith("osc ") for text in incoming)
        osc = osc_mode == "always" or (osc_mode == "auto" and inferred_osc)
        inferred_soundfile = bool(
            source and re.search(r"\bsoundfile\s*\(", source, re.IGNORECASE)
        )
        soundfile = soundfile_mode == "always" or (
            soundfile_mode == "auto" and inferred_soundfile
        )
        if midi_mode == "never" and inferred_midi:
            warnings.append("support MIDI détecté mais désactivé par --midi never")
        if osc_mode == "never" and inferred_osc:
            warnings.append("support OSC détecté mais désactivé par --osc never")
        if soundfile_mode == "never" and inferred_soundfile:
            warnings.append("primitive soundfile détectée mais désactivée par --soundfile never")

        for message in incoming:
            head = message.strip().split(" ", 1)[0]
            if head in FAUSTGEN_ONLY_MESSAGES:
                warnings.append(
                    f"message de prototypage conservé mais non applicable après compilation: {message!r}"
                )

        info = FaustgenInfo(
            index=index,
            location=location,
            object_id=str(box.id),
            varname=getattr(box, "varname", None),
            faustgen_class=klass,
            source=source,
            incoming_messages=incoming,
            is_mc=klass == "mc.faustgen~",
            midi=midi,
            osc=osc,
            soundfile=soundfile,
            nvoices=nvoices,
            warnings=warnings,
            patcher=owner,
            box=box,
        )
        raw.append(info)

    used_names: Dict[str, int] = {}
    for info in raw:
        explicit_name = _select_override(name_overrides, info.index, info.location, info.box)
        base = _safe_name(explicit_name) if explicit_name else _name_base(info, patch_path, len(raw))
        used_names[base] = used_names.get(base, 0) + 1
        info.external_name = base if used_names[base] == 1 else f"{base}_{used_names[base]}"

        args = ["-nopatch"]
        if info.is_mc:
            args.append("-mc")
        if info.midi:
            args.append("-midi")
        if info.osc:
            args.append("-osc")
        if info.soundfile:
            args.append("-soundfile")
        if info.nvoices is not None and (
            nvoices_override is not None
            or not (info.source and _declared_nvoices(info.source))
        ):
            args.extend(["-nvoices", str(info.nvoices)])
        args.extend(compiler_args)
        info.compile_args = args

    return patcher, raw


def _compilation_units(
    infos: Sequence[FaustgenInfo], output_dir: Path, patch_dir: Path
) -> List[CompilationUnit]:
    """Group identical sources and build settings into compilation units.

    Boxes in a group share one external and are all renamed to that external.
    The original patch directory is retained as a Faust library search path.
    """

    units: List[CompilationUnit] = []
    by_key: Dict[Tuple[str, Tuple[str, ...], Tuple[str, ...]], CompilationUnit] = {}
    for info in infos:
        if info.source is None or info.external_name is None:
            continue
        include_dirs = [patch_dir]
        include_strings = tuple(str(path.resolve()) for path in dict.fromkeys(include_dirs))
        args = list(info.compile_args)
        key = (
            hashlib.sha256(info.source.encode("utf-8")).hexdigest(),
            tuple(info.compile_args),
            include_strings,
        )
        unit = by_key.get(key)
        if unit is None:
            source_path = output_dir / f"{info.external_name}.dsp"
            unit = CompilationUnit(
                info.external_name,
                info.source,
                source_path,
                args,
                [Path(item) for item in include_strings],
                [],
            )
            by_key[key] = unit
            units.append(unit)
        else:
            # Identical source and build settings share one external.
            info.external_name = unit.name
        unit.objects.append(info)
    return units


def _default_compile(command: Sequence[str], cwd: Path) -> None:
    """Run faust2max6, echo its output, and turn failures into ConversionError."""

    environment = os.environ.copy()
    bundled_architecture = Path(__file__).resolve().parents[1]
    if (bundled_architecture / "max-msp" / "max-msp64.cpp").is_file():
        # Keep the wrapper and architecture in sync when running from a source
        # checkout. Otherwise faust2max6 falls back to `faust -archdir`, which
        # may silently select an older installed max-msp64.cpp.
        environment.setdefault("FAUSTARCH", str(bundled_architecture))
        environment.setdefault("FAUST_ARCH_PATH", str(bundled_architecture))
    process = subprocess.run(
        list(command),
        cwd=str(cwd),
        env=environment,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    if process.returncode:
        output = process.stdout.strip()
        raise ConversionError(
            f"faust2max6 a échoué ({process.returncode})\n"
            f"commande: {' '.join(command)}\n{output}"
        )
    if process.stdout.strip():
        print(process.stdout.strip())


def _remove_faustgen_state(box: Box) -> None:
    """Remove embedded compiler/cache fields that do not belong to an external."""

    for key in list(vars(box)):
        if key in FAUSTGEN_STATE_KEYS or re.fullmatch(r"library_path\d+", key):
            delattr(box, key)
    for key in list(box._kwds):
        if key in FAUSTGEN_STATE_KEYS or re.fullmatch(r"library_path\d+", key):
            del box._kwds[key]


def convert_patch(
    patch_path: Path,
    output_dir: Path,
    faust2max6: str = "faust2max6",
    force: bool = False,
    compile_runner: Callable[[Sequence[str], Path], None] = _default_compile,
    **analysis_options: Any,
) -> Tuple[Path, Path, List[FaustgenInfo]]:
    """Compile and rewrite one patch.

    Args:
        patch_path: Source patch.  It is loaded but never overwritten.
        output_dir: Directory receiving sources, bundles, patch, and manifest.
        faust2max6: Path to the compiler wrapper.
        force: Permit replacement of known generated products.
        compile_runner: Injectable command runner, primarily for tests.
        **analysis_options: Keyword options accepted by :func:`analyze_patch`.

    Returns:
        ``(output_patch, manifest_path, infos)`` with absolute output paths and
        the complete per-object analysis.

    Raises:
        ConversionError: If there is no faustgen box, source code is missing,
            output already exists without ``force``, compilation fails, or the
            expected external bundle is not produced.

    The actual build runs in a temporary path without spaces because
    ``faust2max6`` internally flattens part of its argument vector into shell
    strings.  Include directories are exposed there through short symlinks and
    completed bundles are copied to ``output_dir``.
    """

    patch_path = patch_path.resolve()
    output_dir = output_dir.resolve()
    patcher, infos = analyze_patch(patch_path, **analysis_options)
    if not infos:
        raise ConversionError(f"aucun objet faustgen~ trouvé dans {patch_path}")
    missing = [info for info in infos if info.source is None]
    if missing:
        details = ", ".join(info.location for info in missing)
        raise ConversionError(f"propriété sourcecode manquante pour: {details}")

    output_patch = output_dir / f"{patch_path.stem}-compiled.maxpat"
    manifest_path = output_dir / f"{patch_path.stem}-compiled.json"
    units = _compilation_units(infos, output_dir, patch_path.parent)
    products = [output_patch, manifest_path]
    products.extend(unit.source_path for unit in units)
    products.extend(output_dir / f"{unit.name}~.mxo" for unit in units)
    existing = [path for path in products if path.exists()]
    if existing and not force:
        shown = ", ".join(str(path) for path in existing[:3])
        raise ConversionError(f"sortie déjà existante ({shown}); utiliser --force")

    output_dir.mkdir(parents=True, exist_ok=True)
    # Keep transient compiler products isolated from the requested output and
    # expose include directories through short symlinks for compatibility with
    # older installed faust2max6 scripts. Copy products only after all builds.
    with tempfile.TemporaryDirectory(prefix="faustgen2max-") as temporary:
        staging = Path(temporary)
        staged_bundles: List[Path] = []
        for unit_index, unit in enumerate(units):
            staged_source = staging / f"{unit.name}.dsp"
            staged_source.write_text(unit.source, encoding="utf-8")
            staged_args = list(unit.args)
            for include_index, include_dir in enumerate(unit.include_dirs):
                alias = staging / f"include_{unit_index}_{include_index}"
                alias.symlink_to(include_dir, target_is_directory=True)
                staged_args.extend(["-A", str(alias)])
            command = [faust2max6] + staged_args + [str(staged_source)]
            compile_runner(command, patch_path.parent)
            staged_bundle = staging / f"{unit.name}~.mxo"
            if not staged_bundle.exists():
                raise ConversionError(
                    f"faust2max6 n'a pas produit l'external attendu: {staged_bundle}"
                )
            staged_bundles.append(staged_bundle)

        # Publish generated products only after every compilation unit has
        # succeeded. This keeps a failed --force conversion from replacing a
        # previously working source or external with a partial result.
        for unit, staged_bundle in zip(units, staged_bundles):
            unit.source_path.write_text(unit.source, encoding="utf-8")
            bundle = output_dir / f"{unit.name}~.mxo"
            if bundle.exists():
                if bundle.is_dir():
                    shutil.rmtree(bundle)
                else:
                    bundle.unlink()
            if staged_bundle.is_dir():
                shutil.copytree(staged_bundle, bundle, symlinks=True)
            else:
                shutil.copy2(staged_bundle, bundle)

    for info in infos:
        assert info.external_name is not None
        _remove_faustgen_state(info.box)
        info.box.__dict__["text"] = f"{info.external_name}~"

    # A stale cache entry can make Max resolve faustgen~ even though no such box
    # remains.  New externals are siblings of the generated patch and resolve via
    # the patcher's own directory, so they do not need absolute cache entries.
    dependency_cache = getattr(patcher, "dependency_cache", None)
    if isinstance(dependency_cache, list):
        patcher.dependency_cache = [
            item
            for item in dependency_cache
            if not (
                isinstance(item, dict)
                and str(item.get("name", "")) in {"faustgen~.mxo", "mc.faustgen~.mxo"}
            )
        ]

    patcher.save_as(output_patch)
    manifest = {
        "input_patch": str(patch_path),
        "output_patch": str(output_patch),
        "faust2max6": faust2max6,
        "objects": [info.public_dict() for info in infos],
        "externals": [
            {
                "name": unit.name,
                "source": str(unit.source_path),
                "bundle": str(output_dir / f"{unit.name}~.mxo"),
                "args": unit.args,
                "include_dirs": [str(path) for path in unit.include_dirs],
                "objects": [info.location for info in unit.objects],
            }
            for unit in units
        ],
    }
    manifest_path.write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    return output_patch, manifest_path, infos


def _collect_patches(inputs: Sequence[str]) -> List[Path]:
    """Expand input files/directories to unique, recursively found patches."""

    patches: List[Path] = []
    for raw in inputs:
        path = Path(raw).expanduser()
        if path.is_dir():
            patches.extend(sorted(path.rglob("*.maxpat")))
        elif path.is_file() and path.suffix.lower() == ".maxpat":
            patches.append(path)
        else:
            raise ConversionError(f"entrée .maxpat introuvable: {path}")
    return list(dict.fromkeys(path.resolve() for path in patches))


def _mode(value: str) -> str:
    """Normalize an auto/always/never option, including French aliases."""

    aliases = {"oui": "always", "non": "never", "toujours": "always", "jamais": "never"}
    value = aliases.get(value.lower(), value.lower())
    if value not in {"auto", "always", "never"}:
        raise argparse.ArgumentTypeError("valeur attendue: auto, always ou never")
    return value


def build_parser() -> argparse.ArgumentParser:
    """Build the command-line parser for :func:`main`."""

    parser = argparse.ArgumentParser(
        description="Convertit des patches faustgen~/mc.faustgen~ en externals faust2max6."
    )
    parser.add_argument(
        "inputs",
        nargs="+",
        help="patch(es) .maxpat ou répertoire(s), parcourus récursivement",
    )
    parser.add_argument(
        "-o",
        "--output-dir",
        help="répertoire de sortie explicite (un seul patch uniquement)",
    )
    parser.add_argument(
        "--output-root",
        help="racine contenant un sous-répertoire compilé par patch",
    )
    parser.add_argument(
        "--analyze",
        action="store_true",
        help="imprime l'analyse JSON sans écrire de fichier ni compiler",
    )
    parser.add_argument(
        "--name",
        action="append",
        default=[],
        metavar="SELECTEUR=NOM_EXTERNAL",
        help="nom d'external par emplacement, id, varname ou occurrence (répétable)",
    )
    parser.add_argument(
        "--midi",
        type=_mode,
        default="auto",
        metavar="{auto,always,never}",
        help="détection ou activation du support MIDI (défaut: auto)",
    )
    parser.add_argument(
        "--osc",
        type=_mode,
        default="auto",
        metavar="{auto,always,never}",
        help="détection ou activation du support OSC (défaut: auto)",
    )
    parser.add_argument(
        "--soundfile",
        type=_mode,
        default="auto",
        metavar="{auto,always,never}",
        help="détection ou activation du support soundfile (défaut: auto)",
    )
    parser.add_argument(
        "--nvoices",
        type=int,
        metavar="N",
        help="nombre global de voix, prioritaire sur les valeurs détectées",
    )
    parser.add_argument(
        "--arch",
        choices=("auto", "arm64", "x86_64", "universal"),
        default="auto",
        help="architecture macOS des externals (défaut: auto)",
    )
    parser.add_argument(
        "--compiler-arg",
        action="append",
        default=[],
        metavar="ARG",
        help="argument faust2max6/Faust supplémentaire, répétable (ex.: =-vec)",
    )
    parser.add_argument(
        "--faust2max6",
        default="faust2max6",
        metavar="CHEMIN",
        help="exécutable faust2max6 (défaut: copie du dépôt, sinon PATH)",
    )
    parser.add_argument(
        "--force",
        action="store_true",
        help="remplace uniquement les produits générés qui existent déjà",
    )
    return parser


def main(argv: Optional[Sequence[str]] = None) -> int:
    """Run the converter CLI and return a process-style status code.

    Status 0 means success.  Analysis returns 1 when at least one input has no
    faustgen object.  Conversion/configuration errors return 2.
    """

    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        patches = _collect_patches(args.inputs)
        if not patches:
            raise ConversionError("aucun patch .maxpat trouvé")
        if args.output_dir and len(patches) != 1:
            raise ConversionError("--output-dir ne peut être utilisé qu'avec un seul patch")
        if args.output_dir and args.output_root:
            raise ConversionError("choisir --output-dir ou --output-root, pas les deux")

        name_overrides = _parse_assignments(args.name, "--name")
        compiler_args = list(args.compiler_arg)
        if args.arch != "auto":
            compiler_args[0:0] = ["-arch", args.arch]
        analysis_options = dict(
            name_overrides=name_overrides,
            midi_mode=args.midi,
            osc_mode=args.osc,
            soundfile_mode=args.soundfile,
            nvoices_override=args.nvoices,
            compiler_args=compiler_args,
        )

        if args.analyze:
            reports = []
            for patch in patches:
                _, infos = analyze_patch(patch, **analysis_options)
                reports.append(
                    {"patch": str(patch), "objects": [info.public_dict() for info in infos]}
                )
            print(json.dumps(reports, indent=2, ensure_ascii=False))
            return 0 if all(report["objects"] for report in reports) else 1

        compiler: Optional[str]
        local_compiler = Path(__file__).resolve().parents[2] / "tools/faust2appls/faust2max6"
        if args.faust2max6 == "faust2max6" and local_compiler.is_file():
            compiler = str(local_compiler)
        elif "/" not in args.faust2max6:
            compiler = shutil.which(args.faust2max6)
        else:
            compiler = str(Path(args.faust2max6).expanduser().resolve())
        if not compiler or not Path(compiler).is_file():
            raise ConversionError(f"faust2max6 introuvable: {args.faust2max6}")

        output_root = Path(args.output_root).expanduser().resolve() if args.output_root else None
        for patch in patches:
            if args.output_dir:
                output_dir = Path(args.output_dir).expanduser()
            elif output_root:
                output_dir = output_root / f"{patch.stem}-compiled"
            else:
                output_dir = patch.parent / f"{patch.stem}-compiled"
            output_patch, manifest, infos = convert_patch(
                patch,
                output_dir,
                faust2max6=str(compiler),
                force=args.force,
                **analysis_options,
            )
            print(f"OK: {output_patch}")
            print(f"    manifeste: {manifest}")
            for info in infos:
                for warning in info.warnings:
                    print(f"    attention {info.location}: {warning}", file=sys.stderr)
        return 0
    except (ConversionError, OSError, json.JSONDecodeError) as error:
        print(f"erreur: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
