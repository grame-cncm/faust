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

#include <math.h>
#include <cmath>

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/meta.h"

//**************************************************************
// OSC configuration (hardcoded for now...)
//**************************************************************

#define OSC_IP_ADDRESS  "192.168.1.1"
#define OSC_IN_PORT     "5510"
#define OSC_OUT_PORT    "5511"

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
#if JACK_DRIVER
    // Nothing to add since jack-dsp.h contains MIDI
#elif JUCE_DRIVER
    #include "faust/midi/juce-midi.h"
#else
    #include "faust/midi/rt-midi.h"
    #include "faust/midi/RtMidi.cpp"
#endif
#endif

#if OSCCTRL
#if JUCE_DRIVER
    #include "faust/gui/JuceOSCUI.h"
#else
    #include "faust/gui/OSCUI.h"
#endif
#endif

#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust()
{
    audio* driver = 0;
#if JACK_DRIVER
    // JACK has its own sample rate and buffer size
#if MIDICTRL
    driver = new jackaudio_midi();
#else
    driver = new jackaudio();
#endif
#elif JUCE_DRIVER
    // JUCE audio device has its own sample rate and buffer size
    driver = new juceaudio();
#else
    std::cout << "You are not setting 'sample_rate' and 'buffer_size', but the audio driver needs it !\n";
    throw std::bad_alloc();
#endif
    init(driver);
}

DspFaust::DspFaust(int sample_rate, int buffer_size)
{
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
    std::cout << "You are setting 'sample_rate' and 'buffer_size' with a driver that does not need it !\n";
#if MIDICTRL
    audio* driver = new jackaudio_midi();
#else
    audio* driver = new jackaudio();
#endif
#elif PORTAUDIO_DRIVER
    audio* driver = new portaudio(sample_rate, buffer_size);
#elif RTAUDIO_DRIVER
    audio* driver = new rtaudio(sample_rate, buffer_size);
#elif OPEN_FRAMEWORK_DRIVER
    audio* driver = new ofaudio(sample_rate, buffer_size);
#elif JUCE_DRIVER
    // JUCE audio device has its own sample rate and buffer size
    std::cout << "You are setting 'sample_rate' and 'buffer_size' with a driver that does not need it !\n";
    audio* driver = new juceaudio();
#elif DUMMY_DRIVER
    audio* driver = new dummyaudio(sample_rate, buffer_size);
#endif
    
    init(driver);
}
 
void DspFaust::init(audio* driver)
{
    fPolyEngine = new FaustPolyEngine(driver);
    
#if OSCCTRL
#if JUCE_DRIVER
    fOSCInterface = new JuceOSCUI(OSC_IP_ADDRESS, atoi(OSC_IN_PORT), atoi(OSC_OUT_PORT));
#else
    const char* argv[9];
    argv[0] = "Faust";  // TODO may be should retrieve the actual name
    argv[1] = "-xmit";
    argv[2] = "1";      // TODO retrieve that from command line or somewhere
    argv[3] = "-desthost";
    argv[4] = OSC_IP_ADDRESS;   // TODO same
    argv[5] = "-port";
    argv[6] = OSC_IN_PORT;      // TODO same
    argv[7] = "-outport";
    argv[8] = OSC_OUT_PORT;     // TODO same
    fOSCInterface = new OSCUI("Faust", 9, (char**)argv); // TODO fix name
#endif
    fPolyEngine->buildUserInterface(fOSCInterface);
#endif
    
#if MIDICTRL
#if JACK_DRIVER
    fMidiUI = new MidiUI(static_cast<jackaudio_midi*>(driver));
#elif JUCE_DRIVER
    fMidiUI = new MidiUI(new juce_midi(), true);
#else
    fMidiUI = new MidiUI(new rt_midi(), true);
#endif
    fPolyEngine->buildUserInterface(fMidiUI);
#endif
}

DspFaust::~DspFaust()
{
#if OSCCTRL
    delete fOSCInterface;
#endif
#if MIDICTRL
    delete fMidiUI;
#endif
    delete fPolyEngine;
}

bool DspFaust::start()
{
#if OSCCTRL
    fOSCInterface->run();
#endif
#if MIDICTRL
    if (!fMidiUI->run()) {
        std::cout << "MIDI run error...\n";
    }
#endif
	return fPolyEngine->start();
}

void DspFaust::stop()
{
#if OSCCTRL
    fOSCInterface->stop();
#endif
#if MIDICTRL
    fMidiUI->stop();
#endif
	fPolyEngine->stop();
}

