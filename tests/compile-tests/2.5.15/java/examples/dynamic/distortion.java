/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "distortion"
version: "0.0"
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
	float fHslider1;
	float fRec2[] = new float[2];
	float fVec0[] = new float[2];
	float fRec0[] = new float[2];
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Distortion demo application.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "distortion");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
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
		fCheckbox0 = (float)0.0f;
		fHslider0 = (float)0.0f;
		fHslider1 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
			
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
		ui_interface.declare("0", "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html");
		ui_interface.openVerticalBox("CUBIC NONLINEARITY cubicnl");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the   nonlinearity has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "tooltip", "Amount of distortion");
		ui_interface.addHorizontalSlider("Drive", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "tooltip", "Brings in even harmonics");
		ui_interface.addHorizontalSlider("Offset", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		int iSlow0 = (int)fCheckbox0;
		float fSlow1 = (0.00100000005f * fHslider0);
		float fSlow2 = (0.00100000005f * fHslider1);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fRec1[0] = (fSlow1 + (0.999000013f * fRec1[1]));
			fRec2[0] = (fSlow2 + (0.999000013f * fRec2[1]));
			float fTemp1 = (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, (((((iSlow0==0)?true:false)?0.0f:fTemp0) * (float)java.lang.Math.pow(10.0f, (2.0f * fRec1[0]))) + fRec2[0])));
			float fTemp2 = (fTemp1 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp1))));
			fVec0[0] = fTemp2;
			fRec0[0] = (((0.995000005f * fRec0[1]) + fTemp2) - fVec0[1]);
			output0[i] = (((iSlow0==0)?true:false)?fTemp0:fRec0[0]);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

