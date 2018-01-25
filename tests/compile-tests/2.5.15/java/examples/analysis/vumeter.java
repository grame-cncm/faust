/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "vumeter"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fRec0[] = new float[2];
	float fHbargraph0;
	float fRec1[] = new float[2];
	float fHbargraph1;
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "vumeter");
		m.declare("version", "1.0");
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
		fConst0 = (1.0f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
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
		ui_interface.openVerticalBox("vumeter");
		ui_interface.declare("fHbargraph0", "2", "");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("0x7fb8eac51b60", new FaustVarAccess() {
				public String getId() { return "fHbargraph0"; }
				public void set(float val) { fHbargraph0 = val; }
				public float get() { return (float)fHbargraph0; }
			}
			, -70.0f, 5.0f);
		ui_interface.declare("fHbargraph1", "2", "");
		ui_interface.declare("fHbargraph1", "unit", "dB");
		ui_interface.addHorizontalBargraph("0x7fb8eac552f0", new FaustVarAccess() {
				public String getId() { return "fHbargraph1"; }
				public void set(float val) { fHbargraph1 = val; }
				public float get() { return (float)fHbargraph1; }
			}
			, -70.0f, 5.0f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fRec0[0] = (float)java.lang.Math.max((fRec0[1] - fConst0), (float)java.lang.Math.abs(fTemp0));
			fHbargraph0 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec0[0])));
			output0[i] = fTemp0;
			float fTemp1 = input1[i];
			fRec1[0] = (float)java.lang.Math.max((fRec1[1] - fConst0), (float)java.lang.Math.abs(fTemp1));
			fHbargraph1 = (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, fRec1[0])));
			output1[i] = fTemp1;
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}
	
};

