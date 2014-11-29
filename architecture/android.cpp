/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
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
 * It uses a modified version of Victor Lazzarini's opensl_io (available at:
 * https://bitbucket.org/victorlazzarini/android-audiotest) adapted to Faust
 * to minimize latency.
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

#include "faust/audio/poly-dsp.h"

//**************************************************************
// Android Audio (modified opensl_io)
//**************************************************************

#include "faust/audio/opensles-android-dsp.h"

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "dsp_faust.h"
#include <stdio.h>
#include <string.h>

#define FAUSTFLOAT float

using namespace std;

OPENSL_STREAM *p; // the audio engine
mydsp DSP; // the monophonic Faust object
mydsp_poly *DSPpoly; // the polyphonic Faust object
MapUI mapUI; // the UI description
pthread_t audioThread; // native thread for audio
JSONUI json(DSP.getNumInputs(), DSP.getNumOutputs());
string jsonString;

// Global variables
int SR, bufferSize, vecSamps, polyMax, inChanNumb, outChanNumb, on;
float **bufferout, **bufferin, polyCoef;

/*
 * init(samplingRate, bufferFrames)
 * Initialize a monophonic Faust object. This function should be
 * called before using start(). If this function was used to initialize
 * the Faust process, keyOn() and keyOff() are not available.
 */
void init(int samplingRate, int bufferFrames) {
	// configuring global variables
	SR = samplingRate;
	bufferSize = bufferFrames;
	vecSamps = bufferSize;
	DSP.init(SR);
	inChanNumb = DSP.getNumInputs();
	outChanNumb = DSP.getNumOutputs();

	// configuring the UI
	DSP.buildUserInterface(&mapUI);
	DSP.buildUserInterface(&json);

	jsonString = json.JSON();

	if(jsonString.find("keyboard") != std::string::npos ||
       jsonString.find("poly") != std::string::npos){
		polyMax = 4;
		polyCoef = 1.0f / polyMax;
		DSPpoly = new mydsp_poly(SR, bufferSize, polyMax);
	}
	else{
		polyMax = 0;
	}

	// allocating memory for output channel
	bufferout = new float *[outChanNumb];
	for (int i = 0; i < outChanNumb; i++) {
		bufferout[i] = new float[vecSamps];
	}

	// allocating memory for input channel
	if (inChanNumb >= 1) {
		bufferin = new float *[inChanNumb];
		for (int i = 0; i < inChanNumb; i++) {
			bufferin[i] = new float[vecSamps];
		}
	}
}

/*
 * processDSP(threadID)
 * Compute the DSP frames of the Faust object.
 */
void *processDSP(void *threadID) {
	while (on) {
		// getting input signal
		if (inChanNumb >= 1)
			android_AudioIn(p, bufferin[0], vecSamps);

		// computing...
		if (polyMax == 0)
			DSP.compute(vecSamps, bufferin, bufferout);
		else
			DSPpoly->compute(vecSamps, bufferin, bufferout);

		// sending output signal
		android_AudioOut(p, bufferout, vecSamps);
	}
}

/*
 * start()
 * Open the audio engine and create a new thread for the Faust
 * process computation.
 * The number of input channels is limited to 1 and the number of
 * output channel to 2 to meet the requirements of most Android
 * devices. If the Faust object has more than one input or more
 * than two outputs, these will be computed but also discarded.
 * start() will return 1 if the audio engine was successfully launched
 * and 0 otherwise.
 */
int start() {
	on = 1;
	p = android_OpenAudioDevice(SR, min(1, inChanNumb),
			min(2, outChanNumb), bufferSize);
	pthread_create(&audioThread, NULL, processDSP, NULL);
	if(p == NULL)
		return 0;
	else
		return 1;
}

/*
 * stop()
 * Stops the audio process, closes the audio engine and frees
 * the memory.
 */
void stop() {
	on = 0;
	pthread_join(audioThread, 0);
	android_CloseAudioDevice(p);
	delete[] bufferin;
	delete[] *bufferout;
	delete[] bufferout;
}

/*
 * isRunning()
 * returns true if the DSP frames are being computed and
 * false if not.
 */
bool isRunning() {
	if (on == 1)
		return true;
	else
		return false;
}

/*
 * keyOn(pitch, velocity)
 * Instantiate a new polyphonic voice where velocity and pitch are
 * MIDI numbers (0-127). keyOn can only be used if initPoly was used
 * to initialize the system.
 */
int keyOn(int pitch, int velocity) {
	if(polyMax > 0){
		DSPpoly->keyOn(0, pitch, velocity);
		return 1;
	}
	else
		return 0;
}

/*
 * keyOff(pitch)
 * Deinstantiate a polyphonic voice where pitch is the MIDI number
 * of the note (0-127). keyOff can only be used if initPoly was used
 * to initialize the system.
 */
int keyOff(int pitch) {
	if(polyMax > 0){
		DSPpoly->keyOff(0, pitch);
	}
	else
		return 0;
}

/*
 * pitchBend(refPitch, pitch)
 * Bends the pitch of refPitch. Pitch is float and is expressed as a MIDI
 * number
 */
int pitchBend(int refPitch, float pitch){
	if(polyMax > 0){
		DSPpoly->pitchBend(refPitch, pitch);
	}
	else
		return 0;
}

/*
 * getJSON()
 * Returns a string containing a JSON description of the
 * UI of the Faust object.
 */
const char *getJSON() {
	return strdup(jsonString.c_str());
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
	if (polyMax == 0)
		return mapUI.getValue(address);
	else
		return DSPpoly->getValue(address);
}

/*
 * setParam(address,value)
 * Set the value of the parameter associated with address.
 */
void setParam(const char* address, float value) {
	if (polyMax == 0)
		mapUI.setValue(address, value);
	else
		DSPpoly->setValue(address, value);
	//__android_log_print(ANDROID_LOG_VERBOSE, "Echo", "Foucou: %s",address);
}

/*
 * setParam(address,value)
 * Set the value of the parameter associated with address and voice.
 */
void setVoiceParam(const char* address, int pitch, float value) {
	DSPpoly->setValue(address, pitch, value);
}

/*
 * setVoiceGain(pitch,gain)
 * Set the gain of a voice where gain is between 0 and 1.
 */
void setVoiceGain(int pitch, float gain){
	setVoiceParam(DSPpoly->fGainLabel.c_str(),pitch,gain);
}

/*
 * getParamAddress(id)
 * Returns the address of a parameter in function of its "id".
 */
const char *getParamAddress(int id) {
	return strdup(mapUI.getParamPath(id).c_str());
}
