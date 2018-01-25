

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
	this.fRec0 = new Float32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fHslider1;
	this.fRec2 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2009");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "osci");
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
		this.fHslider1 = 1000;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
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
		ui_interface.openVerticalBox("Oscillator");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1000, 20, 24000, 1);
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("volume", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0, -96, 0, 0.1);
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var fSlow0 = (0.001 * Math.pow(10, (0.05 * this.fHslider0)));
		var fSlow1 = (this.fConst0 * this.fHslider1);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec0[0] = (fSlow0 + (0.999 * this.fRec0[1]));
			this.fRec2[0] = (fSlow1 + (this.fRec2[1] - Math.floor((fSlow1 + this.fRec2[1]))));
			var fTemp0 = (65536 * this.fRec2[0]);
			var iTemp1 = fTemp0;
			output0[i] = (this.fRec0[0] * (ftbl0mydspSIG0[iTemp1] + ((fTemp0 - Math.floor(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1]))));
			this.fRec0[1] = this.fRec0[0];
			this.fRec2[1] = this.fRec2[0];
			
		}
		
	}
	
}

