/************************************************************************
 FAUST Architecture File
 Copyright (C) 2023-2026 GRAME, Centre National de Creation Musicale
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

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "/Users/letz/Developpements/faust-johann/tests/impulse-tests/archs/controlTools.h"
#include "/Users/letz/Developpements/faust-johann/architecture/faust/dsp/ysfx-dsp.h"

int main(int argc, const char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
   
    // print general informations
    try {
        printHeader(new ysfx_dsp<FAUSTFLOAT>(argv[1]), nbsamples);
    
        runDSP(new ysfx_dsp<FAUSTFLOAT>(argv[1]), argv[0], linenum, nbsamples/4);
        runDSP(new ysfx_dsp<FAUSTFLOAT>(argv[1]), argv[0], linenum, nbsamples/4, false, true);
    } catch (...) {}
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 4);
    //runPolyDSP(new soul_cpp_dsp(), linenum, nbsamples/4, 1);
 
    return 0;
}
