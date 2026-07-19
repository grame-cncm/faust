"""
End-to-end gradient tests using compiled Faust DSPs.

These tests verify that gradients flow correctly through actual Faust-generated
code and that parameters can be optimized using gradient descent.
"""

import pytest
import jax
import jax.numpy as jnp
from jax import random
from flax import nnx
import optax


@pytest.mark.gradient
@pytest.mark.integration
class TestFaustDSPGradients:
    """Test gradient flow through compiled Faust DSPs."""

    def test_gradient_through_gain_dsp(
        self,
        compile_and_load_dsp,
        default_rngs,
        impulse_input,
        assert_finite
    ):
        """Test gradient computation through a simple gain DSP."""
        mydsp = compile_and_load_dsp("learnable_gain.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        # Create input signal
        inputs = impulse_input(model.num_inputs, 1024)

        # Define a simple loss function
        def loss_fn(model, inputs):
            outputs = model(inputs)
            return jnp.sum(outputs ** 2)

        # Compute gradients
        grad_fn = nnx.value_and_grad(loss_fn)
        loss, grads = grad_fn(model, inputs)

        # Verify loss and gradients are finite
        assert jnp.isfinite(loss)

        # Check all gradient leaves are finite
        for leaf in jax.tree.leaves(nnx.state(grads)):
            if isinstance(leaf, jnp.ndarray):
                assert_finite(leaf)

        # Verify we have gradients for the gain parameter
        state = nnx.state(grads)
        # The gradient state should contain the gain parameter gradient
        assert len(jax.tree.leaves(state)) > 0

    def test_parameter_optimization_gain(
        self,
        compile_and_load_dsp,
        default_rngs,
        impulse_input
    ):
        """Test optimizing gain parameter to match target output."""
        mydsp = compile_and_load_dsp("learnable_gain.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        # Create input signal
        inputs = impulse_input(model.num_inputs, 1024)

        # Create target output (gain of 0.8)
        target_gain = 0.8
        target_output = inputs * target_gain

        # Define loss function
        def loss_fn(model):
            outputs = model(inputs)
            return jnp.mean((outputs - target_output) ** 2)

        # Create optimizer - use nnx.Param filter for wrt
        optimizer = nnx.Optimizer(model, optax.adam(learning_rate=0.01), wrt=nnx.Param)

        # Training loop
        initial_loss = loss_fn(model)
        num_steps = 100

        for step in range(num_steps):
            loss, grads = nnx.value_and_grad(loss_fn)(model)
            optimizer.update(model, grads)

        final_loss = loss_fn(model)

        # Loss should decrease significantly
        assert final_loss < initial_loss
        assert final_loss < 0.01  # Should be very close to target

        # Check that output is close to target
        outputs = model(inputs)
        output_error = jnp.mean(jnp.abs(outputs - target_output))
        assert output_error < 0.05  # Output should be close to target

    def test_gradient_flow_through_filter(
        self,
        compile_and_load_dsp,
        default_rngs,
        impulse_input,
        assert_finite
    ):
        """Test gradient computation through a filter DSP."""
        mydsp = compile_and_load_dsp("learnable_filter.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        # Create input signal (white noise for better frequency coverage)
        key = random.key(42)
        inputs = random.uniform(key, shape=(model.num_inputs, 1024),
                                    minval=-1.0, maxval=1.0, dtype=jnp.float32)

        # Define a loss function
        def loss_fn(model, inputs):
            outputs = model(inputs)
            # Loss based on spectral energy
            return jnp.sum(outputs ** 2)

        # Compute gradients
        grad_fn = nnx.value_and_grad(loss_fn)
        loss, grads = grad_fn(model, inputs)

        # Verify loss and gradients are finite
        assert jnp.isfinite(loss)

        # Check all gradient leaves are finite
        for leaf in jax.tree.leaves(nnx.state(grads)):
            if isinstance(leaf, jnp.ndarray):
                assert_finite(leaf)

    @pytest.mark.slow
    def test_filter_cutoff_optimization(
        self,
        compile_and_load_dsp,
        default_rngs
    ):
        """Test optimizing filter cutoff to match target frequency response."""
        mydsp = compile_and_load_dsp("learnable_filter.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        # Create broadband input (white noise)
        key = random.key(42)
        inputs = random.uniform(key, shape=(model.num_inputs, 4096),
                                    minval=-1.0, maxval=1.0, dtype=jnp.float32)

        # Target: lowpass at specific cutoff
        # We'll use a simple proxy: output RMS should be lower than input
        # (since filter removes high frequencies)
        target_rms_ratio = 0.5  # Target 50% energy reduction

        def loss_fn(model):
            outputs = model(inputs)
            input_rms = jnp.sqrt(jnp.mean(inputs ** 2))
            output_rms = jnp.sqrt(jnp.mean(outputs ** 2))
            rms_ratio = output_rms / (input_rms + 1e-8)
            return (rms_ratio - target_rms_ratio) ** 2

        # Create optimizer - use nnx.Param filter for wrt
        optimizer = nnx.Optimizer(model, optax.adam(learning_rate=0.01), wrt=nnx.Param)

        # Training loop
        initial_loss = loss_fn(model)
        num_steps = 50

        losses = []
        for step in range(num_steps):
            loss, grads = nnx.value_and_grad(loss_fn)(model)
            losses.append(float(loss))
            optimizer.update(model, grads)

        final_loss = loss_fn(model)

        # Loss should decrease
        assert final_loss < initial_loss
        # Should converge to some degree
        assert losses[-1] < losses[0] * 0.5


@pytest.mark.gradient
@pytest.mark.integration
class TestGradientNumericalStability:
    """Test numerical stability of gradients through DSPs."""

    def test_no_nan_gradients(
        self,
        compile_and_load_dsp,
        default_rngs,
        impulse_input
    ):
        """Test that gradients don't produce NaN values."""
        mydsp = compile_and_load_dsp("learnable_gain.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        inputs = impulse_input(model.num_inputs, 1024)

        def loss_fn(model, inputs):
            outputs = model(inputs)
            return jnp.sum(outputs ** 2)

        grad_fn = nnx.value_and_grad(loss_fn)
        loss, grads = grad_fn(model, inputs)

        # Check all gradients are finite
        for grad_array in jax.tree.leaves(nnx.state(grads)):
            if isinstance(grad_array, jnp.ndarray):
                assert jnp.all(jnp.isfinite(grad_array)), "Gradient contains NaN or inf"

    def test_gradient_consistency(
        self,
        compile_and_load_dsp,
        default_rngs,
        impulse_input
    ):
        """Test that gradients are consistent across multiple computations."""
        mydsp = compile_and_load_dsp("learnable_gain.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        inputs = impulse_input(model.num_inputs, 1024)

        def loss_fn(model, inputs):
            outputs = model(inputs)
            return jnp.sum(outputs ** 2)

        # Compute gradients multiple times
        grad_fn = nnx.value_and_grad(loss_fn)

        _, grads1 = grad_fn(model, inputs)
        _, grads2 = grad_fn(model, inputs)

        # Gradients should be identical
        state1 = nnx.state(grads1)
        state2 = nnx.state(grads2)

        for leaf1, leaf2 in zip(jax.tree.leaves(state1), jax.tree.leaves(state2)):
            if isinstance(leaf1, jnp.ndarray) and isinstance(leaf2, jnp.ndarray):
                assert jnp.allclose(leaf1, leaf2), "Gradients are not consistent"


@pytest.mark.gradient
class TestJITCompatibility:
    """Test that gradient computation works with JIT compilation."""

    def test_jit_gradient_computation(
        self,
        compile_and_load_dsp,
        default_rngs,
        impulse_input
    ):
        """Test that gradient computation works under JIT."""
        mydsp = compile_and_load_dsp("learnable_gain.dsp")
        model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=default_rngs)

        inputs = impulse_input(model.num_inputs, 1024)

        def loss_fn(model, inputs):
            outputs = model(inputs)
            return jnp.sum(outputs ** 2)

        # JIT the gradient computation
        @jax.jit
        def compute_grad(model, inputs):
            return nnx.value_and_grad(loss_fn)(model, inputs)

        # Should work without errors
        loss, grads = compute_grad(model, inputs)

        assert jnp.isfinite(loss)
        assert len(jax.tree.leaves(nnx.state(grads))) > 0
