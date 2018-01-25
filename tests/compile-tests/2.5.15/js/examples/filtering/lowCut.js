
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider0;
	this.fHslider1;
	this.fRec0 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "lowcut");
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
		this.fHslider0 = 100;
		this.fHslider1 = 0;
		
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
		ui_interface.openVerticalBox("low-freq shelving cut");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "unit", "dB");
		ui_interface.addHorizontalSlider("attenuation", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, -96, 10, 0.1);
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 100, 20, 5000, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = Math.tan((this.fConst0 * this.fHslider0));
		var fSlow1 = Math.pow(10, (0 - (0.05 * this.fHslider1)));
		var fSlow2 = Math.sqrt((2 * fSlow1));
		var fSlow3 = (fSlow0 * fSlow1);
		var fSlow4 = (1 / ((fSlow0 * (fSlow2 + fSlow3)) + 1));
		var fSlow5 = mydsp_faustpower2_f(fSlow0);
		var fSlow6 = (2 * (fSlow5 + -1));
		var fSlow7 = (1 - (fSlow0 * (fSlow2 - fSlow3)));
		var fSlow8 = (2 * ((fSlow5 * fSlow1) + -1));
		var fSlow9 = ((fSlow0 * (fSlow0 + 1.41421)) + 1);
		var fSlow10 = ((fSlow0 * (fSlow0 + -1.41421)) + 1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (input0[i] - (fSlow4 * ((fSlow7 * this.fRec0[2]) + (fSlow8 * this.fRec0[1]))));
			output0[i] = (fSlow4 * (((fSlow6 * this.fRec0[1]) + (fSlow9 * this.fRec0[0])) + (fSlow10 * this.fRec0[2])));
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

