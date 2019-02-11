#ifndef __teensy_dsp__
#define __teensy_dsp__

#define MULT_16 2147483647

#include <Audio.h>

class teensyfaust : public AudioStream {
public:
  
  teensyfaust(dsp* cDSP) : AudioStream(cDSP->getNumInputs(), NULL)
  {  
    fDSP = cDSP;
    if(fDSP->getNumInputs()>0){
      *inputQueueArray = new audio_block_t[fDSP->getNumInputs()];
    }
    DIV_16 = 1.0f/MULT_16;
    // allocating Faust inputs
    if(fDSP->getNumInputs()>0){ 
      fInChannel = new float*[fDSP->getNumInputs()];
      for(int i=0; i<fDSP->getNumInputs(); i++){
        fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
      }
    }
    // allocating Faust outputs
    if(fDSP->getNumOutputs()>0){
      fOutChannel = new float*[fDSP->getNumOutputs()];
      for(int i=0; i<fDSP->getNumOutputs(); i++){
        fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
      }
    }
  }
  
  virtual ~teensyfaust()
  {
    for(int i=0; i<fDSP->getNumInputs(); i++){
      delete inputQueueArray[i];
    }
    for(int i=0; i<fDSP->getNumInputs(); i++) {
      delete[] fInChannel[i];
    }
    delete [] fInChannel;
    for (int i=0; i < fDSP->getNumOutputs(); i++) {
      delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
  }
  
  virtual void update(void)
  {
    audio_block_t *inBlock[fDSP->getNumInputs()], *outBlock[fDSP->getNumOutputs()];
    int32_t val;
    
    if(fDSP->getNumInputs()>0){
      for(int channel=0; channel<fDSP->getNumInputs(); channel++){
        inBlock[channel] = receiveReadOnly(channel);
        for(int i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
          val = inBlock[channel]->data[i] << 16;
          fInChannel[channel][i] = val*DIV_16;
        }
        release(inBlock[channel]);
      }
    }
    
    fDSP->compute(AUDIO_BLOCK_SAMPLES,fInChannel,fOutChannel);
    
    for(int channel=0; channel<fDSP->getNumOutputs(); channel++){
      outBlock[channel] = allocate();
      if(outBlock[channel]){
        for(int i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
          val = fOutChannel[channel][i]*MULT_16;
          outBlock[channel]->data[i] = val >> 16;
        }
        transmit(outBlock[channel],channel);
        release(outBlock[channel]);
      }
    }
  }
private:
  dsp* fDSP;
  float DIV_16;
  float** fInChannel;
  float** fOutChannel;
  audio_block_t **inputQueueArray;
};

class teensyaudio : public audio {
  
public:  
  teensyaudio() {}
  
  virtual ~teensyaudio()
  {
    if(fDSP->getNumInputs()>0){
      //delete audioIn; // Creates a warning, not sure why
      for(int i=0; i<fDSP->getNumInputs(); i++){
        delete inputChords[i];
      }
    }
    if(fDSP->getNumOutputs()>0){
      for(int i=0; i<fDSP->getNumOutputs(); i++){
        delete outputChords[i];
      }
    }
    if(tFaust != NULL) delete tFaust;
  }
  
  bool init(const char* name, dsp* dsp) override
  {
    fDSP = dsp;
    fDSP->init(AUDIO_SAMPLE_RATE_EXACT);
    tFaust = new teensyfaust(fDSP);
    if(fDSP->getNumInputs()>0){
      audioIn = new AudioInputI2S();
      for(int i=0; i<fDSP->getNumInputs(); i++){
        inputChords[i] = new AudioConnection(*audioIn,i,*tFaust,i);
      }
    }
    for(int i=0; i<fDSP->getNumOutputs(); i++){
      outputChords[i] = new AudioConnection(*tFaust,i,audioOut,i);
    }
    AudioMemory(6);
    audioShield.enable();
    return true;
  }
  
  bool start() override
  {
    return true;
  }
  
  void stop() override
  {
  }
  
  int getBufferSize() override
  {
    return AUDIO_BLOCK_SAMPLES;
  }
  
  int getSampleRate() override
  {
    return AUDIO_SAMPLE_RATE;
  }
  
  int getNumInputs() override { return fDSP->getNumInputs(); }
  int getNumOutputs() override { return fDSP->getNumOutputs(); }
  
private:
  dsp* fDSP;
  teensyfaust* tFaust;
  AudioInputI2S* audioIn;
  AudioOutputI2S audioOut;
  AudioConnection* inputChords[];
  AudioConnection* outputChords[];
  AudioControlSGTL5000 audioShield;
};
#endif