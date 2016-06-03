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

//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/poly-dsp.h"

using namespace std;

class FaustPolyEngine {
        
    protected:

        mydsp fMonoDSP;           // the monophonic Faust object
        mydsp_poly* fPolyDSP;     // the polyphonic Faust object
        APIUI fAPIUI;             // the UI description
    
        string fJSON;
        bool fRunning;
        int fPolyMax;
        audio* fDriver;
    
    public:

        FaustPolyEngine()
        {
            fRunning = false;
            
            // configuring the UI
            JSONUI jsonui1(fMonoDSP.getNumInputs(), fMonoDSP.getNumOutputs());
            fMonoDSP.buildUserInterface(&jsonui1);
            fJSON = jsonui1.JSON();

            if (fJSON.find("keyboard") != std::string::npos
                || fJSON.find("poly") != std::string::npos) {
                fPolyMax = 6;
                fPolyDSP = new mydsp_poly(fPolyMax, true);
                fPolyDSP->buildUserInterface(&fAPIUI);
                
                // Update JSON with Poly version
                JSONUI jsonui2(fMonoDSP.getNumInputs(), fMonoDSP.getNumOutputs());
                fPolyDSP->buildUserInterface(&jsonui2);
                fJSON = jsonui2.JSON();
                
            } else {
                fPolyMax = 0;
                fPolyDSP = NULL;
                fMonoDSP.buildUserInterface(&fAPIUI);
            }
         }

        virtual ~FaustPolyEngine()
        {
            delete fPolyDSP;
            delete fDriver;
        }

        bool init()
        {
            return fDriver->init("Dummy", (fPolyMax > 0) ? (dsp*)fPolyDSP : &fMonoDSP);
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
            if (!fRunning) {
                fRunning = fDriver->start();
            }
            return fRunning;
        }
        
        /*
         * isRunning()
         * returns true if the DSP frames are being computed and
         * false if not.
         */
        bool isRunning() 
        {
            return fRunning;
        }

        /*
         * stop()
         * Stops the processing, closes the audio engine and terminates
         * the native thread on Android.
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
         * Faust code. keyOn will return -1 if the object is not
         * polyphonic and the allocated voice otherwise.
         */
        int keyOn(int pitch, int velocity)
        {
            if (fPolyMax > 0) {
                return (int)fPolyDSP->keyOn(0, pitch, velocity); // MapUI* passed to Java as an integer
            } else {
                return -1;
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
         * getJSON()
         * Returns a string containing a JSON description of the
         * UI of the Faust object.
         */
        const char* getJSON()
        {
            return fJSON.c_str();
        }

        /*
         * getParamsCount()
         * Returns the number of parameters of the Faust object.
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
         * setVoiceParamValue will return 0 if the object is not polyphonic
         * and 1 otherwise.
         */
        int setVoiceParamValue(const char* address, int voice, float value)
        {
            assert(sizeof(int) == sizeof(MapUI*));
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code. getVoiceParamValue will return 0 if the
         * object is not polyphonic and the value otherwise.
         */
        float getVoiceParamValue(const char* address, int voice)
        {
            assert(sizeof(int) == sizeof(MapUI*));
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

        void propagateAcc(int acc, float v)
        {
            fAPIUI.propagateAcc(acc, v);
        }

        void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
        {
           fAPIUI.setAccConverter(p, acc, curve, amin, amid, amax);
        }

        void propagateGyr(int gyr, float v)
        {
            fAPIUI.propagateGyr(gyr, v);
        }

        void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
        {
            fAPIUI.setGyrConverter(p, gyr, curve, amin, amid, amax);
        }

        float getCPULoad() { return fDriver->get_cpu_load(); }

        int getScreenColor()
        {
            return fAPIUI.getScreenColor();
        }

};

#endif // __faust_poly_engine__
