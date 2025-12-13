/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020-2021 GRAME, Centre National de Creation Musicale
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

#include "daisysp.h"

#ifdef PATCH
#include "daisy_patch.h"
#elif defined POD
#include "daisy_pod.h"
#elif defined PATCHSM
#include "daisy_patch_sm.h"
#else
#include "daisy_seed.h"
#endif

daisy::DaisySeed* seedptr = nullptr;

#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/DaisyControlUI.h"
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#include "faust/gui/MidiUI.h"
#endif

using namespace daisysp;
using namespace std;

#ifdef USE_SDRAM
    #include"faust2daisy_sdram.h"
    #if FAUST_SDRAM_SIZE_BYTES == 0
        #undef USE_SDRAM
    #endif
#endif

#ifdef USE_SDRAM


uint8_t DSY_SDRAM_BSS faust_sdram_mem[ FAUST_SDRAM_SIZE_BYTES ];
struct faustdaisy_dsp_memory_manager : public dsp_memory_manager
{
    struct mem_info_t
    {
        const char *name;
        MemType type;
        size_t size;
        size_t size_bytes; 
        size_t reads;
        size_t writes;
        void *ptr = nullptr; // pointeur to location in memory
    };

    void begin(size_t count) 
    {
        std::fill(faust_sdram_mem, faust_sdram_mem + FAUST_SDRAM_SIZE_BYTES, 0);
        infos.resize(count);
        info_cnt = 0;
        offset = 0;
    } 

    void info(const char * name, MemType type, 
        size_t size, size_t size_bytes, size_t reads, size_t writes) 
    {
        void * ptr = nullptr; 
        bool is_sdram = (std::strcmp(name, "fZone") == 0) || (std::strcmp(name, "iZone") == 0); 
        if(is_sdram)
            ptr = static_cast<void *>(faust_sdram_mem + offset);
        infos[info_cnt] = {name, type, size, size_bytes, reads, writes, ptr};
        ++info_cnt;
        if(is_sdram)
            offset+= size_bytes;
    }

    void end() 
    {
        offset = 0;
        info_cnt = 0;
    }
   
    void *allocate(size_t size_bytes) 
    {
        if(infos[info_cnt].type == MemType::kObj_ptr)
        {
            ++info_cnt;
            return std::malloc(size_bytes);
        }
        void *ptr = infos[info_cnt].ptr;
        ++info_cnt;
        return ptr;
    }

    void destroy(void *ptr) 
    {
        ptr = nullptr; 
    }

    std::vector<mem_info_t> infos;
    size_t offset;
    size_t info_cnt;
};

#endif  // SDRAM

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

#ifdef POLY
#include "faust/dsp/poly-dsp.h"
#endif

#ifdef PATCH
static daisy::DaisyPatch hw;
#elif defined POD
static daisy::DaisyPod hw; 
#elif defined PATCHSM
static daisy::patch_sm::DaisyPatchSM hw; 
#else
static daisy::DaisySeed hw;
#endif

static DaisyControlUI* control_UI = nullptr;
static dsp* DSP = nullptr;

#ifdef MIDICTRL
list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

static void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t count)
{
    // Update controllers
    control_UI->update();
    
    // DSP processing
    DSP->compute(count, const_cast<float**>(in), out);
}

void createDSP() 
{

#ifdef USE_SDRAM 
    #ifdef POLY 
        mydsp::classInit(MY_SAMPLE_RATE);
        DSP = mydsp::create();
        DSP = new mydsp_poly(DSP, NVOICES, true, true);
    #else 
        mydsp::classInit(MY_SAMPLE_RATE);
        DSP = mydsp::create();
    #endif
#else 
    #ifdef POLY 
        DSP = new mydsp();
        DSP = new mydsp_poly(DSP, NVOICES, true, true);
    #else 
        DSP = new mydsp();
    #endif
#endif
}

void initDSP()
{
#ifdef USE_SDRAM 
    #ifdef POLY
    #else 
        DSP->instanceInit(MY_SAMPLE_RATE);
    #endif
#else 
    DSP->init(MY_SAMPLE_RATE);
#endif
}

int main(void)
{
    // (init)ialize seed hardware and daisysp modules
    hw.Init();
/*
    Memory Manager Creation 
*/
#ifdef USE_SDRAM 
    mydsp::fManager = new faustdaisy_dsp_memory_manager();
    mydsp::memoryInfo();
#endif

/*
    DSP Creation 
*/
    DSP = createDSP();

    // set buffer-size
    hw.SetAudioBlockSize(MY_BUFFER_SIZE);
/*
    DSP Initialization
*/
    initDSP();
/*
    Controllers setup 
*/
#if (defined PATCH) || (defined POD)
    control_UI = new DaisyControlUI(&hw.seed, MY_SAMPLE_RATE/MY_BUFFER_SIZE);
    DSP->buildUserInterface(control_UI);
    hw.StartAdc();
#elif defined (PATCHSM)
    control_UI = new DaisyControlUI(&hw, MY_SAMPLE_RATE/MY_BUFFER_SIZE);
    DSP->buildUserInterface(control_UI);
#else
    //initialize UI for seed
    control_UI = new DaisyControlUI(&hw, MY_SAMPLE_RATE/MY_BUFFER_SIZE);
    DSP->buildUserInterface(control_UI);
    // start ADC
    hw.adc.Start();
#endif
    // define and start callback
    hw.StartAudio(AudioCallback);
#ifdef MIDICTRL
    daisy_midi midi_handler;
    MidiUI midi_interface(&midi_handler);
    DSP->buildUserInterface(&midi_interface);
    midi_handler.startMidi();
#endif
    
    // MIDI handling loop
    while(1) {
    #ifdef MIDICTRL
        midi_handler.processMidi();
    #endif
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
