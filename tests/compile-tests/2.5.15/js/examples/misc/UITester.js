

function mydsp() {
	
	this.fCheckbox0;
	this.fCheckbox1;
	this.fEntry0;
	this.fVslider0;
	this.fVslider1;
	this.fVslider2;
	this.fVslider3;
	this.fVslider4;
	this.fVslider5;
	this.fVslider6;
	this.fButton0;
	this.fHslider0;
	this.fVslider7;
	this.fVslider8;
	this.fVslider9;
	this.fEntry1;
	this.fVbargraph0;
	this.fVslider10;
	this.fVslider11;
	this.fVslider12;
	this.fEntry2;
	this.fVbargraph1;
	this.fVslider13;
	this.fVslider14;
	this.fVslider15;
	this.fEntry3;
	this.fVbargraph2;
	this.fHbargraph0;
	this.fVslider16;
	this.fButton1;
	this.fHslider1;
	this.fEntry4;
	this.fVbargraph3;
	this.fHbargraph1;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "O. Guillerminet");
		m.declare("copyright", "(c) O. Guillerminet 2012");
		m.declare("license", "BSD");
		m.declare("name", "UITester");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 6;
		
	}
	this.getNumOutputs = function() {
		return 34;
		
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
			case 8: {
				rate = 1;
				break;
			}
			case 9: {
				rate = 1;
				break;
			}
			case 10: {
				rate = 1;
				break;
			}
			case 11: {
				rate = 1;
				break;
			}
			case 12: {
				rate = 1;
				break;
			}
			case 13: {
				rate = 1;
				break;
			}
			case 14: {
				rate = 1;
				break;
			}
			case 15: {
				rate = 1;
				break;
			}
			case 16: {
				rate = 1;
				break;
			}
			case 17: {
				rate = 1;
				break;
			}
			case 18: {
				rate = 1;
				break;
			}
			case 19: {
				rate = 1;
				break;
			}
			case 20: {
				rate = 1;
				break;
			}
			case 21: {
				rate = 1;
				break;
			}
			case 22: {
				rate = 1;
				break;
			}
			case 23: {
				rate = 1;
				break;
			}
			case 24: {
				rate = 1;
				break;
			}
			case 25: {
				rate = 1;
				break;
			}
			case 26: {
				rate = 1;
				break;
			}
			case 27: {
				rate = 1;
				break;
			}
			case 28: {
				rate = 1;
				break;
			}
			case 29: {
				rate = 1;
				break;
			}
			case 30: {
				rate = 1;
				break;
			}
			case 31: {
				rate = 1;
				break;
			}
			case 32: {
				rate = 1;
				break;
			}
			case 33: {
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
		this.fCheckbox0 = 0;
		this.fCheckbox1 = 0;
		this.fEntry0 = 60;
		this.fVslider0 = 60;
		this.fVslider1 = 60;
		this.fVslider2 = 60;
		this.fVslider3 = 60;
		this.fVslider4 = 60;
		this.fVslider5 = 60;
		this.fVslider6 = 60;
		this.fButton0 = 0;
		this.fHslider0 = 60;
		this.fVslider7 = 60;
		this.fVslider8 = 60;
		this.fVslider9 = 60;
		this.fEntry1 = 60;
		this.fVslider10 = 60;
		this.fVslider11 = 60;
		this.fVslider12 = 60;
		this.fEntry2 = 60;
		this.fVslider13 = 60;
		this.fVslider14 = 60;
		this.fVslider15 = 60;
		this.fEntry3 = 60;
		this.fVslider16 = 60;
		this.fButton1 = 0;
		this.fHslider1 = 60;
		this.fEntry4 = 60;
		
	}
	
	this.instanceClear = function() {
		
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
		ui_interface.openTabBox("grp 1");
		ui_interface.openHorizontalBox("hmisc");
		ui_interface.addButton("button", function handler(obj) { function setval(val) { obj.fButton1 = val; } return setval; }(this));
		ui_interface.addHorizontalBargraph("hbar", function handler(obj) { function setval(val) { obj.fHbargraph1 = val; } return setval; }(this), 0, 127);
		ui_interface.addHorizontalSlider("hslider", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fEntry4", "unit", "f");
		ui_interface.addNumEntry("num", function handler(obj) { function setval(val) { obj.fEntry4 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.addVerticalBargraph("vbar", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), 0, 127);
		ui_interface.declare("fVslider16", "unit", "f");
		ui_interface.addVerticalSlider("vslider4", function handler(obj) { function setval(val) { obj.fVslider16 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("knobs");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.addVerticalSlider("knob1", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.addVerticalSlider("knob2", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fVslider5", "style", "knob");
		ui_interface.addVerticalSlider("knob3", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("sliders");
		ui_interface.addVerticalSlider("vslider1", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.addVerticalSlider("vslider2", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.addVerticalSlider("vslider3", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("vbox");
		ui_interface.addCheckButton("check1", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.addCheckButton("check2", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.addNumEntry("knob0", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("vmisc");
		ui_interface.addButton("button", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.addHorizontalBargraph("hbar", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), 0, 127);
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("hslider", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.openHorizontalBox("small box 1");
		ui_interface.declare("fVslider9", "style", "knob");
		ui_interface.addVerticalSlider("knob4", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fEntry1", "unit", "f");
		ui_interface.addNumEntry("num1", function handler(obj) { function setval(val) { obj.fEntry1 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.addVerticalBargraph("vbar1", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), 0, 127);
		ui_interface.declare("fVslider7", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider5", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fVslider8", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider6", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("sub box 1");
		ui_interface.openHorizontalBox("small box 2");
		ui_interface.declare("fVslider12", "style", "knob");
		ui_interface.addVerticalSlider("knob5", function handler(obj) { function setval(val) { obj.fVslider12 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fEntry2", "unit", "f");
		ui_interface.addNumEntry("num2", function handler(obj) { function setval(val) { obj.fEntry2 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.addVerticalBargraph("vbar2", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), 0, 127);
		ui_interface.declare("fVslider10", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider7", function handler(obj) { function setval(val) { obj.fVslider10 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fVslider11", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider8", function handler(obj) { function setval(val) { obj.fVslider11 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("small box 3");
		ui_interface.declare("fVslider15", "style", "knob");
		ui_interface.addVerticalSlider("knob6", function handler(obj) { function setval(val) { obj.fVslider15 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fEntry3", "unit", "f");
		ui_interface.addNumEntry("num3", function handler(obj) { function setval(val) { obj.fEntry3 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.addVerticalBargraph("vbar3", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), 0, 127);
		ui_interface.declare("fVslider14", "unit", "m");
		ui_interface.addVerticalSlider("vslider10", function handler(obj) { function setval(val) { obj.fVslider14 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.declare("fVslider13", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider9", function handler(obj) { function setval(val) { obj.fVslider13 = val; } return setval; }(this), 60, 0, 127, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("fVslider6", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider4", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 60, 0, 127, 0.1);
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
		var output0 = outputs[0];
		var output1 = outputs[1];
		var output2 = outputs[2];
		var output3 = outputs[3];
		var output4 = outputs[4];
		var output5 = outputs[5];
		var output6 = outputs[6];
		var output7 = outputs[7];
		var output8 = outputs[8];
		var output9 = outputs[9];
		var output10 = outputs[10];
		var output11 = outputs[11];
		var output12 = outputs[12];
		var output13 = outputs[13];
		var output14 = outputs[14];
		var output15 = outputs[15];
		var output16 = outputs[16];
		var output17 = outputs[17];
		var output18 = outputs[18];
		var output19 = outputs[19];
		var output20 = outputs[20];
		var output21 = outputs[21];
		var output22 = outputs[22];
		var output23 = outputs[23];
		var output24 = outputs[24];
		var output25 = outputs[25];
		var output26 = outputs[26];
		var output27 = outputs[27];
		var output28 = outputs[28];
		var output29 = outputs[29];
		var output30 = outputs[30];
		var output31 = outputs[31];
		var output32 = outputs[32];
		var output33 = outputs[33];
		var fSlow0 = this.fCheckbox0;
		var fSlow1 = this.fCheckbox1;
		var fSlow2 = this.fEntry0;
		var fSlow3 = this.fVslider0;
		var fSlow4 = this.fVslider1;
		var fSlow5 = this.fVslider2;
		var fSlow6 = this.fVslider3;
		var fSlow7 = this.fVslider4;
		var fSlow8 = this.fVslider5;
		var fSlow9 = this.fVslider6;
		var fSlow10 = this.fButton0;
		var fSlow11 = this.fHslider0;
		var fSlow12 = this.fVslider7;
		var fSlow13 = this.fVslider8;
		var fSlow14 = this.fVslider9;
		var fSlow15 = this.fEntry1;
		var fSlow16 = this.fVslider10;
		var fSlow17 = this.fVslider11;
		var fSlow18 = this.fVslider12;
		var fSlow19 = this.fEntry2;
		var fSlow20 = this.fVslider13;
		var fSlow21 = this.fVslider14;
		var fSlow22 = this.fVslider15;
		var fSlow23 = this.fEntry3;
		var fSlow24 = this.fVslider16;
		var fSlow25 = this.fButton1;
		var fSlow26 = this.fHslider1;
		var fSlow27 = this.fEntry4;
		for (var i = 0; (i < count); i = (i + 1)) {
			output0[i] = fSlow0;
			output1[i] = fSlow1;
			output2[i] = fSlow2;
			output3[i] = fSlow3;
			output4[i] = fSlow4;
			output5[i] = fSlow5;
			output6[i] = fSlow6;
			output7[i] = fSlow7;
			output8[i] = fSlow8;
			output9[i] = fSlow9;
			output10[i] = fSlow10;
			output11[i] = fSlow11;
			output12[i] = fSlow12;
			output13[i] = fSlow13;
			output14[i] = fSlow14;
			output15[i] = fSlow15;
			this.fVbargraph0 = input0[i];
			output16[i] = this.fVbargraph0;
			output17[i] = fSlow16;
			output18[i] = fSlow17;
			output19[i] = fSlow18;
			output20[i] = fSlow19;
			this.fVbargraph1 = input1[i];
			output21[i] = this.fVbargraph1;
			output22[i] = fSlow20;
			output23[i] = fSlow21;
			output24[i] = fSlow22;
			output25[i] = fSlow23;
			this.fVbargraph2 = input2[i];
			output26[i] = this.fVbargraph2;
			this.fHbargraph0 = input3[i];
			output27[i] = this.fHbargraph0;
			output28[i] = fSlow24;
			output29[i] = fSlow25;
			output30[i] = fSlow26;
			output31[i] = fSlow27;
			this.fVbargraph3 = input4[i];
			output32[i] = this.fVbargraph3;
			this.fHbargraph1 = input5[i];
			output33[i] = this.fHbargraph1;
			
		}
		
	}
	
}

