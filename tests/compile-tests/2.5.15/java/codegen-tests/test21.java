/* ------------------------------------------------------------
name: "test21"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int IOTA;
	float fVec0[] = new float[1024];
	float fHslider0;
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "test21");
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
		fHslider0 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 1024); l0 = (l0 + 1)) {
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
		ui_interface.openVerticalBox("test21");
		ui_interface.addHorizontalSlider("delay", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 1000.0f, 1.0f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		int iSlow0 = (int)fHslider0;
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[(IOTA & 1023)] = input0[i];
			output0[i] = fVec0[((IOTA - iSlow0) & 1023)];
			IOTA = (IOTA + 1);
			
		}
		
	}
	
};

