/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Clarinet"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	int iRec6[] = new int[2];
	float fHslider1;
	int iVec0[] = new int[2];
	float fRec13[] = new float[2];
	float fHslider2;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider3;
	float fRec17[] = new float[2];
	float fRec18[] = new float[2];
	float fHslider4;
	float fRec19[] = new float[2];
	float fHslider5;
	float fConst2;
	float fHslider6;
	int iRec21[] = new int[2];
	float fRec20[] = new float[3];
	float fRec14[] = new float[2];
	float fHslider7;
	int IOTA;
	float fRec15[] = new float[2048];
	float fConst3;
	float fConst4;
	float fHslider8;
	float fRec22[] = new float[2];
	float fVec1[] = new float[2];
	float fRec11[] = new float[2];
	float fRec2[] = new float[2048];
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple clarinet physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Clarinet");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
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
		fConst1 = (6.28318548f / fConst0);
		fConst2 = (3.14159274f / fConst0);
		fConst3 = (0.00882352982f * fConst0);
		fConst4 = (0.00147058826f * fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.5f;
		fHslider2 = (float)0.25f;
		fHslider3 = (float)5.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)0.10000000000000001f;
		fHslider6 = (float)2000.0f;
		fHslider7 = (float)0.5f;
		fHslider8 = (float)0.80000000000000004f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec6[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec13[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec17[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec18[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec19[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec21[l6] = 0;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec20[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec14[l8] = 0.0f;
			
		}
		IOTA = 0;
		for (int l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			fRec15[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec22[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec1[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec11[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			fRec2[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec0[l14] = 0.0f;
			
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
		ui_interface.openHorizontalBox("clarinet");
		ui_interface.openVerticalBox("blower");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.addHorizontalSlider("pressure", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.addHorizontalSlider("breathGain", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider6", "2", "");
		ui_interface.addHorizontalSlider("breathCutoff", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 2000.0f, 20.0f, 20000.0f, 0.100000001f);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.addHorizontalSlider("vibratoFreq", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 5.0f, 0.100000001f, 10.0f, 0.100000001f);
		ui_interface.declare("fHslider2", "4", "");
		ui_interface.addHorizontalSlider("vibratoGain", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.25f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("clarinetModel");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.addHorizontalSlider("tubeLength", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 0.800000012f, 0.00999999978f, 3.0f, 0.00999999978f);
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.addHorizontalSlider("reedStiffness", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.addHorizontalSlider("bellOpening", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider0", "3", "");
		ui_interface.addHorizontalSlider("outGain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = fHslider1;
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = (0.0299999993f * fHslider2);
		float fSlow4 = (fConst1 * fHslider3);
		float fSlow5 = (float)java.lang.Math.sin(fSlow4);
		float fSlow6 = (float)java.lang.Math.cos(fSlow4);
		float fSlow7 = (0.0f - fSlow5);
		float fSlow8 = (0.00100000005f * fHslider4);
		float fSlow9 = (float)java.lang.Math.tan((fConst2 * fHslider6));
		float fSlow10 = (1.0f / fSlow9);
		float fSlow11 = (((fSlow10 + 1.41421354f) / fSlow9) + 1.0f);
		float fSlow12 = (0.0500000007f * (fHslider5 / fSlow11));
		float fSlow13 = (1.0f / fSlow11);
		float fSlow14 = (((fSlow10 + -1.41421354f) / fSlow9) + 1.0f);
		float fSlow15 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow9))));
		float fSlow16 = ((0.25999999f * fHslider7) + -0.439999998f);
		float fSlow17 = (0.00100000005f * fHslider8);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = 0;
			iVec0[0] = 1;
			fRec13[0] = ((fSlow1 * fRec13[1]) + (fSlow2 * fRec11[1]));
			float fRec10 = (fRec13[0] + (float)iRec6[1]);
			fRec17[0] = ((fSlow5 * fRec18[1]) + (fSlow6 * fRec17[1]));
			fRec18[0] = (((fSlow6 * fRec18[1]) + (fSlow7 * fRec17[1])) + (float)(1 - iVec0[1]));
			float fTemp0 = (fSlow3 * fRec17[0]);
			fRec19[0] = (fSlow8 + (0.999000013f * fRec19[1]));
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			fRec20[0] = ((4.65661287e-10f * (float)iRec21[0]) - (fSlow13 * ((fSlow14 * fRec20[2]) + (fSlow15 * fRec20[1]))));
			float fTemp1 = (fRec19[0] * ((fSlow12 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) + 1.0f));
			fRec14[0] = ((fRec0[1] + fTemp0) + fTemp1);
			float fTemp2 = (0.0f - fRec14[1]);
			fRec15[(IOTA & 2047)] = ((fTemp0 + fTemp1) + (fTemp2 * (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, ((fSlow16 * fTemp2) + 0.699999988f)))));
			int iRec16 = 0;
			fRec22[0] = (fSlow17 + (0.999000013f * fRec22[1]));
			float fTemp3 = (fConst4 * ((0.5f * fRec22[0]) + -0.0500000007f));
			float fTemp4 = (fTemp3 + -1.49999499f);
			int iTemp5 = (int)fTemp4;
			int iTemp6 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, iTemp5)) + 1);
			float fTemp7 = (float)java.lang.Math.floor(fTemp4);
			float fTemp8 = (fTemp3 + (-1.0f - fTemp7));
			float fTemp9 = (0.0f - fTemp8);
			float fTemp10 = (fTemp3 + (-2.0f - fTemp7));
			float fTemp11 = (0.0f - (0.5f * fTemp10));
			float fTemp12 = (fTemp3 + (-3.0f - fTemp7));
			float fTemp13 = (0.0f - (0.333333343f * fTemp12));
			float fTemp14 = (fTemp3 + (-4.0f - fTemp7));
			float fTemp15 = (0.0f - (0.25f * fTemp14));
			float fTemp16 = (fTemp3 - fTemp7);
			int iTemp17 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 2))) + 1);
			float fTemp18 = (0.0f - fTemp12);
			float fTemp19 = (0.0f - (0.5f * fTemp14));
			int iTemp20 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 1))) + 1);
			float fTemp21 = (0.0f - fTemp10);
			float fTemp22 = (0.0f - (0.5f * fTemp12));
			float fTemp23 = (0.0f - (0.333333343f * fTemp14));
			float fTemp24 = (fTemp8 * fTemp10);
			int iTemp25 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 3))) + 1);
			float fTemp26 = (0.0f - fTemp14);
			float fTemp27 = (fTemp24 * fTemp12);
			int iTemp28 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 4))) + 1);
			fVec1[0] = (((((fRec15[((IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5f * (((fTemp8 * fRec15[((IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((fRec15[((IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166666672f * ((fTemp24 * fRec15[((IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416666679f * (fTemp27 * fRec15[((IOTA - iTemp28) & 2047)])))));
			fRec11[0] = fVec1[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = fRec11[0];
			float fRec9 = (fRec11[0] + (float)iRec12);
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * fRec2[((IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166666672f * ((fTemp24 * fTemp26) * fRec2[((IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * fRec2[((IOTA - iTemp20) & 2047)]) + (0.5f * (((fTemp8 * fTemp18) * fTemp19) * fRec2[((IOTA - iTemp17) & 2047)])))) + (0.0416666679f * (fTemp27 * fRec2[((IOTA - iTemp28) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp29 = (fSlow0 * fRec1);
			output0[i] = fTemp29;
			output1[i] = fTemp29;
			iRec6[1] = iRec6[0];
			iVec0[1] = iVec0[0];
			fRec13[1] = fRec13[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			iRec21[1] = iRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec14[1] = fRec14[0];
			IOTA = (IOTA + 1);
			fRec22[1] = fRec22[0];
			fVec1[1] = fVec1[0];
			fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

