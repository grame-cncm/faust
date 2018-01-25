/* ------------------------------------------------------------
name: "felix2"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	int IOTA;
	float fVec0[] = new float[512];
	float fVec1[] = new float[512];
	float fVec2[] = new float[512];
	float fVec3[] = new float[512];
	float fVec4[] = new float[512];
	float fVec5[] = new float[512];
	float fRec0[] = new float[2];
	float fVbargraph0;
	float fRec1[] = new float[2];
	float fVbargraph1;
	float fRec2[] = new float[2];
	float fVbargraph2;
	float fRec3[] = new float[2];
	float fVbargraph3;
	float fRec4[] = new float[2];
	float fVbargraph4;
	float fRec5[] = new float[2];
	float fVbargraph5;
	float fRec6[] = new float[2];
	float fVbargraph6;
	float fRec7[] = new float[2];
	float fVbargraph7;
	float fRec8[] = new float[2];
	float fVbargraph8;
	float fRec9[] = new float[2];
	float fVbargraph9;
	float fRec10[] = new float[2];
	float fVbargraph10;
	float fRec11[] = new float[2];
	float fVbargraph11;
	float fRec12[] = new float[2];
	float fVbargraph12;
	float fRec13[] = new float[2];
	float fVbargraph13;
	float fRec14[] = new float[2];
	float fVbargraph14;
	float fRec15[] = new float[2];
	float fVbargraph15;
	float fRec16[] = new float[2];
	float fVbargraph16;
	float fRec17[] = new float[2];
	float fVbargraph17;
	float fRec18[] = new float[2];
	float fVbargraph18;
	float fRec19[] = new float[2];
	float fVbargraph19;
	float fRec20[] = new float[2];
	float fVbargraph20;
	float fRec21[] = new float[2];
	float fVbargraph21;
	float fRec22[] = new float[2];
	float fVbargraph22;
	float fRec23[] = new float[2];
	float fVbargraph23;
	float fRec24[] = new float[2];
	float fVbargraph24;
	float fRec25[] = new float[2];
	float fVbargraph25;
	float fRec26[] = new float[2];
	float fVbargraph26;
	float fRec27[] = new float[2];
	float fVbargraph27;
	float fRec28[] = new float[2];
	float fVbargraph28;
	float fRec29[] = new float[2];
	float fVbargraph29;
	float fRec30[] = new float[2];
	float fVbargraph30;
	float fRec31[] = new float[2];
	float fVbargraph31;
	float fRec32[] = new float[2];
	float fVbargraph32;
	float fRec33[] = new float[2];
	float fVbargraph33;
	float fRec34[] = new float[2];
	float fVbargraph34;
	float fRec35[] = new float[2];
	float fVbargraph35;
	
	public void metadata(Meta m) { 
		m.declare("math.lib/author", "GRAME");
		m.declare("math.lib/copyright", "GRAME");
		m.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("math.lib/license", "LGPL with exception");
		m.declare("math.lib/name", "Math Library");
		m.declare("math.lib/version", "1.0");
		m.declare("music.lib/author", "GRAME");
		m.declare("music.lib/copyright", "GRAME");
		m.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("music.lib/license", "LGPL with exception");
		m.declare("music.lib/name", "Music Library");
		m.declare("music.lib/version", "1.0");
		m.declare("name", "felix2");
	}

	int getNumInputs() {
		return 6;
		
	}
	int getNumOutputs() {
		return 36;
		
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			case 8: {
				rate = 1;
				break;
			}
			case 9: {
				rate = 1;
				break;
			}
			case 10: {
				rate = 1;
				break;
			}
			case 11: {
				rate = 1;
				break;
			}
			case 12: {
				rate = 1;
				break;
			}
			case 13: {
				rate = 1;
				break;
			}
			case 14: {
				rate = 1;
				break;
			}
			case 15: {
				rate = 1;
				break;
			}
			case 16: {
				rate = 1;
				break;
			}
			case 17: {
				rate = 1;
				break;
			}
			case 18: {
				rate = 1;
				break;
			}
			case 19: {
				rate = 1;
				break;
			}
			case 20: {
				rate = 1;
				break;
			}
			case 21: {
				rate = 1;
				break;
			}
			case 22: {
				rate = 1;
				break;
			}
			case 23: {
				rate = 1;
				break;
			}
			case 24: {
				rate = 1;
				break;
			}
			case 25: {
				rate = 1;
				break;
			}
			case 26: {
				rate = 1;
				break;
			}
			case 27: {
				rate = 1;
				break;
			}
			case 28: {
				rate = 1;
				break;
			}
			case 29: {
				rate = 1;
				break;
			}
			case 30: {
				rate = 1;
				break;
			}
			case 31: {
				rate = 1;
				break;
			}
			case 32: {
				rate = 1;
				break;
			}
			case 33: {
				rate = 1;
				break;
			}
			case 34: {
				rate = 1;
				break;
			}
			case 35: {
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
		fConst0 = (96.0f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		
	}
	
	public void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 512); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 512); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 512); l2 = (l2 + 1)) {
			fVec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 512); l3 = (l3 + 1)) {
			fVec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 512); l4 = (l4 + 1)) {
			fVec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 512); l5 = (l5 + 1)) {
			fVec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec1[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec2[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec3[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec4[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec5[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec6[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec7[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec8[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec9[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec10[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec12[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec13[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec14[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec15[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec16[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec17[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec18[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec19[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec20[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec21[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec22[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec23[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec24[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec25[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec26[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec27[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec28[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec29[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec30[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec31[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec32[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec33[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec34[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec35[l41] = 0.0f;
			
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
		ui_interface.openVerticalBox("felix2");
		ui_interface.openHorizontalBox("ctrl   0");
		ui_interface.addVerticalBargraph("ctrl  0", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl  1", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl  2", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl  3", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl  4", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl  5", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, 0.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   1");
		ui_interface.addVerticalBargraph("ctrl 10", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 11", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 12", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 13", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 14", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 15", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, 0.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   2");
		ui_interface.addVerticalBargraph("ctrl 20", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 21", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 22", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 23", new FaustVarAccess() {
				public String getId() { return "fVbargraph15"; }
				public void set(float val) { fVbargraph15 = val; }
				public float get() { return (float)fVbargraph15; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 24", new FaustVarAccess() {
				public String getId() { return "fVbargraph16"; }
				public void set(float val) { fVbargraph16 = val; }
				public float get() { return (float)fVbargraph16; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 25", new FaustVarAccess() {
				public String getId() { return "fVbargraph17"; }
				public void set(float val) { fVbargraph17 = val; }
				public float get() { return (float)fVbargraph17; }
			}
			, 0.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   3");
		ui_interface.addVerticalBargraph("ctrl 30", new FaustVarAccess() {
				public String getId() { return "fVbargraph18"; }
				public void set(float val) { fVbargraph18 = val; }
				public float get() { return (float)fVbargraph18; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 31", new FaustVarAccess() {
				public String getId() { return "fVbargraph19"; }
				public void set(float val) { fVbargraph19 = val; }
				public float get() { return (float)fVbargraph19; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 32", new FaustVarAccess() {
				public String getId() { return "fVbargraph20"; }
				public void set(float val) { fVbargraph20 = val; }
				public float get() { return (float)fVbargraph20; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 33", new FaustVarAccess() {
				public String getId() { return "fVbargraph21"; }
				public void set(float val) { fVbargraph21 = val; }
				public float get() { return (float)fVbargraph21; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 34", new FaustVarAccess() {
				public String getId() { return "fVbargraph22"; }
				public void set(float val) { fVbargraph22 = val; }
				public float get() { return (float)fVbargraph22; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 35", new FaustVarAccess() {
				public String getId() { return "fVbargraph23"; }
				public void set(float val) { fVbargraph23 = val; }
				public float get() { return (float)fVbargraph23; }
			}
			, 0.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   4");
		ui_interface.addVerticalBargraph("ctrl 40", new FaustVarAccess() {
				public String getId() { return "fVbargraph24"; }
				public void set(float val) { fVbargraph24 = val; }
				public float get() { return (float)fVbargraph24; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 41", new FaustVarAccess() {
				public String getId() { return "fVbargraph25"; }
				public void set(float val) { fVbargraph25 = val; }
				public float get() { return (float)fVbargraph25; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 42", new FaustVarAccess() {
				public String getId() { return "fVbargraph26"; }
				public void set(float val) { fVbargraph26 = val; }
				public float get() { return (float)fVbargraph26; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 43", new FaustVarAccess() {
				public String getId() { return "fVbargraph27"; }
				public void set(float val) { fVbargraph27 = val; }
				public float get() { return (float)fVbargraph27; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 44", new FaustVarAccess() {
				public String getId() { return "fVbargraph28"; }
				public void set(float val) { fVbargraph28 = val; }
				public float get() { return (float)fVbargraph28; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 45", new FaustVarAccess() {
				public String getId() { return "fVbargraph29"; }
				public void set(float val) { fVbargraph29 = val; }
				public float get() { return (float)fVbargraph29; }
			}
			, 0.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("ctrl   5");
		ui_interface.addVerticalBargraph("ctrl 50", new FaustVarAccess() {
				public String getId() { return "fVbargraph30"; }
				public void set(float val) { fVbargraph30 = val; }
				public float get() { return (float)fVbargraph30; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 51", new FaustVarAccess() {
				public String getId() { return "fVbargraph31"; }
				public void set(float val) { fVbargraph31 = val; }
				public float get() { return (float)fVbargraph31; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 52", new FaustVarAccess() {
				public String getId() { return "fVbargraph32"; }
				public void set(float val) { fVbargraph32 = val; }
				public float get() { return (float)fVbargraph32; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 53", new FaustVarAccess() {
				public String getId() { return "fVbargraph33"; }
				public void set(float val) { fVbargraph33 = val; }
				public float get() { return (float)fVbargraph33; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 54", new FaustVarAccess() {
				public String getId() { return "fVbargraph34"; }
				public void set(float val) { fVbargraph34 = val; }
				public float get() { return (float)fVbargraph34; }
			}
			, 0.0f, 1.0f);
		ui_interface.addVerticalBargraph("ctrl 55", new FaustVarAccess() {
				public String getId() { return "fVbargraph35"; }
				public void set(float val) { fVbargraph35 = val; }
				public float get() { return (float)fVbargraph35; }
			}
			, 0.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] input2 = inputs[2];
		float[] input3 = inputs[3];
		float[] input4 = inputs[4];
		float[] input5 = inputs[5];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float[] output4 = outputs[4];
		float[] output5 = outputs[5];
		float[] output6 = outputs[6];
		float[] output7 = outputs[7];
		float[] output8 = outputs[8];
		float[] output9 = outputs[9];
		float[] output10 = outputs[10];
		float[] output11 = outputs[11];
		float[] output12 = outputs[12];
		float[] output13 = outputs[13];
		float[] output14 = outputs[14];
		float[] output15 = outputs[15];
		float[] output16 = outputs[16];
		float[] output17 = outputs[17];
		float[] output18 = outputs[18];
		float[] output19 = outputs[19];
		float[] output20 = outputs[20];
		float[] output21 = outputs[21];
		float[] output22 = outputs[22];
		float[] output23 = outputs[23];
		float[] output24 = outputs[24];
		float[] output25 = outputs[25];
		float[] output26 = outputs[26];
		float[] output27 = outputs[27];
		float[] output28 = outputs[28];
		float[] output29 = outputs[29];
		float[] output30 = outputs[30];
		float[] output31 = outputs[31];
		float[] output32 = outputs[32];
		float[] output33 = outputs[33];
		float[] output34 = outputs[34];
		float[] output35 = outputs[35];
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[(IOTA & 511)] = input0[i];
			float fTemp0 = input1[i];
			fVec1[(IOTA & 511)] = fTemp0;
			float fTemp1 = input2[i];
			fVec2[(IOTA & 511)] = fTemp1;
			float fTemp2 = input3[i];
			fVec3[(IOTA & 511)] = fTemp2;
			float fTemp3 = input4[i];
			fVec4[(IOTA & 511)] = fTemp3;
			float fTemp4 = input5[i];
			fVec5[(IOTA & 511)] = fTemp4;
			fRec0[0] = (float)java.lang.Math.max((fRec0[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 244) & 511)]) + fVec2[((IOTA - 233) & 511)]) + fVec3[((IOTA - 221) & 511)]) + fVec4[((IOTA - 209) & 511)]) + fVec5[((IOTA - 197) & 511)])));
			fVbargraph0 = fRec0[0];
			output0[i] = fVbargraph0;
			float fTemp5 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 246) & 511)]);
			fRec1[0] = (float)java.lang.Math.max((fRec1[1] - fConst0), (float)java.lang.Math.abs(((((fTemp5 + fVec2[((IOTA - 236) & 511)]) + fVec3[((IOTA - 225) & 511)]) + fVec4[((IOTA - 215) & 511)]) + fVec5[((IOTA - 204) & 511)])));
			fVbargraph1 = fRec1[0];
			output1[i] = fVbargraph1;
			fRec2[0] = (float)java.lang.Math.max((fRec2[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 247) & 511)]) + fVec2[((IOTA - 239) & 511)]) + fVec3[((IOTA - 230) & 511)]) + fVec4[((IOTA - 220) & 511)]) + fVec5[((IOTA - 211) & 511)])));
			fVbargraph2 = fRec2[0];
			output2[i] = fVbargraph2;
			float fTemp6 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 249) & 511)]);
			float fTemp7 = (fTemp6 + fVec2[((IOTA - 241) & 511)]);
			fRec3[0] = (float)java.lang.Math.max((fRec3[1] - fConst0), (float)java.lang.Math.abs((((fTemp7 + fVec3[((IOTA - 233) & 511)]) + fVec4[((IOTA - 225) & 511)]) + fVec5[((IOTA - 217) & 511)])));
			fVbargraph3 = fRec3[0];
			output3[i] = fVbargraph3;
			float fTemp8 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 250) & 511)]);
			fRec4[0] = (float)java.lang.Math.max((fRec4[1] - fConst0), (float)java.lang.Math.abs(((((fTemp8 + fVec2[((IOTA - 243) & 511)]) + fVec3[((IOTA - 236) & 511)]) + fVec4[((IOTA - 229) & 511)]) + fVec5[((IOTA - 222) & 511)])));
			fVbargraph4 = fRec4[0];
			output4[i] = fVbargraph4;
			fRec5[0] = (float)java.lang.Math.max((fRec5[1] - fConst0), (float)java.lang.Math.abs(((((fTemp8 + fVec2[((IOTA - 245) & 511)]) + fVec3[((IOTA - 239) & 511)]) + fVec4[((IOTA - 232) & 511)]) + fVec5[((IOTA - 225) & 511)])));
			fVbargraph5 = fRec5[0];
			output5[i] = fVbargraph5;
			fRec6[0] = (float)java.lang.Math.max((fRec6[1] - fConst0), (float)java.lang.Math.abs(((((fTemp5 + fVec2[((IOTA - 235) & 511)]) + fVec3[((IOTA - 224) & 511)]) + fVec4[((IOTA - 213) & 511)]) + fVec5[((IOTA - 201) & 511)])));
			fVbargraph6 = fRec6[0];
			output6[i] = fVbargraph6;
			fRec7[0] = (float)java.lang.Math.max((fRec7[1] - fConst0), (float)java.lang.Math.abs((fVec4[((IOTA - 221) & 511)] + (fVec1[((IOTA - 248) & 511)] + (fVec5[((IOTA - 211) & 511)] + (fVec3[((IOTA - 230) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec2[((IOTA - 239) & 511)])))))));
			fVbargraph7 = fRec7[0];
			output7[i] = fVbargraph7;
			fRec8[0] = (float)java.lang.Math.max((fRec8[1] - fConst0), (float)java.lang.Math.abs(((((fTemp6 + fVec2[((IOTA - 243) & 511)]) + fVec3[((IOTA - 235) & 511)]) + fVec4[((IOTA - 227) & 511)]) + fVec5[((IOTA - 219) & 511)])));
			fVbargraph8 = fRec8[0];
			output8[i] = fVbargraph8;
			fRec9[0] = (float)java.lang.Math.max((fRec9[1] - fConst0), (float)java.lang.Math.abs((fVec1[((IOTA - 251) & 511)] + (fVec5[((IOTA - 225) & 511)] + (fVec4[((IOTA - 232) & 511)] + (fVec3[((IOTA - 239) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec2[((IOTA - 245) & 511)])))))));
			fVbargraph9 = fRec9[0];
			output9[i] = fVbargraph9;
			fRec10[0] = (float)java.lang.Math.max((fRec10[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 251) & 511)]) + fVec2[((IOTA - 247) & 511)]) + fVec3[((IOTA - 241) & 511)]) + fVec4[((IOTA - 236) & 511)]) + fVec5[((IOTA - 230) & 511)])));
			fVbargraph10 = fRec10[0];
			output10[i] = fVbargraph10;
			float fTemp9 = ((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 252) & 511)]) + fVec2[((IOTA - 248) & 511)]);
			fRec11[0] = (float)java.lang.Math.max((fRec11[1] - fConst0), (float)java.lang.Math.abs((((fTemp9 + fVec3[((IOTA - 243) & 511)]) + fVec4[((IOTA - 238) & 511)]) + fVec5[((IOTA - 233) & 511)])));
			fVbargraph11 = fRec11[0];
			output11[i] = fVbargraph11;
			fRec12[0] = (float)java.lang.Math.max((fRec12[1] - fConst0), (float)java.lang.Math.abs((((fTemp7 + fVec3[((IOTA - 232) & 511)]) + fVec4[((IOTA - 223) & 511)]) + fVec5[((IOTA - 212) & 511)])));
			fVbargraph12 = fRec12[0];
			output12[i] = fVbargraph12;
			fRec13[0] = (float)java.lang.Math.max((fRec13[1] - fConst0), (float)java.lang.Math.abs((fVec5[((IOTA - 224) & 511)] + (fVec3[((IOTA - 240) & 511)] + (fVec2[((IOTA - 246) & 511)] + (fVec1[((IOTA - 251) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec4[((IOTA - 232) & 511)])))))));
			fVbargraph13 = fRec13[0];
			output13[i] = fVbargraph13;
			fRec14[0] = (float)java.lang.Math.max((fRec14[1] - fConst0), (float)java.lang.Math.abs((fVec5[((IOTA - 231) & 511)] + (fVec3[((IOTA - 244) & 511)] + (fTemp9 + fVec4[((IOTA - 238) & 511)])))));
			fVbargraph14 = fRec14[0];
			output14[i] = fVbargraph14;
			fRec15[0] = (float)java.lang.Math.max((fRec15[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 253) & 511)]) + fVec2[((IOTA - 250) & 511)]) + fVec3[((IOTA - 246) & 511)]) + fVec4[((IOTA - 241) & 511)]) + fVec5[((IOTA - 236) & 511)])));
			fVbargraph15 = fRec15[0];
			output15[i] = fVbargraph15;
			float fTemp10 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 254) & 511)]);
			fRec16[0] = (float)java.lang.Math.max((fRec16[1] - fConst0), (float)java.lang.Math.abs(((((fTemp10 + fVec2[((IOTA - 251) & 511)]) + fVec3[((IOTA - 248) & 511)]) + fVec4[((IOTA - 244) & 511)]) + fVec5[((IOTA - 239) & 511)])));
			fVbargraph16 = fRec16[0];
			output16[i] = fVbargraph16;
			fRec17[0] = (float)java.lang.Math.max((fRec17[1] - fConst0), (float)java.lang.Math.abs(((((fTemp10 + fVec2[((IOTA - 252) & 511)]) + fVec3[((IOTA - 249) & 511)]) + fVec4[((IOTA - 245) & 511)]) + fVec5[((IOTA - 242) & 511)])));
			fVbargraph17 = fRec17[0];
			output17[i] = fVbargraph17;
			fRec18[0] = (float)java.lang.Math.max((fRec18[1] - fConst0), (float)java.lang.Math.abs((fVec4[((IOTA - 246) & 511)] + (fVec3[((IOTA - 252) & 511)] + (fVec2[((IOTA - 256) & 511)] + (fVec1[((IOTA - 257) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec5[((IOTA - 239) & 511)])))))));
			fVbargraph18 = fRec18[0];
			output18[i] = fVbargraph18;
			float fTemp11 = (fVec1[((IOTA - 256) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec2[((IOTA - 256) & 511)]));
			fRec19[0] = (float)java.lang.Math.max((fRec19[1] - fConst0), (float)java.lang.Math.abs((fVec5[((IOTA - 245) & 511)] + (fVec4[((IOTA - 250) & 511)] + (fVec3[((IOTA - 253) & 511)] + fTemp11)))));
			fVbargraph19 = fRec19[0];
			output19[i] = fVbargraph19;
			float fTemp12 = (fTemp11 + fVec3[((IOTA - 254) & 511)]);
			fRec20[0] = (float)java.lang.Math.max((fRec20[1] - fConst0), (float)java.lang.Math.abs(((fTemp12 + fVec4[((IOTA - 251) & 511)]) + fVec5[((IOTA - 247) & 511)])));
			fVbargraph20 = fRec20[0];
			output20[i] = fVbargraph20;
			fRec21[0] = (float)java.lang.Math.max((fRec21[1] - fConst0), (float)java.lang.Math.abs(((fTemp12 + fVec4[((IOTA - 252) & 511)]) + fVec5[((IOTA - 249) & 511)])));
			fVbargraph21 = fRec21[0];
			output21[i] = fVbargraph21;
			fRec22[0] = (float)java.lang.Math.max((fRec22[1] - fConst0), (float)java.lang.Math.abs(((fTemp12 + fVec4[((IOTA - 253) & 511)]) + fVec5[((IOTA - 250) & 511)])));
			fVbargraph22 = fRec22[0];
			output22[i] = fVbargraph22;
			fRec23[0] = (float)java.lang.Math.max((fRec23[1] - fConst0), (float)java.lang.Math.abs((fVec5[((IOTA - 251) & 511)] + (fVec3[((IOTA - 255) & 511)] + (fTemp11 + fVec4[((IOTA - 253) & 511)])))));
			fVbargraph23 = fRec23[0];
			output23[i] = fVbargraph23;
			fRec24[0] = (float)java.lang.Math.max((fRec24[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 263) & 511)]) + fVec2[((IOTA - 270) & 511)]) + fVec3[((IOTA - 274) & 511)]) + fVec4[((IOTA - 276) & 511)]) + fVec5[((IOTA - 276) & 511)])));
			fVbargraph24 = fRec24[0];
			output24[i] = fVbargraph24;
			fRec25[0] = (float)java.lang.Math.max((fRec25[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 261) & 511)]) + fVec2[((IOTA - 265) & 511)]) + fVec3[((IOTA - 268) & 511)]) + fVec4[((IOTA - 269) & 511)]) + fVec5[((IOTA - 269) & 511)])));
			fVbargraph25 = fRec25[0];
			output25[i] = fVbargraph25;
			float fTemp13 = ((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 260) & 511)]) + fVec2[((IOTA - 263) & 511)]);
			fRec26[0] = (float)java.lang.Math.max((fRec26[1] - fConst0), (float)java.lang.Math.abs((((fTemp13 + fVec3[((IOTA - 265) & 511)]) + fVec4[((IOTA - 265) & 511)]) + fVec5[((IOTA - 265) & 511)])));
			fVbargraph26 = fRec26[0];
			output26[i] = fVbargraph26;
			fRec27[0] = (float)java.lang.Math.max((fRec27[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 259) & 511)]) + fVec2[((IOTA - 261) & 511)]) + fVec3[((IOTA - 263) & 511)]) + fVec4[((IOTA - 263) & 511)]) + fVec5[((IOTA - 263) & 511)])));
			fVbargraph27 = fRec27[0];
			output27[i] = fVbargraph27;
			float fTemp14 = (fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 258) & 511)]);
			fRec28[0] = (float)java.lang.Math.max((fRec28[1] - fConst0), (float)java.lang.Math.abs(((((fTemp14 + fVec2[((IOTA - 260) & 511)]) + fVec3[((IOTA - 261) & 511)]) + fVec4[((IOTA - 262) & 511)]) + fVec5[((IOTA - 262) & 511)])));
			fVbargraph28 = fRec28[0];
			output28[i] = fVbargraph28;
			fRec29[0] = (float)java.lang.Math.max((fRec29[1] - fConst0), (float)java.lang.Math.abs(((((fTemp14 + fVec2[((IOTA - 259) & 511)]) + fVec3[((IOTA - 260) & 511)]) + fVec4[((IOTA - 261) & 511)]) + fVec5[((IOTA - 261) & 511)])));
			fVbargraph29 = fRec29[0];
			output29[i] = fVbargraph29;
			fRec30[0] = (float)java.lang.Math.max((fRec30[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 266) & 511)]) + fVec2[((IOTA - 276) & 511)]) + fVec3[((IOTA - 285) & 511)]) + fVec4[((IOTA - 293) & 511)]) + fVec5[((IOTA - 300) & 511)])));
			fVbargraph30 = fRec30[0];
			output30[i] = fVbargraph30;
			fRec31[0] = (float)java.lang.Math.max((fRec31[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 264) & 511)]) + fVec2[((IOTA - 272) & 511)]) + fVec3[((IOTA - 278) & 511)]) + fVec4[((IOTA - 284) & 511)]) + fVec5[((IOTA - 289) & 511)])));
			fVbargraph31 = fRec31[0];
			output31[i] = fVbargraph31;
			fRec32[0] = (float)java.lang.Math.max((fRec32[1] - fConst0), (float)java.lang.Math.abs((((((fVec0[((IOTA - 256) & 511)] + fVec1[((IOTA - 262) & 511)]) + fVec2[((IOTA - 268) & 511)]) + fVec3[((IOTA - 273) & 511)]) + fVec4[((IOTA - 278) & 511)]) + fVec5[((IOTA - 281) & 511)])));
			fVbargraph32 = fRec32[0];
			output32[i] = fVbargraph32;
			fRec33[0] = (float)java.lang.Math.max((fRec33[1] - fConst0), (float)java.lang.Math.abs((fVec4[((IOTA - 274) & 511)] + (fVec3[((IOTA - 270) & 511)] + (fVec2[((IOTA - 266) & 511)] + (fVec1[((IOTA - 261) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec5[((IOTA - 276) & 511)])))))));
			fVbargraph33 = fRec33[0];
			output33[i] = fVbargraph33;
			fRec34[0] = (float)java.lang.Math.max((fRec34[1] - fConst0), (float)java.lang.Math.abs((((fVec2[((IOTA - 264) & 511)] + (fVec1[((IOTA - 260) & 511)] + (fVec0[((IOTA - 256) & 511)] + fVec3[((IOTA - 268) & 511)]))) + fVec4[((IOTA - 271) & 511)]) + fVec5[((IOTA - 273) & 511)])));
			fVbargraph34 = fRec34[0];
			output34[i] = fVbargraph34;
			fRec35[0] = (float)java.lang.Math.max((fRec35[1] - fConst0), (float)java.lang.Math.abs((((fTemp13 + fVec3[((IOTA - 266) & 511)]) + fVec4[((IOTA - 268) & 511)]) + fVec5[((IOTA - 270) & 511)])));
			fVbargraph35 = fRec35[0];
			output35[i] = fVbargraph35;
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			
		}
		
	}
	
};

