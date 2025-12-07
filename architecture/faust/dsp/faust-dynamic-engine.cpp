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
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

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

// Optional lightweight logging; enable at runtime via setDynamicEngineLogging(true)
static bool gEnableDynamicEngineLog = false;
static void logError(const std::string& msg)
{
    if (gEnableDynamicEngineLog) {
        std::cerr << msg << std::endl;
    }
}

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
    struct FactoryDeleter {
        void operator()(dsp_factory* factory) const noexcept
        {
        #ifdef LLVM_DSP
            deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
        #elif INTERP_DSP
            deleteInterpreterDSPFactory(static_cast<interpreter_dsp_factory*>(factory));
        #endif
        }
    };
    struct DriverDeleter {
        void operator()(audio* driver) const noexcept
        {
            if (driver) {
                driver->stop();
                delete driver;
            }
        }
    };

    std::unique_ptr<dsp_factory, FactoryDeleter> fFactory;
#if SOUNDFILE
    std::unique_ptr<SoundUI>    fSoundInterface;
#endif
    std::unique_ptr<dsp>        fDSP;
    std::unique_ptr<audio, DriverDeleter>      fDriver;
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
        fFactory.reset(createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, gLastError, opt_level));
    #elif INTERP_DSP
        fFactory.reset(createInterpreterDSPFactoryFromString(name_app, dsp_content, argc, argv, gLastError));
    #endif
        if (!fFactory) {
            throw std::runtime_error(gLastError.empty() ? "Factory creation failed" : gLastError);
        }
        fDSP.reset(fFactory->createDSPInstance());
        if (!fDSP) {
            gLastError = "Cannot create DSP instance";
            throw std::runtime_error(gLastError);
        }
        createJSON(name_app);
    }
    
    dsp_aux(const char* name_app, Box box, int argc, const char* argv[], const char* target, int opt_level)
    : fDriver(nullptr)
    {
        fNameApp = name_app;
    #ifdef LLVM_DSP
        fFactory.reset(createDSPFactoryFromBoxes(name_app, box, argc, argv, target, gLastError, opt_level));
    #elif INTERP_DSP
        fFactory.reset(createInterpreterDSPFactoryFromBoxes(name_app, box, argc, argv, gLastError));
    #endif
        if (!fFactory) {
            throw std::runtime_error(gLastError.empty() ? "Factory creation failed" : gLastError);
        }
        fDSP.reset(fFactory->createDSPInstance());
        if (!fDSP) {
            gLastError = "Cannot create DSP instance";
            throw std::runtime_error(gLastError);
        }
        createJSON(name_app);
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
        fFactory.reset(createDSPFactoryFromSignals(name_app, signals, argc, argv, target, gLastError, opt_level));
    #elif INTERP_DSP
        fFactory.reset(createInterpreterDSPFactoryFromSignals(name_app, signals, argc, argv, gLastError));
    #endif
        if (!fFactory) {
            throw std::runtime_error(gLastError.empty() ? "Factory creation failed" : gLastError);
        }
        fDSP.reset(fFactory->createDSPInstance());
        if (!fDSP) {
            gLastError = "Cannot create DSP instance";
            throw std::runtime_error(gLastError);
        }
        createJSON(name_app);
    }
  
    virtual ~dsp_aux()
    {
        // unique_ptr deleters handle cleanup.
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
                fDriver.reset(new jackaudio());
                break;
        #endif

        #ifdef PORTAUDIO_DRIVER
            case kPortAudioRenderer:
                fDriver.reset(new portaudio(sr, bsize));
                break;
        #endif

        #ifdef RTAUDIO_DRIVER
            case kRtAudioRenderer:
                fDriver.reset(new rtaudio(sr, bsize));
                break;
        #endif

        #ifdef COREAUDIO_DRIVER
            case kCoreAudioRenderer:
                fDriver.reset(new coreaudio(sr, bsize));
                break;
        #endif

        #ifdef IOS_DRIVER
            case kiOSRenderer:
                fDriver.reset(new iosaudio(sr, bsize));
                break;
        #endif

        #ifdef ANDROID_DRIVER
            case kAndroidRenderer:
                fDriver.reset(new androidaudio(sr, bsize));
                break;
        #endif

        #ifdef ALSA_DRIVER
            case kAlsaRenderer:
                fDriver.reset(new alsaaudio(sr, bsize));
                break;
        #endif
                
            default:
                gLastError = "Unknown renderer type";
                logError(gLastError);
                return false;
        };

        if (fDriver) {
            if (!fDriver->init(fNameApp, fDSP.get())) {
                gLastError = "Driver init failed";
                logError(gLastError);
                fDriver.reset();
                return false;
            }
            fDSP->buildUserInterface(&fParams);
    #if SOUNDFILE
            // Use bundle path and "soundfiles" metadata URLs
            vector<string> base_url = SoundUI::getSoundfilePaths(fDSP.get());
            base_url.push_back(SoundUI::getBinaryPath());
            fSoundInterface.reset(new SoundUI(base_url));
            fDSP->buildUserInterface(fSoundInterface.get());
    #endif
            return true;
        } else {
            gLastError = "Cannot create audio driver";
            return false;
        }
    }

    int getNumInputs() const noexcept { return fDSP ? fDSP->getNumInputs() : -1; }
    int getNumOutputs() const noexcept { return fDSP ? fDSP->getNumOutputs() : -1; }
};

