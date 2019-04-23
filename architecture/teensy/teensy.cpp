#include "teensy.h"
// IMPORTANT: in order for MapUI to work, the teensy linker must be g++
#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
// MIDI support
#include "faust/gui/MidiUI.h"
#include "faust/gui/UI.h"
#include "faust/midi/teensy-midi.h"

<<includeIntrinsic>>

<<includeclass>>

#define MULT_16 2147483647
#define DIV_16 4.6566129e-10

teensy_midi gMIDI;
MidiUI* gMidiInterface = NULL;
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
extern usb_midi_class usbMIDI;

AudioFaust::AudioFaust() : AudioStream((fDSP = new mydsp())->getNumInputs(), new audio_block_t*[fDSP->getNumInputs()])
{
	UI = new MapUI();
	fDSP->init(AUDIO_SAMPLE_RATE_EXACT);
	fDSP->buildUserInterface(UI);
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
	gMidiInterface = new MidiUI(&gMIDI);
	fDSP->buildUserInterface(gMidiInterface);
	gMidiInterface->run();	
}

void AudioFaust::update(void)
{
	// Pass to Faust the midi messages recived by the Teensy
	gMIDI.processMidi(usbMIDI);
	// Synchronize all GUI controllers
	GUI::updateAllGuis();
		
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

AudioFaust::~AudioFaust(){
	delete fDSP;
	delete UI;
	for(int i=0; i<fDSP->getNumInputs(); i++) {
		delete[] fInChannel[i];
  }
  delete [] fInChannel;
	for (int i=0; i < fDSP->getNumOutputs(); i++) {
		delete[] fOutChannel[i];
  }
  delete [] fOutChannel;
}

void AudioFaust::setParamValue(const std::string& path, float value){
	UI->setParamValue(path,value);
}
