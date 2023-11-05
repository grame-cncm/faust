# ************************************************************************
# FAUST Architecture File
# Copyright (C) 2022 GRAME, Centre National de Creation Musicale
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

import json
import re
import dataclasses
from pathlib import Path
from typing import List

import numpy as np
import librosa
import jax
import jax.numpy as jnp
from jax import random
from flax import linen as nn


def remainder(x, y):
	a = jnp.remainder(x, y)
	return a - y*((a > y/2).astype(jnp.int32))


# Generated code
<<includeIntrinsic>>
<<includeclass>>
	
	def load_soundfile(self, filepath: str):
		# soundfile_dirs should always include at least "".
		soundfile_dirs = [""] + list(self.soundfile_dirs)
		# Create a list of potential filepaths to check
		potential_paths = [Path(filepath)] if Path(filepath).is_absolute() else [Path(d) / filepath for d in soundfile_dirs]

		# Loop through potential paths and try to load the audio file
		for full_path in potential_paths:
			try:
				audio, sr = librosa.load(str(full_path), mono=False, sr=None)
				if audio.ndim == 1:
					audio = np.expand_dims(audio, 0)
				return audio, sr
			except FileNotFoundError:
				# If not found at this path, continue to the next
				continue
		
		# If none of the paths worked, return the default silence array and sample rate
		return np.zeros((1, 1024)), self.sample_rate
	
	def add_soundfile(self, state, zone: str, ui_path: List[str], label: str, url: str, x):
		# example url: {'tango.wav';'foo.wav';'bar/baz.wav'}
		filepaths = url[2:-2].split("';'")
		fLength, fOffset, fSR, offset = [], [], [], 0
		audio_data = [self.load_soundfile(filepath) for filepath in filepaths]
		num_chans = max([y.shape[0] for y, _ in audio_data])
		total_length = sum([y.shape[1] for y, _ in audio_data])
		fBuffers = jnp.zeros((num_chans, total_length))
		for y, sr in audio_data:
			fSR.append(sr)
			assert y.ndim == 2
			y = jnp.array(y)
			fLength.append(y.shape[1])
			fOffset.append(offset)
			fBuffers = fBuffers.at[:y.shape[0],offset:offset+y.shape[1]].set(y)
			offset += y.shape[1]
		if label.startswith('param:'):
			label = label[6:]  # remove "param:"
			label = "/".join(ui_path+[label])
			fBuffers = self.param("_"+label, (lambda key, shape: fBuffers), None)
		else:
			label = "/".join(ui_path+[label])
		self.sow('intermediates', label, fBuffers)
		state[zone] = {'fLength': fLength, 'fOffset': fOffset, 'fBuffers': fBuffers, 'fSR': fSR}

	def add_button(self, state, zone: str, ui_path: List[str], label: str):
		label = "/".join(ui_path+[label])
		param = self.param("_"+label, nn.initializers.constant(0.), ())
		param = jnp.where(param>0., 1., 0.)
		self.sow('intermediates', label, param)
		state[zone] = param
	
	def add_nentry(self, state, zone: str, ui_path: List[str], label: str, init: float, a_min: float, a_max: float, step_size: float, scale_mode='linear'):
		label = "/".join(ui_path+[label])
		num_steps = int(round((a_max-a_min)/step_size))+1
		init_unit = int(round(init-a_min)/step_size)
		param = jnp.ones((num_steps,))
		param = param.at[init_unit].set(2)
		param = nn.softmax(param)
		param = self.param("_"+label, (lambda key, shape: param), None)
		param = jnp.argmax(param, axis=-1)*step_size+a_min
		self.sow('intermediates', label, param)
		state[zone] = param
	
	def add_slider(self, state, zone: str, ui_path: List[str], label: str, init: float, a_min: float, a_max: float, scale_mode='linear'):
		label = "/".join(ui_path+[label])
		init, a_min, a_max = float(init), float(a_min), float(a_max)
		if scale_mode == 'linear':
			init = jnp.interp(init, jnp.array([a_min, a_max]), jnp.array([-1.,1.]))
			param = self.param("_"+label, nn.initializers.constant(init), ())
			param = jnp.clip(param, -1., 1.)
			param = jnp.interp(param, jnp.array([-1., 1.]), jnp.array([a_min, a_max]))
		elif scale_mode == 'exp':
			init = jnp.interp(init, jnp.array([a_min, a_max]), jnp.array([1., jnp.e]))
			init = jnp.log(init)
			init = jnp.interp(init, jnp.array([0., 1.]), jnp.array([-1.,1.]))
			param = self.param("_"+label, nn.initializers.constant(init), ())
			param = jnp.clip(param, -1., 1.)
			param = jnp.interp(param, jnp.array([-1., 1.]), jnp.array([0., 1.]))
			param = jnp.interp(jnp.exp(param), jnp.array([1., jnp.e]), jnp.array([a_min, a_max]))
		elif scale_mode == 'log':
			init = jnp.interp(init, jnp.array([a_min, a_max]), jnp.array([-4., 0.]))
			init = jnp.power(10., init)
			init = jnp.interp(init, jnp.array([10.**-4., 1.]), jnp.array([-1.,1.]))
			param = self.param("_"+label, nn.initializers.constant(init), ())
			param = jnp.clip(param, -1., 1.)
			param = jnp.interp(param, jnp.array([-1., 1.]), jnp.array([10.**-4., 1.]))
			param = jnp.interp(jnp.log10(param), jnp.array([-4., 0.]), jnp.array([a_min, a_max]))
		else:
			raise ValueError(f"Unknown scale '{scale_mode}'.")
		self.sow('intermediates', label, param)
		state[zone] = param
		
	@nn.compact
	def __call__(self, x, T: int) -> jnp.array:
		state = self.initialize(x, T)
		state = self.build_interface(state, x, T)
		# convert any numpy arrays to jax numpy arrays
		state = jax.tree_map(jnp.array, state)

		x = jnp.transpose(x, axes=(1, 0))
		state, y = jax.lax.scan(self.tick, state, x)
		y = jnp.transpose(y, axes=(1, 0))
		return y


