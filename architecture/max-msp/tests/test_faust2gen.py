"""Functional tests for the ``faust2gen`` patch generator.

These portable tests invoke the real shell command and validate the generated
JSON patches.  They do not require Max or compile a native external.
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


# Resolve every executable and template from the checkout so the tests never
# depend on a separately installed Faust tree.
ROOT = Path(__file__).resolve().parents[3]
ARCHITECTURE = ROOT / "architecture"
MAX_MSP = ARCHITECTURE / "max-msp"
TOOLS = ROOT / "tools" / "faust2appls"
FAUST2GEN = TOOLS / "faust2gen"


def nested_values(value: Any, key: str) -> Iterable[Any]:
    """Yield every value stored under ``key`` in a JSON-compatible tree."""

    if isinstance(value, dict):
        for item_key, item_value in value.items():
            if item_key == key:
                yield item_value
            yield from nested_values(item_value, key)
    elif isinstance(value, list):
        for item in value:
            yield from nested_values(item, key)


@unittest.skipUnless(os.name == "posix" and shutil.which("faust"), "requires Faust and bash")
class Faust2GenTests(unittest.TestCase):
    """Validate template choice, substitution, metadata, paths, and diagnostics."""

    def environment(self) -> dict[str, str]:
        """Return an environment that selects this checkout's architecture files."""

        environment = os.environ.copy()
        environment["FAUSTARCH"] = str(ARCHITECTURE)
        environment["FAUST_ARCH_PATH"] = str(ARCHITECTURE)
        environment["PATH"] = f"{TOOLS}{os.pathsep}{environment['PATH']}"
        return environment

    def run_faust2gen(self, directory: Path, *arguments: object) -> subprocess.CompletedProcess[str]:
        """Run faust2gen in ``directory`` and combine output for useful failures."""

        return subprocess.run(
            [str(FAUST2GEN), *(str(argument) for argument in arguments)],
            cwd=directory,
            env=self.environment(),
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

    @staticmethod
    def write_dsp(path: Path, nvoices: int | None = None) -> None:
        """Create a pass-through DSP with optional polyphony metadata."""

        declaration = f'declare nvoices "{nvoices}";\n' if nvoices else ""
        path.write_text(f"{declaration}process = _;\n", encoding="utf-8")

    @staticmethod
    def load_patch(path: Path) -> tuple[dict[str, Any], str, list[str], list[str]]:
        """Load a patch and collect nested box texts and Max class names."""

        raw = path.read_text(encoding="utf-8")
        data = json.loads(raw)
        texts = [value for value in nested_values(data, "text") if isinstance(value, str)]
        classes = [
            value for value in nested_values(data, "maxclass") if isinstance(value, str)
        ]
        return data, raw, texts, classes

    def test_mono_polyphonic_and_mc_template_matrix(self):
        """Cover all mono/polyphonic and faustgen~/mc.faustgen~ combinations."""

        for mc in (False, True):
            for voices in (None, 6):
                with self.subTest(mc=mc, voices=voices), tempfile.TemporaryDirectory() as temporary:
                    directory = Path(temporary)
                    dsp = directory / "voice.dsp"
                    self.write_dsp(dsp)
                    arguments: list[object] = []
                    if mc:
                        arguments.append("-mc")
                    if voices:
                        arguments.extend(("-nvoices", voices))
                    arguments.append(dsp)

                    result = self.run_faust2gen(directory, *arguments)
                    self.assertEqual(result.returncode, 0, result.stdout)
                    _, raw, texts, classes = self.load_patch(directory / "voice.maxpat")

                    # Every marker from the source template must be resolved.
                    self.assertNotIn("DSP_NAME", raw)
                    self.assertNotIn("UI_FILE", raw)
                    self.assertNotIn("NVOICES", raw)
                    self.assertIn("read voice.dsp", texts)
                    self.assertIn("mc.faustgen~" if mc else "faustgen~", texts)
                    self.assertIn("mc.ezdac~" if mc else "ezdac~", classes)
                    # A mono patch must not accidentally retain the polyphony
                    # message, while a poly patch must contain the exact count.
                    if voices:
                        self.assertIn(f"polyphony {voices}", texts)
                    else:
                        self.assertFalse(any(text.startswith("polyphony ") for text in texts))
                    self.assertEqual(
                        (directory / "ui.js").read_bytes(), (MAX_MSP / "ui.js").read_bytes()
                    )

    def test_declared_voice_counts_are_applied_per_file(self):
        """Read nvoices independently when several DSP files share one command."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            first = directory / "first.dsp"
            second = directory / "second.dsp"
            self.write_dsp(first, nvoices=12)
            self.write_dsp(second, nvoices=5)

            result = self.run_faust2gen(directory, first, second)
            self.assertEqual(result.returncode, 0, result.stdout)
            for stem, voices in (("first", 12), ("second", 5)):
                _, raw, texts, _ = self.load_patch(directory / f"{stem}.maxpat")
                self.assertNotIn("NVOICES", raw)
                self.assertIn(f"polyphony {voices}", texts)

    def test_cli_voice_count_overrides_declared_metadata(self):
        """Prefer an explicit command-line count over declare nvoices."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            dsp = directory / "override.dsp"
            self.write_dsp(dsp, nvoices=12)

            result = self.run_faust2gen(directory, "-nvoices", 6, dsp)
            self.assertEqual(result.returncode, 0, result.stdout)
            _, _, texts, _ = self.load_patch(directory / "override.maxpat")
            self.assertIn("polyphony 6", texts)
            self.assertNotIn("polyphony 12", texts)

    def test_mixed_mono_and_declared_poly_files_are_independent(self):
        """Do not make every input polyphonic when only one declares nvoices."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            mono = directory / "mono.dsp"
            poly = directory / "poly.dsp"
            self.write_dsp(mono)
            self.write_dsp(poly, nvoices=5)

            result = self.run_faust2gen(directory, mono, poly)
            self.assertEqual(result.returncode, 0, result.stdout)
            _, _, mono_texts, _ = self.load_patch(directory / "mono.maxpat")
            _, _, poly_texts, _ = self.load_patch(directory / "poly.maxpat")
            self.assertFalse(any(text.startswith("polyphony ") for text in mono_texts))
            self.assertIn("polyphony 5", poly_texts)

    def test_input_directory_may_contain_spaces(self):
        """Accept an input path containing spaces without splitting the filename."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            source_directory = directory / "DSP sources"
            source_directory.mkdir()
            dsp = source_directory / "spaced.dsp"
            self.write_dsp(dsp)

            result = self.run_faust2gen(directory, dsp)
            self.assertEqual(result.returncode, 0, result.stdout)
            _, _, texts, _ = self.load_patch(directory / "spaced.maxpat")
            self.assertIn("read spaced.dsp", texts)

    def test_help_and_invalid_inputs(self):
        """Keep help successful and malformed invocations non-zero."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            dsp = directory / "voice.dsp"
            self.write_dsp(dsp)

            help_result = self.run_faust2gen(directory, "--help")
            self.assertEqual(help_result.returncode, 0, help_result.stdout)
            for arguments in (
                (),
                (directory / "missing.dsp",),
                ("-nvoices",),
                ("-nvoices", "invalid", dsp),
                ("-nvoices", "0", dsp),
            ):
                with self.subTest(arguments=arguments):
                    result = self.run_faust2gen(directory, *arguments)
                    self.assertNotEqual(result.returncode, 0, result.stdout)


if __name__ == "__main__":
    unittest.main()
