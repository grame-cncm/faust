"""Opt-in end-to-end Max runtime test for dynamic Faust polyphony.

The harness is generated with the bundled py2max package.  The test compiles
an ARM64 ``faust2max6`` external, launches Max, sends MIDI messages directly
to the external, and checks that audio remains non-zero after ``polyphony 24``.
It is excluded from the default suite because it opens a GUI application and
temporarily starts the Max audio engine.
"""

from __future__ import annotations

import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
import time
import unittest
from pathlib import Path
from typing import Any, Iterable


ROOT = Path(__file__).resolve().parents[3]
MAX_MSP = ROOT / "architecture" / "max-msp"
TOOLS = ROOT / "tools" / "faust2appls"
FAUST2MAX6 = TOOLS / "faust2max6"
CONTROLLER = Path(__file__).with_name("max_polyphony_runtime.js")
BARGRAPH_CONTROLLER = Path(__file__).with_name("max_bargraph_runtime.js")
DEFAULT_MAX = Path("/Applications/Max.app/Contents/MacOS/Max")

# Import the in-tree package under test, independently of any globally
# installed py2max version.
sys.path.insert(0, str(MAX_MSP / "py2max"))
from py2max import Patcher  # noqa: E402


def nested_values(value: Any, key: str) -> Iterable[Any]:
    """Yield every occurrence of a key in generated Max patch JSON."""

    if isinstance(value, dict):
        for item_key, item_value in value.items():
            if item_key == key:
                yield item_value
            yield from nested_values(item_value, key)
    elif isinstance(value, list):
        for item in value:
            yield from nested_values(item, key)


def build_harness(path: Path, external_name: str, result_path: Path) -> None:
    """Generate the self-driving runtime patch with py2max."""

    patcher = Patcher(path)
    external = patcher.add_textbox(
        f"{external_name}~",
        numinlets=1,
        numoutlets=3,
        outlettype=["signal", "", ""],
    )
    snapshot = patcher.add_textbox("snapshot~")
    mute = patcher.add_textbox("*~ 0.")
    audio = patcher.add_textbox("ezdac~")
    controller = patcher.add_textbox(
        f"js {CONTROLLER.name} {result_path}",
        numinlets=1,
        numoutlets=4,
        outlettype=["", "bang", "int", ""],
    )
    thispatcher = patcher.add_textbox("thispatcher")

    patcher.add_line(controller, external, outlet=0, inlet=0)
    patcher.add_line(controller, snapshot, outlet=1, inlet=0)
    patcher.add_line(controller, audio, outlet=2, inlet=0)
    patcher.add_line(controller, thispatcher, outlet=3, inlet=0)
    patcher.add_line(external, snapshot, outlet=0, inlet=0)
    # Keep the signal graph active but never send the DC measurement signal to
    # physical outputs.  snapshot~ observes the unmuted branch above.
    patcher.add_line(external, mute, outlet=0, inlet=0)
    patcher.add_line(mute, audio, outlet=0, inlet=0)
    patcher.add_line(mute, audio, outlet=0, inlet=1)
    patcher.add_line(snapshot, controller, outlet=0, inlet=0)
    patcher.save()


def build_bargraph_harness(path: Path, external_name: str, result_path: Path) -> None:
    """Generate a patch that observes a polyphonic external's bargraph output."""

    patcher = Patcher(path)
    external = patcher.add_textbox(
        f"{external_name}~",
        numinlets=1,
        numoutlets=3,
        outlettype=["signal", "", ""],
    )
    mute = patcher.add_textbox("*~ 0.")
    audio = patcher.add_textbox("ezdac~")
    controller = patcher.add_textbox(
        f"js {BARGRAPH_CONTROLLER.name} {result_path}",
        numinlets=1,
        numoutlets=3,
        outlettype=["", "bang", ""],
    )
    thispatcher = patcher.add_textbox("thispatcher")

    patcher.add_line(controller, external, outlet=0, inlet=0)
    patcher.add_line(controller, audio, outlet=1, inlet=0)
    patcher.add_line(controller, thispatcher, outlet=2, inlet=0)
    patcher.add_line(external, controller, outlet=1, inlet=0)
    patcher.add_line(external, mute, outlet=0, inlet=0)
    patcher.add_line(mute, audio, outlet=0, inlet=0)
    patcher.add_line(mute, audio, outlet=0, inlet=1)
    patcher.save()


