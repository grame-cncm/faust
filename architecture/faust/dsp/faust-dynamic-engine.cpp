/************************** BEGIN faust-dynamic-engine.cpp *****************
FAUST Architecture File
Copyright (C) 2003-2023 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <assert.h>

#include "faust/audio/audio.h"
#include "faust/gui/APIUI.h"
#include "faust/gui/JSONUI.h"

#ifdef LLVM_DSP
#include "faust/dsp/llvm-dsp.h"
#elif INTERP_DSP
#include "faust/dsp/interpreter-dsp.h"
#else
#error Missing dynamic backend, either use LLVM_DSP or INTERP_DSP flag
#endif

#if COREAUDIO_DRIVER
#include "faust/audio/coreaudio-dsp.h"
#endif
#if IOS_DRIVER
#include "faust/audio/coreaudio-ios-dsp.h"
#endif
#if ANDROID_DRIVER
#include "faust/audio/oboe-dsp.h"
#endif
#if ALSA_DRIVER
#include "faust/audio/alsa-dsp.h"
#endif
#if JACK_DRIVER
#include "faust/audio/jack-dsp.h"
#endif
#if PORTAUDIO_DRIVER
#include "faust/audio/portaudio-dsp.h"
#endif
#if RTAUDIO_DRIVER
#include "faust/audio/rtaudio-dsp.h"
#endif

#if SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

using namespace std;

// Audio renderer types

enum RendererType {
    kPortAudioRenderer = 0,
    kRtAudioRenderer,
    kJackRenderer,
    kCoreAudioRenderer,
    kiOSRenderer,
    kAlsaRenderer,
    kAndroidRenderer
};

//**************************************************************
// Globals
//**************************************************************

// DSP wrapper

struct dsp_aux {
    dsp_factory* fFactory;
#if SOUNDFILE
    SoundUI*    fSoundInterface;
#endif
    dsp*        fDSP;
    audio*      fDriver;
    APIUI       fParams;
    string      fJSON;
    const char* fNameApp;
    
    static string gLastError;

    dsp_aux(const char* name_app, const char* dsp_content, int argc, const char* argv[], const char* target,
            int opt_level)
    : fDriver(nullptr)
    {
        fNameApp = name_app;
    #ifdef LLVM_DSP
        fFactory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, gLastError, opt_level);
    #elif INTERP_DSP
        fFactory = createInterpreterDSPFactoryFromString(name_app, dsp_content, argc, argv, gLastError);
    #endif
        if (fFactory) {
            fDSP = fFactory->createDSPInstance();
            createJSON(name_app);
        } else {
            throw std::bad_alloc();
        }
    }
    
    dsp_aux(const char* name_app, Box box, int argc, const char* argv[], const char* target, int opt_level)
    : fDriver(nullptr)
    {
        fNameApp = name_app;
    #ifdef LLVM_DSP
        fFactory = createDSPFactoryFromBoxes(name_app, box, argc, argv, target, gLastError, opt_level);
    #elif INTERP_DSP
        fFactory = createInterpreterDSPFactoryFromBoxes(name_app, box, argc, argv, gLastError);
    #endif
        if (fFactory) {
            fDSP = fFactory->createDSPInstance();
            createJSON(name_app);
        } else {
            throw std::bad_alloc();
        }
    }
    
    dsp_aux(const char* name_app, Signal* signals_aux, int argc, const char* argv[], const char* target, int opt_level)
    : fDriver(nullptr)
    {
        fNameApp = name_app;
        tvec signals;
        int k = 0;
        while (signals_aux[k]) {
            signals.push_back(signals_aux[k]);
            k++;
        }
    #ifdef LLVM_DSP
        fFactory = createDSPFactoryFromSignals(name_app, signals, argc, argv, target, gLastError, opt_level);
    #elif INTERP_DSP
        fFactory = createInterpreterDSPFactoryFromSignals(name_app, signals, argc, argv, gLastError);
    #endif
        if (fFactory) {
            fDSP = fFactory->createDSPInstance();
            createJSON(name_app);
        } else {
            throw std::bad_alloc();
        }
    }
  
    dsp_aux() : fDriver(nullptr)
    {
        fDSP = nullptr;
        createJSON("dummy_dsp");
    }

    virtual ~dsp_aux()
    {
        if (fDriver) {
            fDriver->stop();
            delete fDriver;
        }
        delete fDSP;
    #if SOUNDFILE
        delete fSoundInterface;
    #endif
    #ifdef LLVM_DSP
        deleteDSPFactory(static_cast<llvm_dsp_factory*>(fFactory));
    #elif INTERP_DSP
        deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(fFactory));
    #endif
    }

    void createJSON(const string& name_app)
    {
        // JSON creation
        JSONUI json(name_app, "", fDSP->getNumInputs(), fDSP->getNumOutputs());
        fDSP->buildUserInterface(&json);
        fDSP->metadata(&json);
        fJSON = json.JSON();
    }

    bool init(RendererType renderer, int sr, int bsize)
    {
        switch (renderer) {
        #ifdef JACK_DRIVER
            case kJackRenderer:
                fDriver = new jackaudio();
                break;
        #endif

        #ifdef PORTAUDIO_DRIVER
            case kPortAudioRenderer:
                fDriver = new portaudio(sr, bsize);
                break;
        #endif

        #ifdef RTAUDIO_DRIVER
            case kRtAudioRenderer:
                fDriver = new rtaudio(sr, bsize);
                break;
        #endif

        #ifdef COREAUDIO_DRIVER
            case kCoreAudioRenderer:
                fDriver = new coreaudio(sr, bsize);
                break;
        #endif

        #ifdef IOS_DRIVER
            case kiOSRenderer:
                fDriver = new iosaudio(sr, bsize);
                break;
        #endif

        #ifdef ANDROID_DRIVER
            case kAndroidRenderer:
                fDriver = new androidaudio(sr, bsize);
                break;
        #endif

        #ifdef ALSA_DRIVER
            case kAlsaRenderer:
                fDriver = new alsaaudio(sr, bsize);
                break;
        #endif
                
            default:
                assert(false);
                break;
        };

        if (fDriver) {
            fDriver->init(fNameApp, fDSP);
            fDSP->buildUserInterface(&fParams);
    #if SOUNDFILE
            // Use bundle path and "soundfiles" metadata URLs
            vector<string> base_url = SoundUI::getSoundfilePaths(fDSP);
            base_url.push_back(SoundUI::getBinaryPath());
            fSoundInterface = new SoundUI(base_url);
            fDSP->buildUserInterface(fSoundInterface);
    #endif
            return true;
        } else {
            return false;
        }
    }

    int getNumInputs() { return fDSP->getNumInputs(); }
    int getNumOutputs() { return fDSP->getNumOutputs(); }
};

#if JACK_DRIVER
static audio* createDriver()
{
    return new jackaudio();
}

static jackaudio* getJackDriver(dsp* dsp_ext)
{
    return (dsp_ext) ? dynamic_cast<jackaudio*>(reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver) : nullptr;
}
#endif

string dsp_aux::gLastError;

// Exported external C API

#ifdef __cplusplus
extern "C" {
#endif

int getNumInputsDsp(dsp* dsp_ext)
{
#if JACK_DRIVER
    if (dsp_ext) {
        return reinterpret_cast<dsp_aux*>(dsp_ext)->getNumInputs();
    } else {
        int    res    = 0;
        audio* driver = createDriver();
        if (driver && driver->init("dummy", nullptr)) {
            res = driver->getNumInputs();
            delete driver;
        }
        return res;
    }
#else
    return -1;
#endif
}

int getNumOutputsDsp(dsp* dsp_ext)
{
#if JACK_DRIVER
    if (dsp_ext) {
        return reinterpret_cast<dsp_aux*>(dsp_ext)->getNumOutputs();
    } else {
        int    res    = 0;
        audio* driver = createDriver();
        if (driver && driver->init("dummy", nullptr)) {
            res = driver->getNumInputs();
            delete driver;
        }
        return res;
    }
#else
    return -1;
#endif
}

void connectDsp(dsp* dsp1_ext, dsp* dsp2_ext, int src, int dst)
{
#if JACK_DRIVER
    jackaudio* driver1 = getJackDriver(dsp1_ext);
    jackaudio* driver2 = getJackDriver(dsp2_ext);
    if (driver1 == nullptr && driver2 == nullptr) return;

    if (driver1 == nullptr) {
        // Connnection with physical input
        driver2->connect(driver1, src, dst, true);
    } else if (driver2 == nullptr) {
        // Connnection with physical output
        driver1->connect(driver2, src, dst, false);
    } else {
        // Connnection between drivers
        driver1->connect(driver2, src, dst, false);
    }
#endif
}

void disconnectDsp(dsp* dsp1_ext, dsp* dsp2_ext, int src, int dst)
{
#if JACK_DRIVER
    jackaudio* driver1 = getJackDriver(dsp1_ext);
    jackaudio* driver2 = getJackDriver(dsp2_ext);
    if (driver1 == nullptr && driver2 == nullptr) return;

    if (driver1 == nullptr) {
        // Disconnnection with physical input
        driver2->disconnect(driver1, src, dst, true);
    } else if (driver2 == nullptr) {
        // Disconnnection with physical output
        driver1->disconnect(driver2, src, dst, false);
    } else {
        // Disconnnection between drivers
        driver1->disconnect(driver2, src, dst, false);
    }
#endif
}

bool isConnectedDsp(dsp* dsp1_ext, dsp* dsp2_ext, int src, int dst)
{
#if JACK_DRIVER
    jackaudio* driver1 = getJackDriver(dsp1_ext);
    jackaudio* driver2 = getJackDriver(dsp2_ext);
    if (driver1 == nullptr && driver2 == nullptr) return false;

    if (driver1 == nullptr) {
        // Connection test with physical input
        return driver2->isConnected(driver1, src, dst, true);
    } else if (driver2 == nullptr) {
        // Connection test with physical output
        return driver1->isConnected(driver2, src, dst, false);
    } else {
        // Connection test between Dsp
        return driver1->isConnected(driver2, src, dst, false);
    }
#else
    return false;
#endif
}

dsp* createDsp(const char* name_app, const char* dsp_content, int argc, const char* argv[], const char* target,
               int opt_level)
{
    try {
        return reinterpret_cast<dsp*>(new dsp_aux(name_app, dsp_content, argc, argv, target, opt_level));
    } catch (...) {
        cerr << "Cannot create DSP\n";
        return nullptr;
    }
}
    
dsp* createDspFromBoxes(const char* name_app, Box box, int argc, const char* argv[], const char* target, int opt_level)
{
    try {
        return reinterpret_cast<dsp*>(new dsp_aux(name_app, box, argc, argv, target, opt_level));
    } catch (...) {
        cerr << "Cannot create DSP\n";
        return nullptr;
    }
}
    
dsp* createDspFromSignals(const char* name_app, Signal* signals, int argc, const char* argv[], const char* target, int opt_level)
{
    try {
        return reinterpret_cast<dsp*>(new dsp_aux(name_app, signals, argc, argv, target, opt_level));
    } catch (...) {
        cerr << "Cannot create DSP\n";
        return nullptr;
    }
}

const char* getLastError()
{
    return dsp_aux::gLastError.c_str();
}

bool initDsp(dsp* dsp_ext, RendererType renderer, int sr, int bsize)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->init(renderer, sr, bsize);
}

void destroyDsp(dsp* dsp_ext)
{
    delete reinterpret_cast<dsp_aux*>(dsp_ext);
}

bool startDsp(dsp* dsp_ext)
{
    dsp_aux* dsp = reinterpret_cast<dsp_aux*>(dsp_ext);
    return (dsp->fDriver) ? dsp->fDriver->start() : false;
}

void stopDsp(dsp* dsp_ext)
{
    dsp_aux* dsp = reinterpret_cast<dsp_aux*>(dsp_ext);
    if (dsp->fDriver) dsp->fDriver->stop();
}

/*
 * Faust objects have control parameters that can be read and changed.
 * getParamsCountDsp() returns the number n of such parameters
 *
 * getParamAddressDsp(int index) retrieves the name of a parameter by its index
 * getParamIndexDsp(const char* name) retrieves the index of a parameter by its name
 *
 * getNamedParamDsp(const char* name) retrieves the value of a parameter by its name
 * getIndexParamDsp(int i) retrieves the value of a parameter by its index
 */
