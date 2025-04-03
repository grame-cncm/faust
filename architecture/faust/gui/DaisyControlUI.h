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
    
        #if defined PATCHSM
        struct AnalogKnob : UpdatableZone {
           
            std::unique_ptr<ValueConverter> fConverter;
            daisy::AnalogControl* fControl;

            FAUSTFLOAT fStep;
            bool fQuantizeToStep;
            
            AnalogKnob(daisy::AnalogControl* control, FAUSTFLOAT* zone, std::unique_ptr<ValueConverter>& converter, int rate, FAUSTFLOAT step, bool quantize)
            : UpdatableZone(zone), fConverter(std::move(converter)), fControl(control), fStep(step), fQuantizeToStep(quantize)
            {
            }
            
            void update()
            {
                FAUSTFLOAT newValue = fConverter->ui2faust(fControl->Process());
                if (fQuantizeToStep) {
                    *fZone = round(newValue / fStep) * fStep;
                } else {
                    *fZone = newValue;
                }
            }
        };
        #else
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
        #endif

        std::vector<std::unique_ptr<UpdatableZone>> fItems;
        #if defined PATCHSM
        daisy::patch_sm::DaisyPatchSM* fHw;
        bool fQuantize = false;
        #else
        daisy::DaisySeed* fSeed;
        #endif
    
        std::string fKey, fValue, fScale;
        int fRate, fBoxLevel;

        #if defined PATCHSM
        struct KnobContext
        {
            int fKnobId;
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fMin;
            FAUSTFLOAT fMax;
            std::string fScale;
            FAUSTFLOAT fStep;
            bool fQuantizeToStep;
            KnobContext(int kid,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min,
                        FAUSTFLOAT max,
                        const std::string& scale,
                        FAUSTFLOAT step,
                        bool quantize)
            :fKnobId(kid), fZone(zone), fMin(min), fMax(max), fScale(scale), fStep(step), fQuantizeToStep(quantize)
            {}
        };
        std::vector<KnobContext> fKnobs;
    
        void InitKnob(int knob_pin, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, const std::string& scale, FAUSTFLOAT step, bool quantize)
        {
            // context is kept, to be used in InitKnobs()
            fKnobs.push_back(KnobContext(knob_pin, zone, min, max, scale, step, quantize));
        }
    
        void InitKnobs()
        {
            for (size_t i = 0; i < fKnobs.size(); i++) {
                std::unique_ptr<ValueConverter> converter;
                if (fKnobs[i].fScale == "log") {
                    converter = std::make_unique<LogValueConverter>(0., 1., fKnobs[i].fMin, fKnobs[i].fMax);
                } else if (fKnobs[i].fScale == "exp") {
                    converter = std::make_unique<ExpValueConverter>(0., 1., fKnobs[i].fMin, fKnobs[i].fMax);
                } else {
                    converter = std::make_unique<LinearValueConverter>(0., 1., fKnobs[i].fMin, fKnobs[i].fMax);
                }
                std::unique_ptr<AnalogKnob> knob = std::make_unique<AnalogKnob>(&fHw->controls[fKnobs[i].fKnobId],
                                                  fKnobs[i].fZone,
                                                  converter,
                                                  fRate,
                                                  fKnobs[i].fStep,
                                                  fKnobs[i].fQuantizeToStep);
                fItems.push_back(std::move(knob));
            }
        }
        #else
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
        #endif
        
    public:
        
        #if defined PATCHSM
        DaisyControlUI(daisy::patch_sm::DaisyPatchSM* hw, int rate)
        :fHw(hw), fScale("lin"), fRate(rate), fBoxLevel(0)
        {}
        #else
        DaisyControlUI(daisy::DaisySeed* seed, int rate)
        :fSeed(seed), fScale("lin"), fRate(rate), fBoxLevel(0)
        {}
        #endif
    
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
                #if defined PATCHSM
                std::unique_ptr<CheckButton> button = std::make_unique<CheckButton>(zone);
                //if (fValue == "1") {
                    //button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                //}
                #else
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
                #endif
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
                #if defined PATCHSM
                if (fValue == "1") {
                    InitKnob(daisy::patch_sm::CV_1, zone, min, max, fScale, step, fQuantize);
                } else if (fValue == "2") {
                    InitKnob(daisy::patch_sm::CV_2, zone, min, max, fScale, step, fQuantize);
                } else if (fValue == "3") {
                    InitKnob(daisy::patch_sm::CV_3, zone, min, max, fScale, step, fQuantize);
                } else if (fValue == "4") {
                    InitKnob(daisy::patch_sm::CV_4, zone, min, max, fScale, step, fQuantize);
                }
                #else
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
                #endif
            }
            fValue = fKey = fScale = "";
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            #if defined PATCHSM
            if (strcmp(key, "switch") == 0
                || strcmp(key, "knob") == 0) {
                fKey = key;
                fValue = val;
            } else if (strcmp(key, "scale") == 0) {
                fScale = val;
            } else if(strcmp(key, "quantize") == 0) {
                fQuantize = true;
            }
            #else
            if (strcmp(key, "switch") == 0
                || strcmp(key, "knob") == 0
                || strcmp(key, "encoder") == 0) {
                fKey = key;
                fValue = val;
            } else if (strcmp(key, "scale") == 0) {
                fScale = val;
            }
            #endif
        }
    
        void update()
        {
            for (const auto& it : fItems) it->update();
        }
    
};

#endif // FAUST_DAISYCONTROL_H
/**************************  END  DaisyControlUI.h **************************/
