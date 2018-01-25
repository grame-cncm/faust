/* ------------------------------------------------------------
name: "crazyGuiro"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	float fRec9[] = new float[2];
	float fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fVec0[] = new float[2];
	float fConst1;
	float fHslider2;
	float fHslider3;
	int iRec11[] = new int[2];
	float fButton0;
	float fVec1[] = new float[2];
	float fConst2;
	float fRec12[] = new float[2];
	float fConst3;
	float fConst4;
	float fRec10[] = new float[3];
	int IOTA;
	float fVec2[] = new float[8192];
	int iConst5;
	float fRec8[] = new float[2];
	float fRec14[] = new float[2];
	float fVec3[] = new float[8192];
	int iConst6;
	float fRec13[] = new float[2];
	float fRec16[] = new float[2];
	float fVec4[] = new float[8192];
	int iConst7;
	float fRec15[] = new float[2];
	float fRec18[] = new float[2];
	float fVec5[] = new float[8192];
	int iConst8;
	float fRec17[] = new float[2];
	float fRec20[] = new float[2];
	float fVec6[] = new float[8192];
	int iConst9;
	float fRec19[] = new float[2];
	float fRec22[] = new float[2];
	float fVec7[] = new float[8192];
	int iConst10;
	float fRec21[] = new float[2];
	float fRec24[] = new float[2];
	float fVec8[] = new float[8192];
	int iConst11;
	float fRec23[] = new float[2];
	float fRec26[] = new float[2];
	float fVec9[] = new float[8192];
	int iConst12;
	float fRec25[] = new float[2];
	float fVec10[] = new float[2048];
	int iConst13;
	float fRec6[] = new float[2];
	float fVec11[] = new float[2048];
	int iConst14;
	float fRec4[] = new float[2];
	float fVec12[] = new float[2048];
	int iConst15;
	float fRec2[] = new float[2];
	float fVec13[] = new float[1024];
	int iConst16;
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'8',  'Keyboard 0 - Number of Keys':'16',  'Keyboard 1 - Number of Keys':'16',  'Keyboard 2 - Number of Keys':'16',  'Keyboard 3 - Number of Keys':'16',  'Keyboard 4 - Number of Keys':'16',  'Keyboard 5 - Number of Keys':'16',  'Keyboard 6 - Number of Keys':'16',  'Keyboard 7 - Number of Keys':'16',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 2 - Piano Keyboard':'0',  'Keyboard 3 - Piano Keyboard':'0',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 5 - Piano Keyboard':'0',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 7 - Piano Keyboard':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "crazyGuiro");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
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
		fConst1 = (1382.30078f / fConst0);
		fConst2 = (0.00200000009f * fConst0);
		fConst3 = (0.00100000005f * fConst0);
		fConst4 = (1000.0f / fConst0);
		iConst5 = (int)(0.0253061224f * fConst0);
		iConst6 = (int)(0.0269387756f * fConst0);
		iConst7 = (int)(0.0289569162f * fConst0);
		iConst8 = (int)(0.0307482984f * fConst0);
		iConst9 = (int)(0.0322448984f * fConst0);
		iConst10 = (int)(0.033809524f * fConst0);
		iConst11 = (int)(0.0353061222f * fConst0);
		iConst12 = (int)(0.0366666652f * fConst0);
		iConst13 = java.lang.Math.min(1024, java.lang.Math.max(0, ((int)(0.0126077095f * fConst0) + -1)));
		iConst14 = java.lang.Math.min(1024, java.lang.Math.max(0, ((int)(0.00999999978f * fConst0) + -1)));
		iConst15 = java.lang.Math.min(1024, java.lang.Math.max(0, ((int)(0.00773242628f * fConst0) + -1)));
		iConst16 = java.lang.Math.min(1024, java.lang.Math.max(0, ((int)(0.00510204071f * fConst0) + -1)));
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fButton0 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec9[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec11[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec12[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec10[l5] = 0.0f;
			
		}
		IOTA = 0;
		for (int l6 = 0; (l6 < 8192); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec8[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec14[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 8192); l9 = (l9 + 1)) {
			fVec3[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec13[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec16[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 8192); l12 = (l12 + 1)) {
			fVec4[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec15[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec18[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 8192); l15 = (l15 + 1)) {
			fVec5[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec17[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec20[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 8192); l18 = (l18 + 1)) {
			fVec6[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec19[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec22[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 8192); l21 = (l21 + 1)) {
			fVec7[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec21[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec24[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 8192); l24 = (l24 + 1)) {
			fVec8[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec23[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec26[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 8192); l27 = (l27 + 1)) {
			fVec9[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec25[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			fVec10[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec6[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2048); l31 = (l31 + 1)) {
			fVec11[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec4[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			fVec12[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec2[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 1024); l35 = (l35 + 1)) {
			fVec13[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec0[l36] = 0.0f;
			
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
		ui_interface.openVerticalBox("crazyGuiro");
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.addHorizontalSlider("key", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface.addHorizontalSlider("keyboard", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface.declare("fHslider0", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("res", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("wet", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = fHslider1;
		float fSlow2 = (float)java.lang.Math.tan((fConst1 * (float)java.lang.Math.pow(2.0f, (0.0833333358f * ((fHslider2 + (8.0f * fHslider3)) + -19.0f)))));
		float fSlow3 = (1.0f / fSlow2);
		float fSlow4 = (((fSlow3 + 0.125f) / fSlow2) + 1.0f);
		float fSlow5 = (fSlow1 / fSlow4);
		float fSlow6 = fButton0;
		float fSlow7 = (1.0f / fSlow4);
		float fSlow8 = (((fSlow3 + -0.125f) / fSlow2) + 1.0f);
		float fSlow9 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow2))));
		float fSlow10 = (0.0f - fSlow3);
		float fSlow11 = ((1.0f - fSlow1) / fSlow4);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec9[0] = (0.5f * (fRec9[1] + fRec8[1]));
			fVec0[0] = fConst0;
			iRec11[0] = ((1103515245 * iRec11[1]) + 12345);
			fVec1[0] = fSlow6;
			fRec12[0] = (((((fSlow6 - fVec1[1]) > 0.0f) > 0))?0.0f:(float)java.lang.Math.min(fConst2, ((fRec12[1] + (0.00200000009f * (fConst0 - fVec0[1]))) + 1.0f)));
			int iTemp0 = (fRec12[0] < fConst3);
			fRec10[0] = ((4.65661287e-10f * ((float)iRec11[0] * (((iTemp0==0)?true:false)?(((fRec12[0] < 0.0f))?0.0f:(((iTemp0==0)?true:false)?(fConst4 * fRec12[0]):1.0f)):(((fRec12[0] < fConst2))?((fConst4 * (0.0f - (fRec12[0] - fConst3))) + 1.0f):0.0f)))) - (fSlow7 * ((fSlow8 * fRec10[2]) + (fSlow9 * fRec10[1]))));
			float fTemp1 = ((fSlow3 * fRec10[0]) + (fSlow10 * fRec10[2]));
			float fTemp2 = (fSlow5 * fTemp1);
			fVec2[(IOTA & 8191)] = ((fSlow0 * fRec9[0]) + fTemp2);
			fRec8[0] = fVec2[((IOTA - iConst5) & 8191)];
			fRec14[0] = (0.5f * (fRec14[1] + fRec13[1]));
			fVec3[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec14[0]));
			fRec13[0] = fVec3[((IOTA - iConst6) & 8191)];
			fRec16[0] = (0.5f * (fRec16[1] + fRec15[1]));
			fVec4[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec16[0]));
			fRec15[0] = fVec4[((IOTA - iConst7) & 8191)];
			fRec18[0] = (0.5f * (fRec18[1] + fRec17[1]));
			fVec5[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec18[0]));
			fRec17[0] = fVec5[((IOTA - iConst8) & 8191)];
			fRec20[0] = (0.5f * (fRec20[1] + fRec19[1]));
			fVec6[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec20[0]));
			fRec19[0] = fVec6[((IOTA - iConst9) & 8191)];
			fRec22[0] = (0.5f * (fRec22[1] + fRec21[1]));
			fVec7[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec22[0]));
			fRec21[0] = fVec7[((IOTA - iConst10) & 8191)];
			fRec24[0] = (0.5f * (fRec24[1] + fRec23[1]));
			fVec8[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec24[0]));
			fRec23[0] = fVec8[((IOTA - iConst11) & 8191)];
			fRec26[0] = (0.5f * (fRec26[1] + fRec25[1]));
			fVec9[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec26[0]));
			fRec25[0] = fVec9[((IOTA - iConst12) & 8191)];
			float fTemp3 = ((((((((fRec8[0] + fRec13[0]) + fRec15[0]) + fRec17[0]) + fRec19[0]) + fRec21[0]) + fRec23[0]) + fRec25[0]) + (0.5f * fRec6[1]));
			fVec10[(IOTA & 2047)] = fTemp3;
			fRec6[0] = fVec10[((IOTA - iConst13) & 2047)];
			float fRec7 = (0.0f - (0.5f * fTemp3));
			float fTemp4 = (fRec6[1] + (fRec7 + (0.5f * fRec4[1])));
			fVec11[(IOTA & 2047)] = fTemp4;
			fRec4[0] = fVec11[((IOTA - iConst14) & 2047)];
			float fRec5 = (0.0f - (0.5f * fTemp4));
			float fTemp5 = (fRec4[1] + (fRec5 + (0.5f * fRec2[1])));
			fVec12[(IOTA & 2047)] = fTemp5;
			fRec2[0] = fVec12[((IOTA - iConst15) & 2047)];
			float fRec3 = (0.0f - (0.5f * fTemp5));
			float fTemp6 = (fRec2[1] + (fRec3 + (0.5f * fRec0[1])));
			fVec13[(IOTA & 1023)] = fTemp6;
			fRec0[0] = fVec13[((IOTA - iConst16) & 1023)];
			float fRec1 = (0.0f - (0.5f * fTemp6));
			float fTemp7 = (fRec0[1] + (fRec1 + (fSlow11 * fTemp1)));
			output0[i] = fTemp7;
			output1[i] = fTemp7;
			fRec9[1] = fRec9[0];
			fVec0[1] = fVec0[0];
			iRec11[1] = iRec11[0];
			fVec1[1] = fVec1[0];
			fRec12[1] = fRec12[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

