//----------------------------------------------------------
// author: "Grame"
// copyright: "(c)GRAME 2006"
// license: "BSD"
// name: "matrix"
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
	FAUSTFLOAT 	fslider0;
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider1;
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider2;
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider3;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider4;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider5;
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider6;
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider7;
	float 	fTempPerm7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fslider37;
	FAUSTFLOAT 	fslider38;
	FAUSTFLOAT 	fslider39;
	FAUSTFLOAT 	fslider40;
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fslider43;
	FAUSTFLOAT 	fslider44;
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fslider46;
	FAUSTFLOAT 	fslider47;
	FAUSTFLOAT 	fslider48;
	FAUSTFLOAT 	fslider49;
	FAUSTFLOAT 	fslider50;
	FAUSTFLOAT 	fslider51;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	FAUSTFLOAT 	fslider54;
	FAUSTFLOAT 	fslider55;
	FAUSTFLOAT 	fslider56;
	FAUSTFLOAT 	fslider57;
	FAUSTFLOAT 	fslider58;
	FAUSTFLOAT 	fslider59;
	FAUSTFLOAT 	fslider60;
	FAUSTFLOAT 	fslider61;
	FAUSTFLOAT 	fslider62;
	FAUSTFLOAT 	fslider63;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("name", "matrix");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() { return 8; }
	virtual int getNumOutputs() { return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = -10.0f;
		fslider1 = -10.0f;
		fslider2 = -10.0f;
		fslider3 = -10.0f;
		fslider4 = -10.0f;
		fslider5 = -10.0f;
		fslider6 = -10.0f;
		fslider7 = -10.0f;
		fslider8 = -10.0f;
		fslider9 = -10.0f;
		fslider10 = -10.0f;
		fslider11 = -10.0f;
		fslider12 = -10.0f;
		fslider13 = -10.0f;
		fslider14 = -10.0f;
		fslider15 = -10.0f;
		fslider16 = -10.0f;
		fslider17 = -10.0f;
		fslider18 = -10.0f;
		fslider19 = -10.0f;
		fslider20 = -10.0f;
		fslider21 = -10.0f;
		fslider22 = -10.0f;
		fslider23 = -10.0f;
		fslider24 = -10.0f;
		fslider25 = -10.0f;
		fslider26 = -10.0f;
		fslider27 = -10.0f;
		fslider28 = -10.0f;
		fslider29 = -10.0f;
		fslider30 = -10.0f;
		fslider31 = -10.0f;
		fslider32 = -10.0f;
		fslider33 = -10.0f;
		fslider34 = -10.0f;
		fslider35 = -10.0f;
		fslider36 = -10.0f;
		fslider37 = -10.0f;
		fslider38 = -10.0f;
		fslider39 = -10.0f;
		fslider40 = -10.0f;
		fslider41 = -10.0f;
		fslider42 = -10.0f;
		fslider43 = -10.0f;
		fslider44 = -10.0f;
		fslider45 = -10.0f;
		fslider46 = -10.0f;
		fslider47 = -10.0f;
		fslider48 = -10.0f;
		fslider49 = -10.0f;
		fslider50 = -10.0f;
		fslider51 = -10.0f;
		fslider52 = -10.0f;
		fslider53 = -10.0f;
		fslider54 = -10.0f;
		fslider55 = -10.0f;
		fslider56 = -10.0f;
		fslider57 = -10.0f;
		fslider58 = -10.0f;
		fslider59 = -10.0f;
		fslider60 = -10.0f;
		fslider61 = -10.0f;
		fslider62 = -10.0f;
		fslider63 = -10.0f;
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
		ui_interface->openTabBox("Matrix 8 x 8");
		ui_interface->openHorizontalBox("Output 0");
		ui_interface->addVerticalSlider("Input 0", &fslider0, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider1, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider2, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider3, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider4, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider5, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider6, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider7, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 1");
		ui_interface->addVerticalSlider("Input 0", &fslider8, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider9, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider10, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider11, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider12, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider13, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider14, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider15, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 2");
		ui_interface->addVerticalSlider("Input 0", &fslider16, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider17, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider18, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider19, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider20, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider21, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider22, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider23, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 3");
		ui_interface->addVerticalSlider("Input 0", &fslider24, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider25, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider26, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider27, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider28, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider29, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider30, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider31, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 4");
		ui_interface->addVerticalSlider("Input 0", &fslider32, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider33, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider34, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider35, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider36, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider37, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider38, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider39, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 5");
		ui_interface->addVerticalSlider("Input 0", &fslider40, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider41, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider42, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider43, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider44, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider45, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider46, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider47, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 6");
		ui_interface->addVerticalSlider("Input 0", &fslider48, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider49, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider50, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider51, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider52, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider53, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider54, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider55, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output 7");
		ui_interface->addVerticalSlider("Input 0", &fslider56, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 1", &fslider57, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 2", &fslider58, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 3", &fslider59, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 4", &fslider60, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 5", &fslider61, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 6", &fslider62, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->addVerticalSlider("Input 7", &fslider63, -10.0f, -96.0f, 4.0f, 0.10000000000000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = powf(10,(0.050000000000000003f * float(fslider0)));
		float 	fSlow1 = powf(10,(0.050000000000000003f * float(fslider1)));
		float 	fSlow2 = powf(10,(0.050000000000000003f * float(fslider2)));
		float 	fSlow3 = powf(10,(0.050000000000000003f * float(fslider3)));
		float 	fSlow4 = powf(10,(0.050000000000000003f * float(fslider4)));
		float 	fSlow5 = powf(10,(0.050000000000000003f * float(fslider5)));
		float 	fSlow6 = powf(10,(0.050000000000000003f * float(fslider6)));
		float 	fSlow7 = powf(10,(0.050000000000000003f * float(fslider7)));
		float 	fSlow8 = powf(10,(0.050000000000000003f * float(fslider8)));
		float 	fSlow9 = powf(10,(0.050000000000000003f * float(fslider9)));
		float 	fSlow10 = powf(10,(0.050000000000000003f * float(fslider10)));
		float 	fSlow11 = powf(10,(0.050000000000000003f * float(fslider11)));
		float 	fSlow12 = powf(10,(0.050000000000000003f * float(fslider12)));
		float 	fSlow13 = powf(10,(0.050000000000000003f * float(fslider13)));
		float 	fSlow14 = powf(10,(0.050000000000000003f * float(fslider14)));
		float 	fSlow15 = powf(10,(0.050000000000000003f * float(fslider15)));
		float 	fSlow16 = powf(10,(0.050000000000000003f * float(fslider16)));
		float 	fSlow17 = powf(10,(0.050000000000000003f * float(fslider17)));
		float 	fSlow18 = powf(10,(0.050000000000000003f * float(fslider18)));
		float 	fSlow19 = powf(10,(0.050000000000000003f * float(fslider19)));
		float 	fSlow20 = powf(10,(0.050000000000000003f * float(fslider20)));
		float 	fSlow21 = powf(10,(0.050000000000000003f * float(fslider21)));
		float 	fSlow22 = powf(10,(0.050000000000000003f * float(fslider22)));
		float 	fSlow23 = powf(10,(0.050000000000000003f * float(fslider23)));
		float 	fSlow24 = powf(10,(0.050000000000000003f * float(fslider24)));
		float 	fSlow25 = powf(10,(0.050000000000000003f * float(fslider25)));
		float 	fSlow26 = powf(10,(0.050000000000000003f * float(fslider26)));
		float 	fSlow27 = powf(10,(0.050000000000000003f * float(fslider27)));
		float 	fSlow28 = powf(10,(0.050000000000000003f * float(fslider28)));
		float 	fSlow29 = powf(10,(0.050000000000000003f * float(fslider29)));
		float 	fSlow30 = powf(10,(0.050000000000000003f * float(fslider30)));
		float 	fSlow31 = powf(10,(0.050000000000000003f * float(fslider31)));
		float 	fSlow32 = powf(10,(0.050000000000000003f * float(fslider32)));
		float 	fSlow33 = powf(10,(0.050000000000000003f * float(fslider33)));
		float 	fSlow34 = powf(10,(0.050000000000000003f * float(fslider34)));
		float 	fSlow35 = powf(10,(0.050000000000000003f * float(fslider35)));
		float 	fSlow36 = powf(10,(0.050000000000000003f * float(fslider36)));
		float 	fSlow37 = powf(10,(0.050000000000000003f * float(fslider37)));
		float 	fSlow38 = powf(10,(0.050000000000000003f * float(fslider38)));
		float 	fSlow39 = powf(10,(0.050000000000000003f * float(fslider39)));
		float 	fSlow40 = powf(10,(0.050000000000000003f * float(fslider40)));
		float 	fSlow41 = powf(10,(0.050000000000000003f * float(fslider41)));
		float 	fSlow42 = powf(10,(0.050000000000000003f * float(fslider42)));
		float 	fSlow43 = powf(10,(0.050000000000000003f * float(fslider43)));
		float 	fSlow44 = powf(10,(0.050000000000000003f * float(fslider44)));
		float 	fSlow45 = powf(10,(0.050000000000000003f * float(fslider45)));
		float 	fSlow46 = powf(10,(0.050000000000000003f * float(fslider46)));
		float 	fSlow47 = powf(10,(0.050000000000000003f * float(fslider47)));
		float 	fSlow48 = powf(10,(0.050000000000000003f * float(fslider48)));
		float 	fSlow49 = powf(10,(0.050000000000000003f * float(fslider49)));
		float 	fSlow50 = powf(10,(0.050000000000000003f * float(fslider50)));
		float 	fSlow51 = powf(10,(0.050000000000000003f * float(fslider51)));
		float 	fSlow52 = powf(10,(0.050000000000000003f * float(fslider52)));
		float 	fSlow53 = powf(10,(0.050000000000000003f * float(fslider53)));
		float 	fSlow54 = powf(10,(0.050000000000000003f * float(fslider54)));
		float 	fSlow55 = powf(10,(0.050000000000000003f * float(fslider55)));
		float 	fSlow56 = powf(10,(0.050000000000000003f * float(fslider56)));
		float 	fSlow57 = powf(10,(0.050000000000000003f * float(fslider57)));
		float 	fSlow58 = powf(10,(0.050000000000000003f * float(fslider58)));
		float 	fSlow59 = powf(10,(0.050000000000000003f * float(fslider59)));
		float 	fSlow60 = powf(10,(0.050000000000000003f * float(fslider60)));
		float 	fSlow61 = powf(10,(0.050000000000000003f * float(fslider61)));
		float 	fSlow62 = powf(10,(0.050000000000000003f * float(fslider62)));
		float 	fSlow63 = powf(10,(0.050000000000000003f * float(fslider63)));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* input5 = input[5];
		FAUSTFLOAT* input6 = input[6];
		FAUSTFLOAT* input7 = input[7];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fTempPerm1 = (float)input1[i];
			fTempPerm2 = (float)input2[i];
			fTempPerm3 = (float)input3[i];
			fTempPerm4 = (float)input4[i];
			fTempPerm5 = (float)input5[i];
			fTempPerm6 = (float)input6[i];
			fTempPerm7 = (float)input7[i];
			output0[i] = (FAUSTFLOAT)((((((((fSlow0 * fTempPerm0) + (fSlow1 * fTempPerm1)) + (fSlow2 * fTempPerm2)) + (fSlow3 * fTempPerm3)) + (fSlow4 * fTempPerm4)) + (fSlow5 * fTempPerm5)) + (fSlow6 * fTempPerm6)) + (fSlow7 * fTempPerm7));
			output1[i] = (FAUSTFLOAT)((((((((fSlow8 * fTempPerm0) + (fSlow9 * fTempPerm1)) + (fSlow10 * fTempPerm2)) + (fSlow11 * fTempPerm3)) + (fSlow12 * fTempPerm4)) + (fSlow13 * fTempPerm5)) + (fSlow14 * fTempPerm6)) + (fSlow15 * fTempPerm7));
			output2[i] = (FAUSTFLOAT)((((((((fSlow16 * fTempPerm0) + (fSlow17 * fTempPerm1)) + (fSlow18 * fTempPerm2)) + (fSlow19 * fTempPerm3)) + (fSlow20 * fTempPerm4)) + (fSlow21 * fTempPerm5)) + (fSlow22 * fTempPerm6)) + (fSlow23 * fTempPerm7));
			output3[i] = (FAUSTFLOAT)((((((((fSlow24 * fTempPerm0) + (fSlow25 * fTempPerm1)) + (fSlow26 * fTempPerm2)) + (fSlow27 * fTempPerm3)) + (fSlow28 * fTempPerm4)) + (fSlow29 * fTempPerm5)) + (fSlow30 * fTempPerm6)) + (fSlow31 * fTempPerm7));
			output4[i] = (FAUSTFLOAT)((((((((fSlow32 * fTempPerm0) + (fSlow33 * fTempPerm1)) + (fSlow34 * fTempPerm2)) + (fSlow35 * fTempPerm3)) + (fSlow36 * fTempPerm4)) + (fSlow37 * fTempPerm5)) + (fSlow38 * fTempPerm6)) + (fSlow39 * fTempPerm7));
			output5[i] = (FAUSTFLOAT)((((((((fSlow40 * fTempPerm0) + (fSlow41 * fTempPerm1)) + (fSlow42 * fTempPerm2)) + (fSlow43 * fTempPerm3)) + (fSlow44 * fTempPerm4)) + (fSlow45 * fTempPerm5)) + (fSlow46 * fTempPerm6)) + (fSlow47 * fTempPerm7));
			output6[i] = (FAUSTFLOAT)((((((((fSlow48 * fTempPerm0) + (fSlow49 * fTempPerm1)) + (fSlow50 * fTempPerm2)) + (fSlow51 * fTempPerm3)) + (fSlow52 * fTempPerm4)) + (fSlow53 * fTempPerm5)) + (fSlow54 * fTempPerm6)) + (fSlow55 * fTempPerm7));
			output7[i] = (FAUSTFLOAT)((((((((fSlow56 * fTempPerm0) + (fSlow57 * fTempPerm1)) + (fSlow58 * fTempPerm2)) + (fSlow59 * fTempPerm3)) + (fSlow60 * fTempPerm4)) + (fSlow61 * fTempPerm5)) + (fSlow62 * fTempPerm6)) + (fSlow63 * fTempPerm7));
		}
	}
};


