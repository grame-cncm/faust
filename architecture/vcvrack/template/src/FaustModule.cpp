/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

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
 
 ************************************************************************
 ************************************************************************/

// #include "faust/dsp/dsp.h"
// dsp.h file is included and dsp file is renamed to rack_dsp to avoid namespace conflicts. Then 'faust -scn rack_dsp' is used in faust2vcvrack.

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <assert.h>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

using namespace std;

struct UI;
struct Meta;

/**
 * Signal processor definition.
 */

class rack_dsp {
    
    public:
    
        rack_dsp() {}
        virtual ~rack_dsp() {}
    
        virtual int getNumInputs() = 0;
        virtual int getNumOutputs() = 0;
        virtual void buildUserInterface(UI* ui_interface) = 0;
        virtual int getSampleRate() = 0;
        virtual void init(int sample_rate) = 0;
        virtual void instanceInit(int sample_rate) = 0;
        virtual void instanceConstants(int sample_rate) = 0;
        virtual void instanceResetUserInterface() = 0;
        virtual void instanceClear() = 0;
        virtual rack_dsp* clone() = 0;
        virtual void metadata(Meta* m) = 0;
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
    
};

struct one_sample_dsp : public rack_dsp {
    
    int* iZone;
    FAUSTFLOAT* fZone;
    
    one_sample_dsp():iZone(nullptr), fZone(nullptr)
    {}
    
    virtual ~one_sample_dsp()
    {
        delete [] iZone;
        delete [] fZone;
    }
    
    void initControl()
    {
        iZone = new int[getNumIntControls()];
        fZone = new FAUSTFLOAT[getNumRealControls()];
    }
    
    virtual int getNumIntControls() = 0;
    virtual int getNumRealControls() = 0;
    
    virtual void control(int* iControl, FAUSTFLOAT* fControl) = 0;
    
    virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, FAUSTFLOAT* fControl) = 0;
    
    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {}
    
    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/ValueConverter.h"
#include "faust/misc.h"
#include "plugin.hpp"

// params  = [buttons][entries][bargraph]

/*
 - notion of minimal size for leaves items
 
 ==> compute the global minimal width/height pour the entire UI
 
 - on peut calculer la taille minimale width/height de la section audio inputs et audio outputs
 
 1) calculer somme taille minimale width/height des section audio inputs et audio outputs tous en ligne
 2) en deduire la taille width/height pour l'UI globale
 3) eventuellement ajuster les groupages audio inputs et audio outputs (passer de 1 à 2 ligne), recalculer la taille width/height pour l'UI globale
 
 */

// UI handler for switches, knobs and lights
struct RackUI : public GenericUI
{
    // A internal class to count items of each type
    struct ManagerUI : public GenericUI
    {
        enum UIType {
            kButton,
            kCheckbox,
            kVSlider,
            kHSlider,
            kNumEntry,
            kVBargraph,
            kHBargraph,
            kNotype
        };
        
        struct UIItem {
            std::string fLabel;
            float fWidth = 0.f;
            float fHight = 0.f;
            UIType fType = kNotype;
            FAUSTFLOAT fInit;
            FAUSTFLOAT fMin;
            FAUSTFLOAT fMax;
            UIItem(const std::string& label,
                   FAUSTFLOAT init,
                   FAUSTFLOAT fmin,
                   FAUSTFLOAT fmax,
                   UIType type)
                :fLabel(label), fType(type), fInit(init), fMin(fmin), fMax(fmax)
            {}
        };
        
        std::vector<UIItem> fButtons;
        std::vector<UIItem> fRanges;
        std::vector<UIItem> fOutputs;
        
        void openTabBox(const char* label) {}
        void openHorizontalBox(const char* label) {}
        void openVerticalBox(const char* label) {}
        void closeBox() {}
        
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fButtons.push_back(UIItem(label, 0, 1, 0, kButton));
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fButtons.push_back(UIItem(label, 0, 1, 0, kCheckbox));
        }
        
