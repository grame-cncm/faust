/* ------------------------------------------------------------
name: "shortdelays2"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fVec0[] = new float[8];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "shortdelays2");
	}

	int getNumInputs() {
		return 1;
		
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
		for (int l0 = 0; (l0 < 8); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
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
		ui_interface.openVerticalBox("shortdelays2");
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fVec0[0] = fTemp0;
			output0[i] = (((fVec0[4] + (0.5f * fVec0[5])) + (0.333333343f * fVec0[6])) + (0.25f * fVec0[7]));
			for (int j0 = 7; (j0 > 0); j0 = (j0 - 1)) {
				fVec0[j0] = fVec0[(j0 - 1)];
				
			}
			
		}
		
	}
	
};

