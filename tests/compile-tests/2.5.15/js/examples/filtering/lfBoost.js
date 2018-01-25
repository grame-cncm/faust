
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fEntry0;
	this.fVslider0;
	this.fRec0 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "lfboost");
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
		this.fConst0 = (3.14159 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fEntry0 = 100;
		this.fVslider0 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
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
		ui_interface.openVerticalBox("lowboost");
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.declare("fEntry0", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 100, 20, 150, 1);
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, -20, 20, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = Math.tan((this.fConst0 * this.fEntry0));
		var fSlow1 = (1 / ((fSlow0 * (fSlow0 + 1.41421)) + 1));
		var fSlow2 = Math.pow(10, (0.05 * this.fVslider0));
		var fSlow3 = mydsp_faustpower2_f(fSlow0);
		var fSlow4 = (2 * ((fSlow2 * fSlow3) + -1));
		var fSlow5 = ((fSlow0 * (fSlow0 + -1.41421)) + 1);
		var fSlow6 = (2 * (fSlow3 + -1));
		var fSlow7 = Math.sqrt((2 * fSlow2));
		var fSlow8 = (fSlow2 * fSlow0);
		var fSlow9 = ((fSlow0 * (fSlow7 + fSlow8)) + 1);
		var fSlow10 = (1 - (fSlow0 * (fSlow7 - fSlow8)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (input0[i] - (fSlow1 * ((fSlow5 * this.fRec0[2]) + (fSlow6 * this.fRec0[1]))));
			output0[i] = (fSlow1 * (((fSlow4 * this.fRec0[1]) + (fSlow9 * this.fRec0[0])) + (fSlow10 * this.fRec0[2])));
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

