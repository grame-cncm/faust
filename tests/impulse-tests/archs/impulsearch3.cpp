#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"
#include "faust/dsp/dsp-checker.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new dsp_me_checker(new mydsp()), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new dsp_me_checker(new mydsp()), argv[0], linenum, nbsamples/4);
    runDSP(new dsp_me_checker(new mydsp()), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new dsp_me_checker(new mydsp()), linenum, nbsamples/4, 4);
    runPolyDSP(new dsp_me_checker(new mydsp()), linenum, nbsamples/4, 1);
    
    return 0;
}
