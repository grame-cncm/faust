/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

import std.math;
import std.stdio;
import std.conv;
import std.algorithm;
import std.format;
import core.stdc.stdlib;

alias FAUSTFLOAT = float;

class Meta {
nothrow:
@nogc:
    void declare(string name, string value) {}
}

class UI {
nothrow:
@nogc:
    void declare(string id, string key, string value) {}
    void declare(int id, string key, string value) {}
    void declare(FAUSTFLOAT* id, string key, string value) {}

    // -- layout groups

    void openTabBox(string label) {}
    void openHorizontalBox(string label) {}
    void openVerticalBox(string label) {}
    void closeBox() {}

    // -- active widgets

    void addButton(string label, FAUSTFLOAT* val) {}
    void addCheckButton(string label, FAUSTFLOAT* val) {}
    void addVerticalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    void addHorizontalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    void addNumEntry(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}

    // -- passive display widgets

    void addHorizontalBargraph(string label, FAUSTFLOAT* val, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void addVerticalBargraph(string label, FAUSTFLOAT* val, FAUSTFLOAT min, FAUSTFLOAT max) {}
}

interface dsp {
nothrow:
@nogc:
public:
    void metadata(Meta* m);
    int getNumInputs();
    int getNumOutputs();
    void buildUserInterface(UI* uiInterface);
    int getSampleRate();
    void instanceInit(int sample_rate);
    void instanceResetUserInterface();
    void compute(int count, FAUSTFLOAT*[] inputs, FAUSTFLOAT*[] outputs);
    void initialize(int sample_rate);
}

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/


enum int BUFFER_SIZE = 64;
enum int SAMPLE_RATE = 44_100;

void main (string[] args)
{
    mydsp dsp = new mydsp();
    
    writeln(format!"DSP inputs: %d\n"(dsp.getNumInputs()));
    writeln(format!"DSP outputs: %d\n"(dsp.getNumOutputs()));
    
    // Init with audio driver SR
    dsp.initialize(SAMPLE_RATE);
    
    // Compute one buffer
    FAUSTFLOAT*[] inputs = new FAUSTFLOAT*[dsp.getNumInputs()];
    FAUSTFLOAT*[] outputs = new FAUSTFLOAT*[dsp.getNumOutputs()];
    for (int chan = 0; chan < dsp.getNumInputs(); ++chan) {
        inputs[chan] = cast(float*)malloc(FAUSTFLOAT.sizeof * BUFFER_SIZE);
    }
    for (int chan = 0; chan < dsp.getNumOutputs(); ++chan) {
        outputs[chan] = cast(float*)malloc(FAUSTFLOAT.sizeof * BUFFER_SIZE);
    }
    dsp.compute(BUFFER_SIZE, inputs, outputs);
    
    // Print output buffers
    for (int frame = 0; frame < BUFFER_SIZE; ++frame) {
        for (int chan = 0; chan <  dsp.getNumOutputs(); ++chan) {
            writeln(format!"Audio output chan: %d sample: %f\n"(chan, outputs[chan][frame]));
        }
    }
    
    for (int chan = 0; chan < dsp.getNumInputs(); ++chan) {
        free(inputs[chan]);
    }
    for (int chan = 0; chan < dsp.getNumOutputs(); ++chan) {
        free(outputs[chan]);
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
