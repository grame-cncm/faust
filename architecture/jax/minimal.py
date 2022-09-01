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

def test(args):

    dtype = jnp.float32  # todo: pass dtype to the model

    model = mydsp(sample_rate=args.sample_rate)
    print("NUM INPUT CHANNELS: ", model.getNumInputs())
    print("NUM OUTPUT CHANNELS: ", model.getNumOutputs())

    json_obj = model.getJSON()
    # print('json_obj: ', json_obj)

    key = random.PRNGKey(0)

    if args.input is not None:
        input_audio, _ = librosa.load(args.input, mono=False, sr=args.sample_rate, duration=args.duration)
        if input_audio.ndim == 1:
            input_audio = input_audio.unsqueeze(0)

        N_SAMPLES = input_audio.shape[1]
        N_CHANNELS = input_audio.shape[0]
        assert N_CHANNELS == model.getNumInputs()

        input_audio = dtype(input_audio)
    else:
        duration_sec = args.duration or 1.  # default to 1 second when making noise.

        N_SAMPLES = int(duration_sec*args.sample_rate)
        N_CHANNELS = model.getNumInputs()

        # input_audio = jnp.ones((N_CHANNELS, N_SAMPLES), dtype)
        input_audio = random.uniform(key, shape=(N_CHANNELS, N_SAMPLES), dtype=dtype)

    variables = model.init({'params': key}, input_audio, N_SAMPLES)  
    y, mod_vars = model.apply(variables, input_audio, N_SAMPLES, mutable='intermediates')

    assert y.ndim == 2
    assert y.shape[0] == model.getNumOutputs()
    assert y.shape[1] == input_audio.shape[1]
    assert y.shape[1] == N_SAMPLES

    if args.output is not None:
        from scipy.io import wavfile
        import numpy as np
        output_audio = np.array(y).T
        wavfile.write(args.output, args.sample_rate, output_audio)
        

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description='Run a JAX/Flax model converted from Faust code')
    parser.add_argument('-sr', '--sample-rate', type=int, default=44100, help='Sample rate (such as 44100)')
    parser.add_argument('-d', '--duration', type=float, default=None, help='Duration in seconds')
    parser.add_argument('-i', '--input', type=str, default=None, help='Filepath for input audio WAV')
    parser.add_argument('-o', '--output', type=str, default=None, help='Filepath for output audio WAV')

    args = parser.parse_args()

    test(args)
    print('All done!')
