//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "EnglishChurchBell"
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
		m->declare("description", "English church bell physical model.");
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
		m->declare("name", "EnglishChurchBell");
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
		fConst12 = powf(0.001f,(1.0f / float((20.346989644553652f * fConst0))));
		fConst13 = ((0 - (2 * fConst12)) * cosf((1630.0404810562927f / fConst0)));
		fConst14 = faustpower<2>(fConst12);
		fConst15 = powf(0.001f,(1.0f / float((20.26822245756393f * fConst0))));
		fConst16 = ((0 - (2 * fConst15)) * cosf((1645.2834886115106f / fConst0)));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((13.650799900615313f * fConst0))));
		fConst19 = ((0 - (2 * fConst18)) * cosf((3099.6900907762124f / fConst0)));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((13.622392037859123f * fConst0))));
		fConst22 = ((0 - (2 * fConst21)) * cosf((3106.8592052117042f / fConst0)));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((11.095645822450564f * fConst0))));
		fConst25 = ((0 - (2 * fConst24)) * cosf((3789.0623331240349f / fConst0)));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((11.058927361611808f * fConst0))));
		fConst28 = ((0 - (2 * fConst27)) * cosf((3799.706049034397f / fConst0)));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((8.6621298206728596f * fConst0))));
		fConst31 = ((0 - (2 * fConst30)) * cosf((4552.5824452818842f / fConst0)));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((8.6582484684287806f * fConst0))));
		fConst34 = ((0 - (2 * fConst33)) * cosf((4553.9081973816992f / fConst0)));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((7.5637590600138438f * fConst0))));
		fConst37 = ((0 - (2 * fConst36)) * cosf((4944.7725889707272f / fConst0)));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((5.3802613620526891f * fConst0))));
		fConst40 = ((0 - (2 * fConst39)) * cosf((5855.2564054635068f / fConst0)));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((5.367507725684165f * fConst0))));
		fConst43 = ((0 - (2 * fConst42)) * cosf((5861.2442810612483f / fConst0)));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((5.2272315543679753f * fConst0))));
		fConst46 = ((0 - (2 * fConst45)) * cosf((5927.7392311671301f / fConst0)));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((5.1865570737549982f * fConst0))));
		fConst49 = ((0 - (2 * fConst48)) * cosf((5947.2422383606154f / fConst0)));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((5.1790325190219306f * fConst0))));
		fConst52 = ((0 - (2 * fConst51)) * cosf((5950.8613530975508f / fConst0)));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((5.1053119375968725f * fConst0))));
		fConst55 = ((0 - (2 * fConst54)) * cosf((5986.5058633451808f / fConst0)));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((4.2357922582370282f * fConst0))));
		fConst58 = ((0 - (2 * fConst57)) * cosf((6435.4897190256197f / fConst0)));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((4.1156731698312505f * fConst0))));
		fConst61 = ((0 - (2 * fConst60)) * cosf((6502.2171469878658f / fConst0)));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((2.436364038689613f * fConst0))));
		fConst64 = ((0 - (2 * fConst63)) * cosf((7612.6444863257148f / fConst0)));
		fConst65 = faustpower<2>(fConst63);
		fConst66 = powf(0.001f,(1.0f / float((2.4314706334864691f * fConst0))));
		fConst67 = ((0 - (2 * fConst66)) * cosf((7616.5400612161666f / fConst0)));
		fConst68 = faustpower<2>(fConst66);
		fConst69 = powf(0.001f,(1.0f / float((2.2465214934789559f * fConst0))));
		fConst70 = ((0 - (2 * fConst69)) * cosf((7767.7763315599786f / fConst0)));
		fConst71 = faustpower<2>(fConst69);
		fConst72 = powf(0.001f,(1.0f / float((1.5551788128959461f * fConst0))));
		fConst73 = ((0 - (2 * fConst72)) * cosf((8420.7877805351527f / fConst0)));
		fConst74 = faustpower<2>(fConst72);
		fConst75 = powf(0.001f,(1.0f / float((1.5496814888727277f * fConst0))));
		fConst76 = ((0 - (2 * fConst75)) * cosf((8426.693974723903f / fConst0)));
		fConst77 = faustpower<2>(fConst75);
		fConst78 = powf(0.001f,(1.0f / float((0.98544488733779434f * fConst0))));
		fConst79 = ((0 - (2 * fConst78)) * cosf((9127.1434727682827f / fConst0)));
		fConst80 = faustpower<2>(fConst78);
		fConst81 = powf(0.001f,(1.0f / float((0.98220878303745462f * fConst0))));
		fConst82 = ((0 - (2 * fConst81)) * cosf((9131.8558617486669f / fConst0)));
		fConst83 = faustpower<2>(fConst81);
		fConst84 = powf(0.001f,(1.0f / float((0.9805288122357434f * fConst0))));
		fConst85 = ((0 - (2 * fConst84)) * cosf((9134.3063040184661f / fConst0)));
		fConst86 = faustpower<2>(fConst84);
		fConst87 = powf(0.001f,(1.0f / float((0.96477099971326241f * fConst0))));
		fConst88 = ((0 - (2 * fConst87)) * cosf((9157.4284259488886f / fConst0)));
		fConst89 = faustpower<2>(fConst87);
		fConst90 = powf(0.001f,(1.0f / float((0.95720997764465754f * fConst0))));
		fConst91 = ((0 - (2 * fConst90)) * cosf((9168.6124957956672f / fConst0)));
		fConst92 = faustpower<2>(fConst90);
		fConst93 = powf(0.001f,(1.0f / float((0.9509956289530096f * fConst0))));
		fConst94 = ((0 - (2 * fConst93)) * cosf((9177.8487781972217f / fConst0)));
		fConst95 = faustpower<2>(fConst93);
		fConst96 = powf(0.001f,(1.0f / float((0.86074531260401566f * fConst0))));
		fConst97 = ((0 - (2 * fConst96)) * cosf((9316.7700053389617f / fConst0)));
		fConst98 = faustpower<2>(fConst96);
		fConst99 = powf(0.001f,(1.0f / float((0.8598378251842046f * fConst0))));
		fConst100 = ((0 - (2 * fConst99)) * cosf((9318.2151379596125f / fConst0)));
		fConst101 = faustpower<2>(fConst99);
		fConst102 = powf(0.001f,(1.0f / float((0.72372418788472803f * fConst0))));
		fConst103 = ((0 - (2 * fConst102)) * cosf((9547.6142335247405f / fConst0)));
		fConst104 = faustpower<2>(fConst102);
		fConst105 = powf(0.001f,(1.0f / float((0.63056713762797367f * fConst0))));
		fConst106 = ((0 - (2 * fConst105)) * cosf((9721.7841302397592f / fConst0)));
		fConst107 = faustpower<2>(fConst105);
		fConst108 = powf(0.001f,(1.0f / float((0.57252831233958168f * fConst0))));
		fConst109 = ((0 - (2 * fConst108)) * cosf((9839.1540317778727f / fConst0)));
		fConst110 = faustpower<2>(fConst108);
		fConst111 = powf(0.001f,(1.0f / float((0.54007833671700944f * fConst0))));
		fConst112 = ((0 - (2 * fConst111)) * cosf((9908.2690701568481f / fConst0)));
		fConst113 = faustpower<2>(fConst111);
		fConst114 = powf(0.001f,(1.0f / float((0.26107629190376497f * fConst0))));
		fConst115 = ((0 - (2 * fConst114)) * cosf((10665.518563378133f / fConst0)));
		fConst116 = faustpower<2>(fConst114);
		fConst117 = powf(0.001f,(1.0f / float((0.091954789804467446f * fConst0))));
		fConst118 = ((0 - (2 * fConst117)) * cosf((11476.929113947303f / fConst0)));
		fConst119 = faustpower<2>(fConst117);
		fConst120 = powf(0.001f,(1.0f / float((0.044917265793401807f * fConst0))));
		fConst121 = ((0 - (2 * fConst120)) * cosf((11891.305184955798f / fConst0)));
		fConst122 = faustpower<2>(fConst120);
		fConst123 = powf(0.001f,(1.0f / float((0.042999568079710032f * fConst0))));
		fConst124 = ((0 - (2 * fConst123)) * cosf((11913.484829090141f / fConst0)));
		fConst125 = faustpower<2>(fConst123);
		fConst126 = powf(0.001f,(1.0f / float((0.04101261824121398f * fConst0))));
		fConst127 = ((0 - (2 * fConst126)) * cosf((11937.172437698207f / fConst0)));
		fConst128 = faustpower<2>(fConst126);
		fConst129 = powf(0.001f,(1.0f / float((0.036793119375196873f * fConst0))));
		fConst130 = ((0 - (2 * fConst129)) * cosf((11990.139689837732f / fConst0)));
		fConst131 = faustpower<2>(fConst129);
		fConst132 = powf(0.001f,(1.0f / float((0.0072463545014592933f * fConst0))));
		fConst133 = ((0 - (2 * fConst132)) * cosf((12591.189196322532f / fConst0)));
		fConst134 = faustpower<2>(fConst132);
		fConst135 = powf(0.001f,(1.0f / float((0.0070649477027738281f * fConst0))));
		fConst136 = ((0 - (2 * fConst135)) * cosf((12598.226363866572f / fConst0)));
		fConst137 = faustpower<2>(fConst135);
		fConst138 = powf(0.001f,(1.0f / float((0.0069340694332770889f * fConst0))));
		fConst139 = ((0 - (2 * fConst138)) * cosf((12603.37857581846f / fConst0)));
		fConst140 = faustpower<2>(fConst138);
		fConst141 = powf(0.001f,(1.0f / float((0.0069182201378559949f * fConst0))));
		fConst142 = ((0 - (2 * fConst141)) * cosf((12604.006894349179f / fConst0)));
		fConst143 = faustpower<2>(fConst141);
		fConst144 = powf(0.001f,(1.0f / float((0.0010372545728773355f * fConst0))));
		fConst145 = ((0 - (2 * fConst144)) * cosf((12989.982967769221f / fConst0)));
		fConst146 = faustpower<2>(fConst144);
		fConst147 = powf(0.001f,(1.0f / float((0.00050088541825259278f * fConst0))));
		fConst148 = ((0 - (2 * fConst147)) * cosf((13084.230747376914f / fConst0)));
		fConst149 = faustpower<2>(fConst147);
		fConst150 = powf(0.001f,(1.0f / float((0.00038955863533521231f * fConst0))));
		fConst151 = ((0 - (2 * fConst150)) * cosf((13111.813930875433f / fConst0)));
		fConst152 = faustpower<2>(fConst150);
		fConst153 = powf(0.001f,(1.0f / float((1.3757987907390359e-05f * fConst0))));
		fConst154 = ((0 - (2 * fConst153)) * cosf((13323.871434992743f / fConst0)));
		fConst155 = faustpower<2>(fConst153);
		fConst156 = powf(0.001f,(1.0f / float((1.1713786955137761e-06f * fConst0))));
		fConst157 = ((0 - (2 * fConst156)) * cosf((13381.865235378011f / fConst0)));
		fConst158 = faustpower<2>(fConst156);
		fConst159 = powf(0.001f,(1.0f / float((1.7000364314854178e-07f * fConst0))));
		fConst160 = ((0 - (2 * fConst159)) * cosf((13403.479392834708f / fConst0)));
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
		ui_interface->openVerticalBox("englishBell");
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


