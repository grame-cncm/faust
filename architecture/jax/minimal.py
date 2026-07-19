# ************************************************************************
# FAUST Architecture File
# Copyright (C) 2026 GRAME, Centre National de Creation Musicale
# ---------------------------------------------------------------------

# This is sample code. This file is provided as an example of minimal
# FAUST architecture file. Redistribution and use in source and binary
# forms, with or without modification, in part or in full are permitted.
# In particular you can create a derived work of this FAUST architecture
# and distribute that work under terms of your choice.

# This sample code is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# ************************************************************************

import argparse
from collections.abc import Mapping
from functools import partial
import json
from pathlib import Path
import re
from typing import Dict, List, Tuple, Optional, Any, Callable
import warnings
import numpy as np
import jax
from jax import numpy as jnp, random, Array
from jax.typing import ArrayLike
from flax import nnx
from flax.nnx import rnglib
from flax.nnx.module import first_from
from flax.typing import Dtype
import librosa


# Constants for scaling and normalization
NORMALIZED_MIN = 0.0
NORMALIZED_MAX = 1.0
EXP_SCALE_MIN = 1.0
NENTRY_LOGITS_INIT = 1.0
NENTRY_TAU_INIT = 1.0
IMPULSE_VALUE = 1.0
DEFAULT_SAMPLE_RATE = 44100
DEFAULT_BLOCK_SIZE = 512
DEFAULT_RNG_SEED = 0

# Custom exceptions
class FaustError(Exception):
	"""Base exception for Faust-related errors."""
	pass


class SoundfileLoadError(FaustError):
	"""Exception raised when soundfile loading fails."""
	pass


class InvalidScaleModeError(FaustError):
	"""Exception raised when an invalid scale mode is provided."""
	pass


class InvalidRNGError(FaustError):
	"""Exception raised when an invalid RNG type is provided."""
	pass


class InvalidParameterError(FaustError):
	"""Exception raised when parameter validation fails."""
	pass


class UnknownParameterError(FaustError):
	"""Exception raised when an unknown parameter zone or label is provided."""
	pass


# Utility functions for metadata parsing
def extract_metadata(full_label: str) -> Tuple[str, Dict[str, str]]:
	"""
	Extract metadata from a Faust UI label.

	Parses labels like "Name[key1:value1][key2:value2]" into:
	- Clean label: "Name"
	- Metadata dict: {"key1": "value1", "key2": "value2"}

	Args:
		full_label: Full label string with embedded metadata

	Returns:
		Tuple of (clean_label, metadata_dict)

	Examples:
		>>> extract_metadata("Gain[unit:dB]")
		("Gain", {"unit": "dB"})

		>>> extract_metadata("Tango[param:1][url:{'tango.wav'}]")
		("Tango", {"param": "1", "url": "{'tango.wav'}"})

		>>> extract_metadata("[0] Wave [style:menu{'Saw':0;'Square':1}]")
		("Wave", {"style": "menu{'Saw':0;'Square':1}"})
	"""
	# Find all [key:value] patterns
	# Pattern matches [key:value] where value can contain anything except ]
	pattern = r'\[([^:\]]+):([^\]]+)\]'
	matches = re.findall(pattern, full_label)

	# Extract metadata dict
	metadata = {key.strip(): value.strip() for key, value in matches}

	# Remove all metadata brackets from label to get clean label
	clean_label = re.sub(pattern, '', full_label).strip()

	# Remove UI ordering prefix like [0], [3], etc. (no colon, so not caught above)
	clean_label = re.sub(r'^\[\d+\]\s*', '', clean_label)

	return clean_label, metadata


@jax.custom_vjp
def magic_clamp(x, min_val=0.0, max_val=1.0):
	"""
	Clip with conditional straight-through estimator for better gradient flow.

	Forward pass: Standard clipping
	Backward pass: Gradients flow when update moves toward valid region

	This improves optimization convergence when parameters start outside bounds
	or frequently hit boundaries during training.

	Based on: Hayes, B. (2025). "Magic Clamp" https://github.com/ben-hayes/magic-clamp
	Reference: Yang, Y., Jin, Z., Barnes, C., & Finkelstein, A. (2023).
	  "White Box Search Over Audio Synthesizer Parameters." ISMIR, pp. 190-196.
	"""
	return jnp.clip(x, min_val, max_val)


def magic_clamp_fwd(x, min_val=0.0, max_val=1.0):
	"""Forward pass: standard clipping."""
	y = jnp.clip(x, min_val, max_val)
	return y, (x, min_val, max_val)


def magic_clamp_bwd(res, g):
	"""
	Backward pass: conditional straight-through estimator.

	Gradient flow when parameter update moves toward valid region:
	- If x < min and update would increase x (g < 0): allow gradient
	- If x > max and update would decrease x (g > 0): allow gradient
	- Otherwise: block gradient (would move further out of bounds)
	"""
	x, min_val, max_val = res

	# Block gradients when update would move further out of bounds
	grad_x = jnp.where(
		((x < min_val) & (g > 0)) | ((x > max_val) & (g < 0)),
		0.0,  # Zero gradient
		g     # Pass gradient through
	)

	return (grad_x, None, None)


# Register custom VJP
magic_clamp.defvjp(magic_clamp_fwd, magic_clamp_bwd)


# ---------------------------------------------------------------------------
# Safetensors parameter persistence (portable, framework-agnostic).
#
# safetensors cannot store 0-dim arrays, but Faust UI parameters are commonly
# scalars (0-dim). Such leaves are reshaped to (1,) on save and their keys are
# recorded in the file's metadata under "__zero_dim__" so the original 0-dim
# shape is restored exactly on load.
# ---------------------------------------------------------------------------
def _flatten_state(tree: Mapping, prefix: str = "") -> Dict[str, np.ndarray]:
	"""Flatten a nested parameter mapping into dot-separated keys.

	Args:
		tree: Nested mapping of names to arrays (or nested mappings).
		prefix: Key prefix used during recursion.

	Returns:
		Flat dict mapping dot-separated paths to numpy arrays.
	"""
	out: Dict[str, np.ndarray] = {}
	for k, v in tree.items():
		key = f"{prefix}.{k}" if prefix else str(k)
		if isinstance(v, Mapping):
			out.update(_flatten_state(v, key))
		else:
			out[key] = np.asarray(v)
	return out


def _unflatten_state(flat: Dict[str, np.ndarray]) -> Dict[str, Any]:
	"""Rebuild a nested dict from dot-separated keys (inverse of ``_flatten_state``).

	All-digit path components are converted back to ``int`` so that list/Sequential
	indices in nnx state round-trip — nnx uses integer keys for sequences, and
	module attribute names are never all-digit.

	Args:
		flat: Flat dict mapping dot-separated paths to arrays.

	Returns:
		Nested dict reconstructed from the dotted paths.
	"""
	def _key(part: str) -> str | int:
		return int(part) if part.isdigit() else part

	out: Dict[Any, Any] = {}
	for key, value in flat.items():
		parts = key.split(".")
		d = out
		for part in parts[:-1]:
			d = d.setdefault(_key(part), {})
		d[_key(parts[-1])] = value
	return out


def _save_state_safetensors(
	pure_tree: Mapping, path: str | Path, extra_metadata: Optional[Dict[str, str]] = None
) -> None:
	"""Write a nested parameter mapping to a ``.safetensors`` file.

	Args:
		pure_tree: Nested mapping of plain arrays (no Variable wrappers).
		path: Destination ``.safetensors`` file path.
		extra_metadata: Additional string entries stored in the file's metadata
			header (e.g. DSP identity, used by ``load_params`` to verify the
			file matches the model it is loaded into).
	"""
	from safetensors.numpy import save_file

	flat = _flatten_state(pure_tree)
	zero_dim: List[str] = []
	out: Dict[str, np.ndarray] = {}
	for k, v in flat.items():
		arr = np.asarray(v)
		if arr.ndim == 0:
			# np.ascontiguousarray promotes 0-dim to (1,), so detect/reshape first.
			zero_dim.append(k)
			arr = arr.reshape(1)
		out[k] = np.ascontiguousarray(arr)
	metadata = {"__zero_dim__": json.dumps(zero_dim)}
	if extra_metadata is not None:
		metadata.update(extra_metadata)
	save_file(out, str(path), metadata=metadata)


def _load_state_safetensors(path: str | Path) -> Tuple[Dict[str, Any], Dict[str, str]]:
	"""Read a ``.safetensors`` file written by ``_save_state_safetensors``.

	Args:
		path: Source ``.safetensors`` file path.

	Returns:
		Tuple of (nested dict of arrays with original (incl. 0-dim) shapes
		restored, metadata dict from the file header).
	"""
	from safetensors import safe_open

	flat: Dict[str, np.ndarray] = {}
	with safe_open(str(path), framework="numpy") as f:
		meta = f.metadata() or {}
		for key in f.keys():
			flat[key] = f.get_tensor(key)
	zero_dim = json.loads(meta["__zero_dim__"]) if "__zero_dim__" in meta else []
	for key in zero_dim:
		flat[key] = flat[key].reshape(())
	return _unflatten_state(flat), meta