        void addVerticalSlider(const char* label,
                               FAUSTFLOAT* zone,
                               FAUSTFLOAT init,
                               FAUSTFLOAT min,
                               FAUSTFLOAT max,
                               FAUSTFLOAT step)
        {
            fRanges.push_back(UIItem(label, init, min, max, kVSlider));
        }
        void addHorizontalSlider(const char* label,
                                 FAUSTFLOAT* zone,
                                 FAUSTFLOAT init,
                                 FAUSTFLOAT min,
                                 FAUSTFLOAT max,
                                 FAUSTFLOAT step)
        {
            fRanges.push_back(UIItem(label, init, min, max, kHSlider));
        }
        void addNumEntry(const char* label,
                         FAUSTFLOAT* zone,
                         FAUSTFLOAT init,
                         FAUSTFLOAT min,
                         FAUSTFLOAT max,
                         FAUSTFLOAT step)
        {
            fRanges.push_back(UIItem(label, init, min, max, kNumEntry));
        }
        
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fOutputs.push_back(UIItem(label, 0, min, max, kHBargraph));
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fOutputs.push_back(UIItem(label, 0, min, max, kVBargraph));
        }
    };
    
    typedef function<void(std::vector<Param>& params)> updateFunction;
    
    std::vector<ConverterZoneControl*> fConverters;
    std::vector<updateFunction> fUpdateFunIn;
    std::vector<updateFunction> fUpdateFunOut;
    
    RackUI::ManagerUI fParams;
    std::string fScale;
    
    int fButtonsCounter = 0;
    int fParamsCounter = 0;
    
    RackUI(const RackUI::ManagerUI& counter):fParams(counter), fScale("lin")
    {}
    
    virtual ~RackUI()
    {
        for (auto& it : fConverters) delete it;
    }
    
    void reset()
    {
        fButtonsCounter = 0;
        fParamsCounter = 0;
        fScale = "lin";
    }
    
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        // Takes the value at lambda contruction time
        int index = fButtonsCounter;
        fUpdateFunIn.push_back([=] (std::vector<Param>& params)
                               {
                                   // 'buttons' start at 0
                                   *zone = params[index].getValue();
                                });
        fButtonsCounter++;
    }
    
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        addButton(label, zone);
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
        ConverterZoneControl* converter;
        if (fScale == "log") {
            converter = new ConverterZoneControl(zone, new LogValueConverter(min, max, min, max));
        } else if (fScale == "exp") {
            converter = new ConverterZoneControl(zone, new ExpValueConverter(min, max, min, max));
        } else {
            converter = new ConverterZoneControl(zone, new ValueConverter());
        }
        
        // Takes the value at lambda contruction time
        int index = fParamsCounter;
        fUpdateFunIn.push_back([=] (std::vector<Param>& params)
                               {
                                   // 'nentries' start at fParams.fButtons.size()
                                   converter->update(params[index + fParams.fButtons.size()].getValue());
                               });
        fConverters.push_back(converter);
        fScale = "lin";
        fParamsCounter++;
    }
    
    void addBarGraph(FAUSTFLOAT* zone)
    {
        /*
        // index start at 0
        int index = getIndex(fValue) - 1;
        if ((fKey == "light_red") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params)
                                    {
                                        // 'nentries' start at fParams.fButton + fParams.fNumEntry
                                        params[index + fParams.fButton + fParams.fNumEntry][0].setValue(*zone);
                                    });
        } else if ((fKey == "light_green") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params) { lights[index-1][1] = *zone; });
        } else if ((fKey == "light_blue") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params) { lights[index-1][2] = *zone; });
        } else if ((fKey == "switchlight_red") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params) { switchLights[index-1][0] = *zone; });
        } else if ((fKey == "switchlight_green") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params) { switchLights[index-1][1] = *zone; });
        } else if ((fKey == "switchlight_blue") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params) { switchLights[index-1][2] = *zone; });
        }
        */
    }
    
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addBarGraph(zone);
    }
    
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addBarGraph(zone);
    }
    
    void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        if (std::string(key) == "scale") {
            fScale = val;
        }
    }
    
    void updateInputs(std::vector<Param>& params)
    {
        for (auto& it : fUpdateFunIn) it(params);
    }
    
    void updateOutputs(std::vector<Param>& params)
    {
        for (auto& it : fUpdateFunOut) it(params);
    }
};

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

#define CONTROL_RATE_HZ  100
#define DEFAULT_SR       44100

template <int VOICES>
struct mydspModule : Module {
    
    RackUI* fRackUI;    // One single version for all VOICES
    mydsp fDSP[VOICES];
    int fControlCounter;
    
    mydspModule()
    {
        // Count items of button, nentry, bargraph categories
        RackUI::ManagerUI params;
        fDSP[0].buildUserInterface(&params);
        
        // Controllers are connected to all VOICES
        fRackUI = new RackUI(params);
        for (int v = 0; v < VOICES; v++) {
            fDSP[v].buildUserInterface(fRackUI);
            fRackUI->reset();
        }
        
        uint buttons = params.fButtons.size();
        uint entries = params.fRanges.size();
        
        // Config: by default we allocate complete set of parameters, even if all off them are not 'connected' using metadata
        config(buttons + entries, fDSP[0].getNumInputs(), fDSP[0].getNumOutputs(), params.fOutputs.size());
        
        // Setup buttons
        for (uint pa = 0; pa < buttons; pa++) {
            configParam(pa, 0.f, 1.f, 0.f, "");
        }
        // Setup range params min/max/init values
        for (uint pa = 0; pa < entries; pa++) {
            configParam(pa + buttons, params.fRanges[pa].fMin, params.fRanges[pa].fMax, params.fRanges[pa].fInit, "");
        }
       
        for (int v = 0; v < VOICES; v++) {
            // Init control zones
            fDSP[v].initControl();
            // Init DSP with default SR
            fDSP[v].init(DEFAULT_SR);
        }
        
        // So that control update will be done at first cycle
        fControlCounter = 1;
    }
    
