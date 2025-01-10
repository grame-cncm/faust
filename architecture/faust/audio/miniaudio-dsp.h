/************************** BEGIN miniaudio-dsp.h ************************
 FAUST Architecture File
 Copyright (C) 2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __miniaudio_dsp__
#define __miniaudio_dsp__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "faust/audio/audio.h"

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#include "faust/miniaudio.h"

/******************************************************************************
 *******************************************************************************
 
 MINIAUDIO INTERFACE
 
 *******************************************************************************
 *******************************************************************************/

class miniaudio : public audio {
    
    protected:
        
        ::dsp* fDSP;
        ma_device fAudioDevice;  // MiniAudio device
        long fSampleRate;
        long fBufferSize;
    
        // Callback function for MiniAudio stream
        static void audioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
        {
            static_cast<miniaudio*>(pDevice->pUserData)->processAudio(pInput, pOutput, frameCount);
        }
        
        virtual void processAudio(const void* pInput, void* pOutput, ma_uint32 frameCount)
        {
            AVOIDDENORMALS;
          
            float** in_buffers = (float**)alloca(fDSP->getNumInputs() * sizeof(float*));
            for (int i = 0; i < fDSP->getNumInputs(); ++i) {
                in_buffers[i] = (float*)alloca(frameCount * sizeof(float));
            }
            float** out_buffers = (float**)alloca(fDSP->getNumOutputs() * sizeof(float*));
            for (int i = 0; i < fDSP->getNumOutputs(); ++i) {
                out_buffers[i] = (float*)alloca(frameCount * sizeof(float));
            }
            
            // Deinterleave the input audio frames into the input buffers
            ma_deinterleave_pcm_frames(ma_format_f32, fDSP->getNumInputs(), frameCount, pInput, (void **)in_buffers);
            
            // Compute the DSP process on the deinterleaved buffers
            fDSP->compute(frameCount, in_buffers, out_buffers);
            
            // Re-interleave the output frames back into a single interleaved buffer
            ma_interleave_pcm_frames(ma_format_f32, fDSP->getNumOutputs(), frameCount, (const void **)out_buffers, pOutput);
        }
        
    public:
        
        miniaudio(long srate, long bsize) :
            fDSP(nullptr), fSampleRate(srate), fBufferSize(bsize)
        {}
        
        virtual ~miniaudio()
        {
            ma_device_stop(&fAudioDevice);
            ma_device_uninit(&fAudioDevice);
        }
        
        virtual bool init(const char* name, ::dsp* DSP)
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
            ma_result result;
            ma_device_config config;
          
            config = ma_device_config_init(ma_device_type_duplex);
            config.capture.format     = ma_format_f32;
            config.capture.channels   = numInputs;
            config.playback.format    = ma_format_f32;
            config.playback.channels  = numOutputs;
            config.sampleRate         = fSampleRate;
            config.periodSizeInFrames = fBufferSize;
            config.dataCallback       = audioCallback;
            config.pUserData          = this;
        
            result = ma_device_init(NULL, &config, &fAudioDevice);
            return (result == MA_SUCCESS);
        }
        
        void setDsp(::dsp* DSP)
        {
            fDSP = DSP;
            fDSP->init(fSampleRate);
        }
        
        bool start()
        {
            return ma_device_start(&fAudioDevice) == MA_SUCCESS;
        }
        
        void stop()
        {
            ma_device_stop(&fAudioDevice);
        }
        
        int getBufferSize()
        {
            return fBufferSize;
        }
        
        int getSampleRate()
        {
            return fSampleRate;
        }
        
        int getNumInputs()
        {
            return fDSP->getNumInputs();
        }
        
        int getNumOutputs()
        {
            return fDSP->getNumOutputs();
        }
};

#endif
/**************************  END  miniaudio-dsp.h **************************/
