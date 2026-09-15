"""Argument and opt-in macOS integration tests for ``faust2max6``.

Argument validation remains part of the portable default suite.  Native bundle
tests are enabled with ``FAUST_RUN_MAX_INTEGRATION=1`` because they require
macOS, the Max SDK, both compiler architectures, and signing tools.
"""

from __future__ import annotations

import json
import os
import plistlib
import platform
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path
from typing import Any, Iterable


# Use the command and architecture files from the source tree under test.
ROOT = Path(__file__).resolve().parents[3]
ARCHITECTURE = ROOT / "architecture"
TOOLS = ROOT / "tools" / "faust2appls"
FAUST2MAX6 = TOOLS / "faust2max6"


def nested_values(value: Any, key: str) -> Iterable[Any]:
    """Yield every occurrence of ``key`` from nested Max patch JSON."""

    if isinstance(value, dict):
        for item_key, item_value in value.items():
            if item_key == key:
                yield item_value
            yield from nested_values(item_value, key)
    elif isinstance(value, list):
        for item in value:
            yield from nested_values(item, key)


def base_environment() -> dict[str, str]:
    """Build the common environment used by argument and integration tests."""

    environment = os.environ.copy()
    environment["FAUSTARCH"] = str(ARCHITECTURE)
    environment["FAUST_ARCH_PATH"] = str(ARCHITECTURE)
    environment["PATH"] = f"{TOOLS}{os.pathsep}{environment['PATH']}"
    return environment


