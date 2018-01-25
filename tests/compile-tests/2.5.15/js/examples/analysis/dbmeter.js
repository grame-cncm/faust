
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.iConst1;
	this.fRec1 = new Float32Array(2);
	this.fVbargraph1;
	this.iConst2;
	this.fRec2 = new Float32Array(2);
	this.fVbargraph2;
	this.iConst3;
	this.fRec3 = new Float32Array(2);
	this.fVbargraph3;
	this.iConst4;
	this.fRec4 = new Float32Array(2);
	this.fVbargraph4;
	this.iConst5;
	this.fRec5 = new Float32Array(2);
	this.fVbargraph5;
	this.iConst6;
	this.fRec6 = new Float32Array(2);
	this.fVbargraph6;
	this.iConst7;
	this.fRec7 = new Float32Array(2);
	this.fVbargraph7;
	this.iConst8;
	
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
		m.declare("name", "dbmeter");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 8;
		
	}
	this.getNumOutputs = function() {
		return 8;
		
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
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = (80 / min_f(192000, max_f(1, this.fSamplingFreq)));
		this.iConst1 = 0;
		this.iConst2 = 0;
		this.iConst3 = 0;
		this.iConst4 = 0;
		this.iConst5 = 0;
		this.iConst6 = 0;
		this.iConst7 = 0;
		this.iConst8 = 0;
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fRec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec2[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec3[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec4[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec5[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec6[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec7[l7] = 0;
			
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
		ui_interface.openHorizontalBox("8 channels dB meter");
		ui_interface.openVerticalBox("0");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b85c7e0", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("1");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b860ec0", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("2");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b8655a0", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("3");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b869d30", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("4");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b86e570", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("5");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b872e60", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("6");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b877800", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -70, 10);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("7");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7faa4b87c250", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -70, 10);
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
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec0[0] = max_f((this.fRec0[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp0))))));
			this.fVbargraph0 = this.fRec0[0];
			output0[i] = this.iConst1;
			var fTemp1 = input1[i];
			this.fRec1[0] = max_f((this.fRec1[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp1))))));
			this.fVbargraph1 = this.fRec1[0];
			output1[i] = this.iConst2;
			var fTemp2 = input2[i];
			this.fRec2[0] = max_f((this.fRec2[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp2))))));
			this.fVbargraph2 = this.fRec2[0];
			output2[i] = this.iConst3;
			var fTemp3 = input3[i];
			this.fRec3[0] = max_f((this.fRec3[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp3))))));
			this.fVbargraph3 = this.fRec3[0];
			output3[i] = this.iConst4;
			var fTemp4 = input4[i];
			this.fRec4[0] = max_f((this.fRec4[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp4))))));
			this.fVbargraph4 = this.fRec4[0];
			output4[i] = this.iConst5;
			var fTemp5 = input5[i];
			this.fRec5[0] = max_f((this.fRec5[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp5))))));
			this.fVbargraph5 = this.fRec5[0];
			output5[i] = this.iConst6;
			var fTemp6 = input6[i];
			this.fRec6[0] = max_f((this.fRec6[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp6))))));
			this.fVbargraph6 = this.fRec6[0];
			output6[i] = this.iConst7;
			var fTemp7 = input7[i];
			this.fRec7[0] = max_f((this.fRec7[1] - this.fConst0), min_f(10, (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(0.000316228, Math.abs(fTemp7))))));
			this.fVbargraph7 = this.fRec7[0];
			output7[i] = this.iConst8;
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[1] = this.fRec7[0];
			
		}
		
	}
	
}

