
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

int main(int argc, char* argv[])
{
    int argc1 = argc - 2;
    const char* argv1[argc1];
    for (int i = 0; i < argc - 2;  i++) {
        argv1[i] = argv[i + 2];
    }
    
    string factory_str;
    llvm_dsp_factory* factory = NULL;
    
    bool inpl = isopt(argv, "-inpl");
    
    {
        // Test factory generated from compilation
        string error_msg;
        factory = createDSPFactoryFromFile(argv[1], argc1, argv1, "", error_msg, 3);
        if (!factory) {
            cerr << "createDSPFactoryFromFile " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
        runFactory(factory, argv[1], false, inpl);
        
        testPolyphony1(factory);
        testPolyphony1(factory, true);
    }
    
    {
        // Test writeDSPFactoryToBitcodeFile/readDSPFactoryFromBitcodeFile
        writeDSPFactoryToBitcodeFile(factory, "/var/tmp/llvm-factory.bc");
        factory = readDSPFactoryFromBitcodeFile("/var/tmp/llvm-factory.bc", "");
        
        if (!factory) {
            cerr << " ERROR in readDSPFactoryFromBitcodeFile " << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        // Test writeDSPFactoryToBitcode/readDSPFactoryFromBitcode
        factory_str = writeDSPFactoryToBitcode(factory);
        factory = readDSPFactoryFromBitcode(factory_str, "");
        
        if (!factory) {
            cerr << " ERROR in readDSPFactoryFromBitcode " << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
   
    {
        // Test writeDSPFactoryToIRFile/readDSPFactoryFromIRFile
        writeDSPFactoryToIRFile(factory, "/var/tmp/llvm-factory.ll");
        factory = readDSPFactoryFromIRFile("/var/tmp/llvm-factory.ll", "");
        
        if (!factory) {
            cerr << " ERROR in readDSPFactoryFromIRFile " << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        // Test writeDSPFactoryToIR/readDSPFactoryFromIR
        factory_str = writeDSPFactoryToIR(factory);
        factory = readDSPFactoryFromIR(factory_str, "");
        
        if (!factory) {
            cerr << " ERROR in readDSPFactoryFromIRFile " << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        // Test writeDSPFactoryToMachineFile/readDSPFactoryFromMachineFile
        writeDSPFactoryToMachineFile(factory, "/var/tmp/llvm-factory-machine", "");
        factory = readDSPFactoryFromMachineFile("/var/tmp/llvm-factory-machine", "");
        
        if (!factory) {
            cerr << " ERROR in readDSPFactoryFromMachineFile " << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        // Test writeDSPFactoryToMachine/readDSPFactoryFromMachine
        factory_str = writeDSPFactoryToMachine(factory, "");
        factory = readDSPFactoryFromMachine(factory_str, "");
        
        if (!factory) {
            cerr << " ERROR in readDSPFactoryFromMachine " << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    return 0;
}
