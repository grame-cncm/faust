/************************************************************************

    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
	Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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

unsigned long DspFaust::keyOn(int pitch, int velocity){
    return (long) fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch){
    return fPolyEngine->keyOff(pitch);
}

unsigned long DspFaust::newVoice(){
    return (long) fPolyEngine->newVoice();
}

int DspFaust::deleteVoice(unsigned long voice){
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

void DspFaust::setVoiceParamValue(const char* address, unsigned long voice, float value){
    fPolyEngine->setVoiceParamValue(address, voice, value);
}

void DspFaust::setVoiceParamValue(int id, unsigned long voice, float value){
    fPolyEngine->setVoiceParamValue(id, voice, value);
}

float DspFaust::getVoiceParamValue(const char* address, unsigned long voice){
    return fPolyEngine->getVoiceParamValue(address, voice);
}

float DspFaust::getVoiceParamValue(int id, unsigned long voice){
    return fPolyEngine->getVoiceParamValue(id, voice);
}

const char* DspFaust::getParamAddress(int id){
    return fPolyEngine->getParamAddress(id);
}

const char* DspFaust::getVoiceParamAddress(int id, unsigned long voice){
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

