/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/
/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <ostream>
#include <sstream>

#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/dsp.h"
#include "faust/midi/midi.h"

#define kFreeVoice        -2
#define kReleaseVoice     -1

#define VOICE_STOP_LEVEL  0.001
#define MIX_BUFFER_SIZE   16384

// ends_with(<str>,<end>) : returns true if <str> ends with <end>
static bool ends_with(std::string const& str, std::string const& end)
{
	unsigned int l1 = str.length();
	unsigned int l2 = end.length();
    return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
}

// One voice of polyphony
struct dsp_voice : public MapUI, public dsp {
       
    int fNote;

    dsp_voice()
    {
        fNote = kFreeVoice;
    }
    
    virtual void metadata(Meta* meta) = 0;
 
};

struct voice_factory {

    virtual dsp_voice* create() = 0;
};

struct mydsp_voice : public dsp_voice {

    mydsp fVoice;
     
    mydsp_voice():dsp_voice()
    {
        fVoice.buildUserInterface(this);
    }
    
    virtual int getNumInputs() { return fVoice.getNumInputs(); }
    virtual int getNumOutputs() { return fVoice.getNumOutputs(); }
    virtual void buildUserInterface(UI* ui_interface) { fVoice.buildUserInterface(ui_interface); }
    virtual void init(int samplingRate) { fVoice.init(samplingRate); }
    virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fVoice.compute(len, inputs, outputs); }

    virtual void metadata(Meta* meta) { mydsp::metadata(meta); }

};

struct mydsp_voice_factory : public voice_factory {

    virtual dsp_voice* create() { return new mydsp_voice(); }
};

// Polyphonic DSP
class mydsp_poly : public dsp, public midi
{

    private:
  
        std::string fJSON;
        
        dsp_voice** fVoiceTable;
        
        std::string fGateLabel;
        std::string fGainLabel;
        std::string fFreqLabel;
        
        int fMaxPolyphony;
        bool fVoiceControl;
        
        FAUSTFLOAT** fMixBuffer;
        int fNumOutputs;
        
