/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "dbmeter"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int fSamplingFreq;
	float fConst0;
	float fRec0[] = new float[2];
	float fVbargraph0;
	int iConst1;
	float fRec1[] = new float[2];
	float fVbargraph1;
	int iConst2;
	float fRec2[] = new float[2];
	float fVbargraph2;
	int iConst3;
	float fRec3[] = new float[2];
	float fVbargraph3;
	int iConst4;
	float fRec4[] = new float[2];
	float fVbargraph4;
	int iConst5;
	float fRec5[] = new float[2];
	float fVbargraph5;
	int iConst6;
	float fRec6[] = new float[2];
	float fVbargraph6;
	int iConst7;
	float fRec7[] = new float[2];
	float fVbargraph7;
	int iConst8;
	
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
		m.declare("name", "dbmeter");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 8;
		
	}
	int getNumOutputs() {
		return 8;
		
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
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
		fConst0 = (80.0f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		iConst1 = 0;
		iConst2 = 0;
		iConst3 = 0;
		iConst4 = 0;
		iConst5 = 0;
		iConst6 = 0;
		iConst7 = 0;
		iConst8 = 0;
		
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
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
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
		ui_interface.openHorizontalBox("8 channels dB meter");
		ui_interface.openVerticalBox("0");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f5d400", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("1");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f61ae0", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("2");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f661c0", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("3");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f6a950", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("4");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f6f190", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("5");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f73a80", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("6");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f78420", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("7");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc7c0f7ce70", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -70.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] input2 = inputs[2];
		float[] input3 = inputs[3];
		float[] input4 = inputs[4];
		float[] input5 = inputs[5];
		float[] input6 = inputs[6];
		float[] input7 = inputs[7];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float[] output4 = outputs[4];
		float[] output5 = outputs[5];
		float[] output6 = outputs[6];
		float[] output7 = outputs[7];
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fRec0[0] = (float)java.lang.Math.max((fRec0[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp0))))));
			fVbargraph0 = fRec0[0];
			output0[i] = (float)iConst1;
			float fTemp1 = input1[i];
			fRec1[0] = (float)java.lang.Math.max((fRec1[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp1))))));
			fVbargraph1 = fRec1[0];
			output1[i] = (float)iConst2;
			float fTemp2 = input2[i];
			fRec2[0] = (float)java.lang.Math.max((fRec2[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp2))))));
			fVbargraph2 = fRec2[0];
			output2[i] = (float)iConst3;
			float fTemp3 = input3[i];
			fRec3[0] = (float)java.lang.Math.max((fRec3[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp3))))));
			fVbargraph3 = fRec3[0];
			output3[i] = (float)iConst4;
			float fTemp4 = input4[i];
			fRec4[0] = (float)java.lang.Math.max((fRec4[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp4))))));
			fVbargraph4 = fRec4[0];
			output4[i] = (float)iConst5;
			float fTemp5 = input5[i];
			fRec5[0] = (float)java.lang.Math.max((fRec5[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp5))))));
			fVbargraph5 = fRec5[0];
			output5[i] = (float)iConst6;
			float fTemp6 = input6[i];
			fRec6[0] = (float)java.lang.Math.max((fRec6[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp6))))));
			fVbargraph6 = fRec6[0];
			output6[i] = (float)iConst7;
			float fTemp7 = input7[i];
			fRec7[0] = (float)java.lang.Math.max((fRec7[1] - fConst0), (float)java.lang.Math.min(10.0f, (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(0.000316227757f, (float)java.lang.Math.abs(fTemp7))))));
			fVbargraph7 = fRec7[0];
			output7[i] = (float)iConst8;
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}
	
};

