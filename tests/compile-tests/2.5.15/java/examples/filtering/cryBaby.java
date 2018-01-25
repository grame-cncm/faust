/* ------------------------------------------------------------
name: "cryBaby"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fCheckbox0;
	float fHslider0;
	float fRec1[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec2[] = new float[2];
	float fRec3[] = new float[2];
	float fRec0[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Application demonstrating the CryBaby wah pedal emulation");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "cryBaby");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m.declare("vaeffects.lib/version", "0.0");
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
		fConst1 = (1413.71667f / fConst0);
		fConst2 = (2827.43335f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fCheckbox0 = (float)0.0f;
		fHslider0 = (float)0.80000000000000004f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
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
		ui_interface.declare("0", "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html");
		ui_interface.openHorizontalBox("CRYBABY");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the wah   pedal has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)");
		ui_interface.addHorizontalSlider("Wah parameter", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		int iSlow0 = (int)fCheckbox0;
		float fSlow1 = fHslider0;
		float fSlow2 = (9.99999975e-05f * (float)java.lang.Math.pow(4.0f, fSlow1));
		float fSlow3 = (float)java.lang.Math.pow(2.0f, (2.29999995f * fSlow1));
		float fSlow4 = (1.0f - (fConst1 * (fSlow3 / (float)java.lang.Math.pow(2.0f, ((2.0f * (1.0f - fSlow1)) + 1.0f)))));
		float fSlow5 = (0.00100000005f * (0.0f - (2.0f * (fSlow4 * (float)java.lang.Math.cos((fConst2 * fSlow3))))));
		float fSlow6 = (0.00100000005f * mydsp_faustpower2_f(fSlow4));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fRec1[0] = (fSlow2 + (0.999000013f * fRec1[1]));
			fRec2[0] = (fSlow5 + (0.999000013f * fRec2[1]));
			fRec3[0] = (fSlow6 + (0.999000013f * fRec3[1]));
			fRec0[0] = (((((iSlow0==0)?true:false)?0.0f:fTemp0) * fRec1[0]) - ((fRec2[0] * fRec0[1]) + (fRec3[0] * fRec0[2])));
			output0[i] = (((iSlow0==0)?true:false)?fTemp0:(fRec0[0] - fRec0[1]));
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

