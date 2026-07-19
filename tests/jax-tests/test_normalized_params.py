"""
Test normalized_params argument - designed for RL/neural network policies.

RL policies typically output parameters in [0, 1] using Beta distribution.
The normalized_params argument allows using these directly without manual unnormalization.
"""

import jax
from jax import numpy as jnp
from flax import nnx
import subprocess
from pathlib import Path

from test_utils import load_module


def compile_my_example():
    """Compile my_example.dsp"""
    faust_bin = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
    arch_file = Path(__file__).parent.parent.parent / "architecture" / "jax" / "minimal.py"
    lib_dir = Path(__file__).parent.parent.parent / "libraries"
    dsp_file = Path(__file__).parent / "dsp" / "my_example.dsp"
    output_file = Path(__file__).parent / "my_example.py"

    cmd = [str(faust_bin), "-lang", "nnx", "-a", str(arch_file),
           "-I", str(lib_dir), str(dsp_file), "-o", str(output_file)]

    subprocess.run(cmd, capture_output=True, check=True)

    return load_module(output_file, "my_example").mydsp


def test_normalized_params_single():
    """Test using normalized_params for single inference."""
    print("\n" + "="*60)
    print("Test 1: Normalized Params (Single Inference)")
    print("="*60)

    mydsp = compile_my_example()
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Simulate RL policy output (Beta distribution in [0, 1])
    normalized_from_policy = {
        'fHslider0': jnp.array(0.3),  # cutoff (normalized)
        'fHslider1': jnp.array(0.7),  # gain (normalized)
        'fHslider2': jnp.array(0.5),  # freq (normalized)
    }

    print(f"Normalized params (from RL policy): {normalized_from_policy}")

    # Use normalized_params argument
    inputs = jnp.ones((model.num_inputs, 1024))
    outputs = model(inputs, normalized_params=normalized_from_policy)

    print(f"Output shape: {outputs.shape}")
    print(f"Output mean: {float(jnp.mean(outputs)):.6f}")
    print("✓ normalized_params works for RL policy integration!")


def test_normalized_params_vmap():
    """Test vmap with normalized_params - THE RL USE CASE!"""
    print("\n" + "="*60)
    print("Test 2: Normalized Params with vmap (RL Batch Inference)")
    print("="*60)

    mydsp = compile_my_example()
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    batch_size = 4

    # Simulate RL policy outputting Beta(2, 2) distribution for each parameter
    key = jax.random.key(42)
    normalized_batch = {}

    # Get parameter names
    default_normalized = model.get_continuous_params()
    print(f"Parameter zones: {list(default_normalized.keys())}")

    # Simulate policy output for batch
    for zone in default_normalized.keys():
        # Beta(2, 2) distribution - common in RL for bounded actions
        key, subkey = jax.random.split(key)
        normalized_batch[zone] = jax.random.beta(subkey, a=2.0, b=2.0, shape=(batch_size,))

    print(f"\nNormalized params from policy (batch):")
    for key in normalized_batch:
        print(f"  {key}: {normalized_batch[key]}")

    # Prepare batched inputs
    inputs_batch = jnp.ones((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(0), batch_size)

    # SIMPLE VMAP with normalized_params
    @jax.vmap
    def render_batch(normalized_dict, inp, rng):
        return model(inp, normalized_params=normalized_dict, rngs=rng)

    outputs_batch = render_batch(normalized_batch, inputs_batch, rngs_batch)

    print(f"\nOutput shape: {outputs_batch.shape}")
    print(f"Output means: {[float(jnp.mean(outputs_batch[i])) for i in range(batch_size)]}")

    # Verify outputs are different (different params should produce different audio)
    all_same = all(jnp.allclose(outputs_batch[0], outputs_batch[i]) for i in range(1, batch_size))
    print(f"All outputs identical: {all_same} (should be False)")
    assert not all_same, "Expected different outputs for different parameters!"

    print("\n✓ Perfect for RL: policy outputs [0, 1] → Faust automatically unnormalizes!")


def test_get_default_params_normalized():
    """Test get_continuous_params helper with normalized flag."""
    print("\n" + "="*60)
    print("Test 3: get_continuous_params() Helper")
    print("="*60)

    mydsp = compile_my_example()
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Get physical values
    physical = model.get_continuous_params(normalized=False)
    print("Physical values (unnormalized):")
    for key, val in physical.items():
        print(f"  {key}: {float(val):.2f}")

    # Get normalized values (default)
    normalized = model.get_continuous_params()  # normalized=True is default
    print("\nNormalized values [0, 1] (default):")
    for key, val in normalized.items():
        print(f"  {key}: {float(val):.4f}")

    # Get batched normalized values (what RL policy should output)
    batch_size = 4
    normalized_batch = model.get_continuous_params(batch_size=batch_size)
    print(f"\nBatched normalized (for RL vmap):")
    for key, val in normalized_batch.items():
        print(f"  {key}: {val}")

    print("\n✓ Helper methods make RL integration easy!")


def test_params_vs_normalized_params():
    """Test that params and normalized_params are mutually exclusive."""
    print("\n" + "="*60)
    print("Test 4: Mutual Exclusion (params vs normalized_params)")
    print("="*60)

    mydsp = compile_my_example()
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    inputs = jnp.ones((model.num_inputs, 1024))

    physical = model.unnormalize()  # Get physical values
    normalized = model.get_continuous_params()  # Get normalized values (default)

    # Should raise error if both provided
    try:
        outputs = model(inputs, params=physical, normalized_params=normalized)
        assert False, "Should have raised error!"
    except ValueError as e:
        print(f"✓ Correctly raises error: {e}")
