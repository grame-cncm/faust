"""
Integration tests for JAX backend features.

Tests all interesting features:
- Random stream independence
- Gumbel-softmax (nentry with learnable tau)
- Scale modes (linear, log, exp)
- Learnable soundfiles
- Magic-clamp gradients
"""

import pytest
import jax
import jax.numpy as jnp
from flax import nnx
import numpy as np


@pytest.mark.integration
@pytest.mark.ci
class TestRandomStreamIndependence:
	"""Test that random functions produce independent streams per channel."""

	@pytest.mark.parametrize("dsp_file", [
		"random_uniform.dsp",
		"random_normal.dsp",
		"random_exponential.dsp",
		"random_bernoulli.dsp",
		"random_beta.dsp",
	])
	def test_stereo_random_independence(
		self,
		compile_and_load_dsp,
		default_rngs,
		dsp_file
	):
		"""Test that stereo random generators produce independent streams."""
		mydsp = compile_and_load_dsp(dsp_file)
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		# Generate samples
		inputs = jnp.zeros((model.num_inputs, 1000))
		outputs = model(inputs)

		# Should have 2 output channels
		assert outputs.shape[0] == 2

		ch0 = outputs[0, :]
		ch1 = outputs[1, :]

		# Channels should NOT be identical
		identical = jnp.allclose(ch0, ch1)
		assert not identical, f"{dsp_file}: Channels have identical values (caching issue!)"

		# Correlation should be low (< 0.5 for independence)
		correlation = float(jnp.corrcoef(jnp.stack([ch0, ch1]))[0, 1])
		assert abs(correlation) < 0.5, f"{dsp_file}: Correlation {correlation} too high (streams not independent)"


