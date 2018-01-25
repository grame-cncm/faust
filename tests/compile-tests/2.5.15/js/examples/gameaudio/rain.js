

function mydsp() {
	
	this.fHslider0;
	this.iRec0 = new Int32Array(2);
	this.fVec0 = new Float32Array(2);
	this.fHslider1;
	this.fVec1 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "rain");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 300;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fVec1[l2] = 0;
			
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
		ui_interface.openVerticalBox("rain");
		ui_interface.addHorizontalSlider("density", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 300, 0, 1000, 1);
		ui_interface.addHorizontalSlider("volume", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.001 * this.fHslider1);
		for (var i = 0; (i < count); i = (i + 1)) {
			var iTemp0 = (1103515245 * (this.iRec0[1] + 12345));
			this.iRec0[0] = (1103515245 * (iTemp0 + 12345));
			var iRec1 = iTemp0;
			var fTemp1 = (4.65661e-10 * this.iRec0[0]);
			this.fVec0[0] = fTemp1;
			output0[i] = (fSlow0 * (this.fVec0[1] * (Math.abs(fTemp1) < fSlow1)));
			var fTemp2 = (4.65661e-10 * iRec1);
			this.fVec1[0] = fTemp2;
			output1[i] = (fSlow0 * (this.fVec1[1] * (Math.abs(fTemp2) < fSlow1)));
			this.iRec0[1] = this.iRec0[0];
			this.fVec0[1] = this.fVec0[0];
			this.fVec1[1] = this.fVec1[0];
			
		}
		
	}
	
}