def compilation_environment() -> dict[str, str]:
    """Return an environment that selects the source-tree architectures."""

    environment = os.environ.copy()
    architecture = ROOT / "architecture"
    environment["FAUSTARCH"] = str(architecture)
    environment["FAUST_ARCH_PATH"] = str(architecture)
    environment["PATH"] = f"{ROOT / 'build' / 'bin'}{os.pathsep}{TOOLS}{os.pathsep}{environment['PATH']}"
    environment["MAXSDK"] = os.environ.get("MAXSDK", "/usr/local/include/c74support")
    return environment


class MaxRuntimeHarnessTests(unittest.TestCase):
    """Keep py2max harness generation covered by the portable suite."""

    def test_py2max_harness_contains_controller_audio_and_feedback(self):
        """Generate a valid patch containing all runtime-test components."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            patch = directory / "runtime.maxpat"
            result = directory / "runtime-result.json"
            build_harness(patch, "runtime_poly", result)

            data = json.loads(patch.read_text(encoding="utf-8"))
            texts = set(nested_values(data, "text"))
            self.assertIn("runtime_poly~", texts)
            self.assertIn("snapshot~", texts)
            self.assertIn("*~ 0.", texts)
            self.assertIn("ezdac~", texts)
            self.assertIn("thispatcher", texts)
            self.assertIn(f"js {CONTROLLER.name} {result}", texts)
            lines = list(nested_values(data, "patchline"))
            self.assertEqual(len(lines), 9)

    def test_py2max_bargraph_harness_observes_control_outlet(self):
        """Connect the external's control outlet to the bargraph observer."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            patch = directory / "bargraph-runtime.maxpat"
            result = directory / "bargraph-runtime-result.json"
            build_bargraph_harness(patch, "runtime_bargraph", result)

            data = json.loads(patch.read_text(encoding="utf-8"))
            texts = set(nested_values(data, "text"))
            self.assertIn("runtime_bargraph~", texts)
            self.assertIn(f"js {BARGRAPH_CONTROLLER.name} {result}", texts)
            self.assertIn("ezdac~", texts)


