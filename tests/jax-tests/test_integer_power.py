"""Integer powers must wrap in int32 before conversion to audio samples."""

from pathlib import Path
import subprocess

import jax
import jax.numpy as jnp
from flax import nnx
import numpy as np
import pytest

from test_utils import load_module


pytestmark = [pytest.mark.integration, pytest.mark.ci]
_REPO = Path(__file__).resolve().parents[2]


@pytest.fixture(scope="module", autouse=True)
def enable_x64():
    previous = jax.config.jax_enable_x64
    jax.config.update("jax_enable_x64", True)
    yield
    jax.config.update("jax_enable_x64", previous)


@pytest.mark.parametrize("backend", ["nnx", "linen"])
@pytest.mark.parametrize("precision", ["single", "double"])
@pytest.mark.parametrize("dsp_name", ["pow_int_float", "pow_float_int"])
def test_mixed_integer_and_float_power(
    faust_compiler, temp_output_dir, backend, precision, dsp_name
):
    arch_name = "minimal.py" if backend == "nnx" else "minimal_linen.py"
    output = temp_output_dir / "power.py"
    subprocess.run(
        [str(faust_compiler), "-lang", backend, "-" + precision,
         "-a", str(_REPO / "architecture/jax" / arch_name),
         "-o", str(output),
         str(_REPO / "tests/impulse-tests/dsp" / (dsp_name + ".dsp"))],
        check=True, capture_output=True, text=True,
    )
    dtype = jnp.float64 if precision == "double" else jnp.float32
    mydsp = load_module(output, module_name="integer_power").mydsp
    inputs = jnp.zeros((0, 16), dtype=dtype)
    if backend == "nnx":
        model = mydsp(sample_rate=44100, faust_float=dtype, rngs=nnx.Rngs(0))
        samples = nnx.jit(lambda m, x: m(x))(model, inputs)
    else:
        model = mydsp(sample_rate=44100, faust_float=dtype)
        variables = model.init(jax.random.key(0), inputs)
        samples = jax.jit(lambda v, x: model.apply(v, x))(variables, inputs)

    # 50000 squared wraps to -1794967296 in int32, while 0.6 squared is 0.36.
    expected = [-1794967296.0, 0.36]
    if dsp_name == "pow_float_int":
        expected.reverse()
    assert samples.shape == (2, 16)
    expected = np.broadcast_to(np.asarray(expected, dtype=np.dtype(dtype))[:, None], (2, 16))
    integer_channel = 0 if dsp_name == "pow_int_float" else 1
    np.testing.assert_array_equal(np.asarray(samples)[integer_channel], expected[integer_channel])
    np.testing.assert_allclose(np.asarray(samples), expected, rtol=1e-6, atol=1e-6)
