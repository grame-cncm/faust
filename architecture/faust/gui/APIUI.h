/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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

#ifndef API_UI_H
#define API_UI_H

#include "faust/misc.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/PathBuilder.h"
#include "faust/gui/ValueConverter.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum { kLin = 0, kLog = 1, kExp = 2 };

class APIUI : public PathBuilder, public Meta, public UI
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
        vector<ZoneControl*>	fGyr[3];

        // Screen color control
        // "...[screencolor:red]..." etc.
        bool                    fHasScreenControl;      // true if control screen color metadata
        ZoneReader*             fRedReader;
        ZoneReader*             fGreenReader;
        ZoneReader*             fBlueReader;

        // Current values controlled by metadata
        string	fCurrentUnit;
        int     fCurrentScale;
        string	fCurrentAcc;
        string	fCurrentGyr;
        string  fCurrentColor;

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
                    fAcc[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    cerr << "incorrect acc metadata : " << fCurrentAcc << endl;
                }
            }
            fCurrentAcc = "";

            // handle gyr metadata "...[gyr : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentGyr.size() > 0) {
                istringstream iss(fCurrentGyr);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fGyr[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    cerr << "incorrect gyr metadata : " << fCurrentGyr << endl;
                }
            }
            fCurrentGyr = "";

            // handle screencolor metadata "...[screencolor:red|green|blue]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == 0)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == 0)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == 0) && (fGreenReader == 0) && (fBlueReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    cerr << "incorrect screencolor metadata : " << fCurrentColor << endl;
                }
            }
            fCurrentColor = "";
        }

        int getAccZoneIndex(int p, int acc)
        {
            FAUSTFLOAT* zone = fZone[p];
            for (int i = 0; i < fAcc[acc].size(); i++) {
                if (zone == fAcc[acc][i]->getZone()) return i;
            }
            return -1;
        }

     public:

        APIUI() : fNumParameters(0), fHasScreenControl(false), fRedReader(0), fGreenReader(0), fBlueReader(0)
        {}

        virtual ~APIUI()
        {
            vector<ValueConverter*>::iterator it1;
            for (it1 = fConversion.begin(); it1 != fConversion.end(); it1++) {
                delete(*it1);
            }

            vector<ZoneControl*>::iterator it2;
            for (int i = 0; i < 3; i++) {
                for (it2 = fAcc[i].begin(); it2 != fAcc[i].end(); it2++) {
                    delete(*it2);
                }
                for (it2 = fGyr[i].begin(); it2 != fGyr[i].end(); it2++) {
                    delete(*it2);
                }
            }
            
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }

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
			} else if (strcmp(key, "gyr") == 0) {
				fCurrentGyr = val;
			} else if (strcmp(key, "screencolor") == 0) {
                fCurrentColor = val; // val = "red", "green" or "blue"
            }
        }

        virtual void declare(const char* key, const char* val)
        {}

		//-------------------------------------------------------------------------------
		// Simple API part
		//-------------------------------------------------------------------------------
		int getParamsCount()				{ return fNumParameters; }
		int getParamIndex(const char* n) 	{ return (fMap.count(n) > 0) ? fMap[n] : -1; }
		const char* getParamName(int p)		{ return fName[p].c_str(); }
		const char* getParamUnit(int p)		{ return fUnit[p].c_str(); }
		FAUSTFLOAT getParamMin(int p)		{ return fMin[p]; }
		FAUSTFLOAT getParamMax(int p)		{ return fMax[p]; }
		FAUSTFLOAT getParamStep(int p)		{ return fStep[p]; }

		FAUSTFLOAT getParamValue(int p)         { return *fZone[p]; }
		void setParamValue(int p, FAUSTFLOAT v) { *fZone[p] = v; }

		double getParamRatio(int p)         { return fConversion[p]->faust2ui(*fZone[p]); }
		void setParamRatio(int p, double r) { *fZone[p] = fConversion[p]->ui2faust(r); }

		double value2ratio(int p, double r)	{ return fConversion[p]->faust2ui(r); }
		double ratio2value(int p, double r)	{ return fConversion[p]->ui2faust(r); }

        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant float* zones.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @param value - the new value
         *
         */
        void propagateAcc(int acc, double value)
        {
            for (int i = 0; i < fAcc[acc].size(); i++) {
                fAcc[acc][i]->update(value);
            }
        }

        /**
         * Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setAccConverter(int p, int acc, int curve, double amin, double amid, double amax)
        {
            int id1 = getAccZoneIndex(p, 0);
            int id2 = getAccZoneIndex(p, 1);
            int id3 = getAccZoneIndex(p, 2);

            // Deactivates everywhere..
            if (id1 != -1) fAcc[0][id1]->setActive(false);
            if (id2 != -1) fAcc[1][id2]->setActive(false);
            if (id3 != -1) fAcc[2][id3]->setActive(false);

            if (acc == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getAccZoneIndex(p, acc);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                    fAcc[acc][id4]->setMappingValues(curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]);
                    fAcc[acc][id4]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fZone[p];
                    fAcc[acc].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]));
                    //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter new CurveZoneControl %d", acc);
                }
            }
        }

         /**
         * Used to edit accelerometer curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - the acc value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getAccConverter(int p, int& acc, int& curve, double& amin, double& amid, double& amax)
        {
            int id1 = getAccZoneIndex(p, 0);
            int id2 = getAccZoneIndex(p, 1);
            int id3 = getAccZoneIndex(p, 2);
       
            if (id1 != -1) {
                acc = 0;
                curve = fAcc[acc][id1]->getCurve();
                fAcc[acc][id1]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                acc = 1;
                curve = fAcc[acc][id2]->getCurve();
                fAcc[acc][id2]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                acc = 2;
                curve = fAcc[acc][id3]->getCurve();
                fAcc[acc][id3]->getMappingValues(amin, amid, amax);
            } else {
                acc = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }

        // TODO
        void propagateGyr(int gyr, double value)
        {
            for (int i = 0; i < fGyr[gyr].size(); i++) {
                fGyr[gyr][i]->update(value);
            }
        }

        void setGyrConverter(int p, int gyr, int curve, double amin, double amid, double amax) {}

        void getGyrConverter(int p, int& gyr, int& curve, double& amin, double& amid, double& amax) {}

        // getScreenColor() : -1 means no screen color control (no screencolor metadata found)
        // otherwise return 0x00RRGGBB a ready to use color
        int getScreenColor()
        {
            if (fHasScreenControl) {
                int r = (fRedReader) ? fRedReader->getValue() : 0;
                int g = (fGreenReader) ? fGreenReader->getValue() : 0;
                int b = (fBlueReader) ? fBlueReader->getValue() : 0;
                return (r<<16) | (g<<8) | b;
            } else {
                return -1;
            }
        }

};

#endif
