/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "GermanChurchBell"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: c, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


typedef struct Soundfile Soundfile;

#include "gui/CInterface.h"

#ifndef max
// define min and max (the result doesn't matter)
#define max(a,b) (a)
#define min(a,b) (b)
#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>

static float fmydspSIG0Wave0[350] = {0.761411011f,0.797802985f,0.586057007f,0.225039005f,0.926353991f,0.81387502f,0.529870987f,0.158914998f,0.662515998f,0.308409989f,0.0454785004f,0.55608201f,0.78471297f,0.213035002f,0.956227005f,0.795165002f,0.313508004f,0.158530995f,0.301586002f,0.16832f,0.281266987f,0.154237002f,0.217234999f,0.247238994f,0.522687972f,0.170303002f,0.32061401f,0.154856995f,0.414941013f,0.788363993f,0.713298976f,0.381592005f,0.707010984f,1.0f,0.0106945997f,0.359762996f,0.0746155977f,0.431124002f,0.118052997f,0.527289987f,0.255302995f,0.646854997f,0.201144993f,0.919907987f,0.359389007f,0.253493994f,0.865695f,0.0829263031f,0.222589001f,0.041573599f,0.735773981f,0.769677997f,0.381415993f,0.197542995f,0.682389021f,0.614766002f,0.249524996f,0.289882988f,0.300318986f,0.443690985f,0.275272012f,0.370218009f,0.748790026f,0.161247f,0.634352982f,0.498497993f,0.221988007f,0.350636989f,0.43681699f,0.436462998f,0.525080025f,0.842646003f,0.195324004f,0.224755004f,0.545681f,0.353778005f,0.269044012f,0.327814013f,0.448951989f,0.852304995f,0.380502999f,1.0f,0.458063006f,0.565057993f,0.354635f,0.659528971f,0.449485004f,0.802013993f,0.283446014f,0.521562994f,0.374639004f,0.652112007f,0.181042001f,0.468394011f,0.430115998f,0.157206997f,0.414995015f,0.292737007f,0.487785012f,0.477679998f,0.481445014f,0.556988001f,0.561132014f,0.378264993f,0.291462004f,0.323249996f,0.482602f,0.328247994f,0.196792006f,0.712253988f,0.389806002f,0.307751f,0.792876005f,0.199098006f,0.288837999f,0.146810994f,0.0178443994f,0.394017011f,0.588212013f,0.489226013f,0.701485991f,0.940303028f,0.213191003f,0.0778845027f,0.474462986f,0.609972f,0.163379997f,0.408376008f,0.330864012f,0.889989972f,0.0798100978f,1.0f,0.167172f,0.208727002f,0.227549002f,0.825902998f,0.531897008f,0.580946028f,0.215339005f,0.247318998f,0.268148005f,0.504087985f,0.160954997f,0.170315996f,0.230768993f,0.151190996f,0.0825031027f,0.141328007f,0.288078994f,0.499675989f,0.420354992f,0.487764001f,0.753709972f,0.492247999f,0.181364f,0.205939993f,0.524969995f,0.325641006f,0.236827001f,0.931842029f,0.472981006f,0.312162012f,0.901031971f,0.27047801f,0.167111993f,0.0709697977f,0.166004002f,0.29074499f,0.425893009f,0.403632998f,0.581772029f,0.855693996f,0.0325586982f,0.056835901f,0.241923004f,0.799310029f,0.181961998f,0.530282974f,0.415609986f,1.0f,0.0291501004f,0.831155002f,0.119755f,0.102187999f,0.132036999f,0.766030014f,0.442220986f,0.174899995f,0.142175004f,0.0140794003f,0.4375f,0.851859987f,0.196835995f,0.0907521993f,0.551672995f,0.25652799f,0.0424376987f,0.490363002f,0.108177997f,0.50327599f,0.226584002f,0.312757999f,0.824078977f,0.484120011f,0.0347337984f,0.0619428009f,0.255097002f,0.145273f,0.190358996f,0.995297015f,0.503419995f,0.217574999f,0.793974996f,0.357178986f,0.0409727991f,0.0187931005f,0.414458007f,0.158439994f,0.34623301f,0.0771673024f,0.175110996f,0.380567014f,0.497408986f,0.316163987f,0.488669008f,1.0f,0.420657009f,0.442333013f,0.247060001f,0.796406984f,0.0104146004f,0.227079004f,0.10684f,0.0289872997f,0.767570019f,0.0643121973f,0.0423097983f,0.715521991f,0.472117007f,0.392576993f,0.660432994f,0.803574979f,0.188653007f,0.0191652998f,0.87321198f,0.448718995f,0.0147128003f,0.618966997f,0.307179987f,0.345898986f,0.131393999f,0.193224996f,0.715282977f,0.405620009f,0.0406370014f,0.0503336005f,0.0544330999f,0.0452023f,0.152301997f,0.894549012f,0.443343014f,0.172070995f,0.647666991f,0.328992993f,0.0416014008f,0.0229487997f,0.551070988f,0.42354399f,0.862362027f,0.363525987f,0.769928992f,0.123452f,0.710702002f,0.394894987f,0.556638002f,1.0f,0.450924993f,0.422849f,0.0921870023f,0.413892001f,0.00995371956f,0.321146011f,0.160623997f,0.0300680995f,0.915385008f,0.475499988f,0.506950974f,0.387549013f,0.275590986f,0.468281001f,0.184775993f,0.186837003f,0.188195005f,0.0202785004f,0.697135985f,0.408861995f,0.0116935f,0.349822998f,0.202300996f,0.461378992f,0.0559022985f,0.0582570992f,0.260607988f,0.181875005f,0.0271738991f,0.0249578003f,0.685088992f,0.470384002f,0.283194005f,0.331050009f,0.138348997f,0.338068008f,0.481992006f,0.178241998f,0.0155942002f,0.0110435002f,0.783770978f,0.442707002f,0.616478026f,0.381541997f,0.510891974f,0.0459849983f,0.303119004f,0.0731908977f,0.547715008f,0.348940998f,0.149981007f,0.302157998f,0.284482002f,0.398176998f,0.00413049012f,0.180739f,0.0628390014f,0.0133459f,0.347088009f,0.576370001f,0.240764007f,0.978480995f,0.452755004f,0.529742002f,0.340470999f,0.66228199f,0.444305003f,0.0429900996f,1.0f,0.361939996f,0.0183371995f,0.626892984f,0.552850008f,0.384936005f};

