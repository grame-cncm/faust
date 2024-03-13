/************************** BEGIN cmajorpatch-dsp.h *************************
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

#ifndef __cmajorpatch_dsp__
#define __cmajorpatch_dsp__

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <algorithm>
#include <libgen.h>

#include <cmajor/API/cmaj_Engine.h>
#include <cmajor/API/cmaj_Performer.h>

#include "faust/dsp/dsp.h"
#include "faust/misc.h"
#include "faust/midi/midi.h"
#include "faust/gui/UI.h"

class cmajor_dsp_factory;

/**
 * Faust wrapped JIT compiled Cmajor DSP
 */
class cmajorpatch_dsp : public dsp {
    
    private:
    
        cmajor_dsp_factory* fFactory;
         
        cmaj::Performer fPerformer;
        cmaj::EndpointDetailsList fEndpointInputs;
        cmaj::EndpointDetailsList fEndpointOutputs;
        int fNumInputs = 0;
        int fNumOutputs = 0;
        int fSampleRate;
        FAUSTFLOAT* fZoneMap;
        std::map<FAUSTFLOAT*, std::function<void(FAUSTFLOAT)>> fInputsFunMap;
        std::map<FAUSTFLOAT*, std::function<FAUSTFLOAT()>> fOutputsFunMap;
        
        // MIDI handling
        midi_handler* fMIDIHander;
    
        void updateInputControls()
        {
            for (const auto& it : fInputsFunMap) {
                it.second(*it.first);
            }
        }
        void updateOutputControls()
        {
            for (const auto& it : fOutputsFunMap) {
                *it.first = it.second();
            }
        }
    
    public:

        // Implemented later on
        cmajorpatch_dsp(cmajor_dsp_factory* factory, std::string& error_msg);
    
        virtual ~cmajorpatch_dsp()
        {
            delete [] fZoneMap;
        }
    
        void setMidiHandler(midi_handler* handler) { fMIDIHander = handler; }
        midi_handler* getMidiHandler() { return fMIDIHander; }

        virtual int getNumInputs()
        {
            return fNumInputs;
        }
    
        virtual int getNumOutputs()
        {
            return fNumOutputs;
        }
    
        virtual void buildUserInterface(UI* ui_interface);
   
        virtual int getSampleRate()
        {
            return fSampleRate;
        }
    
        void classInit(int sample_rate)
        {}
    
        // Implemented later on
        virtual void init(int sample_rate);
  
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }

        virtual void instanceConstants(int sample_rate)
        {}
    
        virtual void instanceResetUserInterface()
        {}
    
        virtual void instanceClear()
        {}
 
        // Implemented later on
        virtual cmajorpatch_dsp* clone();
    
        virtual void metadata(Meta* m) {}
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Faust wrapped Cmajor patches factory
 */
class cmajor_dsp_factory : public dsp_factory {
    
    protected:
    
        friend cmajorpatch_dsp;
    
        cmaj::Engine fEngine;
        std::vector<cmaj::EndpointHandle> fHandleInputs;
        std::vector<cmaj::EndpointHandle> fHandleOutputs;
    
        std::map<std::string, uint32_t> fHandleInputControls;
        std::map<std::string, uint32_t> fHandleOutputControls;
    
    public:
    
