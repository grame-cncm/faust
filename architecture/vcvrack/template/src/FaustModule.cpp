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

// Rack needed ressources
#include <rack.hpp>
using namespace rack;
static Plugin* pluginInstance;

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifdef _WIN32
typedef unsigned int uint
#endif

/*
// Pixels are just a weird unit, defined by VCV Rack as 1/75 inches, or 0.338(6) mm
*/

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

template <typename REAL>
struct one_sample_dsp : public rack_dsp {
    
    int* iZone;
    REAL* fZone;
    
    one_sample_dsp()
    :iZone(nullptr), fZone(nullptr)
    {}
    
    one_sample_dsp(int* icontrol, REAL* fcontrol)
    :iZone(icontrol), fZone(fcontrol)
    {
        assert(false);
    }
    
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
    
    virtual void control(int* iControl, REAL* fControl) = 0;
    
    virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, REAL* fControl) = 0;
    
    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {}
    
    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/LayoutUI.h"
#include "faust/gui/ValueConverter.h"
#include "faust/misc.h"
#include "plugin.hpp"

#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

// params = [buttons][entries][bargraph]

// A class to count items of each type.
// Parameters with the "CV:N" metadata are kept separately in fInputCV and fOutputCV
// and will be connected to audio CV inputs and outputs.

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
    std::vector<UIItem> fBargraph;
    std::vector<UIItem> fInputCV;
    std::vector<UIItem> fOutputCV;
    
    std::string fCV;
    
    void addRange(const char* label,
                  FAUSTFLOAT init,
                  FAUSTFLOAT min,
                  FAUSTFLOAT max,
                  UIType type)
    {
        if (fCV != "") {
            fInputCV.push_back(UIItem(label, init, min, max, type));
            fCV = "";
        } else {
            fRanges.push_back(UIItem(label, init, min, max, type));
        }
    }
    
    void addBargraph(const char* label,
                     FAUSTFLOAT min,
                     FAUSTFLOAT max,
                     UIType type)
    {
        if (fCV != "") {
            fOutputCV.push_back(UIItem(label, 0, min, max, type));
            fCV = "";
        } else {
            fBargraph.push_back(UIItem(label, 0, min, max, type));
        }
    }
    
    // External API
    void openTabBox(const char* label) {}
    void openHorizontalBox(const char* label) {}
    void openVerticalBox(const char* label) {}
    void closeBox() {}
    
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        if (fCV != "") {
            fInputCV.push_back(UIItem(label, 0, 1, 0, kButton));
            fCV = "";
        } else {
            fButtons.push_back(UIItem(label, 0, 1, 0, kButton));
        }
    }
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        if (fCV != "") {
            fInputCV.push_back(UIItem(label, 0, 1, 0, kCheckbox));
            fCV = "";
        } else {
            fButtons.push_back(UIItem(label, 0, 1, 0, kCheckbox));
        }
    }
    
    void addVerticalSlider(const char* label,
                           FAUSTFLOAT* zone,
                           FAUSTFLOAT init,
                           FAUSTFLOAT min,
                           FAUSTFLOAT max,
                           FAUSTFLOAT step)
    {
        addRange(label, init, min, max, kVSlider);
    }
    void addHorizontalSlider(const char* label,
                             FAUSTFLOAT* zone,
                             FAUSTFLOAT init,
                             FAUSTFLOAT min,
                             FAUSTFLOAT max,
                             FAUSTFLOAT step)
    {
        addRange(label, init, min, max, kHSlider);
    }
    void addNumEntry(const char* label,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT init,
                     FAUSTFLOAT min,
                     FAUSTFLOAT max,
                     FAUSTFLOAT step)
    {
        addRange(label, init, min, max, kNumEntry);
    }
    
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addBargraph(label, min, max, kHBargraph);
    }
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addBargraph(label, min, max, kVBargraph);
    }
    
    void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        if (std::string(key) == "CV" || std::string(key) == "cv") {
            fCV = val;
        }
    }
};

// UI handler for switches, knobs and lights
template <int VOICES>
struct RackUI : public GenericUI
{
    typedef function<void(Module* module)> updateFunction;
    