@unittest.skipUnless(
    os.environ.get("FAUST_RUN_MAX_RUNTIME") == "1",
    "set FAUST_RUN_MAX_RUNTIME=1 to launch Max",
)
class MaxRuntimePolyphonyTests(unittest.TestCase):
    """Exercise an actual compiled external inside the Max audio runtime."""

    @classmethod
    def setUpClass(cls):
        """Verify native compiler, SDK, controller, and Max prerequisites."""

        if platform.system() != "Darwin":
            raise unittest.SkipTest("Max runtime integration requires macOS")
        missing = [tool for tool in ("faust", "c++", "codesign") if not shutil.which(tool)]
        if missing:
            raise unittest.SkipTest(f"missing tools: {', '.join(missing)}")
        max_sdk = Path(os.environ.get("MAXSDK", "/usr/local/include/c74support"))
        if not (max_sdk / "max-includes" / "ext.h").is_file():
            raise unittest.SkipTest(f"Max SDK not found at {max_sdk}")
        if not CONTROLLER.is_file():
            raise unittest.SkipTest(f"Max controller not found at {CONTROLLER}")
        cls.max_binary = Path(os.environ.get("MAX_APPLICATION", DEFAULT_MAX))
        if not cls.max_binary.is_file():
            raise unittest.SkipTest(f"Max executable not found at {cls.max_binary}")

    def test_audio_survives_polyphony_reconfiguration(self):
        """Keep producing audio after replacing 8 voices with 24 voices."""

        with tempfile.TemporaryDirectory(prefix="faust-max-runtime-") as temporary:
            directory = Path(temporary)
            dsp = directory / "runtime_poly.dsp"
            patch = directory / "runtime_poly_test.maxpat"
            result_path = directory / "runtime-result.json"
            log_path = directory / "max-runtime.log"

            # The conventional freq/gain/gate controls make this a polyphonic
            # MIDI DSP.  A gated DC value is deliberate: snapshot~ can measure
            # it deterministically without depending on oscillator phase.
            dsp.write_text(
                'declare options "[midi:on][nvoices:8]";\n'
                'freq = hslider("freq", 440, 20, 20000, 1);\n'
                'gain = hslider("gain", 0, 0, 1, 0.01);\n'
                'gate = button("gate");\n'
                "process = gain * gate;\n",
                encoding="utf-8",
            )
            compile_result = subprocess.run(
                [
                    str(FAUST2MAX6),
                    "-nopatch",
                    "-midi",
                    "-nvoices",
                    "8",
                    "-arch",
                    "arm64",
                    str(dsp),
                ],
                cwd=directory,
                env=compilation_environment(),
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=180,
            )
            self.assertEqual(compile_result.returncode, 0, compile_result.stdout)
            self.assertTrue((directory / "runtime_poly~.mxo").is_dir())

            shutil.copy2(CONTROLLER, directory / CONTROLLER.name)
            build_harness(patch, "runtime_poly", result_path)

            process: subprocess.Popen[str] | None = None
            with log_path.open("w", encoding="utf-8") as log:
                try:
                    process = subprocess.Popen(
                        [str(self.max_binary), str(patch)],
                        cwd=directory,
                        text=True,
                        stdout=log,
                        stderr=subprocess.STDOUT,
                    )
                    deadline = time.monotonic() + 30
                    while time.monotonic() < deadline and not result_path.is_file():
                        time.sleep(0.1)
                finally:
                    if process is not None and process.poll() is None:
                        process.terminate()
                        try:
                            process.wait(timeout=5)
                        except subprocess.TimeoutExpired:
                            process.kill()
                            process.wait(timeout=5)

            log_text = log_path.read_text(encoding="utf-8", errors="replace")
            self.assertTrue(
                result_path.is_file(),
                f"Max did not produce a result within 30 seconds.\n{log_text}",
            )
            result = json.loads(result_path.read_text(encoding="utf-8"))
            self.assertTrue(result["passed"], f"{result}\n{log_text}")
            self.assertEqual(result["polyphony"], 24)
            self.assertGreater(result["before"], 0.01)
            self.assertGreater(result["after_polyphony"], 0.01)

    def test_polyphonic_midi_bargraph_reports_its_current_value(self):
        """A MIDI-triggered voice must expose a live bargraph, not its reset value."""

        with tempfile.TemporaryDirectory(prefix="faust-max-bargraph-") as temporary:
            directory = Path(temporary)
            dsp = directory / "runtime_bargraph.dsp"
            patch = directory / "runtime_bargraph_test.maxpat"
            result_path = directory / "bargraph-runtime-result.json"
            log_path = directory / "max-bargraph-runtime.log"
            dsp.write_text(
                'declare options "[midi:on][nvoices:8]";\n'
                'freq = hslider("freq", 440, 20, 22500, 1);\n'
                'gain = hslider("gain", 1, 0, 1, 0.01);\n'
                'gate = button("gate");\n'
                'signal = freq * gain * gate;\n'
                'process = attach(signal, signal : vbargraph("param", 20, 22500));\n',
                encoding="utf-8",
            )
            compile_result = subprocess.run(
                [
                    str(FAUST2MAX6),
                    "-nopatch",
                    "-midi",
                    "-nvoices",
                    "8",
                    "-arch",
                    "arm64",
                    str(dsp),
                ],
                cwd=directory,
                env=compilation_environment(),
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=180,
            )
            self.assertEqual(compile_result.returncode, 0, compile_result.stdout)
            self.assertTrue((directory / "runtime_bargraph~.mxo").is_dir())

            shutil.copy2(BARGRAPH_CONTROLLER, directory / BARGRAPH_CONTROLLER.name)
            build_bargraph_harness(patch, "runtime_bargraph", result_path)

            process: subprocess.Popen[str] | None = None
            with log_path.open("w", encoding="utf-8") as log:
                try:
                    process = subprocess.Popen(
                        [str(self.max_binary), str(patch)],
                        cwd=directory,
                        text=True,
                        stdout=log,
                        stderr=subprocess.STDOUT,
                    )
                    deadline = time.monotonic() + 30
                    while time.monotonic() < deadline and not result_path.is_file():
                        time.sleep(0.1)
                finally:
                    if process is not None and process.poll() is None:
                        process.terminate()
                        try:
                            process.wait(timeout=5)
                        except subprocess.TimeoutExpired:
                            process.kill()
                            process.wait(timeout=5)

            log_text = log_path.read_text(encoding="utf-8", errors="replace")
            self.assertTrue(
                result_path.is_file(),
                f"Max did not produce a bargraph result within 30 seconds.\n{log_text}",
            )
            result = json.loads(result_path.read_text(encoding="utf-8"))
            self.assertTrue(result["passed"], f"{result}\n{log_text}")
            self.assertGreater(result["current"], 20.0)


if __name__ == "__main__":
    unittest.main()
