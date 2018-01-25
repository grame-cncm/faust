

function mydsp() {
	
	this.IOTA;
	this.fVec0 = new Float32Array(1024);
	this.fHslider0;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "test21");
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
		this.fHslider0 = 0;
		
	}
	
	this.instanceClear = function() {
		this.IOTA = 0;
		for (var l0 = 0; (l0 < 1024); l0 = (l0 + 1)) {
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
		ui_interface.openVerticalBox("test21");
		ui_interface.addHorizontalSlider("delay", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1000, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var iSlow0 = this.fHslider0;
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[(this.IOTA & 1023)] = input0[i];
			output0[i] = this.fVec0[((this.IOTA - iSlow0) & 1023)];
			this.IOTA = (this.IOTA + 1);
			
		}
		
	}
	
}

