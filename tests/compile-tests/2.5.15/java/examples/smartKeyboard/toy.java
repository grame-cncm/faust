/* ------------------------------------------------------------
name: "toy"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	float fRec1[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fHslider1;
	float fRec2[] = new float[2];
	float fConst1;
	float fHslider2;
	float fRec5[] = new float[2];
	float fVec0[] = new float[2];
	float fRec4[] = new float[2];
	float fConst2;
	float fHslider3;
	float fRec6[] = new float[2];
	float fHslider4;
	float fRec7[] = new float[2];
	float fRec3[] = new float[3];
	int IOTA;
	float fRec0[] = new float[131072];
	float fHslider5;
	float fRec8[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Send Numbered X':'1',  'Keyboard 0 - Send Numbered Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "toy");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fConst2 = (3.14159274f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.5f;
		fHslider2 = (float)0.5f;
		fHslider3 = (float)0.5f;
		fHslider4 = (float)30.0f;
		fHslider5 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec5[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec3[l7] = 0.0f;
			
		}
		IOTA = 0;
		for (int l8 = 0; (l8 < 131072); l8 = (l8 + 1)) {
			fRec0[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec8[l9] = 0.0f;
			
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
		ui_interface.openVerticalBox("toy");
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("del", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.5f, 0.00999999978f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider0", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("fb", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("q", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 30.0f, 10.0f, 50.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("x0", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("y0", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("y1", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * fHslider0);
		float fSlow1 = (0.00100000005f * fHslider1);
		float fSlow2 = (0.00100000005f * fHslider2);
		float fSlow3 = (0.00100000005f * fHslider3);
		float fSlow4 = (0.00100000005f * fHslider4);
		float fSlow5 = (0.00100000005f * fHslider5);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (0.999000013f * fRec1[1]));
			fRec2[0] = (fSlow1 + (0.999000013f * fRec2[1]));
			fRec5[0] = (fSlow2 + (0.999000013f * fRec5[1]));
			fVec0[0] = ((20.0f * fRec5[0]) + 2.0f);
			float fTemp0 = (fRec4[1] + (fConst1 * fVec0[1]));
			fRec4[0] = (fTemp0 - (float)java.lang.Math.floor(fTemp0));
			fRec6[0] = (fSlow3 + (0.999000013f * fRec6[1]));
			float fTemp1 = (float)java.lang.Math.tan((fConst2 * ((3000.0f * fRec6[0]) + 300.0f)));
			float fTemp2 = (1.0f / fTemp1);
			fRec7[0] = (fSlow4 + (0.999000013f * fRec7[1]));
			float fTemp3 = (1.0f / fRec7[0]);
			float fTemp4 = (((fTemp2 + fTemp3) / fTemp1) + 1.0f);
			fRec3[0] = (((((fRec4[0] - fRec4[1]) < 0.0f))?1.f:0.f) - (((fRec3[2] * (((fTemp2 - fTemp3) / fTemp1) + 1.0f)) + (2.0f * (fRec3[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp1)))))) / fTemp4));
			fRec0[(IOTA & 131071)] = ((fRec1[0] * fRec0[((IOTA - ((int)(float)java.lang.Math.min(65536.0f, (float)java.lang.Math.max(0.0f, (fConst0 * fRec2[0]))) + 1)) & 131071)]) + ((fRec3[2] + (fRec3[0] + (2.0f * fRec3[1]))) / fTemp4));
			fRec8[0] = (fSlow5 + (0.999000013f * fRec8[1]));
			float fTemp5 = (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, (fRec0[((IOTA - 0) & 131071)] * (float)java.lang.Math.pow(10.0f, (2.0f * fRec8[0])))));
			float fTemp6 = (0.949999988f * (fTemp5 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp5)))));
			output0[i] = fTemp6;
			output1[i] = fTemp6;
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fVec0[1] = fVec0[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
			
		}
		
	}
	
};

