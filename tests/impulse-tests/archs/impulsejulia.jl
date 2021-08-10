
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

const FAUSTFLOAT = Float64

# Architecture
include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/meta.jl")
include("/usr/local/share/faust/julia/gui/MapUI.jl")

# Generated code
<<includeIntrinsic>>
<<includeclass>>

# ControlUI to keep buttons
mutable struct ControlUI <: UI
    ControlUI(dsp::dsp) = begin
        control_ui = new()
        control_ui.dsp = dsp
        control_ui.buttons = Vector{Symbol}()
        control_ui
	end
    dsp::dsp
    buttons::Vector{Symbol}  # list of buttons (of type :fHslider0)
end

# -- active widgets
function addButton!(ui_interface::ControlUI, label::String, param::Symbol) 
    push!(ui_interface.buttons, param)
end

function setButtons!(dsp::mydsp, ui_interface::ControlUI, state::Bool) 
    for field in ui_interface.buttons
        setproperty!(dsp, field, state)
    end
end

# Testing
using Printf

samplerate = Int32(44100)
kFrames = Int32(64)

function impulse!(chans::Int32, inputs)
    for i = 1:chans
        input = @inbounds @view inputs[:, i]
        input[1] = FAUSTFLOAT(1) 
     end
end

function normalize(f::FAUSTFLOAT)
    if isnan(f) 
        println("ERROR : isnan")
        throw(-1)
    elseif isinf(f)
        println("ERROR : isinf")
        throw(-1)
    end
    return (abs(f) < FAUSTFLOAT(0.000001) ? FAUSTFLOAT(0.0) : f)
end

function printHeader(dsp::mydsp, nbsamples::Int32)
    # Print general informations
    @printf "number_of_inputs  : %3d\n" getNumInputs(dsp)
    @printf "number_of_outputs : %3d\n" getNumOutputs(dsp)
    @printf "number_of_frames  : %6d\n" nbsamples
end

function runDSP!(dsp::mydsp, control_ui::ControlUI, nbsamples::Int32)
    run::Int32 = 0
    linenum::Int32 = 0

    nins = getNumInputs(dsp)
    nouts = getNumOutputs(dsp)

    inputs = zeros(REAL, kFrames, nins)
    outputs = zeros(REAL, kFrames, nouts)
  
    try 
        while nbsamples > 0

            if run == 0
                impulse!(nins, inputs)
                setButtons!(dsp, control_ui, true);
            end
            if run >= 1
                inputs = zeros(REAL, kFrames, nins)
                setButtons!(dsp, control_ui, false);
            end
         
            nFrames = min(kFrames, nbsamples)  
            compute!(dsp, nFrames, inputs, outputs);
            run += 1
          
            for i = 1:nFrames
                @printf "%6d : " linenum    
                linenum += 1 
                for c = 1:nouts
                    output = @view outputs[i, :]
                    f::FAUSTFLOAT = normalize(output[c])
                    @printf " %8.6f" f
                end
                println("")
            end
          
            nbsamples -= nFrames
        end
    catch e
        println("ERROR in file ", e)
    end 
end 

main!() = begin
    nbsamples::Int32 = 60000;

    dsp = mydsp{REAL}()
    init!(dsp, samplerate)
    control_ui::ControlUI = ControlUI(dsp)
    buildUserInterface!(dsp, control_ui)
    printHeader(dsp, nbsamples)
    runDSP!(dsp, control_ui, Int32(nbsamples/4))
end

main!()


