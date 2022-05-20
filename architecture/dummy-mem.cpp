/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN dummy-mem.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "faust/gui/UI.h"
#include "faust/misc.h"
#include "faust/audio/dummy-audio.h"

// faust -mem -a dummy-mem.cpp noise.dsp -o noise.cpp && c++ -std=c++11 noise.cpp -o noise && ./noise

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

using namespace std;

#define SAMPLE_RATE 48000

// Simple heap based custom memory manager

struct malloc_memory_manager : public dsp_memory_manager {
    
    virtual void begin(size_t count)
    {
        cout << "malloc_memory_manager::begin count = " << count << endl;
    }
    
    virtual void info(size_t size, size_t reads, size_t writes)
    {
        cout << "malloc_memory_manager::info size = " << size << " reads = " << reads << " writes = " << writes << endl;
    }
    
    virtual void end()
    {
        cout << "malloc_memory_manager::end" << endl;
    }
    
    virtual void* allocate(size_t size)
    {
        void* res = malloc(size);
        cout << "malloc_manager::allocate " << size << endl;
        return res;
    }
    
    virtual void destroy(void* ptr)
    {
        cout << "malloc_memory_manager::destroy" << endl;
        free(ptr);
    }
    
};

static void test1()
{
    // Custom memory manager
    malloc_memory_manager manager;
    
    // Setup manager for the class
    mydsp::fManager = &manager;
    
    // Make the memory manager get information on all subcontainers,
    // static tables, DSP and arrays and prepare memory allocation
    mydsp::memoryInfo();
    
    // Static class allocation with custom memory manager called once
    mydsp::classInit(SAMPLE_RATE);
    
    // 'placement' new used to allocate the DSP object
    mydsp* DSP = mydsp::create();
    
    // Init the DSP instance
    DSP->instanceInit(SAMPLE_RATE);
    
    // Audio rendering
    dummyaudio audio(SAMPLE_RATE, 512, 5, 1, true);  // custom memory manager is used
    
    audio.init("Dummy", DSP);
    audio.start();
    audio.stop();
    
    // DSP destructor called, then custom memory manager used to destroy the DSP object
    mydsp::destroy(DSP);
    
    // DSP static data is destroyed using classDestroy
    mydsp::classDestroy();
}

static void test2()
{
    // Custom memory manager
    malloc_memory_manager manager;
    
    // Setup manager for the class
    mydsp::fManager = &manager;
    
    // Static class allocation with custom memory manager called once
    mydsp::classInit(SAMPLE_RATE);
    
    // 'placement' new used to allocate the DSP objects
    mydsp* DSP1 = mydsp::create();
    mydsp* DSP2 = mydsp::create();
    
    // Init the DSP instance1
    DSP1->instanceInit(SAMPLE_RATE);
    DSP2->instanceInit(SAMPLE_RATE);
    
    /// Audio rendering
    dummyaudio audio(SAMPLE_RATE, 512, 5, 1, true);  // custom memory manager is used
    
    audio.init("Dummy", DSP1);
    audio.start();
    audio.stop();
    
    audio.init("Dummy", DSP2);
    audio.start();
    audio.stop();
    
    // DSP destructor called, then custom memory manager used to destroy the DSP object
    mydsp::destroy(DSP1);
    mydsp::destroy(DSP2);
    
    // DSP static data is destroyed using classDestroy
    mydsp::classDestroy();
}

int main(int argc, char* argv[])
{
    test1();
    //test2();
    
    return 0;
}

/******************** BEGIN dummy-mem.cpp ****************/

