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
#include <sstream>
#include <math.h>
#include <algorithm>
#include <cfenv>
#include <cmath>
#include <cfloat>
#include <vector>

#include "faust/misc.h"
#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/FUI.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/audio/channels.h"
#include "faust/dsp/poly-dsp.h"

using std::max;
using std::min;

#define kFrames 64

using namespace std;

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

//----------------------------------------------------------------------------
// DSP control UI
//----------------------------------------------------------------------------

struct CheckControlUI : public GenericUI {
    
    vector<FAUSTFLOAT> fControlDefault;
    vector<FAUSTFLOAT*> fControlZone;
   
    virtual void addButton(const char* label, FAUSTFLOAT* zone) { addItem(zone, FAUSTFLOAT(0)); }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) { addItem(zone, FAUSTFLOAT(0)); }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        addItem(zone, init);
    }
    
    void addItem(FAUSTFLOAT* zone, FAUSTFLOAT init)
    {
        fControlZone.push_back(zone);
        fControlDefault.push_back(init);
    }
   
    bool checkDefaults()
    {
        for (int i= 0; i < fControlDefault.size(); i++) {
            if (fControlDefault[i] != *fControlZone[i]) return false;
        }
        return true;
    }
    
    void initRandom()
    {
        for (int i= 0; i < fControlZone.size(); i++) {
            *fControlZone[i] = 0.123456789;
        }
    }
};

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

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

static void testPolyphony(dsp* voice)
{
    mydsp_poly* DSP = new mydsp_poly(voice, 4, true, false);
    
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP->buildUserInterface(&controlui);
    controlui.initRandom();
    
    // init signal processor and the user interface values:
    DSP->init(44100);
    
    // Check getSampleRate
    if (DSP->getSampleRate() != 44100) {
        cerr << "ERROR in getSampleRate" << std::endl;
    }
    
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'init'" << std::endl;
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP->instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'instanceResetUserInterface'" << std::endl;
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP->instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'instanceInit'" << std::endl;
    }
    
    // Init again
    DSP->init(44100);
    
    int nins = DSP->getNumInputs();
    channels ichan(kFrames, nins);
    
    int nouts = DSP->getNumOutputs();
    channels ochan(kFrames, nouts);
    
    DSP->keyOn(0, 60, 100);
    DSP->keyOn(0, 67, 100);
    DSP->keyOn(0, 72, 100);
    
    int nbsamples = 1000;
    
    // Compute audio frames
    while (nbsamples > 0) {
        int nFrames = min(kFrames, nbsamples);
        DSP->compute(nFrames, ichan.buffers(), ochan.buffers());
        nbsamples -= nFrames;
    }
    
    delete DSP;
}

int main(int argc, char* argv[])
{
    char rcfilename[256];
    FUI finterface;
    snprintf(rcfilename, 255, "%src", argv[0]);
    
    bool inpl = isopt(argv, "-inpl");
    
    DSP = new mydsp();
    
    DSP->buildUserInterface(&finterface);
 
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP->buildUserInterface(&controlui);
    controlui.initRandom();
    
    // Init signal processor and the user interface values
    DSP->init(44100);
    
    // Check getSampleRate
    if (DSP->getSampleRate() != 44100) {
        cerr << "ERROR in getSampleRate" << std::endl;
    }
   
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'init'" << std::endl;
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP->instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'instanceResetUserInterface'" << std::endl;
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP->instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr << "ERROR in checkDefaults after 'instanceInit'" << std::endl;
    }
    
    // Init again
    DSP->init(44100);
 
    int nins = DSP->getNumInputs();
    int nouts = DSP->getNumOutputs();
    
    channels* ichan = new channels(kFrames, ((inpl) ? std::max(nins, nouts) : nins));
    channels* ochan = (inpl) ? ichan : new channels(kFrames, nouts);

    int nbsamples = 60000;
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
                ichan->impulse();
                finterface.setButtons(true);
            }
            if (run >= 1) {
                ichan->zero();
                finterface.setButtons(false);
            }
            int nFrames = min(kFrames, nbsamples);
            DSP->compute(nFrames, ichan->buffers(), ochan->buffers());
            run++;
            for (int i = 0; i < nFrames; i++) {
                printf("%6d : ", linenum++);
                for (int c = 0; c < nouts; c++) {
                    FAUSTFLOAT f = normalize(ochan->buffers()[c][i]);
                    printf(" %8.6f", f);
                }
                printf("\n");
            }
            nbsamples -= nFrames;
        }
    } catch (...) {
        cerr << "ERROR in " << argv[1] << " line : " << i << std::endl;
    }
    
    testPolyphony(DSP);
    
    return 0;
}