    std::vector<ConverterZoneControl*> fConverters;
    std::vector<updateFunction> fUpdateFunIn;
    std::vector<updateFunction> fUpdateFunOut;
    
    ManagerUI fParams;
    std::string fScale, fCV;
    
    int fButtonsCounter = 0;
    int fParamsCounter = 0;
    int fBargraphCounter = 0;
    int fCurVoice = -1;
    
    int parseIndex(const std::string& value)
    {
        try {
            return stoi(value);
        } catch (invalid_argument& e) {
            return -1;
        }
    }
    
    RackUI(const ManagerUI& counter):fParams(counter), fScale("lin")
    {}
    
    virtual ~RackUI()
    {
        for (const auto& it : fConverters) delete it;
    }
    
    void reset()
    {
        fButtonsCounter = 0;
        fParamsCounter = 0;
        fBargraphCounter = 0;
        fScale = "lin";
        fCV = "";
    }
    
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        if (fCV != "") {
            int index = parseIndex(fCV)-1;
            if (index < 0) {
                WARN("Incorrect index");
                return;
            }
            
            // Capture current voice
            int voice = fCurVoice;
            fUpdateFunIn.push_back([=] (Module* module)
                                   {
                                       float cv = (VOICES == 1) ? module->inputs[index].getVoltage() : module->inputs[index].getVoltage(voice);
                                       *zone = cv/10.f;
                                   });
            
            fCV = "";
        } else {
            // Takes the value at lambda contruction time
            int index = fButtonsCounter;
            fUpdateFunIn.push_back([=] (Module* module)
                                   {
                                       // 'buttons' start at 0
                                       *zone = module->params[index].getValue()/10.f;
                                   });
            fButtonsCounter++;
        }
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
        
