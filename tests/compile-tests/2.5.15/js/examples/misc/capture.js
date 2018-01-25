
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);

function mydsp() {
	
	this.fButton0;
	this.IOTA;
	this.fVec0 = new Float32Array(1048576);
	this.iVec1 = new Int32Array(2);
	this.iRec1 = new Int32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fHslider0;
	this.fRec2 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("name", "capture");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
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
		this.fButton0 = 0;
		this.fHslider0 = 0;
		
	}
	
	this.instanceClear = function() {
		this.IOTA = 0;
		for (var l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.iRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec2[l4] = 0;
			
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
		ui_interface.openVerticalBox("Audio Capture");
		ui_interface.addButton("Capture", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.addHorizontalSlider("level (db)", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, -96, 4, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = this.fButton0;
		var fSlow1 = (1 - fSlow0);
		var iSlow2 = fSlow0;
		var fSlow3 = (0.001 * Math.pow(10, (0.05 * this.fHslider0)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[(this.IOTA & 1048575)] = ((fSlow1 * this.fRec0[1]) + (fSlow0 * input0[i]));
			this.iVec1[0] = iSlow2;
			this.iRec1[0] = ((iSlow2 + this.iRec1[1]) * ((iSlow2 - this.iVec1[1]) <= 0));
			this.fRec0[0] = this.fVec0[((this.IOTA - min_i(524288, max_i(0, (this.iRec1[0] + -1)))) & 1048575)];
			this.fRec2[0] = (fSlow3 + (0.999 * this.fRec2[1]));
			output0[i] = (this.fRec0[0] * this.fRec2[0]);
			this.IOTA = (this.IOTA + 1);
			this.iVec1[1] = this.iVec1[0];
			this.iRec1[1] = this.iRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec2[1] = this.fRec2[0];
			
		}
		
	}
	
}

