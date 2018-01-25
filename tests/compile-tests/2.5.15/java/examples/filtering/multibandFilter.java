/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "multibandFilter"
version: "1.0"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	int fSamplingFreq;
	float fConst0;
	float fEntry0;
	float fVslider0;
	float fEntry1;
	float fEntry2;
	float fVslider1;
	float fEntry3;
	float fEntry4;
	float fVslider2;
	float fEntry5;
	float fEntry6;
	float fVslider3;
	float fEntry7;
	float fEntry8;
	float fVslider4;
	float fEntry9;
	float fEntry10;
	float fVslider5;
	float fEntry11;
	float fEntry12;
	float fVslider6;
	float fEntry13;
	float fEntry14;
	float fVslider7;
	float fEntry15;
	float fEntry16;
	float fVslider8;
	float fEntry17;
	float fEntry18;
	float fVslider9;
	float fEntry19;
	float fRec9[] = new float[3];
	float fRec8[] = new float[3];
	float fRec7[] = new float[3];
	float fRec6[] = new float[3];
	float fRec5[] = new float[3];
	float fRec4[] = new float[3];
	float fRec3[] = new float[3];
	float fRec2[] = new float[3];
	float fRec1[] = new float[3];
	float fRec0[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("author", "Grame");
		m.declare("bandfilter.dsp/author", "Grame");
		m.declare("bandfilter.dsp/copyright", "(c)GRAME 2006");
		m.declare("bandfilter.dsp/license", "BSD");
		m.declare("bandfilter.dsp/name", "bandFilter");
		m.declare("bandfilter.dsp/version", "1.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)GRAME 2006");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "BSD");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "multibandFilter");
		m.declare("version", "1.0");
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
		fConst0 = (3.14159274f / (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq)));
		
	}
	
	public void instanceResetUserInterface() {
		fEntry0 = (float)10000.0f;
		fVslider0 = (float)0.0f;
		fEntry1 = (float)50.0f;
		fEntry2 = (float)9000.0f;
		fVslider1 = (float)0.0f;
		fEntry3 = (float)50.0f;
		fEntry4 = (float)8000.0f;
		fVslider2 = (float)0.0f;
		fEntry5 = (float)50.0f;
		fEntry6 = (float)7000.0f;
		fVslider3 = (float)0.0f;
		fEntry7 = (float)50.0f;
		fEntry8 = (float)6000.0f;
		fVslider4 = (float)0.0f;
		fEntry9 = (float)50.0f;
		fEntry10 = (float)5000.0f;
		fVslider5 = (float)0.0f;
		fEntry11 = (float)50.0f;
		fEntry12 = (float)4000.0f;
		fVslider6 = (float)0.0f;
		fEntry13 = (float)50.0f;
		fEntry14 = (float)3000.0f;
		fVslider7 = (float)0.0f;
		fEntry15 = (float)50.0f;
		fEntry16 = (float)2000.0f;
		fVslider8 = (float)0.0f;
		fEntry17 = (float)50.0f;
		fEntry18 = (float)1000.0f;
		fVslider9 = (float)0.0f;
		fEntry19 = (float)50.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec9[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec8[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec7[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec6[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec2[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
			
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
		ui_interface.openHorizontalBox("Multi Band Filter");
		ui_interface.openVerticalBox("peak 0");
		ui_interface.declare("fEntry19", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry19"; }
				public void set(float val) { fEntry19 = val; }
				public float get() { return (float)fEntry19; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry18", "style", "knob");
		ui_interface.declare("fEntry18", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry18"; }
				public void set(float val) { fEntry18 = val; }
				public float get() { return (float)fEntry18; }
			}
			, 1000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider9", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 1");
		ui_interface.declare("fEntry17", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry17"; }
				public void set(float val) { fEntry17 = val; }
				public float get() { return (float)fEntry17; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry16", "style", "knob");
		ui_interface.declare("fEntry16", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry16"; }
				public void set(float val) { fEntry16 = val; }
				public float get() { return (float)fEntry16; }
			}
			, 2000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider8", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 2");
		ui_interface.declare("fEntry15", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry15"; }
				public void set(float val) { fEntry15 = val; }
				public float get() { return (float)fEntry15; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry14", "style", "knob");
		ui_interface.declare("fEntry14", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry14"; }
				public void set(float val) { fEntry14 = val; }
				public float get() { return (float)fEntry14; }
			}
			, 3000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider7", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 3");
		ui_interface.declare("fEntry13", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry13"; }
				public void set(float val) { fEntry13 = val; }
				public float get() { return (float)fEntry13; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry12", "style", "knob");
		ui_interface.declare("fEntry12", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry12"; }
				public void set(float val) { fEntry12 = val; }
				public float get() { return (float)fEntry12; }
			}
			, 4000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider6", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 4");
		ui_interface.declare("fEntry11", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry11"; }
				public void set(float val) { fEntry11 = val; }
				public float get() { return (float)fEntry11; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry10", "style", "knob");
		ui_interface.declare("fEntry10", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry10"; }
				public void set(float val) { fEntry10 = val; }
				public float get() { return (float)fEntry10; }
			}
			, 5000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 5");
		ui_interface.declare("fEntry9", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry9"; }
				public void set(float val) { fEntry9 = val; }
				public float get() { return (float)fEntry9; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry8", "style", "knob");
		ui_interface.declare("fEntry8", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry8"; }
				public void set(float val) { fEntry8 = val; }
				public float get() { return (float)fEntry8; }
			}
			, 6000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider4", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 6");
		ui_interface.declare("fEntry7", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry7"; }
				public void set(float val) { fEntry7 = val; }
				public float get() { return (float)fEntry7; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry6", "style", "knob");
		ui_interface.declare("fEntry6", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry6"; }
				public void set(float val) { fEntry6 = val; }
				public float get() { return (float)fEntry6; }
			}
			, 7000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider3", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 7");
		ui_interface.declare("fEntry5", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry5"; }
				public void set(float val) { fEntry5 = val; }
				public float get() { return (float)fEntry5; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry4", "style", "knob");
		ui_interface.declare("fEntry4", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry4"; }
				public void set(float val) { fEntry4 = val; }
				public float get() { return (float)fEntry4; }
			}
			, 8000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider2", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 8");
		ui_interface.declare("fEntry3", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry3"; }
				public void set(float val) { fEntry3 = val; }
				public float get() { return (float)fEntry3; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry2", "style", "knob");
		ui_interface.declare("fEntry2", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry2"; }
				public void set(float val) { fEntry2 = val; }
				public float get() { return (float)fEntry2; }
			}
			, 9000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider1", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("peak 9");
		ui_interface.declare("fEntry1", "style", "knob");
		ui_interface.addNumEntry("Q factor", new FaustVarAccess() {
				public String getId() { return "fEntry1"; }
				public void set(float val) { fEntry1 = val; }
				public float get() { return (float)fEntry1; }
			}
			, 50.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fEntry0", "style", "knob");
		ui_interface.declare("fEntry0", "unit", "Hz");
		ui_interface.addNumEntry("freq", new FaustVarAccess() {
				public String getId() { return "fEntry0"; }
				public void set(float val) { fEntry0 = val; }
				public float get() { return (float)fEntry0; }
			}
			, 10000.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.0f, -50.0f, 50.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = (float)java.lang.Math.tan((fConst0 * fEntry0));
		float fSlow1 = fEntry1;
		float fSlow2 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider0))) / fSlow1);
		float fSlow3 = (1.0f / ((fSlow0 * (fSlow0 + fSlow2)) + 1.0f));
		float fSlow4 = (2.0f * (mydsp_faustpower2_f(fSlow0) + -1.0f));
		float fSlow5 = (float)java.lang.Math.tan((fConst0 * fEntry2));
		float fSlow6 = fEntry3;
		float fSlow7 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider1))) / fSlow6);
		float fSlow8 = (1.0f / ((fSlow5 * (fSlow5 + fSlow7)) + 1.0f));
		float fSlow9 = (2.0f * (mydsp_faustpower2_f(fSlow5) + -1.0f));
		float fSlow10 = (float)java.lang.Math.tan((fConst0 * fEntry4));
		float fSlow11 = fEntry5;
		float fSlow12 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider2))) / fSlow11);
		float fSlow13 = (1.0f / ((fSlow10 * (fSlow10 + fSlow12)) + 1.0f));
		float fSlow14 = (2.0f * (mydsp_faustpower2_f(fSlow10) + -1.0f));
		float fSlow15 = (float)java.lang.Math.tan((fConst0 * fEntry6));
		float fSlow16 = fEntry7;
		float fSlow17 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider3))) / fSlow16);
		float fSlow18 = (1.0f / ((fSlow15 * (fSlow15 + fSlow17)) + 1.0f));
		float fSlow19 = (2.0f * (mydsp_faustpower2_f(fSlow15) + -1.0f));
		float fSlow20 = (float)java.lang.Math.tan((fConst0 * fEntry8));
		float fSlow21 = fEntry9;
		float fSlow22 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider4))) / fSlow21);
		float fSlow23 = (1.0f / ((fSlow20 * (fSlow20 + fSlow22)) + 1.0f));
		float fSlow24 = (2.0f * (mydsp_faustpower2_f(fSlow20) + -1.0f));
		float fSlow25 = (float)java.lang.Math.tan((fConst0 * fEntry10));
		float fSlow26 = fEntry11;
		float fSlow27 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider5))) / fSlow26);
		float fSlow28 = (1.0f / ((fSlow25 * (fSlow25 + fSlow27)) + 1.0f));
		float fSlow29 = (2.0f * (mydsp_faustpower2_f(fSlow25) + -1.0f));
		float fSlow30 = (float)java.lang.Math.tan((fConst0 * fEntry12));
		float fSlow31 = fEntry13;
		float fSlow32 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider6))) / fSlow31);
		float fSlow33 = (1.0f / ((fSlow30 * (fSlow30 + fSlow32)) + 1.0f));
		float fSlow34 = (2.0f * (mydsp_faustpower2_f(fSlow30) + -1.0f));
		float fSlow35 = (float)java.lang.Math.tan((fConst0 * fEntry14));
		float fSlow36 = fEntry15;
		float fSlow37 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider7))) / fSlow36);
		float fSlow38 = (1.0f / ((fSlow35 * (fSlow35 + fSlow37)) + 1.0f));
		float fSlow39 = (2.0f * (mydsp_faustpower2_f(fSlow35) + -1.0f));
		float fSlow40 = (float)java.lang.Math.tan((fConst0 * fEntry16));
		float fSlow41 = fEntry17;
		float fSlow42 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider8))) / fSlow41);
		float fSlow43 = (1.0f / ((fSlow40 * (fSlow40 + fSlow42)) + 1.0f));
		float fSlow44 = (2.0f * (mydsp_faustpower2_f(fSlow40) + -1.0f));
		float fSlow45 = (float)java.lang.Math.tan((fConst0 * fEntry18));
		float fSlow46 = fEntry19;
		float fSlow47 = ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (0.0f - fVslider9))) / fSlow46);
		float fSlow48 = (1.0f / ((fSlow45 * (fSlow45 + fSlow47)) + 1.0f));
		float fSlow49 = (2.0f * (mydsp_faustpower2_f(fSlow45) + -1.0f));
		float fSlow50 = ((fSlow45 * (fSlow45 - fSlow47)) + 1.0f);
		float fSlow51 = (1.0f / fSlow46);
		float fSlow52 = ((fSlow45 * (fSlow45 + fSlow51)) + 1.0f);
		float fSlow53 = (1.0f - (fSlow45 * (fSlow51 - fSlow45)));
		float fSlow54 = ((fSlow40 * (fSlow40 - fSlow42)) + 1.0f);
		float fSlow55 = (1.0f / fSlow41);
		float fSlow56 = ((fSlow40 * (fSlow40 + fSlow55)) + 1.0f);
		float fSlow57 = (1.0f - (fSlow40 * (fSlow55 - fSlow40)));
		float fSlow58 = ((fSlow35 * (fSlow35 - fSlow37)) + 1.0f);
		float fSlow59 = (1.0f / fSlow36);
		float fSlow60 = ((fSlow35 * (fSlow35 + fSlow59)) + 1.0f);
		float fSlow61 = (1.0f - (fSlow35 * (fSlow59 - fSlow35)));
		float fSlow62 = ((fSlow30 * (fSlow30 - fSlow32)) + 1.0f);
		float fSlow63 = (1.0f / fSlow31);
		float fSlow64 = ((fSlow30 * (fSlow30 + fSlow63)) + 1.0f);
		float fSlow65 = (1.0f - (fSlow30 * (fSlow63 - fSlow30)));
		float fSlow66 = ((fSlow25 * (fSlow25 - fSlow27)) + 1.0f);
		float fSlow67 = (1.0f / fSlow26);
		float fSlow68 = ((fSlow25 * (fSlow25 + fSlow67)) + 1.0f);
		float fSlow69 = (1.0f - (fSlow25 * (fSlow67 - fSlow25)));
		float fSlow70 = ((fSlow20 * (fSlow20 - fSlow22)) + 1.0f);
		float fSlow71 = (1.0f / fSlow21);
		float fSlow72 = ((fSlow20 * (fSlow20 + fSlow71)) + 1.0f);
		float fSlow73 = (1.0f - (fSlow20 * (fSlow71 - fSlow20)));
		float fSlow74 = ((fSlow15 * (fSlow15 - fSlow17)) + 1.0f);
		float fSlow75 = (1.0f / fSlow16);
		float fSlow76 = ((fSlow15 * (fSlow15 + fSlow75)) + 1.0f);
		float fSlow77 = (1.0f - (fSlow15 * (fSlow75 - fSlow15)));
		float fSlow78 = ((fSlow10 * (fSlow10 - fSlow12)) + 1.0f);
		float fSlow79 = (1.0f / fSlow11);
		float fSlow80 = ((fSlow10 * (fSlow10 + fSlow79)) + 1.0f);
		float fSlow81 = (1.0f - (fSlow10 * (fSlow79 - fSlow10)));
		float fSlow82 = ((fSlow5 * (fSlow5 - fSlow7)) + 1.0f);
		float fSlow83 = (1.0f / fSlow6);
		float fSlow84 = ((fSlow5 * (fSlow5 + fSlow83)) + 1.0f);
		float fSlow85 = (1.0f - (fSlow5 * (fSlow83 - fSlow5)));
		float fSlow86 = ((fSlow0 * (fSlow0 - fSlow2)) + 1.0f);
		float fSlow87 = (1.0f / fSlow1);
		float fSlow88 = ((fSlow0 * (fSlow0 + fSlow87)) + 1.0f);
		float fSlow89 = (1.0f - (fSlow0 * (fSlow87 - fSlow0)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (fSlow49 * fRec9[1]);
			fRec9[0] = (input0[i] - (fSlow48 * ((fSlow50 * fRec9[2]) + fTemp0)));
			float fTemp1 = (fSlow44 * fRec8[1]);
			fRec8[0] = ((fSlow48 * ((fTemp0 + (fSlow52 * fRec9[0])) + (fSlow53 * fRec9[2]))) - (fSlow43 * ((fSlow54 * fRec8[2]) + fTemp1)));
			float fTemp2 = (fSlow39 * fRec7[1]);
			fRec7[0] = ((fSlow43 * ((fTemp1 + (fSlow56 * fRec8[0])) + (fSlow57 * fRec8[2]))) - (fSlow38 * ((fSlow58 * fRec7[2]) + fTemp2)));
			float fTemp3 = (fSlow34 * fRec6[1]);
			fRec6[0] = ((fSlow38 * ((fTemp2 + (fSlow60 * fRec7[0])) + (fSlow61 * fRec7[2]))) - (fSlow33 * ((fSlow62 * fRec6[2]) + fTemp3)));
			float fTemp4 = (fSlow29 * fRec5[1]);
			fRec5[0] = ((fSlow33 * ((fTemp3 + (fSlow64 * fRec6[0])) + (fSlow65 * fRec6[2]))) - (fSlow28 * ((fSlow66 * fRec5[2]) + fTemp4)));
			float fTemp5 = (fSlow24 * fRec4[1]);
			fRec4[0] = ((fSlow28 * ((fTemp4 + (fSlow68 * fRec5[0])) + (fSlow69 * fRec5[2]))) - (fSlow23 * ((fSlow70 * fRec4[2]) + fTemp5)));
			float fTemp6 = (fSlow19 * fRec3[1]);
			fRec3[0] = ((fSlow23 * ((fTemp5 + (fSlow72 * fRec4[0])) + (fSlow73 * fRec4[2]))) - (fSlow18 * ((fSlow74 * fRec3[2]) + fTemp6)));
			float fTemp7 = (fSlow14 * fRec2[1]);
			fRec2[0] = ((fSlow18 * ((fTemp6 + (fSlow76 * fRec3[0])) + (fSlow77 * fRec3[2]))) - (fSlow13 * ((fSlow78 * fRec2[2]) + fTemp7)));
			float fTemp8 = (fSlow9 * fRec1[1]);
			fRec1[0] = ((fSlow13 * ((fTemp7 + (fSlow80 * fRec2[0])) + (fSlow81 * fRec2[2]))) - (fSlow8 * ((fSlow82 * fRec1[2]) + fTemp8)));
			float fTemp9 = (fSlow4 * fRec0[1]);
			fRec0[0] = ((fSlow8 * ((fTemp8 + (fSlow84 * fRec1[0])) + (fSlow85 * fRec1[2]))) - (fSlow3 * ((fSlow86 * fRec0[2]) + fTemp9)));
			output0[i] = (fSlow3 * ((fTemp9 + (fSlow88 * fRec0[0])) + (fSlow89 * fRec0[2])));
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

