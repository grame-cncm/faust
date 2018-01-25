/* ------------------------------------------------------------
name: "clarinet"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int iRec6[] = new int[2];
	float fRec13[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec18[] = new float[2];
	float fRec17[] = new float[2];
	float fRec14[] = new float[2];
	float fHslider0;
	float fRec19[] = new float[2];
	int IOTA;
	float fRec15[] = new float[2048];
	float fConst3;
	float fConst4;
	float fHslider1;
	float fHslider2;
	float fHslider3;
	float fHslider4;
	float fHslider5;
	float fHslider6;
	float fHslider7;
	float fHslider8;
	int iVec0[] = new int[2];
	int iRec21[] = new int[2];
	float fHslider9;
	int iVec1[] = new int[2];
	int iRec22[] = new int[2];
	float fRec20[] = new float[2];
	float fVec2[] = new float[2];
	float fRec11[] = new float[2];
	float fRec2[] = new float[2048];
	float fRec0[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'4',   'Keyboard 1 - Number of Keys':'5',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Key 3 - Label':'O+',  'Keyboard 1 - Key 4 - Label':'O-' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "clarinet");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	int getNumInputs() {
		return 1;
		
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
		fConst1 = (float)java.lang.Math.exp((0.0f - (50.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = (0.00882352982f * fConst0);
		fConst4 = (0.00147058826f * fConst0);
		
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
		fHslider8 = (float)0.0f;
		fHslider9 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec6[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec13[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec18[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec17[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec14[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec19[l5] = 0.0f;
			
		}
		IOTA = 0;
		for (int l6 = 0; (l6 < 2048); l6 = (l6 + 1)) {
			fRec15[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iVec0[l7] = 0;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec21[l8] = 0;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iVec1[l9] = 0;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			iRec22[l10] = 0;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec20[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fRec2[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec0[l15] = 0.0f;
			
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
		ui_interface.openVerticalBox("clarinet");
		ui_interface.addHorizontalSlider("kb0k0status", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb0k1status", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb0k2status", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb0k3status", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1k0status", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1k1status", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1k2status", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1k3status", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb1k4status", new FaustVarAccess() {
				public String getId() { return "fHslider9"; }
				public void set(float val) { fHslider9 = val; }
				public float get() { return (float)fHslider9; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.declare("fHslider0", "acc", "1 1 -10 0 10");
		ui_interface.addHorizontalSlider("reedStiffness", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * fHslider0);
		int iSlow1 = (int)(float)java.lang.Math.min(1.0f, fHslider1);
		int iSlow2 = (iSlow1 == 1);
		int iSlow3 = (int)(float)java.lang.Math.min(1.0f, fHslider2);
		int iSlow4 = (iSlow3 == 1);
		int iSlow5 = (iSlow2 & iSlow4);
		int iSlow6 = (int)(float)java.lang.Math.min(1.0f, fHslider3);
		int iSlow7 = (iSlow6 == 0);
		int iSlow8 = (iSlow5 & iSlow7);
		int iSlow9 = (int)(float)java.lang.Math.min(1.0f, fHslider4);
		int iSlow10 = (iSlow9 == 0);
		int iSlow11 = (int)(float)java.lang.Math.min(1.0f, fHslider5);
		int iSlow12 = (iSlow11 == 0);
		int iSlow13 = (int)(float)java.lang.Math.min(1.0f, fHslider6);
		int iSlow14 = (iSlow13 == 0);
		int iSlow15 = (int)(float)java.lang.Math.min(1.0f, fHslider7);
		int iSlow16 = (iSlow15 == 0);
		float fSlow17 = (4.0f * (1.0f - (float)((((iSlow8 & iSlow10) & iSlow12) & iSlow14) & iSlow16)));
		int iSlow18 = (iSlow6 == 1);
		int iSlow19 = (iSlow5 & iSlow18);
		int iSlow20 = (iSlow9 == 1);
		int iSlow21 = (iSlow19 & iSlow20);
		int iSlow22 = (iSlow11 == 1);
		int iSlow23 = (iSlow21 & iSlow22);
		int iSlow24 = (iSlow23 & (((iSlow13 == 1))?1:0));
		int iSlow25 = (iSlow15 == 1);
		int iSlow26 = (iSlow23 & iSlow14);
		int iSlow27 = (iSlow19 & iSlow10);
		int iSlow28 = (iSlow1 == 0);
		int iSlow29 = (iSlow3 == 0);
		int iSlow30 = (iSlow2 & iSlow29);
		int iSlow31 = ((13 * (iSlow24 & iSlow25)) + ((11 * (iSlow24 & iSlow16)) + ((10 * (iSlow26 & iSlow25)) + ((9 * (iSlow26 & iSlow16)) + ((8 * (((iSlow21 & iSlow12) & iSlow14) & iSlow16)) + ((7 * (((iSlow27 & iSlow22) & iSlow14) & iSlow16)) + ((6 * (((iSlow27 & iSlow12) & iSlow14) & iSlow16)) + (((((((((iSlow28 & iSlow4) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16) + (2 * (((((iSlow30 & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (3 * (((((iSlow30 & iSlow18) & iSlow10) & iSlow12) & iSlow14) & iSlow16))) + (5 * ((((iSlow8 & iSlow20) & iSlow12) & iSlow14) & iSlow16))))))))));
		int iSlow32 = ((((((iSlow28 & iSlow29) & iSlow7) & iSlow10) & iSlow12) & iSlow14) & iSlow25);
		int iSlow33 = (int)(float)java.lang.Math.min(1.0f, fHslider8);
		int iSlow34 = (int)(float)java.lang.Math.min(1.0f, fHslider9);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = 0;
			fRec13[0] = (0.5f * (fRec13[1] + fRec11[1]));
			float fRec10 = (fRec13[0] + (float)iRec6[1]);
			float fTemp0 = (float)java.lang.Math.abs(input0[i]);
			fRec18[0] = (float)java.lang.Math.max(fTemp0, ((fConst1 * fRec18[1]) + (fConst2 * fTemp0)));
			fRec17[0] = ((fConst1 * fRec17[1]) + (fConst2 * fRec18[0]));
			float fTemp1 = (0.699999988f * fRec17[0]);
			fRec14[0] = (fRec0[1] + fTemp1);
			float fTemp2 = (0.0f - fRec14[1]);
			fRec19[0] = (fSlow0 + (0.999000013f * fRec19[1]));
			fRec15[(IOTA & 2047)] = (fTemp1 + (fTemp2 * (float)java.lang.Math.max(-1.0f, (float)java.lang.Math.min(1.0f, ((fTemp2 * ((0.25999999f * fRec19[0]) + -0.439999998f)) + 0.699999988f)))));
			int iRec16 = 0;
			iVec0[0] = iSlow33;
			iRec21[0] = (((((iSlow33 - iVec0[1]) > 0))?1:0) + iRec21[1]);
			iVec1[0] = iSlow34;
			iRec22[0] = (((((iSlow34 - iVec1[1]) > 0))?1:0) + iRec22[1]);
			fRec20[0] = ((0.999000013f * fRec20[1]) + (0.000772727246f / (float)java.lang.Math.pow(2.0f, (0.0833333358f * (fSlow17 - (float)(iSlow31 + (12 * (iSlow32 - (iRec21[0] - iRec22[0])))))))));
			float fTemp3 = (fConst4 * ((0.5f * fRec20[0]) + -0.0500000007f));
			float fTemp4 = (fTemp3 + -1.49999499f);
			int iTemp5 = (int)fTemp4;
			int iTemp6 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, iTemp5)) + 1);
			float fTemp7 = (float)java.lang.Math.floor(fTemp4);
			float fTemp8 = (fTemp3 + (-1.0f - fTemp7));
			float fTemp9 = (0.0f - fTemp8);
			float fTemp10 = (fTemp3 + (-2.0f - fTemp7));
			float fTemp11 = (0.0f - (0.5f * fTemp10));
			float fTemp12 = (fTemp3 + (-3.0f - fTemp7));
			float fTemp13 = (0.0f - (0.333333343f * fTemp12));
			float fTemp14 = (fTemp3 + (-4.0f - fTemp7));
			float fTemp15 = (0.0f - (0.25f * fTemp14));
			float fTemp16 = (fTemp3 - fTemp7);
			int iTemp17 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 2))) + 1);
			float fTemp18 = (0.0f - fTemp12);
			float fTemp19 = (0.0f - (0.5f * fTemp14));
			int iTemp20 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 1))) + 1);
			float fTemp21 = (0.0f - fTemp10);
			float fTemp22 = (0.0f - (0.5f * fTemp12));
			float fTemp23 = (0.0f - (0.333333343f * fTemp14));
			float fTemp24 = (fTemp8 * fTemp10);
			int iTemp25 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 3))) + 1);
			float fTemp26 = (0.0f - fTemp14);
			float fTemp27 = (fTemp24 * fTemp12);
			int iTemp28 = ((int)(float)java.lang.Math.min(fConst3, (float)java.lang.Math.max(0, (iTemp5 + 4))) + 1);
			fVec2[0] = (((((fRec15[((IOTA - iTemp6) & 2047)] * fTemp9) * fTemp11) * fTemp13) * fTemp15) + (fTemp16 * ((((0.5f * (((fTemp8 * fRec15[((IOTA - iTemp17) & 2047)]) * fTemp18) * fTemp19)) + (((fRec15[((IOTA - iTemp20) & 2047)] * fTemp21) * fTemp22) * fTemp23)) + (0.166666672f * ((fTemp24 * fRec15[((IOTA - iTemp25) & 2047)]) * fTemp26))) + (0.0416666679f * (fTemp27 * fRec15[((IOTA - iTemp28) & 2047)])))));
			fRec11[0] = fVec2[1];
			int iRec12 = iRec16;
			float fRec7 = fRec10;
			float fRec8 = fRec11[0];
			float fRec9 = (fRec11[0] + (float)iRec12);
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = (((((fTemp9 * fTemp11) * fTemp13) * fTemp15) * fRec2[((IOTA - iTemp6) & 2047)]) + (fTemp16 * (((0.166666672f * ((fTemp24 * fTemp26) * fRec2[((IOTA - iTemp25) & 2047)])) + ((((fTemp21 * fTemp22) * fTemp23) * fRec2[((IOTA - iTemp20) & 2047)]) + (0.5f * (((fTemp8 * fTemp18) * fTemp19) * fRec2[((IOTA - iTemp17) & 2047)])))) + (0.0416666679f * (fTemp27 * fRec2[((IOTA - iTemp28) & 2047)])))));
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i] = fRec1;
			output1[i] = fRec1;
			iRec6[1] = iRec6[0];
			fRec13[1] = fRec13[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec14[1] = fRec14[0];
			fRec19[1] = fRec19[0];
			IOTA = (IOTA + 1);
			iVec0[1] = iVec0[0];
			iRec21[1] = iRec21[0];
			iVec1[1] = iVec1[0];
			iRec22[1] = iRec22[0];
			fRec20[1] = fRec20[0];
			fVec2[1] = fVec2[0];
			fRec11[1] = fRec11[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}
	
};

