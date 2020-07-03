/************************** BEGIN soul-cpp-dsp.h **************************/
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
 ************************************************************************/

#ifndef __soul_cpp_dsp__
#define __soul_cpp_dsp__

#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <algorithm>
#include <assert.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/JSONUIDecoder.h"

#include "souldsp.h"

/**
* Faust wrapped C++ SOUL DSP
*/

class soul_cpp_dsp : public dsp {
    
    private:

        JSONUITemplatedDecoder* fDecoder;
        souldsp fDSP;
        int fSampleRate;
    
        FAUSTFLOAT* fZoneMap;
        std::map <FAUSTFLOAT*, std::function<void(float)> > fZoneFunMap;
    
        std::string unquote(const std::string& str)
        {
            return (str[0] == '"') ? str.substr(1, str.size() - 2) : str;
        }
    
        bool startWith(const std::string& str, const std::string& prefix)
        {
            return (str.substr(0, prefix.size()) == prefix);
        }
  
        void updateControls()
        {
            for (auto& it : fZoneFunMap) {
                it.second(*it.first);
            }
        }
    
    public:
    
        soul_cpp_dsp()
        {
            fDecoder = nullptr;
            fSampleRate = 0;
            
            /*
            std::vector<souldsp::EndpointDetails> endpoints = fDSP.getInputEndpoints();
            assert(std::string(endpoints[0].name) == "eventbuildUserInterface");
            */
            
            std::vector<souldsp::ParameterProperties> properties = fDSP.getParameterProperties();
            fZoneMap = new FAUSTFLOAT[properties.size()];
        }
    
        virtual ~soul_cpp_dsp()
        {
            delete fDecoder;
            delete [] fZoneMap;
        }
    
        virtual int getNumInputs()
        {
            return fDSP.numAudioInputChannels;
        }
    
        virtual int getNumOutputs()
        {
            return fDSP.numAudioOutputChannels;
        }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            //fDecoder->buildUserInterface(ui_interface);
            
            std::vector<souldsp::ParameterProperties> prop = fDSP.getParameterProperties();
            for (int i= 0; i < prop.size(); i++) {
                if (prop[i].isBoolean) {
                    if (startWith(prop[i].UID, "eventfCheckbox")) {
                        ui_interface->addCheckButton(prop[i].name, &fZoneMap[i]);
                    } else {
                        ui_interface->addButton(prop[i].name, &fZoneMap[i]);
                    }
                    fZoneMap[i] = 0;
                    fZoneFunMap[&fZoneMap[i]] = prop[i].setValue;
                } else {
                    ui_interface->addNumEntry(prop[i].name, &fZoneMap[i], prop[i].initialValue, prop[i].minValue, prop[i].maxValue, prop[i].step);
                    fZoneMap[i] = prop[i].initialValue;
                    fZoneFunMap[&fZoneMap[i]] = prop[i].setValue;
                }
            }
        }
    
        virtual int getSampleRate()
        {
            return fSampleRate;
        }
    
        virtual void init(int sample_rate)
        {
            fSampleRate = sample_rate;
            fDSP.init(double(sample_rate), 0);
        }
    
        virtual void instanceInit(int sample_rate)
        {
            fSampleRate = sample_rate;
            // classInit has to be called for each instance since the tables are actually not shared between instances
            fDSP.addInputEvent_eventclassInit(sample_rate);
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            fSampleRate = sample_rate;
            fDSP.addInputEvent_eventinstanceConstants(sample_rate);
        }
    
        virtual void instanceResetUserInterface()
        {
            fDSP.addInputEvent_eventinstanceResetUserInterface(0);
        }
    
        virtual void instanceClear()
        {
            fDSP.addInputEvent_eventinstanceClear(0);
        }
    
        virtual soul_cpp_dsp* clone()
        {
            return new soul_cpp_dsp();
        }
    
        virtual void metadata(Meta* m)
        {
            //fDecoder->metadata(m);
        }
    
        template <typename REAL>
        void computeAux(int count, REAL** inputs, REAL** outputs)
        {
            // Prepare buffers
            souldsp::RenderContext<REAL> context;
            if constexpr (souldsp::numAudioInputChannels > 0) {
                for (int chan = 0; chan < souldsp::numAudioInputChannels; chan++) {
                    context.inputChannels[chan] = inputs[chan];
                }
            }
            
            if (souldsp::numAudioOutputChannels > 0) {
                for (int chan = 0; chan < souldsp::numAudioOutputChannels; chan++) {
                    context.outputChannels[chan] = outputs[chan];
                }
            }
            
            // Update control
            updateControls();
            
            // Render
            context.numFrames = count;
            fDSP.render(context);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            computeAux<FAUSTFLOAT>(count, inputs, outputs);
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            computeAux<FAUSTFLOAT>(count, inputs, outputs);
        }
   
};

#endif

/**************************  END  soul-cpp-dsp.h **************************/
