
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
    bool is_vec = false;
    for (int i = 0; i < argc - 2; i++) {
        argv1[i] = argv[i + 2];
        is_vec = is_vec || (strcmp(argv1[i], "-vec") == 0)
                        || (strcmp(argv1[i], "-omp") == 0)
                        || (strcmp(argv1[i], "-sch") == 0);
    }
    
    llvm_dsp_factory* factory = nullptr;
    int linenum = 0;
    int nbsamples = 60000;
    
    bool inpl = isopt(argv, "-inpl");
    
    // Test factory generated from compilation
    {
        string error_msg;
        factory = createDSPFactoryFromFile(argv[1], argc1, argv1, "", error_msg, 3);
        
        if (!factory) {
            cerr << "ERROR in createDSPFactoryFromFile " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4, true);
        runDSP1(factory, argv[1], linenum, nbsamples/4, true, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
        
        /// 'inplace' only works in 'scalar' mode
        if (!is_vec) {
            // print general informations
            printHeader(DSP, nbsamples);
            
            runDSP1(factory, argv[1], linenum, nbsamples/4, false, inpl);
            runDSP1(factory, argv[1], linenum, nbsamples/4, false, inpl, true);
            runPolyDSP1(factory, linenum, nbsamples/4, 4);
            runPolyDSP1(factory, linenum, nbsamples/4, 1);
        }
    }
    
    // Test writeDSPFactoryToBitcodeFile/readDSPFactoryFromBitcodeFile
    {
        string error_msg;
        stringstream str; str << "/var/tmp/llvm-factory" << factory << ".bc";
        if (!writeDSPFactoryToBitcodeFile(factory, str.str())) {
             cerr << "ERROR in writeDSPFactoryToBitcodeFile \n";
        }
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromBitcodeFile(str.str(), "", error_msg);
        
        if (!factory) {
            cerr << "ERROR in readDSPFactoryFromBitcodeFile " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
    
    // Test writeDSPFactoryToBitcode/readDSPFactoryFromBitcode
    {
        string error_msg;
        string factory_str = writeDSPFactoryToBitcode(factory);
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromBitcode(factory_str, "", error_msg);
        
        if (!factory) {
            cerr << "ERROR in readDSPFactoryFromBitcode " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
   
    // Test writeDSPFactoryToIRFile/readDSPFactoryFromIRFile
    {
        string error_msg;
        stringstream str; str << "/var/tmp/llvm-factory" << factory << ".ll";
        if (!writeDSPFactoryToIRFile(factory, str.str())) {
            cerr << "ERROR in writeDSPFactoryToIRFile \n";
        }
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromIRFile(str.str(), "", error_msg);
        
        if (!factory) {
            cerr << "ERROR in readDSPFactoryFromIRFile " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
    
    // Test writeDSPFactoryToIR/readDSPFactoryFromIR
    {
        string error_msg;
        string factory_str = writeDSPFactoryToIR(factory);
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromIR(factory_str, "", error_msg);
        
        if (!factory) {
            cerr << "ERROR in readDSPFactoryFromIRFile " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
    
    // Test writeDSPFactoryToMachineFile/readDSPFactoryFromMachineFile
    {
        string error_msg;
        string machine_file_name = "/var/tmp/" + string(argv[1]) + "-llvm-factory-machine";
        if (!writeDSPFactoryToMachineFile(factory, machine_file_name, "")) {
            cerr << "ERROR in writeDSPFactoryToMachineFile \n";
        }
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromMachineFile(machine_file_name, "", error_msg);
        
        if (!factory) {
            cerr << "ERROR in readDSPFactoryFromMachineFile " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
    
    // Test writeDSPFactoryToMachine/readDSPFactoryFromMachine
    {
        string error_msg;
        string factory_str = writeDSPFactoryToMachine(factory, "");
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        factory = readDSPFactoryFromMachine(factory_str, "", error_msg);
        
        if (!factory) {
            cerr << "ERROR in readDSPFactoryFromMachine " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
    
    // Test expandDSPFromFile
    {
        string sha_key;
        string error_msg;
        string expanded_dsp = expandDSPFromFile(argv[1], argc1, argv1, sha_key, error_msg);
        factory = createDSPFactoryFromString("FausDSP", expanded_dsp, argc1, argv1, "", error_msg, 3);
    
        if (!factory) {
            cerr << "ERROR in expandDSPFromFile " << error_msg;
            exit(-1);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "ERROR in createDSPInstance" << endl;
            exit(-1);
        }
        
        // print general informations
        printHeader(DSP, nbsamples);
        
        runDSP1(factory, argv[1], linenum, nbsamples/4);
        runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
        runPolyDSP1(factory, linenum, nbsamples/4, 4);
        runPolyDSP1(factory, linenum, nbsamples/4, 1);
    }
    
    return 0;
}
