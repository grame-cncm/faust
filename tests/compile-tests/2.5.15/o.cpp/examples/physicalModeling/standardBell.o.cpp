//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "StandardChurchBell"
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
		m->declare("description", "Standard church bell physical model.");
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
		m->declare("name", "StandardChurchBell");
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
		fConst12 = powf(0.001f,(1.0f / float((21.982853584773636f * fConst0))));
		fConst13 = ((0 - (2 * fConst12)) * cosf((3080.3315968447923f / fConst0)));
		fConst14 = faustpower<2>(fConst12);
		fConst15 = powf(0.001f,(1.0f / float((21.932469698864463f * fConst0))));
		fConst16 = ((0 - (2 * fConst15)) * cosf((3101.6692941479741f / fConst0)));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((16.087593238460567f * fConst0))));
		fConst19 = ((0 - (2 * fConst18)) * cosf((5810.9285331213541f / fConst0)));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((16.051413216692655f * fConst0))));
		fConst22 = ((0 - (2 * fConst21)) * cosf((5829.4073811097696f / fConst0)));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((13.114874870120767f * fConst0))));
		fConst25 = ((0 - (2 * fConst24)) * cosf((7421.7613166935989f / fConst0)));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((13.052563776165233f * fConst0))));
		fConst28 = ((0 - (2 * fConst27)) * cosf((7457.7639685037384f / fConst0)));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((11.364888445110509f * fConst0))));
		fConst31 = ((0 - (2 * fConst30)) * cosf((8475.0116697361118f / fConst0)));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((11.358293975944655f * fConst0))));
		fConst34 = ((0 - (2 * fConst33)) * cosf((8479.1585720388521f / fConst0)));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((9.3678292421214024f * fConst0))));
		fConst37 = ((0 - (2 * fConst36)) * cosf((9803.8425303515232f / fConst0)));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((8.7091274892074768f * fConst0))));
		fConst40 = ((0 - (2 * fConst39)) * cosf((10279.102666986588f / fConst0)));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((8.1188238696053876f * fConst0))));
		fConst43 = ((0 - (2 * fConst42)) * cosf((10723.700859322615f / fConst0)));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((8.0686079715015087f * fConst0))));
		fConst46 = ((0 - (2 * fConst45)) * cosf((10762.405280814843f / fConst0)));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((7.8094702054557921f * fConst0))));
		fConst49 = ((0 - (2 * fConst48)) * cosf((10964.472520293737f / fConst0)));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((7.8078745146888222f * fConst0))));
		fConst52 = ((0 - (2 * fConst51)) * cosf((10965.729157355172f / fConst0)));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((5.8942008392667091f * fConst0))));
		fConst55 = ((0 - (2 * fConst54)) * cosf((12600.990965401732f / fConst0)));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((5.7606001367313509f * fConst0))));
		fConst58 = ((0 - (2 * fConst57)) * cosf((12726.403344133038f / fConst0)));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((5.5736002821756339f * fConst0))));
		fConst61 = ((0 - (2 * fConst60)) * cosf((12904.908638710009f / fConst0)));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((5.0146797867234678f * fConst0))));
		fConst64 = ((0 - (2 * fConst63)) * cosf((13460.90770654233f / fConst0)));
		fConst65 = faustpower<2>(fConst63);
		fConst66 = powf(0.001f,(1.0f / float((4.959628215620957f * fConst0))));
		fConst67 = ((0 - (2 * fConst66)) * cosf((13517.644869866162f / fConst0)));
		fConst68 = faustpower<2>(fConst66);
		fConst69 = powf(0.001f,(1.0f / float((3.5435644188953579f * fConst0))));
		fConst70 = ((0 - (2 * fConst69)) * cosf((15130.915529337592f / fConst0)));
		fConst71 = faustpower<2>(fConst69);
		fConst72 = powf(0.001f,(1.0f / float((2.9507849172756142f * fConst0))));
		fConst73 = ((0 - (2 * fConst72)) * cosf((15922.282718776862f / fConst0)));
		fConst74 = faustpower<2>(fConst72);
		fConst75 = powf(0.001f,(1.0f / float((2.940516749763971f * fConst0))));
		fConst76 = ((0 - (2 * fConst75)) * cosf((15936.796876836446f / fConst0)));
		fConst77 = faustpower<2>(fConst75);
		fConst78 = powf(0.001f,(1.0f / float((2.569781241154915f * fConst0))));
		fConst79 = ((0 - (2 * fConst78)) * cosf((16482.680016324211f / fConst0)));
		fConst80 = faustpower<2>(fConst78);
		fConst81 = powf(0.001f,(1.0f / float((2.5489449420550847f * fConst0))));
		fConst82 = ((0 - (2 * fConst81)) * cosf((16514.724261390824f / fConst0)));
		fConst83 = faustpower<2>(fConst81);
		fConst84 = powf(0.001f,(1.0f / float((2.223381781799759f * fConst0))));
		fConst85 = ((0 - (2 * fConst84)) * cosf((17037.296783388952f / fConst0)));
		fConst86 = faustpower<2>(fConst84);
		fConst87 = powf(0.001f,(1.0f / float((2.2200415623386314f * fConst0))));
		fConst88 = ((0 - (2 * fConst87)) * cosf((17042.888818312342f / fConst0)));
		fConst89 = faustpower<2>(fConst87);
		fConst90 = powf(0.001f,(1.0f / float((1.827542785362976f * fConst0))));
		fConst91 = ((0 - (2 * fConst90)) * cosf((17738.877254788622f / fConst0)));
		fConst92 = faustpower<2>(fConst90);
		fConst93 = powf(0.001f,(1.0f / float((1.8142530679057502f * fConst0))));
		fConst94 = ((0 - (2 * fConst93)) * cosf((17763.947164164267f / fConst0)));
		fConst95 = faustpower<2>(fConst93);
		fConst96 = powf(0.001f,(1.0f / float((1.6963264523608588f * fConst0))));
		fConst97 = ((0 - (2 * fConst96)) * cosf((17991.398472284171f / fConst0)));
		fConst98 = faustpower<2>(fConst96);
		fConst99 = powf(0.001f,(1.0f / float((1.6621561524100801f * fConst0))));
		fConst100 = ((0 - (2 * fConst99)) * cosf((18059.068378042495f / fConst0)));
		fConst101 = faustpower<2>(fConst99);
		fConst102 = powf(0.001f,(1.0f / float((1.5124892449600522f * fConst0))));
		fConst103 = ((0 - (2 * fConst102)) * cosf((18365.75065288593f / fConst0)));
		fConst104 = faustpower<2>(fConst102);
		fConst105 = powf(0.001f,(1.0f / float((1.5044863100420911f * fConst0))));
		fConst106 = ((0 - (2 * fConst105)) * cosf((18382.652421362243f / fConst0)));
		fConst107 = faustpower<2>(fConst105);
		fConst108 = powf(0.001f,(1.0f / float((1.2069585444670108f * fConst0))));
		fConst109 = ((0 - (2 * fConst108)) * cosf((19053.885107728238f / fConst0)));
		fConst110 = faustpower<2>(fConst108);
		fConst111 = powf(0.001f,(1.0f / float((1.1820525405111491f * fConst0))));
		fConst112 = ((0 - (2 * fConst111)) * cosf((19114.392182236377f / fConst0)));
		fConst113 = faustpower<2>(fConst111);
		fConst114 = powf(0.001f,(1.0f / float((0.79962147339677903f * fConst0))));
		fConst115 = ((0 - (2 * fConst114)) * cosf((20160.039881057208f / fConst0)));
		fConst116 = faustpower<2>(fConst114);
		fConst117 = powf(0.001f,(1.0f / float((0.47646622960512469f * fConst0))));
		fConst118 = ((0 - (2 * fConst117)) * cosf((21315.83181831289f / fConst0)));
		fConst119 = faustpower<2>(fConst117);
		fConst120 = powf(0.001f,(1.0f / float((0.34925200475519302f * fConst0))));
		fConst121 = ((0 - (2 * fConst120)) * cosf((21902.681326003465f / fConst0)));
		fConst122 = faustpower<2>(fConst120);
		fConst123 = powf(0.001f,(1.0f / float((0.33977085657473471f * fConst0))));
		fConst124 = ((0 - (2 * fConst123)) * cosf((21951.250348427962f / fConst0)));
		fConst125 = faustpower<2>(fConst123);
		fConst126 = powf(0.001f,(1.0f / float((0.28638466984116151f * fConst0))));
		fConst127 = ((0 - (2 * fConst126)) * cosf((22241.219350354302f / fConst0)));
		fConst128 = faustpower<2>(fConst126);
		fConst129 = powf(0.001f,(1.0f / float((0.2747175984026391f * fConst0))));
		fConst130 = ((0 - (2 * fConst129)) * cosf((22308.826424259551f / fConst0)));
		fConst131 = faustpower<2>(fConst129);
		fConst132 = powf(0.001f,(1.0f / float((0.15735562081214677f * fConst0))));
		fConst133 = ((0 - (2 * fConst132)) * cosf((23114.016621374616f / fConst0)));
		fConst134 = faustpower<2>(fConst132);
		fConst135 = powf(0.001f,(1.0f / float((0.12824110865059202f * fConst0))));
		fConst136 = ((0 - (2 * fConst135)) * cosf((23367.41748481317f / fConst0)));
		fConst137 = faustpower<2>(fConst135);
		fConst138 = powf(0.001f,(1.0f / float((0.12584796810332841f * fConst0))));
		fConst139 = ((0 - (2 * fConst138)) * cosf((23389.722792653658f / fConst0)));
		fConst140 = faustpower<2>(fConst138);
		fConst141 = powf(0.001f,(1.0f / float((0.087400365760330362f * fConst0))));
		fConst142 = ((0 - (2 * fConst141)) * cosf((23789.898864867926f / fConst0)));
		fConst143 = faustpower<2>(fConst141);
		fConst144 = powf(0.001f,(1.0f / float((0.085740209231991202f * fConst0))));
		fConst145 = ((0 - (2 * fConst144)) * cosf((23809.376739320182f / fConst0)));
		fConst146 = faustpower<2>(fConst144);
		fConst147 = powf(0.001f,(1.0f / float((0.014612222244971888f * fConst0))));
		fConst148 = ((0 - (2 * fConst147)) * cosf((25092.466010899323f / fConst0)));
		fConst149 = faustpower<2>(fConst147);
		fConst150 = powf(0.001f,(1.0f / float((0.013737118934548435f * fConst0))));
		fConst151 = ((0 - (2 * fConst150)) * cosf((25122.87662778607f / fConst0)));
		fConst152 = faustpower<2>(fConst150);
		fConst153 = powf(0.001f,(1.0f / float((0.0010255132363247515f * fConst0))));
		fConst154 = ((0 - (2 * fConst153)) * cosf((25908.149127477376f / fConst0)));
		fConst155 = faustpower<2>(fConst153);
		fConst156 = powf(0.001f,(1.0f / float((0.00010099624633845641f * fConst0))));
		fConst157 = ((0 - (2 * fConst156)) * cosf((26168.398662900756f / fConst0)));
		fConst158 = faustpower<2>(fConst156);
		fConst159 = powf(0.001f,(1.0f / float((8.2805138300926982e-07f * fConst0))));
		fConst160 = ((0 - (2 * fConst159)) * cosf((26313.854402761961f / fConst0)));
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
		ui_interface->openVerticalBox("standardBell");
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


