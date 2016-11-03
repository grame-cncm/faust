/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Audio engine
//**************************************************************

#include "faust/dsp/faust-poly-engine.h"

//**************************************************************
// Android Audio
//**************************************************************

#include "faust/audio/android-dsp.h"

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(int sample_rate, int buffer_size){
    fPolyEngine = new FaustPolyEngine(new androidaudio(sample_rate, buffer_size));
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

unsigned long DspFaust::keyOn(int pitch, int velocity){
    return (long) fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch){
    return fPolyEngine->keyOff(pitch);
}

void DspFaust::propagateMidi(int count, double time, int type, int channel, int data1, int data2){
    fPolyEngine->propagateMidi(count, time, type, channel, data1, data2);
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

float DspFaust::getParamValue(const char* address){
    return fPolyEngine->getParamValue(address);
}

void DspFaust::setVoiceParamValue(const char* address, unsigned long voice, float value){
    fPolyEngine->setVoiceParamValue(address, voice, value);
}

float DspFaust::getVoiceParamValue(const char* address, unsigned long voice){
    return fPolyEngine->getVoiceParamValue(address, voice);
}

const char* DspFaust::getParamAddress(int id){
    return fPolyEngine->getParamAddress(id);
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

