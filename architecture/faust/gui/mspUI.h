/************************** BEGIN mspUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
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
 
 mspUI.h for static Max/MSP externals and faustgen~
 Created by Martin Di Rollo on 18/04/12.
 ********************************************************************/

#ifndef _mspUI_h
#define _mspUI_h

#include <math.h>
#include <assert.h>
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
    std::string fName;
    
    bool endWith(const std::string& str, const std::string& suffix)
    {
        size_t i = str.rfind(suffix);
        return (i != std::string::npos) && (i == (str.length() - suffix.length()));
    }
    
    void declare(const char* key, const char* value)
    {
        if ((strcmp("filename", key) == 0)) {
            std::string val = value;
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
        
        std::string fLabel;
        FAUSTFLOAT* fZone;
        
        FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}
        
    public:
        
        mspUIObject(const std::string& label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
        virtual ~mspUIObject() {}
        
        virtual void setValue(FAUSTFLOAT f) { *fZone = range(0.0, 1.0, f); }
        virtual FAUSTFLOAT getValue() { return *fZone; }
    
        virtual FAUSTFLOAT getInitValue() { return FAUSTFLOAT(0); }
        virtual FAUSTFLOAT getMinValue() { return FAUSTFLOAT(0); }
        virtual FAUSTFLOAT getMaxValue() { return FAUSTFLOAT(0); }
    
        virtual void toString(char* buffer) {}
        virtual std::string getName() { return fLabel; }
};

class mspCheckButton : public mspUIObject {
    
    public:
        
        mspCheckButton(const std::string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspCheckButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, STR_SIZE, "CheckButton(float): %s", fLabel.c_str());
        }
};

class mspButton : public mspUIObject {
    
    public:
        
        mspButton(const std::string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
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
        
        mspSlider(const std::string& label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        :mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
        virtual ~mspSlider() {}
        
        void toString(char* buffer)
        {
            std::stringstream str;
            str << "Slider(float): " << fLabel << " [init=" << fInit << ":min=" << fMin << ":max=" << fMax << ":step=" << fStep << ":cur=" << *fZone << "]";
            std::string res = str.str();
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
        
        mspBargraph(const std::string& label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        :mspUIObject(label,zone), fMin(min), fMax(max), fCurrent(*zone) {}
        virtual ~mspBargraph() {}
        
        void toString(char* buffer)
        {
            std::stringstream str;
            str << "Bargraph(float): " << fLabel << " [min=" << fMin << ":max=" << fMax << ":cur=" << *fZone << "]";
            std::string res = str.str();
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
        
        std::map<std::string, mspUIObject*> fInputLabelTable;      // Input table using labels
        std::map<std::string, mspUIObject*> fInputShortnameTable;  // Input table using shortnames
        std::map<std::string, mspUIObject*> fInputPathTable;       // Input table using paths
        std::map<std::string, mspUIObject*> fOutputLabelTable;     // Table containing bargraph with labels
        std::map<std::string, mspUIObject*> fOutputShortnameTable; // Table containing bargraph with shortnames
        std::map<std::string, mspUIObject*> fOutputPathTable;      // Table containing bargraph with paths
        
        std::map<const char*, const char*> fDeclareTable;
        
        FAUSTFLOAT* fMultiTable[MULTI_SIZE];
        int fMultiIndex;
        int fMultiControl;
        
        std::string createLabel(const char* label)
        {
            std::map<const char*, const char*>::reverse_iterator it;
            if (fDeclareTable.size() > 0) {
                std::string res = std::string(label);
                char sep = '[';
                for (it = fDeclareTable.rbegin(); it != fDeclareTable.rend(); it++) {
                    res = res + sep + (*it).first + ":" + (*it).second;
                    sep = ',';
                }
                res += ']';
                fDeclareTable.clear();
                return res;
            } else {
                return std::string(label);
            }
        }
    
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fInputLabelTable[std::string(label)] = obj;
            std::string path = buildPath(label);
            fInputPathTable[path] = obj;
            fFullPaths.push_back(path);
            fDeclareTable.clear();
        }
    
        void addBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            mspUIObject* obj = new mspBargraph(createLabel(label), zone, min, max);
            fOutputLabelTable[std::string(label)] = obj;
            std::string path = buildPath(label);
            fOutputPathTable[path] = obj;
            fFullPaths.push_back(path);
            fDeclareTable.clear();
        }
    
    public:
        
        typedef std::map<std::string, mspUIObject*>::iterator iterator;
        
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
            fInputLabelTable[std::string(label)] = obj;
            std::string path = buildPath(label);
            fInputPathTable[path] = obj;
            fFullPaths.push_back(path);
        }
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            mspUIObject* obj = new mspCheckButton(createLabel(label), zone);
            fInputLabelTable[std::string(label)] = obj;
            std::string path = buildPath(label);
            fInputPathTable[path] = obj;
            fFullPaths.push_back(path);
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
        void closeBox()
        {
            fDeclareTable.clear();
            if (popLabel()) {
                // Shortnames can be computed when all fullnames are known
                computeShortNames();
                // Fill 'shortname' map
                for (const auto& path : fFullPaths) {
                    if (fInputPathTable.count(path)) {
                        fInputShortnameTable[fFull2Short[path]] = fInputPathTable[path];
                    } else if (fOutputPathTable.count(path)) {
                        fOutputShortnameTable[fFull2Short[path]] = fOutputPathTable[path];
                    } else {
                        assert(false);
                    }
                }
             }
        }
        
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
        
        bool isValue(const std::string& name)
        {
            return (isOutputValue(name) || isInputValue(name));
        }
    
        bool isInputValue(const std::string& name)
        {
            return fInputLabelTable.count(name) || fInputShortnameTable.count(name) || fInputPathTable.count(name);
        }
    
        bool isOutputValue(const std::string& name)
        {
            return fOutputLabelTable.count(name) || fOutputShortnameTable.count(name) || fOutputPathTable.count(name);
        }
    
        bool setValue(const std::string& name, FAUSTFLOAT val)
        {
            if (fInputLabelTable.count(name)) {
                fInputLabelTable[name]->setValue(val);
                return true;
            } else if (fInputShortnameTable.count(name)) {
                fInputShortnameTable[name]->setValue(val);
                return true;
            } else if (fInputPathTable.count(name)) {
                fInputPathTable[name]->setValue(val);
                return true;
            } else {
                return false;
            }
        }
    
        FAUSTFLOAT getOutputValue(const std::string& name, bool& new_val)
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
            for (const auto& it : fInputLabelTable) {
                delete it.second;
            }
            fInputLabelTable.clear();
            fInputShortnameTable.clear();
            fInputPathTable.clear();
            
            for (const auto& it : fOutputLabelTable) {
                delete it.second;
            }
            fOutputLabelTable.clear();
            fOutputShortnameTable.clear();
            fOutputPathTable.clear();
        }
        
        void displayControls()
        {
            post("------- Range, shortname and path ----------");
            for (const auto& it : fInputPathTable) {
                char param[STR_SIZE];
                it.second->toString(param);
                post(param);
                std::string shortname = "Shortname: " + fFull2Short[it.first];
                post(shortname.c_str());
                std::string path = "Complete path: " + it.first;
                post(path.c_str());
            }
            post("---------------------------------------------");
        }
    
        static bool checkDigit(const std::string& name)
        {
            for (int i = name.size() - 1; i >= 0; i--) {
                if (isdigit(name[i])) { return true; }
            }
            return false;
        }
        
        static int countDigit(const std::string& name)
        {
            int count = 0;
            for (int i = name.size() - 1; i >= 0; i--) {
                if (isdigit(name[i])) { count++; }
            }
            return count;
        }

};

//==============
// MIDI handler
//==============

struct max_midi : public midi_handler {
    