float 	mydsp::SIG0::fWave0[350] = {0.69191100000000005f,0.62233300000000003f,0.548651f,0.463306f,0.82694599999999996f,0.74951299999999998f,0.22420000000000001f,0.64267799999999997f,0.76044199999999995f,0.32605400000000001f,0.27646300000000001f,0.359344f,0.18257999999999999f,0.68676499999999996f,0.45715899999999998f,0.83901499999999996f,0.84533800000000003f,0.37237700000000001f,0.30641699999999999f,0.14738100000000001f,0.359707f,0.65353700000000003f,0.27553f,0.40123300000000001f,0.435417f,0.25148100000000001f,0.19006200000000001f,0.77337199999999995f,0.31501400000000002f,0.22881199999999999f,0.52151199999999998f,0.41154200000000002f,0.72076200000000001f,1,0.28650199999999998f,0.33893800000000002f,0.119995f,0.43228899999999998f,0.40967700000000001f,0.15627199999999999f,0.298871f,0.25078600000000001f,0.64077600000000001f,0.20943100000000001f,0.17000999999999999f,0.39001400000000003f,0.30169800000000002f,0.79941300000000004f,0.98058100000000004f,0.38500000000000001f,0.82543999999999995f,0.81889400000000001f,0.34961599999999998f,0.23539599999999999f,0.78316399999999997f,0.82191400000000003f,0.28410999999999997f,0.430286f,0.50767099999999998f,0.32625399999999999f,0.260488f,0.273364f,0.20518f,0.71485200000000004f,0.47994999999999999f,0.80363700000000005f,0.68394299999999997f,0.35537099999999999f,0.40692400000000001f,0.65625699999999998f,0.42302499999999998f,0.41351500000000002f,0.38635999999999998f,0.38478699999999999f,0.38944800000000002f,0.81336699999999995f,0.234988f,1,0.31126799999999999f,0.35024499999999997f,0.40385599999999999f,0.64614300000000002f,0.50048499999999996f,0.83355299999999999f,0.43176799999999999f,0.46706399999999998f,0.29897899999999999f,0.48741299999999999f,0.514907f,0.36938300000000002f,0.106197f,0.494224f,0.816079f,0.53580700000000003f,0.37987300000000002f,0.38020100000000001f,0.60630600000000001f,0.51611700000000005f,0.74844900000000003f,0.556948f,0.58706599999999998f,0.58442300000000003f,0.39486599999999999f,0.34112100000000001f,0.43345800000000001f,0.45598699999999998f,0.36123699999999997f,0.42938999999999999f,0.12296899999999999f,0.13317499999999999f,0.50517599999999996f,0.51398500000000003f,0.055461900000000001f,0.60494199999999998f,0.37207400000000002f,0.38112600000000002f,0.31435400000000002f,0.49963600000000002f,0.51871100000000003f,0.92379199999999995f,0.259544f,0.57651699999999995f,0.55391500000000005f,0.58544399999999996f,0.245369f,1,0.117757f,0.97731800000000002f,0.65286200000000005f,0.50931400000000004f,0.14854999999999999f,0.50640200000000002f,0.180059f,0.35600500000000002f,0.38680999999999999f,0.27935399999999999f,0.205792f,0.55105499999999996f,0.68910700000000003f,0.44572400000000001f,0.30685699999999999f,0.32474700000000001f,0.60362099999999996f,0.39446599999999998f,0.28861300000000001f,0.26469700000000002f,0.60611999999999999f,0.20274f,0.26727099999999998f,0.92565600000000003f,0.43922800000000001f,0.42588399999999998f,0.626633f,0.54720400000000002f,0.230022f,0.22565399999999999f,0.39269700000000002f,0.49347400000000002f,0.14985699999999999f,0.060404800000000002f,0.69388899999999998f,0.74027100000000001f,0.175485f,0.70499800000000001f,0.32973200000000003f,0.153026f,0.12574399999999999f,0.286995f,0.27887800000000001f,0.81237199999999998f,0.056217400000000001f,0.241479f,0.29452499999999998f,0.35883399999999999f,0.171047f,0.84760400000000002f,0.17227999999999999f,0.97521000000000002f,0.892073f,0.61398699999999995f,0.065921300000000002f,0.30158299999999999f,0.061084699999999999f,0.12543799999999999f,0.145151f,0.180086f,0.12423099999999999f,0.26016099999999998f,0.33757300000000001f,0.20374300000000001f,0.65579799999999999f,0.42589300000000002f,0.90234700000000001f,0.50068599999999996f,0.31117299999999998f,0.215561f,0.34959099999999999f,0.085421800000000006f,0.0805062f,1,0.33865200000000001f,0.29539599999999999f,0.69831399999999999f,0.66497200000000001f,0.11898300000000001f,0.088190500000000005f,0.31158000000000002f,0.39113599999999998f,0.15191499999999999f,0.23950399999999999f,0.68574199999999996f,0.88433200000000001f,0.28851599999999999f,0.76868800000000004f,0.27485100000000001f,0.049031100000000001f,0.035786499999999999f,0.29330299999999998f,0.24946099999999999f,0.49377100000000002f,0.34098400000000001f,0.46762300000000001f,0.21663099999999999f,0.25523499999999999f,0.098869499999999999f,0.46198f,0.14724699999999999f,0.64019599999999999f,1,0.55193800000000004f,0.045373200000000002f,0.18990699999999999f,0.0197542f,0.0309217f,0.76983699999999999f,0.36041800000000002f,0.38404100000000002f,0.86743400000000004f,0.39894800000000002f,0.171848f,0.74865199999999998f,0.30195699999999998f,0.86061100000000001f,0.95867400000000003f,0.54903000000000002f,0.27275300000000002f,0.372753f,0.0180728f,0.029235299999999999f,0.85019999999999996f,0.224583f,0.214805f,0.670319f,0.58643299999999998f,0.043514200000000003f,0.0388574f,0.144811f,0.15706100000000001f,0.15556900000000001f,0.41833399999999998f,0.67365600000000003f,0.74957300000000004f,0.33735399999999999f,0.74725399999999997f,0.25599699999999997f,0.0239656f,0.0310719f,0.72108700000000003f,0.70061600000000002f,0.19905100000000001f,0.51184399999999997f,0.84948500000000005f,0.70068200000000003f,0.77865799999999996f,0.171289f,0.26197300000000001f,0.12922800000000001f,0.32859699999999997f,0.78182099999999999f,0.58381300000000003f,0.080671300000000001f,0.41687600000000002f,0.011820199999999999f,0.0086856299999999997f,1,0.46188400000000002f,0.18688199999999999f,0.64136400000000005f,0.99470499999999995f,0.50190199999999996f,0.56644899999999998f,0.0678845f,0.139737f,0.46258199999999999f,0.31865599999999999f,0.23394699999999999f,0.49594100000000002f,0.031402800000000002f,0.014647800000000001f,0.70431999999999995f,0.12495299999999999f,0.132549f,0.45712599999999998f,0.37863599999999997f,0.016936199999999998f,0.019549400000000001f,0.204155f,0.29440100000000002f,0.27136700000000002f,0.73085699999999998f,0.45932200000000001f,0.43307800000000002f,0.32517099999999999f,0.73453599999999997f,0.41620499999999999f,0.012873000000000001f,0.038848899999999999f,0.82156700000000005f,0.86368299999999998f,0.092053099999999999f,0.39397199999999999f,0.53954400000000002f,0.83205200000000001f,0.84273200000000004f,0.241144f,0.47955799999999998f,0.28309200000000001f,0.47784500000000002f,0.38547300000000001f,0.436587f,0.14430799999999999f,0.64239500000000005f,0.0215791f,0.0077902900000000001f,0.56371400000000005f,0.838279f,0.41000399999999998f,0.82908599999999999f,1,0.63059799999999999f,0.023372899999999999f,0.49621700000000002f,0.71104199999999995f,0.91426600000000002f,0.69504200000000005f,0.33189400000000002f,0.89844199999999996f,0.028568f,0.017496600000000001f,0.482846f};
float 	mydsp::ftbl0[350];
