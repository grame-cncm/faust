/* ------------------------------------------------------------
name: "virtualAnalogLab"
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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider3;
	float fRec10[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry0;
	float fConst14;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fVslider2;
	float fRec12[2];
	float fVec1[2];
	float fRec11[2];
	float fConst15;
	float fVec2[2];
	float fConst16;
	float fVec3[2];
	float fVec4[2];
	float fConst17;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec13[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec14[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	float fConst18;
	FAUSTFLOAT fVslider5;
	float fVec22[2];
	float fRec15[2];
	float fVec23[2];
	int IOTA;
	float fVec24[4096];
	float fConst19;
	float fVec25[2];
	float fRec16[2];
	float fVec26[2];
	float fVec27[4096];
	float fVec28[2];
	float fRec17[2];
	float fVec29[2];
	float fVec30[4096];
	float fConst20;
	FAUSTFLOAT fVslider6;
	float fRec18[2];
	float fRec19[2];
	float fRec20[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fVslider8;
	float fRec21[2];
	float fConst21;
	float fVec31[2];
	float fVec32[2];
	float fVec33[4096];
	float fVec34[2];
	float fVec35[2];
	float fVec36[4096];
	float fVec37[2];
	float fVec38[2];
	float fVec39[4096];
	FAUSTFLOAT fVslider9;
	int iRec23[2];
	float fRec22[4];
	float fConst22;
	FAUSTFLOAT fHslider5;
	float fRec24[2];
	FAUSTFLOAT fHslider6;
	float fRec9[2];
	float fRec8[2];
	float fRec7[2];
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fCheckbox3;
	float fConst23;
	float fRec27[2];
	float fRec26[3];
	float fRec25[3];
	float fRec30[2];
	float fRec28[2];
	float fRec33[2];
	float fRec31[2];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec3[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec2[3];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec1[3];
	float fConst33;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fConst53;
	float fConst54;
	float fRec40[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec39[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec38[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec37[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec36[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec35[3];
	float fConst71;
	float fRec34[2];
	FAUSTFLOAT fVbargraph1;
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
	float fConst91;
	float fConst92;
	float fRec47[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec46[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec45[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec44[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec43[3];
	float fConst106;
	float fConst107;
	float fConst108;
	float fRec42[3];
	float fConst109;
	float fRec41[2];
	FAUSTFLOAT fVbargraph2;
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
	float fConst129;
	float fConst130;
	float fRec54[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec53[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec52[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec51[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec50[3];
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec49[3];
	float fConst147;
	float fRec48[2];
	FAUSTFLOAT fVbargraph3;
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
	float fConst167;
	float fConst168;
	float fRec61[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec60[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec59[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fRec58[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec57[3];
	float fConst182;
	float fConst183;
	float fConst184;
	float fRec56[3];
	float fConst185;
	float fRec55[2];
	FAUSTFLOAT fVbargraph4;
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
	float fConst205;
	float fConst206;
	float fRec68[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec67[3];
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec66[3];
	float fConst213;
	float fConst214;
	float fConst215;
	float fConst216;
	float fRec65[3];
	float fConst217;
	float fConst218;
	float fConst219;
	float fRec64[3];
	float fConst220;
	float fConst221;
	float fConst222;
	float fRec63[3];
	float fConst223;
	float fRec62[2];
	FAUSTFLOAT fVbargraph5;
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
	float fConst243;
	float fConst244;
	float fRec75[3];
	float fConst245;
	float fConst246;
	float fConst247;
	float fRec74[3];
	float fConst248;
	float fConst249;
	float fConst250;
	float fRec73[3];
	float fConst251;
	float fConst252;
	float fConst253;
	float fConst254;
	float fRec72[3];
	float fConst255;
	float fConst256;
	float fConst257;
	float fRec71[3];
	float fConst258;
	float fConst259;
	float fConst260;
	float fRec70[3];
	float fConst261;
	float fRec69[2];
	FAUSTFLOAT fVbargraph6;
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
	float fConst281;
	float fConst282;
	float fRec82[3];
	float fConst283;
	float fConst284;
	float fConst285;
	float fRec81[3];
	float fConst286;
	float fConst287;
	float fConst288;
	float fRec80[3];
	float fConst289;
	float fConst290;
	float fConst291;
	float fConst292;
	float fRec79[3];
	float fConst293;
	float fConst294;
	float fConst295;
	float fRec78[3];
	float fConst296;
	float fConst297;
	float fConst298;
	float fRec77[3];
	float fConst299;
	float fRec76[2];
	FAUSTFLOAT fVbargraph7;
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
	float fConst319;
	float fConst320;
	float fRec89[3];
	float fConst321;
	float fConst322;
	float fConst323;
	float fRec88[3];
	float fConst324;
	float fConst325;
	float fConst326;
	float fRec87[3];
	float fConst327;
	float fConst328;
	float fConst329;
	float fConst330;
	float fRec86[3];
	float fConst331;
	float fConst332;
	float fConst333;
	float fRec85[3];
	float fConst334;
	float fConst335;
	float fConst336;
	float fRec84[3];
	float fConst337;
	float fRec83[2];
	FAUSTFLOAT fVbargraph8;
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
	float fConst357;
	float fConst358;
	float fRec96[3];
	float fConst359;
	float fConst360;
	float fConst361;
	float fRec95[3];
	float fConst362;
	float fConst363;
	float fConst364;
	float fRec94[3];
	float fConst365;
	float fConst366;
	float fConst367;
	float fConst368;
	float fRec93[3];
	float fConst369;
	float fConst370;
	float fConst371;
	float fRec92[3];
	float fConst372;
	float fConst373;
	float fConst374;
	float fRec91[3];
	float fConst375;
	float fRec90[2];
	FAUSTFLOAT fVbargraph9;
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
	float fConst395;
	float fConst396;
	float fRec103[3];
	float fConst397;
	float fConst398;
	float fConst399;
	float fRec102[3];
	float fConst400;
	float fConst401;
	float fConst402;
	float fRec101[3];
	float fConst403;
	float fConst404;
	float fConst405;
	float fConst406;
	float fRec100[3];
	float fConst407;
	float fConst408;
	float fConst409;
	float fRec99[3];
	float fConst410;
	float fConst411;
	float fConst412;
	float fRec98[3];
	float fConst413;
	float fRec97[2];
	FAUSTFLOAT fVbargraph10;
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
	float fConst433;
	float fConst434;
	float fRec110[3];
	float fConst435;
	float fConst436;
	float fConst437;
	float fRec109[3];
	float fConst438;
	float fConst439;
	float fConst440;
	float fRec108[3];
	float fConst441;
	float fConst442;
	float fConst443;
	float fConst444;
	float fRec107[3];
	float fConst445;
	float fConst446;
	float fConst447;
	float fRec106[3];
	float fConst448;
	float fConst449;
	float fConst450;
	float fRec105[3];
	float fConst451;
	float fRec104[2];
	FAUSTFLOAT fVbargraph11;
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
	float fConst471;
	float fConst472;
	float fRec117[3];
	float fConst473;
	float fConst474;
	float fConst475;
	float fRec116[3];
	float fConst476;
	float fConst477;
	float fConst478;
	float fRec115[3];
	float fConst479;
	float fConst480;
	float fConst481;
	float fConst482;
	float fRec114[3];
	float fConst483;
	float fConst484;
	float fConst485;
	float fRec113[3];
	float fConst486;
	float fConst487;
	float fConst488;
	float fRec112[3];
	float fConst489;
	float fRec111[2];
	FAUSTFLOAT fVbargraph12;
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
	float fConst509;
	float fConst510;
	float fRec124[3];
	float fConst511;
	float fConst512;
	float fConst513;
	float fRec123[3];
	float fConst514;
	float fConst515;
	float fConst516;
	float fRec122[3];
	float fConst517;
	float fConst518;
	float fConst519;
	float fConst520;
	float fRec121[3];
	float fConst521;
	float fConst522;
	float fConst523;
	float fRec120[3];
	float fConst524;
	float fConst525;
	float fConst526;
	float fRec119[3];
	float fConst527;
	float fRec118[2];
	FAUSTFLOAT fVbargraph13;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fConst535;
	float fConst536;
	float fRec128[3];
	float fConst537;
	float fConst538;
	float fConst539;
	float fRec127[3];
	float fConst540;
	float fConst541;
	float fConst542;
	float fRec126[3];
	float fConst543;
	float fRec125[2];
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
	m->declare(m->metaInterface, "name", "virtualAnalogLab");
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
	dsp->fVslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider3 = (FAUSTFLOAT)-20.0f;
	dsp->fVslider1 = (FAUSTFLOAT)1.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fHslider4 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider5 = (FAUSTFLOAT)0.0f;
	dsp->fVslider6 = (FAUSTFLOAT)0.0f;
	dsp->fVslider7 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fVslider8 = (FAUSTFLOAT)0.5f;
	dsp->fVslider9 = (FAUSTFLOAT)0.0f;
	dsp->fHslider5 = (FAUSTFLOAT)25.0f;
	dsp->fHslider6 = (FAUSTFLOAT)0.90000000000000002f;
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
			dsp->fRec4[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec10[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec12[l3] = 0.0f;
			
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
			dsp->fRec11[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fVec2[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec3[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec4[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec5[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec6[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec7[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fVec8[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec13[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fVec9[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec10[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec11[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec12[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec13[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec14[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fVec15[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec14[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec16[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fVec17[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec18[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec19[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec20[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fVec21[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fVec22[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec15[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fVec23[l30] = 0.0f;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			dsp->fVec24[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fVec25[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			dsp->fRec16[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fVec26[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 4096); l35 = (l35 + 1)) {
			dsp->fVec27[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			dsp->fVec28[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec17[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fVec29[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			dsp->fVec30[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec18[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec19[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec20[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec21[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fVec31[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fVec32[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 4096); l46 = (l46 + 1)) {
			dsp->fVec33[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fVec34[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			dsp->fVec35[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 4096); l49 = (l49 + 1)) {
			dsp->fVec36[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fVec37[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			dsp->fVec38[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 4096); l52 = (l52 + 1)) {
			dsp->fVec39[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->iRec23[l53] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			dsp->fRec22[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->fRec24[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			dsp->fRec9[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec8[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			dsp->fRec7[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec6[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			dsp->fRec5[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec27[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec26[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec25[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			dsp->fRec30[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			dsp->fRec28[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec33[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			dsp->fRec31[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec3[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec2[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			dsp->fRec1[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			dsp->fRec0[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec40[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			dsp->fRec39[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			dsp->fRec38[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec37[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec36[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			dsp->fRec35[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			dsp->fRec34[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec47[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			dsp->fRec46[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec45[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec44[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec43[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			dsp->fRec42[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			dsp->fRec41[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec54[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			dsp->fRec53[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec52[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec51[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec50[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			dsp->fRec49[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			dsp->fRec48[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec61[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			dsp->fRec60[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec59[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec58[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			dsp->fRec57[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			dsp->fRec56[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			dsp->fRec55[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			dsp->fRec68[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			dsp->fRec67[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			dsp->fRec66[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec65[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			dsp->fRec64[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			dsp->fRec63[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			dsp->fRec62[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			dsp->fRec75[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			dsp->fRec74[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			dsp->fRec73[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			dsp->fRec72[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			dsp->fRec71[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			dsp->fRec70[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			dsp->fRec69[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			dsp->fRec82[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			dsp->fRec81[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			dsp->fRec80[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			dsp->fRec79[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			dsp->fRec78[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			dsp->fRec77[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			dsp->fRec76[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			dsp->fRec89[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			dsp->fRec88[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec87[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			dsp->fRec86[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			dsp->fRec85[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			dsp->fRec84[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			dsp->fRec83[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec96[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			dsp->fRec95[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			dsp->fRec94[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			dsp->fRec93[l131] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l132;
		for (l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			dsp->fRec92[l132] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l133;
		for (l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			dsp->fRec91[l133] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l134;
		for (l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			dsp->fRec90[l134] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l135;
		for (l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			dsp->fRec103[l135] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l136;
		for (l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			dsp->fRec102[l136] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l137;
		for (l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			dsp->fRec101[l137] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l138;
		for (l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			dsp->fRec100[l138] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l139;
		for (l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			dsp->fRec99[l139] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l140;
		for (l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			dsp->fRec98[l140] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l141;
		for (l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			dsp->fRec97[l141] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l142;
		for (l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			dsp->fRec110[l142] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l143;
		for (l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			dsp->fRec109[l143] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l144;
		for (l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			dsp->fRec108[l144] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l145;
		for (l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			dsp->fRec107[l145] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l146;
		for (l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			dsp->fRec106[l146] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l147;
		for (l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			dsp->fRec105[l147] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l148;
		for (l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			dsp->fRec104[l148] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l149;
		for (l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			dsp->fRec117[l149] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l150;
		for (l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			dsp->fRec116[l150] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l151;
		for (l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			dsp->fRec115[l151] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l152;
		for (l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			dsp->fRec114[l152] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l153;
		for (l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			dsp->fRec113[l153] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l154;
		for (l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			dsp->fRec112[l154] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l155;
		for (l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			dsp->fRec111[l155] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l156;
		for (l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			dsp->fRec124[l156] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l157;
		for (l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			dsp->fRec123[l157] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l158;
		for (l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			dsp->fRec122[l158] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l159;
		for (l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			dsp->fRec121[l159] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l160;
		for (l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			dsp->fRec120[l160] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l161;
		for (l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			dsp->fRec119[l161] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l162;
		for (l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			dsp->fRec118[l162] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l163;
		for (l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			dsp->fRec128[l163] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l164;
		for (l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			dsp->fRec127[l164] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l165;
		for (l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			dsp->fRec126[l165] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l166;
		for (l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			dsp->fRec125[l166] = 0.0f;
			
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
	dsp->fConst14 = (1.0f / dsp->fConst0);
	dsp->fConst15 = (0.25f * dsp->fConst0);
	dsp->fConst16 = (0.0416666679f * mydsp_faustpower2_f(dsp->fConst0));
	dsp->fConst17 = (0.00520833349f * mydsp_faustpower3_f(dsp->fConst0));
	dsp->fConst18 = (0.0833333358f * dsp->fConst0);
	dsp->fConst19 = (0.5f * dsp->fConst0);
	dsp->fConst20 = (1.33333337f / dsp->fConst0);
	dsp->fConst21 = (0.013888889f * dsp->fConst0);
	dsp->fConst22 = (6.28318548f / dsp->fConst0);
	dsp->fConst23 = (3.14159274f / dsp->fConst0);
	dsp->fConst24 = (((dsp->fConst3 + -3.18972731f) / dsp->fConst2) + 4.07678175f);
	dsp->fConst25 = (1.0f / dsp->fConst5);
	dsp->fConst26 = (2.0f * (4.07678175f - dsp->fConst25));
	dsp->fConst27 = (dsp->fConst12 + 0.000407678192f);
	dsp->fConst28 = (((dsp->fConst3 + -0.743130445f) / dsp->fConst2) + 1.4500711f);
	dsp->fConst29 = (2.0f * (1.4500711f - dsp->fConst25));
	dsp->fConst30 = (dsp->fConst9 + 1.4500711f);
	dsp->fConst31 = (((dsp->fConst3 + -0.157482162f) / dsp->fConst2) + 0.935140193f);
	dsp->fConst32 = (2.0f * (0.935140193f - dsp->fConst25));
	dsp->fConst33 = (dsp->fConst6 + 0.935140193f);
	dsp->fConst34 = tanf((31665.2695f / dsp->fConst0));
	dsp->fConst35 = (1.0f / dsp->fConst34);
	dsp->fConst36 = (1.0f / (((dsp->fConst35 + 0.157482162f) / dsp->fConst34) + 0.935140193f));
	dsp->fConst37 = mydsp_faustpower2_f(dsp->fConst34);
	dsp->fConst38 = (50.0638084f / dsp->fConst37);
	dsp->fConst39 = (2.0f * (0.935140193f - dsp->fConst38));
	dsp->fConst40 = (1.0f / (((dsp->fConst35 + 0.743130445f) / dsp->fConst34) + 1.4500711f));
	dsp->fConst41 = (11.0520525f / dsp->fConst37);
	dsp->fConst42 = (2.0f * (1.4500711f - dsp->fConst41));
	dsp->fConst43 = (1.0f / (((dsp->fConst35 + 3.18972731f) / dsp->fConst34) + 4.07678175f));
	dsp->fConst44 = (0.00176617282f / dsp->fConst37);
	dsp->fConst45 = (2.0f * (0.000407678192f - dsp->fConst44));
	dsp->fConst46 = (1.0f / (((dsp->fConst3 + 0.168404877f) / dsp->fConst2) + 1.06935835f));
	dsp->fConst47 = (2.0f * (53.5361519f - dsp->fConst25));
	dsp->fConst48 = (1.0f / (((dsp->fConst3 + 0.51247865f) / dsp->fConst2) + 0.689621389f));
	dsp->fConst49 = (2.0f * (7.62173128f - dsp->fConst25));
	dsp->fConst50 = (1.0f / (((dsp->fConst3 + 0.782413065f) / dsp->fConst2) + 0.245291501f));
	dsp->fConst51 = (9.99999975e-05f / dsp->fConst5);
	dsp->fConst52 = (2.0f * (0.000433227193f - dsp->fConst51));
	dsp->fConst53 = (((dsp->fConst3 + -0.782413065f) / dsp->fConst2) + 0.245291501f);
	dsp->fConst54 = (2.0f * (0.245291501f - dsp->fConst25));
	dsp->fConst55 = (dsp->fConst51 + 0.000433227193f);
	dsp->fConst56 = (((dsp->fConst3 + -0.51247865f) / dsp->fConst2) + 0.689621389f);
	dsp->fConst57 = (2.0f * (0.689621389f - dsp->fConst25));
	dsp->fConst58 = (dsp->fConst25 + 7.62173128f);
	dsp->fConst59 = (((dsp->fConst3 + -0.168404877f) / dsp->fConst2) + 1.06935835f);
	dsp->fConst60 = (2.0f * (1.06935835f - dsp->fConst25));
	dsp->fConst61 = (dsp->fConst25 + 53.5361519f);
	dsp->fConst62 = (((dsp->fConst35 + -3.18972731f) / dsp->fConst34) + 4.07678175f);
	dsp->fConst63 = (1.0f / dsp->fConst37);
	dsp->fConst64 = (2.0f * (4.07678175f - dsp->fConst63));
	dsp->fConst65 = (dsp->fConst44 + 0.000407678192f);
	dsp->fConst66 = (((dsp->fConst35 + -0.743130445f) / dsp->fConst34) + 1.4500711f);
	dsp->fConst67 = (2.0f * (1.4500711f - dsp->fConst63));
	dsp->fConst68 = (dsp->fConst41 + 1.4500711f);
	dsp->fConst69 = (((dsp->fConst35 + -0.157482162f) / dsp->fConst34) + 0.935140193f);
	dsp->fConst70 = (2.0f * (0.935140193f - dsp->fConst63));
	dsp->fConst71 = (dsp->fConst38 + 0.935140193f);
	dsp->fConst72 = tanf((19947.8691f / dsp->fConst0));
	dsp->fConst73 = (1.0f / dsp->fConst72);
	dsp->fConst74 = (1.0f / (((dsp->fConst73 + 0.157482162f) / dsp->fConst72) + 0.935140193f));
	dsp->fConst75 = mydsp_faustpower2_f(dsp->fConst72);
	dsp->fConst76 = (50.0638084f / dsp->fConst75);
	dsp->fConst77 = (2.0f * (0.935140193f - dsp->fConst76));
	dsp->fConst78 = (1.0f / (((dsp->fConst73 + 0.743130445f) / dsp->fConst72) + 1.4500711f));
	dsp->fConst79 = (11.0520525f / dsp->fConst75);
	dsp->fConst80 = (2.0f * (1.4500711f - dsp->fConst79));
	dsp->fConst81 = (1.0f / (((dsp->fConst73 + 3.18972731f) / dsp->fConst72) + 4.07678175f));
	dsp->fConst82 = (0.00176617282f / dsp->fConst75);
	dsp->fConst83 = (2.0f * (0.000407678192f - dsp->fConst82));
	dsp->fConst84 = (1.0f / (((dsp->fConst35 + 0.168404877f) / dsp->fConst34) + 1.06935835f));
	dsp->fConst85 = (2.0f * (53.5361519f - dsp->fConst63));
	dsp->fConst86 = (1.0f / (((dsp->fConst35 + 0.51247865f) / dsp->fConst34) + 0.689621389f));
	dsp->fConst87 = (2.0f * (7.62173128f - dsp->fConst63));
	dsp->fConst88 = (1.0f / (((dsp->fConst35 + 0.782413065f) / dsp->fConst34) + 0.245291501f));
	dsp->fConst89 = (9.99999975e-05f / dsp->fConst37);
	dsp->fConst90 = (2.0f * (0.000433227193f - dsp->fConst89));
	dsp->fConst91 = (((dsp->fConst35 + -0.782413065f) / dsp->fConst34) + 0.245291501f);
	dsp->fConst92 = (2.0f * (0.245291501f - dsp->fConst63));
	dsp->fConst93 = (dsp->fConst89 + 0.000433227193f);
	dsp->fConst94 = (((dsp->fConst35 + -0.51247865f) / dsp->fConst34) + 0.689621389f);
	dsp->fConst95 = (2.0f * (0.689621389f - dsp->fConst63));
	dsp->fConst96 = (dsp->fConst63 + 7.62173128f);
	dsp->fConst97 = (((dsp->fConst35 + -0.168404877f) / dsp->fConst34) + 1.06935835f);
	dsp->fConst98 = (2.0f * (1.06935835f - dsp->fConst63));
	dsp->fConst99 = (dsp->fConst63 + 53.5361519f);
	dsp->fConst100 = (((dsp->fConst73 + -3.18972731f) / dsp->fConst72) + 4.07678175f);
	dsp->fConst101 = (1.0f / dsp->fConst75);
	dsp->fConst102 = (2.0f * (4.07678175f - dsp->fConst101));
	dsp->fConst103 = (dsp->fConst82 + 0.000407678192f);
	dsp->fConst104 = (((dsp->fConst73 + -0.743130445f) / dsp->fConst72) + 1.4500711f);
	dsp->fConst105 = (2.0f * (1.4500711f - dsp->fConst101));
	dsp->fConst106 = (dsp->fConst79 + 1.4500711f);
	dsp->fConst107 = (((dsp->fConst73 + -0.157482162f) / dsp->fConst72) + 0.935140193f);
	dsp->fConst108 = (2.0f * (0.935140193f - dsp->fConst101));
	dsp->fConst109 = (dsp->fConst76 + 0.935140193f);
	dsp->fConst110 = tanf((12566.3711f / dsp->fConst0));
	dsp->fConst111 = (1.0f / dsp->fConst110);
	dsp->fConst112 = (1.0f / (((dsp->fConst111 + 0.157482162f) / dsp->fConst110) + 0.935140193f));
	dsp->fConst113 = mydsp_faustpower2_f(dsp->fConst110);
	dsp->fConst114 = (50.0638084f / dsp->fConst113);
	dsp->fConst115 = (2.0f * (0.935140193f - dsp->fConst114));
	dsp->fConst116 = (1.0f / (((dsp->fConst111 + 0.743130445f) / dsp->fConst110) + 1.4500711f));
	dsp->fConst117 = (11.0520525f / dsp->fConst113);
	dsp->fConst118 = (2.0f * (1.4500711f - dsp->fConst117));
	dsp->fConst119 = (1.0f / (((dsp->fConst111 + 3.18972731f) / dsp->fConst110) + 4.07678175f));
	dsp->fConst120 = (0.00176617282f / dsp->fConst113);
	dsp->fConst121 = (2.0f * (0.000407678192f - dsp->fConst120));
	dsp->fConst122 = (1.0f / (((dsp->fConst73 + 0.168404877f) / dsp->fConst72) + 1.06935835f));
	dsp->fConst123 = (2.0f * (53.5361519f - dsp->fConst101));
	dsp->fConst124 = (1.0f / (((dsp->fConst73 + 0.51247865f) / dsp->fConst72) + 0.689621389f));
	dsp->fConst125 = (2.0f * (7.62173128f - dsp->fConst101));
	dsp->fConst126 = (1.0f / (((dsp->fConst73 + 0.782413065f) / dsp->fConst72) + 0.245291501f));
	dsp->fConst127 = (9.99999975e-05f / dsp->fConst75);
	dsp->fConst128 = (2.0f * (0.000433227193f - dsp->fConst127));
	dsp->fConst129 = (((dsp->fConst73 + -0.782413065f) / dsp->fConst72) + 0.245291501f);
	dsp->fConst130 = (2.0f * (0.245291501f - dsp->fConst101));
	dsp->fConst131 = (dsp->fConst127 + 0.000433227193f);
	dsp->fConst132 = (((dsp->fConst73 + -0.51247865f) / dsp->fConst72) + 0.689621389f);
	dsp->fConst133 = (2.0f * (0.689621389f - dsp->fConst101));
	dsp->fConst134 = (dsp->fConst101 + 7.62173128f);
	dsp->fConst135 = (((dsp->fConst73 + -0.168404877f) / dsp->fConst72) + 1.06935835f);
	dsp->fConst136 = (2.0f * (1.06935835f - dsp->fConst101));
	dsp->fConst137 = (dsp->fConst101 + 53.5361519f);
	dsp->fConst138 = (((dsp->fConst111 + -3.18972731f) / dsp->fConst110) + 4.07678175f);
	dsp->fConst139 = (1.0f / dsp->fConst113);
	dsp->fConst140 = (2.0f * (4.07678175f - dsp->fConst139));
	dsp->fConst141 = (dsp->fConst120 + 0.000407678192f);
	dsp->fConst142 = (((dsp->fConst111 + -0.743130445f) / dsp->fConst110) + 1.4500711f);
	dsp->fConst143 = (2.0f * (1.4500711f - dsp->fConst139));
	dsp->fConst144 = (dsp->fConst117 + 1.4500711f);
	dsp->fConst145 = (((dsp->fConst111 + -0.157482162f) / dsp->fConst110) + 0.935140193f);
	dsp->fConst146 = (2.0f * (0.935140193f - dsp->fConst139));
	dsp->fConst147 = (dsp->fConst114 + 0.935140193f);
	dsp->fConst148 = tanf((7916.31738f / dsp->fConst0));
	dsp->fConst149 = (1.0f / dsp->fConst148);
	dsp->fConst150 = (1.0f / (((dsp->fConst149 + 0.157482162f) / dsp->fConst148) + 0.935140193f));
	dsp->fConst151 = mydsp_faustpower2_f(dsp->fConst148);
	dsp->fConst152 = (50.0638084f / dsp->fConst151);
	dsp->fConst153 = (2.0f * (0.935140193f - dsp->fConst152));
	dsp->fConst154 = (1.0f / (((dsp->fConst149 + 0.743130445f) / dsp->fConst148) + 1.4500711f));
	dsp->fConst155 = (11.0520525f / dsp->fConst151);
	dsp->fConst156 = (2.0f * (1.4500711f - dsp->fConst155));
	dsp->fConst157 = (1.0f / (((dsp->fConst149 + 3.18972731f) / dsp->fConst148) + 4.07678175f));
	dsp->fConst158 = (0.00176617282f / dsp->fConst151);
	dsp->fConst159 = (2.0f * (0.000407678192f - dsp->fConst158));
	dsp->fConst160 = (1.0f / (((dsp->fConst111 + 0.168404877f) / dsp->fConst110) + 1.06935835f));
	dsp->fConst161 = (2.0f * (53.5361519f - dsp->fConst139));
	dsp->fConst162 = (1.0f / (((dsp->fConst111 + 0.51247865f) / dsp->fConst110) + 0.689621389f));
	dsp->fConst163 = (2.0f * (7.62173128f - dsp->fConst139));
	dsp->fConst164 = (1.0f / (((dsp->fConst111 + 0.782413065f) / dsp->fConst110) + 0.245291501f));
	dsp->fConst165 = (9.99999975e-05f / dsp->fConst113);
	dsp->fConst166 = (2.0f * (0.000433227193f - dsp->fConst165));
	dsp->fConst167 = (((dsp->fConst111 + -0.782413065f) / dsp->fConst110) + 0.245291501f);
	dsp->fConst168 = (2.0f * (0.245291501f - dsp->fConst139));
	dsp->fConst169 = (dsp->fConst165 + 0.000433227193f);
	dsp->fConst170 = (((dsp->fConst111 + -0.51247865f) / dsp->fConst110) + 0.689621389f);
	dsp->fConst171 = (2.0f * (0.689621389f - dsp->fConst139));
	dsp->fConst172 = (dsp->fConst139 + 7.62173128f);
	dsp->fConst173 = (((dsp->fConst111 + -0.168404877f) / dsp->fConst110) + 1.06935835f);
	dsp->fConst174 = (2.0f * (1.06935835f - dsp->fConst139));
	dsp->fConst175 = (dsp->fConst139 + 53.5361519f);
	dsp->fConst176 = (((dsp->fConst149 + -3.18972731f) / dsp->fConst148) + 4.07678175f);
	dsp->fConst177 = (1.0f / dsp->fConst151);
	dsp->fConst178 = (2.0f * (4.07678175f - dsp->fConst177));
	dsp->fConst179 = (dsp->fConst158 + 0.000407678192f);
	dsp->fConst180 = (((dsp->fConst149 + -0.743130445f) / dsp->fConst148) + 1.4500711f);
	dsp->fConst181 = (2.0f * (1.4500711f - dsp->fConst177));
	dsp->fConst182 = (dsp->fConst155 + 1.4500711f);
	dsp->fConst183 = (((dsp->fConst149 + -0.157482162f) / dsp->fConst148) + 0.935140193f);
	dsp->fConst184 = (2.0f * (0.935140193f - dsp->fConst177));
	dsp->fConst185 = (dsp->fConst152 + 0.935140193f);
	dsp->fConst186 = tanf((4986.96729f / dsp->fConst0));
	dsp->fConst187 = (1.0f / dsp->fConst186);
	dsp->fConst188 = (1.0f / (((dsp->fConst187 + 0.157482162f) / dsp->fConst186) + 0.935140193f));
	dsp->fConst189 = mydsp_faustpower2_f(dsp->fConst186);
	dsp->fConst190 = (50.0638084f / dsp->fConst189);
	dsp->fConst191 = (2.0f * (0.935140193f - dsp->fConst190));
	dsp->fConst192 = (1.0f / (((dsp->fConst187 + 0.743130445f) / dsp->fConst186) + 1.4500711f));
	dsp->fConst193 = (11.0520525f / dsp->fConst189);
	dsp->fConst194 = (2.0f * (1.4500711f - dsp->fConst193));
	dsp->fConst195 = (1.0f / (((dsp->fConst187 + 3.18972731f) / dsp->fConst186) + 4.07678175f));
	dsp->fConst196 = (0.00176617282f / dsp->fConst189);
	dsp->fConst197 = (2.0f * (0.000407678192f - dsp->fConst196));
	dsp->fConst198 = (1.0f / (((dsp->fConst149 + 0.168404877f) / dsp->fConst148) + 1.06935835f));
	dsp->fConst199 = (2.0f * (53.5361519f - dsp->fConst177));
	dsp->fConst200 = (1.0f / (((dsp->fConst149 + 0.51247865f) / dsp->fConst148) + 0.689621389f));
	dsp->fConst201 = (2.0f * (7.62173128f - dsp->fConst177));
	dsp->fConst202 = (1.0f / (((dsp->fConst149 + 0.782413065f) / dsp->fConst148) + 0.245291501f));
	dsp->fConst203 = (9.99999975e-05f / dsp->fConst151);
	dsp->fConst204 = (2.0f * (0.000433227193f - dsp->fConst203));
	dsp->fConst205 = (((dsp->fConst149 + -0.782413065f) / dsp->fConst148) + 0.245291501f);
	dsp->fConst206 = (2.0f * (0.245291501f - dsp->fConst177));
	dsp->fConst207 = (dsp->fConst203 + 0.000433227193f);
	dsp->fConst208 = (((dsp->fConst149 + -0.51247865f) / dsp->fConst148) + 0.689621389f);
	dsp->fConst209 = (2.0f * (0.689621389f - dsp->fConst177));
	dsp->fConst210 = (dsp->fConst177 + 7.62173128f);
	dsp->fConst211 = (((dsp->fConst149 + -0.168404877f) / dsp->fConst148) + 1.06935835f);
	dsp->fConst212 = (2.0f * (1.06935835f - dsp->fConst177));
	dsp->fConst213 = (dsp->fConst177 + 53.5361519f);
	dsp->fConst214 = (((dsp->fConst187 + -3.18972731f) / dsp->fConst186) + 4.07678175f);
	dsp->fConst215 = (1.0f / dsp->fConst189);
	dsp->fConst216 = (2.0f * (4.07678175f - dsp->fConst215));
	dsp->fConst217 = (dsp->fConst196 + 0.000407678192f);
	dsp->fConst218 = (((dsp->fConst187 + -0.743130445f) / dsp->fConst186) + 1.4500711f);
	dsp->fConst219 = (2.0f * (1.4500711f - dsp->fConst215));
	dsp->fConst220 = (dsp->fConst193 + 1.4500711f);
	dsp->fConst221 = (((dsp->fConst187 + -0.157482162f) / dsp->fConst186) + 0.935140193f);
	dsp->fConst222 = (2.0f * (0.935140193f - dsp->fConst215));
	dsp->fConst223 = (dsp->fConst190 + 0.935140193f);
	dsp->fConst224 = tanf((3141.59277f / dsp->fConst0));
	dsp->fConst225 = (1.0f / dsp->fConst224);
	dsp->fConst226 = (1.0f / (((dsp->fConst225 + 0.157482162f) / dsp->fConst224) + 0.935140193f));
	dsp->fConst227 = mydsp_faustpower2_f(dsp->fConst224);
	dsp->fConst228 = (50.0638084f / dsp->fConst227);
	dsp->fConst229 = (2.0f * (0.935140193f - dsp->fConst228));
	dsp->fConst230 = (1.0f / (((dsp->fConst225 + 0.743130445f) / dsp->fConst224) + 1.4500711f));
	dsp->fConst231 = (11.0520525f / dsp->fConst227);
	dsp->fConst232 = (2.0f * (1.4500711f - dsp->fConst231));
	dsp->fConst233 = (1.0f / (((dsp->fConst225 + 3.18972731f) / dsp->fConst224) + 4.07678175f));
	dsp->fConst234 = (0.00176617282f / dsp->fConst227);
	dsp->fConst235 = (2.0f * (0.000407678192f - dsp->fConst234));
	dsp->fConst236 = (1.0f / (((dsp->fConst187 + 0.168404877f) / dsp->fConst186) + 1.06935835f));
	dsp->fConst237 = (2.0f * (53.5361519f - dsp->fConst215));
	dsp->fConst238 = (1.0f / (((dsp->fConst187 + 0.51247865f) / dsp->fConst186) + 0.689621389f));
	dsp->fConst239 = (2.0f * (7.62173128f - dsp->fConst215));
	dsp->fConst240 = (1.0f / (((dsp->fConst187 + 0.782413065f) / dsp->fConst186) + 0.245291501f));
	dsp->fConst241 = (9.99999975e-05f / dsp->fConst189);
	dsp->fConst242 = (2.0f * (0.000433227193f - dsp->fConst241));
	dsp->fConst243 = (((dsp->fConst187 + -0.782413065f) / dsp->fConst186) + 0.245291501f);
	dsp->fConst244 = (2.0f * (0.245291501f - dsp->fConst215));
	dsp->fConst245 = (dsp->fConst241 + 0.000433227193f);
	dsp->fConst246 = (((dsp->fConst187 + -0.51247865f) / dsp->fConst186) + 0.689621389f);
	dsp->fConst247 = (2.0f * (0.689621389f - dsp->fConst215));
	dsp->fConst248 = (dsp->fConst215 + 7.62173128f);
	dsp->fConst249 = (((dsp->fConst187 + -0.168404877f) / dsp->fConst186) + 1.06935835f);
	dsp->fConst250 = (2.0f * (1.06935835f - dsp->fConst215));
	dsp->fConst251 = (dsp->fConst215 + 53.5361519f);
	dsp->fConst252 = (((dsp->fConst225 + -3.18972731f) / dsp->fConst224) + 4.07678175f);
	dsp->fConst253 = (1.0f / dsp->fConst227);
	dsp->fConst254 = (2.0f * (4.07678175f - dsp->fConst253));
	dsp->fConst255 = (dsp->fConst234 + 0.000407678192f);
	dsp->fConst256 = (((dsp->fConst225 + -0.743130445f) / dsp->fConst224) + 1.4500711f);
	dsp->fConst257 = (2.0f * (1.4500711f - dsp->fConst253));
	dsp->fConst258 = (dsp->fConst231 + 1.4500711f);
	dsp->fConst259 = (((dsp->fConst225 + -0.157482162f) / dsp->fConst224) + 0.935140193f);
	dsp->fConst260 = (2.0f * (0.935140193f - dsp->fConst253));
	dsp->fConst261 = (dsp->fConst228 + 0.935140193f);
	dsp->fConst262 = tanf((1979.07935f / dsp->fConst0));
	dsp->fConst263 = (1.0f / dsp->fConst262);
	dsp->fConst264 = (1.0f / (((dsp->fConst263 + 0.157482162f) / dsp->fConst262) + 0.935140193f));
	dsp->fConst265 = mydsp_faustpower2_f(dsp->fConst262);
	dsp->fConst266 = (50.0638084f / dsp->fConst265);
	dsp->fConst267 = (2.0f * (0.935140193f - dsp->fConst266));
	dsp->fConst268 = (1.0f / (((dsp->fConst263 + 0.743130445f) / dsp->fConst262) + 1.4500711f));
	dsp->fConst269 = (11.0520525f / dsp->fConst265);
	dsp->fConst270 = (2.0f * (1.4500711f - dsp->fConst269));
	dsp->fConst271 = (1.0f / (((dsp->fConst263 + 3.18972731f) / dsp->fConst262) + 4.07678175f));
	dsp->fConst272 = (0.00176617282f / dsp->fConst265);
	dsp->fConst273 = (2.0f * (0.000407678192f - dsp->fConst272));
	dsp->fConst274 = (1.0f / (((dsp->fConst225 + 0.168404877f) / dsp->fConst224) + 1.06935835f));
	dsp->fConst275 = (2.0f * (53.5361519f - dsp->fConst253));
	dsp->fConst276 = (1.0f / (((dsp->fConst225 + 0.51247865f) / dsp->fConst224) + 0.689621389f));
	dsp->fConst277 = (2.0f * (7.62173128f - dsp->fConst253));
	dsp->fConst278 = (1.0f / (((dsp->fConst225 + 0.782413065f) / dsp->fConst224) + 0.245291501f));
	dsp->fConst279 = (9.99999975e-05f / dsp->fConst227);
	dsp->fConst280 = (2.0f * (0.000433227193f - dsp->fConst279));
	dsp->fConst281 = (((dsp->fConst225 + -0.782413065f) / dsp->fConst224) + 0.245291501f);
	dsp->fConst282 = (2.0f * (0.245291501f - dsp->fConst253));
	dsp->fConst283 = (dsp->fConst279 + 0.000433227193f);
	dsp->fConst284 = (((dsp->fConst225 + -0.51247865f) / dsp->fConst224) + 0.689621389f);
	dsp->fConst285 = (2.0f * (0.689621389f - dsp->fConst253));
	dsp->fConst286 = (dsp->fConst253 + 7.62173128f);
	dsp->fConst287 = (((dsp->fConst225 + -0.168404877f) / dsp->fConst224) + 1.06935835f);
	dsp->fConst288 = (2.0f * (1.06935835f - dsp->fConst253));
	dsp->fConst289 = (dsp->fConst253 + 53.5361519f);
	dsp->fConst290 = (((dsp->fConst263 + -3.18972731f) / dsp->fConst262) + 4.07678175f);
	dsp->fConst291 = (1.0f / dsp->fConst265);
	dsp->fConst292 = (2.0f * (4.07678175f - dsp->fConst291));
	dsp->fConst293 = (dsp->fConst272 + 0.000407678192f);
	dsp->fConst294 = (((dsp->fConst263 + -0.743130445f) / dsp->fConst262) + 1.4500711f);
	dsp->fConst295 = (2.0f * (1.4500711f - dsp->fConst291));
	dsp->fConst296 = (dsp->fConst269 + 1.4500711f);
	dsp->fConst297 = (((dsp->fConst263 + -0.157482162f) / dsp->fConst262) + 0.935140193f);
	dsp->fConst298 = (2.0f * (0.935140193f - dsp->fConst291));
	dsp->fConst299 = (dsp->fConst266 + 0.935140193f);
	dsp->fConst300 = tanf((1246.74182f / dsp->fConst0));
	dsp->fConst301 = (1.0f / dsp->fConst300);
	dsp->fConst302 = (1.0f / (((dsp->fConst301 + 0.157482162f) / dsp->fConst300) + 0.935140193f));
	dsp->fConst303 = mydsp_faustpower2_f(dsp->fConst300);
	dsp->fConst304 = (50.0638084f / dsp->fConst303);
	dsp->fConst305 = (2.0f * (0.935140193f - dsp->fConst304));
	dsp->fConst306 = (1.0f / (((dsp->fConst301 + 0.743130445f) / dsp->fConst300) + 1.4500711f));
	dsp->fConst307 = (11.0520525f / dsp->fConst303);
	dsp->fConst308 = (2.0f * (1.4500711f - dsp->fConst307));
	dsp->fConst309 = (1.0f / (((dsp->fConst301 + 3.18972731f) / dsp->fConst300) + 4.07678175f));
	dsp->fConst310 = (0.00176617282f / dsp->fConst303);
	dsp->fConst311 = (2.0f * (0.000407678192f - dsp->fConst310));
	dsp->fConst312 = (1.0f / (((dsp->fConst263 + 0.168404877f) / dsp->fConst262) + 1.06935835f));
	dsp->fConst313 = (2.0f * (53.5361519f - dsp->fConst291));
	dsp->fConst314 = (1.0f / (((dsp->fConst263 + 0.51247865f) / dsp->fConst262) + 0.689621389f));
	dsp->fConst315 = (2.0f * (7.62173128f - dsp->fConst291));
	dsp->fConst316 = (1.0f / (((dsp->fConst263 + 0.782413065f) / dsp->fConst262) + 0.245291501f));
	dsp->fConst317 = (9.99999975e-05f / dsp->fConst265);
	dsp->fConst318 = (2.0f * (0.000433227193f - dsp->fConst317));
	dsp->fConst319 = (((dsp->fConst263 + -0.782413065f) / dsp->fConst262) + 0.245291501f);
	dsp->fConst320 = (2.0f * (0.245291501f - dsp->fConst291));
	dsp->fConst321 = (dsp->fConst317 + 0.000433227193f);
	dsp->fConst322 = (((dsp->fConst263 + -0.51247865f) / dsp->fConst262) + 0.689621389f);
	dsp->fConst323 = (2.0f * (0.689621389f - dsp->fConst291));
	dsp->fConst324 = (dsp->fConst291 + 7.62173128f);
	dsp->fConst325 = (((dsp->fConst263 + -0.168404877f) / dsp->fConst262) + 1.06935835f);
	dsp->fConst326 = (2.0f * (1.06935835f - dsp->fConst291));
	dsp->fConst327 = (dsp->fConst291 + 53.5361519f);
	dsp->fConst328 = (((dsp->fConst301 + -3.18972731f) / dsp->fConst300) + 4.07678175f);
	dsp->fConst329 = (1.0f / dsp->fConst303);
	dsp->fConst330 = (2.0f * (4.07678175f - dsp->fConst329));
	dsp->fConst331 = (dsp->fConst310 + 0.000407678192f);
	dsp->fConst332 = (((dsp->fConst301 + -0.743130445f) / dsp->fConst300) + 1.4500711f);
	dsp->fConst333 = (2.0f * (1.4500711f - dsp->fConst329));
	dsp->fConst334 = (dsp->fConst307 + 1.4500711f);
	dsp->fConst335 = (((dsp->fConst301 + -0.157482162f) / dsp->fConst300) + 0.935140193f);
	dsp->fConst336 = (2.0f * (0.935140193f - dsp->fConst329));
	dsp->fConst337 = (dsp->fConst304 + 0.935140193f);
	dsp->fConst338 = tanf((785.398193f / dsp->fConst0));
	dsp->fConst339 = (1.0f / dsp->fConst338);
	dsp->fConst340 = (1.0f / (((dsp->fConst339 + 0.157482162f) / dsp->fConst338) + 0.935140193f));
	dsp->fConst341 = mydsp_faustpower2_f(dsp->fConst338);
	dsp->fConst342 = (50.0638084f / dsp->fConst341);
	dsp->fConst343 = (2.0f * (0.935140193f - dsp->fConst342));
	dsp->fConst344 = (1.0f / (((dsp->fConst339 + 0.743130445f) / dsp->fConst338) + 1.4500711f));
	dsp->fConst345 = (11.0520525f / dsp->fConst341);
	dsp->fConst346 = (2.0f * (1.4500711f - dsp->fConst345));
	dsp->fConst347 = (1.0f / (((dsp->fConst339 + 3.18972731f) / dsp->fConst338) + 4.07678175f));
	dsp->fConst348 = (0.00176617282f / dsp->fConst341);
	dsp->fConst349 = (2.0f * (0.000407678192f - dsp->fConst348));
	dsp->fConst350 = (1.0f / (((dsp->fConst301 + 0.168404877f) / dsp->fConst300) + 1.06935835f));
	dsp->fConst351 = (2.0f * (53.5361519f - dsp->fConst329));
	dsp->fConst352 = (1.0f / (((dsp->fConst301 + 0.51247865f) / dsp->fConst300) + 0.689621389f));
	dsp->fConst353 = (2.0f * (7.62173128f - dsp->fConst329));
	dsp->fConst354 = (1.0f / (((dsp->fConst301 + 0.782413065f) / dsp->fConst300) + 0.245291501f));
	dsp->fConst355 = (9.99999975e-05f / dsp->fConst303);
	dsp->fConst356 = (2.0f * (0.000433227193f - dsp->fConst355));
	dsp->fConst357 = (((dsp->fConst301 + -0.782413065f) / dsp->fConst300) + 0.245291501f);
	dsp->fConst358 = (2.0f * (0.245291501f - dsp->fConst329));
	dsp->fConst359 = (dsp->fConst355 + 0.000433227193f);
	dsp->fConst360 = (((dsp->fConst301 + -0.51247865f) / dsp->fConst300) + 0.689621389f);
	dsp->fConst361 = (2.0f * (0.689621389f - dsp->fConst329));
	dsp->fConst362 = (dsp->fConst329 + 7.62173128f);
	dsp->fConst363 = (((dsp->fConst301 + -0.168404877f) / dsp->fConst300) + 1.06935835f);
	dsp->fConst364 = (2.0f * (1.06935835f - dsp->fConst329));
	dsp->fConst365 = (dsp->fConst329 + 53.5361519f);
	dsp->fConst366 = (((dsp->fConst339 + -3.18972731f) / dsp->fConst338) + 4.07678175f);
	dsp->fConst367 = (1.0f / dsp->fConst341);
	dsp->fConst368 = (2.0f * (4.07678175f - dsp->fConst367));
	dsp->fConst369 = (dsp->fConst348 + 0.000407678192f);
	dsp->fConst370 = (((dsp->fConst339 + -0.743130445f) / dsp->fConst338) + 1.4500711f);
	dsp->fConst371 = (2.0f * (1.4500711f - dsp->fConst367));
	dsp->fConst372 = (dsp->fConst345 + 1.4500711f);
	dsp->fConst373 = (((dsp->fConst339 + -0.157482162f) / dsp->fConst338) + 0.935140193f);
	dsp->fConst374 = (2.0f * (0.935140193f - dsp->fConst367));
	dsp->fConst375 = (dsp->fConst342 + 0.935140193f);
	dsp->fConst376 = tanf((494.769836f / dsp->fConst0));
	dsp->fConst377 = (1.0f / dsp->fConst376);
	dsp->fConst378 = (1.0f / (((dsp->fConst377 + 0.157482162f) / dsp->fConst376) + 0.935140193f));
	dsp->fConst379 = mydsp_faustpower2_f(dsp->fConst376);
	dsp->fConst380 = (50.0638084f / dsp->fConst379);
	dsp->fConst381 = (2.0f * (0.935140193f - dsp->fConst380));
	dsp->fConst382 = (1.0f / (((dsp->fConst377 + 0.743130445f) / dsp->fConst376) + 1.4500711f));
	dsp->fConst383 = (11.0520525f / dsp->fConst379);
	dsp->fConst384 = (2.0f * (1.4500711f - dsp->fConst383));
	dsp->fConst385 = (1.0f / (((dsp->fConst377 + 3.18972731f) / dsp->fConst376) + 4.07678175f));
	dsp->fConst386 = (0.00176617282f / dsp->fConst379);
	dsp->fConst387 = (2.0f * (0.000407678192f - dsp->fConst386));
	dsp->fConst388 = (1.0f / (((dsp->fConst339 + 0.168404877f) / dsp->fConst338) + 1.06935835f));
	dsp->fConst389 = (2.0f * (53.5361519f - dsp->fConst367));
	dsp->fConst390 = (1.0f / (((dsp->fConst339 + 0.51247865f) / dsp->fConst338) + 0.689621389f));
	dsp->fConst391 = (2.0f * (7.62173128f - dsp->fConst367));
	dsp->fConst392 = (1.0f / (((dsp->fConst339 + 0.782413065f) / dsp->fConst338) + 0.245291501f));
	dsp->fConst393 = (9.99999975e-05f / dsp->fConst341);
	dsp->fConst394 = (2.0f * (0.000433227193f - dsp->fConst393));
	dsp->fConst395 = (((dsp->fConst339 + -0.782413065f) / dsp->fConst338) + 0.245291501f);
	dsp->fConst396 = (2.0f * (0.245291501f - dsp->fConst367));
	dsp->fConst397 = (dsp->fConst393 + 0.000433227193f);
	dsp->fConst398 = (((dsp->fConst339 + -0.51247865f) / dsp->fConst338) + 0.689621389f);
	dsp->fConst399 = (2.0f * (0.689621389f - dsp->fConst367));
	dsp->fConst400 = (dsp->fConst367 + 7.62173128f);
	dsp->fConst401 = (((dsp->fConst339 + -0.168404877f) / dsp->fConst338) + 1.06935835f);
	dsp->fConst402 = (2.0f * (1.06935835f - dsp->fConst367));
	dsp->fConst403 = (dsp->fConst367 + 53.5361519f);
	dsp->fConst404 = (((dsp->fConst377 + -3.18972731f) / dsp->fConst376) + 4.07678175f);
	dsp->fConst405 = (1.0f / dsp->fConst379);
	dsp->fConst406 = (2.0f * (4.07678175f - dsp->fConst405));
	dsp->fConst407 = (dsp->fConst386 + 0.000407678192f);
	dsp->fConst408 = (((dsp->fConst377 + -0.743130445f) / dsp->fConst376) + 1.4500711f);
	dsp->fConst409 = (2.0f * (1.4500711f - dsp->fConst405));
	dsp->fConst410 = (dsp->fConst383 + 1.4500711f);
	dsp->fConst411 = (((dsp->fConst377 + -0.157482162f) / dsp->fConst376) + 0.935140193f);
	dsp->fConst412 = (2.0f * (0.935140193f - dsp->fConst405));
	dsp->fConst413 = (dsp->fConst380 + 0.935140193f);
	dsp->fConst414 = tanf((311.685455f / dsp->fConst0));
	dsp->fConst415 = (1.0f / dsp->fConst414);
	dsp->fConst416 = (1.0f / (((dsp->fConst415 + 0.157482162f) / dsp->fConst414) + 0.935140193f));
	dsp->fConst417 = mydsp_faustpower2_f(dsp->fConst414);
	dsp->fConst418 = (50.0638084f / dsp->fConst417);
	dsp->fConst419 = (2.0f * (0.935140193f - dsp->fConst418));
	dsp->fConst420 = (1.0f / (((dsp->fConst415 + 0.743130445f) / dsp->fConst414) + 1.4500711f));
	dsp->fConst421 = (11.0520525f / dsp->fConst417);
	dsp->fConst422 = (2.0f * (1.4500711f - dsp->fConst421));
	dsp->fConst423 = (1.0f / (((dsp->fConst415 + 3.18972731f) / dsp->fConst414) + 4.07678175f));
	dsp->fConst424 = (0.00176617282f / dsp->fConst417);
	dsp->fConst425 = (2.0f * (0.000407678192f - dsp->fConst424));
	dsp->fConst426 = (1.0f / (((dsp->fConst377 + 0.168404877f) / dsp->fConst376) + 1.06935835f));
	dsp->fConst427 = (2.0f * (53.5361519f - dsp->fConst405));
	dsp->fConst428 = (1.0f / (((dsp->fConst377 + 0.51247865f) / dsp->fConst376) + 0.689621389f));
	dsp->fConst429 = (2.0f * (7.62173128f - dsp->fConst405));
	dsp->fConst430 = (1.0f / (((dsp->fConst377 + 0.782413065f) / dsp->fConst376) + 0.245291501f));
	dsp->fConst431 = (9.99999975e-05f / dsp->fConst379);
	dsp->fConst432 = (2.0f * (0.000433227193f - dsp->fConst431));
	dsp->fConst433 = (((dsp->fConst377 + -0.782413065f) / dsp->fConst376) + 0.245291501f);
	dsp->fConst434 = (2.0f * (0.245291501f - dsp->fConst405));
	dsp->fConst435 = (dsp->fConst431 + 0.000433227193f);
	dsp->fConst436 = (((dsp->fConst377 + -0.51247865f) / dsp->fConst376) + 0.689621389f);
	dsp->fConst437 = (2.0f * (0.689621389f - dsp->fConst405));
	dsp->fConst438 = (dsp->fConst405 + 7.62173128f);
	dsp->fConst439 = (((dsp->fConst377 + -0.168404877f) / dsp->fConst376) + 1.06935835f);
	dsp->fConst440 = (2.0f * (1.06935835f - dsp->fConst405));
	dsp->fConst441 = (dsp->fConst405 + 53.5361519f);
	dsp->fConst442 = (((dsp->fConst415 + -3.18972731f) / dsp->fConst414) + 4.07678175f);
	dsp->fConst443 = (1.0f / dsp->fConst417);
	dsp->fConst444 = (2.0f * (4.07678175f - dsp->fConst443));
	dsp->fConst445 = (dsp->fConst424 + 0.000407678192f);
	dsp->fConst446 = (((dsp->fConst415 + -0.743130445f) / dsp->fConst414) + 1.4500711f);
	dsp->fConst447 = (2.0f * (1.4500711f - dsp->fConst443));
	dsp->fConst448 = (dsp->fConst421 + 1.4500711f);
	dsp->fConst449 = (((dsp->fConst415 + -0.157482162f) / dsp->fConst414) + 0.935140193f);
	dsp->fConst450 = (2.0f * (0.935140193f - dsp->fConst443));
	dsp->fConst451 = (dsp->fConst418 + 0.935140193f);
	dsp->fConst452 = tanf((196.349548f / dsp->fConst0));
	dsp->fConst453 = (1.0f / dsp->fConst452);
	dsp->fConst454 = (1.0f / (((dsp->fConst453 + 0.157482162f) / dsp->fConst452) + 0.935140193f));
	dsp->fConst455 = mydsp_faustpower2_f(dsp->fConst452);
	dsp->fConst456 = (50.0638084f / dsp->fConst455);
	dsp->fConst457 = (2.0f * (0.935140193f - dsp->fConst456));
	dsp->fConst458 = (1.0f / (((dsp->fConst453 + 0.743130445f) / dsp->fConst452) + 1.4500711f));
	dsp->fConst459 = (11.0520525f / dsp->fConst455);
	dsp->fConst460 = (2.0f * (1.4500711f - dsp->fConst459));
	dsp->fConst461 = (1.0f / (((dsp->fConst453 + 3.18972731f) / dsp->fConst452) + 4.07678175f));
	dsp->fConst462 = (0.00176617282f / dsp->fConst455);
	dsp->fConst463 = (2.0f * (0.000407678192f - dsp->fConst462));
	dsp->fConst464 = (1.0f / (((dsp->fConst415 + 0.168404877f) / dsp->fConst414) + 1.06935835f));
	dsp->fConst465 = (2.0f * (53.5361519f - dsp->fConst443));
	dsp->fConst466 = (1.0f / (((dsp->fConst415 + 0.51247865f) / dsp->fConst414) + 0.689621389f));
	dsp->fConst467 = (2.0f * (7.62173128f - dsp->fConst443));
	dsp->fConst468 = (1.0f / (((dsp->fConst415 + 0.782413065f) / dsp->fConst414) + 0.245291501f));
	dsp->fConst469 = (9.99999975e-05f / dsp->fConst417);
	dsp->fConst470 = (2.0f * (0.000433227193f - dsp->fConst469));
	dsp->fConst471 = (((dsp->fConst415 + -0.782413065f) / dsp->fConst414) + 0.245291501f);
	dsp->fConst472 = (2.0f * (0.245291501f - dsp->fConst443));
	dsp->fConst473 = (dsp->fConst469 + 0.000433227193f);
	dsp->fConst474 = (((dsp->fConst415 + -0.51247865f) / dsp->fConst414) + 0.689621389f);
	dsp->fConst475 = (2.0f * (0.689621389f - dsp->fConst443));
	dsp->fConst476 = (dsp->fConst443 + 7.62173128f);
	dsp->fConst477 = (((dsp->fConst415 + -0.168404877f) / dsp->fConst414) + 1.06935835f);
	dsp->fConst478 = (2.0f * (1.06935835f - dsp->fConst443));
	dsp->fConst479 = (dsp->fConst443 + 53.5361519f);
	dsp->fConst480 = (((dsp->fConst453 + -3.18972731f) / dsp->fConst452) + 4.07678175f);
	dsp->fConst481 = (1.0f / dsp->fConst455);
	dsp->fConst482 = (2.0f * (4.07678175f - dsp->fConst481));
	dsp->fConst483 = (dsp->fConst462 + 0.000407678192f);
	dsp->fConst484 = (((dsp->fConst453 + -0.743130445f) / dsp->fConst452) + 1.4500711f);
	dsp->fConst485 = (2.0f * (1.4500711f - dsp->fConst481));
	dsp->fConst486 = (dsp->fConst459 + 1.4500711f);
	dsp->fConst487 = (((dsp->fConst453 + -0.157482162f) / dsp->fConst452) + 0.935140193f);
	dsp->fConst488 = (2.0f * (0.935140193f - dsp->fConst481));
	dsp->fConst489 = (dsp->fConst456 + 0.935140193f);
	dsp->fConst490 = tanf((123.692459f / dsp->fConst0));
	dsp->fConst491 = (1.0f / dsp->fConst490);
	dsp->fConst492 = (1.0f / (((dsp->fConst491 + 0.157482162f) / dsp->fConst490) + 0.935140193f));
	dsp->fConst493 = mydsp_faustpower2_f(dsp->fConst490);
	dsp->fConst494 = (50.0638084f / dsp->fConst493);
	dsp->fConst495 = (2.0f * (0.935140193f - dsp->fConst494));
	dsp->fConst496 = (1.0f / (((dsp->fConst491 + 0.743130445f) / dsp->fConst490) + 1.4500711f));
	dsp->fConst497 = (11.0520525f / dsp->fConst493);
	dsp->fConst498 = (2.0f * (1.4500711f - dsp->fConst497));
	dsp->fConst499 = (1.0f / (((dsp->fConst491 + 3.18972731f) / dsp->fConst490) + 4.07678175f));
	dsp->fConst500 = (0.00176617282f / dsp->fConst493);
	dsp->fConst501 = (2.0f * (0.000407678192f - dsp->fConst500));
	dsp->fConst502 = (1.0f / (((dsp->fConst453 + 0.168404877f) / dsp->fConst452) + 1.06935835f));
	dsp->fConst503 = (2.0f * (53.5361519f - dsp->fConst481));
	dsp->fConst504 = (1.0f / (((dsp->fConst453 + 0.51247865f) / dsp->fConst452) + 0.689621389f));
	dsp->fConst505 = (2.0f * (7.62173128f - dsp->fConst481));
	dsp->fConst506 = (1.0f / (((dsp->fConst453 + 0.782413065f) / dsp->fConst452) + 0.245291501f));
	dsp->fConst507 = (9.99999975e-05f / dsp->fConst455);
	dsp->fConst508 = (2.0f * (0.000433227193f - dsp->fConst507));
	dsp->fConst509 = (((dsp->fConst453 + -0.782413065f) / dsp->fConst452) + 0.245291501f);
	dsp->fConst510 = (2.0f * (0.245291501f - dsp->fConst481));
	dsp->fConst511 = (dsp->fConst507 + 0.000433227193f);
	dsp->fConst512 = (((dsp->fConst453 + -0.51247865f) / dsp->fConst452) + 0.689621389f);
	dsp->fConst513 = (2.0f * (0.689621389f - dsp->fConst481));
	dsp->fConst514 = (dsp->fConst481 + 7.62173128f);
	dsp->fConst515 = (((dsp->fConst453 + -0.168404877f) / dsp->fConst452) + 1.06935835f);
	dsp->fConst516 = (2.0f * (1.06935835f - dsp->fConst481));
	dsp->fConst517 = (dsp->fConst481 + 53.5361519f);
	dsp->fConst518 = (((dsp->fConst491 + -3.18972731f) / dsp->fConst490) + 4.07678175f);
	dsp->fConst519 = (1.0f / dsp->fConst493);
	dsp->fConst520 = (2.0f * (4.07678175f - dsp->fConst519));
	dsp->fConst521 = (dsp->fConst500 + 0.000407678192f);
	dsp->fConst522 = (((dsp->fConst491 + -0.743130445f) / dsp->fConst490) + 1.4500711f);
	dsp->fConst523 = (2.0f * (1.4500711f - dsp->fConst519));
	dsp->fConst524 = (dsp->fConst497 + 1.4500711f);
	dsp->fConst525 = (((dsp->fConst491 + -0.157482162f) / dsp->fConst490) + 0.935140193f);
	dsp->fConst526 = (2.0f * (0.935140193f - dsp->fConst519));
	dsp->fConst527 = (dsp->fConst494 + 0.935140193f);
	dsp->fConst528 = (1.0f / (((dsp->fConst491 + 0.168404877f) / dsp->fConst490) + 1.06935835f));
	dsp->fConst529 = (2.0f * (53.5361519f - dsp->fConst519));
	dsp->fConst530 = (1.0f / (((dsp->fConst491 + 0.51247865f) / dsp->fConst490) + 0.689621389f));
	dsp->fConst531 = (2.0f * (7.62173128f - dsp->fConst519));
	dsp->fConst532 = (1.0f / (((dsp->fConst491 + 0.782413065f) / dsp->fConst490) + 0.245291501f));
	dsp->fConst533 = (9.99999975e-05f / dsp->fConst493);
	dsp->fConst534 = (2.0f * (0.000433227193f - dsp->fConst533));
	dsp->fConst535 = (((dsp->fConst491 + -0.782413065f) / dsp->fConst490) + 0.245291501f);
	dsp->fConst536 = (2.0f * (0.245291501f - dsp->fConst519));
	dsp->fConst537 = (dsp->fConst533 + 0.000433227193f);
	dsp->fConst538 = (((dsp->fConst491 + -0.51247865f) / dsp->fConst490) + 0.689621389f);
	dsp->fConst539 = (2.0f * (0.689621389f - dsp->fConst519));
	dsp->fConst540 = (dsp->fConst519 + 7.62173128f);
	dsp->fConst541 = (((dsp->fConst491 + -0.168404877f) / dsp->fConst490) + 1.06935835f);
	dsp->fConst542 = (2.0f * (1.06935835f - dsp->fConst519));
	dsp->fConst543 = (dsp->fConst519 + 53.5361519f);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "virtualAnalogLab");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's oscillators.lib for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "VIRTUAL ANALOG OSCILLATORS");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Signal Levels");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Sawtooth", &dsp->fVslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Pulse Train");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Order 3", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "style", "knob");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Duty Cycle", &dsp->fVslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Square", &dsp->fVslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Triangle", &dsp->fVslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "style", "vslider");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Pink Noise", &dsp->fVslider9, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "vslider");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Ext Input", &dsp->fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "Signal Parameters");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "style", "hslider");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "tooltip", "Sawtooth waveform amplitude");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider3, "unit", "dB");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Mix Amplitude", &dsp->fHslider3, -20.0f, -120.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "style", "hslider");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fHslider4, "unit", "PK");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Frequency", &dsp->fHslider4, 49.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Percentange frequency-shift up or down for second oscillator");
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
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "tooltip", "Order of sawtooth aliasing  suppression");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Saw Order", &dsp->fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
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
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Normalized Ladders", &dsp->fCheckbox3);
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
	ui_interface->declare(ui_interface->uiInterface, 0, "3", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d54326b0", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d5420d50", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d53fac80", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d53d8b30", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d53b69e0", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d5394890", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d5372740", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d53505f0", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d532e4a0", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d530c350", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d52e6280", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d52c4130", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d52a1fe0", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d527fe90", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f80d525ccb0", &dsp->fVbargraph0, -50.0f, 10.0f);
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
	float fSlow6 = (float)dsp->fVslider0;
	float fSlow7 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fHslider3)));
	float fSlow8 = (0.333333343f * (float)dsp->fVslider1);
	int iSlow9 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow10 = (iSlow9 >= 2);
	int iSlow11 = (iSlow9 >= 1);
	float fSlow12 = expf((0.0f - (dsp->fConst14 / (float)dsp->fVslider2)));
	float fSlow13 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fHslider4 + -49.0f))) * (1.0f - fSlow12)));
	int iSlow14 = (iSlow9 >= 3);
	float fSlow15 = (1.0f - (0.00999999978f * (float)dsp->fVslider3));
	float fSlow16 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	float fSlow17 = (dsp->fConst18 * (float)dsp->fVslider5);
	float fSlow18 = (dsp->fConst20 * (float)dsp->fVslider6);
	float fSlow19 = (dsp->fConst0 * (float)dsp->fVslider7);
	float fSlow20 = (float)dsp->fCheckbox2;
	float fSlow21 = (0.0833333358f * (1.0f - fSlow20));
	float fSlow22 = (0.00999999978f * (float)dsp->fVslider8);
	float fSlow23 = (dsp->fConst21 * fSlow20);
	float fSlow24 = (float)dsp->fVslider9;
	float fSlow25 = (0.439999998f * powf(2.0f, (0.0833333358f * ((float)dsp->fHslider5 + -49.0f))));
	float fSlow26 = (float)dsp->fHslider6;
	float fSlow27 = (0.0f - (4.0f * max(0.0f, min(mydsp_faustpower4_f(fSlow26), 0.999998987f))));
	int iSlow28 = (int)(float)dsp->fCheckbox3;
	float fSlow29 = min(1.41419947f, (1.41421354f * fSlow26));
	float fSlow30 = (fSlow29 * (fSlow29 + 1.41421354f));
	float fSlow31 = (1.41421354f * fSlow29);
	float fSlow32 = (fSlow31 + 2.0f);
	float fSlow33 = (fSlow29 * (fSlow29 + -1.41421354f));
	float fSlow34 = (2.0f - fSlow31);
	float fSlow35 = mydsp_faustpower2_f((1.41419947f * fSlow26));
	float fSlow36 = (1.99997997f * fSlow26);
	float fSlow37 = (fSlow35 + fSlow36);
	float fSlow38 = (fSlow36 + 2.0f);
	float fSlow39 = (2.0f - fSlow36);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec4[0] = (fSlow4 + (0.999000013f * dsp->fRec4[1]));
			dsp->fRec10[0] = (fSlow7 + (0.999000013f * dsp->fRec10[1]));
			dsp->fRec12[0] = (fSlow13 + (fSlow12 * dsp->fRec12[1]));
			float fTemp0 = max(20.0f, fabsf(dsp->fRec12[0]));
			dsp->fVec1[0] = fTemp0;
			float fTemp1 = (dsp->fRec11[1] + (dsp->fConst14 * dsp->fVec1[1]));
			dsp->fRec11[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * dsp->fRec11[0]);
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
			float fTemp10 = (fSlow15 * dsp->fRec12[0]);
			float fTemp11 = max(20.0f, fabsf(fTemp10));
			dsp->fVec8[0] = fTemp11;
			float fTemp12 = (dsp->fRec13[1] + (dsp->fConst14 * dsp->fVec8[1]));
			dsp->fRec13[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (2.0f * dsp->fRec13[0]);
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
			float fTemp21 = (fSlow16 * dsp->fRec12[0]);
			float fTemp22 = max(20.0f, fabsf(fTemp21));
			dsp->fVec15[0] = fTemp22;
			float fTemp23 = (dsp->fRec14[1] + (dsp->fConst14 * dsp->fVec15[1]));
			dsp->fRec14[0] = (fTemp23 - floorf(fTemp23));
			float fTemp24 = (2.0f * dsp->fRec14[0]);
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
			float fTemp32 = max(dsp->fRec12[0], 23.4489498f);
			float fTemp33 = max(20.0f, fabsf(fTemp32));
			dsp->fVec22[0] = fTemp33;
			float fTemp34 = (dsp->fRec15[1] + (dsp->fConst14 * dsp->fVec22[1]));
			dsp->fRec15[0] = (fTemp34 - floorf(fTemp34));
			float fTemp35 = (2.0f * dsp->fRec15[0]);
			float fTemp36 = (fTemp35 + -1.0f);
			float fTemp37 = mydsp_faustpower2_f(fTemp36);
			dsp->fVec23[0] = fTemp37;
			float fTemp38 = (((float)dsp->iVec0[1] * (fTemp37 - dsp->fVec23[1])) / fTemp33);
			dsp->fVec24[(dsp->IOTA & 4095)] = fTemp38;
			float fTemp39 = max(0.0f, min(2047.0f, (dsp->fConst19 / fTemp32)));
			int iTemp40 = (int)fTemp39;
			float fTemp41 = floorf(fTemp39);
			float fTemp42 = ((fTemp38 - (dsp->fVec24[((dsp->IOTA - iTemp40) & 4095)] * (fTemp41 + (1.0f - fTemp39)))) - ((fTemp39 - fTemp41) * dsp->fVec24[((dsp->IOTA - (iTemp40 + 1)) & 4095)]));
			float fTemp43 = max(fTemp10, 23.4489498f);
			float fTemp44 = max(20.0f, fabsf(fTemp43));
			dsp->fVec25[0] = fTemp44;
			float fTemp45 = (dsp->fRec16[1] + (dsp->fConst14 * dsp->fVec25[1]));
			dsp->fRec16[0] = (fTemp45 - floorf(fTemp45));
			float fTemp46 = (2.0f * dsp->fRec16[0]);
			float fTemp47 = (fTemp46 + -1.0f);
			float fTemp48 = mydsp_faustpower2_f(fTemp47);
			dsp->fVec26[0] = fTemp48;
			float fTemp49 = (((float)dsp->iVec0[1] * (fTemp48 - dsp->fVec26[1])) / fTemp44);
			dsp->fVec27[(dsp->IOTA & 4095)] = fTemp49;
			float fTemp50 = max(0.0f, min(2047.0f, (dsp->fConst19 / fTemp43)));
			int iTemp51 = (int)fTemp50;
			float fTemp52 = floorf(fTemp50);
			float fTemp53 = ((fTemp49 - (dsp->fVec27[((dsp->IOTA - iTemp51) & 4095)] * (fTemp52 + (1.0f - fTemp50)))) - ((fTemp50 - fTemp52) * dsp->fVec27[((dsp->IOTA - (iTemp51 + 1)) & 4095)]));
			float fTemp54 = max(fTemp21, 23.4489498f);
			float fTemp55 = max(20.0f, fabsf(fTemp54));
			dsp->fVec28[0] = fTemp55;
			float fTemp56 = (dsp->fRec17[1] + (dsp->fConst14 * dsp->fVec28[1]));
			dsp->fRec17[0] = (fTemp56 - floorf(fTemp56));
			float fTemp57 = (2.0f * dsp->fRec17[0]);
			float fTemp58 = (fTemp57 + -1.0f);
			float fTemp59 = mydsp_faustpower2_f(fTemp58);
			dsp->fVec29[0] = fTemp59;
			float fTemp60 = (((float)dsp->iVec0[1] * (fTemp59 - dsp->fVec29[1])) / fTemp55);
			dsp->fVec30[(dsp->IOTA & 4095)] = fTemp60;
			float fTemp61 = max(0.0f, min(2047.0f, (dsp->fConst19 / fTemp54)));
			int iTemp62 = (int)fTemp61;
			float fTemp63 = floorf(fTemp61);
			float fTemp64 = ((fTemp60 - (dsp->fVec30[((dsp->IOTA - iTemp62) & 4095)] * (fTemp63 + (1.0f - fTemp61)))) - ((fTemp61 - fTemp63) * dsp->fVec30[((dsp->IOTA - (iTemp62 + 1)) & 4095)]));
			dsp->fRec18[0] = ((dsp->fConst15 * fTemp42) + (0.999000013f * dsp->fRec18[1]));
			dsp->fRec19[0] = ((dsp->fConst15 * fTemp53) + (0.999000013f * dsp->fRec19[1]));
			dsp->fRec20[0] = ((dsp->fConst15 * fTemp64) + (0.999000013f * dsp->fRec20[1]));
			dsp->fRec21[0] = (fSlow22 + (0.99000001f * dsp->fRec21[1]));
			float fTemp65 = max(0.0f, min(2047.0f, (dsp->fConst0 * (dsp->fRec21[0] / fTemp32))));
			float fTemp66 = floorf(fTemp65);
			float fTemp67 = (fTemp66 + (1.0f - fTemp65));
			int iTemp68 = (int)fTemp65;
			float fTemp69 = (fTemp65 - fTemp66);
			int iTemp70 = (iTemp68 + 1);
			float fTemp71 = max(0.0f, min(2047.0f, (dsp->fConst0 * (dsp->fRec21[0] / fTemp43))));
			float fTemp72 = floorf(fTemp71);
			float fTemp73 = (fTemp72 + (1.0f - fTemp71));
			int iTemp74 = (int)fTemp71;
			float fTemp75 = (fTemp71 - fTemp72);
			int iTemp76 = (iTemp74 + 1);
			float fTemp77 = max(0.0f, min(2047.0f, (dsp->fConst0 * (dsp->fRec21[0] / fTemp54))));
			float fTemp78 = floorf(fTemp77);
			float fTemp79 = (fTemp78 + (1.0f - fTemp77));
			int iTemp80 = (int)fTemp77;
			float fTemp81 = (fTemp77 - fTemp78);
			int iTemp82 = (iTemp80 + 1);
			float fTemp83 = mydsp_faustpower3_f(fTemp36);
			dsp->fVec31[0] = (fTemp83 + (1.0f - fTemp35));
			float fTemp84 = ((fTemp83 + (1.0f - (fTemp35 + dsp->fVec31[1]))) / fTemp33);
			dsp->fVec32[0] = fTemp84;
			float fTemp85 = (((float)dsp->iVec0[2] * (fTemp84 - dsp->fVec32[1])) / fTemp33);
			dsp->fVec33[(dsp->IOTA & 4095)] = fTemp85;
			float fTemp86 = mydsp_faustpower3_f(fTemp47);
			dsp->fVec34[0] = (fTemp86 + (1.0f - fTemp46));
			float fTemp87 = ((fTemp86 + (1.0f - (fTemp46 + dsp->fVec34[1]))) / fTemp44);
			dsp->fVec35[0] = fTemp87;
			float fTemp88 = (((float)dsp->iVec0[2] * (fTemp87 - dsp->fVec35[1])) / fTemp44);
			dsp->fVec36[(dsp->IOTA & 4095)] = fTemp88;
			float fTemp89 = mydsp_faustpower3_f(fTemp58);
			dsp->fVec37[0] = (fTemp89 + (1.0f - fTemp57));
			float fTemp90 = ((fTemp89 + (1.0f - (fTemp57 + dsp->fVec37[1]))) / fTemp55);
			dsp->fVec38[0] = fTemp90;
			float fTemp91 = (((float)dsp->iVec0[2] * (fTemp90 - dsp->fVec38[1])) / fTemp55);
			dsp->fVec39[(dsp->IOTA & 4095)] = fTemp91;
			dsp->iRec23[0] = ((1103515245 * dsp->iRec23[1]) + 12345);
			dsp->fRec22[0] = (((0.522189379f * dsp->fRec22[3]) + ((4.65661287e-10f * (float)dsp->iRec23[0]) + (2.49495602f * dsp->fRec22[1]))) - (2.0172658f * dsp->fRec22[2]));
			float fTemp92 = ((fSlow6 * (float)input0[i]) + (dsp->fRec10[0] * (((((fSlow8 * (((iSlow10?(iSlow14?(dsp->fConst17 * (((float)dsp->iVec0[3] * (fTemp9 - dsp->fVec7[1])) / fTemp0)):(dsp->fConst16 * (((float)dsp->iVec0[2] * (fTemp6 - dsp->fVec4[1])) / fTemp0))):(iSlow11?(dsp->fConst15 * (((float)dsp->iVec0[1] * (fTemp4 - dsp->fVec2[1])) / fTemp0)):fTemp3)) + (iSlow10?(iSlow14?(dsp->fConst17 * (((float)dsp->iVec0[3] * (fTemp20 - dsp->fVec14[1])) / fTemp11)):(dsp->fConst16 * (((float)dsp->iVec0[2] * (fTemp17 - dsp->fVec11[1])) / fTemp11))):(iSlow11?(dsp->fConst15 * (((float)dsp->iVec0[1] * (fTemp15 - dsp->fVec9[1])) / fTemp11)):fTemp14))) + (iSlow10?(iSlow14?(dsp->fConst17 * (((float)dsp->iVec0[3] * (fTemp31 - dsp->fVec21[1])) / fTemp22)):(dsp->fConst16 * (((float)dsp->iVec0[2] * (fTemp28 - dsp->fVec18[1])) / fTemp22))):(iSlow11?(dsp->fConst15 * (((float)dsp->iVec0[1] * (fTemp26 - dsp->fVec16[1])) / fTemp22)):fTemp25)))) + (fSlow17 * ((fTemp42 + fTemp53) + fTemp64))) + (fSlow18 * (dsp->fRec12[0] * ((dsp->fRec18[0] + (fSlow15 * dsp->fRec19[0])) + (fSlow16 * dsp->fRec20[0]))))) + (fSlow19 * ((fSlow21 * ((((fTemp38 - (fTemp67 * dsp->fVec24[((dsp->IOTA - iTemp68) & 4095)])) - (fTemp69 * dsp->fVec24[((dsp->IOTA - iTemp70) & 4095)])) + ((fTemp49 - (fTemp73 * dsp->fVec27[((dsp->IOTA - iTemp74) & 4095)])) - (fTemp75 * dsp->fVec27[((dsp->IOTA - iTemp76) & 4095)]))) + ((fTemp60 - (fTemp79 * dsp->fVec30[((dsp->IOTA - iTemp80) & 4095)])) - (fTemp81 * dsp->fVec30[((dsp->IOTA - iTemp82) & 4095)])))) + (fSlow23 * ((((fTemp85 - (dsp->fVec33[((dsp->IOTA - iTemp68) & 4095)] * fTemp67)) - (fTemp69 * dsp->fVec33[((dsp->IOTA - iTemp70) & 4095)])) + ((fTemp88 - (dsp->fVec36[((dsp->IOTA - iTemp74) & 4095)] * fTemp73)) - (fTemp75 * dsp->fVec36[((dsp->IOTA - iTemp76) & 4095)]))) + ((fTemp91 - (dsp->fVec39[((dsp->IOTA - iTemp80) & 4095)] * fTemp79)) - (fTemp81 * dsp->fVec39[((dsp->IOTA - iTemp82) & 4095)]))))))) + (fSlow24 * (((0.0499220341f * dsp->fRec22[0]) + (0.0506126992f * dsp->fRec22[2])) - ((0.0959935337f * dsp->fRec22[1]) + (0.00440878607f * dsp->fRec22[3])))))));
			float fTemp93 = (iSlow3?0.0f:fTemp92);
			dsp->fRec24[0] = (fSlow25 + (0.999000013f * dsp->fRec24[1]));
			float fTemp94 = (dsp->fConst22 * dsp->fRec24[0]);
			float fTemp95 = (1.0f - fTemp94);
			dsp->fRec9[0] = (fTemp93 + ((fTemp95 * dsp->fRec9[1]) + (fSlow27 * dsp->fRec5[1])));
			dsp->fRec8[0] = (dsp->fRec9[0] + (fTemp95 * dsp->fRec8[1]));
			dsp->fRec7[0] = (dsp->fRec8[0] + (fTemp95 * dsp->fRec7[1]));
			dsp->fRec6[0] = (dsp->fRec7[0] + (dsp->fRec6[1] * fTemp95));
			dsp->fRec5[0] = (dsp->fRec6[0] * powf(fTemp94, 4.0f));
			dsp->fRec27[0] = (fSlow25 + (0.999000013f * dsp->fRec27[1]));
			float fTemp96 = tanf((dsp->fConst23 * max(20.0f, min(10000.0f, dsp->fRec27[0]))));
			float fTemp97 = (1.0f / fTemp96);
			float fTemp98 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp96)));
			float fTemp99 = (fSlow30 + (((fSlow32 + fTemp97) / fTemp96) + 1.0f));
			dsp->fRec26[0] = (fTemp93 - (((dsp->fRec26[2] * (fSlow30 + (((fTemp97 - fSlow32) / fTemp96) + 1.0f))) + (2.0f * (dsp->fRec26[1] * (fSlow30 + fTemp98)))) / fTemp99));
			float fTemp100 = (fSlow33 + (((fSlow34 + fTemp97) / fTemp96) + 1.0f));
			dsp->fRec25[0] = (((dsp->fRec26[2] + (dsp->fRec26[0] + (2.0f * dsp->fRec26[1]))) / fTemp99) - (((dsp->fRec25[2] * (fSlow33 + (((fTemp97 - fSlow34) / fTemp96) + 1.0f))) + (2.0f * (dsp->fRec25[1] * (fSlow33 + fTemp98)))) / fTemp100));
			float fTemp101 = tanf((dsp->fConst23 * max(dsp->fRec27[0], 20.0f)));
			float fTemp102 = (1.0f / fTemp101);
			float fTemp103 = (fSlow37 + (((fSlow38 + fTemp102) / fTemp101) + 1.0f));
			float fTemp104 = ((fSlow37 + (1.0f - ((fSlow38 - fTemp102) / fTemp101))) / fTemp103);
			float fTemp105 = max(-0.999899983f, min(0.999899983f, fTemp104));
			float fTemp106 = (1.0f - mydsp_faustpower2_f(fTemp105));
			float fTemp107 = sqrtf(max(0.0f, fTemp106));
			float fTemp108 = ((dsp->fRec28[1] * (0.0f - fTemp105)) + (fTemp93 * fTemp107));
			float fTemp109 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp101)));
			float fTemp110 = (fSlow37 + fTemp109);
			float fTemp111 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp110 / (fTemp103 * (fTemp104 + 1.0f))))));
			float fTemp112 = (1.0f - mydsp_faustpower2_f(fTemp111));
			float fTemp113 = sqrtf(max(0.0f, fTemp112));
			dsp->fRec30[0] = ((dsp->fRec30[1] * (0.0f - fTemp111)) + (fTemp108 * fTemp113));
			dsp->fRec28[0] = ((fTemp108 * fTemp111) + (dsp->fRec30[1] * fTemp113));
			float fRec29 = dsp->fRec30[0];
			float fTemp114 = (1.0f - (fTemp110 / fTemp103));
			float fTemp115 = sqrtf(fTemp106);
			float fTemp116 = ((((fTemp93 * fTemp105) + (dsp->fRec28[1] * fTemp107)) + (2.0f * ((dsp->fRec28[0] * fTemp114) / fTemp115))) + ((fRec29 * ((1.0f - fTemp104) - (2.0f * (fTemp111 * fTemp114)))) / (fTemp115 * sqrtf(fTemp112))));
			float fTemp117 = (fSlow35 + ((((fSlow39 + fTemp102) / fTemp101) + 1.0f) - fSlow36));
			float fTemp118 = ((fSlow35 + ((((fTemp102 - fSlow39) / fTemp101) + 1.0f) - fSlow36)) / fTemp117);
			float fTemp119 = max(-0.999899983f, min(0.999899983f, fTemp118));
			float fTemp120 = (1.0f - mydsp_faustpower2_f(fTemp119));
			float fTemp121 = sqrtf(max(0.0f, fTemp120));
			float fTemp122 = ((dsp->fRec31[1] * (0.0f - fTemp119)) + ((fTemp116 * fTemp121) / fTemp103));
			float fTemp123 = (fSlow35 + (fTemp109 - fSlow36));
			float fTemp124 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp123 / (fTemp117 * (fTemp118 + 1.0f))))));
			float fTemp125 = (1.0f - mydsp_faustpower2_f(fTemp124));
			float fTemp126 = sqrtf(max(0.0f, fTemp125));
			dsp->fRec33[0] = ((dsp->fRec33[1] * (0.0f - fTemp124)) + (fTemp122 * fTemp126));
			dsp->fRec31[0] = ((fTemp122 * fTemp124) + (dsp->fRec33[1] * fTemp126));
			float fRec32 = dsp->fRec33[0];
			float fTemp127 = (1.0f - (fTemp123 / fTemp117));
			float fTemp128 = sqrtf(fTemp120);
			float fTemp129 = (iSlow3?fTemp92:(dsp->fRec4[0] * (iSlow5?(iSlow28?((((((fTemp116 * fTemp119) / fTemp103) + (dsp->fRec31[1] * fTemp121)) + (2.0f * ((dsp->fRec31[0] * fTemp127) / fTemp128))) + ((fRec32 * ((1.0f - fTemp118) - (2.0f * (fTemp124 * fTemp127)))) / (fTemp128 * sqrtf(fTemp125)))) / fTemp117):((dsp->fRec25[2] + (dsp->fRec25[0] + (2.0f * dsp->fRec25[1]))) / fTemp100)):dsp->fRec5[0])));
			dsp->fRec3[0] = (fTemp129 - (dsp->fConst11 * ((dsp->fConst24 * dsp->fRec3[2]) + (dsp->fConst26 * dsp->fRec3[1]))));
			dsp->fRec2[0] = ((dsp->fConst11 * (((dsp->fConst13 * dsp->fRec3[1]) + (dsp->fConst27 * dsp->fRec3[0])) + (dsp->fConst27 * dsp->fRec3[2]))) - (dsp->fConst8 * ((dsp->fConst28 * dsp->fRec2[2]) + (dsp->fConst29 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst8 * (((dsp->fConst10 * dsp->fRec2[1]) + (dsp->fConst30 * dsp->fRec2[0])) + (dsp->fConst30 * dsp->fRec2[2]))) - (dsp->fConst4 * ((dsp->fConst31 * dsp->fRec1[2]) + (dsp->fConst32 * dsp->fRec1[1]))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * fabsf((dsp->fConst4 * (((dsp->fConst7 * dsp->fRec1[1]) + (dsp->fConst33 * dsp->fRec1[0])) + (dsp->fConst33 * dsp->fRec1[2]))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec0[0]))));
			dsp->fRec40[0] = (fTemp129 - (dsp->fConst50 * ((dsp->fConst53 * dsp->fRec40[2]) + (dsp->fConst54 * dsp->fRec40[1]))));
			dsp->fRec39[0] = ((dsp->fConst50 * (((dsp->fConst52 * dsp->fRec40[1]) + (dsp->fConst55 * dsp->fRec40[0])) + (dsp->fConst55 * dsp->fRec40[2]))) - (dsp->fConst48 * ((dsp->fConst56 * dsp->fRec39[2]) + (dsp->fConst57 * dsp->fRec39[1]))));
			dsp->fRec38[0] = ((dsp->fConst48 * (((dsp->fConst49 * dsp->fRec39[1]) + (dsp->fConst58 * dsp->fRec39[0])) + (dsp->fConst58 * dsp->fRec39[2]))) - (dsp->fConst46 * ((dsp->fConst59 * dsp->fRec38[2]) + (dsp->fConst60 * dsp->fRec38[1]))));
			float fTemp130 = (dsp->fConst46 * (((dsp->fConst47 * dsp->fRec38[1]) + (dsp->fConst61 * dsp->fRec38[0])) + (dsp->fConst61 * dsp->fRec38[2])));
			dsp->fRec37[0] = (fTemp130 - (dsp->fConst43 * ((dsp->fConst62 * dsp->fRec37[2]) + (dsp->fConst64 * dsp->fRec37[1]))));
			dsp->fRec36[0] = ((dsp->fConst43 * (((dsp->fConst45 * dsp->fRec37[1]) + (dsp->fConst65 * dsp->fRec37[0])) + (dsp->fConst65 * dsp->fRec37[2]))) - (dsp->fConst40 * ((dsp->fConst66 * dsp->fRec36[2]) + (dsp->fConst67 * dsp->fRec36[1]))));
			dsp->fRec35[0] = ((dsp->fConst40 * (((dsp->fConst42 * dsp->fRec36[1]) + (dsp->fConst68 * dsp->fRec36[0])) + (dsp->fConst68 * dsp->fRec36[2]))) - (dsp->fConst36 * ((dsp->fConst69 * dsp->fRec35[2]) + (dsp->fConst70 * dsp->fRec35[1]))));
			dsp->fRec34[0] = ((fSlow1 * dsp->fRec34[1]) + (fSlow2 * fabsf((dsp->fConst36 * (((dsp->fConst39 * dsp->fRec35[1]) + (dsp->fConst71 * dsp->fRec35[0])) + (dsp->fConst71 * dsp->fRec35[2]))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec34[0]))));
			dsp->fRec47[0] = (fTemp130 - (dsp->fConst88 * ((dsp->fConst91 * dsp->fRec47[2]) + (dsp->fConst92 * dsp->fRec47[1]))));
			dsp->fRec46[0] = ((dsp->fConst88 * (((dsp->fConst90 * dsp->fRec47[1]) + (dsp->fConst93 * dsp->fRec47[0])) + (dsp->fConst93 * dsp->fRec47[2]))) - (dsp->fConst86 * ((dsp->fConst94 * dsp->fRec46[2]) + (dsp->fConst95 * dsp->fRec46[1]))));
			dsp->fRec45[0] = ((dsp->fConst86 * (((dsp->fConst87 * dsp->fRec46[1]) + (dsp->fConst96 * dsp->fRec46[0])) + (dsp->fConst96 * dsp->fRec46[2]))) - (dsp->fConst84 * ((dsp->fConst97 * dsp->fRec45[2]) + (dsp->fConst98 * dsp->fRec45[1]))));
			float fTemp131 = (dsp->fConst84 * (((dsp->fConst85 * dsp->fRec45[1]) + (dsp->fConst99 * dsp->fRec45[0])) + (dsp->fConst99 * dsp->fRec45[2])));
			dsp->fRec44[0] = (fTemp131 - (dsp->fConst81 * ((dsp->fConst100 * dsp->fRec44[2]) + (dsp->fConst102 * dsp->fRec44[1]))));
			dsp->fRec43[0] = ((dsp->fConst81 * (((dsp->fConst83 * dsp->fRec44[1]) + (dsp->fConst103 * dsp->fRec44[0])) + (dsp->fConst103 * dsp->fRec44[2]))) - (dsp->fConst78 * ((dsp->fConst104 * dsp->fRec43[2]) + (dsp->fConst105 * dsp->fRec43[1]))));
			dsp->fRec42[0] = ((dsp->fConst78 * (((dsp->fConst80 * dsp->fRec43[1]) + (dsp->fConst106 * dsp->fRec43[0])) + (dsp->fConst106 * dsp->fRec43[2]))) - (dsp->fConst74 * ((dsp->fConst107 * dsp->fRec42[2]) + (dsp->fConst108 * dsp->fRec42[1]))));
			dsp->fRec41[0] = ((fSlow1 * dsp->fRec41[1]) + (fSlow2 * fabsf((dsp->fConst74 * (((dsp->fConst77 * dsp->fRec42[1]) + (dsp->fConst109 * dsp->fRec42[0])) + (dsp->fConst109 * dsp->fRec42[2]))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec41[0]))));
			dsp->fRec54[0] = (fTemp131 - (dsp->fConst126 * ((dsp->fConst129 * dsp->fRec54[2]) + (dsp->fConst130 * dsp->fRec54[1]))));
			dsp->fRec53[0] = ((dsp->fConst126 * (((dsp->fConst128 * dsp->fRec54[1]) + (dsp->fConst131 * dsp->fRec54[0])) + (dsp->fConst131 * dsp->fRec54[2]))) - (dsp->fConst124 * ((dsp->fConst132 * dsp->fRec53[2]) + (dsp->fConst133 * dsp->fRec53[1]))));
			dsp->fRec52[0] = ((dsp->fConst124 * (((dsp->fConst125 * dsp->fRec53[1]) + (dsp->fConst134 * dsp->fRec53[0])) + (dsp->fConst134 * dsp->fRec53[2]))) - (dsp->fConst122 * ((dsp->fConst135 * dsp->fRec52[2]) + (dsp->fConst136 * dsp->fRec52[1]))));
			float fTemp132 = (dsp->fConst122 * (((dsp->fConst123 * dsp->fRec52[1]) + (dsp->fConst137 * dsp->fRec52[0])) + (dsp->fConst137 * dsp->fRec52[2])));
			dsp->fRec51[0] = (fTemp132 - (dsp->fConst119 * ((dsp->fConst138 * dsp->fRec51[2]) + (dsp->fConst140 * dsp->fRec51[1]))));
			dsp->fRec50[0] = ((dsp->fConst119 * (((dsp->fConst121 * dsp->fRec51[1]) + (dsp->fConst141 * dsp->fRec51[0])) + (dsp->fConst141 * dsp->fRec51[2]))) - (dsp->fConst116 * ((dsp->fConst142 * dsp->fRec50[2]) + (dsp->fConst143 * dsp->fRec50[1]))));
			dsp->fRec49[0] = ((dsp->fConst116 * (((dsp->fConst118 * dsp->fRec50[1]) + (dsp->fConst144 * dsp->fRec50[0])) + (dsp->fConst144 * dsp->fRec50[2]))) - (dsp->fConst112 * ((dsp->fConst145 * dsp->fRec49[2]) + (dsp->fConst146 * dsp->fRec49[1]))));
			dsp->fRec48[0] = ((fSlow1 * dsp->fRec48[1]) + (fSlow2 * fabsf((dsp->fConst112 * (((dsp->fConst115 * dsp->fRec49[1]) + (dsp->fConst147 * dsp->fRec49[0])) + (dsp->fConst147 * dsp->fRec49[2]))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec48[0]))));
			dsp->fRec61[0] = (fTemp132 - (dsp->fConst164 * ((dsp->fConst167 * dsp->fRec61[2]) + (dsp->fConst168 * dsp->fRec61[1]))));
			dsp->fRec60[0] = ((dsp->fConst164 * (((dsp->fConst166 * dsp->fRec61[1]) + (dsp->fConst169 * dsp->fRec61[0])) + (dsp->fConst169 * dsp->fRec61[2]))) - (dsp->fConst162 * ((dsp->fConst170 * dsp->fRec60[2]) + (dsp->fConst171 * dsp->fRec60[1]))));
			dsp->fRec59[0] = ((dsp->fConst162 * (((dsp->fConst163 * dsp->fRec60[1]) + (dsp->fConst172 * dsp->fRec60[0])) + (dsp->fConst172 * dsp->fRec60[2]))) - (dsp->fConst160 * ((dsp->fConst173 * dsp->fRec59[2]) + (dsp->fConst174 * dsp->fRec59[1]))));
			float fTemp133 = (dsp->fConst160 * (((dsp->fConst161 * dsp->fRec59[1]) + (dsp->fConst175 * dsp->fRec59[0])) + (dsp->fConst175 * dsp->fRec59[2])));
			dsp->fRec58[0] = (fTemp133 - (dsp->fConst157 * ((dsp->fConst176 * dsp->fRec58[2]) + (dsp->fConst178 * dsp->fRec58[1]))));
			dsp->fRec57[0] = ((dsp->fConst157 * (((dsp->fConst159 * dsp->fRec58[1]) + (dsp->fConst179 * dsp->fRec58[0])) + (dsp->fConst179 * dsp->fRec58[2]))) - (dsp->fConst154 * ((dsp->fConst180 * dsp->fRec57[2]) + (dsp->fConst181 * dsp->fRec57[1]))));
			dsp->fRec56[0] = ((dsp->fConst154 * (((dsp->fConst156 * dsp->fRec57[1]) + (dsp->fConst182 * dsp->fRec57[0])) + (dsp->fConst182 * dsp->fRec57[2]))) - (dsp->fConst150 * ((dsp->fConst183 * dsp->fRec56[2]) + (dsp->fConst184 * dsp->fRec56[1]))));
			dsp->fRec55[0] = ((fSlow1 * dsp->fRec55[1]) + (fSlow2 * fabsf((dsp->fConst150 * (((dsp->fConst153 * dsp->fRec56[1]) + (dsp->fConst185 * dsp->fRec56[0])) + (dsp->fConst185 * dsp->fRec56[2]))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec55[0]))));
			dsp->fRec68[0] = (fTemp133 - (dsp->fConst202 * ((dsp->fConst205 * dsp->fRec68[2]) + (dsp->fConst206 * dsp->fRec68[1]))));
			dsp->fRec67[0] = ((dsp->fConst202 * (((dsp->fConst204 * dsp->fRec68[1]) + (dsp->fConst207 * dsp->fRec68[0])) + (dsp->fConst207 * dsp->fRec68[2]))) - (dsp->fConst200 * ((dsp->fConst208 * dsp->fRec67[2]) + (dsp->fConst209 * dsp->fRec67[1]))));
			dsp->fRec66[0] = ((dsp->fConst200 * (((dsp->fConst201 * dsp->fRec67[1]) + (dsp->fConst210 * dsp->fRec67[0])) + (dsp->fConst210 * dsp->fRec67[2]))) - (dsp->fConst198 * ((dsp->fConst211 * dsp->fRec66[2]) + (dsp->fConst212 * dsp->fRec66[1]))));
			float fTemp134 = (dsp->fConst198 * (((dsp->fConst199 * dsp->fRec66[1]) + (dsp->fConst213 * dsp->fRec66[0])) + (dsp->fConst213 * dsp->fRec66[2])));
			dsp->fRec65[0] = (fTemp134 - (dsp->fConst195 * ((dsp->fConst214 * dsp->fRec65[2]) + (dsp->fConst216 * dsp->fRec65[1]))));
			dsp->fRec64[0] = ((dsp->fConst195 * (((dsp->fConst197 * dsp->fRec65[1]) + (dsp->fConst217 * dsp->fRec65[0])) + (dsp->fConst217 * dsp->fRec65[2]))) - (dsp->fConst192 * ((dsp->fConst218 * dsp->fRec64[2]) + (dsp->fConst219 * dsp->fRec64[1]))));
			dsp->fRec63[0] = ((dsp->fConst192 * (((dsp->fConst194 * dsp->fRec64[1]) + (dsp->fConst220 * dsp->fRec64[0])) + (dsp->fConst220 * dsp->fRec64[2]))) - (dsp->fConst188 * ((dsp->fConst221 * dsp->fRec63[2]) + (dsp->fConst222 * dsp->fRec63[1]))));
			dsp->fRec62[0] = ((fSlow1 * dsp->fRec62[1]) + (fSlow2 * fabsf((dsp->fConst188 * (((dsp->fConst191 * dsp->fRec63[1]) + (dsp->fConst223 * dsp->fRec63[0])) + (dsp->fConst223 * dsp->fRec63[2]))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec62[0]))));
			dsp->fRec75[0] = (fTemp134 - (dsp->fConst240 * ((dsp->fConst243 * dsp->fRec75[2]) + (dsp->fConst244 * dsp->fRec75[1]))));
			dsp->fRec74[0] = ((dsp->fConst240 * (((dsp->fConst242 * dsp->fRec75[1]) + (dsp->fConst245 * dsp->fRec75[0])) + (dsp->fConst245 * dsp->fRec75[2]))) - (dsp->fConst238 * ((dsp->fConst246 * dsp->fRec74[2]) + (dsp->fConst247 * dsp->fRec74[1]))));
			dsp->fRec73[0] = ((dsp->fConst238 * (((dsp->fConst239 * dsp->fRec74[1]) + (dsp->fConst248 * dsp->fRec74[0])) + (dsp->fConst248 * dsp->fRec74[2]))) - (dsp->fConst236 * ((dsp->fConst249 * dsp->fRec73[2]) + (dsp->fConst250 * dsp->fRec73[1]))));
			float fTemp135 = (dsp->fConst236 * (((dsp->fConst237 * dsp->fRec73[1]) + (dsp->fConst251 * dsp->fRec73[0])) + (dsp->fConst251 * dsp->fRec73[2])));
			dsp->fRec72[0] = (fTemp135 - (dsp->fConst233 * ((dsp->fConst252 * dsp->fRec72[2]) + (dsp->fConst254 * dsp->fRec72[1]))));
			dsp->fRec71[0] = ((dsp->fConst233 * (((dsp->fConst235 * dsp->fRec72[1]) + (dsp->fConst255 * dsp->fRec72[0])) + (dsp->fConst255 * dsp->fRec72[2]))) - (dsp->fConst230 * ((dsp->fConst256 * dsp->fRec71[2]) + (dsp->fConst257 * dsp->fRec71[1]))));
			dsp->fRec70[0] = ((dsp->fConst230 * (((dsp->fConst232 * dsp->fRec71[1]) + (dsp->fConst258 * dsp->fRec71[0])) + (dsp->fConst258 * dsp->fRec71[2]))) - (dsp->fConst226 * ((dsp->fConst259 * dsp->fRec70[2]) + (dsp->fConst260 * dsp->fRec70[1]))));
			dsp->fRec69[0] = ((fSlow1 * dsp->fRec69[1]) + (fSlow2 * fabsf((dsp->fConst226 * (((dsp->fConst229 * dsp->fRec70[1]) + (dsp->fConst261 * dsp->fRec70[0])) + (dsp->fConst261 * dsp->fRec70[2]))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec69[0]))));
			dsp->fRec82[0] = (fTemp135 - (dsp->fConst278 * ((dsp->fConst281 * dsp->fRec82[2]) + (dsp->fConst282 * dsp->fRec82[1]))));
			dsp->fRec81[0] = ((dsp->fConst278 * (((dsp->fConst280 * dsp->fRec82[1]) + (dsp->fConst283 * dsp->fRec82[0])) + (dsp->fConst283 * dsp->fRec82[2]))) - (dsp->fConst276 * ((dsp->fConst284 * dsp->fRec81[2]) + (dsp->fConst285 * dsp->fRec81[1]))));
			dsp->fRec80[0] = ((dsp->fConst276 * (((dsp->fConst277 * dsp->fRec81[1]) + (dsp->fConst286 * dsp->fRec81[0])) + (dsp->fConst286 * dsp->fRec81[2]))) - (dsp->fConst274 * ((dsp->fConst287 * dsp->fRec80[2]) + (dsp->fConst288 * dsp->fRec80[1]))));
			float fTemp136 = (dsp->fConst274 * (((dsp->fConst275 * dsp->fRec80[1]) + (dsp->fConst289 * dsp->fRec80[0])) + (dsp->fConst289 * dsp->fRec80[2])));
			dsp->fRec79[0] = (fTemp136 - (dsp->fConst271 * ((dsp->fConst290 * dsp->fRec79[2]) + (dsp->fConst292 * dsp->fRec79[1]))));
			dsp->fRec78[0] = ((dsp->fConst271 * (((dsp->fConst273 * dsp->fRec79[1]) + (dsp->fConst293 * dsp->fRec79[0])) + (dsp->fConst293 * dsp->fRec79[2]))) - (dsp->fConst268 * ((dsp->fConst294 * dsp->fRec78[2]) + (dsp->fConst295 * dsp->fRec78[1]))));
			dsp->fRec77[0] = ((dsp->fConst268 * (((dsp->fConst270 * dsp->fRec78[1]) + (dsp->fConst296 * dsp->fRec78[0])) + (dsp->fConst296 * dsp->fRec78[2]))) - (dsp->fConst264 * ((dsp->fConst297 * dsp->fRec77[2]) + (dsp->fConst298 * dsp->fRec77[1]))));
			dsp->fRec76[0] = ((fSlow1 * dsp->fRec76[1]) + (fSlow2 * fabsf((dsp->fConst264 * (((dsp->fConst267 * dsp->fRec77[1]) + (dsp->fConst299 * dsp->fRec77[0])) + (dsp->fConst299 * dsp->fRec77[2]))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec76[0]))));
			dsp->fRec89[0] = (fTemp136 - (dsp->fConst316 * ((dsp->fConst319 * dsp->fRec89[2]) + (dsp->fConst320 * dsp->fRec89[1]))));
			dsp->fRec88[0] = ((dsp->fConst316 * (((dsp->fConst318 * dsp->fRec89[1]) + (dsp->fConst321 * dsp->fRec89[0])) + (dsp->fConst321 * dsp->fRec89[2]))) - (dsp->fConst314 * ((dsp->fConst322 * dsp->fRec88[2]) + (dsp->fConst323 * dsp->fRec88[1]))));
			dsp->fRec87[0] = ((dsp->fConst314 * (((dsp->fConst315 * dsp->fRec88[1]) + (dsp->fConst324 * dsp->fRec88[0])) + (dsp->fConst324 * dsp->fRec88[2]))) - (dsp->fConst312 * ((dsp->fConst325 * dsp->fRec87[2]) + (dsp->fConst326 * dsp->fRec87[1]))));
			float fTemp137 = (dsp->fConst312 * (((dsp->fConst313 * dsp->fRec87[1]) + (dsp->fConst327 * dsp->fRec87[0])) + (dsp->fConst327 * dsp->fRec87[2])));
			dsp->fRec86[0] = (fTemp137 - (dsp->fConst309 * ((dsp->fConst328 * dsp->fRec86[2]) + (dsp->fConst330 * dsp->fRec86[1]))));
			dsp->fRec85[0] = ((dsp->fConst309 * (((dsp->fConst311 * dsp->fRec86[1]) + (dsp->fConst331 * dsp->fRec86[0])) + (dsp->fConst331 * dsp->fRec86[2]))) - (dsp->fConst306 * ((dsp->fConst332 * dsp->fRec85[2]) + (dsp->fConst333 * dsp->fRec85[1]))));
			dsp->fRec84[0] = ((dsp->fConst306 * (((dsp->fConst308 * dsp->fRec85[1]) + (dsp->fConst334 * dsp->fRec85[0])) + (dsp->fConst334 * dsp->fRec85[2]))) - (dsp->fConst302 * ((dsp->fConst335 * dsp->fRec84[2]) + (dsp->fConst336 * dsp->fRec84[1]))));
			dsp->fRec83[0] = ((fSlow1 * dsp->fRec83[1]) + (fSlow2 * fabsf((dsp->fConst302 * (((dsp->fConst305 * dsp->fRec84[1]) + (dsp->fConst337 * dsp->fRec84[0])) + (dsp->fConst337 * dsp->fRec84[2]))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec83[0]))));
			dsp->fRec96[0] = (fTemp137 - (dsp->fConst354 * ((dsp->fConst357 * dsp->fRec96[2]) + (dsp->fConst358 * dsp->fRec96[1]))));
			dsp->fRec95[0] = ((dsp->fConst354 * (((dsp->fConst356 * dsp->fRec96[1]) + (dsp->fConst359 * dsp->fRec96[0])) + (dsp->fConst359 * dsp->fRec96[2]))) - (dsp->fConst352 * ((dsp->fConst360 * dsp->fRec95[2]) + (dsp->fConst361 * dsp->fRec95[1]))));
			dsp->fRec94[0] = ((dsp->fConst352 * (((dsp->fConst353 * dsp->fRec95[1]) + (dsp->fConst362 * dsp->fRec95[0])) + (dsp->fConst362 * dsp->fRec95[2]))) - (dsp->fConst350 * ((dsp->fConst363 * dsp->fRec94[2]) + (dsp->fConst364 * dsp->fRec94[1]))));
			float fTemp138 = (dsp->fConst350 * (((dsp->fConst351 * dsp->fRec94[1]) + (dsp->fConst365 * dsp->fRec94[0])) + (dsp->fConst365 * dsp->fRec94[2])));
			dsp->fRec93[0] = (fTemp138 - (dsp->fConst347 * ((dsp->fConst366 * dsp->fRec93[2]) + (dsp->fConst368 * dsp->fRec93[1]))));
			dsp->fRec92[0] = ((dsp->fConst347 * (((dsp->fConst349 * dsp->fRec93[1]) + (dsp->fConst369 * dsp->fRec93[0])) + (dsp->fConst369 * dsp->fRec93[2]))) - (dsp->fConst344 * ((dsp->fConst370 * dsp->fRec92[2]) + (dsp->fConst371 * dsp->fRec92[1]))));
			dsp->fRec91[0] = ((dsp->fConst344 * (((dsp->fConst346 * dsp->fRec92[1]) + (dsp->fConst372 * dsp->fRec92[0])) + (dsp->fConst372 * dsp->fRec92[2]))) - (dsp->fConst340 * ((dsp->fConst373 * dsp->fRec91[2]) + (dsp->fConst374 * dsp->fRec91[1]))));
			dsp->fRec90[0] = ((fSlow1 * dsp->fRec90[1]) + (fSlow2 * fabsf((dsp->fConst340 * (((dsp->fConst343 * dsp->fRec91[1]) + (dsp->fConst375 * dsp->fRec91[0])) + (dsp->fConst375 * dsp->fRec91[2]))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec90[0]))));
			dsp->fRec103[0] = (fTemp138 - (dsp->fConst392 * ((dsp->fConst395 * dsp->fRec103[2]) + (dsp->fConst396 * dsp->fRec103[1]))));
			dsp->fRec102[0] = ((dsp->fConst392 * (((dsp->fConst394 * dsp->fRec103[1]) + (dsp->fConst397 * dsp->fRec103[0])) + (dsp->fConst397 * dsp->fRec103[2]))) - (dsp->fConst390 * ((dsp->fConst398 * dsp->fRec102[2]) + (dsp->fConst399 * dsp->fRec102[1]))));
			dsp->fRec101[0] = ((dsp->fConst390 * (((dsp->fConst391 * dsp->fRec102[1]) + (dsp->fConst400 * dsp->fRec102[0])) + (dsp->fConst400 * dsp->fRec102[2]))) - (dsp->fConst388 * ((dsp->fConst401 * dsp->fRec101[2]) + (dsp->fConst402 * dsp->fRec101[1]))));
			float fTemp139 = (dsp->fConst388 * (((dsp->fConst389 * dsp->fRec101[1]) + (dsp->fConst403 * dsp->fRec101[0])) + (dsp->fConst403 * dsp->fRec101[2])));
			dsp->fRec100[0] = (fTemp139 - (dsp->fConst385 * ((dsp->fConst404 * dsp->fRec100[2]) + (dsp->fConst406 * dsp->fRec100[1]))));
			dsp->fRec99[0] = ((dsp->fConst385 * (((dsp->fConst387 * dsp->fRec100[1]) + (dsp->fConst407 * dsp->fRec100[0])) + (dsp->fConst407 * dsp->fRec100[2]))) - (dsp->fConst382 * ((dsp->fConst408 * dsp->fRec99[2]) + (dsp->fConst409 * dsp->fRec99[1]))));
			dsp->fRec98[0] = ((dsp->fConst382 * (((dsp->fConst384 * dsp->fRec99[1]) + (dsp->fConst410 * dsp->fRec99[0])) + (dsp->fConst410 * dsp->fRec99[2]))) - (dsp->fConst378 * ((dsp->fConst411 * dsp->fRec98[2]) + (dsp->fConst412 * dsp->fRec98[1]))));
			dsp->fRec97[0] = ((fSlow1 * dsp->fRec97[1]) + (fSlow2 * fabsf((dsp->fConst378 * (((dsp->fConst381 * dsp->fRec98[1]) + (dsp->fConst413 * dsp->fRec98[0])) + (dsp->fConst413 * dsp->fRec98[2]))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec97[0]))));
			dsp->fRec110[0] = (fTemp139 - (dsp->fConst430 * ((dsp->fConst433 * dsp->fRec110[2]) + (dsp->fConst434 * dsp->fRec110[1]))));
			dsp->fRec109[0] = ((dsp->fConst430 * (((dsp->fConst432 * dsp->fRec110[1]) + (dsp->fConst435 * dsp->fRec110[0])) + (dsp->fConst435 * dsp->fRec110[2]))) - (dsp->fConst428 * ((dsp->fConst436 * dsp->fRec109[2]) + (dsp->fConst437 * dsp->fRec109[1]))));
			dsp->fRec108[0] = ((dsp->fConst428 * (((dsp->fConst429 * dsp->fRec109[1]) + (dsp->fConst438 * dsp->fRec109[0])) + (dsp->fConst438 * dsp->fRec109[2]))) - (dsp->fConst426 * ((dsp->fConst439 * dsp->fRec108[2]) + (dsp->fConst440 * dsp->fRec108[1]))));
			float fTemp140 = (dsp->fConst426 * (((dsp->fConst427 * dsp->fRec108[1]) + (dsp->fConst441 * dsp->fRec108[0])) + (dsp->fConst441 * dsp->fRec108[2])));
			dsp->fRec107[0] = (fTemp140 - (dsp->fConst423 * ((dsp->fConst442 * dsp->fRec107[2]) + (dsp->fConst444 * dsp->fRec107[1]))));
			dsp->fRec106[0] = ((dsp->fConst423 * (((dsp->fConst425 * dsp->fRec107[1]) + (dsp->fConst445 * dsp->fRec107[0])) + (dsp->fConst445 * dsp->fRec107[2]))) - (dsp->fConst420 * ((dsp->fConst446 * dsp->fRec106[2]) + (dsp->fConst447 * dsp->fRec106[1]))));
			dsp->fRec105[0] = ((dsp->fConst420 * (((dsp->fConst422 * dsp->fRec106[1]) + (dsp->fConst448 * dsp->fRec106[0])) + (dsp->fConst448 * dsp->fRec106[2]))) - (dsp->fConst416 * ((dsp->fConst449 * dsp->fRec105[2]) + (dsp->fConst450 * dsp->fRec105[1]))));
			dsp->fRec104[0] = ((fSlow1 * dsp->fRec104[1]) + (fSlow2 * fabsf((dsp->fConst416 * (((dsp->fConst419 * dsp->fRec105[1]) + (dsp->fConst451 * dsp->fRec105[0])) + (dsp->fConst451 * dsp->fRec105[2]))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec104[0]))));
			dsp->fRec117[0] = (fTemp140 - (dsp->fConst468 * ((dsp->fConst471 * dsp->fRec117[2]) + (dsp->fConst472 * dsp->fRec117[1]))));
			dsp->fRec116[0] = ((dsp->fConst468 * (((dsp->fConst470 * dsp->fRec117[1]) + (dsp->fConst473 * dsp->fRec117[0])) + (dsp->fConst473 * dsp->fRec117[2]))) - (dsp->fConst466 * ((dsp->fConst474 * dsp->fRec116[2]) + (dsp->fConst475 * dsp->fRec116[1]))));
			dsp->fRec115[0] = ((dsp->fConst466 * (((dsp->fConst467 * dsp->fRec116[1]) + (dsp->fConst476 * dsp->fRec116[0])) + (dsp->fConst476 * dsp->fRec116[2]))) - (dsp->fConst464 * ((dsp->fConst477 * dsp->fRec115[2]) + (dsp->fConst478 * dsp->fRec115[1]))));
			float fTemp141 = (dsp->fConst464 * (((dsp->fConst465 * dsp->fRec115[1]) + (dsp->fConst479 * dsp->fRec115[0])) + (dsp->fConst479 * dsp->fRec115[2])));
			dsp->fRec114[0] = (fTemp141 - (dsp->fConst461 * ((dsp->fConst480 * dsp->fRec114[2]) + (dsp->fConst482 * dsp->fRec114[1]))));
			dsp->fRec113[0] = ((dsp->fConst461 * (((dsp->fConst463 * dsp->fRec114[1]) + (dsp->fConst483 * dsp->fRec114[0])) + (dsp->fConst483 * dsp->fRec114[2]))) - (dsp->fConst458 * ((dsp->fConst484 * dsp->fRec113[2]) + (dsp->fConst485 * dsp->fRec113[1]))));
			dsp->fRec112[0] = ((dsp->fConst458 * (((dsp->fConst460 * dsp->fRec113[1]) + (dsp->fConst486 * dsp->fRec113[0])) + (dsp->fConst486 * dsp->fRec113[2]))) - (dsp->fConst454 * ((dsp->fConst487 * dsp->fRec112[2]) + (dsp->fConst488 * dsp->fRec112[1]))));
			dsp->fRec111[0] = ((fSlow1 * dsp->fRec111[1]) + (fSlow2 * fabsf((dsp->fConst454 * (((dsp->fConst457 * dsp->fRec112[1]) + (dsp->fConst489 * dsp->fRec112[0])) + (dsp->fConst489 * dsp->fRec112[2]))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec111[0]))));
			dsp->fRec124[0] = (fTemp141 - (dsp->fConst506 * ((dsp->fConst509 * dsp->fRec124[2]) + (dsp->fConst510 * dsp->fRec124[1]))));
			dsp->fRec123[0] = ((dsp->fConst506 * (((dsp->fConst508 * dsp->fRec124[1]) + (dsp->fConst511 * dsp->fRec124[0])) + (dsp->fConst511 * dsp->fRec124[2]))) - (dsp->fConst504 * ((dsp->fConst512 * dsp->fRec123[2]) + (dsp->fConst513 * dsp->fRec123[1]))));
			dsp->fRec122[0] = ((dsp->fConst504 * (((dsp->fConst505 * dsp->fRec123[1]) + (dsp->fConst514 * dsp->fRec123[0])) + (dsp->fConst514 * dsp->fRec123[2]))) - (dsp->fConst502 * ((dsp->fConst515 * dsp->fRec122[2]) + (dsp->fConst516 * dsp->fRec122[1]))));
			float fTemp142 = (dsp->fConst502 * (((dsp->fConst503 * dsp->fRec122[1]) + (dsp->fConst517 * dsp->fRec122[0])) + (dsp->fConst517 * dsp->fRec122[2])));
			dsp->fRec121[0] = (fTemp142 - (dsp->fConst499 * ((dsp->fConst518 * dsp->fRec121[2]) + (dsp->fConst520 * dsp->fRec121[1]))));
			dsp->fRec120[0] = ((dsp->fConst499 * (((dsp->fConst501 * dsp->fRec121[1]) + (dsp->fConst521 * dsp->fRec121[0])) + (dsp->fConst521 * dsp->fRec121[2]))) - (dsp->fConst496 * ((dsp->fConst522 * dsp->fRec120[2]) + (dsp->fConst523 * dsp->fRec120[1]))));
			dsp->fRec119[0] = ((dsp->fConst496 * (((dsp->fConst498 * dsp->fRec120[1]) + (dsp->fConst524 * dsp->fRec120[0])) + (dsp->fConst524 * dsp->fRec120[2]))) - (dsp->fConst492 * ((dsp->fConst525 * dsp->fRec119[2]) + (dsp->fConst526 * dsp->fRec119[1]))));
			dsp->fRec118[0] = ((fSlow1 * dsp->fRec118[1]) + (fSlow2 * fabsf((dsp->fConst492 * (((dsp->fConst495 * dsp->fRec119[1]) + (dsp->fConst527 * dsp->fRec119[0])) + (dsp->fConst527 * dsp->fRec119[2]))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec118[0]))));
			dsp->fRec128[0] = (fTemp142 - (dsp->fConst532 * ((dsp->fConst535 * dsp->fRec128[2]) + (dsp->fConst536 * dsp->fRec128[1]))));
			dsp->fRec127[0] = ((dsp->fConst532 * (((dsp->fConst534 * dsp->fRec128[1]) + (dsp->fConst537 * dsp->fRec128[0])) + (dsp->fConst537 * dsp->fRec128[2]))) - (dsp->fConst530 * ((dsp->fConst538 * dsp->fRec127[2]) + (dsp->fConst539 * dsp->fRec127[1]))));
			dsp->fRec126[0] = ((dsp->fConst530 * (((dsp->fConst531 * dsp->fRec127[1]) + (dsp->fConst540 * dsp->fRec127[0])) + (dsp->fConst540 * dsp->fRec127[2]))) - (dsp->fConst528 * ((dsp->fConst541 * dsp->fRec126[2]) + (dsp->fConst542 * dsp->fRec126[1]))));
			dsp->fRec125[0] = ((fSlow1 * dsp->fRec125[1]) + (fSlow2 * fabsf((dsp->fConst528 * (((dsp->fConst529 * dsp->fRec126[1]) + (dsp->fConst543 * dsp->fRec126[0])) + (dsp->fConst543 * dsp->fRec126[2]))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec125[0]))));
			output0[i] = (FAUSTFLOAT)fTemp129;
			output1[i] = (FAUSTFLOAT)fTemp129;
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->fVec22[1] = dsp->fVec22[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fVec23[1] = dsp->fVec23[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fVec25[1] = dsp->fVec25[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fVec26[1] = dsp->fVec26[0];
			dsp->fVec28[1] = dsp->fVec28[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fVec29[1] = dsp->fVec29[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fVec31[1] = dsp->fVec31[0];
			dsp->fVec32[1] = dsp->fVec32[0];
			dsp->fVec34[1] = dsp->fVec34[0];
			dsp->fVec35[1] = dsp->fVec35[0];
			dsp->fVec37[1] = dsp->fVec37[0];
			dsp->fVec38[1] = dsp->fVec38[0];
			dsp->iRec23[1] = dsp->iRec23[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec22[j1] = dsp->fRec22[(j1 - 1)];
					
				}
				
			}
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
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
			dsp->fRec124[2] = dsp->fRec124[1];
			dsp->fRec124[1] = dsp->fRec124[0];
			dsp->fRec123[2] = dsp->fRec123[1];
			dsp->fRec123[1] = dsp->fRec123[0];
			dsp->fRec122[2] = dsp->fRec122[1];
			dsp->fRec122[1] = dsp->fRec122[0];
			dsp->fRec121[2] = dsp->fRec121[1];
			dsp->fRec121[1] = dsp->fRec121[0];
			dsp->fRec120[2] = dsp->fRec120[1];
			dsp->fRec120[1] = dsp->fRec120[0];
			dsp->fRec119[2] = dsp->fRec119[1];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec118[1] = dsp->fRec118[0];
			dsp->fRec128[2] = dsp->fRec128[1];
			dsp->fRec128[1] = dsp->fRec128[0];
			dsp->fRec127[2] = dsp->fRec127[1];
			dsp->fRec127[1] = dsp->fRec127[0];
			dsp->fRec126[2] = dsp->fRec126[1];
			dsp->fRec126[1] = dsp->fRec126[0];
			dsp->fRec125[1] = dsp->fRec125[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
