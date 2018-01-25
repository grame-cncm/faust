//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "GermanChurchBell"
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
		m->declare("description", "German church bell physical model.");
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
		m->declare("name", "GermanChurchBell");
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
		fConst12 = powf(0.001f,(1.0f / float((0.0064329863032784318f * fConst0))));
		fConst13 = faustpower<2>(fConst12);
		fConst14 = ((0 - (2 * fConst12)) * cosf((12240.90161544727f / fConst0)));
		fConst15 = powf(0.001f,(1.0f / float((0.0024973530493694698f * fConst0))));
		fConst16 = ((0 - (2 * fConst15)) * cosf((12376.995409200779f / fConst0)));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((0.00049788746261603426f * fConst0))));
		fConst19 = ((0 - (2 * fConst18)) * cosf((12517.613096375459f / fConst0)));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((9.5980556367937377e-06f * fConst0))));
		fConst22 = ((0 - (2 * fConst21)) * cosf((12640.82636024925f / fConst0)));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((21.889564882066438f * fConst0))));
		fConst25 = ((0 - (2 * fConst24)) * cosf((1501.1095185529678f / fConst0)));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((21.848776321176928f * fConst0))));
		fConst28 = ((0 - (2 * fConst27)) * cosf((1509.4410222702879f / fConst0)));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((17.096952816214348f * fConst0))));
		fConst31 = ((0 - (2 * fConst30)) * cosf((2552.5440310417071f / fConst0)));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((17.044882409103749f * fConst0))));
		fConst34 = ((0 - (2 * fConst33)) * cosf((2564.8842069850075f / fConst0)));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((13.279117003716509f * fConst0))));
		fConst37 = ((0 - (2 * fConst36)) * cosf((3525.5266917850017f / fConst0)));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((13.237699485362832f * fConst0))));
		fConst40 = ((0 - (2 * fConst39)) * cosf((3536.9495226734543f / fConst0)));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((9.3884575777665447f * fConst0))));
		fConst43 = ((0 - (2 * fConst42)) * cosf((4710.0767681916468f / fConst0)));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((9.3838651744883457f * fConst0))));
		fConst46 = ((0 - (2 * fConst45)) * cosf((4711.6349981478279f / fConst0)));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((8.811310358836641f * fConst0))));
		fConst49 = ((0 - (2 * fConst48)) * cosf((4909.6118839917499f / fConst0)));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((8.4713937323952262f * fConst0))));
		fConst52 = ((0 - (2 * fConst51)) * cosf((5030.820811752551f / fConst0)));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((8.4563049106570123f * fConst0))));
		fConst55 = ((0 - (2 * fConst54)) * cosf((5036.2683334138756f / fConst0)));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((7.0866377360250059f * fConst0))));
		fConst58 = ((0 - (2 * fConst57)) * cosf((5557.3894396060432f / fConst0)));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((6.2133242330329983f * fConst0))));
		fConst61 = ((0 - (2 * fConst60)) * cosf((5922.0278157229031f / fConst0)));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((6.2105054254257848f * fConst0))));
		fConst64 = ((0 - (2 * fConst63)) * cosf((5923.2530368578036f / fConst0)));
		fConst65 = faustpower<2>(fConst63);
		fConst66 = powf(0.001f,(1.0f / float((5.9838622037054821f * fConst0))));
		fConst67 = ((0 - (2 * fConst66)) * cosf((6022.8792230884437f / fConst0)));
		fConst68 = faustpower<2>(fConst66);
		fConst69 = powf(0.001f,(1.0f / float((5.9554920491180159f * fConst0))));
		fConst70 = ((0 - (2 * fConst69)) * cosf((6035.5084255558741f / fConst0)));
		fConst71 = faustpower<2>(fConst69);
		fConst72 = powf(0.001f,(1.0f / float((5.1935558480870316f * fConst0))));
		fConst73 = ((0 - (2 * fConst72)) * cosf((6389.1826433117058f / fConst0)));
		fConst74 = faustpower<2>(fConst72);
		fConst75 = powf(0.001f,(1.0f / float((5.1751396434752781f * fConst0))));
		fConst76 = ((0 - (2 * fConst75)) * cosf((6398.1047664479011f / fConst0)));
		fConst77 = faustpower<2>(fConst75);
		fConst78 = powf(0.001f,(1.0f / float((5.1234738584617077f * fConst0))));
		fConst79 = ((0 - (2 * fConst78)) * cosf((6423.2375076766193f / fConst0)));
		fConst80 = faustpower<2>(fConst78);
		fConst81 = powf(0.001f,(1.0f / float((3.0732140411045421f * fConst0))));
		fConst82 = ((0 - (2 * fConst81)) * cosf((7578.7781175200171f / fConst0)));
		fConst83 = faustpower<2>(fConst81);
		fConst84 = powf(0.001f,(1.0f / float((3.0668686733740405f * fConst0))));
		fConst85 = ((0 - (2 * fConst84)) * cosf((7582.9878516758263f / fConst0)));
		fConst86 = faustpower<2>(fConst84);
		fConst87 = powf(0.001f,(1.0f / float((3.0004831439337836f * fConst0))));
		fConst88 = ((0 - (2 * fConst87)) * cosf((7627.3471399445152f / fConst0)));
		fConst89 = faustpower<2>(fConst87);
		fConst90 = powf(0.001f,(1.0f / float((2.9185860398219567f * fConst0))));
		fConst91 = ((0 - (2 * fConst90)) * cosf((7682.8904980599827f / fConst0)));
		fConst92 = faustpower<2>(fConst90);
		fConst93 = powf(0.001f,(1.0f / float((2.8374126227662084f * fConst0))));
		fConst94 = ((0 - (2 * fConst93)) * cosf((7738.8736791469528f / fConst0)));
		fConst95 = faustpower<2>(fConst93);
		fConst96 = powf(0.001f,(1.0f / float((1.9171860109386616f * fConst0))));
		fConst97 = ((0 - (2 * fConst96)) * cosf((8454.9683086062105f / fConst0)));
		fConst98 = faustpower<2>(fConst96);
		fConst99 = powf(0.001f,(1.0f / float((1.8498652282754398f * fConst0))));
		fConst100 = ((0 - (2 * fConst99)) * cosf((8514.8470645836314f / fConst0)));
		fConst101 = faustpower<2>(fConst99);
		fConst102 = powf(0.001f,(1.0f / float((1.840305940369545f * fConst0))));
		fConst103 = ((0 - (2 * fConst102)) * cosf((8523.4550284544675f / fConst0)));
		fConst104 = faustpower<2>(fConst102);
		fConst105 = powf(0.001f,(1.0f / float((1.8350853357245294f * fConst0))));
		fConst106 = ((0 - (2 * fConst105)) * cosf((8528.1674174348518f / fConst0)));
		fConst107 = faustpower<2>(fConst105);
		fConst108 = powf(0.001f,(1.0f / float((1.6206253956036778f * fConst0))));
		fConst109 = ((0 - (2 * fConst108)) * cosf((8729.1665154115271f / fConst0)));
		fConst110 = faustpower<2>(fConst108);
		fConst111 = powf(0.001f,(1.0f / float((1.6089025933747316f * fConst0))));
		fConst112 = ((0 - (2 * fConst111)) * cosf((8740.6019126705942f / fConst0)));
		fConst113 = faustpower<2>(fConst111);
		fConst114 = powf(0.001f,(1.0f / float((1.4285855867001482f * fConst0))));
		fConst115 = ((0 - (2 * fConst114)) * cosf((8923.1912776972331f / fConst0)));
		fConst116 = faustpower<2>(fConst114);
		fConst117 = powf(0.001f,(1.0f / float((1.4054782222168165f * fConst0))));
		fConst118 = ((0 - (2 * fConst117)) * cosf((8947.5700366890887f / fConst0)));
		fConst119 = faustpower<2>(fConst117);
		fConst120 = powf(0.001f,(1.0f / float((1.4039378683592962f * fConst0))));
		fConst121 = ((0 - (2 * fConst120)) * cosf((8949.2036648689555f / fConst0)));
		fConst122 = faustpower<2>(fConst120);
		fConst123 = powf(0.001f,(1.0f / float((1.3907679672128541f * fConst0))));
		fConst124 = ((0 - (2 * fConst123)) * cosf((8963.2151681039668f / fConst0)));
		fConst125 = faustpower<2>(fConst123);
		fConst126 = powf(0.001f,(1.0f / float((0.64671515358313036f * fConst0))));
		fConst127 = ((0 - (2 * fConst126)) * cosf((9941.8841115502582f / fConst0)));
		fConst128 = faustpower<2>(fConst126);
		fConst129 = powf(0.001f,(1.0f / float((0.48027650862273052f * fConst0))));
		fConst130 = ((0 - (2 * fConst129)) * cosf((10248.315058981407f / fConst0)));
		fConst131 = faustpower<2>(fConst129);
		fConst132 = powf(0.001f,(1.0f / float((0.4585482814741117f * fConst0))));
		fConst133 = ((0 - (2 * fConst132)) * cosf((10292.80001095624f / fConst0)));
		fConst134 = faustpower<2>(fConst132);
		fConst135 = powf(0.001f,(1.0f / float((0.24890652875828637f * fConst0))));
		fConst136 = ((0 - (2 * fConst135)) * cosf((10808.838020234898f / fConst0)));
		fConst137 = faustpower<2>(fConst135);
		fConst138 = powf(0.001f,(1.0f / float((0.23565788231448603f * fConst0))));
		fConst139 = ((0 - (2 * fConst138)) * cosf((10849.176069906991f / fConst0)));
		fConst140 = faustpower<2>(fConst138);
		fConst141 = powf(0.001f,(1.0f / float((0.1089186248893748f * fConst0))));
		fConst142 = ((0 - (2 * fConst141)) * cosf((11333.546825237465f / fConst0)));
		fConst143 = faustpower<2>(fConst141);
		fConst144 = powf(0.001f,(1.0f / float((0.081559113868941283f * fConst0))));
		fConst145 = ((0 - (2 * fConst144)) * cosf((11479.882211041679f / fConst0)));
		fConst146 = faustpower<2>(fConst144);
		fConst147 = powf(0.001f,(1.0f / float((0.079048200416298897f * fConst0))));
		fConst148 = ((0 - (2 * fConst147)) * cosf((11494.710528366622f / fConst0)));
		fConst149 = faustpower<2>(fConst147);
		fConst150 = powf(0.001f,(1.0f / float((0.014093428849302854f * fConst0))));
		fConst151 = ((0 - (2 * fConst150)) * cosf((12081.748531616411f / fConst0)));
		fConst152 = faustpower<2>(fConst150);
		fConst153 = powf(0.001f,(1.0f / float((0.012618132421747266f * fConst0))));
		fConst154 = ((0 - (2 * fConst153)) * cosf((12107.321095816633f / fConst0)));
		fConst155 = faustpower<2>(fConst153);
		fConst156 = powf(0.001f,(1.0f / float((0.0082629862538303057f * fConst0))));
		fConst157 = ((0 - (2 * fConst156)) * cosf((12195.41135382329f / fConst0)));
		fConst158 = faustpower<2>(fConst156);
		fConst159 = powf(0.001f,(1.0f / float((0.0073414942084404911f * fConst0))));
		fConst160 = ((0 - (2 * fConst159)) * cosf((12217.46533425149f / fConst0)));
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
		ui_interface->openVerticalBox("germanBell");
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
		float 	fSlow1 = ftbl0[int((iSlow0 + 46))];
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
		float 	fSlow14 = ftbl0[int((iSlow0 + 47))];
		float 	fSlow15 = ftbl0[int((iSlow0 + 48))];
		float 	fSlow16 = ftbl0[int((iSlow0 + 49))];
		float 	fSlow17 = ftbl0[int(iSlow0)];
		float 	fSlow18 = ftbl0[int((iSlow0 + 1))];
		float 	fSlow19 = ftbl0[int((iSlow0 + 2))];
		float 	fSlow20 = ftbl0[int((iSlow0 + 3))];
		float 	fSlow21 = ftbl0[int((iSlow0 + 4))];
		float 	fSlow22 = ftbl0[int((iSlow0 + 5))];
		float 	fSlow23 = ftbl0[int((iSlow0 + 6))];
		float 	fSlow24 = ftbl0[int((iSlow0 + 7))];
		float 	fSlow25 = ftbl0[int((iSlow0 + 8))];
		float 	fSlow26 = ftbl0[int((iSlow0 + 9))];
		float 	fSlow27 = ftbl0[int((iSlow0 + 10))];
		float 	fSlow28 = ftbl0[int((iSlow0 + 11))];
		float 	fSlow29 = ftbl0[int((iSlow0 + 12))];
		float 	fSlow30 = ftbl0[int((iSlow0 + 13))];
		float 	fSlow31 = ftbl0[int((iSlow0 + 14))];
		float 	fSlow32 = ftbl0[int((iSlow0 + 15))];
		float 	fSlow33 = ftbl0[int((iSlow0 + 16))];
		float 	fSlow34 = ftbl0[int((iSlow0 + 17))];
		float 	fSlow35 = ftbl0[int((iSlow0 + 18))];
		float 	fSlow36 = ftbl0[int((iSlow0 + 19))];
		float 	fSlow37 = ftbl0[int((iSlow0 + 20))];
		float 	fSlow38 = ftbl0[int((iSlow0 + 21))];
		float 	fSlow39 = ftbl0[int((iSlow0 + 22))];
		float 	fSlow40 = ftbl0[int((iSlow0 + 23))];
		float 	fSlow41 = ftbl0[int((iSlow0 + 24))];
		float 	fSlow42 = ftbl0[int((iSlow0 + 25))];
		float 	fSlow43 = ftbl0[int((iSlow0 + 26))];
		float 	fSlow44 = ftbl0[int((iSlow0 + 27))];
		float 	fSlow45 = ftbl0[int((iSlow0 + 28))];
		float 	fSlow46 = ftbl0[int((iSlow0 + 29))];
		float 	fSlow47 = ftbl0[int((iSlow0 + 30))];
		float 	fSlow48 = ftbl0[int((iSlow0 + 31))];
		float 	fSlow49 = ftbl0[int((iSlow0 + 32))];
		float 	fSlow50 = ftbl0[int((iSlow0 + 33))];
		float 	fSlow51 = ftbl0[int((iSlow0 + 34))];
		float 	fSlow52 = ftbl0[int((iSlow0 + 35))];
		float 	fSlow53 = ftbl0[int((iSlow0 + 36))];
		float 	fSlow54 = ftbl0[int((iSlow0 + 37))];
		float 	fSlow55 = ftbl0[int((iSlow0 + 38))];
		float 	fSlow56 = ftbl0[int((iSlow0 + 39))];
		float 	fSlow57 = ftbl0[int((iSlow0 + 40))];
		float 	fSlow58 = ftbl0[int((iSlow0 + 41))];
		float 	fSlow59 = ftbl0[int((iSlow0 + 42))];
		float 	fSlow60 = ftbl0[int((iSlow0 + 43))];
		float 	fSlow61 = ftbl0[int((iSlow0 + 44))];
		float 	fSlow62 = ftbl0[int((iSlow0 + 45))];
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
			fRec0[0] = (fTempPerm2 - ((fConst13 * fRec0[2]) + (fConst14 * fRec0[1])));
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


