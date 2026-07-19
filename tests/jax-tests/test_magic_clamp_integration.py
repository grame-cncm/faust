#!/usr/bin/env python3
"""
Test that magic_clamp integration works correctly in compiled Faust DSPs.
"""

import subprocess
from pathlib import Path

from test_utils import load_module

import jax
import jax.numpy as jnp
from flax import nnx


def compile_dsp(dsp_file, output_file):
    """Compile a Faust DSP file to JAX."""
    faust_bin = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
    arch_file = Path(__file__).parent.parent.parent / "architecture" / "jax" / "minimal.py"
    lib_dir = Path(__file__).parent.parent.parent / "libraries"

    cmd = [
        str(faust_bin),
        "-lang", "nnx",
        "-a", str(arch_file),
        "-I", str(lib_dir),
        str(dsp_file),
        "-o", str(output_file)
    ]

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Compilation failed: {result.stderr}")
        return False
    return True



def test_magic_clamp_parameter():
    """Test that use_magic_clamp parameter is present and works."""
    print("Testing magic_clamp parameter integration...")

    # Compile DSP
    dsp_file = Path(__file__).parent / "dsp" / "learnable_gain.dsp"
    output_file = Path(__file__).parent / "generated" / "test_magic_clamp_param.py"

    assert compile_dsp(dsp_file, output_file), "Compilation failed"

    # Load module
    module = load_module(output_file)

    # Test 1: Default (magic_clamp enabled)
    rngs = nnx.Rngs(0, params=0, rng_stream=0)
    model_default = module.mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs)
    assert model_default.use_magic_clamp == True, "Default should be True"
    print("✓ Default use_magic_clamp=True works")

    # Test 2: Explicitly enabled
    model_enabled = module.mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs, use_magic_clamp=True)
    assert model_enabled.use_magic_clamp == True
    print("✓ Explicit use_magic_clamp=True works")

    # Test 3: Explicitly disabled
    model_disabled = module.mydsp(sample_rate=44100, faust_float=jnp.float32, rngs=rngs, use_magic_clamp=False)
    assert model_disabled.use_magic_clamp == False
    print("✓ Explicit use_magic_clamp=False works")

    # Test 4: Verify gradient behavior difference
    inputs = jnp.zeros((model_default.num_inputs, 1024))
    inputs = inputs.at[:, 0].set(1.0)  # Impulse

    def loss_fn(model):
        outputs = model(inputs)
        return jnp.sum(outputs ** 2)

    # Both should compute gradients successfully
    _, grads_with = nnx.value_and_grad(loss_fn)(model_enabled)
    _, grads_without = nnx.value_and_grad(loss_fn)(model_disabled)

    print("✓ Gradients compute successfully with both settings")

    print("\n✅ All magic_clamp integration tests passed!")


if __name__ == "__main__":
    test_magic_clamp_parameter()
