/* ------------------------------------------------------------
name: "fm"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int iVec0[] = new int[2];
	int fSamplingFreq;
	float fConst0;
	float fButton0;
	float fVec1[] = new float[2];
	float fHslider0;
	float fRec2[] = new float[2];
	float fHslider1;
	float fRec5[] = new float[2];
	float fRec3[] = new float[2];
	float fRec4[] = new float[2];
	float fHslider2;
	float fRec6[] = new float[2];
	float fRec0[] = new float[2];
	float fRec1[] = new float[2];
	float fRec7[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "fm");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
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
		fButton0 = (float)0.0f;
		fHslider0 = (float)0.0f;
		fHslider1 = (float)1.0f;
		fHslider2 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
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
		ui_interface.openVerticalBox("fm");
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("res", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 1.0f, 0.0f, 2.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("x", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("y", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float fSlow0 = fButton0;
		int iSlow1 = (fSlow0 == 0.0f);
		float fSlow2 = ((420.0f * fHslider0) + 80.0f);
		float fSlow3 = (0.00100000005f * fHslider1);
		float fSlow4 = (1.0f * fHslider2);
		float fSlow5 = (0.00100000005f * fSlow0);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fVec1[0] = fSlow0;
			int iTemp0 = ((((fSlow0 == fVec1[1]))?1:0) | iSlow1);
			fRec2[0] = ((0.999000013f * (fRec2[1] * (float)iTemp0)) + (fSlow2 * (1.0f - (0.999000013f * (float)iTemp0))));
			fRec5[0] = (fSlow3 + (0.999000013f * fRec5[1]));
			float fTemp1 = (fConst0 * (fRec2[0] * fRec5[0]));
			float fTemp2 = (float)java.lang.Math.sin(fTemp1);
			float fTemp3 = (float)java.lang.Math.cos(fTemp1);
			fRec3[0] = ((fRec4[1] * fTemp2) + (fRec3[1] * fTemp3));
			int iTemp4 = (1 - iVec0[1]);
			fRec4[0] = (((fRec4[1] * fTemp3) + (fRec3[1] * (0.0f - fTemp2))) + (float)iTemp4);
			fRec6[0] = (fSlow4 + (0.999000013f * fRec6[1]));
			float fTemp5 = (fConst0 * (fRec2[0] + (fRec3[0] * fRec6[0])));
			float fTemp6 = (float)java.lang.Math.sin(fTemp5);
			float fTemp7 = (float)java.lang.Math.cos(fTemp5);
			fRec0[0] = ((fRec1[1] * fTemp6) + (fRec0[1] * fTemp7));
			fRec1[0] = (((fRec1[1] * fTemp7) + (fRec0[1] * (0.0f - fTemp6))) + (float)iTemp4);
			fRec7[0] = (fSlow5 + (0.999000013f * fRec7[1]));
			output0[i] = (0.5f * (fRec0[0] * fRec7[0]));
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}
	
};

