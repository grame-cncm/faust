#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

// To be used in static context with -mem
static void runDSP2(dsp* DSP, const string& file, int& linenum, int nbsamples, bool inpl = false, bool random = false)
{
    char rcfilename[256];
    string filename = file;
    filename = filename.substr(0, filename.find ('.'));
    snprintf(rcfilename, 255, "%src", filename.c_str());
    
    FUI finterface;
    DSP->buildUserInterface(&finterface);
    
    // Soundfile
    TestMemoryReader memory_reader;
    SoundUI sound_ui("", -1, &memory_reader, (sizeof(FAUSTFLOAT) == sizeof(double)));
    DSP->buildUserInterface(&sound_ui);
    
    // Get control and then 'initRandom'
    CheckControlUI controlui;
    DSP->buildUserInterface(&controlui);
    controlui.initRandom();
    
    // MIDI control
    midi_handler handler;
    MidiUI midi_ui(&handler);
    DSP->buildUserInterface(&midi_ui);
    
    // Init signal processor and the user interface values
    DSP->instanceInit(44100);
    
    // Check getSampleRate
    if (DSP->getSampleRate() != 44100) {
        cerr << "ERROR runDSP in getSampleRate : " << DSP->getSampleRate() << std::endl;
    }
    
    // Check default after 'init'
    if (!controlui.checkDefaults()) {
        cerr << "ERROR runDSP in checkDefaults after 'init'" << std::endl;
    }
    
    // Check default after 'instanceResetUserInterface'
    controlui.initRandom();
    DSP->instanceResetUserInterface();
    if (!controlui.checkDefaults()) {
        cerr << "ERROR runDSP in checkDefaults after 'instanceResetUserInterface'" << std::endl;
    }
    
    // Check default after 'instanceInit'
    controlui.initRandom();
    DSP->instanceInit(44100);
    if (!controlui.checkDefaults()) {
        cerr << "ERROR runDSP in checkDefaults after 'instanceInit'" << std::endl;
    }
    
    // To test that instanceInit properly init a cloned DSP
    DSP = DSP->clone();
    DSP->instanceInit(44100);
    
    // Init UIs on cloned DSP
    DSP->buildUserInterface(&finterface);
    DSP->buildUserInterface(&sound_ui);
    DSP->buildUserInterface(&midi_ui);
    
    int nins = DSP->getNumInputs();
    int nouts = DSP->getNumOutputs();
    
    channels* ichan = new channels(kFrames, ((inpl) ? std::max(nins, nouts) : nins));
    channels* ochan = (inpl) ? ichan : new channels(kFrames, nouts);
    
    int run = 0;
    
    // recall saved state
    finterface.recallState(rcfilename);
    
    // Test MIDI control
    for (int i = 0; i < 127; i++) {
        handler.handleData2(0, midi::MidiStatus::MIDI_CONTROL_CHANGE, 0, i, 100);
        handler.handleData2(0, midi::MidiStatus::MIDI_POLY_AFTERTOUCH, 0, i, 75);
        handler.handleData2(0, midi::MidiStatus::MIDI_NOTE_ON, 0, i, 75);
        handler.handleData2(0, midi::MidiStatus::MIDI_NOTE_OFF, 0, i, 75);
        handler.handleData2(0, midi::MidiStatus::MIDI_PITCH_BEND, 0, i, 4000);
    }
    handler.handleData1(0, midi::MidiStatus::MIDI_PROGRAM_CHANGE, 0, 10);
    handler.handleData1(0, midi::MidiStatus::MIDI_AFTERTOUCH, 0, 10);
    
    GUI::updateAllGuis();
    
    // print audio frames
    int i = 0;
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
                int n2 = nFrames - n1;
                DSP->compute(n1, ichan->buffers(), ochan->buffers());
                DSP->compute(n2, ichan->buffers(n1), ochan->buffers(n1));
            } else {
                DSP->compute(nFrames, ichan->buffers(), ochan->buffers());
            }
            
            run++;
            // Print samples
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
        cerr << "ERROR in '" << file << "' at line : " << i << std::endl;
    }
    
    delete ichan;
    if (ochan != ichan) delete ochan;
    mydsp::destroy(DSP);
}


malloc_memory_manager gManager;

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // Setup the global custom memory manager
    mydsp::fManager = &gManager;
    
    // Make the memory manager get information on all subcontainers,
    // static tables, DSP and arrays
    mydsp::memoryInfo();
    
    // Done once before allocating any DSP
    mydsp::classInit(44100);
    
    // print general informations
    printHeader(mydsp::create(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP2(mydsp::create(), argv[0], linenum, nbsamples/4);
    runDSP2(mydsp::create(), argv[0], linenum, nbsamples/4, false, true);
    //runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    //runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    // Done once after the last DSP has been destroyed
    mydsp::classDestroy();
    
    return 0;
}
