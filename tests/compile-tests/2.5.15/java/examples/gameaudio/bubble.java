/* ------------------------------------------------------------
copyright: "(c) 2017: Yann Orlarey, GRAME"
license: "MIT"
name: "bubble"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fVslider0;
	float fConst2;
	float fVslider1;
	int iVec0[] = new int[2];
	float fRec9[] = new float[2];
	float fVslider2;
	float fConst3;
	float fHslider0;
	float fConst4;
	float fButton0;
	float fVec1[] = new float[2];
	int iRec12[] = new int[2];
	float fRec10[] = new float[2];
	float fRec11[] = new float[2];
	float fConst5;
	float fRec13[] = new float[2];
	int IOTA;
	float fVec2[] = new float[8192];
	int iConst6;
	float fRec8[] = new float[2];
	float fRec15[] = new float[2];
	float fVec3[] = new float[8192];
	int iConst7;
	float fRec14[] = new float[2];
	float fRec17[] = new float[2];
	float fVec4[] = new float[8192];
	int iConst8;
	float fRec16[] = new float[2];
	float fRec19[] = new float[2];
	float fVec5[] = new float[8192];
	int iConst9;
	float fRec18[] = new float[2];
	float fRec21[] = new float[2];
	float fVec6[] = new float[8192];
	int iConst10;
	float fRec20[] = new float[2];
	float fRec23[] = new float[2];
	float fVec7[] = new float[8192];
	int iConst11;
	float fRec22[] = new float[2];
	float fRec25[] = new float[2];
	float fVec8[] = new float[8192];
	int iConst12;
	float fRec24[] = new float[2];
	float fRec27[] = new float[2];
	float fVec9[] = new float[8192];
	int iConst13;
	float fRec26[] = new float[2];
	float fVec10[] = new float[2048];
	int iConst14;
	int iConst15;
	float fRec6[] = new float[2];
	float fVec11[] = new float[2048];
	int iConst16;
	int iConst17;
	float fRec4[] = new float[2];
	float fVec12[] = new float[2048];
	int iConst18;
	int iConst19;
	float fRec2[] = new float[2];
	float fVec13[] = new float[1024];
	int iConst20;
	int iConst21;
	float fRec0[] = new float[2];
	float fRec37[] = new float[2];
	float fVec14[] = new float[8192];
	float fConst22;
	float fVslider3;
	float fRec36[] = new float[2];
	float fRec39[] = new float[2];
	float fVec15[] = new float[8192];
	float fRec38[] = new float[2];
	float fRec41[] = new float[2];
	float fVec16[] = new float[8192];
	float fRec40[] = new float[2];
	float fRec43[] = new float[2];
	float fVec17[] = new float[8192];
	float fRec42[] = new float[2];
	float fRec45[] = new float[2];
	float fVec18[] = new float[8192];
	float fRec44[] = new float[2];
	float fRec47[] = new float[2];
	float fVec19[] = new float[8192];
	float fRec46[] = new float[2];
	float fRec49[] = new float[2];
	float fVec20[] = new float[8192];
	float fRec48[] = new float[2];
	float fRec51[] = new float[2];
	float fVec21[] = new float[8192];
	float fRec50[] = new float[2];
	float fVec22[] = new float[2048];
	float fRec34[] = new float[2];
	float fVec23[] = new float[2048];
	float fRec32[] = new float[2];
	float fVec24[] = new float[2048];
	float fRec30[] = new float[2];
	float fVec25[] = new float[2048];
	float fRec28[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c) 2017: Yann Orlarey, GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Production of a water drop bubble sound.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "bubble");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
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
		fConst1 = (12348.0f / fConst0);
		fConst2 = (17640.0f / fConst0);
		fConst3 = (6.28318548f / fConst0);
		fConst4 = (0.075000003f / fConst0);
		fConst5 = (1.0f / fConst0);
		iConst6 = (int)(0.0253061224f * fConst0);
		iConst7 = (int)(0.0269387756f * fConst0);
		iConst8 = (int)(0.0289569162f * fConst0);
		iConst9 = (int)(0.0307482984f * fConst0);
		iConst10 = (int)(0.0322448984f * fConst0);
		iConst11 = (int)(0.033809524f * fConst0);
		iConst12 = (int)(0.0353061222f * fConst0);
		iConst13 = (int)(0.0366666652f * fConst0);
		iConst14 = (int)(0.0126077095f * fConst0);
		iConst15 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst14 + -1)));
		iConst16 = (int)(0.00999999978f * fConst0);
		iConst17 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst16 + -1)));
		iConst18 = (int)(0.00773242628f * fConst0);
		iConst19 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst18 + -1)));
		iConst20 = (int)(0.00510204071f * fConst0);
		iConst21 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst20 + -1)));
		fConst22 = (0.00104308384f * fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fVslider0 = (float)0.5f;
		fVslider1 = (float)0.5f;
		fVslider2 = (float)0.33329999999999999f;
		fHslider0 = (float)600.0f;
		fButton0 = (float)0.0f;
		fVslider3 = (float)0.5f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec9[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec12[l3] = 0;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec10[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec11[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec13[l6] = 0.0f;
			
		}
		IOTA = 0;
		for (int l7 = 0; (l7 < 8192); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec15[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 8192); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec14[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec17[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 8192); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec19[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 8192); l16 = (l16 + 1)) {
			fVec5[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec18[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec21[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 8192); l19 = (l19 + 1)) {
			fVec6[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec20[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec23[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 8192); l22 = (l22 + 1)) {
			fVec7[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec22[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec25[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 8192); l25 = (l25 + 1)) {
			fVec8[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec24[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec27[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 8192); l28 = (l28 + 1)) {
			fVec9[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec26[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2048); l30 = (l30 + 1)) {
			fVec10[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec6[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2048); l32 = (l32 + 1)) {
			fVec11[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec4[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2048); l34 = (l34 + 1)) {
			fVec12[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec2[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 1024); l36 = (l36 + 1)) {
			fVec13[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec0[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec37[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 8192); l39 = (l39 + 1)) {
			fVec14[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec36[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec39[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 8192); l42 = (l42 + 1)) {
			fVec15[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec38[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec41[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 8192); l45 = (l45 + 1)) {
			fVec16[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec40[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec43[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 8192); l48 = (l48 + 1)) {
			fVec17[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec42[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec45[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 8192); l51 = (l51 + 1)) {
			fVec18[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec44[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec47[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 8192); l54 = (l54 + 1)) {
			fVec19[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec46[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec49[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 8192); l57 = (l57 + 1)) {
			fVec20[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec48[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec51[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 8192); l60 = (l60 + 1)) {
			fVec21[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec50[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			fVec22[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec34[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2048); l64 = (l64 + 1)) {
			fVec23[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec32[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2048); l66 = (l66 + 1)) {
			fVec24[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec30[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2048); l68 = (l68 + 1)) {
			fVec25[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec28[l69] = 0.0f;
			
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
		ui_interface.openVerticalBox("bubble");
		ui_interface.openHorizontalBox("Freeverb");
		ui_interface.declare("0", "0", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("fVslider1", "0", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "Somehow control the   density of the reverb.");
		ui_interface.addVerticalSlider("Damp", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "The room size   between 0 and 1 with 1 for the largest room.");
		ui_interface.addVerticalSlider("RoomSize", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		ui_interface.declare("fVslider3", "2", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Spatial   spread between 0 and 1 with 1 for maximum spread.");
		ui_interface.addVerticalSlider("Stereo Spread", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.declare("fVslider2", "tooltip", "The amount of reverb applied to the signal   between 0 and 1 with 1 for the maximum amount of reverb.");
		ui_interface.addVerticalSlider("Wet", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 0.333299994f, 0.0f, 1.0f, 0.0250000004f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("bubble");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 600.0f, 150.0f, 2000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.addButton("drop", new FaustVarAccess() {
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
		float fSlow0 = ((fConst1 * fVslider0) + 0.699999988f);
		float fSlow1 = (fConst2 * fVslider1);
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = fVslider2;
		float fSlow4 = (0.200000003f * fSlow3);
		float fSlow5 = fHslider0;
		float fSlow6 = (fConst3 * fSlow5);
		float fSlow7 = ((0.0430000015f * fSlow5) + (0.00139999995f * (float)java.lang.Math.pow(fSlow5, 1.5f)));
		float fSlow8 = (fConst4 * fSlow7);
		float fSlow9 = fButton0;
		float fSlow10 = (fConst5 * (0.0f - fSlow7));
		float fSlow11 = (1.0f - fSlow3);
		int iSlow12 = (int)(fConst22 * fVslider3);
		int iSlow13 = (iConst6 + iSlow12);
		int iSlow14 = (iConst7 + iSlow12);
		int iSlow15 = (iConst8 + iSlow12);
		int iSlow16 = (iConst9 + iSlow12);
		int iSlow17 = (iConst10 + iSlow12);
		int iSlow18 = (iConst11 + iSlow12);
		int iSlow19 = (iConst12 + iSlow12);
		int iSlow20 = (iConst13 + iSlow12);
		int iSlow21 = (iSlow12 + -1);
		int iSlow22 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst14 + iSlow21)));
		int iSlow23 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst16 + iSlow21)));
		int iSlow24 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst18 + iSlow21)));
		int iSlow25 = java.lang.Math.min(1024, java.lang.Math.max(0, (iConst20 + iSlow21)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec9[0] = ((fSlow1 * fRec9[1]) + (fSlow2 * fRec8[1]));
			fVec1[0] = fSlow9;
			iRec12[0] = ((((fSlow9 > fVec1[1]))?0:iRec12[1]) + 1);
			float fTemp0 = (fSlow6 * ((fSlow8 * (float)iRec12[0]) + 1.0f));
			float fTemp1 = (float)java.lang.Math.sin(fTemp0);
			float fTemp2 = (float)java.lang.Math.cos(fTemp0);
			fRec10[0] = ((fRec11[1] * fTemp1) + (fRec10[1] * fTemp2));
			fRec11[0] = (((fRec11[1] * fTemp2) + (fRec10[1] * (0.0f - fTemp1))) + (float)(1 - iVec0[1]));
			fRec13[0] = ((0.99000001f * fRec13[1]) + (0.00999999978f * (float)java.lang.Math.exp((fSlow10 * (float)iRec12[0]))));
			float fTemp3 = (fRec10[0] * fRec13[0]);
			float fTemp4 = (fSlow4 * fTemp3);
			fVec2[(IOTA & 8191)] = ((fSlow0 * fRec9[0]) + fTemp4);
			fRec8[0] = fVec2[((IOTA - iConst6) & 8191)];
			fRec15[0] = ((fSlow1 * fRec15[1]) + (fSlow2 * fRec14[1]));
			fVec3[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec15[0]));
			fRec14[0] = fVec3[((IOTA - iConst7) & 8191)];
			fRec17[0] = ((fSlow1 * fRec17[1]) + (fSlow2 * fRec16[1]));
			fVec4[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec17[0]));
			fRec16[0] = fVec4[((IOTA - iConst8) & 8191)];
			fRec19[0] = ((fSlow1 * fRec19[1]) + (fSlow2 * fRec18[1]));
			fVec5[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec19[0]));
			fRec18[0] = fVec5[((IOTA - iConst9) & 8191)];
			fRec21[0] = ((fSlow1 * fRec21[1]) + (fSlow2 * fRec20[1]));
			fVec6[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec21[0]));
			fRec20[0] = fVec6[((IOTA - iConst10) & 8191)];
			fRec23[0] = ((fSlow1 * fRec23[1]) + (fSlow2 * fRec22[1]));
			fVec7[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec23[0]));
			fRec22[0] = fVec7[((IOTA - iConst11) & 8191)];
			fRec25[0] = ((fSlow1 * fRec25[1]) + (fSlow2 * fRec24[1]));
			fVec8[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec25[0]));
			fRec24[0] = fVec8[((IOTA - iConst12) & 8191)];
			fRec27[0] = ((fSlow1 * fRec27[1]) + (fSlow2 * fRec26[1]));
			fVec9[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec27[0]));
			fRec26[0] = fVec9[((IOTA - iConst13) & 8191)];
			float fTemp5 = ((((((((fRec8[0] + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]) + fRec24[0]) + fRec26[0]) + (0.5f * fRec6[1]));
			fVec10[(IOTA & 2047)] = fTemp5;
			fRec6[0] = fVec10[((IOTA - iConst15) & 2047)];
			float fRec7 = (0.0f - (0.5f * fTemp5));
			float fTemp6 = (fRec6[1] + (fRec7 + (0.5f * fRec4[1])));
			fVec11[(IOTA & 2047)] = fTemp6;
			fRec4[0] = fVec11[((IOTA - iConst17) & 2047)];
			float fRec5 = (0.0f - (0.5f * fTemp6));
			float fTemp7 = (fRec4[1] + (fRec5 + (0.5f * fRec2[1])));
			fVec12[(IOTA & 2047)] = fTemp7;
			fRec2[0] = fVec12[((IOTA - iConst19) & 2047)];
			float fRec3 = (0.0f - (0.5f * fTemp7));
			float fTemp8 = (fRec2[1] + (fRec3 + (0.5f * fRec0[1])));
			fVec13[(IOTA & 1023)] = fTemp8;
			fRec0[0] = fVec13[((IOTA - iConst21) & 1023)];
			float fRec1 = (0.0f - (0.5f * fTemp8));
			float fTemp9 = (fSlow11 * fTemp3);
			output0[i] = ((fRec1 + fRec0[1]) + fTemp9);
			fRec37[0] = ((fSlow1 * fRec37[1]) + (fSlow2 * fRec36[1]));
			fVec14[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec37[0]));
			fRec36[0] = fVec14[((IOTA - iSlow13) & 8191)];
			fRec39[0] = ((fSlow1 * fRec39[1]) + (fSlow2 * fRec38[1]));
			fVec15[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec39[0]));
			fRec38[0] = fVec15[((IOTA - iSlow14) & 8191)];
			fRec41[0] = ((fSlow1 * fRec41[1]) + (fSlow2 * fRec40[1]));
			fVec16[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec41[0]));
			fRec40[0] = fVec16[((IOTA - iSlow15) & 8191)];
			fRec43[0] = ((fSlow1 * fRec43[1]) + (fSlow2 * fRec42[1]));
			fVec17[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec43[0]));
			fRec42[0] = fVec17[((IOTA - iSlow16) & 8191)];
			fRec45[0] = ((fSlow1 * fRec45[1]) + (fSlow2 * fRec44[1]));
			fVec18[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec45[0]));
			fRec44[0] = fVec18[((IOTA - iSlow17) & 8191)];
			fRec47[0] = ((fSlow1 * fRec47[1]) + (fSlow2 * fRec46[1]));
			fVec19[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec47[0]));
			fRec46[0] = fVec19[((IOTA - iSlow18) & 8191)];
			fRec49[0] = ((fSlow1 * fRec49[1]) + (fSlow2 * fRec48[1]));
			fVec20[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec49[0]));
			fRec48[0] = fVec20[((IOTA - iSlow19) & 8191)];
			fRec51[0] = ((fSlow1 * fRec51[1]) + (fSlow2 * fRec50[1]));
			fVec21[(IOTA & 8191)] = (fTemp4 + (fSlow0 * fRec51[0]));
			fRec50[0] = fVec21[((IOTA - iSlow20) & 8191)];
			float fTemp10 = ((((((((fRec36[0] + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) + fRec46[0]) + fRec48[0]) + fRec50[0]) + (0.5f * fRec34[1]));
			fVec22[(IOTA & 2047)] = fTemp10;
			fRec34[0] = fVec22[((IOTA - iSlow22) & 2047)];
			float fRec35 = (0.0f - (0.5f * fTemp10));
			float fTemp11 = (fRec34[1] + (fRec35 + (0.5f * fRec32[1])));
			fVec23[(IOTA & 2047)] = fTemp11;
			fRec32[0] = fVec23[((IOTA - iSlow23) & 2047)];
			float fRec33 = (0.0f - (0.5f * fTemp11));
			float fTemp12 = (fRec32[1] + (fRec33 + (0.5f * fRec30[1])));
			fVec24[(IOTA & 2047)] = fTemp12;
			fRec30[0] = fVec24[((IOTA - iSlow24) & 2047)];
			float fRec31 = (0.0f - (0.5f * fTemp12));
			float fTemp13 = (fRec30[1] + (fRec31 + (0.5f * fRec28[1])));
			fVec25[(IOTA & 2047)] = fTemp13;
			fRec28[0] = fVec25[((IOTA - iSlow25) & 2047)];
			float fRec29 = (0.0f - (0.5f * fTemp13));
			output1[i] = (fRec28[1] + (fRec29 + fTemp9));
			iVec0[1] = iVec0[0];
			fRec9[1] = fRec9[0];
			fVec1[1] = fVec1[0];
			iRec12[1] = iRec12[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec41[1] = fRec41[0];
			fRec40[1] = fRec40[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			
		}
		
	}
	
};

