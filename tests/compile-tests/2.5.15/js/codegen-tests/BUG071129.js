

function mydsp() {
	
	this.fRec4 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "BUG071129");
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
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec4[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec5[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec0[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec1[l5] = 0;
			
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
		ui_interface.openVerticalBox("BUG071129");
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec4[0] = (Math.sqrt(this.fRec4[1]) + this.fRec0[1]);
			this.fRec2[0] = ((this.fRec4[0] + (0.9 * this.fRec2[1])) + (0.1 * this.fRec3[1]));
			this.fRec5[0] = (Math.sin(this.fRec5[1]) + this.fRec1[1]);
			this.fRec3[0] = ((this.fRec5[0] + (0.2 * this.fRec2[1])) - (0.8 * this.fRec3[1]));
			this.fRec0[0] = (11 * this.fRec2[0]);
			this.fRec1[0] = (13 * this.fRec3[0]);
			output0[i] = this.fRec0[0];
			output1[i] = this.fRec1[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			
		}
		
	}
	
}

