"""Round-trip tests for the safetensors parameter persistence helpers.

Both backends gain portable, framework-agnostic ``.safetensors`` save/load:
  - NNX (``minimal.py``):   ``model.save_params(path)`` / ``model.load_params(path)``
  - Linen (``minimal_linen.py``): module-level ``save_params(variables, path)`` /
    ``load_params(path)`` (Linen keeps params external).

Faust UI parameters are commonly 0-dim scalars, which safetensors cannot store;
these tests confirm the ``__zero_dim__`` metadata trick restores the original
shapes exactly.
"""

import subprocess
import tempfile
from pathlib import Path

import pytest
import jax
import jax.numpy as jnp
from flax import nnx

from test_utils import load_module

_HERE = Path(__file__).parent
_FAUST = _HERE.parent.parent / "build" / "bin" / "faust"
_LIBS = _HERE.parent.parent / "libraries"
_ARCH_NNX = _HERE.parent.parent / "architecture" / "jax" / "minimal.py"
_ARCH_LINEN = _HERE.parent.parent / "architecture" / "jax" / "minimal_linen.py"

pytestmark = [pytest.mark.integration, pytest.mark.ci]


def _compile(lang: str, arch: Path, dsp_name: str):
	"""Compile a DSP with the given backend and return the loaded module."""
	if not _FAUST.exists():
		pytest.skip(f"faust compiler not found at {_FAUST}")
	dsp = _HERE / "dsp" / dsp_name
	out = Path(tempfile.mkdtemp(prefix=f"faust_{lang}_")) / (dsp.stem + ".py")
	subprocess.run(
		[str(_FAUST), "-lang", lang, "-a", str(arch), "-I", str(_LIBS),
		 "-o", str(out), str(dsp)],
		check=True, capture_output=True, text=True,
	)
	return load_module(out, module_name=f"{lang}_{dsp.stem}")


def test_nnx_safetensors_roundtrip(tmp_path):
	"""NNX save_params/load_params reproduce params and output exactly."""
	module = _compile("nnx", _ARCH_NNX, "learnable_gain.dsp")
	mydsp = module.mydsp
	model = mydsp(sample_rate=44100, rngs=nnx.Rngs(0, params=0, rng_stream=0))

	# Move the learnable param off its init so the round-trip is meaningful.
	_, ps, _ = nnx.split(model, nnx.Param, ...)
	new_ps = jax.tree.map(lambda p: jnp.full_like(p, 0.3), ps)
	nnx.update(model, new_ps)

	x = jnp.ones((model.num_inputs, 64))
	y_before = model(x)

	ckpt = tmp_path / "gain.safetensors"
	model.save_params(ckpt)

	# Fresh model with a *different* seed; loading must overwrite its params.
	fresh = mydsp(sample_rate=44100, rngs=nnx.Rngs(1, params=1, rng_stream=1))
	fresh.load_params(ckpt)

	_, fps, _ = nnx.split(fresh, nnx.Param, ...)
	loaded_leaves = jax.tree.leaves(fps)
	saved_leaves = jax.tree.leaves(new_ps)
	assert loaded_leaves, "no learnable params were saved"
	for a, b in zip(saved_leaves, loaded_leaves):
		assert jnp.array_equal(a, b)
		assert a.shape == b.shape  # 0-dim scalar shape restored exactly
	assert jnp.array_equal(fresh(x), y_before)


def test_linen_safetensors_roundtrip(tmp_path):
	"""Linen save_params/load_params reproduce variables and output exactly."""
	module = _compile("linen", _ARCH_LINEN, "learnable_gain.dsp")
	mydsp = module.mydsp
	model = mydsp(sample_rate=44100, faust_float=jnp.float32)

	x = jnp.ones((model.num_inputs, 64), dtype=jnp.float32)
	variables = model.init(jax.random.key(0), x)
	y_before = model.apply(variables, x)

	ckpt = tmp_path / "gain_linen.safetensors"
	module.save_params(variables, ckpt)
	loaded = module.load_params(ckpt)

	saved_leaves = jax.tree_util.tree_leaves(variables)
	loaded_leaves = jax.tree_util.tree_leaves(loaded)
	assert saved_leaves, "no learnable params were saved"
	assert len(saved_leaves) == len(loaded_leaves)
	for a, b in zip(saved_leaves, loaded_leaves):
		assert jnp.array_equal(jnp.asarray(a), jnp.asarray(b))
		assert jnp.shape(a) == jnp.shape(b)  # 0-dim scalar shape restored exactly

	# apply() with the loaded variables reproduces the output.
	assert jnp.array_equal(model.apply(loaded, x), y_before)


def test_nnx_strict_load_rejects_different_dsp(tmp_path):
	"""Strict load refuses a file saved from a different DSP.

	learnable_gain.dsp and learnable_filter.dsp both compile to a single
	``fHslider0`` parameter, so the tensor names alone cannot tell them apart;
	the UI labels recorded in the file metadata ("gain" vs "cutoff") can.
	"""
	gain_module = _compile("nnx", _ARCH_NNX, "learnable_gain.dsp")
	filter_module = _compile("nnx", _ARCH_NNX, "learnable_filter.dsp")

	gain = gain_module.mydsp(sample_rate=44100, rngs=nnx.Rngs(0, params=0, rng_stream=0))
	ckpt = tmp_path / "gain.safetensors"
	gain.save_params(ckpt)

	filt = filter_module.mydsp(sample_rate=44100, rngs=nnx.Rngs(0, params=0, rng_stream=0))
	with pytest.raises(filter_module.UnknownParameterError):
		filt.load_params(ckpt)

	# strict=False is the explicit opt-out: overlapping parameters are loaded.
	filt.load_params(ckpt, strict=False)
	assert jnp.array_equal(filt.fHslider0[...], gain.fHslider0[...])


def test_linen_load_params_expected_validation(tmp_path):
	"""Linen load_params(expected=...) accepts a matching file, rejects a mismatch."""
	module = _compile("linen", _ARCH_LINEN, "learnable_gain.dsp")
	mydsp = module.mydsp
	model = mydsp(sample_rate=44100, faust_float=jnp.float32)

	x = jnp.ones((model.num_inputs, 64), dtype=jnp.float32)
	variables = model.init(jax.random.key(0), x)

	ckpt = tmp_path / "gain_linen.safetensors"
	module.save_params(variables, ckpt)

	# Matching structure loads fine.
	loaded = module.load_params(ckpt, expected=variables)
	assert jnp.array_equal(model.apply(loaded, x), model.apply(variables, x))

	# A structure with an extra parameter must be rejected.
	wrong = {"params": {**variables["params"], "fHslider1": jnp.zeros(())}}
	with pytest.raises(module.UnknownParameterError):
		module.load_params(ckpt, expected=wrong)
