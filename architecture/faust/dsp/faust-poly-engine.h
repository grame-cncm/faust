/************************************************************************
 ************************************************************************
 FAUST Polyphonic Architecture File
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

#ifndef __faust_poly_engine__
#define __faust_poly_engine__

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "faust/misc.h"
#include "faust/dsp/dsp.h"
#include "faust/audio/audio.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/APIUI.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/dsp/faust-engine.h"
#include "faust/dsp/dsp-combiner.h"

//**************************************************************
// Mono or polyphonic audio DSP engine
//**************************************************************

#ifndef POLY_VOICES
#define POLY_VOICES 0 	// default is no polyphony (mono)
#endif

using namespace std;

class FaustPolyEngine {
        
    protected:

        mydsp* fMonoDSP;          // the monophonic Faust object
        mydsp_poly* fPolyDSP;     // the polyphonic Faust object
        dsp* fFinalDSP;           // the "final" dsp object submitted to the audio driver
    
        APIUI fAPIUI;             // the UI description

        string fJSON;
        bool fRunning;
        int fPolyMax;
        audio* fDriver;
    
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
    
    public:

        FaustPolyEngine(audio* driver = NULL):fMidiUI(&fMidiHandler)
        {
            fDriver = driver;
            fRunning = false;
            fMonoDSP = new mydsp();

            // Configuring the UI
            JSONUI jsonui1(fMonoDSP->getNumInputs(), fMonoDSP->getNumOutputs());
            fMonoDSP->buildUserInterface(&jsonui1);
            fJSON = jsonui1.JSON();

            if (fJSON.find("keyboard") != std::string::npos
                || fJSON.find("poly") != std::string::npos
                || POLY_VOICES != 0) {
                
                if (POLY_VOICES != 0) {
                    fPolyMax = POLY_VOICES;
                } else {
                    fPolyMax = 10; // default number of poly voices
                }

                fPolyDSP = new mydsp_poly(fMonoDSP, fPolyMax, true);

            #if POLY2
                fFinalDSP = new dsp_sequencer(fPolyDSP, new effect());
            #else
                fFinalDSP = fPolyDSP;
            #endif
                
                // Update JSON with Poly version
                JSONUI jsonui2(fMonoDSP->getNumInputs(), fMonoDSP->getNumOutputs());
                fFinalDSP->buildUserInterface(&jsonui2);
                fJSON = jsonui2.JSON();
                
            } else {
                fPolyMax = 0;
                fPolyDSP = NULL;
                fFinalDSP = fMonoDSP;
            }
            
            fFinalDSP->buildUserInterface(&fMidiUI);
            fFinalDSP->buildUserInterface(&fAPIUI);

			fDriver->init("Dummy", fFinalDSP);
        }

        virtual ~FaustPolyEngine()
        {
            delete fFinalDSP;
            delete fDriver;
        }

        /*
         * start()
         * Begins the processing and return true if the connection
         * with the audio device was successful and false if not.
         */
        bool start()
        {
            if (!fRunning) {
                fRunning = fDriver->start();
            }
            return fRunning;
        }
        
        /*
         * isRunning()
         * Returns true if the DSP frames are being computed and
         * false if not.
         */
        bool isRunning() 
        {
            return fRunning;
        }

        /*
         * stop()
         * Stops the processing, closes the audio engine.
         */
        void stop()
        {
            if (fRunning) {
                fRunning = false;
                fDriver->stop();
            }
        }
    
        /*
         * keyOn(pitch, velocity)
         * Instantiates a new polyphonic voice where velocity
         * and pitch are MIDI numbers (0-127). keyOn can only
         * be used if the [style:poly] metadata is used in the
         * Faust code. keyOn will return 0 if the object is not
         * polyphonic and the allocated voice otherwise.
         */
        MapUI* keyOn(int pitch, int velocity)
        {
            if (fPolyMax > 0) {
                return fPolyDSP->keyOn(0, pitch, velocity); // MapUI* passed to Java as an integer
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
        int keyOff(int pitch, int velocity = 127)
        {
            if (fPolyMax > 0) {
                fPolyDSP->keyOff(0, pitch, velocity);
                return 1;
            } else {
                return 0;
            }
        }
    
        /*
         * Propagate MIDI data to the Faust object.
         */
        void propagateMidi(int count, double time, int type, int channel, int data1, int data2)
        {
            if (count == 3) fMidiHandler.handleData2(time, type, channel, data1, data2);
            else if (count == 2) fMidiHandler.handleData1(time, type, channel, data1);
            else if (count == 1) fMidiHandler.handleSync(time, type);
            GUI::updateAllGuis();
        }
    
        /*
         * getJSON()
         * Returns a string containing a JSON description of the
         * UI of the Faust object.
         */
        const char* getJSON()
        {
            return fJSON.c_str();
        }
    
        /*
         * buildUserInterface(ui)
         * Calls the polyphonic of monophonic buildUserInterface with the ui parameter.
         */
        void buildUserInterface(UI* ui_interface)
        {
            if (fPolyMax > 0) {
                fPolyDSP->buildUserInterface(ui_interface);
            } else {
                fMonoDSP->buildUserInterface(ui_interface);
            }
        }

        /*
         * getParamsCount()
         * Returns the number of control parameters of the Faust object.
         */
        int getParamsCount()
        {
            return fAPIUI.getParamsCount();
        }
    
        /*
         * setParam(address, value)
         * Sets the value of the parameter associated with address.
         */
        void setParamValue(const char* address, float value)
        {
            fAPIUI.setParamValue(fAPIUI.getParamIndex(address), value);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }

        /*
         * getParamValue(address)
         * Takes the address of a parameter and returns its current
         * value.
         */
        float getParamValue(const char* address)
        {
            return fAPIUI.getParamValue(fAPIUI.getParamIndex(address));
        }

        /*
         * setVoiceParamValue(address, voice, value)
         * Sets the value of the parameter associated with address for
         * the voice. setVoiceParamValue can only be
         * used if the [style:poly] metadata is used in the Faust code.
         */
        void setVoiceParamValue(const char* address, long voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code.
         */
        float getVoiceParamValue(const char* address, long voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(address);
        }
    
        /*
         * getParamAddress(id)
         * Returns the address of a parameter in function of its "id".
         */
        const char* getParamAddress(int id)
        {
            return fAPIUI.getParamAddress(id);
        }

        /*
         * propagateAcc(int acc, float v)
         * Propage accelerometer value to the curve conversion layer.
         */
        void propagateAcc(int acc, float v)
        {
            fAPIUI.propagateAcc(acc, v);
        }

        /*
         * setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change accelerometer curve mapping.
         */
        void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
        {
           fAPIUI.setAccConverter(p, acc, curve, amin, amid, amax);
        }

        /*
         * propagateGyr(int gyr, float v)
         * Propage gyroscope value to the curve conversion layer.
         */
        void propagateGyr(int gyr, float v)
        {
            fAPIUI.propagateGyr(gyr, v);
        }

        /*
         * setGyrConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change gyroscope curve mapping.
         */
        void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
        {
            fAPIUI.setGyrConverter(p, gyr, curve, amin, amid, amax);
        }
    
        /*
         * getCPULoad()
         * Return DSP CPU load.
         */
        float getCPULoad() { return fDriver->get_cpu_load(); }

    
        /*
         * getScreenColor() -> c:int
         * Get the requested screen color c :
         * c <  0 : no screen color requested (keep regular UI)
         * c >= 0 : requested color (no UI but a colored screen)
         */
        int getScreenColor()
        {
            return fAPIUI.getScreenColor();
        }

};

// Public C API

#ifdef __cplusplus
extern "C" {
#endif
    
    void destroy(void* dsp) { delete reinterpret_cast<FaustPolyEngine*>(dsp); }

    bool start(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->start(); }
    void stop(void* dsp) { reinterpret_cast<FaustPolyEngine*>(dsp)->stop(); }
    bool isRunning(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->isRunning(); }

    long keyOn(void* dsp, int pitch, int velocity) { return (long)reinterpret_cast<FaustPolyEngine*>(dsp)->keyOn(pitch, velocity); }
    int keyOff(void* dsp, int pitch) { return reinterpret_cast<FaustPolyEngine*>(dsp)->keyOff(pitch); }
    void propagateMidi(void* dsp, int count, double time, int type, int channel, int data1, int data2)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->propagateMidi(count, time, type, channel, data1, data2);
    }

    const char* getJSON(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getJSON(); }

    int getParamsCount(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamsCount(); }
    void setParamValue(void* dsp, const char* address, float value) { reinterpret_cast<FaustPolyEngine*>(dsp)->setParamValue(address, value); }
    float getParamValue(void* dsp, const char* address) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamValue(address); }
    void setVoiceParamValue(void* dsp, const char* address, long voice, float value)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setVoiceParamValue(address, voice, value);
    }
    float getVoiceParamValue(void* dsp, const char* address, long voice) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getVoiceParamValue(address, voice); }
    const char* getParamAddress(void* dsp, int id) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamAddress(id); }

    void propagateAcc(void* dsp, int acc, float v)  { reinterpret_cast<FaustPolyEngine*>(dsp)->propagateAcc(acc, v); }
    void setAccConverter(void* dsp, int p, int acc, int curve, float amin, float amid, float amax)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setAccConverter(p, acc, curve, amin, amid, amax);
    }
    void propagateGyr(void* dsp, int acc, float v)  { reinterpret_cast<FaustPolyEngine*>(dsp)->propagateGyr(acc, v); }
    void setGyrConverter(void* dsp, int p, int gyr, int curve, float amin, float amid, float amax)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setGyrConverter(p, gyr, curve, amin, amid, amax);
    }

    float getCPULoad(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getCPULoad(); }
    int getScreenColor(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getScreenColor(); }
    
#ifdef __cplusplus
}
#endif

#endif // __faust_poly_engine__
