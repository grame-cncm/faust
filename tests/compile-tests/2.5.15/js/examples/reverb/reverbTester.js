

function mydsp() {
	
	this.fButton0;
	this.fVec0 = new Float32Array(2);
	this.fCheckbox0;
	this.fButton1;
	this.fVec1 = new Float32Array(2);
	this.fCheckbox1;
	this.iRec1 = new Int32Array(2);
	this.fRec0 = new Float32Array(4);
	this.fButton2;
	this.fVec2 = new Float32Array(2);
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Handy test inputs for reverberator demos below.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "reverbTester");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("version", "0.0");
	}

	this.getNumInputs = function() {
		return 5;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
		var rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			case 1: {
				rate = 0;
				break;
			}
			case 2: {
				rate = 0;
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
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fButton0 = 0;
		this.fCheckbox0 = 0;
		this.fButton1 = 0;
		this.fCheckbox1 = 0;
		this.fButton2 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fVec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.iRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			this.fRec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fVec2[l4] = 0;
			
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
		ui_interface.openVerticalBox("reverbTester");
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Input Config");
		ui_interface.declare("fCheckbox0", "1", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the stereo external audio inputs are   disabled (good for hearing the impulse response or pink-noise response alone)");
		ui_interface.addCheckButton("Mute Ext Inputs", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "2", "");
		ui_interface.declare("fCheckbox1", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting   the EQ sections)");
		ui_interface.addCheckButton("Pink Noise", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Impulse Selection");
		ui_interface.declare("fButton1", "1", "");
		ui_interface.declare("fButton1", "tooltip", "Send impulse into LEFT channel");
		ui_interface.addButton("Left", function handler(obj) { function setval(val) { obj.fButton1 = val; } return setval; }(this));
		ui_interface.declare("fButton0", "2", "");
		ui_interface.declare("fButton0", "tooltip", "Send impulse into LEFT and RIGHT channels");
		ui_interface.addButton("Center", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.declare("fButton2", "3", "");
		ui_interface.declare("fButton2", "tooltip", "Send impulse into RIGHT channel");
		ui_interface.addButton("Right", function handler(obj) { function setval(val) { obj.fButton2 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var input1 = inputs[1];
		var input2 = inputs[2];
		var input3 = inputs[3];
		var input4 = inputs[4];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fButton0;
		var fSlow1 = (1 - this.fCheckbox0);
		var fSlow2 = this.fButton1;
		var fSlow3 = (0.1 * this.fCheckbox1);
		var fSlow4 = this.fButton2;
		for (var i = 0; (i < count); i = (i + 1)) {
			this.fVec0[0] = fSlow0;
			var iTemp0 = ((fSlow0 - this.fVec0[1]) > 0);
			this.fVec1[0] = fSlow2;
			this.iRec1[0] = ((1103515245 * this.iRec1[1]) + 12345);
			this.fRec0[0] = (((0.522189 * this.fRec0[3]) + ((4.65661e-10 * this.iRec1[0]) + (2.49496 * this.fRec0[1]))) - (2.01727 * this.fRec0[2]));
			var fTemp1 = (fSlow3 * (((0.049922 * this.fRec0[0]) + (0.0506127 * this.fRec0[2])) - ((0.0959935 * this.fRec0[1]) + (0.00440879 * this.fRec0[3]))));
			output0[i] = ((iTemp0 + ((fSlow1 * input3[i]) + ((fSlow2 - this.fVec1[1]) > 0))) + fTemp1);
			this.fVec2[0] = fSlow4;
			output1[i] = (((fSlow4 - this.fVec2[1]) > 0) + ((fSlow1 * input4[i]) + (iTemp0 + fTemp1)));
			this.fVec0[1] = this.fVec0[0];
			this.fVec1[1] = this.fVec1[0];
			this.iRec1[1] = this.iRec1[0];
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.fRec0[j0] = this.fRec0[(j0 - 1)];
				
			}
			this.fVec2[1] = this.fVec2[0];
			
		}
		
	}
	
}

