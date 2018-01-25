/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "flanger"
version: "0.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fCheckbox0;
	float fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider1;
	int iVec0[] = new int[2];
	float fRec0[] = new float[2];
	float fRec1[] = new float[2];
	float fHbargraph0;
	float fCheckbox1;
	float fHslider2;
	float fHslider3;
	int IOTA;
	float fVec1[] = new float[4096];
	float fHslider4;
	float fHslider5;
	float fRec2[] = new float[2];
	float fVec2[] = new float[4096];
	float fRec3[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Flanger effect application.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "flanger");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m.declare("phaflangers.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
	}

	int getNumInputs() {
		return 2;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
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
		fConst1 = (6.28318548f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fCheckbox0 = (float)0.0f;
		fHslider0 = (float)0.0f;
		fHslider1 = (float)0.5f;
		fCheckbox1 = (float)0.0f;
		fHslider2 = (float)1.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)1.0f;
		fHslider5 = (float)10.0f;
		
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
		IOTA = 0;
		for (int l3 = 0; (l3 < 4096); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 4096); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
			
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
		ui_interface.declare("0", "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface.openVerticalBox("FLANGER");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the flanger   has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fCheckbox1", "1", "");
		ui_interface.addCheckButton("Invert Flange Sum", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.declare("fHbargraph0", "2", "");
		ui_interface.declare("fHbargraph0", "style", "led");
		ui_interface.declare("fHbargraph0", "tooltip", "Display sum of flange delays");
		ui_interface.addHorizontalBargraph("Flange LFO", new FaustVarAccess() {
				public String getId() { return "fHbargraph0"; }
				public void set(float val) { fHbargraph0 = val; }
				public float get() { return (float)fHbargraph0; }
			}
			, -1.5f, 1.5f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.5f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider2", "2", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("Depth", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Delay Controls");
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "unit", "ms");
		ui_interface.addHorizontalSlider("Flange Delay", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 10.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "unit", "ms");
		ui_interface.addHorizontalSlider("Delay Offset", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 1.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Flanger Output Level", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, -60.0f, 10.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		int iSlow0 = (int)fCheckbox0;
		float fSlow1 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider0));
		float fSlow2 = (fConst1 * fHslider1);
		float fSlow3 = (float)java.lang.Math.sin(fSlow2);
		float fSlow4 = (float)java.lang.Math.cos(fSlow2);
		float fSlow5 = (0.0f - fSlow3);
		float fSlow6 = fHslider2;
		float fSlow7 = ((((int)fCheckbox1==0)?true:false)?(0.0f - fSlow6):fSlow6);
		float fSlow8 = fHslider3;
		float fSlow9 = (0.00100000005f * fHslider4);
		float fSlow10 = (0.000500000024f * fHslider5);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = ((fSlow3 * fRec1[1]) + (fSlow4 * fRec0[1]));
			fRec1[0] = (((fSlow4 * fRec1[1]) + (fSlow5 * fRec0[1])) + (float)(1 - iVec0[1]));
			fHbargraph0 = (fRec1[0] + fRec0[0]);
			float fTemp0 = input0[i];
			float fTemp1 = (fSlow1 * (((iSlow0==0)?true:false)?0.0f:fTemp0));
			float fTemp2 = ((fSlow8 * fRec2[1]) - fTemp1);
			fVec1[(IOTA & 4095)] = fTemp2;
			float fTemp3 = (fConst0 * (fSlow9 + (fSlow10 * (fRec0[0] + 1.0f))));
			int iTemp4 = (int)fTemp3;
			float fTemp5 = (float)java.lang.Math.floor(fTemp3);
			fRec2[0] = ((fVec1[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, iTemp4))) & 4095)] * (fTemp5 + (1.0f - fTemp3))) + ((fTemp3 - fTemp5) * fVec1[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, (iTemp4 + 1)))) & 4095)]));
			output0[i] = (((iSlow0==0)?true:false)?fTemp0:(0.5f * (fTemp1 + (fSlow7 * fRec2[0]))));
			float fTemp6 = input1[i];
			float fTemp7 = (fSlow1 * (((iSlow0==0)?true:false)?0.0f:fTemp6));
			float fTemp8 = ((fSlow8 * fRec3[1]) - fTemp7);
			fVec2[(IOTA & 4095)] = fTemp8;
			float fTemp9 = (fConst0 * (fSlow9 + (fSlow10 * (fRec1[0] + 1.0f))));
			int iTemp10 = (int)fTemp9;
			float fTemp11 = (float)java.lang.Math.floor(fTemp9);
			fRec3[0] = ((fVec2[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, iTemp10))) & 4095)] * (fTemp11 + (1.0f - fTemp9))) + ((fTemp9 - fTemp11) * fVec2[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, (iTemp10 + 1)))) & 4095)]));
			output1[i] = (((iSlow0==0)?true:false)?fTemp6:(0.5f * (fTemp7 + (fSlow7 * fRec3[0]))));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			IOTA = (IOTA + 1);
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			
		}
		
	}
	
};

