/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "capture"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fButton0;
	int IOTA;
	float fVec0[] = new float[1048576];
	int iVec1[] = new int[2];
	int iRec1[] = new int[2];
	float fRec0[] = new float[2];
	float fHslider0;
	float fRec2[] = new float[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("name", "capture");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
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
		fButton0 = (float)0.0f;
		fHslider0 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 1048576); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec1[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec1[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
			
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
		ui_interface.openVerticalBox("Audio Capture");
		ui_interface.addButton("Capture", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.addHorizontalSlider("level (db)", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, -96.0f, 4.0f, 0.100000001f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = fButton0;
		float fSlow1 = (1.0f - fSlow0);
		int iSlow2 = (int)fSlow0;
		float fSlow3 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider0)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[(IOTA & 1048575)] = ((fSlow1 * fRec0[1]) + (fSlow0 * input0[i]));
			iVec1[0] = iSlow2;
			iRec1[0] = ((iSlow2 + iRec1[1]) * ((((iSlow2 - iVec1[1]) <= 0))?1:0));
			fRec0[0] = fVec0[((IOTA - java.lang.Math.min(524288, java.lang.Math.max(0, (iRec1[0] + -1)))) & 1048575)];
			fRec2[0] = (fSlow3 + (0.999000013f * fRec2[1]));
			output0[i] = (fRec0[0] * fRec2[0]);
			IOTA = (IOTA + 1);
			iVec1[1] = iVec1[0];
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			
		}
		
	}
	
};

