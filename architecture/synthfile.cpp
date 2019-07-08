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

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <map>
#include <stack>
#include <string>
#include <time.h>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/GUI/ControlUI.h"
#include "faust/gui/console.h"
#include "faust/GUI/meta.h"
#include "faust/dsp/dsp-tools.h"

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

#define kFrames         512
#define kSampleRate     44100

int main(int argc, char* argv[])
{
	CMDUI* interface = new CMDUI(argc, argv, true);
	DSP.buildUserInterface(interface);
	interface->process_command();
    
    unsigned int nSamples = loptrm(&argc, argv, "--samples", "-s", 44100*5);
		
	// open output file
	SNDFILE* out_sf;
    SF_INFO	out_info = { nSamples, kSampleRate, DSP.getNumOutputs(),
        SF_FORMAT_WAV|SF_FORMAT_PCM_16|SF_ENDIAN_LITTLE, 0, 0};
    
	out_sf = sf_open(interface->input_file(), SFM_WRITE, &out_info);
	if (out_sf == NULL) { 
		cerr << "Error: "; 
		sf_perror(out_sf); 
		exit(1); 
	}
	
	// create interleaver
	Interleaver ilv(kFrames, DSP.getNumOutputs(), DSP.getNumOutputs());
	
	// init signal processor
	DSP.init(kSampleRate);
	interface->process_init();

	// process all samples
    int frames = nSamples;
 	int nbf = 0;
	do {
        if (frames > kFrames) {
            nbf = kFrames;
            frames -= kFrames;
        } else {
		 	nbf = frames;
		 	frames = 0;
        }
		DSP.compute(nbf, 0, ilv.inputs());
		ilv.interleave();
		sf_writef_float(out_sf, ilv.output(), nbf);		
	} while (nbf);
	
	sf_close(out_sf);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

