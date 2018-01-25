
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider0;
	this.fRec0 = new Float32Array(2);
	this.fHslider1;
	this.fRec1 = new Float32Array(2);
	this.fHslider2;
	this.fRec2 = new Float32Array(2);
	this.fHslider3;
	this.fRec3 = new Float32Array(2);
	this.fHslider4;
	this.fRec4 = new Float32Array(2);
	this.fHslider5;
	this.fRec5 = new Float32Array(2);
	this.fHslider6;
	this.fRec6 = new Float32Array(2);
	this.fHslider7;
	this.fRec7 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "CICM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)CICM 2013");
		m.declare("hoa.lib/author", "Pierre Guillot");
		m.declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m.declare("hoa.lib/name", "High Order Ambisonics library");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "fourSourcesToOcto");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 4;
		
	}
	this.getNumOutputs = function() {
		return 8;
		
	}
	this.getInputRate = function(channel) {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
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
		this.fConst0 = Math.exp((0 - (50 / min_f(192000, max_f(1, this.fSamplingFreq)))));
		this.fConst1 = (1 - this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 1;
		this.fHslider1 = 1;
		this.fHslider2 = 1;
		this.fHslider3 = 1;
		this.fHslider4 = 0;
		this.fHslider5 = 0;
		this.fHslider6 = 0;
		this.fHslider7 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec5[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec6[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec7[l7] = 0;
			
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
		ui_interface.openVerticalBox("fourSourcesToOcto");
		ui_interface.addHorizontalSlider("Angle1", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, -6.28319, 6.28319, 0.001);
		ui_interface.addHorizontalSlider("Angle2", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0, -6.28319, 6.28319, 0.001);
		ui_interface.addHorizontalSlider("Angle3", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, -6.28319, 6.28319, 0.001);
		ui_interface.addHorizontalSlider("Angle4", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0, -6.28319, 6.28319, 0.001);
		ui_interface.addHorizontalSlider("Radius1", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 1, 0, 5, 0.001);
		ui_interface.addHorizontalSlider("Radius2", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0, 5, 0.001);
		ui_interface.addHorizontalSlider("Radius3", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 5, 0.001);
		ui_interface.addHorizontalSlider("Radius4", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 1, 0, 5, 0.001);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		var fSlow0 = (this.fConst1 * this.fHslider0);
		var fSlow1 = (this.fConst1 * this.fHslider1);
		var fSlow2 = (this.fConst1 * this.fHslider2);
		var fSlow3 = (this.fConst1 * this.fHslider3);
		var fSlow4 = (this.fConst1 * this.fHslider4);
		var fSlow5 = (this.fConst1 * this.fHslider5);
		var fSlow6 = (this.fConst1 * this.fHslider6);
		var fSlow7 = (this.fConst1 * this.fHslider7);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow0 + (this.fConst0 * this.fRec0[1]));
			var iTemp0 = (this.fRec0[0] > 1);
			var iTemp1 = (this.fRec0[0] < 1);
			var fTemp2 = (iTemp0 + (this.fRec0[0] * iTemp1));
			var fTemp3 = ((1.38629 * (1 - fTemp2)) + 1);
			var fTemp4 = input0[i];
			var fTemp5 = (iTemp1 + (mydsp_faustpower2_f(this.fRec0[0]) * iTemp0));
			this.fRec1[0] = (fSlow1 + (this.fConst0 * this.fRec1[1]));
			var iTemp6 = (this.fRec1[0] > 1);
			var iTemp7 = (this.fRec1[0] < 1);
			var fTemp8 = (iTemp6 + (this.fRec1[0] * iTemp7));
			var fTemp9 = ((1.38629 * (1 - fTemp8)) + 1);
			var fTemp10 = input1[i];
			var fTemp11 = (iTemp7 + (mydsp_faustpower2_f(this.fRec1[0]) * iTemp6));
			this.fRec2[0] = (fSlow2 + (this.fConst0 * this.fRec2[1]));
			var iTemp12 = (this.fRec2[0] > 1);
			var iTemp13 = (this.fRec2[0] < 1);
			var fTemp14 = (iTemp12 + (this.fRec2[0] * iTemp13));
			var fTemp15 = ((1.38629 * (1 - fTemp14)) + 1);
			var fTemp16 = input2[i];
			var fTemp17 = (iTemp13 + (mydsp_faustpower2_f(this.fRec2[0]) * iTemp12));
			this.fRec3[0] = (fSlow3 + (this.fConst0 * this.fRec3[1]));
			var iTemp18 = (this.fRec3[0] > 1);
			var iTemp19 = (this.fRec3[0] < 1);
			var fTemp20 = (iTemp18 + (this.fRec3[0] * iTemp19));
			var fTemp21 = ((1.38629 * (1 - fTemp20)) + 1);
			var fTemp22 = input3[i];
			var fTemp23 = (iTemp19 + (mydsp_faustpower2_f(this.fRec3[0]) * iTemp18));
			var fTemp24 = (0.142857 * (((((fTemp3 * fTemp4) / fTemp5) + ((fTemp9 * fTemp10) / fTemp11)) + ((fTemp15 * fTemp16) / fTemp17)) + ((fTemp21 * fTemp22) / fTemp23)));
			var fTemp25 = (2 * fTemp2);
			var fTemp26 = ((2 * ((fTemp2 * (fTemp25 > 0)) * (fTemp25 <= 1))) + (fTemp25 > 1));
			this.fRec4[0] = (fSlow4 + (this.fConst0 * this.fRec4[1]));
			var fTemp27 = (2 * fTemp8);
			var fTemp28 = ((2 * ((fTemp8 * (fTemp27 > 0)) * (fTemp27 <= 1))) + (fTemp27 > 1));
			this.fRec5[0] = (fSlow5 + (this.fConst0 * this.fRec5[1]));
			var fTemp29 = (2 * fTemp14);
			var fTemp30 = ((2 * ((fTemp14 * (fTemp29 > 0)) * (fTemp29 <= 1))) + (fTemp29 > 1));
			this.fRec6[0] = (fSlow6 + (this.fConst0 * this.fRec6[1]));
			var fTemp31 = (2 * fTemp20);
			var fTemp32 = ((2 * ((fTemp20 * (fTemp31 > 0)) * (fTemp31 <= 1))) + (fTemp31 > 1));
			this.fRec7[0] = (fSlow7 + (this.fConst0 * this.fRec7[1]));
			var fTemp33 = (((((((fTemp3 * fTemp26) * Math.cos(this.fRec4[0])) * fTemp4) / fTemp5) + ((((fTemp9 * fTemp28) * Math.cos(this.fRec5[0])) * fTemp10) / fTemp11)) + ((((fTemp15 * fTemp30) * Math.cos(this.fRec6[0])) * fTemp16) / fTemp17)) + ((((fTemp21 * fTemp32) * Math.cos(this.fRec7[0])) * fTemp22) / fTemp23));
			var fTemp34 = (0.214286 * fTemp33);
			var fTemp35 = (2 * this.fRec4[0]);
			var fTemp36 = (1.38629 * fTemp2);
			var fTemp37 = (fTemp36 + -0.693147);
			var fTemp38 = (2.4663 * fTemp37);
			var fTemp39 = ((2.4663 * ((fTemp37 * (fTemp38 > 0)) * (fTemp38 <= 1))) + (fTemp38 > 1));
			var fTemp40 = (2 * this.fRec5[0]);
			var fTemp41 = (1.38629 * fTemp8);
			var fTemp42 = (fTemp41 + -0.693147);
			var fTemp43 = (2.4663 * fTemp42);
			var fTemp44 = ((2.4663 * ((fTemp42 * (fTemp43 > 0)) * (fTemp43 <= 1))) + (fTemp43 > 1));
			var fTemp45 = (2 * this.fRec6[0]);
			var fTemp46 = (1.38629 * fTemp14);
			var fTemp47 = (fTemp46 + -0.693147);
			var fTemp48 = (2.4663 * fTemp47);
			var fTemp49 = ((2.4663 * ((fTemp47 * (fTemp48 > 0)) * (fTemp48 <= 1))) + (fTemp48 > 1));
			var fTemp50 = (2 * this.fRec7[0]);
			var fTemp51 = (1.38629 * fTemp20);
			var fTemp52 = (fTemp51 + -0.693147);
			var fTemp53 = (2.4663 * fTemp52);
			var fTemp54 = ((2.4663 * ((fTemp52 * (fTemp53 > 0)) * (fTemp53 <= 1))) + (fTemp53 > 1));
			var fTemp55 = (0.0857143 * (((((((Math.cos(fTemp35) * fTemp3) * fTemp39) * fTemp4) / fTemp5) + ((((Math.cos(fTemp40) * fTemp9) * fTemp44) * fTemp10) / fTemp11)) + ((((Math.cos(fTemp45) * fTemp15) * fTemp49) * fTemp16) / fTemp17)) + ((((Math.cos(fTemp50) * fTemp21) * fTemp54) * fTemp22) / fTemp23)));
			var fTemp56 = (3 * this.fRec4[0]);
			var fTemp57 = (fTemp36 + -1.09861);
			var fTemp58 = (3.47606 * fTemp57);
			var fTemp59 = ((3.47606 * ((fTemp57 * (fTemp58 > 0)) * (fTemp58 <= 1))) + (fTemp58 > 1));
			var fTemp60 = (3 * this.fRec5[0]);
			var fTemp61 = (fTemp41 + -1.09861);
			var fTemp62 = (3.47606 * fTemp61);
			var fTemp63 = ((3.47606 * ((fTemp61 * (fTemp62 > 0)) * (fTemp62 <= 1))) + (fTemp62 > 1));
			var fTemp64 = (3 * this.fRec6[0]);
			var fTemp65 = (fTemp46 + -1.09861);
			var fTemp66 = (3.47606 * fTemp65);
			var fTemp67 = ((3.47606 * ((fTemp65 * (fTemp66 > 0)) * (fTemp66 <= 1))) + (fTemp66 > 1));
			var fTemp68 = (3 * this.fRec7[0]);
			var fTemp69 = (fTemp51 + -1.09861);
			var fTemp70 = (3.47606 * fTemp69);
			var fTemp71 = ((3.47606 * ((fTemp69 * (fTemp70 > 0)) * (fTemp70 <= 1))) + (fTemp70 > 1));
			var fTemp72 = (((((((Math.cos(fTemp56) * fTemp3) * fTemp59) * fTemp4) / fTemp5) + ((((Math.cos(fTemp60) * fTemp9) * fTemp63) * fTemp10) / fTemp11)) + ((((Math.cos(fTemp64) * fTemp15) * fTemp67) * fTemp16) / fTemp17)) + ((((Math.cos(fTemp68) * fTemp21) * fTemp71) * fTemp22) / fTemp23));
			var fTemp73 = (0.0142857 * fTemp72);
			output0[i] = (((fTemp24 + fTemp34) + fTemp55) + fTemp73);
			var fTemp74 = (((((((fTemp3 * Math.sin(this.fRec4[0])) * fTemp26) * fTemp4) / fTemp5) + ((((fTemp9 * Math.sin(this.fRec5[0])) * fTemp28) * fTemp10) / fTemp11)) + ((((fTemp15 * Math.sin(this.fRec6[0])) * fTemp30) * fTemp16) / fTemp17)) + ((((fTemp21 * Math.sin(this.fRec7[0])) * fTemp32) * fTemp22) / fTemp23));
			var fTemp75 = (0.151523 * fTemp74);
			var fTemp76 = (0.0857143 * (((((((Math.sin(fTemp35) * fTemp3) * fTemp39) * fTemp4) / fTemp5) + ((((Math.sin(fTemp40) * fTemp9) * fTemp44) * fTemp10) / fTemp11)) + ((((Math.sin(fTemp45) * fTemp15) * fTemp49) * fTemp16) / fTemp17)) + ((((Math.sin(fTemp50) * fTemp21) * fTemp54) * fTemp22) / fTemp23)));
			var fTemp77 = (((((((Math.sin(fTemp56) * fTemp3) * fTemp59) * fTemp4) / fTemp5) + ((((Math.sin(fTemp60) * fTemp9) * fTemp63) * fTemp10) / fTemp11)) + ((((Math.sin(fTemp64) * fTemp15) * fTemp67) * fTemp16) / fTemp17)) + ((((Math.sin(fTemp68) * fTemp21) * fTemp71) * fTemp22) / fTemp23));
			output1[i] = (((((fTemp24 + fTemp75) + (0.151523 * fTemp33)) + fTemp76) + (0.0101015 * fTemp77)) - (0.0101015 * fTemp72));
			var fTemp78 = (0.214286 * fTemp74);
			var fTemp79 = (0.0142857 * fTemp77);
			output2[i] = ((fTemp24 + fTemp78) - (fTemp55 + fTemp79));
			var fTemp80 = (0.151523 * fTemp33);
			output3[i] = ((((fTemp24 + (0.151523 * fTemp74)) + (0.0101015 * fTemp77)) + (0.0101015 * fTemp72)) - (fTemp76 + fTemp80));
			output4[i] = ((fTemp24 + fTemp55) - (fTemp34 + fTemp73));
			output5[i] = (((fTemp24 + fTemp76) + (0.0101015 * fTemp72)) - ((fTemp75 + (0.151523 * fTemp33)) + (0.0101015 * fTemp77)));
			output6[i] = ((fTemp24 + fTemp79) - (fTemp55 + fTemp78));
			output7[i] = ((fTemp24 + fTemp80) - (((fTemp76 + (0.151523 * fTemp74)) + (0.0101015 * fTemp77)) + (0.0101015 * fTemp72)));
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			
		}
		
	}
	
}

