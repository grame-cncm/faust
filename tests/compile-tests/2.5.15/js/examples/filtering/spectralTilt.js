
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider0;
	this.fHslider1;
	this.fHslider2;
	this.fConst2;
	this.fVec0 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("description", "Demonstrate the Spectral Tilt effect on test signals");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "spectralTilt");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (3.14159 / this.fConst0);
		this.fConst2 = (1 / Math.tan((0.5 / this.fConst0)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 100;
		this.fHslider1 = 5000;
		this.fHslider2 = -0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fVec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec0[l3] = 0;
			
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
		ui_interface.openVerticalBox("spectralTilt");
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.addHorizontalSlider("Slope of Spectral Tilt across Band", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), -0.5, -1, 1, 0.001);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Start Frequency", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 100, 20, 10000, 1);
		ui_interface.declare("fHslider1", "3", "");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Width", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 5000, 100, 10000, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = this.fHslider0;
		var fSlow1 = Math.pow(((fSlow0 + this.fHslider1) / fSlow0), 1);
		var fSlow2 = Math.tan((this.fConst1 * (fSlow0 * fSlow1)));
		var fSlow3 = this.fHslider2;
		var fSlow4 = Math.tan((this.fConst1 * (fSlow0 * Math.pow(fSlow1, (1 - fSlow3)))));
		var fSlow5 = (fSlow2 / fSlow4);
		var fSlow6 = Math.tan((this.fConst1 * fSlow0));
		var fSlow7 = (6.28319 * ((fSlow0 * fSlow2) / fSlow6));
		var fSlow8 = (this.fConst2 + fSlow7);
		var fSlow9 = (0 - ((fSlow7 - this.fConst2) / fSlow8));
		var fSlow10 = (1 / fSlow8);
		var fSlow11 = (6.28319 * ((fSlow0 * fSlow4) / fSlow6));
		var fSlow12 = (fSlow11 - this.fConst2);
		var fSlow13 = Math.tan((this.fConst1 * (fSlow0 * Math.pow(fSlow1, (0 - fSlow3)))));
		var fSlow14 = (fSlow6 / fSlow13);
		var fSlow15 = (6.28319 * fSlow0);
		var fSlow16 = (this.fConst2 + fSlow15);
		var fSlow17 = (0 - ((fSlow15 - this.fConst2) / fSlow16));
		var fSlow18 = (1 / fSlow16);
		var fSlow19 = (6.28319 * ((fSlow0 * fSlow13) / fSlow6));
		var fSlow20 = (this.fConst2 + fSlow19);
		var fSlow21 = (fSlow19 - this.fConst2);
		var fSlow22 = ((fSlow6 * (this.fConst2 + fSlow11)) / fSlow13);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fVec0[0] = fTemp0;
			this.fRec1[0] = ((fSlow17 * this.fRec1[1]) + (fSlow18 * ((fSlow20 * fTemp0) + (fSlow21 * this.fVec0[1]))));
			this.fVec1[0] = (fSlow14 * this.fRec1[0]);
			this.fRec0[0] = ((fSlow9 * this.fRec0[1]) + (fSlow10 * ((fSlow12 * this.fVec1[1]) + (fSlow22 * this.fRec1[0]))));
			output0[i] = (fSlow5 * this.fRec0[0]);
			this.fVec0[1] = this.fVec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

