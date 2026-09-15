"""Portable generation tests for ``faust2rnbo``.

The real Faust Codebox backend and bundled py2max module are used to generate
patches in temporary directories.  The resulting JSON is inspected directly;
Max and the RNBO runtime are never launched.
"""

from __future__ import annotations

import json
import os
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path
from typing import Any, Iterable


# Always exercise the scripts and architecture files from this checkout.
ROOT = Path(__file__).resolve().parents[3]
ARCHITECTURE = ROOT / "architecture"
TOOLS = ROOT / "tools" / "faust2appls"
FAUST2RNBO = TOOLS / "faust2rnbo"


def nested_values(value: Any, key: str) -> Iterable[Any]:
    """Yield all values stored under ``key`` in an arbitrarily nested patch."""

    if isinstance(value, dict):
        for item_key, item_value in value.items():
            if item_key == key:
                yield item_value
            yield from nested_values(item_value, key)
    elif isinstance(value, list):
        for item in value:
            yield from nested_values(item, key)


def base_environment() -> dict[str, str]:
    """Select this checkout for Faust architecture and helper script lookup."""

    environment = os.environ.copy()
    environment["FAUSTARCH"] = str(ARCHITECTURE)
    environment["FAUST_ARCH_PATH"] = str(ARCHITECTURE)
    environment["PATH"] = f"{TOOLS}{os.pathsep}{environment['PATH']}"
    return environment


