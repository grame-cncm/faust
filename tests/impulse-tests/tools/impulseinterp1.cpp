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

#include "faust/dsp/interpreter-machine-dsp.h"
#include "controlTools.h"

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // Test factory generated from file
    string error_msg;
    interpreter_dsp_factory* factory = readInterpreterDSPFactoryFromBitcodeFile(argv[1], error_msg);
    
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
    deleteInterpreterDSPFactory(factory);
    return 0;
}
