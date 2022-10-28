
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "/Users/letz/Developpements/faust-johann/tests/impulse-tests/archs/controlTools.h"
#include "/Users/letz/Developpements/faust-johann/architecture/faust/dsp/ysfx-dsp.h"

int main(int argc, const char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
   
    // print general informations
    try {
        printHeader(new ysfx_dsp<FAUSTFLOAT>(argv[1]), nbsamples);
    
        runDSP(new ysfx_dsp<FAUSTFLOAT>(argv[1]), argv[0], linenum, nbsamples/4);
        runDSP(new ysfx_dsp<FAUSTFLOAT>(argv[1]), argv[0], linenum, nbsamples/4, false, true);
    } catch (...) {}
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 4);
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 1);
 
    return 0;
}
