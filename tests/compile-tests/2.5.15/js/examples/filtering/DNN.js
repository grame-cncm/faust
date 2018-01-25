

function mydsp() {
	
	this.fSamplingFreq;
	
	this.metadata = function(m) { 
		m.declare("author", "JOS");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("license", "STK-4.3");
		m.declare("name", "DNN");
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
		ui_interface.openVerticalBox("DNN");
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
			var fTemp0 = input7[i];
			var fTemp1 = input6[i];
			var fTemp2 = input5[i];
			var fTemp3 = input4[i];
			var fTemp4 = input2[i];
			var fTemp5 = input1[i];
			var fTemp6 = input3[i];
			var fTemp7 = ((30 * fTemp0) + ((60 * fTemp1) + ((10 * fTemp2) + ((40 * fTemp3) + (((20 * fTemp4) + (50 * fTemp5)) + (70 * fTemp6))))));
			var fTemp8 = ((fTemp7 > 0) * fTemp7);
			var fTemp9 = input0[i];
			var fTemp10 = ((43 * fTemp0) + (((23 * fTemp2) + ((53 * fTemp3) + ((3 * fTemp6) + ((33 * fTemp4) + ((13 * fTemp9) + (63 * fTemp5)))))) + (73 * fTemp1)));
			var fTemp11 = ((fTemp10 > 0) * fTemp10);
			var fTemp12 = ((61 * fTemp0) + ((11 * fTemp1) + ((41 * fTemp2) + (((21 * fTemp6) + ((fTemp5 + (31 * fTemp9)) + (51 * fTemp4))) + (71 * fTemp3)))));
			var fTemp13 = ((fTemp12 > 0) * fTemp12);
			var fTemp14 = (((24 * fTemp1) + ((54 * fTemp2) + ((4 * fTemp3) + ((34 * fTemp6) + (((14 * fTemp5) + (44 * fTemp9)) + (64 * fTemp4)))))) + (74 * fTemp0));
			var fTemp15 = (fTemp14 * (fTemp14 > 0));
			var fTemp16 = ((12 * fTemp0) + ((42 * fTemp1) + (((22 * fTemp3) + ((52 * fTemp6) + ((2 * fTemp4) + ((32 * fTemp5) + (62 * fTemp9))))) + (72 * fTemp2))));
			var fTemp17 = ((fTemp16 > 0) * fTemp16);
			var fTemp18 = (((((100 * fTemp8) + (110 * fTemp11)) + (120 * fTemp13)) + (130 * fTemp15)) + (140 * fTemp17));
			output0[i] = (fTemp18 * (fTemp18 > 0));
			var fTemp19 = ((121 * fTemp17) + ((111 * fTemp15) + ((101 * fTemp13) + ((131 * fTemp8) + (141 * fTemp11)))));
			output1[i] = ((fTemp19 > 0) * fTemp19);
			var fTemp20 = ((102 * fTemp17) + ((((112 * fTemp8) + (122 * fTemp11)) + (132 * fTemp13)) + (142 * fTemp15)));
			output2[i] = ((fTemp20 > 0) * fTemp20);
			var fTemp21 = ((133 * fTemp17) + ((123 * fTemp15) + ((113 * fTemp13) + ((103 * fTemp11) + (143 * fTemp8)))));
			output3[i] = ((fTemp21 > 0) * fTemp21);
			var fTemp22 = ((114 * fTemp17) + ((104 * fTemp15) + (((124 * fTemp8) + (134 * fTemp11)) + (144 * fTemp13))));
			output4[i] = ((fTemp22 > 0) * fTemp22);
			var fTemp23 = (((((105 * fTemp8) + (115 * fTemp11)) + (125 * fTemp13)) + (135 * fTemp15)) + (145 * fTemp17));
			output5[i] = (fTemp23 * (fTemp23 > 0));
			var fTemp24 = ((126 * fTemp17) + ((116 * fTemp15) + ((106 * fTemp13) + ((136 * fTemp8) + (146 * fTemp11)))));
			output6[i] = ((fTemp24 > 0) * fTemp24);
			var fTemp25 = ((107 * fTemp17) + ((((117 * fTemp8) + (127 * fTemp11)) + (137 * fTemp13)) + (147 * fTemp15)));
			output7[i] = ((fTemp25 > 0) * fTemp25);
			
		}
		
	}
	
}

