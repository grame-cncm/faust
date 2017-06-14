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
#include <iostream>
#include <iomanip>
			
#include "faust/dsp/dsp.h"
#include "faust/audio/audio.h"

#define BUFFER_TO_RENDER 10

class dummyaudio : public audio {

    private:

        dsp* fDSP;

        long fSampleRate;
        long fBufferSize;
    
        int fNumInputs;
        int fNumOutputs;

        FAUSTFLOAT** fInChannel;
        FAUSTFLOAT** fOutChannel;  

        int fRender;
        int fCount;
        bool fIsSample;
        bool fManager;

    public:

        dummyaudio(int sr, int bs, int count = 10, bool sample = false, bool manager = false)
        :fSampleRate(sr), fBufferSize(bs), fRender(0), fCount(count), fIsSample(sample), fManager(manager) {}
    
        dummyaudio(int count = 10)
        :fSampleRate(48000), fBufferSize(512), fRender(0), fCount(count), fIsSample(false), fManager(false) {}
    
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
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();
            
            if (fManager) {
                // classInit is called elsewhere with a custom memory manager
                fDSP->instanceInit(fSampleRate);
            } else {
                fDSP->init(fSampleRate);
            }
            
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
            return true;
        }
        virtual bool start()
        {
            fRender = fCount;
            while (--fRender > 0) {
                printf("Render one buffer\n");
                render();
            }
            return true;
        }
        virtual void stop()
        {}

        void render()
        {
            fDSP->compute(fBufferSize, fInChannel, fOutChannel);
            if (fNumInputs > 0) {
                if (fIsSample) {
                    for (int frame = 0; frame < fBufferSize; frame++) {
                        std::cout << std::setprecision(6) << "sample in " << fInChannel[0][frame] << std::endl;
                    }
                } else {
                    std::cout << std::setprecision(6) << "sample in " << fInChannel[0][0] << std::endl;
                }
            }
            if (fNumOutputs > 0) {
                if (fIsSample) {
                    for (int frame = 0; frame < fBufferSize; frame++) {
                        std::cout << std::fixed << std::setprecision(6) << "sample out " << fOutChannel[0][frame] << std::endl;
                    }
                } else {
                    std::cout << std::fixed << std::setprecision(6) << "sample out " << fOutChannel[0][0] << std::endl;
                }
            }
        }
    
        virtual int getBufferSize() { return fBufferSize; }
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual int getNumInputs() { return fNumInputs; }
        virtual int getNumOutputs() { return fNumOutputs; }
    
};
					
#endif
