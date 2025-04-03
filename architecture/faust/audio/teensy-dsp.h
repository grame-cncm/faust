/************************** BEGIN teensyaudio.h **************************
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
 ************************************************************************/

#ifndef __teensyaudio__
#define __teensyaudio__

#include <set>
#include <utility>
#include <string.h> // for memset

#include "faust/dsp/dsp.h"

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#define MULT_16 32767
#define DIV_16 0.0000305185

// Not needed
// unsigned __exidx_start;
// unsigned __exidx_end;

// we require macro declarations
#ifndef FAUST_UIMACROS
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)
#endif

class teensyaudio : public AudioStream, public audio {
    
    private:
    
        float** fInChannel;
        float** fOutChannel;
        bool fRunning;
        ::dsp* fDSP;
    
        template <int INPUTS, int OUTPUTS>
        void updateImp()
        {
            if (INPUTS > 0) {
                audio_block_t* inBlock[INPUTS];
                for (int channel = 0; channel < INPUTS; channel++) {
                    inBlock[channel] = receiveReadOnly(channel);
                    if (inBlock[channel]) {
                        for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                            int16_t val = inBlock[channel]->data[i];
                            fInChannel[channel][i] = val*DIV_16;
                        }
                        release(inBlock[channel]);
                    } else {
                        memset(fInChannel[channel], 0, AUDIO_BLOCK_SAMPLES * sizeof(float));
                    }
                }
            }
            
            fDSP->compute(AUDIO_BLOCK_SAMPLES, fInChannel, fOutChannel);
            
            audio_block_t* outBlock[OUTPUTS];
            for (int channel = 0; channel < OUTPUTS; channel++) {
                outBlock[channel] = allocate();
                if (outBlock[channel]) {
                    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                        int16_t val = fOutChannel[channel][i]*MULT_16;
                        outBlock[channel]->data[i] = val;
                    }
                    transmit(outBlock[channel], channel);
                    release(outBlock[channel]);
                }
            }
        }
    
        // Check running state
        void update(void) { if (fRunning) updateImp<FAUST_INPUTS, FAUST_OUTPUTS>(); }
    
    public:
    
        teensyaudio():AudioStream(FAUST_INPUTS, new audio_block_t*[FAUST_INPUTS]), fRunning(false), fDSP(nullptr)
        {}
    
        virtual ~teensyaudio()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete[] fInChannel[i];
            }
            delete [] fInChannel;
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete[] fOutChannel[i];
            }
            delete [] fOutChannel;
        }

        virtual bool init(const char* name, ::dsp* dsp)
        {
            fDSP = dsp;
            fDSP->init(AUDIO_SAMPLE_RATE_EXACT);
            
            if (fDSP->getNumInputs() > 0) {
                fInChannel = new float*[fDSP->getNumInputs()];
                for (int i = 0; i < fDSP->getNumInputs(); i++) {
                    fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
                }
            } else {
                fInChannel = NULL;
            }
            
            if (fDSP->getNumOutputs() > 0) {
                fOutChannel = new float*[fDSP->getNumOutputs()];
                for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                    fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
                }
            } else {
                fOutChannel = NULL;
            }
            return true;
        }
    
        virtual bool start()
        {
            fRunning = true;
            return fRunning;
        }
    
        virtual void stop()
        {
            fRunning = false;
        }
    
        virtual int getBufferSize() { return AUDIO_BLOCK_SAMPLES; }
        virtual int getSampleRate() { return AUDIO_SAMPLE_RATE_EXACT; }

        virtual int getNumInputs() { return 2; }
        virtual int getNumOutputs() { return 2; }
    
        // Returns the average proportion of available CPU being spent inside the audio callbacks (between 0 and 1.0).
        virtual float getCPULoad() { return 0.f; }
    
};
					
#endif
/**************************  END  teensyaudio.h **************************/
