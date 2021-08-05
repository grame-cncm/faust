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

# Architectures
include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/meta.jl")
include("/usr/local/share/faust/julia/gui/MapUI.jl")
include("/usr/local/share/faust/julia/gui/GTKUI.jl")
include("/usr/local/share/faust/julia/gui/OSCUI.jl")

# Generated code
<<includeIntrinsic>>
<<includeclass>>

 # Using PortAudio for audio rendiring
 using PortAudio, ThreadPools

samplerate = Int32(44100)
block_size = Int32(512)
devices = PortAudio.devices()

function runAudio!(dsp)
    PortAudioStream(1, 2) do stream
    outputs = zeros(REAL, block_size, getNumOutputs(dsp))
    while true
        inputs = convert(Matrix{REAL}, read(stream, block_size))
        compute(dsp, block_size, inputs, outputs)
        write(stream, outputs)
    end
    end
end

# Main code
function main!(args)

    # DSP allocation and init
    my_dsp = mydsp()
    init(my_dsp, samplerate)
    println("getNumInputs ", getNumInputs(my_dsp))
    println("getNumOutputs ", getNumOutputs(my_dsp), "\n")
    
     # Print all paths
    map_ui = MapUI(my_dsp)
    buildUserInterface(my_dsp, map_ui)
    println(getZoneMap(map_ui), "\n")

    #= Possibly manually change control values
    - using simple labels (end of path):
    setParamValue(map_ui, "freq", 500.0f0)
    setParamValue(map_ui, "volume", -10.0f0)
    - or using complete path:
    setParamValue(map_ui, "/Oscillator/freq", 500.0f0)
    setParamValue(map_ui, "/Oscillator/volume", -10.0f0)
    =#

    # No controller
    if length(args) == 0
        runAudio!(my_dsp)
    # OSC controller
    elseif args[1] == "-osc"
        ThreadPools.@tspawnat 2 runAudio!(my_dsp)
        osc_ui = OSCUI(my_dsp)
        buildUserInterface(my_dsp, osc_ui)
        # Blocking...
        run(osc_ui)
    # GTK controller
    elseif args[1] == "-gtk"
        ThreadPools.@tspawnat 2 runAudio!(my_dsp)
        println("Starting with GTK interface")
        gtk_ui = GTKUI(my_dsp)
        buildUserInterface(my_dsp, gtk_ui)
        # Blocking...
        run(gtk_ui)
    end

end

# Start the application
main!(ARGS)
