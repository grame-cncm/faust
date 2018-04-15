#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <math.h>
#include <list>

#include "faust/dsp/llvm-dsp.h"
#include "faust/gui/GUI.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/audio/channels.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/FUI.h"
#include "faust/misc.h"

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
    
    map<FAUSTFLOAT*, FAUSTFLOAT> fControlZone;
   
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
        fControlZone[zone] = init;
    }
   
    bool checkDefaults()
    {
        map<FAUSTFLOAT*, FAUSTFLOAT>::iterator it;
        for (it = fControlZone.begin(); it != fControlZone.end(); it++) {
            if ((*it).second != *(*it).first) return false;
        }
        return true;
    }
    
    void initRandom()
    {
        map<FAUSTFLOAT*, FAUSTFLOAT>::iterator it;
        for (it = fControlZone.begin(); it != fControlZone.end(); it++) {
            *(*it).first = 0.123456789;
        }
    }
};

// Standard memory manager
struct malloc_memory_manager : public dsp_memory_manager {
    
    virtual void* allocate(size_t size)
    {
        void* res = malloc(size);
        // cout << "malloc_manager: " << size << endl;
        return res;
    }
    
    virtual void destroy(void* ptr)
    {
        //cout << "free_manager" << endl;
        free(ptr);
    }
    
};

static inline FAUSTFLOAT normalize(FAUSTFLOAT f)
{
    if (std::isnan(f)) {
        cerr << "ERROR : isnan" << std::endl;
        throw -1;
    } else if (std::isinf(f)) {
        cerr << "ERROR : isinf" << std::endl;
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

static void testPolyphony1(dsp_factory* factory, bool is_mem_alloc = false)
{
    malloc_memory_manager manager;
    factory->setMemoryManager((is_mem_alloc) ? &manager : nullptr);
    
    mydsp_poly* DSP = new mydsp_poly(factory->createDSPInstance(), 4, true, false);
    if (!DSP) {
        exit(-1);
    }
    
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

static void runFactory(dsp_factory* factory, const string& file, bool is_mem_alloc = false, bool inpl = false)
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
    int nouts = DSP->getNumOutputs();
    
    channels* ichan = new channels(kFrames, ((inpl) ? ((nins > nouts) ? nins : nouts) : nins));
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
            for (i = 0; i < nFrames; i++) {
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
        cerr << "ERROR in " << file << " line : " << i << std::endl;
    }
    
    delete DSP;
}
