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
#include <vector>
#include <memory>
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

class DaisyControlUI : public GenericUI
{
    
    private:
    
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
    
        struct AnalogKnob : daisy::AnalogControl, UpdatableZone {
            
            std::unique_ptr<ValueConverter> fConverter;
            
            AnalogKnob(uint16_t* adcptr, FAUSTFLOAT* zone, std::unique_ptr<ValueConverter>& converter, int rate)
            :UpdatableZone(zone), fConverter(std::move(converter))
            {
                Init(adcptr, rate);
            }
            
            void update()
            {
                *fZone = fConverter->ui2faust(Process());
            }
        };
    
        std::vector<std::unique_ptr<UpdatableZone>> fItems;
        daisy::DaisySeed* fSeed;
    
        std::string fKey, fValue, fScale;
        int fRate, fBoxLevel;
    
        struct KnobContext
        {
            int fKnobId;
            int fAdcId;
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fMin;
            FAUSTFLOAT fMax;
            std::string fScale;
            KnobContext(int kid,
                        int adcid,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min,
                        FAUSTFLOAT max,
                        const std::string& scale)
            :fKnobId(kid), fAdcId(adcid), fZone(zone), fMin(min), fMax(max), fScale(scale)
            {}
        };
        std::vector<KnobContext> fKnobs;
    
        void InitKnob(int knob_pin, int adc_id, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, const std::string& scale)
        {
            // context is kept, to be used in InitKnobs()
            fKnobs.push_back(KnobContext(knob_pin, adc_id, zone, min, max, scale));
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
                std::unique_ptr<ValueConverter> converter;
                if (fKnobs[i].fScale == "log") {
                    converter = std::make_unique<LogValueConverter>(0., 1., fKnobs[i].fMin, fKnobs[i].fMax);
                } else if (fKnobs[i].fScale == "exp") {
                    converter = std::make_unique<ExpValueConverter>(0., 1., fKnobs[i].fMin, fKnobs[i].fMax);
                } else {
                    converter = std::make_unique<LinearValueConverter>(0., 1., fKnobs[i].fMin, fKnobs[i].fMax);
                }
                std::unique_ptr<AnalogKnob> knob = std::make_unique<AnalogKnob>(fSeed->adc.GetPtr(fKnobs[i].fAdcId),
                                                  fKnobs[i].fZone,
                                                  converter,
                                                  fRate);
                fItems.push_back(std::move(knob));
            }
        }
        
    public:
        
        DaisyControlUI(daisy::DaisySeed* seed, int rate)
        :fSeed(seed), fScale("lin"),fRate(rate), fBoxLevel(0)
        {}
    
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
                std::unique_ptr<SwitchButton> button = std::make_unique<SwitchButton>(zone);
                if (fValue == "1") {
                    button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                } else if (fValue == "2") {
                    button->Init(fSeed->GetPin(SW_2_PIN), fRate);
                } else if (fValue == "3") {
                    button->Init(fSeed->GetPin(SW_3_PIN), fRate);
                } else if (fValue == "4") {
                    button->Init(fSeed->GetPin(SW_4_PIN), fRate);
                }
                fItems.push_back(std::move(button));
            }
            fValue = fKey = fScale = "";
        }
    
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "switch") {
                std::unique_ptr<CheckButton> button = std::make_unique<CheckButton>(zone);
                if (fValue == "1") {
                    button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                } else if (fValue == "2") {
                    button->Init(fSeed->GetPin(SW_2_PIN), fRate);
                } else if (fValue == "3") {
                    button->Init(fSeed->GetPin(SW_3_PIN), fRate);
                } else if (fValue == "4") {
                    button->Init(fSeed->GetPin(SW_4_PIN), fRate);
                }
                fItems.push_back(std::move(button));
            }
            fValue = fKey = fScale = "";
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
                    InitKnob(KNOB_1_PIN, 0, zone, min, max, fScale);
                } else if (fValue == "2") {
                    InitKnob(KNOB_2_PIN, 1, zone, min, max, fScale);
                } else if (fValue == "3") {
                    InitKnob(KNOB_3_PIN, 2, zone, min, max, fScale);
                } else if (fValue == "4") {
                    InitKnob(KNOB_4_PIN, 3, zone, min, max, fScale);
                } else if (fValue == "5") {
                    InitKnob(KNOB_5_PIN, 4, zone, min, max, fScale);
                } else if (fValue == "6") {
                    InitKnob(KNOB_6_PIN, 5, zone, min, max, fScale);
                }
            }
            fValue = fKey = fScale = "";
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "switch") == 0
                || strcmp(key, "knob") == 0
                || strcmp(key, "encoder") == 0) {
                fKey = key;
                fValue = val;
            } else if (std::string(key) == "scale") {
                fScale = val;
            }
        }
    
        void update()
        {
            for (const auto& it : fItems) it->update();
        }
    
};

#endif // FAUST_DAISYCONTROL_H
/**************************  END  DaisyControlUI.h **************************/