typedef struct {
	
	int fmydspSIG0Wave0_idx;
	
} mydspSIG0;

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)malloc(sizeof(mydspSIG0)); }
static void deletemydspSIG0(mydspSIG0* dsp) { free(dsp); }

int getNumInputsmydspSIG0(mydspSIG0* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG0(mydspSIG0* dsp) {
	return 1;
	
}
int getInputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG0(mydspSIG0* dsp, int channel) {
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

static void instanceInitmydspSIG0(mydspSIG0* dsp, int samplingFreq) {
	dsp->fmydspSIG0Wave0_idx = 0;
	
}

static void fillmydspSIG0(mydspSIG0* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG0Wave0[dsp->fmydspSIG0Wave0_idx];
			dsp->fmydspSIG0Wave0_idx = ((1 + dsp->fmydspSIG0Wave0_idx) % 350);
			
		}
		
	}
	
};

static float ftbl0mydspSIG0[350];
static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
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
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
	m->declare(m->metaInterface, "description", "German church bell physical model.");
	m->declare(m->metaInterface, "envelopes.lib/author", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "envelopes.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "envelopes.lib/name", "Faust Envelope Library");
	m->declare(m->metaInterface, "envelopes.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "license", "MIT");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "GermanChurchBell");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
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

void classInitmydsp(int samplingFreq) {
	mydspSIG0* sig0 = newmydspSIG0();
	instanceInitmydspSIG0(sig0, samplingFreq);
	fillmydspSIG0(sig0, 350, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fEntry0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider0 = (FAUSTFLOAT)1.0f;
	dsp->fHslider1 = (FAUSTFLOAT)6500.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec3[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			dsp->fRec2[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			dsp->fRec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fVec1[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec4[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec0[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec5[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			dsp->fRec6[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			dsp->fRec7[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec8[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec9[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec10[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec11[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec12[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec13[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			dsp->fRec14[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			dsp->fRec15[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			dsp->fRec16[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			dsp->fRec17[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec18[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec19[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			dsp->fRec20[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec21[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec22[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			dsp->fRec23[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			dsp->fRec24[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			dsp->fRec25[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			dsp->fRec26[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			dsp->fRec27[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			dsp->fRec28[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			dsp->fRec29[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec30[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			dsp->fRec31[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			dsp->fRec32[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec33[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec34[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			dsp->fRec35[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec36[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec37[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec38[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			dsp->fRec39[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec40[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec41[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec42[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			dsp->fRec43[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			dsp->fRec44[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec45[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec46[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec47[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec48[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec49[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec50[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec51[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec52[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec53[l55] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = tanf((31.415926f / dsp->fConst0));
	dsp->fConst3 = (1.0f / dsp->fConst2);
	dsp->fConst4 = (1.0f / (((dsp->fConst3 + 1.41421354f) / dsp->fConst2) + 1.0f));
	dsp->fConst5 = (1.0f / mydsp_faustpower2_f(dsp->fConst2));
	dsp->fConst6 = (((dsp->fConst3 + -1.41421354f) / dsp->fConst2) + 1.0f);
	dsp->fConst7 = (2.0f * (1.0f - dsp->fConst5));
	dsp->fConst8 = (2.0f * (0.0f - dsp->fConst5));
	dsp->fConst9 = (0.00400000019f * dsp->fConst0);
	dsp->fConst10 = (0.00200000009f * dsp->fConst0);
	dsp->fConst11 = (500.0f / dsp->fConst0);
	dsp->fConst12 = powf(0.00100000005f, (1.0f / (21.8895645f * dsp->fConst0)));
	dsp->fConst13 = ((0.0f - (2.0f * dsp->fConst12)) * cosf((1501.1095f / dsp->fConst0)));
	dsp->fConst14 = mydsp_faustpower2_f(dsp->fConst12);
	dsp->fConst15 = powf(0.00100000005f, (1.0f / (21.8487759f * dsp->fConst0)));
	dsp->fConst16 = ((0.0f - (2.0f * dsp->fConst15)) * cosf((1509.44104f / dsp->fConst0)));
	dsp->fConst17 = mydsp_faustpower2_f(dsp->fConst15);
	dsp->fConst18 = powf(0.00100000005f, (1.0f / (17.0969524f * dsp->fConst0)));
	dsp->fConst19 = ((0.0f - (2.0f * dsp->fConst18)) * cosf((2552.54395f / dsp->fConst0)));
	dsp->fConst20 = mydsp_faustpower2_f(dsp->fConst18);
	dsp->fConst21 = powf(0.00100000005f, (1.0f / (17.0448818f * dsp->fConst0)));
	dsp->fConst22 = ((0.0f - (2.0f * dsp->fConst21)) * cosf((2564.88428f / dsp->fConst0)));
	dsp->fConst23 = mydsp_faustpower2_f(dsp->fConst21);
	dsp->fConst24 = powf(0.00100000005f, (1.0f / (13.2791166f * dsp->fConst0)));
	dsp->fConst25 = ((0.0f - (2.0f * dsp->fConst24)) * cosf((3525.52661f / dsp->fConst0)));
	dsp->fConst26 = mydsp_faustpower2_f(dsp->fConst24);
	dsp->fConst27 = powf(0.00100000005f, (1.0f / (13.2376995f * dsp->fConst0)));
	dsp->fConst28 = ((0.0f - (2.0f * dsp->fConst27)) * cosf((3536.94946f / dsp->fConst0)));
	dsp->fConst29 = mydsp_faustpower2_f(dsp->fConst27);
	dsp->fConst30 = powf(0.00100000005f, (1.0f / (9.3884573f * dsp->fConst0)));
	dsp->fConst31 = ((0.0f - (2.0f * dsp->fConst30)) * cosf((4710.07666f / dsp->fConst0)));
	dsp->fConst32 = mydsp_faustpower2_f(dsp->fConst30);
	dsp->fConst33 = powf(0.00100000005f, (1.0f / (9.38386536f * dsp->fConst0)));
	dsp->fConst34 = ((0.0f - (2.0f * dsp->fConst33)) * cosf((4711.63477f / dsp->fConst0)));
	dsp->fConst35 = mydsp_faustpower2_f(dsp->fConst33);
	dsp->fConst36 = powf(0.00100000005f, (1.0f / (8.81131077f * dsp->fConst0)));
	dsp->fConst37 = ((0.0f - (2.0f * dsp->fConst36)) * cosf((4909.61182f / dsp->fConst0)));
	dsp->fConst38 = mydsp_faustpower2_f(dsp->fConst36);
	dsp->fConst39 = powf(0.00100000005f, (1.0f / (8.47139359f * dsp->fConst0)));
	dsp->fConst40 = ((0.0f - (2.0f * dsp->fConst39)) * cosf((5030.8208f / dsp->fConst0)));
	dsp->fConst41 = mydsp_faustpower2_f(dsp->fConst39);
	dsp->fConst42 = powf(0.00100000005f, (1.0f / (8.45630455f * dsp->fConst0)));
	dsp->fConst43 = ((0.0f - (2.0f * dsp->fConst42)) * cosf((5036.26855f / dsp->fConst0)));
	dsp->fConst44 = mydsp_faustpower2_f(dsp->fConst42);
	dsp->fConst45 = powf(0.00100000005f, (1.0f / (7.08663797f * dsp->fConst0)));
	dsp->fConst46 = ((0.0f - (2.0f * dsp->fConst45)) * cosf((5557.38965f / dsp->fConst0)));
	dsp->fConst47 = mydsp_faustpower2_f(dsp->fConst45);
	dsp->fConst48 = powf(0.00100000005f, (1.0f / (6.21332407f * dsp->fConst0)));
	dsp->fConst49 = ((0.0f - (2.0f * dsp->fConst48)) * cosf((5922.02783f / dsp->fConst0)));
	dsp->fConst50 = mydsp_faustpower2_f(dsp->fConst48);
	dsp->fConst51 = powf(0.00100000005f, (1.0f / (6.21050549f * dsp->fConst0)));
	dsp->fConst52 = ((0.0f - (2.0f * dsp->fConst51)) * cosf((5923.25293f / dsp->fConst0)));
	dsp->fConst53 = mydsp_faustpower2_f(dsp->fConst51);
	dsp->fConst54 = powf(0.00100000005f, (1.0f / (5.9838624f * dsp->fConst0)));
	dsp->fConst55 = ((0.0f - (2.0f * dsp->fConst54)) * cosf((6022.87939f / dsp->fConst0)));
	dsp->fConst56 = mydsp_faustpower2_f(dsp->fConst54);
	dsp->fConst57 = powf(0.00100000005f, (1.0f / (5.95549202f * dsp->fConst0)));
	dsp->fConst58 = ((0.0f - (2.0f * dsp->fConst57)) * cosf((6035.5083f / dsp->fConst0)));
	dsp->fConst59 = mydsp_faustpower2_f(dsp->fConst57);
	dsp->fConst60 = powf(0.00100000005f, (1.0f / (5.19355583f * dsp->fConst0)));
	dsp->fConst61 = ((0.0f - (2.0f * dsp->fConst60)) * cosf((6389.18262f / dsp->fConst0)));
	dsp->fConst62 = mydsp_faustpower2_f(dsp->fConst60);
	dsp->fConst63 = powf(0.00100000005f, (1.0f / (5.17513943f * dsp->fConst0)));
	dsp->fConst64 = ((0.0f - (2.0f * dsp->fConst63)) * cosf((6398.10498f / dsp->fConst0)));
	dsp->fConst65 = mydsp_faustpower2_f(dsp->fConst63);
	dsp->fConst66 = powf(0.00100000005f, (1.0f / (5.12347364f * dsp->fConst0)));
	dsp->fConst67 = ((0.0f - (2.0f * dsp->fConst66)) * cosf((6423.2373f / dsp->fConst0)));
	dsp->fConst68 = mydsp_faustpower2_f(dsp->fConst66);
	dsp->fConst69 = powf(0.00100000005f, (1.0f / (3.07321405f * dsp->fConst0)));
	dsp->fConst70 = ((0.0f - (2.0f * dsp->fConst69)) * cosf((7578.77832f / dsp->fConst0)));
	dsp->fConst71 = mydsp_faustpower2_f(dsp->fConst69);
	dsp->fConst72 = powf(0.00100000005f, (1.0f / (3.06686878f * dsp->fConst0)));
	dsp->fConst73 = ((0.0f - (2.0f * dsp->fConst72)) * cosf((7582.98779f / dsp->fConst0)));
	dsp->fConst74 = mydsp_faustpower2_f(dsp->fConst72);
	dsp->fConst75 = powf(0.00100000005f, (1.0f / (3.00048304f * dsp->fConst0)));
	dsp->fConst76 = ((0.0f - (2.0f * dsp->fConst75)) * cosf((7627.34717f / dsp->fConst0)));
	dsp->fConst77 = mydsp_faustpower2_f(dsp->fConst75);
	dsp->fConst78 = powf(0.00100000005f, (1.0f / (2.91858602f * dsp->fConst0)));
	dsp->fConst79 = ((0.0f - (2.0f * dsp->fConst78)) * cosf((7682.89062f / dsp->fConst0)));
	dsp->fConst80 = mydsp_faustpower2_f(dsp->fConst78);
	dsp->fConst81 = powf(0.00100000005f, (1.0f / (2.8374126f * dsp->fConst0)));
	dsp->fConst82 = ((0.0f - (2.0f * dsp->fConst81)) * cosf((7738.87354f / dsp->fConst0)));
	dsp->fConst83 = mydsp_faustpower2_f(dsp->fConst81);
	dsp->fConst84 = powf(0.00100000005f, (1.0f / (1.91718602f * dsp->fConst0)));
	dsp->fConst85 = ((0.0f - (2.0f * dsp->fConst84)) * cosf((8454.96875f / dsp->fConst0)));
	dsp->fConst86 = mydsp_faustpower2_f(dsp->fConst84);
	dsp->fConst87 = powf(0.00100000005f, (1.0f / (1.8498652f * dsp->fConst0)));
	dsp->fConst88 = ((0.0f - (2.0f * dsp->fConst87)) * cosf((8514.84668f / dsp->fConst0)));
	dsp->fConst89 = mydsp_faustpower2_f(dsp->fConst87);
	dsp->fConst90 = powf(0.00100000005f, (1.0f / (1.84030592f * dsp->fConst0)));
	dsp->fConst91 = ((0.0f - (2.0f * dsp->fConst90)) * cosf((8523.45508f / dsp->fConst0)));
	dsp->fConst92 = mydsp_faustpower2_f(dsp->fConst90);
	dsp->fConst93 = powf(0.00100000005f, (1.0f / (1.83508539f * dsp->fConst0)));
	dsp->fConst94 = ((0.0f - (2.0f * dsp->fConst93)) * cosf((8528.16699f / dsp->fConst0)));
	dsp->fConst95 = mydsp_faustpower2_f(dsp->fConst93);
	dsp->fConst96 = powf(0.00100000005f, (1.0f / (1.62062538f * dsp->fConst0)));
	dsp->fConst97 = ((0.0f - (2.0f * dsp->fConst96)) * cosf((8729.16699f / dsp->fConst0)));
	dsp->fConst98 = mydsp_faustpower2_f(dsp->fConst96);
	dsp->fConst99 = powf(0.00100000005f, (1.0f / (1.60890257f * dsp->fConst0)));
	dsp->fConst100 = ((0.0f - (2.0f * dsp->fConst99)) * cosf((8740.60156f / dsp->fConst0)));
	dsp->fConst101 = mydsp_faustpower2_f(dsp->fConst99);
	dsp->fConst102 = powf(0.00100000005f, (1.0f / (1.42858553f * dsp->fConst0)));
	dsp->fConst103 = ((0.0f - (2.0f * dsp->fConst102)) * cosf((8923.19141f / dsp->fConst0)));
	dsp->fConst104 = mydsp_faustpower2_f(dsp->fConst102);
	dsp->fConst105 = powf(0.00100000005f, (1.0f / (1.40547824f * dsp->fConst0)));
	dsp->fConst106 = ((0.0f - (2.0f * dsp->fConst105)) * cosf((8947.57031f / dsp->fConst0)));
	dsp->fConst107 = mydsp_faustpower2_f(dsp->fConst105);
	dsp->fConst108 = powf(0.00100000005f, (1.0f / (1.40393782f * dsp->fConst0)));
	dsp->fConst109 = ((0.0f - (2.0f * dsp->fConst108)) * cosf((8949.2041f / dsp->fConst0)));
	dsp->fConst110 = mydsp_faustpower2_f(dsp->fConst108);
	dsp->fConst111 = powf(0.00100000005f, (1.0f / (1.39076793f * dsp->fConst0)));
	dsp->fConst112 = ((0.0f - (2.0f * dsp->fConst111)) * cosf((8963.21484f / dsp->fConst0)));
	dsp->fConst113 = mydsp_faustpower2_f(dsp->fConst111);
	dsp->fConst114 = powf(0.00100000005f, (1.0f / (0.646715164f * dsp->fConst0)));
	dsp->fConst115 = ((0.0f - (2.0f * dsp->fConst114)) * cosf((9941.88379f / dsp->fConst0)));
	dsp->fConst116 = mydsp_faustpower2_f(dsp->fConst114);
	dsp->fConst117 = powf(0.00100000005f, (1.0f / (0.480276495f * dsp->fConst0)));
	dsp->fConst118 = ((0.0f - (2.0f * dsp->fConst117)) * cosf((10248.3154f / dsp->fConst0)));
	dsp->fConst119 = mydsp_faustpower2_f(dsp->fConst117);
	dsp->fConst120 = powf(0.00100000005f, (1.0f / (0.458548278f * dsp->fConst0)));
	dsp->fConst121 = ((0.0f - (2.0f * dsp->fConst120)) * cosf((10292.7998f / dsp->fConst0)));
	dsp->fConst122 = mydsp_faustpower2_f(dsp->fConst120);
	dsp->fConst123 = powf(0.00100000005f, (1.0f / (0.248906523f * dsp->fConst0)));
	dsp->fConst124 = ((0.0f - (2.0f * dsp->fConst123)) * cosf((10808.8379f / dsp->fConst0)));
	dsp->fConst125 = mydsp_faustpower2_f(dsp->fConst123);
	dsp->fConst126 = powf(0.00100000005f, (1.0f / (0.235657886f * dsp->fConst0)));
	dsp->fConst127 = ((0.0f - (2.0f * dsp->fConst126)) * cosf((10849.1758f / dsp->fConst0)));
	dsp->fConst128 = mydsp_faustpower2_f(dsp->fConst126);
	dsp->fConst129 = powf(0.00100000005f, (1.0f / (0.108918622f * dsp->fConst0)));
	dsp->fConst130 = ((0.0f - (2.0f * dsp->fConst129)) * cosf((11333.5469f / dsp->fConst0)));
	dsp->fConst131 = mydsp_faustpower2_f(dsp->fConst129);
	dsp->fConst132 = powf(0.00100000005f, (1.0f / (0.0815591142f * dsp->fConst0)));
	dsp->fConst133 = ((0.0f - (2.0f * dsp->fConst132)) * cosf((11479.8818f / dsp->fConst0)));
	dsp->fConst134 = mydsp_faustpower2_f(dsp->fConst132);
	dsp->fConst135 = powf(0.00100000005f, (1.0f / (0.0790482014f * dsp->fConst0)));
	dsp->fConst136 = ((0.0f - (2.0f * dsp->fConst135)) * cosf((11494.7109f / dsp->fConst0)));
	dsp->fConst137 = mydsp_faustpower2_f(dsp->fConst135);
	dsp->fConst138 = powf(0.00100000005f, (1.0f / (0.0140934289f * dsp->fConst0)));
	dsp->fConst139 = ((0.0f - (2.0f * dsp->fConst138)) * cosf((12081.748f / dsp->fConst0)));
	dsp->fConst140 = mydsp_faustpower2_f(dsp->fConst138);
	dsp->fConst141 = powf(0.00100000005f, (1.0f / (0.0126181329f * dsp->fConst0)));
	dsp->fConst142 = ((0.0f - (2.0f * dsp->fConst141)) * cosf((12107.3213f / dsp->fConst0)));
	dsp->fConst143 = mydsp_faustpower2_f(dsp->fConst141);
	dsp->fConst144 = powf(0.00100000005f, (1.0f / (0.00826298632f * dsp->fConst0)));
	dsp->fConst145 = ((0.0f - (2.0f * dsp->fConst144)) * cosf((12195.4111f / dsp->fConst0)));
	dsp->fConst146 = mydsp_faustpower2_f(dsp->fConst144);
	dsp->fConst147 = powf(0.00100000005f, (1.0f / (0.00734149432f * dsp->fConst0)));
	dsp->fConst148 = ((0.0f - (2.0f * dsp->fConst147)) * cosf((12217.4658f / dsp->fConst0)));
	dsp->fConst149 = mydsp_faustpower2_f(dsp->fConst147);
	dsp->fConst150 = powf(0.00100000005f, (1.0f / (0.00643298635f * dsp->fConst0)));
	dsp->fConst151 = ((0.0f - (2.0f * dsp->fConst150)) * cosf((12240.9014f / dsp->fConst0)));
	dsp->fConst152 = mydsp_faustpower2_f(dsp->fConst150);
	dsp->fConst153 = powf(0.00100000005f, (1.0f / (0.00249735313f * dsp->fConst0)));
	dsp->fConst154 = ((0.0f - (2.0f * dsp->fConst153)) * cosf((12376.9951f / dsp->fConst0)));
	dsp->fConst155 = mydsp_faustpower2_f(dsp->fConst153);
	dsp->fConst156 = powf(0.00100000005f, (1.0f / (0.000497887435f * dsp->fConst0)));
	dsp->fConst157 = ((0.0f - (2.0f * dsp->fConst156)) * cosf((12517.6133f / dsp->fConst0)));
	dsp->fConst158 = mydsp_faustpower2_f(dsp->fConst156);
	dsp->fConst159 = powf(0.00100000005f, (1.0f / (9.59805584e-06f * dsp->fConst0)));
	dsp->fConst160 = ((0.0f - (2.0f * dsp->fConst159)) * cosf((12640.8262f / dsp->fConst0)));
	dsp->fConst161 = mydsp_faustpower2_f(dsp->fConst159);
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	instanceConstantsmydsp(dsp, samplingFreq);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openVerticalBox(ui_interface->uiInterface, "germanBell");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "0", "");
	ui_interface->addNumEntry(ui_interface->uiInterface, "strikePosition", &dsp->fEntry0, 0.0f, 0.0f, 4.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "strikeCutOff", &dsp->fHslider1, 6500.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "2", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "strikeSharpness", &dsp->fHslider2, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "3", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "4", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	int iSlow0 = (50 * (int)(float)dsp->fEntry0);
	float fSlow1 = tanf((dsp->fConst1 * (float)dsp->fHslider1));
	float fSlow2 = (1.0f / fSlow1);
	float fSlow3 = (((fSlow2 + 1.41421354f) / fSlow1) + 1.0f);
	float fSlow4 = ((float)dsp->fHslider0 / fSlow3);
	float fSlow5 = (1.0f / fSlow3);
	float fSlow6 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
	float fSlow7 = (((fSlow2 + -1.41421354f) / fSlow1) + 1.0f);
	float fSlow8 = (float)dsp->fButton0;
	float fSlow9 = (float)dsp->fHslider2;
	float fSlow10 = (dsp->fConst9 * fSlow9);
	float fSlow11 = (dsp->fConst10 * fSlow9);
	float fSlow12 = (dsp->fConst11 / fSlow9);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec3[0] = ((1103515245 * dsp->iRec3[1]) + 12345);
			dsp->fRec2[0] = ((4.65661287e-10f * (float)dsp->iRec3[0]) - (dsp->fConst4 * ((dsp->fConst6 * dsp->fRec2[2]) + (dsp->fConst7 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst4 * (((dsp->fConst5 * dsp->fRec2[0]) + (dsp->fConst8 * dsp->fRec2[1])) + (dsp->fConst5 * dsp->fRec2[2]))) - (fSlow5 * ((fSlow6 * dsp->fRec1[1]) + (fSlow7 * dsp->fRec1[2]))));
			dsp->fVec0[0] = fSlow8;
			dsp->fVec1[0] = fSlow9;
			dsp->fRec4[0] = ((((fSlow8 - dsp->fVec0[1]) > 0.0f) > 0)?0.0f:min(fSlow10, ((dsp->fRec4[1] + (dsp->fConst9 * (fSlow9 - dsp->fVec1[1]))) + 1.0f)));
			int iTemp0 = (dsp->fRec4[0] < fSlow11);
			float fTemp1 = (fSlow4 * ((dsp->fRec1[2] + (dsp->fRec1[0] + (2.0f * dsp->fRec1[1]))) * (iTemp0?((dsp->fRec4[0] < 0.0f)?0.0f:(iTemp0?(fSlow12 * dsp->fRec4[0]):1.0f)):((dsp->fRec4[0] < fSlow10)?((fSlow12 * (0.0f - (dsp->fRec4[0] - fSlow11))) + 1.0f):0.0f))));
			dsp->fRec0[0] = (fTemp1 - ((dsp->fConst13 * dsp->fRec0[1]) + (dsp->fConst14 * dsp->fRec0[2])));
			dsp->fRec5[0] = (fTemp1 - ((dsp->fConst16 * dsp->fRec5[1]) + (dsp->fConst17 * dsp->fRec5[2])));
			dsp->fRec6[0] = (fTemp1 - ((dsp->fConst19 * dsp->fRec6[1]) + (dsp->fConst20 * dsp->fRec6[2])));
			dsp->fRec7[0] = (fTemp1 - ((dsp->fConst22 * dsp->fRec7[1]) + (dsp->fConst23 * dsp->fRec7[2])));
			dsp->fRec8[0] = (fTemp1 - ((dsp->fConst25 * dsp->fRec8[1]) + (dsp->fConst26 * dsp->fRec8[2])));
			dsp->fRec9[0] = (fTemp1 - ((dsp->fConst28 * dsp->fRec9[1]) + (dsp->fConst29 * dsp->fRec9[2])));
			dsp->fRec10[0] = (fTemp1 - ((dsp->fConst31 * dsp->fRec10[1]) + (dsp->fConst32 * dsp->fRec10[2])));
			dsp->fRec11[0] = (fTemp1 - ((dsp->fConst34 * dsp->fRec11[1]) + (dsp->fConst35 * dsp->fRec11[2])));
			dsp->fRec12[0] = (fTemp1 - ((dsp->fConst37 * dsp->fRec12[1]) + (dsp->fConst38 * dsp->fRec12[2])));
			dsp->fRec13[0] = (fTemp1 - ((dsp->fConst40 * dsp->fRec13[1]) + (dsp->fConst41 * dsp->fRec13[2])));
			dsp->fRec14[0] = (fTemp1 - ((dsp->fConst43 * dsp->fRec14[1]) + (dsp->fConst44 * dsp->fRec14[2])));
			dsp->fRec15[0] = (fTemp1 - ((dsp->fConst46 * dsp->fRec15[1]) + (dsp->fConst47 * dsp->fRec15[2])));
			dsp->fRec16[0] = (fTemp1 - ((dsp->fConst49 * dsp->fRec16[1]) + (dsp->fConst50 * dsp->fRec16[2])));
			dsp->fRec17[0] = (fTemp1 - ((dsp->fConst52 * dsp->fRec17[1]) + (dsp->fConst53 * dsp->fRec17[2])));
			dsp->fRec18[0] = (fTemp1 - ((dsp->fConst55 * dsp->fRec18[1]) + (dsp->fConst56 * dsp->fRec18[2])));
			dsp->fRec19[0] = (fTemp1 - ((dsp->fConst58 * dsp->fRec19[1]) + (dsp->fConst59 * dsp->fRec19[2])));
			dsp->fRec20[0] = (fTemp1 - ((dsp->fConst61 * dsp->fRec20[1]) + (dsp->fConst62 * dsp->fRec20[2])));
			dsp->fRec21[0] = (fTemp1 - ((dsp->fConst64 * dsp->fRec21[1]) + (dsp->fConst65 * dsp->fRec21[2])));
			dsp->fRec22[0] = (fTemp1 - ((dsp->fConst67 * dsp->fRec22[1]) + (dsp->fConst68 * dsp->fRec22[2])));
			dsp->fRec23[0] = (fTemp1 - ((dsp->fConst70 * dsp->fRec23[1]) + (dsp->fConst71 * dsp->fRec23[2])));
			dsp->fRec24[0] = (fTemp1 - ((dsp->fConst73 * dsp->fRec24[1]) + (dsp->fConst74 * dsp->fRec24[2])));
			dsp->fRec25[0] = (fTemp1 - ((dsp->fConst76 * dsp->fRec25[1]) + (dsp->fConst77 * dsp->fRec25[2])));
			dsp->fRec26[0] = (fTemp1 - ((dsp->fConst79 * dsp->fRec26[1]) + (dsp->fConst80 * dsp->fRec26[2])));
			dsp->fRec27[0] = (fTemp1 - ((dsp->fConst82 * dsp->fRec27[1]) + (dsp->fConst83 * dsp->fRec27[2])));
			dsp->fRec28[0] = (fTemp1 - ((dsp->fConst85 * dsp->fRec28[1]) + (dsp->fConst86 * dsp->fRec28[2])));
			dsp->fRec29[0] = (fTemp1 - ((dsp->fConst88 * dsp->fRec29[1]) + (dsp->fConst89 * dsp->fRec29[2])));
			dsp->fRec30[0] = (fTemp1 - ((dsp->fConst91 * dsp->fRec30[1]) + (dsp->fConst92 * dsp->fRec30[2])));
			dsp->fRec31[0] = (fTemp1 - ((dsp->fConst94 * dsp->fRec31[1]) + (dsp->fConst95 * dsp->fRec31[2])));
			dsp->fRec32[0] = (fTemp1 - ((dsp->fConst97 * dsp->fRec32[1]) + (dsp->fConst98 * dsp->fRec32[2])));
			dsp->fRec33[0] = (fTemp1 - ((dsp->fConst100 * dsp->fRec33[1]) + (dsp->fConst101 * dsp->fRec33[2])));
			dsp->fRec34[0] = (fTemp1 - ((dsp->fConst103 * dsp->fRec34[1]) + (dsp->fConst104 * dsp->fRec34[2])));
			dsp->fRec35[0] = (fTemp1 - ((dsp->fConst106 * dsp->fRec35[1]) + (dsp->fConst107 * dsp->fRec35[2])));
			dsp->fRec36[0] = (fTemp1 - ((dsp->fConst109 * dsp->fRec36[1]) + (dsp->fConst110 * dsp->fRec36[2])));
			dsp->fRec37[0] = (fTemp1 - ((dsp->fConst112 * dsp->fRec37[1]) + (dsp->fConst113 * dsp->fRec37[2])));
			dsp->fRec38[0] = (fTemp1 - ((dsp->fConst115 * dsp->fRec38[1]) + (dsp->fConst116 * dsp->fRec38[2])));
			dsp->fRec39[0] = (fTemp1 - ((dsp->fConst118 * dsp->fRec39[1]) + (dsp->fConst119 * dsp->fRec39[2])));
			dsp->fRec40[0] = (fTemp1 - ((dsp->fConst121 * dsp->fRec40[1]) + (dsp->fConst122 * dsp->fRec40[2])));
			dsp->fRec41[0] = (fTemp1 - ((dsp->fConst124 * dsp->fRec41[1]) + (dsp->fConst125 * dsp->fRec41[2])));
			dsp->fRec42[0] = (fTemp1 - ((dsp->fConst127 * dsp->fRec42[1]) + (dsp->fConst128 * dsp->fRec42[2])));
			dsp->fRec43[0] = (fTemp1 - ((dsp->fConst130 * dsp->fRec43[1]) + (dsp->fConst131 * dsp->fRec43[2])));
			dsp->fRec44[0] = (fTemp1 - ((dsp->fConst133 * dsp->fRec44[1]) + (dsp->fConst134 * dsp->fRec44[2])));
			dsp->fRec45[0] = (fTemp1 - ((dsp->fConst136 * dsp->fRec45[1]) + (dsp->fConst137 * dsp->fRec45[2])));
			dsp->fRec46[0] = (fTemp1 - ((dsp->fConst139 * dsp->fRec46[1]) + (dsp->fConst140 * dsp->fRec46[2])));
			dsp->fRec47[0] = (fTemp1 - ((dsp->fConst142 * dsp->fRec47[1]) + (dsp->fConst143 * dsp->fRec47[2])));
			dsp->fRec48[0] = (fTemp1 - ((dsp->fConst145 * dsp->fRec48[1]) + (dsp->fConst146 * dsp->fRec48[2])));
			dsp->fRec49[0] = (fTemp1 - ((dsp->fConst148 * dsp->fRec49[1]) + (dsp->fConst149 * dsp->fRec49[2])));
			dsp->fRec50[0] = (fTemp1 - ((dsp->fConst151 * dsp->fRec50[1]) + (dsp->fConst152 * dsp->fRec50[2])));
			dsp->fRec51[0] = (fTemp1 - ((dsp->fConst154 * dsp->fRec51[1]) + (dsp->fConst155 * dsp->fRec51[2])));
			dsp->fRec52[0] = (fTemp1 - ((dsp->fConst157 * dsp->fRec52[1]) + (dsp->fConst158 * dsp->fRec52[2])));
			dsp->fRec53[0] = (fTemp1 - ((dsp->fConst160 * dsp->fRec53[1]) + (dsp->fConst161 * dsp->fRec53[2])));
			float fTemp2 = (0.0199999996f * ((((((((((((((((((((((((((((((((((((((((((((((((((ftbl0mydspSIG0[iSlow0] * (dsp->fRec0[0] - dsp->fRec0[2])) + (ftbl0mydspSIG0[(iSlow0 + 1)] * (dsp->fRec5[0] - dsp->fRec5[2]))) + (ftbl0mydspSIG0[(iSlow0 + 2)] * (dsp->fRec6[0] - dsp->fRec6[2]))) + (ftbl0mydspSIG0[(iSlow0 + 3)] * (dsp->fRec7[0] - dsp->fRec7[2]))) + (ftbl0mydspSIG0[(iSlow0 + 4)] * (dsp->fRec8[0] - dsp->fRec8[2]))) + (ftbl0mydspSIG0[(iSlow0 + 5)] * (dsp->fRec9[0] - dsp->fRec9[2]))) + (ftbl0mydspSIG0[(iSlow0 + 6)] * (dsp->fRec10[0] - dsp->fRec10[2]))) + (ftbl0mydspSIG0[(iSlow0 + 7)] * (dsp->fRec11[0] - dsp->fRec11[2]))) + (ftbl0mydspSIG0[(iSlow0 + 8)] * (dsp->fRec12[0] - dsp->fRec12[2]))) + (ftbl0mydspSIG0[(iSlow0 + 9)] * (dsp->fRec13[0] - dsp->fRec13[2]))) + (ftbl0mydspSIG0[(iSlow0 + 10)] * (dsp->fRec14[0] - dsp->fRec14[2]))) + (ftbl0mydspSIG0[(iSlow0 + 11)] * (dsp->fRec15[0] - dsp->fRec15[2]))) + (ftbl0mydspSIG0[(iSlow0 + 12)] * (dsp->fRec16[0] - dsp->fRec16[2]))) + (ftbl0mydspSIG0[(iSlow0 + 13)] * (dsp->fRec17[0] - dsp->fRec17[2]))) + (ftbl0mydspSIG0[(iSlow0 + 14)] * (dsp->fRec18[0] - dsp->fRec18[2]))) + (ftbl0mydspSIG0[(iSlow0 + 15)] * (dsp->fRec19[0] - dsp->fRec19[2]))) + (ftbl0mydspSIG0[(iSlow0 + 16)] * (dsp->fRec20[0] - dsp->fRec20[2]))) + (ftbl0mydspSIG0[(iSlow0 + 17)] * (dsp->fRec21[0] - dsp->fRec21[2]))) + (ftbl0mydspSIG0[(iSlow0 + 18)] * (dsp->fRec22[0] - dsp->fRec22[2]))) + (ftbl0mydspSIG0[(iSlow0 + 19)] * (dsp->fRec23[0] - dsp->fRec23[2]))) + (ftbl0mydspSIG0[(iSlow0 + 20)] * (dsp->fRec24[0] - dsp->fRec24[2]))) + (ftbl0mydspSIG0[(iSlow0 + 21)] * (dsp->fRec25[0] - dsp->fRec25[2]))) + (ftbl0mydspSIG0[(iSlow0 + 22)] * (dsp->fRec26[0] - dsp->fRec26[2]))) + (ftbl0mydspSIG0[(iSlow0 + 23)] * (dsp->fRec27[0] - dsp->fRec27[2]))) + (ftbl0mydspSIG0[(iSlow0 + 24)] * (dsp->fRec28[0] - dsp->fRec28[2]))) + (ftbl0mydspSIG0[(iSlow0 + 25)] * (dsp->fRec29[0] - dsp->fRec29[2]))) + (ftbl0mydspSIG0[(iSlow0 + 26)] * (dsp->fRec30[0] - dsp->fRec30[2]))) + (ftbl0mydspSIG0[(iSlow0 + 27)] * (dsp->fRec31[0] - dsp->fRec31[2]))) + (ftbl0mydspSIG0[(iSlow0 + 28)] * (dsp->fRec32[0] - dsp->fRec32[2]))) + (ftbl0mydspSIG0[(iSlow0 + 29)] * (dsp->fRec33[0] - dsp->fRec33[2]))) + (ftbl0mydspSIG0[(iSlow0 + 30)] * (dsp->fRec34[0] - dsp->fRec34[2]))) + (ftbl0mydspSIG0[(iSlow0 + 31)] * (dsp->fRec35[0] - dsp->fRec35[2]))) + (ftbl0mydspSIG0[(iSlow0 + 32)] * (dsp->fRec36[0] - dsp->fRec36[2]))) + (ftbl0mydspSIG0[(iSlow0 + 33)] * (dsp->fRec37[0] - dsp->fRec37[2]))) + (ftbl0mydspSIG0[(iSlow0 + 34)] * (dsp->fRec38[0] - dsp->fRec38[2]))) + (ftbl0mydspSIG0[(iSlow0 + 35)] * (dsp->fRec39[0] - dsp->fRec39[2]))) + (ftbl0mydspSIG0[(iSlow0 + 36)] * (dsp->fRec40[0] - dsp->fRec40[2]))) + (ftbl0mydspSIG0[(iSlow0 + 37)] * (dsp->fRec41[0] - dsp->fRec41[2]))) + (ftbl0mydspSIG0[(iSlow0 + 38)] * (dsp->fRec42[0] - dsp->fRec42[2]))) + (ftbl0mydspSIG0[(iSlow0 + 39)] * (dsp->fRec43[0] - dsp->fRec43[2]))) + (ftbl0mydspSIG0[(iSlow0 + 40)] * (dsp->fRec44[0] - dsp->fRec44[2]))) + (ftbl0mydspSIG0[(iSlow0 + 41)] * (dsp->fRec45[0] - dsp->fRec45[2]))) + (ftbl0mydspSIG0[(iSlow0 + 42)] * (dsp->fRec46[0] - dsp->fRec46[2]))) + (ftbl0mydspSIG0[(iSlow0 + 43)] * (dsp->fRec47[0] - dsp->fRec47[2]))) + (ftbl0mydspSIG0[(iSlow0 + 44)] * (dsp->fRec48[0] - dsp->fRec48[2]))) + (ftbl0mydspSIG0[(iSlow0 + 45)] * (dsp->fRec49[0] - dsp->fRec49[2]))) + (ftbl0mydspSIG0[(iSlow0 + 46)] * (dsp->fRec50[0] - dsp->fRec50[2]))) + (ftbl0mydspSIG0[(iSlow0 + 47)] * (dsp->fRec51[0] - dsp->fRec51[2]))) + (ftbl0mydspSIG0[(iSlow0 + 48)] * (dsp->fRec52[0] - dsp->fRec52[2]))) + (ftbl0mydspSIG0[(iSlow0 + 49)] * (dsp->fRec53[0] - dsp->fRec53[2]))));
			output0[i] = (FAUSTFLOAT)fTemp2;
			output1[i] = (FAUSTFLOAT)fTemp2;
			dsp->iRec3[1] = dsp->iRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[2] = dsp->fRec21[1];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec31[2] = dsp->fRec31[1];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec32[2] = dsp->fRec32[1];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec35[2] = dsp->fRec35[1];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec37[2] = dsp->fRec37[1];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec48[2] = dsp->fRec48[1];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec49[2] = dsp->fRec49[1];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec50[2] = dsp->fRec50[1];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec51[2] = dsp->fRec51[1];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec53[2] = dsp->fRec53[1];
			dsp->fRec53[1] = dsp->fRec53[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
