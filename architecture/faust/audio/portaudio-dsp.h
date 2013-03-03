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
#include <assert.h>
#include <portaudio.h>

#include "faust/audio/audio.h"
#include "faust/audio/dsp.h"

static int audioCallback(const void* ibuf, void* obuf, unsigned long frames, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void* drv);

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

    private:

        dsp* fDsp;
        PaStream* fAudioStream;
        long fSampleRate;
        long fBufferSize;
        PaStreamParameters fInputParameters;
        PaStreamParameters fOutputParameters;
        
        //----------------------------------------------------------------------------
        // 	number of physical input and output channels of the PA device
        //----------------------------------------------------------------------------
        int	fDevNumInChans;
        int	fDevNumOutChans;

	public:
    
        portaudio(long srate, long bsize) : fDsp(0), fAudioStream(0),
                fSampleRate(srate), fBufferSize(bsize), fDevNumInChans(0), fDevNumOutChans(0) {}
        virtual ~portaudio() 
        {   
            stop(); 
            Pa_Terminate();
        }

        virtual bool init(const char* name, dsp* DSP)
        {
            fDsp = DSP;
            if (pa_error(Pa_Initialize())) {
                return false;
            }

            const PaDeviceInfo*	idev = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
            const PaDeviceInfo*	odev = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());
         
            if (fDsp->getNumInputs() > idev->maxInputChannels || fDsp->getNumOutputs() > odev->maxOutputChannels) {
                printf("DSP has %d inputs and %d outputs, physical inputs = %d physical outputs = %d \n", 
                        fDsp->getNumInputs(), fDsp->getNumOutputs(), 
                        idev->maxInputChannels, odev->maxOutputChannels);
                return false;
            }
            
            fDevNumInChans = idev->maxInputChannels;
            fDevNumOutChans = odev->maxOutputChannels;

            fInputParameters.device = Pa_GetDefaultInputDevice();
            fInputParameters.sampleFormat = paFloat32 | paNonInterleaved;;
            fInputParameters.channelCount = fDevNumInChans;
            fInputParameters.hostApiSpecificStreamInfo = 0;

            fOutputParameters.device = Pa_GetDefaultOutputDevice();
            fOutputParameters.sampleFormat = paFloat32 | paNonInterleaved;;
            fOutputParameters.channelCount = fDevNumOutChans;
            fOutputParameters.hostApiSpecificStreamInfo = 0;
          
            PaError err;
            if ((err = Pa_IsFormatSupported(
                ((fDevNumInChans > 0) ? &fInputParameters : 0),
                ((fDevNumOutChans > 0) ? &fOutputParameters : 0), fSampleRate)) != 0) {
                printf("stream format is not supported err = %d\n", err);
                return false;
            }

            fDsp->init(fSampleRate);
            return true;
        }

        virtual bool start() 
        {
            if (pa_error(Pa_OpenStream(&fAudioStream, &fInputParameters, &fOutputParameters, fSampleRate, fBufferSize, paNoFlag, audioCallback, this))) {
                return false;
            }      
            
            if (pa_error(Pa_StartStream(fAudioStream))) {
                return false;
            }
            return true;
        }

        virtual void stop() 
        {
            if (fAudioStream) {
                Pa_StopStream(fAudioStream);
                Pa_CloseStream(fAudioStream);
                fAudioStream = 0;
            }
        }

        int processAudio(float** ibuf, float** obuf, unsigned long frames) 
        {
            // process samples
            fDsp->compute(frames, ibuf, obuf);
            return paContinue;
        }
};

//----------------------------------------------------------------------------
// Port Audio Callback
//----------------------------------------------------------------------------
static int audioCallback(const void* ibuf, void* obuf, unsigned long frames, const PaStreamCallbackTimeInfo*,  PaStreamCallbackFlags, void* drv)
{
	portaudio* pa = (portaudio*)drv;
	return pa->processAudio((float**)ibuf, (float**)obuf, frames);
}

#endif
