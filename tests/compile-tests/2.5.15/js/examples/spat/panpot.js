

function mydsp() {
	
	this.fEntry0;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("name", "panpot");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
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
		this.fEntry0 = 0;
		
	}
	
	this.instanceClear = function() {
		
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
		ui_interface.openVerticalBox("panpot");
		ui_interface.declare("fEntry0", "1", "");
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.00555556 * (this.fEntry0 + -90));
		var fSlow1 = Math.sqrt((0 - fSlow0));
		var fSlow2 = Math.sqrt((fSlow0 + 1));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			output0[i] = (fSlow1 * fTemp0);
			output1[i] = (fSlow2 * fTemp0);
			
		}
		
	}
	
}

