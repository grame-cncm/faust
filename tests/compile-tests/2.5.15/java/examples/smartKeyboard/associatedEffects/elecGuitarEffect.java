/* ------------------------------------------------------------
name: "elecGuitarEffect"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fVslider0;
	float fRec0[] = new float[2];
	float fVslider1;
	float fRec1[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fVslider2;
	float fVslider3;
	float fVslider4;
	float fVslider5;
	float fConst2;
	float fConst3;
	float fVslider6;
	float fConst4;
	float fVslider7;
	float fVslider8;
	float fConst5;
	float fVslider9;
	float fRec15[] = new float[2];
	float fRec14[] = new float[2];
	int IOTA;
	float fVec0[] = new float[32768];
	float fConst6;
	int iConst7;
	float fVec1[] = new float[16384];
	float fConst8;
	float fVslider10;
	float fVec2[] = new float[2048];
	int iConst9;
	float fRec12[] = new float[2];
	float fConst10;
	float fConst11;
	float fRec19[] = new float[2];
	float fRec18[] = new float[2];
	float fVec3[] = new float[32768];
	float fConst12;
	int iConst13;
	float fVec4[] = new float[4096];
	int iConst14;
	float fRec16[] = new float[2];
	float fConst15;
	float fConst16;
	float fRec23[] = new float[2];
	float fRec22[] = new float[2];
	float fVec5[] = new float[16384];
	float fConst17;
	int iConst18;
	float fVec6[] = new float[4096];
	int iConst19;
	float fRec20[] = new float[2];
	float fConst20;
	float fConst21;
	float fRec27[] = new float[2];
	float fRec26[] = new float[2];
	float fVec7[] = new float[32768];
	float fConst22;
	int iConst23;
	float fVec8[] = new float[4096];
	int iConst24;
	float fRec24[] = new float[2];
	float fConst25;
	float fConst26;
	float fRec31[] = new float[2];
	float fRec30[] = new float[2];
	float fVec9[] = new float[16384];
	float fConst27;
	int iConst28;
	float fVec10[] = new float[16384];
	float fVec11[] = new float[2048];
	int iConst29;
	float fRec28[] = new float[2];
	float fConst30;
	float fConst31;
	float fRec35[] = new float[2];
	float fRec34[] = new float[2];
	float fVec12[] = new float[16384];
	float fConst32;
	int iConst33;
	float fVec13[] = new float[4096];
	int iConst34;
	float fRec32[] = new float[2];
	float fConst35;
	float fConst36;
	float fRec39[] = new float[2];
	float fRec38[] = new float[2];
	float fVec14[] = new float[16384];
	float fConst37;
	int iConst38;
	float fVec15[] = new float[4096];
	int iConst39;
	float fRec36[] = new float[2];
	float fConst40;
	float fConst41;
	float fRec43[] = new float[2];
	float fRec42[] = new float[2];
	float fVec16[] = new float[16384];
	float fConst42;
	int iConst43;
	float fVec17[] = new float[2048];
	int iConst44;
	float fRec40[] = new float[2];
	float fRec4[] = new float[3];
	float fRec5[] = new float[3];
	float fRec6[] = new float[3];
	float fRec7[] = new float[3];
	float fRec8[] = new float[3];
	float fRec9[] = new float[3];
	float fRec10[] = new float[3];
	float fRec11[] = new float[3];
	float fRec3[] = new float[3];
	float fRec2[] = new float[3];
	float fRec45[] = new float[3];
	float fRec44[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "elecGuitarEffect");
		m.declare("reverbs.lib/name", "Faust Reverb Library");
		m.declare("reverbs.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	int getNumInputs() {
		return 2;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
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
		fConst2 = (float)java.lang.Math.floor(((0.219990999f * fConst0) + 0.5f));
		fConst3 = ((0.0f - (6.90775537f * fConst2)) / fConst0);
		fConst4 = (6.28318548f / fConst0);
		fConst5 = (3.14159274f / fConst0);
		fConst6 = (float)java.lang.Math.floor(((0.0191229992f * fConst0) + 0.5f));
		iConst7 = (int)(float)java.lang.Math.min(16384.0f, (float)java.lang.Math.max(0.0f, (fConst2 - fConst6)));
		fConst8 = (0.00100000005f * fConst0);
		iConst9 = (int)(float)java.lang.Math.min(1024.0f, (float)java.lang.Math.max(0.0f, (fConst6 + -1.0f)));
		fConst10 = (float)java.lang.Math.floor(((0.256891012f * fConst0) + 0.5f));
		fConst11 = ((0.0f - (6.90775537f * fConst10)) / fConst0);
		fConst12 = (float)java.lang.Math.floor(((0.0273330007f * fConst0) + 0.5f));
		iConst13 = (int)(float)java.lang.Math.min(16384.0f, (float)java.lang.Math.max(0.0f, (fConst10 - fConst12)));
		iConst14 = (int)(float)java.lang.Math.min(2048.0f, (float)java.lang.Math.max(0.0f, (fConst12 + -1.0f)));
		fConst15 = (float)java.lang.Math.floor(((0.192303002f * fConst0) + 0.5f));
		fConst16 = ((0.0f - (6.90775537f * fConst15)) / fConst0);
		fConst17 = (float)java.lang.Math.floor(((0.0292910002f * fConst0) + 0.5f));
		iConst18 = (int)(float)java.lang.Math.min(8192.0f, (float)java.lang.Math.max(0.0f, (fConst15 - fConst17)));
		iConst19 = (int)(float)java.lang.Math.min(2048.0f, (float)java.lang.Math.max(0.0f, (fConst17 + -1.0f)));
		fConst20 = (float)java.lang.Math.floor(((0.210389003f * fConst0) + 0.5f));
		fConst21 = ((0.0f - (6.90775537f * fConst20)) / fConst0);
		fConst22 = (float)java.lang.Math.floor(((0.0244210009f * fConst0) + 0.5f));
		iConst23 = (int)(float)java.lang.Math.min(16384.0f, (float)java.lang.Math.max(0.0f, (fConst20 - fConst22)));
		iConst24 = (int)(float)java.lang.Math.min(2048.0f, (float)java.lang.Math.max(0.0f, (fConst22 + -1.0f)));
		fConst25 = (float)java.lang.Math.floor(((0.125f * fConst0) + 0.5f));
		fConst26 = ((0.0f - (6.90775537f * fConst25)) / fConst0);
		fConst27 = (float)java.lang.Math.floor(((0.0134579996f * fConst0) + 0.5f));
		iConst28 = (int)(float)java.lang.Math.min(8192.0f, (float)java.lang.Math.max(0.0f, (fConst25 - fConst27)));
		iConst29 = (int)(float)java.lang.Math.min(1024.0f, (float)java.lang.Math.max(0.0f, (fConst27 + -1.0f)));
		fConst30 = (float)java.lang.Math.floor(((0.127837002f * fConst0) + 0.5f));
		fConst31 = ((0.0f - (6.90775537f * fConst30)) / fConst0);
		fConst32 = (float)java.lang.Math.floor(((0.0316039994f * fConst0) + 0.5f));
		iConst33 = (int)(float)java.lang.Math.min(8192.0f, (float)java.lang.Math.max(0.0f, (fConst30 - fConst32)));
		iConst34 = (int)(float)java.lang.Math.min(2048.0f, (float)java.lang.Math.max(0.0f, (fConst32 + -1.0f)));
		fConst35 = (float)java.lang.Math.floor(((0.174713001f * fConst0) + 0.5f));
		fConst36 = ((0.0f - (6.90775537f * fConst35)) / fConst0);
		fConst37 = (float)java.lang.Math.floor(((0.0229039993f * fConst0) + 0.5f));
		iConst38 = (int)(float)java.lang.Math.min(8192.0f, (float)java.lang.Math.max(0.0f, (fConst35 - fConst37)));
		iConst39 = (int)(float)java.lang.Math.min(2048.0f, (float)java.lang.Math.max(0.0f, (fConst37 + -1.0f)));
		fConst40 = (float)java.lang.Math.floor(((0.153128996f * fConst0) + 0.5f));
		fConst41 = ((0.0f - (6.90775537f * fConst40)) / fConst0);
		fConst42 = (float)java.lang.Math.floor(((0.0203460008f * fConst0) + 0.5f));
		iConst43 = (int)(float)java.lang.Math.min(8192.0f, (float)java.lang.Math.max(0.0f, (fConst40 - fConst42)));
		iConst44 = (int)(float)java.lang.Math.min(1024.0f, (float)java.lang.Math.max(0.0f, (fConst42 + -1.0f)));
		
	}
	
	public void instanceResetUserInterface() {
		fVslider0 = (float)-20.0f;
		fVslider1 = (float)0.0f;
		fVslider2 = (float)1500.0f;
		fVslider3 = (float)0.0f;
		fVslider4 = (float)315.0f;
		fVslider5 = (float)0.0f;
		fVslider6 = (float)2.0f;
		fVslider7 = (float)6000.0f;
		fVslider8 = (float)3.0f;
		fVslider9 = (float)200.0f;
		fVslider10 = (float)60.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec15[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec14[l3] = 0.0f;
			
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 32768); l4 = (l4 + 1)) {
			fVec0[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 16384); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec12[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec19[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec18[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 32768); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 4096); l11 = (l11 + 1)) {
			fVec4[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec16[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec23[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec22[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 16384); l15 = (l15 + 1)) {
			fVec5[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 4096); l16 = (l16 + 1)) {
			fVec6[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec20[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec27[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec26[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 32768); l20 = (l20 + 1)) {
			fVec7[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 4096); l21 = (l21 + 1)) {
			fVec8[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec24[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec31[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec30[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 16384); l25 = (l25 + 1)) {
			fVec9[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 16384); l26 = (l26 + 1)) {
			fVec10[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			fVec11[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec28[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec35[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec34[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 16384); l31 = (l31 + 1)) {
			fVec12[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 4096); l32 = (l32 + 1)) {
			fVec13[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec32[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec39[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec38[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 16384); l36 = (l36 + 1)) {
			fVec14[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			fVec15[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec36[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec43[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec42[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 16384); l41 = (l41 + 1)) {
			fVec16[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			fVec17[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec40[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec4[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec5[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec6[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec7[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec8[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec9[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec10[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec11[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec3[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec2[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec45[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec44[l55] = 0.0f;
			
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
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER  ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and  references");
		ui_interface.openHorizontalBox("Zita_Rev1");
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("Input");
		ui_interface.declare("fVslider10", "1", "");
		ui_interface.declare("fVslider10", "style", "knob");
		ui_interface.declare("fVslider10", "tooltip", "Delay in ms   before reverberation begins");
		ui_interface.declare("fVslider10", "unit", "ms");
		ui_interface.addVerticalSlider("In Delay", new FaustVarAccess() {
				public String getId() { return "fVslider10"; }
				public void set(float val) { fVslider10 = val; }
				public float get() { return (float)fVslider10; }
			}
			, 60.0f, 20.0f, 100.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface.declare("fVslider9", "1", "");
		ui_interface.declare("fVslider9", "scale", "log");
		ui_interface.declare("fVslider9", "style", "knob");
		ui_interface.declare("fVslider9", "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface.declare("fVslider9", "unit", "Hz");
		ui_interface.addVerticalSlider("LF X", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, 200.0f, 50.0f, 1000.0f, 1.0f);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "scale", "log");
		ui_interface.declare("fVslider8", "style", "knob");
		ui_interface.declare("fVslider8", "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface.declare("fVslider8", "unit", "s");
		ui_interface.addVerticalSlider("Low RT60", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, 3.0f, 1.0f, 8.0f, 0.100000001f);
		ui_interface.declare("fVslider6", "3", "");
		ui_interface.declare("fVslider6", "scale", "log");
		ui_interface.declare("fVslider6", "style", "knob");
		ui_interface.declare("fVslider6", "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface.declare("fVslider6", "unit", "s");
		ui_interface.addVerticalSlider("Mid RT60", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, 2.0f, 1.0f, 8.0f, 0.100000001f);
		ui_interface.declare("fVslider7", "4", "");
		ui_interface.declare("fVslider7", "scale", "log");
		ui_interface.declare("fVslider7", "style", "knob");
		ui_interface.declare("fVslider7", "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface.declare("fVslider7", "unit", "Hz");
		ui_interface.addVerticalSlider("HF Damping", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, 6000.0f, 1500.0f, 23520.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface.declare("fVslider4", "1", "");
		ui_interface.declare("fVslider4", "scale", "log");
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.declare("fVslider4", "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface.declare("fVslider4", "unit", "Hz");
		ui_interface.addVerticalSlider("Eq1 Freq", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, 315.0f, 40.0f, 2500.0f, 1.0f);
		ui_interface.declare("fVslider5", "2", "");
		ui_interface.declare("fVslider5", "style", "knob");
		ui_interface.declare("fVslider5", "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("Eq1 Level", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, 0.0f, -15.0f, 15.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.declare("fVslider2", "scale", "log");
		ui_interface.declare("fVslider2", "style", "knob");
		ui_interface.declare("fVslider2", "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface.declare("fVslider2", "unit", "Hz");
		ui_interface.addVerticalSlider("Eq2 Freq", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 1500.0f, 160.0f, 10000.0f, 1.0f);
		ui_interface.declare("fVslider3", "2", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface.declare("fVslider3", "unit", "dB");
		ui_interface.addVerticalSlider("Eq2 Level", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, 0.0f, -15.0f, 15.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.declare("0", "5", "");
		ui_interface.openHorizontalBox("Output");
		ui_interface.declare("fVslider1", "1", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "-1 = dry, 1 = wet");
		ui_interface.addVerticalSlider("Dry/Wet Mix", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 0.0f, -1.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fVslider0", "2", "");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "Output scale   factor");
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("Level", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, -20.0f, -70.0f, 40.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		float fSlow1 = (0.00100000005f * fVslider1);
		float fSlow2 = fVslider2;
		float fSlow3 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider3));
		float fSlow4 = (fConst1 * (fSlow2 / (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fSlow3))));
		float fSlow5 = ((1.0f - fSlow4) / (fSlow4 + 1.0f));
		float fSlow6 = fVslider4;
		float fSlow7 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider5));
		float fSlow8 = (fConst1 * (fSlow6 / (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fSlow7))));
		float fSlow9 = ((1.0f - fSlow8) / (fSlow8 + 1.0f));
		float fSlow10 = fVslider6;
		float fSlow11 = (float)java.lang.Math.exp((fConst3 / fSlow10));
		float fSlow12 = mydsp_faustpower2_f(fSlow11);
		float fSlow13 = (float)java.lang.Math.cos((fConst4 * fVslider7));
		float fSlow14 = (1.0f - (fSlow12 * fSlow13));
		float fSlow15 = (1.0f - fSlow12);
		float fSlow16 = (fSlow14 / fSlow15);
		float fSlow17 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow14) / mydsp_faustpower2_f(fSlow15)) + -1.0f)));
		float fSlow18 = (fSlow16 - fSlow17);
		float fSlow19 = (fSlow11 * (fSlow17 + (1.0f - fSlow16)));
		float fSlow20 = fVslider8;
		float fSlow21 = (((float)java.lang.Math.exp((fConst3 / fSlow20)) / fSlow11) + -1.0f);
		float fSlow22 = (1.0f / (float)java.lang.Math.tan((fConst5 * fVslider9)));
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (0.0f - ((1.0f - fSlow22) / fSlow23));
		float fSlow25 = (1.0f / fSlow23);
		int iSlow26 = (int)(float)java.lang.Math.min(8192.0f, (float)java.lang.Math.max(0.0f, (fConst8 * fVslider10)));
		float fSlow27 = (float)java.lang.Math.exp((fConst11 / fSlow10));
		float fSlow28 = mydsp_faustpower2_f(fSlow27);
		float fSlow29 = (1.0f - (fSlow13 * fSlow28));
		float fSlow30 = (1.0f - fSlow28);
		float fSlow31 = (fSlow29 / fSlow30);
		float fSlow32 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow29) / mydsp_faustpower2_f(fSlow30)) + -1.0f)));
		float fSlow33 = (fSlow31 - fSlow32);
		float fSlow34 = (fSlow27 * (fSlow32 + (1.0f - fSlow31)));
		float fSlow35 = (((float)java.lang.Math.exp((fConst11 / fSlow20)) / fSlow27) + -1.0f);
		float fSlow36 = (float)java.lang.Math.exp((fConst16 / fSlow10));
		float fSlow37 = mydsp_faustpower2_f(fSlow36);
		float fSlow38 = (1.0f - (fSlow13 * fSlow37));
		float fSlow39 = (1.0f - fSlow37);
		float fSlow40 = (fSlow38 / fSlow39);
		float fSlow41 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow38) / mydsp_faustpower2_f(fSlow39)) + -1.0f)));
		float fSlow42 = (fSlow40 - fSlow41);
		float fSlow43 = (fSlow36 * (fSlow41 + (1.0f - fSlow40)));
		float fSlow44 = (((float)java.lang.Math.exp((fConst16 / fSlow20)) / fSlow36) + -1.0f);
		float fSlow45 = (float)java.lang.Math.exp((fConst21 / fSlow10));
		float fSlow46 = mydsp_faustpower2_f(fSlow45);
		float fSlow47 = (1.0f - (fSlow46 * fSlow13));
		float fSlow48 = (1.0f - fSlow46);
		float fSlow49 = (fSlow47 / fSlow48);
		float fSlow50 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow47) / mydsp_faustpower2_f(fSlow48)) + -1.0f)));
		float fSlow51 = (fSlow49 - fSlow50);
		float fSlow52 = (fSlow45 * (fSlow50 + (1.0f - fSlow49)));
		float fSlow53 = (((float)java.lang.Math.exp((fConst21 / fSlow20)) / fSlow45) + -1.0f);
		float fSlow54 = (float)java.lang.Math.exp((fConst26 / fSlow10));
		float fSlow55 = mydsp_faustpower2_f(fSlow54);
		float fSlow56 = (1.0f - (fSlow13 * fSlow55));
		float fSlow57 = (1.0f - fSlow55);
		float fSlow58 = (fSlow56 / fSlow57);
		float fSlow59 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow56) / mydsp_faustpower2_f(fSlow57)) + -1.0f)));
		float fSlow60 = (fSlow58 - fSlow59);
		float fSlow61 = (fSlow54 * (fSlow59 + (1.0f - fSlow58)));
		float fSlow62 = (((float)java.lang.Math.exp((fConst26 / fSlow20)) / fSlow54) + -1.0f);
		float fSlow63 = (float)java.lang.Math.exp((fConst31 / fSlow10));
		float fSlow64 = mydsp_faustpower2_f(fSlow63);
		float fSlow65 = (1.0f - (fSlow13 * fSlow64));
		float fSlow66 = (1.0f - fSlow64);
		float fSlow67 = (fSlow65 / fSlow66);
		float fSlow68 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow65) / mydsp_faustpower2_f(fSlow66)) + -1.0f)));
		float fSlow69 = (fSlow67 - fSlow68);
		float fSlow70 = (fSlow63 * (fSlow68 + (1.0f - fSlow67)));
		float fSlow71 = (((float)java.lang.Math.exp((fConst31 / fSlow20)) / fSlow63) + -1.0f);
		float fSlow72 = (float)java.lang.Math.exp((fConst36 / fSlow10));
		float fSlow73 = mydsp_faustpower2_f(fSlow72);
		float fSlow74 = (1.0f - (fSlow13 * fSlow73));
		float fSlow75 = (1.0f - fSlow73);
		float fSlow76 = (fSlow74 / fSlow75);
		float fSlow77 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow74) / mydsp_faustpower2_f(fSlow75)) + -1.0f)));
		float fSlow78 = (fSlow76 - fSlow77);
		float fSlow79 = (fSlow72 * (fSlow77 + (1.0f - fSlow76)));
		float fSlow80 = (((float)java.lang.Math.exp((fConst36 / fSlow20)) / fSlow72) + -1.0f);
		float fSlow81 = (float)java.lang.Math.exp((fConst41 / fSlow10));
		float fSlow82 = mydsp_faustpower2_f(fSlow81);
		float fSlow83 = (1.0f - (fSlow82 * fSlow13));
		float fSlow84 = (1.0f - fSlow82);
		float fSlow85 = (fSlow83 / fSlow84);
		float fSlow86 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, ((mydsp_faustpower2_f(fSlow83) / mydsp_faustpower2_f(fSlow84)) + -1.0f)));
		float fSlow87 = (fSlow85 - fSlow86);
		float fSlow88 = (fSlow81 * (fSlow86 + (1.0f - fSlow85)));
		float fSlow89 = (((float)java.lang.Math.exp((fConst41 / fSlow20)) / fSlow81) + -1.0f);
		float fSlow90 = ((0.0f - (float)java.lang.Math.cos((fConst1 * fSlow6))) * (fSlow9 + 1.0f));
		float fSlow91 = ((0.0f - (float)java.lang.Math.cos((fConst1 * fSlow2))) * (fSlow5 + 1.0f));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec1[0] = (fSlow1 + (0.999000013f * fRec1[1]));
			float fTemp0 = (fRec1[0] + 1.0f);
			float fTemp1 = (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, (39.8107185f * input0[i])));
			float fTemp2 = (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp1)));
			float fTemp3 = (1.0f - (0.5f * fTemp0));
			fRec15[0] = ((fSlow24 * fRec15[1]) + (fSlow25 * (fRec11[1] + fRec11[2])));
			fRec14[0] = ((fSlow18 * fRec14[1]) + (fSlow19 * (fRec11[1] + (fSlow21 * fRec15[0]))));
			fVec0[(IOTA & 32767)] = ((0.353553385f * fRec14[0]) + 9.99999968e-21f);
			float fTemp4 = (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, (39.8107185f * input1[i])));
			float fTemp5 = (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp4)));
			fVec1[(IOTA & 16383)] = (fTemp4 * fTemp5);
			float fTemp6 = (0.300000012f * fVec1[((IOTA - iSlow26) & 16383)]);
			float fTemp7 = (((0.600000024f * fRec12[1]) + fVec0[((IOTA - iConst7) & 32767)]) - fTemp6);
			fVec2[(IOTA & 2047)] = fTemp7;
			fRec12[0] = fVec2[((IOTA - iConst9) & 2047)];
			float fRec13 = (0.0f - (0.600000024f * fTemp7));
			fRec19[0] = ((fSlow24 * fRec19[1]) + (fSlow25 * (fRec7[1] + fRec7[2])));
			fRec18[0] = ((fSlow33 * fRec18[1]) + (fSlow34 * (fRec7[1] + (fSlow35 * fRec19[0]))));
			fVec3[(IOTA & 32767)] = ((0.353553385f * fRec18[0]) + 9.99999968e-21f);
			float fTemp8 = (((0.600000024f * fRec16[1]) + fVec3[((IOTA - iConst13) & 32767)]) - fTemp6);
			fVec4[(IOTA & 4095)] = fTemp8;
			fRec16[0] = fVec4[((IOTA - iConst14) & 4095)];
			float fRec17 = (0.0f - (0.600000024f * fTemp8));
			fRec23[0] = ((fSlow24 * fRec23[1]) + (fSlow25 * (fRec9[1] + fRec9[2])));
			fRec22[0] = ((fSlow42 * fRec22[1]) + (fSlow43 * (fRec9[1] + (fSlow44 * fRec23[0]))));
			fVec5[(IOTA & 16383)] = ((0.353553385f * fRec22[0]) + 9.99999968e-21f);
			float fTemp9 = (fVec5[((IOTA - iConst18) & 16383)] + (fTemp6 + (0.600000024f * fRec20[1])));
			fVec6[(IOTA & 4095)] = fTemp9;
			fRec20[0] = fVec6[((IOTA - iConst19) & 4095)];
			float fRec21 = (0.0f - (0.600000024f * fTemp9));
			fRec27[0] = ((fSlow24 * fRec27[1]) + (fSlow25 * (fRec5[1] + fRec5[2])));
			fRec26[0] = ((fSlow51 * fRec26[1]) + (fSlow52 * (fRec5[1] + (fSlow53 * fRec27[0]))));
			fVec7[(IOTA & 32767)] = ((0.353553385f * fRec26[0]) + 9.99999968e-21f);
			float fTemp10 = (fTemp6 + ((0.600000024f * fRec24[1]) + fVec7[((IOTA - iConst23) & 32767)]));
			fVec8[(IOTA & 4095)] = fTemp10;
			fRec24[0] = fVec8[((IOTA - iConst24) & 4095)];
			float fRec25 = (0.0f - (0.600000024f * fTemp10));
			fRec31[0] = ((fSlow24 * fRec31[1]) + (fSlow25 * (fRec10[1] + fRec10[2])));
			fRec30[0] = ((fSlow60 * fRec30[1]) + (fSlow61 * (fRec10[1] + (fSlow62 * fRec31[0]))));
			fVec9[(IOTA & 16383)] = ((0.353553385f * fRec30[0]) + 9.99999968e-21f);
			fVec10[(IOTA & 16383)] = (fTemp1 * fTemp2);
			float fTemp11 = (0.300000012f * fVec10[((IOTA - iSlow26) & 16383)]);
			float fTemp12 = (fVec9[((IOTA - iConst28) & 16383)] - (fTemp11 + (0.600000024f * fRec28[1])));
			fVec11[(IOTA & 2047)] = fTemp12;
			fRec28[0] = fVec11[((IOTA - iConst29) & 2047)];
			float fRec29 = (0.600000024f * fTemp12);
			fRec35[0] = ((fSlow24 * fRec35[1]) + (fSlow25 * (fRec6[1] + fRec6[2])));
			fRec34[0] = ((fSlow69 * fRec34[1]) + (fSlow70 * (fRec6[1] + (fSlow71 * fRec35[0]))));
			fVec12[(IOTA & 16383)] = ((0.353553385f * fRec34[0]) + 9.99999968e-21f);
			float fTemp13 = (fVec12[((IOTA - iConst33) & 16383)] - (fTemp11 + (0.600000024f * fRec32[1])));
			fVec13[(IOTA & 4095)] = fTemp13;
			fRec32[0] = fVec13[((IOTA - iConst34) & 4095)];
			float fRec33 = (0.600000024f * fTemp13);
			fRec39[0] = ((fSlow24 * fRec39[1]) + (fSlow25 * (fRec8[1] + fRec8[2])));
			fRec38[0] = ((fSlow78 * fRec38[1]) + (fSlow79 * (fRec8[1] + (fSlow80 * fRec39[0]))));
			fVec14[(IOTA & 16383)] = ((0.353553385f * fRec38[0]) + 9.99999968e-21f);
			float fTemp14 = ((fTemp11 + fVec14[((IOTA - iConst38) & 16383)]) - (0.600000024f * fRec36[1]));
			fVec15[(IOTA & 4095)] = fTemp14;
			fRec36[0] = fVec15[((IOTA - iConst39) & 4095)];
			float fRec37 = (0.600000024f * fTemp14);
			fRec43[0] = ((fSlow24 * fRec43[1]) + (fSlow25 * (fRec4[1] + fRec4[2])));
			fRec42[0] = ((fSlow87 * fRec42[1]) + (fSlow88 * (fRec4[1] + (fSlow89 * fRec43[0]))));
			fVec16[(IOTA & 16383)] = ((0.353553385f * fRec42[0]) + 9.99999968e-21f);
			float fTemp15 = ((fVec16[((IOTA - iConst43) & 16383)] + fTemp11) - (0.600000024f * fRec40[1]));
			fVec17[(IOTA & 2047)] = fTemp15;
			fRec40[0] = fVec17[((IOTA - iConst44) & 2047)];
			float fRec41 = (0.600000024f * fTemp15);
			float fTemp16 = (fRec41 + fRec37);
			float fTemp17 = (fRec29 + (fRec33 + fTemp16));
			fRec4[0] = (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec17 + (fRec21 + (fRec25 + fTemp17))))))))))));
			fRec5[0] = ((fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec40[1] + fTemp17)))) - (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec13 + (fRec17 + (fRec25 + fRec21))))))));
			float fTemp18 = (fRec33 + fRec29);
			fRec6[0] = ((fRec20[1] + (fRec24[1] + (fRec36[1] + (fRec40[1] + (fRec21 + (fRec25 + fTemp16)))))) - (fRec12[1] + (fRec16[1] + (fRec28[1] + (fRec32[1] + (fRec13 + (fRec17 + fTemp18)))))));
			fRec7[0] = ((fRec12[1] + (fRec16[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec17 + fTemp16)))))) - (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec21 + (fRec25 + fTemp18)))))));
			float fTemp19 = (fRec41 + fRec33);
			float fTemp20 = (fRec37 + fRec29);
			fRec8[0] = ((fRec16[1] + (fRec24[1] + (fRec32[1] + (fRec40[1] + (fRec17 + (fRec25 + fTemp19)))))) - (fRec12[1] + (fRec20[1] + (fRec28[1] + (fRec36[1] + (fRec13 + (fRec21 + fTemp20)))))));
			fRec9[0] = ((fRec12[1] + (fRec20[1] + (fRec32[1] + (fRec40[1] + (fRec13 + (fRec21 + fTemp19)))))) - (fRec16[1] + (fRec24[1] + (fRec28[1] + (fRec36[1] + (fRec17 + (fRec25 + fTemp20)))))));
			float fTemp21 = (fRec41 + fRec29);
			float fTemp22 = (fRec37 + fRec33);
			fRec10[0] = ((fRec12[1] + (fRec24[1] + (fRec28[1] + (fRec40[1] + (fRec13 + (fRec25 + fTemp21)))))) - (fRec16[1] + (fRec20[1] + (fRec32[1] + (fRec36[1] + (fRec17 + (fRec21 + fTemp22)))))));
			fRec11[0] = ((fRec16[1] + (fRec20[1] + (fRec28[1] + (fRec40[1] + (fRec17 + (fRec21 + fTemp21)))))) - (fRec12[1] + (fRec24[1] + (fRec32[1] + (fRec36[1] + (fRec13 + (fRec25 + fTemp22)))))));
			float fTemp23 = (0.370000005f * (fRec5[0] + fRec6[0]));
			float fTemp24 = (fSlow90 * fRec3[1]);
			fRec3[0] = (fTemp23 - (fTemp24 + (fSlow9 * fRec3[2])));
			float fTemp25 = (fSlow9 * fRec3[0]);
			float fTemp26 = (0.5f * ((fTemp25 + (fRec3[2] + (fTemp23 + fTemp24))) + (fSlow7 * ((fTemp25 + (fTemp24 + fRec3[2])) - fTemp23))));
			float fTemp27 = (fSlow91 * fRec2[1]);
			fRec2[0] = (fTemp26 - (fTemp27 + (fSlow5 * fRec2[2])));
			float fTemp28 = (fSlow5 * fRec2[0]);
			output0[i] = (0.5f * (fRec0[0] * (((fTemp0 * fTemp1) * fTemp2) + (fTemp3 * ((fTemp28 + (fRec2[2] + (fTemp26 + fTemp27))) + (fSlow3 * ((fTemp28 + (fTemp27 + fRec2[2])) - fTemp26)))))));
			float fTemp29 = (0.370000005f * (fRec5[0] - fRec6[0]));
			float fTemp30 = (fSlow90 * fRec45[1]);
			fRec45[0] = (fTemp29 - (fTemp30 + (fSlow9 * fRec45[2])));
			float fTemp31 = (fSlow9 * fRec45[0]);
			float fTemp32 = (0.5f * ((fTemp31 + (fRec45[2] + (fTemp29 + fTemp30))) + (fSlow7 * ((fTemp31 + (fTemp30 + fRec45[2])) - fTemp29))));
			float fTemp33 = (fSlow91 * fRec44[1]);
			fRec44[0] = (fTemp32 - (fTemp33 + (fSlow5 * fRec44[2])));
			float fTemp34 = (fSlow5 * fRec44[0]);
			output1[i] = (0.5f * (fRec0[0] * (((fTemp0 * fTemp4) * fTemp5) + (fTemp3 * ((fTemp34 + (fRec44[2] + (fTemp32 + fTemp33))) + (fSlow3 * ((fTemp34 + (fTemp33 + fRec44[2])) - fTemp32)))))));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			IOTA = (IOTA + 1);
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec20[1] = fRec20[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec24[1] = fRec24[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec36[1] = fRec36[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec40[1] = fRec40[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			
		}
		
	}
	
};

