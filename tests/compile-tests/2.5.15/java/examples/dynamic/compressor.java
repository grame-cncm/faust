/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "compressor"
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
	float fConst2;
	float fHslider1;
	float fHslider2;
	float fHslider3;
	float fRec2[] = new float[2];
	float fRec1[] = new float[2];
	float fHslider4;
	float fRec0[] = new float[2];
	float fRec5[] = new float[2];
	float fRec4[] = new float[2];
	float fRec3[] = new float[2];
	float fHbargraph0;
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("compressors.lib/name", "Faust Compressor Effect Library");
		m.declare("compressors.lib/version", "0.0");
		m.declare("description", "Compressor demo application");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "compressor");
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
		fConst1 = (2.0f / fConst0);
		fConst2 = (1.0f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fCheckbox0 = (float)0.0f;
		fHslider0 = (float)40.0f;
		fHslider1 = (float)50.0f;
		fHslider2 = (float)5.0f;
		fHslider3 = (float)500.0f;
		fHslider4 = (float)-30.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec3[l5] = 0.0f;
			
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
		ui_interface.declare("0", "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface.openVerticalBox("COMPRESSOR");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the compressor   has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fHbargraph0", "1", "");
		ui_interface.declare("fHbargraph0", "tooltip", "Current gain of  the compressor in dB");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("Compressor Gain", new FaustVarAccess() {
				public String getId() { return "fHbargraph0"; }
				public void set(float val) { fHbargraph0 = val; }
				public float get() { return (float)fHbargraph0; }
			}
			, -50.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("Compression Control");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB");
		ui_interface.addHorizontalSlider("Ratio", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 5.0f, 1.0f, 20.0f, 0.100000001f);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio");
		ui_interface.declare("fHslider4", "unit", "dB");
		ui_interface.addHorizontalSlider("Threshold", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, -30.0f, -100.0f, 10.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openHorizontalBox("Compression Response");
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 50.0f, 1.0f, 1000.0f, 0.100000001f);
		ui_interface.declare("fHslider3", "2", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')");
		ui_interface.declare("fHslider3", "unit", "ms");
		ui_interface.addHorizontalSlider("Release", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 500.0f, 1.0f, 1000.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("fHslider0", "5", "");
		ui_interface.declare("fHslider0", "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Makeup Gain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 40.0f, -96.0f, 96.0f, 0.100000001f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		int iSlow0 = (int)fCheckbox0;
		float fSlow1 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider0));
		float fSlow2 = (float)java.lang.Math.max(fConst2, (0.00100000005f * fHslider1));
		float fSlow3 = (float)java.lang.Math.exp((0.0f - (fConst1 / fSlow2)));
		float fSlow4 = (((1.0f / fHslider2) + -1.0f) * (1.0f - fSlow3));
		float fSlow5 = (float)java.lang.Math.exp((0.0f - (fConst2 / fSlow2)));
		float fSlow6 = (float)java.lang.Math.exp((0.0f - (fConst2 / (float)java.lang.Math.max(fConst2, (0.00100000005f * fHslider3)))));
		float fSlow7 = fHslider4;
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			float fTemp1 = (((iSlow0==0)?true:false)?0.0f:fTemp0);
			float fTemp2 = input1[i];
			float fTemp3 = (((iSlow0==0)?true:false)?0.0f:fTemp2);
			float fTemp4 = (float)java.lang.Math.abs(((float)java.lang.Math.abs(fTemp1) + (float)java.lang.Math.abs(fTemp3)));
			float fTemp5 = (((fRec1[1] > fTemp4))?fSlow6:fSlow5);
			fRec2[0] = ((fRec2[1] * fTemp5) + ((1.0f - fTemp5) * fTemp4));
			fRec1[0] = fRec2[0];
			fRec0[0] = ((fSlow3 * fRec0[1]) + (fSlow4 * (float)java.lang.Math.max(((20.0f * (float)java.lang.Math.log10(fRec1[0])) - fSlow7), 0.0f)));
			float fTemp6 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec0[0]));
			float fTemp7 = (fTemp6 * fTemp1);
			output0[i] = (((iSlow0==0)?true:false)?fTemp0:(fSlow1 * fTemp7));
			float fTemp8 = (fTemp6 * fTemp3);
			float fTemp9 = (float)java.lang.Math.abs(((float)java.lang.Math.abs(fTemp7) + (float)java.lang.Math.abs(fTemp8)));
			float fTemp10 = (((fRec4[1] > fTemp9))?fSlow6:fSlow5);
			fRec5[0] = ((fRec5[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			fRec4[0] = fRec5[0];
			fRec3[0] = ((fSlow3 * fRec3[1]) + (fSlow4 * (float)java.lang.Math.max(((20.0f * (float)java.lang.Math.log10(fRec4[0])) - fSlow7), 0.0f)));
			fHbargraph0 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec3[0]))));
			output1[i] = (((iSlow0==0)?true:false)?fTemp2:(fSlow1 * fTemp8));
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			
		}
		
	}
	
};

