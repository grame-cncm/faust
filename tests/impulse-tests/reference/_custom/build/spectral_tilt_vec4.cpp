/* ------------------------------------------------------------
name: "spectral_tilt"
Code generated with Faust 2.87.10 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
#ifndef FAUST_INT_WRAP
#define FAUST_INT_WRAP
inline int faust_wrap_add(int a, int b) { return int((unsigned int)a + (unsigned int)b); }
inline int faust_wrap_sub(int a, int b) { return int((unsigned int)a - (unsigned int)b); }
inline int faust_wrap_mul(int a, int b) { return int((unsigned int)a * (unsigned int)b); }
#endif


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static double mydsp_faustpower2_f(double value) {
	return value * value;
}
static double mydsp_faustpower3_f(double value) {
	return value * value * value;
}
static double mydsp_faustpower4_f(double value) {
	return value * value * value * value;
}
static double mydsp_faustpower5_f(double value) {
	return value * value * value * value * value;
}
static double mydsp_faustpower6_f(double value) {
	return value * value * value * value * value * value;
}
static double mydsp_faustpower7_f(double value) {
	return value * value * value * value * value * value * value;
}
static double mydsp_faustpower8_f(double value) {
	return value * value * value * value * value * value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	double fRec10_perm[4];
	FAUSTFLOAT fVslider1;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider2;
	double fRec12_perm[4];
	double fRec11_perm[4];
	FAUSTFLOAT fVslider3;
	double fRec13_perm[4];
	FAUSTFLOAT fVslider4;
	double fRec14_perm[4];
	int iRec15_perm[4];
	double fRec16_perm[4];
	double fConst2;
	FAUSTFLOAT fHslider0;
	double fConst3;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fEntry0;
	int iVec0_perm[4];
	double fConst4;
	double fYec0_perm[4];
	double fConst5;
	double fYec1_perm[4];
	double fYec2_perm[4];
	double fConst6;
	double fYec3_perm[4];
	double fYec4_perm[4];
	double fYec5_perm[4];
	double fYec6_perm[4];
	double fYec7_perm[4];
	double fYec8_perm[4];
	double fYec9_perm[4];
	double fYec10_perm[4];
	double fYec11_perm[4];
	double fYec12_perm[4];
	double fYec13_perm[4];
	double fYec14_perm[4];
	double fYec15_perm[4];
	double fYec16_perm[4];
	double fYec17_perm[4];
	FAUSTFLOAT fCheckbox3;
	double fYec18_perm[4];
	double fRec9_perm[4];
	double fYec19_perm[4];
	double fRec8_perm[4];
	double fYec20_perm[4];
	double fRec7_perm[4];
	double fYec21_perm[4];
	double fRec6_perm[4];
	double fYec22_perm[4];
	double fRec5_perm[4];
	double fYec23_perm[4];
	double fRec4_perm[4];
	double fYec24_perm[4];
	double fRec3_perm[4];
	double fYec25_perm[4];
	double fRec2_perm[4];
	double fYec26_perm[4];
	double fRec1_perm[4];
	double fYec27_perm[4];
	double fRec0_perm[4];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fRec20_perm[4];
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fRec19_perm[4];
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fRec18_perm[4];
	FAUSTFLOAT fHslider3;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fRec17_perm[4];
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec27_perm[4];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec26_perm[4];
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec25_perm[4];
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec24_perm[4];
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec23_perm[4];
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec22_perm[4];
	double fConst65;
	double fConst66;
	double fConst67;
	double fRec21_perm[4];
	double fConst68;
	double fConst69;
	double fConst70;
	double fRec34_perm[4];
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fRec33_perm[4];
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fRec32_perm[4];
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fRec31_perm[4];
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fRec30_perm[4];
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fRec29_perm[4];
	double fConst103;
	double fConst104;
	double fConst105;
	double fRec28_perm[4];
	double fConst106;
	double fConst107;
	double fConst108;
	double fRec41_perm[4];
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fRec40_perm[4];
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fRec39_perm[4];
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fRec38_perm[4];
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fRec37_perm[4];
	double fConst135;
	double fConst136;
	double fConst137;
	double fConst138;
	double fConst139;
	double fConst140;
	double fRec36_perm[4];
	double fConst141;
	double fConst142;
	double fConst143;
	double fRec35_perm[4];
	double fConst144;
	double fConst145;
	double fConst146;
	double fRec48_perm[4];
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fRec47_perm[4];
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fRec46_perm[4];
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fRec45_perm[4];
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fRec44_perm[4];
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fConst177;
	double fConst178;
	double fRec43_perm[4];
	double fConst179;
	double fConst180;
	double fConst181;
	double fRec42_perm[4];
	double fConst182;
	double fConst183;
	double fConst184;
	double fRec55_perm[4];
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fRec54_perm[4];
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fRec53_perm[4];
	double fConst196;
	double fConst197;
	double fConst198;
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fRec52_perm[4];
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fRec51_perm[4];
	double fConst211;
	double fConst212;
	double fConst213;
	double fConst214;
	double fConst215;
	double fConst216;
	double fRec50_perm[4];
	double fConst217;
	double fConst218;
	double fConst219;
	double fRec49_perm[4];
	double fConst220;
	double fConst221;
	double fConst222;
	double fRec62_perm[4];
	double fConst223;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fRec61_perm[4];
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fRec60_perm[4];
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst237;
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fRec59_perm[4];
	double fConst243;
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fRec58_perm[4];
	double fConst249;
	double fConst250;
	double fConst251;
	double fConst252;
	double fConst253;
	double fConst254;
	double fRec57_perm[4];
	double fConst255;
	double fConst256;
	double fConst257;
	double fRec56_perm[4];
	double fConst258;
	double fConst259;
	double fConst260;
	double fRec69_perm[4];
	double fConst261;
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fRec68_perm[4];
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fRec67_perm[4];
	double fConst272;
	double fConst273;
	double fConst274;
	double fConst275;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fRec66_perm[4];
	double fConst281;
	double fConst282;
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fRec65_perm[4];
	double fConst287;
	double fConst288;
	double fConst289;
	double fConst290;
	double fConst291;
	double fConst292;
	double fRec64_perm[4];
	double fConst293;
	double fConst294;
	double fConst295;
	double fRec63_perm[4];
	double fConst296;
	double fConst297;
	double fConst298;
	double fRec76_perm[4];
	double fConst299;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fRec75_perm[4];
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst308;
	double fConst309;
	double fRec74_perm[4];
	double fConst310;
	double fConst311;
	double fConst312;
	double fConst313;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fRec73_perm[4];
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fRec72_perm[4];
	double fConst325;
	double fConst326;
	double fConst327;
	double fConst328;
	double fConst329;
	double fConst330;
	double fRec71_perm[4];
	double fConst331;
	double fConst332;
	double fConst333;
	double fRec70_perm[4];
	double fConst334;
	double fConst335;
	double fConst336;
	double fRec83_perm[4];
	double fConst337;
	double fConst338;
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fRec82_perm[4];
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fRec81_perm[4];
	double fConst348;
	double fConst349;
	double fConst350;
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fRec80_perm[4];
	double fConst357;
	double fConst358;
	double fConst359;
	double fConst360;
	double fConst361;
	double fConst362;
	double fRec79_perm[4];
	double fConst363;
	double fConst364;
	double fConst365;
	double fConst366;
	double fConst367;
	double fConst368;
	double fRec78_perm[4];
	double fConst369;
	double fConst370;
	double fConst371;
	double fRec77_perm[4];
	double fConst372;
	double fConst373;
	double fConst374;
	double fRec90_perm[4];
	double fConst375;
	double fConst376;
	double fConst377;
	double fConst378;
	double fConst379;
	double fConst380;
	double fRec89_perm[4];
	double fConst381;
	double fConst382;
	double fConst383;
	double fConst384;
	double fConst385;
	double fRec88_perm[4];
	double fConst386;
	double fConst387;
	double fConst388;
	double fConst389;
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fRec87_perm[4];
	double fConst395;
	double fConst396;
	double fConst397;
	double fConst398;
	double fConst399;
	double fConst400;
	double fRec86_perm[4];
	double fConst401;
	double fConst402;
	double fConst403;
	double fConst404;
	double fConst405;
	double fConst406;
	double fRec85_perm[4];
	double fConst407;
	double fConst408;
	double fConst409;
	double fRec84_perm[4];
	double fConst410;
	double fConst411;
	double fConst412;
	double fRec97_perm[4];
	double fConst413;
	double fConst414;
	double fConst415;
	double fConst416;
	double fConst417;
	double fConst418;
	double fRec96_perm[4];
	double fConst419;
	double fConst420;
	double fConst421;
	double fConst422;
	double fConst423;
	double fRec95_perm[4];
	double fConst424;
	double fConst425;
	double fConst426;
	double fConst427;
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fRec94_perm[4];
	double fConst433;
	double fConst434;
	double fConst435;
	double fConst436;
	double fConst437;
	double fConst438;
	double fRec93_perm[4];
	double fConst439;
	double fConst440;
	double fConst441;
	double fConst442;
	double fConst443;
	double fConst444;
	double fRec92_perm[4];
	double fConst445;
	double fConst446;
	double fConst447;
	double fRec91_perm[4];
	double fConst448;
	double fConst449;
	double fConst450;
	double fRec104_perm[4];
	double fConst451;
	double fConst452;
	double fConst453;
	double fConst454;
	double fConst455;
	double fConst456;
	double fRec103_perm[4];
	double fConst457;
	double fConst458;
	double fConst459;
	double fConst460;
	double fConst461;
	double fRec102_perm[4];
	double fConst462;
	double fConst463;
	double fConst464;
	double fConst465;
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fConst470;
	double fRec101_perm[4];
	double fConst471;
	double fConst472;
	double fConst473;
	double fConst474;
	double fConst475;
	double fConst476;
	double fRec100_perm[4];
	double fConst477;
	double fConst478;
	double fConst479;
	double fConst480;
	double fConst481;
	double fConst482;
	double fRec99_perm[4];
	double fConst483;
	double fConst484;
	double fConst485;
	double fRec98_perm[4];
	double fConst486;
	double fConst487;
	double fConst488;
	double fRec111_perm[4];
	double fConst489;
	double fConst490;
	double fConst491;
	double fConst492;
	double fConst493;
	double fConst494;
	double fRec110_perm[4];
	double fConst495;
	double fConst496;
	double fConst497;
	double fConst498;
	double fConst499;
	double fRec109_perm[4];
	double fConst500;
	double fConst501;
	double fConst502;
	double fConst503;
	double fConst504;
	double fConst505;
	double fConst506;
	double fConst507;
	double fConst508;
	double fRec108_perm[4];
	double fConst509;
	double fConst510;
	double fConst511;
	double fConst512;
	double fConst513;
	double fConst514;
	double fRec107_perm[4];
	double fConst515;
	double fConst516;
	double fConst517;
	double fConst518;
	double fConst519;
	double fConst520;
	double fRec106_perm[4];
	double fConst521;
	double fConst522;
	double fConst523;
	double fRec105_perm[4];
	double fConst524;
	double fConst525;
	double fConst526;
	double fRec115_perm[4];
	double fConst527;
	double fConst528;
	double fConst529;
	double fConst530;
	double fConst531;
	double fConst532;
	double fRec114_perm[4];
	double fConst533;
	double fConst534;
	double fConst535;
	double fConst536;
	double fConst537;
	double fRec113_perm[4];
	double fConst538;
	double fConst539;
	double fRec112_perm[4];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fVbargraph7;
	FAUSTFLOAT fVbargraph8;
	FAUSTFLOAT fVbargraph9;
	FAUSTFLOAT fVbargraph10;
	FAUSTFLOAT fVbargraph11;
	FAUSTFLOAT fVbargraph12;
	FAUSTFLOAT fVbargraph13;
	FAUSTFLOAT fVbargraph14;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("effect.lib/bypass1:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/bypass1:copyright", "Julius O. Smith III");
		m->declare("effect.lib/bypass1:license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("filename", "spectral_tilt.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "spectral_tilt");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/license", "STK-4.3");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "1.11");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 1.0 / fConst0;
		fConst2 = 1.0 / std::tan(0.5 / fConst0);
		fConst3 = 3.141592653589793 / fConst0;
		fConst4 = 0.25 * fConst0;
		fConst5 = 0.041666666666666664 * mydsp_faustpower2_f(fConst0);
		fConst6 = 0.005208333333333333 * mydsp_faustpower3_f(fConst0);
		fConst7 = std::tan(50265.48245743669 / fConst0);
		fConst8 = 1.0 / fConst7;
		fConst9 = 1.0 / ((fConst8 + 3.1897274020965583) / fConst7 + 4.076781969643807);
		fConst10 = (fConst8 + -3.1897274020965583) / fConst7 + 4.076781969643807;
		fConst11 = mydsp_faustpower2_f(fConst7);
		fConst12 = 1.0 / fConst11;
		fConst13 = 2.0 * (4.076781969643807 - fConst12);
		fConst14 = 0.0017661728399818856 / fConst11;
		fConst15 = fConst14 + 0.00040767818495825777;
		fConst16 = 2.0 * (0.00040767818495825777 - fConst14);
		fConst17 = 1.0 / ((fConst8 + 0.7431304601070396) / fConst7 + 1.450071084655647);
		fConst18 = (fConst8 + -0.7431304601070396) / fConst7 + 1.450071084655647;
		fConst19 = 2.0 * (1.450071084655647 - fConst12);
		fConst20 = 11.052052171507189 / fConst11;
		fConst21 = fConst20 + 1.450071084655647;
		fConst22 = 2.0 * (1.450071084655647 - fConst20);
		fConst23 = 1.0 / ((fConst8 + 0.157482159302087) / fConst7 + 0.9351401670315425);
		fConst24 = (fConst8 + -0.157482159302087) / fConst7 + 0.9351401670315425;
		fConst25 = 2.0 * (0.9351401670315425 - fConst12);
		fConst26 = 1e+03 / fConst0;
		fConst27 = 50.063807016150385 / fConst11;
		fConst28 = fConst27 + 0.9351401670315425;
		fConst29 = 2.0 * (0.9351401670315425 - fConst27);
		fConst30 = 1.0 / ((fConst8 + 0.782413046821645) / fConst7 + 0.24529150870616);
		fConst31 = (fConst8 + -0.782413046821645) / fConst7 + 0.24529150870616;
		fConst32 = 2.0 * (0.24529150870616 - fConst12);
		fConst33 = 9.9999997055e-05 / fConst11;
		fConst34 = fConst33 + 0.000433227200555;
		fConst35 = 2.0 * (0.000433227200555 - fConst33);
		fConst36 = 1.0 / ((fConst8 + 0.512478641889141) / fConst7 + 0.689621364484675);
		fConst37 = (fConst8 + -0.512478641889141) / fConst7 + 0.689621364484675;
		fConst38 = 2.0 * (0.689621364484675 - fConst12);
		fConst39 = fConst12 + 7.621731298870603;
		fConst40 = 2.0 * (7.621731298870603 - fConst12);
		fConst41 = 1.0 / ((fConst8 + 0.168404871113589) / fConst7 + 1.069358407707312);
		fConst42 = (fConst8 + -0.168404871113589) / fConst7 + 1.069358407707312;
		fConst43 = 2.0 * (1.069358407707312 - fConst12);
		fConst44 = fConst12 + 53.53615295455673;
		fConst45 = 2.0 * (53.53615295455673 - fConst12);
		fConst46 = std::tan(31665.269715622984 / fConst0);
		fConst47 = 1.0 / fConst46;
		fConst48 = 1.0 / ((fConst47 + 3.1897274020965583) / fConst46 + 4.076781969643807);
		fConst49 = (fConst47 + -3.1897274020965583) / fConst46 + 4.076781969643807;
		fConst50 = mydsp_faustpower2_f(fConst46);
		fConst51 = 1.0 / fConst50;
		fConst52 = 2.0 * (4.076781969643807 - fConst51);
		fConst53 = 0.0017661728399818856 / fConst50;
		fConst54 = fConst53 + 0.00040767818495825777;
		fConst55 = 2.0 * (0.00040767818495825777 - fConst53);
		fConst56 = 1.0 / ((fConst47 + 0.7431304601070396) / fConst46 + 1.450071084655647);
		fConst57 = (fConst47 + -0.7431304601070396) / fConst46 + 1.450071084655647;
		fConst58 = 2.0 * (1.450071084655647 - fConst51);
		fConst59 = 11.052052171507189 / fConst50;
		fConst60 = fConst59 + 1.450071084655647;
		fConst61 = 2.0 * (1.450071084655647 - fConst59);
		fConst62 = 1.0 / ((fConst47 + 0.157482159302087) / fConst46 + 0.9351401670315425);
		fConst63 = (fConst47 + -0.157482159302087) / fConst46 + 0.9351401670315425;
		fConst64 = 2.0 * (0.9351401670315425 - fConst51);
		fConst65 = 50.063807016150385 / fConst50;
		fConst66 = fConst65 + 0.9351401670315425;
		fConst67 = 2.0 * (0.9351401670315425 - fConst65);
		fConst68 = 1.0 / ((fConst47 + 0.782413046821645) / fConst46 + 0.24529150870616);
		fConst69 = (fConst47 + -0.782413046821645) / fConst46 + 0.24529150870616;
		fConst70 = 2.0 * (0.24529150870616 - fConst51);
		fConst71 = 9.9999997055e-05 / fConst50;
		fConst72 = fConst71 + 0.000433227200555;
		fConst73 = 2.0 * (0.000433227200555 - fConst71);
		fConst74 = 1.0 / ((fConst47 + 0.512478641889141) / fConst46 + 0.689621364484675);
		fConst75 = (fConst47 + -0.512478641889141) / fConst46 + 0.689621364484675;
		fConst76 = 2.0 * (0.689621364484675 - fConst51);
		fConst77 = fConst51 + 7.621731298870603;
		fConst78 = 2.0 * (7.621731298870603 - fConst51);
		fConst79 = 1.0 / ((fConst47 + 0.168404871113589) / fConst46 + 1.069358407707312);
		fConst80 = (fConst47 + -0.168404871113589) / fConst46 + 1.069358407707312;
		fConst81 = 2.0 * (1.069358407707312 - fConst51);
		fConst82 = fConst51 + 53.53615295455673;
		fConst83 = 2.0 * (53.53615295455673 - fConst51);
		fConst84 = std::tan(19947.869932656024 / fConst0);
		fConst85 = 1.0 / fConst84;
		fConst86 = 1.0 / ((fConst85 + 3.1897274020965583) / fConst84 + 4.076781969643807);
		fConst87 = (fConst85 + -3.1897274020965583) / fConst84 + 4.076781969643807;
		fConst88 = mydsp_faustpower2_f(fConst84);
		fConst89 = 1.0 / fConst88;
		fConst90 = 2.0 * (4.076781969643807 - fConst89);
		fConst91 = 0.0017661728399818856 / fConst88;
		fConst92 = fConst91 + 0.00040767818495825777;
		fConst93 = 2.0 * (0.00040767818495825777 - fConst91);
		fConst94 = 1.0 / ((fConst85 + 0.7431304601070396) / fConst84 + 1.450071084655647);
		fConst95 = (fConst85 + -0.7431304601070396) / fConst84 + 1.450071084655647;
		fConst96 = 2.0 * (1.450071084655647 - fConst89);
		fConst97 = 11.052052171507189 / fConst88;
		fConst98 = fConst97 + 1.450071084655647;
		fConst99 = 2.0 * (1.450071084655647 - fConst97);
		fConst100 = 1.0 / ((fConst85 + 0.157482159302087) / fConst84 + 0.9351401670315425);
		fConst101 = (fConst85 + -0.157482159302087) / fConst84 + 0.9351401670315425;
		fConst102 = 2.0 * (0.9351401670315425 - fConst89);
		fConst103 = 50.063807016150385 / fConst88;
		fConst104 = fConst103 + 0.9351401670315425;
		fConst105 = 2.0 * (0.9351401670315425 - fConst103);
		fConst106 = 1.0 / ((fConst85 + 0.782413046821645) / fConst84 + 0.24529150870616);
		fConst107 = (fConst85 + -0.782413046821645) / fConst84 + 0.24529150870616;
		fConst108 = 2.0 * (0.24529150870616 - fConst89);
		fConst109 = 9.9999997055e-05 / fConst88;
		fConst110 = fConst109 + 0.000433227200555;
		fConst111 = 2.0 * (0.000433227200555 - fConst109);
		fConst112 = 1.0 / ((fConst85 + 0.512478641889141) / fConst84 + 0.689621364484675);
		fConst113 = (fConst85 + -0.512478641889141) / fConst84 + 0.689621364484675;
		fConst114 = 2.0 * (0.689621364484675 - fConst89);
		fConst115 = fConst89 + 7.621731298870603;
		fConst116 = 2.0 * (7.621731298870603 - fConst89);
		fConst117 = 1.0 / ((fConst85 + 0.168404871113589) / fConst84 + 1.069358407707312);
		fConst118 = (fConst85 + -0.168404871113589) / fConst84 + 1.069358407707312;
		fConst119 = 2.0 * (1.069358407707312 - fConst89);
		fConst120 = fConst89 + 53.53615295455673;
		fConst121 = 2.0 * (53.53615295455673 - fConst89);
		fConst122 = std::tan(12566.370614359172 / fConst0);
		fConst123 = 1.0 / fConst122;
		fConst124 = 1.0 / ((fConst123 + 3.1897274020965583) / fConst122 + 4.076781969643807);
		fConst125 = (fConst123 + -3.1897274020965583) / fConst122 + 4.076781969643807;
		fConst126 = mydsp_faustpower2_f(fConst122);
		fConst127 = 1.0 / fConst126;
		fConst128 = 2.0 * (4.076781969643807 - fConst127);
		fConst129 = 0.0017661728399818856 / fConst126;
		fConst130 = fConst129 + 0.00040767818495825777;
		fConst131 = 2.0 * (0.00040767818495825777 - fConst129);
		fConst132 = 1.0 / ((fConst123 + 0.7431304601070396) / fConst122 + 1.450071084655647);
		fConst133 = (fConst123 + -0.7431304601070396) / fConst122 + 1.450071084655647;
		fConst134 = 2.0 * (1.450071084655647 - fConst127);
		fConst135 = 11.052052171507189 / fConst126;
		fConst136 = fConst135 + 1.450071084655647;
		fConst137 = 2.0 * (1.450071084655647 - fConst135);
		fConst138 = 1.0 / ((fConst123 + 0.157482159302087) / fConst122 + 0.9351401670315425);
		fConst139 = (fConst123 + -0.157482159302087) / fConst122 + 0.9351401670315425;
		fConst140 = 2.0 * (0.9351401670315425 - fConst127);
		fConst141 = 50.063807016150385 / fConst126;
		fConst142 = fConst141 + 0.9351401670315425;
		fConst143 = 2.0 * (0.9351401670315425 - fConst141);
		fConst144 = 1.0 / ((fConst123 + 0.782413046821645) / fConst122 + 0.24529150870616);
		fConst145 = (fConst123 + -0.782413046821645) / fConst122 + 0.24529150870616;
		fConst146 = 2.0 * (0.24529150870616 - fConst127);
		fConst147 = 9.9999997055e-05 / fConst126;
		fConst148 = fConst147 + 0.000433227200555;
		fConst149 = 2.0 * (0.000433227200555 - fConst147);
		fConst150 = 1.0 / ((fConst123 + 0.512478641889141) / fConst122 + 0.689621364484675);
		fConst151 = (fConst123 + -0.512478641889141) / fConst122 + 0.689621364484675;
		fConst152 = 2.0 * (0.689621364484675 - fConst127);
		fConst153 = fConst127 + 7.621731298870603;
		fConst154 = 2.0 * (7.621731298870603 - fConst127);
		fConst155 = 1.0 / ((fConst123 + 0.168404871113589) / fConst122 + 1.069358407707312);
		fConst156 = (fConst123 + -0.168404871113589) / fConst122 + 1.069358407707312;
		fConst157 = 2.0 * (1.069358407707312 - fConst127);
		fConst158 = fConst127 + 53.53615295455673;
		fConst159 = 2.0 * (53.53615295455673 - fConst127);
		fConst160 = std::tan(7916.317428905746 / fConst0);
		fConst161 = 1.0 / fConst160;
		fConst162 = 1.0 / ((fConst161 + 3.1897274020965583) / fConst160 + 4.076781969643807);
		fConst163 = (fConst161 + -3.1897274020965583) / fConst160 + 4.076781969643807;
		fConst164 = mydsp_faustpower2_f(fConst160);
		fConst165 = 1.0 / fConst164;
		fConst166 = 2.0 * (4.076781969643807 - fConst165);
		fConst167 = 0.0017661728399818856 / fConst164;
		fConst168 = fConst167 + 0.00040767818495825777;
		fConst169 = 2.0 * (0.00040767818495825777 - fConst167);
		fConst170 = 1.0 / ((fConst161 + 0.7431304601070396) / fConst160 + 1.450071084655647);
		fConst171 = (fConst161 + -0.7431304601070396) / fConst160 + 1.450071084655647;
		fConst172 = 2.0 * (1.450071084655647 - fConst165);
		fConst173 = 11.052052171507189 / fConst164;
		fConst174 = fConst173 + 1.450071084655647;
		fConst175 = 2.0 * (1.450071084655647 - fConst173);
		fConst176 = 1.0 / ((fConst161 + 0.157482159302087) / fConst160 + 0.9351401670315425);
		fConst177 = (fConst161 + -0.157482159302087) / fConst160 + 0.9351401670315425;
		fConst178 = 2.0 * (0.9351401670315425 - fConst165);
		fConst179 = 50.063807016150385 / fConst164;
		fConst180 = fConst179 + 0.9351401670315425;
		fConst181 = 2.0 * (0.9351401670315425 - fConst179);
		fConst182 = 1.0 / ((fConst161 + 0.782413046821645) / fConst160 + 0.24529150870616);
		fConst183 = (fConst161 + -0.782413046821645) / fConst160 + 0.24529150870616;
		fConst184 = 2.0 * (0.24529150870616 - fConst165);
		fConst185 = 9.9999997055e-05 / fConst164;
		fConst186 = fConst185 + 0.000433227200555;
		fConst187 = 2.0 * (0.000433227200555 - fConst185);
		fConst188 = 1.0 / ((fConst161 + 0.512478641889141) / fConst160 + 0.689621364484675);
		fConst189 = (fConst161 + -0.512478641889141) / fConst160 + 0.689621364484675;
		fConst190 = 2.0 * (0.689621364484675 - fConst165);
		fConst191 = fConst165 + 7.621731298870603;
		fConst192 = 2.0 * (7.621731298870603 - fConst165);
		fConst193 = 1.0 / ((fConst161 + 0.168404871113589) / fConst160 + 1.069358407707312);
		fConst194 = (fConst161 + -0.168404871113589) / fConst160 + 1.069358407707312;
		fConst195 = 2.0 * (1.069358407707312 - fConst165);
		fConst196 = fConst165 + 53.53615295455673;
		fConst197 = 2.0 * (53.53615295455673 - fConst165);
		fConst198 = std::tan(4986.967483164005 / fConst0);
		fConst199 = 1.0 / fConst198;
		fConst200 = 1.0 / ((fConst199 + 3.1897274020965583) / fConst198 + 4.076781969643807);
		fConst201 = (fConst199 + -3.1897274020965583) / fConst198 + 4.076781969643807;
		fConst202 = mydsp_faustpower2_f(fConst198);
		fConst203 = 1.0 / fConst202;
		fConst204 = 2.0 * (4.076781969643807 - fConst203);
		fConst205 = 0.0017661728399818856 / fConst202;
		fConst206 = fConst205 + 0.00040767818495825777;
		fConst207 = 2.0 * (0.00040767818495825777 - fConst205);
		fConst208 = 1.0 / ((fConst199 + 0.7431304601070396) / fConst198 + 1.450071084655647);
		fConst209 = (fConst199 + -0.7431304601070396) / fConst198 + 1.450071084655647;
		fConst210 = 2.0 * (1.450071084655647 - fConst203);
		fConst211 = 11.052052171507189 / fConst202;
		fConst212 = fConst211 + 1.450071084655647;
		fConst213 = 2.0 * (1.450071084655647 - fConst211);
		fConst214 = 1.0 / ((fConst199 + 0.157482159302087) / fConst198 + 0.9351401670315425);
		fConst215 = (fConst199 + -0.157482159302087) / fConst198 + 0.9351401670315425;
		fConst216 = 2.0 * (0.9351401670315425 - fConst203);
		fConst217 = 50.063807016150385 / fConst202;
		fConst218 = fConst217 + 0.9351401670315425;
		fConst219 = 2.0 * (0.9351401670315425 - fConst217);
		fConst220 = 1.0 / ((fConst199 + 0.782413046821645) / fConst198 + 0.24529150870616);
		fConst221 = (fConst199 + -0.782413046821645) / fConst198 + 0.24529150870616;
		fConst222 = 2.0 * (0.24529150870616 - fConst203);
		fConst223 = 9.9999997055e-05 / fConst202;
		fConst224 = fConst223 + 0.000433227200555;
		fConst225 = 2.0 * (0.000433227200555 - fConst223);
		fConst226 = 1.0 / ((fConst199 + 0.512478641889141) / fConst198 + 0.689621364484675);
		fConst227 = (fConst199 + -0.512478641889141) / fConst198 + 0.689621364484675;
		fConst228 = 2.0 * (0.689621364484675 - fConst203);
		fConst229 = fConst203 + 7.621731298870603;
		fConst230 = 2.0 * (7.621731298870603 - fConst203);
		fConst231 = 1.0 / ((fConst199 + 0.168404871113589) / fConst198 + 1.069358407707312);
		fConst232 = (fConst199 + -0.168404871113589) / fConst198 + 1.069358407707312;
		fConst233 = 2.0 * (1.069358407707312 - fConst203);
		fConst234 = fConst203 + 53.53615295455673;
		fConst235 = 2.0 * (53.53615295455673 - fConst203);
		fConst236 = std::tan(3141.592653589793 / fConst0);
		fConst237 = 1.0 / fConst236;
		fConst238 = 1.0 / ((fConst237 + 3.1897274020965583) / fConst236 + 4.076781969643807);
		fConst239 = (fConst237 + -3.1897274020965583) / fConst236 + 4.076781969643807;
		fConst240 = mydsp_faustpower2_f(fConst236);
		fConst241 = 1.0 / fConst240;
		fConst242 = 2.0 * (4.076781969643807 - fConst241);
		fConst243 = 0.0017661728399818856 / fConst240;
		fConst244 = fConst243 + 0.00040767818495825777;
		fConst245 = 2.0 * (0.00040767818495825777 - fConst243);
		fConst246 = 1.0 / ((fConst237 + 0.7431304601070396) / fConst236 + 1.450071084655647);
		fConst247 = (fConst237 + -0.7431304601070396) / fConst236 + 1.450071084655647;
		fConst248 = 2.0 * (1.450071084655647 - fConst241);
		fConst249 = 11.052052171507189 / fConst240;
		fConst250 = fConst249 + 1.450071084655647;
		fConst251 = 2.0 * (1.450071084655647 - fConst249);
		fConst252 = 1.0 / ((fConst237 + 0.157482159302087) / fConst236 + 0.9351401670315425);
		fConst253 = (fConst237 + -0.157482159302087) / fConst236 + 0.9351401670315425;
		fConst254 = 2.0 * (0.9351401670315425 - fConst241);
		fConst255 = 50.063807016150385 / fConst240;
		fConst256 = fConst255 + 0.9351401670315425;
		fConst257 = 2.0 * (0.9351401670315425 - fConst255);
		fConst258 = 1.0 / ((fConst237 + 0.782413046821645) / fConst236 + 0.24529150870616);
		fConst259 = (fConst237 + -0.782413046821645) / fConst236 + 0.24529150870616;
		fConst260 = 2.0 * (0.24529150870616 - fConst241);
		fConst261 = 9.9999997055e-05 / fConst240;
		fConst262 = fConst261 + 0.000433227200555;
		fConst263 = 2.0 * (0.000433227200555 - fConst261);
		fConst264 = 1.0 / ((fConst237 + 0.512478641889141) / fConst236 + 0.689621364484675);
		fConst265 = (fConst237 + -0.512478641889141) / fConst236 + 0.689621364484675;
		fConst266 = 2.0 * (0.689621364484675 - fConst241);
		fConst267 = fConst241 + 7.621731298870603;
		fConst268 = 2.0 * (7.621731298870603 - fConst241);
		fConst269 = 1.0 / ((fConst237 + 0.168404871113589) / fConst236 + 1.069358407707312);
		fConst270 = (fConst237 + -0.168404871113589) / fConst236 + 1.069358407707312;
		fConst271 = 2.0 * (1.069358407707312 - fConst241);
		fConst272 = fConst241 + 53.53615295455673;
		fConst273 = 2.0 * (53.53615295455673 - fConst241);
		fConst274 = std::tan(1979.079357226436 / fConst0);
		fConst275 = 1.0 / fConst274;
		fConst276 = 1.0 / ((fConst275 + 3.1897274020965583) / fConst274 + 4.076781969643807);
		fConst277 = (fConst275 + -3.1897274020965583) / fConst274 + 4.076781969643807;
		fConst278 = mydsp_faustpower2_f(fConst274);
		fConst279 = 1.0 / fConst278;
		fConst280 = 2.0 * (4.076781969643807 - fConst279);
		fConst281 = 0.0017661728399818856 / fConst278;
		fConst282 = fConst281 + 0.00040767818495825777;
		fConst283 = 2.0 * (0.00040767818495825777 - fConst281);
		fConst284 = 1.0 / ((fConst275 + 0.7431304601070396) / fConst274 + 1.450071084655647);
		fConst285 = (fConst275 + -0.7431304601070396) / fConst274 + 1.450071084655647;
		fConst286 = 2.0 * (1.450071084655647 - fConst279);
		fConst287 = 11.052052171507189 / fConst278;
		fConst288 = fConst287 + 1.450071084655647;
		fConst289 = 2.0 * (1.450071084655647 - fConst287);
		fConst290 = 1.0 / ((fConst275 + 0.157482159302087) / fConst274 + 0.9351401670315425);
		fConst291 = (fConst275 + -0.157482159302087) / fConst274 + 0.9351401670315425;
		fConst292 = 2.0 * (0.9351401670315425 - fConst279);
		fConst293 = 50.063807016150385 / fConst278;
		fConst294 = fConst293 + 0.9351401670315425;
		fConst295 = 2.0 * (0.9351401670315425 - fConst293);
		fConst296 = 1.0 / ((fConst275 + 0.782413046821645) / fConst274 + 0.24529150870616);
		fConst297 = (fConst275 + -0.782413046821645) / fConst274 + 0.24529150870616;
		fConst298 = 2.0 * (0.24529150870616 - fConst279);
		fConst299 = 9.9999997055e-05 / fConst278;
		fConst300 = fConst299 + 0.000433227200555;
		fConst301 = 2.0 * (0.000433227200555 - fConst299);
		fConst302 = 1.0 / ((fConst275 + 0.512478641889141) / fConst274 + 0.689621364484675);
		fConst303 = (fConst275 + -0.512478641889141) / fConst274 + 0.689621364484675;
		fConst304 = 2.0 * (0.689621364484675 - fConst279);
		fConst305 = fConst279 + 7.621731298870603;
		fConst306 = 2.0 * (7.621731298870603 - fConst279);
		fConst307 = 1.0 / ((fConst275 + 0.168404871113589) / fConst274 + 1.069358407707312);
		fConst308 = (fConst275 + -0.168404871113589) / fConst274 + 1.069358407707312;
		fConst309 = 2.0 * (1.069358407707312 - fConst279);
		fConst310 = fConst279 + 53.53615295455673;
		fConst311 = 2.0 * (53.53615295455673 - fConst279);
		fConst312 = std::tan(1246.7418707910015 / fConst0);
		fConst313 = 1.0 / fConst312;
		fConst314 = 1.0 / ((fConst313 + 3.1897274020965583) / fConst312 + 4.076781969643807);
		fConst315 = (fConst313 + -3.1897274020965583) / fConst312 + 4.076781969643807;
		fConst316 = mydsp_faustpower2_f(fConst312);
		fConst317 = 1.0 / fConst316;
		fConst318 = 2.0 * (4.076781969643807 - fConst317);
		fConst319 = 0.0017661728399818856 / fConst316;
		fConst320 = fConst319 + 0.00040767818495825777;
		fConst321 = 2.0 * (0.00040767818495825777 - fConst319);
		fConst322 = 1.0 / ((fConst313 + 0.7431304601070396) / fConst312 + 1.450071084655647);
		fConst323 = (fConst313 + -0.7431304601070396) / fConst312 + 1.450071084655647;
		fConst324 = 2.0 * (1.450071084655647 - fConst317);
		fConst325 = 11.052052171507189 / fConst316;
		fConst326 = fConst325 + 1.450071084655647;
		fConst327 = 2.0 * (1.450071084655647 - fConst325);
		fConst328 = 1.0 / ((fConst313 + 0.157482159302087) / fConst312 + 0.9351401670315425);
		fConst329 = (fConst313 + -0.157482159302087) / fConst312 + 0.9351401670315425;
		fConst330 = 2.0 * (0.9351401670315425 - fConst317);
		fConst331 = 50.063807016150385 / fConst316;
		fConst332 = fConst331 + 0.9351401670315425;
		fConst333 = 2.0 * (0.9351401670315425 - fConst331);
		fConst334 = 1.0 / ((fConst313 + 0.782413046821645) / fConst312 + 0.24529150870616);
		fConst335 = (fConst313 + -0.782413046821645) / fConst312 + 0.24529150870616;
		fConst336 = 2.0 * (0.24529150870616 - fConst317);
		fConst337 = 9.9999997055e-05 / fConst316;
		fConst338 = fConst337 + 0.000433227200555;
		fConst339 = 2.0 * (0.000433227200555 - fConst337);
		fConst340 = 1.0 / ((fConst313 + 0.512478641889141) / fConst312 + 0.689621364484675);
		fConst341 = (fConst313 + -0.512478641889141) / fConst312 + 0.689621364484675;
		fConst342 = 2.0 * (0.689621364484675 - fConst317);
		fConst343 = fConst317 + 7.621731298870603;
		fConst344 = 2.0 * (7.621731298870603 - fConst317);
		fConst345 = 1.0 / ((fConst313 + 0.168404871113589) / fConst312 + 1.069358407707312);
		fConst346 = (fConst313 + -0.168404871113589) / fConst312 + 1.069358407707312;
		fConst347 = 2.0 * (1.069358407707312 - fConst317);
		fConst348 = fConst317 + 53.53615295455673;
		fConst349 = 2.0 * (53.53615295455673 - fConst317);
		fConst350 = std::tan(785.3981633974482 / fConst0);
		fConst351 = 1.0 / fConst350;
		fConst352 = 1.0 / ((fConst351 + 3.1897274020965583) / fConst350 + 4.076781969643807);
		fConst353 = (fConst351 + -3.1897274020965583) / fConst350 + 4.076781969643807;
		fConst354 = mydsp_faustpower2_f(fConst350);
		fConst355 = 1.0 / fConst354;
		fConst356 = 2.0 * (4.076781969643807 - fConst355);
		fConst357 = 0.0017661728399818856 / fConst354;
		fConst358 = fConst357 + 0.00040767818495825777;
		fConst359 = 2.0 * (0.00040767818495825777 - fConst357);
		fConst360 = 1.0 / ((fConst351 + 0.7431304601070396) / fConst350 + 1.450071084655647);
		fConst361 = (fConst351 + -0.7431304601070396) / fConst350 + 1.450071084655647;
		fConst362 = 2.0 * (1.450071084655647 - fConst355);
		fConst363 = 11.052052171507189 / fConst354;
		fConst364 = fConst363 + 1.450071084655647;
		fConst365 = 2.0 * (1.450071084655647 - fConst363);
		fConst366 = 1.0 / ((fConst351 + 0.157482159302087) / fConst350 + 0.9351401670315425);
		fConst367 = (fConst351 + -0.157482159302087) / fConst350 + 0.9351401670315425;
		fConst368 = 2.0 * (0.9351401670315425 - fConst355);
		fConst369 = 50.063807016150385 / fConst354;
		fConst370 = fConst369 + 0.9351401670315425;
		fConst371 = 2.0 * (0.9351401670315425 - fConst369);
		fConst372 = 1.0 / ((fConst351 + 0.782413046821645) / fConst350 + 0.24529150870616);
		fConst373 = (fConst351 + -0.782413046821645) / fConst350 + 0.24529150870616;
		fConst374 = 2.0 * (0.24529150870616 - fConst355);
		fConst375 = 9.9999997055e-05 / fConst354;
		fConst376 = fConst375 + 0.000433227200555;
		fConst377 = 2.0 * (0.000433227200555 - fConst375);
		fConst378 = 1.0 / ((fConst351 + 0.512478641889141) / fConst350 + 0.689621364484675);
		fConst379 = (fConst351 + -0.512478641889141) / fConst350 + 0.689621364484675;
		fConst380 = 2.0 * (0.689621364484675 - fConst355);
		fConst381 = fConst355 + 7.621731298870603;
		fConst382 = 2.0 * (7.621731298870603 - fConst355);
		fConst383 = 1.0 / ((fConst351 + 0.168404871113589) / fConst350 + 1.069358407707312);
		fConst384 = (fConst351 + -0.168404871113589) / fConst350 + 1.069358407707312;
		fConst385 = 2.0 * (1.069358407707312 - fConst355);
		fConst386 = fConst355 + 53.53615295455673;
		fConst387 = 2.0 * (53.53615295455673 - fConst355);
		fConst388 = std::tan(494.769839306609 / fConst0);
		fConst389 = 1.0 / fConst388;
		fConst390 = 1.0 / ((fConst389 + 3.1897274020965583) / fConst388 + 4.076781969643807);
		fConst391 = (fConst389 + -3.1897274020965583) / fConst388 + 4.076781969643807;
		fConst392 = mydsp_faustpower2_f(fConst388);
		fConst393 = 1.0 / fConst392;
		fConst394 = 2.0 * (4.076781969643807 - fConst393);
		fConst395 = 0.0017661728399818856 / fConst392;
		fConst396 = fConst395 + 0.00040767818495825777;
		fConst397 = 2.0 * (0.00040767818495825777 - fConst395);
		fConst398 = 1.0 / ((fConst389 + 0.7431304601070396) / fConst388 + 1.450071084655647);
		fConst399 = (fConst389 + -0.7431304601070396) / fConst388 + 1.450071084655647;
		fConst400 = 2.0 * (1.450071084655647 - fConst393);
		fConst401 = 11.052052171507189 / fConst392;
		fConst402 = fConst401 + 1.450071084655647;
		fConst403 = 2.0 * (1.450071084655647 - fConst401);
		fConst404 = 1.0 / ((fConst389 + 0.157482159302087) / fConst388 + 0.9351401670315425);
		fConst405 = (fConst389 + -0.157482159302087) / fConst388 + 0.9351401670315425;
		fConst406 = 2.0 * (0.9351401670315425 - fConst393);
		fConst407 = 50.063807016150385 / fConst392;
		fConst408 = fConst407 + 0.9351401670315425;
		fConst409 = 2.0 * (0.9351401670315425 - fConst407);
		fConst410 = 1.0 / ((fConst389 + 0.782413046821645) / fConst388 + 0.24529150870616);
		fConst411 = (fConst389 + -0.782413046821645) / fConst388 + 0.24529150870616;
		fConst412 = 2.0 * (0.24529150870616 - fConst393);
		fConst413 = 9.9999997055e-05 / fConst392;
		fConst414 = fConst413 + 0.000433227200555;
		fConst415 = 2.0 * (0.000433227200555 - fConst413);
		fConst416 = 1.0 / ((fConst389 + 0.512478641889141) / fConst388 + 0.689621364484675);
		fConst417 = (fConst389 + -0.512478641889141) / fConst388 + 0.689621364484675;
		fConst418 = 2.0 * (0.689621364484675 - fConst393);
		fConst419 = fConst393 + 7.621731298870603;
		fConst420 = 2.0 * (7.621731298870603 - fConst393);
		fConst421 = 1.0 / ((fConst389 + 0.168404871113589) / fConst388 + 1.069358407707312);
		fConst422 = (fConst389 + -0.168404871113589) / fConst388 + 1.069358407707312;
		fConst423 = 2.0 * (1.069358407707312 - fConst393);
		fConst424 = fConst393 + 53.53615295455673;
		fConst425 = 2.0 * (53.53615295455673 - fConst393);
		fConst426 = std::tan(311.68546769775037 / fConst0);
		fConst427 = 1.0 / fConst426;
		fConst428 = 1.0 / ((fConst427 + 3.1897274020965583) / fConst426 + 4.076781969643807);
		fConst429 = (fConst427 + -3.1897274020965583) / fConst426 + 4.076781969643807;
		fConst430 = mydsp_faustpower2_f(fConst426);
		fConst431 = 1.0 / fConst430;
		fConst432 = 2.0 * (4.076781969643807 - fConst431);
		fConst433 = 0.0017661728399818856 / fConst430;
		fConst434 = fConst433 + 0.00040767818495825777;
		fConst435 = 2.0 * (0.00040767818495825777 - fConst433);
		fConst436 = 1.0 / ((fConst427 + 0.7431304601070396) / fConst426 + 1.450071084655647);
		fConst437 = (fConst427 + -0.7431304601070396) / fConst426 + 1.450071084655647;
		fConst438 = 2.0 * (1.450071084655647 - fConst431);
		fConst439 = 11.052052171507189 / fConst430;
		fConst440 = fConst439 + 1.450071084655647;
		fConst441 = 2.0 * (1.450071084655647 - fConst439);
		fConst442 = 1.0 / ((fConst427 + 0.157482159302087) / fConst426 + 0.9351401670315425);
		fConst443 = (fConst427 + -0.157482159302087) / fConst426 + 0.9351401670315425;
		fConst444 = 2.0 * (0.9351401670315425 - fConst431);
		fConst445 = 50.063807016150385 / fConst430;
		fConst446 = fConst445 + 0.9351401670315425;
		fConst447 = 2.0 * (0.9351401670315425 - fConst445);
		fConst448 = 1.0 / ((fConst427 + 0.782413046821645) / fConst426 + 0.24529150870616);
		fConst449 = (fConst427 + -0.782413046821645) / fConst426 + 0.24529150870616;
		fConst450 = 2.0 * (0.24529150870616 - fConst431);
		fConst451 = 9.9999997055e-05 / fConst430;
		fConst452 = fConst451 + 0.000433227200555;
		fConst453 = 2.0 * (0.000433227200555 - fConst451);
		fConst454 = 1.0 / ((fConst427 + 0.512478641889141) / fConst426 + 0.689621364484675);
		fConst455 = (fConst427 + -0.512478641889141) / fConst426 + 0.689621364484675;
		fConst456 = 2.0 * (0.689621364484675 - fConst431);
		fConst457 = fConst431 + 7.621731298870603;
		fConst458 = 2.0 * (7.621731298870603 - fConst431);
		fConst459 = 1.0 / ((fConst427 + 0.168404871113589) / fConst426 + 1.069358407707312);
		fConst460 = (fConst427 + -0.168404871113589) / fConst426 + 1.069358407707312;
		fConst461 = 2.0 * (1.069358407707312 - fConst431);
		fConst462 = fConst431 + 53.53615295455673;
		fConst463 = 2.0 * (53.53615295455673 - fConst431);
		fConst464 = std::tan(196.34954084936206 / fConst0);
		fConst465 = 1.0 / fConst464;
		fConst466 = 1.0 / ((fConst465 + 3.1897274020965583) / fConst464 + 4.076781969643807);
		fConst467 = (fConst465 + -3.1897274020965583) / fConst464 + 4.076781969643807;
		fConst468 = mydsp_faustpower2_f(fConst464);
		fConst469 = 1.0 / fConst468;
		fConst470 = 2.0 * (4.076781969643807 - fConst469);
		fConst471 = 0.0017661728399818856 / fConst468;
		fConst472 = fConst471 + 0.00040767818495825777;
		fConst473 = 2.0 * (0.00040767818495825777 - fConst471);
		fConst474 = 1.0 / ((fConst465 + 0.7431304601070396) / fConst464 + 1.450071084655647);
		fConst475 = (fConst465 + -0.7431304601070396) / fConst464 + 1.450071084655647;
		fConst476 = 2.0 * (1.450071084655647 - fConst469);
		fConst477 = 11.052052171507189 / fConst468;
		fConst478 = fConst477 + 1.450071084655647;
		fConst479 = 2.0 * (1.450071084655647 - fConst477);
		fConst480 = 1.0 / ((fConst465 + 0.157482159302087) / fConst464 + 0.9351401670315425);
		fConst481 = (fConst465 + -0.157482159302087) / fConst464 + 0.9351401670315425;
		fConst482 = 2.0 * (0.9351401670315425 - fConst469);
		fConst483 = 50.063807016150385 / fConst468;
		fConst484 = fConst483 + 0.9351401670315425;
		fConst485 = 2.0 * (0.9351401670315425 - fConst483);
		fConst486 = 1.0 / ((fConst465 + 0.782413046821645) / fConst464 + 0.24529150870616);
		fConst487 = (fConst465 + -0.782413046821645) / fConst464 + 0.24529150870616;
		fConst488 = 2.0 * (0.24529150870616 - fConst469);
		fConst489 = 9.9999997055e-05 / fConst468;
		fConst490 = fConst489 + 0.000433227200555;
		fConst491 = 2.0 * (0.000433227200555 - fConst489);
		fConst492 = 1.0 / ((fConst465 + 0.512478641889141) / fConst464 + 0.689621364484675);
		fConst493 = (fConst465 + -0.512478641889141) / fConst464 + 0.689621364484675;
		fConst494 = 2.0 * (0.689621364484675 - fConst469);
		fConst495 = fConst469 + 7.621731298870603;
		fConst496 = 2.0 * (7.621731298870603 - fConst469);
		fConst497 = 1.0 / ((fConst465 + 0.168404871113589) / fConst464 + 1.069358407707312);
		fConst498 = (fConst465 + -0.168404871113589) / fConst464 + 1.069358407707312;
		fConst499 = 2.0 * (1.069358407707312 - fConst469);
		fConst500 = fConst469 + 53.53615295455673;
		fConst501 = 2.0 * (53.53615295455673 - fConst469);
		fConst502 = std::tan(123.69245982665232 / fConst0);
		fConst503 = 1.0 / fConst502;
		fConst504 = 1.0 / ((fConst503 + 3.1897274020965583) / fConst502 + 4.076781969643807);
		fConst505 = (fConst503 + -3.1897274020965583) / fConst502 + 4.076781969643807;
		fConst506 = mydsp_faustpower2_f(fConst502);
		fConst507 = 1.0 / fConst506;
		fConst508 = 2.0 * (4.076781969643807 - fConst507);
		fConst509 = 0.0017661728399818856 / fConst506;
		fConst510 = fConst509 + 0.00040767818495825777;
		fConst511 = 2.0 * (0.00040767818495825777 - fConst509);
		fConst512 = 1.0 / ((fConst503 + 0.7431304601070396) / fConst502 + 1.450071084655647);
		fConst513 = (fConst503 + -0.7431304601070396) / fConst502 + 1.450071084655647;
		fConst514 = 2.0 * (1.450071084655647 - fConst507);
		fConst515 = 11.052052171507189 / fConst506;
		fConst516 = fConst515 + 1.450071084655647;
		fConst517 = 2.0 * (1.450071084655647 - fConst515);
		fConst518 = 1.0 / ((fConst503 + 0.157482159302087) / fConst502 + 0.9351401670315425);
		fConst519 = (fConst503 + -0.157482159302087) / fConst502 + 0.9351401670315425;
		fConst520 = 2.0 * (0.9351401670315425 - fConst507);
		fConst521 = 50.063807016150385 / fConst506;
		fConst522 = fConst521 + 0.9351401670315425;
		fConst523 = 2.0 * (0.9351401670315425 - fConst521);
		fConst524 = 1.0 / ((fConst503 + 0.782413046821645) / fConst502 + 0.24529150870616);
		fConst525 = (fConst503 + -0.782413046821645) / fConst502 + 0.24529150870616;
		fConst526 = 2.0 * (0.24529150870616 - fConst507);
		fConst527 = 9.9999997055e-05 / fConst506;
		fConst528 = fConst527 + 0.000433227200555;
		fConst529 = 2.0 * (0.000433227200555 - fConst527);
		fConst530 = 1.0 / ((fConst503 + 0.512478641889141) / fConst502 + 0.689621364484675);
		fConst531 = (fConst503 + -0.512478641889141) / fConst502 + 0.689621364484675;
		fConst532 = 2.0 * (0.689621364484675 - fConst507);
		fConst533 = fConst507 + 7.621731298870603;
		fConst534 = 2.0 * (7.621731298870603 - fConst507);
		fConst535 = 1.0 / ((fConst503 + 0.168404871113589) / fConst502 + 1.069358407707312);
		fConst536 = (fConst503 + -0.168404871113589) / fConst502 + 1.069358407707312;
		fConst537 = 2.0 * (1.069358407707312 - fConst507);
		fConst538 = fConst507 + 53.53615295455673;
		fConst539 = 2.0 * (53.53615295455673 - fConst507);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(-2e+01);
		fVslider1 = static_cast<FAUSTFLOAT>(0.1);
		fVslider2 = static_cast<FAUSTFLOAT>(49.0);
		fVslider3 = static_cast<FAUSTFLOAT>(-0.1);
		fVslider4 = static_cast<FAUSTFLOAT>(0.1);
		fHslider0 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider1 = static_cast<FAUSTFLOAT>(5e+03);
		fHslider2 = static_cast<FAUSTFLOAT>(-0.5);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry0 = static_cast<FAUSTFLOAT>(2.0);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider3 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider4 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec10_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec12_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec11_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec13_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec14_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			iRec15_perm[l5] = 0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec16_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			iVec0_perm[l7] = 0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fYec0_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fYec1_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fYec2_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fYec3_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fYec4_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fYec5_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fYec6_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fYec7_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fYec8_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fYec9_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fYec10_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fYec11_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fYec12_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fYec13_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fYec14_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fYec15_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fYec16_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fYec17_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fYec18_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec9_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fYec19_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec8_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fYec20_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec7_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fYec21_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec6_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fYec22_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec5_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fYec23_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec4_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fYec24_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec3_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fYec25_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec2_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fYec26_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec1_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fYec27_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec0_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec20_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec19_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec18_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec17_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec27_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec26_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec25_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec24_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec23_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec22_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec21_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec34_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec33_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec32_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec31_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec30_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec29_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec28_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec41_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec40_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec39_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec38_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec37_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec36_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec35_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec48_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fRec47_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec46_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec45_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec44_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec43_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec42_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec55_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec54_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec53_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec52_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec51_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec50_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec49_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec62_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec61_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec60_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec59_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec58_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec57_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec56_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec69_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec68_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec67_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec66_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec65_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fRec64_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec63_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec76_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec75_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec74_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec73_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec72_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec71_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec70_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec83_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec82_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = faust_wrap_add(l108, 1)) {
			fRec81_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = faust_wrap_add(l109, 1)) {
			fRec80_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = faust_wrap_add(l110, 1)) {
			fRec79_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = faust_wrap_add(l111, 1)) {
			fRec78_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = faust_wrap_add(l112, 1)) {
			fRec77_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = faust_wrap_add(l113, 1)) {
			fRec90_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = faust_wrap_add(l114, 1)) {
			fRec89_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = faust_wrap_add(l115, 1)) {
			fRec88_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = faust_wrap_add(l116, 1)) {
			fRec87_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = faust_wrap_add(l117, 1)) {
			fRec86_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = faust_wrap_add(l118, 1)) {
			fRec85_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = faust_wrap_add(l119, 1)) {
			fRec84_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = faust_wrap_add(l120, 1)) {
			fRec97_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = faust_wrap_add(l121, 1)) {
			fRec96_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = faust_wrap_add(l122, 1)) {
			fRec95_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = faust_wrap_add(l123, 1)) {
			fRec94_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = faust_wrap_add(l124, 1)) {
			fRec93_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = faust_wrap_add(l125, 1)) {
			fRec92_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = faust_wrap_add(l126, 1)) {
			fRec91_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = faust_wrap_add(l127, 1)) {
			fRec104_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = faust_wrap_add(l128, 1)) {
			fRec103_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = faust_wrap_add(l129, 1)) {
			fRec102_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = faust_wrap_add(l130, 1)) {
			fRec101_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = faust_wrap_add(l131, 1)) {
			fRec100_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = faust_wrap_add(l132, 1)) {
			fRec99_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = faust_wrap_add(l133, 1)) {
			fRec98_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = faust_wrap_add(l134, 1)) {
			fRec111_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = faust_wrap_add(l135, 1)) {
			fRec110_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = faust_wrap_add(l136, 1)) {
			fRec109_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = faust_wrap_add(l137, 1)) {
			fRec108_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = faust_wrap_add(l138, 1)) {
			fRec107_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = faust_wrap_add(l139, 1)) {
			fRec106_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = faust_wrap_add(l140, 1)) {
			fRec105_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = faust_wrap_add(l141, 1)) {
			fRec115_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 4; l142 = faust_wrap_add(l142, 1)) {
			fRec114_perm[l142] = 0.0;
		}
		for (int l143 = 0; l143 < 4; l143 = faust_wrap_add(l143, 1)) {
			fRec113_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = faust_wrap_add(l144, 1)) {
			fRec112_perm[l144] = 0.0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("spectral_tilt");
		ui_interface->declare(0, "1", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for spectral_tilt_demo");
		ui_interface->openVerticalBox("Spectral Tilt Filter");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->addHorizontalSlider("Slope of Spectral Tilt across Band", &fHslider2, FAUSTFLOAT(-0.5), FAUSTFLOAT(-1.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.001));
		ui_interface->declare(0, "1", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for spectral_tilt_demo");
		ui_interface->openVerticalBox("Spectral Tilt Filter");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->addCheckButton("Bypass Spectral Tilt", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Start Frequency", &fHslider0, FAUSTFLOAT(1e+02), FAUSTFLOAT(2e+01), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Width", &fHslider1, FAUSTFLOAT(5e+03), FAUSTFLOAT(1e+02), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillator.lib for sawtooth_demo");
		ui_interface->openVerticalBox("Test Signal");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillator.lib for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fVslider0, FAUSTFLOAT(-2e+01), FAUSTFLOAT(-1.2e+02), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider2, "2", "");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fVslider2, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fVslider2, FAUSTFLOAT(49.0), FAUSTFLOAT(1.0), FAUSTFLOAT(88.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentage frequency-shift up or down for second oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider3, FAUSTFLOAT(-0.1), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider4, "4", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider4, FAUSTFLOAT(0.1), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider1, "5", "");
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider1, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider1, FAUSTFLOAT(0.1), FAUSTFLOAT(0.001), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.001));
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtootn aliasing suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, FAUSTFLOAT(2.0), FAUSTFLOAT(1.0), FAUSTFLOAT(4.0), FAUSTFLOAT(1.0));
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fCheckbox2, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on the left)", &fCheckbox2);
		ui_interface->declare(&fCheckbox3, "1", "");
		ui_interface->declare(&fCheckbox3, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox3);
		ui_interface->declare(&fCheckbox1, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise selection above)", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for spectral_level_demo");
		ui_interface->openVerticalBox("Spectrum Analyzer");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph14, "0", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph14, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph13, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph12, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph11, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph10, "4", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph10, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph9, "5", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph9, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph8, "6", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph8, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph7, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph6, "8", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph8", &fVbargraph6, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph5, "9", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph9", &fVbargraph5, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph4, "10", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph10", &fVbargraph4, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph3, "11", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph11", &fVbargraph3, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph2, "12", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph12", &fVbargraph2, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph1, "13", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph13", &fVbargraph1, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph0, "14", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph14", &fVbargraph0, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider3, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider4, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fSlow1 = static_cast<double>(fVslider1);
		double fSlow2 = ((fSlow1 > 0.0) ? std::exp(-(fConst1 / fSlow1)) : 0.0);
		double fSlow3 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fVslider2) + -49.0)) * (1.0 - fSlow2);
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fZec0[4];
		double fZec1[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fSlow4 = 0.01 * static_cast<double>(fVslider3) + 1.0;
		double fZec2[4];
		double fZec3[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fSlow5 = 0.01 * static_cast<double>(fVslider4) + 1.0;
		double fZec4[4];
		double fZec5[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		int iRec15_tmp[8];
		int* iRec15 = &iRec15_tmp[4];
		double fZec6[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fSlow6 = static_cast<double>(fHslider0);
		double fSlow7 = 6.283185307179586 * fSlow6;
		double fSlow8 = 1.0 / (fConst2 + fSlow7);
		double fSlow9 = fSlow7 - fConst2;
		double fSlow10 = std::pow((fSlow6 + static_cast<double>(fHslider1)) / fSlow6, 0.1111111111111111);
		double fSlow11 = static_cast<double>(fHslider2);
		double fSlow12 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, -fSlow11));
		double fSlow13 = std::tan(fConst3 * fSlow6);
		double fSlow14 = 6.283185307179586 * (fSlow6 * fSlow12 / fSlow13);
		double fSlow15 = fConst2 + fSlow14;
		int iSlow16 = static_cast<int>(static_cast<double>(fCheckbox0));
		int iSlow17 = static_cast<int>(static_cast<double>(fCheckbox1));
		int iSlow18 = static_cast<int>(static_cast<double>(fCheckbox2));
		int iSlow19 = static_cast<int>(static_cast<double>(fEntry0) + -1.0);
		int iSlow20 = iSlow19 >= 2;
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		int iSlow21 = iSlow19 >= 1;
		double fZec7[4];
		double fZec8[4];
		double fZec9[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		int iSlow22 = iSlow19 >= 3;
		double fZec10[4];
		double fZec11[4];
		double fYec1_tmp[8];
		double* fYec1 = &fYec1_tmp[4];
		double fYec2_tmp[8];
		double* fYec2 = &fYec2_tmp[4];
		double fZec12[4];
		double fYec3_tmp[8];
		double* fYec3 = &fYec3_tmp[4];
		double fYec4_tmp[8];
		double* fYec4 = &fYec4_tmp[4];
		double fYec5_tmp[8];
		double* fYec5 = &fYec5_tmp[4];
		double fZec13[4];
		double fZec14[4];
		double fYec6_tmp[8];
		double* fYec6 = &fYec6_tmp[4];
		double fZec15[4];
		double fYec7_tmp[8];
		double* fYec7 = &fYec7_tmp[4];
		double fYec8_tmp[8];
		double* fYec8 = &fYec8_tmp[4];
		double fYec9_tmp[8];
		double* fYec9 = &fYec9_tmp[4];
		double fYec10_tmp[8];
		double* fYec10 = &fYec10_tmp[4];
		double fYec11_tmp[8];
		double* fYec11 = &fYec11_tmp[4];
		double fZec16[4];
		double fZec17[4];
		double fYec12_tmp[8];
		double* fYec12 = &fYec12_tmp[4];
		double fZec18[4];
		double fYec13_tmp[8];
		double* fYec13 = &fYec13_tmp[4];
		double fYec14_tmp[8];
		double* fYec14 = &fYec14_tmp[4];
		double fYec15_tmp[8];
		double* fYec15 = &fYec15_tmp[4];
		double fYec16_tmp[8];
		double* fYec16 = &fYec16_tmp[4];
		double fYec17_tmp[8];
		double* fYec17 = &fYec17_tmp[4];
		int iSlow23 = static_cast<int>(static_cast<double>(fCheckbox3));
		double fZec19[4];
		double fYec18_tmp[8];
		double* fYec18 = &fYec18_tmp[4];
		double fSlow24 = fSlow14 - fConst2;
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fSlow25 = std::tan(fConst3 * fSlow6 * fSlow10);
		double fSlow26 = 6.283185307179586 * (fSlow6 * fSlow25 / fSlow13);
		double fSlow27 = 1.0 / (fConst2 + fSlow26);
		double fSlow28 = fSlow26 - fConst2;
		double fSlow29 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 1.0 - fSlow11));
		double fSlow30 = 6.283185307179586 * (fSlow6 * fSlow29 / fSlow13);
		double fSlow31 = fSlow13 * (fConst2 + fSlow30) / fSlow12;
		double fSlow32 = fSlow30 - fConst2;
		double fSlow33 = fSlow13 / fSlow12;
		double fYec19_tmp[8];
		double* fYec19 = &fYec19_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow34 = std::tan(fConst3 * fSlow6 * mydsp_faustpower2_f(fSlow10));
		double fSlow35 = 6.283185307179586 * (fSlow6 * fSlow34 / fSlow13);
		double fSlow36 = 1.0 / (fConst2 + fSlow35);
		double fSlow37 = fSlow35 - fConst2;
		double fSlow38 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 2.0 - fSlow11));
		double fSlow39 = 6.283185307179586 * (fSlow6 * fSlow38 / fSlow13);
		double fSlow40 = fSlow25 * (fConst2 + fSlow39) / fSlow29;
		double fSlow41 = fSlow39 - fConst2;
		double fSlow42 = fSlow25 / fSlow29;
		double fYec20_tmp[8];
		double* fYec20 = &fYec20_tmp[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fSlow43 = std::tan(fConst3 * fSlow6 * mydsp_faustpower3_f(fSlow10));
		double fSlow44 = 6.283185307179586 * (fSlow6 * fSlow43 / fSlow13);
		double fSlow45 = 1.0 / (fConst2 + fSlow44);
		double fSlow46 = fSlow44 - fConst2;
		double fSlow47 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 3.0 - fSlow11));
		double fSlow48 = 6.283185307179586 * (fSlow6 * fSlow47 / fSlow13);
		double fSlow49 = fSlow34 * (fConst2 + fSlow48) / fSlow38;
		double fSlow50 = fSlow48 - fConst2;
		double fSlow51 = fSlow34 / fSlow38;
		double fYec21_tmp[8];
		double* fYec21 = &fYec21_tmp[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow52 = std::tan(fConst3 * fSlow6 * mydsp_faustpower4_f(fSlow10));
		double fSlow53 = 6.283185307179586 * (fSlow6 * fSlow52 / fSlow13);
		double fSlow54 = 1.0 / (fConst2 + fSlow53);
		double fSlow55 = fSlow53 - fConst2;
		double fSlow56 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 4.0 - fSlow11));
		double fSlow57 = 6.283185307179586 * (fSlow6 * fSlow56 / fSlow13);
		double fSlow58 = fSlow43 * (fConst2 + fSlow57) / fSlow47;
		double fSlow59 = fSlow57 - fConst2;
		double fSlow60 = fSlow43 / fSlow47;
		double fYec22_tmp[8];
		double* fYec22 = &fYec22_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow61 = std::tan(fConst3 * fSlow6 * mydsp_faustpower5_f(fSlow10));
		double fSlow62 = 6.283185307179586 * (fSlow6 * fSlow61 / fSlow13);
		double fSlow63 = 1.0 / (fConst2 + fSlow62);
		double fSlow64 = fSlow62 - fConst2;
		double fSlow65 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 5.0 - fSlow11));
		double fSlow66 = 6.283185307179586 * (fSlow6 * fSlow65 / fSlow13);
		double fSlow67 = fSlow52 * (fConst2 + fSlow66) / fSlow56;
		double fSlow68 = fSlow66 - fConst2;
		double fSlow69 = fSlow52 / fSlow56;
		double fYec23_tmp[8];
		double* fYec23 = &fYec23_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow70 = std::tan(fConst3 * fSlow6 * mydsp_faustpower6_f(fSlow10));
		double fSlow71 = 6.283185307179586 * (fSlow6 * fSlow70 / fSlow13);
		double fSlow72 = 1.0 / (fConst2 + fSlow71);
		double fSlow73 = fSlow71 - fConst2;
		double fSlow74 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 6.0 - fSlow11));
		double fSlow75 = 6.283185307179586 * (fSlow6 * fSlow74 / fSlow13);
		double fSlow76 = fSlow61 * (fConst2 + fSlow75) / fSlow65;
		double fSlow77 = fSlow75 - fConst2;
		double fSlow78 = fSlow61 / fSlow65;
		double fYec24_tmp[8];
		double* fYec24 = &fYec24_tmp[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fSlow79 = std::tan(fConst3 * fSlow6 * mydsp_faustpower7_f(fSlow10));
		double fSlow80 = 6.283185307179586 * (fSlow6 * fSlow79 / fSlow13);
		double fSlow81 = 1.0 / (fConst2 + fSlow80);
		double fSlow82 = fSlow80 - fConst2;
		double fSlow83 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 7.0 - fSlow11));
		double fSlow84 = 6.283185307179586 * (fSlow6 * fSlow83 / fSlow13);
		double fSlow85 = fSlow70 * (fConst2 + fSlow84) / fSlow74;
		double fSlow86 = fSlow84 - fConst2;
		double fSlow87 = fSlow70 / fSlow74;
		double fYec25_tmp[8];
		double* fYec25 = &fYec25_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow88 = std::tan(fConst3 * fSlow6 * mydsp_faustpower8_f(fSlow10));
		double fSlow89 = 6.283185307179586 * (fSlow6 * fSlow88 / fSlow13);
		double fSlow90 = 1.0 / (fConst2 + fSlow89);
		double fSlow91 = fSlow89 - fConst2;
		double fSlow92 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 8.0 - fSlow11));
		double fSlow93 = 6.283185307179586 * (fSlow6 * fSlow92 / fSlow13);
		double fSlow94 = fSlow79 * (fConst2 + fSlow93) / fSlow83;
		double fSlow95 = fSlow93 - fConst2;
		double fSlow96 = fSlow79 / fSlow83;
		double fYec26_tmp[8];
		double* fYec26 = &fYec26_tmp[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow97 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 9.0));
		double fSlow98 = 6.283185307179586 * (fSlow6 * fSlow97 / fSlow13);
		double fSlow99 = 1.0 / (fConst2 + fSlow98);
		double fSlow100 = fSlow98 - fConst2;
		double fSlow101 = std::tan(fConst3 * fSlow6 * std::pow(fSlow10, 9.0 - fSlow11));
		double fSlow102 = 6.283185307179586 * (fSlow6 * fSlow101 / fSlow13);
		double fSlow103 = fSlow88 * (fConst2 + fSlow102) / fSlow92;
		double fSlow104 = fSlow102 - fConst2;
		double fSlow105 = fSlow88 / fSlow92;
		double fYec27_tmp[8];
		double* fYec27 = &fYec27_tmp[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow106 = fSlow97 / fSlow101;
		double fZec20[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fSlow107 = static_cast<double>(fHslider3);
		double fSlow108 = (((0.001 * fSlow107) > 0.0) ? std::exp(-(fConst26 / fSlow107)) : 0.0);
		double fSlow109 = 1.0 - fSlow108;
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fZec21[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fZec22[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fZec23[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec48_tmp[8];
		double* fRec48 = &fRec48_tmp[4];
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fZec24[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec55_tmp[8];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[8];
		double* fRec54 = &fRec54_tmp[4];
		double fRec53_tmp[8];
		double* fRec53 = &fRec53_tmp[4];
		double fZec25[4];
		double fRec52_tmp[8];
		double* fRec52 = &fRec52_tmp[4];
		double fRec51_tmp[8];
		double* fRec51 = &fRec51_tmp[4];
		double fRec50_tmp[8];
		double* fRec50 = &fRec50_tmp[4];
		double fRec49_tmp[8];
		double* fRec49 = &fRec49_tmp[4];
		double fRec62_tmp[8];
		double* fRec62 = &fRec62_tmp[4];
		double fRec61_tmp[8];
		double* fRec61 = &fRec61_tmp[4];
		double fRec60_tmp[8];
		double* fRec60 = &fRec60_tmp[4];
		double fZec26[4];
		double fRec59_tmp[8];
		double* fRec59 = &fRec59_tmp[4];
		double fRec58_tmp[8];
		double* fRec58 = &fRec58_tmp[4];
		double fRec57_tmp[8];
		double* fRec57 = &fRec57_tmp[4];
		double fRec56_tmp[8];
		double* fRec56 = &fRec56_tmp[4];
		double fRec69_tmp[8];
		double* fRec69 = &fRec69_tmp[4];
		double fRec68_tmp[8];
		double* fRec68 = &fRec68_tmp[4];
		double fRec67_tmp[8];
		double* fRec67 = &fRec67_tmp[4];
		double fZec27[4];
		double fRec66_tmp[8];
		double* fRec66 = &fRec66_tmp[4];
		double fRec65_tmp[8];
		double* fRec65 = &fRec65_tmp[4];
		double fRec64_tmp[8];
		double* fRec64 = &fRec64_tmp[4];
		double fRec63_tmp[8];
		double* fRec63 = &fRec63_tmp[4];
		double fRec76_tmp[8];
		double* fRec76 = &fRec76_tmp[4];
		double fRec75_tmp[8];
		double* fRec75 = &fRec75_tmp[4];
		double fRec74_tmp[8];
		double* fRec74 = &fRec74_tmp[4];
		double fZec28[4];
		double fRec73_tmp[8];
		double* fRec73 = &fRec73_tmp[4];
		double fRec72_tmp[8];
		double* fRec72 = &fRec72_tmp[4];
		double fRec71_tmp[8];
		double* fRec71 = &fRec71_tmp[4];
		double fRec70_tmp[8];
		double* fRec70 = &fRec70_tmp[4];
		double fRec83_tmp[8];
		double* fRec83 = &fRec83_tmp[4];
		double fRec82_tmp[8];
		double* fRec82 = &fRec82_tmp[4];
		double fRec81_tmp[8];
		double* fRec81 = &fRec81_tmp[4];
		double fZec29[4];
		double fRec80_tmp[8];
		double* fRec80 = &fRec80_tmp[4];
		double fRec79_tmp[8];
		double* fRec79 = &fRec79_tmp[4];
		double fRec78_tmp[8];
		double* fRec78 = &fRec78_tmp[4];
		double fRec77_tmp[8];
		double* fRec77 = &fRec77_tmp[4];
		double fRec90_tmp[8];
		double* fRec90 = &fRec90_tmp[4];
		double fRec89_tmp[8];
		double* fRec89 = &fRec89_tmp[4];
		double fRec88_tmp[8];
		double* fRec88 = &fRec88_tmp[4];
		double fZec30[4];
		double fRec87_tmp[8];
		double* fRec87 = &fRec87_tmp[4];
		double fRec86_tmp[8];
		double* fRec86 = &fRec86_tmp[4];
		double fRec85_tmp[8];
		double* fRec85 = &fRec85_tmp[4];
		double fRec84_tmp[8];
		double* fRec84 = &fRec84_tmp[4];
		double fRec97_tmp[8];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[8];
		double* fRec96 = &fRec96_tmp[4];
		double fRec95_tmp[8];
		double* fRec95 = &fRec95_tmp[4];
		double fZec31[4];
		double fRec94_tmp[8];
		double* fRec94 = &fRec94_tmp[4];
		double fRec93_tmp[8];
		double* fRec93 = &fRec93_tmp[4];
		double fRec92_tmp[8];
		double* fRec92 = &fRec92_tmp[4];
		double fRec91_tmp[8];
		double* fRec91 = &fRec91_tmp[4];
		double fRec104_tmp[8];
		double* fRec104 = &fRec104_tmp[4];
		double fRec103_tmp[8];
		double* fRec103 = &fRec103_tmp[4];
		double fRec102_tmp[8];
		double* fRec102 = &fRec102_tmp[4];
		double fZec32[4];
		double fRec101_tmp[8];
		double* fRec101 = &fRec101_tmp[4];
		double fRec100_tmp[8];
		double* fRec100 = &fRec100_tmp[4];
		double fRec99_tmp[8];
		double* fRec99 = &fRec99_tmp[4];
		double fRec98_tmp[8];
		double* fRec98 = &fRec98_tmp[4];
		double fRec111_tmp[8];
		double* fRec111 = &fRec111_tmp[4];
		double fRec110_tmp[8];
		double* fRec110 = &fRec110_tmp[4];
		double fRec109_tmp[8];
		double* fRec109 = &fRec109_tmp[4];
		double fZec33[4];
		double fRec108_tmp[8];
		double* fRec108 = &fRec108_tmp[4];
		double fRec107_tmp[8];
		double* fRec107 = &fRec107_tmp[4];
		double fRec106_tmp[8];
		double* fRec106 = &fRec106_tmp[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec115_tmp[8];
		double* fRec115 = &fRec115_tmp[4];
		double fRec114_tmp[8];
		double* fRec114 = &fRec114_tmp[4];
		double fRec113_tmp[8];
		double* fRec113 = &fRec113_tmp[4];
		double fRec112_tmp[8];
		double* fRec112 = &fRec112_tmp[4];
		double fSlow110 = static_cast<double>(fHslider4);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec10_tmp[j0] = fRec10_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = fSlow0 + 0.999 * fRec10[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec10_perm[j1] = fRec10_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec12_tmp[j2] = fRec12_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fRec12[faust_wrap_sub(i, 1)] * fSlow2 + fSlow3;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec12_perm[j3] = fRec12_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec12[i]));
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec11_tmp[j4] = fRec11_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec11[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec11[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec11_perm[j5] = fRec11_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec12[i]));
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec13_tmp[j6] = fRec13_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec13[faust_wrap_sub(i, 1)] + fConst1 * fZec2[i];
				fRec13[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec13_perm[j7] = fRec13_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec12[i]));
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec14_tmp[j8] = fRec14_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fRec14[faust_wrap_sub(i, 1)] + fConst1 * fZec4[i];
				fRec14[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec14_perm[j9] = fRec14_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iRec15_tmp[j10] = iRec15_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec15[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec15[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iRec15_perm[j11] = iRec15_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec15[i]);
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec16_tmp[j12] = fRec16_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = 0.5221894 * fRec16[faust_wrap_sub(i, 3)] + fZec6[i] + 2.494956002 * fRec16[faust_wrap_sub(i, 1)] - 2.017265875 * fRec16[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec16_perm[j13] = fRec16_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				iVec0_tmp[j14] = iVec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				iVec0_perm[j15] = iVec0_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 2.0 * fRec11[i];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fZec7[i] + -1.0;
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fYec0_tmp[j16] = fYec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = mydsp_faustpower2_f(fZec8[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fYec0_perm[j17] = fYec0_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 2)]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = mydsp_faustpower3_f(fZec8[i]);
			}
			/* Vectorizable loop 18 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fYec1_tmp[j18] = fYec1_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fZec11[i] + (1.0 - fZec7[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fYec1_perm[j19] = fYec1_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 19 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fYec2_tmp[j20] = fYec2_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[i] = (fZec11[i] + (1.0 - (fZec7[i] + fYec1[faust_wrap_sub(i, 1)]))) / fZec0[i];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fYec2_perm[j21] = fYec2_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 3)]);
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fYec3_tmp[j22] = fYec3_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fYec3_perm[j23] = fYec3_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 22 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fYec4_tmp[j24] = fYec4_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[i] = (fYec3[i] - fYec3[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fYec4_perm[j25] = fYec4_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Vectorizable loop 23 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fYec5_tmp[j26] = fYec5_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[i] = (fYec4[i] - fYec4[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fYec5_perm[j27] = fYec5_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = 2.0 * fRec13[i];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fZec13[i] + -1.0;
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fYec6_tmp[j28] = fYec6_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[i] = mydsp_faustpower2_f(fZec14[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fYec6_perm[j29] = fYec6_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = mydsp_faustpower3_f(fZec14[i]);
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fYec7_tmp[j30] = fYec7_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[i] = fZec15[i] + (1.0 - fZec13[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fYec7_perm[j31] = fYec7_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fYec8_tmp[j32] = fYec8_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[i] = (fZec15[i] + (1.0 - (fZec13[i] + fYec7[faust_wrap_sub(i, 1)]))) / fZec2[i];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fYec8_perm[j33] = fYec8_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 30 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fYec9_tmp[j34] = fYec9_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fYec9_perm[j35] = fYec9_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 31 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fYec10_tmp[j36] = fYec10_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[i] = (fYec9[i] - fYec9[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fYec10_perm[j37] = fYec10_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 32 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fYec11_tmp[j38] = fYec11_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[i] = (fYec10[i] - fYec10[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fYec11_perm[j39] = fYec11_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = 2.0 * fRec14[i];
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fZec16[i] + -1.0;
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fYec12_tmp[j40] = fYec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[i] = mydsp_faustpower2_f(fZec17[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fYec12_perm[j41] = fYec12_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = mydsp_faustpower3_f(fZec17[i]);
			}
			/* Vectorizable loop 37 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fYec13_tmp[j42] = fYec13_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[i] = fZec18[i] + (1.0 - fZec16[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fYec13_perm[j43] = fYec13_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 38 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec14_tmp[j44] = fYec14_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[i] = (fZec18[i] + (1.0 - (fZec16[i] + fYec13[faust_wrap_sub(i, 1)]))) / fZec4[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec14_perm[j45] = fYec14_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 39 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fYec15_tmp[j46] = fYec15_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fYec15_perm[j47] = fYec15_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Vectorizable loop 40 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fYec16_tmp[j48] = fYec16_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[i] = (fYec15[i] - fYec15[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fYec16_perm[j49] = fYec16_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fYec17_tmp[j50] = fYec17_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[i] = (fYec16[i] - fYec16[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fYec17_perm[j51] = fYec17_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fRec10[i] * ((iSlow17) ? static_cast<double>(input0[i]) : ((iSlow18) ? ((iSlow23) ? 0.049922035 * fRec16[i] + 0.050612699 * fRec16[faust_wrap_sub(i, 2)] - (0.095993537 * fRec16[faust_wrap_sub(i, 1)] + 0.004408786 * fRec16[faust_wrap_sub(i, 3)]) : fZec6[i]) : 0.3333333333333333 * fRec10[i] * (((iSlow20) ? ((iSlow22) ? fConst6 * (fZec12[i] * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst5 * (fZec10[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow21) ? fConst4 * (fZec9[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec8[i])) + ((iSlow20) ? ((iSlow22) ? fConst6 * (fZec12[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec2[i]) : fConst5 * (fZec10[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec2[i])) : ((iSlow21) ? fConst4 * (fZec9[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec2[i]) : fZec14[i])) + ((iSlow20) ? ((iSlow22) ? fConst6 * (fZec12[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec4[i]) : fConst5 * (fZec10[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec4[i])) : ((iSlow21) ? fConst4 * (fZec9[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec4[i]) : fZec17[i])))));
			}
			/* Vectorizable loop 43 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec18_tmp[j52] = fYec18_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[i] = ((iSlow16) ? 0.0 : fZec19[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec18_perm[j53] = fYec18_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec9_tmp[j54] = fRec9_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = -(fSlow8 * (fSlow9 * fRec9[faust_wrap_sub(i, 1)] - (fSlow15 * fYec18[i] + fSlow24 * fYec18[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec9_perm[j55] = fRec9_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 45 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fYec19_tmp[j56] = fYec19_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[i] = fSlow33 * fRec9[i];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fYec19_perm[j57] = fYec19_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec8_tmp[j58] = fRec8_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = -(fSlow27 * (fSlow28 * fRec8[faust_wrap_sub(i, 1)] - (fSlow31 * fRec9[i] + fSlow32 * fYec19[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec8_perm[j59] = fRec8_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fYec20_tmp[j60] = fYec20_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[i] = fSlow42 * fRec8[i];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fYec20_perm[j61] = fYec20_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec7_tmp[j62] = fRec7_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = -(fSlow36 * (fSlow37 * fRec7[faust_wrap_sub(i, 1)] - (fSlow40 * fRec8[i] + fSlow41 * fYec20[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec7_perm[j63] = fRec7_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 49 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fYec21_tmp[j64] = fYec21_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[i] = fSlow51 * fRec7[i];
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fYec21_perm[j65] = fYec21_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec6_tmp[j66] = fRec6_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = -(fSlow45 * (fSlow46 * fRec6[faust_wrap_sub(i, 1)] - (fSlow49 * fRec7[i] + fSlow50 * fYec21[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec6_perm[j67] = fRec6_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 51 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fYec22_tmp[j68] = fYec22_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[i] = fSlow60 * fRec6[i];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fYec22_perm[j69] = fYec22_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec5_tmp[j70] = fRec5_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = -(fSlow54 * (fSlow55 * fRec5[faust_wrap_sub(i, 1)] - (fSlow58 * fRec6[i] + fSlow59 * fYec22[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec5_perm[j71] = fRec5_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 53 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fYec23_tmp[j72] = fYec23_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[i] = fSlow69 * fRec5[i];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fYec23_perm[j73] = fYec23_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec4_tmp[j74] = fRec4_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = -(fSlow63 * (fSlow64 * fRec4[faust_wrap_sub(i, 1)] - (fSlow67 * fRec5[i] + fSlow68 * fYec23[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec4_perm[j75] = fRec4_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 55 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fYec24_tmp[j76] = fYec24_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec24[i] = fSlow78 * fRec4[i];
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fYec24_perm[j77] = fYec24_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec3_tmp[j78] = fRec3_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = -(fSlow72 * (fSlow73 * fRec3[faust_wrap_sub(i, 1)] - (fSlow76 * fRec4[i] + fSlow77 * fYec24[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec3_perm[j79] = fRec3_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 57 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fYec25_tmp[j80] = fYec25_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec25[i] = fSlow87 * fRec3[i];
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fYec25_perm[j81] = fYec25_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec2_tmp[j82] = fRec2_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = -(fSlow81 * (fSlow82 * fRec2[faust_wrap_sub(i, 1)] - (fSlow85 * fRec3[i] + fSlow86 * fYec25[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec2_perm[j83] = fRec2_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 59 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fYec26_tmp[j84] = fYec26_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec26[i] = fSlow96 * fRec2[i];
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fYec26_perm[j85] = fYec26_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec1_tmp[j86] = fRec1_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = -(fSlow90 * (fSlow91 * fRec1[faust_wrap_sub(i, 1)] - (fSlow94 * fRec2[i] + fSlow95 * fYec26[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec1_perm[j87] = fRec1_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 61 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fYec27_tmp[j88] = fYec27_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec27[i] = fSlow105 * fRec1[i];
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fYec27_perm[j89] = fYec27_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec0_tmp[j90] = fRec0_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = -(fSlow99 * (fSlow100 * fRec0[faust_wrap_sub(i, 1)] - (fSlow103 * fRec1[i] + fSlow104 * fYec27[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec0_perm[j91] = fRec0_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = ((iSlow16) ? fZec19[i] : fSlow106 * fRec0[i]);
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec27_tmp[j100] = fRec27_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fZec20[i] - fConst30 * (fConst31 * fRec27[faust_wrap_sub(i, 2)] + fConst32 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec27_perm[j101] = fRec27_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec26_tmp[j102] = fRec26_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst30 * (fConst34 * fRec27[i] + fConst35 * fRec27[faust_wrap_sub(i, 1)] + fConst34 * fRec27[faust_wrap_sub(i, 2)]) - fConst36 * (fConst37 * fRec26[faust_wrap_sub(i, 2)] + fConst38 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec26_perm[j103] = fRec26_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec25_tmp[j104] = fRec25_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fConst36 * (fConst39 * fRec26[i] + fConst40 * fRec26[faust_wrap_sub(i, 1)] + fConst39 * fRec26[faust_wrap_sub(i, 2)]) - fConst41 * (fConst42 * fRec25[faust_wrap_sub(i, 2)] + fConst43 * fRec25[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec25_perm[j105] = fRec25_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = fConst41 * (fConst44 * fRec25[i] + fConst45 * fRec25[faust_wrap_sub(i, 1)] + fConst44 * fRec25[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec34_tmp[j114] = fRec34_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fZec21[i] - fConst68 * (fConst69 * fRec34[faust_wrap_sub(i, 2)] + fConst70 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec34_perm[j115] = fRec34_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec33_tmp[j116] = fRec33_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst68 * (fConst72 * fRec34[i] + fConst73 * fRec34[faust_wrap_sub(i, 1)] + fConst72 * fRec34[faust_wrap_sub(i, 2)]) - fConst74 * (fConst75 * fRec33[faust_wrap_sub(i, 2)] + fConst76 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec33_perm[j117] = fRec33_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec32_tmp[j118] = fRec32_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fConst74 * (fConst77 * fRec33[i] + fConst78 * fRec33[faust_wrap_sub(i, 1)] + fConst77 * fRec33[faust_wrap_sub(i, 2)]) - fConst79 * (fConst80 * fRec32[faust_wrap_sub(i, 2)] + fConst81 * fRec32[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec32_perm[j119] = fRec32_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fConst79 * (fConst82 * fRec32[i] + fConst83 * fRec32[faust_wrap_sub(i, 1)] + fConst82 * fRec32[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec41_tmp[j128] = fRec41_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fZec22[i] - fConst106 * (fConst107 * fRec41[faust_wrap_sub(i, 2)] + fConst108 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec41_perm[j129] = fRec41_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec40_tmp[j130] = fRec40_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst106 * (fConst110 * fRec41[i] + fConst111 * fRec41[faust_wrap_sub(i, 1)] + fConst110 * fRec41[faust_wrap_sub(i, 2)]) - fConst112 * (fConst113 * fRec40[faust_wrap_sub(i, 2)] + fConst114 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec40_perm[j131] = fRec40_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec39_tmp[j132] = fRec39_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fConst112 * (fConst115 * fRec40[i] + fConst116 * fRec40[faust_wrap_sub(i, 1)] + fConst115 * fRec40[faust_wrap_sub(i, 2)]) - fConst117 * (fConst118 * fRec39[faust_wrap_sub(i, 2)] + fConst119 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec39_perm[j133] = fRec39_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fConst117 * (fConst120 * fRec39[i] + fConst121 * fRec39[faust_wrap_sub(i, 1)] + fConst120 * fRec39[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec48_tmp[j142] = fRec48_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fZec23[i] - fConst144 * (fConst145 * fRec48[faust_wrap_sub(i, 2)] + fConst146 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec48_perm[j143] = fRec48_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec47_tmp[j144] = fRec47_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst144 * (fConst148 * fRec48[i] + fConst149 * fRec48[faust_wrap_sub(i, 1)] + fConst148 * fRec48[faust_wrap_sub(i, 2)]) - fConst150 * (fConst151 * fRec47[faust_wrap_sub(i, 2)] + fConst152 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec47_perm[j145] = fRec47_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec46_tmp[j146] = fRec46_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fConst150 * (fConst153 * fRec47[i] + fConst154 * fRec47[faust_wrap_sub(i, 1)] + fConst153 * fRec47[faust_wrap_sub(i, 2)]) - fConst155 * (fConst156 * fRec46[faust_wrap_sub(i, 2)] + fConst157 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec46_perm[j147] = fRec46_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fConst155 * (fConst158 * fRec46[i] + fConst159 * fRec46[faust_wrap_sub(i, 1)] + fConst158 * fRec46[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec55_tmp[j156] = fRec55_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fZec24[i] - fConst182 * (fConst183 * fRec55[faust_wrap_sub(i, 2)] + fConst184 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec55_perm[j157] = fRec55_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec54_tmp[j158] = fRec54_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst182 * (fConst186 * fRec55[i] + fConst187 * fRec55[faust_wrap_sub(i, 1)] + fConst186 * fRec55[faust_wrap_sub(i, 2)]) - fConst188 * (fConst189 * fRec54[faust_wrap_sub(i, 2)] + fConst190 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec54_perm[j159] = fRec54_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec53_tmp[j160] = fRec53_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fConst188 * (fConst191 * fRec54[i] + fConst192 * fRec54[faust_wrap_sub(i, 1)] + fConst191 * fRec54[faust_wrap_sub(i, 2)]) - fConst193 * (fConst194 * fRec53[faust_wrap_sub(i, 2)] + fConst195 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec53_perm[j161] = fRec53_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = fConst193 * (fConst196 * fRec53[i] + fConst197 * fRec53[faust_wrap_sub(i, 1)] + fConst196 * fRec53[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec62_tmp[j170] = fRec62_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fZec25[i] - fConst220 * (fConst221 * fRec62[faust_wrap_sub(i, 2)] + fConst222 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec62_perm[j171] = fRec62_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec61_tmp[j172] = fRec61_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst220 * (fConst224 * fRec62[i] + fConst225 * fRec62[faust_wrap_sub(i, 1)] + fConst224 * fRec62[faust_wrap_sub(i, 2)]) - fConst226 * (fConst227 * fRec61[faust_wrap_sub(i, 2)] + fConst228 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec61_perm[j173] = fRec61_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec60_tmp[j174] = fRec60_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fConst226 * (fConst229 * fRec61[i] + fConst230 * fRec61[faust_wrap_sub(i, 1)] + fConst229 * fRec61[faust_wrap_sub(i, 2)]) - fConst231 * (fConst232 * fRec60[faust_wrap_sub(i, 2)] + fConst233 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec60_perm[j175] = fRec60_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fConst231 * (fConst234 * fRec60[i] + fConst235 * fRec60[faust_wrap_sub(i, 1)] + fConst234 * fRec60[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec69_tmp[j184] = fRec69_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fZec26[i] - fConst258 * (fConst259 * fRec69[faust_wrap_sub(i, 2)] + fConst260 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec69_perm[j185] = fRec69_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec68_tmp[j186] = fRec68_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst258 * (fConst262 * fRec69[i] + fConst263 * fRec69[faust_wrap_sub(i, 1)] + fConst262 * fRec69[faust_wrap_sub(i, 2)]) - fConst264 * (fConst265 * fRec68[faust_wrap_sub(i, 2)] + fConst266 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec68_perm[j187] = fRec68_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec67_tmp[j188] = fRec67_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fConst264 * (fConst267 * fRec68[i] + fConst268 * fRec68[faust_wrap_sub(i, 1)] + fConst267 * fRec68[faust_wrap_sub(i, 2)]) - fConst269 * (fConst270 * fRec67[faust_wrap_sub(i, 2)] + fConst271 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec67_perm[j189] = fRec67_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = fConst269 * (fConst272 * fRec67[i] + fConst273 * fRec67[faust_wrap_sub(i, 1)] + fConst272 * fRec67[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec76_tmp[j198] = fRec76_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fZec27[i] - fConst296 * (fConst297 * fRec76[faust_wrap_sub(i, 2)] + fConst298 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec76_perm[j199] = fRec76_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec75_tmp[j200] = fRec75_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst296 * (fConst300 * fRec76[i] + fConst301 * fRec76[faust_wrap_sub(i, 1)] + fConst300 * fRec76[faust_wrap_sub(i, 2)]) - fConst302 * (fConst303 * fRec75[faust_wrap_sub(i, 2)] + fConst304 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec75_perm[j201] = fRec75_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec74_tmp[j202] = fRec74_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fConst302 * (fConst305 * fRec75[i] + fConst306 * fRec75[faust_wrap_sub(i, 1)] + fConst305 * fRec75[faust_wrap_sub(i, 2)]) - fConst307 * (fConst308 * fRec74[faust_wrap_sub(i, 2)] + fConst309 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec74_perm[j203] = fRec74_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = fConst307 * (fConst310 * fRec74[i] + fConst311 * fRec74[faust_wrap_sub(i, 1)] + fConst310 * fRec74[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec83_tmp[j212] = fRec83_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fZec28[i] - fConst334 * (fConst335 * fRec83[faust_wrap_sub(i, 2)] + fConst336 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec83_perm[j213] = fRec83_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec82_tmp[j214] = fRec82_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst334 * (fConst338 * fRec83[i] + fConst339 * fRec83[faust_wrap_sub(i, 1)] + fConst338 * fRec83[faust_wrap_sub(i, 2)]) - fConst340 * (fConst341 * fRec82[faust_wrap_sub(i, 2)] + fConst342 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec82_perm[j215] = fRec82_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec81_tmp[j216] = fRec81_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fConst340 * (fConst343 * fRec82[i] + fConst344 * fRec82[faust_wrap_sub(i, 1)] + fConst343 * fRec82[faust_wrap_sub(i, 2)]) - fConst345 * (fConst346 * fRec81[faust_wrap_sub(i, 2)] + fConst347 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec81_perm[j217] = fRec81_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = fConst345 * (fConst348 * fRec81[i] + fConst349 * fRec81[faust_wrap_sub(i, 1)] + fConst348 * fRec81[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec90_tmp[j226] = fRec90_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fZec29[i] - fConst372 * (fConst373 * fRec90[faust_wrap_sub(i, 2)] + fConst374 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec90_perm[j227] = fRec90_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec89_tmp[j228] = fRec89_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst372 * (fConst376 * fRec90[i] + fConst377 * fRec90[faust_wrap_sub(i, 1)] + fConst376 * fRec90[faust_wrap_sub(i, 2)]) - fConst378 * (fConst379 * fRec89[faust_wrap_sub(i, 2)] + fConst380 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec89_perm[j229] = fRec89_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec88_tmp[j230] = fRec88_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fConst378 * (fConst381 * fRec89[i] + fConst382 * fRec89[faust_wrap_sub(i, 1)] + fConst381 * fRec89[faust_wrap_sub(i, 2)]) - fConst383 * (fConst384 * fRec88[faust_wrap_sub(i, 2)] + fConst385 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec88_perm[j231] = fRec88_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = fConst383 * (fConst386 * fRec88[i] + fConst387 * fRec88[faust_wrap_sub(i, 1)] + fConst386 * fRec88[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec97_tmp[j240] = fRec97_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fZec30[i] - fConst410 * (fConst411 * fRec97[faust_wrap_sub(i, 2)] + fConst412 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec97_perm[j241] = fRec97_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec96_tmp[j242] = fRec96_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst410 * (fConst414 * fRec97[i] + fConst415 * fRec97[faust_wrap_sub(i, 1)] + fConst414 * fRec97[faust_wrap_sub(i, 2)]) - fConst416 * (fConst417 * fRec96[faust_wrap_sub(i, 2)] + fConst418 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec96_perm[j243] = fRec96_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec95_tmp[j244] = fRec95_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fConst416 * (fConst419 * fRec96[i] + fConst420 * fRec96[faust_wrap_sub(i, 1)] + fConst419 * fRec96[faust_wrap_sub(i, 2)]) - fConst421 * (fConst422 * fRec95[faust_wrap_sub(i, 2)] + fConst423 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec95_perm[j245] = fRec95_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fConst421 * (fConst424 * fRec95[i] + fConst425 * fRec95[faust_wrap_sub(i, 1)] + fConst424 * fRec95[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec104_tmp[j254] = fRec104_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fZec31[i] - fConst448 * (fConst449 * fRec104[faust_wrap_sub(i, 2)] + fConst450 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec104_perm[j255] = fRec104_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec103_tmp[j256] = fRec103_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst448 * (fConst452 * fRec104[i] + fConst453 * fRec104[faust_wrap_sub(i, 1)] + fConst452 * fRec104[faust_wrap_sub(i, 2)]) - fConst454 * (fConst455 * fRec103[faust_wrap_sub(i, 2)] + fConst456 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec103_perm[j257] = fRec103_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec102_tmp[j258] = fRec102_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fConst454 * (fConst457 * fRec103[i] + fConst458 * fRec103[faust_wrap_sub(i, 1)] + fConst457 * fRec103[faust_wrap_sub(i, 2)]) - fConst459 * (fConst460 * fRec102[faust_wrap_sub(i, 2)] + fConst461 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec102_perm[j259] = fRec102_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = fConst459 * (fConst462 * fRec102[i] + fConst463 * fRec102[faust_wrap_sub(i, 1)] + fConst462 * fRec102[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec101_tmp[j260] = fRec101_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec32[i] - fConst466 * (fConst467 * fRec101[faust_wrap_sub(i, 2)] + fConst470 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec101_perm[j261] = fRec101_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec100_tmp[j262] = fRec100_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst466 * (fConst472 * fRec101[i] + fConst473 * fRec101[faust_wrap_sub(i, 1)] + fConst472 * fRec101[faust_wrap_sub(i, 2)]) - fConst474 * (fConst475 * fRec100[faust_wrap_sub(i, 2)] + fConst476 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec100_perm[j263] = fRec100_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec99_tmp[j264] = fRec99_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst474 * (fConst478 * fRec100[i] + fConst479 * fRec100[faust_wrap_sub(i, 1)] + fConst478 * fRec100[faust_wrap_sub(i, 2)]) - fConst480 * (fConst481 * fRec99[faust_wrap_sub(i, 2)] + fConst482 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec99_perm[j265] = fRec99_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Recursive loop 115 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec98_tmp[j266] = fRec98_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fSlow108 * fRec98[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst480 * (fConst484 * fRec99[i] + fConst485 * fRec99[faust_wrap_sub(i, 1)] + fConst484 * fRec99[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec98_perm[j267] = fRec98_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec111_tmp[j268] = fRec111_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fZec32[i] - fConst486 * (fConst487 * fRec111[faust_wrap_sub(i, 2)] + fConst488 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec111_perm[j269] = fRec111_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec110_tmp[j270] = fRec110_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst486 * (fConst490 * fRec111[i] + fConst491 * fRec111[faust_wrap_sub(i, 1)] + fConst490 * fRec111[faust_wrap_sub(i, 2)]) - fConst492 * (fConst493 * fRec110[faust_wrap_sub(i, 2)] + fConst494 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec110_perm[j271] = fRec110_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec109_tmp[j272] = fRec109_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fConst492 * (fConst495 * fRec110[i] + fConst496 * fRec110[faust_wrap_sub(i, 1)] + fConst495 * fRec110[faust_wrap_sub(i, 2)]) - fConst497 * (fConst498 * fRec109[faust_wrap_sub(i, 2)] + fConst499 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec109_perm[j273] = fRec109_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = fConst497 * (fConst500 * fRec109[i] + fConst501 * fRec109[faust_wrap_sub(i, 1)] + fConst500 * fRec109[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec108_tmp[j274] = fRec108_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fZec33[i] - fConst504 * (fConst505 * fRec108[faust_wrap_sub(i, 2)] + fConst508 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec108_perm[j275] = fRec108_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec107_tmp[j276] = fRec107_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst504 * (fConst510 * fRec108[i] + fConst511 * fRec108[faust_wrap_sub(i, 1)] + fConst510 * fRec108[faust_wrap_sub(i, 2)]) - fConst512 * (fConst513 * fRec107[faust_wrap_sub(i, 2)] + fConst514 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec107_perm[j277] = fRec107_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec106_tmp[j278] = fRec106_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fConst512 * (fConst516 * fRec107[i] + fConst517 * fRec107[faust_wrap_sub(i, 1)] + fConst516 * fRec107[faust_wrap_sub(i, 2)]) - fConst518 * (fConst519 * fRec106[faust_wrap_sub(i, 2)] + fConst520 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec106_perm[j279] = fRec106_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec105_tmp[j280] = fRec105_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fSlow108 * fRec105[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst518 * (fConst522 * fRec106[i] + fConst523 * fRec106[faust_wrap_sub(i, 1)] + fConst522 * fRec106[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec105_perm[j281] = fRec105_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec115_tmp[j282] = fRec115_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fZec33[i] - fConst524 * (fConst525 * fRec115[faust_wrap_sub(i, 2)] + fConst526 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec115_perm[j283] = fRec115_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec114_tmp[j284] = fRec114_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst524 * (fConst528 * fRec115[i] + fConst529 * fRec115[faust_wrap_sub(i, 1)] + fConst528 * fRec115[faust_wrap_sub(i, 2)]) - fConst530 * (fConst531 * fRec114[faust_wrap_sub(i, 2)] + fConst532 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec114_perm[j285] = fRec114_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec113_tmp[j286] = fRec113_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fConst530 * (fConst533 * fRec114[i] + fConst534 * fRec114[faust_wrap_sub(i, 1)] + fConst533 * fRec114[faust_wrap_sub(i, 2)]) - fConst535 * (fConst536 * fRec113[faust_wrap_sub(i, 2)] + fConst537 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec113_perm[j287] = fRec113_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec112_tmp[j288] = fRec112_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fSlow108 * fRec112[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst535 * (fConst538 * fRec113[i] + fConst539 * fRec113[faust_wrap_sub(i, 1)] + fConst538 * fRec113[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec112_perm[j289] = fRec112_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec20_tmp[j92] = fRec20_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fZec20[i] - fConst9 * (fConst10 * fRec20[faust_wrap_sub(i, 2)] + fConst13 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec20_perm[j93] = fRec20_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec19_tmp[j94] = fRec19_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst9 * (fConst15 * fRec20[i] + fConst16 * fRec20[faust_wrap_sub(i, 1)] + fConst15 * fRec20[faust_wrap_sub(i, 2)]) - fConst17 * (fConst18 * fRec19[faust_wrap_sub(i, 2)] + fConst19 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec19_perm[j95] = fRec19_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec18_tmp[j96] = fRec18_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fConst17 * (fConst21 * fRec19[i] + fConst22 * fRec19[faust_wrap_sub(i, 1)] + fConst21 * fRec19[faust_wrap_sub(i, 2)]) - fConst23 * (fConst24 * fRec18[faust_wrap_sub(i, 2)] + fConst25 * fRec18[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec18_perm[j97] = fRec18_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec17_tmp[j98] = fRec17_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] * fSlow108 + std::fabs(fConst23 * (fConst28 * fRec18[i] + fConst29 * fRec18[faust_wrap_sub(i, 1)] + fConst28 * fRec18[faust_wrap_sub(i, 2)])) * fSlow109;
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec17_perm[j99] = fRec17_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec24_tmp[j106] = fRec24_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec21[i] - fConst48 * (fConst49 * fRec24[faust_wrap_sub(i, 2)] + fConst52 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec24_perm[j107] = fRec24_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec23_tmp[j108] = fRec23_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst48 * (fConst54 * fRec24[i] + fConst55 * fRec24[faust_wrap_sub(i, 1)] + fConst54 * fRec24[faust_wrap_sub(i, 2)]) - fConst56 * (fConst57 * fRec23[faust_wrap_sub(i, 2)] + fConst58 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec23_perm[j109] = fRec23_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec22_tmp[j110] = fRec22_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst56 * (fConst60 * fRec23[i] + fConst61 * fRec23[faust_wrap_sub(i, 1)] + fConst60 * fRec23[faust_wrap_sub(i, 2)]) - fConst62 * (fConst63 * fRec22[faust_wrap_sub(i, 2)] + fConst64 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec22_perm[j111] = fRec22_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec21_tmp[j112] = fRec21_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fSlow108 * fRec21[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst62 * (fConst66 * fRec22[i] + fConst67 * fRec22[faust_wrap_sub(i, 1)] + fConst66 * fRec22[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec21_perm[j113] = fRec21_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec31_tmp[j120] = fRec31_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec22[i] - fConst86 * (fConst87 * fRec31[faust_wrap_sub(i, 2)] + fConst90 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec31_perm[j121] = fRec31_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec30_tmp[j122] = fRec30_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst86 * (fConst92 * fRec31[i] + fConst93 * fRec31[faust_wrap_sub(i, 1)] + fConst92 * fRec31[faust_wrap_sub(i, 2)]) - fConst94 * (fConst95 * fRec30[faust_wrap_sub(i, 2)] + fConst96 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec30_perm[j123] = fRec30_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec29_tmp[j124] = fRec29_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst94 * (fConst98 * fRec30[i] + fConst99 * fRec30[faust_wrap_sub(i, 1)] + fConst98 * fRec30[faust_wrap_sub(i, 2)]) - fConst100 * (fConst101 * fRec29[faust_wrap_sub(i, 2)] + fConst102 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec29_perm[j125] = fRec29_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec28_tmp[j126] = fRec28_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fSlow108 * fRec28[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst100 * (fConst104 * fRec29[i] + fConst105 * fRec29[faust_wrap_sub(i, 1)] + fConst104 * fRec29[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec28_perm[j127] = fRec28_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec38_tmp[j134] = fRec38_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec23[i] - fConst124 * (fConst125 * fRec38[faust_wrap_sub(i, 2)] + fConst128 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec38_perm[j135] = fRec38_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec37_tmp[j136] = fRec37_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst124 * (fConst130 * fRec38[i] + fConst131 * fRec38[faust_wrap_sub(i, 1)] + fConst130 * fRec38[faust_wrap_sub(i, 2)]) - fConst132 * (fConst133 * fRec37[faust_wrap_sub(i, 2)] + fConst134 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec37_perm[j137] = fRec37_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec36_tmp[j138] = fRec36_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst132 * (fConst136 * fRec37[i] + fConst137 * fRec37[faust_wrap_sub(i, 1)] + fConst136 * fRec37[faust_wrap_sub(i, 2)]) - fConst138 * (fConst139 * fRec36[faust_wrap_sub(i, 2)] + fConst140 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec36_perm[j139] = fRec36_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec35_tmp[j140] = fRec35_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fSlow108 * fRec35[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst138 * (fConst142 * fRec36[i] + fConst143 * fRec36[faust_wrap_sub(i, 1)] + fConst142 * fRec36[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec35_perm[j141] = fRec35_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec45_tmp[j148] = fRec45_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec24[i] - fConst162 * (fConst163 * fRec45[faust_wrap_sub(i, 2)] + fConst166 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec45_perm[j149] = fRec45_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec44_tmp[j150] = fRec44_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst162 * (fConst168 * fRec45[i] + fConst169 * fRec45[faust_wrap_sub(i, 1)] + fConst168 * fRec45[faust_wrap_sub(i, 2)]) - fConst170 * (fConst171 * fRec44[faust_wrap_sub(i, 2)] + fConst172 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec44_perm[j151] = fRec44_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec43_tmp[j152] = fRec43_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst170 * (fConst174 * fRec44[i] + fConst175 * fRec44[faust_wrap_sub(i, 1)] + fConst174 * fRec44[faust_wrap_sub(i, 2)]) - fConst176 * (fConst177 * fRec43[faust_wrap_sub(i, 2)] + fConst178 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec43_perm[j153] = fRec43_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec42_tmp[j154] = fRec42_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fSlow108 * fRec42[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst176 * (fConst180 * fRec43[i] + fConst181 * fRec43[faust_wrap_sub(i, 1)] + fConst180 * fRec43[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec42_perm[j155] = fRec42_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec52_tmp[j162] = fRec52_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec25[i] - fConst200 * (fConst201 * fRec52[faust_wrap_sub(i, 2)] + fConst204 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec52_perm[j163] = fRec52_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec51_tmp[j164] = fRec51_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst200 * (fConst206 * fRec52[i] + fConst207 * fRec52[faust_wrap_sub(i, 1)] + fConst206 * fRec52[faust_wrap_sub(i, 2)]) - fConst208 * (fConst209 * fRec51[faust_wrap_sub(i, 2)] + fConst210 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec51_perm[j165] = fRec51_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec50_tmp[j166] = fRec50_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst208 * (fConst212 * fRec51[i] + fConst213 * fRec51[faust_wrap_sub(i, 1)] + fConst212 * fRec51[faust_wrap_sub(i, 2)]) - fConst214 * (fConst215 * fRec50[faust_wrap_sub(i, 2)] + fConst216 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec50_perm[j167] = fRec50_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec49_tmp[j168] = fRec49_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fSlow108 * fRec49[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst214 * (fConst218 * fRec50[i] + fConst219 * fRec50[faust_wrap_sub(i, 1)] + fConst218 * fRec50[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec49_perm[j169] = fRec49_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec59_tmp[j176] = fRec59_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec26[i] - fConst238 * (fConst239 * fRec59[faust_wrap_sub(i, 2)] + fConst242 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec59_perm[j177] = fRec59_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec58_tmp[j178] = fRec58_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst238 * (fConst244 * fRec59[i] + fConst245 * fRec59[faust_wrap_sub(i, 1)] + fConst244 * fRec59[faust_wrap_sub(i, 2)]) - fConst246 * (fConst247 * fRec58[faust_wrap_sub(i, 2)] + fConst248 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec58_perm[j179] = fRec58_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec57_tmp[j180] = fRec57_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst246 * (fConst250 * fRec58[i] + fConst251 * fRec58[faust_wrap_sub(i, 1)] + fConst250 * fRec58[faust_wrap_sub(i, 2)]) - fConst252 * (fConst253 * fRec57[faust_wrap_sub(i, 2)] + fConst254 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec57_perm[j181] = fRec57_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec56_tmp[j182] = fRec56_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fSlow108 * fRec56[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst252 * (fConst256 * fRec57[i] + fConst257 * fRec57[faust_wrap_sub(i, 1)] + fConst256 * fRec57[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec56_perm[j183] = fRec56_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec66_tmp[j190] = fRec66_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec27[i] - fConst276 * (fConst277 * fRec66[faust_wrap_sub(i, 2)] + fConst280 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec66_perm[j191] = fRec66_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec65_tmp[j192] = fRec65_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst276 * (fConst282 * fRec66[i] + fConst283 * fRec66[faust_wrap_sub(i, 1)] + fConst282 * fRec66[faust_wrap_sub(i, 2)]) - fConst284 * (fConst285 * fRec65[faust_wrap_sub(i, 2)] + fConst286 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec65_perm[j193] = fRec65_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec64_tmp[j194] = fRec64_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst284 * (fConst288 * fRec65[i] + fConst289 * fRec65[faust_wrap_sub(i, 1)] + fConst288 * fRec65[faust_wrap_sub(i, 2)]) - fConst290 * (fConst291 * fRec64[faust_wrap_sub(i, 2)] + fConst292 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec64_perm[j195] = fRec64_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec63_tmp[j196] = fRec63_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fSlow108 * fRec63[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst290 * (fConst294 * fRec64[i] + fConst295 * fRec64[faust_wrap_sub(i, 1)] + fConst294 * fRec64[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec63_perm[j197] = fRec63_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec73_tmp[j204] = fRec73_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec28[i] - fConst314 * (fConst315 * fRec73[faust_wrap_sub(i, 2)] + fConst318 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec73_perm[j205] = fRec73_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec72_tmp[j206] = fRec72_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst314 * (fConst320 * fRec73[i] + fConst321 * fRec73[faust_wrap_sub(i, 1)] + fConst320 * fRec73[faust_wrap_sub(i, 2)]) - fConst322 * (fConst323 * fRec72[faust_wrap_sub(i, 2)] + fConst324 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec72_perm[j207] = fRec72_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec71_tmp[j208] = fRec71_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst322 * (fConst326 * fRec72[i] + fConst327 * fRec72[faust_wrap_sub(i, 1)] + fConst326 * fRec72[faust_wrap_sub(i, 2)]) - fConst328 * (fConst329 * fRec71[faust_wrap_sub(i, 2)] + fConst330 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec71_perm[j209] = fRec71_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec70_tmp[j210] = fRec70_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fSlow108 * fRec70[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst328 * (fConst332 * fRec71[i] + fConst333 * fRec71[faust_wrap_sub(i, 1)] + fConst332 * fRec71[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec70_perm[j211] = fRec70_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec80_tmp[j218] = fRec80_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec29[i] - fConst352 * (fConst353 * fRec80[faust_wrap_sub(i, 2)] + fConst356 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec80_perm[j219] = fRec80_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec79_tmp[j220] = fRec79_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst352 * (fConst358 * fRec80[i] + fConst359 * fRec80[faust_wrap_sub(i, 1)] + fConst358 * fRec80[faust_wrap_sub(i, 2)]) - fConst360 * (fConst361 * fRec79[faust_wrap_sub(i, 2)] + fConst362 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec79_perm[j221] = fRec79_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec78_tmp[j222] = fRec78_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst360 * (fConst364 * fRec79[i] + fConst365 * fRec79[faust_wrap_sub(i, 1)] + fConst364 * fRec79[faust_wrap_sub(i, 2)]) - fConst366 * (fConst367 * fRec78[faust_wrap_sub(i, 2)] + fConst368 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec78_perm[j223] = fRec78_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec77_tmp[j224] = fRec77_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fSlow108 * fRec77[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst366 * (fConst370 * fRec78[i] + fConst371 * fRec78[faust_wrap_sub(i, 1)] + fConst370 * fRec78[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec77_perm[j225] = fRec77_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec87_tmp[j232] = fRec87_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec30[i] - fConst390 * (fConst391 * fRec87[faust_wrap_sub(i, 2)] + fConst394 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec87_perm[j233] = fRec87_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec86_tmp[j234] = fRec86_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst390 * (fConst396 * fRec87[i] + fConst397 * fRec87[faust_wrap_sub(i, 1)] + fConst396 * fRec87[faust_wrap_sub(i, 2)]) - fConst398 * (fConst399 * fRec86[faust_wrap_sub(i, 2)] + fConst400 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec86_perm[j235] = fRec86_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec85_tmp[j236] = fRec85_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst398 * (fConst402 * fRec86[i] + fConst403 * fRec86[faust_wrap_sub(i, 1)] + fConst402 * fRec86[faust_wrap_sub(i, 2)]) - fConst404 * (fConst405 * fRec85[faust_wrap_sub(i, 2)] + fConst406 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec85_perm[j237] = fRec85_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec84_tmp[j238] = fRec84_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fSlow108 * fRec84[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst404 * (fConst408 * fRec85[i] + fConst409 * fRec85[faust_wrap_sub(i, 1)] + fConst408 * fRec85[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec84_perm[j239] = fRec84_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec94_tmp[j246] = fRec94_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec31[i] - fConst428 * (fConst429 * fRec94[faust_wrap_sub(i, 2)] + fConst432 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec94_perm[j247] = fRec94_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec93_tmp[j248] = fRec93_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst428 * (fConst434 * fRec94[i] + fConst435 * fRec94[faust_wrap_sub(i, 1)] + fConst434 * fRec94[faust_wrap_sub(i, 2)]) - fConst436 * (fConst437 * fRec93[faust_wrap_sub(i, 2)] + fConst438 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec93_perm[j249] = fRec93_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec92_tmp[j250] = fRec92_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst436 * (fConst440 * fRec93[i] + fConst441 * fRec93[faust_wrap_sub(i, 1)] + fConst440 * fRec93[faust_wrap_sub(i, 2)]) - fConst442 * (fConst443 * fRec92[faust_wrap_sub(i, 2)] + fConst444 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec92_perm[j251] = fRec92_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec91_tmp[j252] = fRec91_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fSlow108 * fRec91[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst442 * (fConst446 * fRec92[i] + fConst447 * fRec92[faust_wrap_sub(i, 1)] + fConst446 * fRec92[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec91_perm[j253] = fRec91_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Vectorizable loop 176 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec17[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec21[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec28[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec35[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec42[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec49[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec56[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec63[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec70[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec77[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec84[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec91[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec98[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec105[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec112[i]));
				output0[i] = static_cast<FAUSTFLOAT>(fZec20[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec10_tmp[j0] = fRec10_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = fSlow0 + 0.999 * fRec10[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec10_perm[j1] = fRec10_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec12_tmp[j2] = fRec12_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fRec12[faust_wrap_sub(i, 1)] * fSlow2 + fSlow3;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec12_perm[j3] = fRec12_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec12[i]));
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec11_tmp[j4] = fRec11_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec11[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec11[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec11_perm[j5] = fRec11_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec12[i]));
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec13_tmp[j6] = fRec13_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec13[faust_wrap_sub(i, 1)] + fConst1 * fZec2[i];
				fRec13[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec13_perm[j7] = fRec13_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec12[i]));
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec14_tmp[j8] = fRec14_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fRec14[faust_wrap_sub(i, 1)] + fConst1 * fZec4[i];
				fRec14[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec14_perm[j9] = fRec14_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iRec15_tmp[j10] = iRec15_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec15[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec15[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iRec15_perm[j11] = iRec15_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec15[i]);
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec16_tmp[j12] = fRec16_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = 0.5221894 * fRec16[faust_wrap_sub(i, 3)] + fZec6[i] + 2.494956002 * fRec16[faust_wrap_sub(i, 1)] - 2.017265875 * fRec16[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec16_perm[j13] = fRec16_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				iVec0_tmp[j14] = iVec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				iVec0_perm[j15] = iVec0_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 2.0 * fRec11[i];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fZec7[i] + -1.0;
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fYec0_tmp[j16] = fYec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = mydsp_faustpower2_f(fZec8[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fYec0_perm[j17] = fYec0_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 2)]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = mydsp_faustpower3_f(fZec8[i]);
			}
			/* Vectorizable loop 18 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fYec1_tmp[j18] = fYec1_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fZec11[i] + (1.0 - fZec7[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fYec1_perm[j19] = fYec1_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 19 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fYec2_tmp[j20] = fYec2_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[i] = (fZec11[i] + (1.0 - (fZec7[i] + fYec1[faust_wrap_sub(i, 1)]))) / fZec0[i];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fYec2_perm[j21] = fYec2_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 3)]);
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fYec3_tmp[j22] = fYec3_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fYec3_perm[j23] = fYec3_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 22 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fYec4_tmp[j24] = fYec4_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[i] = (fYec3[i] - fYec3[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fYec4_perm[j25] = fYec4_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Vectorizable loop 23 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fYec5_tmp[j26] = fYec5_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[i] = (fYec4[i] - fYec4[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fYec5_perm[j27] = fYec5_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = 2.0 * fRec13[i];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fZec13[i] + -1.0;
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fYec6_tmp[j28] = fYec6_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[i] = mydsp_faustpower2_f(fZec14[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fYec6_perm[j29] = fYec6_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = mydsp_faustpower3_f(fZec14[i]);
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fYec7_tmp[j30] = fYec7_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[i] = fZec15[i] + (1.0 - fZec13[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fYec7_perm[j31] = fYec7_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fYec8_tmp[j32] = fYec8_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[i] = (fZec15[i] + (1.0 - (fZec13[i] + fYec7[faust_wrap_sub(i, 1)]))) / fZec2[i];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fYec8_perm[j33] = fYec8_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 30 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fYec9_tmp[j34] = fYec9_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fYec9_perm[j35] = fYec9_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 31 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fYec10_tmp[j36] = fYec10_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[i] = (fYec9[i] - fYec9[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fYec10_perm[j37] = fYec10_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 32 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fYec11_tmp[j38] = fYec11_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[i] = (fYec10[i] - fYec10[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fYec11_perm[j39] = fYec11_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = 2.0 * fRec14[i];
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fZec16[i] + -1.0;
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fYec12_tmp[j40] = fYec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[i] = mydsp_faustpower2_f(fZec17[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fYec12_perm[j41] = fYec12_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = mydsp_faustpower3_f(fZec17[i]);
			}
			/* Vectorizable loop 37 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fYec13_tmp[j42] = fYec13_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[i] = fZec18[i] + (1.0 - fZec16[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fYec13_perm[j43] = fYec13_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 38 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec14_tmp[j44] = fYec14_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[i] = (fZec18[i] + (1.0 - (fZec16[i] + fYec13[faust_wrap_sub(i, 1)]))) / fZec4[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec14_perm[j45] = fYec14_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 39 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fYec15_tmp[j46] = fYec15_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fYec15_perm[j47] = fYec15_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Vectorizable loop 40 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fYec16_tmp[j48] = fYec16_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[i] = (fYec15[i] - fYec15[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fYec16_perm[j49] = fYec16_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fYec17_tmp[j50] = fYec17_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[i] = (fYec16[i] - fYec16[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fYec17_perm[j51] = fYec17_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fRec10[i] * ((iSlow17) ? static_cast<double>(input0[i]) : ((iSlow18) ? ((iSlow23) ? 0.049922035 * fRec16[i] + 0.050612699 * fRec16[faust_wrap_sub(i, 2)] - (0.095993537 * fRec16[faust_wrap_sub(i, 1)] + 0.004408786 * fRec16[faust_wrap_sub(i, 3)]) : fZec6[i]) : 0.3333333333333333 * fRec10[i] * (((iSlow20) ? ((iSlow22) ? fConst6 * (fZec12[i] * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst5 * (fZec10[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow21) ? fConst4 * (fZec9[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec8[i])) + ((iSlow20) ? ((iSlow22) ? fConst6 * (fZec12[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec2[i]) : fConst5 * (fZec10[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec2[i])) : ((iSlow21) ? fConst4 * (fZec9[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec2[i]) : fZec14[i])) + ((iSlow20) ? ((iSlow22) ? fConst6 * (fZec12[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec4[i]) : fConst5 * (fZec10[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec4[i])) : ((iSlow21) ? fConst4 * (fZec9[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec4[i]) : fZec17[i])))));
			}
			/* Vectorizable loop 43 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec18_tmp[j52] = fYec18_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[i] = ((iSlow16) ? 0.0 : fZec19[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec18_perm[j53] = fYec18_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec9_tmp[j54] = fRec9_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = -(fSlow8 * (fSlow9 * fRec9[faust_wrap_sub(i, 1)] - (fSlow15 * fYec18[i] + fSlow24 * fYec18[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec9_perm[j55] = fRec9_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 45 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fYec19_tmp[j56] = fYec19_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[i] = fSlow33 * fRec9[i];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fYec19_perm[j57] = fYec19_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec8_tmp[j58] = fRec8_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = -(fSlow27 * (fSlow28 * fRec8[faust_wrap_sub(i, 1)] - (fSlow31 * fRec9[i] + fSlow32 * fYec19[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec8_perm[j59] = fRec8_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fYec20_tmp[j60] = fYec20_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[i] = fSlow42 * fRec8[i];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fYec20_perm[j61] = fYec20_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec7_tmp[j62] = fRec7_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = -(fSlow36 * (fSlow37 * fRec7[faust_wrap_sub(i, 1)] - (fSlow40 * fRec8[i] + fSlow41 * fYec20[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec7_perm[j63] = fRec7_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 49 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fYec21_tmp[j64] = fYec21_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[i] = fSlow51 * fRec7[i];
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fYec21_perm[j65] = fYec21_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec6_tmp[j66] = fRec6_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = -(fSlow45 * (fSlow46 * fRec6[faust_wrap_sub(i, 1)] - (fSlow49 * fRec7[i] + fSlow50 * fYec21[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec6_perm[j67] = fRec6_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 51 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fYec22_tmp[j68] = fYec22_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[i] = fSlow60 * fRec6[i];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fYec22_perm[j69] = fYec22_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec5_tmp[j70] = fRec5_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = -(fSlow54 * (fSlow55 * fRec5[faust_wrap_sub(i, 1)] - (fSlow58 * fRec6[i] + fSlow59 * fYec22[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec5_perm[j71] = fRec5_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 53 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fYec23_tmp[j72] = fYec23_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[i] = fSlow69 * fRec5[i];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fYec23_perm[j73] = fYec23_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec4_tmp[j74] = fRec4_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = -(fSlow63 * (fSlow64 * fRec4[faust_wrap_sub(i, 1)] - (fSlow67 * fRec5[i] + fSlow68 * fYec23[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec4_perm[j75] = fRec4_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 55 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fYec24_tmp[j76] = fYec24_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec24[i] = fSlow78 * fRec4[i];
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fYec24_perm[j77] = fYec24_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec3_tmp[j78] = fRec3_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = -(fSlow72 * (fSlow73 * fRec3[faust_wrap_sub(i, 1)] - (fSlow76 * fRec4[i] + fSlow77 * fYec24[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec3_perm[j79] = fRec3_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 57 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fYec25_tmp[j80] = fYec25_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec25[i] = fSlow87 * fRec3[i];
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fYec25_perm[j81] = fYec25_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec2_tmp[j82] = fRec2_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = -(fSlow81 * (fSlow82 * fRec2[faust_wrap_sub(i, 1)] - (fSlow85 * fRec3[i] + fSlow86 * fYec25[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec2_perm[j83] = fRec2_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 59 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fYec26_tmp[j84] = fYec26_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec26[i] = fSlow96 * fRec2[i];
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fYec26_perm[j85] = fYec26_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec1_tmp[j86] = fRec1_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = -(fSlow90 * (fSlow91 * fRec1[faust_wrap_sub(i, 1)] - (fSlow94 * fRec2[i] + fSlow95 * fYec26[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec1_perm[j87] = fRec1_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 61 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fYec27_tmp[j88] = fYec27_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec27[i] = fSlow105 * fRec1[i];
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fYec27_perm[j89] = fYec27_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec0_tmp[j90] = fRec0_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = -(fSlow99 * (fSlow100 * fRec0[faust_wrap_sub(i, 1)] - (fSlow103 * fRec1[i] + fSlow104 * fYec27[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec0_perm[j91] = fRec0_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = ((iSlow16) ? fZec19[i] : fSlow106 * fRec0[i]);
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec27_tmp[j100] = fRec27_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fZec20[i] - fConst30 * (fConst31 * fRec27[faust_wrap_sub(i, 2)] + fConst32 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec27_perm[j101] = fRec27_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec26_tmp[j102] = fRec26_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst30 * (fConst34 * fRec27[i] + fConst35 * fRec27[faust_wrap_sub(i, 1)] + fConst34 * fRec27[faust_wrap_sub(i, 2)]) - fConst36 * (fConst37 * fRec26[faust_wrap_sub(i, 2)] + fConst38 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec26_perm[j103] = fRec26_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec25_tmp[j104] = fRec25_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fConst36 * (fConst39 * fRec26[i] + fConst40 * fRec26[faust_wrap_sub(i, 1)] + fConst39 * fRec26[faust_wrap_sub(i, 2)]) - fConst41 * (fConst42 * fRec25[faust_wrap_sub(i, 2)] + fConst43 * fRec25[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec25_perm[j105] = fRec25_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = fConst41 * (fConst44 * fRec25[i] + fConst45 * fRec25[faust_wrap_sub(i, 1)] + fConst44 * fRec25[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec34_tmp[j114] = fRec34_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fZec21[i] - fConst68 * (fConst69 * fRec34[faust_wrap_sub(i, 2)] + fConst70 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec34_perm[j115] = fRec34_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec33_tmp[j116] = fRec33_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst68 * (fConst72 * fRec34[i] + fConst73 * fRec34[faust_wrap_sub(i, 1)] + fConst72 * fRec34[faust_wrap_sub(i, 2)]) - fConst74 * (fConst75 * fRec33[faust_wrap_sub(i, 2)] + fConst76 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec33_perm[j117] = fRec33_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec32_tmp[j118] = fRec32_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fConst74 * (fConst77 * fRec33[i] + fConst78 * fRec33[faust_wrap_sub(i, 1)] + fConst77 * fRec33[faust_wrap_sub(i, 2)]) - fConst79 * (fConst80 * fRec32[faust_wrap_sub(i, 2)] + fConst81 * fRec32[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec32_perm[j119] = fRec32_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fConst79 * (fConst82 * fRec32[i] + fConst83 * fRec32[faust_wrap_sub(i, 1)] + fConst82 * fRec32[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec41_tmp[j128] = fRec41_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fZec22[i] - fConst106 * (fConst107 * fRec41[faust_wrap_sub(i, 2)] + fConst108 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec41_perm[j129] = fRec41_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec40_tmp[j130] = fRec40_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst106 * (fConst110 * fRec41[i] + fConst111 * fRec41[faust_wrap_sub(i, 1)] + fConst110 * fRec41[faust_wrap_sub(i, 2)]) - fConst112 * (fConst113 * fRec40[faust_wrap_sub(i, 2)] + fConst114 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec40_perm[j131] = fRec40_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec39_tmp[j132] = fRec39_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fConst112 * (fConst115 * fRec40[i] + fConst116 * fRec40[faust_wrap_sub(i, 1)] + fConst115 * fRec40[faust_wrap_sub(i, 2)]) - fConst117 * (fConst118 * fRec39[faust_wrap_sub(i, 2)] + fConst119 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec39_perm[j133] = fRec39_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fConst117 * (fConst120 * fRec39[i] + fConst121 * fRec39[faust_wrap_sub(i, 1)] + fConst120 * fRec39[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec48_tmp[j142] = fRec48_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fZec23[i] - fConst144 * (fConst145 * fRec48[faust_wrap_sub(i, 2)] + fConst146 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec48_perm[j143] = fRec48_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec47_tmp[j144] = fRec47_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst144 * (fConst148 * fRec48[i] + fConst149 * fRec48[faust_wrap_sub(i, 1)] + fConst148 * fRec48[faust_wrap_sub(i, 2)]) - fConst150 * (fConst151 * fRec47[faust_wrap_sub(i, 2)] + fConst152 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec47_perm[j145] = fRec47_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec46_tmp[j146] = fRec46_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fConst150 * (fConst153 * fRec47[i] + fConst154 * fRec47[faust_wrap_sub(i, 1)] + fConst153 * fRec47[faust_wrap_sub(i, 2)]) - fConst155 * (fConst156 * fRec46[faust_wrap_sub(i, 2)] + fConst157 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec46_perm[j147] = fRec46_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fConst155 * (fConst158 * fRec46[i] + fConst159 * fRec46[faust_wrap_sub(i, 1)] + fConst158 * fRec46[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec55_tmp[j156] = fRec55_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fZec24[i] - fConst182 * (fConst183 * fRec55[faust_wrap_sub(i, 2)] + fConst184 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec55_perm[j157] = fRec55_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec54_tmp[j158] = fRec54_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst182 * (fConst186 * fRec55[i] + fConst187 * fRec55[faust_wrap_sub(i, 1)] + fConst186 * fRec55[faust_wrap_sub(i, 2)]) - fConst188 * (fConst189 * fRec54[faust_wrap_sub(i, 2)] + fConst190 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec54_perm[j159] = fRec54_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec53_tmp[j160] = fRec53_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fConst188 * (fConst191 * fRec54[i] + fConst192 * fRec54[faust_wrap_sub(i, 1)] + fConst191 * fRec54[faust_wrap_sub(i, 2)]) - fConst193 * (fConst194 * fRec53[faust_wrap_sub(i, 2)] + fConst195 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec53_perm[j161] = fRec53_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = fConst193 * (fConst196 * fRec53[i] + fConst197 * fRec53[faust_wrap_sub(i, 1)] + fConst196 * fRec53[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec62_tmp[j170] = fRec62_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fZec25[i] - fConst220 * (fConst221 * fRec62[faust_wrap_sub(i, 2)] + fConst222 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec62_perm[j171] = fRec62_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec61_tmp[j172] = fRec61_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst220 * (fConst224 * fRec62[i] + fConst225 * fRec62[faust_wrap_sub(i, 1)] + fConst224 * fRec62[faust_wrap_sub(i, 2)]) - fConst226 * (fConst227 * fRec61[faust_wrap_sub(i, 2)] + fConst228 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec61_perm[j173] = fRec61_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec60_tmp[j174] = fRec60_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fConst226 * (fConst229 * fRec61[i] + fConst230 * fRec61[faust_wrap_sub(i, 1)] + fConst229 * fRec61[faust_wrap_sub(i, 2)]) - fConst231 * (fConst232 * fRec60[faust_wrap_sub(i, 2)] + fConst233 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec60_perm[j175] = fRec60_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fConst231 * (fConst234 * fRec60[i] + fConst235 * fRec60[faust_wrap_sub(i, 1)] + fConst234 * fRec60[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec69_tmp[j184] = fRec69_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fZec26[i] - fConst258 * (fConst259 * fRec69[faust_wrap_sub(i, 2)] + fConst260 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec69_perm[j185] = fRec69_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec68_tmp[j186] = fRec68_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst258 * (fConst262 * fRec69[i] + fConst263 * fRec69[faust_wrap_sub(i, 1)] + fConst262 * fRec69[faust_wrap_sub(i, 2)]) - fConst264 * (fConst265 * fRec68[faust_wrap_sub(i, 2)] + fConst266 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec68_perm[j187] = fRec68_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec67_tmp[j188] = fRec67_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fConst264 * (fConst267 * fRec68[i] + fConst268 * fRec68[faust_wrap_sub(i, 1)] + fConst267 * fRec68[faust_wrap_sub(i, 2)]) - fConst269 * (fConst270 * fRec67[faust_wrap_sub(i, 2)] + fConst271 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec67_perm[j189] = fRec67_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = fConst269 * (fConst272 * fRec67[i] + fConst273 * fRec67[faust_wrap_sub(i, 1)] + fConst272 * fRec67[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec76_tmp[j198] = fRec76_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fZec27[i] - fConst296 * (fConst297 * fRec76[faust_wrap_sub(i, 2)] + fConst298 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec76_perm[j199] = fRec76_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec75_tmp[j200] = fRec75_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst296 * (fConst300 * fRec76[i] + fConst301 * fRec76[faust_wrap_sub(i, 1)] + fConst300 * fRec76[faust_wrap_sub(i, 2)]) - fConst302 * (fConst303 * fRec75[faust_wrap_sub(i, 2)] + fConst304 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec75_perm[j201] = fRec75_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec74_tmp[j202] = fRec74_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fConst302 * (fConst305 * fRec75[i] + fConst306 * fRec75[faust_wrap_sub(i, 1)] + fConst305 * fRec75[faust_wrap_sub(i, 2)]) - fConst307 * (fConst308 * fRec74[faust_wrap_sub(i, 2)] + fConst309 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec74_perm[j203] = fRec74_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = fConst307 * (fConst310 * fRec74[i] + fConst311 * fRec74[faust_wrap_sub(i, 1)] + fConst310 * fRec74[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec83_tmp[j212] = fRec83_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fZec28[i] - fConst334 * (fConst335 * fRec83[faust_wrap_sub(i, 2)] + fConst336 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec83_perm[j213] = fRec83_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec82_tmp[j214] = fRec82_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst334 * (fConst338 * fRec83[i] + fConst339 * fRec83[faust_wrap_sub(i, 1)] + fConst338 * fRec83[faust_wrap_sub(i, 2)]) - fConst340 * (fConst341 * fRec82[faust_wrap_sub(i, 2)] + fConst342 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec82_perm[j215] = fRec82_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec81_tmp[j216] = fRec81_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fConst340 * (fConst343 * fRec82[i] + fConst344 * fRec82[faust_wrap_sub(i, 1)] + fConst343 * fRec82[faust_wrap_sub(i, 2)]) - fConst345 * (fConst346 * fRec81[faust_wrap_sub(i, 2)] + fConst347 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec81_perm[j217] = fRec81_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = fConst345 * (fConst348 * fRec81[i] + fConst349 * fRec81[faust_wrap_sub(i, 1)] + fConst348 * fRec81[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec90_tmp[j226] = fRec90_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fZec29[i] - fConst372 * (fConst373 * fRec90[faust_wrap_sub(i, 2)] + fConst374 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec90_perm[j227] = fRec90_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec89_tmp[j228] = fRec89_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst372 * (fConst376 * fRec90[i] + fConst377 * fRec90[faust_wrap_sub(i, 1)] + fConst376 * fRec90[faust_wrap_sub(i, 2)]) - fConst378 * (fConst379 * fRec89[faust_wrap_sub(i, 2)] + fConst380 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec89_perm[j229] = fRec89_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec88_tmp[j230] = fRec88_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fConst378 * (fConst381 * fRec89[i] + fConst382 * fRec89[faust_wrap_sub(i, 1)] + fConst381 * fRec89[faust_wrap_sub(i, 2)]) - fConst383 * (fConst384 * fRec88[faust_wrap_sub(i, 2)] + fConst385 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec88_perm[j231] = fRec88_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = fConst383 * (fConst386 * fRec88[i] + fConst387 * fRec88[faust_wrap_sub(i, 1)] + fConst386 * fRec88[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec97_tmp[j240] = fRec97_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fZec30[i] - fConst410 * (fConst411 * fRec97[faust_wrap_sub(i, 2)] + fConst412 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec97_perm[j241] = fRec97_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec96_tmp[j242] = fRec96_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst410 * (fConst414 * fRec97[i] + fConst415 * fRec97[faust_wrap_sub(i, 1)] + fConst414 * fRec97[faust_wrap_sub(i, 2)]) - fConst416 * (fConst417 * fRec96[faust_wrap_sub(i, 2)] + fConst418 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec96_perm[j243] = fRec96_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec95_tmp[j244] = fRec95_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fConst416 * (fConst419 * fRec96[i] + fConst420 * fRec96[faust_wrap_sub(i, 1)] + fConst419 * fRec96[faust_wrap_sub(i, 2)]) - fConst421 * (fConst422 * fRec95[faust_wrap_sub(i, 2)] + fConst423 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec95_perm[j245] = fRec95_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fConst421 * (fConst424 * fRec95[i] + fConst425 * fRec95[faust_wrap_sub(i, 1)] + fConst424 * fRec95[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec104_tmp[j254] = fRec104_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fZec31[i] - fConst448 * (fConst449 * fRec104[faust_wrap_sub(i, 2)] + fConst450 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec104_perm[j255] = fRec104_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec103_tmp[j256] = fRec103_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst448 * (fConst452 * fRec104[i] + fConst453 * fRec104[faust_wrap_sub(i, 1)] + fConst452 * fRec104[faust_wrap_sub(i, 2)]) - fConst454 * (fConst455 * fRec103[faust_wrap_sub(i, 2)] + fConst456 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec103_perm[j257] = fRec103_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec102_tmp[j258] = fRec102_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fConst454 * (fConst457 * fRec103[i] + fConst458 * fRec103[faust_wrap_sub(i, 1)] + fConst457 * fRec103[faust_wrap_sub(i, 2)]) - fConst459 * (fConst460 * fRec102[faust_wrap_sub(i, 2)] + fConst461 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec102_perm[j259] = fRec102_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = fConst459 * (fConst462 * fRec102[i] + fConst463 * fRec102[faust_wrap_sub(i, 1)] + fConst462 * fRec102[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec101_tmp[j260] = fRec101_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec32[i] - fConst466 * (fConst467 * fRec101[faust_wrap_sub(i, 2)] + fConst470 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec101_perm[j261] = fRec101_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec100_tmp[j262] = fRec100_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst466 * (fConst472 * fRec101[i] + fConst473 * fRec101[faust_wrap_sub(i, 1)] + fConst472 * fRec101[faust_wrap_sub(i, 2)]) - fConst474 * (fConst475 * fRec100[faust_wrap_sub(i, 2)] + fConst476 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec100_perm[j263] = fRec100_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec99_tmp[j264] = fRec99_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst474 * (fConst478 * fRec100[i] + fConst479 * fRec100[faust_wrap_sub(i, 1)] + fConst478 * fRec100[faust_wrap_sub(i, 2)]) - fConst480 * (fConst481 * fRec99[faust_wrap_sub(i, 2)] + fConst482 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec99_perm[j265] = fRec99_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Recursive loop 115 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec98_tmp[j266] = fRec98_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fSlow108 * fRec98[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst480 * (fConst484 * fRec99[i] + fConst485 * fRec99[faust_wrap_sub(i, 1)] + fConst484 * fRec99[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec98_perm[j267] = fRec98_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec111_tmp[j268] = fRec111_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fZec32[i] - fConst486 * (fConst487 * fRec111[faust_wrap_sub(i, 2)] + fConst488 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec111_perm[j269] = fRec111_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec110_tmp[j270] = fRec110_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst486 * (fConst490 * fRec111[i] + fConst491 * fRec111[faust_wrap_sub(i, 1)] + fConst490 * fRec111[faust_wrap_sub(i, 2)]) - fConst492 * (fConst493 * fRec110[faust_wrap_sub(i, 2)] + fConst494 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec110_perm[j271] = fRec110_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec109_tmp[j272] = fRec109_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fConst492 * (fConst495 * fRec110[i] + fConst496 * fRec110[faust_wrap_sub(i, 1)] + fConst495 * fRec110[faust_wrap_sub(i, 2)]) - fConst497 * (fConst498 * fRec109[faust_wrap_sub(i, 2)] + fConst499 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec109_perm[j273] = fRec109_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = fConst497 * (fConst500 * fRec109[i] + fConst501 * fRec109[faust_wrap_sub(i, 1)] + fConst500 * fRec109[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec108_tmp[j274] = fRec108_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fZec33[i] - fConst504 * (fConst505 * fRec108[faust_wrap_sub(i, 2)] + fConst508 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec108_perm[j275] = fRec108_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec107_tmp[j276] = fRec107_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst504 * (fConst510 * fRec108[i] + fConst511 * fRec108[faust_wrap_sub(i, 1)] + fConst510 * fRec108[faust_wrap_sub(i, 2)]) - fConst512 * (fConst513 * fRec107[faust_wrap_sub(i, 2)] + fConst514 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec107_perm[j277] = fRec107_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec106_tmp[j278] = fRec106_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fConst512 * (fConst516 * fRec107[i] + fConst517 * fRec107[faust_wrap_sub(i, 1)] + fConst516 * fRec107[faust_wrap_sub(i, 2)]) - fConst518 * (fConst519 * fRec106[faust_wrap_sub(i, 2)] + fConst520 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec106_perm[j279] = fRec106_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec105_tmp[j280] = fRec105_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fSlow108 * fRec105[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst518 * (fConst522 * fRec106[i] + fConst523 * fRec106[faust_wrap_sub(i, 1)] + fConst522 * fRec106[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec105_perm[j281] = fRec105_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec115_tmp[j282] = fRec115_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fZec33[i] - fConst524 * (fConst525 * fRec115[faust_wrap_sub(i, 2)] + fConst526 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec115_perm[j283] = fRec115_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec114_tmp[j284] = fRec114_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst524 * (fConst528 * fRec115[i] + fConst529 * fRec115[faust_wrap_sub(i, 1)] + fConst528 * fRec115[faust_wrap_sub(i, 2)]) - fConst530 * (fConst531 * fRec114[faust_wrap_sub(i, 2)] + fConst532 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec114_perm[j285] = fRec114_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec113_tmp[j286] = fRec113_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fConst530 * (fConst533 * fRec114[i] + fConst534 * fRec114[faust_wrap_sub(i, 1)] + fConst533 * fRec114[faust_wrap_sub(i, 2)]) - fConst535 * (fConst536 * fRec113[faust_wrap_sub(i, 2)] + fConst537 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec113_perm[j287] = fRec113_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec112_tmp[j288] = fRec112_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fSlow108 * fRec112[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst535 * (fConst538 * fRec113[i] + fConst539 * fRec113[faust_wrap_sub(i, 1)] + fConst538 * fRec113[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec112_perm[j289] = fRec112_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec20_tmp[j92] = fRec20_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fZec20[i] - fConst9 * (fConst10 * fRec20[faust_wrap_sub(i, 2)] + fConst13 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec20_perm[j93] = fRec20_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec19_tmp[j94] = fRec19_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst9 * (fConst15 * fRec20[i] + fConst16 * fRec20[faust_wrap_sub(i, 1)] + fConst15 * fRec20[faust_wrap_sub(i, 2)]) - fConst17 * (fConst18 * fRec19[faust_wrap_sub(i, 2)] + fConst19 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec19_perm[j95] = fRec19_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec18_tmp[j96] = fRec18_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fConst17 * (fConst21 * fRec19[i] + fConst22 * fRec19[faust_wrap_sub(i, 1)] + fConst21 * fRec19[faust_wrap_sub(i, 2)]) - fConst23 * (fConst24 * fRec18[faust_wrap_sub(i, 2)] + fConst25 * fRec18[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec18_perm[j97] = fRec18_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec17_tmp[j98] = fRec17_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] * fSlow108 + std::fabs(fConst23 * (fConst28 * fRec18[i] + fConst29 * fRec18[faust_wrap_sub(i, 1)] + fConst28 * fRec18[faust_wrap_sub(i, 2)])) * fSlow109;
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec17_perm[j99] = fRec17_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec24_tmp[j106] = fRec24_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec21[i] - fConst48 * (fConst49 * fRec24[faust_wrap_sub(i, 2)] + fConst52 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec24_perm[j107] = fRec24_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec23_tmp[j108] = fRec23_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst48 * (fConst54 * fRec24[i] + fConst55 * fRec24[faust_wrap_sub(i, 1)] + fConst54 * fRec24[faust_wrap_sub(i, 2)]) - fConst56 * (fConst57 * fRec23[faust_wrap_sub(i, 2)] + fConst58 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec23_perm[j109] = fRec23_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec22_tmp[j110] = fRec22_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst56 * (fConst60 * fRec23[i] + fConst61 * fRec23[faust_wrap_sub(i, 1)] + fConst60 * fRec23[faust_wrap_sub(i, 2)]) - fConst62 * (fConst63 * fRec22[faust_wrap_sub(i, 2)] + fConst64 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec22_perm[j111] = fRec22_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec21_tmp[j112] = fRec21_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fSlow108 * fRec21[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst62 * (fConst66 * fRec22[i] + fConst67 * fRec22[faust_wrap_sub(i, 1)] + fConst66 * fRec22[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec21_perm[j113] = fRec21_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec31_tmp[j120] = fRec31_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec22[i] - fConst86 * (fConst87 * fRec31[faust_wrap_sub(i, 2)] + fConst90 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec31_perm[j121] = fRec31_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec30_tmp[j122] = fRec30_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst86 * (fConst92 * fRec31[i] + fConst93 * fRec31[faust_wrap_sub(i, 1)] + fConst92 * fRec31[faust_wrap_sub(i, 2)]) - fConst94 * (fConst95 * fRec30[faust_wrap_sub(i, 2)] + fConst96 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec30_perm[j123] = fRec30_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec29_tmp[j124] = fRec29_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst94 * (fConst98 * fRec30[i] + fConst99 * fRec30[faust_wrap_sub(i, 1)] + fConst98 * fRec30[faust_wrap_sub(i, 2)]) - fConst100 * (fConst101 * fRec29[faust_wrap_sub(i, 2)] + fConst102 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec29_perm[j125] = fRec29_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec28_tmp[j126] = fRec28_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fSlow108 * fRec28[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst100 * (fConst104 * fRec29[i] + fConst105 * fRec29[faust_wrap_sub(i, 1)] + fConst104 * fRec29[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec28_perm[j127] = fRec28_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec38_tmp[j134] = fRec38_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec23[i] - fConst124 * (fConst125 * fRec38[faust_wrap_sub(i, 2)] + fConst128 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec38_perm[j135] = fRec38_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec37_tmp[j136] = fRec37_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst124 * (fConst130 * fRec38[i] + fConst131 * fRec38[faust_wrap_sub(i, 1)] + fConst130 * fRec38[faust_wrap_sub(i, 2)]) - fConst132 * (fConst133 * fRec37[faust_wrap_sub(i, 2)] + fConst134 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec37_perm[j137] = fRec37_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec36_tmp[j138] = fRec36_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst132 * (fConst136 * fRec37[i] + fConst137 * fRec37[faust_wrap_sub(i, 1)] + fConst136 * fRec37[faust_wrap_sub(i, 2)]) - fConst138 * (fConst139 * fRec36[faust_wrap_sub(i, 2)] + fConst140 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec36_perm[j139] = fRec36_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec35_tmp[j140] = fRec35_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fSlow108 * fRec35[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst138 * (fConst142 * fRec36[i] + fConst143 * fRec36[faust_wrap_sub(i, 1)] + fConst142 * fRec36[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec35_perm[j141] = fRec35_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec45_tmp[j148] = fRec45_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec24[i] - fConst162 * (fConst163 * fRec45[faust_wrap_sub(i, 2)] + fConst166 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec45_perm[j149] = fRec45_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec44_tmp[j150] = fRec44_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst162 * (fConst168 * fRec45[i] + fConst169 * fRec45[faust_wrap_sub(i, 1)] + fConst168 * fRec45[faust_wrap_sub(i, 2)]) - fConst170 * (fConst171 * fRec44[faust_wrap_sub(i, 2)] + fConst172 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec44_perm[j151] = fRec44_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec43_tmp[j152] = fRec43_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst170 * (fConst174 * fRec44[i] + fConst175 * fRec44[faust_wrap_sub(i, 1)] + fConst174 * fRec44[faust_wrap_sub(i, 2)]) - fConst176 * (fConst177 * fRec43[faust_wrap_sub(i, 2)] + fConst178 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec43_perm[j153] = fRec43_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec42_tmp[j154] = fRec42_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fSlow108 * fRec42[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst176 * (fConst180 * fRec43[i] + fConst181 * fRec43[faust_wrap_sub(i, 1)] + fConst180 * fRec43[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec42_perm[j155] = fRec42_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec52_tmp[j162] = fRec52_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec25[i] - fConst200 * (fConst201 * fRec52[faust_wrap_sub(i, 2)] + fConst204 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec52_perm[j163] = fRec52_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec51_tmp[j164] = fRec51_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst200 * (fConst206 * fRec52[i] + fConst207 * fRec52[faust_wrap_sub(i, 1)] + fConst206 * fRec52[faust_wrap_sub(i, 2)]) - fConst208 * (fConst209 * fRec51[faust_wrap_sub(i, 2)] + fConst210 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec51_perm[j165] = fRec51_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec50_tmp[j166] = fRec50_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst208 * (fConst212 * fRec51[i] + fConst213 * fRec51[faust_wrap_sub(i, 1)] + fConst212 * fRec51[faust_wrap_sub(i, 2)]) - fConst214 * (fConst215 * fRec50[faust_wrap_sub(i, 2)] + fConst216 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec50_perm[j167] = fRec50_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec49_tmp[j168] = fRec49_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fSlow108 * fRec49[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst214 * (fConst218 * fRec50[i] + fConst219 * fRec50[faust_wrap_sub(i, 1)] + fConst218 * fRec50[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec49_perm[j169] = fRec49_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec59_tmp[j176] = fRec59_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec26[i] - fConst238 * (fConst239 * fRec59[faust_wrap_sub(i, 2)] + fConst242 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec59_perm[j177] = fRec59_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec58_tmp[j178] = fRec58_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst238 * (fConst244 * fRec59[i] + fConst245 * fRec59[faust_wrap_sub(i, 1)] + fConst244 * fRec59[faust_wrap_sub(i, 2)]) - fConst246 * (fConst247 * fRec58[faust_wrap_sub(i, 2)] + fConst248 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec58_perm[j179] = fRec58_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec57_tmp[j180] = fRec57_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst246 * (fConst250 * fRec58[i] + fConst251 * fRec58[faust_wrap_sub(i, 1)] + fConst250 * fRec58[faust_wrap_sub(i, 2)]) - fConst252 * (fConst253 * fRec57[faust_wrap_sub(i, 2)] + fConst254 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec57_perm[j181] = fRec57_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec56_tmp[j182] = fRec56_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fSlow108 * fRec56[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst252 * (fConst256 * fRec57[i] + fConst257 * fRec57[faust_wrap_sub(i, 1)] + fConst256 * fRec57[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec56_perm[j183] = fRec56_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec66_tmp[j190] = fRec66_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec27[i] - fConst276 * (fConst277 * fRec66[faust_wrap_sub(i, 2)] + fConst280 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec66_perm[j191] = fRec66_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec65_tmp[j192] = fRec65_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst276 * (fConst282 * fRec66[i] + fConst283 * fRec66[faust_wrap_sub(i, 1)] + fConst282 * fRec66[faust_wrap_sub(i, 2)]) - fConst284 * (fConst285 * fRec65[faust_wrap_sub(i, 2)] + fConst286 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec65_perm[j193] = fRec65_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec64_tmp[j194] = fRec64_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst284 * (fConst288 * fRec65[i] + fConst289 * fRec65[faust_wrap_sub(i, 1)] + fConst288 * fRec65[faust_wrap_sub(i, 2)]) - fConst290 * (fConst291 * fRec64[faust_wrap_sub(i, 2)] + fConst292 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec64_perm[j195] = fRec64_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec63_tmp[j196] = fRec63_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fSlow108 * fRec63[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst290 * (fConst294 * fRec64[i] + fConst295 * fRec64[faust_wrap_sub(i, 1)] + fConst294 * fRec64[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec63_perm[j197] = fRec63_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec73_tmp[j204] = fRec73_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec28[i] - fConst314 * (fConst315 * fRec73[faust_wrap_sub(i, 2)] + fConst318 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec73_perm[j205] = fRec73_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec72_tmp[j206] = fRec72_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst314 * (fConst320 * fRec73[i] + fConst321 * fRec73[faust_wrap_sub(i, 1)] + fConst320 * fRec73[faust_wrap_sub(i, 2)]) - fConst322 * (fConst323 * fRec72[faust_wrap_sub(i, 2)] + fConst324 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec72_perm[j207] = fRec72_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec71_tmp[j208] = fRec71_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst322 * (fConst326 * fRec72[i] + fConst327 * fRec72[faust_wrap_sub(i, 1)] + fConst326 * fRec72[faust_wrap_sub(i, 2)]) - fConst328 * (fConst329 * fRec71[faust_wrap_sub(i, 2)] + fConst330 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec71_perm[j209] = fRec71_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec70_tmp[j210] = fRec70_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fSlow108 * fRec70[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst328 * (fConst332 * fRec71[i] + fConst333 * fRec71[faust_wrap_sub(i, 1)] + fConst332 * fRec71[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec70_perm[j211] = fRec70_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec80_tmp[j218] = fRec80_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec29[i] - fConst352 * (fConst353 * fRec80[faust_wrap_sub(i, 2)] + fConst356 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec80_perm[j219] = fRec80_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec79_tmp[j220] = fRec79_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst352 * (fConst358 * fRec80[i] + fConst359 * fRec80[faust_wrap_sub(i, 1)] + fConst358 * fRec80[faust_wrap_sub(i, 2)]) - fConst360 * (fConst361 * fRec79[faust_wrap_sub(i, 2)] + fConst362 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec79_perm[j221] = fRec79_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec78_tmp[j222] = fRec78_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst360 * (fConst364 * fRec79[i] + fConst365 * fRec79[faust_wrap_sub(i, 1)] + fConst364 * fRec79[faust_wrap_sub(i, 2)]) - fConst366 * (fConst367 * fRec78[faust_wrap_sub(i, 2)] + fConst368 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec78_perm[j223] = fRec78_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec77_tmp[j224] = fRec77_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fSlow108 * fRec77[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst366 * (fConst370 * fRec78[i] + fConst371 * fRec78[faust_wrap_sub(i, 1)] + fConst370 * fRec78[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec77_perm[j225] = fRec77_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec87_tmp[j232] = fRec87_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec30[i] - fConst390 * (fConst391 * fRec87[faust_wrap_sub(i, 2)] + fConst394 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec87_perm[j233] = fRec87_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec86_tmp[j234] = fRec86_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst390 * (fConst396 * fRec87[i] + fConst397 * fRec87[faust_wrap_sub(i, 1)] + fConst396 * fRec87[faust_wrap_sub(i, 2)]) - fConst398 * (fConst399 * fRec86[faust_wrap_sub(i, 2)] + fConst400 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec86_perm[j235] = fRec86_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec85_tmp[j236] = fRec85_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst398 * (fConst402 * fRec86[i] + fConst403 * fRec86[faust_wrap_sub(i, 1)] + fConst402 * fRec86[faust_wrap_sub(i, 2)]) - fConst404 * (fConst405 * fRec85[faust_wrap_sub(i, 2)] + fConst406 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec85_perm[j237] = fRec85_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec84_tmp[j238] = fRec84_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fSlow108 * fRec84[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst404 * (fConst408 * fRec85[i] + fConst409 * fRec85[faust_wrap_sub(i, 1)] + fConst408 * fRec85[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec84_perm[j239] = fRec84_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec94_tmp[j246] = fRec94_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec31[i] - fConst428 * (fConst429 * fRec94[faust_wrap_sub(i, 2)] + fConst432 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec94_perm[j247] = fRec94_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec93_tmp[j248] = fRec93_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst428 * (fConst434 * fRec94[i] + fConst435 * fRec94[faust_wrap_sub(i, 1)] + fConst434 * fRec94[faust_wrap_sub(i, 2)]) - fConst436 * (fConst437 * fRec93[faust_wrap_sub(i, 2)] + fConst438 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec93_perm[j249] = fRec93_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec92_tmp[j250] = fRec92_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst436 * (fConst440 * fRec93[i] + fConst441 * fRec93[faust_wrap_sub(i, 1)] + fConst440 * fRec93[faust_wrap_sub(i, 2)]) - fConst442 * (fConst443 * fRec92[faust_wrap_sub(i, 2)] + fConst444 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec92_perm[j251] = fRec92_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec91_tmp[j252] = fRec91_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fSlow108 * fRec91[faust_wrap_sub(i, 1)] + fSlow109 * std::fabs(fConst442 * (fConst446 * fRec92[i] + fConst447 * fRec92[faust_wrap_sub(i, 1)] + fConst446 * fRec92[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec91_perm[j253] = fRec91_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Vectorizable loop 176 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec17[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec21[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec28[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec35[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec42[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec49[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec56[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec63[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec70[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec77[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec84[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec91[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec98[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec105[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow110 + 2e+01 * std::log10(fRec112[i]));
				output0[i] = static_cast<FAUSTFLOAT>(fZec20[i]);
			}
		}
	}

};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}

#endif
