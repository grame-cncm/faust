
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fVslider0;
	this.fRec1 = new Float32Array(2);
	this.fEntry0;
	this.fCheckbox0;
	this.fVslider1;
	this.fRec3 = new Float32Array(2);
	this.fRec2 = new Float32Array(2);
	this.fVbargraph0;
	this.fEntry1;
	this.fCheckbox1;
	this.fVslider2;
	this.fRec5 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fVbargraph1;
	this.fEntry2;
	this.fCheckbox2;
	this.fVslider3;
	this.fRec7 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fVbargraph2;
	this.fEntry3;
	this.fCheckbox3;
	this.fVslider4;
	this.fRec9 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fVbargraph3;
	this.fEntry4;
	this.fCheckbox4;
	this.fVslider5;
	this.fRec11 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fVbargraph4;
	this.fEntry5;
	this.fCheckbox5;
	this.fVslider6;
	this.fRec13 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fVbargraph5;
	this.fEntry6;
	this.fCheckbox6;
	this.fVslider7;
	this.fRec15 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fVbargraph6;
	this.fEntry7;
	this.fCheckbox7;
	this.fVslider8;
	this.fRec17 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fVbargraph7;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph8;
	this.fRec18 = new Float32Array(2);
	this.fVbargraph9;
	
	this.metadata = function(m) { 
		m.declare("../analysis/vumeter.dsp/author", "Grame");
		m.declare("../analysis/vumeter.dsp/copyright", "(c)GRAME 2006");
		m.declare("../analysis/vumeter.dsp/license", "BSD");
		m.declare("../analysis/vumeter.dsp/name", "vumeter");
		m.declare("../analysis/vumeter.dsp/version", "1.0");
		m.declare("../dynamic/volume.dsp/author", "Grame");
		m.declare("../dynamic/volume.dsp/copyright", "(c)GRAME 2006");
		m.declare("../dynamic/volume.dsp/license", "BSD");
		m.declare("../dynamic/volume.dsp/name", "volume");
		m.declare("../dynamic/volume.dsp/version", "1.0");
		m.declare("../spat/panpot.dsp/author", "Grame");
		m.declare("../spat/panpot.dsp/copyright", "(c)GRAME 2006");
		m.declare("../spat/panpot.dsp/license", "BSD");
		m.declare("../spat/panpot.dsp/name", "panpot");
		m.declare("../spat/panpot.dsp/version", "1.0");
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
		m.declare("name", "mixer");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 8;
		
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
		this.fVslider0 = 0;
		this.fEntry0 = 0;
		this.fCheckbox0 = 0;
		this.fVslider1 = 0;
		this.fEntry1 = 0;
		this.fCheckbox1 = 0;
		this.fVslider2 = 0;
		this.fEntry2 = 0;
		this.fCheckbox2 = 0;
		this.fVslider3 = 0;
		this.fEntry3 = 0;
		this.fCheckbox3 = 0;
		this.fVslider4 = 0;
		this.fEntry4 = 0;
		this.fCheckbox4 = 0;
		this.fVslider5 = 0;
		this.fEntry5 = 0;
		this.fCheckbox5 = 0;
		this.fVslider6 = 0;
		this.fEntry6 = 0;
		this.fCheckbox6 = 0;
		this.fVslider7 = 0;
		this.fEntry7 = 0;
		this.fCheckbox7 = 0;
		this.fVslider8 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec1[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec3[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec5[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec7[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec6[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec9[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fRec8[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec11[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec10[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec13[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec12[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec15[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec14[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec17[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fRec16[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec0[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec18[l18] = 0;
			
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
		ui_interface.openHorizontalBox("mixer");
		ui_interface.openVerticalBox("Ch 0");
		ui_interface.declare("fEntry0", "1", "");
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider1", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph0", "2", "");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa885fe2f00", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 1");
		ui_interface.declare("fEntry1", "1", "");
		ui_interface.declare("fEntry1", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry1 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider2", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph1", "2", "");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa885fed000", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 2");
		ui_interface.declare("fEntry2", "1", "");
		ui_interface.declare("fEntry2", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry2 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider3", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph2", "2", "");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa885ff7540", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 3");
		ui_interface.declare("fEntry3", "1", "");
		ui_interface.declare("fEntry3", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry3 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider4", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph3", "2", "");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa888005cc0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox3 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 4");
		ui_interface.declare("fEntry4", "1", "");
		ui_interface.declare("fEntry4", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry4 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider5", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph4", "2", "");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa888010780", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox4 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 5");
		ui_interface.declare("fEntry5", "1", "");
		ui_interface.declare("fEntry5", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry5 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider6", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph5", "2", "");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa88801b500", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox5 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 6");
		ui_interface.declare("fEntry6", "1", "");
		ui_interface.declare("fEntry6", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry6 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider7", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph6", "2", "");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa888026540", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox6 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Ch 7");
		ui_interface.declare("fEntry7", "1", "");
		ui_interface.declare("fEntry7", "style", "knob");
		ui_interface.addNumEntry("pan", function handler(obj) { function setval(val) { obj.fEntry7 = val; } return setval; }(this), 0, -90, 90, 1);
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider8", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.declare("fVbargraph7", "2", "");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa888031840", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.addCheckButton("mute", function handler(obj) { function setval(val) { obj.fCheckbox7 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("stereo out");
		ui_interface.openVerticalBox("L");
		ui_interface.declare("fVbargraph8", "2", "");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa888035730", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("R");
		ui_interface.declare("fVbargraph9", "2", "");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fa88803ecd0", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -70, 5);
		ui_interface.closeBox();
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, -70, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var input4 = inputs[4];
		var input5 = inputs[5];
		var input6 = inputs[6];
		var input7 = inputs[7];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var fSlow1 = (0.00555556 * (this.fEntry0 + -90));
		var fSlow2 = Math.sqrt((0 - fSlow1));
		var fSlow3 = (1 - this.fCheckbox0);
		var fSlow4 = (0.001 * Math.pow(10, (0.05 * this.fVslider1)));
		var fSlow5 = (0.00555556 * (this.fEntry1 + -90));
		var fSlow6 = Math.sqrt((0 - fSlow5));
		var fSlow7 = (1 - this.fCheckbox1);
		var fSlow8 = (0.001 * Math.pow(10, (0.05 * this.fVslider2)));
		var fSlow9 = (0.00555556 * (this.fEntry2 + -90));
		var fSlow10 = Math.sqrt((0 - fSlow9));
		var fSlow11 = (1 - this.fCheckbox2);
		var fSlow12 = (0.001 * Math.pow(10, (0.05 * this.fVslider3)));
		var fSlow13 = (0.00555556 * (this.fEntry3 + -90));
		var fSlow14 = Math.sqrt((0 - fSlow13));
		var fSlow15 = (1 - this.fCheckbox3);
		var fSlow16 = (0.001 * Math.pow(10, (0.05 * this.fVslider4)));
		var fSlow17 = (0.00555556 * (this.fEntry4 + -90));
		var fSlow18 = Math.sqrt((0 - fSlow17));
		var fSlow19 = (1 - this.fCheckbox4);
		var fSlow20 = (0.001 * Math.pow(10, (0.05 * this.fVslider5)));
		var fSlow21 = (0.00555556 * (this.fEntry5 + -90));
		var fSlow22 = Math.sqrt((0 - fSlow21));
		var fSlow23 = (1 - this.fCheckbox5);
		var fSlow24 = (0.001 * Math.pow(10, (0.05 * this.fVslider6)));
		var fSlow25 = (0.00555556 * (this.fEntry6 + -90));
		var fSlow26 = Math.sqrt((0 - fSlow25));
		var fSlow27 = (1 - this.fCheckbox6);
		var fSlow28 = (0.001 * Math.pow(10, (0.05 * this.fVslider7)));
		var fSlow29 = (0.00555556 * (this.fEntry7 + -90));
		var fSlow30 = Math.sqrt((0 - fSlow29));
		var fSlow31 = (1 - this.fCheckbox7);
		var fSlow32 = (0.001 * Math.pow(10, (0.05 * this.fVslider8)));
		var fSlow33 = Math.sqrt((fSlow1 + 1));
		var fSlow34 = Math.sqrt((fSlow5 + 1));
		var fSlow35 = Math.sqrt((fSlow9 + 1));
		var fSlow36 = Math.sqrt((fSlow13 + 1));
		var fSlow37 = Math.sqrt((fSlow17 + 1));
		var fSlow38 = Math.sqrt((fSlow21 + 1));
		var fSlow39 = Math.sqrt((fSlow25 + 1));
		var fSlow40 = Math.sqrt((fSlow29 + 1));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fRec1[0] = (fSlow0 + (0.999 * this.fRec1[1]));
			this.fRec3[0] = (fSlow4 + (0.999 * this.fRec3[1]));
			var fTemp0 = (fSlow3 * (input0[i] * this.fRec3[0]));
			this.fRec2[0] = max_f((this.fRec2[1] - this.fConst0), Math.abs(fTemp0));
			this.fVbargraph0 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec2[0])));
			this.fRec5[0] = (fSlow8 + (0.999 * this.fRec5[1]));
			var fTemp1 = (fSlow7 * (input1[i] * this.fRec5[0]));
			this.fRec4[0] = max_f((this.fRec4[1] - this.fConst0), Math.abs(fTemp1));
			this.fVbargraph1 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec4[0])));
			this.fRec7[0] = (fSlow12 + (0.999 * this.fRec7[1]));
			var fTemp2 = (fSlow11 * (input2[i] * this.fRec7[0]));
			this.fRec6[0] = max_f((this.fRec6[1] - this.fConst0), Math.abs(fTemp2));
			this.fVbargraph2 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec6[0])));
			this.fRec9[0] = (fSlow16 + (0.999 * this.fRec9[1]));
			var fTemp3 = (fSlow15 * (input3[i] * this.fRec9[0]));
			this.fRec8[0] = max_f((this.fRec8[1] - this.fConst0), Math.abs(fTemp3));
			this.fVbargraph3 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec8[0])));
			this.fRec11[0] = (fSlow20 + (0.999 * this.fRec11[1]));
			var fTemp4 = (fSlow19 * (input4[i] * this.fRec11[0]));
			this.fRec10[0] = max_f((this.fRec10[1] - this.fConst0), Math.abs(fTemp4));
			this.fVbargraph4 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec10[0])));
			this.fRec13[0] = (fSlow24 + (0.999 * this.fRec13[1]));
			var fTemp5 = (fSlow23 * (input5[i] * this.fRec13[0]));
			this.fRec12[0] = max_f((this.fRec12[1] - this.fConst0), Math.abs(fTemp5));
			this.fVbargraph5 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec12[0])));
			this.fRec15[0] = (fSlow28 + (0.999 * this.fRec15[1]));
			var fTemp6 = (fSlow27 * (input6[i] * this.fRec15[0]));
			this.fRec14[0] = max_f((this.fRec14[1] - this.fConst0), Math.abs(fTemp6));
			this.fVbargraph6 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec14[0])));
			this.fRec17[0] = (fSlow32 + (0.999 * this.fRec17[1]));
			var fTemp7 = (fSlow31 * (input7[i] * this.fRec17[0]));
			this.fRec16[0] = max_f((this.fRec16[1] - this.fConst0), Math.abs(fTemp7));
			this.fVbargraph7 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec16[0])));
			var fTemp8 = (this.fRec1[0] * ((((((((fSlow2 * fTemp0) + (fSlow6 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow14 * fTemp3)) + (fSlow18 * fTemp4)) + (fSlow22 * fTemp5)) + (fSlow26 * fTemp6)) + (fSlow30 * fTemp7)));
			this.fRec0[0] = max_f((this.fRec0[1] - this.fConst0), Math.abs(fTemp8));
			this.fVbargraph8 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec0[0])));
			output0[i] = fTemp8;
			var fTemp9 = (this.fRec1[0] * ((((((((fSlow33 * fTemp0) + (fSlow34 * fTemp1)) + (fSlow35 * fTemp2)) + (fSlow36 * fTemp3)) + (fSlow37 * fTemp4)) + (fSlow38 * fTemp5)) + (fSlow39 * fTemp6)) + (fSlow40 * fTemp7)));
			this.fRec18[0] = max_f((this.fRec18[1] - this.fConst0), Math.abs(fTemp9));
			this.fVbargraph9 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, this.fRec18[0])));
			output1[i] = fTemp9;
			this.fRec1[1] = this.fRec1[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec18[1] = this.fRec18[0];
			
		}
		
	}
	
}

