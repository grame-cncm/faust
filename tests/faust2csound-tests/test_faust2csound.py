"""Compile and render generated opcodes with the selected Csound SDK."""

import os
from pathlib import Path
import shlex
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]


class CsoundArchitectureTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.faust = shutil.which(os.environ.get("FAUST", "faust"))
        cls.csound = shutil.which(os.environ.get("CSOUND", "csound"))
        include = os.environ.get("CSOUND_INCLUDE_DIR")
        if not cls.faust or not cls.csound or not include:
            raise RuntimeError("Set FAUST, CSOUND, and CSOUND_INCLUDE_DIR for the SDK under test")
        cls.faust = str(Path(cls.faust).resolve())
        cls.csound = str(Path(cls.csound).resolve())

        cls.temp = tempfile.TemporaryDirectory(prefix="faust-csound-")
        cls.addClassCleanup(cls.temp.cleanup)
        cls.directory = Path(cls.temp.name)
        tool_directory = cls.directory / "bin"
        tool_directory.mkdir()
        (tool_directory / "faust").symlink_to(cls.faust)
        include_directory = cls.directory / "include"
        include_directory.symlink_to(Path(include).resolve(), target_is_directory=True)
        cls.env = os.environ.copy()
        cls.env["PATH"] = os.pathsep.join([
            str(tool_directory),
            str(ROOT / "tools/faust2appls"),
            cls.env.get("PATH", ""),
        ])
        cls.env["FAUSTARCH"] = str(ROOT / "architecture")
        cls.env["CXXFLAGS"] = " ".join([
            cls.env.get("CXXFLAGS", ""), "-std=c++11", "-I" + str(include_directory),
        ])
        # These flags follow faust2csound's default optimization flags.
        cls.env["FAUSTTOOLSFLAGS"] = "-fno-fast-math -ffp-contract=off"
        # Load only the test opcodes, regardless of the user's installed plugins.
        for name in ("OPCODE6DIR64", "OPCODE7DIR64", "CS_USER_PLUGINDIR"):
            cls.env[name] = ""

        sources = {
            "faustgain": 'process = _ * hslider("gain", 0.5, 0, 1, 0.01);',
            "faustcounter": "process = (+(1) ~ _) / 1024.0;",
            "faustrate": 'import("stdfaust.lib"); process = ma.SR / 48000.0;',
        }
        cls.plugins = {}
        for name, source in sources.items():
            dsp = cls.directory / (name + ".dsp")
            dsp.write_text(source + "\n")
            cls.run_command([
                "bash", str(ROOT / "tools/faust2appls/faust2csound"), str(dsp),
            ])
            extension = ".dylib" if sys.platform == "darwin" else ".so"
            cls.plugins[name] = cls.directory / (name + extension)
            if not cls.plugins[name].is_file():
                raise AssertionError("faust2csound did not create " + str(cls.plugins[name]))

    @classmethod
    def run_command(cls, command):
        result = subprocess.run(command, cwd=cls.directory, env=cls.env,
                                text=True, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, timeout=60)
        if result.returncode:
            raise AssertionError("Command failed: " + shlex.join(command) + "\n" + result.stdout)
        return result.stdout

    def render(self, plugin, body, expected):
        csd = self.directory / (self._testMethodName + ".csd")
        audio = self.directory / (self._testMethodName + ".raw")
        csd.write_text("""<CsoundSynthesizer>
<CsInstruments>
sr = 48000
ksmps = 64
nchnls = 1
0dbfs = 1
instr 1
""" + body + """
out asignal
endin
</CsInstruments>
<CsScore>
i 1 0 [512 / 48000]
e
</CsScore>
</CsoundSynthesizer>
""")
        self.run_command([
            self.csound, "--opcode-lib=" + str(self.plugins[plugin]),
            "-d", "-m0", "-f", "-h", "-o", str(audio), str(csd),
        ])
        samples = [value for (value,) in struct.iter_unpack("=f", audio.read_bytes())]
        self.assertEqual(len(samples), 512)
        expected_samples = expected if isinstance(expected, list) else [expected] * 512
        for sample, reference in zip(samples, expected_samples):
            self.assertAlmostEqual(sample, reference, places=6)

    def test_audio_input_and_control(self):
        self.render("faustgain", "ain init 0.5\nasignal faustgain ain, 0.25", 0.125)

    def test_local_block_size(self):
        self.render("faustcounter", "setksmps 16\nasignal faustcounter",
                    [(i + 1) / 1024.0 for i in range(512)])

    def test_sample_rate_and_no_inputs(self):
        self.render("faustrate", "asignal faustrate", 1.0)


if __name__ == "__main__":
    unittest.main()
