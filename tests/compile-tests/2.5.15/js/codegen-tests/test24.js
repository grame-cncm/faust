

function mydsp() {
	
	this.fHslider0;
	this.fVec0 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "test24");
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
		this.fHslider0 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
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
		ui_interface.openVerticalBox("test24");
		ui_interface.addHorizontalSlider("toto", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 100, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (3 * fSlow0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[0] = fSlow0;
			output0[i] = (fSlow0 - this.fVec0[1]);
			output1[i] = fSlow1;
			this.fVec0[1] = this.fVec0[0];
			
		}
		
	}
	
}

