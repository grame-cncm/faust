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

# Architectures files
include("/usr/local/share/faust/julia/audio/audio.jl")

# Using PortAudio for audio rendering
using PortAudio

mutable struct portaudio <: audio
    portaudio(buffer_size::Int, sample_rate::Int) = begin
        driver = new()
        driver.buffer_size = buffer_size
        driver.sample_rate = sample_rate
        driver
    end 
    dsp::dsp
    buffer_size::Int
    sample_rate::Int
    name::String        
end

function init!(driver::portaudio, name::String, dsp::dsp)
    driver.name = name
    driver.dsp = dsp
    init!(dsp, Int32(driver.sample_rate))
end

function run!(driver::portaudio)
    PortAudioStream(1, 2) do stream
        outputs = zeros(FAUSTFLOAT, driver.buffer_size, getNumOutputs(driver.dsp))
        while true
            inputs = convert(Matrix{FAUSTFLOAT}, read(stream, driver.buffer_size))
            compute!(driver.dsp, Int32(driver.buffer_size), inputs, outputs)
            write(stream, outputs)
        end
    end
end
