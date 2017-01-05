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

#ifndef __ios_api__
#define __ios_api__

//===============API Reference==============
//==========================================

class FaustPolyEngine;
class MidiUI;

class DspFaust
{
public:
	//--------------`DspFaust(int SR, int BS)`----------------
	// Constructor.
	//
	// #### Arguments
	//
	// * `SR`: sampling rate
	// * `BS`: block size
	//--------------------------------------------------------
	DspFaust(int,int);
	~DspFaust();
	
	//---------------------`bool start()`---------------------
	// Start the audio processing.
	//
	// Returns `true` if successful and `false` if not.
	//--------------------------------------------------------
	bool start();
	
	//-----------------`void stop()`--------------------------
	// Stop the audio processing. 
	//--------------------------------------------------------
	void stop();
	
	//---------------------`bool isRunning()`-----------------
	// Returns `true` if audio is running.
	//--------------------------------------------------------
	bool isRunning();
	
	//--------`long keyOn(int pitch, int velocity)`-----------
	// Instantiate a new polyphonic voice. This method can
	// only be used if the `[style:poly]` metadata is used in
	// the Faust code or if the `-polyvoices` flag has been
	// provided before compilation.
	//
	// `keyOn` will return 0 if the Faust object is not
	// polyphonic or the address to the allocated voice as
	// a `long` otherwise. This value can be used later with
	// [`setVoiceParamValue`](#setvoiceparamvalue) or
	// [`getVoiceParamValue`](#getvoiceparamvalue) to access
	// the parameters of a specific voice.
	//
	// #### Arguments
	//
	// * `pitch`: MIDI note number (0-127)
	// * `velocity`: MIDI velocity (0-127)
	//--------------------------------------------------------
	long keyOn(int, int);
	
	//----------------`int keyOff(int pitch)`-----------------
	// De-instantiate a polyphonic voice. This method can
	// only be used if the `[style:poly]` metadata is used in
	// the Faust code or if the `-polyvoices` flag has been
	// provided before compilation.
	//
	// `keyOff` will return 0 if the object is not polyphonic
	// and 1 otherwise.
	//
	// #### Arguments
	//
	// * `pitch`: MIDI note number (0-127), should be the same
	// as the one used for `keyOn`
	//--------------------------------------------------------
	int keyOff(int);
	
	//-------------------`long newVoice()`--------------------
	// Instantiate a new polyphonic voice. This method can
	// only be used if the `[style:poly]` metadata is used in
	// the Faust code or if `-polyvoices` flag has been
	// provided before compilation.
	//
	// `keyOn` will return 0 if the Faust object is not
	// polyphonic or the address to the allocated voice as
	// a `long` otherwise. This value can be used later with
	// `setVoiceParamValue`, `getVoiceParamValue` or
	// `deleteVoice` to access the parameters of a specific
	// voice.
	//--------------------------------------------------------
	long newVoice();
	
	//---------`int deleteVoice(long voice)`------------------
	// De-instantiate a polyphonic voice. This method can
	// only be used if the `[style:poly]` metadata is used in
	// the Faust code or if `-polyvoices` flag has been
	// provided before compilation.
	//
	// `deleteVoice` will return 0 if the object is not polyphonic
	// and 1 otherwise.
	//
	// #### Arguments
	//
	// * `voice`: the address of the voice given by `newVoice`
	//--------------------------------------------------------
	int deleteVoice(long);

	//-----------------`void allNotesOff()`----------------
	// Gently terminates all the active voices. 
	//--------------------------------------------------------
	void allNotesOff();
	
	//-----------------`const char* getJSONUI()`----------------
	// Returns the JSON description of the UI of the Faust object. 
	//--------------------------------------------------------
	const char* getJSONUI();

	//-----------------`const char* getJSONMeta()`----------------
	// Returns the JSON description of the metadata of the Faust object. 
	//--------------------------------------------------------
	const char* getJSONMeta();
	
	//-----------------`int getParamsCount()`-----------------
	// Returns the number of parameters of the Faust object. 
	//--------------------------------------------------------
	int getParamsCount();
	
	//----`void setParamValue(const char* address, float value)`------
	// Set the value of one of the parameters of the Faust
	// object in function of its address (path).
	//
	// #### Arguments
	//
	// * `address`: address (path) of the parameter
	// * `value`: value of the parameter
	//--------------------------------------------------------
	void setParamValue(const char*, float);
	
	//----`void setParamValue(int id, float value)`---
	// Set the value of one of the parameters of the Faust
	// object in function of its id.
	//
	// #### Arguments
	//
	// * `id`: id of the parameter
	// * `value`: value of the parameter
	//--------------------------------------------------------
	void setParamValue(int, float);
	
	//----`float getParamValue(const char* address)`----------
	// Returns the value of a parameter in function of its
	// address (path).
	//
	// #### Arguments
	//
	// * `address`: address (path) of the parameter
	//--------------------------------------------------------
	float getParamValue(const char*);
	
	//---------`float getParamValue(int id)`----------
	// Returns the value of a parameter in function of its
	// id.
	//
	// #### Arguments
	//
	// * `id`: id of the parameter
	//--------------------------------------------------------
	float getParamValue(int);
	
