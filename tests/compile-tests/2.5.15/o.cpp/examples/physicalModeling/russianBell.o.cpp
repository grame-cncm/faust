//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "RussianChurchBell"
//
// Code generated with Faust 2.5.15 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif

// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		static float 	fWave0[350];
		int 	idxfWave0;
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			idxfWave0 = 0;
			fTempPerm0 = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				fTempPerm0 = fWave0[idxfWave0];
				output[i] = fTempPerm0;
				// post processing
				idxfWave0 = (idxfWave0 + 1) % 350;
			}
		}
	};


	static float 	ftbl0[350];
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	int 	iRec3[2];
	float 	fConst6;
	float 	fConst7;
	float 	fRec2[3];
	float 	fConst8;
	float 	fRec1[3];
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	float 	fConst9;
	FAUSTFLOAT 	fslider2;
	float 	fVec1[2];
	float 	fRec4[2];
	float 	fConst10;
	int 	iTempPerm1;
	float 	fConst11;
	float 	fTempPerm2;
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	float 	fRec0[3];
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fRec5[3];
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fRec6[3];
	float 	fConst21;
	float 	fConst22;
	float 	fConst23;
	float 	fRec7[3];
	float 	fConst24;
	float 	fConst25;
	float 	fConst26;
	float 	fRec8[3];
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fRec9[3];
	float 	fConst30;
	float 	fConst31;
	float 	fConst32;
	float 	fRec10[3];
	float 	fConst33;
	float 	fConst34;
	float 	fConst35;
	float 	fRec11[3];
	float 	fConst36;
	float 	fConst37;
	float 	fConst38;
	float 	fRec12[3];
	float 	fConst39;
	float 	fConst40;
	float 	fConst41;
	float 	fRec13[3];
	float 	fConst42;
	float 	fConst43;
	float 	fConst44;
	float 	fRec14[3];
	float 	fConst45;
	float 	fConst46;
	float 	fConst47;
	float 	fRec15[3];
	float 	fConst48;
	float 	fConst49;
	float 	fConst50;
	float 	fRec16[3];
	float 	fConst51;
	float 	fConst52;
	float 	fConst53;
	float 	fRec17[3];
	float 	fConst54;
	float 	fConst55;
	float 	fConst56;
	float 	fRec18[3];
	float 	fConst57;
	float 	fConst58;
	float 	fConst59;
	float 	fRec19[3];
	float 	fConst60;
	float 	fConst61;
	float 	fConst62;
	float 	fRec20[3];
	float 	fConst63;
	float 	fConst64;
	float 	fConst65;
	float 	fRec21[3];
	float 	fConst66;
	float 	fConst67;
	float 	fConst68;
	float 	fRec22[3];
	float 	fConst69;
	float 	fConst70;
	float 	fConst71;
	float 	fRec23[3];
	float 	fConst72;
	float 	fConst73;
	float 	fConst74;
	float 	fRec24[3];
	float 	fConst75;
	float 	fConst76;
	float 	fConst77;
	float 	fRec25[3];
	float 	fConst78;
	float 	fConst79;
	float 	fConst80;
	float 	fRec26[3];
	float 	fConst81;
	float 	fConst82;
	float 	fConst83;
	float 	fRec27[3];
	float 	fConst84;
	float 	fConst85;
	float 	fConst86;
	float 	fRec28[3];
	float 	fConst87;
	float 	fConst88;
	float 	fConst89;
	float 	fRec29[3];
	float 	fConst90;
	float 	fConst91;
	float 	fConst92;
	float 	fRec30[3];
	float 	fConst93;
	float 	fConst94;
	float 	fConst95;
	float 	fRec31[3];
	float 	fConst96;
	float 	fConst97;
	float 	fConst98;
	float 	fRec32[3];
	float 	fConst99;
	float 	fConst100;
	float 	fConst101;
	float 	fRec33[3];
	float 	fConst102;
	float 	fConst103;
	float 	fConst104;
	float 	fRec34[3];
	float 	fConst105;
	float 	fConst106;
	float 	fConst107;
	float 	fRec35[3];
	float 	fConst108;
	float 	fConst109;
	float 	fConst110;
	float 	fRec36[3];
	float 	fConst111;
	float 	fConst112;
	float 	fConst113;
	float 	fRec37[3];
	float 	fConst114;
	float 	fConst115;
	float 	fConst116;
	float 	fRec38[3];
	float 	fConst117;
	float 	fConst118;
	float 	fConst119;
	float 	fRec39[3];
	float 	fConst120;
	float 	fConst121;
	float 	fConst122;
	float 	fRec40[3];
	float 	fConst123;
	float 	fConst124;
	float 	fConst125;
	float 	fRec41[3];
	float 	fConst126;
	float 	fConst127;
	float 	fConst128;
	float 	fRec42[3];
	float 	fConst129;
	float 	fConst130;
	float 	fConst131;
	float 	fRec43[3];
	float 	fConst132;
	float 	fConst133;
	float 	fConst134;
	float 	fRec44[3];
	float 	fConst135;
	float 	fConst136;
	float 	fConst137;
	float 	fRec45[3];
	float 	fConst138;
	float 	fConst139;
	float 	fConst140;
	float 	fRec46[3];
	float 	fConst141;
	float 	fConst142;
	float 	fConst143;
	float 	fRec47[3];
	float 	fConst144;
	float 	fConst145;
	float 	fConst146;
	float 	fRec48[3];
	float 	fConst147;
	float 	fConst148;
	float 	fConst149;
	float 	fRec49[3];
	float 	fConst150;
	float 	fConst151;
	float 	fConst152;
	float 	fRec50[3];
	float 	fConst153;
	float 	fConst154;
	float 	fConst155;
	float 	fRec51[3];
	float 	fConst156;
	float 	fConst157;
	float 	fConst158;
	float 	fRec52[3];
	float 	fConst159;
	float 	fConst160;
	float 	fConst161;
	float 	fRec53[3];
	float 	fTempPerm3;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("description", "Russian church bell physical model.");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "RussianChurchBell");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(350,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fConst2 = tanf((31.415926535897931f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 1.4142135623730949f) / fConst2) + 1));
		fConst5 = (1.0f / faustpower<2>(fConst2));
		fConst6 = (((fConst3 + -1.4142135623730949f) / fConst2) + 1);
		fConst7 = (2 * (1 - fConst5));
		fConst8 = (2 * (0 - fConst5));
		fConst9 = (0.0040000000000000001f * fConst0);
		fConst10 = (0.002f * fConst0);
		iTempPerm1 = 0;
		fConst11 = (500.0f / fConst0);
		fTempPerm2 = 0;
		fConst12 = powf(0.001f,(1.0f / float((20.890153741822246f * fConst0))));
		fConst13 = ((0 - (2 * fConst12)) * cosf((857.59824576224901f / fConst0)));
		fConst14 = faustpower<2>(fConst12);
		fConst15 = powf(0.001f,(1.0f / float((20.860672702556624f * fConst0))));
		fConst16 = ((0 - (2 * fConst15)) * cosf((860.74612160114577f / fConst0)));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((14.477914648462914f * fConst0))));
		fConst19 = ((0 - (2 * fConst18)) * cosf((1627.0811007766115f / fConst0)));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((14.41065897924317f * fConst0))));
		fConst22 = ((0 - (2 * fConst21)) * cosf((1636.2608345104006f / fConst0)));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((11.984111166533006f * fConst0))));
		fConst25 = ((0 - (2 * fConst24)) * cosf((1988.5590346839599f / fConst0)));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((11.90615898267875f * fConst0))));
		fConst28 = ((0 - (2 * fConst27)) * cosf((2000.6353168443593f / fConst0)));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((9.1066165639380277f * fConst0))));
		fConst31 = ((0 - (2 * fConst30)) * cosf((2474.6450996032941f / fConst0)));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((9.1033338027354453f * fConst0))));
		fConst34 = ((0 - (2 * fConst33)) * cosf((2475.254568578091f / fConst0)));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((7.1991184444136032f * fConst0))));
		fConst37 = ((0 - (2 * fConst36)) * cosf((2856.8198459124928f / fConst0)));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((6.8345816271582756f * fConst0))));
		fConst40 = ((0 - (2 * fConst39)) * cosf((2937.3451488093065f / fConst0)));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((5.8743132838871066f * fConst0))));
		fConst43 = ((0 - (2 * fConst42)) * cosf((3164.1744215837966f / fConst0)));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((5.8732267878899194f * fConst0))));
		fConst46 = ((0 - (2 * fConst45)) * cosf((3164.4445985520051f / fConst0)));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((5.2212547669187543f * fConst0))));
		fConst49 = ((0 - (2 * fConst48)) * cosf((3332.9784780464834f / fConst0)));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((5.2075780140566525f * fConst0))));
		fConst52 = ((0 - (2 * fConst51)) * cosf((3336.6604246364909f / fConst0)));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((4.975274503795533f * fConst0))));
		fConst55 = ((0 - (2 * fConst54)) * cosf((3400.2085608333045f / fConst0)));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((4.8630737850904886f * fConst0))));
		fConst58 = ((0 - (2 * fConst57)) * cosf((3431.6119209985886f / fConst0)));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((4.1808604570806223f * fConst0))));
		fConst61 = ((0 - (2 * fConst60)) * cosf((3633.7859746277063f / fConst0)));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((4.1501573244598138f * fConst0))));
		fConst64 = ((0 - (2 * fConst63)) * cosf((3643.3866817770768f / fConst0)));
		fConst65 = faustpower<2>(fConst63);
		fConst66 = powf(0.001f,(1.0f / float((2.7417928931699174f * fConst0))));
		fConst67 = ((0 - (2 * fConst66)) * cosf((4147.0656655565135f / fConst0)));
		fConst68 = faustpower<2>(fConst66);
		fConst69 = powf(0.001f,(1.0f / float((2.0708552216160001f * fConst0))));
		fConst70 = ((0 - (2 * fConst69)) * cosf((4450.6314804875883f / fConst0)));
		fConst71 = faustpower<2>(fConst69);
		fConst72 = powf(0.001f,(1.0f / float((1.9645956374668789f * fConst0))));
		fConst73 = ((0 - (2 * fConst72)) * cosf((4504.5097944966528f / fConst0)));
		fConst74 = faustpower<2>(fConst72);
		fConst75 = powf(0.001f,(1.0f / float((1.9607630527689446f * fConst0))));
		fConst76 = ((0 - (2 * fConst75)) * cosf((4506.488997868415f / fConst0)));
		fConst77 = faustpower<2>(fConst75);
		fConst78 = powf(0.001f,(1.0f / float((1.3309823241169609f * fConst0))));
		fConst79 = ((0 - (2 * fConst78)) * cosf((4874.740205536903f / fConst0)));
		fConst80 = faustpower<2>(fConst78);
		fConst81 = powf(0.001f,(1.0f / float((1.3288516164255231f * fConst0))));
		fConst82 = ((0 - (2 * fConst81)) * cosf((4876.1664886016333f / fConst0)));
		fConst83 = faustpower<2>(fConst81);
		fConst84 = powf(0.001f,(1.0f / float((1.2616280019462445f * fConst0))));
		fConst85 = ((0 - (2 * fConst84)) * cosf((4921.9709094909722f / fConst0)));
		fConst86 = faustpower<2>(fConst84);
		fConst87 = powf(0.001f,(1.0f / float((1.2606495322567774f * fConst0))));
		fConst88 = ((0 - (2 * fConst87)) * cosf((4922.6494935041474f / fConst0)));
		fConst89 = faustpower<2>(fConst87);
		fConst90 = powf(0.001f,(1.0f / float((1.2127038957377048f * fConst0))));
		fConst91 = ((0 - (2 * fConst90)) * cosf((4956.339933121244f / fConst0)));
		fConst92 = faustpower<2>(fConst90);
		fConst93 = powf(0.001f,(1.0f / float((1.2070901467819748f * fConst0))));
		fConst94 = ((0 - (2 * fConst93)) * cosf((4960.3423221619178f / fConst0)));
		fConst95 = faustpower<2>(fConst93);
		fConst96 = powf(0.001f,(1.0f / float((1.1138221442155232f * fConst0))));
		fConst97 = ((0 - (2 * fConst96)) * cosf((5028.7347942305669f / fConst0)));
		fConst98 = faustpower<2>(fConst96);
		fConst99 = powf(0.001f,(1.0f / float((1.0612143149644129f * fConst0))));
		fConst100 = ((0 - (2 * fConst99)) * cosf((5069.010012049589f / fConst0)));
		fConst101 = faustpower<2>(fConst99);
		fConst102 = powf(0.001f,(1.0f / float((0.59021307416752367f * fConst0))));
		fConst103 = ((0 - (2 * fConst102)) * cosf((5509.0214791113749f / fConst0)));
		fConst104 = faustpower<2>(fConst102);
		fConst105 = powf(0.001f,(1.0f / float((0.57063142210601736f * fConst0))));
		fConst106 = ((0 - (2 * fConst105)) * cosf((5531.8043090352085f / fConst0)));
		fConst107 = faustpower<2>(fConst105);
		fConst108 = powf(0.001f,(1.0f / float((0.53466152382957954f * fConst0))));
		fConst109 = ((0 - (2 * fConst108)) * cosf((5575.0514735045253f / fConst0)));
		fConst110 = faustpower<2>(fConst108);
		fConst111 = powf(0.001f,(1.0f / float((0.52994601857628443f * fConst0))));
		fConst112 = ((0 - (2 * fConst111)) * cosf((5580.8634199136659f / fConst0)));
		fConst113 = faustpower<2>(fConst111);
		fConst114 = powf(0.001f,(1.0f / float((0.39749409638261052f * fConst0))));
		fConst115 = ((0 - (2 * fConst114)) * cosf((5760.5185374018529f / fConst0)));
		fConst116 = faustpower<2>(fConst114);
		fConst117 = powf(0.001f,(1.0f / float((0.38546588630869577f * fConst0))));
		fConst118 = ((0 - (2 * fConst117)) * cosf((5778.7146420514446f / fConst0)));
		fConst119 = faustpower<2>(fConst117);
		fConst120 = powf(0.001f,(1.0f / float((0.31619333771390828f * fConst0))));
		fConst121 = ((0 - (2 * fConst120)) * cosf((5891.6548979479976f / fConst0)));
		fConst122 = faustpower<2>(fConst120);
		fConst123 = powf(0.001f,(1.0f / float((0.17550004662824115f * fConst0))));
		fConst124 = ((0 - (2 * fConst123)) * cosf((6186.4619525608632f / fConst0)));
		fConst125 = faustpower<2>(fConst123);
		fConst126 = powf(0.001f,(1.0f / float((0.051504911240661547f * fConst0))));
		fConst127 = ((0 - (2 * fConst126)) * cosf((6642.5835067502585f / fConst0)));
		fConst128 = faustpower<2>(fConst126);
		fConst129 = powf(0.001f,(1.0f / float((0.050173505399798209f * fConst0))));
		fConst130 = ((0 - (2 * fConst129)) * cosf((6650.4374883842329f / fConst0)));
		fConst131 = faustpower<2>(fConst129);
		fConst132 = powf(0.001f,(1.0f / float((0.043110960529481129f * fConst0))));
		fConst133 = ((0 - (2 * fConst132)) * cosf((6694.608281093706f / fConst0)));
		fConst134 = faustpower<2>(fConst132);
		fConst135 = powf(0.001f,(1.0f / float((0.028991622294433323f * fConst0))));
		fConst136 = ((0 - (2 * fConst135)) * cosf((6800.1029624012508f / fConst0)));
		fConst137 = faustpower<2>(fConst135);
		fConst138 = powf(0.001f,(1.0f / float((0.027792622305882937f * fConst0))));
		fConst139 = ((0 - (2 * fConst138)) * cosf((6810.5330500111695f / fConst0)));
		fConst140 = faustpower<2>(fConst138);
		fConst141 = powf(0.001f,(1.0f / float((0.025968245541453865f * fConst0))));
		fConst142 = ((0 - (2 * fConst141)) * cosf((6826.9949955159791f / fConst0)));
		fConst143 = faustpower<2>(fConst141);
		fConst144 = powf(0.001f,(1.0f / float((0.025818794897172426f * fConst0))));
		fConst145 = ((0 - (2 * fConst144)) * cosf((6828.3772962835592f / fConst0)));
		fConst146 = faustpower<2>(fConst144);
		fConst147 = powf(0.001f,(1.0f / float((0.013844131066933968f * fConst0))));
		fConst148 = ((0 - (2 * fConst147)) * cosf((6963.0259574164174f / fConst0)));
		fConst149 = faustpower<2>(fConst147);
		fConst150 = powf(0.001f,(1.0f / float((0.010575072750766266f * fConst0))));
		fConst151 = ((0 - (2 * fConst150)) * cosf((7013.102944314639f / fConst0)));
		fConst152 = faustpower<2>(fConst150);
		fConst153 = powf(0.001f,(1.0f / float((0.0024363627201956423f * fConst0))));
		fConst154 = ((0 - (2 * fConst153)) * cosf((7219.3799179493444f / fConst0)));
		fConst155 = faustpower<2>(fConst153);
		fConst156 = powf(0.001f,(1.0f / float((0.0022262877592101656f * fConst0))));
		fConst157 = ((0 - (2 * fConst156)) * cosf((7229.0560233224005f / fConst0)));
		fConst158 = faustpower<2>(fConst156);
		fConst159 = powf(0.001f,(1.0f / float((5.5008954202353615e-08f * fConst0))));
		fConst160 = ((0 - (2 * fConst159)) * cosf((7536.9321033742008f / fConst0)));
		fConst161 = faustpower<2>(fConst159);
		fTempPerm3 = 0;
	}
	virtual void instanceResetUserInterface() {
		fentry0 = 0.0f;
		fslider0 = 1.0f;
		fslider1 = 6500.0f;
		fbutton0 = 0.0;
		fslider2 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec15[i] = 0;
		for (int i=0; i<3; i++) fRec16[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		for (int i=0; i<3; i++) fRec18[i] = 0;
		for (int i=0; i<3; i++) fRec19[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<3; i++) fRec21[i] = 0;
		for (int i=0; i<3; i++) fRec22[i] = 0;
		for (int i=0; i<3; i++) fRec23[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<3; i++) fRec25[i] = 0;
		for (int i=0; i<3; i++) fRec26[i] = 0;
		for (int i=0; i<3; i++) fRec27[i] = 0;
		for (int i=0; i<3; i++) fRec28[i] = 0;
		for (int i=0; i<3; i++) fRec29[i] = 0;
		for (int i=0; i<3; i++) fRec30[i] = 0;
		for (int i=0; i<3; i++) fRec31[i] = 0;
		for (int i=0; i<3; i++) fRec32[i] = 0;
		for (int i=0; i<3; i++) fRec33[i] = 0;
		for (int i=0; i<3; i++) fRec34[i] = 0;
		for (int i=0; i<3; i++) fRec35[i] = 0;
		for (int i=0; i<3; i++) fRec36[i] = 0;
		for (int i=0; i<3; i++) fRec37[i] = 0;
		for (int i=0; i<3; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fRec39[i] = 0;
		for (int i=0; i<3; i++) fRec40[i] = 0;
		for (int i=0; i<3; i++) fRec41[i] = 0;
		for (int i=0; i<3; i++) fRec42[i] = 0;
		for (int i=0; i<3; i++) fRec43[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
		for (int i=0; i<3; i++) fRec46[i] = 0;
		for (int i=0; i<3; i++) fRec47[i] = 0;
		for (int i=0; i<3; i++) fRec48[i] = 0;
		for (int i=0; i<3; i++) fRec49[i] = 0;
		for (int i=0; i<3; i++) fRec50[i] = 0;
		for (int i=0; i<3; i++) fRec51[i] = 0;
		for (int i=0; i<3; i++) fRec52[i] = 0;
		for (int i=0; i<3; i++) fRec53[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("russianBell");
		ui_interface->declare(&fentry0, "0", "");
		ui_interface->addNumEntry("strikePosition", &fentry0, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->addHorizontalSlider("strikeCutOff", &fslider1, 6500.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fslider2, "2", "");
		ui_interface->addHorizontalSlider("strikeSharpness", &fslider2, 0.5f, 0.01f, 5.0f, 0.01f);
		ui_interface->declare(&fslider0, "3", "");
		ui_interface->addHorizontalSlider("gain", &fslider0, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fbutton0, "4", "");
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = (50 * int(float(fentry0)));
		float 	fSlow1 = ftbl0[int(iSlow0)];
		float 	fSlow2 = tanf((fConst1 * float(fslider1)));
		float 	fSlow3 = (1.0f / fSlow2);
		float 	fSlow4 = (((fSlow3 + 1.4142135623730949f) / fSlow2) + 1);
		float 	fSlow5 = (float(fslider0) / fSlow4);
		float 	fSlow6 = (1.0f / fSlow4);
		float 	fSlow7 = (2 * (1 - (1.0f / faustpower<2>(fSlow2))));
		float 	fSlow8 = (((fSlow3 + -1.4142135623730949f) / fSlow2) + 1);
		float 	fSlow9 = float(fbutton0);
		float 	fSlow10 = float(fslider2);
		float 	fSlow11 = (fConst9 * fSlow10);
		float 	fSlow12 = (fConst10 * fSlow10);
		float 	fSlow13 = (fConst11 / fSlow10);
		float 	fSlow14 = ftbl0[int((iSlow0 + 1))];
		float 	fSlow15 = ftbl0[int((iSlow0 + 2))];
		float 	fSlow16 = ftbl0[int((iSlow0 + 3))];
		float 	fSlow17 = ftbl0[int((iSlow0 + 4))];
		float 	fSlow18 = ftbl0[int((iSlow0 + 5))];
		float 	fSlow19 = ftbl0[int((iSlow0 + 6))];
		float 	fSlow20 = ftbl0[int((iSlow0 + 7))];
		float 	fSlow21 = ftbl0[int((iSlow0 + 8))];
		float 	fSlow22 = ftbl0[int((iSlow0 + 9))];
		float 	fSlow23 = ftbl0[int((iSlow0 + 10))];
		float 	fSlow24 = ftbl0[int((iSlow0 + 11))];
		float 	fSlow25 = ftbl0[int((iSlow0 + 12))];
		float 	fSlow26 = ftbl0[int((iSlow0 + 13))];
		float 	fSlow27 = ftbl0[int((iSlow0 + 14))];
		float 	fSlow28 = ftbl0[int((iSlow0 + 15))];
		float 	fSlow29 = ftbl0[int((iSlow0 + 16))];
		float 	fSlow30 = ftbl0[int((iSlow0 + 17))];
		float 	fSlow31 = ftbl0[int((iSlow0 + 18))];
		float 	fSlow32 = ftbl0[int((iSlow0 + 19))];
		float 	fSlow33 = ftbl0[int((iSlow0 + 20))];
		float 	fSlow34 = ftbl0[int((iSlow0 + 21))];
		float 	fSlow35 = ftbl0[int((iSlow0 + 22))];
		float 	fSlow36 = ftbl0[int((iSlow0 + 23))];
		float 	fSlow37 = ftbl0[int((iSlow0 + 24))];
		float 	fSlow38 = ftbl0[int((iSlow0 + 25))];
		float 	fSlow39 = ftbl0[int((iSlow0 + 26))];
		float 	fSlow40 = ftbl0[int((iSlow0 + 27))];
		float 	fSlow41 = ftbl0[int((iSlow0 + 28))];
		float 	fSlow42 = ftbl0[int((iSlow0 + 29))];
		float 	fSlow43 = ftbl0[int((iSlow0 + 30))];
		float 	fSlow44 = ftbl0[int((iSlow0 + 31))];
		float 	fSlow45 = ftbl0[int((iSlow0 + 32))];
		float 	fSlow46 = ftbl0[int((iSlow0 + 33))];
		float 	fSlow47 = ftbl0[int((iSlow0 + 34))];
		float 	fSlow48 = ftbl0[int((iSlow0 + 35))];
		float 	fSlow49 = ftbl0[int((iSlow0 + 36))];
		float 	fSlow50 = ftbl0[int((iSlow0 + 37))];
		float 	fSlow51 = ftbl0[int((iSlow0 + 38))];
		float 	fSlow52 = ftbl0[int((iSlow0 + 39))];
		float 	fSlow53 = ftbl0[int((iSlow0 + 40))];
		float 	fSlow54 = ftbl0[int((iSlow0 + 41))];
		float 	fSlow55 = ftbl0[int((iSlow0 + 42))];
		float 	fSlow56 = ftbl0[int((iSlow0 + 43))];
		float 	fSlow57 = ftbl0[int((iSlow0 + 44))];
		float 	fSlow58 = ftbl0[int((iSlow0 + 45))];
		float 	fSlow59 = ftbl0[int((iSlow0 + 46))];
		float 	fSlow60 = ftbl0[int((iSlow0 + 47))];
		float 	fSlow61 = ftbl0[int((iSlow0 + 48))];
		float 	fSlow62 = ftbl0[int((iSlow0 + 49))];
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.6566128752457969e-10f * iRec3[0]) - (fConst4 * ((fConst6 * fRec2[2]) + (fConst7 * fRec2[1]))));
			fRec1[0] = ((fConst4 * (((fConst5 * fRec2[0]) + (fConst8 * fRec2[1])) + (fConst5 * fRec2[2]))) - (fSlow6 * ((fSlow7 * fRec1[1]) + (fSlow8 * fRec1[2]))));
			fVec0[0] = fSlow9;
			fVec1[0] = fSlow10;
			fRec4[0] = ((int((((fSlow9 - fVec0[1]) > 0) > 0)))?0:min(fSlow11, ((fRec4[1] + (fConst9 * (fSlow10 - fVec1[1]))) + 1)));
			iTempPerm1 = int((fRec4[0] < fSlow12));
			fTempPerm2 = (fSlow5 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * ((iTempPerm1)?((int((fRec4[0] < 0)))?0:((iTempPerm1)?(fSlow13 * fRec4[0]):1)):((int((fRec4[0] < fSlow11)))?((fSlow13 * (0 - (fRec4[0] - fSlow12))) + 1):0))));
			fRec0[0] = (fTempPerm2 - ((fConst13 * fRec0[1]) + (fConst14 * fRec0[2])));
			fRec5[0] = (fTempPerm2 - ((fConst16 * fRec5[1]) + (fConst17 * fRec5[2])));
			fRec6[0] = (fTempPerm2 - ((fConst19 * fRec6[1]) + (fConst20 * fRec6[2])));
			fRec7[0] = (fTempPerm2 - ((fConst22 * fRec7[1]) + (fConst23 * fRec7[2])));
			fRec8[0] = (fTempPerm2 - ((fConst25 * fRec8[1]) + (fConst26 * fRec8[2])));
			fRec9[0] = (fTempPerm2 - ((fConst28 * fRec9[1]) + (fConst29 * fRec9[2])));
			fRec10[0] = (fTempPerm2 - ((fConst31 * fRec10[1]) + (fConst32 * fRec10[2])));
			fRec11[0] = (fTempPerm2 - ((fConst34 * fRec11[1]) + (fConst35 * fRec11[2])));
			fRec12[0] = (fTempPerm2 - ((fConst37 * fRec12[1]) + (fConst38 * fRec12[2])));
			fRec13[0] = (fTempPerm2 - ((fConst40 * fRec13[1]) + (fConst41 * fRec13[2])));
			fRec14[0] = (fTempPerm2 - ((fConst43 * fRec14[1]) + (fConst44 * fRec14[2])));
			fRec15[0] = (fTempPerm2 - ((fConst46 * fRec15[1]) + (fConst47 * fRec15[2])));
			fRec16[0] = (fTempPerm2 - ((fConst49 * fRec16[1]) + (fConst50 * fRec16[2])));
			fRec17[0] = (fTempPerm2 - ((fConst52 * fRec17[1]) + (fConst53 * fRec17[2])));
			fRec18[0] = (fTempPerm2 - ((fConst55 * fRec18[1]) + (fConst56 * fRec18[2])));
			fRec19[0] = (fTempPerm2 - ((fConst58 * fRec19[1]) + (fConst59 * fRec19[2])));
			fRec20[0] = (fTempPerm2 - ((fConst61 * fRec20[1]) + (fConst62 * fRec20[2])));
			fRec21[0] = (fTempPerm2 - ((fConst64 * fRec21[1]) + (fConst65 * fRec21[2])));
			fRec22[0] = (fTempPerm2 - ((fConst67 * fRec22[1]) + (fConst68 * fRec22[2])));
			fRec23[0] = (fTempPerm2 - ((fConst70 * fRec23[1]) + (fConst71 * fRec23[2])));
			fRec24[0] = (fTempPerm2 - ((fConst73 * fRec24[1]) + (fConst74 * fRec24[2])));
			fRec25[0] = (fTempPerm2 - ((fConst76 * fRec25[1]) + (fConst77 * fRec25[2])));
			fRec26[0] = (fTempPerm2 - ((fConst79 * fRec26[1]) + (fConst80 * fRec26[2])));
			fRec27[0] = (fTempPerm2 - ((fConst82 * fRec27[1]) + (fConst83 * fRec27[2])));
			fRec28[0] = (fTempPerm2 - ((fConst85 * fRec28[1]) + (fConst86 * fRec28[2])));
			fRec29[0] = (fTempPerm2 - ((fConst88 * fRec29[1]) + (fConst89 * fRec29[2])));
			fRec30[0] = (fTempPerm2 - ((fConst91 * fRec30[1]) + (fConst92 * fRec30[2])));
			fRec31[0] = (fTempPerm2 - ((fConst94 * fRec31[1]) + (fConst95 * fRec31[2])));
			fRec32[0] = (fTempPerm2 - ((fConst97 * fRec32[1]) + (fConst98 * fRec32[2])));
			fRec33[0] = (fTempPerm2 - ((fConst100 * fRec33[1]) + (fConst101 * fRec33[2])));
			fRec34[0] = (fTempPerm2 - ((fConst103 * fRec34[1]) + (fConst104 * fRec34[2])));
			fRec35[0] = (fTempPerm2 - ((fConst106 * fRec35[1]) + (fConst107 * fRec35[2])));
			fRec36[0] = (fTempPerm2 - ((fConst109 * fRec36[1]) + (fConst110 * fRec36[2])));
			fRec37[0] = (fTempPerm2 - ((fConst112 * fRec37[1]) + (fConst113 * fRec37[2])));
			fRec38[0] = (fTempPerm2 - ((fConst115 * fRec38[1]) + (fConst116 * fRec38[2])));
			fRec39[0] = (fTempPerm2 - ((fConst118 * fRec39[1]) + (fConst119 * fRec39[2])));
			fRec40[0] = (fTempPerm2 - ((fConst121 * fRec40[1]) + (fConst122 * fRec40[2])));
			fRec41[0] = (fTempPerm2 - ((fConst124 * fRec41[1]) + (fConst125 * fRec41[2])));
			fRec42[0] = (fTempPerm2 - ((fConst127 * fRec42[1]) + (fConst128 * fRec42[2])));
			fRec43[0] = (fTempPerm2 - ((fConst130 * fRec43[1]) + (fConst131 * fRec43[2])));
			fRec44[0] = (fTempPerm2 - ((fConst133 * fRec44[1]) + (fConst134 * fRec44[2])));
			fRec45[0] = (fTempPerm2 - ((fConst136 * fRec45[1]) + (fConst137 * fRec45[2])));
			fRec46[0] = (fTempPerm2 - ((fConst139 * fRec46[1]) + (fConst140 * fRec46[2])));
			fRec47[0] = (fTempPerm2 - ((fConst142 * fRec47[1]) + (fConst143 * fRec47[2])));
			fRec48[0] = (fTempPerm2 - ((fConst145 * fRec48[1]) + (fConst146 * fRec48[2])));
			fRec49[0] = (fTempPerm2 - ((fConst148 * fRec49[1]) + (fConst149 * fRec49[2])));
			fRec50[0] = (fTempPerm2 - ((fConst151 * fRec50[1]) + (fConst152 * fRec50[2])));
			fRec51[0] = (fTempPerm2 - ((fConst154 * fRec51[1]) + (fConst155 * fRec51[2])));
			fRec52[0] = (fTempPerm2 - ((fConst157 * fRec52[1]) + (fConst158 * fRec52[2])));
			fRec53[0] = (fTempPerm2 - ((fConst160 * fRec53[1]) + (fConst161 * fRec53[2])));
			fTempPerm3 = (0.02f * ((((((((((((((((((((((((((((((((((((((((((((((((((fSlow1 * (fRec0[0] - fRec0[2])) + (fSlow14 * (fRec5[0] - fRec5[2]))) + (fSlow15 * (fRec6[0] - fRec6[2]))) + (fSlow16 * (fRec7[0] - fRec7[2]))) + (fSlow17 * (fRec8[0] - fRec8[2]))) + (fSlow18 * (fRec9[0] - fRec9[2]))) + (fSlow19 * (fRec10[0] - fRec10[2]))) + (fSlow20 * (fRec11[0] - fRec11[2]))) + (fSlow21 * (fRec12[0] - fRec12[2]))) + (fSlow22 * (fRec13[0] - fRec13[2]))) + (fSlow23 * (fRec14[0] - fRec14[2]))) + (fSlow24 * (fRec15[0] - fRec15[2]))) + (fSlow25 * (fRec16[0] - fRec16[2]))) + (fSlow26 * (fRec17[0] - fRec17[2]))) + (fSlow27 * (fRec18[0] - fRec18[2]))) + (fSlow28 * (fRec19[0] - fRec19[2]))) + (fSlow29 * (fRec20[0] - fRec20[2]))) + (fSlow30 * (fRec21[0] - fRec21[2]))) + (fSlow31 * (fRec22[0] - fRec22[2]))) + (fSlow32 * (fRec23[0] - fRec23[2]))) + (fSlow33 * (fRec24[0] - fRec24[2]))) + (fSlow34 * (fRec25[0] - fRec25[2]))) + (fSlow35 * (fRec26[0] - fRec26[2]))) + (fSlow36 * (fRec27[0] - fRec27[2]))) + (fSlow37 * (fRec28[0] - fRec28[2]))) + (fSlow38 * (fRec29[0] - fRec29[2]))) + (fSlow39 * (fRec30[0] - fRec30[2]))) + (fSlow40 * (fRec31[0] - fRec31[2]))) + (fSlow41 * (fRec32[0] - fRec32[2]))) + (fSlow42 * (fRec33[0] - fRec33[2]))) + (fSlow43 * (fRec34[0] - fRec34[2]))) + (fSlow44 * (fRec35[0] - fRec35[2]))) + (fSlow45 * (fRec36[0] - fRec36[2]))) + (fSlow46 * (fRec37[0] - fRec37[2]))) + (fSlow47 * (fRec38[0] - fRec38[2]))) + (fSlow48 * (fRec39[0] - fRec39[2]))) + (fSlow49 * (fRec40[0] - fRec40[2]))) + (fSlow50 * (fRec41[0] - fRec41[2]))) + (fSlow51 * (fRec42[0] - fRec42[2]))) + (fSlow52 * (fRec43[0] - fRec43[2]))) + (fSlow53 * (fRec44[0] - fRec44[2]))) + (fSlow54 * (fRec45[0] - fRec45[2]))) + (fSlow55 * (fRec46[0] - fRec46[2]))) + (fSlow56 * (fRec47[0] - fRec47[2]))) + (fSlow57 * (fRec48[0] - fRec48[2]))) + (fSlow58 * (fRec49[0] - fRec49[2]))) + (fSlow59 * (fRec50[0] - fRec50[2]))) + (fSlow60 * (fRec51[0] - fRec51[2]))) + (fSlow61 * (fRec52[0] - fRec52[2]))) + (fSlow62 * (fRec53[0] - fRec53[2]))));
			output0[i] = (FAUSTFLOAT)fTempPerm3;
			output1[i] = (FAUSTFLOAT)fTempPerm3;
			// post processing
			fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fVec1[1] = fVec1[0];
			fVec0[1] = fVec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
		}
	}
};


