//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "FrenchChurchBell"
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
		m->declare("description", "French church bell physical model.");
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
		m->declare("name", "FrenchChurchBell");
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
		fConst12 = powf(0.001f,(1.0f / float((17.04040295618125f * fConst0))));
		fConst13 = ((0 - (2 * fConst12)) * cosf((2758.8021551204911f / fConst0)));
		fConst14 = faustpower<2>(fConst12);
		fConst15 = powf(0.001f,(1.0f / float((17.010755596973247f * fConst0))));
		fConst16 = ((0 - (2 * fConst15)) * cosf((2766.5179066777077f / fConst0)));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((13.308511157375246f * fConst0))));
		fConst19 = ((0 - (2 * fConst18)) * cosf((3810.4502959096744f / fConst0)));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((13.199737475192013f * fConst0))));
		fConst22 = ((0 - (2 * fConst21)) * cosf((3843.9019744850984f / fConst0)));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((11.304904713130588f * fConst0))));
		fConst25 = ((0 - (2 * fConst24)) * cosf((4458.6551081248563f / fConst0)));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((11.300127845394371f * fConst0))));
		fConst28 = ((0 - (2 * fConst27)) * cosf((4460.288736304723f / fConst0)));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((8.8077480341046552f * fConst0))));
		fConst31 = ((0 - (2 * fConst30)) * cosf((5384.4761799524613f / fConst0)));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((8.1690669816675641f * fConst0))));
		fConst34 = ((0 - (2 * fConst33)) * cosf((5648.9040336051148f / fConst0)));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((5.9589169207409025f * fConst0))));
		fConst37 = ((0 - (2 * fConst36)) * cosf((6687.6339454027357f / fConst0)));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((5.9543617544807077f * fConst0))));
		fConst40 = ((0 - (2 * fConst39)) * cosf((6690.0215558194641f / fConst0)));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((5.855682576919202f * fConst0))));
		fConst43 = ((0 - (2 * fConst42)) * cosf((6742.0463301629115f / fConst0)));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((5.8391062141137358f * fConst0))));
		fConst46 = ((0 - (2 * fConst45)) * cosf((6750.8427895929635f / fConst0)));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((5.8137106144624733f * fConst0))));
		fConst49 = ((0 - (2 * fConst48)) * cosf((6764.3516380033989f / fConst0)));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((5.0389728617421001f * fConst0))));
		fConst52 = ((0 - (2 * fConst51)) * cosf((7196.8861145496421f / fConst0)));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((5.0017518683155444f * fConst0))));
		fConst55 = ((0 - (2 * fConst54)) * cosf((7218.7515994186269f / fConst0)));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((4.5050160328421054f * fConst0))));
		fConst58 = ((0 - (2 * fConst57)) * cosf((7521.5382993716103f / fConst0)));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((4.477013471385078f * fConst0))));
		fConst61 = ((0 - (2 * fConst60)) * cosf((7539.2568819378575f / fConst0)));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((2.8620540343361816f * fConst0))));
		fConst64 = ((0 - (2 * fConst63)) * cosf((8719.1762507731128f / fConst0)));
		fConst65 = faustpower<2>(fConst63);
		fConst66 = powf(0.001f,(1.0f / float((2.7714014396041233f * fConst0))));
		fConst67 = ((0 - (2 * fConst66)) * cosf((8797.4647397005701f / fConst0)));
		fConst68 = faustpower<2>(fConst66);
		fConst69 = powf(0.001f,(1.0f / float((2.7555252165511002f * fConst0))));
		fConst70 = ((0 - (2 * fConst69)) * cosf((8811.3505792294363f / fConst0)));
		fConst71 = faustpower<2>(fConst69);
		fConst72 = powf(0.001f,(1.0f / float((2.0414947209883065f * fConst0))));
		fConst73 = ((0 - (2 * fConst72)) * cosf((9500.5531755739648f / fConst0)));
		fConst74 = faustpower<2>(fConst72);
		fConst75 = powf(0.001f,(1.0f / float((2.0356297087179271f * fConst0))));
		fConst76 = ((0 - (2 * fConst75)) * cosf((9506.8363608811451f / fConst0)));
		fConst77 = faustpower<2>(fConst75);
		fConst78 = powf(0.001f,(1.0f / float((1.6048868209702056f * fConst0))));
		fConst79 = ((0 - (2 * fConst78)) * cosf((10005.784106124276f / fConst0)));
		fConst80 = faustpower<2>(fConst78);
		fConst81 = powf(0.001f,(1.0f / float((1.6004903751006789f * fConst0))));
		fConst82 = ((0 - (2 * fConst81)) * cosf((10011.313309194593f / fConst0)));
		fConst83 = faustpower<2>(fConst81);
		fConst84 = powf(0.001f,(1.0f / float((1.2754722662774238f * fConst0))));
		fConst85 = ((0 - (2 * fConst84)) * cosf((10451.764599227883f / fConst0)));
		fConst86 = faustpower<2>(fConst84);
		fConst87 = powf(0.001f,(1.0f / float((1.2625590045232717f * fConst0))));
		fConst88 = ((0 - (2 * fConst87)) * cosf((10470.739818855565f / fConst0)));
		fConst89 = faustpower<2>(fConst87);
		fConst90 = powf(0.001f,(1.0f / float((1.1595958104151465f * fConst0))));
		fConst91 = ((0 - (2 * fConst90)) * cosf((10626.876973738978f / fConst0)));
		fConst92 = faustpower<2>(fConst90);
		fConst93 = powf(0.001f,(1.0f / float((1.1497589123614478f * fConst0))));
		fConst94 = ((0 - (2 * fConst93)) * cosf((10642.270777741567f / fConst0)));
		fConst95 = faustpower<2>(fConst93);
		fConst96 = powf(0.001f,(1.0f / float((0.75996847616547847f * fConst0))));
		fConst97 = ((0 - (2 * fConst96)) * cosf((11340.081337956932f / fConst0)));
		fConst98 = faustpower<2>(fConst96);
		fConst99 = powf(0.001f,(1.0f / float((0.74785119377754439f * fConst0))));
		fConst100 = ((0 - (2 * fConst99)) * cosf((11365.276911038722f / fConst0)));
		fConst101 = faustpower<2>(fConst99);
		fConst102 = powf(0.001f,(1.0f / float((0.71460364706108059f * fConst0))));
		fConst103 = ((0 - (2 * fConst102)) * cosf((11435.83708203835f / fConst0)));
		fConst104 = faustpower<2>(fConst102);
		fConst105 = powf(0.001f,(1.0f / float((0.63854240932405604f * fConst0))));
		fConst106 = ((0 - (2 * fConst105)) * cosf((11605.922908303701f / fConst0)));
		fConst107 = faustpower<2>(fConst105);
		fConst108 = powf(0.001f,(1.0f / float((0.48151058112985545f * fConst0))));
		fConst109 = ((0 - (2 * fConst108)) * cosf((12005.47066198725f / fConst0)));
		fConst110 = faustpower<2>(fConst108);
		fConst111 = powf(0.001f,(1.0f / float((0.44447196651029619f * fConst0))));
		fConst112 = ((0 - (2 * fConst111)) * cosf((12112.096316650088f / fConst0)));
		fConst113 = faustpower<2>(fConst111);
		fConst114 = powf(0.001f,(1.0f / float((0.25315222492990691f * fConst0))));
		fConst115 = ((0 - (2 * fConst114)) * cosf((12786.721923081961f / fConst0)));
		fConst116 = faustpower<2>(fConst114);
		fConst117 = powf(0.001f,(1.0f / float((0.24784668362861059f * fConst0))));
		fConst118 = ((0 - (2 * fConst117)) * cosf((12809.718381306238f / fConst0)));
		fConst119 = faustpower<2>(fConst117);
		fConst120 = powf(0.001f,(1.0f / float((0.22561720108958672f * fConst0))));
		fConst121 = ((0 - (2 * fConst120)) * cosf((12909.809523249607f / fConst0)));
		fConst122 = faustpower<2>(fConst120);
		fConst123 = powf(0.001f,(1.0f / float((0.22425446159732085f * fConst0))));
		fConst124 = ((0 - (2 * fConst123)) * cosf((12916.15554040986f / fConst0)));
		fConst125 = faustpower<2>(fConst123);
		fConst126 = powf(0.001f,(1.0f / float((0.19466372098518633f * fConst0))));
		fConst127 = ((0 - (2 * fConst126)) * cosf((13060.794466181134f / fConst0)));
		fConst128 = faustpower<2>(fConst126);
		fConst129 = powf(0.001f,(1.0f / float((0.17908417853502584f * fConst0))));
		fConst130 = ((0 - (2 * fConst129)) * cosf((13142.915698145973f / fConst0)));
		fConst131 = faustpower<2>(fConst129);
		fConst132 = powf(0.001f,(1.0f / float((0.1526621927614977f * fConst0))));
		fConst133 = ((0 - (2 * fConst132)) * cosf((13293.837809224426f / fConst0)));
		fConst134 = faustpower<2>(fConst132);
		fConst135 = powf(0.001f,(1.0f / float((0.14125680298676502f * fConst0))));
		fConst136 = ((0 - (2 * fConst135)) * cosf((13364.397980224054f / fConst0)));
		fConst137 = faustpower<2>(fConst135);
		fConst138 = powf(0.001f,(1.0f / float((0.074116251238799224f * fConst0))));
		fConst139 = ((0 - (2 * fConst138)) * cosf((13884.959882923882f / fConst0)));
		fConst140 = faustpower<2>(fConst138);
		fConst141 = powf(0.001f,(1.0f / float((0.071451861871339228f * fConst0))));
		fConst142 = ((0 - (2 * fConst141)) * cosf((13911.286429360964f / fConst0)));
		fConst143 = faustpower<2>(fConst141);
		fConst144 = powf(0.001f,(1.0f / float((0.031293144776313404f * fConst0))));
		fConst145 = ((0 - (2 * fConst144)) * cosf((14427.135943080408f / fConst0)));
		fConst146 = faustpower<2>(fConst144);
		fConst147 = powf(0.001f,(1.0f / float((0.030599178813371701f * fConst0))));
		fConst148 = ((0 - (2 * fConst147)) * cosf((14439.262490723264f / fConst0)));
		fConst149 = faustpower<2>(fConst147);
		fConst150 = powf(0.001f,(1.0f / float((0.030282650370147293f * fConst0))));
		fConst151 = ((0 - (2 * fConst150)) * cosf((14444.854525646651f / fConst0)));
		fConst152 = faustpower<2>(fConst150);
		fConst153 = powf(0.001f,(1.0f / float((0.027319225746369299f * fConst0))));
		fConst154 = ((0 - (2 * fConst153)) * cosf((14499.204078553756f / fConst0)));
		fConst155 = faustpower<2>(fConst153);
		fConst156 = powf(0.001f,(1.0f / float((0.0061733070698476869f * fConst0))));
		fConst157 = ((0 - (2 * fConst156)) * cosf((15107.542079994884f / fConst0)));
		fConst158 = faustpower<2>(fConst156);
		fConst159 = powf(0.001f,(1.0f / float((0.0056314158749425705f * fConst0))));
		fConst160 = ((0 - (2 * fConst159)) * cosf((15136.130573142551f / fConst0)));
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
		ui_interface->openVerticalBox("frenchBell");
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


