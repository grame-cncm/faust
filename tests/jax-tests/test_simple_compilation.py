"""
Integration tests for basic Faust DSP compilation and execution.
"""

import pytest
import jax
import jax.numpy as jnp
from flax import nnx


@pytest.fixture(scope="module", autouse=True)
def enable_x64():
	"""Enable 64-bit precision for this module's float64 tests.

	Scoped to the module (not set at import time) so the float32 tests in the
	rest of the suite run under JAX's default configuration.
	"""
	jax.config.update("jax_enable_x64", True)
	yield
	jax.config.update("jax_enable_x64", False)


@pytest.mark.integration
@pytest.mark.ci
class TestSimpleCompilation:
	"""Test basic compilation and execution of simple DSP files."""

	def test_compile_process_dsp(self, compile_and_load_dsp, default_rngs):
		"""Test that process.dsp compiles and runs without errors."""
		# Compile the DSP
		mydsp = compile_and_load_dsp("process.dsp")

		# Instantiate the model
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		# Verify model has expected attributes
		assert hasattr(model, "num_inputs")
		assert hasattr(model, "num_outputs")
		assert hasattr(model, "__call__")
		assert hasattr(model, "initialize_carry")

	def test_impulse_response(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input,
		assert_output_shape,
		assert_finite
	):
		"""Test impulse response generation."""
		# Compile and load
		mydsp = compile_and_load_dsp("process.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		# Create impulse input
		length = 1024
		inputs = impulse_input(model.num_inputs, length)

		# Process
		outputs = model(inputs)

		# Verify output shape
		assert_output_shape(outputs, model.num_outputs, length)

		# Verify output is finite
		assert_finite(outputs)

	def test_process_block_stateful(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input,
		assert_output_shape,
		assert_finite
	):
		"""Test stateful block-by-block processing."""
		# Compile and load
		mydsp = compile_and_load_dsp("process.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		# Initialize carry
		carry = model.initialize_carry()

		# Process multiple blocks
		block_size = 512
		num_blocks = 4

		for i in range(num_blocks):
			inputs = impulse_input(model.num_inputs, block_size)
			carry, outputs = model.process_block(carry, inputs, rngs=default_rngs)

			# Verify output
			assert_output_shape(outputs, model.num_outputs, block_size)
			assert_finite(outputs)

			# Verify carry is a dictionary
			assert isinstance(carry, dict)

	@pytest.mark.parametrize("sample_rate", [44100, 48000, 96000])
	def test_different_sample_rates(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input,
		sample_rate
	):
		"""Test compilation and execution with different sample rates."""
		mydsp = compile_and_load_dsp("process.dsp")
		model = mydsp(sample_rate=sample_rate, faust_float=jnp.float32, rngs=default_rngs)

		inputs = impulse_input(model.num_inputs, 1024)
		outputs = model(inputs)

		assert outputs.shape == (model.num_outputs, 1024)

	@pytest.mark.parametrize("dtype", [jnp.float32, jnp.float64])
	def test_different_dtypes(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input,
		dtype
	):
		"""Test compilation with different floating point types."""
		mydsp = compile_and_load_dsp("process.dsp")
		model = mydsp(sample_rate=44100, faust_float=dtype, rngs=default_rngs)

		inputs = impulse_input(model.num_inputs, 1024, dtype=dtype)
		outputs = model(inputs)

		assert outputs.dtype == dtype
		assert outputs.shape == (model.num_outputs, 1024)


@pytest.mark.integration
class TestParameterHandling:
	"""Test parameter initialization and metadata."""

	def test_parameter_metadata(self, compile_and_load_dsp, default_rngs):
		"""Test that parameter metadata is correctly generated."""
		# This test would work with a DSP that has UI parameters
		# For now, just verify the method exists
		mydsp = compile_and_load_dsp("process.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		assert hasattr(model, "get_parameter_metadata")
		metadata = model.get_parameter_metadata()
		assert isinstance(metadata, dict)

	def test_unnormalize_parameters(self, compile_and_load_dsp, default_rngs):
		"""Test parameter unnormalization."""
		mydsp = compile_and_load_dsp("process.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		assert hasattr(model, "unnormalize")
		params = model.unnormalize()
		# params might be empty dict or 0 if no UI parameters
		assert params is not None