    ~mydspModule()
    {
        delete fRackUI;
    }
    
    void process(const ProcessArgs& args) override
    {
        // Possibly update SR
        if (args.sampleRate != fDSP[0].getSampleRate()) {
            for (int v = 0; v < VOICES; v++) {
                fDSP[v].init(args.sampleRate);
            }
        }
        
        // Update control and inputs controllers at CONTROL_RATE_HZ
        if (--fControlCounter == 0) {
            // DSP Control
            for (int v = 0; v < VOICES; v++) {
                fDSP[v].control(fDSP[v].iZone, fDSP[v].fZone);
            }
            // Controller update
            fRackUI->updateInputs(params);
        }
        
        // Setup polyphony for inputs
        for (int chan = 0; chan < fDSP[0].getNumInputs(); chan++) {
            inputs[chan].setChannels(VOICES);
        }
        
        // Setup polyphony for outputs
        for (int chan = 0; chan < fDSP[0].getNumOutputs(); chan++) {
            outputs[chan].setChannels(VOICES);
        }
        
        FAUSTFLOAT* inputs_aux = static_cast<FAUSTFLOAT*>(alloca(fDSP[0].getNumInputs() * sizeof(FAUSTFLOAT)));
        FAUSTFLOAT* outputs_aux = static_cast<FAUSTFLOAT*>(alloca(fDSP[0].getNumOutputs() * sizeof(FAUSTFLOAT)));
        
        // Compute all VOICES
        for (int v = 0; v < VOICES; v++) {
            
            // Copy inputs
            for (int chan = 0; chan < fDSP[0].getNumInputs(); chan++) {
                inputs_aux[chan] = (VOICES == 1) ? inputs[chan].getVoltageSum() : inputs[chan].getVoltage(v);
            }
            
            // One sample compute
            fDSP[v].compute(inputs_aux, outputs_aux, fDSP[v].iZone, fDSP[v].fZone);
            
            // Copy outputs
            for (int chan = 0; chan < fDSP[0].getNumOutputs(); chan++) {
                outputs[chan].setVoltage(outputs_aux[chan], v);
            }
        }
        
        // Update output controllers at CONTROL_RATE_HZ
        if (fControlCounter == 0) {
            fRackUI->updateOutputs(params);
            fControlCounter = args.sampleRate/CONTROL_RATE_HZ;
        }
    }
    
};

template <int VOICES>
struct mydspModuleWidget : ModuleWidget {
    
    mydspModuleWidget(mydspModule<VOICES>* module) {
        setModule(module);
       
        // Set a large SVG
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/FaustModule.svg")));
        //box.size.x = RACK_GRID_WIDTH * 30;
       
        // General title
        addLabel(mm2px(Vec(10, 10.0)), "Faust");
        
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        
         // Module is null at plugins selection step, so we can not create the final GUI at that time...
        if (module) {
        
            // Add params
            addLabel(mm2px(Vec(10, 20.0)), "Params");
            
            // Add buttons
            uint buttons = module->fRackUI->fParams.fButtons.size();
            for (uint pa = 0; pa < buttons; pa++) {
                if (module->fRackUI->fParams.fButtons[pa].fType == RackUI::ManagerUI::UIType::kButton) {
                    addParam(createParamCentered<BefacoPush>(mm2px(Vec(8.0 + pa * 15, 35.0)), module, pa));
                } else {
                    addParam(createParamCentered<CKSS>(mm2px(Vec(8.0 + pa * 15, 35.0)), module, pa));
                }
            }
            
            // Add ranges
            uint nentries = module->fRackUI->fParams.fRanges.size();
            for (uint pa = 0; pa < nentries; pa++) {
                 addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.0 + pa * 15, 50.0)), module, pa + buttons));
            }
            
            // Add inputs
            addLabel(mm2px(Vec(10, 60.0)), "Inputs");
            for (int chan = 0; chan < module->fDSP[0].getNumInputs(); chan++) {
                addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.0 + chan * 15, 75.0)), module, chan));
            }
            
            // Add outputs
            addLabel(mm2px(Vec(10, 85.0)), "Outputs");
            for (int chan = 0; chan < module->fDSP[0].getNumOutputs(); chan++) {
                addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.0 + chan * 15, 100.0)), module, chan));
            }
        }
    }
    
    // TODO: use nvgText
    Label* addLabel(const Vec& v, const std::string& str)
    {
        NVGcolor black = nvgRGB(0,0,0);
        Label* label = new Label();
        label->box.pos = v;
        label->text = str;
        label->color = black;
        addChild(label);
        return label;
    }
    
};

Model* modelFaustModule = createModel<mydspModule<NVOICES>, mydspModuleWidget<NVOICES> >("mydsp");

/********************END ARCHITECTURE SECTION (part 2/2)****************/
