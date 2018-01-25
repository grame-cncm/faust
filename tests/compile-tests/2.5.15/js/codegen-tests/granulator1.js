
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.iConst1;
	this.iRec3 = new Int32Array(2);
	this.fHslider1;
	this.fHslider2;
	this.iRec4 = new Int32Array(2);
	this.iRec2 = new Int32Array(2);
	this.iVec0 = new Int32Array(2);
	this.fConst2;
	this.fConst3;
	this.fRec5 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.iVec1 = new Int32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.IOTA;
	this.fVec2 = new Float32Array(524288);
	this.iConst4;
	this.iVec3 = new Int32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
	this.iConst5;
	this.iVec4 = new Int32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.iConst6;
	this.iVec5 = new Int32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.iConst7;
	this.iVec6 = new Int32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fRec18 = new Float32Array(2);
	this.iConst8;
	this.iVec7 = new Int32Array(2);
	this.fRec23 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fRec21 = new Float32Array(2);
	this.iConst9;
	this.iVec8 = new Int32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.iConst10;
	this.iVec9 = new Int32Array(2);
	this.fRec29 = new Float32Array(2);
	this.fRec28 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.iConst11;
	this.iVec10 = new Int32Array(2);
	this.fRec32 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fRec30 = new Float32Array(2);
	this.iConst12;
	this.iVec11 = new Int32Array(2);
	this.fRec35 = new Float32Array(2);
	this.fRec34 = new Float32Array(2);
	this.fRec33 = new Float32Array(2);
	this.iConst13;
	this.iVec12 = new Int32Array(2);
	this.fRec38 = new Float32Array(2);
	this.fRec37 = new Float32Array(2);
	this.fRec36 = new Float32Array(2);
	this.iConst14;
	this.iVec13 = new Int32Array(2);
	this.fRec41 = new Float32Array(2);
	this.fRec40 = new Float32Array(2);
	this.fRec39 = new Float32Array(2);
	this.iConst15;
	this.iVec14 = new Int32Array(2);
	this.fRec44 = new Float32Array(2);
	this.fRec43 = new Float32Array(2);
	this.fRec42 = new Float32Array(2);
	this.iConst16;
	this.iVec15 = new Int32Array(2);
	this.fRec47 = new Float32Array(2);
	this.fRec46 = new Float32Array(2);
	this.fRec45 = new Float32Array(2);
	this.iConst17;
	this.iVec16 = new Int32Array(2);
	this.fRec50 = new Float32Array(2);
	this.fRec49 = new Float32Array(2);
	this.fRec48 = new Float32Array(2);
	this.iConst18;
	this.iVec17 = new Int32Array(2);
	this.fRec53 = new Float32Array(2);
	this.fRec52 = new Float32Array(2);
	this.fRec51 = new Float32Array(2);
	this.iConst19;
	this.iVec18 = new Int32Array(2);
	this.fRec56 = new Float32Array(2);
	this.fRec55 = new Float32Array(2);
	this.fRec54 = new Float32Array(2);
	this.iConst20;
	this.iVec19 = new Int32Array(2);
	this.fRec59 = new Float32Array(2);
	this.fRec58 = new Float32Array(2);
	this.fRec57 = new Float32Array(2);
	this.iConst21;
	this.iVec20 = new Int32Array(2);
	this.fRec62 = new Float32Array(2);
	this.fRec61 = new Float32Array(2);
	this.fRec60 = new Float32Array(2);
	this.iConst22;
	this.iVec21 = new Int32Array(2);
	this.fRec65 = new Float32Array(2);
	this.fRec64 = new Float32Array(2);
	this.fRec63 = new Float32Array(2);
	this.iConst23;
	this.iVec22 = new Int32Array(2);
	this.fRec68 = new Float32Array(2);
	this.fRec67 = new Float32Array(2);
	this.fRec66 = new Float32Array(2);
	this.iConst24;
	this.iVec23 = new Int32Array(2);
	this.fRec71 = new Float32Array(2);
	this.fRec70 = new Float32Array(2);
	this.fRec69 = new Float32Array(2);
	this.iConst25;
	this.iVec24 = new Int32Array(2);
	this.fRec74 = new Float32Array(2);
	this.fRec73 = new Float32Array(2);
	this.fRec72 = new Float32Array(2);
	this.iConst26;
	this.iVec25 = new Int32Array(2);
	this.fRec77 = new Float32Array(2);
	this.fRec76 = new Float32Array(2);
	this.fRec75 = new Float32Array(2);
	this.iConst27;
	this.iVec26 = new Int32Array(2);
	this.fRec80 = new Float32Array(2);
	this.fRec79 = new Float32Array(2);
	this.fRec78 = new Float32Array(2);
	this.iConst28;
	this.iVec27 = new Int32Array(2);
	this.fRec83 = new Float32Array(2);
	this.fRec82 = new Float32Array(2);
	this.fRec81 = new Float32Array(2);
	this.iConst29;
	this.iVec28 = new Int32Array(2);
	this.fRec86 = new Float32Array(2);
	this.fRec85 = new Float32Array(2);
	this.fRec84 = new Float32Array(2);
	this.iConst30;
	this.iVec29 = new Int32Array(2);
	this.fRec89 = new Float32Array(2);
	this.fRec88 = new Float32Array(2);
	this.fRec87 = new Float32Array(2);
	this.iConst31;
	this.iVec30 = new Int32Array(2);
	this.fRec92 = new Float32Array(2);
	this.fRec91 = new Float32Array(2);
	this.fRec90 = new Float32Array(2);
	this.iConst32;
	this.iVec31 = new Int32Array(2);
	this.fRec95 = new Float32Array(2);
	this.fRec94 = new Float32Array(2);
	this.fRec93 = new Float32Array(2);
	this.iConst33;
	this.iVec32 = new Int32Array(2);
	this.fRec98 = new Float32Array(2);
	this.fRec97 = new Float32Array(2);
	this.fRec96 = new Float32Array(2);
	this.iConst34;
	
	this.metadata = function(m) { 
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

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
		var rate;
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
	this.getOutputRate = function(channel) {
		var rate;
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
	
	this.classInit = function(samplingFreq) {
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.iConst1 = (0.00729927 * this.fConst0);
		this.fConst2 = (4 * ((20 - (400 / this.fConst0)) / this.fConst0));
		this.fConst3 = (3200 / mydsp_faustpower2_f(this.fConst0));
		this.iConst4 = ((0.3125 * this.fConst0) & 524287);
		this.iConst5 = ((0.625 * this.fConst0) & 524287);
		this.iConst6 = ((0.9375 * this.fConst0) & 524287);
		this.iConst7 = ((1.25 * this.fConst0) & 524287);
		this.iConst8 = ((1.5625 * this.fConst0) & 524287);
		this.iConst9 = ((1.875 * this.fConst0) & 524287);
		this.iConst10 = ((2.1875 * this.fConst0) & 524287);
		this.iConst11 = ((2.5 * this.fConst0) & 524287);
		this.iConst12 = ((2.8125 * this.fConst0) & 524287);
		this.iConst13 = ((3.125 * this.fConst0) & 524287);
		this.iConst14 = ((3.4375 * this.fConst0) & 524287);
		this.iConst15 = ((3.75 * this.fConst0) & 524287);
		this.iConst16 = ((4.0625 * this.fConst0) & 524287);
		this.iConst17 = ((4.375 * this.fConst0) & 524287);
		this.iConst18 = ((4.6875 * this.fConst0) & 524287);
		this.iConst19 = ((0.15625 * this.fConst0) & 524287);
		this.iConst20 = ((0.46875 * this.fConst0) & 524287);
		this.iConst21 = ((0.78125 * this.fConst0) & 524287);
		this.iConst22 = ((1.09375 * this.fConst0) & 524287);
		this.iConst23 = ((1.40625 * this.fConst0) & 524287);
		this.iConst24 = ((1.71875 * this.fConst0) & 524287);
		this.iConst25 = ((2.03125 * this.fConst0) & 524287);
		this.iConst26 = ((2.34375 * this.fConst0) & 524287);
		this.iConst27 = ((2.65625 * this.fConst0) & 524287);
		this.iConst28 = ((2.96875 * this.fConst0) & 524287);
		this.iConst29 = ((3.28125 * this.fConst0) & 524287);
		this.iConst30 = ((3.59375 * this.fConst0) & 524287);
		this.iConst31 = ((3.90625 * this.fConst0) & 524287);
		this.iConst32 = ((4.21875 * this.fConst0) & 524287);
		this.iConst33 = ((4.53125 * this.fConst0) & 524287);
		this.iConst34 = ((4.84375 * this.fConst0) & 524287);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0;
		this.fHslider1 = 0;
		this.fHslider2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec3[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iRec4[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.iRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.iVec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec0[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.iVec1[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec8[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec7[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec6[l10] = 0;
			
		}
		this.IOTA = 0;
		for (var l11 = 0; (l11 < 524288); l11 = (l11 + 1)) {
			this.fVec2[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.iVec3[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec11[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec10[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec9[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.iVec4[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec14[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec13[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec12[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.iVec5[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec17[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec16[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec15[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.iVec6[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec20[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec19[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec18[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.iVec7[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec23[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec22[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec21[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.iVec8[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec26[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec25[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec24[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.iVec9[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec29[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec28[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec27[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.iVec10[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec32[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec31[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec30[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.iVec11[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fRec35[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec34[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fRec33[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			this.iVec12[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fRec38[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fRec37[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			this.fRec36[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.iVec13[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec41[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			this.fRec40[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec39[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			this.iVec14[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec44[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			this.fRec43[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fRec42[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			this.iVec15[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			this.fRec47[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			this.fRec46[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			this.fRec45[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			this.iVec16[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			this.fRec50[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			this.fRec49[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			this.fRec48[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			this.iVec17[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			this.fRec53[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			this.fRec52[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			this.fRec51[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			this.iVec18[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			this.fRec56[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			this.fRec55[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			this.fRec54[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			this.iVec19[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			this.fRec59[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			this.fRec58[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			this.fRec57[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			this.iVec20[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			this.fRec62[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			this.fRec61[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			this.fRec60[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			this.iVec21[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			this.fRec65[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			this.fRec64[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			this.fRec63[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			this.iVec22[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			this.fRec68[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			this.fRec67[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			this.fRec66[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			this.iVec23[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			this.fRec71[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			this.fRec70[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			this.fRec69[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			this.iVec24[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			this.fRec74[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			this.fRec73[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			this.fRec72[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			this.iVec25[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			this.fRec77[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			this.fRec76[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			this.fRec75[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			this.iVec26[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			this.fRec80[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			this.fRec79[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			this.fRec78[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			this.iVec27[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			this.fRec83[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			this.fRec82[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			this.fRec81[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			this.iVec28[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			this.fRec86[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			this.fRec85[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			this.fRec84[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			this.iVec29[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			this.fRec89[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			this.fRec88[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			this.fRec87[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			this.iVec30[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			this.fRec92[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			this.fRec91[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			this.fRec90[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			this.iVec31[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			this.fRec95[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			this.fRec94[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			this.fRec93[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			this.iVec32[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			this.fRec98[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			this.fRec97[l130] = 0;
			
		}
		for (var l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			this.fRec96[l131] = 0;
			
		}
		
	}
	
	this.init = function(samplingFreq) {
		this.classInit(samplingFreq);
		this.instanceInit(samplingFreq);
	}
	
	this.instanceInit = function(samplingFreq) {
		this.instanceConstants(samplingFreq);
		this.instanceResetUserInterface();
		this.instanceClear();
	}
	
	this.buildUserInterface = function(ui_interface) {
		ui_interface.openVerticalBox("granulator1");
		ui_interface.addHorizontalSlider("lim1", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 10000, 1);
		ui_interface.addHorizontalSlider("lim2", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 10000, 1);
		ui_interface.addHorizontalSlider("vol", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = this.fHslider2;
		var fSlow3 = (0.5 * (fSlow1 + fSlow2));
		var fSlow4 = (2.32831e-10 * (fSlow2 - fSlow1));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.iRec3[0] = ((this.iRec3[1] + 1) % this.iConst1);
			var iTemp1 = (this.iRec3[0] == 0);
			this.iRec4[0] = ((1103515245 * this.iRec4[1]) + 12345);
			this.iRec2[0] = (((1 - iTemp1) * this.iRec2[1]) + (iTemp1 * (fSlow3 + (fSlow4 * this.iRec4[0]))));
			var iTemp2 = (this.iRec2[0] == 0);
			this.iVec0[0] = iTemp2;
			var iTemp3 = (((this.fRec0[1] > 0) | iTemp2) | this.iVec0[1]);
			this.fRec5[0] = ((this.fRec5[1] - this.fConst3) * iTemp3);
			this.fRec1[0] = (iTemp3 * (this.fConst2 + (this.fRec1[1] + this.fRec5[1])));
			this.fRec0[0] = max_f(0, this.fRec1[1]);
			var iTemp4 = (this.iRec2[0] == 2);
			this.iVec1[0] = iTemp4;
			var iTemp5 = (((this.fRec6[1] > 0) | iTemp4) | this.iVec1[1]);
			this.fRec8[0] = ((this.fRec8[1] - this.fConst3) * iTemp5);
			this.fRec7[0] = (iTemp5 * (this.fConst2 + (this.fRec7[1] + this.fRec8[1])));
			this.fRec6[0] = max_f(0, this.fRec7[1]);
			var fTemp6 = (fSlow0 * fTemp0);
			this.fVec2[(this.IOTA & 524287)] = fTemp6;
			var iTemp7 = (this.iRec2[0] == 4);
			this.iVec3[0] = iTemp7;
			var iTemp8 = (((this.fRec9[1] > 0) | iTemp7) | this.iVec3[1]);
			this.fRec11[0] = ((this.fRec11[1] - this.fConst3) * iTemp8);
			this.fRec10[0] = (iTemp8 * (this.fConst2 + (this.fRec10[1] + this.fRec11[1])));
			this.fRec9[0] = max_f(0, this.fRec10[1]);
			var iTemp9 = (this.iRec2[0] == 6);
			this.iVec4[0] = iTemp9;
			var iTemp10 = (((this.fRec12[1] > 0) | iTemp9) | this.iVec4[1]);
			this.fRec14[0] = ((this.fRec14[1] - this.fConst3) * iTemp10);
			this.fRec13[0] = (iTemp10 * (this.fConst2 + (this.fRec13[1] + this.fRec14[1])));
			this.fRec12[0] = max_f(0, this.fRec13[1]);
			var iTemp11 = (this.iRec2[0] == 8);
			this.iVec5[0] = iTemp11;
			var iTemp12 = (((this.fRec15[1] > 0) | iTemp11) | this.iVec5[1]);
			this.fRec17[0] = ((this.fRec17[1] - this.fConst3) * iTemp12);
			this.fRec16[0] = (iTemp12 * (this.fConst2 + (this.fRec16[1] + this.fRec17[1])));
			this.fRec15[0] = max_f(0, this.fRec16[1]);
			var iTemp13 = (this.iRec2[0] == 10);
			this.iVec6[0] = iTemp13;
			var iTemp14 = (((this.fRec18[1] > 0) | iTemp13) | this.iVec6[1]);
			this.fRec20[0] = ((this.fRec20[1] - this.fConst3) * iTemp14);
			this.fRec19[0] = (iTemp14 * (this.fConst2 + (this.fRec19[1] + this.fRec20[1])));
			this.fRec18[0] = max_f(0, this.fRec19[1]);
			var iTemp15 = (this.iRec2[0] == 12);
			this.iVec7[0] = iTemp15;
			var iTemp16 = (((this.fRec21[1] > 0) | iTemp15) | this.iVec7[1]);
			this.fRec23[0] = ((this.fRec23[1] - this.fConst3) * iTemp16);
			this.fRec22[0] = (iTemp16 * (this.fConst2 + (this.fRec22[1] + this.fRec23[1])));
			this.fRec21[0] = max_f(0, this.fRec22[1]);
			var iTemp17 = (this.iRec2[0] == 14);
			this.iVec8[0] = iTemp17;
			var iTemp18 = (((this.fRec24[1] > 0) | iTemp17) | this.iVec8[1]);
			this.fRec26[0] = ((this.fRec26[1] - this.fConst3) * iTemp18);
			this.fRec25[0] = (iTemp18 * (this.fConst2 + (this.fRec25[1] + this.fRec26[1])));
			this.fRec24[0] = max_f(0, this.fRec25[1]);
			var iTemp19 = (this.iRec2[0] == 16);
			this.iVec9[0] = iTemp19;
			var iTemp20 = (((this.fRec27[1] > 0) | iTemp19) | this.iVec9[1]);
			this.fRec29[0] = ((this.fRec29[1] - this.fConst3) * iTemp20);
			this.fRec28[0] = (iTemp20 * (this.fConst2 + (this.fRec28[1] + this.fRec29[1])));
			this.fRec27[0] = max_f(0, this.fRec28[1]);
			var iTemp21 = (this.iRec2[0] == 18);
			this.iVec10[0] = iTemp21;
			var iTemp22 = (((this.fRec30[1] > 0) | iTemp21) | this.iVec10[1]);
			this.fRec32[0] = ((this.fRec32[1] - this.fConst3) * iTemp22);
			this.fRec31[0] = (iTemp22 * (this.fConst2 + (this.fRec31[1] + this.fRec32[1])));
			this.fRec30[0] = max_f(0, this.fRec31[1]);
			var iTemp23 = (this.iRec2[0] == 20);
			this.iVec11[0] = iTemp23;
			var iTemp24 = (((this.fRec33[1] > 0) | iTemp23) | this.iVec11[1]);
			this.fRec35[0] = ((this.fRec35[1] - this.fConst3) * iTemp24);
			this.fRec34[0] = (iTemp24 * (this.fConst2 + (this.fRec34[1] + this.fRec35[1])));
			this.fRec33[0] = max_f(0, this.fRec34[1]);
			var iTemp25 = (this.iRec2[0] == 22);
			this.iVec12[0] = iTemp25;
			var iTemp26 = (((this.fRec36[1] > 0) | iTemp25) | this.iVec12[1]);
			this.fRec38[0] = ((this.fRec38[1] - this.fConst3) * iTemp26);
			this.fRec37[0] = (iTemp26 * (this.fConst2 + (this.fRec37[1] + this.fRec38[1])));
			this.fRec36[0] = max_f(0, this.fRec37[1]);
			var iTemp27 = (this.iRec2[0] == 24);
			this.iVec13[0] = iTemp27;
			var iTemp28 = (((this.fRec39[1] > 0) | iTemp27) | this.iVec13[1]);
			this.fRec41[0] = ((this.fRec41[1] - this.fConst3) * iTemp28);
			this.fRec40[0] = (iTemp28 * (this.fConst2 + (this.fRec40[1] + this.fRec41[1])));
			this.fRec39[0] = max_f(0, this.fRec40[1]);
			var iTemp29 = (this.iRec2[0] == 26);
			this.iVec14[0] = iTemp29;
			var iTemp30 = (((this.fRec42[1] > 0) | iTemp29) | this.iVec14[1]);
			this.fRec44[0] = ((this.fRec44[1] - this.fConst3) * iTemp30);
			this.fRec43[0] = (iTemp30 * (this.fConst2 + (this.fRec43[1] + this.fRec44[1])));
			this.fRec42[0] = max_f(0, this.fRec43[1]);
			var iTemp31 = (this.iRec2[0] == 28);
			this.iVec15[0] = iTemp31;
			var iTemp32 = (((this.fRec45[1] > 0) | iTemp31) | this.iVec15[1]);
			this.fRec47[0] = ((this.fRec47[1] - this.fConst3) * iTemp32);
			this.fRec46[0] = (iTemp32 * (this.fConst2 + (this.fRec46[1] + this.fRec47[1])));
			this.fRec45[0] = max_f(0, this.fRec46[1]);
			var iTemp33 = (this.iRec2[0] == 30);
			this.iVec16[0] = iTemp33;
			var iTemp34 = (((this.fRec48[1] > 0) | iTemp33) | this.iVec16[1]);
			this.fRec50[0] = ((this.fRec50[1] - this.fConst3) * iTemp34);
			this.fRec49[0] = (iTemp34 * (this.fConst2 + (this.fRec49[1] + this.fRec50[1])));
			this.fRec48[0] = max_f(0, this.fRec49[1]);
			output0[i] = ((((((((((((((((fSlow0 * (fTemp0 * this.fRec0[0])) + (this.fRec6[0] * this.fVec2[((this.IOTA - this.iConst4) & 524287)])) + (this.fRec9[0] * this.fVec2[((this.IOTA - this.iConst5) & 524287)])) + (this.fRec12[0] * this.fVec2[((this.IOTA - this.iConst6) & 524287)])) + (this.fRec15[0] * this.fVec2[((this.IOTA - this.iConst7) & 524287)])) + (this.fRec18[0] * this.fVec2[((this.IOTA - this.iConst8) & 524287)])) + (this.fRec21[0] * this.fVec2[((this.IOTA - this.iConst9) & 524287)])) + (this.fRec24[0] * this.fVec2[((this.IOTA - this.iConst10) & 524287)])) + (this.fRec27[0] * this.fVec2[((this.IOTA - this.iConst11) & 524287)])) + (this.fRec30[0] * this.fVec2[((this.IOTA - this.iConst12) & 524287)])) + (this.fRec33[0] * this.fVec2[((this.IOTA - this.iConst13) & 524287)])) + (this.fRec36[0] * this.fVec2[((this.IOTA - this.iConst14) & 524287)])) + (this.fRec39[0] * this.fVec2[((this.IOTA - this.iConst15) & 524287)])) + (this.fRec42[0] * this.fVec2[((this.IOTA - this.iConst16) & 524287)])) + (this.fRec45[0] * this.fVec2[((this.IOTA - this.iConst17) & 524287)])) + (this.fRec48[0] * this.fVec2[((this.IOTA - this.iConst18) & 524287)]));
			var iTemp35 = (this.iRec2[0] == 1);
			this.iVec17[0] = iTemp35;
			var iTemp36 = (((this.fRec51[1] > 0) | iTemp35) | this.iVec17[1]);
			this.fRec53[0] = ((this.fRec53[1] - this.fConst3) * iTemp36);
			this.fRec52[0] = (iTemp36 * (this.fConst2 + (this.fRec52[1] + this.fRec53[1])));
			this.fRec51[0] = max_f(0, this.fRec52[1]);
			var iTemp37 = (this.iRec2[0] == 3);
			this.iVec18[0] = iTemp37;
			var iTemp38 = (((this.fRec54[1] > 0) | iTemp37) | this.iVec18[1]);
			this.fRec56[0] = ((this.fRec56[1] - this.fConst3) * iTemp38);
			this.fRec55[0] = (iTemp38 * (this.fConst2 + (this.fRec55[1] + this.fRec56[1])));
			this.fRec54[0] = max_f(0, this.fRec55[1]);
			var iTemp39 = (this.iRec2[0] == 5);
			this.iVec19[0] = iTemp39;
			var iTemp40 = (((this.fRec57[1] > 0) | iTemp39) | this.iVec19[1]);
			this.fRec59[0] = ((this.fRec59[1] - this.fConst3) * iTemp40);
			this.fRec58[0] = (iTemp40 * (this.fConst2 + (this.fRec58[1] + this.fRec59[1])));
			this.fRec57[0] = max_f(0, this.fRec58[1]);
			var iTemp41 = (this.iRec2[0] == 7);
			this.iVec20[0] = iTemp41;
			var iTemp42 = (((this.fRec60[1] > 0) | iTemp41) | this.iVec20[1]);
			this.fRec62[0] = ((this.fRec62[1] - this.fConst3) * iTemp42);
			this.fRec61[0] = (iTemp42 * (this.fConst2 + (this.fRec61[1] + this.fRec62[1])));
			this.fRec60[0] = max_f(0, this.fRec61[1]);
			var iTemp43 = (this.iRec2[0] == 9);
			this.iVec21[0] = iTemp43;
			var iTemp44 = (((this.fRec63[1] > 0) | iTemp43) | this.iVec21[1]);
			this.fRec65[0] = ((this.fRec65[1] - this.fConst3) * iTemp44);
			this.fRec64[0] = (iTemp44 * (this.fConst2 + (this.fRec64[1] + this.fRec65[1])));
			this.fRec63[0] = max_f(0, this.fRec64[1]);
			var iTemp45 = (this.iRec2[0] == 11);
			this.iVec22[0] = iTemp45;
			var iTemp46 = (((this.fRec66[1] > 0) | iTemp45) | this.iVec22[1]);
			this.fRec68[0] = ((this.fRec68[1] - this.fConst3) * iTemp46);
			this.fRec67[0] = (iTemp46 * (this.fConst2 + (this.fRec67[1] + this.fRec68[1])));
			this.fRec66[0] = max_f(0, this.fRec67[1]);
			var iTemp47 = (this.iRec2[0] == 13);
			this.iVec23[0] = iTemp47;
			var iTemp48 = (((this.fRec69[1] > 0) | iTemp47) | this.iVec23[1]);
			this.fRec71[0] = ((this.fRec71[1] - this.fConst3) * iTemp48);
			this.fRec70[0] = (iTemp48 * (this.fConst2 + (this.fRec70[1] + this.fRec71[1])));
			this.fRec69[0] = max_f(0, this.fRec70[1]);
			var iTemp49 = (this.iRec2[0] == 15);
			this.iVec24[0] = iTemp49;
			var iTemp50 = (((this.fRec72[1] > 0) | iTemp49) | this.iVec24[1]);
			this.fRec74[0] = ((this.fRec74[1] - this.fConst3) * iTemp50);
			this.fRec73[0] = (iTemp50 * (this.fConst2 + (this.fRec73[1] + this.fRec74[1])));
			this.fRec72[0] = max_f(0, this.fRec73[1]);
			var iTemp51 = (this.iRec2[0] == 17);
			this.iVec25[0] = iTemp51;
			var iTemp52 = (((this.fRec75[1] > 0) | iTemp51) | this.iVec25[1]);
			this.fRec77[0] = ((this.fRec77[1] - this.fConst3) * iTemp52);
			this.fRec76[0] = (iTemp52 * (this.fConst2 + (this.fRec76[1] + this.fRec77[1])));
			this.fRec75[0] = max_f(0, this.fRec76[1]);
			var iTemp53 = (this.iRec2[0] == 19);
			this.iVec26[0] = iTemp53;
			var iTemp54 = (((this.fRec78[1] > 0) | iTemp53) | this.iVec26[1]);
			this.fRec80[0] = ((this.fRec80[1] - this.fConst3) * iTemp54);
			this.fRec79[0] = (iTemp54 * (this.fConst2 + (this.fRec79[1] + this.fRec80[1])));
			this.fRec78[0] = max_f(0, this.fRec79[1]);
			var iTemp55 = (this.iRec2[0] == 21);
			this.iVec27[0] = iTemp55;
			var iTemp56 = (((this.fRec81[1] > 0) | iTemp55) | this.iVec27[1]);
			this.fRec83[0] = ((this.fRec83[1] - this.fConst3) * iTemp56);
			this.fRec82[0] = (iTemp56 * (this.fConst2 + (this.fRec82[1] + this.fRec83[1])));
			this.fRec81[0] = max_f(0, this.fRec82[1]);
			var iTemp57 = (this.iRec2[0] == 23);
			this.iVec28[0] = iTemp57;
			var iTemp58 = (((this.fRec84[1] > 0) | iTemp57) | this.iVec28[1]);
			this.fRec86[0] = ((this.fRec86[1] - this.fConst3) * iTemp58);
			this.fRec85[0] = (iTemp58 * (this.fConst2 + (this.fRec85[1] + this.fRec86[1])));
			this.fRec84[0] = max_f(0, this.fRec85[1]);
			var iTemp59 = (this.iRec2[0] == 25);
			this.iVec29[0] = iTemp59;
			var iTemp60 = (((this.fRec87[1] > 0) | iTemp59) | this.iVec29[1]);
			this.fRec89[0] = ((this.fRec89[1] - this.fConst3) * iTemp60);
			this.fRec88[0] = (iTemp60 * (this.fConst2 + (this.fRec88[1] + this.fRec89[1])));
			this.fRec87[0] = max_f(0, this.fRec88[1]);
			var iTemp61 = (this.iRec2[0] == 27);
			this.iVec30[0] = iTemp61;
			var iTemp62 = (((this.fRec90[1] > 0) | iTemp61) | this.iVec30[1]);
			this.fRec92[0] = ((this.fRec92[1] - this.fConst3) * iTemp62);
			this.fRec91[0] = (iTemp62 * (this.fConst2 + (this.fRec91[1] + this.fRec92[1])));
			this.fRec90[0] = max_f(0, this.fRec91[1]);
			var iTemp63 = (this.iRec2[0] == 29);
			this.iVec31[0] = iTemp63;
			var iTemp64 = (((this.fRec93[1] > 0) | iTemp63) | this.iVec31[1]);
			this.fRec95[0] = ((this.fRec95[1] - this.fConst3) * iTemp64);
			this.fRec94[0] = (iTemp64 * (this.fConst2 + (this.fRec94[1] + this.fRec95[1])));
			this.fRec93[0] = max_f(0, this.fRec94[1]);
			var iTemp65 = (this.iRec2[0] == 31);
			this.iVec32[0] = iTemp65;
			var iTemp66 = (((this.fRec96[1] > 0) | iTemp65) | this.iVec32[1]);
			this.fRec98[0] = ((this.fRec98[1] - this.fConst3) * iTemp66);
			this.fRec97[0] = (iTemp66 * (this.fConst2 + (this.fRec97[1] + this.fRec98[1])));
			this.fRec96[0] = max_f(0, this.fRec97[1]);
			output1[i] = ((((((((((((((((this.fRec51[0] * this.fVec2[((this.IOTA - this.iConst19) & 524287)]) + (this.fRec54[0] * this.fVec2[((this.IOTA - this.iConst20) & 524287)])) + (this.fRec57[0] * this.fVec2[((this.IOTA - this.iConst21) & 524287)])) + (this.fRec60[0] * this.fVec2[((this.IOTA - this.iConst22) & 524287)])) + (this.fRec63[0] * this.fVec2[((this.IOTA - this.iConst23) & 524287)])) + (this.fRec66[0] * this.fVec2[((this.IOTA - this.iConst24) & 524287)])) + (this.fRec69[0] * this.fVec2[((this.IOTA - this.iConst25) & 524287)])) + (this.fRec72[0] * this.fVec2[((this.IOTA - this.iConst26) & 524287)])) + (this.fRec75[0] * this.fVec2[((this.IOTA - this.iConst27) & 524287)])) + (this.fRec78[0] * this.fVec2[((this.IOTA - this.iConst28) & 524287)])) + (this.fRec81[0] * this.fVec2[((this.IOTA - this.iConst29) & 524287)])) + (this.fRec84[0] * this.fVec2[((this.IOTA - this.iConst30) & 524287)])) + (this.fRec87[0] * this.fVec2[((this.IOTA - this.iConst31) & 524287)])) + (this.fRec90[0] * this.fVec2[((this.IOTA - this.iConst32) & 524287)])) + (this.fRec93[0] * this.fVec2[((this.IOTA - this.iConst33) & 524287)])) + (this.fRec96[0] * this.fVec2[((this.IOTA - this.iConst34) & 524287)]));
			this.iRec3[1] = this.iRec3[0];
			this.iRec4[1] = this.iRec4[0];
			this.iRec2[1] = this.iRec2[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.iVec1[1] = this.iVec1[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec6[1] = this.fRec6[0];
			this.IOTA = (this.IOTA + 1);
			this.iVec3[1] = this.iVec3[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec9[1] = this.fRec9[0];
			this.iVec4[1] = this.iVec4[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[1] = this.fRec12[0];
			this.iVec5[1] = this.iVec5[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[1] = this.fRec15[0];
			this.iVec6[1] = this.iVec6[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec18[1] = this.fRec18[0];
			this.iVec7[1] = this.iVec7[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec21[1] = this.fRec21[0];
			this.iVec8[1] = this.iVec8[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec24[1] = this.fRec24[0];
			this.iVec9[1] = this.iVec9[0];
			this.fRec29[1] = this.fRec29[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec27[1] = this.fRec27[0];
			this.iVec10[1] = this.iVec10[0];
			this.fRec32[1] = this.fRec32[0];
			this.fRec31[1] = this.fRec31[0];
			this.fRec30[1] = this.fRec30[0];
			this.iVec11[1] = this.iVec11[0];
			this.fRec35[1] = this.fRec35[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec33[1] = this.fRec33[0];
			this.iVec12[1] = this.iVec12[0];
			this.fRec38[1] = this.fRec38[0];
			this.fRec37[1] = this.fRec37[0];
			this.fRec36[1] = this.fRec36[0];
			this.iVec13[1] = this.iVec13[0];
			this.fRec41[1] = this.fRec41[0];
			this.fRec40[1] = this.fRec40[0];
			this.fRec39[1] = this.fRec39[0];
			this.iVec14[1] = this.iVec14[0];
			this.fRec44[1] = this.fRec44[0];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[1] = this.fRec42[0];
			this.iVec15[1] = this.iVec15[0];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[1] = this.fRec46[0];
			this.fRec45[1] = this.fRec45[0];
			this.iVec16[1] = this.iVec16[0];
			this.fRec50[1] = this.fRec50[0];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[1] = this.fRec48[0];
			this.iVec17[1] = this.iVec17[0];
			this.fRec53[1] = this.fRec53[0];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[1] = this.fRec51[0];
			this.iVec18[1] = this.iVec18[0];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[1] = this.fRec55[0];
			this.fRec54[1] = this.fRec54[0];
			this.iVec19[1] = this.iVec19[0];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[1] = this.fRec58[0];
			this.fRec57[1] = this.fRec57[0];
			this.iVec20[1] = this.iVec20[0];
			this.fRec62[1] = this.fRec62[0];
			this.fRec61[1] = this.fRec61[0];
			this.fRec60[1] = this.fRec60[0];
			this.iVec21[1] = this.iVec21[0];
			this.fRec65[1] = this.fRec65[0];
			this.fRec64[1] = this.fRec64[0];
			this.fRec63[1] = this.fRec63[0];
			this.iVec22[1] = this.iVec22[0];
			this.fRec68[1] = this.fRec68[0];
			this.fRec67[1] = this.fRec67[0];
			this.fRec66[1] = this.fRec66[0];
			this.iVec23[1] = this.iVec23[0];
			this.fRec71[1] = this.fRec71[0];
			this.fRec70[1] = this.fRec70[0];
			this.fRec69[1] = this.fRec69[0];
			this.iVec24[1] = this.iVec24[0];
			this.fRec74[1] = this.fRec74[0];
			this.fRec73[1] = this.fRec73[0];
			this.fRec72[1] = this.fRec72[0];
			this.iVec25[1] = this.iVec25[0];
			this.fRec77[1] = this.fRec77[0];
			this.fRec76[1] = this.fRec76[0];
			this.fRec75[1] = this.fRec75[0];
			this.iVec26[1] = this.iVec26[0];
			this.fRec80[1] = this.fRec80[0];
			this.fRec79[1] = this.fRec79[0];
			this.fRec78[1] = this.fRec78[0];
			this.iVec27[1] = this.iVec27[0];
			this.fRec83[1] = this.fRec83[0];
			this.fRec82[1] = this.fRec82[0];
			this.fRec81[1] = this.fRec81[0];
			this.iVec28[1] = this.iVec28[0];
			this.fRec86[1] = this.fRec86[0];
			this.fRec85[1] = this.fRec85[0];
			this.fRec84[1] = this.fRec84[0];
			this.iVec29[1] = this.iVec29[0];
			this.fRec89[1] = this.fRec89[0];
			this.fRec88[1] = this.fRec88[0];
			this.fRec87[1] = this.fRec87[0];
			this.iVec30[1] = this.iVec30[0];
			this.fRec92[1] = this.fRec92[0];
			this.fRec91[1] = this.fRec91[0];
			this.fRec90[1] = this.fRec90[0];
			this.iVec31[1] = this.iVec31[0];
			this.fRec95[1] = this.fRec95[0];
			this.fRec94[1] = this.fRec94[0];
			this.fRec93[1] = this.fRec93[0];
			this.iVec32[1] = this.iVec32[0];
			this.fRec98[1] = this.fRec98[0];
			this.fRec97[1] = this.fRec97[0];
			this.fRec96[1] = this.fRec96[0];
			
		}
		
	}
	
}