        if (fCV != "") {
            
            int index = parseIndex(fCV)-1;
            if (index < 0) {
                WARN("Incorrect index");
                return;
            }
            
            // Capture current voice
            int voice = fCurVoice;
            
            if (MapUI::endsWith(label, "freq")) {
                
                converter = new ConverterZoneControl(zone, new ValueConverter());
                fUpdateFunIn.push_back([=] (Module* module)
                                       {
                                           float cv = (VOICES == 1) ? module->inputs[index].getVoltage() : module->inputs[index].getVoltage(voice);
                                           float freq = 440.f * std::pow(2.f, (cv - 0.75f));
                                           // Receive a 1V/oct pitch signal of the last held MIDI note: https://vcvrack.com/manual/Core#midi-cv
                                           converter->update(freq);
                                       });
                
            } else if (MapUI::endsWith(label, "gate")) {
                
                converter = new ConverterZoneControl(zone, new ValueConverter());
                fUpdateFunIn.push_back([=] (Module* module)
                                       {
                                           float cv = (VOICES == 1) ? module->inputs[index].getVoltage() : module->inputs[index].getVoltage(voice);
                                           // Receive a 10V signal when a key is held: https://vcvrack.com/manual/Core#midi-cv
                                           converter->update(cv/10.f);
                                       });
                
                
            } else if (MapUI::endsWith(label, "gain")) {
                
                converter = new ConverterZoneControl(zone, new ValueConverter());
                fUpdateFunIn.push_back([=] (Module* module)
                                       {
                                           float cv = (VOICES == 1) ? module->inputs[index].getVoltage() : module->inputs[index].getVoltage(voice);
                                           // Receive a signal from 0V to 10V for the velocity: https://vcvrack.com/manual/Core#midi-cv
                                           converter->update(cv/10.f);
                                       });
                
            } else {
                if (fScale == "log") {
                    converter = new ConverterZoneControl(zone, new LogValueConverter(-5, 5, min, max));
                } else if (fScale == "exp") {
                    converter = new ConverterZoneControl(zone, new ExpValueConverter(-5, 5, min, max));
                } else {
                    converter = new ConverterZoneControl(zone, new LinearValueConverter(-5, 5, min, max));
                }
                
                fUpdateFunIn.push_back([=] (Module* module)
                                       {
                                           float cv = (VOICES == 1) ? module->inputs[index].getVoltage() : module->inputs[index].getVoltage(voice);
                                           converter->update(cv);
                                       });
            }
            
            fCV = "";
        } else {
            
            if (fScale == "log") {
                converter = new ConverterZoneControl(zone, new LogValueConverter(min, max, min, max));
            } else if (fScale == "exp") {
                converter = new ConverterZoneControl(zone, new ExpValueConverter(min, max, min, max));
            } else {
                converter = new ConverterZoneControl(zone, new ValueConverter());
            }
            
            // Takes the value at lambda contruction time
            int index = fParamsCounter;
            fUpdateFunIn.push_back([=] (Module* module)
                                   {
                                       // 'nentries' start at fParams.fButtons.size()
                                       converter->update(module->params[index + fParams.fButtons.size()].getValue());
                                   });
            fScale = "lin";
            fParamsCounter++;
        }
        fConverters.push_back(converter);
    }
    
    void addBarGraph(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        ConverterZoneControl* converter;
        
        if (fCV != "") {
            
            if (fScale == "log") {
                converter = new ConverterZoneControl(zone, new LogValueConverter(-5, 5, min, max));
            } else if (fScale == "exp") {
                converter = new ConverterZoneControl(zone, new ExpValueConverter(-5, 5, min, max));
            } else {
                converter = new ConverterZoneControl(zone, new LinearValueConverter(-5, 5, min, max));
            }
            
            int index = parseIndex(fCV)-1;
            if (index < 0) {
                WARN("Incorrect index");
                return;
            }
            
            int voice = fCurVoice;
            fUpdateFunOut.push_back([=] (Module* module)
                                    {
                                        if (VOICES == 1) {
                                            module->outputs[index].setVoltage(converter->getConverter()->faust2ui(*zone));
                                        }  else {
                                            module->outputs[index].setVoltage(voice, converter->getConverter()->faust2ui(*zone));
                                        }
                                    });
            fCV = "";
        } else {
            
            if (fScale == "log") {
                converter = new ConverterZoneControl(zone, new LogValueConverter(0., 1., min, max));
            } else if (fScale == "exp") {
                converter = new ConverterZoneControl(zone, new ExpValueConverter(0., 1., min, max));
            } else {
                converter = new ConverterZoneControl(zone, new LinearValueConverter(0., 1., min, max));
            }
            
            // Takes the value at lambda contruction time
            int index = fBargraphCounter;
            
            fUpdateFunOut.push_back([=] (Module* module) {
                module->lights[index].setBrightness(converter->getConverter()->faust2ui(*zone));
            });
            fBargraphCounter++;
        }
        
        fConverters.push_back(converter);
        fScale = "lin";
    }
    
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addBarGraph(zone, min, max);
    }
    
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        addBarGraph(zone, min, max);
    }
    
    void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        if (std::string(key) == "scale") {
            fScale = val;
        } else if (std::string(key) == "CV" || std::string(key) == "cv") {
            fCV = val;
        }
    }
    
    void updateInputs(Module* module)
    {
        for (const auto& it : fUpdateFunIn) it(module);
    }
    
    void updateOutputs(Module* module)
    {
        for (const auto& it : fUpdateFunOut) it(module);
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
    
    LayoutUI fLayoutUI;
    RackUI<VOICES>* fRackUI;    // One single version for all VOICES
    mydsp fDSP[VOICES];
    int fControlCounter;
#ifdef SOUNDFILE
    SoundUI* fSoundUI;
#endif
    mydspModule()
    {
        // Count items of button, nentry, bargraph categories
        ManagerUI params;
        fDSP[0].buildUserInterface(&params);
    #ifdef SOUNDFILE
        fSoundUI = new SoundUI(rack::asset::plugin(pluginInstance, "res/"));
    #endif
        // Controllers are connected to all VOICES
        fRackUI = new RackUI<VOICES>(params);
        for (int v = 0; v < VOICES; v++) {
            fRackUI->fCurVoice = v;
            fDSP[v].buildUserInterface(fRackUI);
            fRackUI->reset();
        #ifdef SOUNDFILE
            fDSP[v].buildUserInterface(fSoundUI);
        #endif
        }
        
        uint buttons = params.fButtons.size();
        uint entries = params.fRanges.size();
        uint bargraphs = params.fBargraph.size();
        uint inputCV = params.fInputCV.size();
        uint outputCV = params.fOutputCV.size();
        
        // Config: by default we allocate complete set of parameters, even if all of them are not 'connected' using metadata
        config(buttons + entries, inputCV + fDSP[0].getNumInputs(), outputCV + fDSP[0].getNumOutputs(), bargraphs);
        
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
        
        // Set items minimal size
        gItemSize.kVSliderWidth = 20.0;
        gItemSize.kVSliderHeight = 20.0;
        
        gItemSize.kHSliderWidth = 20.0;
        gItemSize.kHSliderHeight = 20.0;
        
        gItemSize.kButtonWidth = 20.0;
        gItemSize.kButtonHeight = 20.0;
        
        gItemSize.kCheckButtonWidth = 20.0;
        gItemSize.kCheckButtonWidth = 20.0;
    }
    
    ~mydspModule()
    {
        delete fRackUI;
    #ifdef SOUNDFILE
        delete fSoundUI;
    #endif
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
            fRackUI->updateInputs(this);
        }
        
        // Setup polyphony for CV inputs
        uint inputsCV = fRackUI->fParams.fInputCV.size();
        for (uint chan = 0; chan < inputsCV; chan++) {
            inputs[chan].setChannels(VOICES);
        }
        
        // Setup polyphony for audio inputs (shifted by inputsCV in 'inputs' struct)
        for (int chan = 0; chan < fDSP[0].getNumInputs(); chan++) {
            inputs[chan + inputsCV].setChannels(VOICES);
        }
        
        // Setup polyphony for CV outputs
        uint outputsCV = fRackUI->fParams.fOutputCV.size();
        for (uint chan = 0; chan < outputsCV; chan++) {
            outputs[chan].setChannels(VOICES);
        }
        
        // Setup polyphony for audio outputs (shifted by outputsCV in 'outputs' struct)
        for (int chan = 0; chan < fDSP[0].getNumOutputs(); chan++) {
            outputs[chan + outputsCV].setChannels(VOICES);
        }
        
        FAUSTFLOAT* inputs_aux = static_cast<FAUSTFLOAT*>(alloca(fDSP[0].getNumInputs() * sizeof(FAUSTFLOAT)));
        FAUSTFLOAT* outputs_aux = static_cast<FAUSTFLOAT*>(alloca(fDSP[0].getNumOutputs() * sizeof(FAUSTFLOAT)));
        
        // Compute all VOICES
        for (int v = 0; v < VOICES; v++) {
            
            // Copy inputs
            for (int chan = 0; chan < fDSP[0].getNumInputs(); chan++) {
                inputs_aux[chan] = ((VOICES == 1) ? inputs[chan + inputsCV].getVoltageSum() : inputs[chan + inputsCV].getVoltage(v))/5.0f;
            }
            
            // One sample compute
            fDSP[v].compute(inputs_aux, outputs_aux, fDSP[v].iZone, fDSP[v].fZone);
            
            // Copy outputs
            for (int chan = 0; chan < fDSP[0].getNumOutputs(); chan++) {
                outputs[chan + outputsCV].setVoltage(outputs_aux[chan]*5.0f, v);
            }
        }
        
        // Update output controllers at CONTROL_RATE_HZ
        if (fControlCounter == 0) {
            fRackUI->updateOutputs(this);
            fControlCounter = args.sampleRate/CONTROL_RATE_HZ;
        }
    }
    
    void getMinimumSize(float& width, float& height)
    {
        // Set items minimal size
        gItemSize.kHSliderWidth = 50.0;
        gItemSize.kVSliderWidth = 50.0;
        
        gItemSize.kButtonWidth = 50.0;
        gItemSize.kButtonHeight = 50.0;
        
        // Prepare layout
        fDSP[0].buildUserInterface(&fLayoutUI);
        
        cout << "==========================" << endl;
        for (const auto& it : fLayoutUI.fPathItemMap) {
            cout << it.first << endl;
            cout << it.second << endl;
        }
        
        cout << "Width " << fLayoutUI.getWidth() << endl;
        cout << "Height " << fLayoutUI.getHeight() << endl;
        
        width = fLayoutUI.getWidth();
        height = fLayoutUI.getHeight();
    }
    
    void setSize(float x_pos, float y_pos, float width, float height)
    {
        fLayoutUI.setSize(width, height);
        fLayoutUI.setPos(x_pos, y_pos);
        
        cout << "==========================" << endl;
        for (const auto& it : fLayoutUI.fPathItemMap) {
            cout << it.first << endl;
            cout << it.second << endl;
        }
        
        cout << "Width " << fLayoutUI.getWidth() << endl;
        cout << "Height " << fLayoutUI.getHeight() << endl;
    }
    
};

