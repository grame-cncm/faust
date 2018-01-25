
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider1;
	this.fHslider2;
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
		m.declare("name", "highShelf");
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
		this.fHslider0 = 0;
		this.fHslider1 = 1000;
		this.fHslider2 = 1;
		
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
		ui_interface.openVerticalBox("highShelf");
		ui_interface.addHorizontalSlider("Freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1000, 100, 10000, 1);
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Gain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, -10, 10, 0.1);
		ui_interface.addHorizontalSlider("Q", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0.01, 100, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = Math.pow(10, (0.025 * this.fHslider0));
		var fSlow1 = (this.fConst0 * max_f(0, this.fHslider1));
		var fSlow2 = ((Math.sqrt(fSlow0) * Math.sin(fSlow1)) / max_f(0.001, this.fHslider2));
		var fSlow3 = Math.cos(fSlow1);
		var fSlow4 = ((fSlow0 + -1) * fSlow3);
		var fSlow5 = (1 / ((fSlow0 + fSlow2) + (1 - fSlow4)));
		var fSlow6 = (fSlow0 + fSlow4);
		var fSlow7 = (fSlow0 * ((fSlow2 + fSlow6) + 1));
		var fSlow8 = (fSlow0 + (1 - (fSlow4 + fSlow2)));
		var fSlow9 = ((fSlow0 + 1) * fSlow3);
		var fSlow10 = (2 * (fSlow0 + (-1 - fSlow9)));
		var fSlow11 = ((0 - (2 * fSlow0)) * ((fSlow0 + fSlow9) + -1));
		var fSlow12 = (fSlow0 * (fSlow6 + (1 - fSlow2)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (input0[i] - (fSlow5 * ((fSlow8 * this.fRec0[2]) + (fSlow10 * this.fRec0[1]))));
			output0[i] = (fSlow5 * (((fSlow7 * this.fRec0[0]) + (fSlow11 * this.fRec0[1])) + (fSlow12 * this.fRec0[2])));
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

