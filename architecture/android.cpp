/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

/*
 * README:
 * The file only implements the native part of faust2android applications.
 * The native C API is documented at the end of this file in the "Native Faust
 * API" section.
 */

#include <math.h>
#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"
#include "faust/gui/JSONUI.h"

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/poly-dsp.h"

//**************************************************************
// Android Audio
//**************************************************************

#define FAUSTFLOAT float

#include "faust/audio/android-dsp.h"

#include "faust/gui/APIUI.h"

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "dsp_faust.h"
#include <stdio.h>
#include <string.h>

using namespace std;

struct AndroidEngine {

    androidaudio* fDriver;    // the audio engine
    mydsp fMonoDSP;           // the monophonic Faust object
    mydsp_poly* fPolyDSP;     // the polyphonic Faust object
    APIUI fAPIUI;             // the UI description
    JSONUI fJSON;
    string fJSONString;
    bool fRunning;

    int fSampleRate, fBufferSize, fPolyMax;

    AndroidEngine(int sampling_rate, int buffer_size):fJSON(fMonoDSP.getNumInputs(), fMonoDSP.getNumOutputs())
    {
        fPolyDSP = NULL;
        fDriver = NULL;
        fSampleRate = sampling_rate;
        fBufferSize = buffer_size;
        fRunning = false;

        // configuring the UI
        fMonoDSP.buildUserInterface(&fAPIUI);
        fMonoDSP.buildUserInterface(&fJSON);

        fJSONString = fJSON.JSON();

        if (fJSONString.find("keyboard") != std::string::npos ||
            fJSONString.find("poly") != std::string::npos){
            fPolyMax = 6;
            fPolyDSP = new mydsp_poly(fBufferSize, fPolyMax);
            fPolyDSP->init(fSampleRate);
        } else {
            fPolyMax = 0;
        }

        // allocating audio
        fDriver = new androidaudio(fSampleRate, fBufferSize);
    }

    virtual ~AndroidEngine()
    {
        delete fDriver;
        delete fPolyDSP;
    }

    bool init()
    {
        return fDriver->init("Dummy", (fPolyMax == 0) ? &fMonoDSP : (dsp*)fPolyDSP);
    }

    bool start()
    {
        if (!fRunning) {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "REAL start");
            fRunning = fDriver->start();
        }
        return fRunning;
    }

    void stop()
    {
        if (fRunning) {
            fRunning = false;
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "REAL stop");
            fDriver->stop();
        }
    }

    int keyOn(int pitch, int velocity)
    {
        if (fPolyMax > 0) {
            fPolyDSP->keyOn(0, pitch, velocity);
            return 1;
        } else {
            return 0;
        }
    }

    int keyOff(int pitch)
    {
        if (fPolyMax > 0) {
            fPolyDSP->keyOff(0, pitch);
            return 1;
        } else {
            return 0;
        }
    }

    int pitchBend(int refPitch, float pitch)
    {
        if (fPolyMax > 0) {
            fPolyDSP->pitchBend(0, refPitch, pitch);
            return 1;
        } else {
            return 0;
        }
    }

    const char* getJSON()
    {
        return fJSONString.c_str();
    }

    int getParamsCount()
    {
        return fAPIUI.getParamsCount();
    }

    float getParam(const char* address)
    {
        if (fPolyMax == 0) {
            return fAPIUI.getParamValue(fAPIUI.getParamIndex(address));
        } else {
            return fPolyDSP->getValue(address);
        }
    }

    void setParam(const char* address, float value)
    {
        if (fPolyMax == 0) {
            fAPIUI.setParamValue(fAPIUI.getParamIndex(address), value);
        } else {
            fPolyDSP->setValue(address, value);
        }
    }

    int setVoiceParam(const char* address, int pitch, float value)
    {
        if (fPolyMax > 0) {
            fPolyDSP->setValue(address, pitch, value);
            return 1;
        } else {
            return 0;
        }
    }

    int setVoiceGain(int pitch, float gain) {
        if (fPolyMax > 0) {
            fPolyDSP->setVoiceGain(pitch, gain);
            return 1;
        } else {
            return 0;
        }
    }

    const char* getParamAddress(int id) {
        return fAPIUI.getParamName(id);
    }

    void propagateAcc(int acc, float v)
    {
        fAPIUI.propagateAcc(acc, v);
    }

    void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
        fAPIUI.setAccConverter(p, acc, curve, amin, amid, amax);
    }

    void propagateGyr(int gyr, float v)
    {
        fAPIUI.propagateGyr(gyr, v);
    }

    void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Faust", "setGyrConverter %d %d %d %f %f %f", p, gyr, curve, amin, amid, amax);
        fAPIUI.setGyrConverter(p, gyr, curve, amin, amid, amax);
    }

    float getCPULoad() { return fDriver->getCPULoad(); }

    int getScreenColor()
    {
        int c = fAPIUI.getScreenColor();
        __android_log_print(ANDROID_LOG_ERROR, "Faust", "getScreenColor() = %d", c);
        return c;
    }

};

static AndroidEngine* gGlobal = NULL;

/*
 * init(samplingRate, bufferFrames)
 * Initializes the Audio engine and the DSP code
 * with samplingRate and bufferFrames.
 * This method also looks for the [style:poly]
 * metadata in the Faust code and initializes a
 * polyphonic object or not based on that. init
 * should be called before start.
 */
