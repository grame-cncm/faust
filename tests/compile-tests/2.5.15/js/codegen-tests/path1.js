

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fHslider2;
	this.fHslider3;
	this.fHslider4;
	this.fHslider5;
	this.fHslider6;
	this.fHslider7;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "path1");
	}

	this.getNumInputs = function() {
		return 4;
		
	}
	this.getNumOutputs = function() {
		return 4;
		
	}
	this.getInputRate = function(channel) {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
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
		this.fHslider3 = 0;
		this.fHslider4 = 0;
		this.fHslider5 = 0;
		this.fHslider6 = 0;
		this.fHslider7 = 0;
		
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
		ui_interface.openTabBox("toto");
		ui_interface.openVerticalBox("foo 0");
		ui_interface.addHorizontalSlider("slid1", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addHorizontalSlider("slid2", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("foo 1");
		ui_interface.addHorizontalSlider("slid1", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addHorizontalSlider("slid2", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("foo 2");
		ui_interface.addHorizontalSlider("slid1", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addHorizontalSlider("slid2", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("foo 3");
		ui_interface.addHorizontalSlider("slid1", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addHorizontalSlider("slid2", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var fSlow0 = (this.fHslider0 * this.fHslider1);
		var fSlow1 = (this.fHslider2 * this.fHslider3);
		var fSlow2 = (this.fHslider4 * this.fHslider5);
		var fSlow3 = (this.fHslider6 * this.fHslider7);
		for (var i = 0; (i < count); i = (i + 1)) {
			output0[i] = (fSlow0 * input0[i]);
			output1[i] = (fSlow1 * input1[i]);
			output2[i] = (fSlow2 * input2[i]);
			output3[i] = (fSlow3 * input3[i]);
			
		}
		
	}
	
}

