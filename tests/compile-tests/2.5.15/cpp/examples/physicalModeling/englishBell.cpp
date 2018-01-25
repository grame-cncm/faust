/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "EnglishChurchBell"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


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

#include <cmath>
#include <math.h>

static float fmydspSIG0Wave0[350] = {0.694274008f,0.471697986f,0.172389999f,0.585446f,0.397985995f,0.919579029f,0.531947017f,0.100204997f,0.639469028f,0.672209024f,0.144345f,0.416595012f,0.124108002f,0.380591005f,0.256577998f,0.646031022f,0.852199972f,0.0224376004f,0.382762015f,0.143924996f,0.368690997f,0.430555999f,0.32317999f,0.142956004f,0.274520993f,0.713823974f,0.442793995f,0.352472991f,0.247756004f,0.415152013f,1.0f,0.401868999f,0.197981f,0.279509991f,0.210249007f,0.369740009f,0.369226992f,0.155769005f,0.272368014f,0.335711986f,0.31645f,0.714102983f,0.285780996f,0.220060006f,0.827704012f,0.206341997f,0.180177003f,0.311477989f,0.197606996f,0.575474977f,0.473311007f,0.587231994f,0.502879977f,0.33730799f,0.304513991f,0.429039001f,0.351521999f,0.341372997f,0.175081f,0.561748028f,0.439172f,0.323163986f,0.540517986f,0.536522985f,0.0743864998f,0.213416994f,0.358011991f,0.47449401f,0.310274005f,0.839412987f,0.241372004f,0.202343002f,0.480634004f,0.995684981f,0.373739988f,0.133998007f,0.52067399f,0.207514003f,1.0f,0.101239003f,0.279536009f,0.185984999f,0.436293006f,0.624109983f,0.334518999f,0.283585012f,0.179316998f,0.353846997f,0.449544996f,0.574127972f,0.135171995f,0.538275003f,0.476424009f,0.832903028f,0.164197996f,0.188562006f,0.135977998f,0.390127987f,0.131044999f,0.312065005f,0.142139003f,0.0255900994f,0.266947001f,0.371607006f,0.0168434996f,0.0249467995f,0.508916974f,0.354409993f,0.283347994f,0.628154993f,0.292477995f,0.358350009f,0.342568994f,0.441237003f,0.886699021f,0.0174697991f,0.00641842978f,0.555320024f,0.88012898f,0.0306908991f,0.290080994f,0.248815998f,0.981736004f,0.324624002f,0.213676006f,0.432884991f,0.0981559008f,0.444148988f,0.395554006f,0.525068998f,0.077130802f,0.0488803983f,0.591320992f,0.108043998f,0.443801999f,0.740318f,0.599438012f,0.293092996f,1.0f,0.141662002f,0.910031021f,0.226126f,0.299701989f,0.341472f,0.0568060987f,0.222494006f,0.91871798f,0.199478f,0.216619998f,0.107758999f,0.692323983f,0.556335986f,0.281717986f,0.430831999f,0.341655999f,0.60809499f,0.342128992f,0.31131199f,0.229953006f,0.695087016f,0.0761488974f,0.349817991f,0.361705989f,0.577611029f,0.147797003f,0.327376008f,0.465714991f,0.342902005f,0.521381021f,0.836827993f,0.241111994f,0.284393996f,0.539315999f,0.143408f,0.517019987f,1.0f,0.236335993f,0.480333f,0.676743984f,0.807582021f,0.468620986f,0.236953005f,0.411603987f,0.579250991f,0.425098002f,0.375990003f,0.461176008f,0.276529998f,0.462368011f,0.613004029f,0.666849017f,0.954715014f,0.161506996f,0.170433f,0.290461004f,0.117302999f,0.365132987f,0.233794004f,0.194567993f,0.338874012f,0.523380995f,0.39835f,0.447838992f,0.65289098f,0.157079995f,0.340353996f,0.442169994f,0.338764012f,0.184396997f,0.771606982f,0.160502002f,0.324487001f,0.477499008f,0.831519008f,0.0168763995f,0.154264003f,0.201865003f,0.237785995f,0.390065998f,0.880164027f,0.284233987f,0.162836999f,0.437557012f,0.227845997f,0.399340004f,1.0f,0.158106998f,0.396903008f,0.513028979f,0.676456988f,0.204282001f,0.0895574987f,0.555410028f,0.73248601f,0.125062004f,0.171229005f,0.0816460028f,0.0541394018f,0.396160007f,0.454288006f,0.466863006f,0.928842008f,0.155393004f,0.262849987f,0.113453001f,0.133163005f,0.302020997f,0.612616003f,0.228392005f,0.195617005f,0.287236005f,0.198762f,0.499884009f,0.809139013f,0.00929925032f,0.084029898f,0.286446005f,0.182111993f,0.186043993f,0.754137993f,0.279556006f,0.266948014f,0.494291008f,1.0f,0.321283996f,0.0230981f,0.0375537015f,0.262531012f,0.602204025f,0.489924997f,0.633077025f,0.407409012f,0.422255993f,0.0910641029f,0.357935011f,0.550179005f,0.106192f,0.132366002f,0.376231015f,0.35115099f,0.0420302004f,0.0372182988f,0.696335018f,0.840821028f,0.855234981f,0.249247998f,0.860010982f,0.340481013f,0.285580009f,0.363038987f,0.324122012f,0.515699029f,0.228130996f,0.172591999f,0.0188723002f,0.168243006f,0.995105028f,0.741759002f,0.107092999f,0.0703490004f,0.136636004f,0.0780455023f,0.315748006f,0.502201021f,0.0190421995f,0.0339139998f,0.225723997f,0.160236001f,0.184101f,0.564203024f,0.247317001f,0.284224987f,0.327152997f,0.651443005f,0.593470991f,0.0163899008f,0.0141048003f,0.521130025f,1.0f,0.105108999f,0.530936003f,0.363723993f,0.924808979f,0.250409991f,0.692879975f,0.414121985f,0.0793657973f,0.34781301f,0.441731006f,0.476428002f,0.0808833987f,0.0581637993f,0.557238996f,0.556514978f,0.746083975f,0.582228005f,0.177230999f,0.158425003f,0.850902975f,0.755271018f,0.673614025f,0.317059994f,0.0515386015f,0.201897994f,0.0577937998f,0.232031003f,0.734987974f,0.141593993f,0.267062008f,0.145806998f};

