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
from typing import List

import numpy as np
import librosa
import jax
import jax.numpy as jnp
from flax import linen as nn

def remainder(x, y):
	a = jnp.remainder(x, y)
	return a - y*((a > y/2).astype(jnp.int32))

# Generated code
<<includeIntrinsic>>
<<includeclass>>
	
	def load_soundfile(self, filepath):
		try:
			audio, sr = librosa.load(filepath, mono=False, sr=None)
		except FileNotFoundError:
			return np.zeros((1,1024)), 44100
		if audio.ndim == 1:
			audio = np.expand_dims(audio, 0)
		return audio, sr
	
	def add_soundfile(self, state, zone: str, ui_path: List[str], label: str, url: str, x):
		# todo: better parsing
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
			label = label[6:]  # remove param:
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
		state = self.initialize(self.sample_rate, x, T)
		state = self.build_interface(state, x, T)
		# convert numpy array to jax numpy array
		state = jax.tree_map(jnp.array, state)
		return jnp.transpose(jax.lax.scan(self.tick, state, jnp.transpose(x, axes=(1, 0)))[1], axes=(1,0))


class SubClass(mydsp):

	"""
	We need to subclass for two reasons:
	* We re-implement load_soundfile so that we can pretend an audio file exists.
	* We re-implement tick so that we can set the buttons to 1.0 for the first 64 samples.
	"""

	def load_soundfile(self, filepath):
		audio = jnp.sin(jnp.linspace(0, 2*jnp.pi, num=4096, endpoint=False, dtype=FAUSTFLOAT))
		audio = jnp.stack([audio, audio])
		return audio, 44100

	@nn.compact
	def __call__(self, x, T: int) -> jnp.array:
		state = self.initialize(self.sample_rate, x, T)
		state = self.build_interface(state, x, T)
		# convert numpy array to jax numpy array
		state = jax.tree_map(jnp.array, state)
		
		# impulse all the buttons
		for key in state:
			if key.startswith('fButton'):
				state[key] = 1.

		state['COUNTER'] = 64

		def tick2(state: dict, inputs: jnp.array):
			state, out = self.tick(state, inputs)

			state['COUNTER'] -= 1

			# zero all the buttons
			for key in state:
				if key.startswith('fButton'):
					state[key] *= (state['COUNTER']>0).astype(np.int8)

			return state, out

		x = jnp.transpose(x, axes=(1, 0))
		state, y = jax.lax.scan(tick2, state, x)
		y = jnp.transpose(y, axes=(1, 0))
		return y

def test(args, N_SAMPLES, OFFSET, print_header=True):

	from jax import random
	from scipy.io import wavfile
	import warnings
	warnings.filterwarnings("ignore")

	model = SubClass(sample_rate=args.sample_rate)

	json_obj = model.getJSON()
	# print('json_obj: ', json_obj)

	key = random.PRNGKey(0)

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

	output_audio = np.array(y).T

	if args.output is not None:
		
		wavfile.write(args.output, args.sample_rate, output_audio)
	
	# print the header
	if print_header:
		print(f"number_of_inputs  :   {model.getNumInputs()}")
		print(f"number_of_outputs :   {model.getNumOutputs()}")
		print(f"number_of_frames  :   {N_SAMPLES*4}")

	# print the samples
	for i, frame in enumerate(output_audio):
		print(f"     {i+OFFSET} :  " + ' '.join(["{:.6f}".format(c) for c in frame]))

if __name__ == '__main__':
	import argparse
	parser = argparse.ArgumentParser(description='Run a JAX/Flax model converted from Faust code')
	parser.add_argument('-sr', '--sample-rate', type=int, default=44100, help='Sample rate (such as 44100)')
	parser.add_argument('--random', type=bool, default=False, help="Whether the default audio is random. By default it's an impulse.")
	parser.add_argument('-o', '--output', type=str, default=None, help='Filepath for output audio WAV')

	args = parser.parse_args()

	test(args, 15000, 0)
	test(args, 15000, 15000, print_header=False)
