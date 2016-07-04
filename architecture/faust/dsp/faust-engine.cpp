/************************************************************************

    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

************************************************************************
************************************************************************/

#include <math.h>
#include <string.h>
#include <stdlib.h> 
#include <string> 

#include "faust/gui/JSONUI.h"
#include "faust/gui/APIUI.h"
#include "faust/dsp/llvm-dsp.h"

#if defined(_WIN32)

    #define STRDUP _strdup
    #include "faust/audio/portaudio-dsp.h"

#elif defined(__APPLE__) 

    #define STRDUP strdup
    #if defined(TARGET_OS_IPHONE)
        #include "faust/audio/coreaudio-ios-dsp"
    #else
        #include "faust/audio/coreaudio-dsp.h"
    #endif

#elif defined(__linux__)

    #define STRDUP strdup
    #if defined(ANDROID)
        #include "faust/audio/android-dsp.h"
    #else
        #include "faust/audio/alsa-dsp.h"
    #endif

#endif

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
    #define HAS_JACK 1
#endif 

#if HAS_JACK
    #include "faust/audio/jack-dsp.h"
#endif 

#if !defined(LLVM_DSP)

/**************************BEGIN USER SECTION **************************/

<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

#endif

//**************************************************************
// APIUI : Faust User Interface
// This class a simple parameter based interface
//**************************************************************

using namespace std;

enum { kPortAudioRenderer = 0, kJackRenderer, kCoreAudioRenderer, kiOSRenderer, kAlsaRenderer, kAndroidRenderer };

//**************************************************************
// Globals
//**************************************************************

static string gLastError;

// DSP wrapper 

struct dsp_aux {
    
#ifdef LLVM_DSP
    llvm_dsp_factory* fFactory;
#endif
    dsp* fDSP;
    audio* fDriver;
    APIUI fParams;
    string fJSON;
    
#ifdef LLVM_DSP
    dsp_aux(const char* name_app, 
            const char* dsp_content, 
            const char* argv, 
            const char* target, 
            int opt_level)
        :fDriver(0)
    {
        int argc1 = 0;
        const char* argv1[64];
        stringstream os(argv);
        string token;
        
        // Allocate parameters
        while (os >> token) {               
            argv1[argc1++] = STRDUP(token.c_str());
        }

    #ifdef _WIN32
        argv1[argc1++] = STRDUP("-l");
        argv1[argc1++] = STRDUP("llvm_math.ll"); 
    #endif
 
        fFactory = createDSPFactoryFromString(name_app, dsp_content, argc1, argv1, "", gLastError, opt_level);
        
        // Free parameters
        for (int i = 0; i < argc1; i++) {
            free((void*)argv1[i]);
        }
    
        if (fFactory) {
            fDSP = fFactory->createDSPInstance();
            createJSON(name_app);
        } else {
            throw -1;
        }
    }
#else
    dsp_aux():fDriver(0)
    {
        fDSP = new mydsp();
        createJSON("dummy_dsp");
    }
#endif
    
    virtual ~dsp_aux()
    {
        if (fDriver) {
            fDriver->stop();
            delete fDriver;
        }
        delete fDSP;
    #ifdef LLVM_DSP
        deleteDSPFactory(fFactory);
    #endif
    }
    
    void createJSON(const string& name_app)
    {
        // JSON creation
        JSONUI json(name_app, fDSP->getNumInputs(), fDSP->getNumOutputs());
        fDSP->buildUserInterface(&json);
        fDSP->metadata(&json);
        fJSON = json.JSON();
    }
    
    bool init2(const char* name, int sr, int bsize, int renderer)
    {
        switch (renderer) {
         #ifdef HAS_JACK
            case kJackRenderer:
                fDriver = new jackaudio();
                break;
        #endif
                
        #ifdef _WIN32
            case kPortAudioRenderer:
                fDriver = new portaudio(sr, bsize);
                break;
        #endif
                
        #ifdef __APPLE__
            #if defined(TARGET_OS_IPHONE)
            case kCoreAudioRenderer:
                fDriver = new coreaudio(sr, bsize);
                break;
            #else
            case kiOSRenderer:
                fDriver = new iosaudio(sr, bsize);
                break;
            #endif
        #endif
                
        #ifdef __linux__
            #if defined(ANDROID)
            case kAndroidRenderer:
                fDriver = new androidaudio(sr, bsize);
                break;
            #else
            case kAlsaRenderer:
                fDriver = new alsaaudio(sr, bsize);
                break;
            #endif
        #endif
        
        };
        
        if (fDriver) {
            fDriver->init(name, fDSP);
            fDSP->buildUserInterface(&fParams);
            return true;
        } else {
            return false;
        }
    }
    
