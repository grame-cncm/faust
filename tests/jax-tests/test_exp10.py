"""Execute base-10 powers and table initialization in both Flax backends."""

import subprocess

import jax
import jax.numpy as jnp
import numpy as np
import pytest
from flax import nnx

from test_utils import load_module


pytestmark = [pytest.mark.integration, pytest.mark.ci]


@pytest.fixture(scope="module", autouse=True)
def enable_x64():
    previous = jax.config.jax_enable_x64
    jax.config.update("jax_enable_x64", True)
    yield
    jax.config.update("jax_enable_x64", previous)


@pytest.mark.parametrize("backend", ["nnx", "linen"])
@pytest.mark.parametrize("precision", ["single", "double"])
@pytest.mark.parametrize("sample_rate", [44100, 48000])
@pytest.mark.parametrize("case", [
    "constant_table", "constant_table_native", "dynamic_table",
    "table_sample_rate", "table_sample_rate_native", "carry", "tick", "mixed",
])
def test_exp10_execution(
    faust_compiler, jax_architecture_dir, jax_library_dir, tmp_path,
    backend, precision, sample_rate, case,
):
    dtype = jnp.float64 if precision == "double" else jnp.float32
    powers = np.power(10.0, np.asarray([-2.0, -0.5, 0.0, 1.0, 2.0]))
    rate_power = 10.0 ** (sample_rate / 44100.0)
    cases = {
        # Exact reproducer from PR #1331: the first table entry is 10.
        "constant_table": ("rdtable(10, pow(10, +(1)~_), 0)", [], 10.0),
        "constant_table_native": (
            "rdtable(4, pow(10.0, float(+(1)~_)), 0)", [], 10.0),
        "dynamic_table": (
            "rdtable(4, pow(10, +(1)~_), int(_))", [0, 1, 2, 3],
            np.power(10.0, np.arange(1, 5))),
        "table_sample_rate": (
            "rdtable(4, pow(10, float(ma.SR)/44100) + float(+(1)~_), 0)",
            [], rate_power + 1.0),
        "table_sample_rate_native": (
            "rdtable(4, float(ma.SR) + float(+(1)~_), 0)", [], sample_rate + 1.0),
        "carry": ("pow(10, float(ma.SR)/44100)", [], rate_power),
        "tick": ("pow(10, _)", [-2, -0.5, 0, 1, 2], powers),
        "mixed": (
            "rdtable(4, pow(10, +(1)~_), 0) * pow(10, _)",
            [-2, -0.5, 0, 1, 2], 10.0 * powers),
    }
    process, input_values, expected = cases[case]
    dsp = tmp_path / "exp10.dsp"
    dsp.write_text(f'import("stdfaust.lib"); process = {process};\n')
    output = tmp_path / "exp10.py"
    arch = "minimal.py" if backend == "nnx" else "minimal_linen.py"
    cmd = [str(faust_compiler), "-lang", backend, "-" + precision,
           "-I", str(jax_library_dir), "-a", str(jax_architecture_dir / arch),
           str(dsp), "-o", str(output)]
    if not case.endswith("_native"):
        cmd.append("-exp10")
    subprocess.run(cmd, check=True, capture_output=True, text=True)

    mydsp = load_module(output, module_name="exp10_dsp").mydsp
    model = mydsp(sample_rate=sample_rate, faust_float=dtype)
    inputs = (jnp.asarray([input_values], dtype=dtype) if input_values
              else jnp.zeros((0, 5), dtype=dtype))
    if backend == "nnx":
        samples = model(inputs)
        jit_samples = nnx.jit(lambda m, x: m(x))(model, inputs)
    else:
        variables = model.init(jax.random.key(0), inputs)
        samples = model.apply(variables, inputs)
        jit_samples = jax.jit(model.apply)(variables, inputs)

    expected = np.broadcast_to(np.asarray(expected), (1, inputs.shape[1]))
    assert samples.dtype == dtype
    assert jit_samples.dtype == dtype
    np.testing.assert_allclose(samples, expected, rtol=1e-6)
    np.testing.assert_allclose(jit_samples, expected, rtol=1e-6)
    if case in ("tick", "mixed"):
        apply = model if backend == "nnx" else lambda x: model.apply(variables, x)
        gradients = jax.grad(lambda x: jnp.sum(apply(x)))(inputs)
        np.testing.assert_allclose(gradients, np.log(10.0) * expected, rtol=1e-6)
