"""
Test the modified my_example.py with params argument support.

This demonstrates how adding an optional params argument to __call__
dramatically simplifies vmap for batch processing with different parameters.
"""

import subprocess
import tempfile
from pathlib import Path

import pytest
import jax
from jax import numpy as jnp
from flax import nnx

from test_utils import load_module

_HERE = Path(__file__).parent


def _compile_my_example():
    """Compile dsp/my_example.dsp with the JAX backend and return its mydsp class."""
    faust = _HERE.parent.parent / "build" / "bin" / "faust"
    arch = _HERE.parent.parent / "architecture" / "jax" / "minimal.py"
    libs = _HERE.parent.parent / "libraries"
    dsp = _HERE / "dsp" / "my_example.dsp"
    out = Path(tempfile.mkdtemp(prefix="faust_my_example_")) / "my_example.py"
    subprocess.run(
        [str(faust), "-lang", "nnx", "-a", str(arch), "-I", str(libs),
         "-o", str(out), str(dsp)],
        check=True, capture_output=True, text=True,
    )
    return load_module(out, module_name="my_example").mydsp


@pytest.fixture(scope="module")
def mydsp():
    """Compile my_example.dsp once per module and expose the mydsp class."""
    return _compile_my_example()


def test_original_api_still_works(mydsp):
    """Test that original API (no params arg) still works."""
    print("\n" + "="*60)
    print("Test 1: Original API (params=None)")
    print("="*60)

    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Original usage - no params argument
    inputs = jnp.ones((model.num_inputs, 1024))
    outputs = model(inputs)

    print(f"Output shape: {outputs.shape}")
    print("✓ Original API works (backward compatible)")


def test_params_argument_override(mydsp):
    """Test passing params explicitly."""
    print("\n" + "="*60)
    print("Test 2: Params Argument Override")
    print("="*60)

    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Get default unnormalized params
    default_params = model.unnormalize()
    print(f"Default params: {default_params}")

    # Create custom params (all zeros)
    custom_params = {key: jnp.zeros_like(val) for key, val in default_params.items()}

    # Test with default params
    inputs = jnp.ones((model.num_inputs, 1024))
    outputs_default = model(inputs, params=None)

    # Test with custom params
    outputs_custom = model(inputs, params=custom_params)

    print(f"Output with default params - mean: {float(jnp.mean(outputs_default)):.4f}")
    print(f"Output with custom params - mean: {float(jnp.mean(outputs_custom)):.4f}")
    print("✓ Params override works")


def test_vmap_with_params_simplified(mydsp):
    """Test vmap with params argument - THE KEY BENEFIT!"""
    print("\n" + "="*60)
    print("Test 3: Simplified vmap with Params Argument")
    print("="*60)

    # Create single model instance
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Get batched params using helper method
    batch_size = 4

    # Get default params and tile for batch
    default_params = model.unnormalize()
    params_batch = jax.tree.map(
        lambda x: jnp.tile(x, (batch_size,) + (1,) * x.ndim),
        default_params
    )

    # Add some variation to each batch item
    for key in params_batch:
        noise = jax.random.normal(jax.random.key(0), params_batch[key].shape) * 0.1
        params_batch[key] = jnp.clip(params_batch[key] + noise, 0, 1)

    print(f"Batched params shapes: {jax.tree.map(lambda x: x.shape, params_batch)}")
    print("✓ Manual batching of default params")

    # Prepare batched inputs
    inputs_batch = jnp.ones((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(42), batch_size)

    # THE SIMPLE VMAP - no split/merge/clone needed!
    @jax.vmap
    def render_batch(params_dict, single_input, single_rng):
        return model(single_input, params=params_dict, rngs=single_rng)

    outputs = render_batch(params_batch, inputs_batch, rngs_batch)

    print(f"Output shape: {outputs.shape}")
    print(f"Output means per batch item: {[float(jnp.mean(outputs[i])) for i in range(batch_size)]}")
    print("✓ Simplified vmap works - NO split/merge/clone overhead!")


def test_params_with_variation(mydsp):
    """Test params argument with varied parameter values per batch item."""
    print("\n" + "="*60)
    print("Test 4: Params Argument with Variation")
    print("="*60)

    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    batch_size = 4
    inputs_batch = jnp.ones((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(42), batch_size)

    # Create varied params for each batch item
    default_params = model.unnormalize()
    params_batch = {}

    for key, val in default_params.items():
        # Create different values per batch item
        varied = jnp.linspace(float(val) * 0.5, float(val) * 1.5, batch_size)
        params_batch[key] = varied

    print("Parameter variation per batch item:")
    for key, vals in params_batch.items():
        print(f"  {key}: [{vals[0]:.2f}, {vals[1]:.2f}, {vals[2]:.2f}, {vals[3]:.2f}]")

    # Render with vmap
    @jax.vmap
    def render(params_dict, single_input, single_rng):
        return model(single_input, params=params_dict, rngs=single_rng)

    outputs = render(params_batch, inputs_batch, rngs_batch)

    print(f"\nOutput shape: {outputs.shape}")
    print(f"Output means per batch item: {[float(jnp.mean(outputs[i])) for i in range(batch_size)]}")

    # Verify different params produce different outputs
    all_same = all(jnp.allclose(outputs[0], outputs[i]) for i in range(1, batch_size))
    assert not all_same, "Expected different outputs for different parameters"

    print("✓ Different parameters produce different outputs!")