// Draw a opaque background color
struct FaustBackgroundWidget : widget::Widget {
    
    std::shared_ptr<Font> fFont;
    
    FaustBackgroundWidget(std::shared_ptr<Font> font)
    {
        fFont = font;
    }
    
    void draw(const DrawArgs& args) override {
        nvgBeginPath(args.vg);
        nvgRect(args.vg, 0, 0, box.size.x, box.size.y);
        // nvgRGB(234,88,15)); // Faust orange color
        nvgFillColor(args.vg, nvgRGB(254,108,35)); // Faust orange color + 20 white
        nvgFill(args.vg);
    }
    
};

template <int VOICES>
struct mydspModuleWidget : ModuleWidget {
    
    std::shared_ptr<Font> fFont;
    
    void addBackground(int width, int height)
    {
        // Default size
        box.size.x = width;
        box.size.y = height;
        FaustBackgroundWidget* wd = new FaustBackgroundWidget(fFont);
        wd->setSize(Vec(box.size.x, box.size.y));
        addChild(wd);
    
        // General title
        addLabel(Vec(width/2.0 - 32, 10.0), "Faust", 20);
        
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    }
    
    mydspModuleWidget(mydspModule<VOICES>* module) {
        
        //fFont = APP->window->loadFont(asset::plugin(pluginInstance, "res/Lato-HairlineItalic.ttf"));
        bndSetFont(0);
        setModule(module);
        
        // Set a large SVG
        //setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/FaustModule.svg")));
       
        // Module is null at plugins selection step, so we cannot create the final GUI at that time
        if (module) {
            
            // Compute available size by removing space for CV inputs/outputs and audio inputs/outputs
            uint buttons = module->fRackUI->fParams.fButtons.size();
            uint nentries = module->fRackUI->fParams.fRanges.size();
            uint bargraphs = module->fRackUI->fParams.fBargraph.size();
            uint inputsCV = module->fRackUI->fParams.fInputCV.size();
            uint outputsCV = module->fRackUI->fParams.fOutputCV.size();
            
            float item_width = 18;
            float item_height = 20;
            
            /*
            uint reserved_height = ((inputsCV > 0) ? 10 : 0)
                + ((outputsCV > 0) ? 10 : 0)
                + ((module->fDSP[0].getNumInputs() > 0) ? 10 : 0)
                + ((module->fDSP[0].getNumOutputs() > 0) ? 10 : 0);
            */
            
            vector<int> items = { 2, int(bargraphs), int(buttons), int(nentries), module->fDSP[0].getNumInputs(), module->fDSP[0].getNumOutputs() };
            sort(items.begin(), items.end(), greater<int>());
            int needed_width = mm2px(items[0] * item_width);
            addBackground(std::max(int(RACK_GRID_WIDTH), int(needed_width)), RACK_GRID_HEIGHT);
            
            /*
            // TODO
             
            // Get UI minimum size
            float minimal_width, minimal_height;
            module->getMinimumSize(minimal_width, minimal_height);
           
            // Then prepare the size of UI params
            module->setSize(5.f, 5.f, minimal_width, 100 - reserved_height);
            
            // Add params
            //addLabel(mm2px(Vec(6, 10.0)), "Params");
            */
            
            // Add buttons
            for (uint pa = 0; pa < buttons; pa++) {
                std::string label = module->fRackUI->fParams.fButtons[pa].fLabel;
                if (module->fRackUI->fParams.fButtons[pa].fType == ManagerUI::UIType::kButton) {
                    addParam(createParamCentered<BefacoPush>(mm2px(Vec(8.0 + pa * item_width, item_height)), module, pa));
                } else {
                    addParam(createParamCentered<CKSS>(mm2px(Vec(8.0 + pa * item_width, item_height)), module, pa));
                }
                addLabel(mm2px(Vec(0.0 + pa * item_width, item_height + 5.0)), label);
            }
            
            // Add ranges (sliders, nentry)
            for (uint pa = 0; pa < nentries; pa++) {
                std::string label = module->fRackUI->fParams.fRanges[pa].fLabel;
                addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.0 + pa * item_width, item_height * 2)), module, pa + buttons));
                addLabel(mm2px(Vec(0.0 + pa * item_width, item_height * 2 + 5.0)), label);
            }
            
            // Add bargraph
            for (uint pa = 0; pa < bargraphs; pa++) {
                std::string label = module->fRackUI->fParams.fBargraph[pa].fLabel;
                addChild(createLightCentered<LargeLight<RedLight>>(mm2px(Vec(8.0 + pa * item_width, item_height * 3)), module, pa));
                addLabel(mm2px(Vec(0.0 + pa * item_width, item_height * 3 + 5.0)), label);
            }
            
            // Add CV inputs
            if (inputsCV > 0) {
                addLabel(mm2px(Vec(0.0, 55.0)), "Inputs CV");
                for (uint chan = 0; chan < inputsCV; chan++) {
                    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.0 + chan * 15, 66.0)), module, chan));
                }
            }
            
            // Add audio inputs (shifted by inputsCV in 'inputs' struct)
            if (module->fDSP[0].getNumInputs() > 0) {
                addLabel(mm2px(Vec(0.0, 72.0)), "Inputs");
                for (int chan = 0; chan < module->fDSP[0].getNumInputs(); chan++) {
                    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.0 + chan * 15, 83.0)), module, inputsCV + chan));
                }
            }
            
            // Add CV outputs
            if (outputsCV > 0) {
                addLabel(mm2px(Vec(0.0, 89.0)), "Outputs CV");
                for (uint chan = 0; chan < outputsCV; chan++) {
                    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.0 + chan * 15, 100.0)), module, chan));
                }
            }
            
            // Add outputs (shifted by outputsCV in 'outputs' struct)
            if (module->fDSP[0].getNumOutputs() > 0) {
                addLabel(mm2px(Vec(0.0, 106.0)), "Outputs");
                for (int chan = 0; chan < module->fDSP[0].getNumOutputs(); chan++) {
                    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.0 + chan * 15, 117.0)), module, outputsCV + chan));
                }
            }
        } else {
            addBackground(RACK_GRID_WIDTH * 5, RACK_GRID_HEIGHT);
        }
    }
    
    // TODO: use nvgText
    // https://community.vcvrack.com/t/advanced-nanovg-custom-label/6769
    // https://www.1001fonts.com
    Label* addLabel(const Vec& v, const std::string& str, float fontSize = 13)
    {
        NVGcolor black = nvgRGB(0,0,0);
        Label* label = new Label();
        label->box.pos = v;
        label->text = str;
        label->color = black;
        label->fontSize = fontSize;
        //label->alignment = rack::ui::Label::RIGHT_ALIGNMENT;
        addChild(label);
        return label;
    }
    
};

// Create and init plugin
Model* modelFaustModule = createModel<mydspModule<NVOICES>, mydspModuleWidget<NVOICES> >("mydsp");

void init(Plugin* p)
{
    pluginInstance = p;
    // Add modules here
    p->addModel(modelFaustModule);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
