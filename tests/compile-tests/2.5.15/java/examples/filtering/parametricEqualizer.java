/* ------------------------------------------------------------
name: "parametricEqualizer"
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
	float fHslider0;
	float fHslider1;
	float fVec0[] = new float[2];
	float fRec4[] = new float[2];
	float fRec3[] = new float[3];
	float fHslider2;
	float fRec6[] = new float[2];
	float fRec5[] = new float[3];
	float fConst2;
	float fHslider3;
	float fRec7[] = new float[2];
	float fHslider4;
	float fConst3;
	float fConst4;
	float fHslider5;
	float fConst5;
	float fRec2[] = new float[3];
	float fVec1[] = new float[2];
	float fRec1[] = new float[2];
	float fRec0[] = new float[3];
	float fHslider6;
	float fRec9[] = new float[2];
	float fRec8[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Exercise and compare Parametric Equalizer sections on test signals");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "parametricEqualizer");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (1382.30078f / fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (1382.30078f * fConst3);
		fConst5 = (2764.60156f * fConst3);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)8000.0f;
		fHslider1 = (float)200.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)49.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)40.0f;
		fHslider6 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec4[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec6[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec7[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec2[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec1[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec9[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec8[l11] = 0.0f;
			
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
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib   for info and pointers");
		ui_interface.openHorizontalBox("PARAMETRIC EQ SECTIONS");
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Low Shelf");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "Amount of low-frequency boost or cut in decibels");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("Low Boost|Cut", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface.declare("fHslider1", "1", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface.declare("fHslider1", "unit", "Hz");
		ui_interface.addHorizontalSlider("Transition Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 200.0f, 1.0f, 5000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.declare("0", "tooltip", "Parametric Equalizer   sections from filters.lib");
		ui_interface.openVerticalBox("Peaking Equalizer");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "Amount of   local boost or cut in decibels");
		ui_interface.declare("fHslider4", "unit", "dB");
		ui_interface.addHorizontalSlider("Peak Boost|Cut", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Peak   Frequency in Piano Key (PK) units (A440 = 49PK)");
		ui_interface.declare("fHslider3", "unit", "PK");
		ui_interface.addHorizontalSlider("Peak Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 49.0f, 1.0f, 100.0f, 1.0f);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "scale", "log");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "tooltip", "Quality factor   (Q) of the peak = center-frequency/bandwidth");
		ui_interface.addHorizontalSlider("Peak Q", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 40.0f, 1.0f, 1000.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.declare("0", "tooltip", "A high shelf provides a boost   or cut above some frequency");
		ui_interface.openVerticalBox("High Shelf");
		ui_interface.declare("fHslider6", "0", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "Amount of   high-frequency boost or cut in decibels");
		ui_interface.declare("fHslider6", "unit", "dB");
		ui_interface.addHorizontalSlider("High Boost|Cut", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "scale", "log");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface.declare("fHslider0", "unit", "Hz");
		ui_interface.addHorizontalSlider("Transition Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 8000.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float fSlow0 = (float)java.lang.Math.tan((fConst1 * fHslider0));
		float fSlow1 = (1.0f / fSlow0);
		float fSlow2 = (1.0f / (((fSlow1 + 1.0f) / fSlow0) + 1.0f));
		float fSlow3 = (fSlow1 + 1.0f);
		float fSlow4 = (0.0f - ((1.0f - fSlow1) / fSlow3));
		float fSlow5 = (1.0f / fSlow3);
		float fSlow6 = (float)java.lang.Math.tan((fConst1 * fHslider1));
		float fSlow7 = (1.0f / fSlow6);
		float fSlow8 = (1.0f / (((fSlow7 + 1.0f) / fSlow6) + 1.0f));
		float fSlow9 = (1.0f / mydsp_faustpower2_f(fSlow6));
		float fSlow10 = (fSlow7 + 1.0f);
		float fSlow11 = (0.0f - ((1.0f - fSlow7) / fSlow10));
		float fSlow12 = (1.0f / fSlow10);
		float fSlow13 = (0.0f - fSlow7);
		float fSlow14 = (2.0f * (1.0f - fSlow9));
		float fSlow15 = (((fSlow7 + -1.0f) / fSlow6) + 1.0f);
		float fSlow16 = (2.0f * (0.0f - fSlow9));
		float fSlow17 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider2));
		float fSlow18 = (0.00100000005f * fHslider3);
		float fSlow19 = fHslider4;
		int iSlow20 = (fSlow19 > 0.0f);
		float fSlow21 = fHslider5;
		float fSlow22 = (fConst4 * ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (float)java.lang.Math.abs(fSlow19))) / fSlow21));
		float fSlow23 = (fConst4 / fSlow21);
		float fSlow24 = (1.0f / mydsp_faustpower2_f(fSlow0));
		float fSlow25 = (2.0f * (1.0f - fSlow24));
		float fSlow26 = (((fSlow1 + -1.0f) / fSlow0) + 1.0f);
		float fSlow27 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider6));
		float fSlow28 = (0.0f - fSlow1);
		float fSlow29 = (2.0f * (0.0f - fSlow24));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			fVec0[0] = fTemp0;
			fRec4[0] = ((fSlow11 * fRec4[1]) + (fSlow12 * ((fSlow7 * fTemp0) + (fSlow13 * fVec0[1]))));
			fRec3[0] = (fRec4[0] - (fSlow8 * ((fSlow14 * fRec3[1]) + (fSlow15 * fRec3[2]))));
			fRec6[0] = ((fSlow11 * fRec6[1]) + (fSlow12 * (fTemp0 + fVec0[1])));
			fRec5[0] = (fRec6[0] - (fSlow8 * ((fSlow14 * fRec5[1]) + (fSlow15 * fRec5[2]))));
			fRec7[0] = (fSlow18 + (0.999000013f * fRec7[1]));
			float fTemp1 = (float)java.lang.Math.pow(2.0f, (0.0833333358f * (fRec7[0] + -49.0f)));
			float fTemp2 = (float)java.lang.Math.tan((fConst2 * fTemp1));
			float fTemp3 = (1.0f / fTemp2);
			float fTemp4 = (fTemp1 / (float)java.lang.Math.sin((fConst5 * fTemp1)));
			float fTemp5 = (fSlow22 * fTemp4);
			float fTemp6 = (fSlow23 * fTemp4);
			float fTemp7 = (((iSlow20==0)?true:false)?fTemp6:fTemp5);
			float fTemp8 = (2.0f * (fRec2[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp2)))));
			float fTemp9 = (((fTemp3 + fTemp7) / fTemp2) + 1.0f);
			fRec2[0] = ((fSlow8 * ((((fSlow9 * fRec3[0]) + (fSlow16 * fRec3[1])) + (fSlow9 * fRec3[2])) + (fSlow17 * (fRec5[2] + (fRec5[0] + (2.0f * fRec5[1])))))) - (((fRec2[2] * (((fTemp3 - fTemp7) / fTemp2) + 1.0f)) + fTemp8) / fTemp9));
			float fTemp10 = (((iSlow20==0)?true:false)?fTemp5:fTemp6);
			float fTemp11 = (((fTemp8 + (fRec2[0] * (((fTemp3 + fTemp10) / fTemp2) + 1.0f))) + (fRec2[2] * (((fTemp3 - fTemp10) / fTemp2) + 1.0f))) / fTemp9);
			fVec1[0] = fTemp11;
			fRec1[0] = ((fSlow4 * fRec1[1]) + (fSlow5 * (fVec1[1] + fTemp11)));
			fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow25 * fRec0[1]) + (fSlow26 * fRec0[2]))));
			fRec9[0] = ((fSlow4 * fRec9[1]) + (fSlow5 * ((fSlow28 * fVec1[1]) + (fSlow1 * fTemp11))));
			fRec8[0] = (fRec9[0] - (fSlow2 * ((fSlow25 * fRec8[1]) + (fSlow26 * fRec8[2]))));
			output0[i] = (fSlow2 * ((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) + (fSlow27 * (((fSlow24 * fRec8[0]) + (fSlow29 * fRec8[1])) + (fSlow24 * fRec8[2])))));
			fVec0[1] = fVec0[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec7[1] = fRec7[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			
		}
		
	}
	
};

