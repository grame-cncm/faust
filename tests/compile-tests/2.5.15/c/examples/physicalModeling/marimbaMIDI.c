/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "MarimbaMIDI"
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

static float fmydspSIG0Wave0[250] = {1.0f,0.776724994f,0.625723004f,0.855223f,0.760159016f,0.69837302f,0.768010974f,0.64112699f,0.244034007f,0.707754016f,0.634012997f,0.247527003f,0.660848975f,0.450396001f,0.567782998f,0.106361002f,0.716813982f,0.663919985f,0.291207999f,0.310598999f,0.801495016f,0.635291994f,0.307435006f,0.874123991f,0.497667998f,0.487087995f,0.459114999f,0.733455002f,0.541818023f,0.441318005f,0.313919991f,0.40309f,0.685352981f,0.603139997f,0.400552005f,0.453511f,0.634386003f,0.291547f,0.131604999f,0.368506998f,0.839906991f,0.602159977f,0.288296014f,0.579670012f,0.0242493004f,0.262746006f,0.368588001f,0.890284002f,0.408962995f,0.556071997f,0.884427011f,0.832109988f,0.612015009f,0.757175982f,0.919476986f,1.0f,0.827962995f,0.89240998f,0.0357408002f,0.480789006f,0.75287199f,0.0546301007f,0.235936999f,0.362937987f,0.444471985f,0.101751f,0.703418016f,0.453135997f,0.316628993f,0.490393996f,0.982508004f,0.551621974f,0.602008998f,0.666957021f,0.776830018f,0.905662f,0.0987197012f,0.402967989f,0.829451978f,0.307644993f,0.640479982f,0.983971f,0.584204972f,0.650364995f,0.334446996f,0.583570004f,0.540190995f,0.672533989f,0.245711997f,0.687298f,0.883058012f,0.792949975f,0.600619018f,0.572682023f,0.122612f,0.388247997f,0.290657997f,0.380255014f,0.290966988f,0.567818999f,0.0737721026f,0.42098999f,0.0786577985f,0.393994987f,0.268983006f,0.260614008f,0.494085997f,0.238025993f,0.0987823978f,0.277879f,0.440562993f,0.0770211965f,0.450590998f,0.128137007f,0.0368275009f,0.128699005f,0.329605013f,0.374511987f,0.363590002f,0.272594005f,0.379052013f,0.305240989f,0.0741128996f,0.34572801f,0.299349993f,0.221284002f,0.0261390992f,0.293202013f,0.361885011f,0.114330001f,0.239004999f,0.434156001f,0.329582989f,0.219459996f,0.284175009f,0.198554993f,0.431975991f,0.302985013f,1.0f,0.146220997f,0.140700996f,0.264243007f,0.185996994f,0.426322013f,0.304780006f,0.343989998f,0.195429996f,0.386954993f,0.187600002f,0.172812f,0.0434115008f,0.303761005f,0.0694539994f,0.453943014f,0.832450986f,0.317817003f,0.940600991f,1.0f,0.180657998f,0.737921f,0.832297027f,0.402352005f,0.126785994f,0.594398022f,0.485455006f,0.324470013f,0.365101993f,0.777921975f,0.588271976f,0.401353002f,0.610734999f,0.158693001f,0.0746072009f,0.825098991f,0.925459027f,0.65377003f,0.260791987f,0.719384015f,0.559907973f,0.372590005f,0.360035002f,0.622938991f,0.210271001f,0.444595009f,0.311286002f,0.464309007f,0.557231009f,0.524079978f,0.0701055974f,0.320749015f,0.194460005f,0.727608979f,0.522062004f,0.394003987f,0.235035002f,0.395646006f,0.494796008f,0.51731801f,0.109751999f,0.69284898f,0.00632009003f,0.0207582992f,0.00306107011f,0.0637191013f,0.0816610008f,0.0351100005f,0.127813995f,0.202294007f,0.0764145032f,0.263126999f,0.400198996f,0.267277986f,0.633385003f,1.0f,0.73990202f,0.413762987f,0.418110013f,0.612715006f,0.67237401f,0.339673996f,0.211720005f,0.459645003f,0.102499999f,0.325890005f,0.148154005f,0.265442014f,0.0974304974f,0.286437988f,0.275213003f,0.109111004f,0.575088978f,0.370283008f,0.29411f,0.259826005f,0.0648718998f,0.583418012f,0.282662988f,0.182004005f,0.117421001f,0.417726994f,0.169650003f,0.24853f,0.122818999f,0.185486004f,0.0433618017f,0.373849005f,0.25276801f,0.195103005f,0.0927835032f,0.166543007f};

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
			dsp->fmydspSIG0Wave0_idx = ((1 + dsp->fmydspSIG0Wave0_idx) % 250);
			
		}
		
	}
	
};

