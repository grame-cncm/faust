
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.IOTA;
	this.fVec0 = new Float32Array(131072);
	this.fHslider0;
	this.fHslider1;
	this.fRec0 = new Float32Array(2);
	this.fHslider2;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "pitchShifter");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
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
		this.fHslider0 = 1000;
		this.fHslider1 = 0;
		this.fHslider2 = 10;
		
	}
	
	this.instanceClear = function() {
		this.IOTA = 0;
		for (var l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec0[l1] = 0;
			
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
		ui_interface.openVerticalBox("Pitch Shifter");
		ui_interface.addHorizontalSlider("shift (semitones)", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, -12, 12, 0.1);
		ui_interface.addHorizontalSlider("window (samples)", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 1000, 50, 10000, 1);
		ui_interface.addHorizontalSlider("xfade (samples)", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 10, 1, 10000, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = this.fHslider0;
		var fSlow1 = Math.pow(2, (0.0833333 * this.fHslider1));
		var fSlow2 = (1 / this.fHslider2);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fVec0[(this.IOTA & 131071)] = fTemp0;
			this.fRec0[0] = function fmod(a, b) { return a % b; }((fSlow0 + ((this.fRec0[1] + 1) - fSlow1)), fSlow0);
			var iTemp1 = this.fRec0[0];
			var fTemp2 = Math.floor(this.fRec0[0]);
			var fTemp3 = (1 - this.fRec0[0]);
			var fTemp4 = min_f((fSlow2 * this.fRec0[0]), 1);
			var fTemp5 = (fSlow0 + this.fRec0[0]);
			var iTemp6 = fTemp5;
			var fTemp7 = Math.floor(fTemp5);
			output0[i] = ((((this.fVec0[((this.IOTA - min_i(65537, max_i(0, iTemp1))) & 131071)] * (fTemp2 + fTemp3)) + ((this.fRec0[0] - fTemp2) * this.fVec0[((this.IOTA - min_i(65537, max_i(0, (iTemp1 + 1)))) & 131071)])) * fTemp4) + (((this.fVec0[((this.IOTA - min_i(65537, max_i(0, iTemp6))) & 131071)] * ((fTemp7 + fTemp3) - fSlow0)) + ((fSlow0 + (this.fRec0[0] - fTemp7)) * this.fVec0[((this.IOTA - min_i(65537, max_i(0, (iTemp6 + 1)))) & 131071)])) * (1 - fTemp4)));
			this.IOTA = (this.IOTA + 1);
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

