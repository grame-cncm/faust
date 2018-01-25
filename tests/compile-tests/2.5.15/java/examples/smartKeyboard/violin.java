/* ------------------------------------------------------------
name: "violin"
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
	float fHslider4;
	float fRec32[] = new float[2];
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
	int iRec43[] = new int[2];
	float fHslider5;
	float fHslider6;
	float fRec59[] = new float[2];
	float fRec55[] = new float[2];
	float fHslider7;
	float fRec60[] = new float[4];
	float fRec61[] = new float[2048];
	float fVec2[] = new float[2];
	float fVec3[] = new float[2048];
	float fRec51[] = new float[2048];
	float fRec53[] = new float[2];
	float fRec49[] = new float[4];
	float fRec47[] = new float[3];
	int iRec39[] = new int[2];
	float fRec35[] = new float[2048];
	float fRec33[] = new float[2];
	int iRec73[] = new int[2];
	float fHslider8;
	float fHslider9;
	float fRec89[] = new float[2];
	float fRec85[] = new float[2];
	float fHslider10;
	float fRec90[] = new float[4];
	float fRec91[] = new float[2048];
	float fVec4[] = new float[2];
	float fVec5[] = new float[2048];
	float fRec81[] = new float[2048];
	float fRec83[] = new float[2];
	float fRec79[] = new float[4];
	float fRec77[] = new float[3];
	int iRec69[] = new int[2];
	float fRec65[] = new float[2048];
	float fRec63[] = new float[2];
	int iRec103[] = new int[2];
	float fHslider11;
	float fHslider12;
	float fRec119[] = new float[2];
	float fRec115[] = new float[2];
	float fHslider13;
	float fRec120[] = new float[4];
	float fRec121[] = new float[2048];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2048];
	float fRec111[] = new float[2048];
	float fRec113[] = new float[2];
	float fRec109[] = new float[4];
	float fRec107[] = new float[3];
	int iRec99[] = new int[2];
	float fRec95[] = new float[2048];
	float fRec93[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Send Fingers Count':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 4 - Send Key X':'1',  'Keyboard 4 - Send Key Y':'1',  'Keyboard 4 - Key 0 - Label':'Bow',  'Keyboard 4 - Static Mode':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "violin");
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
		fHslider4 = (float)0.0f;
		fHslider5 = (float)330.0f;
		fHslider6 = (float)1.0f;
		fHslider7 = (float)0.0f;
		fHslider8 = (float)440.0f;
		fHslider9 = (float)1.0f;
		fHslider10 = (float)0.0f;
		fHslider11 = (float)550.0f;
		fHslider12 = (float)1.0f;
		fHslider13 = (float)0.0f;
		
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
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			iRec43[l17] = 0;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec59[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec55[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 4); l20 = (l20 + 1)) {
			fRec60[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2048); l21 = (l21 + 1)) {
			fRec61[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec2[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			fVec3[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			fRec51[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec53[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 4); l26 = (l26 + 1)) {
			fRec49[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec47[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			iRec39[l28] = 0;
			
		}
		for (int l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			fRec35[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec33[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			iRec73[l31] = 0;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec89[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec85[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 4); l34 = (l34 + 1)) {
			fRec90[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2048); l35 = (l35 + 1)) {
			fRec91[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec4[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2048); l37 = (l37 + 1)) {
			fVec5[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			fRec81[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec83[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 4); l40 = (l40 + 1)) {
			fRec79[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec77[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			iRec69[l42] = 0;
			
		}
		for (int l43 = 0; (l43 < 2048); l43 = (l43 + 1)) {
			fRec65[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec63[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			iRec103[l45] = 0;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec119[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec115[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			fRec120[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2048); l49 = (l49 + 1)) {
			fRec121[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec6[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2048); l51 = (l51 + 1)) {
			fVec7[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2048); l52 = (l52 + 1)) {
			fRec111[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec113[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			fRec109[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec107[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			iRec99[l56] = 0;
			
		}
		for (int l57 = 0; (l57 < 2048); l57 = (l57 + 1)) {
			fRec95[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec93[l58] = 0.0f;
			
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
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb1fingers", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1freq", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 330.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb2bend", new FaustVarAccess() {
				public String getId() { return "fHslider9"; }
				public void set(float val) { fHslider9 = val; }
				public float get() { return (float)fHslider9; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb2fingers", new FaustVarAccess() {
				public String getId() { return "fHslider10"; }
				public void set(float val) { fHslider10 = val; }
				public float get() { return (float)fHslider10; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb2freq", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 440.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb3bend", new FaustVarAccess() {
				public String getId() { return "fHslider12"; }
				public void set(float val) { fHslider12 = val; }
				public float get() { return (float)fHslider12; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb3fingers", new FaustVarAccess() {
				public String getId() { return "fHslider13"; }
				public void set(float val) { fHslider13 = val; }
				public float get() { return (float)fHslider13; }
			}
			, 0.0f, 0.0f, 10.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb3freq", new FaustVarAccess() {
				public String getId() { return "fHslider11"; }
				public void set(float val) { fHslider11 = val; }
				public float get() { return (float)fHslider11; }
			}
			, 550.0f, 20.0f, 10000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("kb4k0x", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb4k0y", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
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
		float fSlow3 = (0.00100000005f * fHslider4);
		float fSlow4 = (0.340000004f / (fHslider5 * fHslider6));
		int iSlow5 = ((int)fHslider7 > 0);
		float fSlow6 = (0.340000004f / (fHslider8 * fHslider9));
		int iSlow7 = ((int)fHslider10 > 0);
		float fSlow8 = (0.340000004f / (fHslider11 * fHslider12));
		int iSlow9 = ((int)fHslider13 > 0);
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
			fRec27[0] = ((0.999000013f * fRec27[1]) + (0.00100000005f * (float)java.lang.Math.min(1.0f, (8000.0f * (float)java.lang.Math.abs((fRec28[0] - fRec28[1]))))));
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
			fRec32[0] = (fSlow3 + (0.999000013f * fRec32[1]));
			float fTemp54 = (5.0f - (4.0f * fRec32[0]));
			float fTemp55 = (fTemp53 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((fTemp54 * fTemp53)) + 0.75f)))));
			float fRec23 = (fRec22[1] + fTemp55);
			float fTemp56 = (fVec0[1] + fTemp55);
			fVec1[(IOTA & 2047)] = fTemp56;
			float fRec24 = (((((fTemp7 * fTemp9) * fTemp11) * fTemp13) * fVec1[((IOTA - iTemp4) & 2047)]) + (fTemp14 * ((0.0416666679f * (fTemp25 * fVec1[((IOTA - iTemp26) & 2047)])) + (((((fTemp19 * fTemp20) * fTemp21) * fVec1[((IOTA - iTemp18) & 2047)]) + (0.5f * (((fTemp6 * fTemp16) * fTemp17) * fVec1[((IOTA - iTemp15) & 2047)]))) + (0.166666672f * ((fTemp22 * fTemp24) * fVec1[((IOTA - iTemp23) & 2047)]))))));
			int iRec25 = iRec31;
			fRec18[(IOTA & 2047)] = fRec23;
			float fRec19 = (((((fTemp33 * fTemp35) * fTemp37) * fTemp39) * fRec18[((IOTA - (iTemp30 + 1)) & 2047)]) + (fTemp40 * (((0.166666672f * ((fTemp48 * fTemp50) * fRec18[((IOTA - (iTemp49 + 1)) & 2047)])) + ((((fTemp45 * fTemp46) * fTemp47) * fRec18[((IOTA - (iTemp44 + 1)) & 2047)]) + (0.5f * (((fTemp32 * fTemp42) * fTemp43) * fRec18[((IOTA - (iTemp41 + 1)) & 2047)])))) + (0.0416666679f * (fTemp51 * fRec18[((IOTA - (iTemp52 + 1)) & 2047)])))));
			fRec20[0] = fRec24;
			int iRec21 = iRec25;
			fRec16[0] = fRec20[1];
			int iRec17 = iRec21;
			fRec14[0] = (fRec16[1] - (fConst3 * ((fConst7 * fRec14[2]) + (fConst8 * fRec14[1]))));
			float fTemp57 = (fConst3 * ((fConst2 * fRec14[0]) + (fConst9 * fRec14[2])));
			float fRec12 = fTemp57;
			float fRec13 = ((float)iRec17 + fTemp57);
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
			iRec43[0] = 0;
			int iRec44 = iRec43[1];
			float fRec48 = ((float)iRec39[1] - (0.989264667f * ((0.600000024f * fRec49[2]) + (0.200000003f * (fRec49[1] + fRec49[3])))));
			fRec59[0] = (fSlow4 + (0.999000013f * fRec59[1]));
			float fTemp58 = (fRec59[0] + -0.0799999982f);
			float fTemp59 = (fConst5 * fTemp58);
			float fTemp60 = (fTemp59 + -1.49999499f);
			int iTemp61 = (int)fTemp60;
			int iTemp62 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp61));
			float fTemp63 = (float)java.lang.Math.floor(fTemp60);
			float fTemp64 = (fTemp59 + (-1.0f - fTemp63));
			float fTemp65 = (0.0f - fTemp64);
			float fTemp66 = (fTemp59 + (-2.0f - fTemp63));
			float fTemp67 = (0.0f - (0.5f * fTemp66));
			float fTemp68 = (fTemp59 + (-3.0f - fTemp63));
			float fTemp69 = (0.0f - (0.333333343f * fTemp68));
			float fTemp70 = (fTemp59 + (-4.0f - fTemp63));
			float fTemp71 = (0.0f - (0.25f * fTemp70));
			float fTemp72 = (fTemp59 - fTemp63);
			int iTemp73 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp61 + 2)));
			float fTemp74 = (0.0f - fTemp68);
			float fTemp75 = (0.0f - (0.5f * fTemp70));
			int iTemp76 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp61 + 1)));
			float fTemp77 = (0.0f - fTemp66);
			float fTemp78 = (0.0f - (0.5f * fTemp68));
			float fTemp79 = (0.0f - (0.333333343f * fTemp70));
			float fTemp80 = (fTemp64 * fTemp66);
			int iTemp81 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp61 + 3)));
			float fTemp82 = (0.0f - fTemp70);
			float fTemp83 = (fTemp80 * fTemp68);
			int iTemp84 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp61 + 4)));
			fRec55[0] = (((((fRec35[((IOTA - (iTemp62 + 1)) & 2047)] * fTemp65) * fTemp67) * fTemp69) * fTemp71) + (fTemp72 * ((((0.5f * (((fTemp64 * fRec35[((IOTA - (iTemp73 + 1)) & 2047)]) * fTemp74) * fTemp75)) + (((fRec35[((IOTA - (iTemp76 + 1)) & 2047)] * fTemp77) * fTemp78) * fTemp79)) + (0.166666672f * ((fTemp80 * fRec35[((IOTA - (iTemp81 + 1)) & 2047)]) * fTemp82))) + (0.0416666679f * (fTemp83 * fRec35[((IOTA - (iTemp84 + 1)) & 2047)])))));
			fRec60[0] = fRec33[1];
			fRec61[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec60[2]) + (0.100000001f * (fRec60[1] + fRec60[3])))));
			int iRec62 = 0;
			float fTemp85 = (fConst6 * fTemp58);
			float fTemp86 = (fTemp85 + -1.49999499f);
			int iTemp87 = (int)fTemp86;
			int iTemp88 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp87));
			float fTemp89 = (float)java.lang.Math.floor(fTemp86);
			float fTemp90 = (fTemp85 + (-1.0f - fTemp89));
			float fTemp91 = (0.0f - fTemp90);
			float fTemp92 = (fTemp85 + (-2.0f - fTemp89));
			float fTemp93 = (0.0f - (0.5f * fTemp92));
			float fTemp94 = (fTemp85 + (-3.0f - fTemp89));
			float fTemp95 = (0.0f - (0.333333343f * fTemp94));
			float fTemp96 = (fTemp85 + (-4.0f - fTemp89));
			float fTemp97 = (0.0f - (0.25f * fTemp96));
			float fTemp98 = (fTemp85 - fTemp89);
			int iTemp99 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp87 + 2)));
			float fTemp100 = (0.0f - fTemp94);
			float fTemp101 = (0.0f - (0.5f * fTemp96));
			int iTemp102 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp87 + 1)));
			float fTemp103 = (0.0f - fTemp92);
			float fTemp104 = (0.0f - (0.5f * fTemp94));
			float fTemp105 = (0.0f - (0.333333343f * fTemp96));
			float fTemp106 = (fTemp90 * fTemp92);
			int iTemp107 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp87 + 3)));
			float fTemp108 = (0.0f - fTemp96);
			float fTemp109 = (fTemp106 * fTemp94);
			int iTemp110 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp87 + 4)));
			fVec2[0] = (((((fRec61[((IOTA - (iTemp88 + 2)) & 2047)] * fTemp91) * fTemp93) * fTemp95) * fTemp97) + (fTemp98 * ((((0.5f * (((fTemp90 * fRec61[((IOTA - (iTemp99 + 2)) & 2047)]) * fTemp100) * fTemp101)) + (((fRec61[((IOTA - (iTemp102 + 2)) & 2047)] * fTemp103) * fTemp104) * fTemp105)) + (0.166666672f * ((fTemp106 * fRec61[((IOTA - (iTemp107 + 2)) & 2047)]) * fTemp108))) + (0.0416666679f * (fTemp109 * fRec61[((IOTA - (iTemp110 + 2)) & 2047)])))));
			float fTemp111 = (((float)iSlow5 * fRec27[0]) - (fRec55[1] + fVec2[1]));
			float fTemp112 = (fTemp111 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((fTemp54 * fTemp111)) + 0.75f)))));
			float fRec56 = (fRec55[1] + fTemp112);
			float fTemp113 = (fVec2[1] + fTemp112);
			fVec3[(IOTA & 2047)] = fTemp113;
			float fRec57 = (((((fTemp65 * fTemp67) * fTemp69) * fTemp71) * fVec3[((IOTA - iTemp62) & 2047)]) + (fTemp72 * ((0.0416666679f * (fTemp83 * fVec3[((IOTA - iTemp84) & 2047)])) + (((((fTemp77 * fTemp78) * fTemp79) * fVec3[((IOTA - iTemp76) & 2047)]) + (0.5f * (((fTemp64 * fTemp74) * fTemp75) * fVec3[((IOTA - iTemp73) & 2047)]))) + (0.166666672f * ((fTemp80 * fTemp82) * fVec3[((IOTA - iTemp81) & 2047)]))))));
			int iRec58 = iRec62;
			fRec51[(IOTA & 2047)] = fRec56;
			float fRec52 = (((((fTemp91 * fTemp93) * fTemp95) * fTemp97) * fRec51[((IOTA - (iTemp88 + 1)) & 2047)]) + (fTemp98 * (((0.166666672f * ((fTemp106 * fTemp108) * fRec51[((IOTA - (iTemp107 + 1)) & 2047)])) + ((((fTemp103 * fTemp104) * fTemp105) * fRec51[((IOTA - (iTemp102 + 1)) & 2047)]) + (0.5f * (((fTemp90 * fTemp100) * fTemp101) * fRec51[((IOTA - (iTemp99 + 1)) & 2047)])))) + (0.0416666679f * (fTemp109 * fRec51[((IOTA - (iTemp110 + 1)) & 2047)])))));
			fRec53[0] = fRec57;
			int iRec54 = iRec58;
			fRec49[0] = fRec53[1];
			int iRec50 = iRec54;
			fRec47[0] = (fRec49[1] - (fConst3 * ((fConst8 * fRec47[1]) + (fConst7 * fRec47[2]))));
			float fTemp114 = (fConst3 * ((fConst2 * fRec47[0]) + (fConst9 * fRec47[2])));
			float fRec45 = fTemp114;
			float fRec46 = ((float)iRec50 + fTemp114);
			iRec39[0] = iRec44;
			float fRec40 = fRec48;
			float fRec41 = fRec45;
			float fRec42 = fRec46;
			fRec35[(IOTA & 2047)] = fRec40;
			float fRec36 = fRec52;
			float fRec37 = fRec41;
			float fRec38 = fRec42;
			fRec33[0] = fRec36;
			float fRec34 = fRec38;
			iRec73[0] = 0;
			int iRec74 = iRec73[1];
			float fRec78 = ((float)iRec69[1] - (0.989264667f * ((0.600000024f * fRec79[2]) + (0.200000003f * (fRec79[1] + fRec79[3])))));
			fRec89[0] = (fSlow6 + (0.999000013f * fRec89[1]));
			float fTemp115 = (fRec89[0] + -0.0799999982f);
			float fTemp116 = (fConst5 * fTemp115);
			float fTemp117 = (fTemp116 + -1.49999499f);
			int iTemp118 = (int)fTemp117;
			int iTemp119 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp118));
			float fTemp120 = (float)java.lang.Math.floor(fTemp117);
			float fTemp121 = (fTemp116 + (-1.0f - fTemp120));
			float fTemp122 = (0.0f - fTemp121);
			float fTemp123 = (fTemp116 + (-2.0f - fTemp120));
			float fTemp124 = (0.0f - (0.5f * fTemp123));
			float fTemp125 = (fTemp116 + (-3.0f - fTemp120));
			float fTemp126 = (0.0f - (0.333333343f * fTemp125));
			float fTemp127 = (fTemp116 + (-4.0f - fTemp120));
			float fTemp128 = (0.0f - (0.25f * fTemp127));
			float fTemp129 = (fTemp116 - fTemp120);
			int iTemp130 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp118 + 2)));
			float fTemp131 = (0.0f - fTemp125);
			float fTemp132 = (0.0f - (0.5f * fTemp127));
			int iTemp133 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp118 + 1)));
			float fTemp134 = (0.0f - fTemp123);
			float fTemp135 = (0.0f - (0.5f * fTemp125));
			float fTemp136 = (0.0f - (0.333333343f * fTemp127));
			float fTemp137 = (fTemp121 * fTemp123);
			int iTemp138 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp118 + 3)));
			float fTemp139 = (0.0f - fTemp127);
			float fTemp140 = (fTemp137 * fTemp125);
			int iTemp141 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp118 + 4)));
			fRec85[0] = (((((fRec65[((IOTA - (iTemp119 + 1)) & 2047)] * fTemp122) * fTemp124) * fTemp126) * fTemp128) + (fTemp129 * ((((0.5f * (((fTemp121 * fRec65[((IOTA - (iTemp130 + 1)) & 2047)]) * fTemp131) * fTemp132)) + (((fRec65[((IOTA - (iTemp133 + 1)) & 2047)] * fTemp134) * fTemp135) * fTemp136)) + (0.166666672f * ((fTemp137 * fRec65[((IOTA - (iTemp138 + 1)) & 2047)]) * fTemp139))) + (0.0416666679f * (fTemp140 * fRec65[((IOTA - (iTemp141 + 1)) & 2047)])))));
			fRec90[0] = fRec63[1];
			fRec91[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec90[2]) + (0.100000001f * (fRec90[1] + fRec90[3])))));
			int iRec92 = 0;
			float fTemp142 = (fConst6 * fTemp115);
			float fTemp143 = (fTemp142 + -1.49999499f);
			int iTemp144 = (int)fTemp143;
			int iTemp145 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp144));
			float fTemp146 = (float)java.lang.Math.floor(fTemp143);
			float fTemp147 = (fTemp142 + (-1.0f - fTemp146));
			float fTemp148 = (0.0f - fTemp147);
			float fTemp149 = (fTemp142 + (-2.0f - fTemp146));
			float fTemp150 = (0.0f - (0.5f * fTemp149));
			float fTemp151 = (fTemp142 + (-3.0f - fTemp146));
			float fTemp152 = (0.0f - (0.333333343f * fTemp151));
			float fTemp153 = (fTemp142 + (-4.0f - fTemp146));
			float fTemp154 = (0.0f - (0.25f * fTemp153));
			float fTemp155 = (fTemp142 - fTemp146);
			int iTemp156 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp144 + 2)));
			float fTemp157 = (0.0f - fTemp151);
			float fTemp158 = (0.0f - (0.5f * fTemp153));
			int iTemp159 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp144 + 1)));
			float fTemp160 = (0.0f - fTemp149);
			float fTemp161 = (0.0f - (0.5f * fTemp151));
			float fTemp162 = (0.0f - (0.333333343f * fTemp153));
			float fTemp163 = (fTemp147 * fTemp149);
			int iTemp164 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp144 + 3)));
			float fTemp165 = (0.0f - fTemp153);
			float fTemp166 = (fTemp163 * fTemp151);
			int iTemp167 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp144 + 4)));
			fVec4[0] = (((((fRec91[((IOTA - (iTemp145 + 2)) & 2047)] * fTemp148) * fTemp150) * fTemp152) * fTemp154) + (fTemp155 * ((((0.5f * (((fTemp147 * fRec91[((IOTA - (iTemp156 + 2)) & 2047)]) * fTemp157) * fTemp158)) + (((fRec91[((IOTA - (iTemp159 + 2)) & 2047)] * fTemp160) * fTemp161) * fTemp162)) + (0.166666672f * ((fTemp163 * fRec91[((IOTA - (iTemp164 + 2)) & 2047)]) * fTemp165))) + (0.0416666679f * (fTemp166 * fRec91[((IOTA - (iTemp167 + 2)) & 2047)])))));
			float fTemp168 = (((float)iSlow7 * fRec27[0]) - (fRec85[1] + fVec4[1]));
			float fTemp169 = (fTemp168 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((fTemp54 * fTemp168)) + 0.75f)))));
			float fRec86 = (fRec85[1] + fTemp169);
			float fTemp170 = (fVec4[1] + fTemp169);
			fVec5[(IOTA & 2047)] = fTemp170;
			float fRec87 = (((((fTemp122 * fTemp124) * fTemp126) * fTemp128) * fVec5[((IOTA - iTemp119) & 2047)]) + (fTemp129 * ((0.0416666679f * (fTemp140 * fVec5[((IOTA - iTemp141) & 2047)])) + (((((fTemp134 * fTemp135) * fTemp136) * fVec5[((IOTA - iTemp133) & 2047)]) + (0.5f * (((fTemp121 * fTemp131) * fTemp132) * fVec5[((IOTA - iTemp130) & 2047)]))) + (0.166666672f * ((fTemp137 * fTemp139) * fVec5[((IOTA - iTemp138) & 2047)]))))));
			int iRec88 = iRec92;
			fRec81[(IOTA & 2047)] = fRec86;
			float fRec82 = (((((fTemp148 * fTemp150) * fTemp152) * fTemp154) * fRec81[((IOTA - (iTemp145 + 1)) & 2047)]) + (fTemp155 * (((0.166666672f * ((fTemp163 * fTemp165) * fRec81[((IOTA - (iTemp164 + 1)) & 2047)])) + ((((fTemp160 * fTemp161) * fTemp162) * fRec81[((IOTA - (iTemp159 + 1)) & 2047)]) + (0.5f * (((fTemp147 * fTemp157) * fTemp158) * fRec81[((IOTA - (iTemp156 + 1)) & 2047)])))) + (0.0416666679f * (fTemp166 * fRec81[((IOTA - (iTemp167 + 1)) & 2047)])))));
			fRec83[0] = fRec87;
			int iRec84 = iRec88;
			fRec79[0] = fRec83[1];
			int iRec80 = iRec84;
			fRec77[0] = (fRec79[1] - (fConst3 * ((fConst8 * fRec77[1]) + (fConst7 * fRec77[2]))));
			float fTemp171 = (fConst3 * ((fConst2 * fRec77[0]) + (fConst9 * fRec77[2])));
			float fRec75 = fTemp171;
			float fRec76 = ((float)iRec80 + fTemp171);
			iRec69[0] = iRec74;
			float fRec70 = fRec78;
			float fRec71 = fRec75;
			float fRec72 = fRec76;
			fRec65[(IOTA & 2047)] = fRec70;
			float fRec66 = fRec82;
			float fRec67 = fRec71;
			float fRec68 = fRec72;
			fRec63[0] = fRec66;
			float fRec64 = fRec68;
			iRec103[0] = 0;
			int iRec104 = iRec103[1];
			float fRec108 = ((float)iRec99[1] - (0.989264667f * ((0.600000024f * fRec109[2]) + (0.200000003f * (fRec109[1] + fRec109[3])))));
			fRec119[0] = (fSlow8 + (0.999000013f * fRec119[1]));
			float fTemp172 = (fRec119[0] + -0.0799999982f);
			float fTemp173 = (fConst5 * fTemp172);
			float fTemp174 = (fTemp173 + -1.49999499f);
			int iTemp175 = (int)fTemp174;
			int iTemp176 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp175));
			float fTemp177 = (float)java.lang.Math.floor(fTemp174);
			float fTemp178 = (fTemp173 + (-1.0f - fTemp177));
			float fTemp179 = (0.0f - fTemp178);
			float fTemp180 = (fTemp173 + (-2.0f - fTemp177));
			float fTemp181 = (0.0f - (0.5f * fTemp180));
			float fTemp182 = (fTemp173 + (-3.0f - fTemp177));
			float fTemp183 = (0.0f - (0.333333343f * fTemp182));
			float fTemp184 = (fTemp173 + (-4.0f - fTemp177));
			float fTemp185 = (0.0f - (0.25f * fTemp184));
			float fTemp186 = (fTemp173 - fTemp177);
			int iTemp187 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp175 + 2)));
			float fTemp188 = (0.0f - fTemp182);
			float fTemp189 = (0.0f - (0.5f * fTemp184));
			int iTemp190 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp175 + 1)));
			float fTemp191 = (0.0f - fTemp180);
			float fTemp192 = (0.0f - (0.5f * fTemp182));
			float fTemp193 = (0.0f - (0.333333343f * fTemp184));
			float fTemp194 = (fTemp178 * fTemp180);
			int iTemp195 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp175 + 3)));
			float fTemp196 = (0.0f - fTemp184);
			float fTemp197 = (fTemp194 * fTemp182);
			int iTemp198 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp175 + 4)));
			fRec115[0] = (((((fRec95[((IOTA - (iTemp176 + 1)) & 2047)] * fTemp179) * fTemp181) * fTemp183) * fTemp185) + (fTemp186 * ((((0.5f * (((fTemp178 * fRec95[((IOTA - (iTemp187 + 1)) & 2047)]) * fTemp188) * fTemp189)) + (((fRec95[((IOTA - (iTemp190 + 1)) & 2047)] * fTemp191) * fTemp192) * fTemp193)) + (0.166666672f * ((fTemp194 * fRec95[((IOTA - (iTemp195 + 1)) & 2047)]) * fTemp196))) + (0.0416666679f * (fTemp197 * fRec95[((IOTA - (iTemp198 + 1)) & 2047)])))));
			fRec120[0] = fRec93[1];
			fRec121[(IOTA & 2047)] = (0.0f - (0.99880147f * ((0.800000012f * fRec120[2]) + (0.100000001f * (fRec120[1] + fRec120[3])))));
			int iRec122 = 0;
			float fTemp199 = (fConst6 * fTemp172);
			float fTemp200 = (fTemp199 + -1.49999499f);
			int iTemp201 = (int)fTemp200;
			int iTemp202 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, iTemp201));
			float fTemp203 = (float)java.lang.Math.floor(fTemp200);
			float fTemp204 = (fTemp199 + (-1.0f - fTemp203));
			float fTemp205 = (0.0f - fTemp204);
			float fTemp206 = (fTemp199 + (-2.0f - fTemp203));
			float fTemp207 = (0.0f - (0.5f * fTemp206));
			float fTemp208 = (fTemp199 + (-3.0f - fTemp203));
			float fTemp209 = (0.0f - (0.333333343f * fTemp208));
			float fTemp210 = (fTemp199 + (-4.0f - fTemp203));
			float fTemp211 = (0.0f - (0.25f * fTemp210));
			float fTemp212 = (fTemp199 - fTemp203);
			int iTemp213 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp201 + 2)));
			float fTemp214 = (0.0f - fTemp208);
			float fTemp215 = (0.0f - (0.5f * fTemp210));
			int iTemp216 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp201 + 1)));
			float fTemp217 = (0.0f - fTemp206);
			float fTemp218 = (0.0f - (0.5f * fTemp208));
			float fTemp219 = (0.0f - (0.333333343f * fTemp210));
			float fTemp220 = (fTemp204 * fTemp206);
			int iTemp221 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp201 + 3)));
			float fTemp222 = (0.0f - fTemp210);
			int iTemp223 = (int)(float)java.lang.Math.min(fConst4, (float)java.lang.Math.max(0, (iTemp201 + 4)));
			fVec6[0] = (((((fRec121[((IOTA - (iTemp202 + 2)) & 2047)] * fTemp205) * fTemp207) * fTemp209) * fTemp211) + (fTemp212 * ((((0.5f * (((fTemp204 * fRec121[((IOTA - (iTemp213 + 2)) & 2047)]) * fTemp214) * fTemp215)) + (((fRec121[((IOTA - (iTemp216 + 2)) & 2047)] * fTemp217) * fTemp218) * fTemp219)) + (0.166666672f * ((fTemp220 * fRec121[((IOTA - (iTemp221 + 2)) & 2047)]) * fTemp222))) + (0.0416666679f * ((fTemp220 * fTemp208) * fRec121[((IOTA - (iTemp223 + 2)) & 2047)])))));
			float fTemp224 = (((float)iSlow9 * fRec27[0]) - (fRec115[1] + fVec6[1]));
			float fTemp225 = (fTemp224 * (float)java.lang.Math.min(1.0f, (1.0f / mydsp_faustpower4_f(((float)java.lang.Math.abs((fTemp54 * fTemp224)) + 0.75f)))));
			float fRec116 = (fRec115[1] + fTemp225);
			float fTemp226 = (fVec6[1] + fTemp225);
			fVec7[(IOTA & 2047)] = fTemp226;
			float fRec117 = (((((fTemp179 * fTemp181) * fTemp183) * fTemp185) * fVec7[((IOTA - iTemp176) & 2047)]) + (fTemp186 * ((0.0416666679f * (fTemp197 * fVec7[((IOTA - iTemp198) & 2047)])) + (((((fTemp191 * fTemp192) * fTemp193) * fVec7[((IOTA - iTemp190) & 2047)]) + (0.5f * (((fTemp178 * fTemp188) * fTemp189) * fVec7[((IOTA - iTemp187) & 2047)]))) + (0.166666672f * ((fTemp194 * fTemp196) * fVec7[((IOTA - iTemp195) & 2047)]))))));
			int iRec118 = iRec122;
			fRec111[(IOTA & 2047)] = fRec116;
			float fRec112 = (((((fTemp205 * fTemp207) * fTemp209) * fTemp211) * fRec111[((IOTA - (iTemp202 + 1)) & 2047)]) + (fTemp212 * (((0.166666672f * ((fTemp220 * fTemp222) * fRec111[((IOTA - (iTemp221 + 1)) & 2047)])) + ((((fTemp217 * fTemp218) * fTemp219) * fRec111[((IOTA - (iTemp216 + 1)) & 2047)]) + (0.5f * (((fTemp204 * fTemp214) * fTemp215) * fRec111[((IOTA - (iTemp213 + 1)) & 2047)])))) + (0.0416666679f * (((fRec111[((IOTA - (iTemp223 + 1)) & 2047)] * fTemp204) * fTemp206) * fTemp208)))));
			fRec113[0] = fRec117;
			int iRec114 = iRec118;
			fRec109[0] = fRec113[1];
			int iRec110 = iRec114;
			fRec107[0] = (fRec109[1] - (fConst3 * ((fConst8 * fRec107[1]) + (fConst7 * fRec107[2]))));
			float fTemp227 = (fConst3 * ((fConst2 * fRec107[0]) + (fConst9 * fRec107[2])));
			float fRec105 = fTemp227;
			float fRec106 = ((float)iRec110 + fTemp227);
			iRec99[0] = iRec104;
			float fRec100 = fRec108;
			float fRec101 = fRec105;
			float fRec102 = fRec106;
			fRec95[(IOTA & 2047)] = fRec100;
			float fRec96 = fRec112;
			float fRec97 = fRec101;
			float fRec98 = fRec102;
			fRec93[0] = fRec96;
			float fRec94 = fRec98;
			float fTemp228 = (((fRec1 + fRec34) + fRec64) + fRec94);
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
			fRec32[1] = fRec32[0];
			fRec20[1] = fRec20[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec16[j1] = fRec16[(j1 - 1)];
				
			}
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
			iRec43[1] = iRec43[0];
			fRec59[1] = fRec59[0];
			fRec55[1] = fRec55[0];
			for (int j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
				fRec60[j2] = fRec60[(j2 - 1)];
				
			}
			fVec2[1] = fVec2[0];
			fRec53[1] = fRec53[0];
			for (int j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
				fRec49[j3] = fRec49[(j3 - 1)];
				
			}
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			iRec39[1] = iRec39[0];
			fRec33[1] = fRec33[0];
			iRec73[1] = iRec73[0];
			fRec89[1] = fRec89[0];
			fRec85[1] = fRec85[0];
			for (int j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
				fRec90[j4] = fRec90[(j4 - 1)];
				
			}
			fVec4[1] = fVec4[0];
			fRec83[1] = fRec83[0];
			for (int j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
				fRec79[j5] = fRec79[(j5 - 1)];
				
			}
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			iRec69[1] = iRec69[0];
			fRec63[1] = fRec63[0];
			iRec103[1] = iRec103[0];
			fRec119[1] = fRec119[0];
			fRec115[1] = fRec115[0];
			for (int j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
				fRec120[j6] = fRec120[(j6 - 1)];
				
			}
			fVec6[1] = fVec6[0];
			fRec113[1] = fRec113[0];
			for (int j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
				fRec109[j7] = fRec109[(j7 - 1)];
				
			}
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			iRec99[1] = iRec99[0];
			fRec93[1] = fRec93[0];
			
		}
		
	}
	
};

