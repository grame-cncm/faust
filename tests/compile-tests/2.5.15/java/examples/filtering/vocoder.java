/* ------------------------------------------------------------
author: "RM"
name: "Vocoder"
version: "0.0"
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
	float fConst2;
	float fHslider0;
	float fVslider0;
	float fRec1[] = new float[2];
	float fConst3;
	float fHslider1;
	float fVec0[] = new float[2];
	float fRec2[] = new float[2];
	float fConst4;
	float fRec0[] = new float[3];
	float fRec5[] = new float[3];
	float fConst5;
	float fConst6;
	float fHslider2;
	float fHslider3;
	float fRec4[] = new float[2];
	float fRec3[] = new float[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec6[] = new float[3];
	float fRec9[] = new float[3];
	float fConst10;
	float fRec8[] = new float[2];
	float fRec7[] = new float[2];
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec10[] = new float[3];
	float fRec13[] = new float[3];
	float fConst14;
	float fRec12[] = new float[2];
	float fRec11[] = new float[2];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec14[] = new float[3];
	float fRec17[] = new float[3];
	float fConst18;
	float fRec16[] = new float[2];
	float fRec15[] = new float[2];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec18[] = new float[3];
	float fRec21[] = new float[3];
	float fConst22;
	float fRec20[] = new float[2];
	float fRec19[] = new float[2];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec22[] = new float[3];
	float fRec25[] = new float[3];
	float fConst26;
	float fRec24[] = new float[2];
	float fRec23[] = new float[2];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec26[] = new float[3];
	float fRec29[] = new float[3];
	float fConst30;
	float fRec28[] = new float[2];
	float fRec27[] = new float[2];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec30[] = new float[3];
	float fRec33[] = new float[3];
	float fConst34;
	float fRec32[] = new float[2];
	float fRec31[] = new float[2];
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec34[] = new float[3];
	float fRec37[] = new float[3];
	float fConst38;
	float fRec36[] = new float[2];
	float fRec35[] = new float[2];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec38[] = new float[3];
	float fRec41[] = new float[3];
	float fConst42;
	float fRec40[] = new float[2];
	float fRec39[] = new float[2];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec42[] = new float[3];
	float fRec45[] = new float[3];
	float fConst46;
	float fRec44[] = new float[2];
	float fRec43[] = new float[2];
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec46[] = new float[3];
	float fRec49[] = new float[3];
	float fConst50;
	float fRec48[] = new float[2];
	float fRec47[] = new float[2];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec50[] = new float[3];
	float fRec53[] = new float[3];
	float fConst54;
	float fRec52[] = new float[2];
	float fRec51[] = new float[2];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec54[] = new float[3];
	float fRec57[] = new float[3];
	float fConst58;
	float fRec56[] = new float[2];
	float fRec55[] = new float[2];
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec58[] = new float[3];
	float fRec61[] = new float[3];
	float fConst62;
	float fRec60[] = new float[2];
	float fRec59[] = new float[2];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec62[] = new float[3];
	float fRec65[] = new float[3];
	float fConst66;
	float fRec64[] = new float[2];
	float fRec63[] = new float[2];
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec66[] = new float[3];
	float fRec69[] = new float[3];
	float fConst70;
	float fRec68[] = new float[2];
	float fRec67[] = new float[2];
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec70[] = new float[3];
	float fRec73[] = new float[3];
	float fConst74;
	float fRec72[] = new float[2];
	float fRec71[] = new float[2];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec74[] = new float[3];
	float fRec77[] = new float[3];
	float fConst78;
	float fRec76[] = new float[2];
	float fRec75[] = new float[2];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec78[] = new float[3];
	float fRec81[] = new float[3];
	float fConst82;
	float fRec80[] = new float[2];
	float fRec79[] = new float[2];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec82[] = new float[3];
	float fRec85[] = new float[3];
	float fConst86;
	float fRec84[] = new float[2];
	float fRec83[] = new float[2];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec86[] = new float[3];
	float fRec89[] = new float[3];
	float fConst90;
	float fRec88[] = new float[2];
	float fRec87[] = new float[2];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec90[] = new float[3];
	float fRec93[] = new float[3];
	float fConst94;
	float fRec92[] = new float[2];
	float fRec91[] = new float[2];
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec94[] = new float[3];
	float fRec97[] = new float[3];
	float fConst98;
	float fRec96[] = new float[2];
	float fRec95[] = new float[2];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec98[] = new float[3];
	float fRec101[] = new float[3];
	float fConst102;
	float fRec100[] = new float[2];
	float fRec99[] = new float[2];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec102[] = new float[3];
	float fRec105[] = new float[3];
	float fConst106;
	float fRec104[] = new float[2];
	float fRec103[] = new float[2];
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec106[] = new float[3];
	float fRec109[] = new float[3];
	float fConst110;
	float fRec108[] = new float[2];
	float fRec107[] = new float[2];
	float fConst111;
	float fConst112;
	float fConst113;
	float fRec110[] = new float[3];
	float fRec113[] = new float[3];
	float fConst114;
	float fRec112[] = new float[2];
	float fRec111[] = new float[2];
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec114[] = new float[3];
	float fRec117[] = new float[3];
	float fConst118;
	float fRec116[] = new float[2];
	float fRec115[] = new float[2];
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec118[] = new float[3];
	float fRec121[] = new float[3];
	float fConst122;
	float fRec120[] = new float[2];
	float fRec119[] = new float[2];
	float fConst123;
	float fConst124;
	float fConst125;
	float fRec122[] = new float[3];
	float fRec125[] = new float[3];
	float fConst126;
	float fRec124[] = new float[2];
	float fRec123[] = new float[2];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec126[] = new float[3];
	float fRec129[] = new float[3];
	float fConst130;
	float fRec128[] = new float[2];
	float fRec127[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Use example of the vocoder function where an impulse train is used as excitation.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocoder");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m.declare("vaeffects.lib/version", "0.0");
		m.declare("version", "0.0");
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
		fConst1 = (float)java.lang.Math.tan((95.4453049f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / fConst0);
		fConst4 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst1))));
		fConst5 = (0.0f - fConst2);
		fConst6 = (1000.0f / fConst0);
		fConst7 = (float)java.lang.Math.tan((115.989655f / fConst0));
		fConst8 = (1.0f / fConst7);
		fConst9 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst7))));
		fConst10 = (0.0f - fConst8);
		fConst11 = (float)java.lang.Math.tan((140.956116f / fConst0));
		fConst12 = (1.0f / fConst11);
		fConst13 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst11))));
		fConst14 = (0.0f - fConst12);
		fConst15 = (float)java.lang.Math.tan((171.296555f / fConst0));
		fConst16 = (1.0f / fConst15);
		fConst17 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst15))));
		fConst18 = (0.0f - fConst16);
		fConst19 = (float)java.lang.Math.tan((208.167679f / fConst0));
		fConst20 = (1.0f / fConst19);
		fConst21 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst19))));
		fConst22 = (0.0f - fConst20);
		fConst23 = (float)java.lang.Math.tan((252.975235f / fConst0));
		fConst24 = (1.0f / fConst23);
		fConst25 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst23))));
		fConst26 = (0.0f - fConst24);
		fConst27 = (float)java.lang.Math.tan((307.42749f / fConst0));
		fConst28 = (1.0f / fConst27);
		fConst29 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst27))));
		fConst30 = (0.0f - fConst28);
		fConst31 = (float)java.lang.Math.tan((373.600433f / fConst0));
		fConst32 = (1.0f / fConst31);
		fConst33 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst31))));
		fConst34 = (0.0f - fConst32);
		fConst35 = (float)java.lang.Math.tan((454.016937f / fConst0));
		fConst36 = (1.0f / fConst35);
		fConst37 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst35))));
		fConst38 = (0.0f - fConst36);
		fConst39 = (float)java.lang.Math.tan((551.742859f / fConst0));
		fConst40 = (1.0f / fConst39);
		fConst41 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst39))));
		fConst42 = (0.0f - fConst40);
		fConst43 = (float)java.lang.Math.tan((670.504089f / fConst0));
		fConst44 = (1.0f / fConst43);
		fConst45 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst43))));
		fConst46 = (0.0f - fConst44);
		fConst47 = (float)java.lang.Math.tan((814.828308f / fConst0));
		fConst48 = (1.0f / fConst47);
		fConst49 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst47))));
		fConst50 = (0.0f - fConst48);
		fConst51 = (float)java.lang.Math.tan((990.217957f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst51))));
		fConst54 = (0.0f - fConst52);
		fConst55 = (float)java.lang.Math.tan((1203.35974f / fConst0));
		fConst56 = (1.0f / fConst55);
		fConst57 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst55))));
		fConst58 = (0.0f - fConst56);
		fConst59 = (float)java.lang.Math.tan((1462.37976f / fConst0));
		fConst60 = (1.0f / fConst59);
		fConst61 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst59))));
		fConst62 = (0.0f - fConst60);
		fConst63 = (float)java.lang.Math.tan((1777.1532f / fConst0));
		fConst64 = (1.0f / fConst63);
		fConst65 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst63))));
		fConst66 = (0.0f - fConst64);
		fConst67 = (float)java.lang.Math.tan((2159.68066f / fConst0));
		fConst68 = (1.0f / fConst67);
		fConst69 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst67))));
		fConst70 = (0.0f - fConst68);
		fConst71 = (float)java.lang.Math.tan((2624.54639f / fConst0));
		fConst72 = (1.0f / fConst71);
		fConst73 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst71))));
		fConst74 = (0.0f - fConst72);
		fConst75 = (float)java.lang.Math.tan((3189.4729f / fConst0));
		fConst76 = (1.0f / fConst75);
		fConst77 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst75))));
		fConst78 = (0.0f - fConst76);
		fConst79 = (float)java.lang.Math.tan((3875.99854f / fConst0));
		fConst80 = (1.0f / fConst79);
		fConst81 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst79))));
		fConst82 = (0.0f - fConst80);
		fConst83 = (float)java.lang.Math.tan((4710.29688f / fConst0));
		fConst84 = (1.0f / fConst83);
		fConst85 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst83))));
		fConst86 = (0.0f - fConst84);
		fConst87 = (float)java.lang.Math.tan((5724.17578f / fConst0));
		fConst88 = (1.0f / fConst87);
		fConst89 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst87))));
		fConst90 = (0.0f - fConst88);
		fConst91 = (float)java.lang.Math.tan((6956.28955f / fConst0));
		fConst92 = (1.0f / fConst91);
		fConst93 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst91))));
		fConst94 = (0.0f - fConst92);
		fConst95 = (float)java.lang.Math.tan((8453.61328f / fConst0));
		fConst96 = (1.0f / fConst95);
		fConst97 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst95))));
		fConst98 = (0.0f - fConst96);
		fConst99 = (float)java.lang.Math.tan((10273.2305f / fConst0));
		fConst100 = (1.0f / fConst99);
		fConst101 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst99))));
		fConst102 = (0.0f - fConst100);
		fConst103 = (float)java.lang.Math.tan((12484.5166f / fConst0));
		fConst104 = (1.0f / fConst103);
		fConst105 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst103))));
		fConst106 = (0.0f - fConst104);
		fConst107 = (float)java.lang.Math.tan((15171.7754f / fConst0));
		fConst108 = (1.0f / fConst107);
		fConst109 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst107))));
		fConst110 = (0.0f - fConst108);
		fConst111 = (float)java.lang.Math.tan((18437.4609f / fConst0));
		fConst112 = (1.0f / fConst111);
		fConst113 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst111))));
		fConst114 = (0.0f - fConst112);
		fConst115 = (float)java.lang.Math.tan((22406.0742f / fConst0));
		fConst116 = (1.0f / fConst115);
		fConst117 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst115))));
		fConst118 = (0.0f - fConst116);
		fConst119 = (float)java.lang.Math.tan((27228.9238f / fConst0));
		fConst120 = (1.0f / fConst119);
		fConst121 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst119))));
		fConst122 = (0.0f - fConst120);
		fConst123 = (float)java.lang.Math.tan((33089.8789f / fConst0));
		fConst124 = (1.0f / fConst123);
		fConst125 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst123))));
		fConst126 = (0.0f - fConst124);
		fConst127 = (float)java.lang.Math.tan((40212.3867f / fConst0));
		fConst128 = (1.0f / fConst127);
		fConst129 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst127))));
		fConst130 = (0.0f - fConst128);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)0.5f;
		fVslider0 = (float)0.5f;
		fHslider1 = (float)330.0f;
		fHslider2 = (float)5.0f;
		fHslider3 = (float)5.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec6[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec9[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec8[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec7[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec10[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec13[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec11[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec14[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec17[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec16[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec15[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec18[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec21[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec20[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec19[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec22[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec25[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec24[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec23[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec26[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec29[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec28[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec27[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec30[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec33[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec32[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec31[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec34[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec37[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec36[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec35[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec38[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec41[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec40[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec39[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec42[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec45[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec44[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec43[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec46[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec49[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec48[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec47[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec50[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec53[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec52[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec51[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec54[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec57[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec56[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec55[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec58[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec61[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec60[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec59[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec62[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec65[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec64[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec63[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec66[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec69[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec68[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec67[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec70[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec73[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec72[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec71[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec74[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec77[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec76[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec75[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec78[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec81[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec80[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fRec79[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec82[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec85[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec84[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec83[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec86[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec89[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fRec88[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec87[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec90[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec93[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec92[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec91[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec94[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec97[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec96[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec95[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec98[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec101[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec100[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec99[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec102[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec105[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec104[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec103[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec106[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec109[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			fRec108[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fRec107[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec110[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec113[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec112[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec111[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec114[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec117[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec116[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fRec115[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec118[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec121[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fRec120[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec119[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec122[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec125[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec124[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec123[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec126[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec129[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec128[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec127[l130] = 0.0f;
			
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
		ui_interface.openHorizontalBox("My Vocoder");
		ui_interface.openVerticalBox("Excitation");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("Freq", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 330.0f, 50.0f, 2000.0f, 0.100000001f);
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.addVerticalSlider("Gain", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Vocoder");
		ui_interface.declare("fHslider2", "0", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "Attack time in seconds");
		ui_interface.addHorizontalSlider("Attack", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 5.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Release time in seconds");
		ui_interface.addHorizontalSlider("Release", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 5.0f, 0.100000001f, 100.0f, 0.100000001f);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "Coefficient to adjust the   bandwidth of each band");
		ui_interface.addHorizontalSlider("BW", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 0.5f, 0.100000001f, 2.0f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (0.177122265f * fSlow0);
		float fSlow2 = (1.0f / ((fConst2 * (fConst2 + fSlow1)) + 1.0f));
		float fSlow3 = (0.00100000005f * fVslider0);
		float fSlow4 = fHslider1;
		float fSlow5 = ((fConst2 * (fConst2 - fSlow1)) + 1.0f);
		float fSlow6 = (float)java.lang.Math.exp((0.0f - (fConst6 / fHslider2)));
		float fSlow7 = (float)java.lang.Math.exp((0.0f - (fConst6 / fHslider3)));
		float fSlow8 = (0.177122265f * fSlow0);
		float fSlow9 = (1.0f / ((fConst8 * (fConst8 + fSlow8)) + 1.0f));
		float fSlow10 = ((fConst8 * (fConst8 - fSlow8)) + 1.0f);
		float fSlow11 = (1.0f / ((fConst12 * (fConst12 + fSlow1)) + 1.0f));
		float fSlow12 = ((fConst12 * (fConst12 - fSlow1)) + 1.0f);
		float fSlow13 = (0.177122265f * fSlow0);
		float fSlow14 = (1.0f / ((fConst16 * (fConst16 + fSlow13)) + 1.0f));
		float fSlow15 = ((fConst16 * (fConst16 - fSlow13)) + 1.0f);
		float fSlow16 = (0.177122265f * fSlow0);
		float fSlow17 = (1.0f / ((fConst20 * (fConst20 + fSlow16)) + 1.0f));
		float fSlow18 = ((fConst20 * (fConst20 - fSlow16)) + 1.0f);
		float fSlow19 = (0.177122265f * fSlow0);
		float fSlow20 = (1.0f / ((fConst24 * (fConst24 + fSlow19)) + 1.0f));
		float fSlow21 = ((fConst24 * (fConst24 - fSlow19)) + 1.0f);
		float fSlow22 = (0.177122265f * fSlow0);
		float fSlow23 = (1.0f / ((fConst28 * (fConst28 + fSlow22)) + 1.0f));
		float fSlow24 = ((fConst28 * (fConst28 - fSlow22)) + 1.0f);
		float fSlow25 = (1.0f / ((fConst32 * (fConst32 + fSlow1)) + 1.0f));
		float fSlow26 = ((fConst32 * (fConst32 - fSlow1)) + 1.0f);
		float fSlow27 = (1.0f / ((fConst36 * (fConst36 + fSlow16)) + 1.0f));
		float fSlow28 = ((fConst36 * (fConst36 - fSlow16)) + 1.0f);
		float fSlow29 = (1.0f / ((fConst40 * (fConst40 + fSlow8)) + 1.0f));
		float fSlow30 = ((fConst40 * (fConst40 - fSlow8)) + 1.0f);
		float fSlow31 = (0.177122265f * fSlow0);
		float fSlow32 = (1.0f / ((fConst44 * (fConst44 + fSlow31)) + 1.0f));
		float fSlow33 = ((fConst44 * (fConst44 - fSlow31)) + 1.0f);
		float fSlow34 = (0.177122265f * fSlow0);
		float fSlow35 = (1.0f / ((fConst48 * (fConst48 + fSlow34)) + 1.0f));
		float fSlow36 = ((fConst48 * (fConst48 - fSlow34)) + 1.0f);
		float fSlow37 = (1.0f / ((fConst52 * (fConst52 + fSlow31)) + 1.0f));
		float fSlow38 = ((fConst52 * (fConst52 - fSlow31)) + 1.0f);
		float fSlow39 = (0.177122265f * fSlow0);
		float fSlow40 = (1.0f / ((fConst56 * (fConst56 + fSlow39)) + 1.0f));
		float fSlow41 = ((fConst56 * (fConst56 - fSlow39)) + 1.0f);
		float fSlow42 = (1.0f / ((fConst60 * (fConst60 + fSlow13)) + 1.0f));
		float fSlow43 = ((fConst60 * (fConst60 - fSlow13)) + 1.0f);
		float fSlow44 = (1.0f / ((fConst64 * (fConst64 + fSlow13)) + 1.0f));
		float fSlow45 = ((fConst64 * (fConst64 - fSlow13)) + 1.0f);
		float fSlow46 = (1.0f / ((fConst68 * (fConst68 + fSlow8)) + 1.0f));
		float fSlow47 = ((fConst68 * (fConst68 - fSlow8)) + 1.0f);
		float fSlow48 = (0.177122265f * fSlow0);
		float fSlow49 = (1.0f / ((fConst72 * (fConst72 + fSlow48)) + 1.0f));
		float fSlow50 = ((fConst72 * (fConst72 - fSlow48)) + 1.0f);
		float fSlow51 = (1.0f / ((fConst76 * (fConst76 + fSlow16)) + 1.0f));
		float fSlow52 = ((fConst76 * (fConst76 - fSlow16)) + 1.0f);
		float fSlow53 = (1.0f / ((fConst80 * (fConst80 + fSlow39)) + 1.0f));
		float fSlow54 = ((fConst80 * (fConst80 - fSlow39)) + 1.0f);
		float fSlow55 = (1.0f / ((fConst84 * (fConst84 + fSlow22)) + 1.0f));
		float fSlow56 = ((fConst84 * (fConst84 - fSlow22)) + 1.0f);
		float fSlow57 = (1.0f / ((fConst88 * (fConst88 + fSlow39)) + 1.0f));
		float fSlow58 = ((fConst88 * (fConst88 - fSlow39)) + 1.0f);
		float fSlow59 = (1.0f / ((fConst92 * (fConst92 + fSlow22)) + 1.0f));
		float fSlow60 = ((fConst92 * (fConst92 - fSlow22)) + 1.0f);
		float fSlow61 = (0.177122265f * fSlow0);
		float fSlow62 = (1.0f / ((fConst96 * (fConst96 + fSlow61)) + 1.0f));
		float fSlow63 = ((fConst96 * (fConst96 - fSlow61)) + 1.0f);
		float fSlow64 = (1.0f / ((fConst100 * (fConst100 + fSlow13)) + 1.0f));
		float fSlow65 = ((fConst100 * (fConst100 - fSlow13)) + 1.0f);
		float fSlow66 = (1.0f / ((fConst104 * (fConst104 + fSlow1)) + 1.0f));
		float fSlow67 = ((fConst104 * (fConst104 - fSlow1)) + 1.0f);
		float fSlow68 = (1.0f / ((fConst108 * (fConst108 + fSlow31)) + 1.0f));
		float fSlow69 = ((fConst108 * (fConst108 - fSlow31)) + 1.0f);
		float fSlow70 = (0.177122265f * fSlow0);
		float fSlow71 = (1.0f / ((fConst112 * (fConst112 + fSlow70)) + 1.0f));
		float fSlow72 = ((fConst112 * (fConst112 - fSlow70)) + 1.0f);
		float fSlow73 = (1.0f / ((fConst116 * (fConst116 + fSlow1)) + 1.0f));
		float fSlow74 = ((fConst116 * (fConst116 - fSlow1)) + 1.0f);
		float fSlow75 = (1.0f / ((fConst120 * (fConst120 + fSlow39)) + 1.0f));
		float fSlow76 = ((fConst120 * (fConst120 - fSlow39)) + 1.0f);
		float fSlow77 = (0.177122265f * fSlow0);
		float fSlow78 = (1.0f / ((fConst124 * (fConst124 + fSlow77)) + 1.0f));
		float fSlow79 = ((fConst124 * (fConst124 - fSlow77)) + 1.0f);
		float fSlow80 = (1.0f / ((fConst128 * (fConst128 + fSlow61)) + 1.0f));
		float fSlow81 = ((fConst128 * (fConst128 - fSlow61)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow3 + (0.999000013f * fRec1[1]));
			fVec0[0] = fSlow4;
			float fTemp0 = (fRec2[1] + (fConst3 * fVec0[1]));
			fRec2[0] = (fTemp0 - (float)java.lang.Math.floor(fTemp0));
			float fTemp1 = (fRec1[0] * ((((fRec2[0] - fRec2[1]) < 0.0f))?1.f:0.f));
			fRec0[0] = (fTemp1 - (fSlow2 * ((fSlow5 * fRec0[2]) + (fConst4 * fRec0[1]))));
			float fTemp2 = input0[i];
			fRec5[0] = (fTemp2 - (fSlow2 * ((fConst4 * fRec5[1]) + (fSlow5 * fRec5[2]))));
			float fTemp3 = (float)java.lang.Math.abs((fSlow2 * ((fConst2 * fRec5[0]) + (fConst5 * fRec5[2]))));
			float fTemp4 = (((fRec3[1] > fTemp3))?fSlow7:fSlow6);
			fRec4[0] = ((fRec4[1] * fTemp4) + (fTemp3 * (1.0f - fTemp4)));
			fRec3[0] = fRec4[0];
			fRec6[0] = (fTemp1 - (fSlow9 * ((fSlow10 * fRec6[2]) + (fConst9 * fRec6[1]))));
			fRec9[0] = (fTemp2 - (fSlow9 * ((fConst9 * fRec9[1]) + (fSlow10 * fRec9[2]))));
			float fTemp5 = (float)java.lang.Math.abs((fSlow9 * ((fConst8 * fRec9[0]) + (fConst10 * fRec9[2]))));
			float fTemp6 = (((fRec7[1] > fTemp5))?fSlow7:fSlow6);
			fRec8[0] = ((fRec8[1] * fTemp6) + (fTemp5 * (1.0f - fTemp6)));
			fRec7[0] = fRec8[0];
			fRec10[0] = (fTemp1 - (fSlow11 * ((fSlow12 * fRec10[2]) + (fConst13 * fRec10[1]))));
			fRec13[0] = (fTemp2 - (fSlow11 * ((fConst13 * fRec13[1]) + (fSlow12 * fRec13[2]))));
			float fTemp7 = (float)java.lang.Math.abs((fSlow11 * ((fConst12 * fRec13[0]) + (fConst14 * fRec13[2]))));
			float fTemp8 = (((fRec11[1] > fTemp7))?fSlow7:fSlow6);
			fRec12[0] = ((fRec12[1] * fTemp8) + (fTemp7 * (1.0f - fTemp8)));
			fRec11[0] = fRec12[0];
			fRec14[0] = (fTemp1 - (fSlow14 * ((fSlow15 * fRec14[2]) + (fConst17 * fRec14[1]))));
			fRec17[0] = (fTemp2 - (fSlow14 * ((fConst17 * fRec17[1]) + (fSlow15 * fRec17[2]))));
			float fTemp9 = (float)java.lang.Math.abs((fSlow14 * ((fConst16 * fRec17[0]) + (fConst18 * fRec17[2]))));
			float fTemp10 = (((fRec15[1] > fTemp9))?fSlow7:fSlow6);
			fRec16[0] = ((fRec16[1] * fTemp10) + (fTemp9 * (1.0f - fTemp10)));
			fRec15[0] = fRec16[0];
			fRec18[0] = (fTemp1 - (fSlow17 * ((fSlow18 * fRec18[2]) + (fConst21 * fRec18[1]))));
			fRec21[0] = (fTemp2 - (fSlow17 * ((fConst21 * fRec21[1]) + (fSlow18 * fRec21[2]))));
			float fTemp11 = (float)java.lang.Math.abs((fSlow17 * ((fConst20 * fRec21[0]) + (fConst22 * fRec21[2]))));
			float fTemp12 = (((fRec19[1] > fTemp11))?fSlow7:fSlow6);
			fRec20[0] = ((fRec20[1] * fTemp12) + (fTemp11 * (1.0f - fTemp12)));
			fRec19[0] = fRec20[0];
			fRec22[0] = (fTemp1 - (fSlow20 * ((fSlow21 * fRec22[2]) + (fConst25 * fRec22[1]))));
			fRec25[0] = (fTemp2 - (fSlow20 * ((fConst25 * fRec25[1]) + (fSlow21 * fRec25[2]))));
			float fTemp13 = (float)java.lang.Math.abs((fSlow20 * ((fConst24 * fRec25[0]) + (fConst26 * fRec25[2]))));
			float fTemp14 = (((fRec23[1] > fTemp13))?fSlow7:fSlow6);
			fRec24[0] = ((fRec24[1] * fTemp14) + (fTemp13 * (1.0f - fTemp14)));
			fRec23[0] = fRec24[0];
			fRec26[0] = (fTemp1 - (fSlow23 * ((fSlow24 * fRec26[2]) + (fConst29 * fRec26[1]))));
			fRec29[0] = (fTemp2 - (fSlow23 * ((fConst29 * fRec29[1]) + (fSlow24 * fRec29[2]))));
			float fTemp15 = (float)java.lang.Math.abs((fSlow23 * ((fConst28 * fRec29[0]) + (fConst30 * fRec29[2]))));
			float fTemp16 = (((fRec27[1] > fTemp15))?fSlow7:fSlow6);
			fRec28[0] = ((fRec28[1] * fTemp16) + (fTemp15 * (1.0f - fTemp16)));
			fRec27[0] = fRec28[0];
			fRec30[0] = (fTemp1 - (fSlow25 * ((fSlow26 * fRec30[2]) + (fConst33 * fRec30[1]))));
			fRec33[0] = (fTemp2 - (fSlow25 * ((fConst33 * fRec33[1]) + (fSlow26 * fRec33[2]))));
			float fTemp17 = (float)java.lang.Math.abs((fSlow25 * ((fConst32 * fRec33[0]) + (fConst34 * fRec33[2]))));
			float fTemp18 = (((fRec31[1] > fTemp17))?fSlow7:fSlow6);
			fRec32[0] = ((fRec32[1] * fTemp18) + (fTemp17 * (1.0f - fTemp18)));
			fRec31[0] = fRec32[0];
			fRec34[0] = (fTemp1 - (fSlow27 * ((fSlow28 * fRec34[2]) + (fConst37 * fRec34[1]))));
			fRec37[0] = (fTemp2 - (fSlow27 * ((fConst37 * fRec37[1]) + (fSlow28 * fRec37[2]))));
			float fTemp19 = (float)java.lang.Math.abs((fSlow27 * ((fConst36 * fRec37[0]) + (fConst38 * fRec37[2]))));
			float fTemp20 = (((fRec35[1] > fTemp19))?fSlow7:fSlow6);
			fRec36[0] = ((fRec36[1] * fTemp20) + (fTemp19 * (1.0f - fTemp20)));
			fRec35[0] = fRec36[0];
			fRec38[0] = (fTemp1 - (fSlow29 * ((fSlow30 * fRec38[2]) + (fConst41 * fRec38[1]))));
			fRec41[0] = (fTemp2 - (fSlow29 * ((fConst41 * fRec41[1]) + (fSlow30 * fRec41[2]))));
			float fTemp21 = (float)java.lang.Math.abs((fSlow29 * ((fConst40 * fRec41[0]) + (fConst42 * fRec41[2]))));
			float fTemp22 = (((fRec39[1] > fTemp21))?fSlow7:fSlow6);
			fRec40[0] = ((fRec40[1] * fTemp22) + (fTemp21 * (1.0f - fTemp22)));
			fRec39[0] = fRec40[0];
			fRec42[0] = (fTemp1 - (fSlow32 * ((fSlow33 * fRec42[2]) + (fConst45 * fRec42[1]))));
			fRec45[0] = (fTemp2 - (fSlow32 * ((fConst45 * fRec45[1]) + (fSlow33 * fRec45[2]))));
			float fTemp23 = (float)java.lang.Math.abs((fSlow32 * ((fConst44 * fRec45[0]) + (fConst46 * fRec45[2]))));
			float fTemp24 = (((fRec43[1] > fTemp23))?fSlow7:fSlow6);
			fRec44[0] = ((fRec44[1] * fTemp24) + (fTemp23 * (1.0f - fTemp24)));
			fRec43[0] = fRec44[0];
			fRec46[0] = (fTemp1 - (fSlow35 * ((fSlow36 * fRec46[2]) + (fConst49 * fRec46[1]))));
			fRec49[0] = (fTemp2 - (fSlow35 * ((fConst49 * fRec49[1]) + (fSlow36 * fRec49[2]))));
			float fTemp25 = (float)java.lang.Math.abs((fSlow35 * ((fConst48 * fRec49[0]) + (fConst50 * fRec49[2]))));
			float fTemp26 = (((fRec47[1] > fTemp25))?fSlow7:fSlow6);
			fRec48[0] = ((fRec48[1] * fTemp26) + (fTemp25 * (1.0f - fTemp26)));
			fRec47[0] = fRec48[0];
			fRec50[0] = (fTemp1 - (fSlow37 * ((fSlow38 * fRec50[2]) + (fConst53 * fRec50[1]))));
			fRec53[0] = (fTemp2 - (fSlow37 * ((fConst53 * fRec53[1]) + (fSlow38 * fRec53[2]))));
			float fTemp27 = (float)java.lang.Math.abs((fSlow37 * ((fConst52 * fRec53[0]) + (fConst54 * fRec53[2]))));
			float fTemp28 = (((fRec51[1] > fTemp27))?fSlow7:fSlow6);
			fRec52[0] = ((fRec52[1] * fTemp28) + (fTemp27 * (1.0f - fTemp28)));
			fRec51[0] = fRec52[0];
			fRec54[0] = (fTemp1 - (fSlow40 * ((fSlow41 * fRec54[2]) + (fConst57 * fRec54[1]))));
			fRec57[0] = (fTemp2 - (fSlow40 * ((fConst57 * fRec57[1]) + (fSlow41 * fRec57[2]))));
			float fTemp29 = (float)java.lang.Math.abs((fSlow40 * ((fConst56 * fRec57[0]) + (fConst58 * fRec57[2]))));
			float fTemp30 = (((fRec55[1] > fTemp29))?fSlow7:fSlow6);
			fRec56[0] = ((fRec56[1] * fTemp30) + (fTemp29 * (1.0f - fTemp30)));
			fRec55[0] = fRec56[0];
			fRec58[0] = (fTemp1 - (fSlow42 * ((fSlow43 * fRec58[2]) + (fConst61 * fRec58[1]))));
			fRec61[0] = (fTemp2 - (fSlow42 * ((fConst61 * fRec61[1]) + (fSlow43 * fRec61[2]))));
			float fTemp31 = (float)java.lang.Math.abs((fSlow42 * ((fConst60 * fRec61[0]) + (fConst62 * fRec61[2]))));
			float fTemp32 = (((fRec59[1] > fTemp31))?fSlow7:fSlow6);
			fRec60[0] = ((fRec60[1] * fTemp32) + (fTemp31 * (1.0f - fTemp32)));
			fRec59[0] = fRec60[0];
			fRec62[0] = (fTemp1 - (fSlow44 * ((fSlow45 * fRec62[2]) + (fConst65 * fRec62[1]))));
			fRec65[0] = (fTemp2 - (fSlow44 * ((fConst65 * fRec65[1]) + (fSlow45 * fRec65[2]))));
			float fTemp33 = (float)java.lang.Math.abs((fSlow44 * ((fConst64 * fRec65[0]) + (fConst66 * fRec65[2]))));
			float fTemp34 = (((fRec63[1] > fTemp33))?fSlow7:fSlow6);
			fRec64[0] = ((fRec64[1] * fTemp34) + (fTemp33 * (1.0f - fTemp34)));
			fRec63[0] = fRec64[0];
			fRec66[0] = (fTemp1 - (fSlow46 * ((fSlow47 * fRec66[2]) + (fConst69 * fRec66[1]))));
			fRec69[0] = (fTemp2 - (fSlow46 * ((fConst69 * fRec69[1]) + (fSlow47 * fRec69[2]))));
			float fTemp35 = (float)java.lang.Math.abs((fSlow46 * ((fConst68 * fRec69[0]) + (fConst70 * fRec69[2]))));
			float fTemp36 = (((fRec67[1] > fTemp35))?fSlow7:fSlow6);
			fRec68[0] = ((fRec68[1] * fTemp36) + (fTemp35 * (1.0f - fTemp36)));
			fRec67[0] = fRec68[0];
			fRec70[0] = (fTemp1 - (fSlow49 * ((fSlow50 * fRec70[2]) + (fConst73 * fRec70[1]))));
			fRec73[0] = (fTemp2 - (fSlow49 * ((fConst73 * fRec73[1]) + (fSlow50 * fRec73[2]))));
			float fTemp37 = (float)java.lang.Math.abs((fSlow49 * ((fConst72 * fRec73[0]) + (fConst74 * fRec73[2]))));
			float fTemp38 = (((fRec71[1] > fTemp37))?fSlow7:fSlow6);
			fRec72[0] = ((fRec72[1] * fTemp38) + (fTemp37 * (1.0f - fTemp38)));
			fRec71[0] = fRec72[0];
			fRec74[0] = (fTemp1 - (fSlow51 * ((fSlow52 * fRec74[2]) + (fConst77 * fRec74[1]))));
			fRec77[0] = (fTemp2 - (fSlow51 * ((fConst77 * fRec77[1]) + (fSlow52 * fRec77[2]))));
			float fTemp39 = (float)java.lang.Math.abs((fSlow51 * ((fConst76 * fRec77[0]) + (fConst78 * fRec77[2]))));
			float fTemp40 = (((fRec75[1] > fTemp39))?fSlow7:fSlow6);
			fRec76[0] = ((fRec76[1] * fTemp40) + (fTemp39 * (1.0f - fTemp40)));
			fRec75[0] = fRec76[0];
			fRec78[0] = (fTemp1 - (fSlow53 * ((fSlow54 * fRec78[2]) + (fConst81 * fRec78[1]))));
			fRec81[0] = (fTemp2 - (fSlow53 * ((fConst81 * fRec81[1]) + (fSlow54 * fRec81[2]))));
			float fTemp41 = (float)java.lang.Math.abs((fSlow53 * ((fConst80 * fRec81[0]) + (fConst82 * fRec81[2]))));
			float fTemp42 = (((fRec79[1] > fTemp41))?fSlow7:fSlow6);
			fRec80[0] = ((fRec80[1] * fTemp42) + (fTemp41 * (1.0f - fTemp42)));
			fRec79[0] = fRec80[0];
			fRec82[0] = (fTemp1 - (fSlow55 * ((fSlow56 * fRec82[2]) + (fConst85 * fRec82[1]))));
			fRec85[0] = (fTemp2 - (fSlow55 * ((fConst85 * fRec85[1]) + (fSlow56 * fRec85[2]))));
			float fTemp43 = (float)java.lang.Math.abs((fSlow55 * ((fConst84 * fRec85[0]) + (fConst86 * fRec85[2]))));
			float fTemp44 = (((fRec83[1] > fTemp43))?fSlow7:fSlow6);
			fRec84[0] = ((fRec84[1] * fTemp44) + (fTemp43 * (1.0f - fTemp44)));
			fRec83[0] = fRec84[0];
			fRec86[0] = (fTemp1 - (fSlow57 * ((fSlow58 * fRec86[2]) + (fConst89 * fRec86[1]))));
			fRec89[0] = (fTemp2 - (fSlow57 * ((fConst89 * fRec89[1]) + (fSlow58 * fRec89[2]))));
			float fTemp45 = (float)java.lang.Math.abs((fSlow57 * ((fConst88 * fRec89[0]) + (fConst90 * fRec89[2]))));
			float fTemp46 = (((fRec87[1] > fTemp45))?fSlow7:fSlow6);
			fRec88[0] = ((fRec88[1] * fTemp46) + (fTemp45 * (1.0f - fTemp46)));
			fRec87[0] = fRec88[0];
			fRec90[0] = (fTemp1 - (fSlow59 * ((fSlow60 * fRec90[2]) + (fConst93 * fRec90[1]))));
			fRec93[0] = (fTemp2 - (fSlow59 * ((fConst93 * fRec93[1]) + (fSlow60 * fRec93[2]))));
			float fTemp47 = (float)java.lang.Math.abs((fSlow59 * ((fConst92 * fRec93[0]) + (fConst94 * fRec93[2]))));
			float fTemp48 = (((fRec91[1] > fTemp47))?fSlow7:fSlow6);
			fRec92[0] = ((fRec92[1] * fTemp48) + (fTemp47 * (1.0f - fTemp48)));
			fRec91[0] = fRec92[0];
			fRec94[0] = (fTemp1 - (fSlow62 * ((fSlow63 * fRec94[2]) + (fConst97 * fRec94[1]))));
			fRec97[0] = (fTemp2 - (fSlow62 * ((fConst97 * fRec97[1]) + (fSlow63 * fRec97[2]))));
			float fTemp49 = (float)java.lang.Math.abs((fSlow62 * ((fConst96 * fRec97[0]) + (fConst98 * fRec97[2]))));
			float fTemp50 = (((fRec95[1] > fTemp49))?fSlow7:fSlow6);
			fRec96[0] = ((fRec96[1] * fTemp50) + (fTemp49 * (1.0f - fTemp50)));
			fRec95[0] = fRec96[0];
			fRec98[0] = (fTemp1 - (fSlow64 * ((fSlow65 * fRec98[2]) + (fConst101 * fRec98[1]))));
			fRec101[0] = (fTemp2 - (fSlow64 * ((fConst101 * fRec101[1]) + (fSlow65 * fRec101[2]))));
			float fTemp51 = (float)java.lang.Math.abs((fSlow64 * ((fConst100 * fRec101[0]) + (fConst102 * fRec101[2]))));
			float fTemp52 = (((fRec99[1] > fTemp51))?fSlow7:fSlow6);
			fRec100[0] = ((fRec100[1] * fTemp52) + (fTemp51 * (1.0f - fTemp52)));
			fRec99[0] = fRec100[0];
			fRec102[0] = (fTemp1 - (fSlow66 * ((fSlow67 * fRec102[2]) + (fConst105 * fRec102[1]))));
			fRec105[0] = (fTemp2 - (fSlow66 * ((fConst105 * fRec105[1]) + (fSlow67 * fRec105[2]))));
			float fTemp53 = (float)java.lang.Math.abs((fSlow66 * ((fConst104 * fRec105[0]) + (fConst106 * fRec105[2]))));
			float fTemp54 = (((fRec103[1] > fTemp53))?fSlow7:fSlow6);
			fRec104[0] = ((fRec104[1] * fTemp54) + (fTemp53 * (1.0f - fTemp54)));
			fRec103[0] = fRec104[0];
			fRec106[0] = (fTemp1 - (fSlow68 * ((fSlow69 * fRec106[2]) + (fConst109 * fRec106[1]))));
			fRec109[0] = (fTemp2 - (fSlow68 * ((fConst109 * fRec109[1]) + (fSlow69 * fRec109[2]))));
			float fTemp55 = (float)java.lang.Math.abs((fSlow68 * ((fConst108 * fRec109[0]) + (fConst110 * fRec109[2]))));
			float fTemp56 = (((fRec107[1] > fTemp55))?fSlow7:fSlow6);
			fRec108[0] = ((fRec108[1] * fTemp56) + (fTemp55 * (1.0f - fTemp56)));
			fRec107[0] = fRec108[0];
			fRec110[0] = (fTemp1 - (fSlow71 * ((fSlow72 * fRec110[2]) + (fConst113 * fRec110[1]))));
			fRec113[0] = (fTemp2 - (fSlow71 * ((fConst113 * fRec113[1]) + (fSlow72 * fRec113[2]))));
			float fTemp57 = (float)java.lang.Math.abs((fSlow71 * ((fConst112 * fRec113[0]) + (fConst114 * fRec113[2]))));
			float fTemp58 = (((fRec111[1] > fTemp57))?fSlow7:fSlow6);
			fRec112[0] = ((fRec112[1] * fTemp58) + (fTemp57 * (1.0f - fTemp58)));
			fRec111[0] = fRec112[0];
			fRec114[0] = (fTemp1 - (fSlow73 * ((fSlow74 * fRec114[2]) + (fConst117 * fRec114[1]))));
			fRec117[0] = (fTemp2 - (fSlow73 * ((fConst117 * fRec117[1]) + (fSlow74 * fRec117[2]))));
			float fTemp59 = (float)java.lang.Math.abs((fSlow73 * ((fConst116 * fRec117[0]) + (fConst118 * fRec117[2]))));
			float fTemp60 = (((fRec115[1] > fTemp59))?fSlow7:fSlow6);
			fRec116[0] = ((fRec116[1] * fTemp60) + (fTemp59 * (1.0f - fTemp60)));
			fRec115[0] = fRec116[0];
			fRec118[0] = (fTemp1 - (fSlow75 * ((fSlow76 * fRec118[2]) + (fConst121 * fRec118[1]))));
			fRec121[0] = (fTemp2 - (fSlow75 * ((fConst121 * fRec121[1]) + (fSlow76 * fRec121[2]))));
			float fTemp61 = (float)java.lang.Math.abs((fSlow75 * ((fConst120 * fRec121[0]) + (fConst122 * fRec121[2]))));
			float fTemp62 = (((fRec119[1] > fTemp61))?fSlow7:fSlow6);
			fRec120[0] = ((fRec120[1] * fTemp62) + (fTemp61 * (1.0f - fTemp62)));
			fRec119[0] = fRec120[0];
			fRec122[0] = (fTemp1 - (fSlow78 * ((fSlow79 * fRec122[2]) + (fConst125 * fRec122[1]))));
			fRec125[0] = (fTemp2 - (fSlow78 * ((fConst125 * fRec125[1]) + (fSlow79 * fRec125[2]))));
			float fTemp63 = (float)java.lang.Math.abs((fSlow78 * ((fConst124 * fRec125[0]) + (fConst126 * fRec125[2]))));
			float fTemp64 = (((fRec123[1] > fTemp63))?fSlow7:fSlow6);
			fRec124[0] = ((fRec124[1] * fTemp64) + (fTemp63 * (1.0f - fTemp64)));
			fRec123[0] = fRec124[0];
			fRec126[0] = (fTemp1 - (fSlow80 * ((fSlow81 * fRec126[2]) + (fConst129 * fRec126[1]))));
			fRec129[0] = (fTemp2 - (fSlow80 * ((fConst129 * fRec129[1]) + (fSlow81 * fRec129[2]))));
			float fTemp65 = (float)java.lang.Math.abs((fSlow80 * ((fConst128 * fRec129[0]) + (fConst130 * fRec129[2]))));
			float fTemp66 = (((fRec127[1] > fTemp65))?fSlow7:fSlow6);
			fRec128[0] = ((fRec128[1] * fTemp66) + (fTemp65 * (1.0f - fTemp66)));
			fRec127[0] = fRec128[0];
			float fTemp67 = ((((((((((((((((((((((((((((((((fSlow2 * ((fRec0[2] * (0.0f - (fConst2 * fRec3[0]))) + (fConst2 * (fRec0[0] * fRec3[0])))) + (fSlow9 * ((fRec6[2] * (0.0f - (fConst8 * fRec7[0]))) + (fConst8 * (fRec6[0] * fRec7[0]))))) + (fSlow11 * ((fRec10[2] * (0.0f - (fConst12 * fRec11[0]))) + (fConst12 * (fRec10[0] * fRec11[0]))))) + (fSlow14 * ((fRec14[2] * (0.0f - (fConst16 * fRec15[0]))) + (fConst16 * (fRec14[0] * fRec15[0]))))) + (fSlow17 * ((fRec18[2] * (0.0f - (fConst20 * fRec19[0]))) + (fConst20 * (fRec18[0] * fRec19[0]))))) + (fSlow20 * ((fRec22[2] * (0.0f - (fConst24 * fRec23[0]))) + (fConst24 * (fRec22[0] * fRec23[0]))))) + (fSlow23 * ((fRec26[2] * (0.0f - (fConst28 * fRec27[0]))) + (fConst28 * (fRec26[0] * fRec27[0]))))) + (fSlow25 * ((fRec30[2] * (0.0f - (fConst32 * fRec31[0]))) + (fConst32 * (fRec30[0] * fRec31[0]))))) + (fSlow27 * ((fRec34[2] * (0.0f - (fConst36 * fRec35[0]))) + (fConst36 * (fRec34[0] * fRec35[0]))))) + (fSlow29 * ((fRec38[2] * (0.0f - (fConst40 * fRec39[0]))) + (fConst40 * (fRec38[0] * fRec39[0]))))) + (fSlow32 * ((fRec42[2] * (0.0f - (fConst44 * fRec43[0]))) + (fConst44 * (fRec42[0] * fRec43[0]))))) + (fSlow35 * ((fRec46[2] * (0.0f - (fConst48 * fRec47[0]))) + (fConst48 * (fRec46[0] * fRec47[0]))))) + (fSlow37 * ((fRec50[2] * (0.0f - (fConst52 * fRec51[0]))) + (fConst52 * (fRec50[0] * fRec51[0]))))) + (fSlow40 * ((fRec54[2] * (0.0f - (fConst56 * fRec55[0]))) + (fConst56 * (fRec54[0] * fRec55[0]))))) + (fSlow42 * ((fRec58[2] * (0.0f - (fConst60 * fRec59[0]))) + (fConst60 * (fRec58[0] * fRec59[0]))))) + (fSlow44 * ((fRec62[2] * (0.0f - (fConst64 * fRec63[0]))) + (fConst64 * (fRec62[0] * fRec63[0]))))) + (fSlow46 * ((fRec66[2] * (0.0f - (fConst68 * fRec67[0]))) + (fConst68 * (fRec66[0] * fRec67[0]))))) + (fSlow49 * ((fRec70[2] * (0.0f - (fConst72 * fRec71[0]))) + (fConst72 * (fRec70[0] * fRec71[0]))))) + (fSlow51 * ((fRec74[2] * (0.0f - (fConst76 * fRec75[0]))) + (fConst76 * (fRec74[0] * fRec75[0]))))) + (fSlow53 * ((fRec78[2] * (0.0f - (fConst80 * fRec79[0]))) + (fConst80 * (fRec78[0] * fRec79[0]))))) + (fSlow55 * ((fRec82[2] * (0.0f - (fConst84 * fRec83[0]))) + (fConst84 * (fRec82[0] * fRec83[0]))))) + (fSlow57 * ((fRec86[2] * (0.0f - (fConst88 * fRec87[0]))) + (fConst88 * (fRec86[0] * fRec87[0]))))) + (fSlow59 * ((fRec90[2] * (0.0f - (fConst92 * fRec91[0]))) + (fConst92 * (fRec90[0] * fRec91[0]))))) + (fSlow62 * ((fRec94[2] * (0.0f - (fConst96 * fRec95[0]))) + (fConst96 * (fRec94[0] * fRec95[0]))))) + (fSlow64 * ((fRec98[2] * (0.0f - (fConst100 * fRec99[0]))) + (fConst100 * (fRec98[0] * fRec99[0]))))) + (fSlow66 * ((fRec102[2] * (0.0f - (fConst104 * fRec103[0]))) + (fConst104 * (fRec102[0] * fRec103[0]))))) + (fSlow68 * ((fRec106[2] * (0.0f - (fConst108 * fRec107[0]))) + (fConst108 * (fRec106[0] * fRec107[0]))))) + (fSlow71 * ((fRec110[2] * (0.0f - (fConst112 * fRec111[0]))) + (fConst112 * (fRec110[0] * fRec111[0]))))) + (fSlow73 * ((fRec114[2] * (0.0f - (fConst116 * fRec115[0]))) + (fConst116 * (fRec114[0] * fRec115[0]))))) + (fSlow75 * ((fRec118[2] * (0.0f - (fConst120 * fRec119[0]))) + (fConst120 * (fRec118[0] * fRec119[0]))))) + (fSlow78 * ((fRec122[2] * (0.0f - (fConst124 * fRec123[0]))) + (fConst124 * (fRec122[0] * fRec123[0]))))) + (fSlow80 * ((fRec126[2] * (0.0f - (fConst128 * fRec127[0]))) + (fConst128 * (fRec126[0] * fRec127[0])))));
			output0[i] = fTemp67;
			output1[i] = fTemp67;
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[1] = fRec56[0];
			fRec55[1] = fRec55[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[1] = fRec64[0];
			fRec63[1] = fRec63[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[1] = fRec72[0];
			fRec71[1] = fRec71[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[1] = fRec76[0];
			fRec75[1] = fRec75[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[1] = fRec80[0];
			fRec79[1] = fRec79[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[1] = fRec84[0];
			fRec83[1] = fRec83[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[1] = fRec88[0];
			fRec87[1] = fRec87[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[1] = fRec92[0];
			fRec91[1] = fRec91[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[1] = fRec100[0];
			fRec99[1] = fRec99[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[1] = fRec104[0];
			fRec103[1] = fRec103[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[1] = fRec108[0];
			fRec107[1] = fRec107[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[1] = fRec112[0];
			fRec111[1] = fRec111[0];
			fRec114[2] = fRec114[1];
			fRec114[1] = fRec114[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[1] = fRec116[0];
			fRec115[1] = fRec115[0];
			fRec118[2] = fRec118[1];
			fRec118[1] = fRec118[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[1] = fRec120[0];
			fRec119[1] = fRec119[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec124[1] = fRec124[0];
			fRec123[1] = fRec123[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec128[1] = fRec128[0];
			fRec127[1] = fRec127[0];
			
		}
		
	}
	
};