        inline FAUSTFLOAT mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer) 
        {
            FAUSTFLOAT level = 0;
            // Normalize sample by the max polyphony (as in vst.cpp file)
            FAUSTFLOAT gain_level = 1./sqrt(fMaxPolyphony);
            for (int i = 0; i < fNumOutputs; i++) {
                FAUSTFLOAT* mixChannel = mixBuffer[i];
                FAUSTFLOAT* outChannel = outputBuffer[i];
                for (int j = 0; j < count; j++) {
                    level = std::max(level, (FAUSTFLOAT)fabs(outChannel[j]));
                    mixChannel[j] += outChannel[j] * gain_level;
                }
            }
            return level;
        }
        
        inline double midiToFreq(double note) 
        {
            return 440.0 * pow(2.0, (note-69.0)/12.0);
        }
        
        inline void clearOutput(int count, FAUSTFLOAT** mixBuffer) 
        {
            for (int i = 0; i < fNumOutputs; i++) {
                memset(mixBuffer[i], 0, count * sizeof(FAUSTFLOAT));
            }
        }
        
        inline int getVoice(int note)
        {
            for (int i = 0; i < fMaxPolyphony; i++) {
                if (fVoiceTable[i]->fNote == note) return i;
            }
            return kReleaseVoice;
        }
        
        inline void init(int max_polyphony, voice_factory* factory)
        {
            fMaxPolyphony = max_polyphony;
            fVoiceTable = new dsp_voice*[fMaxPolyphony];
            
             // Init it with supplied sample_rate 
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i] = factory->create();
            }
            
            // Init audio output buffers
            fNumOutputs = fVoiceTable[0]->getNumOutputs();
            fMixBuffer = new FAUSTFLOAT*[fNumOutputs];
            for (int i = 0; i < fNumOutputs; i++) {
                fMixBuffer[i] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }
        }
    
    public: 
    
        mydsp_poly(int max_polyphony, bool control, int buffer_size = 8192)  // Second argument to remove ASAP
        {
            fVoiceControl = control;
            mydsp_voice_factory factory;
            init(max_polyphony, &factory);
        }
        
        mydsp_poly(int max_polyphony, int buffer_size = 8192)  // Second argument to remove ASAP
        {
            fVoiceControl = false;
            mydsp_voice_factory factory;
            init(max_polyphony, &factory);
        }
          
        virtual ~mydsp_poly()
        {
            for (int i = 0; i < fNumOutputs; i++) {
                delete[] fMixBuffer[i];
            }
            delete[] fMixBuffer;
            
            for (int i = 0; i < fMaxPolyphony; i++) {
                delete fVoiceTable[i];
            }
            delete[] fVoiceTable;
        }
        
        void init(int sample_rate) 
        {
            // Init voices
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i]->init(sample_rate);
            }
            
            // Creates JSON
            JSONUI builder(fVoiceTable[0]->getNumInputs(), fVoiceTable[0]->getNumOutputs());
            fVoiceTable[0]->metadata(&builder);
            builder.openTabBox("Polyphonic instrument");
            for (int i = 0; i < fMaxPolyphony; i++) {
                std::stringstream voice; voice << "Voice" << i;
                builder.openHorizontalBox(voice.str().c_str());
                fVoiceTable[i]->buildUserInterface(&builder);
                builder.closeBox();
            }
            builder.closeBox();
            fJSON = builder.JSON();
            
            // Keep gain, freq and gate labels
            std::map<std::string, FAUSTFLOAT*>::iterator it;
            
            for (it = fVoiceTable[0]->getMap().begin(); it != fVoiceTable[0]->getMap().end(); it++) {
                std::string label = (*it).first;
                if (ends_with(label, "/gate")) {
                    fGateLabel = label;
                } else if (ends_with(label, "/freq")) {
                    fFreqLabel = label;
                } else if (ends_with(label, "/gain")) {
                    fGainLabel = label;
                }
            }
        }
        
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            assert(count < MIX_BUFFER_SIZE);
            
            // First clear the outputs
            clearOutput(count, outputs);
            
            if (fVoiceControl) {
                // Mix all playing voices
                for (int i = 0; i < fMaxPolyphony; i++) {
                    if (fVoiceTable[i]->fNote != kFreeVoice) {
                        fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                        FAUSTFLOAT level = mixVoice(count, fMixBuffer, outputs);
                        if ((level < VOICE_STOP_LEVEL) && (fVoiceTable[i]->fNote == kReleaseVoice)) {
                            fVoiceTable[i]->fNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (int i = 0; i < fMaxPolyphony; i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, outputs);
                }
            }
        }
        
        int getNumInputs()
        {
            return fVoiceTable[0]->getNumInputs();
        }
        
        int getNumOutputs()
        {
            return fVoiceTable[0]->getNumOutputs();
        }
        
        void buildUserInterface(UI* ui_interface) 
        {   
            if (fMaxPolyphony > 1) {
                ui_interface->openTabBox("Polyphonic instrument");
                for (int i = 0; i < fMaxPolyphony; i++) {
                    std::stringstream voice; voice << "Voice" << i;
                    ui_interface->openHorizontalBox(voice.str().c_str());
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
                ui_interface->closeBox();
            } else {
                fVoiceTable[0]->buildUserInterface(ui_interface);
            }
        }
        
        // Pure MIDI control
        void keyOn(int channel, int pitch, int velocity)
        {
            int voice = getVoice(kFreeVoice);
            if (voice == kReleaseVoice) voice = getVoice(kReleaseVoice);  // Gets a free voice
            
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(fFreqLabel, midiToFreq(pitch));
                fVoiceTable[voice]->setValue(fGainLabel, float(velocity)/127.f);
                fVoiceTable[voice]->setValue(fGateLabel, 1.0f);
                fVoiceTable[voice]->fNote = pitch;
            } else {
                printf("No more free voice...\n");
            }
        }
        
        void keyOff(int channel, int pitch, int velocity = 127)
        {
            int voice = getVoice(pitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(fGainLabel, float(velocity)/127.f);
                fVoiceTable[voice]->setValue(fGateLabel, 0.0f);
                fVoiceTable[voice]->fNote = kReleaseVoice;
            } else {
                printf("Playing voice not found...\n");
            }
        }
        
        void pitchWheel(int channel, int wheel)
        {}
        
        void ctrlChange(int channel, int ctrl, int value)
        {}
        
        void progChange(int channel, int pgm)
        {}

        // Additional API
        void allNotesOff()
        {
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i]->setValue(fGateLabel, 0.0f);
                fVoiceTable[i]->fNote = kReleaseVoice;
            }
        }
        
        void pitchBend(int channel, int refPitch, float pitch)
        {
            int voice = getVoice(refPitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(fFreqLabel, midiToFreq(pitch));
            } else {
                printf("Playing voice not found...\n");
            }
        }
        
        void setValue(const char* path, float value)
        {
            for (int i = 0; i < fMaxPolyphony; i++) {
                fVoiceTable[i]->setValue(path, value);
            }
        }
        
        void setValue(const char* path, int pitch, float value)
        {
            int voice = getVoice(pitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(path, value);
            }
        }
        
        float getValue(const char* path)
        {
            return fVoiceTable[0]->getValue(path);
        }
        
        void setVoiceGain(int pitch, float value)
        {   
            int voice = getVoice(pitch);
            if (voice >= 0) {
                fVoiceTable[voice]->setValue(fGainLabel, value);
            }
        }
        
        const char* getJSON()
        {
            return fJSON.c_str();
        }
    
};
   