#if JACK_DRIVER
static audio* createDriver()
{
    return new jackaudio();
}

static jackaudio* getJackDriver(dsp* dsp_ext)
{
    if (!dsp_ext) {
        return nullptr;
    }
    auto* driver = reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver.get();
    return dynamic_cast<jackaudio*>(driver);
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
            res = driver->getNumOutputs();
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
    } catch (const std::exception& e) {
        dsp_aux::gLastError = e.what();
        cerr << "Cannot create DSP: " << dsp_aux::gLastError << "\n";
        return nullptr;
    } catch (...) {
        dsp_aux::gLastError = "Cannot create DSP";
        cerr << dsp_aux::gLastError << "\n";
        return nullptr;
    }
}
    
dsp* createDspFromBoxes(const char* name_app, Box box, int argc, const char* argv[], const char* target, int opt_level)
{
    try {
        return reinterpret_cast<dsp*>(new dsp_aux(name_app, box, argc, argv, target, opt_level));
    } catch (const std::exception& e) {
        dsp_aux::gLastError = e.what();
        cerr << "Cannot create DSP: " << dsp_aux::gLastError << "\n";
        return nullptr;
    } catch (...) {
        dsp_aux::gLastError = "Cannot create DSP";
        cerr << dsp_aux::gLastError << "\n";
        return nullptr;
    }
}
    
dsp* createDspFromSignals(const char* name_app, Signal* signals, int argc, const char* argv[], const char* target, int opt_level)
{
    try {
        return reinterpret_cast<dsp*>(new dsp_aux(name_app, signals, argc, argv, target, opt_level));
    } catch (const std::exception& e) {
        dsp_aux::gLastError = e.what();
        cerr << "Cannot create DSP: " << dsp_aux::gLastError << "\n";
        return nullptr;
    } catch (...) {
        dsp_aux::gLastError = "Cannot create DSP";
        cerr << dsp_aux::gLastError << "\n";
        return nullptr;
    }
}

const char* getLastError()
{
    return dsp_aux::gLastError.c_str();
}

void setDynamicEngineLogging(int enable)
{
    gEnableDynamicEngineLog = (enable != 0);
}

bool initDsp(dsp* dsp_ext, RendererType renderer, int sr, int bsize)
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->init(renderer, sr, bsize) : false;
}

void destroyDsp(dsp* dsp_ext)
{
    if (dsp_ext) {
        delete reinterpret_cast<dsp_aux*>(dsp_ext);
    }
}

bool startDsp(dsp* dsp_ext)
{
    dsp_aux* dsp = reinterpret_cast<dsp_aux*>(dsp_ext);
    if (dsp && dsp->fDriver) {
        if (!dsp->fDriver->start()) {
            dsp_aux::gLastError = "Driver start failed";
            logError(dsp_aux::gLastError);
            return false;
        }
        return true;
    }
    dsp_aux::gLastError = "Driver not initialized";
    logError(dsp_aux::gLastError);
    return false;
}

void stopDsp(dsp* dsp_ext)
{
    dsp_aux* dsp = reinterpret_cast<dsp_aux*>(dsp_ext);
    if (dsp && dsp->fDriver) dsp->fDriver->stop();
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
const char* getJSONDsp(dsp* dsp_ext) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fJSON.c_str() : nullptr;
}

