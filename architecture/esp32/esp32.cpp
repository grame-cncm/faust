/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#include "esp32.h"

#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

<<includeIntrinsic>>

<<includeclass>>

class ESP32Dsp : public mydsp {
  public:
    ESP32Dsp(int sample_rate, int buffer_size){
      fSR = sample_rate;
      fBS = buffer_size;
      init(fSR);
      buildUserInterface(&fUI);
      if(getNumInputs()>0){
        fInChannel = new float*[getNumInputs()];
        for(int i=0; i<getNumInputs(); i++){
          fInChannel[i] = new float[fBS];
        }
      }
      if(getNumOutputs()>0){
        fOutChannel = new float*[getNumOutputs()];
        for(int i=0; i<getNumOutputs(); i++){
          fOutChannel[i] = new float[fBS];
        }
      }
    }
    ~ESP32Dsp(){
      for(int i=0; i<getNumInputs(); i++) {
        delete[] fInChannel[i];
      }
      delete [] fInChannel;
      for (int i=0; i < getNumOutputs(); i++) {
        delete[] fOutChannel[i];
      }
      delete [] fOutChannel;
    }
    void computeBlock(){
      compute(fBS,fInChannel,fOutChannel);
    }
    void setParamValue(const std::string& path, float value){
      fUI.setParamValue(path,value);
    }
    float **fInChannel, **fOutChannel;
    int fSR, fBS;
  private:
    MapUI fUI;
};

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10

AudioFaust::AudioFaust(int sample_rate, int buffer_size)
{
  xHandle = NULL;
  esp32Dsp = new ESP32Dsp(sample_rate, buffer_size);
  i2s_pin_config_t pin_config;
#if TTGO_TAUDIO  
  pin_config = {
    .bck_io_num = 33,
    .ws_io_num = 25,
    .data_out_num = 26,
    .data_in_num = 27
  };
#else // Default
  pin_config = {
    .bck_io_num = 33,
    .ws_io_num = 25,
    .data_out_num = 26,
    .data_in_num = 27
  };
#endif
  configureI2S(sample_rate, buffer_size,pin_config);
}

AudioFaust::~AudioFaust()
{
  delete esp32Dsp;
}

bool AudioFaust::start()
{
  xTaskCreate(audioTask, "Faust DSP Task", 1024, (void *) esp32Dsp, 5, &xHandle);
  return true;
}

void AudioFaust::stop()
{
  if( xHandle != NULL ){
    vTaskDelete( xHandle );
    xHandle = NULL;
  }
}

void AudioFaust::setParamValue(const std::string& path, float value){
  esp32Dsp->setParamValue(path,value);
}

void AudioFaust::configureI2S(int sample_rate, int buffer_size, i2s_pin_config_t pin_config){
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
  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, &pin_config);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
  REG_WRITE(PIN_CTRL, 0xFFFFFFF0);
}

void AudioFaust::audioTask(void* arg){
  ESP32Dsp* fDSP = (ESP32Dsp*) arg;
  while(true){
    if(fDSP->getNumInputs()>0){
      int32_t samples_data_in[2*fDSP->fBS];
      size_t bytes_read = 0;
      i2s_read((i2s_port_t)0, &samples_data_in, 8*fDSP->fBS, &bytes_read, portMAX_DELAY);
      for(int i=0; i<fDSP->fBS; i++){
        fDSP->fInChannel[0][i] = (float) samples_data_in[i*2]*DIV_S32;
        if(fDSP->getNumInputs()>1){
          fDSP->fInChannel[1][i] = (float) samples_data_in[i*2 + 1]*DIV_S32;
        }
      }
    }
    fDSP->computeBlock();
    int32_t samples_data_out[2*fDSP->fBS];
    for(int i=0; i<fDSP->fBS; i++){
      samples_data_out[i*2] = std::max(-MULT_S32,std::min(MULT_S32,((int32_t) (fDSP->fOutChannel[0][i]*MULT_S32)))) ;
      if(fDSP->getNumOutputs() == 2){ // if stereo
        samples_data_out[i*2 + 1] = ((int32_t) (fDSP->fOutChannel[1][i]*MULT_S32)) ;
      }
      else{ // otherwise only first channel only
        samples_data_out[i*2 + 1] = samples_data_out[i*2];
      }
    }
    size_t bytes_writen = 0;
    i2s_write((i2s_port_t)0, &samples_data_out, 8*fDSP->fBS, &bytes_writen, portMAX_DELAY);
  }
}
