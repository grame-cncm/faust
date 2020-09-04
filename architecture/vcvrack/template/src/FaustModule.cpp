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
    
    /* Return instance number of audio inputs */
    virtual int getNumInputs() = 0;
    
    /* Return instance number of audio outputs */
    virtual int getNumOutputs() = 0;
    
    /**
     * Trigger the ui_interface parameter with instance specific calls
     * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
     *
     * @param ui_interface - the user interface builder
     */
    virtual void buildUserInterface(UI* ui_interface) = 0;
    
    /* Returns the sample rate currently used by the instance */
    virtual int getSampleRate() = 0;
    
    /**
     * Global init, calls the following methods:
     * - static class 'classInit': static tables initialization
     * - 'instanceInit': constants and instance state initialization
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    virtual void init(int sample_rate) = 0;
    
    /**
     * Init instance state
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    virtual void instanceInit(int sample_rate) = 0;
    
    /**
     * Init instance constant state
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    virtual void instanceConstants(int sample_rate) = 0;
    
    /* Init default control parameters values */
    virtual void instanceResetUserInterface() = 0;
    
    /* Init instance state (delay lines...) */
    virtual void instanceClear() = 0;
    
    /**
     * Return a clone of the instance.
     *
     * @return a copy of the instance on success, otherwise a null pointer.
     */
    virtual rack_dsp* clone() = 0;
    
    /**
     * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
     *
     * @param m - the Meta* meta user
     */
    virtual void metadata(Meta* m) = 0;
    
    /**
     * DSP instance computation, to be called with successive in/out audio buffers.
     *
     * @param count - the number of frames to compute
     * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
     * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
     *
     */
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
    /**
     * DSP instance computation: alternative method to be used by subclasses.
     *
     * @param date_usec - the timestamp in microsec given by audio driver.
     * @param count - the number of frames to compute
     * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
     * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
     *
     */
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
	
	FaustModule() {
		config(FAUST_ACTIVES, FAUST_INPUTS, FAUST_OUTPUTS, FAUST_PASSIVES);
        for (int param = 0; param < FAUST_ACTIVES; param++) {
            configParam(param, 0.f, 1.f, 0.f, "");
        }
	}

	void process(const ProcessArgs& args) override {
   	}
};

struct FaustModuleWidget : ModuleWidget {
	FaustModuleWidget(FaustModule* module) {
		setModule(module);
        /*
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MyModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.002, 21.161)), module, MyModule::PARAM1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.705, 21.161)), module, MyModule::PARAM2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.877, 42.705)), module, MyModule::PARAM3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.92, 42.857)), module, MyModule::PARAM4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.569, 75.336)), module, MyModule::INPUT1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.894, 75.336)), module, MyModule::INPUT2_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.323, 100.332)), module, MyModule::OUTPUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.92, 100.332)), module, MyModule::OUTPUT2_OUTPUT));
        */
	}
};

Model* modelFaustModule = createModel<FaustModule, FaustModuleWidget>("FaustModule");

//} // end of namespace

/********************END ARCHITECTURE SECTION (part 2/2)****************/