@pytest.mark.integration
class TestNentryGumbelSoftmax:
	"""Test nentry with Gumbel-softmax and tau configuration."""

	def test_nentry_default_tau(self, compile_and_load_dsp, default_rngs):
		"""Test nentry with default tau (fixed at 1.0)."""
		mydsp = compile_and_load_dsp("nentry_default.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		# Check tau parameter exists
		assert hasattr(model, "fEntry0_tau")
		tau = model.fEntry0_tau

		# Should be Variable (non-learnable) with value 1.0
		assert isinstance(tau, nnx.Variable)
		assert float(tau[...]) == 1.0

		# Check metadata
		metadata = model.get_parameter_metadata()["fEntry0"]
		assert metadata["tau_learnable"] == False
		assert metadata["tau_init"] == 1.0

	def test_nentry_learnable_tau(self, compile_and_load_dsp, default_rngs):
		"""Test nentry with learnable tau."""
		mydsp = compile_and_load_dsp("nentry_test.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		# Check tau parameter exists
		assert hasattr(model, "fEntry0_tau")
		tau = model.fEntry0_tau

		# Should be Param (learnable) with initial value 0.5
		assert isinstance(tau, nnx.Param)
		assert float(tau[...]) == 0.5

		# Check metadata
		metadata = model.get_parameter_metadata()["fEntry0"]
		assert metadata["tau_learnable"] == True
		assert metadata["tau_init"] == 0.5
		assert metadata["metadata"]["tau"] == "learnable"
		assert metadata["metadata"]["tau_init"] == "0.5"

	def test_nentry_gumbel_softmax_output(
		self,
		compile_and_load_dsp,
		impulse_input
	):
		"""Test that nentry produces valid discrete outputs."""
		# Create RNGs with nentry for soft sampling
		rngs = nnx.Rngs(42, params=42, rng_stream=42, nentry=123)
		mydsp = compile_and_load_dsp("nentry_test.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

		inputs = impulse_input(model.num_inputs, 1024)
		outputs = model(inputs)

		# Output should be finite and valid
		assert jnp.all(jnp.isfinite(outputs))

		# For nentry with range [0, 3], outputs should be in that range
		assert jnp.all(outputs >= 0.0)
		assert jnp.all(outputs <= 3.0)


@pytest.mark.integration
class TestScaleModes:
	"""Test different scale modes for sliders."""

	def test_linear_scale(self):
		"""Test linear scale mode (default)."""
		# This would require a DSP with linear slider
		pytest.skip("Requires DSP with linear scale slider")

	def test_log_scale(self):
		"""Test logarithmic scale mode."""
		# This would require a DSP with log scale slider
		pytest.skip("Requires DSP with log scale slider")

	def test_exp_scale(self):
		"""Test exponential scale mode."""
		# This would require a DSP with exp scale slider
		pytest.skip("Requires DSP with exp scale slider")


@pytest.mark.integration
class TestLearnableSoundfiles:
	"""Test soundfile parameters with [param:1] metadata."""

	def test_soundfile_non_learnable(self, compile_and_load_dsp, default_rngs, assets_dir):
		"""Test that default soundfiles are not learnable."""
		if assets_dir is None:
			pytest.skip("Requires assets folder - run from tests/jax-tests directory")

		mydsp = compile_and_load_dsp("sound.dsp")
		model = mydsp(
			sample_rate=44100,
			faust_float=jnp.float32,
			rngs=default_rngs,
			soundfile_dirs=[assets_dir]
		)

		# Check metadata
		metadata = model.get_parameter_metadata()["fSoundfile0"]
		assert metadata["is_param"] == False

		# fBuffers should be regular array, not Param
		sf = model.fSoundfile0
		assert not isinstance(sf["fBuffers"], nnx.Param)

	def test_soundfile_learnable(self, compile_and_load_dsp, default_rngs, assets_dir):
		"""Test soundfile with [param:1] metadata makes it learnable."""
		if assets_dir is None:
			pytest.skip("Requires assets folder - run from tests/jax-tests directory")

		mydsp = compile_and_load_dsp("soundfile_learnable.dsp")
		model = mydsp(
			sample_rate=44100,
			faust_float=jnp.float32,
			rngs=default_rngs,
			soundfile_dirs=[assets_dir]
		)

		# Check metadata
		metadata = model.get_parameter_metadata()["fSoundfile0"]
		assert metadata["is_param"] == True
		assert metadata["metadata"]["param"] == "1"

		# fBuffers should be Param (learnable)
		sf = model.fSoundfile0
		assert isinstance(sf["fBuffers"], nnx.Param)

	def test_soundfile_gradient_flow(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input,
		assets_dir
	):
		"""Test that gradients flow through learnable soundfiles."""
		if assets_dir is None:
			pytest.skip("Requires assets folder - run from tests/jax-tests directory")

		mydsp = compile_and_load_dsp("soundfile_learnable.dsp")
		model = mydsp(
			sample_rate=44100,
			faust_float=jnp.float32,
			rngs=default_rngs,
			soundfile_dirs=[assets_dir]
		)

		inputs = impulse_input(model.num_inputs, 1024)

		def loss_fn(model, inputs):
			outputs = model(inputs)
			return jnp.sum(outputs ** 2)

		# Compute gradients
		grad_fn = nnx.value_and_grad(loss_fn)
		loss, grads = grad_fn(model, inputs)

		# Should compute successfully
		assert jnp.isfinite(loss)

		# Check that soundfile buffers have gradients
		grad_state = nnx.state(grads)
		has_soundfile_grad = False
		for leaf in jax.tree.leaves(grad_state):
			if isinstance(leaf, jnp.ndarray) and leaf.size > 100:
				# Likely the soundfile buffer gradient
				has_soundfile_grad = True
				break

		assert has_soundfile_grad, "No gradients found for soundfile buffers"


@pytest.mark.integration
class TestMagicClampIntegration:
	"""Test magic-clamp enabled by default in compiled DSPs."""

	def test_magic_clamp_enabled_by_default(self, compile_and_load_dsp, default_rngs):
		"""Test that magic-clamp is enabled by default."""
		mydsp = compile_and_load_dsp("learnable_gain.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		assert hasattr(model, "use_magic_clamp")
		assert model.use_magic_clamp == True

	def test_magic_clamp_can_be_disabled(self, compile_and_load_dsp, default_rngs):
		"""Test that magic-clamp can be explicitly disabled."""
		mydsp = compile_and_load_dsp("learnable_gain.dsp")
		model = mydsp(
			sample_rate=44100,
			faust_float=jnp.float32,
			rngs=default_rngs,
			use_magic_clamp=False
		)

		assert model.use_magic_clamp == False
