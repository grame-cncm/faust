/* ------------------------------------------------------------
name: "lowShelf"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fHslider1;
	float fHslider2;
	float fRec0[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("maxmsp.lib/author", "GRAME");
		m.declare("maxmsp.lib/copyright", "GRAME");
		m.declare("maxmsp.lib/license", "LGPL");
		m.declare("maxmsp.lib/name", "MaxMSP compatibility Library");
		m.declare("maxmsp.lib/version", "1.1");
		m.declare("name", "lowShelf");
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
		fConst0 = (6.28318548f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.0f;
		fHslider1 = (float)1000.0f;
		fHslider2 = (float)1.0f;
		
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
		ui_interface.openVerticalBox("lowShelf");
		ui_interface.addHorizontalSlider("Freq", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 1000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Gain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, -10.0f, 10.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("Q", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 1.0f, 0.00999999978f, 100.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = (float)java.lang.Math.pow(10.0f, (0.0250000004f * fHslider0));
		float fSlow1 = (fConst0 * (float)java.lang.Math.max(0.0f, fHslider1));
		float fSlow2 = (float)java.lang.Math.cos(fSlow1);
		float fSlow3 = ((fSlow0 + -1.0f) * fSlow2);
		float fSlow4 = (fSlow0 + fSlow3);
		float fSlow5 = (((float)java.lang.Math.sqrt(fSlow0) * (float)java.lang.Math.sin(fSlow1)) / (float)java.lang.Math.max(0.00100000005f, fHslider2));
		float fSlow6 = ((fSlow4 + fSlow5) + 1.0f);
		float fSlow7 = (fSlow0 / fSlow6);
		float fSlow8 = ((fSlow0 + fSlow5) + (1.0f - fSlow3));
		float fSlow9 = (1.0f / fSlow6);
		float fSlow10 = ((fSlow0 + 1.0f) * fSlow2);
		float fSlow11 = (0.0f - (2.0f * ((fSlow0 + fSlow10) + -1.0f)));
		float fSlow12 = (fSlow4 + (1.0f - fSlow5));
		float fSlow13 = (2.0f * (fSlow0 + (-1.0f - fSlow10)));
		float fSlow14 = (fSlow0 + (1.0f - (fSlow3 + fSlow5)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (input0[i] - (fSlow9 * ((fSlow11 * fRec0[1]) + (fSlow12 * fRec0[2]))));
			output0[i] = (fSlow7 * (((fSlow8 * fRec0[0]) + (fSlow13 * fRec0[1])) + (fSlow14 * fRec0[2])));
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

