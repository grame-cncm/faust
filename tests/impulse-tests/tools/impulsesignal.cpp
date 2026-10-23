/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2020-2026 GRAME, Centre National de Creation Musicale
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
        cerr << "ERROR in createSignalDSPFactoryFromFile " << error_msg  << endl;
        exit(-1);
    }
    
    dsp* DSP = factory->createDSPInstance();
    if (!DSP) {
        cerr << "ERROR : createDSPInstance " << endl;
        exit(-1);
    }
    
    // print general informations : the signal interpreter is slow, a quarter of the samples
    // is computed, and the header says so (compared with -part)
    printHeader(DSP, nbsamples/4);
    
    runDSP1(factory, argv[1], linenum, nbsamples/4);
   
    delete DSP;
    deleteSignalDSPFactory(factory);
  
    return 0;
}
