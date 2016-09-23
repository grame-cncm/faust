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

#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/FUI.h"
#include "faust/gui/UIGlue.h"
#include "faust/audio/channels.h"

using std::max;
using std::min;

#define kFrames 64

using namespace std;

//----------------------------------------------------------------------------
//FAUST generated code
// ----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

mydsp* DSP;

static inline FAUSTFLOAT normalize(FAUSTFLOAT f)
{
    if (std::isnan(f)) {
        cerr << "ERROR : isnan" << std::endl;
        throw -1;
    } else if (!std::isfinite(f)) {
        cerr << "ERROR : !isfinite" << std::endl;
        throw -1;
    }
    return (fabs(f) < FAUSTFLOAT(0.000001) ? FAUSTFLOAT(0.0) : f);
}

int main(int argc, char* argv[])
{
    float fnbsamples;
    char rcfilename[256];
    
    DSP = newmydsp();
    
    CMDUI* interface = new CMDUI(argc, argv);
    UIGlue glue1;
    buildUIGlue(&glue1, interface, true);
    buildUserInterfacemydsp(DSP, &glue1);
    interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);
    
    FUI finterface;
    snprintf(rcfilename, 255, "%src", argv[0]);
    
    UIGlue glue2;
    buildUIGlue(&glue2, &finterface, true);
    buildUserInterfacemydsp(DSP, &glue2);
    
    // init signal processor and the user interface values:
    initmydsp(DSP, 44100);
    
    // modify the UI values according to the command - line options:
    interface->process_command();
    
    int nins = getNumInputsmydsp(DSP);
    channels ichan(kFrames, nins);
    
    int nouts = getNumOutputsmydsp(DSP);
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
    int i;
    try {
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
            computemydsp(DSP, nFrames, ichan.buffers(), ochan.buffers());
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
    } catch (...) {
        cerr << "ERROR in " << argv[1] << " line : " << i << std::endl;
    }
    return 0;
}
