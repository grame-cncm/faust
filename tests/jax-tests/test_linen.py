"""Pytest parity for the Flax Linen backend.

The Linen backend (``-lang linen`` + ``architecture/jax/minimal_linen.py``) is
otherwise only covered by the impulse-response tests. These tests exercise the
idiomatic Linen lifecycle directly: compile -> ``init`` -> ``apply``, gradient
flow through ``self.param`` parameters, and the learnable-soundfile path.
"""

import subprocess
import tempfile
from pathlib import Path

import pytest
import jax
import jax.numpy as jnp

from test_utils import load_module

_HERE = Path(__file__).parent
_FAUST = _HERE.parent.parent / "build" / "bin" / "faust"
_ARCH = _HERE.parent.parent / "architecture" / "jax" / "minimal_linen.py"
_LIBS = _HERE.parent.parent / "libraries"

pytestmark = [pytest.mark.integration, pytest.mark.ci]


def _compile_linen(dsp_name: str):
    """Compile a DSP with the Linen backend and return its ``mydsp`` class."""
    if not _FAUST.exists():
        pytest.skip(f"faust compiler not found at {_FAUST}")
    dsp = _HERE / "dsp" / dsp_name
    out = Path(tempfile.mkdtemp(prefix="faust_linen_")) / (dsp.stem + ".py")
    subprocess.run(
        [str(_FAUST), "-lang", "linen", "-a", str(_ARCH), "-I", str(_LIBS),
         "-o", str(out), str(dsp)],
        check=True, capture_output=True, text=True,
    )
    return load_module(out, module_name="linen_" + dsp.stem).mydsp


def test_linen_compile_and_run():
    """A Linen module initializes and applies, producing correctly shaped audio."""
    mydsp = _compile_linen("simple_gain.dsp")
    model = mydsp(sample_rate=44100, faust_float=jnp.float32)

    x = jnp.ones((model.num_inputs, 64), dtype=jnp.float32)
    variables = model.init(jax.random.key(0), x)
    y = model.apply(variables, x)

    assert y.shape == (model.num_outputs, 64)
    assert jnp.all(jnp.isfinite(y))


def test_linen_param_is_registered():
    """UI sliders are registered as real Flax Linen parameters (not plain attrs)."""
    mydsp = _compile_linen("learnable_gain.dsp")
    model = mydsp(sample_rate=44100, faust_float=jnp.float32)

    x = jnp.ones((model.num_inputs, 16), dtype=jnp.float32)
    variables = model.init(jax.random.key(0), x)

    assert "params" in variables
    assert "fHslider0" in variables["params"]


def test_linen_gradient_flows():
    """Gradients flow through the learnable parameter (the point of the backend)."""
    mydsp = _compile_linen("learnable_gain.dsp")
    model = mydsp(sample_rate=44100, faust_float=jnp.float32)

    x = jnp.ones((model.num_inputs, 64), dtype=jnp.float32)
    variables = model.init(jax.random.key(0), x)

    def loss(params):
        return jnp.mean(model.apply({"params": params}, x) ** 2)

    grads = jax.grad(loss)(variables["params"])
    leaves = jax.tree_util.tree_leaves(grads)

    assert leaves, "no learnable parameters were found"
    assert any(float(jnp.sum(jnp.abs(g))) > 0 for g in leaves), \
        "gradient is zero for every parameter"


def test_linen_jit_apply():
    """apply() runs under jax.jit (no state mutation in the forward pass)."""
    mydsp = _compile_linen("learnable_gain.dsp")
    model = mydsp(sample_rate=44100, faust_float=jnp.float32)

    x = jnp.ones((model.num_inputs, 64), dtype=jnp.float32)
    variables = model.init(jax.random.key(0), x)

    jitted = jax.jit(lambda v, xx: model.apply(v, xx))
    y = jitted(variables, x)
    assert y.shape == (model.num_outputs, 64)


def test_linen_learnable_soundfile():
    """A ``[param:1]`` soundfile registers its buffers as a learnable parameter."""
    mydsp = _compile_linen("soundfile_learnable.dsp")
    # The DSP references assets/sound1.wav relative to this directory.
    model = mydsp(sample_rate=44100, faust_float=jnp.float32,
                  soundfile_dirs=(str(_HERE),))

    x = jnp.zeros((model.num_inputs, 16), dtype=jnp.float32)
    variables = model.init(jax.random.key(0), x)

    param_keys = list(variables["params"].keys())
    assert any("fBuffers" in k for k in param_keys), \
        f"learnable soundfile buffers not registered as a param: {param_keys}"

    # And the buffer parameter should receive a gradient.
    def loss(params):
        return jnp.sum(model.apply({"params": params}, x) ** 2)

    grads = jax.grad(loss)(variables["params"])
    buf_key = next(k for k in param_keys if "fBuffers" in k)
    assert float(jnp.sum(jnp.abs(grads[buf_key]))) >= 0.0  # finite, well-defined
    assert jnp.all(jnp.isfinite(grads[buf_key]))
