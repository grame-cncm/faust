
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider0;
	this.fConst2;
	this.fHslider1;
	this.fRec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fRec3 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fHslider2;
	this.IOTA;
	this.fVec0 = new Float32Array(1048576);
	this.fRec0 = new Float32Array(2);
	this.fVec1 = new Float32Array(1048576);
	this.fRec5 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "Yann Orlarey");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "Grame");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "STK-4.3");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "smoothDelay");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (0.001 * this.fConst0);
		this.fConst2 = (1000 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0;
		this.fHslider1 = 10;
		this.fHslider2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec1[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec4[l3] = 0;
			
		}
		this.IOTA = 0;
		for (var l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			this.fVec0[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec0[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			this.fVec1[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec5[l7] = 0;
			
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
		ui_interface.openVerticalBox("smoothDelay");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "unit", "ms");
		ui_interface.addHorizontalSlider("delay", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 5000, 0.1);
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("feedback", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 100, 0.1);
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("interpolation", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 10, 1, 100, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (this.fConst1 * this.fHslider0);
		var fSlow1 = (this.fConst2 / this.fHslider1);
		var fSlow2 = (0 - fSlow1);
		var fSlow3 = (0.01 * this.fHslider2);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = ((this.fRec1[1] != 0)?(((this.fRec2[1] > 0) & (this.fRec2[1] < 1))?this.fRec1[1]:0):(((this.fRec2[1] == 0) & (fSlow0 != this.fRec3[1]))?fSlow1:(((this.fRec2[1] == 1) & (fSlow0 != this.fRec4[1]))?fSlow2:0)));
			this.fRec1[0] = fTemp0;
			this.fRec2[0] = max_f(0, min_f(1, (this.fRec2[1] + fTemp0)));
			this.fRec3[0] = (((this.fRec2[1] >= 1) & (this.fRec4[1] != fSlow0))?fSlow0:this.fRec3[1]);
			this.fRec4[0] = (((this.fRec2[1] <= 0) & (this.fRec3[1] != fSlow0))?fSlow0:this.fRec4[1]);
			var fTemp1 = (1 - this.fRec2[0]);
			var fTemp2 = (input0[i] + (fSlow3 * this.fRec0[1]));
			this.fVec0[(this.IOTA & 1048575)] = fTemp2;
			var iTemp3 = min_f(524288, max_f(0, this.fRec3[0]));
			var iTemp4 = min_f(524288, max_f(0, this.fRec4[0]));
			this.fRec0[0] = ((fTemp1 * this.fVec0[((this.IOTA - iTemp3) & 1048575)]) + (this.fRec2[0] * this.fVec0[((this.IOTA - iTemp4) & 1048575)]));
			output0[i] = this.fRec0[0];
			var fTemp5 = (input1[i] + (fSlow3 * this.fRec5[1]));
			this.fVec1[(this.IOTA & 1048575)] = fTemp5;
			this.fRec5[0] = ((fTemp1 * this.fVec1[((this.IOTA - iTemp3) & 1048575)]) + (this.fRec2[0] * this.fVec1[((this.IOTA - iTemp4) & 1048575)]));
			output1[i] = this.fRec5[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec0[1] = this.fRec0[0];
			this.fRec5[1] = this.fRec5[0];
			
		}
		
	}
	
}

