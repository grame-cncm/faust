"""Regression tests for the :mod:`max2faustgen` converter.

The fixtures are synthetic: a fake ``faust2max6`` bundle holding the three
sources the converter reads, and small ``.maxpat`` files.  Neither Max nor a
Faust compiler is needed; ``--check`` is exercised with fake compilers.
"""

import contextlib
import importlib.util
import io
import json
import os
import stat
import sys
import tempfile
import unittest
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "max2faustgen.py"
SPEC = importlib.util.spec_from_file_location("max2faustgen", SCRIPT)
assert SPEC and SPEC.loader
max2faustgen = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = max2faustgen
SPEC.loader.exec_module(max2faustgen)


ORIGINAL = 'declare name "osc";\nprocess = library("my.lib").osc;\n'
EXPANDED = 'declare name "osc";\nprocess = _, _ : + : *(0.5);\n'
OPTIONS_LINE = ("-a /x/max-msp/max-msp64.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 "
                "-cn osc -es 1 -mcd 16 -double -ftz 0")


def make_bundle(directory: Path, name: str = "osc", options: str = OPTIONS_LINE,
                inputs: int = 2, outputs: int = 1, sources: bool = True,
                binary: str = "plain", resources: bool = True) -> Path:
    """Write a bundle shaped like a faust2max6 output, sources at its top.

    ``binary`` is "plain" or "mc" for a binary holding the strings of an
    external compiled without or with -mc, or "none" for no binary.
    ``resources`` puts the sources in Contents/Resources, as faust2max6 does;
    older versions put them at the top of the bundle.
    """

    bundle = directory / f"{name}~.mxo"
    macos = bundle / "Contents" / "MacOS"
    macos.mkdir(parents=True)
    if binary != "none":
        strings = {"plain": b"\0(signal) : Audio Output %ld\0signal\0list\0",
                   "mc": b"\0(multi-channel signal) : Audio Output %ld\0"
                         b"multichannelsignal\0list\0"}[binary]
        (macos / f"{name}~").write_bytes(b"\xcf\xfa\xed\xfe" + strings)
    folder = bundle / "Contents" / "Resources" if resources else bundle
    folder.mkdir(parents=True, exist_ok=True)
    if sources:
        (folder / f"{name}.dsp").write_text(ORIGINAL, encoding="utf-8")
        (folder / f"{name}-exp.dsp").write_text(EXPANDED, encoding="utf-8")
        # Wrapper classes forward the counts; only the DSP class has constants.
        (folder / f"{name}.cpp").write_text(
            "/* ------------------------------------------------------------\n"
            f"Code generated with Faust 2.85.9\nCompilation options: {options}\n"
            "------------------------------------------------------------ */\n"
            "class decorator_dsp {\n"
            "    virtual int getNumInputs() { return fDSP->getNumInputs(); }\n"
            "    virtual int getNumOutputs() { return fDSP->getNumOutputs(); }\n"
            "};\n"
            f"class {name} : public dsp {{\n"
            f"\tvirtual int getNumInputs() {{\n\t\treturn {inputs};\n\t}}\n"
            f"\tvirtual int getNumOutputs() {{\n\t\treturn {outputs};\n\t}}\n"
            "};\n",
            encoding="utf-8")
    return bundle


def box(id_, text, maxclass="newobj", **extra):
    content = {"id": id_, "maxclass": maxclass, "text": text,
               "patching_rect": [10.0, 10.0, 80.0, 22.0]}
    content.update(extra)
    return {"box": content}


def line(src, outlet, dst, inlet):
    return {"patchline": {"source": [src, outlet], "destination": [dst, inlet]}}


def patcher(boxes, lines):
    return {"fileversion": 1,
            "appversion": {"major": 9, "minor": 0, "revision": 3, "architecture": "x64"},
            "classnamespace": "box", "rect": [0.0, 0.0, 640.0, 480.0],
            "boxes": boxes, "lines": lines}


