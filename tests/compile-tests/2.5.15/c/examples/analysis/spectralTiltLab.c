/* ------------------------------------------------------------
name: "spectralTiltLab"
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

static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}
static float mydsp_faustpower9_f(float value) {
	return ((((((((value * value) * value) * value) * value) * value) * value) * value) * value);
	
}
static float mydsp_faustpower8_f(float value) {
	return (((((((value * value) * value) * value) * value) * value) * value) * value);
	
}
static float mydsp_faustpower7_f(float value) {
	return ((((((value * value) * value) * value) * value) * value) * value);
	
}
static float mydsp_faustpower6_f(float value) {
	return (((((value * value) * value) * value) * value) * value);
	
}
static float mydsp_faustpower5_f(float value) {
	return ((((value * value) * value) * value) * value);
	
}
static float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
}
static float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
	
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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	int iVec0[4];
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	FAUSTFLOAT fCheckbox0;
	float fConst14;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fConst15;
	FAUSTFLOAT fVslider0;
	float fRec14[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fEntry0;
	float fConst16;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec16[2];
	float fVec1[2];
	float fRec15[2];
	float fConst17;
	float fVec2[2];
	float fConst18;
	float fVec3[2];
	float fVec4[2];
	float fConst19;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec17[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec18[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox3;
	int iRec19[2];
	float fRec20[4];
	float fVec22[2];
	float fRec13[2];
	float fVec23[2];
	float fRec12[2];
	float fVec24[2];
	float fRec11[2];
	float fVec25[2];
	float fRec10[2];
	float fVec26[2];
	float fRec9[2];
	float fVec27[2];
	float fRec8[2];
	float fVec28[2];
	float fRec7[2];
	float fVec29[2];
	float fRec6[2];
	float fVec30[2];
	float fRec5[2];
	float fVec31[2];
	float fRec4[2];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec3[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec2[3];
	float fConst26;
	float fConst27;
	float fConst28;
	float fRec1[3];
	float fConst29;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec27[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec26[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec25[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec24[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec23[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec22[3];
	float fConst67;
	float fRec21[2];
	FAUSTFLOAT fVbargraph1;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fRec34[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec33[3];
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec32[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec31[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec30[3];
	float fConst102;
	float fConst103;
	float fConst104;
	float fRec29[3];
	float fConst105;
	float fRec28[2];
	FAUSTFLOAT fVbargraph2;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec41[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec40[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec39[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec38[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec37[3];
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec36[3];
	float fConst143;
	float fRec35[2];
	FAUSTFLOAT fVbargraph3;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec48[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec47[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fRec46[3];
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec45[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec44[3];
	float fConst178;
	float fConst179;
	float fConst180;
	float fRec43[3];
	float fConst181;
	float fRec42[2];
	FAUSTFLOAT fVbargraph4;
	float fConst182;
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fConst196;
	float fConst197;
	float fConst198;
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec55[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec54[3];
	float fConst206;
	float fConst207;
	float fConst208;
	float fRec53[3];
	float fConst209;
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec52[3];
	float fConst213;
	float fConst214;
	float fConst215;
	float fRec51[3];
	float fConst216;
	float fConst217;
	float fConst218;
	float fRec50[3];
	float fConst219;
	float fRec49[2];
	FAUSTFLOAT fVbargraph5;
	float fConst220;
	float fConst221;
	float fConst222;
	float fConst223;
	float fConst224;
	float fConst225;
	float fConst226;
	float fConst227;
	float fConst228;
	float fConst229;
	float fConst230;
	float fConst231;
	float fConst232;
	float fConst233;
	float fConst234;
	float fConst235;
	float fConst236;
	float fConst237;
	float fConst238;
	float fConst239;
	float fConst240;
	float fRec62[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fRec61[3];
	float fConst244;
	float fConst245;
	float fConst246;
	float fRec60[3];
	float fConst247;
	float fConst248;
	float fConst249;
	float fConst250;
	float fRec59[3];
	float fConst251;
	float fConst252;
	float fConst253;
	float fRec58[3];
	float fConst254;
	float fConst255;
	float fConst256;
	float fRec57[3];
	float fConst257;
	float fRec56[2];
	FAUSTFLOAT fVbargraph6;
	float fConst258;
	float fConst259;
	float fConst260;
	float fConst261;
	float fConst262;
	float fConst263;
	float fConst264;
	float fConst265;
	float fConst266;
	float fConst267;
	float fConst268;
	float fConst269;
	float fConst270;
	float fConst271;
	float fConst272;
	float fConst273;
	float fConst274;
	float fConst275;
	float fConst276;
	float fConst277;
	float fConst278;
	float fRec69[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fRec68[3];
	float fConst282;
	float fConst283;
	float fConst284;
	float fRec67[3];
	float fConst285;
	float fConst286;
	float fConst287;
	float fConst288;
	float fRec66[3];
	float fConst289;
	float fConst290;
	float fConst291;
	float fRec65[3];
	float fConst292;
	float fConst293;
	float fConst294;
	float fRec64[3];
	float fConst295;
	float fRec63[2];
	FAUSTFLOAT fVbargraph7;
	float fConst296;
	float fConst297;
	float fConst298;
	float fConst299;
	float fConst300;
	float fConst301;
	float fConst302;
	float fConst303;
	float fConst304;
	float fConst305;
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fConst314;
	float fConst315;
	float fConst316;
	float fRec76[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fRec75[3];
	float fConst320;
	float fConst321;
	float fConst322;
	float fRec74[3];
	float fConst323;
	float fConst324;
	float fConst325;
	float fConst326;
	float fRec73[3];
	float fConst327;
	float fConst328;
	float fConst329;
	float fRec72[3];
	float fConst330;
	float fConst331;
	float fConst332;
	float fRec71[3];
	float fConst333;
	float fRec70[2];
	FAUSTFLOAT fVbargraph8;
	float fConst334;
	float fConst335;
	float fConst336;
	float fConst337;
	float fConst338;
	float fConst339;
	float fConst340;
	float fConst341;
	float fConst342;
	float fConst343;
	float fConst344;
	float fConst345;
	float fConst346;
	float fConst347;
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fConst352;
	float fConst353;
	float fConst354;
	float fRec83[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fRec82[3];
	float fConst358;
	float fConst359;
	float fConst360;
	float fRec81[3];
	float fConst361;
	float fConst362;
	float fConst363;
	float fConst364;
	float fRec80[3];
	float fConst365;
	float fConst366;
	float fConst367;
	float fRec79[3];
	float fConst368;
	float fConst369;
	float fConst370;
	float fRec78[3];
	float fConst371;
	float fRec77[2];
	FAUSTFLOAT fVbargraph9;
	float fConst372;
	float fConst373;
	float fConst374;
	float fConst375;
	float fConst376;
	float fConst377;
	float fConst378;
	float fConst379;
	float fConst380;
	float fConst381;
	float fConst382;
	float fConst383;
	float fConst384;
	float fConst385;
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fConst390;
	float fConst391;
	float fConst392;
	float fRec90[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fRec89[3];
	float fConst396;
	float fConst397;
	float fConst398;
	float fRec88[3];
	float fConst399;
	float fConst400;
	float fConst401;
	float fConst402;
	float fRec87[3];
	float fConst403;
	float fConst404;
	float fConst405;
	float fRec86[3];
	float fConst406;
	float fConst407;
	float fConst408;
	float fRec85[3];
	float fConst409;
	float fRec84[2];
	FAUSTFLOAT fVbargraph10;
	float fConst410;
	float fConst411;
	float fConst412;
	float fConst413;
	float fConst414;
	float fConst415;
	float fConst416;
	float fConst417;
	float fConst418;
	float fConst419;
	float fConst420;
	float fConst421;
	float fConst422;
	float fConst423;
	float fConst424;
	float fConst425;
	float fConst426;
	float fConst427;
	float fConst428;
	float fConst429;
	float fConst430;
	float fRec97[3];
	float fConst431;
	float fConst432;
	float fConst433;
	float fRec96[3];
	float fConst434;
	float fConst435;
	float fConst436;
	float fRec95[3];
	float fConst437;
	float fConst438;
	float fConst439;
	float fConst440;
	float fRec94[3];
	float fConst441;
	float fConst442;
	float fConst443;
	float fRec93[3];
	float fConst444;
	float fConst445;
	float fConst446;
	float fRec92[3];
	float fConst447;
	float fRec91[2];
	FAUSTFLOAT fVbargraph11;
	float fConst448;
	float fConst449;
	float fConst450;
	float fConst451;
	float fConst452;
	float fConst453;
	float fConst454;
	float fConst455;
	float fConst456;
	float fConst457;
	float fConst458;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fConst463;
	float fConst464;
	float fConst465;
	float fConst466;
	float fConst467;
	float fConst468;
	float fRec104[3];
	float fConst469;
	float fConst470;
	float fConst471;
	float fRec103[3];
	float fConst472;
	float fConst473;
	float fConst474;
	float fRec102[3];
	float fConst475;
	float fConst476;
	float fConst477;
	float fConst478;
	float fRec101[3];
	float fConst479;
	float fConst480;
	float fConst481;
	float fRec100[3];
	float fConst482;
	float fConst483;
	float fConst484;
	float fRec99[3];
	float fConst485;
	float fRec98[2];
	FAUSTFLOAT fVbargraph12;
	float fConst486;
	float fConst487;
	float fConst488;
	float fConst489;
	float fConst490;
	float fConst491;
	float fConst492;
	float fConst493;
	float fConst494;
	float fConst495;
	float fConst496;
	float fConst497;
	float fConst498;
	float fConst499;
	float fConst500;
	float fConst501;
	float fConst502;
	float fConst503;
	float fConst504;
	float fConst505;
	float fConst506;
	float fRec111[3];
	float fConst507;
	float fConst508;
	float fConst509;
	float fRec110[3];
	float fConst510;
	float fConst511;
	float fConst512;
	float fRec109[3];
	float fConst513;
	float fConst514;
	float fConst515;
	float fConst516;
	float fRec108[3];
	float fConst517;
	float fConst518;
	float fConst519;
	float fRec107[3];
	float fConst520;
	float fConst521;
	float fConst522;
	float fRec106[3];
	float fConst523;
	float fRec105[2];
	FAUSTFLOAT fVbargraph13;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fRec115[3];
	float fConst533;
	float fConst534;
	float fConst535;
	float fRec114[3];
	float fConst536;
	float fConst537;
	float fConst538;
	float fRec113[3];
	float fConst539;
	float fRec112[2];
	FAUSTFLOAT fVbargraph14;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "analyzers.lib/name", "Faust Analyzer Library");
	m->declare(m->metaInterface, "analyzers.lib/version", "0.0");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "spectralTiltLab");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
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
int getOutputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
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
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)50.0f;
	dsp->fHslider1 = (FAUSTFLOAT)100.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)100.0f;
	dsp->fHslider3 = (FAUSTFLOAT)5000.0f;
	dsp->fHslider4 = (FAUSTFLOAT)-0.5f;
	dsp->fVslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fVslider1 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fCheckbox3 = (FAUSTFLOAT)0.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			dsp->iVec0[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec14[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec16[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec15[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fVec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec5[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec6[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec7[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec8[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec17[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec9[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fVec10[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec11[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec12[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec13[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec14[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec15[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec18[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec16[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec17[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fVec18[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec19[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec20[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec21[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->iRec19[l27] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			dsp->fRec20[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fVec22[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec13[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fVec23[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec12[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fVec24[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec11[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fVec25[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec10[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fVec26[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec9[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fVec27[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec8[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fVec28[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec7[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fVec29[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fRec6[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fVec30[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec5[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fVec31[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			dsp->fRec4[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec3[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec2[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec1[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec0[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec27[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec26[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec25[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec24[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			dsp->fRec23[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec22[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec21[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec34[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			dsp->fRec33[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec32[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec31[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec30[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec29[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec28[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec41[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec40[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec39[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			dsp->fRec38[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			dsp->fRec37[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec36[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			dsp->fRec35[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			dsp->fRec48[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec47[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec46[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			dsp->fRec45[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			dsp->fRec44[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec43[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			dsp->fRec42[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec55[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec54[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec53[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			dsp->fRec52[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			dsp->fRec51[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec50[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fRec49[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec62[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec61[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec60[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			dsp->fRec59[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			dsp->fRec58[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec57[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			dsp->fRec56[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec69[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec68[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			dsp->fRec67[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			dsp->fRec66[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			dsp->fRec65[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			dsp->fRec64[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			dsp->fRec63[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			dsp->fRec76[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec75[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			dsp->fRec74[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			dsp->fRec73[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			dsp->fRec72[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec71[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			dsp->fRec70[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			dsp->fRec83[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			dsp->fRec82[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			dsp->fRec81[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			dsp->fRec80[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			dsp->fRec79[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			dsp->fRec78[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			dsp->fRec77[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			dsp->fRec90[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			dsp->fRec89[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			dsp->fRec88[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			dsp->fRec87[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			dsp->fRec86[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			dsp->fRec85[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			dsp->fRec84[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec97[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			dsp->fRec96[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			dsp->fRec95[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			dsp->fRec94[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			dsp->fRec93[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec92[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			dsp->fRec91[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			dsp->fRec104[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			dsp->fRec103[l131] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l132;
		for (l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			dsp->fRec102[l132] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l133;
		for (l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			dsp->fRec101[l133] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l134;
		for (l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			dsp->fRec100[l134] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l135;
		for (l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			dsp->fRec99[l135] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l136;
		for (l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			dsp->fRec98[l136] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l137;
		for (l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			dsp->fRec111[l137] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l138;
		for (l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			dsp->fRec110[l138] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l139;
		for (l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			dsp->fRec109[l139] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l140;
		for (l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			dsp->fRec108[l140] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l141;
		for (l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			dsp->fRec107[l141] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l142;
		for (l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			dsp->fRec106[l142] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l143;
		for (l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			dsp->fRec105[l143] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l144;
		for (l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			dsp->fRec115[l144] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l145;
		for (l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			dsp->fRec114[l145] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l146;
		for (l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			dsp->fRec113[l146] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l147;
		for (l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			dsp->fRec112[l147] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (1000.0f / dsp->fConst0);
	dsp->fConst2 = tanf((50265.4844f / dsp->fConst0));
	dsp->fConst3 = (1.0f / dsp->fConst2);
	dsp->fConst4 = (1.0f / (((dsp->fConst3 + 0.157482162f) / dsp->fConst2) + 0.935140193f));
	dsp->fConst5 = mydsp_faustpower2_f(dsp->fConst2);
	dsp->fConst6 = (50.0638084f / dsp->fConst5);
	dsp->fConst7 = (2.0f * (0.935140193f - dsp->fConst6));
	dsp->fConst8 = (1.0f / (((dsp->fConst3 + 0.743130445f) / dsp->fConst2) + 1.4500711f));
	dsp->fConst9 = (11.0520525f / dsp->fConst5);
	dsp->fConst10 = (2.0f * (1.4500711f - dsp->fConst9));
	dsp->fConst11 = (1.0f / (((dsp->fConst3 + 3.18972731f) / dsp->fConst2) + 4.07678175f));
	dsp->fConst12 = (0.00176617282f / dsp->fConst5);
	dsp->fConst13 = (2.0f * (0.000407678192f - dsp->fConst12));
	dsp->fConst14 = (3.14159274f / dsp->fConst0);
	dsp->fConst15 = (1.0f / tanf((0.5f / dsp->fConst0)));
	dsp->fConst16 = (1.0f / dsp->fConst0);
	dsp->fConst17 = (0.25f * dsp->fConst0);
	dsp->fConst18 = (0.0416666679f * mydsp_faustpower2_f(dsp->fConst0));
	dsp->fConst19 = (0.00520833349f * mydsp_faustpower3_f(dsp->fConst0));
	dsp->fConst20 = (((dsp->fConst3 + -3.18972731f) / dsp->fConst2) + 4.07678175f);
	dsp->fConst21 = (1.0f / dsp->fConst5);
	dsp->fConst22 = (2.0f * (4.07678175f - dsp->fConst21));
	dsp->fConst23 = (dsp->fConst12 + 0.000407678192f);
	dsp->fConst24 = (((dsp->fConst3 + -0.743130445f) / dsp->fConst2) + 1.4500711f);
	dsp->fConst25 = (2.0f * (1.4500711f - dsp->fConst21));
	dsp->fConst26 = (dsp->fConst9 + 1.4500711f);
	dsp->fConst27 = (((dsp->fConst3 + -0.157482162f) / dsp->fConst2) + 0.935140193f);
	dsp->fConst28 = (2.0f * (0.935140193f - dsp->fConst21));
	dsp->fConst29 = (dsp->fConst6 + 0.935140193f);
	dsp->fConst30 = tanf((31665.2695f / dsp->fConst0));
	dsp->fConst31 = (1.0f / dsp->fConst30);
	dsp->fConst32 = (1.0f / (((dsp->fConst31 + 0.157482162f) / dsp->fConst30) + 0.935140193f));
	dsp->fConst33 = mydsp_faustpower2_f(dsp->fConst30);
	dsp->fConst34 = (50.0638084f / dsp->fConst33);
	dsp->fConst35 = (2.0f * (0.935140193f - dsp->fConst34));
	dsp->fConst36 = (1.0f / (((dsp->fConst31 + 0.743130445f) / dsp->fConst30) + 1.4500711f));
	dsp->fConst37 = (11.0520525f / dsp->fConst33);
	dsp->fConst38 = (2.0f * (1.4500711f - dsp->fConst37));
	dsp->fConst39 = (1.0f / (((dsp->fConst31 + 3.18972731f) / dsp->fConst30) + 4.07678175f));
	dsp->fConst40 = (0.00176617282f / dsp->fConst33);
	dsp->fConst41 = (2.0f * (0.000407678192f - dsp->fConst40));
	dsp->fConst42 = (1.0f / (((dsp->fConst3 + 0.168404877f) / dsp->fConst2) + 1.06935835f));
	dsp->fConst43 = (2.0f * (53.5361519f - dsp->fConst21));
	dsp->fConst44 = (1.0f / (((dsp->fConst3 + 0.51247865f) / dsp->fConst2) + 0.689621389f));
	dsp->fConst45 = (2.0f * (7.62173128f - dsp->fConst21));
	dsp->fConst46 = (1.0f / (((dsp->fConst3 + 0.782413065f) / dsp->fConst2) + 0.245291501f));
	dsp->fConst47 = (9.99999975e-05f / dsp->fConst5);
	dsp->fConst48 = (2.0f * (0.000433227193f - dsp->fConst47));
	dsp->fConst49 = (((dsp->fConst3 + -0.782413065f) / dsp->fConst2) + 0.245291501f);
	dsp->fConst50 = (2.0f * (0.245291501f - dsp->fConst21));
	dsp->fConst51 = (dsp->fConst47 + 0.000433227193f);
	dsp->fConst52 = (((dsp->fConst3 + -0.51247865f) / dsp->fConst2) + 0.689621389f);
	dsp->fConst53 = (2.0f * (0.689621389f - dsp->fConst21));
	dsp->fConst54 = (dsp->fConst21 + 7.62173128f);
	dsp->fConst55 = (((dsp->fConst3 + -0.168404877f) / dsp->fConst2) + 1.06935835f);
	dsp->fConst56 = (2.0f * (1.06935835f - dsp->fConst21));
	dsp->fConst57 = (dsp->fConst21 + 53.5361519f);
	dsp->fConst58 = (((dsp->fConst31 + -3.18972731f) / dsp->fConst30) + 4.07678175f);
	dsp->fConst59 = (1.0f / dsp->fConst33);
	dsp->fConst60 = (2.0f * (4.07678175f - dsp->fConst59));
	dsp->fConst61 = (dsp->fConst40 + 0.000407678192f);
	dsp->fConst62 = (((dsp->fConst31 + -0.743130445f) / dsp->fConst30) + 1.4500711f);
	dsp->fConst63 = (2.0f * (1.4500711f - dsp->fConst59));
	dsp->fConst64 = (dsp->fConst37 + 1.4500711f);
	dsp->fConst65 = (((dsp->fConst31 + -0.157482162f) / dsp->fConst30) + 0.935140193f);
	dsp->fConst66 = (2.0f * (0.935140193f - dsp->fConst59));
	dsp->fConst67 = (dsp->fConst34 + 0.935140193f);
	dsp->fConst68 = tanf((19947.8691f / dsp->fConst0));
	dsp->fConst69 = (1.0f / dsp->fConst68);
	dsp->fConst70 = (1.0f / (((dsp->fConst69 + 0.157482162f) / dsp->fConst68) + 0.935140193f));
	dsp->fConst71 = mydsp_faustpower2_f(dsp->fConst68);
	dsp->fConst72 = (50.0638084f / dsp->fConst71);
	dsp->fConst73 = (2.0f * (0.935140193f - dsp->fConst72));
	dsp->fConst74 = (1.0f / (((dsp->fConst69 + 0.743130445f) / dsp->fConst68) + 1.4500711f));
	dsp->fConst75 = (11.0520525f / dsp->fConst71);
	dsp->fConst76 = (2.0f * (1.4500711f - dsp->fConst75));
	dsp->fConst77 = (1.0f / (((dsp->fConst69 + 3.18972731f) / dsp->fConst68) + 4.07678175f));
	dsp->fConst78 = (0.00176617282f / dsp->fConst71);
	dsp->fConst79 = (2.0f * (0.000407678192f - dsp->fConst78));
	dsp->fConst80 = (1.0f / (((dsp->fConst31 + 0.168404877f) / dsp->fConst30) + 1.06935835f));
	dsp->fConst81 = (2.0f * (53.5361519f - dsp->fConst59));
	dsp->fConst82 = (1.0f / (((dsp->fConst31 + 0.51247865f) / dsp->fConst30) + 0.689621389f));
	dsp->fConst83 = (2.0f * (7.62173128f - dsp->fConst59));
	dsp->fConst84 = (1.0f / (((dsp->fConst31 + 0.782413065f) / dsp->fConst30) + 0.245291501f));
	dsp->fConst85 = (9.99999975e-05f / dsp->fConst33);
	dsp->fConst86 = (2.0f * (0.000433227193f - dsp->fConst85));
	dsp->fConst87 = (((dsp->fConst31 + -0.782413065f) / dsp->fConst30) + 0.245291501f);
	dsp->fConst88 = (2.0f * (0.245291501f - dsp->fConst59));
	dsp->fConst89 = (dsp->fConst85 + 0.000433227193f);
	dsp->fConst90 = (((dsp->fConst31 + -0.51247865f) / dsp->fConst30) + 0.689621389f);
	dsp->fConst91 = (2.0f * (0.689621389f - dsp->fConst59));
	dsp->fConst92 = (dsp->fConst59 + 7.62173128f);
	dsp->fConst93 = (((dsp->fConst31 + -0.168404877f) / dsp->fConst30) + 1.06935835f);
	dsp->fConst94 = (2.0f * (1.06935835f - dsp->fConst59));
	dsp->fConst95 = (dsp->fConst59 + 53.5361519f);
	dsp->fConst96 = (((dsp->fConst69 + -3.18972731f) / dsp->fConst68) + 4.07678175f);
	dsp->fConst97 = (1.0f / dsp->fConst71);
	dsp->fConst98 = (2.0f * (4.07678175f - dsp->fConst97));
	dsp->fConst99 = (dsp->fConst78 + 0.000407678192f);
	dsp->fConst100 = (((dsp->fConst69 + -0.743130445f) / dsp->fConst68) + 1.4500711f);
	dsp->fConst101 = (2.0f * (1.4500711f - dsp->fConst97));
	dsp->fConst102 = (dsp->fConst75 + 1.4500711f);
	dsp->fConst103 = (((dsp->fConst69 + -0.157482162f) / dsp->fConst68) + 0.935140193f);
	dsp->fConst104 = (2.0f * (0.935140193f - dsp->fConst97));
	dsp->fConst105 = (dsp->fConst72 + 0.935140193f);
	dsp->fConst106 = tanf((12566.3711f / dsp->fConst0));
	dsp->fConst107 = (1.0f / dsp->fConst106);
	dsp->fConst108 = (1.0f / (((dsp->fConst107 + 0.157482162f) / dsp->fConst106) + 0.935140193f));
	dsp->fConst109 = mydsp_faustpower2_f(dsp->fConst106);
	dsp->fConst110 = (50.0638084f / dsp->fConst109);
	dsp->fConst111 = (2.0f * (0.935140193f - dsp->fConst110));
	dsp->fConst112 = (1.0f / (((dsp->fConst107 + 0.743130445f) / dsp->fConst106) + 1.4500711f));
	dsp->fConst113 = (11.0520525f / dsp->fConst109);
	dsp->fConst114 = (2.0f * (1.4500711f - dsp->fConst113));
	dsp->fConst115 = (1.0f / (((dsp->fConst107 + 3.18972731f) / dsp->fConst106) + 4.07678175f));
	dsp->fConst116 = (0.00176617282f / dsp->fConst109);
	dsp->fConst117 = (2.0f * (0.000407678192f - dsp->fConst116));
	dsp->fConst118 = (1.0f / (((dsp->fConst69 + 0.168404877f) / dsp->fConst68) + 1.06935835f));
	dsp->fConst119 = (2.0f * (53.5361519f - dsp->fConst97));
	dsp->fConst120 = (1.0f / (((dsp->fConst69 + 0.51247865f) / dsp->fConst68) + 0.689621389f));
	dsp->fConst121 = (2.0f * (7.62173128f - dsp->fConst97));
	dsp->fConst122 = (1.0f / (((dsp->fConst69 + 0.782413065f) / dsp->fConst68) + 0.245291501f));
	dsp->fConst123 = (9.99999975e-05f / dsp->fConst71);
	dsp->fConst124 = (2.0f * (0.000433227193f - dsp->fConst123));
	dsp->fConst125 = (((dsp->fConst69 + -0.782413065f) / dsp->fConst68) + 0.245291501f);
	dsp->fConst126 = (2.0f * (0.245291501f - dsp->fConst97));
	dsp->fConst127 = (dsp->fConst123 + 0.000433227193f);
	dsp->fConst128 = (((dsp->fConst69 + -0.51247865f) / dsp->fConst68) + 0.689621389f);
	dsp->fConst129 = (2.0f * (0.689621389f - dsp->fConst97));
	dsp->fConst130 = (dsp->fConst97 + 7.62173128f);
	dsp->fConst131 = (((dsp->fConst69 + -0.168404877f) / dsp->fConst68) + 1.06935835f);
	dsp->fConst132 = (2.0f * (1.06935835f - dsp->fConst97));
	dsp->fConst133 = (dsp->fConst97 + 53.5361519f);
	dsp->fConst134 = (((dsp->fConst107 + -3.18972731f) / dsp->fConst106) + 4.07678175f);
	dsp->fConst135 = (1.0f / dsp->fConst109);
	dsp->fConst136 = (2.0f * (4.07678175f - dsp->fConst135));
	dsp->fConst137 = (dsp->fConst116 + 0.000407678192f);
	dsp->fConst138 = (((dsp->fConst107 + -0.743130445f) / dsp->fConst106) + 1.4500711f);
	dsp->fConst139 = (2.0f * (1.4500711f - dsp->fConst135));
	dsp->fConst140 = (dsp->fConst113 + 1.4500711f);
	dsp->fConst141 = (((dsp->fConst107 + -0.157482162f) / dsp->fConst106) + 0.935140193f);
	dsp->fConst142 = (2.0f * (0.935140193f - dsp->fConst135));
	dsp->fConst143 = (dsp->fConst110 + 0.935140193f);
	dsp->fConst144 = tanf((7916.31738f / dsp->fConst0));
	dsp->fConst145 = (1.0f / dsp->fConst144);
	dsp->fConst146 = (1.0f / (((dsp->fConst145 + 0.157482162f) / dsp->fConst144) + 0.935140193f));
	dsp->fConst147 = mydsp_faustpower2_f(dsp->fConst144);
	dsp->fConst148 = (50.0638084f / dsp->fConst147);
	dsp->fConst149 = (2.0f * (0.935140193f - dsp->fConst148));
	dsp->fConst150 = (1.0f / (((dsp->fConst145 + 0.743130445f) / dsp->fConst144) + 1.4500711f));
	dsp->fConst151 = (11.0520525f / dsp->fConst147);
	dsp->fConst152 = (2.0f * (1.4500711f - dsp->fConst151));
	dsp->fConst153 = (1.0f / (((dsp->fConst145 + 3.18972731f) / dsp->fConst144) + 4.07678175f));
	dsp->fConst154 = (0.00176617282f / dsp->fConst147);
	dsp->fConst155 = (2.0f * (0.000407678192f - dsp->fConst154));
	dsp->fConst156 = (1.0f / (((dsp->fConst107 + 0.168404877f) / dsp->fConst106) + 1.06935835f));
	dsp->fConst157 = (2.0f * (53.5361519f - dsp->fConst135));
	dsp->fConst158 = (1.0f / (((dsp->fConst107 + 0.51247865f) / dsp->fConst106) + 0.689621389f));
	dsp->fConst159 = (2.0f * (7.62173128f - dsp->fConst135));
	dsp->fConst160 = (1.0f / (((dsp->fConst107 + 0.782413065f) / dsp->fConst106) + 0.245291501f));
	dsp->fConst161 = (9.99999975e-05f / dsp->fConst109);
	dsp->fConst162 = (2.0f * (0.000433227193f - dsp->fConst161));
	dsp->fConst163 = (((dsp->fConst107 + -0.782413065f) / dsp->fConst106) + 0.245291501f);
	dsp->fConst164 = (2.0f * (0.245291501f - dsp->fConst135));
	dsp->fConst165 = (dsp->fConst161 + 0.000433227193f);
	dsp->fConst166 = (((dsp->fConst107 + -0.51247865f) / dsp->fConst106) + 0.689621389f);
	dsp->fConst167 = (2.0f * (0.689621389f - dsp->fConst135));
	dsp->fConst168 = (dsp->fConst135 + 7.62173128f);
	dsp->fConst169 = (((dsp->fConst107 + -0.168404877f) / dsp->fConst106) + 1.06935835f);
	dsp->fConst170 = (2.0f * (1.06935835f - dsp->fConst135));
	dsp->fConst171 = (dsp->fConst135 + 53.5361519f);
	dsp->fConst172 = (((dsp->fConst145 + -3.18972731f) / dsp->fConst144) + 4.07678175f);
	dsp->fConst173 = (1.0f / dsp->fConst147);
	dsp->fConst174 = (2.0f * (4.07678175f - dsp->fConst173));
	dsp->fConst175 = (dsp->fConst154 + 0.000407678192f);
	dsp->fConst176 = (((dsp->fConst145 + -0.743130445f) / dsp->fConst144) + 1.4500711f);
	dsp->fConst177 = (2.0f * (1.4500711f - dsp->fConst173));
	dsp->fConst178 = (dsp->fConst151 + 1.4500711f);
	dsp->fConst179 = (((dsp->fConst145 + -0.157482162f) / dsp->fConst144) + 0.935140193f);
	dsp->fConst180 = (2.0f * (0.935140193f - dsp->fConst173));
	dsp->fConst181 = (dsp->fConst148 + 0.935140193f);
	dsp->fConst182 = tanf((4986.96729f / dsp->fConst0));
	dsp->fConst183 = (1.0f / dsp->fConst182);
	dsp->fConst184 = (1.0f / (((dsp->fConst183 + 0.157482162f) / dsp->fConst182) + 0.935140193f));
	dsp->fConst185 = mydsp_faustpower2_f(dsp->fConst182);
	dsp->fConst186 = (50.0638084f / dsp->fConst185);
	dsp->fConst187 = (2.0f * (0.935140193f - dsp->fConst186));
	dsp->fConst188 = (1.0f / (((dsp->fConst183 + 0.743130445f) / dsp->fConst182) + 1.4500711f));
	dsp->fConst189 = (11.0520525f / dsp->fConst185);
	dsp->fConst190 = (2.0f * (1.4500711f - dsp->fConst189));
	dsp->fConst191 = (1.0f / (((dsp->fConst183 + 3.18972731f) / dsp->fConst182) + 4.07678175f));
	dsp->fConst192 = (0.00176617282f / dsp->fConst185);
	dsp->fConst193 = (2.0f * (0.000407678192f - dsp->fConst192));
	dsp->fConst194 = (1.0f / (((dsp->fConst145 + 0.168404877f) / dsp->fConst144) + 1.06935835f));
	dsp->fConst195 = (2.0f * (53.5361519f - dsp->fConst173));
	dsp->fConst196 = (1.0f / (((dsp->fConst145 + 0.51247865f) / dsp->fConst144) + 0.689621389f));
	dsp->fConst197 = (2.0f * (7.62173128f - dsp->fConst173));
	dsp->fConst198 = (1.0f / (((dsp->fConst145 + 0.782413065f) / dsp->fConst144) + 0.245291501f));
	dsp->fConst199 = (9.99999975e-05f / dsp->fConst147);
	dsp->fConst200 = (2.0f * (0.000433227193f - dsp->fConst199));
	dsp->fConst201 = (((dsp->fConst145 + -0.782413065f) / dsp->fConst144) + 0.245291501f);
	dsp->fConst202 = (2.0f * (0.245291501f - dsp->fConst173));
	dsp->fConst203 = (dsp->fConst199 + 0.000433227193f);
	dsp->fConst204 = (((dsp->fConst145 + -0.51247865f) / dsp->fConst144) + 0.689621389f);
	dsp->fConst205 = (2.0f * (0.689621389f - dsp->fConst173));
	dsp->fConst206 = (dsp->fConst173 + 7.62173128f);
	dsp->fConst207 = (((dsp->fConst145 + -0.168404877f) / dsp->fConst144) + 1.06935835f);
	dsp->fConst208 = (2.0f * (1.06935835f - dsp->fConst173));
	dsp->fConst209 = (dsp->fConst173 + 53.5361519f);
	dsp->fConst210 = (((dsp->fConst183 + -3.18972731f) / dsp->fConst182) + 4.07678175f);
	dsp->fConst211 = (1.0f / dsp->fConst185);
	dsp->fConst212 = (2.0f * (4.07678175f - dsp->fConst211));
	dsp->fConst213 = (dsp->fConst192 + 0.000407678192f);
	dsp->fConst214 = (((dsp->fConst183 + -0.743130445f) / dsp->fConst182) + 1.4500711f);
	dsp->fConst215 = (2.0f * (1.4500711f - dsp->fConst211));
	dsp->fConst216 = (dsp->fConst189 + 1.4500711f);
	dsp->fConst217 = (((dsp->fConst183 + -0.157482162f) / dsp->fConst182) + 0.935140193f);
	dsp->fConst218 = (2.0f * (0.935140193f - dsp->fConst211));
	dsp->fConst219 = (dsp->fConst186 + 0.935140193f);
	dsp->fConst220 = tanf((3141.59277f / dsp->fConst0));
	dsp->fConst221 = (1.0f / dsp->fConst220);
	dsp->fConst222 = (1.0f / (((dsp->fConst221 + 0.157482162f) / dsp->fConst220) + 0.935140193f));
	dsp->fConst223 = mydsp_faustpower2_f(dsp->fConst220);
	dsp->fConst224 = (50.0638084f / dsp->fConst223);
	dsp->fConst225 = (2.0f * (0.935140193f - dsp->fConst224));
	dsp->fConst226 = (1.0f / (((dsp->fConst221 + 0.743130445f) / dsp->fConst220) + 1.4500711f));
	dsp->fConst227 = (11.0520525f / dsp->fConst223);
	dsp->fConst228 = (2.0f * (1.4500711f - dsp->fConst227));
	dsp->fConst229 = (1.0f / (((dsp->fConst221 + 3.18972731f) / dsp->fConst220) + 4.07678175f));
	dsp->fConst230 = (0.00176617282f / dsp->fConst223);
	dsp->fConst231 = (2.0f * (0.000407678192f - dsp->fConst230));
	dsp->fConst232 = (1.0f / (((dsp->fConst183 + 0.168404877f) / dsp->fConst182) + 1.06935835f));
	dsp->fConst233 = (2.0f * (53.5361519f - dsp->fConst211));
	dsp->fConst234 = (1.0f / (((dsp->fConst183 + 0.51247865f) / dsp->fConst182) + 0.689621389f));
	dsp->fConst235 = (2.0f * (7.62173128f - dsp->fConst211));
	dsp->fConst236 = (1.0f / (((dsp->fConst183 + 0.782413065f) / dsp->fConst182) + 0.245291501f));
	dsp->fConst237 = (9.99999975e-05f / dsp->fConst185);
	dsp->fConst238 = (2.0f * (0.000433227193f - dsp->fConst237));
	dsp->fConst239 = (((dsp->fConst183 + -0.782413065f) / dsp->fConst182) + 0.245291501f);
	dsp->fConst240 = (2.0f * (0.245291501f - dsp->fConst211));
	dsp->fConst241 = (dsp->fConst237 + 0.000433227193f);
	dsp->fConst242 = (((dsp->fConst183 + -0.51247865f) / dsp->fConst182) + 0.689621389f);
	dsp->fConst243 = (2.0f * (0.689621389f - dsp->fConst211));
	dsp->fConst244 = (dsp->fConst211 + 7.62173128f);
	dsp->fConst245 = (((dsp->fConst183 + -0.168404877f) / dsp->fConst182) + 1.06935835f);
	dsp->fConst246 = (2.0f * (1.06935835f - dsp->fConst211));
	dsp->fConst247 = (dsp->fConst211 + 53.5361519f);
	dsp->fConst248 = (((dsp->fConst221 + -3.18972731f) / dsp->fConst220) + 4.07678175f);
	dsp->fConst249 = (1.0f / dsp->fConst223);
	dsp->fConst250 = (2.0f * (4.07678175f - dsp->fConst249));
	dsp->fConst251 = (dsp->fConst230 + 0.000407678192f);
	dsp->fConst252 = (((dsp->fConst221 + -0.743130445f) / dsp->fConst220) + 1.4500711f);
	dsp->fConst253 = (2.0f * (1.4500711f - dsp->fConst249));
	dsp->fConst254 = (dsp->fConst227 + 1.4500711f);
	dsp->fConst255 = (((dsp->fConst221 + -0.157482162f) / dsp->fConst220) + 0.935140193f);
	dsp->fConst256 = (2.0f * (0.935140193f - dsp->fConst249));
	dsp->fConst257 = (dsp->fConst224 + 0.935140193f);
	dsp->fConst258 = tanf((1979.07935f / dsp->fConst0));
	dsp->fConst259 = (1.0f / dsp->fConst258);
	dsp->fConst260 = (1.0f / (((dsp->fConst259 + 0.157482162f) / dsp->fConst258) + 0.935140193f));
	dsp->fConst261 = mydsp_faustpower2_f(dsp->fConst258);
	dsp->fConst262 = (50.0638084f / dsp->fConst261);
	dsp->fConst263 = (2.0f * (0.935140193f - dsp->fConst262));
	dsp->fConst264 = (1.0f / (((dsp->fConst259 + 0.743130445f) / dsp->fConst258) + 1.4500711f));
	dsp->fConst265 = (11.0520525f / dsp->fConst261);
	dsp->fConst266 = (2.0f * (1.4500711f - dsp->fConst265));
	dsp->fConst267 = (1.0f / (((dsp->fConst259 + 3.18972731f) / dsp->fConst258) + 4.07678175f));
	dsp->fConst268 = (0.00176617282f / dsp->fConst261);
	dsp->fConst269 = (2.0f * (0.000407678192f - dsp->fConst268));
	dsp->fConst270 = (1.0f / (((dsp->fConst221 + 0.168404877f) / dsp->fConst220) + 1.06935835f));
	dsp->fConst271 = (2.0f * (53.5361519f - dsp->fConst249));
	dsp->fConst272 = (1.0f / (((dsp->fConst221 + 0.51247865f) / dsp->fConst220) + 0.689621389f));
	dsp->fConst273 = (2.0f * (7.62173128f - dsp->fConst249));
	dsp->fConst274 = (1.0f / (((dsp->fConst221 + 0.782413065f) / dsp->fConst220) + 0.245291501f));
	dsp->fConst275 = (9.99999975e-05f / dsp->fConst223);
	dsp->fConst276 = (2.0f * (0.000433227193f - dsp->fConst275));
	dsp->fConst277 = (((dsp->fConst221 + -0.782413065f) / dsp->fConst220) + 0.245291501f);
	dsp->fConst278 = (2.0f * (0.245291501f - dsp->fConst249));
	dsp->fConst279 = (dsp->fConst275 + 0.000433227193f);
	dsp->fConst280 = (((dsp->fConst221 + -0.51247865f) / dsp->fConst220) + 0.689621389f);
	dsp->fConst281 = (2.0f * (0.689621389f - dsp->fConst249));
	dsp->fConst282 = (dsp->fConst249 + 7.62173128f);
	dsp->fConst283 = (((dsp->fConst221 + -0.168404877f) / dsp->fConst220) + 1.06935835f);
	dsp->fConst284 = (2.0f * (1.06935835f - dsp->fConst249));
	dsp->fConst285 = (dsp->fConst249 + 53.5361519f);
	dsp->fConst286 = (((dsp->fConst259 + -3.18972731f) / dsp->fConst258) + 4.07678175f);
	dsp->fConst287 = (1.0f / dsp->fConst261);
	dsp->fConst288 = (2.0f * (4.07678175f - dsp->fConst287));
	dsp->fConst289 = (dsp->fConst268 + 0.000407678192f);
	dsp->fConst290 = (((dsp->fConst259 + -0.743130445f) / dsp->fConst258) + 1.4500711f);
	dsp->fConst291 = (2.0f * (1.4500711f - dsp->fConst287));
	dsp->fConst292 = (dsp->fConst265 + 1.4500711f);
	dsp->fConst293 = (((dsp->fConst259 + -0.157482162f) / dsp->fConst258) + 0.935140193f);
	dsp->fConst294 = (2.0f * (0.935140193f - dsp->fConst287));
	dsp->fConst295 = (dsp->fConst262 + 0.935140193f);
	dsp->fConst296 = tanf((1246.74182f / dsp->fConst0));
	dsp->fConst297 = (1.0f / dsp->fConst296);
	dsp->fConst298 = (1.0f / (((dsp->fConst297 + 0.157482162f) / dsp->fConst296) + 0.935140193f));
	dsp->fConst299 = mydsp_faustpower2_f(dsp->fConst296);
	dsp->fConst300 = (50.0638084f / dsp->fConst299);
	dsp->fConst301 = (2.0f * (0.935140193f - dsp->fConst300));
	dsp->fConst302 = (1.0f / (((dsp->fConst297 + 0.743130445f) / dsp->fConst296) + 1.4500711f));
	dsp->fConst303 = (11.0520525f / dsp->fConst299);
	dsp->fConst304 = (2.0f * (1.4500711f - dsp->fConst303));
	dsp->fConst305 = (1.0f / (((dsp->fConst297 + 3.18972731f) / dsp->fConst296) + 4.07678175f));
	dsp->fConst306 = (0.00176617282f / dsp->fConst299);
	dsp->fConst307 = (2.0f * (0.000407678192f - dsp->fConst306));
	dsp->fConst308 = (1.0f / (((dsp->fConst259 + 0.168404877f) / dsp->fConst258) + 1.06935835f));
	dsp->fConst309 = (2.0f * (53.5361519f - dsp->fConst287));
	dsp->fConst310 = (1.0f / (((dsp->fConst259 + 0.51247865f) / dsp->fConst258) + 0.689621389f));
	dsp->fConst311 = (2.0f * (7.62173128f - dsp->fConst287));
	dsp->fConst312 = (1.0f / (((dsp->fConst259 + 0.782413065f) / dsp->fConst258) + 0.245291501f));
	dsp->fConst313 = (9.99999975e-05f / dsp->fConst261);
	dsp->fConst314 = (2.0f * (0.000433227193f - dsp->fConst313));
	dsp->fConst315 = (((dsp->fConst259 + -0.782413065f) / dsp->fConst258) + 0.245291501f);
	dsp->fConst316 = (2.0f * (0.245291501f - dsp->fConst287));
	dsp->fConst317 = (dsp->fConst313 + 0.000433227193f);
	dsp->fConst318 = (((dsp->fConst259 + -0.51247865f) / dsp->fConst258) + 0.689621389f);
	dsp->fConst319 = (2.0f * (0.689621389f - dsp->fConst287));
	dsp->fConst320 = (dsp->fConst287 + 7.62173128f);
	dsp->fConst321 = (((dsp->fConst259 + -0.168404877f) / dsp->fConst258) + 1.06935835f);
	dsp->fConst322 = (2.0f * (1.06935835f - dsp->fConst287));
	dsp->fConst323 = (dsp->fConst287 + 53.5361519f);
	dsp->fConst324 = (((dsp->fConst297 + -3.18972731f) / dsp->fConst296) + 4.07678175f);
	dsp->fConst325 = (1.0f / dsp->fConst299);
	dsp->fConst326 = (2.0f * (4.07678175f - dsp->fConst325));
	dsp->fConst327 = (dsp->fConst306 + 0.000407678192f);
	dsp->fConst328 = (((dsp->fConst297 + -0.743130445f) / dsp->fConst296) + 1.4500711f);
	dsp->fConst329 = (2.0f * (1.4500711f - dsp->fConst325));
	dsp->fConst330 = (dsp->fConst303 + 1.4500711f);
	dsp->fConst331 = (((dsp->fConst297 + -0.157482162f) / dsp->fConst296) + 0.935140193f);
	dsp->fConst332 = (2.0f * (0.935140193f - dsp->fConst325));
	dsp->fConst333 = (dsp->fConst300 + 0.935140193f);
	dsp->fConst334 = tanf((785.398193f / dsp->fConst0));
	dsp->fConst335 = (1.0f / dsp->fConst334);
	dsp->fConst336 = (1.0f / (((dsp->fConst335 + 0.157482162f) / dsp->fConst334) + 0.935140193f));
	dsp->fConst337 = mydsp_faustpower2_f(dsp->fConst334);
	dsp->fConst338 = (50.0638084f / dsp->fConst337);
	dsp->fConst339 = (2.0f * (0.935140193f - dsp->fConst338));
	dsp->fConst340 = (1.0f / (((dsp->fConst335 + 0.743130445f) / dsp->fConst334) + 1.4500711f));
	dsp->fConst341 = (11.0520525f / dsp->fConst337);
	dsp->fConst342 = (2.0f * (1.4500711f - dsp->fConst341));
	dsp->fConst343 = (1.0f / (((dsp->fConst335 + 3.18972731f) / dsp->fConst334) + 4.07678175f));
	dsp->fConst344 = (0.00176617282f / dsp->fConst337);
	dsp->fConst345 = (2.0f * (0.000407678192f - dsp->fConst344));
	dsp->fConst346 = (1.0f / (((dsp->fConst297 + 0.168404877f) / dsp->fConst296) + 1.06935835f));
	dsp->fConst347 = (2.0f * (53.5361519f - dsp->fConst325));
	dsp->fConst348 = (1.0f / (((dsp->fConst297 + 0.51247865f) / dsp->fConst296) + 0.689621389f));
	dsp->fConst349 = (2.0f * (7.62173128f - dsp->fConst325));
	dsp->fConst350 = (1.0f / (((dsp->fConst297 + 0.782413065f) / dsp->fConst296) + 0.245291501f));
	dsp->fConst351 = (9.99999975e-05f / dsp->fConst299);
	dsp->fConst352 = (2.0f * (0.000433227193f - dsp->fConst351));
	dsp->fConst353 = (((dsp->fConst297 + -0.782413065f) / dsp->fConst296) + 0.245291501f);
	dsp->fConst354 = (2.0f * (0.245291501f - dsp->fConst325));
	dsp->fConst355 = (dsp->fConst351 + 0.000433227193f);
	dsp->fConst356 = (((dsp->fConst297 + -0.51247865f) / dsp->fConst296) + 0.689621389f);
	dsp->fConst357 = (2.0f * (0.689621389f - dsp->fConst325));
	dsp->fConst358 = (dsp->fConst325 + 7.62173128f);
	dsp->fConst359 = (((dsp->fConst297 + -0.168404877f) / dsp->fConst296) + 1.06935835f);
	dsp->fConst360 = (2.0f * (1.06935835f - dsp->fConst325));
	dsp->fConst361 = (dsp->fConst325 + 53.5361519f);
	dsp->fConst362 = (((dsp->fConst335 + -3.18972731f) / dsp->fConst334) + 4.07678175f);
	dsp->fConst363 = (1.0f / dsp->fConst337);
	dsp->fConst364 = (2.0f * (4.07678175f - dsp->fConst363));
	dsp->fConst365 = (dsp->fConst344 + 0.000407678192f);
	dsp->fConst366 = (((dsp->fConst335 + -0.743130445f) / dsp->fConst334) + 1.4500711f);
	dsp->fConst367 = (2.0f * (1.4500711f - dsp->fConst363));
	dsp->fConst368 = (dsp->fConst341 + 1.4500711f);
	dsp->fConst369 = (((dsp->fConst335 + -0.157482162f) / dsp->fConst334) + 0.935140193f);
	dsp->fConst370 = (2.0f * (0.935140193f - dsp->fConst363));
	dsp->fConst371 = (dsp->fConst338 + 0.935140193f);
	dsp->fConst372 = tanf((494.769836f / dsp->fConst0));
	dsp->fConst373 = (1.0f / dsp->fConst372);
	dsp->fConst374 = (1.0f / (((dsp->fConst373 + 0.157482162f) / dsp->fConst372) + 0.935140193f));
	dsp->fConst375 = mydsp_faustpower2_f(dsp->fConst372);
	dsp->fConst376 = (50.0638084f / dsp->fConst375);
	dsp->fConst377 = (2.0f * (0.935140193f - dsp->fConst376));
	dsp->fConst378 = (1.0f / (((dsp->fConst373 + 0.743130445f) / dsp->fConst372) + 1.4500711f));
	dsp->fConst379 = (11.0520525f / dsp->fConst375);
	dsp->fConst380 = (2.0f * (1.4500711f - dsp->fConst379));
	dsp->fConst381 = (1.0f / (((dsp->fConst373 + 3.18972731f) / dsp->fConst372) + 4.07678175f));
	dsp->fConst382 = (0.00176617282f / dsp->fConst375);
	dsp->fConst383 = (2.0f * (0.000407678192f - dsp->fConst382));
	dsp->fConst384 = (1.0f / (((dsp->fConst335 + 0.168404877f) / dsp->fConst334) + 1.06935835f));
	dsp->fConst385 = (2.0f * (53.5361519f - dsp->fConst363));
	dsp->fConst386 = (1.0f / (((dsp->fConst335 + 0.51247865f) / dsp->fConst334) + 0.689621389f));
	dsp->fConst387 = (2.0f * (7.62173128f - dsp->fConst363));
	dsp->fConst388 = (1.0f / (((dsp->fConst335 + 0.782413065f) / dsp->fConst334) + 0.245291501f));
	dsp->fConst389 = (9.99999975e-05f / dsp->fConst337);
	dsp->fConst390 = (2.0f * (0.000433227193f - dsp->fConst389));
	dsp->fConst391 = (((dsp->fConst335 + -0.782413065f) / dsp->fConst334) + 0.245291501f);
	dsp->fConst392 = (2.0f * (0.245291501f - dsp->fConst363));
	dsp->fConst393 = (dsp->fConst389 + 0.000433227193f);
	dsp->fConst394 = (((dsp->fConst335 + -0.51247865f) / dsp->fConst334) + 0.689621389f);
	dsp->fConst395 = (2.0f * (0.689621389f - dsp->fConst363));
	dsp->fConst396 = (dsp->fConst363 + 7.62173128f);
	dsp->fConst397 = (((dsp->fConst335 + -0.168404877f) / dsp->fConst334) + 1.06935835f);
	dsp->fConst398 = (2.0f * (1.06935835f - dsp->fConst363));
	dsp->fConst399 = (dsp->fConst363 + 53.5361519f);
	dsp->fConst400 = (((dsp->fConst373 + -3.18972731f) / dsp->fConst372) + 4.07678175f);
	dsp->fConst401 = (1.0f / dsp->fConst375);
	dsp->fConst402 = (2.0f * (4.07678175f - dsp->fConst401));
	dsp->fConst403 = (dsp->fConst382 + 0.000407678192f);
	dsp->fConst404 = (((dsp->fConst373 + -0.743130445f) / dsp->fConst372) + 1.4500711f);
	dsp->fConst405 = (2.0f * (1.4500711f - dsp->fConst401));
	dsp->fConst406 = (dsp->fConst379 + 1.4500711f);
	dsp->fConst407 = (((dsp->fConst373 + -0.157482162f) / dsp->fConst372) + 0.935140193f);
	dsp->fConst408 = (2.0f * (0.935140193f - dsp->fConst401));
	dsp->fConst409 = (dsp->fConst376 + 0.935140193f);
	dsp->fConst410 = tanf((311.685455f / dsp->fConst0));
	dsp->fConst411 = (1.0f / dsp->fConst410);
	dsp->fConst412 = (1.0f / (((dsp->fConst411 + 0.157482162f) / dsp->fConst410) + 0.935140193f));
	dsp->fConst413 = mydsp_faustpower2_f(dsp->fConst410);
	dsp->fConst414 = (50.0638084f / dsp->fConst413);
	dsp->fConst415 = (2.0f * (0.935140193f - dsp->fConst414));
	dsp->fConst416 = (1.0f / (((dsp->fConst411 + 0.743130445f) / dsp->fConst410) + 1.4500711f));
	dsp->fConst417 = (11.0520525f / dsp->fConst413);
	dsp->fConst418 = (2.0f * (1.4500711f - dsp->fConst417));
	dsp->fConst419 = (1.0f / (((dsp->fConst411 + 3.18972731f) / dsp->fConst410) + 4.07678175f));
	dsp->fConst420 = (0.00176617282f / dsp->fConst413);
	dsp->fConst421 = (2.0f * (0.000407678192f - dsp->fConst420));
	dsp->fConst422 = (1.0f / (((dsp->fConst373 + 0.168404877f) / dsp->fConst372) + 1.06935835f));
	dsp->fConst423 = (2.0f * (53.5361519f - dsp->fConst401));
	dsp->fConst424 = (1.0f / (((dsp->fConst373 + 0.51247865f) / dsp->fConst372) + 0.689621389f));
	dsp->fConst425 = (2.0f * (7.62173128f - dsp->fConst401));
	dsp->fConst426 = (1.0f / (((dsp->fConst373 + 0.782413065f) / dsp->fConst372) + 0.245291501f));
	dsp->fConst427 = (9.99999975e-05f / dsp->fConst375);
	dsp->fConst428 = (2.0f * (0.000433227193f - dsp->fConst427));
	dsp->fConst429 = (((dsp->fConst373 + -0.782413065f) / dsp->fConst372) + 0.245291501f);
	dsp->fConst430 = (2.0f * (0.245291501f - dsp->fConst401));
	dsp->fConst431 = (dsp->fConst427 + 0.000433227193f);
	dsp->fConst432 = (((dsp->fConst373 + -0.51247865f) / dsp->fConst372) + 0.689621389f);
	dsp->fConst433 = (2.0f * (0.689621389f - dsp->fConst401));
	dsp->fConst434 = (dsp->fConst401 + 7.62173128f);
	dsp->fConst435 = (((dsp->fConst373 + -0.168404877f) / dsp->fConst372) + 1.06935835f);
	dsp->fConst436 = (2.0f * (1.06935835f - dsp->fConst401));
	dsp->fConst437 = (dsp->fConst401 + 53.5361519f);
	dsp->fConst438 = (((dsp->fConst411 + -3.18972731f) / dsp->fConst410) + 4.07678175f);
	dsp->fConst439 = (1.0f / dsp->fConst413);
	dsp->fConst440 = (2.0f * (4.07678175f - dsp->fConst439));
	dsp->fConst441 = (dsp->fConst420 + 0.000407678192f);
	dsp->fConst442 = (((dsp->fConst411 + -0.743130445f) / dsp->fConst410) + 1.4500711f);
	dsp->fConst443 = (2.0f * (1.4500711f - dsp->fConst439));
	dsp->fConst444 = (dsp->fConst417 + 1.4500711f);
	dsp->fConst445 = (((dsp->fConst411 + -0.157482162f) / dsp->fConst410) + 0.935140193f);
	dsp->fConst446 = (2.0f * (0.935140193f - dsp->fConst439));
	dsp->fConst447 = (dsp->fConst414 + 0.935140193f);
	dsp->fConst448 = tanf((196.349548f / dsp->fConst0));
	dsp->fConst449 = (1.0f / dsp->fConst448);
	dsp->fConst450 = (1.0f / (((dsp->fConst449 + 0.157482162f) / dsp->fConst448) + 0.935140193f));
	dsp->fConst451 = mydsp_faustpower2_f(dsp->fConst448);
	dsp->fConst452 = (50.0638084f / dsp->fConst451);
	dsp->fConst453 = (2.0f * (0.935140193f - dsp->fConst452));
	dsp->fConst454 = (1.0f / (((dsp->fConst449 + 0.743130445f) / dsp->fConst448) + 1.4500711f));
	dsp->fConst455 = (11.0520525f / dsp->fConst451);
	dsp->fConst456 = (2.0f * (1.4500711f - dsp->fConst455));
	dsp->fConst457 = (1.0f / (((dsp->fConst449 + 3.18972731f) / dsp->fConst448) + 4.07678175f));
	dsp->fConst458 = (0.00176617282f / dsp->fConst451);
	dsp->fConst459 = (2.0f * (0.000407678192f - dsp->fConst458));
	dsp->fConst460 = (1.0f / (((dsp->fConst411 + 0.168404877f) / dsp->fConst410) + 1.06935835f));
	dsp->fConst461 = (2.0f * (53.5361519f - dsp->fConst439));
	dsp->fConst462 = (1.0f / (((dsp->fConst411 + 0.51247865f) / dsp->fConst410) + 0.689621389f));
	dsp->fConst463 = (2.0f * (7.62173128f - dsp->fConst439));
	dsp->fConst464 = (1.0f / (((dsp->fConst411 + 0.782413065f) / dsp->fConst410) + 0.245291501f));
	dsp->fConst465 = (9.99999975e-05f / dsp->fConst413);
	dsp->fConst466 = (2.0f * (0.000433227193f - dsp->fConst465));
	dsp->fConst467 = (((dsp->fConst411 + -0.782413065f) / dsp->fConst410) + 0.245291501f);
	dsp->fConst468 = (2.0f * (0.245291501f - dsp->fConst439));
	dsp->fConst469 = (dsp->fConst465 + 0.000433227193f);
	dsp->fConst470 = (((dsp->fConst411 + -0.51247865f) / dsp->fConst410) + 0.689621389f);
	dsp->fConst471 = (2.0f * (0.689621389f - dsp->fConst439));
	dsp->fConst472 = (dsp->fConst439 + 7.62173128f);
	dsp->fConst473 = (((dsp->fConst411 + -0.168404877f) / dsp->fConst410) + 1.06935835f);
	dsp->fConst474 = (2.0f * (1.06935835f - dsp->fConst439));
	dsp->fConst475 = (dsp->fConst439 + 53.5361519f);
	dsp->fConst476 = (((dsp->fConst449 + -3.18972731f) / dsp->fConst448) + 4.07678175f);
	dsp->fConst477 = (1.0f / dsp->fConst451);
	dsp->fConst478 = (2.0f * (4.07678175f - dsp->fConst477));
	dsp->fConst479 = (dsp->fConst458 + 0.000407678192f);
	dsp->fConst480 = (((dsp->fConst449 + -0.743130445f) / dsp->fConst448) + 1.4500711f);
	dsp->fConst481 = (2.0f * (1.4500711f - dsp->fConst477));
	dsp->fConst482 = (dsp->fConst455 + 1.4500711f);
	dsp->fConst483 = (((dsp->fConst449 + -0.157482162f) / dsp->fConst448) + 0.935140193f);
	dsp->fConst484 = (2.0f * (0.935140193f - dsp->fConst477));
	dsp->fConst485 = (dsp->fConst452 + 0.935140193f);
	dsp->fConst486 = tanf((123.692459f / dsp->fConst0));
	dsp->fConst487 = (1.0f / dsp->fConst486);
	dsp->fConst488 = (1.0f / (((dsp->fConst487 + 0.157482162f) / dsp->fConst486) + 0.935140193f));
	dsp->fConst489 = mydsp_faustpower2_f(dsp->fConst486);
	dsp->fConst490 = (50.0638084f / dsp->fConst489);
	dsp->fConst491 = (2.0f * (0.935140193f - dsp->fConst490));
	dsp->fConst492 = (1.0f / (((dsp->fConst487 + 0.743130445f) / dsp->fConst486) + 1.4500711f));
	dsp->fConst493 = (11.0520525f / dsp->fConst489);
	dsp->fConst494 = (2.0f * (1.4500711f - dsp->fConst493));
	dsp->fConst495 = (1.0f / (((dsp->fConst487 + 3.18972731f) / dsp->fConst486) + 4.07678175f));
	dsp->fConst496 = (0.00176617282f / dsp->fConst489);
	dsp->fConst497 = (2.0f * (0.000407678192f - dsp->fConst496));
	dsp->fConst498 = (1.0f / (((dsp->fConst449 + 0.168404877f) / dsp->fConst448) + 1.06935835f));
	dsp->fConst499 = (2.0f * (53.5361519f - dsp->fConst477));
	dsp->fConst500 = (1.0f / (((dsp->fConst449 + 0.51247865f) / dsp->fConst448) + 0.689621389f));
	dsp->fConst501 = (2.0f * (7.62173128f - dsp->fConst477));
	dsp->fConst502 = (1.0f / (((dsp->fConst449 + 0.782413065f) / dsp->fConst448) + 0.245291501f));
	dsp->fConst503 = (9.99999975e-05f / dsp->fConst451);
	dsp->fConst504 = (2.0f * (0.000433227193f - dsp->fConst503));
	dsp->fConst505 = (((dsp->fConst449 + -0.782413065f) / dsp->fConst448) + 0.245291501f);
	dsp->fConst506 = (2.0f * (0.245291501f - dsp->fConst477));
	dsp->fConst507 = (dsp->fConst503 + 0.000433227193f);
	dsp->fConst508 = (((dsp->fConst449 + -0.51247865f) / dsp->fConst448) + 0.689621389f);
	dsp->fConst509 = (2.0f * (0.689621389f - dsp->fConst477));
	dsp->fConst510 = (dsp->fConst477 + 7.62173128f);
	dsp->fConst511 = (((dsp->fConst449 + -0.168404877f) / dsp->fConst448) + 1.06935835f);
	dsp->fConst512 = (2.0f * (1.06935835f - dsp->fConst477));
	dsp->fConst513 = (dsp->fConst477 + 53.5361519f);
	dsp->fConst514 = (((dsp->fConst487 + -3.18972731f) / dsp->fConst486) + 4.07678175f);
	dsp->fConst515 = (1.0f / dsp->fConst489);
	dsp->fConst516 = (2.0f * (4.07678175f - dsp->fConst515));
	dsp->fConst517 = (dsp->fConst496 + 0.000407678192f);
	dsp->fConst518 = (((dsp->fConst487 + -0.743130445f) / dsp->fConst486) + 1.4500711f);
	dsp->fConst519 = (2.0f * (1.4500711f - dsp->fConst515));
	dsp->fConst520 = (dsp->fConst493 + 1.4500711f);
	dsp->fConst521 = (((dsp->fConst487 + -0.157482162f) / dsp->fConst486) + 0.935140193f);
	dsp->fConst522 = (2.0f * (0.935140193f - dsp->fConst515));
	dsp->fConst523 = (dsp->fConst490 + 0.935140193f);
	dsp->fConst524 = (1.0f / (((dsp->fConst487 + 0.168404877f) / dsp->fConst486) + 1.06935835f));
	dsp->fConst525 = (2.0f * (53.5361519f - dsp->fConst515));
	dsp->fConst526 = (1.0f / (((dsp->fConst487 + 0.51247865f) / dsp->fConst486) + 0.689621389f));
	dsp->fConst527 = (2.0f * (7.62173128f - dsp->fConst515));
	dsp->fConst528 = (1.0f / (((dsp->fConst487 + 0.782413065f) / dsp->fConst486) + 0.245291501f));
	dsp->fConst529 = (9.99999975e-05f / dsp->fConst489);
	dsp->fConst530 = (2.0f * (0.000433227193f - dsp->fConst529));
	dsp->fConst531 = (((dsp->fConst487 + -0.782413065f) / dsp->fConst486) + 0.245291501f);
	dsp->fConst532 = (2.0f * (0.245291501f - dsp->fConst515));
	dsp->fConst533 = (dsp->fConst529 + 0.000433227193f);
	dsp->fConst534 = (((dsp->fConst487 + -0.51247865f) / dsp->fConst486) + 0.689621389f);
	dsp->fConst535 = (2.0f * (0.689621389f - dsp->fConst515));
	dsp->fConst536 = (dsp->fConst515 + 7.62173128f);
	dsp->fConst537 = (((dsp->fConst487 + -0.168404877f) / dsp->fConst486) + 1.06935835f);
	dsp->fConst538 = (2.0f * (1.06935835f - dsp->fConst515));
	dsp->fConst539 = (dsp->fConst515 + 53.5361519f);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "spectralTiltLab");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Spectral Tilt Filter");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "1", "");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Slope of Spectral Tilt across Band", &dsp->fHslider4, -0.5f, -1.0f, 1.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Spectral Tilt Filter");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass Spectral Tilt", &dsp->fCheckbox0);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band Start Frequency", &dsp->fHslider2, 100.0f, 20.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Band Width", &dsp->fHslider3, 5000.0f, 100.0f, 10000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's oscillator.lib for sawtooth_demo");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Test Signal");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "SAWTOOTH OSCILLATOR");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "Sawtooth   waveform amplitude");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Amplitude", &dsp->fVslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "PK");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Frequency", &dsp->fVslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "unit", "%%");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Detuning 1", &dsp->fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider4, "unit", "%%");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Detuning 2", &dsp->fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider2, "unit", "sec");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Portamento", &dsp->fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "tooltip", "Order of sawtootn aliasing   suppression");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Saw Order", &dsp->fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "7", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Alternate Signals");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "0", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Noise (White or Pink - uses only Amplitude control on   the left)", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink instead of White Noise (also called 1/f Noise)", &dsp->fCheckbox3);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "External Signal Input (overrides Sawtooth/Noise   selection above)", &dsp->fCheckbox1);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for spectral_level_demo");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Spectrum Analyzer");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746eaa8d0", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746e98f70", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746e76e20", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746e54cd0", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746e32b80", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746e10a30", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746dea960", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746dc8810", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746da66c0", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746d84570", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746d62420", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746d402d0", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746d1e180", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746cf80b0", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fc746cd4ed0", &dsp->fVbargraph0, -50.0f, 10.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "SPECTRUM ANALYZER CONTROLS");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "tooltip", "band-level averaging time in milliseconds");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider1, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Level Averaging Time", &dsp->fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "tooltip", "Level offset in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider0, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Level dB Offset", &dsp->fHslider0, 50.0f, -50.0f, 100.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = expf((0.0f - (dsp->fConst1 / (float)dsp->fHslider1)));
	float fSlow2 = (1.0f - fSlow1);
	int iSlow3 = (int)(float)dsp->fCheckbox0;
	float fSlow4 = (float)dsp->fHslider2;
	float fSlow5 = powf(((fSlow4 + (float)dsp->fHslider3) / fSlow4), 0.111111112f);
	float fSlow6 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower9_f(fSlow5))));
	float fSlow7 = (float)dsp->fHslider4;
	float fSlow8 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (9.0f - fSlow7)))));
	float fSlow9 = (fSlow6 / fSlow8);
	float fSlow10 = tanf((dsp->fConst14 * fSlow4));
	float fSlow11 = (6.28318548f * ((fSlow4 * fSlow6) / fSlow10));
	float fSlow12 = (dsp->fConst15 + fSlow11);
	float fSlow13 = (0.0f - ((fSlow11 - dsp->fConst15) / fSlow12));
	float fSlow14 = (1.0f / fSlow12);
	float fSlow15 = (6.28318548f * ((fSlow4 * fSlow8) / fSlow10));
	float fSlow16 = (fSlow15 - dsp->fConst15);
	float fSlow17 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower8_f(fSlow5))));
	float fSlow18 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (8.0f - fSlow7)))));
	float fSlow19 = (fSlow17 / fSlow18);
	float fSlow20 = (6.28318548f * ((fSlow4 * fSlow17) / fSlow10));
	float fSlow21 = (dsp->fConst15 + fSlow20);
	float fSlow22 = (0.0f - ((fSlow20 - dsp->fConst15) / fSlow21));
	float fSlow23 = (1.0f / fSlow21);
	float fSlow24 = (6.28318548f * ((fSlow4 * fSlow18) / fSlow10));
	float fSlow25 = (fSlow24 - dsp->fConst15);
	float fSlow26 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower7_f(fSlow5))));
	float fSlow27 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (7.0f - fSlow7)))));
	float fSlow28 = (fSlow26 / fSlow27);
	float fSlow29 = (6.28318548f * ((fSlow4 * fSlow26) / fSlow10));
	float fSlow30 = (dsp->fConst15 + fSlow29);
	float fSlow31 = (0.0f - ((fSlow29 - dsp->fConst15) / fSlow30));
	float fSlow32 = (1.0f / fSlow30);
	float fSlow33 = (6.28318548f * ((fSlow4 * fSlow27) / fSlow10));
	float fSlow34 = (fSlow33 - dsp->fConst15);
	float fSlow35 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower6_f(fSlow5))));
	float fSlow36 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (6.0f - fSlow7)))));
	float fSlow37 = (fSlow35 / fSlow36);
	float fSlow38 = (6.28318548f * ((fSlow4 * fSlow35) / fSlow10));
	float fSlow39 = (dsp->fConst15 + fSlow38);
	float fSlow40 = (0.0f - ((fSlow38 - dsp->fConst15) / fSlow39));
	float fSlow41 = (1.0f / fSlow39);
	float fSlow42 = (6.28318548f * ((fSlow4 * fSlow36) / fSlow10));
	float fSlow43 = (fSlow42 - dsp->fConst15);
	float fSlow44 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower5_f(fSlow5))));
	float fSlow45 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (5.0f - fSlow7)))));
	float fSlow46 = (fSlow44 / fSlow45);
	float fSlow47 = (6.28318548f * ((fSlow4 * fSlow44) / fSlow10));
	float fSlow48 = (dsp->fConst15 + fSlow47);
	float fSlow49 = (0.0f - ((fSlow47 - dsp->fConst15) / fSlow48));
	float fSlow50 = (1.0f / fSlow48);
	float fSlow51 = (6.28318548f * ((fSlow4 * fSlow45) / fSlow10));
	float fSlow52 = (fSlow51 - dsp->fConst15);
	float fSlow53 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower4_f(fSlow5))));
	float fSlow54 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (4.0f - fSlow7)))));
	float fSlow55 = (fSlow53 / fSlow54);
	float fSlow56 = (6.28318548f * ((fSlow4 * fSlow53) / fSlow10));
	float fSlow57 = (dsp->fConst15 + fSlow56);
	float fSlow58 = (0.0f - ((fSlow56 - dsp->fConst15) / fSlow57));
	float fSlow59 = (1.0f / fSlow57);
	float fSlow60 = (6.28318548f * ((fSlow4 * fSlow54) / fSlow10));
	float fSlow61 = (fSlow60 - dsp->fConst15);
	float fSlow62 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower3_f(fSlow5))));
	float fSlow63 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (3.0f - fSlow7)))));
	float fSlow64 = (fSlow62 / fSlow63);
	float fSlow65 = (6.28318548f * ((fSlow4 * fSlow62) / fSlow10));
	float fSlow66 = (dsp->fConst15 + fSlow65);
	float fSlow67 = (0.0f - ((fSlow65 - dsp->fConst15) / fSlow66));
	float fSlow68 = (1.0f / fSlow66);
	float fSlow69 = (6.28318548f * ((fSlow4 * fSlow63) / fSlow10));
	float fSlow70 = (fSlow69 - dsp->fConst15);
	float fSlow71 = tanf((dsp->fConst14 * (fSlow4 * mydsp_faustpower2_f(fSlow5))));
	float fSlow72 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (2.0f - fSlow7)))));
	float fSlow73 = (fSlow71 / fSlow72);
	float fSlow74 = (6.28318548f * ((fSlow4 * fSlow71) / fSlow10));
	float fSlow75 = (dsp->fConst15 + fSlow74);
	float fSlow76 = (0.0f - ((fSlow74 - dsp->fConst15) / fSlow75));
	float fSlow77 = (1.0f / fSlow75);
	float fSlow78 = (6.28318548f * ((fSlow4 * fSlow72) / fSlow10));
	float fSlow79 = (fSlow78 - dsp->fConst15);
	float fSlow80 = tanf((dsp->fConst14 * (fSlow4 * fSlow5)));
	float fSlow81 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (1.0f - fSlow7)))));
	float fSlow82 = (fSlow80 / fSlow81);
	float fSlow83 = (6.28318548f * ((fSlow4 * fSlow80) / fSlow10));
	float fSlow84 = (dsp->fConst15 + fSlow83);
	float fSlow85 = (0.0f - ((fSlow83 - dsp->fConst15) / fSlow84));
	float fSlow86 = (1.0f / fSlow84);
	float fSlow87 = (6.28318548f * ((fSlow4 * fSlow81) / fSlow10));
	float fSlow88 = (fSlow87 - dsp->fConst15);
	float fSlow89 = tanf((dsp->fConst14 * (fSlow4 * powf(fSlow5, (0.0f - fSlow7)))));
	float fSlow90 = (fSlow10 / fSlow89);
	float fSlow91 = (6.28318548f * fSlow4);
	float fSlow92 = (dsp->fConst15 + fSlow91);
	float fSlow93 = (0.0f - ((fSlow91 - dsp->fConst15) / fSlow92));
	float fSlow94 = (1.0f / fSlow92);
	float fSlow95 = (6.28318548f * ((fSlow4 * fSlow89) / fSlow10));
	float fSlow96 = (dsp->fConst15 + fSlow95);
	float fSlow97 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	int iSlow98 = (int)(float)dsp->fCheckbox1;
	int iSlow99 = (int)(float)dsp->fCheckbox2;
	int iSlow100 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow101 = (iSlow100 >= 2);
	int iSlow102 = (iSlow100 >= 1);
	float fSlow103 = expf((0.0f - (dsp->fConst16 / (float)dsp->fVslider2)));
	float fSlow104 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fVslider1 + -49.0f))) * (1.0f - fSlow103)));
	int iSlow105 = (iSlow100 >= 3);
	float fSlow106 = ((0.00999999978f * (float)dsp->fVslider3) + 1.0f);
	float fSlow107 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	int iSlow108 = (int)(float)dsp->fCheckbox3;
	float fSlow109 = (fSlow95 - dsp->fConst15);
	float fSlow110 = ((fSlow10 * (dsp->fConst15 + fSlow87)) / fSlow89);
	float fSlow111 = ((fSlow80 * (dsp->fConst15 + fSlow78)) / fSlow81);
	float fSlow112 = ((fSlow71 * (dsp->fConst15 + fSlow69)) / fSlow72);
	float fSlow113 = ((fSlow62 * (dsp->fConst15 + fSlow60)) / fSlow63);
	float fSlow114 = ((fSlow53 * (dsp->fConst15 + fSlow51)) / fSlow54);
	float fSlow115 = ((fSlow44 * (dsp->fConst15 + fSlow42)) / fSlow45);
	float fSlow116 = ((fSlow35 * (dsp->fConst15 + fSlow33)) / fSlow36);
	float fSlow117 = ((fSlow26 * (dsp->fConst15 + fSlow24)) / fSlow27);
	float fSlow118 = ((fSlow17 * (dsp->fConst15 + fSlow15)) / fSlow18);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec14[0] = (fSlow97 + (0.999000013f * dsp->fRec14[1]));
			dsp->fRec16[0] = (fSlow104 + (fSlow103 * dsp->fRec16[1]));
			float fTemp0 = max(20.0f, fabsf(dsp->fRec16[0]));
			dsp->fVec1[0] = fTemp0;
			float fTemp1 = (dsp->fRec15[1] + (dsp->fConst16 * dsp->fVec1[1]));
			dsp->fRec15[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * dsp->fRec15[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = mydsp_faustpower2_f(fTemp3);
			dsp->fVec2[0] = fTemp4;
			float fTemp5 = mydsp_faustpower3_f(fTemp3);
			dsp->fVec3[0] = (fTemp5 + (1.0f - fTemp2));
			float fTemp6 = ((fTemp5 + (1.0f - (fTemp2 + dsp->fVec3[1]))) / fTemp0);
			dsp->fVec4[0] = fTemp6;
			float fTemp7 = (fTemp4 * (fTemp4 + -2.0f));
			dsp->fVec5[0] = fTemp7;
			float fTemp8 = ((fTemp7 - dsp->fVec5[1]) / fTemp0);
			dsp->fVec6[0] = fTemp8;
			float fTemp9 = ((fTemp8 - dsp->fVec6[1]) / fTemp0);
			dsp->fVec7[0] = fTemp9;
			float fTemp10 = max(20.0f, fabsf((fSlow106 * dsp->fRec16[0])));
			dsp->fVec8[0] = fTemp10;
			float fTemp11 = (dsp->fRec17[1] + (dsp->fConst16 * dsp->fVec8[1]));
			dsp->fRec17[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (2.0f * dsp->fRec17[0]);
			float fTemp13 = (fTemp12 + -1.0f);
			float fTemp14 = mydsp_faustpower2_f(fTemp13);
			dsp->fVec9[0] = fTemp14;
			float fTemp15 = mydsp_faustpower3_f(fTemp13);
			dsp->fVec10[0] = (fTemp15 + (1.0f - fTemp12));
			float fTemp16 = ((fTemp15 + (1.0f - (fTemp12 + dsp->fVec10[1]))) / fTemp10);
			dsp->fVec11[0] = fTemp16;
			float fTemp17 = (fTemp14 * (fTemp14 + -2.0f));
			dsp->fVec12[0] = fTemp17;
			float fTemp18 = ((fTemp17 - dsp->fVec12[1]) / fTemp10);
			dsp->fVec13[0] = fTemp18;
			float fTemp19 = ((fTemp18 - dsp->fVec13[1]) / fTemp10);
			dsp->fVec14[0] = fTemp19;
			float fTemp20 = max(20.0f, fabsf((fSlow107 * dsp->fRec16[0])));
			dsp->fVec15[0] = fTemp20;
			float fTemp21 = (dsp->fRec18[1] + (dsp->fConst16 * dsp->fVec15[1]));
			dsp->fRec18[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (2.0f * dsp->fRec18[0]);
			float fTemp23 = (fTemp22 + -1.0f);
			float fTemp24 = mydsp_faustpower2_f(fTemp23);
			dsp->fVec16[0] = fTemp24;
			float fTemp25 = mydsp_faustpower3_f(fTemp23);
			dsp->fVec17[0] = (fTemp25 + (1.0f - fTemp22));
			float fTemp26 = ((fTemp25 + (1.0f - (fTemp22 + dsp->fVec17[1]))) / fTemp20);
			dsp->fVec18[0] = fTemp26;
			float fTemp27 = (fTemp24 * (fTemp24 + -2.0f));
			dsp->fVec19[0] = fTemp27;
			float fTemp28 = ((fTemp27 - dsp->fVec19[1]) / fTemp20);
			dsp->fVec20[0] = fTemp28;
			float fTemp29 = ((fTemp28 - dsp->fVec20[1]) / fTemp20);
			dsp->fVec21[0] = fTemp29;
			dsp->iRec19[0] = ((1103515245 * dsp->iRec19[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * (float)dsp->iRec19[0]);
			dsp->fRec20[0] = (((0.522189379f * dsp->fRec20[3]) + (fTemp30 + (2.49495602f * dsp->fRec20[1]))) - (2.0172658f * dsp->fRec20[2]));
			float fTemp31 = (dsp->fRec14[0] * (iSlow98?(float)input0[i]:(iSlow99?(iSlow108?(((0.0499220341f * dsp->fRec20[0]) + (0.0506126992f * dsp->fRec20[2])) - ((0.0959935337f * dsp->fRec20[1]) + (0.00440878607f * dsp->fRec20[3]))):fTemp30):(0.333333343f * (dsp->fRec14[0] * (((iSlow101?(iSlow105?(dsp->fConst19 * (((float)dsp->iVec0[3] * (fTemp9 - dsp->fVec7[1])) / fTemp0)):(dsp->fConst18 * (((float)dsp->iVec0[2] * (fTemp6 - dsp->fVec4[1])) / fTemp0))):(iSlow102?(dsp->fConst17 * (((float)dsp->iVec0[1] * (fTemp4 - dsp->fVec2[1])) / fTemp0)):fTemp3)) + (iSlow101?(iSlow105?(dsp->fConst19 * (((float)dsp->iVec0[3] * (fTemp19 - dsp->fVec14[1])) / fTemp10)):(dsp->fConst18 * (((float)dsp->iVec0[2] * (fTemp16 - dsp->fVec11[1])) / fTemp10))):(iSlow102?(dsp->fConst17 * (((float)dsp->iVec0[1] * (fTemp14 - dsp->fVec9[1])) / fTemp10)):fTemp13))) + (iSlow101?(iSlow105?(dsp->fConst19 * (((float)dsp->iVec0[3] * (fTemp29 - dsp->fVec21[1])) / fTemp20)):(dsp->fConst18 * (((float)dsp->iVec0[2] * (fTemp26 - dsp->fVec18[1])) / fTemp20))):(iSlow102?(dsp->fConst17 * (((float)dsp->iVec0[1] * (fTemp24 - dsp->fVec16[1])) / fTemp20)):fTemp23))))))));
			float fTemp32 = (iSlow3?0.0f:fTemp31);
			dsp->fVec22[0] = fTemp32;
			dsp->fRec13[0] = ((fSlow93 * dsp->fRec13[1]) + (fSlow94 * ((fSlow96 * fTemp32) + (fSlow109 * dsp->fVec22[1]))));
			dsp->fVec23[0] = (fSlow90 * dsp->fRec13[0]);
			dsp->fRec12[0] = ((fSlow85 * dsp->fRec12[1]) + (fSlow86 * ((fSlow88 * dsp->fVec23[1]) + (fSlow110 * dsp->fRec13[0]))));
			dsp->fVec24[0] = (fSlow82 * dsp->fRec12[0]);
			dsp->fRec11[0] = ((fSlow76 * dsp->fRec11[1]) + (fSlow77 * ((fSlow79 * dsp->fVec24[1]) + (fSlow111 * dsp->fRec12[0]))));
			dsp->fVec25[0] = (fSlow73 * dsp->fRec11[0]);
			dsp->fRec10[0] = ((fSlow67 * dsp->fRec10[1]) + (fSlow68 * ((fSlow70 * dsp->fVec25[1]) + (fSlow112 * dsp->fRec11[0]))));
			dsp->fVec26[0] = (fSlow64 * dsp->fRec10[0]);
			dsp->fRec9[0] = ((fSlow58 * dsp->fRec9[1]) + (fSlow59 * ((fSlow61 * dsp->fVec26[1]) + (fSlow113 * dsp->fRec10[0]))));
			dsp->fVec27[0] = (fSlow55 * dsp->fRec9[0]);
			dsp->fRec8[0] = ((fSlow49 * dsp->fRec8[1]) + (fSlow50 * ((fSlow52 * dsp->fVec27[1]) + (fSlow114 * dsp->fRec9[0]))));
			dsp->fVec28[0] = (fSlow46 * dsp->fRec8[0]);
			dsp->fRec7[0] = ((fSlow40 * dsp->fRec7[1]) + (fSlow41 * ((fSlow43 * dsp->fVec28[1]) + (fSlow115 * dsp->fRec8[0]))));
			dsp->fVec29[0] = (fSlow37 * dsp->fRec7[0]);
			dsp->fRec6[0] = ((fSlow31 * dsp->fRec6[1]) + (fSlow32 * ((fSlow34 * dsp->fVec29[1]) + (fSlow116 * dsp->fRec7[0]))));
			dsp->fVec30[0] = (fSlow28 * dsp->fRec6[0]);
			dsp->fRec5[0] = ((fSlow22 * dsp->fRec5[1]) + (fSlow23 * ((fSlow25 * dsp->fVec30[1]) + (fSlow117 * dsp->fRec6[0]))));
			dsp->fVec31[0] = (fSlow19 * dsp->fRec5[0]);
			dsp->fRec4[0] = ((fSlow13 * dsp->fRec4[1]) + (fSlow14 * ((fSlow16 * dsp->fVec31[1]) + (fSlow118 * dsp->fRec5[0]))));
			float fTemp33 = (iSlow3?fTemp31:(fSlow9 * dsp->fRec4[0]));
			dsp->fRec3[0] = (fTemp33 - (dsp->fConst11 * ((dsp->fConst20 * dsp->fRec3[2]) + (dsp->fConst22 * dsp->fRec3[1]))));
			dsp->fRec2[0] = ((dsp->fConst11 * (((dsp->fConst13 * dsp->fRec3[1]) + (dsp->fConst23 * dsp->fRec3[0])) + (dsp->fConst23 * dsp->fRec3[2]))) - (dsp->fConst8 * ((dsp->fConst24 * dsp->fRec2[2]) + (dsp->fConst25 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst8 * (((dsp->fConst10 * dsp->fRec2[1]) + (dsp->fConst26 * dsp->fRec2[0])) + (dsp->fConst26 * dsp->fRec2[2]))) - (dsp->fConst4 * ((dsp->fConst27 * dsp->fRec1[2]) + (dsp->fConst28 * dsp->fRec1[1]))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * fabsf((dsp->fConst4 * (((dsp->fConst7 * dsp->fRec1[1]) + (dsp->fConst29 * dsp->fRec1[0])) + (dsp->fConst29 * dsp->fRec1[2]))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec0[0]))));
			dsp->fRec27[0] = (fTemp33 - (dsp->fConst46 * ((dsp->fConst49 * dsp->fRec27[2]) + (dsp->fConst50 * dsp->fRec27[1]))));
			dsp->fRec26[0] = ((dsp->fConst46 * (((dsp->fConst48 * dsp->fRec27[1]) + (dsp->fConst51 * dsp->fRec27[0])) + (dsp->fConst51 * dsp->fRec27[2]))) - (dsp->fConst44 * ((dsp->fConst52 * dsp->fRec26[2]) + (dsp->fConst53 * dsp->fRec26[1]))));
			dsp->fRec25[0] = ((dsp->fConst44 * (((dsp->fConst45 * dsp->fRec26[1]) + (dsp->fConst54 * dsp->fRec26[0])) + (dsp->fConst54 * dsp->fRec26[2]))) - (dsp->fConst42 * ((dsp->fConst55 * dsp->fRec25[2]) + (dsp->fConst56 * dsp->fRec25[1]))));
			float fTemp34 = (dsp->fConst42 * (((dsp->fConst43 * dsp->fRec25[1]) + (dsp->fConst57 * dsp->fRec25[0])) + (dsp->fConst57 * dsp->fRec25[2])));
			dsp->fRec24[0] = (fTemp34 - (dsp->fConst39 * ((dsp->fConst58 * dsp->fRec24[2]) + (dsp->fConst60 * dsp->fRec24[1]))));
			dsp->fRec23[0] = ((dsp->fConst39 * (((dsp->fConst41 * dsp->fRec24[1]) + (dsp->fConst61 * dsp->fRec24[0])) + (dsp->fConst61 * dsp->fRec24[2]))) - (dsp->fConst36 * ((dsp->fConst62 * dsp->fRec23[2]) + (dsp->fConst63 * dsp->fRec23[1]))));
			dsp->fRec22[0] = ((dsp->fConst36 * (((dsp->fConst38 * dsp->fRec23[1]) + (dsp->fConst64 * dsp->fRec23[0])) + (dsp->fConst64 * dsp->fRec23[2]))) - (dsp->fConst32 * ((dsp->fConst65 * dsp->fRec22[2]) + (dsp->fConst66 * dsp->fRec22[1]))));
			dsp->fRec21[0] = ((fSlow1 * dsp->fRec21[1]) + (fSlow2 * fabsf((dsp->fConst32 * (((dsp->fConst35 * dsp->fRec22[1]) + (dsp->fConst67 * dsp->fRec22[0])) + (dsp->fConst67 * dsp->fRec22[2]))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec21[0]))));
			dsp->fRec34[0] = (fTemp34 - (dsp->fConst84 * ((dsp->fConst87 * dsp->fRec34[2]) + (dsp->fConst88 * dsp->fRec34[1]))));
			dsp->fRec33[0] = ((dsp->fConst84 * (((dsp->fConst86 * dsp->fRec34[1]) + (dsp->fConst89 * dsp->fRec34[0])) + (dsp->fConst89 * dsp->fRec34[2]))) - (dsp->fConst82 * ((dsp->fConst90 * dsp->fRec33[2]) + (dsp->fConst91 * dsp->fRec33[1]))));
			dsp->fRec32[0] = ((dsp->fConst82 * (((dsp->fConst83 * dsp->fRec33[1]) + (dsp->fConst92 * dsp->fRec33[0])) + (dsp->fConst92 * dsp->fRec33[2]))) - (dsp->fConst80 * ((dsp->fConst93 * dsp->fRec32[2]) + (dsp->fConst94 * dsp->fRec32[1]))));
			float fTemp35 = (dsp->fConst80 * (((dsp->fConst81 * dsp->fRec32[1]) + (dsp->fConst95 * dsp->fRec32[0])) + (dsp->fConst95 * dsp->fRec32[2])));
			dsp->fRec31[0] = (fTemp35 - (dsp->fConst77 * ((dsp->fConst96 * dsp->fRec31[2]) + (dsp->fConst98 * dsp->fRec31[1]))));
			dsp->fRec30[0] = ((dsp->fConst77 * (((dsp->fConst79 * dsp->fRec31[1]) + (dsp->fConst99 * dsp->fRec31[0])) + (dsp->fConst99 * dsp->fRec31[2]))) - (dsp->fConst74 * ((dsp->fConst100 * dsp->fRec30[2]) + (dsp->fConst101 * dsp->fRec30[1]))));
			dsp->fRec29[0] = ((dsp->fConst74 * (((dsp->fConst76 * dsp->fRec30[1]) + (dsp->fConst102 * dsp->fRec30[0])) + (dsp->fConst102 * dsp->fRec30[2]))) - (dsp->fConst70 * ((dsp->fConst103 * dsp->fRec29[2]) + (dsp->fConst104 * dsp->fRec29[1]))));
			dsp->fRec28[0] = ((fSlow1 * dsp->fRec28[1]) + (fSlow2 * fabsf((dsp->fConst70 * (((dsp->fConst73 * dsp->fRec29[1]) + (dsp->fConst105 * dsp->fRec29[0])) + (dsp->fConst105 * dsp->fRec29[2]))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec28[0]))));
			dsp->fRec41[0] = (fTemp35 - (dsp->fConst122 * ((dsp->fConst125 * dsp->fRec41[2]) + (dsp->fConst126 * dsp->fRec41[1]))));
			dsp->fRec40[0] = ((dsp->fConst122 * (((dsp->fConst124 * dsp->fRec41[1]) + (dsp->fConst127 * dsp->fRec41[0])) + (dsp->fConst127 * dsp->fRec41[2]))) - (dsp->fConst120 * ((dsp->fConst128 * dsp->fRec40[2]) + (dsp->fConst129 * dsp->fRec40[1]))));
			dsp->fRec39[0] = ((dsp->fConst120 * (((dsp->fConst121 * dsp->fRec40[1]) + (dsp->fConst130 * dsp->fRec40[0])) + (dsp->fConst130 * dsp->fRec40[2]))) - (dsp->fConst118 * ((dsp->fConst131 * dsp->fRec39[2]) + (dsp->fConst132 * dsp->fRec39[1]))));
			float fTemp36 = (dsp->fConst118 * (((dsp->fConst119 * dsp->fRec39[1]) + (dsp->fConst133 * dsp->fRec39[0])) + (dsp->fConst133 * dsp->fRec39[2])));
			dsp->fRec38[0] = (fTemp36 - (dsp->fConst115 * ((dsp->fConst134 * dsp->fRec38[2]) + (dsp->fConst136 * dsp->fRec38[1]))));
			dsp->fRec37[0] = ((dsp->fConst115 * (((dsp->fConst117 * dsp->fRec38[1]) + (dsp->fConst137 * dsp->fRec38[0])) + (dsp->fConst137 * dsp->fRec38[2]))) - (dsp->fConst112 * ((dsp->fConst138 * dsp->fRec37[2]) + (dsp->fConst139 * dsp->fRec37[1]))));
			dsp->fRec36[0] = ((dsp->fConst112 * (((dsp->fConst114 * dsp->fRec37[1]) + (dsp->fConst140 * dsp->fRec37[0])) + (dsp->fConst140 * dsp->fRec37[2]))) - (dsp->fConst108 * ((dsp->fConst141 * dsp->fRec36[2]) + (dsp->fConst142 * dsp->fRec36[1]))));
			dsp->fRec35[0] = ((fSlow1 * dsp->fRec35[1]) + (fSlow2 * fabsf((dsp->fConst108 * (((dsp->fConst111 * dsp->fRec36[1]) + (dsp->fConst143 * dsp->fRec36[0])) + (dsp->fConst143 * dsp->fRec36[2]))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec35[0]))));
			dsp->fRec48[0] = (fTemp36 - (dsp->fConst160 * ((dsp->fConst163 * dsp->fRec48[2]) + (dsp->fConst164 * dsp->fRec48[1]))));
			dsp->fRec47[0] = ((dsp->fConst160 * (((dsp->fConst162 * dsp->fRec48[1]) + (dsp->fConst165 * dsp->fRec48[0])) + (dsp->fConst165 * dsp->fRec48[2]))) - (dsp->fConst158 * ((dsp->fConst166 * dsp->fRec47[2]) + (dsp->fConst167 * dsp->fRec47[1]))));
			dsp->fRec46[0] = ((dsp->fConst158 * (((dsp->fConst159 * dsp->fRec47[1]) + (dsp->fConst168 * dsp->fRec47[0])) + (dsp->fConst168 * dsp->fRec47[2]))) - (dsp->fConst156 * ((dsp->fConst169 * dsp->fRec46[2]) + (dsp->fConst170 * dsp->fRec46[1]))));
			float fTemp37 = (dsp->fConst156 * (((dsp->fConst157 * dsp->fRec46[1]) + (dsp->fConst171 * dsp->fRec46[0])) + (dsp->fConst171 * dsp->fRec46[2])));
			dsp->fRec45[0] = (fTemp37 - (dsp->fConst153 * ((dsp->fConst172 * dsp->fRec45[2]) + (dsp->fConst174 * dsp->fRec45[1]))));
			dsp->fRec44[0] = ((dsp->fConst153 * (((dsp->fConst155 * dsp->fRec45[1]) + (dsp->fConst175 * dsp->fRec45[0])) + (dsp->fConst175 * dsp->fRec45[2]))) - (dsp->fConst150 * ((dsp->fConst176 * dsp->fRec44[2]) + (dsp->fConst177 * dsp->fRec44[1]))));
			dsp->fRec43[0] = ((dsp->fConst150 * (((dsp->fConst152 * dsp->fRec44[1]) + (dsp->fConst178 * dsp->fRec44[0])) + (dsp->fConst178 * dsp->fRec44[2]))) - (dsp->fConst146 * ((dsp->fConst179 * dsp->fRec43[2]) + (dsp->fConst180 * dsp->fRec43[1]))));
			dsp->fRec42[0] = ((fSlow1 * dsp->fRec42[1]) + (fSlow2 * fabsf((dsp->fConst146 * (((dsp->fConst149 * dsp->fRec43[1]) + (dsp->fConst181 * dsp->fRec43[0])) + (dsp->fConst181 * dsp->fRec43[2]))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec42[0]))));
			dsp->fRec55[0] = (fTemp37 - (dsp->fConst198 * ((dsp->fConst201 * dsp->fRec55[2]) + (dsp->fConst202 * dsp->fRec55[1]))));
			dsp->fRec54[0] = ((dsp->fConst198 * (((dsp->fConst200 * dsp->fRec55[1]) + (dsp->fConst203 * dsp->fRec55[0])) + (dsp->fConst203 * dsp->fRec55[2]))) - (dsp->fConst196 * ((dsp->fConst204 * dsp->fRec54[2]) + (dsp->fConst205 * dsp->fRec54[1]))));
			dsp->fRec53[0] = ((dsp->fConst196 * (((dsp->fConst197 * dsp->fRec54[1]) + (dsp->fConst206 * dsp->fRec54[0])) + (dsp->fConst206 * dsp->fRec54[2]))) - (dsp->fConst194 * ((dsp->fConst207 * dsp->fRec53[2]) + (dsp->fConst208 * dsp->fRec53[1]))));
			float fTemp38 = (dsp->fConst194 * (((dsp->fConst195 * dsp->fRec53[1]) + (dsp->fConst209 * dsp->fRec53[0])) + (dsp->fConst209 * dsp->fRec53[2])));
			dsp->fRec52[0] = (fTemp38 - (dsp->fConst191 * ((dsp->fConst210 * dsp->fRec52[2]) + (dsp->fConst212 * dsp->fRec52[1]))));
			dsp->fRec51[0] = ((dsp->fConst191 * (((dsp->fConst193 * dsp->fRec52[1]) + (dsp->fConst213 * dsp->fRec52[0])) + (dsp->fConst213 * dsp->fRec52[2]))) - (dsp->fConst188 * ((dsp->fConst214 * dsp->fRec51[2]) + (dsp->fConst215 * dsp->fRec51[1]))));
			dsp->fRec50[0] = ((dsp->fConst188 * (((dsp->fConst190 * dsp->fRec51[1]) + (dsp->fConst216 * dsp->fRec51[0])) + (dsp->fConst216 * dsp->fRec51[2]))) - (dsp->fConst184 * ((dsp->fConst217 * dsp->fRec50[2]) + (dsp->fConst218 * dsp->fRec50[1]))));
			dsp->fRec49[0] = ((fSlow1 * dsp->fRec49[1]) + (fSlow2 * fabsf((dsp->fConst184 * (((dsp->fConst187 * dsp->fRec50[1]) + (dsp->fConst219 * dsp->fRec50[0])) + (dsp->fConst219 * dsp->fRec50[2]))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec49[0]))));
			dsp->fRec62[0] = (fTemp38 - (dsp->fConst236 * ((dsp->fConst239 * dsp->fRec62[2]) + (dsp->fConst240 * dsp->fRec62[1]))));
			dsp->fRec61[0] = ((dsp->fConst236 * (((dsp->fConst238 * dsp->fRec62[1]) + (dsp->fConst241 * dsp->fRec62[0])) + (dsp->fConst241 * dsp->fRec62[2]))) - (dsp->fConst234 * ((dsp->fConst242 * dsp->fRec61[2]) + (dsp->fConst243 * dsp->fRec61[1]))));
			dsp->fRec60[0] = ((dsp->fConst234 * (((dsp->fConst235 * dsp->fRec61[1]) + (dsp->fConst244 * dsp->fRec61[0])) + (dsp->fConst244 * dsp->fRec61[2]))) - (dsp->fConst232 * ((dsp->fConst245 * dsp->fRec60[2]) + (dsp->fConst246 * dsp->fRec60[1]))));
			float fTemp39 = (dsp->fConst232 * (((dsp->fConst233 * dsp->fRec60[1]) + (dsp->fConst247 * dsp->fRec60[0])) + (dsp->fConst247 * dsp->fRec60[2])));
			dsp->fRec59[0] = (fTemp39 - (dsp->fConst229 * ((dsp->fConst248 * dsp->fRec59[2]) + (dsp->fConst250 * dsp->fRec59[1]))));
			dsp->fRec58[0] = ((dsp->fConst229 * (((dsp->fConst231 * dsp->fRec59[1]) + (dsp->fConst251 * dsp->fRec59[0])) + (dsp->fConst251 * dsp->fRec59[2]))) - (dsp->fConst226 * ((dsp->fConst252 * dsp->fRec58[2]) + (dsp->fConst253 * dsp->fRec58[1]))));
			dsp->fRec57[0] = ((dsp->fConst226 * (((dsp->fConst228 * dsp->fRec58[1]) + (dsp->fConst254 * dsp->fRec58[0])) + (dsp->fConst254 * dsp->fRec58[2]))) - (dsp->fConst222 * ((dsp->fConst255 * dsp->fRec57[2]) + (dsp->fConst256 * dsp->fRec57[1]))));
			dsp->fRec56[0] = ((fSlow1 * dsp->fRec56[1]) + (fSlow2 * fabsf((dsp->fConst222 * (((dsp->fConst225 * dsp->fRec57[1]) + (dsp->fConst257 * dsp->fRec57[0])) + (dsp->fConst257 * dsp->fRec57[2]))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec56[0]))));
			dsp->fRec69[0] = (fTemp39 - (dsp->fConst274 * ((dsp->fConst277 * dsp->fRec69[2]) + (dsp->fConst278 * dsp->fRec69[1]))));
			dsp->fRec68[0] = ((dsp->fConst274 * (((dsp->fConst276 * dsp->fRec69[1]) + (dsp->fConst279 * dsp->fRec69[0])) + (dsp->fConst279 * dsp->fRec69[2]))) - (dsp->fConst272 * ((dsp->fConst280 * dsp->fRec68[2]) + (dsp->fConst281 * dsp->fRec68[1]))));
			dsp->fRec67[0] = ((dsp->fConst272 * (((dsp->fConst273 * dsp->fRec68[1]) + (dsp->fConst282 * dsp->fRec68[0])) + (dsp->fConst282 * dsp->fRec68[2]))) - (dsp->fConst270 * ((dsp->fConst283 * dsp->fRec67[2]) + (dsp->fConst284 * dsp->fRec67[1]))));
			float fTemp40 = (dsp->fConst270 * (((dsp->fConst271 * dsp->fRec67[1]) + (dsp->fConst285 * dsp->fRec67[0])) + (dsp->fConst285 * dsp->fRec67[2])));
			dsp->fRec66[0] = (fTemp40 - (dsp->fConst267 * ((dsp->fConst286 * dsp->fRec66[2]) + (dsp->fConst288 * dsp->fRec66[1]))));
			dsp->fRec65[0] = ((dsp->fConst267 * (((dsp->fConst269 * dsp->fRec66[1]) + (dsp->fConst289 * dsp->fRec66[0])) + (dsp->fConst289 * dsp->fRec66[2]))) - (dsp->fConst264 * ((dsp->fConst290 * dsp->fRec65[2]) + (dsp->fConst291 * dsp->fRec65[1]))));
			dsp->fRec64[0] = ((dsp->fConst264 * (((dsp->fConst266 * dsp->fRec65[1]) + (dsp->fConst292 * dsp->fRec65[0])) + (dsp->fConst292 * dsp->fRec65[2]))) - (dsp->fConst260 * ((dsp->fConst293 * dsp->fRec64[2]) + (dsp->fConst294 * dsp->fRec64[1]))));
			dsp->fRec63[0] = ((fSlow1 * dsp->fRec63[1]) + (fSlow2 * fabsf((dsp->fConst260 * (((dsp->fConst263 * dsp->fRec64[1]) + (dsp->fConst295 * dsp->fRec64[0])) + (dsp->fConst295 * dsp->fRec64[2]))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec63[0]))));
			dsp->fRec76[0] = (fTemp40 - (dsp->fConst312 * ((dsp->fConst315 * dsp->fRec76[2]) + (dsp->fConst316 * dsp->fRec76[1]))));
			dsp->fRec75[0] = ((dsp->fConst312 * (((dsp->fConst314 * dsp->fRec76[1]) + (dsp->fConst317 * dsp->fRec76[0])) + (dsp->fConst317 * dsp->fRec76[2]))) - (dsp->fConst310 * ((dsp->fConst318 * dsp->fRec75[2]) + (dsp->fConst319 * dsp->fRec75[1]))));
			dsp->fRec74[0] = ((dsp->fConst310 * (((dsp->fConst311 * dsp->fRec75[1]) + (dsp->fConst320 * dsp->fRec75[0])) + (dsp->fConst320 * dsp->fRec75[2]))) - (dsp->fConst308 * ((dsp->fConst321 * dsp->fRec74[2]) + (dsp->fConst322 * dsp->fRec74[1]))));
			float fTemp41 = (dsp->fConst308 * (((dsp->fConst309 * dsp->fRec74[1]) + (dsp->fConst323 * dsp->fRec74[0])) + (dsp->fConst323 * dsp->fRec74[2])));
			dsp->fRec73[0] = (fTemp41 - (dsp->fConst305 * ((dsp->fConst324 * dsp->fRec73[2]) + (dsp->fConst326 * dsp->fRec73[1]))));
			dsp->fRec72[0] = ((dsp->fConst305 * (((dsp->fConst307 * dsp->fRec73[1]) + (dsp->fConst327 * dsp->fRec73[0])) + (dsp->fConst327 * dsp->fRec73[2]))) - (dsp->fConst302 * ((dsp->fConst328 * dsp->fRec72[2]) + (dsp->fConst329 * dsp->fRec72[1]))));
			dsp->fRec71[0] = ((dsp->fConst302 * (((dsp->fConst304 * dsp->fRec72[1]) + (dsp->fConst330 * dsp->fRec72[0])) + (dsp->fConst330 * dsp->fRec72[2]))) - (dsp->fConst298 * ((dsp->fConst331 * dsp->fRec71[2]) + (dsp->fConst332 * dsp->fRec71[1]))));
			dsp->fRec70[0] = ((fSlow1 * dsp->fRec70[1]) + (fSlow2 * fabsf((dsp->fConst298 * (((dsp->fConst301 * dsp->fRec71[1]) + (dsp->fConst333 * dsp->fRec71[0])) + (dsp->fConst333 * dsp->fRec71[2]))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec70[0]))));
			dsp->fRec83[0] = (fTemp41 - (dsp->fConst350 * ((dsp->fConst353 * dsp->fRec83[2]) + (dsp->fConst354 * dsp->fRec83[1]))));
			dsp->fRec82[0] = ((dsp->fConst350 * (((dsp->fConst352 * dsp->fRec83[1]) + (dsp->fConst355 * dsp->fRec83[0])) + (dsp->fConst355 * dsp->fRec83[2]))) - (dsp->fConst348 * ((dsp->fConst356 * dsp->fRec82[2]) + (dsp->fConst357 * dsp->fRec82[1]))));
			dsp->fRec81[0] = ((dsp->fConst348 * (((dsp->fConst349 * dsp->fRec82[1]) + (dsp->fConst358 * dsp->fRec82[0])) + (dsp->fConst358 * dsp->fRec82[2]))) - (dsp->fConst346 * ((dsp->fConst359 * dsp->fRec81[2]) + (dsp->fConst360 * dsp->fRec81[1]))));
			float fTemp42 = (dsp->fConst346 * (((dsp->fConst347 * dsp->fRec81[1]) + (dsp->fConst361 * dsp->fRec81[0])) + (dsp->fConst361 * dsp->fRec81[2])));
			dsp->fRec80[0] = (fTemp42 - (dsp->fConst343 * ((dsp->fConst362 * dsp->fRec80[2]) + (dsp->fConst364 * dsp->fRec80[1]))));
			dsp->fRec79[0] = ((dsp->fConst343 * (((dsp->fConst345 * dsp->fRec80[1]) + (dsp->fConst365 * dsp->fRec80[0])) + (dsp->fConst365 * dsp->fRec80[2]))) - (dsp->fConst340 * ((dsp->fConst366 * dsp->fRec79[2]) + (dsp->fConst367 * dsp->fRec79[1]))));
			dsp->fRec78[0] = ((dsp->fConst340 * (((dsp->fConst342 * dsp->fRec79[1]) + (dsp->fConst368 * dsp->fRec79[0])) + (dsp->fConst368 * dsp->fRec79[2]))) - (dsp->fConst336 * ((dsp->fConst369 * dsp->fRec78[2]) + (dsp->fConst370 * dsp->fRec78[1]))));
			dsp->fRec77[0] = ((fSlow1 * dsp->fRec77[1]) + (fSlow2 * fabsf((dsp->fConst336 * (((dsp->fConst339 * dsp->fRec78[1]) + (dsp->fConst371 * dsp->fRec78[0])) + (dsp->fConst371 * dsp->fRec78[2]))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec77[0]))));
			dsp->fRec90[0] = (fTemp42 - (dsp->fConst388 * ((dsp->fConst391 * dsp->fRec90[2]) + (dsp->fConst392 * dsp->fRec90[1]))));
			dsp->fRec89[0] = ((dsp->fConst388 * (((dsp->fConst390 * dsp->fRec90[1]) + (dsp->fConst393 * dsp->fRec90[0])) + (dsp->fConst393 * dsp->fRec90[2]))) - (dsp->fConst386 * ((dsp->fConst394 * dsp->fRec89[2]) + (dsp->fConst395 * dsp->fRec89[1]))));
			dsp->fRec88[0] = ((dsp->fConst386 * (((dsp->fConst387 * dsp->fRec89[1]) + (dsp->fConst396 * dsp->fRec89[0])) + (dsp->fConst396 * dsp->fRec89[2]))) - (dsp->fConst384 * ((dsp->fConst397 * dsp->fRec88[2]) + (dsp->fConst398 * dsp->fRec88[1]))));
			float fTemp43 = (dsp->fConst384 * (((dsp->fConst385 * dsp->fRec88[1]) + (dsp->fConst399 * dsp->fRec88[0])) + (dsp->fConst399 * dsp->fRec88[2])));
			dsp->fRec87[0] = (fTemp43 - (dsp->fConst381 * ((dsp->fConst400 * dsp->fRec87[2]) + (dsp->fConst402 * dsp->fRec87[1]))));
			dsp->fRec86[0] = ((dsp->fConst381 * (((dsp->fConst383 * dsp->fRec87[1]) + (dsp->fConst403 * dsp->fRec87[0])) + (dsp->fConst403 * dsp->fRec87[2]))) - (dsp->fConst378 * ((dsp->fConst404 * dsp->fRec86[2]) + (dsp->fConst405 * dsp->fRec86[1]))));
			dsp->fRec85[0] = ((dsp->fConst378 * (((dsp->fConst380 * dsp->fRec86[1]) + (dsp->fConst406 * dsp->fRec86[0])) + (dsp->fConst406 * dsp->fRec86[2]))) - (dsp->fConst374 * ((dsp->fConst407 * dsp->fRec85[2]) + (dsp->fConst408 * dsp->fRec85[1]))));
			dsp->fRec84[0] = ((fSlow1 * dsp->fRec84[1]) + (fSlow2 * fabsf((dsp->fConst374 * (((dsp->fConst377 * dsp->fRec85[1]) + (dsp->fConst409 * dsp->fRec85[0])) + (dsp->fConst409 * dsp->fRec85[2]))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec84[0]))));
			dsp->fRec97[0] = (fTemp43 - (dsp->fConst426 * ((dsp->fConst429 * dsp->fRec97[2]) + (dsp->fConst430 * dsp->fRec97[1]))));
			dsp->fRec96[0] = ((dsp->fConst426 * (((dsp->fConst428 * dsp->fRec97[1]) + (dsp->fConst431 * dsp->fRec97[0])) + (dsp->fConst431 * dsp->fRec97[2]))) - (dsp->fConst424 * ((dsp->fConst432 * dsp->fRec96[2]) + (dsp->fConst433 * dsp->fRec96[1]))));
			dsp->fRec95[0] = ((dsp->fConst424 * (((dsp->fConst425 * dsp->fRec96[1]) + (dsp->fConst434 * dsp->fRec96[0])) + (dsp->fConst434 * dsp->fRec96[2]))) - (dsp->fConst422 * ((dsp->fConst435 * dsp->fRec95[2]) + (dsp->fConst436 * dsp->fRec95[1]))));
			float fTemp44 = (dsp->fConst422 * (((dsp->fConst423 * dsp->fRec95[1]) + (dsp->fConst437 * dsp->fRec95[0])) + (dsp->fConst437 * dsp->fRec95[2])));
			dsp->fRec94[0] = (fTemp44 - (dsp->fConst419 * ((dsp->fConst438 * dsp->fRec94[2]) + (dsp->fConst440 * dsp->fRec94[1]))));
			dsp->fRec93[0] = ((dsp->fConst419 * (((dsp->fConst421 * dsp->fRec94[1]) + (dsp->fConst441 * dsp->fRec94[0])) + (dsp->fConst441 * dsp->fRec94[2]))) - (dsp->fConst416 * ((dsp->fConst442 * dsp->fRec93[2]) + (dsp->fConst443 * dsp->fRec93[1]))));
			dsp->fRec92[0] = ((dsp->fConst416 * (((dsp->fConst418 * dsp->fRec93[1]) + (dsp->fConst444 * dsp->fRec93[0])) + (dsp->fConst444 * dsp->fRec93[2]))) - (dsp->fConst412 * ((dsp->fConst445 * dsp->fRec92[2]) + (dsp->fConst446 * dsp->fRec92[1]))));
			dsp->fRec91[0] = ((fSlow1 * dsp->fRec91[1]) + (fSlow2 * fabsf((dsp->fConst412 * (((dsp->fConst415 * dsp->fRec92[1]) + (dsp->fConst447 * dsp->fRec92[0])) + (dsp->fConst447 * dsp->fRec92[2]))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec91[0]))));
			dsp->fRec104[0] = (fTemp44 - (dsp->fConst464 * ((dsp->fConst467 * dsp->fRec104[2]) + (dsp->fConst468 * dsp->fRec104[1]))));
			dsp->fRec103[0] = ((dsp->fConst464 * (((dsp->fConst466 * dsp->fRec104[1]) + (dsp->fConst469 * dsp->fRec104[0])) + (dsp->fConst469 * dsp->fRec104[2]))) - (dsp->fConst462 * ((dsp->fConst470 * dsp->fRec103[2]) + (dsp->fConst471 * dsp->fRec103[1]))));
			dsp->fRec102[0] = ((dsp->fConst462 * (((dsp->fConst463 * dsp->fRec103[1]) + (dsp->fConst472 * dsp->fRec103[0])) + (dsp->fConst472 * dsp->fRec103[2]))) - (dsp->fConst460 * ((dsp->fConst473 * dsp->fRec102[2]) + (dsp->fConst474 * dsp->fRec102[1]))));
			float fTemp45 = (dsp->fConst460 * (((dsp->fConst461 * dsp->fRec102[1]) + (dsp->fConst475 * dsp->fRec102[0])) + (dsp->fConst475 * dsp->fRec102[2])));
			dsp->fRec101[0] = (fTemp45 - (dsp->fConst457 * ((dsp->fConst476 * dsp->fRec101[2]) + (dsp->fConst478 * dsp->fRec101[1]))));
			dsp->fRec100[0] = ((dsp->fConst457 * (((dsp->fConst459 * dsp->fRec101[1]) + (dsp->fConst479 * dsp->fRec101[0])) + (dsp->fConst479 * dsp->fRec101[2]))) - (dsp->fConst454 * ((dsp->fConst480 * dsp->fRec100[2]) + (dsp->fConst481 * dsp->fRec100[1]))));
			dsp->fRec99[0] = ((dsp->fConst454 * (((dsp->fConst456 * dsp->fRec100[1]) + (dsp->fConst482 * dsp->fRec100[0])) + (dsp->fConst482 * dsp->fRec100[2]))) - (dsp->fConst450 * ((dsp->fConst483 * dsp->fRec99[2]) + (dsp->fConst484 * dsp->fRec99[1]))));
			dsp->fRec98[0] = ((fSlow1 * dsp->fRec98[1]) + (fSlow2 * fabsf((dsp->fConst450 * (((dsp->fConst453 * dsp->fRec99[1]) + (dsp->fConst485 * dsp->fRec99[0])) + (dsp->fConst485 * dsp->fRec99[2]))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec98[0]))));
			dsp->fRec111[0] = (fTemp45 - (dsp->fConst502 * ((dsp->fConst505 * dsp->fRec111[2]) + (dsp->fConst506 * dsp->fRec111[1]))));
			dsp->fRec110[0] = ((dsp->fConst502 * (((dsp->fConst504 * dsp->fRec111[1]) + (dsp->fConst507 * dsp->fRec111[0])) + (dsp->fConst507 * dsp->fRec111[2]))) - (dsp->fConst500 * ((dsp->fConst508 * dsp->fRec110[2]) + (dsp->fConst509 * dsp->fRec110[1]))));
			dsp->fRec109[0] = ((dsp->fConst500 * (((dsp->fConst501 * dsp->fRec110[1]) + (dsp->fConst510 * dsp->fRec110[0])) + (dsp->fConst510 * dsp->fRec110[2]))) - (dsp->fConst498 * ((dsp->fConst511 * dsp->fRec109[2]) + (dsp->fConst512 * dsp->fRec109[1]))));
			float fTemp46 = (dsp->fConst498 * (((dsp->fConst499 * dsp->fRec109[1]) + (dsp->fConst513 * dsp->fRec109[0])) + (dsp->fConst513 * dsp->fRec109[2])));
			dsp->fRec108[0] = (fTemp46 - (dsp->fConst495 * ((dsp->fConst514 * dsp->fRec108[2]) + (dsp->fConst516 * dsp->fRec108[1]))));
			dsp->fRec107[0] = ((dsp->fConst495 * (((dsp->fConst497 * dsp->fRec108[1]) + (dsp->fConst517 * dsp->fRec108[0])) + (dsp->fConst517 * dsp->fRec108[2]))) - (dsp->fConst492 * ((dsp->fConst518 * dsp->fRec107[2]) + (dsp->fConst519 * dsp->fRec107[1]))));
			dsp->fRec106[0] = ((dsp->fConst492 * (((dsp->fConst494 * dsp->fRec107[1]) + (dsp->fConst520 * dsp->fRec107[0])) + (dsp->fConst520 * dsp->fRec107[2]))) - (dsp->fConst488 * ((dsp->fConst521 * dsp->fRec106[2]) + (dsp->fConst522 * dsp->fRec106[1]))));
			dsp->fRec105[0] = ((fSlow1 * dsp->fRec105[1]) + (fSlow2 * fabsf((dsp->fConst488 * (((dsp->fConst491 * dsp->fRec106[1]) + (dsp->fConst523 * dsp->fRec106[0])) + (dsp->fConst523 * dsp->fRec106[2]))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec105[0]))));
			dsp->fRec115[0] = (fTemp46 - (dsp->fConst528 * ((dsp->fConst531 * dsp->fRec115[2]) + (dsp->fConst532 * dsp->fRec115[1]))));
			dsp->fRec114[0] = ((dsp->fConst528 * (((dsp->fConst530 * dsp->fRec115[1]) + (dsp->fConst533 * dsp->fRec115[0])) + (dsp->fConst533 * dsp->fRec115[2]))) - (dsp->fConst526 * ((dsp->fConst534 * dsp->fRec114[2]) + (dsp->fConst535 * dsp->fRec114[1]))));
			dsp->fRec113[0] = ((dsp->fConst526 * (((dsp->fConst527 * dsp->fRec114[1]) + (dsp->fConst536 * dsp->fRec114[0])) + (dsp->fConst536 * dsp->fRec114[2]))) - (dsp->fConst524 * ((dsp->fConst537 * dsp->fRec113[2]) + (dsp->fConst538 * dsp->fRec113[1]))));
			dsp->fRec112[0] = ((fSlow1 * dsp->fRec112[1]) + (fSlow2 * fabsf((dsp->fConst524 * (((dsp->fConst525 * dsp->fRec113[1]) + (dsp->fConst539 * dsp->fRec113[0])) + (dsp->fConst539 * dsp->fRec113[2]))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec112[0]))));
			output0[i] = (FAUSTFLOAT)fTemp33;
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->iRec19[1] = dsp->iRec19[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec20[j1] = dsp->fRec20[(j1 - 1)];
					
				}
				
			}
			dsp->fVec22[1] = dsp->fVec22[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fVec23[1] = dsp->fVec23[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fVec24[1] = dsp->fVec24[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fVec25[1] = dsp->fVec25[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fVec26[1] = dsp->fVec26[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fVec27[1] = dsp->fVec27[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fVec28[1] = dsp->fVec28[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fVec29[1] = dsp->fVec29[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fVec30[1] = dsp->fVec30[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fVec31[1] = dsp->fVec31[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[2] = dsp->fRec32[1];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec31[2] = dsp->fRec31[1];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec37[2] = dsp->fRec37[1];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec48[2] = dsp->fRec48[1];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec53[2] = dsp->fRec53[1];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[2] = dsp->fRec51[1];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec50[2] = dsp->fRec50[1];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec61[2] = dsp->fRec61[1];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec60[2] = dsp->fRec60[1];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec57[2] = dsp->fRec57[1];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec68[2] = dsp->fRec68[1];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec67[2] = dsp->fRec67[1];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec66[2] = dsp->fRec66[1];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec65[2] = dsp->fRec65[1];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec64[2] = dsp->fRec64[1];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[2] = dsp->fRec75[1];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[2] = dsp->fRec74[1];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec72[2] = dsp->fRec72[1];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec71[2] = dsp->fRec71[1];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec83[2] = dsp->fRec83[1];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[2] = dsp->fRec82[1];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec81[2] = dsp->fRec81[1];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec80[2] = dsp->fRec80[1];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec79[2] = dsp->fRec79[1];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec78[2] = dsp->fRec78[1];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec90[2] = dsp->fRec90[1];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec88[2] = dsp->fRec88[1];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec87[2] = dsp->fRec87[1];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[2] = dsp->fRec86[1];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec97[2] = dsp->fRec97[1];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec95[2] = dsp->fRec95[1];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec94[2] = dsp->fRec94[1];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[2] = dsp->fRec93[1];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec92[2] = dsp->fRec92[1];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec104[2] = dsp->fRec104[1];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec103[2] = dsp->fRec103[1];
			dsp->fRec103[1] = dsp->fRec103[0];
			dsp->fRec102[2] = dsp->fRec102[1];
			dsp->fRec102[1] = dsp->fRec102[0];
			dsp->fRec101[2] = dsp->fRec101[1];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->fRec100[2] = dsp->fRec100[1];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec99[2] = dsp->fRec99[1];
			dsp->fRec99[1] = dsp->fRec99[0];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec111[2] = dsp->fRec111[1];
			dsp->fRec111[1] = dsp->fRec111[0];
			dsp->fRec110[2] = dsp->fRec110[1];
			dsp->fRec110[1] = dsp->fRec110[0];
			dsp->fRec109[2] = dsp->fRec109[1];
			dsp->fRec109[1] = dsp->fRec109[0];
			dsp->fRec108[2] = dsp->fRec108[1];
			dsp->fRec108[1] = dsp->fRec108[0];
			dsp->fRec107[2] = dsp->fRec107[1];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->fRec106[2] = dsp->fRec106[1];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec115[2] = dsp->fRec115[1];
			dsp->fRec115[1] = dsp->fRec115[0];
			dsp->fRec114[2] = dsp->fRec114[1];
			dsp->fRec114[1] = dsp->fRec114[0];
			dsp->fRec113[2] = dsp->fRec113[1];
			dsp->fRec113[1] = dsp->fRec113[0];
			dsp->fRec112[1] = dsp->fRec112[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
