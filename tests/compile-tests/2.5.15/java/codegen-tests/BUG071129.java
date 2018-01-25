/* ------------------------------------------------------------
name: "BUG071129"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fRec4[] = new float[2];
	float fRec2[] = new float[2];
	float fRec5[] = new float[2];
	float fRec3[] = new float[2];
	float fRec0[] = new float[2];
	float fRec1[] = new float[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "BUG071129");
	}

	int getNumInputs() {
		return 0;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
			fRec4[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec5[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec0[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec1[l5] = 0.0f;
			
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
		ui_interface.openVerticalBox("BUG071129");
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec4[0] = ((float)java.lang.Math.sqrt(fRec4[1]) + fRec0[1]);
			fRec2[0] = ((fRec4[0] + (0.899999976f * fRec2[1])) + (0.100000001f * fRec3[1]));
			fRec5[0] = ((float)java.lang.Math.sin(fRec5[1]) + fRec1[1]);
			fRec3[0] = ((fRec5[0] + (0.200000003f * fRec2[1])) - (0.800000012f * fRec3[1]));
			fRec0[0] = (11.0f * fRec2[0]);
			fRec1[0] = (13.0f * fRec3[0]);
			output0[i] = fRec0[0];
			output1[i] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}
	
};

