#!/usr/bin/env python3
"""
Test script for JAX random_uniform foreign function feature.
This verifies that the random generation produces proper random values
using JAX's PRNG system and that stereo channels are independent.
"""

import subprocess
import sys
import os
from os import environ
environ["JAX_PLATFORM_NAME"] = "cpu"
environ["CUDA_VISIBLE_DEVICES"] = ""
environ["JAX_PLATFORMS"] = "cpu"

import jax
from jax import numpy as jnp, random
from flax import nnx
import numpy as np

# Import the generated module - determine which test we're running
script_dir = os.path.dirname(os.path.abspath(__file__))
generated_path = os.path.join(script_dir, 'generated')
sys.path.insert(0, generated_path)

# The Makefile compiles dsp/random_test.dsp (or random_uniform.dsp) into
# generated/ before running this script. When run standalone (e.g. by pytest),
# compile random_test.dsp on demand so the test is self-contained.
if not (os.path.exists(os.path.join(generated_path, 'random_test.py'))
        or os.path.exists(os.path.join(generated_path, 'random_uniform.py'))):
    os.makedirs(generated_path, exist_ok=True)
    repo_root = os.path.join(script_dir, '..', '..')
    subprocess.run(
        [
            os.path.join(repo_root, 'build', 'bin', 'faust'),
            '-lang', 'nnx',
            '-a', os.path.join(repo_root, 'architecture', 'jax', 'minimal.py'),
            '-I', os.path.join(repo_root, 'libraries'),
            os.path.join(script_dir, 'dsp', 'random_test.dsp'),
            '-o', os.path.join(generated_path, 'random_test.py'),
        ],
        check=True,
    )

# The Makefile passes the DSP under test (random_test or random_uniform) as
# argv[1]; without it (e.g. under pytest, whose argv holds pytest options)
# fall back to whichever generated module exists, preferring random_test.
if len(sys.argv) > 1 and sys.argv[1] in ("random_test", "random_uniform"):
    import importlib
    test_name = sys.argv[1]
    random_module = importlib.import_module(test_name)
elif os.path.exists(os.path.join(generated_path, 'random_test.py')):
    import random_test as random_module
    test_name = "random_test"
elif os.path.exists(os.path.join(generated_path, 'random_uniform.py')):
    import random_uniform as random_module
    test_name = "random_uniform"
else:
    raise ImportError(f"No random test module found in {generated_path}")


def test_random():
    """Test that random_uniform produces proper random values."""

    # Initialize with RNG
    rngs = nnx.Rngs(0, params=42, rng_stream=1337)

    # Create DSP instance
    dsp = random_module.mydsp(sample_rate=44100, rngs=rngs)

    # Check number of channels
    assert dsp.num_inputs == 0, f"Expected 0 inputs, got {dsp.num_inputs}"
    assert dsp.num_outputs in [1, 2], f"Expected 1 or 2 outputs, got {dsp.num_outputs}"

    is_stereo = dsp.num_outputs == 2

    # Generate samples to test randomness
    carry = dsp.initialize_carry()
    block_size = 1024
    inputs = jnp.zeros((dsp.num_inputs, block_size))

    # Collect samples
    values_ch0 = []
    values_ch1 = [] if is_stereo else None

    num_samples = 100
    for i in range(num_samples):
        # unroll and rngs are keyword-only; process_block returns carry first
        carry, outputs = dsp.process_block(carry, inputs, unroll=1, rngs=rngs())
        values_ch0.append(float(outputs[0, 0]))
        if is_stereo:
            values_ch1.append(float(outputs[1, 0]))

    # Test 1: Values should be different over time (random)
    unique_ch0 = len(set(values_ch0))
    assert unique_ch0 > 90, f"Channel 0 has only {unique_ch0} unique values out of {num_samples}"

    if is_stereo:
        unique_ch1 = len(set(values_ch1))
        assert unique_ch1 > 90, f"Channel 1 has only {unique_ch1} unique values out of {num_samples}"

    # Test 2: For stereo, channels should be independent
    if is_stereo:
        identical_count = sum(1 for v0, v1 in zip(values_ch0, values_ch1) if v0 == v1)
        assert identical_count < 10, f"Channels have {identical_count} identical values, should be independent"

    # Test 3: Values should be in range [0, 1]
    min_ch0, max_ch0 = min(values_ch0), max(values_ch0)
    assert 0.0 <= min_ch0 <= 1.0, f"Channel 0 min value {min_ch0} out of range"
    assert 0.0 <= max_ch0 <= 1.0, f"Channel 0 max value {max_ch0} out of range"

    if is_stereo:
        min_ch1, max_ch1 = min(values_ch1), max(values_ch1)
        assert 0.0 <= min_ch1 <= 1.0, f"Channel 1 min value {min_ch1} out of range"
        assert 0.0 <= max_ch1 <= 1.0, f"Channel 1 max value {max_ch1} out of range"

    # Test 4: Distribution should be roughly uniform
    # Check that values span a good range (at least 50% of [0, 1])
    range_ch0 = max_ch0 - min_ch0
    assert range_ch0 > 0.5, f"Channel 0 range {range_ch0} is too narrow"

    if is_stereo:
        range_ch1 = max_ch1 - min_ch1
        assert range_ch1 > 0.5, f"Channel 1 range {range_ch1} is too narrow"

    # Test 5: Check mean is roughly 0.5 (for uniform distribution in [0, 1])
    mean_ch0 = np.mean(values_ch0)
    assert 0.3 < mean_ch0 < 0.7, f"Channel 0 mean {mean_ch0} is too far from 0.5"

    if is_stereo:
        mean_ch1 = np.mean(values_ch1)
        assert 0.3 < mean_ch1 < 0.7, f"Channel 1 mean {mean_ch1} is too far from 0.5"

    # Print results
    print(f"✅ All random_uniform tests passed for {test_name} ({'stereo' if is_stereo else 'mono'})!")
    print(f"  - Generated {unique_ch0}/{num_samples} unique values on channel 0")
    print(f"  - Range ch0: [{min_ch0:.3f}, {max_ch0:.3f}]")
    print(f"  - Mean ch0: {mean_ch0:.3f}")

    if is_stereo:
        print(f"  - Generated {unique_ch1}/{num_samples} unique values on channel 1")
        print(f"  - Range ch1: [{min_ch1:.3f}, {max_ch1:.3f}]")
        print(f"  - Mean ch1: {mean_ch1:.3f}")
        print(f"  - Channels are independent (only {identical_count} identical values)")


if __name__ == "__main__":
    # An uncaught exception exits nonzero with a traceback, which is what the
    # Makefile checks for.
    test_random()
