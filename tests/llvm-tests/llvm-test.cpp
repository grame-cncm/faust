/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/libfaust.h"
#include "faust/audio/dummy-audio.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/misc.h"

using namespace std;

// To do CPU native compilation
#ifndef JIT_TARGET
#define JIT_TARGET ""
#endif

// To do cross-compilation for a given target
//#define JIT_TARGET "x86_64-apple-darwin20.6.0:westmere"

static void printList(const vector<string>& list)
{
    for (int i = 0; i < list.size(); i++) {
        cout << "item: " << list[i] << "\n";
    }
}

struct TestUI : public GenericUI {
    
    FAUSTFLOAT fInit;
    FAUSTFLOAT fMin;
    FAUSTFLOAT fMax;
    FAUSTFLOAT fStep;
    
    TestUI(FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        fInit = init;
        fMin = min;
        fMax = max;
        fStep = step;
    }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        if (init != fInit) {
            cerr << "ERROR in addVerticalSlider init : " << fInit << " " << init << "\n";
        }
        if (min != fMin) {
            cerr << "ERROR in addVerticalSlider min : " << fMin << " " << min << "\n";
        }
        if (max != fMax) {
            cerr << "ERROR in addVerticalSlider max : " << fMax << " " << max << "\n";
        }
        if (step != fStep) {
            cerr << "ERROR in addVerticalSlider step : " << fStep << " " << step << "\n";
        }
    }
    
};

// The foreign function has to be exported with C linkage and should be made public
FAUST_API extern "C" float ForeignLLVM(float val)
{
    return val + 0.12345;
}

