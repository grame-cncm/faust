/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "lfboost"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	int fSamplingFreq;
	float fConst0;
	float fEntry0;
	float fVslider0;
	float fRec0[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "lfboost");
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
		fConst0 = (3.14159274f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fEntry0 = (float)100.0f;
		fVslider0 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
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
		ui_interface.openVerticalBox("lowboost");
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.declare("fEntry0", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry0"; }
				public void set(float val) { fEntry0 = val; }
				public float get() { return (float)fEntry0; }
			}
			, 100.0f, 20.0f, 150.0f, 1.0f);
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.0f, -20.0f, 20.0f, 0.100000001f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = (float)java.lang.Math.tan((fConst0 * fEntry0));
		float fSlow1 = (1.0f / ((fSlow0 * (fSlow0 + 1.41421354f)) + 1.0f));
		float fSlow2 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0));
		float fSlow3 = mydsp_faustpower2_f(fSlow0);
		float fSlow4 = (2.0f * ((fSlow2 * fSlow3) + -1.0f));
		float fSlow5 = ((fSlow0 * (fSlow0 + -1.41421354f)) + 1.0f);
		float fSlow6 = (2.0f * (fSlow3 + -1.0f));
		float fSlow7 = (float)java.lang.Math.sqrt((2.0f * fSlow2));
		float fSlow8 = (fSlow2 * fSlow0);
		float fSlow9 = ((fSlow0 * (fSlow7 + fSlow8)) + 1.0f);
		float fSlow10 = (1.0f - (fSlow0 * (fSlow7 - fSlow8)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (input0[i] - (fSlow1 * ((fSlow5 * fRec0[2]) + (fSlow6 * fRec0[1]))));
			output0[i] = (fSlow1 * (((fSlow4 * fRec0[1]) + (fSlow9 * fRec0[0])) + (fSlow10 * fRec0[2])));
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

