/* ------------------------------------------------------------
name: "bowed"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	
	int iVec0[] = new int[2];
	float fHslider0;
	float fRec2[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec1[] = new float[2];
	float fRec0[] = new float[2];
	float fConst3;
	float fHslider1;
	float fHslider2;
	float fHslider3;
	float fRec6[] = new float[2];
	float fRec5[] = new float[2];
	float fHslider4;
	float fRec9[] = new float[2];
	float fRec7[] = new float[2];
	float fRec8[] = new float[2];
	float fRec12[] = new float[2];
	float fRec11[] = new float[2];
	float fRec10[] = new float[2];
	float fRec3[] = new float[2];
	float fRec4[] = new float[2];
	float fRec16[] = new float[2];
	float fRec15[] = new float[2];
	float fRec17[] = new float[2];
	float fRec18[] = new float[2];
	float fRec13[] = new float[2];
	float fRec14[] = new float[2];
	float fRec22[] = new float[2];
	float fRec21[] = new float[2];
	float fRec23[] = new float[2];
	float fRec24[] = new float[2];
	float fRec19[] = new float[2];
	float fRec20[] = new float[2];
	float fRec28[] = new float[2];
	float fRec27[] = new float[2];
	float fRec29[] = new float[2];
	float fRec30[] = new float[2];
	float fRec25[] = new float[2];
	float fRec26[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'5',  'Max Keyboard Polyphony':'0',  'Rounding Mode':'1',  'Keyboard 0 - Number of Keys':'19',  'Keyboard 1 - Number of Keys':'19',  'Keyboard 2 - Number of Keys':'19',  'Keyboard 3 - Number of Keys':'19',  'Keyboard 4 - Number of Keys':'1',  'Keyboard 4 - Send Freq':'0',  'Keyboard 0 - Send X':'0',  'Keyboard 1 - Send X':'0',  'Keyboard 2 - Send X':'0',  'Keyboard 3 - Send X':'0',  'Keyboard 0 - Send Y':'0',  'Keyboard 1 - Send Y':'0',  'Keyboard 2 - Send Y':'0',  'Keyboard 3 - Send Y':'0',  'Keyboard 0 - Lowest Key':'55',  'Keyboard 1 - Lowest Key':'62',  'Keyboard 2 - Lowest Key':'69',  'Keyboard 3 - Lowest Key':'76',  'Keyboard 4 - Piano Keyboard':'0',  'Keyboard 4 - Key 0 - Label':'Bow' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "bowed");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("synths.lib/name", "Faust Synthesizer Library");
		m.declare("synths.lib/version", "0.0");
	}

	int getNumInputs() {
		return 0;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
		fConst1 = (float)java.lang.Math.exp((0.0f - (10.0f / fConst0)));
		fConst2 = (float)java.lang.Math.exp((0.0f - (1.0f / fConst0)));
		fConst3 = (6.28318548f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)400.0f;
		fHslider3 = (float)1.0f;
		fHslider4 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec6[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec9[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec12[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec11[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec10[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec3[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec15[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec17[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec18[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec13[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec14[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec22[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec21[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec23[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec24[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec19[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec20[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec28[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec27[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec29[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec30[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec25[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec26[l31] = 0.0f;
			
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
		ui_interface.openVerticalBox("bowed");
		ui_interface.addHorizontalSlider("bend", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 400.0f, 50.0f, 2000.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("keyboard", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 5.0f, 1.0f);
		ui_interface.addHorizontalSlider("x", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("y", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (0.00100000005f * fHslider0);
		int iSlow1 = (int)fHslider1;
		int iSlow2 = (iSlow1 == 3);
		float fSlow3 = (fHslider2 * fHslider3);
		float fSlow4 = (0.00100000005f * fHslider4);
		int iSlow5 = (iSlow1 == 2);
		int iSlow6 = (iSlow1 == 0);
		int iSlow7 = (iSlow1 == 1);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec2[0] = (fSlow0 + (0.999000013f * fRec2[1]));
			float fTemp0 = (float)java.lang.Math.abs((float)java.lang.Math.abs((fRec2[0] - fRec2[1])));
			float fTemp1 = (((fRec0[1] > fTemp0))?fConst2:fConst1);
			fRec1[0] = ((fRec1[1] * fTemp1) + (fTemp0 * (1.0f - fTemp1)));
			fRec0[0] = fRec1[0];
			fRec6[0] = (((iSlow2==0)?true:false)?fSlow3:fRec6[1]);
			fRec5[0] = ((0.999000013f * fRec5[1]) + (0.00100000005f * fRec6[0]));
			fRec9[0] = (fSlow4 + (0.999000013f * fRec9[1]));
			float fTemp2 = ((0.300000012f * fRec9[0]) + 1.0f);
			float fTemp3 = (fConst3 * (fRec5[0] * fTemp2));
			float fTemp4 = (float)java.lang.Math.sin(fTemp3);
			float fTemp5 = (float)java.lang.Math.cos(fTemp3);
			fRec7[0] = ((fRec8[1] * fTemp4) + (fRec7[1] * fTemp5));
			int iTemp6 = (1 - iVec0[1]);
			fRec8[0] = (((fRec8[1] * fTemp5) + (fRec7[1] * (0.0f - fTemp4))) + (float)iTemp6);
			fRec12[0] = (fSlow0 + (0.999000013f * fRec12[1]));
			float fTemp7 = (float)java.lang.Math.abs((float)java.lang.Math.abs((fRec12[0] - fRec12[1])));
			float fTemp8 = (((fRec10[1] > fTemp7))?fConst2:fConst1);
			fRec11[0] = ((fRec11[1] * fTemp8) + (fTemp7 * (1.0f - fTemp8)));
			fRec10[0] = fRec11[0];
			float fTemp9 = (float)java.lang.Math.min(1.0f, (8000.0f * fRec10[0]));
			float fTemp10 = (fConst3 * (fRec5[0] + (1000.0f * (fRec7[0] * fTemp9))));
			float fTemp11 = (float)java.lang.Math.sin(fTemp10);
			float fTemp12 = (float)java.lang.Math.cos(fTemp10);
			fRec3[0] = ((fRec4[1] * fTemp11) + (fRec3[1] * fTemp12));
			fRec4[0] = (((fRec4[1] * fTemp12) + (fRec3[1] * (0.0f - fTemp11))) + (float)iTemp6);
			fRec16[0] = (((iSlow5==0)?true:false)?fSlow3:fRec16[1]);
			fRec15[0] = ((0.999000013f * fRec15[1]) + (0.00100000005f * fRec16[0]));
			float fTemp13 = (fConst3 * (fRec15[0] * fTemp2));
			float fTemp14 = (float)java.lang.Math.sin(fTemp13);
			float fTemp15 = (float)java.lang.Math.cos(fTemp13);
			fRec17[0] = ((fRec18[1] * fTemp14) + (fRec17[1] * fTemp15));
			fRec18[0] = (((fRec18[1] * fTemp15) + (fRec17[1] * (0.0f - fTemp14))) + (float)iTemp6);
			float fTemp16 = (fConst3 * (fRec15[0] + (1000.0f * (fRec17[0] * fTemp9))));
			float fTemp17 = (float)java.lang.Math.sin(fTemp16);
			float fTemp18 = (float)java.lang.Math.cos(fTemp16);
			fRec13[0] = ((fRec14[1] * fTemp17) + (fRec13[1] * fTemp18));
			fRec14[0] = (((fRec14[1] * fTemp18) + (fRec13[1] * (0.0f - fTemp17))) + (float)iTemp6);
			fRec22[0] = (((iSlow6==0)?true:false)?fSlow3:fRec22[1]);
			fRec21[0] = ((0.999000013f * fRec21[1]) + (0.00100000005f * fRec22[0]));
			float fTemp19 = (fConst3 * (fRec21[0] * fTemp2));
			float fTemp20 = (float)java.lang.Math.sin(fTemp19);
			float fTemp21 = (float)java.lang.Math.cos(fTemp19);
			fRec23[0] = ((fRec24[1] * fTemp20) + (fRec23[1] * fTemp21));
			fRec24[0] = (((fRec24[1] * fTemp21) + (fRec23[1] * (0.0f - fTemp20))) + (float)iTemp6);
			float fTemp22 = (fConst3 * (fRec21[0] + (1000.0f * (fRec23[0] * fTemp9))));
			float fTemp23 = (float)java.lang.Math.sin(fTemp22);
			float fTemp24 = (float)java.lang.Math.cos(fTemp22);
			fRec19[0] = ((fRec20[1] * fTemp23) + (fRec19[1] * fTemp24));
			fRec20[0] = (((fRec20[1] * fTemp24) + (fRec19[1] * (0.0f - fTemp23))) + (float)iTemp6);
			fRec28[0] = (((iSlow7==0)?true:false)?fSlow3:fRec28[1]);
			fRec27[0] = ((0.999000013f * fRec27[1]) + (0.00100000005f * fRec28[0]));
			float fTemp25 = (fConst3 * (fRec27[0] * fTemp2));
			float fTemp26 = (float)java.lang.Math.sin(fTemp25);
			float fTemp27 = (float)java.lang.Math.cos(fTemp25);
			fRec29[0] = ((fRec30[1] * fTemp26) + (fRec29[1] * fTemp27));
			fRec30[0] = (((fRec30[1] * fTemp27) + (fRec29[1] * (0.0f - fTemp26))) + (float)iTemp6);
			float fTemp28 = (fConst3 * (fRec27[0] + (1000.0f * (fRec29[0] * fTemp9))));
			float fTemp29 = (float)java.lang.Math.sin(fTemp28);
			float fTemp30 = (float)java.lang.Math.cos(fTemp28);
			fRec25[0] = ((fRec26[1] * fTemp29) + (fRec25[1] * fTemp30));
			fRec26[0] = (((fRec26[1] * fTemp30) + (fRec25[1] * (0.0f - fTemp29))) + (float)iTemp6);
			float fTemp31 = ((float)java.lang.Math.min(1.0f, (8000.0f * fRec0[0])) * (fRec3[0] + (fRec13[0] + (fRec19[0] + fRec25[0]))));
			output0[i] = fTemp31;
			output1[i] = fTemp31;
			iVec0[1] = iVec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec9[1] = fRec9[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			
		}
		
	}
	
};

