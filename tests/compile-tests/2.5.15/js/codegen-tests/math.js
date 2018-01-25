
this.rintf = function(dummy0);
this.remainderf = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_f = function(dummy0, dummy1);

function mydsp() {
	
	this.iRec0 = new Int32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("math.lib/author", "GRAME");
		m.declare("math.lib/copyright", "GRAME");
		m.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("math.lib/license", "LGPL with exception");
		m.declare("math.lib/name", "Math Library");
		m.declare("math.lib/version", "1.0");
		m.declare("music.lib/author", "GRAME");
		m.declare("music.lib/copyright", "GRAME");
		m.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("music.lib/license", "LGPL with exception");
		m.declare("music.lib/name", "Music Library");
		m.declare("music.lib/version", "1.0");
		m.declare("name", "math");
	}

	this.getNumInputs = function() {
		return 6;
		
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
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
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
		ui_interface.openVerticalBox("math");
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var input4 = inputs[4];
		var input5 = inputs[5];
		var output0 = outputs[0];
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec0[0] = (this.iRec0[1] + 1);
			var iTemp0 = (this.iRec0[0] + -1);
			output0[i] = (Math.sqrt(iTemp0) + (Math.tan(iTemp0) + (rintf(iTemp0) + (Math.sin(iTemp0) + (remainderf(iTemp0, input5[i]) + (Math.pow(input4[i], iTemp0) + (min_f(iTemp0, input3[i]) + (Math.log(iTemp0) + (function log10(a) { return Math.log(a)/Math.log(10); }(iTemp0) + (((((((((Math.abs(iTemp0) + Math.asin(iTemp0)) + Math.atan2(iTemp0, input0[i])) + Math.atan(iTemp0)) + Math.ceil(iTemp0)) + Math.cos(iTemp0)) + Math.exp(iTemp0)) + Math.floor(iTemp0)) + function fmod(a, b) { return a % b; }(iTemp0, input1[i])) + max_f(iTemp0, input2[i])))))))))));
			this.iRec0[1] = this.iRec0[0];
			
		}
		
	}
	
}