    void* m_midi_outlet = NULL;
    
    max_midi(void* midi_outlet = NULL):m_midi_outlet(midi_outlet)
    {}
    
    void sendMessage(std::vector<unsigned char>& message)
    {
        if (m_midi_outlet) {
            for (int i = 0; i < message.size(); i++) {
                outlet_int(m_midi_outlet, message[i]);
            }
        }
    }
    
    // MIDI output API
    MapUI* keyOn(int channel, int pitch, int velocity)
    {
        std::vector<unsigned char> message = {ucast(MIDI_NOTE_ON + channel), ucast(pitch), ucast(velocity)};
        sendMessage(message);
        return NULL;
    }
    
    void keyOff(int channel, int pitch, int velocity)
    {
        std::vector<unsigned char> message = {ucast(MIDI_NOTE_OFF + channel), ucast(pitch), ucast(velocity)};
        sendMessage(message);
    }
    
    void ctrlChange(int channel, int ctrl, int val)
    {
        std::vector<unsigned char> message = {ucast(MIDI_CONTROL_CHANGE + channel), ucast(ctrl), ucast(val)};
        sendMessage(message);
    }
    
    void chanPress(int channel, int press)
    {
        std::vector<unsigned char> message = {ucast(MIDI_AFTERTOUCH + channel), ucast(press)};
        sendMessage(message);
    }
    
    void progChange(int channel, int pgm)
    {
        std::vector<unsigned char> message = {ucast(MIDI_PROGRAM_CHANGE + channel), ucast(pgm)};
        sendMessage(message);
    }
    
    void keyPress(int channel, int pitch, int press)
    {
        std::vector<unsigned char> message = {ucast(MIDI_POLY_AFTERTOUCH + channel), ucast(pitch), ucast(press)};
        sendMessage(message);
    }
    
    void pitchWheel(int channel, int wheel)
    {
        // lsb 7bit, msb 7bit
        std::vector<unsigned char> message = {ucast(MIDI_PITCH_BEND + channel), ucast(wheel & 0x7F), ucast((wheel >> 7) & 0x7F)};
        sendMessage(message);
    }
    
    void ctrlChange14bits(int channel, int ctrl, int value) {}
    
    void startSync(double date)
    {
        std::vector<unsigned char> message = {ucast(MIDI_START)};
        sendMessage(message);
    }
    
    void stopSync(double date)
    {
        std::vector<unsigned char> message = {ucast(MIDI_STOP)};
        sendMessage(message);
    }
    
    void clock(double date)
    {
        std::vector<unsigned char> message = {ucast(MIDI_CLOCK)};
        sendMessage(message);
    }
    
    void sysEx(double, std::vector<unsigned char>& message)
    {
        sendMessage(message);
    }
};

#endif
/**************************  END  mspUI.h **************************/
