
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"
#include "faust/dsp/rnbo-dsp.h"

int main(int argc, const char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
   
    // print general informations
    printHeader(new rnbo_dsp(), nbsamples);
    
    runDSP(new rnbo_dsp(), argv[0], linenum, nbsamples/4);
    runDSP(new rnbo_dsp(), argv[0], linenum, nbsamples/4, false, true);
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 4);
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 1);
 
    return 0;
}
