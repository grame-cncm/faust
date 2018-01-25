/* ------------------------------------------------------------
name: "spectralTilt"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider0;
	float fHslider1;
	float fHslider2;
	float fConst2;
	float fVec0[] = new float[2];
	float fRec1[] = new float[2];
	float fVec1[] = new float[2];
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("description", "Demonstrate the Spectral Tilt effect on test signals");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "spectralTilt");
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
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (1.0f / (float)java.lang.Math.tan((0.5f / fConst0)));
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)100.0f;
		fHslider1 = (float)5000.0f;
		fHslider2 = (float)-0.5f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
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
		ui_interface.openVerticalBox("spectralTilt");
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.addHorizontalSlider("Slope of Spectral Tilt across Band", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, -0.5f, -1.0f, 1.0f, 0.00100000005f);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Start Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 100.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface.declare("fHslider1", "3", "");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Width", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 5000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = fHslider0;
		float fSlow1 = (float)java.lang.Math.pow(((fSlow0 + fHslider1) / fSlow0), 1.0f);
		float fSlow2 = (float)java.lang.Math.tan((fConst1 * (fSlow0 * fSlow1)));
		float fSlow3 = fHslider2;
		float fSlow4 = (float)java.lang.Math.tan((fConst1 * (fSlow0 * (float)java.lang.Math.pow(fSlow1, (1.0f - fSlow3)))));
		float fSlow5 = (fSlow2 / fSlow4);
		float fSlow6 = (float)java.lang.Math.tan((fConst1 * fSlow0));
		float fSlow7 = (6.28318548f * ((fSlow0 * fSlow2) / fSlow6));
		float fSlow8 = (fConst2 + fSlow7);
		float fSlow9 = (0.0f - ((fSlow7 - fConst2) / fSlow8));
		float fSlow10 = (1.0f / fSlow8);
		float fSlow11 = (6.28318548f * ((fSlow0 * fSlow4) / fSlow6));
		float fSlow12 = (fSlow11 - fConst2);
		float fSlow13 = (float)java.lang.Math.tan((fConst1 * (fSlow0 * (float)java.lang.Math.pow(fSlow1, (0.0f - fSlow3)))));
		float fSlow14 = (fSlow6 / fSlow13);
		float fSlow15 = (6.28318548f * fSlow0);
		float fSlow16 = (fConst2 + fSlow15);
		float fSlow17 = (0.0f - ((fSlow15 - fConst2) / fSlow16));
		float fSlow18 = (1.0f / fSlow16);
		float fSlow19 = (6.28318548f * ((fSlow0 * fSlow13) / fSlow6));
		float fSlow20 = (fConst2 + fSlow19);
		float fSlow21 = (fSlow19 - fConst2);
		float fSlow22 = ((fSlow6 * (fConst2 + fSlow11)) / fSlow13);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fVec0[0] = fTemp0;
			fRec1[0] = ((fSlow17 * fRec1[1]) + (fSlow18 * ((fSlow20 * fTemp0) + (fSlow21 * fVec0[1]))));
			fVec1[0] = (fSlow14 * fRec1[0]);
			fRec0[0] = ((fSlow9 * fRec0[1]) + (fSlow10 * ((fSlow12 * fVec1[1]) + (fSlow22 * fRec1[0]))));
			output0[i] = (fSlow5 * fRec0[0]);
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

