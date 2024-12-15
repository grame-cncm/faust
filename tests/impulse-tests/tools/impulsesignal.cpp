
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/dsp/signal-dsp.h"
#include "controlTools.h"

int main(int argc, char* argv[])
{
    signal_dsp_factory* factory = nullptr;
    int linenum = 0;
    int nbsamples = 60000;
        
    int argc1 = argc - 2;
    const char* argv1[argc1];
    for (int i = 0; i < argc - 2;  i++) {
        argv1[i] = argv[i + 2];
    }
    
    // Test factory generated from compilation
    string error_msg;
    factory = createSignalDSPFactoryFromFile(argv[1], argc1, argv1, error_msg);
    
    if (!factory) {
        cerr << "ERROR in createInterpreterDSPFactory " << error_msg  << endl;
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
   
    delete DSP;
    deleteSignalDSPFactory(factory);
  
    return 0;
}
