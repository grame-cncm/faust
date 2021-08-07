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
include("/usr/local/share/faust/julia/audio/portaudio.jl")
include("/usr/local/share/faust/julia/gui/MapUI.jl")
include("/usr/local/share/faust/julia/gui/GTKUI.jl")
include("/usr/local/share/faust/julia/gui/OSCUI.jl")

# Generated code
<<includeIntrinsic>>
<<includeclass>>

# Main code

using ThreadPools

function main!(args)

    # DSP allocation
    my_dsp = mydsp()

    # Audio driver allocation and init
    driver = portaudio(16, 44100)
    init!(driver, "dummy", my_dsp)

    println("getNumInputs: ", getNumInputs(my_dsp))
    println("getNumOutputs: ", getNumOutputs(my_dsp), "\n")
    
     # Print all paths
    map_ui = MapUI(my_dsp)
    buildUserInterface!(my_dsp, map_ui)
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
        run(driver)
    # OSC controller
    elseif args[1] == "-osc"
        ThreadPools.@tspawnat 2 run(driver)
        osc_ui = OSCUI(my_dsp)
        buildUserInterface!(my_dsp, osc_ui)
        # Blocking...
        run(osc_ui)
    # GTK controller
    elseif args[1] == "-gtk"
        ThreadPools.@tspawnat 2 run(driver)
        println("Starting with GTK interface")
        gtk_ui = GTKUI(my_dsp)
        buildUserInterface!(my_dsp, gtk_ui)
        # Blocking...
        run(gtk_ui)
    end

end

# Start the application
main!(ARGS)