# Generated code
<<includeIntrinsic>>
<<includeclass>>

	def __repr__(self):
		name = self.__class__.__name__
		return f"{name}(sample_rate={self.sample_rate}, faust_float={self.faust_float}, use_magic_clamp={self.use_magic_clamp}, deterministic={self.deterministic}, num_inputs={self.num_inputs}, num_outputs={self.num_outputs}, is_stochastic={self.is_stochastic}, soundfile_dirs={self.soundfile_dirs})"

	def load_soundfile(self, filepath: str) -> Tuple[np.ndarray, int]:
		"""
		Load a soundfile from the given filepath.

		Args:
			filepath: Path to the soundfile

		Returns:
			Tuple of (audio data, sample rate)

		Raises:
			SoundfileLoadError: If the soundfile cannot be loaded from any search path
		"""
		if not filepath:
			raise SoundfileLoadError("Soundfile filepath cannot be empty")

		# soundfile_dirs should always include at least "".
		soundfile_dirs = [""] + list(self.soundfile_dirs)
		# Create a list of potential filepaths to check
		potential_paths = [Path(filepath)] if Path(filepath).is_absolute() else [Path(d) / filepath for d in soundfile_dirs]

		# Track all attempted paths for error message
		attempted_paths = []

		# Loop through potential paths and try to load the audio file
		for full_path in potential_paths:
			attempted_paths.append(str(full_path))
			try:
				# Suppress deprecation warnings from librosa (aifc, audioop deprecated in Python 3.13)
				with warnings.catch_warnings():
					warnings.filterwarnings("ignore", category=DeprecationWarning)
					audio, sr = librosa.load(str(full_path), mono=False, sr=None)
				if audio.ndim == 1:
					audio = np.expand_dims(audio, 0)
				return audio, sr
			except FileNotFoundError:
				# If not found at this path, continue to the next
				continue
			except Exception as e:
				# Other errors (corrupted file, unsupported format, ...) are
				# real failures for a path that exists
				raise SoundfileLoadError(f"Error loading soundfile from {full_path}: {e}") from e

		raise SoundfileLoadError(
			f"Could not load soundfile '{filepath}'. "
			f"Attempted paths: {', '.join(attempted_paths)}"
		)
	
	def add_soundfile(self, zone: str, ui_path: List[str], label: str, url: str, unnorm_funcs: Dict[str, Tuple[str, Callable]], metadata: Optional[Dict[str, str]] = None) -> None:
		"""
		Add a soundfile to the DSP.

		Supports widget metadata for configuration:
		- [param:1] - Make soundfile buffers learnable (default: 0, non-learnable)
		- [param:0] - Explicitly mark as non-learnable

		Args:
			zone: Internal variable name for the soundfile
			ui_path: UI path components for organizing the parameter
			label: Display label for the soundfile
			url: Soundfile URL in format {'file1.wav';'file2.wav';'...'} extracted by compiler from [url:...] metadata
			unnorm_funcs: Dictionary mapping labels to (zone, unnormalization_func) tuples
			metadata: Widget metadata declared in the Faust source, e.g. {"param": "1"}
		"""
		# The compiler delivers [key:value] widget metadata via the metadata
		# argument (the label itself is clean); extract_metadata also handles
		# metadata still embedded in the label string (e.g. hand-written calls).
		clean_label, label_metadata = extract_metadata(label)
		metadata = {**label_metadata, **(metadata or {})}

		# Check if soundfile should be a learnable parameter using [param:1] metadata
		is_param = metadata.get("param", "0") == "1"

		# Get URL (compiler extracts from metadata and passes as argument)
		if not url:
			raise SoundfileLoadError(f"No URL provided for soundfile '{clean_label}'")

		# Parse filepaths from URL
		# example url: {'tango.wav';'foo.wav';'bar/baz.wav'}
		filepaths = url[2:-2].split("';'")
		fLength, fOffset, fSR, offset = [], [], [], 0
		audio_data = [self.load_soundfile(filepath) for filepath in filepaths]
		num_chans = max([y.shape[0] for y, _ in audio_data])
		total_length = sum([y.shape[1] for y, _ in audio_data])
		fBuffers = jnp.zeros((num_chans, total_length), dtype=self.faust_float)
		for y, sr in audio_data:
			fSR.append(sr)
			assert y.ndim == 2
			y = jnp.array(y, dtype=self.faust_float)
			fLength.append(y.shape[1])
			fOffset.append(offset)
			fBuffers = fBuffers.at[:y.shape[0],offset:offset+y.shape[1]].set(y)
			offset += y.shape[1]

		# Build full label for UI path
		full_label = "/".join(ui_path + [clean_label])

		# Wrap buffers as Param if learnable, otherwise leave as array
		# Note: Learnable soundfiles are stored in the dict and accessed via state,
		# not through unnormalize() like regular UI parameters
		if is_param:
			fBuffers = nnx.Param(fBuffers)

		# Wrap soundfile dict with nnx.data() to prevent Flax NNX pytree errors
		soundfile_dict = {
			"fLength": jnp.array(fLength, dtype=jnp.int32),
			"fOffset": jnp.array(fOffset, dtype=jnp.int32),
			"fBuffers": fBuffers,
			"fSR": jnp.array(fSR, dtype=self.faust_float)
		}
		setattr(self, zone, nnx.data(soundfile_dict))
		
		# Store parameter metadata
		self._parameter_metadata[zone] = {
			"full_label": full_label,
			"label": clean_label,
			"type": "soundfile",
			"internal_name": zone,
			"is_param": is_param,
			"metadata": metadata,
			"num_files": len(filepaths),
		}
	
	def add_button(self, zone: str, ui_path: List[str], label: str, unnorm_funcs: Dict[str, Tuple[str, Callable]]) -> None:
		"""
		Add a button UI element.

		Args:
			zone: Internal variable name for the button
			ui_path: UI path components for organizing the parameter
			label: Display label for the button
			unnorm_funcs: Dictionary mapping labels to (zone, unnormalization_func) tuples
		"""
		full_label = "/".join(ui_path+[label])
		setattr(self, zone, nnx.Param(jnp.zeros((), dtype=self.faust_float)))
		unnorm_funcs[full_label] = (zone, lambda x: x)
		
		# Store parameter metadata
		self._parameter_metadata[zone] = {
			"full_label": full_label,
			"label": label,
			"type": "button",
			"internal_name": zone,
			"min": 0.0,
			"max": 1.0,
			"default": 0.0,
		}
	
	def add_checkbox(self, zone: str, ui_path: List[str], label: str, unnorm_funcs: Dict[str, Tuple[str, Callable]]) -> None:
		"""
		Add a checkbox UI element.

		Args:
			zone: Internal variable name for the checkbox
			ui_path: UI path components for organizing the parameter
			label: Display label for the checkbox
			unnorm_funcs: Dictionary mapping labels to (zone, unnormalization_func) tuples
		"""
		self.add_button(zone, ui_path, label, unnorm_funcs)
		# Update type in metadata
		self._parameter_metadata[zone]["type"] = "checkbox"
	
	def add_nentry(
		self, zone: str, ui_path: List[str], label: str,
		init: float, a_min: float, a_max: float, step_size: float,
		unnorm_funcs: Dict[str, Tuple[str, Callable]], scale_mode: str = "linear",
		metadata: Optional[Dict[str, str]] = None,
	) -> None:
		"""
		Gumbel-Softmax version of a FAUST nentry with configurable temperature.

		Supports widget metadata for configuration:
		- [tau:learnable] - Make temperature learnable (default: fixed)
		- [tau_init:X] - Set initial temperature value (default: 1.0)

		Args:
			zone: Internal variable name
			ui_path: UI path components
			label: Display label
			init: Initial value
			a_min: Minimum value
			a_max: Maximum value
			step_size: Step size
			unnorm_funcs: Dictionary mapping labels to unnormalization functions
			scale_mode: Scaling mode
			metadata: Widget metadata declared in the Faust source,
				e.g. {"tau": "learnable", "tau_init": "0.5"}
		"""
		# A non-positive step is Faust-legal and means "no discrete grid" (other
		# backends treat step purely as a UI hint), so there is nothing for the
		# Gumbel-softmax machinery to enumerate: register the nentry as a
		# continuous parameter instead, like a slider.
		if step_size <= 0:
			self.add_hslider(zone, ui_path, label, init, a_min, a_max, step_size, unnorm_funcs, scale_mode)
			self._parameter_metadata[zone]["type"] = "nentry"
			return

		# The compiler delivers [key:value] widget metadata via the metadata
		# argument (the label itself is clean); extract_metadata also handles
		# metadata still embedded in the label string (e.g. hand-written calls).
		clean_label, label_metadata = extract_metadata(label)
		metadata = {**label_metadata, **(metadata or {})}

		faust_float = self.faust_float
		# ---------- set up grid ----------
		full_label = "/".join(ui_path + [clean_label])
		num_steps  = int(round((a_max - a_min) / step_size)) + 1
		init_step  = int(round((init - a_min) / step_size))
		step_values = jnp.arange(num_steps, dtype=faust_float) * faust_float(step_size) + faust_float(a_min)

		# ---------- parameters ----------
		# (1) logits, initialised to favor the initial step
		logits = jnp.zeros((num_steps,), dtype=faust_float)
		logits = logits.at[init_step].set(faust_float(NENTRY_LOGITS_INIT))

		logits_zone = zone + "_logits"
		setattr(self, logits_zone, nnx.Param(logits))

		# (2) Temperature (Gumbel-softmax temperature parameter)
		# Parse tau configuration from metadata
		tau_learnable = metadata.get("tau", "fixed") == "learnable"
		tau_init = float(metadata.get("tau_init", str(NENTRY_TAU_INIT)))

		tau_zone = zone + "_tau"
		if tau_learnable:
			setattr(self, tau_zone, nnx.Param(faust_float(tau_init)))
		else:
			setattr(self, tau_zone, nnx.Variable(faust_float(tau_init)))
		
		# Add unnormalization lambda for nentry
		def make_nentry_unnorm(zone, step_values):
			def unnorm_nentry(logits, tau, gumbel_key=None):
				# Gumbel-softmax computation for differentiable discrete parameters
				# Training mode: soft Gumbel-softmax (if gumbel key provided)
				# Eval mode: hard argmax (deterministic)
				if gumbel_key is not None and not self.deterministic:
					# Training mode with gumbel key: soft Gumbel-softmax
					gumbel_noise = random.gumbel(
						gumbel_key, logits.shape, dtype=faust_float
					)
					logits_with_noise = logits + gumbel_noise
					probs = jax.nn.softmax(logits_with_noise / tau, axis=-1)
					return jnp.dot(probs, step_values)

				# Eval mode or no gumbel key: hard argmax
				index = jnp.argmax(logits, axis=-1)
				return step_values[index]

			return unnorm_nentry

		unnorm_funcs[full_label] = (zone, make_nentry_unnorm(zone, step_values))
		
		# Store parameter metadata
		self._parameter_metadata[zone] = {
			"full_label": full_label,
			"label": clean_label,
			"type": "nentry",
			"internal_name": zone,
			"min": float(a_min),
			"max": float(a_max),
			"default": float(init),
			"step": float(step_size),
			"num_options": int(num_steps),
			"scale_mode": scale_mode,
			"gumbel_softmax": True,  # Indicates this uses Gumbel-softmax
			"tau_learnable": tau_learnable,
			"tau_init": float(tau_init),
			"metadata": metadata,
		}
	
	def normalize_value(self, value: float, a_min: float, a_max: float, scale_mode: str) -> Array:
		"""
		Normalize a value from [a_min, a_max] to [0, 1] based on scale mode.

		Args:
			value: Value to normalize
			a_min: Minimum value of the parameter range
			a_max: Maximum value of the parameter range
			scale_mode: Scaling mode ("linear", "exp", or "log")

		Returns:
			Normalized value in [0, 1]

		Raises:
			InvalidScaleModeError: If scale_mode is not one of the supported modes
			InvalidParameterError: If parameter ranges are invalid
		"""
		if a_min >= a_max:
			raise InvalidParameterError(f"Invalid parameter range: min ({a_min}) must be less than max ({a_max})")

		faust_float = self.faust_float

		if scale_mode == "linear":
			return jnp.interp(value, jnp.array([a_min, a_max], dtype=faust_float),
							 jnp.array([faust_float(NORMALIZED_MIN), faust_float(NORMALIZED_MAX)], dtype=faust_float))
		elif scale_mode == "exp":
			# Map to [1, e] and take the log: the log of a value in [1, e] is
			# already the normalized position in [0, 1]; clip guards rounding.
			value_exp = jnp.interp(value, jnp.array([a_min, a_max], dtype=faust_float),
								  jnp.array([faust_float(EXP_SCALE_MIN), jnp.e], dtype=faust_float))
			value_log = jnp.log(value_exp)
			return jnp.clip(value_log, faust_float(NORMALIZED_MIN), faust_float(NORMALIZED_MAX))
		elif scale_mode == "log":
			# Geometric mapping: the exact inverse of the "log" unnormalizer,
			# which spaces [0, 1] geometrically over [a_min, a_max].
			if a_min <= 0:
				raise InvalidParameterError(
					f"Log scale requires a positive minimum; got min={a_min}"
				)
			log_min = jnp.log10(faust_float(a_min))
			log_max = jnp.log10(faust_float(a_max))
			normalized = (jnp.log10(value) - log_min) / (log_max - log_min)
			return jnp.clip(normalized, faust_float(NORMALIZED_MIN), faust_float(NORMALIZED_MAX))
		else:
			raise InvalidScaleModeError(
				f"Unknown scale mode '{scale_mode}'. "
				f"Supported modes are: 'linear', 'exp', 'log'"
			)
	
	def create_unnormalize_func(self, a_min: float, a_max: float, scale_mode: str) -> Callable[[Array], Array]:
		"""
		Create an unnormalization function for the given scale mode.

		Args:
			a_min: Minimum value of the parameter range
			a_max: Maximum value of the parameter range
			scale_mode: Scaling mode ("linear", "exp", or "log")

		Returns:
			Function that unnormalizes values from [0, 1] to [a_min, a_max]

		Raises:
			InvalidScaleModeError: If scale_mode is not one of the supported modes
			InvalidParameterError: If parameter ranges are invalid
		"""
		if a_min >= a_max:
			raise InvalidParameterError(f"Invalid parameter range: min ({a_min}) must be less than max ({a_max})")

		faust_float = self.faust_float
		pair = lambda x, y: jnp.array([faust_float(x), faust_float(y)], dtype=faust_float)

		# Use magic_clamp for better gradient flow if enabled, otherwise standard clipping
		if self.use_magic_clamp:
			clip = lambda x: magic_clamp(x, faust_float(NORMALIZED_MIN), faust_float(NORMALIZED_MAX))
		else:
			clip = lambda x: jnp.clip(x, faust_float(NORMALIZED_MIN), faust_float(NORMALIZED_MAX))

		if scale_mode == "linear":
			return lambda normalized: jnp.interp(
				clip(normalized),
				pair(NORMALIZED_MIN, NORMALIZED_MAX),
				pair(a_min, a_max)
			)
		elif scale_mode == "exp":
			return lambda normalized: jnp.interp(
				jnp.exp(clip(normalized)),
				pair(EXP_SCALE_MIN, jnp.e),
				pair(a_min, a_max)
			)
		elif scale_mode == "log":
			# Logarithmic scale: map normalized [0,1] to log space, then exponentiate
			# For [100, 10000]: 0.0→100, 0.5→1000, 1.0→10000 (geometric spacing)
			if a_min <= 0:
				raise InvalidParameterError(
					f"Log scale requires a positive minimum; got min={a_min}"
				)
			def log_unnorm(normalized):
				# Map [0,1] → [log10(a_min), log10(a_max)]
				log_min = jnp.log10(faust_float(a_min))
				log_max = jnp.log10(faust_float(a_max))
				log_val = jnp.interp(
					clip(normalized),
					pair(NORMALIZED_MIN, NORMALIZED_MAX),
					jnp.array([log_min, log_max], dtype=faust_float)
				)
				# Apply 10^x to get physical value
				return jnp.power(faust_float(10), log_val)
			return log_unnorm
		else:
			raise InvalidScaleModeError(
				f"Unknown scale mode '{scale_mode}'. "
				f"Supported modes are: 'linear', 'exp', 'log'"
			)
	
	def add_slider(self, zone: str, ui_path: List[str], label: str, init: float, a_min: float, a_max: float, step_size: float, unnorm_funcs: Dict[str, Tuple[str, Callable]], scale_mode: str = "linear") -> None:
		"""
		Add a slider UI element with the specified parameters.

		Args:
			zone: Internal variable name for the slider
			ui_path: UI path components for organizing the parameter
			label: Display label for the slider
			init: Initial value
			a_min: Minimum value
			a_max: Maximum value
			step_size: Step size declared in the Faust source (metadata only;
				slider values are not quantized)
			unnorm_funcs: Dictionary mapping labels to (zone, unnormalization_func) tuples
			scale_mode: Scaling mode ("linear", "exp", or "log")
		"""
		faust_float = self.faust_float
		full_label = "/".join(ui_path + [label])
		# Store parameter metadata
		self._parameter_metadata[zone] = {
			"full_label": full_label,
			"label": label,
			"type": "slider",
			"internal_name": zone,
			"min": a_min,
			"max": a_max,
			"default": init,
			"step": step_size,
			"scale_mode": scale_mode,
		}

		init, a_min, a_max = faust_float(init), faust_float(a_min), faust_float(a_max)

		# Normalize init value to [0, 1] based on scale mode
		normalized_init = self.normalize_value(init, a_min, a_max, scale_mode)

		# Create the normalized parameter with label as name
		setattr(self, zone, nnx.Param(normalized_init))

		# Create and store the unnormalization function
		unnorm_func = self.create_unnormalize_func(a_min, a_max, scale_mode)
		unnorm_funcs[full_label] = (zone, unnorm_func)

	def add_hslider(self, zone: str, ui_path: List[str], label: str, init: float, a_min: float, a_max: float, step_size: float, unnorm_funcs: Dict[str, Tuple[str, Callable]], scale_mode: str) -> None:
		"""Add a horizontal slider UI element. See add_slider for details."""
		self.add_slider(zone, ui_path, label, init, a_min, a_max, step_size, unnorm_funcs, scale_mode)
		# Update type in metadata
		self._parameter_metadata[zone]["type"] = "hslider"

	def add_vslider(self, zone: str, ui_path: List[str], label: str, init: float, a_min: float, a_max: float, step_size: float, unnorm_funcs: Dict[str, Tuple[str, Callable]], scale_mode: str) -> None:
		"""Add a vertical slider UI element. See add_slider for details."""
		self.add_slider(zone, ui_path, label, init, a_min, a_max, step_size, unnorm_funcs, scale_mode)
		# Update type in metadata
		self._parameter_metadata[zone]["type"] = "vslider"

	def add_bargraph(self, zone: str, ui_path: List[str], label: str, a_min: float, a_max: float, unnorm_funcs: Dict[str, Tuple[str, Callable]]) -> None:
		"""
		Add a bargraph UI element (output-only).

		Args:
			zone: Internal variable name for the bargraph
			ui_path: UI path components for organizing the parameter
			label: Display label for the bargraph
			a_min: Minimum display value
			a_max: Maximum display value
			unnorm_funcs: Dictionary mapping labels to (zone, unnormalization_func) tuples
		"""
		# Bargraphs are output-only, no parameters needed
		# But we can still store metadata
		self._parameter_metadata[zone] = {
			"full_label": "/".join(ui_path + [label]),
			"label": label,
			"type": "hbargraph",
			"internal_name": zone,
			"min": a_min,
			"max": a_max,
			"output_only": True,
		}
	
	def add_hbargraph(self, zone: str, ui_path: List[str], label: str, a_min: float, a_max: float, unnorm_funcs: Dict[str, Tuple[str, Callable]]) -> None:
		"""Add a horizontal bargraph UI element. See add_bargraph for details."""
		self.add_bargraph(zone, ui_path, label, a_min, a_max, unnorm_funcs)
		self._parameter_metadata[zone]["type"] = "hbargraph"

	def add_vbargraph(self, zone: str, ui_path: List[str], label: str, a_min: float, a_max: float, unnorm_funcs: Dict[str, Tuple[str, Callable]]) -> None:
		"""Add a vertical bargraph UI element. See add_bargraph for details."""
		self.add_bargraph(zone, ui_path, label, a_min, a_max, unnorm_funcs)
		self._parameter_metadata[zone]["type"] = "vbargraph"

	def _finalize_interface(self) -> None:
		"""Attach JSON-derived metadata and build the parameter key-resolution map.

		Called by the generated ``__init__`` after ``build_interface``. Walks the
		compiled-in ``json_metadata`` UI tree to attach each widget's Faust
		``shortname`` (guaranteed unique per DSP) to ``_parameter_metadata``, then
		builds ``_key_to_zone`` so parameter dicts may be keyed by zone name,
		shortname, or full label path. When the same string appears in several
		domains, zone names take precedence over shortnames over full labels.
		"""
		shortnames: Dict[str, str] = {}

		def walk(items: List[Dict[str, Any]]) -> None:
			for item in items:
				if "items" in item:
					walk(item["items"])
				elif "varname" in item and "shortname" in item:
					shortnames[item["varname"]] = item["shortname"]

		walk(self.json_metadata["ui"])

		for zone, meta in self._parameter_metadata.items():
			if zone in shortnames:
				meta["shortname"] = shortnames[zone]

		# Scalar input parameters only: bargraphs are output-only and soundfiles
		# live in the carry, so neither is addressable through a params dict.
		input_params = {
			zone: meta
			for zone, meta in self._parameter_metadata.items()
			if not meta.get("output_only") and meta["type"] != "soundfile"
		}
		key_to_zone: Dict[str, str] = {}
		# Insertion order sets precedence: later writes win, so register the
		# weakest key domain (full labels) first and the strongest (zones) last.
		for zone, meta in input_params.items():
			key_to_zone[meta["full_label"]] = zone
		for zone, meta in input_params.items():
			if "shortname" in meta:
				key_to_zone[meta["shortname"]] = zone
		for zone in input_params:
			key_to_zone[zone] = zone
		self._key_to_zone = key_to_zone

	def _resolve_param_keys(self, params: Mapping) -> Dict[str, Any]:
		"""Return a zone-keyed copy of ``params``.

		Keys may be zone names (``fHslider0``), Faust shortnames (``gain_db``),
		or full label paths (``Gain/gain_db``). nentry logits/temperature entries
		may use any of those stems with a ``_logits``/``_tau`` suffix.

		Args:
			params: Parameter dict keyed by zone, shortname, or full label.

		Returns:
			Dict with the same values keyed by zone.

		Raises:
			UnknownParameterError: If a key matches no parameter of this DSP.
		"""
		resolved: Dict[str, Any] = {}
		for key, value in params.items():
			if key in self._key_to_zone:
				resolved[self._key_to_zone[key]] = value
			elif key.endswith("_logits") and key[: -len("_logits")] in self._key_to_zone:
				resolved[self._key_to_zone[key[: -len("_logits")]] + "_logits"] = value
			elif key.endswith("_tau") and key[: -len("_tau")] in self._key_to_zone:
				resolved[self._key_to_zone[key[: -len("_tau")]] + "_tau"] = value
			else:
				raise UnknownParameterError(
					f"Unknown parameter '{key}'. Valid keys are zones, shortnames, "
					f"or full labels: {sorted(self._key_to_zone)}"
				)
		return resolved

	def random_uniform(self, rng: Array) -> Array:
		"""
		Generate a random uniform value in the range [0, 1] using JAX's PRNG.

		Args:
			rng: JAX random number generator key

		Returns:
			Random value from uniform distribution U(0, 1)
		"""
		return random.uniform(rng, shape=(), minval=0.0, maxval=1.0, dtype=self.faust_float)

	def random_normal(self, rng: Array) -> Array:
		"""
		Generate a random normal (Gaussian) value with mean=0, std=1 using JAX's PRNG.

		Args:
			rng: JAX random number generator key

		Returns:
			Random value from standard normal distribution N(0, 1)
		"""
		return random.normal(rng, shape=(), dtype=self.faust_float)

	def random_exponential(self, rng: Array, rate: float = 1.0) -> Array:
		"""
		Generate a random exponential value using JAX's PRNG.

		The exponential distribution models time between events in a Poisson process.
		Useful for decay times, inter-arrival times, and stochastic envelopes.

		Args:
			rng: JAX random number generator key
			rate: Rate parameter (λ, must be > 0). Mean = 1/rate. Default: 1.0

		Returns:
			Random value from exponential distribution with specified rate
		"""
		# JAX's exponential uses scale parameter (1/rate)
		return random.exponential(rng, shape=(), dtype=self.faust_float) / rate

	def random_bernoulli(self, rng: Array, p: float = 0.5) -> Array:
		"""
		Generate a random binary value (0 or 1) using JAX's PRNG.

		Useful for random gates, triggers, coin flips, and binary decisions.

		Args:
			rng: JAX random number generator key
			p: Probability of returning 1 (must be in [0, 1]). Default: 0.5

		Returns:
			Random value: 0.0 or 1.0 based on probability p
		"""
		return self.faust_float(random.bernoulli(rng, p=p, shape=()))

	def random_beta(self, rng: Array, a: float = 2.0, b: float = 2.0) -> Array:
		"""
		Generate a random beta value using JAX's PRNG.

		The beta distribution generates values in [0, 1] with configurable skew.
		With a=b=2 (default), produces a symmetric bell-shaped distribution centered at 0.5.

		Args:
			rng: JAX random number generator key
			a: Alpha parameter (shape parameter, must be > 0). Default: 2.0
			b: Beta parameter (shape parameter, must be > 0). Default: 2.0

		Returns:
			Random value from beta(a, b) distribution in [0, 1]
		"""
		return random.beta(rng, a=a, b=b, shape=(), dtype=self.faust_float)

	def _extract_rng_key(
		self, rngs: Optional[rnglib.Rngs | rnglib.RngStream | Array] = None
	) -> Array:
		"""
		Extract a JAX random key from various RNG sources.

		Args:
			rngs: RNG source (Rngs, RngStream, or JAX array)

		Returns:
			JAX random key

		Raises:
			InvalidRNGError: If rngs is not a valid type
		"""
		rngs = first_from(
			rngs, self.rngs,
			error_msg="This DSP is stochastic (it calls random_* foreign functions), "
			"so an RNG is required: pass `rngs` to the call or construct the module with one"
		)

		if isinstance(rngs, Array):
			return rngs
		elif isinstance(rngs, rnglib.Rngs):
			return rngs[self.rng_collection]()
		elif isinstance(rngs, rnglib.RngStream):
			return rngs()
		else:
			raise InvalidRNGError(
				f"`rngs` must be JAX array, Rngs or RngStream, got {type(rngs).__name__}"
			)

	def _extract_gumbel_key(
		self, rngs: Optional[rnglib.Rngs | rnglib.RngStream] = None
	) -> Optional[Array]:
		"""
		Extract a Gumbel PRNG key for nentry Gumbel-softmax sampling.

		Must be called outside JAX transforms to avoid TraceContextError
		from RngCount mutation.

		Uses the ``nentry`` RNG name to avoid collision with
		``jax.random.gumbel`` which Flax NNX binds onto ``Rngs``.

		Returns:
			JAX PRNG key if nentry is available and model is in
			training mode, None otherwise.
		"""
		if self.deterministic:
			return None
		# Fall back to the module's own rngs; a missing RNG is not an error here
		# (nentry sampling is simply skipped), so don't use first_from(), which
		# raises when every candidate is None.
		if rngs is None:
			rngs = self.rngs
		if isinstance(rngs, rnglib.Rngs) and "nentry" in rngs:
			return rngs.nentry()
		# note: don't check if rngs is Array because we require the user to instantiate nnx.Rngs with an `nentry` kwarg.
		return None

	def _split_gumbel_keys(self, gumbel_key: Optional[Array]) -> Dict[str, Array]:
		"""Split one PRNG key into per-nentry Gumbel-softmax subkeys.

		Args:
			gumbel_key: PRNG key to split, or None.

		Returns:
			Dict mapping each nentry zone to its own subkey; empty when
			gumbel_key is None or the DSP has no nentries.
		"""
		nentry_zones = [zone for _, (zone, _) in self._unnorm_funcs.items()
						if hasattr(self, f"{zone}_logits")]
		if gumbel_key is None or not nentry_zones:
			return {}
		if len(nentry_zones) == 1:
			return {nentry_zones[0]: gumbel_key}
		return dict(zip(nentry_zones, random.split(gumbel_key, len(nentry_zones))))

	def _reject_normalized_only_keys(self, provided: Dict[str, Any]) -> None:
		"""Raise if a physical parameter dict contains nentry logits/tau entries.

		The generated tick reads only plain zone keys from the physical dict,
		so logits/tau entries would be silently ignored there; they belong to
		the normalized parameter domain.

		Args:
			provided: Zone-keyed dict returned by ``_resolve_param_keys``.

		Raises:
			ValueError: If any key carries a ``_logits``/``_tau`` suffix.
		"""
		suffixed = sorted(k for k in provided if k.endswith(("_logits", "_tau")))
		if suffixed:
			raise ValueError(
				f"nentry logits/tau entries {suffixed} are normalized-domain "
				f"inputs; pass them via normalized_params= (physical params= "
				f"accepts only plain parameter values)"
			)

	def unnormalize(self, gumbel_key: Optional[Array] = None) -> Dict[str, ArrayLike]:
		"""
		Unnormalize all UI parameters from [0, 1] to their original ranges.

		Args:
			gumbel_key: Optional pre-extracted JAX PRNG key for Gumbel-softmax
				sampling of nentry parameters. Required for training mode
				(deterministic=False) when nentry params exist.
				Extract before calling: ``gumbel_key = self.rngs.nentry()``

		Returns:
			Dictionary mapping zones to unnormalized parameter values
		"""
		params = {}

		# Split the gumbel key for each nentry parameter
		gumbel_keys = self._split_gumbel_keys(gumbel_key)

		# Simply use the stored unnormalization functions
		for label, (zone, unnorm_func) in self._unnorm_funcs.items():
			# Check if it's a nentry (needs module as arg)
			if hasattr(self, f"{zone}_logits"):
				logits = getattr(self, f"{zone}_logits")[...]
				tau = getattr(self, f"{zone}_tau")[...]
				params[zone] = unnorm_func(logits, tau, gumbel_keys.get(zone))
			elif hasattr(self, zone):
				# Regular parameter
				normalized_value = getattr(self, zone)[...]
				params[zone] = unnorm_func(normalized_value)
			else:
				raise ValueError(f"Zone not found: {zone}")

		return params

	def unnormalize_params(self, normalized_params: Dict[str, ArrayLike], gumbel_key: Optional[Array] = None) -> Dict[str, ArrayLike]:
		"""
		Unnormalize parameters to their physical ranges.

		This is useful when you have normalized parameters (e.g., from an RL policy)
		and need to convert them to physical values.

		Args:
			normalized_params: Dict mapping zones to normalized values
			                   - Continuous params: values in [0, 1]
			                   - Categorical params: logits, tau, or discrete values
			gumbel_key: Optional PRNG key for Gumbel-softmax sampling of the
				provided nentry logits (training mode). Without it, logits
				collapse to a hard argmax: tau has no effect and their
				gradients are identically zero.

		Returns:
			Dict mapping zones to unnormalized (physical) values

		Only entries for the provided keys are returned; merge with
		:meth:`unnormalize` (or let ``__call__``/``process_block`` do it) to get
		a complete parameter dict. Keys may be zones, shortnames, or full labels.

		Example:
			>>> # RL policy outputs continuous [0,1] and categorical logits
			>>> normalized = {
			...     'fHslider0': 0.5,  # Continuous
			...     'fEntry0_logits': jnp.array([2.0, 0.1, -1.0]),  # Categorical
			...     'fEntry0_tau': 1.0
			... }
			>>> # Convert to physical ranges
			>>> physical = model.unnormalize_params(normalized)
			>>> # Use in __call__
			>>> outputs = model(inputs, params=physical)
		"""
		normalized_params = self._resolve_param_keys(normalized_params)
		unnormalized = {}
		gumbel_keys = self._split_gumbel_keys(gumbel_key)

		for label, (zone, unnorm_func) in self._unnorm_funcs.items():
			# nentry parameters are driven by logits (+ optional tau) or by an
			# already-selected discrete value under the plain zone key.
			if hasattr(self, f"{zone}_logits"):
				if f"{zone}_logits" in normalized_params:
					logits = normalized_params[f"{zone}_logits"]
					if f"{zone}_tau" in normalized_params:
						tau = normalized_params[f"{zone}_tau"]
					else:
						tau = getattr(self, f"{zone}_tau")[...]
					unnormalized[zone] = unnorm_func(logits, tau, gumbel_keys.get(zone))
				elif f"{zone}_tau" in normalized_params:
					# tau provided without logits: sample the module's own
					# logits at the requested temperature.
					logits = getattr(self, f"{zone}_logits")[...]
					tau = normalized_params[f"{zone}_tau"]
					unnormalized[zone] = unnorm_func(logits, tau, gumbel_keys.get(zone))
				elif zone in normalized_params:
					# Direct value provided (e.g., from categorical policy after
					# sampling). Pass through - it's already the selected value.
					unnormalized[zone] = normalized_params[zone]
			elif zone in normalized_params:
				# Regular parameter - apply unnorm_func
				normalized_value = normalized_params[zone]
				unnormalized[zone] = unnorm_func(normalized_value)

		return unnormalized
	
	def get_parameter_metadata(self) -> Dict[str, Dict[str, Any]]:
		"""
		Get metadata for all parameters.

		Returns:
			Dictionary mapping internal names to parameter metadata
		"""
		return self._parameter_metadata.copy()

	def get_continuous_params(self, batch_size: Optional[int] = None, normalized: bool = True) -> Dict[str, ArrayLike]:
		"""
		Get continuous parameters (sliders, buttons), optionally batched.

		Returns only continuous parameters (excludes nentrys/categorical).
		This is what RL policies using Beta/Gaussian distributions should output.

		Args:
			batch_size: If provided, returns batched parameters
			normalized: If True, returns [0, 1] values; if False, returns physical values

		Returns:
			Dictionary mapping zones to continuous parameter values

		Example:
			>>> # Normalized continuous params (for RL policy)
			>>> norm = model.get_continuous_params(normalized=True)
			>>> # {'fHslider0': Array(0.5), ...}  # All in [0, 1]
			>>>
			>>> # Physical continuous params
			>>> phys = model.get_continuous_params(normalized=False)
			>>> # {'fHslider0': Array(1000.0), ...}  # Physical values
			>>>
			>>> # Batched for RL vmap
			>>> norm_batch = model.get_continuous_params(batch_size=4, normalized=True)
		"""
		continuous = {}

		# Iterate over parameter metadata for explicit type checking
		for zone, metadata in self._parameter_metadata.items():
			param_type = metadata["type"]

			# Only include continuous UI parameters (exclude nentrys, soundfiles, bargraphs)
			if param_type in ["slider", "hslider", "vslider", "button", "checkbox"]:
				if normalized:
					# Return normalized [0, 1] value
					continuous[zone] = getattr(self, zone)[...]
				else:
					# Return physical (unnormalized) value
					_, unnorm_func = self._unnorm_funcs[metadata["full_label"]]
					continuous[zone] = unnorm_func(getattr(self, zone)[...])

		if batch_size is None:
			return continuous

		# Tile to add batch dimension
		return jax.tree.map(
			lambda x: jnp.tile(x, (batch_size,) + (1,) * x.ndim),
			continuous
		)

	def get_categorical_params(self, batch_size: Optional[int] = None) -> Dict[str, Dict[str, ArrayLike]]:
		"""
		Get categorical parameters (nentrys), optionally batched.

		Returns nentry parameters with their logits and tau values.
		RL policies should handle these separately (e.g., categorical distribution).

		Args:
			batch_size: If provided, returns batched parameters

		Returns:
			Dictionary mapping zones to {'logits': ..., 'tau': ...}

		Example:
			>>> # Get categorical params for RL
			>>> cat = model.get_categorical_params()
			>>> # {'fEntry0': {'logits': Array([0, 1, 0, 0]), 'tau': Array(1.0)}}
			>>>
			>>> # Batched for RL vmap
			>>> cat_batch = model.get_categorical_params(batch_size=4)
		"""
		categorical = {}

		# Iterate over parameter metadata for explicit type checking
		for zone, metadata in self._parameter_metadata.items():
			param_type = metadata["type"]

			# Only include nentry parameters
			if param_type == "nentry":
				# Access logits and tau (works for both nnx.Param and nnx.Variable)
				logits = getattr(self, f"{zone}_logits")[...]
				tau = getattr(self, f"{zone}_tau")[...]

				categorical[zone] = {
					'logits': logits,
					'tau': tau
				}

		if batch_size is None:
			return categorical

		# Tile to add batch dimension
		return jax.tree.map(
			lambda x: jnp.tile(x, (batch_size,) + (1,) * x.ndim),
			categorical
		)

	def label_to_zone(self, label: str) -> str:
		"""
		Convert a parameter key to its corresponding zone (internal parameter name).

		Zones are the internal variable names used by Faust (e.g., 'fHslider0',
		'fEntry2'). Accepted keys are full label paths (e.g. 'DX7/Global/LFO/Speed'),
		Faust shortnames (e.g. 'Speed'), or zone names themselves.

		Args:
			label: Full label path, shortname, or zone name

		Returns:
			The zone name (e.g., 'fHslider18')

		Raises:
			UnknownParameterError: If the key doesn't match any parameter

		Example:
			>>> zone = model.label_to_zone('DX7/Global/LFO/Speed')
			>>> # 'fHslider18'
		"""
		if label in self._key_to_zone:
			return self._key_to_zone[label]
		raise UnknownParameterError(
			f"Unknown parameter '{label}'. Valid keys are zones, shortnames, "
			f"or full labels: {sorted(self._key_to_zone)}"
		)

	def params_from_labels(self, label_params: Dict[str, Any]) -> Dict[str, Any]:
		"""
		Convert a parameter dict keyed by labels/shortnames to one keyed by zones.

		This is a thin public wrapper over the key resolution that
		``__call__``/``process_block`` already apply to their parameter dicts;
		use it when you need explicit zone keys (e.g. to address ``nnx.Param``
		attributes directly).

		Args:
			label_params: Dict keyed by full label path, shortname, or zone
			              (e.g., {'DX7/Global/LFO/Speed': 50.0, ...})

		Returns:
			Dict mapping zones to values
			(e.g., {'fHslider18': 50.0, ...})

		Raises:
			UnknownParameterError: If any key doesn't match a known parameter
		"""
		return self._resolve_param_keys(label_params)

	def with_defaults(self, partial_params: Dict[str, Any]) -> Dict[str, ArrayLike]:
		"""
		Merge partial parameters with defaults, returning a complete parameter dict.

		Use this when you have a subset of parameters and want to fill in the rest
		with the model's default values. This method validates that all provided
		keys are known parameters. ``__call__`` and ``process_block`` apply the
		same merge to their ``params`` argument, so calling this yourself is only
		needed when you want the completed dict (e.g. to inspect or cache it).

		Args:
			partial_params: Dict keyed by zone, shortname, or full label.

		Returns:
			Complete zone-keyed parameter dict, using provided values where
			available and defaults elsewhere.

		Raises:
			UnknownParameterError: If any key doesn't match a known parameter

		Example:
			>>> # Only specify the parameters you care about
			>>> partial = {'Speed': 50.0, 'Delay': 10.0}
			>>> full_params = model.with_defaults(partial)
			>>> # full_params contains ALL parameters, with defaults for unspecified ones
			>>> audio = model(inputs, params=full_params)
		"""
		return self._prepare_params(partial_params, None, None)

	def initialize_carry(self) -> Dict[str, ArrayLike]:
		"""
		Initialize the carry state for real-time processing.

		The carry state contains all stateful components needed for processing,
		including delay lines, filter states, and other memory elements.

		Returns:
			Dictionary containing all stateful components (delays, filter states, soundfiles, etc.)
		"""		
		# Initialize the full state using fast numpy
		state = self._initialize_carry()

		# Add soundfiles to state if they exist
		# Soundfiles are wrapped with nnx.data() for Flax NNX compatibility
		for zone, metadata in self._parameter_metadata.items():
			if metadata["type"] == "soundfile":
				# nnx.data() creates a transparent wrapper, just add it directly
				state[zone] = getattr(self, zone)

		# Convert numpy to JAX arrays. Floating leaves follow faust_float so the
		# carry dtype stays coherent regardless of the ambient jax_enable_x64
		# setting (init constants are computed with 64-bit numpy scalars).
		def to_jax(leaf):
			arr = jnp.asarray(leaf)
			if jnp.issubdtype(arr.dtype, jnp.floating):
				return arr.astype(self.faust_float)
			return arr

		state = jax.tree.map(to_jax, state)

		return state

	def _param_labels(self) -> Dict[str, str]:
		"""Map each input parameter zone to its human-readable full label.

		Bargraphs are excluded: they are output-only displays, not saved
		parameters. The map serves as a lightweight identity for the compiled
		DSP — two different DSPs can share generic zone names like
		``fHslider0``, but they will rarely also share the full UI label paths.

		Returns:
			Dict mapping zones (e.g. ``fHslider0``) to full labels
			(e.g. ``Synth/Oscillator/Frequency``).
		"""
		return {
			zone: meta["full_label"]
			for zone, meta in self._parameter_metadata.items()
			if not meta.get("output_only")
		}

	def save_params(self, path: str | Path) -> None:
		"""Save the model's learnable parameters to a ``.safetensors`` file.

		Serializes every ``nnx.Param`` leaf (UI parameters, nentry logits,
		learnable soundfile buffers, ...) into a portable, framework-agnostic
		safetensors file. Non-trainable state (fixed temperatures, RNG counters,
		soundfile metadata) is reconstructed at construction time and is not saved.

		The file's metadata header records the DSP class name and the
		zone-to-label map so that :meth:`load_params` can verify the file was
		saved from the same compiled DSP.

		Args:
			path: Destination ``.safetensors`` file path.
		"""
		extra_metadata = {
			"__dsp_class__": type(self).__name__,
			"__labels__": json.dumps(self._param_labels()),
		}
		_save_state_safetensors(
			nnx.to_pure_dict(nnx.state(self, nnx.Param)), path, extra_metadata
		)

	def load_params(self, path: str | Path, strict: bool = True) -> None:
		"""Load learnable parameters in-place from a ``.safetensors`` file.

		The file must have been written by :meth:`save_params` for a model with
		the same structure (e.g. the same compiled DSP). Because different DSPs
		reuse generic zone names (most DSPs have an ``fHslider0``), a file from
		the wrong DSP could otherwise load without complaint and silently
		produce wrong values — so by default the parameter names and UI labels
		recorded in the file are checked against this model first.

		Args:
			path: Source ``.safetensors`` file path.
			strict: If True (default), raise :class:`UnknownParameterError`
				unless the file's parameter set and UI labels exactly match this
				model's. If False, skip the checks and load only the parameters
				present in both the file and the model (useful when transferring
				values between related DSP variants).

		Raises:
			UnknownParameterError: If ``strict`` is True and the file does not
				match this model.
		"""
		tree, metadata = _load_state_safetensors(path)
		flat_file = _flatten_state(tree)
		model_keys = set(_flatten_state(nnx.to_pure_dict(nnx.state(self, nnx.Param))))

		if not strict:
			kept = {k: v for k, v in flat_file.items() if k in model_keys}
			nnx.update(self, _unflatten_state(kept))
			return

		saved_class = metadata.get("__dsp_class__", "<unknown>")
		missing = sorted(model_keys - set(flat_file))
		unexpected = sorted(set(flat_file) - model_keys)
		if missing or unexpected:
			raise UnknownParameterError(
				f"'{path}' (saved from DSP class '{saved_class}') does not match "
				f"{type(self).__name__}: parameters missing from the file: {missing}; "
				f"parameters not in this model: {unexpected}. "
				f"Pass strict=False to load only the overlapping parameters."
			)

		if "__labels__" in metadata:
			file_labels = json.loads(metadata["__labels__"])
			model_labels = self._param_labels()
			if file_labels != model_labels:
				differing = {
					zone: (file_labels.get(zone), model_labels.get(zone))
					for zone in sorted(set(file_labels) | set(model_labels))
					if file_labels.get(zone) != model_labels.get(zone)
				}
				details = ", ".join(
					f"{zone}: file={file_label!r} vs model={model_label!r}"
					for zone, (file_label, model_label) in differing.items()
				)
				raise UnknownParameterError(
					f"'{path}' (saved from DSP class '{saved_class}') has the same "
					f"parameter names as {type(self).__name__} but different UI "
					f"labels, so it comes from a different DSP: {details}. "
					f"Pass strict=False to load anyway."
				)

		nnx.update(self, tree)

	def _get_bargraph_zones(self) -> list:
		"""Return list of bargraph zone names (output-only parameters)."""
		return [
			zone for zone, meta in self._parameter_metadata.items()
			if meta.get("output_only")
		]

	def _prepare_params(
		self,
		params: Optional[Dict[str, ArrayLike]],
		normalized_params: Optional[Dict[str, ArrayLike]],
		gumbel_key: Optional[Array],
	) -> Dict[str, ArrayLike]:
		"""Build the complete zone-keyed physical parameter dict for one call.

		Starts from the module's own parameter state (defaults), then overrides
		with the provided physical ``params`` or ``normalized_params``. Keys may
		be zones, shortnames, or full labels; unknown keys raise. Values are
		cast to ``faust_float`` so weakly-typed Python scalars don't change the
		jitted avals between calls (which would force a retrace).

		Args:
			params: Physical parameter values, or None.
			normalized_params: Normalized parameter values (continuous in
				[0, 1]; nentries as logits/tau or already-selected values),
				or None. Mutually exclusive with ``params``.
			gumbel_key: PRNG key for Gumbel-softmax sampling of nentry defaults.

		Returns:
			Zone-keyed dict covering every input parameter of the DSP.

		Raises:
			ValueError: If both ``params`` and ``normalized_params`` are given.
			UnknownParameterError: If a key matches no parameter of this DSP.
		"""
		if params is not None and normalized_params is not None:
			raise ValueError("Cannot provide both params and normalized_params")

		complete = self.unnormalize(gumbel_key=gumbel_key)

		if params is not None:
			provided = self._resolve_param_keys(params)
			self._reject_normalized_only_keys(provided)
		elif normalized_params is not None:
			provided = self.unnormalize_params(normalized_params, gumbel_key=gumbel_key)
		else:
			provided = {}

		for zone, value in provided.items():
			complete[zone] = value if isinstance(value, Array) else jnp.asarray(value, dtype=self.faust_float)

		return complete

	def process_block(
		self,
		carry: Dict[str, ArrayLike],
		inputs: Optional[ArrayLike] = None,
		params: Optional[Dict[str, ArrayLike]] = None,
		normalized_params: Optional[Dict[str, ArrayLike]] = None,
		*,
		num_samples: Optional[int] = None,
		unroll: int = 1,
		rngs: Optional[rnglib.Rngs | rnglib.RngStream | Array] = None,
	) -> Tuple[Dict[str, Array], Array]:
		"""
		Process one block of audio and return updated state.

		Args:
			carry: State dictionary from previous block
			inputs: Input audio block of shape (num_inputs, block_size).
				For generators (num_inputs == 0) it may be omitted; pass
				``num_samples`` instead.
			params: Optional physical parameter dict
			normalized_params: Optional normalized parameter dict
			                   - Continuous params: values in [0, 1]
			                   - Categorical params: logits, tau, or discrete values
			num_samples: Block size when ``inputs`` is omitted (generators only)
			unroll (int): unroll argument for nnx.scan
			rngs: RNG source (Rngs, RngStream, or raw JAX key). Only consulted
				when the DSP is stochastic (``is_stochastic``) or samples
				nentries (training mode with an ``nentry`` stream).

		Returns:
			Tuple of (new_carry, output_block) where:
			- new_carry is the updated state dictionary
			- output_block has shape (num_outputs, block_size)
			The carry-first order matches ``tick`` and Flax RNN cells.

		Note:
			Provide either params OR normalized_params, not both. Keys may be
			zones ("fHslider0"), Faust shortnames ("gain_db"), or full labels
			("Gain/gain_db"); missing parameters use the module's own values
			and unknown keys raise UnknownParameterError.
			- params: Use when you have physical values (e.g., freq=440.0)
			- normalized_params: Use for RL (continuous [0,1] + categorical logits/tau)

		Bargraph outputs:
			Controlled by ``return_bargraphs`` (constructor parameter, default False).
			When True, a third element is always returned:
			``carry, outputs, bargraphs = model.process_block(carry, inputs)``
			where bargraphs is a dict mapping zone names to arrays of shape (block_size,).
			If the DSP has no bargraphs, the dict is empty.
			When False (default), only (new_carry, outputs) is returned.
		"""
		if inputs is None:
			if self.num_inputs != 0:
				raise ValueError(
					f"This DSP has {self.num_inputs} input channel(s); `inputs` is required"
				)
			if num_samples is None:
				raise ValueError("Provide `num_samples` when `inputs` is omitted")
			inputs = jnp.zeros((0, num_samples), dtype=self.faust_float)
		else:
			inputs = jnp.asarray(inputs, dtype=self.faust_float)
			if inputs.shape[0] != self.num_inputs:
				raise ValueError(
					f"Expected inputs of shape ({self.num_inputs}, block_size); "
					f"got {inputs.shape}"
				)
			if num_samples is not None and num_samples != inputs.shape[-1]:
				raise ValueError(
					f"num_samples={num_samples} contradicts inputs.shape[-1]={inputs.shape[-1]}"
				)
		length = inputs.shape[-1]

		# Extract RNG keys before entering transforms
		gumbel_key = self._extract_gumbel_key(rngs)
		params = self._prepare_params(params, normalized_params, gumbel_key)

		bargraph_zones = self._get_bargraph_zones()

		# Pre-populate bargraph keys so the params pytree is stable across scan steps
		for zone in bargraph_zones:
			if zone not in params:
				params[zone] = self.faust_float(0.0)

		faust_float = self.faust_float

		# Per-sample bargraph values are only collected (and stacked by the
		# scan) when the caller asked for them.
		return_bargraphs = self.return_bargraphs

		if self.is_stochastic:
			# One PRNG key per sample, threaded through the scan
			rng_key = self._extract_rng_key(rngs)
			scan_rngs = random.split(rng_key, length)

			def scan_body(carry_and_params, x, _rng):
				carry, params = carry_and_params
				new_carry, y = self.tick(params, carry, x, _rng)
				ys = (y, {zone: params[zone] for zone in bargraph_zones}) if return_bargraphs else y
				# Cast bargraph values to faust_float so carry dtype stays consistent
				for zone in bargraph_zones:
					params[zone] = faust_float(params[zone])
				return (new_carry, params), ys

			(new_carry, _), scanned = nnx.scan(
				scan_body,
				length=length,
				unroll=unroll,
				in_axes=(nnx.Carry, 1, 0),
				out_axes=(nnx.Carry, (1, 0)) if return_bargraphs else (nnx.Carry, 1),
			)((carry, params), inputs, scan_rngs)
		else:
			# Deterministic DSP: no per-sample keys to split or thread
			def scan_body(carry_and_params, x):
				carry, params = carry_and_params
				new_carry, y = self.tick(params, carry, x)
				ys = (y, {zone: params[zone] for zone in bargraph_zones}) if return_bargraphs else y
				# Cast bargraph values to faust_float so carry dtype stays consistent
				for zone in bargraph_zones:
					params[zone] = faust_float(params[zone])
				return (new_carry, params), ys

			(new_carry, _), scanned = nnx.scan(
				scan_body,
				length=length,
				unroll=unroll,
				in_axes=(nnx.Carry, 1),
				out_axes=(nnx.Carry, (1, 0)) if return_bargraphs else (nnx.Carry, 1),
			)((carry, params), inputs)

		if return_bargraphs:
			outputs, bargraph_data = scanned
			return new_carry, outputs, bargraph_data
		return new_carry, scanned

	def __call__(
		self,
		inputs: Optional[ArrayLike] = None,
		params: Optional[Dict[str, ArrayLike]] = None,
		normalized_params: Optional[Dict[str, ArrayLike]] = None,
		*,
		num_samples: Optional[int] = None,
		unroll: int = 1,
		rngs: Optional[rnglib.Rngs | rnglib.RngStream | Array] = None,
	) -> Array:
		"""
		Process audio through the DSP, starting from a fresh state.

		Equivalent to ``process_block`` with ``initialize_carry()`` and the
		final carry discarded; use ``process_block`` directly for streaming.

		Args:
			inputs: Input audio of shape (num_inputs, length). For generators
				(num_inputs == 0) it may be omitted; pass ``num_samples`` instead.
			params: Optional physical parameter dict
			normalized_params: Optional normalized parameter dict
			                   - Continuous params: values in [0, 1]
			                   - Categorical params: logits, tau, or discrete values
			num_samples: Output length when ``inputs`` is omitted (generators only)
			unroll: Unroll factor for scan
			rngs: RNG source (Rngs, RngStream, or raw JAX key). Only consulted
				when the DSP is stochastic (``is_stochastic``) or samples
				nentries (training mode with an ``nentry`` stream).

		Returns:
			Output audio of shape (num_outputs, length); with
			``return_bargraphs`` enabled, a tuple of (outputs, bargraphs).

		Note:
			Provide either params OR normalized_params, not both. Keys may be
			zones ("fHslider0"), Faust shortnames ("gain_db"), or full labels
			("Gain/gain_db"); missing parameters use the module's own values
			and unknown keys raise UnknownParameterError.
			- params: Use when you have physical values (e.g., freq=440.0)
			- normalized_params: Use for RL (continuous [0,1] + categorical logits/tau)
		"""
		carry = self.initialize_carry()
		result = self.process_block(
			carry,
			inputs,
			params=params,
			normalized_params=normalized_params,
			num_samples=num_samples,
			unroll=unroll,
			rngs=rngs,
		)

		if self.return_bargraphs:
			_, outputs, bargraph_data = result
			return outputs, bargraph_data
		_, outputs = result
		return outputs


