/* ------------------------------------------------------------
name: "drums"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	int fSamplingFreq;
	float fConst0;
	float fVec0[] = new float[2];
	float fConst1;
	float fHslider0;
	float fHslider1;
	int iRec3[] = new int[2];
	float fRec2[] = new float[3];
	float fRec1[] = new float[3];
	float fButton0;
	float fVec1[] = new float[2];
	float fConst2;
	float fRec4[] = new float[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fHslider2;
	float fHslider3;
	float fConst8;
	float fRec0[] = new float[3];
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fRec5[] = new float[3];
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec6[] = new float[3];
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec7[] = new float[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec8[] = new float[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec9[] = new float[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec10[] = new float[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec11[] = new float[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec12[] = new float[3];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec13[] = new float[3];
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec14[] = new float[3];
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec15[] = new float[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec16[] = new float[3];
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec17[] = new float[3];
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec18[] = new float[3];
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec19[] = new float[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec20[] = new float[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec21[] = new float[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec22[] = new float[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec23[] = new float[3];
	
	public void metadata(Meta m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Keyboard 0 - Number of Keys':'2',  'Keyboard 1 - Number of Keys':'1',  'Keyboard 0 - Static Mode':'1',  'Keyboard 1 - Static Mode':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send X':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 0 - Piano Keyboard':'0',  'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Key 0 - Label':'High',  'Keyboard 0 - Key 1 - Label':'Mid',  'Keyboard 1 - Key 0 - Label':'Low' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "drums");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
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
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (0.00200000009f * fConst0);
		fConst3 = (0.00100000005f * fConst0);
		fConst4 = (1000.0f / fConst0);
		fConst5 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.600000024f * fConst0)));
		fConst6 = (0.0f - (2.0f * fConst5));
		fConst7 = (376.991119f / fConst0);
		fConst8 = mydsp_faustpower2_f(fConst5);
		fConst9 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.569999993f * fConst0)));
		fConst10 = (0.0f - (2.0f * fConst9));
		fConst11 = (6.28318548f / fConst0);
		fConst12 = mydsp_faustpower2_f(fConst9);
		fConst13 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.540000021f * fConst0)));
		fConst14 = (0.0f - (2.0f * fConst13));
		fConst15 = mydsp_faustpower2_f(fConst13);
		fConst16 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.50999999f * fConst0)));
		fConst17 = (0.0f - (2.0f * fConst16));
		fConst18 = mydsp_faustpower2_f(fConst16);
		fConst19 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.479999989f * fConst0)));
		fConst20 = (0.0f - (2.0f * fConst19));
		fConst21 = mydsp_faustpower2_f(fConst19);
		fConst22 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.449999988f * fConst0)));
		fConst23 = (0.0f - (2.0f * fConst22));
		fConst24 = mydsp_faustpower2_f(fConst22);
		fConst25 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.419999987f * fConst0)));
		fConst26 = (0.0f - (2.0f * fConst25));
		fConst27 = mydsp_faustpower2_f(fConst25);
		fConst28 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.389999986f * fConst0)));
		fConst29 = (0.0f - (2.0f * fConst28));
		fConst30 = mydsp_faustpower2_f(fConst28);
		fConst31 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.360000014f * fConst0)));
		fConst32 = (0.0f - (2.0f * fConst31));
		fConst33 = mydsp_faustpower2_f(fConst31);
		fConst34 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.330000013f * fConst0)));
		fConst35 = (0.0f - (2.0f * fConst34));
		fConst36 = mydsp_faustpower2_f(fConst34);
		fConst37 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.300000012f * fConst0)));
		fConst38 = (0.0f - (2.0f * fConst37));
		fConst39 = mydsp_faustpower2_f(fConst37);
		fConst40 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.270000011f * fConst0)));
		fConst41 = (0.0f - (2.0f * fConst40));
		fConst42 = mydsp_faustpower2_f(fConst40);
		fConst43 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.239999995f * fConst0)));
		fConst44 = (0.0f - (2.0f * fConst43));
		fConst45 = mydsp_faustpower2_f(fConst43);
		fConst46 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.209999993f * fConst0)));
		fConst47 = (0.0f - (2.0f * fConst46));
		fConst48 = mydsp_faustpower2_f(fConst46);
		fConst49 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.180000007f * fConst0)));
		fConst50 = (0.0f - (2.0f * fConst49));
		fConst51 = mydsp_faustpower2_f(fConst49);
		fConst52 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.150000006f * fConst0)));
		fConst53 = (0.0f - (2.0f * fConst52));
		fConst54 = mydsp_faustpower2_f(fConst52);
		fConst55 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.119999997f * fConst0)));
		fConst56 = (0.0f - (2.0f * fConst55));
		fConst57 = mydsp_faustpower2_f(fConst55);
		fConst58 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.0900000036f * fConst0)));
		fConst59 = (0.0f - (2.0f * fConst58));
		fConst60 = mydsp_faustpower2_f(fConst58);
		fConst61 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.0599999987f * fConst0)));
		fConst62 = (0.0f - (2.0f * fConst61));
		fConst63 = mydsp_faustpower2_f(fConst61);
		fConst64 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (0.0299999993f * fConst0)));
		fConst65 = (0.0f - (2.0f * fConst64));
		fConst66 = mydsp_faustpower2_f(fConst64);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)1.0f;
		fHslider1 = (float)1.0f;
		fButton0 = (float)0.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec3[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec5[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec9[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec10[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec12[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec13[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec15[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec16[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec17[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec22[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec23[l25] = 0.0f;
			
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
		ui_interface.openVerticalBox("drums");
		ui_interface.addButton("gate", new FaustVarAccess() {
				public String getId() { return "fButton0"; }
				public void set(float val) { fButton0 = val; }
				public float get() { return (float)fButton0; }
			}
			);
		ui_interface.addHorizontalSlider("key", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("keyboard", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("x", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface.addHorizontalSlider("y", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = (float)java.lang.Math.min((float)java.lang.Math.abs(((2.0f * fHslider0) + -1.0f)), (float)java.lang.Math.abs(((2.0f * fHslider1) + -1.0f)));
		float fSlow1 = (float)java.lang.Math.tan((fConst1 * ((15000.0f * fSlow0) + 500.0f)));
		float fSlow2 = (1.0f / fSlow1);
		float fSlow3 = (((fSlow2 + 1.41421354f) / fSlow1) + 1.0f);
		float fSlow4 = (2.0f / fSlow3);
		float fSlow5 = (float)java.lang.Math.tan((fConst1 * ((500.0f * fSlow0) + 40.0f)));
		float fSlow6 = (1.0f / fSlow5);
		float fSlow7 = (1.0f / (((fSlow6 + 1.41421354f) / fSlow5) + 1.0f));
		float fSlow8 = (1.0f / mydsp_faustpower2_f(fSlow5));
		float fSlow9 = (((fSlow6 + -1.41421354f) / fSlow5) + 1.0f);
		float fSlow10 = (2.0f * (1.0f - fSlow8));
		float fSlow11 = (2.0f * (0.0f - fSlow8));
		float fSlow12 = (1.0f / fSlow3);
		float fSlow13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
		float fSlow14 = (((fSlow2 + -1.41421354f) / fSlow1) + 1.0f);
		float fSlow15 = fButton0;
		int iSlow16 = ((2 * (1 - (int)fHslider2)) + (1 - (int)fHslider3));
		float fSlow17 = (fConst6 * (float)java.lang.Math.cos((fConst7 * (float)iSlow16)));
		int iSlow18 = (60 * iSlow16);
		float fSlow19 = (fConst10 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 200))));
		float fSlow20 = (fConst14 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 400))));
		float fSlow21 = (fConst17 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 600))));
		float fSlow22 = (fConst20 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 800))));
		float fSlow23 = (fConst23 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 1000))));
		float fSlow24 = (fConst26 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 1200))));
		float fSlow25 = (fConst29 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 1400))));
		float fSlow26 = (fConst32 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 1600))));
		float fSlow27 = (fConst35 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 1800))));
		float fSlow28 = (fConst38 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 2000))));
		float fSlow29 = (fConst41 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 2200))));
		float fSlow30 = (fConst44 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 2400))));
		float fSlow31 = (fConst47 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 2600))));
		float fSlow32 = (fConst50 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 2800))));
		float fSlow33 = (fConst53 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 3000))));
		float fSlow34 = (fConst56 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 3200))));
		float fSlow35 = (fConst59 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 3400))));
		float fSlow36 = (fConst62 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 3600))));
		float fSlow37 = (fConst65 * (float)java.lang.Math.cos((fConst11 * (float)(iSlow18 + 3800))));
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fConst0;
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.65661287e-10f * (float)iRec3[0]) - (fSlow7 * ((fSlow9 * fRec2[2]) + (fSlow10 * fRec2[1]))));
			fRec1[0] = ((fSlow7 * (((fSlow8 * fRec2[0]) + (fSlow11 * fRec2[1])) + (fSlow8 * fRec2[2]))) - (fSlow12 * ((fSlow13 * fRec1[1]) + (fSlow14 * fRec1[2]))));
			fVec1[0] = fSlow15;
			fRec4[0] = (((((fSlow15 - fVec1[1]) > 0.0f) > 0))?0.0f:(float)java.lang.Math.min(fConst2, ((fRec4[1] + (0.00200000009f * (fConst0 - fVec0[1]))) + 1.0f)));
			int iTemp0 = (fRec4[0] < fConst3);
			float fTemp1 = (fSlow4 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * (((iTemp0==0)?true:false)?(((fRec4[0] < 0.0f))?0.0f:(((iTemp0==0)?true:false)?(fConst4 * fRec4[0]):1.0f)):(((fRec4[0] < fConst2))?((fConst4 * (0.0f - (fRec4[0] - fConst3))) + 1.0f):0.0f))));
			fRec0[0] = (fTemp1 - ((fSlow17 * fRec0[1]) + (fConst8 * fRec0[2])));
			fRec5[0] = (fTemp1 - ((fSlow19 * fRec5[1]) + (fConst12 * fRec5[2])));
			fRec6[0] = (fTemp1 - ((fSlow20 * fRec6[1]) + (fConst15 * fRec6[2])));
			fRec7[0] = (fTemp1 - ((fSlow21 * fRec7[1]) + (fConst18 * fRec7[2])));
			fRec8[0] = (fTemp1 - ((fSlow22 * fRec8[1]) + (fConst21 * fRec8[2])));
			fRec9[0] = (fTemp1 - ((fSlow23 * fRec9[1]) + (fConst24 * fRec9[2])));
			fRec10[0] = (fTemp1 - ((fSlow24 * fRec10[1]) + (fConst27 * fRec10[2])));
			fRec11[0] = (fTemp1 - ((fSlow25 * fRec11[1]) + (fConst30 * fRec11[2])));
			fRec12[0] = (fTemp1 - ((fSlow26 * fRec12[1]) + (fConst33 * fRec12[2])));
			fRec13[0] = (fTemp1 - ((fSlow27 * fRec13[1]) + (fConst36 * fRec13[2])));
			fRec14[0] = (fTemp1 - ((fSlow28 * fRec14[1]) + (fConst39 * fRec14[2])));
			fRec15[0] = (fTemp1 - ((fSlow29 * fRec15[1]) + (fConst42 * fRec15[2])));
			fRec16[0] = (fTemp1 - ((fSlow30 * fRec16[1]) + (fConst45 * fRec16[2])));
			fRec17[0] = (fTemp1 - ((fSlow31 * fRec17[1]) + (fConst48 * fRec17[2])));
			fRec18[0] = (fTemp1 - ((fSlow32 * fRec18[1]) + (fConst51 * fRec18[2])));
			fRec19[0] = (fTemp1 - ((fSlow33 * fRec19[1]) + (fConst54 * fRec19[2])));
			fRec20[0] = (fTemp1 - ((fSlow34 * fRec20[1]) + (fConst57 * fRec20[2])));
			fRec21[0] = (fTemp1 - ((fSlow35 * fRec21[1]) + (fConst60 * fRec21[2])));
			fRec22[0] = (fTemp1 - ((fSlow36 * fRec22[1]) + (fConst63 * fRec22[2])));
			fRec23[0] = (fTemp1 - ((fSlow37 * fRec23[1]) + (fConst66 * fRec23[2])));
			float fTemp2 = (0.0500000007f * ((((((((((((((((((((fRec0[0] + (0.25f * (fRec5[0] - fRec5[2]))) + (0.111111112f * (fRec6[0] - fRec6[2]))) + (0.0625f * (fRec7[0] - fRec7[2]))) + (0.0399999991f * (fRec8[0] - fRec8[2]))) + (0.027777778f * (fRec9[0] - fRec9[2]))) + (0.0204081628f * (fRec10[0] - fRec10[2]))) + (0.015625f * (fRec11[0] - fRec11[2]))) + (0.0123456791f * (fRec12[0] - fRec12[2]))) + (0.00999999978f * (fRec13[0] - fRec13[2]))) + (0.00826446246f * (fRec14[0] - fRec14[2]))) + (0.0069444445f * (fRec15[0] - fRec15[2]))) + (0.00591715984f * (fRec16[0] - fRec16[2]))) + (0.00510204071f * (fRec17[0] - fRec17[2]))) + (0.00444444455f * (fRec18[0] - fRec18[2]))) + (0.00390625f * (fRec19[0] - fRec19[2]))) + (0.00346020772f * (fRec20[0] - fRec20[2]))) + (0.00308641978f * (fRec21[0] - fRec21[2]))) + (0.00277008303f * (fRec22[0] - fRec22[2]))) + (0.00249999994f * (fRec23[0] - fRec23[2]))) - fRec0[2]));
			output0[i] = fTemp2;
			output1[i] = fTemp2;
			fVec0[1] = fVec0[0];
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			
		}
		
	}
	
};

