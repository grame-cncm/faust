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

#ifdef SEED 
#include "daisy_seed.h"
using namespace daisy::seed;
static daisy::DaisySeed hw;
#elif defined PATCHSM
#include "daisy_patch_sm.h"
static daisy::DaisyPatchSM hw;
#endif

#ifdef MIDICTRL
#include<unordered_map>
#endif
#include <functional>
#include <array>

inline static float normalize(float v, float min, float max)
{
    return (v - min) / (max - min);    
}

inline static float snap_to_step(float v, float step) 
{ 
    return std::round(v / step) * step; 
}

inline static float scale_from_norm(float v, float min, float max)
{
    return (max - min) * v  + min; 
}

#ifdef MIDICTRL

struct midi_t
{
    enum type_t 
    {
        keyon, keyoff, key, cc
    };
    type_t type;
    // Channel 0 means all 
    uint8_t index, channel, value;

    midi_t() = default;
    midi_t(type_t t, uint8_t id, uint8_t chan)
        : type(t)
        , index(id)
        , channel(chan)
    {}
};

#endif

struct control 
{
    enum scale_t {
        lin, log, exp
    };
    control::scale_t scale; // To implement in update methods
    const char *label; // Might be useless‘

    control() {}

    virtual void setup();
    virtual void update();
    virtual void set_value_ptr(float *zone);
};

#ifdef SEED
    constexpr static const daisy::Pin DEFAULT_PIN = daisy::seed::A1;
#elif defined PATCHSM 
    constexpr static const daisy::Pin DEFAULT_PIN = daisy::patch_sm::A1;
#endif

struct adc : public control
{
    enum type_t {
        slider, 
        button, 
        checkbox, 
    };

    adc::type_t type;
    float init, min, max, step, previous_state;  // Init might be useless

    daisy::Pin pin;
    uint8_t channel; // index in used ADC list 
    float *value_ptr;

    
    adc(adc::type_t t, float init_, float min_, float max_, float step_, daisy::Pin pin_ = DEFAULT_PIN)
        : type(t)
        , init(init_)
        , min(min_)
        , max(max_)
        , step(step_)
        , previous_state(init_)
        , pin(pin_)
    {}

    /*
        ADC control methods    
    */

    using adc_method = std::function<void(float, float *)>;
    adc_method slider_method = [&](float value, float *fZone)
    {
        *fZone = snap_to_step(scale_from_norm(value, min, max), step);
    };

    /*
        For Buttons and checkboxes 0.05f we need a threshold to eliminate potential DC or noise 
    */
    constexpr static float noise_threshold = 0.05f;
    adc_method button_method = [&](float value, float *fZone)
    {
        *fZone = (value > noise_threshold) ? 1.0f : 0.0f; 
    };
    
    adc_method checkbox_method = [&](float value, float *fZone)
    {
        if(value > noise_threshold && value > previous_state && (value - previous_state) > noise_threshold)
        {
            *fZone = 1.0f - (*fZone);
        }
        previous_state = value;
    };

    adc_method update_method;

    void set_value_ptr(float *zone) override 
    {
        value_ptr = zone;
    }

    void setup() override 
    {
        switch(type)
        {
        case type_t::slider:
            update_method = slider_method;
            break;
        case type_t::button:
            update_method = button_method;
            break;
        case type_t::checkbox:
            update_method = checkbox_method;
            break;
        default:
            break;
        }
    }

    void update() override
    {
        update_method(hw.adc.GetFloat(channel), value_ptr);
    }
};

#ifdef MIDICTRL

// Not really an ADC, but shared logic 
struct midi_input : public adc
{
    midi_t *m;
    midi_input(adc::type_t t, float init_, float min_, float max_, float step_, midi_t *midiptr)
        : adc::adc(t, init_, min_, max_, step_)
        , m(midiptr)
    {}

    void update() override 
    {
        update_method(float(m->value) / 128.0, value_ptr);
    }
};

#endif

struct dac : public control
{
    float min, max; 
    const char *label;

    daisy::DacHandle::Channel channel; // index in used ADC list 
    float *value_ptr;

    dac(daisy::DacHandle::Channel chn, float min_, float max_)
        : min(min_)
        , max(max_)
        , channel(chn)
    {}

    void update() override
    {
        hw.dac.WriteValue(channel, uint16_t(normalize(*value_ptr, min, max) * 4095.0f));
    }
};

// Do not remove following tag, as it is used by python to inline code
/*<UI CONTROL TAG>*/

#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/DaisyControlUI.h"
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#endif

using namespace daisysp;
using namespace std;                    

#ifdef USE_SDRAM
    // Do not remove following tag as it is used by python to inline code
    /*<SDRAM TAG>*/
    #if FAUST_SDRAM_SIZE_BYTES == 0
        #undef USE_SDRAM
    #else 
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

            faustdaisy_dsp_memory_manager() {
                std::fill(faust_sdram_mem, faust_sdram_mem + FAUST_SDRAM_SIZE_BYTES, 0);
                offset = 0;
            }

            void begin(size_t count) {}
            

            void info(const char * name, MemType type, 
                size_t size, size_t size_bytes, size_t reads, size_t writes) {}

            void end() {}
        
            void *allocate(size_t size_bytes) 
            {
                void *ptr = faust_sdram_mem + offset; 
                offset += size_bytes;
                return ptr;
            }

            void destroy(void *ptr) { ptr = nullptr; }

            size_t offset;
        };
    #endif
#endif

#include <string>
#include <type_traits>
#include <utility>


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
#include "faust/dsp/daisy-poly.h"
#endif

static DaisyControlUI control_UI;

#ifdef POLY
    static mydsp_poly<NVOICES> DSP;
#else 
    static mydsp DSP;
#endif

#ifdef USE_SDRAM 
    static faustdaisy_dsp_memory_manager memory_manager; 
#endif

static void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t count)
{
    #ifdef MIDICTRL 
        //midi_handler.processMidi();
    #endif 
    // Update controllers
    control_UI.update_adcs();
    
    // DSP processing
    DSP.compute(count, const_cast<float**>(in), out);

    control_UI.update_dacs();
}

int main(void)
{

    // Initialize Daisy 
    hw.Init();
    hw.SetAudioBlockSize(MY_BUFFER_SIZE);

#ifdef MIDICTRL
    daisy_midi midi_handler;
#endif

    // For debug only
    //hw.StartLog();
    daisy::System::Delay(500);
/*
    Memory Manager Creation 
*/
#ifdef USE_SDRAM 
    mydsp::fManager = &memory_manager;
    mydsp::classInit(MY_SAMPLE_RATE);
#endif
    

/*
    DSP Initialization
*/
#ifdef USE_SDRAM 
    DSP::classInit(MY_SAMPLE_RATE);
    DSP.instanceInit(MY_SAMPLE_RATE);
#else 
    DSP.init(MY_SAMPLE_RATE);
#endif

/*
    Controllers setup 
*/
    DSP.buildUserInterface(&control_UI);
    control_UI.setup_controls();

    hw.adc.Start();
    hw.StartAudio(AudioCallback);

    // MIDI handling loop
    while(1) {
        #ifdef MIDICTRL
            midi_handler.processMidi();
        #endif
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
