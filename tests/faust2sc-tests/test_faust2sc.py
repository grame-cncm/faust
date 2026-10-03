import contextlib
import importlib.util
import io
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch


SCRIPT = Path(__file__).resolve().parents[2] / "tools/faust2appls/faust2sc.py"
spec = importlib.util.spec_from_file_location("faust2sc", SCRIPT)
faust2sc = importlib.util.module_from_spec(spec)
spec.loader.exec_module(faust2sc)


class ConvertFilesTests(unittest.TestCase):
    def convert(self, dsp_file, arch=None, flags=""):
        with contextlib.redirect_stdout(io.StringIO()):
            return faust2sc.convert_files(dsp_file, "output", arch, flags)

    def test_default_architecture_without_extra_flags(self):
        with patch.object(faust2sc.subprocess, "run") as run:
            result = self.convert("oscillator.dsp")
        run.assert_called_once_with(
            ["faust", "-i", "-a", "supercollider.cpp", "-json",
             "oscillator.dsp", "-o", "oscillator.cpp"],
            check=True, capture_output=False,
        )
        self.assertEqual(result["json_file"], "oscillator.dsp.json")

    def test_input_paths_with_spaces_are_single_arguments(self):
        for dsp_file in ("My sounds/oscillator.dsp", "sounds/my oscillator.dsp"):
            with self.subTest(dsp_file=dsp_file):
                with patch.object(faust2sc.subprocess, "run") as run:
                    result = self.convert(dsp_file, flags="-double -vec")
                args = run.call_args.args[0]
                self.assertEqual(args[args.index("-json") + 1], dsp_file)
                self.assertEqual(args[args.index("-o") + 1], result["cpp_file"])
                self.assertEqual(args[-2:], ["-double", "-vec"])
                self.assertEqual(len(args), 10)

    def test_custom_architecture_path_with_spaces(self):
        with patch.object(faust2sc.subprocess, "run") as run:
            self.convert("oscillator.dsp", arch="My architectures/custom.cpp")
        args = run.call_args.args[0]
        self.assertEqual(args[args.index("-a") + 1], "My architectures/custom.cpp")
        self.assertEqual(len(args), 8)

    def test_compiler_failure_exits(self):
        failure = subprocess.CalledProcessError(1, "faust")
        with patch.object(faust2sc.subprocess, "run", side_effect=failure):
            with self.assertRaisesRegex(SystemExit, "faust failed to compile json file"):
                self.convert("oscillator.dsp")


class ControlArgumentsTests(unittest.TestCase):
    def setUp(self):
        self.data = {
            "inputs": 1,
            "ui": [
                {"type": "vgroup", "label": "main", "items": [
                    {"type": "button", "label": "gate"},
                    {"type": "hgroup", "label": "envelope", "items": [
                        {"type": "hslider", "label": "attack", "init": 0.25},
                        {"type": "hbargraph", "label": "meter"},
                        {"type": "tgroup", "label": "options", "items": [
                            {"type": "checkbox", "label": "hold"},
                            {"type": "vslider", "label": "release", "init": 0.5,
                             "meta": [{"tooltip": "Release time"}]},
                        ]},
                    ]},
                ]},
                {"type": "hgroup", "label": "other", "items": [
                    {"type": "nentry", "label": "voices", "init": 4},
                    {"type": "vbargraph", "label": "output"},
                    {"type": "soundfile", "label": "sample"},
                ]},
            ],
        }

    def test_nested_groups_preserve_active_control_order(self):
        self.assertEqual(
            faust2sc.get_parameter_list(self.data, False),
            "in0,gate, attack, hold, release, voices",
        )
        self.assertEqual(
            faust2sc.get_parameter_list(self.data, True),
            "in0,gate(0), attack(0.25), hold(0), release(0.5), voices(4)",
        )

    def test_help_uses_control_names_instead_of_group_names(self):
        help_text = faust2sc.get_help_file_arguments(self.data)
        self.assertEqual(
            [line for line in help_text.splitlines() if line.startswith("ARGUMENT::")],
            ["ARGUMENT::gate", "ARGUMENT::attack", "ARGUMENT::hold",
             "ARGUMENT::release", "ARGUMENT::voices"],
        )
        self.assertIn("ARGUMENT::release\nRelease time\n", help_text)

    def test_duplicate_names_and_audio_inputs_are_distinct(self):
        self.data["ui"] = [{"type": "hslider", "label": label, "init": value}
                           for value, label in enumerate(("in0", "gain", "Gain", "gain 2"))]
        self.assertEqual(
            faust2sc.get_parameter_list(self.data, False),
            "in0,in0_2, gain, gain_2, gain_2_2",
        )

    def test_empty_ui_has_no_controls(self):
        for ui in ([], [{"type": "vgroup", "label": "empty", "items": []}]):
            with self.subTest(ui=ui):
                self.data["ui"] = ui
                self.assertEqual(faust2sc.get_parameter_list(self.data, False), "in0")
                self.assertEqual(faust2sc.get_help_file_arguments(self.data), "")

    def test_flat_controls_keep_existing_arguments(self):
        self.data["ui"] = [{"type": "vgroup", "label": "flat", "items": [
            {"type": "hslider", "label": "freq", "init": 440},
            {"type": "button", "label": "gate"},
        ]}]
        self.assertEqual(faust2sc.get_parameter_list(self.data, True), "in0,freq(440), gate(0)")


class DattorroDemoTests(unittest.TestCase):
    fixture_dir = Path(__file__).resolve().parent / "fixtures"
    arguments = ("in0, in1,prefilter, diffusion_1, diffusion_2, diffusion_1_2, "
                 "diffusion_2_2, decay_rate, damping, drywet_mix, level")

    def check_demo(self, data):
        self.assertEqual(faust2sc.get_parameter_list(data, False), self.arguments)
        class_text = faust2sc.get_sc_class(data, 1)
        self.assertIn("^this.multiNew('audio', " + self.arguments + ")", class_text)
        self.assertIn("^this.multiNew('control', " + self.arguments + ")", class_text)
        self.assertEqual(
            [line for line in faust2sc.get_help_file_arguments(data).splitlines()
             if line.startswith("ARGUMENT::")],
            ["ARGUMENT::" + name.strip() for name in self.arguments.split(",")[2:]],
        )

    def test_recorded_demo_json(self):
        self.check_demo(json.loads((self.fixture_dir / "dattorro-reverb.json").read_text()))

    @unittest.skipUnless(shutil.which("faust"), "faust is not on PATH")
    def test_compiled_demo_json(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            dsp_file = Path(temp_dir) / "dattorro-reverb.dsp"
            shutil.copyfile(self.fixture_dir / dsp_file.name, dsp_file)
            subprocess.run(["faust", "-json", "-o", str(Path(temp_dir) / "demo.cpp"),
                            str(dsp_file)], check=True, capture_output=True)
            self.check_demo(json.loads(Path(str(dsp_file) + ".json").read_text()))


if __name__ == "__main__":
    unittest.main()
