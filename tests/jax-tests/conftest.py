"""
Pytest configuration and shared fixtures for Faust JAX backend tests.
"""

import os

# The suite always runs on CPU (matches the CI jobs' JAX_PLATFORMS=cpu).
os.environ.setdefault("JAX_PLATFORMS", "cpu")

import pytest
import subprocess
import sys
from pathlib import Path
import tempfile
import shutil

from test_utils import load_module

import jax
import jax.numpy as jnp
from flax import nnx


# Test configuration constants
FAUST_COMPILER = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
JAX_ARCH_DIR = Path(__file__).parent.parent.parent / "architecture" / "jax"
JAX_LIB_DIR = Path(__file__).parent.parent.parent / "libraries"
DSP_DIR = Path(__file__).parent / "dsp"
GENERATED_DIR = Path(__file__).parent / "generated"


@pytest.fixture(scope="session")
def faust_compiler():
	"""Path to the Faust compiler executable."""
	if not FAUST_COMPILER.exists():
		pytest.skip(f"Faust compiler not found at {FAUST_COMPILER}")
	return FAUST_COMPILER


@pytest.fixture(scope="session")
def jax_architecture_dir():
	"""Path to JAX architecture directory."""
	if not JAX_ARCH_DIR.exists():
		pytest.skip(f"JAX architecture directory not found at {JAX_ARCH_DIR}")
	return JAX_ARCH_DIR


@pytest.fixture(scope="session")
def jax_library_dir():
	"""Path to Faust libraries directory."""
	if not JAX_LIB_DIR.exists():
		pytest.skip(f"Faust libraries directory not found at {JAX_LIB_DIR}")
	return JAX_LIB_DIR


@pytest.fixture
def temp_output_dir():
	"""Create a temporary directory for test outputs."""
	temp_dir = tempfile.mkdtemp(prefix="faust_jax_test_")
	yield Path(temp_dir)
	shutil.rmtree(temp_dir, ignore_errors=True)


@pytest.fixture
def compile_faust_dsp(faust_compiler, jax_architecture_dir, jax_library_dir, temp_output_dir):
	"""
	Fixture that returns a function to compile Faust DSP files to JAX.

	Usage:
		compile_func = compile_faust_dsp
		output_file = compile_func("simple_gain.dsp")
	"""
	def _compile(dsp_filename: str, extra_args: list = None) -> Path:
		"""
		Compile a Faust DSP file to JAX/Python.

		Args:
			dsp_filename: Name of the DSP file (with .dsp extension)
			extra_args: Additional compiler arguments

		Returns:
			Path to the generated Python file

		Raises:
			subprocess.CalledProcessError: If compilation fails
		"""
		dsp_file = DSP_DIR / dsp_filename
		if not dsp_file.exists():
			raise FileNotFoundError(f"DSP file not found: {dsp_file}")

		output_file = temp_output_dir / dsp_filename.replace(".dsp", ".py")

		cmd = [
			str(faust_compiler),
			"-lang", "nnx",
			"-a", str(jax_architecture_dir / "minimal.py"),
			"-I", str(jax_library_dir),
			"-o", str(output_file),
			str(dsp_file),
		]

		if extra_args:
			cmd.extend(extra_args)

		result = subprocess.run(
			cmd,
			capture_output=True,
			text=True,
			check=True,
		)

		if not output_file.exists():
			raise RuntimeError(f"Compilation succeeded but output file not created: {output_file}")

		return output_file

	return _compile


@pytest.fixture
def load_compiled_dsp(temp_output_dir):
	"""
	Fixture that returns a function to load a compiled DSP module.

	Usage:
		load_func = load_compiled_dsp
		mydsp = load_func(output_file)
		model = mydsp(sample_rate=48000, rngs=rngs)
	"""
	def _load(python_file: Path):
		"""
		Dynamically load a compiled Faust Python module.

		Args:
			python_file: Path to the generated Python file

		Returns:
			The mydsp class from the module
		"""
		module = load_module(python_file)

		if not hasattr(module, "mydsp"):
			raise AttributeError(f"Module does not contain 'mydsp' class: {python_file}")

		return module.mydsp

	return _load


