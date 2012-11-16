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

using namespace std;

/*--------------------------------------------------------------------------*/
class mspUIObject {
    
protected:
    
    string fLabel;
    FAUSTFLOAT* fZone;
    
    FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}
    
public:
    
    mspUIObject(const char* label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
    virtual ~mspUIObject() {}
    
    virtual void SetValue(FAUSTFLOAT f) {*fZone = range(0.0, 1.0, f);}
    virtual void toString(char* buffer) {}
    virtual string GetName() {return fLabel;}
  
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {
    
    public:
        
        mspCheckButton(const char* label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
        virtual ~mspCheckButton() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, 256, "CheckButton(float): %s", fLabel.c_str());
        }
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {
    
    public:
        
        mspButton(const char* label, FAUSTFLOAT* zone):mspUIObject(label, zone) {}
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
        
        mspSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        :mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
        virtual ~mspSlider() {}
        
        void toString(char* buffer)
        {
            snprintf(buffer, 256, "Slider(float): %s [init=%.1f:min=%.1f:max=%.1f:step=%.1f:cur=%.1f]", fLabel.c_str(), fInit, fMin, fMax, fStep, *fZone);
        }
        
        void SetValue(FAUSTFLOAT f) {*fZone = range(fMin, fMax, f);}
};

/*--------------------------------------------------------------------------*/
class mspUI : public UI
{

    private:
        
        map<string, mspUIObject*> fUITable;
        map<const char*, const char*> fDeclareTable;
        
    public:
        
        typedef map<string,mspUIObject*>::iterator iterator;
        
        mspUI() {}
        virtual ~mspUI()
        {
            for (iterator iter = fUITable.begin(); iter != fUITable.end(); iter++) {
                delete (iter->second);
            }
        }
        
        void addButton(const char* label, FAUSTFLOAT* zone) {fUITable[string(label)] = new mspButton(label, zone);}
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone) {fUITable[string(label)] = new mspCheckButton(label, zone);}
        
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            map<const char*, const char*>::reverse_iterator it;
            
            if (fDeclareTable.size() > 0) {
                int i = 0;
                string res = string(label) + "[";
                for (it = fDeclareTable.rbegin(); it != fDeclareTable.rend(); it++, i++) {
                    res = res + (*it).first + ":" + (*it).second;
                    if (i < fDeclareTable.size() - 1) {
                        res += ",";
                    }
                }
                res += "]";
                fUITable[string(label)] = new mspSlider(res.c_str(), zone, init, min, max, step);
                fDeclareTable.clear();
            } else {
                fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
            }
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
            fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
        }

        void openTabBox(const char* label) {}
        void openHorizontalBox(const char* label) {}
        void openVerticalBox(const char* label) {}
        void closeBox() {}
        
        bool SetValue(string name, FAUSTFLOAT f)
        {
            if (fUITable.count(name)) {
                fUITable[name]->SetValue(f);
                return true;
            } else {
                return false;
            }
        }
        iterator begin()	{ return fUITable.begin(); }
        iterator end()		{ return fUITable.end(); }
        
        // To be implemented
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fDeclareTable[key] = val;
        }
        
        int itemsCount() { return fUITable.size(); }
        void clear() { fUITable.clear(); }
    
};
#endif
