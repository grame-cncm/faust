
/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2013 GRAME, Centre National de Creation Musicale
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

 ************************************************************************
 ************************************************************************/

#ifndef __faust_llvm_h__
#define __faust_llvm_h__

#include <libgen.h>
#include <iostream>
#include <stdlib.h>

#include "faust/audio/dummy-audio.h"
#include "faust/gui/PrintUI.h"
#include "faust/dsp/llvm-dsp.h"

#define BUFFER_TO_RENDER 10
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    char jackname[256];
    snprintf(jackname, 255, "%s", basename(argv[0]));
    std::string error_msg;

    if (argc < 2) {
        printf("faust-llvm 'foo.dsp'\n");
        exit(-1);
    }

    // Error check to add....
    // llvm_dsp_factory* factory = createDSPFactoryFromFile(argv[1], argc-2, (const char**)&argv[2], "", error_msg, -1);

    // Another possibility by directly giving the Faust program as a string

    // Additional parameters given to the compiler
    int argc1 = 3;
    const char* argv1[argc];
    argv1[0] = "-vec";
    argv1[1] = "-lv";
    argv1[2] = " 1";

    // Faust program
    std::string faust_program = "process = 1;";

    llvm_dsp_factory* factory = createDSPFactoryFromString("test", faust_program, argc1, argv1, "", error_msg, -1);

    dsp* DSP = createDSPInstance(factory);

    PrintUI interface;
    DSP->buildUserInterface(&interface);

    dummyaudio audio(BUFFER_TO_RENDER);
    audio.init(jackname, DSP);
    audio.start();
    
    // Render BUFFER_TO_RENDER buffers...
    audio.stop();
    return 0;
}

#endif

/*
Compilation :

g++ faust-llvm.cpp /usr/local/lib/libfaust.a `llvm-config --ldflags --libs all` -lz -lcurses -o faust-llvm-static
g++ faust-llvm.cpp -lfaust -L /usr/local/lib `llvm-config --ldflags --libs all` -lz -lcurses -o faust-llvm-shared

Usage (possibly with explicit parameters given to the compiler) : 

./faust-llvm-static karplus.dsp
./faust-llvm-static -vec -lv 1 karplus.dsp
./faust-llvm-static -double -vec -lv 0 -vs 64 karplus.dsp
*/

