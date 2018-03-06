/************************************************************************
 FAUST Audio Unit UI
 Copyright (C) 2013 Reza Payami
 All rights reserved.
 ----------------------------BSD License------------------------------
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following
 disclaimer in the documentation and/or other materials provided
 with the distribution.
 * Neither the name of Remy Muller nor the names of its
 contributors may be used to endorse or promote products derived
 from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 OF THE POSSIBILITY OF SUCH DAMAGE.
 
 ----------------------------Audio Unit SDK----------------------------------
 In order to compile a AU (TM) Synth plugin with this architecture file
 you will need the proprietary AU SDK from Apple. Please check
 the corresponding license.
 ************************************************************************/

#include <set>

#include "faust/gui/UI.h"
#include "faust/gui/MetaDataUI.h"

using namespace std;

class auUI;

struct auUIObject {
    
    string fLabel;
    FAUSTFLOAT* fZone;
    
    FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val)
    { // AU parameters are normalized in the range [0;1]
        val = min + val * (max - min);
        return (val < min) ? min : (val > max) ? max : val;
    }
    
    auUIObject(const char* label, FAUSTFLOAT* zone): fLabel(label), fZone(zone)
    {}
    
    virtual ~auUIObject()
    {}
    
    virtual void GetName(char *text)
    {
        std::strcpy(text, fLabel.c_str());
    }
    
    virtual void SetValue(double f)
    {
        *fZone = range(0.0f, 1.0f, FAUSTFLOAT(f));
    }
    
    virtual FAUSTFLOAT GetValue()
    {
        return *fZone;
    }
    
    virtual void GetDisplay(char *text)
    {
        std::sprintf(text, "%f", *fZone);
    }
    
    virtual long GetID()
    { /* returns the sum of all the ASCII characters contained in the parameter's label */
        int i;
        long acc;
        for (i = 0, acc = 0; i < fLabel.length(); i++)
            acc += (fLabel.c_str())[i];
        return acc;
    }
};

/**********************************************************************************/
struct auToggleButton: public auUIObject {
    
    auToggleButton(const char* label, FAUSTFLOAT* zone) :
    auUIObject(label, zone)
    {}
    
    virtual ~auToggleButton()
    {}
    
    virtual FAUSTFLOAT GetValue()
    {
        return *fZone;
    }
    
    virtual void SetValue(double f)
    {
        *fZone = (f > 0.5f) ? 1.0f : 0.0f;
    }
    
    virtual void GetDisplay(char *text)
    {
        (*fZone > 0.5f) ? std::strcpy(text, "ON") : std::strcpy(text, "OFF");
    }
    
};

/**********************************************************************************/
struct auCheckButton: public auUIObject {
    
    auCheckButton(const char* label, FAUSTFLOAT* zone) :
    auUIObject(label, zone)
    {}
    
    virtual ~auCheckButton()
    {}
    
    virtual FAUSTFLOAT GetValue()
    {
        return *fZone;
    }
    
    virtual void SetValue(double f)
    {
        *fZone = (f > 0.5f) ? 1.0f : 0.0f;
    }
    
    virtual void GetDisplay(char *text)
    {
        (*fZone > 0.5f) ? std::strcpy(text, "ON") : std::strcpy(text, "OFF");
    }
    
};

/**********************************************************************************/
struct auButton: public auUIObject {
    
    auButton(const char* label, FAUSTFLOAT* zone) :
    auUIObject(label, zone)
    {}
    
    virtual ~auButton()
    {}
    
    virtual FAUSTFLOAT GetValue()
    {
        return *fZone;
    }
    
    virtual void SetValue(double f)
    {
        *fZone = (f > 0.5f) ? 1.0f : 0.0f;
    }
    
    virtual void GetDisplay(char *text)
    {
        (*fZone > 0.5f) ? std::strcpy(text, "ON") : std::strcpy(text, "OFF");
    }
    
};

/**********************************************************************************/
struct auSlider: public auUIObject {
    
    FAUSTFLOAT fInit;
    FAUSTFLOAT fMin;
    FAUSTFLOAT fMax;
    FAUSTFLOAT fStep;
    bool fIsVertical;
    
    auSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
             FAUSTFLOAT step, bool isVertical) :
    auUIObject(label, zone), fInit(init), fMin(min), fMax(max), fStep(step), fIsVertical(isVertical)
    {}
    
    virtual ~auSlider()
    {}
    
    virtual FAUSTFLOAT GetValue()
    {
        return (*fZone - fMin) / (fMax - fMin);
    }	// normalize
    
    virtual void SetValue(double f)
    {
        *fZone = range(fMin, fMax, FAUSTFLOAT(f));
    } // expand
    
};

/**********************************************************************************/

struct auBargraph: public auUIObject {
    
