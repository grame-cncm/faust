/************************** BEGIN samAudio.h **************************/
/************************************************************************
  SHARC Audio Module Faust Architecture File
  Copyright (c) 2018 Analog Devices, Inc. All rights reserved.
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2 of
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

#ifndef __sam_audio__
#define __sam_audio__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
			
#include "faust/dsp/dsp.h"
#include "faust/audio/audio.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class samAudio : public audio {

    private:

        dsp* fDSP;

        int iSampleRate;
        int iBufferSize;
        int iNumInputs;
        int iNumOutputs;
    
        // Faust convention for input/output arrays
        FAUSTFLOAT *inputsArray[8];
        FAUSTFLOAT *outputsArray[8];

    public:
    
        samAudio(int sampleRate, int bufferSize, int numInputs, int numOutputs)
        {
            iSampleRate = sampleRate;
            iBufferSize = bufferSize;
            iNumInputs = numInputs;
            iNumOutputs = numOutputs;
        }
    
        virtual ~samAudio() 
        {
            // nothing for now
        }
    
        // the sam hardware DSP supports up to 8 channels (4 stereo pairs).
        virtual void setDSP_ChannelBuffers(FAUSTFLOAT *AudioChannelA_0_Left,
                                       FAUSTFLOAT *AudioChannelA_0_Right,
                                       FAUSTFLOAT *AudioChannelA_1_Left,
                                       FAUSTFLOAT *AudioChannelA_1_Right,
                                       FAUSTFLOAT *AudioChannelA_2_Left,
                                       FAUSTFLOAT *AudioChannelA_2_Right,
                                       FAUSTFLOAT *AudioChannelA_3_Left,
                                       FAUSTFLOAT *AudioChannelA_3_Right,
                                       FAUSTFLOAT *AudioChannelB_0_Left,
                                       FAUSTFLOAT *AudioChannelB_0_Right,
                                       FAUSTFLOAT *AudioChannelB_1_Left,
                                       FAUSTFLOAT *AudioChannelB_1_Right,
                                       FAUSTFLOAT *AudioChannelB_2_Left,
                                       FAUSTFLOAT *AudioChannelB_2_Right,
                                       FAUSTFLOAT *AudioChannelB_3_Left,
                                       FAUSTFLOAT *AudioChannelB_3_Right)
        {
            // set the pointers, generalized for the sam's 8 channels.
            inputsArray[0] = AudioChannelB_0_Left;
            inputsArray[1] = AudioChannelB_0_Right;
            inputsArray[2] = AudioChannelB_1_Left;
            inputsArray[3] = AudioChannelB_1_Right;
            inputsArray[4] = AudioChannelB_2_Left;
            inputsArray[5] = AudioChannelB_2_Right;
            inputsArray[6] = AudioChannelB_3_Left;
            inputsArray[7] = AudioChannelB_3_Right;
            
            outputsArray[0] = AudioChannelA_0_Left;
            outputsArray[1] = AudioChannelA_0_Right;
            outputsArray[2] = AudioChannelA_1_Left;
            outputsArray[3] = AudioChannelA_1_Right;
            outputsArray[4] = AudioChannelA_2_Left;
            outputsArray[5] = AudioChannelA_2_Right;
            outputsArray[6] = AudioChannelA_3_Left;
            outputsArray[7] = AudioChannelA_3_Right;
        }
    
        virtual bool init(const char* name, dsp* dsp)
        {
            fDSP = dsp;                // this should be fFinalDSP
            fDSP->init(iSampleRate);   // this sets the sample rate
            return true;
        }

        virtual bool start()
        {
            // Nothing for now. Will want to find the sam way to start.
            return true;
        }

        virtual void stop()
        {
            // nothing for now. Will want to find the sam way to stop.
        }
    
        void processAudioCallback()
        {
            // Faust compute function
            fDSP->compute(iBufferSize, inputsArray, outputsArray);
        }
         
        virtual int getBufferSize() { return iBufferSize; }
        virtual int getSampleRate() { return iSampleRate; }
        virtual int getNumInputs()  { return iNumInputs;  }
        virtual int getNumOutputs() { return iNumOutputs; }    
};
					
#endif
/**************************  END  samAudio.h **************************/
