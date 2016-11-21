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
// DSP control UI
//----------------------------------------------------------------------------

struct CheckControlUI : public UI {
    
    vector<FAUSTFLOAT> fControlDefault;
    vector<FAUSTFLOAT*> fControlZone;
    
    virtual void openTabBox(const char* label) {}
    virtual void openHorizontalBox(const char* label)  {}
    virtual void openVerticalBox(const char* label)  {}
    virtual void closeBox() {};
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone) { fControlZone.push_back(zone); fControlDefault.push_back(FAUSTFLOAT(0)); }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) { fControlZone.push_back(zone); fControlDefault.push_back(FAUSTFLOAT(0)); }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        fControlZone.push_back(zone); fControlDefault.push_back(init);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        fControlZone.push_back(zone); fControlDefault.push_back(init);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        fControlZone.push_back(zone); fControlDefault.push_back(init);
    }
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {}
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {}
    
    virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
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
    FAUSTFLOAT fnbsamples;
    char rcfilename[256];
    
    interpreter_dsp_factory* factory = readInterpreterDSPFactoryFromMachineFile(argv[1]);
    if (!factory) {
        cerr << "Error in readInterpreterDSPFactoryFromMachineFile" << endl;
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
    
    CheckControlUI controlui;
    
    DSP->buildUserInterface(&finterface);
    
    // Get control and then 'initRandom'
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
    } catch (...) {
        cerr << "ERROR in " << argv[1] << " line : " << i << std::endl;
    }
    return 0;
}
