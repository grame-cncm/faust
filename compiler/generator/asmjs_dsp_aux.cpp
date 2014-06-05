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

/*
int main(int argc, const char* argv[])
{
    string error;
    char buffer[2048];
    asmjs_dsp_factory(buffer);
    printf("factory = %s\n", buffer);
    return 0;
}
 */

/*
EXPORT string asmjs_dsp_factory(const string& sha_key, int argc, const char* argv[], 
                                 const string& name_app,
                                 const string& dsp_content, 
                                 const string& target, 
                                 string& error_msg, int opt_level)
*/

string factory = "(function noise() { \
        var that = {}; \
        that.iRec0 = new Int32Array(2); \
        that.fVslider0; \
        that.fSamplingFreq; \
        that.metadata = function(m) {  \
        m.declare(\"author\", \"Grame\"); \
        m.declare(\"copyright\", \"(c)GRAME 2009\"); \
        m.declare(\"license\", \"BSD\"); \
        m.declare(\"name\", \"Noise\"); \
        m.declare(\"version\", \"1.1\"); \
        }; \
        that.getNumInputs = function() { \
        return 0; \
        }; \ 
        that.getNumOutputs = function() { \
        return 1; \
        }; \
        that.getInputRate = function(channel) { \
        var rate; \
        switch (channel) { \
        default: { \
        rate = -1; \
        break; \
        }; \
        };\
        return rate;\
        };\
        that.getOutputRate = function(channel) {\
        var rate;\
        switch (channel) {\
        case 0: {\
        rate = 1;\
        break;\
        };\
        default: {\
        rate = -1;\
        break;\
        };\
        };\
        return rate;\
        };\
        that.classInit = function(samplingFreq) {\
        };\
        that.instanceInit = function(samplingFreq) {\
        that.fSamplingFreq = samplingFreq;\
        that.fVslider0 = 0.5;\
        for (var i = 0; (i < 2); i = (i + 1)) {\
        that.iRec0[i] = 0;\
        };\
        };\
        that.init = function(samplingFreq) {\
        that.classInit(samplingFreq);\
        that.instanceInit(samplingFreq);\
        };\
        that.buildUserInterface = function(ui_interface) {\
        ui_interface.openVerticalBox(\"noise\");\
        ui_interface.declare(\"fVslider0\", \"style\", \"knob\");\
        ui_interface.addVerticalSlider(\"Volume\", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(that), 0, 0, 1, 0.1);\
        ui_interface.closeBox();\
        };\
        that.compute = function(count, inputs, outputs) {\
        var output0 = outputs[0];\
        var fSlow0 = (4.65661e-10 * that.fVslider0);\
        for (var i = 0; (i < count); i = (i + 1)) {\
        that.iRec0[0] = (12345 + (1103515245 * that.iRec0[1]));\
        output0[i] = (fSlow0 * that.iRec0[0]);\
        that.iRec0[1] = that.iRec0[0];\
        };\
        };\
       return that;\
       }())";

EXPORT const char* asmjs_dsp_factory(char* dsp_content)
{
    return factory.c_str();
}