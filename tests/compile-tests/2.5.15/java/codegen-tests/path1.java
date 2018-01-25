/* ------------------------------------------------------------
name: "path1"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fHslider0;
	float fHslider1;
	float fHslider2;
	float fHslider3;
	float fHslider4;
	float fHslider5;
	float fHslider6;
	float fHslider7;
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("name", "path1");
	}

	int getNumInputs() {
		return 4;
		
	}
	int getNumOutputs() {
		return 4;
		
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
		fHslider0 = (float)0.0f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)0.0f;
		fHslider6 = (float)0.0f;
		fHslider7 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		
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
		ui_interface.openTabBox("toto");
		ui_interface.openVerticalBox("foo 0");
		ui_interface.addHorizontalSlider("slid1", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("slid2", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("foo 1");
		ui_interface.addHorizontalSlider("slid1", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("slid2", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("foo 2");
		ui_interface.addHorizontalSlider("slid1", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("slid2", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("foo 3");
		ui_interface.addHorizontalSlider("slid1", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.addHorizontalSlider("slid2", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 0.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] input1 = inputs[1];
		float[] input2 = inputs[2];
		float[] input3 = inputs[3];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float fSlow0 = (fHslider0 * fHslider1);
		float fSlow1 = (fHslider2 * fHslider3);
		float fSlow2 = (fHslider4 * fHslider5);
		float fSlow3 = (fHslider6 * fHslider7);
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = (fSlow0 * input0[i]);
			output1[i] = (fSlow1 * input1[i]);
			output2[i] = (fSlow2 * input2[i]);
			output3[i] = (fSlow3 * input3[i]);
			
		}
		
	}
	
};

