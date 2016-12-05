/************************************************************************
 ************************************************************************
 FAUST API Architecture File 
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2016 GRAME, Centre National de Creation Musicale
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
#include "faust/gui/jsonfaustui.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"

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
// IOS Coreaudio
//**************************************************************

#include "faust/audio/coreaudio-ios-dsp.h"

//**************************************************************
// Interface
//**************************************************************

#if IOS_MIDI_SUPPORT
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(int sample_rate, int buffer_size){
    fPolyEngine = new FaustPolyEngine(new iosaudio(sample_rate, buffer_size));
    
    #if IOS_MIDI_SUPPORT
    fPolyEngine->buildUserInterface(new MidiUI(new rt_midi()));
    #endif
}

DspFaust::~DspFaust(){
    delete fPolyEngine;
}

bool DspFaust::start(){
    return fPolyEngine->start();
}

void DspFaust::stop(){
    fPolyEngine->stop();
}

bool DspFaust::isRunning(){
    return fPolyEngine->isRunning();
}

long DspFaust::keyOn(int pitch, int velocity){
    return (long) fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch){
    return fPolyEngine->keyOff(pitch);
}

long DspFaust::newVoice(){
    return (long) fPolyEngine->newVoice();
}

int DspFaust::deleteVoice(long voice){
    return fPolyEngine->deleteVoice(voice);
}

const char* DspFaust::getJSON(){
    return fPolyEngine->getJSON();
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

