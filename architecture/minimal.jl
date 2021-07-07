# ************************************************************************
# FAUST Architecture File
# Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

# Architecture
mutable struct UIGlue
end

const FAUSTFLOAT = Float32

# Generated code
<<includeIntrinsic>>
<<includeclass>>

# Testing
samplerate = Int32(44100)
block_size = Int32(512)

test!() = begin
    dsp = mydsp{Float32}()
    println("getNumInputsmydsp ", getNumInputsmydsp(dsp))
    println("getNumOutputsmydsp ", getNumOutputsmydsp(dsp))
    inputs = zeros(Float32, block_size, getNumInputsmydsp(dsp))
    outputs = zeros(Float32, block_size, getNumOutputsmydsp(dsp))
    initmydsp(dsp, samplerate)
    computemydsp(dsp, block_size, inputs, outputs)
end

test!()