/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "spectralLevel"
version: "0.0"
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
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec3[3];
	float fConst17;
	float fConst18;
	float fConst19;
	float fRec2[3];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec1[3];
	float fConst23;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
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
	float fRec10[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec9[3];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec8[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec7[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec6[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec5[3];
	float fConst61;
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
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
	float fRec17[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec16[3];
	float fConst86;
	float fConst87;
	float fConst88;
	float fRec15[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec14[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec13[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec12[3];
	float fConst99;
	float fRec11[2];
	FAUSTFLOAT fVbargraph2;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
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
	float fRec24[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec23[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec22[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec21[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec20[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec19[3];
	float fConst137;
	float fRec18[2];
	FAUSTFLOAT fVbargraph3;
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
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
	float fRec31[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec30[3];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec29[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec28[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec27[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec26[3];
	float fConst175;
	float fRec25[2];
	FAUSTFLOAT fVbargraph4;
	float fConst176;
	float fConst177;
	float fConst178;
	float fConst179;
	float fConst180;
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
	float fRec38[3];
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec37[3];
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec36[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec35[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec34[3];
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec33[3];
	float fConst213;
	float fRec32[2];
	FAUSTFLOAT fVbargraph5;
	float fConst214;
	float fConst215;
	float fConst216;
	float fConst217;
	float fConst218;
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
	float fRec45[3];
	float fConst235;
	float fConst236;
	float fConst237;
	float fRec44[3];
	float fConst238;
	float fConst239;
	float fConst240;
	float fRec43[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fConst244;
	float fRec42[3];
	float fConst245;
	float fConst246;
	float fConst247;
	float fRec41[3];
	float fConst248;
	float fConst249;
	float fConst250;
	float fRec40[3];
	float fConst251;
	float fRec39[2];
	FAUSTFLOAT fVbargraph6;
	float fConst252;
	float fConst253;
	float fConst254;
	float fConst255;
	float fConst256;
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
	float fRec52[3];
	float fConst273;
	float fConst274;
	float fConst275;
	float fRec51[3];
	float fConst276;
	float fConst277;
	float fConst278;
	float fRec50[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fConst282;
	float fRec49[3];
	float fConst283;
	float fConst284;
	float fConst285;
	float fRec48[3];
	float fConst286;
	float fConst287;
	float fConst288;
	float fRec47[3];
	float fConst289;
	float fRec46[2];
	FAUSTFLOAT fVbargraph7;
	float fConst290;
	float fConst291;
	float fConst292;
	float fConst293;
	float fConst294;
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
	float fRec59[3];
	float fConst311;
	float fConst312;
	float fConst313;
	float fRec58[3];
	float fConst314;
	float fConst315;
	float fConst316;
	float fRec57[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fConst320;
	float fRec56[3];
	float fConst321;
	float fConst322;
	float fConst323;
	float fRec55[3];
	float fConst324;
	float fConst325;
	float fConst326;
	float fRec54[3];
	float fConst327;
	float fRec53[2];
	FAUSTFLOAT fVbargraph8;
	float fConst328;
	float fConst329;
	float fConst330;
	float fConst331;
	float fConst332;
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
	float fRec66[3];
	float fConst349;
	float fConst350;
	float fConst351;
	float fRec65[3];
	float fConst352;
	float fConst353;
	float fConst354;
	float fRec64[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fConst358;
	float fRec63[3];
	float fConst359;
	float fConst360;
	float fConst361;
	float fRec62[3];
	float fConst362;
	float fConst363;
	float fConst364;
	float fRec61[3];
	float fConst365;
	float fRec60[2];
	FAUSTFLOAT fVbargraph9;
	float fConst366;
	float fConst367;
	float fConst368;
	float fConst369;
	float fConst370;
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
	float fRec73[3];
	float fConst387;
	float fConst388;
	float fConst389;
	float fRec72[3];
	float fConst390;
	float fConst391;
	float fConst392;
	float fRec71[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fConst396;
	float fRec70[3];
	float fConst397;
	float fConst398;
	float fConst399;
	float fRec69[3];
	float fConst400;
	float fConst401;
	float fConst402;
	float fRec68[3];
	float fConst403;
	float fRec67[2];
	FAUSTFLOAT fVbargraph10;
	float fConst404;
	float fConst405;
	float fConst406;
	float fConst407;
	float fConst408;
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
	float fRec80[3];
	float fConst425;
	float fConst426;
	float fConst427;
	float fRec79[3];
	float fConst428;
	float fConst429;
	float fConst430;
	float fRec78[3];
	float fConst431;
	float fConst432;
	float fConst433;
	float fConst434;
	float fRec77[3];
	float fConst435;
	float fConst436;
	float fConst437;
	float fRec76[3];
	float fConst438;
	float fConst439;
	float fConst440;
	float fRec75[3];
	float fConst441;
	float fRec74[2];
	FAUSTFLOAT fVbargraph11;
	float fConst442;
	float fConst443;
	float fConst444;
	float fConst445;
	float fConst446;
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
	float fRec87[3];
	float fConst463;
	float fConst464;
	float fConst465;
	float fRec86[3];
	float fConst466;
	float fConst467;
	float fConst468;
	float fRec85[3];
	float fConst469;
	float fConst470;
	float fConst471;
	float fConst472;
	float fRec84[3];
	float fConst473;
	float fConst474;
	float fConst475;
	float fRec83[3];
	float fConst476;
	float fConst477;
	float fConst478;
	float fRec82[3];
	float fConst479;
	float fRec81[2];
	FAUSTFLOAT fVbargraph12;
	float fConst480;
	float fConst481;
	float fConst482;
	float fConst483;
	float fConst484;
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
	float fRec94[3];
	float fConst501;
	float fConst502;
	float fConst503;
	float fRec93[3];
	float fConst504;
	float fConst505;
	float fConst506;
	float fRec92[3];
	float fConst507;
	float fConst508;
	float fConst509;
	float fConst510;
	float fRec91[3];
	float fConst511;
	float fConst512;
	float fConst513;
	float fRec90[3];
	float fConst514;
	float fConst515;
	float fConst516;
	float fRec89[3];
	float fConst517;
	float fRec88[2];
	FAUSTFLOAT fVbargraph13;
	float fConst518;
	float fConst519;
	float fConst520;
	float fConst521;
	float fConst522;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fRec98[3];
	float fConst527;
	float fConst528;
	float fConst529;
	float fRec97[3];
	float fConst530;
	float fConst531;
	float fConst532;
	float fRec96[3];
	float fConst533;
	float fRec95[2];
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
	m->declare(m->metaInterface, "author", "JOS, revised by RM");
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.0");
	m->declare(m->metaInterface, "description", "Demonstrates mth_octave_spectral_level in a standalone GUI.");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "spectralLevel");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
	m->declare(m->metaInterface, "version", "0.0");
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
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			dsp->fRec3[l0] = 0.0f;
			
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
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			dsp->fRec10[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			dsp->fRec9[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			dsp->fRec8[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			dsp->fRec7[l7] = 0.0f;
			
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
			dsp->fRec5[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec4[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			dsp->fRec17[l11] = 0.0f;
			
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
			dsp->fRec15[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			dsp->fRec14[l14] = 0.0f;
			
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
			dsp->fRec12[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec11[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			dsp->fRec24[l18] = 0.0f;
			
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
			dsp->fRec22[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			dsp->fRec21[l21] = 0.0f;
			
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
			dsp->fRec19[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fRec18[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			dsp->fRec31[l25] = 0.0f;
			
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
			dsp->fRec29[l27] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			dsp->fRec28[l28] = 0.0f;
			
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
			dsp->fRec26[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec25[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec38[l32] = 0.0f;
			
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
			dsp->fRec36[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec35[l35] = 0.0f;
			
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
			dsp->fRec33[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec32[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec45[l39] = 0.0f;
			
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
			dsp->fRec43[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			dsp->fRec42[l42] = 0.0f;
			
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
			dsp->fRec40[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fRec39[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			dsp->fRec52[l46] = 0.0f;
			
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
			dsp->fRec50[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec49[l49] = 0.0f;
			
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
			dsp->fRec47[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec46[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec59[l53] = 0.0f;
			
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
			dsp->fRec57[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			dsp->fRec56[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			dsp->fRec55[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec54[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec53[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			dsp->fRec66[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			dsp->fRec65[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec64[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec63[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec62[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec61[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			dsp->fRec60[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec73[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec72[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec71[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			dsp->fRec70[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			dsp->fRec69[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec68[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			dsp->fRec67[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			dsp->fRec80[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			dsp->fRec79[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec78[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			dsp->fRec77[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			dsp->fRec76[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec75[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			dsp->fRec74[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec87[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec86[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			dsp->fRec85[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			dsp->fRec84[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			dsp->fRec83[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec82[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fRec81[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			dsp->fRec94[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec93[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec92[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			dsp->fRec91[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			dsp->fRec90[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec89[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			dsp->fRec88[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			dsp->fRec98[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			dsp->fRec97[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			dsp->fRec96[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			dsp->fRec95[l98] = 0.0f;
			
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
	dsp->fConst14 = (((dsp->fConst3 + -3.18972731f) / dsp->fConst2) + 4.07678175f);
	dsp->fConst15 = (1.0f / dsp->fConst5);
	dsp->fConst16 = (2.0f * (4.07678175f - dsp->fConst15));
	dsp->fConst17 = (dsp->fConst12 + 0.000407678192f);
	dsp->fConst18 = (((dsp->fConst3 + -0.743130445f) / dsp->fConst2) + 1.4500711f);
	dsp->fConst19 = (2.0f * (1.4500711f - dsp->fConst15));
	dsp->fConst20 = (dsp->fConst9 + 1.4500711f);
	dsp->fConst21 = (((dsp->fConst3 + -0.157482162f) / dsp->fConst2) + 0.935140193f);
	dsp->fConst22 = (2.0f * (0.935140193f - dsp->fConst15));
	dsp->fConst23 = (dsp->fConst6 + 0.935140193f);
	dsp->fConst24 = tanf((31665.2695f / dsp->fConst0));
	dsp->fConst25 = (1.0f / dsp->fConst24);
	dsp->fConst26 = (1.0f / (((dsp->fConst25 + 0.157482162f) / dsp->fConst24) + 0.935140193f));
	dsp->fConst27 = mydsp_faustpower2_f(dsp->fConst24);
	dsp->fConst28 = (50.0638084f / dsp->fConst27);
	dsp->fConst29 = (2.0f * (0.935140193f - dsp->fConst28));
	dsp->fConst30 = (1.0f / (((dsp->fConst25 + 0.743130445f) / dsp->fConst24) + 1.4500711f));
	dsp->fConst31 = (11.0520525f / dsp->fConst27);
	dsp->fConst32 = (2.0f * (1.4500711f - dsp->fConst31));
	dsp->fConst33 = (1.0f / (((dsp->fConst25 + 3.18972731f) / dsp->fConst24) + 4.07678175f));
	dsp->fConst34 = (0.00176617282f / dsp->fConst27);
	dsp->fConst35 = (2.0f * (0.000407678192f - dsp->fConst34));
	dsp->fConst36 = (1.0f / (((dsp->fConst3 + 0.168404877f) / dsp->fConst2) + 1.06935835f));
	dsp->fConst37 = (2.0f * (53.5361519f - dsp->fConst15));
	dsp->fConst38 = (1.0f / (((dsp->fConst3 + 0.51247865f) / dsp->fConst2) + 0.689621389f));
	dsp->fConst39 = (2.0f * (7.62173128f - dsp->fConst15));
	dsp->fConst40 = (1.0f / (((dsp->fConst3 + 0.782413065f) / dsp->fConst2) + 0.245291501f));
	dsp->fConst41 = (9.99999975e-05f / dsp->fConst5);
	dsp->fConst42 = (2.0f * (0.000433227193f - dsp->fConst41));
	dsp->fConst43 = (((dsp->fConst3 + -0.782413065f) / dsp->fConst2) + 0.245291501f);
	dsp->fConst44 = (2.0f * (0.245291501f - dsp->fConst15));
	dsp->fConst45 = (dsp->fConst41 + 0.000433227193f);
	dsp->fConst46 = (((dsp->fConst3 + -0.51247865f) / dsp->fConst2) + 0.689621389f);
	dsp->fConst47 = (2.0f * (0.689621389f - dsp->fConst15));
	dsp->fConst48 = (dsp->fConst15 + 7.62173128f);
	dsp->fConst49 = (((dsp->fConst3 + -0.168404877f) / dsp->fConst2) + 1.06935835f);
	dsp->fConst50 = (2.0f * (1.06935835f - dsp->fConst15));
	dsp->fConst51 = (dsp->fConst15 + 53.5361519f);
	dsp->fConst52 = (((dsp->fConst25 + -3.18972731f) / dsp->fConst24) + 4.07678175f);
	dsp->fConst53 = (1.0f / dsp->fConst27);
	dsp->fConst54 = (2.0f * (4.07678175f - dsp->fConst53));
	dsp->fConst55 = (dsp->fConst34 + 0.000407678192f);
	dsp->fConst56 = (((dsp->fConst25 + -0.743130445f) / dsp->fConst24) + 1.4500711f);
	dsp->fConst57 = (2.0f * (1.4500711f - dsp->fConst53));
	dsp->fConst58 = (dsp->fConst31 + 1.4500711f);
	dsp->fConst59 = (((dsp->fConst25 + -0.157482162f) / dsp->fConst24) + 0.935140193f);
	dsp->fConst60 = (2.0f * (0.935140193f - dsp->fConst53));
	dsp->fConst61 = (dsp->fConst28 + 0.935140193f);
	dsp->fConst62 = tanf((19947.8691f / dsp->fConst0));
	dsp->fConst63 = (1.0f / dsp->fConst62);
	dsp->fConst64 = (1.0f / (((dsp->fConst63 + 0.157482162f) / dsp->fConst62) + 0.935140193f));
	dsp->fConst65 = mydsp_faustpower2_f(dsp->fConst62);
	dsp->fConst66 = (50.0638084f / dsp->fConst65);
	dsp->fConst67 = (2.0f * (0.935140193f - dsp->fConst66));
	dsp->fConst68 = (1.0f / (((dsp->fConst63 + 0.743130445f) / dsp->fConst62) + 1.4500711f));
	dsp->fConst69 = (11.0520525f / dsp->fConst65);
	dsp->fConst70 = (2.0f * (1.4500711f - dsp->fConst69));
	dsp->fConst71 = (1.0f / (((dsp->fConst63 + 3.18972731f) / dsp->fConst62) + 4.07678175f));
	dsp->fConst72 = (0.00176617282f / dsp->fConst65);
	dsp->fConst73 = (2.0f * (0.000407678192f - dsp->fConst72));
	dsp->fConst74 = (1.0f / (((dsp->fConst25 + 0.168404877f) / dsp->fConst24) + 1.06935835f));
	dsp->fConst75 = (2.0f * (53.5361519f - dsp->fConst53));
	dsp->fConst76 = (1.0f / (((dsp->fConst25 + 0.51247865f) / dsp->fConst24) + 0.689621389f));
	dsp->fConst77 = (2.0f * (7.62173128f - dsp->fConst53));
	dsp->fConst78 = (1.0f / (((dsp->fConst25 + 0.782413065f) / dsp->fConst24) + 0.245291501f));
	dsp->fConst79 = (9.99999975e-05f / dsp->fConst27);
	dsp->fConst80 = (2.0f * (0.000433227193f - dsp->fConst79));
	dsp->fConst81 = (((dsp->fConst25 + -0.782413065f) / dsp->fConst24) + 0.245291501f);
	dsp->fConst82 = (2.0f * (0.245291501f - dsp->fConst53));
	dsp->fConst83 = (dsp->fConst79 + 0.000433227193f);
	dsp->fConst84 = (((dsp->fConst25 + -0.51247865f) / dsp->fConst24) + 0.689621389f);
	dsp->fConst85 = (2.0f * (0.689621389f - dsp->fConst53));
	dsp->fConst86 = (dsp->fConst53 + 7.62173128f);
	dsp->fConst87 = (((dsp->fConst25 + -0.168404877f) / dsp->fConst24) + 1.06935835f);
	dsp->fConst88 = (2.0f * (1.06935835f - dsp->fConst53));
	dsp->fConst89 = (dsp->fConst53 + 53.5361519f);
	dsp->fConst90 = (((dsp->fConst63 + -3.18972731f) / dsp->fConst62) + 4.07678175f);
	dsp->fConst91 = (1.0f / dsp->fConst65);
	dsp->fConst92 = (2.0f * (4.07678175f - dsp->fConst91));
	dsp->fConst93 = (dsp->fConst72 + 0.000407678192f);
	dsp->fConst94 = (((dsp->fConst63 + -0.743130445f) / dsp->fConst62) + 1.4500711f);
	dsp->fConst95 = (2.0f * (1.4500711f - dsp->fConst91));
	dsp->fConst96 = (dsp->fConst69 + 1.4500711f);
	dsp->fConst97 = (((dsp->fConst63 + -0.157482162f) / dsp->fConst62) + 0.935140193f);
	dsp->fConst98 = (2.0f * (0.935140193f - dsp->fConst91));
	dsp->fConst99 = (dsp->fConst66 + 0.935140193f);
	dsp->fConst100 = tanf((12566.3711f / dsp->fConst0));
	dsp->fConst101 = (1.0f / dsp->fConst100);
	dsp->fConst102 = (1.0f / (((dsp->fConst101 + 0.157482162f) / dsp->fConst100) + 0.935140193f));
	dsp->fConst103 = mydsp_faustpower2_f(dsp->fConst100);
	dsp->fConst104 = (50.0638084f / dsp->fConst103);
	dsp->fConst105 = (2.0f * (0.935140193f - dsp->fConst104));
	dsp->fConst106 = (1.0f / (((dsp->fConst101 + 0.743130445f) / dsp->fConst100) + 1.4500711f));
	dsp->fConst107 = (11.0520525f / dsp->fConst103);
	dsp->fConst108 = (2.0f * (1.4500711f - dsp->fConst107));
	dsp->fConst109 = (1.0f / (((dsp->fConst101 + 3.18972731f) / dsp->fConst100) + 4.07678175f));
	dsp->fConst110 = (0.00176617282f / dsp->fConst103);
	dsp->fConst111 = (2.0f * (0.000407678192f - dsp->fConst110));
	dsp->fConst112 = (1.0f / (((dsp->fConst63 + 0.168404877f) / dsp->fConst62) + 1.06935835f));
	dsp->fConst113 = (2.0f * (53.5361519f - dsp->fConst91));
	dsp->fConst114 = (1.0f / (((dsp->fConst63 + 0.51247865f) / dsp->fConst62) + 0.689621389f));
	dsp->fConst115 = (2.0f * (7.62173128f - dsp->fConst91));
	dsp->fConst116 = (1.0f / (((dsp->fConst63 + 0.782413065f) / dsp->fConst62) + 0.245291501f));
	dsp->fConst117 = (9.99999975e-05f / dsp->fConst65);
	dsp->fConst118 = (2.0f * (0.000433227193f - dsp->fConst117));
	dsp->fConst119 = (((dsp->fConst63 + -0.782413065f) / dsp->fConst62) + 0.245291501f);
	dsp->fConst120 = (2.0f * (0.245291501f - dsp->fConst91));
	dsp->fConst121 = (dsp->fConst117 + 0.000433227193f);
	dsp->fConst122 = (((dsp->fConst63 + -0.51247865f) / dsp->fConst62) + 0.689621389f);
	dsp->fConst123 = (2.0f * (0.689621389f - dsp->fConst91));
	dsp->fConst124 = (dsp->fConst91 + 7.62173128f);
	dsp->fConst125 = (((dsp->fConst63 + -0.168404877f) / dsp->fConst62) + 1.06935835f);
	dsp->fConst126 = (2.0f * (1.06935835f - dsp->fConst91));
	dsp->fConst127 = (dsp->fConst91 + 53.5361519f);
	dsp->fConst128 = (((dsp->fConst101 + -3.18972731f) / dsp->fConst100) + 4.07678175f);
	dsp->fConst129 = (1.0f / dsp->fConst103);
	dsp->fConst130 = (2.0f * (4.07678175f - dsp->fConst129));
	dsp->fConst131 = (dsp->fConst110 + 0.000407678192f);
	dsp->fConst132 = (((dsp->fConst101 + -0.743130445f) / dsp->fConst100) + 1.4500711f);
	dsp->fConst133 = (2.0f * (1.4500711f - dsp->fConst129));
	dsp->fConst134 = (dsp->fConst107 + 1.4500711f);
	dsp->fConst135 = (((dsp->fConst101 + -0.157482162f) / dsp->fConst100) + 0.935140193f);
	dsp->fConst136 = (2.0f * (0.935140193f - dsp->fConst129));
	dsp->fConst137 = (dsp->fConst104 + 0.935140193f);
	dsp->fConst138 = tanf((7916.31738f / dsp->fConst0));
	dsp->fConst139 = (1.0f / dsp->fConst138);
	dsp->fConst140 = (1.0f / (((dsp->fConst139 + 0.157482162f) / dsp->fConst138) + 0.935140193f));
	dsp->fConst141 = mydsp_faustpower2_f(dsp->fConst138);
	dsp->fConst142 = (50.0638084f / dsp->fConst141);
	dsp->fConst143 = (2.0f * (0.935140193f - dsp->fConst142));
	dsp->fConst144 = (1.0f / (((dsp->fConst139 + 0.743130445f) / dsp->fConst138) + 1.4500711f));
	dsp->fConst145 = (11.0520525f / dsp->fConst141);
	dsp->fConst146 = (2.0f * (1.4500711f - dsp->fConst145));
	dsp->fConst147 = (1.0f / (((dsp->fConst139 + 3.18972731f) / dsp->fConst138) + 4.07678175f));
	dsp->fConst148 = (0.00176617282f / dsp->fConst141);
	dsp->fConst149 = (2.0f * (0.000407678192f - dsp->fConst148));
	dsp->fConst150 = (1.0f / (((dsp->fConst101 + 0.168404877f) / dsp->fConst100) + 1.06935835f));
	dsp->fConst151 = (2.0f * (53.5361519f - dsp->fConst129));
	dsp->fConst152 = (1.0f / (((dsp->fConst101 + 0.51247865f) / dsp->fConst100) + 0.689621389f));
	dsp->fConst153 = (2.0f * (7.62173128f - dsp->fConst129));
	dsp->fConst154 = (1.0f / (((dsp->fConst101 + 0.782413065f) / dsp->fConst100) + 0.245291501f));
	dsp->fConst155 = (9.99999975e-05f / dsp->fConst103);
	dsp->fConst156 = (2.0f * (0.000433227193f - dsp->fConst155));
	dsp->fConst157 = (((dsp->fConst101 + -0.782413065f) / dsp->fConst100) + 0.245291501f);
	dsp->fConst158 = (2.0f * (0.245291501f - dsp->fConst129));
	dsp->fConst159 = (dsp->fConst155 + 0.000433227193f);
	dsp->fConst160 = (((dsp->fConst101 + -0.51247865f) / dsp->fConst100) + 0.689621389f);
	dsp->fConst161 = (2.0f * (0.689621389f - dsp->fConst129));
	dsp->fConst162 = (dsp->fConst129 + 7.62173128f);
	dsp->fConst163 = (((dsp->fConst101 + -0.168404877f) / dsp->fConst100) + 1.06935835f);
	dsp->fConst164 = (2.0f * (1.06935835f - dsp->fConst129));
	dsp->fConst165 = (dsp->fConst129 + 53.5361519f);
	dsp->fConst166 = (((dsp->fConst139 + -3.18972731f) / dsp->fConst138) + 4.07678175f);
	dsp->fConst167 = (1.0f / dsp->fConst141);
	dsp->fConst168 = (2.0f * (4.07678175f - dsp->fConst167));
	dsp->fConst169 = (dsp->fConst148 + 0.000407678192f);
	dsp->fConst170 = (((dsp->fConst139 + -0.743130445f) / dsp->fConst138) + 1.4500711f);
	dsp->fConst171 = (2.0f * (1.4500711f - dsp->fConst167));
	dsp->fConst172 = (dsp->fConst145 + 1.4500711f);
	dsp->fConst173 = (((dsp->fConst139 + -0.157482162f) / dsp->fConst138) + 0.935140193f);
	dsp->fConst174 = (2.0f * (0.935140193f - dsp->fConst167));
	dsp->fConst175 = (dsp->fConst142 + 0.935140193f);
	dsp->fConst176 = tanf((4986.96729f / dsp->fConst0));
	dsp->fConst177 = (1.0f / dsp->fConst176);
	dsp->fConst178 = (1.0f / (((dsp->fConst177 + 0.157482162f) / dsp->fConst176) + 0.935140193f));
	dsp->fConst179 = mydsp_faustpower2_f(dsp->fConst176);
	dsp->fConst180 = (50.0638084f / dsp->fConst179);
	dsp->fConst181 = (2.0f * (0.935140193f - dsp->fConst180));
	dsp->fConst182 = (1.0f / (((dsp->fConst177 + 0.743130445f) / dsp->fConst176) + 1.4500711f));
	dsp->fConst183 = (11.0520525f / dsp->fConst179);
	dsp->fConst184 = (2.0f * (1.4500711f - dsp->fConst183));
	dsp->fConst185 = (1.0f / (((dsp->fConst177 + 3.18972731f) / dsp->fConst176) + 4.07678175f));
	dsp->fConst186 = (0.00176617282f / dsp->fConst179);
	dsp->fConst187 = (2.0f * (0.000407678192f - dsp->fConst186));
	dsp->fConst188 = (1.0f / (((dsp->fConst139 + 0.168404877f) / dsp->fConst138) + 1.06935835f));
	dsp->fConst189 = (2.0f * (53.5361519f - dsp->fConst167));
	dsp->fConst190 = (1.0f / (((dsp->fConst139 + 0.51247865f) / dsp->fConst138) + 0.689621389f));
	dsp->fConst191 = (2.0f * (7.62173128f - dsp->fConst167));
	dsp->fConst192 = (1.0f / (((dsp->fConst139 + 0.782413065f) / dsp->fConst138) + 0.245291501f));
	dsp->fConst193 = (9.99999975e-05f / dsp->fConst141);
	dsp->fConst194 = (2.0f * (0.000433227193f - dsp->fConst193));
	dsp->fConst195 = (((dsp->fConst139 + -0.782413065f) / dsp->fConst138) + 0.245291501f);
	dsp->fConst196 = (2.0f * (0.245291501f - dsp->fConst167));
	dsp->fConst197 = (dsp->fConst193 + 0.000433227193f);
	dsp->fConst198 = (((dsp->fConst139 + -0.51247865f) / dsp->fConst138) + 0.689621389f);
	dsp->fConst199 = (2.0f * (0.689621389f - dsp->fConst167));
	dsp->fConst200 = (dsp->fConst167 + 7.62173128f);
	dsp->fConst201 = (((dsp->fConst139 + -0.168404877f) / dsp->fConst138) + 1.06935835f);
	dsp->fConst202 = (2.0f * (1.06935835f - dsp->fConst167));
	dsp->fConst203 = (dsp->fConst167 + 53.5361519f);
	dsp->fConst204 = (((dsp->fConst177 + -3.18972731f) / dsp->fConst176) + 4.07678175f);
	dsp->fConst205 = (1.0f / dsp->fConst179);
	dsp->fConst206 = (2.0f * (4.07678175f - dsp->fConst205));
	dsp->fConst207 = (dsp->fConst186 + 0.000407678192f);
	dsp->fConst208 = (((dsp->fConst177 + -0.743130445f) / dsp->fConst176) + 1.4500711f);
	dsp->fConst209 = (2.0f * (1.4500711f - dsp->fConst205));
	dsp->fConst210 = (dsp->fConst183 + 1.4500711f);
	dsp->fConst211 = (((dsp->fConst177 + -0.157482162f) / dsp->fConst176) + 0.935140193f);
	dsp->fConst212 = (2.0f * (0.935140193f - dsp->fConst205));
	dsp->fConst213 = (dsp->fConst180 + 0.935140193f);
	dsp->fConst214 = tanf((3141.59277f / dsp->fConst0));
	dsp->fConst215 = (1.0f / dsp->fConst214);
	dsp->fConst216 = (1.0f / (((dsp->fConst215 + 0.157482162f) / dsp->fConst214) + 0.935140193f));
	dsp->fConst217 = mydsp_faustpower2_f(dsp->fConst214);
	dsp->fConst218 = (50.0638084f / dsp->fConst217);
	dsp->fConst219 = (2.0f * (0.935140193f - dsp->fConst218));
	dsp->fConst220 = (1.0f / (((dsp->fConst215 + 0.743130445f) / dsp->fConst214) + 1.4500711f));
	dsp->fConst221 = (11.0520525f / dsp->fConst217);
	dsp->fConst222 = (2.0f * (1.4500711f - dsp->fConst221));
	dsp->fConst223 = (1.0f / (((dsp->fConst215 + 3.18972731f) / dsp->fConst214) + 4.07678175f));
	dsp->fConst224 = (0.00176617282f / dsp->fConst217);
	dsp->fConst225 = (2.0f * (0.000407678192f - dsp->fConst224));
	dsp->fConst226 = (1.0f / (((dsp->fConst177 + 0.168404877f) / dsp->fConst176) + 1.06935835f));
	dsp->fConst227 = (2.0f * (53.5361519f - dsp->fConst205));
	dsp->fConst228 = (1.0f / (((dsp->fConst177 + 0.51247865f) / dsp->fConst176) + 0.689621389f));
	dsp->fConst229 = (2.0f * (7.62173128f - dsp->fConst205));
	dsp->fConst230 = (1.0f / (((dsp->fConst177 + 0.782413065f) / dsp->fConst176) + 0.245291501f));
	dsp->fConst231 = (9.99999975e-05f / dsp->fConst179);
	dsp->fConst232 = (2.0f * (0.000433227193f - dsp->fConst231));
	dsp->fConst233 = (((dsp->fConst177 + -0.782413065f) / dsp->fConst176) + 0.245291501f);
	dsp->fConst234 = (2.0f * (0.245291501f - dsp->fConst205));
	dsp->fConst235 = (dsp->fConst231 + 0.000433227193f);
	dsp->fConst236 = (((dsp->fConst177 + -0.51247865f) / dsp->fConst176) + 0.689621389f);
	dsp->fConst237 = (2.0f * (0.689621389f - dsp->fConst205));
	dsp->fConst238 = (dsp->fConst205 + 7.62173128f);
	dsp->fConst239 = (((dsp->fConst177 + -0.168404877f) / dsp->fConst176) + 1.06935835f);
	dsp->fConst240 = (2.0f * (1.06935835f - dsp->fConst205));
	dsp->fConst241 = (dsp->fConst205 + 53.5361519f);
	dsp->fConst242 = (((dsp->fConst215 + -3.18972731f) / dsp->fConst214) + 4.07678175f);
	dsp->fConst243 = (1.0f / dsp->fConst217);
	dsp->fConst244 = (2.0f * (4.07678175f - dsp->fConst243));
	dsp->fConst245 = (dsp->fConst224 + 0.000407678192f);
	dsp->fConst246 = (((dsp->fConst215 + -0.743130445f) / dsp->fConst214) + 1.4500711f);
	dsp->fConst247 = (2.0f * (1.4500711f - dsp->fConst243));
	dsp->fConst248 = (dsp->fConst221 + 1.4500711f);
	dsp->fConst249 = (((dsp->fConst215 + -0.157482162f) / dsp->fConst214) + 0.935140193f);
	dsp->fConst250 = (2.0f * (0.935140193f - dsp->fConst243));
	dsp->fConst251 = (dsp->fConst218 + 0.935140193f);
	dsp->fConst252 = tanf((1979.07935f / dsp->fConst0));
	dsp->fConst253 = (1.0f / dsp->fConst252);
	dsp->fConst254 = (1.0f / (((dsp->fConst253 + 0.157482162f) / dsp->fConst252) + 0.935140193f));
	dsp->fConst255 = mydsp_faustpower2_f(dsp->fConst252);
	dsp->fConst256 = (50.0638084f / dsp->fConst255);
	dsp->fConst257 = (2.0f * (0.935140193f - dsp->fConst256));
	dsp->fConst258 = (1.0f / (((dsp->fConst253 + 0.743130445f) / dsp->fConst252) + 1.4500711f));
	dsp->fConst259 = (11.0520525f / dsp->fConst255);
	dsp->fConst260 = (2.0f * (1.4500711f - dsp->fConst259));
	dsp->fConst261 = (1.0f / (((dsp->fConst253 + 3.18972731f) / dsp->fConst252) + 4.07678175f));
	dsp->fConst262 = (0.00176617282f / dsp->fConst255);
	dsp->fConst263 = (2.0f * (0.000407678192f - dsp->fConst262));
	dsp->fConst264 = (1.0f / (((dsp->fConst215 + 0.168404877f) / dsp->fConst214) + 1.06935835f));
	dsp->fConst265 = (2.0f * (53.5361519f - dsp->fConst243));
	dsp->fConst266 = (1.0f / (((dsp->fConst215 + 0.51247865f) / dsp->fConst214) + 0.689621389f));
	dsp->fConst267 = (2.0f * (7.62173128f - dsp->fConst243));
	dsp->fConst268 = (1.0f / (((dsp->fConst215 + 0.782413065f) / dsp->fConst214) + 0.245291501f));
	dsp->fConst269 = (9.99999975e-05f / dsp->fConst217);
	dsp->fConst270 = (2.0f * (0.000433227193f - dsp->fConst269));
	dsp->fConst271 = (((dsp->fConst215 + -0.782413065f) / dsp->fConst214) + 0.245291501f);
	dsp->fConst272 = (2.0f * (0.245291501f - dsp->fConst243));
	dsp->fConst273 = (dsp->fConst269 + 0.000433227193f);
	dsp->fConst274 = (((dsp->fConst215 + -0.51247865f) / dsp->fConst214) + 0.689621389f);
	dsp->fConst275 = (2.0f * (0.689621389f - dsp->fConst243));
	dsp->fConst276 = (dsp->fConst243 + 7.62173128f);
	dsp->fConst277 = (((dsp->fConst215 + -0.168404877f) / dsp->fConst214) + 1.06935835f);
	dsp->fConst278 = (2.0f * (1.06935835f - dsp->fConst243));
	dsp->fConst279 = (dsp->fConst243 + 53.5361519f);
	dsp->fConst280 = (((dsp->fConst253 + -3.18972731f) / dsp->fConst252) + 4.07678175f);
	dsp->fConst281 = (1.0f / dsp->fConst255);
	dsp->fConst282 = (2.0f * (4.07678175f - dsp->fConst281));
	dsp->fConst283 = (dsp->fConst262 + 0.000407678192f);
	dsp->fConst284 = (((dsp->fConst253 + -0.743130445f) / dsp->fConst252) + 1.4500711f);
	dsp->fConst285 = (2.0f * (1.4500711f - dsp->fConst281));
	dsp->fConst286 = (dsp->fConst259 + 1.4500711f);
	dsp->fConst287 = (((dsp->fConst253 + -0.157482162f) / dsp->fConst252) + 0.935140193f);
	dsp->fConst288 = (2.0f * (0.935140193f - dsp->fConst281));
	dsp->fConst289 = (dsp->fConst256 + 0.935140193f);
	dsp->fConst290 = tanf((1246.74182f / dsp->fConst0));
	dsp->fConst291 = (1.0f / dsp->fConst290);
	dsp->fConst292 = (1.0f / (((dsp->fConst291 + 0.157482162f) / dsp->fConst290) + 0.935140193f));
	dsp->fConst293 = mydsp_faustpower2_f(dsp->fConst290);
	dsp->fConst294 = (50.0638084f / dsp->fConst293);
	dsp->fConst295 = (2.0f * (0.935140193f - dsp->fConst294));
	dsp->fConst296 = (1.0f / (((dsp->fConst291 + 0.743130445f) / dsp->fConst290) + 1.4500711f));
	dsp->fConst297 = (11.0520525f / dsp->fConst293);
	dsp->fConst298 = (2.0f * (1.4500711f - dsp->fConst297));
	dsp->fConst299 = (1.0f / (((dsp->fConst291 + 3.18972731f) / dsp->fConst290) + 4.07678175f));
	dsp->fConst300 = (0.00176617282f / dsp->fConst293);
	dsp->fConst301 = (2.0f * (0.000407678192f - dsp->fConst300));
	dsp->fConst302 = (1.0f / (((dsp->fConst253 + 0.168404877f) / dsp->fConst252) + 1.06935835f));
	dsp->fConst303 = (2.0f * (53.5361519f - dsp->fConst281));
	dsp->fConst304 = (1.0f / (((dsp->fConst253 + 0.51247865f) / dsp->fConst252) + 0.689621389f));
	dsp->fConst305 = (2.0f * (7.62173128f - dsp->fConst281));
	dsp->fConst306 = (1.0f / (((dsp->fConst253 + 0.782413065f) / dsp->fConst252) + 0.245291501f));
	dsp->fConst307 = (9.99999975e-05f / dsp->fConst255);
	dsp->fConst308 = (2.0f * (0.000433227193f - dsp->fConst307));
	dsp->fConst309 = (((dsp->fConst253 + -0.782413065f) / dsp->fConst252) + 0.245291501f);
	dsp->fConst310 = (2.0f * (0.245291501f - dsp->fConst281));
	dsp->fConst311 = (dsp->fConst307 + 0.000433227193f);
	dsp->fConst312 = (((dsp->fConst253 + -0.51247865f) / dsp->fConst252) + 0.689621389f);
	dsp->fConst313 = (2.0f * (0.689621389f - dsp->fConst281));
	dsp->fConst314 = (dsp->fConst281 + 7.62173128f);
	dsp->fConst315 = (((dsp->fConst253 + -0.168404877f) / dsp->fConst252) + 1.06935835f);
	dsp->fConst316 = (2.0f * (1.06935835f - dsp->fConst281));
	dsp->fConst317 = (dsp->fConst281 + 53.5361519f);
	dsp->fConst318 = (((dsp->fConst291 + -3.18972731f) / dsp->fConst290) + 4.07678175f);
	dsp->fConst319 = (1.0f / dsp->fConst293);
	dsp->fConst320 = (2.0f * (4.07678175f - dsp->fConst319));
	dsp->fConst321 = (dsp->fConst300 + 0.000407678192f);
	dsp->fConst322 = (((dsp->fConst291 + -0.743130445f) / dsp->fConst290) + 1.4500711f);
	dsp->fConst323 = (2.0f * (1.4500711f - dsp->fConst319));
	dsp->fConst324 = (dsp->fConst297 + 1.4500711f);
	dsp->fConst325 = (((dsp->fConst291 + -0.157482162f) / dsp->fConst290) + 0.935140193f);
	dsp->fConst326 = (2.0f * (0.935140193f - dsp->fConst319));
	dsp->fConst327 = (dsp->fConst294 + 0.935140193f);
	dsp->fConst328 = tanf((785.398193f / dsp->fConst0));
	dsp->fConst329 = (1.0f / dsp->fConst328);
	dsp->fConst330 = (1.0f / (((dsp->fConst329 + 0.157482162f) / dsp->fConst328) + 0.935140193f));
	dsp->fConst331 = mydsp_faustpower2_f(dsp->fConst328);
	dsp->fConst332 = (50.0638084f / dsp->fConst331);
	dsp->fConst333 = (2.0f * (0.935140193f - dsp->fConst332));
	dsp->fConst334 = (1.0f / (((dsp->fConst329 + 0.743130445f) / dsp->fConst328) + 1.4500711f));
	dsp->fConst335 = (11.0520525f / dsp->fConst331);
	dsp->fConst336 = (2.0f * (1.4500711f - dsp->fConst335));
	dsp->fConst337 = (1.0f / (((dsp->fConst329 + 3.18972731f) / dsp->fConst328) + 4.07678175f));
	dsp->fConst338 = (0.00176617282f / dsp->fConst331);
	dsp->fConst339 = (2.0f * (0.000407678192f - dsp->fConst338));
	dsp->fConst340 = (1.0f / (((dsp->fConst291 + 0.168404877f) / dsp->fConst290) + 1.06935835f));
	dsp->fConst341 = (2.0f * (53.5361519f - dsp->fConst319));
	dsp->fConst342 = (1.0f / (((dsp->fConst291 + 0.51247865f) / dsp->fConst290) + 0.689621389f));
	dsp->fConst343 = (2.0f * (7.62173128f - dsp->fConst319));
	dsp->fConst344 = (1.0f / (((dsp->fConst291 + 0.782413065f) / dsp->fConst290) + 0.245291501f));
	dsp->fConst345 = (9.99999975e-05f / dsp->fConst293);
	dsp->fConst346 = (2.0f * (0.000433227193f - dsp->fConst345));
	dsp->fConst347 = (((dsp->fConst291 + -0.782413065f) / dsp->fConst290) + 0.245291501f);
	dsp->fConst348 = (2.0f * (0.245291501f - dsp->fConst319));
	dsp->fConst349 = (dsp->fConst345 + 0.000433227193f);
	dsp->fConst350 = (((dsp->fConst291 + -0.51247865f) / dsp->fConst290) + 0.689621389f);
	dsp->fConst351 = (2.0f * (0.689621389f - dsp->fConst319));
	dsp->fConst352 = (dsp->fConst319 + 7.62173128f);
	dsp->fConst353 = (((dsp->fConst291 + -0.168404877f) / dsp->fConst290) + 1.06935835f);
	dsp->fConst354 = (2.0f * (1.06935835f - dsp->fConst319));
	dsp->fConst355 = (dsp->fConst319 + 53.5361519f);
	dsp->fConst356 = (((dsp->fConst329 + -3.18972731f) / dsp->fConst328) + 4.07678175f);
	dsp->fConst357 = (1.0f / dsp->fConst331);
	dsp->fConst358 = (2.0f * (4.07678175f - dsp->fConst357));
	dsp->fConst359 = (dsp->fConst338 + 0.000407678192f);
	dsp->fConst360 = (((dsp->fConst329 + -0.743130445f) / dsp->fConst328) + 1.4500711f);
	dsp->fConst361 = (2.0f * (1.4500711f - dsp->fConst357));
	dsp->fConst362 = (dsp->fConst335 + 1.4500711f);
	dsp->fConst363 = (((dsp->fConst329 + -0.157482162f) / dsp->fConst328) + 0.935140193f);
	dsp->fConst364 = (2.0f * (0.935140193f - dsp->fConst357));
	dsp->fConst365 = (dsp->fConst332 + 0.935140193f);
	dsp->fConst366 = tanf((494.769836f / dsp->fConst0));
	dsp->fConst367 = (1.0f / dsp->fConst366);
	dsp->fConst368 = (1.0f / (((dsp->fConst367 + 0.157482162f) / dsp->fConst366) + 0.935140193f));
	dsp->fConst369 = mydsp_faustpower2_f(dsp->fConst366);
	dsp->fConst370 = (50.0638084f / dsp->fConst369);
	dsp->fConst371 = (2.0f * (0.935140193f - dsp->fConst370));
	dsp->fConst372 = (1.0f / (((dsp->fConst367 + 0.743130445f) / dsp->fConst366) + 1.4500711f));
	dsp->fConst373 = (11.0520525f / dsp->fConst369);
	dsp->fConst374 = (2.0f * (1.4500711f - dsp->fConst373));
	dsp->fConst375 = (1.0f / (((dsp->fConst367 + 3.18972731f) / dsp->fConst366) + 4.07678175f));
	dsp->fConst376 = (0.00176617282f / dsp->fConst369);
	dsp->fConst377 = (2.0f * (0.000407678192f - dsp->fConst376));
	dsp->fConst378 = (1.0f / (((dsp->fConst329 + 0.168404877f) / dsp->fConst328) + 1.06935835f));
	dsp->fConst379 = (2.0f * (53.5361519f - dsp->fConst357));
	dsp->fConst380 = (1.0f / (((dsp->fConst329 + 0.51247865f) / dsp->fConst328) + 0.689621389f));
	dsp->fConst381 = (2.0f * (7.62173128f - dsp->fConst357));
	dsp->fConst382 = (1.0f / (((dsp->fConst329 + 0.782413065f) / dsp->fConst328) + 0.245291501f));
	dsp->fConst383 = (9.99999975e-05f / dsp->fConst331);
	dsp->fConst384 = (2.0f * (0.000433227193f - dsp->fConst383));
	dsp->fConst385 = (((dsp->fConst329 + -0.782413065f) / dsp->fConst328) + 0.245291501f);
	dsp->fConst386 = (2.0f * (0.245291501f - dsp->fConst357));
	dsp->fConst387 = (dsp->fConst383 + 0.000433227193f);
	dsp->fConst388 = (((dsp->fConst329 + -0.51247865f) / dsp->fConst328) + 0.689621389f);
	dsp->fConst389 = (2.0f * (0.689621389f - dsp->fConst357));
	dsp->fConst390 = (dsp->fConst357 + 7.62173128f);
	dsp->fConst391 = (((dsp->fConst329 + -0.168404877f) / dsp->fConst328) + 1.06935835f);
	dsp->fConst392 = (2.0f * (1.06935835f - dsp->fConst357));
	dsp->fConst393 = (dsp->fConst357 + 53.5361519f);
	dsp->fConst394 = (((dsp->fConst367 + -3.18972731f) / dsp->fConst366) + 4.07678175f);
	dsp->fConst395 = (1.0f / dsp->fConst369);
	dsp->fConst396 = (2.0f * (4.07678175f - dsp->fConst395));
	dsp->fConst397 = (dsp->fConst376 + 0.000407678192f);
	dsp->fConst398 = (((dsp->fConst367 + -0.743130445f) / dsp->fConst366) + 1.4500711f);
	dsp->fConst399 = (2.0f * (1.4500711f - dsp->fConst395));
	dsp->fConst400 = (dsp->fConst373 + 1.4500711f);
	dsp->fConst401 = (((dsp->fConst367 + -0.157482162f) / dsp->fConst366) + 0.935140193f);
	dsp->fConst402 = (2.0f * (0.935140193f - dsp->fConst395));
	dsp->fConst403 = (dsp->fConst370 + 0.935140193f);
	dsp->fConst404 = tanf((311.685455f / dsp->fConst0));
	dsp->fConst405 = (1.0f / dsp->fConst404);
	dsp->fConst406 = (1.0f / (((dsp->fConst405 + 0.157482162f) / dsp->fConst404) + 0.935140193f));
	dsp->fConst407 = mydsp_faustpower2_f(dsp->fConst404);
	dsp->fConst408 = (50.0638084f / dsp->fConst407);
	dsp->fConst409 = (2.0f * (0.935140193f - dsp->fConst408));
	dsp->fConst410 = (1.0f / (((dsp->fConst405 + 0.743130445f) / dsp->fConst404) + 1.4500711f));
	dsp->fConst411 = (11.0520525f / dsp->fConst407);
	dsp->fConst412 = (2.0f * (1.4500711f - dsp->fConst411));
	dsp->fConst413 = (1.0f / (((dsp->fConst405 + 3.18972731f) / dsp->fConst404) + 4.07678175f));
	dsp->fConst414 = (0.00176617282f / dsp->fConst407);
	dsp->fConst415 = (2.0f * (0.000407678192f - dsp->fConst414));
	dsp->fConst416 = (1.0f / (((dsp->fConst367 + 0.168404877f) / dsp->fConst366) + 1.06935835f));
	dsp->fConst417 = (2.0f * (53.5361519f - dsp->fConst395));
	dsp->fConst418 = (1.0f / (((dsp->fConst367 + 0.51247865f) / dsp->fConst366) + 0.689621389f));
	dsp->fConst419 = (2.0f * (7.62173128f - dsp->fConst395));
	dsp->fConst420 = (1.0f / (((dsp->fConst367 + 0.782413065f) / dsp->fConst366) + 0.245291501f));
	dsp->fConst421 = (9.99999975e-05f / dsp->fConst369);
	dsp->fConst422 = (2.0f * (0.000433227193f - dsp->fConst421));
	dsp->fConst423 = (((dsp->fConst367 + -0.782413065f) / dsp->fConst366) + 0.245291501f);
	dsp->fConst424 = (2.0f * (0.245291501f - dsp->fConst395));
	dsp->fConst425 = (dsp->fConst421 + 0.000433227193f);
	dsp->fConst426 = (((dsp->fConst367 + -0.51247865f) / dsp->fConst366) + 0.689621389f);
	dsp->fConst427 = (2.0f * (0.689621389f - dsp->fConst395));
	dsp->fConst428 = (dsp->fConst395 + 7.62173128f);
	dsp->fConst429 = (((dsp->fConst367 + -0.168404877f) / dsp->fConst366) + 1.06935835f);
	dsp->fConst430 = (2.0f * (1.06935835f - dsp->fConst395));
	dsp->fConst431 = (dsp->fConst395 + 53.5361519f);
	dsp->fConst432 = (((dsp->fConst405 + -3.18972731f) / dsp->fConst404) + 4.07678175f);
	dsp->fConst433 = (1.0f / dsp->fConst407);
	dsp->fConst434 = (2.0f * (4.07678175f - dsp->fConst433));
	dsp->fConst435 = (dsp->fConst414 + 0.000407678192f);
	dsp->fConst436 = (((dsp->fConst405 + -0.743130445f) / dsp->fConst404) + 1.4500711f);
	dsp->fConst437 = (2.0f * (1.4500711f - dsp->fConst433));
	dsp->fConst438 = (dsp->fConst411 + 1.4500711f);
	dsp->fConst439 = (((dsp->fConst405 + -0.157482162f) / dsp->fConst404) + 0.935140193f);
	dsp->fConst440 = (2.0f * (0.935140193f - dsp->fConst433));
	dsp->fConst441 = (dsp->fConst408 + 0.935140193f);
	dsp->fConst442 = tanf((196.349548f / dsp->fConst0));
	dsp->fConst443 = (1.0f / dsp->fConst442);
	dsp->fConst444 = (1.0f / (((dsp->fConst443 + 0.157482162f) / dsp->fConst442) + 0.935140193f));
	dsp->fConst445 = mydsp_faustpower2_f(dsp->fConst442);
	dsp->fConst446 = (50.0638084f / dsp->fConst445);
	dsp->fConst447 = (2.0f * (0.935140193f - dsp->fConst446));
	dsp->fConst448 = (1.0f / (((dsp->fConst443 + 0.743130445f) / dsp->fConst442) + 1.4500711f));
	dsp->fConst449 = (11.0520525f / dsp->fConst445);
	dsp->fConst450 = (2.0f * (1.4500711f - dsp->fConst449));
	dsp->fConst451 = (1.0f / (((dsp->fConst443 + 3.18972731f) / dsp->fConst442) + 4.07678175f));
	dsp->fConst452 = (0.00176617282f / dsp->fConst445);
	dsp->fConst453 = (2.0f * (0.000407678192f - dsp->fConst452));
	dsp->fConst454 = (1.0f / (((dsp->fConst405 + 0.168404877f) / dsp->fConst404) + 1.06935835f));
	dsp->fConst455 = (2.0f * (53.5361519f - dsp->fConst433));
	dsp->fConst456 = (1.0f / (((dsp->fConst405 + 0.51247865f) / dsp->fConst404) + 0.689621389f));
	dsp->fConst457 = (2.0f * (7.62173128f - dsp->fConst433));
	dsp->fConst458 = (1.0f / (((dsp->fConst405 + 0.782413065f) / dsp->fConst404) + 0.245291501f));
	dsp->fConst459 = (9.99999975e-05f / dsp->fConst407);
	dsp->fConst460 = (2.0f * (0.000433227193f - dsp->fConst459));
	dsp->fConst461 = (((dsp->fConst405 + -0.782413065f) / dsp->fConst404) + 0.245291501f);
	dsp->fConst462 = (2.0f * (0.245291501f - dsp->fConst433));
	dsp->fConst463 = (dsp->fConst459 + 0.000433227193f);
	dsp->fConst464 = (((dsp->fConst405 + -0.51247865f) / dsp->fConst404) + 0.689621389f);
	dsp->fConst465 = (2.0f * (0.689621389f - dsp->fConst433));
	dsp->fConst466 = (dsp->fConst433 + 7.62173128f);
	dsp->fConst467 = (((dsp->fConst405 + -0.168404877f) / dsp->fConst404) + 1.06935835f);
	dsp->fConst468 = (2.0f * (1.06935835f - dsp->fConst433));
	dsp->fConst469 = (dsp->fConst433 + 53.5361519f);
	dsp->fConst470 = (((dsp->fConst443 + -3.18972731f) / dsp->fConst442) + 4.07678175f);
	dsp->fConst471 = (1.0f / dsp->fConst445);
	dsp->fConst472 = (2.0f * (4.07678175f - dsp->fConst471));
	dsp->fConst473 = (dsp->fConst452 + 0.000407678192f);
	dsp->fConst474 = (((dsp->fConst443 + -0.743130445f) / dsp->fConst442) + 1.4500711f);
	dsp->fConst475 = (2.0f * (1.4500711f - dsp->fConst471));
	dsp->fConst476 = (dsp->fConst449 + 1.4500711f);
	dsp->fConst477 = (((dsp->fConst443 + -0.157482162f) / dsp->fConst442) + 0.935140193f);
	dsp->fConst478 = (2.0f * (0.935140193f - dsp->fConst471));
	dsp->fConst479 = (dsp->fConst446 + 0.935140193f);
	dsp->fConst480 = tanf((123.692459f / dsp->fConst0));
	dsp->fConst481 = (1.0f / dsp->fConst480);
	dsp->fConst482 = (1.0f / (((dsp->fConst481 + 0.157482162f) / dsp->fConst480) + 0.935140193f));
	dsp->fConst483 = mydsp_faustpower2_f(dsp->fConst480);
	dsp->fConst484 = (50.0638084f / dsp->fConst483);
	dsp->fConst485 = (2.0f * (0.935140193f - dsp->fConst484));
	dsp->fConst486 = (1.0f / (((dsp->fConst481 + 0.743130445f) / dsp->fConst480) + 1.4500711f));
	dsp->fConst487 = (11.0520525f / dsp->fConst483);
	dsp->fConst488 = (2.0f * (1.4500711f - dsp->fConst487));
	dsp->fConst489 = (1.0f / (((dsp->fConst481 + 3.18972731f) / dsp->fConst480) + 4.07678175f));
	dsp->fConst490 = (0.00176617282f / dsp->fConst483);
	dsp->fConst491 = (2.0f * (0.000407678192f - dsp->fConst490));
	dsp->fConst492 = (1.0f / (((dsp->fConst443 + 0.168404877f) / dsp->fConst442) + 1.06935835f));
	dsp->fConst493 = (2.0f * (53.5361519f - dsp->fConst471));
	dsp->fConst494 = (1.0f / (((dsp->fConst443 + 0.51247865f) / dsp->fConst442) + 0.689621389f));
	dsp->fConst495 = (2.0f * (7.62173128f - dsp->fConst471));
	dsp->fConst496 = (1.0f / (((dsp->fConst443 + 0.782413065f) / dsp->fConst442) + 0.245291501f));
	dsp->fConst497 = (9.99999975e-05f / dsp->fConst445);
	dsp->fConst498 = (2.0f * (0.000433227193f - dsp->fConst497));
	dsp->fConst499 = (((dsp->fConst443 + -0.782413065f) / dsp->fConst442) + 0.245291501f);
	dsp->fConst500 = (2.0f * (0.245291501f - dsp->fConst471));
	dsp->fConst501 = (dsp->fConst497 + 0.000433227193f);
	dsp->fConst502 = (((dsp->fConst443 + -0.51247865f) / dsp->fConst442) + 0.689621389f);
	dsp->fConst503 = (2.0f * (0.689621389f - dsp->fConst471));
	dsp->fConst504 = (dsp->fConst471 + 7.62173128f);
	dsp->fConst505 = (((dsp->fConst443 + -0.168404877f) / dsp->fConst442) + 1.06935835f);
	dsp->fConst506 = (2.0f * (1.06935835f - dsp->fConst471));
	dsp->fConst507 = (dsp->fConst471 + 53.5361519f);
	dsp->fConst508 = (((dsp->fConst481 + -3.18972731f) / dsp->fConst480) + 4.07678175f);
	dsp->fConst509 = (1.0f / dsp->fConst483);
	dsp->fConst510 = (2.0f * (4.07678175f - dsp->fConst509));
	dsp->fConst511 = (dsp->fConst490 + 0.000407678192f);
	dsp->fConst512 = (((dsp->fConst481 + -0.743130445f) / dsp->fConst480) + 1.4500711f);
	dsp->fConst513 = (2.0f * (1.4500711f - dsp->fConst509));
	dsp->fConst514 = (dsp->fConst487 + 1.4500711f);
	dsp->fConst515 = (((dsp->fConst481 + -0.157482162f) / dsp->fConst480) + 0.935140193f);
	dsp->fConst516 = (2.0f * (0.935140193f - dsp->fConst509));
	dsp->fConst517 = (dsp->fConst484 + 0.935140193f);
	dsp->fConst518 = (1.0f / (((dsp->fConst481 + 0.168404877f) / dsp->fConst480) + 1.06935835f));
	dsp->fConst519 = (2.0f * (53.5361519f - dsp->fConst509));
	dsp->fConst520 = (1.0f / (((dsp->fConst481 + 0.51247865f) / dsp->fConst480) + 0.689621389f));
	dsp->fConst521 = (2.0f * (7.62173128f - dsp->fConst509));
	dsp->fConst522 = (1.0f / (((dsp->fConst481 + 0.782413065f) / dsp->fConst480) + 0.245291501f));
	dsp->fConst523 = (9.99999975e-05f / dsp->fConst483);
	dsp->fConst524 = (2.0f * (0.000433227193f - dsp->fConst523));
	dsp->fConst525 = (((dsp->fConst481 + -0.782413065f) / dsp->fConst480) + 0.245291501f);
	dsp->fConst526 = (2.0f * (0.245291501f - dsp->fConst509));
	dsp->fConst527 = (dsp->fConst523 + 0.000433227193f);
	dsp->fConst528 = (((dsp->fConst481 + -0.51247865f) / dsp->fConst480) + 0.689621389f);
	dsp->fConst529 = (2.0f * (0.689621389f - dsp->fConst509));
	dsp->fConst530 = (dsp->fConst509 + 7.62173128f);
	dsp->fConst531 = (((dsp->fConst481 + -0.168404877f) / dsp->fConst480) + 1.06935835f);
	dsp->fConst532 = (2.0f * (1.06935835f - dsp->fConst509));
	dsp->fConst533 = (dsp->fConst509 + 53.5361519f);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "spectralLevel");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph14, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4732bd70", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4731a780", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b472f4a20", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b472d2c40", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b472b0e60", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4728f080", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4726d2a0", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4724b4c0", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b472296e0", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b47207900", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b471e1ba0", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b471bfdc0", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4719dfe0", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b4717c200", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7f9b47159250", &dsp->fVbargraph0, -50.0f, 10.0f);
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
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = expf((0.0f - (dsp->fConst1 / (float)dsp->fHslider1)));
	float fSlow2 = (1.0f - fSlow1);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fRec3[0] = (fTemp0 - (dsp->fConst11 * ((dsp->fConst14 * dsp->fRec3[2]) + (dsp->fConst16 * dsp->fRec3[1]))));
			dsp->fRec2[0] = ((dsp->fConst11 * (((dsp->fConst13 * dsp->fRec3[1]) + (dsp->fConst17 * dsp->fRec3[0])) + (dsp->fConst17 * dsp->fRec3[2]))) - (dsp->fConst8 * ((dsp->fConst18 * dsp->fRec2[2]) + (dsp->fConst19 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst8 * (((dsp->fConst10 * dsp->fRec2[1]) + (dsp->fConst20 * dsp->fRec2[0])) + (dsp->fConst20 * dsp->fRec2[2]))) - (dsp->fConst4 * ((dsp->fConst21 * dsp->fRec1[2]) + (dsp->fConst22 * dsp->fRec1[1]))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * fabsf((dsp->fConst4 * (((dsp->fConst7 * dsp->fRec1[1]) + (dsp->fConst23 * dsp->fRec1[0])) + (dsp->fConst23 * dsp->fRec1[2]))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec0[0]))));
			dsp->fRec10[0] = (fTemp0 - (dsp->fConst40 * ((dsp->fConst43 * dsp->fRec10[2]) + (dsp->fConst44 * dsp->fRec10[1]))));
			dsp->fRec9[0] = ((dsp->fConst40 * (((dsp->fConst42 * dsp->fRec10[1]) + (dsp->fConst45 * dsp->fRec10[0])) + (dsp->fConst45 * dsp->fRec10[2]))) - (dsp->fConst38 * ((dsp->fConst46 * dsp->fRec9[2]) + (dsp->fConst47 * dsp->fRec9[1]))));
			dsp->fRec8[0] = ((dsp->fConst38 * (((dsp->fConst39 * dsp->fRec9[1]) + (dsp->fConst48 * dsp->fRec9[0])) + (dsp->fConst48 * dsp->fRec9[2]))) - (dsp->fConst36 * ((dsp->fConst49 * dsp->fRec8[2]) + (dsp->fConst50 * dsp->fRec8[1]))));
			float fTemp1 = (dsp->fConst36 * (((dsp->fConst37 * dsp->fRec8[1]) + (dsp->fConst51 * dsp->fRec8[0])) + (dsp->fConst51 * dsp->fRec8[2])));
			dsp->fRec7[0] = (fTemp1 - (dsp->fConst33 * ((dsp->fConst52 * dsp->fRec7[2]) + (dsp->fConst54 * dsp->fRec7[1]))));
			dsp->fRec6[0] = ((dsp->fConst33 * (((dsp->fConst35 * dsp->fRec7[1]) + (dsp->fConst55 * dsp->fRec7[0])) + (dsp->fConst55 * dsp->fRec7[2]))) - (dsp->fConst30 * ((dsp->fConst56 * dsp->fRec6[2]) + (dsp->fConst57 * dsp->fRec6[1]))));
			dsp->fRec5[0] = ((dsp->fConst30 * (((dsp->fConst32 * dsp->fRec6[1]) + (dsp->fConst58 * dsp->fRec6[0])) + (dsp->fConst58 * dsp->fRec6[2]))) - (dsp->fConst26 * ((dsp->fConst59 * dsp->fRec5[2]) + (dsp->fConst60 * dsp->fRec5[1]))));
			dsp->fRec4[0] = ((fSlow1 * dsp->fRec4[1]) + (fSlow2 * fabsf((dsp->fConst26 * (((dsp->fConst29 * dsp->fRec5[1]) + (dsp->fConst61 * dsp->fRec5[0])) + (dsp->fConst61 * dsp->fRec5[2]))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec4[0]))));
			dsp->fRec17[0] = (fTemp1 - (dsp->fConst78 * ((dsp->fConst81 * dsp->fRec17[2]) + (dsp->fConst82 * dsp->fRec17[1]))));
			dsp->fRec16[0] = ((dsp->fConst78 * (((dsp->fConst80 * dsp->fRec17[1]) + (dsp->fConst83 * dsp->fRec17[0])) + (dsp->fConst83 * dsp->fRec17[2]))) - (dsp->fConst76 * ((dsp->fConst84 * dsp->fRec16[2]) + (dsp->fConst85 * dsp->fRec16[1]))));
			dsp->fRec15[0] = ((dsp->fConst76 * (((dsp->fConst77 * dsp->fRec16[1]) + (dsp->fConst86 * dsp->fRec16[0])) + (dsp->fConst86 * dsp->fRec16[2]))) - (dsp->fConst74 * ((dsp->fConst87 * dsp->fRec15[2]) + (dsp->fConst88 * dsp->fRec15[1]))));
			float fTemp2 = (dsp->fConst74 * (((dsp->fConst75 * dsp->fRec15[1]) + (dsp->fConst89 * dsp->fRec15[0])) + (dsp->fConst89 * dsp->fRec15[2])));
			dsp->fRec14[0] = (fTemp2 - (dsp->fConst71 * ((dsp->fConst90 * dsp->fRec14[2]) + (dsp->fConst92 * dsp->fRec14[1]))));
			dsp->fRec13[0] = ((dsp->fConst71 * (((dsp->fConst73 * dsp->fRec14[1]) + (dsp->fConst93 * dsp->fRec14[0])) + (dsp->fConst93 * dsp->fRec14[2]))) - (dsp->fConst68 * ((dsp->fConst94 * dsp->fRec13[2]) + (dsp->fConst95 * dsp->fRec13[1]))));
			dsp->fRec12[0] = ((dsp->fConst68 * (((dsp->fConst70 * dsp->fRec13[1]) + (dsp->fConst96 * dsp->fRec13[0])) + (dsp->fConst96 * dsp->fRec13[2]))) - (dsp->fConst64 * ((dsp->fConst97 * dsp->fRec12[2]) + (dsp->fConst98 * dsp->fRec12[1]))));
			dsp->fRec11[0] = ((fSlow1 * dsp->fRec11[1]) + (fSlow2 * fabsf((dsp->fConst64 * (((dsp->fConst67 * dsp->fRec12[1]) + (dsp->fConst99 * dsp->fRec12[0])) + (dsp->fConst99 * dsp->fRec12[2]))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec11[0]))));
			dsp->fRec24[0] = (fTemp2 - (dsp->fConst116 * ((dsp->fConst119 * dsp->fRec24[2]) + (dsp->fConst120 * dsp->fRec24[1]))));
			dsp->fRec23[0] = ((dsp->fConst116 * (((dsp->fConst118 * dsp->fRec24[1]) + (dsp->fConst121 * dsp->fRec24[0])) + (dsp->fConst121 * dsp->fRec24[2]))) - (dsp->fConst114 * ((dsp->fConst122 * dsp->fRec23[2]) + (dsp->fConst123 * dsp->fRec23[1]))));
			dsp->fRec22[0] = ((dsp->fConst114 * (((dsp->fConst115 * dsp->fRec23[1]) + (dsp->fConst124 * dsp->fRec23[0])) + (dsp->fConst124 * dsp->fRec23[2]))) - (dsp->fConst112 * ((dsp->fConst125 * dsp->fRec22[2]) + (dsp->fConst126 * dsp->fRec22[1]))));
			float fTemp3 = (dsp->fConst112 * (((dsp->fConst113 * dsp->fRec22[1]) + (dsp->fConst127 * dsp->fRec22[0])) + (dsp->fConst127 * dsp->fRec22[2])));
			dsp->fRec21[0] = (fTemp3 - (dsp->fConst109 * ((dsp->fConst128 * dsp->fRec21[2]) + (dsp->fConst130 * dsp->fRec21[1]))));
			dsp->fRec20[0] = ((dsp->fConst109 * (((dsp->fConst111 * dsp->fRec21[1]) + (dsp->fConst131 * dsp->fRec21[0])) + (dsp->fConst131 * dsp->fRec21[2]))) - (dsp->fConst106 * ((dsp->fConst132 * dsp->fRec20[2]) + (dsp->fConst133 * dsp->fRec20[1]))));
			dsp->fRec19[0] = ((dsp->fConst106 * (((dsp->fConst108 * dsp->fRec20[1]) + (dsp->fConst134 * dsp->fRec20[0])) + (dsp->fConst134 * dsp->fRec20[2]))) - (dsp->fConst102 * ((dsp->fConst135 * dsp->fRec19[2]) + (dsp->fConst136 * dsp->fRec19[1]))));
			dsp->fRec18[0] = ((fSlow1 * dsp->fRec18[1]) + (fSlow2 * fabsf((dsp->fConst102 * (((dsp->fConst105 * dsp->fRec19[1]) + (dsp->fConst137 * dsp->fRec19[0])) + (dsp->fConst137 * dsp->fRec19[2]))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec18[0]))));
			dsp->fRec31[0] = (fTemp3 - (dsp->fConst154 * ((dsp->fConst157 * dsp->fRec31[2]) + (dsp->fConst158 * dsp->fRec31[1]))));
			dsp->fRec30[0] = ((dsp->fConst154 * (((dsp->fConst156 * dsp->fRec31[1]) + (dsp->fConst159 * dsp->fRec31[0])) + (dsp->fConst159 * dsp->fRec31[2]))) - (dsp->fConst152 * ((dsp->fConst160 * dsp->fRec30[2]) + (dsp->fConst161 * dsp->fRec30[1]))));
			dsp->fRec29[0] = ((dsp->fConst152 * (((dsp->fConst153 * dsp->fRec30[1]) + (dsp->fConst162 * dsp->fRec30[0])) + (dsp->fConst162 * dsp->fRec30[2]))) - (dsp->fConst150 * ((dsp->fConst163 * dsp->fRec29[2]) + (dsp->fConst164 * dsp->fRec29[1]))));
			float fTemp4 = (dsp->fConst150 * (((dsp->fConst151 * dsp->fRec29[1]) + (dsp->fConst165 * dsp->fRec29[0])) + (dsp->fConst165 * dsp->fRec29[2])));
			dsp->fRec28[0] = (fTemp4 - (dsp->fConst147 * ((dsp->fConst166 * dsp->fRec28[2]) + (dsp->fConst168 * dsp->fRec28[1]))));
			dsp->fRec27[0] = ((dsp->fConst147 * (((dsp->fConst149 * dsp->fRec28[1]) + (dsp->fConst169 * dsp->fRec28[0])) + (dsp->fConst169 * dsp->fRec28[2]))) - (dsp->fConst144 * ((dsp->fConst170 * dsp->fRec27[2]) + (dsp->fConst171 * dsp->fRec27[1]))));
			dsp->fRec26[0] = ((dsp->fConst144 * (((dsp->fConst146 * dsp->fRec27[1]) + (dsp->fConst172 * dsp->fRec27[0])) + (dsp->fConst172 * dsp->fRec27[2]))) - (dsp->fConst140 * ((dsp->fConst173 * dsp->fRec26[2]) + (dsp->fConst174 * dsp->fRec26[1]))));
			dsp->fRec25[0] = ((fSlow1 * dsp->fRec25[1]) + (fSlow2 * fabsf((dsp->fConst140 * (((dsp->fConst143 * dsp->fRec26[1]) + (dsp->fConst175 * dsp->fRec26[0])) + (dsp->fConst175 * dsp->fRec26[2]))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec25[0]))));
			dsp->fRec38[0] = (fTemp4 - (dsp->fConst192 * ((dsp->fConst195 * dsp->fRec38[2]) + (dsp->fConst196 * dsp->fRec38[1]))));
			dsp->fRec37[0] = ((dsp->fConst192 * (((dsp->fConst194 * dsp->fRec38[1]) + (dsp->fConst197 * dsp->fRec38[0])) + (dsp->fConst197 * dsp->fRec38[2]))) - (dsp->fConst190 * ((dsp->fConst198 * dsp->fRec37[2]) + (dsp->fConst199 * dsp->fRec37[1]))));
			dsp->fRec36[0] = ((dsp->fConst190 * (((dsp->fConst191 * dsp->fRec37[1]) + (dsp->fConst200 * dsp->fRec37[0])) + (dsp->fConst200 * dsp->fRec37[2]))) - (dsp->fConst188 * ((dsp->fConst201 * dsp->fRec36[2]) + (dsp->fConst202 * dsp->fRec36[1]))));
			float fTemp5 = (dsp->fConst188 * (((dsp->fConst189 * dsp->fRec36[1]) + (dsp->fConst203 * dsp->fRec36[0])) + (dsp->fConst203 * dsp->fRec36[2])));
			dsp->fRec35[0] = (fTemp5 - (dsp->fConst185 * ((dsp->fConst204 * dsp->fRec35[2]) + (dsp->fConst206 * dsp->fRec35[1]))));
			dsp->fRec34[0] = ((dsp->fConst185 * (((dsp->fConst187 * dsp->fRec35[1]) + (dsp->fConst207 * dsp->fRec35[0])) + (dsp->fConst207 * dsp->fRec35[2]))) - (dsp->fConst182 * ((dsp->fConst208 * dsp->fRec34[2]) + (dsp->fConst209 * dsp->fRec34[1]))));
			dsp->fRec33[0] = ((dsp->fConst182 * (((dsp->fConst184 * dsp->fRec34[1]) + (dsp->fConst210 * dsp->fRec34[0])) + (dsp->fConst210 * dsp->fRec34[2]))) - (dsp->fConst178 * ((dsp->fConst211 * dsp->fRec33[2]) + (dsp->fConst212 * dsp->fRec33[1]))));
			dsp->fRec32[0] = ((fSlow1 * dsp->fRec32[1]) + (fSlow2 * fabsf((dsp->fConst178 * (((dsp->fConst181 * dsp->fRec33[1]) + (dsp->fConst213 * dsp->fRec33[0])) + (dsp->fConst213 * dsp->fRec33[2]))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec32[0]))));
			dsp->fRec45[0] = (fTemp5 - (dsp->fConst230 * ((dsp->fConst233 * dsp->fRec45[2]) + (dsp->fConst234 * dsp->fRec45[1]))));
			dsp->fRec44[0] = ((dsp->fConst230 * (((dsp->fConst232 * dsp->fRec45[1]) + (dsp->fConst235 * dsp->fRec45[0])) + (dsp->fConst235 * dsp->fRec45[2]))) - (dsp->fConst228 * ((dsp->fConst236 * dsp->fRec44[2]) + (dsp->fConst237 * dsp->fRec44[1]))));
			dsp->fRec43[0] = ((dsp->fConst228 * (((dsp->fConst229 * dsp->fRec44[1]) + (dsp->fConst238 * dsp->fRec44[0])) + (dsp->fConst238 * dsp->fRec44[2]))) - (dsp->fConst226 * ((dsp->fConst239 * dsp->fRec43[2]) + (dsp->fConst240 * dsp->fRec43[1]))));
			float fTemp6 = (dsp->fConst226 * (((dsp->fConst227 * dsp->fRec43[1]) + (dsp->fConst241 * dsp->fRec43[0])) + (dsp->fConst241 * dsp->fRec43[2])));
			dsp->fRec42[0] = (fTemp6 - (dsp->fConst223 * ((dsp->fConst242 * dsp->fRec42[2]) + (dsp->fConst244 * dsp->fRec42[1]))));
			dsp->fRec41[0] = ((dsp->fConst223 * (((dsp->fConst225 * dsp->fRec42[1]) + (dsp->fConst245 * dsp->fRec42[0])) + (dsp->fConst245 * dsp->fRec42[2]))) - (dsp->fConst220 * ((dsp->fConst246 * dsp->fRec41[2]) + (dsp->fConst247 * dsp->fRec41[1]))));
			dsp->fRec40[0] = ((dsp->fConst220 * (((dsp->fConst222 * dsp->fRec41[1]) + (dsp->fConst248 * dsp->fRec41[0])) + (dsp->fConst248 * dsp->fRec41[2]))) - (dsp->fConst216 * ((dsp->fConst249 * dsp->fRec40[2]) + (dsp->fConst250 * dsp->fRec40[1]))));
			dsp->fRec39[0] = ((fSlow1 * dsp->fRec39[1]) + (fSlow2 * fabsf((dsp->fConst216 * (((dsp->fConst219 * dsp->fRec40[1]) + (dsp->fConst251 * dsp->fRec40[0])) + (dsp->fConst251 * dsp->fRec40[2]))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec39[0]))));
			dsp->fRec52[0] = (fTemp6 - (dsp->fConst268 * ((dsp->fConst271 * dsp->fRec52[2]) + (dsp->fConst272 * dsp->fRec52[1]))));
			dsp->fRec51[0] = ((dsp->fConst268 * (((dsp->fConst270 * dsp->fRec52[1]) + (dsp->fConst273 * dsp->fRec52[0])) + (dsp->fConst273 * dsp->fRec52[2]))) - (dsp->fConst266 * ((dsp->fConst274 * dsp->fRec51[2]) + (dsp->fConst275 * dsp->fRec51[1]))));
			dsp->fRec50[0] = ((dsp->fConst266 * (((dsp->fConst267 * dsp->fRec51[1]) + (dsp->fConst276 * dsp->fRec51[0])) + (dsp->fConst276 * dsp->fRec51[2]))) - (dsp->fConst264 * ((dsp->fConst277 * dsp->fRec50[2]) + (dsp->fConst278 * dsp->fRec50[1]))));
			float fTemp7 = (dsp->fConst264 * (((dsp->fConst265 * dsp->fRec50[1]) + (dsp->fConst279 * dsp->fRec50[0])) + (dsp->fConst279 * dsp->fRec50[2])));
			dsp->fRec49[0] = (fTemp7 - (dsp->fConst261 * ((dsp->fConst280 * dsp->fRec49[2]) + (dsp->fConst282 * dsp->fRec49[1]))));
			dsp->fRec48[0] = ((dsp->fConst261 * (((dsp->fConst263 * dsp->fRec49[1]) + (dsp->fConst283 * dsp->fRec49[0])) + (dsp->fConst283 * dsp->fRec49[2]))) - (dsp->fConst258 * ((dsp->fConst284 * dsp->fRec48[2]) + (dsp->fConst285 * dsp->fRec48[1]))));
			dsp->fRec47[0] = ((dsp->fConst258 * (((dsp->fConst260 * dsp->fRec48[1]) + (dsp->fConst286 * dsp->fRec48[0])) + (dsp->fConst286 * dsp->fRec48[2]))) - (dsp->fConst254 * ((dsp->fConst287 * dsp->fRec47[2]) + (dsp->fConst288 * dsp->fRec47[1]))));
			dsp->fRec46[0] = ((fSlow1 * dsp->fRec46[1]) + (fSlow2 * fabsf((dsp->fConst254 * (((dsp->fConst257 * dsp->fRec47[1]) + (dsp->fConst289 * dsp->fRec47[0])) + (dsp->fConst289 * dsp->fRec47[2]))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec46[0]))));
			dsp->fRec59[0] = (fTemp7 - (dsp->fConst306 * ((dsp->fConst309 * dsp->fRec59[2]) + (dsp->fConst310 * dsp->fRec59[1]))));
			dsp->fRec58[0] = ((dsp->fConst306 * (((dsp->fConst308 * dsp->fRec59[1]) + (dsp->fConst311 * dsp->fRec59[0])) + (dsp->fConst311 * dsp->fRec59[2]))) - (dsp->fConst304 * ((dsp->fConst312 * dsp->fRec58[2]) + (dsp->fConst313 * dsp->fRec58[1]))));
			dsp->fRec57[0] = ((dsp->fConst304 * (((dsp->fConst305 * dsp->fRec58[1]) + (dsp->fConst314 * dsp->fRec58[0])) + (dsp->fConst314 * dsp->fRec58[2]))) - (dsp->fConst302 * ((dsp->fConst315 * dsp->fRec57[2]) + (dsp->fConst316 * dsp->fRec57[1]))));
			float fTemp8 = (dsp->fConst302 * (((dsp->fConst303 * dsp->fRec57[1]) + (dsp->fConst317 * dsp->fRec57[0])) + (dsp->fConst317 * dsp->fRec57[2])));
			dsp->fRec56[0] = (fTemp8 - (dsp->fConst299 * ((dsp->fConst318 * dsp->fRec56[2]) + (dsp->fConst320 * dsp->fRec56[1]))));
			dsp->fRec55[0] = ((dsp->fConst299 * (((dsp->fConst301 * dsp->fRec56[1]) + (dsp->fConst321 * dsp->fRec56[0])) + (dsp->fConst321 * dsp->fRec56[2]))) - (dsp->fConst296 * ((dsp->fConst322 * dsp->fRec55[2]) + (dsp->fConst323 * dsp->fRec55[1]))));
			dsp->fRec54[0] = ((dsp->fConst296 * (((dsp->fConst298 * dsp->fRec55[1]) + (dsp->fConst324 * dsp->fRec55[0])) + (dsp->fConst324 * dsp->fRec55[2]))) - (dsp->fConst292 * ((dsp->fConst325 * dsp->fRec54[2]) + (dsp->fConst326 * dsp->fRec54[1]))));
			dsp->fRec53[0] = ((fSlow1 * dsp->fRec53[1]) + (fSlow2 * fabsf((dsp->fConst292 * (((dsp->fConst295 * dsp->fRec54[1]) + (dsp->fConst327 * dsp->fRec54[0])) + (dsp->fConst327 * dsp->fRec54[2]))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec53[0]))));
			dsp->fRec66[0] = (fTemp8 - (dsp->fConst344 * ((dsp->fConst347 * dsp->fRec66[2]) + (dsp->fConst348 * dsp->fRec66[1]))));
			dsp->fRec65[0] = ((dsp->fConst344 * (((dsp->fConst346 * dsp->fRec66[1]) + (dsp->fConst349 * dsp->fRec66[0])) + (dsp->fConst349 * dsp->fRec66[2]))) - (dsp->fConst342 * ((dsp->fConst350 * dsp->fRec65[2]) + (dsp->fConst351 * dsp->fRec65[1]))));
			dsp->fRec64[0] = ((dsp->fConst342 * (((dsp->fConst343 * dsp->fRec65[1]) + (dsp->fConst352 * dsp->fRec65[0])) + (dsp->fConst352 * dsp->fRec65[2]))) - (dsp->fConst340 * ((dsp->fConst353 * dsp->fRec64[2]) + (dsp->fConst354 * dsp->fRec64[1]))));
			float fTemp9 = (dsp->fConst340 * (((dsp->fConst341 * dsp->fRec64[1]) + (dsp->fConst355 * dsp->fRec64[0])) + (dsp->fConst355 * dsp->fRec64[2])));
			dsp->fRec63[0] = (fTemp9 - (dsp->fConst337 * ((dsp->fConst356 * dsp->fRec63[2]) + (dsp->fConst358 * dsp->fRec63[1]))));
			dsp->fRec62[0] = ((dsp->fConst337 * (((dsp->fConst339 * dsp->fRec63[1]) + (dsp->fConst359 * dsp->fRec63[0])) + (dsp->fConst359 * dsp->fRec63[2]))) - (dsp->fConst334 * ((dsp->fConst360 * dsp->fRec62[2]) + (dsp->fConst361 * dsp->fRec62[1]))));
			dsp->fRec61[0] = ((dsp->fConst334 * (((dsp->fConst336 * dsp->fRec62[1]) + (dsp->fConst362 * dsp->fRec62[0])) + (dsp->fConst362 * dsp->fRec62[2]))) - (dsp->fConst330 * ((dsp->fConst363 * dsp->fRec61[2]) + (dsp->fConst364 * dsp->fRec61[1]))));
			dsp->fRec60[0] = ((fSlow1 * dsp->fRec60[1]) + (fSlow2 * fabsf((dsp->fConst330 * (((dsp->fConst333 * dsp->fRec61[1]) + (dsp->fConst365 * dsp->fRec61[0])) + (dsp->fConst365 * dsp->fRec61[2]))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec60[0]))));
			dsp->fRec73[0] = (fTemp9 - (dsp->fConst382 * ((dsp->fConst385 * dsp->fRec73[2]) + (dsp->fConst386 * dsp->fRec73[1]))));
			dsp->fRec72[0] = ((dsp->fConst382 * (((dsp->fConst384 * dsp->fRec73[1]) + (dsp->fConst387 * dsp->fRec73[0])) + (dsp->fConst387 * dsp->fRec73[2]))) - (dsp->fConst380 * ((dsp->fConst388 * dsp->fRec72[2]) + (dsp->fConst389 * dsp->fRec72[1]))));
			dsp->fRec71[0] = ((dsp->fConst380 * (((dsp->fConst381 * dsp->fRec72[1]) + (dsp->fConst390 * dsp->fRec72[0])) + (dsp->fConst390 * dsp->fRec72[2]))) - (dsp->fConst378 * ((dsp->fConst391 * dsp->fRec71[2]) + (dsp->fConst392 * dsp->fRec71[1]))));
			float fTemp10 = (dsp->fConst378 * (((dsp->fConst379 * dsp->fRec71[1]) + (dsp->fConst393 * dsp->fRec71[0])) + (dsp->fConst393 * dsp->fRec71[2])));
			dsp->fRec70[0] = (fTemp10 - (dsp->fConst375 * ((dsp->fConst394 * dsp->fRec70[2]) + (dsp->fConst396 * dsp->fRec70[1]))));
			dsp->fRec69[0] = ((dsp->fConst375 * (((dsp->fConst377 * dsp->fRec70[1]) + (dsp->fConst397 * dsp->fRec70[0])) + (dsp->fConst397 * dsp->fRec70[2]))) - (dsp->fConst372 * ((dsp->fConst398 * dsp->fRec69[2]) + (dsp->fConst399 * dsp->fRec69[1]))));
			dsp->fRec68[0] = ((dsp->fConst372 * (((dsp->fConst374 * dsp->fRec69[1]) + (dsp->fConst400 * dsp->fRec69[0])) + (dsp->fConst400 * dsp->fRec69[2]))) - (dsp->fConst368 * ((dsp->fConst401 * dsp->fRec68[2]) + (dsp->fConst402 * dsp->fRec68[1]))));
			dsp->fRec67[0] = ((fSlow1 * dsp->fRec67[1]) + (fSlow2 * fabsf((dsp->fConst368 * (((dsp->fConst371 * dsp->fRec68[1]) + (dsp->fConst403 * dsp->fRec68[0])) + (dsp->fConst403 * dsp->fRec68[2]))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec67[0]))));
			dsp->fRec80[0] = (fTemp10 - (dsp->fConst420 * ((dsp->fConst423 * dsp->fRec80[2]) + (dsp->fConst424 * dsp->fRec80[1]))));
			dsp->fRec79[0] = ((dsp->fConst420 * (((dsp->fConst422 * dsp->fRec80[1]) + (dsp->fConst425 * dsp->fRec80[0])) + (dsp->fConst425 * dsp->fRec80[2]))) - (dsp->fConst418 * ((dsp->fConst426 * dsp->fRec79[2]) + (dsp->fConst427 * dsp->fRec79[1]))));
			dsp->fRec78[0] = ((dsp->fConst418 * (((dsp->fConst419 * dsp->fRec79[1]) + (dsp->fConst428 * dsp->fRec79[0])) + (dsp->fConst428 * dsp->fRec79[2]))) - (dsp->fConst416 * ((dsp->fConst429 * dsp->fRec78[2]) + (dsp->fConst430 * dsp->fRec78[1]))));
			float fTemp11 = (dsp->fConst416 * (((dsp->fConst417 * dsp->fRec78[1]) + (dsp->fConst431 * dsp->fRec78[0])) + (dsp->fConst431 * dsp->fRec78[2])));
			dsp->fRec77[0] = (fTemp11 - (dsp->fConst413 * ((dsp->fConst432 * dsp->fRec77[2]) + (dsp->fConst434 * dsp->fRec77[1]))));
			dsp->fRec76[0] = ((dsp->fConst413 * (((dsp->fConst415 * dsp->fRec77[1]) + (dsp->fConst435 * dsp->fRec77[0])) + (dsp->fConst435 * dsp->fRec77[2]))) - (dsp->fConst410 * ((dsp->fConst436 * dsp->fRec76[2]) + (dsp->fConst437 * dsp->fRec76[1]))));
			dsp->fRec75[0] = ((dsp->fConst410 * (((dsp->fConst412 * dsp->fRec76[1]) + (dsp->fConst438 * dsp->fRec76[0])) + (dsp->fConst438 * dsp->fRec76[2]))) - (dsp->fConst406 * ((dsp->fConst439 * dsp->fRec75[2]) + (dsp->fConst440 * dsp->fRec75[1]))));
			dsp->fRec74[0] = ((fSlow1 * dsp->fRec74[1]) + (fSlow2 * fabsf((dsp->fConst406 * (((dsp->fConst409 * dsp->fRec75[1]) + (dsp->fConst441 * dsp->fRec75[0])) + (dsp->fConst441 * dsp->fRec75[2]))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec74[0]))));
			dsp->fRec87[0] = (fTemp11 - (dsp->fConst458 * ((dsp->fConst461 * dsp->fRec87[2]) + (dsp->fConst462 * dsp->fRec87[1]))));
			dsp->fRec86[0] = ((dsp->fConst458 * (((dsp->fConst460 * dsp->fRec87[1]) + (dsp->fConst463 * dsp->fRec87[0])) + (dsp->fConst463 * dsp->fRec87[2]))) - (dsp->fConst456 * ((dsp->fConst464 * dsp->fRec86[2]) + (dsp->fConst465 * dsp->fRec86[1]))));
			dsp->fRec85[0] = ((dsp->fConst456 * (((dsp->fConst457 * dsp->fRec86[1]) + (dsp->fConst466 * dsp->fRec86[0])) + (dsp->fConst466 * dsp->fRec86[2]))) - (dsp->fConst454 * ((dsp->fConst467 * dsp->fRec85[2]) + (dsp->fConst468 * dsp->fRec85[1]))));
			float fTemp12 = (dsp->fConst454 * (((dsp->fConst455 * dsp->fRec85[1]) + (dsp->fConst469 * dsp->fRec85[0])) + (dsp->fConst469 * dsp->fRec85[2])));
			dsp->fRec84[0] = (fTemp12 - (dsp->fConst451 * ((dsp->fConst470 * dsp->fRec84[2]) + (dsp->fConst472 * dsp->fRec84[1]))));
			dsp->fRec83[0] = ((dsp->fConst451 * (((dsp->fConst453 * dsp->fRec84[1]) + (dsp->fConst473 * dsp->fRec84[0])) + (dsp->fConst473 * dsp->fRec84[2]))) - (dsp->fConst448 * ((dsp->fConst474 * dsp->fRec83[2]) + (dsp->fConst475 * dsp->fRec83[1]))));
			dsp->fRec82[0] = ((dsp->fConst448 * (((dsp->fConst450 * dsp->fRec83[1]) + (dsp->fConst476 * dsp->fRec83[0])) + (dsp->fConst476 * dsp->fRec83[2]))) - (dsp->fConst444 * ((dsp->fConst477 * dsp->fRec82[2]) + (dsp->fConst478 * dsp->fRec82[1]))));
			dsp->fRec81[0] = ((fSlow1 * dsp->fRec81[1]) + (fSlow2 * fabsf((dsp->fConst444 * (((dsp->fConst447 * dsp->fRec82[1]) + (dsp->fConst479 * dsp->fRec82[0])) + (dsp->fConst479 * dsp->fRec82[2]))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec81[0]))));
			dsp->fRec94[0] = (fTemp12 - (dsp->fConst496 * ((dsp->fConst499 * dsp->fRec94[2]) + (dsp->fConst500 * dsp->fRec94[1]))));
			dsp->fRec93[0] = ((dsp->fConst496 * (((dsp->fConst498 * dsp->fRec94[1]) + (dsp->fConst501 * dsp->fRec94[0])) + (dsp->fConst501 * dsp->fRec94[2]))) - (dsp->fConst494 * ((dsp->fConst502 * dsp->fRec93[2]) + (dsp->fConst503 * dsp->fRec93[1]))));
			dsp->fRec92[0] = ((dsp->fConst494 * (((dsp->fConst495 * dsp->fRec93[1]) + (dsp->fConst504 * dsp->fRec93[0])) + (dsp->fConst504 * dsp->fRec93[2]))) - (dsp->fConst492 * ((dsp->fConst505 * dsp->fRec92[2]) + (dsp->fConst506 * dsp->fRec92[1]))));
			float fTemp13 = (dsp->fConst492 * (((dsp->fConst493 * dsp->fRec92[1]) + (dsp->fConst507 * dsp->fRec92[0])) + (dsp->fConst507 * dsp->fRec92[2])));
			dsp->fRec91[0] = (fTemp13 - (dsp->fConst489 * ((dsp->fConst508 * dsp->fRec91[2]) + (dsp->fConst510 * dsp->fRec91[1]))));
			dsp->fRec90[0] = ((dsp->fConst489 * (((dsp->fConst491 * dsp->fRec91[1]) + (dsp->fConst511 * dsp->fRec91[0])) + (dsp->fConst511 * dsp->fRec91[2]))) - (dsp->fConst486 * ((dsp->fConst512 * dsp->fRec90[2]) + (dsp->fConst513 * dsp->fRec90[1]))));
			dsp->fRec89[0] = ((dsp->fConst486 * (((dsp->fConst488 * dsp->fRec90[1]) + (dsp->fConst514 * dsp->fRec90[0])) + (dsp->fConst514 * dsp->fRec90[2]))) - (dsp->fConst482 * ((dsp->fConst515 * dsp->fRec89[2]) + (dsp->fConst516 * dsp->fRec89[1]))));
			dsp->fRec88[0] = ((fSlow1 * dsp->fRec88[1]) + (fSlow2 * fabsf((dsp->fConst482 * (((dsp->fConst485 * dsp->fRec89[1]) + (dsp->fConst517 * dsp->fRec89[0])) + (dsp->fConst517 * dsp->fRec89[2]))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec88[0]))));
			dsp->fRec98[0] = (fTemp13 - (dsp->fConst522 * ((dsp->fConst525 * dsp->fRec98[2]) + (dsp->fConst526 * dsp->fRec98[1]))));
			dsp->fRec97[0] = ((dsp->fConst522 * (((dsp->fConst524 * dsp->fRec98[1]) + (dsp->fConst527 * dsp->fRec98[0])) + (dsp->fConst527 * dsp->fRec98[2]))) - (dsp->fConst520 * ((dsp->fConst528 * dsp->fRec97[2]) + (dsp->fConst529 * dsp->fRec97[1]))));
			dsp->fRec96[0] = ((dsp->fConst520 * (((dsp->fConst521 * dsp->fRec97[1]) + (dsp->fConst530 * dsp->fRec97[0])) + (dsp->fConst530 * dsp->fRec97[2]))) - (dsp->fConst518 * ((dsp->fConst531 * dsp->fRec96[2]) + (dsp->fConst532 * dsp->fRec96[1]))));
			dsp->fRec95[0] = ((fSlow1 * dsp->fRec95[1]) + (fSlow2 * fabsf((dsp->fConst518 * (((dsp->fConst519 * dsp->fRec96[1]) + (dsp->fConst533 * dsp->fRec96[0])) + (dsp->fConst533 * dsp->fRec96[2]))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec95[0]))));
			output0[i] = (FAUSTFLOAT)fTemp0;
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec10[2] = dsp->fRec10[1];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec9[2] = dsp->fRec9[1];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[2] = dsp->fRec6[1];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[2] = dsp->fRec5[1];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec17[2] = dsp->fRec17[1];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[2] = dsp->fRec14[1];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[2] = dsp->fRec22[1];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[2] = dsp->fRec21[1];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec31[2] = dsp->fRec31[1];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[2] = dsp->fRec30[1];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec29[2] = dsp->fRec29[1];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[2] = dsp->fRec26[1];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec37[2] = dsp->fRec37[1];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec35[2] = dsp->fRec35[1];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec45[2] = dsp->fRec45[1];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[2] = dsp->fRec42[1];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec41[2] = dsp->fRec41[1];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec51[2] = dsp->fRec51[1];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec50[2] = dsp->fRec50[1];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec49[2] = dsp->fRec49[1];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec48[2] = dsp->fRec48[1];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec57[2] = dsp->fRec57[1];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[2] = dsp->fRec54[1];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec66[2] = dsp->fRec66[1];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec65[2] = dsp->fRec65[1];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec64[2] = dsp->fRec64[1];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec61[2] = dsp->fRec61[1];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec72[2] = dsp->fRec72[1];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec71[2] = dsp->fRec71[1];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec70[2] = dsp->fRec70[1];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec68[2] = dsp->fRec68[1];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec80[2] = dsp->fRec80[1];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec79[2] = dsp->fRec79[1];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec78[2] = dsp->fRec78[1];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[2] = dsp->fRec75[1];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec87[2] = dsp->fRec87[1];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[2] = dsp->fRec86[1];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[2] = dsp->fRec84[1];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec83[2] = dsp->fRec83[1];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[2] = dsp->fRec82[1];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec94[2] = dsp->fRec94[1];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[2] = dsp->fRec93[1];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec92[2] = dsp->fRec92[1];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec91[2] = dsp->fRec91[1];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[2] = dsp->fRec90[1];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec98[2] = dsp->fRec98[1];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[2] = dsp->fRec97[1];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec95[1] = dsp->fRec95[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
