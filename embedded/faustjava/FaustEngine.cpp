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
#include <sstream> 
#include <string> 

#include "faust/misc.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/ValueConverter.h"
#ifdef _WIN32
#include "faust/audio/portaudio-dsp.h"	
#else
#include "faust/audio/coreaudio-dsp.h"	
#endif

#include "faust/audio/jack-dsp.h"
#include "faust/dsp/llvm-dsp.h"

#ifdef _WIN32
#define STRDUP _strdup
#else
#define STRDUP strdup
#endif

//**************************************************************
// APIUI : Faust User Interface
// This class a simple parameter based interface
//**************************************************************

using namespace std;

enum { kLin = 0, kLog = 1, kExp = 2 };

enum { kPortAudioRenderer = 0, kJackRenderer, kCoreAudioRenderer };

static string gLastError;

class APIUI : public PathUI, public Meta
{
    protected:
    
        int	fNumParameters;
        vector<string>			fName;
        map<string, int>		fMap;
        vector<ValueConverter*>	fConversion;
        vector<FAUSTFLOAT*>		fZone;
        vector<FAUSTFLOAT>		fInit;
        vector<FAUSTFLOAT>		fMin;
        vector<FAUSTFLOAT>		fMax;
        vector<FAUSTFLOAT>		fStep;        
        vector<string>			fUnit; 

        vector<ZoneControl*>	fAcc[3];

        // Current values controlled by metadata
        string	fCurrentUnit;     
        int     fCurrentScale;
        string	fCurrentAcc;     

        // Add a generic parameter
        virtual void addParameter(const char* label, 
                                FAUSTFLOAT* zone, 
                                FAUSTFLOAT init, 
                                FAUSTFLOAT min, 
                                FAUSTFLOAT max, 
                                FAUSTFLOAT step)
        {
            string name = buildPath(label);

            fMap[name] = fNumParameters++;
            fName.push_back(name);
            fZone.push_back(zone);
            fInit.push_back(init);
            fMin.push_back(min);
            fMax.push_back(max);
            fStep.push_back(step);

            //handle unit metadata
            fUnit.push_back(fCurrentUnit); 
            fCurrentUnit = "";

            //handle scale metadata
            switch (fCurrentScale) {
                case kLin : fConversion.push_back(new LinearValueConverter(0,1, min, max)); break;
                case kLog : fConversion.push_back(new LogValueConverter(0,1, min, max)); break;							
                case kExp : fConversion.push_back(new ExpValueConverter(0,1, min, max)); break;
            }
            fCurrentScale  = kLin;

            // handle acc metadata "...[acc : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentAcc.size() > 0) {
                istringstream iss(fCurrentAcc); 
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;
                
                if ((0 <= axe) && (axe < 3) && 
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax)) 
                {
                    ValueConverter* vc = 0;
                    switch (curve) {
                        case 0 : vc = new AccUpConverter(amin, amid, amax, min, init, max); break;
                        case 1 : vc = new AccDownConverter(amin, amid, amax, min, init, max); break;
                        case 2 : vc = new AccUpDownConverter(amin, amid, amax, min, init, max); break;
                        case 3 : vc = new AccDownUpConverter(amin, amid, amax, min, init, max); break;
                    }
                    if (vc) { fAcc[axe].push_back(new ZoneControl(zone, vc)); }
                } else {
                    cerr << "incorrect acc metadata : " << fCurrentAcc << endl;
                }
            }
            fCurrentAcc = "";
        }
     
     public:
     
        APIUI() : fNumParameters(0) {}
        virtual ~APIUI() {}

        // -- widget's layouts
    
        virtual void openTabBox(const char* label)			{ fControlsLevel.push_back(label); 	}    
        virtual void openHorizontalBox(const char* label)	{ fControlsLevel.push_back(label); 	} 
        virtual void openVerticalBox(const char* label)		{ fControlsLevel.push_back(label); 	}
        virtual void closeBox()								{ fControlsLevel.pop_back();		}
    
        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1);
        }
    
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1);
        }
    
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0);
        }
    
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
			if (strcmp(key, "scale") == 0) {
                if (strcmp(val, "log") == 0) {
                    fCurrentScale = kLog;
                } else if (strcmp(val, "exp") == 0) {
                    fCurrentScale = kExp;
                } else {
                    fCurrentScale = kLin;
                }
			} else if (strcmp(key, "unit") == 0) {
				fCurrentUnit = val;
			} else if (strcmp(key, "acc") == 0) {
				fCurrentAcc = val;
			}
        }

        virtual void declare(const char* key, const char* val)
        {}

		//-------------------------------------------------------------------------------
		// Simple API part
		//-------------------------------------------------------------------------------
		int getParamsCount()				{ return fNumParameters; }
		int getParamIndex(const char* n) 	{ return (fMap.count(n)>0) ? fMap[n] : -1; }
		const char* getParamName(int p)		{ return fName[p].c_str(); }
		const char* getParamUnit(int p)		{ return fUnit[p].c_str(); }
		float getParamMin(int p)			{ return fMin[p]; }
		float getParamMax(int p)			{ return fMax[p]; }
		float getParamStep(int p)			{ return fStep[p]; }
	
		float getParamValue(int p)			{ return *fZone[p]; }
		void  setParamValue(int p, float v)	{ *fZone[p] = v; }
	
		float getParamRatio(int p)			{ return fConversion[p]->faust2ui(*fZone[p]); }
		void  setParamRatio(int p, float r)	{ *fZone[p] = fConversion[p]->ui2faust(r); }
	
		float value2ratio(int p, float r)	{ return fConversion[p]->faust2ui(r); }
		float ratio2value(int p, float r)	{ return fConversion[p]->ui2faust(r); }

		void  propagateAccX(double a)				{ 
			for (int i = 0; i < fAcc[0].size(); i++) {
				fAcc[0][i]->update(a);
			}
		}

		void  propagateAccY(double a)				{ 
			for (int i = 0; i < fAcc[1].size(); i++) {
				fAcc[1][i]->update(a);
			}
		}

		void  propagateAccZ(double a)				{ 
			for (int i = 0; i < fAcc[2].size(); i++) {
				fAcc[2][i]->update(a);
			}
		}

};

