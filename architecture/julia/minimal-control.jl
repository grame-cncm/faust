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
include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/meta.jl")
include("/usr/local/share/faust/julia/gui/MapUI.jl")

# Generated code
<<includeIntrinsic>>
<<includeclass>>

# Retrieve the application name
mutable struct NameMeta <: FMeta
    name::String
end

function declare!(m::NameMeta, key::String, value::String)
    if (key == "name") 
        m.name = value;
    end
end

# Testing
samplerate = Int32(44100)
block_size = Int32(512 * 10)

test!() = begin
    # Init DSP
    my_dsp = mydsp{REAL}()
    try 
        init!(my_dsp, samplerate)
    catch (e) 
        println(e)
    end 

    m = NameMeta("")
    metadata!(my_dsp, m)
    println("Application name: ", m.name, "\n")

    println("getNumInputs: ", getNumInputs(my_dsp))
    println("getNumOutputs: ", getNumOutputs(my_dsp), "\n")
    
    # Create a MapUI controller
    map_ui = MapUI(my_dsp)
    buildUserInterface!(my_dsp, map_ui)
  
    inputs = zeros(FAUSTFLOAT, block_size, getNumInputs(my_dsp))
    outputs = zeros(FAUSTFLOAT, block_size, getNumOutputs(my_dsp)) 

    # Test all controllers
    for control in map_ui.osc_paths
        path = control.first
        zone = control.second

        # Test min
        try 
            println("Test min: ", path, " ", zone.min)
            setproperty!(map_ui.dsp, zone.field, zone.min)
            compute!(my_dsp, block_size, inputs, outputs)
            setproperty!(map_ui.dsp, zone.field, zone.init) # reset to init
        catch (e) 
            println(e)
            Base.show_backtrace(stdout, backtrace())
        end

        # Test max
        try 
            println("Test max: ", path, " ", zone.max)
            setproperty!(map_ui.dsp, zone.field, zone.max)
            compute!(my_dsp, block_size, inputs, outputs)
            setproperty!(map_ui.dsp, zone.field, zone.init) # reset to init
        catch (e) 
            println(e)
            Base.show_backtrace(stdout, backtrace())
        end
    end
end

test!()