@unittest.skipUnless(os.name == "posix" and shutil.which("faust"), "requires Faust and bash")
class Faust2Max6ArgumentTests(unittest.TestCase):
    """Check inexpensive command-line behavior without compiling an external."""

    def run_script(self, *arguments: object) -> subprocess.CompletedProcess[str]:
        """Run faust2max6 and merge output to make failures self-contained."""

        return subprocess.run(
            [str(FAUST2MAX6), *(str(argument) for argument in arguments)],
            env=base_environment(),
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

    def test_help_succeeds(self):
        """Treat an explicit help request as a successful invocation."""

        result = self.run_script("--help")
        self.assertEqual(result.returncode, 0, result.stdout)

    def test_missing_input_and_invalid_options_fail(self):
        """Reject absent input, bad architectures, and invalid voice counts."""

        for arguments in ((), ("-arch", "invalid"), ("-nvoices",), ("-nvoices", "0")):
            with self.subTest(arguments=arguments):
                result = self.run_script(*arguments)
                self.assertNotEqual(result.returncode, 0, result.stdout)


@unittest.skipUnless(
    os.environ.get("FAUST_RUN_MAX_INTEGRATION") == "1",
    "set FAUST_RUN_MAX_INTEGRATION=1 to compile Max externals",
)
class Faust2Max6IntegrationTests(unittest.TestCase):
    """Compile, sign, and inspect genuine macOS Max external bundles."""

    @classmethod
    def setUpClass(cls):
        """Skip cleanly unless every native build prerequisite is available."""

        if platform.system() != "Darwin":
            raise unittest.SkipTest("faust2max6 integration requires macOS")
        missing = [tool for tool in ("faust", "c++", "lipo", "codesign") if not shutil.which(tool)]
        if missing:
            raise unittest.SkipTest(f"missing tools: {', '.join(missing)}")
        max_sdk = Path(os.environ.get("MAXSDK", "/usr/local/include/c74support"))
        if not (max_sdk / "max-includes" / "ext.h").is_file():
            raise unittest.SkipTest(f"Max SDK not found at {max_sdk}")
        cls.max_sdk = max_sdk

    def setUp(self):
        """Create an isolated source directory whose name contains a space."""

        self.temporary = tempfile.TemporaryDirectory()
        self.directory = Path(self.temporary.name)
        self.source_directory = self.directory / "DSP sources"
        self.source_directory.mkdir()

    def tearDown(self):
        """Remove compiled bundles and generated patches after each scenario."""

        self.temporary.cleanup()

    def environment(self) -> dict[str, str]:
        """Add the detected Max SDK to the common test environment."""

        environment = base_environment()
        environment["MAXSDK"] = str(self.max_sdk)
        return environment

    def write_dsp(self, name: str, nvoices: int | None = None) -> Path:
        """Create a pass-through DSP with optional declared polyphony."""

        declaration = f'declare nvoices "{nvoices}";\n' if nvoices else ""
        path = self.source_directory / f"{name}.dsp"
        path.write_text(f"{declaration}process = _;\n", encoding="utf-8")
        return path

    def run_faust2max6(self, *arguments: object) -> subprocess.CompletedProcess[str]:
        """Run a real external compilation inside the temporary workspace."""

        return subprocess.run(
            [str(FAUST2MAX6), *(str(argument) for argument in arguments)],
            cwd=self.directory,
            env=self.environment(),
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

    def assert_bundle(self, dsp: Path, architectures: set[str]) -> Path:
        """Validate binary slices, signature, resources, and Info.plist metadata."""

        bundle = dsp.with_name(f"{dsp.stem}~.mxo")
        binary = bundle / "Contents" / "MacOS" / f"{dsp.stem}~"
        resources = bundle / "Contents" / "Resources"
        self.assertTrue(binary.is_file(), bundle)
        # lipo is authoritative for the Mach-O slices present in the bundle.
        actual_architectures = set(
            subprocess.check_output(["lipo", "-archs", str(binary)], text=True).split()
        )
        self.assertEqual(actual_architectures, architectures)
        # Verify after all resources have been installed, matching Max's view of
        # the final sealed bundle rather than merely checking the linker output.
        subprocess.run(
            ["codesign", "--verify", "--deep", "--strict", str(bundle)], check=True
        )
        self.assertTrue((resources / dsp.name).is_file())
        self.assertTrue((resources / f"{dsp.stem}-exp.dsp").is_file())
        self.assertTrue((resources / f"{dsp.stem}.cpp").is_file())
        with (bundle / "Contents" / "Info.plist").open("rb") as stream:
            info = plistlib.load(stream)
        self.assertEqual(info["CFBundleExecutable"], f"{dsp.stem}~")
        return bundle

    def patch_texts(self, path: Path) -> list[str]:
        """Collect nested message and object texts from a generated Max patch."""

        data = json.loads(path.read_text(encoding="utf-8"))
        return [value for value in nested_values(data, "text") if isinstance(value, str)]

    def test_architecture_matrix_and_bundle_contents(self):
        """Build thin ARM64, thin Intel, and universal signed externals."""

        for architecture, expected in (
            ("arm64", {"arm64"}),
            ("x86_64", {"x86_64"}),
            ("universal", {"arm64", "x86_64"}),
        ):
            with self.subTest(architecture=architecture):
                dsp = self.write_dsp(f"arch_{architecture}")
                result = self.run_faust2max6("-nopatch", "-arch", architecture, dsp)
                self.assertEqual(result.returncode, 0, result.stdout)
                self.assert_bundle(dsp, expected)
                self.assertFalse((self.directory / f"{dsp.stem}.maxpat").exists())

    def test_requested_and_declared_polyphony_reach_generated_patch(self):
        """Use exact CLI and source-declared voice counts in wrapper messages."""

        explicit = self.write_dsp("explicit_poly")
        declared = self.write_dsp("declared", nvoices=12)

        explicit_result = self.run_faust2max6(
            "-midi", "-nvoices", 6, "-arch", "arm64", explicit
        )
        self.assertEqual(explicit_result.returncode, 0, explicit_result.stdout)
        self.assert_bundle(explicit, {"arm64"})
        self.assertIn(
            "polyphony 6", self.patch_texts(self.directory / "explicit_poly.maxpat")
        )

        declared_result = self.run_faust2max6("-midi", "-arch", "arm64", declared)
        self.assertEqual(declared_result.returncode, 0, declared_result.stdout)
        self.assert_bundle(declared, {"arm64"})
        self.assertIn("polyphony 12", self.patch_texts(self.directory / "declared.maxpat"))

    def test_mc_midi_nopatch(self):
        """Combine MC, MIDI, and polyphony while suppressing wrapper generation."""

        dsp = self.write_dsp("mc_poly")
        result = self.run_faust2max6(
            "-nopatch", "-mc", "-midi", "-nvoices", 4, "-arch", "arm64", dsp
        )
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assert_bundle(dsp, {"arm64"})
        self.assertFalse((self.directory / "mc_poly.maxpat").exists())


if __name__ == "__main__":
    unittest.main()
