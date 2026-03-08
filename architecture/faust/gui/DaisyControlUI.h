/************************** BEGIN DaisyControlUI.h **********************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*************************************************************************/

#ifndef FAUST_DAISYCONTROL_H
#define FAUST_DAISYCONTROL_H

#include <string>
#include <array>
#include <memory>
#include <string.h>

#include "faust/gui/DecoratorUI.h"
//#include "faust/gui/ValueConverter.h"

/*******************************************************************************
 * DaisyControlUI : Faust User Interface
 ******************************************************************************/

#if defined POD
/*
Note from DBraun: This section has been tested for Pod Rev5.
If it doesn't work correctly on earlier versions, sorry! Please make a PR and
we'll add a flag to faust2daisy for the Pod version.
*/
// https://github.com/electro-smith/libDaisy/blob/bd13385c823b6777d7f3c0a90c488a345409175c/src/daisy_pod.cpp#L10-L27
#define SW_1_PIN 27
#define SW_2_PIN 28
// not used:
#define SW_3_PIN 1 // spdt switches
#define SW_4_PIN 2 // spdt switches

// We swap these two knobs in Faust (maybe the Daisy source is wrong.)
#define KNOB_1_PIN 15
#define KNOB_2_PIN 21
// not used, but copied from legacy code anyway:
#define KNOB_3_PIN 21
#define KNOB_4_PIN 18
#define KNOB_5_PIN 19
#define KNOB_6_PIN 17
#else
/*
Note from DBraun: This section is legacy code for people using the Seed, 
not the Pod or patch.Init(). It hasn't been tested recently.
I have only recently tested that the above POD section is correct for
Pod Rev5.
*/

// Compatible with Seed Rev3 and Rev4
/*
#define SW_1_PIN 28
#define SW_2_PIN 27
*/

// Seems to be inverted (compared to daisy_pod.cpp)
#define SW_1_PIN 5 // buttons
#define SW_2_PIN 6 // buttons

#define SW_3_PIN 1 // spdt switches
#define SW_4_PIN 2 // spdt switches

#define KNOB_1_PIN 15 // 1
#define KNOB_2_PIN 16 // 2

#define KNOB_3_PIN 21
#define KNOB_4_PIN 18

#define KNOB_5_PIN 19
#define KNOB_6_PIN 17

#endif

#include "per/adc.h"
#include "per/dac.h"

#ifdef SEED
    using namespace daisy::seed;
    constexpr size_t ADC_COUNT = 12;
    constexpr daisy::Pin ADC[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
    constexpr size_t DAC_COUNT = 2;
    constexpr daisy::Pin DAC[] = {A7, A8};
#elif defined PATCHSM

#endif


class DaisyControlUI : public GenericUI
{
    
    private:
        size_t control_counter = 0;
        size_t dac_counter = 0; 
    
        #if defined PATCHSM
        bool fQuantize = false;
        #elif defined SEED
        #endif
    
        std::string fKey, fValue, fScale;
        int fRate, fBoxLevel;

        #if defined PATCHSM
    
        void InitKnob(int knob_pin, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, const std::string& scale, FAUSTFLOAT step, bool quantize)
        {
        }
    
        void InitKnobs()
        {
        }
        #else
        
        void InitKnob(int knob_pin, int adc_id, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, const std::string& scale)
        {
        }
    
        void InitKnobs()
        {
        }
        #endif
        
    public:
        
        // -- widget's layouts
        void openTabBox(const char* label) {  }
        void openHorizontalBox(const char* label) {  }
        void openVerticalBox(const char* label) {  }
        void closeBox(){}
    
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addADCEntry(label, zone);
        }
    
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addADCEntry(label, zone);
        }
            // Base class for updatable items
        struct UpdatableZone {
            FAUSTFLOAT* fZone;
            
            UpdatableZone(FAUSTFLOAT* zone) : fZone(zone) {}
            virtual ~UpdatableZone() {}
            
            virtual void update() = 0;
        };
    
        struct SwitchButton : daisy::Switch, UpdatableZone {
            
            SwitchButton(FAUSTFLOAT* zone):UpdatableZone(zone)
            {}
            
            void update()
            {
                *fZone = RawState();
            }
        };
    
        // Implement checkbox using daisy::Switch
        struct CheckButton : daisy::Switch, UpdatableZone {
            
            FAUSTFLOAT fLastButton;
            
            CheckButton(FAUSTFLOAT* zone):UpdatableZone(zone), fLastButton(0)
            {}
            
            void update()
            {
                FAUSTFLOAT button = RawState();
                if (button == 1.0 && (button != fLastButton)) {
                    *fZone = !*fZone;
                }
                fLastButton = button;
            }
        };
    
        #if defined PATCHSM
        #elif defined SEED
        #endif

        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addADCEntry(label, zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addADCEntry(label, zone);
        }

        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addADCEntry(label, zone);
        }
    
        void addADCEntry(const char *label, FAUSTFLOAT *zone)
        {
            //assert( strcmp(label, adc_list[build_ui_counter].label) == 0 );
            input_list[control_counter]->set_value_ptr(zone);
            input_list[control_counter]->setup();
            control_counter++;
        }

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { 
            addDACEntry(label, zone);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addDACEntry(label, zone);
        }


        void addDACEntry(const char *label, FAUSTFLOAT *zone)
        {
            output_list[dac_counter]->set_value_ptr( zone );
            dac_counter = (dac_counter + 1) % output_list.size();
        }

        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
        }
    
        void update_adcs()
        {
            for(auto & it : input_list) 
            {
                it->update();
            }
        }

        void update_dacs()
        {
            for(auto & it : output_list) 
                it->update();
        }

        void setup_controls()
        {
            #ifdef SEED
            for(size_t i = 0; i < adc_list.size(); ++i)
            {
                adc_config_list[i].InitSingle(adc_list[i].pin);
                adc_list[i].channel = i;
            }

            hw.adc.Init(adc_config_list.data(), adc_config_list.size());

            if(dacs_used)
            {
                daisy::DacHandle::Config cfg; 
                cfg.chn = dac_chnls;
                cfg.mode = daisy::DacHandle::Mode::POLLING;
                cfg.bitdepth = daisy::DacHandle::BitDepth::BITS_12;
                cfg.buff_state = daisy::DacHandle::BufferState::ENABLED; 
                hw.dac.Init(cfg); 
            }

            #elif defined PATCHSM
            #endif
        }
};

#endif // FAUST_DAISYCONTROL_H
/**************************  END  DaisyControlUI.h **************************/
