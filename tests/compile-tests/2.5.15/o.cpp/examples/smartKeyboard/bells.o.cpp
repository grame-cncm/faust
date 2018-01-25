//----------------------------------------------------------
// name: "bells"
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


	class SIG1 {
	  private:
		int fSamplingFreq;
		static float 	fWave1[350];
		int 	idxfWave1;
		float 	fTempPerm5;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			idxfWave1 = 0;
			fTempPerm5 = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				fTempPerm5 = fWave1[idxfWave1];
				output[i] = fTempPerm5;
				// post processing
				idxfWave1 = (idxfWave1 + 1) % 350;
			}
		}
	};


	class SIG2 {
	  private:
		int fSamplingFreq;
		static float 	fWave2[350];
		int 	idxfWave2;
		float 	fTempPerm8;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			idxfWave2 = 0;
			fTempPerm8 = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				fTempPerm8 = fWave2[idxfWave2];
				output[i] = fTempPerm8;
				// post processing
				idxfWave2 = (idxfWave2 + 1) % 350;
			}
		}
	};


	class SIG3 {
	  private:
		int fSamplingFreq;
		static float 	fWave3[350];
		int 	idxfWave3;
		float 	fTempPerm11;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			idxfWave3 = 0;
			fTempPerm11 = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				fTempPerm11 = fWave3[idxfWave3];
				output[i] = fTempPerm11;
				// post processing
				idxfWave3 = (idxfWave3 + 1) % 350;
			}
		}
	};


	static float 	ftbl0[350];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fVec0[2];
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	int 	iRec3[2];
	float 	fConst8;
	float 	fConst9;
	float 	fRec2[3];
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fRec1[3];
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider2;
	int 	iVec1[2];
	float 	fConst13;
	float 	fTempPerm2;
	float 	fRec4[2];
	float 	fConst14;
	int 	iTempPerm3;
	float 	fConst15;
	float 	fTempPerm4;
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fRec0[3];
	float 	fConst19;
	float 	fConst20;
	float 	fConst21;
	float 	fRec5[3];
	float 	fConst22;
	float 	fConst23;
	float 	fConst24;
	float 	fRec6[3];
	float 	fConst25;
	float 	fConst26;
	float 	fConst27;
	float 	fRec7[3];
	float 	fConst28;
	float 	fConst29;
	float 	fConst30;
	float 	fRec8[3];
	float 	fConst31;
	float 	fConst32;
	float 	fConst33;
	float 	fRec9[3];
	float 	fConst34;
	float 	fConst35;
	float 	fConst36;
	float 	fRec10[3];
	float 	fConst37;
	float 	fConst38;
	float 	fConst39;
	float 	fRec11[3];
	float 	fConst40;
	float 	fConst41;
	float 	fConst42;
	float 	fRec12[3];
	float 	fConst43;
	float 	fConst44;
	float 	fConst45;
	float 	fRec13[3];
	static float 	ftbl1[350];
	FAUSTFLOAT 	fslider3;
	int 	iVec2[2];
	float 	fRec15[2];
	int 	iTempPerm6;
	float 	fTempPerm7;
	float 	fConst46;
	float 	fConst47;
	float 	fConst48;
	float 	fRec14[3];
	float 	fConst49;
	float 	fConst50;
	float 	fConst51;
	float 	fRec16[3];
	float 	fConst52;
	float 	fConst53;
	float 	fConst54;
	float 	fRec17[3];
	float 	fConst55;
	float 	fConst56;
	float 	fConst57;
	float 	fRec18[3];
	float 	fConst58;
	float 	fConst59;
	float 	fConst60;
	float 	fRec19[3];
	float 	fConst61;
	float 	fConst62;
	float 	fConst63;
	float 	fRec20[3];
	float 	fConst64;
	float 	fConst65;
	float 	fConst66;
	float 	fRec21[3];
	float 	fConst67;
	float 	fConst68;
	float 	fConst69;
	float 	fRec22[3];
	float 	fConst70;
	float 	fConst71;
	float 	fConst72;
	float 	fRec23[3];
	float 	fConst73;
	float 	fConst74;
	float 	fConst75;
	float 	fRec24[3];
	static float 	ftbl2[350];
	FAUSTFLOAT 	fslider4;
	int 	iVec3[2];
	float 	fRec26[2];
	int 	iTempPerm9;
	float 	fTempPerm10;
	float 	fConst76;
	float 	fConst77;
	float 	fConst78;
	float 	fRec25[3];
	float 	fConst79;
	float 	fConst80;
	float 	fConst81;
	float 	fRec27[3];
	float 	fConst82;
	float 	fConst83;
	float 	fConst84;
	float 	fRec28[3];
	float 	fConst85;
	float 	fConst86;
	float 	fConst87;
	float 	fRec29[3];
	float 	fConst88;
	float 	fConst89;
	float 	fConst90;
	float 	fRec30[3];
	float 	fConst91;
	float 	fConst92;
	float 	fConst93;
	float 	fRec31[3];
	float 	fConst94;
	float 	fConst95;
	float 	fConst96;
	float 	fRec32[3];
	float 	fConst97;
	float 	fConst98;
	float 	fConst99;
	float 	fRec33[3];
	float 	fConst100;
	float 	fConst101;
	float 	fConst102;
	float 	fRec34[3];
	float 	fConst103;
	float 	fConst104;
	float 	fConst105;
	float 	fRec35[3];
	static float 	ftbl3[350];
	FAUSTFLOAT 	fslider5;
	int 	iVec4[2];
	float 	fRec37[2];
	int 	iTempPerm12;
	float 	fTempPerm13;
	float 	fConst106;
	float 	fConst107;
	float 	fConst108;
	float 	fRec36[3];
	float 	fConst109;
	float 	fConst110;
	float 	fConst111;
	float 	fRec38[3];
	float 	fConst112;
	float 	fConst113;
	float 	fConst114;
	float 	fRec39[3];
	float 	fConst115;
	float 	fConst116;
	float 	fConst117;
	float 	fRec40[3];
	float 	fConst118;
	float 	fConst119;
	float 	fConst120;
	float 	fRec41[3];
	float 	fConst121;
	float 	fConst122;
	float 	fConst123;
	float 	fRec42[3];
	float 	fConst124;
	float 	fConst125;
	float 	fConst126;
	float 	fRec43[3];
	float 	fConst127;
	float 	fConst128;
	float 	fConst129;
	float 	fRec44[3];
	float 	fConst130;
	float 	fConst131;
	float 	fConst132;
	float 	fRec45[3];
	float 	fConst133;
	float 	fConst134;
	float 	fConst135;
	float 	fRec46[3];
	float 	fTempPerm14;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("interface", "SmartKeyboard{  'Number of Keyboards':'2',  'Max Keyboard Polyphony':'0',  'Keyboard 0 - Number of Keys':'2',   'Keyboard 1 - Number of Keys':'2',  'Keyboard 0 - Send Freq':'0',   'Keyboard 1 - Send Freq':'0',  'Keyboard 0 - Piano Keyboard':'0',   'Keyboard 1 - Piano Keyboard':'0',  'Keyboard 0 - Send Key Status':'1',  'Keyboard 1 - Send Key Status':'1',  'Keyboard 0 - Send X':'1',  'Keyboard 0 - Send Y':'1',  'Keyboard 1 - Send X':'1',  'Keyboard 1 - Send Y':'1',  'Keyboard 0 - Key 0 - Label':'English Bell',  'Keyboard 0 - Key 1 - Label':'French Bell',  'Keyboard 1 - Key 0 - Label':'German Bell',  'Keyboard 1 - Key 1 - Label':'Russian Bell' }");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "bells");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(350,ftbl0);
		SIG1 sig1;
		sig1.init(samplingFreq);
		sig1.fill(350,ftbl1);
		SIG2 sig2;
		sig2.init(samplingFreq);
		sig2.fill(350,ftbl2);
		SIG3 sig3;
		sig3.init(samplingFreq);
		sig3.fill(350,ftbl3);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = tanf((20420.352248333656f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 1.4142135623730949f) / fConst1) + 1));
		fConst4 = tanf((31.415926535897931f / fConst0));
		fConst5 = (1.0f / fConst4);
		fConst6 = (1.0f / (((fConst5 + 1.4142135623730949f) / fConst4) + 1));
		fConst7 = (1.0f / faustpower<2>(fConst4));
		fConst8 = (((fConst5 + -1.4142135623730949f) / fConst4) + 1);
		fConst9 = (2 * (1 - fConst7));
		fConst10 = (2 * (0 - fConst7));
		fConst11 = (2 * (1 - (1.0f / faustpower<2>(fConst1))));
		fConst12 = (((fConst2 + -1.4142135623730949f) / fConst1) + 1);
		fTempPerm1 = 0;
		fConst13 = (0.002f * fConst0);
		fTempPerm2 = 0;
		fConst14 = (0.001f * fConst0);
		iTempPerm3 = 0;
		fConst15 = (1000.0f / fConst0);
		fTempPerm4 = 0;
		fConst16 = powf(0.001f,(1.0f / float((20.346989644553652f * fConst0))));
		fConst17 = ((0 - (2 * fConst16)) * cosf((1630.0404810562927f / fConst0)));
		fConst18 = faustpower<2>(fConst16);
		fConst19 = powf(0.001f,(1.0f / float((20.26822245756393f * fConst0))));
		fConst20 = ((0 - (2 * fConst19)) * cosf((1645.2834886115106f / fConst0)));
		fConst21 = faustpower<2>(fConst19);
		fConst22 = powf(0.001f,(1.0f / float((13.650799900615313f * fConst0))));
		fConst23 = ((0 - (2 * fConst22)) * cosf((3099.6900907762124f / fConst0)));
		fConst24 = faustpower<2>(fConst22);
		fConst25 = powf(0.001f,(1.0f / float((13.622392037859123f * fConst0))));
		fConst26 = ((0 - (2 * fConst25)) * cosf((3106.8592052117042f / fConst0)));
		fConst27 = faustpower<2>(fConst25);
		fConst28 = powf(0.001f,(1.0f / float((11.095645822450564f * fConst0))));
		fConst29 = ((0 - (2 * fConst28)) * cosf((3789.0623331240349f / fConst0)));
		fConst30 = faustpower<2>(fConst28);
		fConst31 = powf(0.001f,(1.0f / float((11.058927361611808f * fConst0))));
		fConst32 = ((0 - (2 * fConst31)) * cosf((3799.706049034397f / fConst0)));
		fConst33 = faustpower<2>(fConst31);
		fConst34 = powf(0.001f,(1.0f / float((8.6621298206728596f * fConst0))));
		fConst35 = ((0 - (2 * fConst34)) * cosf((4552.5824452818842f / fConst0)));
		fConst36 = faustpower<2>(fConst34);
		fConst37 = powf(0.001f,(1.0f / float((8.6582484684287806f * fConst0))));
		fConst38 = ((0 - (2 * fConst37)) * cosf((4553.9081973816992f / fConst0)));
		fConst39 = faustpower<2>(fConst37);
		fConst40 = powf(0.001f,(1.0f / float((7.5637590600138438f * fConst0))));
		fConst41 = ((0 - (2 * fConst40)) * cosf((4944.7725889707272f / fConst0)));
		fConst42 = faustpower<2>(fConst40);
		fConst43 = powf(0.001f,(1.0f / float((5.3802613620526891f * fConst0))));
		fConst44 = ((0 - (2 * fConst43)) * cosf((5855.2564054635068f / fConst0)));
		fConst45 = faustpower<2>(fConst43);
		iTempPerm6 = 0;
		fTempPerm7 = 0;
		fConst46 = powf(0.001f,(1.0f / float((17.04040295618125f * fConst0))));
		fConst47 = ((0 - (2 * fConst46)) * cosf((2758.8021551204911f / fConst0)));
		fConst48 = faustpower<2>(fConst46);
		fConst49 = powf(0.001f,(1.0f / float((17.010755596973247f * fConst0))));
		fConst50 = ((0 - (2 * fConst49)) * cosf((2766.5179066777077f / fConst0)));
		fConst51 = faustpower<2>(fConst49);
		fConst52 = powf(0.001f,(1.0f / float((13.308511157375246f * fConst0))));
		fConst53 = ((0 - (2 * fConst52)) * cosf((3810.4502959096744f / fConst0)));
		fConst54 = faustpower<2>(fConst52);
		fConst55 = powf(0.001f,(1.0f / float((13.199737475192013f * fConst0))));
		fConst56 = ((0 - (2 * fConst55)) * cosf((3843.9019744850984f / fConst0)));
		fConst57 = faustpower<2>(fConst55);
		fConst58 = powf(0.001f,(1.0f / float((11.304904713130588f * fConst0))));
		fConst59 = ((0 - (2 * fConst58)) * cosf((4458.6551081248563f / fConst0)));
		fConst60 = faustpower<2>(fConst58);
		fConst61 = powf(0.001f,(1.0f / float((11.300127845394371f * fConst0))));
		fConst62 = ((0 - (2 * fConst61)) * cosf((4460.288736304723f / fConst0)));
		fConst63 = faustpower<2>(fConst61);
		fConst64 = powf(0.001f,(1.0f / float((8.8077480341046552f * fConst0))));
		fConst65 = ((0 - (2 * fConst64)) * cosf((5384.4761799524613f / fConst0)));
		fConst66 = faustpower<2>(fConst64);
		fConst67 = powf(0.001f,(1.0f / float((8.1690669816675641f * fConst0))));
		fConst68 = ((0 - (2 * fConst67)) * cosf((5648.9040336051148f / fConst0)));
		fConst69 = faustpower<2>(fConst67);
		fConst70 = powf(0.001f,(1.0f / float((5.9589169207409025f * fConst0))));
		fConst71 = ((0 - (2 * fConst70)) * cosf((6687.6339454027357f / fConst0)));
		fConst72 = faustpower<2>(fConst70);
		fConst73 = powf(0.001f,(1.0f / float((5.9543617544807077f * fConst0))));
		fConst74 = ((0 - (2 * fConst73)) * cosf((6690.0215558194641f / fConst0)));
		fConst75 = faustpower<2>(fConst73);
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		fConst76 = powf(0.001f,(1.0f / float((21.889564882066438f * fConst0))));
		fConst77 = ((0 - (2 * fConst76)) * cosf((1501.1095185529678f / fConst0)));
		fConst78 = faustpower<2>(fConst76);
		fConst79 = powf(0.001f,(1.0f / float((21.848776321176928f * fConst0))));
		fConst80 = ((0 - (2 * fConst79)) * cosf((1509.4410222702879f / fConst0)));
		fConst81 = faustpower<2>(fConst79);
		fConst82 = powf(0.001f,(1.0f / float((17.096952816214348f * fConst0))));
		fConst83 = ((0 - (2 * fConst82)) * cosf((2552.5440310417071f / fConst0)));
		fConst84 = faustpower<2>(fConst82);
		fConst85 = powf(0.001f,(1.0f / float((17.044882409103749f * fConst0))));
		fConst86 = ((0 - (2 * fConst85)) * cosf((2564.8842069850075f / fConst0)));
		fConst87 = faustpower<2>(fConst85);
		fConst88 = powf(0.001f,(1.0f / float((13.279117003716509f * fConst0))));
		fConst89 = ((0 - (2 * fConst88)) * cosf((3525.5266917850017f / fConst0)));
		fConst90 = faustpower<2>(fConst88);
		fConst91 = powf(0.001f,(1.0f / float((13.237699485362832f * fConst0))));
		fConst92 = ((0 - (2 * fConst91)) * cosf((3536.9495226734543f / fConst0)));
		fConst93 = faustpower<2>(fConst91);
		fConst94 = powf(0.001f,(1.0f / float((9.3884575777665447f * fConst0))));
		fConst95 = ((0 - (2 * fConst94)) * cosf((4710.0767681916468f / fConst0)));
		fConst96 = faustpower<2>(fConst94);
		fConst97 = powf(0.001f,(1.0f / float((9.3838651744883457f * fConst0))));
		fConst98 = ((0 - (2 * fConst97)) * cosf((4711.6349981478279f / fConst0)));
		fConst99 = faustpower<2>(fConst97);
		fConst100 = powf(0.001f,(1.0f / float((8.811310358836641f * fConst0))));
		fConst101 = ((0 - (2 * fConst100)) * cosf((4909.6118839917499f / fConst0)));
		fConst102 = faustpower<2>(fConst100);
		fConst103 = powf(0.001f,(1.0f / float((8.4713937323952262f * fConst0))));
		fConst104 = ((0 - (2 * fConst103)) * cosf((5030.820811752551f / fConst0)));
		fConst105 = faustpower<2>(fConst103);
		iTempPerm12 = 0;
		fTempPerm13 = 0;
		fConst106 = powf(0.001f,(1.0f / float((20.890153741822246f * fConst0))));
		fConst107 = ((0 - (2 * fConst106)) * cosf((857.59824576224901f / fConst0)));
		fConst108 = faustpower<2>(fConst106);
		fConst109 = powf(0.001f,(1.0f / float((20.860672702556624f * fConst0))));
		fConst110 = ((0 - (2 * fConst109)) * cosf((860.74612160114577f / fConst0)));
		fConst111 = faustpower<2>(fConst109);
		fConst112 = powf(0.001f,(1.0f / float((14.477914648462914f * fConst0))));
		fConst113 = ((0 - (2 * fConst112)) * cosf((1627.0811007766115f / fConst0)));
		fConst114 = faustpower<2>(fConst112);
		fConst115 = powf(0.001f,(1.0f / float((14.41065897924317f * fConst0))));
		fConst116 = ((0 - (2 * fConst115)) * cosf((1636.2608345104006f / fConst0)));
		fConst117 = faustpower<2>(fConst115);
		fConst118 = powf(0.001f,(1.0f / float((11.984111166533006f * fConst0))));
		fConst119 = ((0 - (2 * fConst118)) * cosf((1988.5590346839599f / fConst0)));
		fConst120 = faustpower<2>(fConst118);
		fConst121 = powf(0.001f,(1.0f / float((11.90615898267875f * fConst0))));
		fConst122 = ((0 - (2 * fConst121)) * cosf((2000.6353168443593f / fConst0)));
		fConst123 = faustpower<2>(fConst121);
		fConst124 = powf(0.001f,(1.0f / float((9.1066165639380277f * fConst0))));
		fConst125 = ((0 - (2 * fConst124)) * cosf((2474.6450996032941f / fConst0)));
		fConst126 = faustpower<2>(fConst124);
		fConst127 = powf(0.001f,(1.0f / float((9.1033338027354453f * fConst0))));
		fConst128 = ((0 - (2 * fConst127)) * cosf((2475.254568578091f / fConst0)));
		fConst129 = faustpower<2>(fConst127);
		fConst130 = powf(0.001f,(1.0f / float((7.1991184444136032f * fConst0))));
		fConst131 = ((0 - (2 * fConst130)) * cosf((2856.8198459124928f / fConst0)));
		fConst132 = faustpower<2>(fConst130);
		fConst133 = powf(0.001f,(1.0f / float((6.8345816271582756f * fConst0))));
		fConst134 = ((0 - (2 * fConst133)) * cosf((2937.3451488093065f / fConst0)));
		fConst135 = faustpower<2>(fConst133);
		fTempPerm14 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fslider1 = 1.0f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) iVec1[i] = 0;
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
		for (int i=0; i<2; i++) iVec2[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<3; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec16[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		for (int i=0; i<3; i++) fRec18[i] = 0;
		for (int i=0; i<3; i++) fRec19[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<3; i++) fRec21[i] = 0;
		for (int i=0; i<3; i++) fRec22[i] = 0;
		for (int i=0; i<3; i++) fRec23[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) iVec3[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<3; i++) fRec25[i] = 0;
		for (int i=0; i<3; i++) fRec27[i] = 0;
		for (int i=0; i<3; i++) fRec28[i] = 0;
		for (int i=0; i<3; i++) fRec29[i] = 0;
		for (int i=0; i<3; i++) fRec30[i] = 0;
		for (int i=0; i<3; i++) fRec31[i] = 0;
		for (int i=0; i<3; i++) fRec32[i] = 0;
		for (int i=0; i<3; i++) fRec33[i] = 0;
		for (int i=0; i<3; i++) fRec34[i] = 0;
		for (int i=0; i<3; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) iVec4[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<3; i++) fRec36[i] = 0;
		for (int i=0; i<3; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fRec39[i] = 0;
		for (int i=0; i<3; i++) fRec40[i] = 0;
		for (int i=0; i<3; i++) fRec41[i] = 0;
		for (int i=0; i<3; i++) fRec42[i] = 0;
		for (int i=0; i<3; i++) fRec43[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
		for (int i=0; i<3; i++) fRec46[i] = 0;
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
		ui_interface->openVerticalBox("bells");
		ui_interface->addHorizontalSlider("kb0k0status", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb0k1status", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k0status", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("kb1k1status", &fslider5, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("x", &fslider0, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("y", &fslider1, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = (10 * int((6 * min(fabsf(((2 * float(fslider0)) + -1)), fabsf(((2 * float(fslider1)) + -1))))));
		int 	iSlow1 = int(iSlow0);
		float 	fSlow2 = ftbl0[iSlow1];
		int 	iSlow3 = int(min((float)1, float(fslider2)));
		int 	iSlow4 = int((iSlow0 + 1));
		float 	fSlow5 = ftbl0[iSlow4];
		int 	iSlow6 = int((iSlow0 + 2));
		float 	fSlow7 = ftbl0[iSlow6];
		int 	iSlow8 = int((iSlow0 + 3));
		float 	fSlow9 = ftbl0[iSlow8];
		int 	iSlow10 = int((iSlow0 + 4));
		float 	fSlow11 = ftbl0[iSlow10];
		int 	iSlow12 = int((iSlow0 + 5));
		float 	fSlow13 = ftbl0[iSlow12];
		int 	iSlow14 = int((iSlow0 + 6));
		float 	fSlow15 = ftbl0[iSlow14];
		int 	iSlow16 = int((iSlow0 + 7));
		float 	fSlow17 = ftbl0[iSlow16];
		int 	iSlow18 = int((iSlow0 + 8));
		float 	fSlow19 = ftbl0[iSlow18];
		int 	iSlow20 = int((iSlow0 + 9));
		float 	fSlow21 = ftbl0[iSlow20];
		float 	fSlow22 = ftbl1[iSlow1];
		int 	iSlow23 = int(min((float)1, float(fslider3)));
		float 	fSlow24 = ftbl1[iSlow4];
		float 	fSlow25 = ftbl1[iSlow6];
		float 	fSlow26 = ftbl1[iSlow8];
		float 	fSlow27 = ftbl1[iSlow10];
		float 	fSlow28 = ftbl1[iSlow12];
		float 	fSlow29 = ftbl1[iSlow14];
		float 	fSlow30 = ftbl1[iSlow16];
		float 	fSlow31 = ftbl1[iSlow18];
		float 	fSlow32 = ftbl1[iSlow20];
		float 	fSlow33 = ftbl2[iSlow1];
		int 	iSlow34 = int(min((float)1, float(fslider4)));
		float 	fSlow35 = ftbl2[iSlow4];
		float 	fSlow36 = ftbl2[iSlow6];
		float 	fSlow37 = ftbl2[iSlow8];
		float 	fSlow38 = ftbl2[iSlow10];
		float 	fSlow39 = ftbl2[iSlow12];
		float 	fSlow40 = ftbl2[iSlow14];
		float 	fSlow41 = ftbl2[iSlow16];
		float 	fSlow42 = ftbl2[iSlow18];
		float 	fSlow43 = ftbl2[iSlow20];
		float 	fSlow44 = ftbl3[iSlow1];
		int 	iSlow45 = int(min((float)1, float(fslider5)));
		float 	fSlow46 = ftbl3[iSlow4];
		float 	fSlow47 = ftbl3[iSlow6];
		float 	fSlow48 = ftbl3[iSlow8];
		float 	fSlow49 = ftbl3[iSlow10];
		float 	fSlow50 = ftbl3[iSlow12];
		float 	fSlow51 = ftbl3[iSlow14];
		float 	fSlow52 = ftbl3[iSlow16];
		float 	fSlow53 = ftbl3[iSlow18];
		float 	fSlow54 = ftbl3[iSlow20];
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[0] = fConst0;
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.6566128752457969e-10f * iRec3[0]) - (fConst6 * ((fConst8 * fRec2[2]) + (fConst9 * fRec2[1]))));
			fRec1[0] = ((fConst6 * (((fConst7 * fRec2[0]) + (fConst10 * fRec2[1])) + (fConst7 * fRec2[2]))) - (fConst3 * ((fConst11 * fRec1[1]) + (fConst12 * fRec1[2]))));
			fTempPerm1 = (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])));
			iVec1[0] = iSlow3;
			fTempPerm2 = (0.002f * (fConst0 - fVec0[1]));
			fRec4[0] = ((int((((iSlow3 - iVec1[1]) > 0) > 0)))?0:min(fConst13, ((fRec4[1] + fTempPerm2) + 1)));
			iTempPerm3 = int((fRec4[0] < fConst14));
			fTempPerm4 = (fConst3 * (fTempPerm1 * ((iTempPerm3)?((int((fRec4[0] < 0)))?0:((iTempPerm3)?(fConst15 * fRec4[0]):1)):((int((fRec4[0] < fConst13)))?((fConst15 * (0 - (fRec4[0] - fConst14))) + 1):0))));
			fRec0[0] = (fTempPerm4 - ((fConst17 * fRec0[1]) + (fConst18 * fRec0[2])));
			fRec5[0] = (fTempPerm4 - ((fConst20 * fRec5[1]) + (fConst21 * fRec5[2])));
			fRec6[0] = (fTempPerm4 - ((fConst23 * fRec6[1]) + (fConst24 * fRec6[2])));
			fRec7[0] = (fTempPerm4 - ((fConst26 * fRec7[1]) + (fConst27 * fRec7[2])));
			fRec8[0] = (fTempPerm4 - ((fConst29 * fRec8[1]) + (fConst30 * fRec8[2])));
			fRec9[0] = (fTempPerm4 - ((fConst32 * fRec9[1]) + (fConst33 * fRec9[2])));
			fRec10[0] = (fTempPerm4 - ((fConst35 * fRec10[1]) + (fConst36 * fRec10[2])));
			fRec11[0] = (fTempPerm4 - ((fConst38 * fRec11[1]) + (fConst39 * fRec11[2])));
			fRec12[0] = (fTempPerm4 - ((fConst41 * fRec12[1]) + (fConst42 * fRec12[2])));
			fRec13[0] = (fTempPerm4 - ((fConst44 * fRec13[1]) + (fConst45 * fRec13[2])));
			iVec2[0] = iSlow23;
			fRec15[0] = ((int((((iSlow23 - iVec2[1]) > 0) > 0)))?0:min(fConst13, ((fTempPerm2 + fRec15[1]) + 1)));
			iTempPerm6 = int((fRec15[0] < fConst14));
			fTempPerm7 = (fConst3 * (fTempPerm1 * ((iTempPerm6)?((int((fRec15[0] < 0)))?0:((iTempPerm6)?(fConst15 * fRec15[0]):1)):((int((fRec15[0] < fConst13)))?((fConst15 * (0 - (fRec15[0] - fConst14))) + 1):0))));
			fRec14[0] = (fTempPerm7 - ((fConst47 * fRec14[1]) + (fConst48 * fRec14[2])));
			fRec16[0] = (fTempPerm7 - ((fConst50 * fRec16[1]) + (fConst51 * fRec16[2])));
			fRec17[0] = (fTempPerm7 - ((fConst53 * fRec17[1]) + (fConst54 * fRec17[2])));
			fRec18[0] = (fTempPerm7 - ((fConst56 * fRec18[1]) + (fConst57 * fRec18[2])));
			fRec19[0] = (fTempPerm7 - ((fConst59 * fRec19[1]) + (fConst60 * fRec19[2])));
			fRec20[0] = (fTempPerm7 - ((fConst62 * fRec20[1]) + (fConst63 * fRec20[2])));
			fRec21[0] = (fTempPerm7 - ((fConst65 * fRec21[1]) + (fConst66 * fRec21[2])));
			fRec22[0] = (fTempPerm7 - ((fConst68 * fRec22[1]) + (fConst69 * fRec22[2])));
			fRec23[0] = (fTempPerm7 - ((fConst71 * fRec23[1]) + (fConst72 * fRec23[2])));
			fRec24[0] = (fTempPerm7 - ((fConst74 * fRec24[1]) + (fConst75 * fRec24[2])));
			iVec3[0] = iSlow34;
			fRec26[0] = ((int((((iSlow34 - iVec3[1]) > 0) > 0)))?0:min(fConst13, ((fTempPerm2 + fRec26[1]) + 1)));
			iTempPerm9 = int((fRec26[0] < fConst14));
			fTempPerm10 = (fConst3 * (fTempPerm1 * ((iTempPerm9)?((int((fRec26[0] < 0)))?0:((iTempPerm9)?(fConst15 * fRec26[0]):1)):((int((fRec26[0] < fConst13)))?((fConst15 * (0 - (fRec26[0] - fConst14))) + 1):0))));
			fRec25[0] = (fTempPerm10 - ((fConst77 * fRec25[1]) + (fConst78 * fRec25[2])));
			fRec27[0] = (fTempPerm10 - ((fConst80 * fRec27[1]) + (fConst81 * fRec27[2])));
			fRec28[0] = (fTempPerm10 - ((fConst83 * fRec28[1]) + (fConst84 * fRec28[2])));
			fRec29[0] = (fTempPerm10 - ((fConst86 * fRec29[1]) + (fConst87 * fRec29[2])));
			fRec30[0] = (fTempPerm10 - ((fConst89 * fRec30[1]) + (fConst90 * fRec30[2])));
			fRec31[0] = (fTempPerm10 - ((fConst92 * fRec31[1]) + (fConst93 * fRec31[2])));
			fRec32[0] = (fTempPerm10 - ((fConst95 * fRec32[1]) + (fConst96 * fRec32[2])));
			fRec33[0] = (fTempPerm10 - ((fConst98 * fRec33[1]) + (fConst99 * fRec33[2])));
			fRec34[0] = (fTempPerm10 - ((fConst101 * fRec34[1]) + (fConst102 * fRec34[2])));
			fRec35[0] = (fTempPerm10 - ((fConst104 * fRec35[1]) + (fConst105 * fRec35[2])));
			iVec4[0] = iSlow45;
			fRec37[0] = ((int((((iSlow45 - iVec4[1]) > 0) > 0)))?0:min(fConst13, ((fTempPerm2 + fRec37[1]) + 1)));
			iTempPerm12 = int((fRec37[0] < fConst14));
			fTempPerm13 = (fConst3 * (fTempPerm1 * ((iTempPerm12)?((int((fRec37[0] < 0)))?0:((iTempPerm12)?(fConst15 * fRec37[0]):1)):((int((fRec37[0] < fConst13)))?((fConst15 * (0 - (fRec37[0] - fConst14))) + 1):0))));
			fRec36[0] = (fTempPerm13 - ((fConst107 * fRec36[1]) + (fConst108 * fRec36[2])));
			fRec38[0] = (fTempPerm13 - ((fConst110 * fRec38[1]) + (fConst111 * fRec38[2])));
			fRec39[0] = (fTempPerm13 - ((fConst113 * fRec39[1]) + (fConst114 * fRec39[2])));
			fRec40[0] = (fTempPerm13 - ((fConst116 * fRec40[1]) + (fConst117 * fRec40[2])));
			fRec41[0] = (fTempPerm13 - ((fConst119 * fRec41[1]) + (fConst120 * fRec41[2])));
			fRec42[0] = (fTempPerm13 - ((fConst122 * fRec42[1]) + (fConst123 * fRec42[2])));
			fRec43[0] = (fTempPerm13 - ((fConst125 * fRec43[1]) + (fConst126 * fRec43[2])));
			fRec44[0] = (fTempPerm13 - ((fConst128 * fRec44[1]) + (fConst129 * fRec44[2])));
			fRec45[0] = (fTempPerm13 - ((fConst131 * fRec45[1]) + (fConst132 * fRec45[2])));
			fRec46[0] = (fTempPerm13 - ((fConst134 * fRec46[1]) + (fConst135 * fRec46[2])));
			fTempPerm14 = (0.020000000000000004f * (((((((((((((fSlow2 * (fRec0[0] - fRec0[2])) + (fSlow5 * (fRec5[0] - fRec5[2]))) + (fSlow7 * (fRec6[0] - fRec6[2]))) + (fSlow9 * (fRec7[0] - fRec7[2]))) + (fSlow11 * (fRec8[0] - fRec8[2]))) + (fSlow13 * (fRec9[0] - fRec9[2]))) + (fSlow15 * (fRec10[0] - fRec10[2]))) + (fSlow17 * (fRec11[0] - fRec11[2]))) + (fSlow19 * (fRec12[0] - fRec12[2]))) + (fSlow21 * (fRec13[0] - fRec13[2]))) + ((((((((((fSlow22 * (fRec14[0] - fRec14[2])) + (fSlow24 * (fRec16[0] - fRec16[2]))) + (fSlow25 * (fRec17[0] - fRec17[2]))) + (fSlow26 * (fRec18[0] - fRec18[2]))) + (fSlow27 * (fRec19[0] - fRec19[2]))) + (fSlow28 * (fRec20[0] - fRec20[2]))) + (fSlow29 * (fRec21[0] - fRec21[2]))) + (fSlow30 * (fRec22[0] - fRec22[2]))) + (fSlow31 * (fRec23[0] - fRec23[2]))) + (fSlow32 * (fRec24[0] - fRec24[2])))) + ((((((((((fSlow33 * (fRec25[0] - fRec25[2])) + (fSlow35 * (fRec27[0] - fRec27[2]))) + (fSlow36 * (fRec28[0] - fRec28[2]))) + (fSlow37 * (fRec29[0] - fRec29[2]))) + (fSlow38 * (fRec30[0] - fRec30[2]))) + (fSlow39 * (fRec31[0] - fRec31[2]))) + (fSlow40 * (fRec32[0] - fRec32[2]))) + (fSlow41 * (fRec33[0] - fRec33[2]))) + (fSlow42 * (fRec34[0] - fRec34[2]))) + (fSlow43 * (fRec35[0] - fRec35[2])))) + ((((((((((fSlow44 * (fRec36[0] - fRec36[2])) + (fSlow46 * (fRec38[0] - fRec38[2]))) + (fSlow47 * (fRec39[0] - fRec39[2]))) + (fSlow48 * (fRec40[0] - fRec40[2]))) + (fSlow49 * (fRec41[0] - fRec41[2]))) + (fSlow50 * (fRec42[0] - fRec42[2]))) + (fSlow51 * (fRec43[0] - fRec43[2]))) + (fSlow52 * (fRec44[0] - fRec44[2]))) + (fSlow53 * (fRec45[0] - fRec45[2]))) + (fSlow54 * (fRec46[0] - fRec46[2])))));
			output0[i] = (FAUSTFLOAT)fTempPerm14;
			output1[i] = (FAUSTFLOAT)fTempPerm14;
			// post processing
			fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
			fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			iVec4[1] = iVec4[0];
			fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			iVec3[1] = iVec3[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			iVec2[1] = iVec2[0];
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
			iVec1[1] = iVec1[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			fVec0[1] = fVec0[0];
		}
	}
};


float 	mydsp::SIG0::fWave0[350] = {0.69427399999999995f,0.47169800000000001f,0.17238999999999999f,0.58544600000000002f,0.39798600000000001f,0.91957900000000004f,0.53194699999999995f,0.100205f,0.63946899999999995f,0.67220899999999995f,0.144345f,0.41659499999999999f,0.124108f,0.38059100000000001f,0.25657799999999997f,0.64603100000000002f,0.85219999999999996f,0.022437599999999999f,0.38276199999999999f,0.143925f,0.36869099999999999f,0.43055599999999999f,0.32318000000000002f,0.142956f,0.27452100000000002f,0.71382400000000001f,0.44279400000000002f,0.35247299999999998f,0.247756f,0.41515200000000002f,1,0.40186899999999998f,0.19798099999999999f,0.27950999999999998f,0.21024899999999999f,0.36974000000000001f,0.36922700000000003f,0.15576899999999999f,0.272368f,0.33571200000000001f,0.31645000000000001f,0.71410300000000004f,0.28578100000000001f,0.22006000000000001f,0.827704f,0.206342f,0.180177f,0.31147799999999998f,0.197607f,0.57547499999999996f,0.47331099999999998f,0.58723199999999998f,0.50287999999999999f,0.337308f,0.30451400000000001f,0.429039f,0.351522f,0.34137299999999998f,0.17508099999999999f,0.56174800000000003f,0.43917200000000001f,0.32316400000000001f,0.54051800000000005f,0.53652299999999997f,0.074386499999999994f,0.213417f,0.358012f,0.47449400000000003f,0.31027399999999999f,0.83941299999999996f,0.241372f,0.202343f,0.48063400000000001f,0.99568500000000004f,0.37374000000000002f,0.13399800000000001f,0.52067399999999997f,0.207514f,1,0.101239f,0.27953600000000001f,0.18598500000000001f,0.43629299999999999f,0.62411000000000005f,0.33451900000000001f,0.28358499999999998f,0.179317f,0.35384700000000002f,0.44954499999999997f,0.57412799999999997f,0.13517199999999999f,0.53827499999999995f,0.47642400000000001f,0.83290299999999995f,0.16419800000000001f,0.18856200000000001f,0.13597799999999999f,0.39012799999999997f,0.13104499999999999f,0.31206499999999998f,0.14213899999999999f,0.025590100000000001f,0.26694699999999999f,0.37160700000000002f,0.016843500000000001f,0.024946800000000002f,0.50891699999999995f,0.35441f,0.28334799999999999f,0.62815500000000002f,0.29247800000000002f,0.35835f,0.34256900000000001f,0.44123699999999999f,0.88669900000000001f,0.017469800000000001f,0.0064184300000000001f,0.55532000000000004f,0.88012900000000005f,0.0306909f,0.29008099999999998f,0.24881600000000001f,0.98173600000000005f,0.32462400000000002f,0.213676f,0.43288500000000002f,0.098155900000000004f,0.44414900000000002f,0.39555400000000002f,0.52506900000000001f,0.077130799999999999f,0.048880399999999997f,0.59132099999999999f,0.108044f,0.44380199999999997f,0.74031800000000003f,0.59943800000000003f,0.29309299999999999f,1,0.14166200000000001f,0.91003100000000003f,0.22612599999999999f,0.29970200000000002f,0.341472f,0.056806099999999998f,0.222494f,0.91871800000000003f,0.19947799999999999f,0.21662000000000001f,0.10775899999999999f,0.69232400000000005f,0.55633600000000005f,0.28171800000000002f,0.43083199999999999f,0.34165600000000002f,0.60809500000000005f,0.34212900000000002f,0.31131199999999998f,0.22995299999999999f,0.69508700000000001f,0.076148900000000005f,0.34981800000000002f,0.36170600000000003f,0.57761099999999999f,0.14779700000000001f,0.327376f,0.46571499999999999f,0.34290199999999998f,0.52138099999999998f,0.83682800000000002f,0.24111199999999999f,0.28439399999999998f,0.53931600000000002f,0.14340800000000001f,0.51702000000000004f,1,0.23633599999999999f,0.48033300000000001f,0.67674400000000001f,0.80758200000000002f,0.46862100000000001f,0.236953f,0.41160400000000003f,0.57925099999999996f,0.42509799999999998f,0.37598999999999999f,0.46117599999999997f,0.27653f,0.462368f,0.61300399999999999f,0.66684900000000003f,0.95471499999999998f,0.16150700000000001f,0.170433f,0.29046100000000002f,0.117303f,0.36513299999999999f,0.233794f,0.19456799999999999f,0.33887400000000001f,0.52338099999999999f,0.39834999999999998f,0.44783899999999999f,0.652891f,0.15708f,0.34035399999999999f,0.44217000000000001f,0.33876400000000001f,0.18439700000000001f,0.77160700000000004f,0.16050200000000001f,0.32448700000000003f,0.47749900000000001f,0.83151900000000001f,0.0168764f,0.15426400000000001f,0.20186499999999999f,0.237786f,0.39006600000000002f,0.88016399999999995f,0.28423399999999999f,0.16283700000000001f,0.43755699999999997f,0.22784599999999999f,0.39933999999999997f,1,0.158107f,0.39690300000000001f,0.51302899999999996f,0.67645699999999997f,0.20428199999999999f,0.089557499999999998f,0.55540999999999996f,0.73248599999999997f,0.12506200000000001f,0.17122899999999999f,0.081645999999999996f,0.054139399999999997f,0.39616000000000001f,0.45428800000000003f,0.46686299999999997f,0.92884199999999995f,0.155393f,0.26284999999999997f,0.113453f,0.133163f,0.30202099999999998f,0.61261600000000005f,0.22839200000000001f,0.19561700000000001f,0.28723599999999999f,0.19876199999999999f,0.499884f,0.80913900000000005f,0.0092992500000000002f,0.084029900000000005f,0.28644599999999998f,0.182112f,0.18604399999999999f,0.75413799999999998f,0.27955600000000003f,0.26694800000000002f,0.49429099999999998f,1,0.32128400000000001f,0.0230981f,0.037553700000000002f,0.26253100000000001f,0.60220399999999996f,0.489925f,0.633077f,0.40740900000000002f,0.42225600000000002f,0.091064099999999995f,0.357935f,0.55017899999999997f,0.10619199999999999f,0.13236600000000001f,0.37623099999999998f,0.35115099999999999f,0.042030199999999997f,0.037218300000000003f,0.69633500000000004f,0.84082100000000004f,0.85523499999999997f,0.249248f,0.86001099999999997f,0.34048099999999998f,0.28558f,0.363039f,0.32412200000000002f,0.51569900000000002f,0.228131f,0.172592f,0.018872300000000002f,0.168243f,0.99510500000000002f,0.74175899999999995f,0.10709299999999999f,0.070348999999999995f,0.13663600000000001f,0.078045500000000004f,0.31574799999999997f,0.50220100000000001f,0.019042199999999999f,0.033914f,0.22572400000000001f,0.16023599999999999f,0.18410099999999999f,0.56420300000000001f,0.24731700000000001f,0.28422500000000001f,0.32715300000000003f,0.65144299999999999f,0.59347099999999997f,0.016389899999999999f,0.014104800000000001f,0.52112999999999998f,1,0.10510899999999999f,0.53093599999999996f,0.36372399999999999f,0.92480899999999999f,0.25041000000000002f,0.69288000000000005f,0.41412199999999999f,0.0793658f,0.34781299999999998f,0.44173099999999998f,0.47642800000000002f,0.080883399999999994f,0.058163800000000002f,0.55723900000000004f,0.55651499999999998f,0.74608399999999997f,0.58222799999999997f,0.177231f,0.15842500000000001f,0.85090299999999996f,0.75527100000000003f,0.67361400000000005f,0.31706000000000001f,0.051538599999999997f,0.20189799999999999f,0.057793799999999999f,0.23203099999999999f,0.73498799999999997f,0.141594f,0.26706200000000002f,0.14580699999999999f};
float 	mydsp::ftbl0[350];
float 	mydsp::SIG1::fWave1[350] = {0.97289000000000003f,0.54239300000000001f,0.49583199999999999f,0.89796600000000004f,0.55236700000000005f,0.55789500000000003f,0.61421300000000001f,0.35369400000000001f,0.43603900000000001f,0.44102400000000003f,0.67491299999999999f,0.56675399999999998f,0.75500800000000001f,0.69903000000000004f,0.16439799999999999f,0.91003999999999996f,0.62837299999999996f,0.20171800000000001f,0.42951699999999998f,0.50371500000000002f,0.871174f,0.10688599999999999f,0.76117299999999999f,0.67360200000000003f,0.291937f,0.58858999999999995f,0.31528f,0.41308099999999998f,0.27446399999999999f,0.494062f,0.69612099999999999f,0.61201000000000005f,0.38275700000000001f,0.99511300000000003f,0.22880600000000001f,0.19844899999999999f,0.59584700000000002f,0.30626300000000001f,0.25239699999999998f,0.088356699999999996f,0.23608599999999999f,1,0.245278f,0.379388f,0.198824f,0.54889200000000005f,0.49276399999999998f,0.420871f,0.79463700000000004f,0.60563400000000001f,1,0.604159f,0.399841f,0.79934700000000003f,0.50718700000000005f,0.50980999999999999f,0.477383f,0.310226f,0.42697600000000002f,0.43762299999999998f,0.73571200000000003f,0.63072799999999996f,0.62578500000000004f,0.65116799999999997f,0.27773799999999998f,0.850858f,0.57807900000000001f,0.64535399999999998f,0.38369999999999999f,0.37059799999999998f,0.78254199999999996f,0.18132499999999999f,0.61439100000000002f,0.74068400000000001f,0.342441f,0.58618599999999998f,0.28690900000000003f,0.40519699999999997f,0.25921499999999997f,0.56698300000000001f,0.74821899999999997f,0.65589799999999998f,0.36825999999999998f,0.94081400000000004f,0.33615699999999998f,0.41370200000000001f,0.56155699999999997f,0.40217599999999998f,0.117698f,0.32936900000000002f,0.25457099999999999f,0.87070599999999998f,0.26098100000000002f,0.27412199999999998f,0.20624700000000001f,0.64529999999999998f,0.400758f,0.363622f,0.63683400000000001f,0.58456600000000003f,0.975603f,0.61693699999999996f,0.29540100000000002f,0.650447f,0.46422099999999999f,0.465057f,0.31246699999999999f,0.23835799999999999f,0.38369500000000001f,0.39967399999999997f,0.75391200000000003f,0.66201200000000004f,0.50426800000000005f,0.599248f,0.37866499999999997f,0.72536299999999998f,0.49321399999999999f,1,0.33283600000000002f,0.26588899999999999f,0.67407300000000003f,0.32040099999999999f,0.44001800000000002f,0.76978199999999997f,0.31641900000000001f,0.52996799999999999f,0.38050899999999999f,0.57867599999999997f,0.24901300000000001f,0.59138400000000002f,0.76171699999999998f,0.68705700000000003f,0.32443699999999998f,0.81886400000000004f,0.50536899999999996f,0.672485f,0.461783f,0.42619800000000002f,0.067887500000000003f,0.43532900000000002f,0.34795500000000001f,0.70839399999999997f,0.29332200000000003f,0.328986f,0.25825399999999998f,0.89351199999999997f,0.320131f,0.43355399999999999f,0.45930199999999999f,0.54221299999999995f,0.817241f,0.51622999999999997f,0.20530200000000001f,0.46735399999999999f,0.388683f,0.38821600000000001f,0.171262f,0.150865f,0.29171999999999998f,0.31141400000000002f,0.65887600000000002f,0.57064700000000002f,0.38361899999999999f,0.50245499999999998f,0.36411399999999999f,0.53231300000000004f,0.352989f,1,0.26198399999999999f,0.21959100000000001f,0.54403100000000004f,0.33719900000000003f,0.279173f,0.66830299999999998f,0.20843900000000001f,0.39922999999999997f,0.41867399999999999f,0.64861800000000003f,0.23413300000000001f,0.50472899999999998f,0.645347f,0.572851f,0.23282800000000001f,0.61429199999999995f,0.48527199999999998f,0.66626399999999997f,0.31657000000000002f,0.320355f,0.19142100000000001f,0.34013100000000002f,0.34206900000000001f,0.53837100000000004f,0.28113100000000002f,0.39311499999999999f,0.25139400000000001f,0.89072499999999999f,0.31064399999999998f,0.50370000000000004f,0.29909000000000002f,0.44247799999999998f,0.733128f,0.45521699999999998f,0.199322f,0.31569900000000001f,0.37585600000000002f,0.37648999999999999f,0.029145000000000001f,0.020028299999999999f,0.27957799999999999f,0.31680000000000003f,0.65595700000000001f,0.54684299999999997f,0.34966599999999998f,0.47024899999999997f,0.353765f,0.28679399999999999f,0.18018500000000001f,1,0.21083099999999999f,0.28013300000000002f,0.53585300000000002f,0.37648799999999999f,0.15367f,0.634745f,0.051044899999999997f,0.48557499999999998f,0.59311100000000005f,0.91788400000000003f,0.38047700000000001f,0.422925f,0.59937300000000004f,0.311421f,0.135654f,0.359954f,0.29574800000000001f,0.474439f,0.35333900000000001f,0.116743f,0.45431300000000002f,0.112858f,0.35931000000000002f,0.48389700000000002f,0.30160799999999999f,0.57734200000000002f,0.26266299999999998f,0.79498599999999997f,0.54957999999999996f,0.80808599999999997f,0.15251100000000001f,0.43959100000000001f,0.535941f,0.30801800000000001f,0.41983700000000002f,0.57919100000000001f,0.25042799999999998f,0.25212000000000001f,0.10285999999999999f,0.28833199999999998f,0.59967899999999996f,0.66510800000000003f,0.63628499999999999f,0.49523400000000001f,0.25161299999999998f,0.20852699999999999f,0.093907199999999996f,0.45841500000000002f,0.31895200000000001f,0.23535f,0.21518899999999999f,0.31341200000000002f,0.0472787f,0.038689300000000003f,0.086335899999999993f,0.22234599999999999f,0.36151100000000003f,0.99703699999999995f,0.238509f,0.38213999999999998f,1,0.20355400000000001f,0.47208699999999998f,0.509015f,0.206371f,0.44101299999999999f,0.79400800000000005f,0.97162300000000001f,0.79638399999999998f,0.55042999999999997f,0.68777999999999995f,0.55429799999999996f,0.043654499999999999f,0.059557699999999998f,0.21468499999999999f,0.58147000000000004f,0.27732000000000001f,0.36846600000000002f,0.121382f,0.15273900000000001f,0.078224399999999999f,0.190497f,0.31626900000000002f,0.18045600000000001f,0.405196f,0.51871599999999995f,0.15936500000000001f,0.16580800000000001f,0.19437199999999999f,0.61476399999999998f,0.55341499999999999f,0.64479399999999998f,0.44178000000000001f,0.44148999999999999f,0.22158800000000001f,1,0.57937099999999997f,0.60633899999999996f,0.52916700000000005f,0.021447500000000001f,0.41704599999999997f,0.66315199999999996f,0.894841f,0.47575200000000001f,0.16828899999999999f,0.46859000000000001f,0.30460399999999999f,0.66636899999999999f,0.30833700000000003f,0.29509099999999999f,0.76894499999999999f,0.35091099999999997f,0.49068000000000001f,0.51658400000000004f,0.400117f,0.82068700000000006f,0.54548600000000003f,0.70935700000000002f,0.50975899999999996f,0.47200599999999998f,0.15245500000000001f,0.98126500000000005f,0.45913399999999999f,0.69866600000000001f,0.24715400000000001f,0.62325299999999995f,0.25550800000000001f,0.83081499999999997f,0.088708999999999996f,0.126082f,0.0770623f,0.26332800000000001f};
float 	mydsp::ftbl1[350];
float 	mydsp::SIG2::fWave2[350] = {0.76141099999999995f,0.79780300000000004f,0.58605700000000005f,0.22503899999999999f,0.92635400000000001f,0.81387500000000002f,0.52987099999999998f,0.158915f,0.66251599999999999f,0.30841000000000002f,0.045478499999999998f,0.55608199999999997f,0.78471299999999999f,0.213035f,0.95622700000000005f,0.79516500000000001f,0.31350800000000001f,0.15853100000000001f,0.30158600000000002f,0.16832f,0.28126699999999999f,0.15423700000000001f,0.21723500000000001f,0.24723899999999999f,0.52268800000000004f,0.17030300000000001f,0.32061400000000001f,0.15485699999999999f,0.414941f,0.78836399999999995f,0.71329900000000002f,0.38159199999999999f,0.70701099999999995f,1,0.0106946f,0.359763f,0.074615600000000004f,0.43112400000000001f,0.11805300000000001f,0.52729000000000004f,0.255303f,0.64685499999999996f,0.20114499999999999f,0.91990799999999995f,0.35938900000000001f,0.253494f,0.86569499999999999f,0.082926299999999994f,0.22258900000000001f,0.041573600000000002f,0.73577400000000004f,0.76967799999999997f,0.38141599999999998f,0.197543f,0.68238900000000002f,0.61476600000000003f,0.249525f,0.289883f,0.300319f,0.443691f,0.27527200000000002f,0.37021799999999999f,0.74878999999999996f,0.161247f,0.63435299999999994f,0.498498f,0.22198799999999999f,0.35063699999999998f,0.43681700000000001f,0.43646299999999999f,0.52507999999999999f,0.84264600000000001f,0.195324f,0.22475500000000001f,0.54568099999999997f,0.35377799999999998f,0.26904400000000001f,0.32781399999999999f,0.44895200000000002f,0.85230499999999998f,0.38050299999999998f,1,0.458063f,0.56505799999999995f,0.35463499999999998f,0.65952900000000003f,0.44948500000000002f,0.802014f,0.28344599999999998f,0.521563f,0.374639f,0.65211200000000002f,0.18104200000000001f,0.46839399999999998f,0.430116f,0.15720700000000001f,0.414995f,0.29273700000000002f,0.48778500000000002f,0.47767999999999999f,0.48144500000000001f,0.55698800000000004f,0.56113199999999996f,0.37826500000000002f,0.291462f,0.32324999999999998f,0.48260199999999998f,0.32824799999999998f,0.19679199999999999f,0.71225400000000005f,0.38980599999999999f,0.307751f,0.79287600000000003f,0.199098f,0.28883799999999998f,0.146811f,0.0178444f,0.39401700000000001f,0.58821199999999996f,0.48922599999999999f,0.70148600000000005f,0.940303f,0.21319099999999999f,0.077884499999999995f,0.47446300000000002f,0.60997199999999996f,0.16338f,0.40837600000000002f,0.33086399999999999f,0.88998999999999995f,0.079810099999999995f,1,0.16717199999999999f,0.208727f,0.227549f,0.82590300000000005f,0.53189699999999995f,0.58094599999999996f,0.215339f,0.24731900000000001f,0.268148f,0.50408799999999998f,0.16095499999999999f,0.170316f,0.230769f,0.15119099999999999f,0.082503099999999996f,0.14132800000000001f,0.28807899999999997f,0.49967600000000001f,0.42035499999999998f,0.48776399999999998f,0.75370999999999999f,0.49224800000000002f,0.181364f,0.20594000000000001f,0.52497000000000005f,0.32564100000000001f,0.23682700000000001f,0.93184199999999995f,0.47298099999999998f,0.312162f,0.90103200000000006f,0.270478f,0.16711200000000001f,0.0709698f,0.16600400000000001f,0.29074499999999998f,0.42589300000000002f,0.40363300000000002f,0.58177199999999996f,0.85569399999999995f,0.032558700000000003f,0.056835900000000002f,0.241923f,0.79930999999999996f,0.18196200000000001f,0.53028299999999995f,0.41560999999999998f,1,0.029150100000000002f,0.83115499999999998f,0.119755f,0.102188f,0.13203699999999999f,0.76602999999999999f,0.44222099999999998f,0.1749f,0.142175f,0.014079400000000001f,0.4375f,0.85185999999999995f,0.19683600000000001f,0.090752200000000005f,0.55167299999999997f,0.25652799999999998f,0.042437700000000002f,0.49036299999999999f,0.108178f,0.50327599999999995f,0.22658400000000001f,0.31275799999999998f,0.82407900000000001f,0.48411999999999999f,0.034733800000000002f,0.061942799999999999f,0.25509700000000002f,0.14527300000000001f,0.190359f,0.99529699999999999f,0.50341999999999998f,0.21757499999999999f,0.79397499999999999f,0.35717900000000002f,0.040972799999999997f,0.0187931f,0.41445799999999999f,0.15844f,0.34623300000000001f,0.077167299999999994f,0.17511099999999999f,0.38056699999999999f,0.49740899999999999f,0.316164f,0.48866900000000002f,1,0.420657f,0.44233299999999998f,0.24706f,0.79640699999999998f,0.0104146f,0.227079f,0.10684f,0.028987300000000001f,0.76756999999999997f,0.0643122f,0.042309800000000002f,0.71552199999999999f,0.47211700000000001f,0.39257700000000001f,0.66043300000000005f,0.80357500000000004f,0.18865299999999999f,0.0191653f,0.87321199999999999f,0.44871899999999998f,0.0147128f,0.61896700000000004f,0.30718000000000001f,0.34589900000000001f,0.13139400000000001f,0.19322500000000001f,0.715283f,0.40561999999999998f,0.040637f,0.050333599999999999f,0.054433099999999998f,0.045202300000000001f,0.15230199999999999f,0.89454900000000004f,0.44334299999999999f,0.172071f,0.64766699999999999f,0.32899299999999998f,0.041601399999999997f,0.022948799999999998f,0.55107099999999998f,0.42354399999999998f,0.86236199999999996f,0.36352600000000002f,0.76992899999999997f,0.12345200000000001f,0.71070199999999994f,0.394895f,0.55663799999999997f,1,0.45092500000000002f,0.42284899999999997f,0.092187000000000005f,0.41389199999999998f,0.0099537199999999992f,0.32114599999999999f,0.16062399999999999f,0.0300681f,0.915385f,0.47549999999999998f,0.50695100000000004f,0.38754899999999998f,0.27559099999999997f,0.468281f,0.184776f,0.186837f,0.188195f,0.020278500000000001f,0.69713599999999998f,0.408862f,0.011693500000000001f,0.349823f,0.20230100000000001f,0.46137899999999998f,0.055902300000000002f,0.058257099999999999f,0.26060800000000001f,0.18187500000000001f,0.027173900000000001f,0.024957799999999999f,0.68508899999999995f,0.47038400000000002f,0.283194f,0.33105000000000001f,0.138349f,0.33806799999999998f,0.48199199999999998f,0.17824200000000001f,0.015594200000000001f,0.011043499999999999f,0.783771f,0.44270700000000002f,0.61647799999999997f,0.38154199999999999f,0.51089200000000001f,0.045984999999999998f,0.30311900000000003f,0.073190900000000003f,0.54771499999999995f,0.348941f,0.149981f,0.30215799999999998f,0.28448200000000001f,0.398177f,0.0041304899999999997f,0.18073900000000001f,0.062839000000000006f,0.013345900000000001f,0.34708800000000001f,0.57637000000000005f,0.24076400000000001f,0.97848100000000005f,0.45275500000000002f,0.52974200000000005f,0.34047100000000002f,0.66228200000000004f,0.44430500000000001f,0.042990100000000003f,1,0.36193999999999998f,0.018337200000000001f,0.62689300000000003f,0.55284999999999995f,0.384936f};
float 	mydsp::ftbl2[350];
float 	mydsp::SIG3::fWave3[350] = {0.92550699999999997f,0.59752000000000005f,0.096567100000000003f,0.45412000000000002f,0.98977300000000001f,0.59349799999999997f,0.51254100000000002f,0.124241f,0.70541100000000001f,0.29239599999999999f,0.67339899999999997f,0.30218099999999998f,0.026234f,0.28624899999999998f,0.55626699999999996f,1,0.25042599999999998f,0.107711f,0.42729899999999998f,0.33629500000000001f,0.61625700000000005f,0.21442f,0.084529400000000005f,0.23136300000000001f,0.52272399999999997f,0.559114f,0.34847f,0.85419699999999998f,0.83557599999999999f,0.73503600000000002f,0.28849399999999997f,0.117122f,0.40968599999999999f,0.36357499999999998f,0.48494300000000001f,0.17086200000000001f,0.42053099999999999f,0.164793f,0.233847f,0.861232f,0.21403700000000001f,0.28346199999999999f,0.173153f,0.87612199999999996f,0.60780900000000004f,0.29474499999999998f,0.14314199999999999f,0.332009f,0.49187799999999998f,0.62610399999999999f,0.96202699999999997f,0.58429799999999998f,0.21365300000000001f,0.42045199999999999f,0.81232899999999997f,0.54517199999999999f,0.38074400000000003f,0.331536f,0.38680100000000001f,0.24890899999999999f,0.68875600000000003f,0.31390400000000002f,0.37789400000000001f,0.59584599999999999f,0.41227399999999997f,0.73962600000000001f,0.54114799999999996f,0.39300499999999999f,0.65663700000000003f,0.84767199999999998f,0.93065299999999995f,0.28828900000000002f,0.40493800000000002f,0.65798900000000005f,0.76394899999999999f,0.57408499999999996f,0.28224100000000002f,1,0.42913099999999998f,0.57204900000000003f,0.73486799999999997f,0.57747700000000002f,0.52078899999999995f,0.35559299999999999f,0.89006700000000005f,0.27239099999999999f,0.44822299999999998f,0.42396899999999998f,0.392237f,0.85609100000000005f,0.058379399999999998f,0.78496699999999997f,0.35952699999999999f,0.57656700000000005f,0.201513f,0.64201299999999994f,0.41930800000000001f,0.340667f,0.42319000000000001f,0.86081200000000002f,0.69401999999999997f,0.423568f,0.37698700000000002f,0.56845299999999999f,0.50230200000000003f,0.28071600000000002f,0.46404099999999998f,0.39560099999999998f,0.19985f,0.095039799999999994f,0.64278999999999997f,0.228326f,0.48491099999999998f,0.84235300000000002f,0.16140399999999999f,0.40343200000000001f,0.65554900000000005f,0.40909800000000002f,0.69939200000000001f,0.87605f,1,0.18560599999999999f,0.41425499999999998f,0.69520499999999996f,0.73261200000000004f,0.478298f,0.24947f,0.92773899999999998f,0.21313499999999999f,0.227382f,0.976352f,0.64274500000000001f,0.37631100000000001f,0.26067400000000002f,0.81103400000000003f,0.26463100000000001f,0.239979f,0.26189699999999999f,0.19164200000000001f,0.78166999999999998f,0.390679f,0.38243700000000003f,0.20671400000000001f,0.22472f,0.067633200000000004f,0.50261100000000003f,0.30145499999999997f,0.24102899999999999f,0.22450500000000001f,0.72119299999999997f,0.43634800000000001f,0.25406200000000001f,0.48049599999999998f,0.77237100000000003f,0.21068100000000001f,0.10341500000000001f,0.48533799999999999f,0.378334f,0.22848399999999999f,0.11487700000000001f,0.68676000000000004f,0.29694199999999998f,0.50741999999999998f,0.99746999999999997f,0.037710300000000002f,0.132212f,0.31954700000000003f,0.19203200000000001f,0.52057399999999998f,0.58584400000000003f,0.41936200000000001f,0.084731699999999993f,0.134544f,0.19476199999999999f,0.61668900000000004f,0.39735999999999999f,0.29880899999999999f,0.91474599999999995f,0.051337099999999997f,0.0543569f,0.98915900000000001f,0.60289199999999998f,0.14558199999999999f,0.102149f,0.129022f,0.11648500000000001f,0.27998800000000001f,0.39427000000000001f,0.29013899999999998f,1,0.70865500000000003f,0.780555f,0.38752599999999998f,0.0395217f,0.0096406700000000005f,0.24368000000000001f,0.074062500000000003f,0.61931499999999995f,0.44739499999999999f,0.29249700000000001f,0.295458f,0.163748f,0.52137500000000003f,0.864533f,0.077340800000000001f,0.033423099999999997f,0.34512100000000001f,0.27886f,0.22387599999999999f,0.30775599999999997f,0.76310599999999995f,0.424707f,0.487201f,0.96896199999999999f,0.0091174700000000008f,0.032465300000000002f,0.33427499999999999f,0.16678699999999999f,0.312498f,0.264262f,0.35487999999999997f,0.37558999999999998f,0.26109399999999999f,0.56500600000000001f,0.474935f,0.31352000000000002f,0.251249f,0.73535200000000001f,0.018907199999999999f,0.015363399999999999f,0.78622499999999995f,0.50329900000000005f,0.36903799999999998f,0.25076500000000002f,0.67301900000000003f,0.387573f,0.74202500000000005f,0.74905600000000006f,0.261714f,0.75186799999999998f,0.77181599999999995f,1,0.459484f,0.0124402f,0.010539400000000001f,0.96410899999999999f,0.45705200000000001f,0.53231600000000001f,0.40712799999999999f,0.697241f,0.1522f,0.089589299999999997f,0.40617500000000001f,0.65103999999999995f,0.023395099999999999f,0.010107f,0.072234699999999999f,0.066633999999999999f,0.195489f,0.41674f,0.654451f,0.38278200000000001f,0.305396f,0.63150099999999998f,0.00162802f,0.0140906f,0.76291500000000001f,0.41024500000000003f,0.18943599999999999f,0.060446199999999999f,0.62494099999999997f,0.43978099999999998f,0.51627299999999998f,0.89667799999999998f,0.27329799999999999f,0.20286799999999999f,0.099602200000000002f,0.25765700000000002f,0.017450799999999999f,0.015785899999999999f,0.42943300000000001f,0.202184f,0.44311099999999998f,0.34381099999999998f,0.44756200000000002f,0.26869399999999999f,0.75355099999999997f,0.52942599999999995f,0.077297299999999999f,0.097696000000000005f,0.44641399999999998f,0.26167800000000002f,0.16903499999999999f,0.011621899999999999f,0.020739899999999999f,1,0.48885600000000001f,0.41302899999999998f,0.25266100000000002f,0.148369f,0.091964400000000002f,0.0330634f,0.268764f,0.44184899999999999f,0.013987299999999999f,0.010858400000000001f,0.65779900000000002f,0.48824800000000002f,0.37543300000000002f,0.958179f,0.76149199999999995f,0.40949000000000002f,0.15170900000000001f,0.31493100000000002f,0.0036118000000000001f,0.013306999999999999f,1,0.60534299999999996f,0.55050600000000005f,0.36351600000000001f,0.255278f,0.13753699999999999f,0.44888099999999997f,0.86761500000000003f,0.48324699999999998f,0.30862200000000001f,0.34844399999999998f,0.53483499999999995f,0.0157716f,0.0128965f,0.14760799999999999f,0.076261099999999998f,0.76222400000000001f,0.51158499999999996f,0.98586300000000004f,0.54022700000000001f,0.69169099999999994f,0.90529599999999999f,0.39752100000000001f,0.69794f,0.42328900000000003f,0.92461300000000002f,0.49155900000000002f,0.0056791100000000002f,0.010600200000000001f,0.64791600000000005f,0.32418200000000003f,0.57944899999999999f,0.451936f,0.87789700000000004f};
float 	mydsp::ftbl3[350];