	FAUSTFLOAT fInit;
	FAUSTFLOAT fMin;
	FAUSTFLOAT fMax;
	FAUSTFLOAT fStep;
    bool fIsVertical;
    
	auBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool isVertical) :
    auUIObject(label, zone), fMin(min), fMax(max), fIsVertical(isVertical)
    {}
    
	virtual ~auBargraph()
    {}
    
	virtual FAUSTFLOAT GetValue()
    {
		return (*fZone - fMin) / (fMax - fMin);
	}	// normalize
    
	virtual void SetValue(double f)
    {
		*fZone = range(fMin, fMax, FAUSTFLOAT(f));
	} // expand
    
};

/**********************************************************************************/

struct auBox: public auUIObject {
    
	vector<auUIObject*> fChildren;
    bool fIsVertical;
    auBox* parent;
    
	auBox(const char* label, auBox* inParent, bool inIsVertical) :
    auUIObject(label, NULL), parent(inParent), fIsVertical(inIsVertical)
    {}
    
    virtual ~auBox()
    {}
  
    void add(auUIObject* child)
    {
        fChildren.push_back(child);
    }
 
};

/**********************************************************************************/
//eunum Direction {HORIZONTAL, VERTICAL}; //TODO

struct auUI: public UI, public MetaDataUI {
    
	vector<auUIObject*> fUITable;
    
    auBox* currentBox = NULL;
    auBox* boundingBox = NULL;
    
	auUI()
    {
        currentBox = boundingBox = new auBox("", NULL, true);
	}
    
	virtual ~auUI()
    {
		for (vector<auUIObject*>::iterator iter = fUITable.begin();
            iter != fUITable.end(); iter++)
			delete *iter;
        // TODO delete boxes
	}
    
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        auButton* button = new auButton(label, zone);
        fUITable.push_back(button);
        currentBox->add(button);
    }
    
    void openTabBox(const char* label)
    {}
    
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        auCheckButton* checkButton= new auCheckButton(label, zone);
        fUITable.push_back(checkButton);
        currentBox->add(checkButton);
    }
    
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        auSlider* slider = new auSlider(label, zone, init, min, max, step, true);
        fUITable.push_back(slider);
        currentBox->add(slider);
    }
    
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        auSlider* slider = new auSlider(label, zone, init, min, max, step, false);
        fUITable.push_back(slider);
        currentBox->add(slider);
    }
    
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        auSlider* slider = new auSlider(label, zone, init, min, max, step, false);
        fUITable.push_back(slider);
        currentBox->add(slider);
    }
    
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        auBargraph* bargraph = new auBargraph(label, zone, min, max, false);
        fUITable.push_back(bargraph);
        currentBox->add(bargraph);
    }
    
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        auBargraph* bargraph = new auBargraph(label, zone, min, max, true);
        fUITable.push_back(bargraph);
        currentBox->add(bargraph);
    }
    
    void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
    void openHorizontalBox(const char* label)
    {
        auBox* box = new auBox(label, currentBox, false);
        currentBox->add(box);
        currentBox = box;
    }
    
    void openVerticalBox(const char* label)
    {
        auBox* box = new auBox(label, currentBox, true);
        currentBox->add(box);
        currentBox = box;
    }
    
    void closeBox()
    {
        if (currentBox) { //TODO else?
            currentBox = currentBox->parent;
        }
    }
    
    void SetValue(int index, double f)
    {
        assert(index < fUITable.size());
        fUITable[index]->SetValue(f);
    }
    
    FAUSTFLOAT GetValue(long index)
    {
        assert(index < fUITable.size());
        return fUITable[index]->GetValue();
    }
    
    void GetDisplay(long index, char *text)
    {
        assert(index < fUITable.size());
        fUITable[index]->GetDisplay(text);
    }
    
    void GetName(long index, char *text)
    {
        assert(index < fUITable.size());
        fUITable[index]->GetName(text);
    }
    
    long GetNumParams()
    {
        return fUITable.size();
    }
    
    long makeID()
    /* Creates a (unique) id by summing all the parameter's labels,
     * then wrapping it in the range [0;maxNumberOfId] and adding
     * this number to the offset made by the Four Character ID: 'FAUS'
     */
    {
        const long maxNumberOfId = 128;
        long baseid = 'FAUS';
        long id = 0;
        for (int i = 0; i < fUITable.size(); i++)
            id += fUITable[i]->GetID();
        return baseid + id % maxNumberOfId;
    }
    
    void addNumDisplay(char* label, FAUSTFLOAT* zone, int precision)
    {}
    
    void addTextDisplay(char* label, FAUSTFLOAT* zone, char* names[], FAUSTFLOAT min, FAUSTFLOAT max)
    {}
    
};


