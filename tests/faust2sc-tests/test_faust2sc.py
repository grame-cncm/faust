import contextlib
import importlib.util
import io
from pathlib import Path
import subprocess
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


class GetScClassTests(unittest.TestCase):
    def test_zero_inputs_and_controls_omits_trailing_comma(self):
        json_data = {
            "name": "noise_gen",
            "inputs": 0,
            "outputs": 1,
            "meta": [],
            "ui": []
        }
        sc_class = faust2sc.get_sc_class(json_data, noprefix=1)
        self.assertNotIn("multiNew('audio', )", sc_class)
        self.assertNotIn("multiNew('control', )", sc_class)
        self.assertNotIn("*ar{||", sc_class)
        self.assertNotIn("*kr{||", sc_class)
        self.assertIn("*ar{\n      ^this.multiNew('audio')\n    }", sc_class)
        self.assertIn("*kr{\n      ^this.multiNew('control')\n    }", sc_class)


if __name__ == "__main__":
    unittest.main()

