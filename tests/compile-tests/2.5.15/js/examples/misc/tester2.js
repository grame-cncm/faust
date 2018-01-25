

function mydspSIG0() {
	
	this.iRec2 = new Int32Array(2);
	
	this.getNumInputsmydspSIG0 = function() {
		return 0;
		
	}
	this.getNumOutputsmydspSIG0 = function() {
		return 1;
		
	}
	this.getInputRatemydspSIG0 = function(channel) {
		var rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	this.getOutputRatemydspSIG0 = function(channel) {
		var rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	this.instanceInitmydspSIG0 = function(samplingFreq) {
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.iRec2[l2] = 0;
			
		}
		
	}
	
	this.fillmydspSIG0 = function(count, output) {
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec2[0] = (this.iRec2[1] + 1);
			output[i] = Math.sin((9.58738e-05 * (this.iRec2[0] + -1)));
			this.iRec2[1] = this.iRec2[0];
			
		}
		
	}
}

newmydspSIG0 = function() { return new mydspSIG0(); }
deletemydspSIG0= function(dsp) {}

this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
var ftbl0mydspSIG0 = new Float32Array(65537);

function mydsp() {
	
	this.fHslider0;
	this.fRec0 = new Float32Array(2);
	this.fHslider1;
	this.fRec1 = new Float32Array(2);
	this.fHslider2;
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider3;
	this.fRec3 = new Float32Array(2);
	this.iRec5 = new Int32Array(3);
	this.fRec4 = new Float32Array(3);
	this.fRec6 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2014");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "tester2");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
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
		var sig0 = newmydspSIG0();
		sig0.instanceInitmydspSIG0(samplingFreq);
		sig0.fillmydspSIG0(65537, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = (1 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = -96;
		this.fHslider1 = 0;
		this.fHslider2 = 0;
		this.fHslider3 = 440;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.iRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			this.fRec4[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec6[l6] = 0;
			
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
		ui_interface.openVerticalBox("Stereo Audio Tester");
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 440, 40, 20000, 1);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("volume", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), -96, -96, 0, 1);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "style", "menu{'white noise':0;'pink noise':1;'sine':2}");
		ui_interface.addHorizontalSlider("signal", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, 0, 2, 1);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.declare("fHslider1", "style", "radio{'none':0;'left':1;'right':2;'both':3}");
		ui_interface.addHorizontalSlider("channel", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 0, 0, 3, 1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * Math.pow(10, (0.05 * this.fHslider0)));
		var iSlow1 = this.fHslider1;
		var iSlow2 = ((iSlow1 & 1) != 0);
		var iSlow3 = this.fHslider2;
		var iSlow4 = (iSlow3 == 0);
		var iSlow5 = (iSlow3 == 1);
		var fSlow6 = (this.fConst0 * this.fHslider3);
		var iSlow7 = ((iSlow1 & 2) != 0);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow0 + (0.999 * this.fRec0[1]));
			this.fRec1[0] = ((this.fRec1[1] < iSlow2)?min_f((this.fRec1[1] + 0.000226757), iSlow2):max_f((this.fRec1[1] + -0.000226757), iSlow2));
			this.fRec3[0] = (fSlow6 + (this.fRec3[1] - Math.floor((fSlow6 + this.fRec3[1]))));
			var fTemp0 = (65536 * this.fRec3[0]);
			var iTemp1 = fTemp0;
			this.iRec5[0] = ((1103515245 * this.iRec5[1]) + 12345);
			this.fRec4[0] = (((6.90678e-12 * this.iRec5[2]) + ((1.80116 * this.fRec4[1]) + (2.30853e-11 * this.iRec5[0]))) - ((0.802577 * this.fRec4[2]) + (2.93627e-11 * this.iRec5[1])));
			var fTemp2 = (iSlow4?(4.65661e-10 * this.iRec5[0]):(iSlow5?this.fRec4[0]:(ftbl0mydspSIG0[iTemp1] + ((fTemp0 - Math.floor(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))));
			output0[i] = ((this.fRec0[0] * this.fRec1[0]) * fTemp2);
			this.fRec6[0] = ((this.fRec6[1] < iSlow7)?min_f((this.fRec6[1] + 0.000226757), iSlow7):max_f((this.fRec6[1] + -0.000226757), iSlow7));
			output1[i] = ((this.fRec0[0] * this.fRec6[0]) * fTemp2);
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec3[1] = this.fRec3[0];
			this.iRec5[2] = this.iRec5[1];
			this.iRec5[1] = this.iRec5[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			this.fRec6[1] = this.fRec6[0];
			
		}
		
	}
	
}

