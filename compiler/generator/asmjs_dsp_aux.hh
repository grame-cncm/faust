/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
 
#ifndef ASMJS_DSP_AUX_H
#define ASMJS_DSP_AUX_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <string>
#include <cstdlib>

#include "faust/gui/CUI.h"
#include "faust/audio/dsp.h"
#include "export.hh"
#include "smartpointer.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

    // Public C interface using asm.js
    EXPORT const char* createAsmCDSPFactoryFromString(const char* name_app, const char* dsp_content, const char* class_name, char* error_msg);
    
#ifdef __cplusplus
}
#endif

#endif
