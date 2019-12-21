/************************** BEGIN dummy-audio.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#ifndef __dummy_audio__
#define __dummy_audio__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <iomanip>

#ifdef USE_PTHREAD
#include <pthread.h>
#else
#include <thread>
#endif

#include "faust/dsp/dsp.h"
#include "faust/audio/audio.h"

#define BUFFER_TO_RENDER 10

class dummyaudio : public audio {
    
    private:
        
        dsp* fDSP;
        
        long fSampleRate;
        long fBufferSize;
        
        FAUSTFLOAT** fInChannel;
        FAUSTFLOAT** fOutChannel;
        
        int fNumInputs;
        int fNumOutputs;
        
        bool fRunning;
        
        int fRender;
        int fCount;
        int fSample;
        bool fManager;
        
    #ifdef USE_PTHREAD
        pthread_t fAudioThread;
        static void* run(void* ptr)
        {
            dummyaudio* audio = (dummyaudio*)ptr;
            audio->process();
            return 0;
        }
    #else
        static void run(dummyaudio* audio)
        {
            audio->process();
        }
        std::thread* fAudioThread = 0;
    #endif
        
        void process()
        {
            while (fRunning && (--fRender > 0)) {
                if (fSample > 0) { std::cout << "Render one buffer\n"; }
                render();
            }
            fRunning = false;
        }
        
    public:
        
        dummyaudio(int sr, int bs, int count = BUFFER_TO_RENDER, int sample = -1, bool manager = false)
        :fSampleRate(sr), fBufferSize(bs),
        fInChannel(nullptr), fOutChannel(nullptr),
        fNumInputs(-1), fNumOutputs(-1),
        fRender(0), fCount(count),
        fSample(sample), fManager(manager)
        {}
        
        dummyaudio(int count = BUFFER_TO_RENDER)
        :fSampleRate(48000), fBufferSize(512),
        fInChannel(nullptr), fOutChannel(nullptr),
        fNumInputs(-1), fNumOutputs(-1),
        fRender(0), fCount(count),
        fSample(512), fManager(false)
        {}
        
        virtual ~dummyaudio()
        {
            for (int i = 0; i < fNumInputs; i++) {
                delete[] fInChannel[i];
            }
            for (int i = 0; i < fNumOutputs; i++) {
                delete[] fOutChannel[i];
            }
            delete [] fInChannel;
            delete [] fOutChannel;
        }
        
        virtual bool init(const char* name, dsp* dsp)
        {
            fDSP = dsp;
            
            // To be used in destructor
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();
            
            fInChannel = new FAUSTFLOAT*[fNumInputs];
            fOutChannel = new FAUSTFLOAT*[fNumOutputs];
            
            for (int i = 0; i < fNumInputs; i++) {
                fInChannel[i] = new FAUSTFLOAT[fBufferSize];
                memset(fInChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            for (int i = 0; i < fNumOutputs; i++) {
                fOutChannel[i] = new FAUSTFLOAT[fBufferSize];
                memset(fOutChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            
            if (fManager) {
                // classInit is called elsewhere with a custom memory manager
                fDSP->instanceInit(fSampleRate);
            } else {
                fDSP->init(fSampleRate);
            }
            
            return true;
        }
        
        virtual bool start()
        {
            fRender = fCount;
            fRunning = true;
            if (fCount == INT_MAX) {
            #ifdef USE_PTHREAD
                if (pthread_create(&fAudioThread, 0, run, this) != 0) {
                    fRunning = false;
                }
            #else
                fAudioThread = new std::thread (dummyaudio::run, this);
            #endif
                return fRunning;
            } else {
                process();
                return true;
            }
        }
        
        virtual void stop()
        {
            if (fRunning) {
                fRunning = false;
            #ifdef USE_PTHREAD
                pthread_join(fAudioThread, 0);
            #else
                fAudioThread->join();
                delete fAudioThread;
                fAudioThread = 0;
            #endif
            }
        }
        
        void render()
        {
            fDSP->compute(fBufferSize, fInChannel, fOutChannel);
            if (fNumInputs > 0) {
                for (int frame = 0; frame < fSample; frame++) {
                    std::cout << std::fixed << std::setprecision(6) << "sample in " << fInChannel[0][frame] << std::endl;
                }
            }
            if (fNumOutputs > 0) {
                for (int frame = 0; frame < fSample; frame++) {
                    std::cout << std::fixed << std::setprecision(6) << "sample out " << fOutChannel[0][frame] << std::endl;
                }
            }
        }
        
        virtual int getBufferSize() { return fBufferSize; }
        virtual int getSampleRate() { return fSampleRate; }
        
        virtual int getNumInputs() { return fNumInputs; }
        virtual int getNumOutputs() { return fNumOutputs; }
    
};

#endif
/**************************  END  dummy-audio.h **************************/
