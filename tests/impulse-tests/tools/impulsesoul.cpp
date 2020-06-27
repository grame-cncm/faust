
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"
#include "faust/dsp/soulpatch-dsp.h"

int main(int argc, const char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    string error_msg;
    soul_dsp_factory* factory = createSOULDSPFactoryFromFile(argv[1], argc, argv, error_msg);
    if (!factory) {
        cerr << "ERROR in createSOULDSPFactoryFromFile " << error_msg;
        exit(-1);
    }
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "ERROR : createDSPInstance " << endl;
        exit(-1);
    }
    
    // print general informations
    printHeader(DSP, nbsamples);
    
    runDSP1(factory, argv[1], linenum, nbsamples/4);
    //runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
    //runPolyDSP1(factory, linenum, nbsamples/4, 4);
    //runPolyDSP1(factory, linenum, nbsamples/4, 1);
 
    return 0;
}