float 	mydsp::SIG0::fWave0[350] = {0.97289000000000003f,0.54239300000000001f,0.49583199999999999f,0.89796600000000004f,0.55236700000000005f,0.55789500000000003f,0.61421300000000001f,0.35369400000000001f,0.43603900000000001f,0.44102400000000003f,0.67491299999999999f,0.56675399999999998f,0.75500800000000001f,0.69903000000000004f,0.16439799999999999f,0.91003999999999996f,0.62837299999999996f,0.20171800000000001f,0.42951699999999998f,0.50371500000000002f,0.871174f,0.10688599999999999f,0.76117299999999999f,0.67360200000000003f,0.291937f,0.58858999999999995f,0.31528f,0.41308099999999998f,0.27446399999999999f,0.494062f,0.69612099999999999f,0.61201000000000005f,0.38275700000000001f,0.99511300000000003f,0.22880600000000001f,0.19844899999999999f,0.59584700000000002f,0.30626300000000001f,0.25239699999999998f,0.088356699999999996f,0.23608599999999999f,1,0.245278f,0.379388f,0.198824f,0.54889200000000005f,0.49276399999999998f,0.420871f,0.79463700000000004f,0.60563400000000001f,1,0.604159f,0.399841f,0.79934700000000003f,0.50718700000000005f,0.50980999999999999f,0.477383f,0.310226f,0.42697600000000002f,0.43762299999999998f,0.73571200000000003f,0.63072799999999996f,0.62578500000000004f,0.65116799999999997f,0.27773799999999998f,0.850858f,0.57807900000000001f,0.64535399999999998f,0.38369999999999999f,0.37059799999999998f,0.78254199999999996f,0.18132499999999999f,0.61439100000000002f,0.74068400000000001f,0.342441f,0.58618599999999998f,0.28690900000000003f,0.40519699999999997f,0.25921499999999997f,0.56698300000000001f,0.74821899999999997f,0.65589799999999998f,0.36825999999999998f,0.94081400000000004f,0.33615699999999998f,0.41370200000000001f,0.56155699999999997f,0.40217599999999998f,0.117698f,0.32936900000000002f,0.25457099999999999f,0.87070599999999998f,0.26098100000000002f,0.27412199999999998f,0.20624700000000001f,0.64529999999999998f,0.400758f,0.363622f,0.63683400000000001f,0.58456600000000003f,0.975603f,0.61693699999999996f,0.29540100000000002f,0.650447f,0.46422099999999999f,0.465057f,0.31246699999999999f,0.23835799999999999f,0.38369500000000001f,0.39967399999999997f,0.75391200000000003f,0.66201200000000004f,0.50426800000000005f,0.599248f,0.37866499999999997f,0.72536299999999998f,0.49321399999999999f,1,0.33283600000000002f,0.26588899999999999f,0.67407300000000003f,0.32040099999999999f,0.44001800000000002f,0.76978199999999997f,0.31641900000000001f,0.52996799999999999f,0.38050899999999999f,0.57867599999999997f,0.24901300000000001f,0.59138400000000002f,0.76171699999999998f,0.68705700000000003f,0.32443699999999998f,0.81886400000000004f,0.50536899999999996f,0.672485f,0.461783f,0.42619800000000002f,0.067887500000000003f,0.43532900000000002f,0.34795500000000001f,0.70839399999999997f,0.29332200000000003f,0.328986f,0.25825399999999998f,0.89351199999999997f,0.320131f,0.43355399999999999f,0.45930199999999999f,0.54221299999999995f,0.817241f,0.51622999999999997f,0.20530200000000001f,0.46735399999999999f,0.388683f,0.38821600000000001f,0.171262f,0.150865f,0.29171999999999998f,0.31141400000000002f,0.65887600000000002f,0.57064700000000002f,0.38361899999999999f,0.50245499999999998f,0.36411399999999999f,0.53231300000000004f,0.352989f,1,0.26198399999999999f,0.21959100000000001f,0.54403100000000004f,0.33719900000000003f,0.279173f,0.66830299999999998f,0.20843900000000001f,0.39922999999999997f,0.41867399999999999f,0.64861800000000003f,0.23413300000000001f,0.50472899999999998f,0.645347f,0.572851f,0.23282800000000001f,0.61429199999999995f,0.48527199999999998f,0.66626399999999997f,0.31657000000000002f,0.320355f,0.19142100000000001f,0.34013100000000002f,0.34206900000000001f,0.53837100000000004f,0.28113100000000002f,0.39311499999999999f,0.25139400000000001f,0.89072499999999999f,0.31064399999999998f,0.50370000000000004f,0.29909000000000002f,0.44247799999999998f,0.733128f,0.45521699999999998f,0.199322f,0.31569900000000001f,0.37585600000000002f,0.37648999999999999f,0.029145000000000001f,0.020028299999999999f,0.27957799999999999f,0.31680000000000003f,0.65595700000000001f,0.54684299999999997f,0.34966599999999998f,0.47024899999999997f,0.353765f,0.28679399999999999f,0.18018500000000001f,1,0.21083099999999999f,0.28013300000000002f,0.53585300000000002f,0.37648799999999999f,0.15367f,0.634745f,0.051044899999999997f,0.48557499999999998f,0.59311100000000005f,0.91788400000000003f,0.38047700000000001f,0.422925f,0.59937300000000004f,0.311421f,0.135654f,0.359954f,0.29574800000000001f,0.474439f,0.35333900000000001f,0.116743f,0.45431300000000002f,0.112858f,0.35931000000000002f,0.48389700000000002f,0.30160799999999999f,0.57734200000000002f,0.26266299999999998f,0.79498599999999997f,0.54957999999999996f,0.80808599999999997f,0.15251100000000001f,0.43959100000000001f,0.535941f,0.30801800000000001f,0.41983700000000002f,0.57919100000000001f,0.25042799999999998f,0.25212000000000001f,0.10285999999999999f,0.28833199999999998f,0.59967899999999996f,0.66510800000000003f,0.63628499999999999f,0.49523400000000001f,0.25161299999999998f,0.20852699999999999f,0.093907199999999996f,0.45841500000000002f,0.31895200000000001f,0.23535f,0.21518899999999999f,0.31341200000000002f,0.0472787f,0.038689300000000003f,0.086335899999999993f,0.22234599999999999f,0.36151100000000003f,0.99703699999999995f,0.238509f,0.38213999999999998f,1,0.20355400000000001f,0.47208699999999998f,0.509015f,0.206371f,0.44101299999999999f,0.79400800000000005f,0.97162300000000001f,0.79638399999999998f,0.55042999999999997f,0.68777999999999995f,0.55429799999999996f,0.043654499999999999f,0.059557699999999998f,0.21468499999999999f,0.58147000000000004f,0.27732000000000001f,0.36846600000000002f,0.121382f,0.15273900000000001f,0.078224399999999999f,0.190497f,0.31626900000000002f,0.18045600000000001f,0.405196f,0.51871599999999995f,0.15936500000000001f,0.16580800000000001f,0.19437199999999999f,0.61476399999999998f,0.55341499999999999f,0.64479399999999998f,0.44178000000000001f,0.44148999999999999f,0.22158800000000001f,1,0.57937099999999997f,0.60633899999999996f,0.52916700000000005f,0.021447500000000001f,0.41704599999999997f,0.66315199999999996f,0.894841f,0.47575200000000001f,0.16828899999999999f,0.46859000000000001f,0.30460399999999999f,0.66636899999999999f,0.30833700000000003f,0.29509099999999999f,0.76894499999999999f,0.35091099999999997f,0.49068000000000001f,0.51658400000000004f,0.400117f,0.82068700000000006f,0.54548600000000003f,0.70935700000000002f,0.50975899999999996f,0.47200599999999998f,0.15245500000000001f,0.98126500000000005f,0.45913399999999999f,0.69866600000000001f,0.24715400000000001f,0.62325299999999995f,0.25550800000000001f,0.83081499999999997f,0.088708999999999996f,0.126082f,0.0770623f,0.26332800000000001f};
float 	mydsp::ftbl0[350];