@pytest.fixture
def compile_and_load_dsp(compile_faust_dsp, load_compiled_dsp):
	"""
	Fixture that compiles and loads a DSP in one step.

	Usage:
		compile_and_load = compile_and_load_dsp
		mydsp = compile_and_load("simple_gain.dsp")
		model = mydsp(sample_rate=48000, rngs=rngs)
	"""
	def _compile_and_load(dsp_filename: str, extra_args: list = None):
		"""
		Compile and load a Faust DSP file.

		Args:
			dsp_filename: Name of the DSP file
			extra_args: Additional compiler arguments

		Returns:
			The mydsp class
		"""
		output_file = compile_faust_dsp(dsp_filename, extra_args)
		return load_compiled_dsp(output_file)

	return _compile_and_load


@pytest.fixture
def default_rngs():
	"""Default RNG configuration for tests."""
	return nnx.Rngs(0, params=0, rng_stream=0)


@pytest.fixture
def assets_dir():
	"""Path to the assets directory for soundfile tests.

	The dummy WAV files are gitignored (assets/.gitignore holds ``*.wav``),
	so the directory always exists in a checkout but the files do not. Create
	them on demand — 1 s of 4-channel silence, matching the Makefile's dummy
	files for sound.dsp — so the soundfile tests are self-sufficient whether or
	not ``make`` has run (the CI pytest job invokes pytest directly).
	"""
	import numpy as np
	from scipy.io import wavfile

	assets_path = Path(__file__).parent / "assets"
	assets_path.mkdir(exist_ok=True)
	silence = np.zeros((44100, 4), dtype=np.float32)
	for name in ("sound1.wav", "sound2.wav"):
		wav = assets_path / name
		if not wav.exists():
			wavfile.write(str(wav), 44100, silence)
	return str(assets_path)


@pytest.fixture(params=[44100, 48000])
def sample_rate(request):
	"""Parametrize tests across common sample rates."""
	return request.param


@pytest.fixture(params=[jnp.float32, jnp.float64])
def faust_float(request):
	"""Parametrize tests across float32 and float64."""
	return request.param


@pytest.fixture
def impulse_input():
	"""Generate an impulse signal for testing."""
	def _impulse(num_inputs: int, length: int, dtype=jnp.float32):
		signal = jnp.zeros((num_inputs, length), dtype=dtype)
		signal = signal.at[:, 0].set(1.0)
		return signal
	return _impulse


@pytest.fixture
def random_input():
	"""Generate random noise signal for testing."""
	def _random(num_inputs: int, length: int, seed: int = 0, dtype=jnp.float32):
		key = jax.random.key(seed)
		return jax.random.uniform(
			key,
			shape=(num_inputs, length),
			minval=-1.0,
			maxval=1.0,
			dtype=dtype,
		)
	return _random


@pytest.fixture
def assert_output_shape():
	"""Helper to assert output has correct shape."""
	def _assert(output, num_outputs: int, length: int):
		assert output.ndim == 2, f"Expected 2D output, got {output.ndim}D"
		assert output.shape[0] == num_outputs, f"Expected {num_outputs} channels, got {output.shape[0]}"
		assert output.shape[1] == length, f"Expected {length} samples, got {output.shape[1]}"
	return _assert


@pytest.fixture
def assert_finite():
	"""Helper to assert all values are finite (no NaN or inf)."""
	def _assert(array):
		assert jnp.all(jnp.isfinite(array)), "Output contains NaN or inf values"
	return _assert


# Hooks for pytest reporting

def pytest_configure(config):
	"""Add custom markers to pytest configuration."""
	config.addinivalue_line("markers", "unit: Unit tests")
	config.addinivalue_line("markers", "integration: Integration tests")
	config.addinivalue_line("markers", "gradient: Gradient/AD tests")
	config.addinivalue_line("markers", "performance: Performance tests")
	config.addinivalue_line("markers", "slow: Slow-running tests")
	config.addinivalue_line("markers", "ci: CI-suitable tests")


def pytest_collection_modifyitems(config, items):
	"""Automatically mark tests based on their location/name."""
	for item in items:
		# Auto-mark based on test file location
		if "unit" in str(item.fspath):
			item.add_marker(pytest.mark.unit)
		elif "integration" in str(item.fspath):
			item.add_marker(pytest.mark.integration)
		elif "gradient" in str(item.fspath) or "ad" in str(item.fspath):
			item.add_marker(pytest.mark.gradient)
		elif "performance" in str(item.fspath) or "benchmark" in str(item.fspath):
			item.add_marker(pytest.mark.performance)

		# Auto-mark tests containing "slow" in their name
		if "slow" in item.nodeid.lower():
			item.add_marker(pytest.mark.slow)
