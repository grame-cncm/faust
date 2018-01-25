//----------------------------------------------------------
// copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
// license: "MIT"
// name: "ChurchBell"
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
		m->declare("description", "Generic church bell physical model.");
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
		m->declare("name", "ChurchBell");
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
		fConst12 = powf(0.001f,(1.0f / float((22.293035422721548f * fConst0))));
		fConst13 = ((0 - (2 * fConst12)) * cosf((2839.4845376499843f / fConst0)));
		fConst14 = faustpower<2>(fConst12);
		fConst15 = powf(0.001f,(1.0f / float((22.245133649714504f * fConst0))));
		fConst16 = ((0 - (2 * fConst15)) * cosf((2858.8493147667118f / fConst0)));
		fConst17 = faustpower<2>(fConst15);
		fConst18 = powf(0.001f,(1.0f / float((16.417805830211599f * fConst0))));
		fConst19 = ((0 - (2 * fConst18)) * cosf((5432.7121935556788f / fConst0)));
		fConst20 = faustpower<2>(fConst18);
		fConst21 = powf(0.001f,(1.0f / float((16.330453498288815f * fConst0))));
		fConst22 = ((0 - (2 * fConst21)) * cosf((5475.1802430469061f / fConst0)));
		fConst23 = faustpower<2>(fConst21);
		fConst24 = powf(0.001f,(1.0f / float((13.858370062870259f * fConst0))));
		fConst25 = ((0 - (2 * fConst24)) * cosf((6738.5277463908906f / fConst0)));
		fConst26 = faustpower<2>(fConst24);
		fConst27 = powf(0.001f,(1.0f / float((13.840720423209111f * fConst0))));
		fConst28 = ((0 - (2 * fConst27)) * cosf((6748.0153562047317f / fConst0)));
		fConst29 = faustpower<2>(fConst27);
		fConst30 = powf(0.001f,(1.0f / float((11.429879627134644f * fConst0))));
		fConst31 = ((0 - (2 * fConst30)) * cosf((8119.3205494966769f / fConst0)));
		fConst32 = faustpower<2>(fConst30);
		fConst33 = powf(0.001f,(1.0f / float((11.427275675377377f * fConst0))));
		fConst34 = ((0 - (2 * fConst33)) * cosf((8120.891345823472f / fConst0)));
		fConst35 = faustpower<2>(fConst33);
		fConst36 = powf(0.001f,(1.0f / float((9.3444930036016327f * fConst0))));
		fConst37 = ((0 - (2 * fConst36)) * cosf((9453.6806131824051f / fConst0)));
		fConst38 = faustpower<2>(fConst36);
		fConst39 = powf(0.001f,(1.0f / float((9.0899010504006643f * fConst0))));
		fConst40 = ((0 - (2 * fConst39)) * cosf((9628.4159965750696f / fConst0)));
		fConst41 = faustpower<2>(fConst39);
		fConst42 = powf(0.001f,(1.0f / float((8.0917687148999082f * fConst0))));
		fConst43 = ((0 - (2 * fConst42)) * cosf((10343.379652679036f / fConst0)));
		fConst44 = faustpower<2>(fConst42);
		fConst45 = powf(0.001f,(1.0f / float((8.0849969073161052f * fConst0))));
		fConst46 = ((0 - (2 * fConst45)) * cosf((10348.406200924779f / fConst0)));
		fConst47 = faustpower<2>(fConst45);
		fConst48 = powf(0.001f,(1.0f / float((7.8266142781967414f * fConst0))));
		fConst49 = ((0 - (2 * fConst48)) * cosf((10542.116803945124f / fConst0)));
		fConst50 = faustpower<2>(fConst48);
		fConst51 = powf(0.001f,(1.0f / float((7.8241247228771087f * fConst0))));
		fConst52 = ((0 - (2 * fConst51)) * cosf((10544.001759537279f / fConst0)));
		fConst53 = faustpower<2>(fConst51);
		fConst54 = powf(0.001f,(1.0f / float((6.3525455252069429f * fConst0))));
		fConst55 = ((0 - (2 * fConst54)) * cosf((11728.382189940632f / fConst0)));
		fConst56 = faustpower<2>(fConst54);
		fConst57 = powf(0.001f,(1.0f / float((6.2400148361996539f * fConst0))));
		fConst58 = ((0 - (2 * fConst57)) * cosf((11825.457402936556f / fConst0)));
		fConst59 = faustpower<2>(fConst57);
		fConst60 = powf(0.001f,(1.0f / float((5.519576720440738f * fConst0))));
		fConst61 = ((0 - (2 * fConst60)) * cosf((12473.379471812916f / fConst0)));
		fConst62 = faustpower<2>(fConst60);
		fConst63 = powf(0.001f,(1.0f / float((5.4881994119314381f * fConst0))));
		fConst64 = ((0 - (2 * fConst63)) * cosf((12502.721947197442f / fConst0)));
		fConst65 = faustpower<2>(fConst63);
		fConst66 = powf(0.001f,(1.0f / float((4.6874370741121876f * fConst0))));
		fConst67 = ((0 - (2 * fConst66)) * cosf((13288.497101713321f / fConst0)));
		fConst68 = faustpower<2>(fConst66);
		fConst69 = powf(0.001f,(1.0f / float((3.3479693201684717f * fConst0))));
		fConst70 = ((0 - (2 * fConst69)) * cosf((14808.273963813921f / fConst0)));
		fConst71 = faustpower<2>(fConst69);
		fConst72 = powf(0.001f,(1.0f / float((2.9285413155179514f * fConst0))));
		fConst73 = ((0 - (2 * fConst72)) * cosf((15358.115510045207f / fConst0)));
		fConst74 = faustpower<2>(fConst72);
		fConst75 = powf(0.001f,(1.0f / float((2.9198065151994665f * fConst0))));
		fConst76 = ((0 - (2 * fConst75)) * cosf((15370.053562128845f / fConst0)));
		fConst77 = faustpower<2>(fConst75);
		fConst78 = powf(0.001f,(1.0f / float((2.5552851484167252f * fConst0))));
		fConst79 = ((0 - (2 * fConst78)) * cosf((15888.730509236522f / fConst0)));
		fConst80 = faustpower<2>(fConst78);
		fConst81 = powf(0.001f,(1.0f / float((2.5461789992429535f * fConst0))));
		fConst82 = ((0 - (2 * fConst81)) * cosf((15902.239357646959f / fConst0)));
		fConst83 = faustpower<2>(fConst81);
		fConst84 = powf(0.001f,(1.0f / float((2.0020811180747198f * fConst0))));
		fConst85 = ((0 - (2 * fConst84)) * cosf((16768.94193891931f / fConst0)));
		fConst86 = faustpower<2>(fConst84);
		fConst87 = powf(0.001f,(1.0f / float((1.9992621263952208f * fConst0))));
		fConst88 = ((0 - (2 * fConst87)) * cosf((16773.779991605839f / fConst0)));
		fConst89 = faustpower<2>(fConst87);
		fConst90 = powf(0.001f,(1.0f / float((1.7581746552766708f * fConst0))));
		fConst91 = ((0 - (2 * fConst90)) * cosf((17203.738362176136f / fConst0)));
		fConst92 = faustpower<2>(fConst90);
		fConst93 = powf(0.001f,(1.0f / float((1.7212443872671888f * fConst0))));
		fConst94 = ((0 - (2 * fConst93)) * cosf((17272.664904995898f / fConst0)));
		fConst95 = faustpower<2>(fConst93);
		fConst96 = powf(0.001f,(1.0f / float((1.7162311933626619f * fConst0))));
		fConst97 = ((0 - (2 * fConst96)) * cosf((17282.08968295667f / fConst0)));
		fConst98 = faustpower<2>(fConst96);
		fConst99 = powf(0.001f,(1.0f / float((1.7076290138606625f * fConst0))));
		fConst100 = ((0 - (2 * fConst99)) * cosf((17298.300301049192f / fConst0)));
		fConst101 = faustpower<2>(fConst99);
		fConst102 = powf(0.001f,(1.0f / float((1.4715872894147235f * fConst0))));
		fConst103 = ((0 - (2 * fConst102)) * cosf((17763.758668605056f / fConst0)));
		fConst104 = faustpower<2>(fConst102);
		fConst105 = powf(0.001f,(1.0f / float((1.425950116026103f * fConst0))));
		fConst106 = ((0 - (2 * fConst105)) * cosf((17858.823262302682f / fConst0)));
		fConst107 = faustpower<2>(fConst105);
		fConst108 = powf(0.001f,(1.0f / float((1.0185441657462206f * fConst0))));
		fConst109 = ((0 - (2 * fConst108)) * cosf((18802.809022853344f / fConst0)));
		fConst110 = faustpower<2>(fConst108);
		fConst111 = powf(0.001f,(1.0f / float((1.0081259968051075f * fConst0))));
		fConst112 = ((0 - (2 * fConst111)) * cosf((18829.701055968071f / fConst0)));
		fConst113 = faustpower<2>(fConst111);
		fConst114 = powf(0.001f,(1.0f / float((0.63417206923152292f * fConst0))));
		fConst115 = ((0 - (2 * fConst114)) * cosf((19934.096537411027f / fConst0)));
		fConst116 = faustpower<2>(fConst114);
		fConst117 = powf(0.001f,(1.0f / float((0.38223254243315624f * fConst0))));
		fConst118 = ((0 - (2 * fConst117)) * cosf((20927.970789300693f / fConst0)));
		fConst119 = faustpower<2>(fConst117);
		fConst120 = powf(0.001f,(1.0f / float((0.30653385969154728f * fConst0))));
		fConst121 = ((0 - (2 * fConst120)) * cosf((21302.071642490166f / fConst0)));
		fConst122 = faustpower<2>(fConst120);
		fConst123 = powf(0.001f,(1.0f / float((0.29158867722417398f * fConst0))));
		fConst124 = ((0 - (2 * fConst123)) * cosf((21382.307918862851f / fConst0)));
		fConst125 = faustpower<2>(fConst123);
		fConst126 = powf(0.001f,(1.0f / float((0.17796448112382104f * fConst0))));
		fConst127 = ((0 - (2 * fConst126)) * cosf((22094.381309725512f / fConst0)));
		fConst128 = faustpower<2>(fConst126);
		fConst129 = powf(0.001f,(1.0f / float((0.15961235681083921f * fConst0))));
		fConst130 = ((0 - (2 * fConst129)) * cosf((22233.302536867253f / fConst0)));
		fConst131 = faustpower<2>(fConst129);
		fConst132 = powf(0.001f,(1.0f / float((0.12641550103046229f * fConst0))));
		fConst133 = ((0 - (2 * fConst132)) * cosf((22511.333486709951f / fConst0)));
		fConst134 = faustpower<2>(fConst132);
		fConst135 = powf(0.001f,(1.0f / float((0.12569758522749719f * fConst0))));
		fConst136 = ((0 - (2 * fConst135)) * cosf((22517.805167576345f / fConst0)));
		fConst137 = faustpower<2>(fConst135);
		fConst138 = powf(0.001f,(1.0f / float((0.047267931806947078f * fConst0))));
		fConst139 = ((0 - (2 * fConst138)) * cosf((23436.532523192145f / fConst0)));
		fConst140 = faustpower<2>(fConst138);
		fConst141 = powf(0.001f,(1.0f / float((0.043747512958826597f * fConst0))));
		fConst142 = ((0 - (2 * fConst141)) * cosf((23495.028978401984f / fConst0)));
		fConst143 = faustpower<2>(fConst141);
		fConst144 = powf(0.001f,(1.0f / float((0.036959899444756021f * fConst0))));
		fConst145 = ((0 - (2 * fConst144)) * cosf((23616.357286683622f / fConst0)));
		fConst146 = faustpower<2>(fConst144);
		fConst147 = powf(0.001f,(1.0f / float((0.0057680450727207941f * fConst0))));
		fConst148 = ((0 - (2 * fConst147)) * cosf((24528.173138461527f / fConst0)));
		fConst149 = faustpower<2>(fConst147);
		fConst150 = powf(0.001f,(1.0f / float((0.0024090665013359789f * fConst0))));
		fConst151 = ((0 - (2 * fConst150)) * cosf((24772.023560233167f / fConst0)));
		fConst152 = faustpower<2>(fConst150);
		fConst153 = powf(0.001f,(1.0f / float((0.00061281548777665322f * fConst0))));
		fConst154 = ((0 - (2 * fConst153)) * cosf((25018.010265009245f / fConst0)));
		fConst155 = faustpower<2>(fConst153);
		fConst156 = powf(0.001f,(1.0f / float((0.00057064006521013923f * fConst0))));
		fConst157 = ((0 - (2 * fConst156)) * cosf((25027.497874823086f / fConst0)));
		fConst158 = faustpower<2>(fConst156);
		fConst159 = powf(0.001f,(1.0f / float((7.5977912197573418e-08f * fConst0))));
		fConst160 = ((0 - (2 * fConst159)) * cosf((25346.181033603236f / fConst0)));
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
		ui_interface->openVerticalBox("churchBell");
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


