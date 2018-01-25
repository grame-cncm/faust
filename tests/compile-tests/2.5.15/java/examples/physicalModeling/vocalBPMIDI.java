/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Vocal BandPass MIDI"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	float fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider2;
	int iVec0[] = new int[2];
	float fButton0;
	float fHslider3;
	float fVec1[] = new float[2];
	float fRec1[] = new float[2];
	float fHslider4;
	float fRec2[] = new float[2];
	float fConst2;
	float fHslider5;
	float fHslider6;
	float fRec5[] = new float[2];
	float fHslider7;
	float fConst3;
	float fHslider8;
	float fRec6[] = new float[2];
	float fRec7[] = new float[2];
	float fRec3[] = new float[2];
	int iRec8[] = new int[2];
	float fConst4;
	float fHslider9;
	float fHslider10;
	float fRec9[] = new float[2];
	float fRec10[] = new float[2];
	float fRec11[] = new float[2];
	float fRec0[] = new float[3];
	float fRec12[] = new float[3];
	float fRec13[] = new float[3];
	float fRec14[] = new float[3];
	float fRec15[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("description", "Simple MIDI-controllable source-filter vocal synthesizer.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocal BandPass MIDI");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		fConst1 = (1000.0f / fConst0);
		fConst2 = (1.0f / fConst0);
		fConst3 = (6.28318548f / fConst0);
		fConst4 = (3.14159274f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fHslider1 = (float)0.90000000000000002f;
		fHslider2 = (float)10.0f;
		fButton0 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)440.0f;
		fHslider6 = (float)1.0f;
		fHslider7 = (float)0.5f;
		fHslider8 = (float)6.0f;
		fHslider9 = (float)0.0f;
		fHslider10 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec3[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec8[l8] = 0;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec0[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec13[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec14[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec15[l16] = 0.0f;
			
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
		ui_interface.openVerticalBox("vocal");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider5", "0", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface.declare("fHslider6", "1", "");
		ui_interface.declare("fHslider6", "hidden", "1");
		ui_interface.declare("fHslider6", "midi", "pitchwheel");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("bend", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 1.0f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "2", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("envAttack", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 10.0f, 0.0f, 30.0f, 0.00999999978f);
		ui_interface.declare("fHslider3", "4", "");
		ui_interface.declare("fHslider3", "hidden", "1");
		ui_interface.declare("fHslider3", "midi", "ctrl 64");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("sustain", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fHslider9", "0", "");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("voiceType", new FaustVarAccess() {
				public String getId() { return "fHslider9"; }
				public void set(float val) { fHslider9 = val; }
				public float get() { return (float)fHslider9; }
			}
			, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface.declare("fHslider10", "1", "");
		ui_interface.declare("fHslider10", "midi", "ctrl 1");
		ui_interface.declare("fHslider10", "style", "knob");
		ui_interface.addHorizontalSlider("vowel", new FaustVarAccess() {
				public String getId() { return "fHslider10"; }
				public void set(float val) { fHslider10 = val; }
				public float get() { return (float)fHslider10; }
			}
			, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("fricative", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider8", "3", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoFreq", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 6.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider7", "4", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.addHorizontalSlider("vibratoGain", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider0", "5", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("outGain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "2", "");
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (float)java.lang.Math.exp((0.0f - (fConst1 / fHslider2)));
		float fSlow2 = (float)java.lang.Math.min(1.0f, (fButton0 + fHslider3));
		float fSlow3 = ((fHslider1 * (1.0f - fSlow1)) * fSlow2);
		float fSlow4 = (0.00100000005f * fHslider4);
		float fSlow5 = fHslider5;
		int iSlow6 = (fSlow2 == 0.0f);
		float fSlow7 = fHslider6;
		float fSlow8 = (0.100000001f * fHslider7);
		float fSlow9 = (fConst3 * fHslider8);
		float fSlow10 = (float)java.lang.Math.sin(fSlow9);
		float fSlow11 = (float)java.lang.Math.cos(fSlow9);
		float fSlow12 = (0.0f - fSlow10);
		float fSlow13 = fHslider9;
		float fSlow14 = (5.0f * fSlow13);
		float fSlow15 = (0.00100000005f * fHslider10);
		float fSlow16 = (5.0f * (1.0f - fSlow13));
		int iSlow17 = ((((fSlow13 == 0.0f))?1:(((fSlow13 == 3.0f))?1:0)) == 0);
		int iSlow18 = (fSlow13 != 2.0f);
		float fSlow19 = (2.0f * fSlow5);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fVec1[0] = fSlow2;
			fRec1[0] = (fSlow3 + (fSlow1 * fRec1[1]));
			fRec2[0] = (fSlow4 + (0.999000013f * fRec2[1]));
			int iTemp0 = ((((fSlow2 == fVec1[1]))?1:0) | iSlow6);
			fRec5[0] = ((0.999000013f * (fRec5[1] * (float)iTemp0)) + (fSlow7 * (1.0f - (0.999000013f * (float)iTemp0))));
			fRec6[0] = ((fSlow10 * fRec7[1]) + (fSlow11 * fRec6[1]));
			int iTemp1 = (1 - iVec0[1]);
			fRec7[0] = (((fSlow11 * fRec7[1]) + (fSlow12 * fRec6[1])) + (float)iTemp1);
			float fTemp2 = (float)java.lang.Math.max(1.00000001e-07f, (float)java.lang.Math.abs((fSlow5 * (fRec5[0] * ((fSlow8 * fRec6[0]) + 1.0f)))));
			float fTemp3 = (fRec3[1] + (fConst2 * fTemp2));
			float fTemp4 = (fTemp3 + -1.0f);
			int iTemp5 = (fTemp4 < 0.0f);
			fRec3[0] = (((iTemp5==0)?true:false)?fTemp3:fTemp4);
			float fRec4 = (((iTemp5==0)?true:false)?fTemp3:(fTemp3 + (fTemp4 * (1.0f - (fConst0 / fTemp2)))));
			iRec8[0] = ((1103515245 * iRec8[1]) + 12345);
			float fTemp6 = (fRec1[0] * (((1.0f - fRec2[0]) * ((2.0f * fRec4) + -1.0f)) + (4.65661287e-10f * (fRec2[0] * (float)iRec8[0]))));
			fRec9[0] = (fSlow15 + (0.999000013f * fRec9[1]));
			float fTemp7 = (fSlow14 + fRec9[0]);
			int iTemp8 = (fTemp7 < 23.0f);
			int iTemp9 = (fTemp7 < 24.0f);
			float fTemp10 = (fSlow14 + (fRec9[0] + -23.0f));
			int iTemp11 = (fTemp7 < 22.0f);
			float fTemp12 = (fSlow14 + (fRec9[0] + -22.0f));
			int iTemp13 = (fTemp7 < 21.0f);
			float fTemp14 = (fSlow14 + (fRec9[0] + -21.0f));
			int iTemp15 = (fTemp7 < 20.0f);
			float fTemp16 = (fSlow14 + (fRec9[0] + -20.0f));
			int iTemp17 = (fTemp7 < 19.0f);
			float fTemp18 = (fSlow14 + (fRec9[0] + -19.0f));
			int iTemp19 = (fTemp7 < 18.0f);
			float fTemp20 = (fSlow14 + (fRec9[0] + -18.0f));
			int iTemp21 = (fTemp7 < 17.0f);
			float fTemp22 = (fSlow14 + (fRec9[0] + -17.0f));
			int iTemp23 = (fTemp7 < 16.0f);
			float fTemp24 = (fSlow14 + (fRec9[0] + -16.0f));
			float fTemp25 = (80.0f * fTemp24);
			int iTemp26 = (fTemp7 < 15.0f);
			float fTemp27 = (fSlow14 + (fRec9[0] + -15.0f));
			int iTemp28 = (fTemp7 < 14.0f);
			float fTemp29 = (fSlow14 + (fRec9[0] + -14.0f));
			int iTemp30 = (fTemp7 < 13.0f);
			float fTemp31 = (fSlow14 + (fRec9[0] + -13.0f));
			int iTemp32 = (fTemp7 < 12.0f);
			float fTemp33 = (fSlow14 + (fRec9[0] + -12.0f));
			int iTemp34 = (fTemp7 < 11.0f);
			float fTemp35 = (fSlow14 + (fRec9[0] + -11.0f));
			int iTemp36 = (fTemp7 < 10.0f);
			float fTemp37 = (fSlow14 + (fRec9[0] + -10.0f));
			int iTemp38 = (fTemp7 < 9.0f);
			float fTemp39 = (fSlow14 + (fRec9[0] + -9.0f));
			int iTemp40 = (fTemp7 < 8.0f);
			float fTemp41 = (fSlow14 + (fRec9[0] + -8.0f));
			float fTemp42 = (50.0f * fTemp41);
			int iTemp43 = (fTemp7 < 7.0f);
			float fTemp44 = (fSlow14 + (fRec9[0] + -7.0f));
			int iTemp45 = (fTemp7 < 6.0f);
			float fTemp46 = (fSlow14 + (fRec9[0] + -6.0f));
			int iTemp47 = (fTemp7 < 5.0f);
			float fTemp48 = (fRec9[0] - fSlow16);
			int iTemp49 = (fTemp7 < 4.0f);
			float fTemp50 = (fSlow14 + (fRec9[0] + -4.0f));
			int iTemp51 = (fTemp7 < 3.0f);
			float fTemp52 = (fSlow14 + (fRec9[0] + -3.0f));
			int iTemp53 = (fTemp7 < 2.0f);
			float fTemp54 = (fSlow14 + (fRec9[0] + -2.0f));
			int iTemp55 = (fTemp7 < 1.0f);
			float fTemp56 = (fSlow14 + (fRec9[0] + -1.0f));
			int iTemp57 = (fTemp7 < 0.0f);
			float fTemp58 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?800.0f:(((iTemp55==0)?true:false)?(800.0f - (400.0f * fTemp7)):400.0f)):(((iTemp53==0)?true:false)?(400.0f - (50.0f * fTemp56)):350.0f)):(((iTemp51==0)?true:false)?((100.0f * fTemp54) + 350.0f):450.0f)):(((iTemp49==0)?true:false)?(450.0f - (125.0f * fTemp52)):325.0f)):(((iTemp47==0)?true:false)?((275.0f * fTemp50) + 325.0f):600.0f)):(((iTemp45==0)?true:false)?(600.0f - (200.0f * fTemp48)):400.0f)):(((iTemp43==0)?true:false)?(400.0f - (150.0f * fTemp46)):250.0f)):(((iTemp40==0)?true:false)?((150.0f * fTemp44) + 250.0f):400.0f)):(((iTemp38==0)?true:false)?(400.0f - fTemp42):350.0f)):(((iTemp36==0)?true:false)?((310.0f * fTemp39) + 350.0f):660.0f)):(((iTemp34==0)?true:false)?(660.0f - (220.0f * fTemp37)):440.0f)):(((iTemp32==0)?true:false)?(440.0f - (170.0f * fTemp35)):270.0f)):(((iTemp30==0)?true:false)?((160.0f * fTemp33) + 270.0f):430.0f)):(((iTemp28==0)?true:false)?(430.0f - (60.0f * fTemp31)):370.0f)):(((iTemp26==0)?true:false)?((430.0f * fTemp29) + 370.0f):800.0f)):(((iTemp23==0)?true:false)?(800.0f - (450.0f * fTemp27)):350.0f)):(((iTemp21==0)?true:false)?(350.0f - fTemp25):270.0f)):(((iTemp19==0)?true:false)?((180.0f * fTemp22) + 270.0f):450.0f)):(((iTemp17==0)?true:false)?(450.0f - (125.0f * fTemp20)):325.0f)):(((iTemp15==0)?true:false)?(325.0f * (fTemp18 + 1.0f)):650.0f)):(((iTemp13==0)?true:false)?(650.0f - (250.0f * fTemp16)):400.0f)):(((iTemp11==0)?true:false)?(400.0f - (110.0f * fTemp14)):290.0f)):(((iTemp8==0)?true:false)?((110.0f * fTemp12) + 290.0f):400.0f)):(((iTemp9==0)?true:false)?(400.0f - (50.0f * fTemp10)):350.0f));
			fRec10[0] = ((fSlow10 * fRec11[1]) + (fSlow11 * fRec10[1]));
			fRec11[0] = (((fSlow11 * fRec11[1]) + (fSlow12 * fRec10[1])) + (float)iTemp1);
			float fTemp59 = (fRec5[0] * ((fSlow8 * fRec10[0]) + 1.0f));
			float fTemp60 = (fSlow5 * fTemp59);
			float fTemp61 = (((fTemp58 <= fTemp60))?fTemp60:fTemp58);
			float fTemp62 = (float)java.lang.Math.tan((fConst4 * fTemp61));
			float fTemp63 = (1.0f / fTemp62);
			float fTemp64 = (20.0f * fTemp16);
			float fTemp65 = (20.0f * fTemp27);
			float fTemp66 = (10.0f * fTemp37);
			float fTemp67 = (10.0f * fTemp50);
			float fTemp68 = (20.0f * fTemp52);
			float fTemp69 = (20.0f * fTemp54);
			float fTemp70 = (20.0f * fTemp7);
			float fTemp71 = ((((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?80.0f:(((iTemp55==0)?true:false)?(80.0f - fTemp70):60.0f)):(((iTemp53==0)?true:false)?(60.0f - (10.0f * fTemp56)):50.0f)):(((iTemp51==0)?true:false)?(fTemp69 + 50.0f):70.0f)):(((iTemp49==0)?true:false)?(70.0f - fTemp68):50.0f)):(((iTemp47==0)?true:false)?(fTemp67 + 50.0f):60.0f)):(((iTemp45==0)?true:false)?(60.0f - (20.0f * fTemp48)):40.0f)):(((iTemp43==0)?true:false)?((20.0f * fTemp46) + 40.0f):60.0f)):(((iTemp40==0)?true:false)?(60.0f - (20.0f * fTemp44)):40.0f)):40.0f):(((iTemp36==0)?true:false)?(40.0f * (fTemp39 + 1.0f)):80.0f)):(((iTemp34==0)?true:false)?(80.0f - fTemp66):70.0f)):(((iTemp32==0)?true:false)?(70.0f - (30.0f * fTemp35)):40.0f)):40.0f):40.0f):(((iTemp26==0)?true:false)?(40.0f * (fTemp29 + 1.0f)):80.0f)):(((iTemp23==0)?true:false)?(80.0f - fTemp65):60.0f)):60.0f):(((iTemp19==0)?true:false)?(60.0f - (20.0f * fTemp22)):40.0f)):(((iTemp17==0)?true:false)?((10.0f * fTemp20) + 40.0f):50.0f)):50.0f):(((iTemp13==0)?true:false)?(fTemp64 + 50.0f):70.0f)):(((iTemp11==0)?true:false)?(70.0f - (30.0f * fTemp14)):40.0f)):(((iTemp8==0)?true:false)?((30.0f * fTemp12) + 40.0f):70.0f)):(((iTemp9==0)?true:false)?(70.0f - (30.0f * fTemp10)):40.0f)) / fTemp61);
			float fTemp72 = (((fTemp63 + fTemp71) / fTemp62) + 1.0f);
			fRec0[0] = (fTemp6 - (((fRec0[2] * (((fTemp63 - fTemp71) / fTemp62) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp62)))))) / fTemp72));
			float fTemp73 = ((0.000839999993f * (1000.0f - fTemp60)) + 0.800000012f);
			float fTemp74 = ((0.00366666657f * (400.0f - fTemp60)) + 3.0f);
			float fTemp75 = (((iSlow17==0)?true:false)?fTemp74:fTemp73);
			float fTemp76 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?1150.0f:(((iTemp55==0)?true:false)?((450.0f * fTemp7) + 1150.0f):1600.0f)):(((iTemp53==0)?true:false)?((100.0f * fTemp56) + 1600.0f):1700.0f)):(((iTemp51==0)?true:false)?(1700.0f - (900.0f * fTemp54)):800.0f)):(((iTemp49==0)?true:false)?(800.0f - (100.0f * fTemp52)):700.0f)):(((iTemp47==0)?true:false)?((340.0f * fTemp50) + 700.0f):1040.0f)):(((iTemp45==0)?true:false)?((580.0f * fTemp48) + 1040.0f):1620.0f)):(((iTemp43==0)?true:false)?((130.0f * fTemp46) + 1620.0f):1750.0f)):(((iTemp40==0)?true:false)?(1750.0f - (1000.0f * fTemp44)):750.0f)):(((iTemp38==0)?true:false)?(750.0f - (150.0f * fTemp41)):600.0f)):(((iTemp36==0)?true:false)?((520.0f * fTemp39) + 600.0f):1120.0f)):(((iTemp34==0)?true:false)?((680.0f * fTemp37) + 1120.0f):1800.0f)):(((iTemp32==0)?true:false)?((50.0f * fTemp35) + 1800.0f):1850.0f)):(((iTemp30==0)?true:false)?(1850.0f - (1030.0f * fTemp33)):820.0f)):(((iTemp28==0)?true:false)?(820.0f - (190.0f * fTemp31)):630.0f)):(((iTemp26==0)?true:false)?((520.0f * fTemp29) + 630.0f):1150.0f)):(((iTemp23==0)?true:false)?((850.0f * fTemp27) + 1150.0f):2000.0f)):(((iTemp21==0)?true:false)?((140.0f * fTemp24) + 2000.0f):2140.0f)):(((iTemp19==0)?true:false)?(2140.0f - (1340.0f * fTemp22)):800.0f)):(((iTemp17==0)?true:false)?(800.0f - (100.0f * fTemp20)):700.0f)):(((iTemp15==0)?true:false)?((380.0f * fTemp18) + 700.0f):1080.0f)):(((iTemp13==0)?true:false)?((620.0f * fTemp16) + 1080.0f):1700.0f)):(((iTemp11==0)?true:false)?((170.0f * fTemp14) + 1700.0f):1870.0f)):(((iTemp8==0)?true:false)?(1870.0f - (1070.0f * fTemp12)):800.0f)):(((iTemp9==0)?true:false)?(800.0f - (200.0f * fTemp10)):600.0f));
			float fTemp77 = ((fSlow19 * fTemp59) + 30.0f);
			float fTemp78 = (((iSlow18==0)?true:false)?((((((fTemp76 >= 1300.0f))?1:0) & (((fTemp60 >= 200.0f))?1:0)))?(fTemp76 - (0.000952380942f * ((fTemp60 + -200.0f) * (fTemp76 + -1300.0f)))):(((fTemp76 <= fTemp77))?fTemp77:fTemp76)):fTemp76);
			float fTemp79 = (float)java.lang.Math.tan((fConst4 * fTemp78));
			float fTemp80 = (1.0f / fTemp79);
			float fTemp81 = (10.0f * fTemp12);
			float fTemp82 = (10.0f * fTemp16);
			float fTemp83 = (10.0f * fTemp39);
			float fTemp84 = (10.0f * fTemp48);
			float fTemp85 = ((((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?90.0f:(((iTemp55==0)?true:false)?(90.0f - (10.0f * fTemp7)):80.0f)):(((iTemp53==0)?true:false)?((20.0f * fTemp56) + 80.0f):100.0f)):(((iTemp51==0)?true:false)?(100.0f - fTemp69):80.0f)):(((iTemp49==0)?true:false)?(80.0f - fTemp68):60.0f)):(((iTemp47==0)?true:false)?(fTemp67 + 60.0f):70.0f)):(((iTemp45==0)?true:false)?(fTemp84 + 70.0f):80.0f)):(((iTemp43==0)?true:false)?((10.0f * fTemp46) + 80.0f):90.0f)):(((iTemp40==0)?true:false)?(90.0f - (10.0f * fTemp44)):80.0f)):80.0f):(((iTemp36==0)?true:false)?(fTemp83 + 80.0f):90.0f)):(((iTemp34==0)?true:false)?(90.0f - fTemp66):80.0f)):(((iTemp32==0)?true:false)?((10.0f * fTemp35) + 80.0f):90.0f)):(((iTemp30==0)?true:false)?(90.0f - (10.0f * fTemp33)):80.0f)):(((iTemp28==0)?true:false)?(80.0f - (20.0f * fTemp31)):60.0f)):(((iTemp26==0)?true:false)?((30.0f * fTemp29) + 60.0f):90.0f)):(((iTemp23==0)?true:false)?((10.0f * fTemp27) + 90.0f):100.0f)):(((iTemp21==0)?true:false)?(100.0f - (10.0f * fTemp24)):90.0f)):(((iTemp19==0)?true:false)?(90.0f - (10.0f * fTemp22)):80.0f)):(((iTemp17==0)?true:false)?(80.0f - (20.0f * fTemp20)):60.0f)):(((iTemp15==0)?true:false)?((30.0f * fTemp18) + 60.0f):90.0f)):(((iTemp13==0)?true:false)?(90.0f - fTemp82):80.0f)):(((iTemp11==0)?true:false)?((10.0f * fTemp14) + 80.0f):90.0f)):(((iTemp8==0)?true:false)?(90.0f - fTemp81):80.0f)):(((iTemp9==0)?true:false)?(80.0f - (20.0f * fTemp10)):60.0f)) / fTemp78);
			float fTemp86 = (((fTemp80 + fTemp85) / fTemp79) + 1.0f);
			fRec12[0] = (fTemp6 - (((fRec12[2] * (((fTemp80 - fTemp85) / fTemp79) + 1.0f)) + (2.0f * (fRec12[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp79)))))) / fTemp86));
			float fTemp87 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?0.630957007f:(((iTemp55==0)?true:false)?(0.630957007f - (0.567861021f * fTemp7)):0.0630960017f)):(((iTemp53==0)?true:false)?((0.0369039997f * fTemp56) + 0.0630960017f):0.100000001f)):(((iTemp51==0)?true:false)?((0.254812986f * fTemp54) + 0.100000001f):0.35481301f)):(((iTemp49==0)?true:false)?(0.35481301f - (0.103624001f * fTemp52)):0.251188993f)):(((iTemp47==0)?true:false)?((0.195494995f * fTemp50) + 0.251188993f):0.446684003f)):(((iTemp45==0)?true:false)?(0.446684003f - (0.195494995f * fTemp48)):0.251188993f)):(((iTemp43==0)?true:false)?(0.251188993f - (0.219566002f * fTemp46)):0.0316229984f)):(((iTemp40==0)?true:false)?((0.250214994f * fTemp44) + 0.0316229984f):0.281838f)):(((iTemp38==0)?true:false)?(0.281838f - (0.181838006f * fTemp41)):0.100000001f)):(((iTemp36==0)?true:false)?((0.401187003f * fTemp39) + 0.100000001f):0.501187027f)):(((iTemp34==0)?true:false)?(0.501187027f - (0.301661015f * fTemp37)):0.199525997f)):(((iTemp32==0)?true:false)?(0.199525997f - (0.136429995f * fTemp35)):0.0630960017f)):(((iTemp30==0)?true:false)?((0.253131986f * fTemp33) + 0.0630960017f):0.316228002f)):(((iTemp28==0)?true:false)?(0.316228002f - (0.216227993f * fTemp31)):0.100000001f)):(((iTemp26==0)?true:false)?((0.401187003f * fTemp29) + 0.100000001f):0.501187027f)):(((iTemp23==0)?true:false)?(0.501187027f - (0.401187003f * fTemp27)):0.100000001f)):(((iTemp21==0)?true:false)?((0.151188999f * fTemp24) + 0.100000001f):0.251188993f)):(((iTemp19==0)?true:false)?((0.0306490008f * fTemp22) + 0.251188993f):0.281838f)):(((iTemp17==0)?true:false)?(0.281838f - (0.123349003f * fTemp20)):0.158489004f)):(((iTemp15==0)?true:false)?((0.342698008f * fTemp18) + 0.158489004f):0.501187027f)):(((iTemp13==0)?true:false)?(0.501187027f - (0.301661015f * fTemp16)):0.199525997f)):(((iTemp11==0)?true:false)?(0.199525997f - (0.0216979999f * fTemp14)):0.177827999f)):(((iTemp8==0)?true:false)?((0.138400003f * fTemp12) + 0.177827999f):0.316228002f)):(((iTemp9==0)?true:false)?(0.316228002f - (0.216227993f * fTemp10)):0.100000001f));
			float fTemp88 = (((iSlow17==0)?true:false)?(fTemp74 * fTemp87):(fTemp73 * fTemp87));
			float fTemp89 = (100.0f * fTemp10);
			float fTemp90 = (50.0f * fTemp18);
			float fTemp91 = (50.0f * fTemp37);
			float fTemp92 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?2800.0f:(((iTemp55==0)?true:false)?(2800.0f - (100.0f * fTemp7)):2700.0f)):2700.0f):(((iTemp51==0)?true:false)?((130.0f * fTemp54) + 2700.0f):2830.0f)):(((iTemp49==0)?true:false)?(2830.0f - (300.0f * fTemp52)):2530.0f)):(((iTemp47==0)?true:false)?(2530.0f - (280.0f * fTemp50)):2250.0f)):(((iTemp45==0)?true:false)?((150.0f * fTemp48) + 2250.0f):2400.0f)):(((iTemp43==0)?true:false)?((200.0f * fTemp46) + 2400.0f):2600.0f)):(((iTemp40==0)?true:false)?(2600.0f - (200.0f * fTemp44)):2400.0f)):2400.0f):(((iTemp36==0)?true:false)?((350.0f * fTemp39) + 2400.0f):2750.0f)):(((iTemp34==0)?true:false)?(2750.0f - fTemp91):2700.0f)):(((iTemp32==0)?true:false)?((200.0f * fTemp35) + 2700.0f):2900.0f)):(((iTemp30==0)?true:false)?(2900.0f - (200.0f * fTemp33)):2700.0f)):(((iTemp28==0)?true:false)?((50.0f * fTemp31) + 2700.0f):2750.0f)):(((iTemp26==0)?true:false)?((150.0f * fTemp29) + 2750.0f):2900.0f)):(((iTemp23==0)?true:false)?(2900.0f - (100.0f * fTemp27)):2800.0f)):(((iTemp21==0)?true:false)?((150.0f * fTemp24) + 2800.0f):2950.0f)):(((iTemp19==0)?true:false)?(2950.0f - (120.0f * fTemp22)):2830.0f)):(((iTemp17==0)?true:false)?(2830.0f - (130.0f * fTemp20)):2700.0f)):(((iTemp15==0)?true:false)?(2700.0f - fTemp90):2650.0f)):(((iTemp13==0)?true:false)?(2650.0f - (50.0f * fTemp16)):2600.0f)):(((iTemp11==0)?true:false)?((200.0f * fTemp14) + 2600.0f):2800.0f)):(((iTemp8==0)?true:false)?(2800.0f - (200.0f * fTemp12)):2600.0f)):(((iTemp9==0)?true:false)?(fTemp89 + 2600.0f):2700.0f));
			float fTemp93 = (float)java.lang.Math.tan((fConst4 * fTemp92));
			float fTemp94 = (1.0f / fTemp93);
			float fTemp95 = (20.0f * fTemp29);
			float fTemp96 = (20.0f * fTemp37);
			float fTemp97 = (20.0f * fTemp39);
			float fTemp98 = (60.0f * fTemp50);
			float fTemp99 = ((((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?120.0f:(((iTemp51==0)?true:false)?(120.0f - fTemp69):100.0f)):(((iTemp49==0)?true:false)?((70.0f * fTemp52) + 100.0f):170.0f)):(((iTemp47==0)?true:false)?(170.0f - fTemp98):110.0f)):(((iTemp45==0)?true:false)?(110.0f - fTemp84):100.0f)):100.0f):100.0f):100.0f):(((iTemp36==0)?true:false)?(fTemp97 + 100.0f):120.0f)):(((iTemp34==0)?true:false)?(120.0f - fTemp96):100.0f)):100.0f):100.0f):100.0f):(((iTemp26==0)?true:false)?(fTemp95 + 100.0f):120.0f)):120.0f):(((iTemp21==0)?true:false)?(120.0f - (20.0f * fTemp24)):100.0f)):100.0f):(((iTemp17==0)?true:false)?((70.0f * fTemp20) + 100.0f):170.0f)):(((iTemp15==0)?true:false)?(170.0f - fTemp90):120.0f)):(((iTemp13==0)?true:false)?(120.0f - fTemp64):100.0f)):100.0f):100.0f):100.0f) / fTemp92);
			float fTemp100 = (((fTemp94 + fTemp99) / fTemp93) + 1.0f);
			fRec13[0] = (fTemp6 - (((fRec13[2] * (((fTemp94 - fTemp99) / fTemp93) + 1.0f)) + (2.0f * (fRec13[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp93)))))) / fTemp100));
			float fTemp101 = (((iTemp19==0)?true:false)?((0.0293140002f * fTemp22) + 0.0501190014f):0.0794330016f);
			float fTemp102 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?0.100000001f:(((iTemp55==0)?true:false)?(0.100000001f - (0.0683770031f * fTemp7)):0.0316229984f)):0.0316229984f):(((iTemp51==0)?true:false)?((0.126865998f * fTemp54) + 0.0316229984f):0.158489004f)):(((iTemp49==0)?true:false)?(0.158489004f - (0.126865998f * fTemp52)):0.0316229984f)):(((iTemp47==0)?true:false)?((0.323190004f * fTemp50) + 0.0316229984f):0.35481301f)):0.35481301f):(((iTemp43==0)?true:false)?(0.35481301f - (0.196324006f * fTemp46)):0.158489004f)):(((iTemp40==0)?true:false)?(0.158489004f - (0.0693639964f * fTemp44)):0.0891249999f)):(((iTemp38==0)?true:false)?(0.0891249999f - (0.0640060008f * fTemp41)):0.0251189992f)):(((iTemp36==0)?true:false)?((0.0456760004f * fTemp39) + 0.0251189992f):0.0707949996f)):(((iTemp34==0)?true:false)?((0.0550980009f * fTemp37) + 0.0707949996f):0.125892997f)):(((iTemp32==0)?true:false)?(0.125892997f - (0.0627970025f * fTemp35)):0.0630960017f)):(((iTemp30==0)?true:false)?(0.0630960017f - (0.0129770003f * fTemp33)):0.0501190014f)):(((iTemp28==0)?true:false)?((0.020676f * fTemp31) + 0.0501190014f):0.0707949996f)):(((iTemp26==0)?true:false)?(0.0707949996f - (0.0456760004f * fTemp29)):0.0251189992f)):(((iTemp23==0)?true:false)?((0.152709007f * fTemp27) + 0.0251189992f):0.177827999f)):(((iTemp21==0)?true:false)?(0.177827999f - (0.127709001f * fTemp24)):0.0501190014f)):fTemp101):(((iTemp17==0)?true:false)?(0.0794330016f - (0.0616500005f * fTemp20)):0.0177829992f)):(((iTemp15==0)?true:false)?((0.428900987f * fTemp18) + 0.0177829992f):0.446684003f)):(((iTemp13==0)?true:false)?(0.446684003f - (0.195494995f * fTemp16)):0.251188993f)):(((iTemp11==0)?true:false)?(0.251188993f - (0.125295997f * fTemp14)):0.125892997f)):(((iTemp8==0)?true:false)?((0.125295997f * fTemp12) + 0.125892997f):0.251188993f)):(((iTemp9==0)?true:false)?(0.251188993f - (0.109935001f * fTemp10)):0.141253993f));
			float fTemp103 = (((iSlow17==0)?true:false)?(fTemp74 * fTemp102):(fTemp73 * fTemp102));
			float fTemp104 = (350.0f * fTemp48);
			float fTemp105 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?3500.0f:(((iTemp55==0)?true:false)?(3500.0f - (200.0f * fTemp7)):3300.0f)):(((iTemp53==0)?true:false)?((400.0f * fTemp56) + 3300.0f):3700.0f)):(((iTemp51==0)?true:false)?(3700.0f - (200.0f * fTemp54)):3500.0f)):3500.0f):(((iTemp47==0)?true:false)?(3500.0f - (1050.0f * fTemp50)):2450.0f)):(((iTemp45==0)?true:false)?(fTemp104 + 2450.0f):2800.0f)):(((iTemp43==0)?true:false)?((250.0f * fTemp46) + 2800.0f):3050.0f)):(((iTemp40==0)?true:false)?(3050.0f - (450.0f * fTemp44)):2600.0f)):(((iTemp38==0)?true:false)?((75.0f * fTemp41) + 2600.0f):2675.0f)):(((iTemp36==0)?true:false)?((325.0f * fTemp39) + 2675.0f):3000.0f)):3000.0f):(((iTemp32==0)?true:false)?((350.0f * fTemp35) + 3000.0f):3350.0f)):(((iTemp30==0)?true:false)?(3350.0f - (350.0f * fTemp33)):3000.0f)):3000.0f):(((iTemp26==0)?true:false)?((900.0f * fTemp29) + 3000.0f):3900.0f)):(((iTemp23==0)?true:false)?(3900.0f - (300.0f * fTemp27)):3600.0f)):(((iTemp21==0)?true:false)?((300.0f * fTemp24) + 3600.0f):3900.0f)):(((iTemp19==0)?true:false)?(3900.0f - (100.0f * fTemp22)):3800.0f)):3800.0f):(((iTemp15==0)?true:false)?(3800.0f - (900.0f * fTemp18)):2900.0f)):(((iTemp13==0)?true:false)?((300.0f * fTemp16) + 2900.0f):3200.0f)):(((iTemp11==0)?true:false)?((50.0f * fTemp14) + 3200.0f):3250.0f)):(((iTemp8==0)?true:false)?(3250.0f - (450.0f * fTemp12)):2800.0f)):(((iTemp9==0)?true:false)?(fTemp89 + 2800.0f):2900.0f));
			float fTemp106 = (float)java.lang.Math.tan((fConst4 * fTemp105));
			float fTemp107 = (1.0f / fTemp106);
			float fTemp108 = ((((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?130.0f:(((iTemp55==0)?true:false)?(fTemp70 + 130.0f):150.0f)):150.0f):(((iTemp51==0)?true:false)?(150.0f - fTemp69):130.0f)):(((iTemp49==0)?true:false)?((50.0f * fTemp52) + 130.0f):180.0f)):(((iTemp47==0)?true:false)?(180.0f - fTemp98):120.0f)):120.0f):120.0f):120.0f):120.0f):(((iTemp36==0)?true:false)?(fTemp83 + 120.0f):130.0f)):(((iTemp34==0)?true:false)?(130.0f - fTemp66):120.0f)):120.0f):120.0f):120.0f):(((iTemp26==0)?true:false)?((10.0f * fTemp29) + 120.0f):130.0f)):(((iTemp23==0)?true:false)?(fTemp65 + 130.0f):150.0f)):(((iTemp21==0)?true:false)?(150.0f - (30.0f * fTemp24)):120.0f)):120.0f):(((iTemp17==0)?true:false)?((60.0f * fTemp20) + 120.0f):180.0f)):(((iTemp15==0)?true:false)?(180.0f - fTemp90):130.0f)):(((iTemp13==0)?true:false)?(130.0f - fTemp82):120.0f)):120.0f):(((iTemp8==0)?true:false)?(fTemp81 + 120.0f):130.0f)):(((iTemp9==0)?true:false)?(130.0f - (10.0f * fTemp10)):120.0f)) / fTemp105);
			float fTemp109 = (((fTemp107 + fTemp108) / fTemp106) + 1.0f);
			fRec14[0] = (fTemp6 - (((fRec14[2] * (((fTemp107 - fTemp108) / fTemp106) + 1.0f)) + (2.0f * (fRec14[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp106)))))) / fTemp109));
			float fTemp110 = (((iTemp32==0)?true:false)?(0.100000001f - (0.0841509998f * fTemp35)):0.0158489998f);
			float fTemp111 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?0.0158489998f:(((iTemp55==0)?true:false)?((0.00193400006f * fTemp7) + 0.0158489998f):0.0177829992f)):(((iTemp53==0)?true:false)?(0.0177829992f - (0.00193400006f * fTemp56)):0.0158489998f)):(((iTemp51==0)?true:false)?((0.0239620004f * fTemp54) + 0.0158489998f):0.0398110002f)):(((iTemp49==0)?true:false)?(0.0398110002f - (0.0298110005f * fTemp52)):0.00999999978f)):(((iTemp47==0)?true:false)?((0.344812989f * fTemp50) + 0.00999999978f):0.35481301f)):(((iTemp45==0)?true:false)?(0.35481301f - (0.103624001f * fTemp48)):0.251188993f)):(((iTemp43==0)?true:false)?(0.251188993f - (0.171755999f * fTemp46)):0.0794330016f)):(((iTemp40==0)?true:false)?((0.0205669999f * fTemp44) + 0.0794330016f):0.100000001f)):(((iTemp38==0)?true:false)?(0.100000001f - (0.0601890013f * fTemp41)):0.0398110002f)):(((iTemp36==0)?true:false)?((0.0232849997f * fTemp39) + 0.0398110002f):0.0630960017f)):(((iTemp34==0)?true:false)?((0.0369039997f * fTemp37) + 0.0630960017f):0.100000001f)):fTemp110):(((iTemp30==0)?true:false)?((0.0635839999f * fTemp33) + 0.0158489998f):0.0794330016f)):(((iTemp28==0)?true:false)?(0.0794330016f - (0.0478099994f * fTemp31)):0.0316229984f)):(((iTemp26==0)?true:false)?((0.0683770031f * fTemp29) + 0.0316229984f):0.100000001f)):(((iTemp23==0)?true:false)?(0.100000001f - (0.0900000036f * fTemp27)):0.00999999978f)):(((iTemp21==0)?true:false)?((0.0401189998f * fTemp24) + 0.00999999978f):0.0501190014f)):fTemp101):(((iTemp17==0)?true:false)?(0.0794330016f - (0.0694330037f * fTemp20)):0.00999999978f)):(((iTemp15==0)?true:false)?((0.388107002f * fTemp18) + 0.00999999978f):0.398106992f)):(((iTemp13==0)?true:false)?(0.398106992f - (0.198580995f * fTemp16)):0.199525997f)):(((iTemp11==0)?true:false)?(0.199525997f - (0.099526003f * fTemp14)):0.100000001f)):(((iTemp8==0)?true:false)?((0.151188999f * fTemp12) + 0.100000001f):0.251188993f)):(((iTemp9==0)?true:false)?(0.251188993f - (0.0516630001f * fTemp10)):0.199525997f));
			float fTemp112 = (((iSlow17==0)?true:false)?(fTemp74 * fTemp111):(fTemp73 * fTemp111));
			float fTemp113 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?4950.0f:(((iTemp47==0)?true:false)?(4950.0f - (2200.0f * fTemp50)):2750.0f)):(((iTemp45==0)?true:false)?(fTemp104 + 2750.0f):3100.0f)):(((iTemp43==0)?true:false)?((240.0f * fTemp46) + 3100.0f):3340.0f)):(((iTemp40==0)?true:false)?(3340.0f - (440.0f * fTemp44)):2900.0f)):(((iTemp38==0)?true:false)?(fTemp42 + 2900.0f):2950.0f)):(((iTemp36==0)?true:false)?((400.0f * fTemp39) + 2950.0f):3350.0f)):(((iTemp34==0)?true:false)?(3350.0f - fTemp91):3300.0f)):(((iTemp32==0)?true:false)?((290.0f * fTemp35) + 3300.0f):3590.0f)):(((iTemp30==0)?true:false)?(3590.0f - (290.0f * fTemp33)):3300.0f)):(((iTemp28==0)?true:false)?((100.0f * fTemp31) + 3300.0f):3400.0f)):(((iTemp26==0)?true:false)?((1550.0f * fTemp29) + 3400.0f):4950.0f)):4950.0f):4950.0f):4950.0f):4950.0f):(((iTemp15==0)?true:false)?(4950.0f - (1700.0f * fTemp18)):3250.0f)):(((iTemp13==0)?true:false)?((330.0f * fTemp16) + 3250.0f):3580.0f)):(((iTemp11==0)?true:false)?(3580.0f - (40.0f * fTemp14)):3540.0f)):(((iTemp8==0)?true:false)?(3540.0f - (540.0f * fTemp12)):3000.0f)):(((iTemp9==0)?true:false)?((300.0f * fTemp10) + 3000.0f):3300.0f));
			float fTemp114 = (float)java.lang.Math.tan((fConst4 * fTemp113));
			float fTemp115 = (1.0f / fTemp114);
			float fTemp116 = ((((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?(((iTemp57==0)?true:false)?140.0f:(((iTemp55==0)?true:false)?((60.0f * fTemp7) + 140.0f):200.0f)):200.0f):(((iTemp51==0)?true:false)?(200.0f - (65.0f * fTemp54)):135.0f)):(((iTemp49==0)?true:false)?((65.0f * fTemp52) + 135.0f):200.0f)):(((iTemp47==0)?true:false)?(200.0f - (70.0f * fTemp50)):130.0f)):(((iTemp45==0)?true:false)?(130.0f - fTemp84):120.0f)):120.0f):120.0f):120.0f):(((iTemp36==0)?true:false)?(fTemp97 + 120.0f):140.0f)):(((iTemp34==0)?true:false)?(140.0f - fTemp96):120.0f)):120.0f):120.0f):120.0f):(((iTemp26==0)?true:false)?(fTemp95 + 120.0f):140.0f)):(((iTemp23==0)?true:false)?((60.0f * fTemp27) + 140.0f):200.0f)):(((iTemp21==0)?true:false)?(200.0f - fTemp25):120.0f)):120.0f):(((iTemp17==0)?true:false)?((80.0f * fTemp20) + 120.0f):200.0f)):(((iTemp15==0)?true:false)?(200.0f - (60.0f * fTemp18)):140.0f)):(((iTemp13==0)?true:false)?(140.0f - fTemp64):120.0f)):120.0f):(((iTemp8==0)?true:false)?((15.0f * fTemp12) + 120.0f):135.0f)):(((iTemp9==0)?true:false)?(135.0f - (15.0f * fTemp10)):120.0f)) / fTemp113);
			float fTemp117 = (((fTemp115 + fTemp116) / fTemp114) + 1.0f);
			fRec15[0] = (fTemp6 - (((fRec15[2] * (((fTemp115 - fTemp116) / fTemp114) + 1.0f)) + (2.0f * (fRec15[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp114)))))) / fTemp117));
			float fTemp118 = (((iTemp8==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp19==0)?true:false)?(((iTemp21==0)?true:false)?(((iTemp23==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp38==0)?true:false)?(((iTemp40==0)?true:false)?(((iTemp43==0)?true:false)?(((iTemp45==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?0.00100000005f:(((iTemp51==0)?true:false)?((0.000777999987f * fTemp54) + 0.00100000005f):0.00177800003f)):(((iTemp49==0)?true:false)?(0.00177800003f - (0.001147f * fTemp52)):0.000630999974f)):(((iTemp47==0)?true:false)?((0.0993689969f * fTemp50) + 0.000630999974f):0.100000001f)):(((iTemp45==0)?true:false)?((0.0258930009f * fTemp48) + 0.100000001f):0.125892997f)):(((iTemp43==0)?true:false)?(0.125892997f - (0.0860819966f * fTemp46)):0.0398110002f)):(((iTemp40==0)?true:false)?(0.0398110002f - (0.0298110005f * fTemp44)):0.00999999978f)):(((iTemp38==0)?true:false)?((0.00584900007f * fTemp41) + 0.00999999978f):0.0158489998f)):(((iTemp36==0)?true:false)?(0.0158489998f - (0.00325999991f * fTemp39)):0.0125890002f)):(((iTemp34==0)?true:false)?((0.0874110013f * fTemp37) + 0.0125890002f):0.100000001f)):fTemp110):(((iTemp30==0)?true:false)?((0.00410400005f * fTemp33) + 0.0158489998f):0.0199529994f)):0.0199529994f):(((iTemp26==0)?true:false)?(0.0199529994f - (0.0167909991f * fTemp29)):0.0031620001f)):(((iTemp23==0)?true:false)?(0.0031620001f - (0.00157700002f * fTemp27)):0.00158499996f)):(((iTemp21==0)?true:false)?((0.00472499989f * fTemp24) + 0.00158499996f):0.00631000008f)):(((iTemp19==0)?true:false)?(0.00631000008f - (0.00314799999f * fTemp22)):0.0031620001f)):(((iTemp17==0)?true:false)?(0.0031620001f - (0.00216199993f * fTemp20)):0.00100000005f)):(((iTemp15==0)?true:false)?((0.0784329996f * fTemp18) + 0.00100000005f):0.0794330016f)):(((iTemp13==0)?true:false)?((0.0205669999f * fTemp16) + 0.0794330016f):0.100000001f)):(((iTemp11==0)?true:false)?(0.100000001f - (0.0683770031f * fTemp14)):0.0316229984f)):(((iTemp8==0)?true:false)?((0.0184959993f * fTemp12) + 0.0316229984f):0.0501190014f)):0.0501190014f);
			float fTemp119 = (((iSlow17==0)?true:false)?(fTemp74 * fTemp118):(fTemp73 * fTemp118));
			float fTemp120 = (fSlow0 * (((((((fRec0[2] * (0.0f - (fTemp75 / fTemp62))) + ((fRec0[0] * fTemp75) / fTemp62)) / fTemp72) + (((fRec12[2] * (0.0f - (fTemp88 / fTemp79))) + ((fRec12[0] * fTemp88) / fTemp79)) / fTemp86)) + (((fRec13[2] * (0.0f - (fTemp103 / fTemp93))) + ((fRec13[0] * fTemp103) / fTemp93)) / fTemp100)) + (((fRec14[2] * (0.0f - (fTemp112 / fTemp106))) + ((fRec14[0] * fTemp112) / fTemp106)) / fTemp109)) + (((fRec15[2] * (0.0f - (fTemp119 / fTemp114))) + ((fRec15[0] * fTemp119) / fTemp114)) / fTemp117)));
			output0[i] = fTemp120;
			output1[i] = fTemp120;
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec3[1] = fRec3[0];
			iRec8[1] = iRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			
		}
		
	}
	
};

