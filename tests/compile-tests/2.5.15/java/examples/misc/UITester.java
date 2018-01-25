/* ------------------------------------------------------------
author: "O. Guillerminet"
copyright: "(c) O. Guillerminet 2012"
license: "BSD"
name: "UITester"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	float fCheckbox0;
	float fCheckbox1;
	float fEntry0;
	float fVslider0;
	float fVslider1;
	float fVslider2;
	float fVslider3;
	float fVslider4;
	float fVslider5;
	float fVslider6;
	float fButton0;
	float fHslider0;
	float fVslider7;
	float fVslider8;
	float fVslider9;
	float fEntry1;
	float fVbargraph0;
	float fVslider10;
	float fVslider11;
	float fVslider12;
	float fEntry2;
	float fVbargraph1;
	float fVslider13;
	float fVslider14;
	float fVslider15;
	float fEntry3;
	float fVbargraph2;
	float fHbargraph0;
	float fVslider16;
	float fButton1;
	float fHslider1;
	float fEntry4;
	float fVbargraph3;
	float fHbargraph1;
	int fSamplingFreq;
	
	public void metadata(Meta m) { 
		m.declare("author", "O. Guillerminet");
		m.declare("copyright", "(c) O. Guillerminet 2012");
		m.declare("license", "BSD");
		m.declare("name", "UITester");
		m.declare("version", "1.0");
	}

	int getNumInputs() {
		return 6;
		
	}
	int getNumOutputs() {
		return 34;
		
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
			case 8: {
				rate = 1;
				break;
			}
			case 9: {
				rate = 1;
				break;
			}
			case 10: {
				rate = 1;
				break;
			}
			case 11: {
				rate = 1;
				break;
			}
			case 12: {
				rate = 1;
				break;
			}
			case 13: {
				rate = 1;
				break;
			}
			case 14: {
				rate = 1;
				break;
			}
			case 15: {
				rate = 1;
				break;
			}
			case 16: {
				rate = 1;
				break;
			}
			case 17: {
				rate = 1;
				break;
			}
			case 18: {
				rate = 1;
				break;
			}
			case 19: {
				rate = 1;
				break;
			}
			case 20: {
				rate = 1;
				break;
			}
			case 21: {
				rate = 1;
				break;
			}
			case 22: {
				rate = 1;
				break;
			}
			case 23: {
				rate = 1;
				break;
			}
			case 24: {
				rate = 1;
				break;
			}
			case 25: {
				rate = 1;
				break;
			}
			case 26: {
				rate = 1;
				break;
			}
			case 27: {
				rate = 1;
				break;
			}
			case 28: {
				rate = 1;
				break;
			}
			case 29: {
				rate = 1;
				break;
			}
			case 30: {
				rate = 1;
				break;
			}
			case 31: {
				rate = 1;
				break;
			}
			case 32: {
				rate = 1;
				break;
			}
			case 33: {
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
		fCheckbox1 = (float)0.0f;
		fEntry0 = (float)60.0f;
		fVslider0 = (float)60.0f;
		fVslider1 = (float)60.0f;
		fVslider2 = (float)60.0f;
		fVslider3 = (float)60.0f;
		fVslider4 = (float)60.0f;
		fVslider5 = (float)60.0f;
		fVslider6 = (float)60.0f;
		fButton0 = (float)0.0f;
		fHslider0 = (float)60.0f;
		fVslider7 = (float)60.0f;
		fVslider8 = (float)60.0f;
		fVslider9 = (float)60.0f;
		fEntry1 = (float)60.0f;
		fVslider10 = (float)60.0f;
		fVslider11 = (float)60.0f;
		fVslider12 = (float)60.0f;
		fEntry2 = (float)60.0f;
		fVslider13 = (float)60.0f;
		fVslider14 = (float)60.0f;
		fVslider15 = (float)60.0f;
		fEntry3 = (float)60.0f;
		fVslider16 = (float)60.0f;
		fButton1 = (float)0.0f;
		fHslider1 = (float)60.0f;
		fEntry4 = (float)60.0f;
		
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
		ui_interface.openTabBox("grp 1");
		ui_interface.openHorizontalBox("hmisc");
		ui_interface.addButton("button", new FaustVarAccess() {
				public String getId() { return "fButton1"; }
				public void set(float val) { fButton1 = val; }
				public float get() { return (float)fButton1; }
			}
			);
		ui_interface.addHorizontalBargraph("hbar", new FaustVarAccess() {
				public String getId() { return "fHbargraph1"; }
				public void set(float val) { fHbargraph1 = val; }
				public float get() { return (float)fHbargraph1; }
			}
			, 0.0f, 127.0f);
		ui_interface.addHorizontalSlider("hslider", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fEntry4", "unit", "f");
		ui_interface.addNumEntry("num", new FaustVarAccess() {
				public String getId() { return "fEntry4"; }
				public void set(float val) { fEntry4 = val; }
				public float get() { return (float)fEntry4; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.addVerticalBargraph("vbar", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, 0.0f, 127.0f);
		ui_interface.declare("fVslider16", "unit", "f");
		ui_interface.addVerticalSlider("vslider4", new FaustVarAccess() {
				public String getId() { return "fVslider16"; }
				public void set(float val) { fVslider16 = val; }
				public float get() { return (float)fVslider16; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("knobs");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.addVerticalSlider("knob1", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.addVerticalSlider("knob2", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fVslider5", "style", "knob");
		ui_interface.addVerticalSlider("knob3", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("sliders");
		ui_interface.addVerticalSlider("vslider1", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.addVerticalSlider("vslider2", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.addVerticalSlider("vslider3", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("vbox");
		ui_interface.addCheckButton("check1", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.addCheckButton("check2", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.addNumEntry("knob0", new FaustVarAccess() {
				public String getId() { return "fEntry0"; }
				public void set(float val) { fEntry0 = val; }
				public float get() { return (float)fEntry0; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("vmisc");
		ui_interface.addButton("button", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.addHorizontalBargraph("hbar", new FaustVarAccess() {
				public String getId() { return "fHbargraph0"; }
				public void set(float val) { fHbargraph0 = val; }
				public float get() { return (float)fHbargraph0; }
			}
			, 0.0f, 127.0f);
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("hslider", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.openHorizontalBox("small box 1");
		ui_interface.declare("fVslider9", "style", "knob");
		ui_interface.addVerticalSlider("knob4", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fEntry1", "unit", "f");
		ui_interface.addNumEntry("num1", new FaustVarAccess() {
				public String getId() { return "fEntry1"; }
				public void set(float val) { fEntry1 = val; }
				public float get() { return (float)fEntry1; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.addVerticalBargraph("vbar1", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, 0.0f, 127.0f);
		ui_interface.declare("fVslider7", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider5", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fVslider8", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider6", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("sub box 1");
		ui_interface.openHorizontalBox("small box 2");
		ui_interface.declare("fVslider12", "style", "knob");
		ui_interface.addVerticalSlider("knob5", new FaustVarAccess() {
				public String getId() { return "fVslider12"; }
				public void set(float val) { fVslider12 = val; }
				public float get() { return (float)fVslider12; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fEntry2", "unit", "f");
		ui_interface.addNumEntry("num2", new FaustVarAccess() {
				public String getId() { return "fEntry2"; }
				public void set(float val) { fEntry2 = val; }
				public float get() { return (float)fEntry2; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.addVerticalBargraph("vbar2", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, 0.0f, 127.0f);
		ui_interface.declare("fVslider10", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider7", new FaustVarAccess() {
				public String getId() { return "fVslider10"; }
				public void set(float val) { fVslider10 = val; }
				public float get() { return (float)fVslider10; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fVslider11", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider8", new FaustVarAccess() {
				public String getId() { return "fVslider11"; }
				public void set(float val) { fVslider11 = val; }
				public float get() { return (float)fVslider11; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openHorizontalBox("small box 3");
		ui_interface.declare("fVslider15", "style", "knob");
		ui_interface.addVerticalSlider("knob6", new FaustVarAccess() {
				public String getId() { return "fVslider15"; }
				public void set(float val) { fVslider15 = val; }
				public float get() { return (float)fVslider15; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fEntry3", "unit", "f");
		ui_interface.addNumEntry("num3", new FaustVarAccess() {
				public String getId() { return "fEntry3"; }
				public void set(float val) { fEntry3 = val; }
				public float get() { return (float)fEntry3; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.addVerticalBargraph("vbar3", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, 0.0f, 127.0f);
		ui_interface.declare("fVslider14", "unit", "m");
		ui_interface.addVerticalSlider("vslider10", new FaustVarAccess() {
				public String getId() { return "fVslider14"; }
				public void set(float val) { fVslider14 = val; }
				public float get() { return (float)fVslider14; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.declare("fVslider13", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider9", new FaustVarAccess() {
				public String getId() { return "fVslider13"; }
				public void set(float val) { fVslider13 = val; }
				public float get() { return (float)fVslider13; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("fVslider6", "unit", "Hz");
		ui_interface.addVerticalSlider("vslider4", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, 60.0f, 0.0f, 127.0f, 0.100000001f);
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
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float[] output2 = outputs[2];
		float[] output3 = outputs[3];
		float[] output4 = outputs[4];
		float[] output5 = outputs[5];
		float[] output6 = outputs[6];
		float[] output7 = outputs[7];
		float[] output8 = outputs[8];
		float[] output9 = outputs[9];
		float[] output10 = outputs[10];
		float[] output11 = outputs[11];
		float[] output12 = outputs[12];
		float[] output13 = outputs[13];
		float[] output14 = outputs[14];
		float[] output15 = outputs[15];
		float[] output16 = outputs[16];
		float[] output17 = outputs[17];
		float[] output18 = outputs[18];
		float[] output19 = outputs[19];
		float[] output20 = outputs[20];
		float[] output21 = outputs[21];
		float[] output22 = outputs[22];
		float[] output23 = outputs[23];
		float[] output24 = outputs[24];
		float[] output25 = outputs[25];
		float[] output26 = outputs[26];
		float[] output27 = outputs[27];
		float[] output28 = outputs[28];
		float[] output29 = outputs[29];
		float[] output30 = outputs[30];
		float[] output31 = outputs[31];
		float[] output32 = outputs[32];
		float[] output33 = outputs[33];
		float fSlow0 = fCheckbox0;
		float fSlow1 = fCheckbox1;
		float fSlow2 = fEntry0;
		float fSlow3 = fVslider0;
		float fSlow4 = fVslider1;
		float fSlow5 = fVslider2;
		float fSlow6 = fVslider3;
		float fSlow7 = fVslider4;
		float fSlow8 = fVslider5;
		float fSlow9 = fVslider6;
		float fSlow10 = fButton0;
		float fSlow11 = fHslider0;
		float fSlow12 = fVslider7;
		float fSlow13 = fVslider8;
		float fSlow14 = fVslider9;
		float fSlow15 = fEntry1;
		float fSlow16 = fVslider10;
		float fSlow17 = fVslider11;
		float fSlow18 = fVslider12;
		float fSlow19 = fEntry2;
		float fSlow20 = fVslider13;
		float fSlow21 = fVslider14;
		float fSlow22 = fVslider15;
		float fSlow23 = fEntry3;
		float fSlow24 = fVslider16;
		float fSlow25 = fButton1;
		float fSlow26 = fHslider1;
		float fSlow27 = fEntry4;
		for (int i = 0; (i < count); i = (i + 1)) {
			output0[i] = fSlow0;
			output1[i] = fSlow1;
			output2[i] = fSlow2;
			output3[i] = fSlow3;
			output4[i] = fSlow4;
			output5[i] = fSlow5;
			output6[i] = fSlow6;
			output7[i] = fSlow7;
			output8[i] = fSlow8;
			output9[i] = fSlow9;
			output10[i] = fSlow10;
			output11[i] = fSlow11;
			output12[i] = fSlow12;
			output13[i] = fSlow13;
			output14[i] = fSlow14;
			output15[i] = fSlow15;
			fVbargraph0 = input0[i];
			output16[i] = fVbargraph0;
			output17[i] = fSlow16;
			output18[i] = fSlow17;
			output19[i] = fSlow18;
			output20[i] = fSlow19;
			fVbargraph1 = input1[i];
			output21[i] = fVbargraph1;
			output22[i] = fSlow20;
			output23[i] = fSlow21;
			output24[i] = fSlow22;
			output25[i] = fSlow23;
			fVbargraph2 = input2[i];
			output26[i] = fVbargraph2;
			fHbargraph0 = input3[i];
			output27[i] = fHbargraph0;
			output28[i] = fSlow24;
			output29[i] = fSlow25;
			output30[i] = fSlow26;
			output31[i] = fSlow27;
			fVbargraph3 = input4[i];
			output32[i] = fVbargraph3;
			fHbargraph1 = input5[i];
			output33[i] = fHbargraph1;
			
		}
		
	}
	
};

