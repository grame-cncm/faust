"""
Tests for magic-clamp gradient handling.

These tests verify that the conditional straight-through estimator (STE)
improves gradient flow for constrained parameters compared to standard clipping.
"""

import pytest
import jax
import jax.numpy as jnp
import numpy as np
from magic_clamp import magic_clamp, standard_clamp, compare_clipping_gradients


@pytest.mark.gradient
@pytest.mark.unit
class TestMagicClampGradients:
    """Test basic gradient behavior of magic-clamp."""

    def test_gradient_inside_bounds(self):
        """Test that gradients flow normally when inside bounds."""
        x = jnp.array(0.5)

        # Both should pass gradients when inside bounds
        grad_std = jax.grad(lambda x: standard_clamp(x, 0.0, 1.0))(x)
        grad_magic = jax.grad(lambda x: magic_clamp(x, 0.0, 1.0))(x)

        assert grad_std == 1.0
        assert grad_magic == 1.0

    def test_gradient_below_lower_bound_negative_update(self):
        """Test gradient when below bound where update moves toward valid region."""
        x = jnp.array(-0.5)

        def loss_that_increases_x(x):
            # Loss that wants to decrease clip(x), so gradient is negative
            # Update: x_new = x - lr * (-1) = x + lr → moves toward bounds
            return -magic_clamp(x, 0.0, 1.0)

        # Standard clipping: gradient is 0 when outside bounds
        grad_std = jax.grad(lambda x: -standard_clamp(x, 0.0, 1.0))(x)
        assert grad_std == 0.0

        # Magic-clamp: gradient flows (update moves toward valid region)
        grad_magic = jax.grad(loss_that_increases_x)(x)
        assert grad_magic == -1.0  # Negative gradient means update increases x

    def test_gradient_below_lower_bound_positive_update(self):
        """Test gradient when below bound where update moves away from valid region."""
        x = jnp.array(-0.5)

        def loss_that_decreases_x(x):
            # Loss that wants to increase clip(x), so gradient is positive
            # Update: x_new = x - lr * (+1) = x - lr → moves away from bounds
            return magic_clamp(x, 0.0, 1.0)

        grad = jax.grad(loss_that_decreases_x)(x)

        # Magic-clamp should zero gradient when update moves further out
        assert grad == 0.0

    def test_gradient_above_upper_bound_positive_update(self):
        """Test gradient when above bound where update moves toward valid region."""
        x = jnp.array(1.5)

        def loss_that_decreases_x(x):
            # Loss that wants to increase clip(x), so gradient is positive
            # Update: x_new = x - lr * (+1) = x - lr → moves toward bounds
            return magic_clamp(x, 0.0, 1.0)

        # Standard clipping: gradient is 0
        grad_std = jax.grad(lambda x: standard_clamp(x, 0.0, 1.0))(x)
        assert grad_std == 0.0

        # Magic-clamp: gradient flows (update moves toward valid region)
        grad_magic = jax.grad(loss_that_decreases_x)(x)
        assert grad_magic == 1.0

    def test_gradient_above_upper_bound_negative_update(self):
        """Test gradient when above bound where update moves away from valid region."""
        x = jnp.array(1.5)

        def loss_that_increases_x(x):
            # Loss that wants to decrease clip(x), so gradient is negative
            # Update: x_new = x - lr * (-1) = x + lr → moves away from bounds
            return -magic_clamp(x, 0.0, 1.0)

        grad = jax.grad(loss_that_increases_x)(x)

        # Magic-clamp should zero gradient when update moves further out
        assert grad == 0.0

    def test_forward_pass_identical(self):
        """Test that forward pass is identical to standard clipping."""
        test_values = jnp.array([-1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0])

        std_output = jax.vmap(lambda x: standard_clamp(x, 0.0, 1.0))(test_values)
        magic_output = jax.vmap(lambda x: magic_clamp(x, 0.0, 1.0))(test_values)

        assert jnp.allclose(std_output, magic_output)

    def test_gradient_comparison_sweep(self):
        """Test gradient behavior across a sweep of values.

        Note: The gradient comparison uses the loss f(x) = clip(x) which has
        positive gradient everywhere. For x outside bounds:
        - x < min: grad > 0, update moves away from bounds → blocked by magic-clamp
        - x > max: grad > 0, update moves toward bounds → allowed by magic-clamp
        """
        x_values = jnp.linspace(-1.0, 2.0, 31)

        results = compare_clipping_gradients(x_values, min_val=0.0, max_val=1.0)

        for i, x in enumerate(x_values):
            grad_std = results['standard_grad'][i]
            grad_magic = results['magic_clamp_grad'][i]

            if x == 0.0 or x == 1.0:
                # Exactly on a bound: jnp.clip uses JAX's tie-splitting
                # subgradient (0.5), while magic-clamp passes the gradient
                # through (1.0) because the point is not strictly out of bounds.
                assert grad_std == 0.5
                assert grad_magic == 1.0
            elif 0.0 < x < 1.0:
                # Strictly inside bounds: both should be 1.0
                assert grad_std == 1.0
                assert grad_magic == 1.0
            elif x < 0.0:
                # Below lower bound with positive gradient:
                # Update x_new = x - lr * (+1) moves left (away from bounds)
                # Standard: 0, Magic: 0 (blocked)
                assert grad_std == 0.0
                assert grad_magic == 0.0
            else:  # x > 1.0
                # Above upper bound with positive gradient:
                # Update x_new = x - lr * (+1) moves left (toward bounds)
                # Standard: 0, Magic: 1 (allowed)
                assert grad_std == 0.0
                assert grad_magic == 1.0


