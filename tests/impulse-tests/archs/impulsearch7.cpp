#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

// Wrapping C++ class used with -ec option.

struct ControlDSP : public decorator_dsp {
    
    ControlDSP(dsp* dsp):decorator_dsp(dsp)
    {}
    
    // This is mandatory
    virtual ControlDSP* clone()
    {
        return new ControlDSP(fDSP->clone());
    }
    
    void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
    {
        fDSP->control();
        fDSP->compute(count, inputs, outputs);
    }
    
};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new ControlDSP(new mydsp()), argv[0], linenum, nbsamples/4);
    runDSP(new ControlDSP(new mydsp()), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new ControlDSP(new mydsp()), linenum, nbsamples/4, 4);
    runPolyDSP(new ControlDSP(new mydsp()), linenum, nbsamples/4, 1);
    
    return 0;
}
