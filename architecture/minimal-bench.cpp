/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
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

#include <iostream>
#include <string>

#include "faust/gui/PrintUI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"
#include "faust/dsp/dsp-bench.h"

// faust -a minimal-bench.cpp noise.dsp -o noise.cpp && c++ -std=c++11 noise.cpp -o noise && ./noise

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

static void bench(dsp* dsp, int dsp_size, const std::string& name, int run)
{
    // Buffer_size and duration in sec of measure
    measure_dsp mes(dsp, 512, 5., true);
    for (int i = 0; i < run; i++) {
        mes.measure();
        std::cout << name << " : " << mes.getStats() << " " << "(DSP CPU % : " << (mes.getCPULoad() * 100) << "), DSP size : " << dsp_size << std::endl;
    }
}

int main(int argc, char* argv[])
{
    mydsp DSP;
    
    // Bench the dsp
    bench(DSP.clone(), sizeof(DSP), "mydsp", 3);

    // Activate the UI, here that only print the control paths
    PrintUI ui;
    DSP.buildUserInterface(&ui);
    
    // Allocate the audio driver to render 5 buffers of 512 frames
    dummyaudio audio(1);
    audio.init("Test", &DSP);
    
    // Render buffers...
    audio.start();
    audio.stop();
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

