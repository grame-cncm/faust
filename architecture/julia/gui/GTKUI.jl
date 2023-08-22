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

using Gtk4, GtkObservables

# GTKUI: a basic GUI developed using the GtkObservables package
mutable struct GTKUI <: UI
    GTKUI(dsp::dsp) = begin
        gtk_ui = new()
        gtk_ui.dsp = dsp
        gtk_ui.box = GtkBox(:v)
        gtk_ui.window = GtkWindow("Faust Program", 400, 200)
        gtk_ui
    end
    dsp::dsp
    window
    box
end

function run!(ui_interface::GTKUI)
    show(ui_interface.window)
    #= 
    if !isinteractive()
        @async Gtk.gtk_main()
        Gtk.waitforsignal(ui_interface.window, :destroy)
    end =#

    if !isinteractive()
        c = Condition()
        signal_connect(ui_interface.window, :destroy) do widget
            notify(c)
        end
        @async Gtk.gtk_main()
        wait(c)
    end
end

# -- active widgets
function addButton!(ui_interface::GTKUI, label::String, param::Symbol)
    button = GtkObservables.button(label)
    obs_func = on(observable(button)) do val
        setproperty!(ui_interface.dsp, param, FAUSTFLOAT(1.0))
        # Hack to make it work...
        sleep(0.1)
        setproperty!(ui_interface.dsp, param, FAUSTFLOAT(0.0))
    end
    push!(ui_interface.box, button)
end

function addCheckButton!(ui_interface::GTKUI, label::String, param::Symbol)
    checkbox = GtkObservables.checkbox()
    obs_func = on(observable(checkbox)) do val
        setproperty!(ui_interface.dsp, param, FAUSTFLOAT(val))
    end
    push!(ui_interface.box, checkbox)
end

function addHorizontalSlider!(ui_interface::GTKUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
    slider = GtkObservables.slider(min:max, value=init, orientation="horizontal")
    label_str = GtkObservables.label(label)
    obs_func = on(observable(slider)) do val
        setproperty!(ui_interface.dsp, param, val)
    end
    box = GtkBox(:h)
    push!(box, slider)
    push!(box, label_str)
    push!(ui_interface.box, box)
end

function addVerticalSlider!(ui_interface::GTKUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
    slider = GtkObservables.slider(min:max, value=init, orientation="vertical")
    set_gtk_property!(slider, :expand, true)
    label_str = GtkObservables.label(label)
    obs_func = on(observable(slider)) do val
        setproperty!(ui_interface.dsp, param, val)
    end
    box = GtkBox(:v)
    push!(box, slider)
    push!(box, label_str)
    push!(ui_interface.box, box)
end

function addNumEntry!(ui_interface::GTKUI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
    nentry = GtkObservables.textbox(FAUSTFLOAT; range=min:max, value=string(init))
    label_str = GtkObservables.label(label)
    obs_func = on(observable(nentry)) do val
        setproperty!(ui_interface.dsp, param, val)
    end
    box = GtkBox(:h)
    push!(box, nentry)
    push!(box, label_str)
    push!(ui_interface.box, box)
end
