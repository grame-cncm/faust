
this.max_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fRec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("name", "spat");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("spats.lib/name", "Faust Spatialization Library");
		m.declare("spats.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 1;
		
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 0;
		
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
		ui_interface.openVerticalBox("Spatializer 1x8");
		ui_interface.addHorizontalSlider("angle", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.addHorizontalSlider("distance", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (fSlow0 + 1);
		var fSlow2 = this.fHslider1;
		var fSlow3 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 1.5), 1) + -0.5)))))))));
		var fSlow4 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 1.375), 1) + -0.5)))))))));
		var fSlow5 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 1.25), 1) + -0.5)))))))));
		var fSlow6 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 1.125), 1) + -0.5)))))))));
		var fSlow7 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 1), 1) + -0.5)))))))));
		var fSlow8 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 0.875), 1) + -0.5)))))))));
		var fSlow9 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 0.75), 1) + -0.5)))))))));
		var fSlow10 = (5e-05 * (fSlow1 * Math.sqrt(max_f(0, (1 - (8 * (fSlow0 * Math.abs((function fmod(a, b) { return a % b; }((fSlow2 + 0.625), 1) + -0.5)))))))));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec0[0] = (fSlow3 + (0.9999 * this.fRec0[1]));
			output0[i] = (fTemp0 * this.fRec0[0]);
			this.fRec1[0] = (fSlow4 + (0.9999 * this.fRec1[1]));
			output1[i] = (fTemp0 * this.fRec1[0]);
			this.fRec2[0] = (fSlow5 + (0.9999 * this.fRec2[1]));
			output2[i] = (fTemp0 * this.fRec2[0]);
			this.fRec3[0] = (fSlow6 + (0.9999 * this.fRec3[1]));
			output3[i] = (fTemp0 * this.fRec3[0]);
			this.fRec4[0] = (fSlow7 + (0.9999 * this.fRec4[1]));
			output4[i] = (fTemp0 * this.fRec4[0]);
			this.fRec5[0] = (fSlow8 + (0.9999 * this.fRec5[1]));
			output5[i] = (fTemp0 * this.fRec5[0]);
			this.fRec6[0] = (fSlow9 + (0.9999 * this.fRec6[1]));
			output6[i] = (fTemp0 * this.fRec6[0]);
			this.fRec7[0] = (fSlow10 + (0.9999 * this.fRec7[1]));
			output7[i] = (fTemp0 * this.fRec7[0]);
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