float 	mydsp::SIG0::fWave0[350] = {0.525285f,0.81417399999999995f,0.483261f,0.29674499999999998f,0.97505600000000003f,0.472244f,0.409501f,0.42536400000000002f,0.68755900000000003f,0.288381f,0.30928499999999998f,0.123054f,0.286333f,0.57670600000000005f,0.90832199999999996f,0.62697400000000003f,0.080185199999999998f,0.30983500000000003f,0.45143f,0.13284499999999999f,0.47063500000000003f,0.41700799999999999f,0.26511200000000001f,0.075280200000000005f,0.46346999999999999f,0.47181000000000001f,0.27532400000000001f,0.54702700000000004f,0.51251899999999995f,0.39407799999999998f,0.59540400000000004f,0.94130599999999998f,0.39250099999999999f,0.38143500000000002f,0.39123200000000002f,0.118924f,0.33949499999999999f,0.101421f,0.241755f,0.0873255f,0.378944f,0.63770499999999997f,0.17194599999999999f,0.14985899999999999f,0.23329f,0.54181000000000001f,1,0.115554f,0.244172f,0.57432899999999998f,0.60617100000000002f,0.93839700000000004f,0.39255499999999999f,0.27735900000000002f,0.86856999999999995f,0.43248900000000001f,0.408856f,0.40793200000000002f,0.299815f,0.25665900000000003f,0.54957199999999995f,0.40634700000000001f,0.31233100000000003f,0.62757799999999997f,0.67016699999999996f,0.524648f,0.40692600000000001f,0.63752399999999998f,0.55583700000000003f,1,0.81897900000000001f,0.70534699999999995f,0.67814099999999999f,0.42738199999999998f,0.674404f,0.63610500000000003f,0.64363499999999996f,0.69913599999999998f,0.83620099999999997f,0.61308499999999999f,0.319019f,0.72525899999999999f,0.54551899999999998f,0.47986099999999998f,0.49836000000000003f,0.48865399999999998f,0.86167199999999999f,0.31428699999999998f,0.67105199999999998f,0.53190499999999996f,0.42178100000000002f,0.81506599999999996f,0.77203200000000005f,0.48872199999999999f,0.089667399999999994f,0.29128599999999999f,0.65873000000000004f,0.63563199999999997f,0.67935699999999999f,0.45949699999999999f,0.36024f,0.58228899999999995f,0.65060499999999999f,0.49095f,0.38191000000000003f,0.15726100000000001f,0.47962399999999999f,0.477491f,0.17443500000000001f,0.013094f,0.87911300000000003f,0.60806899999999997f,0.26887699999999998f,0.60447899999999999f,0.24512999999999999f,0.17050699999999999f,0.29288799999999998f,0.54584900000000003f,0.47664600000000001f,0.92231600000000002f,0.66919200000000001f,0.578094f,0.57879700000000001f,0.31139600000000001f,0.60121000000000002f,0.54995499999999997f,1,0.66573000000000004f,0.98011499999999996f,0.53784799999999999f,0.074053099999999997f,0.25247199999999997f,0.25574999999999998f,0.22397400000000001f,0.086510299999999998f,0.138209f,0.19862299999999999f,0.045303400000000001f,0.43245299999999998f,0.29240699999999997f,0.39440999999999998f,0.85765899999999995f,0.27166800000000002f,0.201545f,0.58399400000000001f,0.060237800000000001f,0.19061800000000001f,0.84950499999999995f,0.97554200000000002f,0.17313999999999999f,0.20647199999999999f,0.34479300000000002f,0.76101099999999999f,0.55812499999999998f,0.117245f,0.033848499999999997f,0.33759699999999998f,0.336646f,0.17425299999999999f,0.23017000000000001f,0.93487299999999995f,0.59364700000000004f,0.39322499999999999f,0.68370399999999998f,0.056609300000000001f,0.040501200000000001f,0.14897199999999999f,0.33872200000000002f,0.28341899999999998f,0.394007f,0.23747499999999999f,0.26996399999999998f,0.428313f,0.17749899999999999f,0.46258500000000002f,0.443963f,0.98179300000000003f,0.40823900000000002f,0.67652699999999999f,0.40286499999999997f,0.016330299999999999f,0.051511399999999999f,0.34139000000000003f,0.31113499999999999f,0.61327600000000004f,0.80588400000000004f,0.95328999999999997f,0.40609099999999998f,0.57870500000000002f,0.38678499999999999f,0.43410300000000002f,0.77525999999999995f,1,0.63590899999999995f,0.78205199999999997f,0.013718299999999999f,0.038772500000000001f,0.61896399999999996f,0.85707100000000003f,0.131522f,0.18498800000000001f,0.29949500000000001f,0.78921200000000002f,0.60311400000000004f,0.070498900000000003f,0.0129339f,0.25248100000000001f,0.25412099999999999f,0.18920600000000001f,0.357713f,0.95030800000000004f,0.55257299999999998f,0.46645399999999998f,0.77736000000000005f,0.030788599999999999f,0.025194299999999999f,0.378886f,0.74018700000000004f,0.247637f,0.23520099999999999f,0.49304500000000001f,0.51785000000000003f,0.88395400000000002f,0.42947299999999999f,0.40943299999999999f,0.41526600000000002f,0.94019799999999998f,0.28233399999999997f,0.43789f,0.37538500000000002f,0.0157366f,0.017176299999999999f,0.48555500000000001f,0.46101500000000001f,0.858958f,0.90799099999999999f,0.93519099999999999f,0.37551000000000001f,1,0.58549300000000004f,0.26998100000000003f,0.42305300000000001f,0.66606699999999996f,0.43508999999999998f,0.79025199999999995f,0.0088958600000000002f,0.020884400000000001f,0.449735f,0.79080799999999996f,0.159856f,0.089598999999999998f,0.161546f,0.52816799999999997f,0.38064199999999998f,0.020627599999999999f,0.0072642599999999998f,0.031535199999999999f,0.031584099999999997f,0.19764899999999999f,0.47505700000000001f,0.51723200000000003f,0.36092200000000002f,0.42120400000000002f,0.63134000000000001f,0.0095213899999999994f,0.016105000000000001f,0.49961499999999998f,0.92295799999999995f,0.21498300000000001f,0.065514100000000006f,0.50397000000000003f,0.51484799999999997f,1,0.48361900000000002f,0.254027f,0.22837199999999999f,0.43610500000000002f,0.233125f,0.15224199999999999f,0.27951300000000001f,0.0090673899999999998f,0.013233200000000001f,0.45125700000000002f,0.38856600000000002f,0.73722600000000005f,0.47937800000000003f,0.23303699999999999f,0.103767f,0.84560900000000006f,0.64412700000000001f,0.26135900000000001f,0.37145699999999998f,0.52722899999999995f,0.38137300000000002f,0.33449200000000001f,0.0083374899999999995f,0.0086198200000000003f,0.25591900000000001f,0.25419700000000001f,0.0872333f,0.046151200000000003f,0.11301799999999999f,0.34598600000000002f,0.236344f,0.01078f,0.00816506f,0.40518100000000001f,0.38718000000000002f,0.34368100000000001f,0.81649300000000002f,0.25908199999999998f,0.21190600000000001f,0.43245499999999998f,0.69688600000000001f,0.0057622400000000001f,0.013131f,0.45596900000000001f,0.81160900000000002f,0.42654399999999998f,0.12848899999999999f,0.21593699999999999f,0.233934f,0.72306999999999999f,0.35162300000000002f,0.394231f,0.323766f,0.16880300000000001f,0.27693200000000001f,0.26468399999999997f,0.22770299999999999f,0.0068093499999999996f,0.0170703f,0.60301800000000005f,0.47646100000000002f,0.58592500000000003f,0.71696000000000004f,1,0.57652700000000001f,0.475524f,0.447322f,0.356902f,0.59757300000000002f,0.69724600000000003f,0.50533300000000003f,0.28542099999999998f,0.014719299999999999f,0.0141618f,0.136188f,0.033653700000000002f,0.21643699999999999f};
float 	mydsp::ftbl0[350];
