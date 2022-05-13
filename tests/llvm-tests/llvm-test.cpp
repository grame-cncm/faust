/************************************************************************
    FAUST Architecture File
    Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/libfaust.h"
#include "faust/audio/dummy-audio.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PrintUI.h"
#include "faust/misc.h"

using namespace std;

// To do CPU native compilation
#define JIT_TARGET ""

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

int main(int argc, char* argv[])
{
    if (isopt((char**)argv, "-h") || isopt((char**)argv, "-help") || argc < 2) {
        cout << "llvm-test foo.dsp" << endl;
        exit(EXIT_FAILURE);
    }
    
    string error_msg;
    cout << "Libfaust version : " << getCLibFaustVersion () << endl;
    string dspFile = argv[1];
    
    std::cout << "getDSPMachineTarget " << getDSPMachineTarget() << std::endl;
   
    cout << "=============================\n";
    cout << "Test createDSPFactoryFromFile\n";
    {
        llvm_dsp_factory* factory = createDSPFactoryFromFile(dspFile, 0, NULL, JIT_TARGET, error_msg, -1);
        
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
            return 0;
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
            return 0;
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
    
    // Test generateAuxFilesFromFile/generateAuxFilesFromString
    string tempDir = "/private/var/tmp/";
    int argc2 = 0;
    const char* argv2[64];
    argv2[argc2++] = "-svg";
    argv2[argc2++] = "-O";
    argv2[argc2++] = tempDir.c_str();
    argv2[argc2] = nullptr;  // NULL terminated argv
   
    {
        cout << "=============================\n";
        cout << "Test generateAuxFilesFromFile\n";
        if (!generateAuxFilesFromFile(dspFile, argc2, argv2, error_msg)) {
            cout << "ERROR in generateAuxFilesFromFile : " << error_msg;
        } else {
            string filename =  string(dspFile);
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
        cout << "Test generateAuxFilesFromString\n";
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
    
    return 0;
}

