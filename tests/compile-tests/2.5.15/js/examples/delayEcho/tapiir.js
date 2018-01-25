
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);

function mydsp() {
	
	this.fVslider0;
	this.fVslider1;
	this.fVslider2;
	this.fVslider3;
	this.fVslider4;
	this.fVslider5;
	this.fVslider6;
	this.fVslider7;
	this.fVslider8;
	this.fVslider9;
	this.fVslider10;
	this.IOTA;
	this.fVec0 = new Float32Array(1048576);
	this.fSamplingFreq;
	this.fConst0;
	this.fVslider11;
	this.fRec0 = new Float32Array(2);
	this.fVslider12;
	this.fVslider13;
	this.fVslider14;
	this.fVslider15;
	this.fVslider16;
	this.fVslider17;
	this.fVslider18;
	this.fVslider19;
	this.fVslider20;
	this.fVec1 = new Float32Array(1048576);
	this.fVslider21;
	this.fRec1 = new Float32Array(2);
	this.fVslider22;
	this.fVslider23;
	this.fVslider24;
	this.fVslider25;
	this.fVslider26;
	this.fVslider27;
	this.fVslider28;
	this.fVslider29;
	this.fVslider30;
	this.fVec2 = new Float32Array(1048576);
	this.fVslider31;
	this.fRec2 = new Float32Array(2);
	this.fVslider32;
	this.fVslider33;
	this.fVslider34;
	this.fVslider35;
	this.fVslider36;
	this.fVslider37;
	this.fVslider38;
	this.fVslider39;
	this.fVslider40;
	this.fVec3 = new Float32Array(1048576);
	this.fVslider41;
	this.fRec3 = new Float32Array(2);
	this.fVslider42;
	this.fVslider43;
	this.fVslider44;
	this.fVslider45;
	this.fVslider46;
	this.fVslider47;
	this.fVslider48;
	this.fVslider49;
	this.fVslider50;
	this.fVec4 = new Float32Array(1048576);
	this.fVslider51;
	this.fRec4 = new Float32Array(2);
	this.fVslider52;
	this.fVslider53;
	this.fVslider54;
	this.fVslider55;
	this.fVslider56;
	this.fVslider57;
	this.fVslider58;
	this.fVslider59;
	this.fVslider60;
	this.fVec5 = new Float32Array(1048576);
	this.fVslider61;
	this.fRec5 = new Float32Array(2);
	this.fVslider62;
	this.fVslider63;
	this.fVslider64;
	this.fVslider65;
	this.fVslider66;
	this.fVslider67;
	this.fVslider68;
	this.fVslider69;
	this.fVslider70;
	this.fVslider71;
	this.fVslider72;
	this.fVslider73;
	this.fVslider74;
	this.fVslider75;
	this.fVslider76;
	this.fVslider77;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "tapiir");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
	}

	this.getNumInputs = function() {
		return 2;
		
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = 1;
		this.fVslider1 = 0;
		this.fVslider2 = 1;
		this.fVslider3 = 0;
		this.fVslider4 = 0;
		this.fVslider5 = 0;
		this.fVslider6 = 0;
		this.fVslider7 = 0;
		this.fVslider8 = 0;
		this.fVslider9 = 1;
		this.fVslider10 = 1;
		this.fVslider11 = 0;
		this.fVslider12 = 1;
		this.fVslider13 = 0;
		this.fVslider14 = 0;
		this.fVslider15 = 0;
		this.fVslider16 = 0;
		this.fVslider17 = 0;
		this.fVslider18 = 0;
		this.fVslider19 = 1;
		this.fVslider20 = 1;
		this.fVslider21 = 0;
		this.fVslider22 = 1;
		this.fVslider23 = 0;
		this.fVslider24 = 0;
		this.fVslider25 = 0;
		this.fVslider26 = 0;
		this.fVslider27 = 0;
		this.fVslider28 = 0;
		this.fVslider29 = 1;
		this.fVslider30 = 1;
		this.fVslider31 = 0;
		this.fVslider32 = 1;
		this.fVslider33 = 0;
		this.fVslider34 = 0;
		this.fVslider35 = 0;
		this.fVslider36 = 0;
		this.fVslider37 = 0;
		this.fVslider38 = 0;
		this.fVslider39 = 1;
		this.fVslider40 = 1;
		this.fVslider41 = 0;
		this.fVslider42 = 1;
		this.fVslider43 = 0;
		this.fVslider44 = 0;
		this.fVslider45 = 0;
		this.fVslider46 = 0;
		this.fVslider47 = 0;
		this.fVslider48 = 0;
		this.fVslider49 = 1;
		this.fVslider50 = 1;
		this.fVslider51 = 0;
		this.fVslider52 = 1;
		this.fVslider53 = 0;
		this.fVslider54 = 0;
		this.fVslider55 = 0;
		this.fVslider56 = 0;
		this.fVslider57 = 0;
		this.fVslider58 = 0;
		this.fVslider59 = 1;
		this.fVslider60 = 1;
		this.fVslider61 = 0;
		this.fVslider62 = 0;
		this.fVslider63 = 0;
		this.fVslider64 = 0;
		this.fVslider65 = 0;
		this.fVslider66 = 0;
		this.fVslider67 = 1;
		this.fVslider68 = 1;
		this.fVslider69 = 1;
		this.fVslider70 = 0;
		this.fVslider71 = 0;
		this.fVslider72 = 0;
		this.fVslider73 = 0;
		this.fVslider74 = 0;
		this.fVslider75 = 0;
		this.fVslider76 = 1;
		this.fVslider77 = 1;
		
	}
	
	this.instanceClear = function() {
		this.IOTA = 0;
		for (var l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec0[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 1048576); l2 = (l2 + 1)) {
			this.fVec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 1048576); l4 = (l4 + 1)) {
			this.fVec2[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 1048576); l6 = (l6 + 1)) {
			this.fVec3[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec3[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 1048576); l8 = (l8 + 1)) {
			this.fVec4[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec4[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 1048576); l10 = (l10 + 1)) {
			this.fVec5[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fRec5[l11] = 0;
			
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
		ui_interface.openVerticalBox("Tapiir");
		ui_interface.openTabBox("0x00");
		ui_interface.openHorizontalBox("Tap 0");
		ui_interface.addVerticalSlider("delay (sec)", function handler(obj) { function setval(val) { obj.fVslider11 = val; } return setval; }(this), 0, 0, 5, 0.01);
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider10 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 1");
		ui_interface.addVerticalSlider("delay (sec)", function handler(obj) { function setval(val) { obj.fVslider21 = val; } return setval; }(this), 0, 0, 5, 0.01);
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider12 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider19 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider20 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider13 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider14 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider15 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider16 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider17 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider18 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 2");
		ui_interface.addVerticalSlider("delay (sec)", function handler(obj) { function setval(val) { obj.fVslider31 = val; } return setval; }(this), 0, 0, 5, 0.01);
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider22 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider29 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider30 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider23 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider24 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider25 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider26 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider27 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider28 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 3");
		ui_interface.addVerticalSlider("delay (sec)", function handler(obj) { function setval(val) { obj.fVslider41 = val; } return setval; }(this), 0, 0, 5, 0.01);
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider32 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider39 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider40 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider33 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider34 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider35 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider36 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider37 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider38 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 4");
		ui_interface.addVerticalSlider("delay (sec)", function handler(obj) { function setval(val) { obj.fVslider51 = val; } return setval; }(this), 0, 0, 5, 0.01);
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider42 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider49 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider50 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider43 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider44 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider45 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider46 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider47 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider48 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Tap 5");
		ui_interface.addVerticalSlider("delay (sec)", function handler(obj) { function setval(val) { obj.fVslider61 = val; } return setval; }(this), 0, 0, 5, 0.01);
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider52 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider59 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider60 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider53 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider54 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider55 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider56 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider57 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider58 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.openVerticalBox("outputs");
		ui_interface.openHorizontalBox("output 0");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider67 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider68 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider62 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider63 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider64 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider65 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider66 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("output 1");
		ui_interface.addVerticalSlider("gain", function handler(obj) { function setval(val) { obj.fVslider69 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 0", function handler(obj) { function setval(val) { obj.fVslider76 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("input 1", function handler(obj) { function setval(val) { obj.fVslider77 = val; } return setval; }(this), 1, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 0", function handler(obj) { function setval(val) { obj.fVslider70 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 1", function handler(obj) { function setval(val) { obj.fVslider71 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 2", function handler(obj) { function setval(val) { obj.fVslider72 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 3", function handler(obj) { function setval(val) { obj.fVslider73 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 4", function handler(obj) { function setval(val) { obj.fVslider74 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.addVerticalSlider("tap 5", function handler(obj) { function setval(val) { obj.fVslider75 = val; } return setval; }(this), 0, 0, 1, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fVslider0;
		var fSlow1 = this.fVslider1;
		var fSlow2 = this.fVslider2;
		var fSlow3 = this.fVslider3;
		var fSlow4 = this.fVslider4;
		var fSlow5 = this.fVslider5;
		var fSlow6 = this.fVslider6;
		var fSlow7 = this.fVslider7;
		var fSlow8 = this.fVslider8;
		var fSlow9 = this.fVslider9;
		var fSlow10 = this.fVslider10;
		var iSlow11 = min_f(524288, max_f(0, (this.fConst0 * this.fVslider11)));
		var fSlow12 = this.fVslider12;
		var fSlow13 = this.fVslider13;
		var fSlow14 = this.fVslider14;
		var fSlow15 = this.fVslider15;
		var fSlow16 = this.fVslider16;
		var fSlow17 = this.fVslider17;
		var fSlow18 = this.fVslider18;
		var fSlow19 = this.fVslider19;
		var fSlow20 = this.fVslider20;
		var iSlow21 = min_f(524288, max_f(0, (this.fConst0 * this.fVslider21)));
		var fSlow22 = this.fVslider22;
		var fSlow23 = this.fVslider23;
		var fSlow24 = this.fVslider24;
		var fSlow25 = this.fVslider25;
		var fSlow26 = this.fVslider26;
		var fSlow27 = this.fVslider27;
		var fSlow28 = this.fVslider28;
		var fSlow29 = this.fVslider29;
		var fSlow30 = this.fVslider30;
		var iSlow31 = min_f(524288, max_f(0, (this.fConst0 * this.fVslider31)));
		var fSlow32 = this.fVslider32;
		var fSlow33 = this.fVslider33;
		var fSlow34 = this.fVslider34;
		var fSlow35 = this.fVslider35;
		var fSlow36 = this.fVslider36;
		var fSlow37 = this.fVslider37;
		var fSlow38 = this.fVslider38;
		var fSlow39 = this.fVslider39;
		var fSlow40 = this.fVslider40;
		var iSlow41 = min_f(524288, max_f(0, (this.fConst0 * this.fVslider41)));
		var fSlow42 = this.fVslider42;
		var fSlow43 = this.fVslider43;
		var fSlow44 = this.fVslider44;
		var fSlow45 = this.fVslider45;
		var fSlow46 = this.fVslider46;
		var fSlow47 = this.fVslider47;
		var fSlow48 = this.fVslider48;
		var fSlow49 = this.fVslider49;
		var fSlow50 = this.fVslider50;
		var iSlow51 = min_f(524288, max_f(0, (this.fConst0 * this.fVslider51)));
		var fSlow52 = this.fVslider52;
		var fSlow53 = this.fVslider53;
		var fSlow54 = this.fVslider54;
		var fSlow55 = this.fVslider55;
		var fSlow56 = this.fVslider56;
		var fSlow57 = this.fVslider57;
		var fSlow58 = this.fVslider58;
		var fSlow59 = this.fVslider59;
		var fSlow60 = this.fVslider60;
		var iSlow61 = min_f(524288, max_f(0, (this.fConst0 * this.fVslider61)));
		var fSlow62 = this.fVslider62;
		var fSlow63 = this.fVslider63;
		var fSlow64 = this.fVslider64;
		var fSlow65 = this.fVslider65;
		var fSlow66 = this.fVslider66;
		var fSlow67 = this.fVslider67;
		var fSlow68 = this.fVslider68;
		var fSlow69 = this.fVslider69;
		var fSlow70 = this.fVslider70;
		var fSlow71 = this.fVslider71;
		var fSlow72 = this.fVslider72;
		var fSlow73 = this.fVslider73;
		var fSlow74 = this.fVslider74;
		var fSlow75 = this.fVslider75;
		var fSlow76 = this.fVslider76;
		var fSlow77 = this.fVslider77;
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			var fTemp1 = input1[i];
			this.fVec0[(this.IOTA & 1048575)] = (fSlow2 * ((((((((fSlow3 * this.fRec0[1]) + (fSlow4 * this.fRec1[1])) + (fSlow5 * this.fRec2[1])) + (fSlow6 * this.fRec3[1])) + (fSlow7 * this.fRec4[1])) + (fSlow8 * this.fRec5[1])) + (fSlow9 * fTemp0)) + (fSlow10 * fTemp1)));
			this.fRec0[0] = this.fVec0[((this.IOTA - iSlow11) & 1048575)];
			this.fVec1[(this.IOTA & 1048575)] = (fSlow12 * ((((((((fSlow13 * this.fRec0[1]) + (fSlow14 * this.fRec1[1])) + (fSlow15 * this.fRec2[1])) + (fSlow16 * this.fRec3[1])) + (fSlow17 * this.fRec4[1])) + (fSlow18 * this.fRec5[1])) + (fSlow19 * fTemp0)) + (fSlow20 * fTemp1)));
			this.fRec1[0] = this.fVec1[((this.IOTA - iSlow21) & 1048575)];
			this.fVec2[(this.IOTA & 1048575)] = (fSlow22 * ((((((((fSlow23 * this.fRec0[1]) + (fSlow24 * this.fRec1[1])) + (fSlow25 * this.fRec2[1])) + (fSlow26 * this.fRec3[1])) + (fSlow27 * this.fRec4[1])) + (fSlow28 * this.fRec5[1])) + (fSlow29 * fTemp0)) + (fSlow30 * fTemp1)));
			this.fRec2[0] = this.fVec2[((this.IOTA - iSlow31) & 1048575)];
			this.fVec3[(this.IOTA & 1048575)] = (fSlow32 * ((((((((fSlow33 * this.fRec0[1]) + (fSlow34 * this.fRec1[1])) + (fSlow35 * this.fRec2[1])) + (fSlow36 * this.fRec3[1])) + (fSlow37 * this.fRec4[1])) + (fSlow38 * this.fRec5[1])) + (fSlow39 * fTemp0)) + (fSlow40 * fTemp1)));
			this.fRec3[0] = this.fVec3[((this.IOTA - iSlow41) & 1048575)];
			this.fVec4[(this.IOTA & 1048575)] = (fSlow42 * ((((((((fSlow43 * this.fRec0[1]) + (fSlow44 * this.fRec1[1])) + (fSlow45 * this.fRec2[1])) + (fSlow46 * this.fRec3[1])) + (fSlow47 * this.fRec4[1])) + (fSlow48 * this.fRec5[1])) + (fSlow49 * fTemp0)) + (fSlow50 * fTemp1)));
			this.fRec4[0] = this.fVec4[((this.IOTA - iSlow51) & 1048575)];
			this.fVec5[(this.IOTA & 1048575)] = (fSlow52 * ((((((((fSlow53 * this.fRec0[1]) + (fSlow54 * this.fRec1[1])) + (fSlow55 * this.fRec2[1])) + (fSlow56 * this.fRec3[1])) + (fSlow57 * this.fRec4[1])) + (fSlow58 * this.fRec5[1])) + (fSlow59 * fTemp0)) + (fSlow60 * fTemp1)));
			this.fRec5[0] = this.fVec5[((this.IOTA - iSlow61) & 1048575)];
			output0[i] = (fSlow0 * ((((((((fSlow1 * this.fRec0[0]) + (fSlow62 * this.fRec1[0])) + (fSlow63 * this.fRec2[0])) + (fSlow64 * this.fRec3[0])) + (fSlow65 * this.fRec4[0])) + (fSlow66 * this.fRec5[0])) + (fSlow67 * fTemp0)) + (fSlow68 * fTemp1)));
			output1[i] = (fSlow69 * ((((((((fSlow70 * this.fRec0[0]) + (fSlow71 * this.fRec1[0])) + (fSlow72 * this.fRec2[0])) + (fSlow73 * this.fRec3[0])) + (fSlow74 * this.fRec4[0])) + (fSlow75 * this.fRec5[0])) + (fSlow76 * fTemp0)) + (fSlow77 * fTemp1)));
			this.IOTA = (this.IOTA + 1);
			this.fRec0[1] = this.fRec0[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec2[1] = this.fRec2[0];
			this.fRec3[1] = this.fRec3[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			
		}
		
	}
	
}

