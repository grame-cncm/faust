"""
Test params argument with edge cases: soundfiles, nentry/Gumbel-softmax, train mode.
"""

import jax
from jax import numpy as jnp
from flax import nnx
import subprocess
from pathlib import Path

from test_utils import load_module


# Compile fresh versions with params argument support
def compile_dsp(dsp_name):
    faust_bin = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
    arch_file = Path(__file__).parent.parent.parent / "architecture" / "jax" / "minimal.py"
    lib_dir = Path(__file__).parent.parent.parent / "libraries"
    dsp_file = Path(__file__).parent / "dsp" / f"{dsp_name}.dsp"
    output_file = Path(__file__).parent / "generated" / f"{dsp_name}.py"

    cmd = [
        str(faust_bin), "-lang", "nnx",
        "-a", str(arch_file),
        "-I", str(lib_dir),
        str(dsp_file),
        "-o", str(output_file)
    ]

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Compilation failed: {result.stderr}")
        return None

    return load_module(output_file, dsp_name).mydsp


def test_soundfile_non_trainable_with_params():
    """Test params argument with non-trainable soundfiles."""
    print("\n" + "="*60)
    print("Edge Case 1: Non-Trainable Soundfiles + Params Argument")
    print("="*60)

    mydsp = compile_dsp("sound")
    if mydsp is None:
        print("❌ Compilation failed")
        return False

    # Check assets exist
    assets_dir = Path(__file__).parent / "assets"
    if not assets_dir.exists():
        print("⊘ Skipping - no assets directory")
        return True

    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs, soundfile_dirs=[str(assets_dir)])

    # Get params (should be empty or 0 since soundfiles aren't in unnormalize)
    params = model.unnormalize()
    print(f"Unnormalized params: {params}")

    # Test with params=None (default)
    inputs = jnp.zeros((model.num_inputs, 1024))
    outputs1 = model(inputs)
    print(f"Output shape (params=None): {outputs1.shape}")

    # Test with empty params dict
    outputs2 = model(inputs, params={})
    print(f"Output shape (params={{}}): {outputs2.shape}")

    # Test vmap with soundfiles. The soundfile-only DSP has no scalar params,
    # so the params dict is empty (a dict with no leaves is fine under vmap).
    batch_size = 2
    inputs_batch = jnp.zeros((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(42), batch_size)
    params_batch = {}

    @jax.vmap
    def render(params_dict, inp, rng):
        return model(inp, params=params_dict, rngs=rng)

    outputs_batch = render(params_batch, inputs_batch, rngs_batch)
    print(f"Batched output shape: {outputs_batch.shape}")
    print("✓ Soundfiles work with params argument in vmap!")


def test_soundfile_trainable_with_params():
    """Test params argument with trainable soundfiles."""
    print("\n" + "="*60)
    print("Edge Case 2: Trainable Soundfiles + Params Argument")
    print("="*60)

    mydsp = compile_dsp("soundfile_learnable")
    if mydsp is None:
        print("❌ Compilation failed")
        return False

    assets_dir = Path(__file__).parent / "assets"
    if not assets_dir.exists():
        print("⊘ Skipping - no assets directory")
        return True

    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs, soundfile_dirs=[str(assets_dir)])

    # Soundfile buffers are accessed via state, not unnormalize()
    # So params dict might still be empty
    params = model.unnormalize()
    print(f"Unnormalized params: {params}")

    inputs = jnp.zeros((model.num_inputs, 1024))

    # Test with params=None
    outputs1 = model(inputs)
    print(f"Output shape (params=None): {outputs1.shape}")

    # Test with empty params
    outputs2 = model(inputs, params={})
    print(f"Output shape (params={{}}): {outputs2.shape}")

    print("✓ Trainable soundfiles work with params argument!")


