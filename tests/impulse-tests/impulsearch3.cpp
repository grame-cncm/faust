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
#include "faust/dsp/poly-dsp.h"

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

// Standard memory manager
struct malloc_memory_manager : public dsp_memory_manager {
    
    void* allocate(size_t size)
    {
        void* res = malloc(size);
        //std::cout << "malloc_manager : " << size << " " << res << std::endl;
        return res;
    }
    virtual void destroy(void* ptr)
    {
        //std::cout << "free_manager : " << ptr << std::endl;
        free(ptr);
    }
    
};

static void testPolyphony(dsp_factory* factory, bool is_mem_alloc = false)
{
    malloc_memory_manager manager;
    factory->setMemoryManager((is_mem_alloc) ? &manager : nullptr);
    
    dsp* DSP = new mydsp_poly(factory->createDSPInstance(), 4, true);
    if (!DSP) {
        exit(-1);
    }
    
    delete DSP;
}

static void runFactory(dsp_factory* factory, const string& file, bool is_mem_alloc = false)
{
    char rcfilename[256];
    malloc_memory_manager manager;
    factory->setMemoryManager((is_mem_alloc) ? &manager : nullptr);
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        exit(-1);
    }
    
    FUI finterface;
    string filename = file;
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
    
    int nins = DSP->getNumInputs();
    channels ichan(kFrames, nins);
    
    int nouts = DSP->getNumOutputs();
    channels ochan(kFrames, nouts);
    
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
            for (i = 0; i < nFrames; i++) {
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
        cerr << "ERROR in " << file << " line : " << i << std::endl;
    }
    
    delete DSP;
}

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    string factory_str;
    interpreter_dsp_factory* factory = NULL;
    
    if (endsWith(argv[1], ".dsp")) {
        
        {
            int argc1 = argc - 2;
            const char* argv1[argc1];
            for (int i = 0; i < argc - 2;  i++) {
                argv1[i] = argv[i + 2];
            }
            
            // Test factory generated from compilation
            string error_msg;
            factory = createInterpreterDSPFactoryFromFile(argv[1], argc1, argv1, error_msg);
            if (!factory) {
                cerr << "Error in createInterpreterDSPFactory " << error_msg  << endl;
                exit(-1);
            }
            runFactory(factory, argv[1]);
            runFactory(factory, argv[1], true);
        }
        
        {
            // Test writeInterpreterDSPFactoryToMachineFile/readInterpreterDSPFactoryFromMachineFile
            writeInterpreterDSPFactoryToMachineFile(factory, "/var/tmp/interp-factory.fbc");
            factory = readInterpreterDSPFactoryFromMachineFile("/var/tmp/interp-factory.fbc");
            if (!factory) {
                cerr << "Error in readInterpreterDSPFactoryFromMachineFile" << endl;
                exit(-1);
            }
            runFactory(factory, argv[1]);
            runFactory(factory, argv[1], true);
        }
        
        {
            // Test writeInterpreterDSPFactoryToMachine/readInterpreterDSPFactoryFromMachine
            factory_str = writeInterpreterDSPFactoryToMachine(factory);
            factory = readInterpreterDSPFactoryFromMachine(factory_str);
            if (!factory) {
                cerr << "Error in readInterpreterDSPFactoryFromMachine" << endl;
                exit(-1);
            }
            runFactory(factory, argv[1]);
            runFactory(factory, argv[1], true);
        }
        
        testPolyphony(factory);
        testPolyphony(factory, true);
      
    } else {
        
        // Test factory generated from file
        factory = readInterpreterDSPFactoryFromMachineFile(argv[1]);
        if (!factory) {
            cerr << "Error in readInterpreterDSPFactoryFromMachineFile" << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
  
    return 0;
}
