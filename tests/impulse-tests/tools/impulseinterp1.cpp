
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/dsp/interpreter-machine-dsp.h"
#include "controlTools.h"

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // Test factory generated from file
    string error_msg;
    interpreter_dsp_factory* factory = readInterpreterDSPFactoryFromBitcodeFile(argv[1], error_msg);
    
    if (!factory) {
        cerr << "ERROR in readInterpreterDSPFactoryFromBitcodeFile " << error_msg;
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
    runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
    runPolyDSP1(factory, linenum, nbsamples/4, 4);
    runPolyDSP1(factory, linenum, nbsamples/4, 1);
  
    return 0;
}
