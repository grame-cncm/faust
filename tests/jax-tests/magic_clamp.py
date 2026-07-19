"""
Magic-clamp: Conditional Straight-Through Estimator for parameter constraints.

This implements a gradient-aware clipping function that improves optimization
convergence when parameters frequently hit their bounds.

Standard clipping:
- Forward: clip(x, min, max)
- Backward: gradient is 0 when outside bounds

Magic-clamp (conditional STE):
- Forward: clip(x, min, max)
- Backward: gradient flows when moving TOWARD valid region, 0 when moving AWAY
"""

import jax
import jax.numpy as jnp


@jax.custom_vjp
def magic_clamp(x, min_val=0.0, max_val=1.0):
    """
    Clip with conditional straight-through estimator.

    Args:
        x: Value to clip
        min_val: Minimum value
        max_val: Maximum value

    Returns:
        Clipped value

    Gradient behavior:
        - Inside bounds: gradient flows normally
        - At/beyond lower bound with positive gradient: gradient flows (moving toward valid)
        - At/beyond lower bound with negative gradient: gradient is 0 (moving further out)
        - At/beyond upper bound with negative gradient: gradient flows (moving toward valid)
        - At/beyond upper bound with positive gradient: gradient is 0 (moving further out)
    """
    return jnp.clip(x, min_val, max_val)


def magic_clamp_fwd(x, min_val=0.0, max_val=1.0):
    """Forward pass: standard clipping."""
    y = jnp.clip(x, min_val, max_val)
    return y, (x, min_val, max_val)


def magic_clamp_bwd(res, g):
    """
    Backward pass: conditional straight-through estimator.

    Pass gradients when moving toward valid region, zero when moving away.

    Note: Gradient g is dL/d(clip(x)). Parameter update is x_new = x - lr * g.
    - If x > max and g > 0: update moves x toward bounds (x - lr*g moves left). ALLOW.
    - If x > max and g < 0: update moves x away from bounds (x - lr*g moves right). BLOCK.
    - If x < min and g > 0: update moves x away from bounds (x - lr*g moves left). BLOCK.
    - If x < min and g < 0: update moves x toward bounds (x - lr*g moves right). ALLOW.
    """
    x, min_val, max_val = res

    grad_x = jnp.where(
        # Block gradients when update would move further out of bounds
        ((x < min_val) & (g > 0)) | ((x > max_val) & (g < 0)),
        0.0,  # Zero gradient
        g     # Pass gradient through
    )

    return (grad_x, None, None)


# Register custom VJP
magic_clamp.defvjp(magic_clamp_fwd, magic_clamp_bwd)


def standard_clamp(x, min_val=0.0, max_val=1.0):
    """
    Standard JAX clipping for comparison.

    Gradient behavior:
        - Inside bounds: gradient flows
        - Outside bounds: gradient is 0
    """
    return jnp.clip(x, min_val, max_val)


def compare_clipping_gradients(x_values, min_val=0.0, max_val=1.0):
    """
    Compare gradient behavior between standard clipping and magic-clamp.

    Args:
        x_values: Array of x values to test
        min_val: Minimum bound
        max_val: Maximum bound

    Returns:
        Dictionary with comparison results
    """
    results = {
        'x': x_values,
        'standard_grad': [],
        'magic_clamp_grad': [],
    }

    for x in x_values:
        # Standard clipping gradient
        grad_std = jax.grad(lambda x: standard_clamp(x, min_val, max_val))(x)
        results['standard_grad'].append(float(grad_std))

        # Magic-clamp gradient
        grad_magic = jax.grad(lambda x: magic_clamp(x, min_val, max_val))(x)
        results['magic_clamp_grad'].append(float(grad_magic))

    return results