//**************************************************************
// Globals
//**************************************************************

// DSP wrapper 

struct dsp_aux {
    
    llvm_dsp_factory* fFactory;
    llvm_dsp* fDSP;
    audio* fDriver;
    APIUI fParams;
    string fName;
    string fJSON;
    
    dsp_aux(const char* name_app, 
                const char* dsp_content, 
                const char* argv, 
                const char* target, 
                int opt_level)
        :fDSP(0),fDriver(0)
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
            fDSP = createDSPInstance(fFactory);
            // JSON creation
            JSONUI json(name_app, fDSP->getNumInputs(), fDSP->getNumOutputs());
            metadataDSPFactory(fFactory, &json);
            fDSP->buildUserInterface(&json);
            fJSON = json.JSON();
        } else {
            throw -1;
        }
    }
    
    virtual ~dsp_aux()
    {
        if (fDriver) {
            fDriver->stop();
            delete fDriver;
        }
        deleteDSPInstance(fDSP);
        deleteDSPFactory(fFactory);
    }
    
    bool init2(const char* name, int sr, int bsize, int renderer)
    {
        fName = name;
        
        switch (renderer) {
        
        #ifdef _WIN32
            case kPortAudioRenderer:
                fDriver = new portaudio(sr, bsize);
                break;
        #endif
                
            case kJackRenderer:
                fDriver = new jackaudio();
                break;
                
        #ifdef __APPLE__
            case kCoreAudioRenderer:
                fDriver = new coreaudio(sr, bsize);
                break;
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

static audio* createDriver()
{
    audio* driver;
 #ifdef _WIN32
    driver = new portaudio(44100, 512);
 #endif
 #ifdef __APPLE__
    //driver = new coreaudio(44100, 512);
    driver = new jackaudio(0, 0);
 #endif
    return driver;
}

jackaudio* getJackDriver(dsp* dsp1_ext)
{
    return (dsp1_ext) ? dynamic_cast<jackaudio*>(reinterpret_cast<dsp_aux*>(dsp1_ext)->fDriver) : 0;
}

// Exported external API

#ifdef __cplusplus
extern "C"
{
#endif

int getNumInputs(dsp* dsp_ext)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->getNumInputs();
}

int getNumOutputs(dsp* dsp_ext)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->getNumOutputs();
}

int getNumPhysicalInputs()
{
    int res = 0;
    audio* driver = createDriver();
    if (driver && driver->init("dummy", 0)) {
        res = driver->get_num_inputs();
        delete driver;
    }
    return res;
}

int getNumPhysicalOutputs()
{
    int res = 0;
    audio* driver = createDriver();
    if (driver && driver->init("dummy", 0)) {
        res = driver->get_num_outputs();
        delete driver;
    }
    return res;
}

void connect(dsp* dsp1_ext, dsp* dsp2_ext, int src, int dst)
{
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
}

void disconnect(dsp* dsp1_ext, dsp* dsp2_ext, int src, int dst)
{   
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
}

bool isConnected(dsp* dsp1_ext, dsp* dsp2_ext, int src, int dst)
{ 
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
        // Connection test between DSP
        return driver1->is_connected(driver2, src, dst, false);
    }
}

