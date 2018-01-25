
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider1;
	this.IOTA;
	this.fRec0 = new Float32Array(131072);
	this.fRec1 = new Float32Array(131072);
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2007");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "stereoEcho");
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
		this.fConst0 = (0.001 * min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0;
		this.fHslider1 = 0;
		
	}
	
	this.instanceClear = function() {
		this.IOTA = 0;
		for (var l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 131072); l1 = (l1 + 1)) {
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
		ui_interface.openVerticalBox("stereo echo");
		ui_interface.openVerticalBox("echo  1000");
		ui_interface.addHorizontalSlider("feedback", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 100, 0.1);
		ui_interface.addHorizontalSlider("millisecond", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 1000, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.01 * this.fHslider0);
		var iSlow1 = (min_i(65536, max_i(0, ((this.fConst0 * this.fHslider1) + -1))) + 1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[(this.IOTA & 131071)] = (input0[i] + (fSlow0 * this.fRec0[((this.IOTA - iSlow1) & 131071)]));
			output0[i] = this.fRec0[((this.IOTA - 0) & 131071)];
			this.fRec1[(this.IOTA & 131071)] = (input1[i] + (fSlow0 * this.fRec1[((this.IOTA - iSlow1) & 131071)]));
			output1[i] = this.fRec1[((this.IOTA - 0) & 131071)];
			this.IOTA = (this.IOTA + 1);
			
		}
		
	}
	
}

