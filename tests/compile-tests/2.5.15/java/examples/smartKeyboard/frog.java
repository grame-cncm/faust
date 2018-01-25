/* ------------------------------------------------------------
name: "frog"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fButton0;
	float fVec0[] = new float[2];
	float fRec1[] = new float[2];
	float fConst3;
	float fHslider0;
	float fRec4[] = new float[2];
	float fRec2[] = new float[2];
	float fConst4;
	float fHslider1;
	float fRec5[] = new float[2];
	float fHslider2;
	float fRec6[] = new float[2];
	float fRec0[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "frog");
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
		fConst1 = (float)java.lang.Math.exp((0.0f - (100.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = (1.0f / fConst0);
		fConst4 = (3.14159274f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fButton0 = (float)0.0f;
		fHslider0 = (float)0.0f;
		fHslider1 = (float)2500.0f;
		fHslider2 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
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
		ui_interface.openVerticalBox("frog");
		ui_interface.declare("fHslider1", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("cutoff", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 2500.0f, 50.0f, 5000.0f, 0.00999999978f);
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
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
		float[] output1 = outputs[1];
		float fSlow0 = fButton0;
		float fSlow1 = (fConst2 * fSlow0);
		float fSlow2 = ((99.0f * fHslider0) + 1.0f);
		int iSlow3 = (fSlow0 == 0.0f);
		float fSlow4 = (0.00100000005f * fHslider1);
		float fSlow5 = (0.00100000005f * ((39.0f * (1.0f - fHslider2)) + 1.0f));
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fSlow0;
			fRec1[0] = (fSlow1 + (fConst1 * fRec1[1]));
			int iTemp0 = ((((fSlow0 == fVec0[1]))?1:0) | iSlow3);
			fRec4[0] = ((fSlow2 * (1.0f - (0.999000013f * (float)iTemp0))) + (0.999000013f * ((float)iTemp0 * fRec4[1])));
			float fTemp1 = (float)java.lang.Math.max(1.00000001e-07f, (float)java.lang.Math.abs(fRec4[0]));
			float fTemp2 = (fRec2[1] + (fConst3 * fTemp1));
			float fTemp3 = (fTemp2 + -1.0f);
			int iTemp4 = (fTemp3 < 0.0f);
			fRec2[0] = (((iTemp4==0)?true:false)?fTemp2:fTemp3);
			float fRec3 = (((iTemp4==0)?true:false)?fTemp2:(fTemp2 + ((1.0f - (fConst0 / fTemp1)) * fTemp3)));
			fRec5[0] = (fSlow4 + (0.999000013f * fRec5[1]));
			float fTemp5 = (float)java.lang.Math.tan((fConst4 * fRec5[0]));
			float fTemp6 = (1.0f / fTemp5);
			fRec6[0] = (fSlow5 + (0.999000013f * fRec6[1]));
			float fTemp7 = (1.0f / fRec6[0]);
			float fTemp8 = (((fTemp6 + fTemp7) / fTemp5) + 1.0f);
			fRec0[0] = ((0.5f * (fRec1[0] * ((2.0f * fRec3) + -1.0f))) - (((fRec0[2] * (((fTemp6 - fTemp7) / fTemp5) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp5)))))) / fTemp8));
			float fTemp9 = ((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) / fTemp8);
			output0[i] = fTemp9;
			output1[i] = fTemp9;
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