float 	mydsp::SIG0::fWave0[350] = {0.69427399999999995f,0.47169800000000001f,0.17238999999999999f,0.58544600000000002f,0.39798600000000001f,0.91957900000000004f,0.53194699999999995f,0.100205f,0.63946899999999995f,0.67220899999999995f,0.144345f,0.41659499999999999f,0.124108f,0.38059100000000001f,0.25657799999999997f,0.64603100000000002f,0.85219999999999996f,0.022437599999999999f,0.38276199999999999f,0.143925f,0.36869099999999999f,0.43055599999999999f,0.32318000000000002f,0.142956f,0.27452100000000002f,0.71382400000000001f,0.44279400000000002f,0.35247299999999998f,0.247756f,0.41515200000000002f,1,0.40186899999999998f,0.19798099999999999f,0.27950999999999998f,0.21024899999999999f,0.36974000000000001f,0.36922700000000003f,0.15576899999999999f,0.272368f,0.33571200000000001f,0.31645000000000001f,0.71410300000000004f,0.28578100000000001f,0.22006000000000001f,0.827704f,0.206342f,0.180177f,0.31147799999999998f,0.197607f,0.57547499999999996f,0.47331099999999998f,0.58723199999999998f,0.50287999999999999f,0.337308f,0.30451400000000001f,0.429039f,0.351522f,0.34137299999999998f,0.17508099999999999f,0.56174800000000003f,0.43917200000000001f,0.32316400000000001f,0.54051800000000005f,0.53652299999999997f,0.074386499999999994f,0.213417f,0.358012f,0.47449400000000003f,0.31027399999999999f,0.83941299999999996f,0.241372f,0.202343f,0.48063400000000001f,0.99568500000000004f,0.37374000000000002f,0.13399800000000001f,0.52067399999999997f,0.207514f,1,0.101239f,0.27953600000000001f,0.18598500000000001f,0.43629299999999999f,0.62411000000000005f,0.33451900000000001f,0.28358499999999998f,0.179317f,0.35384700000000002f,0.44954499999999997f,0.57412799999999997f,0.13517199999999999f,0.53827499999999995f,0.47642400000000001f,0.83290299999999995f,0.16419800000000001f,0.18856200000000001f,0.13597799999999999f,0.39012799999999997f,0.13104499999999999f,0.31206499999999998f,0.14213899999999999f,0.025590100000000001f,0.26694699999999999f,0.37160700000000002f,0.016843500000000001f,0.024946800000000002f,0.50891699999999995f,0.35441f,0.28334799999999999f,0.62815500000000002f,0.29247800000000002f,0.35835f,0.34256900000000001f,0.44123699999999999f,0.88669900000000001f,0.017469800000000001f,0.0064184300000000001f,0.55532000000000004f,0.88012900000000005f,0.0306909f,0.29008099999999998f,0.24881600000000001f,0.98173600000000005f,0.32462400000000002f,0.213676f,0.43288500000000002f,0.098155900000000004f,0.44414900000000002f,0.39555400000000002f,0.52506900000000001f,0.077130799999999999f,0.048880399999999997f,0.59132099999999999f,0.108044f,0.44380199999999997f,0.74031800000000003f,0.59943800000000003f,0.29309299999999999f,1,0.14166200000000001f,0.91003100000000003f,0.22612599999999999f,0.29970200000000002f,0.341472f,0.056806099999999998f,0.222494f,0.91871800000000003f,0.19947799999999999f,0.21662000000000001f,0.10775899999999999f,0.69232400000000005f,0.55633600000000005f,0.28171800000000002f,0.43083199999999999f,0.34165600000000002f,0.60809500000000005f,0.34212900000000002f,0.31131199999999998f,0.22995299999999999f,0.69508700000000001f,0.076148900000000005f,0.34981800000000002f,0.36170600000000003f,0.57761099999999999f,0.14779700000000001f,0.327376f,0.46571499999999999f,0.34290199999999998f,0.52138099999999998f,0.83682800000000002f,0.24111199999999999f,0.28439399999999998f,0.53931600000000002f,0.14340800000000001f,0.51702000000000004f,1,0.23633599999999999f,0.48033300000000001f,0.67674400000000001f,0.80758200000000002f,0.46862100000000001f,0.236953f,0.41160400000000003f,0.57925099999999996f,0.42509799999999998f,0.37598999999999999f,0.46117599999999997f,0.27653f,0.462368f,0.61300399999999999f,0.66684900000000003f,0.95471499999999998f,0.16150700000000001f,0.170433f,0.29046100000000002f,0.117303f,0.36513299999999999f,0.233794f,0.19456799999999999f,0.33887400000000001f,0.52338099999999999f,0.39834999999999998f,0.44783899999999999f,0.652891f,0.15708f,0.34035399999999999f,0.44217000000000001f,0.33876400000000001f,0.18439700000000001f,0.77160700000000004f,0.16050200000000001f,0.32448700000000003f,0.47749900000000001f,0.83151900000000001f,0.0168764f,0.15426400000000001f,0.20186499999999999f,0.237786f,0.39006600000000002f,0.88016399999999995f,0.28423399999999999f,0.16283700000000001f,0.43755699999999997f,0.22784599999999999f,0.39933999999999997f,1,0.158107f,0.39690300000000001f,0.51302899999999996f,0.67645699999999997f,0.20428199999999999f,0.089557499999999998f,0.55540999999999996f,0.73248599999999997f,0.12506200000000001f,0.17122899999999999f,0.081645999999999996f,0.054139399999999997f,0.39616000000000001f,0.45428800000000003f,0.46686299999999997f,0.92884199999999995f,0.155393f,0.26284999999999997f,0.113453f,0.133163f,0.30202099999999998f,0.61261600000000005f,0.22839200000000001f,0.19561700000000001f,0.28723599999999999f,0.19876199999999999f,0.499884f,0.80913900000000005f,0.0092992500000000002f,0.084029900000000005f,0.28644599999999998f,0.182112f,0.18604399999999999f,0.75413799999999998f,0.27955600000000003f,0.26694800000000002f,0.49429099999999998f,1,0.32128400000000001f,0.0230981f,0.037553700000000002f,0.26253100000000001f,0.60220399999999996f,0.489925f,0.633077f,0.40740900000000002f,0.42225600000000002f,0.091064099999999995f,0.357935f,0.55017899999999997f,0.10619199999999999f,0.13236600000000001f,0.37623099999999998f,0.35115099999999999f,0.042030199999999997f,0.037218300000000003f,0.69633500000000004f,0.84082100000000004f,0.85523499999999997f,0.249248f,0.86001099999999997f,0.34048099999999998f,0.28558f,0.363039f,0.32412200000000002f,0.51569900000000002f,0.228131f,0.172592f,0.018872300000000002f,0.168243f,0.99510500000000002f,0.74175899999999995f,0.10709299999999999f,0.070348999999999995f,0.13663600000000001f,0.078045500000000004f,0.31574799999999997f,0.50220100000000001f,0.019042199999999999f,0.033914f,0.22572400000000001f,0.16023599999999999f,0.18410099999999999f,0.56420300000000001f,0.24731700000000001f,0.28422500000000001f,0.32715300000000003f,0.65144299999999999f,0.59347099999999997f,0.016389899999999999f,0.014104800000000001f,0.52112999999999998f,1,0.10510899999999999f,0.53093599999999996f,0.36372399999999999f,0.92480899999999999f,0.25041000000000002f,0.69288000000000005f,0.41412199999999999f,0.0793658f,0.34781299999999998f,0.44173099999999998f,0.47642800000000002f,0.080883399999999994f,0.058163800000000002f,0.55723900000000004f,0.55651499999999998f,0.74608399999999997f,0.58222799999999997f,0.177231f,0.15842500000000001f,0.85090299999999996f,0.75527100000000003f,0.67361400000000005f,0.31706000000000001f,0.051538599999999997f,0.20189799999999999f,0.057793799999999999f,0.23203099999999999f,0.73498799999999997f,0.141594f,0.26706200000000002f,0.14580699999999999f};
float 	mydsp::ftbl0[350];
