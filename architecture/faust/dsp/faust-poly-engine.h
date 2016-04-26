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
        JSONUI fJSONUI;
        string fJSON;
        bool fRunning;
        int fPolyMax;
        audio* fDriver;
        
    public:

        FaustPolyEngine():fJSONUI(fMonoDSP.getNumInputs(), fMonoDSP.getNumOutputs()), fRunning(false)
        {
            // configuring the UI
            fMonoDSP.buildUserInterface(&fAPIUI);
            fMonoDSP.buildUserInterface(&fJSONUI);
            fJSON = fJSONUI.JSON();

            if (fJSON.find("keyboard") != std::string::npos
                || fJSON.find("poly") != std::string::npos) {
                fPolyMax = 6;
                fPolyDSP = new mydsp_poly(fPolyMax, true);
            } else {
                fPolyMax = 0;
                fPolyDSP = NULL;
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
         * Faust code. keyOn will return 0 if the object is not
         * polyphonic and 1 otherwise.
         */
        int keyOn(int pitch, int velocity)
        {
            if (fPolyMax > 0) {
                fPolyDSP->keyOn(0, pitch, velocity);
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
         * pitchBend(refPitch, pitch)
         * Replaces refPitch in the voice associated with it with pitch.
         * pitch is a MIDI number expressed as a decimal number.
         * pitchBend can only be used if the [style:poly] metadata
         * is used in the Faust code. pitchBend will return 0
         * if the object is not polyphonic and 1 otherwise.
         */
        int pitchBend(int refPitch, float pitch)
        {
            if (fPolyMax > 0) {
                fPolyDSP->pitchBend(0, refPitch, pitch);
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
         * getParamValus(address)
         * Takes the address of a parameter and returns its current
         * value.
         */
        float getParamValue(const char* address)
        {
            if (fPolyMax > 0) {
                return fPolyDSP->getParamValue(address);
             } else {
                return fAPIUI.getParamValue(fAPIUI.getParamIndex(address));
            }
        }

        /*
         * setParam(address,value)
         * Sets the value of the parameter associated with address.
         */
        void setParamValue(const char* address, float value)
        {
            if (fPolyMax > 0) {
                fPolyDSP->setParamValue(address, value);
            } else {
                fAPIUI.setParamValue(fAPIUI.getParamIndex(address), value);
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
        int setVoiceParam(const char* address, int pitch, float value)
        {
            if (fPolyMax > 0) {
                fPolyDSP->setParamValue(address, pitch, value);
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
        int setVoiceGain(int pitch, float gain)
        {
            if (fPolyMax > 0) {
                fPolyDSP->setVoiceGain(pitch, gain);
                return 1;
            } else {
                return 0;
            }
        }

        /*
         * getParamAddress(id)
         * Returns the address of a parameter in function of its "id".
         */
        const char* getParamAddress(int id)
        {
            return fAPIUI.getParamName(id);
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
