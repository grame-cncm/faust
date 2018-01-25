/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "KarplusStrong"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fHslider0;
	float fRec11[] = new float[2];
	int IOTA;
	float fRec7[] = new float[2048];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fHslider1;
	float fHslider2;
	float fButton0;
	float fHslider3;
	float fVec0[] = new float[2];
	float fRec12[] = new float[2];
	float fHslider4;
	float fVec1[] = new float[2048];
	float fRec3[] = new float[2];
	float fRec0[] = new float[3];
	float fRec1[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple call of the Karplus-Strong model for the Faust physical modeling library");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "KarplusStrong");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	int getNumInputs() {
		return 0;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	public void classInit(int samplingFreq) {
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		fConst1 = (0.00882352982f * fConst0);
		fConst2 = (0.00147058826f * fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.01f;
		fHslider1 = (float)440.0f;
		fHslider2 = (float)1.0f;
		fButton0 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.80000000000000004f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec11[l0] = 0.0f;
			
		}
		IOTA = 0;
		for (int l1 = 0; (l1 < 2048); l1 = (l1 + 1)) {
			fRec7[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec12[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec3[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec1[l7] = 0.0f;
			
		}
		
	}
	
	public void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	public void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	public void buildUserInterface(UI ui_interface) {
		ui_interface.openVerticalBox("karplus");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("params");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "hidden", "1");
		ui_interface.declare("fHslider2", "midi", "pitchwheel");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("bend", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "midi", "ctrl 1");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("damping", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.00999999978f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "ctrl 64");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "1", "");
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * fHslider0);
		float fSlow1 = (340.0f / fHslider1);
		float fSlow2 = fHslider2;
		float fSlow3 = (float)java.lang.Math.min(1.0f, (fButton0 + fHslider3));
		int iSlow4 = (fSlow3 == 0.0f);
		float fSlow5 = fHslider4;
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec11[0] = (fSlow0 + (0.999000013f * fRec11[1]));
			float fTemp0 = (0.5f * ((fRec1[1] + fRec1[2]) * ((0.200000003f * (1.0f - fRec11[0])) + 0.800000012f)));
			fRec7[(IOTA & 2047)] = fTemp0;
			fVec0[0] = fSlow3;
			int iTemp1 = ((((fSlow3 == fVec0[1]))?1:0) | iSlow4);
			fRec12[0] = ((fSlow2 * (1.0f - (0.999000013f * (float)iTemp1))) + (0.999000013f * ((float)iTemp1 * fRec12[1])));
			float fTemp2 = (fConst2 * ((fSlow1 / fRec12[0]) + -0.0500000007f));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = (int)fTemp3;
			int iTemp5 = ((int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, iTemp4)) + 1);
			float fTemp6 = (float)java.lang.Math.floor(fTemp3);
			float fTemp7 = (fTemp2 + (-1.0f - fTemp6));
			float fTemp8 = (0.0f - fTemp7);
			float fTemp9 = (fTemp2 + (-2.0f - fTemp6));
			float fTemp10 = (0.0f - (0.5f * fTemp9));
			float fTemp11 = (fTemp2 + (-3.0f - fTemp6));
			float fTemp12 = (0.0f - (0.333333343f * fTemp11));
			float fTemp13 = (fTemp2 + (-4.0f - fTemp6));
			float fTemp14 = (0.0f - (0.25f * fTemp13));
			float fTemp15 = (fTemp2 - fTemp6);
			int iTemp16 = ((int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 2))) + 1);
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = ((int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 1))) + 1);
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = ((int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 3))) + 1);
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = ((int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 4))) + 1);
			float fRec8 = (((((fRec7[((IOTA - iTemp5) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * fRec7[((IOTA - iTemp16) & 2047)]) * fTemp17) * fTemp18)) + (((fRec7[((IOTA - iTemp19) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * fRec7[((IOTA - iTemp24) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * fRec7[((IOTA - iTemp27) & 2047)])))));
			float fTemp28 = (fSlow5 * ((((fSlow3 - fVec0[1]) > 0.0f))?1.f:0.f));
			float fTemp29 = (fRec0[2] + fTemp28);
			fVec1[(IOTA & 2047)] = fTemp29;
			float fTemp30 = ((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * fVec1[((IOTA - iTemp5) & 2047)]);
			float fTemp31 = (fTemp15 * (((0.166666672f * ((fTemp23 * fTemp25) * fVec1[((IOTA - iTemp24) & 2047)])) + ((((fTemp20 * fTemp21) * fTemp22) * fVec1[((IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * fVec1[((IOTA - iTemp16) & 2047)])))) + (0.0416666679f * (fTemp26 * fVec1[((IOTA - iTemp27) & 2047)]))));
			float fRec9 = (fTemp30 + fTemp31);
			float fRec10 = ((fTemp0 + fTemp30) + fTemp31);
			fRec3[0] = fRec8;
			float fRec4 = (fTemp28 + fRec3[1]);
			float fRec5 = fRec9;
			float fRec6 = fRec10;
			fRec0[0] = fRec4;
			fRec1[0] = fRec5;
			float fRec2 = fRec6;
			output0[i] = fRec2;
			output1[i] = fRec2;
			fRec11[1] = fRec11[0];
			IOTA = (IOTA + 1);
			fVec0[1] = fVec0[0];
			fRec12[1] = fRec12[0];
			fRec3[1] = fRec3[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			
		}
		
	}
	
};

