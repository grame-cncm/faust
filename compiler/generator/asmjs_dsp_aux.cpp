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

#include "compatibility.hh"

#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#ifndef _WIN32
#include <libgen.h>
#endif

#include "asmjs_dsp_aux.hh"
#include "faust/gui/UIGlue.h"
#include "libfaust.h"
#include "dsp_aux.hh"
#include "timing.hh"
#include "exception.hh"

string gFactory; 

EXPORT const char* createCDSPFactoryFromString(const char* name_app, const char* dsp_content, char* error_msg)
{
    //printf("dsp_content = %s\n", dsp_content);
    int argc = 0;
    
    int argc1 = argc + 5;
 	const char* argv1[32];
    
    argv1[0] = "faust";
	argv1[1] = "-lang";
	argv1[2] = "ajs";
    argv1[3] = "-o";
    argv1[4] = "asmjs";
    
    /*
    for (int i = 0; i < argc; i++) {
        argv1[i+5] = argv[i];
    }
    */
    try {
        gFactory = compile_faust_asmjs(argc1, argv1, name_app, dsp_content, error_msg);
    } catch (...) {
        strncpy(error_msg, "libfaust.js fatal error...", 256);
        gFactory = "";
    }
    printf("error_msg %s\n", error_msg);
    //printf("factory = %s\n", gFactory.c_str());
    return gFactory.c_str();
}
