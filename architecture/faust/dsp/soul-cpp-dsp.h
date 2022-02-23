/************************** BEGIN soul-cpp-dsp.h **************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
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

// Generated with 'soul generate --cpp foo.soul --output=souldsp.h'
#include "souldsp.h"

/**
* Faust wrapped C++ SOUL DSP
*/

class soul_cpp_dsp : public dsp {
    
    private:

        JSONUIDecoderBase* fDecoder;
        souldsp fDSP;
    
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
            for (const auto& it : fZoneFunMap) {
                it.second(*it.first);
            }
        }
    
    public:
    
        soul_cpp_dsp()
        {
            fDecoder = nullptr;
            souldsp::ParameterList parameters = fDSP.createParameterList();
            fZoneMap = new FAUSTFLOAT[parameters.size()];
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
            
            souldsp::ParameterList parameters = fDSP.createParameterList();
            for (int i = 0; i < parameters.size(); i++) {
                souldsp::Parameter& param = parameters[i];
                souldsp::ParameterProperties& prop = param.properties;
                if (prop.isBoolean) {
                    if (startWith(prop.UID, "eventfCheckbox")) {
                        ui_interface->addCheckButton(prop.name, &fZoneMap[i]);
                    } else if (startWith(prop.UID, "eventfButton")) {
                        ui_interface->addButton(prop.name, &fZoneMap[i]);
                    }
                    fZoneMap[i] = 0;
                    fZoneFunMap[&fZoneMap[i]] = param.applyValue;
                } else if (startWith(prop.UID, "eventfHslider")) {
                    ui_interface->addHorizontalSlider(prop.name, &fZoneMap[i], prop.initialValue, prop.minValue, prop.maxValue, prop.step);
                    fZoneMap[i] = prop.initialValue;
                    fZoneFunMap[&fZoneMap[i]] = param.applyValue;
                } else if (startWith(prop.UID, "eventfVslider")) {
                    ui_interface->addVerticalSlider(prop.name, &fZoneMap[i], prop.initialValue, prop.minValue, prop.maxValue, prop.step);
                    fZoneMap[i] = prop.initialValue;
                    fZoneFunMap[&fZoneMap[i]] = param.applyValue;
                } else if (startWith(prop.UID, "eventfEntry")) {
                    ui_interface->addNumEntry(prop.name, &fZoneMap[i], prop.initialValue, prop.minValue, prop.maxValue, prop.step);
                    fZoneMap[i] = prop.initialValue;
                    fZoneFunMap[&fZoneMap[i]] = param.applyValue;
                } else if (startWith(prop.UID, "eventfVbargraph")) {
                    ui_interface->addHorizontalBargraph(prop.name, &fZoneMap[i], prop.minValue, prop.maxValue);
                    fZoneMap[i] = 0;
                } else if (startWith(prop.UID, "eventfHbargraph")) {
                    ui_interface->addVerticalBargraph(prop.name, &fZoneMap[i], prop.minValue, prop.maxValue);
                    fZoneMap[i] = 0;
                }
            }
        }
    
        virtual int getSampleRate()
        {
            return fDSP.sampleRate;
        }
    
        virtual void init(int sample_rate)
        {
            fDSP.init(double(sample_rate), 0);
        }
    
        virtual void instanceInit(int sample_rate)
        {
            fDSP.sampleRate = double(sample_rate);
            // classInit has to be called for each instance since the tables are actually not shared between instances
            fDSP.addInputEvent_eventclassInit(sample_rate);
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            fDSP.sampleRate = double(sample_rate);
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
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Prepare buffers
            souldsp::RenderContext<FAUSTFLOAT> context;
            if (souldsp::numAudioInputChannels > 0) {
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
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
   
};

#endif

/************************** END soul-cpp-dsp.h **************************/