float 	mydsp::SIG0::fWave0[350] = {0.92550699999999997f,0.59752000000000005f,0.096567100000000003f,0.45412000000000002f,0.98977300000000001f,0.59349799999999997f,0.51254100000000002f,0.124241f,0.70541100000000001f,0.29239599999999999f,0.67339899999999997f,0.30218099999999998f,0.026234f,0.28624899999999998f,0.55626699999999996f,1,0.25042599999999998f,0.107711f,0.42729899999999998f,0.33629500000000001f,0.61625700000000005f,0.21442f,0.084529400000000005f,0.23136300000000001f,0.52272399999999997f,0.559114f,0.34847f,0.85419699999999998f,0.83557599999999999f,0.73503600000000002f,0.28849399999999997f,0.117122f,0.40968599999999999f,0.36357499999999998f,0.48494300000000001f,0.17086200000000001f,0.42053099999999999f,0.164793f,0.233847f,0.861232f,0.21403700000000001f,0.28346199999999999f,0.173153f,0.87612199999999996f,0.60780900000000004f,0.29474499999999998f,0.14314199999999999f,0.332009f,0.49187799999999998f,0.62610399999999999f,0.96202699999999997f,0.58429799999999998f,0.21365300000000001f,0.42045199999999999f,0.81232899999999997f,0.54517199999999999f,0.38074400000000003f,0.331536f,0.38680100000000001f,0.24890899999999999f,0.68875600000000003f,0.31390400000000002f,0.37789400000000001f,0.59584599999999999f,0.41227399999999997f,0.73962600000000001f,0.54114799999999996f,0.39300499999999999f,0.65663700000000003f,0.84767199999999998f,0.93065299999999995f,0.28828900000000002f,0.40493800000000002f,0.65798900000000005f,0.76394899999999999f,0.57408499999999996f,0.28224100000000002f,1,0.42913099999999998f,0.57204900000000003f,0.73486799999999997f,0.57747700000000002f,0.52078899999999995f,0.35559299999999999f,0.89006700000000005f,0.27239099999999999f,0.44822299999999998f,0.42396899999999998f,0.392237f,0.85609100000000005f,0.058379399999999998f,0.78496699999999997f,0.35952699999999999f,0.57656700000000005f,0.201513f,0.64201299999999994f,0.41930800000000001f,0.340667f,0.42319000000000001f,0.86081200000000002f,0.69401999999999997f,0.423568f,0.37698700000000002f,0.56845299999999999f,0.50230200000000003f,0.28071600000000002f,0.46404099999999998f,0.39560099999999998f,0.19985f,0.095039799999999994f,0.64278999999999997f,0.228326f,0.48491099999999998f,0.84235300000000002f,0.16140399999999999f,0.40343200000000001f,0.65554900000000005f,0.40909800000000002f,0.69939200000000001f,0.87605f,1,0.18560599999999999f,0.41425499999999998f,0.69520499999999996f,0.73261200000000004f,0.478298f,0.24947f,0.92773899999999998f,0.21313499999999999f,0.227382f,0.976352f,0.64274500000000001f,0.37631100000000001f,0.26067400000000002f,0.81103400000000003f,0.26463100000000001f,0.239979f,0.26189699999999999f,0.19164200000000001f,0.78166999999999998f,0.390679f,0.38243700000000003f,0.20671400000000001f,0.22472f,0.067633200000000004f,0.50261100000000003f,0.30145499999999997f,0.24102899999999999f,0.22450500000000001f,0.72119299999999997f,0.43634800000000001f,0.25406200000000001f,0.48049599999999998f,0.77237100000000003f,0.21068100000000001f,0.10341500000000001f,0.48533799999999999f,0.378334f,0.22848399999999999f,0.11487700000000001f,0.68676000000000004f,0.29694199999999998f,0.50741999999999998f,0.99746999999999997f,0.037710300000000002f,0.132212f,0.31954700000000003f,0.19203200000000001f,0.52057399999999998f,0.58584400000000003f,0.41936200000000001f,0.084731699999999993f,0.134544f,0.19476199999999999f,0.61668900000000004f,0.39735999999999999f,0.29880899999999999f,0.91474599999999995f,0.051337099999999997f,0.0543569f,0.98915900000000001f,0.60289199999999998f,0.14558199999999999f,0.102149f,0.129022f,0.11648500000000001f,0.27998800000000001f,0.39427000000000001f,0.29013899999999998f,1,0.70865500000000003f,0.780555f,0.38752599999999998f,0.0395217f,0.0096406700000000005f,0.24368000000000001f,0.074062500000000003f,0.61931499999999995f,0.44739499999999999f,0.29249700000000001f,0.295458f,0.163748f,0.52137500000000003f,0.864533f,0.077340800000000001f,0.033423099999999997f,0.34512100000000001f,0.27886f,0.22387599999999999f,0.30775599999999997f,0.76310599999999995f,0.424707f,0.487201f,0.96896199999999999f,0.0091174700000000008f,0.032465300000000002f,0.33427499999999999f,0.16678699999999999f,0.312498f,0.264262f,0.35487999999999997f,0.37558999999999998f,0.26109399999999999f,0.56500600000000001f,0.474935f,0.31352000000000002f,0.251249f,0.73535200000000001f,0.018907199999999999f,0.015363399999999999f,0.78622499999999995f,0.50329900000000005f,0.36903799999999998f,0.25076500000000002f,0.67301900000000003f,0.387573f,0.74202500000000005f,0.74905600000000006f,0.261714f,0.75186799999999998f,0.77181599999999995f,1,0.459484f,0.0124402f,0.010539400000000001f,0.96410899999999999f,0.45705200000000001f,0.53231600000000001f,0.40712799999999999f,0.697241f,0.1522f,0.089589299999999997f,0.40617500000000001f,0.65103999999999995f,0.023395099999999999f,0.010107f,0.072234699999999999f,0.066633999999999999f,0.195489f,0.41674f,0.654451f,0.38278200000000001f,0.305396f,0.63150099999999998f,0.00162802f,0.0140906f,0.76291500000000001f,0.41024500000000003f,0.18943599999999999f,0.060446199999999999f,0.62494099999999997f,0.43978099999999998f,0.51627299999999998f,0.89667799999999998f,0.27329799999999999f,0.20286799999999999f,0.099602200000000002f,0.25765700000000002f,0.017450799999999999f,0.015785899999999999f,0.42943300000000001f,0.202184f,0.44311099999999998f,0.34381099999999998f,0.44756200000000002f,0.26869399999999999f,0.75355099999999997f,0.52942599999999995f,0.077297299999999999f,0.097696000000000005f,0.44641399999999998f,0.26167800000000002f,0.16903499999999999f,0.011621899999999999f,0.020739899999999999f,1,0.48885600000000001f,0.41302899999999998f,0.25266100000000002f,0.148369f,0.091964400000000002f,0.0330634f,0.268764f,0.44184899999999999f,0.013987299999999999f,0.010858400000000001f,0.65779900000000002f,0.48824800000000002f,0.37543300000000002f,0.958179f,0.76149199999999995f,0.40949000000000002f,0.15170900000000001f,0.31493100000000002f,0.0036118000000000001f,0.013306999999999999f,1,0.60534299999999996f,0.55050600000000005f,0.36351600000000001f,0.255278f,0.13753699999999999f,0.44888099999999997f,0.86761500000000003f,0.48324699999999998f,0.30862200000000001f,0.34844399999999998f,0.53483499999999995f,0.0157716f,0.0128965f,0.14760799999999999f,0.076261099999999998f,0.76222400000000001f,0.51158499999999996f,0.98586300000000004f,0.54022700000000001f,0.69169099999999994f,0.90529599999999999f,0.39752100000000001f,0.69794f,0.42328900000000003f,0.92461300000000002f,0.49155900000000002f,0.0056791100000000002f,0.010600200000000001f,0.64791600000000005f,0.32418200000000003f,0.57944899999999999f,0.451936f,0.87789700000000004f};
float 	mydsp::ftbl0[350];
