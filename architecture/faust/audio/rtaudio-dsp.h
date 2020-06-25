/************************** BEGIN rtaudio-dsp.h **************************/
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

#ifndef __rtaudio_dsp__
#define __rtaudio_dsp__

#include <stdio.h>
#include <assert.h>
#include <RtAudio.h>
#include <stdlib.h>

#include "faust/audio/audio.h"
#include "faust/dsp/dsp-adapter.h"

#define FORMAT RTAUDIO_FLOAT32

/******************************************************************************
 *******************************************************************************
 
 RTAUDIO INTERFACE
 
 *******************************************************************************
 *******************************************************************************/

class rtaudio : public audio {
    
    protected:
        
        dsp* fDsp;
        RtAudio fAudioDAC;
        unsigned int fSampleRate;
        unsigned int fBufferSize;
         
        //----------------------------------------------------------------------------
        // 	number of physical input and output channels of the PA device
        //----------------------------------------------------------------------------
        int	fDevNumInChans;
        int	fDevNumOutChans;
        
        virtual int processAudio(double streamTime, void* inbuf, void* outbuf, unsigned long frames) 
        {
            AVOIDDENORMALS;
            
            float* inputs[fDsp->getNumInputs()];
            float* outputs[fDsp->getNumOutputs()];
            
            for (int i = 0; i < fDsp->getNumInputs(); i++) {
                inputs[i] = &(static_cast<float*>(inbuf))[i * frames];
            }
            for (int i = 0; i < fDsp->getNumOutputs(); i++) {
                outputs[i] = &(static_cast<float*>(outbuf))[i * frames];
            }

            // process samples
            fDsp->compute(streamTime * 1000000., frames, inputs, outputs);
            return 0;
        }
    
        static int audioCallback(void* outputBuffer, void* inputBuffer, 
                                unsigned int nBufferFrames,
                                double streamTime, RtAudioStreamStatus status, 
                                void* drv)
        {
            return static_cast<rtaudio*>(drv)->processAudio(streamTime, inputBuffer, outputBuffer, nBufferFrames);
        }
      
    public:
        
        rtaudio(int srate, int bsize) : fDsp(0),
                fSampleRate(srate), fBufferSize(bsize), 
                fDevNumInChans(0), fDevNumOutChans(0) {}
            
        virtual ~rtaudio() 
        {   
            try {
                fAudioDAC.stopStream();
                fAudioDAC.closeStream();
            } catch (RtAudioError& e) {
                std::cout << '\n' << e.getMessage() << '\n' << std::endl;
            }
        }
        
        virtual bool init(const char* name, dsp* DSP)
        {
            if (init(name, DSP->getNumInputs(), DSP->getNumOutputs())) {
                setDsp(DSP);
                return true;
            } else {
                return false;
            }
        }
        
        bool init(const char* /*name*/, int numInputs, int numOutputs)
        {           
            if (fAudioDAC.getDeviceCount() < 1) {
                std::cout << "No audio devices found!\n";
                return false;
            }
            
            RtAudio::DeviceInfo info_in = fAudioDAC.getDeviceInfo(fAudioDAC.getDefaultInputDevice());
            RtAudio::DeviceInfo info_out = fAudioDAC.getDeviceInfo(fAudioDAC.getDefaultOutputDevice());
            RtAudio::StreamParameters iParams, oParams;
            
            iParams.deviceId = fAudioDAC.getDefaultInputDevice();
            fDevNumInChans = info_in.inputChannels;
            iParams.nChannels = fDevNumInChans;
            iParams.firstChannel = 0;
            
            oParams.deviceId = fAudioDAC.getDefaultOutputDevice();
            fDevNumOutChans = info_out.outputChannels;
            oParams.nChannels = fDevNumOutChans;
            oParams.firstChannel = 0;
            
            RtAudio::StreamOptions options;
            options.flags |= RTAUDIO_NONINTERLEAVED;
         
            try {
                fAudioDAC.openStream(((numOutputs > 0) ? &oParams : NULL), 
                    ((numInputs > 0) ? &iParams : NULL), FORMAT, 
                    fSampleRate, &fBufferSize, audioCallback, this, &options);
            } catch (RtAudioError& e) {
                std::cout << '\n' << e.getMessage() << '\n' << std::endl;
                return false;
            }
               
            return true;
        }
        
        void setDsp(dsp* DSP)
        {
            fDsp = DSP;
            
            if (fDsp->getNumInputs() > fDevNumInChans || fDsp->getNumOutputs() > fDevNumOutChans) {
                printf("DSP has %d inputs and %d outputs, physical inputs = %d physical outputs = %d \n", 
                       fDsp->getNumInputs(), fDsp->getNumOutputs(), 
                       fDevNumInChans, fDevNumOutChans);
                fDsp = new dsp_adapter(fDsp, fDevNumInChans, fDevNumOutChans, fBufferSize);
            }
            
            fDsp->init(fSampleRate);
        }
        
        virtual bool start() 
        {
            try {
                fAudioDAC.startStream();
            } catch (RtAudioError& e) {
                std::cout << '\n' << e.getMessage() << '\n' << std::endl;
                return false;
            }
            return true;
        }
        
        virtual void stop() 
        {
            try {
                fAudioDAC.stopStream();
            } catch (RtAudioError& e) {
                std::cout << '\n' << e.getMessage() << '\n' << std::endl;
            }
        }
        
        virtual int getBufferSize() 
        { 
            return fBufferSize; 
        }
        
        virtual int getSampleRate()
        { 
            return fSampleRate; 
        }
        
        virtual int getNumInputs()
        {
            return fDevNumInChans;
        }
        
        virtual int getNumOutputs()
        {
            return fDevNumOutChans;
        }
};

#endif
/**************************  END  rtaudio-dsp.h **************************/
