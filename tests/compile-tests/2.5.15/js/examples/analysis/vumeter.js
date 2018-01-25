
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fRec0 = new Float32Array(2);
	this.fHbargraph0;
	this.fRec1 = new Float32Array(2);
	this.fHbargraph1;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "vumeter");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 2;
		
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
		this.fConst0 = (1 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
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
		ui_interface.openVerticalBox("vumeter");
		ui_interface.declare("fHbargraph0", "2", "");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("0x7fe6095ba310", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -70, 5);
		ui_interface.declare("fHbargraph1", "2", "");
		ui_interface.declare("fHbargraph1", "unit", "dB");
		ui_interface.addHorizontalBargraph("0x7fe6095bdaa0", function handler(obj) { function setval(val) { obj.fHbargraph1 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec0[0] = max_f((this.fRec0[1] - this.fConst0), Math.abs(fTemp0));
			this.fHbargraph0 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec0[0])));
			output0[i] = fTemp0;
			var fTemp1 = input1[i];
			this.fRec1[0] = max_f((this.fRec1[1] - this.fConst0), Math.abs(fTemp1));
			this.fHbargraph1 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec1[0])));
			output1[i] = fTemp1;
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			
		}
		
	}
	
}

