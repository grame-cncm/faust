
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);

function mydsp() {
	
	this.iRec10 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider0;
	this.fRec29 = new Float32Array(2);
	this.fHslider1;
	this.fHslider2;
	this.fRec30 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fRec33 = new Float32Array(4);
	this.IOTA;
	this.fRec34 = new Float32Array(2048);
	this.fVec0 = new Float32Array(2);
	this.fHslider3;
	this.iVec1 = new Int32Array(2);
	this.fVec2 = new Float32Array(2);
	this.fRec32 = new Float32Array(2048);
	this.fRec21 = new Float32Array(2);
	this.fRec17 = new Float32Array(2048);
	this.fRec19 = new Float32Array(2);
	this.fRec15 = new Float32Array(4);
	this.iRec6 = new Int32Array(2);
	this.fRec2 = new Float32Array(2048);
	this.fRec0 = new Float32Array(2);
	this.iRec46 = new Int32Array(2);
	this.fHslider4;
	this.fHslider5;
	this.fRec65 = new Float32Array(2);
	this.fRec61 = new Float32Array(2);
	this.fRec66 = new Float32Array(2);
	this.fHslider6;
	this.iVec3 = new Int32Array(2);
	this.fRec68 = new Float32Array(4);
	this.fRec69 = new Float32Array(2048);
	this.fVec4 = new Float32Array(2);
	this.fVec5 = new Float32Array(2);
	this.fRec67 = new Float32Array(2048);
	this.fRec57 = new Float32Array(2);
	this.fRec53 = new Float32Array(2048);
	this.fRec55 = new Float32Array(2);
	this.fRec51 = new Float32Array(4);
	this.iRec42 = new Int32Array(2);
	this.fRec38 = new Float32Array(2048);
	this.fRec36 = new Float32Array(2);
	this.iRec81 = new Int32Array(2);
	this.fHslider7;
	this.fHslider8;
	this.fRec100 = new Float32Array(2);
	this.fRec96 = new Float32Array(2);
	this.fRec101 = new Float32Array(2);
	this.fHslider9;
	this.iVec6 = new Int32Array(2);
	this.fRec103 = new Float32Array(4);
	this.fRec104 = new Float32Array(2048);
	this.fVec7 = new Float32Array(2);
	this.fVec8 = new Float32Array(2);
	this.fRec102 = new Float32Array(2048);
	this.fRec92 = new Float32Array(2);
	this.fRec88 = new Float32Array(2048);
	this.fRec90 = new Float32Array(2);
	this.fRec86 = new Float32Array(4);
	this.iRec77 = new Int32Array(2);
	this.fRec73 = new Float32Array(2048);
	this.fRec71 = new Float32Array(2);
	this.iRec116 = new Int32Array(2);
	this.fHslider10;
	this.fHslider11;
	this.fRec135 = new Float32Array(2);
	this.fRec131 = new Float32Array(2);
	this.fRec136 = new Float32Array(2);
	this.fHslider12;
	this.iVec9 = new Int32Array(2);
	this.fRec138 = new Float32Array(4);
	this.fRec139 = new Float32Array(2048);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fRec137 = new Float32Array(2048);
	this.fRec127 = new Float32Array(2);
	this.fRec123 = new Float32Array(2048);
	this.fRec125 = new Float32Array(2);
	this.fRec121 = new Float32Array(4);
	this.iRec112 = new Int32Array(2);
	this.fRec108 = new Float32Array(2048);
	this.fRec106 = new Float32Array(2);
	this.iRec151 = new Int32Array(2);
	this.fHslider13;
	this.fHslider14;
	this.fRec170 = new Float32Array(2);
	this.fRec166 = new Float32Array(2);
	this.fRec171 = new Float32Array(2);
	this.fHslider15;
	this.iVec12 = new Int32Array(2);
	this.fRec173 = new Float32Array(4);
	this.fRec174 = new Float32Array(2048);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fRec172 = new Float32Array(2048);
	this.fRec162 = new Float32Array(2);
	this.fRec158 = new Float32Array(2048);
	this.fRec160 = new Float32Array(2);
	this.fRec156 = new Float32Array(4);
	this.iRec147 = new Int32Array(2);
	this.fRec143 = new Float32Array(2048);
	this.fRec141 = new Float32Array(2);
	this.iRec186 = new Int32Array(2);
	this.fHslider16;
	this.fHslider17;
	this.fRec205 = new Float32Array(2);
	this.fRec201 = new Float32Array(2);
	this.fRec206 = new Float32Array(2);
	this.fHslider18;
	this.iVec15 = new Int32Array(2);
	this.fRec208 = new Float32Array(4);
	this.fRec209 = new Float32Array(2048);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fRec207 = new Float32Array(2048);
	this.fRec197 = new Float32Array(2);
	this.fRec193 = new Float32Array(2048);
	this.fRec195 = new Float32Array(2);
	this.fRec191 = new Float32Array(4);
	this.iRec182 = new Int32Array(2);
	this.fRec178 = new Float32Array(2048);
	this.fRec176 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'7',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'2',  'Keyboard 0 - Number of Keys':'14',   'Keyboard 1 - Number of Keys':'14',  'Keyboard 2 - Number of Keys':'14',  'Keyboard 3 - Number of Keys':'14',  'Keyboard 4 - Number of Keys':'14',  'Keyboard 5 - Number of Keys':'14',  'Keyboard 6 - Number of Keys':'6',  'Keyboard 0 - Lowest Key':'52',  'Keyboard 1 - Lowest Key':'57',  'Keyboard 2 - Lowest Key':'62',  'Keyboard 3 - Lowest Key':'67',  'Keyboard 4 - Lowest Key':'71',  'Keyboard 5 - Lowest Key':'76',  'Keyboard 0 - Send Keyboard Freq':'1',  'Keyboard 1 - Send Keyboard Freq':'1',  'Keyboard 2 - Send Keyboard Freq':'1',  'Keyboard 3 - Send Keyboard Freq':'1',  'Keyboard 4 - Send Keyboard Freq':'1',  'Keyboard 5 - Send Keyboard Freq':'1',  'Keyboard 6 - Piano Keyboard':'0',  'Keyboard 6 - Send Key Status':'1',  'Keyboard 6 - Key 0 - Label':'S0',  'Keyboard 6 - Key 1 - Label':'S1',  'Keyboard 6 - Key 2 - Label':'S2',  'Keyboard 6 - Key 3 - Label':'S3',  'Keyboard 6 - Key 4 - Label':'S4',  'Keyboard 6 - Key 5 - Label':'S5' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "acGuitar");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
		var rate;
		switch (channel) {
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
		this.fConst1 = (0.00882353 * this.fConst0);
		this.fConst2 = (0.00147059 * this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 164.8;
		this.fHslider2 = 1;
		this.fHslider3 = 0;
		this.fHslider4 = 220;
		this.fHslider5 = 1;
		this.fHslider6 = 0;
		this.fHslider7 = 293.7;
		this.fHslider8 = 1;
		this.fHslider9 = 0;
		this.fHslider10 = 392;
		this.fHslider11 = 1;
		this.fHslider12 = 0;
		this.fHslider13 = 493.9;
		this.fHslider14 = 1;
		this.fHslider15 = 0;
		this.fHslider16 = 659.2;
		this.fHslider17 = 1;
		this.fHslider18 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec10[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec29[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec30[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec25[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec31[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			this.fRec33[l5] = 0;
			
		}
		this.IOTA = 0;
		for (var l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			this.fRec34[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec0[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.iVec1[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec2[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
			this.fRec32[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec21[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2048); l12 = (l12 + 1)) {
			this.fRec17[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec19[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 4); l14 = (l14 + 1)) {
			this.fRec15[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.iRec6[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2048); l16 = (l16 + 1)) {
			this.fRec2[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec0[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.iRec46[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fRec65[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec61[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec66[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.iVec3[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 4); l23 = (l23 + 1)) {
			this.fRec68[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			this.fRec69[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec4[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fVec5[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			this.fRec67[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec57[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			this.fRec53[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec55[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			this.fRec51[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.iRec42[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			this.fRec38[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec36[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.iRec81[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec100[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec96[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec101[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.iVec6[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 4); l40 = (l40 + 1)) {
			this.fRec103[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2048); l41 = (l41 + 1)) {
			this.fRec104[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fVec7[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fVec8[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2048); l44 = (l44 + 1)) {
			this.fRec102[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fRec92[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2048); l46 = (l46 + 1)) {
			this.fRec88[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fRec90[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			this.fRec86[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.iRec77[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			this.fRec73[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			this.fRec71[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.iRec116[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec135[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			this.fRec131[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec136[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			this.iVec9[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 4); l57 = (l57 + 1)) {
			this.fRec138[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2048); l58 = (l58 + 1)) {
			this.fRec139[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fVec10[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			this.fVec11[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2048); l61 = (l61 + 1)) {
			this.fRec137[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			this.fRec127[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 2048); l63 = (l63 + 1)) {
			this.fRec123[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			this.fRec125[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 4); l65 = (l65 + 1)) {
			this.fRec121[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			this.iRec112[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 2048); l67 = (l67 + 1)) {
			this.fRec108[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			this.fRec106[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			this.iRec151[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			this.fRec170[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			this.fRec166[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			this.fRec171[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			this.iVec12[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 4); l74 = (l74 + 1)) {
			this.fRec173[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 2048); l75 = (l75 + 1)) {
			this.fRec174[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			this.fVec13[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			this.fVec14[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2048); l78 = (l78 + 1)) {
			this.fRec172[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			this.fRec162[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 2048); l80 = (l80 + 1)) {
			this.fRec158[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			this.fRec160[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 4); l82 = (l82 + 1)) {
			this.fRec156[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			this.iRec147[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 2048); l84 = (l84 + 1)) {
			this.fRec143[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			this.fRec141[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			this.iRec186[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			this.fRec205[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			this.fRec201[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			this.fRec206[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			this.iVec15[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 4); l91 = (l91 + 1)) {
			this.fRec208[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 2048); l92 = (l92 + 1)) {
			this.fRec209[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			this.fVec16[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			this.fVec17[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 2048); l95 = (l95 + 1)) {
			this.fRec207[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			this.fRec197[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 2048); l97 = (l97 + 1)) {
			this.fRec193[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			this.fRec195[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 4); l99 = (l99 + 1)) {
			this.fRec191[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			this.iRec182[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 2048); l101 = (l101 + 1)) {
			this.fRec178[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			this.fRec176[l102] = 0;
			
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
		ui_interface.openVerticalBox("acGuitar");
		ui_interface.addHorizontalSlider("kb0bend", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb0freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 164.8, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb1bend", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb1freq", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 220, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb2bend", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb2freq", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 293.7, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb3bend", function handler(obj) { function setval(val) { obj.fHslider11 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb3freq", function handler(obj) { function setval(val) { obj.fHslider10 = val; } return setval; }(this), 392, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb4bend", function handler(obj) { function setval(val) { obj.fHslider14 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb4freq", function handler(obj) { function setval(val) { obj.fHslider13 = val; } return setval; }(this), 493.9, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb5bend", function handler(obj) { function setval(val) { obj.fHslider17 = val; } return setval; }(this), 1, 0, 10, 0.01);
		ui_interface.addHorizontalSlider("kb5freq", function handler(obj) { function setval(val) { obj.fHslider16 = val; } return setval; }(this), 659.2, 20, 10000, 0.01);
		ui_interface.addHorizontalSlider("kb6k0status", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb6k1status", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb6k2status", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb6k3status", function handler(obj) { function setval(val) { obj.fHslider12 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb6k4status", function handler(obj) { function setval(val) { obj.fHslider15 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.addHorizontalSlider("kb6k5status", function handler(obj) { function setval(val) { obj.fHslider18 = val; } return setval; }(this), 0, 0, 1, 1);
		ui_interface.declare("fHslider0", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("pluckPosition", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * this.fHslider0);
		var fSlow1 = (0.34 / (this.fHslider1 * this.fHslider2));
		var fSlow2 = this.fHslider3;
		var iSlow3 = ((fSlow2 == 1) | (fSlow2 == 4));
		var fSlow4 = (0.34 / (this.fHslider4 * this.fHslider5));
		var fSlow5 = this.fHslider6;
		var iSlow6 = ((fSlow5 == 1) | (fSlow5 == 4));
		var fSlow7 = (0.34 / (this.fHslider7 * this.fHslider8));
		var fSlow8 = this.fHslider9;
		var iSlow9 = ((fSlow8 == 1) | (fSlow8 == 4));
		var fSlow10 = (0.34 / (this.fHslider10 * this.fHslider11));
		var fSlow11 = this.fHslider12;
		var iSlow12 = ((fSlow11 == 1) | (fSlow11 == 4));
		var fSlow13 = (0.34 / (this.fHslider13 * this.fHslider14));
		var fSlow14 = this.fHslider15;
		var iSlow15 = ((fSlow14 == 1) | (fSlow14 == 4));
		var fSlow16 = (0.34 / (this.fHslider16 * this.fHslider17));
		var fSlow17 = this.fHslider18;
		var iSlow18 = ((fSlow17 == 1) | (fSlow17 == 4));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec10[0] = 0;
			var iRec11 = this.iRec10[1];
			var fRec14 = (this.iRec6[1] - (0.997844 * ((0.7 * this.fRec15[2]) + (0.15 * (this.fRec15[1] + this.fRec15[3])))));
			this.fRec29[0] = (fSlow0 + (0.999 * this.fRec29[1]));
			var fTemp0 = (1 - this.fRec29[0]);
			this.fRec30[0] = (fSlow1 + (0.999 * this.fRec30[1]));
			var fTemp1 = (this.fRec30[0] + -0.11);
			var fTemp2 = (this.fConst2 * (fTemp0 * fTemp1));
			var fTemp3 = (fTemp2 + -1.49999);
			var iTemp4 = fTemp3;
			var iTemp5 = min_f(this.fConst1, max_i(0, iTemp4));
			var fTemp6 = Math.floor(fTemp3);
			var fTemp7 = (fTemp2 + (-1 - fTemp6));
			var fTemp8 = (0 - fTemp7);
			var fTemp9 = (fTemp2 + (-2 - fTemp6));
			var fTemp10 = (0 - (0.5 * fTemp9));
			var fTemp11 = (fTemp2 + (-3 - fTemp6));
			var fTemp12 = (0 - (0.333333 * fTemp11));
			var fTemp13 = (fTemp2 + (-4 - fTemp6));
			var fTemp14 = (0 - (0.25 * fTemp13));
			var fTemp15 = (fTemp2 - fTemp6);
			var iTemp16 = min_f(this.fConst1, max_i(0, (iTemp4 + 2)));
			var fTemp17 = (0 - fTemp11);
			var fTemp18 = (0 - (0.5 * fTemp13));
			var iTemp19 = min_f(this.fConst1, max_i(0, (iTemp4 + 1)));
			var fTemp20 = (0 - fTemp9);
			var fTemp21 = (0 - (0.5 * fTemp11));
			var fTemp22 = (0 - (0.333333 * fTemp13));
			var fTemp23 = (fTemp7 * fTemp9);
			var iTemp24 = min_f(this.fConst1, max_i(0, (iTemp4 + 3)));
			var fTemp25 = (0 - fTemp13);
			var fTemp26 = (fTemp23 * fTemp11);
			var iTemp27 = min_f(this.fConst1, max_i(0, (iTemp4 + 4)));
			this.fRec25[0] = (((((this.fRec2[((this.IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((0.5 * (((fTemp7 * this.fRec2[((this.IOTA - (iTemp16 + 1)) & 2047)]) * fTemp17) * fTemp18)) + (((this.fRec2[((this.IOTA - (iTemp19 + 1)) & 2047)] * fTemp20) * fTemp21) * fTemp22)) + (0.166667 * ((fTemp23 * this.fRec2[((this.IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416667 * (fTemp26 * this.fRec2[((this.IOTA - (iTemp27 + 1)) & 2047)])))));
			this.fRec31[0] = ((0.4 * this.fRec31[1]) + (0.6 * this.fRec25[1]));
			var fRec26 = this.fRec31[0];
			this.fRec33[0] = this.fRec0[1];
			this.fRec34[(this.IOTA & 2047)] = (0 - (0.997844 * ((0.7 * this.fRec33[2]) + (0.15 * (this.fRec33[1] + this.fRec33[3])))));
			var iRec35 = 0;
			var fTemp28 = (this.fConst2 * (this.fRec29[0] * fTemp1));
			var fTemp29 = (fTemp28 + -1.49999);
			var iTemp30 = fTemp29;
			var iTemp31 = min_f(this.fConst1, max_i(0, iTemp30));
			var fTemp32 = Math.floor(fTemp29);
			var fTemp33 = (fTemp28 + (-1 - fTemp32));
			var fTemp34 = (0 - fTemp33);
			var fTemp35 = (fTemp28 + (-2 - fTemp32));
			var fTemp36 = (0 - (0.5 * fTemp35));
			var fTemp37 = (fTemp28 + (-3 - fTemp32));
			var fTemp38 = (0 - (0.333333 * fTemp37));
			var fTemp39 = (fTemp28 + (-4 - fTemp32));
			var fTemp40 = (0 - (0.25 * fTemp39));
			var fTemp41 = (fTemp28 - fTemp32);
			var iTemp42 = min_f(this.fConst1, max_i(0, (iTemp30 + 2)));
			var fTemp43 = (0 - fTemp37);
			var fTemp44 = (0 - (0.5 * fTemp39));
			var iTemp45 = min_f(this.fConst1, max_i(0, (iTemp30 + 1)));
			var fTemp46 = (0 - fTemp35);
			var fTemp47 = (0 - (0.5 * fTemp37));
			var fTemp48 = (0 - (0.333333 * fTemp39));
			var fTemp49 = (fTemp33 * fTemp35);
			var iTemp50 = min_f(this.fConst1, max_i(0, (iTemp30 + 3)));
			var fTemp51 = (0 - fTemp39);
			var fTemp52 = (fTemp49 * fTemp37);
			var iTemp53 = min_f(this.fConst1, max_i(0, (iTemp30 + 4)));
			this.fVec0[0] = (((((this.fRec34[((this.IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((0.5 * (((fTemp33 * this.fRec34[((this.IOTA - (iTemp42 + 2)) & 2047)]) * fTemp43) * fTemp44)) + (((this.fRec34[((this.IOTA - (iTemp45 + 2)) & 2047)] * fTemp46) * fTemp47) * fTemp48)) + (0.166667 * ((fTemp49 * this.fRec34[((this.IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416667 * (fTemp52 * this.fRec34[((this.IOTA - (iTemp53 + 2)) & 2047)])))));
			this.iVec1[0] = iSlow3;
			var iTemp54 = ((iSlow3 - this.iVec1[1]) > 0);
			this.fVec2[0] = (this.fVec0[1] + iTemp54);
			this.fRec32[(this.IOTA & 2047)] = ((0.4 * this.fRec32[((this.IOTA - 1) & 2047)]) + (0.6 * this.fVec2[1]));
			var fRec27 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * this.fRec32[((this.IOTA - iTemp5) & 2047)]) + (fTemp15 * ((0.0416667 * (fTemp26 * this.fRec32[((this.IOTA - iTemp27) & 2047)])) + (((((fTemp20 * fTemp21) * fTemp22) * this.fRec32[((this.IOTA - iTemp19) & 2047)]) + (0.5 * (((fTemp7 * fTemp17) * fTemp18) * this.fRec32[((this.IOTA - iTemp16) & 2047)]))) + (0.166667 * ((fTemp23 * fTemp25) * this.fRec32[((this.IOTA - iTemp24) & 2047)]))))));
			var iRec28 = iRec35;
			this.fRec21[0] = fRec26;
			var fRec22 = (iTemp54 + this.fRec21[1]);
			var fRec23 = fRec27;
			var iRec24 = iRec28;
			this.fRec17[(this.IOTA & 2047)] = fRec22;
			var fRec18 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * this.fRec17[((this.IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * (((0.166667 * ((fTemp49 * fTemp51) * this.fRec17[((this.IOTA - (iTemp50 + 1)) & 2047)])) + ((((fTemp46 * fTemp47) * fTemp48) * this.fRec17[((this.IOTA - (iTemp45 + 1)) & 2047)]) + (0.5 * (((fTemp33 * fTemp43) * fTemp44) * this.fRec17[((this.IOTA - (iTemp42 + 1)) & 2047)])))) + (0.0416667 * (fTemp52 * this.fRec17[((this.IOTA - (iTemp53 + 1)) & 2047)])))));
			this.fRec19[0] = fRec23;
			var iRec20 = iRec24;
			this.fRec15[0] = this.fRec19[1];
			var iRec16 = iRec20;
			var fRec12 = this.fRec15[1];
			var fRec13 = (iRec16 + this.fRec15[1]);
			this.iRec6[0] = iRec11;
			var fRec7 = fRec14;
			var fRec8 = fRec12;
			var fRec9 = fRec13;
			this.fRec2[(this.IOTA & 2047)] = fRec7;
			var fRec3 = fRec18;
			var fRec4 = fRec8;
			var fRec5 = fRec9;
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			this.iRec46[0] = 0;
			var iRec47 = this.iRec46[1];
			var fRec50 = (this.iRec42[1] - (0.997844 * ((0.7 * this.fRec51[2]) + (0.15 * (this.fRec51[1] + this.fRec51[3])))));
			this.fRec65[0] = (fSlow4 + (0.999 * this.fRec65[1]));
			var fTemp55 = (this.fRec65[0] + -0.11);
			var fTemp56 = (this.fConst2 * (fTemp0 * fTemp55));
			var fTemp57 = (fTemp56 + -1.49999);
			var iTemp58 = fTemp57;
			var iTemp59 = min_f(this.fConst1, max_i(0, iTemp58));
			var fTemp60 = Math.floor(fTemp57);
			var fTemp61 = (fTemp56 + (-1 - fTemp60));
			var fTemp62 = (0 - fTemp61);
			var fTemp63 = (fTemp56 + (-2 - fTemp60));
			var fTemp64 = (0 - (0.5 * fTemp63));
			var fTemp65 = (fTemp56 + (-3 - fTemp60));
			var fTemp66 = (0 - (0.333333 * fTemp65));
			var fTemp67 = (fTemp56 + (-4 - fTemp60));
			var fTemp68 = (0 - (0.25 * fTemp67));
			var fTemp69 = (fTemp56 - fTemp60);
			var iTemp70 = min_f(this.fConst1, max_i(0, (iTemp58 + 2)));
			var fTemp71 = (0 - fTemp65);
			var fTemp72 = (0 - (0.5 * fTemp67));
			var iTemp73 = min_f(this.fConst1, max_i(0, (iTemp58 + 1)));
			var fTemp74 = (0 - fTemp63);
			var fTemp75 = (0 - (0.5 * fTemp65));
			var fTemp76 = (0 - (0.333333 * fTemp67));
			var fTemp77 = (fTemp61 * fTemp63);
			var iTemp78 = min_f(this.fConst1, max_i(0, (iTemp58 + 3)));
			var fTemp79 = (0 - fTemp67);
			var fTemp80 = (fTemp77 * fTemp65);
			var iTemp81 = min_f(this.fConst1, max_i(0, (iTemp58 + 4)));
			this.fRec61[0] = (((((this.fRec38[((this.IOTA - (iTemp59 + 1)) & 2047)] * fTemp62) * fTemp64) * fTemp66) * fTemp68) + (fTemp69 * ((((0.5 * (((fTemp61 * this.fRec38[((this.IOTA - (iTemp70 + 1)) & 2047)]) * fTemp71) * fTemp72)) + (((this.fRec38[((this.IOTA - (iTemp73 + 1)) & 2047)] * fTemp74) * fTemp75) * fTemp76)) + (0.166667 * ((fTemp77 * this.fRec38[((this.IOTA - (iTemp78 + 1)) & 2047)]) * fTemp79))) + (0.0416667 * (fTemp80 * this.fRec38[((this.IOTA - (iTemp81 + 1)) & 2047)])))));
			this.fRec66[0] = ((0.6 * this.fRec61[1]) + (0.4 * this.fRec66[1]));
			var fRec62 = this.fRec66[0];
			this.iVec3[0] = iSlow6;
			var iTemp82 = ((iSlow6 - this.iVec3[1]) > 0);
			this.fRec68[0] = this.fRec36[1];
			this.fRec69[(this.IOTA & 2047)] = (0 - (0.997844 * ((0.7 * this.fRec68[2]) + (0.15 * (this.fRec68[1] + this.fRec68[3])))));
			var iRec70 = 0;
			var fTemp83 = (this.fConst2 * (this.fRec29[0] * fTemp55));
			var fTemp84 = (fTemp83 + -1.49999);
			var iTemp85 = fTemp84;
			var iTemp86 = min_f(this.fConst1, max_i(0, iTemp85));
			var fTemp87 = Math.floor(fTemp84);
			var fTemp88 = (fTemp83 + (-1 - fTemp87));
			var fTemp89 = (0 - fTemp88);
			var fTemp90 = (fTemp83 + (-2 - fTemp87));
			var fTemp91 = (0 - (0.5 * fTemp90));
			var fTemp92 = (fTemp83 + (-3 - fTemp87));
			var fTemp93 = (0 - (0.333333 * fTemp92));
			var fTemp94 = (fTemp83 + (-4 - fTemp87));
			var fTemp95 = (0 - (0.25 * fTemp94));
			var fTemp96 = (fTemp83 - fTemp87);
			var iTemp97 = min_f(this.fConst1, max_i(0, (iTemp85 + 2)));
			var fTemp98 = (0 - fTemp92);
			var fTemp99 = (0 - (0.5 * fTemp94));
			var iTemp100 = min_f(this.fConst1, max_i(0, (iTemp85 + 1)));
			var fTemp101 = (0 - fTemp90);
			var fTemp102 = (0 - (0.5 * fTemp92));
			var fTemp103 = (0 - (0.333333 * fTemp94));
			var fTemp104 = (fTemp88 * fTemp90);
			var iTemp105 = min_f(this.fConst1, max_i(0, (iTemp85 + 3)));
			var fTemp106 = (0 - fTemp94);
			var fTemp107 = (fTemp104 * fTemp92);
			var iTemp108 = min_f(this.fConst1, max_i(0, (iTemp85 + 4)));
			this.fVec4[0] = (((((this.fRec69[((this.IOTA - (iTemp86 + 2)) & 2047)] * fTemp89) * fTemp91) * fTemp93) * fTemp95) + (fTemp96 * ((((0.5 * (((fTemp88 * this.fRec69[((this.IOTA - (iTemp97 + 2)) & 2047)]) * fTemp98) * fTemp99)) + (((this.fRec69[((this.IOTA - (iTemp100 + 2)) & 2047)] * fTemp101) * fTemp102) * fTemp103)) + (0.166667 * ((fTemp104 * this.fRec69[((this.IOTA - (iTemp105 + 2)) & 2047)]) * fTemp106))) + (0.0416667 * (fTemp107 * this.fRec69[((this.IOTA - (iTemp108 + 2)) & 2047)])))));
			this.fVec5[0] = (iTemp82 + this.fVec4[1]);
			this.fRec67[(this.IOTA & 2047)] = ((0.4 * this.fRec67[((this.IOTA - 1) & 2047)]) + (0.6 * this.fVec5[1]));
			var fRec63 = (((((fTemp62 * fTemp64) * fTemp66) * fTemp68) * this.fRec67[((this.IOTA - iTemp59) & 2047)]) + (fTemp69 * ((0.0416667 * (fTemp80 * this.fRec67[((this.IOTA - iTemp81) & 2047)])) + (((((fTemp74 * fTemp75) * fTemp76) * this.fRec67[((this.IOTA - iTemp73) & 2047)]) + (0.5 * (((fTemp61 * fTemp71) * fTemp72) * this.fRec67[((this.IOTA - iTemp70) & 2047)]))) + (0.166667 * ((fTemp77 * fTemp79) * this.fRec67[((this.IOTA - iTemp78) & 2047)]))))));
			var iRec64 = iRec70;
			this.fRec57[0] = fRec62;
			var fRec58 = (iTemp82 + this.fRec57[1]);
			var fRec59 = fRec63;
			var iRec60 = iRec64;
			this.fRec53[(this.IOTA & 2047)] = fRec58;
			var fRec54 = (((((fTemp89 * fTemp91) * fTemp93) * fTemp95) * this.fRec53[((this.IOTA - (iTemp86 + 1)) & 2047)]) + (fTemp96 * (((0.166667 * ((fTemp104 * fTemp106) * this.fRec53[((this.IOTA - (iTemp105 + 1)) & 2047)])) + ((((fTemp101 * fTemp102) * fTemp103) * this.fRec53[((this.IOTA - (iTemp100 + 1)) & 2047)]) + (0.5 * (((fTemp88 * fTemp98) * fTemp99) * this.fRec53[((this.IOTA - (iTemp97 + 1)) & 2047)])))) + (0.0416667 * (fTemp107 * this.fRec53[((this.IOTA - (iTemp108 + 1)) & 2047)])))));
			this.fRec55[0] = fRec59;
			var iRec56 = iRec60;
			this.fRec51[0] = this.fRec55[1];
			var iRec52 = iRec56;
			var fRec48 = this.fRec51[1];
			var fRec49 = (iRec52 + this.fRec51[1]);
			this.iRec42[0] = iRec47;
			var fRec43 = fRec50;
			var fRec44 = fRec48;
			var fRec45 = fRec49;
			this.fRec38[(this.IOTA & 2047)] = fRec43;
			var fRec39 = fRec54;
			var fRec40 = fRec44;
			var fRec41 = fRec45;
			this.fRec36[0] = fRec39;
			var fRec37 = fRec41;
			this.iRec81[0] = 0;
			var iRec82 = this.iRec81[1];
			var fRec85 = (this.iRec77[1] - (0.997844 * ((0.7 * this.fRec86[2]) + (0.15 * (this.fRec86[1] + this.fRec86[3])))));
			this.fRec100[0] = (fSlow7 + (0.999 * this.fRec100[1]));
			var fTemp109 = (this.fRec100[0] + -0.11);
			var fTemp110 = (this.fConst2 * (fTemp0 * fTemp109));
			var fTemp111 = (fTemp110 + -1.49999);
			var iTemp112 = fTemp111;
			var iTemp113 = min_f(this.fConst1, max_i(0, iTemp112));
			var fTemp114 = Math.floor(fTemp111);
			var fTemp115 = (fTemp110 + (-1 - fTemp114));
			var fTemp116 = (0 - fTemp115);
			var fTemp117 = (fTemp110 + (-2 - fTemp114));
			var fTemp118 = (0 - (0.5 * fTemp117));
			var fTemp119 = (fTemp110 + (-3 - fTemp114));
			var fTemp120 = (0 - (0.333333 * fTemp119));
			var fTemp121 = (fTemp110 + (-4 - fTemp114));
			var fTemp122 = (0 - (0.25 * fTemp121));
			var fTemp123 = (fTemp110 - fTemp114);
			var iTemp124 = min_f(this.fConst1, max_i(0, (iTemp112 + 2)));
			var fTemp125 = (0 - fTemp119);
			var fTemp126 = (0 - (0.5 * fTemp121));
			var iTemp127 = min_f(this.fConst1, max_i(0, (iTemp112 + 1)));
			var fTemp128 = (0 - fTemp117);
			var fTemp129 = (0 - (0.5 * fTemp119));
			var fTemp130 = (0 - (0.333333 * fTemp121));
			var fTemp131 = (fTemp115 * fTemp117);
			var iTemp132 = min_f(this.fConst1, max_i(0, (iTemp112 + 3)));
			var fTemp133 = (0 - fTemp121);
			var fTemp134 = (fTemp131 * fTemp119);
			var iTemp135 = min_f(this.fConst1, max_i(0, (iTemp112 + 4)));
			this.fRec96[0] = (((((this.fRec73[((this.IOTA - (iTemp113 + 1)) & 2047)] * fTemp116) * fTemp118) * fTemp120) * fTemp122) + (fTemp123 * ((((0.5 * (((fTemp115 * this.fRec73[((this.IOTA - (iTemp124 + 1)) & 2047)]) * fTemp125) * fTemp126)) + (((this.fRec73[((this.IOTA - (iTemp127 + 1)) & 2047)] * fTemp128) * fTemp129) * fTemp130)) + (0.166667 * ((fTemp131 * this.fRec73[((this.IOTA - (iTemp132 + 1)) & 2047)]) * fTemp133))) + (0.0416667 * (fTemp134 * this.fRec73[((this.IOTA - (iTemp135 + 1)) & 2047)])))));
			this.fRec101[0] = ((0.6 * this.fRec96[1]) + (0.4 * this.fRec101[1]));
			var fRec97 = this.fRec101[0];
			this.iVec6[0] = iSlow9;
			var iTemp136 = ((iSlow9 - this.iVec6[1]) > 0);
			this.fRec103[0] = this.fRec71[1];
			this.fRec104[(this.IOTA & 2047)] = (0 - (0.997844 * ((0.7 * this.fRec103[2]) + (0.15 * (this.fRec103[1] + this.fRec103[3])))));
			var iRec105 = 0;
			var fTemp137 = (this.fConst2 * (this.fRec29[0] * fTemp109));
			var fTemp138 = (fTemp137 + -1.49999);
			var iTemp139 = fTemp138;
			var iTemp140 = min_f(this.fConst1, max_i(0, iTemp139));
			var fTemp141 = Math.floor(fTemp138);
			var fTemp142 = (fTemp137 + (-1 - fTemp141));
			var fTemp143 = (0 - fTemp142);
			var fTemp144 = (fTemp137 + (-2 - fTemp141));
			var fTemp145 = (0 - (0.5 * fTemp144));
			var fTemp146 = (fTemp137 + (-3 - fTemp141));
			var fTemp147 = (0 - (0.333333 * fTemp146));
			var fTemp148 = (fTemp137 + (-4 - fTemp141));
			var fTemp149 = (0 - (0.25 * fTemp148));
			var fTemp150 = (fTemp137 - fTemp141);
			var iTemp151 = min_f(this.fConst1, max_i(0, (iTemp139 + 2)));
			var fTemp152 = (0 - fTemp146);
			var fTemp153 = (0 - (0.5 * fTemp148));
			var iTemp154 = min_f(this.fConst1, max_i(0, (iTemp139 + 1)));
			var fTemp155 = (0 - fTemp144);
			var fTemp156 = (0 - (0.5 * fTemp146));
			var fTemp157 = (0 - (0.333333 * fTemp148));
			var fTemp158 = (fTemp142 * fTemp144);
			var iTemp159 = min_f(this.fConst1, max_i(0, (iTemp139 + 3)));
			var fTemp160 = (0 - fTemp148);
			var fTemp161 = (fTemp158 * fTemp146);
			var iTemp162 = min_f(this.fConst1, max_i(0, (iTemp139 + 4)));
			this.fVec7[0] = (((((this.fRec104[((this.IOTA - (iTemp140 + 2)) & 2047)] * fTemp143) * fTemp145) * fTemp147) * fTemp149) + (fTemp150 * ((((0.5 * (((fTemp142 * this.fRec104[((this.IOTA - (iTemp151 + 2)) & 2047)]) * fTemp152) * fTemp153)) + (((this.fRec104[((this.IOTA - (iTemp154 + 2)) & 2047)] * fTemp155) * fTemp156) * fTemp157)) + (0.166667 * ((fTemp158 * this.fRec104[((this.IOTA - (iTemp159 + 2)) & 2047)]) * fTemp160))) + (0.0416667 * (fTemp161 * this.fRec104[((this.IOTA - (iTemp162 + 2)) & 2047)])))));
			this.fVec8[0] = (iTemp136 + this.fVec7[1]);
			this.fRec102[(this.IOTA & 2047)] = ((0.4 * this.fRec102[((this.IOTA - 1) & 2047)]) + (0.6 * this.fVec8[1]));
			var fRec98 = (((((fTemp116 * fTemp118) * fTemp120) * fTemp122) * this.fRec102[((this.IOTA - iTemp113) & 2047)]) + (fTemp123 * ((0.0416667 * (fTemp134 * this.fRec102[((this.IOTA - iTemp135) & 2047)])) + (((((fTemp128 * fTemp129) * fTemp130) * this.fRec102[((this.IOTA - iTemp127) & 2047)]) + (0.5 * (((fTemp115 * fTemp125) * fTemp126) * this.fRec102[((this.IOTA - iTemp124) & 2047)]))) + (0.166667 * ((fTemp131 * fTemp133) * this.fRec102[((this.IOTA - iTemp132) & 2047)]))))));
			var iRec99 = iRec105;
			this.fRec92[0] = fRec97;
			var fRec93 = (iTemp136 + this.fRec92[1]);
			var fRec94 = fRec98;
			var iRec95 = iRec99;
			this.fRec88[(this.IOTA & 2047)] = fRec93;
			var fRec89 = (((((fTemp143 * fTemp145) * fTemp147) * fTemp149) * this.fRec88[((this.IOTA - (iTemp140 + 1)) & 2047)]) + (fTemp150 * (((0.166667 * ((fTemp158 * fTemp160) * this.fRec88[((this.IOTA - (iTemp159 + 1)) & 2047)])) + ((((fTemp155 * fTemp156) * fTemp157) * this.fRec88[((this.IOTA - (iTemp154 + 1)) & 2047)]) + (0.5 * (((fTemp142 * fTemp152) * fTemp153) * this.fRec88[((this.IOTA - (iTemp151 + 1)) & 2047)])))) + (0.0416667 * (fTemp161 * this.fRec88[((this.IOTA - (iTemp162 + 1)) & 2047)])))));
			this.fRec90[0] = fRec94;
			var iRec91 = iRec95;
			this.fRec86[0] = this.fRec90[1];
			var iRec87 = iRec91;
			var fRec83 = this.fRec86[1];
			var fRec84 = (iRec87 + this.fRec86[1]);
			this.iRec77[0] = iRec82;
			var fRec78 = fRec85;
			var fRec79 = fRec83;
			var fRec80 = fRec84;
			this.fRec73[(this.IOTA & 2047)] = fRec78;
			var fRec74 = fRec89;
			var fRec75 = fRec79;
			var fRec76 = fRec80;
			this.fRec71[0] = fRec74;
			var fRec72 = fRec76;
			this.iRec116[0] = 0;
			var iRec117 = this.iRec116[1];
			var fRec120 = (this.iRec112[1] - (0.997844 * ((0.7 * this.fRec121[2]) + (0.15 * (this.fRec121[1] + this.fRec121[3])))));
			this.fRec135[0] = (fSlow10 + (0.999 * this.fRec135[1]));
			var fTemp163 = (this.fRec135[0] + -0.11);
			var fTemp164 = (this.fConst2 * (fTemp0 * fTemp163));
			var fTemp165 = (fTemp164 + -1.49999);
			var iTemp166 = fTemp165;
			var iTemp167 = min_f(this.fConst1, max_i(0, iTemp166));
			var fTemp168 = Math.floor(fTemp165);
			var fTemp169 = (fTemp164 + (-1 - fTemp168));
			var fTemp170 = (0 - fTemp169);
			var fTemp171 = (fTemp164 + (-2 - fTemp168));
			var fTemp172 = (0 - (0.5 * fTemp171));
			var fTemp173 = (fTemp164 + (-3 - fTemp168));
			var fTemp174 = (0 - (0.333333 * fTemp173));
			var fTemp175 = (fTemp164 + (-4 - fTemp168));
			var fTemp176 = (0 - (0.25 * fTemp175));
			var fTemp177 = (fTemp164 - fTemp168);
			var iTemp178 = min_f(this.fConst1, max_i(0, (iTemp166 + 2)));
			var fTemp179 = (0 - fTemp173);
			var fTemp180 = (0 - (0.5 * fTemp175));
			var iTemp181 = min_f(this.fConst1, max_i(0, (iTemp166 + 1)));
			var fTemp182 = (0 - fTemp171);
			var fTemp183 = (0 - (0.5 * fTemp173));
			var fTemp184 = (0 - (0.333333 * fTemp175));
			var fTemp185 = (fTemp169 * fTemp171);
			var iTemp186 = min_f(this.fConst1, max_i(0, (iTemp166 + 3)));
			var fTemp187 = (0 - fTemp175);
			var fTemp188 = (fTemp185 * fTemp173);
			var iTemp189 = min_f(this.fConst1, max_i(0, (iTemp166 + 4)));
			this.fRec131[0] = (((((this.fRec108[((this.IOTA - (iTemp167 + 1)) & 2047)] * fTemp170) * fTemp172) * fTemp174) * fTemp176) + (fTemp177 * ((((0.5 * (((fTemp169 * this.fRec108[((this.IOTA - (iTemp178 + 1)) & 2047)]) * fTemp179) * fTemp180)) + (((this.fRec108[((this.IOTA - (iTemp181 + 1)) & 2047)] * fTemp182) * fTemp183) * fTemp184)) + (0.166667 * ((fTemp185 * this.fRec108[((this.IOTA - (iTemp186 + 1)) & 2047)]) * fTemp187))) + (0.0416667 * (fTemp188 * this.fRec108[((this.IOTA - (iTemp189 + 1)) & 2047)])))));
			this.fRec136[0] = ((0.6 * this.fRec131[1]) + (0.4 * this.fRec136[1]));
			var fRec132 = this.fRec136[0];
			this.iVec9[0] = iSlow12;
			var iTemp190 = ((iSlow12 - this.iVec9[1]) > 0);
			this.fRec138[0] = this.fRec106[1];
			this.fRec139[(this.IOTA & 2047)] = (0 - (0.997844 * ((0.7 * this.fRec138[2]) + (0.15 * (this.fRec138[1] + this.fRec138[3])))));
			var iRec140 = 0;
			var fTemp191 = (this.fConst2 * (this.fRec29[0] * fTemp163));
			var fTemp192 = (fTemp191 + -1.49999);
			var iTemp193 = fTemp192;
			var iTemp194 = min_f(this.fConst1, max_i(0, iTemp193));
			var fTemp195 = Math.floor(fTemp192);
			var fTemp196 = (fTemp191 + (-1 - fTemp195));
			var fTemp197 = (0 - fTemp196);
			var fTemp198 = (fTemp191 + (-2 - fTemp195));
			var fTemp199 = (0 - (0.5 * fTemp198));
			var fTemp200 = (fTemp191 + (-3 - fTemp195));
			var fTemp201 = (0 - (0.333333 * fTemp200));
			var fTemp202 = (fTemp191 + (-4 - fTemp195));
			var fTemp203 = (0 - (0.25 * fTemp202));
			var fTemp204 = (fTemp191 - fTemp195);
			var iTemp205 = min_f(this.fConst1, max_i(0, (iTemp193 + 2)));
			var fTemp206 = (0 - fTemp200);
			var fTemp207 = (0 - (0.5 * fTemp202));
			var iTemp208 = min_f(this.fConst1, max_i(0, (iTemp193 + 1)));
			var fTemp209 = (0 - fTemp198);
			var fTemp210 = (0 - (0.5 * fTemp200));
			var fTemp211 = (0 - (0.333333 * fTemp202));
			var fTemp212 = (fTemp196 * fTemp198);
			var iTemp213 = min_f(this.fConst1, max_i(0, (iTemp193 + 3)));
			var fTemp214 = (0 - fTemp202);
			var fTemp215 = (fTemp212 * fTemp200);
			var iTemp216 = min_f(this.fConst1, max_i(0, (iTemp193 + 4)));
			this.fVec10[0] = (((((this.fRec139[((this.IOTA - (iTemp194 + 2)) & 2047)] * fTemp197) * fTemp199) * fTemp201) * fTemp203) + (fTemp204 * ((((0.5 * (((fTemp196 * this.fRec139[((this.IOTA - (iTemp205 + 2)) & 2047)]) * fTemp206) * fTemp207)) + (((this.fRec139[((this.IOTA - (iTemp208 + 2)) & 2047)] * fTemp209) * fTemp210) * fTemp211)) + (0.166667 * ((fTemp212 * this.fRec139[((this.IOTA - (iTemp213 + 2)) & 2047)]) * fTemp214))) + (0.0416667 * (fTemp215 * this.fRec139[((this.IOTA - (iTemp216 + 2)) & 2047)])))));
			this.fVec11[0] = (iTemp190 + this.fVec10[1]);
			this.fRec137[(this.IOTA & 2047)] = ((0.4 * this.fRec137[((this.IOTA - 1) & 2047)]) + (0.6 * this.fVec11[1]));
			var fRec133 = (((((fTemp170 * fTemp172) * fTemp174) * fTemp176) * this.fRec137[((this.IOTA - iTemp167) & 2047)]) + (fTemp177 * ((0.0416667 * (fTemp188 * this.fRec137[((this.IOTA - iTemp189) & 2047)])) + (((((fTemp182 * fTemp183) * fTemp184) * this.fRec137[((this.IOTA - iTemp181) & 2047)]) + (0.5 * (((fTemp169 * fTemp179) * fTemp180) * this.fRec137[((this.IOTA - iTemp178) & 2047)]))) + (0.166667 * ((fTemp185 * fTemp187) * this.fRec137[((this.IOTA - iTemp186) & 2047)]))))));
			var iRec134 = iRec140;
			this.fRec127[0] = fRec132;
			var fRec128 = (iTemp190 + this.fRec127[1]);
			var fRec129 = fRec133;
			var iRec130 = iRec134;
			this.fRec123[(this.IOTA & 2047)] = fRec128;
			var fRec124 = (((((fTemp197 * fTemp199) * fTemp201) * fTemp203) * this.fRec123[((this.IOTA - (iTemp194 + 1)) & 2047)]) + (fTemp204 * (((0.166667 * ((fTemp212 * fTemp214) * this.fRec123[((this.IOTA - (iTemp213 + 1)) & 2047)])) + ((((fTemp209 * fTemp210) * fTemp211) * this.fRec123[((this.IOTA - (iTemp208 + 1)) & 2047)]) + (0.5 * (((fTemp196 * fTemp206) * fTemp207) * this.fRec123[((this.IOTA - (iTemp205 + 1)) & 2047)])))) + (0.0416667 * (fTemp215 * this.fRec123[((this.IOTA - (iTemp216 + 1)) & 2047)])))));
			this.fRec125[0] = fRec129;
			var iRec126 = iRec130;
			this.fRec121[0] = this.fRec125[1];
			var iRec122 = iRec126;
			var fRec118 = this.fRec121[1];
			var fRec119 = (iRec122 + this.fRec121[1]);
			this.iRec112[0] = iRec117;
			var fRec113 = fRec120;
			var fRec114 = fRec118;
			var fRec115 = fRec119;
			this.fRec108[(this.IOTA & 2047)] = fRec113;
			var fRec109 = fRec124;
			var fRec110 = fRec114;
			var fRec111 = fRec115;
			this.fRec106[0] = fRec109;
			var fRec107 = fRec111;
			this.iRec151[0] = 0;
			var iRec152 = this.iRec151[1];
			var fRec155 = (this.iRec147[1] - (0.997844 * ((0.7 * this.fRec156[2]) + (0.15 * (this.fRec156[1] + this.fRec156[3])))));
			this.fRec170[0] = (fSlow13 + (0.999 * this.fRec170[1]));
			var fTemp217 = (this.fRec170[0] + -0.11);
			var fTemp218 = (this.fConst2 * (fTemp0 * fTemp217));
			var fTemp219 = (fTemp218 + -1.49999);
			var iTemp220 = fTemp219;
			var iTemp221 = min_f(this.fConst1, max_i(0, iTemp220));
			var fTemp222 = Math.floor(fTemp219);
			var fTemp223 = (fTemp218 + (-1 - fTemp222));
			var fTemp224 = (0 - fTemp223);
			var fTemp225 = (fTemp218 + (-2 - fTemp222));
			var fTemp226 = (0 - (0.5 * fTemp225));
			var fTemp227 = (fTemp218 + (-3 - fTemp222));
			var fTemp228 = (0 - (0.333333 * fTemp227));
			var fTemp229 = (fTemp218 + (-4 - fTemp222));
			var fTemp230 = (0 - (0.25 * fTemp229));
			var fTemp231 = (fTemp218 - fTemp222);
			var iTemp232 = min_f(this.fConst1, max_i(0, (iTemp220 + 2)));
			var fTemp233 = (0 - fTemp227);
			var fTemp234 = (0 - (0.5 * fTemp229));
			var iTemp235 = min_f(this.fConst1, max_i(0, (iTemp220 + 1)));
			var fTemp236 = (0 - fTemp225);
			var fTemp237 = (0 - (0.5 * fTemp227));
			var fTemp238 = (0 - (0.333333 * fTemp229));
			var fTemp239 = (fTemp223 * fTemp225);
			var iTemp240 = min_f(this.fConst1, max_i(0, (iTemp220 + 3)));
			var fTemp241 = (0 - fTemp229);
			var fTemp242 = (fTemp239 * fTemp227);
			var iTemp243 = min_f(this.fConst1, max_i(0, (iTemp220 + 4)));
			this.fRec166[0] = (((((this.fRec143[((this.IOTA - (iTemp221 + 1)) & 2047)] * fTemp224) * fTemp226) * fTemp228) * fTemp230) + (fTemp231 * ((((0.5 * (((fTemp223 * this.fRec143[((this.IOTA - (iTemp232 + 1)) & 2047)]) * fTemp233) * fTemp234)) + (((this.fRec143[((this.IOTA - (iTemp235 + 1)) & 2047)] * fTemp236) * fTemp237) * fTemp238)) + (0.166667 * ((fTemp239 * this.fRec143[((this.IOTA - (iTemp240 + 1)) & 2047)]) * fTemp241))) + (0.0416667 * (fTemp242 * this.fRec143[((this.IOTA - (iTemp243 + 1)) & 2047)])))));
			this.fRec171[0] = ((0.6 * this.fRec166[1]) + (0.4 * this.fRec171[1]));
			var fRec167 = this.fRec171[0];
			this.iVec12[0] = iSlow15;
			var iTemp244 = ((iSlow15 - this.iVec12[1]) > 0);
			this.fRec173[0] = this.fRec141[1];
			this.fRec174[(this.IOTA & 2047)] = (0 - (0.997844 * ((0.7 * this.fRec173[2]) + (0.15 * (this.fRec173[1] + this.fRec173[3])))));
			var iRec175 = 0;
			var fTemp245 = (this.fConst2 * (this.fRec29[0] * fTemp217));
			var fTemp246 = (fTemp245 + -1.49999);
			var iTemp247 = fTemp246;
			var iTemp248 = min_f(this.fConst1, max_i(0, iTemp247));
			var fTemp249 = Math.floor(fTemp246);
			var fTemp250 = (fTemp245 + (-1 - fTemp249));
			var fTemp251 = (0 - fTemp250);
			var fTemp252 = (fTemp245 + (-2 - fTemp249));
			var fTemp253 = (0 - (0.5 * fTemp252));
			var fTemp254 = (fTemp245 + (-3 - fTemp249));
			var fTemp255 = (0 - (0.333333 * fTemp254));
			var fTemp256 = (fTemp245 + (-4 - fTemp249));
			var fTemp257 = (0 - (0.25 * fTemp256));
			var fTemp258 = (fTemp245 - fTemp249);
			var iTemp259 = min_f(this.fConst1, max_i(0, (iTemp247 + 2)));
			var fTemp260 = (0 - fTemp254);
			var fTemp261 = (0 - (0.5 * fTemp256));
			var iTemp262 = min_f(this.fConst1, max_i(0, (iTemp247 + 1)));
			var fTemp263 = (0 - fTemp252);
			var fTemp264 = (0 - (0.5 * fTemp254));
			var fTemp265 = (0 - (0.333333 * fTemp256));
			var fTemp266 = (fTemp250 * fTemp252);
			var iTemp267 = min_f(this.fConst1, max_i(0, (iTemp247 + 3)));
			var fTemp268 = (0 - fTemp256);
			var fTemp269 = (fTemp266 * fTemp254);
			var iTemp270 = min_f(this.fConst1, max_i(0, (iTemp247 + 4)));
			this.fVec13[0] = (((((this.fRec174[((this.IOTA - (iTemp248 + 2)) & 2047)] * fTemp251) * fTemp253) * fTemp255) * fTemp257) + (fTemp258 * ((((0.5 * (((fTemp250 * this.fRec174[((this.IOTA - (iTemp259 + 2)) & 2047)]) * fTemp260) * fTemp261)) + (((this.fRec174[((this.IOTA - (iTemp262 + 2)) & 2047)] * fTemp263) * fTemp264) * fTemp265)) + (0.166667 * ((fTemp266 * this.fRec174[((this.IOTA - (iTemp267 + 2)) & 2047)]) * fTemp268))) + (0.0416667 * (fTemp269 * this.fRec174[((this.IOTA - (iTemp270 + 2)) & 2047)])))));
			this.fVec14[0] = (iTemp244 + this.fVec13[1]);
			this.fRec172[(this.IOTA & 2047)] = ((0.4 * this.fRec172[((this.IOTA - 1) & 2047)]) + (0.6 * this.fVec14[1]));
			var fRec168 = (((((fTemp224 * fTemp226) * fTemp228) * fTemp230) * this.fRec172[((this.IOTA - iTemp221) & 2047)]) + (fTemp231 * ((0.0416667 * (fTemp242 * this.fRec172[((this.IOTA - iTemp243) & 2047)])) + (((((fTemp236 * fTemp237) * fTemp238) * this.fRec172[((this.IOTA - iTemp235) & 2047)]) + (0.5 * (((fTemp223 * fTemp233) * fTemp234) * this.fRec172[((this.IOTA - iTemp232) & 2047)]))) + (0.166667 * ((fTemp239 * fTemp241) * this.fRec172[((this.IOTA - iTemp240) & 2047)]))))));
			var iRec169 = iRec175;
			this.fRec162[0] = fRec167;
			var fRec163 = (iTemp244 + this.fRec162[1]);
			var fRec164 = fRec168;
			var iRec165 = iRec169;
			this.fRec158[(this.IOTA & 2047)] = fRec163;
			var fRec159 = (((((fTemp251 * fTemp253) * fTemp255) * fTemp257) * this.fRec158[((this.IOTA - (iTemp248 + 1)) & 2047)]) + (fTemp258 * (((0.166667 * ((fTemp266 * fTemp268) * this.fRec158[((this.IOTA - (iTemp267 + 1)) & 2047)])) + ((((fTemp263 * fTemp264) * fTemp265) * this.fRec158[((this.IOTA - (iTemp262 + 1)) & 2047)]) + (0.5 * (((fTemp250 * fTemp260) * fTemp261) * this.fRec158[((this.IOTA - (iTemp259 + 1)) & 2047)])))) + (0.0416667 * (fTemp269 * this.fRec158[((this.IOTA - (iTemp270 + 1)) & 2047)])))));
			this.fRec160[0] = fRec164;
			var iRec161 = iRec165;
			this.fRec156[0] = this.fRec160[1];
			var iRec157 = iRec161;
			var fRec153 = this.fRec156[1];
			var fRec154 = (iRec157 + this.fRec156[1]);
			this.iRec147[0] = iRec152;
			var fRec148 = fRec155;
			var fRec149 = fRec153;
			var fRec150 = fRec154;
			this.fRec143[(this.IOTA & 2047)] = fRec148;
			var fRec144 = fRec159;
			var fRec145 = fRec149;
			var fRec146 = fRec150;
			this.fRec141[0] = fRec144;
			var fRec142 = fRec146;
			this.iRec186[0] = 0;
			var iRec187 = this.iRec186[1];
			var fRec190 = (this.iRec182[1] - (0.997844 * ((0.7 * this.fRec191[2]) + (0.15 * (this.fRec191[1] + this.fRec191[3])))));
			this.fRec205[0] = (fSlow16 + (0.999 * this.fRec205[1]));
			var fTemp271 = (this.fRec205[0] + -0.11);
			var fTemp272 = (this.fConst2 * (fTemp0 * fTemp271));
			var fTemp273 = (fTemp272 + -1.49999);
			var iTemp274 = fTemp273;
			var iTemp275 = min_f(this.fConst1, max_i(0, iTemp274));
			var fTemp276 = Math.floor(fTemp273);
			var fTemp277 = (fTemp272 + (-1 - fTemp276));
			var fTemp278 = (0 - fTemp277);
			var fTemp279 = (fTemp272 + (-2 - fTemp276));
			var fTemp280 = (0 - (0.5 * fTemp279));
			var fTemp281 = (fTemp272 + (-3 - fTemp276));
			var fTemp282 = (0 - (0.333333 * fTemp281));
			var fTemp283 = (fTemp272 + (-4 - fTemp276));
			var fTemp284 = (0 - (0.25 * fTemp283));
			var fTemp285 = (fTemp272 - fTemp276);
			var iTemp286 = min_f(this.fConst1, max_i(0, (iTemp274 + 2)));
			var fTemp287 = (0 - fTemp281);
			var fTemp288 = (0 - (0.5 * fTemp283));
			var iTemp289 = min_f(this.fConst1, max_i(0, (iTemp274 + 1)));
			var fTemp290 = (0 - fTemp279);
			var fTemp291 = (0 - (0.5 * fTemp281));
			var fTemp292 = (0 - (0.333333 * fTemp283));
			var fTemp293 = (fTemp277 * fTemp279);
			var iTemp294 = min_f(this.fConst1, max_i(0, (iTemp274 + 3)));
			var fTemp295 = (0 - fTemp283);
			var fTemp296 = (fTemp293 * fTemp281);
			var iTemp297 = min_f(this.fConst1, max_i(0, (iTemp274 + 4)));
			this.fRec201[0] = (((((this.fRec178[((this.IOTA - (iTemp275 + 1)) & 2047)] * fTemp278) * fTemp280) * fTemp282) * fTemp284) + (fTemp285 * ((((0.5 * (((fTemp277 * this.fRec178[((this.IOTA - (iTemp286 + 1)) & 2047)]) * fTemp287) * fTemp288)) + (((this.fRec178[((this.IOTA - (iTemp289 + 1)) & 2047)] * fTemp290) * fTemp291) * fTemp292)) + (0.166667 * ((fTemp293 * this.fRec178[((this.IOTA - (iTemp294 + 1)) & 2047)]) * fTemp295))) + (0.0416667 * (fTemp296 * this.fRec178[((this.IOTA - (iTemp297 + 1)) & 2047)])))));
			this.fRec206[0] = ((0.6 * this.fRec201[1]) + (0.4 * this.fRec206[1]));
			var fRec202 = this.fRec206[0];
			this.iVec15[0] = iSlow18;
			var iTemp298 = ((iSlow18 - this.iVec15[1]) > 0);
			this.fRec208[0] = this.fRec176[1];
			this.fRec209[(this.IOTA & 2047)] = (0 - (0.997844 * ((0.7 * this.fRec208[2]) + (0.15 * (this.fRec208[1] + this.fRec208[3])))));
			var iRec210 = 0;
			var fTemp299 = (this.fConst2 * (this.fRec29[0] * fTemp271));
			var fTemp300 = (fTemp299 + -1.49999);
			var iTemp301 = fTemp300;
			var iTemp302 = min_f(this.fConst1, max_i(0, iTemp301));
			var fTemp303 = Math.floor(fTemp300);
			var fTemp304 = (fTemp299 + (-1 - fTemp303));
			var fTemp305 = (0 - fTemp304);
			var fTemp306 = (fTemp299 + (-2 - fTemp303));
			var fTemp307 = (0 - (0.5 * fTemp306));
			var fTemp308 = (fTemp299 + (-3 - fTemp303));
			var fTemp309 = (0 - (0.333333 * fTemp308));
			var fTemp310 = (fTemp299 + (-4 - fTemp303));
			var fTemp311 = (0 - (0.25 * fTemp310));
			var fTemp312 = (fTemp299 - fTemp303);
			var iTemp313 = min_f(this.fConst1, max_i(0, (iTemp301 + 2)));
			var fTemp314 = (0 - fTemp308);
			var fTemp315 = (0 - (0.5 * fTemp310));
			var iTemp316 = min_f(this.fConst1, max_i(0, (iTemp301 + 1)));
			var fTemp317 = (0 - fTemp306);
			var fTemp318 = (0 - (0.5 * fTemp308));
			var fTemp319 = (0 - (0.333333 * fTemp310));
			var fTemp320 = (fTemp304 * fTemp306);
			var iTemp321 = min_f(this.fConst1, max_i(0, (iTemp301 + 3)));
			var fTemp322 = (0 - fTemp310);
			var fTemp323 = (fTemp320 * fTemp308);
			var iTemp324 = min_f(this.fConst1, max_i(0, (iTemp301 + 4)));
			this.fVec16[0] = (((((this.fRec209[((this.IOTA - (iTemp302 + 2)) & 2047)] * fTemp305) * fTemp307) * fTemp309) * fTemp311) + (fTemp312 * ((((0.5 * (((fTemp304 * this.fRec209[((this.IOTA - (iTemp313 + 2)) & 2047)]) * fTemp314) * fTemp315)) + (((this.fRec209[((this.IOTA - (iTemp316 + 2)) & 2047)] * fTemp317) * fTemp318) * fTemp319)) + (0.166667 * ((fTemp320 * this.fRec209[((this.IOTA - (iTemp321 + 2)) & 2047)]) * fTemp322))) + (0.0416667 * (fTemp323 * this.fRec209[((this.IOTA - (iTemp324 + 2)) & 2047)])))));
			this.fVec17[0] = (iTemp298 + this.fVec16[1]);
			this.fRec207[(this.IOTA & 2047)] = ((0.4 * this.fRec207[((this.IOTA - 1) & 2047)]) + (0.6 * this.fVec17[1]));
			var fRec203 = (((((fTemp278 * fTemp280) * fTemp282) * fTemp284) * this.fRec207[((this.IOTA - iTemp275) & 2047)]) + (fTemp285 * ((0.0416667 * (fTemp296 * this.fRec207[((this.IOTA - iTemp297) & 2047)])) + (((((fTemp290 * fTemp291) * fTemp292) * this.fRec207[((this.IOTA - iTemp289) & 2047)]) + (0.5 * (((fTemp277 * fTemp287) * fTemp288) * this.fRec207[((this.IOTA - iTemp286) & 2047)]))) + (0.166667 * ((fTemp293 * fTemp295) * this.fRec207[((this.IOTA - iTemp294) & 2047)]))))));
			var iRec204 = iRec210;
			this.fRec197[0] = fRec202;
			var fRec198 = (iTemp298 + this.fRec197[1]);
			var fRec199 = fRec203;
			var iRec200 = iRec204;
			this.fRec193[(this.IOTA & 2047)] = fRec198;
			var fRec194 = (((((fTemp305 * fTemp307) * fTemp309) * fTemp311) * this.fRec193[((this.IOTA - (iTemp302 + 1)) & 2047)]) + (fTemp312 * (((0.166667 * ((fTemp320 * fTemp322) * this.fRec193[((this.IOTA - (iTemp321 + 1)) & 2047)])) + ((((fTemp317 * fTemp318) * fTemp319) * this.fRec193[((this.IOTA - (iTemp316 + 1)) & 2047)]) + (0.5 * (((fTemp304 * fTemp314) * fTemp315) * this.fRec193[((this.IOTA - (iTemp313 + 1)) & 2047)])))) + (0.0416667 * (fTemp323 * this.fRec193[((this.IOTA - (iTemp324 + 1)) & 2047)])))));
			this.fRec195[0] = fRec199;
			var iRec196 = iRec200;
			this.fRec191[0] = this.fRec195[1];
			var iRec192 = iRec196;
			var fRec188 = this.fRec191[1];
			var fRec189 = (iRec192 + this.fRec191[1]);
			this.iRec182[0] = iRec187;
			var fRec183 = fRec190;
			var fRec184 = fRec188;
			var fRec185 = fRec189;
			this.fRec178[(this.IOTA & 2047)] = fRec183;
			var fRec179 = fRec194;
			var fRec180 = fRec184;
			var fRec181 = fRec185;
			this.fRec176[0] = fRec179;
			var fRec177 = fRec181;
			var fTemp325 = (((((fRec1 + fRec37) + fRec72) + fRec107) + fRec142) + fRec177);
			output0[i] = fTemp325;
			output1[i] = fTemp325;
			this.iRec10[1] = this.iRec10[0];
			this.fRec29[1] = this.fRec29[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec31[1] = this.fRec31[0];
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.fRec33[j0] = this.fRec33[(j0 - 1)];
				
			}
			this.IOTA = (this.IOTA + 1);
			this.fVec0[1] = this.fVec0[0];
			this.iVec1[1] = this.iVec1[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec19[1] = this.fRec19[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec15[j1] = this.fRec15[(j1 - 1)];
				
			}
			this.iRec6[1] = this.iRec6[0];
			this.fRec0[1] = this.fRec0[0];
			this.iRec46[1] = this.iRec46[0];
			this.fRec65[1] = this.fRec65[0];
			this.fRec61[1] = this.fRec61[0];
			this.fRec66[1] = this.fRec66[0];
			this.iVec3[1] = this.iVec3[0];
			for (var j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
				this.fRec68[j2] = this.fRec68[(j2 - 1)];
				
			}
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fRec57[1] = this.fRec57[0];
			this.fRec55[1] = this.fRec55[0];
			for (var j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
				this.fRec51[j3] = this.fRec51[(j3 - 1)];
				
			}
			this.iRec42[1] = this.iRec42[0];
			this.fRec36[1] = this.fRec36[0];
			this.iRec81[1] = this.iRec81[0];
			this.fRec100[1] = this.fRec100[0];
			this.fRec96[1] = this.fRec96[0];
			this.fRec101[1] = this.fRec101[0];
			this.iVec6[1] = this.iVec6[0];
			for (var j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
				this.fRec103[j4] = this.fRec103[(j4 - 1)];
				
			}
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec92[1] = this.fRec92[0];
			this.fRec90[1] = this.fRec90[0];
			for (var j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
				this.fRec86[j5] = this.fRec86[(j5 - 1)];
				
			}
			this.iRec77[1] = this.iRec77[0];
			this.fRec71[1] = this.fRec71[0];
			this.iRec116[1] = this.iRec116[0];
			this.fRec135[1] = this.fRec135[0];
			this.fRec131[1] = this.fRec131[0];
			this.fRec136[1] = this.fRec136[0];
			this.iVec9[1] = this.iVec9[0];
			for (var j6 = 3; (j6 > 0); j6 = (j6 - 1)) {
				this.fRec138[j6] = this.fRec138[(j6 - 1)];
				
			}
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fRec127[1] = this.fRec127[0];
			this.fRec125[1] = this.fRec125[0];
			for (var j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
				this.fRec121[j7] = this.fRec121[(j7 - 1)];
				
			}
			this.iRec112[1] = this.iRec112[0];
			this.fRec106[1] = this.fRec106[0];
			this.iRec151[1] = this.iRec151[0];
			this.fRec170[1] = this.fRec170[0];
			this.fRec166[1] = this.fRec166[0];
			this.fRec171[1] = this.fRec171[0];
			this.iVec12[1] = this.iVec12[0];
			for (var j8 = 3; (j8 > 0); j8 = (j8 - 1)) {
				this.fRec173[j8] = this.fRec173[(j8 - 1)];
				
			}
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fRec162[1] = this.fRec162[0];
			this.fRec160[1] = this.fRec160[0];
			for (var j9 = 3; (j9 > 0); j9 = (j9 - 1)) {
				this.fRec156[j9] = this.fRec156[(j9 - 1)];
				
			}
			this.iRec147[1] = this.iRec147[0];
			this.fRec141[1] = this.fRec141[0];
			this.iRec186[1] = this.iRec186[0];
			this.fRec205[1] = this.fRec205[0];
			this.fRec201[1] = this.fRec201[0];
			this.fRec206[1] = this.fRec206[0];
			this.iVec15[1] = this.iVec15[0];
			for (var j10 = 3; (j10 > 0); j10 = (j10 - 1)) {
				this.fRec208[j10] = this.fRec208[(j10 - 1)];
				
			}
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fRec197[1] = this.fRec197[0];
			this.fRec195[1] = this.fRec195[0];
			for (var j11 = 3; (j11 > 0); j11 = (j11 - 1)) {
				this.fRec191[j11] = this.fRec191[(j11 - 1)];
				
			}
			this.iRec182[1] = this.iRec182[0];
			this.fRec176[1] = this.fRec176[0];
			
		}
		
	}
	
}

