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

    FaustPolyEngine(int sampling_rate, int buffer_size)
    :fJSONUI(fMonoDSP.getNumInputs(), fMonoDSP.getNumOutputs()), fRunning(false)
    {
        // configuring the UI
        fMonoDSP.buildUserInterface(&fAPIUI);
        fMonoDSP.buildUserInterface(&fJSONUI);
        fJSON = fJSONUI.JSON();

        if (fJSON.find("keyboard") != std::string::npos ||
            fJSON.find("poly") != std::string::npos){
            fPolyMax = 6;
            fPolyDSP = new mydsp_poly(fPolyMax, true);
            fPolyDSP->init(sampling_rate);
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

    bool start()
    {
        if (!fRunning) {
            fRunning = fDriver->start();
        }
        return fRunning;
    }

    void stop()
    {
        if (fRunning) {
            fRunning = false;
            fDriver->stop();
        }
    }

    int keyOn(int pitch, int velocity)
    {
        if (fPolyMax > 0) {
            fPolyDSP->keyOn(0, pitch, velocity);
            return 1;
        } else {
            return 0;
        }
    }

    int keyOff(int pitch, int velocity = 127)
    {
        if (fPolyMax > 0) {
            fPolyDSP->keyOff(0, pitch, velocity);
            return 1;
        } else {
            return 0;
        }
    }

    int pitchBend(int refPitch, float pitch)
    {
        if (fPolyMax > 0) {
            fPolyDSP->pitchBend(0, refPitch, pitch);
            return 1;
        } else {
            return 0;
        }
    }
    
    const char* getJSON()
    {
        return fJSON.c_str();
    }

    int getParamsCount()
    {
        return fAPIUI.getParamsCount();
    }

    float getParam(const char* address)
    {
        if (fPolyMax > 0) {
            return fPolyDSP->getValue(address);
         } else {
            return fAPIUI.getParamValue(fAPIUI.getParamIndex(address));
        }
    }

    void setParam(const char* address, float value)
    {
        if (fPolyMax > 0) {
            fPolyDSP->setValue(address, value);
        } else {
            fAPIUI.setParamValue(fAPIUI.getParamIndex(address), value);
        }
    }

    int setVoiceParam(const char* address, int pitch, float value)
    {
        if (fPolyMax > 0) {
            fPolyDSP->setValue(address, pitch, value);
            return 1;
        } else {
            return 0;
        }
    }

    int setVoiceGain(int pitch, float gain)
    {
        if (fPolyMax > 0) {
            fPolyDSP->setVoiceGain(pitch, gain);
            return 1;
        } else {
            return 0;
        }
    }

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
