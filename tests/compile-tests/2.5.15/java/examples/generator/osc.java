/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2009"
license: "BSD"
name: "osc"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fHslider0;
	int iVec0[] = new int[2];
	float fRec0[] = new float[2];
	float fRec1[] = new float[2];
	float fHslider1;
	float fRec2[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2009");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "osc");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "1.0");
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
		fConst0 = (6.28318548f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)1000.0f;
		fHslider1 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
			
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
		ui_interface.openVerticalBox("Oscillator");
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 1000.0f, 20.0f, 24000.0f, 1.0f);
		ui_interface.declare("fHslider1", "unit", "dB");
		ui_interface.addHorizontalSlider("volume", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, -96.0f, 0.0f, 0.100000001f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float fSlow0 = (fConst0 * fHslider0);
		float fSlow1 = (float)java.lang.Math.sin(fSlow0);
		float fSlow2 = (float)java.lang.Math.cos(fSlow0);
		float fSlow3 = (0.0f - fSlow1);
		float fSlow4 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider1)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = ((fSlow1 * fRec1[1]) + (fSlow2 * fRec0[1]));
			fRec1[0] = (((fSlow2 * fRec1[1]) + (fSlow3 * fRec0[1])) + (float)(1 - iVec0[1]));
			fRec2[0] = (fSlow4 + (0.999000013f * fRec2[1]));
			output0[i] = (fRec0[0] * fRec2[0]);
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			
		}
		
	}
	
};

