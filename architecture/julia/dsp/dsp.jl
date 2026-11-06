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

# UI
abstract type UI end

# Soundfile (the 'soundfile' primitive, see faust/gui/Soundfile.h)
const MAX_SOUNDFILE_PARTS = 256
const SOUNDFILE_BUFFER_SIZE = 1024
const SOUNDFILE_SAMPLE_RATE = 44100

# Several sound files (the 'parts') are concatenated in one buffer per channel.
# Indexes follow the C convention used by the generated code: part P (from 0)
# is stored in fLength[P+1], fSR[P+1], fOffset[P+1], and its frame F (from 0)
# of channel C (from 0) is fBuffers[C+1][fOffset[P+1] + F + 1].
mutable struct Soundfile{T}
    fBuffers::Vector{Vector{T}}  # one buffer per channel
    fLength::Vector{Int32}       # length in frames of each part
    fSR::Vector{Int32}           # sample rate of each part
    fOffset::Vector{Int32}       # offset in frames of each part in the buffers
    fChannels::Int32             # max number of channels of all concatenated files
    fParts::Int32                # number of loaded parts
    fIsDouble::Bool              # T == Float64
end

# Default sound, used until 'addSoundfile!' sets a soundfile: one silent channel
defaultsound(::Type{T}) where {T} =
    Soundfile{T}([zeros(T, SOUNDFILE_BUFFER_SIZE)],
                 fill(Int32(SOUNDFILE_BUFFER_SIZE), MAX_SOUNDFILE_PARTS),
                 fill(Int32(SOUNDFILE_SAMPLE_RATE), MAX_SOUNDFILE_PARTS),
                 zeros(Int32, MAX_SOUNDFILE_PARTS),
                 Int32(1), Int32(0), T == Float64)

# DSP
abstract type dsp end

function getSampleRate(dsp::dsp)
end

function getNumInputs(dsp::dsp)
end

function getNumOutputs(dsp::dsp)
end

function classInit!(sample_rate::Int32)
end

function instanceResetUserInterface!(dsp::dsp)
end

function instanceClear!(dsp::dsp)
end

function instanceInit!(dsp::dsp, sample_rate::Int32)
end

function init!(dsp::dsp, sample_rate::Int32)
end

function getJSON(dsp::dsp)
end

function buildUserInterface!(dsp::dsp, ui_interface::UI)
end

function compute!(dsp::dsp, count::Int32, inputs, outputs)
end
