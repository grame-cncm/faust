/* ------------------------------------------------------------
name: "phaserFlangerLab"
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
static float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
	
}
static float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
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
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider3;
	float fConst14;
	FAUSTFLOAT fHslider4;
	float fRec4[2];
	float fRec5[2];
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fVslider0;
	float fRec6[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fEntry0;
	float fConst15;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec8[2];
	float fVec1[2];
	float fRec7[2];
	float fConst16;
	float fVec2[2];
	float fConst17;
	float fVec3[2];
	float fVec4[2];
	float fConst18;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec9[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec10[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox4;
	int iRec11[2];
	float fRec12[4];
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	int IOTA;
	float fVec22[4096];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec13[2];
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	float fRec19[2];
	float fRec20[2];
	float fRec18[3];
	float fRec17[3];
	float fRec16[3];
	float fRec15[3];
	float fRec14[2];
	FAUSTFLOAT fCheckbox7;
	float fVec23[4096];
	float fRec21[2];
	float fRec26[3];
	float fRec25[3];
	float fRec24[3];
	float fRec23[3];
	float fRec22[2];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec3[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec2[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec1[3];
	float fConst28;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst29;
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
	float fRec33[3];
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec32[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec31[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec30[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec29[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec28[3];
	float fConst66;
	float fRec27[2];
	FAUSTFLOAT fVbargraph1;
	float fConst67;
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
	float fRec40[3];
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec39[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec38[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec37[3];
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec36[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec35[3];
	float fConst104;
	float fRec34[2];
	FAUSTFLOAT fVbargraph2;
	float fConst105;
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
	float fRec47[3];
	float fConst126;
	float fConst127;
	float fConst128;
	float fRec46[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec45[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec44[3];
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec43[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec42[3];
	float fConst142;
	float fRec41[2];
	FAUSTFLOAT fVbargraph3;
	float fConst143;
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
	float fRec54[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec53[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec52[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fRec51[3];
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec50[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec49[3];
	float fConst180;
	float fRec48[2];
	FAUSTFLOAT fVbargraph4;
	float fConst181;
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
	float fRec61[3];
	float fConst202;
	float fConst203;
	float fConst204;
	float fRec60[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec59[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fRec58[3];
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec57[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec56[3];
	float fConst218;
	float fRec55[2];
	FAUSTFLOAT fVbargraph5;
	float fConst219;
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
	float fRec68[3];
	float fConst240;
	float fConst241;
	float fConst242;
	float fRec67[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec66[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fConst249;
	float fRec65[3];
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec64[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec63[3];
	float fConst256;
	float fRec62[2];
	FAUSTFLOAT fVbargraph6;
	float fConst257;
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
	float fRec75[3];
	float fConst278;
	float fConst279;
	float fConst280;
	float fRec74[3];
	float fConst281;
	float fConst282;
	float fConst283;
	float fRec73[3];
	float fConst284;
	float fConst285;
	float fConst286;
	float fConst287;
	float fRec72[3];
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec71[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec70[3];
	float fConst294;
	float fRec69[2];
	FAUSTFLOAT fVbargraph7;
	float fConst295;
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
	float fRec82[3];
	float fConst316;
	float fConst317;
	float fConst318;
	float fRec81[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec80[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fConst325;
	float fRec79[3];
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec78[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec77[3];
	float fConst332;
	float fRec76[2];
	FAUSTFLOAT fVbargraph8;
	float fConst333;
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
	float fRec89[3];
	float fConst354;
	float fConst355;
	float fConst356;
	float fRec88[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec87[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fConst363;
	float fRec86[3];
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec85[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec84[3];
	float fConst370;
	float fRec83[2];
	FAUSTFLOAT fVbargraph9;
	float fConst371;
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
	float fRec96[3];
	float fConst392;
	float fConst393;
	float fConst394;
	float fRec95[3];
	float fConst395;
	float fConst396;
	float fConst397;
	float fRec94[3];
	float fConst398;
	float fConst399;
	float fConst400;
	float fConst401;
	float fRec93[3];
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec92[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec91[3];
	float fConst408;
	float fRec90[2];
	FAUSTFLOAT fVbargraph10;
	float fConst409;
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
	float fRec103[3];
	float fConst430;
	float fConst431;
	float fConst432;
	float fRec102[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec101[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fRec100[3];
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec99[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec98[3];
	float fConst446;
	float fRec97[2];
	FAUSTFLOAT fVbargraph11;
	float fConst447;
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
	float fRec110[3];
	float fConst468;
	float fConst469;
	float fConst470;
	float fRec109[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec108[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fRec107[3];
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec106[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec105[3];
	float fConst484;
	float fRec104[2];
	FAUSTFLOAT fVbargraph12;
	float fConst485;
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
	float fRec117[3];
	float fConst506;
	float fConst507;
	float fConst508;
	float fRec116[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec115[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fRec114[3];
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec113[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec112[3];
	float fConst522;
	float fRec111[2];
	FAUSTFLOAT fVbargraph13;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fRec121[3];
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec120[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec119[3];
	float fConst538;
	float fRec118[2];
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
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "phaserFlangerLab");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "phaflangers.lib/name", "Faust Phaser and Flanger Library");
	m->declare(m->metaInterface, "phaflangers.lib/version", "0.0");
	m->declare(m->metaInterface, "routes.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "routes.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
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
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)50.0f;
	dsp->fHslider1 = (FAUSTFLOAT)100.0f;
	dsp->fCheckbox0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.5f;
	dsp->fVslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox3 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fVslider1 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fCheckbox4 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox5 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)1.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider7 = (FAUSTFLOAT)1.0f;
	dsp->fHslider8 = (FAUSTFLOAT)10.0f;
	dsp->fCheckbox6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider9 = (FAUSTFLOAT)1.0f;
	dsp->fHslider10 = (FAUSTFLOAT)1000.0f;
	dsp->fHslider11 = (FAUSTFLOAT)0.0f;
	dsp->fHslider12 = (FAUSTFLOAT)1.5f;
	dsp->fHslider13 = (FAUSTFLOAT)100.0f;
	dsp->fHslider14 = (FAUSTFLOAT)800.0f;
	dsp->fHslider15 = (FAUSTFLOAT)0.5f;
	dsp->fCheckbox7 = (FAUSTFLOAT)0.0f;
	
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
			dsp->fRec4[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec5[l2] = 0.0f;
			
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
			dsp->fRec8[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fVec1[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec7[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec2[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec3[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec4[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec5[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec6[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fVec7[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec8[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec9[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec9[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec10[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec11[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec12[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec13[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fVec14[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec15[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec10[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fVec16[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec17[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec18[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec19[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fVec20[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fVec21[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->iRec11[l29] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 4); l30 = (l30 + 1)) {
			dsp->fRec12[l30] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			dsp->fVec22[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec13[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec19[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec20[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec18[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec17[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			dsp->fRec16[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec15[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec14[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 4096); l40 = (l40 + 1)) {
			dsp->fVec23[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec21[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec26[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec25[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec24[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			dsp->fRec23[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec22[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec3[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec2[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec1[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec0[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec33[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec32[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec31[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec30[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec29[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec28[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec27[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec40[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			dsp->fRec39[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec38[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			dsp->fRec37[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec36[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec35[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			dsp->fRec34[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec47[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			dsp->fRec46[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec45[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec44[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec43[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			dsp->fRec42[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			dsp->fRec41[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec54[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			dsp->fRec53[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			dsp->fRec52[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec51[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec50[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			dsp->fRec49[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			dsp->fRec48[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec61[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			dsp->fRec60[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec59[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec58[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec57[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			dsp->fRec56[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			dsp->fRec55[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec68[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			dsp->fRec67[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec66[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec65[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec64[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			dsp->fRec63[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			dsp->fRec62[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec75[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			dsp->fRec74[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec73[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec72[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			dsp->fRec71[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			dsp->fRec70[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			dsp->fRec69[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			dsp->fRec82[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			dsp->fRec81[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			dsp->fRec80[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec79[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			dsp->fRec78[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			dsp->fRec77[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			dsp->fRec76[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec89[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			dsp->fRec88[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			dsp->fRec87[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			dsp->fRec86[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			dsp->fRec85[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			dsp->fRec84[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			dsp->fRec83[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			dsp->fRec96[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			dsp->fRec95[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			dsp->fRec94[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			dsp->fRec93[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			dsp->fRec92[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			dsp->fRec91[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			dsp->fRec90[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			dsp->fRec103[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			dsp->fRec102[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec101[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			dsp->fRec100[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			dsp->fRec99[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			dsp->fRec98[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			dsp->fRec97[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec110[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			dsp->fRec109[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			dsp->fRec108[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			dsp->fRec107[l131] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l132;
		for (l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			dsp->fRec106[l132] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l133;
		for (l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			dsp->fRec105[l133] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l134;
		for (l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			dsp->fRec104[l134] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l135;
		for (l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			dsp->fRec117[l135] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l136;
		for (l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			dsp->fRec116[l136] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l137;
		for (l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			dsp->fRec115[l137] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l138;
		for (l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			dsp->fRec114[l138] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l139;
		for (l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			dsp->fRec113[l139] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l140;
		for (l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			dsp->fRec112[l140] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l141;
		for (l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			dsp->fRec111[l141] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l142;
		for (l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			dsp->fRec121[l142] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l143;
		for (l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			dsp->fRec120[l143] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l144;
		for (l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			dsp->fRec119[l144] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l145;
		for (l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			dsp->fRec118[l145] = 0.0f;
			
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
	dsp->fConst14 = (6.28318548f / dsp->fConst0);
	dsp->fConst15 = (1.0f / dsp->fConst0);
	dsp->fConst16 = (0.25f * dsp->fConst0);
	dsp->fConst17 = (0.0416666679f * mydsp_faustpower2_f(dsp->fConst0));
	dsp->fConst18 = (0.00520833349f * mydsp_faustpower3_f(dsp->fConst0));
	dsp->fConst19 = (((dsp->fConst3 + -3.18972731f) / dsp->fConst2) + 4.07678175f);
	dsp->fConst20 = (1.0f / dsp->fConst5);
	dsp->fConst21 = (2.0f * (4.07678175f - dsp->fConst20));
	dsp->fConst22 = (dsp->fConst12 + 0.000407678192f);
	dsp->fConst23 = (((dsp->fConst3 + -0.743130445f) / dsp->fConst2) + 1.4500711f);
	dsp->fConst24 = (2.0f * (1.4500711f - dsp->fConst20));
	dsp->fConst25 = (dsp->fConst9 + 1.4500711f);
	dsp->fConst26 = (((dsp->fConst3 + -0.157482162f) / dsp->fConst2) + 0.935140193f);
	dsp->fConst27 = (2.0f * (0.935140193f - dsp->fConst20));
	dsp->fConst28 = (dsp->fConst6 + 0.935140193f);
	dsp->fConst29 = tanf((31665.2695f / dsp->fConst0));
	dsp->fConst30 = (1.0f / dsp->fConst29);
	dsp->fConst31 = (1.0f / (((dsp->fConst30 + 0.157482162f) / dsp->fConst29) + 0.935140193f));
	dsp->fConst32 = mydsp_faustpower2_f(dsp->fConst29);
	dsp->fConst33 = (50.0638084f / dsp->fConst32);
	dsp->fConst34 = (2.0f * (0.935140193f - dsp->fConst33));
	dsp->fConst35 = (1.0f / (((dsp->fConst30 + 0.743130445f) / dsp->fConst29) + 1.4500711f));
	dsp->fConst36 = (11.0520525f / dsp->fConst32);
	dsp->fConst37 = (2.0f * (1.4500711f - dsp->fConst36));
	dsp->fConst38 = (1.0f / (((dsp->fConst30 + 3.18972731f) / dsp->fConst29) + 4.07678175f));
	dsp->fConst39 = (0.00176617282f / dsp->fConst32);
	dsp->fConst40 = (2.0f * (0.000407678192f - dsp->fConst39));
	dsp->fConst41 = (1.0f / (((dsp->fConst3 + 0.168404877f) / dsp->fConst2) + 1.06935835f));
	dsp->fConst42 = (2.0f * (53.5361519f - dsp->fConst20));
	dsp->fConst43 = (1.0f / (((dsp->fConst3 + 0.51247865f) / dsp->fConst2) + 0.689621389f));
	dsp->fConst44 = (2.0f * (7.62173128f - dsp->fConst20));
	dsp->fConst45 = (1.0f / (((dsp->fConst3 + 0.782413065f) / dsp->fConst2) + 0.245291501f));
	dsp->fConst46 = (9.99999975e-05f / dsp->fConst5);
	dsp->fConst47 = (2.0f * (0.000433227193f - dsp->fConst46));
	dsp->fConst48 = (((dsp->fConst3 + -0.782413065f) / dsp->fConst2) + 0.245291501f);
	dsp->fConst49 = (2.0f * (0.245291501f - dsp->fConst20));
	dsp->fConst50 = (dsp->fConst46 + 0.000433227193f);
	dsp->fConst51 = (((dsp->fConst3 + -0.51247865f) / dsp->fConst2) + 0.689621389f);
	dsp->fConst52 = (2.0f * (0.689621389f - dsp->fConst20));
	dsp->fConst53 = (dsp->fConst20 + 7.62173128f);
	dsp->fConst54 = (((dsp->fConst3 + -0.168404877f) / dsp->fConst2) + 1.06935835f);
	dsp->fConst55 = (2.0f * (1.06935835f - dsp->fConst20));
	dsp->fConst56 = (dsp->fConst20 + 53.5361519f);
	dsp->fConst57 = (((dsp->fConst30 + -3.18972731f) / dsp->fConst29) + 4.07678175f);
	dsp->fConst58 = (1.0f / dsp->fConst32);
	dsp->fConst59 = (2.0f * (4.07678175f - dsp->fConst58));
	dsp->fConst60 = (dsp->fConst39 + 0.000407678192f);
	dsp->fConst61 = (((dsp->fConst30 + -0.743130445f) / dsp->fConst29) + 1.4500711f);
	dsp->fConst62 = (2.0f * (1.4500711f - dsp->fConst58));
	dsp->fConst63 = (dsp->fConst36 + 1.4500711f);
	dsp->fConst64 = (((dsp->fConst30 + -0.157482162f) / dsp->fConst29) + 0.935140193f);
	dsp->fConst65 = (2.0f * (0.935140193f - dsp->fConst58));
	dsp->fConst66 = (dsp->fConst33 + 0.935140193f);
	dsp->fConst67 = tanf((19947.8691f / dsp->fConst0));
	dsp->fConst68 = (1.0f / dsp->fConst67);
	dsp->fConst69 = (1.0f / (((dsp->fConst68 + 0.157482162f) / dsp->fConst67) + 0.935140193f));
	dsp->fConst70 = mydsp_faustpower2_f(dsp->fConst67);
	dsp->fConst71 = (50.0638084f / dsp->fConst70);
	dsp->fConst72 = (2.0f * (0.935140193f - dsp->fConst71));
	dsp->fConst73 = (1.0f / (((dsp->fConst68 + 0.743130445f) / dsp->fConst67) + 1.4500711f));
	dsp->fConst74 = (11.0520525f / dsp->fConst70);
	dsp->fConst75 = (2.0f * (1.4500711f - dsp->fConst74));
	dsp->fConst76 = (1.0f / (((dsp->fConst68 + 3.18972731f) / dsp->fConst67) + 4.07678175f));
	dsp->fConst77 = (0.00176617282f / dsp->fConst70);
	dsp->fConst78 = (2.0f * (0.000407678192f - dsp->fConst77));
	dsp->fConst79 = (1.0f / (((dsp->fConst30 + 0.168404877f) / dsp->fConst29) + 1.06935835f));
	dsp->fConst80 = (2.0f * (53.5361519f - dsp->fConst58));
	dsp->fConst81 = (1.0f / (((dsp->fConst30 + 0.51247865f) / dsp->fConst29) + 0.689621389f));
	dsp->fConst82 = (2.0f * (7.62173128f - dsp->fConst58));
	dsp->fConst83 = (1.0f / (((dsp->fConst30 + 0.782413065f) / dsp->fConst29) + 0.245291501f));
	dsp->fConst84 = (9.99999975e-05f / dsp->fConst32);
	dsp->fConst85 = (2.0f * (0.000433227193f - dsp->fConst84));
	dsp->fConst86 = (((dsp->fConst30 + -0.782413065f) / dsp->fConst29) + 0.245291501f);
	dsp->fConst87 = (2.0f * (0.245291501f - dsp->fConst58));
	dsp->fConst88 = (dsp->fConst84 + 0.000433227193f);
	dsp->fConst89 = (((dsp->fConst30 + -0.51247865f) / dsp->fConst29) + 0.689621389f);
	dsp->fConst90 = (2.0f * (0.689621389f - dsp->fConst58));
	dsp->fConst91 = (dsp->fConst58 + 7.62173128f);
	dsp->fConst92 = (((dsp->fConst30 + -0.168404877f) / dsp->fConst29) + 1.06935835f);
	dsp->fConst93 = (2.0f * (1.06935835f - dsp->fConst58));
	dsp->fConst94 = (dsp->fConst58 + 53.5361519f);
	dsp->fConst95 = (((dsp->fConst68 + -3.18972731f) / dsp->fConst67) + 4.07678175f);
	dsp->fConst96 = (1.0f / dsp->fConst70);
	dsp->fConst97 = (2.0f * (4.07678175f - dsp->fConst96));
	dsp->fConst98 = (dsp->fConst77 + 0.000407678192f);
	dsp->fConst99 = (((dsp->fConst68 + -0.743130445f) / dsp->fConst67) + 1.4500711f);
	dsp->fConst100 = (2.0f * (1.4500711f - dsp->fConst96));
	dsp->fConst101 = (dsp->fConst74 + 1.4500711f);
	dsp->fConst102 = (((dsp->fConst68 + -0.157482162f) / dsp->fConst67) + 0.935140193f);
	dsp->fConst103 = (2.0f * (0.935140193f - dsp->fConst96));
	dsp->fConst104 = (dsp->fConst71 + 0.935140193f);
	dsp->fConst105 = tanf((12566.3711f / dsp->fConst0));
	dsp->fConst106 = (1.0f / dsp->fConst105);
	dsp->fConst107 = (1.0f / (((dsp->fConst106 + 0.157482162f) / dsp->fConst105) + 0.935140193f));
	dsp->fConst108 = mydsp_faustpower2_f(dsp->fConst105);
	dsp->fConst109 = (50.0638084f / dsp->fConst108);
	dsp->fConst110 = (2.0f * (0.935140193f - dsp->fConst109));
	dsp->fConst111 = (1.0f / (((dsp->fConst106 + 0.743130445f) / dsp->fConst105) + 1.4500711f));
	dsp->fConst112 = (11.0520525f / dsp->fConst108);
	dsp->fConst113 = (2.0f * (1.4500711f - dsp->fConst112));
	dsp->fConst114 = (1.0f / (((dsp->fConst106 + 3.18972731f) / dsp->fConst105) + 4.07678175f));
	dsp->fConst115 = (0.00176617282f / dsp->fConst108);
	dsp->fConst116 = (2.0f * (0.000407678192f - dsp->fConst115));
	dsp->fConst117 = (1.0f / (((dsp->fConst68 + 0.168404877f) / dsp->fConst67) + 1.06935835f));
	dsp->fConst118 = (2.0f * (53.5361519f - dsp->fConst96));
	dsp->fConst119 = (1.0f / (((dsp->fConst68 + 0.51247865f) / dsp->fConst67) + 0.689621389f));
	dsp->fConst120 = (2.0f * (7.62173128f - dsp->fConst96));
	dsp->fConst121 = (1.0f / (((dsp->fConst68 + 0.782413065f) / dsp->fConst67) + 0.245291501f));
	dsp->fConst122 = (9.99999975e-05f / dsp->fConst70);
	dsp->fConst123 = (2.0f * (0.000433227193f - dsp->fConst122));
	dsp->fConst124 = (((dsp->fConst68 + -0.782413065f) / dsp->fConst67) + 0.245291501f);
	dsp->fConst125 = (2.0f * (0.245291501f - dsp->fConst96));
	dsp->fConst126 = (dsp->fConst122 + 0.000433227193f);
	dsp->fConst127 = (((dsp->fConst68 + -0.51247865f) / dsp->fConst67) + 0.689621389f);
	dsp->fConst128 = (2.0f * (0.689621389f - dsp->fConst96));
	dsp->fConst129 = (dsp->fConst96 + 7.62173128f);
	dsp->fConst130 = (((dsp->fConst68 + -0.168404877f) / dsp->fConst67) + 1.06935835f);
	dsp->fConst131 = (2.0f * (1.06935835f - dsp->fConst96));
	dsp->fConst132 = (dsp->fConst96 + 53.5361519f);
	dsp->fConst133 = (((dsp->fConst106 + -3.18972731f) / dsp->fConst105) + 4.07678175f);
	dsp->fConst134 = (1.0f / dsp->fConst108);
	dsp->fConst135 = (2.0f * (4.07678175f - dsp->fConst134));
	dsp->fConst136 = (dsp->fConst115 + 0.000407678192f);
	dsp->fConst137 = (((dsp->fConst106 + -0.743130445f) / dsp->fConst105) + 1.4500711f);
	dsp->fConst138 = (2.0f * (1.4500711f - dsp->fConst134));
	dsp->fConst139 = (dsp->fConst112 + 1.4500711f);
	dsp->fConst140 = (((dsp->fConst106 + -0.157482162f) / dsp->fConst105) + 0.935140193f);
	dsp->fConst141 = (2.0f * (0.935140193f - dsp->fConst134));
	dsp->fConst142 = (dsp->fConst109 + 0.935140193f);
	dsp->fConst143 = tanf((7916.31738f / dsp->fConst0));
	dsp->fConst144 = (1.0f / dsp->fConst143);
	dsp->fConst145 = (1.0f / (((dsp->fConst144 + 0.157482162f) / dsp->fConst143) + 0.935140193f));
	dsp->fConst146 = mydsp_faustpower2_f(dsp->fConst143);
	dsp->fConst147 = (50.0638084f / dsp->fConst146);
	dsp->fConst148 = (2.0f * (0.935140193f - dsp->fConst147));
	dsp->fConst149 = (1.0f / (((dsp->fConst144 + 0.743130445f) / dsp->fConst143) + 1.4500711f));
	dsp->fConst150 = (11.0520525f / dsp->fConst146);
	dsp->fConst151 = (2.0f * (1.4500711f - dsp->fConst150));
	dsp->fConst152 = (1.0f / (((dsp->fConst144 + 3.18972731f) / dsp->fConst143) + 4.07678175f));
	dsp->fConst153 = (0.00176617282f / dsp->fConst146);
	dsp->fConst154 = (2.0f * (0.000407678192f - dsp->fConst153));
	dsp->fConst155 = (1.0f / (((dsp->fConst106 + 0.168404877f) / dsp->fConst105) + 1.06935835f));
	dsp->fConst156 = (2.0f * (53.5361519f - dsp->fConst134));
	dsp->fConst157 = (1.0f / (((dsp->fConst106 + 0.51247865f) / dsp->fConst105) + 0.689621389f));
	dsp->fConst158 = (2.0f * (7.62173128f - dsp->fConst134));
	dsp->fConst159 = (1.0f / (((dsp->fConst106 + 0.782413065f) / dsp->fConst105) + 0.245291501f));
	dsp->fConst160 = (9.99999975e-05f / dsp->fConst108);
	dsp->fConst161 = (2.0f * (0.000433227193f - dsp->fConst160));
	dsp->fConst162 = (((dsp->fConst106 + -0.782413065f) / dsp->fConst105) + 0.245291501f);
	dsp->fConst163 = (2.0f * (0.245291501f - dsp->fConst134));
	dsp->fConst164 = (dsp->fConst160 + 0.000433227193f);
	dsp->fConst165 = (((dsp->fConst106 + -0.51247865f) / dsp->fConst105) + 0.689621389f);
	dsp->fConst166 = (2.0f * (0.689621389f - dsp->fConst134));
	dsp->fConst167 = (dsp->fConst134 + 7.62173128f);
	dsp->fConst168 = (((dsp->fConst106 + -0.168404877f) / dsp->fConst105) + 1.06935835f);
	dsp->fConst169 = (2.0f * (1.06935835f - dsp->fConst134));
	dsp->fConst170 = (dsp->fConst134 + 53.5361519f);
	dsp->fConst171 = (((dsp->fConst144 + -3.18972731f) / dsp->fConst143) + 4.07678175f);
	dsp->fConst172 = (1.0f / dsp->fConst146);
	dsp->fConst173 = (2.0f * (4.07678175f - dsp->fConst172));
	dsp->fConst174 = (dsp->fConst153 + 0.000407678192f);
	dsp->fConst175 = (((dsp->fConst144 + -0.743130445f) / dsp->fConst143) + 1.4500711f);
	dsp->fConst176 = (2.0f * (1.4500711f - dsp->fConst172));
	dsp->fConst177 = (dsp->fConst150 + 1.4500711f);
	dsp->fConst178 = (((dsp->fConst144 + -0.157482162f) / dsp->fConst143) + 0.935140193f);
	dsp->fConst179 = (2.0f * (0.935140193f - dsp->fConst172));
	dsp->fConst180 = (dsp->fConst147 + 0.935140193f);
	dsp->fConst181 = tanf((4986.96729f / dsp->fConst0));
	dsp->fConst182 = (1.0f / dsp->fConst181);
	dsp->fConst183 = (1.0f / (((dsp->fConst182 + 0.157482162f) / dsp->fConst181) + 0.935140193f));
	dsp->fConst184 = mydsp_faustpower2_f(dsp->fConst181);
	dsp->fConst185 = (50.0638084f / dsp->fConst184);
	dsp->fConst186 = (2.0f * (0.935140193f - dsp->fConst185));
	dsp->fConst187 = (1.0f / (((dsp->fConst182 + 0.743130445f) / dsp->fConst181) + 1.4500711f));
	dsp->fConst188 = (11.0520525f / dsp->fConst184);
	dsp->fConst189 = (2.0f * (1.4500711f - dsp->fConst188));
	dsp->fConst190 = (1.0f / (((dsp->fConst182 + 3.18972731f) / dsp->fConst181) + 4.07678175f));
	dsp->fConst191 = (0.00176617282f / dsp->fConst184);
	dsp->fConst192 = (2.0f * (0.000407678192f - dsp->fConst191));
	dsp->fConst193 = (1.0f / (((dsp->fConst144 + 0.168404877f) / dsp->fConst143) + 1.06935835f));
	dsp->fConst194 = (2.0f * (53.5361519f - dsp->fConst172));
	dsp->fConst195 = (1.0f / (((dsp->fConst144 + 0.51247865f) / dsp->fConst143) + 0.689621389f));
	dsp->fConst196 = (2.0f * (7.62173128f - dsp->fConst172));
	dsp->fConst197 = (1.0f / (((dsp->fConst144 + 0.782413065f) / dsp->fConst143) + 0.245291501f));
	dsp->fConst198 = (9.99999975e-05f / dsp->fConst146);
	dsp->fConst199 = (2.0f * (0.000433227193f - dsp->fConst198));
	dsp->fConst200 = (((dsp->fConst144 + -0.782413065f) / dsp->fConst143) + 0.245291501f);
	dsp->fConst201 = (2.0f * (0.245291501f - dsp->fConst172));
	dsp->fConst202 = (dsp->fConst198 + 0.000433227193f);
	dsp->fConst203 = (((dsp->fConst144 + -0.51247865f) / dsp->fConst143) + 0.689621389f);
	dsp->fConst204 = (2.0f * (0.689621389f - dsp->fConst172));
	dsp->fConst205 = (dsp->fConst172 + 7.62173128f);
	dsp->fConst206 = (((dsp->fConst144 + -0.168404877f) / dsp->fConst143) + 1.06935835f);
	dsp->fConst207 = (2.0f * (1.06935835f - dsp->fConst172));
	dsp->fConst208 = (dsp->fConst172 + 53.5361519f);
	dsp->fConst209 = (((dsp->fConst182 + -3.18972731f) / dsp->fConst181) + 4.07678175f);
	dsp->fConst210 = (1.0f / dsp->fConst184);
	dsp->fConst211 = (2.0f * (4.07678175f - dsp->fConst210));
	dsp->fConst212 = (dsp->fConst191 + 0.000407678192f);
	dsp->fConst213 = (((dsp->fConst182 + -0.743130445f) / dsp->fConst181) + 1.4500711f);
	dsp->fConst214 = (2.0f * (1.4500711f - dsp->fConst210));
	dsp->fConst215 = (dsp->fConst188 + 1.4500711f);
	dsp->fConst216 = (((dsp->fConst182 + -0.157482162f) / dsp->fConst181) + 0.935140193f);
	dsp->fConst217 = (2.0f * (0.935140193f - dsp->fConst210));
	dsp->fConst218 = (dsp->fConst185 + 0.935140193f);
	dsp->fConst219 = tanf((3141.59277f / dsp->fConst0));
	dsp->fConst220 = (1.0f / dsp->fConst219);
	dsp->fConst221 = (1.0f / (((dsp->fConst220 + 0.157482162f) / dsp->fConst219) + 0.935140193f));
	dsp->fConst222 = mydsp_faustpower2_f(dsp->fConst219);
	dsp->fConst223 = (50.0638084f / dsp->fConst222);
	dsp->fConst224 = (2.0f * (0.935140193f - dsp->fConst223));
	dsp->fConst225 = (1.0f / (((dsp->fConst220 + 0.743130445f) / dsp->fConst219) + 1.4500711f));
	dsp->fConst226 = (11.0520525f / dsp->fConst222);
	dsp->fConst227 = (2.0f * (1.4500711f - dsp->fConst226));
	dsp->fConst228 = (1.0f / (((dsp->fConst220 + 3.18972731f) / dsp->fConst219) + 4.07678175f));
	dsp->fConst229 = (0.00176617282f / dsp->fConst222);
	dsp->fConst230 = (2.0f * (0.000407678192f - dsp->fConst229));
	dsp->fConst231 = (1.0f / (((dsp->fConst182 + 0.168404877f) / dsp->fConst181) + 1.06935835f));
	dsp->fConst232 = (2.0f * (53.5361519f - dsp->fConst210));
	dsp->fConst233 = (1.0f / (((dsp->fConst182 + 0.51247865f) / dsp->fConst181) + 0.689621389f));
	dsp->fConst234 = (2.0f * (7.62173128f - dsp->fConst210));
	dsp->fConst235 = (1.0f / (((dsp->fConst182 + 0.782413065f) / dsp->fConst181) + 0.245291501f));
	dsp->fConst236 = (9.99999975e-05f / dsp->fConst184);
	dsp->fConst237 = (2.0f * (0.000433227193f - dsp->fConst236));
	dsp->fConst238 = (((dsp->fConst182 + -0.782413065f) / dsp->fConst181) + 0.245291501f);
	dsp->fConst239 = (2.0f * (0.245291501f - dsp->fConst210));
	dsp->fConst240 = (dsp->fConst236 + 0.000433227193f);
	dsp->fConst241 = (((dsp->fConst182 + -0.51247865f) / dsp->fConst181) + 0.689621389f);
	dsp->fConst242 = (2.0f * (0.689621389f - dsp->fConst210));
	dsp->fConst243 = (dsp->fConst210 + 7.62173128f);
	dsp->fConst244 = (((dsp->fConst182 + -0.168404877f) / dsp->fConst181) + 1.06935835f);
	dsp->fConst245 = (2.0f * (1.06935835f - dsp->fConst210));
	dsp->fConst246 = (dsp->fConst210 + 53.5361519f);
	dsp->fConst247 = (((dsp->fConst220 + -3.18972731f) / dsp->fConst219) + 4.07678175f);
	dsp->fConst248 = (1.0f / dsp->fConst222);
	dsp->fConst249 = (2.0f * (4.07678175f - dsp->fConst248));
	dsp->fConst250 = (dsp->fConst229 + 0.000407678192f);
	dsp->fConst251 = (((dsp->fConst220 + -0.743130445f) / dsp->fConst219) + 1.4500711f);
	dsp->fConst252 = (2.0f * (1.4500711f - dsp->fConst248));
	dsp->fConst253 = (dsp->fConst226 + 1.4500711f);
	dsp->fConst254 = (((dsp->fConst220 + -0.157482162f) / dsp->fConst219) + 0.935140193f);
	dsp->fConst255 = (2.0f * (0.935140193f - dsp->fConst248));
	dsp->fConst256 = (dsp->fConst223 + 0.935140193f);
	dsp->fConst257 = tanf((1979.07935f / dsp->fConst0));
	dsp->fConst258 = (1.0f / dsp->fConst257);
	dsp->fConst259 = (1.0f / (((dsp->fConst258 + 0.157482162f) / dsp->fConst257) + 0.935140193f));
	dsp->fConst260 = mydsp_faustpower2_f(dsp->fConst257);
	dsp->fConst261 = (50.0638084f / dsp->fConst260);
	dsp->fConst262 = (2.0f * (0.935140193f - dsp->fConst261));
	dsp->fConst263 = (1.0f / (((dsp->fConst258 + 0.743130445f) / dsp->fConst257) + 1.4500711f));
	dsp->fConst264 = (11.0520525f / dsp->fConst260);
	dsp->fConst265 = (2.0f * (1.4500711f - dsp->fConst264));
	dsp->fConst266 = (1.0f / (((dsp->fConst258 + 3.18972731f) / dsp->fConst257) + 4.07678175f));
	dsp->fConst267 = (0.00176617282f / dsp->fConst260);
	dsp->fConst268 = (2.0f * (0.000407678192f - dsp->fConst267));
	dsp->fConst269 = (1.0f / (((dsp->fConst220 + 0.168404877f) / dsp->fConst219) + 1.06935835f));
	dsp->fConst270 = (2.0f * (53.5361519f - dsp->fConst248));
	dsp->fConst271 = (1.0f / (((dsp->fConst220 + 0.51247865f) / dsp->fConst219) + 0.689621389f));
	dsp->fConst272 = (2.0f * (7.62173128f - dsp->fConst248));
	dsp->fConst273 = (1.0f / (((dsp->fConst220 + 0.782413065f) / dsp->fConst219) + 0.245291501f));
	dsp->fConst274 = (9.99999975e-05f / dsp->fConst222);
	dsp->fConst275 = (2.0f * (0.000433227193f - dsp->fConst274));
	dsp->fConst276 = (((dsp->fConst220 + -0.782413065f) / dsp->fConst219) + 0.245291501f);
	dsp->fConst277 = (2.0f * (0.245291501f - dsp->fConst248));
	dsp->fConst278 = (dsp->fConst274 + 0.000433227193f);
	dsp->fConst279 = (((dsp->fConst220 + -0.51247865f) / dsp->fConst219) + 0.689621389f);
	dsp->fConst280 = (2.0f * (0.689621389f - dsp->fConst248));
	dsp->fConst281 = (dsp->fConst248 + 7.62173128f);
	dsp->fConst282 = (((dsp->fConst220 + -0.168404877f) / dsp->fConst219) + 1.06935835f);
	dsp->fConst283 = (2.0f * (1.06935835f - dsp->fConst248));
	dsp->fConst284 = (dsp->fConst248 + 53.5361519f);
	dsp->fConst285 = (((dsp->fConst258 + -3.18972731f) / dsp->fConst257) + 4.07678175f);
	dsp->fConst286 = (1.0f / dsp->fConst260);
	dsp->fConst287 = (2.0f * (4.07678175f - dsp->fConst286));
	dsp->fConst288 = (dsp->fConst267 + 0.000407678192f);
	dsp->fConst289 = (((dsp->fConst258 + -0.743130445f) / dsp->fConst257) + 1.4500711f);
	dsp->fConst290 = (2.0f * (1.4500711f - dsp->fConst286));
	dsp->fConst291 = (dsp->fConst264 + 1.4500711f);
	dsp->fConst292 = (((dsp->fConst258 + -0.157482162f) / dsp->fConst257) + 0.935140193f);
	dsp->fConst293 = (2.0f * (0.935140193f - dsp->fConst286));
	dsp->fConst294 = (dsp->fConst261 + 0.935140193f);
	dsp->fConst295 = tanf((1246.74182f / dsp->fConst0));
	dsp->fConst296 = (1.0f / dsp->fConst295);
	dsp->fConst297 = (1.0f / (((dsp->fConst296 + 0.157482162f) / dsp->fConst295) + 0.935140193f));
	dsp->fConst298 = mydsp_faustpower2_f(dsp->fConst295);
	dsp->fConst299 = (50.0638084f / dsp->fConst298);
	dsp->fConst300 = (2.0f * (0.935140193f - dsp->fConst299));
	dsp->fConst301 = (1.0f / (((dsp->fConst296 + 0.743130445f) / dsp->fConst295) + 1.4500711f));
	dsp->fConst302 = (11.0520525f / dsp->fConst298);
	dsp->fConst303 = (2.0f * (1.4500711f - dsp->fConst302));
	dsp->fConst304 = (1.0f / (((dsp->fConst296 + 3.18972731f) / dsp->fConst295) + 4.07678175f));
	dsp->fConst305 = (0.00176617282f / dsp->fConst298);
	dsp->fConst306 = (2.0f * (0.000407678192f - dsp->fConst305));
	dsp->fConst307 = (1.0f / (((dsp->fConst258 + 0.168404877f) / dsp->fConst257) + 1.06935835f));
	dsp->fConst308 = (2.0f * (53.5361519f - dsp->fConst286));
	dsp->fConst309 = (1.0f / (((dsp->fConst258 + 0.51247865f) / dsp->fConst257) + 0.689621389f));
	dsp->fConst310 = (2.0f * (7.62173128f - dsp->fConst286));
	dsp->fConst311 = (1.0f / (((dsp->fConst258 + 0.782413065f) / dsp->fConst257) + 0.245291501f));
	dsp->fConst312 = (9.99999975e-05f / dsp->fConst260);
	dsp->fConst313 = (2.0f * (0.000433227193f - dsp->fConst312));
	dsp->fConst314 = (((dsp->fConst258 + -0.782413065f) / dsp->fConst257) + 0.245291501f);
	dsp->fConst315 = (2.0f * (0.245291501f - dsp->fConst286));
	dsp->fConst316 = (dsp->fConst312 + 0.000433227193f);
	dsp->fConst317 = (((dsp->fConst258 + -0.51247865f) / dsp->fConst257) + 0.689621389f);
	dsp->fConst318 = (2.0f * (0.689621389f - dsp->fConst286));
	dsp->fConst319 = (dsp->fConst286 + 7.62173128f);
	dsp->fConst320 = (((dsp->fConst258 + -0.168404877f) / dsp->fConst257) + 1.06935835f);
	dsp->fConst321 = (2.0f * (1.06935835f - dsp->fConst286));
	dsp->fConst322 = (dsp->fConst286 + 53.5361519f);
	dsp->fConst323 = (((dsp->fConst296 + -3.18972731f) / dsp->fConst295) + 4.07678175f);
	dsp->fConst324 = (1.0f / dsp->fConst298);
	dsp->fConst325 = (2.0f * (4.07678175f - dsp->fConst324));
	dsp->fConst326 = (dsp->fConst305 + 0.000407678192f);
	dsp->fConst327 = (((dsp->fConst296 + -0.743130445f) / dsp->fConst295) + 1.4500711f);
	dsp->fConst328 = (2.0f * (1.4500711f - dsp->fConst324));
	dsp->fConst329 = (dsp->fConst302 + 1.4500711f);
	dsp->fConst330 = (((dsp->fConst296 + -0.157482162f) / dsp->fConst295) + 0.935140193f);
	dsp->fConst331 = (2.0f * (0.935140193f - dsp->fConst324));
	dsp->fConst332 = (dsp->fConst299 + 0.935140193f);
	dsp->fConst333 = tanf((785.398193f / dsp->fConst0));
	dsp->fConst334 = (1.0f / dsp->fConst333);
	dsp->fConst335 = (1.0f / (((dsp->fConst334 + 0.157482162f) / dsp->fConst333) + 0.935140193f));
	dsp->fConst336 = mydsp_faustpower2_f(dsp->fConst333);
	dsp->fConst337 = (50.0638084f / dsp->fConst336);
	dsp->fConst338 = (2.0f * (0.935140193f - dsp->fConst337));
	dsp->fConst339 = (1.0f / (((dsp->fConst334 + 0.743130445f) / dsp->fConst333) + 1.4500711f));
	dsp->fConst340 = (11.0520525f / dsp->fConst336);
	dsp->fConst341 = (2.0f * (1.4500711f - dsp->fConst340));
	dsp->fConst342 = (1.0f / (((dsp->fConst334 + 3.18972731f) / dsp->fConst333) + 4.07678175f));
	dsp->fConst343 = (0.00176617282f / dsp->fConst336);
	dsp->fConst344 = (2.0f * (0.000407678192f - dsp->fConst343));
	dsp->fConst345 = (1.0f / (((dsp->fConst296 + 0.168404877f) / dsp->fConst295) + 1.06935835f));
	dsp->fConst346 = (2.0f * (53.5361519f - dsp->fConst324));
	dsp->fConst347 = (1.0f / (((dsp->fConst296 + 0.51247865f) / dsp->fConst295) + 0.689621389f));
	dsp->fConst348 = (2.0f * (7.62173128f - dsp->fConst324));
	dsp->fConst349 = (1.0f / (((dsp->fConst296 + 0.782413065f) / dsp->fConst295) + 0.245291501f));
	dsp->fConst350 = (9.99999975e-05f / dsp->fConst298);
	dsp->fConst351 = (2.0f * (0.000433227193f - dsp->fConst350));
	dsp->fConst352 = (((dsp->fConst296 + -0.782413065f) / dsp->fConst295) + 0.245291501f);
	dsp->fConst353 = (2.0f * (0.245291501f - dsp->fConst324));
	dsp->fConst354 = (dsp->fConst350 + 0.000433227193f);
	dsp->fConst355 = (((dsp->fConst296 + -0.51247865f) / dsp->fConst295) + 0.689621389f);
	dsp->fConst356 = (2.0f * (0.689621389f - dsp->fConst324));
	dsp->fConst357 = (dsp->fConst324 + 7.62173128f);
	dsp->fConst358 = (((dsp->fConst296 + -0.168404877f) / dsp->fConst295) + 1.06935835f);
	dsp->fConst359 = (2.0f * (1.06935835f - dsp->fConst324));
	dsp->fConst360 = (dsp->fConst324 + 53.5361519f);
	dsp->fConst361 = (((dsp->fConst334 + -3.18972731f) / dsp->fConst333) + 4.07678175f);
	dsp->fConst362 = (1.0f / dsp->fConst336);
	dsp->fConst363 = (2.0f * (4.07678175f - dsp->fConst362));
	dsp->fConst364 = (dsp->fConst343 + 0.000407678192f);
	dsp->fConst365 = (((dsp->fConst334 + -0.743130445f) / dsp->fConst333) + 1.4500711f);
	dsp->fConst366 = (2.0f * (1.4500711f - dsp->fConst362));
	dsp->fConst367 = (dsp->fConst340 + 1.4500711f);
	dsp->fConst368 = (((dsp->fConst334 + -0.157482162f) / dsp->fConst333) + 0.935140193f);
	dsp->fConst369 = (2.0f * (0.935140193f - dsp->fConst362));
	dsp->fConst370 = (dsp->fConst337 + 0.935140193f);
	dsp->fConst371 = tanf((494.769836f / dsp->fConst0));
	dsp->fConst372 = (1.0f / dsp->fConst371);
	dsp->fConst373 = (1.0f / (((dsp->fConst372 + 0.157482162f) / dsp->fConst371) + 0.935140193f));
	dsp->fConst374 = mydsp_faustpower2_f(dsp->fConst371);
	dsp->fConst375 = (50.0638084f / dsp->fConst374);
	dsp->fConst376 = (2.0f * (0.935140193f - dsp->fConst375));
	dsp->fConst377 = (1.0f / (((dsp->fConst372 + 0.743130445f) / dsp->fConst371) + 1.4500711f));
	dsp->fConst378 = (11.0520525f / dsp->fConst374);
	dsp->fConst379 = (2.0f * (1.4500711f - dsp->fConst378));
	dsp->fConst380 = (1.0f / (((dsp->fConst372 + 3.18972731f) / dsp->fConst371) + 4.07678175f));
	dsp->fConst381 = (0.00176617282f / dsp->fConst374);
	dsp->fConst382 = (2.0f * (0.000407678192f - dsp->fConst381));
	dsp->fConst383 = (1.0f / (((dsp->fConst334 + 0.168404877f) / dsp->fConst333) + 1.06935835f));
	dsp->fConst384 = (2.0f * (53.5361519f - dsp->fConst362));
	dsp->fConst385 = (1.0f / (((dsp->fConst334 + 0.51247865f) / dsp->fConst333) + 0.689621389f));
	dsp->fConst386 = (2.0f * (7.62173128f - dsp->fConst362));
	dsp->fConst387 = (1.0f / (((dsp->fConst334 + 0.782413065f) / dsp->fConst333) + 0.245291501f));
	dsp->fConst388 = (9.99999975e-05f / dsp->fConst336);
	dsp->fConst389 = (2.0f * (0.000433227193f - dsp->fConst388));
	dsp->fConst390 = (((dsp->fConst334 + -0.782413065f) / dsp->fConst333) + 0.245291501f);
	dsp->fConst391 = (2.0f * (0.245291501f - dsp->fConst362));
	dsp->fConst392 = (dsp->fConst388 + 0.000433227193f);
	dsp->fConst393 = (((dsp->fConst334 + -0.51247865f) / dsp->fConst333) + 0.689621389f);
	dsp->fConst394 = (2.0f * (0.689621389f - dsp->fConst362));
	dsp->fConst395 = (dsp->fConst362 + 7.62173128f);
	dsp->fConst396 = (((dsp->fConst334 + -0.168404877f) / dsp->fConst333) + 1.06935835f);
	dsp->fConst397 = (2.0f * (1.06935835f - dsp->fConst362));
	dsp->fConst398 = (dsp->fConst362 + 53.5361519f);
	dsp->fConst399 = (((dsp->fConst372 + -3.18972731f) / dsp->fConst371) + 4.07678175f);
	dsp->fConst400 = (1.0f / dsp->fConst374);
	dsp->fConst401 = (2.0f * (4.07678175f - dsp->fConst400));
	dsp->fConst402 = (dsp->fConst381 + 0.000407678192f);
	dsp->fConst403 = (((dsp->fConst372 + -0.743130445f) / dsp->fConst371) + 1.4500711f);
	dsp->fConst404 = (2.0f * (1.4500711f - dsp->fConst400));
	dsp->fConst405 = (dsp->fConst378 + 1.4500711f);
	dsp->fConst406 = (((dsp->fConst372 + -0.157482162f) / dsp->fConst371) + 0.935140193f);
	dsp->fConst407 = (2.0f * (0.935140193f - dsp->fConst400));
	dsp->fConst408 = (dsp->fConst375 + 0.935140193f);
	dsp->fConst409 = tanf((311.685455f / dsp->fConst0));
	dsp->fConst410 = (1.0f / dsp->fConst409);
	dsp->fConst411 = (1.0f / (((dsp->fConst410 + 0.157482162f) / dsp->fConst409) + 0.935140193f));
	dsp->fConst412 = mydsp_faustpower2_f(dsp->fConst409);
	dsp->fConst413 = (50.0638084f / dsp->fConst412);
	dsp->fConst414 = (2.0f * (0.935140193f - dsp->fConst413));
	dsp->fConst415 = (1.0f / (((dsp->fConst410 + 0.743130445f) / dsp->fConst409) + 1.4500711f));
	dsp->fConst416 = (11.0520525f / dsp->fConst412);
	dsp->fConst417 = (2.0f * (1.4500711f - dsp->fConst416));
	dsp->fConst418 = (1.0f / (((dsp->fConst410 + 3.18972731f) / dsp->fConst409) + 4.07678175f));
	dsp->fConst419 = (0.00176617282f / dsp->fConst412);
	dsp->fConst420 = (2.0f * (0.000407678192f - dsp->fConst419));
	dsp->fConst421 = (1.0f / (((dsp->fConst372 + 0.168404877f) / dsp->fConst371) + 1.06935835f));
	dsp->fConst422 = (2.0f * (53.5361519f - dsp->fConst400));
	dsp->fConst423 = (1.0f / (((dsp->fConst372 + 0.51247865f) / dsp->fConst371) + 0.689621389f));
	dsp->fConst424 = (2.0f * (7.62173128f - dsp->fConst400));
	dsp->fConst425 = (1.0f / (((dsp->fConst372 + 0.782413065f) / dsp->fConst371) + 0.245291501f));
	dsp->fConst426 = (9.99999975e-05f / dsp->fConst374);
	dsp->fConst427 = (2.0f * (0.000433227193f - dsp->fConst426));
	dsp->fConst428 = (((dsp->fConst372 + -0.782413065f) / dsp->fConst371) + 0.245291501f);
	dsp->fConst429 = (2.0f * (0.245291501f - dsp->fConst400));
	dsp->fConst430 = (dsp->fConst426 + 0.000433227193f);
	dsp->fConst431 = (((dsp->fConst372 + -0.51247865f) / dsp->fConst371) + 0.689621389f);
	dsp->fConst432 = (2.0f * (0.689621389f - dsp->fConst400));
	dsp->fConst433 = (dsp->fConst400 + 7.62173128f);
	dsp->fConst434 = (((dsp->fConst372 + -0.168404877f) / dsp->fConst371) + 1.06935835f);
	dsp->fConst435 = (2.0f * (1.06935835f - dsp->fConst400));
	dsp->fConst436 = (dsp->fConst400 + 53.5361519f);
	dsp->fConst437 = (((dsp->fConst410 + -3.18972731f) / dsp->fConst409) + 4.07678175f);
	dsp->fConst438 = (1.0f / dsp->fConst412);
	dsp->fConst439 = (2.0f * (4.07678175f - dsp->fConst438));
	dsp->fConst440 = (dsp->fConst419 + 0.000407678192f);
	dsp->fConst441 = (((dsp->fConst410 + -0.743130445f) / dsp->fConst409) + 1.4500711f);
	dsp->fConst442 = (2.0f * (1.4500711f - dsp->fConst438));
	dsp->fConst443 = (dsp->fConst416 + 1.4500711f);
	dsp->fConst444 = (((dsp->fConst410 + -0.157482162f) / dsp->fConst409) + 0.935140193f);
	dsp->fConst445 = (2.0f * (0.935140193f - dsp->fConst438));
	dsp->fConst446 = (dsp->fConst413 + 0.935140193f);
	dsp->fConst447 = tanf((196.349548f / dsp->fConst0));
	dsp->fConst448 = (1.0f / dsp->fConst447);
	dsp->fConst449 = (1.0f / (((dsp->fConst448 + 0.157482162f) / dsp->fConst447) + 0.935140193f));
	dsp->fConst450 = mydsp_faustpower2_f(dsp->fConst447);
	dsp->fConst451 = (50.0638084f / dsp->fConst450);
	dsp->fConst452 = (2.0f * (0.935140193f - dsp->fConst451));
	dsp->fConst453 = (1.0f / (((dsp->fConst448 + 0.743130445f) / dsp->fConst447) + 1.4500711f));
	dsp->fConst454 = (11.0520525f / dsp->fConst450);
	dsp->fConst455 = (2.0f * (1.4500711f - dsp->fConst454));
	dsp->fConst456 = (1.0f / (((dsp->fConst448 + 3.18972731f) / dsp->fConst447) + 4.07678175f));
	dsp->fConst457 = (0.00176617282f / dsp->fConst450);
	dsp->fConst458 = (2.0f * (0.000407678192f - dsp->fConst457));
	dsp->fConst459 = (1.0f / (((dsp->fConst410 + 0.168404877f) / dsp->fConst409) + 1.06935835f));
	dsp->fConst460 = (2.0f * (53.5361519f - dsp->fConst438));
	dsp->fConst461 = (1.0f / (((dsp->fConst410 + 0.51247865f) / dsp->fConst409) + 0.689621389f));
	dsp->fConst462 = (2.0f * (7.62173128f - dsp->fConst438));
	dsp->fConst463 = (1.0f / (((dsp->fConst410 + 0.782413065f) / dsp->fConst409) + 0.245291501f));
	dsp->fConst464 = (9.99999975e-05f / dsp->fConst412);
	dsp->fConst465 = (2.0f * (0.000433227193f - dsp->fConst464));
	dsp->fConst466 = (((dsp->fConst410 + -0.782413065f) / dsp->fConst409) + 0.245291501f);
	dsp->fConst467 = (2.0f * (0.245291501f - dsp->fConst438));
	dsp->fConst468 = (dsp->fConst464 + 0.000433227193f);
	dsp->fConst469 = (((dsp->fConst410 + -0.51247865f) / dsp->fConst409) + 0.689621389f);
	dsp->fConst470 = (2.0f * (0.689621389f - dsp->fConst438));
	dsp->fConst471 = (dsp->fConst438 + 7.62173128f);
	dsp->fConst472 = (((dsp->fConst410 + -0.168404877f) / dsp->fConst409) + 1.06935835f);
	dsp->fConst473 = (2.0f * (1.06935835f - dsp->fConst438));
	dsp->fConst474 = (dsp->fConst438 + 53.5361519f);
	dsp->fConst475 = (((dsp->fConst448 + -3.18972731f) / dsp->fConst447) + 4.07678175f);
	dsp->fConst476 = (1.0f / dsp->fConst450);
	dsp->fConst477 = (2.0f * (4.07678175f - dsp->fConst476));
	dsp->fConst478 = (dsp->fConst457 + 0.000407678192f);
	dsp->fConst479 = (((dsp->fConst448 + -0.743130445f) / dsp->fConst447) + 1.4500711f);
	dsp->fConst480 = (2.0f * (1.4500711f - dsp->fConst476));
	dsp->fConst481 = (dsp->fConst454 + 1.4500711f);
	dsp->fConst482 = (((dsp->fConst448 + -0.157482162f) / dsp->fConst447) + 0.935140193f);
	dsp->fConst483 = (2.0f * (0.935140193f - dsp->fConst476));
	dsp->fConst484 = (dsp->fConst451 + 0.935140193f);
	dsp->fConst485 = tanf((123.692459f / dsp->fConst0));
	dsp->fConst486 = (1.0f / dsp->fConst485);
	dsp->fConst487 = (1.0f / (((dsp->fConst486 + 0.157482162f) / dsp->fConst485) + 0.935140193f));
	dsp->fConst488 = mydsp_faustpower2_f(dsp->fConst485);
	dsp->fConst489 = (50.0638084f / dsp->fConst488);
	dsp->fConst490 = (2.0f * (0.935140193f - dsp->fConst489));
	dsp->fConst491 = (1.0f / (((dsp->fConst486 + 0.743130445f) / dsp->fConst485) + 1.4500711f));
	dsp->fConst492 = (11.0520525f / dsp->fConst488);
	dsp->fConst493 = (2.0f * (1.4500711f - dsp->fConst492));
	dsp->fConst494 = (1.0f / (((dsp->fConst486 + 3.18972731f) / dsp->fConst485) + 4.07678175f));
	dsp->fConst495 = (0.00176617282f / dsp->fConst488);
	dsp->fConst496 = (2.0f * (0.000407678192f - dsp->fConst495));
	dsp->fConst497 = (1.0f / (((dsp->fConst448 + 0.168404877f) / dsp->fConst447) + 1.06935835f));
	dsp->fConst498 = (2.0f * (53.5361519f - dsp->fConst476));
	dsp->fConst499 = (1.0f / (((dsp->fConst448 + 0.51247865f) / dsp->fConst447) + 0.689621389f));
	dsp->fConst500 = (2.0f * (7.62173128f - dsp->fConst476));
	dsp->fConst501 = (1.0f / (((dsp->fConst448 + 0.782413065f) / dsp->fConst447) + 0.245291501f));
	dsp->fConst502 = (9.99999975e-05f / dsp->fConst450);
	dsp->fConst503 = (2.0f * (0.000433227193f - dsp->fConst502));
	dsp->fConst504 = (((dsp->fConst448 + -0.782413065f) / dsp->fConst447) + 0.245291501f);
	dsp->fConst505 = (2.0f * (0.245291501f - dsp->fConst476));
	dsp->fConst506 = (dsp->fConst502 + 0.000433227193f);
	dsp->fConst507 = (((dsp->fConst448 + -0.51247865f) / dsp->fConst447) + 0.689621389f);
	dsp->fConst508 = (2.0f * (0.689621389f - dsp->fConst476));
	dsp->fConst509 = (dsp->fConst476 + 7.62173128f);
	dsp->fConst510 = (((dsp->fConst448 + -0.168404877f) / dsp->fConst447) + 1.06935835f);
	dsp->fConst511 = (2.0f * (1.06935835f - dsp->fConst476));
	dsp->fConst512 = (dsp->fConst476 + 53.5361519f);
	dsp->fConst513 = (((dsp->fConst486 + -3.18972731f) / dsp->fConst485) + 4.07678175f);
	dsp->fConst514 = (1.0f / dsp->fConst488);
	dsp->fConst515 = (2.0f * (4.07678175f - dsp->fConst514));
	dsp->fConst516 = (dsp->fConst495 + 0.000407678192f);
	dsp->fConst517 = (((dsp->fConst486 + -0.743130445f) / dsp->fConst485) + 1.4500711f);
	dsp->fConst518 = (2.0f * (1.4500711f - dsp->fConst514));
	dsp->fConst519 = (dsp->fConst492 + 1.4500711f);
	dsp->fConst520 = (((dsp->fConst486 + -0.157482162f) / dsp->fConst485) + 0.935140193f);
	dsp->fConst521 = (2.0f * (0.935140193f - dsp->fConst514));
	dsp->fConst522 = (dsp->fConst489 + 0.935140193f);
	dsp->fConst523 = (1.0f / (((dsp->fConst486 + 0.168404877f) / dsp->fConst485) + 1.06935835f));
	dsp->fConst524 = (2.0f * (53.5361519f - dsp->fConst514));
	dsp->fConst525 = (1.0f / (((dsp->fConst486 + 0.51247865f) / dsp->fConst485) + 0.689621389f));
	dsp->fConst526 = (2.0f * (7.62173128f - dsp->fConst514));
	dsp->fConst527 = (1.0f / (((dsp->fConst486 + 0.782413065f) / dsp->fConst485) + 0.245291501f));
	dsp->fConst528 = (9.99999975e-05f / dsp->fConst488);
	dsp->fConst529 = (2.0f * (0.000433227193f - dsp->fConst528));
	dsp->fConst530 = (((dsp->fConst486 + -0.782413065f) / dsp->fConst485) + 0.245291501f);
	dsp->fConst531 = (2.0f * (0.245291501f - dsp->fConst514));
	dsp->fConst532 = (dsp->fConst528 + 0.000433227193f);
	dsp->fConst533 = (((dsp->fConst486 + -0.51247865f) / dsp->fConst485) + 0.689621389f);
	dsp->fConst534 = (2.0f * (0.689621389f - dsp->fConst514));
	dsp->fConst535 = (dsp->fConst514 + 7.62173128f);
	dsp->fConst536 = (((dsp->fConst486 + -0.168404877f) / dsp->fConst485) + 1.06935835f);
	dsp->fConst537 = (2.0f * (1.06935835f - dsp->fConst514));
	dsp->fConst538 = (dsp->fConst514 + 53.5361519f);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "phaserFlangerLab");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
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
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "0", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Noise (White or Pink - uses only Amplitude control on   the left)", &dsp->fCheckbox3);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox4, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox4, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink instead of White Noise (also called 1/f Noise)", &dsp->fCheckbox4);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "External Signal Input (overrides Sawtooth/Noise   selection above)", &dsp->fCheckbox2);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "FLANGER");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "tooltip", "When this is checked, the flanger   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox5, "1", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Invert Flange Sum", &dsp->fCheckbox5);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "style", "led");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHbargraph0, "tooltip", "Display sum of flange delays");
	ui_interface->addHorizontalBargraph(ui_interface->uiInterface, "Flange LFO", &dsp->fHbargraph0, -1.5f, 1.5f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Speed", &dsp->fHslider4, 0.5f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Depth", &dsp->fHslider5, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Feedback", &dsp->fHslider6, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Delay Controls");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider8, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Flange Delay", &dsp->fHslider8, 10.0f, 0.0f, 20.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider7, "unit", "ms");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Delay Offset", &dsp->fHslider7, 1.0f, 0.0f, 20.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Flanger Output Level", &dsp->fHslider3, 0.0f, -60.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "PHASER2");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the phaser   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox7, "1", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Invert Internal Phaser Sum", &dsp->fCheckbox7);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox6, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Vibrato Mode", &dsp->fCheckbox6);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider15, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider15, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider15, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Speed", &dsp->fHslider15, 0.5f, 0.0f, 10.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider9, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Notch Depth (Intensity)", &dsp->fHslider9, 1.0f, 0.0f, 1.0f, 0.00100000005f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider11, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Feedback Gain", &dsp->fHslider11, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider10, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider10, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider10, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider10, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Notch width", &dsp->fHslider10, 1000.0f, 10.0f, 5000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider13, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider13, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider13, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider13, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Min Notch1 Freq", &dsp->fHslider13, 100.0f, 20.0f, 5000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider14, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider14, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider14, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider14, "unit", "Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Max Notch1 Freq", &dsp->fHslider14, 800.0f, 20.0f, 10000.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider12, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider12, "style", "knob");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &dsp->fHslider12, 1.5f, 1.10000002f, 4.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Phaser Output Level", &dsp->fHslider2, 0.0f, -60.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b81b030", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b809620", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b7e34a0", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b7c12a0", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b79f0a0", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b77cea0", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b75aca0", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b738aa0", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b7168a0", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b6f0720", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b6ce520", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b6ac320", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b68a120", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b667f20", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f8c4b644c90", &dsp->fVbargraph0, -50.0f, 10.0f);
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
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = expf((0.0f - (dsp->fConst1 / (float)dsp->fHslider1)));
	float fSlow2 = (1.0f - fSlow1);
	int iSlow3 = (int)(float)dsp->fCheckbox0;
	float fSlow4 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider2));
	int iSlow5 = (int)(float)dsp->fCheckbox1;
	float fSlow6 = powf(10.0f, (0.0500000007f * (float)dsp->fHslider3));
	float fSlow7 = (dsp->fConst14 * (float)dsp->fHslider4);
	float fSlow8 = sinf(fSlow7);
	float fSlow9 = cosf(fSlow7);
	float fSlow10 = (0.0f - fSlow8);
	float fSlow11 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	int iSlow12 = (int)(float)dsp->fCheckbox2;
	int iSlow13 = (int)(float)dsp->fCheckbox3;
	int iSlow14 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow15 = (iSlow14 >= 2);
	int iSlow16 = (iSlow14 >= 1);
	float fSlow17 = expf((0.0f - (dsp->fConst15 / (float)dsp->fVslider2)));
	float fSlow18 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fVslider1 + -49.0f))) * (1.0f - fSlow17)));
	int iSlow19 = (iSlow14 >= 3);
	float fSlow20 = ((0.00999999978f * (float)dsp->fVslider3) + 1.0f);
	float fSlow21 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	int iSlow22 = (int)(float)dsp->fCheckbox4;
	float fSlow23 = (float)dsp->fHslider5;
	float fSlow24 = ((int)(float)dsp->fCheckbox5?(0.0f - fSlow23):fSlow23);
	float fSlow25 = (float)dsp->fHslider6;
	float fSlow26 = (0.00100000005f * (float)dsp->fHslider7);
	float fSlow27 = (0.000500000024f * (float)dsp->fHslider8);
	float fSlow28 = (0.5f * ((int)(float)dsp->fCheckbox6?2.0f:(float)dsp->fHslider9));
	float fSlow29 = (1.0f - fSlow28);
	float fSlow30 = expf((dsp->fConst15 * (0.0f - (3.14159274f * (float)dsp->fHslider10))));
	float fSlow31 = mydsp_faustpower2_f(fSlow30);
	float fSlow32 = (float)dsp->fHslider11;
	float fSlow33 = (0.0f - (2.0f * fSlow30));
	float fSlow34 = (float)dsp->fHslider12;
	float fSlow35 = (float)dsp->fHslider13;
	float fSlow36 = (dsp->fConst14 * fSlow35);
	float fSlow37 = (0.5f * (0.0f - (dsp->fConst14 * (fSlow35 - max(fSlow35, (float)dsp->fHslider14)))));
	float fSlow38 = (dsp->fConst14 * (float)dsp->fHslider15);
	float fSlow39 = sinf(fSlow38);
	float fSlow40 = cosf(fSlow38);
	float fSlow41 = (0.0f - fSlow39);
	float fSlow42 = mydsp_faustpower2_f(fSlow34);
	float fSlow43 = mydsp_faustpower3_f(fSlow34);
	float fSlow44 = mydsp_faustpower4_f(fSlow34);
	float fSlow45 = ((int)(float)dsp->fCheckbox7?(0.0f - fSlow28):fSlow28);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec4[0] = ((fSlow8 * dsp->fRec5[1]) + (fSlow9 * dsp->fRec4[1]));
			int iTemp0 = (1 - dsp->iVec0[1]);
			dsp->fRec5[0] = (((fSlow9 * dsp->fRec5[1]) + (fSlow10 * dsp->fRec4[1])) + (float)iTemp0);
			dsp->fHbargraph0 = (FAUSTFLOAT)(dsp->fRec5[0] + dsp->fRec4[0]);
			dsp->fRec6[0] = (fSlow11 + (0.999000013f * dsp->fRec6[1]));
			dsp->fRec8[0] = (fSlow18 + (fSlow17 * dsp->fRec8[1]));
			float fTemp1 = max(20.0f, fabsf(dsp->fRec8[0]));
			dsp->fVec1[0] = fTemp1;
			float fTemp2 = (dsp->fRec7[1] + (dsp->fConst15 * dsp->fVec1[1]));
			dsp->fRec7[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = (2.0f * dsp->fRec7[0]);
			float fTemp4 = (fTemp3 + -1.0f);
			float fTemp5 = mydsp_faustpower2_f(fTemp4);
			dsp->fVec2[0] = fTemp5;
			float fTemp6 = mydsp_faustpower3_f(fTemp4);
			dsp->fVec3[0] = (fTemp6 + (1.0f - fTemp3));
			float fTemp7 = ((fTemp6 + (1.0f - (fTemp3 + dsp->fVec3[1]))) / fTemp1);
			dsp->fVec4[0] = fTemp7;
			float fTemp8 = (fTemp5 * (fTemp5 + -2.0f));
			dsp->fVec5[0] = fTemp8;
			float fTemp9 = ((fTemp8 - dsp->fVec5[1]) / fTemp1);
			dsp->fVec6[0] = fTemp9;
			float fTemp10 = ((fTemp9 - dsp->fVec6[1]) / fTemp1);
			dsp->fVec7[0] = fTemp10;
			float fTemp11 = max(20.0f, fabsf((fSlow20 * dsp->fRec8[0])));
			dsp->fVec8[0] = fTemp11;
			float fTemp12 = (dsp->fRec9[1] + (dsp->fConst15 * dsp->fVec8[1]));
			dsp->fRec9[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (2.0f * dsp->fRec9[0]);
			float fTemp14 = (fTemp13 + -1.0f);
			float fTemp15 = mydsp_faustpower2_f(fTemp14);
			dsp->fVec9[0] = fTemp15;
			float fTemp16 = mydsp_faustpower3_f(fTemp14);
			dsp->fVec10[0] = (fTemp16 + (1.0f - fTemp13));
			float fTemp17 = ((fTemp16 + (1.0f - (fTemp13 + dsp->fVec10[1]))) / fTemp11);
			dsp->fVec11[0] = fTemp17;
			float fTemp18 = (fTemp15 * (fTemp15 + -2.0f));
			dsp->fVec12[0] = fTemp18;
			float fTemp19 = ((fTemp18 - dsp->fVec12[1]) / fTemp11);
			dsp->fVec13[0] = fTemp19;
			float fTemp20 = ((fTemp19 - dsp->fVec13[1]) / fTemp11);
			dsp->fVec14[0] = fTemp20;
			float fTemp21 = max(20.0f, fabsf((fSlow21 * dsp->fRec8[0])));
			dsp->fVec15[0] = fTemp21;
			float fTemp22 = (dsp->fRec10[1] + (dsp->fConst15 * dsp->fVec15[1]));
			dsp->fRec10[0] = (fTemp22 - floorf(fTemp22));
			float fTemp23 = (2.0f * dsp->fRec10[0]);
			float fTemp24 = (fTemp23 + -1.0f);
			float fTemp25 = mydsp_faustpower2_f(fTemp24);
			dsp->fVec16[0] = fTemp25;
			float fTemp26 = mydsp_faustpower3_f(fTemp24);
			dsp->fVec17[0] = (fTemp26 + (1.0f - fTemp23));
			float fTemp27 = ((fTemp26 + (1.0f - (fTemp23 + dsp->fVec17[1]))) / fTemp21);
			dsp->fVec18[0] = fTemp27;
			float fTemp28 = (fTemp25 * (fTemp25 + -2.0f));
			dsp->fVec19[0] = fTemp28;
			float fTemp29 = ((fTemp28 - dsp->fVec19[1]) / fTemp21);
			dsp->fVec20[0] = fTemp29;
			float fTemp30 = ((fTemp29 - dsp->fVec20[1]) / fTemp21);
			dsp->fVec21[0] = fTemp30;
			dsp->iRec11[0] = ((1103515245 * dsp->iRec11[1]) + 12345);
			float fTemp31 = (4.65661287e-10f * (float)dsp->iRec11[0]);
			dsp->fRec12[0] = (((0.522189379f * dsp->fRec12[3]) + (fTemp31 + (2.49495602f * dsp->fRec12[1]))) - (2.0172658f * dsp->fRec12[2]));
			float fTemp32 = (dsp->fRec6[0] * (iSlow12?(float)input0[i]:(iSlow13?(iSlow22?(((0.0499220341f * dsp->fRec12[0]) + (0.0506126992f * dsp->fRec12[2])) - ((0.0959935337f * dsp->fRec12[1]) + (0.00440878607f * dsp->fRec12[3]))):fTemp31):(0.333333343f * (dsp->fRec6[0] * (((iSlow15?(iSlow19?(dsp->fConst18 * (((float)dsp->iVec0[3] * (fTemp10 - dsp->fVec7[1])) / fTemp1)):(dsp->fConst17 * (((float)dsp->iVec0[2] * (fTemp7 - dsp->fVec4[1])) / fTemp1))):(iSlow16?(dsp->fConst16 * (((float)dsp->iVec0[1] * (fTemp5 - dsp->fVec2[1])) / fTemp1)):fTemp4)) + (iSlow15?(iSlow19?(dsp->fConst18 * (((float)dsp->iVec0[3] * (fTemp20 - dsp->fVec14[1])) / fTemp11)):(dsp->fConst17 * (((float)dsp->iVec0[2] * (fTemp17 - dsp->fVec11[1])) / fTemp11))):(iSlow16?(dsp->fConst16 * (((float)dsp->iVec0[1] * (fTemp15 - dsp->fVec9[1])) / fTemp11)):fTemp14))) + (iSlow15?(iSlow19?(dsp->fConst18 * (((float)dsp->iVec0[3] * (fTemp30 - dsp->fVec21[1])) / fTemp21)):(dsp->fConst17 * (((float)dsp->iVec0[2] * (fTemp27 - dsp->fVec18[1])) / fTemp21))):(iSlow16?(dsp->fConst16 * (((float)dsp->iVec0[1] * (fTemp25 - dsp->fVec16[1])) / fTemp21)):fTemp24))))))));
			float fTemp33 = (iSlow5?0.0f:fTemp32);
			float fTemp34 = (fSlow6 * fTemp33);
			float fTemp35 = ((fSlow25 * dsp->fRec13[1]) - fTemp34);
			dsp->fVec22[(dsp->IOTA & 4095)] = fTemp35;
			float fTemp36 = (dsp->fConst0 * (fSlow26 + (fSlow27 * (dsp->fRec4[0] + 1.0f))));
			int iTemp37 = (int)fTemp36;
			float fTemp38 = floorf(fTemp36);
			dsp->fRec13[0] = ((dsp->fVec22[((dsp->IOTA - min(2049, max(0, iTemp37))) & 4095)] * (fTemp38 + (1.0f - fTemp36))) + ((fTemp36 - fTemp38) * dsp->fVec22[((dsp->IOTA - min(2049, max(0, (iTemp37 + 1)))) & 4095)]));
			float fTemp39 = (iSlow5?fTemp32:(0.5f * (fTemp34 + (fSlow24 * dsp->fRec13[0]))));
			float fTemp40 = (iSlow3?0.0f:fTemp39);
			dsp->fRec19[0] = ((fSlow39 * dsp->fRec20[1]) + (fSlow40 * dsp->fRec19[1]));
			dsp->fRec20[0] = (((fSlow40 * dsp->fRec20[1]) + (fSlow41 * dsp->fRec19[1])) + (float)iTemp0);
			float fTemp41 = (fSlow36 + (fSlow37 * (1.0f - dsp->fRec19[0])));
			float fTemp42 = (dsp->fRec18[1] * cosf((fSlow34 * fTemp41)));
			dsp->fRec18[0] = (((fSlow4 * fTemp40) + (fSlow32 * dsp->fRec14[1])) - ((fSlow33 * fTemp42) + (fSlow31 * dsp->fRec18[2])));
			float fTemp43 = (dsp->fRec17[1] * cosf((fSlow42 * fTemp41)));
			dsp->fRec17[0] = ((dsp->fRec18[2] + (fSlow33 * (fTemp42 - fTemp43))) + (fSlow31 * (dsp->fRec18[0] - dsp->fRec17[2])));
			float fTemp44 = (dsp->fRec16[1] * cosf((fSlow43 * fTemp41)));
			dsp->fRec16[0] = ((dsp->fRec17[2] + (fSlow33 * (fTemp43 - fTemp44))) + (fSlow31 * (dsp->fRec17[0] - dsp->fRec16[2])));
			float fTemp45 = (dsp->fRec15[1] * cosf((fSlow44 * fTemp41)));
			dsp->fRec15[0] = ((dsp->fRec16[2] + (fSlow33 * (fTemp44 - fTemp45))) + (fSlow31 * (dsp->fRec16[0] - dsp->fRec15[2])));
			dsp->fRec14[0] = ((fSlow31 * dsp->fRec15[0]) + ((fSlow33 * fTemp45) + dsp->fRec15[2]));
			float fTemp46 = (iSlow3?fTemp39:((fSlow4 * (fTemp40 * fSlow29)) + (dsp->fRec14[0] * fSlow45)));
			float fTemp47 = (fSlow6 * fTemp33);
			float fTemp48 = ((fSlow25 * dsp->fRec21[1]) - fTemp47);
			dsp->fVec23[(dsp->IOTA & 4095)] = fTemp48;
			float fTemp49 = (dsp->fConst0 * (fSlow26 + (fSlow27 * (dsp->fRec5[0] + 1.0f))));
			int iTemp50 = (int)fTemp49;
			float fTemp51 = floorf(fTemp49);
			dsp->fRec21[0] = ((dsp->fVec23[((dsp->IOTA - min(2049, max(0, iTemp50))) & 4095)] * (fTemp51 + (1.0f - fTemp49))) + ((fTemp49 - fTemp51) * dsp->fVec23[((dsp->IOTA - min(2049, max(0, (iTemp50 + 1)))) & 4095)]));
			float fTemp52 = (iSlow5?fTemp32:(0.5f * (fTemp47 + (fSlow24 * dsp->fRec21[0]))));
			float fTemp53 = (iSlow3?0.0f:fTemp52);
			float fTemp54 = (fSlow36 + (fSlow37 * (1.0f - dsp->fRec20[0])));
			float fTemp55 = (dsp->fRec26[1] * cosf((fSlow34 * fTemp54)));
			dsp->fRec26[0] = (((fSlow4 * fTemp53) + (fSlow32 * dsp->fRec22[1])) - ((fSlow33 * fTemp55) + (fSlow31 * dsp->fRec26[2])));
			float fTemp56 = (dsp->fRec25[1] * cosf((fSlow42 * fTemp54)));
			dsp->fRec25[0] = ((dsp->fRec26[2] + (fSlow33 * (fTemp55 - fTemp56))) + (fSlow31 * (dsp->fRec26[0] - dsp->fRec25[2])));
			float fTemp57 = (dsp->fRec24[1] * cosf((fSlow43 * fTemp54)));
			dsp->fRec24[0] = ((dsp->fRec25[2] + (fSlow33 * (fTemp56 - fTemp57))) + (fSlow31 * (dsp->fRec25[0] - dsp->fRec24[2])));
			float fTemp58 = (dsp->fRec23[1] * cosf((fSlow44 * fTemp54)));
			dsp->fRec23[0] = ((dsp->fRec24[2] + (fSlow33 * (fTemp57 - fTemp58))) + (fSlow31 * (dsp->fRec24[0] - dsp->fRec23[2])));
			dsp->fRec22[0] = ((fSlow31 * dsp->fRec23[0]) + ((fSlow33 * fTemp58) + dsp->fRec23[2]));
			float fTemp59 = (iSlow3?fTemp52:((fSlow4 * (fSlow29 * fTemp53)) + (dsp->fRec22[0] * fSlow45)));
			float fTemp60 = (fTemp46 + fTemp59);
			dsp->fRec3[0] = (fTemp60 - (dsp->fConst11 * ((dsp->fConst19 * dsp->fRec3[2]) + (dsp->fConst21 * dsp->fRec3[1]))));
			dsp->fRec2[0] = ((dsp->fConst11 * (((dsp->fConst13 * dsp->fRec3[1]) + (dsp->fConst22 * dsp->fRec3[0])) + (dsp->fConst22 * dsp->fRec3[2]))) - (dsp->fConst8 * ((dsp->fConst23 * dsp->fRec2[2]) + (dsp->fConst24 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst8 * (((dsp->fConst10 * dsp->fRec2[1]) + (dsp->fConst25 * dsp->fRec2[0])) + (dsp->fConst25 * dsp->fRec2[2]))) - (dsp->fConst4 * ((dsp->fConst26 * dsp->fRec1[2]) + (dsp->fConst27 * dsp->fRec1[1]))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * fabsf((dsp->fConst4 * (((dsp->fConst7 * dsp->fRec1[1]) + (dsp->fConst28 * dsp->fRec1[0])) + (dsp->fConst28 * dsp->fRec1[2]))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec0[0]))));
			dsp->fRec33[0] = (fTemp60 - (dsp->fConst45 * ((dsp->fConst48 * dsp->fRec33[2]) + (dsp->fConst49 * dsp->fRec33[1]))));
			dsp->fRec32[0] = ((dsp->fConst45 * (((dsp->fConst47 * dsp->fRec33[1]) + (dsp->fConst50 * dsp->fRec33[0])) + (dsp->fConst50 * dsp->fRec33[2]))) - (dsp->fConst43 * ((dsp->fConst51 * dsp->fRec32[2]) + (dsp->fConst52 * dsp->fRec32[1]))));
			dsp->fRec31[0] = ((dsp->fConst43 * (((dsp->fConst44 * dsp->fRec32[1]) + (dsp->fConst53 * dsp->fRec32[0])) + (dsp->fConst53 * dsp->fRec32[2]))) - (dsp->fConst41 * ((dsp->fConst54 * dsp->fRec31[2]) + (dsp->fConst55 * dsp->fRec31[1]))));
			float fTemp61 = (dsp->fConst41 * (((dsp->fConst42 * dsp->fRec31[1]) + (dsp->fConst56 * dsp->fRec31[0])) + (dsp->fConst56 * dsp->fRec31[2])));
			dsp->fRec30[0] = (fTemp61 - (dsp->fConst38 * ((dsp->fConst57 * dsp->fRec30[2]) + (dsp->fConst59 * dsp->fRec30[1]))));
			dsp->fRec29[0] = ((dsp->fConst38 * (((dsp->fConst40 * dsp->fRec30[1]) + (dsp->fConst60 * dsp->fRec30[0])) + (dsp->fConst60 * dsp->fRec30[2]))) - (dsp->fConst35 * ((dsp->fConst61 * dsp->fRec29[2]) + (dsp->fConst62 * dsp->fRec29[1]))));
			dsp->fRec28[0] = ((dsp->fConst35 * (((dsp->fConst37 * dsp->fRec29[1]) + (dsp->fConst63 * dsp->fRec29[0])) + (dsp->fConst63 * dsp->fRec29[2]))) - (dsp->fConst31 * ((dsp->fConst64 * dsp->fRec28[2]) + (dsp->fConst65 * dsp->fRec28[1]))));
			dsp->fRec27[0] = ((fSlow1 * dsp->fRec27[1]) + (fSlow2 * fabsf((dsp->fConst31 * (((dsp->fConst34 * dsp->fRec28[1]) + (dsp->fConst66 * dsp->fRec28[0])) + (dsp->fConst66 * dsp->fRec28[2]))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec27[0]))));
			dsp->fRec40[0] = (fTemp61 - (dsp->fConst83 * ((dsp->fConst86 * dsp->fRec40[2]) + (dsp->fConst87 * dsp->fRec40[1]))));
			dsp->fRec39[0] = ((dsp->fConst83 * (((dsp->fConst85 * dsp->fRec40[1]) + (dsp->fConst88 * dsp->fRec40[0])) + (dsp->fConst88 * dsp->fRec40[2]))) - (dsp->fConst81 * ((dsp->fConst89 * dsp->fRec39[2]) + (dsp->fConst90 * dsp->fRec39[1]))));
			dsp->fRec38[0] = ((dsp->fConst81 * (((dsp->fConst82 * dsp->fRec39[1]) + (dsp->fConst91 * dsp->fRec39[0])) + (dsp->fConst91 * dsp->fRec39[2]))) - (dsp->fConst79 * ((dsp->fConst92 * dsp->fRec38[2]) + (dsp->fConst93 * dsp->fRec38[1]))));
			float fTemp62 = (dsp->fConst79 * (((dsp->fConst80 * dsp->fRec38[1]) + (dsp->fConst94 * dsp->fRec38[0])) + (dsp->fConst94 * dsp->fRec38[2])));
			dsp->fRec37[0] = (fTemp62 - (dsp->fConst76 * ((dsp->fConst95 * dsp->fRec37[2]) + (dsp->fConst97 * dsp->fRec37[1]))));
			dsp->fRec36[0] = ((dsp->fConst76 * (((dsp->fConst78 * dsp->fRec37[1]) + (dsp->fConst98 * dsp->fRec37[0])) + (dsp->fConst98 * dsp->fRec37[2]))) - (dsp->fConst73 * ((dsp->fConst99 * dsp->fRec36[2]) + (dsp->fConst100 * dsp->fRec36[1]))));
			dsp->fRec35[0] = ((dsp->fConst73 * (((dsp->fConst75 * dsp->fRec36[1]) + (dsp->fConst101 * dsp->fRec36[0])) + (dsp->fConst101 * dsp->fRec36[2]))) - (dsp->fConst69 * ((dsp->fConst102 * dsp->fRec35[2]) + (dsp->fConst103 * dsp->fRec35[1]))));
			dsp->fRec34[0] = ((fSlow1 * dsp->fRec34[1]) + (fSlow2 * fabsf((dsp->fConst69 * (((dsp->fConst72 * dsp->fRec35[1]) + (dsp->fConst104 * dsp->fRec35[0])) + (dsp->fConst104 * dsp->fRec35[2]))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec34[0]))));
			dsp->fRec47[0] = (fTemp62 - (dsp->fConst121 * ((dsp->fConst124 * dsp->fRec47[2]) + (dsp->fConst125 * dsp->fRec47[1]))));
			dsp->fRec46[0] = ((dsp->fConst121 * (((dsp->fConst123 * dsp->fRec47[1]) + (dsp->fConst126 * dsp->fRec47[0])) + (dsp->fConst126 * dsp->fRec47[2]))) - (dsp->fConst119 * ((dsp->fConst127 * dsp->fRec46[2]) + (dsp->fConst128 * dsp->fRec46[1]))));
			dsp->fRec45[0] = ((dsp->fConst119 * (((dsp->fConst120 * dsp->fRec46[1]) + (dsp->fConst129 * dsp->fRec46[0])) + (dsp->fConst129 * dsp->fRec46[2]))) - (dsp->fConst117 * ((dsp->fConst130 * dsp->fRec45[2]) + (dsp->fConst131 * dsp->fRec45[1]))));
			float fTemp63 = (dsp->fConst117 * (((dsp->fConst118 * dsp->fRec45[1]) + (dsp->fConst132 * dsp->fRec45[0])) + (dsp->fConst132 * dsp->fRec45[2])));
			dsp->fRec44[0] = (fTemp63 - (dsp->fConst114 * ((dsp->fConst133 * dsp->fRec44[2]) + (dsp->fConst135 * dsp->fRec44[1]))));
			dsp->fRec43[0] = ((dsp->fConst114 * (((dsp->fConst116 * dsp->fRec44[1]) + (dsp->fConst136 * dsp->fRec44[0])) + (dsp->fConst136 * dsp->fRec44[2]))) - (dsp->fConst111 * ((dsp->fConst137 * dsp->fRec43[2]) + (dsp->fConst138 * dsp->fRec43[1]))));
			dsp->fRec42[0] = ((dsp->fConst111 * (((dsp->fConst113 * dsp->fRec43[1]) + (dsp->fConst139 * dsp->fRec43[0])) + (dsp->fConst139 * dsp->fRec43[2]))) - (dsp->fConst107 * ((dsp->fConst140 * dsp->fRec42[2]) + (dsp->fConst141 * dsp->fRec42[1]))));
			dsp->fRec41[0] = ((fSlow1 * dsp->fRec41[1]) + (fSlow2 * fabsf((dsp->fConst107 * (((dsp->fConst110 * dsp->fRec42[1]) + (dsp->fConst142 * dsp->fRec42[0])) + (dsp->fConst142 * dsp->fRec42[2]))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec41[0]))));
			dsp->fRec54[0] = (fTemp63 - (dsp->fConst159 * ((dsp->fConst162 * dsp->fRec54[2]) + (dsp->fConst163 * dsp->fRec54[1]))));
			dsp->fRec53[0] = ((dsp->fConst159 * (((dsp->fConst161 * dsp->fRec54[1]) + (dsp->fConst164 * dsp->fRec54[0])) + (dsp->fConst164 * dsp->fRec54[2]))) - (dsp->fConst157 * ((dsp->fConst165 * dsp->fRec53[2]) + (dsp->fConst166 * dsp->fRec53[1]))));
			dsp->fRec52[0] = ((dsp->fConst157 * (((dsp->fConst158 * dsp->fRec53[1]) + (dsp->fConst167 * dsp->fRec53[0])) + (dsp->fConst167 * dsp->fRec53[2]))) - (dsp->fConst155 * ((dsp->fConst168 * dsp->fRec52[2]) + (dsp->fConst169 * dsp->fRec52[1]))));
			float fTemp64 = (dsp->fConst155 * (((dsp->fConst156 * dsp->fRec52[1]) + (dsp->fConst170 * dsp->fRec52[0])) + (dsp->fConst170 * dsp->fRec52[2])));
			dsp->fRec51[0] = (fTemp64 - (dsp->fConst152 * ((dsp->fConst171 * dsp->fRec51[2]) + (dsp->fConst173 * dsp->fRec51[1]))));
			dsp->fRec50[0] = ((dsp->fConst152 * (((dsp->fConst154 * dsp->fRec51[1]) + (dsp->fConst174 * dsp->fRec51[0])) + (dsp->fConst174 * dsp->fRec51[2]))) - (dsp->fConst149 * ((dsp->fConst175 * dsp->fRec50[2]) + (dsp->fConst176 * dsp->fRec50[1]))));
			dsp->fRec49[0] = ((dsp->fConst149 * (((dsp->fConst151 * dsp->fRec50[1]) + (dsp->fConst177 * dsp->fRec50[0])) + (dsp->fConst177 * dsp->fRec50[2]))) - (dsp->fConst145 * ((dsp->fConst178 * dsp->fRec49[2]) + (dsp->fConst179 * dsp->fRec49[1]))));
			dsp->fRec48[0] = ((fSlow1 * dsp->fRec48[1]) + (fSlow2 * fabsf((dsp->fConst145 * (((dsp->fConst148 * dsp->fRec49[1]) + (dsp->fConst180 * dsp->fRec49[0])) + (dsp->fConst180 * dsp->fRec49[2]))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec48[0]))));
			dsp->fRec61[0] = (fTemp64 - (dsp->fConst197 * ((dsp->fConst200 * dsp->fRec61[2]) + (dsp->fConst201 * dsp->fRec61[1]))));
			dsp->fRec60[0] = ((dsp->fConst197 * (((dsp->fConst199 * dsp->fRec61[1]) + (dsp->fConst202 * dsp->fRec61[0])) + (dsp->fConst202 * dsp->fRec61[2]))) - (dsp->fConst195 * ((dsp->fConst203 * dsp->fRec60[2]) + (dsp->fConst204 * dsp->fRec60[1]))));
			dsp->fRec59[0] = ((dsp->fConst195 * (((dsp->fConst196 * dsp->fRec60[1]) + (dsp->fConst205 * dsp->fRec60[0])) + (dsp->fConst205 * dsp->fRec60[2]))) - (dsp->fConst193 * ((dsp->fConst206 * dsp->fRec59[2]) + (dsp->fConst207 * dsp->fRec59[1]))));
			float fTemp65 = (dsp->fConst193 * (((dsp->fConst194 * dsp->fRec59[1]) + (dsp->fConst208 * dsp->fRec59[0])) + (dsp->fConst208 * dsp->fRec59[2])));
			dsp->fRec58[0] = (fTemp65 - (dsp->fConst190 * ((dsp->fConst209 * dsp->fRec58[2]) + (dsp->fConst211 * dsp->fRec58[1]))));
			dsp->fRec57[0] = ((dsp->fConst190 * (((dsp->fConst192 * dsp->fRec58[1]) + (dsp->fConst212 * dsp->fRec58[0])) + (dsp->fConst212 * dsp->fRec58[2]))) - (dsp->fConst187 * ((dsp->fConst213 * dsp->fRec57[2]) + (dsp->fConst214 * dsp->fRec57[1]))));
			dsp->fRec56[0] = ((dsp->fConst187 * (((dsp->fConst189 * dsp->fRec57[1]) + (dsp->fConst215 * dsp->fRec57[0])) + (dsp->fConst215 * dsp->fRec57[2]))) - (dsp->fConst183 * ((dsp->fConst216 * dsp->fRec56[2]) + (dsp->fConst217 * dsp->fRec56[1]))));
			dsp->fRec55[0] = ((fSlow1 * dsp->fRec55[1]) + (fSlow2 * fabsf((dsp->fConst183 * (((dsp->fConst186 * dsp->fRec56[1]) + (dsp->fConst218 * dsp->fRec56[0])) + (dsp->fConst218 * dsp->fRec56[2]))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec55[0]))));
			dsp->fRec68[0] = (fTemp65 - (dsp->fConst235 * ((dsp->fConst238 * dsp->fRec68[2]) + (dsp->fConst239 * dsp->fRec68[1]))));
			dsp->fRec67[0] = ((dsp->fConst235 * (((dsp->fConst237 * dsp->fRec68[1]) + (dsp->fConst240 * dsp->fRec68[0])) + (dsp->fConst240 * dsp->fRec68[2]))) - (dsp->fConst233 * ((dsp->fConst241 * dsp->fRec67[2]) + (dsp->fConst242 * dsp->fRec67[1]))));
			dsp->fRec66[0] = ((dsp->fConst233 * (((dsp->fConst234 * dsp->fRec67[1]) + (dsp->fConst243 * dsp->fRec67[0])) + (dsp->fConst243 * dsp->fRec67[2]))) - (dsp->fConst231 * ((dsp->fConst244 * dsp->fRec66[2]) + (dsp->fConst245 * dsp->fRec66[1]))));
			float fTemp66 = (dsp->fConst231 * (((dsp->fConst232 * dsp->fRec66[1]) + (dsp->fConst246 * dsp->fRec66[0])) + (dsp->fConst246 * dsp->fRec66[2])));
			dsp->fRec65[0] = (fTemp66 - (dsp->fConst228 * ((dsp->fConst247 * dsp->fRec65[2]) + (dsp->fConst249 * dsp->fRec65[1]))));
			dsp->fRec64[0] = ((dsp->fConst228 * (((dsp->fConst230 * dsp->fRec65[1]) + (dsp->fConst250 * dsp->fRec65[0])) + (dsp->fConst250 * dsp->fRec65[2]))) - (dsp->fConst225 * ((dsp->fConst251 * dsp->fRec64[2]) + (dsp->fConst252 * dsp->fRec64[1]))));
			dsp->fRec63[0] = ((dsp->fConst225 * (((dsp->fConst227 * dsp->fRec64[1]) + (dsp->fConst253 * dsp->fRec64[0])) + (dsp->fConst253 * dsp->fRec64[2]))) - (dsp->fConst221 * ((dsp->fConst254 * dsp->fRec63[2]) + (dsp->fConst255 * dsp->fRec63[1]))));
			dsp->fRec62[0] = ((fSlow1 * dsp->fRec62[1]) + (fSlow2 * fabsf((dsp->fConst221 * (((dsp->fConst224 * dsp->fRec63[1]) + (dsp->fConst256 * dsp->fRec63[0])) + (dsp->fConst256 * dsp->fRec63[2]))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec62[0]))));
			dsp->fRec75[0] = (fTemp66 - (dsp->fConst273 * ((dsp->fConst276 * dsp->fRec75[2]) + (dsp->fConst277 * dsp->fRec75[1]))));
			dsp->fRec74[0] = ((dsp->fConst273 * (((dsp->fConst275 * dsp->fRec75[1]) + (dsp->fConst278 * dsp->fRec75[0])) + (dsp->fConst278 * dsp->fRec75[2]))) - (dsp->fConst271 * ((dsp->fConst279 * dsp->fRec74[2]) + (dsp->fConst280 * dsp->fRec74[1]))));
			dsp->fRec73[0] = ((dsp->fConst271 * (((dsp->fConst272 * dsp->fRec74[1]) + (dsp->fConst281 * dsp->fRec74[0])) + (dsp->fConst281 * dsp->fRec74[2]))) - (dsp->fConst269 * ((dsp->fConst282 * dsp->fRec73[2]) + (dsp->fConst283 * dsp->fRec73[1]))));
			float fTemp67 = (dsp->fConst269 * (((dsp->fConst270 * dsp->fRec73[1]) + (dsp->fConst284 * dsp->fRec73[0])) + (dsp->fConst284 * dsp->fRec73[2])));
			dsp->fRec72[0] = (fTemp67 - (dsp->fConst266 * ((dsp->fConst285 * dsp->fRec72[2]) + (dsp->fConst287 * dsp->fRec72[1]))));
			dsp->fRec71[0] = ((dsp->fConst266 * (((dsp->fConst268 * dsp->fRec72[1]) + (dsp->fConst288 * dsp->fRec72[0])) + (dsp->fConst288 * dsp->fRec72[2]))) - (dsp->fConst263 * ((dsp->fConst289 * dsp->fRec71[2]) + (dsp->fConst290 * dsp->fRec71[1]))));
			dsp->fRec70[0] = ((dsp->fConst263 * (((dsp->fConst265 * dsp->fRec71[1]) + (dsp->fConst291 * dsp->fRec71[0])) + (dsp->fConst291 * dsp->fRec71[2]))) - (dsp->fConst259 * ((dsp->fConst292 * dsp->fRec70[2]) + (dsp->fConst293 * dsp->fRec70[1]))));
			dsp->fRec69[0] = ((fSlow1 * dsp->fRec69[1]) + (fSlow2 * fabsf((dsp->fConst259 * (((dsp->fConst262 * dsp->fRec70[1]) + (dsp->fConst294 * dsp->fRec70[0])) + (dsp->fConst294 * dsp->fRec70[2]))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec69[0]))));
			dsp->fRec82[0] = (fTemp67 - (dsp->fConst311 * ((dsp->fConst314 * dsp->fRec82[2]) + (dsp->fConst315 * dsp->fRec82[1]))));
			dsp->fRec81[0] = ((dsp->fConst311 * (((dsp->fConst313 * dsp->fRec82[1]) + (dsp->fConst316 * dsp->fRec82[0])) + (dsp->fConst316 * dsp->fRec82[2]))) - (dsp->fConst309 * ((dsp->fConst317 * dsp->fRec81[2]) + (dsp->fConst318 * dsp->fRec81[1]))));
			dsp->fRec80[0] = ((dsp->fConst309 * (((dsp->fConst310 * dsp->fRec81[1]) + (dsp->fConst319 * dsp->fRec81[0])) + (dsp->fConst319 * dsp->fRec81[2]))) - (dsp->fConst307 * ((dsp->fConst320 * dsp->fRec80[2]) + (dsp->fConst321 * dsp->fRec80[1]))));
			float fTemp68 = (dsp->fConst307 * (((dsp->fConst308 * dsp->fRec80[1]) + (dsp->fConst322 * dsp->fRec80[0])) + (dsp->fConst322 * dsp->fRec80[2])));
			dsp->fRec79[0] = (fTemp68 - (dsp->fConst304 * ((dsp->fConst323 * dsp->fRec79[2]) + (dsp->fConst325 * dsp->fRec79[1]))));
			dsp->fRec78[0] = ((dsp->fConst304 * (((dsp->fConst306 * dsp->fRec79[1]) + (dsp->fConst326 * dsp->fRec79[0])) + (dsp->fConst326 * dsp->fRec79[2]))) - (dsp->fConst301 * ((dsp->fConst327 * dsp->fRec78[2]) + (dsp->fConst328 * dsp->fRec78[1]))));
			dsp->fRec77[0] = ((dsp->fConst301 * (((dsp->fConst303 * dsp->fRec78[1]) + (dsp->fConst329 * dsp->fRec78[0])) + (dsp->fConst329 * dsp->fRec78[2]))) - (dsp->fConst297 * ((dsp->fConst330 * dsp->fRec77[2]) + (dsp->fConst331 * dsp->fRec77[1]))));
			dsp->fRec76[0] = ((fSlow1 * dsp->fRec76[1]) + (fSlow2 * fabsf((dsp->fConst297 * (((dsp->fConst300 * dsp->fRec77[1]) + (dsp->fConst332 * dsp->fRec77[0])) + (dsp->fConst332 * dsp->fRec77[2]))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec76[0]))));
			dsp->fRec89[0] = (fTemp68 - (dsp->fConst349 * ((dsp->fConst352 * dsp->fRec89[2]) + (dsp->fConst353 * dsp->fRec89[1]))));
			dsp->fRec88[0] = ((dsp->fConst349 * (((dsp->fConst351 * dsp->fRec89[1]) + (dsp->fConst354 * dsp->fRec89[0])) + (dsp->fConst354 * dsp->fRec89[2]))) - (dsp->fConst347 * ((dsp->fConst355 * dsp->fRec88[2]) + (dsp->fConst356 * dsp->fRec88[1]))));
			dsp->fRec87[0] = ((dsp->fConst347 * (((dsp->fConst348 * dsp->fRec88[1]) + (dsp->fConst357 * dsp->fRec88[0])) + (dsp->fConst357 * dsp->fRec88[2]))) - (dsp->fConst345 * ((dsp->fConst358 * dsp->fRec87[2]) + (dsp->fConst359 * dsp->fRec87[1]))));
			float fTemp69 = (dsp->fConst345 * (((dsp->fConst346 * dsp->fRec87[1]) + (dsp->fConst360 * dsp->fRec87[0])) + (dsp->fConst360 * dsp->fRec87[2])));
			dsp->fRec86[0] = (fTemp69 - (dsp->fConst342 * ((dsp->fConst361 * dsp->fRec86[2]) + (dsp->fConst363 * dsp->fRec86[1]))));
			dsp->fRec85[0] = ((dsp->fConst342 * (((dsp->fConst344 * dsp->fRec86[1]) + (dsp->fConst364 * dsp->fRec86[0])) + (dsp->fConst364 * dsp->fRec86[2]))) - (dsp->fConst339 * ((dsp->fConst365 * dsp->fRec85[2]) + (dsp->fConst366 * dsp->fRec85[1]))));
			dsp->fRec84[0] = ((dsp->fConst339 * (((dsp->fConst341 * dsp->fRec85[1]) + (dsp->fConst367 * dsp->fRec85[0])) + (dsp->fConst367 * dsp->fRec85[2]))) - (dsp->fConst335 * ((dsp->fConst368 * dsp->fRec84[2]) + (dsp->fConst369 * dsp->fRec84[1]))));
			dsp->fRec83[0] = ((fSlow1 * dsp->fRec83[1]) + (fSlow2 * fabsf((dsp->fConst335 * (((dsp->fConst338 * dsp->fRec84[1]) + (dsp->fConst370 * dsp->fRec84[0])) + (dsp->fConst370 * dsp->fRec84[2]))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec83[0]))));
			dsp->fRec96[0] = (fTemp69 - (dsp->fConst387 * ((dsp->fConst390 * dsp->fRec96[2]) + (dsp->fConst391 * dsp->fRec96[1]))));
			dsp->fRec95[0] = ((dsp->fConst387 * (((dsp->fConst389 * dsp->fRec96[1]) + (dsp->fConst392 * dsp->fRec96[0])) + (dsp->fConst392 * dsp->fRec96[2]))) - (dsp->fConst385 * ((dsp->fConst393 * dsp->fRec95[2]) + (dsp->fConst394 * dsp->fRec95[1]))));
			dsp->fRec94[0] = ((dsp->fConst385 * (((dsp->fConst386 * dsp->fRec95[1]) + (dsp->fConst395 * dsp->fRec95[0])) + (dsp->fConst395 * dsp->fRec95[2]))) - (dsp->fConst383 * ((dsp->fConst396 * dsp->fRec94[2]) + (dsp->fConst397 * dsp->fRec94[1]))));
			float fTemp70 = (dsp->fConst383 * (((dsp->fConst384 * dsp->fRec94[1]) + (dsp->fConst398 * dsp->fRec94[0])) + (dsp->fConst398 * dsp->fRec94[2])));
			dsp->fRec93[0] = (fTemp70 - (dsp->fConst380 * ((dsp->fConst399 * dsp->fRec93[2]) + (dsp->fConst401 * dsp->fRec93[1]))));
			dsp->fRec92[0] = ((dsp->fConst380 * (((dsp->fConst382 * dsp->fRec93[1]) + (dsp->fConst402 * dsp->fRec93[0])) + (dsp->fConst402 * dsp->fRec93[2]))) - (dsp->fConst377 * ((dsp->fConst403 * dsp->fRec92[2]) + (dsp->fConst404 * dsp->fRec92[1]))));
			dsp->fRec91[0] = ((dsp->fConst377 * (((dsp->fConst379 * dsp->fRec92[1]) + (dsp->fConst405 * dsp->fRec92[0])) + (dsp->fConst405 * dsp->fRec92[2]))) - (dsp->fConst373 * ((dsp->fConst406 * dsp->fRec91[2]) + (dsp->fConst407 * dsp->fRec91[1]))));
			dsp->fRec90[0] = ((fSlow1 * dsp->fRec90[1]) + (fSlow2 * fabsf((dsp->fConst373 * (((dsp->fConst376 * dsp->fRec91[1]) + (dsp->fConst408 * dsp->fRec91[0])) + (dsp->fConst408 * dsp->fRec91[2]))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec90[0]))));
			dsp->fRec103[0] = (fTemp70 - (dsp->fConst425 * ((dsp->fConst428 * dsp->fRec103[2]) + (dsp->fConst429 * dsp->fRec103[1]))));
			dsp->fRec102[0] = ((dsp->fConst425 * (((dsp->fConst427 * dsp->fRec103[1]) + (dsp->fConst430 * dsp->fRec103[0])) + (dsp->fConst430 * dsp->fRec103[2]))) - (dsp->fConst423 * ((dsp->fConst431 * dsp->fRec102[2]) + (dsp->fConst432 * dsp->fRec102[1]))));
			dsp->fRec101[0] = ((dsp->fConst423 * (((dsp->fConst424 * dsp->fRec102[1]) + (dsp->fConst433 * dsp->fRec102[0])) + (dsp->fConst433 * dsp->fRec102[2]))) - (dsp->fConst421 * ((dsp->fConst434 * dsp->fRec101[2]) + (dsp->fConst435 * dsp->fRec101[1]))));
			float fTemp71 = (dsp->fConst421 * (((dsp->fConst422 * dsp->fRec101[1]) + (dsp->fConst436 * dsp->fRec101[0])) + (dsp->fConst436 * dsp->fRec101[2])));
			dsp->fRec100[0] = (fTemp71 - (dsp->fConst418 * ((dsp->fConst437 * dsp->fRec100[2]) + (dsp->fConst439 * dsp->fRec100[1]))));
			dsp->fRec99[0] = ((dsp->fConst418 * (((dsp->fConst420 * dsp->fRec100[1]) + (dsp->fConst440 * dsp->fRec100[0])) + (dsp->fConst440 * dsp->fRec100[2]))) - (dsp->fConst415 * ((dsp->fConst441 * dsp->fRec99[2]) + (dsp->fConst442 * dsp->fRec99[1]))));
			dsp->fRec98[0] = ((dsp->fConst415 * (((dsp->fConst417 * dsp->fRec99[1]) + (dsp->fConst443 * dsp->fRec99[0])) + (dsp->fConst443 * dsp->fRec99[2]))) - (dsp->fConst411 * ((dsp->fConst444 * dsp->fRec98[2]) + (dsp->fConst445 * dsp->fRec98[1]))));
			dsp->fRec97[0] = ((fSlow1 * dsp->fRec97[1]) + (fSlow2 * fabsf((dsp->fConst411 * (((dsp->fConst414 * dsp->fRec98[1]) + (dsp->fConst446 * dsp->fRec98[0])) + (dsp->fConst446 * dsp->fRec98[2]))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec97[0]))));
			dsp->fRec110[0] = (fTemp71 - (dsp->fConst463 * ((dsp->fConst466 * dsp->fRec110[2]) + (dsp->fConst467 * dsp->fRec110[1]))));
			dsp->fRec109[0] = ((dsp->fConst463 * (((dsp->fConst465 * dsp->fRec110[1]) + (dsp->fConst468 * dsp->fRec110[0])) + (dsp->fConst468 * dsp->fRec110[2]))) - (dsp->fConst461 * ((dsp->fConst469 * dsp->fRec109[2]) + (dsp->fConst470 * dsp->fRec109[1]))));
			dsp->fRec108[0] = ((dsp->fConst461 * (((dsp->fConst462 * dsp->fRec109[1]) + (dsp->fConst471 * dsp->fRec109[0])) + (dsp->fConst471 * dsp->fRec109[2]))) - (dsp->fConst459 * ((dsp->fConst472 * dsp->fRec108[2]) + (dsp->fConst473 * dsp->fRec108[1]))));
			float fTemp72 = (dsp->fConst459 * (((dsp->fConst460 * dsp->fRec108[1]) + (dsp->fConst474 * dsp->fRec108[0])) + (dsp->fConst474 * dsp->fRec108[2])));
			dsp->fRec107[0] = (fTemp72 - (dsp->fConst456 * ((dsp->fConst475 * dsp->fRec107[2]) + (dsp->fConst477 * dsp->fRec107[1]))));
			dsp->fRec106[0] = ((dsp->fConst456 * (((dsp->fConst458 * dsp->fRec107[1]) + (dsp->fConst478 * dsp->fRec107[0])) + (dsp->fConst478 * dsp->fRec107[2]))) - (dsp->fConst453 * ((dsp->fConst479 * dsp->fRec106[2]) + (dsp->fConst480 * dsp->fRec106[1]))));
			dsp->fRec105[0] = ((dsp->fConst453 * (((dsp->fConst455 * dsp->fRec106[1]) + (dsp->fConst481 * dsp->fRec106[0])) + (dsp->fConst481 * dsp->fRec106[2]))) - (dsp->fConst449 * ((dsp->fConst482 * dsp->fRec105[2]) + (dsp->fConst483 * dsp->fRec105[1]))));
			dsp->fRec104[0] = ((fSlow1 * dsp->fRec104[1]) + (fSlow2 * fabsf((dsp->fConst449 * (((dsp->fConst452 * dsp->fRec105[1]) + (dsp->fConst484 * dsp->fRec105[0])) + (dsp->fConst484 * dsp->fRec105[2]))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec104[0]))));
			dsp->fRec117[0] = (fTemp72 - (dsp->fConst501 * ((dsp->fConst504 * dsp->fRec117[2]) + (dsp->fConst505 * dsp->fRec117[1]))));
			dsp->fRec116[0] = ((dsp->fConst501 * (((dsp->fConst503 * dsp->fRec117[1]) + (dsp->fConst506 * dsp->fRec117[0])) + (dsp->fConst506 * dsp->fRec117[2]))) - (dsp->fConst499 * ((dsp->fConst507 * dsp->fRec116[2]) + (dsp->fConst508 * dsp->fRec116[1]))));
			dsp->fRec115[0] = ((dsp->fConst499 * (((dsp->fConst500 * dsp->fRec116[1]) + (dsp->fConst509 * dsp->fRec116[0])) + (dsp->fConst509 * dsp->fRec116[2]))) - (dsp->fConst497 * ((dsp->fConst510 * dsp->fRec115[2]) + (dsp->fConst511 * dsp->fRec115[1]))));
			float fTemp73 = (dsp->fConst497 * (((dsp->fConst498 * dsp->fRec115[1]) + (dsp->fConst512 * dsp->fRec115[0])) + (dsp->fConst512 * dsp->fRec115[2])));
			dsp->fRec114[0] = (fTemp73 - (dsp->fConst494 * ((dsp->fConst513 * dsp->fRec114[2]) + (dsp->fConst515 * dsp->fRec114[1]))));
			dsp->fRec113[0] = ((dsp->fConst494 * (((dsp->fConst496 * dsp->fRec114[1]) + (dsp->fConst516 * dsp->fRec114[0])) + (dsp->fConst516 * dsp->fRec114[2]))) - (dsp->fConst491 * ((dsp->fConst517 * dsp->fRec113[2]) + (dsp->fConst518 * dsp->fRec113[1]))));
			dsp->fRec112[0] = ((dsp->fConst491 * (((dsp->fConst493 * dsp->fRec113[1]) + (dsp->fConst519 * dsp->fRec113[0])) + (dsp->fConst519 * dsp->fRec113[2]))) - (dsp->fConst487 * ((dsp->fConst520 * dsp->fRec112[2]) + (dsp->fConst521 * dsp->fRec112[1]))));
			dsp->fRec111[0] = ((fSlow1 * dsp->fRec111[1]) + (fSlow2 * fabsf((dsp->fConst487 * (((dsp->fConst490 * dsp->fRec112[1]) + (dsp->fConst522 * dsp->fRec112[0])) + (dsp->fConst522 * dsp->fRec112[2]))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec111[0]))));
			dsp->fRec121[0] = (fTemp73 - (dsp->fConst527 * ((dsp->fConst530 * dsp->fRec121[2]) + (dsp->fConst531 * dsp->fRec121[1]))));
			dsp->fRec120[0] = ((dsp->fConst527 * (((dsp->fConst529 * dsp->fRec121[1]) + (dsp->fConst532 * dsp->fRec121[0])) + (dsp->fConst532 * dsp->fRec121[2]))) - (dsp->fConst525 * ((dsp->fConst533 * dsp->fRec120[2]) + (dsp->fConst534 * dsp->fRec120[1]))));
			dsp->fRec119[0] = ((dsp->fConst525 * (((dsp->fConst526 * dsp->fRec120[1]) + (dsp->fConst535 * dsp->fRec120[0])) + (dsp->fConst535 * dsp->fRec120[2]))) - (dsp->fConst523 * ((dsp->fConst536 * dsp->fRec119[2]) + (dsp->fConst537 * dsp->fRec119[1]))));
			dsp->fRec118[0] = ((fSlow1 * dsp->fRec118[1]) + (fSlow2 * fabsf((dsp->fConst523 * (((dsp->fConst524 * dsp->fRec119[1]) + (dsp->fConst538 * dsp->fRec119[0])) + (dsp->fConst538 * dsp->fRec119[2]))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec118[0]))));
			output0[i] = (FAUSTFLOAT)fTemp46;
			output1[i] = (FAUSTFLOAT)fTemp59;
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->iRec11[1] = dsp->iRec11[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec12[j1] = dsp->fRec12[(j1 - 1)];
					
				}
				
			}
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec18[2] = dsp->fRec18[1];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
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
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[1] = dsp->fRec27[0];
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
			dsp->fRec35[2] = dsp->fRec35[1];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[1] = dsp->fRec34[0];
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
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec41[1] = dsp->fRec41[0];
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
			dsp->fRec49[2] = dsp->fRec49[1];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec48[1] = dsp->fRec48[0];
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
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[1] = dsp->fRec55[0];
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
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec62[1] = dsp->fRec62[0];
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
			dsp->fRec70[2] = dsp->fRec70[1];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[1] = dsp->fRec69[0];
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
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[1] = dsp->fRec76[0];
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
			dsp->fRec84[2] = dsp->fRec84[1];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec83[1] = dsp->fRec83[0];
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
			dsp->fRec91[2] = dsp->fRec91[1];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[1] = dsp->fRec90[0];
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
			dsp->fRec98[2] = dsp->fRec98[1];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[1] = dsp->fRec97[0];
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
			dsp->fRec105[2] = dsp->fRec105[1];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec117[2] = dsp->fRec117[1];
			dsp->fRec117[1] = dsp->fRec117[0];
			dsp->fRec116[2] = dsp->fRec116[1];
			dsp->fRec116[1] = dsp->fRec116[0];
			dsp->fRec115[2] = dsp->fRec115[1];
			dsp->fRec115[1] = dsp->fRec115[0];
			dsp->fRec114[2] = dsp->fRec114[1];
			dsp->fRec114[1] = dsp->fRec114[0];
			dsp->fRec113[2] = dsp->fRec113[1];
			dsp->fRec113[1] = dsp->fRec113[0];
			dsp->fRec112[2] = dsp->fRec112[1];
			dsp->fRec112[1] = dsp->fRec112[0];
			dsp->fRec111[1] = dsp->fRec111[0];
			dsp->fRec121[2] = dsp->fRec121[1];
			dsp->fRec121[1] = dsp->fRec121[0];
			dsp->fRec120[2] = dsp->fRec120[1];
			dsp->fRec120[1] = dsp->fRec120[0];
			dsp->fRec119[2] = dsp->fRec119[1];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec118[1] = dsp->fRec118[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