static float ftbl0mydspSIG0[250];
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
	float fConst3;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider2;
	float fConst4;
	FAUSTFLOAT fHslider3;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	int iRec13[2];
	float fConst9;
	float fConst10;
	float fRec12[3];
	float fConst11;
	float fRec11[3];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	float fConst12;
	FAUSTFLOAT fHslider4;
	float fVec2[2];
	float fRec14[2];
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec10[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec15[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec16[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec17[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fRec18[3];
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec19[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec20[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fRec21[3];
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec22[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec23[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec24[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec25[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec26[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec27[3];
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec28[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fRec29[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec30[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec31[3];
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec32[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec33[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec34[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec35[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec36[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fRec37[3];
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec38[3];
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fRec39[3];
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fRec40[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec41[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec42[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec43[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec44[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec45[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec46[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec47[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fRec48[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec49[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fRec50[3];
	float fConst163;
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec51[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fConst170;
	float fRec52[3];
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec53[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fRec54[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec55[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec56[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fRec57[3];
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec58[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fConst198;
	float fRec59[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec60[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec61[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec62[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec63[3];
	float fVec3[2];
	float fRec64[2];
	float fVec4[2048];
	float fRec7[2];
	float fRec0[2];
	
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
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Simple MIDI-controllable marimba physical model.");
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
	m->declare(m->metaInterface, "name", "MarimbaMIDI");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
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
	fillmydspSIG0(sig0, 250, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.80000000000000004f;
	dsp->fHslider1 = (FAUSTFLOAT)440.0f;
	dsp->fEntry0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)1.0f;
	dsp->fHslider3 = (FAUSTFLOAT)6500.0f;
	dsp->fButton0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iRec2[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec9[l1] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2048); l2 = (l2 + 1)) {
			dsp->fVec0[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec6[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->iRec13[l4] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec12[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec11[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec1[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec2[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec14[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			dsp->fRec10[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec15[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			dsp->fRec16[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			dsp->fRec17[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec18[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			dsp->fRec19[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			dsp->fRec20[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			dsp->fRec21[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			dsp->fRec22[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			dsp->fRec23[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			dsp->fRec24[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec25[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			dsp->fRec26[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			dsp->fRec27[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			dsp->fRec28[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			dsp->fRec29[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			dsp->fRec30[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			dsp->fRec31[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			dsp->fRec32[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			dsp->fRec33[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			dsp->fRec34[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			dsp->fRec35[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec36[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			dsp->fRec37[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			dsp->fRec38[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec39[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec40[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			dsp->fRec41[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec42[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec43[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec44[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			dsp->fRec45[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec46[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec47[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec48[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			dsp->fRec49[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			dsp->fRec50[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec51[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec52[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec53[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec54[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec55[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec56[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec57[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec58[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec59[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec60[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			dsp->fRec61[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec62[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			dsp->fRec63[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			dsp->fVec3[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec64[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			dsp->fVec4[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			dsp->fRec7[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			dsp->fRec0[l64] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (0.00147058826f * dsp->fConst0);
	dsp->fConst2 = (0.00882352982f * dsp->fConst0);
	dsp->fConst3 = ((0.5f * dsp->fConst0) + -1.0f);
	dsp->fConst4 = (3.14159274f / dsp->fConst0);
	dsp->fConst5 = tanf((31.415926f / dsp->fConst0));
	dsp->fConst6 = (1.0f / dsp->fConst5);
	dsp->fConst7 = (1.0f / (((dsp->fConst6 + 1.41421354f) / dsp->fConst5) + 1.0f));
	dsp->fConst8 = (1.0f / mydsp_faustpower2_f(dsp->fConst5));
	dsp->fConst9 = (((dsp->fConst6 + -1.41421354f) / dsp->fConst5) + 1.0f);
	dsp->fConst10 = (2.0f * (1.0f - dsp->fConst8));
	dsp->fConst11 = (2.0f * (0.0f - dsp->fConst8));
	dsp->fConst12 = (0.00400000019f * dsp->fConst0);
	dsp->fConst13 = (0.00200000009f * dsp->fConst0);
	dsp->fConst14 = (500.0f / dsp->fConst0);
	dsp->fConst15 = powf(0.00100000005f, (1.0f / (4.94038545e-07f * dsp->fConst0)));
	dsp->fConst16 = mydsp_faustpower2_f(dsp->fConst15);
	dsp->fConst17 = (0.0f - (2.0f * dsp->fConst15));
	dsp->fConst18 = (1124.29431f / dsp->fConst0);
	dsp->fConst19 = powf(0.00100000005f, (1.0f / (2.19791588e-07f * dsp->fConst0)));
	dsp->fConst20 = (0.0f - (2.0f * dsp->fConst19));
	dsp->fConst21 = (1140.28503f / dsp->fConst0);
	dsp->fConst22 = mydsp_faustpower2_f(dsp->fConst19);
	dsp->fConst23 = powf(0.00100000005f, (1.0f / (4.53858888e-08f * dsp->fConst0)));
	dsp->fConst24 = (0.0f - (2.0f * dsp->fConst23));
	dsp->fConst25 = (1164.89001f / dsp->fConst0);
	dsp->fConst26 = mydsp_faustpower2_f(dsp->fConst23);
	dsp->fConst27 = powf(0.00100000005f, (1.0f / (1.88244775e-09f * dsp->fConst0)));
	dsp->fConst28 = (0.0f - (2.0f * dsp->fConst27));
	dsp->fConst29 = (1196.12366f / dsp->fConst0);
	dsp->fConst30 = mydsp_faustpower2_f(dsp->fConst27);
	dsp->fConst31 = powf(0.00100000005f, (1.0f / (2.61844324e-10f * dsp->fConst0)));
	dsp->fConst32 = (0.0f - (2.0f * dsp->fConst31));
	dsp->fConst33 = (1207.56543f / dsp->fConst0);
	dsp->fConst34 = mydsp_faustpower2_f(dsp->fConst31);
	dsp->fConst35 = powf(0.00100000005f, (1.0f / (6.3867631e-15f * dsp->fConst0)));
	dsp->fConst36 = (0.0f - (2.0f * dsp->fConst35));
	dsp->fConst37 = (1228.39417f / dsp->fConst0);
	dsp->fConst38 = mydsp_faustpower2_f(dsp->fConst35);
	dsp->fConst39 = powf(0.00100000005f, (1.0f / (0.0974743068f * dsp->fConst0)));
	dsp->fConst40 = (0.0f - (2.0f * dsp->fConst39));
	dsp->fConst41 = (6.28318548f / dsp->fConst0);
	dsp->fConst42 = mydsp_faustpower2_f(dsp->fConst39);
	dsp->fConst43 = powf(0.00100000005f, (1.0f / (0.0918262452f * dsp->fConst0)));
	dsp->fConst44 = (0.0f - (2.0f * dsp->fConst43));
	dsp->fConst45 = (20.8197117f / dsp->fConst0);
	dsp->fConst46 = mydsp_faustpower2_f(dsp->fConst43);
	dsp->fConst47 = powf(0.00100000005f, (1.0f / (0.0905909166f * dsp->fConst0)));
	dsp->fConst48 = (0.0f - (2.0f * dsp->fConst47));
	dsp->fConst49 = (24.0940685f / dsp->fConst0);
	dsp->fConst50 = mydsp_faustpower2_f(dsp->fConst47);
	dsp->fConst51 = powf(0.00100000005f, (1.0f / (0.0810509697f * dsp->fConst0)));
	dsp->fConst52 = (0.0f - (2.0f * dsp->fConst51));
	dsp->fConst53 = (50.6621399f / dsp->fConst0);
	dsp->fConst54 = mydsp_faustpower2_f(dsp->fConst51);
	dsp->fConst55 = powf(0.00100000005f, (1.0f / (0.0781081766f * dsp->fConst0)));
	dsp->fConst56 = (0.0f - (2.0f * dsp->fConst55));
	dsp->fConst57 = (59.3621521f / dsp->fConst0);
	dsp->fConst58 = mydsp_faustpower2_f(dsp->fConst55);
	dsp->fConst59 = powf(0.00100000005f, (1.0f / (0.0688085929f * dsp->fConst0)));
	dsp->fConst60 = (0.0f - (2.0f * dsp->fConst59));
	dsp->fConst61 = (88.6990967f / dsp->fConst0);
	dsp->fConst62 = mydsp_faustpower2_f(dsp->fConst59);
	dsp->fConst63 = powf(0.00100000005f, (1.0f / (0.0611052401f * dsp->fConst0)));
	dsp->fConst64 = (0.0f - (2.0f * dsp->fConst63));
	dsp->fConst65 = (115.510078f / dsp->fConst0);
	dsp->fConst66 = mydsp_faustpower2_f(dsp->fConst63);
	dsp->fConst67 = powf(0.00100000005f, (1.0f / (0.0567183308f * dsp->fConst0)));
	dsp->fConst68 = (0.0f - (2.0f * dsp->fConst67));
	dsp->fConst69 = (132.010986f / dsp->fConst0);
	dsp->fConst70 = mydsp_faustpower2_f(dsp->fConst67);
	dsp->fConst71 = powf(0.00100000005f, (1.0f / (0.0488223769f * dsp->fConst0)));
	dsp->fConst72 = (0.0f - (2.0f * dsp->fConst71));
	dsp->fConst73 = (164.478088f / dsp->fConst0);
	dsp->fConst74 = mydsp_faustpower2_f(dsp->fConst71);
	dsp->fConst75 = powf(0.00100000005f, (1.0f / (0.0449043326f * dsp->fConst0)));
	dsp->fConst76 = (0.0f - (2.0f * dsp->fConst75));
	dsp->fConst77 = (182.177185f / dsp->fConst0);
	dsp->fConst78 = mydsp_faustpower2_f(dsp->fConst75);
	dsp->fConst79 = powf(0.00100000005f, (1.0f / (0.0350424498f * dsp->fConst0)));
	dsp->fConst80 = (0.0f - (2.0f * dsp->fConst79));
	dsp->fConst81 = (232.935272f / dsp->fConst0);
	dsp->fConst82 = mydsp_faustpower2_f(dsp->fConst79);
	dsp->fConst83 = powf(0.00100000005f, (1.0f / (0.0341717675f * dsp->fConst0)));
	dsp->fConst84 = (0.0f - (2.0f * dsp->fConst83));
	dsp->fConst85 = (237.946106f / dsp->fConst0);
	dsp->fConst86 = mydsp_faustpower2_f(dsp->fConst83);
	dsp->fConst87 = powf(0.00100000005f, (1.0f / (0.031866312f * dsp->fConst0)));
	dsp->fConst88 = (0.0f - (2.0f * dsp->fConst87));
	dsp->fConst89 = (251.725769f / dsp->fConst0);
	dsp->fConst90 = mydsp_faustpower2_f(dsp->fConst87);
	dsp->fConst91 = powf(0.00100000005f, (1.0f / (0.0248362795f * dsp->fConst0)));
	dsp->fConst92 = (0.0f - (2.0f * dsp->fConst91));
	dsp->fConst93 = (299.355438f / dsp->fConst0);
	dsp->fConst94 = mydsp_faustpower2_f(dsp->fConst91);
	dsp->fConst95 = powf(0.00100000005f, (1.0f / (0.0221360233f * dsp->fConst0)));
	dsp->fConst96 = (0.0f - (2.0f * dsp->fConst95));
	dsp->fConst97 = (320.561829f / dsp->fConst0);
	dsp->fConst98 = mydsp_faustpower2_f(dsp->fConst95);
	dsp->fConst99 = powf(0.00100000005f, (1.0f / (0.0210792925f * dsp->fConst0)));
	dsp->fConst100 = (0.0f - (2.0f * dsp->fConst99));
	dsp->fConst101 = (329.427399f / dsp->fConst0);
	dsp->fConst102 = mydsp_faustpower2_f(dsp->fConst99);
	dsp->fConst103 = powf(0.00100000005f, (1.0f / (0.0171158724f * dsp->fConst0)));
	dsp->fConst104 = (0.0f - (2.0f * dsp->fConst103));
	dsp->fConst105 = (366.221741f / dsp->fConst0);
	dsp->fConst106 = mydsp_faustpower2_f(dsp->fConst103);
	dsp->fConst107 = powf(0.00100000005f, (1.0f / (0.0140852043f * dsp->fConst0)));
	dsp->fConst108 = (0.0f - (2.0f * dsp->fConst107));
	dsp->fConst109 = (399.287628f / dsp->fConst0);
	dsp->fConst110 = mydsp_faustpower2_f(dsp->fConst107);
	dsp->fConst111 = powf(0.00100000005f, (1.0f / (0.0131463278f * dsp->fConst0)));
	dsp->fConst112 = (0.0f - (2.0f * dsp->fConst111));
	dsp->fConst113 = (410.686584f / dsp->fConst0);
	dsp->fConst114 = mydsp_faustpower2_f(dsp->fConst111);
	dsp->fConst115 = powf(0.00100000005f, (1.0f / (0.0123624494f * dsp->fConst0)));
	dsp->fConst116 = (0.0f - (2.0f * dsp->fConst115));
	dsp->fConst117 = (420.713928f / dsp->fConst0);
	dsp->fConst118 = mydsp_faustpower2_f(dsp->fConst115);
	dsp->fConst119 = powf(0.00100000005f, (1.0f / (0.00913601927f * dsp->fConst0)));
	dsp->fConst120 = (0.0f - (2.0f * dsp->fConst119));
	dsp->fConst121 = (468.286438f / dsp->fConst0);
	dsp->fConst122 = mydsp_faustpower2_f(dsp->fConst119);
	dsp->fConst123 = powf(0.00100000005f, (1.0f / (0.00767402584f * dsp->fConst0)));
	dsp->fConst124 = (0.0f - (2.0f * dsp->fConst123));
	dsp->fConst125 = (494.436432f / dsp->fConst0);
	dsp->fConst126 = mydsp_faustpower2_f(dsp->fConst123);
	dsp->fConst127 = powf(0.00100000005f, (1.0f / (0.00699721137f * dsp->fConst0)));
	dsp->fConst128 = (0.0f - (2.0f * dsp->fConst127));
	dsp->fConst129 = (507.916992f / dsp->fConst0);
	dsp->fConst130 = mydsp_faustpower2_f(dsp->fConst127);
	dsp->fConst131 = powf(0.00100000005f, (1.0f / (0.00462675327f * dsp->fConst0)));
	dsp->fConst132 = (0.0f - (2.0f * dsp->fConst131));
	dsp->fConst133 = (565.34845f / dsp->fConst0);
	dsp->fConst134 = mydsp_faustpower2_f(dsp->fConst131);
	dsp->fConst135 = powf(0.00100000005f, (1.0f / (0.00401024008f * dsp->fConst0)));
	dsp->fConst136 = (0.0f - (2.0f * dsp->fConst135));
	dsp->fConst137 = (584.12323f / dsp->fConst0);
	dsp->fConst138 = mydsp_faustpower2_f(dsp->fConst135);
	dsp->fConst139 = powf(0.00100000005f, (1.0f / (0.00359531236f * dsp->fConst0)));
	dsp->fConst140 = (0.0f - (2.0f * dsp->fConst139));
	dsp->fConst141 = (598.105225f / dsp->fConst0);
	dsp->fConst142 = mydsp_faustpower2_f(dsp->fConst139);
	dsp->fConst143 = powf(0.00100000005f, (1.0f / (0.00320503488f * dsp->fConst0)));
	dsp->fConst144 = (0.0f - (2.0f * dsp->fConst143));
	dsp->fConst145 = (612.489319f / dsp->fConst0);
	dsp->fConst146 = mydsp_faustpower2_f(dsp->fConst143);
	dsp->fConst147 = powf(0.00100000005f, (1.0f / (0.0015662252f * dsp->fConst0)));
	dsp->fConst148 = (0.0f - (2.0f * dsp->fConst147));
	dsp->fConst149 = (695.045959f / dsp->fConst0);
	dsp->fConst150 = mydsp_faustpower2_f(dsp->fConst147);
	dsp->fConst151 = powf(0.00100000005f, (1.0f / (0.00143769139f * dsp->fConst0)));
	dsp->fConst152 = (0.0f - (2.0f * dsp->fConst151));
	dsp->fConst153 = (704.150269f / dsp->fConst0);
	dsp->fConst154 = mydsp_faustpower2_f(dsp->fConst151);
	dsp->fConst155 = powf(0.00100000005f, (1.0f / (0.00129330496f * dsp->fConst0)));
	dsp->fConst156 = (0.0f - (2.0f * dsp->fConst155));
	dsp->fConst157 = (715.18988f / dsp->fConst0);
	dsp->fConst158 = mydsp_faustpower2_f(dsp->fConst155);
	dsp->fConst159 = powf(0.00100000005f, (1.0f / (0.000912711956f * dsp->fConst0)));
	dsp->fConst160 = (0.0f - (2.0f * dsp->fConst159));
	dsp->fConst161 = (749.935852f / dsp->fConst0);
	dsp->fConst162 = mydsp_faustpower2_f(dsp->fConst159);
	dsp->fConst163 = powf(0.00100000005f, (1.0f / (0.000537810789f * dsp->fConst0)));
	dsp->fConst164 = (0.0f - (2.0f * dsp->fConst163));
	dsp->fConst165 = (798.247253f / dsp->fConst0);
	dsp->fConst166 = mydsp_faustpower2_f(dsp->fConst163);
	dsp->fConst167 = powf(0.00100000005f, (1.0f / (0.000432563043f * dsp->fConst0)));
	dsp->fConst168 = (0.0f - (2.0f * dsp->fConst167));
	dsp->fConst169 = (816.700989f / dsp->fConst0);
	dsp->fConst170 = mydsp_faustpower2_f(dsp->fConst167);
	dsp->fConst171 = powf(0.00100000005f, (1.0f / (0.000362893392f * dsp->fConst0)));
	dsp->fConst172 = (0.0f - (2.0f * dsp->fConst171));
	dsp->fConst173 = (831.007812f / dsp->fConst0);
	dsp->fConst174 = mydsp_faustpower2_f(dsp->fConst171);
	dsp->fConst175 = powf(0.00100000005f, (1.0f / (0.000329498813f * dsp->fConst0)));
	dsp->fConst176 = (0.0f - (2.0f * dsp->fConst175));
	dsp->fConst177 = (838.660706f / dsp->fConst0);
	dsp->fConst178 = mydsp_faustpower2_f(dsp->fConst175);
	dsp->fConst179 = powf(0.00100000005f, (1.0f / (0.000124247395f * dsp->fConst0)));
	dsp->fConst180 = (0.0f - (2.0f * dsp->fConst179));
	dsp->fConst181 = (908.228149f / dsp->fConst0);
	dsp->fConst182 = mydsp_faustpower2_f(dsp->fConst179);
	dsp->fConst183 = powf(0.00100000005f, (1.0f / (7.53835775e-05f * dsp->fConst0)));
	dsp->fConst184 = (0.0f - (2.0f * dsp->fConst183));
	dsp->fConst185 = (938.946655f / dsp->fConst0);
	dsp->fConst186 = mydsp_faustpower2_f(dsp->fConst183);
	dsp->fConst187 = powf(0.00100000005f, (1.0f / (5.65755508e-05f * dsp->fConst0)));
	dsp->fConst188 = (0.0f - (2.0f * dsp->fConst187));
	dsp->fConst189 = (955.251526f / dsp->fConst0);
	dsp->fConst190 = mydsp_faustpower2_f(dsp->fConst187);
	dsp->fConst191 = powf(0.00100000005f, (1.0f / (4.96453904e-05f * dsp->fConst0)));
	dsp->fConst192 = (0.0f - (2.0f * dsp->fConst191));
	dsp->fConst193 = (962.370361f / dsp->fConst0);
	dsp->fConst194 = mydsp_faustpower2_f(dsp->fConst191);
	dsp->fConst195 = powf(0.00100000005f, (1.0f / (3.7056674e-05f * dsp->fConst0)));
	dsp->fConst196 = (0.0f - (2.0f * dsp->fConst195));
	dsp->fConst197 = (977.644775f / dsp->fConst0);
	dsp->fConst198 = mydsp_faustpower2_f(dsp->fConst195);
	dsp->fConst199 = powf(0.00100000005f, (1.0f / (2.66114275e-05f * dsp->fConst0)));
	dsp->fConst200 = (0.0f - (2.0f * dsp->fConst199));
	dsp->fConst201 = (993.893127f / dsp->fConst0);
	dsp->fConst202 = mydsp_faustpower2_f(dsp->fConst199);
	dsp->fConst203 = powf(0.00100000005f, (1.0f / (5.79888183e-06f * dsp->fConst0)));
	dsp->fConst204 = (0.0f - (2.0f * dsp->fConst203));
	dsp->fConst205 = (1056.23486f / dsp->fConst0);
	dsp->fConst206 = mydsp_faustpower2_f(dsp->fConst203);
	dsp->fConst207 = powf(0.00100000005f, (1.0f / (2.80919903e-06f * dsp->fConst0)));
	dsp->fConst208 = (0.0f - (2.0f * dsp->fConst207));
	dsp->fConst209 = (1079.84705f / dsp->fConst0);
	dsp->fConst210 = mydsp_faustpower2_f(dsp->fConst207);
	dsp->fConst211 = powf(0.00100000005f, (1.0f / (1.5867239e-06f * dsp->fConst0)));
	dsp->fConst212 = (0.0f - (2.0f * dsp->fConst211));
	dsp->fConst213 = (1096.1897f / dsp->fConst0);
	dsp->fConst214 = mydsp_faustpower2_f(dsp->fConst211);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "marimba");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "midi");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freq", &dsp->fHslider1, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gain", &dsp->fHslider2, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "otherParams");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "midi", "ctrl 1");
	ui_interface->addNumEntry(ui_interface->uiInterface, "strikePosition", &dsp->fEntry0, 0.0f, 0.0f, 4.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "midi", "ctrl 1");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "strikeCutOff", &dsp->fHslider3, 6500.0f, 20.0f, 20000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "outGain", &dsp->fHslider0, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "strikeSharpness", &dsp->fHslider4, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fButton0, "3", "");
	ui_interface->addButton(ui_interface->uiInterface, "gate", &dsp->fButton0);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (dsp->fConst1 * ((340.0f / fSlow1) + -0.0399999991f));
	float fSlow3 = (fSlow2 + -1.49999499f);
	float fSlow4 = floorf(fSlow3);
	float fSlow5 = (fSlow2 + (-1.0f - fSlow4));
	float fSlow6 = (fSlow2 + (-2.0f - fSlow4));
	float fSlow7 = (fSlow2 + (-3.0f - fSlow4));
	float fSlow8 = (fSlow2 + (-4.0f - fSlow4));
	float fSlow9 = ((((0.0f - fSlow5) * (0.0f - (0.5f * fSlow6))) * (0.0f - (0.333333343f * fSlow7))) * (0.0f - (0.25f * fSlow8)));
	int iSlow10 = (int)fSlow3;
	int iSlow11 = (int)min(dsp->fConst2, (float)max(0, iSlow10));
	float fSlow12 = (fSlow2 - fSlow4);
	float fSlow13 = (((0.0f - fSlow6) * (0.0f - (0.5f * fSlow7))) * (0.0f - (0.333333343f * fSlow8)));
	int iSlow14 = (int)min(dsp->fConst2, (float)max(0, (iSlow10 + 1)));
	float fSlow15 = (0.5f * ((fSlow5 * (0.0f - fSlow7)) * (0.0f - (0.5f * fSlow8))));
	int iSlow16 = (int)min(dsp->fConst2, (float)max(0, (iSlow10 + 2)));
	float fSlow17 = (fSlow5 * fSlow6);
	float fSlow18 = (0.166666672f * (fSlow17 * (0.0f - fSlow8)));
	int iSlow19 = (int)min(dsp->fConst2, (float)max(0, (iSlow10 + 3)));
	float fSlow20 = (0.0416666679f * (fSlow17 * fSlow7));
	int iSlow21 = (int)min(dsp->fConst2, (float)max(0, (iSlow10 + 4)));
	int iSlow22 = (50 * (int)(float)dsp->fEntry0);
	float fSlow23 = (((178.936996f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 44)]:0.0f);
	float fSlow24 = tanf((dsp->fConst4 * (float)dsp->fHslider3));
	float fSlow25 = (1.0f / fSlow24);
	float fSlow26 = (((fSlow25 + 1.41421354f) / fSlow24) + 1.0f);
	float fSlow27 = ((float)dsp->fHslider2 / fSlow26);
	float fSlow28 = (1.0f / fSlow26);
	float fSlow29 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow24))));
	float fSlow30 = (((fSlow25 + -1.41421354f) / fSlow24) + 1.0f);
	float fSlow31 = (float)dsp->fButton0;
	float fSlow32 = (float)dsp->fHslider4;
	float fSlow33 = (dsp->fConst12 * fSlow32);
	float fSlow34 = (dsp->fConst13 * fSlow32);
	float fSlow35 = (dsp->fConst14 / fSlow32);
	float fSlow36 = (dsp->fConst17 * cosf((dsp->fConst18 * fSlow1)));
	float fSlow37 = (((181.481995f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 45)]:0.0f);
	float fSlow38 = (dsp->fConst20 * cosf((dsp->fConst21 * fSlow1)));
	float fSlow39 = (((185.397995f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 46)]:0.0f);
	float fSlow40 = (dsp->fConst24 * cosf((dsp->fConst25 * fSlow1)));
	float fSlow41 = (((190.369003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 47)]:0.0f);
	float fSlow42 = (dsp->fConst28 * cosf((dsp->fConst29 * fSlow1)));
	float fSlow43 = (((192.190002f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 48)]:0.0f);
	float fSlow44 = (dsp->fConst32 * cosf((dsp->fConst33 * fSlow1)));
	float fSlow45 = (((195.505005f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 49)]:0.0f);
	float fSlow46 = (dsp->fConst36 * cosf((dsp->fConst37 * fSlow1)));
	float fSlow47 = ((fSlow1 < dsp->fConst3)?ftbl0mydspSIG0[iSlow22]:0.0f);
	float fSlow48 = (dsp->fConst40 * cosf((dsp->fConst41 * fSlow1)));
	float fSlow49 = (((3.31356001f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 1)]:0.0f);
	float fSlow50 = (dsp->fConst44 * cosf((dsp->fConst45 * fSlow1)));
	float fSlow51 = (((3.83469009f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 2)]:0.0f);
	float fSlow52 = (dsp->fConst48 * cosf((dsp->fConst49 * fSlow1)));
	float fSlow53 = (((8.06313038f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 3)]:0.0f);
	float fSlow54 = (dsp->fConst52 * cosf((dsp->fConst53 * fSlow1)));
	float fSlow55 = (((9.44777966f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 4)]:0.0f);
	float fSlow56 = (dsp->fConst56 * cosf((dsp->fConst57 * fSlow1)));
	float fSlow57 = (((14.1169004f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 5)]:0.0f);
	float fSlow58 = (dsp->fConst60 * cosf((dsp->fConst61 * fSlow1)));
	float fSlow59 = (((18.3840008f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 6)]:0.0f);
	float fSlow60 = (dsp->fConst64 * cosf((dsp->fConst65 * fSlow1)));
	float fSlow61 = (((21.0102005f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 7)]:0.0f);
	float fSlow62 = (dsp->fConst68 * cosf((dsp->fConst69 * fSlow1)));
	float fSlow63 = (((26.1774998f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 8)]:0.0f);
	float fSlow64 = (dsp->fConst72 * cosf((dsp->fConst73 * fSlow1)));
	float fSlow65 = (((28.9944f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 9)]:0.0f);
	float fSlow66 = (dsp->fConst76 * cosf((dsp->fConst77 * fSlow1)));
	float fSlow67 = (((37.0727997f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 10)]:0.0f);
	float fSlow68 = (dsp->fConst80 * cosf((dsp->fConst81 * fSlow1)));
	float fSlow69 = (((37.8703003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 11)]:0.0f);
	float fSlow70 = (dsp->fConst84 * cosf((dsp->fConst85 * fSlow1)));
	float fSlow71 = (((40.0634003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 12)]:0.0f);
	float fSlow72 = (dsp->fConst88 * cosf((dsp->fConst89 * fSlow1)));
	float fSlow73 = (((47.6439018f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 13)]:0.0f);
	float fSlow74 = (dsp->fConst92 * cosf((dsp->fConst93 * fSlow1)));
	float fSlow75 = (((51.019001f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 14)]:0.0f);
	float fSlow76 = (dsp->fConst96 * cosf((dsp->fConst97 * fSlow1)));
	float fSlow77 = (((52.4300003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 15)]:0.0f);
	float fSlow78 = (dsp->fConst100 * cosf((dsp->fConst101 * fSlow1)));
	float fSlow79 = (((58.2859993f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 16)]:0.0f);
	float fSlow80 = (dsp->fConst104 * cosf((dsp->fConst105 * fSlow1)));
	float fSlow81 = (((63.5485992f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 17)]:0.0f);
	float fSlow82 = (dsp->fConst108 * cosf((dsp->fConst109 * fSlow1)));
	float fSlow83 = (((65.3628006f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 18)]:0.0f);
	float fSlow84 = (dsp->fConst112 * cosf((dsp->fConst113 * fSlow1)));
	float fSlow85 = (((66.9587021f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 19)]:0.0f);
	float fSlow86 = (dsp->fConst116 * cosf((dsp->fConst117 * fSlow1)));
	float fSlow87 = (((74.530098f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 20)]:0.0f);
	float fSlow88 = (dsp->fConst120 * cosf((dsp->fConst121 * fSlow1)));
	float fSlow89 = (((78.6920013f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 21)]:0.0f);
	float fSlow90 = (dsp->fConst124 * cosf((dsp->fConst125 * fSlow1)));
	float fSlow91 = (((80.8375015f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 22)]:0.0f);
	float fSlow92 = (dsp->fConst128 * cosf((dsp->fConst129 * fSlow1)));
	float fSlow93 = (((89.9779968f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 23)]:0.0f);
	float fSlow94 = (dsp->fConst132 * cosf((dsp->fConst133 * fSlow1)));
	float fSlow95 = (((92.9661026f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 24)]:0.0f);
	float fSlow96 = (dsp->fConst136 * cosf((dsp->fConst137 * fSlow1)));
	float fSlow97 = (((95.1913986f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 25)]:0.0f);
	float fSlow98 = (dsp->fConst140 * cosf((dsp->fConst141 * fSlow1)));
	float fSlow99 = (((97.4806976f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 26)]:0.0f);
	float fSlow100 = (dsp->fConst144 * cosf((dsp->fConst145 * fSlow1)));
	float fSlow101 = (((110.620003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 27)]:0.0f);
	float fSlow102 = (dsp->fConst148 * cosf((dsp->fConst149 * fSlow1)));
	float fSlow103 = (((112.069f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 28)]:0.0f);
	float fSlow104 = (dsp->fConst152 * cosf((dsp->fConst153 * fSlow1)));
	float fSlow105 = (((113.825996f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 29)]:0.0f);
	float fSlow106 = (dsp->fConst156 * cosf((dsp->fConst157 * fSlow1)));
	float fSlow107 = (((119.356003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 30)]:0.0f);
	float fSlow108 = (dsp->fConst160 * cosf((dsp->fConst161 * fSlow1)));
	float fSlow109 = (((127.044998f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 31)]:0.0f);
	float fSlow110 = (dsp->fConst164 * cosf((dsp->fConst165 * fSlow1)));
	float fSlow111 = (((129.981995f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 32)]:0.0f);
	float fSlow112 = (dsp->fConst168 * cosf((dsp->fConst169 * fSlow1)));
	float fSlow113 = (((132.259003f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 33)]:0.0f);
	float fSlow114 = (dsp->fConst172 * cosf((dsp->fConst173 * fSlow1)));
	float fSlow115 = (((133.477005f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 34)]:0.0f);
	float fSlow116 = (dsp->fConst176 * cosf((dsp->fConst177 * fSlow1)));
	float fSlow117 = (((144.548996f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 35)]:0.0f);
	float fSlow118 = (dsp->fConst180 * cosf((dsp->fConst181 * fSlow1)));
	float fSlow119 = (((149.438004f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 36)]:0.0f);
	float fSlow120 = (dsp->fConst184 * cosf((dsp->fConst185 * fSlow1)));
	float fSlow121 = (((152.033005f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 37)]:0.0f);
	float fSlow122 = (dsp->fConst188 * cosf((dsp->fConst189 * fSlow1)));
	float fSlow123 = (((153.166f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 38)]:0.0f);
	float fSlow124 = (dsp->fConst192 * cosf((dsp->fConst193 * fSlow1)));
	float fSlow125 = (((155.597f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 39)]:0.0f);
	float fSlow126 = (dsp->fConst196 * cosf((dsp->fConst197 * fSlow1)));
	float fSlow127 = (((158.182999f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 40)]:0.0f);
	float fSlow128 = (dsp->fConst200 * cosf((dsp->fConst201 * fSlow1)));
	float fSlow129 = (((168.104996f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 41)]:0.0f);
	float fSlow130 = (dsp->fConst204 * cosf((dsp->fConst205 * fSlow1)));
	float fSlow131 = (((171.863007f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 42)]:0.0f);
	float fSlow132 = (dsp->fConst208 * cosf((dsp->fConst209 * fSlow1)));
	float fSlow133 = (((174.464005f * fSlow1) < dsp->fConst3)?ftbl0mydspSIG0[(iSlow22 + 43)]:0.0f);
	float fSlow134 = (dsp->fConst212 * cosf((dsp->fConst213 * fSlow1)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec2[0] = 0;
			dsp->fRec9[0] = ((0.949999988f * dsp->fRec9[1]) + (0.0500000007f * dsp->fRec7[1]));
			float fTemp0 = ((0.99000001f * dsp->fRec9[0]) + (float)dsp->iRec2[1]);
			dsp->fVec0[(dsp->IOTA & 2047)] = fTemp0;
			dsp->fRec6[0] = ((fSlow9 * dsp->fVec0[((dsp->IOTA - iSlow11) & 2047)]) + (fSlow12 * ((((fSlow13 * dsp->fVec0[((dsp->IOTA - iSlow14) & 2047)]) + (fSlow15 * dsp->fVec0[((dsp->IOTA - iSlow16) & 2047)])) + (fSlow18 * dsp->fVec0[((dsp->IOTA - iSlow19) & 2047)])) + (fSlow20 * dsp->fVec0[((dsp->IOTA - iSlow21) & 2047)]))));
			dsp->iRec13[0] = ((1103515245 * dsp->iRec13[1]) + 12345);
			dsp->fRec12[0] = ((4.65661287e-10f * (float)dsp->iRec13[0]) - (dsp->fConst7 * ((dsp->fConst9 * dsp->fRec12[2]) + (dsp->fConst10 * dsp->fRec12[1]))));
			dsp->fRec11[0] = ((dsp->fConst7 * (((dsp->fConst8 * dsp->fRec12[0]) + (dsp->fConst11 * dsp->fRec12[1])) + (dsp->fConst8 * dsp->fRec12[2]))) - (fSlow28 * ((fSlow29 * dsp->fRec11[1]) + (fSlow30 * dsp->fRec11[2]))));
			dsp->fVec1[0] = fSlow31;
			dsp->fVec2[0] = fSlow32;
			dsp->fRec14[0] = ((((fSlow31 - dsp->fVec1[1]) > 0.0f) > 0)?0.0f:min(fSlow33, ((dsp->fRec14[1] + (dsp->fConst12 * (fSlow32 - dsp->fVec2[1]))) + 1.0f)));
			int iTemp1 = (dsp->fRec14[0] < fSlow34);
			float fTemp2 = (fSlow27 * ((dsp->fRec11[2] + (dsp->fRec11[0] + (2.0f * dsp->fRec11[1]))) * (iTemp1?((dsp->fRec14[0] < 0.0f)?0.0f:(iTemp1?(fSlow35 * dsp->fRec14[0]):1.0f)):((dsp->fRec14[0] < fSlow33)?((fSlow35 * (0.0f - (dsp->fRec14[0] - fSlow34))) + 1.0f):0.0f))));
			dsp->fRec10[0] = (fTemp2 - ((dsp->fConst16 * dsp->fRec10[2]) + (fSlow36 * dsp->fRec10[1])));
			dsp->fRec15[0] = (fTemp2 - ((fSlow38 * dsp->fRec15[1]) + (dsp->fConst22 * dsp->fRec15[2])));
			dsp->fRec16[0] = (fTemp2 - ((fSlow40 * dsp->fRec16[1]) + (dsp->fConst26 * dsp->fRec16[2])));
			dsp->fRec17[0] = (fTemp2 - ((fSlow42 * dsp->fRec17[1]) + (dsp->fConst30 * dsp->fRec17[2])));
			dsp->fRec18[0] = (fTemp2 - ((fSlow44 * dsp->fRec18[1]) + (dsp->fConst34 * dsp->fRec18[2])));
			dsp->fRec19[0] = (fTemp2 - ((fSlow46 * dsp->fRec19[1]) + (dsp->fConst38 * dsp->fRec19[2])));
			dsp->fRec20[0] = (fTemp2 - ((fSlow48 * dsp->fRec20[1]) + (dsp->fConst42 * dsp->fRec20[2])));
			dsp->fRec21[0] = (fTemp2 - ((fSlow50 * dsp->fRec21[1]) + (dsp->fConst46 * dsp->fRec21[2])));
			dsp->fRec22[0] = (fTemp2 - ((fSlow52 * dsp->fRec22[1]) + (dsp->fConst50 * dsp->fRec22[2])));
			dsp->fRec23[0] = (fTemp2 - ((fSlow54 * dsp->fRec23[1]) + (dsp->fConst54 * dsp->fRec23[2])));
			dsp->fRec24[0] = (fTemp2 - ((fSlow56 * dsp->fRec24[1]) + (dsp->fConst58 * dsp->fRec24[2])));
			dsp->fRec25[0] = (fTemp2 - ((fSlow58 * dsp->fRec25[1]) + (dsp->fConst62 * dsp->fRec25[2])));
			dsp->fRec26[0] = (fTemp2 - ((fSlow60 * dsp->fRec26[1]) + (dsp->fConst66 * dsp->fRec26[2])));
			dsp->fRec27[0] = (fTemp2 - ((fSlow62 * dsp->fRec27[1]) + (dsp->fConst70 * dsp->fRec27[2])));
			dsp->fRec28[0] = (fTemp2 - ((fSlow64 * dsp->fRec28[1]) + (dsp->fConst74 * dsp->fRec28[2])));
			dsp->fRec29[0] = (fTemp2 - ((fSlow66 * dsp->fRec29[1]) + (dsp->fConst78 * dsp->fRec29[2])));
			dsp->fRec30[0] = (fTemp2 - ((fSlow68 * dsp->fRec30[1]) + (dsp->fConst82 * dsp->fRec30[2])));
			dsp->fRec31[0] = (fTemp2 - ((fSlow70 * dsp->fRec31[1]) + (dsp->fConst86 * dsp->fRec31[2])));
			dsp->fRec32[0] = (fTemp2 - ((fSlow72 * dsp->fRec32[1]) + (dsp->fConst90 * dsp->fRec32[2])));
			dsp->fRec33[0] = (fTemp2 - ((fSlow74 * dsp->fRec33[1]) + (dsp->fConst94 * dsp->fRec33[2])));
			dsp->fRec34[0] = (fTemp2 - ((fSlow76 * dsp->fRec34[1]) + (dsp->fConst98 * dsp->fRec34[2])));
			dsp->fRec35[0] = (fTemp2 - ((fSlow78 * dsp->fRec35[1]) + (dsp->fConst102 * dsp->fRec35[2])));
			dsp->fRec36[0] = (fTemp2 - ((fSlow80 * dsp->fRec36[1]) + (dsp->fConst106 * dsp->fRec36[2])));
			dsp->fRec37[0] = (fTemp2 - ((fSlow82 * dsp->fRec37[1]) + (dsp->fConst110 * dsp->fRec37[2])));
			dsp->fRec38[0] = (fTemp2 - ((fSlow84 * dsp->fRec38[1]) + (dsp->fConst114 * dsp->fRec38[2])));
			dsp->fRec39[0] = (fTemp2 - ((fSlow86 * dsp->fRec39[1]) + (dsp->fConst118 * dsp->fRec39[2])));
			dsp->fRec40[0] = (fTemp2 - ((fSlow88 * dsp->fRec40[1]) + (dsp->fConst122 * dsp->fRec40[2])));
			dsp->fRec41[0] = (fTemp2 - ((fSlow90 * dsp->fRec41[1]) + (dsp->fConst126 * dsp->fRec41[2])));
			dsp->fRec42[0] = (fTemp2 - ((fSlow92 * dsp->fRec42[1]) + (dsp->fConst130 * dsp->fRec42[2])));
			dsp->fRec43[0] = (fTemp2 - ((fSlow94 * dsp->fRec43[1]) + (dsp->fConst134 * dsp->fRec43[2])));
			dsp->fRec44[0] = (fTemp2 - ((fSlow96 * dsp->fRec44[1]) + (dsp->fConst138 * dsp->fRec44[2])));
			dsp->fRec45[0] = (fTemp2 - ((fSlow98 * dsp->fRec45[1]) + (dsp->fConst142 * dsp->fRec45[2])));
			dsp->fRec46[0] = (fTemp2 - ((fSlow100 * dsp->fRec46[1]) + (dsp->fConst146 * dsp->fRec46[2])));
			dsp->fRec47[0] = (fTemp2 - ((fSlow102 * dsp->fRec47[1]) + (dsp->fConst150 * dsp->fRec47[2])));
			dsp->fRec48[0] = (fTemp2 - ((fSlow104 * dsp->fRec48[1]) + (dsp->fConst154 * dsp->fRec48[2])));
			dsp->fRec49[0] = (fTemp2 - ((fSlow106 * dsp->fRec49[1]) + (dsp->fConst158 * dsp->fRec49[2])));
			dsp->fRec50[0] = (fTemp2 - ((fSlow108 * dsp->fRec50[1]) + (dsp->fConst162 * dsp->fRec50[2])));
			dsp->fRec51[0] = (fTemp2 - ((fSlow110 * dsp->fRec51[1]) + (dsp->fConst166 * dsp->fRec51[2])));
			dsp->fRec52[0] = (fTemp2 - ((fSlow112 * dsp->fRec52[1]) + (dsp->fConst170 * dsp->fRec52[2])));
			dsp->fRec53[0] = (fTemp2 - ((fSlow114 * dsp->fRec53[1]) + (dsp->fConst174 * dsp->fRec53[2])));
			dsp->fRec54[0] = (fTemp2 - ((fSlow116 * dsp->fRec54[1]) + (dsp->fConst178 * dsp->fRec54[2])));
			dsp->fRec55[0] = (fTemp2 - ((fSlow118 * dsp->fRec55[1]) + (dsp->fConst182 * dsp->fRec55[2])));
			dsp->fRec56[0] = (fTemp2 - ((fSlow120 * dsp->fRec56[1]) + (dsp->fConst186 * dsp->fRec56[2])));
			dsp->fRec57[0] = (fTemp2 - ((fSlow122 * dsp->fRec57[1]) + (dsp->fConst190 * dsp->fRec57[2])));
			dsp->fRec58[0] = (fTemp2 - ((fSlow124 * dsp->fRec58[1]) + (dsp->fConst194 * dsp->fRec58[2])));
			dsp->fRec59[0] = (fTemp2 - ((fSlow126 * dsp->fRec59[1]) + (dsp->fConst198 * dsp->fRec59[2])));
			dsp->fRec60[0] = (fTemp2 - ((fSlow128 * dsp->fRec60[1]) + (dsp->fConst202 * dsp->fRec60[2])));
			dsp->fRec61[0] = (fTemp2 - ((fSlow130 * dsp->fRec61[1]) + (dsp->fConst206 * dsp->fRec61[2])));
			dsp->fRec62[0] = (fTemp2 - ((fSlow132 * dsp->fRec62[1]) + (dsp->fConst210 * dsp->fRec62[2])));
			dsp->fRec63[0] = (fTemp2 - ((fSlow134 * dsp->fRec63[1]) + (dsp->fConst214 * dsp->fRec63[2])));
			float fTemp3 = ((((((((((((((((((((((((((((((((((((((((((((((((((fSlow23 * (dsp->fRec10[0] - dsp->fRec10[2])) + (fSlow37 * (dsp->fRec15[0] - dsp->fRec15[2]))) + (fSlow39 * (dsp->fRec16[0] - dsp->fRec16[2]))) + (fSlow41 * (dsp->fRec17[0] - dsp->fRec17[2]))) + (fSlow43 * (dsp->fRec18[0] - dsp->fRec18[2]))) + (fSlow45 * (dsp->fRec19[0] - dsp->fRec19[2]))) + (fSlow47 * (dsp->fRec20[0] - dsp->fRec20[2]))) + (fSlow49 * (dsp->fRec21[0] - dsp->fRec21[2]))) + (fSlow51 * (dsp->fRec22[0] - dsp->fRec22[2]))) + (fSlow53 * (dsp->fRec23[0] - dsp->fRec23[2]))) + (fSlow55 * (dsp->fRec24[0] - dsp->fRec24[2]))) + (fSlow57 * (dsp->fRec25[0] - dsp->fRec25[2]))) + (fSlow59 * (dsp->fRec26[0] - dsp->fRec26[2]))) + (fSlow61 * (dsp->fRec27[0] - dsp->fRec27[2]))) + (fSlow63 * (dsp->fRec28[0] - dsp->fRec28[2]))) + (fSlow65 * (dsp->fRec29[0] - dsp->fRec29[2]))) + (fSlow67 * (dsp->fRec30[0] - dsp->fRec30[2]))) + (fSlow69 * (dsp->fRec31[0] - dsp->fRec31[2]))) + (fSlow71 * (dsp->fRec32[0] - dsp->fRec32[2]))) + (fSlow73 * (dsp->fRec33[0] - dsp->fRec33[2]))) + (fSlow75 * (dsp->fRec34[0] - dsp->fRec34[2]))) + (fSlow77 * (dsp->fRec35[0] - dsp->fRec35[2]))) + (fSlow79 * (dsp->fRec36[0] - dsp->fRec36[2]))) + (fSlow81 * (dsp->fRec37[0] - dsp->fRec37[2]))) + (fSlow83 * (dsp->fRec38[0] - dsp->fRec38[2]))) + (fSlow85 * (dsp->fRec39[0] - dsp->fRec39[2]))) + (fSlow87 * (dsp->fRec40[0] - dsp->fRec40[2]))) + (fSlow89 * (dsp->fRec41[0] - dsp->fRec41[2]))) + (fSlow91 * (dsp->fRec42[0] - dsp->fRec42[2]))) + (fSlow93 * (dsp->fRec43[0] - dsp->fRec43[2]))) + (fSlow95 * (dsp->fRec44[0] - dsp->fRec44[2]))) + (fSlow97 * (dsp->fRec45[0] - dsp->fRec45[2]))) + (fSlow99 * (dsp->fRec46[0] - dsp->fRec46[2]))) + (fSlow101 * (dsp->fRec47[0] - dsp->fRec47[2]))) + (fSlow103 * (dsp->fRec48[0] - dsp->fRec48[2]))) + (fSlow105 * (dsp->fRec49[0] - dsp->fRec49[2]))) + (fSlow107 * (dsp->fRec50[0] - dsp->fRec50[2]))) + (fSlow109 * (dsp->fRec51[0] - dsp->fRec51[2]))) + (fSlow111 * (dsp->fRec52[0] - dsp->fRec52[2]))) + (fSlow113 * (dsp->fRec53[0] - dsp->fRec53[2]))) + (fSlow115 * (dsp->fRec54[0] - dsp->fRec54[2]))) + (fSlow117 * (dsp->fRec55[0] - dsp->fRec55[2]))) + (fSlow119 * (dsp->fRec56[0] - dsp->fRec56[2]))) + (fSlow121 * (dsp->fRec57[0] - dsp->fRec57[2]))) + (fSlow123 * (dsp->fRec58[0] - dsp->fRec58[2]))) + (fSlow125 * (dsp->fRec59[0] - dsp->fRec59[2]))) + (fSlow127 * (dsp->fRec60[0] - dsp->fRec60[2]))) + (fSlow129 * (dsp->fRec61[0] - dsp->fRec61[2]))) + (fSlow131 * (dsp->fRec62[0] - dsp->fRec62[2]))) + (fSlow133 * (dsp->fRec63[0] - dsp->fRec63[2])));
			dsp->fVec3[0] = fTemp3;
			dsp->fRec64[0] = ((0.949999988f * dsp->fRec64[1]) + (0.0500000007f * dsp->fRec6[1]));
			float fTemp4 = ((0.0199999996f * dsp->fVec3[1]) + (0.99000001f * dsp->fRec64[0]));
			dsp->fVec4[(dsp->IOTA & 2047)] = fTemp4;
			dsp->fRec7[0] = ((fSlow9 * dsp->fVec4[((dsp->IOTA - iSlow11) & 2047)]) + (fSlow12 * (((fSlow18 * dsp->fVec4[((dsp->IOTA - iSlow19) & 2047)]) + ((fSlow15 * dsp->fVec4[((dsp->IOTA - iSlow16) & 2047)]) + (fSlow13 * dsp->fVec4[((dsp->IOTA - iSlow14) & 2047)]))) + (fSlow20 * dsp->fVec4[((dsp->IOTA - iSlow21) & 2047)]))));
			int iRec8 = 0;
			float fRec3 = dsp->fRec6[0];
			float fRec4 = dsp->fRec7[0];
			float fRec5 = (dsp->fRec7[0] + (float)iRec8);
			dsp->fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp5 = (fSlow0 * fRec1);
			output0[i] = (FAUSTFLOAT)fTemp5;
			output1[i] = (FAUSTFLOAT)fTemp5;
			dsp->iRec2[1] = dsp->iRec2[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->iRec13[1] = dsp->iRec13[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
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
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec57[2] = dsp->fRec57[1];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec60[2] = dsp->fRec60[1];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec61[2] = dsp->fRec61[1];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
