
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"
#include "faust/dsp/cmajor-cpp-dsp.h"

int main(int argc, const char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
   
    // print general informations
    printHeader(new cmajor_cpp_dsp(), nbsamples);
    
    runDSP(new cmajor_cpp_dsp(), argv[0], linenum, nbsamples/4);
    runDSP(new cmajor_cpp_dsp(), argv[0], linenum, nbsamples/4, false, true);
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 4);
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 1);
 
    return 0;
}
