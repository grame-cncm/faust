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

static int audioCallback(const void *ibuf, void *obuf, unsigned long frames, const PaStreamCallbackTimeInfo*,  PaStreamCallbackFlags, void * drv);

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
        
        //----------------------------------------------------------------------------
        // 	number of physical input and output channels of the PA device
        //----------------------------------------------------------------------------
        int	fDevNumInChans;
        int	fDevNumOutChans;

        //----------------------------------------------------------------------------
        // tables of noninterleaved input and output channels for FAUST
        //----------------------------------------------------------------------------
        float** fInChannel;
        float** fOutChannel;

        //----------------------------------------------------------------------------
        // allocated the noninterleaved input and output channels for FAUST
        //----------------------------------------------------------------------------
        void allocChannels(int size, int numInChan, int numOutChan)
        {
            fInChannel = new float*[numInChan];
            fOutChannel = new float*[numOutChan];

            for (int i = 0; i < numInChan; i++) {
                fInChannel[i] = (float*) calloc (size, sizeof(float));
                for (int j = 0; j < size; j++)
                    fInChannel[i][j] = 0.0;
            }

            for (int i = 0; i < numOutChan; i++) {
                fOutChannel[i] = (float*) calloc (size, sizeof(float));
                for (int j = 0; j < size; j++)
                    fOutChannel[i][j] = 0.0;
            }
        }

	public:
    
        portaudio(long srate, long bsize) : fDsp(0), fAudioStream(0),
                fSampleRate(srate), fBufferSize(bsize), fDevNumInChans(0), fDevNumOutChans(0) {}
        virtual ~portaudio() 
        {   
            stop(); 
            delete [] fInChannel;
            delete [] fOutChannel;
        }

        virtual bool init(const char* name, dsp* DSP)
        {
            fDsp = DSP;
            if (pa_error(Pa_Initialize())) {
                return false;
            }

            const PaDeviceInfo*	idev = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
            const PaDeviceInfo*	odev = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());

            fDevNumInChans = (fDsp->getNumInputs() > 0) ? idev->maxInputChannels : 0;
            fDevNumOutChans = (fDsp->getNumOutputs() > 0) ? odev->maxOutputChannels : 0;

            PaStreamParameters inputParameters;
            PaStreamParameters outputParameters;

            inputParameters.device = Pa_GetDefaultInputDevice();
            inputParameters.sampleFormat = paFloat32;
            inputParameters.channelCount = fDevNumInChans;
            inputParameters.hostApiSpecificStreamInfo = 0;

            outputParameters.device = Pa_GetDefaultOutputDevice();
            outputParameters.sampleFormat = paFloat32;
            outputParameters.channelCount = fDevNumOutChans;
            outputParameters.hostApiSpecificStreamInfo = 0;

            PaError err;
            if ((err = Pa_IsFormatSupported(
                ((fDevNumInChans > 0) ? &inputParameters : 0),
                ((fDevNumOutChans > 0) ? &outputParameters : 0), fSampleRate)) != 0) {
                printf("stream format is not supported err = %d\n", err);
                return false;
            }

            allocChannels(fBufferSize, max(fDevNumInChans, fDsp->getNumInputs()), max(fDevNumOutChans, fDsp->getNumOutputs()));
            fDsp->init(fSampleRate);
            return true;
        }

        virtual bool start() 
        {
            if (pa_error(Pa_OpenDefaultStream(&fAudioStream, fDevNumInChans, fDevNumOutChans, paFloat32, fSampleRate, fBufferSize, audioCallback, this))) {
                return false;
            }
            if (pa_error(Pa_StartStream(fAudioStream)) {
                return false;
            }
            return true;
        }

        virtual void stop() 
        {
            if (fAudioStream) {
                Pa_StopStream (fAudioStream);
                Pa_CloseStream(fAudioStream);
                fAudioStream = 0;
            }
        }

        int processAudio(const float* ibuf, float* obuf, unsigned long frames) 
        {
            const float* fInputBuffer = ibuf;
            float* fOutputBuffer = obuf;

            // split input samples
            for (unsigned long s = 0; s < frames; s++) {
                for (int c = 0; c < fDevNumInChans; c++) {
                    fInChannel[c][s] = fInputBuffer[c + s*fDevNumInChans];
                }
            }

            // process samples
            fDsp->compute(frames, fInChannel, fOutChannel);

            // merge output samples
            for (unsigned long s = 0; s < frames; s++) {
                for (int c = 0; c < fDevNumOutChans; c++) {
                    fOutputBuffer[c + s*fDevNumOutChans] = fOutChannel[c][s];
                }
            }
            return 0;
        }
};

//----------------------------------------------------------------------------
// Port Audio Callback
//----------------------------------------------------------------------------
static int audioCallback(const void* ibuf, void* obuf, unsigned long frames, const PaStreamCallbackTimeInfo*,  PaStreamCallbackFlags, void* drv)
{
	portaudio* pa = (portaudio*) drv;
	return pa->processAudio((const float*)ibuf, (float*)obuf, frames);
}

#endif
