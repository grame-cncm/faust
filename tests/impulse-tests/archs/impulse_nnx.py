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

import sys
import os
from os import environ
environ["JAX_PLATFORM_NAME"] = "cpu"
environ["JAX_PLATFORMS"] = "cpu"

import contextlib

import warnings
warnings.filterwarnings("ignore")

@contextlib.contextmanager
def suppress_metal_message():
	with open(os.devnull, 'w') as fnull:
		# Suppress both stdout and stderr
		stdout_fileno = sys.stdout.fileno()
		stderr_fileno = sys.stderr.fileno()
		old_stdout = os.dup(stdout_fileno)
		old_stderr = os.dup(stderr_fileno)
		os.dup2(fnull.fileno(), stdout_fileno)
		os.dup2(fnull.fileno(), stderr_fileno)
		try:
			yield
		finally:
			os.dup2(old_stdout, stdout_fileno)
			os.dup2(old_stderr, stderr_fileno)
			os.close(old_stdout)
			os.close(old_stderr)

# Use it when importing or initializing JAX
with suppress_metal_message():
	import jax
	import math
	import json
	import dataclasses
	from typing import Dict, List, Tuple, Callable, Any, Optional
	from pathlib import Path
	import numpy as np
	from jax import numpy as jnp, random
	from flax import nnx
	from flax.nnx import rnglib
	from flax.typing import Dtype

