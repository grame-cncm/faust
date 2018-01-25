
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
		m.declare("name", "oneSourceToStereo");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
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
		this.fConst0 = Math.exp((0 - (50 / min_f(192000, max_f(1, this.fSamplingFreq)))));
		this.fConst1 = (1 - this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 1;
		this.fHslider1 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
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
		ui_interface.openVerticalBox("oneSourceToStereo");
		ui_interface.addHorizontalSlider("Angle", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, -6.28319, 6.28319, 0.001);
		ui_interface.addHorizontalSlider("Radius", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 1, 0, 5, 0.001);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (this.fConst1 * this.fHslider0);
		var fSlow1 = (this.fConst1 * this.fHslider1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow0 + (this.fConst0 * this.fRec0[1]));
			var iTemp0 = (this.fRec0[0] > 1);
			var iTemp1 = (this.fRec0[0] < 1);
			var fTemp2 = (iTemp0 + (this.fRec0[0] * iTemp1));
			var fTemp3 = (input0[i] * ((2.07944 * (1 - fTemp2)) + 1));
			var fTemp4 = (3 * fTemp2);
			var fTemp5 = ((3 * ((fTemp2 * (fTemp4 > 0)) * (fTemp4 <= 1))) + (fTemp4 > 1));
			this.fRec1[0] = (fSlow1 + (this.fConst0 * this.fRec1[1]));
			var fTemp6 = (fTemp5 * Math.cos(this.fRec1[0]));
			var fTemp7 = (2 * this.fRec1[0]);
			var fTemp8 = (2.07944 * fTemp2);
			var fTemp9 = (fTemp8 + -0.693147);
			var fTemp10 = (2.4663 * fTemp9);
			var fTemp11 = ((2.4663 * ((fTemp9 * (fTemp10 > 0)) * (fTemp10 <= 1))) + (fTemp10 > 1));
			var fTemp12 = (Math.cos(fTemp7) * fTemp11);
			var fTemp13 = (0.0777778 * fTemp12);
			var fTemp14 = (3 * this.fRec1[0]);
			var fTemp15 = (fTemp8 + -1.09861);
			var fTemp16 = (3.47606 * fTemp15);
			var fTemp17 = ((3.47606 * ((fTemp15 * (fTemp16 > 0)) * (fTemp16 <= 1))) + (fTemp16 > 1));
			var fTemp18 = (Math.cos(fTemp14) * fTemp17);
			var fTemp19 = (4 * this.fRec1[0]);
			var fTemp20 = (fTemp8 + -1.38629);
			var fTemp21 = (4.48142 * fTemp20);
			var fTemp22 = ((4.48142 * ((fTemp20 * (fTemp21 > 0)) * (fTemp21 <= 1))) + (fTemp21 > 1));
			var fTemp23 = (0.0141414 * (Math.cos(fTemp19) * fTemp22));
			var fTemp24 = (5 * this.fRec1[0]);
			var fTemp25 = (fTemp8 + -1.60944);
			var fTemp26 = (5.48482 * fTemp25);
			var fTemp27 = ((5.48482 * ((fTemp25 * (fTemp26 > 0)) * (fTemp26 <= 1))) + (fTemp26 > 1));
			var fTemp28 = (Math.cos(fTemp24) * fTemp27);
			var fTemp29 = (6 * this.fRec1[0]);
			var fTemp30 = (fTemp8 + -1.79176);
			var fTemp31 = (6.48716 * fTemp30);
			var fTemp32 = ((6.48716 * ((fTemp30 * (fTemp31 > 0)) * (fTemp31 <= 1))) + (fTemp31 > 1));
			var fTemp33 = (Math.cos(fTemp29) * fTemp32);
			var fTemp34 = (0.00175299 * fTemp33);
			var fTemp35 = (7 * this.fRec1[0]);
			var fTemp36 = (fTemp8 + -1.94591);
			var fTemp37 = (7.48888 * fTemp36);
			var fTemp38 = ((7.48888 * ((fTemp36 * (fTemp37 > 0)) * (fTemp37 <= 1))) + (fTemp37 > 1));
			var fTemp39 = (Math.cos(fTemp35) * fTemp38);
			var fTemp40 = (0.707107 * ((((((((0.116667 * fTemp6) + 0.0666667) + fTemp13) + (0.0388889 * fTemp18)) + fTemp23) + (0.00353535 * fTemp28)) + fTemp34) + (0.00264818 * fTemp39)));
			var fTemp41 = (0.0141414 * (Math.sin(fTemp19) * fTemp22));
			var fTemp42 = (Math.sin(this.fRec1[0]) * fTemp5);
			var fTemp43 = (0.107786 * fTemp6);
			var fTemp44 = (Math.sin(fTemp7) * fTemp11);
			var fTemp45 = (0.0549972 * fTemp44);
			var fTemp46 = (0.0549972 * fTemp12);
			var fTemp47 = (Math.sin(fTemp14) * fTemp17);
			var fTemp48 = (Math.sin(fTemp24) * fTemp27);
			var fTemp49 = (Math.sin(fTemp29) * fTemp32);
			var fTemp50 = (0.00123955 * fTemp49);
			var fTemp51 = (0.00123955 * fTemp33);
			var fTemp52 = (Math.sin(fTemp35) * fTemp38);
			var fTemp53 = (((((((fTemp41 + (((((((0.0446464 * fTemp42) + 0.0666667) + fTemp43) + fTemp45) + fTemp46) + (0.0359286 * fTemp47)) + (0.0148821 * fTemp18))) + (0.00326624 * fTemp48)) - (0.00135292 * fTemp28)) + fTemp50) - fTemp51) + (0.00101342 * fTemp52)) - (0.0024466 * fTemp39));
			var fTemp54 = (0.0824958 * fTemp42);
			var fTemp55 = (0.0777778 * fTemp44);
			var fTemp56 = (0.00175299 * fTemp49);
			var fTemp57 = ((0.107786 * fTemp42) + 0.0666667);
			var fTemp58 = (0.0549972 * fTemp12);
			var fTemp59 = (0.116667 * fTemp42);
			var fTemp60 = (0.0388889 * fTemp47);
			var fTemp61 = (0.00353535 * fTemp48);
			var fTemp62 = (0.00264818 * fTemp52);
			var fTemp63 = (0.0824958 * fTemp6);
			var fTemp64 = (0.0359286 * fTemp47);
			var fTemp65 = (0.00326624 * fTemp48);
			var fTemp66 = (((((((((0.0148821 * fTemp18) + (((((0.0666667 - (0.0446464 * fTemp42)) + (0.107786 * fTemp6)) - (0.0549972 * fTemp44)) + (0.0549972 * fTemp12)) - (0.0359286 * fTemp47))) - fTemp41) - fTemp65) - (0.00135292 * fTemp28)) - (0.00123955 * fTemp49)) - (0.00123955 * fTemp33)) - (0.00101342 * fTemp52)) - (0.0024466 * fTemp39));
			var fTemp67 = (iTemp1 + (mydsp_faustpower2_f(this.fRec0[0]) * iTemp0));
			output0[i] = ((fTemp3 * ((((((((fTemp40 + (0.980785 * fTemp53)) + (0.987688 * ((0.00187255 * fTemp39) + ((((((((((fTemp54 + 0.0666667) + (0.0824958 * fTemp6)) + fTemp55) + (0.0274986 * fTemp47)) - (0.0274986 * fTemp18)) - fTemp23) - (0.00249987 * fTemp48)) - (0.00249987 * fTemp28)) - fTemp56) - (0.00187255 * fTemp52))))) + (0.92388 * (((fTemp51 + (fTemp50 + ((((((((fTemp57 + (0.0446464 * fTemp6)) + (0.0549972 * fTemp44)) - fTemp58) - (0.0148821 * fTemp47)) - (0.0359286 * fTemp18)) - fTemp41) - (0.00135292 * fTemp48)) + (0.00326624 * fTemp28)))) + (0.0024466 * fTemp52)) - (0.00101342 * fTemp39)))) + (0.809017 * ((((fTemp23 + (((fTemp59 + 0.0666667) - fTemp13) - fTemp60)) + fTemp61) - fTemp34) - fTemp62))) + (0.649448 * (((((((fTemp41 + (((((fTemp57 - (0.0446464 * fTemp6)) - fTemp45) - (0.0549972 * fTemp12)) - (0.0148821 * fTemp47)) + (0.0359286 * fTemp18))) - (0.00135292 * fTemp48)) - (0.00326624 * fTemp28)) - (0.00123955 * fTemp49)) + (0.00123955 * fTemp33)) + (0.0024466 * fTemp52)) + (0.00101342 * fTemp39)))) + (0.45399 * (((fTemp56 + ((((((0.0274986 * fTemp47) + ((((0.0824958 * fTemp42) + 0.0666667) - fTemp63) - fTemp55)) + (0.0274986 * fTemp18)) - fTemp23) - (0.00249987 * fTemp48)) + (0.00249987 * fTemp28))) - (0.00187255 * fTemp52)) - (0.00187255 * fTemp39)))) + (0.233445 * ((((((((((fTemp58 + ((((0.0446464 * fTemp42) + 0.0666667) - fTemp43) - (0.0549972 * fTemp44))) + fTemp64) - (0.0148821 * fTemp18)) - fTemp41) + fTemp65) + (0.00135292 * fTemp28)) - (0.00123955 * fTemp49)) - (0.00123955 * fTemp33)) + (0.00101342 * fTemp52)) + (0.0024466 * fTemp39)))) + (0.19509 * fTemp66))) / fTemp67);
			var fTemp68 = (0.00249987 * fTemp48);
			var fTemp69 = (0.00326624 * fTemp28);
			output1[i] = ((fTemp3 * ((((((((fTemp40 + (0.19509 * fTemp53)) + (0.233445 * ((((((0.00135292 * fTemp28) + ((fTemp41 + (((fTemp46 + (fTemp45 + ((0.0666667 - (0.0446464 * fTemp42)) - fTemp43))) - fTemp64) - (0.0148821 * fTemp18))) - (0.00326624 * fTemp48))) + (0.00123955 * fTemp49)) - (0.00123955 * fTemp33)) - (0.00101342 * fTemp52)) + (0.0024466 * fTemp39)))) + (0.45399 * (((((((((fTemp55 + ((0.0666667 - fTemp54) - (0.0824958 * fTemp6))) - (0.0274986 * fTemp47)) + (0.0274986 * fTemp18)) - fTemp23) + fTemp68) + (0.00249987 * fTemp28)) - fTemp56) + (0.00187255 * fTemp52)) - (0.00187255 * fTemp39)))) + (0.649448 * ((((((((((((0.0549972 * fTemp44) + ((0.0666667 - (0.107786 * fTemp42)) - (0.0446464 * fTemp6))) - (0.0549972 * fTemp12)) + (0.0148821 * fTemp47)) + (0.0359286 * fTemp18)) - fTemp41) + (0.00135292 * fTemp48)) - fTemp69) + (0.00123955 * fTemp49)) + (0.00123955 * fTemp33)) - (0.0024466 * fTemp52)) + (0.00101342 * fTemp39)))) + (0.809017 * (fTemp62 + (((fTemp23 + (fTemp60 + ((0.0666667 - fTemp59) - fTemp13))) - fTemp61) - fTemp34)))) + (0.92388 * (((((fTemp69 + ((fTemp41 + ((((((0.0666667 - (0.107786 * fTemp42)) + (0.0446464 * fTemp6)) - (0.0549972 * fTemp44)) - (0.0549972 * fTemp12)) + (0.0148821 * fTemp47)) - (0.0359286 * fTemp18))) + (0.00135292 * fTemp48))) - (0.00123955 * fTemp49)) + (0.00123955 * fTemp33)) - (0.0024466 * fTemp52)) - (0.00101342 * fTemp39)))) + (0.987688 * (((fTemp56 + ((fTemp68 + (((((fTemp63 + (0.0666667 - (0.0824958 * fTemp42))) - fTemp55) - (0.0274986 * fTemp47)) - (0.0274986 * fTemp18)) - fTemp23)) - (0.00249987 * fTemp28))) + (0.00187255 * fTemp52)) + (0.00187255 * fTemp39)))) + (0.980785 * fTemp66))) / fTemp67);
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			
		}
		
	}
	
}

