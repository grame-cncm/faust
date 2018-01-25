/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "GermanChurchBell"
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

static float fmydspSIG0Wave0[350] = {0.761411011f,0.797802985f,0.586057007f,0.225039005f,0.926353991f,0.81387502f,0.529870987f,0.158914998f,0.662515998f,0.308409989f,0.0454785004f,0.55608201f,0.78471297f,0.213035002f,0.956227005f,0.795165002f,0.313508004f,0.158530995f,0.301586002f,0.16832f,0.281266987f,0.154237002f,0.217234999f,0.247238994f,0.522687972f,0.170303002f,0.32061401f,0.154856995f,0.414941013f,0.788363993f,0.713298976f,0.381592005f,0.707010984f,1.0f,0.0106945997f,0.359762996f,0.0746155977f,0.431124002f,0.118052997f,0.527289987f,0.255302995f,0.646854997f,0.201144993f,0.919907987f,0.359389007f,0.253493994f,0.865695f,0.0829263031f,0.222589001f,0.041573599f,0.735773981f,0.769677997f,0.381415993f,0.197542995f,0.682389021f,0.614766002f,0.249524996f,0.289882988f,0.300318986f,0.443690985f,0.275272012f,0.370218009f,0.748790026f,0.161247f,0.634352982f,0.498497993f,0.221988007f,0.350636989f,0.43681699f,0.436462998f,0.525080025f,0.842646003f,0.195324004f,0.224755004f,0.545681f,0.353778005f,0.269044012f,0.327814013f,0.448951989f,0.852304995f,0.380502999f,1.0f,0.458063006f,0.565057993f,0.354635f,0.659528971f,0.449485004f,0.802013993f,0.283446014f,0.521562994f,0.374639004f,0.652112007f,0.181042001f,0.468394011f,0.430115998f,0.157206997f,0.414995015f,0.292737007f,0.487785012f,0.477679998f,0.481445014f,0.556988001f,0.561132014f,0.378264993f,0.291462004f,0.323249996f,0.482602f,0.328247994f,0.196792006f,0.712253988f,0.389806002f,0.307751f,0.792876005f,0.199098006f,0.288837999f,0.146810994f,0.0178443994f,0.394017011f,0.588212013f,0.489226013f,0.701485991f,0.940303028f,0.213191003f,0.0778845027f,0.474462986f,0.609972f,0.163379997f,0.408376008f,0.330864012f,0.889989972f,0.0798100978f,1.0f,0.167172f,0.208727002f,0.227549002f,0.825902998f,0.531897008f,0.580946028f,0.215339005f,0.247318998f,0.268148005f,0.504087985f,0.160954997f,0.170315996f,0.230768993f,0.151190996f,0.0825031027f,0.141328007f,0.288078994f,0.499675989f,0.420354992f,0.487764001f,0.753709972f,0.492247999f,0.181364f,0.205939993f,0.524969995f,0.325641006f,0.236827001f,0.931842029f,0.472981006f,0.312162012f,0.901031971f,0.27047801f,0.167111993f,0.0709697977f,0.166004002f,0.29074499f,0.425893009f,0.403632998f,0.581772029f,0.855693996f,0.0325586982f,0.056835901f,0.241923004f,0.799310029f,0.181961998f,0.530282974f,0.415609986f,1.0f,0.0291501004f,0.831155002f,0.119755f,0.102187999f,0.132036999f,0.766030014f,0.442220986f,0.174899995f,0.142175004f,0.0140794003f,0.4375f,0.851859987f,0.196835995f,0.0907521993f,0.551672995f,0.25652799f,0.0424376987f,0.490363002f,0.108177997f,0.50327599f,0.226584002f,0.312757999f,0.824078977f,0.484120011f,0.0347337984f,0.0619428009f,0.255097002f,0.145273f,0.190358996f,0.995297015f,0.503419995f,0.217574999f,0.793974996f,0.357178986f,0.0409727991f,0.0187931005f,0.414458007f,0.158439994f,0.34623301f,0.0771673024f,0.175110996f,0.380567014f,0.497408986f,0.316163987f,0.488669008f,1.0f,0.420657009f,0.442333013f,0.247060001f,0.796406984f,0.0104146004f,0.227079004f,0.10684f,0.0289872997f,0.767570019f,0.0643121973f,0.0423097983f,0.715521991f,0.472117007f,0.392576993f,0.660432994f,0.803574979f,0.188653007f,0.0191652998f,0.87321198f,0.448718995f,0.0147128003f,0.618966997f,0.307179987f,0.345898986f,0.131393999f,0.193224996f,0.715282977f,0.405620009f,0.0406370014f,0.0503336005f,0.0544330999f,0.0452023f,0.152301997f,0.894549012f,0.443343014f,0.172070995f,0.647666991f,0.328992993f,0.0416014008f,0.0229487997f,0.551070988f,0.42354399f,0.862362027f,0.363525987f,0.769928992f,0.123452f,0.710702002f,0.394894987f,0.556638002f,1.0f,0.450924993f,0.422849f,0.0921870023f,0.413892001f,0.00995371956f,0.321146011f,0.160623997f,0.0300680995f,0.915385008f,0.475499988f,0.506950974f,0.387549013f,0.275590986f,0.468281001f,0.184775993f,0.186837003f,0.188195005f,0.0202785004f,0.697135985f,0.408861995f,0.0116935f,0.349822998f,0.202300996f,0.461378992f,0.0559022985f,0.0582570992f,0.260607988f,0.181875005f,0.0271738991f,0.0249578003f,0.685088992f,0.470384002f,0.283194005f,0.331050009f,0.138348997f,0.338068008f,0.481992006f,0.178241998f,0.0155942002f,0.0110435002f,0.783770978f,0.442707002f,0.616478026f,0.381541997f,0.510891974f,0.0459849983f,0.303119004f,0.0731908977f,0.547715008f,0.348940998f,0.149981007f,0.302157998f,0.284482002f,0.398176998f,0.00413049012f,0.180739f,0.0628390014f,0.0133459f,0.347088009f,0.576370001f,0.240764007f,0.978480995f,0.452755004f,0.529742002f,0.340470999f,0.66228199f,0.444305003f,0.0429900996f,1.0f,0.361939996f,0.0183371995f,0.626892984f,0.552850008f,0.384936005f};

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
		fConst12 = powf(0.00100000005f, (1.0f / (21.8895645f * fConst0)));
		fConst13 = ((0.0f - (2.0f * fConst12)) * cosf((1501.1095f / fConst0)));
		fConst14 = mydsp_faustpower2_f(fConst12);
		fConst15 = powf(0.00100000005f, (1.0f / (21.8487759f * fConst0)));
		fConst16 = ((0.0f - (2.0f * fConst15)) * cosf((1509.44104f / fConst0)));
		fConst17 = mydsp_faustpower2_f(fConst15);
		fConst18 = powf(0.00100000005f, (1.0f / (17.0969524f * fConst0)));
		fConst19 = ((0.0f - (2.0f * fConst18)) * cosf((2552.54395f / fConst0)));
		fConst20 = mydsp_faustpower2_f(fConst18);
		fConst21 = powf(0.00100000005f, (1.0f / (17.0448818f * fConst0)));
		fConst22 = ((0.0f - (2.0f * fConst21)) * cosf((2564.88428f / fConst0)));
		fConst23 = mydsp_faustpower2_f(fConst21);
		fConst24 = powf(0.00100000005f, (1.0f / (13.2791166f * fConst0)));
		fConst25 = ((0.0f - (2.0f * fConst24)) * cosf((3525.52661f / fConst0)));
		fConst26 = mydsp_faustpower2_f(fConst24);
		fConst27 = powf(0.00100000005f, (1.0f / (13.2376995f * fConst0)));
		fConst28 = ((0.0f - (2.0f * fConst27)) * cosf((3536.94946f / fConst0)));
		fConst29 = mydsp_faustpower2_f(fConst27);
		fConst30 = powf(0.00100000005f, (1.0f / (9.3884573f * fConst0)));
		fConst31 = ((0.0f - (2.0f * fConst30)) * cosf((4710.07666f / fConst0)));
		fConst32 = mydsp_faustpower2_f(fConst30);
		fConst33 = powf(0.00100000005f, (1.0f / (9.38386536f * fConst0)));
		fConst34 = ((0.0f - (2.0f * fConst33)) * cosf((4711.63477f / fConst0)));
		fConst35 = mydsp_faustpower2_f(fConst33);
		fConst36 = powf(0.00100000005f, (1.0f / (8.81131077f * fConst0)));
		fConst37 = ((0.0f - (2.0f * fConst36)) * cosf((4909.61182f / fConst0)));
		fConst38 = mydsp_faustpower2_f(fConst36);
		fConst39 = powf(0.00100000005f, (1.0f / (8.47139359f * fConst0)));
		fConst40 = ((0.0f - (2.0f * fConst39)) * cosf((5030.8208f / fConst0)));
		fConst41 = mydsp_faustpower2_f(fConst39);
		fConst42 = powf(0.00100000005f, (1.0f / (8.45630455f * fConst0)));
		fConst43 = ((0.0f - (2.0f * fConst42)) * cosf((5036.26855f / fConst0)));
		fConst44 = mydsp_faustpower2_f(fConst42);
		fConst45 = powf(0.00100000005f, (1.0f / (7.08663797f * fConst0)));
		fConst46 = ((0.0f - (2.0f * fConst45)) * cosf((5557.38965f / fConst0)));
		fConst47 = mydsp_faustpower2_f(fConst45);
		fConst48 = powf(0.00100000005f, (1.0f / (6.21332407f * fConst0)));
		fConst49 = ((0.0f - (2.0f * fConst48)) * cosf((5922.02783f / fConst0)));
		fConst50 = mydsp_faustpower2_f(fConst48);
		fConst51 = powf(0.00100000005f, (1.0f / (6.21050549f * fConst0)));
		fConst52 = ((0.0f - (2.0f * fConst51)) * cosf((5923.25293f / fConst0)));
		fConst53 = mydsp_faustpower2_f(fConst51);
		fConst54 = powf(0.00100000005f, (1.0f / (5.9838624f * fConst0)));
		fConst55 = ((0.0f - (2.0f * fConst54)) * cosf((6022.87939f / fConst0)));
		fConst56 = mydsp_faustpower2_f(fConst54);
		fConst57 = powf(0.00100000005f, (1.0f / (5.95549202f * fConst0)));
		fConst58 = ((0.0f - (2.0f * fConst57)) * cosf((6035.5083f / fConst0)));
		fConst59 = mydsp_faustpower2_f(fConst57);
		fConst60 = powf(0.00100000005f, (1.0f / (5.19355583f * fConst0)));
		fConst61 = ((0.0f - (2.0f * fConst60)) * cosf((6389.18262f / fConst0)));
		fConst62 = mydsp_faustpower2_f(fConst60);
		fConst63 = powf(0.00100000005f, (1.0f / (5.17513943f * fConst0)));
		fConst64 = ((0.0f - (2.0f * fConst63)) * cosf((6398.10498f / fConst0)));
		fConst65 = mydsp_faustpower2_f(fConst63);
		fConst66 = powf(0.00100000005f, (1.0f / (5.12347364f * fConst0)));
		fConst67 = ((0.0f - (2.0f * fConst66)) * cosf((6423.2373f / fConst0)));
		fConst68 = mydsp_faustpower2_f(fConst66);
		fConst69 = powf(0.00100000005f, (1.0f / (3.07321405f * fConst0)));
		fConst70 = ((0.0f - (2.0f * fConst69)) * cosf((7578.77832f / fConst0)));
		fConst71 = mydsp_faustpower2_f(fConst69);
		fConst72 = powf(0.00100000005f, (1.0f / (3.06686878f * fConst0)));
		fConst73 = ((0.0f - (2.0f * fConst72)) * cosf((7582.98779f / fConst0)));
		fConst74 = mydsp_faustpower2_f(fConst72);
		fConst75 = powf(0.00100000005f, (1.0f / (3.00048304f * fConst0)));
		fConst76 = ((0.0f - (2.0f * fConst75)) * cosf((7627.34717f / fConst0)));
		fConst77 = mydsp_faustpower2_f(fConst75);
		fConst78 = powf(0.00100000005f, (1.0f / (2.91858602f * fConst0)));
		fConst79 = ((0.0f - (2.0f * fConst78)) * cosf((7682.89062f / fConst0)));
		fConst80 = mydsp_faustpower2_f(fConst78);
		fConst81 = powf(0.00100000005f, (1.0f / (2.8374126f * fConst0)));
		fConst82 = ((0.0f - (2.0f * fConst81)) * cosf((7738.87354f / fConst0)));
		fConst83 = mydsp_faustpower2_f(fConst81);
		fConst84 = powf(0.00100000005f, (1.0f / (1.91718602f * fConst0)));
		fConst85 = ((0.0f - (2.0f * fConst84)) * cosf((8454.96875f / fConst0)));
		fConst86 = mydsp_faustpower2_f(fConst84);
		fConst87 = powf(0.00100000005f, (1.0f / (1.8498652f * fConst0)));
		fConst88 = ((0.0f - (2.0f * fConst87)) * cosf((8514.84668f / fConst0)));
		fConst89 = mydsp_faustpower2_f(fConst87);
		fConst90 = powf(0.00100000005f, (1.0f / (1.84030592f * fConst0)));
		fConst91 = ((0.0f - (2.0f * fConst90)) * cosf((8523.45508f / fConst0)));
		fConst92 = mydsp_faustpower2_f(fConst90);
		fConst93 = powf(0.00100000005f, (1.0f / (1.83508539f * fConst0)));
		fConst94 = ((0.0f - (2.0f * fConst93)) * cosf((8528.16699f / fConst0)));
		fConst95 = mydsp_faustpower2_f(fConst93);
		fConst96 = powf(0.00100000005f, (1.0f / (1.62062538f * fConst0)));
		fConst97 = ((0.0f - (2.0f * fConst96)) * cosf((8729.16699f / fConst0)));
		fConst98 = mydsp_faustpower2_f(fConst96);
		fConst99 = powf(0.00100000005f, (1.0f / (1.60890257f * fConst0)));
		fConst100 = ((0.0f - (2.0f * fConst99)) * cosf((8740.60156f / fConst0)));
		fConst101 = mydsp_faustpower2_f(fConst99);
		fConst102 = powf(0.00100000005f, (1.0f / (1.42858553f * fConst0)));
		fConst103 = ((0.0f - (2.0f * fConst102)) * cosf((8923.19141f / fConst0)));
		fConst104 = mydsp_faustpower2_f(fConst102);
		fConst105 = powf(0.00100000005f, (1.0f / (1.40547824f * fConst0)));
		fConst106 = ((0.0f - (2.0f * fConst105)) * cosf((8947.57031f / fConst0)));
		fConst107 = mydsp_faustpower2_f(fConst105);
		fConst108 = powf(0.00100000005f, (1.0f / (1.40393782f * fConst0)));
		fConst109 = ((0.0f - (2.0f * fConst108)) * cosf((8949.2041f / fConst0)));
		fConst110 = mydsp_faustpower2_f(fConst108);
		fConst111 = powf(0.00100000005f, (1.0f / (1.39076793f * fConst0)));
		fConst112 = ((0.0f - (2.0f * fConst111)) * cosf((8963.21484f / fConst0)));
		fConst113 = mydsp_faustpower2_f(fConst111);
		fConst114 = powf(0.00100000005f, (1.0f / (0.646715164f * fConst0)));
		fConst115 = ((0.0f - (2.0f * fConst114)) * cosf((9941.88379f / fConst0)));
		fConst116 = mydsp_faustpower2_f(fConst114);
		fConst117 = powf(0.00100000005f, (1.0f / (0.480276495f * fConst0)));
		fConst118 = ((0.0f - (2.0f * fConst117)) * cosf((10248.3154f / fConst0)));
		fConst119 = mydsp_faustpower2_f(fConst117);
		fConst120 = powf(0.00100000005f, (1.0f / (0.458548278f * fConst0)));
		fConst121 = ((0.0f - (2.0f * fConst120)) * cosf((10292.7998f / fConst0)));
		fConst122 = mydsp_faustpower2_f(fConst120);
		fConst123 = powf(0.00100000005f, (1.0f / (0.248906523f * fConst0)));
		fConst124 = ((0.0f - (2.0f * fConst123)) * cosf((10808.8379f / fConst0)));
		fConst125 = mydsp_faustpower2_f(fConst123);
		fConst126 = powf(0.00100000005f, (1.0f / (0.235657886f * fConst0)));
		fConst127 = ((0.0f - (2.0f * fConst126)) * cosf((10849.1758f / fConst0)));
		fConst128 = mydsp_faustpower2_f(fConst126);
		fConst129 = powf(0.00100000005f, (1.0f / (0.108918622f * fConst0)));
		fConst130 = ((0.0f - (2.0f * fConst129)) * cosf((11333.5469f / fConst0)));
		fConst131 = mydsp_faustpower2_f(fConst129);
		fConst132 = powf(0.00100000005f, (1.0f / (0.0815591142f * fConst0)));
		fConst133 = ((0.0f - (2.0f * fConst132)) * cosf((11479.8818f / fConst0)));
		fConst134 = mydsp_faustpower2_f(fConst132);
		fConst135 = powf(0.00100000005f, (1.0f / (0.0790482014f * fConst0)));
		fConst136 = ((0.0f - (2.0f * fConst135)) * cosf((11494.7109f / fConst0)));
		fConst137 = mydsp_faustpower2_f(fConst135);
		fConst138 = powf(0.00100000005f, (1.0f / (0.0140934289f * fConst0)));
		fConst139 = ((0.0f - (2.0f * fConst138)) * cosf((12081.748f / fConst0)));
		fConst140 = mydsp_faustpower2_f(fConst138);
		fConst141 = powf(0.00100000005f, (1.0f / (0.0126181329f * fConst0)));
		fConst142 = ((0.0f - (2.0f * fConst141)) * cosf((12107.3213f / fConst0)));
		fConst143 = mydsp_faustpower2_f(fConst141);
		fConst144 = powf(0.00100000005f, (1.0f / (0.00826298632f * fConst0)));
		fConst145 = ((0.0f - (2.0f * fConst144)) * cosf((12195.4111f / fConst0)));
		fConst146 = mydsp_faustpower2_f(fConst144);
		fConst147 = powf(0.00100000005f, (1.0f / (0.00734149432f * fConst0)));
		fConst148 = ((0.0f - (2.0f * fConst147)) * cosf((12217.4658f / fConst0)));
		fConst149 = mydsp_faustpower2_f(fConst147);
		fConst150 = powf(0.00100000005f, (1.0f / (0.00643298635f * fConst0)));
		fConst151 = ((0.0f - (2.0f * fConst150)) * cosf((12240.9014f / fConst0)));
		fConst152 = mydsp_faustpower2_f(fConst150);
		fConst153 = powf(0.00100000005f, (1.0f / (0.00249735313f * fConst0)));
		fConst154 = ((0.0f - (2.0f * fConst153)) * cosf((12376.9951f / fConst0)));
		fConst155 = mydsp_faustpower2_f(fConst153);
		fConst156 = powf(0.00100000005f, (1.0f / (0.000497887435f * fConst0)));
		fConst157 = ((0.0f - (2.0f * fConst156)) * cosf((12517.6133f / fConst0)));
		fConst158 = mydsp_faustpower2_f(fConst156);
		fConst159 = powf(0.00100000005f, (1.0f / (9.59805584e-06f * fConst0)));
		fConst160 = ((0.0f - (2.0f * fConst159)) * cosf((12640.8262f / fConst0)));
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
		ui_interface->openVerticalBox("germanBell");
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
