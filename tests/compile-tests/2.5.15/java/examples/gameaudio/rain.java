/* ------------------------------------------------------------
name: "rain"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fHslider0;
	int iRec0[] = new int[2];
	float fVec0[] = new float[2];
	float fHslider1;
	float fVec1[] = new float[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "rain");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		fHslider0 = (float)0.5f;
		fHslider1 = (float)300.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
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
		ui_interface.openVerticalBox("rain");
		ui_interface.addHorizontalSlider("density", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 300.0f, 0.0f, 1000.0f, 1.0f);
		ui_interface.addHorizontalSlider("volume", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (0.00100000005f * fHslider1);
		for (int i = 0; (i < count); i = (i + 1)) {
			int iTemp0 = (1103515245 * (iRec0[1] + 12345));
			iRec0[0] = (1103515245 * (iTemp0 + 12345));
			int iRec1 = iTemp0;
			float fTemp1 = (4.65661287e-10f * (float)iRec0[0]);
			fVec0[0] = fTemp1;
			output0[i] = (fSlow0 * (fVec0[1] * ((((float)java.lang.Math.abs(fTemp1) < fSlow1))?1.f:0.f)));
			float fTemp2 = (4.65661287e-10f * (float)iRec1);
			fVec1[0] = fTemp2;
			output1[i] = (fSlow0 * (fVec1[1] * ((((float)java.lang.Math.abs(fTemp2) < fSlow1))?1.f:0.f)));
			iRec0[1] = iRec0[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			
		}
		
	}
	
};

