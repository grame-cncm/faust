
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fHslider1;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider2;
	this.iRec3 = new Int32Array(2);
	this.fRec2 = new Float32Array(3);
	this.fRec1 = new Float32Array(3);
	this.fButton0;
	this.fVec0 = new Float32Array(2);
	this.fConst2;
	this.fHslider3;
	this.fVec1 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fConst6;
	this.fConst7;
	this.fHslider4;
	this.fConst8;
	this.fRec0 = new Float32Array(3);
	this.fConst9;
	this.fConst10;
	this.fConst11;
	this.fRec5 = new Float32Array(3);
	this.fConst12;
	this.fConst13;
	this.fConst14;
	this.fRec6 = new Float32Array(3);
	this.fConst15;
	this.fConst16;
	this.fConst17;
	this.fRec7 = new Float32Array(3);
	this.fConst18;
	this.fConst19;
	this.fConst20;
	this.fRec8 = new Float32Array(3);
	this.fConst21;
	this.fConst22;
	this.fConst23;
	this.fRec9 = new Float32Array(3);
	this.fConst24;
	this.fConst25;
	this.fConst26;
	this.fRec10 = new Float32Array(3);
	this.fConst27;
	this.fConst28;
	this.fConst29;
	this.fRec11 = new Float32Array(3);
	this.fConst30;
	this.fConst31;
	this.fConst32;
	this.fRec12 = new Float32Array(3);
	this.fConst33;
	this.fConst34;
	this.fConst35;
	this.fRec13 = new Float32Array(3);
	this.fConst36;
	this.fConst37;
	this.fConst38;
	this.fRec14 = new Float32Array(3);
	this.fConst39;
	this.fConst40;
	this.fConst41;
	this.fRec15 = new Float32Array(3);
	this.fConst42;
	this.fConst43;
	this.fConst44;
	this.fRec16 = new Float32Array(3);
	this.fConst45;
	this.fConst46;
	this.fConst47;
	this.fRec17 = new Float32Array(3);
	this.fConst48;
	this.fConst49;
	this.fConst50;
	this.fRec18 = new Float32Array(3);
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fRec19 = new Float32Array(3);
	this.fConst54;
	this.fConst55;
	this.fConst56;
	this.fRec20 = new Float32Array(3);
	this.fConst57;
	this.fConst58;
	this.fConst59;
	this.fRec21 = new Float32Array(3);
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fRec22 = new Float32Array(3);
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fRec23 = new Float32Array(3);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("description", "Simple MIDI-controllable djembe physical model.");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "DjembeMIDI");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (3.14159 / this.fConst0);
		this.fConst2 = (0.004 * this.fConst0);
		this.fConst3 = (0.002 * this.fConst0);
		this.fConst4 = (500 / this.fConst0);
		this.fConst5 = Math.pow(0.001, (1 / (0.6 * this.fConst0)));
		this.fConst6 = (0 - (2 * this.fConst5));
		this.fConst7 = (6.28319 / this.fConst0);
		this.fConst8 = mydsp_faustpower2_f(this.fConst5);
		this.fConst9 = Math.pow(0.001, (1 / (0.57 * this.fConst0)));
		this.fConst10 = (0 - (2 * this.fConst9));
		this.fConst11 = mydsp_faustpower2_f(this.fConst9);
		this.fConst12 = Math.pow(0.001, (1 / (0.54 * this.fConst0)));
		this.fConst13 = (0 - (2 * this.fConst12));
		this.fConst14 = mydsp_faustpower2_f(this.fConst12);
		this.fConst15 = Math.pow(0.001, (1 / (0.51 * this.fConst0)));
		this.fConst16 = (0 - (2 * this.fConst15));
		this.fConst17 = mydsp_faustpower2_f(this.fConst15);
		this.fConst18 = Math.pow(0.001, (1 / (0.48 * this.fConst0)));
		this.fConst19 = (0 - (2 * this.fConst18));
		this.fConst20 = mydsp_faustpower2_f(this.fConst18);
		this.fConst21 = Math.pow(0.001, (1 / (0.45 * this.fConst0)));
		this.fConst22 = (0 - (2 * this.fConst21));
		this.fConst23 = mydsp_faustpower2_f(this.fConst21);
		this.fConst24 = Math.pow(0.001, (1 / (0.42 * this.fConst0)));
		this.fConst25 = (0 - (2 * this.fConst24));
		this.fConst26 = mydsp_faustpower2_f(this.fConst24);
		this.fConst27 = Math.pow(0.001, (1 / (0.39 * this.fConst0)));
		this.fConst28 = (0 - (2 * this.fConst27));
		this.fConst29 = mydsp_faustpower2_f(this.fConst27);
		this.fConst30 = Math.pow(0.001, (1 / (0.36 * this.fConst0)));
		this.fConst31 = (0 - (2 * this.fConst30));
		this.fConst32 = mydsp_faustpower2_f(this.fConst30);
		this.fConst33 = Math.pow(0.001, (1 / (0.33 * this.fConst0)));
		this.fConst34 = (0 - (2 * this.fConst33));
		this.fConst35 = mydsp_faustpower2_f(this.fConst33);
		this.fConst36 = Math.pow(0.001, (1 / (0.3 * this.fConst0)));
		this.fConst37 = (0 - (2 * this.fConst36));
		this.fConst38 = mydsp_faustpower2_f(this.fConst36);
		this.fConst39 = Math.pow(0.001, (1 / (0.27 * this.fConst0)));
		this.fConst40 = (0 - (2 * this.fConst39));
		this.fConst41 = mydsp_faustpower2_f(this.fConst39);
		this.fConst42 = Math.pow(0.001, (1 / (0.24 * this.fConst0)));
		this.fConst43 = (0 - (2 * this.fConst42));
		this.fConst44 = mydsp_faustpower2_f(this.fConst42);
		this.fConst45 = Math.pow(0.001, (1 / (0.21 * this.fConst0)));
		this.fConst46 = (0 - (2 * this.fConst45));
		this.fConst47 = mydsp_faustpower2_f(this.fConst45);
		this.fConst48 = Math.pow(0.001, (1 / (0.18 * this.fConst0)));
		this.fConst49 = (0 - (2 * this.fConst48));
		this.fConst50 = mydsp_faustpower2_f(this.fConst48);
		this.fConst51 = Math.pow(0.001, (1 / (0.15 * this.fConst0)));
		this.fConst52 = (0 - (2 * this.fConst51));
		this.fConst53 = mydsp_faustpower2_f(this.fConst51);
		this.fConst54 = Math.pow(0.001, (1 / (0.12 * this.fConst0)));
		this.fConst55 = (0 - (2 * this.fConst54));
		this.fConst56 = mydsp_faustpower2_f(this.fConst54);
		this.fConst57 = Math.pow(0.001, (1 / (0.09 * this.fConst0)));
		this.fConst58 = (0 - (2 * this.fConst57));
		this.fConst59 = mydsp_faustpower2_f(this.fConst57);
		this.fConst60 = Math.pow(0.001, (1 / (0.06 * this.fConst0)));
		this.fConst61 = (0 - (2 * this.fConst60));
		this.fConst62 = mydsp_faustpower2_f(this.fConst60);
		this.fConst63 = Math.pow(0.001, (1 / (0.03 * this.fConst0)));
		this.fConst64 = (0 - (2 * this.fConst63));
		this.fConst65 = mydsp_faustpower2_f(this.fConst63);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 1;
		this.fHslider1 = 1;
		this.fHslider2 = 0.5;
		this.fButton0 = 0;
		this.fHslider3 = 0.5;
		this.fHslider4 = 60;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec3[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fVec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec4[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec0[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec5[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec6[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec7[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			this.fRec8[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec9[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec10[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			this.fRec11[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec12[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			this.fRec13[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			this.fRec14[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			this.fRec15[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			this.fRec16[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			this.fRec17[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			this.fRec18[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			this.fRec19[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			this.fRec20[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			this.fRec21[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			this.fRec22[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			this.fRec23[l25] = 0;
			
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
		ui_interface.openVerticalBox("djembe");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 60, 50, 100, 0.01);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "midi", "ctrl 1");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("strikePosition", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("strikeSharpness", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0.5, 0.01, 5, 0.01);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "3", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = (0.05 * this.fHslider0);
		var fSlow1 = this.fHslider2;
		var fSlow2 = Math.tan((this.fConst1 * ((15000 * fSlow1) + 500)));
		var fSlow3 = (1 / fSlow2);
		var fSlow4 = (((fSlow3 + 1.41421) / fSlow2) + 1);
		var fSlow5 = (this.fHslider1 / fSlow4);
		var fSlow6 = Math.tan((this.fConst1 * ((500 * fSlow1) + 40)));
		var fSlow7 = (1 / fSlow6);
		var fSlow8 = (1 / (((fSlow7 + 1.41421) / fSlow6) + 1));
		var fSlow9 = (1 / mydsp_faustpower2_f(fSlow6));
		var fSlow10 = (2 * (0 - fSlow9));
		var fSlow11 = (((fSlow7 + -1.41421) / fSlow6) + 1);
		var fSlow12 = (2 * (1 - fSlow9));
		var fSlow13 = (1 / fSlow4);
		var fSlow14 = (2 * (1 - (1 / mydsp_faustpower2_f(fSlow2))));
		var fSlow15 = (((fSlow3 + -1.41421) / fSlow2) + 1);
		var fSlow16 = this.fButton0;
		var fSlow17 = this.fHslider3;
		var fSlow18 = (this.fConst2 * fSlow17);
		var fSlow19 = (this.fConst3 * fSlow17);
		var fSlow20 = (this.fConst4 / fSlow17);
		var fSlow21 = this.fHslider4;
		var fSlow22 = (this.fConst6 * Math.cos((this.fConst7 * fSlow21)));
		var fSlow23 = (this.fConst10 * Math.cos((this.fConst7 * (fSlow21 + 200))));
		var fSlow24 = (this.fConst13 * Math.cos((this.fConst7 * (fSlow21 + 400))));
		var fSlow25 = (this.fConst16 * Math.cos((this.fConst7 * (fSlow21 + 600))));
		var fSlow26 = (this.fConst19 * Math.cos((this.fConst7 * (fSlow21 + 800))));
		var fSlow27 = (this.fConst22 * Math.cos((this.fConst7 * (fSlow21 + 1000))));
		var fSlow28 = (this.fConst25 * Math.cos((this.fConst7 * (fSlow21 + 1200))));
		var fSlow29 = (this.fConst28 * Math.cos((this.fConst7 * (fSlow21 + 1400))));
		var fSlow30 = (this.fConst31 * Math.cos((this.fConst7 * (fSlow21 + 1600))));
		var fSlow31 = (this.fConst34 * Math.cos((this.fConst7 * (fSlow21 + 1800))));
		var fSlow32 = (this.fConst37 * Math.cos((this.fConst7 * (fSlow21 + 2000))));
		var fSlow33 = (this.fConst40 * Math.cos((this.fConst7 * (fSlow21 + 2200))));
		var fSlow34 = (this.fConst43 * Math.cos((this.fConst7 * (fSlow21 + 2400))));
		var fSlow35 = (this.fConst46 * Math.cos((this.fConst7 * (fSlow21 + 2600))));
		var fSlow36 = (this.fConst49 * Math.cos((this.fConst7 * (fSlow21 + 2800))));
		var fSlow37 = (this.fConst52 * Math.cos((this.fConst7 * (fSlow21 + 3000))));
		var fSlow38 = (this.fConst55 * Math.cos((this.fConst7 * (fSlow21 + 3200))));
		var fSlow39 = (this.fConst58 * Math.cos((this.fConst7 * (fSlow21 + 3400))));
		var fSlow40 = (this.fConst61 * Math.cos((this.fConst7 * (fSlow21 + 3600))));
		var fSlow41 = (this.fConst64 * Math.cos((this.fConst7 * (fSlow21 + 3800))));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec3[0] = ((1103515245 * this.iRec3[1]) + 12345);
			this.fRec2[0] = ((4.65661e-10 * this.iRec3[0]) - (fSlow8 * ((fSlow11 * this.fRec2[2]) + (fSlow12 * this.fRec2[1]))));
			this.fRec1[0] = ((fSlow8 * (((fSlow10 * this.fRec2[1]) + (fSlow9 * this.fRec2[0])) + (fSlow9 * this.fRec2[2]))) - (fSlow13 * ((fSlow14 * this.fRec1[1]) + (fSlow15 * this.fRec1[2]))));
			this.fVec0[0] = fSlow16;
			this.fVec1[0] = fSlow17;
			this.fRec4[0] = ((((fSlow16 - this.fVec0[1]) > 0) > 0)?0:min_f(fSlow18, ((this.fRec4[1] + (this.fConst2 * (fSlow17 - this.fVec1[1]))) + 1)));
			var iTemp0 = (this.fRec4[0] < fSlow19);
			var fTemp1 = (fSlow5 * ((this.fRec1[2] + (this.fRec1[0] + (2 * this.fRec1[1]))) * (iTemp0?((this.fRec4[0] < 0)?0:(iTemp0?(fSlow20 * this.fRec4[0]):1)):((this.fRec4[0] < fSlow18)?((fSlow20 * (0 - (this.fRec4[0] - fSlow19))) + 1):0))));
			this.fRec0[0] = (fTemp1 - ((fSlow22 * this.fRec0[1]) + (this.fConst8 * this.fRec0[2])));
			this.fRec5[0] = (fTemp1 - ((fSlow23 * this.fRec5[1]) + (this.fConst11 * this.fRec5[2])));
			this.fRec6[0] = (fTemp1 - ((fSlow24 * this.fRec6[1]) + (this.fConst14 * this.fRec6[2])));
			this.fRec7[0] = (fTemp1 - ((fSlow25 * this.fRec7[1]) + (this.fConst17 * this.fRec7[2])));
			this.fRec8[0] = (fTemp1 - ((fSlow26 * this.fRec8[1]) + (this.fConst20 * this.fRec8[2])));
			this.fRec9[0] = (fTemp1 - ((fSlow27 * this.fRec9[1]) + (this.fConst23 * this.fRec9[2])));
			this.fRec10[0] = (fTemp1 - ((fSlow28 * this.fRec10[1]) + (this.fConst26 * this.fRec10[2])));
			this.fRec11[0] = (fTemp1 - ((fSlow29 * this.fRec11[1]) + (this.fConst29 * this.fRec11[2])));
			this.fRec12[0] = (fTemp1 - ((fSlow30 * this.fRec12[1]) + (this.fConst32 * this.fRec12[2])));
			this.fRec13[0] = (fTemp1 - ((fSlow31 * this.fRec13[1]) + (this.fConst35 * this.fRec13[2])));
			this.fRec14[0] = (fTemp1 - ((fSlow32 * this.fRec14[1]) + (this.fConst38 * this.fRec14[2])));
			this.fRec15[0] = (fTemp1 - ((fSlow33 * this.fRec15[1]) + (this.fConst41 * this.fRec15[2])));
			this.fRec16[0] = (fTemp1 - ((fSlow34 * this.fRec16[1]) + (this.fConst44 * this.fRec16[2])));
			this.fRec17[0] = (fTemp1 - ((fSlow35 * this.fRec17[1]) + (this.fConst47 * this.fRec17[2])));
			this.fRec18[0] = (fTemp1 - ((fSlow36 * this.fRec18[1]) + (this.fConst50 * this.fRec18[2])));
			this.fRec19[0] = (fTemp1 - ((fSlow37 * this.fRec19[1]) + (this.fConst53 * this.fRec19[2])));
			this.fRec20[0] = (fTemp1 - ((fSlow38 * this.fRec20[1]) + (this.fConst56 * this.fRec20[2])));
			this.fRec21[0] = (fTemp1 - ((fSlow39 * this.fRec21[1]) + (this.fConst59 * this.fRec21[2])));
			this.fRec22[0] = (fTemp1 - ((fSlow40 * this.fRec22[1]) + (this.fConst62 * this.fRec22[2])));
			this.fRec23[0] = (fTemp1 - ((fSlow41 * this.fRec23[1]) + (this.fConst65 * this.fRec23[2])));
			var fTemp2 = (fSlow0 * ((((((((((((((((((((this.fRec0[0] + (0.25 * (this.fRec5[0] - this.fRec5[2]))) + (0.111111 * (this.fRec6[0] - this.fRec6[2]))) + (0.0625 * (this.fRec7[0] - this.fRec7[2]))) + (0.04 * (this.fRec8[0] - this.fRec8[2]))) + (0.0277778 * (this.fRec9[0] - this.fRec9[2]))) + (0.0204082 * (this.fRec10[0] - this.fRec10[2]))) + (0.015625 * (this.fRec11[0] - this.fRec11[2]))) + (0.0123457 * (this.fRec12[0] - this.fRec12[2]))) + (0.01 * (this.fRec13[0] - this.fRec13[2]))) + (0.00826446 * (this.fRec14[0] - this.fRec14[2]))) + (0.00694444 * (this.fRec15[0] - this.fRec15[2]))) + (0.00591716 * (this.fRec16[0] - this.fRec16[2]))) + (0.00510204 * (this.fRec17[0] - this.fRec17[2]))) + (0.00444444 * (this.fRec18[0] - this.fRec18[2]))) + (0.00390625 * (this.fRec19[0] - this.fRec19[2]))) + (0.00346021 * (this.fRec20[0] - this.fRec20[2]))) + (0.00308642 * (this.fRec21[0] - this.fRec21[2]))) + (0.00277008 * (this.fRec22[0] - this.fRec22[2]))) + (0.0025 * (this.fRec23[0] - this.fRec23[2]))) - this.fRec0[2]));
			output0[i] = fTemp2;
			output1[i] = fTemp2;
			this.iRec3[1] = this.iRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fVec0[1] = this.fVec0[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec5[2] = this.fRec5[1];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[2] = this.fRec6[1];
			this.fRec6[1] = this.fRec6[0];
			this.fRec7[2] = this.fRec7[1];
			this.fRec7[1] = this.fRec7[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			this.fRec9[2] = this.fRec9[1];
			this.fRec9[1] = this.fRec9[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fRec13[2] = this.fRec13[1];
			this.fRec13[1] = this.fRec13[0];
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.fRec15[2] = this.fRec15[1];
			this.fRec15[1] = this.fRec15[0];
			this.fRec16[2] = this.fRec16[1];
			this.fRec16[1] = this.fRec16[0];
			this.fRec17[2] = this.fRec17[1];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec19[2] = this.fRec19[1];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fRec21[2] = this.fRec21[1];
			this.fRec21[1] = this.fRec21[0];
			this.fRec22[2] = this.fRec22[1];
			this.fRec22[1] = this.fRec22[0];
			this.fRec23[2] = this.fRec23[1];
			this.fRec23[1] = this.fRec23[0];
			
		}
		
	}
	
}

