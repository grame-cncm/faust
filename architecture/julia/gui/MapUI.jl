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

include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/UI.jl")

# PathBuilder 
mutable struct PathBuilder
    controlsLevel::Array{String}
end

function pushLabel(builder::PathBuilder, label::String)
    push!(builder.controlsLevel, label)
end

function popLabel(builder::PathBuilder)
    deleteat!(builder.controlsLevel, lastindex(builder.controlsLevel))
end

function buildPath(builder::PathBuilder, label::String)
    path = join(builder.controlsLevel, "/")
    "/$path/$label"
end

# MapUI to keep [path,Symbol]
mutable struct MapUI <: UI
    MapUI(dsp::dsp) = begin
        map_ui = new()
        map_ui.dsp = dsp
        map_ui.label_paths = Dict{String, Symbol}()
        map_ui.osc_paths = Dict{String, Symbol}()
        map_ui.pathBuilder = PathBuilder([])
        map_ui
	end
    dsp::dsp
    pathBuilder::PathBuilder
    label_paths::Dict{String, Symbol}
    osc_paths::Dict{String, Symbol}
end

# -- widget's layouts
function openTabBox(ui_interface::MapUI, label::String)
    pushLabel(ui_interface.pathBuilder, label)
end
function openHorizontalBox(ui_interface::MapUI, label::String)
    pushLabel(ui_interface.pathBuilder, label)
end
function openVerticalBox(ui_interface::MapUI, label::String)
    pushLabel(ui_interface.pathBuilder, label)
end
function closeBox(ui_interface::MapUI)
    popLabel(ui_interface.pathBuilder)
end

# -- active widgets
function addButton(ui_interface::MapUI, label::String, param::Symbol) 
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end
function addCheckButton(ui_interface::MapUI, label::String, param::Symbol) 
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end
function addHorizontalSlider(ui_interface::MapUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT) 
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end
function addVerticalSlider(ui_interface::MapUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT) 
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end
function addNumEntry(ui_interface::MapUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT) 
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end

# -- passive widgets
function addHorizontalBargraph(ui_interface::MapUI, label::String, param::Symbol, min::FAUSTFLOAT, max::FAUSTFLOAT)
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end
function addVerticalBargraph(ui_interface::MapUI, label::String, param::Symbol, min::FAUSTFLOAT, max::FAUSTFLOAT)
    ui_interface.label_paths[label] = param
    ui_interface.osc_paths[buildPath(ui_interface.pathBuilder, label)] = param
end

# -- soundfiles
function addSoundfile(ui_interface::MapUI, label::String, filename::String, soundfile::Symbol) 
end

# -- metadata declarations
function declare(ui_interface::MapUI, param::Symbol, key::String, val::String) 
end

# setParamValue/getParamValue
function setParamValue(ui_interface::MapUI, path::String, value::FAUSTFLOAT)
    if (haskey(ui_interface.osc_paths, path))
        setproperty!(ui_interface.dsp, ui_interface.osc_paths[path], value)
    elseif (haskey(ui_interface.label_paths, path))
        setproperty!(ui_interface.dsp, ui_interface.label_paths[path], value)
    else 
        println("ERROR : setParamValue '", path, "' not found")
    end
end

function getParamValue(ui_interface::MapUI, path::String)
    if (haskey(ui_interface.osc_paths, path))
        return getproperty(ui_interface.dsp, ui_interface.osc_paths[path])
    elseif (haskey(ui_interface.label_paths, path))
        return getproperty(ui_interface.dsp, ui_interface.label_paths[path])
    else 
        println("ERROR : getParamValue '", path, "' not found")
        return 0;
    end
end

function getMap(ui_interface::MapUI)
    return ui_interface.osc_paths
end

