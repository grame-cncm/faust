//----------------------------------------------------------
// author: "O. Guillerminet"
// copyright: "(c) O. Guillerminet 2012"
// license: "BSD"
// name: "UITester"
// version: "1.0"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>

// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fentry2;
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fentry3;
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fbutton1;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fentry4;
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT 	fbargraph5;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "O. Guillerminet");
		m->declare("copyright", "(c) O. Guillerminet 2012");
		m->declare("license", "BSD");
		m->declare("name", "UITester");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 6; }
	virtual int getNumOutputs() { return 34; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fcheckbox1 = 0.0;
		fentry0 = 60.0f;
		fslider0 = 60.0f;
		fslider1 = 60.0f;
		fslider2 = 60.0f;
		fslider3 = 60.0f;
		fslider4 = 60.0f;
		fslider5 = 60.0f;
		fslider6 = 60.0f;
		fbutton0 = 0.0;
		fslider7 = 60.0f;
		fslider8 = 60.0f;
		fslider9 = 60.0f;
		fslider10 = 60.0f;
		fentry1 = 60.0f;
		fslider11 = 60.0f;
		fslider12 = 60.0f;
		fslider13 = 60.0f;
		fentry2 = 60.0f;
		fslider14 = 60.0f;
		fslider15 = 60.0f;
		fslider16 = 60.0f;
		fentry3 = 60.0f;
		fslider17 = 60.0f;
		fbutton1 = 0.0;
		fslider18 = 60.0f;
		fentry4 = 60.0f;
	}
	virtual void instanceClear() {
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openTabBox("grp 1");
		ui_interface->openHorizontalBox("hmisc");
		ui_interface->addButton("button", &fbutton1);
		ui_interface->addHorizontalBargraph("hbar", &fbargraph5, 0.0f, 127.0f);
		ui_interface->addHorizontalSlider("hslider", &fslider18, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry4, "unit", "f");
		ui_interface->addNumEntry("num", &fentry4, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->addVerticalBargraph("vbar", &fbargraph4, 0.0f, 127.0f);
		ui_interface->declare(&fslider17, "unit", "f");
		ui_interface->addVerticalSlider("vslider4", &fslider17, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("knobs");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->addVerticalSlider("knob1", &fslider3, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addVerticalSlider("knob2", &fslider4, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->addVerticalSlider("knob3", &fslider5, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sliders");
		ui_interface->addVerticalSlider("vslider1", &fslider0, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("vslider2", &fslider1, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("vslider3", &fslider2, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vbox");
		ui_interface->addCheckButton("check1", &fcheckbox0);
		ui_interface->addCheckButton("check2", &fcheckbox1);
		ui_interface->declare(&fentry0, "style", "knob");
		ui_interface->addNumEntry("knob0", &fentry0, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vmisc");
		ui_interface->addButton("button", &fbutton0);
		ui_interface->addHorizontalBargraph("hbar", &fbargraph3, 0.0f, 127.0f);
		ui_interface->declare(&fslider7, "unit", "Hz");
		ui_interface->addHorizontalSlider("hslider", &fslider7, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->openHorizontalBox("small box 1");
		ui_interface->declare(&fslider10, "style", "knob");
		ui_interface->addVerticalSlider("knob4", &fslider10, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry1, "unit", "f");
		ui_interface->addNumEntry("num1", &fentry1, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->addVerticalBargraph("vbar1", &fbargraph0, 0.0f, 127.0f);
		ui_interface->declare(&fslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider5", &fslider8, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider9, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider6", &fslider9, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sub box 1");
		ui_interface->openHorizontalBox("small box 2");
		ui_interface->declare(&fslider13, "style", "knob");
		ui_interface->addVerticalSlider("knob5", &fslider13, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry2, "unit", "f");
		ui_interface->addNumEntry("num2", &fentry2, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->addVerticalBargraph("vbar2", &fbargraph1, 0.0f, 127.0f);
		ui_interface->declare(&fslider11, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider7", &fslider11, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider12, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider8", &fslider12, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("small box 3");
		ui_interface->declare(&fslider16, "style", "knob");
		ui_interface->addVerticalSlider("knob6", &fslider16, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fentry3, "unit", "f");
		ui_interface->addNumEntry("num3", &fentry3, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->addVerticalBargraph("vbar3", &fbargraph2, 0.0f, 127.0f);
		ui_interface->declare(&fslider15, "unit", "m");
		ui_interface->addVerticalSlider("vslider10", &fslider15, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->declare(&fslider14, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider9", &fslider14, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fslider6, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider4", &fslider6, 60.0f, 0.0f, 127.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fcheckbox0);
		float 	fSlow1 = float(fcheckbox1);
		float 	fSlow2 = float(fentry0);
		float 	fSlow3 = float(fslider0);
		float 	fSlow4 = float(fslider1);
		float 	fSlow5 = float(fslider2);
		float 	fSlow6 = float(fslider3);
		float 	fSlow7 = float(fslider4);
		float 	fSlow8 = float(fslider5);
		float 	fSlow9 = float(fslider6);
		float 	fSlow10 = float(fbutton0);
		float 	fSlow11 = float(fslider7);
		float 	fSlow12 = float(fslider8);
		float 	fSlow13 = float(fslider9);
		float 	fSlow14 = float(fslider10);
		float 	fSlow15 = float(fentry1);
		float 	fSlow16 = float(fslider11);
		float 	fSlow17 = float(fslider12);
		float 	fSlow18 = float(fslider13);
		float 	fSlow19 = float(fentry2);
		float 	fSlow20 = float(fslider14);
		float 	fSlow21 = float(fslider15);
		float 	fSlow22 = float(fslider16);
		float 	fSlow23 = float(fentry3);
		float 	fSlow24 = float(fslider17);
		float 	fSlow25 = float(fbutton1);
		float 	fSlow26 = float(fslider18);
		float 	fSlow27 = float(fentry4);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* input5 = input[5];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		FAUSTFLOAT* output8 = output[8];
		FAUSTFLOAT* output9 = output[9];
		FAUSTFLOAT* output10 = output[10];
		FAUSTFLOAT* output11 = output[11];
		FAUSTFLOAT* output12 = output[12];
		FAUSTFLOAT* output13 = output[13];
		FAUSTFLOAT* output14 = output[14];
		FAUSTFLOAT* output15 = output[15];
		FAUSTFLOAT* output16 = output[16];
		FAUSTFLOAT* output17 = output[17];
		FAUSTFLOAT* output18 = output[18];
		FAUSTFLOAT* output19 = output[19];
		FAUSTFLOAT* output20 = output[20];
		FAUSTFLOAT* output21 = output[21];
		FAUSTFLOAT* output22 = output[22];
		FAUSTFLOAT* output23 = output[23];
		FAUSTFLOAT* output24 = output[24];
		FAUSTFLOAT* output25 = output[25];
		FAUSTFLOAT* output26 = output[26];
		FAUSTFLOAT* output27 = output[27];
		FAUSTFLOAT* output28 = output[28];
		FAUSTFLOAT* output29 = output[29];
		FAUSTFLOAT* output30 = output[30];
		FAUSTFLOAT* output31 = output[31];
		FAUSTFLOAT* output32 = output[32];
		FAUSTFLOAT* output33 = output[33];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			output0[i] = (FAUSTFLOAT)fSlow0;
			output1[i] = (FAUSTFLOAT)fSlow1;
			output2[i] = (FAUSTFLOAT)fSlow2;
			output3[i] = (FAUSTFLOAT)fSlow3;
			output4[i] = (FAUSTFLOAT)fSlow4;
			output5[i] = (FAUSTFLOAT)fSlow5;
			output6[i] = (FAUSTFLOAT)fSlow6;
			output7[i] = (FAUSTFLOAT)fSlow7;
			output8[i] = (FAUSTFLOAT)fSlow8;
			output9[i] = (FAUSTFLOAT)fSlow9;
			output10[i] = (FAUSTFLOAT)fSlow10;
			output11[i] = (FAUSTFLOAT)fSlow11;
			output12[i] = (FAUSTFLOAT)fSlow12;
			output13[i] = (FAUSTFLOAT)fSlow13;
			output14[i] = (FAUSTFLOAT)fSlow14;
			output15[i] = (FAUSTFLOAT)fSlow15;
			fbargraph0 = (float)input0[i];
			output16[i] = (FAUSTFLOAT)fbargraph0;
			output17[i] = (FAUSTFLOAT)fSlow16;
			output18[i] = (FAUSTFLOAT)fSlow17;
			output19[i] = (FAUSTFLOAT)fSlow18;
			output20[i] = (FAUSTFLOAT)fSlow19;
			fbargraph1 = (float)input1[i];
			output21[i] = (FAUSTFLOAT)fbargraph1;
			output22[i] = (FAUSTFLOAT)fSlow20;
			output23[i] = (FAUSTFLOAT)fSlow21;
			output24[i] = (FAUSTFLOAT)fSlow22;
			output25[i] = (FAUSTFLOAT)fSlow23;
			fbargraph2 = (float)input2[i];
			output26[i] = (FAUSTFLOAT)fbargraph2;
			fbargraph3 = (float)input3[i];
			output27[i] = (FAUSTFLOAT)fbargraph3;
			output28[i] = (FAUSTFLOAT)fSlow24;
			output29[i] = (FAUSTFLOAT)fSlow25;
			output30[i] = (FAUSTFLOAT)fSlow26;
			output31[i] = (FAUSTFLOAT)fSlow27;
			fbargraph4 = (float)input4[i];
			output32[i] = (FAUSTFLOAT)fbargraph4;
			fbargraph5 = (float)input5[i];
			output33[i] = (FAUSTFLOAT)fbargraph5;
		}
	}
};