        cmajor_dsp_factory(const std::string& dsp_content, std::string& error_msg)
        {
            std::string filename = "/usr/local/lib/" + std::string(cmaj::Library::getDLLName());
            if (!cmaj::Library::initialise(filename)) {
                error_msg = "ERROR : cannot load CMajor library\n";
                throw std::bad_alloc();
            }
        
            fEngine = cmaj::Engine::create();
            cmaj::DiagnosticMessageList messages;
            cmaj::Program program;
            if (!program.parse(messages, "", dsp_content)) {
                error_msg = "ERROR : failed to parse : " + messages.toString() + "\n";
                throw std::bad_alloc();
            }
        
            cmaj::BuildSettings settings;
            settings.setFrequency(44100);       // Dummy value
            settings.setSessionID(123456);
            settings.setOptimisationLevel(4);   // -O4 to have fastmath like in Faust/LLVM
            fEngine.setBuildSettings(settings);
            
            if (!fEngine.load(messages, program, nullptr, nullptr)) {
                error_msg = "ERROR : failed to load : " + messages.toString() + "\n";
                throw std::bad_alloc();
            }

            /*
             std::cout << "Input endpoints:" << std::endl
                << fEngine.getInputEndpoints().getDescription() << std::endl
                << std::endl
                << "Output endpoints:" << std::endl
                << fEngine.getOutputEndpoints().getDescription() << std::endl
                << std::endl;
             */
        
            cmaj::EndpointDetailsList endpoint_inputs = fEngine.getInputEndpoints();
            cmaj::EndpointDetailsList endpoint_outputs = fEngine.getOutputEndpoints();
        
            // Get control ins/outs handle
            for (const auto& it : endpoint_inputs) {
                std::string name = it.endpointID.toString();
                if (choc::text::startsWith(name, "eventfCheckbox")
                    || choc::text::startsWith(name, "eventfButton")
                    || choc::text::startsWith(name, "eventfHslider")
                    || choc::text::startsWith(name, "eventfVslider")
                    || choc::text::startsWith(name, "eventfEntry")) {
                    fHandleInputControls[name] = fEngine.getEndpointHandle(it.endpointID);
                }
            }
            for (const auto& it : endpoint_outputs) {
                std::string name = it.endpointID.toString();
                if (choc::text::startsWith(name, "eventfHbargraph")
                    || choc::text::startsWith(name, "eventfVbargraph")) {
                    fHandleOutputControls[name] = fEngine.getEndpointHandle(it.endpointID);
                }
            }
        
            // Get audio ins/outs handle
            for (const auto& it : endpoint_inputs) {
                if (it.isInput && it.getNumAudioChannels() > 0) {
                    fHandleInputs.push_back(fEngine.getEndpointHandle(it.endpointID));
                }
            }
            for (const auto& it : endpoint_outputs) {
                if (!it.isInput && it.getNumAudioChannels() > 0) {
                    fHandleOutputs.push_back(fEngine.getEndpointHandle(it.endpointID));
                }
            }
        
            if (!fEngine.link(messages)) {
                std::cout << "Failed to link!" << std::endl
                << messages.toString() << std::endl;
                throw std::bad_alloc();
            }
        }
    
        virtual ~cmajor_dsp_factory() {}
        
        virtual std::string getName() {
            //return fDescription->name;
        }
        virtual std::string getSHAKey() { return ""; }
        virtual std::string getDSPCode() { return ""; }
        virtual std::string getCompileOptions() { return ""; }
        virtual std::vector<std::string> getLibraryList() { return {}; }
        virtual std::vector<std::string> getIncludePathnames() { return {}; }
        virtual std::vector<std::string> getWarningMessages() { return {}; }
    
        virtual cmajorpatch_dsp* createDSPInstance()
        {
            std::string error_msg;
            return new cmajorpatch_dsp(this, error_msg);
        }
    
        virtual void setMemoryManager(dsp_memory_manager* manager) {}
        virtual dsp_memory_manager* getMemoryManager() { return nullptr; };
    
};

cmajorpatch_dsp::cmajorpatch_dsp(cmajor_dsp_factory* factory, std::string& error_msg)
{
    fFactory = factory;
    fMIDIHander = nullptr;
    
    fPerformer = fFactory->fEngine.createPerformer();
    
    fEndpointInputs = fFactory->fEngine.getInputEndpoints();
    fEndpointOutputs = fFactory->fEngine.getOutputEndpoints();
    
    fZoneMap = new FAUSTFLOAT[fEndpointInputs.size() + fEndpointOutputs.size()];
    
    // Get ins/outs number
    for (const auto& it : fEndpointInputs) {
        fNumInputs += it.getNumAudioChannels();
    }
    for (const auto& it : fEndpointOutputs) {
        fNumOutputs += it.getNumAudioChannels();
    }
}

void cmajorpatch_dsp::init(int sample_rate)
{
    cmaj::BuildSettings settings;
    settings.setFrequency(sample_rate);
    settings.setSessionID(123456);
    fFactory->fEngine.setBuildSettings(settings);
}

