#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

template <typename REAL>
int main_aux(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // Global external memory
    int iControl[FAUST_INT_CONTROLS];
    REAL fControl[FAUST_REAL_CONTROLS];
    int iZone[FAUST_INT_ZONE];
    REAL fZone[FAUST_FLOAT_ZONE];
    
    // print general informations
    printHeader(new mydsp(iControl, fControl, iZone, fZone), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(iControl, fControl, iZone, fZone), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(iControl, fControl, iZone, fZone), argv[0], linenum, nbsamples/4, false, true);
    
    // DSP clone actually uses the same iControl, fControl, iZone, fZone, so deactivated for now
    //runPolyDSP(new mydsp(iControl, fControl, iZone, fZone), linenum, nbsamples/4, 4);
    //runPolyDSP(new mydsp(iControl, fControl, iZone, fZone), linenum, nbsamples/4, 1);
    
    return 0;
}

int main(int argc, char* argv[])
{
    //return main_aux<fixpoint_t>(argc, argv);
    return main_aux<double>(argc, argv);
}
