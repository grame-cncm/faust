#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

malloc_memory_manager gManager;

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    mydsp::fManager = &gManager;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}
