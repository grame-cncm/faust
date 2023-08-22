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

# UI architecture
abstract type UI end

# One can override the behavior by defining another set of methods 
# that takes a different concrete UI type. 
# Only the needed methods have to be implemented in subtypes.

# -- widget's layouts
function openTabBox!(ui_interface::UI, label::String)
end
function openHorizontalBox!(ui_interface::UI, label::String)
end
function openVerticalBox!(ui_interface::UI, label::String)
end
function closeBox!(ui_interface::UI)
end

# -- active widgets
function addButton!(ui_interface::UI, label::String, param::Symbol)
end
function addCheckButton!(ui_interface::UI, label::String, param::Symbol)
end
function addHorizontalSlider!(ui_interface::UI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
end
function addVerticalSlider!(ui_interface::UI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
end
function addNumEntry!(ui_interface::UI, label::String, param::Symbol, init::FAUSTFLOAT, min::FAUSTFLOAT, max::FAUSTFLOAT, step::FAUSTFLOAT)
end

# -- passive widgets
function addHorizontalBargraph!(ui_interface::UI, label::String, param::Symbol, min::FAUSTFLOAT, max::FAUSTFLOAT)
end
function addVerticalBargraph!(ui_interface::UI, label::String, param::Symbol, min::FAUSTFLOAT, max::FAUSTFLOAT)
end

# -- soundfiles
function addSoundfile!(ui_interface::UI, label::String, filename::String, soundfile::Symbol)
end

# -- metadata declarations
function declare!(ui_interface::UI, param::Symbol, key::String, val::String)
end
