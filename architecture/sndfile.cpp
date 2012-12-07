/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
#include "faust/audio/dsp.h"
#include "faust/misc.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#define READ_SAMPLE sf_readf_float
//#define READ_SAMPLE sf_readf_double

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

mydsp	DSP;

class Separator
{
	int		fNumFrames;
	int		fNumInputs;
	int		fNumOutputs;

	FAUSTFLOAT*	fInput;
	FAUSTFLOAT*	fOutputs[256];

  public:

	Separator(int numFrames, int numInputs, int numOutputs)
	{
		fNumFrames 	= numFrames;
		fNumInputs 	= numInputs;
		fNumOutputs = max(numInputs, numOutputs);

		// allocate interleaved input channel
		fInput = (FAUSTFLOAT*) calloc(fNumFrames * fNumInputs, sizeof(FAUSTFLOAT));

		// allocate separate output channels
		for (int i = 0; i < fNumOutputs; i++) {
			fOutputs[i] = (FAUSTFLOAT*) calloc (fNumFrames, sizeof(FAUSTFLOAT));
		}
	}

	~Separator()
	{
		// free interleaved input channel
		free(fInput);

		// free separate output channels
		for (int i = 0; i < fNumOutputs; i++) {
			free(fOutputs[i]);
		}
	}

	FAUSTFLOAT*	input()		{ return fInput; }

	FAUSTFLOAT** outputs()	{ return fOutputs; }

	void 	separate()
	{
		for (int s = 0; s < fNumFrames; s++) {
			for (int c = 0; c < fNumInputs; c++) {
				fOutputs[c][s] = fInput[c + s*fNumInputs];
			}
		}
	}
};

class Interleaver
{
	int		fNumFrames;
	int		fNumInputs;
	int		fNumOutputs;

	FAUSTFLOAT*	fInputs[256];
	FAUSTFLOAT*	fOutput;

  public:

	Interleaver(int numFrames, int numInputs, int numOutputs)
	{
		fNumFrames 	= numFrames;
		fNumInputs 	= max(numInputs, numOutputs);
		fNumOutputs = numOutputs;

		// allocate separate input channels
		for (int i = 0; i < fNumInputs; i++) {
			fInputs[i] = (FAUSTFLOAT*) calloc (fNumFrames, sizeof(FAUSTFLOAT));
		}

		// allocate interleaved output channel
		fOutput = (FAUSTFLOAT*) calloc(fNumFrames * fNumOutputs, sizeof(FAUSTFLOAT));

	}

	~Interleaver()
	{
		// free separate input channels
		for (int i = 0; i < fNumInputs; i++) {
			free(fInputs[i]);
		}

		// free interleaved output channel
		free(fOutput);
	}

	FAUSTFLOAT**	inputs()		{ return fInputs; }

	FAUSTFLOAT* 	output()		{ return fOutput; }

	void 	interleave()
	{
		for (int s = 0; s < fNumFrames; s++) {
			for (int c = 0; c < fNumOutputs; c++) {
				fOutput[c + s*fNumOutputs] = fInputs[c][s];
			}
		}
	}
};

#define kFrames 512

int main(int argc, char *argv[] )
{
	SNDFILE*		in_sf;
	SNDFILE*		out_sf;
	SF_INFO			in_info;
	SF_INFO			out_info;

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	interface->process_command();

	// open input file
	in_info.format = 0;
	in_sf = sf_open (interface->input_file(), SFM_READ, &in_info);
	if (in_sf == NULL) { sf_perror(in_sf); exit(0); }

	// open output file
	out_info = in_info;
    out_info.format = in_info.format;
	out_info.channels = DSP.getNumOutputs();
	out_sf = sf_open(interface->output_file(), SFM_WRITE, &out_info);
	if (out_sf == NULL) { sf_perror(out_sf); exit(0); }


	// create separator and interleaver
	Separator 	sep (kFrames, in_info.channels, DSP.getNumInputs());
	Interleaver ilv (kFrames, DSP.getNumOutputs(), DSP.getNumOutputs());

	// init signal processor
	DSP.init(in_info.samplerate);
	//DSP.buildUserInterface(interface);
	interface->process_init();

	// process all samples
	int nbf;
	do {
        nbf = READ_SAMPLE(in_sf, sep.input(), kFrames);
     	sep.separate();
		DSP.compute(nbf, sep.outputs(), ilv.inputs());
		ilv.interleave();
		sf_writef_float(out_sf, ilv.output(), nbf);
		//sf_write_raw(out_sf, ilv.output(), nbf);
	} while (nbf == kFrames);

	// close the input and output files
	sf_close(in_sf);
	sf_close(out_sf);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/


