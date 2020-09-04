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

//#include "faust/dsp/dsp.h"

// dsp.h file is included and dsp file is renamed to rack_dsp to avoid name conflicts. Then 'faust -scn rack_dsp' has to be used.

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

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

#include "faust/gui/UI.h"
#include "faust/misc.h"

#include "plugin.hpp"

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

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

mydsp DSP;

struct FaustModule : Module {
    
    FAUSTFLOAT** fInputs;
    FAUSTFLOAT** fOutputs;
    
    FaustModule()
    {
        config(FAUST_ACTIVES, FAUST_INPUTS, FAUST_OUTPUTS, FAUST_PASSIVES);
        for (int param = 0; param < FAUST_ACTIVES; param++) {
            configParam(param, 0.f, 1.f, 0.f, "");
        }
        
        fInputs = new FAUSTFLOAT*[DSP.getNumInputs()];
        for (int chan = 0; chan < DSP.getNumInputs(); chan++) {
            fInputs[chan] = new FAUSTFLOAT[1];
        }
        
        fOutputs = new FAUSTFLOAT*[DSP.getNumOutputs()];
        for (int chan = 0; chan < DSP.getNumOutputs(); chan++) {
            fOutputs[chan] = new FAUSTFLOAT[1];
        }
        
        // Init DSP with default SR
        DSP.init(44100);
    }
    
    ~FaustModule()
    {
        for (int chan = 0; chan < DSP.getNumInputs(); chan++) {
            delete [] fInputs[chan];
        }
        delete [] fInputs;
        for (int chan = 0; chan < DSP.getNumOutputs(); chan++) {
            delete [] fOutputs[chan];
        }
        delete [] fOutputs;
    }
    
    void process(const ProcessArgs& args) override
    {
        // Possibly update SR
        if (args.sampleRate != DSP.getSampleRate()) {
            DSP.init(args.sampleRate);
        }
        
        // Copy inputs
        for (int chan = 0; chan < DSP.getNumInputs(); chan++) {
            fInputs[chan][0] = inputs[chan + 1].getVoltage() / 5.0f;
        }
        
        // Compute samples
        DSP.compute(1, fInputs, fOutputs);
        
        // Copy outputs
        for (int chan = 0; chan < DSP.getNumOutputs(); chan++) {
            outputs[chan + 1].setVoltage(fOutputs[chan][0] * 5.0f);
        }
    }
    
};

struct FaustModuleWidget : ModuleWidget {
    FaustModuleWidget(FaustModule* module) {
        setModule(module);
        
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/FaustModule.svg")));
        
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        
        /*
         addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.002, 21.161)), module, 0));
         addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.705, 21.161)), module, 1));
         addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.877, 42.705)), module, 2));
         addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.92, 42.857)), module, 3));
         
         addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.569, 75.336)), module, 0));
         addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.894, 75.336)), module, 1));
         */
        
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.323, 100.332)), module, 0));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.92, 100.332)), module, 1));
    }
};

Model* modelFaustModule = createModel<FaustModule, FaustModuleWidget>("FaustModule");

/********************END ARCHITECTURE SECTION (part 2/2)****************/
