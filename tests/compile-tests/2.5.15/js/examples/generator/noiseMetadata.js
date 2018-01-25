

function mydsp() {
	
	this.fVslider0;
	this.iRec0 = new Int32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("contributor", "Yghe");
		m.declare("copyright", "(c)GRAME 2009");
		m.declare("license", "BSD");
		m.declare("name", "noiseMetadata");
		m.declare("version", "1.1");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
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
		this.fVslider0 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec0[l0] = 0;
			
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
		ui_interface.openVerticalBox("noiseMetadata");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.addVerticalSlider("Volume", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = (4.65661e-10 * this.fVslider0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec0[0] = ((1103515245 * this.iRec0[1]) + 12345);
			output0[i] = (fSlow0 * this.iRec0[0]);
			this.iRec0[1] = this.iRec0[0];
			
		}
		
	}
	
}

