/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2016-2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/dsp/interpreter-dsp.h"
#include "faust/gui/MapUI.h"
#include "controlTools.h"

int main(int argc, char* argv[])
{
    interpreter_dsp_factory* factory = nullptr;
    
    bool inpl = isopt(argv, "-inpl");
    int linenum = 0;
    int nbsamples = 60000;
    
    if (MapUI::endsWith(argv[1], ".dsp")) {
        
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
            runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, true);
            runPolyDSP1(factory, linenum, nbsamples/4, 4);
            runPolyDSP1(factory, linenum, nbsamples/4, 1);
            
            // print general informations
            printHeader(DSP, nbsamples);
            
            runDSP1(factory, argv[1], linenum, nbsamples/4, true);
            runDSP1(factory, argv[1], linenum, nbsamples/4, true, false, true);
            runPolyDSP1(factory, linenum, nbsamples/4, 4);
            runPolyDSP1(factory, linenum, nbsamples/4, 1);
            
            // print general informations
            printHeader(DSP, nbsamples);
            
            runDSP1(factory, argv[1], linenum, nbsamples/4, false, inpl);
            runDSP1(factory, argv[1], linenum, nbsamples/4, false, inpl, true);
            runPolyDSP1(factory, linenum, nbsamples/4, 4);
            runPolyDSP1(factory, linenum, nbsamples/4, 1);
        
            delete DSP;
        }
        
        {
            string error_msg;
            // Test writeInterpreterDSPFactoryToBitcodeFile/readInterpreterDSPFactoryFromBitcodeFile
            stringstream str; str << "/var/tmp/interp-factory" << factory << ".fbc";
            writeInterpreterDSPFactoryToBitcodeFile(factory, str.str());
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
            factory = readInterpreterDSPFactoryFromBitcodeFile(str.str(), error_msg);
            
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
        
            delete DSP;
        }
        
        {
            string error_msg;
            // Test writeInterpreterDSPFactoryToBitcode/readInterpreterDSPFactoryFromBitcode
            string factory_str = writeInterpreterDSPFactoryToBitcode(factory);
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
            factory = readInterpreterDSPFactoryFromBitcode(factory_str, error_msg);
            
            if (!factory) {
                cerr << "ERROR in readInterpreterDSPFactoryFromBitcode " << error_msg;
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
            runDSP1(factory, argv[1], linenum, nbsamples/4, false, false, false);
            runPolyDSP1(factory, linenum, nbsamples/4, 4);
            runPolyDSP1(factory, linenum, nbsamples/4, 1);
        
            delete DSP;
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
        }
     
    } else {
        
        // Test factory generated from file
        string error_msg;
        factory = readInterpreterDSPFactoryFromBitcodeFile(argv[1], error_msg);
        
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
        
        delete DSP;
        deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
    }
  
    return 0;
}
