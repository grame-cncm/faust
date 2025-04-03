/************************** BEGIN dummy-audio.h *************************
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

struct dummyaudio_base : public audio {
    
    virtual void render() = 0;
};

template <typename REAL>
class dummyaudio_real : public dummyaudio_base {
    
    private:
        
        ::dsp* fDSP;
        
        int fSampleRate;
        int fBufferSize;
        
        REAL** fInChannel;
        REAL** fOutChannel;
        
        int fNumInputs;
        int fNumOutputs;
        
        bool fRunning;
        
        int fRender;
        int fCount;
        int fSample;
        bool fManager;
        bool fExit;
    
        void runAux()
        {
            try {
                process();
            } catch (...) {
                if (fExit) exit(EXIT_FAILURE);
            }
        }
        
    #ifdef USE_PTHREAD
        pthread_t fAudioThread;
        static void* run(void* ptr)
        {
            static_cast<dummyaudio_real*>(ptr)->runAux();
        }
    #else
        std::thread* fAudioThread = nullptr;
        static void run(dummyaudio_real* audio)
        {
            audio->runAux();
        }
    #endif
        
        void process()
        {
            while (fRunning && (fRender-- > 0)) {
                if (fSample > 0) { std::cout << "Render one buffer\n"; }
                render();
            }
            fRunning = false;
        }
        
    public:
        
        dummyaudio_real(int sr, int bs,
                        int count = BUFFER_TO_RENDER,
                        int sample = -1,
                        bool manager = false,
                        bool exit = false)
        :fSampleRate(sr), fBufferSize(bs),
        fInChannel(nullptr), fOutChannel(nullptr),
        fNumInputs(-1), fNumOutputs(-1),
        fRender(0), fCount(count),
        fSample(sample), fManager(manager),
        fExit(exit)
        {}
        
        dummyaudio_real(int count = BUFFER_TO_RENDER)
        :fSampleRate(48000), fBufferSize(512),
        fInChannel(nullptr), fOutChannel(nullptr),
        fNumInputs(-1), fNumOutputs(-1),
        fRender(0), fCount(count),
        fSample(512), fManager(false),
        fExit(false)
        {}
        
        virtual ~dummyaudio_real()
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
        
        virtual bool init(const char* name, ::dsp* dsp)
        {
            fDSP = dsp;
            
            // To be used in destructor
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();
            
            fInChannel = new REAL*[fNumInputs];
            fOutChannel = new REAL*[fNumOutputs];
            
            for (int i = 0; i < fNumInputs; i++) {
                fInChannel[i] = new REAL[fBufferSize];
                memset(fInChannel[i], 0, sizeof(REAL) * fBufferSize);
            }
            for (int i = 0; i < fNumOutputs; i++) {
                fOutChannel[i] = new REAL[fBufferSize];
                memset(fOutChannel[i], 0, sizeof(REAL) * fBufferSize);
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
                fAudioThread = new std::thread(dummyaudio_real::run, this);
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
            AVOIDDENORMALS;
            
            fDSP->compute(fBufferSize, reinterpret_cast<FAUSTFLOAT**>(fInChannel), reinterpret_cast<FAUSTFLOAT**>(fOutChannel));
            if (fNumInputs > 0) {
                for (int frame = 0; frame < fSample; frame++) {
                    for (int chan = 0; chan < fNumInputs; chan++) {
                        std::cout << std::fixed << std::setprecision(10) << "\t chan " << chan << " in " << fInChannel[0][frame];
                    }
                    std::cout << std::endl;
                }
            }
            if (fNumOutputs > 0) {
                for (int frame = 0; frame < fSample; frame++) {
                    for (int chan = 0; chan < fNumOutputs; chan++) {
                        std::cout << std::fixed << std::setprecision(10) << "\t chan " << chan << " out " << fOutChannel[chan][frame];
                    }
                    std::cout << std::endl;
                }
            }
        }
        
        virtual int getBufferSize() { return fBufferSize; }
        virtual int getSampleRate() { return fSampleRate; }
        
        virtual int getNumInputs() { return fNumInputs; }
        virtual int getNumOutputs() { return fNumOutputs; }

        REAL** getOutput() { return fOutChannel; }
    
};

struct dummyaudio : public dummyaudio_real<FAUSTFLOAT> {
    
    dummyaudio(int sr, int bs,
               int count = BUFFER_TO_RENDER,
               int sample = -1,
               bool manager = false,
               bool exit = false)
    : dummyaudio_real(sr, bs, count, sample, manager, exit)
    {}
    
    dummyaudio(int count = BUFFER_TO_RENDER) : dummyaudio_real(count)
    {}
    
};

#endif
/**************************  END  dummy-audio.h **************************/
