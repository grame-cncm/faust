/************************** BEGIN mspUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/
//
//  mspUI.h for static Max/MSP externals and faustgen~
//
//  Created by Martin Di Rollo on 18/04/12.
//  Copyright (c) 2012-2019 Grame. All rights reserved.
//

#ifndef _mspUI_h
#define _mspUI_h

#include <math.h>
#include <string>
#include <map>

#include "faust/gui/UI.h"
#include "faust/gui/PathBuilder.h"

#define STR_SIZE    512
#define MULTI_SIZE  256

#ifdef WIN32
#include <stdio.h>
#define snprintf _snprintf
#ifndef NAN
    static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif
#endif

using namespace std;

struct Max_Meta1 : Meta
{
    int fCount;
    
    Max_Meta1():fCount(0)
    {}
    
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            fCount++;
        }
    }
};

struct Max_Meta2 : Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};

struct Max_Meta3 : Meta
{
    string fName;
    
    bool endWith(const string& str, const string& suffix)
    {
        size_t i = str.rfind(suffix);
        return (i != string::npos) && (i == (str.length() - suffix.length()));
    }
    
    void declare(const char* key, const char* value)
    {
        if ((strcmp("filename", key) == 0)) {
            string val = value;
            if (endWith(value, ".dsp")) {
                fName = "com.grame." + val.substr(0, val.size() - 4) + "~";
            } else {
                fName = "com.grame." + val + "~";
            }
        }
    }
};

class mspUIObject {
    
    protected:
        
        string fLabel;
        FAUSTFLOAT* fZone;
        
        FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}
        
    public:
        
        mspUIObject(const string& label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
        virtual ~mspUIObject() {}
        
        virtual void setValue(FAUSTFLOAT f) { *fZone = range(0.0, 1.0, f); }
        virtual FAUSTFLOAT getValue() { return *fZone; }
    
        virtual FAUSTFLOAT getInitValue() { return FAUSTFLOAT(0); }
        virtual FAUSTFLOAT getMinValue() { return FAUSTFLOAT(0); }
        virtual FAUSTFLOAT getMaxValue() { return FAUSTFLOAT(0); }
    
        virtual void toString(char* buffer) {}
        virtual string getName() { return fLabel; }
};

class mspCheckButton : public mspUIObject {
    
    public:
        
        mspCheckButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspCheckButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, STR_SIZE, "CheckButton(float): %s", fLabel.c_str());
        }
};

class mspButton : public mspUIObject {
    
    public:
        
        mspButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, STR_SIZE, "Button(float): %s", fLabel.c_str());
        }
};

class mspSlider : public mspUIObject {
    
    private:
        
        FAUSTFLOAT fInit;
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fStep;
        
    public:
        
        mspSlider(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        :mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
        virtual ~mspSlider() {}
        
        void toString(char* buffer)
        {
            stringstream str;
            str << "Slider(float): " << fLabel << " [init=" << fInit << ":min=" << fMin << ":max=" << fMax << ":step=" << fStep << ":cur=" << *fZone << "]";
            string res = str.str();
            snprintf(buffer, STR_SIZE, "%s", res.c_str());
        }
        
        void setValue(FAUSTFLOAT f) { *fZone = range(fMin, fMax, f); }
    
        virtual FAUSTFLOAT getInitValue() { return fInit; }
        virtual FAUSTFLOAT getMinValue() { return fMin; }
        virtual FAUSTFLOAT getMaxValue() { return fMax; }
    
};

class mspBargraph : public mspUIObject {
    
    private:
        
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fCurrent;
        
    public:
        
        mspBargraph(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        :mspUIObject(label,zone), fMin(min), fMax(max), fCurrent(*zone) {}
        virtual ~mspBargraph() {}
        
        void toString(char* buffer)
        {
            stringstream str;
            str << "Bargraph(float): " << fLabel << " [min=" << fMin << ":max=" << fMax << ":cur=" << *fZone << "]";
            string res = str.str();
            snprintf(buffer, STR_SIZE, "%s", res.c_str());
        }
    
        // special version
        virtual FAUSTFLOAT getValue(bool& new_val)
        {
            if (*fZone != fCurrent) {
                fCurrent = *fZone;
                new_val = true;
            } else {
                new_val = false;
            }
            return fCurrent;
        }
    
        virtual FAUSTFLOAT getMinValue() { return fMin; }
        virtual FAUSTFLOAT getMaxValue() { return fMax; }
    
};

class mspUI : public UI, public PathBuilder
{
    private:
        
        map<string, mspUIObject*> fInputLabelTable;      // Input table using labels
        map<string, mspUIObject*> fInputPathTable;       // Input table using paths
        map<string, mspUIObject*> fOutputLabelTable;     // Table containing bargraph with labels
        map<string, mspUIObject*> fOutputPathTable;      // Table containing bargraph with paths
        
        map<const char*, const char*> fDeclareTable;
        
        FAUSTFLOAT* fMultiTable[MULTI_SIZE];
        int fMultiIndex;
        int fMultiControl;
        
        string createLabel(const char* label)
        {
            map<const char*, const char*>::reverse_iterator it;
            if (fDeclareTable.size() > 0) {
                unsigned int i = 0;
                string res = string(label);
                char sep = '[';
                for (it = fDeclareTable.rbegin(); it != fDeclareTable.rend(); it++, i++) {
                    res = res + sep + (*it).first + ":" + (*it).second;
                    sep = ',';
                }
                res += ']';
                fDeclareTable.clear();
                return res;
            } else {
                return string(label);
            }
        }
    
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fInputLabelTable[string(label)] = obj;
            fInputPathTable[buildPath(label)] = obj;
            fDeclareTable.clear();
        }
    
        void addBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            mspUIObject* obj = new mspBargraph(createLabel(label), zone, min, max);
            fOutputLabelTable[string(label)] = obj;
            fOutputPathTable[buildPath(label)] = obj;
            fDeclareTable.clear();
        }
    
    public:
        
        typedef map<string, mspUIObject*>::iterator iterator;
        
        mspUI()
        {
            for (int i = 0; i < MULTI_SIZE; i++) {
                fMultiTable[i] = 0;
            }
            fMultiIndex = fMultiControl = 0;
        }
    
        virtual ~mspUI()
        {
            clear();
        }
        
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            mspUIObject* obj = new mspButton(createLabel(label), zone);
            fInputLabelTable[string(label)] = obj;
            fInputPathTable[buildPath(label)] = obj;
        }
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            mspUIObject* obj = new mspCheckButton(createLabel(label), zone);
            fInputLabelTable[string(label)] = obj;
            fInputPathTable[buildPath(label)] = obj;
        }
        
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
    
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addBargraph(label, zone, min, max);
        }
    
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addBargraph(label, zone, min, max);
        }
        
        void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        void openTabBox(const char* label) { pushLabel(label); fDeclareTable.clear(); }
        void openHorizontalBox(const char* label) { pushLabel(label); fDeclareTable.clear(); }
        void openVerticalBox(const char* label) { pushLabel(label); fDeclareTable.clear(); }
        void closeBox() { popLabel(); fDeclareTable.clear(); }
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key, "multi") == 0) {
                int index = atoi(val);
                if (index >= 0 && index < MULTI_SIZE) {
                    fMultiTable[index] = zone;
                    fMultiControl++;
                } else {
                    post("Invalid multi index = %d", index);
                }
            }
            
            fDeclareTable[key] = val;
        }
        
        void setMultiValues(FAUSTFLOAT* multi, int buffer_size)
        {
            for (int read = 0; read < buffer_size; read++) {
                int write = (fMultiIndex + read) & (MULTI_SIZE - 1);
                if (fMultiTable[write]) {
                    *fMultiTable[write] = multi[read];
                }
            }
            fMultiIndex += buffer_size;
        }
        
        bool isMulti() { return fMultiControl > 0; }
        
        bool isValue(const string& name)
        {
            return (fInputLabelTable.count(name) || fInputPathTable.count(name));
        }
    
        bool isOutputValue(const string& name)
        {
            return fOutputPathTable.count(name);
        }
    
        bool isInputValue(const string& name)
        {
            return fInputPathTable.count(name);
        }
    
        bool setValue(const string& name, FAUSTFLOAT val)
        {
            if (fInputLabelTable.count(name)) {
                fInputLabelTable[name]->setValue(val);
                return true;
            } else if (fInputPathTable.count(name)) {
                fInputPathTable[name]->setValue(val);
                return true;
            } else {
                return false;
            }
        }
    
        FAUSTFLOAT getOutputValue(const string& name, bool& new_val)
        {
            return static_cast<mspBargraph*>(fOutputPathTable[name])->getValue(new_val);
        }
        
        iterator begin1() { return fInputLabelTable.begin(); }
        iterator end1() { return fInputLabelTable.end(); }
        
        iterator begin2() { return fInputPathTable.begin(); }
        iterator end2() { return fInputPathTable.end(); }
    
        iterator begin3() { return fOutputLabelTable.begin(); }
        iterator end3() { return fOutputLabelTable.end(); }
    
        iterator begin4() { return fOutputPathTable.begin(); }
        iterator end4() { return fOutputPathTable.end(); }
    
        int inputItemsCount() { return fInputLabelTable.size(); }
        int outputItemsCount() { return fOutputLabelTable.size(); }
    
        void clear()
        {
            for (auto& it : fInputLabelTable) {
                delete it.second;
            }
            fInputLabelTable.clear();
            fInputPathTable.clear();
            
            for (auto& it : fOutputLabelTable) {
                delete it.second;
            }
            fOutputLabelTable.clear();
            fOutputPathTable.clear();
        }
        
        void displayControls()
        {
            post("------- Range and path ----------");
            for (auto& it : fInputPathTable) {
                char param[STR_SIZE];
                it.second->toString(param);
                post(param);
                string path = "Complete path: " + it.first;
                post(path.c_str());
            }
            post("---------------------------------");
        }
    
        static bool checkDigit(const string& name)
        {
            for (int i = name.size() - 1; i >= 0; i--) {
                if (isdigit(name[i])) { return true; }
            }
            return false;
        }
        
        static int countDigit(const string& name)
        {
            int count = 0;
            for (int i = name.size() - 1; i >= 0; i--) {
                if (isdigit(name[i])) { count++; }
            }
            return count;
        }

};

#endif
/**************************  END  mspUI.h **************************/
