
this.max_f = function(dummy0, dummy1);

function mydsp() {
	
	this.iRec0 = new Int32Array(2);
	this.iVec0 = new Int32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("name", "parabolic-env5");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 3;
		
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
			case 2: {
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
			this.iRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec2[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec1[l4] = 0;
			
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
		ui_interface.openVerticalBox("parabolic-env5");
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec0[0] = (this.iRec0[1] + 1);
			output0[i] = this.iRec0[1];
			var iTemp0 = ((this.iRec0[1] % 7) == 0);
			this.iVec0[0] = iTemp0;
			output1[i] = iTemp0;
			var iTemp1 = (((this.fRec1[1] > 0) | iTemp0) | this.iVec0[1]);
			this.fRec3[0] = ((this.fRec3[1] + -0.224) * iTemp1);
			this.fRec2[0] = (iTemp1 * ((this.fRec2[1] + this.fRec3[1]) + 1.008));
			this.fRec1[0] = max_f(0, this.fRec2[1]);
			output2[i] = this.fRec1[0];
			this.iRec0[1] = this.iRec0[0];
			this.iVec0[1] = this.iVec0[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			
		}
		
	}
	
}

