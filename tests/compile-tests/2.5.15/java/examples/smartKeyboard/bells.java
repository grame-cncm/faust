/* ------------------------------------------------------------
name: "bells"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	static float ftbl0mydspSIG0[] = new float[350];
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	static float ftbl1mydspSIG1[] = new float[350];
	static float ftbl2mydspSIG2[] = new float[350];
	static float ftbl3mydspSIG3[] = new float[350];
	
	
	final class mydspSIG0 {
		
		int fmydspSIG0Wave0_idx;
		
		int getNumInputsmydspSIG0() {
			return 0;
			
		}
		int getNumOutputsmydspSIG0() {
			return 1;
			
		}
		int getInputRatemydspSIG0(int channel) {
			int rate;
			switch (channel) {
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		int getOutputRatemydspSIG0(int channel) {
			int rate;
			switch (channel) {
				case 0: {
					rate = 0;
					break;
				}
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		
		void instanceInitmydspSIG0(int samplingFreq) {
			fmydspSIG0Wave0_idx = 0;
			
		}
		void fillmydspSIG0(int count, float[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				output[i] = fmydspSIG0Wave0[fmydspSIG0Wave0_idx];
				fmydspSIG0Wave0_idx = ((1 + fmydspSIG0Wave0_idx) % 350);
				
			}
			
		}
	};

	mydspSIG0 newmydspSIG0() {return new mydspSIG0(); }
	void deletemydspSIG0(mydspSIG0 dsp) {}
	
	
	final class mydspSIG1 {
		
		int fmydspSIG1Wave0_idx;
		
		int getNumInputsmydspSIG1() {
			return 0;
			
		}
		int getNumOutputsmydspSIG1() {
			return 1;
			
		}
		int getInputRatemydspSIG1(int channel) {
			int rate;
			switch (channel) {
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		int getOutputRatemydspSIG1(int channel) {
			int rate;
			switch (channel) {
				case 0: {
					rate = 0;
					break;
				}
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		
		void instanceInitmydspSIG1(int samplingFreq) {
			fmydspSIG1Wave0_idx = 0;
			
		}
		void fillmydspSIG1(int count, float[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				output[i] = fmydspSIG1Wave0[fmydspSIG1Wave0_idx];
				fmydspSIG1Wave0_idx = ((1 + fmydspSIG1Wave0_idx) % 350);
				
			}
			
		}
	};

	mydspSIG1 newmydspSIG1() {return new mydspSIG1(); }
	void deletemydspSIG1(mydspSIG1 dsp) {}
	
	
	final class mydspSIG2 {
		
		int fmydspSIG2Wave0_idx;
		
		int getNumInputsmydspSIG2() {
			return 0;
			
		}
		int getNumOutputsmydspSIG2() {
			return 1;
			
		}
		int getInputRatemydspSIG2(int channel) {
			int rate;
			switch (channel) {
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		int getOutputRatemydspSIG2(int channel) {
			int rate;
			switch (channel) {
				case 0: {
					rate = 0;
					break;
				}
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		
		void instanceInitmydspSIG2(int samplingFreq) {
			fmydspSIG2Wave0_idx = 0;
			
		}
		void fillmydspSIG2(int count, float[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				output[i] = fmydspSIG2Wave0[fmydspSIG2Wave0_idx];
				fmydspSIG2Wave0_idx = ((1 + fmydspSIG2Wave0_idx) % 350);
				
			}
			
		}
	};

	mydspSIG2 newmydspSIG2() {return new mydspSIG2(); }
	void deletemydspSIG2(mydspSIG2 dsp) {}
	
	
	final class mydspSIG3 {
		
		int fmydspSIG3Wave0_idx;
		
		int getNumInputsmydspSIG3() {
			return 0;
			
		}
		int getNumOutputsmydspSIG3() {
			return 1;
			
		}
		int getInputRatemydspSIG3(int channel) {
			int rate;
			switch (channel) {
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		int getOutputRatemydspSIG3(int channel) {
			int rate;
			switch (channel) {
				case 0: {
					rate = 0;
					break;
				}
				default: {
					rate = -1;
					break;
				}
				
			}
			return rate;
			
		}
		
		void instanceInitmydspSIG3(int samplingFreq) {
			fmydspSIG3Wave0_idx = 0;
			
		}
		void fillmydspSIG3(int count, float[] output) {
			for (int i = 0; (i < count); i = (i + 1)) {
				output[i] = fmydspSIG3Wave0[fmydspSIG3Wave0_idx];
				fmydspSIG3Wave0_idx = ((1 + fmydspSIG3Wave0_idx) % 350);
				
			}
			
		}
	};

	mydspSIG3 newmydspSIG3() {return new mydspSIG3(); }
	void deletemydspSIG3(mydspSIG3 dsp) {}
	
	float fHslider0;
	float fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fVec0[] = new float[2];
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	int iRec3[] = new int[2];
	float fConst8;
	float fConst9;
	float fRec2[] = new float[3];
	float fConst10;
	float fConst11;
	float fConst12;
	float fRec1[] = new float[3];
	float fHslider2;
	int iVec1[] = new int[2];
	float fConst13;
	float fRec4[] = new float[2];
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec0[] = new float[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec5[] = new float[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec6[] = new float[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec7[] = new float[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec8[] = new float[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec9[] = new float[3];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec10[] = new float[3];
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec11[] = new float[3];
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec12[] = new float[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec13[] = new float[3];
	float fHslider3;
	int iVec2[] = new int[2];
	float fRec15[] = new float[2];
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec14[] = new float[3];
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec16[] = new float[3];
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec17[] = new float[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec18[] = new float[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec19[] = new float[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec20[] = new float[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec21[] = new float[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec22[] = new float[3];
	float fConst70;
	float fConst71;
	float fConst72;
	float fRec23[] = new float[3];
	float fConst73;
	float fConst74;
	float fConst75;
	float fRec24[] = new float[3];
	float fHslider4;
	int iVec3[] = new int[2];
	float fRec26[] = new float[2];
	float fConst76;
	float fConst77;
	float fConst78;
	float fRec25[] = new float[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec27[] = new float[3];
	float fConst82;
	float fConst83;
	float fConst84;
	float fRec28[] = new float[3];
	float fConst85;
	float fConst86;
	float fConst87;
	float fRec29[] = new float[3];
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec30[] = new float[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec31[] = new float[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec32[] = new float[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec33[] = new float[3];
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec34[] = new float[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec35[] = new float[3];
	float fHslider5;
	int iVec4[] = new int[2];
	float fRec37[] = new float[2];
	float fConst106;
	float fConst107;
	float fConst108;
	float fRec36[] = new float[3];
	float fConst109;
	float fConst110;
	float fConst111;
	float fRec38[] = new float[3];
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec39[] = new float[3];
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec40[] = new float[3];
	float fConst118;
	float fConst119;
	float fConst120;
	float fRec41[] = new float[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec42[] = new float[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec43[] = new float[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec44[] = new float[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec45[] = new float[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec46[] = new float[3];
	
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
		m.declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'2',   'Keyboard 1 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send X':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 0 - Key 0 - Label':'English Bell',  'Keyboard 0 - Key 1 - Label':'French Bell',  'Keyboard 1 - Key 0 - Label':'German Bell',  'Keyboard 1 - Key 1 - Label':'Russian Bell' }");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "bells");
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
		mydspSIG0 sig0 = newmydspSIG0();
		sig0.instanceInitmydspSIG0(samplingFreq);
		sig0.fillmydspSIG0(350, ftbl0mydspSIG0);
		mydspSIG1 sig1 = newmydspSIG1();
		sig1.instanceInitmydspSIG1(samplingFreq);
		sig1.fillmydspSIG1(350, ftbl1mydspSIG1);
		mydspSIG2 sig2 = newmydspSIG2();
		sig2.instanceInitmydspSIG2(samplingFreq);
		sig2.fillmydspSIG2(350, ftbl2mydspSIG2);
		mydspSIG3 sig3 = newmydspSIG3();
		sig3.instanceInitmydspSIG3(samplingFreq);
		sig3.fillmydspSIG3(350, ftbl3mydspSIG3);
		deletemydspSIG0(sig0);
		deletemydspSIG1(sig1);
		deletemydspSIG2(sig2);
		deletemydspSIG3(sig3);
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		fConst1 = (float)java.lang.Math.tan((20420.3516f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 1.41421354f) / fConst1) + 1.0f));
		fConst4 = (float)java.lang.Math.tan((31.415926f / fConst0));
		fConst5 = (1.0f / fConst4);
		fConst6 = (1.0f / (((fConst5 + 1.41421354f) / fConst4) + 1.0f));
		fConst7 = (1.0f / mydsp_faustpower2_f(fConst4));
		fConst8 = (((fConst5 + -1.41421354f) / fConst4) + 1.0f);
		fConst9 = (2.0f * (1.0f - fConst7));
		fConst10 = (2.0f * (0.0f - fConst7));
		fConst11 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst1))));
		fConst12 = (((fConst2 + -1.41421354f) / fConst1) + 1.0f);
		fConst13 = (0.00200000009f * fConst0);
		fConst14 = (0.00100000005f * fConst0);
		fConst15 = (1000.0f / fConst0);
		fConst16 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (20.3469906f * fConst0)));
		fConst17 = ((0.0f - (2.0f * fConst16)) * (float)java.lang.Math.cos((1630.04053f / fConst0)));
		fConst18 = mydsp_faustpower2_f(fConst16);
		fConst19 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (20.2682228f * fConst0)));
		fConst20 = ((0.0f - (2.0f * fConst19)) * (float)java.lang.Math.cos((1645.28345f / fConst0)));
		fConst21 = mydsp_faustpower2_f(fConst19);
		fConst22 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (13.6507998f * fConst0)));
		fConst23 = ((0.0f - (2.0f * fConst22)) * (float)java.lang.Math.cos((3099.69019f / fConst0)));
		fConst24 = mydsp_faustpower2_f(fConst22);
		fConst25 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (13.6223917f * fConst0)));
		fConst26 = ((0.0f - (2.0f * fConst25)) * (float)java.lang.Math.cos((3106.85913f / fConst0)));
		fConst27 = mydsp_faustpower2_f(fConst25);
		fConst28 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (11.0956459f * fConst0)));
		fConst29 = ((0.0f - (2.0f * fConst28)) * (float)java.lang.Math.cos((3789.06226f / fConst0)));
		fConst30 = mydsp_faustpower2_f(fConst28);
		fConst31 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (11.0589275f * fConst0)));
		fConst32 = ((0.0f - (2.0f * fConst31)) * (float)java.lang.Math.cos((3799.70605f / fConst0)));
		fConst33 = mydsp_faustpower2_f(fConst31);
		fConst34 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (8.6621294f * fConst0)));
		fConst35 = ((0.0f - (2.0f * fConst34)) * (float)java.lang.Math.cos((4552.58252f / fConst0)));
		fConst36 = mydsp_faustpower2_f(fConst34);
		fConst37 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (8.6582489f * fConst0)));
		fConst38 = ((0.0f - (2.0f * fConst37)) * (float)java.lang.Math.cos((4553.9082f / fConst0)));
		fConst39 = mydsp_faustpower2_f(fConst37);
		fConst40 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (7.56375885f * fConst0)));
		fConst41 = ((0.0f - (2.0f * fConst40)) * (float)java.lang.Math.cos((4944.77246f / fConst0)));
		fConst42 = mydsp_faustpower2_f(fConst40);
		fConst43 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (5.38026142f * fConst0)));
		fConst44 = ((0.0f - (2.0f * fConst43)) * (float)java.lang.Math.cos((5855.25635f / fConst0)));
		fConst45 = mydsp_faustpower2_f(fConst43);
		fConst46 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (17.0404034f * fConst0)));
		fConst47 = ((0.0f - (2.0f * fConst46)) * (float)java.lang.Math.cos((2758.80225f / fConst0)));
		fConst48 = mydsp_faustpower2_f(fConst46);
		fConst49 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (17.0107555f * fConst0)));
		fConst50 = ((0.0f - (2.0f * fConst49)) * (float)java.lang.Math.cos((2766.51782f / fConst0)));
		fConst51 = mydsp_faustpower2_f(fConst49);
		fConst52 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (13.3085108f * fConst0)));
		fConst53 = ((0.0f - (2.0f * fConst52)) * (float)java.lang.Math.cos((3810.4502f / fConst0)));
		fConst54 = mydsp_faustpower2_f(fConst52);
		fConst55 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (13.1997375f * fConst0)));
		fConst56 = ((0.0f - (2.0f * fConst55)) * (float)java.lang.Math.cos((3843.90186f / fConst0)));
		fConst57 = mydsp_faustpower2_f(fConst55);
		fConst58 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (11.3049049f * fConst0)));
		fConst59 = ((0.0f - (2.0f * fConst58)) * (float)java.lang.Math.cos((4458.65527f / fConst0)));
		fConst60 = mydsp_faustpower2_f(fConst58);
		fConst61 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (11.300128f * fConst0)));
		fConst62 = ((0.0f - (2.0f * fConst61)) * (float)java.lang.Math.cos((4460.28857f / fConst0)));
		fConst63 = mydsp_faustpower2_f(fConst61);
		fConst64 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (8.80774784f * fConst0)));
		fConst65 = ((0.0f - (2.0f * fConst64)) * (float)java.lang.Math.cos((5384.47607f / fConst0)));
		fConst66 = mydsp_faustpower2_f(fConst64);
		fConst67 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (8.16906738f * fConst0)));
		fConst68 = ((0.0f - (2.0f * fConst67)) * (float)java.lang.Math.cos((5648.90381f / fConst0)));
		fConst69 = mydsp_faustpower2_f(fConst67);
		fConst70 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (5.95891714f * fConst0)));
		fConst71 = ((0.0f - (2.0f * fConst70)) * (float)java.lang.Math.cos((6687.63379f / fConst0)));
		fConst72 = mydsp_faustpower2_f(fConst70);
		fConst73 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (5.95436192f * fConst0)));
		fConst74 = ((0.0f - (2.0f * fConst73)) * (float)java.lang.Math.cos((6690.02148f / fConst0)));
		fConst75 = mydsp_faustpower2_f(fConst73);
		fConst76 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (21.8895645f * fConst0)));
		fConst77 = ((0.0f - (2.0f * fConst76)) * (float)java.lang.Math.cos((1501.1095f / fConst0)));
		fConst78 = mydsp_faustpower2_f(fConst76);
		fConst79 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (21.8487759f * fConst0)));
		fConst80 = ((0.0f - (2.0f * fConst79)) * (float)java.lang.Math.cos((1509.44104f / fConst0)));
		fConst81 = mydsp_faustpower2_f(fConst79);
		fConst82 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (17.0969524f * fConst0)));
		fConst83 = ((0.0f - (2.0f * fConst82)) * (float)java.lang.Math.cos((2552.54395f / fConst0)));
		fConst84 = mydsp_faustpower2_f(fConst82);
		fConst85 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (17.0448818f * fConst0)));
		fConst86 = ((0.0f - (2.0f * fConst85)) * (float)java.lang.Math.cos((2564.88428f / fConst0)));
		fConst87 = mydsp_faustpower2_f(fConst85);
		fConst88 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (13.2791166f * fConst0)));
		fConst89 = ((0.0f - (2.0f * fConst88)) * (float)java.lang.Math.cos((3525.52661f / fConst0)));
		fConst90 = mydsp_faustpower2_f(fConst88);
		fConst91 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (13.2376995f * fConst0)));
		fConst92 = ((0.0f - (2.0f * fConst91)) * (float)java.lang.Math.cos((3536.94946f / fConst0)));
		fConst93 = mydsp_faustpower2_f(fConst91);
		fConst94 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (9.3884573f * fConst0)));
		fConst95 = ((0.0f - (2.0f * fConst94)) * (float)java.lang.Math.cos((4710.07666f / fConst0)));
		fConst96 = mydsp_faustpower2_f(fConst94);
		fConst97 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (9.38386536f * fConst0)));
		fConst98 = ((0.0f - (2.0f * fConst97)) * (float)java.lang.Math.cos((4711.63477f / fConst0)));
		fConst99 = mydsp_faustpower2_f(fConst97);
		fConst100 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (8.81131077f * fConst0)));
		fConst101 = ((0.0f - (2.0f * fConst100)) * (float)java.lang.Math.cos((4909.61182f / fConst0)));
		fConst102 = mydsp_faustpower2_f(fConst100);
		fConst103 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (8.47139359f * fConst0)));
		fConst104 = ((0.0f - (2.0f * fConst103)) * (float)java.lang.Math.cos((5030.8208f / fConst0)));
		fConst105 = mydsp_faustpower2_f(fConst103);
		fConst106 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (20.8901539f * fConst0)));
		fConst107 = ((0.0f - (2.0f * fConst106)) * (float)java.lang.Math.cos((857.598267f / fConst0)));
		fConst108 = mydsp_faustpower2_f(fConst106);
		fConst109 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (20.860672f * fConst0)));
		fConst110 = ((0.0f - (2.0f * fConst109)) * (float)java.lang.Math.cos((860.746094f / fConst0)));
		fConst111 = mydsp_faustpower2_f(fConst109);
		fConst112 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (14.4779148f * fConst0)));
		fConst113 = ((0.0f - (2.0f * fConst112)) * (float)java.lang.Math.cos((1627.08105f / fConst0)));
		fConst114 = mydsp_faustpower2_f(fConst112);
		fConst115 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (14.4106588f * fConst0)));
		fConst116 = ((0.0f - (2.0f * fConst115)) * (float)java.lang.Math.cos((1636.26086f / fConst0)));
		fConst117 = mydsp_faustpower2_f(fConst115);
		fConst118 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (11.9841108f * fConst0)));
		fConst119 = ((0.0f - (2.0f * fConst118)) * (float)java.lang.Math.cos((1988.55908f / fConst0)));
		fConst120 = mydsp_faustpower2_f(fConst118);
		fConst121 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (11.9061594f * fConst0)));
		fConst122 = ((0.0f - (2.0f * fConst121)) * (float)java.lang.Math.cos((2000.63538f / fConst0)));
		fConst123 = mydsp_faustpower2_f(fConst121);
		fConst124 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (9.10661697f * fConst0)));
		fConst125 = ((0.0f - (2.0f * fConst124)) * (float)java.lang.Math.cos((2474.64502f / fConst0)));
		fConst126 = mydsp_faustpower2_f(fConst124);
		fConst127 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (9.10333347f * fConst0)));
		fConst128 = ((0.0f - (2.0f * fConst127)) * (float)java.lang.Math.cos((2475.25464f / fConst0)));
		fConst129 = mydsp_faustpower2_f(fConst127);
		fConst130 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (7.19911861f * fConst0)));
		fConst131 = ((0.0f - (2.0f * fConst130)) * (float)java.lang.Math.cos((2856.81982f / fConst0)));
		fConst132 = mydsp_faustpower2_f(fConst130);
		fConst133 = (float)java.lang.Math.pow(0.00100000005f, (1.0f / (6.83458185f * fConst0)));
		fConst134 = ((0.0f - (2.0f * fConst133)) * (float)java.lang.Math.cos((2937.34521f / fConst0)));
		fConst135 = mydsp_faustpower2_f(fConst133);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)1.0f;
		fHslider1 = (float)1.0f;
		fHslider2 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)0.0f;
		
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
			iVec1[l4] = 0;
			
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
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			iVec2[l16] = 0;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec15[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec14[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec16[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec17[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec18[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec19[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec20[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec21[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec22[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec23[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec24[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			iVec3[l28] = 0;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec26[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec25[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec27[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec28[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec29[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec30[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec31[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec32[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec33[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec34[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec35[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			iVec4[l40] = 0;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec37[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec36[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec38[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec39[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec40[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec41[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec42[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec43[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec44[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec45[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec46[l51] = 0.0f;
			
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
		ui_interface.openVerticalBox("bells");
		ui_interface.addHorizontalSlider("kb0k0status", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface.addHorizontalSlider("kb0k1status", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
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
		int iSlow0 = (10 * (int)(6.0f * (float)java.lang.Math.min((float)java.lang.Math.abs(((2.0f * fHslider0) + -1.0f)), (float)java.lang.Math.abs(((2.0f * fHslider1) + -1.0f)))));
		int iSlow1 = (int)(float)java.lang.Math.min(1.0f, fHslider2);
		int iSlow2 = (iSlow0 + 1);
		int iSlow3 = (iSlow0 + 2);
		int iSlow4 = (iSlow0 + 3);
		int iSlow5 = (iSlow0 + 4);
		int iSlow6 = (iSlow0 + 5);
		int iSlow7 = (iSlow0 + 6);
		int iSlow8 = (iSlow0 + 7);
		int iSlow9 = (iSlow0 + 8);
		int iSlow10 = (iSlow0 + 9);
		int iSlow11 = (int)(float)java.lang.Math.min(1.0f, fHslider3);
		int iSlow12 = (int)(float)java.lang.Math.min(1.0f, fHslider4);
		int iSlow13 = (int)(float)java.lang.Math.min(1.0f, fHslider5);
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fConst0;
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.65661287e-10f * (float)iRec3[0]) - (fConst6 * ((fConst8 * fRec2[2]) + (fConst9 * fRec2[1]))));
			fRec1[0] = ((fConst6 * (((fConst7 * fRec2[0]) + (fConst10 * fRec2[1])) + (fConst7 * fRec2[2]))) - (fConst3 * ((fConst11 * fRec1[1]) + (fConst12 * fRec1[2]))));
			float fTemp0 = (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])));
			iVec1[0] = iSlow1;
			float fTemp1 = (0.00200000009f * (fConst0 - fVec0[1]));
			fRec4[0] = (((((iSlow1 - iVec1[1]) > 0) > 0))?0.0f:(float)java.lang.Math.min(fConst13, ((fRec4[1] + fTemp1) + 1.0f)));
			int iTemp2 = (fRec4[0] < fConst14);
			float fTemp3 = (fConst3 * (fTemp0 * (((iTemp2==0)?true:false)?(((fRec4[0] < 0.0f))?0.0f:(((iTemp2==0)?true:false)?(fConst15 * fRec4[0]):1.0f)):(((fRec4[0] < fConst13))?((fConst15 * (0.0f - (fRec4[0] - fConst14))) + 1.0f):0.0f))));
			fRec0[0] = (fTemp3 - ((fConst17 * fRec0[1]) + (fConst18 * fRec0[2])));
			fRec5[0] = (fTemp3 - ((fConst20 * fRec5[1]) + (fConst21 * fRec5[2])));
			fRec6[0] = (fTemp3 - ((fConst23 * fRec6[1]) + (fConst24 * fRec6[2])));
			fRec7[0] = (fTemp3 - ((fConst26 * fRec7[1]) + (fConst27 * fRec7[2])));
			fRec8[0] = (fTemp3 - ((fConst29 * fRec8[1]) + (fConst30 * fRec8[2])));
			fRec9[0] = (fTemp3 - ((fConst32 * fRec9[1]) + (fConst33 * fRec9[2])));
			fRec10[0] = (fTemp3 - ((fConst35 * fRec10[1]) + (fConst36 * fRec10[2])));
			fRec11[0] = (fTemp3 - ((fConst38 * fRec11[1]) + (fConst39 * fRec11[2])));
			fRec12[0] = (fTemp3 - ((fConst41 * fRec12[1]) + (fConst42 * fRec12[2])));
			fRec13[0] = (fTemp3 - ((fConst44 * fRec13[1]) + (fConst45 * fRec13[2])));
			iVec2[0] = iSlow11;
			fRec15[0] = (((((iSlow11 - iVec2[1]) > 0) > 0))?0.0f:(float)java.lang.Math.min(fConst13, ((fTemp1 + fRec15[1]) + 1.0f)));
			int iTemp4 = (fRec15[0] < fConst14);
			float fTemp5 = (fConst3 * (fTemp0 * (((iTemp4==0)?true:false)?(((fRec15[0] < 0.0f))?0.0f:(((iTemp4==0)?true:false)?(fConst15 * fRec15[0]):1.0f)):(((fRec15[0] < fConst13))?((fConst15 * (0.0f - (fRec15[0] - fConst14))) + 1.0f):0.0f))));
			fRec14[0] = (fTemp5 - ((fConst47 * fRec14[1]) + (fConst48 * fRec14[2])));
			fRec16[0] = (fTemp5 - ((fConst50 * fRec16[1]) + (fConst51 * fRec16[2])));
			fRec17[0] = (fTemp5 - ((fConst53 * fRec17[1]) + (fConst54 * fRec17[2])));
			fRec18[0] = (fTemp5 - ((fConst56 * fRec18[1]) + (fConst57 * fRec18[2])));
			fRec19[0] = (fTemp5 - ((fConst59 * fRec19[1]) + (fConst60 * fRec19[2])));
			fRec20[0] = (fTemp5 - ((fConst62 * fRec20[1]) + (fConst63 * fRec20[2])));
			fRec21[0] = (fTemp5 - ((fConst65 * fRec21[1]) + (fConst66 * fRec21[2])));
			fRec22[0] = (fTemp5 - ((fConst68 * fRec22[1]) + (fConst69 * fRec22[2])));
			fRec23[0] = (fTemp5 - ((fConst71 * fRec23[1]) + (fConst72 * fRec23[2])));
			fRec24[0] = (fTemp5 - ((fConst74 * fRec24[1]) + (fConst75 * fRec24[2])));
			iVec3[0] = iSlow12;
			fRec26[0] = (((((iSlow12 - iVec3[1]) > 0) > 0))?0.0f:(float)java.lang.Math.min(fConst13, ((fTemp1 + fRec26[1]) + 1.0f)));
			int iTemp6 = (fRec26[0] < fConst14);
			float fTemp7 = (fConst3 * (fTemp0 * (((iTemp6==0)?true:false)?(((fRec26[0] < 0.0f))?0.0f:(((iTemp6==0)?true:false)?(fConst15 * fRec26[0]):1.0f)):(((fRec26[0] < fConst13))?((fConst15 * (0.0f - (fRec26[0] - fConst14))) + 1.0f):0.0f))));
			fRec25[0] = (fTemp7 - ((fConst77 * fRec25[1]) + (fConst78 * fRec25[2])));
			fRec27[0] = (fTemp7 - ((fConst80 * fRec27[1]) + (fConst81 * fRec27[2])));
			fRec28[0] = (fTemp7 - ((fConst83 * fRec28[1]) + (fConst84 * fRec28[2])));
			fRec29[0] = (fTemp7 - ((fConst86 * fRec29[1]) + (fConst87 * fRec29[2])));
			fRec30[0] = (fTemp7 - ((fConst89 * fRec30[1]) + (fConst90 * fRec30[2])));
			fRec31[0] = (fTemp7 - ((fConst92 * fRec31[1]) + (fConst93 * fRec31[2])));
			fRec32[0] = (fTemp7 - ((fConst95 * fRec32[1]) + (fConst96 * fRec32[2])));
			fRec33[0] = (fTemp7 - ((fConst98 * fRec33[1]) + (fConst99 * fRec33[2])));
			fRec34[0] = (fTemp7 - ((fConst101 * fRec34[1]) + (fConst102 * fRec34[2])));
			fRec35[0] = (fTemp7 - ((fConst104 * fRec35[1]) + (fConst105 * fRec35[2])));
			iVec4[0] = iSlow13;
			fRec37[0] = (((((iSlow13 - iVec4[1]) > 0) > 0))?0.0f:(float)java.lang.Math.min(fConst13, ((fTemp1 + fRec37[1]) + 1.0f)));
			int iTemp8 = (fRec37[0] < fConst14);
			float fTemp9 = (fConst3 * (fTemp0 * (((iTemp8==0)?true:false)?(((fRec37[0] < 0.0f))?0.0f:(((iTemp8==0)?true:false)?(fConst15 * fRec37[0]):1.0f)):(((fRec37[0] < fConst13))?((fConst15 * (0.0f - (fRec37[0] - fConst14))) + 1.0f):0.0f))));
			fRec36[0] = (fTemp9 - ((fConst107 * fRec36[1]) + (fConst108 * fRec36[2])));
			fRec38[0] = (fTemp9 - ((fConst110 * fRec38[1]) + (fConst111 * fRec38[2])));
			fRec39[0] = (fTemp9 - ((fConst113 * fRec39[1]) + (fConst114 * fRec39[2])));
			fRec40[0] = (fTemp9 - ((fConst116 * fRec40[1]) + (fConst117 * fRec40[2])));
			fRec41[0] = (fTemp9 - ((fConst119 * fRec41[1]) + (fConst120 * fRec41[2])));
			fRec42[0] = (fTemp9 - ((fConst122 * fRec42[1]) + (fConst123 * fRec42[2])));
			fRec43[0] = (fTemp9 - ((fConst125 * fRec43[1]) + (fConst126 * fRec43[2])));
			fRec44[0] = (fTemp9 - ((fConst128 * fRec44[1]) + (fConst129 * fRec44[2])));
			fRec45[0] = (fTemp9 - ((fConst131 * fRec45[1]) + (fConst132 * fRec45[2])));
			fRec46[0] = (fTemp9 - ((fConst134 * fRec46[1]) + (fConst135 * fRec46[2])));
			float fTemp10 = (0.0199999996f * (((((((((((((ftbl0mydspSIG0[iSlow0] * (fRec0[0] - fRec0[2])) + (ftbl0mydspSIG0[iSlow2] * (fRec5[0] - fRec5[2]))) + (ftbl0mydspSIG0[iSlow3] * (fRec6[0] - fRec6[2]))) + (ftbl0mydspSIG0[iSlow4] * (fRec7[0] - fRec7[2]))) + (ftbl0mydspSIG0[iSlow5] * (fRec8[0] - fRec8[2]))) + (ftbl0mydspSIG0[iSlow6] * (fRec9[0] - fRec9[2]))) + (ftbl0mydspSIG0[iSlow7] * (fRec10[0] - fRec10[2]))) + (ftbl0mydspSIG0[iSlow8] * (fRec11[0] - fRec11[2]))) + (ftbl0mydspSIG0[iSlow9] * (fRec12[0] - fRec12[2]))) + (ftbl0mydspSIG0[iSlow10] * (fRec13[0] - fRec13[2]))) + ((((((((((ftbl1mydspSIG1[iSlow0] * (fRec14[0] - fRec14[2])) + (ftbl1mydspSIG1[iSlow2] * (fRec16[0] - fRec16[2]))) + (ftbl1mydspSIG1[iSlow3] * (fRec17[0] - fRec17[2]))) + (ftbl1mydspSIG1[iSlow4] * (fRec18[0] - fRec18[2]))) + (ftbl1mydspSIG1[iSlow5] * (fRec19[0] - fRec19[2]))) + (ftbl1mydspSIG1[iSlow6] * (fRec20[0] - fRec20[2]))) + (ftbl1mydspSIG1[iSlow7] * (fRec21[0] - fRec21[2]))) + (ftbl1mydspSIG1[iSlow8] * (fRec22[0] - fRec22[2]))) + (ftbl1mydspSIG1[iSlow9] * (fRec23[0] - fRec23[2]))) + (ftbl1mydspSIG1[iSlow10] * (fRec24[0] - fRec24[2])))) + ((((((((((ftbl2mydspSIG2[iSlow0] * (fRec25[0] - fRec25[2])) + (ftbl2mydspSIG2[iSlow2] * (fRec27[0] - fRec27[2]))) + (ftbl2mydspSIG2[iSlow3] * (fRec28[0] - fRec28[2]))) + (ftbl2mydspSIG2[iSlow4] * (fRec29[0] - fRec29[2]))) + (ftbl2mydspSIG2[iSlow5] * (fRec30[0] - fRec30[2]))) + (ftbl2mydspSIG2[iSlow6] * (fRec31[0] - fRec31[2]))) + (ftbl2mydspSIG2[iSlow7] * (fRec32[0] - fRec32[2]))) + (ftbl2mydspSIG2[iSlow8] * (fRec33[0] - fRec33[2]))) + (ftbl2mydspSIG2[iSlow9] * (fRec34[0] - fRec34[2]))) + (ftbl2mydspSIG2[iSlow10] * (fRec35[0] - fRec35[2])))) + ((((((((((ftbl3mydspSIG3[iSlow0] * (fRec36[0] - fRec36[2])) + (ftbl3mydspSIG3[iSlow2] * (fRec38[0] - fRec38[2]))) + (ftbl3mydspSIG3[iSlow3] * (fRec39[0] - fRec39[2]))) + (ftbl3mydspSIG3[iSlow4] * (fRec40[0] - fRec40[2]))) + (ftbl3mydspSIG3[iSlow5] * (fRec41[0] - fRec41[2]))) + (ftbl3mydspSIG3[iSlow6] * (fRec42[0] - fRec42[2]))) + (ftbl3mydspSIG3[iSlow7] * (fRec43[0] - fRec43[2]))) + (ftbl3mydspSIG3[iSlow8] * (fRec44[0] - fRec44[2]))) + (ftbl3mydspSIG3[iSlow9] * (fRec45[0] - fRec45[2]))) + (ftbl3mydspSIG3[iSlow10] * (fRec46[0] - fRec46[2])))));
			output0[i] = fTemp10;
			output1[i] = fTemp10;
			fVec0[1] = fVec0[0];
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			iVec1[1] = iVec1[0];
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
			iVec2[1] = iVec2[0];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
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
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			iVec3[1] = iVec3[0];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			iVec4[1] = iVec4[0];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			
		}
		
	}
	
};

