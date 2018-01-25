/* ------------------------------------------------------------
name: "violin2"
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
	
	int iRec10[] = new int[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fHslider0;
	float fHslider1;
	float fRec26[] = new float[2];
	float fRec22[] = new float[2];
	float fHslider2;
	float fHslider3;
	float fRec28[] = new float[2];
	float fRec27[] = new float[2];
	float fRec29[] = new float[4];
	int IOTA;
	float fRec30[] = new float[2048];
	float fConst6;
	float fVec0[] = new float[2];
	float fVec1[] = new float[2048];
	float fRec18[] = new float[2048];
	float fRec20[] = new float[2];
	float fRec16[] = new float[4];
	float fConst7;
	float fConst8;
	float fRec14[] = new float[3];
	float fConst9;
	int iRec6[] = new int[2];
	float fRec2[] = new float[2048];
	float fRec0[] = new float[2];
	int iRec42[] = new int[2];
	float fHslider4;
	float fHslider5;
	float fRec58[] = new float[2];
	float fRec54[] = new float[2];
	float fHslider6;
	float fRec59[] = new float[4];
	float fRec60[] = new float[2048];
	float fVec2[] = new float[2];
	float fVec3[] = new float[2048];
	float fRec50[] = new float[2048];
	float fRec52[] = new float[2];
	float fRec48[] = new float[4];
	float fRec46[] = new float[3];
	int iRec38[] = new int[2];
	float fRec34[] = new float[2048];
	float fRec32[] = new float[2];
	int iRec72[] = new int[2];
	float fHslider7;
	float fHslider8;
	float fRec88[] = new float[2];
	float fRec84[] = new float[2];
	float fHslider9;
	float fRec89[] = new float[4];
	float fRec90[] = new float[2048];
	float fVec4[] = new float[2];
	float fVec5[] = new float[2048];
	float fRec80[] = new float[2048];
	float fRec82[] = new float[2];
	float fRec78[] = new float[4];
	float fRec76[] = new float[3];
	int iRec68[] = new int[2];
	float fRec64[] = new float[2048];
	float fRec62[] = new float[2];
	int iRec102[] = new int[2];
	float fHslider10;
	float fHslider11;
	float fRec118[] = new float[2];
	float fRec114[] = new float[2];
	float fHslider12;
	float fRec119[] = new float[4];
	float fRec120[] = new float[2048];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2048];
	float fRec110[] = new float[2048];
	float fRec112[] = new float[2];
	float fRec108[] = new float[4];
	float fRec106[] = new float[3];
	int iRec98[] = new int[2];
	float fRec94[] = new float[2048];
	float fRec92[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'4',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Send Fingers Count':'1',  'Keyboard 0 - Number of Keys':'12',  'Keyboard 1 - Number of Keys':'12',  'Keyboard 2 - Number of Keys':'12',  'Keyboard 3 - Number of Keys':'12',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 2 - Send Y':'1',  'Keyboard 3 - Send Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "violin2");
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
		fConst5 = (0.000441176468f * fConst0);
		fConst6 = (0.0010294118f * fConst0);
		fConst7 = (((fConst2 + -0.5f) / fConst1) + 1.0f);
		fConst8 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst1))));
		fConst9 = (0.0f - fConst2);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)220.0f;
		fHslider1 = (float)1.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)330.0f;
		fHslider5 = (float)1.0f;
		fHslider6 = (float)0.0f;
		fHslider7 = (float)440.0f;
		fHslider8 = (float)1.0f;
		fHslider9 = (float)0.0f;
		fHslider10 = (float)550.0f;
		fHslider11 = (float)1.0f;
		fHslider12 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec10[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec26[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec22[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec28[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec27[l4] = 0.0f;
			
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
		for (int l8 = 0; (l8 < 2048); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2048); l9 = (l9 + 1)) {
			fRec18[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec20[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 4); l11 = (l11 + 1)) {
			fRec16[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec14[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			iRec6[l13] = 0;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fRec2[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec0[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			iRec42[l16] = 0;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec58[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec54[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 4); l19 = (l19 + 1)) {
			fRec59[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2048); l20 = (l20 + 1)) {
			fRec60[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec2[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2048); l22 = (l22 + 1)) {
			fVec3[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			fRec50[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec52[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 4); l25 = (l25 + 1)) {
			fRec48[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec46[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			iRec38[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 2048); l28 = (l28 + 1)) {
			fRec34[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec32[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			iRec72[l30] = 0;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec88[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec84[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 4); l33 = (l33 + 1)) {
			fRec89[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2048); l34 = (l34 + 1)) {
			fRec90[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec4[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2048); l36 = (l36 + 1)) {
			fVec5[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2048); l37 = (l37 + 1)) {
			fRec80[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec82[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 4); l39 = (l39 + 1)) {
			fRec78[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec76[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			iRec68[l41] = 0;
			
		}
		for (int l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			fRec64[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec62[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			iRec102[l44] = 0;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec118[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec114[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 4); l47 = (l47 + 1)) {
			fRec119[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2048); l48 = (l48 + 1)) {
			fRec120[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec6[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			fVec7[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			fRec110[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec112[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			fRec108[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec106[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			iRec98[l55] = 0;
			
		}
		for (int l56 = 0; (l56 < 2048); l56 = (l56 + 1)) {
			fRec94[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec92[l57] = 0.0f;
			
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
		ui_interface.openVerticalBox("violin2");
		ui_interface.addHorizontalSlider("kb0bend", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb0fingers", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb0freq", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 220.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb1bend", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb1fingers", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1freq", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 330.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb2bend", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb2fingers", new FaustVarAccess() {
				public String getId() { return "fHslider9"; }
				public void set(float val) { fHslider9 = val; }
				public float get() { return (float)fHslider9; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb2freq", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 440.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb3bend", new FaustVarAccess() {
				public String getId() { return "fHslider11"; }
				public void set(float val) { fHslider11 = val; }
				public float get() { return (float)fHslider11; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb3fingers", new FaustVarAccess() {
				public String getId() { return "fHslider12"; }
				public void set(float val) { fHslider12 = val; }
				public float get() { return (float)fHslider12; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb3freq", new FaustVarAccess() {
				public String getId() { return "fHslider10"; }
				public void set(float val) { fHslider10 = val; }
				public float get() { return (float)fHslider10; }
			}
			, 550.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("y", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.340000004f / (fHslider0 * fHslider1));
		int iSlow1 = ((int)fHslider2 > 0);
		float fSlow2 = (0.00100000005f * fHslider3);
		float fSlow3 = (0.340000004f / (fHslider4 * fHslider5));
		int iSlow4 = ((int)fHslider6 > 0);
		float fSlow5 = (0.340000004f / (fHslider7 * fHslider8));
		int iSlow6 = ((int)fHslider9 > 0);
		float fSlow7 = (0.340000004f / (fHslider10 * fHslider11));
		int iSlow8 = ((int)fHslider12 > 0);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec10[0] = 0;
			int iRec11 = iRec10[1];
			float fRec15 = ((float)iRec6[1] - (0.989264667f * ((0.600000024f * fRec16[2]) + (0.200000003f * (fRec16[1] + fRec16[3])))));
			fRec26[0] = (fSlow0 + (0.999000013f * fRec26[1]));
			float fTemp0 = (fRec26[0] + -0.0799999982f);
			float fTemp1 = (fConst5 * fTemp0);
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
			fRec28[0] = (fSlow2 + (0.999000013f * fRec28[1]));
			fRec27[0] = ((0.999000013f * fRec27[1]) + (0.00100000005f * (float)java.lang.Math.min(1.0f, (3000.0f * (float)java.lang.Math.abs((fRec28[0] - fRec28[1]))))));
			fRec29[0] = fRec0[1];
			fRec30[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec29[2]) + (0.100000001f * (fRec29[1] + fRec29[3])))));
			int iRec31 = 0;
			float fTemp27 = (fConst6 * fTemp0);
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
			float fTemp53 = (((float)iSlow1 * fRec27[0]) - (fRec22[1] + fVec0[1]));
			float fTemp54 = (fTemp53 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((3.0f * fTemp53)) + 0.75f)))));
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
			fRec14[0] = (fRec16[1] - (fConst3 * ((fConst7 * fRec14[2]) + (fConst8 * fRec14[1]))));
			float fTemp56 = (fConst3 * ((fConst2 * fRec14[0]) + (fConst9 * fRec14[2])));
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
			iRec42[0] = 0;
			int iRec43 = iRec42[1];
			float fRec47 = ((float)iRec38[1] - (0.989264667f * ((0.600000024f * fRec48[2]) + (0.200000003f * (fRec48[1] + fRec48[3])))));
			fRec58[0] = (fSlow3 + (0.999000013f * fRec58[1]));
			float fTemp57 = (fRec58[0] + -0.0799999982f);
			float fTemp58 = (fConst5 * fTemp57);
			float fTemp59 = (fTemp58 + -1.49999499f);
			int iTemp60 = (int)fTemp59;
			int iTemp61 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp60));
			float fTemp62 = (float)java.lang.Math.floor(fTemp59);
			float fTemp63 = (fTemp58 + (-1.0f - fTemp62));
			float fTemp64 = (0.0f - fTemp63);
			float fTemp65 = (fTemp58 + (-2.0f - fTemp62));
			float fTemp66 = (0.0f - (0.5f * fTemp65));
			float fTemp67 = (fTemp58 + (-3.0f - fTemp62));
			float fTemp68 = (0.0f - (0.333333343f * fTemp67));
			float fTemp69 = (fTemp58 + (-4.0f - fTemp62));
			float fTemp70 = (0.0f - (0.25f * fTemp69));
			float fTemp71 = (fTemp58 - fTemp62);
			int iTemp72 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp60 + 2)));
			float fTemp73 = (0.0f - fTemp67);
			float fTemp74 = (0.0f - (0.5f * fTemp69));
			int iTemp75 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp60 + 1)));
			float fTemp76 = (0.0f - fTemp65);
			float fTemp77 = (0.0f - (0.5f * fTemp67));
			float fTemp78 = (0.0f - (0.333333343f * fTemp69));
			float fTemp79 = (fTemp63 * fTemp65);
			int iTemp80 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp60 + 3)));
			float fTemp81 = (0.0f - fTemp69);
			float fTemp82 = (fTemp79 * fTemp67);
			int iTemp83 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp60 + 4)));
			fRec54[0] = (((((fRec34[((IOTA - (iTemp61 + 1)) & 2047)] * fTemp64) * fTemp66) * fTemp68) * fTemp70) + (fTemp71 * ((((0.5f * (((fTemp63 * fRec34[((IOTA - (iTemp72 + 1)) & 2047)]) * fTemp73) * fTemp74)) + (((fRec34[((IOTA - (iTemp75 + 1)) & 2047)] * fTemp76) * fTemp77) * fTemp78)) + (0.166666672f * ((fTemp79 * fRec34[((IOTA - (iTemp80 + 1)) & 2047)]) * fTemp81))) + (0.0416666679f * (fTemp82 * fRec34[((IOTA - (iTemp83 + 1)) & 2047)])))));
			fRec59[0] = fRec32[1];
			fRec60[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec59[2]) + (0.100000001f * (fRec59[1] + fRec59[3])))));
			int iRec61 = 0;
			float fTemp84 = (fConst6 * fTemp57);
			float fTemp85 = (fTemp84 + -1.49999499f);
			int iTemp86 = (int)fTemp85;
			int iTemp87 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp86));
			float fTemp88 = (float)java.lang.Math.floor(fTemp85);
			float fTemp89 = (fTemp84 + (-1.0f - fTemp88));
			float fTemp90 = (0.0f - fTemp89);
			float fTemp91 = (fTemp84 + (-2.0f - fTemp88));
			float fTemp92 = (0.0f - (0.5f * fTemp91));
			float fTemp93 = (fTemp84 + (-3.0f - fTemp88));
			float fTemp94 = (0.0f - (0.333333343f * fTemp93));
			float fTemp95 = (fTemp84 + (-4.0f - fTemp88));
			float fTemp96 = (0.0f - (0.25f * fTemp95));
			float fTemp97 = (fTemp84 - fTemp88);
			int iTemp98 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp86 + 2)));
			float fTemp99 = (0.0f - fTemp93);
			float fTemp100 = (0.0f - (0.5f * fTemp95));
			int iTemp101 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp86 + 1)));
			float fTemp102 = (0.0f - fTemp91);
			float fTemp103 = (0.0f - (0.5f * fTemp93));
			float fTemp104 = (0.0f - (0.333333343f * fTemp95));
			float fTemp105 = (fTemp89 * fTemp91);
			int iTemp106 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp86 + 3)));
			float fTemp107 = (0.0f - fTemp95);
			float fTemp108 = (fTemp105 * fTemp93);
			int iTemp109 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp86 + 4)));
			fVec2[0] = (((((fRec60[((IOTA - (iTemp87 + 2)) & 2047)] * fTemp90) * fTemp92) * fTemp94) * fTemp96) + (fTemp97 * ((((0.5f * (((fTemp89 * fRec60[((IOTA - (iTemp98 + 2)) & 2047)]) * fTemp99) * fTemp100)) + (((fRec60[((IOTA - (iTemp101 + 2)) & 2047)] * fTemp102) * fTemp103) * fTemp104)) + (0.166666672f * ((fTemp105 * fRec60[((IOTA - (iTemp106 + 2)) & 2047)]) * fTemp107))) + (0.0416666679f * (fTemp108 * fRec60[((IOTA - (iTemp109 + 2)) & 2047)])))));
			float fTemp110 = (((float)iSlow4 * fRec27[0]) - (fRec54[1] + fVec2[1]));
			float fTemp111 = (fTemp110 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((3.0f * fTemp110)) + 0.75f)))));
			float fRec55 = (fRec54[1] + fTemp111);
			float fTemp112 = (fVec2[1] + fTemp111);
			fVec3[(IOTA & 2047)] = fTemp112;
			float fRec56 = (((((fTemp64 * fTemp66) * fTemp68) * fTemp70) * fVec3[((IOTA - iTemp61) & 2047)]) + (fTemp71 * ((0.0416666679f * (fTemp82 * fVec3[((IOTA - iTemp83) & 2047)])) + (((((fTemp76 * fTemp77) * fTemp78) * fVec3[((IOTA - iTemp75) & 2047)]) + (0.5f * (((fTemp63 * fTemp73) * fTemp74) * fVec3[((IOTA - iTemp72) & 2047)]))) + (0.166666672f * ((fTemp79 * fTemp81) * fVec3[((IOTA - iTemp80) & 2047)]))))));
			int iRec57 = iRec61;
			fRec50[(IOTA & 2047)] = fRec55;
			float fRec51 = (((((fTemp90 * fTemp92) * fTemp94) * fTemp96) * fRec50[((IOTA - (iTemp87 + 1)) & 2047)]) + (fTemp97 * (((0.166666672f * ((fTemp105 * fTemp107) * fRec50[((IOTA - (iTemp106 + 1)) & 2047)])) + ((((fTemp102 * fTemp103) * fTemp104) * fRec50[((IOTA - (iTemp101 + 1)) & 2047)]) + (0.5f * (((fTemp89 * fTemp99) * fTemp100) * fRec50[((IOTA - (iTemp98 + 1)) & 2047)])))) + (0.0416666679f * (fTemp108 * fRec50[((IOTA - (iTemp109 + 1)) & 2047)])))));
			fRec52[0] = fRec56;
			int iRec53 = iRec57;
			fRec48[0] = fRec52[1];
			int iRec49 = iRec53;
			fRec46[0] = (fRec48[1] - (fConst3 * ((fConst8 * fRec46[1]) + (fConst7 * fRec46[2]))));
			float fTemp113 = (fConst3 * ((fConst2 * fRec46[0]) + (fConst9 * fRec46[2])));
			float fRec44 = fTemp113;
			float fRec45 = ((float)iRec49 + fTemp113);
			iRec38[0] = iRec43;
			float fRec39 = fRec47;
			float fRec40 = fRec44;
			float fRec41 = fRec45;
			fRec34[(IOTA & 2047)] = fRec39;
			float fRec35 = fRec51;
			float fRec36 = fRec40;
			float fRec37 = fRec41;
			fRec32[0] = fRec35;
			float fRec33 = fRec37;
			iRec72[0] = 0;
			int iRec73 = iRec72[1];
			float fRec77 = ((float)iRec68[1] - (0.989264667f * ((0.600000024f * fRec78[2]) + (0.200000003f * (fRec78[1] + fRec78[3])))));
			fRec88[0] = (fSlow5 + (0.999000013f * fRec88[1]));
			float fTemp114 = (fRec88[0] + -0.0799999982f);
			float fTemp115 = (fConst5 * fTemp114);
			float fTemp116 = (fTemp115 + -1.49999499f);
			int iTemp117 = (int)fTemp116;
			int iTemp118 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp117));
			float fTemp119 = (float)java.lang.Math.floor(fTemp116);
			float fTemp120 = (fTemp115 + (-1.0f - fTemp119));
			float fTemp121 = (0.0f - fTemp120);
			float fTemp122 = (fTemp115 + (-2.0f - fTemp119));
			float fTemp123 = (0.0f - (0.5f * fTemp122));
			float fTemp124 = (fTemp115 + (-3.0f - fTemp119));
			float fTemp125 = (0.0f - (0.333333343f * fTemp124));
			float fTemp126 = (fTemp115 + (-4.0f - fTemp119));
			float fTemp127 = (0.0f - (0.25f * fTemp126));
			float fTemp128 = (fTemp115 - fTemp119);
			int iTemp129 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp117 + 2)));
			float fTemp130 = (0.0f - fTemp124);
			float fTemp131 = (0.0f - (0.5f * fTemp126));
			int iTemp132 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp117 + 1)));
			float fTemp133 = (0.0f - fTemp122);
			float fTemp134 = (0.0f - (0.5f * fTemp124));
			float fTemp135 = (0.0f - (0.333333343f * fTemp126));
			float fTemp136 = (fTemp120 * fTemp122);
			int iTemp137 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp117 + 3)));
			float fTemp138 = (0.0f - fTemp126);
			float fTemp139 = (fTemp136 * fTemp124);
			int iTemp140 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp117 + 4)));
			fRec84[0] = (((((fRec64[((IOTA - (iTemp118 + 1)) & 2047)] * fTemp121) * fTemp123) * fTemp125) * fTemp127) + (fTemp128 * ((((0.5f * (((fTemp120 * fRec64[((IOTA - (iTemp129 + 1)) & 2047)]) * fTemp130) * fTemp131)) + (((fRec64[((IOTA - (iTemp132 + 1)) & 2047)] * fTemp133) * fTemp134) * fTemp135)) + (0.166666672f * ((fTemp136 * fRec64[((IOTA - (iTemp137 + 1)) & 2047)]) * fTemp138))) + (0.0416666679f * (fTemp139 * fRec64[((IOTA - (iTemp140 + 1)) & 2047)])))));
			fRec89[0] = fRec62[1];
			fRec90[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec89[2]) + (0.100000001f * (fRec89[1] + fRec89[3])))));
			int iRec91 = 0;
			float fTemp141 = (fConst6 * fTemp114);
			float fTemp142 = (fTemp141 + -1.49999499f);
			int iTemp143 = (int)fTemp142;
			int iTemp144 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp143));
			float fTemp145 = (float)java.lang.Math.floor(fTemp142);
			float fTemp146 = (fTemp141 + (-1.0f - fTemp145));
			float fTemp147 = (0.0f - fTemp146);
			float fTemp148 = (fTemp141 + (-2.0f - fTemp145));
			float fTemp149 = (0.0f - (0.5f * fTemp148));
			float fTemp150 = (fTemp141 + (-3.0f - fTemp145));
			float fTemp151 = (0.0f - (0.333333343f * fTemp150));
			float fTemp152 = (fTemp141 + (-4.0f - fTemp145));
			float fTemp153 = (0.0f - (0.25f * fTemp152));
			float fTemp154 = (fTemp141 - fTemp145);
			int iTemp155 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp143 + 2)));
			float fTemp156 = (0.0f - fTemp150);
			float fTemp157 = (0.0f - (0.5f * fTemp152));
			int iTemp158 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp143 + 1)));
			float fTemp159 = (0.0f - fTemp148);
			float fTemp160 = (0.0f - (0.5f * fTemp150));
			float fTemp161 = (0.0f - (0.333333343f * fTemp152));
			float fTemp162 = (fTemp146 * fTemp148);
			int iTemp163 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp143 + 3)));
			float fTemp164 = (0.0f - fTemp152);
			float fTemp165 = (fTemp162 * fTemp150);
			int iTemp166 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp143 + 4)));
			fVec4[0] = (((((fRec90[((IOTA - (iTemp144 + 2)) & 2047)] * fTemp147) * fTemp149) * fTemp151) * fTemp153) + (fTemp154 * ((((0.5f * (((fTemp146 * fRec90[((IOTA - (iTemp155 + 2)) & 2047)]) * fTemp156) * fTemp157)) + (((fRec90[((IOTA - (iTemp158 + 2)) & 2047)] * fTemp159) * fTemp160) * fTemp161)) + (0.166666672f * ((fTemp162 * fRec90[((IOTA - (iTemp163 + 2)) & 2047)]) * fTemp164))) + (0.0416666679f * (fTemp165 * fRec90[((IOTA - (iTemp166 + 2)) & 2047)])))));
			float fTemp167 = (((float)iSlow6 * fRec27[0]) - (fRec84[1] + fVec4[1]));
			float fTemp168 = (fTemp167 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((3.0f * fTemp167)) + 0.75f)))));
			float fRec85 = (fRec84[1] + fTemp168);
			float fTemp169 = (fVec4[1] + fTemp168);
			fVec5[(IOTA & 2047)] = fTemp169;
			float fRec86 = (((((fTemp121 * fTemp123) * fTemp125) * fTemp127) * fVec5[((IOTA - iTemp118) & 2047)]) + (fTemp128 * ((0.0416666679f * (fTemp139 * fVec5[((IOTA - iTemp140) & 2047)])) + (((((fTemp133 * fTemp134) * fTemp135) * fVec5[((IOTA - iTemp132) & 2047)]) + (0.5f * (((fTemp120 * fTemp130) * fTemp131) * fVec5[((IOTA - iTemp129) & 2047)]))) + (0.166666672f * ((fTemp136 * fTemp138) * fVec5[((IOTA - iTemp137) & 2047)]))))));
			int iRec87 = iRec91;
			fRec80[(IOTA & 2047)] = fRec85;
			float fRec81 = (((((fTemp147 * fTemp149) * fTemp151) * fTemp153) * fRec80[((IOTA - (iTemp144 + 1)) & 2047)]) + (fTemp154 * (((0.166666672f * ((fTemp162 * fTemp164) * fRec80[((IOTA - (iTemp163 + 1)) & 2047)])) + ((((fTemp159 * fTemp160) * fTemp161) * fRec80[((IOTA - (iTemp158 + 1)) & 2047)]) + (0.5f * (((fTemp146 * fTemp156) * fTemp157) * fRec80[((IOTA - (iTemp155 + 1)) & 2047)])))) + (0.0416666679f * (fTemp165 * fRec80[((IOTA - (iTemp166 + 1)) & 2047)])))));
			fRec82[0] = fRec86;
			int iRec83 = iRec87;
			fRec78[0] = fRec82[1];
			int iRec79 = iRec83;
			fRec76[0] = (fRec78[1] - (fConst3 * ((fConst8 * fRec76[1]) + (fConst7 * fRec76[2]))));
			float fTemp170 = (fConst3 * ((fConst2 * fRec76[0]) + (fConst9 * fRec76[2])));
			float fRec74 = fTemp170;
			float fRec75 = ((float)iRec79 + fTemp170);
			iRec68[0] = iRec73;
			float fRec69 = fRec77;
			float fRec70 = fRec74;
			float fRec71 = fRec75;
			fRec64[(IOTA & 2047)] = fRec69;
			float fRec65 = fRec81;
			float fRec66 = fRec70;
			float fRec67 = fRec71;
			fRec62[0] = fRec65;
			float fRec63 = fRec67;
			iRec102[0] = 0;
			int iRec103 = iRec102[1];
			float fRec107 = ((float)iRec98[1] - (0.989264667f * ((0.600000024f * fRec108[2]) + (0.200000003f * (fRec108[1] + fRec108[3])))));
			fRec118[0] = (fSlow7 + (0.999000013f * fRec118[1]));
			float fTemp171 = (fRec118[0] + -0.0799999982f);
			float fTemp172 = (fConst5 * fTemp171);
			float fTemp173 = (fTemp172 + -1.49999499f);
			int iTemp174 = (int)fTemp173;
			int iTemp175 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp174));
			float fTemp176 = (float)java.lang.Math.floor(fTemp173);
			float fTemp177 = (fTemp172 + (-1.0f - fTemp176));
			float fTemp178 = (0.0f - fTemp177);
			float fTemp179 = (fTemp172 + (-2.0f - fTemp176));
			float fTemp180 = (0.0f - (0.5f * fTemp179));
			float fTemp181 = (fTemp172 + (-3.0f - fTemp176));
			float fTemp182 = (0.0f - (0.333333343f * fTemp181));
			float fTemp183 = (fTemp172 + (-4.0f - fTemp176));
			float fTemp184 = (0.0f - (0.25f * fTemp183));
			float fTemp185 = (fTemp172 - fTemp176);
			int iTemp186 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp174 + 2)));
			float fTemp187 = (0.0f - fTemp181);
			float fTemp188 = (0.0f - (0.5f * fTemp183));
			int iTemp189 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp174 + 1)));
			float fTemp190 = (0.0f - fTemp179);
			float fTemp191 = (0.0f - (0.5f * fTemp181));
			float fTemp192 = (0.0f - (0.333333343f * fTemp183));
			float fTemp193 = (fTemp177 * fTemp179);
			int iTemp194 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp174 + 3)));
			float fTemp195 = (0.0f - fTemp183);
			float fTemp196 = (fTemp193 * fTemp181);
			int iTemp197 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp174 + 4)));
			fRec114[0] = (((((fRec94[((IOTA - (iTemp175 + 1)) & 2047)] * fTemp178) * fTemp180) * fTemp182) * fTemp184) + (fTemp185 * ((((0.5f * (((fTemp177 * fRec94[((IOTA - (iTemp186 + 1)) & 2047)]) * fTemp187) * fTemp188)) + (((fRec94[((IOTA - (iTemp189 + 1)) & 2047)] * fTemp190) * fTemp191) * fTemp192)) + (0.166666672f * ((fTemp193 * fRec94[((IOTA - (iTemp194 + 1)) & 2047)]) * fTemp195))) + (0.0416666679f * (fTemp196 * fRec94[((IOTA - (iTemp197 + 1)) & 2047)])))));
			fRec119[0] = fRec92[1];
			fRec120[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec119[2]) + (0.100000001f * (fRec119[1] + fRec119[3])))));
			int iRec121 = 0;
			float fTemp198 = (fConst6 * fTemp171);
			float fTemp199 = (fTemp198 + -1.49999499f);
			int iTemp200 = (int)fTemp199;
			int iTemp201 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp200));
			float fTemp202 = (float)java.lang.Math.floor(fTemp199);
			float fTemp203 = (fTemp198 + (-1.0f - fTemp202));
			float fTemp204 = (0.0f - fTemp203);
			float fTemp205 = (fTemp198 + (-2.0f - fTemp202));
			float fTemp206 = (0.0f - (0.5f * fTemp205));
			float fTemp207 = (fTemp198 + (-3.0f - fTemp202));
			float fTemp208 = (0.0f - (0.333333343f * fTemp207));
			float fTemp209 = (fTemp198 + (-4.0f - fTemp202));
			float fTemp210 = (0.0f - (0.25f * fTemp209));
			float fTemp211 = (fTemp198 - fTemp202);
			int iTemp212 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp200 + 2)));
			float fTemp213 = (0.0f - fTemp207);
			float fTemp214 = (0.0f - (0.5f * fTemp209));
			int iTemp215 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp200 + 1)));
			float fTemp216 = (0.0f - fTemp205);
			float fTemp217 = (0.0f - (0.5f * fTemp207));
			float fTemp218 = (0.0f - (0.333333343f * fTemp209));
			float fTemp219 = (fTemp203 * fTemp205);
			int iTemp220 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp200 + 3)));
			float fTemp221 = (0.0f - fTemp209);
			float fTemp222 = (fTemp219 * fTemp207);
			int iTemp223 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp200 + 4)));
			fVec6[0] = (((((fRec120[((IOTA - (iTemp201 + 2)) & 2047)] * fTemp204) * fTemp206) * fTemp208) * fTemp210) + (fTemp211 * ((((0.5f * (((fTemp203 * fRec120[((IOTA - (iTemp212 + 2)) & 2047)]) * fTemp213) * fTemp214)) + (((fRec120[((IOTA - (iTemp215 + 2)) & 2047)] * fTemp216) * fTemp217) * fTemp218)) + (0.166666672f * ((fTemp219 * fRec120[((IOTA - (iTemp220 + 2)) & 2047)]) * fTemp221))) + (0.0416666679f * (fTemp222 * fRec120[((IOTA - (iTemp223 + 2)) & 2047)])))));
			float fTemp224 = (((float)iSlow8 * fRec27[0]) - (fRec114[1] + fVec6[1]));
			float fTemp225 = (fTemp224 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((3.0f * fTemp224)) + 0.75f)))));
			float fRec115 = (fRec114[1] + fTemp225);
			float fTemp226 = (fVec6[1] + fTemp225);
			fVec7[(IOTA & 2047)] = fTemp226;
			float fRec116 = (((((fTemp178 * fTemp180) * fTemp182) * fTemp184) * fVec7[((IOTA - iTemp175) & 2047)]) + (fTemp185 * ((0.0416666679f * (fTemp196 * fVec7[((IOTA - iTemp197) & 2047)])) + (((((fTemp190 * fTemp191) * fTemp192) * fVec7[((IOTA - iTemp189) & 2047)]) + (0.5f * (((fTemp177 * fTemp187) * fTemp188) * fVec7[((IOTA - iTemp186) & 2047)]))) + (0.166666672f * ((fTemp193 * fTemp195) * fVec7[((IOTA - iTemp194) & 2047)]))))));
			int iRec117 = iRec121;
			fRec110[(IOTA & 2047)] = fRec115;
			float fRec111 = (((((fTemp204 * fTemp206) * fTemp208) * fTemp210) * fRec110[((IOTA - (iTemp201 + 1)) & 2047)]) + (fTemp211 * (((0.166666672f * ((fTemp219 * fTemp221) * fRec110[((IOTA - (iTemp220 + 1)) & 2047)])) + ((((fTemp216 * fTemp217) * fTemp218) * fRec110[((IOTA - (iTemp215 + 1)) & 2047)]) + (0.5f * (((fTemp203 * fTemp213) * fTemp214) * fRec110[((IOTA - (iTemp212 + 1)) & 2047)])))) + (0.0416666679f * (fTemp222 * fRec110[((IOTA - (iTemp223 + 1)) & 2047)])))));
			fRec112[0] = fRec116;
			int iRec113 = iRec117;
			fRec108[0] = fRec112[1];
			int iRec109 = iRec113;
			fRec106[0] = (fRec108[1] - (fConst3 * ((fConst8 * fRec106[1]) + (fConst7 * fRec106[2]))));
			float fTemp227 = (fConst3 * ((fConst2 * fRec106[0]) + (fConst9 * fRec106[2])));
			float fRec104 = fTemp227;
			float fRec105 = ((float)iRec109 + fTemp227);
			iRec98[0] = iRec103;
			float fRec99 = fRec107;
			float fRec100 = fRec104;
			float fRec101 = fRec105;
			fRec94[(IOTA & 2047)] = fRec99;
			float fRec95 = fRec111;
			float fRec96 = fRec100;
			float fRec97 = fRec101;
			fRec92[0] = fRec95;
			float fRec93 = fRec97;
			float fTemp228 = (((fRec1 + fRec33) + fRec63) + fRec93);
			output0[i] = fTemp228;
			output1[i] = fTemp228;
			iRec10[1] = iRec10[0];
			fRec26[1] = fRec26[0];
			fRec22[1] = fRec22[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec29[j0] = fRec29[(j0 - 1)];
				
			}
			IOTA = (IOTA + 1);
			fVec0[1] = fVec0[0];
			fRec20[1] = fRec20[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec16[j1] = fRec16[(j1 - 1)];
				
			}
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
			iRec42[1] = iRec42[0];
			fRec58[1] = fRec58[0];
			fRec54[1] = fRec54[0];
			for (int j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
				fRec59[j2] = fRec59[(j2 - 1)];
				
			}
			fVec2[1] = fVec2[0];
			fRec52[1] = fRec52[0];
			for (int j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
				fRec48[j3] = fRec48[(j3 - 1)];
				
			}
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			iRec38[1] = iRec38[0];
			fRec32[1] = fRec32[0];
			iRec72[1] = iRec72[0];
			fRec88[1] = fRec88[0];
			fRec84[1] = fRec84[0];
			for (int j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
				fRec89[j4] = fRec89[(j4 - 1)];
				
			}
			fVec4[1] = fVec4[0];
			fRec82[1] = fRec82[0];
			for (int j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
				fRec78[j5] = fRec78[(j5 - 1)];
				
			}
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			iRec68[1] = iRec68[0];
			fRec62[1] = fRec62[0];
			iRec102[1] = iRec102[0];
			fRec118[1] = fRec118[0];
			fRec114[1] = fRec114[0];
			for (int j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
				fRec119[j6] = fRec119[(j6 - 1)];
				
			}
			fVec6[1] = fVec6[0];
			fRec112[1] = fRec112[0];
			for (int j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
				fRec108[j7] = fRec108[(j7 - 1)];
				
			}
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			iRec98[1] = iRec98[0];
			fRec92[1] = fRec92[0];
			
		}
		
	}
	
};

