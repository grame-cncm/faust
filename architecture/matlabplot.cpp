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
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "faust/gui/UI.h"
#include "faust/gui/console.h"
#include "faust/gui/meta.h"
#include "faust/audio/channels.h"
#include "faust/dsp/dsp.h"

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

mydsp DSP;

#define kFrames 512

int main(int argc, char* argv[])
{
    FAUSTFLOAT fStartAtSample;
    FAUSTFLOAT fnbsamples;
    FAUSTFLOAT srate;

    CMDUI* interface = new CMDUI(argc, argv);
    DSP.buildUserInterface(interface);

    interface->addOption("-s", &fStartAtSample, 0, 0.0, 100000000.0);
    interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);
    interface->addOption("-r", &srate, 44100.0, 1.0, 100000000.0);

    // init signal processor and the user interface values:
    DSP.init(int(srate));

    // modify the UI values according to the command-line options:
    interface->process_command();

    // prepare input channels (if any) with an impulse
    int nins = DSP.getNumInputs();
    channels inchan(kFrames, nins);
    inchan.impulse(); // after each compute we will zero them

    // prepare output channels
    int nouts = DSP.getNumOutputs();
    channels outchan (kFrames, nouts);

    // print usage info:
    printf("%% Usage: octave --persist thisfile.m\n\n");

    // print matlab-compatible matrix syntax followed by a plot command:
    printf("faustout = [ ...\n");

    // skip <start> samples
    int start = int(fStartAtSample);
    while (start > kFrames) {
        DSP.compute(kFrames, inchan.buffers(), outchan.buffers());
        inchan.zero();
        start -= kFrames;
    }
    if (start > 0) {
        DSP.compute(start, inchan.buffers(), outchan.buffers());
    }
    // end skip

    int nbsamples = int(fnbsamples);
    cout << setprecision(numeric_limits<FAUSTFLOAT>::max_digits10);

    while (nbsamples > kFrames) {
        DSP.compute(kFrames, inchan.buffers(), outchan.buffers());
        inchan.zero();
        for (int i = 0; i < kFrames; i++) {
            for (int c = 0; c < nouts; c++) {
                cout << " " << outchan.buffers()[c][i];
            }
            if (i < kFrames-1) {
                printf("; ...\n");
            } else {
                printf("; ...\n%%---- Chunk Boundary ----\n");
            }
        }
        nbsamples -= kFrames;
    }

    if (nbsamples) { // Write out partial-chunk buffer:
        DSP.compute(nbsamples, inchan.buffers(), outchan.buffers());
        inchan.zero();
        for (int i = 0; i < nbsamples; i++) {
            for (int c = 0; c < nouts; c++) {
                cout << " " << outchan.buffers()[c][i];
            }
            printf("; ...\n");
        }
    }
    printf("];\n\n");
    printf("plot(faustout);\n");
    printf("title('Plot generated by %s made using ''faust -a matlabplot.cpp ...''');\n", argv[0]);
    printf("xlabel('Time (samples)');\n");
    printf("ylabel('Amplitude');\n");
    if (nouts > 0) {
        printf("legend(");
        for (int c = 0; c < nouts; c++) {
            printf("'channel %d'", c+1);
            if (c < nouts-1) { printf(","); }
        }
        printf(");\n");
        printf("print -dpdf %s.pdf;\n", argv[0]);
    }
    return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

