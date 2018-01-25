/* ------------------------------------------------------------
name: "filterBank"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	
	float fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fVec0[] = new float[2];
	float fConst11;
	float fRec10[] = new float[2];
	float fConst12;
	float fConst13;
	float fRec9[] = new float[3];
	float fConst14;
	float fRec8[] = new float[3];
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec7[] = new float[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec6[] = new float[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec5[] = new float[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec4[] = new float[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec3[] = new float[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec2[] = new float[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec1[] = new float[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec0[] = new float[3];
	float fVslider0;
	float fRec11[] = new float[2];
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec24[] = new float[2];
	float fRec23[] = new float[3];
	float fRec22[] = new float[3];
	float fVec1[] = new float[2];
	float fConst70;
	float fRec21[] = new float[2];
	float fConst71;
	float fRec20[] = new float[3];
	float fConst72;
	float fRec19[] = new float[3];
	float fRec18[] = new float[3];
	float fRec17[] = new float[3];
	float fRec16[] = new float[3];
	float fRec15[] = new float[3];
	float fRec14[] = new float[3];
	float fRec13[] = new float[3];
	float fRec12[] = new float[3];
	float fVslider1;
	float fRec25[] = new float[2];
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec37[] = new float[2];
	float fRec36[] = new float[3];
	float fRec35[] = new float[3];
	float fVec2[] = new float[2];
	float fConst80;
	float fRec34[] = new float[2];
	float fConst81;
	float fRec33[] = new float[3];
	float fConst82;
	float fRec32[] = new float[3];
	float fRec31[] = new float[3];
	float fRec30[] = new float[3];
	float fRec29[] = new float[3];
	float fRec28[] = new float[3];
	float fRec27[] = new float[3];
	float fRec26[] = new float[3];
	float fVslider2;
	float fRec38[] = new float[2];
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec49[] = new float[2];
	float fRec48[] = new float[3];
	float fRec47[] = new float[3];
	float fVec3[] = new float[2];
	float fConst90;
	float fRec46[] = new float[2];
	float fConst91;
	float fRec45[] = new float[3];
	float fConst92;
	float fRec44[] = new float[3];
	float fRec43[] = new float[3];
	float fRec42[] = new float[3];
	float fRec41[] = new float[3];
	float fRec40[] = new float[3];
	float fRec39[] = new float[3];
	float fVslider3;
	float fRec50[] = new float[2];
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec60[] = new float[2];
	float fRec59[] = new float[3];
	float fRec58[] = new float[3];
	float fVec4[] = new float[2];
	float fConst100;
	float fRec57[] = new float[2];
	float fConst101;
	float fRec56[] = new float[3];
	float fConst102;
	float fRec55[] = new float[3];
	float fRec54[] = new float[3];
	float fRec53[] = new float[3];
	float fRec52[] = new float[3];
	float fRec51[] = new float[3];
	float fVslider4;
	float fRec61[] = new float[2];
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec70[] = new float[2];
	float fRec69[] = new float[3];
	float fRec68[] = new float[3];
	float fVec5[] = new float[2];
	float fConst110;
	float fRec67[] = new float[2];
	float fConst111;
	float fRec66[] = new float[3];
	float fConst112;
	float fRec65[] = new float[3];
	float fRec64[] = new float[3];
	float fRec63[] = new float[3];
	float fRec62[] = new float[3];
	float fVslider5;
	float fRec71[] = new float[2];
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec79[] = new float[2];
	float fRec78[] = new float[3];
	float fRec77[] = new float[3];
	float fVec6[] = new float[2];
	float fConst120;
	float fRec76[] = new float[2];
	float fConst121;
	float fRec75[] = new float[3];
	float fConst122;
	float fRec74[] = new float[3];
	float fRec73[] = new float[3];
	float fRec72[] = new float[3];
	float fVslider6;
	float fRec80[] = new float[2];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec87[] = new float[2];
	float fRec86[] = new float[3];
	float fRec85[] = new float[3];
	float fVec7[] = new float[2];
	float fConst130;
	float fRec84[] = new float[2];
	float fConst131;
	float fRec83[] = new float[3];
	float fConst132;
	float fRec82[] = new float[3];
	float fRec81[] = new float[3];
	float fVslider7;
	float fRec88[] = new float[2];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec94[] = new float[2];
	float fRec93[] = new float[3];
	float fRec92[] = new float[3];
	float fVec8[] = new float[2];
	float fConst139;
	float fRec91[] = new float[2];
	float fConst140;
	float fRec90[] = new float[3];
	float fConst141;
	float fRec89[] = new float[3];
	float fVslider8;
	float fRec95[] = new float[2];
	float fRec98[] = new float[2];
	float fRec97[] = new float[3];
	float fRec96[] = new float[3];
	float fVslider9;
	float fRec99[] = new float[2];
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Graphic Equalizer consisting of a filter-bank driving a bank of faders");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "filterBank");
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
		fConst1 = (float)java.lang.Math.tan((31415.9258f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (((fConst2 + 0.618034005f) / fConst1) + 1.0f);
		fConst4 = (1.0f / fConst3);
		fConst5 = (1.0f / mydsp_faustpower2_f(fConst1));
		fConst6 = (2.0f * (0.0f - fConst5));
		fConst7 = (1.0f / (((fConst2 + 1.61803401f) / fConst1) + 1.0f));
		fConst8 = (fConst2 + 1.0f);
		fConst9 = (0.0f - ((1.0f - fConst2) / fConst8));
		fConst10 = (1.0f / fConst8);
		fConst11 = (0.0f - fConst2);
		fConst12 = (2.0f * (1.0f - fConst5));
		fConst13 = (((fConst2 + -1.61803401f) / fConst1) + 1.0f);
		fConst14 = (((fConst2 + -0.618034005f) / fConst1) + 1.0f);
		fConst15 = (float)java.lang.Math.tan((122.71846f / fConst0));
		fConst16 = (1.0f / fConst15);
		fConst17 = (1.0f / (((fConst16 + 1.61803401f) / fConst15) + 1.0f));
		fConst18 = (((fConst16 + -1.61803401f) / fConst15) + 1.0f);
		fConst19 = (1.0f / mydsp_faustpower2_f(fConst15));
		fConst20 = (2.0f * (1.0f - fConst19));
		fConst21 = (float)java.lang.Math.tan((245.43692f / fConst0));
		fConst22 = (1.0f / fConst21);
		fConst23 = (1.0f / (((fConst22 + 1.61803401f) / fConst21) + 1.0f));
		fConst24 = (((fConst22 + -1.61803401f) / fConst21) + 1.0f);
		fConst25 = (1.0f / mydsp_faustpower2_f(fConst21));
		fConst26 = (2.0f * (1.0f - fConst25));
		fConst27 = (float)java.lang.Math.tan((490.87384f / fConst0));
		fConst28 = (1.0f / fConst27);
		fConst29 = (1.0f / (((fConst28 + 1.61803401f) / fConst27) + 1.0f));
		fConst30 = (((fConst28 + -1.61803401f) / fConst27) + 1.0f);
		fConst31 = (1.0f / mydsp_faustpower2_f(fConst27));
		fConst32 = (2.0f * (1.0f - fConst31));
		fConst33 = (float)java.lang.Math.tan((981.747681f / fConst0));
		fConst34 = (1.0f / fConst33);
		fConst35 = (1.0f / (((fConst34 + 1.61803401f) / fConst33) + 1.0f));
		fConst36 = (((fConst34 + -1.61803401f) / fConst33) + 1.0f);
		fConst37 = (1.0f / mydsp_faustpower2_f(fConst33));
		fConst38 = (2.0f * (1.0f - fConst37));
		fConst39 = (float)java.lang.Math.tan((1963.49536f / fConst0));
		fConst40 = (1.0f / fConst39);
		fConst41 = (1.0f / (((fConst40 + 1.61803401f) / fConst39) + 1.0f));
		fConst42 = (((fConst40 + -1.61803401f) / fConst39) + 1.0f);
		fConst43 = (1.0f / mydsp_faustpower2_f(fConst39));
		fConst44 = (2.0f * (1.0f - fConst43));
		fConst45 = (float)java.lang.Math.tan((3926.99072f / fConst0));
		fConst46 = (1.0f / fConst45);
		fConst47 = (1.0f / (((fConst46 + 1.61803401f) / fConst45) + 1.0f));
		fConst48 = (((fConst46 + -1.61803401f) / fConst45) + 1.0f);
		fConst49 = (1.0f / mydsp_faustpower2_f(fConst45));
		fConst50 = (2.0f * (1.0f - fConst49));
		fConst51 = (float)java.lang.Math.tan((7853.98145f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (1.0f / (((fConst52 + 1.61803401f) / fConst51) + 1.0f));
		fConst54 = (((fConst52 + -1.61803401f) / fConst51) + 1.0f);
		fConst55 = (1.0f / mydsp_faustpower2_f(fConst51));
		fConst56 = (2.0f * (1.0f - fConst55));
		fConst57 = (float)java.lang.Math.tan((15707.9629f / fConst0));
		fConst58 = (1.0f / fConst57);
		fConst59 = (1.0f / (((fConst58 + 1.61803401f) / fConst57) + 1.0f));
		fConst60 = (((fConst58 + -1.61803401f) / fConst57) + 1.0f);
		fConst61 = (1.0f / mydsp_faustpower2_f(fConst57));
		fConst62 = (2.0f * (1.0f - fConst61));
		fConst63 = (((fConst58 + 0.618034005f) / fConst57) + 1.0f);
		fConst64 = (1.0f / fConst63);
		fConst65 = (2.0f * (0.0f - fConst61));
		fConst66 = (1.0f / (((fConst58 + 1.61803401f) / fConst57) + 1.0f));
		fConst67 = (fConst58 + 1.0f);
		fConst68 = (0.0f - ((1.0f - fConst58) / fConst67));
		fConst69 = (1.0f / (fConst3 * fConst67));
		fConst70 = (0.0f - fConst58);
		fConst71 = (((fConst58 + -1.61803401f) / fConst57) + 1.0f);
		fConst72 = (((fConst58 + -0.618034005f) / fConst57) + 1.0f);
		fConst73 = (((fConst52 + 0.618034005f) / fConst51) + 1.0f);
		fConst74 = (1.0f / fConst73);
		fConst75 = (2.0f * (0.0f - fConst55));
		fConst76 = (1.0f / (((fConst52 + 1.61803401f) / fConst51) + 1.0f));
		fConst77 = (fConst52 + 1.0f);
		fConst78 = (0.0f - ((1.0f - fConst52) / fConst77));
		fConst79 = (1.0f / (fConst63 * fConst77));
		fConst80 = (0.0f - fConst52);
		fConst81 = (((fConst52 + -1.61803401f) / fConst51) + 1.0f);
		fConst82 = (((fConst52 + -0.618034005f) / fConst51) + 1.0f);
		fConst83 = (((fConst46 + 0.618034005f) / fConst45) + 1.0f);
		fConst84 = (1.0f / fConst83);
		fConst85 = (2.0f * (0.0f - fConst49));
		fConst86 = (1.0f / (((fConst46 + 1.61803401f) / fConst45) + 1.0f));
		fConst87 = (fConst46 + 1.0f);
		fConst88 = (0.0f - ((1.0f - fConst46) / fConst87));
		fConst89 = (1.0f / (fConst73 * fConst87));
		fConst90 = (0.0f - fConst46);
		fConst91 = (((fConst46 + -1.61803401f) / fConst45) + 1.0f);
		fConst92 = (((fConst46 + -0.618034005f) / fConst45) + 1.0f);
		fConst93 = (((fConst40 + 0.618034005f) / fConst39) + 1.0f);
		fConst94 = (1.0f / fConst93);
		fConst95 = (2.0f * (0.0f - fConst43));
		fConst96 = (1.0f / (((fConst40 + 1.61803401f) / fConst39) + 1.0f));
		fConst97 = (fConst40 + 1.0f);
		fConst98 = (0.0f - ((1.0f - fConst40) / fConst97));
		fConst99 = (1.0f / (fConst83 * fConst97));
		fConst100 = (0.0f - fConst40);
		fConst101 = (((fConst40 + -1.61803401f) / fConst39) + 1.0f);
		fConst102 = (((fConst40 + -0.618034005f) / fConst39) + 1.0f);
		fConst103 = (((fConst34 + 0.618034005f) / fConst33) + 1.0f);
		fConst104 = (1.0f / fConst103);
		fConst105 = (2.0f * (0.0f - fConst37));
		fConst106 = (1.0f / (((fConst34 + 1.61803401f) / fConst33) + 1.0f));
		fConst107 = (fConst34 + 1.0f);
		fConst108 = (0.0f - ((1.0f - fConst34) / fConst107));
		fConst109 = (1.0f / (fConst93 * fConst107));
		fConst110 = (0.0f - fConst34);
		fConst111 = (((fConst34 + -1.61803401f) / fConst33) + 1.0f);
		fConst112 = (((fConst34 + -0.618034005f) / fConst33) + 1.0f);
		fConst113 = (((fConst28 + 0.618034005f) / fConst27) + 1.0f);
		fConst114 = (1.0f / fConst113);
		fConst115 = (2.0f * (0.0f - fConst31));
		fConst116 = (1.0f / (((fConst28 + 1.61803401f) / fConst27) + 1.0f));
		fConst117 = (fConst28 + 1.0f);
		fConst118 = (0.0f - ((1.0f - fConst28) / fConst117));
		fConst119 = (1.0f / (fConst103 * fConst117));
		fConst120 = (0.0f - fConst28);
		fConst121 = (((fConst28 + -1.61803401f) / fConst27) + 1.0f);
		fConst122 = (((fConst28 + -0.618034005f) / fConst27) + 1.0f);
		fConst123 = (((fConst22 + 0.618034005f) / fConst21) + 1.0f);
		fConst124 = (1.0f / fConst123);
		fConst125 = (2.0f * (0.0f - fConst25));
		fConst126 = (1.0f / (((fConst22 + 1.61803401f) / fConst21) + 1.0f));
		fConst127 = (fConst22 + 1.0f);
		fConst128 = (0.0f - ((1.0f - fConst22) / fConst127));
		fConst129 = (1.0f / (fConst113 * fConst127));
		fConst130 = (0.0f - fConst22);
		fConst131 = (((fConst22 + -1.61803401f) / fConst21) + 1.0f);
		fConst132 = (((fConst22 + -0.618034005f) / fConst21) + 1.0f);
		fConst133 = (1.0f / (((fConst16 + 0.618034005f) / fConst15) + 1.0f));
		fConst134 = (2.0f * (0.0f - fConst19));
		fConst135 = (1.0f / (((fConst16 + 1.61803401f) / fConst15) + 1.0f));
		fConst136 = (fConst16 + 1.0f);
		fConst137 = (0.0f - ((1.0f - fConst16) / fConst136));
		fConst138 = (1.0f / (fConst123 * fConst136));
		fConst139 = (0.0f - fConst16);
		fConst140 = (((fConst16 + -1.61803401f) / fConst15) + 1.0f);
		fConst141 = (((fConst16 + -0.618034005f) / fConst15) + 1.0f);
		
	}
	
	public void instanceResetUserInterface() {
		fCheckbox0 = (float)0.0f;
		fVslider0 = (float)-10.0f;
		fVslider1 = (float)-10.0f;
		fVslider2 = (float)-10.0f;
		fVslider3 = (float)-10.0f;
		fVslider4 = (float)-10.0f;
		fVslider5 = (float)-10.0f;
		fVslider6 = (float)-10.0f;
		fVslider7 = (float)-10.0f;
		fVslider8 = (float)-10.0f;
		fVslider9 = (float)-10.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec10[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec9[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec8[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec7[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec5[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec4[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec3[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec2[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec1[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec0[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec11[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec24[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec23[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec22[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec1[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec21[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec20[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec19[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec17[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec16[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec15[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec14[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec13[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec12[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec25[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec37[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec36[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec35[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec2[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec34[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec33[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec32[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec31[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec30[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec29[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec28[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec27[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec26[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec38[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec49[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec48[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec47[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec3[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec46[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec45[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec44[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec43[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec42[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec41[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec40[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec39[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec50[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec60[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec59[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec58[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fVec4[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec57[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec56[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec55[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec54[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec53[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec52[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec51[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec61[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec70[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec69[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec68[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fVec5[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec67[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec66[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec65[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec64[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec63[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec62[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec71[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec79[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec78[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec77[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fVec6[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fRec76[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec75[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec74[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec73[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec72[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec80[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec87[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec86[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec85[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fVec7[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec84[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec83[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec82[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec81[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec88[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec94[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec93[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec92[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fVec8[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec91[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec90[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec89[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec95[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec98[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec97[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec96[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec99[l108] = 0.0f;
			
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
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openVerticalBox("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the filter-bank has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider9", "1", "");
		ui_interface.declare("fVslider9", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider9", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider8", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider7", "3", "");
		ui_interface.declare("fVslider7", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider7", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider6", "4", "");
		ui_interface.declare("fVslider6", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider6", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider5", "5", "");
		ui_interface.declare("fVslider5", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider4", "6", "");
		ui_interface.declare("fVslider4", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider4", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider3", "7", "");
		ui_interface.declare("fVslider3", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider3", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider2", "8", "");
		ui_interface.declare("fVslider2", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider2", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider1", "9", "");
		ui_interface.declare("fVslider1", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider1", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider0", "10", "");
		ui_interface.declare("fVslider0", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		int iSlow0 = (int)fCheckbox0;
		float fSlow1 = (0.00100000005f * fVslider0);
		float fSlow2 = (0.00100000005f * fVslider1);
		float fSlow3 = (0.00100000005f * fVslider2);
		float fSlow4 = (0.00100000005f * fVslider3);
		float fSlow5 = (0.00100000005f * fVslider4);
		float fSlow6 = (0.00100000005f * fVslider5);
		float fSlow7 = (0.00100000005f * fVslider6);
		float fSlow8 = (0.00100000005f * fVslider7);
		float fSlow9 = (0.00100000005f * fVslider8);
		float fSlow10 = (0.00100000005f * fVslider9);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = input0[i];
			float fTemp1 = (((iSlow0==0)?true:false)?0.0f:fTemp0);
			fVec0[0] = fTemp1;
			fRec10[0] = ((fConst9 * fRec10[1]) + (fConst10 * ((fConst2 * fTemp1) + (fConst11 * fVec0[1]))));
			fRec9[0] = (fRec10[0] - (fConst7 * ((fConst12 * fRec9[1]) + (fConst13 * fRec9[2]))));
			fRec8[0] = ((fConst7 * (((fConst5 * fRec9[0]) + (fConst6 * fRec9[1])) + (fConst5 * fRec9[2]))) - (fConst4 * ((fConst12 * fRec8[1]) + (fConst14 * fRec8[2]))));
			float fTemp2 = (fConst20 * fRec7[1]);
			fRec7[0] = ((fConst4 * (((fConst6 * fRec8[1]) + (fConst5 * fRec8[0])) + (fConst5 * fRec8[2]))) - (fConst17 * ((fConst18 * fRec7[2]) + fTemp2)));
			float fTemp3 = (fConst26 * fRec6[1]);
			fRec6[0] = ((fRec7[2] + (fConst17 * (fTemp2 + (fConst18 * fRec7[0])))) - (fConst23 * ((fConst24 * fRec6[2]) + fTemp3)));
			float fTemp4 = (fConst32 * fRec5[1]);
			fRec5[0] = ((fRec6[2] + (fConst23 * (fTemp3 + (fConst24 * fRec6[0])))) - (fConst29 * ((fConst30 * fRec5[2]) + fTemp4)));
			float fTemp5 = (fConst38 * fRec4[1]);
			fRec4[0] = ((fRec5[2] + (fConst29 * (fTemp4 + (fConst30 * fRec5[0])))) - (fConst35 * ((fConst36 * fRec4[2]) + fTemp5)));
			float fTemp6 = (fConst44 * fRec3[1]);
			fRec3[0] = ((fRec4[2] + (fConst35 * (fTemp5 + (fConst36 * fRec4[0])))) - (fConst41 * ((fConst42 * fRec3[2]) + fTemp6)));
			float fTemp7 = (fConst50 * fRec2[1]);
			fRec2[0] = ((fRec3[2] + (fConst41 * (fTemp6 + (fConst42 * fRec3[0])))) - (fConst47 * ((fConst48 * fRec2[2]) + fTemp7)));
			float fTemp8 = (fConst56 * fRec1[1]);
			fRec1[0] = ((fRec2[2] + (fConst47 * (fTemp7 + (fConst48 * fRec2[0])))) - (fConst53 * ((fConst54 * fRec1[2]) + fTemp8)));
			float fTemp9 = (fConst62 * fRec0[1]);
			fRec0[0] = ((fRec1[2] + (fConst53 * (fTemp8 + (fConst54 * fRec1[0])))) - (fConst59 * ((fConst60 * fRec0[2]) + fTemp9)));
			fRec11[0] = (fSlow1 + (0.999000013f * fRec11[1]));
			fRec24[0] = ((fConst9 * fRec24[1]) + (fConst10 * (fTemp1 + fVec0[1])));
			fRec23[0] = (fRec24[0] - (fConst7 * ((fConst12 * fRec23[1]) + (fConst13 * fRec23[2]))));
			fRec22[0] = ((fConst7 * (fRec23[2] + (fRec23[0] + (2.0f * fRec23[1])))) - (fConst4 * ((fConst12 * fRec22[1]) + (fConst14 * fRec22[2]))));
			float fTemp10 = (fRec22[2] + (fRec22[0] + (2.0f * fRec22[1])));
			fVec1[0] = fTemp10;
			fRec21[0] = ((fConst68 * fRec21[1]) + (fConst69 * ((fConst58 * fTemp10) + (fConst70 * fVec1[1]))));
			fRec20[0] = (fRec21[0] - (fConst66 * ((fConst62 * fRec20[1]) + (fConst71 * fRec20[2]))));
			fRec19[0] = ((fConst66 * (((fConst61 * fRec20[0]) + (fConst65 * fRec20[1])) + (fConst61 * fRec20[2]))) - (fConst64 * ((fConst62 * fRec19[1]) + (fConst72 * fRec19[2]))));
			float fTemp11 = (fConst20 * fRec18[1]);
			fRec18[0] = ((fConst64 * (((fConst65 * fRec19[1]) + (fConst61 * fRec19[0])) + (fConst61 * fRec19[2]))) - (fConst17 * (fTemp11 + (fConst18 * fRec18[2]))));
			float fTemp12 = (fConst26 * fRec17[1]);
			fRec17[0] = ((fRec18[2] + (fConst17 * (fTemp11 + (fConst18 * fRec18[0])))) - (fConst23 * (fTemp12 + (fConst24 * fRec17[2]))));
			float fTemp13 = (fConst32 * fRec16[1]);
			fRec16[0] = ((fRec17[2] + (fConst23 * (fTemp12 + (fConst24 * fRec17[0])))) - (fConst29 * (fTemp13 + (fConst30 * fRec16[2]))));
			float fTemp14 = (fConst38 * fRec15[1]);
			fRec15[0] = ((fRec16[2] + (fConst29 * (fTemp13 + (fConst30 * fRec16[0])))) - (fConst35 * (fTemp14 + (fConst36 * fRec15[2]))));
			float fTemp15 = (fConst44 * fRec14[1]);
			fRec14[0] = ((fRec15[2] + (fConst35 * (fTemp14 + (fConst36 * fRec15[0])))) - (fConst41 * (fTemp15 + (fConst42 * fRec14[2]))));
			float fTemp16 = (fConst50 * fRec13[1]);
			fRec13[0] = ((fRec14[2] + (fConst41 * (fTemp15 + (fConst42 * fRec14[0])))) - (fConst47 * (fTemp16 + (fConst48 * fRec13[2]))));
			float fTemp17 = (fConst56 * fRec12[1]);
			fRec12[0] = ((fRec13[2] + (fConst47 * (fTemp16 + (fConst48 * fRec13[0])))) - (fConst53 * (fTemp17 + (fConst54 * fRec12[2]))));
			fRec25[0] = (fSlow2 + (0.999000013f * fRec25[1]));
			fRec37[0] = ((fConst68 * fRec37[1]) + (fConst69 * (fTemp10 + fVec1[1])));
			fRec36[0] = (fRec37[0] - (fConst66 * ((fConst62 * fRec36[1]) + (fConst71 * fRec36[2]))));
			fRec35[0] = ((fConst66 * (fRec36[2] + (fRec36[0] + (2.0f * fRec36[1])))) - (fConst64 * ((fConst62 * fRec35[1]) + (fConst72 * fRec35[2]))));
			float fTemp18 = (fRec35[2] + (fRec35[0] + (2.0f * fRec35[1])));
			fVec2[0] = fTemp18;
			fRec34[0] = ((fConst78 * fRec34[1]) + (fConst79 * ((fConst52 * fTemp18) + (fConst80 * fVec2[1]))));
			fRec33[0] = (fRec34[0] - (fConst76 * ((fConst56 * fRec33[1]) + (fConst81 * fRec33[2]))));
			fRec32[0] = ((fConst76 * (((fConst55 * fRec33[0]) + (fConst75 * fRec33[1])) + (fConst55 * fRec33[2]))) - (fConst74 * ((fConst56 * fRec32[1]) + (fConst82 * fRec32[2]))));
			float fTemp19 = (fConst20 * fRec31[1]);
			fRec31[0] = ((fConst74 * (((fConst75 * fRec32[1]) + (fConst55 * fRec32[0])) + (fConst55 * fRec32[2]))) - (fConst17 * (fTemp19 + (fConst18 * fRec31[2]))));
			float fTemp20 = (fConst26 * fRec30[1]);
			fRec30[0] = ((fRec31[2] + (fConst17 * (fTemp19 + (fConst18 * fRec31[0])))) - (fConst23 * (fTemp20 + (fConst24 * fRec30[2]))));
			float fTemp21 = (fConst32 * fRec29[1]);
			fRec29[0] = ((fRec30[2] + (fConst23 * (fTemp20 + (fConst24 * fRec30[0])))) - (fConst29 * (fTemp21 + (fConst30 * fRec29[2]))));
			float fTemp22 = (fConst38 * fRec28[1]);
			fRec28[0] = ((fRec29[2] + (fConst29 * (fTemp21 + (fConst30 * fRec29[0])))) - (fConst35 * (fTemp22 + (fConst36 * fRec28[2]))));
			float fTemp23 = (fConst44 * fRec27[1]);
			fRec27[0] = ((fRec28[2] + (fConst35 * (fTemp22 + (fConst36 * fRec28[0])))) - (fConst41 * (fTemp23 + (fConst42 * fRec27[2]))));
			float fTemp24 = (fConst50 * fRec26[1]);
			fRec26[0] = ((fRec27[2] + (fConst41 * (fTemp23 + (fConst42 * fRec27[0])))) - (fConst47 * (fTemp24 + (fConst48 * fRec26[2]))));
			fRec38[0] = (fSlow3 + (0.999000013f * fRec38[1]));
			fRec49[0] = ((fConst78 * fRec49[1]) + (fConst79 * (fTemp18 + fVec2[1])));
			fRec48[0] = (fRec49[0] - (fConst76 * ((fConst56 * fRec48[1]) + (fConst81 * fRec48[2]))));
			fRec47[0] = ((fConst76 * (fRec48[2] + (fRec48[0] + (2.0f * fRec48[1])))) - (fConst74 * ((fConst56 * fRec47[1]) + (fConst82 * fRec47[2]))));
			float fTemp25 = (fRec47[2] + (fRec47[0] + (2.0f * fRec47[1])));
			fVec3[0] = fTemp25;
			fRec46[0] = ((fConst88 * fRec46[1]) + (fConst89 * ((fConst46 * fTemp25) + (fConst90 * fVec3[1]))));
			fRec45[0] = (fRec46[0] - (fConst86 * ((fConst50 * fRec45[1]) + (fConst91 * fRec45[2]))));
			fRec44[0] = ((fConst86 * (((fConst49 * fRec45[0]) + (fConst85 * fRec45[1])) + (fConst49 * fRec45[2]))) - (fConst84 * ((fConst50 * fRec44[1]) + (fConst92 * fRec44[2]))));
			float fTemp26 = (fConst20 * fRec43[1]);
			fRec43[0] = ((fConst84 * (((fConst85 * fRec44[1]) + (fConst49 * fRec44[0])) + (fConst49 * fRec44[2]))) - (fConst17 * (fTemp26 + (fConst18 * fRec43[2]))));
			float fTemp27 = (fConst26 * fRec42[1]);
			fRec42[0] = ((fRec43[2] + (fConst17 * (fTemp26 + (fConst18 * fRec43[0])))) - (fConst23 * (fTemp27 + (fConst24 * fRec42[2]))));
			float fTemp28 = (fConst32 * fRec41[1]);
			fRec41[0] = ((fRec42[2] + (fConst23 * (fTemp27 + (fConst24 * fRec42[0])))) - (fConst29 * (fTemp28 + (fConst30 * fRec41[2]))));
			float fTemp29 = (fConst38 * fRec40[1]);
			fRec40[0] = ((fRec41[2] + (fConst29 * (fTemp28 + (fConst30 * fRec41[0])))) - (fConst35 * (fTemp29 + (fConst36 * fRec40[2]))));
			float fTemp30 = (fConst44 * fRec39[1]);
			fRec39[0] = ((fRec40[2] + (fConst35 * (fTemp29 + (fConst36 * fRec40[0])))) - (fConst41 * (fTemp30 + (fConst42 * fRec39[2]))));
			fRec50[0] = (fSlow4 + (0.999000013f * fRec50[1]));
			fRec60[0] = ((fConst88 * fRec60[1]) + (fConst89 * (fTemp25 + fVec3[1])));
			fRec59[0] = (fRec60[0] - (fConst86 * ((fConst50 * fRec59[1]) + (fConst91 * fRec59[2]))));
			fRec58[0] = ((fConst86 * (fRec59[2] + (fRec59[0] + (2.0f * fRec59[1])))) - (fConst84 * ((fConst50 * fRec58[1]) + (fConst92 * fRec58[2]))));
			float fTemp31 = (fRec58[2] + (fRec58[0] + (2.0f * fRec58[1])));
			fVec4[0] = fTemp31;
			fRec57[0] = ((fConst98 * fRec57[1]) + (fConst99 * ((fConst40 * fTemp31) + (fConst100 * fVec4[1]))));
			fRec56[0] = (fRec57[0] - (fConst96 * ((fConst44 * fRec56[1]) + (fConst101 * fRec56[2]))));
			fRec55[0] = ((fConst96 * (((fConst43 * fRec56[0]) + (fConst95 * fRec56[1])) + (fConst43 * fRec56[2]))) - (fConst94 * ((fConst44 * fRec55[1]) + (fConst102 * fRec55[2]))));
			float fTemp32 = (fConst20 * fRec54[1]);
			fRec54[0] = ((fConst94 * (((fConst95 * fRec55[1]) + (fConst43 * fRec55[0])) + (fConst43 * fRec55[2]))) - (fConst17 * (fTemp32 + (fConst18 * fRec54[2]))));
			float fTemp33 = (fConst26 * fRec53[1]);
			fRec53[0] = ((fRec54[2] + (fConst17 * (fTemp32 + (fConst18 * fRec54[0])))) - (fConst23 * (fTemp33 + (fConst24 * fRec53[2]))));
			float fTemp34 = (fConst32 * fRec52[1]);
			fRec52[0] = ((fRec53[2] + (fConst23 * (fTemp33 + (fConst24 * fRec53[0])))) - (fConst29 * (fTemp34 + (fConst30 * fRec52[2]))));
			float fTemp35 = (fConst38 * fRec51[1]);
			fRec51[0] = ((fRec52[2] + (fConst29 * (fTemp34 + (fConst30 * fRec52[0])))) - (fConst35 * (fTemp35 + (fConst36 * fRec51[2]))));
			fRec61[0] = (fSlow5 + (0.999000013f * fRec61[1]));
			fRec70[0] = ((fConst98 * fRec70[1]) + (fConst99 * (fTemp31 + fVec4[1])));
			fRec69[0] = (fRec70[0] - (fConst96 * ((fConst44 * fRec69[1]) + (fConst101 * fRec69[2]))));
			fRec68[0] = ((fConst96 * (fRec69[2] + (fRec69[0] + (2.0f * fRec69[1])))) - (fConst94 * ((fConst44 * fRec68[1]) + (fConst102 * fRec68[2]))));
			float fTemp36 = (fRec68[2] + (fRec68[0] + (2.0f * fRec68[1])));
			fVec5[0] = fTemp36;
			fRec67[0] = ((fConst108 * fRec67[1]) + (fConst109 * ((fConst34 * fTemp36) + (fConst110 * fVec5[1]))));
			fRec66[0] = (fRec67[0] - (fConst106 * ((fConst38 * fRec66[1]) + (fConst111 * fRec66[2]))));
			fRec65[0] = ((fConst106 * (((fConst37 * fRec66[0]) + (fConst105 * fRec66[1])) + (fConst37 * fRec66[2]))) - (fConst104 * ((fConst38 * fRec65[1]) + (fConst112 * fRec65[2]))));
			float fTemp37 = (fConst20 * fRec64[1]);
			fRec64[0] = ((fConst104 * (((fConst105 * fRec65[1]) + (fConst37 * fRec65[0])) + (fConst37 * fRec65[2]))) - (fConst17 * (fTemp37 + (fConst18 * fRec64[2]))));
			float fTemp38 = (fConst26 * fRec63[1]);
			fRec63[0] = ((fRec64[2] + (fConst17 * (fTemp37 + (fConst18 * fRec64[0])))) - (fConst23 * (fTemp38 + (fConst24 * fRec63[2]))));
			float fTemp39 = (fConst32 * fRec62[1]);
			fRec62[0] = ((fRec63[2] + (fConst23 * (fTemp38 + (fConst24 * fRec63[0])))) - (fConst29 * (fTemp39 + (fConst30 * fRec62[2]))));
			fRec71[0] = (fSlow6 + (0.999000013f * fRec71[1]));
			fRec79[0] = ((fConst108 * fRec79[1]) + (fConst109 * (fTemp36 + fVec5[1])));
			fRec78[0] = (fRec79[0] - (fConst106 * ((fConst38 * fRec78[1]) + (fConst111 * fRec78[2]))));
			fRec77[0] = ((fConst106 * (fRec78[2] + (fRec78[0] + (2.0f * fRec78[1])))) - (fConst104 * ((fConst38 * fRec77[1]) + (fConst112 * fRec77[2]))));
			float fTemp40 = (fRec77[2] + (fRec77[0] + (2.0f * fRec77[1])));
			fVec6[0] = fTemp40;
			fRec76[0] = ((fConst118 * fRec76[1]) + (fConst119 * ((fConst28 * fTemp40) + (fConst120 * fVec6[1]))));
			fRec75[0] = (fRec76[0] - (fConst116 * ((fConst32 * fRec75[1]) + (fConst121 * fRec75[2]))));
			fRec74[0] = ((fConst116 * (((fConst31 * fRec75[0]) + (fConst115 * fRec75[1])) + (fConst31 * fRec75[2]))) - (fConst114 * ((fConst32 * fRec74[1]) + (fConst122 * fRec74[2]))));
			float fTemp41 = (fConst20 * fRec73[1]);
			fRec73[0] = ((fConst114 * (((fConst115 * fRec74[1]) + (fConst31 * fRec74[0])) + (fConst31 * fRec74[2]))) - (fConst17 * (fTemp41 + (fConst18 * fRec73[2]))));
			float fTemp42 = (fConst26 * fRec72[1]);
			fRec72[0] = ((fRec73[2] + (fConst17 * (fTemp41 + (fConst18 * fRec73[0])))) - (fConst23 * (fTemp42 + (fConst24 * fRec72[2]))));
			fRec80[0] = (fSlow7 + (0.999000013f * fRec80[1]));
			fRec87[0] = ((fConst118 * fRec87[1]) + (fConst119 * (fTemp40 + fVec6[1])));
			fRec86[0] = (fRec87[0] - (fConst116 * ((fConst32 * fRec86[1]) + (fConst121 * fRec86[2]))));
			fRec85[0] = ((fConst116 * (fRec86[2] + (fRec86[0] + (2.0f * fRec86[1])))) - (fConst114 * ((fConst32 * fRec85[1]) + (fConst122 * fRec85[2]))));
			float fTemp43 = (fRec85[2] + (fRec85[0] + (2.0f * fRec85[1])));
			fVec7[0] = fTemp43;
			fRec84[0] = ((fConst128 * fRec84[1]) + (fConst129 * ((fConst22 * fTemp43) + (fConst130 * fVec7[1]))));
			fRec83[0] = (fRec84[0] - (fConst126 * ((fConst26 * fRec83[1]) + (fConst131 * fRec83[2]))));
			fRec82[0] = ((fConst126 * (((fConst25 * fRec83[0]) + (fConst125 * fRec83[1])) + (fConst25 * fRec83[2]))) - (fConst124 * ((fConst26 * fRec82[1]) + (fConst132 * fRec82[2]))));
			float fTemp44 = (fConst20 * fRec81[1]);
			fRec81[0] = ((fConst124 * (((fConst125 * fRec82[1]) + (fConst25 * fRec82[0])) + (fConst25 * fRec82[2]))) - (fConst17 * (fTemp44 + (fConst18 * fRec81[2]))));
			fRec88[0] = (fSlow8 + (0.999000013f * fRec88[1]));
			fRec94[0] = ((fConst128 * fRec94[1]) + (fConst129 * (fTemp43 + fVec7[1])));
			fRec93[0] = (fRec94[0] - (fConst126 * ((fConst26 * fRec93[1]) + (fConst131 * fRec93[2]))));
			fRec92[0] = ((fConst126 * (fRec93[2] + (fRec93[0] + (2.0f * fRec93[1])))) - (fConst124 * ((fConst26 * fRec92[1]) + (fConst132 * fRec92[2]))));
			float fTemp45 = (fRec92[2] + (fRec92[0] + (2.0f * fRec92[1])));
			fVec8[0] = fTemp45;
			fRec91[0] = ((fConst137 * fRec91[1]) + (fConst138 * ((fConst16 * fTemp45) + (fConst139 * fVec8[1]))));
			fRec90[0] = (fRec91[0] - (fConst135 * ((fConst20 * fRec90[1]) + (fConst140 * fRec90[2]))));
			fRec89[0] = ((fConst135 * (((fConst19 * fRec90[0]) + (fConst134 * fRec90[1])) + (fConst19 * fRec90[2]))) - (fConst133 * ((fConst20 * fRec89[1]) + (fConst141 * fRec89[2]))));
			fRec95[0] = (fSlow9 + (0.999000013f * fRec95[1]));
			fRec98[0] = ((fConst137 * fRec98[1]) + (fConst138 * (fTemp45 + fVec8[1])));
			fRec97[0] = (fRec98[0] - (fConst135 * ((fConst20 * fRec97[1]) + (fConst140 * fRec97[2]))));
			fRec96[0] = ((fConst135 * (fRec97[2] + (fRec97[0] + (2.0f * fRec97[1])))) - (fConst133 * ((fConst20 * fRec96[1]) + (fConst141 * fRec96[2]))));
			fRec99[0] = (fSlow10 + (0.999000013f * fRec99[1]));
			output0[i] = (((iSlow0==0)?true:false)?fTemp0:((((((((((fRec0[2] + (fConst59 * (fTemp9 + (fConst60 * fRec0[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec11[0]))) + ((fRec12[2] + (fConst53 * (fTemp17 + (fConst54 * fRec12[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec25[0])))) + ((fRec26[2] + (fConst47 * (fTemp24 + (fConst48 * fRec26[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec38[0])))) + ((fRec39[2] + (fConst41 * (fTemp30 + (fConst42 * fRec39[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec50[0])))) + ((fRec51[2] + (fConst35 * (fTemp35 + (fConst36 * fRec51[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec61[0])))) + ((fRec62[2] + (fConst29 * (fTemp39 + (fConst30 * fRec62[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec71[0])))) + ((fRec72[2] + (fConst23 * (fTemp42 + (fConst24 * fRec72[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec80[0])))) + ((fRec81[2] + (fConst17 * (fTemp44 + (fConst18 * fRec81[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec88[0])))) + (fConst133 * (((((fConst134 * fRec89[1]) + (fConst19 * fRec89[0])) + (fConst19 * fRec89[2])) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec95[0]))) + ((fRec96[2] + (fRec96[0] + (2.0f * fRec96[1]))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec99[0])))))));
			fVec0[1] = fVec0[0];
			fRec10[1] = fRec10[0];
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
			fRec11[1] = fRec11[0];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fVec1[1] = fVec1[0];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec25[1] = fRec25[0];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fVec2[1] = fVec2[0];
			fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec38[1] = fRec38[0];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fVec3[1] = fVec3[0];
			fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec50[1] = fRec50[0];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fVec4[1] = fVec4[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec61[1] = fRec61[0];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fVec5[1] = fVec5[0];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec71[1] = fRec71[0];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fVec6[1] = fVec6[0];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec80[1] = fRec80[0];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fVec7[1] = fVec7[0];
			fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec88[1] = fRec88[0];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fVec8[1] = fVec8[0];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec95[1] = fRec95[0];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec99[1] = fRec99[0];
			
		}
		
	}
	
};