bool DspFaust::configureOSC(bool xmit, int inport, int outport, int errport, const char* address)
{
#if OSCCTRL
#if JUCE_DRIVER
    // Nothing got now
    return false;
#else
    if (isRunning()) {
        return false;
    } else {
        oscfaust::OSCControler::gXmit = xmit;
        fOSCInterface->setUDPPort(inport);
        fOSCInterface->setUDPOut(outport);
        fOSCInterface->setUDPErr(errport);
        fOSCInterface->setDestAddress(address);
        return true;
    }
#endif
#else
    return false;
#endif
}

bool DspFaust::isRunning()
{
	return fPolyEngine->isRunning();
}

unsigned long DspFaust::keyOn(int pitch, int velocity)
{
	return (unsigned long)fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch)
{
	return fPolyEngine->keyOff(pitch);
}

unsigned long DspFaust::newVoice()
{
	return (unsigned long)fPolyEngine->newVoice();
}

int DspFaust::deleteVoice(long voice)
{
	return fPolyEngine->deleteVoice(voice);
}

void DspFaust::allNotesOff()
{
    fPolyEngine->allNotesOff();
}

void DspFaust::propagateMidi(int count, double time, int type, int channel, int data1, int data2)
{
    fPolyEngine->propagateMidi(count, time, type, channel, data1, data2);
}

const char* DspFaust::getJSONUI()
{
	return fPolyEngine->getJSONUI();
}

const char* DspFaust::getJSONMeta()
{
	return fPolyEngine->getJSONMeta();
}

int DspFaust::getParamsCount()
{
	return fPolyEngine->getParamsCount();
}

void DspFaust::setParamValue(const char* address, float value)
{
	fPolyEngine->setParamValue(address, value);
}

void DspFaust::setParamValue(int id, float value)
{
	fPolyEngine->setParamValue(id, value);
}

float DspFaust::getParamValue(const char* address)
{
	return fPolyEngine->getParamValue(address);
}

float DspFaust::getParamValue(int id)
{
	return fPolyEngine->getParamValue(id);
}

void DspFaust::setVoiceParamValue(const char* address, long voice, float value)
{
	fPolyEngine->setVoiceParamValue(address, voice, value);
}

void DspFaust::setVoiceParamValue(int id, long voice, float value)
{
	fPolyEngine->setVoiceParamValue(id, voice, value);
}

float DspFaust::getVoiceParamValue(const char* address, long voice)
{
	return fPolyEngine->getVoiceParamValue(address, voice);
}

float DspFaust::getVoiceParamValue(int id, long voice)
{
	return fPolyEngine->getVoiceParamValue(id, voice);
}

const char* DspFaust::getParamAddress(int id)
{
	return fPolyEngine->getParamAddress(id);
}

const char* DspFaust::getVoiceParamAddress(int id, long voice)
{
	return fPolyEngine->getVoiceParamAddress(id, voice);
}

float DspFaust::getParamMin(const char* address)
{
    return fPolyEngine->getParamMin(address);
}
      
float DspFaust::getParamMin(int id)
{
    return fPolyEngine->getParamMin(id);
}
      
float DspFaust::getParamMax(const char* address)
{
    return fPolyEngine->getParamMax(address);
}
      
float DspFaust::getParamMax(int id)
{
    return fPolyEngine->getParamMax(id);
}
      
float DspFaust::getParamInit(const char* address)
{
    return fPolyEngine->getParamInit(address);
}
      
float DspFaust::getParamInit(int id)
{
    return fPolyEngine->getParamInit(id);
}
      
const char* DspFaust::getParamTooltip(const char* address)
{
    return fPolyEngine->getParamTooltip(address);
}
      
const char* DspFaust::getParamTooltip(int id)
{
    return fPolyEngine->getParamTooltip(id);
}

void DspFaust::propagateAcc(int acc, float v)
{
	fPolyEngine->propagateAcc(acc, v);
}

void DspFaust::setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
{
	fPolyEngine->setAccConverter(p, acc, curve, amin, amid, amax);
}

void DspFaust::propagateGyr(int acc, float v)
{
	fPolyEngine->propagateGyr(acc, v);
}

void DspFaust::setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
{
	fPolyEngine->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

float DspFaust::getCPULoad()
{
	return fPolyEngine->getCPULoad();
}

int DspFaust::getScreenColor()
{
	return fPolyEngine->getScreenColor();
}