@pytest.mark.gradient
@pytest.mark.integration
class TestMagicClampOptimization:
    """Test that magic-clamp improves optimization convergence."""

    def test_optimization_convergence_below_bounds(self):
        """Test that magic-clamp allows optimization when starting below bounds."""
        # Target: learn to output 0.8
        target = 0.8

        # Start parameter below lower bound
        param_init = -0.3

        # Standard clipping optimization
        param_std = param_init
        learning_rate = 0.05

        for _ in range(20):
            def loss_std(p):
                p_clipped = standard_clamp(p, 0.0, 1.0)
                return (p_clipped - target) ** 2

            grad = jax.grad(loss_std)(param_std)
            param_std = param_std - learning_rate * grad

        # Magic-clamp optimization
        param_magic = param_init

        for _ in range(20):
            def loss_magic(p):
                p_clipped = magic_clamp(p, 0.0, 1.0)
                return (p_clipped - target) ** 2

            grad = jax.grad(loss_magic)(param_magic)
            param_magic = param_magic - learning_rate * grad

        # Get final clipped values
        std_final = standard_clamp(param_std, 0.0, 1.0)
        magic_final = magic_clamp(param_magic, 0.0, 1.0)

        # Magic-clamp should make significantly more progress
        # Standard clipping gets stuck because gradients are zero when p < 0
        assert magic_final > std_final + 0.2
        assert magic_final > 0.6  # Made good progress toward target

    def test_optimization_convergence_comparison(self):
        """Compare convergence speed between standard and magic-clamp."""
        target = 0.7
        param_init = -0.5  # Start outside lower bound
        learning_rate = 0.05
        num_steps = 50

        # Track losses
        losses_std = []
        losses_magic = []

        # Standard clipping - will be stuck at 0.0 output
        param_std = param_init
        for _ in range(num_steps):
            def loss_std(p):
                p_clipped = standard_clamp(p, 0.0, 1.0)
                return (p_clipped - target) ** 2

            loss_val = loss_std(param_std)
            losses_std.append(float(loss_val))

            grad = jax.grad(loss_std)(param_std)
            param_std = param_std - learning_rate * grad

        # Magic-clamp - should converge
        param_magic = param_init
        for _ in range(num_steps):
            def loss_magic(p):
                p_clipped = magic_clamp(p, 0.0, 1.0)
                return (p_clipped - target) ** 2

            loss_val = loss_magic(param_magic)
            losses_magic.append(float(loss_val))

            grad = jax.grad(loss_magic)(param_magic)
            param_magic = param_magic - learning_rate * grad

        # Magic-clamp should converge much better
        final_loss_std = losses_std[-1]
        final_loss_magic = losses_magic[-1]

        # Standard gets stuck with high loss (clip(p) = 0, target = 0.7 → loss = 0.49)
        assert final_loss_std > 0.4

        # Magic-clamp converges
        assert final_loss_magic < final_loss_std
        assert final_loss_magic < 0.05  # Should be close to target

    @pytest.mark.slow
    def test_multiple_parameter_optimization(self):
        """Test optimization with multiple bounded parameters."""
        # Target: learn to output specific values for multiple parameters
        targets = jnp.array([0.2, 0.5, 0.8])
        params_init = jnp.array([-0.3, -0.2, 1.3])  # All starting outside bounds

        learning_rate = 0.03
        num_steps = 100

        # Magic-clamp optimization
        params = params_init
        for _ in range(num_steps):
            def loss(p):
                p_clipped = jax.vmap(lambda x: magic_clamp(x, 0.0, 1.0))(p)
                return jnp.sum((p_clipped - targets) ** 2)

            grad = jax.grad(loss)(params)
            params = params - learning_rate * grad

        final_values = jax.vmap(lambda x: magic_clamp(x, 0.0, 1.0))(params)

        # Should be close to targets
        assert jnp.allclose(final_values, targets, atol=0.1)
