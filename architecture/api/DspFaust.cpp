/************************************************************************
 ************************************************************************
 FAUST API Architecture File 
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include <math.h>
#include <cmath>

//**************************************************************
// Intrinsic
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/faust-poly-engine.h"

//**************************************************************
// Audio driver
//**************************************************************

#if COREAUDIO_DRIVER
    #include "faust/audio/coreaudio-dsp.h"
#elif IOS_DRIVER
    #include "faust/audio/coreaudio-ios-dsp.h"
#elif ANDROID_DRIVER
    #include <android/log.h>
    #include "faust/audio/android-dsp.h"
#elif ALSA_DRIVER
    #include "faust/audio/alsa-dsp.h"
#elif JACK_DRIVER
    #include "faust/audio/jack-dsp.h"
#elif PORTAUDIO_DRIVER
    #include "faust/audio/portaudio-dsp.h"
#elif RTAUDIO_DRIVER
    #include "faust/audio/rtaudio-dsp.h"
#elif OPEN_FRAMEWORK_DRIVER
    #include "faust/audio/ofaudio-dsp.h"
#elif JUCE_DRIVER
    #include "faust/audio/juce-dsp.h"
#elif DUMMY_DRIVER
    #include "faust/audio/dummy-audio.h"
#endif

//**************************************************************
// Interface
//**************************************************************

#if MIDICTRL
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

#if OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(int sample_rate, int buffer_size){
    
#if COREAUDIO_DRIVER
    audio* driver = new coreaudio(sample_rate, buffer_size);
#elif IOS_DRIVER
    audio* driver = new iosaudio(sample_rate, buffer_size);
#elif ANDROID_DRIVER
    audio* driver = new androidaudio(sample_rate, buffer_size);
#elif ALSA_DRIVER
    audio* driver = new alsaaudio(sample_rate, buffer_size);
#elif JACK_DRIVER
    // JACK has its own sample rate and buffer size
    audio* driver = new jackaudio();
#elif PORTAUDIO_DRIVER
    audio* driver = new portaudio(sample_rate, buffer_size);
#elif RTAUDIO_DRIVER
    audio* driver = new rtaudio(sample_rate, buffer_size);
#elif OPEN_FRAMEWORK_DRIVER
    audio* driver = new ofaudio(sample_rate, buffer_size);
#elif JUCE_DRIVER
    // JUCE audio device has its own sample rate and buffer size
    audio* driver = new juceaudio();
#elif DUMMY_DRIVER
    audio* driver = new dummyaudio(sample_rate, buffer_size);
#endif
    
	fPolyEngine = new FaustPolyEngine(driver);

#if OSCCTRL
    const char* argv[9];
    argv[0] = "Faust"; // TODO may be should retrieve the actual name
    argv[1] = "-xmit";
    argv[2] = "1"; // TODO retrieve that from command line or somewhere
    argv[3] = "-desthost";
    argv[4] = "192.168.1.1"; // TODO same
    argv[5] = "-port";
    argv[6] = "5510"; // TODO same
    argv[7] = "-outport";
    argv[8] = "5511"; // TODO same
    oscinterface = new OSCUI("Faust", 9, (char**)argv); // TODO fix name
    fPolyEngine->buildUserInterface(oscinterface);
#endif

#if MIDICTRL
    fMidiUI = new MidiUI(new rt_midi());
	fPolyEngine->buildUserInterface(fMidiUI);
#endif
}

DspFaust::~DspFaust(){
#if OSCCTRL
    delete oscinterface;
#endif
#if MIDICTRL
    delete fMidiUI;
#endif
    delete fPolyEngine;
}

bool DspFaust::start(){
#if OSCCTRL
    oscinterface->run();
#endif
#if MIDICTRL
    if (!fMidiUI->run()) {
        std::cerr << "MIDI run error...\n";
    }
#endif
	return fPolyEngine->start();
}

void DspFaust::stop(){
#if OSCCTRL
    oscinterface->stop();
#endif
#if MIDICTRL
    fMidiUI->stop();
#endif
	fPolyEngine->stop();
}

bool DspFaust::configureOSC(bool xmit, int inport, int outport, int errport, const char* address){
#if OSCCTRL
    if (isRunning()) {
        return false;
    } else {
        oscfaust::OSCControler::gXmit = xmit;
        oscinterface->setUDPPort(inport);
        oscinterface->setUDPOut(outport);
        oscinterface->setUDPErr(errport);
        oscinterface->setDestAddress(address);
        return true;
    }
#else
    return false;
#endif
}

bool DspFaust::isRunning(){
	return fPolyEngine->isRunning();
}

unsigned long DspFaust::keyOn(int pitch, int velocity){
	return (unsigned long)fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch){
	return fPolyEngine->keyOff(pitch);
}

unsigned long DspFaust::newVoice(){
	return (unsigned long)fPolyEngine->newVoice();
}

int DspFaust::deleteVoice(long voice){
	return fPolyEngine->deleteVoice(voice);
}

void DspFaust::allNotesOff(){
    fPolyEngine->allNotesOff();
}

void DspFaust::propagateMidi(int count, double time, int type, int channel, int data1, int data2){
    fPolyEngine->propagateMidi(count, time, type, channel, data1, data2);
}

const char* DspFaust::getJSONUI(){
	return fPolyEngine->getJSONUI();
}

const char* DspFaust::getJSONMeta(){
	return fPolyEngine->getJSONMeta();
}

int DspFaust::getParamsCount(){
	return fPolyEngine->getParamsCount();
}

void DspFaust::setParamValue(const char* address, float value){
	fPolyEngine->setParamValue(address, value);
}

void DspFaust::setParamValue(int id, float value){
	fPolyEngine->setParamValue(id, value);
}

float DspFaust::getParamValue(const char* address){
	return fPolyEngine->getParamValue(address);
}

float DspFaust::getParamValue(int id){
	return fPolyEngine->getParamValue(id);
}

void DspFaust::setVoiceParamValue(const char* address, long voice, float value){
	fPolyEngine->setVoiceParamValue(address, voice, value);
}

void DspFaust::setVoiceParamValue(int id, long voice, float value){
	fPolyEngine->setVoiceParamValue(id, voice, value);
}

float DspFaust::getVoiceParamValue(const char* address, long voice){
	return fPolyEngine->getVoiceParamValue(address, voice);
}

float DspFaust::getVoiceParamValue(int id, long voice){
	return fPolyEngine->getVoiceParamValue(id, voice);
}

const char* DspFaust::getParamAddress(int id){
	return fPolyEngine->getParamAddress(id);
}

const char* DspFaust::getVoiceParamAddress(int id, long voice){
	return fPolyEngine->getVoiceParamAddress(id, voice);
}

float DspFaust::getParamMin(const char* address){
    return fPolyEngine->getParamMin(address);
}
      
float DspFaust::getParamMin(int id){
    return fPolyEngine->getParamMin(id);
}
      
float DspFaust::getParamMax(const char* address){
    return fPolyEngine->getParamMax(address);
}
      
float DspFaust::getParamMax(int id){
    return fPolyEngine->getParamMax(id);
}
      
float DspFaust::getParamInit(const char* address){
    return fPolyEngine->getParamInit(address);
}
      
float DspFaust::getParamInit(int id){
    return fPolyEngine->getParamInit(id);
}
      
const char* DspFaust::getParamTooltip(const char* address){
    return fPolyEngine->getParamTooltip(address);
}
      
const char* DspFaust::getParamTooltip(int id){
    return fPolyEngine->getParamTooltip(id);
}

void DspFaust::propagateAcc(int acc, float v){
	fPolyEngine->propagateAcc(acc, v);
}

void DspFaust::setAccConverter(int p, int acc, int curve, float amin, float amid, float amax){
	fPolyEngine->setAccConverter(p, acc, curve, amin, amid, amax);
}

void DspFaust::propagateGyr(int acc, float v){
	fPolyEngine->propagateGyr(acc, v);
}

void DspFaust::setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax){
	fPolyEngine->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

float DspFaust::getCPULoad(){
	return fPolyEngine->getCPULoad();
}

int DspFaust::getScreenColor(){
	return fPolyEngine->getScreenColor();
}