static void Test(const char* dspFileAux)
{
    string error_msg;
    string dspFile = dspFileAux;
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromFile\n";
    {
        llvm_dsp_factory* factory = createDSPFactoryFromFile(dspFile, 0, nullptr, JIT_TARGET, error_msg, -1);
        
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        printList(factory->getLibraryList());
        printList(factory->getIncludePathnames());    
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
        
        cout << "getName " << factory->getName() << endl;
        cout << "getSHAKey " << factory->getSHAKey() << endl;
        
        cout << "Print UI parameters" << endl;
        PrintUI print_ui;
        DSP->buildUserInterface(&print_ui);
        
        dummyaudio audio(1);
        if (!audio.init("FaustDSP", DSP)) {
            exit(EXIT_FAILURE);
        }
        
        audio.start();
        audio.stop();
        
        delete DSP;
        deleteDSPFactory(factory);
    }
    
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromString\n";
    {
        llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", "process = +;", 0, NULL, JIT_TARGET, error_msg, -1);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        printList(factory->getLibraryList());
        printList(factory->getIncludePathnames());
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
        
        cout << "getName " << factory->getName() << endl;
        cout << "getSHAKey " << factory->getSHAKey() << endl;
        
        dummyaudio audio(1);
        if (!audio.init("FaustDSP", DSP)) {
            exit(EXIT_FAILURE);
        }
        
        audio.start();
        audio.stop();
        
        delete DSP;
        deleteDSPFactory(factory);
    }
    
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromString with classInit\n";
    {
        llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(440);", 0, NULL, JIT_TARGET, error_msg, -1);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
    
        // Static tables initialisation
        factory->classInit(44100);
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
     
        // Use "manager" mode to test 'classInit'
        dummyaudio audio(44100, 512, 1 , 512 , true);
        if (!audio.init("FaustDSP", DSP)) {
            exit(EXIT_FAILURE);
        }
        
        audio.start();
        audio.stop();
        
        delete DSP;
        deleteDSPFactory(factory);
    }
    
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromString with getWarningMessages\n";
    {
        const char* argv[8];
        int argc = 0;
        argv[argc++] = "-wall";
        argv[argc] = nullptr; // NULL terminated argv
        string code = "process = rwtable(10, 10.0, idx, _, idx) with { idx = +(1)~_; };";
        llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", code, argc, argv, JIT_TARGET, error_msg, -1);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        printList(factory->getWarningMessages());
        deleteDSPFactory(factory);
    }
    
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromString with registerForeignFunction\n";
    {
        registerForeignFunction("ForeignLLVM");
        llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", "process = ffunction(float ForeignLLVM(float), <dummy.h>, \"\");", 0, NULL, JIT_TARGET, error_msg, -1);
     
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        cout << "getCompileOptions " << factory->getCompileOptions() << endl;
        printList(factory->getLibraryList());
        printList(factory->getIncludePathnames());
    
        // Print LLVM IR code
        // cout << "Code = " << writeDSPFactoryToIR(factory) << endl;
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
        
        cout << "getName " << factory->getName() << endl;
        cout << "getSHAKey " << factory->getSHAKey() << endl;
          
        dummyaudio audio(1);
        if (!audio.init("FaustDSP", DSP)) {
            exit(EXIT_FAILURE);
        }
        
        audio.start();
        audio.stop();
        
        delete DSP;
        deleteDSPFactory(factory);
    }
    
    cout << "=============================\n";
    cout << "Test of UI element encoding\n";
    {
        llvm_dsp_factory* factory = createDSPFactoryFromString("FaustDSP", "process = vslider(\"Volume\", 0.5, 0, 1, 0.025);", 0, NULL, JIT_TARGET, error_msg, -1);
        if (!factory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        
        dsp* DSP = factory->createDSPInstance();
        if (!DSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }

        TestUI test(0.5, 0, 1, 0.025);
        DSP->buildUserInterface(&test);
        
        delete DSP;
        deleteDSPFactory(factory);
    }
    
    // Test generateAuxFilesFromFile/generateAuxFilesFromString to generate a SVG file
    string tempDir = "/private/var/tmp/";
    int argc2 = 0;
    const char* argv2[64];
    argv2[argc2++] = "-svg";
    argv2[argc2++] = "-O";
    argv2[argc2++] = tempDir.c_str();
    argv2[argc2] = nullptr;  // NULL terminated argv
   
    {
        cout << "=============================\n";
        cout << "Test generateAuxFilesFromFile in /private/var/tmp/\n";
        if (!generateAuxFilesFromFile(dspFile, argc2, argv2, error_msg)) {
            cout << "ERROR in generateAuxFilesFromFile : " << error_msg;
        } else {
            string filename = string(dspFile);
            string pathname = tempDir + filename.substr(0, filename.size() - 4) + "-svg";
            ifstream reader(pathname.c_str());
            if (!reader.is_open()) {
                cerr << "ERROR in generateAuxFilesFromFile error : " << pathname << " cannot be opened\n";
            } else {
                cout << "generateAuxFilesFromFile OK\n";
            }
        }
    }
    
    {
        cout << "===============================\n";
        cout << "Test generateAuxFilesFromString in /private/var/tmp/\n";
        if (!generateAuxFilesFromString("FaustDSP", pathToContent(dspFile), argc2, argv2, error_msg)) {
            cout << "generateAuxFilesFromString error : " << error_msg;
        } else {
            string pathname = tempDir + "/FaustDSP-svg";
            ifstream reader(pathname.c_str());
            if (!reader.is_open()) {
                cerr << "ERROR in generateAuxFilesFromString error : " << pathname << " cannot be opened\n";
            } else {
                cout << "generateAuxFilesFromString OK\n";
            }
        }
    }
    
    // Test generateAuxFilesFromString to generate a Cmajor file
    int argc3 = 0;
    const char* argv3[64];
    argv3[argc3++] = "-lang";
    argv3[argc3++] = "cmajor";
    argv3[argc3++] = "-o";
    argv3[argc3++] = "FaustDSP.cmajor";
    argv3[argc3++] = "-O";
    argv3[argc3++] = tempDir.c_str();
    argv3[argc3] = nullptr;  // NULL terminated argv
    {
        cout << "===============================\n";
        cout << "Test generateAuxFilesFromString to use Rust backend in /private/var/tmp/\n";
        if (!generateAuxFilesFromString("FaustDSP", pathToContent(dspFile), argc3, argv3, error_msg)) {
            cout << "generateAuxFilesFromString error : " << error_msg;
        } else {
            string pathname = tempDir + "/FaustDSP.cmajor";
            ifstream reader(pathname.c_str());
            if (!reader.is_open()) {
                cerr << "ERROR in generateAuxFilesFromString error : " << pathname << " cannot be opened\n";
            } else {
                cout << "generateAuxFilesFromString to use Cmajor backend OK\n";
            }
        }
    }
    
}

int main(int argc, char* argv[])
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help") || argc < 2) {
        cout << "llvm-test foo.dsp" << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    std::cout << "getDSPMachineTarget " << getDSPMachineTarget() << std::endl;
   
    // Running in the main thread
    Test(argv[1]);
    
    // Starting in a separated thread
    thread th(&Test, argv[1]);
    th.join();
    
    return 0;
}

