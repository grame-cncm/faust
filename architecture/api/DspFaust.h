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

#ifndef __faust_api__
#define __faust_api__

#include <cstdint>

//===============API Reference==============
//==========================================

class FaustPolyEngine;
class MidiUI;
class OSCUI;
class JuceOSCUI;
class SoundUI;
class audio;
class dsp;
class UI;
class dsp_factory;

class DspFaust
{

    private:

        FaustPolyEngine* fPolyEngine;

    #if OSCCTRL
    #if JUCE_DRIVER
        JuceOSCUI* fOSCInterface;
    #else
        OSCUI* fOSCInterface;
    #endif
    #endif

    #if MIDICTRL
        MidiUI* fMidiInterface;
    #endif

    #if SOUNDFILE
        SoundUI* fSoundInterface;
    #endif

    #if DYNAMIC_DSP
        dsp_factory* fFactory;
    #endif

        void init(dsp* mono_dsp, audio* driver);
        audio* createDriver(int sample_rate, int buffer_size, bool auto_connect = true);

    public:

        //--------------`DspFaust()`----------------
        // Default constructor, to be used wih audio drivers
        /// that impose their sample rate and buffer size
        // (like JACK and JUCE)
        //
        // #### Arguments
        //
        // * `auto_connect`: whether to automatically connect audio outpus to the hardware (usable with JACK)
        //----
        DspFaust(bool auto_connect = true);

        //--------------`DspFaust(int SR, int BS)`----------------
        // Constructor.
        //
        // #### Arguments
        //
        // * `SR`: sampling rate
        // * `BS`: buffer size
        // * `auto_connect`: whether to automatically connect audio outputs to the hardware (usable with JACK)
        //--------------------------------------------------------
        DspFaust(int, int, bool auto_connect = true);

        //--------------`DspFaust(const string& dsp_content, int SR, int BS)`----------------
        // Constructor.
        //
        // #### Arguments
        //
        // * `dsp_content`: the DSP as a file or string
        // * `SR`: sampling rate
        // * `BS`: buffer size
        // * `auto_connect`: whether to automatically connect audio outputs to the hardware (usable with JACK)
        //--------------------------------------------------------
    #if DYNAMIC_DSP
        DspFaust(const std::string&, int, int, bool auto_connect = true);
    #endif

        // No virtual destructor since DspFaust does not have any virtual methods and is not supposed to be subclassed
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
        // a `uintptr_t` otherwise. This value can be used later with
        // [`setVoiceParamValue`](#setvoiceparamvalue) or
        // [`getVoiceParamValue`](#getvoiceparamvalue) to access
        // the parameters of a specific voice.
        //
        // #### Arguments
        //
        // * `pitch`: MIDI note number (0-127)
        // * `velocity`: MIDI velocity (0-127)
        //--------------------------------------------------------
        uintptr_t keyOn(int, int);

        //----------------`int keyOff(int pitch)`-----------------
        // De-instantiate a polyphonic voice. This method can
        // only be used if the `[style:poly]` metadata is used in
        // the Faust code or if the `-nvoices` flag has been
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

        //-------------------`uintptr_t newVoice()`--------------------
        // Instantiate a new polyphonic voice. This method can
        // only be used if the `[style:poly]` metadata is used in
        // the Faust code or if `-nvoices` flag has been
        // provided before compilation.
        //
        // `newVoice` will return 0 if the Faust object is not
        // polyphonic or the address to the allocated voice as
        // a `uintptr_t` otherwise. This value can be used later with
        // `setVoiceParamValue`, `getVoiceParamValue` or
        // `deleteVoice` to access the parameters of a specific
        // voice.
        //--------------------------------------------------------
        uintptr_t newVoice();

        //---------`int deleteVoice(uintptr_t voice)`------------------
        // De-instantiate a polyphonic voice. This method can
        // only be used if the `[style:poly]` metadata is used in
        // the Faust code or if `-nvoices` flag has been
        // provided before compilation.
        //
        // `deleteVoice` will return 0 if the object is not polyphonic
        // and 1 otherwise.
        //
        // #### Arguments
        //
        // * `voice`: the address of the voice given by `newVoice`
        //--------------------------------------------------------
        int deleteVoice(uintptr_t);

        //-----------------`void allNotesOff()`----------------
        // Terminates all the active voices, gently (with release when hard = false or immediately when hard = true).
        //--------------------------------------------------------
        void allNotesOff(bool hard = false);
   
