
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider0;
	this.fHslider1;
	this.fRec0 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("maxmsp.lib/author", "GRAME");
		m.declare("maxmsp.lib/copyright", "GRAME");
		m.declare("maxmsp.lib/license", "LGPL");
		m.declare("maxmsp.lib/name", "MaxMSP compatibility Library");
		m.declare("maxmsp.lib/version", "1.1");
		m.declare("name", "BPF");
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
		this.fConst0 = (6.28319 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 1000;
		this.fHslider1 = 1;
		
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
		ui_interface.openVerticalBox("BPF");
		ui_interface.addHorizontalSlider("Freq", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 1000, 100, 10000, 1);
		ui_interface.addHorizontalSlider("Q", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0.01, 100, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = (this.fConst0 * max_f(0, this.fHslider0));
		var fSlow1 = (0.5 * (Math.sin(fSlow0) / max_f(0.001, this.fHslider1)));
		var fSlow2 = (1 / (fSlow1 + 1));
		var fSlow3 = (0 - fSlow1);
		var fSlow4 = (0 - (2 * Math.cos(fSlow0)));
		var fSlow5 = (1 - fSlow1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (input0[i] - (fSlow2 * ((fSlow4 * this.fRec0[1]) + (fSlow5 * this.fRec0[2]))));
			output0[i] = (fSlow2 * ((fSlow3 * this.fRec0[2]) + (fSlow1 * this.fRec0[0])));
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

