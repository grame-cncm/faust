/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "NylonGuitarMidi"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	int iRec10[] = new int[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fHslider1;
	float fRec29[] = new float[2];
	float fHslider2;
	float fHslider3;
	float fButton0;
	float fHslider4;
	float fVec0[] = new float[2];
	float fRec30[] = new float[2];
	float fRec25[] = new float[2];
	float fRec31[] = new float[2];
	float fRec33[] = new float[4];
	int IOTA;
	float fRec34[] = new float[2048];
	float fVec1[] = new float[2];
	float fHslider5;
	int iRec37[] = new int[2];
	float fConst3;
	float fRec36[] = new float[3];
	float fConst4;
	float fVec2[] = new float[2];
	float fRec38[] = new float[2];
	float fConst5;
	float fConst6;
	float fVec3[] = new float[2];
	float fRec32[] = new float[2048];
	float fRec21[] = new float[2];
	float fRec17[] = new float[2048];
	float fRec19[] = new float[2];
	float fRec15[] = new float[4];
	int iRec6[] = new int[2];
	float fRec2[] = new float[2048];
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple acoustic guitar model with nylon strings.");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "NylonGuitarMidi");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		fConst3 = (15.707963f / fConst0);
		fConst4 = (0.00400000019f * fConst0);
		fConst5 = (0.00200000009f * fConst0);
		fConst6 = (500.0f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.80000000000000004f;
		fHslider2 = (float)440.0f;
		fHslider3 = (float)1.0f;
		fButton0 = (float)0.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)0.80000000000000004f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec10[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec29[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec30[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec25[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec31[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			fRec33[l6] = 0.0f;
			
		}
		IOTA = 0;
		for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			fRec34[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iRec37[l9] = 0;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec36[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec2[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec38[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec3[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fRec32[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec21[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			fRec17[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec19[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 4); l18 = (l18 + 1)) {
			fRec15[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			iRec6[l19] = 0;
			
		}
		for (int l20 = 0; (l20 < 2048); l20 = (l20 + 1)) {
			fRec2[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec0[l21] = 0.0f;
			
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
		ui_interface.openVerticalBox("nylonGuitar");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "pitchwheel");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("bend", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "3", "");
		ui_interface.declare("fHslider4", "hidden", "1");
		ui_interface.declare("fHslider4", "midi", "ctrl 64");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "4", "");
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.addHorizontalSlider("outGain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "midi", "ctrl 1");
		ui_interface.addHorizontalSlider("pluckPosition", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (0.00100000005f * fHslider1);
		float fSlow2 = fHslider2;
		float fSlow3 = (340.0f / fSlow2);
		float fSlow4 = fHslider3;
		float fSlow5 = (float)java.lang.Math.min(1.0f, (fButton0 + fHslider4));
		int iSlow6 = (fSlow5 == 0.0f);
		float fSlow7 = fHslider5;
		float fSlow8 = (fConst3 * fSlow2);
		float fSlow9 = (0.00033333333f * fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec10[0] = 0;
			int iRec11 = iRec10[1];
			float fRec14 = ((float)iRec6[1] - (0.997843683f * ((0.699999988f * fRec15[2]) + (0.150000006f * (fRec15[1] + fRec15[3])))));
			fRec29[0] = (fSlow1 + (0.999000013f * fRec29[1]));
			fVec0[0] = fSlow5;
			int iTemp0 = ((((fSlow5 == fVec0[1]))?1:0) | iSlow6);
			fRec30[0] = ((fSlow4 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * fRec30[1])));
			float fTemp1 = ((fSlow3 / fRec30[0]) + -0.109999999f);
			float fTemp2 = (fConst2 * ((1.0f - fRec29[0]) * fTemp1));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = (int)fTemp3;
			int iTemp5 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, iTemp4));
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
			int iTemp16 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 2)));
			float fTemp17 = (0.0f - fTemp11);
			float fTemp18 = (0.0f - (0.5f * fTemp13));
			int iTemp19 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 1)));
			float fTemp20 = (0.0f - fTemp9);
			float fTemp21 = (0.0f - (0.5f * fTemp11));
			float fTemp22 = (0.0f - (0.333333343f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 3)));
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp4 + 4)));
			fRec25[0] = (((((fRec2[((IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5f * (((fTemp7 * fRec2[((IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((fRec2[((IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166666672f * ((fTemp23 * fRec2[((IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * fRec2[((IOTA - (iTemp27 + 1)) & 2047)])))));
			fRec31[0] = ((0.400000006f * fRec31[1]) + (0.600000024f * fRec25[1]));
			float fRec26 = fRec31[0];
			fRec33[0] = fRec0[1];
			fRec34[(IOTA & 2047)] = (0.0f - (0.997843683f * ((0.699999988f * fRec33[2]) + (0.150000006f * (fRec33[1] + fRec33[3])))));
			int iRec35 = 0;
			float fTemp28 = (fConst2 * (fRec29[0] * fTemp1));
			float fTemp29 = (fTemp28 + -1.49999499f);
			int iTemp30 = (int)fTemp29;
			int iTemp31 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, iTemp30));
			float fTemp32 = (float)java.lang.Math.floor(fTemp29);
			float fTemp33 = (fTemp28 + (-1.0f - fTemp32));
			float fTemp34 = (0.0f - fTemp33);
			float fTemp35 = (fTemp28 + (-2.0f - fTemp32));
			float fTemp36 = (0.0f - (0.5f * fTemp35));
			float fTemp37 = (fTemp28 + (-3.0f - fTemp32));
			float fTemp38 = (0.0f - (0.333333343f * fTemp37));
			float fTemp39 = (fTemp28 + (-4.0f - fTemp32));
			float fTemp40 = (0.0f - (0.25f * fTemp39));
			float fTemp41 = (fTemp28 - fTemp32);
			int iTemp42 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp30 + 2)));
			float fTemp43 = (0.0f - fTemp37);
			float fTemp44 = (0.0f - (0.5f * fTemp39));
			int iTemp45 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp30 + 1)));
			float fTemp46 = (0.0f - fTemp35);
			float fTemp47 = (0.0f - (0.5f * fTemp37));
			float fTemp48 = (0.0f - (0.333333343f * fTemp39));
			float fTemp49 = (fTemp33 * fTemp35);
			int iTemp50 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp30 + 3)));
			float fTemp51 = (0.0f - fTemp39);
			float fTemp52 = (fTemp49 * fTemp37);
			int iTemp53 = (int)(float)java.lang.Math.min(fConst1, (float)java.lang.Math.max(0, (iTemp30 + 4)));
			fVec1[0] = (((((fRec34[((IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5f * (((fTemp33 * fRec34[((IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((fRec34[((IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166666672f * ((fTemp49 * fRec34[((IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416666679f * (fTemp52 * fRec34[((IOTA - (iTemp53 + 2)) & 2047)])))));
			iRec37[0] = ((1103515245 * iRec37[1]) + 12345);
			float fTemp54 = (float)java.lang.Math.tan((fSlow8 * fRec30[0]));
			float fTemp55 = (1.0f / fTemp54);
			float fTemp56 = (((fTemp55 + 1.41421354f) / fTemp54) + 1.0f);
			fRec36[0] = ((4.65661287e-10f * (float)iRec37[0]) - (((fRec36[2] * (((fTemp55 + -1.41421354f) / fTemp54) + 1.0f)) + (2.0f * (fRec36[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp54)))))) / fTemp56));
			float fTemp57 = mydsp_faustpower2_f((1.0f - (fSlow9 * fRec30[0])));
			fVec2[0] = fTemp57;
			float fTemp58 = (fConst4 * fTemp57);
			fRec38[0] = (((((fSlow5 - fVec0[1]) > 0.0f) > 0))?0.0f:(float)java.lang.Math.min(fTemp58, ((fRec38[1] + (fConst4 * (fTemp57 - fVec2[1]))) + 1.0f)));
			float fTemp59 = (fConst5 * fTemp57);
			int iTemp60 = (fRec38[0] < fTemp59);
			float fTemp61 = (fSlow7 * (((fRec36[2] + (fRec36[0] + (2.0f * fRec36[1]))) * (((iTemp60==0)?true:false)?(((fRec38[0] < 0.0f))?0.0f:(((iTemp60==0)?true:false)?(fConst6 * (fRec38[0] / fTemp57)):1.0f)):(((fRec38[0] < fTemp58))?((fConst6 * ((0.0f - (fRec38[0] - fTemp59)) / fTemp57)) + 1.0f):0.0f))) / fTemp56));
			fVec3[0] = (fVec1[1] + fTemp61);
			fRec32[(IOTA & 2047)] = ((0.400000006f * fRec32[((IOTA - 1) & 2047)]) + (0.600000024f * fVec3[1]));
			float fRec27 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * fRec32[((IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416666679f * (fTemp26 * fRec32[((IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * fRec32[((IOTA - iTemp19) & 2047)]) + (0.5f * (((fTemp7 * fTemp17) * fTemp18) * fRec32[((IOTA - iTemp16) & 2047)]))) + (0.166666672f * ((fTemp23 * fTemp25) * fRec32[((IOTA - iTemp24) & 2047)]))))));
			int iRec28 = iRec35;
			fRec21[0] = fRec26;
			float fRec22 = (fTemp61 + fRec21[1]);
			float fRec23 = fRec27;
			int iRec24 = iRec28;
			fRec17[(IOTA & 2047)] = fRec22;
			float fRec18 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * fRec17[((IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166666672f * ((fTemp49 * fTemp51) * fRec17[((IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * fRec17[((IOTA - (iTemp45 + 1)) & 2047)]) + (0.5f * (((fTemp33 * fTemp43) * fTemp44) * fRec17[((IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416666679f * (fTemp52 * fRec17[((IOTA - (iTemp53 + 1)) & 2047)])))));
			fRec19[0] = fRec23;
			int iRec20 = iRec24;
			fRec15[0] = fRec19[1];
			int iRec16 = iRec20;
			float fRec12 = fRec15[1];
			float fRec13 = ((float)iRec16 + fRec15[1]);
			iRec6[0] = iRec11;
			float fRec7 = fRec14;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = fRec18;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp62 = (fSlow0 * fRec1);
			output0[i] = fTemp62;
			output1[i] = fTemp62;
			iRec10[1] = iRec10[0];
			fRec29[1] = fRec29[0];
			fVec0[1] = fVec0[0];
			fRec30[1] = fRec30[0];
			fRec25[1] = fRec25[0];
			fRec31[1] = fRec31[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec33[j0] = fRec33[(j0 - 1)];
				
			}
			IOTA = (IOTA + 1);
			fVec1[1] = fVec1[0];
			iRec37[1] = iRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fVec2[1] = fVec2[0];
			fRec38[1] = fRec38[0];
			fVec3[1] = fVec3[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec15[j1] = fRec15[(j1 - 1)];
				
			}
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

