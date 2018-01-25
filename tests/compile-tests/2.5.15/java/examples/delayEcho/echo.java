/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "echo"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fHslider1;
	int IOTA;
	float fRec0[] = new float[131072];
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "echo");
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
		fConst0 = (0.00100000005f * (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.0f;
		fHslider1 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
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
		ui_interface.openVerticalBox("echo-simple");
		ui_interface.openVerticalBox("echo  1000");
		ui_interface.addHorizontalSlider("feedback", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 100.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("millisecond", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1000.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = (0.00999999978f * fHslider0);
		int iSlow1 = (java.lang.Math.min(65536, java.lang.Math.max(0, ((int)(fConst0 * fHslider1) + -1))) + 1);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[(IOTA & 131071)] = (input0[i] + (fSlow0 * fRec0[((IOTA - iSlow1) & 131071)]));
			output0[i] = fRec0[((IOTA - 0) & 131071)];
			IOTA = (IOTA + 1);
			
		}
		
	}
	
};

