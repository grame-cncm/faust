/* ------------------------------------------------------------
name: "parabolic-env5"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int iRec0[] = new int[2];
	int iVec0[] = new int[2];
	float fRec3[] = new float[2];
	float fRec2[] = new float[2];
	float fRec1[] = new float[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "parabolic-env5");
	}

	int getNumInputs() {
		return 0;
		
	}
	int getNumOutputs() {
		return 3;
		
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
			case 2: {
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
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
			
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
		ui_interface.openVerticalBox("parabolic-env5");
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			output0[i] = (float)iRec0[1];
			int iTemp0 = ((iRec0[1] % 7) == 0);
			iVec0[0] = iTemp0;
			output1[i] = (float)iTemp0;
			int iTemp1 = (((((fRec1[1] > 0.0f))?1:0) | iTemp0) | iVec0[1]);
			fRec3[0] = ((fRec3[1] + -0.224000007f) * (float)iTemp1);
			fRec2[0] = ((float)iTemp1 * ((fRec2[1] + fRec3[1]) + 1.00800002f));
			fRec1[0] = (float)java.lang.Math.max(0.0f, fRec2[1]);
			output2[i] = fRec1[0];
			iRec0[1] = iRec0[0];
			iVec0[1] = iVec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}
	
};

