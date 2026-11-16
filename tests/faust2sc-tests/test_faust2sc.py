import contextlib
import importlib.util
import io
import os
from pathlib import Path
import shlex
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


class CompileTests(unittest.TestCase):
    def test_cxx_standard_can_be_overridden_by_cxxflags(self):
        with patch.dict(os.environ, {"CXXFLAGS": "-std=c++20"}):
            flags = faust2sc.faustoptflags()["MYGCCFLAGS"].split()
        # The compiler follows the last -std of its command line.
        self.assertEqual([f for f in flags if f.startswith("-std=")], ["-std=c++17", "-std=c++20"])

    def test_include_paths_with_spaces_and_shell_characters(self):
        headers = ["SC headers/plugin_interface", "SC headers/common", "SC headers/server"]
        includedir = "/opt/Faust's headers \n"
        with patch.object(faust2sc.subprocess, "run", return_value=subprocess.CompletedProcess([], 0, includedir.encode())):
            with patch.object(faust2sc, "find_headers", return_value=headers):
                with patch.object(faust2sc.os, "getcwd", return_value="/tmp/My sounds"):
                    flags = faust2sc.includeflags("SC headers")
        self.assertEqual(shlex.split(flags), ["-I" + p for p in headers + [includedir.rstrip("\r\n"), "/tmp/My sounds"]])

    def test_compile_paths_are_preserved_for_both_servers(self):
        cpp_file = "My sounds/oscillator's sound.cpp"
        out_dir = "My plugins/it's here"
        env = {"EXT": "so"}
        with patch.object(faust2sc, "buildflags", return_value="-O3 -shared -fPIC"):
            with patch.object(faust2sc, "faustoptflags", return_value=env):
                with patch.object(faust2sc.path, "exists", return_value=True):
                    with patch.dict(os.environ, {"CXX": "ccache c++"}):
                        with patch.object(faust2sc.os, "system", return_value=0) as system:
                            with contextlib.redirect_stdout(io.StringIO()):
                                faust2sc.compile(out_dir, cpp_file, "FaustSound", True, "", "")
        self.assertEqual(system.call_count, 2)
        for call, name in zip(system.call_args_list, ("FaustSound", "FaustSound_supernova")):
            args = shlex.split(call.args[0])
            self.assertEqual(args[:2], ["ccache", "c++"])
            self.assertEqual(args[-1], cpp_file)
            self.assertEqual(args[args.index("-o") + 1], str(Path(out_dir) / (name + ".so")))
            self.assertIn("-Dmydsp=" + name, args)
        self.assertIn("-DSUPERNOVA", shlex.split(system.call_args_list[1].args[0]))


class CompileFailureTests(unittest.TestCase):
    def test_compiler_failure_stops_export(self):
        for statuses, server, calls in (([256, 0], "scsynth", 1), ([0, 256], "supernova", 2)):
            with self.subTest(server=server):
                with (
                    patch.object(faust2sc, "buildflags", return_value="-shared"),
                    patch.object(faust2sc, "faustoptflags", return_value={"EXT": "so"}),
                    patch.object(faust2sc.path, "exists", return_value=True),
                    patch.dict(os.environ, {"CXX": "c++"}),
                    patch.object(faust2sc.os, "system", side_effect=statuses) as system,
                    contextlib.redirect_stdout(io.StringIO()),
                    self.assertRaisesRegex(SystemExit, "compilation failed for " + server),
                ):
                    faust2sc.compile("output", "sound.cpp", "Sound", True, "", "")
                self.assertEqual(system.call_count, calls)


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

