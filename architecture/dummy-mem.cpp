/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#include <libgen.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <math.h>

#include "faust/gui/UI.h"
#include "faust/misc.h"
#include "faust/audio/dummy-audio.h"

/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

<<includeclass>>

using namespace std;

mydsp* DSP;

#define SAMPLE_RATE 48000

// Simple heap based custom memory manager

struct malloc_memory_manager : public dsp_memory_manager {
    
    void* allocate(size_t size)
    {
        void* res = malloc(size);
        cout << "malloc_manager: " << size << endl;
        return res;
    }
    virtual void destroy(void* ptr)
    {
        cout << "free_manager" << endl;
        free(ptr);
    }
    
};

int main(int argc, char* argv[])
{
    // Custom memory manager with 'placement' new used to allocate the DSP object
    malloc_memory_manager manager;
    DSP = new (manager.allocate(sizeof(mydsp))) mydsp();
    
    // Static class allocation with custom memory manager called once
    mydsp::classInit(SAMPLE_RATE, &manager);
    
    /// Audio rendering
    dummyaudio audio(SAMPLE_RATE, 512, 5, false, true);  // custom memory manager is used
    audio.init("Dummy", DSP);   // 'instanceInit' only will be called on the DSP
    audio.start();
    audio.stop();
    
    // DSP destructor called, then custom memory manager used to destroy the DSP object
    DSP->~mydsp();
    manager.destroy(DSP);
    
    // DSP static data is *not* destroyed in this simple case, the custom memory manager will have to handle that case if needed.
    
    return 0;
}
