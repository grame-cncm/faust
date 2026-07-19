#!/usr/bin/env python3
"""
CI validation script for JAX backend tests.
Ensures critical features are working correctly.
"""

import subprocess
import sys
import tempfile
import os
from pathlib import Path

def test_random_generation():
    """Test that random_uniform foreign function works correctly."""
    print("Testing random_uniform foreign function...")

    # Create a test DSP
    dsp_code = """
import("stdfaust.lib");
random_uniform = ffunction(float random_uniform(), <math.h>, "");
process = random_uniform;
"""

    with tempfile.NamedTemporaryFile(mode='w', suffix='.dsp', delete=False) as f:
        f.write(dsp_code)
        dsp_path = f.name

    try:
        # Compile the DSP
        faust_bin = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
        arch_file = Path(__file__).parent.parent.parent / "architecture" / "jax" / "minimal.py"

        with tempfile.NamedTemporaryFile(suffix='.py', delete=False) as f:
            py_path = f.name

        libraries_path = Path(__file__).parent.parent.parent / "libraries"

        cmd = [
            str(faust_bin),
            "-lang", "nnx",
            "-a", str(arch_file),
            "-I", str(libraries_path),
            dsp_path,
            "-o", py_path
        ]

        result = subprocess.run(cmd, capture_output=True, text=True)
        assert result.returncode == 0, f"Compilation failed: {result.stderr}"

        # Test the generated code
        test_script = f"""
import sys
sys.path.insert(0, '{os.path.dirname(py_path)}')
import {Path(py_path).stem} as module
from jax import numpy as jnp, random
from flax import nnx

# Initialize model with proper RNG setup
rngs = nnx.Rngs(0, params=0, rng_stream=0)
model = module.mydsp(sample_rate=44100, rngs=rngs)

# Generate random values - for generators, use zero-channel input with desired length
length = 100
inputs = jnp.zeros((model.num_inputs, length))
output = model(inputs)

# Check that values are different and in range
unique_values = len(jnp.unique(output))
min_val = float(jnp.min(output))
max_val = float(jnp.max(output))

print(f"Unique values: {{unique_values}}/100")
print(f"Range: [{{min_val:.3f}}, {{max_val:.3f}}]")

# Validate - random_uniform outputs [0, 1] (standard uniform distribution)
assert unique_values > 50, f"Not enough unique values: {{unique_values}}"
assert 0.0 <= min_val <= 1.0, f"Min value out of range: {{min_val}}"
assert 0.0 <= max_val <= 1.0, f"Max value out of range: {{max_val}}"
print("✓ Random generation working correctly")
"""

        result = subprocess.run([sys.executable, "-c", test_script],
                              capture_output=True, text=True)

        assert result.returncode == 0, f"Test failed: {result.stderr}"

        print(result.stdout)

    finally:
        # Cleanup
        if 'dsp_path' in locals():
            os.unlink(dsp_path)
        if 'py_path' in locals():
            os.unlink(py_path)

def test_delay_optimization():
    """Test that delay line optimization works."""
    print("\nTesting delay line optimization...")
    
    # Create a simple delay test
    dsp_code = """
import("stdfaust.lib");
process = _ : @(100);
"""
    
    with tempfile.NamedTemporaryFile(mode='w', suffix='.dsp', delete=False) as f:
        f.write(dsp_code)
        dsp_path = f.name
    
    try:
        faust_bin = Path(__file__).parent.parent.parent / "build" / "bin" / "faust"
        
        results = {}
        for mcd in [8, 16, 64]:
            with tempfile.NamedTemporaryFile(suffix='.py', delete=False) as f:
                py_path = f.name
            
            libraries_path = Path(__file__).parent.parent.parent / "libraries"
            
            cmd = [
                str(faust_bin),
                "-lang", "nnx",
                "-mcd", str(mcd),
                "-I", str(libraries_path),
                dsp_path,
                "-o", py_path
            ]
            
            result = subprocess.run(cmd, capture_output=True, text=True)
            assert result.returncode == 0, f"Compilation with -mcd {mcd} failed: {result.stderr}"
            
            # Check implementation type
            with open(py_path, 'r') as f:
                content = f.read()
            
            if "jnp.roll" in content:
                impl_type = "roll"
            elif "IOTA" in content:
                impl_type = "circular"
            else:
                impl_type = "unknown"
            
            results[mcd] = impl_type
            os.unlink(py_path)
        
        print(f"Delay implementations by -mcd value:")
        for mcd, impl in results.items():
            print(f"  -mcd {mcd:3d}: {impl}")
        
        # Validate expected behavior (delay is 100 samples)
        # Delay > mcd should use circular buffer
        assert results[8] == "circular", f"Expected circular for -mcd 8 (100 > 8), got {results[8]}"
        assert results[16] == "circular", f"Expected circular for -mcd 16 (100 > 16), got {results[16]}"
        # With -mcd 64, delay is still > 64, so still circular
        assert results[64] == "circular", f"Expected circular for -mcd 64 (100 > 64), got {results[64]}"
        
        print("✓ Delay optimization working correctly")

    finally:
        if 'dsp_path' in locals():
            os.unlink(dsp_path)

def main():
    """Run all CI validation tests.

    Each test function asserts internally, so a failure raises and exits
    nonzero with a traceback.
    """
    print("="*60)
    print("JAX Backend CI Validation")
    print("="*60)

    test_random_generation()
    test_delay_optimization()

    print("\n" + "="*60)
    print("✅ All CI validation tests passed")
    return 0

if __name__ == "__main__":
    sys.exit(main())