/* ------------------------------------------------------------
name: "vocal"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	int iVec0[] = new int[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider1;
	float fRec3[] = new float[2];
	float fHslider2;
	float fConst2;
	float fConst3;
	float fConst4;
	float fRec4[] = new float[2];
	float fConst5;
	float fRec5[] = new float[2];
	float fRec1[] = new float[2];
	float fConst6;
	float fHslider3;
	float fRec6[] = new float[2];
	float fRec7[] = new float[2];
	float fRec8[] = new float[2];
	float fRec9[] = new float[2];
	float fRec0[] = new float[3];
	float fRec10[] = new float[3];
	float fRec11[] = new float[3];
	float fRec12[] = new float[3];
	float fRec13[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'1',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'1',  'Keyboard 0 - Send Freq':'0',  'Keyboard 0 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Piano Keyboard':'0' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "vocal");
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
		fConst1 = (1.0f / fConst0);
		fConst2 = (37.6991119f / fConst0);
		fConst3 = (float)java.lang.Math.sin(fConst2);
		fConst4 = (float)java.lang.Math.cos(fConst2);
		fConst5 = (0.0f - fConst3);
		fConst6 = (3.14159274f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.25f;
		fHslider1 = (float)0.5f;
		fHslider2 = (float)0.050000000000000003f;
		fHslider3 = (float)2.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec3[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec8[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec9[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec12[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;
			
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
		ui_interface.addHorizontalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.25f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider2", "acc", "1 0 -10 0 10");
		ui_interface.addHorizontalSlider("vibrato", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0500000007f, 0.0f, 0.100000001f, 0.00999999978f);
		ui_interface.declare("fHslider3", "acc", "0 0 -10 0 10");
		ui_interface.addHorizontalSlider("vowel", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 2.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface.addHorizontalSlider("x", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (0.00100000005f * fHslider1);
		float fSlow2 = fHslider2;
		float fSlow3 = (0.00100000005f * fHslider3);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec3[0] = (fSlow1 + (0.999000013f * fRec3[1]));
			fRec4[0] = ((fConst3 * fRec5[1]) + (fConst4 * fRec4[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec5[0] = (((fConst4 * fRec5[1]) + (fConst5 * fRec4[1])) + (float)iTemp0);
			float fTemp1 = (float)java.lang.Math.max(1.00000001e-07f, (float)java.lang.Math.abs((((200.0f * fRec3[0]) + 50.0f) * ((fSlow2 * fRec4[0]) + 1.0f))));
			float fTemp2 = (fRec1[1] + (fConst1 * fTemp1));
			float fTemp3 = (fTemp2 + -1.0f);
			int iTemp4 = (fTemp3 < 0.0f);
			fRec1[0] = (((iTemp4==0)?true:false)?fTemp2:fTemp3);
			float fRec2 = (((iTemp4==0)?true:false)?fTemp2:(fTemp2 + (fTemp3 * (1.0f - (fConst0 / fTemp1)))));
			float fTemp5 = (fSlow0 * ((2.0f * fRec2) + -1.0f));
			fRec6[0] = (fSlow3 + (0.999000013f * fRec6[1]));
			float fTemp6 = (fRec6[0] + 5.0f);
			int iTemp7 = (fTemp6 < 23.0f);
			int iTemp8 = (fTemp6 < 24.0f);
			float fTemp9 = (fRec6[0] + -18.0f);
			int iTemp10 = (fTemp6 < 22.0f);
			float fTemp11 = (fRec6[0] + -17.0f);
			int iTemp12 = (fTemp6 < 21.0f);
			float fTemp13 = (fRec6[0] + -16.0f);
			int iTemp14 = (fTemp6 < 20.0f);
			float fTemp15 = (fRec6[0] + -15.0f);
			int iTemp16 = (fTemp6 < 19.0f);
			float fTemp17 = (fRec6[0] + -14.0f);
			int iTemp18 = (fTemp6 < 18.0f);
			float fTemp19 = (fRec6[0] + -13.0f);
			int iTemp20 = (fTemp6 < 17.0f);
			float fTemp21 = (fRec6[0] + -12.0f);
			int iTemp22 = (fTemp6 < 16.0f);
			float fTemp23 = (fRec6[0] + -11.0f);
			float fTemp24 = (80.0f * fTemp23);
			int iTemp25 = (fTemp6 < 15.0f);
			float fTemp26 = (fRec6[0] + -10.0f);
			int iTemp27 = (fTemp6 < 14.0f);
			float fTemp28 = (fRec6[0] + -9.0f);
			int iTemp29 = (fTemp6 < 13.0f);
			float fTemp30 = (fRec6[0] + -8.0f);
			int iTemp31 = (fTemp6 < 12.0f);
			float fTemp32 = (fRec6[0] + -7.0f);
			int iTemp33 = (fTemp6 < 11.0f);
			float fTemp34 = (fRec6[0] + -6.0f);
			int iTemp35 = (fTemp6 < 10.0f);
			float fTemp36 = (fRec6[0] + -5.0f);
			int iTemp37 = (fTemp6 < 9.0f);
			float fTemp38 = (fRec6[0] + -4.0f);
			int iTemp39 = (fTemp6 < 8.0f);
			float fTemp40 = (fRec6[0] + -3.0f);
			float fTemp41 = (50.0f * fTemp40);
			int iTemp42 = (fTemp6 < 7.0f);
			float fTemp43 = (fRec6[0] + -2.0f);
			int iTemp44 = (fTemp6 < 6.0f);
			float fTemp45 = (fRec6[0] + -1.0f);
			int iTemp46 = (fTemp6 < 5.0f);
			int iTemp47 = (fTemp6 < 4.0f);
			float fTemp48 = (fRec6[0] + 1.0f);
			int iTemp49 = (fTemp6 < 3.0f);
			float fTemp50 = (fRec6[0] + 2.0f);
			int iTemp51 = (fTemp6 < 2.0f);
			float fTemp52 = (fRec6[0] + 3.0f);
			int iTemp53 = (fTemp6 < 1.0f);
			float fTemp54 = (fRec6[0] + 4.0f);
			int iTemp55 = (fTemp6 < 0.0f);
			float fTemp56 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?800.0f:(((iTemp53==0)?true:false)?(800.0f - (400.0f * fTemp6)):400.0f)):(((iTemp51==0)?true:false)?(400.0f - (50.0f * fTemp54)):350.0f)):(((iTemp49==0)?true:false)?((100.0f * fTemp52) + 350.0f):450.0f)):(((iTemp47==0)?true:false)?(450.0f - (125.0f * fTemp50)):325.0f)):(((iTemp46==0)?true:false)?((275.0f * fTemp48) + 325.0f):600.0f)):(((iTemp44==0)?true:false)?(600.0f - (200.0f * fRec6[0])):400.0f)):(((iTemp42==0)?true:false)?(400.0f - (150.0f * fTemp45)):250.0f)):(((iTemp39==0)?true:false)?((150.0f * fTemp43) + 250.0f):400.0f)):(((iTemp37==0)?true:false)?(400.0f - fTemp41):350.0f)):(((iTemp35==0)?true:false)?((310.0f * fTemp38) + 350.0f):660.0f)):(((iTemp33==0)?true:false)?(660.0f - (220.0f * fTemp36)):440.0f)):(((iTemp31==0)?true:false)?(440.0f - (170.0f * fTemp34)):270.0f)):(((iTemp29==0)?true:false)?((160.0f * fTemp32) + 270.0f):430.0f)):(((iTemp27==0)?true:false)?(430.0f - (60.0f * fTemp30)):370.0f)):(((iTemp25==0)?true:false)?((430.0f * fTemp28) + 370.0f):800.0f)):(((iTemp22==0)?true:false)?(800.0f - (450.0f * fTemp26)):350.0f)):(((iTemp20==0)?true:false)?(350.0f - fTemp24):270.0f)):(((iTemp18==0)?true:false)?((180.0f * fTemp21) + 270.0f):450.0f)):(((iTemp16==0)?true:false)?(450.0f - (125.0f * fTemp19)):325.0f)):(((iTemp14==0)?true:false)?(325.0f * (fTemp17 + 1.0f)):650.0f)):(((iTemp12==0)?true:false)?(650.0f - (250.0f * fTemp15)):400.0f)):(((iTemp10==0)?true:false)?(400.0f - (110.0f * fTemp13)):290.0f)):(((iTemp7==0)?true:false)?((110.0f * fTemp11) + 290.0f):400.0f)):(((iTemp8==0)?true:false)?(400.0f - (50.0f * fTemp9)):350.0f));
			fRec7[0] = (fSlow1 + (0.999000013f * fRec7[1]));
			fRec8[0] = ((fConst3 * fRec9[1]) + (fConst4 * fRec8[1]));
			fRec9[0] = (((fConst4 * fRec9[1]) + (fConst5 * fRec8[1])) + (float)iTemp0);
			float fTemp57 = (((200.0f * fRec7[0]) + 50.0f) * ((fSlow2 * fRec8[0]) + 1.0f));
			float fTemp58 = (((fTemp56 <= fTemp57))?fTemp57:fTemp56);
			float fTemp59 = (float)java.lang.Math.tan((fConst6 * fTemp58));
			float fTemp60 = (1.0f / fTemp59);
			float fTemp61 = (20.0f * fTemp15);
			float fTemp62 = (20.0f * fTemp26);
			float fTemp63 = (10.0f * fTemp36);
			float fTemp64 = (10.0f * fTemp48);
			float fTemp65 = (20.0f * fTemp50);
			float fTemp66 = (20.0f * fTemp52);
			float fTemp67 = (20.0f * fTemp6);
			float fTemp68 = ((((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?80.0f:(((iTemp53==0)?true:false)?(80.0f - fTemp67):60.0f)):(((iTemp51==0)?true:false)?(60.0f - (10.0f * fTemp54)):50.0f)):(((iTemp49==0)?true:false)?(fTemp66 + 50.0f):70.0f)):(((iTemp47==0)?true:false)?(70.0f - fTemp65):50.0f)):(((iTemp46==0)?true:false)?(fTemp64 + 50.0f):60.0f)):(((iTemp44==0)?true:false)?(60.0f - (20.0f * fRec6[0])):40.0f)):(((iTemp42==0)?true:false)?((20.0f * fTemp45) + 40.0f):60.0f)):(((iTemp39==0)?true:false)?(60.0f - (20.0f * fTemp43)):40.0f)):40.0f):(((iTemp35==0)?true:false)?(40.0f * (fTemp38 + 1.0f)):80.0f)):(((iTemp33==0)?true:false)?(80.0f - fTemp63):70.0f)):(((iTemp31==0)?true:false)?(70.0f - (30.0f * fTemp34)):40.0f)):40.0f):40.0f):(((iTemp25==0)?true:false)?(40.0f * (fTemp28 + 1.0f)):80.0f)):(((iTemp22==0)?true:false)?(80.0f - fTemp62):60.0f)):60.0f):(((iTemp18==0)?true:false)?(60.0f - (20.0f * fTemp21)):40.0f)):(((iTemp16==0)?true:false)?((10.0f * fTemp19) + 40.0f):50.0f)):50.0f):(((iTemp12==0)?true:false)?(fTemp61 + 50.0f):70.0f)):(((iTemp10==0)?true:false)?(70.0f - (30.0f * fTemp13)):40.0f)):(((iTemp7==0)?true:false)?((30.0f * fTemp11) + 40.0f):70.0f)):(((iTemp8==0)?true:false)?(70.0f - (30.0f * fTemp9)):40.0f)) / fTemp58);
			float fTemp69 = (((fTemp60 + fTemp68) / fTemp59) + 1.0f);
			fRec0[0] = (fTemp5 - (((fRec0[2] * (((fTemp60 - fTemp68) / fTemp59) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp59)))))) / fTemp69));
			float fTemp70 = ((0.00366666657f * (400.0f - fTemp57)) + 3.0f);
			float fTemp71 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?1150.0f:(((iTemp53==0)?true:false)?((450.0f * fTemp6) + 1150.0f):1600.0f)):(((iTemp51==0)?true:false)?((100.0f * fTemp54) + 1600.0f):1700.0f)):(((iTemp49==0)?true:false)?(1700.0f - (900.0f * fTemp52)):800.0f)):(((iTemp47==0)?true:false)?(800.0f - (100.0f * fTemp50)):700.0f)):(((iTemp46==0)?true:false)?((340.0f * fTemp48) + 700.0f):1040.0f)):(((iTemp44==0)?true:false)?((580.0f * fRec6[0]) + 1040.0f):1620.0f)):(((iTemp42==0)?true:false)?((130.0f * fTemp45) + 1620.0f):1750.0f)):(((iTemp39==0)?true:false)?(1750.0f - (1000.0f * fTemp43)):750.0f)):(((iTemp37==0)?true:false)?(750.0f - (150.0f * fTemp40)):600.0f)):(((iTemp35==0)?true:false)?((520.0f * fTemp38) + 600.0f):1120.0f)):(((iTemp33==0)?true:false)?((680.0f * fTemp36) + 1120.0f):1800.0f)):(((iTemp31==0)?true:false)?((50.0f * fTemp34) + 1800.0f):1850.0f)):(((iTemp29==0)?true:false)?(1850.0f - (1030.0f * fTemp32)):820.0f)):(((iTemp27==0)?true:false)?(820.0f - (190.0f * fTemp30)):630.0f)):(((iTemp25==0)?true:false)?((520.0f * fTemp28) + 630.0f):1150.0f)):(((iTemp22==0)?true:false)?((850.0f * fTemp26) + 1150.0f):2000.0f)):(((iTemp20==0)?true:false)?((140.0f * fTemp23) + 2000.0f):2140.0f)):(((iTemp18==0)?true:false)?(2140.0f - (1340.0f * fTemp21)):800.0f)):(((iTemp16==0)?true:false)?(800.0f - (100.0f * fTemp19)):700.0f)):(((iTemp14==0)?true:false)?((380.0f * fTemp17) + 700.0f):1080.0f)):(((iTemp12==0)?true:false)?((620.0f * fTemp15) + 1080.0f):1700.0f)):(((iTemp10==0)?true:false)?((170.0f * fTemp13) + 1700.0f):1870.0f)):(((iTemp7==0)?true:false)?(1870.0f - (1070.0f * fTemp11)):800.0f)):(((iTemp8==0)?true:false)?(800.0f - (200.0f * fTemp9)):600.0f));
			float fTemp72 = ((2.0f * fTemp57) + 30.0f);
			float fTemp73 = ((((((fTemp71 >= 1300.0f))?1:0) & (((fTemp57 >= 200.0f))?1:0)))?(fTemp71 - (0.000952380942f * ((fTemp57 + -200.0f) * (fTemp71 + -1300.0f)))):(((fTemp71 <= fTemp72))?fTemp72:fTemp71));
			float fTemp74 = (float)java.lang.Math.tan((fConst6 * fTemp73));
			float fTemp75 = (1.0f / fTemp74);
			float fTemp76 = (10.0f * fTemp11);
			float fTemp77 = (10.0f * fTemp15);
			float fTemp78 = (10.0f * fTemp38);
			float fTemp79 = (10.0f * fRec6[0]);
			float fTemp80 = ((((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?90.0f:(((iTemp53==0)?true:false)?(90.0f - (10.0f * fTemp6)):80.0f)):(((iTemp51==0)?true:false)?((20.0f * fTemp54) + 80.0f):100.0f)):(((iTemp49==0)?true:false)?(100.0f - fTemp66):80.0f)):(((iTemp47==0)?true:false)?(80.0f - fTemp65):60.0f)):(((iTemp46==0)?true:false)?(fTemp64 + 60.0f):70.0f)):(((iTemp44==0)?true:false)?(fTemp79 + 70.0f):80.0f)):(((iTemp42==0)?true:false)?((10.0f * fTemp45) + 80.0f):90.0f)):(((iTemp39==0)?true:false)?(90.0f - (10.0f * fTemp43)):80.0f)):80.0f):(((iTemp35==0)?true:false)?(fTemp78 + 80.0f):90.0f)):(((iTemp33==0)?true:false)?(90.0f - fTemp63):80.0f)):(((iTemp31==0)?true:false)?((10.0f * fTemp34) + 80.0f):90.0f)):(((iTemp29==0)?true:false)?(90.0f - (10.0f * fTemp32)):80.0f)):(((iTemp27==0)?true:false)?(80.0f - (20.0f * fTemp30)):60.0f)):(((iTemp25==0)?true:false)?((30.0f * fTemp28) + 60.0f):90.0f)):(((iTemp22==0)?true:false)?((10.0f * fTemp26) + 90.0f):100.0f)):(((iTemp20==0)?true:false)?(100.0f - (10.0f * fTemp23)):90.0f)):(((iTemp18==0)?true:false)?(90.0f - (10.0f * fTemp21)):80.0f)):(((iTemp16==0)?true:false)?(80.0f - (20.0f * fTemp19)):60.0f)):(((iTemp14==0)?true:false)?((30.0f * fTemp17) + 60.0f):90.0f)):(((iTemp12==0)?true:false)?(90.0f - fTemp77):80.0f)):(((iTemp10==0)?true:false)?((10.0f * fTemp13) + 80.0f):90.0f)):(((iTemp7==0)?true:false)?(90.0f - fTemp76):80.0f)):(((iTemp8==0)?true:false)?(80.0f - (20.0f * fTemp9)):60.0f)) / fTemp73);
			float fTemp81 = (((fTemp75 + fTemp80) / fTemp74) + 1.0f);
			fRec10[0] = (fTemp5 - (((fRec10[2] * (((fTemp75 - fTemp80) / fTemp74) + 1.0f)) + (2.0f * (fRec10[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp74)))))) / fTemp81));
			float fTemp82 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?0.630957007f:(((iTemp53==0)?true:false)?(0.630957007f - (0.567861021f * fTemp6)):0.0630960017f)):(((iTemp51==0)?true:false)?((0.0369039997f * fTemp54) + 0.0630960017f):0.100000001f)):(((iTemp49==0)?true:false)?((0.254812986f * fTemp52) + 0.100000001f):0.35481301f)):(((iTemp47==0)?true:false)?(0.35481301f - (0.103624001f * fTemp50)):0.251188993f)):(((iTemp46==0)?true:false)?((0.195494995f * fTemp48) + 0.251188993f):0.446684003f)):(((iTemp44==0)?true:false)?(0.446684003f - (0.195494995f * fRec6[0])):0.251188993f)):(((iTemp42==0)?true:false)?(0.251188993f - (0.219566002f * fTemp45)):0.0316229984f)):(((iTemp39==0)?true:false)?((0.250214994f * fTemp43) + 0.0316229984f):0.281838f)):(((iTemp37==0)?true:false)?(0.281838f - (0.181838006f * fTemp40)):0.100000001f)):(((iTemp35==0)?true:false)?((0.401187003f * fTemp38) + 0.100000001f):0.501187027f)):(((iTemp33==0)?true:false)?(0.501187027f - (0.301661015f * fTemp36)):0.199525997f)):(((iTemp31==0)?true:false)?(0.199525997f - (0.136429995f * fTemp34)):0.0630960017f)):(((iTemp29==0)?true:false)?((0.253131986f * fTemp32) + 0.0630960017f):0.316228002f)):(((iTemp27==0)?true:false)?(0.316228002f - (0.216227993f * fTemp30)):0.100000001f)):(((iTemp25==0)?true:false)?((0.401187003f * fTemp28) + 0.100000001f):0.501187027f)):(((iTemp22==0)?true:false)?(0.501187027f - (0.401187003f * fTemp26)):0.100000001f)):(((iTemp20==0)?true:false)?((0.151188999f * fTemp23) + 0.100000001f):0.251188993f)):(((iTemp18==0)?true:false)?((0.0306490008f * fTemp21) + 0.251188993f):0.281838f)):(((iTemp16==0)?true:false)?(0.281838f - (0.123349003f * fTemp19)):0.158489004f)):(((iTemp14==0)?true:false)?((0.342698008f * fTemp17) + 0.158489004f):0.501187027f)):(((iTemp12==0)?true:false)?(0.501187027f - (0.301661015f * fTemp15)):0.199525997f)):(((iTemp10==0)?true:false)?(0.199525997f - (0.0216979999f * fTemp13)):0.177827999f)):(((iTemp7==0)?true:false)?((0.138400003f * fTemp11) + 0.177827999f):0.316228002f)):(((iTemp8==0)?true:false)?(0.316228002f - (0.216227993f * fTemp9)):0.100000001f));
			float fTemp83 = (100.0f * fTemp9);
			float fTemp84 = (50.0f * fTemp17);
			float fTemp85 = (50.0f * fTemp36);
			float fTemp86 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?2800.0f:(((iTemp53==0)?true:false)?(2800.0f - (100.0f * fTemp6)):2700.0f)):2700.0f):(((iTemp49==0)?true:false)?((130.0f * fTemp52) + 2700.0f):2830.0f)):(((iTemp47==0)?true:false)?(2830.0f - (300.0f * fTemp50)):2530.0f)):(((iTemp46==0)?true:false)?(2530.0f - (280.0f * fTemp48)):2250.0f)):(((iTemp44==0)?true:false)?((150.0f * fRec6[0]) + 2250.0f):2400.0f)):(((iTemp42==0)?true:false)?((200.0f * fTemp45) + 2400.0f):2600.0f)):(((iTemp39==0)?true:false)?(2600.0f - (200.0f * fTemp43)):2400.0f)):2400.0f):(((iTemp35==0)?true:false)?((350.0f * fTemp38) + 2400.0f):2750.0f)):(((iTemp33==0)?true:false)?(2750.0f - fTemp85):2700.0f)):(((iTemp31==0)?true:false)?((200.0f * fTemp34) + 2700.0f):2900.0f)):(((iTemp29==0)?true:false)?(2900.0f - (200.0f * fTemp32)):2700.0f)):(((iTemp27==0)?true:false)?((50.0f * fTemp30) + 2700.0f):2750.0f)):(((iTemp25==0)?true:false)?((150.0f * fTemp28) + 2750.0f):2900.0f)):(((iTemp22==0)?true:false)?(2900.0f - (100.0f * fTemp26)):2800.0f)):(((iTemp20==0)?true:false)?((150.0f * fTemp23) + 2800.0f):2950.0f)):(((iTemp18==0)?true:false)?(2950.0f - (120.0f * fTemp21)):2830.0f)):(((iTemp16==0)?true:false)?(2830.0f - (130.0f * fTemp19)):2700.0f)):(((iTemp14==0)?true:false)?(2700.0f - fTemp84):2650.0f)):(((iTemp12==0)?true:false)?(2650.0f - (50.0f * fTemp15)):2600.0f)):(((iTemp10==0)?true:false)?((200.0f * fTemp13) + 2600.0f):2800.0f)):(((iTemp7==0)?true:false)?(2800.0f - (200.0f * fTemp11)):2600.0f)):(((iTemp8==0)?true:false)?(fTemp83 + 2600.0f):2700.0f));
			float fTemp87 = (float)java.lang.Math.tan((fConst6 * fTemp86));
			float fTemp88 = (1.0f / fTemp87);
			float fTemp89 = (20.0f * fTemp28);
			float fTemp90 = (20.0f * fTemp36);
			float fTemp91 = (20.0f * fTemp38);
			float fTemp92 = (60.0f * fTemp48);
			float fTemp93 = ((((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?120.0f:(((iTemp49==0)?true:false)?(120.0f - fTemp66):100.0f)):(((iTemp47==0)?true:false)?((70.0f * fTemp50) + 100.0f):170.0f)):(((iTemp46==0)?true:false)?(170.0f - fTemp92):110.0f)):(((iTemp44==0)?true:false)?(110.0f - fTemp79):100.0f)):100.0f):100.0f):100.0f):(((iTemp35==0)?true:false)?(fTemp91 + 100.0f):120.0f)):(((iTemp33==0)?true:false)?(120.0f - fTemp90):100.0f)):100.0f):100.0f):100.0f):(((iTemp25==0)?true:false)?(fTemp89 + 100.0f):120.0f)):120.0f):(((iTemp20==0)?true:false)?(120.0f - (20.0f * fTemp23)):100.0f)):100.0f):(((iTemp16==0)?true:false)?((70.0f * fTemp19) + 100.0f):170.0f)):(((iTemp14==0)?true:false)?(170.0f - fTemp84):120.0f)):(((iTemp12==0)?true:false)?(120.0f - fTemp61):100.0f)):100.0f):100.0f):100.0f) / fTemp86);
			float fTemp94 = (((fTemp88 + fTemp93) / fTemp87) + 1.0f);
			fRec11[0] = (fTemp5 - (((fRec11[2] * (((fTemp88 - fTemp93) / fTemp87) + 1.0f)) + (2.0f * (fRec11[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp87)))))) / fTemp94));
			float fTemp95 = (((iTemp18==0)?true:false)?((0.0293140002f * fTemp21) + 0.0501190014f):0.0794330016f);
			float fTemp96 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?0.100000001f:(((iTemp53==0)?true:false)?(0.100000001f - (0.0683770031f * fTemp6)):0.0316229984f)):0.0316229984f):(((iTemp49==0)?true:false)?((0.126865998f * fTemp52) + 0.0316229984f):0.158489004f)):(((iTemp47==0)?true:false)?(0.158489004f - (0.126865998f * fTemp50)):0.0316229984f)):(((iTemp46==0)?true:false)?((0.323190004f * fTemp48) + 0.0316229984f):0.35481301f)):0.35481301f):(((iTemp42==0)?true:false)?(0.35481301f - (0.196324006f * fTemp45)):0.158489004f)):(((iTemp39==0)?true:false)?(0.158489004f - (0.0693639964f * fTemp43)):0.0891249999f)):(((iTemp37==0)?true:false)?(0.0891249999f - (0.0640060008f * fTemp40)):0.0251189992f)):(((iTemp35==0)?true:false)?((0.0456760004f * fTemp38) + 0.0251189992f):0.0707949996f)):(((iTemp33==0)?true:false)?((0.0550980009f * fTemp36) + 0.0707949996f):0.125892997f)):(((iTemp31==0)?true:false)?(0.125892997f - (0.0627970025f * fTemp34)):0.0630960017f)):(((iTemp29==0)?true:false)?(0.0630960017f - (0.0129770003f * fTemp32)):0.0501190014f)):(((iTemp27==0)?true:false)?((0.020676f * fTemp30) + 0.0501190014f):0.0707949996f)):(((iTemp25==0)?true:false)?(0.0707949996f - (0.0456760004f * fTemp28)):0.0251189992f)):(((iTemp22==0)?true:false)?((0.152709007f * fTemp26) + 0.0251189992f):0.177827999f)):(((iTemp20==0)?true:false)?(0.177827999f - (0.127709001f * fTemp23)):0.0501190014f)):fTemp95):(((iTemp16==0)?true:false)?(0.0794330016f - (0.0616500005f * fTemp19)):0.0177829992f)):(((iTemp14==0)?true:false)?((0.428900987f * fTemp17) + 0.0177829992f):0.446684003f)):(((iTemp12==0)?true:false)?(0.446684003f - (0.195494995f * fTemp15)):0.251188993f)):(((iTemp10==0)?true:false)?(0.251188993f - (0.125295997f * fTemp13)):0.125892997f)):(((iTemp7==0)?true:false)?((0.125295997f * fTemp11) + 0.125892997f):0.251188993f)):(((iTemp8==0)?true:false)?(0.251188993f - (0.109935001f * fTemp9)):0.141253993f));
			float fTemp97 = (350.0f * fRec6[0]);
			float fTemp98 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?3500.0f:(((iTemp53==0)?true:false)?(3500.0f - (200.0f * fTemp6)):3300.0f)):(((iTemp51==0)?true:false)?((400.0f * fTemp54) + 3300.0f):3700.0f)):(((iTemp49==0)?true:false)?(3700.0f - (200.0f * fTemp52)):3500.0f)):3500.0f):(((iTemp46==0)?true:false)?(3500.0f - (1050.0f * fTemp48)):2450.0f)):(((iTemp44==0)?true:false)?(fTemp97 + 2450.0f):2800.0f)):(((iTemp42==0)?true:false)?((250.0f * fTemp45) + 2800.0f):3050.0f)):(((iTemp39==0)?true:false)?(3050.0f - (450.0f * fTemp43)):2600.0f)):(((iTemp37==0)?true:false)?((75.0f * fTemp40) + 2600.0f):2675.0f)):(((iTemp35==0)?true:false)?((325.0f * fTemp38) + 2675.0f):3000.0f)):3000.0f):(((iTemp31==0)?true:false)?((350.0f * fTemp34) + 3000.0f):3350.0f)):(((iTemp29==0)?true:false)?(3350.0f - (350.0f * fTemp32)):3000.0f)):3000.0f):(((iTemp25==0)?true:false)?((900.0f * fTemp28) + 3000.0f):3900.0f)):(((iTemp22==0)?true:false)?(3900.0f - (300.0f * fTemp26)):3600.0f)):(((iTemp20==0)?true:false)?((300.0f * fTemp23) + 3600.0f):3900.0f)):(((iTemp18==0)?true:false)?(3900.0f - (100.0f * fTemp21)):3800.0f)):3800.0f):(((iTemp14==0)?true:false)?(3800.0f - (900.0f * fTemp17)):2900.0f)):(((iTemp12==0)?true:false)?((300.0f * fTemp15) + 2900.0f):3200.0f)):(((iTemp10==0)?true:false)?((50.0f * fTemp13) + 3200.0f):3250.0f)):(((iTemp7==0)?true:false)?(3250.0f - (450.0f * fTemp11)):2800.0f)):(((iTemp8==0)?true:false)?(fTemp83 + 2800.0f):2900.0f));
			float fTemp99 = (float)java.lang.Math.tan((fConst6 * fTemp98));
			float fTemp100 = (1.0f / fTemp99);
			float fTemp101 = ((((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?130.0f:(((iTemp53==0)?true:false)?(fTemp67 + 130.0f):150.0f)):150.0f):(((iTemp49==0)?true:false)?(150.0f - fTemp66):130.0f)):(((iTemp47==0)?true:false)?((50.0f * fTemp50) + 130.0f):180.0f)):(((iTemp46==0)?true:false)?(180.0f - fTemp92):120.0f)):120.0f):120.0f):120.0f):120.0f):(((iTemp35==0)?true:false)?(fTemp78 + 120.0f):130.0f)):(((iTemp33==0)?true:false)?(130.0f - fTemp63):120.0f)):120.0f):120.0f):120.0f):(((iTemp25==0)?true:false)?((10.0f * fTemp28) + 120.0f):130.0f)):(((iTemp22==0)?true:false)?(fTemp62 + 130.0f):150.0f)):(((iTemp20==0)?true:false)?(150.0f - (30.0f * fTemp23)):120.0f)):120.0f):(((iTemp16==0)?true:false)?((60.0f * fTemp19) + 120.0f):180.0f)):(((iTemp14==0)?true:false)?(180.0f - fTemp84):130.0f)):(((iTemp12==0)?true:false)?(130.0f - fTemp77):120.0f)):120.0f):(((iTemp7==0)?true:false)?(fTemp76 + 120.0f):130.0f)):(((iTemp8==0)?true:false)?(130.0f - (10.0f * fTemp9)):120.0f)) / fTemp98);
			float fTemp102 = (((fTemp100 + fTemp101) / fTemp99) + 1.0f);
			fRec12[0] = (fTemp5 - (((fRec12[2] * (((fTemp100 - fTemp101) / fTemp99) + 1.0f)) + (2.0f * (fRec12[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp99)))))) / fTemp102));
			float fTemp103 = (((iTemp31==0)?true:false)?(0.100000001f - (0.0841509998f * fTemp34)):0.0158489998f);
			float fTemp104 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?0.0158489998f:(((iTemp53==0)?true:false)?((0.00193400006f * fTemp6) + 0.0158489998f):0.0177829992f)):(((iTemp51==0)?true:false)?(0.0177829992f - (0.00193400006f * fTemp54)):0.0158489998f)):(((iTemp49==0)?true:false)?((0.0239620004f * fTemp52) + 0.0158489998f):0.0398110002f)):(((iTemp47==0)?true:false)?(0.0398110002f - (0.0298110005f * fTemp50)):0.00999999978f)):(((iTemp46==0)?true:false)?((0.344812989f * fTemp48) + 0.00999999978f):0.35481301f)):(((iTemp44==0)?true:false)?(0.35481301f - (0.103624001f * fRec6[0])):0.251188993f)):(((iTemp42==0)?true:false)?(0.251188993f - (0.171755999f * fTemp45)):0.0794330016f)):(((iTemp39==0)?true:false)?((0.0205669999f * fTemp43) + 0.0794330016f):0.100000001f)):(((iTemp37==0)?true:false)?(0.100000001f - (0.0601890013f * fTemp40)):0.0398110002f)):(((iTemp35==0)?true:false)?((0.0232849997f * fTemp38) + 0.0398110002f):0.0630960017f)):(((iTemp33==0)?true:false)?((0.0369039997f * fTemp36) + 0.0630960017f):0.100000001f)):fTemp103):(((iTemp29==0)?true:false)?((0.0635839999f * fTemp32) + 0.0158489998f):0.0794330016f)):(((iTemp27==0)?true:false)?(0.0794330016f - (0.0478099994f * fTemp30)):0.0316229984f)):(((iTemp25==0)?true:false)?((0.0683770031f * fTemp28) + 0.0316229984f):0.100000001f)):(((iTemp22==0)?true:false)?(0.100000001f - (0.0900000036f * fTemp26)):0.00999999978f)):(((iTemp20==0)?true:false)?((0.0401189998f * fTemp23) + 0.00999999978f):0.0501190014f)):fTemp95):(((iTemp16==0)?true:false)?(0.0794330016f - (0.0694330037f * fTemp19)):0.00999999978f)):(((iTemp14==0)?true:false)?((0.388107002f * fTemp17) + 0.00999999978f):0.398106992f)):(((iTemp12==0)?true:false)?(0.398106992f - (0.198580995f * fTemp15)):0.199525997f)):(((iTemp10==0)?true:false)?(0.199525997f - (0.099526003f * fTemp13)):0.100000001f)):(((iTemp7==0)?true:false)?((0.151188999f * fTemp11) + 0.100000001f):0.251188993f)):(((iTemp8==0)?true:false)?(0.251188993f - (0.0516630001f * fTemp9)):0.199525997f));
			float fTemp105 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?4950.0f:(((iTemp46==0)?true:false)?(4950.0f - (2200.0f * fTemp48)):2750.0f)):(((iTemp44==0)?true:false)?(fTemp97 + 2750.0f):3100.0f)):(((iTemp42==0)?true:false)?((240.0f * fTemp45) + 3100.0f):3340.0f)):(((iTemp39==0)?true:false)?(3340.0f - (440.0f * fTemp43)):2900.0f)):(((iTemp37==0)?true:false)?(fTemp41 + 2900.0f):2950.0f)):(((iTemp35==0)?true:false)?((400.0f * fTemp38) + 2950.0f):3350.0f)):(((iTemp33==0)?true:false)?(3350.0f - fTemp85):3300.0f)):(((iTemp31==0)?true:false)?((290.0f * fTemp34) + 3300.0f):3590.0f)):(((iTemp29==0)?true:false)?(3590.0f - (290.0f * fTemp32)):3300.0f)):(((iTemp27==0)?true:false)?((100.0f * fTemp30) + 3300.0f):3400.0f)):(((iTemp25==0)?true:false)?((1550.0f * fTemp28) + 3400.0f):4950.0f)):4950.0f):4950.0f):4950.0f):4950.0f):(((iTemp14==0)?true:false)?(4950.0f - (1700.0f * fTemp17)):3250.0f)):(((iTemp12==0)?true:false)?((330.0f * fTemp15) + 3250.0f):3580.0f)):(((iTemp10==0)?true:false)?(3580.0f - (40.0f * fTemp13)):3540.0f)):(((iTemp7==0)?true:false)?(3540.0f - (540.0f * fTemp11)):3000.0f)):(((iTemp8==0)?true:false)?((300.0f * fTemp9) + 3000.0f):3300.0f));
			float fTemp106 = (float)java.lang.Math.tan((fConst6 * fTemp105));
			float fTemp107 = (1.0f / fTemp106);
			float fTemp108 = ((((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?(((iTemp53==0)?true:false)?(((iTemp55==0)?true:false)?140.0f:(((iTemp53==0)?true:false)?((60.0f * fTemp6) + 140.0f):200.0f)):200.0f):(((iTemp49==0)?true:false)?(200.0f - (65.0f * fTemp52)):135.0f)):(((iTemp47==0)?true:false)?((65.0f * fTemp50) + 135.0f):200.0f)):(((iTemp46==0)?true:false)?(200.0f - (70.0f * fTemp48)):130.0f)):(((iTemp44==0)?true:false)?(130.0f - fTemp79):120.0f)):120.0f):120.0f):120.0f):(((iTemp35==0)?true:false)?(fTemp91 + 120.0f):140.0f)):(((iTemp33==0)?true:false)?(140.0f - fTemp90):120.0f)):120.0f):120.0f):120.0f):(((iTemp25==0)?true:false)?(fTemp89 + 120.0f):140.0f)):(((iTemp22==0)?true:false)?((60.0f * fTemp26) + 140.0f):200.0f)):(((iTemp20==0)?true:false)?(200.0f - fTemp24):120.0f)):120.0f):(((iTemp16==0)?true:false)?((80.0f * fTemp19) + 120.0f):200.0f)):(((iTemp14==0)?true:false)?(200.0f - (60.0f * fTemp17)):140.0f)):(((iTemp12==0)?true:false)?(140.0f - fTemp61):120.0f)):120.0f):(((iTemp7==0)?true:false)?((15.0f * fTemp11) + 120.0f):135.0f)):(((iTemp8==0)?true:false)?(135.0f - (15.0f * fTemp9)):120.0f)) / fTemp105);
			float fTemp109 = (((fTemp107 + fTemp108) / fTemp106) + 1.0f);
			fRec13[0] = (fTemp5 - (((fRec13[2] * (((fTemp107 - fTemp108) / fTemp106) + 1.0f)) + (2.0f * (fRec13[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp106)))))) / fTemp109));
			float fTemp110 = (((iTemp7==0)?true:false)?(((iTemp10==0)?true:false)?(((iTemp12==0)?true:false)?(((iTemp14==0)?true:false)?(((iTemp16==0)?true:false)?(((iTemp18==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp25==0)?true:false)?(((iTemp27==0)?true:false)?(((iTemp29==0)?true:false)?(((iTemp31==0)?true:false)?(((iTemp33==0)?true:false)?(((iTemp35==0)?true:false)?(((iTemp37==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp47==0)?true:false)?(((iTemp49==0)?true:false)?(((iTemp51==0)?true:false)?0.00100000005f:(((iTemp49==0)?true:false)?((0.000777999987f * fTemp52) + 0.00100000005f):0.00177800003f)):(((iTemp47==0)?true:false)?(0.00177800003f - (0.001147f * fTemp50)):0.000630999974f)):(((iTemp46==0)?true:false)?((0.0993689969f * fTemp48) + 0.000630999974f):0.100000001f)):(((iTemp44==0)?true:false)?((0.0258930009f * fRec6[0]) + 0.100000001f):0.125892997f)):(((iTemp42==0)?true:false)?(0.125892997f - (0.0860819966f * fTemp45)):0.0398110002f)):(((iTemp39==0)?true:false)?(0.0398110002f - (0.0298110005f * fTemp43)):0.00999999978f)):(((iTemp37==0)?true:false)?((0.00584900007f * fTemp40) + 0.00999999978f):0.0158489998f)):(((iTemp35==0)?true:false)?(0.0158489998f - (0.00325999991f * fTemp38)):0.0125890002f)):(((iTemp33==0)?true:false)?((0.0874110013f * fTemp36) + 0.0125890002f):0.100000001f)):fTemp103):(((iTemp29==0)?true:false)?((0.00410400005f * fTemp32) + 0.0158489998f):0.0199529994f)):0.0199529994f):(((iTemp25==0)?true:false)?(0.0199529994f - (0.0167909991f * fTemp28)):0.0031620001f)):(((iTemp22==0)?true:false)?(0.0031620001f - (0.00157700002f * fTemp26)):0.00158499996f)):(((iTemp20==0)?true:false)?((0.00472499989f * fTemp23) + 0.00158499996f):0.00631000008f)):(((iTemp18==0)?true:false)?(0.00631000008f - (0.00314799999f * fTemp21)):0.0031620001f)):(((iTemp16==0)?true:false)?(0.0031620001f - (0.00216199993f * fTemp19)):0.00100000005f)):(((iTemp14==0)?true:false)?((0.0784329996f * fTemp17) + 0.00100000005f):0.0794330016f)):(((iTemp12==0)?true:false)?((0.0205669999f * fTemp15) + 0.0794330016f):0.100000001f)):(((iTemp10==0)?true:false)?(0.100000001f - (0.0683770031f * fTemp13)):0.0316229984f)):(((iTemp7==0)?true:false)?((0.0184959993f * fTemp11) + 0.0316229984f):0.0501190014f)):0.0501190014f);
			float fTemp111 = (((((((fRec0[2] * (0.0f - (fTemp70 / fTemp59))) + ((fRec0[0] * fTemp70) / fTemp59)) / fTemp69) + (((fRec10[2] * (0.0f - ((fTemp70 * fTemp82) / fTemp74))) + (((fRec10[0] * fTemp70) * fTemp82) / fTemp74)) / fTemp81)) + (((fRec11[2] * (0.0f - ((fTemp70 * fTemp96) / fTemp87))) + (((fRec11[0] * fTemp70) * fTemp96) / fTemp87)) / fTemp94)) + (((fRec12[2] * (0.0f - ((fTemp70 * fTemp104) / fTemp99))) + (((fRec12[0] * fTemp70) * fTemp104) / fTemp99)) / fTemp102)) + (((fRec13[2] * (0.0f - ((fTemp70 * fTemp110) / fTemp106))) + (((fRec13[0] * fTemp70) * fTemp110) / fTemp106)) / fTemp109));
			output0[i] = fTemp111;
			output1[i] = fTemp111;
			iVec0[1] = iVec0[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			
		}
		
	}
	
};

