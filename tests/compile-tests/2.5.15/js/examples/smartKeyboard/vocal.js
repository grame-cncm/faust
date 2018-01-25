
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
	this.fRec3 = new Float32Array(2);
	this.fHslider2;
	this.fConst2;
	this.fConst3;
	this.fConst4;
	this.fRec4 = new Float32Array(2);
	this.fConst5;
	this.fRec5 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fConst6;
	this.fHslider3;
	this.fRec6 = new Float32Array(2);
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
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Piano Keyboard':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "vocal");
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
		this.fConst2 = (37.6991 / this.fConst0);
		this.fConst3 = Math.sin(this.fConst2);
		this.fConst4 = Math.cos(this.fConst2);
		this.fConst5 = (0 - this.fConst3);
		this.fConst6 = (3.14159 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.25;
		this.fHslider1 = 0.5;
		this.fHslider2 = 0.05;
		this.fHslider3 = 2;
		
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
			this.fRec5[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec6[l5] = 0;
			
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
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.25, 0, 1, 0.01);
		ui_interface.declare("fHslider2", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("vibrato", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.05, 0, 0.1, 0.01);
		ui_interface.declare("fHslider3", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("vowel", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 2, 0, 4, 0.01);
		ui_interface.addHorizontalSlider("x", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.001 * this.fHslider1);
		var fSlow2 = this.fHslider2;
		var fSlow3 = (0.001 * this.fHslider3);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec3[0] = (fSlow1 + (0.999 * this.fRec3[1]));
			this.fRec4[0] = ((this.fConst3 * this.fRec5[1]) + (this.fConst4 * this.fRec4[1]));
			var iTemp0 = (1 - this.iVec0[1]);
			this.fRec5[0] = (((this.fConst4 * this.fRec5[1]) + (this.fConst5 * this.fRec4[1])) + iTemp0);
			var fTemp1 = max_f(1e-07, Math.abs((((200 * this.fRec3[0]) + 50) * ((fSlow2 * this.fRec4[0]) + 1))));
			var fTemp2 = (this.fRec1[1] + (this.fConst1 * fTemp1));
			var fTemp3 = (fTemp2 + -1);
			var iTemp4 = (fTemp3 < 0);
			this.fRec1[0] = (iTemp4?fTemp2:fTemp3);
			var fRec2 = (iTemp4?fTemp2:(fTemp2 + (fTemp3 * (1 - (this.fConst0 / fTemp1)))));
			var fTemp5 = (fSlow0 * ((2 * fRec2) + -1));
			this.fRec6[0] = (fSlow3 + (0.999 * this.fRec6[1]));
			var fTemp6 = (this.fRec6[0] + 5);
			var iTemp7 = (fTemp6 < 23);
			var iTemp8 = (fTemp6 < 24);
			var fTemp9 = (this.fRec6[0] + -18);
			var iTemp10 = (fTemp6 < 22);
			var fTemp11 = (this.fRec6[0] + -17);
			var iTemp12 = (fTemp6 < 21);
			var fTemp13 = (this.fRec6[0] + -16);
			var iTemp14 = (fTemp6 < 20);
			var fTemp15 = (this.fRec6[0] + -15);
			var iTemp16 = (fTemp6 < 19);
			var fTemp17 = (this.fRec6[0] + -14);
			var iTemp18 = (fTemp6 < 18);
			var fTemp19 = (this.fRec6[0] + -13);
			var iTemp20 = (fTemp6 < 17);
			var fTemp21 = (this.fRec6[0] + -12);
			var iTemp22 = (fTemp6 < 16);
			var fTemp23 = (this.fRec6[0] + -11);
			var fTemp24 = (80 * fTemp23);
			var iTemp25 = (fTemp6 < 15);
			var fTemp26 = (this.fRec6[0] + -10);
			var iTemp27 = (fTemp6 < 14);
			var fTemp28 = (this.fRec6[0] + -9);
			var iTemp29 = (fTemp6 < 13);
			var fTemp30 = (this.fRec6[0] + -8);
			var iTemp31 = (fTemp6 < 12);
			var fTemp32 = (this.fRec6[0] + -7);
			var iTemp33 = (fTemp6 < 11);
			var fTemp34 = (this.fRec6[0] + -6);
			var iTemp35 = (fTemp6 < 10);
			var fTemp36 = (this.fRec6[0] + -5);
			var iTemp37 = (fTemp6 < 9);
			var fTemp38 = (this.fRec6[0] + -4);
			var iTemp39 = (fTemp6 < 8);
			var fTemp40 = (this.fRec6[0] + -3);
			var fTemp41 = (50 * fTemp40);
			var iTemp42 = (fTemp6 < 7);
			var fTemp43 = (this.fRec6[0] + -2);
			var iTemp44 = (fTemp6 < 6);
			var fTemp45 = (this.fRec6[0] + -1);
			var iTemp46 = (fTemp6 < 5);
			var iTemp47 = (fTemp6 < 4);
			var fTemp48 = (this.fRec6[0] + 1);
			var iTemp49 = (fTemp6 < 3);
			var fTemp50 = (this.fRec6[0] + 2);
			var iTemp51 = (fTemp6 < 2);
			var fTemp52 = (this.fRec6[0] + 3);
			var iTemp53 = (fTemp6 < 1);
			var fTemp54 = (this.fRec6[0] + 4);
			var iTemp55 = (fTemp6 < 0);
			var fTemp56 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?800:(iTemp53?(800 - (400 * fTemp6)):400)):(iTemp51?(400 - (50 * fTemp54)):350)):(iTemp49?((100 * fTemp52) + 350):450)):(iTemp47?(450 - (125 * fTemp50)):325)):(iTemp46?((275 * fTemp48) + 325):600)):(iTemp44?(600 - (200 * this.fRec6[0])):400)):(iTemp42?(400 - (150 * fTemp45)):250)):(iTemp39?((150 * fTemp43) + 250):400)):(iTemp37?(400 - fTemp41):350)):(iTemp35?((310 * fTemp38) + 350):660)):(iTemp33?(660 - (220 * fTemp36)):440)):(iTemp31?(440 - (170 * fTemp34)):270)):(iTemp29?((160 * fTemp32) + 270):430)):(iTemp27?(430 - (60 * fTemp30)):370)):(iTemp25?((430 * fTemp28) + 370):800)):(iTemp22?(800 - (450 * fTemp26)):350)):(iTemp20?(350 - fTemp24):270)):(iTemp18?((180 * fTemp21) + 270):450)):(iTemp16?(450 - (125 * fTemp19)):325)):(iTemp14?(325 * (fTemp17 + 1)):650)):(iTemp12?(650 - (250 * fTemp15)):400)):(iTemp10?(400 - (110 * fTemp13)):290)):(iTemp7?((110 * fTemp11) + 290):400)):(iTemp8?(400 - (50 * fTemp9)):350));
			this.fRec7[0] = (fSlow1 + (0.999 * this.fRec7[1]));
			this.fRec8[0] = ((this.fConst3 * this.fRec9[1]) + (this.fConst4 * this.fRec8[1]));
			this.fRec9[0] = (((this.fConst4 * this.fRec9[1]) + (this.fConst5 * this.fRec8[1])) + iTemp0);
			var fTemp57 = (((200 * this.fRec7[0]) + 50) * ((fSlow2 * this.fRec8[0]) + 1));
			var fTemp58 = ((fTemp56 <= fTemp57)?fTemp57:fTemp56);
			var fTemp59 = Math.tan((this.fConst6 * fTemp58));
			var fTemp60 = (1 / fTemp59);
			var fTemp61 = (20 * fTemp15);
			var fTemp62 = (20 * fTemp26);
			var fTemp63 = (10 * fTemp36);
			var fTemp64 = (10 * fTemp48);
			var fTemp65 = (20 * fTemp50);
			var fTemp66 = (20 * fTemp52);
			var fTemp67 = (20 * fTemp6);
			var fTemp68 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?80:(iTemp53?(80 - fTemp67):60)):(iTemp51?(60 - (10 * fTemp54)):50)):(iTemp49?(fTemp66 + 50):70)):(iTemp47?(70 - fTemp65):50)):(iTemp46?(fTemp64 + 50):60)):(iTemp44?(60 - (20 * this.fRec6[0])):40)):(iTemp42?((20 * fTemp45) + 40):60)):(iTemp39?(60 - (20 * fTemp43)):40)):40):(iTemp35?(40 * (fTemp38 + 1)):80)):(iTemp33?(80 - fTemp63):70)):(iTemp31?(70 - (30 * fTemp34)):40)):40):40):(iTemp25?(40 * (fTemp28 + 1)):80)):(iTemp22?(80 - fTemp62):60)):60):(iTemp18?(60 - (20 * fTemp21)):40)):(iTemp16?((10 * fTemp19) + 40):50)):50):(iTemp12?(fTemp61 + 50):70)):(iTemp10?(70 - (30 * fTemp13)):40)):(iTemp7?((30 * fTemp11) + 40):70)):(iTemp8?(70 - (30 * fTemp9)):40)) / fTemp58);
			var fTemp69 = (((fTemp60 + fTemp68) / fTemp59) + 1);
			this.fRec0[0] = (fTemp5 - (((this.fRec0[2] * (((fTemp60 - fTemp68) / fTemp59) + 1)) + (2 * (this.fRec0[1] * (1 - (1 / mydsp_faustpower2_f(fTemp59)))))) / fTemp69));
			var fTemp70 = ((0.00366667 * (400 - fTemp57)) + 3);
			var fTemp71 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?1150:(iTemp53?((450 * fTemp6) + 1150):1600)):(iTemp51?((100 * fTemp54) + 1600):1700)):(iTemp49?(1700 - (900 * fTemp52)):800)):(iTemp47?(800 - (100 * fTemp50)):700)):(iTemp46?((340 * fTemp48) + 700):1040)):(iTemp44?((580 * this.fRec6[0]) + 1040):1620)):(iTemp42?((130 * fTemp45) + 1620):1750)):(iTemp39?(1750 - (1000 * fTemp43)):750)):(iTemp37?(750 - (150 * fTemp40)):600)):(iTemp35?((520 * fTemp38) + 600):1120)):(iTemp33?((680 * fTemp36) + 1120):1800)):(iTemp31?((50 * fTemp34) + 1800):1850)):(iTemp29?(1850 - (1030 * fTemp32)):820)):(iTemp27?(820 - (190 * fTemp30)):630)):(iTemp25?((520 * fTemp28) + 630):1150)):(iTemp22?((850 * fTemp26) + 1150):2000)):(iTemp20?((140 * fTemp23) + 2000):2140)):(iTemp18?(2140 - (1340 * fTemp21)):800)):(iTemp16?(800 - (100 * fTemp19)):700)):(iTemp14?((380 * fTemp17) + 700):1080)):(iTemp12?((620 * fTemp15) + 1080):1700)):(iTemp10?((170 * fTemp13) + 1700):1870)):(iTemp7?(1870 - (1070 * fTemp11)):800)):(iTemp8?(800 - (200 * fTemp9)):600));
			var fTemp72 = ((2 * fTemp57) + 30);
			var fTemp73 = (((fTemp71 >= 1300) & (fTemp57 >= 200))?(fTemp71 - (0.000952381 * ((fTemp57 + -200) * (fTemp71 + -1300)))):((fTemp71 <= fTemp72)?fTemp72:fTemp71));
			var fTemp74 = Math.tan((this.fConst6 * fTemp73));
			var fTemp75 = (1 / fTemp74);
			var fTemp76 = (10 * fTemp11);
			var fTemp77 = (10 * fTemp15);
			var fTemp78 = (10 * fTemp38);
			var fTemp79 = (10 * this.fRec6[0]);
			var fTemp80 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?90:(iTemp53?(90 - (10 * fTemp6)):80)):(iTemp51?((20 * fTemp54) + 80):100)):(iTemp49?(100 - fTemp66):80)):(iTemp47?(80 - fTemp65):60)):(iTemp46?(fTemp64 + 60):70)):(iTemp44?(fTemp79 + 70):80)):(iTemp42?((10 * fTemp45) + 80):90)):(iTemp39?(90 - (10 * fTemp43)):80)):80):(iTemp35?(fTemp78 + 80):90)):(iTemp33?(90 - fTemp63):80)):(iTemp31?((10 * fTemp34) + 80):90)):(iTemp29?(90 - (10 * fTemp32)):80)):(iTemp27?(80 - (20 * fTemp30)):60)):(iTemp25?((30 * fTemp28) + 60):90)):(iTemp22?((10 * fTemp26) + 90):100)):(iTemp20?(100 - (10 * fTemp23)):90)):(iTemp18?(90 - (10 * fTemp21)):80)):(iTemp16?(80 - (20 * fTemp19)):60)):(iTemp14?((30 * fTemp17) + 60):90)):(iTemp12?(90 - fTemp77):80)):(iTemp10?((10 * fTemp13) + 80):90)):(iTemp7?(90 - fTemp76):80)):(iTemp8?(80 - (20 * fTemp9)):60)) / fTemp73);
			var fTemp81 = (((fTemp75 + fTemp80) / fTemp74) + 1);
			this.fRec10[0] = (fTemp5 - (((this.fRec10[2] * (((fTemp75 - fTemp80) / fTemp74) + 1)) + (2 * (this.fRec10[1] * (1 - (1 / mydsp_faustpower2_f(fTemp74)))))) / fTemp81));
			var fTemp82 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?0.630957:(iTemp53?(0.630957 - (0.567861 * fTemp6)):0.063096)):(iTemp51?((0.036904 * fTemp54) + 0.063096):0.1)):(iTemp49?((0.254813 * fTemp52) + 0.1):0.354813)):(iTemp47?(0.354813 - (0.103624 * fTemp50)):0.251189)):(iTemp46?((0.195495 * fTemp48) + 0.251189):0.446684)):(iTemp44?(0.446684 - (0.195495 * this.fRec6[0])):0.251189)):(iTemp42?(0.251189 - (0.219566 * fTemp45)):0.031623)):(iTemp39?((0.250215 * fTemp43) + 0.031623):0.281838)):(iTemp37?(0.281838 - (0.181838 * fTemp40)):0.1)):(iTemp35?((0.401187 * fTemp38) + 0.1):0.501187)):(iTemp33?(0.501187 - (0.301661 * fTemp36)):0.199526)):(iTemp31?(0.199526 - (0.13643 * fTemp34)):0.063096)):(iTemp29?((0.253132 * fTemp32) + 0.063096):0.316228)):(iTemp27?(0.316228 - (0.216228 * fTemp30)):0.1)):(iTemp25?((0.401187 * fTemp28) + 0.1):0.501187)):(iTemp22?(0.501187 - (0.401187 * fTemp26)):0.1)):(iTemp20?((0.151189 * fTemp23) + 0.1):0.251189)):(iTemp18?((0.030649 * fTemp21) + 0.251189):0.281838)):(iTemp16?(0.281838 - (0.123349 * fTemp19)):0.158489)):(iTemp14?((0.342698 * fTemp17) + 0.158489):0.501187)):(iTemp12?(0.501187 - (0.301661 * fTemp15)):0.199526)):(iTemp10?(0.199526 - (0.021698 * fTemp13)):0.177828)):(iTemp7?((0.1384 * fTemp11) + 0.177828):0.316228)):(iTemp8?(0.316228 - (0.216228 * fTemp9)):0.1));
			var fTemp83 = (100 * fTemp9);
			var fTemp84 = (50 * fTemp17);
			var fTemp85 = (50 * fTemp36);
			var fTemp86 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?2800:(iTemp53?(2800 - (100 * fTemp6)):2700)):2700):(iTemp49?((130 * fTemp52) + 2700):2830)):(iTemp47?(2830 - (300 * fTemp50)):2530)):(iTemp46?(2530 - (280 * fTemp48)):2250)):(iTemp44?((150 * this.fRec6[0]) + 2250):2400)):(iTemp42?((200 * fTemp45) + 2400):2600)):(iTemp39?(2600 - (200 * fTemp43)):2400)):2400):(iTemp35?((350 * fTemp38) + 2400):2750)):(iTemp33?(2750 - fTemp85):2700)):(iTemp31?((200 * fTemp34) + 2700):2900)):(iTemp29?(2900 - (200 * fTemp32)):2700)):(iTemp27?((50 * fTemp30) + 2700):2750)):(iTemp25?((150 * fTemp28) + 2750):2900)):(iTemp22?(2900 - (100 * fTemp26)):2800)):(iTemp20?((150 * fTemp23) + 2800):2950)):(iTemp18?(2950 - (120 * fTemp21)):2830)):(iTemp16?(2830 - (130 * fTemp19)):2700)):(iTemp14?(2700 - fTemp84):2650)):(iTemp12?(2650 - (50 * fTemp15)):2600)):(iTemp10?((200 * fTemp13) + 2600):2800)):(iTemp7?(2800 - (200 * fTemp11)):2600)):(iTemp8?(fTemp83 + 2600):2700));
			var fTemp87 = Math.tan((this.fConst6 * fTemp86));
			var fTemp88 = (1 / fTemp87);
			var fTemp89 = (20 * fTemp28);
			var fTemp90 = (20 * fTemp36);
			var fTemp91 = (20 * fTemp38);
			var fTemp92 = (60 * fTemp48);
			var fTemp93 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?120:(iTemp49?(120 - fTemp66):100)):(iTemp47?((70 * fTemp50) + 100):170)):(iTemp46?(170 - fTemp92):110)):(iTemp44?(110 - fTemp79):100)):100):100):100):(iTemp35?(fTemp91 + 100):120)):(iTemp33?(120 - fTemp90):100)):100):100):100):(iTemp25?(fTemp89 + 100):120)):120):(iTemp20?(120 - (20 * fTemp23)):100)):100):(iTemp16?((70 * fTemp19) + 100):170)):(iTemp14?(170 - fTemp84):120)):(iTemp12?(120 - fTemp61):100)):100):100):100) / fTemp86);
			var fTemp94 = (((fTemp88 + fTemp93) / fTemp87) + 1);
			this.fRec11[0] = (fTemp5 - (((this.fRec11[2] * (((fTemp88 - fTemp93) / fTemp87) + 1)) + (2 * (this.fRec11[1] * (1 - (1 / mydsp_faustpower2_f(fTemp87)))))) / fTemp94));
			var fTemp95 = (iTemp18?((0.029314 * fTemp21) + 0.050119):0.079433);
			var fTemp96 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?0.1:(iTemp53?(0.1 - (0.068377 * fTemp6)):0.031623)):0.031623):(iTemp49?((0.126866 * fTemp52) + 0.031623):0.158489)):(iTemp47?(0.158489 - (0.126866 * fTemp50)):0.031623)):(iTemp46?((0.32319 * fTemp48) + 0.031623):0.354813)):0.354813):(iTemp42?(0.354813 - (0.196324 * fTemp45)):0.158489)):(iTemp39?(0.158489 - (0.069364 * fTemp43)):0.089125)):(iTemp37?(0.089125 - (0.064006 * fTemp40)):0.025119)):(iTemp35?((0.045676 * fTemp38) + 0.025119):0.070795)):(iTemp33?((0.055098 * fTemp36) + 0.070795):0.125893)):(iTemp31?(0.125893 - (0.062797 * fTemp34)):0.063096)):(iTemp29?(0.063096 - (0.012977 * fTemp32)):0.050119)):(iTemp27?((0.020676 * fTemp30) + 0.050119):0.070795)):(iTemp25?(0.070795 - (0.045676 * fTemp28)):0.025119)):(iTemp22?((0.152709 * fTemp26) + 0.025119):0.177828)):(iTemp20?(0.177828 - (0.127709 * fTemp23)):0.050119)):fTemp95):(iTemp16?(0.079433 - (0.06165 * fTemp19)):0.017783)):(iTemp14?((0.428901 * fTemp17) + 0.017783):0.446684)):(iTemp12?(0.446684 - (0.195495 * fTemp15)):0.251189)):(iTemp10?(0.251189 - (0.125296 * fTemp13)):0.125893)):(iTemp7?((0.125296 * fTemp11) + 0.125893):0.251189)):(iTemp8?(0.251189 - (0.109935 * fTemp9)):0.141254));
			var fTemp97 = (350 * this.fRec6[0]);
			var fTemp98 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?3500:(iTemp53?(3500 - (200 * fTemp6)):3300)):(iTemp51?((400 * fTemp54) + 3300):3700)):(iTemp49?(3700 - (200 * fTemp52)):3500)):3500):(iTemp46?(3500 - (1050 * fTemp48)):2450)):(iTemp44?(fTemp97 + 2450):2800)):(iTemp42?((250 * fTemp45) + 2800):3050)):(iTemp39?(3050 - (450 * fTemp43)):2600)):(iTemp37?((75 * fTemp40) + 2600):2675)):(iTemp35?((325 * fTemp38) + 2675):3000)):3000):(iTemp31?((350 * fTemp34) + 3000):3350)):(iTemp29?(3350 - (350 * fTemp32)):3000)):3000):(iTemp25?((900 * fTemp28) + 3000):3900)):(iTemp22?(3900 - (300 * fTemp26)):3600)):(iTemp20?((300 * fTemp23) + 3600):3900)):(iTemp18?(3900 - (100 * fTemp21)):3800)):3800):(iTemp14?(3800 - (900 * fTemp17)):2900)):(iTemp12?((300 * fTemp15) + 2900):3200)):(iTemp10?((50 * fTemp13) + 3200):3250)):(iTemp7?(3250 - (450 * fTemp11)):2800)):(iTemp8?(fTemp83 + 2800):2900));
			var fTemp99 = Math.tan((this.fConst6 * fTemp98));
			var fTemp100 = (1 / fTemp99);
			var fTemp101 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?130:(iTemp53?(fTemp67 + 130):150)):150):(iTemp49?(150 - fTemp66):130)):(iTemp47?((50 * fTemp50) + 130):180)):(iTemp46?(180 - fTemp92):120)):120):120):120):120):(iTemp35?(fTemp78 + 120):130)):(iTemp33?(130 - fTemp63):120)):120):120):120):(iTemp25?((10 * fTemp28) + 120):130)):(iTemp22?(fTemp62 + 130):150)):(iTemp20?(150 - (30 * fTemp23)):120)):120):(iTemp16?((60 * fTemp19) + 120):180)):(iTemp14?(180 - fTemp84):130)):(iTemp12?(130 - fTemp77):120)):120):(iTemp7?(fTemp76 + 120):130)):(iTemp8?(130 - (10 * fTemp9)):120)) / fTemp98);
			var fTemp102 = (((fTemp100 + fTemp101) / fTemp99) + 1);
			this.fRec12[0] = (fTemp5 - (((this.fRec12[2] * (((fTemp100 - fTemp101) / fTemp99) + 1)) + (2 * (this.fRec12[1] * (1 - (1 / mydsp_faustpower2_f(fTemp99)))))) / fTemp102));
			var fTemp103 = (iTemp31?(0.1 - (0.084151 * fTemp34)):0.015849);
			var fTemp104 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?0.015849:(iTemp53?((0.001934 * fTemp6) + 0.015849):0.017783)):(iTemp51?(0.017783 - (0.001934 * fTemp54)):0.015849)):(iTemp49?((0.023962 * fTemp52) + 0.015849):0.039811)):(iTemp47?(0.039811 - (0.029811 * fTemp50)):0.01)):(iTemp46?((0.344813 * fTemp48) + 0.01):0.354813)):(iTemp44?(0.354813 - (0.103624 * this.fRec6[0])):0.251189)):(iTemp42?(0.251189 - (0.171756 * fTemp45)):0.079433)):(iTemp39?((0.020567 * fTemp43) + 0.079433):0.1)):(iTemp37?(0.1 - (0.060189 * fTemp40)):0.039811)):(iTemp35?((0.023285 * fTemp38) + 0.039811):0.063096)):(iTemp33?((0.036904 * fTemp36) + 0.063096):0.1)):fTemp103):(iTemp29?((0.063584 * fTemp32) + 0.015849):0.079433)):(iTemp27?(0.079433 - (0.04781 * fTemp30)):0.031623)):(iTemp25?((0.068377 * fTemp28) + 0.031623):0.1)):(iTemp22?(0.1 - (0.09 * fTemp26)):0.01)):(iTemp20?((0.040119 * fTemp23) + 0.01):0.050119)):fTemp95):(iTemp16?(0.079433 - (0.069433 * fTemp19)):0.01)):(iTemp14?((0.388107 * fTemp17) + 0.01):0.398107)):(iTemp12?(0.398107 - (0.198581 * fTemp15)):0.199526)):(iTemp10?(0.199526 - (0.099526 * fTemp13)):0.1)):(iTemp7?((0.151189 * fTemp11) + 0.1):0.251189)):(iTemp8?(0.251189 - (0.051663 * fTemp9)):0.199526));
			var fTemp105 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?4950:(iTemp46?(4950 - (2200 * fTemp48)):2750)):(iTemp44?(fTemp97 + 2750):3100)):(iTemp42?((240 * fTemp45) + 3100):3340)):(iTemp39?(3340 - (440 * fTemp43)):2900)):(iTemp37?(fTemp41 + 2900):2950)):(iTemp35?((400 * fTemp38) + 2950):3350)):(iTemp33?(3350 - fTemp85):3300)):(iTemp31?((290 * fTemp34) + 3300):3590)):(iTemp29?(3590 - (290 * fTemp32)):3300)):(iTemp27?((100 * fTemp30) + 3300):3400)):(iTemp25?((1550 * fTemp28) + 3400):4950)):4950):4950):4950):4950):(iTemp14?(4950 - (1700 * fTemp17)):3250)):(iTemp12?((330 * fTemp15) + 3250):3580)):(iTemp10?(3580 - (40 * fTemp13)):3540)):(iTemp7?(3540 - (540 * fTemp11)):3000)):(iTemp8?((300 * fTemp9) + 3000):3300));
			var fTemp106 = Math.tan((this.fConst6 * fTemp105));
			var fTemp107 = (1 / fTemp106);
			var fTemp108 = ((iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?(iTemp53?(iTemp55?140:(iTemp53?((60 * fTemp6) + 140):200)):200):(iTemp49?(200 - (65 * fTemp52)):135)):(iTemp47?((65 * fTemp50) + 135):200)):(iTemp46?(200 - (70 * fTemp48)):130)):(iTemp44?(130 - fTemp79):120)):120):120):120):(iTemp35?(fTemp91 + 120):140)):(iTemp33?(140 - fTemp90):120)):120):120):120):(iTemp25?(fTemp89 + 120):140)):(iTemp22?((60 * fTemp26) + 140):200)):(iTemp20?(200 - fTemp24):120)):120):(iTemp16?((80 * fTemp19) + 120):200)):(iTemp14?(200 - (60 * fTemp17)):140)):(iTemp12?(140 - fTemp61):120)):120):(iTemp7?((15 * fTemp11) + 120):135)):(iTemp8?(135 - (15 * fTemp9)):120)) / fTemp105);
			var fTemp109 = (((fTemp107 + fTemp108) / fTemp106) + 1);
			this.fRec13[0] = (fTemp5 - (((this.fRec13[2] * (((fTemp107 - fTemp108) / fTemp106) + 1)) + (2 * (this.fRec13[1] * (1 - (1 / mydsp_faustpower2_f(fTemp106)))))) / fTemp109));
			var fTemp110 = (iTemp7?(iTemp10?(iTemp12?(iTemp14?(iTemp16?(iTemp18?(iTemp20?(iTemp22?(iTemp25?(iTemp27?(iTemp29?(iTemp31?(iTemp33?(iTemp35?(iTemp37?(iTemp39?(iTemp42?(iTemp44?(iTemp46?(iTemp47?(iTemp49?(iTemp51?0.001:(iTemp49?((0.000778 * fTemp52) + 0.001):0.001778)):(iTemp47?(0.001778 - (0.001147 * fTemp50)):0.000631)):(iTemp46?((0.099369 * fTemp48) + 0.000631):0.1)):(iTemp44?((0.025893 * this.fRec6[0]) + 0.1):0.125893)):(iTemp42?(0.125893 - (0.086082 * fTemp45)):0.039811)):(iTemp39?(0.039811 - (0.029811 * fTemp43)):0.01)):(iTemp37?((0.005849 * fTemp40) + 0.01):0.015849)):(iTemp35?(0.015849 - (0.00326 * fTemp38)):0.012589)):(iTemp33?((0.087411 * fTemp36) + 0.012589):0.1)):fTemp103):(iTemp29?((0.004104 * fTemp32) + 0.015849):0.019953)):0.019953):(iTemp25?(0.019953 - (0.016791 * fTemp28)):0.003162)):(iTemp22?(0.003162 - (0.001577 * fTemp26)):0.001585)):(iTemp20?((0.004725 * fTemp23) + 0.001585):0.00631)):(iTemp18?(0.00631 - (0.003148 * fTemp21)):0.003162)):(iTemp16?(0.003162 - (0.002162 * fTemp19)):0.001)):(iTemp14?((0.078433 * fTemp17) + 0.001):0.079433)):(iTemp12?((0.020567 * fTemp15) + 0.079433):0.1)):(iTemp10?(0.1 - (0.068377 * fTemp13)):0.031623)):(iTemp7?((0.018496 * fTemp11) + 0.031623):0.050119)):0.050119);
			var fTemp111 = (((((((this.fRec0[2] * (0 - (fTemp70 / fTemp59))) + ((this.fRec0[0] * fTemp70) / fTemp59)) / fTemp69) + (((this.fRec10[2] * (0 - ((fTemp70 * fTemp82) / fTemp74))) + (((this.fRec10[0] * fTemp70) * fTemp82) / fTemp74)) / fTemp81)) + (((this.fRec11[2] * (0 - ((fTemp70 * fTemp96) / fTemp87))) + (((this.fRec11[0] * fTemp70) * fTemp96) / fTemp87)) / fTemp94)) + (((this.fRec12[2] * (0 - ((fTemp70 * fTemp104) / fTemp99))) + (((this.fRec12[0] * fTemp70) * fTemp104) / fTemp99)) / fTemp102)) + (((this.fRec13[2] * (0 - ((fTemp70 * fTemp110) / fTemp106))) + (((this.fRec13[0] * fTemp70) * fTemp110) / fTemp106)) / fTemp109));
			output0[i] = fTemp111;
			output1[i] = fTemp111;
			this.iVec0[1] = this.iVec0[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec6[1] = this.fRec6[0];
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

