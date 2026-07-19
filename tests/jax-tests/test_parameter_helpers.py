"""
Test parameter helper methods added to minimal.py:
- extract_metadata (with ordering prefix stripping)
- label_to_zone()
- params_from_labels()
- with_defaults()
- UnknownParameterError
"""

import pytest
import jax.numpy as jnp
from flax import nnx

# Import the extract_metadata function and exception directly from a generated module
# We'll use my_example.py which should have these


class TestExtractMetadata:
	"""Test the extract_metadata utility function."""

	def test_basic_metadata_extraction(self, compile_and_load_dsp, default_rngs):
		"""Test basic [key:value] metadata extraction."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		# Import the function from the module's namespace
		import sys
		module = sys.modules["compiled_dsp"]
		extract_metadata = module.extract_metadata

		# Test basic case
		clean, meta = extract_metadata("Gain[unit:dB]")
		assert clean == "Gain"
		assert meta == {"unit": "dB"}

	def test_multiple_metadata(self, compile_and_load_dsp, default_rngs):
		"""Test multiple metadata extraction."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")

		import sys
		module = sys.modules["compiled_dsp"]
		extract_metadata = module.extract_metadata

		clean, meta = extract_metadata("param[tau:learnable][tau_init:0.5]")
		assert clean == "param"
		assert meta == {"tau": "learnable", "tau_init": "0.5"}

	def test_ordering_prefix_stripped(self, compile_and_load_dsp, default_rngs):
		"""Test that ordering prefixes like [0], [3] are stripped from labels."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")

		import sys
		module = sys.modules["compiled_dsp"]
		extract_metadata = module.extract_metadata

		# Test ordering prefix stripping
		clean, meta = extract_metadata("[0] Wave [style:menu{'Saw':0;'Square':1}]")
		assert clean == "Wave"
		assert "style" in meta

		# Test another ordering prefix
		clean, meta = extract_metadata("[3] L Curve [style:menu{'-LIN':0;'-EXP':1}]")
		assert clean == "L Curve"

		# Test prefix without metadata
		clean, meta = extract_metadata("[4] R Curve")
		assert clean == "R Curve"
		assert meta == {}

	def test_no_metadata(self, compile_and_load_dsp, default_rngs):
		"""Test label with no metadata."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")

		import sys
		module = sys.modules["compiled_dsp"]
		extract_metadata = module.extract_metadata

		clean, meta = extract_metadata("Simple Label")
		assert clean == "Simple Label"
		assert meta == {}


class TestLabelToZone:
	"""Test the label_to_zone method."""

	def test_basic_label_to_zone(self, compile_and_load_dsp, default_rngs):
		"""Test converting a label to its zone."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		# Get metadata to find the labels
		metadata = model.get_parameter_metadata()

		# Pick a parameter and verify label_to_zone works
		for zone, meta in metadata.items():
			label = meta["full_label"]
			found_zone = model.label_to_zone(label)
			assert found_zone == zone, f"Expected {zone}, got {found_zone} for label '{label}'"

	def test_unknown_label_raises(self, compile_and_load_dsp, default_rngs):
		"""Test that unknown labels raise UnknownParameterError."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		import sys
		module = sys.modules["compiled_dsp"]
		UnknownParameterError = module.UnknownParameterError

		with pytest.raises(UnknownParameterError, match="Unknown parameter"):
			model.label_to_zone("nonexistent/parameter/path")


