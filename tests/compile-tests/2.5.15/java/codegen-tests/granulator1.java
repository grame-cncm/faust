/* ------------------------------------------------------------
name: "granulator1"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	int fSamplingFreq;
	float fConst0;
	int iConst1;
	int iRec3[] = new int[2];
	float fHslider1;
	float fHslider2;
	int iRec4[] = new int[2];
	int iRec2[] = new int[2];
	int iVec0[] = new int[2];
	float fConst2;
	float fConst3;
	float fRec5[] = new float[2];
	float fRec1[] = new float[2];
	float fRec0[] = new float[2];
	int iVec1[] = new int[2];
	float fRec8[] = new float[2];
	float fRec7[] = new float[2];
	float fRec6[] = new float[2];
	int IOTA;
	float fVec2[] = new float[524288];
	int iConst4;
	int iVec3[] = new int[2];
	float fRec11[] = new float[2];
	float fRec10[] = new float[2];
	float fRec9[] = new float[2];
	int iConst5;
	int iVec4[] = new int[2];
	float fRec14[] = new float[2];
	float fRec13[] = new float[2];
	float fRec12[] = new float[2];
	int iConst6;
	int iVec5[] = new int[2];
	float fRec17[] = new float[2];
	float fRec16[] = new float[2];
	float fRec15[] = new float[2];
	int iConst7;
	int iVec6[] = new int[2];
	float fRec20[] = new float[2];
	float fRec19[] = new float[2];
	float fRec18[] = new float[2];
	int iConst8;
	int iVec7[] = new int[2];
	float fRec23[] = new float[2];
	float fRec22[] = new float[2];
	float fRec21[] = new float[2];
	int iConst9;
	int iVec8[] = new int[2];
	float fRec26[] = new float[2];
	float fRec25[] = new float[2];
	float fRec24[] = new float[2];
	int iConst10;
	int iVec9[] = new int[2];
	float fRec29[] = new float[2];
	float fRec28[] = new float[2];
	float fRec27[] = new float[2];
	int iConst11;
	int iVec10[] = new int[2];
	float fRec32[] = new float[2];
	float fRec31[] = new float[2];
	float fRec30[] = new float[2];
	int iConst12;
	int iVec11[] = new int[2];
	float fRec35[] = new float[2];
	float fRec34[] = new float[2];
	float fRec33[] = new float[2];
	int iConst13;
	int iVec12[] = new int[2];
	float fRec38[] = new float[2];
	float fRec37[] = new float[2];
	float fRec36[] = new float[2];
	int iConst14;
	int iVec13[] = new int[2];
	float fRec41[] = new float[2];
	float fRec40[] = new float[2];
	float fRec39[] = new float[2];
	int iConst15;
	int iVec14[] = new int[2];
	float fRec44[] = new float[2];
	float fRec43[] = new float[2];
	float fRec42[] = new float[2];
	int iConst16;
	int iVec15[] = new int[2];
	float fRec47[] = new float[2];
	float fRec46[] = new float[2];
	float fRec45[] = new float[2];
	int iConst17;
	int iVec16[] = new int[2];
	float fRec50[] = new float[2];
	float fRec49[] = new float[2];
	float fRec48[] = new float[2];
	int iConst18;
	int iVec17[] = new int[2];
	float fRec53[] = new float[2];
	float fRec52[] = new float[2];
	float fRec51[] = new float[2];
	int iConst19;
	int iVec18[] = new int[2];
	float fRec56[] = new float[2];
	float fRec55[] = new float[2];
	float fRec54[] = new float[2];
	int iConst20;
	int iVec19[] = new int[2];
	float fRec59[] = new float[2];
	float fRec58[] = new float[2];
	float fRec57[] = new float[2];
	int iConst21;
	int iVec20[] = new int[2];
	float fRec62[] = new float[2];
	float fRec61[] = new float[2];
	float fRec60[] = new float[2];
	int iConst22;
	int iVec21[] = new int[2];
	float fRec65[] = new float[2];
	float fRec64[] = new float[2];
	float fRec63[] = new float[2];
	int iConst23;
	int iVec22[] = new int[2];
	float fRec68[] = new float[2];
	float fRec67[] = new float[2];
	float fRec66[] = new float[2];
	int iConst24;
	int iVec23[] = new int[2];
	float fRec71[] = new float[2];
	float fRec70[] = new float[2];
	float fRec69[] = new float[2];
	int iConst25;
	int iVec24[] = new int[2];
	float fRec74[] = new float[2];
	float fRec73[] = new float[2];
	float fRec72[] = new float[2];
	int iConst26;
	int iVec25[] = new int[2];
	float fRec77[] = new float[2];
	float fRec76[] = new float[2];
	float fRec75[] = new float[2];
	int iConst27;
	int iVec26[] = new int[2];
	float fRec80[] = new float[2];
	float fRec79[] = new float[2];
	float fRec78[] = new float[2];
	int iConst28;
	int iVec27[] = new int[2];
	float fRec83[] = new float[2];
	float fRec82[] = new float[2];
	float fRec81[] = new float[2];
	int iConst29;
	int iVec28[] = new int[2];
	float fRec86[] = new float[2];
	float fRec85[] = new float[2];
	float fRec84[] = new float[2];
	int iConst30;
	int iVec29[] = new int[2];
	float fRec89[] = new float[2];
	float fRec88[] = new float[2];
	float fRec87[] = new float[2];
	int iConst31;
	int iVec30[] = new int[2];
	float fRec92[] = new float[2];
	float fRec91[] = new float[2];
	float fRec90[] = new float[2];
	int iConst32;
	int iVec31[] = new int[2];
	float fRec95[] = new float[2];
	float fRec94[] = new float[2];
	float fRec93[] = new float[2];
	int iConst33;
	int iVec32[] = new int[2];
	float fRec98[] = new float[2];
	float fRec97[] = new float[2];
	float fRec96[] = new float[2];
	int iConst34;
	
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
		m.declare("name", "granulator1");
	}

	int getNumInputs() {
		return 1;
		
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
		iConst1 = (int)(0.00729927002f * fConst0);
		fConst2 = (4.0f * ((20.0f - (400.0f / fConst0)) / fConst0));
		fConst3 = (3200.0f / mydsp_faustpower2_f(fConst0));
		iConst4 = ((int)(0.3125f * fConst0) & 524287);
		iConst5 = ((int)(0.625f * fConst0) & 524287);
		iConst6 = ((int)(0.9375f * fConst0) & 524287);
		iConst7 = ((int)(1.25f * fConst0) & 524287);
		iConst8 = ((int)(1.5625f * fConst0) & 524287);
		iConst9 = ((int)(1.875f * fConst0) & 524287);
		iConst10 = ((int)(2.1875f * fConst0) & 524287);
		iConst11 = ((int)(2.5f * fConst0) & 524287);
		iConst12 = ((int)(2.8125f * fConst0) & 524287);
		iConst13 = ((int)(3.125f * fConst0) & 524287);
		iConst14 = ((int)(3.4375f * fConst0) & 524287);
		iConst15 = ((int)(3.75f * fConst0) & 524287);
		iConst16 = ((int)(4.0625f * fConst0) & 524287);
		iConst17 = ((int)(4.375f * fConst0) & 524287);
		iConst18 = ((int)(4.6875f * fConst0) & 524287);
		iConst19 = ((int)(0.15625f * fConst0) & 524287);
		iConst20 = ((int)(0.46875f * fConst0) & 524287);
		iConst21 = ((int)(0.78125f * fConst0) & 524287);
		iConst22 = ((int)(1.09375f * fConst0) & 524287);
		iConst23 = ((int)(1.40625f * fConst0) & 524287);
		iConst24 = ((int)(1.71875f * fConst0) & 524287);
		iConst25 = ((int)(2.03125f * fConst0) & 524287);
		iConst26 = ((int)(2.34375f * fConst0) & 524287);
		iConst27 = ((int)(2.65625f * fConst0) & 524287);
		iConst28 = ((int)(2.96875f * fConst0) & 524287);
		iConst29 = ((int)(3.28125f * fConst0) & 524287);
		iConst30 = ((int)(3.59375f * fConst0) & 524287);
		iConst31 = ((int)(3.90625f * fConst0) & 524287);
		iConst32 = ((int)(4.21875f * fConst0) & 524287);
		iConst33 = ((int)(4.53125f * fConst0) & 524287);
		iConst34 = ((int)(4.84375f * fConst0) & 524287);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.0f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec3[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec4[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec2[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iVec0[l3] = 0;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iVec1[l7] = 0;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec6[l10] = 0.0f;
			
		}
		IOTA = 0;
		for (int l11 = 0; (l11 < 524288); l11 = (l11 + 1)) {
			fVec2[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iVec3[l12] = 0;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec10[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec9[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			iVec4[l16] = 0;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec14[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec13[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec12[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			iVec5[l20] = 0;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec17[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec16[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec15[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			iVec6[l24] = 0;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec20[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec19[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec18[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			iVec7[l28] = 0;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec23[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec22[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec21[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			iVec8[l32] = 0;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec26[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec25[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec24[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			iVec9[l36] = 0;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec29[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec28[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec27[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			iVec10[l40] = 0;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec32[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec31[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec30[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			iVec11[l44] = 0;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec35[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec34[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec33[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			iVec12[l48] = 0;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec38[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec37[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec36[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			iVec13[l52] = 0;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec41[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec40[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec39[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			iVec14[l56] = 0;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec44[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec43[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec42[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			iVec15[l60] = 0;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec47[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec46[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec45[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			iVec16[l64] = 0;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec50[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec49[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec48[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			iVec17[l68] = 0;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec53[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec52[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec51[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			iVec18[l72] = 0;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec56[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec55[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec54[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			iVec19[l76] = 0;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec59[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec58[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec57[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			iVec20[l80] = 0;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec62[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fRec61[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec60[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			iVec21[l84] = 0;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec65[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec64[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec63[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			iVec22[l88] = 0;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fRec68[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec67[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fRec66[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			iVec23[l92] = 0;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec71[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec70[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			fRec69[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			iVec24[l96] = 0;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec74[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec73[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec72[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			iVec25[l100] = 0;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec77[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec76[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			fRec75[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			iVec26[l104] = 0;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec80[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec79[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec78[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			iVec27[l108] = 0;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			fRec83[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fRec82[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec81[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			iVec28[l112] = 0;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec86[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec85[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec84[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			iVec29[l116] = 0;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec89[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fRec88[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec87[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			iVec30[l120] = 0;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fRec92[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec91[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec90[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			iVec31[l124] = 0;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec95[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec94[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec93[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			iVec32[l128] = 0;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec98[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec97[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			fRec96[l131] = 0.0f;
			
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
		ui_interface.openVerticalBox("granulator1");
		ui_interface.addHorizontalSlider("lim1", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 10000.0f, 1.0f);
		ui_interface.addHorizontalSlider("lim2", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 10000.0f, 1.0f);
		ui_interface.addHorizontalSlider("vol", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = fHslider1;
		float fSlow2 = fHslider2;
		float fSlow3 = (0.5f * (fSlow1 + fSlow2));
		float fSlow4 = (2.32830644e-10f * (fSlow2 - fSlow1));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			iRec3[0] = ((iRec3[1] + 1) % iConst1);
			int iTemp1 = (iRec3[0] == 0);
			iRec4[0] = ((1103515245 * iRec4[1]) + 12345);
			iRec2[0] = (((1 - iTemp1) * iRec2[1]) + (iTemp1 * (int)(fSlow3 + (fSlow4 * (float)iRec4[0]))));
			int iTemp2 = (iRec2[0] == 0);
			iVec0[0] = iTemp2;
			int iTemp3 = (((((fRec0[1] > 0.0f))?1:0) | iTemp2) | iVec0[1]);
			fRec5[0] = ((fRec5[1] - fConst3) * (float)iTemp3);
			fRec1[0] = ((float)iTemp3 * (fConst2 + (fRec1[1] + fRec5[1])));
			fRec0[0] = (float)java.lang.Math.max(0.0f, fRec1[1]);
			int iTemp4 = (iRec2[0] == 2);
			iVec1[0] = iTemp4;
			int iTemp5 = (((((fRec6[1] > 0.0f))?1:0) | iTemp4) | iVec1[1]);
			fRec8[0] = ((fRec8[1] - fConst3) * (float)iTemp5);
			fRec7[0] = ((float)iTemp5 * (fConst2 + (fRec7[1] + fRec8[1])));
			fRec6[0] = (float)java.lang.Math.max(0.0f, fRec7[1]);
			float fTemp6 = (fSlow0 * fTemp0);
			fVec2[(IOTA & 524287)] = fTemp6;
			int iTemp7 = (iRec2[0] == 4);
			iVec3[0] = iTemp7;
			int iTemp8 = (((((fRec9[1] > 0.0f))?1:0) | iTemp7) | iVec3[1]);
			fRec11[0] = ((fRec11[1] - fConst3) * (float)iTemp8);
			fRec10[0] = ((float)iTemp8 * (fConst2 + (fRec10[1] + fRec11[1])));
			fRec9[0] = (float)java.lang.Math.max(0.0f, fRec10[1]);
			int iTemp9 = (iRec2[0] == 6);
			iVec4[0] = iTemp9;
			int iTemp10 = (((((fRec12[1] > 0.0f))?1:0) | iTemp9) | iVec4[1]);
			fRec14[0] = ((fRec14[1] - fConst3) * (float)iTemp10);
			fRec13[0] = ((float)iTemp10 * (fConst2 + (fRec13[1] + fRec14[1])));
			fRec12[0] = (float)java.lang.Math.max(0.0f, fRec13[1]);
			int iTemp11 = (iRec2[0] == 8);
			iVec5[0] = iTemp11;
			int iTemp12 = (((((fRec15[1] > 0.0f))?1:0) | iTemp11) | iVec5[1]);
			fRec17[0] = ((fRec17[1] - fConst3) * (float)iTemp12);
			fRec16[0] = ((float)iTemp12 * (fConst2 + (fRec16[1] + fRec17[1])));
			fRec15[0] = (float)java.lang.Math.max(0.0f, fRec16[1]);
			int iTemp13 = (iRec2[0] == 10);
			iVec6[0] = iTemp13;
			int iTemp14 = (((((fRec18[1] > 0.0f))?1:0) | iTemp13) | iVec6[1]);
			fRec20[0] = ((fRec20[1] - fConst3) * (float)iTemp14);
			fRec19[0] = ((float)iTemp14 * (fConst2 + (fRec19[1] + fRec20[1])));
			fRec18[0] = (float)java.lang.Math.max(0.0f, fRec19[1]);
			int iTemp15 = (iRec2[0] == 12);
			iVec7[0] = iTemp15;
			int iTemp16 = (((((fRec21[1] > 0.0f))?1:0) | iTemp15) | iVec7[1]);
			fRec23[0] = ((fRec23[1] - fConst3) * (float)iTemp16);
			fRec22[0] = ((float)iTemp16 * (fConst2 + (fRec22[1] + fRec23[1])));
			fRec21[0] = (float)java.lang.Math.max(0.0f, fRec22[1]);
			int iTemp17 = (iRec2[0] == 14);
			iVec8[0] = iTemp17;
			int iTemp18 = (((((fRec24[1] > 0.0f))?1:0) | iTemp17) | iVec8[1]);
			fRec26[0] = ((fRec26[1] - fConst3) * (float)iTemp18);
			fRec25[0] = ((float)iTemp18 * (fConst2 + (fRec25[1] + fRec26[1])));
			fRec24[0] = (float)java.lang.Math.max(0.0f, fRec25[1]);
			int iTemp19 = (iRec2[0] == 16);
			iVec9[0] = iTemp19;
			int iTemp20 = (((((fRec27[1] > 0.0f))?1:0) | iTemp19) | iVec9[1]);
			fRec29[0] = ((fRec29[1] - fConst3) * (float)iTemp20);
			fRec28[0] = ((float)iTemp20 * (fConst2 + (fRec28[1] + fRec29[1])));
			fRec27[0] = (float)java.lang.Math.max(0.0f, fRec28[1]);
			int iTemp21 = (iRec2[0] == 18);
			iVec10[0] = iTemp21;
			int iTemp22 = (((((fRec30[1] > 0.0f))?1:0) | iTemp21) | iVec10[1]);
			fRec32[0] = ((fRec32[1] - fConst3) * (float)iTemp22);
			fRec31[0] = ((float)iTemp22 * (fConst2 + (fRec31[1] + fRec32[1])));
			fRec30[0] = (float)java.lang.Math.max(0.0f, fRec31[1]);
			int iTemp23 = (iRec2[0] == 20);
			iVec11[0] = iTemp23;
			int iTemp24 = (((((fRec33[1] > 0.0f))?1:0) | iTemp23) | iVec11[1]);
			fRec35[0] = ((fRec35[1] - fConst3) * (float)iTemp24);
			fRec34[0] = ((float)iTemp24 * (fConst2 + (fRec34[1] + fRec35[1])));
			fRec33[0] = (float)java.lang.Math.max(0.0f, fRec34[1]);
			int iTemp25 = (iRec2[0] == 22);
			iVec12[0] = iTemp25;
			int iTemp26 = (((((fRec36[1] > 0.0f))?1:0) | iTemp25) | iVec12[1]);
			fRec38[0] = ((fRec38[1] - fConst3) * (float)iTemp26);
			fRec37[0] = ((float)iTemp26 * (fConst2 + (fRec37[1] + fRec38[1])));
			fRec36[0] = (float)java.lang.Math.max(0.0f, fRec37[1]);
			int iTemp27 = (iRec2[0] == 24);
			iVec13[0] = iTemp27;
			int iTemp28 = (((((fRec39[1] > 0.0f))?1:0) | iTemp27) | iVec13[1]);
			fRec41[0] = ((fRec41[1] - fConst3) * (float)iTemp28);
			fRec40[0] = ((float)iTemp28 * (fConst2 + (fRec40[1] + fRec41[1])));
			fRec39[0] = (float)java.lang.Math.max(0.0f, fRec40[1]);
			int iTemp29 = (iRec2[0] == 26);
			iVec14[0] = iTemp29;
			int iTemp30 = (((((fRec42[1] > 0.0f))?1:0) | iTemp29) | iVec14[1]);
			fRec44[0] = ((fRec44[1] - fConst3) * (float)iTemp30);
			fRec43[0] = ((float)iTemp30 * (fConst2 + (fRec43[1] + fRec44[1])));
			fRec42[0] = (float)java.lang.Math.max(0.0f, fRec43[1]);
			int iTemp31 = (iRec2[0] == 28);
			iVec15[0] = iTemp31;
			int iTemp32 = (((((fRec45[1] > 0.0f))?1:0) | iTemp31) | iVec15[1]);
			fRec47[0] = ((fRec47[1] - fConst3) * (float)iTemp32);
			fRec46[0] = ((float)iTemp32 * (fConst2 + (fRec46[1] + fRec47[1])));
			fRec45[0] = (float)java.lang.Math.max(0.0f, fRec46[1]);
			int iTemp33 = (iRec2[0] == 30);
			iVec16[0] = iTemp33;
			int iTemp34 = (((((fRec48[1] > 0.0f))?1:0) | iTemp33) | iVec16[1]);
			fRec50[0] = ((fRec50[1] - fConst3) * (float)iTemp34);
			fRec49[0] = ((float)iTemp34 * (fConst2 + (fRec49[1] + fRec50[1])));
			fRec48[0] = (float)java.lang.Math.max(0.0f, fRec49[1]);
			output0[i] = ((((((((((((((((fSlow0 * (fTemp0 * fRec0[0])) + (fRec6[0] * fVec2[((IOTA - iConst4) & 524287)])) + (fRec9[0] * fVec2[((IOTA - iConst5) & 524287)])) + (fRec12[0] * fVec2[((IOTA - iConst6) & 524287)])) + (fRec15[0] * fVec2[((IOTA - iConst7) & 524287)])) + (fRec18[0] * fVec2[((IOTA - iConst8) & 524287)])) + (fRec21[0] * fVec2[((IOTA - iConst9) & 524287)])) + (fRec24[0] * fVec2[((IOTA - iConst10) & 524287)])) + (fRec27[0] * fVec2[((IOTA - iConst11) & 524287)])) + (fRec30[0] * fVec2[((IOTA - iConst12) & 524287)])) + (fRec33[0] * fVec2[((IOTA - iConst13) & 524287)])) + (fRec36[0] * fVec2[((IOTA - iConst14) & 524287)])) + (fRec39[0] * fVec2[((IOTA - iConst15) & 524287)])) + (fRec42[0] * fVec2[((IOTA - iConst16) & 524287)])) + (fRec45[0] * fVec2[((IOTA - iConst17) & 524287)])) + (fRec48[0] * fVec2[((IOTA - iConst18) & 524287)]));
			int iTemp35 = (iRec2[0] == 1);
			iVec17[0] = iTemp35;
			int iTemp36 = (((((fRec51[1] > 0.0f))?1:0) | iTemp35) | iVec17[1]);
			fRec53[0] = ((fRec53[1] - fConst3) * (float)iTemp36);
			fRec52[0] = ((float)iTemp36 * (fConst2 + (fRec52[1] + fRec53[1])));
			fRec51[0] = (float)java.lang.Math.max(0.0f, fRec52[1]);
			int iTemp37 = (iRec2[0] == 3);
			iVec18[0] = iTemp37;
			int iTemp38 = (((((fRec54[1] > 0.0f))?1:0) | iTemp37) | iVec18[1]);
			fRec56[0] = ((fRec56[1] - fConst3) * (float)iTemp38);
			fRec55[0] = ((float)iTemp38 * (fConst2 + (fRec55[1] + fRec56[1])));
			fRec54[0] = (float)java.lang.Math.max(0.0f, fRec55[1]);
			int iTemp39 = (iRec2[0] == 5);
			iVec19[0] = iTemp39;
			int iTemp40 = (((((fRec57[1] > 0.0f))?1:0) | iTemp39) | iVec19[1]);
			fRec59[0] = ((fRec59[1] - fConst3) * (float)iTemp40);
			fRec58[0] = ((float)iTemp40 * (fConst2 + (fRec58[1] + fRec59[1])));
			fRec57[0] = (float)java.lang.Math.max(0.0f, fRec58[1]);
			int iTemp41 = (iRec2[0] == 7);
			iVec20[0] = iTemp41;
			int iTemp42 = (((((fRec60[1] > 0.0f))?1:0) | iTemp41) | iVec20[1]);
			fRec62[0] = ((fRec62[1] - fConst3) * (float)iTemp42);
			fRec61[0] = ((float)iTemp42 * (fConst2 + (fRec61[1] + fRec62[1])));
			fRec60[0] = (float)java.lang.Math.max(0.0f, fRec61[1]);
			int iTemp43 = (iRec2[0] == 9);
			iVec21[0] = iTemp43;
			int iTemp44 = (((((fRec63[1] > 0.0f))?1:0) | iTemp43) | iVec21[1]);
			fRec65[0] = ((fRec65[1] - fConst3) * (float)iTemp44);
			fRec64[0] = ((float)iTemp44 * (fConst2 + (fRec64[1] + fRec65[1])));
			fRec63[0] = (float)java.lang.Math.max(0.0f, fRec64[1]);
			int iTemp45 = (iRec2[0] == 11);
			iVec22[0] = iTemp45;
			int iTemp46 = (((((fRec66[1] > 0.0f))?1:0) | iTemp45) | iVec22[1]);
			fRec68[0] = ((fRec68[1] - fConst3) * (float)iTemp46);
			fRec67[0] = ((float)iTemp46 * (fConst2 + (fRec67[1] + fRec68[1])));
			fRec66[0] = (float)java.lang.Math.max(0.0f, fRec67[1]);
			int iTemp47 = (iRec2[0] == 13);
			iVec23[0] = iTemp47;
			int iTemp48 = (((((fRec69[1] > 0.0f))?1:0) | iTemp47) | iVec23[1]);
			fRec71[0] = ((fRec71[1] - fConst3) * (float)iTemp48);
			fRec70[0] = ((float)iTemp48 * (fConst2 + (fRec70[1] + fRec71[1])));
			fRec69[0] = (float)java.lang.Math.max(0.0f, fRec70[1]);
			int iTemp49 = (iRec2[0] == 15);
			iVec24[0] = iTemp49;
			int iTemp50 = (((((fRec72[1] > 0.0f))?1:0) | iTemp49) | iVec24[1]);
			fRec74[0] = ((fRec74[1] - fConst3) * (float)iTemp50);
			fRec73[0] = ((float)iTemp50 * (fConst2 + (fRec73[1] + fRec74[1])));
			fRec72[0] = (float)java.lang.Math.max(0.0f, fRec73[1]);
			int iTemp51 = (iRec2[0] == 17);
			iVec25[0] = iTemp51;
			int iTemp52 = (((((fRec75[1] > 0.0f))?1:0) | iTemp51) | iVec25[1]);
			fRec77[0] = ((fRec77[1] - fConst3) * (float)iTemp52);
			fRec76[0] = ((float)iTemp52 * (fConst2 + (fRec76[1] + fRec77[1])));
			fRec75[0] = (float)java.lang.Math.max(0.0f, fRec76[1]);
			int iTemp53 = (iRec2[0] == 19);
			iVec26[0] = iTemp53;
			int iTemp54 = (((((fRec78[1] > 0.0f))?1:0) | iTemp53) | iVec26[1]);
			fRec80[0] = ((fRec80[1] - fConst3) * (float)iTemp54);
			fRec79[0] = ((float)iTemp54 * (fConst2 + (fRec79[1] + fRec80[1])));
			fRec78[0] = (float)java.lang.Math.max(0.0f, fRec79[1]);
			int iTemp55 = (iRec2[0] == 21);
			iVec27[0] = iTemp55;
			int iTemp56 = (((((fRec81[1] > 0.0f))?1:0) | iTemp55) | iVec27[1]);
			fRec83[0] = ((fRec83[1] - fConst3) * (float)iTemp56);
			fRec82[0] = ((float)iTemp56 * (fConst2 + (fRec82[1] + fRec83[1])));
			fRec81[0] = (float)java.lang.Math.max(0.0f, fRec82[1]);
			int iTemp57 = (iRec2[0] == 23);
			iVec28[0] = iTemp57;
			int iTemp58 = (((((fRec84[1] > 0.0f))?1:0) | iTemp57) | iVec28[1]);
			fRec86[0] = ((fRec86[1] - fConst3) * (float)iTemp58);
			fRec85[0] = ((float)iTemp58 * (fConst2 + (fRec85[1] + fRec86[1])));
			fRec84[0] = (float)java.lang.Math.max(0.0f, fRec85[1]);
			int iTemp59 = (iRec2[0] == 25);
			iVec29[0] = iTemp59;
			int iTemp60 = (((((fRec87[1] > 0.0f))?1:0) | iTemp59) | iVec29[1]);
			fRec89[0] = ((fRec89[1] - fConst3) * (float)iTemp60);
			fRec88[0] = ((float)iTemp60 * (fConst2 + (fRec88[1] + fRec89[1])));
			fRec87[0] = (float)java.lang.Math.max(0.0f, fRec88[1]);
			int iTemp61 = (iRec2[0] == 27);
			iVec30[0] = iTemp61;
			int iTemp62 = (((((fRec90[1] > 0.0f))?1:0) | iTemp61) | iVec30[1]);
			fRec92[0] = ((fRec92[1] - fConst3) * (float)iTemp62);
			fRec91[0] = ((float)iTemp62 * (fConst2 + (fRec91[1] + fRec92[1])));
			fRec90[0] = (float)java.lang.Math.max(0.0f, fRec91[1]);
			int iTemp63 = (iRec2[0] == 29);
			iVec31[0] = iTemp63;
			int iTemp64 = (((((fRec93[1] > 0.0f))?1:0) | iTemp63) | iVec31[1]);
			fRec95[0] = ((fRec95[1] - fConst3) * (float)iTemp64);
			fRec94[0] = ((float)iTemp64 * (fConst2 + (fRec94[1] + fRec95[1])));
			fRec93[0] = (float)java.lang.Math.max(0.0f, fRec94[1]);
			int iTemp65 = (iRec2[0] == 31);
			iVec32[0] = iTemp65;
			int iTemp66 = (((((fRec96[1] > 0.0f))?1:0) | iTemp65) | iVec32[1]);
			fRec98[0] = ((fRec98[1] - fConst3) * (float)iTemp66);
			fRec97[0] = ((float)iTemp66 * (fConst2 + (fRec97[1] + fRec98[1])));
			fRec96[0] = (float)java.lang.Math.max(0.0f, fRec97[1]);
			output1[i] = ((((((((((((((((fRec51[0] * fVec2[((IOTA - iConst19) & 524287)]) + (fRec54[0] * fVec2[((IOTA - iConst20) & 524287)])) + (fRec57[0] * fVec2[((IOTA - iConst21) & 524287)])) + (fRec60[0] * fVec2[((IOTA - iConst22) & 524287)])) + (fRec63[0] * fVec2[((IOTA - iConst23) & 524287)])) + (fRec66[0] * fVec2[((IOTA - iConst24) & 524287)])) + (fRec69[0] * fVec2[((IOTA - iConst25) & 524287)])) + (fRec72[0] * fVec2[((IOTA - iConst26) & 524287)])) + (fRec75[0] * fVec2[((IOTA - iConst27) & 524287)])) + (fRec78[0] * fVec2[((IOTA - iConst28) & 524287)])) + (fRec81[0] * fVec2[((IOTA - iConst29) & 524287)])) + (fRec84[0] * fVec2[((IOTA - iConst30) & 524287)])) + (fRec87[0] * fVec2[((IOTA - iConst31) & 524287)])) + (fRec90[0] * fVec2[((IOTA - iConst32) & 524287)])) + (fRec93[0] * fVec2[((IOTA - iConst33) & 524287)])) + (fRec96[0] * fVec2[((IOTA - iConst34) & 524287)]));
			iRec3[1] = iRec3[0];
			iRec4[1] = iRec4[0];
			iRec2[1] = iRec2[0];
			iVec0[1] = iVec0[0];
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			iVec1[1] = iVec1[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			IOTA = (IOTA + 1);
			iVec3[1] = iVec3[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			iVec4[1] = iVec4[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			iVec5[1] = iVec5[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			iVec6[1] = iVec6[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			iVec7[1] = iVec7[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			iVec8[1] = iVec8[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			iVec9[1] = iVec9[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			iVec10[1] = iVec10[0];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			iVec11[1] = iVec11[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			iVec12[1] = iVec12[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			iVec13[1] = iVec13[0];
			fRec41[1] = fRec41[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			iVec14[1] = iVec14[0];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			iVec15[1] = iVec15[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			iVec16[1] = iVec16[0];
			fRec50[1] = fRec50[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			iVec17[1] = iVec17[0];
			fRec53[1] = fRec53[0];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			iVec18[1] = iVec18[0];
			fRec56[1] = fRec56[0];
			fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
			iVec19[1] = iVec19[0];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec57[1] = fRec57[0];
			iVec20[1] = iVec20[0];
			fRec62[1] = fRec62[0];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			iVec21[1] = iVec21[0];
			fRec65[1] = fRec65[0];
			fRec64[1] = fRec64[0];
			fRec63[1] = fRec63[0];
			iVec22[1] = iVec22[0];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec66[1] = fRec66[0];
			iVec23[1] = iVec23[0];
			fRec71[1] = fRec71[0];
			fRec70[1] = fRec70[0];
			fRec69[1] = fRec69[0];
			iVec24[1] = iVec24[0];
			fRec74[1] = fRec74[0];
			fRec73[1] = fRec73[0];
			fRec72[1] = fRec72[0];
			iVec25[1] = iVec25[0];
			fRec77[1] = fRec77[0];
			fRec76[1] = fRec76[0];
			fRec75[1] = fRec75[0];
			iVec26[1] = iVec26[0];
			fRec80[1] = fRec80[0];
			fRec79[1] = fRec79[0];
			fRec78[1] = fRec78[0];
			iVec27[1] = iVec27[0];
			fRec83[1] = fRec83[0];
			fRec82[1] = fRec82[0];
			fRec81[1] = fRec81[0];
			iVec28[1] = iVec28[0];
			fRec86[1] = fRec86[0];
			fRec85[1] = fRec85[0];
			fRec84[1] = fRec84[0];
			iVec29[1] = iVec29[0];
			fRec89[1] = fRec89[0];
			fRec88[1] = fRec88[0];
			fRec87[1] = fRec87[0];
			iVec30[1] = iVec30[0];
			fRec92[1] = fRec92[0];
			fRec91[1] = fRec91[0];
			fRec90[1] = fRec90[0];
			iVec31[1] = iVec31[0];
			fRec95[1] = fRec95[0];
			fRec94[1] = fRec94[0];
			fRec93[1] = fRec93[0];
			iVec32[1] = iVec32[0];
			fRec98[1] = fRec98[0];
			fRec97[1] = fRec97[0];
			fRec96[1] = fRec96[0];
			
		}
		
	}
	
};

