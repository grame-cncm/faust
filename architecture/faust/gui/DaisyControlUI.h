/************************** BEGIN Esp32ControlUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_DAISYCONTROL_H
#define FAUST_DAISYCONTROL_H

#include <string>
#include <vector>
#include <string.h>

#include "daisysp.h"
#include "daisy_seed.h"

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/ValueConverter.h"

/*******************************************************************************
 * DaisyControlUI : Faust User Interface
 ******************************************************************************/

// Compatible with Seed Rev3 and Rev4
/*
#define SW_1_PIN 28
#define SW_2_PIN 27
*/

// Seems to be inverted (compared to daisy_pod.cpp)
#define SW_1_PIN 27
#define SW_2_PIN 28

#define KNOB_1_PIN 21
#define KNOB_2_PIN 15

class DaisyControlUI : public GenericUI
{
    
    private:
    
        struct SwitchButton : daisy::Switch {
            
            FAUSTFLOAT* fZone;
            
            SwitchButton(FAUSTFLOAT* zone):fZone(zone)
            {}
            
            void update()
            {
                *fZone = RawState();
            }
        };
    
        struct CheckButton : daisy::Switch {
            
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fLastButton;
            
            CheckButton(FAUSTFLOAT* zone):fZone(zone), fLastButton(0)
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
    
        struct AnalogKnob  {
            
            uint16_t* fADCPtr;
            FAUSTFLOAT* fZone;
            ValueConverter* fValueConverter;
            
            AnalogKnob(uint16_t* adcptr, FAUSTFLOAT* zone, ValueConverter* converter, int rate)
            :fADCPtr(adcptr), fZone(zone), fValueConverter(converter)
            {}
            
            void update()
            {
                *fZone = fValueConverter->ui2faust(*fADCPtr);
            }
        };
    
        /*
        struct AnalogKnob : daisy::AnalogControl {
            
            FAUSTFLOAT* fZone;
            ValueConverter* fValueConverter;
            
            AnalogKnob(uint16_t* adcptr, FAUSTFLOAT* zone, ValueConverter* converter, int rate)
            :fZone(zone), fValueConverter(converter)
            {
                Init(adcptr, rate);
            }
            
            void update()
            {
                *fZone = fValueConverter->ui2faust(Process());
            }
        };
        */
    
        std::vector<SwitchButton*> fSwitchButton;
        std::vector<CheckButton*> fCheckButton;
        std::vector<AnalogKnob*> fKnobConverter;
    
        daisy::DaisySeed* fSeed;
    
        std::string fKey, fValue;
        int fRate;
        int fBoxLevel;
    
        struct KnobContext {
            int fKnobId;
            int fAdcId;
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fMin;
            FAUSTFLOAT fMax;
            KnobContext(int kid, int adcid, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            :fKnobId(kid), fAdcId(adcid), fZone(zone), fMin(min), fMax(max)
            {}
        };
        std::vector<KnobContext> fKnobs;
    
        void InitKnob(int knob_pin, int adc_id, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            // context is kept, to be used in InitKnobs()
            fKnobs.push_back(KnobContext(knob_pin, adc_id, zone, min, max));
        }
    
        void InitKnobs()
        {
            // initialize all knobs in a single step
            daisy::AdcChannelConfig knobs_init[fKnobs.size()];
            for (size_t i = 0; i < fKnobs.size(); i++) {
                knobs_init[i].InitSingle(fSeed->GetPin(fKnobs[i].fKnobId));
            }
            fSeed->adc.Init(knobs_init, fKnobs.size());
            
            for (size_t i = 0; i < fKnobs.size(); i++) {
                AnalogKnob* knob = new AnalogKnob(fSeed->adc.GetPtr(fKnobs[i].fAdcId),
                                                  fKnobs[i].fZone,
                                                  new LinearValueConverter(0., 1., fKnobs[i].fMin, fKnobs[i].fMax), fRate);
                fKnobConverter.push_back(knob);
            }
        }
        
    public:
        
        DaisyControlUI(daisy::DaisySeed* seed, int rate)
        :fSeed(seed), fRate(rate), fBoxLevel(0)
        {}
    
        virtual ~DaisyControlUI()
        {
            for (auto& it : fSwitchButton) delete it;
            for (auto& it : fCheckButton) delete it;
            for (auto& it : fKnobConverter) delete it;
        }
    
        // -- widget's layouts
        void openTabBox(const char* label) { fBoxLevel++; }
        void openHorizontalBox(const char* label) { fBoxLevel++; }
        void openVerticalBox(const char* label) { fBoxLevel++; }
        void closeBox()
        {
            if (--fBoxLevel == 0) InitKnobs();
        }
    
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "switch") {
                //std::cout << "addButton " << std::endl;
                SwitchButton* button = new SwitchButton(zone);
                fSwitchButton.push_back(button);
                if (fValue == "1") {
                    button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                } else if (fValue == "2") {
                    button->Init(fSeed->GetPin(SW_2_PIN), fRate);
                }
            }
            fValue = fKey = "";
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "switch") {
                //std::cout << "addCheckButton " << std::endl;
                CheckButton* button = new CheckButton(zone);
                fCheckButton.push_back(button);
                if (fValue == "1") {
                    button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                } else if (fValue == "2") {
                    button->Init(fSeed->GetPin(SW_2_PIN), fRate);
                }
            }
            fValue = fKey = "";
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addNumEntry(label, zone, init, min, max, step);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addNumEntry(label, zone, init, min, max, step);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            if (fKey == "knob") {
                if (fValue == "1") {
                    //std::cout << "knob1 " << min << " " << max << std::endl;
                    InitKnob(KNOB_1_PIN, 0, zone, min, max);
                } else if (fValue == "2") {
                    //std::cout << "knob2 " << min << " " << max << std::endl;
                    InitKnob(KNOB_2_PIN, 1, zone, min, max);
                }
            }
            fValue = fKey = "";
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "switch") == 0
                || strcmp(key, "knob") == 0
                || strcmp(key, "encoder") == 0) {
                //std::cout << "key " << key << " val " << val << std::endl;
                fKey = key;
                fValue = val;
            }
        }
    
        void update()
        {
            for (auto& it : fSwitchButton) it->update();
            for (auto& it : fCheckButton) it->update();
            for (auto& it : fKnobConverter) it->update();
        }
    
};

#endif // FAUST_DAISYCONTROL_H
/**************************  END  DaisyControlUI.h **************************/
