"""
Integration tests for polyphony via widget modulation and jax.vmap.

Tests the workflow described in the README Polyphony Support section:
1. Widget modulation turns hslider params into signal inputs
2. Single-voice processing with process_block
3. Multi-voice polyphony via jax.vmap
"""

import pytest
import jax
import jax.numpy as jnp
from jax import random
from flax import nnx


@pytest.fixture(scope="module", autouse=True)
def enable_x64():
	"""Enable 64-bit precision for this module's -double compiled DSPs.

	Scoped to the module (not set at import time) so the float32 tests in the
	rest of the suite run under JAX's default configuration.
	"""
	jax.config.update("jax_enable_x64", True)
	yield
	jax.config.update("jax_enable_x64", False)


@pytest.mark.integration
@pytest.mark.ci
class TestWidgetModulation:
	"""Test that widget modulation replaces UI params with signal inputs."""

	def test_widget_modulation_removes_params(self, compile_and_load_dsp, default_rngs):
		"""Widget modulation should produce 3 inputs and no UI parameters."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		assert model.num_inputs == 3, f"Expected 3 inputs (freq, gain, gate), got {model.num_inputs}"
		assert model.num_outputs == 1

		# No UI parameters — all widgets replaced by signal inputs
		metadata = model.get_parameter_metadata()
		assert len(metadata) == 0, f"Expected no UI params, got {list(metadata.keys())}"


@pytest.mark.integration
@pytest.mark.ci
class TestSingleVoice:
	"""Test single-voice processing with widget-modulated DSP."""

	def test_single_voice_process_block(self, compile_and_load_dsp, default_rngs):
		"""Single voice should produce finite audio output."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)
		carry = model.initialize_carry()

		num_frames = 1024
		inputs = jnp.stack([
			jnp.full(num_frames, 440.0),  # freq
			jnp.full(num_frames, 0.8),    # gain
			jnp.full(num_frames, 1.0),    # gate
		])

		carry, audio = model.process_block(carry, inputs, rngs=default_rngs)

		assert audio.shape == (1, num_frames)
		assert jnp.all(jnp.isfinite(audio))
		# Gate is on and gain > 0, so output should be non-silent after smoothing kicks in
		assert jnp.max(jnp.abs(audio)) > 0.0

	def test_gate_off_produces_silence(self, compile_and_load_dsp, default_rngs):
		"""With gate=0 from the start, output should converge to silence."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)
		carry = model.initialize_carry()

		num_frames = 4096
		inputs = jnp.stack([
			jnp.full(num_frames, 440.0),  # freq
			jnp.full(num_frames, 0.8),    # gain
			jnp.full(num_frames, 0.0),    # gate OFF
		])

		carry, audio = model.process_block(carry, inputs, rngs=default_rngs)

		# en.ar envelope stays at 0 when gate is always 0, so output should be all zeros
		assert jnp.allclose(audio, 0.0, atol=1e-10)


@pytest.mark.integration
@pytest.mark.ci
class TestPolyphonyVmap:
	"""Test multi-voice polyphony via jax.vmap.

	Note: process_block uses Flax NNX's Rngs internally, which has mutable state
	that cannot be used inside jax.vmap. The solution is to pass explicit JAX
	random keys (jax.Array), which process_block accepts and passes through
	without mutation.
	"""

	@staticmethod
	def _make_voice_inputs(freqs, num_frames, gain=0.5):
		"""Create per-voice inputs: (num_voices, 3, num_frames)."""
		return jnp.stack([
			jnp.stack([
				jnp.full(num_frames, f),
				jnp.full(num_frames, gain),
				jnp.full(num_frames, 1.0),
			])
			for f in freqs
		])

	def test_vmap_produces_correct_shape(self, compile_and_load_dsp, default_rngs):
		"""vmap over process_block should produce (num_voices, 1, num_frames)."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		num_voices = 4
		num_frames = 1024

		states = jax.tree.map(
			lambda x: jnp.stack([x] * num_voices),
			model.initialize_carry(),
		)

		freqs = jnp.array([261.63, 329.63, 392.00, 523.25])
		voice_inputs = self._make_voice_inputs(freqs, num_frames)

		# Pass explicit per-voice RNG keys to avoid Flax Rngs mutation inside vmap
		rng_keys = random.split(random.key(0), num_voices)

		def poly_step(carry, inputs, rng_key):
			return model.process_block(carry, inputs, rngs=rng_key)

		new_states, voices = jax.vmap(poly_step)(states, voice_inputs, rng_keys)

		assert voices.shape == (num_voices, 1, num_frames)
		assert jnp.all(jnp.isfinite(voices))

	def test_vmap_voices_are_independent(self, compile_and_load_dsp, default_rngs):
		"""Each voice should produce different output for different frequencies."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		num_voices = 2
		num_frames = 1024

		states = jax.tree.map(
			lambda x: jnp.stack([x] * num_voices),
			model.initialize_carry(),
		)

		freqs = jnp.array([440.0, 880.0])
		voice_inputs = self._make_voice_inputs(freqs, num_frames)
		rng_keys = random.split(random.key(0), num_voices)

		def poly_step(carry, inputs, rng_key):
			return model.process_block(carry, inputs, rngs=rng_key)

		_, voices = jax.vmap(poly_step)(states, voice_inputs, rng_keys)

		# Voices should NOT be identical (different frequencies)
		assert not jnp.allclose(voices[0], voices[1]), "Voices at different frequencies should differ"

	def test_vmap_sum_produces_mix(self, compile_and_load_dsp, default_rngs):
		"""Summing vmapped voices should produce a valid polyphonic mix."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		num_voices = 4
		num_frames = 1024

		states = jax.tree.map(
			lambda x: jnp.stack([x] * num_voices),
			model.initialize_carry(),
		)

		# C major chord
		freqs = jnp.array([261.63, 329.63, 392.00, 523.25])
		voice_inputs = self._make_voice_inputs(freqs, num_frames, gain=0.25)
		rng_keys = random.split(random.key(0), num_voices)

		def poly_step(carry, inputs, rng_key):
			return model.process_block(carry, inputs, rngs=rng_key)

		_, voices = jax.vmap(poly_step)(states, voice_inputs, rng_keys)

		# Sum voices
		output = jnp.sum(voices, axis=0)  # (1, num_frames)
		assert output.shape == (1, num_frames)
		assert jnp.all(jnp.isfinite(output))
		# Mixed output should be non-silent
		assert jnp.max(jnp.abs(output)) > 0.0

	def test_vmap_state_propagation(self, compile_and_load_dsp, default_rngs):
		"""State should propagate correctly across multiple vmapped blocks."""
		mydsp = compile_and_load_dsp("poly_synth.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		num_voices = 2
		num_frames = 512

		states = jax.tree.map(
			lambda x: jnp.stack([x] * num_voices),
			model.initialize_carry(),
		)

		freqs = jnp.array([440.0, 880.0])
		voice_inputs = self._make_voice_inputs(freqs, num_frames)

		def poly_step(carry, inputs, rng_key):
			return model.process_block(carry, inputs, rngs=rng_key)

		poly_process = jax.vmap(poly_step)

		# Process two consecutive blocks with different RNG keys
		rng_keys1 = random.split(random.key(0), num_voices)
		states, voices1 = poly_process(states, voice_inputs, rng_keys1)

		rng_keys2 = random.split(random.key(1), num_voices)
		states, voices2 = poly_process(states, voice_inputs, rng_keys2)

		# Second block should differ from first (oscillator phase has advanced,
		# AR envelope has evolved)
		assert not jnp.allclose(voices1, voices2), "Consecutive blocks should differ (state should evolve)"


@pytest.mark.integration
@pytest.mark.gradient
@pytest.mark.ci
class TestPolyphonyGradSafetensors:
	"""Backprop into shared params and safetensors round-trip, under outer jax.jit + vmap.

	Uses poly_synth_param.dsp, which keeps one shared learnable ``cutoff`` slider
	(an ``nnx.Param`` broadcast across voices) alongside the per-voice freq/gain/gate
	inputs. This demonstrates the conventions this branch standardizes on:

	1. The functional split/merge ``jax.jit(jax.vmap(...))`` render matches the
	   plain closed-over-model render (composition).
	2. Gradients flow into the shared param — the per-voice contributions
	   accumulate onto the one shared param set — and a small gradient step lowers
	   the loss (polyphonic training).
	3. ``save_params``/``load_params`` reproduce identical params, audio, and
	   gradients, independent of voice count (portable persistence).
	"""

	@staticmethod
	def _make_voice_inputs(freqs, num_frames, gain=0.5):
		"""Create per-voice inputs: (num_voices, 3, num_frames)."""
		return jnp.stack([
			jnp.stack([
				jnp.full(num_frames, f),
				jnp.full(num_frames, gain),
				jnp.full(num_frames, 1.0),
			])
			for f in freqs
		])

	def test_backprop_and_safetensors_roundtrip(self, compile_and_load_dsp, tmp_path):
		mydsp = compile_and_load_dsp("poly_synth_param.dsp", extra_args=["-double"])
		model = mydsp(sample_rate=44100, rngs=nnx.Rngs(0, params=0, rng_stream=0))

		assert model.num_inputs == 3  # freq, gain, gate as inputs

		num_voices, num_frames = 3, 256
		freqs = jnp.array([261.63, 329.63, 392.00])  # C major triad
		voice_inputs = self._make_voice_inputs(freqs, num_frames)
		carries = jax.tree.map(
			lambda x: jnp.stack([x] * num_voices), model.initialize_carry()
		)
		rng_keys = random.split(random.key(0), num_voices)

		# Split the shared learnable params (the differentiation target) from the
		# rest of the module state (RNG counters, fixed variables, ...).
		graphdef, params_state, rest = nnx.split(model, nnx.Param, ...)
		assert len(jax.tree.leaves(params_state)) == 1  # exactly the shared cutoff

		@jax.jit
		def poly_render(params_state):
			m = nnx.merge(graphdef, params_state, rest)

			def poly_step(carry, inputs, rng_key):
				return m.process_block(carry, inputs, rngs=rng_key)

			# Params are shared (closed over in `m`); voices/carry/rng are mapped.
			_, voices = jax.vmap(poly_step, in_axes=(0, 0, 0))(
				carries, voice_inputs, rng_keys
			)
			return jnp.sum(voices, axis=0)  # polyphonic mix: (num_outputs, frames)

		# (1) Composition: the split/merge jit+vmap render matches the plain
		# closed-over-model render.
		def poly_render_plain(m):
			def poly_step(carry, inputs, rng_key):
				return m.process_block(carry, inputs, rngs=rng_key)

			_, voices = jax.vmap(poly_step)(carries, voice_inputs, rng_keys)
			return jnp.sum(voices, axis=0)

		out_jit = poly_render(params_state)
		out_plain = poly_render_plain(model)
		assert out_jit.shape == (model.num_outputs, num_frames)
		assert jnp.allclose(out_jit, out_plain, atol=1e-6)

		# Target: the polyphonic mix at a different (reachable) normalized cutoff.
		target_state = jax.tree.map(lambda p: jnp.full_like(p, 0.6), params_state)
		target = poly_render(target_state)

		def loss_fn(ps):
			return jnp.mean((poly_render(ps) - target) ** 2)

		# (2) Backprop into the shared param.
		loss0, grads = jax.value_and_grad(loss_fn)(params_state)
		gleaves = jax.tree.leaves(grads)
		assert all(jnp.all(jnp.isfinite(g)) for g in gleaves)
		gnorm = jnp.sqrt(sum(jnp.sum(g ** 2) for g in gleaves))
		assert float(gnorm) > 0.0, "shared-param gradient should be non-zero"

		# A small (normalized) gradient-descent step lowers the loss.
		lr = 1e-2
		stepped = jax.tree.map(
			lambda p, g: p - lr * g / (gnorm + 1e-12), params_state, grads
		)
		loss1 = loss_fn(stepped)
		assert float(loss1) < float(loss0)

		# (3) Save/load round-trip reproduces params, audio, and gradients.
		nnx.update(model, stepped)  # write trained params into the live model
		ckpt = tmp_path / "poly.safetensors"
		model.save_params(ckpt)

		fresh = mydsp(sample_rate=44100, rngs=nnx.Rngs(0, params=0, rng_stream=0))
		fresh.load_params(ckpt)
		_, fresh_ps, _ = nnx.split(fresh, nnx.Param, ...)

		# (a) identical params
		for a, b in zip(jax.tree.leaves(stepped), jax.tree.leaves(fresh_ps)):
			assert jnp.array_equal(a, b)
		# (b) identical polyphonic audio
		assert jnp.array_equal(poly_render(fresh_ps), poly_render(stepped))
		# (c) identical gradients
		_, grads_stepped = jax.value_and_grad(loss_fn)(stepped)
		_, grads_fresh = jax.value_and_grad(loss_fn)(fresh_ps)
		for a, b in zip(jax.tree.leaves(grads_stepped), jax.tree.leaves(grads_fresh)):
			assert jnp.array_equal(a, b)