@unittest.skipUnless(os.name == "posix" and shutil.which("faust"), "requires Faust and bash")
class Faust2RnboTests(unittest.TestCase):
    """Validate RNBO generation modes and command-line error handling."""

    def setUp(self):
        """Create an isolated source tree whose name exercises space handling."""

        self.temporary = tempfile.TemporaryDirectory()
        self.directory = Path(self.temporary.name)
        self.source_directory = self.directory / "DSP sources"
        self.source_directory.mkdir()

    def tearDown(self):
        """Remove patches and sources produced by the current test."""

        self.temporary.cleanup()

    def write_dsp(self, name: str, source: str | None = None) -> Path:
        """Write ``source`` or a default oscillator with one exposed control."""

        path = self.source_directory / f"{name}.dsp"
        path.write_text(
            source
            or 'import("stdfaust.lib");\n'
            'process = hslider("gain", 0.5, 0, 1, 0.01) * os.osc(440);\n',
            encoding="utf-8",
        )
        return path

    def run_script(self, *arguments: object) -> subprocess.CompletedProcess[str]:
        """Run faust2rnbo and retain its merged output for assertion messages."""

        return subprocess.run(
            [str(FAUST2RNBO), *(str(argument) for argument in arguments)],
            cwd=self.directory,
            env=base_environment(),
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

    def load_patch(self, path: Path) -> dict[str, Any]:
        """Parse a generated maxpat or rnbopat file."""

        return json.loads(path.read_text(encoding="utf-8"))

    def texts(self, patch: dict[str, Any]) -> list[str]:
        """Collect all nested Max box texts from a patch."""

        return [value for value in nested_values(patch, "text") if isinstance(value, str)]

    def assert_no_compiler_temporaries(self, dsp: Path):
        """Check that successful generation removes Codebox and JSON intermediates."""

        self.assertFalse(dsp.with_suffix(".codebox").exists())
        self.assertFalse(Path(f"{dsp}.json").exists())

    def test_help_and_invalid_arguments(self):
        """Return zero for help and non-zero for incomplete or invalid commands."""

        help_result = self.run_script("--help")
        self.assertEqual(help_result.returncode, 0, help_result.stdout)

        for arguments in (
            (),
            ("-nvoices",),
            ("-nvoices", "0"),
            ("-effect",),
            ("missing.dsp",),
        ):
            with self.subTest(arguments=arguments):
                result = self.run_script(*arguments)
                self.assertNotEqual(result.returncode, 0, result.stdout)

    def test_flat_mono_patch_embeds_codebox(self):
        """Embed a monophonic Codebox subpatch and avoid an external rnbopat."""

        dsp = self.write_dsp("mono tone")
        result = self.run_script(dsp)
        self.assertEqual(result.returncode, 0, result.stdout)

        patch_path = dsp.with_suffix(".maxpat")
        patch = self.load_patch(patch_path)
        self.assertIn("rnbo~", self.texts(patch))
        self.assertIn("codebox~", list(nested_values(patch, "maxclass")))
        self.assertTrue(any("set gain" in text for text in self.texts(patch)))
        self.assertFalse(dsp.with_suffix(".rnbopat").exists())
        self.assert_no_compiler_temporaries(dsp)

    def test_cli_polyphony_and_subpatcher(self):
        """Propagate CLI voice count and MIDI routing to a file subpatcher."""

        dsp = self.write_dsp("poly tone")
        result = self.run_script("-midi", "-nvoices", 4, "-sp", dsp)
        self.assertEqual(result.returncode, 0, result.stdout)

        patch = self.load_patch(dsp.with_suffix(".maxpat"))
        texts = self.texts(patch)
        self.assertTrue(any("@polyphony 4" in text for text in texts))
        self.assertIn("midiin", texts)
        self.assertIn("midiout", texts)

        subpatcher = dsp.with_suffix(".rnbopat")
        self.assertTrue(subpatcher.is_file())
        subpatch = self.load_patch(subpatcher)
        self.assertIn("codebox~", list(nested_values(subpatch, "maxclass")))
        self.assert_no_compiler_temporaries(dsp)

    def test_metadata_enables_midi_polyphony(self):
        """Infer MIDI and voice count from Faust's global options metadata."""

        dsp = self.write_dsp(
            "declared poly",
            'declare options "[midi:on][nvoices:5]";\nprocess = _;\n',
        )
        result = self.run_script(dsp)
        self.assertEqual(result.returncode, 0, result.stdout)

        patch = self.load_patch(dsp.with_suffix(".maxpat"))
        texts = self.texts(patch)
        self.assertIn(5, list(nested_values(patch, "polyphony")))
        self.assertIn("midiin", texts)
        self.assertIn("midiout", texts)

    def test_codebox_test_mode_uses_prefixed_parameters(self):
        """Generate the RB_ parameter ABI expected by the RNBO C++ test app."""

        dsp = self.write_dsp("test labels", 'process = hslider("gain", 0.5, 0, 1, 0.01);\n')
        result = self.run_script("-test", dsp)
        self.assertEqual(result.returncode, 0, result.stdout)

        patch = self.load_patch(dsp.with_suffix(".maxpat"))
        self.assertIn("set RB_hslider_gain", self.texts(patch))
        code = "\n".join(
            value for value in nested_values(patch, "code") if isinstance(value, str)
        )
        self.assertIn("RB_hslider_gain", code)
        self.assert_no_compiler_temporaries(dsp)

    def test_explicit_and_automatic_effects(self):
        """Generate both effect modes and preserve the requested C++ export data."""

        # An explicit effect is compiled from its own DSP and connected after
        # the main processor in a second RNBO subpatcher.
        effect = self.write_dsp("effect unit", "process = _;\n")
        explicit = self.write_dsp("explicit effect")
        export_path = self.directory / "C++ export"
        result = self.run_script(
            "-effect",
            effect,
            "-compile",
            "-cpp_path",
            export_path,
            "-cpp_filename",
            "rendered.cpp",
            explicit,
        )
        self.assertEqual(result.returncode, 0, result.stdout)
        texts = self.texts(self.load_patch(explicit.with_suffix(".maxpat")))
        self.assertTrue(any("_effect.rnbopat" in text for text in texts))
        self.assertIn("dumptargetconfig cpp-export cpp-code-export", texts)
        self.assertIn(
            f"set output_path {export_path}, set export_name rendered.cpp", texts
        )
        self.assert_no_compiler_temporaries(explicit)
        self.assert_no_compiler_temporaries(effect)

        # In automatic mode the script extracts the source's ``effect``
        # definition through a temporary adaptor DSP.
        automatic = self.write_dsp(
            "automatic effect",
            'import("stdfaust.lib");\nprocess = os.osc(440);\neffect = _;\n',
        )
        result = self.run_script("-effect", "auto", automatic)
        self.assertEqual(result.returncode, 0, result.stdout)
        texts = self.texts(self.load_patch(automatic.with_suffix(".maxpat")))
        self.assertTrue(any("_effect.rnbopat" in text for text in texts))
        self.assert_no_compiler_temporaries(automatic)


if __name__ == "__main__":
    unittest.main()
