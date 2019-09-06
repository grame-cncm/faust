/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale &
 Aalborg University (Copenhagen, Denmark)
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

#include "esp32.h"

#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//#define A1S_BOARD true                  //uncomment for Ai-thinker A1S board

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10
#define clip(sample) std::max(-MULT_S32, std::min(MULT_S32, ((int32_t)(sample * MULT_S32))));

AudioFaust::AudioFaust(int sample_rate, int buffer_size)
{
    fBS = buffer_size;
    fDSP = new mydsp();
    fDSP->init(sample_rate);
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    fHandle = NULL;
    
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
    configureI2S(sample_rate, buffer_size, pin_config);
    
    if (fDSP->getNumInputs() > 0) {
        fInChannel = new float*[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new float[fBS];
        }
    }
    if (fDSP->getNumOutputs() > 0) {
        fOutChannel = new float*[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new float[fBS];
        }
    }
}

AudioFaust::~AudioFaust()
{
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
        delete[] fInChannel[i];
    }
    delete [] fInChannel;
    
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
        delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
    
    delete fDSP;
    delete fUI;
}

bool AudioFaust::start()
{
    xTaskCreate(audioTaskHandler, "Faust DSP Task", 1024, (void*)this, 5, &fHandle);
    return true;
}

void AudioFaust::stop()
{
    if (fHandle != NULL) {
        vTaskDelete(fHandle);
        fHandle = NULL;
    }
}

void AudioFaust::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

void AudioFaust::configureI2S(int sample_rate, int buffer_size, i2s_pin_config_t pin_config)
{
    #if A1S_BOARD
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
        .sample_rate = sample_rate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
        .dma_buf_count = 3,
        .dma_buf_len = buffer_size,
        .use_apll = true
    };
    #else // default
        i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
        .sample_rate = sample_rate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
        .dma_buf_count = 3,
        .dma_buf_len = buffer_size,
        .use_apll = false
    };
    #endif
    i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
    i2s_set_pin((i2s_port_t)0, &pin_config);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
    REG_WRITE(PIN_CTRL, 0xFFFFFFF0);
}

void AudioFaust::audioTask()
{
    while (true) {
        if (fDSP->getNumInputs() > 0) {
            
            // Read from the card
            int32_t samples_data_in[2*fBS];
            size_t bytes_read = 0;
            i2s_read((i2s_port_t)0, &samples_data_in, 8*fBS, &bytes_read, portMAX_DELAY);
            
            // Convert and copy inputs
            if (fDSP->getNumInputs() == 2) { // if stereo
                for (int i = 0; i < fBS; i++) {
                    fInChannel[0][i] = (float)samples_data_in[i*2]*DIV_S32;
                    fInChannel[1][i] = (float)samples_data_in[i*2+1]*DIV_S32;
                }
            } else {
                for (int i = 0; i < fBS; i++) {
                    fInChannel[0][i] = (float)samples_data_in[i*2]*DIV_S32;
                }
            }
        }
        
        // Call DSP
        fDSP->compute(fBS, fInChannel, fOutChannel);
        
        // Convert and copy outputs
        int32_t samples_data_out[2*fBS];
        if (fDSP->getNumOutputs() == 2) {
            // if stereo
            for (int i = 0; i < fBS; i++) {
                samples_data_out[i*2] = clip(fOutChannel[0][i]);
                samples_data_out[i*2+1] = clip(fOutChannel[1][i]);
            }
        } else {
            // otherwise only first channel
            for (int i = 0; i < fBS; i++) {
                samples_data_out[i*2] = clip(fOutChannel[0][i]);
                samples_data_out[i*2+1] = samples_data_out[i*2];
            }
        }
        
        // Write to the card
        size_t bytes_writen = 0;
        i2s_write((i2s_port_t)0, &samples_data_out, 8*fBS, &bytes_writen, portMAX_DELAY);
    }
}

void AudioFaust::audioTaskHandler(void* arg)
{
    AudioFaust* audio = (AudioFaust*)arg;
    audio->audioTask();
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
