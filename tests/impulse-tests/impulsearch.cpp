/* matlabplot.cpp = simple variation of plot.cpp */
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

#include <math.h>
#include <algorithm>

#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/audio/channels.h"

using std::max;
using std::min;

#define kFrames 512

using namespace std;

struct Meta: map < const char *, const char *>
{
    void declare(const char *key, const char *value)
    {
        (*this)[key] = value;
    }
};

//----------------------------------------------------------------------------
//FAUST generated code
// ----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

mydsp DSP;

static inline float normalize(float f)
{
    return (fabs(f) < 0.000001) ? 0.0 : f;
}

int main(int argc, char *argv[])
{
    float fnbsamples;

    CMDUI* interface = new CMDUI(argc, argv);
    DSP.buildUserInterface(interface);
    interface->addOption("-n", &fnbsamples, 16, 0.0, 100000000.0);

    // init signal processor and the user interface values:
    DSP.init(44100);

    // modify the UI values according to the command - line options:
    interface->process_command();

    int nins = DSP.getNumInputs();
    channels ichan(kFrames, nins);

    int nouts = DSP.getNumOutputs();
    channels ochan(kFrames, nouts);

    int nbsamples = int (fnbsamples);
    int linenum = 0;
    int run = 0;
    
    // print general informations
    printf("number of inputs  : %3d\n", nins);
    printf("number of outputs : %3d\n", nouts);
    printf("number of frames  : %6d\n", nbsamples);
    
    // print audio frames
    while (nbsamples > 0) {
        if (run == 0) ichan.impulse();
        if (run == 1) ichan.zero();
        int nFrames = min(kFrames, nbsamples);
        DSP.compute(nFrames, ichan.buffers(), ochan.buffers());
        run++;
        for (int i = 0; i < nFrames; i++) {
            printf("%6d : ", linenum++);
            for (int c = 0; c < nouts; c++) {
                float f = normalize(ochan.buffers()[c][i]);
                printf(" %8.6f", f);
            }
            printf("\n");
        }
        nbsamples -= nFrames;
    }
    return 0;
}
