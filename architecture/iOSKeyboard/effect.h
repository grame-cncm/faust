//----------------------------------------------------------
// name: "freeverb"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c) GRAME 2006"
//
// Code generated with Faust 0.9.73 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------

    This is sample code. This file is provided as an example of minimal
    FAUST architecture file. Redistribution and use in source and binary
    forms, with or without modification, in part or in full are permitted.
    In particular you can create a derived work of this FAUST architecture
    and distribute that work under terms of your choice.

    This sample code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/
 
#include <math.h>
#include <algorithm>

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
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;

//----------------------------------------------------------------
//  Signal processor definition
//----------------------------------------------------------------

class dsp {

    protected:

        int fSamplingFreq;

    public:

        dsp() {}
        virtual ~dsp() {}

        virtual int getNumInputs() = 0;
        virtual int getNumOutputs() = 0;
        virtual void buildUserInterface(UI* ui_interface) = 0;
        virtual void init(int samplingRate) = 0;
        virtual void instanceInit(int samplingRate) = 0;
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

//----------------------------------------------------------------
// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
//----------------------------------------------------------------

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

using std::max;
using std::min;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS effect
#endif

class effect : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fRec9[2];
	int 	IOTA;
	float 	fVec0[2048];
	float 	fRec8[2];
	float 	fRec11[2];
	float 	fVec1[2048];
	float 	fRec10[2];
	float 	fRec13[2];
	float 	fVec2[2048];
	float 	fRec12[2];
	float 	fRec15[2];
	float 	fVec3[2048];
	float 	fRec14[2];
	float 	fRec17[2];
	float 	fVec4[2048];
	float 	fRec16[2];
	float 	fRec19[2];
	float 	fVec5[2048];
	float 	fRec18[2];
	float 	fRec21[2];
	float 	fVec6[2048];
	float 	fRec20[2];
	float 	fRec23[2];
	float 	fVec7[2048];
	float 	fRec22[2];
	float 	fVec8[1024];
	float 	fRec6[2];
	float 	fVec9[512];
	float 	fRec4[2];
	float 	fVec10[512];
	float 	fRec2[2];
	float 	fVec11[256];
	float 	fRec0[2];
	float 	fRec33[2];
	float 	fVec12[2048];
	float 	fRec32[2];
	float 	fRec35[2];
	float 	fVec13[2048];
	float 	fRec34[2];
	float 	fRec37[2];
	float 	fVec14[2048];
	float 	fRec36[2];
	float 	fRec39[2];
	float 	fVec15[2048];
	float 	fRec38[2];
	float 	fRec41[2];
	float 	fVec16[2048];
	float 	fRec40[2];
	float 	fRec43[2];
	float 	fVec17[2048];
	float 	fRec42[2];
	float 	fRec45[2];
	float 	fVec18[2048];
	float 	fRec44[2];
	float 	fRec47[2];
	float 	fVec19[2048];
	float 	fRec46[2];
	float 	fVec20[1024];
	float 	fRec30[2];
	float 	fVec21[512];
	float 	fRec28[2];
	float 	fVec22[512];
	float 	fRec26[2];
	float 	fVec23[256];
	float 	fRec24[2];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "freeverb");
		m->declare("version", "1.0");
		m->declare("author", "Grame");
		m->declare("license", "BSD");
		m->declare("copyright", "(c) GRAME 2006");
		m->declare("reference", "https://ccrma.stanford.edu/~jos/pasp/Freeverb.html");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 0.3333f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		IOTA = 0;
		for (int i=0; i<2048; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2048; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2048; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2048; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2048; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2048; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2048; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2048; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<1024; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<512; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<512; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<256; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2048; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2048; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2048; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2048; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2048; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2048; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2048; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2048; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<1024; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<512; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<512; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<256; i++) fVec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("Freeverb");
		interface->addHorizontalSlider("Damp", &fslider2, 0.5f, 0.0f, 1.0f, 0.025f);
		interface->addHorizontalSlider("RoomSize", &fslider1, 0.5f, 0.0f, 1.0f, 0.025f);
		interface->addHorizontalSlider("Wet", &fslider0, 0.3333f, 0.0f, 1.0f, 0.025f);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = (0.7f + (0.28f * float(fslider1)));
		float 	fSlow2 = (0.4f * float(fslider2));
		float 	fSlow3 = (1 - fSlow2);
		float 	fSlow4 = (1 - fSlow0);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec9[0] = ((fSlow2 * fRec9[1]) + (fSlow3 * fRec8[1]));
			float fTemp0 = (float)input0[i];
			float fTemp1 = (0.03f * fTemp0);
			fVec0[IOTA&2047] = ((fSlow1 * fRec9[0]) + fTemp1);
			fRec8[0] = fVec0[(IOTA-1116)&2047];
			fRec11[0] = ((fSlow2 * fRec11[1]) + (fSlow3 * fRec10[1]));
			fVec1[IOTA&2047] = (fTemp1 + (fSlow1 * fRec11[0]));
			fRec10[0] = fVec1[(IOTA-1188)&2047];
			fRec13[0] = ((fSlow2 * fRec13[1]) + (fSlow3 * fRec12[1]));
			fVec2[IOTA&2047] = (fTemp1 + (fSlow1 * fRec13[0]));
			fRec12[0] = fVec2[(IOTA-1277)&2047];
			fRec15[0] = ((fSlow2 * fRec15[1]) + (fSlow3 * fRec14[1]));
			fVec3[IOTA&2047] = (fTemp1 + (fSlow1 * fRec15[0]));
			fRec14[0] = fVec3[(IOTA-1356)&2047];
			fRec17[0] = ((fSlow2 * fRec17[1]) + (fSlow3 * fRec16[1]));
			fVec4[IOTA&2047] = (fTemp1 + (fSlow1 * fRec17[0]));
			fRec16[0] = fVec4[(IOTA-1422)&2047];
			fRec19[0] = ((fSlow2 * fRec19[1]) + (fSlow3 * fRec18[1]));
			fVec5[IOTA&2047] = (fTemp1 + (fSlow1 * fRec19[0]));
			fRec18[0] = fVec5[(IOTA-1491)&2047];
			fRec21[0] = ((fSlow2 * fRec21[1]) + (fSlow3 * fRec20[1]));
			fVec6[IOTA&2047] = (fTemp1 + (fSlow1 * fRec21[0]));
			fRec20[0] = fVec6[(IOTA-1557)&2047];
			fRec23[0] = ((fSlow2 * fRec23[1]) + (fSlow3 * fRec22[1]));
			fVec7[IOTA&2047] = (fTemp1 + (fSlow1 * fRec23[0]));
			fRec22[0] = fVec7[(IOTA-1617)&2047];
			float fTemp2 = (((((((fRec8[0] + fRec10[0]) + fRec12[0]) + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]);
			fVec8[IOTA&1023] = (fTemp2 + (0.5f * fRec6[1]));
			fRec6[0] = fVec8[(IOTA-556)&1023];
			float 	fRec7 = (0 - (fTemp2 - fRec6[1]));
			fVec9[IOTA&511] = (fRec7 + (0.5f * fRec4[1]));
			fRec4[0] = fVec9[(IOTA-441)&511];
			float 	fRec5 = (fRec4[1] - fRec7);
			fVec10[IOTA&511] = (fRec5 + (0.5f * fRec2[1]));
			fRec2[0] = fVec10[(IOTA-341)&511];
			float 	fRec3 = (fRec2[1] - fRec5);
			fVec11[IOTA&255] = (fRec3 + (0.5f * fRec0[1]));
			fRec0[0] = fVec11[(IOTA-225)&255];
			float 	fRec1 = (fRec0[1] - fRec3);
			float fTemp3 = (fSlow4 * fTemp0);
			output0[i] = (FAUSTFLOAT)((fSlow0 * fRec1) + fTemp3);
			fRec33[0] = ((fSlow2 * fRec33[1]) + (fSlow3 * fRec32[1]));
			fVec12[IOTA&2047] = (fTemp1 + (fSlow1 * fRec33[0]));
			fRec32[0] = fVec12[(IOTA-1139)&2047];
			fRec35[0] = ((fSlow2 * fRec35[1]) + (fSlow3 * fRec34[1]));
			fVec13[IOTA&2047] = (fTemp1 + (fSlow1 * fRec35[0]));
			fRec34[0] = fVec13[(IOTA-1211)&2047];
			fRec37[0] = ((fSlow2 * fRec37[1]) + (fSlow3 * fRec36[1]));
			fVec14[IOTA&2047] = (fTemp1 + (fSlow1 * fRec37[0]));
			fRec36[0] = fVec14[(IOTA-1300)&2047];
			fRec39[0] = ((fSlow2 * fRec39[1]) + (fSlow3 * fRec38[1]));
			fVec15[IOTA&2047] = (fTemp1 + (fSlow1 * fRec39[0]));
			fRec38[0] = fVec15[(IOTA-1379)&2047];
			fRec41[0] = ((fSlow2 * fRec41[1]) + (fSlow3 * fRec40[1]));
			fVec16[IOTA&2047] = (fTemp1 + (fSlow1 * fRec41[0]));
			fRec40[0] = fVec16[(IOTA-1445)&2047];
			fRec43[0] = ((fSlow2 * fRec43[1]) + (fSlow3 * fRec42[1]));
			fVec17[IOTA&2047] = (fTemp1 + (fSlow1 * fRec43[0]));
			fRec42[0] = fVec17[(IOTA-1514)&2047];
			fRec45[0] = ((fSlow2 * fRec45[1]) + (fSlow3 * fRec44[1]));
			fVec18[IOTA&2047] = (fTemp1 + (fSlow1 * fRec45[0]));
			fRec44[0] = fVec18[(IOTA-1580)&2047];
			fRec47[0] = ((fSlow2 * fRec47[1]) + (fSlow3 * fRec46[1]));
			fVec19[IOTA&2047] = (fTemp1 + (fSlow1 * fRec47[0]));
			fRec46[0] = fVec19[(IOTA-1640)&2047];
			float fTemp4 = (((((((fRec32[0] + fRec34[0]) + fRec36[0]) + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) + fRec46[0]);
			fVec20[IOTA&1023] = (fTemp4 + (0.5f * fRec30[1]));
			fRec30[0] = fVec20[(IOTA-579)&1023];
			float 	fRec31 = (0 - (fTemp4 - fRec30[1]));
			fVec21[IOTA&511] = (fRec31 + (0.5f * fRec28[1]));
			fRec28[0] = fVec21[(IOTA-464)&511];
			float 	fRec29 = (fRec28[1] - fRec31);
			fVec22[IOTA&511] = (fRec29 + (0.5f * fRec26[1]));
			fRec26[0] = fVec22[(IOTA-364)&511];
			float 	fRec27 = (fRec26[1] - fRec29);
			fVec23[IOTA&255] = (fRec27 + (0.5f * fRec24[1]));
			fRec24[0] = fVec23[(IOTA-248)&255];
			float 	fRec25 = (fRec24[1] - fRec27);
			output1[i] = (FAUSTFLOAT)(fTemp3 + (fSlow0 * fRec25));
			// post processing
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec40[1] = fRec40[0];
			fRec41[1] = fRec41[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec8[1] = fRec8[0];
			IOTA = IOTA+1;
			fRec9[1] = fRec9[0];
		}
	}
};



