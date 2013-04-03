/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
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

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <math.h>


#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif


//********************************************************
// Added elements
//********************************************************

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

class UI
{

 public:

	UI() {
		//addaddHorizontalSlider
	}

	virtual ~UI() {}

	virtual void initUI(void) = 0;

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

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
};

class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}

	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 	= 0;
};

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
};

class GUI : public UI {
	public:
	struct para {
		int cnt;
		int cntLay;
		int cntEl;
		int typeEl[numbLayouts*2+numbParams];
		int typeLay[numbLayouts*2];
		const char *labelLay[numbLayouts*2];
		int type[numbParams];
		int layoutEl[numbLayouts*2];
		const char *label[numbParams];
		float *value[numbParams];
		float init[numbParams];
		float min[numbParams];
		float max[numbParams];
		float step[numbParams];
	} params;

		virtual void initUI() {
			params.cnt=0;
			params.cntLay=0;
			params.cntEl=0;
		};

		// -- widget's layouts

	    virtual void openTabBox(const char* label) {};
	    virtual void openHorizontalBox(const char* label) {
	    	params.typeLay[params.cntLay] = 0;
	    	params.labelLay[params.cntLay] = label;
	    	params.typeEl[params.cntEl] = 0;
	    	params.cntLay++;
	    	params.cntEl++;
	    };
	    virtual void openVerticalBox(const char* label) {
	    	params.typeLay[params.cntLay] = 1;
	    	params.labelLay[params.cntLay] = label;
	    	params.typeEl[params.cntEl] = 0;
	    	params.cntLay++;
	    	params.cntEl++;
	    };
	    virtual void closeBox() {
	    	params.typeLay[params.cntLay] = 2;
	    	params.typeEl[params.cntEl] = 0;
	    	params.cntLay++;
	    	params.cntEl++;
	    };

	    // -- active widgets

	    virtual void addButton(const char* label, FAUSTFLOAT* zone) {
	    	params.type[params.cnt] = 0;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.typeEl[params.cntEl] = 1;
	    	params.cnt++;
	    	params.cntEl++;
	    };
	    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {
	    	params.type[params.cnt] = 1;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.typeEl[params.cntEl] = 1;
	    	params.cnt++;
	    	params.cntEl++;
	    };
	    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
	    	params.type[params.cnt] = 2;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.init[params.cnt] = init;
	    	params.min[params.cnt] = min;
	    	params.max[params.cnt] = max;
	    	params.step[params.cnt] = step;
	    	params.typeEl[params.cntEl] = 1;
	    	params.cnt++;
	    	params.cntEl++;
	    };
	    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
	    	params.type[params.cnt] = 3;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.init[params.cnt] = init;
	    	params.min[params.cnt] = min;
	    	params.max[params.cnt] = max;
	    	params.step[params.cnt] = step;
	    	params.typeEl[params.cntEl] = 1;
	    	params.cnt++;
	    	params.cntEl++;
	    };
	    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
	    	params.type[params.cnt] = 4;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.init[params.cnt] = init;
	    	params.min[params.cnt] = min;
	    	params.max[params.cnt] = max;
	    	params.step[params.cnt] = step;
	    	params.typeEl[params.cntEl] = 1;
	    	params.cnt++;
	    	params.cntEl++;
	    };

	    // -- passive widgets

	    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {};
	    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {};

		// -- metadata declarations

	    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
};

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>
