
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fEntry0;
	this.fVslider0;
	this.fEntry1;
	this.fEntry2;
	this.fVslider1;
	this.fEntry3;
	this.fEntry4;
	this.fVslider2;
	this.fEntry5;
	this.fEntry6;
	this.fVslider3;
	this.fEntry7;
	this.fEntry8;
	this.fVslider4;
	this.fEntry9;
	this.fEntry10;
	this.fVslider5;
	this.fEntry11;
	this.fEntry12;
	this.fVslider6;
	this.fEntry13;
	this.fEntry14;
	this.fVslider7;
	this.fEntry15;
	this.fEntry16;
	this.fVslider8;
	this.fEntry17;
	this.fEntry18;
	this.fVslider9;
	this.fEntry19;
	this.fRec9 = new Float32Array(3);
	this.fRec8 = new Float32Array(3);
	this.fRec7 = new Float32Array(3);
	this.fRec6 = new Float32Array(3);
	this.fRec5 = new Float32Array(3);
	this.fRec4 = new Float32Array(3);
	this.fRec3 = new Float32Array(3);
	this.fRec2 = new Float32Array(3);
	this.fRec1 = new Float32Array(3);
	this.fRec0 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("bandfilter.dsp/author", "Grame");
		m.declare("bandfilter.dsp/copyright", "(c)GRAME 2006");
		m.declare("bandfilter.dsp/license", "BSD");
		m.declare("bandfilter.dsp/name", "bandFilter");
		m.declare("bandfilter.dsp/version", "1.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "multibandFilter");
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
		this.fConst0 = (3.14159 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fEntry0 = 10000;
		this.fVslider0 = 0;
		this.fEntry1 = 50;
		this.fEntry2 = 9000;
		this.fVslider1 = 0;
		this.fEntry3 = 50;
		this.fEntry4 = 8000;
		this.fVslider2 = 0;
		this.fEntry5 = 50;
		this.fEntry6 = 7000;
		this.fVslider3 = 0;
		this.fEntry7 = 50;
		this.fEntry8 = 6000;
		this.fVslider4 = 0;
		this.fEntry9 = 50;
		this.fEntry10 = 5000;
		this.fVslider5 = 0;
		this.fEntry11 = 50;
		this.fEntry12 = 4000;
		this.fVslider6 = 0;
		this.fEntry13 = 50;
		this.fEntry14 = 3000;
		this.fVslider7 = 0;
		this.fEntry15 = 50;
		this.fEntry16 = 2000;
		this.fVslider8 = 0;
		this.fEntry17 = 50;
		this.fEntry18 = 1000;
		this.fVslider9 = 0;
		this.fEntry19 = 50;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			this.fRec9[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			this.fRec8[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			this.fRec7[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			this.fRec6[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.fRec5[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			this.fRec4[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec3[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec2[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec1[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec0[l9] = 0;
			
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
		ui_interface.openHorizontalBox("Multi Band Filter");
		ui_interface.openVerticalBox("peak 0");
		ui_interface.declare("fEntry19", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry19 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry18", "style", "knob");
		ui_interface.declare("fEntry18", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry18 = val; } return setval; }(this), 1000, 20, 20000, 1);
		ui_interface.declare("fVslider9", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 1");
		ui_interface.declare("fEntry17", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry17 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry16", "style", "knob");
		ui_interface.declare("fEntry16", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry16 = val; } return setval; }(this), 2000, 20, 20000, 1);
		ui_interface.declare("fVslider8", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 2");
		ui_interface.declare("fEntry15", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry15 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry14", "style", "knob");
		ui_interface.declare("fEntry14", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry14 = val; } return setval; }(this), 3000, 20, 20000, 1);
		ui_interface.declare("fVslider7", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 3");
		ui_interface.declare("fEntry13", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry13 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry12", "style", "knob");
		ui_interface.declare("fEntry12", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry12 = val; } return setval; }(this), 4000, 20, 20000, 1);
		ui_interface.declare("fVslider6", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 4");
		ui_interface.declare("fEntry11", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry11 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry10", "style", "knob");
		ui_interface.declare("fEntry10", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry10 = val; } return setval; }(this), 5000, 20, 20000, 1);
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 5");
		ui_interface.declare("fEntry9", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry9 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry8", "style", "knob");
		ui_interface.declare("fEntry8", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry8 = val; } return setval; }(this), 6000, 20, 20000, 1);
		ui_interface.declare("fVslider4", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 6");
		ui_interface.declare("fEntry7", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry7 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry6", "style", "knob");
		ui_interface.declare("fEntry6", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry6 = val; } return setval; }(this), 7000, 20, 20000, 1);
		ui_interface.declare("fVslider3", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 7");
		ui_interface.declare("fEntry5", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry5 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry4", "style", "knob");
		ui_interface.declare("fEntry4", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry4 = val; } return setval; }(this), 8000, 20, 20000, 1);
		ui_interface.declare("fVslider2", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 8");
		ui_interface.declare("fEntry3", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry3 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry2", "style", "knob");
		ui_interface.declare("fEntry2", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry2 = val; } return setval; }(this), 9000, 20, 20000, 1);
		ui_interface.declare("fVslider1", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 9");
		ui_interface.declare("fEntry1", "style", "knob");
		ui_interface.addNumEntry("Q factor", function handler(obj) { function setval(val) { obj.fEntry1 = val; } return setval; }(this), 50, 0.1, 100, 0.1);
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.declare("fEntry0", "unit", "Hz");
		ui_interface.addNumEntry("freq", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 10000, 20, 20000, 1);
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, -50, 50, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = Math.tan((this.fConst0 * this.fEntry0));
		var fSlow1 = this.fEntry1;
		var fSlow2 = (Math.pow(10, (0.05 * (0 - this.fVslider0))) / fSlow1);
		var fSlow3 = (1 / ((fSlow0 * (fSlow0 + fSlow2)) + 1));
		var fSlow4 = (2 * (mydsp_faustpower2_f(fSlow0) + -1));
		var fSlow5 = Math.tan((this.fConst0 * this.fEntry2));
		var fSlow6 = this.fEntry3;
		var fSlow7 = (Math.pow(10, (0.05 * (0 - this.fVslider1))) / fSlow6);
		var fSlow8 = (1 / ((fSlow5 * (fSlow5 + fSlow7)) + 1));
		var fSlow9 = (2 * (mydsp_faustpower2_f(fSlow5) + -1));
		var fSlow10 = Math.tan((this.fConst0 * this.fEntry4));
		var fSlow11 = this.fEntry5;
		var fSlow12 = (Math.pow(10, (0.05 * (0 - this.fVslider2))) / fSlow11);
		var fSlow13 = (1 / ((fSlow10 * (fSlow10 + fSlow12)) + 1));
		var fSlow14 = (2 * (mydsp_faustpower2_f(fSlow10) + -1));
		var fSlow15 = Math.tan((this.fConst0 * this.fEntry6));
		var fSlow16 = this.fEntry7;
		var fSlow17 = (Math.pow(10, (0.05 * (0 - this.fVslider3))) / fSlow16);
		var fSlow18 = (1 / ((fSlow15 * (fSlow15 + fSlow17)) + 1));
		var fSlow19 = (2 * (mydsp_faustpower2_f(fSlow15) + -1));
		var fSlow20 = Math.tan((this.fConst0 * this.fEntry8));
		var fSlow21 = this.fEntry9;
		var fSlow22 = (Math.pow(10, (0.05 * (0 - this.fVslider4))) / fSlow21);
		var fSlow23 = (1 / ((fSlow20 * (fSlow20 + fSlow22)) + 1));
		var fSlow24 = (2 * (mydsp_faustpower2_f(fSlow20) + -1));
		var fSlow25 = Math.tan((this.fConst0 * this.fEntry10));
		var fSlow26 = this.fEntry11;
		var fSlow27 = (Math.pow(10, (0.05 * (0 - this.fVslider5))) / fSlow26);
		var fSlow28 = (1 / ((fSlow25 * (fSlow25 + fSlow27)) + 1));
		var fSlow29 = (2 * (mydsp_faustpower2_f(fSlow25) + -1));
		var fSlow30 = Math.tan((this.fConst0 * this.fEntry12));
		var fSlow31 = this.fEntry13;
		var fSlow32 = (Math.pow(10, (0.05 * (0 - this.fVslider6))) / fSlow31);
		var fSlow33 = (1 / ((fSlow30 * (fSlow30 + fSlow32)) + 1));
		var fSlow34 = (2 * (mydsp_faustpower2_f(fSlow30) + -1));
		var fSlow35 = Math.tan((this.fConst0 * this.fEntry14));
		var fSlow36 = this.fEntry15;
		var fSlow37 = (Math.pow(10, (0.05 * (0 - this.fVslider7))) / fSlow36);
		var fSlow38 = (1 / ((fSlow35 * (fSlow35 + fSlow37)) + 1));
		var fSlow39 = (2 * (mydsp_faustpower2_f(fSlow35) + -1));
		var fSlow40 = Math.tan((this.fConst0 * this.fEntry16));
		var fSlow41 = this.fEntry17;
		var fSlow42 = (Math.pow(10, (0.05 * (0 - this.fVslider8))) / fSlow41);
		var fSlow43 = (1 / ((fSlow40 * (fSlow40 + fSlow42)) + 1));
		var fSlow44 = (2 * (mydsp_faustpower2_f(fSlow40) + -1));
		var fSlow45 = Math.tan((this.fConst0 * this.fEntry18));
		var fSlow46 = this.fEntry19;
		var fSlow47 = (Math.pow(10, (0.05 * (0 - this.fVslider9))) / fSlow46);
		var fSlow48 = (1 / ((fSlow45 * (fSlow45 + fSlow47)) + 1));
		var fSlow49 = (2 * (mydsp_faustpower2_f(fSlow45) + -1));
		var fSlow50 = ((fSlow45 * (fSlow45 - fSlow47)) + 1);
		var fSlow51 = (1 / fSlow46);
		var fSlow52 = ((fSlow45 * (fSlow45 + fSlow51)) + 1);
		var fSlow53 = (1 - (fSlow45 * (fSlow51 - fSlow45)));
		var fSlow54 = ((fSlow40 * (fSlow40 - fSlow42)) + 1);
		var fSlow55 = (1 / fSlow41);
		var fSlow56 = ((fSlow40 * (fSlow40 + fSlow55)) + 1);
		var fSlow57 = (1 - (fSlow40 * (fSlow55 - fSlow40)));
		var fSlow58 = ((fSlow35 * (fSlow35 - fSlow37)) + 1);
		var fSlow59 = (1 / fSlow36);
		var fSlow60 = ((fSlow35 * (fSlow35 + fSlow59)) + 1);
		var fSlow61 = (1 - (fSlow35 * (fSlow59 - fSlow35)));
		var fSlow62 = ((fSlow30 * (fSlow30 - fSlow32)) + 1);
		var fSlow63 = (1 / fSlow31);
		var fSlow64 = ((fSlow30 * (fSlow30 + fSlow63)) + 1);
		var fSlow65 = (1 - (fSlow30 * (fSlow63 - fSlow30)));
		var fSlow66 = ((fSlow25 * (fSlow25 - fSlow27)) + 1);
		var fSlow67 = (1 / fSlow26);
		var fSlow68 = ((fSlow25 * (fSlow25 + fSlow67)) + 1);
		var fSlow69 = (1 - (fSlow25 * (fSlow67 - fSlow25)));
		var fSlow70 = ((fSlow20 * (fSlow20 - fSlow22)) + 1);
		var fSlow71 = (1 / fSlow21);
		var fSlow72 = ((fSlow20 * (fSlow20 + fSlow71)) + 1);
		var fSlow73 = (1 - (fSlow20 * (fSlow71 - fSlow20)));
		var fSlow74 = ((fSlow15 * (fSlow15 - fSlow17)) + 1);
		var fSlow75 = (1 / fSlow16);
		var fSlow76 = ((fSlow15 * (fSlow15 + fSlow75)) + 1);
		var fSlow77 = (1 - (fSlow15 * (fSlow75 - fSlow15)));
		var fSlow78 = ((fSlow10 * (fSlow10 - fSlow12)) + 1);
		var fSlow79 = (1 / fSlow11);
		var fSlow80 = ((fSlow10 * (fSlow10 + fSlow79)) + 1);
		var fSlow81 = (1 - (fSlow10 * (fSlow79 - fSlow10)));
		var fSlow82 = ((fSlow5 * (fSlow5 - fSlow7)) + 1);
		var fSlow83 = (1 / fSlow6);
		var fSlow84 = ((fSlow5 * (fSlow5 + fSlow83)) + 1);
		var fSlow85 = (1 - (fSlow5 * (fSlow83 - fSlow5)));
		var fSlow86 = ((fSlow0 * (fSlow0 - fSlow2)) + 1);
		var fSlow87 = (1 / fSlow1);
		var fSlow88 = ((fSlow0 * (fSlow0 + fSlow87)) + 1);
		var fSlow89 = (1 - (fSlow0 * (fSlow87 - fSlow0)));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = (fSlow49 * this.fRec9[1]);
			this.fRec9[0] = (input0[i] - (fSlow48 * ((fSlow50 * this.fRec9[2]) + fTemp0)));
			var fTemp1 = (fSlow44 * this.fRec8[1]);
			this.fRec8[0] = ((fSlow48 * ((fTemp0 + (fSlow52 * this.fRec9[0])) + (fSlow53 * this.fRec9[2]))) - (fSlow43 * ((fSlow54 * this.fRec8[2]) + fTemp1)));
			var fTemp2 = (fSlow39 * this.fRec7[1]);
			this.fRec7[0] = ((fSlow43 * ((fTemp1 + (fSlow56 * this.fRec8[0])) + (fSlow57 * this.fRec8[2]))) - (fSlow38 * ((fSlow58 * this.fRec7[2]) + fTemp2)));
			var fTemp3 = (fSlow34 * this.fRec6[1]);
			this.fRec6[0] = ((fSlow38 * ((fTemp2 + (fSlow60 * this.fRec7[0])) + (fSlow61 * this.fRec7[2]))) - (fSlow33 * ((fSlow62 * this.fRec6[2]) + fTemp3)));
			var fTemp4 = (fSlow29 * this.fRec5[1]);
			this.fRec5[0] = ((fSlow33 * ((fTemp3 + (fSlow64 * this.fRec6[0])) + (fSlow65 * this.fRec6[2]))) - (fSlow28 * ((fSlow66 * this.fRec5[2]) + fTemp4)));
			var fTemp5 = (fSlow24 * this.fRec4[1]);
			this.fRec4[0] = ((fSlow28 * ((fTemp4 + (fSlow68 * this.fRec5[0])) + (fSlow69 * this.fRec5[2]))) - (fSlow23 * ((fSlow70 * this.fRec4[2]) + fTemp5)));
			var fTemp6 = (fSlow19 * this.fRec3[1]);
			this.fRec3[0] = ((fSlow23 * ((fTemp5 + (fSlow72 * this.fRec4[0])) + (fSlow73 * this.fRec4[2]))) - (fSlow18 * ((fSlow74 * this.fRec3[2]) + fTemp6)));
			var fTemp7 = (fSlow14 * this.fRec2[1]);
			this.fRec2[0] = ((fSlow18 * ((fTemp6 + (fSlow76 * this.fRec3[0])) + (fSlow77 * this.fRec3[2]))) - (fSlow13 * ((fSlow78 * this.fRec2[2]) + fTemp7)));
			var fTemp8 = (fSlow9 * this.fRec1[1]);
			this.fRec1[0] = ((fSlow13 * ((fTemp7 + (fSlow80 * this.fRec2[0])) + (fSlow81 * this.fRec2[2]))) - (fSlow8 * ((fSlow82 * this.fRec1[2]) + fTemp8)));
			var fTemp9 = (fSlow4 * this.fRec0[1]);
			this.fRec0[0] = ((fSlow8 * ((fTemp8 + (fSlow84 * this.fRec1[0])) + (fSlow85 * this.fRec1[2]))) - (fSlow3 * ((fSlow86 * this.fRec0[2]) + fTemp9)));
			output0[i] = (fSlow3 * ((fTemp9 + (fSlow88 * this.fRec0[0])) + (fSlow89 * this.fRec0[2])));
			this.fRec9[2] = this.fRec9[1];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[2] = this.fRec7[1];
			this.fRec7[1] = this.fRec7[0];
			this.fRec6[2] = this.fRec6[1];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[2] = this.fRec5[1];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

