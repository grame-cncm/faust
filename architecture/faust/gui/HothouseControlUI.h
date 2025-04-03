/************************** BEGIN HothouseControlUI.h **********************
FAUST Architecture File
Copyright (C) 2003-2024 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_HOTHOUSECONTROL_H
#define FAUST_HOTHOUSECONTROL_H

#include <string>
#include <vector>
#include <memory>
#include <string.h>

#include "daisysp.h"
#include "hothouse.h"

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/SimpleParser.h"
#include "faust/gui/ValueConverter.h"

using clevelandmusicco::Hothouse;

class DiscreteValueConverter : public ValueConverter {
    private:
        double fLow;
        double fMid;
        double fHigh;
        
    public:
        DiscreteValueConverter(double valA, double valB, double valC) 
            : fLow(valA), fMid(valB), fHigh(valC) {}
            
        virtual double ui2faust(double x) {
            if (x == 0) return fLow;
            if (x == 1) return fMid;
            if (x == 2) return fHigh;
            return 0;
        }
        
        virtual double faust2ui(double x) {
            if (x == fLow) return 0;
            if (x == fMid) return 1;
            if (x == fHigh) return 2;
            return 0;
        }
};

/*******************************************************************************
 * HothouseControlUI : Faust User Interface
 ******************************************************************************/

class HothouseControlUI : public GenericUI
{
    
    private:
    
        // Base class for updatable items
        struct UpdatableZone {
            FAUSTFLOAT* fZone;
            
            UpdatableZone(FAUSTFLOAT* zone) : fZone(zone) {}
            virtual ~UpdatableZone() = default;
            
            virtual void update() = 0;
        };
    
        struct FootSwitchButtonZone : UpdatableZone {
            private:
                daisy::Switch* daisySwitch;
            
            public:
                FootSwitchButtonZone(FAUSTFLOAT* zone, daisy::Switch* s)
                : UpdatableZone(zone),
                daisySwitch(s)
                {}
                
                void update() override {
                    *fZone = daisySwitch->RawState();
                }
        };
    
        struct CheckboxZone : UpdatableZone {
            private:
                daisy::Switch* daisySwitch;
                FAUSTFLOAT fLastButton;
            
            public:
                CheckboxZone(FAUSTFLOAT* zone, daisy::Switch* s)
                : UpdatableZone(zone),
                daisySwitch(s),
                fLastButton(0)
                {}
            
                void update()
                {
                    FAUSTFLOAT button = daisySwitch->RawState();
                    if (button == 1.0 && (button != fLastButton)) {
                        *fZone = !*fZone;
                    }
                    fLastButton = button;
                }
        };
    
        struct KnobZone : UpdatableZone {
            private:
                daisy::AnalogControl* daisyKnob;
                std::unique_ptr<ValueConverter> fConverter;
            
            public:
                KnobZone(FAUSTFLOAT* zone, std::unique_ptr<ValueConverter>& converter, daisy::AnalogControl* knob)
                : UpdatableZone(zone),
                daisyKnob(knob),
                fConverter(std::move(converter))
                {}
                
                void update()
                {
                    *fZone = fConverter->ui2faust(daisyKnob->Value());
                }
        };

        struct ToggleSwitchZone : UpdatableZone {
            private:
                Hothouse* hothouse;
                std::unique_ptr<ValueConverter> fConverter;
                Hothouse::Toggleswitch switchIndex;
            
            public:
                ToggleSwitchZone(Hothouse* hw, FAUSTFLOAT* zone, std::unique_ptr<ValueConverter>& converter, Hothouse::Toggleswitch tsw)
                : UpdatableZone(zone),
                hothouse(hw),
                fConverter(std::move(converter)),
                switchIndex(tsw)
                {}
            
                void update()
                {
                    Hothouse::ToggleswitchPosition pos = hothouse->GetToggleswitchPosition(switchIndex);
                    if (pos == Hothouse::ToggleswitchPosition::TOGGLESWITCH_UP) {
                        *fZone = fConverter->ui2faust(2.0);
                    } else if (pos == Hothouse::ToggleswitchPosition::TOGGLESWITCH_MIDDLE) {
                        *fZone = fConverter->ui2faust(1.0);
                    } else /*if (pos == Hothouse::ToggleswitchPosition::TOGGLESWITCH_DOWN)*/ {
                        *fZone = fConverter->ui2faust(0.0);
                    }
                }
        };
    
        std::vector<std::unique_ptr<UpdatableZone>> fItems;
        Hothouse* fHothouse;
    
        std::string fKey, fValue, fScale;
        double toggleLow, toggleMid, toggleHigh;
        bool togglesAreSet = false;
        
