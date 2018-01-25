/* ------------------------------------------------------------
author: "JOS"
license: "STK-4.3"
name: "DNN"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "JOS");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("license", "STK-4.3");
		m.declare("name", "DNN");
	}

	int getNumInputs() {
		return 8;
		
	}
	int getNumOutputs() {
		return 8;
		
	}
	int getInputRate(int channel) {
		int rate;
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
	int getOutputRate(int channel) {
		int rate;
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
	
	public void classInit(int samplingFreq) {
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		
	}
	
	public void instanceResetUserInterface() {
		
	}
	
	public void instanceClear() {
		
	}
	
	public void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	public void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	public void buildUserInterface(UI ui_interface) {
		ui_interface.openVerticalBox("DNN");
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] input2 = inputs[2];
		float[] input3 = inputs[3];
		float[] input4 = inputs[4];
		float[] input5 = inputs[5];
		float[] input6 = inputs[6];
		float[] input7 = inputs[7];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float[] output4 = outputs[4];
		float[] output5 = outputs[5];
		float[] output6 = outputs[6];
		float[] output7 = outputs[7];
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input7[i];
			float fTemp1 = input6[i];
			float fTemp2 = input5[i];
			float fTemp3 = input4[i];
			float fTemp4 = input2[i];
			float fTemp5 = input1[i];
			float fTemp6 = input3[i];
			float fTemp7 = ((30.0f * fTemp0) + ((60.0f * fTemp1) + ((10.0f * fTemp2) + ((40.0f * fTemp3) + (((20.0f * fTemp4) + (50.0f * fTemp5)) + (70.0f * fTemp6))))));
			float fTemp8 = ((((fTemp7 > 0.0f))?1.f:0.f) * fTemp7);
			float fTemp9 = input0[i];
			float fTemp10 = ((43.0f * fTemp0) + (((23.0f * fTemp2) + ((53.0f * fTemp3) + ((3.0f * fTemp6) + ((33.0f * fTemp4) + ((13.0f * fTemp9) + (63.0f * fTemp5)))))) + (73.0f * fTemp1)));
			float fTemp11 = ((((fTemp10 > 0.0f))?1.f:0.f) * fTemp10);
			float fTemp12 = ((61.0f * fTemp0) + ((11.0f * fTemp1) + ((41.0f * fTemp2) + (((21.0f * fTemp6) + ((fTemp5 + (31.0f * fTemp9)) + (51.0f * fTemp4))) + (71.0f * fTemp3)))));
			float fTemp13 = ((((fTemp12 > 0.0f))?1.f:0.f) * fTemp12);
			float fTemp14 = (((24.0f * fTemp1) + ((54.0f * fTemp2) + ((4.0f * fTemp3) + ((34.0f * fTemp6) + (((14.0f * fTemp5) + (44.0f * fTemp9)) + (64.0f * fTemp4)))))) + (74.0f * fTemp0));
			float fTemp15 = (fTemp14 * (((fTemp14 > 0.0f))?1.f:0.f));
			float fTemp16 = ((12.0f * fTemp0) + ((42.0f * fTemp1) + (((22.0f * fTemp3) + ((52.0f * fTemp6) + ((2.0f * fTemp4) + ((32.0f * fTemp5) + (62.0f * fTemp9))))) + (72.0f * fTemp2))));
			float fTemp17 = ((((fTemp16 > 0.0f))?1.f:0.f) * fTemp16);
			float fTemp18 = (((((100.0f * fTemp8) + (110.0f * fTemp11)) + (120.0f * fTemp13)) + (130.0f * fTemp15)) + (140.0f * fTemp17));
			output0[i] = (fTemp18 * (((fTemp18 > 0.0f))?1.f:0.f));
			float fTemp19 = ((121.0f * fTemp17) + ((111.0f * fTemp15) + ((101.0f * fTemp13) + ((131.0f * fTemp8) + (141.0f * fTemp11)))));
			output1[i] = ((((fTemp19 > 0.0f))?1.f:0.f) * fTemp19);
			float fTemp20 = ((102.0f * fTemp17) + ((((112.0f * fTemp8) + (122.0f * fTemp11)) + (132.0f * fTemp13)) + (142.0f * fTemp15)));
			output2[i] = ((((fTemp20 > 0.0f))?1.f:0.f) * fTemp20);
			float fTemp21 = ((133.0f * fTemp17) + ((123.0f * fTemp15) + ((113.0f * fTemp13) + ((103.0f * fTemp11) + (143.0f * fTemp8)))));
			output3[i] = ((((fTemp21 > 0.0f))?1.f:0.f) * fTemp21);
			float fTemp22 = ((114.0f * fTemp17) + ((104.0f * fTemp15) + (((124.0f * fTemp8) + (134.0f * fTemp11)) + (144.0f * fTemp13))));
			output4[i] = ((((fTemp22 > 0.0f))?1.f:0.f) * fTemp22);
			float fTemp23 = (((((105.0f * fTemp8) + (115.0f * fTemp11)) + (125.0f * fTemp13)) + (135.0f * fTemp15)) + (145.0f * fTemp17));
			output5[i] = (fTemp23 * (((fTemp23 > 0.0f))?1.f:0.f));
			float fTemp24 = ((126.0f * fTemp17) + ((116.0f * fTemp15) + ((106.0f * fTemp13) + ((136.0f * fTemp8) + (146.0f * fTemp11)))));
			output6[i] = ((((fTemp24 > 0.0f))?1.f:0.f) * fTemp24);
			float fTemp25 = ((107.0f * fTemp17) + ((((117.0f * fTemp8) + (127.0f * fTemp11)) + (137.0f * fTemp13)) + (147.0f * fTemp15)));
			output7[i] = ((((fTemp25 > 0.0f))?1.f:0.f) * fTemp25);
			
		}
		
	}
	
};

