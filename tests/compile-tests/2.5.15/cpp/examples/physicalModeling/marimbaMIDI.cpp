/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "MarimbaMIDI"
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

static float fmydspSIG0Wave0[250] = {1.0f,0.776724994f,0.625723004f,0.855223f,0.760159016f,0.69837302f,0.768010974f,0.64112699f,0.244034007f,0.707754016f,0.634012997f,0.247527003f,0.660848975f,0.450396001f,0.567782998f,0.106361002f,0.716813982f,0.663919985f,0.291207999f,0.310598999f,0.801495016f,0.635291994f,0.307435006f,0.874123991f,0.497667998f,0.487087995f,0.459114999f,0.733455002f,0.541818023f,0.441318005f,0.313919991f,0.40309f,0.685352981f,0.603139997f,0.400552005f,0.453511f,0.634386003f,0.291547f,0.131604999f,0.368506998f,0.839906991f,0.602159977f,0.288296014f,0.579670012f,0.0242493004f,0.262746006f,0.368588001f,0.890284002f,0.408962995f,0.556071997f,0.884427011f,0.832109988f,0.612015009f,0.757175982f,0.919476986f,1.0f,0.827962995f,0.89240998f,0.0357408002f,0.480789006f,0.75287199f,0.0546301007f,0.235936999f,0.362937987f,0.444471985f,0.101751f,0.703418016f,0.453135997f,0.316628993f,0.490393996f,0.982508004f,0.551621974f,0.602008998f,0.666957021f,0.776830018f,0.905662f,0.0987197012f,0.402967989f,0.829451978f,0.307644993f,0.640479982f,0.983971f,0.584204972f,0.650364995f,0.334446996f,0.583570004f,0.540190995f,0.672533989f,0.245711997f,0.687298f,0.883058012f,0.792949975f,0.600619018f,0.572682023f,0.122612f,0.388247997f,0.290657997f,0.380255014f,0.290966988f,0.567818999f,0.0737721026f,0.42098999f,0.0786577985f,0.393994987f,0.268983006f,0.260614008f,0.494085997f,0.238025993f,0.0987823978f,0.277879f,0.440562993f,0.0770211965f,0.450590998f,0.128137007f,0.0368275009f,0.128699005f,0.329605013f,0.374511987f,0.363590002f,0.272594005f,0.379052013f,0.305240989f,0.0741128996f,0.34572801f,0.299349993f,0.221284002f,0.0261390992f,0.293202013f,0.361885011f,0.114330001f,0.239004999f,0.434156001f,0.329582989f,0.219459996f,0.284175009f,0.198554993f,0.431975991f,0.302985013f,1.0f,0.146220997f,0.140700996f,0.264243007f,0.185996994f,0.426322013f,0.304780006f,0.343989998f,0.195429996f,0.386954993f,0.187600002f,0.172812f,0.0434115008f,0.303761005f,0.0694539994f,0.453943014f,0.832450986f,0.317817003f,0.940600991f,1.0f,0.180657998f,0.737921f,0.832297027f,0.402352005f,0.126785994f,0.594398022f,0.485455006f,0.324470013f,0.365101993f,0.777921975f,0.588271976f,0.401353002f,0.610734999f,0.158693001f,0.0746072009f,0.825098991f,0.925459027f,0.65377003f,0.260791987f,0.719384015f,0.559907973f,0.372590005f,0.360035002f,0.622938991f,0.210271001f,0.444595009f,0.311286002f,0.464309007f,0.557231009f,0.524079978f,0.0701055974f,0.320749015f,0.194460005f,0.727608979f,0.522062004f,0.394003987f,0.235035002f,0.395646006f,0.494796008f,0.51731801f,0.109751999f,0.69284898f,0.00632009003f,0.0207582992f,0.00306107011f,0.0637191013f,0.0816610008f,0.0351100005f,0.127813995f,0.202294007f,0.0764145032f,0.263126999f,0.400198996f,0.267277986f,0.633385003f,1.0f,0.73990202f,0.413762987f,0.418110013f,0.612715006f,0.67237401f,0.339673996f,0.211720005f,0.459645003f,0.102499999f,0.325890005f,0.148154005f,0.265442014f,0.0974304974f,0.286437988f,0.275213003f,0.109111004f,0.575088978f,0.370283008f,0.29411f,0.259826005f,0.0648718998f,0.583418012f,0.282662988f,0.182004005f,0.117421001f,0.417726994f,0.169650003f,0.24853f,0.122818999f,0.185486004f,0.0433618017f,0.373849005f,0.25276801f,0.195103005f,0.0927835032f,0.166543007f};

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
			fmydspSIG0Wave0_idx = ((1 + fmydspSIG0Wave0_idx) % 250);
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[250];
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
	
	FAUSTFLOAT fHslider0;
	int iRec2[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fRec9[2];
	int IOTA;
	float fVec0[2048];
	float fConst2;
	float fRec6[2];
	float fRec10[2];
	float fConst3;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider2;
	float fConst4;
	FAUSTFLOAT fHslider3;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	int iRec14[2];
	float fConst9;
	float fConst10;
	float fRec13[3];
	float fConst11;
	float fRec12[3];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	float fConst12;
	FAUSTFLOAT fHslider4;
	float fVec2[2];
	float fRec15[2];
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec11[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec16[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec17[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec18[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fRec19[3];
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec20[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec21[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fRec22[3];
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec23[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec24[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec25[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec26[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec27[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec28[3];
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec29[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fRec30[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec31[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec32[3];
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec33[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec34[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec35[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec36[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec37[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fRec38[3];
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec39[3];
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fRec40[3];
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fRec41[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec42[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec43[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec44[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec45[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec46[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec47[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec48[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fRec49[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec50[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fRec51[3];
	float fConst163;
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec52[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fConst170;
	float fRec53[3];
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec54[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fRec55[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec56[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec57[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fRec58[3];
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec59[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fConst198;
	float fRec60[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec61[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec62[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec63[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec64[3];
	float fVec3[2];
	float fVec4[2048];
	float fRec7[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "Simple MIDI-controllable marimba physical model.");
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
		m->declare("name", "MarimbaMIDI");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
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
		sig0->fillmydspSIG0(250, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (0.00147058826f * fConst0);
		fConst2 = (0.00882352982f * fConst0);
		fConst3 = ((0.5f * fConst0) + -1.0f);
		fConst4 = (3.14159274f / fConst0);
		fConst5 = tanf((31.415926f / fConst0));
		fConst6 = (1.0f / fConst5);
		fConst7 = (1.0f / (((fConst6 + 1.41421354f) / fConst5) + 1.0f));
		fConst8 = (1.0f / mydsp_faustpower2_f(fConst5));
		fConst9 = (((fConst6 + -1.41421354f) / fConst5) + 1.0f);
		fConst10 = (2.0f * (1.0f - fConst8));
		fConst11 = (2.0f * (0.0f - fConst8));
		fConst12 = (0.00400000019f * fConst0);
		fConst13 = (0.00200000009f * fConst0);
		fConst14 = (500.0f / fConst0);
		fConst15 = powf(0.00100000005f, (1.0f / (0.0974743068f * fConst0)));
		fConst16 = (0.0f - (2.0f * fConst15));
		fConst17 = (6.28318548f / fConst0);
		fConst18 = mydsp_faustpower2_f(fConst15);
		fConst19 = powf(0.00100000005f, (1.0f / (0.0918262452f * fConst0)));
		fConst20 = (0.0f - (2.0f * fConst19));
		fConst21 = (20.8197117f / fConst0);
		fConst22 = mydsp_faustpower2_f(fConst19);
		fConst23 = powf(0.00100000005f, (1.0f / (0.0905909166f * fConst0)));
		fConst24 = (0.0f - (2.0f * fConst23));
		fConst25 = (24.0940685f / fConst0);
		fConst26 = mydsp_faustpower2_f(fConst23);
		fConst27 = powf(0.00100000005f, (1.0f / (0.0810509697f * fConst0)));
		fConst28 = (0.0f - (2.0f * fConst27));
		fConst29 = (50.6621399f / fConst0);
		fConst30 = mydsp_faustpower2_f(fConst27);
		fConst31 = powf(0.00100000005f, (1.0f / (0.0781081766f * fConst0)));
		fConst32 = (0.0f - (2.0f * fConst31));
		fConst33 = (59.3621521f / fConst0);
		fConst34 = mydsp_faustpower2_f(fConst31);
		fConst35 = powf(0.00100000005f, (1.0f / (0.0688085929f * fConst0)));
		fConst36 = (0.0f - (2.0f * fConst35));
		fConst37 = (88.6990967f / fConst0);
		fConst38 = mydsp_faustpower2_f(fConst35);
		fConst39 = powf(0.00100000005f, (1.0f / (0.0611052401f * fConst0)));
		fConst40 = (0.0f - (2.0f * fConst39));
		fConst41 = (115.510078f / fConst0);
		fConst42 = mydsp_faustpower2_f(fConst39);
		fConst43 = powf(0.00100000005f, (1.0f / (0.0567183308f * fConst0)));
		fConst44 = (0.0f - (2.0f * fConst43));
		fConst45 = (132.010986f / fConst0);
		fConst46 = mydsp_faustpower2_f(fConst43);
		fConst47 = powf(0.00100000005f, (1.0f / (0.0488223769f * fConst0)));
		fConst48 = (0.0f - (2.0f * fConst47));
		fConst49 = (164.478088f / fConst0);
		fConst50 = mydsp_faustpower2_f(fConst47);
		fConst51 = powf(0.00100000005f, (1.0f / (0.0449043326f * fConst0)));
		fConst52 = (0.0f - (2.0f * fConst51));
		fConst53 = (182.177185f / fConst0);
		fConst54 = mydsp_faustpower2_f(fConst51);
		fConst55 = powf(0.00100000005f, (1.0f / (0.0350424498f * fConst0)));
		fConst56 = (0.0f - (2.0f * fConst55));
		fConst57 = (232.935272f / fConst0);
		fConst58 = mydsp_faustpower2_f(fConst55);
		fConst59 = powf(0.00100000005f, (1.0f / (0.0341717675f * fConst0)));
		fConst60 = (0.0f - (2.0f * fConst59));
		fConst61 = (237.946106f / fConst0);
		fConst62 = mydsp_faustpower2_f(fConst59);
		fConst63 = powf(0.00100000005f, (1.0f / (0.031866312f * fConst0)));
		fConst64 = (0.0f - (2.0f * fConst63));
		fConst65 = (251.725769f / fConst0);
		fConst66 = mydsp_faustpower2_f(fConst63);
		fConst67 = powf(0.00100000005f, (1.0f / (0.0248362795f * fConst0)));
		fConst68 = (0.0f - (2.0f * fConst67));
		fConst69 = (299.355438f / fConst0);
		fConst70 = mydsp_faustpower2_f(fConst67);
		fConst71 = powf(0.00100000005f, (1.0f / (0.0221360233f * fConst0)));
		fConst72 = (0.0f - (2.0f * fConst71));
		fConst73 = (320.561829f / fConst0);
		fConst74 = mydsp_faustpower2_f(fConst71);
		fConst75 = powf(0.00100000005f, (1.0f / (0.0210792925f * fConst0)));
		fConst76 = (0.0f - (2.0f * fConst75));
		fConst77 = (329.427399f / fConst0);
		fConst78 = mydsp_faustpower2_f(fConst75);
		fConst79 = powf(0.00100000005f, (1.0f / (0.0171158724f * fConst0)));
		fConst80 = (0.0f - (2.0f * fConst79));
		fConst81 = (366.221741f / fConst0);
		fConst82 = mydsp_faustpower2_f(fConst79);
		fConst83 = powf(0.00100000005f, (1.0f / (0.0140852043f * fConst0)));
		fConst84 = (0.0f - (2.0f * fConst83));
		fConst85 = (399.287628f / fConst0);
		fConst86 = mydsp_faustpower2_f(fConst83);
		fConst87 = powf(0.00100000005f, (1.0f / (0.0131463278f * fConst0)));
		fConst88 = (0.0f - (2.0f * fConst87));
		fConst89 = (410.686584f / fConst0);
		fConst90 = mydsp_faustpower2_f(fConst87);
		fConst91 = powf(0.00100000005f, (1.0f / (0.0123624494f * fConst0)));
		fConst92 = (0.0f - (2.0f * fConst91));
		fConst93 = (420.713928f / fConst0);
		fConst94 = mydsp_faustpower2_f(fConst91);
		fConst95 = powf(0.00100000005f, (1.0f / (0.00913601927f * fConst0)));
		fConst96 = (0.0f - (2.0f * fConst95));
		fConst97 = (468.286438f / fConst0);
		fConst98 = mydsp_faustpower2_f(fConst95);
		fConst99 = powf(0.00100000005f, (1.0f / (0.00767402584f * fConst0)));
		fConst100 = (0.0f - (2.0f * fConst99));
		fConst101 = (494.436432f / fConst0);
		fConst102 = mydsp_faustpower2_f(fConst99);
		fConst103 = powf(0.00100000005f, (1.0f / (0.00699721137f * fConst0)));
		fConst104 = (0.0f - (2.0f * fConst103));
		fConst105 = (507.916992f / fConst0);
		fConst106 = mydsp_faustpower2_f(fConst103);
		fConst107 = powf(0.00100000005f, (1.0f / (0.00462675327f * fConst0)));
		fConst108 = (0.0f - (2.0f * fConst107));
		fConst109 = (565.34845f / fConst0);
		fConst110 = mydsp_faustpower2_f(fConst107);
		fConst111 = powf(0.00100000005f, (1.0f / (0.00401024008f * fConst0)));
		fConst112 = (0.0f - (2.0f * fConst111));
		fConst113 = (584.12323f / fConst0);
		fConst114 = mydsp_faustpower2_f(fConst111);
		fConst115 = powf(0.00100000005f, (1.0f / (0.00359531236f * fConst0)));
		fConst116 = (0.0f - (2.0f * fConst115));
		fConst117 = (598.105225f / fConst0);
		fConst118 = mydsp_faustpower2_f(fConst115);
		fConst119 = powf(0.00100000005f, (1.0f / (0.00320503488f * fConst0)));
		fConst120 = (0.0f - (2.0f * fConst119));
		fConst121 = (612.489319f / fConst0);
		fConst122 = mydsp_faustpower2_f(fConst119);
		fConst123 = powf(0.00100000005f, (1.0f / (0.0015662252f * fConst0)));
		fConst124 = (0.0f - (2.0f * fConst123));
		fConst125 = (695.045959f / fConst0);
		fConst126 = mydsp_faustpower2_f(fConst123);
		fConst127 = powf(0.00100000005f, (1.0f / (0.00143769139f * fConst0)));
		fConst128 = (0.0f - (2.0f * fConst127));
		fConst129 = (704.150269f / fConst0);
		fConst130 = mydsp_faustpower2_f(fConst127);
		fConst131 = powf(0.00100000005f, (1.0f / (0.00129330496f * fConst0)));
		fConst132 = (0.0f - (2.0f * fConst131));
		fConst133 = (715.18988f / fConst0);
		fConst134 = mydsp_faustpower2_f(fConst131);
		fConst135 = powf(0.00100000005f, (1.0f / (0.000912711956f * fConst0)));
		fConst136 = (0.0f - (2.0f * fConst135));
		fConst137 = (749.935852f / fConst0);
		fConst138 = mydsp_faustpower2_f(fConst135);
		fConst139 = powf(0.00100000005f, (1.0f / (0.000537810789f * fConst0)));
		fConst140 = (0.0f - (2.0f * fConst139));
		fConst141 = (798.247253f / fConst0);
		fConst142 = mydsp_faustpower2_f(fConst139);
		fConst143 = powf(0.00100000005f, (1.0f / (0.000432563043f * fConst0)));
		fConst144 = (0.0f - (2.0f * fConst143));
		fConst145 = (816.700989f / fConst0);
		fConst146 = mydsp_faustpower2_f(fConst143);
		fConst147 = powf(0.00100000005f, (1.0f / (0.000362893392f * fConst0)));
		fConst148 = (0.0f - (2.0f * fConst147));
		fConst149 = (831.007812f / fConst0);
		fConst150 = mydsp_faustpower2_f(fConst147);
		fConst151 = powf(0.00100000005f, (1.0f / (0.000329498813f * fConst0)));
		fConst152 = (0.0f - (2.0f * fConst151));
		fConst153 = (838.660706f / fConst0);
		fConst154 = mydsp_faustpower2_f(fConst151);
		fConst155 = powf(0.00100000005f, (1.0f / (0.000124247395f * fConst0)));
		fConst156 = (0.0f - (2.0f * fConst155));
		fConst157 = (908.228149f / fConst0);
		fConst158 = mydsp_faustpower2_f(fConst155);
		fConst159 = powf(0.00100000005f, (1.0f / (7.53835775e-05f * fConst0)));
		fConst160 = (0.0f - (2.0f * fConst159));
		fConst161 = (938.946655f / fConst0);
		fConst162 = mydsp_faustpower2_f(fConst159);
		fConst163 = powf(0.00100000005f, (1.0f / (5.65755508e-05f * fConst0)));
		fConst164 = (0.0f - (2.0f * fConst163));
		fConst165 = (955.251526f / fConst0);
		fConst166 = mydsp_faustpower2_f(fConst163);
		fConst167 = powf(0.00100000005f, (1.0f / (4.96453904e-05f * fConst0)));
		fConst168 = (0.0f - (2.0f * fConst167));
		fConst169 = (962.370361f / fConst0);
		fConst170 = mydsp_faustpower2_f(fConst167);
		fConst171 = powf(0.00100000005f, (1.0f / (3.7056674e-05f * fConst0)));
		fConst172 = (0.0f - (2.0f * fConst171));
		fConst173 = (977.644775f / fConst0);
		fConst174 = mydsp_faustpower2_f(fConst171);
		fConst175 = powf(0.00100000005f, (1.0f / (2.66114275e-05f * fConst0)));
		fConst176 = (0.0f - (2.0f * fConst175));
		fConst177 = (993.893127f / fConst0);
		fConst178 = mydsp_faustpower2_f(fConst175);
		fConst179 = powf(0.00100000005f, (1.0f / (5.79888183e-06f * fConst0)));
		fConst180 = (0.0f - (2.0f * fConst179));
		fConst181 = (1056.23486f / fConst0);
		fConst182 = mydsp_faustpower2_f(fConst179);
		fConst183 = powf(0.00100000005f, (1.0f / (2.80919903e-06f * fConst0)));
		fConst184 = (0.0f - (2.0f * fConst183));
		fConst185 = (1079.84705f / fConst0);
		fConst186 = mydsp_faustpower2_f(fConst183);
		fConst187 = powf(0.00100000005f, (1.0f / (1.5867239e-06f * fConst0)));
		fConst188 = (0.0f - (2.0f * fConst187));
		fConst189 = (1096.1897f / fConst0);
		fConst190 = mydsp_faustpower2_f(fConst187);
		fConst191 = powf(0.00100000005f, (1.0f / (4.94038545e-07f * fConst0)));
		fConst192 = (0.0f - (2.0f * fConst191));
		fConst193 = (1124.29431f / fConst0);
		fConst194 = mydsp_faustpower2_f(fConst191);
		fConst195 = powf(0.00100000005f, (1.0f / (2.19791588e-07f * fConst0)));
		fConst196 = (0.0f - (2.0f * fConst195));
		fConst197 = (1140.28503f / fConst0);
		fConst198 = mydsp_faustpower2_f(fConst195);
		fConst199 = powf(0.00100000005f, (1.0f / (4.53858888e-08f * fConst0)));
		fConst200 = (0.0f - (2.0f * fConst199));
		fConst201 = (1164.89001f / fConst0);
		fConst202 = mydsp_faustpower2_f(fConst199);
		fConst203 = powf(0.00100000005f, (1.0f / (1.88244775e-09f * fConst0)));
		fConst204 = (0.0f - (2.0f * fConst203));
		fConst205 = (1196.12366f / fConst0);
		fConst206 = mydsp_faustpower2_f(fConst203);
		fConst207 = powf(0.00100000005f, (1.0f / (2.61844324e-10f * fConst0)));
		fConst208 = (0.0f - (2.0f * fConst207));
		fConst209 = (1207.56543f / fConst0);
		fConst210 = mydsp_faustpower2_f(fConst207);
		fConst211 = powf(0.00100000005f, (1.0f / (6.3867631e-15f * fConst0)));
		fConst212 = (0.0f - (2.0f * fConst211));
		fConst213 = (1228.39417f / fConst0);
		fConst214 = mydsp_faustpower2_f(fConst211);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.80000000000000004f);
		fHslider1 = FAUSTFLOAT(440.0f);
		fEntry0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(6500.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec2[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec9[l1] = 0.0f;
			
		}
		IOTA = 0;
		for (int l2 = 0; (l2 < 2048); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec6[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec10[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec14[l5] = 0;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec13[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec12[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec2[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec15[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec16[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec17[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec18[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec19[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec20[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec21[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec22[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec23[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec24[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec25[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec26[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec27[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec28[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec29[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec30[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec31[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec32[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec33[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec34[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec35[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec36[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec37[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec38[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec39[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec40[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec41[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec42[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec43[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec44[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec45[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec46[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec47[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec48[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec49[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec50[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec51[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec52[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec53[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec54[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec55[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec56[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec57[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec58[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec59[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec60[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec61[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec62[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec63[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec64[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec3[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			fVec4[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec7[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec0[l64] = 0.0f;
			
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
		ui_interface->openVerticalBox("marimba");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fHslider1, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("otherParams");
		ui_interface->declare(&fEntry0, "0", "");
		ui_interface->declare(&fEntry0, "midi", "ctrl 1");
		ui_interface->addNumEntry("strikePosition", &fEntry0, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "midi", "ctrl 1");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("strikeCutOff", &fHslider3, 6500.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("outGain", &fHslider0, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("strikeSharpness", &fHslider4, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fButton0, "3", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = (fConst1 * ((340.0f / fSlow1) + -0.0399999991f));
		float fSlow3 = (fSlow2 + -1.49999499f);
		float fSlow4 = floorf(fSlow3);
		float fSlow5 = (fSlow2 + (-1.0f - fSlow4));
		float fSlow6 = (fSlow2 + (-2.0f - fSlow4));
		float fSlow7 = (fSlow2 + (-3.0f - fSlow4));
		float fSlow8 = (fSlow2 + (-4.0f - fSlow4));
		float fSlow9 = ((((0.0f - fSlow5) * (0.0f - (0.5f * fSlow6))) * (0.0f - (0.333333343f * fSlow7))) * (0.0f - (0.25f * fSlow8)));
		int iSlow10 = int(fSlow3);
		int iSlow11 = int(min(fConst2, float(max(0, iSlow10))));
		float fSlow12 = (fSlow2 - fSlow4);
		float fSlow13 = (((0.0f - fSlow6) * (0.0f - (0.5f * fSlow7))) * (0.0f - (0.333333343f * fSlow8)));
		int iSlow14 = int(min(fConst2, float(max(0, (iSlow10 + 1)))));
		float fSlow15 = (0.5f * ((fSlow5 * (0.0f - fSlow7)) * (0.0f - (0.5f * fSlow8))));
		int iSlow16 = int(min(fConst2, float(max(0, (iSlow10 + 2)))));
		float fSlow17 = (fSlow5 * fSlow6);
		float fSlow18 = (0.166666672f * (fSlow17 * (0.0f - fSlow8)));
		int iSlow19 = int(min(fConst2, float(max(0, (iSlow10 + 3)))));
		float fSlow20 = (0.0416666679f * (fSlow17 * fSlow7));
		int iSlow21 = int(min(fConst2, float(max(0, (iSlow10 + 4)))));
		int iSlow22 = (50 * int(float(fEntry0)));
		float fSlow23 = ((fSlow1 < fConst3)?ftbl0mydspSIG0[iSlow22]:0.0f);
		float fSlow24 = tanf((fConst4 * float(fHslider3)));
		float fSlow25 = (1.0f / fSlow24);
		float fSlow26 = (((fSlow25 + 1.41421354f) / fSlow24) + 1.0f);
		float fSlow27 = (float(fHslider2) / fSlow26);
		float fSlow28 = (1.0f / fSlow26);
		float fSlow29 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow24))));
		float fSlow30 = (((fSlow25 + -1.41421354f) / fSlow24) + 1.0f);
		float fSlow31 = float(fButton0);
		float fSlow32 = float(fHslider4);
		float fSlow33 = (fConst12 * fSlow32);
		float fSlow34 = (fConst13 * fSlow32);
		float fSlow35 = (fConst14 / fSlow32);
		float fSlow36 = (fConst16 * cosf((fConst17 * fSlow1)));
		float fSlow37 = (((3.31356001f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 1)]:0.0f);
		float fSlow38 = (fConst20 * cosf((fConst21 * fSlow1)));
		float fSlow39 = (((3.83469009f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 2)]:0.0f);
		float fSlow40 = (fConst24 * cosf((fConst25 * fSlow1)));
		float fSlow41 = (((8.06313038f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 3)]:0.0f);
		float fSlow42 = (fConst28 * cosf((fConst29 * fSlow1)));
		float fSlow43 = (((9.44777966f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 4)]:0.0f);
		float fSlow44 = (fConst32 * cosf((fConst33 * fSlow1)));
		float fSlow45 = (((14.1169004f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 5)]:0.0f);
		float fSlow46 = (fConst36 * cosf((fConst37 * fSlow1)));
		float fSlow47 = (((18.3840008f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 6)]:0.0f);
		float fSlow48 = (fConst40 * cosf((fConst41 * fSlow1)));
		float fSlow49 = (((21.0102005f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 7)]:0.0f);
		float fSlow50 = (fConst44 * cosf((fConst45 * fSlow1)));
		float fSlow51 = (((26.1774998f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 8)]:0.0f);
		float fSlow52 = (fConst48 * cosf((fConst49 * fSlow1)));
		float fSlow53 = (((28.9944f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 9)]:0.0f);
		float fSlow54 = (fConst52 * cosf((fConst53 * fSlow1)));
		float fSlow55 = (((37.0727997f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 10)]:0.0f);
		float fSlow56 = (fConst56 * cosf((fConst57 * fSlow1)));
		float fSlow57 = (((37.8703003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 11)]:0.0f);
		float fSlow58 = (fConst60 * cosf((fConst61 * fSlow1)));
		float fSlow59 = (((40.0634003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 12)]:0.0f);
		float fSlow60 = (fConst64 * cosf((fConst65 * fSlow1)));
		float fSlow61 = (((47.6439018f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 13)]:0.0f);
		float fSlow62 = (fConst68 * cosf((fConst69 * fSlow1)));
		float fSlow63 = (((51.019001f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 14)]:0.0f);
		float fSlow64 = (fConst72 * cosf((fConst73 * fSlow1)));
		float fSlow65 = (((52.4300003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 15)]:0.0f);
		float fSlow66 = (fConst76 * cosf((fConst77 * fSlow1)));
		float fSlow67 = (((58.2859993f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 16)]:0.0f);
		float fSlow68 = (fConst80 * cosf((fConst81 * fSlow1)));
		float fSlow69 = (((63.5485992f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 17)]:0.0f);
		float fSlow70 = (fConst84 * cosf((fConst85 * fSlow1)));
		float fSlow71 = (((65.3628006f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 18)]:0.0f);
		float fSlow72 = (fConst88 * cosf((fConst89 * fSlow1)));
		float fSlow73 = (((66.9587021f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 19)]:0.0f);
		float fSlow74 = (fConst92 * cosf((fConst93 * fSlow1)));
		float fSlow75 = (((74.530098f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 20)]:0.0f);
		float fSlow76 = (fConst96 * cosf((fConst97 * fSlow1)));
		float fSlow77 = (((78.6920013f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 21)]:0.0f);
		float fSlow78 = (fConst100 * cosf((fConst101 * fSlow1)));
		float fSlow79 = (((80.8375015f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 22)]:0.0f);
		float fSlow80 = (fConst104 * cosf((fConst105 * fSlow1)));
		float fSlow81 = (((89.9779968f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 23)]:0.0f);
		float fSlow82 = (fConst108 * cosf((fConst109 * fSlow1)));
		float fSlow83 = (((92.9661026f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 24)]:0.0f);
		float fSlow84 = (fConst112 * cosf((fConst113 * fSlow1)));
		float fSlow85 = (((95.1913986f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 25)]:0.0f);
		float fSlow86 = (fConst116 * cosf((fConst117 * fSlow1)));
		float fSlow87 = (((97.4806976f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 26)]:0.0f);
		float fSlow88 = (fConst120 * cosf((fConst121 * fSlow1)));
		float fSlow89 = (((110.620003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 27)]:0.0f);
		float fSlow90 = (fConst124 * cosf((fConst125 * fSlow1)));
		float fSlow91 = (((112.069f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 28)]:0.0f);
		float fSlow92 = (fConst128 * cosf((fConst129 * fSlow1)));
		float fSlow93 = (((113.825996f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 29)]:0.0f);
		float fSlow94 = (fConst132 * cosf((fConst133 * fSlow1)));
		float fSlow95 = (((119.356003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 30)]:0.0f);
		float fSlow96 = (fConst136 * cosf((fConst137 * fSlow1)));
		float fSlow97 = (((127.044998f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 31)]:0.0f);
		float fSlow98 = (fConst140 * cosf((fConst141 * fSlow1)));
		float fSlow99 = (((129.981995f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 32)]:0.0f);
		float fSlow100 = (fConst144 * cosf((fConst145 * fSlow1)));
		float fSlow101 = (((132.259003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 33)]:0.0f);
		float fSlow102 = (fConst148 * cosf((fConst149 * fSlow1)));
		float fSlow103 = (((133.477005f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 34)]:0.0f);
		float fSlow104 = (fConst152 * cosf((fConst153 * fSlow1)));
		float fSlow105 = (((144.548996f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 35)]:0.0f);
		float fSlow106 = (fConst156 * cosf((fConst157 * fSlow1)));
		float fSlow107 = (((149.438004f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 36)]:0.0f);
		float fSlow108 = (fConst160 * cosf((fConst161 * fSlow1)));
		float fSlow109 = (((152.033005f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 37)]:0.0f);
		float fSlow110 = (fConst164 * cosf((fConst165 * fSlow1)));
		float fSlow111 = (((153.166f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 38)]:0.0f);
		float fSlow112 = (fConst168 * cosf((fConst169 * fSlow1)));
		float fSlow113 = (((155.597f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 39)]:0.0f);
		float fSlow114 = (fConst172 * cosf((fConst173 * fSlow1)));
		float fSlow115 = (((158.182999f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 40)]:0.0f);
		float fSlow116 = (fConst176 * cosf((fConst177 * fSlow1)));
		float fSlow117 = (((168.104996f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 41)]:0.0f);
		float fSlow118 = (fConst180 * cosf((fConst181 * fSlow1)));
		float fSlow119 = (((171.863007f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 42)]:0.0f);
		float fSlow120 = (fConst184 * cosf((fConst185 * fSlow1)));
		float fSlow121 = (((174.464005f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 43)]:0.0f);
		float fSlow122 = (fConst188 * cosf((fConst189 * fSlow1)));
		float fSlow123 = (((178.936996f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 44)]:0.0f);
		float fSlow124 = (fConst192 * cosf((fConst193 * fSlow1)));
		float fSlow125 = (((181.481995f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 45)]:0.0f);
		float fSlow126 = (fConst196 * cosf((fConst197 * fSlow1)));
		float fSlow127 = (((185.397995f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 46)]:0.0f);
		float fSlow128 = (fConst200 * cosf((fConst201 * fSlow1)));
		float fSlow129 = (((190.369003f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 47)]:0.0f);
		float fSlow130 = (fConst204 * cosf((fConst205 * fSlow1)));
		float fSlow131 = (((192.190002f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 48)]:0.0f);
		float fSlow132 = (fConst208 * cosf((fConst209 * fSlow1)));
		float fSlow133 = (((195.505005f * fSlow1) < fConst3)?ftbl0mydspSIG0[(iSlow22 + 49)]:0.0f);
		float fSlow134 = (fConst212 * cosf((fConst213 * fSlow1)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec2[0] = 0;
			fRec9[0] = ((0.949999988f * fRec9[1]) + (0.0500000007f * fRec7[1]));
			float fTemp0 = ((0.99000001f * fRec9[0]) + float(iRec2[1]));
			fVec0[(IOTA & 2047)] = fTemp0;
			fRec6[0] = ((fSlow9 * fVec0[((IOTA - iSlow11) & 2047)]) + (fSlow12 * ((((fSlow13 * fVec0[((IOTA - iSlow14) & 2047)]) + (fSlow15 * fVec0[((IOTA - iSlow16) & 2047)])) + (fSlow18 * fVec0[((IOTA - iSlow19) & 2047)])) + (fSlow20 * fVec0[((IOTA - iSlow21) & 2047)]))));
			fRec10[0] = ((0.949999988f * fRec10[1]) + (0.0500000007f * fRec6[1]));
			iRec14[0] = ((1103515245 * iRec14[1]) + 12345);
			fRec13[0] = ((4.65661287e-10f * float(iRec14[0])) - (fConst7 * ((fConst9 * fRec13[2]) + (fConst10 * fRec13[1]))));
			fRec12[0] = ((fConst7 * (((fConst8 * fRec13[0]) + (fConst11 * fRec13[1])) + (fConst8 * fRec13[2]))) - (fSlow28 * ((fSlow29 * fRec12[1]) + (fSlow30 * fRec12[2]))));
			fVec1[0] = fSlow31;
			fVec2[0] = fSlow32;
			fRec15[0] = ((((fSlow31 - fVec1[1]) > 0.0f) > 0)?0.0f:min(fSlow33, ((fRec15[1] + (fConst12 * (fSlow32 - fVec2[1]))) + 1.0f)));
			int iTemp1 = (fRec15[0] < fSlow34);
			float fTemp2 = (fSlow27 * ((fRec12[2] + (fRec12[0] + (2.0f * fRec12[1]))) * (iTemp1?((fRec15[0] < 0.0f)?0.0f:(iTemp1?(fSlow35 * fRec15[0]):1.0f)):((fRec15[0] < fSlow33)?((fSlow35 * (0.0f - (fRec15[0] - fSlow34))) + 1.0f):0.0f))));
			fRec11[0] = (fTemp2 - ((fSlow36 * fRec11[1]) + (fConst18 * fRec11[2])));
			fRec16[0] = (fTemp2 - ((fSlow38 * fRec16[1]) + (fConst22 * fRec16[2])));
			fRec17[0] = (fTemp2 - ((fSlow40 * fRec17[1]) + (fConst26 * fRec17[2])));
			fRec18[0] = (fTemp2 - ((fSlow42 * fRec18[1]) + (fConst30 * fRec18[2])));
			fRec19[0] = (fTemp2 - ((fSlow44 * fRec19[1]) + (fConst34 * fRec19[2])));
			fRec20[0] = (fTemp2 - ((fSlow46 * fRec20[1]) + (fConst38 * fRec20[2])));
			fRec21[0] = (fTemp2 - ((fSlow48 * fRec21[1]) + (fConst42 * fRec21[2])));
			fRec22[0] = (fTemp2 - ((fSlow50 * fRec22[1]) + (fConst46 * fRec22[2])));
			fRec23[0] = (fTemp2 - ((fSlow52 * fRec23[1]) + (fConst50 * fRec23[2])));
			fRec24[0] = (fTemp2 - ((fSlow54 * fRec24[1]) + (fConst54 * fRec24[2])));
			fRec25[0] = (fTemp2 - ((fSlow56 * fRec25[1]) + (fConst58 * fRec25[2])));
			fRec26[0] = (fTemp2 - ((fSlow58 * fRec26[1]) + (fConst62 * fRec26[2])));
			fRec27[0] = (fTemp2 - ((fSlow60 * fRec27[1]) + (fConst66 * fRec27[2])));
			fRec28[0] = (fTemp2 - ((fSlow62 * fRec28[1]) + (fConst70 * fRec28[2])));
			fRec29[0] = (fTemp2 - ((fSlow64 * fRec29[1]) + (fConst74 * fRec29[2])));
			fRec30[0] = (fTemp2 - ((fSlow66 * fRec30[1]) + (fConst78 * fRec30[2])));
			fRec31[0] = (fTemp2 - ((fSlow68 * fRec31[1]) + (fConst82 * fRec31[2])));
			fRec32[0] = (fTemp2 - ((fSlow70 * fRec32[1]) + (fConst86 * fRec32[2])));
			fRec33[0] = (fTemp2 - ((fSlow72 * fRec33[1]) + (fConst90 * fRec33[2])));
			fRec34[0] = (fTemp2 - ((fSlow74 * fRec34[1]) + (fConst94 * fRec34[2])));
			fRec35[0] = (fTemp2 - ((fSlow76 * fRec35[1]) + (fConst98 * fRec35[2])));
			fRec36[0] = (fTemp2 - ((fSlow78 * fRec36[1]) + (fConst102 * fRec36[2])));
			fRec37[0] = (fTemp2 - ((fSlow80 * fRec37[1]) + (fConst106 * fRec37[2])));
			fRec38[0] = (fTemp2 - ((fSlow82 * fRec38[1]) + (fConst110 * fRec38[2])));
			fRec39[0] = (fTemp2 - ((fSlow84 * fRec39[1]) + (fConst114 * fRec39[2])));
			fRec40[0] = (fTemp2 - ((fSlow86 * fRec40[1]) + (fConst118 * fRec40[2])));
			fRec41[0] = (fTemp2 - ((fSlow88 * fRec41[1]) + (fConst122 * fRec41[2])));
			fRec42[0] = (fTemp2 - ((fSlow90 * fRec42[1]) + (fConst126 * fRec42[2])));
			fRec43[0] = (fTemp2 - ((fSlow92 * fRec43[1]) + (fConst130 * fRec43[2])));
			fRec44[0] = (fTemp2 - ((fSlow94 * fRec44[1]) + (fConst134 * fRec44[2])));
			fRec45[0] = (fTemp2 - ((fSlow96 * fRec45[1]) + (fConst138 * fRec45[2])));
			fRec46[0] = (fTemp2 - ((fSlow98 * fRec46[1]) + (fConst142 * fRec46[2])));
			fRec47[0] = (fTemp2 - ((fSlow100 * fRec47[1]) + (fConst146 * fRec47[2])));
			fRec48[0] = (fTemp2 - ((fSlow102 * fRec48[1]) + (fConst150 * fRec48[2])));
			fRec49[0] = (fTemp2 - ((fSlow104 * fRec49[1]) + (fConst154 * fRec49[2])));
			fRec50[0] = (fTemp2 - ((fSlow106 * fRec50[1]) + (fConst158 * fRec50[2])));
			fRec51[0] = (fTemp2 - ((fSlow108 * fRec51[1]) + (fConst162 * fRec51[2])));
			fRec52[0] = (fTemp2 - ((fSlow110 * fRec52[1]) + (fConst166 * fRec52[2])));
			fRec53[0] = (fTemp2 - ((fSlow112 * fRec53[1]) + (fConst170 * fRec53[2])));
			fRec54[0] = (fTemp2 - ((fSlow114 * fRec54[1]) + (fConst174 * fRec54[2])));
			fRec55[0] = (fTemp2 - ((fSlow116 * fRec55[1]) + (fConst178 * fRec55[2])));
			fRec56[0] = (fTemp2 - ((fSlow118 * fRec56[1]) + (fConst182 * fRec56[2])));
			fRec57[0] = (fTemp2 - ((fSlow120 * fRec57[1]) + (fConst186 * fRec57[2])));
			fRec58[0] = (fTemp2 - ((fSlow122 * fRec58[1]) + (fConst190 * fRec58[2])));
			fRec59[0] = (fTemp2 - ((fSlow124 * fRec59[1]) + (fConst194 * fRec59[2])));
			fRec60[0] = (fTemp2 - ((fSlow126 * fRec60[1]) + (fConst198 * fRec60[2])));
			fRec61[0] = (fTemp2 - ((fSlow128 * fRec61[1]) + (fConst202 * fRec61[2])));
			fRec62[0] = (fTemp2 - ((fSlow130 * fRec62[1]) + (fConst206 * fRec62[2])));
			fRec63[0] = (fTemp2 - ((fSlow132 * fRec63[1]) + (fConst210 * fRec63[2])));
			fRec64[0] = (fTemp2 - ((fSlow134 * fRec64[1]) + (fConst214 * fRec64[2])));
			float fTemp3 = ((((((((((((((((((((((((((((((((((((((((((((((((((fSlow23 * (fRec11[0] - fRec11[2])) + (fSlow37 * (fRec16[0] - fRec16[2]))) + (fSlow39 * (fRec17[0] - fRec17[2]))) + (fSlow41 * (fRec18[0] - fRec18[2]))) + (fSlow43 * (fRec19[0] - fRec19[2]))) + (fSlow45 * (fRec20[0] - fRec20[2]))) + (fSlow47 * (fRec21[0] - fRec21[2]))) + (fSlow49 * (fRec22[0] - fRec22[2]))) + (fSlow51 * (fRec23[0] - fRec23[2]))) + (fSlow53 * (fRec24[0] - fRec24[2]))) + (fSlow55 * (fRec25[0] - fRec25[2]))) + (fSlow57 * (fRec26[0] - fRec26[2]))) + (fSlow59 * (fRec27[0] - fRec27[2]))) + (fSlow61 * (fRec28[0] - fRec28[2]))) + (fSlow63 * (fRec29[0] - fRec29[2]))) + (fSlow65 * (fRec30[0] - fRec30[2]))) + (fSlow67 * (fRec31[0] - fRec31[2]))) + (fSlow69 * (fRec32[0] - fRec32[2]))) + (fSlow71 * (fRec33[0] - fRec33[2]))) + (fSlow73 * (fRec34[0] - fRec34[2]))) + (fSlow75 * (fRec35[0] - fRec35[2]))) + (fSlow77 * (fRec36[0] - fRec36[2]))) + (fSlow79 * (fRec37[0] - fRec37[2]))) + (fSlow81 * (fRec38[0] - fRec38[2]))) + (fSlow83 * (fRec39[0] - fRec39[2]))) + (fSlow85 * (fRec40[0] - fRec40[2]))) + (fSlow87 * (fRec41[0] - fRec41[2]))) + (fSlow89 * (fRec42[0] - fRec42[2]))) + (fSlow91 * (fRec43[0] - fRec43[2]))) + (fSlow93 * (fRec44[0] - fRec44[2]))) + (fSlow95 * (fRec45[0] - fRec45[2]))) + (fSlow97 * (fRec46[0] - fRec46[2]))) + (fSlow99 * (fRec47[0] - fRec47[2]))) + (fSlow101 * (fRec48[0] - fRec48[2]))) + (fSlow103 * (fRec49[0] - fRec49[2]))) + (fSlow105 * (fRec50[0] - fRec50[2]))) + (fSlow107 * (fRec51[0] - fRec51[2]))) + (fSlow109 * (fRec52[0] - fRec52[2]))) + (fSlow111 * (fRec53[0] - fRec53[2]))) + (fSlow113 * (fRec54[0] - fRec54[2]))) + (fSlow115 * (fRec55[0] - fRec55[2]))) + (fSlow117 * (fRec56[0] - fRec56[2]))) + (fSlow119 * (fRec57[0] - fRec57[2]))) + (fSlow121 * (fRec58[0] - fRec58[2]))) + (fSlow123 * (fRec59[0] - fRec59[2]))) + (fSlow125 * (fRec60[0] - fRec60[2]))) + (fSlow127 * (fRec61[0] - fRec61[2]))) + (fSlow129 * (fRec62[0] - fRec62[2]))) + (fSlow131 * (fRec63[0] - fRec63[2]))) + (fSlow133 * (fRec64[0] - fRec64[2])));
			fVec3[0] = fTemp3;
			float fTemp4 = ((0.99000001f * fRec10[0]) + (0.0199999996f * fVec3[1]));
			fVec4[(IOTA & 2047)] = fTemp4;
			fRec7[0] = ((fSlow9 * fVec4[((IOTA - iSlow11) & 2047)]) + (fSlow12 * ((((fSlow13 * fVec4[((IOTA - iSlow14) & 2047)]) + (fSlow15 * fVec4[((IOTA - iSlow16) & 2047)])) + (fSlow18 * fVec4[((IOTA - iSlow19) & 2047)])) + (fSlow20 * fVec4[((IOTA - iSlow21) & 2047)]))));
			int iRec8 = 0;
			float fRec3 = fRec6[0];
			float fRec4 = fRec7[0];
			float fRec5 = (fRec7[0] + float(iRec8));
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp5 = (fSlow0 * fRec1);
			output0[i] = FAUSTFLOAT(fTemp5);
			output1[i] = FAUSTFLOAT(fTemp5);
			iRec2[1] = iRec2[0];
			fRec9[1] = fRec9[0];
			IOTA = (IOTA + 1);
			fRec6[1] = fRec6[0];
			fRec10[1] = fRec10[0];
			iRec14[1] = iRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec15[1] = fRec15[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
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
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fVec3[1] = fVec3[0];
			fRec7[1] = fRec7[0];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};

#endif