    virtual int getNumInputs() { return fDSP->getNumInputs(); }
    virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
    
};

#if HAS_JACK
static audio* createDriver()
{
  return new jackaudio(0, 0);
}

static jackaudio* getJackDriver(dsp* dsp_ext)
{
    return (dsp_ext) ? dynamic_cast<jackaudio*>(reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver) : 0;
}
#endif

// Exported external API

#ifdef __cplusplus
extern "C"
{
#endif

    int getNumInputsDsp(dsp* dsp_ext)
    {
    #if HAS_JACK
        if (dsp_ext) {
            return reinterpret_cast<dsp_aux*>(dsp_ext)->getNumInputs();
        } else {
            int res = 0;
            audio* driver = createDriver();
            if (driver && driver->init("dummy", 0)) {
                res = driver->get_num_inputs();
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
    #if HAS_JACK
        if (dsp_ext) {
            return reinterpret_cast<dsp_aux*>(dsp_ext)->getNumOutputs();
        } else {
            int res = 0;
            audio* driver = createDriver();
            if (driver && driver->init("dummy", 0)) {
                res = driver->get_num_inputs();
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
    #if HAS_JACK
        jackaudio* driver1 = getJackDriver(dsp1_ext);
        jackaudio* driver2 = getJackDriver(dsp2_ext);
        if (driver1 == NULL && driver2 == NULL) return;
       
        if (driver1 == NULL) {
            // Connnection with physical input
            driver2->connect(driver1, src, dst, true);
        } else if (driver2 == NULL) {
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
    #if HAS_JACK
        jackaudio* driver1 = getJackDriver(dsp1_ext);
        jackaudio* driver2 = getJackDriver(dsp2_ext);
        if (driver1 == NULL && driver2 == NULL) return;
     
        if (driver1 == NULL) {
            // Disconnnection with physical input
            driver2->disconnect(driver1, src, dst, true);
        } else if (driver2 == NULL) {
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
    #if HAS_JACK
        jackaudio* driver1 = getJackDriver(dsp1_ext);
        jackaudio* driver2 = getJackDriver(dsp2_ext);
        if (driver1 == NULL && driver2 == NULL) false;
      
        if (driver1 == NULL) {
            // Connection test with physical input
            return driver2->is_connected(driver1, src, dst, true);
        } else if (driver2 == NULL) {
            // Connection test with physical output
            return driver1->is_connected(driver2, src, dst, false);
        } else {
            // Connection test between Dsp
            return driver1->is_connected(driver2, src, dst, false);
        }
    #endif
    }

    dsp* create2Dsp(const char* name_app, const char* dsp_content, const char* argv, const char* target, int opt_level)
    {
    #ifdef LLVM_DSP
        try {
            return reinterpret_cast<dsp*>(new dsp_aux(name_app, dsp_content, argv, target, opt_level));
        } catch (...) {
            printf("Cannot create DSP\n");
        }
    #endif
        return 0;
    }

    dsp* create1Dsp(const char* name_app, const char* dsp_content)
    {
    #ifdef LLVM_DSP
        return create2Dsp(name_app, dsp_content, "", "", 3);
    #else
        return 0;
    #endif
    }

    dsp* create3Dsp()
    {
    #ifdef LLVM_DSP
        return 0;
    #else
        return reinterpret_cast<dsp*>(new dsp_aux());
    #endif
    }

    const char* getLastError() { return gLastError.c_str(); }

    bool init2Dsp(dsp* dsp_ext, const char* name, int sr, int bsize, int renderer)
    {
        return reinterpret_cast<dsp_aux*>(dsp_ext)->init2(name, sr, bsize, renderer);
    }

    bool init1Dsp(dsp* dsp, const char* name)
    {
        return init2Dsp(dsp, name, -1, 512, kJackRenderer);
        //return init2(dsp, name, 44100, 2048, kPortAudioRenderer);
        //return init2(dsp, name, 44100, 512, kCoreAudioRenderer);
    }

    void destroyDsp(dsp* dsp_ext)
    {
        delete reinterpret_cast<dsp_aux*>(dsp_ext);
    }

    bool startDsp(dsp* dsp_ext) 
    {
        return reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver->start();
    }

    void stopDsp(dsp* dsp_ext) 
    {
        return reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver->stop();
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
    const char* getJSONDsp(dsp* dsp_ext) { return reinterpret_cast<dsp_aux*>(dsp_ext)->fJSON.c_str();}

    int getParamsCountDsp(dsp* dsp_ext)  { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamsCount(); }

    int getParamIndexDsp(dsp* dsp_ext, const char* name)	{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamIndex(name); }
    const char* getParamAddressDsp(dsp* dsp_ext, int p)		{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamAddress(p); }
    const char* getParamUnitDsp(dsp* dsp_ext, int p)		{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamUnit(p); }		// [unit: Hz] metadata -> "Hz"
    FAUSTFLOAT getParamMinDsp(dsp* dsp_ext, int p)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMin(p); }
    FAUSTFLOAT getParamMaxDsp(dsp* dsp_ext, int p)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMax(p); }
    FAUSTFLOAT getParamStepDsp(dsp* dsp_ext, int p)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamStep(p); }
        
    FAUSTFLOAT getParamValueDsp(dsp* dsp_ext, int p)            { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamValue(p); }
    void setParamValueDsp(dsp* dsp_ext, int p, FAUSTFLOAT v)	{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamValue(p,v); }
        
    FAUSTFLOAT getParamRatioDsp(dsp* dsp_ext, int p)           { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamRatio(p); }
    void setParamRatioDsp(dsp* dsp_ext, int p, FAUSTFLOAT v)   { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamRatio(p,v); }
        
    FAUSTFLOAT value2ratioDsp(dsp* dsp_ext, int p, FAUSTFLOAT r) { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.value2ratio(p, r); }
    FAUSTFLOAT ratio2valueDsp(dsp* dsp_ext, int p, FAUSTFLOAT r) { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.ratio2value(p, r); }

    void propagateAccDsp(dsp* dsp_ext, int acc, FAUSTFLOAT a) { reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateAcc(acc, a); }
    void setAccConverterDsp(dsp* dsp_ext, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax)
    {
        reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setAccConverter(p, acc, curve, double(amin), double(amid), double(amax));
    }
    void getAccConverterDsp(dsp* dsp_ext, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax)
    {
        double amin_tmp, amid_tmp, amax_tmp;
        int acc_tmp, curve_tmp;
        reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getAccConverter(p, acc_tmp, curve_tmp, amin_tmp, amid_tmp, amax_tmp);
        *acc = acc_tmp;
        *curve = curve_tmp;
        *amin = FAUSTFLOAT(amin_tmp);
        *amin = FAUSTFLOAT(amid_tmp);
        *amin = FAUSTFLOAT(amax_tmp);
    }
        
    void propagateGyrDsp(dsp* dsp_ext, int acc, FAUSTFLOAT a) { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateGyr(acc, a); }
    void setGyrConverterDsp(dsp* dsp_ext, int p, int acc, int curve, FAUSTFLOAT amin, FAUSTFLOAT amid, FAUSTFLOAT amax)
    {
        reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setGyrConverter(p, acc, curve, double(amin), double(amid), double(amax));
    }
    void getGyrConverterDsp(dsp* dsp_ext, int p, int* acc, int* curve, FAUSTFLOAT* amin, FAUSTFLOAT* amid, FAUSTFLOAT* amax)
    {
        double amin_tmp, amid_tmp, amax_tmp;
        int acc_tmp, curve_tmp;
        reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getGyrConverter(p, acc_tmp, curve_tmp, amin_tmp, amid_tmp, amax_tmp);
        *acc = acc_tmp;
        *curve = curve_tmp;
        *amin = FAUSTFLOAT(amin_tmp);
        *amin = FAUSTFLOAT(amid_tmp);
        *amin = FAUSTFLOAT(amax_tmp);
    }
    
#ifdef __cplusplus
}
#endif
