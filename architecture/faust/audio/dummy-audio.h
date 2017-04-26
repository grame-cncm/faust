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
 
/******************************************************************************
*******************************************************************************

						A dummy audio driver

*******************************************************************************
*******************************************************************************/

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

        FAUSTFLOAT** fInChannel;
        FAUSTFLOAT** fOutChannel;  

        int fCount;
        bool fIsSample;

    public:

        dummyaudio(int sr, int bs, int count = 10, bool sample = false)
            :fSampleRate(sr), fBufferSize(bs), fCount(count), fIsSample(sample) {}
        dummyaudio(int count = 10)
            :fSampleRate(48000), fBufferSize(512), fCount(count) {}
    
        virtual ~dummyaudio() 
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete[] fInChannel[i];
            }
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
               delete[] fOutChannel[i];
            }
            
            delete [] fInChannel;
            delete [] fOutChannel;
        }

        virtual bool init(const char* name, dsp* dsp)
        {
            fDSP = dsp;
            fDSP->init(fSampleRate);
            
            fInChannel = new FAUSTFLOAT*[fDSP->getNumInputs()];
            fOutChannel = new FAUSTFLOAT*[fDSP->getNumOutputs()];
            
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                fInChannel[i] = new FAUSTFLOAT[fBufferSize];
                memset(fInChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                fOutChannel[i] = new FAUSTFLOAT[fBufferSize];
                memset(fOutChannel[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            return true;
        }
        virtual bool start()
        {
            while (--fCount > 0) {
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
            if (fDSP->getNumInputs() > 0) {
                if (fIsSample) {
                    for (int frame = 0; frame < fBufferSize; frame++) {
                        std::cout << std::setprecision(6) << "sample in " << fInChannel[0][frame] << std::endl;
                    }
                } else {
                    std::cout << std::setprecision(6) << "sample in " << fInChannel[0][0] << std::endl;
                }
            }
            if (fDSP->getNumOutputs() > 0) {
                if (fIsSample) {
                    for (int frame = 0; frame < fBufferSize; frame++) {
                        std::cout << std::fixed << std::setprecision(6) << "sample out " << fOutChannel[0][frame] << std::endl;
                    }
                } else {
                    std::cout << std::fixed << std::setprecision(6) << "sample out " << fOutChannel[0][0] << std::endl;
                }
            }
        }

        virtual int get_buffer_size() { return fBufferSize; }
        virtual int get_sample_rate() { return fSampleRate; }
    
};
					
#endif