class TestParamsFromLabels:
	"""Test the params_from_labels method."""

	def test_basic_conversion(self, compile_and_load_dsp, default_rngs):
		"""Test converting label-keyed dict to zone-keyed dict."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		# Get metadata to build label dict
		metadata = model.get_parameter_metadata()

		# Create a dict keyed by labels
		label_params = {}
		for zone, meta in metadata.items():
			label_params[meta["full_label"]] = 0.5

		# Convert to zone params
		zone_params = model.params_from_labels(label_params)

		# Verify all zones are present
		assert set(zone_params.keys()) == set(metadata.keys())

		# Verify values are preserved
		for zone in zone_params:
			assert zone_params[zone] == 0.5

	def test_partial_conversion(self, compile_and_load_dsp, default_rngs):
		"""Test converting a partial set of parameters."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		# Get one parameter's label
		metadata = model.get_parameter_metadata()
		first_zone = list(metadata.keys())[0]
		first_label = metadata[first_zone]["full_label"]

		# Convert single parameter
		label_params = {first_label: 0.75}
		zone_params = model.params_from_labels(label_params)

		assert len(zone_params) == 1
		assert first_zone in zone_params
		assert zone_params[first_zone] == 0.75

	def test_unknown_label_raises(self, compile_and_load_dsp, default_rngs):
		"""Test that unknown labels raise UnknownParameterError."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		import sys
		module = sys.modules["compiled_dsp"]
		UnknownParameterError = module.UnknownParameterError

		with pytest.raises(UnknownParameterError):
			model.params_from_labels({"invalid/label": 1.0})


class TestWithDefaults:
	"""Test the with_defaults method."""

	def test_empty_partial_returns_all_defaults(self, compile_and_load_dsp, default_rngs):
		"""Test that empty partial params returns all defaults."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		defaults = model.unnormalize()
		full_params = model.with_defaults({})

		# Should have same keys
		assert set(full_params.keys()) == set(defaults.keys())

		# Values should match defaults
		for zone in defaults:
			assert jnp.allclose(full_params[zone], defaults[zone])

	def test_partial_override(self, compile_and_load_dsp, default_rngs):
		"""Test that partial params override defaults."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		defaults = model.unnormalize()

		# Override first parameter
		first_zone = list(defaults.keys())[0]
		partial = {first_zone: jnp.array(999.0)}

		full_params = model.with_defaults(partial)

		# Overridden param should have new value
		assert jnp.allclose(full_params[first_zone], 999.0)

		# Other params should have default values
		for zone in defaults:
			if zone != first_zone:
				assert jnp.allclose(full_params[zone], defaults[zone])

	def test_all_params_override(self, compile_and_load_dsp, default_rngs):
		"""Test overriding all parameters."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		defaults = model.unnormalize()

		# Override all parameters
		all_override = {zone: jnp.array(float(i)) for i, zone in enumerate(defaults.keys())}
		full_params = model.with_defaults(all_override)

		# All should be overridden
		for i, zone in enumerate(defaults.keys()):
			assert jnp.allclose(full_params[zone], float(i))

	def test_unknown_zone_raises(self, compile_and_load_dsp, default_rngs):
		"""Test that unknown zones raise UnknownParameterError."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		import sys
		module = sys.modules["compiled_dsp"]
		UnknownParameterError = module.UnknownParameterError

		with pytest.raises(UnknownParameterError, match="Unknown parameter"):
			model.with_defaults({"fInvalidZone99": 1.0})

	def test_converts_to_jnp_array(self, compile_and_load_dsp, default_rngs):
		"""Test that float values are converted to jnp arrays."""
		mydsp = compile_and_load_dsp("simple_gain.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		defaults = model.unnormalize()
		first_zone = list(defaults.keys())[0]

		# Pass plain float
		full_params = model.with_defaults({first_zone: 0.5})

		# Should be jnp array
		assert isinstance(full_params[first_zone], jnp.ndarray)


class TestIntegration:
	"""Integration tests combining multiple helper methods."""

	def test_labels_to_params_to_defaults_workflow(self, compile_and_load_dsp, default_rngs):
		"""Test typical workflow: labels -> zones -> with_defaults -> render."""
		mydsp = compile_and_load_dsp("my_example.dsp")
		model = mydsp(sample_rate=44100, rngs=default_rngs)

		# Get one parameter's label
		metadata = model.get_parameter_metadata()
		first_zone = list(metadata.keys())[0]
		first_label = metadata[first_zone]["full_label"]

		# Typical workflow:
		# 1. User has label-keyed params (e.g., from config file)
		label_params = {first_label: 0.8}

		# 2. Convert to zone-keyed
		zone_params = model.params_from_labels(label_params)

		# 3. Fill in defaults
		full_params = model.with_defaults(zone_params)

		# 4. Render with params
		inputs = jnp.zeros((model.num_inputs, 1024))
		output = model(inputs, params=full_params)

		# Should produce valid output
		assert output.shape == (model.num_outputs, 1024)
		assert jnp.all(jnp.isfinite(output))

	def test_with_nentry(self, compile_and_load_dsp):
		"""Test helpers work with nentry parameters."""
		# nentry needs nentry RNG for training mode, or use eval mode
		rngs = nnx.Rngs(0, params=0, rng_stream=0, nentry=42)
		mydsp = compile_and_load_dsp("nentry_test.dsp")
		model = mydsp(sample_rate=44100, rngs=rngs)
		model.eval()  # Use eval mode to avoid nentry sampling in unnormalize

		# Get metadata
		metadata = model.get_parameter_metadata()

		# Find the nentry
		nentry_zone = None
		for zone, meta in metadata.items():
			if meta.get("type") == "nentry":
				nentry_zone = zone
				break

		if nentry_zone is None:
			pytest.skip("No nentry found in DSP")

		# Test label_to_zone works for nentry
		nentry_label = metadata[nentry_zone]["full_label"]
		found_zone = model.label_to_zone(nentry_label)
		assert found_zone == nentry_zone

		# with_defaults should work (nentry has special handling)
		defaults = model.unnormalize()
		full_params = model.with_defaults({})

		# Should have the nentry zone
		assert nentry_zone in full_params


if __name__ == "__main__":
	pytest.main([__file__, "-v"])
