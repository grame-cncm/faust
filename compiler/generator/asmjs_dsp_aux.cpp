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

int main(int argc, const char* argv[])
{
    string error;
    string res = asmjs_dsp_factory("", 0, NULL, "", "", "", error, 0);
    printf("res = %s\n", res.c_str());
    return 0;
}

EXPORT string asmjs_dsp_factory(const string& sha_key, int argc, const char* argv[], 
                                 const string& name_app,
                                 const string& dsp_content, 
                                 const string& target, 
                                 string& error_msg, int opt_level)
{
    return  "function noise() { \
        this.iRec0 = new Int32Array(2); \
        this.fVslider0; \
        this.fSamplingFreq; \
        this.metadata = function(m) {  \
            m.declare(\"author\", \"Grame\"); \
            m.declare(\"copyright\", \"(c)GRAME 2009\"); \
            m.declare(\"license\", \"BSD\"); \
            m.declare(\"name\", \"Noise\"); \
            m.declare(\"version\", \"1.1\"); \
        } \
        this.getNumInputs = function() { \
            return 0; \
        } \ 
        this.getNumOutputs = function() { \
            return 1; \
        } \
        this.getInputRate = function(channel) { \
            var rate; \
            switch (channel) { \
                default: { \
                    rate = -1; \
                    break; \
                } \
            }\
            return rate;\
        }\
        this.getOutputRate = function(channel) {\
            var rate;\
            switch (channel) {\
                case 0: {\
                    rate = 1;\
                    break;\
                }\
                default: {\
                    rate = -1;\
                    break;\
                }\
            }\
            return rate;\
        }\
        this.classInit = function(samplingFreq) {\
        }\
        this.instanceInit = function(samplingFreq) {\
            this.fSamplingFreq = samplingFreq;\
            this.fVslider0 = 0;\
            for (var i = 0; (i < 2); i = (i + 1)) {\
                this.iRec0[i] = 0;\
            }\
        }\
        this.init = function(samplingFreq) {\
            this.classInit(samplingFreq);\
            this.instanceInit(samplingFreq);\
        }\
        this.buildUserInterface = function(ui_interface) {\
            ui_interface.openVerticalBox(\"noise\");\
            ui_interface.declare(\"fVslider0\", \"style\", \"knob\");\
            ui_interface.addVerticalSlider(\"Volume\", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, 0, 1, 0.1);\
            ui_interface.closeBox();\
        }\
        this.compute = function(count, inputs, outputs) {\
            var output0 = outputs[0];\
            var fSlow0 = (4.65661e-10 * this.fVslider0);\
            for (var i = 0; (i < count); i = (i + 1)) {\
                this.iRec0[0] = (12345 + (1103515245 * this.iRec0[1]));\
                output0[i] = (fSlow0 * this.iRec0[0]);\
                this.iRec0[1] = this.iRec0[0];\
            }\
        }\
    }";
}