        void InitKnob(Hothouse::Knob k, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, const std::string& scale)
        {
            std::unique_ptr<ValueConverter> converter;
            if (scale == "log") {
                converter = std::make_unique<LogValueConverter>(0., 1., min, max);
            } else if (scale == "exp") {
                converter = std::make_unique<ExpValueConverter>(0., 1., min, max);
            } else {
                converter = std::make_unique<LinearValueConverter>(0., 1., min, max);
            }
            fItems.push_back(std::make_unique<KnobZone>(zone, converter, &fHothouse->knobs[k]));
        }

        void InitToggleSwitch(Hothouse::Toggleswitch tsw, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            if (!togglesAreSet) {
                toggleLow = (double)min;
                toggleHigh = (double)max;
                toggleMid = 0.5*(toggleLow+toggleHigh);
            }
            std::unique_ptr<ValueConverter> converter = std::make_unique<DiscreteValueConverter>(toggleLow, toggleMid, toggleHigh);
            fItems.push_back(std::make_unique<ToggleSwitchZone>(fHothouse, zone, converter, tsw));
        }
        
    public:
        
        HothouseControlUI(Hothouse* hothouse)
        :fHothouse(hothouse), fScale("lin")
        {}
    
        // -- widget's layouts
        void openTabBox(const char* label) {}
        void openHorizontalBox(const char* label) {}
        void openVerticalBox(const char* label) {}
        void closeBox() {}
    
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "foot") {
                if (fValue == "1") {
                    fItems.push_back(std::make_unique<FootSwitchButtonZone>(zone, &fHothouse->switches[Hothouse::Switches::FOOTSWITCH_1]));
                } else if (fValue == "2") {
                    fItems.push_back(std::make_unique<FootSwitchButtonZone>(zone, &fHothouse->switches[Hothouse::Switches::FOOTSWITCH_2]));
                }
            }
            fValue = fKey = fScale = "";
        }
    
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "foot") {
                if (fValue == "1") {
                    fItems.push_back(std::make_unique<CheckboxZone>(zone, &fHothouse->switches[Hothouse::Switches::FOOTSWITCH_1]));
                } else if (fValue == "2") {
                    fItems.push_back(std::make_unique<CheckboxZone>(zone, &fHothouse->switches[Hothouse::Switches::FOOTSWITCH_2]));
                }
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
                    InitKnob(Hothouse::Knob::KNOB_1, zone, min, max, fScale);
                } else if (fValue == "2") {
                    InitKnob(Hothouse::Knob::KNOB_2, zone, min, max, fScale);
                } else if (fValue == "3") {
                    InitKnob(Hothouse::Knob::KNOB_3, zone, min, max, fScale);
                } else if (fValue == "4") {
                    InitKnob(Hothouse::Knob::KNOB_4, zone, min, max, fScale);
                } else if (fValue == "5") {
                    InitKnob(Hothouse::Knob::KNOB_5, zone, min, max, fScale);
                } else if (fValue == "6") {
                    InitKnob(Hothouse::Knob::KNOB_6, zone, min, max, fScale);
                }
            }
            else if (fKey == "toggle") {
                if (fValue == "1") {
                    InitToggleSwitch(Hothouse::Toggleswitch::TOGGLESWITCH_1, zone, min, max);
                } else if (fValue == "2") {
                    InitToggleSwitch(Hothouse::Toggleswitch::TOGGLESWITCH_2, zone, min, max);
                } else if (fValue == "3") {
                    InitToggleSwitch(Hothouse::Toggleswitch::TOGGLESWITCH_3, zone, min, max);
                }
            }
            fValue = fKey = fScale = "";
            togglesAreSet = false;
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            std::string keyString = std::string(key);
            if (keyString == "knob") {
                fKey = key;
                fValue = val;
            } else if (keyString == "toggle") {
                fKey = key;
                fValue = val;
            } else if (keyString == "foot") {
                fKey = key;
                fValue = val;
            } else if (keyString == "scale") {
                fScale = val;
            } else if (keyString == "style") {
                std::vector<std::string> names;
                std::vector<double> values;
                parseMenuList(val, names, values);
                if (values.size() > 2) {
                    toggleLow = values.at(0);
                    toggleMid = values.at(1);
                    toggleHigh = values.at(2);
                    togglesAreSet = true;
                }
            }
        }
    
        void update()
        {
            for (const auto& it : fItems) it->update();
        }
    
};

#endif // FAUST_HOTHOUSECONTROL_H
/**************************  END  HothouseControlUI.h **************************/
