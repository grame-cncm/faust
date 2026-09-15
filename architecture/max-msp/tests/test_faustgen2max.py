"""Regression tests for the :mod:`faustgen2max` patch converter.

The tests use synthetic ``.maxpat`` fixtures so that patch traversal and
rewriting can be checked without starting Max.  External compilation is
replaced by a small fake compiler; only the environment-building test mocks
``subprocess.run`` directly.
"""

import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock


# Load the standalone command as a module without requiring max-msp to be a
# Python package.  Registering it in sys.modules is needed by dataclasses.
SCRIPT = Path(__file__).resolve().parents[1] / "faustgen2max.py"
SPEC = importlib.util.spec_from_file_location("faustgen2max", SCRIPT)
assert SPEC and SPEC.loader
faustgen2max = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = faustgen2max
SPEC.loader.exec_module(faustgen2max)


def patch_fixture(path: Path, nested: bool = False, with_source: bool = True) -> None:
    """Write a minimal Max patch containing one realistically shaped faustgen~ box.

    ``nested`` puts the object inside a ``p`` subpatcher to exercise recursive
    traversal. ``with_source`` can omit the only compilable representation and
    therefore produces the converter's expected error case.
    """

    # Cache fields deliberately accompany sourcecode.  A successful rewrite
    # must remove these faustgen~-specific implementation details.
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
    # The message-to-faustgen~ connection allows the tests to verify both MIDI
    # inference and preservation of box ids and patch cords.
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
        # Preserve the same inner patch but wrap it in a top-level subpatcher.
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


def multi_patch_fixture(path: Path) -> None:
    """Write three faustgen~ objects distributed over three patcher levels.

    Two objects intentionally share source and build settings, while the third
    has different source under the same declared name. This simultaneously
    exercises recursive discovery, compilation deduplication, and name
    collision handling.
    """

    def faust_box(box_id: str, source: str) -> dict:
        return {
            "box": {
                "id": box_id,
                "maxclass": "newobj",
                "numinlets": 1,
                "numoutlets": 1,
                "outlettype": ["signal"],
                "patching_rect": [100.0, 100.0, 64.0, 22.0],
                "text": "faustgen~",
                "machinecode": "obsolete",
                "sourcecode": source,
            }
        }

    def message(box_id: str) -> dict:
        return {
            "box": {
                "id": box_id,
                "maxclass": "message",
                "numinlets": 2,
                "numoutlets": 1,
                "patching_rect": [10.0, 10.0, 40.0, 22.0],
                "text": "bang",
            }
        }

    def patcher(boxes: list[dict], lines: list[dict]) -> dict:
        return {
            "fileversion": 1,
            "appversion": {"major": 9, "minor": 0, "revision": 0, "architecture": "x64"},
            "classnamespace": "box",
            "rect": [0.0, 0.0, 640.0, 480.0],
            "boxes": boxes,
            "lines": lines,
            "dependency_cache": [],
            "autosave": 0,
        }

    def line(source: str, destination: str) -> dict:
        return {"patchline": {"source": [source, 0], "destination": [destination, 0]}}

    shared = 'declare name "Shared"; process = _;'
    distinct = 'declare name "Shared"; process = 0;'
    deepest = patcher(
        [message("obj-21"), faust_box("obj-5", distinct)],
        [line("obj-21", "obj-5")],
    )
    middle = patcher(
        [
            message("obj-11"),
            faust_box("obj-3", shared),
            {
                "box": {
                    "id": "obj-4",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [200.0, 100.0, 80.0, 22.0],
                    "text": "p deepest",
                    "patcher": deepest,
                }
            },
        ],
        [line("obj-11", "obj-3")],
    )
    top = patcher(
        [
            message("obj-1"),
            faust_box("obj-2", shared),
            {
                "box": {
                    "id": "obj-10",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [200.0, 100.0, 80.0, 22.0],
                    "text": "p nested",
                    "patcher": middle,
                }
            },
        ],
        [line("obj-1", "obj-2")],
    )
    path.write_text(json.dumps({"patcher": top}), encoding="utf-8")


