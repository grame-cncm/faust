/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#include "daisysp.h"
#include "daisy_seed.h"

#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#endif

using namespace daisysp;

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

FAUSTFLOAT* finputs[2];
FAUSTFLOAT* foutputs[2];

mydsp DSP;

#define MY_BUFFER_SIZE 8

static daisy_handle seed;

static void AudioCallback(float *in, float *out, size_t size)
{
    // Deinterleave
    for (size_t frame; frame < size; frame++) {
        finputs[0][frame] = in[frame*2];
        finputs[1][frame] = in[frame*2+1];
    }
    
    // Faust processing
    DSP.compute(size, finputs, foutputs);
    
    // Interleave
    for (size_t frame; frame < size; frame++) {
        out[frame*2] = foutputs[0][frame];
        out[frame*2+1] = foutputs[1][frame];
    }
}

int main(void)
{
    // initialize seed hardware and daisysp modules
    daisy_seed_init(&seed);
    
    // set buffer-size
    dsy_audio_set_blocksize(MY_BUFFER_SIZE);
    
    // allocate deinterleaved buffers
    finputs[0] = new FAUSTFLOAT[MY_BUFFER_SIZE];
    finputs[1] = new FAUSTFLOAT[MY_BUFFER_SIZE];
    
    foutputs[0] = new FAUSTFLOAT[MY_BUFFER_SIZE];
    foutputs[1] = new FAUSTFLOAT[MY_BUFFER_SIZE];
    
    // inti Faust DSP
    DSP.init(DSY_AUDIO_SAMPLE_RATE);
    
#ifdef MIDICTRL
    daisy_midi midi_handler;
#endif
 
    // define callback
    dsy_audio_set_callback(DSY_AUDIO_INTERNAL, AudioCallback);

    // start callback
    dsy_audio_start(DSY_AUDIO_INTERNAL);
 
#ifdef MIDICTRL
    midi_handler.startMidi();;
#endif

    while(1) {
    #ifdef MIDICTRL
        midi_handler.processMidi();
    #endif
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
