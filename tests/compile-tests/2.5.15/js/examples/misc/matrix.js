

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
	this.fVslider11;
	this.fVslider12;
	this.fVslider13;
	this.fVslider14;
	this.fVslider15;
	this.fVslider16;
	this.fVslider17;
	this.fVslider18;
	this.fVslider19;
	this.fVslider20;
	this.fVslider21;
	this.fVslider22;
	this.fVslider23;
	this.fVslider24;
	this.fVslider25;
	this.fVslider26;
	this.fVslider27;
	this.fVslider28;
	this.fVslider29;
	this.fVslider30;
	this.fVslider31;
	this.fVslider32;
	this.fVslider33;
	this.fVslider34;
	this.fVslider35;
	this.fVslider36;
	this.fVslider37;
	this.fVslider38;
	this.fVslider39;
	this.fVslider40;
	this.fVslider41;
	this.fVslider42;
	this.fVslider43;
	this.fVslider44;
	this.fVslider45;
	this.fVslider46;
	this.fVslider47;
	this.fVslider48;
	this.fVslider49;
	this.fVslider50;
	this.fVslider51;
	this.fVslider52;
	this.fVslider53;
	this.fVslider54;
	this.fVslider55;
	this.fVslider56;
	this.fVslider57;
	this.fVslider58;
	this.fVslider59;
	this.fVslider60;
	this.fVslider61;
	this.fVslider62;
	this.fVslider63;
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("name", "matrix");
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fVslider0 = -10;
		this.fVslider1 = -10;
		this.fVslider2 = -10;
		this.fVslider3 = -10;
		this.fVslider4 = -10;
		this.fVslider5 = -10;
		this.fVslider6 = -10;
		this.fVslider7 = -10;
		this.fVslider8 = -10;
		this.fVslider9 = -10;
		this.fVslider10 = -10;
		this.fVslider11 = -10;
		this.fVslider12 = -10;
		this.fVslider13 = -10;
		this.fVslider14 = -10;
		this.fVslider15 = -10;
		this.fVslider16 = -10;
		this.fVslider17 = -10;
		this.fVslider18 = -10;
		this.fVslider19 = -10;
		this.fVslider20 = -10;
		this.fVslider21 = -10;
		this.fVslider22 = -10;
		this.fVslider23 = -10;
		this.fVslider24 = -10;
		this.fVslider25 = -10;
		this.fVslider26 = -10;
		this.fVslider27 = -10;
		this.fVslider28 = -10;
		this.fVslider29 = -10;
		this.fVslider30 = -10;
		this.fVslider31 = -10;
		this.fVslider32 = -10;
		this.fVslider33 = -10;
		this.fVslider34 = -10;
		this.fVslider35 = -10;
		this.fVslider36 = -10;
		this.fVslider37 = -10;
		this.fVslider38 = -10;
		this.fVslider39 = -10;
		this.fVslider40 = -10;
		this.fVslider41 = -10;
		this.fVslider42 = -10;
		this.fVslider43 = -10;
		this.fVslider44 = -10;
		this.fVslider45 = -10;
		this.fVslider46 = -10;
		this.fVslider47 = -10;
		this.fVslider48 = -10;
		this.fVslider49 = -10;
		this.fVslider50 = -10;
		this.fVslider51 = -10;
		this.fVslider52 = -10;
		this.fVslider53 = -10;
		this.fVslider54 = -10;
		this.fVslider55 = -10;
		this.fVslider56 = -10;
		this.fVslider57 = -10;
		this.fVslider58 = -10;
		this.fVslider59 = -10;
		this.fVslider60 = -10;
		this.fVslider61 = -10;
		this.fVslider62 = -10;
		this.fVslider63 = -10;
		
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
		ui_interface.openTabBox("Matrix 8 x 8");
		ui_interface.openHorizontalBox("Output 0");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 1");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider10 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider11 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider12 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider13 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider14 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider15 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 2");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider16 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider17 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider18 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider19 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider20 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider21 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider22 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider23 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 3");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider24 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider25 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider26 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider27 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider28 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider29 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider30 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider31 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 4");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider32 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider33 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider34 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider35 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider36 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider37 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider38 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider39 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 5");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider40 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider41 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider42 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider43 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider44 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider45 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider46 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider47 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 6");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider48 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider49 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider50 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider51 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider52 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider53 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider54 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider55 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("Output 7");
		ui_interface.addVerticalSlider("Input 0", function handler(obj) { function setval(val) { obj.fVslider56 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 1", function handler(obj) { function setval(val) { obj.fVslider57 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 2", function handler(obj) { function setval(val) { obj.fVslider58 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 3", function handler(obj) { function setval(val) { obj.fVslider59 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 4", function handler(obj) { function setval(val) { obj.fVslider60 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 5", function handler(obj) { function setval(val) { obj.fVslider61 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 6", function handler(obj) { function setval(val) { obj.fVslider62 = val; } return setval; }(this), -10, -96, 4, 0.1);
		ui_interface.addVerticalSlider("Input 7", function handler(obj) { function setval(val) { obj.fVslider63 = val; } return setval; }(this), -10, -96, 4, 0.1);
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
		var fSlow0 = Math.pow(10, (0.05 * this.fVslider0));
		var fSlow1 = Math.pow(10, (0.05 * this.fVslider1));
		var fSlow2 = Math.pow(10, (0.05 * this.fVslider2));
		var fSlow3 = Math.pow(10, (0.05 * this.fVslider3));
		var fSlow4 = Math.pow(10, (0.05 * this.fVslider4));
		var fSlow5 = Math.pow(10, (0.05 * this.fVslider5));
		var fSlow6 = Math.pow(10, (0.05 * this.fVslider6));
		var fSlow7 = Math.pow(10, (0.05 * this.fVslider7));
		var fSlow8 = Math.pow(10, (0.05 * this.fVslider8));
		var fSlow9 = Math.pow(10, (0.05 * this.fVslider9));
		var fSlow10 = Math.pow(10, (0.05 * this.fVslider10));
		var fSlow11 = Math.pow(10, (0.05 * this.fVslider11));
		var fSlow12 = Math.pow(10, (0.05 * this.fVslider12));
		var fSlow13 = Math.pow(10, (0.05 * this.fVslider13));
		var fSlow14 = Math.pow(10, (0.05 * this.fVslider14));
		var fSlow15 = Math.pow(10, (0.05 * this.fVslider15));
		var fSlow16 = Math.pow(10, (0.05 * this.fVslider16));
		var fSlow17 = Math.pow(10, (0.05 * this.fVslider17));
		var fSlow18 = Math.pow(10, (0.05 * this.fVslider18));
		var fSlow19 = Math.pow(10, (0.05 * this.fVslider19));
		var fSlow20 = Math.pow(10, (0.05 * this.fVslider20));
		var fSlow21 = Math.pow(10, (0.05 * this.fVslider21));
		var fSlow22 = Math.pow(10, (0.05 * this.fVslider22));
		var fSlow23 = Math.pow(10, (0.05 * this.fVslider23));
		var fSlow24 = Math.pow(10, (0.05 * this.fVslider24));
		var fSlow25 = Math.pow(10, (0.05 * this.fVslider25));
		var fSlow26 = Math.pow(10, (0.05 * this.fVslider26));
		var fSlow27 = Math.pow(10, (0.05 * this.fVslider27));
		var fSlow28 = Math.pow(10, (0.05 * this.fVslider28));
		var fSlow29 = Math.pow(10, (0.05 * this.fVslider29));
		var fSlow30 = Math.pow(10, (0.05 * this.fVslider30));
		var fSlow31 = Math.pow(10, (0.05 * this.fVslider31));
		var fSlow32 = Math.pow(10, (0.05 * this.fVslider32));
		var fSlow33 = Math.pow(10, (0.05 * this.fVslider33));
		var fSlow34 = Math.pow(10, (0.05 * this.fVslider34));
		var fSlow35 = Math.pow(10, (0.05 * this.fVslider35));
		var fSlow36 = Math.pow(10, (0.05 * this.fVslider36));
		var fSlow37 = Math.pow(10, (0.05 * this.fVslider37));
		var fSlow38 = Math.pow(10, (0.05 * this.fVslider38));
		var fSlow39 = Math.pow(10, (0.05 * this.fVslider39));
		var fSlow40 = Math.pow(10, (0.05 * this.fVslider40));
		var fSlow41 = Math.pow(10, (0.05 * this.fVslider41));
		var fSlow42 = Math.pow(10, (0.05 * this.fVslider42));
		var fSlow43 = Math.pow(10, (0.05 * this.fVslider43));
		var fSlow44 = Math.pow(10, (0.05 * this.fVslider44));
		var fSlow45 = Math.pow(10, (0.05 * this.fVslider45));
		var fSlow46 = Math.pow(10, (0.05 * this.fVslider46));
		var fSlow47 = Math.pow(10, (0.05 * this.fVslider47));
		var fSlow48 = Math.pow(10, (0.05 * this.fVslider48));
		var fSlow49 = Math.pow(10, (0.05 * this.fVslider49));
		var fSlow50 = Math.pow(10, (0.05 * this.fVslider50));
		var fSlow51 = Math.pow(10, (0.05 * this.fVslider51));
		var fSlow52 = Math.pow(10, (0.05 * this.fVslider52));
		var fSlow53 = Math.pow(10, (0.05 * this.fVslider53));
		var fSlow54 = Math.pow(10, (0.05 * this.fVslider54));
		var fSlow55 = Math.pow(10, (0.05 * this.fVslider55));
		var fSlow56 = Math.pow(10, (0.05 * this.fVslider56));
		var fSlow57 = Math.pow(10, (0.05 * this.fVslider57));
		var fSlow58 = Math.pow(10, (0.05 * this.fVslider58));
		var fSlow59 = Math.pow(10, (0.05 * this.fVslider59));
		var fSlow60 = Math.pow(10, (0.05 * this.fVslider60));
		var fSlow61 = Math.pow(10, (0.05 * this.fVslider61));
		var fSlow62 = Math.pow(10, (0.05 * this.fVslider62));
		var fSlow63 = Math.pow(10, (0.05 * this.fVslider63));
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			var fTemp1 = input1[i];
			var fTemp2 = input2[i];
			var fTemp3 = input3[i];
			var fTemp4 = input4[i];
			var fTemp5 = input5[i];
			var fTemp6 = input6[i];
			var fTemp7 = input7[i];
			output0[i] = ((((((((fSlow0 * fTemp0) + (fSlow1 * fTemp1)) + (fSlow2 * fTemp2)) + (fSlow3 * fTemp3)) + (fSlow4 * fTemp4)) + (fSlow5 * fTemp5)) + (fSlow6 * fTemp6)) + (fSlow7 * fTemp7));
			output1[i] = ((((((((fSlow8 * fTemp0) + (fSlow9 * fTemp1)) + (fSlow10 * fTemp2)) + (fSlow11 * fTemp3)) + (fSlow12 * fTemp4)) + (fSlow13 * fTemp5)) + (fSlow14 * fTemp6)) + (fSlow15 * fTemp7));
			output2[i] = ((((((((fSlow16 * fTemp0) + (fSlow17 * fTemp1)) + (fSlow18 * fTemp2)) + (fSlow19 * fTemp3)) + (fSlow20 * fTemp4)) + (fSlow21 * fTemp5)) + (fSlow22 * fTemp6)) + (fSlow23 * fTemp7));
			output3[i] = ((((((((fSlow24 * fTemp0) + (fSlow25 * fTemp1)) + (fSlow26 * fTemp2)) + (fSlow27 * fTemp3)) + (fSlow28 * fTemp4)) + (fSlow29 * fTemp5)) + (fSlow30 * fTemp6)) + (fSlow31 * fTemp7));
			output4[i] = ((((((((fSlow32 * fTemp0) + (fSlow33 * fTemp1)) + (fSlow34 * fTemp2)) + (fSlow35 * fTemp3)) + (fSlow36 * fTemp4)) + (fSlow37 * fTemp5)) + (fSlow38 * fTemp6)) + (fSlow39 * fTemp7));
			output5[i] = ((((((((fSlow40 * fTemp0) + (fSlow41 * fTemp1)) + (fSlow42 * fTemp2)) + (fSlow43 * fTemp3)) + (fSlow44 * fTemp4)) + (fSlow45 * fTemp5)) + (fSlow46 * fTemp6)) + (fSlow47 * fTemp7));
			output6[i] = ((((((((fSlow48 * fTemp0) + (fSlow49 * fTemp1)) + (fSlow50 * fTemp2)) + (fSlow51 * fTemp3)) + (fSlow52 * fTemp4)) + (fSlow53 * fTemp5)) + (fSlow54 * fTemp6)) + (fSlow55 * fTemp7));
			output7[i] = ((((((((fSlow56 * fTemp0) + (fSlow57 * fTemp1)) + (fSlow58 * fTemp2)) + (fSlow59 * fTemp3)) + (fSlow60 * fTemp4)) + (fSlow61 * fTemp5)) + (fSlow62 * fTemp6)) + (fSlow63 * fTemp7));
			
		}
		
	}
	
}