void cmajorpatch_dsp::buildUserInterface(UI* ui_interface)
{
    ui_interface->openVerticalBox("CMajor");
    if (fFactory->fHandleInputControls.size() > 0) {
        ui_interface->openVerticalBox("Inputs");
    }
    int i = 0;
    // Inputs
    for (const auto& it : fEndpointInputs) {
        std::string name = it.endpointID.toString();
        uint32_t index = fFactory->fEngine.getEndpointHandle(name.c_str());
        if (choc::text::startsWith(name, "eventfCheckbox")) {
            std::string label = it.annotation["name"].toString();
            ui_interface->addCheckButton(label.c_str(), &fZoneMap[i]);
            fZoneMap[i] = 0;
            fInputsFunMap[&fZoneMap[i]] = [=](FAUSTFLOAT value) { fPerformer.addInputEvent(fFactory->fHandleInputControls[name], 0, value); };
            i++;
        } else if (choc::text::startsWith(name, "eventfButton")) {
            std::string label = it.annotation["name"].toString();
            ui_interface->addButton(label.c_str(), &fZoneMap[i]);
            fZoneMap[i] = 0;
            fInputsFunMap[&fZoneMap[i]] = [=](FAUSTFLOAT value) { fPerformer.addInputEvent(fFactory->fHandleInputControls[name], 0, value); };
            i++;
        } else if (choc::text::startsWith(name, "eventfHslider")) {
            std::string label = it.annotation["name"].toString();
            FAUSTFLOAT min_v = it.annotation["min"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT max_v = it.annotation["max"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT init = it.annotation["init"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT step = it.annotation["step"].getWithDefault<FAUSTFLOAT>(0);
            ui_interface->addHorizontalSlider(label.c_str(), &fZoneMap[i], init, min_v, max_v, step);
            fZoneMap[i] = init;
            fInputsFunMap[&fZoneMap[i]] = [=](FAUSTFLOAT value) { fPerformer.addInputEvent(fFactory->fHandleInputControls[name], 0, value); };
            i++;
        } else if (choc::text::startsWith(name, "eventfVslider")) {
            std::string label = it.annotation["name"].toString();
            FAUSTFLOAT min_v = it.annotation["min"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT max_v = it.annotation["max"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT init = it.annotation["init"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT step = it.annotation["step"].getWithDefault<FAUSTFLOAT>(0);
            ui_interface->addVerticalSlider(label.c_str(), &fZoneMap[i], init, min_v, max_v, step);
            fZoneMap[i] = init;
            fInputsFunMap[&fZoneMap[i]] = [=](FAUSTFLOAT value) { fPerformer.addInputEvent(fFactory->fHandleInputControls[name], 0, value); };
            i++;
        } else if (choc::text::startsWith(name, "eventfEntry")) {
            std::string label = it.annotation["name"].toString();
            FAUSTFLOAT min_v = it.annotation["min"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT max_v = it.annotation["max"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT init = it.annotation["init"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT step = it.annotation["step"].getWithDefault<FAUSTFLOAT>(0);
            ui_interface->addNumEntry(label.c_str(), &fZoneMap[i], init, min_v, max_v, step);
            fZoneMap[i] = init;
            fInputsFunMap[&fZoneMap[i]] = [=](FAUSTFLOAT value) { fPerformer.addInputEvent(fFactory->fHandleInputControls[name], 0, value); };
            i++;
        }
    }
    if (fFactory->fHandleInputControls.size() > 0) {
        ui_interface->closeBox();
    }
    // Outputs
    if (fFactory->fHandleOutputControls.size() > 0) {
        ui_interface->openVerticalBox("Outputs");
    }
    for (const auto& it : fEndpointOutputs) {
        std::string name = it.endpointID.toString();
        uint32_t index = fFactory->fEngine.getEndpointHandle(name.c_str());
        if (choc::text::startsWith(name, "eventfHbargraph")) {
            std::string label = it.annotation["name"].toString();
            FAUSTFLOAT min_v = it.annotation["min"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT max_v = it.annotation["max"].getWithDefault<FAUSTFLOAT>(0);
            ui_interface->addHorizontalBargraph(label.c_str(), &fZoneMap[i], min_v, max_v);
            fZoneMap[i] = 0;
            fOutputsFunMap[&fZoneMap[i]] = [=]() {
                FAUSTFLOAT value; fPerformer.copyOutputValue(fFactory->fHandleOutputControls[name], &value); return value;
            };
            i++;
        } else if (choc::text::startsWith(name, "eventfVbargraph")) {
            std::string label = it.annotation["name"].toString();
            FAUSTFLOAT min_v = it.annotation["min"].getWithDefault<FAUSTFLOAT>(0);
            FAUSTFLOAT max_v = it.annotation["max"].getWithDefault<FAUSTFLOAT>(0);
            ui_interface->addVerticalBargraph(label.c_str(), &fZoneMap[i], min_v, max_v);
            fZoneMap[i] = 0;
            fOutputsFunMap[&fZoneMap[i]] = [=]() {
                FAUSTFLOAT value; fPerformer.copyOutputValue(fFactory->fHandleOutputControls[name], &value); return value;
            };
            i++;
        }
    }
    if (fFactory->fHandleOutputControls.size() > 0) {
        ui_interface->closeBox();
    }
    ui_interface->closeBox();
}

void cmajorpatch_dsp::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    fPerformer.setBlockSize(count);
    
    // Copy audio inputs
    for (size_t chan = 0; chan < fFactory->fHandleInputs.size(); chan++) {
        fPerformer.setInputFrames(fFactory->fHandleInputs[chan], inputs[chan], count);
    }
    
    // Update input controls
    updateInputControls();
    
    // Render
    fPerformer.advance();
    
    // Copy audio outputs
    for (size_t chan = 0; chan < fFactory->fHandleOutputs.size(); chan++) {
        fPerformer.copyOutputFrames(fFactory->fHandleOutputs[chan], outputs[chan], count);
    }
    
    // Update output controls
    // updateOutputControls();
    
    /*
     // MIDI input handling
     if (fMIDIHander) {
            fRenderContext.numMIDIMessagesIn = fMIDIHander->recvMessages(reinterpret_cast<std::vector<MIDIMessage>*>(&fMIDIInputMessages));
            if (fRenderContext.numMIDIMessagesIn > 1024) {
            std::cerr << "MIDI input overflow\n";
        }
        fRenderContext.incomingMIDI = std::addressof(fMIDIInputMessages[0]);
        fRenderContext.outgoingMIDI = std::addressof(fMIDIOutputMessages[0]);
        fRenderContext.maximumMIDIMessagesOut = (uint32_t)fMIDIOutputMessages.size();
        fRenderContext.numMIDIMessagesOut = 0;
     } else {
        fRenderContext.incomingMIDI = nullptr;
        fRenderContext.incomingMIDI = nullptr;
        fRenderContext.numMIDIMessagesIn = 0;
     }
     */
    
    /*
     // MIDI output handling
     if (fMIDIHander && fRenderContext.numMIDIMessagesOut != 0) {
        if (fRenderContext.numMIDIMessagesOut > fRenderContext.maximumMIDIMessagesOut) {
        std::cerr << "MIDI output overflow\n";
     }
        int numMessagesOut = std::min(fRenderContext.numMIDIMessagesOut, fRenderContext.maximumMIDIMessagesOut);
        fMIDIHander->sendMessages(reinterpret_cast<std::vector<MIDIMessage>*>(&fMIDIOutputMessages), numMessagesOut);
     }
     */
}

// External API

cmajorpatch_dsp* cmajorpatch_dsp::clone()
{
    return fFactory->createDSPInstance();
}

cmajor_dsp_factory* getCmajorDSPFactoryFromSHAKey(const std::string& sha_key)
{
    return nullptr;
}

cmajor_dsp_factory* createCmajorDSPFactoryFromString(const std::string& name_app,
                                                  const std::string& dsp_content,
                                                  int argc, const char* argv[],
                                                  std::string& error_msg)
{
    try {
        return new cmajor_dsp_factory(dsp_content, error_msg);
    } catch (...) {
        if (error_msg == "") error_msg = "ERROR : createCmajorDSPFactoryFromString\n";
        return nullptr;
    }
}

cmajor_dsp_factory* createCmajorDSPFactoryFromFile(const std::string& filename,
                                               int argc, const char* argv[],
                                               std::string& error_msg)
{
    std::string base = basename((char*)filename.c_str());
    size_t pos = filename.find(".cmajor");
    
    if (pos != std::string::npos) {
        return createCmajorDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, error_msg);
    } else {
        error_msg = "ERROR : file extension is not the one expected (.cmajor expected)\n";
        return nullptr;
    }
}

bool deleteCmajorDSPFactory(cmajor_dsp_factory* factory)
{
    delete factory;
    return true;
}

#endif
/************************** END cmajorpatch-dsp.h **************************/
