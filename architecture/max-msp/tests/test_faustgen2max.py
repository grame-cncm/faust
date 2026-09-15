"""Regression tests for the faustgen~ patch compiler."""

import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "faustgen2max.py"
SPEC = importlib.util.spec_from_file_location("faustgen2max", SCRIPT)
assert SPEC and SPEC.loader
faustgen2max = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = faustgen2max
SPEC.loader.exec_module(faustgen2max)


def patch_fixture(path: Path, nested: bool = False, with_source: bool = True) -> None:
    faust_box = {
        "id": "obj-2",
        "maxclass": "newobj",
        "numinlets": 1,
        "numoutlets": 3,
        "outlettype": ["signal", "", ""],
        "patching_rect": [100.0, 100.0, 64.0, 22.0],
        "text": "faustgen~",
        "varname": "test_faustgen",
        "machinecode": "obsolete",
        "machinecode_size": 8,
        "sourcecode": 'declare name "Test DSP"; process = _;' if with_source else None,
        "sourcecode_size": 37 if with_source else None,
        "version": "1.99",
    }
    faust_box = {key: value for key, value in faust_box.items() if value is not None}
    inner = {
        "fileversion": 1,
        "appversion": {"major": 9, "minor": 0, "revision": 0, "architecture": "x64"},
        "classnamespace": "box",
        "rect": [0.0, 0.0, 640.0, 480.0],
        "boxes": [
            {
                "box": {
                    "id": "obj-1",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "patching_rect": [10.0, 10.0, 80.0, 22.0],
                    "text": "midievent 144 60 100",
                }
            },
            {"box": faust_box},
        ],
        "lines": [
            {"patchline": {"source": ["obj-1", 0], "destination": ["obj-2", 0]}}
        ],
    }
    if nested:
        top = {
            **{key: value for key, value in inner.items() if key not in {"boxes", "lines"}},
            "boxes": [
                {
                    "box": {
                        "id": "obj-20",
                        "maxclass": "newobj",
                        "numinlets": 1,
                        "numoutlets": 1,
                        "patching_rect": [10.0, 10.0, 80.0, 22.0],
                        "text": "p nested",
                        "patcher": inner,
                    }
                }
            ],
            "lines": [],
            "dependency_cache": [],
            "autosave": 0,
        }
    else:
        top = {**inner, "dependency_cache": [], "autosave": 0}
    path.write_text(json.dumps({"patcher": top}), encoding="utf-8")


class Faustgen2MaxTests(unittest.TestCase):
    def test_analyze_finds_nested_faustgen_and_infers_midi(self):
        with tempfile.TemporaryDirectory() as directory:
            patch = Path(directory) / "nested.maxpat"
            patch_fixture(patch, nested=True)
            _, infos = faustgen2max.analyze_patch(patch)
            self.assertEqual(len(infos), 1)
            self.assertEqual(infos[0].location, "root/obj-20/obj-2")
            self.assertTrue(infos[0].midi)
            self.assertEqual(infos[0].external_name, "test_dsp")

    def test_convert_preserves_id_wiring_and_removes_faustgen_state(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            patch = root / "simple.maxpat"
            output = root / "compiled"
            patch_fixture(patch)

            def fake_compiler(command, cwd):
                dsp = Path(command[-1])
                (dsp.parent / f"{dsp.stem}~.mxo").mkdir()

            generated, manifest, infos = faustgen2max.convert_patch(
                patch, output, faust2max6="fake-faust2max6", compile_runner=fake_compiler
            )
            data = json.loads(generated.read_text())["patcher"]
            boxes = {item["box"]["id"]: item["box"] for item in data["boxes"]}
            self.assertEqual(boxes["obj-2"]["text"], "test_dsp~")
            self.assertNotIn("sourcecode", boxes["obj-2"])
            self.assertNotIn("machinecode", boxes["obj-2"])
            self.assertEqual(
                data["lines"][0]["patchline"]["destination"], ["obj-2", 0]
            )
            self.assertTrue(manifest.is_file())
            self.assertEqual(infos[0].object_id, "obj-2")

    def test_missing_sourcecode_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            patch = root / "old.maxpat"
            patch_fixture(patch, with_source=False)
            with self.assertRaises(faustgen2max.ConversionError):
                faustgen2max.convert_patch(
                    patch, root / "out", faust2max6="fake", compile_runner=lambda *_: None
                )


if __name__ == "__main__":
    unittest.main()