dsp* create2(const char* name_app, const char* dsp_content, const char* argv, const char* target, int opt_level)
{
    try {
        return reinterpret_cast<dsp*>(new dsp_aux(name_app, dsp_content, argv, target, opt_level));
    } catch (...) {
        printf("Cannot create DSP\n");
    }
    return 0;
}

dsp* create1(const char* name_app, const char* dsp_content)
{
    return create2(name_app, dsp_content, "", "", 3);
}

const char* getLastError() { return gLastError.c_str(); }

bool init2(dsp* dsp_ext, const char* name, int sr, int bsize, int renderer)
{
    return reinterpret_cast<dsp_aux*>(dsp_ext)->init2(name, sr, bsize, renderer);
}

bool init1(dsp* dsp, const char* name)
{
	return init2(dsp, name, -1, 512, kJackRenderer);
	//return init2(dsp, name, 44100, 2048, kPortAudioRenderer);
    //return init2(dsp, name, 44100, 512, kCoreAudioRenderer);
}

void destroy(dsp* dsp_ext)
{
    delete reinterpret_cast<dsp_aux*>(dsp_ext);
}

bool start(dsp* dsp_ext) 
{
 	return reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver->start();
}

void stop(dsp* dsp_ext) 
{
	return reinterpret_cast<dsp_aux*>(dsp_ext)->fDriver->stop();
}

/*
 * Faust objects have control parameters that can be read and changed.
 * getParamsCount() returns the number n of such parameters
 *
 * getParamName(int index) retrieves the name of a parameter by its index
 * getParamIndex(const char* name) retrieves the index of a parameter by its name
 *
 * getNamedParam(const char* name) retrieves the value of a parameter by its name
 * getIndexParam(int i) retrieves the value of a parameter by its index
 */
const char* getJSON(dsp* dsp_ext) { return reinterpret_cast<dsp_aux*>(dsp_ext)->fJSON.c_str();}

int getParamsCount(dsp* dsp_ext)					{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamsCount(); }

int getParamIndex(dsp* dsp_ext, const char* name)	{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamIndex(name); }
const char* getParamName(dsp* dsp_ext, int p)		{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamName(p); }
const char* getParamUnit(dsp* dsp_ext, int p)		{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamUnit(p); }		// [unit: Hz] metadata -> "Hz"
float getParamMin(dsp* dsp_ext, int p)				{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMin(p); }
float getParamMax(dsp* dsp_ext, int p)				{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamMax(p); }
float getParamStep(dsp* dsp_ext, int p)				{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamStep(p); }
	
float getParamValue(dsp* dsp_ext, int p)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamValue(p); }
void  setParamValue(dsp* dsp_ext, int p, float v)	{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamValue(p,v); }
	
float getParamRatio(dsp* dsp_ext, int p)            { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.getParamRatio(p); }
void  setParamRatio(dsp* dsp_ext, int p, float v)   { return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.setParamRatio(p,v); }
	
float value2ratio(dsp* dsp_ext, int p, float r)		{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.value2ratio(p, r); }
float ratio2value(dsp* dsp_ext, int p, float r)		{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.ratio2value(p, r); }

void propagateAccX(dsp* dsp_ext, float a)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateAccX(a); }
void propagateAccY(dsp* dsp_ext, float a)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateAccY(a); }
void propagateAccZ(dsp* dsp_ext, float a)			{ return reinterpret_cast<dsp_aux*>(dsp_ext)->fParams.propagateAccZ(a); }

#ifdef __cplusplus
}
#endif
