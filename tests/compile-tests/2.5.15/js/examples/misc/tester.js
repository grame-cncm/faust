

function mydspSIG0() {
	
	this.iRec1 = new Int32Array(2);
	
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
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.iRec1[l1] = 0;
			
		}
		
	}
	
	this.fillmydspSIG0 = function(count, output) {
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec1[0] = (this.iRec1[1] + 1);
			output[i] = Math.sin((9.58738e-05 * (this.iRec1[0] + -1)));
			this.iRec1[1] = this.iRec1[0];
			
		}
		
	}
}

newmydspSIG0 = function() { return new mydspSIG0(); }
deletemydspSIG0= function(dsp) {}

var ftbl0mydspSIG0 = new Float32Array(65537);
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fRec0 = new Float32Array(2);
	this.fCheckbox0;
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider2;
	this.fRec2 = new Float32Array(2);
	this.fCheckbox1;
	this.iRec3 = new Int32Array(3);
	this.fCheckbox2;
	this.fRec4 = new Float32Array(3);
	
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
		m.declare("name", "tester");
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
		return 8;
		
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
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		this.fHslider0 = 0;
		this.fHslider1 = -96;
		this.fCheckbox0 = 0;
		this.fHslider2 = 1000;
		this.fCheckbox1 = 0;
		this.fCheckbox2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			this.iRec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
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
		ui_interface.openVerticalBox("Audio Tester");
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1000, 10, 20000, 1);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "unit", "dB");
		ui_interface.addHorizontalSlider("volume", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), -96, -96, 0, 1);
		ui_interface.declare("fHslider0", "3", "");
		ui_interface.addHorizontalSlider("destination", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, 0, 8, 1);
		ui_interface.addCheckButton("pink noise", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.addCheckButton("sine wave", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.addCheckButton("white noise", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		var fSlow0 = this.fHslider0;
		var iSlow1 = (fSlow0 == 0);
		var fSlow2 = (0.001 * Math.pow(10, (0.05 * this.fHslider1)));
		var fSlow3 = this.fCheckbox0;
		var fSlow4 = (this.fConst0 * this.fHslider2);
		var fSlow5 = (4.65661e-10 * this.fCheckbox1);
		var fSlow6 = (10 * this.fCheckbox2);
		var iSlow7 = (fSlow0 == 1);
		var iSlow8 = (fSlow0 == 2);
		var iSlow9 = (fSlow0 == 3);
		var iSlow10 = (fSlow0 == 4);
		var iSlow11 = (fSlow0 == 5);
		var iSlow12 = (fSlow0 == 6);
		var iSlow13 = (fSlow0 == 7);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow2 + (0.999 * this.fRec0[1]));
			this.fRec2[0] = (fSlow4 + (this.fRec2[1] - Math.floor((fSlow4 + this.fRec2[1]))));
			var fTemp0 = (65536 * this.fRec2[0]);
			var iTemp1 = fTemp0;
			this.iRec3[0] = ((1103515245 * this.iRec3[1]) + 12345);
			this.fRec4[0] = (((6.90678e-12 * this.iRec3[2]) + ((1.80116 * this.fRec4[1]) + (2.30853e-11 * this.iRec3[0]))) - ((0.802577 * this.fRec4[2]) + (2.93627e-11 * this.iRec3[1])));
			var fTemp2 = (this.fRec0[0] * (((fSlow3 * (ftbl0mydspSIG0[iTemp1] + ((fTemp0 - Math.floor(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1])))) + (fSlow5 * this.iRec3[0])) + (fSlow6 * this.fRec4[0])));
			output0[i] = (iSlow1 * fTemp2);
			output1[i] = (iSlow7 * fTemp2);
			output2[i] = (iSlow8 * fTemp2);
			output3[i] = (iSlow9 * fTemp2);
			output4[i] = (iSlow10 * fTemp2);
			output5[i] = (iSlow11 * fTemp2);
			output6[i] = (iSlow12 * fTemp2);
			output7[i] = (iSlow13 * fTemp2);
			this.fRec0[1] = this.fRec0[0];
			this.fRec2[1] = this.fRec2[0];
			this.iRec3[2] = this.iRec3[1];
			this.iRec3[1] = this.iRec3[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			
		}
		
	}
	
}

