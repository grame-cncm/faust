/* ------------------------------------------------------------
name: "vcfWahLab"
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
	float fRec4[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	float fConst14;
	FAUSTFLOAT fHslider3;
	float fRec15[2];
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHslider4;
	float fRec17[2];
	FAUSTFLOAT fVslider0;
	float fRec18[2];
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fEntry0;
	float fConst15;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec20[2];
	float fVec1[2];
	float fRec19[2];
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
	float fRec21[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec22[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox6;
	int iRec23[2];
	float fRec24[4];
	float fConst19;
	float fConst20;
	float fRec25[2];
	float fRec26[2];
	float fRec16[3];
	float fRec14[2];
	float fRec13[2];
	float fRec12[2];
	float fRec11[2];
	float fRec10[2];
	FAUSTFLOAT fHslider5;
	float fRec27[2];
	FAUSTFLOAT fHslider6;
	float fRec9[2];
	float fRec8[2];
	float fRec7[2];
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fCheckbox7;
	float fConst21;
	float fRec30[2];
	float fRec29[3];
	float fRec28[3];
	float fRec33[2];
	float fRec31[2];
	float fRec36[2];
	float fRec34[2];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec3[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec2[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec1[3];
	float fConst31;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fConst51;
	float fConst52;
	float fRec43[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec42[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec41[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec40[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec39[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec38[3];
	float fConst69;
	float fRec37[2];
	FAUSTFLOAT fVbargraph1;
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
	float fConst89;
	float fConst90;
	float fRec50[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec49[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec48[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec47[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec46[3];
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec45[3];
	float fConst107;
	float fRec44[2];
	FAUSTFLOAT fVbargraph2;
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
	float fConst127;
	float fConst128;
	float fRec57[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec56[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec55[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec54[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec53[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fRec52[3];
	float fConst145;
	float fRec51[2];
	FAUSTFLOAT fVbargraph3;
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
	float fConst165;
	float fConst166;
	float fRec64[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec63[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fRec62[3];
	float fConst173;
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec61[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec60[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec59[3];
	float fConst183;
	float fRec58[2];
	FAUSTFLOAT fVbargraph4;
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
	float fConst203;
	float fConst204;
	float fRec71[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec70[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec69[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec68[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec67[3];
	float fConst218;
	float fConst219;
	float fConst220;
	float fRec66[3];
	float fConst221;
	float fRec65[2];
	FAUSTFLOAT fVbargraph5;
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
	float fConst241;
	float fConst242;
	float fRec78[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec77[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fRec76[3];
	float fConst249;
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec75[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec74[3];
	float fConst256;
	float fConst257;
	float fConst258;
	float fRec73[3];
	float fConst259;
	float fRec72[2];
	FAUSTFLOAT fVbargraph6;
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
	float fConst279;
	float fConst280;
	float fRec85[3];
	float fConst281;
	float fConst282;
	float fConst283;
	float fRec84[3];
	float fConst284;
	float fConst285;
	float fConst286;
	float fRec83[3];
	float fConst287;
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec82[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec81[3];
	float fConst294;
	float fConst295;
	float fConst296;
	float fRec80[3];
	float fConst297;
	float fRec79[2];
	FAUSTFLOAT fVbargraph7;
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
	float fConst317;
	float fConst318;
	float fRec92[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec91[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fRec90[3];
	float fConst325;
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec89[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec88[3];
	float fConst332;
	float fConst333;
	float fConst334;
	float fRec87[3];
	float fConst335;
	float fRec86[2];
	FAUSTFLOAT fVbargraph8;
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
	float fConst355;
	float fConst356;
	float fRec99[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec98[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fRec97[3];
	float fConst363;
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec96[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec95[3];
	float fConst370;
	float fConst371;
	float fConst372;
	float fRec94[3];
	float fConst373;
	float fRec93[2];
	FAUSTFLOAT fVbargraph9;
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
	float fConst393;
	float fConst394;
	float fRec106[3];
	float fConst395;
	float fConst396;
	float fConst397;
	float fRec105[3];
	float fConst398;
	float fConst399;
	float fConst400;
	float fRec104[3];
	float fConst401;
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec103[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec102[3];
	float fConst408;
	float fConst409;
	float fConst410;
	float fRec101[3];
	float fConst411;
	float fRec100[2];
	FAUSTFLOAT fVbargraph10;
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
	float fConst431;
	float fConst432;
	float fRec113[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec112[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fRec111[3];
	float fConst439;
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec110[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec109[3];
	float fConst446;
	float fConst447;
	float fConst448;
	float fRec108[3];
	float fConst449;
	float fRec107[2];
	FAUSTFLOAT fVbargraph11;
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
	float fConst469;
	float fConst470;
	float fRec120[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec119[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fRec118[3];
	float fConst477;
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec117[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec116[3];
	float fConst484;
	float fConst485;
	float fConst486;
	float fRec115[3];
	float fConst487;
	float fRec114[2];
	FAUSTFLOAT fVbargraph12;
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
	float fConst507;
	float fConst508;
	float fRec127[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec126[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fRec125[3];
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec124[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec123[3];
	float fConst522;
	float fConst523;
	float fConst524;
	float fRec122[3];
	float fConst525;
	float fRec121[2];
	FAUSTFLOAT fVbargraph13;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec131[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec130[3];
	float fConst538;
	float fConst539;
	float fConst540;
	float fRec129[3];
	float fConst541;
	float fRec128[2];
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
	m->declare(m->metaInterface, "description", "Demonstrate competing variable-lowpass-filter effects on test signals with spectrum analysis display");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "vcfWahLab");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
	m->declare(m->metaInterface, "vaeffects.lib/version", "0.0");
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
	dsp->fHslider2 = (FAUSTFLOAT)5.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)200.0f;
	dsp->fCheckbox3 = (FAUSTFLOAT)0.0f;
	dsp->fHslider4 = (FAUSTFLOAT)0.80000000000000004f;
	dsp->fVslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fCheckbox4 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox5 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fVslider1 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fCheckbox6 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)25.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.90000000000000002f;
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
			dsp->fRec15[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec17[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec18[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec20[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fVec1[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec19[l7] = 0.0f;
			
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
			dsp->fVec3[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec4[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec5[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fVec6[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec7[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fVec8[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec21[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec9[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec10[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec11[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec12[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fVec13[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec14[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec15[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec22[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec16[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec17[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec18[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fVec19[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fVec20[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fVec21[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->iRec23[l30] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			dsp->fRec24[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec25[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec26[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			dsp->fRec16[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec14[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fRec13[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec12[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec11[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			dsp->fRec10[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec27[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec9[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec8[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec7[l43] = 0.0f;
			
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
			dsp->fRec5[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec30[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec29[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec28[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fRec33[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec31[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			dsp->fRec36[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec34[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec3[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec2[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec1[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			dsp->fRec0[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			dsp->fRec43[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec42[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			dsp->fRec41[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec40[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			dsp->fRec39[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec38[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			dsp->fRec37[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec50[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec49[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			dsp->fRec48[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec47[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec46[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec45[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			dsp->fRec44[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			dsp->fRec57[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec56[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			dsp->fRec55[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			dsp->fRec54[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec53[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec52[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			dsp->fRec51[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			dsp->fRec64[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec63[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			dsp->fRec62[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec61[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec60[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec59[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			dsp->fRec58[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			dsp->fRec71[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec70[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			dsp->fRec69[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec68[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec67[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec66[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			dsp->fRec65[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			dsp->fRec78[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec77[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			dsp->fRec76[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec75[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec74[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			dsp->fRec73[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			dsp->fRec72[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			dsp->fRec85[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			dsp->fRec84[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			dsp->fRec83[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			dsp->fRec82[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec81[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			dsp->fRec80[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			dsp->fRec79[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			dsp->fRec92[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec91[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			dsp->fRec90[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			dsp->fRec89[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			dsp->fRec88[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			dsp->fRec87[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			dsp->fRec86[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			dsp->fRec99[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			dsp->fRec98[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			dsp->fRec97[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			dsp->fRec96[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			dsp->fRec95[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			dsp->fRec94[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			dsp->fRec93[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			dsp->fRec106[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			dsp->fRec105[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			dsp->fRec104[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec103[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			dsp->fRec102[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			dsp->fRec101[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			dsp->fRec100[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			dsp->fRec113[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec112[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			dsp->fRec111[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			dsp->fRec110[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			dsp->fRec109[l131] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l132;
		for (l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			dsp->fRec108[l132] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l133;
		for (l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			dsp->fRec107[l133] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l134;
		for (l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			dsp->fRec120[l134] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l135;
		for (l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			dsp->fRec119[l135] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l136;
		for (l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			dsp->fRec118[l136] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l137;
		for (l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			dsp->fRec117[l137] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l138;
		for (l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			dsp->fRec116[l138] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l139;
		for (l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			dsp->fRec115[l139] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l140;
		for (l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			dsp->fRec114[l140] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l141;
		for (l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			dsp->fRec127[l141] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l142;
		for (l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			dsp->fRec126[l142] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l143;
		for (l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			dsp->fRec125[l143] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l144;
		for (l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			dsp->fRec124[l144] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l145;
		for (l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			dsp->fRec123[l145] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l146;
		for (l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			dsp->fRec122[l146] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l147;
		for (l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			dsp->fRec121[l147] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l148;
		for (l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			dsp->fRec131[l148] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l149;
		for (l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			dsp->fRec130[l149] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l150;
		for (l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			dsp->fRec129[l150] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l151;
		for (l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			dsp->fRec128[l151] = 0.0f;
			
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
	dsp->fConst19 = (1413.71667f / dsp->fConst0);
	dsp->fConst20 = (2827.43335f / dsp->fConst0);
	dsp->fConst21 = (3.14159274f / dsp->fConst0);
	dsp->fConst22 = (((dsp->fConst3 + -3.18972731f) / dsp->fConst2) + 4.07678175f);
	dsp->fConst23 = (1.0f / dsp->fConst5);
	dsp->fConst24 = (2.0f * (4.07678175f - dsp->fConst23));
	dsp->fConst25 = (dsp->fConst12 + 0.000407678192f);
	dsp->fConst26 = (((dsp->fConst3 + -0.743130445f) / dsp->fConst2) + 1.4500711f);
	dsp->fConst27 = (2.0f * (1.4500711f - dsp->fConst23));
	dsp->fConst28 = (dsp->fConst9 + 1.4500711f);
	dsp->fConst29 = (((dsp->fConst3 + -0.157482162f) / dsp->fConst2) + 0.935140193f);
	dsp->fConst30 = (2.0f * (0.935140193f - dsp->fConst23));
	dsp->fConst31 = (dsp->fConst6 + 0.935140193f);
	dsp->fConst32 = tanf((31665.2695f / dsp->fConst0));
	dsp->fConst33 = (1.0f / dsp->fConst32);
	dsp->fConst34 = (1.0f / (((dsp->fConst33 + 0.157482162f) / dsp->fConst32) + 0.935140193f));
	dsp->fConst35 = mydsp_faustpower2_f(dsp->fConst32);
	dsp->fConst36 = (50.0638084f / dsp->fConst35);
	dsp->fConst37 = (2.0f * (0.935140193f - dsp->fConst36));
	dsp->fConst38 = (1.0f / (((dsp->fConst33 + 0.743130445f) / dsp->fConst32) + 1.4500711f));
	dsp->fConst39 = (11.0520525f / dsp->fConst35);
	dsp->fConst40 = (2.0f * (1.4500711f - dsp->fConst39));
	dsp->fConst41 = (1.0f / (((dsp->fConst33 + 3.18972731f) / dsp->fConst32) + 4.07678175f));
	dsp->fConst42 = (0.00176617282f / dsp->fConst35);
	dsp->fConst43 = (2.0f * (0.000407678192f - dsp->fConst42));
	dsp->fConst44 = (1.0f / (((dsp->fConst3 + 0.168404877f) / dsp->fConst2) + 1.06935835f));
	dsp->fConst45 = (2.0f * (53.5361519f - dsp->fConst23));
	dsp->fConst46 = (1.0f / (((dsp->fConst3 + 0.51247865f) / dsp->fConst2) + 0.689621389f));
	dsp->fConst47 = (2.0f * (7.62173128f - dsp->fConst23));
	dsp->fConst48 = (1.0f / (((dsp->fConst3 + 0.782413065f) / dsp->fConst2) + 0.245291501f));
	dsp->fConst49 = (9.99999975e-05f / dsp->fConst5);
	dsp->fConst50 = (2.0f * (0.000433227193f - dsp->fConst49));
	dsp->fConst51 = (((dsp->fConst3 + -0.782413065f) / dsp->fConst2) + 0.245291501f);
	dsp->fConst52 = (2.0f * (0.245291501f - dsp->fConst23));
	dsp->fConst53 = (dsp->fConst49 + 0.000433227193f);
	dsp->fConst54 = (((dsp->fConst3 + -0.51247865f) / dsp->fConst2) + 0.689621389f);
	dsp->fConst55 = (2.0f * (0.689621389f - dsp->fConst23));
	dsp->fConst56 = (dsp->fConst23 + 7.62173128f);
	dsp->fConst57 = (((dsp->fConst3 + -0.168404877f) / dsp->fConst2) + 1.06935835f);
	dsp->fConst58 = (2.0f * (1.06935835f - dsp->fConst23));
	dsp->fConst59 = (dsp->fConst23 + 53.5361519f);
	dsp->fConst60 = (((dsp->fConst33 + -3.18972731f) / dsp->fConst32) + 4.07678175f);
	dsp->fConst61 = (1.0f / dsp->fConst35);
	dsp->fConst62 = (2.0f * (4.07678175f - dsp->fConst61));
	dsp->fConst63 = (dsp->fConst42 + 0.000407678192f);
	dsp->fConst64 = (((dsp->fConst33 + -0.743130445f) / dsp->fConst32) + 1.4500711f);
	dsp->fConst65 = (2.0f * (1.4500711f - dsp->fConst61));
	dsp->fConst66 = (dsp->fConst39 + 1.4500711f);
	dsp->fConst67 = (((dsp->fConst33 + -0.157482162f) / dsp->fConst32) + 0.935140193f);
	dsp->fConst68 = (2.0f * (0.935140193f - dsp->fConst61));
	dsp->fConst69 = (dsp->fConst36 + 0.935140193f);
	dsp->fConst70 = tanf((19947.8691f / dsp->fConst0));
	dsp->fConst71 = (1.0f / dsp->fConst70);
	dsp->fConst72 = (1.0f / (((dsp->fConst71 + 0.157482162f) / dsp->fConst70) + 0.935140193f));
	dsp->fConst73 = mydsp_faustpower2_f(dsp->fConst70);
	dsp->fConst74 = (50.0638084f / dsp->fConst73);
	dsp->fConst75 = (2.0f * (0.935140193f - dsp->fConst74));
	dsp->fConst76 = (1.0f / (((dsp->fConst71 + 0.743130445f) / dsp->fConst70) + 1.4500711f));
	dsp->fConst77 = (11.0520525f / dsp->fConst73);
	dsp->fConst78 = (2.0f * (1.4500711f - dsp->fConst77));
	dsp->fConst79 = (1.0f / (((dsp->fConst71 + 3.18972731f) / dsp->fConst70) + 4.07678175f));
	dsp->fConst80 = (0.00176617282f / dsp->fConst73);
	dsp->fConst81 = (2.0f * (0.000407678192f - dsp->fConst80));
	dsp->fConst82 = (1.0f / (((dsp->fConst33 + 0.168404877f) / dsp->fConst32) + 1.06935835f));
	dsp->fConst83 = (2.0f * (53.5361519f - dsp->fConst61));
	dsp->fConst84 = (1.0f / (((dsp->fConst33 + 0.51247865f) / dsp->fConst32) + 0.689621389f));
	dsp->fConst85 = (2.0f * (7.62173128f - dsp->fConst61));
	dsp->fConst86 = (1.0f / (((dsp->fConst33 + 0.782413065f) / dsp->fConst32) + 0.245291501f));
	dsp->fConst87 = (9.99999975e-05f / dsp->fConst35);
	dsp->fConst88 = (2.0f * (0.000433227193f - dsp->fConst87));
	dsp->fConst89 = (((dsp->fConst33 + -0.782413065f) / dsp->fConst32) + 0.245291501f);
	dsp->fConst90 = (2.0f * (0.245291501f - dsp->fConst61));
	dsp->fConst91 = (dsp->fConst87 + 0.000433227193f);
	dsp->fConst92 = (((dsp->fConst33 + -0.51247865f) / dsp->fConst32) + 0.689621389f);
	dsp->fConst93 = (2.0f * (0.689621389f - dsp->fConst61));
	dsp->fConst94 = (dsp->fConst61 + 7.62173128f);
	dsp->fConst95 = (((dsp->fConst33 + -0.168404877f) / dsp->fConst32) + 1.06935835f);
	dsp->fConst96 = (2.0f * (1.06935835f - dsp->fConst61));
	dsp->fConst97 = (dsp->fConst61 + 53.5361519f);
	dsp->fConst98 = (((dsp->fConst71 + -3.18972731f) / dsp->fConst70) + 4.07678175f);
	dsp->fConst99 = (1.0f / dsp->fConst73);
	dsp->fConst100 = (2.0f * (4.07678175f - dsp->fConst99));
	dsp->fConst101 = (dsp->fConst80 + 0.000407678192f);
	dsp->fConst102 = (((dsp->fConst71 + -0.743130445f) / dsp->fConst70) + 1.4500711f);
	dsp->fConst103 = (2.0f * (1.4500711f - dsp->fConst99));
	dsp->fConst104 = (dsp->fConst77 + 1.4500711f);
	dsp->fConst105 = (((dsp->fConst71 + -0.157482162f) / dsp->fConst70) + 0.935140193f);
	dsp->fConst106 = (2.0f * (0.935140193f - dsp->fConst99));
	dsp->fConst107 = (dsp->fConst74 + 0.935140193f);
	dsp->fConst108 = tanf((12566.3711f / dsp->fConst0));
	dsp->fConst109 = (1.0f / dsp->fConst108);
	dsp->fConst110 = (1.0f / (((dsp->fConst109 + 0.157482162f) / dsp->fConst108) + 0.935140193f));
	dsp->fConst111 = mydsp_faustpower2_f(dsp->fConst108);
	dsp->fConst112 = (50.0638084f / dsp->fConst111);
	dsp->fConst113 = (2.0f * (0.935140193f - dsp->fConst112));
	dsp->fConst114 = (1.0f / (((dsp->fConst109 + 0.743130445f) / dsp->fConst108) + 1.4500711f));
	dsp->fConst115 = (11.0520525f / dsp->fConst111);
	dsp->fConst116 = (2.0f * (1.4500711f - dsp->fConst115));
	dsp->fConst117 = (1.0f / (((dsp->fConst109 + 3.18972731f) / dsp->fConst108) + 4.07678175f));
	dsp->fConst118 = (0.00176617282f / dsp->fConst111);
	dsp->fConst119 = (2.0f * (0.000407678192f - dsp->fConst118));
	dsp->fConst120 = (1.0f / (((dsp->fConst71 + 0.168404877f) / dsp->fConst70) + 1.06935835f));
	dsp->fConst121 = (2.0f * (53.5361519f - dsp->fConst99));
	dsp->fConst122 = (1.0f / (((dsp->fConst71 + 0.51247865f) / dsp->fConst70) + 0.689621389f));
	dsp->fConst123 = (2.0f * (7.62173128f - dsp->fConst99));
	dsp->fConst124 = (1.0f / (((dsp->fConst71 + 0.782413065f) / dsp->fConst70) + 0.245291501f));
	dsp->fConst125 = (9.99999975e-05f / dsp->fConst73);
	dsp->fConst126 = (2.0f * (0.000433227193f - dsp->fConst125));
	dsp->fConst127 = (((dsp->fConst71 + -0.782413065f) / dsp->fConst70) + 0.245291501f);
	dsp->fConst128 = (2.0f * (0.245291501f - dsp->fConst99));
	dsp->fConst129 = (dsp->fConst125 + 0.000433227193f);
	dsp->fConst130 = (((dsp->fConst71 + -0.51247865f) / dsp->fConst70) + 0.689621389f);
	dsp->fConst131 = (2.0f * (0.689621389f - dsp->fConst99));
	dsp->fConst132 = (dsp->fConst99 + 7.62173128f);
	dsp->fConst133 = (((dsp->fConst71 + -0.168404877f) / dsp->fConst70) + 1.06935835f);
	dsp->fConst134 = (2.0f * (1.06935835f - dsp->fConst99));
	dsp->fConst135 = (dsp->fConst99 + 53.5361519f);
	dsp->fConst136 = (((dsp->fConst109 + -3.18972731f) / dsp->fConst108) + 4.07678175f);
	dsp->fConst137 = (1.0f / dsp->fConst111);
	dsp->fConst138 = (2.0f * (4.07678175f - dsp->fConst137));
	dsp->fConst139 = (dsp->fConst118 + 0.000407678192f);
	dsp->fConst140 = (((dsp->fConst109 + -0.743130445f) / dsp->fConst108) + 1.4500711f);
	dsp->fConst141 = (2.0f * (1.4500711f - dsp->fConst137));
	dsp->fConst142 = (dsp->fConst115 + 1.4500711f);
	dsp->fConst143 = (((dsp->fConst109 + -0.157482162f) / dsp->fConst108) + 0.935140193f);
	dsp->fConst144 = (2.0f * (0.935140193f - dsp->fConst137));
	dsp->fConst145 = (dsp->fConst112 + 0.935140193f);
	dsp->fConst146 = tanf((7916.31738f / dsp->fConst0));
	dsp->fConst147 = (1.0f / dsp->fConst146);
	dsp->fConst148 = (1.0f / (((dsp->fConst147 + 0.157482162f) / dsp->fConst146) + 0.935140193f));
	dsp->fConst149 = mydsp_faustpower2_f(dsp->fConst146);
	dsp->fConst150 = (50.0638084f / dsp->fConst149);
	dsp->fConst151 = (2.0f * (0.935140193f - dsp->fConst150));
	dsp->fConst152 = (1.0f / (((dsp->fConst147 + 0.743130445f) / dsp->fConst146) + 1.4500711f));
	dsp->fConst153 = (11.0520525f / dsp->fConst149);
	dsp->fConst154 = (2.0f * (1.4500711f - dsp->fConst153));
	dsp->fConst155 = (1.0f / (((dsp->fConst147 + 3.18972731f) / dsp->fConst146) + 4.07678175f));
	dsp->fConst156 = (0.00176617282f / dsp->fConst149);
	dsp->fConst157 = (2.0f * (0.000407678192f - dsp->fConst156));
	dsp->fConst158 = (1.0f / (((dsp->fConst109 + 0.168404877f) / dsp->fConst108) + 1.06935835f));
	dsp->fConst159 = (2.0f * (53.5361519f - dsp->fConst137));
	dsp->fConst160 = (1.0f / (((dsp->fConst109 + 0.51247865f) / dsp->fConst108) + 0.689621389f));
	dsp->fConst161 = (2.0f * (7.62173128f - dsp->fConst137));
	dsp->fConst162 = (1.0f / (((dsp->fConst109 + 0.782413065f) / dsp->fConst108) + 0.245291501f));
	dsp->fConst163 = (9.99999975e-05f / dsp->fConst111);
	dsp->fConst164 = (2.0f * (0.000433227193f - dsp->fConst163));
	dsp->fConst165 = (((dsp->fConst109 + -0.782413065f) / dsp->fConst108) + 0.245291501f);
	dsp->fConst166 = (2.0f * (0.245291501f - dsp->fConst137));
	dsp->fConst167 = (dsp->fConst163 + 0.000433227193f);
	dsp->fConst168 = (((dsp->fConst109 + -0.51247865f) / dsp->fConst108) + 0.689621389f);
	dsp->fConst169 = (2.0f * (0.689621389f - dsp->fConst137));
	dsp->fConst170 = (dsp->fConst137 + 7.62173128f);
	dsp->fConst171 = (((dsp->fConst109 + -0.168404877f) / dsp->fConst108) + 1.06935835f);
	dsp->fConst172 = (2.0f * (1.06935835f - dsp->fConst137));
	dsp->fConst173 = (dsp->fConst137 + 53.5361519f);
	dsp->fConst174 = (((dsp->fConst147 + -3.18972731f) / dsp->fConst146) + 4.07678175f);
	dsp->fConst175 = (1.0f / dsp->fConst149);
	dsp->fConst176 = (2.0f * (4.07678175f - dsp->fConst175));
	dsp->fConst177 = (dsp->fConst156 + 0.000407678192f);
	dsp->fConst178 = (((dsp->fConst147 + -0.743130445f) / dsp->fConst146) + 1.4500711f);
	dsp->fConst179 = (2.0f * (1.4500711f - dsp->fConst175));
	dsp->fConst180 = (dsp->fConst153 + 1.4500711f);
	dsp->fConst181 = (((dsp->fConst147 + -0.157482162f) / dsp->fConst146) + 0.935140193f);
	dsp->fConst182 = (2.0f * (0.935140193f - dsp->fConst175));
	dsp->fConst183 = (dsp->fConst150 + 0.935140193f);
	dsp->fConst184 = tanf((4986.96729f / dsp->fConst0));
	dsp->fConst185 = (1.0f / dsp->fConst184);
	dsp->fConst186 = (1.0f / (((dsp->fConst185 + 0.157482162f) / dsp->fConst184) + 0.935140193f));
	dsp->fConst187 = mydsp_faustpower2_f(dsp->fConst184);
	dsp->fConst188 = (50.0638084f / dsp->fConst187);
	dsp->fConst189 = (2.0f * (0.935140193f - dsp->fConst188));
	dsp->fConst190 = (1.0f / (((dsp->fConst185 + 0.743130445f) / dsp->fConst184) + 1.4500711f));
	dsp->fConst191 = (11.0520525f / dsp->fConst187);
	dsp->fConst192 = (2.0f * (1.4500711f - dsp->fConst191));
	dsp->fConst193 = (1.0f / (((dsp->fConst185 + 3.18972731f) / dsp->fConst184) + 4.07678175f));
	dsp->fConst194 = (0.00176617282f / dsp->fConst187);
	dsp->fConst195 = (2.0f * (0.000407678192f - dsp->fConst194));
	dsp->fConst196 = (1.0f / (((dsp->fConst147 + 0.168404877f) / dsp->fConst146) + 1.06935835f));
	dsp->fConst197 = (2.0f * (53.5361519f - dsp->fConst175));
	dsp->fConst198 = (1.0f / (((dsp->fConst147 + 0.51247865f) / dsp->fConst146) + 0.689621389f));
	dsp->fConst199 = (2.0f * (7.62173128f - dsp->fConst175));
	dsp->fConst200 = (1.0f / (((dsp->fConst147 + 0.782413065f) / dsp->fConst146) + 0.245291501f));
	dsp->fConst201 = (9.99999975e-05f / dsp->fConst149);
	dsp->fConst202 = (2.0f * (0.000433227193f - dsp->fConst201));
	dsp->fConst203 = (((dsp->fConst147 + -0.782413065f) / dsp->fConst146) + 0.245291501f);
	dsp->fConst204 = (2.0f * (0.245291501f - dsp->fConst175));
	dsp->fConst205 = (dsp->fConst201 + 0.000433227193f);
	dsp->fConst206 = (((dsp->fConst147 + -0.51247865f) / dsp->fConst146) + 0.689621389f);
	dsp->fConst207 = (2.0f * (0.689621389f - dsp->fConst175));
	dsp->fConst208 = (dsp->fConst175 + 7.62173128f);
	dsp->fConst209 = (((dsp->fConst147 + -0.168404877f) / dsp->fConst146) + 1.06935835f);
	dsp->fConst210 = (2.0f * (1.06935835f - dsp->fConst175));
	dsp->fConst211 = (dsp->fConst175 + 53.5361519f);
	dsp->fConst212 = (((dsp->fConst185 + -3.18972731f) / dsp->fConst184) + 4.07678175f);
	dsp->fConst213 = (1.0f / dsp->fConst187);
	dsp->fConst214 = (2.0f * (4.07678175f - dsp->fConst213));
	dsp->fConst215 = (dsp->fConst194 + 0.000407678192f);
	dsp->fConst216 = (((dsp->fConst185 + -0.743130445f) / dsp->fConst184) + 1.4500711f);
	dsp->fConst217 = (2.0f * (1.4500711f - dsp->fConst213));
	dsp->fConst218 = (dsp->fConst191 + 1.4500711f);
	dsp->fConst219 = (((dsp->fConst185 + -0.157482162f) / dsp->fConst184) + 0.935140193f);
	dsp->fConst220 = (2.0f * (0.935140193f - dsp->fConst213));
	dsp->fConst221 = (dsp->fConst188 + 0.935140193f);
	dsp->fConst222 = tanf((3141.59277f / dsp->fConst0));
	dsp->fConst223 = (1.0f / dsp->fConst222);
	dsp->fConst224 = (1.0f / (((dsp->fConst223 + 0.157482162f) / dsp->fConst222) + 0.935140193f));
	dsp->fConst225 = mydsp_faustpower2_f(dsp->fConst222);
	dsp->fConst226 = (50.0638084f / dsp->fConst225);
	dsp->fConst227 = (2.0f * (0.935140193f - dsp->fConst226));
	dsp->fConst228 = (1.0f / (((dsp->fConst223 + 0.743130445f) / dsp->fConst222) + 1.4500711f));
	dsp->fConst229 = (11.0520525f / dsp->fConst225);
	dsp->fConst230 = (2.0f * (1.4500711f - dsp->fConst229));
	dsp->fConst231 = (1.0f / (((dsp->fConst223 + 3.18972731f) / dsp->fConst222) + 4.07678175f));
	dsp->fConst232 = (0.00176617282f / dsp->fConst225);
	dsp->fConst233 = (2.0f * (0.000407678192f - dsp->fConst232));
	dsp->fConst234 = (1.0f / (((dsp->fConst185 + 0.168404877f) / dsp->fConst184) + 1.06935835f));
	dsp->fConst235 = (2.0f * (53.5361519f - dsp->fConst213));
	dsp->fConst236 = (1.0f / (((dsp->fConst185 + 0.51247865f) / dsp->fConst184) + 0.689621389f));
	dsp->fConst237 = (2.0f * (7.62173128f - dsp->fConst213));
	dsp->fConst238 = (1.0f / (((dsp->fConst185 + 0.782413065f) / dsp->fConst184) + 0.245291501f));
	dsp->fConst239 = (9.99999975e-05f / dsp->fConst187);
	dsp->fConst240 = (2.0f * (0.000433227193f - dsp->fConst239));
	dsp->fConst241 = (((dsp->fConst185 + -0.782413065f) / dsp->fConst184) + 0.245291501f);
	dsp->fConst242 = (2.0f * (0.245291501f - dsp->fConst213));
	dsp->fConst243 = (dsp->fConst239 + 0.000433227193f);
	dsp->fConst244 = (((dsp->fConst185 + -0.51247865f) / dsp->fConst184) + 0.689621389f);
	dsp->fConst245 = (2.0f * (0.689621389f - dsp->fConst213));
	dsp->fConst246 = (dsp->fConst213 + 7.62173128f);
	dsp->fConst247 = (((dsp->fConst185 + -0.168404877f) / dsp->fConst184) + 1.06935835f);
	dsp->fConst248 = (2.0f * (1.06935835f - dsp->fConst213));
	dsp->fConst249 = (dsp->fConst213 + 53.5361519f);
	dsp->fConst250 = (((dsp->fConst223 + -3.18972731f) / dsp->fConst222) + 4.07678175f);
	dsp->fConst251 = (1.0f / dsp->fConst225);
	dsp->fConst252 = (2.0f * (4.07678175f - dsp->fConst251));
	dsp->fConst253 = (dsp->fConst232 + 0.000407678192f);
	dsp->fConst254 = (((dsp->fConst223 + -0.743130445f) / dsp->fConst222) + 1.4500711f);
	dsp->fConst255 = (2.0f * (1.4500711f - dsp->fConst251));
	dsp->fConst256 = (dsp->fConst229 + 1.4500711f);
	dsp->fConst257 = (((dsp->fConst223 + -0.157482162f) / dsp->fConst222) + 0.935140193f);
	dsp->fConst258 = (2.0f * (0.935140193f - dsp->fConst251));
	dsp->fConst259 = (dsp->fConst226 + 0.935140193f);
	dsp->fConst260 = tanf((1979.07935f / dsp->fConst0));
	dsp->fConst261 = (1.0f / dsp->fConst260);
	dsp->fConst262 = (1.0f / (((dsp->fConst261 + 0.157482162f) / dsp->fConst260) + 0.935140193f));
	dsp->fConst263 = mydsp_faustpower2_f(dsp->fConst260);
	dsp->fConst264 = (50.0638084f / dsp->fConst263);
	dsp->fConst265 = (2.0f * (0.935140193f - dsp->fConst264));
	dsp->fConst266 = (1.0f / (((dsp->fConst261 + 0.743130445f) / dsp->fConst260) + 1.4500711f));
	dsp->fConst267 = (11.0520525f / dsp->fConst263);
	dsp->fConst268 = (2.0f * (1.4500711f - dsp->fConst267));
	dsp->fConst269 = (1.0f / (((dsp->fConst261 + 3.18972731f) / dsp->fConst260) + 4.07678175f));
	dsp->fConst270 = (0.00176617282f / dsp->fConst263);
	dsp->fConst271 = (2.0f * (0.000407678192f - dsp->fConst270));
	dsp->fConst272 = (1.0f / (((dsp->fConst223 + 0.168404877f) / dsp->fConst222) + 1.06935835f));
	dsp->fConst273 = (2.0f * (53.5361519f - dsp->fConst251));
	dsp->fConst274 = (1.0f / (((dsp->fConst223 + 0.51247865f) / dsp->fConst222) + 0.689621389f));
	dsp->fConst275 = (2.0f * (7.62173128f - dsp->fConst251));
	dsp->fConst276 = (1.0f / (((dsp->fConst223 + 0.782413065f) / dsp->fConst222) + 0.245291501f));
	dsp->fConst277 = (9.99999975e-05f / dsp->fConst225);
	dsp->fConst278 = (2.0f * (0.000433227193f - dsp->fConst277));
	dsp->fConst279 = (((dsp->fConst223 + -0.782413065f) / dsp->fConst222) + 0.245291501f);
	dsp->fConst280 = (2.0f * (0.245291501f - dsp->fConst251));
	dsp->fConst281 = (dsp->fConst277 + 0.000433227193f);
	dsp->fConst282 = (((dsp->fConst223 + -0.51247865f) / dsp->fConst222) + 0.689621389f);
	dsp->fConst283 = (2.0f * (0.689621389f - dsp->fConst251));
	dsp->fConst284 = (dsp->fConst251 + 7.62173128f);
	dsp->fConst285 = (((dsp->fConst223 + -0.168404877f) / dsp->fConst222) + 1.06935835f);
	dsp->fConst286 = (2.0f * (1.06935835f - dsp->fConst251));
	dsp->fConst287 = (dsp->fConst251 + 53.5361519f);
	dsp->fConst288 = (((dsp->fConst261 + -3.18972731f) / dsp->fConst260) + 4.07678175f);
	dsp->fConst289 = (1.0f / dsp->fConst263);
	dsp->fConst290 = (2.0f * (4.07678175f - dsp->fConst289));
	dsp->fConst291 = (dsp->fConst270 + 0.000407678192f);
	dsp->fConst292 = (((dsp->fConst261 + -0.743130445f) / dsp->fConst260) + 1.4500711f);
	dsp->fConst293 = (2.0f * (1.4500711f - dsp->fConst289));
	dsp->fConst294 = (dsp->fConst267 + 1.4500711f);
	dsp->fConst295 = (((dsp->fConst261 + -0.157482162f) / dsp->fConst260) + 0.935140193f);
	dsp->fConst296 = (2.0f * (0.935140193f - dsp->fConst289));
	dsp->fConst297 = (dsp->fConst264 + 0.935140193f);
	dsp->fConst298 = tanf((1246.74182f / dsp->fConst0));
	dsp->fConst299 = (1.0f / dsp->fConst298);
	dsp->fConst300 = (1.0f / (((dsp->fConst299 + 0.157482162f) / dsp->fConst298) + 0.935140193f));
	dsp->fConst301 = mydsp_faustpower2_f(dsp->fConst298);
	dsp->fConst302 = (50.0638084f / dsp->fConst301);
	dsp->fConst303 = (2.0f * (0.935140193f - dsp->fConst302));
	dsp->fConst304 = (1.0f / (((dsp->fConst299 + 0.743130445f) / dsp->fConst298) + 1.4500711f));
	dsp->fConst305 = (11.0520525f / dsp->fConst301);
	dsp->fConst306 = (2.0f * (1.4500711f - dsp->fConst305));
	dsp->fConst307 = (1.0f / (((dsp->fConst299 + 3.18972731f) / dsp->fConst298) + 4.07678175f));
	dsp->fConst308 = (0.00176617282f / dsp->fConst301);
	dsp->fConst309 = (2.0f * (0.000407678192f - dsp->fConst308));
	dsp->fConst310 = (1.0f / (((dsp->fConst261 + 0.168404877f) / dsp->fConst260) + 1.06935835f));
	dsp->fConst311 = (2.0f * (53.5361519f - dsp->fConst289));
	dsp->fConst312 = (1.0f / (((dsp->fConst261 + 0.51247865f) / dsp->fConst260) + 0.689621389f));
	dsp->fConst313 = (2.0f * (7.62173128f - dsp->fConst289));
	dsp->fConst314 = (1.0f / (((dsp->fConst261 + 0.782413065f) / dsp->fConst260) + 0.245291501f));
	dsp->fConst315 = (9.99999975e-05f / dsp->fConst263);
	dsp->fConst316 = (2.0f * (0.000433227193f - dsp->fConst315));
	dsp->fConst317 = (((dsp->fConst261 + -0.782413065f) / dsp->fConst260) + 0.245291501f);
	dsp->fConst318 = (2.0f * (0.245291501f - dsp->fConst289));
	dsp->fConst319 = (dsp->fConst315 + 0.000433227193f);
	dsp->fConst320 = (((dsp->fConst261 + -0.51247865f) / dsp->fConst260) + 0.689621389f);
	dsp->fConst321 = (2.0f * (0.689621389f - dsp->fConst289));
	dsp->fConst322 = (dsp->fConst289 + 7.62173128f);
	dsp->fConst323 = (((dsp->fConst261 + -0.168404877f) / dsp->fConst260) + 1.06935835f);
	dsp->fConst324 = (2.0f * (1.06935835f - dsp->fConst289));
	dsp->fConst325 = (dsp->fConst289 + 53.5361519f);
	dsp->fConst326 = (((dsp->fConst299 + -3.18972731f) / dsp->fConst298) + 4.07678175f);
	dsp->fConst327 = (1.0f / dsp->fConst301);
	dsp->fConst328 = (2.0f * (4.07678175f - dsp->fConst327));
	dsp->fConst329 = (dsp->fConst308 + 0.000407678192f);
	dsp->fConst330 = (((dsp->fConst299 + -0.743130445f) / dsp->fConst298) + 1.4500711f);
	dsp->fConst331 = (2.0f * (1.4500711f - dsp->fConst327));
	dsp->fConst332 = (dsp->fConst305 + 1.4500711f);
	dsp->fConst333 = (((dsp->fConst299 + -0.157482162f) / dsp->fConst298) + 0.935140193f);
	dsp->fConst334 = (2.0f * (0.935140193f - dsp->fConst327));
	dsp->fConst335 = (dsp->fConst302 + 0.935140193f);
	dsp->fConst336 = tanf((785.398193f / dsp->fConst0));
	dsp->fConst337 = (1.0f / dsp->fConst336);
	dsp->fConst338 = (1.0f / (((dsp->fConst337 + 0.157482162f) / dsp->fConst336) + 0.935140193f));
	dsp->fConst339 = mydsp_faustpower2_f(dsp->fConst336);
	dsp->fConst340 = (50.0638084f / dsp->fConst339);
	dsp->fConst341 = (2.0f * (0.935140193f - dsp->fConst340));
	dsp->fConst342 = (1.0f / (((dsp->fConst337 + 0.743130445f) / dsp->fConst336) + 1.4500711f));
	dsp->fConst343 = (11.0520525f / dsp->fConst339);
	dsp->fConst344 = (2.0f * (1.4500711f - dsp->fConst343));
	dsp->fConst345 = (1.0f / (((dsp->fConst337 + 3.18972731f) / dsp->fConst336) + 4.07678175f));
	dsp->fConst346 = (0.00176617282f / dsp->fConst339);
	dsp->fConst347 = (2.0f * (0.000407678192f - dsp->fConst346));
	dsp->fConst348 = (1.0f / (((dsp->fConst299 + 0.168404877f) / dsp->fConst298) + 1.06935835f));
	dsp->fConst349 = (2.0f * (53.5361519f - dsp->fConst327));
	dsp->fConst350 = (1.0f / (((dsp->fConst299 + 0.51247865f) / dsp->fConst298) + 0.689621389f));
	dsp->fConst351 = (2.0f * (7.62173128f - dsp->fConst327));
	dsp->fConst352 = (1.0f / (((dsp->fConst299 + 0.782413065f) / dsp->fConst298) + 0.245291501f));
	dsp->fConst353 = (9.99999975e-05f / dsp->fConst301);
	dsp->fConst354 = (2.0f * (0.000433227193f - dsp->fConst353));
	dsp->fConst355 = (((dsp->fConst299 + -0.782413065f) / dsp->fConst298) + 0.245291501f);
	dsp->fConst356 = (2.0f * (0.245291501f - dsp->fConst327));
	dsp->fConst357 = (dsp->fConst353 + 0.000433227193f);
	dsp->fConst358 = (((dsp->fConst299 + -0.51247865f) / dsp->fConst298) + 0.689621389f);
	dsp->fConst359 = (2.0f * (0.689621389f - dsp->fConst327));
	dsp->fConst360 = (dsp->fConst327 + 7.62173128f);
	dsp->fConst361 = (((dsp->fConst299 + -0.168404877f) / dsp->fConst298) + 1.06935835f);
	dsp->fConst362 = (2.0f * (1.06935835f - dsp->fConst327));
	dsp->fConst363 = (dsp->fConst327 + 53.5361519f);
	dsp->fConst364 = (((dsp->fConst337 + -3.18972731f) / dsp->fConst336) + 4.07678175f);
	dsp->fConst365 = (1.0f / dsp->fConst339);
	dsp->fConst366 = (2.0f * (4.07678175f - dsp->fConst365));
	dsp->fConst367 = (dsp->fConst346 + 0.000407678192f);
	dsp->fConst368 = (((dsp->fConst337 + -0.743130445f) / dsp->fConst336) + 1.4500711f);
	dsp->fConst369 = (2.0f * (1.4500711f - dsp->fConst365));
	dsp->fConst370 = (dsp->fConst343 + 1.4500711f);
	dsp->fConst371 = (((dsp->fConst337 + -0.157482162f) / dsp->fConst336) + 0.935140193f);
	dsp->fConst372 = (2.0f * (0.935140193f - dsp->fConst365));
	dsp->fConst373 = (dsp->fConst340 + 0.935140193f);
	dsp->fConst374 = tanf((494.769836f / dsp->fConst0));
	dsp->fConst375 = (1.0f / dsp->fConst374);
	dsp->fConst376 = (1.0f / (((dsp->fConst375 + 0.157482162f) / dsp->fConst374) + 0.935140193f));
	dsp->fConst377 = mydsp_faustpower2_f(dsp->fConst374);
	dsp->fConst378 = (50.0638084f / dsp->fConst377);
	dsp->fConst379 = (2.0f * (0.935140193f - dsp->fConst378));
	dsp->fConst380 = (1.0f / (((dsp->fConst375 + 0.743130445f) / dsp->fConst374) + 1.4500711f));
	dsp->fConst381 = (11.0520525f / dsp->fConst377);
	dsp->fConst382 = (2.0f * (1.4500711f - dsp->fConst381));
	dsp->fConst383 = (1.0f / (((dsp->fConst375 + 3.18972731f) / dsp->fConst374) + 4.07678175f));
	dsp->fConst384 = (0.00176617282f / dsp->fConst377);
	dsp->fConst385 = (2.0f * (0.000407678192f - dsp->fConst384));
	dsp->fConst386 = (1.0f / (((dsp->fConst337 + 0.168404877f) / dsp->fConst336) + 1.06935835f));
	dsp->fConst387 = (2.0f * (53.5361519f - dsp->fConst365));
	dsp->fConst388 = (1.0f / (((dsp->fConst337 + 0.51247865f) / dsp->fConst336) + 0.689621389f));
	dsp->fConst389 = (2.0f * (7.62173128f - dsp->fConst365));
	dsp->fConst390 = (1.0f / (((dsp->fConst337 + 0.782413065f) / dsp->fConst336) + 0.245291501f));
	dsp->fConst391 = (9.99999975e-05f / dsp->fConst339);
	dsp->fConst392 = (2.0f * (0.000433227193f - dsp->fConst391));
	dsp->fConst393 = (((dsp->fConst337 + -0.782413065f) / dsp->fConst336) + 0.245291501f);
	dsp->fConst394 = (2.0f * (0.245291501f - dsp->fConst365));
	dsp->fConst395 = (dsp->fConst391 + 0.000433227193f);
	dsp->fConst396 = (((dsp->fConst337 + -0.51247865f) / dsp->fConst336) + 0.689621389f);
	dsp->fConst397 = (2.0f * (0.689621389f - dsp->fConst365));
	dsp->fConst398 = (dsp->fConst365 + 7.62173128f);
	dsp->fConst399 = (((dsp->fConst337 + -0.168404877f) / dsp->fConst336) + 1.06935835f);
	dsp->fConst400 = (2.0f * (1.06935835f - dsp->fConst365));
	dsp->fConst401 = (dsp->fConst365 + 53.5361519f);
	dsp->fConst402 = (((dsp->fConst375 + -3.18972731f) / dsp->fConst374) + 4.07678175f);
	dsp->fConst403 = (1.0f / dsp->fConst377);
	dsp->fConst404 = (2.0f * (4.07678175f - dsp->fConst403));
	dsp->fConst405 = (dsp->fConst384 + 0.000407678192f);
	dsp->fConst406 = (((dsp->fConst375 + -0.743130445f) / dsp->fConst374) + 1.4500711f);
	dsp->fConst407 = (2.0f * (1.4500711f - dsp->fConst403));
	dsp->fConst408 = (dsp->fConst381 + 1.4500711f);
	dsp->fConst409 = (((dsp->fConst375 + -0.157482162f) / dsp->fConst374) + 0.935140193f);
	dsp->fConst410 = (2.0f * (0.935140193f - dsp->fConst403));
	dsp->fConst411 = (dsp->fConst378 + 0.935140193f);
	dsp->fConst412 = tanf((311.685455f / dsp->fConst0));
	dsp->fConst413 = (1.0f / dsp->fConst412);
	dsp->fConst414 = (1.0f / (((dsp->fConst413 + 0.157482162f) / dsp->fConst412) + 0.935140193f));
	dsp->fConst415 = mydsp_faustpower2_f(dsp->fConst412);
	dsp->fConst416 = (50.0638084f / dsp->fConst415);
	dsp->fConst417 = (2.0f * (0.935140193f - dsp->fConst416));
	dsp->fConst418 = (1.0f / (((dsp->fConst413 + 0.743130445f) / dsp->fConst412) + 1.4500711f));
	dsp->fConst419 = (11.0520525f / dsp->fConst415);
	dsp->fConst420 = (2.0f * (1.4500711f - dsp->fConst419));
	dsp->fConst421 = (1.0f / (((dsp->fConst413 + 3.18972731f) / dsp->fConst412) + 4.07678175f));
	dsp->fConst422 = (0.00176617282f / dsp->fConst415);
	dsp->fConst423 = (2.0f * (0.000407678192f - dsp->fConst422));
	dsp->fConst424 = (1.0f / (((dsp->fConst375 + 0.168404877f) / dsp->fConst374) + 1.06935835f));
	dsp->fConst425 = (2.0f * (53.5361519f - dsp->fConst403));
	dsp->fConst426 = (1.0f / (((dsp->fConst375 + 0.51247865f) / dsp->fConst374) + 0.689621389f));
	dsp->fConst427 = (2.0f * (7.62173128f - dsp->fConst403));
	dsp->fConst428 = (1.0f / (((dsp->fConst375 + 0.782413065f) / dsp->fConst374) + 0.245291501f));
	dsp->fConst429 = (9.99999975e-05f / dsp->fConst377);
	dsp->fConst430 = (2.0f * (0.000433227193f - dsp->fConst429));
	dsp->fConst431 = (((dsp->fConst375 + -0.782413065f) / dsp->fConst374) + 0.245291501f);
	dsp->fConst432 = (2.0f * (0.245291501f - dsp->fConst403));
	dsp->fConst433 = (dsp->fConst429 + 0.000433227193f);
	dsp->fConst434 = (((dsp->fConst375 + -0.51247865f) / dsp->fConst374) + 0.689621389f);
	dsp->fConst435 = (2.0f * (0.689621389f - dsp->fConst403));
	dsp->fConst436 = (dsp->fConst403 + 7.62173128f);
	dsp->fConst437 = (((dsp->fConst375 + -0.168404877f) / dsp->fConst374) + 1.06935835f);
	dsp->fConst438 = (2.0f * (1.06935835f - dsp->fConst403));
	dsp->fConst439 = (dsp->fConst403 + 53.5361519f);
	dsp->fConst440 = (((dsp->fConst413 + -3.18972731f) / dsp->fConst412) + 4.07678175f);
	dsp->fConst441 = (1.0f / dsp->fConst415);
	dsp->fConst442 = (2.0f * (4.07678175f - dsp->fConst441));
	dsp->fConst443 = (dsp->fConst422 + 0.000407678192f);
	dsp->fConst444 = (((dsp->fConst413 + -0.743130445f) / dsp->fConst412) + 1.4500711f);
	dsp->fConst445 = (2.0f * (1.4500711f - dsp->fConst441));
	dsp->fConst446 = (dsp->fConst419 + 1.4500711f);
	dsp->fConst447 = (((dsp->fConst413 + -0.157482162f) / dsp->fConst412) + 0.935140193f);
	dsp->fConst448 = (2.0f * (0.935140193f - dsp->fConst441));
	dsp->fConst449 = (dsp->fConst416 + 0.935140193f);
	dsp->fConst450 = tanf((196.349548f / dsp->fConst0));
	dsp->fConst451 = (1.0f / dsp->fConst450);
	dsp->fConst452 = (1.0f / (((dsp->fConst451 + 0.157482162f) / dsp->fConst450) + 0.935140193f));
	dsp->fConst453 = mydsp_faustpower2_f(dsp->fConst450);
	dsp->fConst454 = (50.0638084f / dsp->fConst453);
	dsp->fConst455 = (2.0f * (0.935140193f - dsp->fConst454));
	dsp->fConst456 = (1.0f / (((dsp->fConst451 + 0.743130445f) / dsp->fConst450) + 1.4500711f));
	dsp->fConst457 = (11.0520525f / dsp->fConst453);
	dsp->fConst458 = (2.0f * (1.4500711f - dsp->fConst457));
	dsp->fConst459 = (1.0f / (((dsp->fConst451 + 3.18972731f) / dsp->fConst450) + 4.07678175f));
	dsp->fConst460 = (0.00176617282f / dsp->fConst453);
	dsp->fConst461 = (2.0f * (0.000407678192f - dsp->fConst460));
	dsp->fConst462 = (1.0f / (((dsp->fConst413 + 0.168404877f) / dsp->fConst412) + 1.06935835f));
	dsp->fConst463 = (2.0f * (53.5361519f - dsp->fConst441));
	dsp->fConst464 = (1.0f / (((dsp->fConst413 + 0.51247865f) / dsp->fConst412) + 0.689621389f));
	dsp->fConst465 = (2.0f * (7.62173128f - dsp->fConst441));
	dsp->fConst466 = (1.0f / (((dsp->fConst413 + 0.782413065f) / dsp->fConst412) + 0.245291501f));
	dsp->fConst467 = (9.99999975e-05f / dsp->fConst415);
	dsp->fConst468 = (2.0f * (0.000433227193f - dsp->fConst467));
	dsp->fConst469 = (((dsp->fConst413 + -0.782413065f) / dsp->fConst412) + 0.245291501f);
	dsp->fConst470 = (2.0f * (0.245291501f - dsp->fConst441));
	dsp->fConst471 = (dsp->fConst467 + 0.000433227193f);
	dsp->fConst472 = (((dsp->fConst413 + -0.51247865f) / dsp->fConst412) + 0.689621389f);
	dsp->fConst473 = (2.0f * (0.689621389f - dsp->fConst441));
	dsp->fConst474 = (dsp->fConst441 + 7.62173128f);
	dsp->fConst475 = (((dsp->fConst413 + -0.168404877f) / dsp->fConst412) + 1.06935835f);
	dsp->fConst476 = (2.0f * (1.06935835f - dsp->fConst441));
	dsp->fConst477 = (dsp->fConst441 + 53.5361519f);
	dsp->fConst478 = (((dsp->fConst451 + -3.18972731f) / dsp->fConst450) + 4.07678175f);
	dsp->fConst479 = (1.0f / dsp->fConst453);
	dsp->fConst480 = (2.0f * (4.07678175f - dsp->fConst479));
	dsp->fConst481 = (dsp->fConst460 + 0.000407678192f);
	dsp->fConst482 = (((dsp->fConst451 + -0.743130445f) / dsp->fConst450) + 1.4500711f);
	dsp->fConst483 = (2.0f * (1.4500711f - dsp->fConst479));
	dsp->fConst484 = (dsp->fConst457 + 1.4500711f);
	dsp->fConst485 = (((dsp->fConst451 + -0.157482162f) / dsp->fConst450) + 0.935140193f);
	dsp->fConst486 = (2.0f * (0.935140193f - dsp->fConst479));
	dsp->fConst487 = (dsp->fConst454 + 0.935140193f);
	dsp->fConst488 = tanf((123.692459f / dsp->fConst0));
	dsp->fConst489 = (1.0f / dsp->fConst488);
	dsp->fConst490 = (1.0f / (((dsp->fConst489 + 0.157482162f) / dsp->fConst488) + 0.935140193f));
	dsp->fConst491 = mydsp_faustpower2_f(dsp->fConst488);
	dsp->fConst492 = (50.0638084f / dsp->fConst491);
	dsp->fConst493 = (2.0f * (0.935140193f - dsp->fConst492));
	dsp->fConst494 = (1.0f / (((dsp->fConst489 + 0.743130445f) / dsp->fConst488) + 1.4500711f));
	dsp->fConst495 = (11.0520525f / dsp->fConst491);
	dsp->fConst496 = (2.0f * (1.4500711f - dsp->fConst495));
	dsp->fConst497 = (1.0f / (((dsp->fConst489 + 3.18972731f) / dsp->fConst488) + 4.07678175f));
	dsp->fConst498 = (0.00176617282f / dsp->fConst491);
	dsp->fConst499 = (2.0f * (0.000407678192f - dsp->fConst498));
	dsp->fConst500 = (1.0f / (((dsp->fConst451 + 0.168404877f) / dsp->fConst450) + 1.06935835f));
	dsp->fConst501 = (2.0f * (53.5361519f - dsp->fConst479));
	dsp->fConst502 = (1.0f / (((dsp->fConst451 + 0.51247865f) / dsp->fConst450) + 0.689621389f));
	dsp->fConst503 = (2.0f * (7.62173128f - dsp->fConst479));
	dsp->fConst504 = (1.0f / (((dsp->fConst451 + 0.782413065f) / dsp->fConst450) + 0.245291501f));
	dsp->fConst505 = (9.99999975e-05f / dsp->fConst453);
	dsp->fConst506 = (2.0f * (0.000433227193f - dsp->fConst505));
	dsp->fConst507 = (((dsp->fConst451 + -0.782413065f) / dsp->fConst450) + 0.245291501f);
	dsp->fConst508 = (2.0f * (0.245291501f - dsp->fConst479));
	dsp->fConst509 = (dsp->fConst505 + 0.000433227193f);
	dsp->fConst510 = (((dsp->fConst451 + -0.51247865f) / dsp->fConst450) + 0.689621389f);
	dsp->fConst511 = (2.0f * (0.689621389f - dsp->fConst479));
	dsp->fConst512 = (dsp->fConst479 + 7.62173128f);
	dsp->fConst513 = (((dsp->fConst451 + -0.168404877f) / dsp->fConst450) + 1.06935835f);
	dsp->fConst514 = (2.0f * (1.06935835f - dsp->fConst479));
	dsp->fConst515 = (dsp->fConst479 + 53.5361519f);
	dsp->fConst516 = (((dsp->fConst489 + -3.18972731f) / dsp->fConst488) + 4.07678175f);
	dsp->fConst517 = (1.0f / dsp->fConst491);
	dsp->fConst518 = (2.0f * (4.07678175f - dsp->fConst517));
	dsp->fConst519 = (dsp->fConst498 + 0.000407678192f);
	dsp->fConst520 = (((dsp->fConst489 + -0.743130445f) / dsp->fConst488) + 1.4500711f);
	dsp->fConst521 = (2.0f * (1.4500711f - dsp->fConst517));
	dsp->fConst522 = (dsp->fConst495 + 1.4500711f);
	dsp->fConst523 = (((dsp->fConst489 + -0.157482162f) / dsp->fConst488) + 0.935140193f);
	dsp->fConst524 = (2.0f * (0.935140193f - dsp->fConst517));
	dsp->fConst525 = (dsp->fConst492 + 0.935140193f);
	dsp->fConst526 = (1.0f / (((dsp->fConst489 + 0.168404877f) / dsp->fConst488) + 1.06935835f));
	dsp->fConst527 = (2.0f * (53.5361519f - dsp->fConst517));
	dsp->fConst528 = (1.0f / (((dsp->fConst489 + 0.51247865f) / dsp->fConst488) + 0.689621389f));
	dsp->fConst529 = (2.0f * (7.62173128f - dsp->fConst517));
	dsp->fConst530 = (1.0f / (((dsp->fConst489 + 0.782413065f) / dsp->fConst488) + 0.245291501f));
	dsp->fConst531 = (9.99999975e-05f / dsp->fConst491);
	dsp->fConst532 = (2.0f * (0.000433227193f - dsp->fConst531));
	dsp->fConst533 = (((dsp->fConst489 + -0.782413065f) / dsp->fConst488) + 0.245291501f);
	dsp->fConst534 = (2.0f * (0.245291501f - dsp->fConst517));
	dsp->fConst535 = (dsp->fConst531 + 0.000433227193f);
	dsp->fConst536 = (((dsp->fConst489 + -0.51247865f) / dsp->fConst488) + 0.689621389f);
	dsp->fConst537 = (2.0f * (0.689621389f - dsp->fConst517));
	dsp->fConst538 = (dsp->fConst517 + 7.62173128f);
	dsp->fConst539 = (((dsp->fConst489 + -0.168404877f) / dsp->fConst488) + 1.06935835f);
	dsp->fConst540 = (2.0f * (1.06935835f - dsp->fConst517));
	dsp->fConst541 = (dsp->fConst517 + 53.5361519f);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "vcfWahLab");
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
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox5, "0", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Noise (White or Pink - uses only Amplitude control on   the left)", &dsp->fCheckbox5);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox6, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox6, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink instead of White Noise (also called 1/f Noise)", &dsp->fCheckbox6);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox4, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "External Signal Input (overrides Sawtooth/Noise   selection above)", &dsp->fCheckbox4);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "CRYBABY");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "tooltip", "When this is checked, the wah   pedal has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox3);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Wah parameter", &dsp->fHslider4, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "Fourth-order wah effect made using moog_vcf");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "WAH4");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "tooltip", "When this is checked, the wah pedal has   no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "scale", "log");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "wah resonance   frequency in Hz");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Resonance Frequency", &dsp->fHslider3, 200.0f, 100.0f, 2000.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "4", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's   vaeffects.lib for info and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "MOOG VCF (Voltage Controlled Filter)");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the Moog VCF   has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Use Biquads", &dsp->fCheckbox1);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox7, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox7, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Normalized Ladders", &dsp->fCheckbox7);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider5, "unit", "PK");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Corner Frequency", &dsp->fHslider5, 25.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider6, "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Corner Resonance", &dsp->fHslider6, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "tooltip", "output level in decibels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider2, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "VCF Output Level", &dsp->fHslider2, 5.0f, -60.0f, 20.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "5", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a4c49c0", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a4b2f00", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a490c50", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a46e9a0", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a44c6f0", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a42a440", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a408190", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a3e1f60", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a3bfcb0", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a39da00", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a37b750", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a3594a0", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a3371f0", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a314f40", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fdf6a2edc80", &dsp->fVbargraph0, -50.0f, 10.0f);
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
	float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider2)));
	int iSlow5 = (int)(float)dsp->fCheckbox1;
	int iSlow6 = (int)(float)dsp->fCheckbox2;
	float fSlow7 = (0.00100000005f * (float)dsp->fHslider3);
	int iSlow8 = (int)(float)dsp->fCheckbox3;
	float fSlow9 = (float)dsp->fHslider4;
	float fSlow10 = (9.99999975e-05f * powf(4.0f, fSlow9));
	float fSlow11 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	int iSlow12 = (int)(float)dsp->fCheckbox4;
	int iSlow13 = (int)(float)dsp->fCheckbox5;
	int iSlow14 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow15 = (iSlow14 >= 2);
	int iSlow16 = (iSlow14 >= 1);
	float fSlow17 = expf((0.0f - (dsp->fConst15 / (float)dsp->fVslider2)));
	float fSlow18 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fVslider1 + -49.0f))) * (1.0f - fSlow17)));
	int iSlow19 = (iSlow14 >= 3);
	float fSlow20 = ((0.00999999978f * (float)dsp->fVslider3) + 1.0f);
	float fSlow21 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	int iSlow22 = (int)(float)dsp->fCheckbox6;
	float fSlow23 = powf(2.0f, (2.29999995f * fSlow9));
	float fSlow24 = (1.0f - (dsp->fConst19 * (fSlow23 / powf(2.0f, ((2.0f * (1.0f - fSlow9)) + 1.0f)))));
	float fSlow25 = (0.00100000005f * (0.0f - (2.0f * (fSlow24 * cosf((dsp->fConst20 * fSlow23))))));
	float fSlow26 = (0.00100000005f * mydsp_faustpower2_f(fSlow24));
	float fSlow27 = (0.439999998f * powf(2.0f, (0.0833333358f * ((float)dsp->fHslider5 + -49.0f))));
	float fSlow28 = (float)dsp->fHslider6;
	float fSlow29 = (0.0f - (4.0f * max(0.0f, min(mydsp_faustpower4_f(fSlow28), 0.999998987f))));
	int iSlow30 = (int)(float)dsp->fCheckbox7;
	float fSlow31 = min(1.41419947f, (1.41421354f * fSlow28));
	float fSlow32 = (fSlow31 * (fSlow31 + 1.41421354f));
	float fSlow33 = (1.41421354f * fSlow31);
	float fSlow34 = (fSlow33 + 2.0f);
	float fSlow35 = (fSlow31 * (fSlow31 + -1.41421354f));
	float fSlow36 = (2.0f - fSlow33);
	float fSlow37 = mydsp_faustpower2_f((1.41419947f * fSlow28));
	float fSlow38 = (1.99997997f * fSlow28);
	float fSlow39 = (fSlow37 + fSlow38);
	float fSlow40 = (fSlow38 + 2.0f);
	float fSlow41 = (2.0f - fSlow38);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec4[0] = (fSlow4 + (0.999000013f * dsp->fRec4[1]));
			dsp->fRec15[0] = (fSlow7 + (0.999000013f * dsp->fRec15[1]));
			float fTemp0 = (dsp->fConst14 * dsp->fRec15[0]);
			float fTemp1 = (1.0f - fTemp0);
			dsp->fRec17[0] = (fSlow10 + (0.999000013f * dsp->fRec17[1]));
			dsp->fRec18[0] = (fSlow11 + (0.999000013f * dsp->fRec18[1]));
			dsp->fRec20[0] = (fSlow18 + (fSlow17 * dsp->fRec20[1]));
			float fTemp2 = max(20.0f, fabsf(dsp->fRec20[0]));
			dsp->fVec1[0] = fTemp2;
			float fTemp3 = (dsp->fRec19[1] + (dsp->fConst15 * dsp->fVec1[1]));
			dsp->fRec19[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = (2.0f * dsp->fRec19[0]);
			float fTemp5 = (fTemp4 + -1.0f);
			float fTemp6 = mydsp_faustpower2_f(fTemp5);
			dsp->fVec2[0] = fTemp6;
			float fTemp7 = mydsp_faustpower3_f(fTemp5);
			dsp->fVec3[0] = (fTemp7 + (1.0f - fTemp4));
			float fTemp8 = ((fTemp7 + (1.0f - (fTemp4 + dsp->fVec3[1]))) / fTemp2);
			dsp->fVec4[0] = fTemp8;
			float fTemp9 = (fTemp6 * (fTemp6 + -2.0f));
			dsp->fVec5[0] = fTemp9;
			float fTemp10 = ((fTemp9 - dsp->fVec5[1]) / fTemp2);
			dsp->fVec6[0] = fTemp10;
			float fTemp11 = ((fTemp10 - dsp->fVec6[1]) / fTemp2);
			dsp->fVec7[0] = fTemp11;
			float fTemp12 = max(20.0f, fabsf((fSlow20 * dsp->fRec20[0])));
			dsp->fVec8[0] = fTemp12;
			float fTemp13 = (dsp->fRec21[1] + (dsp->fConst15 * dsp->fVec8[1]));
			dsp->fRec21[0] = (fTemp13 - floorf(fTemp13));
			float fTemp14 = (2.0f * dsp->fRec21[0]);
			float fTemp15 = (fTemp14 + -1.0f);
			float fTemp16 = mydsp_faustpower2_f(fTemp15);
			dsp->fVec9[0] = fTemp16;
			float fTemp17 = mydsp_faustpower3_f(fTemp15);
			dsp->fVec10[0] = (fTemp17 + (1.0f - fTemp14));
			float fTemp18 = ((fTemp17 + (1.0f - (fTemp14 + dsp->fVec10[1]))) / fTemp12);
			dsp->fVec11[0] = fTemp18;
			float fTemp19 = (fTemp16 * (fTemp16 + -2.0f));
			dsp->fVec12[0] = fTemp19;
			float fTemp20 = ((fTemp19 - dsp->fVec12[1]) / fTemp12);
			dsp->fVec13[0] = fTemp20;
			float fTemp21 = ((fTemp20 - dsp->fVec13[1]) / fTemp12);
			dsp->fVec14[0] = fTemp21;
			float fTemp22 = max(20.0f, fabsf((fSlow21 * dsp->fRec20[0])));
			dsp->fVec15[0] = fTemp22;
			float fTemp23 = (dsp->fRec22[1] + (dsp->fConst15 * dsp->fVec15[1]));
			dsp->fRec22[0] = (fTemp23 - floorf(fTemp23));
			float fTemp24 = (2.0f * dsp->fRec22[0]);
			float fTemp25 = (fTemp24 + -1.0f);
			float fTemp26 = mydsp_faustpower2_f(fTemp25);
			dsp->fVec16[0] = fTemp26;
			float fTemp27 = mydsp_faustpower3_f(fTemp25);
			dsp->fVec17[0] = (fTemp27 + (1.0f - fTemp24));
			float fTemp28 = ((fTemp27 + (1.0f - (fTemp24 + dsp->fVec17[1]))) / fTemp22);
			dsp->fVec18[0] = fTemp28;
			float fTemp29 = (fTemp26 * (fTemp26 + -2.0f));
			dsp->fVec19[0] = fTemp29;
			float fTemp30 = ((fTemp29 - dsp->fVec19[1]) / fTemp22);
			dsp->fVec20[0] = fTemp30;
			float fTemp31 = ((fTemp30 - dsp->fVec20[1]) / fTemp22);
			dsp->fVec21[0] = fTemp31;
			dsp->iRec23[0] = ((1103515245 * dsp->iRec23[1]) + 12345);
			float fTemp32 = (4.65661287e-10f * (float)dsp->iRec23[0]);
			dsp->fRec24[0] = (((0.522189379f * dsp->fRec24[3]) + (fTemp32 + (2.49495602f * dsp->fRec24[1]))) - (2.0172658f * dsp->fRec24[2]));
			float fTemp33 = (dsp->fRec18[0] * (iSlow12?(float)input0[i]:(iSlow13?(iSlow22?(((0.0499220341f * dsp->fRec24[0]) + (0.0506126992f * dsp->fRec24[2])) - ((0.0959935337f * dsp->fRec24[1]) + (0.00440878607f * dsp->fRec24[3]))):fTemp32):(0.333333343f * (dsp->fRec18[0] * (((iSlow15?(iSlow19?(dsp->fConst18 * (((float)dsp->iVec0[3] * (fTemp11 - dsp->fVec7[1])) / fTemp2)):(dsp->fConst17 * (((float)dsp->iVec0[2] * (fTemp8 - dsp->fVec4[1])) / fTemp2))):(iSlow16?(dsp->fConst16 * (((float)dsp->iVec0[1] * (fTemp6 - dsp->fVec2[1])) / fTemp2)):fTemp5)) + (iSlow15?(iSlow19?(dsp->fConst18 * (((float)dsp->iVec0[3] * (fTemp21 - dsp->fVec14[1])) / fTemp12)):(dsp->fConst17 * (((float)dsp->iVec0[2] * (fTemp18 - dsp->fVec11[1])) / fTemp12))):(iSlow16?(dsp->fConst16 * (((float)dsp->iVec0[1] * (fTemp16 - dsp->fVec9[1])) / fTemp12)):fTemp15))) + (iSlow15?(iSlow19?(dsp->fConst18 * (((float)dsp->iVec0[3] * (fTemp31 - dsp->fVec21[1])) / fTemp22)):(dsp->fConst17 * (((float)dsp->iVec0[2] * (fTemp28 - dsp->fVec18[1])) / fTemp22))):(iSlow16?(dsp->fConst16 * (((float)dsp->iVec0[1] * (fTemp26 - dsp->fVec16[1])) / fTemp22)):fTemp25))))))));
			dsp->fRec25[0] = (fSlow25 + (0.999000013f * dsp->fRec25[1]));
			dsp->fRec26[0] = (fSlow26 + (0.999000013f * dsp->fRec26[1]));
			dsp->fRec16[0] = ((dsp->fRec17[0] * (iSlow8?0.0f:fTemp33)) - ((dsp->fRec25[0] * dsp->fRec16[1]) + (dsp->fRec26[0] * dsp->fRec16[2])));
			float fTemp34 = (iSlow8?fTemp33:(dsp->fRec16[0] - dsp->fRec16[1]));
			dsp->fRec14[0] = (((fTemp1 * dsp->fRec14[1]) + (iSlow6?0.0f:fTemp34)) - (3.20000005f * dsp->fRec10[1]));
			dsp->fRec13[0] = (dsp->fRec14[0] + (fTemp1 * dsp->fRec13[1]));
			dsp->fRec12[0] = (dsp->fRec13[0] + (fTemp1 * dsp->fRec12[1]));
			dsp->fRec11[0] = (dsp->fRec12[0] + (dsp->fRec11[1] * fTemp1));
			dsp->fRec10[0] = (dsp->fRec11[0] * powf(fTemp0, 4.0f));
			float fTemp35 = (iSlow6?fTemp34:(4.0f * dsp->fRec10[0]));
			float fTemp36 = (iSlow3?0.0f:fTemp35);
			dsp->fRec27[0] = (fSlow27 + (0.999000013f * dsp->fRec27[1]));
			float fTemp37 = (dsp->fConst14 * dsp->fRec27[0]);
			float fTemp38 = (1.0f - fTemp37);
			dsp->fRec9[0] = (fTemp36 + ((fTemp38 * dsp->fRec9[1]) + (fSlow29 * dsp->fRec5[1])));
			dsp->fRec8[0] = (dsp->fRec9[0] + (fTemp38 * dsp->fRec8[1]));
			dsp->fRec7[0] = (dsp->fRec8[0] + (fTemp38 * dsp->fRec7[1]));
			dsp->fRec6[0] = (dsp->fRec7[0] + (dsp->fRec6[1] * fTemp38));
			dsp->fRec5[0] = (dsp->fRec6[0] * powf(fTemp37, 4.0f));
			dsp->fRec30[0] = (fSlow27 + (0.999000013f * dsp->fRec30[1]));
			float fTemp39 = tanf((dsp->fConst21 * max(20.0f, min(10000.0f, dsp->fRec30[0]))));
			float fTemp40 = (1.0f / fTemp39);
			float fTemp41 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp39)));
			float fTemp42 = (fSlow32 + (((fSlow34 + fTemp40) / fTemp39) + 1.0f));
			dsp->fRec29[0] = (fTemp36 - (((dsp->fRec29[2] * (fSlow32 + (((fTemp40 - fSlow34) / fTemp39) + 1.0f))) + (2.0f * (dsp->fRec29[1] * (fSlow32 + fTemp41)))) / fTemp42));
			float fTemp43 = (fSlow35 + (((fSlow36 + fTemp40) / fTemp39) + 1.0f));
			dsp->fRec28[0] = (((dsp->fRec29[2] + (dsp->fRec29[0] + (2.0f * dsp->fRec29[1]))) / fTemp42) - (((dsp->fRec28[2] * (fSlow35 + (((fTemp40 - fSlow36) / fTemp39) + 1.0f))) + (2.0f * (dsp->fRec28[1] * (fSlow35 + fTemp41)))) / fTemp43));
			float fTemp44 = tanf((dsp->fConst21 * max(dsp->fRec30[0], 20.0f)));
			float fTemp45 = (1.0f / fTemp44);
			float fTemp46 = (fSlow39 + (((fSlow40 + fTemp45) / fTemp44) + 1.0f));
			float fTemp47 = ((fSlow39 + (1.0f - ((fSlow40 - fTemp45) / fTemp44))) / fTemp46);
			float fTemp48 = max(-0.999899983f, min(0.999899983f, fTemp47));
			float fTemp49 = (1.0f - mydsp_faustpower2_f(fTemp48));
			float fTemp50 = sqrtf(max(0.0f, fTemp49));
			float fTemp51 = ((dsp->fRec31[1] * (0.0f - fTemp48)) + (fTemp36 * fTemp50));
			float fTemp52 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp44)));
			float fTemp53 = (fSlow39 + fTemp52);
			float fTemp54 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp53 / (fTemp46 * (fTemp47 + 1.0f))))));
			float fTemp55 = (1.0f - mydsp_faustpower2_f(fTemp54));
			float fTemp56 = sqrtf(max(0.0f, fTemp55));
			dsp->fRec33[0] = ((dsp->fRec33[1] * (0.0f - fTemp54)) + (fTemp51 * fTemp56));
			dsp->fRec31[0] = ((fTemp51 * fTemp54) + (dsp->fRec33[1] * fTemp56));
			float fRec32 = dsp->fRec33[0];
			float fTemp57 = (1.0f - (fTemp53 / fTemp46));
			float fTemp58 = sqrtf(fTemp49);
			float fTemp59 = ((((fTemp36 * fTemp48) + (dsp->fRec31[1] * fTemp50)) + (2.0f * ((dsp->fRec31[0] * fTemp57) / fTemp58))) + ((fRec32 * ((1.0f - fTemp47) - (2.0f * (fTemp54 * fTemp57)))) / (fTemp58 * sqrtf(fTemp55))));
			float fTemp60 = (fSlow37 + ((((fSlow41 + fTemp45) / fTemp44) + 1.0f) - fSlow38));
			float fTemp61 = ((fSlow37 + ((((fTemp45 - fSlow41) / fTemp44) + 1.0f) - fSlow38)) / fTemp60);
			float fTemp62 = max(-0.999899983f, min(0.999899983f, fTemp61));
			float fTemp63 = (1.0f - mydsp_faustpower2_f(fTemp62));
			float fTemp64 = sqrtf(max(0.0f, fTemp63));
			float fTemp65 = ((dsp->fRec34[1] * (0.0f - fTemp62)) + ((fTemp59 * fTemp64) / fTemp46));
			float fTemp66 = (fSlow37 + (fTemp52 - fSlow38));
			float fTemp67 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp66 / (fTemp60 * (fTemp61 + 1.0f))))));
			float fTemp68 = (1.0f - mydsp_faustpower2_f(fTemp67));
			float fTemp69 = sqrtf(max(0.0f, fTemp68));
			dsp->fRec36[0] = ((dsp->fRec36[1] * (0.0f - fTemp67)) + (fTemp65 * fTemp69));
			dsp->fRec34[0] = ((fTemp65 * fTemp67) + (dsp->fRec36[1] * fTemp69));
			float fRec35 = dsp->fRec36[0];
			float fTemp70 = (1.0f - (fTemp66 / fTemp60));
			float fTemp71 = sqrtf(fTemp63);
			float fTemp72 = (iSlow3?fTemp35:(dsp->fRec4[0] * (iSlow5?(iSlow30?((((((fTemp59 * fTemp62) / fTemp46) + (dsp->fRec34[1] * fTemp64)) + (2.0f * ((dsp->fRec34[0] * fTemp70) / fTemp71))) + ((fRec35 * ((1.0f - fTemp61) - (2.0f * (fTemp67 * fTemp70)))) / (fTemp71 * sqrtf(fTemp68)))) / fTemp60):((dsp->fRec28[2] + (dsp->fRec28[0] + (2.0f * dsp->fRec28[1]))) / fTemp43)):dsp->fRec5[0])));
			dsp->fRec3[0] = (fTemp72 - (dsp->fConst11 * ((dsp->fConst22 * dsp->fRec3[2]) + (dsp->fConst24 * dsp->fRec3[1]))));
			dsp->fRec2[0] = ((dsp->fConst11 * (((dsp->fConst13 * dsp->fRec3[1]) + (dsp->fConst25 * dsp->fRec3[0])) + (dsp->fConst25 * dsp->fRec3[2]))) - (dsp->fConst8 * ((dsp->fConst26 * dsp->fRec2[2]) + (dsp->fConst27 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst8 * (((dsp->fConst10 * dsp->fRec2[1]) + (dsp->fConst28 * dsp->fRec2[0])) + (dsp->fConst28 * dsp->fRec2[2]))) - (dsp->fConst4 * ((dsp->fConst29 * dsp->fRec1[2]) + (dsp->fConst30 * dsp->fRec1[1]))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * fabsf((dsp->fConst4 * (((dsp->fConst7 * dsp->fRec1[1]) + (dsp->fConst31 * dsp->fRec1[0])) + (dsp->fConst31 * dsp->fRec1[2]))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec0[0]))));
			dsp->fRec43[0] = (fTemp72 - (dsp->fConst48 * ((dsp->fConst51 * dsp->fRec43[2]) + (dsp->fConst52 * dsp->fRec43[1]))));
			dsp->fRec42[0] = ((dsp->fConst48 * (((dsp->fConst50 * dsp->fRec43[1]) + (dsp->fConst53 * dsp->fRec43[0])) + (dsp->fConst53 * dsp->fRec43[2]))) - (dsp->fConst46 * ((dsp->fConst54 * dsp->fRec42[2]) + (dsp->fConst55 * dsp->fRec42[1]))));
			dsp->fRec41[0] = ((dsp->fConst46 * (((dsp->fConst47 * dsp->fRec42[1]) + (dsp->fConst56 * dsp->fRec42[0])) + (dsp->fConst56 * dsp->fRec42[2]))) - (dsp->fConst44 * ((dsp->fConst57 * dsp->fRec41[2]) + (dsp->fConst58 * dsp->fRec41[1]))));
			float fTemp73 = (dsp->fConst44 * (((dsp->fConst45 * dsp->fRec41[1]) + (dsp->fConst59 * dsp->fRec41[0])) + (dsp->fConst59 * dsp->fRec41[2])));
			dsp->fRec40[0] = (fTemp73 - (dsp->fConst41 * ((dsp->fConst60 * dsp->fRec40[2]) + (dsp->fConst62 * dsp->fRec40[1]))));
			dsp->fRec39[0] = ((dsp->fConst41 * (((dsp->fConst43 * dsp->fRec40[1]) + (dsp->fConst63 * dsp->fRec40[0])) + (dsp->fConst63 * dsp->fRec40[2]))) - (dsp->fConst38 * ((dsp->fConst64 * dsp->fRec39[2]) + (dsp->fConst65 * dsp->fRec39[1]))));
			dsp->fRec38[0] = ((dsp->fConst38 * (((dsp->fConst40 * dsp->fRec39[1]) + (dsp->fConst66 * dsp->fRec39[0])) + (dsp->fConst66 * dsp->fRec39[2]))) - (dsp->fConst34 * ((dsp->fConst67 * dsp->fRec38[2]) + (dsp->fConst68 * dsp->fRec38[1]))));
			dsp->fRec37[0] = ((fSlow1 * dsp->fRec37[1]) + (fSlow2 * fabsf((dsp->fConst34 * (((dsp->fConst37 * dsp->fRec38[1]) + (dsp->fConst69 * dsp->fRec38[0])) + (dsp->fConst69 * dsp->fRec38[2]))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec37[0]))));
			dsp->fRec50[0] = (fTemp73 - (dsp->fConst86 * ((dsp->fConst89 * dsp->fRec50[2]) + (dsp->fConst90 * dsp->fRec50[1]))));
			dsp->fRec49[0] = ((dsp->fConst86 * (((dsp->fConst88 * dsp->fRec50[1]) + (dsp->fConst91 * dsp->fRec50[0])) + (dsp->fConst91 * dsp->fRec50[2]))) - (dsp->fConst84 * ((dsp->fConst92 * dsp->fRec49[2]) + (dsp->fConst93 * dsp->fRec49[1]))));
			dsp->fRec48[0] = ((dsp->fConst84 * (((dsp->fConst85 * dsp->fRec49[1]) + (dsp->fConst94 * dsp->fRec49[0])) + (dsp->fConst94 * dsp->fRec49[2]))) - (dsp->fConst82 * ((dsp->fConst95 * dsp->fRec48[2]) + (dsp->fConst96 * dsp->fRec48[1]))));
			float fTemp74 = (dsp->fConst82 * (((dsp->fConst83 * dsp->fRec48[1]) + (dsp->fConst97 * dsp->fRec48[0])) + (dsp->fConst97 * dsp->fRec48[2])));
			dsp->fRec47[0] = (fTemp74 - (dsp->fConst79 * ((dsp->fConst98 * dsp->fRec47[2]) + (dsp->fConst100 * dsp->fRec47[1]))));
			dsp->fRec46[0] = ((dsp->fConst79 * (((dsp->fConst81 * dsp->fRec47[1]) + (dsp->fConst101 * dsp->fRec47[0])) + (dsp->fConst101 * dsp->fRec47[2]))) - (dsp->fConst76 * ((dsp->fConst102 * dsp->fRec46[2]) + (dsp->fConst103 * dsp->fRec46[1]))));
			dsp->fRec45[0] = ((dsp->fConst76 * (((dsp->fConst78 * dsp->fRec46[1]) + (dsp->fConst104 * dsp->fRec46[0])) + (dsp->fConst104 * dsp->fRec46[2]))) - (dsp->fConst72 * ((dsp->fConst105 * dsp->fRec45[2]) + (dsp->fConst106 * dsp->fRec45[1]))));
			dsp->fRec44[0] = ((fSlow1 * dsp->fRec44[1]) + (fSlow2 * fabsf((dsp->fConst72 * (((dsp->fConst75 * dsp->fRec45[1]) + (dsp->fConst107 * dsp->fRec45[0])) + (dsp->fConst107 * dsp->fRec45[2]))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec44[0]))));
			dsp->fRec57[0] = (fTemp74 - (dsp->fConst124 * ((dsp->fConst127 * dsp->fRec57[2]) + (dsp->fConst128 * dsp->fRec57[1]))));
			dsp->fRec56[0] = ((dsp->fConst124 * (((dsp->fConst126 * dsp->fRec57[1]) + (dsp->fConst129 * dsp->fRec57[0])) + (dsp->fConst129 * dsp->fRec57[2]))) - (dsp->fConst122 * ((dsp->fConst130 * dsp->fRec56[2]) + (dsp->fConst131 * dsp->fRec56[1]))));
			dsp->fRec55[0] = ((dsp->fConst122 * (((dsp->fConst123 * dsp->fRec56[1]) + (dsp->fConst132 * dsp->fRec56[0])) + (dsp->fConst132 * dsp->fRec56[2]))) - (dsp->fConst120 * ((dsp->fConst133 * dsp->fRec55[2]) + (dsp->fConst134 * dsp->fRec55[1]))));
			float fTemp75 = (dsp->fConst120 * (((dsp->fConst121 * dsp->fRec55[1]) + (dsp->fConst135 * dsp->fRec55[0])) + (dsp->fConst135 * dsp->fRec55[2])));
			dsp->fRec54[0] = (fTemp75 - (dsp->fConst117 * ((dsp->fConst136 * dsp->fRec54[2]) + (dsp->fConst138 * dsp->fRec54[1]))));
			dsp->fRec53[0] = ((dsp->fConst117 * (((dsp->fConst119 * dsp->fRec54[1]) + (dsp->fConst139 * dsp->fRec54[0])) + (dsp->fConst139 * dsp->fRec54[2]))) - (dsp->fConst114 * ((dsp->fConst140 * dsp->fRec53[2]) + (dsp->fConst141 * dsp->fRec53[1]))));
			dsp->fRec52[0] = ((dsp->fConst114 * (((dsp->fConst116 * dsp->fRec53[1]) + (dsp->fConst142 * dsp->fRec53[0])) + (dsp->fConst142 * dsp->fRec53[2]))) - (dsp->fConst110 * ((dsp->fConst143 * dsp->fRec52[2]) + (dsp->fConst144 * dsp->fRec52[1]))));
			dsp->fRec51[0] = ((fSlow1 * dsp->fRec51[1]) + (fSlow2 * fabsf((dsp->fConst110 * (((dsp->fConst113 * dsp->fRec52[1]) + (dsp->fConst145 * dsp->fRec52[0])) + (dsp->fConst145 * dsp->fRec52[2]))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec51[0]))));
			dsp->fRec64[0] = (fTemp75 - (dsp->fConst162 * ((dsp->fConst165 * dsp->fRec64[2]) + (dsp->fConst166 * dsp->fRec64[1]))));
			dsp->fRec63[0] = ((dsp->fConst162 * (((dsp->fConst164 * dsp->fRec64[1]) + (dsp->fConst167 * dsp->fRec64[0])) + (dsp->fConst167 * dsp->fRec64[2]))) - (dsp->fConst160 * ((dsp->fConst168 * dsp->fRec63[2]) + (dsp->fConst169 * dsp->fRec63[1]))));
			dsp->fRec62[0] = ((dsp->fConst160 * (((dsp->fConst161 * dsp->fRec63[1]) + (dsp->fConst170 * dsp->fRec63[0])) + (dsp->fConst170 * dsp->fRec63[2]))) - (dsp->fConst158 * ((dsp->fConst171 * dsp->fRec62[2]) + (dsp->fConst172 * dsp->fRec62[1]))));
			float fTemp76 = (dsp->fConst158 * (((dsp->fConst159 * dsp->fRec62[1]) + (dsp->fConst173 * dsp->fRec62[0])) + (dsp->fConst173 * dsp->fRec62[2])));
			dsp->fRec61[0] = (fTemp76 - (dsp->fConst155 * ((dsp->fConst174 * dsp->fRec61[2]) + (dsp->fConst176 * dsp->fRec61[1]))));
			dsp->fRec60[0] = ((dsp->fConst155 * (((dsp->fConst157 * dsp->fRec61[1]) + (dsp->fConst177 * dsp->fRec61[0])) + (dsp->fConst177 * dsp->fRec61[2]))) - (dsp->fConst152 * ((dsp->fConst178 * dsp->fRec60[2]) + (dsp->fConst179 * dsp->fRec60[1]))));
			dsp->fRec59[0] = ((dsp->fConst152 * (((dsp->fConst154 * dsp->fRec60[1]) + (dsp->fConst180 * dsp->fRec60[0])) + (dsp->fConst180 * dsp->fRec60[2]))) - (dsp->fConst148 * ((dsp->fConst181 * dsp->fRec59[2]) + (dsp->fConst182 * dsp->fRec59[1]))));
			dsp->fRec58[0] = ((fSlow1 * dsp->fRec58[1]) + (fSlow2 * fabsf((dsp->fConst148 * (((dsp->fConst151 * dsp->fRec59[1]) + (dsp->fConst183 * dsp->fRec59[0])) + (dsp->fConst183 * dsp->fRec59[2]))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec58[0]))));
			dsp->fRec71[0] = (fTemp76 - (dsp->fConst200 * ((dsp->fConst203 * dsp->fRec71[2]) + (dsp->fConst204 * dsp->fRec71[1]))));
			dsp->fRec70[0] = ((dsp->fConst200 * (((dsp->fConst202 * dsp->fRec71[1]) + (dsp->fConst205 * dsp->fRec71[0])) + (dsp->fConst205 * dsp->fRec71[2]))) - (dsp->fConst198 * ((dsp->fConst206 * dsp->fRec70[2]) + (dsp->fConst207 * dsp->fRec70[1]))));
			dsp->fRec69[0] = ((dsp->fConst198 * (((dsp->fConst199 * dsp->fRec70[1]) + (dsp->fConst208 * dsp->fRec70[0])) + (dsp->fConst208 * dsp->fRec70[2]))) - (dsp->fConst196 * ((dsp->fConst209 * dsp->fRec69[2]) + (dsp->fConst210 * dsp->fRec69[1]))));
			float fTemp77 = (dsp->fConst196 * (((dsp->fConst197 * dsp->fRec69[1]) + (dsp->fConst211 * dsp->fRec69[0])) + (dsp->fConst211 * dsp->fRec69[2])));
			dsp->fRec68[0] = (fTemp77 - (dsp->fConst193 * ((dsp->fConst212 * dsp->fRec68[2]) + (dsp->fConst214 * dsp->fRec68[1]))));
			dsp->fRec67[0] = ((dsp->fConst193 * (((dsp->fConst195 * dsp->fRec68[1]) + (dsp->fConst215 * dsp->fRec68[0])) + (dsp->fConst215 * dsp->fRec68[2]))) - (dsp->fConst190 * ((dsp->fConst216 * dsp->fRec67[2]) + (dsp->fConst217 * dsp->fRec67[1]))));
			dsp->fRec66[0] = ((dsp->fConst190 * (((dsp->fConst192 * dsp->fRec67[1]) + (dsp->fConst218 * dsp->fRec67[0])) + (dsp->fConst218 * dsp->fRec67[2]))) - (dsp->fConst186 * ((dsp->fConst219 * dsp->fRec66[2]) + (dsp->fConst220 * dsp->fRec66[1]))));
			dsp->fRec65[0] = ((fSlow1 * dsp->fRec65[1]) + (fSlow2 * fabsf((dsp->fConst186 * (((dsp->fConst189 * dsp->fRec66[1]) + (dsp->fConst221 * dsp->fRec66[0])) + (dsp->fConst221 * dsp->fRec66[2]))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec65[0]))));
			dsp->fRec78[0] = (fTemp77 - (dsp->fConst238 * ((dsp->fConst241 * dsp->fRec78[2]) + (dsp->fConst242 * dsp->fRec78[1]))));
			dsp->fRec77[0] = ((dsp->fConst238 * (((dsp->fConst240 * dsp->fRec78[1]) + (dsp->fConst243 * dsp->fRec78[0])) + (dsp->fConst243 * dsp->fRec78[2]))) - (dsp->fConst236 * ((dsp->fConst244 * dsp->fRec77[2]) + (dsp->fConst245 * dsp->fRec77[1]))));
			dsp->fRec76[0] = ((dsp->fConst236 * (((dsp->fConst237 * dsp->fRec77[1]) + (dsp->fConst246 * dsp->fRec77[0])) + (dsp->fConst246 * dsp->fRec77[2]))) - (dsp->fConst234 * ((dsp->fConst247 * dsp->fRec76[2]) + (dsp->fConst248 * dsp->fRec76[1]))));
			float fTemp78 = (dsp->fConst234 * (((dsp->fConst235 * dsp->fRec76[1]) + (dsp->fConst249 * dsp->fRec76[0])) + (dsp->fConst249 * dsp->fRec76[2])));
			dsp->fRec75[0] = (fTemp78 - (dsp->fConst231 * ((dsp->fConst250 * dsp->fRec75[2]) + (dsp->fConst252 * dsp->fRec75[1]))));
			dsp->fRec74[0] = ((dsp->fConst231 * (((dsp->fConst233 * dsp->fRec75[1]) + (dsp->fConst253 * dsp->fRec75[0])) + (dsp->fConst253 * dsp->fRec75[2]))) - (dsp->fConst228 * ((dsp->fConst254 * dsp->fRec74[2]) + (dsp->fConst255 * dsp->fRec74[1]))));
			dsp->fRec73[0] = ((dsp->fConst228 * (((dsp->fConst230 * dsp->fRec74[1]) + (dsp->fConst256 * dsp->fRec74[0])) + (dsp->fConst256 * dsp->fRec74[2]))) - (dsp->fConst224 * ((dsp->fConst257 * dsp->fRec73[2]) + (dsp->fConst258 * dsp->fRec73[1]))));
			dsp->fRec72[0] = ((fSlow1 * dsp->fRec72[1]) + (fSlow2 * fabsf((dsp->fConst224 * (((dsp->fConst227 * dsp->fRec73[1]) + (dsp->fConst259 * dsp->fRec73[0])) + (dsp->fConst259 * dsp->fRec73[2]))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec72[0]))));
			dsp->fRec85[0] = (fTemp78 - (dsp->fConst276 * ((dsp->fConst279 * dsp->fRec85[2]) + (dsp->fConst280 * dsp->fRec85[1]))));
			dsp->fRec84[0] = ((dsp->fConst276 * (((dsp->fConst278 * dsp->fRec85[1]) + (dsp->fConst281 * dsp->fRec85[0])) + (dsp->fConst281 * dsp->fRec85[2]))) - (dsp->fConst274 * ((dsp->fConst282 * dsp->fRec84[2]) + (dsp->fConst283 * dsp->fRec84[1]))));
			dsp->fRec83[0] = ((dsp->fConst274 * (((dsp->fConst275 * dsp->fRec84[1]) + (dsp->fConst284 * dsp->fRec84[0])) + (dsp->fConst284 * dsp->fRec84[2]))) - (dsp->fConst272 * ((dsp->fConst285 * dsp->fRec83[2]) + (dsp->fConst286 * dsp->fRec83[1]))));
			float fTemp79 = (dsp->fConst272 * (((dsp->fConst273 * dsp->fRec83[1]) + (dsp->fConst287 * dsp->fRec83[0])) + (dsp->fConst287 * dsp->fRec83[2])));
			dsp->fRec82[0] = (fTemp79 - (dsp->fConst269 * ((dsp->fConst288 * dsp->fRec82[2]) + (dsp->fConst290 * dsp->fRec82[1]))));
			dsp->fRec81[0] = ((dsp->fConst269 * (((dsp->fConst271 * dsp->fRec82[1]) + (dsp->fConst291 * dsp->fRec82[0])) + (dsp->fConst291 * dsp->fRec82[2]))) - (dsp->fConst266 * ((dsp->fConst292 * dsp->fRec81[2]) + (dsp->fConst293 * dsp->fRec81[1]))));
			dsp->fRec80[0] = ((dsp->fConst266 * (((dsp->fConst268 * dsp->fRec81[1]) + (dsp->fConst294 * dsp->fRec81[0])) + (dsp->fConst294 * dsp->fRec81[2]))) - (dsp->fConst262 * ((dsp->fConst295 * dsp->fRec80[2]) + (dsp->fConst296 * dsp->fRec80[1]))));
			dsp->fRec79[0] = ((fSlow1 * dsp->fRec79[1]) + (fSlow2 * fabsf((dsp->fConst262 * (((dsp->fConst265 * dsp->fRec80[1]) + (dsp->fConst297 * dsp->fRec80[0])) + (dsp->fConst297 * dsp->fRec80[2]))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec79[0]))));
			dsp->fRec92[0] = (fTemp79 - (dsp->fConst314 * ((dsp->fConst317 * dsp->fRec92[2]) + (dsp->fConst318 * dsp->fRec92[1]))));
			dsp->fRec91[0] = ((dsp->fConst314 * (((dsp->fConst316 * dsp->fRec92[1]) + (dsp->fConst319 * dsp->fRec92[0])) + (dsp->fConst319 * dsp->fRec92[2]))) - (dsp->fConst312 * ((dsp->fConst320 * dsp->fRec91[2]) + (dsp->fConst321 * dsp->fRec91[1]))));
			dsp->fRec90[0] = ((dsp->fConst312 * (((dsp->fConst313 * dsp->fRec91[1]) + (dsp->fConst322 * dsp->fRec91[0])) + (dsp->fConst322 * dsp->fRec91[2]))) - (dsp->fConst310 * ((dsp->fConst323 * dsp->fRec90[2]) + (dsp->fConst324 * dsp->fRec90[1]))));
			float fTemp80 = (dsp->fConst310 * (((dsp->fConst311 * dsp->fRec90[1]) + (dsp->fConst325 * dsp->fRec90[0])) + (dsp->fConst325 * dsp->fRec90[2])));
			dsp->fRec89[0] = (fTemp80 - (dsp->fConst307 * ((dsp->fConst326 * dsp->fRec89[2]) + (dsp->fConst328 * dsp->fRec89[1]))));
			dsp->fRec88[0] = ((dsp->fConst307 * (((dsp->fConst309 * dsp->fRec89[1]) + (dsp->fConst329 * dsp->fRec89[0])) + (dsp->fConst329 * dsp->fRec89[2]))) - (dsp->fConst304 * ((dsp->fConst330 * dsp->fRec88[2]) + (dsp->fConst331 * dsp->fRec88[1]))));
			dsp->fRec87[0] = ((dsp->fConst304 * (((dsp->fConst306 * dsp->fRec88[1]) + (dsp->fConst332 * dsp->fRec88[0])) + (dsp->fConst332 * dsp->fRec88[2]))) - (dsp->fConst300 * ((dsp->fConst333 * dsp->fRec87[2]) + (dsp->fConst334 * dsp->fRec87[1]))));
			dsp->fRec86[0] = ((fSlow1 * dsp->fRec86[1]) + (fSlow2 * fabsf((dsp->fConst300 * (((dsp->fConst303 * dsp->fRec87[1]) + (dsp->fConst335 * dsp->fRec87[0])) + (dsp->fConst335 * dsp->fRec87[2]))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec86[0]))));
			dsp->fRec99[0] = (fTemp80 - (dsp->fConst352 * ((dsp->fConst355 * dsp->fRec99[2]) + (dsp->fConst356 * dsp->fRec99[1]))));
			dsp->fRec98[0] = ((dsp->fConst352 * (((dsp->fConst354 * dsp->fRec99[1]) + (dsp->fConst357 * dsp->fRec99[0])) + (dsp->fConst357 * dsp->fRec99[2]))) - (dsp->fConst350 * ((dsp->fConst358 * dsp->fRec98[2]) + (dsp->fConst359 * dsp->fRec98[1]))));
			dsp->fRec97[0] = ((dsp->fConst350 * (((dsp->fConst351 * dsp->fRec98[1]) + (dsp->fConst360 * dsp->fRec98[0])) + (dsp->fConst360 * dsp->fRec98[2]))) - (dsp->fConst348 * ((dsp->fConst361 * dsp->fRec97[2]) + (dsp->fConst362 * dsp->fRec97[1]))));
			float fTemp81 = (dsp->fConst348 * (((dsp->fConst349 * dsp->fRec97[1]) + (dsp->fConst363 * dsp->fRec97[0])) + (dsp->fConst363 * dsp->fRec97[2])));
			dsp->fRec96[0] = (fTemp81 - (dsp->fConst345 * ((dsp->fConst364 * dsp->fRec96[2]) + (dsp->fConst366 * dsp->fRec96[1]))));
			dsp->fRec95[0] = ((dsp->fConst345 * (((dsp->fConst347 * dsp->fRec96[1]) + (dsp->fConst367 * dsp->fRec96[0])) + (dsp->fConst367 * dsp->fRec96[2]))) - (dsp->fConst342 * ((dsp->fConst368 * dsp->fRec95[2]) + (dsp->fConst369 * dsp->fRec95[1]))));
			dsp->fRec94[0] = ((dsp->fConst342 * (((dsp->fConst344 * dsp->fRec95[1]) + (dsp->fConst370 * dsp->fRec95[0])) + (dsp->fConst370 * dsp->fRec95[2]))) - (dsp->fConst338 * ((dsp->fConst371 * dsp->fRec94[2]) + (dsp->fConst372 * dsp->fRec94[1]))));
			dsp->fRec93[0] = ((fSlow1 * dsp->fRec93[1]) + (fSlow2 * fabsf((dsp->fConst338 * (((dsp->fConst341 * dsp->fRec94[1]) + (dsp->fConst373 * dsp->fRec94[0])) + (dsp->fConst373 * dsp->fRec94[2]))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec93[0]))));
			dsp->fRec106[0] = (fTemp81 - (dsp->fConst390 * ((dsp->fConst393 * dsp->fRec106[2]) + (dsp->fConst394 * dsp->fRec106[1]))));
			dsp->fRec105[0] = ((dsp->fConst390 * (((dsp->fConst392 * dsp->fRec106[1]) + (dsp->fConst395 * dsp->fRec106[0])) + (dsp->fConst395 * dsp->fRec106[2]))) - (dsp->fConst388 * ((dsp->fConst396 * dsp->fRec105[2]) + (dsp->fConst397 * dsp->fRec105[1]))));
			dsp->fRec104[0] = ((dsp->fConst388 * (((dsp->fConst389 * dsp->fRec105[1]) + (dsp->fConst398 * dsp->fRec105[0])) + (dsp->fConst398 * dsp->fRec105[2]))) - (dsp->fConst386 * ((dsp->fConst399 * dsp->fRec104[2]) + (dsp->fConst400 * dsp->fRec104[1]))));
			float fTemp82 = (dsp->fConst386 * (((dsp->fConst387 * dsp->fRec104[1]) + (dsp->fConst401 * dsp->fRec104[0])) + (dsp->fConst401 * dsp->fRec104[2])));
			dsp->fRec103[0] = (fTemp82 - (dsp->fConst383 * ((dsp->fConst402 * dsp->fRec103[2]) + (dsp->fConst404 * dsp->fRec103[1]))));
			dsp->fRec102[0] = ((dsp->fConst383 * (((dsp->fConst385 * dsp->fRec103[1]) + (dsp->fConst405 * dsp->fRec103[0])) + (dsp->fConst405 * dsp->fRec103[2]))) - (dsp->fConst380 * ((dsp->fConst406 * dsp->fRec102[2]) + (dsp->fConst407 * dsp->fRec102[1]))));
			dsp->fRec101[0] = ((dsp->fConst380 * (((dsp->fConst382 * dsp->fRec102[1]) + (dsp->fConst408 * dsp->fRec102[0])) + (dsp->fConst408 * dsp->fRec102[2]))) - (dsp->fConst376 * ((dsp->fConst409 * dsp->fRec101[2]) + (dsp->fConst410 * dsp->fRec101[1]))));
			dsp->fRec100[0] = ((fSlow1 * dsp->fRec100[1]) + (fSlow2 * fabsf((dsp->fConst376 * (((dsp->fConst379 * dsp->fRec101[1]) + (dsp->fConst411 * dsp->fRec101[0])) + (dsp->fConst411 * dsp->fRec101[2]))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec100[0]))));
			dsp->fRec113[0] = (fTemp82 - (dsp->fConst428 * ((dsp->fConst431 * dsp->fRec113[2]) + (dsp->fConst432 * dsp->fRec113[1]))));
			dsp->fRec112[0] = ((dsp->fConst428 * (((dsp->fConst430 * dsp->fRec113[1]) + (dsp->fConst433 * dsp->fRec113[0])) + (dsp->fConst433 * dsp->fRec113[2]))) - (dsp->fConst426 * ((dsp->fConst434 * dsp->fRec112[2]) + (dsp->fConst435 * dsp->fRec112[1]))));
			dsp->fRec111[0] = ((dsp->fConst426 * (((dsp->fConst427 * dsp->fRec112[1]) + (dsp->fConst436 * dsp->fRec112[0])) + (dsp->fConst436 * dsp->fRec112[2]))) - (dsp->fConst424 * ((dsp->fConst437 * dsp->fRec111[2]) + (dsp->fConst438 * dsp->fRec111[1]))));
			float fTemp83 = (dsp->fConst424 * (((dsp->fConst425 * dsp->fRec111[1]) + (dsp->fConst439 * dsp->fRec111[0])) + (dsp->fConst439 * dsp->fRec111[2])));
			dsp->fRec110[0] = (fTemp83 - (dsp->fConst421 * ((dsp->fConst440 * dsp->fRec110[2]) + (dsp->fConst442 * dsp->fRec110[1]))));
			dsp->fRec109[0] = ((dsp->fConst421 * (((dsp->fConst423 * dsp->fRec110[1]) + (dsp->fConst443 * dsp->fRec110[0])) + (dsp->fConst443 * dsp->fRec110[2]))) - (dsp->fConst418 * ((dsp->fConst444 * dsp->fRec109[2]) + (dsp->fConst445 * dsp->fRec109[1]))));
			dsp->fRec108[0] = ((dsp->fConst418 * (((dsp->fConst420 * dsp->fRec109[1]) + (dsp->fConst446 * dsp->fRec109[0])) + (dsp->fConst446 * dsp->fRec109[2]))) - (dsp->fConst414 * ((dsp->fConst447 * dsp->fRec108[2]) + (dsp->fConst448 * dsp->fRec108[1]))));
			dsp->fRec107[0] = ((fSlow1 * dsp->fRec107[1]) + (fSlow2 * fabsf((dsp->fConst414 * (((dsp->fConst417 * dsp->fRec108[1]) + (dsp->fConst449 * dsp->fRec108[0])) + (dsp->fConst449 * dsp->fRec108[2]))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec107[0]))));
			dsp->fRec120[0] = (fTemp83 - (dsp->fConst466 * ((dsp->fConst469 * dsp->fRec120[2]) + (dsp->fConst470 * dsp->fRec120[1]))));
			dsp->fRec119[0] = ((dsp->fConst466 * (((dsp->fConst468 * dsp->fRec120[1]) + (dsp->fConst471 * dsp->fRec120[0])) + (dsp->fConst471 * dsp->fRec120[2]))) - (dsp->fConst464 * ((dsp->fConst472 * dsp->fRec119[2]) + (dsp->fConst473 * dsp->fRec119[1]))));
			dsp->fRec118[0] = ((dsp->fConst464 * (((dsp->fConst465 * dsp->fRec119[1]) + (dsp->fConst474 * dsp->fRec119[0])) + (dsp->fConst474 * dsp->fRec119[2]))) - (dsp->fConst462 * ((dsp->fConst475 * dsp->fRec118[2]) + (dsp->fConst476 * dsp->fRec118[1]))));
			float fTemp84 = (dsp->fConst462 * (((dsp->fConst463 * dsp->fRec118[1]) + (dsp->fConst477 * dsp->fRec118[0])) + (dsp->fConst477 * dsp->fRec118[2])));
			dsp->fRec117[0] = (fTemp84 - (dsp->fConst459 * ((dsp->fConst478 * dsp->fRec117[2]) + (dsp->fConst480 * dsp->fRec117[1]))));
			dsp->fRec116[0] = ((dsp->fConst459 * (((dsp->fConst461 * dsp->fRec117[1]) + (dsp->fConst481 * dsp->fRec117[0])) + (dsp->fConst481 * dsp->fRec117[2]))) - (dsp->fConst456 * ((dsp->fConst482 * dsp->fRec116[2]) + (dsp->fConst483 * dsp->fRec116[1]))));
			dsp->fRec115[0] = ((dsp->fConst456 * (((dsp->fConst458 * dsp->fRec116[1]) + (dsp->fConst484 * dsp->fRec116[0])) + (dsp->fConst484 * dsp->fRec116[2]))) - (dsp->fConst452 * ((dsp->fConst485 * dsp->fRec115[2]) + (dsp->fConst486 * dsp->fRec115[1]))));
			dsp->fRec114[0] = ((fSlow1 * dsp->fRec114[1]) + (fSlow2 * fabsf((dsp->fConst452 * (((dsp->fConst455 * dsp->fRec115[1]) + (dsp->fConst487 * dsp->fRec115[0])) + (dsp->fConst487 * dsp->fRec115[2]))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec114[0]))));
			dsp->fRec127[0] = (fTemp84 - (dsp->fConst504 * ((dsp->fConst507 * dsp->fRec127[2]) + (dsp->fConst508 * dsp->fRec127[1]))));
			dsp->fRec126[0] = ((dsp->fConst504 * (((dsp->fConst506 * dsp->fRec127[1]) + (dsp->fConst509 * dsp->fRec127[0])) + (dsp->fConst509 * dsp->fRec127[2]))) - (dsp->fConst502 * ((dsp->fConst510 * dsp->fRec126[2]) + (dsp->fConst511 * dsp->fRec126[1]))));
			dsp->fRec125[0] = ((dsp->fConst502 * (((dsp->fConst503 * dsp->fRec126[1]) + (dsp->fConst512 * dsp->fRec126[0])) + (dsp->fConst512 * dsp->fRec126[2]))) - (dsp->fConst500 * ((dsp->fConst513 * dsp->fRec125[2]) + (dsp->fConst514 * dsp->fRec125[1]))));
			float fTemp85 = (dsp->fConst500 * (((dsp->fConst501 * dsp->fRec125[1]) + (dsp->fConst515 * dsp->fRec125[0])) + (dsp->fConst515 * dsp->fRec125[2])));
			dsp->fRec124[0] = (fTemp85 - (dsp->fConst497 * ((dsp->fConst516 * dsp->fRec124[2]) + (dsp->fConst518 * dsp->fRec124[1]))));
			dsp->fRec123[0] = ((dsp->fConst497 * (((dsp->fConst499 * dsp->fRec124[1]) + (dsp->fConst519 * dsp->fRec124[0])) + (dsp->fConst519 * dsp->fRec124[2]))) - (dsp->fConst494 * ((dsp->fConst520 * dsp->fRec123[2]) + (dsp->fConst521 * dsp->fRec123[1]))));
			dsp->fRec122[0] = ((dsp->fConst494 * (((dsp->fConst496 * dsp->fRec123[1]) + (dsp->fConst522 * dsp->fRec123[0])) + (dsp->fConst522 * dsp->fRec123[2]))) - (dsp->fConst490 * ((dsp->fConst523 * dsp->fRec122[2]) + (dsp->fConst524 * dsp->fRec122[1]))));
			dsp->fRec121[0] = ((fSlow1 * dsp->fRec121[1]) + (fSlow2 * fabsf((dsp->fConst490 * (((dsp->fConst493 * dsp->fRec122[1]) + (dsp->fConst525 * dsp->fRec122[0])) + (dsp->fConst525 * dsp->fRec122[2]))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec121[0]))));
			dsp->fRec131[0] = (fTemp85 - (dsp->fConst530 * ((dsp->fConst533 * dsp->fRec131[2]) + (dsp->fConst534 * dsp->fRec131[1]))));
			dsp->fRec130[0] = ((dsp->fConst530 * (((dsp->fConst532 * dsp->fRec131[1]) + (dsp->fConst535 * dsp->fRec131[0])) + (dsp->fConst535 * dsp->fRec131[2]))) - (dsp->fConst528 * ((dsp->fConst536 * dsp->fRec130[2]) + (dsp->fConst537 * dsp->fRec130[1]))));
			dsp->fRec129[0] = ((dsp->fConst528 * (((dsp->fConst529 * dsp->fRec130[1]) + (dsp->fConst538 * dsp->fRec130[0])) + (dsp->fConst538 * dsp->fRec130[2]))) - (dsp->fConst526 * ((dsp->fConst539 * dsp->fRec129[2]) + (dsp->fConst540 * dsp->fRec129[1]))));
			dsp->fRec128[0] = ((fSlow1 * dsp->fRec128[1]) + (fSlow2 * fabsf((dsp->fConst526 * (((dsp->fConst527 * dsp->fRec129[1]) + (dsp->fConst541 * dsp->fRec129[0])) + (dsp->fConst541 * dsp->fRec129[2]))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec128[0]))));
			output0[i] = (FAUSTFLOAT)fTemp72;
			output1[i] = (FAUSTFLOAT)fTemp72;
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->iRec23[1] = dsp->iRec23[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec24[j1] = dsp->fRec24[(j1 - 1)];
					
				}
				
			}
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec50[2] = dsp->fRec50[1];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec49[2] = dsp->fRec49[1];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec48[2] = dsp->fRec48[1];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec57[2] = dsp->fRec57[1];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec53[2] = dsp->fRec53[1];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec64[2] = dsp->fRec64[1];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec61[2] = dsp->fRec61[1];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec60[2] = dsp->fRec60[1];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec71[2] = dsp->fRec71[1];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec70[2] = dsp->fRec70[1];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec68[2] = dsp->fRec68[1];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec67[2] = dsp->fRec67[1];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec66[2] = dsp->fRec66[1];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec78[2] = dsp->fRec78[1];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[2] = dsp->fRec75[1];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[2] = dsp->fRec74[1];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[2] = dsp->fRec84[1];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec83[2] = dsp->fRec83[1];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[2] = dsp->fRec82[1];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec81[2] = dsp->fRec81[1];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec80[2] = dsp->fRec80[1];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec92[2] = dsp->fRec92[1];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec91[2] = dsp->fRec91[1];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[2] = dsp->fRec90[1];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec88[2] = dsp->fRec88[1];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec87[2] = dsp->fRec87[1];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec99[2] = dsp->fRec99[1];
			dsp->fRec99[1] = dsp->fRec99[0];
			dsp->fRec98[2] = dsp->fRec98[1];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[2] = dsp->fRec97[1];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec95[2] = dsp->fRec95[1];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec94[2] = dsp->fRec94[1];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec106[2] = dsp->fRec106[1];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->fRec105[2] = dsp->fRec105[1];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec104[2] = dsp->fRec104[1];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec103[2] = dsp->fRec103[1];
			dsp->fRec103[1] = dsp->fRec103[0];
			dsp->fRec102[2] = dsp->fRec102[1];
			dsp->fRec102[1] = dsp->fRec102[0];
			dsp->fRec101[2] = dsp->fRec101[1];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec113[2] = dsp->fRec113[1];
			dsp->fRec113[1] = dsp->fRec113[0];
			dsp->fRec112[2] = dsp->fRec112[1];
			dsp->fRec112[1] = dsp->fRec112[0];
			dsp->fRec111[2] = dsp->fRec111[1];
			dsp->fRec111[1] = dsp->fRec111[0];
			dsp->fRec110[2] = dsp->fRec110[1];
			dsp->fRec110[1] = dsp->fRec110[0];
			dsp->fRec109[2] = dsp->fRec109[1];
			dsp->fRec109[1] = dsp->fRec109[0];
			dsp->fRec108[2] = dsp->fRec108[1];
			dsp->fRec108[1] = dsp->fRec108[0];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->fRec120[2] = dsp->fRec120[1];
			dsp->fRec120[1] = dsp->fRec120[0];
			dsp->fRec119[2] = dsp->fRec119[1];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec118[2] = dsp->fRec118[1];
			dsp->fRec118[1] = dsp->fRec118[0];
			dsp->fRec117[2] = dsp->fRec117[1];
			dsp->fRec117[1] = dsp->fRec117[0];
			dsp->fRec116[2] = dsp->fRec116[1];
			dsp->fRec116[1] = dsp->fRec116[0];
			dsp->fRec115[2] = dsp->fRec115[1];
			dsp->fRec115[1] = dsp->fRec115[0];
			dsp->fRec114[1] = dsp->fRec114[0];
			dsp->fRec127[2] = dsp->fRec127[1];
			dsp->fRec127[1] = dsp->fRec127[0];
			dsp->fRec126[2] = dsp->fRec126[1];
			dsp->fRec126[1] = dsp->fRec126[0];
			dsp->fRec125[2] = dsp->fRec125[1];
			dsp->fRec125[1] = dsp->fRec125[0];
			dsp->fRec124[2] = dsp->fRec124[1];
			dsp->fRec124[1] = dsp->fRec124[0];
			dsp->fRec123[2] = dsp->fRec123[1];
			dsp->fRec123[1] = dsp->fRec123[0];
			dsp->fRec122[2] = dsp->fRec122[1];
			dsp->fRec122[1] = dsp->fRec122[0];
			dsp->fRec121[1] = dsp->fRec121[0];
			dsp->fRec131[2] = dsp->fRec131[1];
			dsp->fRec131[1] = dsp->fRec131[0];
			dsp->fRec130[2] = dsp->fRec130[1];
			dsp->fRec130[1] = dsp->fRec130[0];
			dsp->fRec129[2] = dsp->fRec129[1];
			dsp->fRec129[1] = dsp->fRec129[0];
			dsp->fRec128[1] = dsp->fRec128[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
