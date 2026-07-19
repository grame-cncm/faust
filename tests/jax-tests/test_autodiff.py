"""
Gradient and automatic differentiation tests for Faust JAX backend.

These tests verify that:
1. Gradients can be computed through DSP operations
2. Parameters can be optimized using gradient descent
3. Gradient flow is preserved through constraints and transformations
"""

import pytest
import jax
import jax.numpy as jnp
from flax import nnx
import optax


@pytest.mark.gradient
@pytest.mark.ci
class TestBasicGradients:
	"""Test basic gradient computation through DSP operations."""

	def test_gradient_through_passthrough(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input
	):
		"""Test gradient computation through a simple passthrough DSP."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		inputs = impulse_input(model.num_inputs, 1024)

		# Define a simple loss function (L2 norm of output)
		def loss_fn(model, inputs):
			outputs = model(inputs)
			return jnp.sum(outputs ** 2)

		# Compute gradients
		# Note: This requires the model to have differentiable parameters
		# For process.dsp (which may not have parameters), this is a structural test
		grad_fn = nnx.value_and_grad(loss_fn)
		loss, grads = grad_fn(model, inputs)

		assert jnp.isfinite(loss)
		assert isinstance(grads, nnx.State)

	def test_gradient_through_scan(
		self,
		compile_and_load_dsp,
		default_rngs,
		impulse_input
	):
		"""Test that gradients propagate through nnx.scan."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		inputs = impulse_input(model.num_inputs, 1024)

		def loss_fn(model, inputs):
			outputs = model(inputs)
			# Mean squared error loss
			return jnp.mean(outputs ** 2)

		# This tests that scan is differentiable
		grad_fn = nnx.value_and_grad(loss_fn)
		loss, grads = grad_fn(model, inputs)

		assert jnp.isfinite(loss)


@pytest.mark.gradient
class TestParameterOptimization:
	"""Test parameter optimization using gradient descent."""

	def test_slider_parameter_optimization(self, compile_and_load_dsp, default_rngs):
		"""Gradient descent on a slider parameter converges to a target output.

		This is the canonical DDSP loop: render a target with a known gain, then
		optimize a second model's gain (starting from its default) to match it.
		"""
		mydsp = compile_and_load_dsp("learnable_gain.dsp")

		# Target: same DSP with the (normalized) gain parameter set to 0.9.
		target = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)
		target.fHslider0 = nnx.Param(jnp.array(0.9, dtype=jnp.float32))
		x = jnp.ones((target.num_inputs, 128), dtype=jnp.float32)
		target_out = target(x)

		# Model under optimization, starting from the default gain (0.5).
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		def loss_fn(model):
			return jnp.mean((model(x) - target_out) ** 2)

		losses = []
		lr = 1.0
		for _ in range(200):
			loss, grads = nnx.value_and_grad(loss_fn)(model)
			losses.append(float(loss))
			params = nnx.state(model, nnx.Param)
			nnx.update(model, jax.tree.map(lambda p, g: p - lr * g, params, grads))

		# Loss collapses and the learned gain matches the target.
		assert losses[-1] < losses[0] * 1e-2, f"loss did not converge: {losses[0]} -> {losses[-1]}"
		assert float(model.fHslider0[...]) == pytest.approx(0.9, abs=1e-2)


@pytest.mark.gradient
class TestConstraintGradients:
	"""Test gradient behavior with parameter constraints."""

	def test_clipping_gradient_flow(self):
		"""Test gradient flow through clipped parameters."""
		# Test that jnp.clip allows some gradient flow
		# Standard clip zeros gradients at boundaries
		x = jnp.array(1.5)

		def f(x):
			# Clip to [0, 1]
			return jnp.clip(x, 0.0, 1.0)

		grad_fn = jax.grad(f)
		grad = grad_fn(x)

		# Outside clip range, gradient is zero
		assert grad == 0.0


@pytest.mark.gradient
class TestGradientNumericalStability:
	"""Test numerical stability of gradients."""

	def test_no_gradient_explosion(
		self,
		compile_and_load_dsp,
		default_rngs,
		random_input
	):
		"""Test that gradients don't explode during backprop."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

		inputs = random_input(model.num_inputs, 1024, seed=0)

		def loss_fn(model, inputs):
			outputs = model(inputs)
			return jnp.sum(outputs ** 2)

		grad_fn = nnx.value_and_grad(loss_fn)
		loss, grads = grad_fn(model, inputs)

		# Check all gradients are finite
		for grad_array in jax.tree_util.tree_leaves(grads):
			if isinstance(grad_array, jnp.ndarray):
				assert jnp.all(jnp.isfinite(grad_array)), "Gradient contains NaN or inf"
