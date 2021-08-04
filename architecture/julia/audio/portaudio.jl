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

const FAUSTFLOAT = Float32

# Architecture
include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/meta.jl")
include("/usr/local/share/faust/julia/gui/MapUI.jl")
include("/usr/local/share/faust/julia/gui/GTKUI.jl")
include("/usr/local/share/faust/julia/gui/OSCUI.jl")

# Generated code
<<includeIntrinsic>>
<<includeclass>>

 # Using PortAudio for audio rendiring
 using PortAudio

samplerate = Int32(44100)
block_size = Int32(512)

# Main code

# DSP allocation and init
my_dsp = mydsp()
println("getNumInputs ", getNumInputs(my_dsp))
println("getNumOutputs ", getNumOutputs(my_dsp))
init(my_dsp, samplerate)

map_ui = MapUI(my_dsp)
buildUserInterface(my_dsp, map_ui)

# Print all paths
println(getZoneMap(map_ui))

#= Possibly change control values
- using simple labels (end of path):
setParamValue(map_ui, "freq", 500.0f0)
setParamValue(map_ui, "volume", -10.0f0)
- or using complete path:
setParamValue(map_ui, "/Oscillator/freq", 500.0f0)
setParamValue(map_ui, "/Oscillator/volume", -10.0f0)
=#
   
# OSC controller
osc_ui = OSCUI(my_dsp)
buildUserInterface(my_dsp, osc_ui)
run(osc_ui, false)

# GTK controller (not working for now...)
#=
gtk_ui = GTKUI(my_dsp)
buildUserInterface(my_dsp, gtk_ui)
run(gtk_ui)
=#

devices = PortAudio.devices()

PortAudioStream(1, 2) do stream
    outputs = zeros(REAL, block_size, getNumOutputs(my_dsp))
    while true
        inputs = convert(Matrix{REAL}, read(stream, block_size))
        compute(my_dsp, block_size, inputs, outputs)
        write(stream, outputs)
    end
end

