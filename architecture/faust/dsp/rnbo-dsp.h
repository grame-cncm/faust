#include <iostream>

#include "rnbo/rnbo/RNBO.h"
#include "rnbo/rnbo/RNBO.cpp"
#include "rnbo/rnbo_source.cpp"

struct rnbo_dsp : public dsp {
    
    RNBO::CoreObject fDSP;
    int fSampleRate;
    
    void init(int sample_rate)
    {
        // Inlined
        // classInit(sample_rate);
        instanceInit(sample_rate);
    }
    
    int getNumInputs() { return fDSP.getNumInputChannels(); }
    int getNumOutputs() { return fDSP.getNumOutputChannels(); }
    
    int getSampleRate() { return fSampleRate; }
    
    void instanceInit(int sample_rate)
    {
        fSampleRate = sample_rate;
        fDSP.prepareToProcess(sample_rate, 512, true);
    }
    
    void instanceConstants(int sample_rate)
    {}
    void instanceResetUserInterface()
    {}
    void instanceClear()
    {}
    
    void buildUserInterface(UI* ui_interface)
    {}
    
    dsp* clone()
    {
        return new rnbo_dsp();
    }
    void metadata(Meta* m)
    {}
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        fDSP.process(inputs, fDSP.getNumInputChannels(), outputs, fDSP.getNumOutputChannels(), count);
    }
    
};