int getParamsCountDsp(dsp* dsp_ext) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamsCount() : 0;
}

int getParamIndexDsp(dsp* dsp_ext, const char* name) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamIndex(name) : -1;
}
const char* getParamAddressDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamAddress(p) : nullptr;
}
const char* getParamUnitDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getMetadata(p, "unit") : nullptr;
}
FAUSTFLOAT getParamMinDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMin(p) : FAUSTFLOAT(0);
}
FAUSTFLOAT getParamMaxDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMax(p) : FAUSTFLOAT(0);
}
FAUSTFLOAT getParamStepDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamStep(p) : FAUSTFLOAT(0);
}

FAUSTFLOAT getParamValueDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamValue(p) : FAUSTFLOAT(0);
}
void setParamValueDsp(dsp* dsp_ext, int p, FAUSTFLOAT v) noexcept
{
    if (dsp_ext) reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamValue(p, v);
}

FAUSTFLOAT getParamRatioDsp(dsp* dsp_ext, int p) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamRatio(p) : FAUSTFLOAT(0);
}
void setParamRatioDsp(dsp* dsp_ext, int p, FAUSTFLOAT v) noexcept
{
    if (dsp_ext) reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamRatio(p, v);
}

FAUSTFLOAT value2ratioDsp(dsp* dsp_ext, int p, FAUSTFLOAT r) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.value2ratio(p, r) : FAUSTFLOAT(0);
}
FAUSTFLOAT ratio2valueDsp(dsp* dsp_ext, int p, FAUSTFLOAT r) noexcept
{
    return (dsp_ext) ? reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.ratio2value(p, r) : FAUSTFLOAT(0);
}

void propagateAccDsp(dsp* dsp_ext, int acc, FAUSTFLOAT a) noexcept
{
    if (dsp_ext) reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateAcc(acc, a);
}
void setAccConverterDsp(dsp* dsp_ext, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax) noexcept
{
    if (dsp_ext) {
        reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setAccConverter(p, acc, curve, double(amin), double(amid),
                                                                     double(amax));
    }
}
void getAccConverterDsp(dsp* dsp_ext, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax) noexcept
{
    if (!dsp_ext) {
        if (acc) *acc = 0;
        if (curve) *curve = 0;
        if (amin) *amin = FAUSTFLOAT(0);
        if (amid) *amid = FAUSTFLOAT(0);
        if (amax) *amax = FAUSTFLOAT(0);
        return;
    }
    double amin_tmp, amid_tmp, amax_tmp;
    int    acc_tmp, curve_tmp;
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getAccConverter(p, acc_tmp, curve_tmp, amin_tmp, amid_tmp, amax_tmp);
    *acc   = acc_tmp;
    *curve = curve_tmp;
    *amin  = FAUSTFLOAT(amin_tmp);
    *amid  = FAUSTFLOAT(amid_tmp);
    *amax  = FAUSTFLOAT(amax_tmp);
}

void propagateGyrDsp(dsp* dsp_ext, int gyr, FAUSTFLOAT a) noexcept
{
    if (dsp_ext) reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateGyr(gyr, a);
}
void setGyrConverterDsp(dsp* dsp_ext, int p, int gyr, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax) noexcept
{
    if (dsp_ext) {
        reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setGyrConverter(p, gyr, curve, double(amin), double(amid),
                                                                     double(amax));
    }
}
void getGyrConverterDsp(dsp* dsp_ext, int p, int* gyr, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax) noexcept
{
    if (!dsp_ext) {
        if (gyr) *gyr = 0;
        if (curve) *curve = 0;
        if (amin) *amin = FAUSTFLOAT(0);
        if (amid) *amid = FAUSTFLOAT(0);
        if (amax) *amax = FAUSTFLOAT(0);
        return;
    }
    double amin_tmp, amid_tmp, amax_tmp;
    int    gyr_tmp, curve_tmp;
    reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getGyrConverter(p, gyr_tmp, curve_tmp, amin_tmp, amid_tmp, amax_tmp);
    *gyr   = gyr_tmp;
    *curve = curve_tmp;
    *amin  = FAUSTFLOAT(amin_tmp);
    *amid  = FAUSTFLOAT(amid_tmp);
    *amax  = FAUSTFLOAT(amax_tmp);
}

#ifdef __cplusplus
}
#endif

/************************** END faust-dynamic-engine.cpp **************************/
