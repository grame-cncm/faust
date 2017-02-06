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
#include <ctype.h>

#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream> 

#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/misc.h"
#include "faust/audio/channels.h"

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
	
#define kFrames 512
	
int main(int argc, char *argv[] )
{
	float fnbsamples;

	CMDUI* interface = new CMDUI(argc, argv);
	DSP.buildUserInterface(interface);
	interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);
	
	if (DSP.getNumInputs() > 0) {
		fprintf(stderr, "no inputs allowed\n");
		exit(1);
	}
	
	// init signal processor and the user interface values
	DSP.init(44100);
	
	// modify the UI values according to the command line options
	interface->process_command();
	
	int nouts = DSP.getNumOutputs();
	channels chan (kFrames, nouts);

	int nbsamples = int(fnbsamples);
	while (nbsamples > kFrames) {
		DSP.compute(kFrames, 0, chan.buffers());
		for (int i = 0; i < kFrames; i++) {
			for (int c = 0; c < nouts; c++) {
				printf("%8f\t", chan.buffers()[c][i]);
			}
			std::cout << std::endl;
		}
		nbsamples -= kFrames;
	}
	
	DSP.compute(nbsamples, 0, chan.buffers());
	for (int i = 0; i < nbsamples; i++) {
		for (int c = 0; c < nouts; c++) {
			printf("%8f\t", chan.buffers()[c][i]);
		}
		std::cout << std::endl;
	}
	return 0;
} 
/********************END ARCHITECTURE SECTION (part 2/2)****************/


