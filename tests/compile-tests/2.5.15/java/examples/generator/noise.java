/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2009"
license: "BSD"
name: "Noise"
version: "1.1"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fVslider0;
	int iRec0[] = new int[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("copyright", "(c)GRAME 2009");
		m.declare("license", "BSD");
		m.declare("name", "Noise");
		m.declare("version", "1.1");
	}

	int getNumInputs() {
		return 0;
		
	}
	int getNumOutputs() {
		return 1;
		
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
		fVslider0 = (float)0.5f;
		
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
		ui_interface.openVerticalBox("Noise");
		ui_interface.declare("fVslider0", "acc", "0 0 -10 0 10");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.addVerticalSlider("Volume", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float fSlow0 = (4.65661287e-10f * fVslider0);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = ((1103515245 * iRec0[1]) + 12345);
			output0[i] = (fSlow0 * (float)iRec0[0]);
			iRec0[1] = iRec0[0];
			
		}
		
	}
	
};