const char* getJSONDsp(dsp* dsp_ext)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fJSON.c_str();
}

int getParamsCountDsp(dsp* dsp_ext)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamsCount();
}

int getParamIndexDsp(dsp* dsp_ext, const char* name)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamIndex(name);
}
const char* getParamAddressDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamAddress(p);
}
const char* getParamUnitDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getMetadata(p, "unit");
}
FAUSTFLOAT getParamMinDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMin(p);
}
FAUSTFLOAT getParamMaxDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMax(p);
}
FAUSTFLOAT getParamStepDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamStep(p);
}

FAUSTFLOAT getParamValueDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamValue(p);
}
void setParamValueDsp(dsp* dsp_ext, int p, FAUSTFLOAT v)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamValue(p, v);
}

FAUSTFLOAT getParamRatioDsp(dsp* dsp_ext, int p)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamRatio(p);
}
void setParamRatioDsp(dsp* dsp_ext, int p, FAUSTFLOAT v)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamRatio(p, v);
}

FAUSTFLOAT value2ratioDsp(dsp* dsp_ext, int p, FAUSTFLOAT r)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.value2ratio(p, r);
}
FAUSTFLOAT ratio2valueDsp(dsp* dsp_ext, int p, FAUSTFLOAT r)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.ratio2value(p, r);
}