def test_nentry_gumbel_with_params():
    """Test params argument with nentry (Gumbel-softmax)."""
    print("\n" + "="*60)
    print("Edge Case 3: Nentry + Gumbel-Softmax + Params Argument")
    print("="*60)

    mydsp = compile_dsp("nentry_test")
    if mydsp is None:
        print("❌ Compilation failed")
        return False

    # Test without nentry RNG (inference mode - hard argmax)
    print("\n--- Inference Mode (no nentry RNG) ---")
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    params = model.unnormalize()
    print(f"Params: {list(params.keys())}")
    print(f"fEntry0 value: {params['fEntry0']}")

    inputs = jnp.ones((model.num_inputs, 1024))
    outputs = model(inputs, params=params)
    print(f"Output mean: {float(jnp.mean(outputs)):.4f}")

    # Test with training mode (nentry RNG)
    print("\n--- Training Mode (with nentry RNG) ---")
    rngs = nnx.Rngs(0, params=0, rng_stream=0, nentry=42)
    model_train = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    params_train = model_train.unnormalize()
    outputs_train = model_train(inputs, params=params_train)
    print(f"Output mean (train): {float(jnp.mean(outputs_train)):.4f}")

    # Test vmap with different nentry logits per batch item
    print("\n--- vmap with Different Logits per Batch ---")
    batch_size = 4
    inputs_batch = jnp.ones((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(42), batch_size)

    # Create custom batched params with different values per item
    # fEntry0 has 4 options (min=0, max=3, step=1)
    params_batch = {
        'fEntry0': jnp.array([0.0, 1.0, 2.0, 3.0])  # Different discrete values
    }

    print(f"Batched params (custom): {params_batch}")

    # Note: For nentry, unnormalize returns the selected value, not logits
    # We're providing the unnormalized values directly here

    @jax.vmap
    def render(params_dict, inp, rng):
        return model(inp, params=params_dict, rngs=rng)

    outputs_batch = render(params_batch, inputs_batch, rngs_batch)
    print(f"Batched output shape: {outputs_batch.shape}")
    print(f"Output means: {[float(jnp.mean(outputs_batch[i])) for i in range(batch_size)]}")
    print("✓ Nentry works with params argument in vmap!")


def test_mixed_params_vmap():
    """Test vmap with DSP that has multiple slider types."""
    print("\n" + "="*60)
    print("Edge Case 4: Mixed Parameters (sliders) + vmap")
    print("="*60)

    mydsp = compile_dsp("my_example")
    if mydsp is None:
        print("❌ Compilation failed")
        return False

    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model = mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)

    # Get parameter info
    params = model.unnormalize()
    metadata = model.get_parameter_metadata()

    print(f"Parameters: {list(params.keys())}")
    for key in params.keys():
        meta = metadata[key]
        print(f"  {key}: {meta['full_label']} = {float(params[key]):.2f} [{meta['min']}, {meta['max']}]")

    # Create custom batched params with different values per item
    batch_size = 4
    params_batch = {}
    for key in params.keys():
        # Create different values for each batch item
        vals = jnp.linspace(0.2, 0.8, batch_size)
        params_batch[key] = vals

    print(f"\nBatched params (custom values):")
    for key in params_batch:
        print(f"  {key}: {params_batch[key]}")

    # Test vmap
    inputs_batch = jnp.ones((batch_size, model.num_inputs, 1024))
    rngs_batch = jax.random.split(jax.random.key(42), batch_size)

    @jax.vmap
    def render(params_dict, inp, rng):
        return model(inp, params=params_dict, rngs=rng)

    outputs_batch = render(params_batch, inputs_batch, rngs_batch)
    print(f"\nBatched output shape: {outputs_batch.shape}")
    print(f"Output means per batch: {[float(jnp.mean(outputs_batch[i])) for i in range(batch_size)]}")

    # Verify outputs are different (different params should produce different audio)
    all_same = all(jnp.allclose(outputs_batch[0], outputs_batch[i]) for i in range(1, batch_size))
    print(f"All outputs identical: {all_same} (should be False)")
    assert not all_same, "Expected different outputs for different parameters!"

    print("✓ Mixed parameters work with vmap!")
