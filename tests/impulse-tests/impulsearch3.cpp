#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <string>
#include <map>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <cfenv>
#include <cmath>
#include <cfloat>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/gui/console.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/gui/FUI.h"
#include "faust/audio/channels.h"

using std::max;
using std::min;

#define kFrames 64

using namespace std;

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

static inline FAUSTFLOAT normalize(FAUSTFLOAT f)
{
    if (std::isnan(f)) {
        cerr << "ERROR : isnan" << std::endl;
        exit(-1);
    } else if (!std::isfinite(f)) {
        cerr << "ERROR : !isfinite" << std::endl;
        exit(-1);
    }
    return (fabs(f) < FAUSTFLOAT(0.000001) ? FAUSTFLOAT(0.0) : f);
}
            
int main(int argc, char* argv[])
{
    FAUSTFLOAT fnbsamples;
    char rcfilename[256];
    
    int argc1 = 1;
    const char* argv1[1];
    argv1[0] = "-double";
    
    string error_msg;
    interpreter_dsp_factory* factory = createInterpreterDSPFactoryFromFile(argv[1], argc1, argv1, error_msg);
    if (!factory) {
        cerr << "createInterpreterDSPFactoryFromFile " << error_msg << endl;
        exit(-1);
    }
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        exit(-1);
    }
  
    CMDUI* interface = new CMDUI(argc, argv);
    DSP->buildUserInterface(interface);
    interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);
    
    FUI finterface;
    string filename = argv[1];
    filename = filename.substr(0, filename.find ('.'));
    snprintf(rcfilename, 255, "%src", filename.c_str());
    
    DSP->buildUserInterface(&finterface);
 
    // init signal processor and the user interface values:
    DSP->init(44100);

    // modify the UI values according to the command - line options:
    interface->process_command();

    int nins = DSP->getNumInputs();
    channels ichan(kFrames, nins);

    int nouts = DSP->getNumOutputs();
    channels ochan(kFrames, nouts);

    int nbsamples = int(fnbsamples);
    int linenum = 0;
    int run = 0;
    
    // recall saved state
    finterface.recallState(rcfilename);
    
    // print general informations
    printf("number_of_inputs  : %3d\n", nins);
    printf("number_of_outputs : %3d\n", nouts);
    printf("number_of_frames  : %6d\n", nbsamples);
    
    // print audio frames
    while (nbsamples > 0) {
        if (run == 0) {
            ichan.impulse();
            finterface.setButtons(true);
        }
        if (run == 1) {
            ichan.zero();
            finterface.setButtons(false);
        }
        int nFrames = min(kFrames, nbsamples);
        DSP->compute(nFrames, ichan.buffers(), ochan.buffers());
        run++;
        for (int i = 0; i < nFrames; i++) {
            printf("%6d : ", linenum++);
            for (int c = 0; c < nouts; c++) {
                FAUSTFLOAT f = normalize(ochan.buffers()[c][i]);
                printf(" %8.6f", f);
            }
            printf("\n");
        }
        nbsamples -= nFrames;
    }
    return 0;
}
