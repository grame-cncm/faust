# ************************************************************************
# FAUST Architecture File
# Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
# ---------------------------------------------------------------------
# This Architecture section is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3 of
# the License, or (at your option) any later version.
 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
 
# You should have received a copy of the GNU General Public License
# along with this program; If not, see <http://www.gnu.org/licenses/>.
 
# EXCEPTION : As a special exception, you may create a larger work
# that contains this FAUST architecture section and distribute
# that work under terms of your choice, so long as this FAUST
# architecture section is not modified.
 
# ************************************************************************
# ************************************************************************/

const FAUSTFLOAT = Float32

# Architectures files
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
    my_dsp = mydsp{REAL}()

    # Audio driver allocation and init
    driver = portaudio(512, 44100)
    init!(driver, "dummy", my_dsp)

    println("getNumInputs: ", getNumInputs(my_dsp))
    println("getNumOutputs: ", getNumOutputs(my_dsp), "\n")
    
     # Print all paths
    map_ui = MapUI(my_dsp)
    buildUserInterface!(my_dsp, map_ui)
    println(getZoneMap(map_ui), "\n")

    #= Possibly manually change control values
    - using simple labels (end of path):
    setParamValue!(map_ui, "freq", 500.0f0)
    setParamValue!(map_ui, "volume", -10.0f0)
    - or using complete path:
    setParamValue!(map_ui, "/Oscillator/freq", 500.0f0)
    setParamValue!(map_ui, "/Oscillator/volume", -10.0f0)
    =#

    # No controller
    if length(args) == 0
        run!(driver)
    # OSC controller
    elseif startswith(args[1], "-osc")
        ThreadPools.@tspawnat 2 run!(driver)
        osc_ui = OSCUI(my_dsp)
        buildUserInterface!(my_dsp, osc_ui)
        if args[1] == "-oscc"
            # Launch external OSC controller
            root = getRoot(osc_ui.map_ui)
            ThreadPools.@tspawnat 2 Base.run(`faust-osc-controller $(root) -port 5001 -outport 5000 -xmit 1`)
        end   
        # Blocking...
        run!(osc_ui)
    # GTK controller
    elseif args[1] == "-gtk"
        ThreadPools.@tspawnat 2 run!(driver)
        println("Starting with GTK interface")
        gtk_ui = GTKUI(my_dsp)
        buildUserInterface!(my_dsp, gtk_ui)
        # Blocking...
        run!(gtk_ui)
    end

end

# Start the application
main!(ARGS)
