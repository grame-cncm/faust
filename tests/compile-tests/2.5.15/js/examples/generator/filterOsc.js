
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.iVec0 = new Int32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.fConst2;
	this.fHslider2;
	this.fRec3 = new Float32Array(2);
	this.fRec1 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Simple application demoing filter based oscillators.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "filterOSC");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
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
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (6.28319 / this.fConst0);
		this.fConst2 = (1 / this.fConst0);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = -20;
		this.fHslider1 = 49;
		this.fHslider2 = 0.1;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec3[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec1[l3] = 0;
			
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
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "Sine oscillator based   on 2D vector rotation");
		ui_interface.openVerticalBox("SINE WAVE OSCILLATOR oscrs");
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "tooltip", "Sawtooth waveform   amplitude");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Amplitude", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), -20, -120, 10, 0.1);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)");
		ui_interface.declare("fHslider1", "unit", "PK");
		ui_interface.addHorizontalSlider("Frequency", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 49, 1, 88, 0.01);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "scale", "log");
		ui_interface.declare("fHslider2", "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface.declare("fHslider2", "unit", "sec");
		ui_interface.addHorizontalSlider("Portamento", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.1, 0.001, 10, 0.001);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = (0.001 * Math.pow(10, (0.05 * this.fHslider0)));
		var fSlow1 = Math.exp((0 - (this.fConst2 / this.fHslider2)));
		var fSlow2 = (440 * (Math.pow(2, (0.0833333 * (this.fHslider1 + -49))) * (1 - fSlow1)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec0[0] = (fSlow0 + (0.999 * this.fRec0[1]));
			this.fRec3[0] = (fSlow2 + (fSlow1 * this.fRec3[1]));
			var fTemp0 = (this.fConst1 * this.fRec3[0]);
			var fTemp1 = Math.sin(fTemp0);
			var fTemp2 = Math.cos(fTemp0);
			this.fRec1[0] = ((this.fRec2[1] * fTemp1) + (this.fRec1[1] * fTemp2));
			this.fRec2[0] = (((this.fRec2[1] * fTemp2) + (this.fRec1[1] * (0 - fTemp1))) + (1 - this.iVec0[1]));
			output0[i] = (this.fRec0[0] * this.fRec1[0]);
			this.iVec0[1] = this.iVec0[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			
		}
		
	}
	
}