float 	mydsp::SIG0::fWave0[350] = {0.76141099999999995f,0.79780300000000004f,0.58605700000000005f,0.22503899999999999f,0.92635400000000001f,0.81387500000000002f,0.52987099999999998f,0.158915f,0.66251599999999999f,0.30841000000000002f,0.045478499999999998f,0.55608199999999997f,0.78471299999999999f,0.213035f,0.95622700000000005f,0.79516500000000001f,0.31350800000000001f,0.15853100000000001f,0.30158600000000002f,0.16832f,0.28126699999999999f,0.15423700000000001f,0.21723500000000001f,0.24723899999999999f,0.52268800000000004f,0.17030300000000001f,0.32061400000000001f,0.15485699999999999f,0.414941f,0.78836399999999995f,0.71329900000000002f,0.38159199999999999f,0.70701099999999995f,1,0.0106946f,0.359763f,0.074615600000000004f,0.43112400000000001f,0.11805300000000001f,0.52729000000000004f,0.255303f,0.64685499999999996f,0.20114499999999999f,0.91990799999999995f,0.35938900000000001f,0.253494f,0.86569499999999999f,0.082926299999999994f,0.22258900000000001f,0.041573600000000002f,0.73577400000000004f,0.76967799999999997f,0.38141599999999998f,0.197543f,0.68238900000000002f,0.61476600000000003f,0.249525f,0.289883f,0.300319f,0.443691f,0.27527200000000002f,0.37021799999999999f,0.74878999999999996f,0.161247f,0.63435299999999994f,0.498498f,0.22198799999999999f,0.35063699999999998f,0.43681700000000001f,0.43646299999999999f,0.52507999999999999f,0.84264600000000001f,0.195324f,0.22475500000000001f,0.54568099999999997f,0.35377799999999998f,0.26904400000000001f,0.32781399999999999f,0.44895200000000002f,0.85230499999999998f,0.38050299999999998f,1,0.458063f,0.56505799999999995f,0.35463499999999998f,0.65952900000000003f,0.44948500000000002f,0.802014f,0.28344599999999998f,0.521563f,0.374639f,0.65211200000000002f,0.18104200000000001f,0.46839399999999998f,0.430116f,0.15720700000000001f,0.414995f,0.29273700000000002f,0.48778500000000002f,0.47767999999999999f,0.48144500000000001f,0.55698800000000004f,0.56113199999999996f,0.37826500000000002f,0.291462f,0.32324999999999998f,0.48260199999999998f,0.32824799999999998f,0.19679199999999999f,0.71225400000000005f,0.38980599999999999f,0.307751f,0.79287600000000003f,0.199098f,0.28883799999999998f,0.146811f,0.0178444f,0.39401700000000001f,0.58821199999999996f,0.48922599999999999f,0.70148600000000005f,0.940303f,0.21319099999999999f,0.077884499999999995f,0.47446300000000002f,0.60997199999999996f,0.16338f,0.40837600000000002f,0.33086399999999999f,0.88998999999999995f,0.079810099999999995f,1,0.16717199999999999f,0.208727f,0.227549f,0.82590300000000005f,0.53189699999999995f,0.58094599999999996f,0.215339f,0.24731900000000001f,0.268148f,0.50408799999999998f,0.16095499999999999f,0.170316f,0.230769f,0.15119099999999999f,0.082503099999999996f,0.14132800000000001f,0.28807899999999997f,0.49967600000000001f,0.42035499999999998f,0.48776399999999998f,0.75370999999999999f,0.49224800000000002f,0.181364f,0.20594000000000001f,0.52497000000000005f,0.32564100000000001f,0.23682700000000001f,0.93184199999999995f,0.47298099999999998f,0.312162f,0.90103200000000006f,0.270478f,0.16711200000000001f,0.0709698f,0.16600400000000001f,0.29074499999999998f,0.42589300000000002f,0.40363300000000002f,0.58177199999999996f,0.85569399999999995f,0.032558700000000003f,0.056835900000000002f,0.241923f,0.79930999999999996f,0.18196200000000001f,0.53028299999999995f,0.41560999999999998f,1,0.029150100000000002f,0.83115499999999998f,0.119755f,0.102188f,0.13203699999999999f,0.76602999999999999f,0.44222099999999998f,0.1749f,0.142175f,0.014079400000000001f,0.4375f,0.85185999999999995f,0.19683600000000001f,0.090752200000000005f,0.55167299999999997f,0.25652799999999998f,0.042437700000000002f,0.49036299999999999f,0.108178f,0.50327599999999995f,0.22658400000000001f,0.31275799999999998f,0.82407900000000001f,0.48411999999999999f,0.034733800000000002f,0.061942799999999999f,0.25509700000000002f,0.14527300000000001f,0.190359f,0.99529699999999999f,0.50341999999999998f,0.21757499999999999f,0.79397499999999999f,0.35717900000000002f,0.040972799999999997f,0.0187931f,0.41445799999999999f,0.15844f,0.34623300000000001f,0.077167299999999994f,0.17511099999999999f,0.38056699999999999f,0.49740899999999999f,0.316164f,0.48866900000000002f,1,0.420657f,0.44233299999999998f,0.24706f,0.79640699999999998f,0.0104146f,0.227079f,0.10684f,0.028987300000000001f,0.76756999999999997f,0.0643122f,0.042309800000000002f,0.71552199999999999f,0.47211700000000001f,0.39257700000000001f,0.66043300000000005f,0.80357500000000004f,0.18865299999999999f,0.0191653f,0.87321199999999999f,0.44871899999999998f,0.0147128f,0.61896700000000004f,0.30718000000000001f,0.34589900000000001f,0.13139400000000001f,0.19322500000000001f,0.715283f,0.40561999999999998f,0.040637f,0.050333599999999999f,0.054433099999999998f,0.045202300000000001f,0.15230199999999999f,0.89454900000000004f,0.44334299999999999f,0.172071f,0.64766699999999999f,0.32899299999999998f,0.041601399999999997f,0.022948799999999998f,0.55107099999999998f,0.42354399999999998f,0.86236199999999996f,0.36352600000000002f,0.76992899999999997f,0.12345200000000001f,0.71070199999999994f,0.394895f,0.55663799999999997f,1,0.45092500000000002f,0.42284899999999997f,0.092187000000000005f,0.41389199999999998f,0.0099537199999999992f,0.32114599999999999f,0.16062399999999999f,0.0300681f,0.915385f,0.47549999999999998f,0.50695100000000004f,0.38754899999999998f,0.27559099999999997f,0.468281f,0.184776f,0.186837f,0.188195f,0.020278500000000001f,0.69713599999999998f,0.408862f,0.011693500000000001f,0.349823f,0.20230100000000001f,0.46137899999999998f,0.055902300000000002f,0.058257099999999999f,0.26060800000000001f,0.18187500000000001f,0.027173900000000001f,0.024957799999999999f,0.68508899999999995f,0.47038400000000002f,0.283194f,0.33105000000000001f,0.138349f,0.33806799999999998f,0.48199199999999998f,0.17824200000000001f,0.015594200000000001f,0.011043499999999999f,0.783771f,0.44270700000000002f,0.61647799999999997f,0.38154199999999999f,0.51089200000000001f,0.045984999999999998f,0.30311900000000003f,0.073190900000000003f,0.54771499999999995f,0.348941f,0.149981f,0.30215799999999998f,0.28448200000000001f,0.398177f,0.0041304899999999997f,0.18073900000000001f,0.062839000000000006f,0.013345900000000001f,0.34708800000000001f,0.57637000000000005f,0.24076400000000001f,0.97848100000000005f,0.45275500000000002f,0.52974200000000005f,0.34047100000000002f,0.66228200000000004f,0.44430500000000001f,0.042990100000000003f,1,0.36193999999999998f,0.018337200000000001f,0.62689300000000003f,0.55284999999999995f,0.384936f};
float 	mydsp::ftbl0[350];