# Generated code
<<includeIntrinsic>>
<<includeclass>>

	def load_soundfile(self, filepath: str) -> Tuple[np.ndarray, int]:
		# This pre-computed sine is desired for the impulse-tests.
		audio = jnp.sin(jnp.linspace(0, 2*jnp.pi, num=4096, endpoint=False, dtype=self.faust_float))
		audio = jnp.stack([audio, audio])
		return audio, 44100
		
	def add_soundfile(self, zone: str, ui_path: list[str], label: str, url: str, unnorm_funcs: dict, metadata: dict | None = None):
		# example url: {"tango.wav';'foo.wav';'bar/baz.wav'}
		filepaths = url[2:-2].split("';'")
		fLength, fOffset, fSR, offset = [], [], [], 0
		audio_data = [self.load_soundfile(filepath) for filepath in filepaths]
		num_chans = max([y.shape[0] for y, _ in audio_data])
		total_length = sum([y.shape[1] for y, _ in audio_data])
		fBuffers = jnp.zeros((num_chans, total_length))
		for y, sr in audio_data:
			fSR.append(sr)
			assert y.ndim == 2
			y = jnp.array(y, dtype=self.faust_float)
			fLength.append(y.shape[1])
			fOffset.append(offset)
			fBuffers = fBuffers.at[:y.shape[0],offset:offset+y.shape[1]].set(y)
			offset += y.shape[1]
		if label.startswith("param:"):
			label = label[6:]  # remove param:
			label = "/".join(ui_path+[label])
			fBuffers = nnx.Param(fBuffers)
			setattr(self, "_" + label, fBuffers)
			unnorm_funcs[zone] = (zone, lambda x: x)
		else:
			label = "/".join(ui_path+[label])

		setattr(self, zone, nnx.data({
			"fLength": jnp.array(fLength, dtype=jnp.int32),
			"fOffset": jnp.array(fOffset, dtype=jnp.int32),
			"fBuffers": fBuffers,
			"fSR": jnp.array(fSR, dtype=self.faust_float)
		}))

	def add_button(self, zone: str, ui_path: list[str], label: str, unnorm_funcs: dict):
		label = "/".join(ui_path+[label])
		setattr(self, zone, nnx.Param(jnp.zeros((), dtype=self.faust_float)))
		unnorm_funcs[label] = (zone, lambda x: x)
	
	def add_checkbox(self, zone: str, ui_path: list[str], label: str, unnorm_funcs: dict):
		self.add_button(zone, ui_path, label, unnorm_funcs)
	
	def add_nentry(
		self, zone: str, ui_path: List[str], label: str,
		init: float, a_min: float, a_max: float, step_size: float,
		unnorm_funcs: dict, scale_mode: str = "linear",
		metadata: dict | None = None,
	):
		# For deterministic impulse tests, use exact init values like C++ CheckControlUI
		label = "/".join(ui_path + [label])
		init = self.faust_float(init)
		
		# Create parameter with exact init value (no normalization for impulse tests)
		setattr(self, zone, nnx.Param(init))
		
		# Create identity unnormalization function (parameter is already at correct value)
		unnorm_funcs[label] = (zone, lambda x: x)
	
	def normalize_value(self, value: float, a_min: float, a_max: float, scale_mode: str) -> float:
		"""Normalize a value from [a_min, a_max] to [0, 1] based on scale mode."""
		faust_float = self.faust_float
		if scale_mode == "linear":
			return jnp.interp(value, jnp.array([a_min, a_max], dtype=faust_float), 
							 jnp.array([faust_float(0), faust_float(1)], dtype=faust_float))
		elif scale_mode == "exp":
			# Map to [1, e], take log, then map to [0, 1]
			value_exp = jnp.interp(value, jnp.array([a_min, a_max], dtype=faust_float), 
								  jnp.array([faust_float(1), jnp.e], dtype=faust_float))
			value_log = jnp.log(value_exp)
			return jnp.interp(value_log, jnp.array([faust_float(0), faust_float(1)], dtype=faust_float), 
							 jnp.array([faust_float(0), faust_float(1)], dtype=faust_float))
		elif scale_mode == "log":
			# Map to [-4, 0], apply 10^x, then map to [0, 1]
			value_log10 = jnp.interp(value, jnp.array([a_min, a_max], dtype=faust_float), 
									jnp.array([faust_float(-4), faust_float(0)], dtype=faust_float))
			value_pow = jnp.power(faust_float(10), value_log10)
			return jnp.interp(value_pow, jnp.array([faust_float(10**-4), faust_float(1)], dtype=faust_float), 
							 jnp.array([faust_float(0), faust_float(1)], dtype=faust_float))
		else:
			raise ValueError(f"Unknown scale mode: {scale_mode}")
	
	def create_unnormalize_func(self, a_min: float, a_max: float, scale_mode: str):
		"""Create an unnormalization function for the given scale mode."""
		faust_float = self.faust_float
		if scale_mode == "linear":
			return lambda normalized: jnp.interp(
				jnp.clip(normalized, faust_float(0), faust_float(1)),
				jnp.array([faust_float(0), faust_float(1)], dtype=faust_float),
				jnp.array([a_min, a_max], dtype=faust_float)
			)
		elif scale_mode == "exp":
			return lambda normalized: jnp.interp(
				jnp.exp(jnp.clip(normalized, faust_float(0), faust_float(1))), 
				jnp.array([faust_float(1), jnp.e], dtype=faust_float), 
				jnp.array([a_min, a_max], dtype=faust_float)
			)
		elif scale_mode == "log":
			return lambda normalized: jnp.interp(
				jnp.log10(jnp.interp(
					jnp.clip(normalized, faust_float(0), faust_float(1)),
					jnp.array([faust_float(0), faust_float(1)], dtype=faust_float),
					jnp.array([faust_float(10**-4), faust_float(1)], dtype=faust_float)
				)), 
				jnp.array([faust_float(-4), faust_float(0)], dtype=faust_float), 
				jnp.array([a_min, a_max], dtype=faust_float)
			)
		else:
			raise ValueError(f"Unknown scale mode: {scale_mode}")
	
	def add_slider(self, zone: str, ui_path: list[str], label: str, init: float, a_min: float, a_max: float, step_size: float, unnorm_funcs: dict, scale_mode="linear"):
		"""Add a slider UI element with the specified parameters."""
		faust_float = self.faust_float
		label = "/".join(ui_path + [label])
		init, a_min, a_max = faust_float(init), faust_float(a_min), faust_float(a_max)

		# Normalize init value to [0, 1] based on scale mode
		normalized_init = self.normalize_value(init, a_min, a_max, scale_mode)

		# Create the normalized parameter with label as name
		setattr(self, zone, nnx.Param(normalized_init))

		# Create and store the unnormalization function
		unnorm_func = self.create_unnormalize_func(a_min, a_max, scale_mode)
		unnorm_funcs[label] = (zone, unnorm_func)

	def add_hslider(self, zone: str, ui_path: list[str], label: str, init: float, a_min: float, a_max: float, step_size: float, unnorm_funcs: dict, scale_mode: str):
		self.add_slider(zone, ui_path, label, init, a_min, a_max, step_size, unnorm_funcs, scale_mode)

	def add_vslider(self, zone: str, ui_path: list[str], label: str, init: float, a_min: float, a_max: float, step_size: float, unnorm_funcs: dict, scale_mode: str):
		self.add_slider(zone, ui_path, label, init, a_min, a_max, step_size, unnorm_funcs, scale_mode)

	def _finalize_interface(self):
		"""No-op: the impulse harness drives parameters directly by zone."""
		pass
	
	def add_hbargraph(self, zone: str, ui_path: list[str], label: str, a_min: float, a_max: float, unnorm_funcs: dict):
		self.add_bargraph(zone, ui_path, label, a_min, a_max)
	
	def add_vbargraph(self, zone: str, ui_path: list[str], label: str, a_min: float, a_max: float, unnorm_funcs: dict):
		self.add_bargraph(zone, ui_path, label, a_min, a_max)

	def add_bargraph(self, zone: str, ui_path: list[str], label: str, a_min: float, a_max: float):
		setattr(self, zone, self.faust_float(0))

	def unnormalize(self, i: int) -> Dict[str, jnp.ndarray]:
		"""
		Unnormalize all UI parameters from [0, 1] to their original ranges.

		Args:
			i: Sample offset of the current block's first frame. Controls are
				held constant within a block, mirroring the C++ reference
				harness where controls only change between compute() calls.

		Returns:
			Dictionary mapping zones to unnormalized parameter values
		"""
		params = {}

		# Simply use the stored unnormalization functions
		for label, (zone, unnorm_func) in self._unnorm_funcs.items():
			if hasattr(self, zone):
				if zone.startswith("fButton"):
					normalized_value = getattr(self, zone)
					# Buttons are pressed for exactly the first 64 samples,
					# matching the C++ reference harness (kFrames = 64 in
					# archs/controlTools.h: buttons on for the first compute()
					# block, off afterwards).
					params[zone] = jnp.where(i > 63, jnp.zeros_like(normalized_value), jnp.ones_like(normalized_value))
				else:
					normalized_value = getattr(self, zone)
					params[zone] = unnorm_func(normalized_value)
			else:
				raise ValueError(f"Zone not found: {zone}")
		
		return params
	
	def initialize_carry(self) -> Dict[str, jnp.ndarray]:
		"""
		Initialize the carry state for real-time processing.
			
		Returns:
			Dictionary containing all stateful components (delays, filter states, etc.)
		"""		
		# Initialize the full state using fast numpy
		state = self._initialize_carry()
		
		# Add soundfiles to state if they exist
		for attr_name in dir(self):
			if attr_name.startswith("fSoundfile"):
				state[attr_name] = getattr(self, attr_name)

		# Add bargraph values to state (needed for scan pytree matching)
		for attr_name in dir(self):
			if attr_name.startswith(("fVbargraph", "fHbargraph")):
				state[attr_name] = getattr(self, attr_name)

		# Convert numpy to JAX numpy arrays
		state = jax.tree.map(jnp.array, state)
		
		return state
	
	def process_block(
		self,
		i: int,
		carry: Dict[str, jnp.ndarray],
		inputs: jnp.ndarray = None,
		length: int = None,
		unroll: int = 1,
	) -> Tuple[jnp.ndarray, Dict[str, jnp.ndarray]]:
		"""
		Process one block of audio and return updated state.

		Args:
			i: sample offset of the block's first frame (special for the
				impulse archs versus minimal.py; controls are held constant
				within a block)
			carry: State dictionary from previous block
			inputs: Input audio block of shape (num_inputs, block_size)
			length (int): block size of generated output
			unroll (int):

		Returns:
			Tuple of (output_block, new_carry) where:
			- output_block has shape (num_outputs, block_size)
			- new_carry is the updated state dictionary
		"""
		if length is None and inputs is not None and hasattr(inputs, "shape"):
			length = inputs.shape[-1]

		# Unnormalize parameters once before the scan
		params = self.unnormalize(i)

		def scan_body(carry, x):
			new_carry, y = self.tick(params, carry, x)
			return new_carry, y

		# Handle input shape for scan
		if inputs is None or self.num_inputs == 0:
			# Generator case
			inputs = jnp.zeros((0, length), dtype=self.faust_float)

		new_carry, outputs = nnx.scan(
			scan_body,
			length=length,
			unroll=unroll,
			in_axes=(nnx.Carry, 1),
			out_axes=(nnx.Carry, 1),
		)(carry, inputs)

		return outputs, new_carry

	def __call__(
		self, x: jnp.ndarray, length: int = None, unroll: int = 1
	) -> jnp.ndarray:

		if length is None and x is not None:
			length = x.shape[-1]

		# Handle generators (no input case)
		if x is None:
			x = jnp.zeros((self.num_inputs, length), dtype=self.faust_float)

		carry = self.initialize_carry()

		# Unnormalize parameters once before the scan
		params = self.unnormalize(0)

		def scan_body(carry, x):
			new_carry, y = self.tick(params, carry, x)
			return new_carry, y

		# Handle input shape for scan
		if self.num_inputs == 0:
			# Generator case
			x = jnp.zeros((0, length), dtype=self.faust_float)

		new_carry, outputs = nnx.scan(
			scan_body,
			length=length,
			unroll=unroll,
			in_axes=(nnx.Carry, 1),
			out_axes=(nnx.Carry, 1),
		)(carry, x)

		return outputs


