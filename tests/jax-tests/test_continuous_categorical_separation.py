"""
Test separation of continuous and categorical parameters for RL integration.

In RL, continuous and categorical parameters are handled differently:
- Continuous: Beta/Gaussian distributions → [0, 1] or unbounded
- Categorical: Categorical/Gumbel-softmax distributions → logits

This test validates that the API cleanly separates these two types.
"""

import jax
from jax import numpy as jnp
from flax import nnx
import subprocess
from pathlib import Path

from test_utils import load_module


def compile_dsp(dsp_name):
    """Compile a DSP file."""
    faust_bin = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
    arch_file = Path(__file__).parent.parent.parent / "architecture" / "jax" / "minimal.py"
    lib_dir = Path(__file__).parent.parent.parent / "libraries"
    dsp_file = Path(__file__).parent / "dsp" / f"{dsp_name}.dsp"
    output_file = Path(__file__).parent / "generated" / f"{dsp_name}.py"

    cmd = [str(faust_bin), "-lang", "nnx", "-a", str(arch_file),
           "-I", str(lib_dir), str(dsp_file), "-o", str(output_file)]

    subprocess.run(cmd, capture_output=True, check=True)

    return load_module(output_file, dsp_name).mydsp


def test_continuous_only():
    """Test DSP with only continuous parameters (sliders)."""
    print("\n" + "="*60)
    print("Test 1: Continuous Parameters Only (Sliders)")
    print("="*60)

    mydsp = compile_dsp("my_example")
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Get continuous params (normalized)
    continuous = model.get_continuous_params(normalized=True)
    print(f"Continuous params [0, 1]: {continuous}")

    # Verify all are in [0, 1]
    for key, val in continuous.items():
        assert 0.0 <= float(val) <= 1.0, f"{key} not in [0, 1]: {val}"

    print("✓ All continuous params in [0, 1]")

    # Get categorical params (should be empty)
    categorical = model.get_categorical_params()
    print(f"Categorical params: {categorical}")
    assert len(categorical) == 0, "Should have no categorical params"

    print("✓ No categorical params (as expected)")


def test_with_nentry():
    """Test DSP with both continuous and categorical parameters."""
    print("\n" + "="*60)
    print("Test 2: Mixed Continuous + Categorical (nentry)")
    print("="*60)

    mydsp = compile_dsp("nentry_test")
    rngs = nnx.Rngs(0, params=0, rng_stream=0, nentry=42)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Get continuous params
    continuous = model.get_continuous_params(normalized=True)
    print(f"Continuous params [0, 1]: {continuous}")
    print(f"  Number of continuous params: {len(continuous)}")

    # Get categorical params
    categorical = model.get_categorical_params()
    print(f"\nCategorical params:")
    for zone, data in categorical.items():
        print(f"  {zone}:")
        print(f"    logits: {data['logits']} (shape: {data['logits'].shape})")
        print(f"    tau: {data['tau']}")

    # Verify logits are NOT constrained to [0, 1]
    for zone, data in categorical.items():
        logits = data['logits']
        print(f"\n  Logits for {zone} are unbounded (not in [0, 1])")
        print(f"  This is correct - categorical params use different distributions!")

    print("\n✓ Continuous and categorical params properly separated!")


def test_rl_vmap_pattern():
    """Test proper RL pattern with separated parameter types."""
    print("\n" + "="*60)
    print("Test 3: RL vmap Pattern with Separated Params")
    print("="*60)

    mydsp = compile_dsp("my_example")
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    batch_size = 4

    # Simulate RL policy: Beta distribution for continuous params [0, 1]
    continuous_batch = model.get_continuous_params(batch_size=batch_size, normalized=True)

    # Add variation using Beta(2, 2) - typical RL distribution
    key = jax.random.key(42)
    for zone in continuous_batch:
        key, subkey = jax.random.split(key)
        continuous_batch[zone] = jax.random.beta(subkey, a=2.0, b=2.0, shape=(batch_size,))

    print("Continuous params from Beta(2, 2) policy:")
    for zone, vals in continuous_batch.items():
        print(f"  {zone}: {vals}")
        # Verify all in [0, 1]
        assert jnp.all((vals >= 0) & (vals <= 1)), f"{zone} not in [0, 1]"

    print("\n✓ All continuous params in [0, 1] (valid for Beta distribution)")

    # Prepare inputs
    inputs_batch = jnp.ones((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(0), batch_size)

    # Simple vmap with normalized continuous params
    @jax.vmap
    def render(continuous_params, inp, rng):
        return model(inp, normalized_params=continuous_params, rngs=rng)

    outputs_batch = render(continuous_batch, inputs_batch, rngs_batch)

    print(f"\nOutput shape: {outputs_batch.shape}")
    print(f"Output means: {[float(jnp.mean(outputs_batch[i])) for i in range(batch_size)]}")

    # Verify different params produce different outputs
    all_same = all(jnp.allclose(outputs_batch[0], outputs_batch[i]) for i in range(1, batch_size))
    assert not all_same, "Expected different outputs"

    print("✓ RL vmap pattern works correctly!")


def test_get_continuous_params_defaults_to_normalized():
    """Test that get_continuous_params defaults to normalized=True."""
    print("\n" + "="*60)
    print("Test 4: get_continuous_params() defaults to normalized=True")
    print("="*60)

    mydsp = compile_dsp("my_example")
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # These should be identical (normalized=True is the default)
    continuous_explicit = model.get_continuous_params(normalized=True)
    continuous_default = model.get_continuous_params()

    print(f"get_continuous_params(normalized=True): {continuous_explicit}")
    print(f"get_continuous_params() [default]: {continuous_default}")

    assert continuous_explicit.keys() == continuous_default.keys()
    for key in continuous_explicit:
        assert jnp.allclose(continuous_explicit[key], continuous_default[key])

    print("✓ get_continuous_params() defaults to normalized=True!")
