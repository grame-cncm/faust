"""Regression tests for the revised NNX/Linen generated-module API.

Covers:
- [scale:log] sliders: defaults survive the normalize/unnormalize round-trip
  and log scale rejects non-positive minima.
- nentry logits path in unnormalize_params ({zone}_logits / {zone}_tau) and
  normalized_params logits keyed by shortname.
- Parameter dict key domains: zone names, Faust shortnames, and full label
  paths; UnknownParameterError on typos; partial dicts merged with defaults.
- Class-level attributes (num_inputs, num_outputs, is_stochastic,
  json_metadata, auto-generated docstring) readable without an instance.
- Widget metadata: checkbox type is "checkbox"; sliders carry "step" and
  "shortname".
- RNG policy: deterministic DSPs run with no rngs anywhere; stochastic DSPs
  require rngs and are reproducible for a fixed key.
- deterministic as a constructor argument (NNX kwarg / Linen dataclass field).
- Generator path: 0-input DSPs called with num_samples only; input shape
  validation raises ValueError.
- process_block returns (new_carry, outputs) with the carry FIRST (NNX and
  Linen).
"""

import subprocess
import sys
import tempfile
from pathlib import Path

import pytest
import jax
import jax.numpy as jnp
from flax import nnx

from test_utils import load_module

_HERE = Path(__file__).parent
_FAUST = _HERE.parent.parent / "build" / "bin" / "faust"
_ARCH_LINEN = _HERE.parent.parent / "architecture" / "jax" / "minimal_linen.py"
_LIBS = _HERE.parent.parent / "libraries"

SAMPLE_RATE = 44100

pytestmark = [pytest.mark.integration, pytest.mark.ci]


def _compiled_module():
	"""Return the module object of the DSP most recently loaded by the fixtures.

	``load_module`` registers each compiled DSP under the fixed name
	"compiled_dsp", so this must be called right after ``compile_and_load_dsp``
	and before the next compilation.
	"""
	return sys.modules["compiled_dsp"]


def _compile_linen(dsp_name: str):
	"""Compile a DSP with the Linen backend and return its generated module."""
	if not _FAUST.exists():
		pytest.skip(f"faust compiler not found at {_FAUST}")
	dsp = _HERE / "dsp" / dsp_name
	out = Path(tempfile.mkdtemp(prefix="faust_linen_api_")) / (dsp.stem + ".py")
	subprocess.run(
		[str(_FAUST), "-lang", "linen", "-a", str(_ARCH_LINEN), "-I", str(_LIBS),
		 "-o", str(out), str(dsp)],
		check=True, capture_output=True, text=True,
	)
	return load_module(out, module_name="linen_api_" + dsp.stem)


