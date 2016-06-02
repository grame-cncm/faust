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

#include <math.h>
#include "faust/misc.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

/*
 * README:
 * The file only implements the native part of faust2android applications.
 * The native C API is documented at the end of this file in the "Native Faust
 * API" section.
 */

//**************************************************************
// Polyphony
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
#include "dsp_faust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

class AndroidEngine : public FaustPolyEngine {

    public:

        AndroidEngine(int srate, int bsize):FaustPolyEngine()
        {
            // allocating audio driver
            fDriver = new androidaudio(srate, bsize);
        }
        
        virtual ~AndroidEngine()
        {}
    
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
float getParamValue(const char* address)
{
    return gGlobal->getParamValue(address);
}

/*
 * setParam(address, value)
 * Sets the value of the parameter associated with address.
 */
void setParamValue(const char* address, float value)
{
    return gGlobal->setParamValue(address, value);
}

/*
 * setVoiceParamValue(address, voice, value)
 * Sets the value of the parameter associated with address for
 * the voice. setVoiceParamValue can only be
 * used if the [style:poly] metadata is used in the Faust code.
 * setVoiceParamValue will return 0 if the object is not polyphonic
 * and 1 otherwise.
 */
int setVoiceParamValue(const char* address, int voice, float value)
{
    return gGlobal->setVoiceParamValue(address, voice, value);
}

/*
 * getVoiceParamValue(address, voice)
 * Gets the parameter value associated with address for the voice.
 * getVoiceParamValue can only be used if the [style:poly] metadata
 * is used in the Faust code. getVoiceParamValue will return 0 if the
 * object is not polyphonic and 1 otherwise.
 */
float getVoiceParamValue(const char* address, int voice)
{
    return gGlobal->getVoiceParamValue(address, voice);
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
    // 05/23/26 : values have to be inverted to behave as with iOS implementation
    gGlobal->propagateAcc(acc, -v);
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