class mydspSIG0 {
	
  private:
	
	int fmydspSIG0Wave0_idx;
	
  public:
	
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
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG0Wave0[fmydspSIG0Wave0_idx];
			fmydspSIG0Wave0_idx = ((1 + fmydspSIG0Wave0_idx) % 350);
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[350];
float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	int iRec3[2];
	float fConst6;
	float fConst7;
	float fRec2[3];
	float fConst8;
	float fRec1[3];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fConst9;
	FAUSTFLOAT fHslider2;
	float fVec1[2];
	float fRec4[2];
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec0[3];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec5[3];
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec6[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec7[3];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec8[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec9[3];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec10[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec11[3];
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec12[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec13[3];
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec14[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec15[3];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec16[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec17[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec18[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec19[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec20[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec21[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec22[3];
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec23[3];
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec24[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec25[3];
	float fConst78;
	float fConst79;
	float fConst80;
	float fRec26[3];
	float fConst81;
	float fConst82;
	float fConst83;
	float fRec27[3];
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec28[3];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec29[3];
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec30[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec31[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec32[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec33[3];
	float fConst102;
	float fConst103;
	float fConst104;
	float fRec34[3];
	float fConst105;
	float fConst106;
	float fConst107;
	float fRec35[3];
	float fConst108;
	float fConst109;
	float fConst110;
	float fRec36[3];
	float fConst111;
	float fConst112;
	float fConst113;
	float fRec37[3];
	float fConst114;
	float fConst115;
	float fConst116;
	float fRec38[3];
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec39[3];
	float fConst120;
	float fConst121;
	float fConst122;
	float fRec40[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fRec41[3];
	float fConst126;
	float fConst127;
	float fConst128;
	float fRec42[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec43[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec44[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec45[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec46[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec47[3];
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec48[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec49[3];
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec50[3];
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec51[3];
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec52[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec53[3];
	
 public:
	
	void metadata(Meta* m) { 
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

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
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
	
	static void classInit(int samplingFreq) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(350, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = tanf((31.415926f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 1.41421354f) / fConst2) + 1.0f));
		fConst5 = (1.0f / mydsp_faustpower2_f(fConst2));
		fConst6 = (((fConst3 + -1.41421354f) / fConst2) + 1.0f);
		fConst7 = (2.0f * (1.0f - fConst5));
		fConst8 = (2.0f * (0.0f - fConst5));
		fConst9 = (0.00400000019f * fConst0);
		fConst10 = (0.00200000009f * fConst0);
		fConst11 = (500.0f / fConst0);
		fConst12 = powf(0.00100000005f, (1.0f / (20.3469906f * fConst0)));
		fConst13 = ((0.0f - (2.0f * fConst12)) * cosf((1630.04053f / fConst0)));
		fConst14 = mydsp_faustpower2_f(fConst12);
		fConst15 = powf(0.00100000005f, (1.0f / (20.2682228f * fConst0)));
		fConst16 = ((0.0f - (2.0f * fConst15)) * cosf((1645.28345f / fConst0)));
		fConst17 = mydsp_faustpower2_f(fConst15);
		fConst18 = powf(0.00100000005f, (1.0f / (13.6507998f * fConst0)));
		fConst19 = ((0.0f - (2.0f * fConst18)) * cosf((3099.69019f / fConst0)));
		fConst20 = mydsp_faustpower2_f(fConst18);
		fConst21 = powf(0.00100000005f, (1.0f / (13.6223917f * fConst0)));
		fConst22 = ((0.0f - (2.0f * fConst21)) * cosf((3106.85913f / fConst0)));
		fConst23 = mydsp_faustpower2_f(fConst21);
		fConst24 = powf(0.00100000005f, (1.0f / (11.0956459f * fConst0)));
		fConst25 = ((0.0f - (2.0f * fConst24)) * cosf((3789.06226f / fConst0)));
		fConst26 = mydsp_faustpower2_f(fConst24);
		fConst27 = powf(0.00100000005f, (1.0f / (11.0589275f * fConst0)));
		fConst28 = ((0.0f - (2.0f * fConst27)) * cosf((3799.70605f / fConst0)));
		fConst29 = mydsp_faustpower2_f(fConst27);
		fConst30 = powf(0.00100000005f, (1.0f / (8.6621294f * fConst0)));
		fConst31 = ((0.0f - (2.0f * fConst30)) * cosf((4552.58252f / fConst0)));
		fConst32 = mydsp_faustpower2_f(fConst30);
		fConst33 = powf(0.00100000005f, (1.0f / (8.6582489f * fConst0)));
		fConst34 = ((0.0f - (2.0f * fConst33)) * cosf((4553.9082f / fConst0)));
		fConst35 = mydsp_faustpower2_f(fConst33);
		fConst36 = powf(0.00100000005f, (1.0f / (7.56375885f * fConst0)));
		fConst37 = ((0.0f - (2.0f * fConst36)) * cosf((4944.77246f / fConst0)));
		fConst38 = mydsp_faustpower2_f(fConst36);
		fConst39 = powf(0.00100000005f, (1.0f / (5.38026142f * fConst0)));
		fConst40 = ((0.0f - (2.0f * fConst39)) * cosf((5855.25635f / fConst0)));
		fConst41 = mydsp_faustpower2_f(fConst39);
		fConst42 = powf(0.00100000005f, (1.0f / (5.36750793f * fConst0)));
		fConst43 = ((0.0f - (2.0f * fConst42)) * cosf((5861.24414f / fConst0)));
		fConst44 = mydsp_faustpower2_f(fConst42);
		fConst45 = powf(0.00100000005f, (1.0f / (5.2272315f * fConst0)));
		fConst46 = ((0.0f - (2.0f * fConst45)) * cosf((5927.73926f / fConst0)));
		fConst47 = mydsp_faustpower2_f(fConst45);
		fConst48 = powf(0.00100000005f, (1.0f / (5.18655729f * fConst0)));
		fConst49 = ((0.0f - (2.0f * fConst48)) * cosf((5947.24219f / fConst0)));
		fConst50 = mydsp_faustpower2_f(fConst48);
		fConst51 = powf(0.00100000005f, (1.0f / (5.17903233f * fConst0)));
		fConst52 = ((0.0f - (2.0f * fConst51)) * cosf((5950.86133f / fConst0)));
		fConst53 = mydsp_faustpower2_f(fConst51);
		fConst54 = powf(0.00100000005f, (1.0f / (5.10531187f * fConst0)));
		fConst55 = ((0.0f - (2.0f * fConst54)) * cosf((5986.50586f / fConst0)));
		fConst56 = mydsp_faustpower2_f(fConst54);
		fConst57 = powf(0.00100000005f, (1.0f / (4.23579216f * fConst0)));
		fConst58 = ((0.0f - (2.0f * fConst57)) * cosf((6435.48975f / fConst0)));
		fConst59 = mydsp_faustpower2_f(fConst57);
		fConst60 = powf(0.00100000005f, (1.0f / (4.11567307f * fConst0)));
		fConst61 = ((0.0f - (2.0f * fConst60)) * cosf((6502.21729f / fConst0)));
		fConst62 = mydsp_faustpower2_f(fConst60);
		fConst63 = powf(0.00100000005f, (1.0f / (2.43636394f * fConst0)));
		fConst64 = ((0.0f - (2.0f * fConst63)) * cosf((7612.64453f / fConst0)));
		fConst65 = mydsp_faustpower2_f(fConst63);
		fConst66 = powf(0.00100000005f, (1.0f / (2.43147063f * fConst0)));
		fConst67 = ((0.0f - (2.0f * fConst66)) * cosf((7616.54004f / fConst0)));
		fConst68 = mydsp_faustpower2_f(fConst66);
		fConst69 = powf(0.00100000005f, (1.0f / (2.24652147f * fConst0)));
		fConst70 = ((0.0f - (2.0f * fConst69)) * cosf((7767.77637f / fConst0)));
		fConst71 = mydsp_faustpower2_f(fConst69);
		fConst72 = powf(0.00100000005f, (1.0f / (1.55517876f * fConst0)));
		fConst73 = ((0.0f - (2.0f * fConst72)) * cosf((8420.78809f / fConst0)));
		fConst74 = mydsp_faustpower2_f(fConst72);
		fConst75 = powf(0.00100000005f, (1.0f / (1.54968154f * fConst0)));
		fConst76 = ((0.0f - (2.0f * fConst75)) * cosf((8426.69434f / fConst0)));
		fConst77 = mydsp_faustpower2_f(fConst75);
		fConst78 = powf(0.00100000005f, (1.0f / (0.985444903f * fConst0)));
		fConst79 = ((0.0f - (2.0f * fConst78)) * cosf((9127.14355f / fConst0)));
		fConst80 = mydsp_faustpower2_f(fConst78);
		fConst81 = powf(0.00100000005f, (1.0f / (0.982208788f * fConst0)));
		fConst82 = ((0.0f - (2.0f * fConst81)) * cosf((9131.85547f / fConst0)));
		fConst83 = mydsp_faustpower2_f(fConst81);
		fConst84 = powf(0.00100000005f, (1.0f / (0.980528831f * fConst0)));
		fConst85 = ((0.0f - (2.0f * fConst84)) * cosf((9134.30664f / fConst0)));
		fConst86 = mydsp_faustpower2_f(fConst84);
		fConst87 = powf(0.00100000005f, (1.0f / (0.964770973f * fConst0)));
		fConst88 = ((0.0f - (2.0f * fConst87)) * cosf((9157.42871f / fConst0)));
		fConst89 = mydsp_faustpower2_f(fConst87);
		fConst90 = powf(0.00100000005f, (1.0f / (0.957210004f * fConst0)));
		fConst91 = ((0.0f - (2.0f * fConst90)) * cosf((9168.6123f / fConst0)));
		fConst92 = mydsp_faustpower2_f(fConst90);
		fConst93 = powf(0.00100000005f, (1.0f / (0.950995624f * fConst0)));
		fConst94 = ((0.0f - (2.0f * fConst93)) * cosf((9177.84863f / fConst0)));
		fConst95 = mydsp_faustpower2_f(fConst93);
		fConst96 = powf(0.00100000005f, (1.0f / (0.860745311f * fConst0)));
		fConst97 = ((0.0f - (2.0f * fConst96)) * cosf((9316.76953f / fConst0)));
		fConst98 = mydsp_faustpower2_f(fConst96);
		fConst99 = powf(0.00100000005f, (1.0f / (0.85983783f * fConst0)));
		fConst100 = ((0.0f - (2.0f * fConst99)) * cosf((9318.21484f / fConst0)));
		fConst101 = mydsp_faustpower2_f(fConst99);
		fConst102 = powf(0.00100000005f, (1.0f / (0.723724186f * fConst0)));
		fConst103 = ((0.0f - (2.0f * fConst102)) * cosf((9547.61426f / fConst0)));
		fConst104 = mydsp_faustpower2_f(fConst102);
		fConst105 = powf(0.00100000005f, (1.0f / (0.630567133f * fConst0)));
		fConst106 = ((0.0f - (2.0f * fConst105)) * cosf((9721.78418f / fConst0)));
		fConst107 = mydsp_faustpower2_f(fConst105);
		fConst108 = powf(0.00100000005f, (1.0f / (0.572528303f * fConst0)));
		fConst109 = ((0.0f - (2.0f * fConst108)) * cosf((9839.1543f / fConst0)));
		fConst110 = mydsp_faustpower2_f(fConst108);
		fConst111 = powf(0.00100000005f, (1.0f / (0.540078342f * fConst0)));
		fConst112 = ((0.0f - (2.0f * fConst111)) * cosf((9908.26953f / fConst0)));
		fConst113 = mydsp_faustpower2_f(fConst111);
		fConst114 = powf(0.00100000005f, (1.0f / (0.261076301f * fConst0)));
		fConst115 = ((0.0f - (2.0f * fConst114)) * cosf((10665.5186f / fConst0)));
		fConst116 = mydsp_faustpower2_f(fConst114);
		fConst117 = powf(0.00100000005f, (1.0f / (0.0919547901f * fConst0)));
		fConst118 = ((0.0f - (2.0f * fConst117)) * cosf((11476.9287f / fConst0)));
		fConst119 = mydsp_faustpower2_f(fConst117);
		fConst120 = powf(0.00100000005f, (1.0f / (0.0449172668f * fConst0)));
		fConst121 = ((0.0f - (2.0f * fConst120)) * cosf((11891.3057f / fConst0)));
		fConst122 = mydsp_faustpower2_f(fConst120);
		fConst123 = powf(0.00100000005f, (1.0f / (0.0429995693f * fConst0)));
		fConst124 = ((0.0f - (2.0f * fConst123)) * cosf((11913.4844f / fConst0)));
		fConst125 = mydsp_faustpower2_f(fConst123);
		fConst126 = powf(0.00100000005f, (1.0f / (0.0410126187f * fConst0)));
		fConst127 = ((0.0f - (2.0f * fConst126)) * cosf((11937.1729f / fConst0)));
		fConst128 = mydsp_faustpower2_f(fConst126);
		fConst129 = powf(0.00100000005f, (1.0f / (0.0367931202f * fConst0)));
		fConst130 = ((0.0f - (2.0f * fConst129)) * cosf((11990.1396f / fConst0)));
		fConst131 = mydsp_faustpower2_f(fConst129);
		fConst132 = powf(0.00100000005f, (1.0f / (0.00724635459f * fConst0)));
		fConst133 = ((0.0f - (2.0f * fConst132)) * cosf((12591.1895f / fConst0)));
		fConst134 = mydsp_faustpower2_f(fConst132);
		fConst135 = powf(0.00100000005f, (1.0f / (0.00706494786f * fConst0)));
		fConst136 = ((0.0f - (2.0f * fConst135)) * cosf((12598.2266f / fConst0)));
		fConst137 = mydsp_faustpower2_f(fConst135);
		fConst138 = powf(0.00100000005f, (1.0f / (0.00693406956f * fConst0)));
		fConst139 = ((0.0f - (2.0f * fConst138)) * cosf((12603.3789f / fConst0)));
		fConst140 = mydsp_faustpower2_f(fConst138);
		fConst141 = powf(0.00100000005f, (1.0f / (0.00691822032f * fConst0)));
		fConst142 = ((0.0f - (2.0f * fConst141)) * cosf((12604.0068f / fConst0)));
		fConst143 = mydsp_faustpower2_f(fConst141);
		fConst144 = powf(0.00100000005f, (1.0f / (0.00103725458f * fConst0)));
		fConst145 = ((0.0f - (2.0f * fConst144)) * cosf((12989.9834f / fConst0)));
		fConst146 = mydsp_faustpower2_f(fConst144);
		fConst147 = powf(0.00100000005f, (1.0f / (0.00050088542f * fConst0)));
		fConst148 = ((0.0f - (2.0f * fConst147)) * cosf((13084.2305f / fConst0)));
		fConst149 = mydsp_faustpower2_f(fConst147);
		fConst150 = powf(0.00100000005f, (1.0f / (0.000389558641f * fConst0)));
		fConst151 = ((0.0f - (2.0f * fConst150)) * cosf((13111.8135f / fConst0)));
		fConst152 = mydsp_faustpower2_f(fConst150);
		fConst153 = powf(0.00100000005f, (1.0f / (1.37579882e-05f * fConst0)));
		fConst154 = ((0.0f - (2.0f * fConst153)) * cosf((13323.8711f / fConst0)));
		fConst155 = mydsp_faustpower2_f(fConst153);
		fConst156 = powf(0.00100000005f, (1.0f / (1.1713787e-06f * fConst0)));
		fConst157 = ((0.0f - (2.0f * fConst156)) * cosf((13381.8652f / fConst0)));
		fConst158 = mydsp_faustpower2_f(fConst156);
		fConst159 = powf(0.00100000005f, (1.0f / (1.70003645e-07f * fConst0)));
		fConst160 = ((0.0f - (2.0f * fConst159)) * cosf((13403.4795f / fConst0)));
		fConst161 = mydsp_faustpower2_f(fConst159);
		
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(6500.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec3[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
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
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec15[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec16[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec17[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec22[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec23[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec24[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec25[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec26[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec27[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec28[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec29[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec30[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec31[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec32[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec33[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec34[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec35[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec36[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec37[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec38[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec39[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec40[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec41[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec42[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec43[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec44[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec45[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec46[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec47[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec48[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec49[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec50[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec51[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec52[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec53[l55] = 0.0f;
			
		}
		
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
		ui_interface->declare(&fEntry0, "0", "");
		ui_interface->addNumEntry("strikePosition", &fEntry0, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->addHorizontalSlider("strikeCutOff", &fHslider1, 6500.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->addHorizontalSlider("strikeSharpness", &fHslider2, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->addHorizontalSlider("gain", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fButton0, "4", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = (50 * int(float(fEntry0)));
		float fSlow1 = tanf((fConst1 * float(fHslider1)));
		float fSlow2 = (1.0f / fSlow1);
		float fSlow3 = (((fSlow2 + 1.41421354f) / fSlow1) + 1.0f);
		float fSlow4 = (float(fHslider0) / fSlow3);
		float fSlow5 = (1.0f / fSlow3);
		float fSlow6 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
		float fSlow7 = (((fSlow2 + -1.41421354f) / fSlow1) + 1.0f);
		float fSlow8 = float(fButton0);
		float fSlow9 = float(fHslider2);
		float fSlow10 = (fConst9 * fSlow9);
		float fSlow11 = (fConst10 * fSlow9);
		float fSlow12 = (fConst11 / fSlow9);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.65661287e-10f * float(iRec3[0])) - (fConst4 * ((fConst6 * fRec2[2]) + (fConst7 * fRec2[1]))));
			fRec1[0] = ((fConst4 * (((fConst5 * fRec2[0]) + (fConst8 * fRec2[1])) + (fConst5 * fRec2[2]))) - (fSlow5 * ((fSlow6 * fRec1[1]) + (fSlow7 * fRec1[2]))));
			fVec0[0] = fSlow8;
			fVec1[0] = fSlow9;
			fRec4[0] = ((((fSlow8 - fVec0[1]) > 0.0f) > 0)?0.0f:min(fSlow10, ((fRec4[1] + (fConst9 * (fSlow9 - fVec1[1]))) + 1.0f)));
			int iTemp0 = (fRec4[0] < fSlow11);
			float fTemp1 = (fSlow4 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * (iTemp0?((fRec4[0] < 0.0f)?0.0f:(iTemp0?(fSlow12 * fRec4[0]):1.0f)):((fRec4[0] < fSlow10)?((fSlow12 * (0.0f - (fRec4[0] - fSlow11))) + 1.0f):0.0f))));
			fRec0[0] = (fTemp1 - ((fConst13 * fRec0[1]) + (fConst14 * fRec0[2])));
			fRec5[0] = (fTemp1 - ((fConst16 * fRec5[1]) + (fConst17 * fRec5[2])));
			fRec6[0] = (fTemp1 - ((fConst19 * fRec6[1]) + (fConst20 * fRec6[2])));
			fRec7[0] = (fTemp1 - ((fConst22 * fRec7[1]) + (fConst23 * fRec7[2])));
			fRec8[0] = (fTemp1 - ((fConst25 * fRec8[1]) + (fConst26 * fRec8[2])));
			fRec9[0] = (fTemp1 - ((fConst28 * fRec9[1]) + (fConst29 * fRec9[2])));
			fRec10[0] = (fTemp1 - ((fConst31 * fRec10[1]) + (fConst32 * fRec10[2])));
			fRec11[0] = (fTemp1 - ((fConst34 * fRec11[1]) + (fConst35 * fRec11[2])));
			fRec12[0] = (fTemp1 - ((fConst37 * fRec12[1]) + (fConst38 * fRec12[2])));
			fRec13[0] = (fTemp1 - ((fConst40 * fRec13[1]) + (fConst41 * fRec13[2])));
			fRec14[0] = (fTemp1 - ((fConst43 * fRec14[1]) + (fConst44 * fRec14[2])));
			fRec15[0] = (fTemp1 - ((fConst46 * fRec15[1]) + (fConst47 * fRec15[2])));
			fRec16[0] = (fTemp1 - ((fConst49 * fRec16[1]) + (fConst50 * fRec16[2])));
			fRec17[0] = (fTemp1 - ((fConst52 * fRec17[1]) + (fConst53 * fRec17[2])));
			fRec18[0] = (fTemp1 - ((fConst55 * fRec18[1]) + (fConst56 * fRec18[2])));
			fRec19[0] = (fTemp1 - ((fConst58 * fRec19[1]) + (fConst59 * fRec19[2])));
			fRec20[0] = (fTemp1 - ((fConst61 * fRec20[1]) + (fConst62 * fRec20[2])));
			fRec21[0] = (fTemp1 - ((fConst64 * fRec21[1]) + (fConst65 * fRec21[2])));
			fRec22[0] = (fTemp1 - ((fConst67 * fRec22[1]) + (fConst68 * fRec22[2])));
			fRec23[0] = (fTemp1 - ((fConst70 * fRec23[1]) + (fConst71 * fRec23[2])));
			fRec24[0] = (fTemp1 - ((fConst73 * fRec24[1]) + (fConst74 * fRec24[2])));
			fRec25[0] = (fTemp1 - ((fConst76 * fRec25[1]) + (fConst77 * fRec25[2])));
			fRec26[0] = (fTemp1 - ((fConst79 * fRec26[1]) + (fConst80 * fRec26[2])));
			fRec27[0] = (fTemp1 - ((fConst82 * fRec27[1]) + (fConst83 * fRec27[2])));
			fRec28[0] = (fTemp1 - ((fConst85 * fRec28[1]) + (fConst86 * fRec28[2])));
			fRec29[0] = (fTemp1 - ((fConst88 * fRec29[1]) + (fConst89 * fRec29[2])));
			fRec30[0] = (fTemp1 - ((fConst91 * fRec30[1]) + (fConst92 * fRec30[2])));
			fRec31[0] = (fTemp1 - ((fConst94 * fRec31[1]) + (fConst95 * fRec31[2])));
			fRec32[0] = (fTemp1 - ((fConst97 * fRec32[1]) + (fConst98 * fRec32[2])));
			fRec33[0] = (fTemp1 - ((fConst100 * fRec33[1]) + (fConst101 * fRec33[2])));
			fRec34[0] = (fTemp1 - ((fConst103 * fRec34[1]) + (fConst104 * fRec34[2])));
			fRec35[0] = (fTemp1 - ((fConst106 * fRec35[1]) + (fConst107 * fRec35[2])));
			fRec36[0] = (fTemp1 - ((fConst109 * fRec36[1]) + (fConst110 * fRec36[2])));
			fRec37[0] = (fTemp1 - ((fConst112 * fRec37[1]) + (fConst113 * fRec37[2])));
			fRec38[0] = (fTemp1 - ((fConst115 * fRec38[1]) + (fConst116 * fRec38[2])));
			fRec39[0] = (fTemp1 - ((fConst118 * fRec39[1]) + (fConst119 * fRec39[2])));
			fRec40[0] = (fTemp1 - ((fConst121 * fRec40[1]) + (fConst122 * fRec40[2])));
			fRec41[0] = (fTemp1 - ((fConst124 * fRec41[1]) + (fConst125 * fRec41[2])));
			fRec42[0] = (fTemp1 - ((fConst127 * fRec42[1]) + (fConst128 * fRec42[2])));
			fRec43[0] = (fTemp1 - ((fConst130 * fRec43[1]) + (fConst131 * fRec43[2])));
			fRec44[0] = (fTemp1 - ((fConst133 * fRec44[1]) + (fConst134 * fRec44[2])));
			fRec45[0] = (fTemp1 - ((fConst136 * fRec45[1]) + (fConst137 * fRec45[2])));
			fRec46[0] = (fTemp1 - ((fConst139 * fRec46[1]) + (fConst140 * fRec46[2])));
			fRec47[0] = (fTemp1 - ((fConst142 * fRec47[1]) + (fConst143 * fRec47[2])));
			fRec48[0] = (fTemp1 - ((fConst145 * fRec48[1]) + (fConst146 * fRec48[2])));
			fRec49[0] = (fTemp1 - ((fConst148 * fRec49[1]) + (fConst149 * fRec49[2])));
			fRec50[0] = (fTemp1 - ((fConst151 * fRec50[1]) + (fConst152 * fRec50[2])));
			fRec51[0] = (fTemp1 - ((fConst154 * fRec51[1]) + (fConst155 * fRec51[2])));
			fRec52[0] = (fTemp1 - ((fConst157 * fRec52[1]) + (fConst158 * fRec52[2])));
			fRec53[0] = (fTemp1 - ((fConst160 * fRec53[1]) + (fConst161 * fRec53[2])));
			float fTemp2 = (0.0199999996f * ((((((((((((((((((((((((((((((((((((((((((((((((((ftbl0mydspSIG0[iSlow0] * (fRec0[0] - fRec0[2])) + (ftbl0mydspSIG0[(iSlow0 + 1)] * (fRec5[0] - fRec5[2]))) + (ftbl0mydspSIG0[(iSlow0 + 2)] * (fRec6[0] - fRec6[2]))) + (ftbl0mydspSIG0[(iSlow0 + 3)] * (fRec7[0] - fRec7[2]))) + (ftbl0mydspSIG0[(iSlow0 + 4)] * (fRec8[0] - fRec8[2]))) + (ftbl0mydspSIG0[(iSlow0 + 5)] * (fRec9[0] - fRec9[2]))) + (ftbl0mydspSIG0[(iSlow0 + 6)] * (fRec10[0] - fRec10[2]))) + (ftbl0mydspSIG0[(iSlow0 + 7)] * (fRec11[0] - fRec11[2]))) + (ftbl0mydspSIG0[(iSlow0 + 8)] * (fRec12[0] - fRec12[2]))) + (ftbl0mydspSIG0[(iSlow0 + 9)] * (fRec13[0] - fRec13[2]))) + (ftbl0mydspSIG0[(iSlow0 + 10)] * (fRec14[0] - fRec14[2]))) + (ftbl0mydspSIG0[(iSlow0 + 11)] * (fRec15[0] - fRec15[2]))) + (ftbl0mydspSIG0[(iSlow0 + 12)] * (fRec16[0] - fRec16[2]))) + (ftbl0mydspSIG0[(iSlow0 + 13)] * (fRec17[0] - fRec17[2]))) + (ftbl0mydspSIG0[(iSlow0 + 14)] * (fRec18[0] - fRec18[2]))) + (ftbl0mydspSIG0[(iSlow0 + 15)] * (fRec19[0] - fRec19[2]))) + (ftbl0mydspSIG0[(iSlow0 + 16)] * (fRec20[0] - fRec20[2]))) + (ftbl0mydspSIG0[(iSlow0 + 17)] * (fRec21[0] - fRec21[2]))) + (ftbl0mydspSIG0[(iSlow0 + 18)] * (fRec22[0] - fRec22[2]))) + (ftbl0mydspSIG0[(iSlow0 + 19)] * (fRec23[0] - fRec23[2]))) + (ftbl0mydspSIG0[(iSlow0 + 20)] * (fRec24[0] - fRec24[2]))) + (ftbl0mydspSIG0[(iSlow0 + 21)] * (fRec25[0] - fRec25[2]))) + (ftbl0mydspSIG0[(iSlow0 + 22)] * (fRec26[0] - fRec26[2]))) + (ftbl0mydspSIG0[(iSlow0 + 23)] * (fRec27[0] - fRec27[2]))) + (ftbl0mydspSIG0[(iSlow0 + 24)] * (fRec28[0] - fRec28[2]))) + (ftbl0mydspSIG0[(iSlow0 + 25)] * (fRec29[0] - fRec29[2]))) + (ftbl0mydspSIG0[(iSlow0 + 26)] * (fRec30[0] - fRec30[2]))) + (ftbl0mydspSIG0[(iSlow0 + 27)] * (fRec31[0] - fRec31[2]))) + (ftbl0mydspSIG0[(iSlow0 + 28)] * (fRec32[0] - fRec32[2]))) + (ftbl0mydspSIG0[(iSlow0 + 29)] * (fRec33[0] - fRec33[2]))) + (ftbl0mydspSIG0[(iSlow0 + 30)] * (fRec34[0] - fRec34[2]))) + (ftbl0mydspSIG0[(iSlow0 + 31)] * (fRec35[0] - fRec35[2]))) + (ftbl0mydspSIG0[(iSlow0 + 32)] * (fRec36[0] - fRec36[2]))) + (ftbl0mydspSIG0[(iSlow0 + 33)] * (fRec37[0] - fRec37[2]))) + (ftbl0mydspSIG0[(iSlow0 + 34)] * (fRec38[0] - fRec38[2]))) + (ftbl0mydspSIG0[(iSlow0 + 35)] * (fRec39[0] - fRec39[2]))) + (ftbl0mydspSIG0[(iSlow0 + 36)] * (fRec40[0] - fRec40[2]))) + (ftbl0mydspSIG0[(iSlow0 + 37)] * (fRec41[0] - fRec41[2]))) + (ftbl0mydspSIG0[(iSlow0 + 38)] * (fRec42[0] - fRec42[2]))) + (ftbl0mydspSIG0[(iSlow0 + 39)] * (fRec43[0] - fRec43[2]))) + (ftbl0mydspSIG0[(iSlow0 + 40)] * (fRec44[0] - fRec44[2]))) + (ftbl0mydspSIG0[(iSlow0 + 41)] * (fRec45[0] - fRec45[2]))) + (ftbl0mydspSIG0[(iSlow0 + 42)] * (fRec46[0] - fRec46[2]))) + (ftbl0mydspSIG0[(iSlow0 + 43)] * (fRec47[0] - fRec47[2]))) + (ftbl0mydspSIG0[(iSlow0 + 44)] * (fRec48[0] - fRec48[2]))) + (ftbl0mydspSIG0[(iSlow0 + 45)] * (fRec49[0] - fRec49[2]))) + (ftbl0mydspSIG0[(iSlow0 + 46)] * (fRec50[0] - fRec50[2]))) + (ftbl0mydspSIG0[(iSlow0 + 47)] * (fRec51[0] - fRec51[2]))) + (ftbl0mydspSIG0[(iSlow0 + 48)] * (fRec52[0] - fRec52[2]))) + (ftbl0mydspSIG0[(iSlow0 + 49)] * (fRec53[0] - fRec53[2]))));
			output0[i] = FAUSTFLOAT(fTemp2);
			output1[i] = FAUSTFLOAT(fTemp2);
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
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
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
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
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
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
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
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
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			
		}
		
	}

	
};

#endif
