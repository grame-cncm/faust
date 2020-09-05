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
// dsp.h file is included and dsp file is renamed to rack_dsp to avoid name conflicts. Then 'faust -scn rack_dsp' is used in faust2vcvrack.

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

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

#include <faust/gui/DecoratorUI.h>
#include <faust/gui/ValueConverter.h>
#include "faust/misc.h"
#include "plugin.hpp"

// params  = [buttons][entries][bargraph]

// UI handler for switches, knobs and lights
struct RackUI : public GenericUI
{
    // A internal class to count items of each type
    struct UILayout : public GenericUI
    {
        #define PARAM_WIDTH 20
        #define PARAM_HEIGHT 20
        
        struct ZoneItem {
            std::string fLabel;
            ZoneItem(const std::string& label):fLabel(label) {}
        };
        
        std::vector<ZoneItem> fButtonParams;
        std::vector<ZoneItem> fRangeParams;
        std::vector<ZoneItem> fOutputParams;
        
        void openTabBox(const char* label) {}
        void openHorizontalBox(const char* label) {}
        void openVerticalBox(const char* label) {}
        void closeBox() {}
        
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fButtonParams.push_back(ZoneItem(label));
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fButtonParams.push_back(ZoneItem(label));
        }
        
        void addVerticalSlider(const char* label,
                               FAUSTFLOAT* zone,
                               FAUSTFLOAT init,
                               FAUSTFLOAT min,
                               FAUSTFLOAT max,
                               FAUSTFLOAT step)
        {
            fRangeParams.push_back(ZoneItem(label));
        }
        void addHorizontalSlider(const char* label,
                                 FAUSTFLOAT* zone,
                                 FAUSTFLOAT init,
                                 FAUSTFLOAT min,
                                 FAUSTFLOAT max,
                                 FAUSTFLOAT step)
        {
            fRangeParams.push_back(ZoneItem(label));
        }
        void addNumEntry(const char* label,
                         FAUSTFLOAT* zone,
                         FAUSTFLOAT init,
                         FAUSTFLOAT min,
                         FAUSTFLOAT max,
                         FAUSTFLOAT step)
        {
            fRangeParams.push_back(ZoneItem(label));
        }
        
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fOutputParams.push_back(ZoneItem(label));
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fOutputParams.push_back(ZoneItem(label));
        }
        
        int getWidth() { return (fButtonParams.size() + fRangeParams.size()) * PARAM_WIDTH; }
        int getHeight() { return (fButtonParams.size() + fRangeParams.size()) * PARAM_HEIGHT; }
    };
    
    typedef function<void(std::vector<Param>& params)> updateFunction;
    
    std::vector<ConverterZoneControl*> fConverters;
    std::vector<updateFunction> fUpdateFunIn;
    std::vector<updateFunction> fUpdateFunOut;
    
    // For checkbox handling
    struct CheckBox { float fLastButton = 0.0f; };
    std::map <FAUSTFLOAT*, CheckBox> fCheckBoxes;
    
    RackUI::UILayout fCounter;
    std::string fKey, fValue, fScale;
    
    int getIndex(const std::string& value)
    {
        try {
            return std::stoi(value);
        } catch (invalid_argument& e) {
            return -1;
        }
    }
    
    RackUI(const RackUI::UILayout& counter):fCounter(counter), fScale("lin")
    {}
    
    virtual ~RackUI()
    {
        for (auto& it : fConverters) delete it;
    }
    
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        int index = getIndex(fValue);
        if (fKey == "switch" && (index != -1)) {
            fUpdateFunIn.push_back([=] (std::vector<Param>& params)
                                   {
                                       // 'buttons' start at 0
                                       *zone = params[index-1].getValue();
                                       
                                       // And set the color to red when ON
                                       //args.switchLights[index-1][0] = *zone;
                                   });
        }
    }
    
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        // index start at 0
        int index = getIndex(fValue) - 1;
        if (fKey == "switch" && (index != -1)) {
            // Add a checkbox
            fCheckBoxes[zone] = CheckBox();
            // Update function
            fUpdateFunIn.push_back([=] (std::vector<Param>& params)
                                   {
                                       // 'buttons' start at 0
                                       float button = params[index].getValue();
                                       // Detect upfront
                                       if (button == 1.0 && (button != fCheckBoxes[zone].fLastButton)) {
                                           // Switch button state
                                           *zone = !*zone;
                                           /*
                                           // And set the color to white when ON
                                           args.switchLights[index-1][0] = *zone;
                                           args.switchLights[index-1][1] = *zone;
                                           args.switchLights[index-1][2] = *zone;
                                           */
                                       }
                                       // Keep previous button state
                                       fCheckBoxes[zone].fLastButton = button;
                                   });
        }
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
        // index start at 0
        int index = getIndex(fValue) - 1;
        if (fKey == "knob" && (index != -1)) {
            ConverterZoneControl* converter;
            if (fScale == "log") {
                converter = new ConverterZoneControl(zone, new LogValueConverter(0., 1., min, max));
            } else if (fScale == "exp") {
                converter = new ConverterZoneControl(zone, new ExpValueConverter(0., 1., min, max));
            } else {
                converter = new ConverterZoneControl(zone, new LinearValueConverter(0., 1., min, max));
            }
            fUpdateFunIn.push_back([=] (std::vector<Param>& params)
                                   {
                                       // 'nentries' start at fCounter.fButtonParams.size()
                                       converter->update(params[index + fCounter.fButtonParams.size()].getValue());
                                   });
            fConverters.push_back(converter);
        }
        fScale = "lin";
    }
    
    void addBarGraph(FAUSTFLOAT* zone)
    {
        /*
        // index start at 0
        int index = getIndex(fValue) - 1;
        if ((fKey == "light_red") && (index != -1)) {
            fUpdateFunOut.push_back([=] (std::vector<Param>& params)
                                    {
                                        // 'nentries' start at fCounter.fButton + fCounter.fNumEntry
                                        params[index + fCounter.fButton + fCounter.fNumEntry][0].setValue(*zone);
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
    
    void addSoundfile(const char* label, const char* soundpath, Soundfile** sf_zone)
    {
        WARN("Faust Prototype : 'soundfile' primitive not yet supported", "");
    }
    
    void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        static vector<std::string> keys = {"switch", "knob", "light_red", "light_green", "light_blue", "switchlight_red", "switchlight_green", "switchlight_blue"};
        if (find(keys.begin(), keys.end(), key) != keys.end()) {
            fKey = key;
            fValue = val;
        } else if (std::string(key) == "scale") {
            fScale = val;
        }
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

struct FaustModule : Module {
    
    FAUSTFLOAT** fInputs;
    FAUSTFLOAT** fOutputs;
    RackUI* fRackUI;
    mydsp fDSP;
    int fControlCounter;
    
    FaustModule()
    {
        // Count items of button, nentry, bargraph categories
        RackUI::UILayout counter;
        fDSP.buildUserInterface(&counter);
        
        fRackUI = new RackUI(counter);
        fDSP.buildUserInterface(fRackUI);
        
        // Config
        config(counter.fButtonParams.size() + counter.fRangeParams.size(),
               fDSP.getNumInputs(),
               fDSP.getNumOutputs(),
               counter.fOutputParams.size());
        for (int param = 0; param < (counter.fButtonParams.size() + counter.fRangeParams.size()); param++) {
            configParam(param, 0.f, 1.f, 0.f, "");
        }
        
        // Allocate non-interleaved audio ins/outs buffers for 'compute'
        fInputs = new FAUSTFLOAT*[fDSP.getNumInputs()];
        for (int chan = 0; chan < fDSP.getNumInputs(); chan++) {
            fInputs[chan] = new FAUSTFLOAT[1];
        }
        
        fOutputs = new FAUSTFLOAT*[fDSP.getNumOutputs()];
        for (int chan = 0; chan < fDSP.getNumOutputs(); chan++) {
            fOutputs[chan] = new FAUSTFLOAT[1];
        }
        
        // Init DSP with default SR
        fDSP.init(DEFAULT_SR);
        fControlCounter = DEFAULT_SR/CONTROL_RATE_HZ;
    }
    
    ~FaustModule()
    {
        for (int chan = 0; chan < fDSP.getNumInputs(); chan++) {
            delete [] fInputs[chan];
        }
        delete [] fInputs;
        for (int chan = 0; chan < fDSP.getNumOutputs(); chan++) {
            delete [] fOutputs[chan];
        }
        delete [] fOutputs;
        delete fRackUI;
    }
    
    void process(const ProcessArgs& args) override
    {
        // Possibly update SR
        if (args.sampleRate != fDSP.getSampleRate()) {
            fDSP.init(args.sampleRate);
        }
        
        // Update control rate counter
        fControlCounter--;
        
        // Copy inputs
        for (int chan = 0; chan < fDSP.getNumInputs(); chan++) {
            fInputs[chan][0] = inputs[chan].getVoltage()/5.0f;
        }
        
        // Update inputs controllers at CONTROL_RATE_HZ
        if (fControlCounter == 0) {
            for (auto& it : fRackUI->fUpdateFunIn) it(params);
        }
        
        // Compute one sample
        fDSP.compute(1, fInputs, fOutputs);
        
        // Update output controllers at CONTROL_RATE_HZ
        if (fControlCounter == 0) {
            for (auto& it : fRackUI->fUpdateFunOut) it(params);
            fControlCounter = args.sampleRate/CONTROL_RATE_HZ;
        }
        
        // Copy outputs
        for (int chan = 0; chan < fDSP.getNumOutputs(); chan++) {
            outputs[chan].setVoltage(fOutputs[chan][0]*5.0f);
        }
    }
    
};

struct FaustModuleWidget : ModuleWidget {
    
    FaustModuleWidget(FaustModule* module) {
        setModule(module);
        // Set a large SVG
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/FaustModule.svg")));
        box.size.x = RACK_GRID_WIDTH * 30;
        
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.002, 21.161)), module, 0));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.705, 21.161)), module, 1));
        
        /*
         addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.877, 42.857)), module, 2));
         addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.92, 42.857)), module, 3));
         
         addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.569, 75.336)), module, 0));
         addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.894, 75.336)), module, 1));
         */
        
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.002, 100.332)), module, 0));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.705, 100.332)), module, 1));
    }
    
};

Model* modelFaustModule = createModel<FaustModule, FaustModuleWidget>("FaustModule");

/********************END ARCHITECTURE SECTION (part 2/2)****************/
