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
