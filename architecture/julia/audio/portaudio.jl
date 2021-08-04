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

# Testing
samplerate = Int32(44100)
block_size = Int32(512)

# Using PortAudio
using PortAudio

devices = PortAudio.devices()

#dev = filter(x -> x.maxinchans == 2 && x.maxoutchans == 2, devices)[1]
# Selecting a Duplex device here
#dev = devices[10]

#PortAudioStream(dev, dev) do stream
PortAudioStream(1, 2) do stream
    dsp = mydsp()
    
    println("getNumInputs ", getNumInputs(dsp))
    println("getNumOutputs ", getNumOutputs(dsp))
    init(dsp, samplerate)

    map_ui = MapUI(dsp)
    buildUserInterface(dsp, map_ui)

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
    
    # GTK controller
    #gtk_ui = GTKUI(dsp)
    #buildUserInterface(dsp, gtk_ui)
    #Threads.@spawn run(gtk_ui)

    # OSC controller
    osc_ui = OSCUI(dsp)
    buildUserInterface(dsp, osc_ui)
    run(osc_ui, false)

    outputs = zeros(REAL, block_size, getNumOutputs(dsp))
    while true
        inputs = convert(Matrix{REAL}, read(stream, block_size))
        compute(dsp, block_size, inputs, outputs)
        write(stream, outputs)
    end
end
