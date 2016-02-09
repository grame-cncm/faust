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

#ifndef __portaudio_dsp__
#define __portaudio_dsp__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <portaudio.h>

#include "faust/audio/audio.h"
#include "faust/dsp/dsp-adapter.h"

static bool pa_error(int err)
{
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return true;
    } else {
        return false;
    }
}

/******************************************************************************
 *******************************************************************************
 
 PORT AUDIO INTERFACE
 
 *******************************************************************************
 *******************************************************************************/

class portaudio : public audio {
    
    protected:
        
        dsp* fDsp;
        PaStream* fAudioStream;
        long fSampleRate;
        long fBufferSize;
        PaStreamParameters fInputParameters;
        PaStreamParameters fOutputParameters;
        
        //----------------------------------------------------------------------------
        // 	Number of physical input and output channels of the PA device
        //----------------------------------------------------------------------------
        int	fDevNumInChans;
        int	fDevNumOutChans;
        
        static int audioCallback(const void* ibuf, void* obuf, unsigned long frames, const PaStreamCallbackTimeInfo* time, PaStreamCallbackFlags, void* drv)
        {
            return static_cast<portaudio*>(drv)->processAudio(time->currentTime, 
                                                            (float**)ibuf, 
                                                            static_cast<float**>(obuf), 
                                                            frames);
        }
        
        virtual int processAudio(PaTime current_time, float** ibuf, float** obuf, unsigned long frames) 
        {
            // Cleanup hardware outputs that are not used by DSP
            for (int i = fDsp->getNumOutputs(); i < fDevNumOutChans; i++) {
                memset(obuf[i], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            
            // Process samples
            fDsp->compute(current_time * 1000000., frames, ibuf, obuf);
            return paContinue;
        }
        
    public:
        
        portaudio(long srate, long bsize) : 
                fDsp(0), fAudioStream(0),
                fSampleRate(srate), fBufferSize(bsize), 
                fDevNumInChans(0), fDevNumOutChans(0) {}
                
        virtual ~portaudio() 
        {   
            if (fAudioStream) {
                pa_error(Pa_StopStream(fAudioStream));
                pa_error(Pa_CloseStream(fAudioStream));
                fAudioStream = 0;
            }
            // Note that Pa_Initialize handled multiple times calls and 
            // must be matched with a corresponding call to Pa_Terminate
            Pa_Terminate();
        }
        
        virtual bool init(const char* name, dsp* DSP)
        {
            if (init(name, DSP->getNumInputs(), DSP->getNumOutputs())) {
                set_dsp(DSP);
                return true;
            } else {
                return false;
            }
        }
        
        bool init(const char* /*name*/, int numInputs, int numOutputs)
        {         
            // Note that Pa_Initialize handled multiple times calls and 
            // must be matched with a corresponding call to Pa_Terminate
            if (pa_error(Pa_Initialize())) {
                return false;
            }
            
            const PaDeviceInfo*	idev = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
            const PaDeviceInfo*	odev = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());
            
            printf("DEVICE = %p || %p\n", idev, odev);
            
            //In case there is no audio device, the function fails
            
            if (idev == NULL) {
                fDevNumInChans = 0;
            } else {
                fDevNumInChans = idev->maxInputChannels;
                fInputParameters.device = Pa_GetDefaultInputDevice();
                fInputParameters.sampleFormat = paFloat32 | paNonInterleaved;
                fInputParameters.channelCount = fDevNumInChans;
                fInputParameters.hostApiSpecificStreamInfo = 0;
            }
            
            if (odev == NULL) {
                fDevNumOutChans = 0;
            } else{
                fDevNumOutChans = odev->maxOutputChannels;
                fOutputParameters.device = Pa_GetDefaultOutputDevice();
                fOutputParameters.sampleFormat = paFloat32 | paNonInterleaved;;
                fOutputParameters.channelCount = fDevNumOutChans;
                fOutputParameters.hostApiSpecificStreamInfo = 0;
            }
            
            // A DSP that has only outputs or only inputs forces the presence of an output or input device
            if (numInputs == 0 && numOutputs != 0 && fDevNumOutChans == 0) {
                printf("Devices not adapted to DSP\n");
                return false;
            }
            
            if (numInputs != 0 && numOutputs == 0 && fDevNumInChans == 0) {
                printf("Devices not adapted to DSP\n");
                return false;
            }
            
            // If no device exists : the function fails
            PaError err;
            if ((err = Pa_IsFormatSupported(((fDevNumInChans > 0) ? &fInputParameters : 0),
                                            ((fDevNumOutChans > 0) ? &fOutputParameters : 0), fSampleRate)) != 0) {
                printf("stream format is not supported err = %d\n", err);
                return false;
            }
            
            if (pa_error(Pa_OpenStream(&fAudioStream, ((fDevNumInChans > 0) ? &fInputParameters : 0),
                                       ((fDevNumOutChans > 0) ? &fOutputParameters : 0), 
                                       fSampleRate, fBufferSize, paNoFlag, audioCallback, this))) {
                return false;
            }    
            
            return true;
        }
        
        void set_dsp(dsp* DSP) 
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
            if (pa_error(Pa_StartStream(fAudioStream))) {
                return false;
            } else {
                return true;
            }
        }
        
        virtual void stop() 
        {
            if (fAudioStream) {
                pa_error(Pa_StopStream(fAudioStream));
            }
        }
        
        virtual int get_buffer_size() 
        { 
            return fBufferSize; 
        }
        
        virtual int get_sample_rate() 
        { 
            return fSampleRate; 
        }
        
        virtual int get_num_inputs() 
        {
            return fDevNumInChans;
        }
        
        virtual int get_num_outputs() 
        {
            return fDevNumOutChans;
        }
};

#endif
