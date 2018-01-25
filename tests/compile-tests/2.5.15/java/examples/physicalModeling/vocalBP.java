/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "Vocal BandPass"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fHslider0;
	int iVec0[] = new int[2];
	float fHslider1;
	float fRec1[] = new float[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider2;
	float fHslider3;
	float fConst2;
	float fHslider4;
	float fRec4[] = new float[2];
	float fRec5[] = new float[2];
	float fRec2[] = new float[2];
	int iRec6[] = new int[2];
	float fConst3;
	float fHslider5;
	float fHslider6;
	float fRec7[] = new float[2];
	float fRec0[] = new float[3];
	float fRec8[] = new float[2];
	float fRec9[] = new float[2];
	float fRec10[] = new float[3];
	float fRec11[] = new float[3];
	float fRec12[] = new float[3];
	float fRec13[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("description", "Simple source-filter vocal synthesizer.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocal BandPass");
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
		fConst2 = (6.28318548f / fConst0);
		fConst3 = (3.14159274f / fConst0);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.90000000000000002f;
		fHslider1 = (float)0.0f;
		fHslider2 = (float)440.0f;
		fHslider3 = (float)0.5f;
		fHslider4 = (float)6.0f;
		fHslider5 = (float)0.0f;
		fHslider6 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec6[l5] = 0;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
			
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
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.addHorizontalSlider("freq", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.addHorizontalSlider("gain", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.addHorizontalSlider("voiceType", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.addHorizontalSlider("vowel", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface.declare("fHslider1", "4", "");
		ui_interface.addHorizontalSlider("fricative", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider4", "5", "");
		ui_interface.addHorizontalSlider("vibratoFreq", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 6.0f, 1.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider3", "6", "");
		ui_interface.addHorizontalSlider("vibratoGain", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
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
		float fSlow3 = (0.100000001f * fHslider3);
		float fSlow4 = (fConst2 * fHslider4);
		float fSlow5 = (float)java.lang.Math.sin(fSlow4);
		float fSlow6 = (float)java.lang.Math.cos(fSlow4);
		float fSlow7 = (0.0f - fSlow5);
		float fSlow8 = fHslider5;
		float fSlow9 = (5.0f * fSlow8);
		float fSlow10 = (0.00100000005f * fHslider6);
		float fSlow11 = (5.0f * (1.0f - fSlow8));
		int iSlow12 = ((((fSlow8 == 0.0f))?1:(((fSlow8 == 3.0f))?1:0)) == 0);
		int iSlow13 = (fSlow8 != 2.0f);
		float fSlow14 = (2.0f * fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec1[0] = (fSlow1 + (0.999000013f * fRec1[1]));
			fRec4[0] = ((fSlow5 * fRec5[1]) + (fSlow6 * fRec4[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec5[0] = (((fSlow6 * fRec5[1]) + (fSlow7 * fRec4[1])) + (float)iTemp0);
			float fTemp1 = (float)java.lang.Math.max(1.00000001e-07f, (float)java.lang.Math.abs((fSlow2 * ((fSlow3 * fRec4[0]) + 1.0f))));
			float fTemp2 = (fRec2[1] + (fConst1 * fTemp1));
			float fTemp3 = (fTemp2 + -1.0f);
			int iTemp4 = (fTemp3 < 0.0f);
			fRec2[0] = (((iTemp4==0)?true:false)?fTemp2:fTemp3);
			float fRec3 = (((iTemp4==0)?true:false)?fTemp2:(fTemp2 + (fTemp3 * (1.0f - (fConst0 / fTemp1)))));
			iRec6[0] = ((1103515245 * iRec6[1]) + 12345);
			float fTemp5 = (fSlow0 * (((1.0f - fRec1[0]) * ((2.0f * fRec3) + -1.0f)) + (4.65661287e-10f * (fRec1[0] * (float)iRec6[0]))));
			fRec7[0] = (fSlow10 + (0.999000013f * fRec7[1]));
			float fTemp6 = (fSlow9 + fRec7[0]);
			int iTemp7 = (fTemp6 < 23.0f);
			int iTemp8 = (fTemp6 < 24.0f);
			float fTemp9 = (fSlow9 + (fRec7[0] + -23.0f));
			float fTemp10 = (100.0f * fTemp9);
			int iTemp11 = (fTemp6 < 22.0f);
			float fTemp12 = (fSlow9 + (fRec7[0] + -22.0f));
			int iTemp13 = (fTemp6 < 21.0f);
			float fTemp14 = (fSlow9 + (fRec7[0] + -21.0f));
			int iTemp15 = (fTemp6 < 20.0f);
			float fTemp16 = (fSlow9 + (fRec7[0] + -20.0f));
			int iTemp17 = (fTemp6 < 19.0f);
			float fTemp18 = (fSlow9 + (fRec7[0] + -19.0f));
			float fTemp19 = (50.0f * fTemp18);
			int iTemp20 = (fTemp6 < 18.0f);
			float fTemp21 = (fSlow9 + (fRec7[0] + -18.0f));
			int iTemp22 = (fTemp6 < 17.0f);
			float fTemp23 = (fSlow9 + (fRec7[0] + -17.0f));
			int iTemp24 = (fTemp6 < 16.0f);
			float fTemp25 = (fSlow9 + (fRec7[0] + -16.0f));
			int iTemp26 = (fTemp6 < 15.0f);
			float fTemp27 = (fSlow9 + (fRec7[0] + -15.0f));
			int iTemp28 = (fTemp6 < 14.0f);
			float fTemp29 = (fSlow9 + (fRec7[0] + -14.0f));
			int iTemp30 = (fTemp6 < 13.0f);
			float fTemp31 = (fSlow9 + (fRec7[0] + -13.0f));
			int iTemp32 = (fTemp6 < 12.0f);
			float fTemp33 = (fSlow9 + (fRec7[0] + -12.0f));
			int iTemp34 = (fTemp6 < 11.0f);
			float fTemp35 = (fSlow9 + (fRec7[0] + -11.0f));
			int iTemp36 = (fTemp6 < 10.0f);
			float fTemp37 = (fSlow9 + (fRec7[0] + -10.0f));
			float fTemp38 = (50.0f * fTemp37);
			int iTemp39 = (fTemp6 < 9.0f);
			float fTemp40 = (fSlow9 + (fRec7[0] + -9.0f));
			int iTemp41 = (fTemp6 < 8.0f);
			int iTemp42 = (fTemp6 < 7.0f);
			float fTemp43 = (fSlow9 + (fRec7[0] + -7.0f));
			int iTemp44 = (fTemp6 < 6.0f);
			float fTemp45 = (fSlow9 + (fRec7[0] + -6.0f));
			int iTemp46 = (fTemp6 < 5.0f);
			float fTemp47 = (fRec7[0] - fSlow11);
			int iTemp48 = (fTemp6 < 4.0f);
			float fTemp49 = (fSlow9 + (fRec7[0] + -4.0f));
			int iTemp50 = (fTemp6 < 3.0f);
			float fTemp51 = (fSlow9 + (fRec7[0] + -3.0f));
			int iTemp52 = (fTemp6 < 2.0f);
			float fTemp53 = (fSlow9 + (fRec7[0] + -2.0f));
			int iTemp54 = (fTemp6 < 1.0f);
			int iTemp55 = (fTemp6 < 0.0f);
			float fTemp56 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?2800.0f:(((iTemp54==0)?true:false)?(2800.0f - (100.0f * fTemp6)):2700.0f)):2700.0f):(((iTemp50==0)?true:false)?((130.0f * fTemp53) + 2700.0f):2830.0f)):(((iTemp48==0)?true:false)?(2830.0f - (300.0f * fTemp51)):2530.0f)):(((iTemp46==0)?true:false)?(2530.0f - (280.0f * fTemp49)):2250.0f)):(((iTemp44==0)?true:false)?((150.0f * fTemp47) + 2250.0f):2400.0f)):(((iTemp42==0)?true:false)?((200.0f * fTemp45) + 2400.0f):2600.0f)):(((iTemp41==0)?true:false)?(2600.0f - (200.0f * fTemp43)):2400.0f)):2400.0f):(((iTemp36==0)?true:false)?((350.0f * fTemp40) + 2400.0f):2750.0f)):(((iTemp34==0)?true:false)?(2750.0f - fTemp38):2700.0f)):(((iTemp32==0)?true:false)?((200.0f * fTemp35) + 2700.0f):2900.0f)):(((iTemp30==0)?true:false)?(2900.0f - (200.0f * fTemp33)):2700.0f)):(((iTemp28==0)?true:false)?((50.0f * fTemp31) + 2700.0f):2750.0f)):(((iTemp26==0)?true:false)?((150.0f * fTemp29) + 2750.0f):2900.0f)):(((iTemp24==0)?true:false)?(2900.0f - (100.0f * fTemp27)):2800.0f)):(((iTemp22==0)?true:false)?((150.0f * fTemp25) + 2800.0f):2950.0f)):(((iTemp20==0)?true:false)?(2950.0f - (120.0f * fTemp23)):2830.0f)):(((iTemp17==0)?true:false)?(2830.0f - (130.0f * fTemp21)):2700.0f)):(((iTemp15==0)?true:false)?(2700.0f - fTemp19):2650.0f)):(((iTemp13==0)?true:false)?(2650.0f - (50.0f * fTemp16)):2600.0f)):(((iTemp11==0)?true:false)?((200.0f * fTemp14) + 2600.0f):2800.0f)):(((iTemp7==0)?true:false)?(2800.0f - (200.0f * fTemp12)):2600.0f)):(((iTemp8==0)?true:false)?(fTemp10 + 2600.0f):2700.0f));
			float fTemp57 = (float)java.lang.Math.tan((fConst3 * fTemp56));
			float fTemp58 = (1.0f / fTemp57);
			float fTemp59 = (20.0f * fTemp16);
			float fTemp60 = (20.0f * fTemp29);
			float fTemp61 = (20.0f * fTemp37);
			float fTemp62 = (20.0f * fTemp40);
			float fTemp63 = (10.0f * fTemp47);
			float fTemp64 = (60.0f * fTemp49);
			float fTemp65 = (20.0f * fTemp53);
			float fTemp66 = ((((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?120.0f:(((iTemp50==0)?true:false)?(120.0f - fTemp65):100.0f)):(((iTemp48==0)?true:false)?((70.0f * fTemp51) + 100.0f):170.0f)):(((iTemp46==0)?true:false)?(170.0f - fTemp64):110.0f)):(((iTemp44==0)?true:false)?(110.0f - fTemp63):100.0f)):100.0f):100.0f):100.0f):(((iTemp36==0)?true:false)?(fTemp62 + 100.0f):120.0f)):(((iTemp34==0)?true:false)?(120.0f - fTemp61):100.0f)):100.0f):100.0f):100.0f):(((iTemp26==0)?true:false)?(fTemp60 + 100.0f):120.0f)):120.0f):(((iTemp22==0)?true:false)?(120.0f - (20.0f * fTemp25)):100.0f)):100.0f):(((iTemp17==0)?true:false)?((70.0f * fTemp21) + 100.0f):170.0f)):(((iTemp15==0)?true:false)?(170.0f - fTemp19):120.0f)):(((iTemp13==0)?true:false)?(120.0f - fTemp59):100.0f)):100.0f):100.0f):100.0f) / fTemp56);
			float fTemp67 = (((fTemp58 + fTemp66) / fTemp57) + 1.0f);
			fRec0[0] = (fTemp5 - (((fRec0[2] * (((fTemp58 - fTemp66) / fTemp57) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp57)))))) / fTemp67));
			fRec8[0] = ((fSlow5 * fRec9[1]) + (fSlow6 * fRec8[1]));
			fRec9[0] = (((fSlow6 * fRec9[1]) + (fSlow7 * fRec8[1])) + (float)iTemp0);
			float fTemp68 = ((fSlow3 * fRec8[0]) + 1.0f);
			float fTemp69 = (fSlow2 * fTemp68);
			float fTemp70 = ((0.000839999993f * (1000.0f - fTemp69)) + 0.800000012f);
			float fTemp71 = (((iTemp20==0)?true:false)?((0.0293140002f * fTemp23) + 0.0501190014f):0.0794330016f);
			float fTemp72 = (fSlow9 + (fRec7[0] + -8.0f));
			float fTemp73 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?0.100000001f:(((iTemp54==0)?true:false)?(0.100000001f - (0.0683770031f * fTemp6)):0.0316229984f)):0.0316229984f):(((iTemp50==0)?true:false)?((0.126865998f * fTemp53) + 0.0316229984f):0.158489004f)):(((iTemp48==0)?true:false)?(0.158489004f - (0.126865998f * fTemp51)):0.0316229984f)):(((iTemp46==0)?true:false)?((0.323190004f * fTemp49) + 0.0316229984f):0.35481301f)):0.35481301f):(((iTemp42==0)?true:false)?(0.35481301f - (0.196324006f * fTemp45)):0.158489004f)):(((iTemp41==0)?true:false)?(0.158489004f - (0.0693639964f * fTemp43)):0.0891249999f)):(((iTemp39==0)?true:false)?(0.0891249999f - (0.0640060008f * fTemp72)):0.0251189992f)):(((iTemp36==0)?true:false)?((0.0456760004f * fTemp40) + 0.0251189992f):0.0707949996f)):(((iTemp34==0)?true:false)?((0.0550980009f * fTemp37) + 0.0707949996f):0.125892997f)):(((iTemp32==0)?true:false)?(0.125892997f - (0.0627970025f * fTemp35)):0.0630960017f)):(((iTemp30==0)?true:false)?(0.0630960017f - (0.0129770003f * fTemp33)):0.0501190014f)):(((iTemp28==0)?true:false)?((0.020676f * fTemp31) + 0.0501190014f):0.0707949996f)):(((iTemp26==0)?true:false)?(0.0707949996f - (0.0456760004f * fTemp29)):0.0251189992f)):(((iTemp24==0)?true:false)?((0.152709007f * fTemp27) + 0.0251189992f):0.177827999f)):(((iTemp22==0)?true:false)?(0.177827999f - (0.127709001f * fTemp25)):0.0501190014f)):fTemp71):(((iTemp17==0)?true:false)?(0.0794330016f - (0.0616500005f * fTemp21)):0.0177829992f)):(((iTemp15==0)?true:false)?((0.428900987f * fTemp18) + 0.0177829992f):0.446684003f)):(((iTemp13==0)?true:false)?(0.446684003f - (0.195494995f * fTemp16)):0.251188993f)):(((iTemp11==0)?true:false)?(0.251188993f - (0.125295997f * fTemp14)):0.125892997f)):(((iTemp7==0)?true:false)?((0.125295997f * fTemp12) + 0.125892997f):0.251188993f)):(((iTemp8==0)?true:false)?(0.251188993f - (0.109935001f * fTemp9)):0.141253993f));
			float fTemp74 = ((0.00366666657f * (400.0f - fTemp69)) + 3.0f);
			float fTemp75 = (((iSlow12==0)?true:false)?(fTemp74 * fTemp73):(fTemp70 * fTemp73));
			float fTemp76 = (350.0f * fTemp47);
			float fTemp77 = (fSlow9 + (fRec7[0] + -1.0f));
			float fTemp78 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?3500.0f:(((iTemp54==0)?true:false)?(3500.0f - (200.0f * fTemp6)):3300.0f)):(((iTemp52==0)?true:false)?((400.0f * fTemp77) + 3300.0f):3700.0f)):(((iTemp50==0)?true:false)?(3700.0f - (200.0f * fTemp53)):3500.0f)):3500.0f):(((iTemp46==0)?true:false)?(3500.0f - (1050.0f * fTemp49)):2450.0f)):(((iTemp44==0)?true:false)?(fTemp76 + 2450.0f):2800.0f)):(((iTemp42==0)?true:false)?((250.0f * fTemp45) + 2800.0f):3050.0f)):(((iTemp41==0)?true:false)?(3050.0f - (450.0f * fTemp43)):2600.0f)):(((iTemp39==0)?true:false)?((75.0f * fTemp72) + 2600.0f):2675.0f)):(((iTemp36==0)?true:false)?((325.0f * fTemp40) + 2675.0f):3000.0f)):3000.0f):(((iTemp32==0)?true:false)?((350.0f * fTemp35) + 3000.0f):3350.0f)):(((iTemp30==0)?true:false)?(3350.0f - (350.0f * fTemp33)):3000.0f)):3000.0f):(((iTemp26==0)?true:false)?((900.0f * fTemp29) + 3000.0f):3900.0f)):(((iTemp24==0)?true:false)?(3900.0f - (300.0f * fTemp27)):3600.0f)):(((iTemp22==0)?true:false)?((300.0f * fTemp25) + 3600.0f):3900.0f)):(((iTemp20==0)?true:false)?(3900.0f - (100.0f * fTemp23)):3800.0f)):3800.0f):(((iTemp15==0)?true:false)?(3800.0f - (900.0f * fTemp18)):2900.0f)):(((iTemp13==0)?true:false)?((300.0f * fTemp16) + 2900.0f):3200.0f)):(((iTemp11==0)?true:false)?((50.0f * fTemp14) + 3200.0f):3250.0f)):(((iTemp7==0)?true:false)?(3250.0f - (450.0f * fTemp12)):2800.0f)):(((iTemp8==0)?true:false)?(fTemp10 + 2800.0f):2900.0f));
			float fTemp79 = (float)java.lang.Math.tan((fConst3 * fTemp78));
			float fTemp80 = (1.0f / fTemp79);
			float fTemp81 = (10.0f * fTemp12);
			float fTemp82 = (10.0f * fTemp16);
			float fTemp83 = (20.0f * fTemp27);
			float fTemp84 = (10.0f * fTemp37);
			float fTemp85 = (10.0f * fTemp40);
			float fTemp86 = (20.0f * fTemp6);
			float fTemp87 = ((((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?130.0f:(((iTemp54==0)?true:false)?(fTemp86 + 130.0f):150.0f)):150.0f):(((iTemp50==0)?true:false)?(150.0f - fTemp65):130.0f)):(((iTemp48==0)?true:false)?((50.0f * fTemp51) + 130.0f):180.0f)):(((iTemp46==0)?true:false)?(180.0f - fTemp64):120.0f)):120.0f):120.0f):120.0f):120.0f):(((iTemp36==0)?true:false)?(fTemp85 + 120.0f):130.0f)):(((iTemp34==0)?true:false)?(130.0f - fTemp84):120.0f)):120.0f):120.0f):120.0f):(((iTemp26==0)?true:false)?((10.0f * fTemp29) + 120.0f):130.0f)):(((iTemp24==0)?true:false)?(fTemp83 + 130.0f):150.0f)):(((iTemp22==0)?true:false)?(150.0f - (30.0f * fTemp25)):120.0f)):120.0f):(((iTemp17==0)?true:false)?((60.0f * fTemp21) + 120.0f):180.0f)):(((iTemp15==0)?true:false)?(180.0f - fTemp19):130.0f)):(((iTemp13==0)?true:false)?(130.0f - fTemp82):120.0f)):120.0f):(((iTemp7==0)?true:false)?(fTemp81 + 120.0f):130.0f)):(((iTemp8==0)?true:false)?(130.0f - (10.0f * fTemp9)):120.0f)) / fTemp78);
			float fTemp88 = (((fTemp80 + fTemp87) / fTemp79) + 1.0f);
			fRec10[0] = (fTemp5 - (((fRec10[2] * (((fTemp80 - fTemp87) / fTemp79) + 1.0f)) + (2.0f * (fRec10[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp79)))))) / fTemp88));
			float fTemp89 = (((iTemp32==0)?true:false)?(0.100000001f - (0.0841509998f * fTemp35)):0.0158489998f);
			float fTemp90 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?0.0158489998f:(((iTemp54==0)?true:false)?((0.00193400006f * fTemp6) + 0.0158489998f):0.0177829992f)):(((iTemp52==0)?true:false)?(0.0177829992f - (0.00193400006f * fTemp77)):0.0158489998f)):(((iTemp50==0)?true:false)?((0.0239620004f * fTemp53) + 0.0158489998f):0.0398110002f)):(((iTemp48==0)?true:false)?(0.0398110002f - (0.0298110005f * fTemp51)):0.00999999978f)):(((iTemp46==0)?true:false)?((0.344812989f * fTemp49) + 0.00999999978f):0.35481301f)):(((iTemp44==0)?true:false)?(0.35481301f - (0.103624001f * fTemp47)):0.251188993f)):(((iTemp42==0)?true:false)?(0.251188993f - (0.171755999f * fTemp45)):0.0794330016f)):(((iTemp41==0)?true:false)?((0.0205669999f * fTemp43) + 0.0794330016f):0.100000001f)):(((iTemp39==0)?true:false)?(0.100000001f - (0.0601890013f * fTemp72)):0.0398110002f)):(((iTemp36==0)?true:false)?((0.0232849997f * fTemp40) + 0.0398110002f):0.0630960017f)):(((iTemp34==0)?true:false)?((0.0369039997f * fTemp37) + 0.0630960017f):0.100000001f)):fTemp89):(((iTemp30==0)?true:false)?((0.0635839999f * fTemp33) + 0.0158489998f):0.0794330016f)):(((iTemp28==0)?true:false)?(0.0794330016f - (0.0478099994f * fTemp31)):0.0316229984f)):(((iTemp26==0)?true:false)?((0.0683770031f * fTemp29) + 0.0316229984f):0.100000001f)):(((iTemp24==0)?true:false)?(0.100000001f - (0.0900000036f * fTemp27)):0.00999999978f)):(((iTemp22==0)?true:false)?((0.0401189998f * fTemp25) + 0.00999999978f):0.0501190014f)):fTemp71):(((iTemp17==0)?true:false)?(0.0794330016f - (0.0694330037f * fTemp21)):0.00999999978f)):(((iTemp15==0)?true:false)?((0.388107002f * fTemp18) + 0.00999999978f):0.398106992f)):(((iTemp13==0)?true:false)?(0.398106992f - (0.198580995f * fTemp16)):0.199525997f)):(((iTemp11==0)?true:false)?(0.199525997f - (0.099526003f * fTemp14)):0.100000001f)):(((iTemp7==0)?true:false)?((0.151188999f * fTemp12) + 0.100000001f):0.251188993f)):(((iTemp8==0)?true:false)?(0.251188993f - (0.0516630001f * fTemp9)):0.199525997f));
			float fTemp91 = (((iSlow12==0)?true:false)?(fTemp90 * fTemp74):(fTemp90 * fTemp70));
			float fTemp92 = (80.0f * fTemp25);
			float fTemp93 = (50.0f * fTemp72);
			float fTemp94 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?800.0f:(((iTemp54==0)?true:false)?(800.0f - (400.0f * fTemp6)):400.0f)):(((iTemp52==0)?true:false)?(400.0f - (50.0f * fTemp77)):350.0f)):(((iTemp50==0)?true:false)?((100.0f * fTemp53) + 350.0f):450.0f)):(((iTemp48==0)?true:false)?(450.0f - (125.0f * fTemp51)):325.0f)):(((iTemp46==0)?true:false)?((275.0f * fTemp49) + 325.0f):600.0f)):(((iTemp44==0)?true:false)?(600.0f - (200.0f * fTemp47)):400.0f)):(((iTemp42==0)?true:false)?(400.0f - (150.0f * fTemp45)):250.0f)):(((iTemp41==0)?true:false)?((150.0f * fTemp43) + 250.0f):400.0f)):(((iTemp39==0)?true:false)?(400.0f - fTemp93):350.0f)):(((iTemp36==0)?true:false)?((310.0f * fTemp40) + 350.0f):660.0f)):(((iTemp34==0)?true:false)?(660.0f - (220.0f * fTemp37)):440.0f)):(((iTemp32==0)?true:false)?(440.0f - (170.0f * fTemp35)):270.0f)):(((iTemp30==0)?true:false)?((160.0f * fTemp33) + 270.0f):430.0f)):(((iTemp28==0)?true:false)?(430.0f - (60.0f * fTemp31)):370.0f)):(((iTemp26==0)?true:false)?((430.0f * fTemp29) + 370.0f):800.0f)):(((iTemp24==0)?true:false)?(800.0f - (450.0f * fTemp27)):350.0f)):(((iTemp22==0)?true:false)?(350.0f - fTemp92):270.0f)):(((iTemp20==0)?true:false)?((180.0f * fTemp23) + 270.0f):450.0f)):(((iTemp17==0)?true:false)?(450.0f - (125.0f * fTemp21)):325.0f)):(((iTemp15==0)?true:false)?(325.0f * (fTemp18 + 1.0f)):650.0f)):(((iTemp13==0)?true:false)?(650.0f - (250.0f * fTemp16)):400.0f)):(((iTemp11==0)?true:false)?(400.0f - (110.0f * fTemp14)):290.0f)):(((iTemp7==0)?true:false)?((110.0f * fTemp12) + 290.0f):400.0f)):(((iTemp8==0)?true:false)?(400.0f - (50.0f * fTemp9)):350.0f));
			float fTemp95 = (((fTemp94 <= fTemp69))?fTemp69:fTemp94);
			float fTemp96 = (float)java.lang.Math.tan((fConst3 * fTemp95));
			float fTemp97 = (1.0f / fTemp96);
			float fTemp98 = (10.0f * fTemp49);
			float fTemp99 = (20.0f * fTemp51);
			float fTemp100 = ((((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?80.0f:(((iTemp54==0)?true:false)?(80.0f - fTemp86):60.0f)):(((iTemp52==0)?true:false)?(60.0f - (10.0f * fTemp77)):50.0f)):(((iTemp50==0)?true:false)?(fTemp65 + 50.0f):70.0f)):(((iTemp48==0)?true:false)?(70.0f - fTemp99):50.0f)):(((iTemp46==0)?true:false)?(fTemp98 + 50.0f):60.0f)):(((iTemp44==0)?true:false)?(60.0f - (20.0f * fTemp47)):40.0f)):(((iTemp42==0)?true:false)?((20.0f * fTemp45) + 40.0f):60.0f)):(((iTemp41==0)?true:false)?(60.0f - (20.0f * fTemp43)):40.0f)):40.0f):(((iTemp36==0)?true:false)?(40.0f * (fTemp40 + 1.0f)):80.0f)):(((iTemp34==0)?true:false)?(80.0f - fTemp84):70.0f)):(((iTemp32==0)?true:false)?(70.0f - (30.0f * fTemp35)):40.0f)):40.0f):40.0f):(((iTemp26==0)?true:false)?(40.0f * (fTemp29 + 1.0f)):80.0f)):(((iTemp24==0)?true:false)?(80.0f - fTemp83):60.0f)):60.0f):(((iTemp20==0)?true:false)?(60.0f - (20.0f * fTemp23)):40.0f)):(((iTemp17==0)?true:false)?((10.0f * fTemp21) + 40.0f):50.0f)):50.0f):(((iTemp13==0)?true:false)?(fTemp59 + 50.0f):70.0f)):(((iTemp11==0)?true:false)?(70.0f - (30.0f * fTemp14)):40.0f)):(((iTemp7==0)?true:false)?((30.0f * fTemp12) + 40.0f):70.0f)):(((iTemp8==0)?true:false)?(70.0f - (30.0f * fTemp9)):40.0f)) / fTemp95);
			float fTemp101 = (((fTemp97 + fTemp100) / fTemp96) + 1.0f);
			fRec11[0] = (fTemp5 - (((fRec11[2] * (((fTemp97 - fTemp100) / fTemp96) + 1.0f)) + (2.0f * (fRec11[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp96)))))) / fTemp101));
			float fTemp102 = (((iSlow12==0)?true:false)?fTemp74:fTemp70);
			float fTemp103 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?1150.0f:(((iTemp54==0)?true:false)?((450.0f * fTemp6) + 1150.0f):1600.0f)):(((iTemp52==0)?true:false)?((100.0f * fTemp77) + 1600.0f):1700.0f)):(((iTemp50==0)?true:false)?(1700.0f - (900.0f * fTemp53)):800.0f)):(((iTemp48==0)?true:false)?(800.0f - (100.0f * fTemp51)):700.0f)):(((iTemp46==0)?true:false)?((340.0f * fTemp49) + 700.0f):1040.0f)):(((iTemp44==0)?true:false)?((580.0f * fTemp47) + 1040.0f):1620.0f)):(((iTemp42==0)?true:false)?((130.0f * fTemp45) + 1620.0f):1750.0f)):(((iTemp41==0)?true:false)?(1750.0f - (1000.0f * fTemp43)):750.0f)):(((iTemp39==0)?true:false)?(750.0f - (150.0f * fTemp72)):600.0f)):(((iTemp36==0)?true:false)?((520.0f * fTemp40) + 600.0f):1120.0f)):(((iTemp34==0)?true:false)?((680.0f * fTemp37) + 1120.0f):1800.0f)):(((iTemp32==0)?true:false)?((50.0f * fTemp35) + 1800.0f):1850.0f)):(((iTemp30==0)?true:false)?(1850.0f - (1030.0f * fTemp33)):820.0f)):(((iTemp28==0)?true:false)?(820.0f - (190.0f * fTemp31)):630.0f)):(((iTemp26==0)?true:false)?((520.0f * fTemp29) + 630.0f):1150.0f)):(((iTemp24==0)?true:false)?((850.0f * fTemp27) + 1150.0f):2000.0f)):(((iTemp22==0)?true:false)?((140.0f * fTemp25) + 2000.0f):2140.0f)):(((iTemp20==0)?true:false)?(2140.0f - (1340.0f * fTemp23)):800.0f)):(((iTemp17==0)?true:false)?(800.0f - (100.0f * fTemp21)):700.0f)):(((iTemp15==0)?true:false)?((380.0f * fTemp18) + 700.0f):1080.0f)):(((iTemp13==0)?true:false)?((620.0f * fTemp16) + 1080.0f):1700.0f)):(((iTemp11==0)?true:false)?((170.0f * fTemp14) + 1700.0f):1870.0f)):(((iTemp7==0)?true:false)?(1870.0f - (1070.0f * fTemp12)):800.0f)):(((iTemp8==0)?true:false)?(800.0f - (200.0f * fTemp9)):600.0f));
			float fTemp104 = ((fSlow14 * fTemp68) + 30.0f);
			float fTemp105 = (((iSlow13==0)?true:false)?((((((fTemp103 >= 1300.0f))?1:0) & (((fTemp69 >= 200.0f))?1:0)))?(fTemp103 - (0.000952380942f * ((fTemp69 + -200.0f) * (fTemp103 + -1300.0f)))):(((fTemp103 <= fTemp104))?fTemp104:fTemp103)):fTemp103);
			float fTemp106 = (float)java.lang.Math.tan((fConst3 * fTemp105));
			float fTemp107 = (1.0f / fTemp106);
			float fTemp108 = ((((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?90.0f:(((iTemp54==0)?true:false)?(90.0f - (10.0f * fTemp6)):80.0f)):(((iTemp52==0)?true:false)?((20.0f * fTemp77) + 80.0f):100.0f)):(((iTemp50==0)?true:false)?(100.0f - fTemp65):80.0f)):(((iTemp48==0)?true:false)?(80.0f - fTemp99):60.0f)):(((iTemp46==0)?true:false)?(fTemp98 + 60.0f):70.0f)):(((iTemp44==0)?true:false)?(fTemp63 + 70.0f):80.0f)):(((iTemp42==0)?true:false)?((10.0f * fTemp45) + 80.0f):90.0f)):(((iTemp41==0)?true:false)?(90.0f - (10.0f * fTemp43)):80.0f)):80.0f):(((iTemp36==0)?true:false)?(fTemp85 + 80.0f):90.0f)):(((iTemp34==0)?true:false)?(90.0f - fTemp84):80.0f)):(((iTemp32==0)?true:false)?((10.0f * fTemp35) + 80.0f):90.0f)):(((iTemp30==0)?true:false)?(90.0f - (10.0f * fTemp33)):80.0f)):(((iTemp28==0)?true:false)?(80.0f - (20.0f * fTemp31)):60.0f)):(((iTemp26==0)?true:false)?((30.0f * fTemp29) + 60.0f):90.0f)):(((iTemp24==0)?true:false)?((10.0f * fTemp27) + 90.0f):100.0f)):(((iTemp22==0)?true:false)?(100.0f - (10.0f * fTemp25)):90.0f)):(((iTemp20==0)?true:false)?(90.0f - (10.0f * fTemp23)):80.0f)):(((iTemp17==0)?true:false)?(80.0f - (20.0f * fTemp21)):60.0f)):(((iTemp15==0)?true:false)?((30.0f * fTemp18) + 60.0f):90.0f)):(((iTemp13==0)?true:false)?(90.0f - fTemp82):80.0f)):(((iTemp11==0)?true:false)?((10.0f * fTemp14) + 80.0f):90.0f)):(((iTemp7==0)?true:false)?(90.0f - fTemp81):80.0f)):(((iTemp8==0)?true:false)?(80.0f - (20.0f * fTemp9)):60.0f)) / fTemp105);
			float fTemp109 = (((fTemp107 + fTemp108) / fTemp106) + 1.0f);
			fRec12[0] = (fTemp5 - (((fRec12[2] * (((fTemp107 - fTemp108) / fTemp106) + 1.0f)) + (2.0f * (fRec12[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp106)))))) / fTemp109));
			float fTemp110 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?0.630957007f:(((iTemp54==0)?true:false)?(0.630957007f - (0.567861021f * fTemp6)):0.0630960017f)):(((iTemp52==0)?true:false)?((0.0369039997f * fTemp77) + 0.0630960017f):0.100000001f)):(((iTemp50==0)?true:false)?((0.254812986f * fTemp53) + 0.100000001f):0.35481301f)):(((iTemp48==0)?true:false)?(0.35481301f - (0.103624001f * fTemp51)):0.251188993f)):(((iTemp46==0)?true:false)?((0.195494995f * fTemp49) + 0.251188993f):0.446684003f)):(((iTemp44==0)?true:false)?(0.446684003f - (0.195494995f * fTemp47)):0.251188993f)):(((iTemp42==0)?true:false)?(0.251188993f - (0.219566002f * fTemp45)):0.0316229984f)):(((iTemp41==0)?true:false)?((0.250214994f * fTemp43) + 0.0316229984f):0.281838f)):(((iTemp39==0)?true:false)?(0.281838f - (0.181838006f * fTemp72)):0.100000001f)):(((iTemp36==0)?true:false)?((0.401187003f * fTemp40) + 0.100000001f):0.501187027f)):(((iTemp34==0)?true:false)?(0.501187027f - (0.301661015f * fTemp37)):0.199525997f)):(((iTemp32==0)?true:false)?(0.199525997f - (0.136429995f * fTemp35)):0.0630960017f)):(((iTemp30==0)?true:false)?((0.253131986f * fTemp33) + 0.0630960017f):0.316228002f)):(((iTemp28==0)?true:false)?(0.316228002f - (0.216227993f * fTemp31)):0.100000001f)):(((iTemp26==0)?true:false)?((0.401187003f * fTemp29) + 0.100000001f):0.501187027f)):(((iTemp24==0)?true:false)?(0.501187027f - (0.401187003f * fTemp27)):0.100000001f)):(((iTemp22==0)?true:false)?((0.151188999f * fTemp25) + 0.100000001f):0.251188993f)):(((iTemp20==0)?true:false)?((0.0306490008f * fTemp23) + 0.251188993f):0.281838f)):(((iTemp17==0)?true:false)?(0.281838f - (0.123349003f * fTemp21)):0.158489004f)):(((iTemp15==0)?true:false)?((0.342698008f * fTemp18) + 0.158489004f):0.501187027f)):(((iTemp13==0)?true:false)?(0.501187027f - (0.301661015f * fTemp16)):0.199525997f)):(((iTemp11==0)?true:false)?(0.199525997f - (0.0216979999f * fTemp14)):0.177827999f)):(((iTemp7==0)?true:false)?((0.138400003f * fTemp12) + 0.177827999f):0.316228002f)):(((iTemp8==0)?true:false)?(0.316228002f - (0.216227993f * fTemp9)):0.100000001f));
			float fTemp111 = (((iSlow12==0)?true:false)?(fTemp74 * fTemp110):(fTemp70 * fTemp110));
			float fTemp112 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?4950.0f:(((iTemp46==0)?true:false)?(4950.0f - (2200.0f * fTemp49)):2750.0f)):(((iTemp44==0)?true:false)?(fTemp76 + 2750.0f):3100.0f)):(((iTemp42==0)?true:false)?((240.0f * fTemp45) + 3100.0f):3340.0f)):(((iTemp41==0)?true:false)?(3340.0f - (440.0f * fTemp43)):2900.0f)):(((iTemp39==0)?true:false)?(fTemp93 + 2900.0f):2950.0f)):(((iTemp36==0)?true:false)?((400.0f * fTemp40) + 2950.0f):3350.0f)):(((iTemp34==0)?true:false)?(3350.0f - fTemp38):3300.0f)):(((iTemp32==0)?true:false)?((290.0f * fTemp35) + 3300.0f):3590.0f)):(((iTemp30==0)?true:false)?(3590.0f - (290.0f * fTemp33)):3300.0f)):(((iTemp28==0)?true:false)?((100.0f * fTemp31) + 3300.0f):3400.0f)):(((iTemp26==0)?true:false)?((1550.0f * fTemp29) + 3400.0f):4950.0f)):4950.0f):4950.0f):4950.0f):4950.0f):(((iTemp15==0)?true:false)?(4950.0f - (1700.0f * fTemp18)):3250.0f)):(((iTemp13==0)?true:false)?((330.0f * fTemp16) + 3250.0f):3580.0f)):(((iTemp11==0)?true:false)?(3580.0f - (40.0f * fTemp14)):3540.0f)):(((iTemp7==0)?true:false)?(3540.0f - (540.0f * fTemp12)):3000.0f)):(((iTemp8==0)?true:false)?((300.0f * fTemp9) + 3000.0f):3300.0f));
			float fTemp113 = (float)java.lang.Math.tan((fConst3 * fTemp112));
			float fTemp114 = (1.0f / fTemp113);
			float fTemp115 = ((((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?(((iTemp54==0)?true:false)?(((iTemp55==0)?true:false)?140.0f:(((iTemp54==0)?true:false)?((60.0f * fTemp6) + 140.0f):200.0f)):200.0f):(((iTemp50==0)?true:false)?(200.0f - (65.0f * fTemp53)):135.0f)):(((iTemp48==0)?true:false)?((65.0f * fTemp51) + 135.0f):200.0f)):(((iTemp46==0)?true:false)?(200.0f - (70.0f * fTemp49)):130.0f)):(((iTemp44==0)?true:false)?(130.0f - fTemp63):120.0f)):120.0f):120.0f):120.0f):(((iTemp36==0)?true:false)?(fTemp62 + 120.0f):140.0f)):(((iTemp34==0)?true:false)?(140.0f - fTemp61):120.0f)):120.0f):120.0f):120.0f):(((iTemp26==0)?true:false)?(fTemp60 + 120.0f):140.0f)):(((iTemp24==0)?true:false)?((60.0f * fTemp27) + 140.0f):200.0f)):(((iTemp22==0)?true:false)?(200.0f - fTemp92):120.0f)):120.0f):(((iTemp17==0)?true:false)?((80.0f * fTemp21) + 120.0f):200.0f)):(((iTemp15==0)?true:false)?(200.0f - (60.0f * fTemp18)):140.0f)):(((iTemp13==0)?true:false)?(140.0f - fTemp59):120.0f)):120.0f):(((iTemp7==0)?true:false)?((15.0f * fTemp12) + 120.0f):135.0f)):(((iTemp8==0)?true:false)?(135.0f - (15.0f * fTemp9)):120.0f)) / fTemp112);
			float fTemp116 = (((fTemp114 + fTemp115) / fTemp113) + 1.0f);
			fRec13[0] = (fTemp5 - (((fRec13[2] * (((fTemp114 - fTemp115) / fTemp113) + 1.0f)) + (2.0f * (fRec13[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp113)))))) / fTemp116));
			float fTemp117 = (((iTemp7==0)?true:false)?(((iTemp11==0)?true:false)?(((iTemp13==0)?true:false)?(((iTemp15==0)?true:false)?(((iTemp17==0)?true:false)?(((iTemp20==0)?true:false)?(((iTemp22==0)?true:false)?(((iTemp24==0)?true:false)?(((iTemp26==0)?true:false)?(((iTemp28==0)?true:false)?(((iTemp30==0)?true:false)?(((iTemp32==0)?true:false)?(((iTemp34==0)?true:false)?(((iTemp36==0)?true:false)?(((iTemp39==0)?true:false)?(((iTemp41==0)?true:false)?(((iTemp42==0)?true:false)?(((iTemp44==0)?true:false)?(((iTemp46==0)?true:false)?(((iTemp48==0)?true:false)?(((iTemp50==0)?true:false)?(((iTemp52==0)?true:false)?0.00100000005f:(((iTemp50==0)?true:false)?((0.000777999987f * fTemp53) + 0.00100000005f):0.00177800003f)):(((iTemp48==0)?true:false)?(0.00177800003f - (0.001147f * fTemp51)):0.000630999974f)):(((iTemp46==0)?true:false)?((0.0993689969f * fTemp49) + 0.000630999974f):0.100000001f)):(((iTemp44==0)?true:false)?((0.0258930009f * fTemp47) + 0.100000001f):0.125892997f)):(((iTemp42==0)?true:false)?(0.125892997f - (0.0860819966f * fTemp45)):0.0398110002f)):(((iTemp41==0)?true:false)?(0.0398110002f - (0.0298110005f * fTemp43)):0.00999999978f)):(((iTemp39==0)?true:false)?((0.00584900007f * fTemp72) + 0.00999999978f):0.0158489998f)):(((iTemp36==0)?true:false)?(0.0158489998f - (0.00325999991f * fTemp40)):0.0125890002f)):(((iTemp34==0)?true:false)?((0.0874110013f * fTemp37) + 0.0125890002f):0.100000001f)):fTemp89):(((iTemp30==0)?true:false)?((0.00410400005f * fTemp33) + 0.0158489998f):0.0199529994f)):0.0199529994f):(((iTemp26==0)?true:false)?(0.0199529994f - (0.0167909991f * fTemp29)):0.0031620001f)):(((iTemp24==0)?true:false)?(0.0031620001f - (0.00157700002f * fTemp27)):0.00158499996f)):(((iTemp22==0)?true:false)?((0.00472499989f * fTemp25) + 0.00158499996f):0.00631000008f)):(((iTemp20==0)?true:false)?(0.00631000008f - (0.00314799999f * fTemp23)):0.0031620001f)):(((iTemp17==0)?true:false)?(0.0031620001f - (0.00216199993f * fTemp21)):0.00100000005f)):(((iTemp15==0)?true:false)?((0.0784329996f * fTemp18) + 0.00100000005f):0.0794330016f)):(((iTemp13==0)?true:false)?((0.0205669999f * fTemp16) + 0.0794330016f):0.100000001f)):(((iTemp11==0)?true:false)?(0.100000001f - (0.0683770031f * fTemp14)):0.0316229984f)):(((iTemp7==0)?true:false)?((0.0184959993f * fTemp12) + 0.0316229984f):0.0501190014f)):0.0501190014f);
			float fTemp118 = (((iSlow12==0)?true:false)?(fTemp74 * fTemp117):(fTemp70 * fTemp117));
			float fTemp119 = (((((((fRec0[2] * (0.0f - (fTemp75 / fTemp57))) + ((fRec0[0] * fTemp75) / fTemp57)) / fTemp67) + (((fRec10[2] * (0.0f - (fTemp91 / fTemp79))) + ((fTemp91 * fRec10[0]) / fTemp79)) / fTemp88)) + (((fRec11[2] * (0.0f - (fTemp102 / fTemp96))) + ((fRec11[0] * fTemp102) / fTemp96)) / fTemp101)) + (((fRec12[2] * (0.0f - (fTemp111 / fTemp106))) + ((fRec12[0] * fTemp111) / fTemp106)) / fTemp109)) + (((fRec13[2] * (0.0f - (fTemp118 / fTemp113))) + ((fRec13[0] * fTemp118) / fTemp113)) / fTemp116));
			output0[i] = fTemp119;
			output1[i] = fTemp119;
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			iRec6[1] = iRec6[0];
			fRec7[1] = fRec7[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
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

