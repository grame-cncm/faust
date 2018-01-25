/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Brass"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	int iRec6[] = new int[2];
	float fHslider0;
	int iVec0[] = new int[2];
	float fRec14[] = new float[2];
	float fRec13[] = new float[2];
	float fRec15[] = new float[2];
	float fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider2;
	float fRec20[] = new float[2];
	float fRec21[] = new float[2];
	float fHslider3;
	float fRec22[] = new float[2];
	float fHslider4;
	float fConst2;
	float fHslider5;
	int iRec24[] = new int[2];
	float fRec23[] = new float[3];
	float fConst3;
	float fHslider6;
	float fRec25[] = new float[2];
	float fHslider7;
	float fRec26[] = new float[2];
	float fRec19[] = new float[3];
	float fVec1[] = new float[2];
	float fRec18[] = new float[2];
	int IOTA;
	float fRec16[] = new float[2048];
	float fConst4;
	float fConst5;
	float fVec2[] = new float[2];
	float fRec11[] = new float[2];
	float fRec2[] = new float[2048];
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple brass instrument physical model with physical parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Brass");
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
		fConst3 = (2136.28296f / fConst0);
		fConst4 = (0.00882352982f * fConst0);
		fConst5 = (0.00147058826f * fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.25f;
		fHslider2 = (float)5.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.10000000000000001f;
		fHslider5 = (float)2000.0f;
		fHslider6 = (float)0.5f;
		fHslider7 = (float)0.5f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec6[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec14[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec13[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec15[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec20[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec21[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec22[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec24[l8] = 0;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec23[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec25[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec26[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec19[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec1[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec18[l14] = 0.0f;
			
		}
		IOTA = 0;
		for (int l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			fRec16[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec2[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2048); l18 = (l18 + 1)) {
			fRec2[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec0[l19] = 0.0f;
			
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
		ui_interface.openHorizontalBox("brass");
		ui_interface.openVerticalBox("blower");
		ui_interface.declare("fHslider3", "0", "");
		ui_interface.addHorizontalSlider("pressure", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.addHorizontalSlider("breathGain", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.addHorizontalSlider("breathCutoff", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 2000.0f, 20.0f, 20000.0f, 0.100000001f);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.addHorizontalSlider("vibratoFreq", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 5.0f, 0.100000001f, 10.0f, 0.100000001f);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.addHorizontalSlider("vibratoGain", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.25f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("brassModel");
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.addHorizontalSlider("tubeLength", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 0.5f, 0.00999999978f, 2.5f, 0.00999999978f);
		ui_interface.declare("fHslider6", "2", "");
		ui_interface.addHorizontalSlider("lipsTension", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider0", "3", "");
		ui_interface.addHorizontalSlider("mute", new FaustVarAccess() {
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
		float fSlow0 = (0.00100000005f * fHslider0);
		float fSlow1 = (0.0299999993f * fHslider1);
		float fSlow2 = (fConst1 * fHslider2);
		float fSlow3 = (float)java.lang.Math.sin(fSlow2);
		float fSlow4 = (float)java.lang.Math.cos(fSlow2);
		float fSlow5 = (0.0f - fSlow3);
		float fSlow6 = (0.00100000005f * fHslider3);
		float fSlow7 = (float)java.lang.Math.tan((fConst2 * fHslider5));
		float fSlow8 = (1.0f / fSlow7);
		float fSlow9 = (((fSlow8 + 1.41421354f) / fSlow7) + 1.0f);
		float fSlow10 = (0.0500000007f * (fHslider4 / fSlow9));
		float fSlow11 = (1.0f / fSlow9);
		float fSlow12 = (((fSlow8 + -1.41421354f) / fSlow7) + 1.0f);
		float fSlow13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow7))));
		float fSlow14 = (0.00100000005f * fHslider6);
		float fSlow15 = (0.00100000005f * fHslider7);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = 0;
			iVec0[0] = 1;
			fRec14[0] = (fSlow0 + (0.999000013f * fRec14[1]));
			fRec13[0] = ((fRec14[0] * fRec13[1]) + ((1.0f - fRec14[0]) * fRec11[1]));
			float fRec10 = (fRec13[0] + (float)iRec6[1]);
			fRec15[0] = fRec0[1];
			fRec20[0] = ((fSlow3 * fRec21[1]) + (fSlow4 * fRec20[1]));
			fRec21[0] = (((fSlow4 * fRec21[1]) + (fSlow5 * fRec20[1])) + (float)(1 - iVec0[1]));
			fRec22[0] = (fSlow6 + (0.999000013f * fRec22[1]));
			iRec24[0] = ((1103515245 * iRec24[1]) + 12345);
			fRec23[0] = ((4.65661287e-10f * (float)iRec24[0]) - (fSlow11 * ((fSlow12 * fRec23[2]) + (fSlow13 * fRec23[1]))));
			float fTemp0 = ((fSlow1 * fRec20[0]) + (fRec22[0] * ((fSlow10 * (fRec23[2] + (fRec23[0] + (2.0f * fRec23[1])))) + 1.0f)));
			fRec25[0] = (fSlow14 + (0.999000013f * fRec25[1]));
			fRec26[0] = (fSlow15 + (0.999000013f * fRec26[1]));
			fRec19[0] = ((0.0299999993f * ((0.300000012f * fTemp0) - (0.850000024f * fRec15[1]))) - ((fRec19[1] * (0.0f - (1.99399996f * (float)java.lang.Math.cos((fConst3 * ((float)java.lang.Math.pow(4.0f, ((2.0f * fRec25[0]) + -1.0f)) / fRec26[0])))))) + (0.994009018f * fRec19[2])));
			float fTemp1 = (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, mydsp_faustpower2_f(fRec19[0])));
			float fTemp2 = (0.850000024f * (fRec15[1] * (1.0f - fTemp1)));
			float fTemp3 = (0.300000012f * (fTemp0 * fTemp1));
			fVec1[0] = (fTemp3 + fTemp2);
			fRec18[0] = ((fTemp2 + ((0.995000005f * fRec18[1]) + fTemp3)) - fVec1[1]);
			fRec16[(IOTA & 2047)] = fRec18[0];
			int iRec17 = 0;
			float fTemp4 = (fConst5 * fRec26[0]);
			float fTemp5 = (fTemp4 + -1.49999499f);
			int iTemp6 = (int)fTemp5;
			int iTemp7 = ((int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp6)) + 1);
			float fTemp8 = (float)java.lang.Math.floor(fTemp5);
			float fTemp9 = (fTemp4 + (-1.0f - fTemp8));
			float fTemp10 = (0.0f - fTemp9);
			float fTemp11 = (fTemp4 + (-2.0f - fTemp8));
			float fTemp12 = (0.0f - (0.5f * fTemp11));
			float fTemp13 = (fTemp4 + (-3.0f - fTemp8));
			float fTemp14 = (0.0f - (0.333333343f * fTemp13));
			float fTemp15 = (fTemp4 + (-4.0f - fTemp8));
			float fTemp16 = (0.0f - (0.25f * fTemp15));
			float fTemp17 = (fTemp4 - fTemp8);
			int iTemp18 = ((int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp6 + 2))) + 1);
			float fTemp19 = (0.0f - fTemp13);
			float fTemp20 = (0.0f - (0.5f * fTemp15));
			int iTemp21 = ((int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp6 + 1))) + 1);
			float fTemp22 = (0.0f - fTemp11);
			float fTemp23 = (0.0f - (0.5f * fTemp13));
			float fTemp24 = (0.0f - (0.333333343f * fTemp15));
			float fTemp25 = (fTemp9 * fTemp11);
			int iTemp26 = ((int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp6 + 3))) + 1);
			float fTemp27 = (0.0f - fTemp15);
			float fTemp28 = (fTemp25 * fTemp13);
			int iTemp29 = ((int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp6 + 4))) + 1);
			fVec2[0] = (((((fRec16[((IOTA - iTemp7) & 2047)] * fTemp10) * fTemp12) * fTemp14) * fTemp16) + (fTemp17 * ((((0.5f * (((fTemp9 * fRec16[((IOTA - iTemp18) & 2047)]) * fTemp19) * fTemp20)) + (((fRec16[((IOTA - iTemp21) & 2047)] * fTemp22) * fTemp23) * fTemp24)) + (0.166666672f * ((fTemp25 * fRec16[((IOTA - iTemp26) & 2047)]) * fTemp27))) + (0.0416666679f * (fTemp28 * fRec16[((IOTA - iTemp29) & 2047)])))));
			fRec11[0] = fVec2[1];
			int iRec12 = iRec17;
			float fRec7 = fRec10;
			float fRec8 = fRec11[0];
			float fRec9 = (fRec11[0] + (float)iRec12);
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp10 * fTemp12) * fTemp14) * fTemp16) * fRec2[((IOTA - iTemp7) & 2047)]) + (fTemp17 * (((0.166666672f * ((fTemp25 * fTemp27) * fRec2[((IOTA - iTemp26) & 2047)])) + ((((fTemp22 * fTemp23) * fTemp24) * fRec2[((IOTA - iTemp21) & 2047)]) + (0.5f * (((fTemp9 * fTemp19) * fTemp20) * fRec2[((IOTA - iTemp18) & 2047)])))) + (0.0416666679f * (fTemp28 * fRec2[((IOTA - iTemp29) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i] = fRec1;
			output1[i] = fRec1;
			iRec6[1] = iRec6[0];
			iVec0[1] = iVec0[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			iRec24[1] = iRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fVec1[1] = fVec1[0];
			fRec18[1] = fRec18[0];
			IOTA = (IOTA + 1);
			fVec2[1] = fVec2[0];
			fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

