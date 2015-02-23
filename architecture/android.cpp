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

OPENSL_STREAM *p;           // the audio engine
mydsp DSP;                  // the monophonic Faust object
mydsp_poly *DSPpoly = NULL; // the polyphonic Faust object
MapUI mapUI;                // the UI description
pthread_t audioThread;      // native thread for audio
JSONUI json(DSP.getNumInputs(), DSP.getNumOutputs());
string jsonString;

// Global variables
int SR, bufferSize, vecSamps, polyMax, inChanNumb, outChanNumb;
float **bufferout, **bufferin;
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

    if (jsonString.find("keyboard") != std::string::npos ||
        jsonString.find("poly") != std::string::npos){
        polyMax = 6;
        DSPpoly = new mydsp_poly(bufferSize, polyMax);
        DSPpoly->init(SR);
    } else {
        polyMax = 0;
    }

	// Allocating memory for output channels. Only the first two channels
	// are played. Additional output channels are ignored.
	bufferout = new float *[outChanNumb];
	for (int i = 0; i < outChanNumb; i++) {
		bufferout[i] = new float[vecSamps];
	}

	// Allocating memory for input channel. We assume no more than
	// one physical input channel. Additional input channels will 
	// share the content of input channel 0.
	if (inChanNumb >= 1) {
		bufferin = new float *[inChanNumb];
		bufferin[0] = new float[vecSamps];
		for (int i = 1; i < inChanNumb; i++) {
			bufferin[i] = bufferin[0];
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
		if (inChanNumb >= 1) {
			android_AudioIn(p, bufferin[0], vecSamps);
        }

		// computing...
		if (polyMax == 0) {
			DSP.compute(vecSamps, bufferin, bufferout);
		} else {
			DSPpoly->compute(vecSamps, bufferin, bufferout);
        }

		// sending output signal
		android_AudioOut(p, bufferout, vecSamps);
	}
}

/*
 * start()
 * Begins the processing and return 1 if the connection
 * with the audio device was successful and 0 if not.
 * On Android it also creates the native thread where the
 * DSP tasks will be computed.
 */
bool start() {
	on = true;
	p = android_OpenAudioDevice(SR, min(1, inChanNumb), min(2, outChanNumb), bufferSize);
	pthread_create(&audioThread, NULL, processDSP, NULL);
	return (p != NULL);
}

/*
 * stop()
 * Stops the processing, closes the audio engine and terminates
 * the native thread on Android.
 */
void stop() {
	on = false;
	pthread_join(audioThread, 0);
	android_CloseAudioDevice(p);
	for (int i = 0; i < outChanNumb; i++) {
		delete[] bufferout[i];
	}
	delete[] bufferout;
	if (inChanNumb >= 1) {
		for (int i = 0; i < inChanNumb; i++) {
			delete[] bufferin[i];
		}
		delete[] bufferin;
	}
	delete DSPpoly;
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
		DSPpoly->keyOn(0, pitch, velocity);
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
		DSPpoly->keyOff(0, pitch);
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
		DSPpoly->pitchBend(0, refPitch, pitch);
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
	 return (polyMax == 0) ? mapUI.getValue(address) : DSPpoly->getValue(address);
}

/*
 * setParam(address,value)
 * Sets the value of the parameter associated with address.
 */
void setParam(const char* address, float value) {
	if (polyMax == 0) {
		mapUI.setValue(address, value);
	} else {
		DSPpoly->setValue(address, value);
    }
	//__android_log_print(ANDROID_LOG_VERBOSE, "Echo", "Foucou: %s",address);
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
		DSPpoly->setValue(address, pitch, value);
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
		DSPpoly->setVoiceGain(pitch, gain);
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
