/************************************************************************
    FAUST Architecture File
    Copyright (C) 2010-2013 GRAME, Centre National de Creation Musicale
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
//
//  mspUI.h for faustgen
//
//  Created by Martin Di Rollo on 18/04/12.
//  Copyright (c) 2012 Grame. All rights reserved.
//

#ifndef faustgen_mspUI_h
#define faustgen_mspUI_h

#include "faust/gui/UI.h"
#include <string>
#include <map>

#ifdef WIN32
#include <stdio.h>
#define snprintf _snprintf
#endif

using namespace std;

/*--------------------------------------------------------------------------*/
class mspUIObject {
    
protected:
    
    string fLabel;
    FAUSTFLOAT* fZone;
    
    FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}
    
public:
    
    mspUIObject(const string& label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
    virtual ~mspUIObject() {}
    
    virtual void setValue(FAUSTFLOAT f) {*fZone = range(0.0, 1.0, f);}
    virtual FAUSTFLOAT getValue() { return *fZone; }
    virtual void toString(char* buffer) {}
    virtual string getName() {return fLabel;}
  
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {
    
    public:
        
        mspCheckButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspCheckButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, 256, "CheckButton(float): %s", fLabel.c_str());
        }
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {
    
    public:
        
        mspButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label, zone) {}
        virtual ~mspButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, 256, "Button(float): %s", fLabel.c_str());
        }
};

/*--------------------------------------------------------------------------*/
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
            stringstream s; 
            s << "Slider(float): " << fLabel << " [init=" << fInit << ":min=" << fMin << ":max=" << fMax << ":step=" << fStep << ":cur=" << *fZone << "]";
            strcpy(buffer, s.str().c_str());
        }
        
        void setValue(FAUSTFLOAT f) {*fZone = range(fMin, fMax, f);}
};

/*--------------------------------------------------------------------------*/
class mspUI : public UI
{

    private:
        
        map<string, mspUIObject*> fUITable;
        map<const char*, const char*> fDeclareTable;
    
        string CreateLabel(const char* label)
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
        
    public:
        
        typedef map<string, mspUIObject*>::iterator iterator;
        
        mspUI() {}
        virtual ~mspUI()
        {
            clear();
        }
        
        void addButton(const char* label, FAUSTFLOAT* zone) {fUITable[string(label)] = new mspButton(CreateLabel(label), zone);}
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone) {fUITable[string(label)] = new mspCheckButton(CreateLabel(label), zone);}
        
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUITable[string(label)] = new mspSlider(CreateLabel(label), zone, init, min, max, step);
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
            fUITable[string(label)] = new mspSlider(CreateLabel(label), zone, init, min, max, step);
        }
        
        // To be implemented
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {fDeclareTable.clear();}
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {fDeclareTable.clear();}
    
        void openTabBox(const char* label) {fDeclareTable.clear();}
        void openHorizontalBox(const char* label) {fDeclareTable.clear();}
        void openVerticalBox(const char* label) {fDeclareTable.clear();}
        void closeBox() {fDeclareTable.clear();}
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fDeclareTable[key] = val;
        }
       
        bool isValue(string name) 
        {
            return fUITable.count(name);
        }
        bool setValue(string name, FAUSTFLOAT f)
        {
            if (fUITable.count(name)) {
                fUITable[name]->setValue(f);
                return true;
            } else {
                return false;
            }
        }
          
        iterator begin()	{ return fUITable.begin(); }
        iterator end()		{ return fUITable.end(); }
        
        int itemsCount() { return fUITable.size(); }
        void clear() 
        { 
            iterator it;
            for (it = begin(); it != end(); it++) {
                delete (*it).second;
            }
            fUITable.clear(); 
        }
    
};
#endif