	//----`void setVoiceParamValue(const char* address, long voice, float value)`-----
	// Set the value of one of the parameters of the Faust
	// object in function of its address (path) for a
	// specific voice.
	//
	// #### Arguments
	//
	// * `address`: address (path) of the parameter
	// * `voice`: address of the polyphonic voice (retrieved
	// from `keyOn`
	// * `value`: value of the parameter
	//--------------------------------------------------------
	void setVoiceParamValue(const char*, long, float);
	
	//----`void setVoiceValue(int id, long voice, float value)`-----
	// Set the value of one of the parameters of the Faust
	// object in function of its id for a
	// specific voice.
	//
	// #### Arguments
	//
	// * `id`: id of the parameter
	// * `voice`: address of the polyphonic voice (retrieved
	// from `keyOn`
	// * `value`: value of the parameter
	//--------------------------------------------------------
	void setVoiceParamValue(int, long, float);
	
	//----`float getVoiceParamValue(const char* address, long voice)`----
	// Returns the value of a parameter in function of its
	// address (path) for a specific voice.
	//
	// #### Arguments
	//
	// * `address`: address (path) of the parameter
	// * `voice`: address of the polyphonic voice (retrieved
	// from `keyOn`)
	//--------------------------------------------------------
	float getVoiceParamValue(const char*, long);
	
	//----`float getVoiceParamValue(int id, long voice)`----
	// Returns the value of a parameter in function of its
	// id for a specific voice.
	//
	// #### Arguments
	//
	// * `id`: id of the parameter
	// * `voice`: address of the polyphonic voice (retrieved
	// from `keyOn`)
	//--------------------------------------------------------
	float getVoiceParamValue(int, long);
	
	//----`const char* getParamAddress(int id)`---------------
	// Returns the address (path) of a parameter in function
	// of its ID.
	//
	// #### Arguments
	//
	// * `id`: id of the parameter
	//--------------------------------------------------------
	const char* getParamAddress(int);
	
	//----`const char* getVoiceParamAddress(int id, long voice)`-----
	// Returns the address (path) of a parameter in function
	// of its ID.
	//
	// #### Arguments
	//
	// * `id`: id of the parameter
	// * `voice`: address of the polyphonic voice (retrieved
	// from `keyOn`)
	//--------------------------------------------------------
	const char* getVoiceParamAddress(int, long);
	
    //-------`float getParamMin(const char* address)`---------
    // Returns the minimum value of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamMin(const char*);
    
    //--------------`float getParamMin(int id)`---------------
    // Returns the minimum value of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamMin(int);
    
    //-------`float getParamMax(const char* address)`---------
    // Returns the maximum value of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamMax(const char*);
    
    //--------------`float getParamMax(int id)`---------------
    // Returns the maximum value of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamMax(int);
    
    //-------`float getParamInit(const char* address)`---------
    // Returns the default value of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamInit(const char*);
    
    //--------------`float getParamInit(int id)`---------------
    // Returns the default value of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamInit(int);
    
    //-----`const char* getParamTooltip(const char* address)`-----
    // Returns the tooltip (description) of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    const char* getParamTooltip(const char*);
    
    //----`const char* getParamTooltip(int id)`---------------
    // Returns the tooltip (description) of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    const char* getParamTooltip(int);
	
	//----`void propagateAcc(int acc, float v)`---------------
	// Propagate the RAW value of a specific accelerometer
	// axis to the Faust object.
	//
	// #### Arguments
	//
	// * `acc`: the accelerometer axis (**0**: x, **1**: y, **2**: z)
	// * `v`: the RAW acceleromter value in m/s
	//--------------------------------------------------------
	void propagateAcc(int, float);
	
	//----`void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)`-----
	// Set the conversion curve for the accelerometer.
	//
	// #### Arguments
	//
	// * `p`: the UI parameter id
	// * `acc`: the accelerometer axis (**0**: x, **1**: y, **2**: z)
	// * `curve`: the curve (**0**: up, **1**: down, **2**: up and down)
	// * `amin`: mapping min point
	// * `amid`: mapping middle point
	// * `amax`: mapping max point
	//--------------------------------------------------------
	// TODO: eventually should add a link to tutorials on this in the doc
	void setAccConverter(int, int, int, float, float, float);
	
	//----`void propagateGyr(int gyr, float v)`---------------
	// Propagate the RAW value of a specific gyroscope
	// axis to the Faust object.
	//
	// #### Arguments
	//
	// * `gyr`: the gyroscope axis (**0**: x, **1**: y, **2**: z)
	// * `v`: the RAW acceleromter value in m/s
	//--------------------------------------------------------
	void propagateGyr(int, float);
	
	//----`void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)`-----
	// Set the conversion curve for the gyroscope.
	//
	// #### Arguments
	//
	// * `p`: the UI parameter id
	// * `acc`: the accelerometer axis (**0**: x, **1**: y, **2**: z)
	// * `curve`: the curve (**0**: up, **1**: down, **2**: up and down)
	// * `amin`: mapping min point
	// * `amid`: mapping middle point
	// * `amax`: mapping max point
	//--------------------------------------------------------
	// TODO: eventually should add a link to tutorials on this in the doc
	void setGyrConverter(int, int, int, float, float, float);
	
	//------------------`float getCPULoad()`------------------
	// Returns the CPU load.
	//--------------------------------------------------------
	float getCPULoad();
	
	int getScreenColor();
	
private:
    FaustPolyEngine *fPolyEngine;
    MidiUI *fMidiUI;
};

#endif