def abstraction_patch(path: Path, external_text: str = "osc~", **external_attrs) -> dict:
    """A patch shaped like a generated abstraction: boxes without port counts,
    a comment naming the external, and a subpatcher with an mc outlet."""

    inner = patcher([box("in-1", "", maxclass="inlet", outlettype=["multichannelsignal"]),
                     box("out-1", "", maxclass="outlet")],
                    [line("in-1", 0, "out-1", 0)])
    content = {"patcher": patcher(
        [
            box("c-1", "osc~ order 3, comment", maxclass="comment"),
            box("u-1", "mc.unpack~ 2"),
            box("x-1", external_text, **external_attrs),
            box("p-1", "p sub", numinlets=1, numoutlets=1,
                outlettype=["multichannelsignal"], patcher=inner),
            box("m-1", "freq 440", maxclass="message", numinlets=2, numoutlets=1,
                outlettype=[""]),
        ],
        [line("u-1", 0, "x-1", 0), line("u-1", 1, "x-1", 1), line("m-1", 0, "x-1", 0),
         line("x-1", 0, "p-1", 0), line("x-1", 1, "p-1", 0)],
    )}
    content["patcher"]["dependency_cache"] = [{"name": "osc~.mxo", "type": "iLaX"},
                                              {"name": "other.js", "type": "TEXT"}]
    path.write_text(json.dumps(content, indent=2), encoding="utf-8")
    return content


def boxes_by_id(p, found=None):
    found = {} if found is None else found
    for entry in p["boxes"]:
        found[entry["box"]["id"]] = entry["box"]
        if "patcher" in entry["box"]:
            boxes_by_id(entry["box"]["patcher"], found)
    return found


def run(*argv):
    """Run main(), returning (status, stdout, stderr)."""

    out, err = io.StringIO(), io.StringIO()
    with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
        status = max2faustgen.main([str(a) for a in argv])
    return status, out.getvalue(), err.getvalue()


def fake_compiler(directory: Path, fail: bool) -> Path:
    script = directory / ("bad-faust" if fail else "good-faust")
    body = 'echo "1 : ERROR : undefined symbol : nope" >&2; exit 1' if fail else "exit 0"
    script.write_text(f"#!/bin/sh\n{body}\n", encoding="utf-8")
    script.chmod(script.stat().st_mode | stat.S_IEXEC)
    return script