# Note: every occurrence of "mydsp" in this file is textually replaced by the
# compiler with the actual class name (`-cn`), so the harness below works for
# any generated class name.
def test(args: argparse.Namespace) -> None:
	"""
	Run the Faust DSP with various test modes and options.

	Args:
		args: Parsed command-line arguments containing configuration options

	This function supports multiple modes:
	- Impulse response testing (default)
	- Random noise input
	- Audio file processing
	- Benchmarking
	- JIT compilation
	- Model structure visualization
	"""
	import logging

	log_level = getattr(logging, args.log_level.upper())
	logging.basicConfig(level=log_level, format="%(levelname)s: %(message)s")

	logger = logging.getLogger(__name__)

	faust_float = jnp.float64 if args.double else jnp.float32

	rngs = nnx.Rngs(args.seed)
	model = mydsp(sample_rate=args.sample_rate, faust_float=faust_float, rngs=rngs)
	
	# Display model structure if requested
	if args.tabulate is not False:
		logger.info("\n" + "="*60)
		logger.info("Model Structure Analysis")
		logger.info("="*60)

		# Create dummy inputs for tabulation
		dummy_length = args.block_size if args.realtime else 1024
		dummy_inputs = jnp.zeros((model.num_inputs, dummy_length), dtype=faust_float)

		# Determine depth: None for full depth, or convert string to int
		if args.tabulate is None:
			depth = None  # --tabulate (no argument) = full depth
		else:
			depth = int(args.tabulate)  # --tabulate 2 = depth 2

		# Tabulate the model structure
		# Note: nnx.tabulate may have issues with scan (https://github.com/google/flax/issues/5067)
		table_str = nnx.tabulate(model, dummy_inputs, depth=depth)

		logger.info(table_str)
		logger.info("="*60 + "\n")

	logger.info(f"Number of input channels: {model.num_inputs}")
	logger.info(f"Number of output channels: {model.num_outputs}")

	# json_obj = model.json_metadata
	# logger.debug(f"JSON info: {json_obj}")

	key = random.key(args.seed)

	if args.input is not None:
		input_audio, _ = librosa.load(
			args.input, mono=False, sr=args.sample_rate, duration=args.duration
		)
		if input_audio.ndim == 1:
			# librosa returns a 1-dim array for mono files; add the channel axis.
			input_audio = np.expand_dims(input_audio, 0)

		N_SAMPLES = input_audio.shape[1]
		N_CHANNELS = input_audio.shape[0]
		assert N_CHANNELS == model.num_inputs

		input_audio = faust_float(input_audio)
	else:
		duration_sec = args.duration or 1.0  # default to 1 second when making noise.

		N_SAMPLES = int(duration_sec * args.sample_rate)
		if isinstance(args.unroll, int):
			N_SAMPLES = (N_SAMPLES // int(args.unroll)) * int(args.unroll)
		N_CHANNELS = model.num_inputs

		if args.random:
			# Generate white noise in [-1, 1] for audio testing
			input_audio = random.uniform(
				key,
				shape=(N_CHANNELS, N_SAMPLES),
				minval=-1.0,
				maxval=1.0,
				dtype=faust_float,
			)
		else:
			input_audio = jnp.zeros((N_CHANNELS, N_SAMPLES), dtype=faust_float)
			input_audio = input_audio.at[:, 0].set(IMPULSE_VALUE)

	if args.verbose:
		print("model:", model)

	if args.jit:
		# For JIT, we need to handle the model call differently
		# Extract a key before JIT compilation
		if model.rngs is not None:
			# Get a single RNG key to use for the entire forward pass
			if isinstance(model.rngs, rnglib.Rngs):
				rng_key = model.rngs[model.rng_collection]()
			elif isinstance(model.rngs, rnglib.RngStream):
				rng_key = model.rngs()
			else:
				rng_key = None
		else:
			rng_key = None
		
		@jax.jit
		def forward(x: ArrayLike):
			# Pass the pre-extracted RNG key
			y = model(x, unroll=args.unroll, rngs=rng_key)
			return y
	else:
		def forward(x: ArrayLike):
			y = model(x, unroll=args.unroll)
			return y

	if args.benchmark:
		import tqdm
		import time

		logger.info(f"Running benchmark with {args.benchmark} iterations...")
		logger.info(f"Block size: {N_SAMPLES} samples")
		logger.info(f"Unroll factor: {args.unroll}")
		
		# Warmup runs
		logger.info("Warming up JIT compilation...")
		for _ in range(3):
			result = forward(input_audio)
			jax.block_until_ready(result)

		# Benchmark runs with timing
		times = []
		for _ in tqdm.trange(args.benchmark, desc="Benchmarking"):
			start_time = time.perf_counter()
			result = forward(input_audio)
			jax.block_until_ready(result)
			end_time = time.perf_counter()
			times.append(end_time - start_time)
		
		# Calculate statistics
		times_ms = [t * 1000 for t in times]
		avg_time_ms = sum(times_ms) / len(times_ms)
		min_time_ms = min(times_ms)
		max_time_ms = max(times_ms)
		
		# Calculate throughput
		samples_per_sec = N_SAMPLES / (avg_time_ms / 1000)
		realtime_factor = samples_per_sec / args.sample_rate
		
		logger.info("\n" + "="*60)
		logger.info("Benchmark Results")
		logger.info("="*60)
		logger.info(f"Average time: {avg_time_ms:.3f} ms")
		logger.info(f"Min time: {min_time_ms:.3f} ms")
		logger.info(f"Max time: {max_time_ms:.3f} ms")
		logger.info(f"Throughput: {samples_per_sec:.0f} samples/sec")
		logger.info(f"Real-time factor: {realtime_factor:.2f}x")
		if realtime_factor >= 1.0:
			logger.info(f"✓ Can run in real-time ({realtime_factor:.2f}x faster than real-time)")
		else:
			logger.info(f"✗ Cannot run in real-time ({realtime_factor:.2f}x slower than real-time)")
		logger.info("="*60 + "\n")

	y = forward(input_audio)

	# If bargraphs are present, __call__ returns (outputs, bargraph_data)
	bargraph_data = None
	if isinstance(y, tuple):
		y, bargraph_data = y

	params = model.unnormalize()
	if args.verbose:
		print("params", params)
		if bargraph_data:
			print("bargraph_data", {k: v.shape for k, v in bargraph_data.items()})

	assert y.ndim == 2
	assert y.shape[0] == model.num_outputs
	assert y.shape[1] == input_audio.shape[1]
	assert y.shape[1] == N_SAMPLES

	if args.output is not None:
		from scipy.io import wavfile

		output_audio = np.array(y).T
		wavfile.write(args.output, args.sample_rate, output_audio)

	logger.info("All done!")


def realtime_audio_example(
	unroll: int = 1, sample_rate: int = 48_000, block_size: int = DEFAULT_BLOCK_SIZE, use_double: bool = False
) -> None:
	"""
	Real-time audio streaming example using sounddevice.

	Demonstrates the real-time API with actual audio output using the
	process_block method for stateful block-by-block processing.

	Args:
		unroll: Unroll factor for jax.lax.scan (default: 1)
		sample_rate: Audio sample rate in Hz (default: 48000)
		block_size: Number of samples per block (default: 512)
		use_double: Whether to use float64 instead of float32 (default: False)

	Raises:
		ImportError: If sounddevice is not installed
	"""
	import sounddevice as sd
	import time

	# Initialize model
	faust_float = jnp.float64 if use_double else jnp.float32

	rngs = nnx.Rngs(DEFAULT_RNG_SEED)
	model = mydsp(sample_rate=sample_rate, faust_float=faust_float, rngs=rngs)

	# Initialize carry state
	carry = model.initialize_carry()

	# JIT compile the process method
	@partial(jax.jit, donate_argnums=(0,))
	def process_block_jit(carry, inputs: ArrayLike, rng_key: Array):
		new_carry, outputs = model.process_block(
			carry,
			inputs,
			unroll=unroll,
			rngs=rng_key,
		)
		return new_carry, outputs

	# Create a generator for audio blocks
	def audio_generator():
		nonlocal carry
		rng_key = random.key(DEFAULT_RNG_SEED)

		# For processors, you would get input from sounddevice
		# For this example, we'll use zeros
		inputs = jnp.zeros((model.num_inputs, block_size))
		
		while True:
			# Process block
			subkey, rng_key = random.split(rng_key)
			carry, outputs = process_block_jit(carry, inputs, subkey)

			# Convert to numpy and reshape for sounddevice
			# sounddevice expects shape (frames, channels)
			output_np = np.asarray(outputs.T, dtype=np.float32)

			# If mono, reshape to (frames, 1)
			if output_np.ndim == 1:
				output_np = output_np.reshape(-1, 1)

			yield output_np

	# Create the audio generator
	audio_gen = audio_generator()

	# Sounddevice callback
	def callback(outdata, frames, time_info, status):
		if status:
			print(f"Sounddevice status: {status}")
		outdata[:] = next(audio_gen)

	# Start streaming
	print(f"▶ Streaming audio at {sample_rate} Hz, {block_size} samples/block")
	print(f"  Model: {model.num_inputs} inputs → {model.num_outputs} outputs")
	print("  Press Ctrl+C to stop...")

	try:
		with sd.OutputStream(
			channels=model.num_outputs,
			samplerate=sample_rate,
			blocksize=block_size,
			dtype="float32",
			callback=callback,
		):
			while True:
				time.sleep(1)
	except KeyboardInterrupt:
		print("\n⏹ Stopped.")


if __name__ == "__main__":
	# fmt: off
	parser = argparse.ArgumentParser(description="Run a JAX/Flax model converted from Faust code")
	parser.add_argument("-sr", "--sample-rate", type=int, default=DEFAULT_SAMPLE_RATE, help=f"Sample rate (default: {DEFAULT_SAMPLE_RATE})")
	parser.add_argument("-d", "--duration", type=float, default=None, help="Output duration in seconds")
	parser.add_argument("--unroll", type=int, default=1, help="Unroll size for jax.lax.scan (default: 1)")
	parser.add_argument("--random", default=False, action=argparse.BooleanOptionalAction, help="Whether the default audio is random. By default it's an impulse.")
	parser.add_argument("--seed", default=DEFAULT_RNG_SEED, type=int, help=f"Seed for random number generator (default: {DEFAULT_RNG_SEED})")
	parser.add_argument("-i", "--input", type=str, default=None, help="Filepath for input audio WAV")
	parser.add_argument("-o", "--output", type=str, default=None, help="Filepath for output audio WAV")
	parser.add_argument("--log-level", default="INFO", choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"], help="Set the logger level (default: INFO)")
	parser.add_argument("--jit", default=False, action=argparse.BooleanOptionalAction, help="Whether to use JIT.")
	parser.add_argument("--benchmark", type=int, default=0, help="Number of loops for a speed benchmark with tqdm (default: 0).")
	parser.add_argument("--platform", default="cpu", choices=["cpu", "gpu", "metal", "tpu"], help="Which platform to use (default: cpu)")
	parser.add_argument("--double", default=False, action=argparse.BooleanOptionalAction, help="Whether to enable double type (jnp.float64)")
	parser.add_argument("--verbose", default=False, action=argparse.BooleanOptionalAction, help="Whether to print the variables of the DSP")
	parser.add_argument("--realtime", default=False, action=argparse.BooleanOptionalAction, help="Run the DSP with silent input and send the output to an audio device in real-time.")
	parser.add_argument("-bs", "--block-size", type=int, default=DEFAULT_BLOCK_SIZE, help=f"Block size for real-time mode (default: {DEFAULT_BLOCK_SIZE})")
	parser.add_argument("--tabulate", nargs='?', const=None, default=False, metavar='DEPTH', help="Tabulate model structure. Use --tabulate for full depth or --tabulate N for specific depth.")
	# fmt: on
	args = parser.parse_args()

	# Global flag to set a specific platform, must be used at startup.
	if args.double:
		jax.config.update("jax_enable_x64", True)
	jax.config.update("jax_platform_name", args.platform)

	if args.realtime:
		realtime_audio_example(
			args.unroll,
			sample_rate=args.sample_rate,
			block_size=args.block_size,
			use_double=args.double,
		)
	else:
		test(args)