extern "C" {
    
    // C like API
    mydsp_poly* mydsp_poly_constructor(int sample_rate, int max_polyphony) 
    {
        mydsp_poly* poly = new mydsp_poly(max_polyphony);
        if (poly) poly->init(sample_rate);
        return poly;
    }

    void mydsp_poly_destructor(mydsp_poly* poly) 
    {
        delete poly;
    }

    const char* mydsp_poly_getJSON(mydsp_poly* poly)
    {
        return poly->getJSON();
    }
  
    void mydsp_poly_compute(mydsp_poly* poly, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        poly->compute(count, inputs, outputs);
    }

    int mydsp_poly_getNumInputs(mydsp_poly* poly)
    {
        return poly->getNumInputs();
    }

    int mydsp_poly_getNumOutputs(mydsp_poly* poly)
    {
        return poly->getNumOutputs();
    }

    void mydsp_poly_keyOn(mydsp_poly* poly, int channel, int pitch, int velocity)
    {
        poly->keyOn(channel, pitch, velocity);
    }

    void mydsp_poly_keyOff(mydsp_poly* poly, int channel, int pitch, int velocity)
    {
        poly->keyOff(channel, pitch, velocity);
    }
    
    void mydsp_poly_allNotesOff(mydsp_poly* poly)
    {
        poly->allNotesOff();
    }
    
    void mydsp_poly_ctrlChange(mydsp_poly* poly, int channel, int ctrl, int value)
    {
        poly->ctrlChange(channel, ctrl, value);
    }
    
    void mydsp_poly_pitchWheel(mydsp_poly* poly, int channel, int wheel)
    {
        poly->pitchWheel(channel, wheel);
    }
    
    void mydsp_poly_pitchBend(mydsp_poly* poly, int channel, int refPitch, float pitch)
    {
        poly->pitchBend(channel, refPitch, pitch);
    }
    
    void mydsp_poly_setValue(mydsp_poly* poly, const char* path, float value)
    {
        poly->setValue(path, value);
    }

    float mydsp_poly_getValue(mydsp_poly* poly, const char* path)
    {
        return poly->getValue(path);
    }
        
}

#endif