def main(args, N_SAMPLES, OFFSET, print_header=True, block_size=1):

	from jax import random
	from scipy.io import wavfile

	faust_float = jnp.float64 if args.double else jnp.float32

	rngs = nnx.Rngs(1, params=1, rng_stream=2)
	model = mydsp(sample_rate=args.sample_rate, faust_float=faust_float, rngs=rngs)

	BLOCK_SIZE = block_size

	N_CHANNELS = model.num_inputs

	if args.random:
		input_audio = random.uniform(random.key(3), shape=(N_CHANNELS, BLOCK_SIZE), minval=-1, maxval=1, dtype=faust_float)
	else:
		input_audio = jnp.zeros((N_CHANNELS, BLOCK_SIZE), dtype=faust_float)
		input_audio = input_audio.at[:,0].set(1.)
	
	# Initialize carry state
	carry = model.initialize_carry()

	@jax.jit
	def process_block_jit(i, carry, inputs: jnp.ndarray):
		outputs, new_carry = model.process_block(i, carry, inputs, length=BLOCK_SIZE, unroll=1)
		return outputs, new_carry

	out_blocks = []
	did_silence_audio = False

	for i in range(math.ceil(N_SAMPLES/BLOCK_SIZE)):
		if not did_silence_audio and i != 0:
			did_silence_audio = True
			input_audio = jnp.zeros_like(input_audio)

		# Pass the sample offset of the block's first frame, so button timing
		# (on for the first 64 samples) is block-size independent.
		out_block, carry = process_block_jit(i * BLOCK_SIZE, carry, input_audio)
		out_blocks.append(np.array(out_block))

	y = np.concatenate(out_blocks, axis=-1)
	y = y[:, :N_SAMPLES]

	assert y.ndim == 2
	assert y.shape[0] == model.num_outputs
	assert y.shape[1] == N_SAMPLES

	output_audio = y.T

	if args.output is not None:
		
		wavfile.write(args.output, args.sample_rate, output_audio)
	
	# print the header
	if print_header:
		print(f"number_of_inputs  : {model.num_inputs}")
		print(f"number_of_outputs : {model.num_outputs}")
		print(f"number_of_frames  : {N_SAMPLES*4}")

	# print the samples
	for i, frame in enumerate(output_audio):
		print(f"     {i+OFFSET} :  " + ' '.join(["{:.6f}".format(c) for c in frame]))

