/************************************************************************
 FAUST Architecture File
 Copyright (C) 2025-2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

<<includeIntrinsic>>
<<includeclass>>

static mydsp m_dsp;
static MapUI map_ui;

void initDSP(int sampleRate) {
    m_dsp.init(sampleRate);
    m_dsp.buildUserInterface(&map_ui);
}

template <typename T> // for the shake of proper usage and to supress a probable warning
void setParameter(const char* name, T value) {
    map_ui.setParamValue(std::string(name), static_cast<FAUSTFLOAT>(value)); 
}

FAUSTFLOAT getParameter(const char* name) { // Not used. Added for potential future debugging of the parameter's integration
    return map_ui.getParamValue(std::string(name)); 
}