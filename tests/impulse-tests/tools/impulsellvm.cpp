
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

int main(int argc, char* argv[])
{
    int argc1 = argc - 2;
 #ifdef WIN32
    const char* argv1[50];
#else
    const char* argv1[argc1];
#endif
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
        string error_msg;
        // Test writeDSPFactoryToBitcodeFile/readDSPFactoryFromBitcodeFile
        writeDSPFactoryToBitcodeFile(factory, "/var/tmp/llvm-factory.bc");
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromBitcodeFile("/var/tmp/llvm-factory.bc", "", error_msg);
        
        if (!factory) {
            cerr << " Error in readDSPFactoryFromBitcodeFile " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        string error_msg;
        // Test writeDSPFactoryToBitcode/readDSPFactoryFromBitcode
        factory_str = writeDSPFactoryToBitcode(factory);
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromBitcode(factory_str, "", error_msg);
        
        if (!factory) {
            cerr << " Error in readDSPFactoryFromBitcode " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
   
    {
        string error_msg;
        // Test writeDSPFactoryToIRFile/readDSPFactoryFromIRFile
        writeDSPFactoryToIRFile(factory, "/var/tmp/llvm-factory.ll");
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromIRFile("/var/tmp/llvm-factory.ll", "", error_msg);
        
        if (!factory) {
            cerr << " Error in readDSPFactoryFromIRFile " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        string error_msg;
        // Test writeDSPFactoryToIR/readDSPFactoryFromIR
        factory_str = writeDSPFactoryToIR(factory);
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromIR(factory_str, "", error_msg);
        
        if (!factory) {
            cerr << " Error in readDSPFactoryFromIRFile " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        string error_msg;
        // Test writeDSPFactoryToMachineFile/readDSPFactoryFromMachineFile
        writeDSPFactoryToMachineFile(factory, "/var/tmp/" + string(argv[1]) + "-llvm-factory-machine", "");
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromMachineFile("/var/tmp/" + string(argv[1]) + "-llvm-factory-machine", "", error_msg);
        
        if (!factory) {
            cerr << " Error in readDSPFactoryFromMachineFile " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    {
        string error_msg;
        // Test writeDSPFactoryToMachine/readDSPFactoryFromMachine
        factory_str = writeDSPFactoryToMachine(factory, "");
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromMachine(factory_str, "", error_msg);
        
        if (!factory) {
            cerr << " Error in readDSPFactoryFromMachine " << error_msg << endl;
            exit(-1);
        }
        runFactory(factory, argv[1]);
        runFactory(factory, argv[1], true);
    }
    
    return 0;
}