        //-------`void propagateMidi(int count, double time, int type, int channel, int data1, int data2)`--------
        // Take a raw MIDI message and propagate it to the Faust
        // DSP object. This method can be used concurrently with
        // [`keyOn`](#keyOn) and [`keyOff`](#keyOff).
        //
        // `propagateMidi` can
        // only be used if the `[style:poly]` metadata is used in
        // the Faust code or if `-nvoices` flag has been
        // provided before compilation.
        //
        // #### Arguments
        //
        // * `count`: size of the message (1-3)
        // * `time`: time stamp
        // * `type`: message type (byte)
        // * `channel`: channel number
        // * `data1`: first data byte (should be `null` if `count<2`)
        // * `data2`: second data byte (should be `null` if `count<3`)
        //--------------------------------------------------------
        void propagateMidi(int, double, int, int, int, int);

        //-----------------`const char* getJSONUI()`----------------
        // Returns the JSON description of the UI of the Faust object.
        //--------------------------------------------------------
        const char* getJSONUI();

        //-----------------`const char* getJSONMeta()`----------------
        // Returns the JSON description of the metadata of the Faust object.
        //--------------------------------------------------------
        const char* getJSONMeta();

        //--------------`void buildUserInterface(UI* ui_interface)`---------------
        // Calls the polyphonic or monophonic buildUserInterface with the ui_interface parameter.
        //
        // #### Arguments
        //
        // * `ui_interface`: an UI* object
        //--------------------------------------------------------
        void buildUserInterface(UI*);

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

        //----`void setVoiceParamValue(const char* address, uintptr_t voice, float value)`-----
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
        void setVoiceParamValue(const char*, uintptr_t, float);

        //----`void setVoiceValue(int id, uintptr_t voice, float value)`-----
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
        void setVoiceParamValue(int, uintptr_t, float);

        //----`float getVoiceParamValue(const char* address, uintptr_t voice)`----
        // Returns the value of a parameter in function of its
        // address (path) for a specific voice.
        //
        // #### Arguments
        //
        // * `address`: address (path) of the parameter
        // * `voice`: address of the polyphonic voice (retrieved
        // from `keyOn`)
        //--------------------------------------------------------
        float getVoiceParamValue(const char*, uintptr_t);

        //----`float getVoiceParamValue(int id, uintptr_t voice)`----
        // Returns the value of a parameter in function of its
        // id for a specific voice.
        //
        // #### Arguments
        //
        // * `id`: id of the parameter
        // * `voice`: address of the polyphonic voice (retrieved
        // from `keyOn`)
        //--------------------------------------------------------
        float getVoiceParamValue(int, uintptr_t);

        //----`const char* getParamAddress(int id)`---------------
        // Returns the address (path) of a parameter in function
        // of its ID.
        //
        // #### Arguments
        //
        // * `id`: id of the parameter
        //--------------------------------------------------------
        const char* getParamAddress(int);

        //----`const char* getVoiceParamAddress(int id, uintptr_t voice)`-----
        // Returns the address (path) of a parameter in function
        // of its ID.
        //
        // #### Arguments
        //
        // * `id`: id of the parameter
        // * `voice`: address of the polyphonic voice (retrieved
        // from `keyOn`)
        //--------------------------------------------------------
        const char* getVoiceParamAddress(int, uintptr_t);

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

        //-----`const char* getMetadata(const char* address, const char* key)`-----
        // Returns the metadataof a parameter in function of
        // its address (path) and the metadata key.
        //
        // #### Arguments
        //
        // * `address`: address (path) of the parameter
        //--------------------------------------------------------
        const char* getMetadata(const char*, const char*);

        //----`const char* getMetadata(int id, const char* key)`---------------
        // Returns the metadataof a parameter in function of
        // its iD and the metadata key.
        //
        // #### Arguments
        //
        // * `id`: id of the parameter
        //--------------------------------------------------------
        const char* getMetadata(int, const char*);

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
        // * `gyr`: the gyroscope axis (**0**: x, **1**: y, **2**: z)
        // * `curve`: the curve (**0**: up, **1**: down, **2**: up and down)
        // * `amin`: mapping min point
        // * `amid`: mapping middle point
        // * `amax`: mapping max point
        //--------------------------------------------------------
        void setGyrConverter(int, int, int, float, float, float);

        //------------------`float getCPULoad()`------------------
        // Returns the CPU load (between 0 and 1.0).
        //--------------------------------------------------------
        float getCPULoad();

        //----`void configureOSC(int xmit, int inport, int outport, int errport, const char* address)`---------------
        // Change the OSC configuration.
        //
        // #### Arguments
        //
        // * `xmit`: the xmit state (off-0 all-1 alias-2)
        // * `inport`: the input port number
        // * `outport`: the output port number
        // * `errport`: the error port number
        // * `address`: the destination IP address
        //--------------------------------------------------------
        bool configureOSC(int xmit, int inport, int outport, int errport, const char* address);

        //----------`bool isOSCOn()`---------------
        // Return OSC Status.
        //-----------------------------------------
        bool isOSCOn();
    
        int getScreenColor();
};

#endif
