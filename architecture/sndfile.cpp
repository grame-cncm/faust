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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sndfile.h>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream>

#include "faust/gui/console.h"
#include "faust/gui/FUI.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-tools.h"
#include "faust/misc.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#define READ_SAMPLE sf_readf_float
//#define READ_SAMPLE sf_readf_double

#define WRITE_SAMPLE sf_writef_float
//#define WRITE_SAMPLE sf_writef_float

using namespace std;

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


// loptrm : Scan command-line arguments and remove and return long int value when found
long loptrm(int* argcP, char* argv[], const char* longname, const char* shortname, long def)
{
    int argc = *argcP;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            int optval = atoi(argv[i]);
            for (int j = i-1; j < argc-2; j++) {  // make it go away for sake of "faust/gui/console.h"
                argv[j] = argv[j+2];
            }
            *argcP -= 2;
            return optval;
        }
    }
    return def;
}

mydsp DSP;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#define kFrames 512

int main(int argc, char* argv[])
{
    CMDUI* interface = new CMDUI(argc, argv, true);
    DSP.buildUserInterface(interface);
    if (argc == 1) {
        interface->printhelp_command(INPUT_OUTPUT_FILE);
        exit(1);
    }
    interface->process_command(INPUT_OUTPUT_FILE);
    
    unsigned int num_samples = loptrm(&argc, argv, "--continue", "-c", 0);
    
    SNDFILE* in_sf;
    SNDFILE* out_sf;
    SF_INFO in_info;
    SF_INFO out_info;
    
    // open input file
    in_info.format = 0;
    in_info.channels = 0;
    in_sf = sf_open(interface->input_file(), SFM_READ, &in_info);
    if (in_sf == NULL) {
        fprintf(stderr, "*** Input file not found.\n");
        sf_perror(in_sf);
        exit(1);
    }
    
    // open output file
    out_info = in_info;
    out_info.format = in_info.format;
    out_info.channels = DSP.getNumOutputs();
    out_sf = sf_open(interface->output_file(), SFM_WRITE, &out_info);
    if (out_sf == NULL) {
        fprintf(stderr, "*** Cannot write output file.\n");
        sf_perror(out_sf);
        exit(1);
    }
    
    // create separator and interleaver
    Deinterleaver sep(kFrames, in_info.channels, DSP.getNumInputs());
    Interleaver ilv(kFrames, DSP.getNumOutputs(), DSP.getNumOutputs());
    
    // init signal processor
    DSP.init(in_info.samplerate);
    interface->process_init();
    
    // process all samples
    int nbf;
    do {
        nbf = READ_SAMPLE(in_sf, sep.input(), kFrames);
        sep.deinterleave();
        DSP.compute(nbf, sep.outputs(), ilv.inputs());
        ilv.interleave();
        WRITE_SAMPLE(out_sf, ilv.output(), nbf);
    } while (nbf == kFrames);
    
    sf_close(in_sf);
    
    // compute tail, if any
    if (num_samples > 0) {
        FAUSTFLOAT* input = (FAUSTFLOAT*)calloc(num_samples * DSP.getNumInputs(), sizeof(FAUSTFLOAT));
        FAUSTFLOAT* inputs[1] = { input };
        Interleaver ailv(num_samples, DSP.getNumOutputs(), DSP.getNumOutputs());
        DSP.compute(num_samples, inputs, ailv.inputs());
        ailv.interleave();
        WRITE_SAMPLE(out_sf, ailv.output(), num_samples);
    }
    
    sf_close(out_sf);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
