
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/dsp/interpreter-dsp.h"
#include "controlTools.h"

int main(int argc, char* argv[])
{
    string factory_str;
    interpreter_dsp_factory* factory = NULL;
    
    bool inpl = isopt(argv, "-inpl");
    
    if (endsWith(argv[1], ".dsp")) {
        
        {
            int argc1 = argc - 2;
            const char* argv1[argc1];
            for (int i = 0; i < argc - 2;  i++) {
                argv1[i] = argv[i + 2];
            }
            
            // Test factory generated from compilation
            string error_msg;
            factory = createInterpreterDSPFactoryFromFile(argv[1], argc1, argv1, error_msg);
            if (!factory) {
                cerr << "Error in createInterpreterDSPFactory " << error_msg  << endl;
                exit(-1);
            }
            runFactory(factory, argv[1]);
            runFactory(factory, argv[1], true);
            runFactory(factory, argv[1], false, inpl);
            
            // Polyphony
            testPolyphony1(factory);
            testPolyphony1(factory, true);
        }
        
        {
            string error_msg;
            // Test writeInterpreterDSPFactoryToBitcodeFile/readInterpreterDSPFactoryFromBitcodeFile
            writeInterpreterDSPFactoryToBitcodeFile(factory, "/var/tmp/interp-factory.fbc");
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
            factory = readInterpreterDSPFactoryFromBitcodeFile("/var/tmp/interp-factory.fbc", error_msg);
            if (!factory) {
                cerr << "Error in readInterpreterDSPFactoryFromBitcodeFile" << error_msg << endl;
                exit(-1);
            }
            runFactory(factory, argv[1]);
            runFactory(factory, argv[1], true);
        }
        
        {
            string error_msg;
            // Test writeInterpreterDSPFactoryToBitcode/readInterpreterDSPFactoryFromBitcode
            factory_str = writeInterpreterDSPFactoryToBitcode(factory);
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
            factory = readInterpreterDSPFactoryFromBitcode(factory_str, error_msg);
            if (!factory) {
                cerr << "Error in readInterpreterDSPFactoryFromBitcode" << error_msg << endl;
                exit(-1);
            }
            runFactory(factory, argv[1]);
            runFactory(factory, argv[1], true);
        }
     
    } else {
        
        // Test factory generated from file
        string error_msg;
        factory = readInterpreterDSPFactoryFromBitcodeFile(argv[1], error_msg);
        if (!factory) {
            cerr << "Error in readInterpreterDSPFactoryFromBitcodeFile" << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
  
    return 0;
}
