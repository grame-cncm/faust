

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fHslider2;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "path4");
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
		this.fHslider0 = 0;
		this.fHslider1 = 0;
		this.fHslider2 = 0;
		
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
		ui_interface.openVerticalBox("foo");
		ui_interface.openHorizontalBox("faa");
		ui_interface.addHorizontalSlider("slid2", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addHorizontalSlider("slid3", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.addHorizontalSlider("slid1", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = ((this.fHslider0 + this.fHslider1) + this.fHslider2);
		for (var i = 0; (i < count); i = (i + 1)) {
			output0[i] = fSlow0;
			
		}
		
	}
	
}

