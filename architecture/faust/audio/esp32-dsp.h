/************************** BEGIN esp32audio.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef __esp32audio__
#define __esp32audio__

#include <utility>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"

#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10
#define clip(sample) std::max(-MULT_S32, std::min(MULT_S32, ((int32_t)(sample * MULT_S32))));

#define AUDIO_MAX_CHAN 2

class esp32audio : public audio {
    
    private:
    
        int fSampleRate;
        int fBufferSize;
        int fNumInputs;
        int fNumOutputs;
        float** fInChannel;
        float** fOutChannel;
        TaskHandle_t fHandle;
        dsp* fDSP;
        bool fRunning;
    
        template <int INPUTS, int OUTPUTS>
        void audioTask()
        {
            while (fRunning) {
                if (INPUTS > 0) {
                    // Read from the card
                    int32_t samples_data_in[AUDIO_MAX_CHAN*fBufferSize];
                    size_t bytes_read = 0;
                    i2s_read((i2s_port_t)0, &samples_data_in, AUDIO_MAX_CHAN*sizeof(float)*fBufferSize, &bytes_read, portMAX_DELAY);
                    
                    // Convert and copy inputs
                    if (INPUTS == AUDIO_MAX_CHAN) {
                        // if stereo
                        for (int i = 0; i < fBufferSize; i++) {
                            fInChannel[0][i] = (float)samples_data_in[i*AUDIO_MAX_CHAN]*DIV_S32;
                            fInChannel[1][i] = (float)samples_data_in[i*AUDIO_MAX_CHAN+1]*DIV_S32;
                        }
                    } else {
                        // otherwise only first channel
                        for (int i = 0; i < fBufferSize; i++) {
                            fInChannel[0][i] = (float)samples_data_in[i*AUDIO_MAX_CHAN]*DIV_S32;
                        }
                    }
                }
                
                // Call DSP
                fDSP->compute(fBufferSize, fInChannel, fOutChannel);
                
                // Convert and copy outputs
                int32_t samples_data_out[AUDIO_MAX_CHAN*fBufferSize];
                if (OUTPUTS == AUDIO_MAX_CHAN) {
                    // if stereo
                    for (int i = 0; i < fBufferSize; i++) {
                        samples_data_out[i*AUDIO_MAX_CHAN] = clip(fOutChannel[0][i]);
                        samples_data_out[i*AUDIO_MAX_CHAN+1] = clip(fOutChannel[1][i]);
                    }
                } else {
                    // otherwise only first channel
                    for (int i = 0; i < fBufferSize; i++) {
                        samples_data_out[i*AUDIO_MAX_CHAN] = clip(fOutChannel[0][i]);
                        samples_data_out[i*AUDIO_MAX_CHAN+1] = samples_data_out[i*AUDIO_MAX_CHAN];
                    }
                }
                
                // Write to the card
                size_t bytes_written = 0;
                i2s_write((i2s_port_t)0, &samples_data_out, AUDIO_MAX_CHAN*sizeof(float)*fBufferSize, &bytes_written, portMAX_DELAY);
            }
            
            // Task has to deleted itself beforee returning
            vTaskDelete(nullptr);
        }
    
        void destroy()
        {
            for (int i = 0; i < fNumInputs; i++) {
                delete[] fInChannel[i];
            }
            delete [] fInChannel;
            
            for (int i = 0; i < fNumOutputs; i++) {
                delete[] fOutChannel[i];
            }
            delete [] fOutChannel;
        }
    
        static void audioTaskHandler(void* arg)
        {
            esp32audio* audio = static_cast<esp32audio*>(arg);
            
            if (audio->fNumInputs == 0 && audio->fNumOutputs == 1) {
                audio->audioTask<0,1>();
            } else if (audio->fNumInputs == 0 && audio->fNumOutputs == 2) {
                audio->audioTask<0,2>();
            } else if (audio->fNumInputs == 1 && audio->fNumOutputs == 1) {
                audio->audioTask<1,1>();
            } else if (audio->fNumInputs == 1 && audio->fNumOutputs == 2) {
                audio->audioTask<1,2>();
            } else if (audio->fNumInputs == 2 && audio->fNumOutputs == 1) {
                audio->audioTask<2,1>();
            } else if (audio->fNumInputs == 2 && audio->fNumOutputs == 2) {
                audio->audioTask<2,2>();
            }
        }
    
    public:
    
        esp32audio(int srate, int bsize):
        fSampleRate(srate),
        fBufferSize(bsize),
        fNumInputs(0),
        fNumOutputs(0),
        fInChannel(nullptr),
        fOutChannel(nullptr),
        fHandle(nullptr),
        fDSP(nullptr),
        fRunning(false)
        {
            i2s_pin_config_t pin_config;
        #if TTGO_TAUDIO
            pin_config = {
                .bck_io_num = 33,
                .ws_io_num = 25,
                .data_out_num = 26,
                .data_in_num = 27
            };
        #elif A1S_BOARD
            pin_config = {
                .bck_io_num = 27,
                .ws_io_num = 26,
                .data_out_num = 25,
                .data_in_num = 35
            };
        #else // Default
            pin_config = {
                .bck_io_num = 33,
                .ws_io_num = 25,
                .data_out_num = 26,
                .data_in_num = 27
            };
        #endif
            
        #if A1S_BOARD
            i2s_config_t i2s_config = {
                .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
                .sample_rate = fSampleRate,
                .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
                .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
                .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
                .intr_alloc_flags = ESP_INTR_FLAG_LEVEL3, // high interrupt priority
                .dma_buf_count = 3,
                .dma_buf_len = fBufferSize,
                .use_apll = true
            };
        #else // default
            i2s_config_t i2s_config = {
                .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
                .sample_rate = fSampleRate,
                .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
                .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
                .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
                .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
                .dma_buf_count = 3,
                .dma_buf_len = fBufferSize,
                .use_apll = false
            };
        #endif
            i2s_driver_install((i2s_port_t)0, &i2s_config, 0, nullptr);
            i2s_set_pin((i2s_port_t)0, &pin_config);
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
            REG_WRITE(PIN_CTRL, 0xFFFFFFF0);
        }
    
        virtual ~esp32audio()
        {
            destroy();
        }
    
        virtual bool init(const char* name, dsp* dsp)
        {
            destroy();
            
            fDSP = dsp;
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();
            
            fDSP->init(fSampleRate);
            
            if (fNumInputs > 0) {
                fInChannel = new FAUSTFLOAT*[fNumInputs];
                for (int i = 0; i < fNumInputs; i++) {
                    fInChannel[i] = new FAUSTFLOAT[fBufferSize];
                }
            } else {
                fInChannel = nullptr;
            }
            
            if (fNumOutputs > 0) {
                fOutChannel = new FAUSTFLOAT*[fNumOutputs];
                for (int i = 0; i < fNumOutputs; i++) {
                    fOutChannel[i] = new FAUSTFLOAT[fBufferSize];
                }
            } else {
                fOutChannel = nullptr;
            }
            
            return true;
        }
    
        virtual bool start()
        {
            if (!fRunning) {
                fRunning = true;
                return (xTaskCreatePinnedToCore(audioTaskHandler, "Faust DSP Task", 4096, (void*)this, 24, &fHandle, 0) == pdPASS);
            } else {
                return true;
            }
        }
    
        virtual void stop()
        {
            if (fRunning) {
                fRunning = false;
                vTaskDelay(1/portTICK_PERIOD_MS);
                fHandle = nullptr;
            }
        }
    
        virtual int getBufferSize() { return fBufferSize; }
        virtual int getSampleRate() { return fSampleRate; }

        virtual int getNumInputs() { return AUDIO_MAX_CHAN; }
        virtual int getNumOutputs() { return AUDIO_MAX_CHAN; }
    
        // Returns the average proportion of available CPU being spent inside the audio callbacks (between 0 and 1.0).
        virtual float getCPULoad() { return 0.f; }
    
};
					
#endif
/**************************  END  esp32audio.h **************************/