class Max2FaustgenTest(unittest.TestCase):

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        self.project = self.root / "project"
        (self.project / "externals").mkdir(parents=True)
        (self.project / "patchers").mkdir()
        self.patch = self.project / "patchers" / "osc-abstraction.maxpat"

    def tearDown(self):
        self.tmp.cleanup()

    def convert(self, *extra, external_text="osc~", bundle_kw=None, **attrs):
        make_bundle(self.project / "externals", **(bundle_kw or {}))
        original = abstraction_patch(self.patch, external_text, **attrs)
        out = self.root / "out"
        status, stdout, stderr = run(self.project, "-o", out, *extra)
        return original, out, status, stdout, stderr

    def converted(self, out):
        return json.loads((out / "patchers" / self.patch.name).read_text(encoding="utf-8"))

    def test_box_is_rewritten_as_faustgen(self):
        original, out, status, _, stderr = self.convert()
        self.assertEqual(status, 0, stderr)
        result = boxes_by_id(self.converted(out)["patcher"])["x-1"]
        self.assertEqual(result["text"], "faustgen~ osc")
        self.assertEqual(result["annotation"], "osc~")
        self.assertEqual(result["sourcecode"], EXPANDED)
        self.assertEqual(result["sourcecode_size"], len(EXPANDED.encode("utf-8")))
        options = [result[f"compile_option{i}"] for i in range(8)]
        self.assertEqual(options, ["-ct", "1", "-es", "1", "-mcd", "16", "-double", "-ftz"])
        self.assertEqual(result["compile_option8"], "0")
        self.assertNotIn("compile_option9", result)
        self.assertEqual((result["numinlets"], result["numoutlets"]), (2, 3))
        self.assertEqual(result["outlettype"], ["signal", "", ""])
        self.assertEqual(result["patching_rect"], [10.0, 10.0, 80.0, 22.0])
        manifest = json.loads((out / max2faustgen.MANIFEST).read_text(encoding="utf-8"))
        self.assertEqual(manifest["externals"][0]["name"], "osc~")
        self.assertEqual(len(manifest["patches"][str(self.patch.resolve())]), 1)

    def test_everything_else_is_written_back_unchanged(self):
        original, out, status, _, stderr = self.convert()
        self.assertEqual(status, 0, stderr)
        result = self.converted(out)
        self.assertEqual(result["patcher"]["lines"], original["patcher"]["lines"])
        before = boxes_by_id(original["patcher"])
        after = boxes_by_id(result["patcher"])
        for id_, content in before.items():
            if id_ not in ("x-1", "p-1"):
                # No numinlets/numoutlets added to boxes saved without them.
                self.assertEqual(after[id_], content, id_)
        # The subpatcher keeps its declared multichannel outlet.
        self.assertEqual(after["p-1"]["outlettype"], ["multichannelsignal"])
        self.assertEqual(result["patcher"]["dependency_cache"],
                         [{"name": "other.js", "type": "TEXT"}])

    def test_inputs_are_never_modified(self):
        make_bundle(self.project / "externals")
        abstraction_patch(self.patch)
        before = self.patch.read_bytes()
        self.assertEqual(run(self.project, "-o", self.root / "out")[0], 0)
        self.assertEqual(run(self.project, "--analyze")[0], 0)
        self.assertEqual(self.patch.read_bytes(), before)

    def test_in_place(self):
        make_bundle(self.project / "externals")
        abstraction_patch(self.patch)
        status, _, stderr = run(self.patch, "-E", self.project / "externals", "--in-place")
        self.assertEqual(status, 0, stderr)
        result = boxes_by_id(json.loads(self.patch.read_text())["patcher"])
        self.assertEqual(result["x-1"]["text"], "faustgen~ osc")

    def test_analyze_writes_nothing(self):
        make_bundle(self.project / "externals")
        abstraction_patch(self.patch)
        status, stdout, _ = run(self.project, "--analyze")
        self.assertEqual(status, 0)
        report = json.loads(stdout)
        self.assertEqual(report["externals"][0]["inputs"], 2)
        self.assertFalse((self.root / "out").exists())

    def test_original_source_with_library_path(self):
        libs = self.root / "libs"
        libs.mkdir()
        _, out, status, _, stderr = self.convert("--source", "original", "-L", libs)
        self.assertEqual(status, 0, stderr)
        result = boxes_by_id(self.converted(out)["patcher"])["x-1"]
        self.assertEqual(result["sourcecode"], ORIGINAL)
        self.assertEqual(result["library_path0"], str(libs.resolve()))

    def test_extra_option_and_switches(self):
        _, out, status, _, _ = self.convert("--compile-option=-vec", "--no-factory-name",
                                            "--no-annotation")
        self.assertEqual(status, 0)
        result = boxes_by_id(self.converted(out)["patcher"])["x-1"]
        self.assertEqual(result["text"], "faustgen~")
        self.assertNotIn("annotation", result)
        self.assertEqual(result["compile_option9"], "-vec")

    def test_existing_annotation_is_kept(self):
        _, out, status, _, stderr = self.convert(annotation="mine")
        self.assertEqual(status, 0)
        self.assertEqual(boxes_by_id(self.converted(out)["patcher"])["x-1"]["annotation"],
                         "mine")
        self.assertIn("annotation existante", stderr)

    def mc_patch(self, binary, **attrs):
        """One external box fed by one cord into its first inlet."""

        make_bundle(self.project / "externals", binary=binary)
        self.patch.write_text(json.dumps({"patcher": patcher(
            [box("s-1", "mc.noise~ @chans 2"), box("x-1", "osc~", **attrs),
             box("d-1", "mc.dac~ 1 2")],
            [line("s-1", 0, "x-1", 0), line("x-1", 0, "d-1", 0)])}))
        status, _, stderr = run(self.project, "-o", self.root / "out")
        self.assertEqual(status, 0, stderr)
        return boxes_by_id(self.converted(self.root / "out")["patcher"])["x-1"], stderr

    def test_mc_external_in_a_box_saved_without_outlet_types(self):
        # Generated abstractions often omit the port fields: the binary decides.
        result, stderr = self.mc_patch("mc")
        self.assertEqual(result["text"], "mc.faustgen~ osc")
        self.assertEqual((result["numinlets"], result["numoutlets"]), (1, 3))
        self.assertEqual(result["outlettype"], ["multichannelsignal", "", ""])
        self.assertEqual(stderr, "")
        manifest = json.loads((self.root / "out" / max2faustgen.MANIFEST).read_text())
        self.assertIs(manifest["externals"][0]["multichannel"], True)

    def test_plain_external_in_a_box_saved_without_outlet_types(self):
        result, stderr = self.mc_patch("plain")
        self.assertEqual(result["text"], "faustgen~ osc")
        self.assertEqual(result["outlettype"], ["signal", "", ""])
        self.assertEqual(stderr, "")

    def test_a_plain_binary_wins_over_saved_mc_outlet_types(self):
        result, stderr = self.mc_patch("plain", outlettype=["multichannelsignal", ""])
        self.assertEqual(result["text"], "faustgen~ osc")
        self.assertIn("le binaire décide", stderr)

    def test_an_mc_binary_wins_over_saved_plain_outlet_types(self):
        result, stderr = self.mc_patch("mc", outlettype=["signal", ""])
        self.assertEqual(result["text"], "mc.faustgen~ osc")
        self.assertIn("le binaire décide", stderr)

    def test_without_binary_the_box_decides(self):
        result, stderr = self.mc_patch("none", outlettype=["multichannelsignal", ""])
        self.assertEqual(result["text"], "mc.faustgen~ osc")
        self.assertIn("pas de binaire", stderr)

    def test_cords_beyond_the_mc_ports_are_reported(self):
        make_bundle(self.project / "externals", binary="mc")
        abstraction_patch(self.patch)   # cords into inlet 1 and from outlet 1
        status, _, stderr = run(self.project, "-o", self.root / "out")
        self.assertEqual(status, 0)
        self.assertIn("inlet 1", stderr)
        self.assertIn("outlet 1", stderr)

    def test_nested_box(self):
        make_bundle(self.project / "externals")
        inner = patcher([box("x-9", "osc~")], [])
        self.patch.write_text(json.dumps(
            {"patcher": patcher([box("p-9", "p wrap", patcher=inner)], [])}))
        status, _, _ = run(self.project, "-o", self.root / "out")
        self.assertEqual(status, 0)
        result = boxes_by_id(self.converted(self.root / "out")["patcher"])
        self.assertEqual(result["x-9"]["text"], "faustgen~ osc")

    def test_cord_from_a_non_audio_outlet_is_reported(self):
        make_bundle(self.project / "externals", outputs=1)
        content = abstraction_patch(self.patch)
        content["patcher"]["lines"].append(line("x-1", 4, "p-1", 0))
        self.patch.write_text(json.dumps(content))
        status, _, stderr = run(self.project, "-o", self.root / "out")
        self.assertEqual(status, 0)
        self.assertIn("outlet 4", stderr)

    def test_arguments_are_rejected(self):
        _, _, status, _, stderr = self.convert(external_text="osc~ @freq 700")
        self.assertEqual(status, 2)
        self.assertIn("arguments", stderr)

    def test_unknown_option_is_rejected(self):
        _, _, status, _, stderr = self.convert(bundle_kw={"options": "-double -mystery 3"})
        self.assertEqual(status, 2)
        self.assertIn("-mystery", stderr)

    def test_sources_at_the_top_of_an_older_bundle(self):
        _, out, status, _, stderr = self.convert(bundle_kw={"resources": False})
        self.assertEqual(status, 0, stderr)
        self.assertEqual(boxes_by_id(self.converted(out)["patcher"])["x-1"]["sourcecode"],
                         EXPANDED)

    def test_bundle_without_sources_is_rejected(self):
        _, _, status, _, stderr = self.convert(bundle_kw={"sources": False})
        self.assertEqual(status, 2)
        self.assertIn("-nosrc", stderr)

    def test_no_external_used(self):
        make_bundle(self.project / "externals")
        abstraction_patch(self.patch, "cycle~ 440")
        self.assertEqual(run(self.project, "-o", self.root / "out")[0], 1)

    def test_existing_output_needs_force(self):
        _, out, status, _, _ = self.convert()
        self.assertEqual(status, 0)
        self.assertEqual(run(self.project, "-o", out)[0], 2)
        self.assertEqual(run(self.project, "-o", out, "--force")[0], 0)

    def test_a_destination_is_required(self):
        make_bundle(self.project / "externals")
        abstraction_patch(self.patch)
        self.assertEqual(run(self.project)[0], 2)

    def test_check_passes_and_fails(self):
        make_bundle(self.project / "externals")
        abstraction_patch(self.patch)
        good = fake_compiler(self.root, fail=False)
        bad = fake_compiler(self.root, fail=True)
        status, stdout, _ = run(self.project, "--analyze", "--check", good)
        self.assertEqual(status, 0)
        self.assertIn("1 programme(s) compilé(s)", stdout)
        status, _, stderr = run(self.project, "-o", self.root / "out", "--check", bad)
        self.assertEqual(status, 2)
        self.assertIn("undefined symbol", stderr)
        self.assertFalse((self.root / "out").exists())


if __name__ == "__main__":
    unittest.main()