class TestLogScaleSlider:
	"""[scale:log] sliders: geometric normalize/unnormalize round-trip."""

	def test_log_default_unnormalizes_to_init(self, compile_and_load_dsp):
		"""The init value 1000 on [100, 10000] round-trips exactly (0.5 normalized)."""
		mydsp = compile_and_load_dsp("log_scale.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		# The stored normalized value is the geometric midpoint of the range.
		assert float(model.fHslider0[...]) == pytest.approx(0.5, abs=1e-6)

		params = model.unnormalize()
		assert float(params["fHslider0"]) == pytest.approx(1000.0, rel=1e-4)

		# log_scale.dsp is a generator that outputs the slider's physical value.
		outputs = model(num_samples=8)
		assert outputs.shape == (1, 8)
		assert jnp.allclose(outputs, 1000.0, rtol=1e-4)

	def test_log_param_override_affects_output(self, compile_and_load_dsp):
		"""A physical params= override is passed through untouched."""
		mydsp = compile_and_load_dsp("log_scale.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		outputs = model(params={"freq": 4400.0}, num_samples=8)
		assert jnp.allclose(outputs, 4400.0, rtol=1e-5)

	def test_log_normalize_unnormalize_roundtrip(self, compile_and_load_dsp):
		"""normalize_value is the exact inverse of the log unnormalizer."""
		mydsp = compile_and_load_dsp("log_scale.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		unnorm = model.create_unnormalize_func(100.0, 10000.0, "log")
		for value in [100.0, 440.0, 1000.0, 10000.0]:
			normalized = model.normalize_value(value, 100.0, 10000.0, "log")
			assert 0.0 <= float(normalized) <= 1.0
			assert float(unnorm(normalized)) == pytest.approx(value, rel=1e-4)

		# Geometric spacing: endpoints and midpoint land where expected.
		assert float(model.normalize_value(100.0, 100.0, 10000.0, "log")) == pytest.approx(0.0, abs=1e-6)
		assert float(model.normalize_value(1000.0, 100.0, 10000.0, "log")) == pytest.approx(0.5, abs=1e-6)
		assert float(model.normalize_value(10000.0, 100.0, 10000.0, "log")) == pytest.approx(1.0, abs=1e-6)

	def test_log_scale_nonpositive_min_raises(self, compile_and_load_dsp):
		"""Log scale with min <= 0 raises InvalidParameterError."""
		mydsp = compile_and_load_dsp("log_scale.dsp")
		module = _compiled_module()
		model = mydsp(sample_rate=SAMPLE_RATE)

		with pytest.raises(module.InvalidParameterError, match="positive minimum"):
			model.create_unnormalize_func(0.0, 100.0, "log")
		with pytest.raises(module.InvalidParameterError, match="positive minimum"):
			model.normalize_value(50.0, -1.0, 100.0, "log")


class TestNentryLogitsPath:
	"""unnormalize_params supports {zone}_logits (+ optional {zone}_tau)."""

	def test_unnormalize_params_logits_and_tau(self, compile_and_load_dsp):
		"""Logits + tau produce the argmax step value under the plain zone key."""
		mydsp = compile_and_load_dsp("nentry_test.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		# nentry_test.dsp: nentry("mode...", 0, 0, 3, 1) -> step values 0..3.
		logits = jnp.array([0.0, 0.0, 5.0, 0.0], dtype=jnp.float32)
		result = model.unnormalize_params({"fEntry0_logits": logits, "fEntry0_tau": 1.0})

		# Only the provided parameter comes back, keyed by the plain zone.
		assert set(result) == {"fEntry0"}
		assert float(result["fEntry0"]) == pytest.approx(2.0)

	def test_unnormalize_params_logits_without_tau(self, compile_and_load_dsp):
		"""Without an explicit tau the module's own temperature is used."""
		mydsp = compile_and_load_dsp("nentry_test.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		logits = jnp.array([4.0, 0.0, 0.0, 0.0], dtype=jnp.float32)
		result = model.unnormalize_params({"fEntry0_logits": logits})
		assert set(result) == {"fEntry0"}
		assert float(result["fEntry0"]) == pytest.approx(0.0)

	def test_call_with_shortname_logits(self, compile_and_load_dsp):
		"""normalized_params logits may be keyed by the Faust shortname."""
		mydsp = compile_and_load_dsp("nentry_default.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		shortname = model.get_parameter_metadata()["fEntry0"]["shortname"]
		assert shortname == "mode"

		# nentry_default.dsp: process = _ * mode, so output = input * argmax value.
		logits = jnp.array([0.0, 0.0, 5.0, 0.0], dtype=jnp.float32)
		inputs = jnp.ones((1, 16), dtype=jnp.float32)
		outputs = model(inputs, normalized_params={f"{shortname}_logits": logits})
		assert jnp.allclose(outputs, 2.0)


class TestParamKeyDomains:
	"""Parameter dicts accept zone names, shortnames, and full label paths."""

	def test_zone_shortname_label_equivalent(self, compile_and_load_dsp):
		"""The same value keyed three different ways renders identically."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		meta = model.get_parameter_metadata()["fHslider0"]
		assert meta["shortname"] == "gain"
		assert meta["full_label"] == "simple_gain/gain"

		inputs = jnp.ones((1, 32), dtype=jnp.float32)
		by_zone = model(inputs, params={"fHslider0": 0.25})
		by_shortname = model(inputs, params={meta["shortname"]: 0.25})
		by_label = model(inputs, params={meta["full_label"]: 0.25})

		assert jnp.array_equal(by_zone, by_shortname)
		assert jnp.array_equal(by_zone, by_label)
		assert jnp.allclose(by_zone, 0.25)

	def test_unknown_key_raises(self, compile_and_load_dsp):
		"""A typo'd key raises UnknownParameterError, in calls and helpers."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		module = _compiled_module()
		model = mydsp(sample_rate=SAMPLE_RATE)

		inputs = jnp.ones((1, 8), dtype=jnp.float32)
		with pytest.raises(module.UnknownParameterError, match="Unknown parameter 'gian'"):
			model(inputs, params={"gian": 0.5})
		with pytest.raises(module.UnknownParameterError, match="Unknown parameter"):
			model.unnormalize_params({"gian": 0.5})

	def test_partial_params_merged_with_defaults(self, compile_and_load_dsp):
		"""params= with a subset of keys fills the rest from module defaults."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		# my_example.dsp is a generator (widgets only, no audio inputs).
		assert model.num_inputs == 0
		num_samples = 256

		partial = {"gain": 0.9}
		outputs_partial = model(params=partial, num_samples=num_samples)
		outputs_full = model(params=model.with_defaults(partial), num_samples=num_samples)
		assert jnp.array_equal(outputs_partial, outputs_full)

		# The override actually changes the render vs. the defaults.
		outputs_default = model(num_samples=num_samples)
		assert not jnp.allclose(outputs_partial, outputs_default)


class TestClassAttributesAndMetadata:
	"""Class attributes are readable without an instance; widget metadata is complete."""

	def test_class_attributes_without_instance(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("simple_gain.dsp")

		assert mydsp.num_inputs == 1
		assert mydsp.num_outputs == 1
		assert mydsp.is_stochastic is False
		assert isinstance(mydsp.json_metadata, dict)
		assert mydsp.json_metadata["inputs"] == 1
		assert mydsp.json_metadata["outputs"] == 1
		assert mydsp.json_metadata["name"] == "simple_gain"

		# Auto-generated docstring names the DSP, I/O, and the parameter table.
		assert "1 in, 1 out" in mydsp.__doc__
		assert "simple_gain/gain" in mydsp.__doc__

	def test_stochastic_class_attribute(self, compile_and_load_dsp):
		"""is_stochastic is True iff the DSP calls random_* foreign functions."""
		mydsp = compile_and_load_dsp("random_test.dsp")
		assert mydsp.is_stochastic is True

	def test_slider_metadata_step_and_shortname(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		meta = model.get_parameter_metadata()["fHslider0"]
		assert meta["type"] == "hslider"
		assert meta["step"] == pytest.approx(0.01)
		assert meta["shortname"] == "gain"
		assert meta["min"] == 0.0
		assert meta["max"] == 1.0
		assert meta["default"] == 0.5

	def test_checkbox_metadata_type(self, compile_and_load_dsp):
		"""Checkboxes register via add_checkbox: metadata type is "checkbox"."""
		mydsp = compile_and_load_dsp("checkbox_gate.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		meta = model.get_parameter_metadata()["fCheckbox0"]
		assert meta["type"] == "checkbox"
		assert meta["shortname"] == "mute"

		# And the checkbox is addressable by shortname like any input widget.
		inputs = jnp.ones((1, 8), dtype=jnp.float32)
		assert jnp.allclose(model(inputs), 0.0)  # default: unchecked
		assert jnp.allclose(model(inputs, params={"mute": 1.0}), 1.0)

	def test_deterministic_constructor_kwarg(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("nentry_test.dsp")

		model = mydsp(sample_rate=SAMPLE_RATE)
		assert model.deterministic is False

		model_det = mydsp(sample_rate=SAMPLE_RATE, deterministic=True)
		assert model_det.deterministic is True

		# deterministic=True skips nentry Gumbel sampling even when an `nentry`
		# RNG stream is available: repeated calls are identical.
		rngs = nnx.Rngs(0, params=0, rng_stream=0, nentry=42)
		model_det_rngs = mydsp(sample_rate=SAMPLE_RATE, deterministic=True, rngs=rngs)
		inputs = jnp.ones((1, 32), dtype=jnp.float32)
		first = model_det_rngs(inputs)
		second = model_det_rngs(inputs)
		assert jnp.array_equal(first, second)


class TestRngPolicy:
	"""rngs is only consulted/required when the DSP is stochastic."""

	def test_deterministic_dsp_runs_without_rngs(self, compile_and_load_dsp):
		"""A deterministic DSP needs no rngs at construction or call time."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)  # no rngs anywhere

		inputs = jnp.ones((1, 64), dtype=jnp.float32)
		outputs = model(inputs)
		assert jnp.allclose(outputs, 0.5)

		# process_block also runs without rngs and returns the carry FIRST.
		carry = model.initialize_carry()
		new_carry, block = model.process_block(carry, inputs)
		assert isinstance(new_carry, dict)
		assert jnp.array_equal(block, outputs)

	def test_stochastic_dsp_requires_rngs(self, compile_and_load_dsp):
		"""With no rngs at all, a stochastic DSP raises instead of silently seeding."""
		mydsp = compile_and_load_dsp("random_test.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		with pytest.raises(ValueError, match="stochastic"):
			model(num_samples=8)

	def test_stochastic_dsp_reproducible_with_key(self, compile_and_load_dsp):
		"""The same explicit key reproduces the exact output; different keys differ."""
		mydsp = compile_and_load_dsp("random_test.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		first = model(num_samples=64, rngs=jax.random.key(0))
		second = model(num_samples=64, rngs=jax.random.key(0))
		other = model(num_samples=64, rngs=jax.random.key(1))

		assert jnp.array_equal(first, second)
		assert not jnp.allclose(first, other)
		# random_test.dsp outputs random_uniform() in [0, 1].
		assert jnp.all(first >= 0.0) and jnp.all(first <= 1.0)


class TestGeneratorAndShapeValidation:
	"""Generators run with num_samples only; bad input shapes raise ValueError."""

	def test_generator_call_with_num_samples(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("gen_constant.dsp")
		assert mydsp.num_inputs == 0
		model = mydsp(sample_rate=SAMPLE_RATE)

		outputs = model(num_samples=32)
		assert outputs.shape == (1, 32)
		assert jnp.allclose(outputs, 0.5)

		carry = model.initialize_carry()
		new_carry, block = model.process_block(carry, num_samples=16)
		assert isinstance(new_carry, dict)
		assert block.shape == (1, 16)

	def test_generator_missing_num_samples_raises(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("gen_constant.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		with pytest.raises(ValueError, match="num_samples"):
			model()

	def test_inputs_required_for_processor(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		with pytest.raises(ValueError, match="`inputs` is required"):
			model(num_samples=8)

	def test_wrong_channel_count_raises(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		with pytest.raises(ValueError, match="Expected inputs of shape"):
			model(jnp.ones((3, 8), dtype=jnp.float32))

	def test_num_samples_contradiction_raises(self, compile_and_load_dsp):
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=SAMPLE_RATE)

		with pytest.raises(ValueError, match="contradicts"):
			model(jnp.ones((1, 8), dtype=jnp.float32), num_samples=9)


class TestLinenApiRevisions:
	"""Linen mirrors of the revised API (init/apply/bind lifecycle)."""

	def test_linen_process_block_carry_first(self):
		module = _compile_linen("simple_gain.dsp")
		model = module.mydsp(sample_rate=SAMPLE_RATE, faust_float=jnp.float32)

		x = jnp.ones((1, 16), dtype=jnp.float32)
		variables = model.init(jax.random.key(0), x)
		bound = model.bind(variables)

		carry = bound.initialize_carry()
		new_carry, outputs = bound.process_block(carry, x)
		assert isinstance(new_carry, dict)
		assert outputs.shape == (1, 16)
		assert jnp.allclose(outputs, 0.5)

	def test_linen_deterministic_call_without_rngs(self):
		"""apply() with no rngs works for a deterministic DSP."""
		module = _compile_linen("simple_gain.dsp")
		model = module.mydsp(sample_rate=SAMPLE_RATE, faust_float=jnp.float32)

		x = jnp.ones((1, 16), dtype=jnp.float32)
		variables = model.init(jax.random.key(0), x)
		outputs = model.apply(variables, x)
		assert jnp.allclose(outputs, 0.5)

	def test_linen_deterministic_dataclass_field(self):
		module = _compile_linen("simple_gain.dsp")

		model = module.mydsp(sample_rate=SAMPLE_RATE, faust_float=jnp.float32)
		assert model.deterministic is False

		model_det = module.mydsp(
			sample_rate=SAMPLE_RATE, faust_float=jnp.float32, deterministic=True
		)
		assert model_det.deterministic is True

	def test_linen_log_scale_default(self):
		"""The log-slider default renders at its init value through init/apply."""
		module = _compile_linen("log_scale.dsp")
		model = module.mydsp(sample_rate=SAMPLE_RATE, faust_float=jnp.float32)
		assert model.num_inputs == 0

		variables = model.init(jax.random.key(0), num_samples=4)
		outputs = model.apply(variables, num_samples=4)
		assert outputs.shape == (1, 4)
		assert jnp.allclose(outputs, 1000.0, rtol=1e-4)

	def test_linen_stochastic_rng_policy(self):
		"""No rngs raises InvalidRNGError; a fixed key is reproducible."""
		module = _compile_linen("random_test.dsp")
		model = module.mydsp(sample_rate=SAMPLE_RATE, faust_float=jnp.float32)
		assert module.mydsp.is_stochastic is True

		# apply() reserves its own rngs= kwarg for make_rng, so the DSP key is
		# bound inside a method closure (same pattern as the test harness).
		key = jax.random.key(0)
		variables = model.init(
			jax.random.key(1), method=lambda mdl: mdl(num_samples=4, rngs=key)
		)

		with pytest.raises(module.InvalidRNGError, match="stochastic"):
			model.apply(variables, num_samples=8)

		first = model.apply(variables, method=lambda mdl: mdl(num_samples=32, rngs=key))
		second = model.apply(variables, method=lambda mdl: mdl(num_samples=32, rngs=key))
		assert jnp.array_equal(first, second)
		assert jnp.all(first >= 0.0) and jnp.all(first <= 1.0)
