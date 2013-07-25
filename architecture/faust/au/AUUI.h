/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

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

#include "faust/gui/UI.h"

using namespace std;

class auUI;

class auUIObject {
public:
	string fLabel;
	float* fZone;
    
	float range(float min, float max, float val) { // AU parameters are normalized in the range [0;1]
		val = min + val * (max - min);
		return (val < min) ? min : (val > max) ? max : val;
	}
    
public:
	auUIObject(const char* label, FAUSTFLOAT* zone) :
        fLabel(label), fZone(zone) {
	}
    
	virtual ~auUIObject() {
	}
    
	virtual void GetName(char *text) {
		std::strcpy(text, fLabel.c_str());
	}
    
	virtual void SetValue(double f) {
		*fZone = range(0.0f, 1.0f, (float) f);
	}
    
	virtual float GetValue() {
		return *fZone;
	}
    
	virtual void GetDisplay(char *text) {
		std::sprintf(text, "%f", *fZone);
	}
    
	virtual long GetID() { /* returns the sum of all the ASCII characters  contained in the parameter's label */
		int i;
		long acc;
		for (i = 0, acc = 0; i < fLabel.length(); i++)
			acc += (fLabel.c_str())[i];
		return acc;
	}
};

/**********************************************************************************/
class auToggleButton: public auUIObject {
    
public:
    
	auToggleButton(const char* label, FAUSTFLOAT* zone) :
        auUIObject(label, zone) {
	}
    
	virtual ~auToggleButton() {
	}
    
	virtual float GetValue() {
		return *fZone;
	}
    
	virtual void SetValue(double f) {
		*fZone = (f > 0.5f) ? 1.0f : 0.0f;
	}
    
	virtual void GetDisplay(char *text) {
		(*fZone > 0.5f) ? std::strcpy(text, "ON") : std::strcpy(text, "OFF");
	}
};

/**********************************************************************************/
class auCheckButton: public auUIObject {
    
public:
    
	auCheckButton(const char* label, FAUSTFLOAT* zone) :
        auUIObject(label, zone) {
	}
    
	virtual ~auCheckButton() {
	}
    
	virtual float GetValue() {
		return *fZone;
	}
    
	virtual void SetValue(double f) {
		*fZone = (f > 0.5f) ? 1.0f : 0.0f;
	}
    
	virtual void GetDisplay(char *text) {
		(*fZone > 0.5f) ? std::strcpy(text, "ON") : std::strcpy(text, "OFF");
	}
};

/**********************************************************************************/
class auButton: public auUIObject {
    
public:
    
	auButton(const char* label, FAUSTFLOAT* zone) :
        auUIObject(label, zone) {
	}
    
	virtual ~auButton() {
	}
    
	virtual float GetValue() {
		return *fZone;
	}
    
	virtual void SetValue(double f) {
		*fZone = (f > 0.5f) ? 1.0f : 0.0f;
	}
    
	virtual void GetDisplay(char *text) {
		(*fZone > 0.5f) ? std::strcpy(text, "ON") : std::strcpy(text, "OFF");
	}
};

/**********************************************************************************/
class auSlider: public auUIObject {
    
public:
	float fInit;
	float fMin;
	float fMax;
	float fStep;
    
public:
    
	auSlider(const char* label, FAUSTFLOAT* zone, float init, float min, float max,
             float step) :
    auUIObject(label, zone), fInit(init), fMin(min), fMax(max), fStep(
                                                                      step) {
	}
    
	virtual ~auSlider() {
	}
    
	virtual float GetValue() {
		return (*fZone - fMin) / (fMax - fMin);
	}	// normalize
    
	virtual void SetValue(double f) {
		*fZone = range(fMin, fMax, (float) f);
	} // expand
};

/**********************************************************************************/
class auUI: public UI {
public:
    
	vector<auUIObject*> fUITable;
    
public:
    
	auUI() {
	}
    
	virtual ~auUI() {
		for (vector<auUIObject*>::iterator iter = fUITable.begin();
             iter != fUITable.end(); iter++)
			delete *iter;
	}
    
	 void addButton(const char* label, FAUSTFLOAT* zone) {
		fUITable.push_back(new auButton(label, zone));
	}
    
    void openTabBox(const char* label) {
        
    }
    
    void closeBox() {
        
    }

    
	void addCheckButton(const char* label, FAUSTFLOAT* zone) {
		fUITable.push_back(new auCheckButton(label, zone));
	}
    
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, float init, float min,
                           float max, float step) {
		fUITable.push_back(new auSlider(label, zone, init, min, max, step));
	}
    
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, float init, float min,
                             float max, float step) {
		fUITable.push_back(new auSlider(label, zone, init, min, max, step));
	}
    
	void addNumEntry(const char* label, FAUSTFLOAT* zone, float init, float min, float max,
                     float step) {
		fUITable.push_back(new auSlider(label, zone, init, min, max, step));
	}

	void openHorizontalBox(const char* label) {
	}
    
	void openVerticalBox(const char* label) {
	}
    
	void SetValue(int index, double f) {
		assert(index < fUITable.size());
		fUITable[index]->SetValue(f);
	}
    
	float GetValue(long index) {
		assert(index < fUITable.size());
		return fUITable[index]->GetValue();
	}
    
	void GetDisplay(long index, char *text) {
		assert(index < fUITable.size());
		fUITable[index]->GetDisplay(text);
	}
    
	void GetName(long index, char *text) {
		assert(index < fUITable.size());
		fUITable[index]->GetName(text);
	}
    
	long GetNumParams() {
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
    
	void addNumDisplay(char* label, float* zone, int precision) {
	}
    
	void addTextDisplay(char* label, float* zone, char* names[], float min,
                        float max) {
	}
    
	void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, float min, float max) {
	}
    
	void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, float min, float max) {
	}
};