def nested_boxes(value: object):
    """Yield every Max box dictionary from a serialized patch hierarchy."""

    if isinstance(value, dict):
        if "box" in value and isinstance(value["box"], dict):
            yield value["box"]
        for item in value.values():
            yield from nested_boxes(item)
    elif isinstance(value, list):
        for item in value:
            yield from nested_boxes(item)


def nested_values(value: object, key: str):
    """Yield all values stored under ``key`` in a JSON-compatible tree."""

    if isinstance(value, dict):
        for item_key, item_value in value.items():
            if item_key == key:
                yield item_value
            yield from nested_values(item_value, key)
    elif isinstance(value, list):
        for item in value:
            yield from nested_values(item, key)


class Faustgen2MaxTests(unittest.TestCase):
    """Exercise architecture selection, analysis, conversion, and errors."""

    def test_default_compile_uses_matching_source_architecture(self):
        """Point both Faust architecture variables at this source checkout."""

        completed = mock.Mock(returncode=0, stdout="")
        with mock.patch.dict(faustgen2max.os.environ, {}, clear=True), mock.patch.object(
            faustgen2max.subprocess, "run", return_value=completed
        ) as run:
            faustgen2max._default_compile(["faust2max6", "test.dsp"], Path("/tmp"))

        environment = run.call_args.kwargs["env"]
        self.assertEqual(environment["FAUSTARCH"], str(SCRIPT.parents[1]))
        self.assertEqual(environment["FAUST_ARCH_PATH"], str(SCRIPT.parents[1]))

    def test_analyze_finds_nested_faustgen_and_infers_midi(self):
        """Find a nested object and infer MIDI support from its incoming message."""

        with tempfile.TemporaryDirectory() as directory:
            patch = Path(directory) / "nested.maxpat"
            patch_fixture(patch, nested=True)
            _, infos = faustgen2max.analyze_patch(patch)
            self.assertEqual(len(infos), 1)
            self.assertEqual(infos[0].location, "root/obj-20/obj-2")
            self.assertTrue(infos[0].midi)
            self.assertEqual(infos[0].external_name, "test_dsp")

    def test_convert_preserves_id_wiring_and_removes_faustgen_state(self):
        """Replace faustgen~ while preserving graph identity and connectivity."""

        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            patch = root / "simple.maxpat"
            output = root / "compiled"
            patch_fixture(patch)

            def fake_compiler(command, cwd):
                """Create the bundle directory expected from a successful compile."""

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

    def test_multiple_nested_objects_deduplicate_and_resolve_name_collisions(self):
        """Compile identical units once and suffix a distinct colliding source."""

        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            patch = root / "multiple.maxpat"
            output = root / "compiled"
            multi_patch_fixture(patch)
            commands = []

            def fake_compiler(command, cwd):
                """Record each unique compilation and create its expected bundle."""

                commands.append(list(command))
                dsp = Path(command[-1])
                (dsp.parent / f"{dsp.stem}~.mxo").mkdir()

            generated, manifest_path, infos = faustgen2max.convert_patch(
                patch, output, compile_runner=fake_compiler
            )

            self.assertEqual(
                [info.location for info in infos],
                ["root/obj-2", "root/obj-10/obj-3", "root/obj-10/obj-4/obj-5"],
            )
            self.assertEqual(len(commands), 2)
            self.assertEqual(
                [info.external_name for info in infos],
                ["shared", "shared", "shared_3"],
            )

            patch_data = json.loads(generated.read_text(encoding="utf-8"))
            boxes = {box["id"]: box for box in nested_boxes(patch_data) if "id" in box}
            self.assertEqual(boxes["obj-2"]["text"], "shared~")
            self.assertEqual(boxes["obj-3"]["text"], "shared~")
            self.assertEqual(boxes["obj-5"]["text"], "shared_3~")
            for object_id in ("obj-2", "obj-3", "obj-5"):
                self.assertNotIn("sourcecode", boxes[object_id])
                self.assertNotIn("machinecode", boxes[object_id])

            destinations = list(nested_values(patch_data, "destination"))
            for object_id in ("obj-2", "obj-3", "obj-5"):
                self.assertIn([object_id, 0], destinations)

            manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
            self.assertEqual(len(manifest["externals"]), 2)
            self.assertEqual(len(manifest["externals"][0]["objects"]), 2)

    def test_voice_override_wins_over_source_and_message_counts(self):
        """Pass an API voice override even when the source declares nvoices."""

        with tempfile.TemporaryDirectory() as directory:
            patch = Path(directory) / "poly.maxpat"
            patch_fixture(patch)
            data = json.loads(patch.read_text(encoding="utf-8"))
            boxes = data["patcher"]["boxes"]
            boxes[0]["box"]["text"] = "polyphony 24"
            boxes[1]["box"]["sourcecode"] = (
                'declare name "Test DSP"; declare nvoices "12"; process = _;'
            )
            patch.write_text(json.dumps(data), encoding="utf-8")

            _, infos = faustgen2max.analyze_patch(patch, nvoices_override=7)
            self.assertEqual(infos[0].nvoices, 7)
            self.assertIn("-nvoices", infos[0].compile_args)
            voice_index = infos[0].compile_args.index("-nvoices")
            self.assertEqual(infos[0].compile_args[voice_index + 1], "7")
            self.assertTrue(any("polyphony 24" in warning for warning in infos[0].warnings))

    def test_failed_compilation_publishes_no_partial_products(self):
        """Keep new and existing outputs untouched until every compile succeeds."""

        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            patch = root / "simple.maxpat"
            patch_fixture(patch)

            def fail_compiler(command, cwd):
                """Model a compiler failure before an external can be published."""

                raise faustgen2max.ConversionError("compiler failed")

            # With two unique units, allow the first compile to succeed before
            # failing the second. Even that completed staged bundle must not be
            # visible in the requested output directory.
            multiple = root / "multiple.maxpat"
            multi_patch_fixture(multiple)
            compile_count = 0

            def fail_second_compiler(command, cwd):
                """Produce one staged bundle, then fail the following unit."""

                nonlocal compile_count
                compile_count += 1
                dsp = Path(command[-1])
                if compile_count == 1:
                    (dsp.parent / f"{dsp.stem}~.mxo").mkdir()
                else:
                    raise faustgen2max.ConversionError("second compiler failed")

            empty_output = root / "empty-output"
            with self.assertRaises(faustgen2max.ConversionError):
                faustgen2max.convert_patch(
                    multiple,
                    empty_output,
                    compile_runner=fail_second_compiler,
                )
            self.assertEqual(compile_count, 2)
            self.assertEqual(list(empty_output.iterdir()), [])

            missing_output = root / "missing-bundle"
            with self.assertRaises(faustgen2max.ConversionError):
                faustgen2max.convert_patch(
                    patch, missing_output, compile_runner=lambda *_: None
                )
            self.assertEqual(list(missing_output.iterdir()), [])

            preserved = root / "preserved"
            preserved.mkdir()
            source = preserved / "test_dsp.dsp"
            bundle = preserved / "test_dsp~.mxo"
            output_patch = preserved / "simple-compiled.maxpat"
            manifest = preserved / "simple-compiled.json"
            source.write_text("old source", encoding="utf-8")
            bundle.mkdir()
            marker = bundle / "old-marker"
            marker.write_text("old bundle", encoding="utf-8")
            output_patch.write_text("old patch", encoding="utf-8")
            manifest.write_text("old manifest", encoding="utf-8")

            with self.assertRaises(faustgen2max.ConversionError):
                faustgen2max.convert_patch(
                    patch,
                    preserved,
                    force=True,
                    compile_runner=fail_compiler,
                )
            self.assertEqual(source.read_text(encoding="utf-8"), "old source")
            self.assertEqual(marker.read_text(encoding="utf-8"), "old bundle")
            self.assertEqual(output_patch.read_text(encoding="utf-8"), "old patch")
            self.assertEqual(manifest.read_text(encoding="utf-8"), "old manifest")

    def test_missing_sourcecode_is_rejected(self):
        """Reject a faustgen~ cache when no reproducible Faust source is present."""

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
