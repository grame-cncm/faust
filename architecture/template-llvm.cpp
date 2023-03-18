/************************************************************************
 ************************************************************************
 FAUST API Architecture File
 Copyright (C) 2022 GRAME, Centre National de Creation Musicale
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
 ************************************************************************
 ************************************************************************/

#ifndef  __template_llvm__
#define  __template_llvm__

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>

#include "faust/dsp/llvm-dsp.h"

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

using namespace std;

/*
 A template that uses libfaust + LLVM backend to dynamically compile a foo.dsp file.
 To be used with the -inj option in faust2xx tools like:
 
 faust2cagtk -inj template-llvm.cpp faust2cagtk-llvm.dsp (a dummy DSP)
 to generate a monophonic 'faust2cagtk-llvm' application.
  
 or:
 
 faust2cagtk -inj template-llvm.cpp -midi -nvoices 8 faust2cagtk-llvm.dsp
 to generate a polyphonic (8 voices), MIDI controllable 'faust2cagtk-llvm' application.
 
 Note that libfaust and LLVM libraries still have to be added at the link stage,
 so a '-dyn : create libfaust + LLVM backend dynamic version' option has been added to the faust2cagtk tool and some others.

 Then 'faust2cagtk-llvm' will ask for a DSP to compile:
 
 ./faust2cagtk-llvm
 <Enter a foo.dsp file>
 
 Note that the resulting binary keeps its own control options, like:
 
 ./faust2cagtk-llvm -h
 ./faust2cagtk-llvm [--frequency <val>] [--buffer <val>] [--nvoices <val>]
    [--control <0/1>] [--group <0/1>] [--virtual-midi <0/1>]
 
So ./faust2cagtk-llvm --nvoices 16 starts the program with 16 voices.
*/

class mydsp final : public dsp {
    
 private:
    
    llvm_dsp_factory* fFactory;
    llvm_dsp* fDSP;
    static string gFileName;
    
 public:
    
    // May be called several times (for instance with the polyphonic architecture),
    // so get the wanted filename only once at first call.
    mydsp()
    {
        if (gFileName == "") {
            // Reading the DSP filename on the standard input
            cout << "<Enter a foo.dsp file>\n";
            getline(cin, gFileName);
        }
        string error_msg;
        if (sizeof(FAUSTFLOAT) == 8) {
            const char* argv[] = {"-double"};
            fFactory = createDSPFactoryFromFile(gFileName, 1, argv, "", error_msg, -1);
        } else {
            fFactory = createDSPFactoryFromFile(gFileName, 0, nullptr, "", error_msg, -1);
        }
        if (!fFactory) {
            cerr << "Cannot create factory : " << error_msg;
            exit(EXIT_FAILURE);
        }
        fDSP = fFactory->createDSPInstance();
        if (!fDSP) {
            cerr << "Cannot create instance "<< endl;
            exit(EXIT_FAILURE);
        }
    }
    
    // Called by the 'clone' method.
    // The factory is kept once in the first mydsp actually allocating it.
    mydsp(llvm_dsp* dsp):fFactory(nullptr), fDSP(dsp)
    {}
    
    ~mydsp()
    {
        // All kept DSP are finally deallocated by the factory
        deleteDSPFactory(fFactory);
    }
    
    void metadata(Meta* m)
    {
        fDSP->metadata(m);
    }

    int getNumInputs()
    {
        return fDSP->getNumInputs();
    }
    int getNumOutputs()
    {
        return fDSP->getNumOutputs();
    }
        
    void instanceConstants(int sample_rate)
    {
        fDSP->instanceConstants(sample_rate);
    }
    
    void instanceResetUserInterface()
    {
        fDSP->instanceResetUserInterface();
    }
    
    void instanceClear()
    {
        fDSP->instanceClear();
    }
    
    void init(int sample_rate)
    {
        fDSP->init(sample_rate);
    }
    
    void instanceInit(int sample_rate)
    {
        fDSP->instanceInit(sample_rate);
    }
    
    mydsp* clone()
    {
        return new mydsp(fDSP->clone());
    }
    
    int getSampleRate()
    {
        return fDSP->getSampleRate();
    }
    
    void buildUserInterface(UI* ui_interface)
    {
        fDSP->buildUserInterface(ui_interface);
    }
    
    void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
    {
        fDSP->compute(count, inputs, outputs);
    }

};

string mydsp::gFileName;

#endif
