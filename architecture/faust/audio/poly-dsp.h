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

#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/dsp.h"

struct mydsp_voice : public MapUI {
    
    mydsp fVoice;
    int fNote;
    
    mydsp_voice(int sample_rate)
    {
        fVoice.init(sample_rate);
        fVoice.buildUserInterface(this);
        fNote = -1;
    }
};

struct mydsp_poly
{
    std::string fJSON;
    
    mydsp_voice** fVoiceTable;
    
    std::string fGateLabel;
    std::string fGainLabel;
    std::string fFreqLabel;
    
    int fMaxPolyphony;
    
    FAUSTFLOAT** fNoteOutputs;
    int fNumOutputs;
    
    inline void mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer) 
    {
        for (int i = 0; i < fNumOutputs; i++) {
            float* mixChannel = mixBuffer[i];
            float* outChannel = outputBuffer[i];
            for (int j = 0; j < count; j++) {
                mixChannel[j] += outChannel[j];
            }
        }
    }
    
    inline float midiToFreq(int note) 
    {
        return 440.0f * powf(2.0f, ((float(note))-69.0f)/12.0f);
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
        return -1;
    }
    
    mydsp_poly(int sample_rate, int buffer_size, int max_polyphony)
    {
        fMaxPolyphony = max_polyphony;
        fVoiceTable = new mydsp_voice*[max_polyphony];
        
        // Init it with supplied sample_rate 
        for (int i = 0; i < fMaxPolyphony; i++) {
            fVoiceTable[i] = new mydsp_voice(sample_rate);
        }
        
        // Init audio output buffers
        fNumOutputs = fVoiceTable[0]->fVoice.getNumOutputs();
        fNoteOutputs = new FAUSTFLOAT*[fNumOutputs];
        for (int i = 0; i < fNumOutputs; i++) {
            fNoteOutputs[i] = new FAUSTFLOAT[buffer_size];
        }
        
        // Creates JSON
        JSONUI builder(fVoiceTable[0]->fVoice.getNumInputs(), fVoiceTable[0]->fVoice.getNumOutputs());
        mydsp::metadata(&builder);
        fVoiceTable[0]->fVoice.buildUserInterface(&builder);
        fJSON = builder.JSON();
        
        // Keep gain, freq and gate labels
        std::map<std::string, FAUSTFLOAT*>::iterator it;
        
        for (it = fVoiceTable[0]->getMap().begin(); it != fVoiceTable[0]->getMap().end(); it++) {
            std::string label = (*it).first;
            if (label.find("gate") != std::string::npos) {
                fGateLabel = label;
            } else if (label.find("freq") != std::string::npos) {
                fFreqLabel = label;
            } else if (label.find("gain") != std::string::npos) {
                fGainLabel = label;
            }
        }
    }
    
    virtual ~mydsp_poly()
    {
        for (int i = 0; i < fNumOutputs; i++) {
            delete[] fNoteOutputs[i];
        }
        delete[] fNoteOutputs;
        
        for (int i = 0; i < fMaxPolyphony; i++) {
            delete fVoiceTable[i];
        }
        delete [] fVoiceTable;
    }
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        // First clear the outputs
        clearOutput(count, outputs);
          
        // Then mix all voices
        for (int i = 0; i < fMaxPolyphony; i++) {
            fVoiceTable[i]->fVoice.compute(count, inputs, fNoteOutputs);
            mixVoice(count, fNoteOutputs, outputs);
        }
    }
    
    int getNumInputs()
    {
        return fVoiceTable[0]->fVoice.getNumInputs();
    }
    
    int getNumOutputs()
    {
        return fVoiceTable[0]->fVoice.getNumOutputs();
    }
    
    void keyOn(int channel, int pitch, int velocity)
    {
        int voice = getVoice(-1);  // Gets a free voice
        if (voice >= 0) {
            printf("noteOn %d\n", voice);
            fVoiceTable[voice]->setValue(fFreqLabel, midiToFreq(pitch));
            fVoiceTable[voice]->setValue(fGainLabel, float(velocity)/127.f);
            fVoiceTable[voice]->setValue(fGateLabel, 1.0f);
            fVoiceTable[voice]->fNote = pitch;
        } else {
            printf("No more free voice...\n");
        }
    }
    
    void keyOff(int channel, int pitch)
    {
        int voice = getVoice(pitch);
        if (voice >= 0) {
            printf("noteOff %d\n", voice);
            fVoiceTable[voice]->setValue(fGateLabel, 0.0f);
            fVoiceTable[voice]->fNote = -1;
        } else {
            printf("Playing voice not found...\n");
        }
    }
    
    void pitchBend(int refPitch, float pitch)
    {
    	int voice = getVoice(refPitch);
        if (voice >= 0) {
        	fVoiceTable[voice]->setValue(fFreqLabel, midiToFreq(pitch));
        }
        else {
        	printf("Playing voice not found...\n");
        }
    }
    
    void ctrlChange(int channel, int ctrl, int value)
    {}
    
    void pitchWheel(int channel, int pitchWheel)
    {}
    
    const char* getJSON()
    {
        return fJSON.c_str();
    }
    
    void setValue(const char* path, float value)
    {
        for (int i = 0; i < fMaxPolyphony; i++) {
            fVoiceTable[i]->setValue(path, value);
        }
    }
    
    float getValue(const char* path)
    {
        return fVoiceTable[0]->getValue(path);
    }
    
};
   
extern "C" {
    
    // C like API
    mydsp_poly* mydsp_poly_constructor(int sample_rate, int buffer_size, int max_polyphony) 
    {
         return new mydsp_poly(sample_rate, buffer_size, max_polyphony);
    }

    void mydsp_poly_destructor(mydsp_poly* n) 
    {
        delete n;
    }

    const char* mydsp_poly_getJSON(mydsp_poly* n)
    {
        return n->getJSON();
    }
  
    void mydsp_poly_compute(mydsp_poly* n, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        n->compute(count, inputs, outputs);
    }

    int mydsp_poly_getNumInputs(mydsp_poly* n)
    {
        return n->getNumInputs();
    }

    int mydsp_poly_getNumOutputs(mydsp_poly* n)
    {
        return n->getNumOutputs();
    }

    void mydsp_poly_keyOn(mydsp_poly* n, int channel, int pitch, int velocity)
    {
        n->keyOn(channel, pitch, velocity);
    }

    void mydsp_poly_keyOff(mydsp_poly* n, int channel, int pitch)
    {
        n->keyOff(channel, pitch);
    }
    
    void mydsp_poly_ctrlChange(mydsp_poly* n, int channel, int ctrl, int value)
    {
        n->ctrlChange(channel, ctrl, value);
    }
    
    void mydsp_poly_pitchWheel(mydsp_poly* n, int channel, int pitchWheel)
    {
        n->pitchWheel(channel, pitchWheel);
    }
    
    void mydsp_poly_setValue(mydsp_poly* n, const char* path, float value)
    {
        n->setValue(path, value);
    }

    float mydsp_poly_getValue(mydsp_poly* n, const char* path)
    {
        return n->getValue(path);
    }
        
}

#endif
