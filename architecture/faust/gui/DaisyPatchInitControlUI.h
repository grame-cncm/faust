#ifndef FAUST_DAISYPATCHINITCONTROL_H
#define FAUST_DAISYPATCHINITCONTROL_H

#include <string>
#include <vector>
#include <memory>
#include <string.h>

#include "daisysp.h"
#include "daisy_seed.h"

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/ValueConverter.h"

/*******************************************************************************
 * DaisyPatchInitControlUI : Faust User Interface
 ******************************************************************************/

class DaisyPatchInitControlUI : public GenericUI
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
   
        // Implements an analog knob by calling Process on the knob instance
        // that has already been created inside DaisyPatchSM
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
    
        std::vector<std::unique_ptr<UpdatableZone>> fItems;
        daisy::patch_sm::DaisyPatchSM* fHw;
    
        std::string fKey, fValue, fScale;
        bool fQuantize = false;
        int fRate, fBoxLevel;
    
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
        
    public:
        
        DaisyPatchInitControlUI(daisy::patch_sm::DaisyPatchSM* hw, int rate)
        :fHw(hw), fScale("lin"),fRate(rate), fBoxLevel(0)
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
                //if (fValue == "1") {
                    //button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                //}
                fItems.push_back(std::move(button));
            }
            fValue = fKey = fScale = "";
        }
    
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fKey == "switch") {
                std::unique_ptr<CheckButton> button = std::make_unique<CheckButton>(zone);
                //if (fValue == "1") {
                    //button->Init(fSeed->GetPin(SW_1_PIN), fRate);
                //}
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
                    InitKnob(daisy::patch_sm::CV_1, zone, min, max, fScale, step, fQuantize);
                } else if (fValue == "2") {
                    InitKnob(daisy::patch_sm::CV_2, zone, min, max, fScale, step, fQuantize);
                } else if (fValue == "3") {
                    InitKnob(daisy::patch_sm::CV_3, zone, min, max, fScale, step, fQuantize);
                } else if (fValue == "4") {
                    InitKnob(daisy::patch_sm::CV_4, zone, min, max, fScale, step, fQuantize);
                }
            }
            fValue = fKey = fScale = "";
        }
    
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "switch") == 0
                || strcmp(key, "knob") == 0) {
                fKey = key;
                fValue = val;
            } else if (std::string(key) == "scale") {
                fScale = val;
            } else if(std::string(key) == "quantize") {
                fQuantize = true;
            }
        }
    
        void update()
        {
            for (const auto& it : fItems) it->update();
        }
    
};

#endif // FAUST_DAISYPATCHINITCONTROL_H
/**************************  END  DaisyPatchInitControlUI.h **************************/
