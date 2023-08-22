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

# Architectures files
include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/UI.jl")

# PathBuilder 
mutable struct PathBuilder
    controlsLevel::Array{String}
end

function pushLabel!(builder::PathBuilder, label::String)
    push!(builder.controlsLevel, label)
end

function popLabel!(builder::PathBuilder)
    deleteat!(builder.controlsLevel, lastindex(builder.controlsLevel))
end

function buildPath(builder::PathBuilder, label::String)
    path = join(builder.controlsLevel, "/")
    res = "/$path/$label"
    for c in [' ', '#', '*', ',', '?', '[', ']', '{', '}', '(', ')']
        res = replace(res, c => '_')
    end
    res
end

# UIZone with for sliders, nentries and bargraph
struct UIZone
    field::Symbol
    init::FAUSTFLOAT
    min::FAUSTFLOAT
    max::FAUSTFLOAT
    step::FAUSTFLOAT
end

# MapUI to keep [path,Symbol] and [label,Symbol] maps
mutable struct MapUI <: UI
    MapUI(dsp::dsp) = begin
        map_ui = new()
        map_ui.dsp = dsp
        map_ui.label_paths = Dict{String,UIZone}()
        map_ui.osc_paths = Dict{String,UIZone}()
        map_ui.path_builder = PathBuilder([])
        map_ui.root = String("")
        map_ui
    end
    dsp::dsp
    path_builder::PathBuilder
    label_paths::Dict{String,UIZone}
    osc_paths::Dict{String,UIZone}
    root::String
end

# -- widget's layouts
function openTabBox!(ui_interface::MapUI, label::String)
    if (ui_interface.root == "")
        ui_interface.root = label
    end
    pushLabel!(ui_interface.path_builder, label)
end
function openHorizontalBox!(ui_interface::MapUI, label::String)
    if (ui_interface.root == "")
        ui_interface.root = label
    end
    pushLabel!(ui_interface.path_builder, label)
end
function openVerticalBox!(ui_interface::MapUI, label::String)
    if (ui_interface.root == "")
        ui_interface.root = label
    end
    pushLabel!(ui_interface.path_builder, label)
end
function closeBox!(ui_interface::MapUI)
    popLabel!(ui_interface.path_builder)
end

# -- active widgets
function addButton!(ui_interface::MapUI, label::String, param::Symbol)
    zone = UIZone(param, 0, 0, 1, 0)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end
function addCheckButton!(ui_interface::MapUI, label::String, param::Symbol)
    zone = UIZone(param, 0, 0, 1, 0)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end
function addHorizontalSlider!(ui_interface::MapUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
    zone = UIZone(param, init, min, max, step)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end
function addVerticalSlider!(ui_interface::MapUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
    zone = UIZone(param, init, min, max, step)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end
function addNumEntry!(ui_interface::MapUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
    zone = UIZone(param, init, min, max, step)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end

# -- passive widgets
function addHorizontalBargraph!(ui_interface::MapUI, label::String, param::Symbol, min::FAUSTFLOAT, max::FAUSTFLOAT)
    zone = UIZone(param, 0, min, max, 0)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end
function addVerticalBargraph!(ui_interface::MapUI, label::String, param::Symbol, min::FAUSTFLOAT, max::FAUSTFLOAT)
    zone = UIZone(param, 0, min, max, 0)
    ui_interface.label_paths[label] = zone
    ui_interface.osc_paths[buildPath(ui_interface.path_builder, label)] = zone
end

# setParamValue/getParamValue
function setParamValue!(ui_interface::MapUI, path::String, value::FAUSTFLOAT)
    if (haskey(ui_interface.osc_paths, path))
        setproperty!(ui_interface.dsp, ui_interface.osc_paths[path].field, value)
    elseif (haskey(ui_interface.label_paths, path))
        setproperty!(ui_interface.dsp, ui_interface.label_paths[path].field, value)
    else
        println("ERROR : setParamValue! '", path, "' not found")
    end
end

function getParamValue(ui_interface::MapUI, path::String)
    if (haskey(ui_interface.osc_paths, path))
        return getproperty(ui_interface.dsp, ui_interface.osc_paths[path].field)
    elseif (haskey(ui_interface.label_paths, path))
        return getproperty(ui_interface.dsp, ui_interface.label_paths[path].field)
    else
        println("ERROR : getParamValue '", path, "' not found")
        return 0
    end
end

function getZoneMap(ui_interface::MapUI)
    return ui_interface.osc_paths
end

function getRoot(ui_interface::MapUI)
    return "/" * ui_interface.root
end