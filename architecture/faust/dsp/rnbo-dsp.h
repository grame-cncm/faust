/************************** BEGIN rnbo-dsp.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2023 GRAME, Centre National de Creation Musicale
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
 ***************************************************************************/

#ifndef __rnbo_dsp__
#define __rnbo_dsp__

#include <iostream>
#include <string>
#include <vector>

#include "rnbo/rnbo/RNBO.h"
#include "rnbo/rnbo/RNBO.cpp"
#include "rnbo/rnbo_source.cpp"

class rnbo_dsp : public dsp {
    
    private:
    
        RNBO::CoreObject fDSP;
        FAUSTFLOAT* fInputsZoneMap;
        //FAUSTFLOAT* fOutputsZoneMap;
        std::vector<std::pair<FAUSTFLOAT*, std::function<void(FAUSTFLOAT)>>> fZoneFunMap;
    
        int fSampleRate;
        
        bool startWith(const std::string& str, const std::string& prefix)
        {
            return (str.substr(0, prefix.size()) == prefix);
        }
        
        void updateControls()
        {
            for (const auto& it : fZoneFunMap) {
                it.second(*it.first);
            }
        }
    
    public:
    
        rnbo_dsp()
        {
            fInputsZoneMap = new FAUSTFLOAT[fDSP.getNumParameters()];
            //fOutputsZoneMap = new FAUSTFLOAT[fDSP.numOutputEndpoints];
        }
    
        virtual ~rnbo_dsp()
        {
            delete [] fInputsZoneMap;
            //delete [] fOutputsZoneMap;
        }
    
        void init(int sample_rate)
        {
            // Inlined
            // classInit(sample_rate);
            instanceInit(sample_rate);
        }
        
        int getNumInputs() { return fDSP.getNumInputChannels(); }
        int getNumOutputs() { return fDSP.getNumOutputChannels(); }
        
        int getSampleRate() { return fSampleRate; }
        
        void instanceInit(int sample_rate)
        {
            fSampleRate = sample_rate;
            fDSP.prepareToProcess(sample_rate, 512, true);
        }
        
        void instanceConstants(int sample_rate)
        {}
        void instanceResetUserInterface()
        {
            for (int i = 0; i < fZoneFunMap.size(); i++) {
                RNBO::ParameterInfo info;
                fDSP.getParameterInfo(i, &info);
                *fZoneFunMap[i].first = info.initialValue;
            }
        }
        void instanceClear()
        {}
        
        void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openVerticalBox("RNBO");
            // Inputs controllers
            int ins = 0;
            for (int i = 0; i < fDSP.getNumParameters(); i++) {
                RNBO::ParameterInfo info;
                fDSP.getParameterInfo(i, &info);
                RNBO::ConstCharPointer name = fDSP.getParameterId(i);
                FAUSTFLOAT* zone = &fInputsZoneMap[ins];
                if (startWith(name, "RB_Button_")) {
                    fInputsZoneMap[ins] = 0;
                    ui_interface->addButton(name, zone);
                    fZoneFunMap.push_back(std::make_pair(zone, [=] (FAUSTFLOAT val) {
                        // std::cerr << "RB_Button_ " << val << std::endl;
                        fDSP.setParameterValue(i, val, 0);
                    }));
                    ins++;
                } else if (startWith(name, "RB_Checkbox_")) {
                    fInputsZoneMap[ins] = 0;
                    ui_interface->addCheckButton(name, zone);
                    fZoneFunMap.push_back(std::make_pair(zone, [=] (FAUSTFLOAT val) { fDSP.setParameterValue(i, val, 0); }));
                    ins++;
                } else if (startWith(name, "RB_HSlider_")) {
                    fInputsZoneMap[ins] = info.initialValue;
                    //double step = (info.max-info.min)/info.steps;
                    double step = 0;
                    ui_interface->addHorizontalSlider(name, zone, info.initialValue, info.min, info.max, step);
                    fZoneFunMap.push_back(std::make_pair(zone, [=] (FAUSTFLOAT val) { fDSP.setParameterValue(i, val, 0); }));
                    ins++;
                } else if (startWith(name, "RB_VSlider_")) {
                    fInputsZoneMap[ins] = info.initialValue;
                    //double step = (info.max-info.min)/info.steps;
                    double step = 0;
                    ui_interface->addVerticalSlider(name, zone, info.initialValue, info.min, info.max, step);
                    fZoneFunMap.push_back(std::make_pair(zone, [=] (FAUSTFLOAT val) { fDSP.setParameterValue(i, val, 0); }));
                    ins++;
                } else if (startWith(name, "RB_NEntry_")) {
                    fInputsZoneMap[ins] = info.initialValue;
                    //double step = (info.max-info.min)/info.steps;
                    double step = 0;
                    ui_interface->addNumEntry(name, zone, info.initialValue, info.min, info.max, step);
                    fZoneFunMap.push_back(std::make_pair(zone, [=] (FAUSTFLOAT val) { fDSP.setParameterValue(i, val, 0); }));
                    ins++;
                }
                // Outputs controllers
                // TODO
            }
            ui_interface->closeBox();
        }
        
        dsp* clone()
        {
            return new rnbo_dsp();
        }
    
        void metadata(Meta* m)
        {}
        
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Update control
            updateControls();
            // Render
            fDSP.process(inputs, fDSP.getNumInputChannels(), outputs, fDSP.getNumOutputChannels(), count);
        }
    
};

#endif

/************************** END rnbo-dsp.h **************************/
