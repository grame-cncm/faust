/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "pitchShifter"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int IOTA;
	float fVec0[] = new float[131072];
	float fHslider0;
	float fHslider1;
	float fRec0[] = new float[2];
	float fHslider2;
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
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
		m.declare("name", "pitchShifter");
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
		fHslider0 = (float)1000.0f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)10.0f;
		
	}
	
	public void instanceClear() {
		IOTA = 0;
		for (int l0 = 0; (l0 < 131072); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
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
		ui_interface.openVerticalBox("Pitch Shifter");
		ui_interface.addHorizontalSlider("shift (semitones)", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, -12.0f, 12.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("window (samples)", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 1000.0f, 50.0f, 10000.0f, 1.0f);
		ui_interface.addHorizontalSlider("xfade (samples)", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 10.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = fHslider0;
		float fSlow1 = (float)java.lang.Math.pow(2.0f, (0.0833333358f * fHslider1));
		float fSlow2 = (1.0f / fHslider2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fVec0[(IOTA & 131071)] = fTemp0;
			fRec0[0] = (float)java.lang.Math.IEEEremainder((fSlow0 + ((fRec0[1] + 1.0f) - fSlow1)), fSlow0);
			int iTemp1 = (int)fRec0[0];
			float fTemp2 = (float)java.lang.Math.floor(fRec0[0]);
			float fTemp3 = (1.0f - fRec0[0]);
			float fTemp4 = (float)java.lang.Math.min((fSlow2 * fRec0[0]), 1.0f);
			float fTemp5 = (fSlow0 + fRec0[0]);
			int iTemp6 = (int)fTemp5;
			float fTemp7 = (float)java.lang.Math.floor(fTemp5);
			output0[i] = ((((fVec0[((IOTA - java.lang.Math.min(65537, java.lang.Math.max(0, iTemp1))) & 131071)] * (fTemp2 + fTemp3)) + ((fRec0[0] - fTemp2) * fVec0[((IOTA - java.lang.Math.min(65537, java.lang.Math.max(0, (iTemp1 + 1)))) & 131071)])) * fTemp4) + (((fVec0[((IOTA - java.lang.Math.min(65537, java.lang.Math.max(0, iTemp6))) & 131071)] * ((fTemp7 + fTemp3) - fSlow0)) + ((fSlow0 + (fRec0[0] - fTemp7)) * fVec0[((IOTA - java.lang.Math.min(65537, java.lang.Math.max(0, (iTemp6 + 1)))) & 131071)])) * (1.0f - fTemp4)));
			IOTA = (IOTA + 1);
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

