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
        memset(res, 0, size);
        return res;
    }
 
    virtual void destroy(void* ptr)
    {
        free(ptr);
    }
    
};

static void printHeader(dsp* DSP, int nbsamples)
{
    // Print general informations
    printf("number_of_inputs  : %3d\n", DSP->getNumInputs());
    printf("number_of_outputs : %3d\n", DSP->getNumOutputs());
    printf("number_of_frames  : %6d\n", nbsamples);
}

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

// To be used in static context
static void runPolyDSP(dsp* dsp, int& linenum, int nbsamples, int num_voices = 4)
{
    mydsp_poly* DSP = new mydsp_poly(dsp, num_voices, true, false);
    
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
    
    for (int i = 0; i < num_voices; i++) {
        DSP->keyOn(0, 60 + i*2, 100);
    }
    
    // Compute audio frames
    while (nbsamples > 0) {
        int nFrames = min(kFrames, nbsamples);
        DSP->compute(nFrames, ichan.buffers(), ochan.buffers());
        // Print samples
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
    
    delete DSP;
}

// To be used in dynamic context (LLVM or interp backends)
static void runPolyDSP1(dsp_factory* factory, int& linenum, int nbsamples, int num_voices = 4, bool is_mem_alloc = false)
{
    malloc_memory_manager manager;
    factory->setMemoryManager((is_mem_alloc) ? &manager : nullptr);
    runPolyDSP(factory->createDSPInstance(), linenum, nbsamples, num_voices);
}

// To be used in static context
static void runDSP(dsp* DSP, const string& file, int& linenum, int nbsamples, bool inpl = false, bool random = false)
{
    char rcfilename[256];
    string filename = file;
    filename = filename.substr(0, filename.find ('.'));
    snprintf(rcfilename, 255, "%src", filename.c_str());
    
    FUI finterface;
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
    
    int run = 0;
    
    // recall saved state
    finterface.recallState(rcfilename);
    
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
            
            if (random) {
                int randval = rand();
                int n1 = randval % nFrames;
                
                if (n1 == 1) n1 = 2;
                if (n1 == 63) n1 = 62;
                
                int n2 = nFrames - n1;
                //std::cerr << "randval " << randval << " nFrames " << nFrames << " linenum " << linenum << " n1 = " << n1 << " n2 = " << n2 << std::endl;
                
                DSP->compute(n1, ichan->buffers(), ochan->buffers());
                DSP->compute(n2, ichan->buffers(n1), ochan->buffers(n1));
            } else {
                //std::cerr << "nFrames = " << nFrames << std::endl;
                
                DSP->compute(nFrames, ichan->buffers(), ochan->buffers());
            }
           
            run++;
            // Print samples
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
        cerr << "ERROR in " << file << " line : " << i << std::endl;
    }
    
    delete ichan;
    if (ochan != ichan) delete ochan;
    delete DSP;
}

// To be used in dynamic context (LLVM or interp backends)
static void runDSP1(dsp_factory* factory, const string& file, int& linenum, int nbsamples, bool is_mem_alloc = false, bool inpl = false, bool random = false)
{
    malloc_memory_manager manager;
    factory->setMemoryManager((is_mem_alloc) ? &manager : nullptr);
    runDSP(factory->createDSPInstance(), file, linenum, nbsamples, inpl, random);
}