bool init(int sample_rate, int buffer_size)
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI init");
    gGlobal = new AndroidEngine(sample_rate, buffer_size);
    return gGlobal->init();
}

/*
 * start()
 * Begins the processing and return 1 if the connection
 * with the audio device was successful and 0 if not.
 * On Android it also creates the native thread where the
 * DSP tasks will be computed.
 */
bool start()
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI start");
    return gGlobal->start();
}

/*
 * stop()
 * Stops the processing.
 */
void stop()
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI stop");
	 return gGlobal->stop();
}

/*
 * destroy()
 * Destroy the audio engine and related ressources.
 * the native thread on Android.
 */
void destroy()
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI destroy");
    delete gGlobal;
    gGlobal = NULL;
}

/*
 * isRunning()
 * returns true if the DSP frames are being computed and
 * false if not.
 */
bool isRunning()
{
	return (gGlobal != NULL);
}

/*
 * keyOn(pitch, velocity)
 * Instantiates a new polyphonic voice where velocity
 * and pitch are MIDI numbers (0-127). keyOn can only
 * be used if the [style:poly] metadata is used in the
 * Faust code. keyOn will return 0 if the object is not
 * polyphonic and 1 otherwise.
 */
int keyOn(int pitch, int velocity)
{
    return gGlobal->keyOn(pitch, velocity);
}

/*
 * keyOff(pitch)
 * De-instantiates a polyphonic voice where pitch is the
 * MIDI number of the note (0-127). keyOff can only be
 * used if the [style:poly] metadata is used in the Faust
 * code. keyOn will return 0 if the object is not polyphonic
 * and 1 otherwise.
 */
int keyOff(int pitch)
{
	return gGlobal->keyOff(pitch);
}

/*
 * pitchBend(refPitch, pitch)
 * Replaces refPitch in the voice associated with it with pitch.
 * pitch is a MIDI number expressed as a decimal number.
 * pitchBend can only be used if the [style:poly] metadata
 * is used in the Faust code. pitchBend will return 0
 * if the object is not polyphonic and 1 otherwise.
 */
int pitchBend(int refPitch, float pitch)
{
    return gGlobal->pitchBend(refPitch, pitch);
}

/*
 * getJSON()
 * Returns a string containing a JSON description of the
 * UI of the Faust object.
 */
const char* getJSON()
{
    return gGlobal->getJSON();
}

/*
 * getParamsCount()
 * Returns the number of parameters of the Faust object.
 */
int getParamsCount()
{
    return gGlobal->getParamsCount();
}

/*
 * getParam(address)
 * Takes the address of a parameter and returns its current
 * value.
 */
float getParam(const char* address)
{
    return gGlobal->getParam(address);
}

/*
 * setParam(address,value)
 * Sets the value of the parameter associated with address.
 */
void setParam(const char* address, float value)
{
    return gGlobal->setParam(address, value);
}

/*
 * setVoiceParam(address,pitch,value)
 * Sets the value of the parameter associated with address for
 * the voice associated with pitch. setVoiceParam can only be
 * used if the [style:poly] metadata is used in the Faust code.
 * setVoiceParam will return 0 if the object is not polyphonic
 * and 1 otherwise.
 */
int setVoiceParam(const char* address, int pitch, float value)
{
    return gGlobal->setVoiceParam(address, pitch, value);
}

/*
 * setVoiceGain(pitch,gain)
 * Sets the gain (0-1) of the voice associated with pitch.
 * setVoiceGain can only be used if the [style:poly] metadata
 * is used in the Faust code. setVoiceGain will return 0 if the
 * object is not polyphonic and 1 otherwise.
 */
int setVoiceGain(int pitch, float gain)
{
    return gGlobal->setVoiceGain(pitch, gain);
}

/*
 * getParamAddress(id)
 * Returns the address of a parameter in function of its "id".
 */
const char* getParamAddress(int id)
{
    return gGlobal->getParamAddress(id);
}

/*
 * propagateAcc(int acc, float v)
 * Propage accelerometer value to the curve conversion layer.
 */
void propagateAcc(int acc, float v)
{
    gGlobal->propagateAcc(acc, v);
}

/*
 * setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
 * Change accelerometer curve mapping.
 */
void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
{
    //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
    gGlobal->setAccConverter(p, acc, curve, amin, amid, amax);
}

/*
 * propagateGyr(int gyr, float v)
 * Propage gyroscope value to the curve conversion layer.
 */
void propagateGyr(int gyr, float v)
{
    gGlobal->propagateGyr(gyr, v);
}

/*
 * setGyrConverter(int p, int acc, int curve, float amin, float amid, float amax)
 * Change gyroscope curve mapping.
 */
void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
{
    //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
    gGlobal->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

/*
 * getCPULoad()
 * Return DSP CPU load.
 */
float getCPULoad()
{
    return gGlobal->getCPULoad();
}

 /*
 * getScreenColor() -> c:int
 * Get the requested screen color c :
 * c <  0 : no screen color requested (keep regular UI)
 * c >= 0 : requested color (no UI but a colored screen)
 */
 int getScreenColor()
 {
     //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
     return gGlobal->getScreenColor();
 }
