/* ------------------------------------------------------------
name: "cubic_distortion"
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

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	double fRec1_perm[4];
	FAUSTFLOAT fHslider1;
	double fRec2_perm[4];
	FAUSTFLOAT fHslider2;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider3;
	double fRec5_perm[4];
	double fConst2;
	double fRec3_perm[4];
	int iVec0_perm[4];
	double fRec4_perm[4];
	FAUSTFLOAT fHslider4;
	double fRec6_perm[4];
	FAUSTFLOAT fCheckbox0;
	double fYec0_perm[4];
	double fRec0_perm[4];
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fRec10_perm[4];
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fRec9_perm[4];
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fRec8_perm[4];
	FAUSTFLOAT fHslider5;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fRec7_perm[4];
	double fConst26;
	double fConst27;
	double fConst28;
	double fRec17_perm[4];
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec16_perm[4];
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec15_perm[4];
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fRec14_perm[4];
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fRec13_perm[4];
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec12_perm[4];
	double fConst61;
	double fConst62;
	double fConst63;
	double fRec11_perm[4];
	double fConst64;
	double fConst65;
	double fConst66;
	double fRec24_perm[4];
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fRec23_perm[4];
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fRec22_perm[4];
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fRec21_perm[4];
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fRec20_perm[4];
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fRec19_perm[4];
	double fConst99;
	double fConst100;
	double fConst101;
	double fRec18_perm[4];
	double fConst102;
	double fConst103;
	double fConst104;
	double fRec31_perm[4];
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fRec30_perm[4];
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fRec29_perm[4];
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fRec28_perm[4];
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fConst130;
	double fRec27_perm[4];
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fConst135;
	double fConst136;
	double fRec26_perm[4];
	double fConst137;
	double fConst138;
	double fConst139;
	double fRec25_perm[4];
	double fConst140;
	double fConst141;
	double fConst142;
	double fRec38_perm[4];
	double fConst143;
	double fConst144;
	double fConst145;
	double fConst146;
	double fConst147;
	double fConst148;
	double fRec37_perm[4];
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fRec36_perm[4];
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fRec35_perm[4];
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fRec34_perm[4];
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fConst173;
	double fConst174;
	double fRec33_perm[4];
	double fConst175;
	double fConst176;
	double fConst177;
	double fRec32_perm[4];
	double fConst178;
	double fConst179;
	double fConst180;
	double fRec45_perm[4];
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fRec44_perm[4];
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst191;
	double fRec43_perm[4];
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fConst197;
	double fConst198;
	double fConst199;
	double fConst200;
	double fRec42_perm[4];
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fConst206;
	double fRec41_perm[4];
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fConst211;
	double fConst212;
	double fRec40_perm[4];
	double fConst213;
	double fConst214;
	double fConst215;
	double fRec39_perm[4];
	double fConst216;
	double fConst217;
	double fConst218;
	double fRec52_perm[4];
	double fConst219;
	double fConst220;
	double fConst221;
	double fConst222;
	double fConst223;
	double fConst224;
	double fRec51_perm[4];
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fConst229;
	double fRec50_perm[4];
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst237;
	double fConst238;
	double fRec49_perm[4];
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fConst243;
	double fConst244;
	double fRec48_perm[4];
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fConst249;
	double fConst250;
	double fRec47_perm[4];
	double fConst251;
	double fConst252;
	double fConst253;
	double fRec46_perm[4];
	double fConst254;
	double fConst255;
	double fConst256;
	double fRec59_perm[4];
	double fConst257;
	double fConst258;
	double fConst259;
	double fConst260;
	double fConst261;
	double fConst262;
	double fRec58_perm[4];
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fConst267;
	double fRec57_perm[4];
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fConst273;
	double fConst274;
	double fConst275;
	double fConst276;
	double fRec56_perm[4];
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fConst281;
	double fConst282;
	double fRec55_perm[4];
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fConst287;
	double fConst288;
	double fRec54_perm[4];
	double fConst289;
	double fConst290;
	double fConst291;
	double fRec53_perm[4];
	double fConst292;
	double fConst293;
	double fConst294;
	double fRec66_perm[4];
	double fConst295;
	double fConst296;
	double fConst297;
	double fConst298;
	double fConst299;
	double fConst300;
	double fRec65_perm[4];
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fRec64_perm[4];
	double fConst306;
	double fConst307;
	double fConst308;
	double fConst309;
	double fConst310;
	double fConst311;
	double fConst312;
	double fConst313;
	double fConst314;
	double fRec63_perm[4];
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fConst319;
	double fConst320;
	double fRec62_perm[4];
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fConst325;
	double fConst326;
	double fRec61_perm[4];
	double fConst327;
	double fConst328;
	double fConst329;
	double fRec60_perm[4];
	double fConst330;
	double fConst331;
	double fConst332;
	double fRec73_perm[4];
	double fConst333;
	double fConst334;
	double fConst335;
	double fConst336;
	double fConst337;
	double fConst338;
	double fRec72_perm[4];
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fConst343;
	double fRec71_perm[4];
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fConst351;
	double fConst352;
	double fRec70_perm[4];
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fConst357;
	double fConst358;
	double fRec69_perm[4];
	double fConst359;
	double fConst360;
	double fConst361;
	double fConst362;
	double fConst363;
	double fConst364;
	double fRec68_perm[4];
	double fConst365;
	double fConst366;
	double fConst367;
	double fRec67_perm[4];
	double fConst368;
	double fConst369;
	double fConst370;
	double fRec80_perm[4];
	double fConst371;
	double fConst372;
	double fConst373;
	double fConst374;
	double fConst375;
	double fConst376;
	double fRec79_perm[4];
	double fConst377;
	double fConst378;
	double fConst379;
	double fConst380;
	double fConst381;
	double fRec78_perm[4];
	double fConst382;
	double fConst383;
	double fConst384;
	double fConst385;
	double fConst386;
	double fConst387;
	double fConst388;
	double fConst389;
	double fConst390;
	double fRec77_perm[4];
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fConst395;
	double fConst396;
	double fRec76_perm[4];
	double fConst397;
	double fConst398;
	double fConst399;
	double fConst400;
	double fConst401;
	double fConst402;
	double fRec75_perm[4];
	double fConst403;
	double fConst404;
	double fConst405;
	double fRec74_perm[4];
	double fConst406;
	double fConst407;
	double fConst408;
	double fRec87_perm[4];
	double fConst409;
	double fConst410;
	double fConst411;
	double fConst412;
	double fConst413;
	double fConst414;
	double fRec86_perm[4];
	double fConst415;
	double fConst416;
	double fConst417;
	double fConst418;
	double fConst419;
	double fRec85_perm[4];
	double fConst420;
	double fConst421;
	double fConst422;
	double fConst423;
	double fConst424;
	double fConst425;
	double fConst426;
	double fConst427;
	double fConst428;
	double fRec84_perm[4];
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fConst433;
	double fConst434;
	double fRec83_perm[4];
	double fConst435;
	double fConst436;
	double fConst437;
	double fConst438;
	double fConst439;
	double fConst440;
	double fRec82_perm[4];
	double fConst441;
	double fConst442;
	double fConst443;
	double fRec81_perm[4];
	double fConst444;
	double fConst445;
	double fConst446;
	double fRec94_perm[4];
	double fConst447;
	double fConst448;
	double fConst449;
	double fConst450;
	double fConst451;
	double fConst452;
	double fRec93_perm[4];
	double fConst453;
	double fConst454;
	double fConst455;
	double fConst456;
	double fConst457;
	double fRec92_perm[4];
	double fConst458;
	double fConst459;
	double fConst460;
	double fConst461;
	double fConst462;
	double fConst463;
	double fConst464;
	double fConst465;
	double fConst466;
	double fRec91_perm[4];
	double fConst467;
	double fConst468;
	double fConst469;
	double fConst470;
	double fConst471;
	double fConst472;
	double fRec90_perm[4];
	double fConst473;
	double fConst474;
	double fConst475;
	double fConst476;
	double fConst477;
	double fConst478;
	double fRec89_perm[4];
	double fConst479;
	double fConst480;
	double fConst481;
	double fRec88_perm[4];
	double fConst482;
	double fConst483;
	double fConst484;
	double fRec101_perm[4];
	double fConst485;
	double fConst486;
	double fConst487;
	double fConst488;
	double fConst489;
	double fConst490;
	double fRec100_perm[4];
	double fConst491;
	double fConst492;
	double fConst493;
	double fConst494;
	double fConst495;
	double fRec99_perm[4];
	double fConst496;
	double fConst497;
	double fConst498;
	double fConst499;
	double fConst500;
	double fConst501;
	double fConst502;
	double fConst503;
	double fConst504;
	double fRec98_perm[4];
	double fConst505;
	double fConst506;
	double fConst507;
	double fConst508;
	double fConst509;
	double fConst510;
	double fRec97_perm[4];
	double fConst511;
	double fConst512;
	double fConst513;
	double fConst514;
	double fConst515;
	double fConst516;
	double fRec96_perm[4];
	double fConst517;
	double fConst518;
	double fConst519;
	double fRec95_perm[4];
	double fConst520;
	double fConst521;
	double fConst522;
	double fRec105_perm[4];
	double fConst523;
	double fConst524;
	double fConst525;
	double fConst526;
	double fConst527;
	double fConst528;
	double fRec104_perm[4];
	double fConst529;
	double fConst530;
	double fConst531;
	double fConst532;
	double fConst533;
	double fRec103_perm[4];
	double fConst534;
	double fConst535;
	double fRec102_perm[4];
	FAUSTFLOAT fHslider6;
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
		m->declare("effect.lib/cubicnl:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/cubicnl:copyright", "Julius O. Smith III");
		m->declare("effect.lib/cubicnl:license", "STK-4.3");
		m->declare("effect.lib/cubicnl_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/cubicnl_demo:copyright", "Julius O. Smith III");
		m->declare("effect.lib/cubicnl_demo:license", "STK-4.3");
		m->declare("effect.lib/cubicnl_nodc:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/cubicnl_nodc:copyright", "Julius O. Smith III");
		m->declare("effect.lib/cubicnl_nodc:license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("filename", "cubic_distortion.dsp");
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
		m->declare("name", "cubic_distortion");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/license", "STK-4.3");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "1.11");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 1.0 / fConst0;
		fConst2 = 6.283185307179586 / fConst0;
		fConst3 = std::tan(50265.48245743669 / fConst0);
		fConst4 = 1.0 / fConst3;
		fConst5 = 1.0 / ((fConst4 + 3.1897274020965583) / fConst3 + 4.076781969643807);
		fConst6 = (fConst4 + -3.1897274020965583) / fConst3 + 4.076781969643807;
		fConst7 = mydsp_faustpower2_f(fConst3);
		fConst8 = 1.0 / fConst7;
		fConst9 = 2.0 * (4.076781969643807 - fConst8);
		fConst10 = 0.0017661728399818856 / fConst7;
		fConst11 = fConst10 + 0.00040767818495825777;
		fConst12 = 2.0 * (0.00040767818495825777 - fConst10);
		fConst13 = 1.0 / ((fConst4 + 0.7431304601070396) / fConst3 + 1.450071084655647);
		fConst14 = (fConst4 + -0.7431304601070396) / fConst3 + 1.450071084655647;
		fConst15 = 2.0 * (1.450071084655647 - fConst8);
		fConst16 = 11.052052171507189 / fConst7;
		fConst17 = fConst16 + 1.450071084655647;
		fConst18 = 2.0 * (1.450071084655647 - fConst16);
		fConst19 = 1.0 / ((fConst4 + 0.157482159302087) / fConst3 + 0.9351401670315425);
		fConst20 = (fConst4 + -0.157482159302087) / fConst3 + 0.9351401670315425;
		fConst21 = 2.0 * (0.9351401670315425 - fConst8);
		fConst22 = 1e+03 / fConst0;
		fConst23 = 50.063807016150385 / fConst7;
		fConst24 = fConst23 + 0.9351401670315425;
		fConst25 = 2.0 * (0.9351401670315425 - fConst23);
		fConst26 = 1.0 / ((fConst4 + 0.782413046821645) / fConst3 + 0.24529150870616);
		fConst27 = (fConst4 + -0.782413046821645) / fConst3 + 0.24529150870616;
		fConst28 = 2.0 * (0.24529150870616 - fConst8);
		fConst29 = 9.9999997055e-05 / fConst7;
		fConst30 = fConst29 + 0.000433227200555;
		fConst31 = 2.0 * (0.000433227200555 - fConst29);
		fConst32 = 1.0 / ((fConst4 + 0.512478641889141) / fConst3 + 0.689621364484675);
		fConst33 = (fConst4 + -0.512478641889141) / fConst3 + 0.689621364484675;
		fConst34 = 2.0 * (0.689621364484675 - fConst8);
		fConst35 = fConst8 + 7.621731298870603;
		fConst36 = 2.0 * (7.621731298870603 - fConst8);
		fConst37 = 1.0 / ((fConst4 + 0.168404871113589) / fConst3 + 1.069358407707312);
		fConst38 = (fConst4 + -0.168404871113589) / fConst3 + 1.069358407707312;
		fConst39 = 2.0 * (1.069358407707312 - fConst8);
		fConst40 = fConst8 + 53.53615295455673;
		fConst41 = 2.0 * (53.53615295455673 - fConst8);
		fConst42 = std::tan(31665.269715622984 / fConst0);
		fConst43 = 1.0 / fConst42;
		fConst44 = 1.0 / ((fConst43 + 3.1897274020965583) / fConst42 + 4.076781969643807);
		fConst45 = (fConst43 + -3.1897274020965583) / fConst42 + 4.076781969643807;
		fConst46 = mydsp_faustpower2_f(fConst42);
		fConst47 = 1.0 / fConst46;
		fConst48 = 2.0 * (4.076781969643807 - fConst47);
		fConst49 = 0.0017661728399818856 / fConst46;
		fConst50 = fConst49 + 0.00040767818495825777;
		fConst51 = 2.0 * (0.00040767818495825777 - fConst49);
		fConst52 = 1.0 / ((fConst43 + 0.7431304601070396) / fConst42 + 1.450071084655647);
		fConst53 = (fConst43 + -0.7431304601070396) / fConst42 + 1.450071084655647;
		fConst54 = 2.0 * (1.450071084655647 - fConst47);
		fConst55 = 11.052052171507189 / fConst46;
		fConst56 = fConst55 + 1.450071084655647;
		fConst57 = 2.0 * (1.450071084655647 - fConst55);
		fConst58 = 1.0 / ((fConst43 + 0.157482159302087) / fConst42 + 0.9351401670315425);
		fConst59 = (fConst43 + -0.157482159302087) / fConst42 + 0.9351401670315425;
		fConst60 = 2.0 * (0.9351401670315425 - fConst47);
		fConst61 = 50.063807016150385 / fConst46;
		fConst62 = fConst61 + 0.9351401670315425;
		fConst63 = 2.0 * (0.9351401670315425 - fConst61);
		fConst64 = 1.0 / ((fConst43 + 0.782413046821645) / fConst42 + 0.24529150870616);
		fConst65 = (fConst43 + -0.782413046821645) / fConst42 + 0.24529150870616;
		fConst66 = 2.0 * (0.24529150870616 - fConst47);
		fConst67 = 9.9999997055e-05 / fConst46;
		fConst68 = fConst67 + 0.000433227200555;
		fConst69 = 2.0 * (0.000433227200555 - fConst67);
		fConst70 = 1.0 / ((fConst43 + 0.512478641889141) / fConst42 + 0.689621364484675);
		fConst71 = (fConst43 + -0.512478641889141) / fConst42 + 0.689621364484675;
		fConst72 = 2.0 * (0.689621364484675 - fConst47);
		fConst73 = fConst47 + 7.621731298870603;
		fConst74 = 2.0 * (7.621731298870603 - fConst47);
		fConst75 = 1.0 / ((fConst43 + 0.168404871113589) / fConst42 + 1.069358407707312);
		fConst76 = (fConst43 + -0.168404871113589) / fConst42 + 1.069358407707312;
		fConst77 = 2.0 * (1.069358407707312 - fConst47);
		fConst78 = fConst47 + 53.53615295455673;
		fConst79 = 2.0 * (53.53615295455673 - fConst47);
		fConst80 = std::tan(19947.869932656024 / fConst0);
		fConst81 = 1.0 / fConst80;
		fConst82 = 1.0 / ((fConst81 + 3.1897274020965583) / fConst80 + 4.076781969643807);
		fConst83 = (fConst81 + -3.1897274020965583) / fConst80 + 4.076781969643807;
		fConst84 = mydsp_faustpower2_f(fConst80);
		fConst85 = 1.0 / fConst84;
		fConst86 = 2.0 * (4.076781969643807 - fConst85);
		fConst87 = 0.0017661728399818856 / fConst84;
		fConst88 = fConst87 + 0.00040767818495825777;
		fConst89 = 2.0 * (0.00040767818495825777 - fConst87);
		fConst90 = 1.0 / ((fConst81 + 0.7431304601070396) / fConst80 + 1.450071084655647);
		fConst91 = (fConst81 + -0.7431304601070396) / fConst80 + 1.450071084655647;
		fConst92 = 2.0 * (1.450071084655647 - fConst85);
		fConst93 = 11.052052171507189 / fConst84;
		fConst94 = fConst93 + 1.450071084655647;
		fConst95 = 2.0 * (1.450071084655647 - fConst93);
		fConst96 = 1.0 / ((fConst81 + 0.157482159302087) / fConst80 + 0.9351401670315425);
		fConst97 = (fConst81 + -0.157482159302087) / fConst80 + 0.9351401670315425;
		fConst98 = 2.0 * (0.9351401670315425 - fConst85);
		fConst99 = 50.063807016150385 / fConst84;
		fConst100 = fConst99 + 0.9351401670315425;
		fConst101 = 2.0 * (0.9351401670315425 - fConst99);
		fConst102 = 1.0 / ((fConst81 + 0.782413046821645) / fConst80 + 0.24529150870616);
		fConst103 = (fConst81 + -0.782413046821645) / fConst80 + 0.24529150870616;
		fConst104 = 2.0 * (0.24529150870616 - fConst85);
		fConst105 = 9.9999997055e-05 / fConst84;
		fConst106 = fConst105 + 0.000433227200555;
		fConst107 = 2.0 * (0.000433227200555 - fConst105);
		fConst108 = 1.0 / ((fConst81 + 0.512478641889141) / fConst80 + 0.689621364484675);
		fConst109 = (fConst81 + -0.512478641889141) / fConst80 + 0.689621364484675;
		fConst110 = 2.0 * (0.689621364484675 - fConst85);
		fConst111 = fConst85 + 7.621731298870603;
		fConst112 = 2.0 * (7.621731298870603 - fConst85);
		fConst113 = 1.0 / ((fConst81 + 0.168404871113589) / fConst80 + 1.069358407707312);
		fConst114 = (fConst81 + -0.168404871113589) / fConst80 + 1.069358407707312;
		fConst115 = 2.0 * (1.069358407707312 - fConst85);
		fConst116 = fConst85 + 53.53615295455673;
		fConst117 = 2.0 * (53.53615295455673 - fConst85);
		fConst118 = std::tan(12566.370614359172 / fConst0);
		fConst119 = 1.0 / fConst118;
		fConst120 = 1.0 / ((fConst119 + 3.1897274020965583) / fConst118 + 4.076781969643807);
		fConst121 = (fConst119 + -3.1897274020965583) / fConst118 + 4.076781969643807;
		fConst122 = mydsp_faustpower2_f(fConst118);
		fConst123 = 1.0 / fConst122;
		fConst124 = 2.0 * (4.076781969643807 - fConst123);
		fConst125 = 0.0017661728399818856 / fConst122;
		fConst126 = fConst125 + 0.00040767818495825777;
		fConst127 = 2.0 * (0.00040767818495825777 - fConst125);
		fConst128 = 1.0 / ((fConst119 + 0.7431304601070396) / fConst118 + 1.450071084655647);
		fConst129 = (fConst119 + -0.7431304601070396) / fConst118 + 1.450071084655647;
		fConst130 = 2.0 * (1.450071084655647 - fConst123);
		fConst131 = 11.052052171507189 / fConst122;
		fConst132 = fConst131 + 1.450071084655647;
		fConst133 = 2.0 * (1.450071084655647 - fConst131);
		fConst134 = 1.0 / ((fConst119 + 0.157482159302087) / fConst118 + 0.9351401670315425);
		fConst135 = (fConst119 + -0.157482159302087) / fConst118 + 0.9351401670315425;
		fConst136 = 2.0 * (0.9351401670315425 - fConst123);
		fConst137 = 50.063807016150385 / fConst122;
		fConst138 = fConst137 + 0.9351401670315425;
		fConst139 = 2.0 * (0.9351401670315425 - fConst137);
		fConst140 = 1.0 / ((fConst119 + 0.782413046821645) / fConst118 + 0.24529150870616);
		fConst141 = (fConst119 + -0.782413046821645) / fConst118 + 0.24529150870616;
		fConst142 = 2.0 * (0.24529150870616 - fConst123);
		fConst143 = 9.9999997055e-05 / fConst122;
		fConst144 = fConst143 + 0.000433227200555;
		fConst145 = 2.0 * (0.000433227200555 - fConst143);
		fConst146 = 1.0 / ((fConst119 + 0.512478641889141) / fConst118 + 0.689621364484675);
		fConst147 = (fConst119 + -0.512478641889141) / fConst118 + 0.689621364484675;
		fConst148 = 2.0 * (0.689621364484675 - fConst123);
		fConst149 = fConst123 + 7.621731298870603;
		fConst150 = 2.0 * (7.621731298870603 - fConst123);
		fConst151 = 1.0 / ((fConst119 + 0.168404871113589) / fConst118 + 1.069358407707312);
		fConst152 = (fConst119 + -0.168404871113589) / fConst118 + 1.069358407707312;
		fConst153 = 2.0 * (1.069358407707312 - fConst123);
		fConst154 = fConst123 + 53.53615295455673;
		fConst155 = 2.0 * (53.53615295455673 - fConst123);
		fConst156 = std::tan(7916.317428905746 / fConst0);
		fConst157 = 1.0 / fConst156;
		fConst158 = 1.0 / ((fConst157 + 3.1897274020965583) / fConst156 + 4.076781969643807);
		fConst159 = (fConst157 + -3.1897274020965583) / fConst156 + 4.076781969643807;
		fConst160 = mydsp_faustpower2_f(fConst156);
		fConst161 = 1.0 / fConst160;
		fConst162 = 2.0 * (4.076781969643807 - fConst161);
		fConst163 = 0.0017661728399818856 / fConst160;
		fConst164 = fConst163 + 0.00040767818495825777;
		fConst165 = 2.0 * (0.00040767818495825777 - fConst163);
		fConst166 = 1.0 / ((fConst157 + 0.7431304601070396) / fConst156 + 1.450071084655647);
		fConst167 = (fConst157 + -0.7431304601070396) / fConst156 + 1.450071084655647;
		fConst168 = 2.0 * (1.450071084655647 - fConst161);
		fConst169 = 11.052052171507189 / fConst160;
		fConst170 = fConst169 + 1.450071084655647;
		fConst171 = 2.0 * (1.450071084655647 - fConst169);
		fConst172 = 1.0 / ((fConst157 + 0.157482159302087) / fConst156 + 0.9351401670315425);
		fConst173 = (fConst157 + -0.157482159302087) / fConst156 + 0.9351401670315425;
		fConst174 = 2.0 * (0.9351401670315425 - fConst161);
		fConst175 = 50.063807016150385 / fConst160;
		fConst176 = fConst175 + 0.9351401670315425;
		fConst177 = 2.0 * (0.9351401670315425 - fConst175);
		fConst178 = 1.0 / ((fConst157 + 0.782413046821645) / fConst156 + 0.24529150870616);
		fConst179 = (fConst157 + -0.782413046821645) / fConst156 + 0.24529150870616;
		fConst180 = 2.0 * (0.24529150870616 - fConst161);
		fConst181 = 9.9999997055e-05 / fConst160;
		fConst182 = fConst181 + 0.000433227200555;
		fConst183 = 2.0 * (0.000433227200555 - fConst181);
		fConst184 = 1.0 / ((fConst157 + 0.512478641889141) / fConst156 + 0.689621364484675);
		fConst185 = (fConst157 + -0.512478641889141) / fConst156 + 0.689621364484675;
		fConst186 = 2.0 * (0.689621364484675 - fConst161);
		fConst187 = fConst161 + 7.621731298870603;
		fConst188 = 2.0 * (7.621731298870603 - fConst161);
		fConst189 = 1.0 / ((fConst157 + 0.168404871113589) / fConst156 + 1.069358407707312);
		fConst190 = (fConst157 + -0.168404871113589) / fConst156 + 1.069358407707312;
		fConst191 = 2.0 * (1.069358407707312 - fConst161);
		fConst192 = fConst161 + 53.53615295455673;
		fConst193 = 2.0 * (53.53615295455673 - fConst161);
		fConst194 = std::tan(4986.967483164005 / fConst0);
		fConst195 = 1.0 / fConst194;
		fConst196 = 1.0 / ((fConst195 + 3.1897274020965583) / fConst194 + 4.076781969643807);
		fConst197 = (fConst195 + -3.1897274020965583) / fConst194 + 4.076781969643807;
		fConst198 = mydsp_faustpower2_f(fConst194);
		fConst199 = 1.0 / fConst198;
		fConst200 = 2.0 * (4.076781969643807 - fConst199);
		fConst201 = 0.0017661728399818856 / fConst198;
		fConst202 = fConst201 + 0.00040767818495825777;
		fConst203 = 2.0 * (0.00040767818495825777 - fConst201);
		fConst204 = 1.0 / ((fConst195 + 0.7431304601070396) / fConst194 + 1.450071084655647);
		fConst205 = (fConst195 + -0.7431304601070396) / fConst194 + 1.450071084655647;
		fConst206 = 2.0 * (1.450071084655647 - fConst199);
		fConst207 = 11.052052171507189 / fConst198;
		fConst208 = fConst207 + 1.450071084655647;
		fConst209 = 2.0 * (1.450071084655647 - fConst207);
		fConst210 = 1.0 / ((fConst195 + 0.157482159302087) / fConst194 + 0.9351401670315425);
		fConst211 = (fConst195 + -0.157482159302087) / fConst194 + 0.9351401670315425;
		fConst212 = 2.0 * (0.9351401670315425 - fConst199);
		fConst213 = 50.063807016150385 / fConst198;
		fConst214 = fConst213 + 0.9351401670315425;
		fConst215 = 2.0 * (0.9351401670315425 - fConst213);
		fConst216 = 1.0 / ((fConst195 + 0.782413046821645) / fConst194 + 0.24529150870616);
		fConst217 = (fConst195 + -0.782413046821645) / fConst194 + 0.24529150870616;
		fConst218 = 2.0 * (0.24529150870616 - fConst199);
		fConst219 = 9.9999997055e-05 / fConst198;
		fConst220 = fConst219 + 0.000433227200555;
		fConst221 = 2.0 * (0.000433227200555 - fConst219);
		fConst222 = 1.0 / ((fConst195 + 0.512478641889141) / fConst194 + 0.689621364484675);
		fConst223 = (fConst195 + -0.512478641889141) / fConst194 + 0.689621364484675;
		fConst224 = 2.0 * (0.689621364484675 - fConst199);
		fConst225 = fConst199 + 7.621731298870603;
		fConst226 = 2.0 * (7.621731298870603 - fConst199);
		fConst227 = 1.0 / ((fConst195 + 0.168404871113589) / fConst194 + 1.069358407707312);
		fConst228 = (fConst195 + -0.168404871113589) / fConst194 + 1.069358407707312;
		fConst229 = 2.0 * (1.069358407707312 - fConst199);
		fConst230 = fConst199 + 53.53615295455673;
		fConst231 = 2.0 * (53.53615295455673 - fConst199);
		fConst232 = std::tan(3141.592653589793 / fConst0);
		fConst233 = 1.0 / fConst232;
		fConst234 = 1.0 / ((fConst233 + 3.1897274020965583) / fConst232 + 4.076781969643807);
		fConst235 = (fConst233 + -3.1897274020965583) / fConst232 + 4.076781969643807;
		fConst236 = mydsp_faustpower2_f(fConst232);
		fConst237 = 1.0 / fConst236;
		fConst238 = 2.0 * (4.076781969643807 - fConst237);
		fConst239 = 0.0017661728399818856 / fConst236;
		fConst240 = fConst239 + 0.00040767818495825777;
		fConst241 = 2.0 * (0.00040767818495825777 - fConst239);
		fConst242 = 1.0 / ((fConst233 + 0.7431304601070396) / fConst232 + 1.450071084655647);
		fConst243 = (fConst233 + -0.7431304601070396) / fConst232 + 1.450071084655647;
		fConst244 = 2.0 * (1.450071084655647 - fConst237);
		fConst245 = 11.052052171507189 / fConst236;
		fConst246 = fConst245 + 1.450071084655647;
		fConst247 = 2.0 * (1.450071084655647 - fConst245);
		fConst248 = 1.0 / ((fConst233 + 0.157482159302087) / fConst232 + 0.9351401670315425);
		fConst249 = (fConst233 + -0.157482159302087) / fConst232 + 0.9351401670315425;
		fConst250 = 2.0 * (0.9351401670315425 - fConst237);
		fConst251 = 50.063807016150385 / fConst236;
		fConst252 = fConst251 + 0.9351401670315425;
		fConst253 = 2.0 * (0.9351401670315425 - fConst251);
		fConst254 = 1.0 / ((fConst233 + 0.782413046821645) / fConst232 + 0.24529150870616);
		fConst255 = (fConst233 + -0.782413046821645) / fConst232 + 0.24529150870616;
		fConst256 = 2.0 * (0.24529150870616 - fConst237);
		fConst257 = 9.9999997055e-05 / fConst236;
		fConst258 = fConst257 + 0.000433227200555;
		fConst259 = 2.0 * (0.000433227200555 - fConst257);
		fConst260 = 1.0 / ((fConst233 + 0.512478641889141) / fConst232 + 0.689621364484675);
		fConst261 = (fConst233 + -0.512478641889141) / fConst232 + 0.689621364484675;
		fConst262 = 2.0 * (0.689621364484675 - fConst237);
		fConst263 = fConst237 + 7.621731298870603;
		fConst264 = 2.0 * (7.621731298870603 - fConst237);
		fConst265 = 1.0 / ((fConst233 + 0.168404871113589) / fConst232 + 1.069358407707312);
		fConst266 = (fConst233 + -0.168404871113589) / fConst232 + 1.069358407707312;
		fConst267 = 2.0 * (1.069358407707312 - fConst237);
		fConst268 = fConst237 + 53.53615295455673;
		fConst269 = 2.0 * (53.53615295455673 - fConst237);
		fConst270 = std::tan(1979.079357226436 / fConst0);
		fConst271 = 1.0 / fConst270;
		fConst272 = 1.0 / ((fConst271 + 3.1897274020965583) / fConst270 + 4.076781969643807);
		fConst273 = (fConst271 + -3.1897274020965583) / fConst270 + 4.076781969643807;
		fConst274 = mydsp_faustpower2_f(fConst270);
		fConst275 = 1.0 / fConst274;
		fConst276 = 2.0 * (4.076781969643807 - fConst275);
		fConst277 = 0.0017661728399818856 / fConst274;
		fConst278 = fConst277 + 0.00040767818495825777;
		fConst279 = 2.0 * (0.00040767818495825777 - fConst277);
		fConst280 = 1.0 / ((fConst271 + 0.7431304601070396) / fConst270 + 1.450071084655647);
		fConst281 = (fConst271 + -0.7431304601070396) / fConst270 + 1.450071084655647;
		fConst282 = 2.0 * (1.450071084655647 - fConst275);
		fConst283 = 11.052052171507189 / fConst274;
		fConst284 = fConst283 + 1.450071084655647;
		fConst285 = 2.0 * (1.450071084655647 - fConst283);
		fConst286 = 1.0 / ((fConst271 + 0.157482159302087) / fConst270 + 0.9351401670315425);
		fConst287 = (fConst271 + -0.157482159302087) / fConst270 + 0.9351401670315425;
		fConst288 = 2.0 * (0.9351401670315425 - fConst275);
		fConst289 = 50.063807016150385 / fConst274;
		fConst290 = fConst289 + 0.9351401670315425;
		fConst291 = 2.0 * (0.9351401670315425 - fConst289);
		fConst292 = 1.0 / ((fConst271 + 0.782413046821645) / fConst270 + 0.24529150870616);
		fConst293 = (fConst271 + -0.782413046821645) / fConst270 + 0.24529150870616;
		fConst294 = 2.0 * (0.24529150870616 - fConst275);
		fConst295 = 9.9999997055e-05 / fConst274;
		fConst296 = fConst295 + 0.000433227200555;
		fConst297 = 2.0 * (0.000433227200555 - fConst295);
		fConst298 = 1.0 / ((fConst271 + 0.512478641889141) / fConst270 + 0.689621364484675);
		fConst299 = (fConst271 + -0.512478641889141) / fConst270 + 0.689621364484675;
		fConst300 = 2.0 * (0.689621364484675 - fConst275);
		fConst301 = fConst275 + 7.621731298870603;
		fConst302 = 2.0 * (7.621731298870603 - fConst275);
		fConst303 = 1.0 / ((fConst271 + 0.168404871113589) / fConst270 + 1.069358407707312);
		fConst304 = (fConst271 + -0.168404871113589) / fConst270 + 1.069358407707312;
		fConst305 = 2.0 * (1.069358407707312 - fConst275);
		fConst306 = fConst275 + 53.53615295455673;
		fConst307 = 2.0 * (53.53615295455673 - fConst275);
		fConst308 = std::tan(1246.7418707910015 / fConst0);
		fConst309 = 1.0 / fConst308;
		fConst310 = 1.0 / ((fConst309 + 3.1897274020965583) / fConst308 + 4.076781969643807);
		fConst311 = (fConst309 + -3.1897274020965583) / fConst308 + 4.076781969643807;
		fConst312 = mydsp_faustpower2_f(fConst308);
		fConst313 = 1.0 / fConst312;
		fConst314 = 2.0 * (4.076781969643807 - fConst313);
		fConst315 = 0.0017661728399818856 / fConst312;
		fConst316 = fConst315 + 0.00040767818495825777;
		fConst317 = 2.0 * (0.00040767818495825777 - fConst315);
		fConst318 = 1.0 / ((fConst309 + 0.7431304601070396) / fConst308 + 1.450071084655647);
		fConst319 = (fConst309 + -0.7431304601070396) / fConst308 + 1.450071084655647;
		fConst320 = 2.0 * (1.450071084655647 - fConst313);
		fConst321 = 11.052052171507189 / fConst312;
		fConst322 = fConst321 + 1.450071084655647;
		fConst323 = 2.0 * (1.450071084655647 - fConst321);
		fConst324 = 1.0 / ((fConst309 + 0.157482159302087) / fConst308 + 0.9351401670315425);
		fConst325 = (fConst309 + -0.157482159302087) / fConst308 + 0.9351401670315425;
		fConst326 = 2.0 * (0.9351401670315425 - fConst313);
		fConst327 = 50.063807016150385 / fConst312;
		fConst328 = fConst327 + 0.9351401670315425;
		fConst329 = 2.0 * (0.9351401670315425 - fConst327);
		fConst330 = 1.0 / ((fConst309 + 0.782413046821645) / fConst308 + 0.24529150870616);
		fConst331 = (fConst309 + -0.782413046821645) / fConst308 + 0.24529150870616;
		fConst332 = 2.0 * (0.24529150870616 - fConst313);
		fConst333 = 9.9999997055e-05 / fConst312;
		fConst334 = fConst333 + 0.000433227200555;
		fConst335 = 2.0 * (0.000433227200555 - fConst333);
		fConst336 = 1.0 / ((fConst309 + 0.512478641889141) / fConst308 + 0.689621364484675);
		fConst337 = (fConst309 + -0.512478641889141) / fConst308 + 0.689621364484675;
		fConst338 = 2.0 * (0.689621364484675 - fConst313);
		fConst339 = fConst313 + 7.621731298870603;
		fConst340 = 2.0 * (7.621731298870603 - fConst313);
		fConst341 = 1.0 / ((fConst309 + 0.168404871113589) / fConst308 + 1.069358407707312);
		fConst342 = (fConst309 + -0.168404871113589) / fConst308 + 1.069358407707312;
		fConst343 = 2.0 * (1.069358407707312 - fConst313);
		fConst344 = fConst313 + 53.53615295455673;
		fConst345 = 2.0 * (53.53615295455673 - fConst313);
		fConst346 = std::tan(785.3981633974482 / fConst0);
		fConst347 = 1.0 / fConst346;
		fConst348 = 1.0 / ((fConst347 + 3.1897274020965583) / fConst346 + 4.076781969643807);
		fConst349 = (fConst347 + -3.1897274020965583) / fConst346 + 4.076781969643807;
		fConst350 = mydsp_faustpower2_f(fConst346);
		fConst351 = 1.0 / fConst350;
		fConst352 = 2.0 * (4.076781969643807 - fConst351);
		fConst353 = 0.0017661728399818856 / fConst350;
		fConst354 = fConst353 + 0.00040767818495825777;
		fConst355 = 2.0 * (0.00040767818495825777 - fConst353);
		fConst356 = 1.0 / ((fConst347 + 0.7431304601070396) / fConst346 + 1.450071084655647);
		fConst357 = (fConst347 + -0.7431304601070396) / fConst346 + 1.450071084655647;
		fConst358 = 2.0 * (1.450071084655647 - fConst351);
		fConst359 = 11.052052171507189 / fConst350;
		fConst360 = fConst359 + 1.450071084655647;
		fConst361 = 2.0 * (1.450071084655647 - fConst359);
		fConst362 = 1.0 / ((fConst347 + 0.157482159302087) / fConst346 + 0.9351401670315425);
		fConst363 = (fConst347 + -0.157482159302087) / fConst346 + 0.9351401670315425;
		fConst364 = 2.0 * (0.9351401670315425 - fConst351);
		fConst365 = 50.063807016150385 / fConst350;
		fConst366 = fConst365 + 0.9351401670315425;
		fConst367 = 2.0 * (0.9351401670315425 - fConst365);
		fConst368 = 1.0 / ((fConst347 + 0.782413046821645) / fConst346 + 0.24529150870616);
		fConst369 = (fConst347 + -0.782413046821645) / fConst346 + 0.24529150870616;
		fConst370 = 2.0 * (0.24529150870616 - fConst351);
		fConst371 = 9.9999997055e-05 / fConst350;
		fConst372 = fConst371 + 0.000433227200555;
		fConst373 = 2.0 * (0.000433227200555 - fConst371);
		fConst374 = 1.0 / ((fConst347 + 0.512478641889141) / fConst346 + 0.689621364484675);
		fConst375 = (fConst347 + -0.512478641889141) / fConst346 + 0.689621364484675;
		fConst376 = 2.0 * (0.689621364484675 - fConst351);
		fConst377 = fConst351 + 7.621731298870603;
		fConst378 = 2.0 * (7.621731298870603 - fConst351);
		fConst379 = 1.0 / ((fConst347 + 0.168404871113589) / fConst346 + 1.069358407707312);
		fConst380 = (fConst347 + -0.168404871113589) / fConst346 + 1.069358407707312;
		fConst381 = 2.0 * (1.069358407707312 - fConst351);
		fConst382 = fConst351 + 53.53615295455673;
		fConst383 = 2.0 * (53.53615295455673 - fConst351);
		fConst384 = std::tan(494.769839306609 / fConst0);
		fConst385 = 1.0 / fConst384;
		fConst386 = 1.0 / ((fConst385 + 3.1897274020965583) / fConst384 + 4.076781969643807);
		fConst387 = (fConst385 + -3.1897274020965583) / fConst384 + 4.076781969643807;
		fConst388 = mydsp_faustpower2_f(fConst384);
		fConst389 = 1.0 / fConst388;
		fConst390 = 2.0 * (4.076781969643807 - fConst389);
		fConst391 = 0.0017661728399818856 / fConst388;
		fConst392 = fConst391 + 0.00040767818495825777;
		fConst393 = 2.0 * (0.00040767818495825777 - fConst391);
		fConst394 = 1.0 / ((fConst385 + 0.7431304601070396) / fConst384 + 1.450071084655647);
		fConst395 = (fConst385 + -0.7431304601070396) / fConst384 + 1.450071084655647;
		fConst396 = 2.0 * (1.450071084655647 - fConst389);
		fConst397 = 11.052052171507189 / fConst388;
		fConst398 = fConst397 + 1.450071084655647;
		fConst399 = 2.0 * (1.450071084655647 - fConst397);
		fConst400 = 1.0 / ((fConst385 + 0.157482159302087) / fConst384 + 0.9351401670315425);
		fConst401 = (fConst385 + -0.157482159302087) / fConst384 + 0.9351401670315425;
		fConst402 = 2.0 * (0.9351401670315425 - fConst389);
		fConst403 = 50.063807016150385 / fConst388;
		fConst404 = fConst403 + 0.9351401670315425;
		fConst405 = 2.0 * (0.9351401670315425 - fConst403);
		fConst406 = 1.0 / ((fConst385 + 0.782413046821645) / fConst384 + 0.24529150870616);
		fConst407 = (fConst385 + -0.782413046821645) / fConst384 + 0.24529150870616;
		fConst408 = 2.0 * (0.24529150870616 - fConst389);
		fConst409 = 9.9999997055e-05 / fConst388;
		fConst410 = fConst409 + 0.000433227200555;
		fConst411 = 2.0 * (0.000433227200555 - fConst409);
		fConst412 = 1.0 / ((fConst385 + 0.512478641889141) / fConst384 + 0.689621364484675);
		fConst413 = (fConst385 + -0.512478641889141) / fConst384 + 0.689621364484675;
		fConst414 = 2.0 * (0.689621364484675 - fConst389);
		fConst415 = fConst389 + 7.621731298870603;
		fConst416 = 2.0 * (7.621731298870603 - fConst389);
		fConst417 = 1.0 / ((fConst385 + 0.168404871113589) / fConst384 + 1.069358407707312);
		fConst418 = (fConst385 + -0.168404871113589) / fConst384 + 1.069358407707312;
		fConst419 = 2.0 * (1.069358407707312 - fConst389);
		fConst420 = fConst389 + 53.53615295455673;
		fConst421 = 2.0 * (53.53615295455673 - fConst389);
		fConst422 = std::tan(311.68546769775037 / fConst0);
		fConst423 = 1.0 / fConst422;
		fConst424 = 1.0 / ((fConst423 + 3.1897274020965583) / fConst422 + 4.076781969643807);
		fConst425 = (fConst423 + -3.1897274020965583) / fConst422 + 4.076781969643807;
		fConst426 = mydsp_faustpower2_f(fConst422);
		fConst427 = 1.0 / fConst426;
		fConst428 = 2.0 * (4.076781969643807 - fConst427);
		fConst429 = 0.0017661728399818856 / fConst426;
		fConst430 = fConst429 + 0.00040767818495825777;
		fConst431 = 2.0 * (0.00040767818495825777 - fConst429);
		fConst432 = 1.0 / ((fConst423 + 0.7431304601070396) / fConst422 + 1.450071084655647);
		fConst433 = (fConst423 + -0.7431304601070396) / fConst422 + 1.450071084655647;
		fConst434 = 2.0 * (1.450071084655647 - fConst427);
		fConst435 = 11.052052171507189 / fConst426;
		fConst436 = fConst435 + 1.450071084655647;
		fConst437 = 2.0 * (1.450071084655647 - fConst435);
		fConst438 = 1.0 / ((fConst423 + 0.157482159302087) / fConst422 + 0.9351401670315425);
		fConst439 = (fConst423 + -0.157482159302087) / fConst422 + 0.9351401670315425;
		fConst440 = 2.0 * (0.9351401670315425 - fConst427);
		fConst441 = 50.063807016150385 / fConst426;
		fConst442 = fConst441 + 0.9351401670315425;
		fConst443 = 2.0 * (0.9351401670315425 - fConst441);
		fConst444 = 1.0 / ((fConst423 + 0.782413046821645) / fConst422 + 0.24529150870616);
		fConst445 = (fConst423 + -0.782413046821645) / fConst422 + 0.24529150870616;
		fConst446 = 2.0 * (0.24529150870616 - fConst427);
		fConst447 = 9.9999997055e-05 / fConst426;
		fConst448 = fConst447 + 0.000433227200555;
		fConst449 = 2.0 * (0.000433227200555 - fConst447);
		fConst450 = 1.0 / ((fConst423 + 0.512478641889141) / fConst422 + 0.689621364484675);
		fConst451 = (fConst423 + -0.512478641889141) / fConst422 + 0.689621364484675;
		fConst452 = 2.0 * (0.689621364484675 - fConst427);
		fConst453 = fConst427 + 7.621731298870603;
		fConst454 = 2.0 * (7.621731298870603 - fConst427);
		fConst455 = 1.0 / ((fConst423 + 0.168404871113589) / fConst422 + 1.069358407707312);
		fConst456 = (fConst423 + -0.168404871113589) / fConst422 + 1.069358407707312;
		fConst457 = 2.0 * (1.069358407707312 - fConst427);
		fConst458 = fConst427 + 53.53615295455673;
		fConst459 = 2.0 * (53.53615295455673 - fConst427);
		fConst460 = std::tan(196.34954084936206 / fConst0);
		fConst461 = 1.0 / fConst460;
		fConst462 = 1.0 / ((fConst461 + 3.1897274020965583) / fConst460 + 4.076781969643807);
		fConst463 = (fConst461 + -3.1897274020965583) / fConst460 + 4.076781969643807;
		fConst464 = mydsp_faustpower2_f(fConst460);
		fConst465 = 1.0 / fConst464;
		fConst466 = 2.0 * (4.076781969643807 - fConst465);
		fConst467 = 0.0017661728399818856 / fConst464;
		fConst468 = fConst467 + 0.00040767818495825777;
		fConst469 = 2.0 * (0.00040767818495825777 - fConst467);
		fConst470 = 1.0 / ((fConst461 + 0.7431304601070396) / fConst460 + 1.450071084655647);
		fConst471 = (fConst461 + -0.7431304601070396) / fConst460 + 1.450071084655647;
		fConst472 = 2.0 * (1.450071084655647 - fConst465);
		fConst473 = 11.052052171507189 / fConst464;
		fConst474 = fConst473 + 1.450071084655647;
		fConst475 = 2.0 * (1.450071084655647 - fConst473);
		fConst476 = 1.0 / ((fConst461 + 0.157482159302087) / fConst460 + 0.9351401670315425);
		fConst477 = (fConst461 + -0.157482159302087) / fConst460 + 0.9351401670315425;
		fConst478 = 2.0 * (0.9351401670315425 - fConst465);
		fConst479 = 50.063807016150385 / fConst464;
		fConst480 = fConst479 + 0.9351401670315425;
		fConst481 = 2.0 * (0.9351401670315425 - fConst479);
		fConst482 = 1.0 / ((fConst461 + 0.782413046821645) / fConst460 + 0.24529150870616);
		fConst483 = (fConst461 + -0.782413046821645) / fConst460 + 0.24529150870616;
		fConst484 = 2.0 * (0.24529150870616 - fConst465);
		fConst485 = 9.9999997055e-05 / fConst464;
		fConst486 = fConst485 + 0.000433227200555;
		fConst487 = 2.0 * (0.000433227200555 - fConst485);
		fConst488 = 1.0 / ((fConst461 + 0.512478641889141) / fConst460 + 0.689621364484675);
		fConst489 = (fConst461 + -0.512478641889141) / fConst460 + 0.689621364484675;
		fConst490 = 2.0 * (0.689621364484675 - fConst465);
		fConst491 = fConst465 + 7.621731298870603;
		fConst492 = 2.0 * (7.621731298870603 - fConst465);
		fConst493 = 1.0 / ((fConst461 + 0.168404871113589) / fConst460 + 1.069358407707312);
		fConst494 = (fConst461 + -0.168404871113589) / fConst460 + 1.069358407707312;
		fConst495 = 2.0 * (1.069358407707312 - fConst465);
		fConst496 = fConst465 + 53.53615295455673;
		fConst497 = 2.0 * (53.53615295455673 - fConst465);
		fConst498 = std::tan(123.69245982665232 / fConst0);
		fConst499 = 1.0 / fConst498;
		fConst500 = 1.0 / ((fConst499 + 3.1897274020965583) / fConst498 + 4.076781969643807);
		fConst501 = (fConst499 + -3.1897274020965583) / fConst498 + 4.076781969643807;
		fConst502 = mydsp_faustpower2_f(fConst498);
		fConst503 = 1.0 / fConst502;
		fConst504 = 2.0 * (4.076781969643807 - fConst503);
		fConst505 = 0.0017661728399818856 / fConst502;
		fConst506 = fConst505 + 0.00040767818495825777;
		fConst507 = 2.0 * (0.00040767818495825777 - fConst505);
		fConst508 = 1.0 / ((fConst499 + 0.7431304601070396) / fConst498 + 1.450071084655647);
		fConst509 = (fConst499 + -0.7431304601070396) / fConst498 + 1.450071084655647;
		fConst510 = 2.0 * (1.450071084655647 - fConst503);
		fConst511 = 11.052052171507189 / fConst502;
		fConst512 = fConst511 + 1.450071084655647;
		fConst513 = 2.0 * (1.450071084655647 - fConst511);
		fConst514 = 1.0 / ((fConst499 + 0.157482159302087) / fConst498 + 0.9351401670315425);
		fConst515 = (fConst499 + -0.157482159302087) / fConst498 + 0.9351401670315425;
		fConst516 = 2.0 * (0.9351401670315425 - fConst503);
		fConst517 = 50.063807016150385 / fConst502;
		fConst518 = fConst517 + 0.9351401670315425;
		fConst519 = 2.0 * (0.9351401670315425 - fConst517);
		fConst520 = 1.0 / ((fConst499 + 0.782413046821645) / fConst498 + 0.24529150870616);
		fConst521 = (fConst499 + -0.782413046821645) / fConst498 + 0.24529150870616;
		fConst522 = 2.0 * (0.24529150870616 - fConst503);
		fConst523 = 9.9999997055e-05 / fConst502;
		fConst524 = fConst523 + 0.000433227200555;
		fConst525 = 2.0 * (0.000433227200555 - fConst523);
		fConst526 = 1.0 / ((fConst499 + 0.512478641889141) / fConst498 + 0.689621364484675);
		fConst527 = (fConst499 + -0.512478641889141) / fConst498 + 0.689621364484675;
		fConst528 = 2.0 * (0.689621364484675 - fConst503);
		fConst529 = fConst503 + 7.621731298870603;
		fConst530 = 2.0 * (7.621731298870603 - fConst503);
		fConst531 = 1.0 / ((fConst499 + 0.168404871113589) / fConst498 + 1.069358407707312);
		fConst532 = (fConst499 + -0.168404871113589) / fConst498 + 1.069358407707312;
		fConst533 = 2.0 * (1.069358407707312 - fConst503);
		fConst534 = fConst503 + 53.53615295455673;
		fConst535 = 2.0 * (53.53615295455673 - fConst503);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider1 = static_cast<FAUSTFLOAT>(-2e+01);
		fHslider2 = static_cast<FAUSTFLOAT>(0.1);
		fHslider3 = static_cast<FAUSTFLOAT>(49.0);
		fHslider4 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider5 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider6 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec1_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec2_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec5_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec3_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			iVec0_perm[l4] = 0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec4_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec6_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fYec0_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec0_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec10_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec9_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec8_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec7_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec17_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec16_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec15_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec14_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec13_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec12_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec11_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec24_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec23_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec22_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec21_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec20_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec19_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fRec18_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec31_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec30_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec29_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec28_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec27_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec26_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec25_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec38_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec37_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec36_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec35_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec34_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec33_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec32_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec45_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec44_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec43_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec42_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec41_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec40_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec39_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec52_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec51_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec50_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec49_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec48_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec47_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec46_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec59_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec58_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec57_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec56_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec55_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec54_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec53_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec66_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec65_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec64_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec63_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec62_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec61_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec60_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec73_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec72_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec71_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fRec70_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec69_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec68_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec67_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec80_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec79_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec78_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec77_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec76_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec75_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec74_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec87_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec86_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec85_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec84_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec83_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec82_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec81_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec94_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec93_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec92_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec91_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec90_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec89_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec88_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fRec101_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec100_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec99_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec98_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec97_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec96_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec95_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec105_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec104_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec103_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec102_perm[l107] = 0.0;
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
		ui_interface->openVerticalBox("cubic_distortion");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "Sine oscillator based on 2D vector rotation");
		ui_interface->openVerticalBox("SINE WAVE OSCILLATOR oscrs");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("Amplitude", &fHslider1, FAUSTFLOAT(-2e+01), FAUSTFLOAT(-1.2e+02), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)");
		ui_interface->declare(&fHslider3, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider3, FAUSTFLOAT(49.0), FAUSTFLOAT(1.0), FAUSTFLOAT(88.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fHslider2, "unit", "sec");
		ui_interface->addHorizontalSlider("Portamento", &fHslider2, FAUSTFLOAT(0.1), FAUSTFLOAT(0.001), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.001));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html");
		ui_interface->openVerticalBox("CUBIC NONLINEARITY cubicnl");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the nonlinearity has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "tooltip", "Amount of distortion");
		ui_interface->addHorizontalSlider("Drive", &fHslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "tooltip", "Brings in even harmonics");
		ui_interface->addHorizontalSlider("Offset", &fHslider0, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
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
		ui_interface->declare(&fHslider5, "0", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider5, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider6, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * static_cast<double>(fHslider0);
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fHslider1));
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow2 = static_cast<double>(fHslider2);
		double fSlow3 = ((fSlow2 > 0.0) ? std::exp(-(fConst1 / fSlow2)) : 0.0);
		double fSlow4 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fHslider3) + -49.0)) * (1.0 - fSlow3);
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fZec0[4];
		double fZec1[4];
		double fZec2[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow5 = 0.0010000000000000009 * static_cast<double>(fHslider4);
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		int iSlow6 = static_cast<int>(static_cast<double>(fCheckbox0));
		double fZec3[4];
		double fZec4[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fZec5[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow7 = static_cast<double>(fHslider5);
		double fSlow8 = (((0.001 * fSlow7) > 0.0) ? std::exp(-(fConst22 / fSlow7)) : 0.0);
		double fSlow9 = 1.0 - fSlow8;
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fZec6[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fZec7[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		double fZec8[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fZec9[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fZec10[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fRec52_tmp[8];
		double* fRec52 = &fRec52_tmp[4];
		double fRec51_tmp[8];
		double* fRec51 = &fRec51_tmp[4];
		double fRec50_tmp[8];
		double* fRec50 = &fRec50_tmp[4];
		double fZec11[4];
		double fRec49_tmp[8];
		double* fRec49 = &fRec49_tmp[4];
		double fRec48_tmp[8];
		double* fRec48 = &fRec48_tmp[4];
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fRec59_tmp[8];
		double* fRec59 = &fRec59_tmp[4];
		double fRec58_tmp[8];
		double* fRec58 = &fRec58_tmp[4];
		double fRec57_tmp[8];
		double* fRec57 = &fRec57_tmp[4];
		double fZec12[4];
		double fRec56_tmp[8];
		double* fRec56 = &fRec56_tmp[4];
		double fRec55_tmp[8];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[8];
		double* fRec54 = &fRec54_tmp[4];
		double fRec53_tmp[8];
		double* fRec53 = &fRec53_tmp[4];
		double fRec66_tmp[8];
		double* fRec66 = &fRec66_tmp[4];
		double fRec65_tmp[8];
		double* fRec65 = &fRec65_tmp[4];
		double fRec64_tmp[8];
		double* fRec64 = &fRec64_tmp[4];
		double fZec13[4];
		double fRec63_tmp[8];
		double* fRec63 = &fRec63_tmp[4];
		double fRec62_tmp[8];
		double* fRec62 = &fRec62_tmp[4];
		double fRec61_tmp[8];
		double* fRec61 = &fRec61_tmp[4];
		double fRec60_tmp[8];
		double* fRec60 = &fRec60_tmp[4];
		double fRec73_tmp[8];
		double* fRec73 = &fRec73_tmp[4];
		double fRec72_tmp[8];
		double* fRec72 = &fRec72_tmp[4];
		double fRec71_tmp[8];
		double* fRec71 = &fRec71_tmp[4];
		double fZec14[4];
		double fRec70_tmp[8];
		double* fRec70 = &fRec70_tmp[4];
		double fRec69_tmp[8];
		double* fRec69 = &fRec69_tmp[4];
		double fRec68_tmp[8];
		double* fRec68 = &fRec68_tmp[4];
		double fRec67_tmp[8];
		double* fRec67 = &fRec67_tmp[4];
		double fRec80_tmp[8];
		double* fRec80 = &fRec80_tmp[4];
		double fRec79_tmp[8];
		double* fRec79 = &fRec79_tmp[4];
		double fRec78_tmp[8];
		double* fRec78 = &fRec78_tmp[4];
		double fZec15[4];
		double fRec77_tmp[8];
		double* fRec77 = &fRec77_tmp[4];
		double fRec76_tmp[8];
		double* fRec76 = &fRec76_tmp[4];
		double fRec75_tmp[8];
		double* fRec75 = &fRec75_tmp[4];
		double fRec74_tmp[8];
		double* fRec74 = &fRec74_tmp[4];
		double fRec87_tmp[8];
		double* fRec87 = &fRec87_tmp[4];
		double fRec86_tmp[8];
		double* fRec86 = &fRec86_tmp[4];
		double fRec85_tmp[8];
		double* fRec85 = &fRec85_tmp[4];
		double fZec16[4];
		double fRec84_tmp[8];
		double* fRec84 = &fRec84_tmp[4];
		double fRec83_tmp[8];
		double* fRec83 = &fRec83_tmp[4];
		double fRec82_tmp[8];
		double* fRec82 = &fRec82_tmp[4];
		double fRec81_tmp[8];
		double* fRec81 = &fRec81_tmp[4];
		double fRec94_tmp[8];
		double* fRec94 = &fRec94_tmp[4];
		double fRec93_tmp[8];
		double* fRec93 = &fRec93_tmp[4];
		double fRec92_tmp[8];
		double* fRec92 = &fRec92_tmp[4];
		double fZec17[4];
		double fRec91_tmp[8];
		double* fRec91 = &fRec91_tmp[4];
		double fRec90_tmp[8];
		double* fRec90 = &fRec90_tmp[4];
		double fRec89_tmp[8];
		double* fRec89 = &fRec89_tmp[4];
		double fRec88_tmp[8];
		double* fRec88 = &fRec88_tmp[4];
		double fRec101_tmp[8];
		double* fRec101 = &fRec101_tmp[4];
		double fRec100_tmp[8];
		double* fRec100 = &fRec100_tmp[4];
		double fRec99_tmp[8];
		double* fRec99 = &fRec99_tmp[4];
		double fZec18[4];
		double fRec98_tmp[8];
		double* fRec98 = &fRec98_tmp[4];
		double fRec97_tmp[8];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[8];
		double* fRec96 = &fRec96_tmp[4];
		double fRec95_tmp[8];
		double* fRec95 = &fRec95_tmp[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[8];
		double* fRec104 = &fRec104_tmp[4];
		double fRec103_tmp[8];
		double* fRec103 = &fRec103_tmp[4];
		double fRec102_tmp[8];
		double* fRec102 = &fRec102_tmp[4];
		double fSlow10 = static_cast<double>(fHslider6);
		double fZec19[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec1_tmp[j0] = fRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow0 + 0.999 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec1_perm[j1] = fRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fSlow1 + 0.999 * fRec2[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec5_tmp[j4] = fRec5_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fRec5[faust_wrap_sub(i, 1)] * fSlow3 + fSlow4;
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec5_perm[j5] = fRec5_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst2 * fRec5[i];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = std::sin(fZec0[i]);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::cos(fZec0[i]);
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				iVec0_tmp[j8] = iVec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				iVec0_perm[j9] = iVec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec4_tmp[j10] = fRec4_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fRec4[faust_wrap_sub(i, 1)] * fZec1[i] + fRec3[faust_wrap_sub(i, 1)] * fZec2[i];
				fRec4[i] = static_cast<double>(faust_wrap_sub(1, iVec0[faust_wrap_sub(i, 1)])) + fRec4[faust_wrap_sub(i, 1)] * fZec2[i] - fZec1[i] * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec4_perm[j11] = fRec4_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fSlow5 + 0.999 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec2[i] * fRec3[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(-1.0, std::min<double>(1.0, fRec1[i] + ((iSlow6) ? 0.0 : fZec3[i]) * std::pow(1e+01, 2.0 * fRec6[i])));
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fYec0_tmp[j14] = fYec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = fZec4[i] * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fZec4[i]));
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fYec0_perm[j15] = fYec0_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec0_tmp[j16] = fRec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 0.995 * fRec0[faust_wrap_sub(i, 1)] + fYec0[i] - fYec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec0_perm[j17] = fRec0_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = ((iSlow6) ? fZec3[i] : fRec0[i]);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec10_tmp[j18] = fRec10_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = fZec5[i] - fConst5 * (fConst6 * fRec10[faust_wrap_sub(i, 2)] + fConst9 * fRec10[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec10_perm[j19] = fRec10_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec9_tmp[j20] = fRec9_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fConst5 * (fConst11 * fRec10[i] + fConst12 * fRec10[faust_wrap_sub(i, 1)] + fConst11 * fRec10[faust_wrap_sub(i, 2)]) - fConst13 * (fConst14 * fRec9[faust_wrap_sub(i, 2)] + fConst15 * fRec9[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec9_perm[j21] = fRec9_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec8_tmp[j22] = fRec8_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = fConst13 * (fConst17 * fRec9[i] + fConst18 * fRec9[faust_wrap_sub(i, 1)] + fConst17 * fRec9[faust_wrap_sub(i, 2)]) - fConst19 * (fConst20 * fRec8[faust_wrap_sub(i, 2)] + fConst21 * fRec8[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec8_perm[j23] = fRec8_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec7_tmp[j24] = fRec7_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec7[faust_wrap_sub(i, 1)] * fSlow8 + std::fabs(fConst19 * (fConst24 * fRec8[i] + fConst25 * fRec8[faust_wrap_sub(i, 1)] + fConst24 * fRec8[faust_wrap_sub(i, 2)])) * fSlow9;
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec7_perm[j25] = fRec7_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec17_tmp[j26] = fRec17_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fZec5[i] - fConst26 * (fConst27 * fRec17[faust_wrap_sub(i, 2)] + fConst28 * fRec17[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec17_perm[j27] = fRec17_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec16_tmp[j28] = fRec16_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = fConst26 * (fConst30 * fRec17[i] + fConst31 * fRec17[faust_wrap_sub(i, 1)] + fConst30 * fRec17[faust_wrap_sub(i, 2)]) - fConst32 * (fConst33 * fRec16[faust_wrap_sub(i, 2)] + fConst34 * fRec16[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec16_perm[j29] = fRec16_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec15_tmp[j30] = fRec15_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fConst32 * (fConst35 * fRec16[i] + fConst36 * fRec16[faust_wrap_sub(i, 1)] + fConst35 * fRec16[faust_wrap_sub(i, 2)]) - fConst37 * (fConst38 * fRec15[faust_wrap_sub(i, 2)] + fConst39 * fRec15[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec15_perm[j31] = fRec15_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = fConst37 * (fConst40 * fRec15[i] + fConst41 * fRec15[faust_wrap_sub(i, 1)] + fConst40 * fRec15[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec14_tmp[j32] = fRec14_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fZec6[i] - fConst44 * (fConst45 * fRec14[faust_wrap_sub(i, 2)] + fConst48 * fRec14[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec14_perm[j33] = fRec14_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 23 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec13_tmp[j34] = fRec13_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fConst44 * (fConst50 * fRec14[i] + fConst51 * fRec14[faust_wrap_sub(i, 1)] + fConst50 * fRec14[faust_wrap_sub(i, 2)]) - fConst52 * (fConst53 * fRec13[faust_wrap_sub(i, 2)] + fConst54 * fRec13[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec13_perm[j35] = fRec13_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec12_tmp[j36] = fRec12_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fConst52 * (fConst56 * fRec13[i] + fConst57 * fRec13[faust_wrap_sub(i, 1)] + fConst56 * fRec13[faust_wrap_sub(i, 2)]) - fConst58 * (fConst59 * fRec12[faust_wrap_sub(i, 2)] + fConst60 * fRec12[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec12_perm[j37] = fRec12_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec11_tmp[j38] = fRec11_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow8 * fRec11[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst58 * (fConst62 * fRec12[i] + fConst63 * fRec12[faust_wrap_sub(i, 1)] + fConst62 * fRec12[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec11_perm[j39] = fRec11_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec24_tmp[j40] = fRec24_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec6[i] - fConst64 * (fConst65 * fRec24[faust_wrap_sub(i, 2)] + fConst66 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec24_perm[j41] = fRec24_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec23_tmp[j42] = fRec23_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst64 * (fConst68 * fRec24[i] + fConst69 * fRec24[faust_wrap_sub(i, 1)] + fConst68 * fRec24[faust_wrap_sub(i, 2)]) - fConst70 * (fConst71 * fRec23[faust_wrap_sub(i, 2)] + fConst72 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec23_perm[j43] = fRec23_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec22_tmp[j44] = fRec22_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst70 * (fConst73 * fRec23[i] + fConst74 * fRec23[faust_wrap_sub(i, 1)] + fConst73 * fRec23[faust_wrap_sub(i, 2)]) - fConst75 * (fConst76 * fRec22[faust_wrap_sub(i, 2)] + fConst77 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec22_perm[j45] = fRec22_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fConst75 * (fConst78 * fRec22[i] + fConst79 * fRec22[faust_wrap_sub(i, 1)] + fConst78 * fRec22[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec21_tmp[j46] = fRec21_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fZec7[i] - fConst82 * (fConst83 * fRec21[faust_wrap_sub(i, 2)] + fConst86 * fRec21[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec21_perm[j47] = fRec21_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec20_tmp[j48] = fRec20_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fConst82 * (fConst88 * fRec21[i] + fConst89 * fRec21[faust_wrap_sub(i, 1)] + fConst88 * fRec21[faust_wrap_sub(i, 2)]) - fConst90 * (fConst91 * fRec20[faust_wrap_sub(i, 2)] + fConst92 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec20_perm[j49] = fRec20_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec19_tmp[j50] = fRec19_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst90 * (fConst94 * fRec20[i] + fConst95 * fRec20[faust_wrap_sub(i, 1)] + fConst94 * fRec20[faust_wrap_sub(i, 2)]) - fConst96 * (fConst97 * fRec19[faust_wrap_sub(i, 2)] + fConst98 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec19_perm[j51] = fRec19_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec18_tmp[j52] = fRec18_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fSlow8 * fRec18[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst96 * (fConst100 * fRec19[i] + fConst101 * fRec19[faust_wrap_sub(i, 1)] + fConst100 * fRec19[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec18_perm[j53] = fRec18_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec31_tmp[j54] = fRec31_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec7[i] - fConst102 * (fConst103 * fRec31[faust_wrap_sub(i, 2)] + fConst104 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec31_perm[j55] = fRec31_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 35 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec30_tmp[j56] = fRec30_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst102 * (fConst106 * fRec31[i] + fConst107 * fRec31[faust_wrap_sub(i, 1)] + fConst106 * fRec31[faust_wrap_sub(i, 2)]) - fConst108 * (fConst109 * fRec30[faust_wrap_sub(i, 2)] + fConst110 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec30_perm[j57] = fRec30_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec29_tmp[j58] = fRec29_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst108 * (fConst111 * fRec30[i] + fConst112 * fRec30[faust_wrap_sub(i, 1)] + fConst111 * fRec30[faust_wrap_sub(i, 2)]) - fConst113 * (fConst114 * fRec29[faust_wrap_sub(i, 2)] + fConst115 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec29_perm[j59] = fRec29_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fConst113 * (fConst116 * fRec29[i] + fConst117 * fRec29[faust_wrap_sub(i, 1)] + fConst116 * fRec29[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 38 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec28_tmp[j60] = fRec28_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fZec8[i] - fConst120 * (fConst121 * fRec28[faust_wrap_sub(i, 2)] + fConst124 * fRec28[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec28_perm[j61] = fRec28_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 39 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec27_tmp[j62] = fRec27_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fConst120 * (fConst126 * fRec28[i] + fConst127 * fRec28[faust_wrap_sub(i, 1)] + fConst126 * fRec28[faust_wrap_sub(i, 2)]) - fConst128 * (fConst129 * fRec27[faust_wrap_sub(i, 2)] + fConst130 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec27_perm[j63] = fRec27_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec26_tmp[j64] = fRec26_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst128 * (fConst132 * fRec27[i] + fConst133 * fRec27[faust_wrap_sub(i, 1)] + fConst132 * fRec27[faust_wrap_sub(i, 2)]) - fConst134 * (fConst135 * fRec26[faust_wrap_sub(i, 2)] + fConst136 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec26_perm[j65] = fRec26_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 41 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec25_tmp[j66] = fRec25_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fSlow8 * fRec25[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst134 * (fConst138 * fRec26[i] + fConst139 * fRec26[faust_wrap_sub(i, 1)] + fConst138 * fRec26[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec25_perm[j67] = fRec25_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec38_tmp[j68] = fRec38_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec8[i] - fConst140 * (fConst141 * fRec38[faust_wrap_sub(i, 2)] + fConst142 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec38_perm[j69] = fRec38_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Recursive loop 43 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec37_tmp[j70] = fRec37_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst140 * (fConst144 * fRec38[i] + fConst145 * fRec38[faust_wrap_sub(i, 1)] + fConst144 * fRec38[faust_wrap_sub(i, 2)]) - fConst146 * (fConst147 * fRec37[faust_wrap_sub(i, 2)] + fConst148 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec37_perm[j71] = fRec37_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec36_tmp[j72] = fRec36_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst146 * (fConst149 * fRec37[i] + fConst150 * fRec37[faust_wrap_sub(i, 1)] + fConst149 * fRec37[faust_wrap_sub(i, 2)]) - fConst151 * (fConst152 * fRec36[faust_wrap_sub(i, 2)] + fConst153 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec36_perm[j73] = fRec36_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = fConst151 * (fConst154 * fRec36[i] + fConst155 * fRec36[faust_wrap_sub(i, 1)] + fConst154 * fRec36[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec35_tmp[j74] = fRec35_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fZec9[i] - fConst158 * (fConst159 * fRec35[faust_wrap_sub(i, 2)] + fConst162 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec35_perm[j75] = fRec35_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 47 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec34_tmp[j76] = fRec34_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst158 * (fConst164 * fRec35[i] + fConst165 * fRec35[faust_wrap_sub(i, 1)] + fConst164 * fRec35[faust_wrap_sub(i, 2)]) - fConst166 * (fConst167 * fRec34[faust_wrap_sub(i, 2)] + fConst168 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec34_perm[j77] = fRec34_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec33_tmp[j78] = fRec33_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst166 * (fConst170 * fRec34[i] + fConst171 * fRec34[faust_wrap_sub(i, 1)] + fConst170 * fRec34[faust_wrap_sub(i, 2)]) - fConst172 * (fConst173 * fRec33[faust_wrap_sub(i, 2)] + fConst174 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec33_perm[j79] = fRec33_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec32_tmp[j80] = fRec32_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fSlow8 * fRec32[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst172 * (fConst176 * fRec33[i] + fConst177 * fRec33[faust_wrap_sub(i, 1)] + fConst176 * fRec33[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec32_perm[j81] = fRec32_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec45_tmp[j82] = fRec45_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec9[i] - fConst178 * (fConst179 * fRec45[faust_wrap_sub(i, 2)] + fConst180 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec45_perm[j83] = fRec45_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Recursive loop 51 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec44_tmp[j84] = fRec44_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst178 * (fConst182 * fRec45[i] + fConst183 * fRec45[faust_wrap_sub(i, 1)] + fConst182 * fRec45[faust_wrap_sub(i, 2)]) - fConst184 * (fConst185 * fRec44[faust_wrap_sub(i, 2)] + fConst186 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec44_perm[j85] = fRec44_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec43_tmp[j86] = fRec43_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst184 * (fConst187 * fRec44[i] + fConst188 * fRec44[faust_wrap_sub(i, 1)] + fConst187 * fRec44[faust_wrap_sub(i, 2)]) - fConst189 * (fConst190 * fRec43[faust_wrap_sub(i, 2)] + fConst191 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec43_perm[j87] = fRec43_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fConst189 * (fConst192 * fRec43[i] + fConst193 * fRec43[faust_wrap_sub(i, 1)] + fConst192 * fRec43[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec42_tmp[j88] = fRec42_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fZec10[i] - fConst196 * (fConst197 * fRec42[faust_wrap_sub(i, 2)] + fConst200 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec42_perm[j89] = fRec42_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Recursive loop 55 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec41_tmp[j90] = fRec41_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst196 * (fConst202 * fRec42[i] + fConst203 * fRec42[faust_wrap_sub(i, 1)] + fConst202 * fRec42[faust_wrap_sub(i, 2)]) - fConst204 * (fConst205 * fRec41[faust_wrap_sub(i, 2)] + fConst206 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec41_perm[j91] = fRec41_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec40_tmp[j92] = fRec40_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst204 * (fConst208 * fRec41[i] + fConst209 * fRec41[faust_wrap_sub(i, 1)] + fConst208 * fRec41[faust_wrap_sub(i, 2)]) - fConst210 * (fConst211 * fRec40[faust_wrap_sub(i, 2)] + fConst212 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec40_perm[j93] = fRec40_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 57 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec39_tmp[j94] = fRec39_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fSlow8 * fRec39[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst210 * (fConst214 * fRec40[i] + fConst215 * fRec40[faust_wrap_sub(i, 1)] + fConst214 * fRec40[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec39_perm[j95] = fRec39_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec52_tmp[j96] = fRec52_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec10[i] - fConst216 * (fConst217 * fRec52[faust_wrap_sub(i, 2)] + fConst218 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec52_perm[j97] = fRec52_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Recursive loop 59 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec51_tmp[j98] = fRec51_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst216 * (fConst220 * fRec52[i] + fConst221 * fRec52[faust_wrap_sub(i, 1)] + fConst220 * fRec52[faust_wrap_sub(i, 2)]) - fConst222 * (fConst223 * fRec51[faust_wrap_sub(i, 2)] + fConst224 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec51_perm[j99] = fRec51_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec50_tmp[j100] = fRec50_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst222 * (fConst225 * fRec51[i] + fConst226 * fRec51[faust_wrap_sub(i, 1)] + fConst225 * fRec51[faust_wrap_sub(i, 2)]) - fConst227 * (fConst228 * fRec50[faust_wrap_sub(i, 2)] + fConst229 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec50_perm[j101] = fRec50_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = fConst227 * (fConst230 * fRec50[i] + fConst231 * fRec50[faust_wrap_sub(i, 1)] + fConst230 * fRec50[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec49_tmp[j102] = fRec49_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fZec11[i] - fConst234 * (fConst235 * fRec49[faust_wrap_sub(i, 2)] + fConst238 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec49_perm[j103] = fRec49_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 63 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec48_tmp[j104] = fRec48_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst234 * (fConst240 * fRec49[i] + fConst241 * fRec49[faust_wrap_sub(i, 1)] + fConst240 * fRec49[faust_wrap_sub(i, 2)]) - fConst242 * (fConst243 * fRec48[faust_wrap_sub(i, 2)] + fConst244 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec48_perm[j105] = fRec48_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec47_tmp[j106] = fRec47_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst242 * (fConst246 * fRec48[i] + fConst247 * fRec48[faust_wrap_sub(i, 1)] + fConst246 * fRec48[faust_wrap_sub(i, 2)]) - fConst248 * (fConst249 * fRec47[faust_wrap_sub(i, 2)] + fConst250 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec47_perm[j107] = fRec47_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec46_tmp[j108] = fRec46_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fSlow8 * fRec46[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst248 * (fConst252 * fRec47[i] + fConst253 * fRec47[faust_wrap_sub(i, 1)] + fConst252 * fRec47[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec46_perm[j109] = fRec46_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec59_tmp[j110] = fRec59_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec11[i] - fConst254 * (fConst255 * fRec59[faust_wrap_sub(i, 2)] + fConst256 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec59_perm[j111] = fRec59_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 67 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec58_tmp[j112] = fRec58_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst254 * (fConst258 * fRec59[i] + fConst259 * fRec59[faust_wrap_sub(i, 1)] + fConst258 * fRec59[faust_wrap_sub(i, 2)]) - fConst260 * (fConst261 * fRec58[faust_wrap_sub(i, 2)] + fConst262 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec58_perm[j113] = fRec58_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec57_tmp[j114] = fRec57_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst260 * (fConst263 * fRec58[i] + fConst264 * fRec58[faust_wrap_sub(i, 1)] + fConst263 * fRec58[faust_wrap_sub(i, 2)]) - fConst265 * (fConst266 * fRec57[faust_wrap_sub(i, 2)] + fConst267 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec57_perm[j115] = fRec57_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = fConst265 * (fConst268 * fRec57[i] + fConst269 * fRec57[faust_wrap_sub(i, 1)] + fConst268 * fRec57[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec56_tmp[j116] = fRec56_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fZec12[i] - fConst272 * (fConst273 * fRec56[faust_wrap_sub(i, 2)] + fConst276 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec56_perm[j117] = fRec56_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 71 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec55_tmp[j118] = fRec55_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst272 * (fConst278 * fRec56[i] + fConst279 * fRec56[faust_wrap_sub(i, 1)] + fConst278 * fRec56[faust_wrap_sub(i, 2)]) - fConst280 * (fConst281 * fRec55[faust_wrap_sub(i, 2)] + fConst282 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec55_perm[j119] = fRec55_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec54_tmp[j120] = fRec54_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst280 * (fConst284 * fRec55[i] + fConst285 * fRec55[faust_wrap_sub(i, 1)] + fConst284 * fRec55[faust_wrap_sub(i, 2)]) - fConst286 * (fConst287 * fRec54[faust_wrap_sub(i, 2)] + fConst288 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec54_perm[j121] = fRec54_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec53_tmp[j122] = fRec53_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fSlow8 * fRec53[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst286 * (fConst290 * fRec54[i] + fConst291 * fRec54[faust_wrap_sub(i, 1)] + fConst290 * fRec54[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec53_perm[j123] = fRec53_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec66_tmp[j124] = fRec66_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec12[i] - fConst292 * (fConst293 * fRec66[faust_wrap_sub(i, 2)] + fConst294 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec66_perm[j125] = fRec66_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 75 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec65_tmp[j126] = fRec65_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst292 * (fConst296 * fRec66[i] + fConst297 * fRec66[faust_wrap_sub(i, 1)] + fConst296 * fRec66[faust_wrap_sub(i, 2)]) - fConst298 * (fConst299 * fRec65[faust_wrap_sub(i, 2)] + fConst300 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec65_perm[j127] = fRec65_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec64_tmp[j128] = fRec64_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst298 * (fConst301 * fRec65[i] + fConst302 * fRec65[faust_wrap_sub(i, 1)] + fConst301 * fRec65[faust_wrap_sub(i, 2)]) - fConst303 * (fConst304 * fRec64[faust_wrap_sub(i, 2)] + fConst305 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec64_perm[j129] = fRec64_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = fConst303 * (fConst306 * fRec64[i] + fConst307 * fRec64[faust_wrap_sub(i, 1)] + fConst306 * fRec64[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec63_tmp[j130] = fRec63_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fZec13[i] - fConst310 * (fConst311 * fRec63[faust_wrap_sub(i, 2)] + fConst314 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec63_perm[j131] = fRec63_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 79 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec62_tmp[j132] = fRec62_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst310 * (fConst316 * fRec63[i] + fConst317 * fRec63[faust_wrap_sub(i, 1)] + fConst316 * fRec63[faust_wrap_sub(i, 2)]) - fConst318 * (fConst319 * fRec62[faust_wrap_sub(i, 2)] + fConst320 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec62_perm[j133] = fRec62_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec61_tmp[j134] = fRec61_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst318 * (fConst322 * fRec62[i] + fConst323 * fRec62[faust_wrap_sub(i, 1)] + fConst322 * fRec62[faust_wrap_sub(i, 2)]) - fConst324 * (fConst325 * fRec61[faust_wrap_sub(i, 2)] + fConst326 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec61_perm[j135] = fRec61_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec60_tmp[j136] = fRec60_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fSlow8 * fRec60[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst324 * (fConst328 * fRec61[i] + fConst329 * fRec61[faust_wrap_sub(i, 1)] + fConst328 * fRec61[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec60_perm[j137] = fRec60_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec73_tmp[j138] = fRec73_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec13[i] - fConst330 * (fConst331 * fRec73[faust_wrap_sub(i, 2)] + fConst332 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec73_perm[j139] = fRec73_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 83 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec72_tmp[j140] = fRec72_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst330 * (fConst334 * fRec73[i] + fConst335 * fRec73[faust_wrap_sub(i, 1)] + fConst334 * fRec73[faust_wrap_sub(i, 2)]) - fConst336 * (fConst337 * fRec72[faust_wrap_sub(i, 2)] + fConst338 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec72_perm[j141] = fRec72_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec71_tmp[j142] = fRec71_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst336 * (fConst339 * fRec72[i] + fConst340 * fRec72[faust_wrap_sub(i, 1)] + fConst339 * fRec72[faust_wrap_sub(i, 2)]) - fConst341 * (fConst342 * fRec71[faust_wrap_sub(i, 2)] + fConst343 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec71_perm[j143] = fRec71_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Vectorizable loop 85 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fConst341 * (fConst344 * fRec71[i] + fConst345 * fRec71[faust_wrap_sub(i, 1)] + fConst344 * fRec71[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec70_tmp[j144] = fRec70_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fZec14[i] - fConst348 * (fConst349 * fRec70[faust_wrap_sub(i, 2)] + fConst352 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec70_perm[j145] = fRec70_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 87 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec69_tmp[j146] = fRec69_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst348 * (fConst354 * fRec70[i] + fConst355 * fRec70[faust_wrap_sub(i, 1)] + fConst354 * fRec70[faust_wrap_sub(i, 2)]) - fConst356 * (fConst357 * fRec69[faust_wrap_sub(i, 2)] + fConst358 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec69_perm[j147] = fRec69_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec68_tmp[j148] = fRec68_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst356 * (fConst360 * fRec69[i] + fConst361 * fRec69[faust_wrap_sub(i, 1)] + fConst360 * fRec69[faust_wrap_sub(i, 2)]) - fConst362 * (fConst363 * fRec68[faust_wrap_sub(i, 2)] + fConst364 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec68_perm[j149] = fRec68_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec67_tmp[j150] = fRec67_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fSlow8 * fRec67[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst362 * (fConst366 * fRec68[i] + fConst367 * fRec68[faust_wrap_sub(i, 1)] + fConst366 * fRec68[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec67_perm[j151] = fRec67_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec80_tmp[j152] = fRec80_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec14[i] - fConst368 * (fConst369 * fRec80[faust_wrap_sub(i, 2)] + fConst370 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec80_perm[j153] = fRec80_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 91 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec79_tmp[j154] = fRec79_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst368 * (fConst372 * fRec80[i] + fConst373 * fRec80[faust_wrap_sub(i, 1)] + fConst372 * fRec80[faust_wrap_sub(i, 2)]) - fConst374 * (fConst375 * fRec79[faust_wrap_sub(i, 2)] + fConst376 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec79_perm[j155] = fRec79_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec78_tmp[j156] = fRec78_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst374 * (fConst377 * fRec79[i] + fConst378 * fRec79[faust_wrap_sub(i, 1)] + fConst377 * fRec79[faust_wrap_sub(i, 2)]) - fConst379 * (fConst380 * fRec78[faust_wrap_sub(i, 2)] + fConst381 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec78_perm[j157] = fRec78_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = fConst379 * (fConst382 * fRec78[i] + fConst383 * fRec78[faust_wrap_sub(i, 1)] + fConst382 * fRec78[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec77_tmp[j158] = fRec77_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fZec15[i] - fConst386 * (fConst387 * fRec77[faust_wrap_sub(i, 2)] + fConst390 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec77_perm[j159] = fRec77_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 95 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec76_tmp[j160] = fRec76_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst386 * (fConst392 * fRec77[i] + fConst393 * fRec77[faust_wrap_sub(i, 1)] + fConst392 * fRec77[faust_wrap_sub(i, 2)]) - fConst394 * (fConst395 * fRec76[faust_wrap_sub(i, 2)] + fConst396 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec76_perm[j161] = fRec76_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec75_tmp[j162] = fRec75_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst394 * (fConst398 * fRec76[i] + fConst399 * fRec76[faust_wrap_sub(i, 1)] + fConst398 * fRec76[faust_wrap_sub(i, 2)]) - fConst400 * (fConst401 * fRec75[faust_wrap_sub(i, 2)] + fConst402 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec75_perm[j163] = fRec75_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec74_tmp[j164] = fRec74_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fSlow8 * fRec74[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst400 * (fConst404 * fRec75[i] + fConst405 * fRec75[faust_wrap_sub(i, 1)] + fConst404 * fRec75[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec74_perm[j165] = fRec74_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec87_tmp[j166] = fRec87_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec15[i] - fConst406 * (fConst407 * fRec87[faust_wrap_sub(i, 2)] + fConst408 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec87_perm[j167] = fRec87_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 99 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec86_tmp[j168] = fRec86_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst406 * (fConst410 * fRec87[i] + fConst411 * fRec87[faust_wrap_sub(i, 1)] + fConst410 * fRec87[faust_wrap_sub(i, 2)]) - fConst412 * (fConst413 * fRec86[faust_wrap_sub(i, 2)] + fConst414 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec86_perm[j169] = fRec86_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec85_tmp[j170] = fRec85_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst412 * (fConst415 * fRec86[i] + fConst416 * fRec86[faust_wrap_sub(i, 1)] + fConst415 * fRec86[faust_wrap_sub(i, 2)]) - fConst417 * (fConst418 * fRec85[faust_wrap_sub(i, 2)] + fConst419 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec85_perm[j171] = fRec85_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Vectorizable loop 101 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fConst417 * (fConst420 * fRec85[i] + fConst421 * fRec85[faust_wrap_sub(i, 1)] + fConst420 * fRec85[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec84_tmp[j172] = fRec84_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fZec16[i] - fConst424 * (fConst425 * fRec84[faust_wrap_sub(i, 2)] + fConst428 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec84_perm[j173] = fRec84_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 103 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec83_tmp[j174] = fRec83_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst424 * (fConst430 * fRec84[i] + fConst431 * fRec84[faust_wrap_sub(i, 1)] + fConst430 * fRec84[faust_wrap_sub(i, 2)]) - fConst432 * (fConst433 * fRec83[faust_wrap_sub(i, 2)] + fConst434 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec83_perm[j175] = fRec83_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec82_tmp[j176] = fRec82_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst432 * (fConst436 * fRec83[i] + fConst437 * fRec83[faust_wrap_sub(i, 1)] + fConst436 * fRec83[faust_wrap_sub(i, 2)]) - fConst438 * (fConst439 * fRec82[faust_wrap_sub(i, 2)] + fConst440 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec82_perm[j177] = fRec82_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec81_tmp[j178] = fRec81_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fSlow8 * fRec81[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst438 * (fConst442 * fRec82[i] + fConst443 * fRec82[faust_wrap_sub(i, 1)] + fConst442 * fRec82[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec81_perm[j179] = fRec81_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec94_tmp[j180] = fRec94_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec16[i] - fConst444 * (fConst445 * fRec94[faust_wrap_sub(i, 2)] + fConst446 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec94_perm[j181] = fRec94_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 107 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec93_tmp[j182] = fRec93_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst444 * (fConst448 * fRec94[i] + fConst449 * fRec94[faust_wrap_sub(i, 1)] + fConst448 * fRec94[faust_wrap_sub(i, 2)]) - fConst450 * (fConst451 * fRec93[faust_wrap_sub(i, 2)] + fConst452 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec93_perm[j183] = fRec93_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec92_tmp[j184] = fRec92_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst450 * (fConst453 * fRec93[i] + fConst454 * fRec93[faust_wrap_sub(i, 1)] + fConst453 * fRec93[faust_wrap_sub(i, 2)]) - fConst455 * (fConst456 * fRec92[faust_wrap_sub(i, 2)] + fConst457 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec92_perm[j185] = fRec92_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Vectorizable loop 109 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fConst455 * (fConst458 * fRec92[i] + fConst459 * fRec92[faust_wrap_sub(i, 1)] + fConst458 * fRec92[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec91_tmp[j186] = fRec91_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fZec17[i] - fConst462 * (fConst463 * fRec91[faust_wrap_sub(i, 2)] + fConst466 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec91_perm[j187] = fRec91_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 111 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec90_tmp[j188] = fRec90_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst462 * (fConst468 * fRec91[i] + fConst469 * fRec91[faust_wrap_sub(i, 1)] + fConst468 * fRec91[faust_wrap_sub(i, 2)]) - fConst470 * (fConst471 * fRec90[faust_wrap_sub(i, 2)] + fConst472 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec90_perm[j189] = fRec90_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec89_tmp[j190] = fRec89_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst470 * (fConst474 * fRec90[i] + fConst475 * fRec90[faust_wrap_sub(i, 1)] + fConst474 * fRec90[faust_wrap_sub(i, 2)]) - fConst476 * (fConst477 * fRec89[faust_wrap_sub(i, 2)] + fConst478 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec89_perm[j191] = fRec89_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec88_tmp[j192] = fRec88_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fSlow8 * fRec88[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst476 * (fConst480 * fRec89[i] + fConst481 * fRec89[faust_wrap_sub(i, 1)] + fConst480 * fRec89[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec88_perm[j193] = fRec88_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec101_tmp[j194] = fRec101_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec17[i] - fConst482 * (fConst483 * fRec101[faust_wrap_sub(i, 2)] + fConst484 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec101_perm[j195] = fRec101_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 115 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec100_tmp[j196] = fRec100_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst482 * (fConst486 * fRec101[i] + fConst487 * fRec101[faust_wrap_sub(i, 1)] + fConst486 * fRec101[faust_wrap_sub(i, 2)]) - fConst488 * (fConst489 * fRec100[faust_wrap_sub(i, 2)] + fConst490 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec100_perm[j197] = fRec100_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec99_tmp[j198] = fRec99_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst488 * (fConst491 * fRec100[i] + fConst492 * fRec100[faust_wrap_sub(i, 1)] + fConst491 * fRec100[faust_wrap_sub(i, 2)]) - fConst493 * (fConst494 * fRec99[faust_wrap_sub(i, 2)] + fConst495 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec99_perm[j199] = fRec99_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Vectorizable loop 117 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = fConst493 * (fConst496 * fRec99[i] + fConst497 * fRec99[faust_wrap_sub(i, 1)] + fConst496 * fRec99[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec98_tmp[j200] = fRec98_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fZec18[i] - fConst500 * (fConst501 * fRec98[faust_wrap_sub(i, 2)] + fConst504 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec98_perm[j201] = fRec98_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 119 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec97_tmp[j202] = fRec97_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst500 * (fConst506 * fRec98[i] + fConst507 * fRec98[faust_wrap_sub(i, 1)] + fConst506 * fRec98[faust_wrap_sub(i, 2)]) - fConst508 * (fConst509 * fRec97[faust_wrap_sub(i, 2)] + fConst510 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec97_perm[j203] = fRec97_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec96_tmp[j204] = fRec96_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst508 * (fConst512 * fRec97[i] + fConst513 * fRec97[faust_wrap_sub(i, 1)] + fConst512 * fRec97[faust_wrap_sub(i, 2)]) - fConst514 * (fConst515 * fRec96[faust_wrap_sub(i, 2)] + fConst516 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec96_perm[j205] = fRec96_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec95_tmp[j206] = fRec95_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fSlow8 * fRec95[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst514 * (fConst518 * fRec96[i] + fConst519 * fRec96[faust_wrap_sub(i, 1)] + fConst518 * fRec96[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec95_perm[j207] = fRec95_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec105_tmp[j208] = fRec105_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fZec18[i] - fConst520 * (fConst521 * fRec105[faust_wrap_sub(i, 2)] + fConst522 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec105_perm[j209] = fRec105_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec104_tmp[j210] = fRec104_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst520 * (fConst524 * fRec105[i] + fConst525 * fRec105[faust_wrap_sub(i, 1)] + fConst524 * fRec105[faust_wrap_sub(i, 2)]) - fConst526 * (fConst527 * fRec104[faust_wrap_sub(i, 2)] + fConst528 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec104_perm[j211] = fRec104_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec103_tmp[j212] = fRec103_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst526 * (fConst529 * fRec104[i] + fConst530 * fRec104[faust_wrap_sub(i, 1)] + fConst529 * fRec104[faust_wrap_sub(i, 2)]) - fConst531 * (fConst532 * fRec103[faust_wrap_sub(i, 2)] + fConst533 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec103_perm[j213] = fRec103_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec102_tmp[j214] = fRec102_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fSlow8 * fRec102[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst531 * (fConst534 * fRec103[i] + fConst535 * fRec103[faust_wrap_sub(i, 1)] + fConst534 * fRec103[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec102_perm[j215] = fRec102_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec7[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec11[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec18[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec25[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec32[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec39[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec46[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec53[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec60[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec67[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec74[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec81[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec88[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec95[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec102[i]));
				fZec19[i] = fZec5[i];
			}
			/* Vectorizable loop 127 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec19[i]);
			}
			/* Vectorizable loop 128 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec19[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec1_tmp[j0] = fRec1_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fSlow0 + 0.999 * fRec1[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec1_perm[j1] = fRec1_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fSlow1 + 0.999 * fRec2[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec5_tmp[j4] = fRec5_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fRec5[faust_wrap_sub(i, 1)] * fSlow3 + fSlow4;
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec5_perm[j5] = fRec5_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst2 * fRec5[i];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = std::sin(fZec0[i]);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::cos(fZec0[i]);
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				iVec0_tmp[j8] = iVec0_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				iVec0_perm[j9] = iVec0_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec3_tmp[j6] = fRec3_perm[j6];
			}
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec4_tmp[j10] = fRec4_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fRec4[faust_wrap_sub(i, 1)] * fZec1[i] + fRec3[faust_wrap_sub(i, 1)] * fZec2[i];
				fRec4[i] = static_cast<double>(faust_wrap_sub(1, iVec0[faust_wrap_sub(i, 1)])) + fRec4[faust_wrap_sub(i, 1)] * fZec2[i] - fZec1[i] * fRec3[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec3_perm[j7] = fRec3_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec4_perm[j11] = fRec4_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec6_tmp[j12] = fRec6_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fSlow5 + 0.999 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec6_perm[j13] = fRec6_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec2[i] * fRec3[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(-1.0, std::min<double>(1.0, fRec1[i] + ((iSlow6) ? 0.0 : fZec3[i]) * std::pow(1e+01, 2.0 * fRec6[i])));
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fYec0_tmp[j14] = fYec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = fZec4[i] * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fZec4[i]));
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fYec0_perm[j15] = fYec0_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec0_tmp[j16] = fRec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = 0.995 * fRec0[faust_wrap_sub(i, 1)] + fYec0[i] - fYec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec0_perm[j17] = fRec0_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = ((iSlow6) ? fZec3[i] : fRec0[i]);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec10_tmp[j18] = fRec10_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = fZec5[i] - fConst5 * (fConst6 * fRec10[faust_wrap_sub(i, 2)] + fConst9 * fRec10[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec10_perm[j19] = fRec10_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec9_tmp[j20] = fRec9_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fConst5 * (fConst11 * fRec10[i] + fConst12 * fRec10[faust_wrap_sub(i, 1)] + fConst11 * fRec10[faust_wrap_sub(i, 2)]) - fConst13 * (fConst14 * fRec9[faust_wrap_sub(i, 2)] + fConst15 * fRec9[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec9_perm[j21] = fRec9_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec8_tmp[j22] = fRec8_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = fConst13 * (fConst17 * fRec9[i] + fConst18 * fRec9[faust_wrap_sub(i, 1)] + fConst17 * fRec9[faust_wrap_sub(i, 2)]) - fConst19 * (fConst20 * fRec8[faust_wrap_sub(i, 2)] + fConst21 * fRec8[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec8_perm[j23] = fRec8_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec7_tmp[j24] = fRec7_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec7[faust_wrap_sub(i, 1)] * fSlow8 + std::fabs(fConst19 * (fConst24 * fRec8[i] + fConst25 * fRec8[faust_wrap_sub(i, 1)] + fConst24 * fRec8[faust_wrap_sub(i, 2)])) * fSlow9;
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec7_perm[j25] = fRec7_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec17_tmp[j26] = fRec17_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fZec5[i] - fConst26 * (fConst27 * fRec17[faust_wrap_sub(i, 2)] + fConst28 * fRec17[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec17_perm[j27] = fRec17_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec16_tmp[j28] = fRec16_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = fConst26 * (fConst30 * fRec17[i] + fConst31 * fRec17[faust_wrap_sub(i, 1)] + fConst30 * fRec17[faust_wrap_sub(i, 2)]) - fConst32 * (fConst33 * fRec16[faust_wrap_sub(i, 2)] + fConst34 * fRec16[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec16_perm[j29] = fRec16_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec15_tmp[j30] = fRec15_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fConst32 * (fConst35 * fRec16[i] + fConst36 * fRec16[faust_wrap_sub(i, 1)] + fConst35 * fRec16[faust_wrap_sub(i, 2)]) - fConst37 * (fConst38 * fRec15[faust_wrap_sub(i, 2)] + fConst39 * fRec15[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec15_perm[j31] = fRec15_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = fConst37 * (fConst40 * fRec15[i] + fConst41 * fRec15[faust_wrap_sub(i, 1)] + fConst40 * fRec15[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec14_tmp[j32] = fRec14_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fZec6[i] - fConst44 * (fConst45 * fRec14[faust_wrap_sub(i, 2)] + fConst48 * fRec14[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec14_perm[j33] = fRec14_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 23 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec13_tmp[j34] = fRec13_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fConst44 * (fConst50 * fRec14[i] + fConst51 * fRec14[faust_wrap_sub(i, 1)] + fConst50 * fRec14[faust_wrap_sub(i, 2)]) - fConst52 * (fConst53 * fRec13[faust_wrap_sub(i, 2)] + fConst54 * fRec13[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec13_perm[j35] = fRec13_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec12_tmp[j36] = fRec12_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fConst52 * (fConst56 * fRec13[i] + fConst57 * fRec13[faust_wrap_sub(i, 1)] + fConst56 * fRec13[faust_wrap_sub(i, 2)]) - fConst58 * (fConst59 * fRec12[faust_wrap_sub(i, 2)] + fConst60 * fRec12[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec12_perm[j37] = fRec12_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec11_tmp[j38] = fRec11_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow8 * fRec11[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst58 * (fConst62 * fRec12[i] + fConst63 * fRec12[faust_wrap_sub(i, 1)] + fConst62 * fRec12[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec11_perm[j39] = fRec11_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec24_tmp[j40] = fRec24_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec6[i] - fConst64 * (fConst65 * fRec24[faust_wrap_sub(i, 2)] + fConst66 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec24_perm[j41] = fRec24_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Recursive loop 27 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec23_tmp[j42] = fRec23_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst64 * (fConst68 * fRec24[i] + fConst69 * fRec24[faust_wrap_sub(i, 1)] + fConst68 * fRec24[faust_wrap_sub(i, 2)]) - fConst70 * (fConst71 * fRec23[faust_wrap_sub(i, 2)] + fConst72 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec23_perm[j43] = fRec23_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec22_tmp[j44] = fRec22_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst70 * (fConst73 * fRec23[i] + fConst74 * fRec23[faust_wrap_sub(i, 1)] + fConst73 * fRec23[faust_wrap_sub(i, 2)]) - fConst75 * (fConst76 * fRec22[faust_wrap_sub(i, 2)] + fConst77 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec22_perm[j45] = fRec22_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fConst75 * (fConst78 * fRec22[i] + fConst79 * fRec22[faust_wrap_sub(i, 1)] + fConst78 * fRec22[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec21_tmp[j46] = fRec21_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fZec7[i] - fConst82 * (fConst83 * fRec21[faust_wrap_sub(i, 2)] + fConst86 * fRec21[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec21_perm[j47] = fRec21_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec20_tmp[j48] = fRec20_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fConst82 * (fConst88 * fRec21[i] + fConst89 * fRec21[faust_wrap_sub(i, 1)] + fConst88 * fRec21[faust_wrap_sub(i, 2)]) - fConst90 * (fConst91 * fRec20[faust_wrap_sub(i, 2)] + fConst92 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec20_perm[j49] = fRec20_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec19_tmp[j50] = fRec19_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst90 * (fConst94 * fRec20[i] + fConst95 * fRec20[faust_wrap_sub(i, 1)] + fConst94 * fRec20[faust_wrap_sub(i, 2)]) - fConst96 * (fConst97 * fRec19[faust_wrap_sub(i, 2)] + fConst98 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec19_perm[j51] = fRec19_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec18_tmp[j52] = fRec18_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fSlow8 * fRec18[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst96 * (fConst100 * fRec19[i] + fConst101 * fRec19[faust_wrap_sub(i, 1)] + fConst100 * fRec19[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec18_perm[j53] = fRec18_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec31_tmp[j54] = fRec31_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec7[i] - fConst102 * (fConst103 * fRec31[faust_wrap_sub(i, 2)] + fConst104 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec31_perm[j55] = fRec31_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 35 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec30_tmp[j56] = fRec30_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst102 * (fConst106 * fRec31[i] + fConst107 * fRec31[faust_wrap_sub(i, 1)] + fConst106 * fRec31[faust_wrap_sub(i, 2)]) - fConst108 * (fConst109 * fRec30[faust_wrap_sub(i, 2)] + fConst110 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec30_perm[j57] = fRec30_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec29_tmp[j58] = fRec29_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst108 * (fConst111 * fRec30[i] + fConst112 * fRec30[faust_wrap_sub(i, 1)] + fConst111 * fRec30[faust_wrap_sub(i, 2)]) - fConst113 * (fConst114 * fRec29[faust_wrap_sub(i, 2)] + fConst115 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec29_perm[j59] = fRec29_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fConst113 * (fConst116 * fRec29[i] + fConst117 * fRec29[faust_wrap_sub(i, 1)] + fConst116 * fRec29[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 38 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec28_tmp[j60] = fRec28_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fZec8[i] - fConst120 * (fConst121 * fRec28[faust_wrap_sub(i, 2)] + fConst124 * fRec28[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec28_perm[j61] = fRec28_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 39 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec27_tmp[j62] = fRec27_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fConst120 * (fConst126 * fRec28[i] + fConst127 * fRec28[faust_wrap_sub(i, 1)] + fConst126 * fRec28[faust_wrap_sub(i, 2)]) - fConst128 * (fConst129 * fRec27[faust_wrap_sub(i, 2)] + fConst130 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec27_perm[j63] = fRec27_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec26_tmp[j64] = fRec26_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst128 * (fConst132 * fRec27[i] + fConst133 * fRec27[faust_wrap_sub(i, 1)] + fConst132 * fRec27[faust_wrap_sub(i, 2)]) - fConst134 * (fConst135 * fRec26[faust_wrap_sub(i, 2)] + fConst136 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec26_perm[j65] = fRec26_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 41 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec25_tmp[j66] = fRec25_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fSlow8 * fRec25[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst134 * (fConst138 * fRec26[i] + fConst139 * fRec26[faust_wrap_sub(i, 1)] + fConst138 * fRec26[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec25_perm[j67] = fRec25_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec38_tmp[j68] = fRec38_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec8[i] - fConst140 * (fConst141 * fRec38[faust_wrap_sub(i, 2)] + fConst142 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec38_perm[j69] = fRec38_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Recursive loop 43 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec37_tmp[j70] = fRec37_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst140 * (fConst144 * fRec38[i] + fConst145 * fRec38[faust_wrap_sub(i, 1)] + fConst144 * fRec38[faust_wrap_sub(i, 2)]) - fConst146 * (fConst147 * fRec37[faust_wrap_sub(i, 2)] + fConst148 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec37_perm[j71] = fRec37_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec36_tmp[j72] = fRec36_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst146 * (fConst149 * fRec37[i] + fConst150 * fRec37[faust_wrap_sub(i, 1)] + fConst149 * fRec37[faust_wrap_sub(i, 2)]) - fConst151 * (fConst152 * fRec36[faust_wrap_sub(i, 2)] + fConst153 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec36_perm[j73] = fRec36_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = fConst151 * (fConst154 * fRec36[i] + fConst155 * fRec36[faust_wrap_sub(i, 1)] + fConst154 * fRec36[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec35_tmp[j74] = fRec35_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fZec9[i] - fConst158 * (fConst159 * fRec35[faust_wrap_sub(i, 2)] + fConst162 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec35_perm[j75] = fRec35_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 47 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec34_tmp[j76] = fRec34_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst158 * (fConst164 * fRec35[i] + fConst165 * fRec35[faust_wrap_sub(i, 1)] + fConst164 * fRec35[faust_wrap_sub(i, 2)]) - fConst166 * (fConst167 * fRec34[faust_wrap_sub(i, 2)] + fConst168 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec34_perm[j77] = fRec34_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec33_tmp[j78] = fRec33_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst166 * (fConst170 * fRec34[i] + fConst171 * fRec34[faust_wrap_sub(i, 1)] + fConst170 * fRec34[faust_wrap_sub(i, 2)]) - fConst172 * (fConst173 * fRec33[faust_wrap_sub(i, 2)] + fConst174 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec33_perm[j79] = fRec33_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec32_tmp[j80] = fRec32_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fSlow8 * fRec32[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst172 * (fConst176 * fRec33[i] + fConst177 * fRec33[faust_wrap_sub(i, 1)] + fConst176 * fRec33[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec32_perm[j81] = fRec32_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec45_tmp[j82] = fRec45_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec9[i] - fConst178 * (fConst179 * fRec45[faust_wrap_sub(i, 2)] + fConst180 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec45_perm[j83] = fRec45_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Recursive loop 51 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec44_tmp[j84] = fRec44_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst178 * (fConst182 * fRec45[i] + fConst183 * fRec45[faust_wrap_sub(i, 1)] + fConst182 * fRec45[faust_wrap_sub(i, 2)]) - fConst184 * (fConst185 * fRec44[faust_wrap_sub(i, 2)] + fConst186 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec44_perm[j85] = fRec44_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec43_tmp[j86] = fRec43_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst184 * (fConst187 * fRec44[i] + fConst188 * fRec44[faust_wrap_sub(i, 1)] + fConst187 * fRec44[faust_wrap_sub(i, 2)]) - fConst189 * (fConst190 * fRec43[faust_wrap_sub(i, 2)] + fConst191 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec43_perm[j87] = fRec43_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fConst189 * (fConst192 * fRec43[i] + fConst193 * fRec43[faust_wrap_sub(i, 1)] + fConst192 * fRec43[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec42_tmp[j88] = fRec42_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fZec10[i] - fConst196 * (fConst197 * fRec42[faust_wrap_sub(i, 2)] + fConst200 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec42_perm[j89] = fRec42_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Recursive loop 55 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec41_tmp[j90] = fRec41_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst196 * (fConst202 * fRec42[i] + fConst203 * fRec42[faust_wrap_sub(i, 1)] + fConst202 * fRec42[faust_wrap_sub(i, 2)]) - fConst204 * (fConst205 * fRec41[faust_wrap_sub(i, 2)] + fConst206 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec41_perm[j91] = fRec41_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec40_tmp[j92] = fRec40_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst204 * (fConst208 * fRec41[i] + fConst209 * fRec41[faust_wrap_sub(i, 1)] + fConst208 * fRec41[faust_wrap_sub(i, 2)]) - fConst210 * (fConst211 * fRec40[faust_wrap_sub(i, 2)] + fConst212 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec40_perm[j93] = fRec40_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 57 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec39_tmp[j94] = fRec39_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fSlow8 * fRec39[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst210 * (fConst214 * fRec40[i] + fConst215 * fRec40[faust_wrap_sub(i, 1)] + fConst214 * fRec40[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec39_perm[j95] = fRec39_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec52_tmp[j96] = fRec52_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec10[i] - fConst216 * (fConst217 * fRec52[faust_wrap_sub(i, 2)] + fConst218 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec52_perm[j97] = fRec52_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Recursive loop 59 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec51_tmp[j98] = fRec51_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst216 * (fConst220 * fRec52[i] + fConst221 * fRec52[faust_wrap_sub(i, 1)] + fConst220 * fRec52[faust_wrap_sub(i, 2)]) - fConst222 * (fConst223 * fRec51[faust_wrap_sub(i, 2)] + fConst224 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec51_perm[j99] = fRec51_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec50_tmp[j100] = fRec50_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst222 * (fConst225 * fRec51[i] + fConst226 * fRec51[faust_wrap_sub(i, 1)] + fConst225 * fRec51[faust_wrap_sub(i, 2)]) - fConst227 * (fConst228 * fRec50[faust_wrap_sub(i, 2)] + fConst229 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec50_perm[j101] = fRec50_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = fConst227 * (fConst230 * fRec50[i] + fConst231 * fRec50[faust_wrap_sub(i, 1)] + fConst230 * fRec50[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec49_tmp[j102] = fRec49_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fZec11[i] - fConst234 * (fConst235 * fRec49[faust_wrap_sub(i, 2)] + fConst238 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec49_perm[j103] = fRec49_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 63 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec48_tmp[j104] = fRec48_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst234 * (fConst240 * fRec49[i] + fConst241 * fRec49[faust_wrap_sub(i, 1)] + fConst240 * fRec49[faust_wrap_sub(i, 2)]) - fConst242 * (fConst243 * fRec48[faust_wrap_sub(i, 2)] + fConst244 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec48_perm[j105] = fRec48_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec47_tmp[j106] = fRec47_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst242 * (fConst246 * fRec48[i] + fConst247 * fRec48[faust_wrap_sub(i, 1)] + fConst246 * fRec48[faust_wrap_sub(i, 2)]) - fConst248 * (fConst249 * fRec47[faust_wrap_sub(i, 2)] + fConst250 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec47_perm[j107] = fRec47_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec46_tmp[j108] = fRec46_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fSlow8 * fRec46[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst248 * (fConst252 * fRec47[i] + fConst253 * fRec47[faust_wrap_sub(i, 1)] + fConst252 * fRec47[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec46_perm[j109] = fRec46_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec59_tmp[j110] = fRec59_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec11[i] - fConst254 * (fConst255 * fRec59[faust_wrap_sub(i, 2)] + fConst256 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec59_perm[j111] = fRec59_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 67 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec58_tmp[j112] = fRec58_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst254 * (fConst258 * fRec59[i] + fConst259 * fRec59[faust_wrap_sub(i, 1)] + fConst258 * fRec59[faust_wrap_sub(i, 2)]) - fConst260 * (fConst261 * fRec58[faust_wrap_sub(i, 2)] + fConst262 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec58_perm[j113] = fRec58_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec57_tmp[j114] = fRec57_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst260 * (fConst263 * fRec58[i] + fConst264 * fRec58[faust_wrap_sub(i, 1)] + fConst263 * fRec58[faust_wrap_sub(i, 2)]) - fConst265 * (fConst266 * fRec57[faust_wrap_sub(i, 2)] + fConst267 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec57_perm[j115] = fRec57_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = fConst265 * (fConst268 * fRec57[i] + fConst269 * fRec57[faust_wrap_sub(i, 1)] + fConst268 * fRec57[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec56_tmp[j116] = fRec56_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fZec12[i] - fConst272 * (fConst273 * fRec56[faust_wrap_sub(i, 2)] + fConst276 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec56_perm[j117] = fRec56_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 71 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec55_tmp[j118] = fRec55_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst272 * (fConst278 * fRec56[i] + fConst279 * fRec56[faust_wrap_sub(i, 1)] + fConst278 * fRec56[faust_wrap_sub(i, 2)]) - fConst280 * (fConst281 * fRec55[faust_wrap_sub(i, 2)] + fConst282 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec55_perm[j119] = fRec55_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec54_tmp[j120] = fRec54_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst280 * (fConst284 * fRec55[i] + fConst285 * fRec55[faust_wrap_sub(i, 1)] + fConst284 * fRec55[faust_wrap_sub(i, 2)]) - fConst286 * (fConst287 * fRec54[faust_wrap_sub(i, 2)] + fConst288 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec54_perm[j121] = fRec54_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec53_tmp[j122] = fRec53_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fSlow8 * fRec53[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst286 * (fConst290 * fRec54[i] + fConst291 * fRec54[faust_wrap_sub(i, 1)] + fConst290 * fRec54[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec53_perm[j123] = fRec53_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec66_tmp[j124] = fRec66_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec12[i] - fConst292 * (fConst293 * fRec66[faust_wrap_sub(i, 2)] + fConst294 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec66_perm[j125] = fRec66_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 75 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec65_tmp[j126] = fRec65_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst292 * (fConst296 * fRec66[i] + fConst297 * fRec66[faust_wrap_sub(i, 1)] + fConst296 * fRec66[faust_wrap_sub(i, 2)]) - fConst298 * (fConst299 * fRec65[faust_wrap_sub(i, 2)] + fConst300 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec65_perm[j127] = fRec65_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec64_tmp[j128] = fRec64_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst298 * (fConst301 * fRec65[i] + fConst302 * fRec65[faust_wrap_sub(i, 1)] + fConst301 * fRec65[faust_wrap_sub(i, 2)]) - fConst303 * (fConst304 * fRec64[faust_wrap_sub(i, 2)] + fConst305 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec64_perm[j129] = fRec64_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = fConst303 * (fConst306 * fRec64[i] + fConst307 * fRec64[faust_wrap_sub(i, 1)] + fConst306 * fRec64[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec63_tmp[j130] = fRec63_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fZec13[i] - fConst310 * (fConst311 * fRec63[faust_wrap_sub(i, 2)] + fConst314 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec63_perm[j131] = fRec63_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 79 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec62_tmp[j132] = fRec62_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst310 * (fConst316 * fRec63[i] + fConst317 * fRec63[faust_wrap_sub(i, 1)] + fConst316 * fRec63[faust_wrap_sub(i, 2)]) - fConst318 * (fConst319 * fRec62[faust_wrap_sub(i, 2)] + fConst320 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec62_perm[j133] = fRec62_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec61_tmp[j134] = fRec61_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst318 * (fConst322 * fRec62[i] + fConst323 * fRec62[faust_wrap_sub(i, 1)] + fConst322 * fRec62[faust_wrap_sub(i, 2)]) - fConst324 * (fConst325 * fRec61[faust_wrap_sub(i, 2)] + fConst326 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec61_perm[j135] = fRec61_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec60_tmp[j136] = fRec60_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fSlow8 * fRec60[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst324 * (fConst328 * fRec61[i] + fConst329 * fRec61[faust_wrap_sub(i, 1)] + fConst328 * fRec61[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec60_perm[j137] = fRec60_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec73_tmp[j138] = fRec73_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec13[i] - fConst330 * (fConst331 * fRec73[faust_wrap_sub(i, 2)] + fConst332 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec73_perm[j139] = fRec73_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 83 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec72_tmp[j140] = fRec72_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst330 * (fConst334 * fRec73[i] + fConst335 * fRec73[faust_wrap_sub(i, 1)] + fConst334 * fRec73[faust_wrap_sub(i, 2)]) - fConst336 * (fConst337 * fRec72[faust_wrap_sub(i, 2)] + fConst338 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec72_perm[j141] = fRec72_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec71_tmp[j142] = fRec71_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst336 * (fConst339 * fRec72[i] + fConst340 * fRec72[faust_wrap_sub(i, 1)] + fConst339 * fRec72[faust_wrap_sub(i, 2)]) - fConst341 * (fConst342 * fRec71[faust_wrap_sub(i, 2)] + fConst343 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec71_perm[j143] = fRec71_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Vectorizable loop 85 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fConst341 * (fConst344 * fRec71[i] + fConst345 * fRec71[faust_wrap_sub(i, 1)] + fConst344 * fRec71[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec70_tmp[j144] = fRec70_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fZec14[i] - fConst348 * (fConst349 * fRec70[faust_wrap_sub(i, 2)] + fConst352 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec70_perm[j145] = fRec70_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 87 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec69_tmp[j146] = fRec69_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst348 * (fConst354 * fRec70[i] + fConst355 * fRec70[faust_wrap_sub(i, 1)] + fConst354 * fRec70[faust_wrap_sub(i, 2)]) - fConst356 * (fConst357 * fRec69[faust_wrap_sub(i, 2)] + fConst358 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec69_perm[j147] = fRec69_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec68_tmp[j148] = fRec68_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst356 * (fConst360 * fRec69[i] + fConst361 * fRec69[faust_wrap_sub(i, 1)] + fConst360 * fRec69[faust_wrap_sub(i, 2)]) - fConst362 * (fConst363 * fRec68[faust_wrap_sub(i, 2)] + fConst364 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec68_perm[j149] = fRec68_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec67_tmp[j150] = fRec67_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fSlow8 * fRec67[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst362 * (fConst366 * fRec68[i] + fConst367 * fRec68[faust_wrap_sub(i, 1)] + fConst366 * fRec68[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec67_perm[j151] = fRec67_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec80_tmp[j152] = fRec80_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec14[i] - fConst368 * (fConst369 * fRec80[faust_wrap_sub(i, 2)] + fConst370 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec80_perm[j153] = fRec80_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 91 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec79_tmp[j154] = fRec79_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst368 * (fConst372 * fRec80[i] + fConst373 * fRec80[faust_wrap_sub(i, 1)] + fConst372 * fRec80[faust_wrap_sub(i, 2)]) - fConst374 * (fConst375 * fRec79[faust_wrap_sub(i, 2)] + fConst376 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec79_perm[j155] = fRec79_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec78_tmp[j156] = fRec78_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst374 * (fConst377 * fRec79[i] + fConst378 * fRec79[faust_wrap_sub(i, 1)] + fConst377 * fRec79[faust_wrap_sub(i, 2)]) - fConst379 * (fConst380 * fRec78[faust_wrap_sub(i, 2)] + fConst381 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec78_perm[j157] = fRec78_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = fConst379 * (fConst382 * fRec78[i] + fConst383 * fRec78[faust_wrap_sub(i, 1)] + fConst382 * fRec78[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec77_tmp[j158] = fRec77_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fZec15[i] - fConst386 * (fConst387 * fRec77[faust_wrap_sub(i, 2)] + fConst390 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec77_perm[j159] = fRec77_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 95 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec76_tmp[j160] = fRec76_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst386 * (fConst392 * fRec77[i] + fConst393 * fRec77[faust_wrap_sub(i, 1)] + fConst392 * fRec77[faust_wrap_sub(i, 2)]) - fConst394 * (fConst395 * fRec76[faust_wrap_sub(i, 2)] + fConst396 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec76_perm[j161] = fRec76_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec75_tmp[j162] = fRec75_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst394 * (fConst398 * fRec76[i] + fConst399 * fRec76[faust_wrap_sub(i, 1)] + fConst398 * fRec76[faust_wrap_sub(i, 2)]) - fConst400 * (fConst401 * fRec75[faust_wrap_sub(i, 2)] + fConst402 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec75_perm[j163] = fRec75_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec74_tmp[j164] = fRec74_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fSlow8 * fRec74[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst400 * (fConst404 * fRec75[i] + fConst405 * fRec75[faust_wrap_sub(i, 1)] + fConst404 * fRec75[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec74_perm[j165] = fRec74_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec87_tmp[j166] = fRec87_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec15[i] - fConst406 * (fConst407 * fRec87[faust_wrap_sub(i, 2)] + fConst408 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec87_perm[j167] = fRec87_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 99 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec86_tmp[j168] = fRec86_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst406 * (fConst410 * fRec87[i] + fConst411 * fRec87[faust_wrap_sub(i, 1)] + fConst410 * fRec87[faust_wrap_sub(i, 2)]) - fConst412 * (fConst413 * fRec86[faust_wrap_sub(i, 2)] + fConst414 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec86_perm[j169] = fRec86_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec85_tmp[j170] = fRec85_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst412 * (fConst415 * fRec86[i] + fConst416 * fRec86[faust_wrap_sub(i, 1)] + fConst415 * fRec86[faust_wrap_sub(i, 2)]) - fConst417 * (fConst418 * fRec85[faust_wrap_sub(i, 2)] + fConst419 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec85_perm[j171] = fRec85_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Vectorizable loop 101 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fConst417 * (fConst420 * fRec85[i] + fConst421 * fRec85[faust_wrap_sub(i, 1)] + fConst420 * fRec85[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec84_tmp[j172] = fRec84_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fZec16[i] - fConst424 * (fConst425 * fRec84[faust_wrap_sub(i, 2)] + fConst428 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec84_perm[j173] = fRec84_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 103 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec83_tmp[j174] = fRec83_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst424 * (fConst430 * fRec84[i] + fConst431 * fRec84[faust_wrap_sub(i, 1)] + fConst430 * fRec84[faust_wrap_sub(i, 2)]) - fConst432 * (fConst433 * fRec83[faust_wrap_sub(i, 2)] + fConst434 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec83_perm[j175] = fRec83_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec82_tmp[j176] = fRec82_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst432 * (fConst436 * fRec83[i] + fConst437 * fRec83[faust_wrap_sub(i, 1)] + fConst436 * fRec83[faust_wrap_sub(i, 2)]) - fConst438 * (fConst439 * fRec82[faust_wrap_sub(i, 2)] + fConst440 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec82_perm[j177] = fRec82_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec81_tmp[j178] = fRec81_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fSlow8 * fRec81[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst438 * (fConst442 * fRec82[i] + fConst443 * fRec82[faust_wrap_sub(i, 1)] + fConst442 * fRec82[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec81_perm[j179] = fRec81_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec94_tmp[j180] = fRec94_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec16[i] - fConst444 * (fConst445 * fRec94[faust_wrap_sub(i, 2)] + fConst446 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec94_perm[j181] = fRec94_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 107 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec93_tmp[j182] = fRec93_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst444 * (fConst448 * fRec94[i] + fConst449 * fRec94[faust_wrap_sub(i, 1)] + fConst448 * fRec94[faust_wrap_sub(i, 2)]) - fConst450 * (fConst451 * fRec93[faust_wrap_sub(i, 2)] + fConst452 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec93_perm[j183] = fRec93_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec92_tmp[j184] = fRec92_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst450 * (fConst453 * fRec93[i] + fConst454 * fRec93[faust_wrap_sub(i, 1)] + fConst453 * fRec93[faust_wrap_sub(i, 2)]) - fConst455 * (fConst456 * fRec92[faust_wrap_sub(i, 2)] + fConst457 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec92_perm[j185] = fRec92_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Vectorizable loop 109 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fConst455 * (fConst458 * fRec92[i] + fConst459 * fRec92[faust_wrap_sub(i, 1)] + fConst458 * fRec92[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec91_tmp[j186] = fRec91_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fZec17[i] - fConst462 * (fConst463 * fRec91[faust_wrap_sub(i, 2)] + fConst466 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec91_perm[j187] = fRec91_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 111 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec90_tmp[j188] = fRec90_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst462 * (fConst468 * fRec91[i] + fConst469 * fRec91[faust_wrap_sub(i, 1)] + fConst468 * fRec91[faust_wrap_sub(i, 2)]) - fConst470 * (fConst471 * fRec90[faust_wrap_sub(i, 2)] + fConst472 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec90_perm[j189] = fRec90_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec89_tmp[j190] = fRec89_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst470 * (fConst474 * fRec90[i] + fConst475 * fRec90[faust_wrap_sub(i, 1)] + fConst474 * fRec90[faust_wrap_sub(i, 2)]) - fConst476 * (fConst477 * fRec89[faust_wrap_sub(i, 2)] + fConst478 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec89_perm[j191] = fRec89_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec88_tmp[j192] = fRec88_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fSlow8 * fRec88[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst476 * (fConst480 * fRec89[i] + fConst481 * fRec89[faust_wrap_sub(i, 1)] + fConst480 * fRec89[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec88_perm[j193] = fRec88_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec101_tmp[j194] = fRec101_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec17[i] - fConst482 * (fConst483 * fRec101[faust_wrap_sub(i, 2)] + fConst484 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec101_perm[j195] = fRec101_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 115 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec100_tmp[j196] = fRec100_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst482 * (fConst486 * fRec101[i] + fConst487 * fRec101[faust_wrap_sub(i, 1)] + fConst486 * fRec101[faust_wrap_sub(i, 2)]) - fConst488 * (fConst489 * fRec100[faust_wrap_sub(i, 2)] + fConst490 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec100_perm[j197] = fRec100_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec99_tmp[j198] = fRec99_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst488 * (fConst491 * fRec100[i] + fConst492 * fRec100[faust_wrap_sub(i, 1)] + fConst491 * fRec100[faust_wrap_sub(i, 2)]) - fConst493 * (fConst494 * fRec99[faust_wrap_sub(i, 2)] + fConst495 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec99_perm[j199] = fRec99_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Vectorizable loop 117 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = fConst493 * (fConst496 * fRec99[i] + fConst497 * fRec99[faust_wrap_sub(i, 1)] + fConst496 * fRec99[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec98_tmp[j200] = fRec98_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fZec18[i] - fConst500 * (fConst501 * fRec98[faust_wrap_sub(i, 2)] + fConst504 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec98_perm[j201] = fRec98_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 119 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec97_tmp[j202] = fRec97_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst500 * (fConst506 * fRec98[i] + fConst507 * fRec98[faust_wrap_sub(i, 1)] + fConst506 * fRec98[faust_wrap_sub(i, 2)]) - fConst508 * (fConst509 * fRec97[faust_wrap_sub(i, 2)] + fConst510 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec97_perm[j203] = fRec97_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec96_tmp[j204] = fRec96_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst508 * (fConst512 * fRec97[i] + fConst513 * fRec97[faust_wrap_sub(i, 1)] + fConst512 * fRec97[faust_wrap_sub(i, 2)]) - fConst514 * (fConst515 * fRec96[faust_wrap_sub(i, 2)] + fConst516 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec96_perm[j205] = fRec96_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec95_tmp[j206] = fRec95_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fSlow8 * fRec95[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst514 * (fConst518 * fRec96[i] + fConst519 * fRec96[faust_wrap_sub(i, 1)] + fConst518 * fRec96[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec95_perm[j207] = fRec95_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec105_tmp[j208] = fRec105_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fZec18[i] - fConst520 * (fConst521 * fRec105[faust_wrap_sub(i, 2)] + fConst522 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec105_perm[j209] = fRec105_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec104_tmp[j210] = fRec104_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst520 * (fConst524 * fRec105[i] + fConst525 * fRec105[faust_wrap_sub(i, 1)] + fConst524 * fRec105[faust_wrap_sub(i, 2)]) - fConst526 * (fConst527 * fRec104[faust_wrap_sub(i, 2)] + fConst528 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec104_perm[j211] = fRec104_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec103_tmp[j212] = fRec103_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst526 * (fConst529 * fRec104[i] + fConst530 * fRec104[faust_wrap_sub(i, 1)] + fConst529 * fRec104[faust_wrap_sub(i, 2)]) - fConst531 * (fConst532 * fRec103[faust_wrap_sub(i, 2)] + fConst533 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec103_perm[j213] = fRec103_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec102_tmp[j214] = fRec102_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fSlow8 * fRec102[faust_wrap_sub(i, 1)] + fSlow9 * std::fabs(fConst531 * (fConst534 * fRec103[i] + fConst535 * fRec103[faust_wrap_sub(i, 1)] + fConst534 * fRec103[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec102_perm[j215] = fRec102_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec7[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec11[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec18[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec25[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec32[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec39[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec46[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec53[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec60[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec67[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec74[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec81[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec88[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec95[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow10 + 2e+01 * std::log10(fRec102[i]));
				fZec19[i] = fZec5[i];
			}
			/* Vectorizable loop 127 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec19[i]);
			}
			/* Vectorizable loop 128 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec19[i]);
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