def test(args):

	import logging

	model = mydsp(sample_rate=args.sample_rate)

	log_level = getattr(logging, args.log_level.upper())
	logging.basicConfig(level=log_level, format='%(levelname)s: %(message)s')

	logger = logging.getLogger(__name__)

	logger.info(f"Number of input channels: {model.getNumInputs()}")
	logger.info(f"Number of output channels: {model.getNumOutputs()}")

	json_obj = model.getJSON()
	logger.debug(f"JSON info: {json_obj}")

	key = random.PRNGKey(args.seed)

	if args.input is not None:
		input_audio, _ = librosa.load(args.input, mono=False, sr=args.sample_rate, duration=args.duration)
		if input_audio.ndim == 1:
			input_audio = input_audio.unsqueeze(0)

		N_SAMPLES = input_audio.shape[1]
		N_CHANNELS = input_audio.shape[0]
		assert N_CHANNELS == model.getNumInputs()

		input_audio = FAUSTFLOAT(input_audio)
	else:
		duration_sec = args.duration or 1.  # default to 1 second when making noise.

		N_SAMPLES = int(duration_sec*args.sample_rate)
		N_CHANNELS = model.getNumInputs()

		if args.random:
			input_audio = -1.+2.*random.uniform(key, shape=(N_CHANNELS, N_SAMPLES), dtype=FAUSTFLOAT)
		else:
			input_audio = jnp.zeros((N_CHANNELS, N_SAMPLES), dtype=FAUSTFLOAT)
			input_audio = input_audio.at[:,0].set(1.)

	variables = model.init({'params': key}, input_audio, N_SAMPLES)  
	y, mod_vars = model.apply(variables, input_audio, N_SAMPLES, mutable='intermediates')

	assert y.ndim == 2
	assert y.shape[0] == model.getNumOutputs()
	assert y.shape[1] == input_audio.shape[1]
	assert y.shape[1] == N_SAMPLES

	if args.output is not None:
		from scipy.io import wavfile
		output_audio = np.array(y).T
		wavfile.write(args.output, args.sample_rate, output_audio)

	logger.info("All done!")
		

if __name__ == '__main__':
	import argparse
	parser = argparse.ArgumentParser(description='Run a JAX/Flax model converted from Faust code')
	parser.add_argument('-sr', '--sample-rate', type=int, default=44100, help='Sample rate (such as 44100)')
	parser.add_argument('-d', '--duration', type=float, default=None, help='Output duration in seconds')
	parser.add_argument('--random', action='store_true',
		help="Whether the default audio is random. By default it's an impulse.")
	parser.add_argument('--seed', default=0, type=int, help="Seed for random number generator (default: 0)")
	parser.add_argument('-i', '--input', type=str, default=None, help='Filepath for input audio WAV')
	parser.add_argument('-o', '--output', type=str, default=None, help='Filepath for output audio WAV')
	parser.add_argument('--log-level', default='INFO', choices=['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL'], 
						help='Set the logger level (default: INFO)')

	args = parser.parse_args()

	test(args)
