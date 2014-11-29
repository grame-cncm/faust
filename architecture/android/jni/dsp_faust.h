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
 * init(samplingRate, bufferFrames)
 * Initialize a monophonic Faust object. This function should be
 * called before using start(). If this function was used to initialize
 * the Faust process, keyOn() and keyOff() are not available.
 */
void init(int, int);

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
int start(void);

/*
 * stop()
 * Stops the audio process, closes the audio engine and frees
 * the memory.
 */
void stop(void);

/*
 * isRunning()
 * returns true if the DSP frames are being computed and
 * false if not.
 */
bool isRunning(void);

/*
 * keyOn(pitch, velocity)
 * Instantiate a new polyphonic voice where velocity and pitch are
 * MIDI numbers (0-127). keyOn can only be used if initPoly was used
 * to initialize the system.
 */
int keyOn(int, int);

/*
 * keyOff(pitch)
 * Deinstantiate a polyphonic voice where pitch is the MIDI number
 * of the note (0-127). keyOff can only be used if initPoly was used
 * to initialize the system.
 */
int keyOff(int);

/*
 * pitchBend(refPitch, pitch)
 * Bends the pitch of refPitch. Pitch is float and is expressed as a MIDI
 * number
 */
int pitchBend(int, float);

/*
 * getJSON()
 * Returns a string containing a JSON description of the
 * UI of the Faust object.
 */
const char *getJSON(void);

/*
 * getParamsCount()
 * Returns the number of parameters of the Faust object.
 */
int getParamsCount(void);

/*
 * getParam(address)
 * Takes the address of a parameter and returns its current
 * value.
 */
float getParam(const char*);

/*
 * setParam(address,value)
 * Set the value of the parameter associated with address.
 */
void setParam(const char*, float);

/*
 * setParam(address,voice,value)
 * Set the value of the parameter associated with address and voice.
 */
void setVoiceParam(const char*, int, float);

/*
 * setVoiceGain(pitch,gain)
 * Set the gain of a voice where gain is between 0 and 1.
 */
void setVoiceGain(int, float);

/*
 * getParamAddress(id)
 * Returns the address of a parameter in function of its "id".
 */
const char *getParamAddress(int);