if __name__ == '__main__':
	import argparse
	parser = argparse.ArgumentParser(description='Run a JAX/Flax model converted from Faust code')
	parser.add_argument('-sr', '--sample-rate', type=int, default=44100, help='Sample rate (such as 44100)')
	parser.add_argument("--double", default=True, action=argparse.BooleanOptionalAction,
						help="Whether to enable double type (jnp.float64)")
	parser.add_argument('--random', default=False, action=argparse.BooleanOptionalAction, help="Whether the default audio is random. By default it's an impulse.")
	parser.add_argument('-o', '--output', type=str, default=None, help='Filepath for output audio WAV')
	parser.add_argument('-d', '--duration', type=int, default=15000, help='duration')

	args = parser.parse_args()

	if args.double:
		jax.config.update("jax_enable_x64", True)

	duration = args.duration

	# Reference files (see archs/impulsearch.cpp) contain FOUR sub-runs of
	# `duration` frames each: mono, mono with randomized compute() splits,
	# polyphonic with 4 voices, and polyphonic with 1 voice. The header must
	# claim the full 4*duration count because filesCompare requires equal
	# header counts; it then stops gracefully at EOF, comparing only the
	# sub-runs emitted here (the Julia, Rust, and D harnesses follow the same
	# convention). This harness emits the first two sub-runs — the poly runs
	# exercise the C++ mydsp_poly wrapper, which has no JAX equivalent
	# (polyphony is done with jax.vmap instead, see architecture/jax/README.md).
	# The second sub-run uses 64-sample blocks so that, like the C++
	# randomized-split run, it verifies output is independent of how the
	# stream is cut into process_block calls (carry state round-trips exactly).
	main(args, duration, 0)
	main(args, duration, duration, print_header=False, block_size=64)