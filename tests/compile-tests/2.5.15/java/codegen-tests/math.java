/* ------------------------------------------------------------
name: "math"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float rintf(float dummy0);
float remainderf(float dummy0, float dummy1);

	int iRec0[] = new int[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("math.lib/author", "GRAME");
		m.declare("math.lib/copyright", "GRAME");
		m.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("math.lib/license", "LGPL with exception");
		m.declare("math.lib/name", "Math Library");
		m.declare("math.lib/version", "1.0");
		m.declare("music.lib/author", "GRAME");
		m.declare("music.lib/copyright", "GRAME");
		m.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m.declare("music.lib/license", "LGPL with exception");
		m.declare("music.lib/name", "Music Library");
		m.declare("music.lib/version", "1.0");
		m.declare("name", "math");
	}

	int getNumInputs() {
		return 6;
		
	}
	int getNumOutputs() {
		return 1;
		
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
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
			
		}
		
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
		ui_interface.openVerticalBox("math");
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] input2 = inputs[2];
		float[] input3 = inputs[3];
		float[] input4 = inputs[4];
		float[] input5 = inputs[5];
		float[] output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			int iTemp0 = (iRec0[0] + -1);
			output0[i] = ((float)java.lang.Math.sqrt((float)iTemp0) + ((float)java.lang.Math.tan((float)iTemp0) + (rintf((float)iTemp0) + ((float)java.lang.Math.sin((float)iTemp0) + (remainderf((float)iTemp0, input5[i]) + ((float)java.lang.Math.pow(input4[i], (float)iTemp0) + ((float)java.lang.Math.min((float)iTemp0, input3[i]) + ((float)java.lang.Math.log((float)iTemp0) + ((float)java.lang.Math.log10((float)iTemp0) + ((((((((((float)java.lang.Math.abs(iTemp0) + (float)java.lang.Math.asin((float)iTemp0)) + (float)java.lang.Math.atan2((float)iTemp0, input0[i])) + (float)java.lang.Math.atan((float)iTemp0)) + (float)java.lang.Math.ceil((float)iTemp0)) + (float)java.lang.Math.cos((float)iTemp0)) + (float)java.lang.Math.exp((float)iTemp0)) + (float)java.lang.Math.floor((float)iTemp0)) + (float)java.lang.Math.IEEEremainder((float)iTemp0, input1[i])) + (float)java.lang.Math.max((float)iTemp0, input2[i])))))))))));
			iRec0[1] = iRec0[0];
			
		}
		
	}
	
};

