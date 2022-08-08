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

# Generated code
<<includeIntrinsic>>
<<includeclass>>

from jax import random
from scipy.io import wavfile
import warnings
warnings.filterwarnings("ignore")


class SubClass(mydsp):

    """
    We need to subclass for two reasons:
    * We re-implement load_soundfile so that we can pretend an audio file exists.
    * We re-implement tick so that we can set the buttons to 1.0 for the first 64 samples.
    """

    def load_soundfile(self, filepath):
        audio = np.sin(np.linspace(0, 2*np.pi, num=4096, endpoint=False, dtype=np.float64))
        audio = np.stack([audio, audio])
        return audio, 44100

    @nn.compact
    def __call__(self, x, T: int) -> jnp.array:
        state = self.classInit(self.sample_rate, x, T)

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

        return jnp.transpose(jax.lax.scan(tick2, state, jnp.transpose(x, axes=(1, 0)))[1], axes=(1,0))


def test(args, N_SAMPLES, OFFSET, print_header=True):

    # dtype = jnp.float32  # single precision
    dtype = jnp.float64  # double instead of single precision

    model = SubClass(sample_rate=args.sample_rate)

    json_obj = model.getJSON()
    # print('json_obj: ', json_obj)

    key = random.PRNGKey(0)

    N_CHANNELS = model.getNumInputs()

    if args.random:
        input_audio = -1.+2.*random.uniform(key, shape=(N_CHANNELS, N_SAMPLES), dtype=dtype)
    else:
        input_audio = jnp.zeros((N_CHANNELS, N_SAMPLES), dtype=dtype)
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
