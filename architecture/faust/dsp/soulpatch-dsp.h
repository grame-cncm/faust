/************************** BEGIN soulpatch-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#ifndef __soulpatch_dsp__
#define __soulpatch_dsp__

#include <iostream>
#include <vector>
#include <string>

#include "faust/dsp/dsp.h"
#include "faust/GUI/UI.h"

#include "soul_patch.h"

/**
* SOUL signal processor definition.
*/

class soulpatch_dsp : public dsp {
    
    private:
    
        struct ZoneParam {
            
            FAUSTFLOAT fZone;
            soul::patch::Parameter::Ptr fParam;
            
            ZoneParam(soul::patch::Parameter::Ptr param):fParam(param)
            {}
            
            void reflectZone()
            {
                fParam->setValue(fZone);
            }
            
            void modifyZone()
            {
                fZone = fParam->getValue();
            }
            
        };
    
        std::string fPath;
        std::vector<ZoneParam*> fInputsControl;
        std::vector<ZoneParam*> fOutputsControl;
    
        soul::patch::PatchPlayer::Ptr fPlayer;
        soul::patch::PatchInstance::Ptr fPatch;
        soul::patch::PatchPlayerConfiguration fConfig;
    
        // Evennt handler used to call additional functions
        soul::patch::Parameter::Ptr fClassInit;
        soul::patch::Parameter::Ptr fInstanceConstants;
        soul::patch::Parameter::Ptr fInstanceResetUserInterface;
        soul::patch::Parameter::Ptr fInstanceClear;
    
        int countTotalBusChannels(const soul::patch::Bus* buses, int numBuses)
        {
            int res = 0;
            for (int i = 0; i < numBuses; ++i) {
                res += buses[i].numChannels;
            }
            return res;
        }
    
    public:

        soulpatch_dsp(const std::string& path)
        {
            fPath = path;
            soul::patch::SOULPatchLibrary library("/usr/local/lib/SOUL_PatchLoader.dylib");
            if (!library.loadedSuccessfully()) {
                throw std::bad_alloc();
            }
            
            fPatch = library.createPatchFromFileBundle(fPath.c_str());
            soul::patch::Description desc = fPatch->getDescription();
            
            fConfig.sampleRate = 44100;
            fConfig.maxFramesPerBlock = 4096;
            fPlayer = fPatch->compileNewPlayer(fConfig, nullptr);
            soul::patch::String::Ptr error = fPlayer->getCompileError();
            if (error) {
                std::cerr << "getCompileError " << error->getCharPointer() << std::endl;
                throw std::bad_alloc();
            }
        }
    
        virtual ~soulpatch_dsp()
        {
            for (auto& i : fInputsControl) {
                delete i;
            }
            for (auto& i : fOutputsControl) {
                delete i;
            }
        }

        virtual int getNumInputs()
        {
            return countTotalBusChannels(fPlayer->getBuses().inputBuses, fPlayer->getBuses().numInputBuses);
        }
    
