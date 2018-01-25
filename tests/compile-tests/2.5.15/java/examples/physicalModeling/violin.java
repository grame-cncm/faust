/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Violin"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower4_f(float value) {
		return (((value * value) * value) * value);
		
	}
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	int iRec10[] = new int[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fHslider1;
	float fRec26[] = new float[2];
	float fHslider2;
	float fRec27[] = new float[2];
	float fRec22[] = new float[2];
	float fHslider3;
	float fRec28[] = new float[2];
	float fRec29[] = new float[4];
	int IOTA;
	float fRec30[] = new float[2048];
	float fVec0[] = new float[2];
	float fHslider4;
	float fRec32[] = new float[2];
	float fVec1[] = new float[2048];
	float fRec18[] = new float[2048];
	float fRec20[] = new float[2];
	float fRec16[] = new float[4];
	float fConst6;
	float fConst7;
	float fRec14[] = new float[3];
	float fConst8;
	int iRec6[] = new int[2];
	float fRec2[] = new float[2048];
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple violin physical model controlled with continuous parameters.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Violin");
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
		fConst1 = (float)java.lang.Math.tan((1570.79639f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 0.5f) / fConst1) + 1.0f));
		fConst4 = (0.00882352982f * fConst0);
		fConst5 = (0.00147058826f * fConst0);
		fConst6 = (((fConst2 + -0.5f) / fConst1) + 1.0f);
		fConst7 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst1))));
		fConst8 = (0.0f - fConst2);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.69999999999999996f;
		fHslider2 = (float)0.75f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.5f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec10[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec26[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec27[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec22[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec28[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			fRec29[l5] = 0.0f;
			
		}
		IOTA = 0;
		for (int l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			fRec30[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec0[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec32[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			fVec1[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			fRec18[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec20[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			fRec16[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec14[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			iRec6[l14] = 0;
			
		}
		for (int l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			fRec2[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec0[l16] = 0.0f;
			
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
		ui_interface.openVerticalBox("violin");
		ui_interface.declare("0", "0", "");
		ui_interface.openVerticalBox("string");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.addHorizontalSlider("length", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.75f, 0.0f, 2.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("bow");
		ui_interface.declare("fHslider3", "0", "");
		ui_interface.addHorizontalSlider("velocity", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.addHorizontalSlider("pressure", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.addHorizontalSlider("position", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.699999988f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.addHorizontalSlider("outGain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (0.00100000005f * fHslider1);
		float fSlow2 = (0.00100000005f * fHslider2);
		float fSlow3 = (0.00100000005f * fHslider3);
		float fSlow4 = (0.00100000005f * fHslider4);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec10[0] = 0;
			int iRec11 = iRec10[1];
			float fRec15 = ((float)iRec6[1] - (0.989264667f * ((0.600000024f * fRec16[2]) + (0.200000003f * (fRec16[1] + fRec16[3])))));
			fRec26[0] = (fSlow1 + (0.999000013f * fRec26[1]));
			fRec27[0] = (fSlow2 + (0.999000013f * fRec27[1]));
			float fTemp0 = (fRec27[0] + -0.0799999982f);
			float fTemp1 = (fConst5 * ((1.0f - fRec26[0]) * fTemp0));
			float fTemp2 = (fTemp1 + -1.49999499f);
			int iTemp3 = (int)fTemp2;
			int iTemp4 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp3));
			float fTemp5 = (float)java.lang.Math.floor(fTemp2);
			float fTemp6 = (fTemp1 + (-1.0f - fTemp5));
			float fTemp7 = (0.0f - fTemp6);
			float fTemp8 = (fTemp1 + (-2.0f - fTemp5));
			float fTemp9 = (0.0f - (0.5f * fTemp8));
			float fTemp10 = (fTemp1 + (-3.0f - fTemp5));
			float fTemp11 = (0.0f - (0.333333343f * fTemp10));
			float fTemp12 = (fTemp1 + (-4.0f - fTemp5));
			float fTemp13 = (0.0f - (0.25f * fTemp12));
			float fTemp14 = (fTemp1 - fTemp5);
			int iTemp15 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp3 + 2)));
			float fTemp16 = (0.0f - fTemp10);
			float fTemp17 = (0.0f - (0.5f * fTemp12));
			int iTemp18 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp3 + 1)));
			float fTemp19 = (0.0f - fTemp8);
			float fTemp20 = (0.0f - (0.5f * fTemp10));
			float fTemp21 = (0.0f - (0.333333343f * fTemp12));
			float fTemp22 = (fTemp6 * fTemp8);
			int iTemp23 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp3 + 3)));
			float fTemp24 = (0.0f - fTemp12);
			float fTemp25 = (fTemp22 * fTemp10);
			int iTemp26 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp3 + 4)));
			fRec22[0] = (((((fRec2[((IOTA - (iTemp4 + 1)) & 2047)] * fTemp7) * fTemp9) * fTemp11) * fTemp13) + (fTemp14 * ((((0.5f * (((fTemp6 * fRec2[((IOTA - (iTemp15 + 1)) & 2047)]) * fTemp16) * fTemp17)) + (((fRec2[((IOTA - (iTemp18 + 1)) & 2047)] * fTemp19) * fTemp20) * fTemp21)) + (0.166666672f * ((fTemp22 * fRec2[((IOTA - (iTemp23 + 1)) & 2047)]) * fTemp24))) + (0.0416666679f * (fTemp25 * fRec2[((IOTA - (iTemp26 + 1)) & 2047)])))));
			fRec28[0] = (fSlow3 + (0.999000013f * fRec28[1]));
			fRec29[0] = fRec0[1];
			fRec30[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec29[2]) + (0.100000001f * (fRec29[1] + fRec29[3])))));
			int iRec31 = 0;
			float fTemp27 = (fConst5 * (fRec26[0] * fTemp0));
			float fTemp28 = (fTemp27 + -1.49999499f);
			int iTemp29 = (int)fTemp28;
			int iTemp30 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp29));
			float fTemp31 = (float)java.lang.Math.floor(fTemp28);
			float fTemp32 = (fTemp27 + (-1.0f - fTemp31));
			float fTemp33 = (0.0f - fTemp32);
			float fTemp34 = (fTemp27 + (-2.0f - fTemp31));
			float fTemp35 = (0.0f - (0.5f * fTemp34));
			float fTemp36 = (fTemp27 + (-3.0f - fTemp31));
			float fTemp37 = (0.0f - (0.333333343f * fTemp36));
			float fTemp38 = (fTemp27 + (-4.0f - fTemp31));
			float fTemp39 = (0.0f - (0.25f * fTemp38));
			float fTemp40 = (fTemp27 - fTemp31);
			int iTemp41 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp29 + 2)));
			float fTemp42 = (0.0f - fTemp36);
			float fTemp43 = (0.0f - (0.5f * fTemp38));
			int iTemp44 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp29 + 1)));
			float fTemp45 = (0.0f - fTemp34);
			float fTemp46 = (0.0f - (0.5f * fTemp36));
			float fTemp47 = (0.0f - (0.333333343f * fTemp38));
			float fTemp48 = (fTemp32 * fTemp34);
			int iTemp49 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp29 + 3)));
			float fTemp50 = (0.0f - fTemp38);
			float fTemp51 = (fTemp48 * fTemp36);
			int iTemp52 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp29 + 4)));
			fVec0[0] = (((((fRec30[((IOTA - (iTemp30 + 2)) & 2047)] * fTemp33) * fTemp35) * fTemp37) * fTemp39) + (fTemp40 * ((((0.5f * (((fTemp32 * fRec30[((IOTA - (iTemp41 + 2)) & 2047)]) * fTemp42) * fTemp43)) + (((fRec30[((IOTA - (iTemp44 + 2)) & 2047)] * fTemp45) * fTemp46) * fTemp47)) + (0.166666672f * ((fTemp48 * fRec30[((IOTA - (iTemp49 + 2)) & 2047)]) * fTemp50))) + (0.0416666679f * (fTemp51 * fRec30[((IOTA - (iTemp52 + 2)) & 2047)])))));
			float fTemp53 = (fRec28[0] - (fRec22[1] + fVec0[1]));
			fRec32[0] = (fSlow4 + (0.999000013f * fRec32[1]));
			float fTemp54 = (fTemp53 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs(((5.0f - (4.0f * fRec32[0])) * fTemp53)) + 0.75f)))));
			float fRec23 = (fRec22[1] + fTemp54);
			float fTemp55 = (fVec0[1] + fTemp54);
			fVec1[(IOTA & 2047)] = fTemp55;
			float fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * fVec1[((IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416666679f * (fTemp25 * fVec1[((IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * fVec1[((IOTA - iTemp18) & 2047)]) + (0.5f * (((fTemp6 * fTemp16) * fTemp17) * fVec1[((IOTA - iTemp15) & 2047)]))) + (0.166666672f * ((fTemp22 * fTemp24) * fVec1[((IOTA - iTemp23) & 2047)]))))));
			int iRec25 = iRec31;
			fRec18[(IOTA & 2047)] = fRec23;
			float fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * fRec18[((IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166666672f * ((fTemp48 * fTemp50) * fRec18[((IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * fRec18[((IOTA - (iTemp44 + 1)) & 2047)]) + (0.5f * (((fTemp32 * fTemp42) * fTemp43) * fRec18[((IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416666679f * (fTemp51 * fRec18[((IOTA - (iTemp52 + 1)) & 2047)])))));
			fRec20[0] = fRec24;
			int iRec21 = iRec25;
			fRec16[0] = fRec20[1];
			int iRec17 = iRec21;
			fRec14[0] = (fRec16[1] - (fConst3 * ((fConst6 * fRec14[2]) + (fConst7 * fRec14[1]))));
			float fTemp56 = (fConst3 * ((fConst2 * fRec14[0]) + (fConst8 * fRec14[2])));
			float fRec12 = fTemp56;
			float fRec13 = ((float)iRec17 + fTemp56);
			iRec6[0] = iRec11;
			float fRec7 = fRec15;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = fRec19;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp57 = (fSlow0 * fRec1);
			output0[i] = fTemp57;
			output1[i] = fTemp57;
			iRec10[1] = iRec10[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec22[1] = fRec22[0];
			fRec28[1] = fRec28[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec29[j0] = fRec29[(j0 - 1)];
				
			}
			IOTA = (IOTA + 1);
			fVec0[1] = fVec0[0];
			fRec32[1] = fRec32[0];
			fRec20[1] = fRec20[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec16[j1] = fRec16[(j1 - 1)];
				
			}
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