void propagateAccDsp(dsp* dsp_ext, int acc, FAUSTFLOAT a)
{
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateAcc(acc, a);
}
void setAccConverterDsp(dsp* dsp_ext, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax)
{
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setAccConverter(p, acc, curve, double(amin), double(amid),
                                                                 double(amax));
}
void getAccConverterDsp(dsp* dsp_ext, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax)
{
    double amin_tmp, amid_tmp, amax_tmp;
    int    acc_tmp, curve_tmp;
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getAccConverter(p, acc_tmp, curve_tmp, amin_tmp, amid_tmp, amax_tmp);
    *acc   = acc_tmp;
    *curve = curve_tmp;
    *amin  = FAUSTFLOAT(amin_tmp);
    *amin  = FAUSTFLOAT(amid_tmp);
    *amin  = FAUSTFLOAT(amax_tmp);
}

void propagateGyrDsp(dsp* dsp_ext, int gyr, FAUSTFLOAT a)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateGyr(gyr, a);
}
void setGyrConverterDsp(dsp* dsp_ext, int p, int gyr, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax)
{
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setGyrConverter(p, gyr, curve, double(amin), double(amid),
                                                                 double(amax));
}
void getGyrConverterDsp(dsp* dsp_ext, int p, int* gyr, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax)
{
    double amin_tmp, amid_tmp, amax_tmp;
    int    gyr_tmp, curve_tmp;
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getGyrConverter(p, gyr_tmp, curve_tmp, amin_tmp, amid_tmp, amax_tmp);
    *gyr   = gyr_tmp;
    *curve = curve_tmp;
    *amin  = FAUSTFLOAT(amin_tmp);
    *amin  = FAUSTFLOAT(amid_tmp);
    *amin  = FAUSTFLOAT(amax_tmp);
}

#ifdef __cplusplus
}
#endif

/************************** END faust-dynamic-engine.cpp **************************/
