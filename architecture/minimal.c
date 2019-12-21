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

#include <math.h>
#include <stdio.h>

#include "faust/gui/CInterface.h"

#define max(a,b) ((a < b) ? b : a)
#define min(a,b) ((a < b) ? a : b)

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

#define BUFFER_SIZE 64
#define SAMPLE_RATE 44100

int main(int argc, char* argv[])
{
    mydsp* dsp = newmydsp();
    
    printf("DSP inputs: %d\n", getNumInputsmydsp(dsp));
    printf("DSP outputs: %d\n", getNumOutputsmydsp(dsp));
    
    // Init with audio driver SR
    initmydsp(dsp, SAMPLE_RATE);
    
    // Compute one buffer
    FAUSTFLOAT* inputs[getNumInputsmydsp(dsp)];
    FAUSTFLOAT* outputs[getNumOutputsmydsp(dsp)];
    for (int chan = 0; chan < getNumInputsmydsp(dsp); ++chan) {
        inputs[chan] = malloc(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    for (int chan = 0; chan < getNumOutputsmydsp(dsp); ++chan) {
        outputs[chan] = malloc(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    computemydsp(dsp, BUFFER_SIZE, inputs, outputs);
    
    // Print output buffers
    for (int frame = 0; frame < BUFFER_SIZE; ++frame) {
        for (int chan = 0; chan <  getNumOutputsmydsp(dsp); ++chan) {
            printf("Audio output chan: %d sample: %f\n", chan, outputs[chan][frame]);
        }
    }
    
    for (int chan = 0; chan < getNumInputsmydsp(dsp); ++chan) {
        free(inputs[chan]);
    }
    for (int chan = 0; chan < getNumOutputsmydsp(dsp); ++chan) {
        free(outputs[chan]);
    }
    deletemydsp(dsp);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
