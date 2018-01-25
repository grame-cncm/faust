
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.iVec0 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.fHslider2;
	this.fConst2;
	this.fHslider3;
	this.fRec3 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fHslider4;
	this.fRec5 = new Float32Array(2);
	this.iRec6 = new Int32Array(2);
	this.fConst3;
	this.fHslider5;
	this.fHslider6;
	this.fRec7 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
	this.fRec0 = new Float32Array(3);
	this.fRec10 = new Float32Array(3);
	this.fRec11 = new Float32Array(3);
	this.fRec12 = new Float32Array(3);
	this.fRec13 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("description", "Simple source-filter vocal synthesizer.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocal BandPass");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
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
		this.fConst1 = (1 / this.fConst0);
		this.fConst2 = (6.28319 / this.fConst0);
		this.fConst3 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.9;
		this.fHslider1 = 440;
		this.fHslider2 = 0.5;
		this.fHslider3 = 6;
		this.fHslider4 = 0;
		this.fHslider5 = 0;
		this.fHslider6 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec3[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec4[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.iRec6[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec7[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec8[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec9[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec0[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			this.fRec10[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec11[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec12[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			this.fRec13[l13] = 0;
			
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
		ui_interface.openVerticalBox("vocal");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.9, 0, 1, 0.01);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.addHorizontalSlider("voiceType", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0, 0, 4, 1);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.addHorizontalSlider("vowel", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, 0, 4, 0.01);
		ui_interface.declare("fHslider4", "4", "");
		ui_interface.addHorizontalSlider("fricative", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fHslider3", "5", "");
		ui_interface.addHorizontalSlider("vibratoFreq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 6, 1, 10, 0.01);
		ui_interface.declare("fHslider2", "6", "");
		ui_interface.addHorizontalSlider("vibratoGain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = (0.1 * this.fHslider2);
		var fSlow3 = (this.fConst2 * this.fHslider3);
		var fSlow4 = Math.sin(fSlow3);
		var fSlow5 = Math.cos(fSlow3);
		var fSlow6 = (0 - fSlow4);
		var fSlow7 = (0.001 * this.fHslider4);
		var fSlow8 = this.fHslider5;
		var fSlow9 = (5 * fSlow8);
		var fSlow10 = (0.001 * this.fHslider6);
		var fSlow11 = (5 * (1 - fSlow8));
		var iSlow12 = (((fSlow8 == 0)?1:((fSlow8 == 3)?1:0)) == 0);
		var iSlow13 = (fSlow8 != 2);
		var fSlow14 = (2 * fSlow1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec3[0] = ((fSlow4 * this.fRec4[1]) + (fSlow5 * this.fRec3[1]));
			var iTemp0 = (1 - this.iVec0[1]);
			this.fRec4[0] = (((fSlow5 * this.fRec4[1]) + (fSlow6 * this.fRec3[1])) + iTemp0);
			var fTemp1 = max_f(1e-07, Math.abs((fSlow1 * ((fSlow2 * this.fRec3[0]) + 1))));
			var fTemp2 = (this.fRec1[1] + (this.fConst1 * fTemp1));
			var fTemp3 = (fTemp2 + -1);
			var iTemp4 = (fTemp3 < 0);
			this.fRec1[0] = (iTemp4?fTemp2:fTemp3);
			var fRec2 = (iTemp4?fTemp2:(fTemp2 + (fTemp3 * (1 - (this.fConst0 / fTemp1)))));
			this.fRec5[0] = (fSlow7 + (0.999 * this.fRec5[1]));
			this.iRec6[0] = ((1103515245 * this.iRec6[1]) + 12345);
			var fTemp5 = (fSlow0 * ((((2 * fRec2) + -1) * (1 - this.fRec5[0])) + (4.65661e-10 * (this.fRec5[0] * this.iRec6[0]))));
			this.fRec7[0] = (fSlow10 + (0.999 * this.fRec7[1]));
			var fTemp6 = (fSlow9 + this.fRec7[0]);
			var iTemp7 = (fTemp6 < 23);
			var iTemp8 = (fTemp6 < 24);
			var fTemp9 = (fSlow9 + (this.fRec7[0] + -23));
			var iTemp10 = (fTemp6 < 22);
			var fTemp11 = (fSlow9 + (this.fRec7[0] + -22));
			var iTemp12 = (fTemp6 < 21);
			var fTemp13 = (fSlow9 + (this.fRec7[0] + -21));
			var iTemp14 = (fTemp6 < 20);
			var fTemp15 = (fSlow9 + (this.fRec7[0] + -20));
			var iTemp16 = (fTemp6 < 19);
			var fTemp17 = (fSlow9 + (this.fRec7[0] + -19));
			var iTemp18 = (fTemp6 < 18);
			var fTemp19 = (fSlow9 + (this.fRec7[0] + -18));
			var iTemp20 = (fTemp6 < 17);
			var fTemp21 = (fSlow9 + (this.fRec7[0] + -17));
			var iTemp22 = (fTemp6 < 16);
			var fTemp23 = (fSlow9 + (this.fRec7[0] + -16));
			var fTemp24 = (80 * fTemp23);
			var iTemp25 = (fTemp6 < 15);
			var fTemp26 = (fSlow9 + (this.fRec7[0] + -15));
			var iTemp27 = (fTemp6 < 14);
			var fTemp28 = (fSlow9 + (this.fRec7[0] + -14));
			var iTemp29 = (fTemp6 < 13);
			var fTemp30 = (fSlow9 + (this.fRec7[0] + -13));
			var iTemp31 = (fTemp6 < 12);
			var fTemp32 = (fSlow9 + (this.fRec7[0] + -12));
			var iTemp33 = (fTemp6 < 11);
			var fTemp34 = (fSlow9 + (this.fRec7[0] + -11));
			var iTemp35 = (fTemp6 < 10);
			var fTemp36 = (fSlow9 + (this.fRec7[0] + -10));
			var iTemp37 = (fTemp6 < 9);
			var fTemp38 = (fSlow9 + (this.fRec7[0] + -9));
			var iTemp39 = (fTemp6 < 8);
			var fTemp40 = (fSlow9 + (this.fRec7[0] + -8));
			var fTemp41 = (50 * fTemp40);
			var iTemp42 = (fTemp6 < 7);
			var fTemp43 = (fSlow9 + (this.fRec7[0] + -7));
			var iTemp44 = (fTemp6 < 6);
			var fTemp45 = (fSlow9 + (this.fRec7[0] + -6));
			var iTemp46 = (fTemp6 < 5);
			var fTemp47 = (this.fRec7[0] - fSlow11);
			var iTemp48 = (fTemp6 < 4);
			var fTemp49 = (fSlow9 + (this.fRec7[0] + -4));
			var iTemp50 = (fTemp6 < 3);
			var fTemp51 = (fSlow9 + (this.fRec7[0] + -3));
			var iTemp52 = (fTemp6 < 2);
			var fTemp53 = (fSlow9 + (this.fRec7[0] + -2));
			var iTemp54 = (fTemp6 < 1);
			var fTemp55 = (fSlow9 + (this.fRec7[0] + -1));
			var iTemp56 = (fTemp6 < 0);
			var fTemp57 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?800:(iTemp54?(800 - (400 * fTemp6)):400)):(iTemp52?(400 - (50 * fTemp55)):350)):(iTemp50?((100 * fTemp53) + 350):450)):(iTemp48?(450 - (125 * fTemp51)):325)):(iTemp46?((275 * fTemp49) + 325):600)):(iTemp44?(600 - (200 * fTemp47)):400)):(iTemp42?(400 - (150 * fTemp45)):250)):(iTemp39?((150 * fTemp43) + 250):400)):(iTemp37?(400 - fTemp41):350)):(iTemp35?((310 * fTemp38) + 350):660)):(iTemp33?(660 - (220 * fTemp36)):440)):(iTemp31?(440 - (170 * fTemp34)):270)):(iTemp29?((160 * fTemp32) + 270):430)):(iTemp27?(430 - (60 * fTemp30)):370)):(iTemp25?((430 * fTemp28) + 370):800)):(iTemp22?(800 - (450 * fTemp26)):350)):(iTemp20?(350 - fTemp24):270)):(iTemp18?((180 * fTemp21) + 270):450)):(iTemp16?(450 - (125 * fTemp19)):325)):(iTemp14?(325 * (fTemp17 + 1)):650)):(iTemp12?(650 - (250 * fTemp15)):400)):(iTemp10?(400 - (110 * fTemp13)):290)):(iTemp7?((110 * fTemp11) + 290):400)):(iTemp8?(400 - (50 * fTemp9)):350));
			this.fRec8[0] = ((fSlow4 * this.fRec9[1]) + (fSlow5 * this.fRec8[1]));
			this.fRec9[0] = (((fSlow5 * this.fRec9[1]) + (fSlow6 * this.fRec8[1])) + iTemp0);
			var fTemp58 = ((fSlow2 * this.fRec8[0]) + 1);
			var fTemp59 = (fSlow1 * fTemp58);
			var fTemp60 = ((fTemp57 <= fTemp59)?fTemp59:fTemp57);
			var fTemp61 = Math.tan((this.fConst3 * fTemp60));
			var fTemp62 = (1 / fTemp61);
			var fTemp63 = (20 * fTemp15);
			var fTemp64 = (20 * fTemp26);
			var fTemp65 = (10 * fTemp36);
			var fTemp66 = (10 * fTemp49);
			var fTemp67 = (20 * fTemp51);
			var fTemp68 = (20 * fTemp53);
			var fTemp69 = (20 * fTemp6);
			var fTemp70 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?80:(iTemp54?(80 - fTemp69):60)):(iTemp52?(60 - (10 * fTemp55)):50)):(iTemp50?(fTemp68 + 50):70)):(iTemp48?(70 - fTemp67):50)):(iTemp46?(fTemp66 + 50):60)):(iTemp44?(60 - (20 * fTemp47)):40)):(iTemp42?((20 * fTemp45) + 40):60)):(iTemp39?(60 - (20 * fTemp43)):40)):40):(iTemp35?(40 * (fTemp38 + 1)):80)):(iTemp33?(80 - fTemp65):70)):(iTemp31?(70 - (30 * fTemp34)):40)):40):40):(iTemp25?(40 * (fTemp28 + 1)):80)):(iTemp22?(80 - fTemp64):60)):60):(iTemp18?(60 - (20 * fTemp21)):40)):(iTemp16?((10 * fTemp19) + 40):50)):50):(iTemp12?(fTemp63 + 50):70)):(iTemp10?(70 - (30 * fTemp13)):40)):(iTemp7?((30 * fTemp11) + 40):70)):(iTemp8?(70 - (30 * fTemp9)):40)) / fTemp60);
			var fTemp71 = (((fTemp62 + fTemp70) / fTemp61) + 1);
			this.fRec0[0] = (fTemp5 - (((this.fRec0[2] * (((fTemp62 - fTemp70) / fTemp61) + 1)) + (2 * (this.fRec0[1] * (1 - (1 / mydsp_faustpower2_f(fTemp61)))))) / fTemp71));
			var fTemp72 = ((0.00084 * (1000 - fTemp59)) + 0.8);
			var fTemp73 = ((0.00366667 * (400 - fTemp59)) + 3);
			var fTemp74 = (iSlow12?fTemp73:fTemp72);
			var fTemp75 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?1150:(iTemp54?((450 * fTemp6) + 1150):1600)):(iTemp52?((100 * fTemp55) + 1600):1700)):(iTemp50?(1700 - (900 * fTemp53)):800)):(iTemp48?(800 - (100 * fTemp51)):700)):(iTemp46?((340 * fTemp49) + 700):1040)):(iTemp44?((580 * fTemp47) + 1040):1620)):(iTemp42?((130 * fTemp45) + 1620):1750)):(iTemp39?(1750 - (1000 * fTemp43)):750)):(iTemp37?(750 - (150 * fTemp40)):600)):(iTemp35?((520 * fTemp38) + 600):1120)):(iTemp33?((680 * fTemp36) + 1120):1800)):(iTemp31?((50 * fTemp34) + 1800):1850)):(iTemp29?(1850 - (1030 * fTemp32)):820)):(iTemp27?(820 - (190 * fTemp30)):630)):(iTemp25?((520 * fTemp28) + 630):1150)):(iTemp22?((850 * fTemp26) + 1150):2000)):(iTemp20?((140 * fTemp23) + 2000):2140)):(iTemp18?(2140 - (1340 * fTemp21)):800)):(iTemp16?(800 - (100 * fTemp19)):700)):(iTemp14?((380 * fTemp17) + 700):1080)):(iTemp12?((620 * fTemp15) + 1080):1700)):(iTemp10?((170 * fTemp13) + 1700):1870)):(iTemp7?(1870 - (1070 * fTemp11)):800)):(iTemp8?(800 - (200 * fTemp9)):600));
			var fTemp76 = ((fSlow14 * fTemp58) + 30);
			var fTemp77 = (iSlow13?(((fTemp75 >= 1300) & (fTemp59 >= 200))?(fTemp75 - (0.000952381 * ((fTemp59 + -200) * (fTemp75 + -1300)))):((fTemp75 <= fTemp76)?fTemp76:fTemp75)):fTemp75);
			var fTemp78 = Math.tan((this.fConst3 * fTemp77));
			var fTemp79 = (1 / fTemp78);
			var fTemp80 = (10 * fTemp11);
			var fTemp81 = (10 * fTemp15);
			var fTemp82 = (10 * fTemp38);
			var fTemp83 = (10 * fTemp47);
			var fTemp84 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?90:(iTemp54?(90 - (10 * fTemp6)):80)):(iTemp52?((20 * fTemp55) + 80):100)):(iTemp50?(100 - fTemp68):80)):(iTemp48?(80 - fTemp67):60)):(iTemp46?(fTemp66 + 60):70)):(iTemp44?(fTemp83 + 70):80)):(iTemp42?((10 * fTemp45) + 80):90)):(iTemp39?(90 - (10 * fTemp43)):80)):80):(iTemp35?(fTemp82 + 80):90)):(iTemp33?(90 - fTemp65):80)):(iTemp31?((10 * fTemp34) + 80):90)):(iTemp29?(90 - (10 * fTemp32)):80)):(iTemp27?(80 - (20 * fTemp30)):60)):(iTemp25?((30 * fTemp28) + 60):90)):(iTemp22?((10 * fTemp26) + 90):100)):(iTemp20?(100 - (10 * fTemp23)):90)):(iTemp18?(90 - (10 * fTemp21)):80)):(iTemp16?(80 - (20 * fTemp19)):60)):(iTemp14?((30 * fTemp17) + 60):90)):(iTemp12?(90 - fTemp81):80)):(iTemp10?((10 * fTemp13) + 80):90)):(iTemp7?(90 - fTemp80):80)):(iTemp8?(80 - (20 * fTemp9)):60)) / fTemp77);
			var fTemp85 = (((fTemp79 + fTemp84) / fTemp78) + 1);
			this.fRec10[0] = (fTemp5 - (((this.fRec10[2] * (((fTemp79 - fTemp84) / fTemp78) + 1)) + (2 * (this.fRec10[1] * (1 - (1 / mydsp_faustpower2_f(fTemp78)))))) / fTemp85));
			var fTemp86 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?0.630957:(iTemp54?(0.630957 - (0.567861 * fTemp6)):0.063096)):(iTemp52?((0.036904 * fTemp55) + 0.063096):0.1)):(iTemp50?((0.254813 * fTemp53) + 0.1):0.354813)):(iTemp48?(0.354813 - (0.103624 * fTemp51)):0.251189)):(iTemp46?((0.195495 * fTemp49) + 0.251189):0.446684)):(iTemp44?(0.446684 - (0.195495 * fTemp47)):0.251189)):(iTemp42?(0.251189 - (0.219566 * fTemp45)):0.031623)):(iTemp39?((0.250215 * fTemp43) + 0.031623):0.281838)):(iTemp37?(0.281838 - (0.181838 * fTemp40)):0.1)):(iTemp35?((0.401187 * fTemp38) + 0.1):0.501187)):(iTemp33?(0.501187 - (0.301661 * fTemp36)):0.199526)):(iTemp31?(0.199526 - (0.13643 * fTemp34)):0.063096)):(iTemp29?((0.253132 * fTemp32) + 0.063096):0.316228)):(iTemp27?(0.316228 - (0.216228 * fTemp30)):0.1)):(iTemp25?((0.401187 * fTemp28) + 0.1):0.501187)):(iTemp22?(0.501187 - (0.401187 * fTemp26)):0.1)):(iTemp20?((0.151189 * fTemp23) + 0.1):0.251189)):(iTemp18?((0.030649 * fTemp21) + 0.251189):0.281838)):(iTemp16?(0.281838 - (0.123349 * fTemp19)):0.158489)):(iTemp14?((0.342698 * fTemp17) + 0.158489):0.501187)):(iTemp12?(0.501187 - (0.301661 * fTemp15)):0.199526)):(iTemp10?(0.199526 - (0.021698 * fTemp13)):0.177828)):(iTemp7?((0.1384 * fTemp11) + 0.177828):0.316228)):(iTemp8?(0.316228 - (0.216228 * fTemp9)):0.1));
			var fTemp87 = (iSlow12?(fTemp73 * fTemp86):(fTemp72 * fTemp86));
			var fTemp88 = (100 * fTemp9);
			var fTemp89 = (50 * fTemp17);
			var fTemp90 = (50 * fTemp36);
			var fTemp91 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?2800:(iTemp54?(2800 - (100 * fTemp6)):2700)):2700):(iTemp50?((130 * fTemp53) + 2700):2830)):(iTemp48?(2830 - (300 * fTemp51)):2530)):(iTemp46?(2530 - (280 * fTemp49)):2250)):(iTemp44?((150 * fTemp47) + 2250):2400)):(iTemp42?((200 * fTemp45) + 2400):2600)):(iTemp39?(2600 - (200 * fTemp43)):2400)):2400):(iTemp35?((350 * fTemp38) + 2400):2750)):(iTemp33?(2750 - fTemp90):2700)):(iTemp31?((200 * fTemp34) + 2700):2900)):(iTemp29?(2900 - (200 * fTemp32)):2700)):(iTemp27?((50 * fTemp30) + 2700):2750)):(iTemp25?((150 * fTemp28) + 2750):2900)):(iTemp22?(2900 - (100 * fTemp26)):2800)):(iTemp20?((150 * fTemp23) + 2800):2950)):(iTemp18?(2950 - (120 * fTemp21)):2830)):(iTemp16?(2830 - (130 * fTemp19)):2700)):(iTemp14?(2700 - fTemp89):2650)):(iTemp12?(2650 - (50 * fTemp15)):2600)):(iTemp10?((200 * fTemp13) + 2600):2800)):(iTemp7?(2800 - (200 * fTemp11)):2600)):(iTemp8?(fTemp88 + 2600):2700));
			var fTemp92 = Math.tan((this.fConst3 * fTemp91));
			var fTemp93 = (1 / fTemp92);
			var fTemp94 = (20 * fTemp28);
			var fTemp95 = (20 * fTemp36);
			var fTemp96 = (20 * fTemp38);
			var fTemp97 = (60 * fTemp49);
			var fTemp98 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?120:(iTemp50?(120 - fTemp68):100)):(iTemp48?((70 * fTemp51) + 100):170)):(iTemp46?(170 - fTemp97):110)):(iTemp44?(110 - fTemp83):100)):100):100):100):(iTemp35?(fTemp96 + 100):120)):(iTemp33?(120 - fTemp95):100)):100):100):100):(iTemp25?(fTemp94 + 100):120)):120):(iTemp20?(120 - (20 * fTemp23)):100)):100):(iTemp16?((70 * fTemp19) + 100):170)):(iTemp14?(170 - fTemp89):120)):(iTemp12?(120 - fTemp63):100)):100):100):100) / fTemp91);
			var fTemp99 = (((fTemp93 + fTemp98) / fTemp92) + 1);
			this.fRec11[0] = (fTemp5 - (((this.fRec11[2] * (((fTemp93 - fTemp98) / fTemp92) + 1)) + (2 * (this.fRec11[1] * (1 - (1 / mydsp_faustpower2_f(fTemp92)))))) / fTemp99));
			var fTemp100 = (iTemp18?((0.029314 * fTemp21) + 0.050119):0.079433);
			var fTemp101 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?0.1:(iTemp54?(0.1 - (0.068377 * fTemp6)):0.031623)):0.031623):(iTemp50?((0.126866 * fTemp53) + 0.031623):0.158489)):(iTemp48?(0.158489 - (0.126866 * fTemp51)):0.031623)):(iTemp46?((0.32319 * fTemp49) + 0.031623):0.354813)):0.354813):(iTemp42?(0.354813 - (0.196324 * fTemp45)):0.158489)):(iTemp39?(0.158489 - (0.069364 * fTemp43)):0.089125)):(iTemp37?(0.089125 - (0.064006 * fTemp40)):0.025119)):(iTemp35?((0.045676 * fTemp38) + 0.025119):0.070795)):(iTemp33?((0.055098 * fTemp36) + 0.070795):0.125893)):(iTemp31?(0.125893 - (0.062797 * fTemp34)):0.063096)):(iTemp29?(0.063096 - (0.012977 * fTemp32)):0.050119)):(iTemp27?((0.020676 * fTemp30) + 0.050119):0.070795)):(iTemp25?(0.070795 - (0.045676 * fTemp28)):0.025119)):(iTemp22?((0.152709 * fTemp26) + 0.025119):0.177828)):(iTemp20?(0.177828 - (0.127709 * fTemp23)):0.050119)):fTemp100):(iTemp16?(0.079433 - (0.06165 * fTemp19)):0.017783)):(iTemp14?((0.428901 * fTemp17) + 0.017783):0.446684)):(iTemp12?(0.446684 - (0.195495 * fTemp15)):0.251189)):(iTemp10?(0.251189 - (0.125296 * fTemp13)):0.125893)):(iTemp7?((0.125296 * fTemp11) + 0.125893):0.251189)):(iTemp8?(0.251189 - (0.109935 * fTemp9)):0.141254));
			var fTemp102 = (iSlow12?(fTemp73 * fTemp101):(fTemp72 * fTemp101));
			var fTemp103 = (350 * fTemp47);
			var fTemp104 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?3500:(iTemp54?(3500 - (200 * fTemp6)):3300)):(iTemp52?((400 * fTemp55) + 3300):3700)):(iTemp50?(3700 - (200 * fTemp53)):3500)):3500):(iTemp46?(3500 - (1050 * fTemp49)):2450)):(iTemp44?(fTemp103 + 2450):2800)):(iTemp42?((250 * fTemp45) + 2800):3050)):(iTemp39?(3050 - (450 * fTemp43)):2600)):(iTemp37?((75 * fTemp40) + 2600):2675)):(iTemp35?((325 * fTemp38) + 2675):3000)):3000):(iTemp31?((350 * fTemp34) + 3000):3350)):(iTemp29?(3350 - (350 * fTemp32)):3000)):3000):(iTemp25?((900 * fTemp28) + 3000):3900)):(iTemp22?(3900 - (300 * fTemp26)):3600)):(iTemp20?((300 * fTemp23) + 3600):3900)):(iTemp18?(3900 - (100 * fTemp21)):3800)):3800):(iTemp14?(3800 - (900 * fTemp17)):2900)):(iTemp12?((300 * fTemp15) + 2900):3200)):(iTemp10?((50 * fTemp13) + 3200):3250)):(iTemp7?(3250 - (450 * fTemp11)):2800)):(iTemp8?(fTemp88 + 2800):2900));
			var fTemp105 = Math.tan((this.fConst3 * fTemp104));
			var fTemp106 = (1 / fTemp105);
			var fTemp107 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?130:(iTemp54?(fTemp69 + 130):150)):150):(iTemp50?(150 - fTemp68):130)):(iTemp48?((50 * fTemp51) + 130):180)):(iTemp46?(180 - fTemp97):120)):120):120):120):120):(iTemp35?(fTemp82 + 120):130)):(iTemp33?(130 - fTemp65):120)):120):120):120):(iTemp25?((10 * fTemp28) + 120):130)):(iTemp22?(fTemp64 + 130):150)):(iTemp20?(150 - (30 * fTemp23)):120)):120):(iTemp16?((60 * fTemp19) + 120):180)):(iTemp14?(180 - fTemp89):130)):(iTemp12?(130 - fTemp81):120)):120):(iTemp7?(fTemp80 + 120):130)):(iTemp8?(130 - (10 * fTemp9)):120)) / fTemp104);
			var fTemp108 = (((fTemp106 + fTemp107) / fTemp105) + 1);
			this.fRec12[0] = (fTemp5 - (((this.fRec12[2] * (((fTemp106 - fTemp107) / fTemp105) + 1)) + (2 * (this.fRec12[1] * (1 - (1 / mydsp_faustpower2_f(fTemp105)))))) / fTemp108));
			var fTemp109 = (iTemp31?(0.1 - (0.084151 * fTemp34)):0.015849);
			var fTemp110 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?0.015849:(iTemp54?((0.001934 * fTemp6) + 0.015849):0.017783)):(iTemp52?(0.017783 - (0.001934 * fTemp55)):0.015849)):(iTemp50?((0.023962 * fTemp53) + 0.015849):0.039811)):(iTemp48?(0.039811 - (0.029811 * fTemp51)):0.01)):(iTemp46?((0.344813 * fTemp49) + 0.01):0.354813)):(iTemp44?(0.354813 - (0.103624 * fTemp47)):0.251189)):(iTemp42?(0.251189 - (0.171756 * fTemp45)):0.079433)):(iTemp39?((0.020567 * fTemp43) + 0.079433):0.1)):(iTemp37?(0.1 - (0.060189 * fTemp40)):0.039811)):(iTemp35?((0.023285 * fTemp38) + 0.039811):0.063096)):(iTemp33?((0.036904 * fTemp36) + 0.063096):0.1)):fTemp109):(iTemp29?((0.063584 * fTemp32) + 0.015849):0.079433)):(iTemp27?(0.079433 - (0.04781 * fTemp30)):0.031623)):(iTemp25?((0.068377 * fTemp28) + 0.031623):0.1)):(iTemp22?(0.1 - (0.09 * fTemp26)):0.01)):(iTemp20?((0.040119 * fTemp23) + 0.01):0.050119)):fTemp100):(iTemp16?(0.079433 - (0.069433 * fTemp19)):0.01)):(iTemp14?((0.388107 * fTemp17) + 0.01):0.398107)):(iTemp12?(0.398107 - (0.198581 * fTemp15)):0.199526)):(iTemp10?(0.199526 - (0.099526 * fTemp13)):0.1)):(iTemp7?((0.151189 * fTemp11) + 0.1):0.251189)):(iTemp8?(0.251189 - (0.051663 * fTemp9)):0.199526));
			var fTemp111 = (iSlow12?(fTemp73 * fTemp110):(fTemp72 * fTemp110));
			var fTemp112 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?4950:(iTemp46?(4950 - (2200 * fTemp49)):2750)):(iTemp44?(fTemp103 + 2750):3100)):(iTemp42?((240 * fTemp45) + 3100):3340)):(iTemp39?(3340 - (440 * fTemp43)):2900)):(iTemp37?(fTemp41 + 2900):2950)):(iTemp35?((400 * fTemp38) + 2950):3350)):(iTemp33?(3350 - fTemp90):3300)):(iTemp31?((290 * fTemp34) + 3300):3590)):(iTemp29?(3590 - (290 * fTemp32)):3300)):(iTemp27?((100 * fTemp30) + 3300):3400)):(iTemp25?((1550 * fTemp28) + 3400):4950)):4950):4950):4950):4950):(iTemp14?(4950 - (1700 * fTemp17)):3250)):(iTemp12?((330 * fTemp15) + 3250):3580)):(iTemp10?(3580 - (40 * fTemp13)):3540)):(iTemp7?(3540 - (540 * fTemp11)):3000)):(iTemp8?((300 * fTemp9) + 3000):3300));
			var fTemp113 = Math.tan((this.fConst3 * fTemp112));
			var fTemp114 = (1 / fTemp113);
			var fTemp115 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?(iTemp54?(iTemp56?140:(iTemp54?((60 * fTemp6) + 140):200)):200):(iTemp50?(200 - (65 * fTemp53)):135)):(iTemp48?((65 * fTemp51) + 135):200)):(iTemp46?(200 - (70 * fTemp49)):130)):(iTemp44?(130 - fTemp83):120)):120):120):120):(iTemp35?(fTemp96 + 120):140)):(iTemp33?(140 - fTemp95):120)):120):120):120):(iTemp25?(fTemp94 + 120):140)):(iTemp22?((60 * fTemp26) + 140):200)):(iTemp20?(200 - fTemp24):120)):120):(iTemp16?((80 * fTemp19) + 120):200)):(iTemp14?(200 - (60 * fTemp17)):140)):(iTemp12?(140 - fTemp63):120)):120):(iTemp7?((15 * fTemp11) + 120):135)):(iTemp8?(135 - (15 * fTemp9)):120)) / fTemp112);
			var fTemp116 = (((fTemp114 + fTemp115) / fTemp113) + 1);
			this.fRec13[0] = (fTemp5 - (((this.fRec13[2] * (((fTemp114 - fTemp115) / fTemp113) + 1)) + (2 * (this.fRec13[1] * (1 - (1 / mydsp_faustpower2_f(fTemp113)))))) / fTemp116));
			var fTemp117 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp48?(iTemp50?(iTemp52?0.001:(iTemp50?((0.000778 * fTemp53) + 0.001):0.001778)):(iTemp48?(0.001778 - (0.001147 * fTemp51)):0.000631)):(iTemp46?((0.099369 * fTemp49) + 0.000631):0.1)):(iTemp44?((0.025893 * fTemp47) + 0.1):0.125893)):(iTemp42?(0.125893 - (0.086082 * fTemp45)):0.039811)):(iTemp39?(0.039811 - (0.029811 * fTemp43)):0.01)):(iTemp37?((0.005849 * fTemp40) + 0.01):0.015849)):(iTemp35?(0.015849 - (0.00326 * fTemp38)):0.012589)):(iTemp33?((0.087411 * fTemp36) + 0.012589):0.1)):fTemp109):(iTemp29?((0.004104 * fTemp32) + 0.015849):0.019953)):0.019953):(iTemp25?(0.019953 - (0.016791 * fTemp28)):0.003162)):(iTemp22?(0.003162 - (0.001577 * fTemp26)):0.001585)):(iTemp20?((0.004725 * fTemp23) + 0.001585):0.00631)):(iTemp18?(0.00631 - (0.003148 * fTemp21)):0.003162)):(iTemp16?(0.003162 - (0.002162 * fTemp19)):0.001)):(iTemp14?((0.078433 * fTemp17) + 0.001):0.079433)):(iTemp12?((0.020567 * fTemp15) + 0.079433):0.1)):(iTemp10?(0.1 - (0.068377 * fTemp13)):0.031623)):(iTemp7?((0.018496 * fTemp11) + 0.031623):0.050119)):0.050119);
			var fTemp118 = (iSlow12?(fTemp73 * fTemp117):(fTemp72 * fTemp117));
			var fTemp119 = (((((((this.fRec0[2] * (0 - (fTemp74 / fTemp61))) + ((this.fRec0[0] * fTemp74) / fTemp61)) / fTemp71) + (((this.fRec10[2] * (0 - (fTemp87 / fTemp78))) + ((this.fRec10[0] * fTemp87) / fTemp78)) / fTemp85)) + (((this.fRec11[2] * (0 - (fTemp102 / fTemp92))) + ((this.fRec11[0] * fTemp102) / fTemp92)) / fTemp99)) + (((this.fRec12[2] * (0 - (fTemp111 / fTemp105))) + ((this.fRec12[0] * fTemp111) / fTemp105)) / fTemp108)) + (((this.fRec13[2] * (0 - (fTemp118 / fTemp113))) + ((this.fRec13[0] * fTemp118) / fTemp113)) / fTemp116));
			output0[i] = fTemp119;
			output1[i] = fTemp119;
			this.iVec0[1] = this.iVec0[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec5[1] = this.fRec5[0];
			this.iRec6[1] = this.iRec6[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fRec13[2] = this.fRec13[1];
			this.fRec13[1] = this.fRec13[0];
			
		}
		
	}
	
}

