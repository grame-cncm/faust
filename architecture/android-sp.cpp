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
#include "faust/gui/MapUI.h"

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

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "dsp_faust.h"
#include <stdio.h>
#include <string.h>

using namespace std;

androidaudio* p;                // the audio engine
mydsp mono_dsp;                 // the monophonic Faust object
mydsp_poly* poly_dsp = NULL;    // the polyphonic Faust object
MapUI mapUI;                    // the UI description
JSONUI json(mono_dsp.getNumInputs(), mono_dsp.getNumOutputs());
string jsonString;

// Global variables
int SR, bufferSize, polyMax;
bool on;

/*
 * init(samplingRate, bufferFrames)
 * Initializes the Audio engine and the DSP code
 * with samplingRate and bufferFrames.
 * This method also looks for the [style:poly]
 * metadata in the Faust code and initializes a
 * polyphonic object or not based on that. init
 * should be called before start.
 */
bool init(int samplingRate, int bufferFrames) {
    
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI init");
    
  	// configuring global variables
	SR = samplingRate;
	bufferSize = bufferFrames;

	// configuring the UI
	mono_dsp.buildUserInterface(&mapUI);
	mono_dsp.buildUserInterface(&json);

	jsonString = json.JSON();

    if (jsonString.find("keyboard") != std::string::npos ||
        jsonString.find("poly") != std::string::npos){
        polyMax = 6;
        poly_dsp = new mydsp_poly(bufferSize, polyMax);
        poly_dsp->init(SR);
    } else {
        polyMax = 0;
    }
    
    // allocating audio
    if (!(p = new androidaudio(SR, bufferSize))) return false;
    if (!p->init("Dummy", (polyMax == 0) ? &mono_dsp : (dsp*)poly_dsp)) return false;
    
    return true;
}

/*
 * start()
 * Begins the processing and return 1 if the connection
 * with the audio device was successful and 0 if not.
 * On Android it also creates the native thread where the
 * DSP tasks will be computed.
 */
bool start() {
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI start");
	on = true;
    return p->start();
}

/*
 * stop()
 * Stops the processing.
 */
void stop() {
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI stop");
	on = false;
    p->stop();
}
        
/*
 * destroy()
 * Destroy the audio engine and related ressources.
 * the native thread on Android.
 */
void destroy() {
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI destroy");
    delete p;
    delete poly_dsp;
}

/*
 * isRunning()
 * returns true if the DSP frames are being computed and
 * false if not.
 */
bool isRunning() {
	return on;
}

/*
 * keyOn(pitch, velocity)
 * Instantiates a new polyphonic voice where velocity
 * and pitch are MIDI numbers (0-127). keyOn can only
 * be used if the [style:poly] metadata is used in the
 * Faust code. keyOn will return 0 if the object is not
 * polyphonic and 1 otherwise.
 */
int keyOn(int pitch, int velocity) {
	if (polyMax > 0) {
		poly_dsp->keyOn(0, pitch, velocity);
		return 1;
	} else {
		return 0;
    }
}

/*
 * keyOff(pitch)
 * De-instantiates a polyphonic voice where pitch is the
 * MIDI number of the note (0-127). keyOff can only be
 * used if the [style:poly] metadata is used in the Faust
 * code. keyOn will return 0 if the object is not polyphonic
 * and 1 otherwise.
 */
int keyOff(int pitch) {
	if (polyMax > 0) {
		poly_dsp->keyOff(0, pitch);
		return 1;
	} else {
		return 0;
    }
}

/*
 * pitchBend(refPitch, pitch)
 * Replaces refPitch in the voice associated with it with pitch.
 * pitch is a MIDI number expressed as a decimal number.
 * pitchBend can only be used if the [style:poly] metadata
 * is used in the Faust code. pitchBend will return 0
 * if the object is not polyphonic and 1 otherwise.
 */
int pitchBend(int refPitch, float pitch){
	if (polyMax > 0) {
		poly_dsp->pitchBend(0, refPitch, pitch);
		return 1;
	} else {
		return 0;
    }
}

/*
 * getJSON()
 * Returns a string containing a JSON description of the
 * UI of the Faust object.
 */
const char *getJSON() {
	return jsonString.c_str();
}

/*
 * getParamsCount()
 * Returns the number of parameters of the Faust object.
 */
int getParamsCount() {
	return mapUI.getParamsCount();
}

/*
 * getParam(address)
 * Takes the address of a parameter and returns its current
 * value.
 */
float getParam(const char* address) {
	 return (polyMax == 0) ? mapUI.getValue(address) : poly_dsp->getValue(address);
}

/*
 * setParam(address,value)
 * Sets the value of the parameter associated with address.
 */
void setParam(const char* address, float value) {
	if (polyMax == 0) {
		mapUI.setValue(address, value);
	} else {
		poly_dsp->setValue(address, value);
    }
}

/*
 * setVoiceParam(address,pitch,value)
 * Sets the value of the parameter associated with address for
 * the voice associated with pitch. setVoiceParam can only be
 * used if the [style:poly] metadata is used in the Faust code.
 * setVoiceParam will return 0 if the object is not polyphonic
 * and 1 otherwise.
 */
int setVoiceParam(const char* address, int pitch, float value) {
	if (polyMax > 0) {
		poly_dsp->setValue(address, pitch, value);
		return 1;
	} else {
        return 0;
    }
}

/*
 * setVoiceGain(pitch,gain)
 * Sets the gain (0-1) of the voice associated with pitch.
 * setVoiceGain can only be used if the [style:poly] metadata
 * is used in the Faust code. setVoiceGain will return 0 if the
 * object is not polyphonic and 1 otherwise.
 */
int setVoiceGain(int pitch, float gain) {
	if (polyMax > 0) {
		poly_dsp->setVoiceGain(pitch, gain);
		return 1;
	} else {
        return 0;
    }
}

/*
 * getParamAddress(id)
 * Returns the address of a parameter in function of its "id".
 */
const char *getParamAddress(int id) {
	return mapUI.getParamPath(id).c_str();
}