        virtual int getNumOutputs()
        {
            return countTotalBusChannels(fPlayer->getBuses().outputBuses, fPlayer->getBuses().numOutputBuses);
        }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openVerticalBox("SOUL");
            {
                ui_interface->openVerticalBox("Inputs");
                soul::patch::Parameter::Ptr* params = fPlayer->getParameters();
                for (int i = 0; i < fPlayer->getNumParameters(); i++) {
                    std::string label = params[i]->ID->getCharPointer();
                    ZoneParam* param = new ZoneParam(params[i]);
                    FAUSTFLOAT* zone = &param->fZone;
                    fInputsControl.push_back(param);
                    if (label.find("Hslider") != std::string::npos) {
                        ui_interface->addHorizontalSlider(params[i]->name->getCharPointer(), zone,
                                                          params[i]->initialValue, params[i]->minValue,
                                                          params[i]->maxValue, params[i]->step);
                    } else if (label.find("Vslider") != std::string::npos) {
                        ui_interface->addVerticalSlider(params[i]->name->getCharPointer(), zone,
                                                        params[i]->initialValue, params[i]->minValue,
                                                        params[i]->maxValue, params[i]->step);
                    } else if (label.find("Entry") != std::string::npos) {
                        ui_interface->addNumEntry(params[i]->name->getCharPointer(), zone,
                                                  params[i]->initialValue, params[i]->minValue,
                                                  params[i]->maxValue, params[i]->step);
                    } else if (label.find("Button") != std::string::npos) {
                        ui_interface->addButton(params[i]->name->getCharPointer(), zone);
                    } else if (label.find("Checkbox") != std::string::npos) {
                        ui_interface->addCheckButton(params[i]->name->getCharPointer(), zone);
                    }
                }
                ui_interface->closeBox();
            }
            {
                ui_interface->openVerticalBox("Outputs");
                soul::patch::Parameter::Ptr* params = fPlayer->getParameters();
                for (int i = 0; i < fPlayer->getNumParameters(); i++) {
                    std::string label = params[i]->ID->getCharPointer();
                    ZoneParam* param = new ZoneParam(params[i]);
                    FAUSTFLOAT* zone = &param->fZone;
                    fOutputsControl.push_back(param);
                    if (label.find("Hbargraph") != std::string::npos) {
                        ui_interface->addHorizontalBargraph(params[i]->name->getCharPointer(), zone,
                                                            params[i]->initialValue, params[i]->minValue);
                    } else if (label.find("Vbargraph") != std::string::npos) {
                        ui_interface->addVerticalBargraph(params[i]->name->getCharPointer(), zone,
                                                          params[i]->initialValue, params[i]->minValue);
                    }
                }
                ui_interface->closeBox();
            }
            ui_interface->closeBox();
        }
    
        virtual int getSampleRate()
        {
            return int(fConfig.sampleRate);
        }
    
        void classInit(int sample_rate)
        {
            if (fClassInit) fClassInit->setValue(0);
        }
    
        virtual void init(int sample_rate)
        {
            fConfig.sampleRate = double(sample_rate);
            fPlayer = fPatch->compileNewPlayer(fConfig, nullptr);
            soul::patch::Parameter::Ptr* params = fPlayer->getParameters();
            for (int i = 0; i < fPlayer->getNumParameters(); i++) {
                std::string label = params[i]->ID->getCharPointer();
                if (label == "eventclassInit") {
                    fClassInit = params[i];
                }
                if (label == "eventinstanceConstants") {
                    fInstanceConstants = params[i];
                }
                if (label == "eventinstanceResetUserInterface") {
                    fInstanceResetUserInterface = params[i];
                }
                if (label == "eventinstanceClear") {
                    fInstanceClear = params[i];
                }
            }
            classInit(sample_rate);
            instanceInit(sample_rate);
        }
  
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }

        virtual void instanceConstants(int sample_rate)
        {
            if (fInstanceConstants) fInstanceConstants->setValue(0);
        }
    
        virtual void instanceResetUserInterface()
        {
            if (fInstanceResetUserInterface) fInstanceResetUserInterface->setValue(0);
        }
    
        virtual void instanceClear()
        {
            if (fInstanceClear) fInstanceClear->setValue(0);
        }
 
        virtual soulpatch_dsp* clone()
        {
            return new soulpatch_dsp(fPath);
        }
    
        virtual void metadata(Meta* m) {}
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Update inputs control
            for (auto& i : fInputsControl) {
                i->reflectZone();
            }
           
            // DSP compute
            soul::patch::PatchPlayer::RenderContext rc;
            rc.inputChannels = (const float**)inputs;
            rc.numInputChannels = getNumInputs();
            rc.outputChannels = outputs;
            rc.numOutputChannels = getNumOutputs();
            rc.numFrames = count;
            fPlayer->render(rc);
            
            // Update outputs control
            for (auto& i : fOutputsControl) {
                i->modifyZone();
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

#endif
/**************************  END  soulpatch-dsp.h **************************/
