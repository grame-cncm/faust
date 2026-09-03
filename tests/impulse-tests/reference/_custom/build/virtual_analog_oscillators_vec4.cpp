/* ------------------------------------------------------------
name: "virtual_analog_oscillators"
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

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	double fRec0_perm[4];
	FAUSTFLOAT fHslider1;
	double fRec6_perm[4];
	FAUSTFLOAT fHslider2;
	double fRec7_perm[4];
	FAUSTFLOAT fVslider0;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider3;
	double fRec9_perm[4];
	double fRec8_perm[4];
	FAUSTFLOAT fVslider1;
	double fRec10_perm[4];
	FAUSTFLOAT fVslider2;
	double fRec11_perm[4];
	double fRec12_perm[4];
	double fRec13_perm[4];
	double fRec14_perm[4];
	double fConst2;
	int iVec0_perm[4];
	double fYec0_perm[4];
	double fYec1[4096];
	int fYec1_idx;
	int fYec1_idx_save;
	double fConst3;
	double fRec15_perm[4];
	double fYec2_perm[4];
	double fYec3[4096];
	int fYec3_idx;
	int fYec3_idx_save;
	double fRec16_perm[4];
	double fYec4_perm[4];
	double fYec5[4096];
	int fYec5_idx;
	int fYec5_idx_save;
	double fRec17_perm[4];
	FAUSTFLOAT fVslider3;
	double fRec18_perm[4];
	int iRec20_perm[4];
	double fRec19_perm[4];
	double fConst4;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fEntry0;
	double fYec6_perm[4];
	double fConst5;
	double fYec7_perm[4];
	double fYec8_perm[4];
	double fConst6;
	double fYec9_perm[4];
	double fYec10_perm[4];
	double fYec11_perm[4];
	double fYec12_perm[4];
	double fYec13_perm[4];
	double fYec14_perm[4];
	double fYec15_perm[4];
	double fYec16_perm[4];
	double fYec17_perm[4];
	double fYec18_perm[4];
	double fYec19_perm[4];
	double fYec20_perm[4];
	double fYec21_perm[4];
	double fYec22_perm[4];
	double fYec23_perm[4];
	double fConst7;
	FAUSTFLOAT fVslider6;
	double fConst8;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	double fConst9;
	FAUSTFLOAT fCheckbox1;
	double fYec24_perm[4];
	double fYec25_perm[4];
	double fYec26[4096];
	int fYec26_idx;
	int fYec26_idx_save;
	double fYec27_perm[4];
	double fYec28_perm[4];
	double fYec29[4096];
	int fYec29_idx;
	int fYec29_idx_save;
	double fYec30_perm[4];
	double fYec31_perm[4];
	double fYec32[4096];
	int fYec32_idx;
	int fYec32_idx_save;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fHslider4;
	double fRec5_perm[4];
	double fRec4_perm[4];
	double fRec3_perm[4];
	double fRec2_perm[4];
	double fRec1_perm[4];
	double fConst10;
	double fRec22_perm[4];
	double fRec21_perm[4];
	double fRec25_perm[4];
	double fRec23_perm[4];
	double fRec28_perm[4];
	double fRec26_perm[4];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fRec32_perm[4];
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fRec31_perm[4];
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fRec30_perm[4];
	FAUSTFLOAT fHslider5;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fRec29_perm[4];
	double fConst34;
	double fConst35;
	double fConst36;
	double fRec39_perm[4];
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec38_perm[4];
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fRec37_perm[4];
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec36_perm[4];
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec35_perm[4];
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fRec34_perm[4];
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec33_perm[4];
	double fConst72;
	double fConst73;
	double fConst74;
	double fRec46_perm[4];
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fRec45_perm[4];
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fRec44_perm[4];
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fRec43_perm[4];
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fRec42_perm[4];
	double fConst101;
	double fConst102;
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fRec41_perm[4];
	double fConst107;
	double fConst108;
	double fConst109;
	double fRec40_perm[4];
	double fConst110;
	double fConst111;
	double fConst112;
	double fRec53_perm[4];
	double fConst113;
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fRec52_perm[4];
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fRec51_perm[4];
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fRec50_perm[4];
	double fConst133;
	double fConst134;
	double fConst135;
	double fConst136;
	double fConst137;
	double fConst138;
	double fRec49_perm[4];
	double fConst139;
	double fConst140;
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fRec48_perm[4];
	double fConst145;
	double fConst146;
	double fConst147;
	double fRec47_perm[4];
	double fConst148;
	double fConst149;
	double fConst150;
	double fRec60_perm[4];
	double fConst151;
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fRec59_perm[4];
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fRec58_perm[4];
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fRec57_perm[4];
	double fConst171;
	double fConst172;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fRec56_perm[4];
	double fConst177;
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fRec55_perm[4];
	double fConst183;
	double fConst184;
	double fConst185;
	double fRec54_perm[4];
	double fConst186;
	double fConst187;
	double fConst188;
	double fRec67_perm[4];
	double fConst189;
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fRec66_perm[4];
	double fConst195;
	double fConst196;
	double fConst197;
	double fConst198;
	double fConst199;
	double fRec65_perm[4];
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fRec64_perm[4];
	double fConst209;
	double fConst210;
	double fConst211;
	double fConst212;
	double fConst213;
	double fConst214;
	double fRec63_perm[4];
	double fConst215;
	double fConst216;
	double fConst217;
	double fConst218;
	double fConst219;
	double fConst220;
	double fRec62_perm[4];
	double fConst221;
	double fConst222;
	double fConst223;
	double fRec61_perm[4];
	double fConst224;
	double fConst225;
	double fConst226;
	double fRec74_perm[4];
	double fConst227;
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fRec73_perm[4];
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst237;
	double fRec72_perm[4];
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fConst243;
	double fConst244;
	double fConst245;
	double fConst246;
	double fRec71_perm[4];
	double fConst247;
	double fConst248;
	double fConst249;
	double fConst250;
	double fConst251;
	double fConst252;
	double fRec70_perm[4];
	double fConst253;
	double fConst254;
	double fConst255;
	double fConst256;
	double fConst257;
	double fConst258;
	double fRec69_perm[4];
	double fConst259;
	double fConst260;
	double fConst261;
	double fRec68_perm[4];
	double fConst262;
	double fConst263;
	double fConst264;
	double fRec81_perm[4];
	double fConst265;
	double fConst266;
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fRec80_perm[4];
	double fConst271;
	double fConst272;
	double fConst273;
	double fConst274;
	double fConst275;
	double fRec79_perm[4];
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fConst281;
	double fConst282;
	double fConst283;
	double fConst284;
	double fRec78_perm[4];
	double fConst285;
	double fConst286;
	double fConst287;
	double fConst288;
	double fConst289;
	double fConst290;
	double fRec77_perm[4];
	double fConst291;
	double fConst292;
	double fConst293;
	double fConst294;
	double fConst295;
	double fConst296;
	double fRec76_perm[4];
	double fConst297;
	double fConst298;
	double fConst299;
	double fRec75_perm[4];
	double fConst300;
	double fConst301;
	double fConst302;
	double fRec88_perm[4];
	double fConst303;
	double fConst304;
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst308;
	double fRec87_perm[4];
	double fConst309;
	double fConst310;
	double fConst311;
	double fConst312;
	double fConst313;
	double fRec86_perm[4];
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fRec85_perm[4];
	double fConst323;
	double fConst324;
	double fConst325;
	double fConst326;
	double fConst327;
	double fConst328;
	double fRec84_perm[4];
	double fConst329;
	double fConst330;
	double fConst331;
	double fConst332;
	double fConst333;
	double fConst334;
	double fRec83_perm[4];
	double fConst335;
	double fConst336;
	double fConst337;
	double fRec82_perm[4];
	double fConst338;
	double fConst339;
	double fConst340;
	double fRec95_perm[4];
	double fConst341;
	double fConst342;
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fRec94_perm[4];
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fConst351;
	double fRec93_perm[4];
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fConst357;
	double fConst358;
	double fConst359;
	double fConst360;
	double fRec92_perm[4];
	double fConst361;
	double fConst362;
	double fConst363;
	double fConst364;
	double fConst365;
	double fConst366;
	double fRec91_perm[4];
	double fConst367;
	double fConst368;
	double fConst369;
	double fConst370;
	double fConst371;
	double fConst372;
	double fRec90_perm[4];
	double fConst373;
	double fConst374;
	double fConst375;
	double fRec89_perm[4];
	double fConst376;
	double fConst377;
	double fConst378;
	double fRec102_perm[4];
	double fConst379;
	double fConst380;
	double fConst381;
	double fConst382;
	double fConst383;
	double fConst384;
	double fRec101_perm[4];
	double fConst385;
	double fConst386;
	double fConst387;
	double fConst388;
	double fConst389;
	double fRec100_perm[4];
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fConst395;
	double fConst396;
	double fConst397;
	double fConst398;
	double fRec99_perm[4];
	double fConst399;
	double fConst400;
	double fConst401;
	double fConst402;
	double fConst403;
	double fConst404;
	double fRec98_perm[4];
	double fConst405;
	double fConst406;
	double fConst407;
	double fConst408;
	double fConst409;
	double fConst410;
	double fRec97_perm[4];
	double fConst411;
	double fConst412;
	double fConst413;
	double fRec96_perm[4];
	double fConst414;
	double fConst415;
	double fConst416;
	double fRec109_perm[4];
	double fConst417;
	double fConst418;
	double fConst419;
	double fConst420;
	double fConst421;
	double fConst422;
	double fRec108_perm[4];
	double fConst423;
	double fConst424;
	double fConst425;
	double fConst426;
	double fConst427;
	double fRec107_perm[4];
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fConst433;
	double fConst434;
	double fConst435;
	double fConst436;
	double fRec106_perm[4];
	double fConst437;
	double fConst438;
	double fConst439;
	double fConst440;
	double fConst441;
	double fConst442;
	double fRec105_perm[4];
	double fConst443;
	double fConst444;
	double fConst445;
	double fConst446;
	double fConst447;
	double fConst448;
	double fRec104_perm[4];
	double fConst449;
	double fConst450;
	double fConst451;
	double fRec103_perm[4];
	double fConst452;
	double fConst453;
	double fConst454;
	double fRec116_perm[4];
	double fConst455;
	double fConst456;
	double fConst457;
	double fConst458;
	double fConst459;
	double fConst460;
	double fRec115_perm[4];
	double fConst461;
	double fConst462;
	double fConst463;
	double fConst464;
	double fConst465;
	double fRec114_perm[4];
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fConst470;
	double fConst471;
	double fConst472;
	double fConst473;
	double fConst474;
	double fRec113_perm[4];
	double fConst475;
	double fConst476;
	double fConst477;
	double fConst478;
	double fConst479;
	double fConst480;
	double fRec112_perm[4];
	double fConst481;
	double fConst482;
	double fConst483;
	double fConst484;
	double fConst485;
	double fConst486;
	double fRec111_perm[4];
	double fConst487;
	double fConst488;
	double fConst489;
	double fRec110_perm[4];
	double fConst490;
	double fConst491;
	double fConst492;
	double fRec123_perm[4];
	double fConst493;
	double fConst494;
	double fConst495;
	double fConst496;
	double fConst497;
	double fConst498;
	double fRec122_perm[4];
	double fConst499;
	double fConst500;
	double fConst501;
	double fConst502;
	double fConst503;
	double fRec121_perm[4];
	double fConst504;
	double fConst505;
	double fConst506;
	double fConst507;
	double fConst508;
	double fConst509;
	double fConst510;
	double fConst511;
	double fConst512;
	double fRec120_perm[4];
	double fConst513;
	double fConst514;
	double fConst515;
	double fConst516;
	double fConst517;
	double fConst518;
	double fRec119_perm[4];
	double fConst519;
	double fConst520;
	double fConst521;
	double fConst522;
	double fConst523;
	double fConst524;
	double fRec118_perm[4];
	double fConst525;
	double fConst526;
	double fConst527;
	double fRec117_perm[4];
	double fConst528;
	double fConst529;
	double fConst530;
	double fRec127_perm[4];
	double fConst531;
	double fConst532;
	double fConst533;
	double fConst534;
	double fConst535;
	double fConst536;
	double fRec126_perm[4];
	double fConst537;
	double fConst538;
	double fConst539;
	double fConst540;
	double fConst541;
	double fRec125_perm[4];
	double fConst542;
	double fConst543;
	double fRec124_perm[4];
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
		m->declare("effect.lib/moog_vcf:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/moog_vcf:copyright", "Julius O. Smith III");
		m->declare("effect.lib/moog_vcf:license", "STK-4.3");
		m->declare("effect.lib/moog_vcf_2b:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/moog_vcf_2b:copyright", "Julius O. Smith III");
		m->declare("effect.lib/moog_vcf_2b:license", "STK-4.3");
		m->declare("effect.lib/moog_vcf_2bn:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/moog_vcf_2bn:copyright", "Julius O. Smith III");
		m->declare("effect.lib/moog_vcf_2bn:license", "STK-4.3");
		m->declare("effect.lib/moog_vcf_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/moog_vcf_demo:copyright", "Julius O. Smith III");
		m->declare("effect.lib/moog_vcf_demo:license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/pianokey2hz:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/pianokey2hz:copyright", "Julius O. Smith III");
		m->declare("effect.lib/pianokey2hz:license", "STK-4.3");
		m->declare("filename", "virtual_analog_oscillators.dsp");
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
		m->declare("name", "virtual_analog_oscillators");
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
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 1.0 / fConst0;
		fConst2 = 0.25 * fConst0;
		fConst3 = 0.5 * fConst0;
		fConst4 = 6.283185307179586 / fConst0;
		fConst5 = 0.041666666666666664 * mydsp_faustpower2_f(fConst0);
		fConst6 = 0.005208333333333333 * mydsp_faustpower3_f(fConst0);
		fConst7 = 0.08333333333333333 * fConst0;
		fConst8 = 1.3333333333333333 / fConst0;
		fConst9 = 0.013888888888888888 * fConst0;
		fConst10 = 3.141592653589793 / fConst0;
		fConst11 = std::tan(50265.48245743669 / fConst0);
		fConst12 = 1.0 / fConst11;
		fConst13 = 1.0 / ((fConst12 + 3.1897274020965583) / fConst11 + 4.076781969643807);
		fConst14 = (fConst12 + -3.1897274020965583) / fConst11 + 4.076781969643807;
		fConst15 = mydsp_faustpower2_f(fConst11);
		fConst16 = 1.0 / fConst15;
		fConst17 = 2.0 * (4.076781969643807 - fConst16);
		fConst18 = 0.0017661728399818856 / fConst15;
		fConst19 = fConst18 + 0.00040767818495825777;
		fConst20 = 2.0 * (0.00040767818495825777 - fConst18);
		fConst21 = 1.0 / ((fConst12 + 0.7431304601070396) / fConst11 + 1.450071084655647);
		fConst22 = (fConst12 + -0.7431304601070396) / fConst11 + 1.450071084655647;
		fConst23 = 2.0 * (1.450071084655647 - fConst16);
		fConst24 = 11.052052171507189 / fConst15;
		fConst25 = fConst24 + 1.450071084655647;
		fConst26 = 2.0 * (1.450071084655647 - fConst24);
		fConst27 = 1.0 / ((fConst12 + 0.157482159302087) / fConst11 + 0.9351401670315425);
		fConst28 = (fConst12 + -0.157482159302087) / fConst11 + 0.9351401670315425;
		fConst29 = 2.0 * (0.9351401670315425 - fConst16);
		fConst30 = 1e+03 / fConst0;
		fConst31 = 50.063807016150385 / fConst15;
		fConst32 = fConst31 + 0.9351401670315425;
		fConst33 = 2.0 * (0.9351401670315425 - fConst31);
		fConst34 = 1.0 / ((fConst12 + 0.782413046821645) / fConst11 + 0.24529150870616);
		fConst35 = (fConst12 + -0.782413046821645) / fConst11 + 0.24529150870616;
		fConst36 = 2.0 * (0.24529150870616 - fConst16);
		fConst37 = 9.9999997055e-05 / fConst15;
		fConst38 = fConst37 + 0.000433227200555;
		fConst39 = 2.0 * (0.000433227200555 - fConst37);
		fConst40 = 1.0 / ((fConst12 + 0.512478641889141) / fConst11 + 0.689621364484675);
		fConst41 = (fConst12 + -0.512478641889141) / fConst11 + 0.689621364484675;
		fConst42 = 2.0 * (0.689621364484675 - fConst16);
		fConst43 = fConst16 + 7.621731298870603;
		fConst44 = 2.0 * (7.621731298870603 - fConst16);
		fConst45 = 1.0 / ((fConst12 + 0.168404871113589) / fConst11 + 1.069358407707312);
		fConst46 = (fConst12 + -0.168404871113589) / fConst11 + 1.069358407707312;
		fConst47 = 2.0 * (1.069358407707312 - fConst16);
		fConst48 = fConst16 + 53.53615295455673;
		fConst49 = 2.0 * (53.53615295455673 - fConst16);
		fConst50 = std::tan(31665.269715622984 / fConst0);
		fConst51 = 1.0 / fConst50;
		fConst52 = 1.0 / ((fConst51 + 3.1897274020965583) / fConst50 + 4.076781969643807);
		fConst53 = (fConst51 + -3.1897274020965583) / fConst50 + 4.076781969643807;
		fConst54 = mydsp_faustpower2_f(fConst50);
		fConst55 = 1.0 / fConst54;
		fConst56 = 2.0 * (4.076781969643807 - fConst55);
		fConst57 = 0.0017661728399818856 / fConst54;
		fConst58 = fConst57 + 0.00040767818495825777;
		fConst59 = 2.0 * (0.00040767818495825777 - fConst57);
		fConst60 = 1.0 / ((fConst51 + 0.7431304601070396) / fConst50 + 1.450071084655647);
		fConst61 = (fConst51 + -0.7431304601070396) / fConst50 + 1.450071084655647;
		fConst62 = 2.0 * (1.450071084655647 - fConst55);
		fConst63 = 11.052052171507189 / fConst54;
		fConst64 = fConst63 + 1.450071084655647;
		fConst65 = 2.0 * (1.450071084655647 - fConst63);
		fConst66 = 1.0 / ((fConst51 + 0.157482159302087) / fConst50 + 0.9351401670315425);
		fConst67 = (fConst51 + -0.157482159302087) / fConst50 + 0.9351401670315425;
		fConst68 = 2.0 * (0.9351401670315425 - fConst55);
		fConst69 = 50.063807016150385 / fConst54;
		fConst70 = fConst69 + 0.9351401670315425;
		fConst71 = 2.0 * (0.9351401670315425 - fConst69);
		fConst72 = 1.0 / ((fConst51 + 0.782413046821645) / fConst50 + 0.24529150870616);
		fConst73 = (fConst51 + -0.782413046821645) / fConst50 + 0.24529150870616;
		fConst74 = 2.0 * (0.24529150870616 - fConst55);
		fConst75 = 9.9999997055e-05 / fConst54;
		fConst76 = fConst75 + 0.000433227200555;
		fConst77 = 2.0 * (0.000433227200555 - fConst75);
		fConst78 = 1.0 / ((fConst51 + 0.512478641889141) / fConst50 + 0.689621364484675);
		fConst79 = (fConst51 + -0.512478641889141) / fConst50 + 0.689621364484675;
		fConst80 = 2.0 * (0.689621364484675 - fConst55);
		fConst81 = fConst55 + 7.621731298870603;
		fConst82 = 2.0 * (7.621731298870603 - fConst55);
		fConst83 = 1.0 / ((fConst51 + 0.168404871113589) / fConst50 + 1.069358407707312);
		fConst84 = (fConst51 + -0.168404871113589) / fConst50 + 1.069358407707312;
		fConst85 = 2.0 * (1.069358407707312 - fConst55);
		fConst86 = fConst55 + 53.53615295455673;
		fConst87 = 2.0 * (53.53615295455673 - fConst55);
		fConst88 = std::tan(19947.869932656024 / fConst0);
		fConst89 = 1.0 / fConst88;
		fConst90 = 1.0 / ((fConst89 + 3.1897274020965583) / fConst88 + 4.076781969643807);
		fConst91 = (fConst89 + -3.1897274020965583) / fConst88 + 4.076781969643807;
		fConst92 = mydsp_faustpower2_f(fConst88);
		fConst93 = 1.0 / fConst92;
		fConst94 = 2.0 * (4.076781969643807 - fConst93);
		fConst95 = 0.0017661728399818856 / fConst92;
		fConst96 = fConst95 + 0.00040767818495825777;
		fConst97 = 2.0 * (0.00040767818495825777 - fConst95);
		fConst98 = 1.0 / ((fConst89 + 0.7431304601070396) / fConst88 + 1.450071084655647);
		fConst99 = (fConst89 + -0.7431304601070396) / fConst88 + 1.450071084655647;
		fConst100 = 2.0 * (1.450071084655647 - fConst93);
		fConst101 = 11.052052171507189 / fConst92;
		fConst102 = fConst101 + 1.450071084655647;
		fConst103 = 2.0 * (1.450071084655647 - fConst101);
		fConst104 = 1.0 / ((fConst89 + 0.157482159302087) / fConst88 + 0.9351401670315425);
		fConst105 = (fConst89 + -0.157482159302087) / fConst88 + 0.9351401670315425;
		fConst106 = 2.0 * (0.9351401670315425 - fConst93);
		fConst107 = 50.063807016150385 / fConst92;
		fConst108 = fConst107 + 0.9351401670315425;
		fConst109 = 2.0 * (0.9351401670315425 - fConst107);
		fConst110 = 1.0 / ((fConst89 + 0.782413046821645) / fConst88 + 0.24529150870616);
		fConst111 = (fConst89 + -0.782413046821645) / fConst88 + 0.24529150870616;
		fConst112 = 2.0 * (0.24529150870616 - fConst93);
		fConst113 = 9.9999997055e-05 / fConst92;
		fConst114 = fConst113 + 0.000433227200555;
		fConst115 = 2.0 * (0.000433227200555 - fConst113);
		fConst116 = 1.0 / ((fConst89 + 0.512478641889141) / fConst88 + 0.689621364484675);
		fConst117 = (fConst89 + -0.512478641889141) / fConst88 + 0.689621364484675;
		fConst118 = 2.0 * (0.689621364484675 - fConst93);
		fConst119 = fConst93 + 7.621731298870603;
		fConst120 = 2.0 * (7.621731298870603 - fConst93);
		fConst121 = 1.0 / ((fConst89 + 0.168404871113589) / fConst88 + 1.069358407707312);
		fConst122 = (fConst89 + -0.168404871113589) / fConst88 + 1.069358407707312;
		fConst123 = 2.0 * (1.069358407707312 - fConst93);
		fConst124 = fConst93 + 53.53615295455673;
		fConst125 = 2.0 * (53.53615295455673 - fConst93);
		fConst126 = std::tan(12566.370614359172 / fConst0);
		fConst127 = 1.0 / fConst126;
		fConst128 = 1.0 / ((fConst127 + 3.1897274020965583) / fConst126 + 4.076781969643807);
		fConst129 = (fConst127 + -3.1897274020965583) / fConst126 + 4.076781969643807;
		fConst130 = mydsp_faustpower2_f(fConst126);
		fConst131 = 1.0 / fConst130;
		fConst132 = 2.0 * (4.076781969643807 - fConst131);
		fConst133 = 0.0017661728399818856 / fConst130;
		fConst134 = fConst133 + 0.00040767818495825777;
		fConst135 = 2.0 * (0.00040767818495825777 - fConst133);
		fConst136 = 1.0 / ((fConst127 + 0.7431304601070396) / fConst126 + 1.450071084655647);
		fConst137 = (fConst127 + -0.7431304601070396) / fConst126 + 1.450071084655647;
		fConst138 = 2.0 * (1.450071084655647 - fConst131);
		fConst139 = 11.052052171507189 / fConst130;
		fConst140 = fConst139 + 1.450071084655647;
		fConst141 = 2.0 * (1.450071084655647 - fConst139);
		fConst142 = 1.0 / ((fConst127 + 0.157482159302087) / fConst126 + 0.9351401670315425);
		fConst143 = (fConst127 + -0.157482159302087) / fConst126 + 0.9351401670315425;
		fConst144 = 2.0 * (0.9351401670315425 - fConst131);
		fConst145 = 50.063807016150385 / fConst130;
		fConst146 = fConst145 + 0.9351401670315425;
		fConst147 = 2.0 * (0.9351401670315425 - fConst145);
		fConst148 = 1.0 / ((fConst127 + 0.782413046821645) / fConst126 + 0.24529150870616);
		fConst149 = (fConst127 + -0.782413046821645) / fConst126 + 0.24529150870616;
		fConst150 = 2.0 * (0.24529150870616 - fConst131);
		fConst151 = 9.9999997055e-05 / fConst130;
		fConst152 = fConst151 + 0.000433227200555;
		fConst153 = 2.0 * (0.000433227200555 - fConst151);
		fConst154 = 1.0 / ((fConst127 + 0.512478641889141) / fConst126 + 0.689621364484675);
		fConst155 = (fConst127 + -0.512478641889141) / fConst126 + 0.689621364484675;
		fConst156 = 2.0 * (0.689621364484675 - fConst131);
		fConst157 = fConst131 + 7.621731298870603;
		fConst158 = 2.0 * (7.621731298870603 - fConst131);
		fConst159 = 1.0 / ((fConst127 + 0.168404871113589) / fConst126 + 1.069358407707312);
		fConst160 = (fConst127 + -0.168404871113589) / fConst126 + 1.069358407707312;
		fConst161 = 2.0 * (1.069358407707312 - fConst131);
		fConst162 = fConst131 + 53.53615295455673;
		fConst163 = 2.0 * (53.53615295455673 - fConst131);
		fConst164 = std::tan(7916.317428905746 / fConst0);
		fConst165 = 1.0 / fConst164;
		fConst166 = 1.0 / ((fConst165 + 3.1897274020965583) / fConst164 + 4.076781969643807);
		fConst167 = (fConst165 + -3.1897274020965583) / fConst164 + 4.076781969643807;
		fConst168 = mydsp_faustpower2_f(fConst164);
		fConst169 = 1.0 / fConst168;
		fConst170 = 2.0 * (4.076781969643807 - fConst169);
		fConst171 = 0.0017661728399818856 / fConst168;
		fConst172 = fConst171 + 0.00040767818495825777;
		fConst173 = 2.0 * (0.00040767818495825777 - fConst171);
		fConst174 = 1.0 / ((fConst165 + 0.7431304601070396) / fConst164 + 1.450071084655647);
		fConst175 = (fConst165 + -0.7431304601070396) / fConst164 + 1.450071084655647;
		fConst176 = 2.0 * (1.450071084655647 - fConst169);
		fConst177 = 11.052052171507189 / fConst168;
		fConst178 = fConst177 + 1.450071084655647;
		fConst179 = 2.0 * (1.450071084655647 - fConst177);
		fConst180 = 1.0 / ((fConst165 + 0.157482159302087) / fConst164 + 0.9351401670315425);
		fConst181 = (fConst165 + -0.157482159302087) / fConst164 + 0.9351401670315425;
		fConst182 = 2.0 * (0.9351401670315425 - fConst169);
		fConst183 = 50.063807016150385 / fConst168;
		fConst184 = fConst183 + 0.9351401670315425;
		fConst185 = 2.0 * (0.9351401670315425 - fConst183);
		fConst186 = 1.0 / ((fConst165 + 0.782413046821645) / fConst164 + 0.24529150870616);
		fConst187 = (fConst165 + -0.782413046821645) / fConst164 + 0.24529150870616;
		fConst188 = 2.0 * (0.24529150870616 - fConst169);
		fConst189 = 9.9999997055e-05 / fConst168;
		fConst190 = fConst189 + 0.000433227200555;
		fConst191 = 2.0 * (0.000433227200555 - fConst189);
		fConst192 = 1.0 / ((fConst165 + 0.512478641889141) / fConst164 + 0.689621364484675);
		fConst193 = (fConst165 + -0.512478641889141) / fConst164 + 0.689621364484675;
		fConst194 = 2.0 * (0.689621364484675 - fConst169);
		fConst195 = fConst169 + 7.621731298870603;
		fConst196 = 2.0 * (7.621731298870603 - fConst169);
		fConst197 = 1.0 / ((fConst165 + 0.168404871113589) / fConst164 + 1.069358407707312);
		fConst198 = (fConst165 + -0.168404871113589) / fConst164 + 1.069358407707312;
		fConst199 = 2.0 * (1.069358407707312 - fConst169);
		fConst200 = fConst169 + 53.53615295455673;
		fConst201 = 2.0 * (53.53615295455673 - fConst169);
		fConst202 = std::tan(4986.967483164005 / fConst0);
		fConst203 = 1.0 / fConst202;
		fConst204 = 1.0 / ((fConst203 + 3.1897274020965583) / fConst202 + 4.076781969643807);
		fConst205 = (fConst203 + -3.1897274020965583) / fConst202 + 4.076781969643807;
		fConst206 = mydsp_faustpower2_f(fConst202);
		fConst207 = 1.0 / fConst206;
		fConst208 = 2.0 * (4.076781969643807 - fConst207);
		fConst209 = 0.0017661728399818856 / fConst206;
		fConst210 = fConst209 + 0.00040767818495825777;
		fConst211 = 2.0 * (0.00040767818495825777 - fConst209);
		fConst212 = 1.0 / ((fConst203 + 0.7431304601070396) / fConst202 + 1.450071084655647);
		fConst213 = (fConst203 + -0.7431304601070396) / fConst202 + 1.450071084655647;
		fConst214 = 2.0 * (1.450071084655647 - fConst207);
		fConst215 = 11.052052171507189 / fConst206;
		fConst216 = fConst215 + 1.450071084655647;
		fConst217 = 2.0 * (1.450071084655647 - fConst215);
		fConst218 = 1.0 / ((fConst203 + 0.157482159302087) / fConst202 + 0.9351401670315425);
		fConst219 = (fConst203 + -0.157482159302087) / fConst202 + 0.9351401670315425;
		fConst220 = 2.0 * (0.9351401670315425 - fConst207);
		fConst221 = 50.063807016150385 / fConst206;
		fConst222 = fConst221 + 0.9351401670315425;
		fConst223 = 2.0 * (0.9351401670315425 - fConst221);
		fConst224 = 1.0 / ((fConst203 + 0.782413046821645) / fConst202 + 0.24529150870616);
		fConst225 = (fConst203 + -0.782413046821645) / fConst202 + 0.24529150870616;
		fConst226 = 2.0 * (0.24529150870616 - fConst207);
		fConst227 = 9.9999997055e-05 / fConst206;
		fConst228 = fConst227 + 0.000433227200555;
		fConst229 = 2.0 * (0.000433227200555 - fConst227);
		fConst230 = 1.0 / ((fConst203 + 0.512478641889141) / fConst202 + 0.689621364484675);
		fConst231 = (fConst203 + -0.512478641889141) / fConst202 + 0.689621364484675;
		fConst232 = 2.0 * (0.689621364484675 - fConst207);
		fConst233 = fConst207 + 7.621731298870603;
		fConst234 = 2.0 * (7.621731298870603 - fConst207);
		fConst235 = 1.0 / ((fConst203 + 0.168404871113589) / fConst202 + 1.069358407707312);
		fConst236 = (fConst203 + -0.168404871113589) / fConst202 + 1.069358407707312;
		fConst237 = 2.0 * (1.069358407707312 - fConst207);
		fConst238 = fConst207 + 53.53615295455673;
		fConst239 = 2.0 * (53.53615295455673 - fConst207);
		fConst240 = std::tan(3141.592653589793 / fConst0);
		fConst241 = 1.0 / fConst240;
		fConst242 = 1.0 / ((fConst241 + 3.1897274020965583) / fConst240 + 4.076781969643807);
		fConst243 = (fConst241 + -3.1897274020965583) / fConst240 + 4.076781969643807;
		fConst244 = mydsp_faustpower2_f(fConst240);
		fConst245 = 1.0 / fConst244;
		fConst246 = 2.0 * (4.076781969643807 - fConst245);
		fConst247 = 0.0017661728399818856 / fConst244;
		fConst248 = fConst247 + 0.00040767818495825777;
		fConst249 = 2.0 * (0.00040767818495825777 - fConst247);
		fConst250 = 1.0 / ((fConst241 + 0.7431304601070396) / fConst240 + 1.450071084655647);
		fConst251 = (fConst241 + -0.7431304601070396) / fConst240 + 1.450071084655647;
		fConst252 = 2.0 * (1.450071084655647 - fConst245);
		fConst253 = 11.052052171507189 / fConst244;
		fConst254 = fConst253 + 1.450071084655647;
		fConst255 = 2.0 * (1.450071084655647 - fConst253);
		fConst256 = 1.0 / ((fConst241 + 0.157482159302087) / fConst240 + 0.9351401670315425);
		fConst257 = (fConst241 + -0.157482159302087) / fConst240 + 0.9351401670315425;
		fConst258 = 2.0 * (0.9351401670315425 - fConst245);
		fConst259 = 50.063807016150385 / fConst244;
		fConst260 = fConst259 + 0.9351401670315425;
		fConst261 = 2.0 * (0.9351401670315425 - fConst259);
		fConst262 = 1.0 / ((fConst241 + 0.782413046821645) / fConst240 + 0.24529150870616);
		fConst263 = (fConst241 + -0.782413046821645) / fConst240 + 0.24529150870616;
		fConst264 = 2.0 * (0.24529150870616 - fConst245);
		fConst265 = 9.9999997055e-05 / fConst244;
		fConst266 = fConst265 + 0.000433227200555;
		fConst267 = 2.0 * (0.000433227200555 - fConst265);
		fConst268 = 1.0 / ((fConst241 + 0.512478641889141) / fConst240 + 0.689621364484675);
		fConst269 = (fConst241 + -0.512478641889141) / fConst240 + 0.689621364484675;
		fConst270 = 2.0 * (0.689621364484675 - fConst245);
		fConst271 = fConst245 + 7.621731298870603;
		fConst272 = 2.0 * (7.621731298870603 - fConst245);
		fConst273 = 1.0 / ((fConst241 + 0.168404871113589) / fConst240 + 1.069358407707312);
		fConst274 = (fConst241 + -0.168404871113589) / fConst240 + 1.069358407707312;
		fConst275 = 2.0 * (1.069358407707312 - fConst245);
		fConst276 = fConst245 + 53.53615295455673;
		fConst277 = 2.0 * (53.53615295455673 - fConst245);
		fConst278 = std::tan(1979.079357226436 / fConst0);
		fConst279 = 1.0 / fConst278;
		fConst280 = 1.0 / ((fConst279 + 3.1897274020965583) / fConst278 + 4.076781969643807);
		fConst281 = (fConst279 + -3.1897274020965583) / fConst278 + 4.076781969643807;
		fConst282 = mydsp_faustpower2_f(fConst278);
		fConst283 = 1.0 / fConst282;
		fConst284 = 2.0 * (4.076781969643807 - fConst283);
		fConst285 = 0.0017661728399818856 / fConst282;
		fConst286 = fConst285 + 0.00040767818495825777;
		fConst287 = 2.0 * (0.00040767818495825777 - fConst285);
		fConst288 = 1.0 / ((fConst279 + 0.7431304601070396) / fConst278 + 1.450071084655647);
		fConst289 = (fConst279 + -0.7431304601070396) / fConst278 + 1.450071084655647;
		fConst290 = 2.0 * (1.450071084655647 - fConst283);
		fConst291 = 11.052052171507189 / fConst282;
		fConst292 = fConst291 + 1.450071084655647;
		fConst293 = 2.0 * (1.450071084655647 - fConst291);
		fConst294 = 1.0 / ((fConst279 + 0.157482159302087) / fConst278 + 0.9351401670315425);
		fConst295 = (fConst279 + -0.157482159302087) / fConst278 + 0.9351401670315425;
		fConst296 = 2.0 * (0.9351401670315425 - fConst283);
		fConst297 = 50.063807016150385 / fConst282;
		fConst298 = fConst297 + 0.9351401670315425;
		fConst299 = 2.0 * (0.9351401670315425 - fConst297);
		fConst300 = 1.0 / ((fConst279 + 0.782413046821645) / fConst278 + 0.24529150870616);
		fConst301 = (fConst279 + -0.782413046821645) / fConst278 + 0.24529150870616;
		fConst302 = 2.0 * (0.24529150870616 - fConst283);
		fConst303 = 9.9999997055e-05 / fConst282;
		fConst304 = fConst303 + 0.000433227200555;
		fConst305 = 2.0 * (0.000433227200555 - fConst303);
		fConst306 = 1.0 / ((fConst279 + 0.512478641889141) / fConst278 + 0.689621364484675);
		fConst307 = (fConst279 + -0.512478641889141) / fConst278 + 0.689621364484675;
		fConst308 = 2.0 * (0.689621364484675 - fConst283);
		fConst309 = fConst283 + 7.621731298870603;
		fConst310 = 2.0 * (7.621731298870603 - fConst283);
		fConst311 = 1.0 / ((fConst279 + 0.168404871113589) / fConst278 + 1.069358407707312);
		fConst312 = (fConst279 + -0.168404871113589) / fConst278 + 1.069358407707312;
		fConst313 = 2.0 * (1.069358407707312 - fConst283);
		fConst314 = fConst283 + 53.53615295455673;
		fConst315 = 2.0 * (53.53615295455673 - fConst283);
		fConst316 = std::tan(1246.7418707910015 / fConst0);
		fConst317 = 1.0 / fConst316;
		fConst318 = 1.0 / ((fConst317 + 3.1897274020965583) / fConst316 + 4.076781969643807);
		fConst319 = (fConst317 + -3.1897274020965583) / fConst316 + 4.076781969643807;
		fConst320 = mydsp_faustpower2_f(fConst316);
		fConst321 = 1.0 / fConst320;
		fConst322 = 2.0 * (4.076781969643807 - fConst321);
		fConst323 = 0.0017661728399818856 / fConst320;
		fConst324 = fConst323 + 0.00040767818495825777;
		fConst325 = 2.0 * (0.00040767818495825777 - fConst323);
		fConst326 = 1.0 / ((fConst317 + 0.7431304601070396) / fConst316 + 1.450071084655647);
		fConst327 = (fConst317 + -0.7431304601070396) / fConst316 + 1.450071084655647;
		fConst328 = 2.0 * (1.450071084655647 - fConst321);
		fConst329 = 11.052052171507189 / fConst320;
		fConst330 = fConst329 + 1.450071084655647;
		fConst331 = 2.0 * (1.450071084655647 - fConst329);
		fConst332 = 1.0 / ((fConst317 + 0.157482159302087) / fConst316 + 0.9351401670315425);
		fConst333 = (fConst317 + -0.157482159302087) / fConst316 + 0.9351401670315425;
		fConst334 = 2.0 * (0.9351401670315425 - fConst321);
		fConst335 = 50.063807016150385 / fConst320;
		fConst336 = fConst335 + 0.9351401670315425;
		fConst337 = 2.0 * (0.9351401670315425 - fConst335);
		fConst338 = 1.0 / ((fConst317 + 0.782413046821645) / fConst316 + 0.24529150870616);
		fConst339 = (fConst317 + -0.782413046821645) / fConst316 + 0.24529150870616;
		fConst340 = 2.0 * (0.24529150870616 - fConst321);
		fConst341 = 9.9999997055e-05 / fConst320;
		fConst342 = fConst341 + 0.000433227200555;
		fConst343 = 2.0 * (0.000433227200555 - fConst341);
		fConst344 = 1.0 / ((fConst317 + 0.512478641889141) / fConst316 + 0.689621364484675);
		fConst345 = (fConst317 + -0.512478641889141) / fConst316 + 0.689621364484675;
		fConst346 = 2.0 * (0.689621364484675 - fConst321);
		fConst347 = fConst321 + 7.621731298870603;
		fConst348 = 2.0 * (7.621731298870603 - fConst321);
		fConst349 = 1.0 / ((fConst317 + 0.168404871113589) / fConst316 + 1.069358407707312);
		fConst350 = (fConst317 + -0.168404871113589) / fConst316 + 1.069358407707312;
		fConst351 = 2.0 * (1.069358407707312 - fConst321);
		fConst352 = fConst321 + 53.53615295455673;
		fConst353 = 2.0 * (53.53615295455673 - fConst321);
		fConst354 = std::tan(785.3981633974482 / fConst0);
		fConst355 = 1.0 / fConst354;
		fConst356 = 1.0 / ((fConst355 + 3.1897274020965583) / fConst354 + 4.076781969643807);
		fConst357 = (fConst355 + -3.1897274020965583) / fConst354 + 4.076781969643807;
		fConst358 = mydsp_faustpower2_f(fConst354);
		fConst359 = 1.0 / fConst358;
		fConst360 = 2.0 * (4.076781969643807 - fConst359);
		fConst361 = 0.0017661728399818856 / fConst358;
		fConst362 = fConst361 + 0.00040767818495825777;
		fConst363 = 2.0 * (0.00040767818495825777 - fConst361);
		fConst364 = 1.0 / ((fConst355 + 0.7431304601070396) / fConst354 + 1.450071084655647);
		fConst365 = (fConst355 + -0.7431304601070396) / fConst354 + 1.450071084655647;
		fConst366 = 2.0 * (1.450071084655647 - fConst359);
		fConst367 = 11.052052171507189 / fConst358;
		fConst368 = fConst367 + 1.450071084655647;
		fConst369 = 2.0 * (1.450071084655647 - fConst367);
		fConst370 = 1.0 / ((fConst355 + 0.157482159302087) / fConst354 + 0.9351401670315425);
		fConst371 = (fConst355 + -0.157482159302087) / fConst354 + 0.9351401670315425;
		fConst372 = 2.0 * (0.9351401670315425 - fConst359);
		fConst373 = 50.063807016150385 / fConst358;
		fConst374 = fConst373 + 0.9351401670315425;
		fConst375 = 2.0 * (0.9351401670315425 - fConst373);
		fConst376 = 1.0 / ((fConst355 + 0.782413046821645) / fConst354 + 0.24529150870616);
		fConst377 = (fConst355 + -0.782413046821645) / fConst354 + 0.24529150870616;
		fConst378 = 2.0 * (0.24529150870616 - fConst359);
		fConst379 = 9.9999997055e-05 / fConst358;
		fConst380 = fConst379 + 0.000433227200555;
		fConst381 = 2.0 * (0.000433227200555 - fConst379);
		fConst382 = 1.0 / ((fConst355 + 0.512478641889141) / fConst354 + 0.689621364484675);
		fConst383 = (fConst355 + -0.512478641889141) / fConst354 + 0.689621364484675;
		fConst384 = 2.0 * (0.689621364484675 - fConst359);
		fConst385 = fConst359 + 7.621731298870603;
		fConst386 = 2.0 * (7.621731298870603 - fConst359);
		fConst387 = 1.0 / ((fConst355 + 0.168404871113589) / fConst354 + 1.069358407707312);
		fConst388 = (fConst355 + -0.168404871113589) / fConst354 + 1.069358407707312;
		fConst389 = 2.0 * (1.069358407707312 - fConst359);
		fConst390 = fConst359 + 53.53615295455673;
		fConst391 = 2.0 * (53.53615295455673 - fConst359);
		fConst392 = std::tan(494.769839306609 / fConst0);
		fConst393 = 1.0 / fConst392;
		fConst394 = 1.0 / ((fConst393 + 3.1897274020965583) / fConst392 + 4.076781969643807);
		fConst395 = (fConst393 + -3.1897274020965583) / fConst392 + 4.076781969643807;
		fConst396 = mydsp_faustpower2_f(fConst392);
		fConst397 = 1.0 / fConst396;
		fConst398 = 2.0 * (4.076781969643807 - fConst397);
		fConst399 = 0.0017661728399818856 / fConst396;
		fConst400 = fConst399 + 0.00040767818495825777;
		fConst401 = 2.0 * (0.00040767818495825777 - fConst399);
		fConst402 = 1.0 / ((fConst393 + 0.7431304601070396) / fConst392 + 1.450071084655647);
		fConst403 = (fConst393 + -0.7431304601070396) / fConst392 + 1.450071084655647;
		fConst404 = 2.0 * (1.450071084655647 - fConst397);
		fConst405 = 11.052052171507189 / fConst396;
		fConst406 = fConst405 + 1.450071084655647;
		fConst407 = 2.0 * (1.450071084655647 - fConst405);
		fConst408 = 1.0 / ((fConst393 + 0.157482159302087) / fConst392 + 0.9351401670315425);
		fConst409 = (fConst393 + -0.157482159302087) / fConst392 + 0.9351401670315425;
		fConst410 = 2.0 * (0.9351401670315425 - fConst397);
		fConst411 = 50.063807016150385 / fConst396;
		fConst412 = fConst411 + 0.9351401670315425;
		fConst413 = 2.0 * (0.9351401670315425 - fConst411);
		fConst414 = 1.0 / ((fConst393 + 0.782413046821645) / fConst392 + 0.24529150870616);
		fConst415 = (fConst393 + -0.782413046821645) / fConst392 + 0.24529150870616;
		fConst416 = 2.0 * (0.24529150870616 - fConst397);
		fConst417 = 9.9999997055e-05 / fConst396;
		fConst418 = fConst417 + 0.000433227200555;
		fConst419 = 2.0 * (0.000433227200555 - fConst417);
		fConst420 = 1.0 / ((fConst393 + 0.512478641889141) / fConst392 + 0.689621364484675);
		fConst421 = (fConst393 + -0.512478641889141) / fConst392 + 0.689621364484675;
		fConst422 = 2.0 * (0.689621364484675 - fConst397);
		fConst423 = fConst397 + 7.621731298870603;
		fConst424 = 2.0 * (7.621731298870603 - fConst397);
		fConst425 = 1.0 / ((fConst393 + 0.168404871113589) / fConst392 + 1.069358407707312);
		fConst426 = (fConst393 + -0.168404871113589) / fConst392 + 1.069358407707312;
		fConst427 = 2.0 * (1.069358407707312 - fConst397);
		fConst428 = fConst397 + 53.53615295455673;
		fConst429 = 2.0 * (53.53615295455673 - fConst397);
		fConst430 = std::tan(311.68546769775037 / fConst0);
		fConst431 = 1.0 / fConst430;
		fConst432 = 1.0 / ((fConst431 + 3.1897274020965583) / fConst430 + 4.076781969643807);
		fConst433 = (fConst431 + -3.1897274020965583) / fConst430 + 4.076781969643807;
		fConst434 = mydsp_faustpower2_f(fConst430);
		fConst435 = 1.0 / fConst434;
		fConst436 = 2.0 * (4.076781969643807 - fConst435);
		fConst437 = 0.0017661728399818856 / fConst434;
		fConst438 = fConst437 + 0.00040767818495825777;
		fConst439 = 2.0 * (0.00040767818495825777 - fConst437);
		fConst440 = 1.0 / ((fConst431 + 0.7431304601070396) / fConst430 + 1.450071084655647);
		fConst441 = (fConst431 + -0.7431304601070396) / fConst430 + 1.450071084655647;
		fConst442 = 2.0 * (1.450071084655647 - fConst435);
		fConst443 = 11.052052171507189 / fConst434;
		fConst444 = fConst443 + 1.450071084655647;
		fConst445 = 2.0 * (1.450071084655647 - fConst443);
		fConst446 = 1.0 / ((fConst431 + 0.157482159302087) / fConst430 + 0.9351401670315425);
		fConst447 = (fConst431 + -0.157482159302087) / fConst430 + 0.9351401670315425;
		fConst448 = 2.0 * (0.9351401670315425 - fConst435);
		fConst449 = 50.063807016150385 / fConst434;
		fConst450 = fConst449 + 0.9351401670315425;
		fConst451 = 2.0 * (0.9351401670315425 - fConst449);
		fConst452 = 1.0 / ((fConst431 + 0.782413046821645) / fConst430 + 0.24529150870616);
		fConst453 = (fConst431 + -0.782413046821645) / fConst430 + 0.24529150870616;
		fConst454 = 2.0 * (0.24529150870616 - fConst435);
		fConst455 = 9.9999997055e-05 / fConst434;
		fConst456 = fConst455 + 0.000433227200555;
		fConst457 = 2.0 * (0.000433227200555 - fConst455);
		fConst458 = 1.0 / ((fConst431 + 0.512478641889141) / fConst430 + 0.689621364484675);
		fConst459 = (fConst431 + -0.512478641889141) / fConst430 + 0.689621364484675;
		fConst460 = 2.0 * (0.689621364484675 - fConst435);
		fConst461 = fConst435 + 7.621731298870603;
		fConst462 = 2.0 * (7.621731298870603 - fConst435);
		fConst463 = 1.0 / ((fConst431 + 0.168404871113589) / fConst430 + 1.069358407707312);
		fConst464 = (fConst431 + -0.168404871113589) / fConst430 + 1.069358407707312;
		fConst465 = 2.0 * (1.069358407707312 - fConst435);
		fConst466 = fConst435 + 53.53615295455673;
		fConst467 = 2.0 * (53.53615295455673 - fConst435);
		fConst468 = std::tan(196.34954084936206 / fConst0);
		fConst469 = 1.0 / fConst468;
		fConst470 = 1.0 / ((fConst469 + 3.1897274020965583) / fConst468 + 4.076781969643807);
		fConst471 = (fConst469 + -3.1897274020965583) / fConst468 + 4.076781969643807;
		fConst472 = mydsp_faustpower2_f(fConst468);
		fConst473 = 1.0 / fConst472;
		fConst474 = 2.0 * (4.076781969643807 - fConst473);
		fConst475 = 0.0017661728399818856 / fConst472;
		fConst476 = fConst475 + 0.00040767818495825777;
		fConst477 = 2.0 * (0.00040767818495825777 - fConst475);
		fConst478 = 1.0 / ((fConst469 + 0.7431304601070396) / fConst468 + 1.450071084655647);
		fConst479 = (fConst469 + -0.7431304601070396) / fConst468 + 1.450071084655647;
		fConst480 = 2.0 * (1.450071084655647 - fConst473);
		fConst481 = 11.052052171507189 / fConst472;
		fConst482 = fConst481 + 1.450071084655647;
		fConst483 = 2.0 * (1.450071084655647 - fConst481);
		fConst484 = 1.0 / ((fConst469 + 0.157482159302087) / fConst468 + 0.9351401670315425);
		fConst485 = (fConst469 + -0.157482159302087) / fConst468 + 0.9351401670315425;
		fConst486 = 2.0 * (0.9351401670315425 - fConst473);
		fConst487 = 50.063807016150385 / fConst472;
		fConst488 = fConst487 + 0.9351401670315425;
		fConst489 = 2.0 * (0.9351401670315425 - fConst487);
		fConst490 = 1.0 / ((fConst469 + 0.782413046821645) / fConst468 + 0.24529150870616);
		fConst491 = (fConst469 + -0.782413046821645) / fConst468 + 0.24529150870616;
		fConst492 = 2.0 * (0.24529150870616 - fConst473);
		fConst493 = 9.9999997055e-05 / fConst472;
		fConst494 = fConst493 + 0.000433227200555;
		fConst495 = 2.0 * (0.000433227200555 - fConst493);
		fConst496 = 1.0 / ((fConst469 + 0.512478641889141) / fConst468 + 0.689621364484675);
		fConst497 = (fConst469 + -0.512478641889141) / fConst468 + 0.689621364484675;
		fConst498 = 2.0 * (0.689621364484675 - fConst473);
		fConst499 = fConst473 + 7.621731298870603;
		fConst500 = 2.0 * (7.621731298870603 - fConst473);
		fConst501 = 1.0 / ((fConst469 + 0.168404871113589) / fConst468 + 1.069358407707312);
		fConst502 = (fConst469 + -0.168404871113589) / fConst468 + 1.069358407707312;
		fConst503 = 2.0 * (1.069358407707312 - fConst473);
		fConst504 = fConst473 + 53.53615295455673;
		fConst505 = 2.0 * (53.53615295455673 - fConst473);
		fConst506 = std::tan(123.69245982665232 / fConst0);
		fConst507 = 1.0 / fConst506;
		fConst508 = 1.0 / ((fConst507 + 3.1897274020965583) / fConst506 + 4.076781969643807);
		fConst509 = (fConst507 + -3.1897274020965583) / fConst506 + 4.076781969643807;
		fConst510 = mydsp_faustpower2_f(fConst506);
		fConst511 = 1.0 / fConst510;
		fConst512 = 2.0 * (4.076781969643807 - fConst511);
		fConst513 = 0.0017661728399818856 / fConst510;
		fConst514 = fConst513 + 0.00040767818495825777;
		fConst515 = 2.0 * (0.00040767818495825777 - fConst513);
		fConst516 = 1.0 / ((fConst507 + 0.7431304601070396) / fConst506 + 1.450071084655647);
		fConst517 = (fConst507 + -0.7431304601070396) / fConst506 + 1.450071084655647;
		fConst518 = 2.0 * (1.450071084655647 - fConst511);
		fConst519 = 11.052052171507189 / fConst510;
		fConst520 = fConst519 + 1.450071084655647;
		fConst521 = 2.0 * (1.450071084655647 - fConst519);
		fConst522 = 1.0 / ((fConst507 + 0.157482159302087) / fConst506 + 0.9351401670315425);
		fConst523 = (fConst507 + -0.157482159302087) / fConst506 + 0.9351401670315425;
		fConst524 = 2.0 * (0.9351401670315425 - fConst511);
		fConst525 = 50.063807016150385 / fConst510;
		fConst526 = fConst525 + 0.9351401670315425;
		fConst527 = 2.0 * (0.9351401670315425 - fConst525);
		fConst528 = 1.0 / ((fConst507 + 0.782413046821645) / fConst506 + 0.24529150870616);
		fConst529 = (fConst507 + -0.782413046821645) / fConst506 + 0.24529150870616;
		fConst530 = 2.0 * (0.24529150870616 - fConst511);
		fConst531 = 9.9999997055e-05 / fConst510;
		fConst532 = fConst531 + 0.000433227200555;
		fConst533 = 2.0 * (0.000433227200555 - fConst531);
		fConst534 = 1.0 / ((fConst507 + 0.512478641889141) / fConst506 + 0.689621364484675);
		fConst535 = (fConst507 + -0.512478641889141) / fConst506 + 0.689621364484675;
		fConst536 = 2.0 * (0.689621364484675 - fConst511);
		fConst537 = fConst511 + 7.621731298870603;
		fConst538 = 2.0 * (7.621731298870603 - fConst511);
		fConst539 = 1.0 / ((fConst507 + 0.168404871113589) / fConst506 + 1.069358407707312);
		fConst540 = (fConst507 + -0.168404871113589) / fConst506 + 1.069358407707312;
		fConst541 = 2.0 * (1.069358407707312 - fConst511);
		fConst542 = fConst511 + 53.53615295455673;
		fConst543 = 2.0 * (53.53615295455673 - fConst511);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(5.0);
		fHslider1 = static_cast<FAUSTFLOAT>(25.0);
		fHslider2 = static_cast<FAUSTFLOAT>(-2e+01);
		fVslider0 = static_cast<FAUSTFLOAT>(0.1);
		fHslider3 = static_cast<FAUSTFLOAT>(49.0);
		fVslider1 = static_cast<FAUSTFLOAT>(-0.1);
		fVslider2 = static_cast<FAUSTFLOAT>(0.1);
		fVslider3 = static_cast<FAUSTFLOAT>(0.5);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fVslider4 = static_cast<FAUSTFLOAT>(0.0);
		fVslider5 = static_cast<FAUSTFLOAT>(1.0);
		fEntry0 = static_cast<FAUSTFLOAT>(2.0);
		fVslider6 = static_cast<FAUSTFLOAT>(0.0);
		fVslider7 = static_cast<FAUSTFLOAT>(0.0);
		fVslider8 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fVslider9 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(0.9);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider5 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider6 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec6_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec7_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec9_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec8_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec10_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec11_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec12_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec13_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec14_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			iVec0_perm[l10] = 0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fYec0_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4096; l12 = faust_wrap_add(l12, 1)) {
			fYec1[l12] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec15_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fYec2_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4096; l15 = faust_wrap_add(l15, 1)) {
			fYec3[l15] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec16_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fYec4_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4096; l18 = faust_wrap_add(l18, 1)) {
			fYec5[l18] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec17_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec18_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			iRec20_perm[l21] = 0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec19_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fYec6_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fYec7_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fYec8_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fYec9_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fYec10_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fYec11_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fYec12_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fYec13_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fYec14_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fYec15_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fYec16_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fYec17_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fYec18_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fYec19_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fYec20_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fYec21_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fYec22_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fYec23_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fYec24_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fYec25_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4096; l43 = faust_wrap_add(l43, 1)) {
			fYec26[l43] = 0.0;
		}
		fYec26_idx = 0;
		fYec26_idx_save = 0;
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fYec27_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fYec28_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4096; l46 = faust_wrap_add(l46, 1)) {
			fYec29[l46] = 0.0;
		}
		fYec29_idx = 0;
		fYec29_idx_save = 0;
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fYec30_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fYec31_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4096; l49 = faust_wrap_add(l49, 1)) {
			fYec32[l49] = 0.0;
		}
		fYec32_idx = 0;
		fYec32_idx_save = 0;
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec5_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec4_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec3_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec2_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec1_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec22_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec21_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec25_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec23_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec28_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec26_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec32_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec31_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec30_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec29_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec39_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec38_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec37_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec36_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec35_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec34_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec33_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fRec46_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec45_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec44_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec43_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec42_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec41_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec40_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec53_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec52_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec51_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec50_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec49_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec48_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec47_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec60_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec59_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec58_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec57_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec56_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec55_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec54_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec67_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec66_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec65_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec64_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fRec63_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec62_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec61_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec74_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec73_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec72_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec71_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec70_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec69_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec68_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec81_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = faust_wrap_add(l108, 1)) {
			fRec80_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = faust_wrap_add(l109, 1)) {
			fRec79_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = faust_wrap_add(l110, 1)) {
			fRec78_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = faust_wrap_add(l111, 1)) {
			fRec77_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = faust_wrap_add(l112, 1)) {
			fRec76_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = faust_wrap_add(l113, 1)) {
			fRec75_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = faust_wrap_add(l114, 1)) {
			fRec88_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = faust_wrap_add(l115, 1)) {
			fRec87_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = faust_wrap_add(l116, 1)) {
			fRec86_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = faust_wrap_add(l117, 1)) {
			fRec85_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = faust_wrap_add(l118, 1)) {
			fRec84_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = faust_wrap_add(l119, 1)) {
			fRec83_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = faust_wrap_add(l120, 1)) {
			fRec82_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = faust_wrap_add(l121, 1)) {
			fRec95_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = faust_wrap_add(l122, 1)) {
			fRec94_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = faust_wrap_add(l123, 1)) {
			fRec93_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = faust_wrap_add(l124, 1)) {
			fRec92_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = faust_wrap_add(l125, 1)) {
			fRec91_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = faust_wrap_add(l126, 1)) {
			fRec90_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = faust_wrap_add(l127, 1)) {
			fRec89_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = faust_wrap_add(l128, 1)) {
			fRec102_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = faust_wrap_add(l129, 1)) {
			fRec101_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = faust_wrap_add(l130, 1)) {
			fRec100_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = faust_wrap_add(l131, 1)) {
			fRec99_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = faust_wrap_add(l132, 1)) {
			fRec98_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = faust_wrap_add(l133, 1)) {
			fRec97_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = faust_wrap_add(l134, 1)) {
			fRec96_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = faust_wrap_add(l135, 1)) {
			fRec109_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = faust_wrap_add(l136, 1)) {
			fRec108_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = faust_wrap_add(l137, 1)) {
			fRec107_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = faust_wrap_add(l138, 1)) {
			fRec106_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = faust_wrap_add(l139, 1)) {
			fRec105_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = faust_wrap_add(l140, 1)) {
			fRec104_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = faust_wrap_add(l141, 1)) {
			fRec103_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 4; l142 = faust_wrap_add(l142, 1)) {
			fRec116_perm[l142] = 0.0;
		}
		for (int l143 = 0; l143 < 4; l143 = faust_wrap_add(l143, 1)) {
			fRec115_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = faust_wrap_add(l144, 1)) {
			fRec114_perm[l144] = 0.0;
		}
		for (int l145 = 0; l145 < 4; l145 = faust_wrap_add(l145, 1)) {
			fRec113_perm[l145] = 0.0;
		}
		for (int l146 = 0; l146 < 4; l146 = faust_wrap_add(l146, 1)) {
			fRec112_perm[l146] = 0.0;
		}
		for (int l147 = 0; l147 < 4; l147 = faust_wrap_add(l147, 1)) {
			fRec111_perm[l147] = 0.0;
		}
		for (int l148 = 0; l148 < 4; l148 = faust_wrap_add(l148, 1)) {
			fRec110_perm[l148] = 0.0;
		}
		for (int l149 = 0; l149 < 4; l149 = faust_wrap_add(l149, 1)) {
			fRec123_perm[l149] = 0.0;
		}
		for (int l150 = 0; l150 < 4; l150 = faust_wrap_add(l150, 1)) {
			fRec122_perm[l150] = 0.0;
		}
		for (int l151 = 0; l151 < 4; l151 = faust_wrap_add(l151, 1)) {
			fRec121_perm[l151] = 0.0;
		}
		for (int l152 = 0; l152 < 4; l152 = faust_wrap_add(l152, 1)) {
			fRec120_perm[l152] = 0.0;
		}
		for (int l153 = 0; l153 < 4; l153 = faust_wrap_add(l153, 1)) {
			fRec119_perm[l153] = 0.0;
		}
		for (int l154 = 0; l154 < 4; l154 = faust_wrap_add(l154, 1)) {
			fRec118_perm[l154] = 0.0;
		}
		for (int l155 = 0; l155 < 4; l155 = faust_wrap_add(l155, 1)) {
			fRec117_perm[l155] = 0.0;
		}
		for (int l156 = 0; l156 < 4; l156 = faust_wrap_add(l156, 1)) {
			fRec127_perm[l156] = 0.0;
		}
		for (int l157 = 0; l157 < 4; l157 = faust_wrap_add(l157, 1)) {
			fRec126_perm[l157] = 0.0;
		}
		for (int l158 = 0; l158 < 4; l158 = faust_wrap_add(l158, 1)) {
			fRec125_perm[l158] = 0.0;
		}
		for (int l159 = 0; l159 < 4; l159 = faust_wrap_add(l159, 1)) {
			fRec124_perm[l159] = 0.0;
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
		ui_interface->openVerticalBox("virtual_analog_oscillators");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillator.lib for documentation and references");
		ui_interface->openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("Signal Levels");
		ui_interface->declare(&fVslider5, "0", "");
		ui_interface->declare(&fVslider5, "style", "vslider");
		ui_interface->addVerticalSlider("Sawtooth", &fVslider5, FAUSTFLOAT(1.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Pulse Train");
		ui_interface->declare(&fCheckbox1, "0", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)      See if you can hear a difference with the freq high and swept");
		ui_interface->addCheckButton("Order 3", &fCheckbox1);
		ui_interface->declare(&fVslider8, "1", "");
		ui_interface->declare(&fVslider8, "style", "vslider");
		ui_interface->addVerticalSlider("0x00", &fVslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider3, "2", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("Duty Cycle", &fVslider3, FAUSTFLOAT(0.5), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
		ui_interface->declare(&fVslider6, "2", "");
		ui_interface->declare(&fVslider6, "style", "vslider");
		ui_interface->addVerticalSlider("Square", &fVslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider7, "3", "");
		ui_interface->declare(&fVslider7, "style", "vslider");
		ui_interface->addVerticalSlider("Triangle", &fVslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider9, "4", "");
		ui_interface->declare(&fVslider9, "style", "vslider");
		ui_interface->declare(&fVslider9, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave (uses only amplitude controls)");
		ui_interface->addVerticalSlider("Pink Noise", &fVslider9, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider4, "5", "");
		ui_interface->declare(&fVslider4, "style", "vslider");
		ui_interface->addVerticalSlider("Ext Input", &fVslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Signal Parameters");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "hslider");
		ui_interface->declare(&fHslider2, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Mix Amplitude", &fHslider2, FAUSTFLOAT(-2e+01), FAUSTFLOAT(-1.2e+02), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "style", "hslider");
		ui_interface->declare(&fHslider3, "tooltip", "Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fHslider3, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider3, FAUSTFLOAT(49.0), FAUSTFLOAT(1.0), FAUSTFLOAT(88.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
		ui_interface->declare(&fVslider1, "3", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Percentage frequency-shift up or down for second oscillator");
		ui_interface->declare(&fVslider1, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider1, FAUSTFLOAT(-0.1), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider2, "4", "");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider2, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider2, FAUSTFLOAT(0.1), FAUSTFLOAT(-1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider0, "5", "");
		ui_interface->declare(&fVslider0, "scale", "log");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider0, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider0, FAUSTFLOAT(0.1), FAUSTFLOAT(0.001), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.001));
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtooth aliasing suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, FAUSTFLOAT(2.0), FAUSTFLOAT(1.0), FAUSTFLOAT(4.0), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "See Faust's effect.lib for info and references");
		ui_interface->openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the Moog VCF has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "Select moog_vcf_2b (two-biquad) implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface->addCheckButton("Use Biquads", &fCheckbox2);
		ui_interface->declare(&fCheckbox3, "2", "");
		ui_interface->declare(&fCheckbox3, "tooltip", "If using biquads, make them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fCheckbox3);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "tooltip", "The VCF resonates at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).  The VCF response is flat below the corner frequency, and rolls off -24 dB per octave above.");
		ui_interface->declare(&fHslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Corner Frequency", &fHslider1, FAUSTFLOAT(25.0), FAUSTFLOAT(1.0), FAUSTFLOAT(88.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "Amount of resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface->addHorizontalSlider("Corner Resonance", &fHslider4, FAUSTFLOAT(0.9), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "output level in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("VCF Output Level", &fHslider0, FAUSTFLOAT(5.0), FAUSTFLOAT(-6e+01), FAUSTFLOAT(2e+01), FAUSTFLOAT(0.1));
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
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fHslider0));
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow1 = 0.4400000000000004 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fHslider1) + -49.0));
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fHslider2));
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fSlow3 = static_cast<double>(fVslider0);
		double fSlow4 = ((fSlow3 > 0.0) ? std::exp(-(fConst1 / fSlow3)) : 0.0);
		double fSlow5 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fHslider3) + -49.0)) * (1.0 - fSlow4);
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fZec0[4];
		double fZec1[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow6 = 1.0 - 0.01 * static_cast<double>(fVslider1);
		double fZec2[4];
		double fZec3[4];
		double fZec4[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fSlow7 = 0.01 * static_cast<double>(fVslider2) + 1.0;
		double fZec5[4];
		double fZec6[4];
		double fZec7[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fZec8[4];
		double fZec9[4];
		double fZec10[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fZec11[4];
		double fZec12[4];
		double fZec13[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fZec14[4];
		double fZec15[4];
		double fZec16[4];
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		double fZec17[4];
		double fZec18[4];
		double fZec19[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fZec20[4];
		int iZec21[4];
		double fZec22[4];
		double fZec23[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fZec24[4];
		double fZec25[4];
		double fYec2_tmp[8];
		double* fYec2 = &fYec2_tmp[4];
		double fZec26[4];
		int iZec27[4];
		double fZec28[4];
		double fZec29[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fZec30[4];
		double fZec31[4];
		double fYec4_tmp[8];
		double* fYec4 = &fYec4_tmp[4];
		double fZec32[4];
		int iZec33[4];
		double fZec34[4];
		double fZec35[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fSlow8 = 0.010000000000000009 * static_cast<double>(fVslider3);
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		int iRec20_tmp[8];
		int* iRec20 = &iRec20_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fZec36[4];
		double fZec37[4];
		int iSlow9 = static_cast<int>(static_cast<double>(fCheckbox0));
		double fSlow10 = static_cast<double>(fVslider4);
		double fSlow11 = 0.3333333333333333 * static_cast<double>(fVslider5);
		int iSlow12 = static_cast<int>(static_cast<double>(fEntry0) + -1.0);
		int iSlow13 = iSlow12 >= 2;
		int iSlow14 = iSlow12 >= 1;
		double fZec38[4];
		double fZec39[4];
		double fYec6_tmp[8];
		double* fYec6 = &fYec6_tmp[4];
		int iSlow15 = iSlow12 >= 3;
		double fZec40[4];
		double fZec41[4];
		double fYec7_tmp[8];
		double* fYec7 = &fYec7_tmp[4];
		double fYec8_tmp[8];
		double* fYec8 = &fYec8_tmp[4];
		double fZec42[4];
		double fYec9_tmp[8];
		double* fYec9 = &fYec9_tmp[4];
		double fYec10_tmp[8];
		double* fYec10 = &fYec10_tmp[4];
		double fYec11_tmp[8];
		double* fYec11 = &fYec11_tmp[4];
		double fZec43[4];
		double fZec44[4];
		double fYec12_tmp[8];
		double* fYec12 = &fYec12_tmp[4];
		double fZec45[4];
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
		double fZec46[4];
		double fZec47[4];
		double fYec18_tmp[8];
		double* fYec18 = &fYec18_tmp[4];
		double fZec48[4];
		double fYec19_tmp[8];
		double* fYec19 = &fYec19_tmp[4];
		double fYec20_tmp[8];
		double* fYec20 = &fYec20_tmp[4];
		double fYec21_tmp[8];
		double* fYec21 = &fYec21_tmp[4];
		double fYec22_tmp[8];
		double* fYec22 = &fYec22_tmp[4];
		double fYec23_tmp[8];
		double* fYec23 = &fYec23_tmp[4];
		double fSlow16 = fConst7 * static_cast<double>(fVslider6);
		double fSlow17 = fConst8 * static_cast<double>(fVslider7);
		double fSlow18 = fConst0 * static_cast<double>(fVslider8);
		double fSlow19 = static_cast<double>(fCheckbox1);
		double fSlow20 = fConst9 * fSlow19;
		double fZec49[4];
		double fYec24_tmp[8];
		double* fYec24 = &fYec24_tmp[4];
		double fYec25_tmp[8];
		double* fYec25 = &fYec25_tmp[4];
		double fZec50[4];
		int iZec51[4];
		double fZec52[4];
		double fZec53[4];
		double fZec54[4];
		int iZec55[4];
		double fZec56[4];
		double fYec27_tmp[8];
		double* fYec27 = &fYec27_tmp[4];
		double fYec28_tmp[8];
		double* fYec28 = &fYec28_tmp[4];
		double fZec57[4];
		int iZec58[4];
		double fZec59[4];
		double fZec60[4];
		double fZec61[4];
		int iZec62[4];
		double fZec63[4];
		double fYec30_tmp[8];
		double* fYec30 = &fYec30_tmp[4];
		double fYec31_tmp[8];
		double* fYec31 = &fYec31_tmp[4];
		double fZec64[4];
		int iZec65[4];
		double fZec66[4];
		double fZec67[4];
		double fZec68[4];
		int iZec69[4];
		double fSlow21 = 0.08333333333333333 * (1.0 - fSlow19);
		double fSlow22 = static_cast<double>(fVslider9);
		double fZec70[4];
		double fZec71[4];
		double fSlow23 = static_cast<double>(fHslider4);
		double fSlow24 = 4.0 * std::max<double>(0.0, std::min<double>(mydsp_faustpower4_f(fSlow23), 0.999999));
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow25 = std::min<double>(1.412799348810722, 1.4142135623730951 * fSlow23);
		double fSlow26 = 1.4142135623730951 * fSlow25;
		double fSlow27 = mydsp_faustpower2_f(fSlow25);
		double fSlow28 = fSlow26 + fSlow27;
		double fZec72[4];
		double fZec73[4];
		double fSlow29 = fSlow26 + 2.0;
		double fZec74[4];
		double fZec75[4];
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fSlow30 = 2.0 - fSlow26;
		double fZec76[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fSlow31 = mydsp_faustpower2_f(1.412799348810722 * fSlow23);
		double fSlow32 = 1.9980000000000002 * fSlow23;
		double fSlow33 = fSlow31 + fSlow32;
		double fSlow34 = fSlow32 + 2.0;
		double fZec77[4];
		double fZec78[4];
		double fZec79[4];
		double fZec80[4];
		double fZec81[4];
		double fZec82[4];
		double fZec83[4];
		double fZec84[4];
		double fZec85[4];
		double fZec86[4];
		double fZec87[4];
		double fZec88[4];
		double fZec89[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec24[4];
		double fZec90[4];
		double fZec91[4];
		double fZec92[4];
		double fSlow35 = 2.0 - fSlow32;
		double fZec93[4];
		double fZec94[4];
		double fZec95[4];
		double fZec96[4];
		double fZec97[4];
		double fZec98[4];
		double fZec99[4];
		double fZec100[4];
		double fZec101[4];
		double fZec102[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec27[4];
		int iSlow36 = static_cast<int>(static_cast<double>(fCheckbox2));
		int iSlow37 = static_cast<int>(static_cast<double>(fCheckbox3));
		double fZec103[4];
		double fZec104[4];
		double fZec105[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fSlow38 = static_cast<double>(fHslider5);
		double fSlow39 = (((0.001 * fSlow38) > 0.0) ? std::exp(-(fConst30 / fSlow38)) : 0.0);
		double fSlow40 = 1.0 - fSlow39;
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fZec106[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fZec107[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec53_tmp[8];
		double* fRec53 = &fRec53_tmp[4];
		double fRec52_tmp[8];
		double* fRec52 = &fRec52_tmp[4];
		double fRec51_tmp[8];
		double* fRec51 = &fRec51_tmp[4];
		double fZec108[4];
		double fRec50_tmp[8];
		double* fRec50 = &fRec50_tmp[4];
		double fRec49_tmp[8];
		double* fRec49 = &fRec49_tmp[4];
		double fRec48_tmp[8];
		double* fRec48 = &fRec48_tmp[4];
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		double fRec60_tmp[8];
		double* fRec60 = &fRec60_tmp[4];
		double fRec59_tmp[8];
		double* fRec59 = &fRec59_tmp[4];
		double fRec58_tmp[8];
		double* fRec58 = &fRec58_tmp[4];
		double fZec109[4];
		double fRec57_tmp[8];
		double* fRec57 = &fRec57_tmp[4];
		double fRec56_tmp[8];
		double* fRec56 = &fRec56_tmp[4];
		double fRec55_tmp[8];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[8];
		double* fRec54 = &fRec54_tmp[4];
		double fRec67_tmp[8];
		double* fRec67 = &fRec67_tmp[4];
		double fRec66_tmp[8];
		double* fRec66 = &fRec66_tmp[4];
		double fRec65_tmp[8];
		double* fRec65 = &fRec65_tmp[4];
		double fZec110[4];
		double fRec64_tmp[8];
		double* fRec64 = &fRec64_tmp[4];
		double fRec63_tmp[8];
		double* fRec63 = &fRec63_tmp[4];
		double fRec62_tmp[8];
		double* fRec62 = &fRec62_tmp[4];
		double fRec61_tmp[8];
		double* fRec61 = &fRec61_tmp[4];
		double fRec74_tmp[8];
		double* fRec74 = &fRec74_tmp[4];
		double fRec73_tmp[8];
		double* fRec73 = &fRec73_tmp[4];
		double fRec72_tmp[8];
		double* fRec72 = &fRec72_tmp[4];
		double fZec111[4];
		double fRec71_tmp[8];
		double* fRec71 = &fRec71_tmp[4];
		double fRec70_tmp[8];
		double* fRec70 = &fRec70_tmp[4];
		double fRec69_tmp[8];
		double* fRec69 = &fRec69_tmp[4];
		double fRec68_tmp[8];
		double* fRec68 = &fRec68_tmp[4];
		double fRec81_tmp[8];
		double* fRec81 = &fRec81_tmp[4];
		double fRec80_tmp[8];
		double* fRec80 = &fRec80_tmp[4];
		double fRec79_tmp[8];
		double* fRec79 = &fRec79_tmp[4];
		double fZec112[4];
		double fRec78_tmp[8];
		double* fRec78 = &fRec78_tmp[4];
		double fRec77_tmp[8];
		double* fRec77 = &fRec77_tmp[4];
		double fRec76_tmp[8];
		double* fRec76 = &fRec76_tmp[4];
		double fRec75_tmp[8];
		double* fRec75 = &fRec75_tmp[4];
		double fRec88_tmp[8];
		double* fRec88 = &fRec88_tmp[4];
		double fRec87_tmp[8];
		double* fRec87 = &fRec87_tmp[4];
		double fRec86_tmp[8];
		double* fRec86 = &fRec86_tmp[4];
		double fZec113[4];
		double fRec85_tmp[8];
		double* fRec85 = &fRec85_tmp[4];
		double fRec84_tmp[8];
		double* fRec84 = &fRec84_tmp[4];
		double fRec83_tmp[8];
		double* fRec83 = &fRec83_tmp[4];
		double fRec82_tmp[8];
		double* fRec82 = &fRec82_tmp[4];
		double fRec95_tmp[8];
		double* fRec95 = &fRec95_tmp[4];
		double fRec94_tmp[8];
		double* fRec94 = &fRec94_tmp[4];
		double fRec93_tmp[8];
		double* fRec93 = &fRec93_tmp[4];
		double fZec114[4];
		double fRec92_tmp[8];
		double* fRec92 = &fRec92_tmp[4];
		double fRec91_tmp[8];
		double* fRec91 = &fRec91_tmp[4];
		double fRec90_tmp[8];
		double* fRec90 = &fRec90_tmp[4];
		double fRec89_tmp[8];
		double* fRec89 = &fRec89_tmp[4];
		double fRec102_tmp[8];
		double* fRec102 = &fRec102_tmp[4];
		double fRec101_tmp[8];
		double* fRec101 = &fRec101_tmp[4];
		double fRec100_tmp[8];
		double* fRec100 = &fRec100_tmp[4];
		double fZec115[4];
		double fRec99_tmp[8];
		double* fRec99 = &fRec99_tmp[4];
		double fRec98_tmp[8];
		double* fRec98 = &fRec98_tmp[4];
		double fRec97_tmp[8];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[8];
		double* fRec96 = &fRec96_tmp[4];
		double fRec109_tmp[8];
		double* fRec109 = &fRec109_tmp[4];
		double fRec108_tmp[8];
		double* fRec108 = &fRec108_tmp[4];
		double fRec107_tmp[8];
		double* fRec107 = &fRec107_tmp[4];
		double fZec116[4];
		double fRec106_tmp[8];
		double* fRec106 = &fRec106_tmp[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[8];
		double* fRec104 = &fRec104_tmp[4];
		double fRec103_tmp[8];
		double* fRec103 = &fRec103_tmp[4];
		double fRec116_tmp[8];
		double* fRec116 = &fRec116_tmp[4];
		double fRec115_tmp[8];
		double* fRec115 = &fRec115_tmp[4];
		double fRec114_tmp[8];
		double* fRec114 = &fRec114_tmp[4];
		double fZec117[4];
		double fRec113_tmp[8];
		double* fRec113 = &fRec113_tmp[4];
		double fRec112_tmp[8];
		double* fRec112 = &fRec112_tmp[4];
		double fRec111_tmp[8];
		double* fRec111 = &fRec111_tmp[4];
		double fRec110_tmp[8];
		double* fRec110 = &fRec110_tmp[4];
		double fRec123_tmp[8];
		double* fRec123 = &fRec123_tmp[4];
		double fRec122_tmp[8];
		double* fRec122 = &fRec122_tmp[4];
		double fRec121_tmp[8];
		double* fRec121 = &fRec121_tmp[4];
		double fZec118[4];
		double fRec120_tmp[8];
		double* fRec120 = &fRec120_tmp[4];
		double fRec119_tmp[8];
		double* fRec119 = &fRec119_tmp[4];
		double fRec118_tmp[8];
		double* fRec118 = &fRec118_tmp[4];
		double fRec117_tmp[8];
		double* fRec117 = &fRec117_tmp[4];
		double fRec127_tmp[8];
		double* fRec127 = &fRec127_tmp[4];
		double fRec126_tmp[8];
		double* fRec126 = &fRec126_tmp[4];
		double fRec125_tmp[8];
		double* fRec125 = &fRec125_tmp[4];
		double fRec124_tmp[8];
		double* fRec124 = &fRec124_tmp[4];
		double fSlow41 = static_cast<double>(fHslider6);
		double fZec119[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec6_tmp[j2] = fRec6_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fSlow1 + 0.999 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec6_perm[j3] = fRec6_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec7_tmp[j4] = fRec7_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fSlow2 + 0.999 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec7_perm[j5] = fRec7_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec9_tmp[j6] = fRec9_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fRec9[faust_wrap_sub(i, 1)] * fSlow4 + fSlow5;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec9_perm[j7] = fRec9_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec9[i]));
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec8_tmp[j8] = fRec8_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec8[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec8[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec8_perm[j9] = fRec8_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fSlow6 * fRec9[i];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = std::max<double>(2e+01, std::fabs(fZec2[i]));
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec10_tmp[j10] = fRec10_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fRec10[faust_wrap_sub(i, 1)] + fConst1 * fZec3[i];
				fRec10[i] = fZec4[i] - std::floor(fZec4[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec10_perm[j11] = fRec10_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fSlow7 * fRec9[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = std::max<double>(2e+01, std::fabs(fZec5[i]));
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec11_tmp[j12] = fRec11_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fRec11[faust_wrap_sub(i, 1)] + fConst1 * fZec6[i];
				fRec11[i] = fZec7[i] - std::floor(fZec7[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec11_perm[j13] = fRec11_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = std::max<double>(fRec9[i], 23.44894968246214);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = std::max<double>(2e+01, std::fabs(fZec8[i]));
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec12_tmp[j14] = fRec12_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fRec12[faust_wrap_sub(i, 1)] + fConst1 * fZec9[i];
				fRec12[i] = fZec10[i] - std::floor(fZec10[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec12_perm[j15] = fRec12_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = std::max<double>(fZec2[i], 23.44894968246214);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = std::max<double>(2e+01, std::fabs(fZec11[i]));
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec13_tmp[j16] = fRec13_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = fRec13[faust_wrap_sub(i, 1)] + fConst1 * fZec12[i];
				fRec13[i] = fZec13[i] - std::floor(fZec13[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec13_perm[j17] = fRec13_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = std::max<double>(fZec5[i], 23.44894968246214);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = std::max<double>(2e+01, std::fabs(fZec14[i]));
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec14_tmp[j18] = fRec14_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fRec14[faust_wrap_sub(i, 1)] + fConst1 * fZec15[i];
				fRec14[i] = fZec16[i] - std::floor(fZec16[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec14_perm[j19] = fRec14_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				iVec0_tmp[j20] = iVec0_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				iVec0_perm[j21] = iVec0_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = 2.0 * fRec12[i];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fZec18[i] + -1.0;
			}
			/* Vectorizable loop 25 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fYec0_tmp[j22] = fYec0_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = mydsp_faustpower2_f(fZec19[i]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fYec0_perm[j23] = fYec0_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 4095] = fZec17[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec9[i];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst3 / fZec8[i]));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec21[i] = static_cast<int>(fZec20[i]);
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = static_cast<double>(iZec21[i]);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fYec1[(faust_wrap_add(i, fYec1_idx)) & 4095] - fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec21[i])) & 4095] * (fZec22[i] + (1.0 - fZec20[i])) - (fZec20[i] - fZec22[i]) * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), faust_wrap_add(iZec21[i], 1))) & 4095];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec15_tmp[j24] = fRec15_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fConst2 * fZec23[i] + 0.999 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec15_perm[j25] = fRec15_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = 2.0 * fRec13[i];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = fZec24[i] + -1.0;
			}
			/* Vectorizable loop 34 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fYec2_tmp[j26] = fYec2_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[i] = mydsp_faustpower2_f(fZec25[i]);
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fYec2_perm[j27] = fYec2_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] = fZec17[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec12[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst3 / fZec11[i]));
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec27[i] = static_cast<int>(fZec26[i]);
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = static_cast<double>(iZec27[i]);
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] - fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iZec27[i])) & 4095] * (fZec28[i] + (1.0 - fZec26[i])) - (fZec26[i] - fZec28[i]) * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), faust_wrap_add(iZec27[i], 1))) & 4095];
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec16_tmp[j28] = fRec16_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = fConst2 * fZec29[i] + 0.999 * fRec16[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec16_perm[j29] = fRec16_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = 2.0 * fRec14[i];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fZec30[i] + -1.0;
			}
			/* Vectorizable loop 43 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fYec4_tmp[j30] = fYec4_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[i] = mydsp_faustpower2_f(fZec31[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fYec4_perm[j31] = fYec4_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 44 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 4095] = fZec17[i] * (fYec4[i] - fYec4[faust_wrap_sub(i, 1)]) / fZec15[i];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst3 / fZec14[i]));
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec33[i] = static_cast<int>(fZec32[i]);
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = static_cast<double>(iZec33[i]);
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = fYec5[(faust_wrap_add(i, fYec5_idx)) & 4095] - fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iZec33[i])) & 4095] * (fZec34[i] + (1.0 - fZec32[i])) - (fZec32[i] - fZec34[i]) * fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), faust_wrap_add(iZec33[i], 1))) & 4095];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec17_tmp[j32] = fRec17_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fConst2 * fZec35[i] + 0.999 * fRec17[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec17_perm[j33] = fRec17_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec18_tmp[j34] = fRec18_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fSlow8 + 0.99 * fRec18[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec18_perm[j35] = fRec18_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 51 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				iRec20_tmp[j36] = iRec20_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec20[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec20[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				iRec20_perm[j37] = iRec20_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec19_tmp[j38] = fRec19_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = 0.5221894 * fRec19[faust_wrap_sub(i, 3)] + 4.656612875245797e-10 * static_cast<double>(iRec20[i]) + 2.494956002 * fRec19[faust_wrap_sub(i, 1)] - 2.017265875 * fRec19[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec19_perm[j39] = fRec19_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec36[i] = fConst4 * fRec6[i];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec37[i] = 1.0 - fZec36[i];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec38[i] = 2.0 * fRec8[i];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec39[i] = fZec38[i] + -1.0;
			}
			/* Vectorizable loop 57 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fYec6_tmp[j40] = fYec6_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[i] = mydsp_faustpower2_f(fZec39[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fYec6_perm[j41] = fYec6_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec40[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 2)]);
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = mydsp_faustpower3_f(fZec39[i]);
			}
			/* Vectorizable loop 60 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fYec7_tmp[j42] = fYec7_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[i] = fZec41[i] + (1.0 - fZec38[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fYec7_perm[j43] = fYec7_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 61 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec8_tmp[j44] = fYec8_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[i] = (fZec41[i] + (1.0 - (fZec38[i] + fYec7[faust_wrap_sub(i, 1)]))) / fZec0[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec8_perm[j45] = fYec8_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 3)]);
			}
			/* Vectorizable loop 63 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fYec9_tmp[j46] = fYec9_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fYec9_perm[j47] = fYec9_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Vectorizable loop 64 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fYec10_tmp[j48] = fYec10_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[i] = (fYec9[i] - fYec9[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fYec10_perm[j49] = fYec10_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 65 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fYec11_tmp[j50] = fYec11_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[i] = (fYec10[i] - fYec10[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fYec11_perm[j51] = fYec11_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = 2.0 * fRec10[i];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec44[i] = fZec43[i] + -1.0;
			}
			/* Vectorizable loop 68 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec12_tmp[j52] = fYec12_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[i] = mydsp_faustpower2_f(fZec44[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec12_perm[j53] = fYec12_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec45[i] = mydsp_faustpower3_f(fZec44[i]);
			}
			/* Vectorizable loop 70 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fYec13_tmp[j54] = fYec13_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[i] = fZec45[i] + (1.0 - fZec43[i]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fYec13_perm[j55] = fYec13_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 71 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fYec14_tmp[j56] = fYec14_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[i] = (fZec45[i] + (1.0 - (fZec43[i] + fYec13[faust_wrap_sub(i, 1)]))) / fZec3[i];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fYec14_perm[j57] = fYec14_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 72 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fYec15_tmp[j58] = fYec15_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fYec15_perm[j59] = fYec15_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 73 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fYec16_tmp[j60] = fYec16_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[i] = (fYec15[i] - fYec15[faust_wrap_sub(i, 1)]) / fZec3[i];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fYec16_perm[j61] = fYec16_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Vectorizable loop 74 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fYec17_tmp[j62] = fYec17_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[i] = (fYec16[i] - fYec16[faust_wrap_sub(i, 1)]) / fZec3[i];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fYec17_perm[j63] = fYec17_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec46[i] = 2.0 * fRec11[i];
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec47[i] = fZec46[i] + -1.0;
			}
			/* Vectorizable loop 77 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fYec18_tmp[j64] = fYec18_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[i] = mydsp_faustpower2_f(fZec47[i]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fYec18_perm[j65] = fYec18_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 78 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec48[i] = mydsp_faustpower3_f(fZec47[i]);
			}
			/* Vectorizable loop 79 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fYec19_tmp[j66] = fYec19_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[i] = fZec48[i] + (1.0 - fZec46[i]);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fYec19_perm[j67] = fYec19_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 80 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fYec20_tmp[j68] = fYec20_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[i] = (fZec48[i] + (1.0 - (fZec46[i] + fYec19[faust_wrap_sub(i, 1)]))) / fZec6[i];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fYec20_perm[j69] = fYec20_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 81 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fYec21_tmp[j70] = fYec21_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[i] = fYec18[i] * (fYec18[i] + -2.0);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fYec21_perm[j71] = fYec21_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 82 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fYec22_tmp[j72] = fYec22_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[i] = (fYec21[i] - fYec21[faust_wrap_sub(i, 1)]) / fZec6[i];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fYec22_perm[j73] = fYec22_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 83 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fYec23_tmp[j74] = fYec23_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[i] = (fYec22[i] - fYec22[faust_wrap_sub(i, 1)]) / fZec6[i];
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fYec23_perm[j75] = fYec23_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 84 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec49[i] = mydsp_faustpower3_f(fZec19[i]);
			}
			/* Vectorizable loop 85 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fYec24_tmp[j76] = fYec24_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec24[i] = fZec49[i] + (1.0 - fZec18[i]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fYec24_perm[j77] = fYec24_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Vectorizable loop 86 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fYec25_tmp[j78] = fYec25_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec25[i] = (fZec49[i] + (1.0 - (fZec18[i] + fYec24[faust_wrap_sub(i, 1)]))) / fZec9[i];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fYec25_perm[j79] = fYec25_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 87 */
			/* Pre code */
			fYec26_idx = (faust_wrap_add(fYec26_idx, fYec26_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec26[(faust_wrap_add(i, fYec26_idx)) & 4095] = fZec40[i] * (fYec25[i] - fYec25[faust_wrap_sub(i, 1)]) / fZec9[i];
			}
			/* Post code */
			fYec26_idx_save = vsize;
			/* Vectorizable loop 88 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec50[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst0 * (fRec18[i] / fZec8[i])));
			}
			/* Vectorizable loop 89 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec51[i] = static_cast<int>(fZec50[i]);
			}
			/* Vectorizable loop 90 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec52[i] = static_cast<double>(iZec51[i]);
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec53[i] = fZec52[i] + (1.0 - fZec50[i]);
			}
			/* Vectorizable loop 92 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec54[i] = fZec50[i] - fZec52[i];
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec55[i] = faust_wrap_add(iZec51[i], 1);
			}
			/* Vectorizable loop 94 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec56[i] = mydsp_faustpower3_f(fZec25[i]);
			}
			/* Vectorizable loop 95 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fYec27_tmp[j80] = fYec27_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec27[i] = fZec56[i] + (1.0 - fZec24[i]);
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fYec27_perm[j81] = fYec27_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Vectorizable loop 96 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fYec28_tmp[j82] = fYec28_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec28[i] = (fZec56[i] + (1.0 - (fZec24[i] + fYec27[faust_wrap_sub(i, 1)]))) / fZec12[i];
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fYec28_perm[j83] = fYec28_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 97 */
			/* Pre code */
			fYec29_idx = (faust_wrap_add(fYec29_idx, fYec29_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec29[(faust_wrap_add(i, fYec29_idx)) & 4095] = fZec40[i] * (fYec28[i] - fYec28[faust_wrap_sub(i, 1)]) / fZec12[i];
			}
			/* Post code */
			fYec29_idx_save = vsize;
			/* Vectorizable loop 98 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec57[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst0 * (fRec18[i] / fZec11[i])));
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec58[i] = static_cast<int>(fZec57[i]);
			}
			/* Vectorizable loop 100 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec59[i] = static_cast<double>(iZec58[i]);
			}
			/* Vectorizable loop 101 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec60[i] = fZec59[i] + (1.0 - fZec57[i]);
			}
			/* Vectorizable loop 102 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec61[i] = fZec57[i] - fZec59[i];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec62[i] = faust_wrap_add(iZec58[i], 1);
			}
			/* Vectorizable loop 104 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec63[i] = mydsp_faustpower3_f(fZec31[i]);
			}
			/* Vectorizable loop 105 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fYec30_tmp[j84] = fYec30_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec30[i] = fZec63[i] + (1.0 - fZec30[i]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fYec30_perm[j85] = fYec30_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Vectorizable loop 106 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fYec31_tmp[j86] = fYec31_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec31[i] = (fZec63[i] + (1.0 - (fZec30[i] + fYec30[faust_wrap_sub(i, 1)]))) / fZec15[i];
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fYec31_perm[j87] = fYec31_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 107 */
			/* Pre code */
			fYec32_idx = (faust_wrap_add(fYec32_idx, fYec32_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec32[(faust_wrap_add(i, fYec32_idx)) & 4095] = fZec40[i] * (fYec31[i] - fYec31[faust_wrap_sub(i, 1)]) / fZec15[i];
			}
			/* Post code */
			fYec32_idx_save = vsize;
			/* Vectorizable loop 108 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec64[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst0 * (fRec18[i] / fZec14[i])));
			}
			/* Vectorizable loop 109 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec65[i] = static_cast<int>(fZec64[i]);
			}
			/* Vectorizable loop 110 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec66[i] = static_cast<double>(iZec65[i]);
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec67[i] = fZec66[i] + (1.0 - fZec64[i]);
			}
			/* Vectorizable loop 112 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec68[i] = fZec64[i] - fZec66[i];
			}
			/* Vectorizable loop 113 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec69[i] = faust_wrap_add(iZec65[i], 1);
			}
			/* Vectorizable loop 114 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec70[i] = fSlow10 * static_cast<double>(input0[i]) + fRec7[i] * (fSlow11 * (((iSlow13) ? ((iSlow15) ? fConst6 * (fZec42[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst5 * (fZec40[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow14) ? fConst2 * (fZec17[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec39[i])) + ((iSlow13) ? ((iSlow15) ? fConst6 * (fZec42[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec3[i]) : fConst5 * (fZec40[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec3[i])) : ((iSlow14) ? fConst2 * (fZec17[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec3[i]) : fZec44[i])) + ((iSlow13) ? ((iSlow15) ? fConst6 * (fZec42[i] * (fYec23[i] - fYec23[faust_wrap_sub(i, 1)]) / fZec6[i]) : fConst5 * (fZec40[i] * (fYec20[i] - fYec20[faust_wrap_sub(i, 1)]) / fZec6[i])) : ((iSlow14) ? fConst2 * (fZec17[i] * (fYec18[i] - fYec18[faust_wrap_sub(i, 1)]) / fZec6[i]) : fZec47[i]))) + fSlow16 * (fZec23[i] + fZec29[i] + fZec35[i]) + fSlow17 * fRec9[i] * (fRec15[i] + fSlow6 * fRec16[i] + fSlow7 * fRec17[i]) + fSlow18 * (fSlow20 * (fYec26[(faust_wrap_add(i, fYec26_idx)) & 4095] - fYec26[(faust_wrap_sub(faust_wrap_add(i, fYec26_idx), iZec51[i])) & 4095] * fZec53[i] - fZec54[i] * fYec26[(faust_wrap_sub(faust_wrap_add(i, fYec26_idx), iZec55[i])) & 4095] + (fYec29[(faust_wrap_add(i, fYec29_idx)) & 4095] - fYec29[(faust_wrap_sub(faust_wrap_add(i, fYec29_idx), iZec58[i])) & 4095] * fZec60[i] - fZec61[i] * fYec29[(faust_wrap_sub(faust_wrap_add(i, fYec29_idx), iZec62[i])) & 4095]) + (fYec32[(faust_wrap_add(i, fYec32_idx)) & 4095] - fYec32[(faust_wrap_sub(faust_wrap_add(i, fYec32_idx), iZec65[i])) & 4095] * fZec67[i] - fZec68[i] * fYec32[(faust_wrap_sub(faust_wrap_add(i, fYec32_idx), iZec69[i])) & 4095])) + fSlow21 * (fYec1[(faust_wrap_add(i, fYec1_idx)) & 4095] - fZec53[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec51[i])) & 4095] - fZec54[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec55[i])) & 4095] + (fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] - fZec60[i] * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iZec58[i])) & 4095] - fZec61[i] * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iZec62[i])) & 4095]) + (fYec5[(faust_wrap_add(i, fYec5_idx)) & 4095] - fZec67[i] * fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iZec65[i])) & 4095] - fZec68[i] * fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iZec69[i])) & 4095]))) + fSlow22 * (0.049922035 * fRec19[i] + 0.050612699 * fRec19[faust_wrap_sub(i, 2)] - (0.095993537 * fRec19[faust_wrap_sub(i, 1)] + 0.004408786 * fRec19[faust_wrap_sub(i, 3)])));
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec71[i] = ((iSlow9) ? 0.0 : fZec70[i]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec5_tmp[j88] = fRec5_perm[j88];
			}
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec4_tmp[j90] = fRec4_perm[j90];
			}
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec3_tmp[j92] = fRec3_perm[j92];
			}
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec2_tmp[j94] = fRec2_perm[j94];
			}
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec1_tmp[j96] = fRec1_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fZec37[i] * fRec5[faust_wrap_sub(i, 1)] + fZec71[i] - fSlow24 * fRec1[faust_wrap_sub(i, 1)];
				fRec4[i] = fRec5[i] + fZec37[i] * fRec4[faust_wrap_sub(i, 1)];
				fRec3[i] = fRec4[i] + fZec37[i] * fRec3[faust_wrap_sub(i, 1)];
				fRec2[i] = fRec3[i] + fRec2[faust_wrap_sub(i, 1)] * fZec37[i];
				fRec1[i] = fRec2[i] * mydsp_faustpower4_f(fZec36[i]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec5_perm[j89] = fRec5_tmp[faust_wrap_add(vsize, j89)];
			}
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec4_perm[j91] = fRec4_tmp[faust_wrap_add(vsize, j91)];
			}
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec3_perm[j93] = fRec3_tmp[faust_wrap_add(vsize, j93)];
			}
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec2_perm[j95] = fRec2_tmp[faust_wrap_add(vsize, j95)];
			}
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec1_perm[j97] = fRec1_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 117 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec72[i] = std::tan(fConst10 * std::max<double>(2e+01, std::min<double>(1e+04, fRec6[i])));
			}
			/* Vectorizable loop 118 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec73[i] = 1.0 / fZec72[i];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec74[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec72[i]);
			}
			/* Vectorizable loop 120 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec75[i] = fSlow28 + (fSlow29 + fZec73[i]) / fZec72[i] + 1.0;
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec22_tmp[j98] = fRec22_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fZec71[i] - (fRec22[faust_wrap_sub(i, 2)] * (fSlow28 + (fZec73[i] - fSlow29) / fZec72[i] + 1.0) + 2.0 * fRec22[faust_wrap_sub(i, 1)] * (fSlow28 + fZec74[i])) / fZec75[i];
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec22_perm[j99] = fRec22_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Vectorizable loop 122 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec76[i] = fSlow27 + ((fSlow30 + fZec73[i]) / fZec72[i] + 1.0 - fSlow26);
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec21_tmp[j100] = fRec21_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = (fRec22[faust_wrap_sub(i, 2)] + fRec22[i] + 2.0 * fRec22[faust_wrap_sub(i, 1)]) / fZec75[i] - (fRec21[faust_wrap_sub(i, 2)] * (fSlow27 + ((fZec73[i] - fSlow30) / fZec72[i] + 1.0 - fSlow26)) + 2.0 * fRec21[faust_wrap_sub(i, 1)] * (fSlow27 + (fZec74[i] - fSlow26))) / fZec76[i];
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec21_perm[j101] = fRec21_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Vectorizable loop 124 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec77[i] = std::tan(fConst10 * std::max<double>(fRec6[i], 2e+01));
			}
			/* Vectorizable loop 125 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec78[i] = 1.0 / fZec77[i];
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec79[i] = fSlow33 + (fSlow34 + fZec78[i]) / fZec77[i] + 1.0;
			}
			/* Vectorizable loop 127 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec85[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec77[i]);
			}
			/* Vectorizable loop 128 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec80[i] = (fSlow33 + (1.0 - (fSlow34 - fZec78[i]) / fZec77[i])) / fZec79[i];
			}
			/* Vectorizable loop 129 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec81[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec80[i]));
			}
			/* Vectorizable loop 130 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec82[i] = 1.0 - mydsp_faustpower2_f(fZec81[i]);
			}
			/* Vectorizable loop 131 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec83[i] = std::sqrt(std::max<double>(0.0, fZec82[i]));
			}
			/* Vectorizable loop 132 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec86[i] = fSlow33 + fZec85[i];
			}
			/* Vectorizable loop 133 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec87[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec86[i] / (fZec79[i] * (fZec80[i] + 1.0)))));
			}
			/* Vectorizable loop 134 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec88[i] = 1.0 - mydsp_faustpower2_f(fZec87[i]);
			}
			/* Vectorizable loop 135 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec89[i] = std::sqrt(std::max<double>(0.0, fZec88[i]));
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec25_tmp[j102] = fRec25_perm[j102];
			}
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec23_tmp[j104] = fRec23_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec84[i] = fZec71[i] * fZec83[i] - fZec81[i] * fRec23[faust_wrap_sub(i, 1)];
				fRec25[i] = fZec84[i] * fZec89[i] - fZec87[i] * fRec25[faust_wrap_sub(i, 1)];
				fRec23[i] = fZec84[i] * fZec87[i] + fRec25[faust_wrap_sub(i, 1)] * fZec89[i];
				fRec24[i] = fRec25[i];
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec25_perm[j103] = fRec25_tmp[faust_wrap_add(vsize, j103)];
			}
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec23_perm[j105] = fRec23_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Vectorizable loop 137 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec90[i] = 1.0 - fZec86[i] / fZec79[i];
			}
			/* Vectorizable loop 138 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec91[i] = std::sqrt(fZec82[i]);
			}
			/* Vectorizable loop 139 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec92[i] = fZec71[i] * fZec81[i] + fRec23[faust_wrap_sub(i, 1)] * fZec83[i] + 2.0 * (fRec23[i] * fZec90[i] / fZec91[i]) + fRec24[i] * (1.0 - fZec80[i] - 2.0 * fZec87[i] * fZec90[i]) / (fZec91[i] * std::sqrt(fZec88[i]));
			}
			/* Vectorizable loop 140 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec93[i] = fSlow31 + ((fSlow35 + fZec78[i]) / fZec77[i] + 1.0 - fSlow32);
			}
			/* Vectorizable loop 141 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec94[i] = (fSlow31 + ((fZec78[i] - fSlow35) / fZec77[i] + 1.0 - fSlow32)) / fZec93[i];
			}
			/* Vectorizable loop 142 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec95[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec94[i]));
			}
			/* Vectorizable loop 143 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec96[i] = 1.0 - mydsp_faustpower2_f(fZec95[i]);
			}
			/* Vectorizable loop 144 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec97[i] = std::sqrt(std::max<double>(0.0, fZec96[i]));
			}
			/* Vectorizable loop 145 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec99[i] = fSlow31 + (fZec85[i] - fSlow32);
			}
			/* Vectorizable loop 146 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec100[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec99[i] / (fZec93[i] * (fZec94[i] + 1.0)))));
			}
			/* Vectorizable loop 147 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec101[i] = 1.0 - mydsp_faustpower2_f(fZec100[i]);
			}
			/* Vectorizable loop 148 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec102[i] = std::sqrt(std::max<double>(0.0, fZec101[i]));
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec28_tmp[j106] = fRec28_perm[j106];
			}
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec26_tmp[j108] = fRec26_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec98[i] = fZec92[i] * fZec97[i] / fZec79[i] - fZec95[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec28[i] = fZec98[i] * fZec102[i] - fZec100[i] * fRec28[faust_wrap_sub(i, 1)];
				fRec26[i] = fZec98[i] * fZec100[i] + fRec28[faust_wrap_sub(i, 1)] * fZec102[i];
				fRec27[i] = fRec28[i];
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec28_perm[j107] = fRec28_tmp[faust_wrap_add(vsize, j107)];
			}
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec26_perm[j109] = fRec26_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Vectorizable loop 150 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec103[i] = 1.0 - fZec99[i] / fZec93[i];
			}
			/* Vectorizable loop 151 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec104[i] = std::sqrt(fZec96[i]);
			}
			/* Vectorizable loop 152 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec105[i] = ((iSlow9) ? fZec70[i] : fRec0[i] * ((iSlow36) ? ((iSlow37) ? (fZec92[i] * fZec95[i] / fZec79[i] + fRec26[faust_wrap_sub(i, 1)] * fZec97[i] + 2.0 * (fRec26[i] * fZec103[i] / fZec104[i]) + fRec27[i] * (1.0 - fZec94[i] - 2.0 * fZec100[i] * fZec103[i]) / (fZec104[i] * std::sqrt(fZec101[i]))) / fZec93[i] : (fRec21[faust_wrap_sub(i, 2)] + fRec21[i] + 2.0 * fRec21[faust_wrap_sub(i, 1)]) / fZec76[i]) : fRec1[i]));
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec39_tmp[j118] = fRec39_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fZec105[i] - fConst34 * (fConst35 * fRec39[faust_wrap_sub(i, 2)] + fConst36 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec39_perm[j119] = fRec39_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec38_tmp[j120] = fRec38_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fConst34 * (fConst38 * fRec39[i] + fConst39 * fRec39[faust_wrap_sub(i, 1)] + fConst38 * fRec39[faust_wrap_sub(i, 2)]) - fConst40 * (fConst41 * fRec38[faust_wrap_sub(i, 2)] + fConst42 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec38_perm[j121] = fRec38_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec37_tmp[j122] = fRec37_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst40 * (fConst43 * fRec38[i] + fConst44 * fRec38[faust_wrap_sub(i, 1)] + fConst43 * fRec38[faust_wrap_sub(i, 2)]) - fConst45 * (fConst46 * fRec37[faust_wrap_sub(i, 2)] + fConst47 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec37_perm[j123] = fRec37_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Vectorizable loop 156 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec106[i] = fConst45 * (fConst48 * fRec37[i] + fConst49 * fRec37[faust_wrap_sub(i, 1)] + fConst48 * fRec37[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec46_tmp[j132] = fRec46_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fZec106[i] - fConst72 * (fConst73 * fRec46[faust_wrap_sub(i, 2)] + fConst74 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec46_perm[j133] = fRec46_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec45_tmp[j134] = fRec45_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fConst72 * (fConst76 * fRec46[i] + fConst77 * fRec46[faust_wrap_sub(i, 1)] + fConst76 * fRec46[faust_wrap_sub(i, 2)]) - fConst78 * (fConst79 * fRec45[faust_wrap_sub(i, 2)] + fConst80 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec45_perm[j135] = fRec45_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec44_tmp[j136] = fRec44_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst78 * (fConst81 * fRec45[i] + fConst82 * fRec45[faust_wrap_sub(i, 1)] + fConst81 * fRec45[faust_wrap_sub(i, 2)]) - fConst83 * (fConst84 * fRec44[faust_wrap_sub(i, 2)] + fConst85 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec44_perm[j137] = fRec44_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Vectorizable loop 160 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec107[i] = fConst83 * (fConst86 * fRec44[i] + fConst87 * fRec44[faust_wrap_sub(i, 1)] + fConst86 * fRec44[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec53_tmp[j146] = fRec53_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fZec107[i] - fConst110 * (fConst111 * fRec53[faust_wrap_sub(i, 2)] + fConst112 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec53_perm[j147] = fRec53_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec52_tmp[j148] = fRec52_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fConst110 * (fConst114 * fRec53[i] + fConst115 * fRec53[faust_wrap_sub(i, 1)] + fConst114 * fRec53[faust_wrap_sub(i, 2)]) - fConst116 * (fConst117 * fRec52[faust_wrap_sub(i, 2)] + fConst118 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec52_perm[j149] = fRec52_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec51_tmp[j150] = fRec51_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst116 * (fConst119 * fRec52[i] + fConst120 * fRec52[faust_wrap_sub(i, 1)] + fConst119 * fRec52[faust_wrap_sub(i, 2)]) - fConst121 * (fConst122 * fRec51[faust_wrap_sub(i, 2)] + fConst123 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec51_perm[j151] = fRec51_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Vectorizable loop 164 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec108[i] = fConst121 * (fConst124 * fRec51[i] + fConst125 * fRec51[faust_wrap_sub(i, 1)] + fConst124 * fRec51[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec60_tmp[j160] = fRec60_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fZec108[i] - fConst148 * (fConst149 * fRec60[faust_wrap_sub(i, 2)] + fConst150 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec60_perm[j161] = fRec60_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec59_tmp[j162] = fRec59_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fConst148 * (fConst152 * fRec60[i] + fConst153 * fRec60[faust_wrap_sub(i, 1)] + fConst152 * fRec60[faust_wrap_sub(i, 2)]) - fConst154 * (fConst155 * fRec59[faust_wrap_sub(i, 2)] + fConst156 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec59_perm[j163] = fRec59_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec58_tmp[j164] = fRec58_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst154 * (fConst157 * fRec59[i] + fConst158 * fRec59[faust_wrap_sub(i, 1)] + fConst157 * fRec59[faust_wrap_sub(i, 2)]) - fConst159 * (fConst160 * fRec58[faust_wrap_sub(i, 2)] + fConst161 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec58_perm[j165] = fRec58_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Vectorizable loop 168 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec109[i] = fConst159 * (fConst162 * fRec58[i] + fConst163 * fRec58[faust_wrap_sub(i, 1)] + fConst162 * fRec58[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec67_tmp[j174] = fRec67_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fZec109[i] - fConst186 * (fConst187 * fRec67[faust_wrap_sub(i, 2)] + fConst188 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec67_perm[j175] = fRec67_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec66_tmp[j176] = fRec66_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fConst186 * (fConst190 * fRec67[i] + fConst191 * fRec67[faust_wrap_sub(i, 1)] + fConst190 * fRec67[faust_wrap_sub(i, 2)]) - fConst192 * (fConst193 * fRec66[faust_wrap_sub(i, 2)] + fConst194 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec66_perm[j177] = fRec66_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec65_tmp[j178] = fRec65_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst192 * (fConst195 * fRec66[i] + fConst196 * fRec66[faust_wrap_sub(i, 1)] + fConst195 * fRec66[faust_wrap_sub(i, 2)]) - fConst197 * (fConst198 * fRec65[faust_wrap_sub(i, 2)] + fConst199 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec65_perm[j179] = fRec65_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Vectorizable loop 172 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec110[i] = fConst197 * (fConst200 * fRec65[i] + fConst201 * fRec65[faust_wrap_sub(i, 1)] + fConst200 * fRec65[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec74_tmp[j188] = fRec74_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fZec110[i] - fConst224 * (fConst225 * fRec74[faust_wrap_sub(i, 2)] + fConst226 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec74_perm[j189] = fRec74_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec73_tmp[j190] = fRec73_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fConst224 * (fConst228 * fRec74[i] + fConst229 * fRec74[faust_wrap_sub(i, 1)] + fConst228 * fRec74[faust_wrap_sub(i, 2)]) - fConst230 * (fConst231 * fRec73[faust_wrap_sub(i, 2)] + fConst232 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec73_perm[j191] = fRec73_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec72_tmp[j192] = fRec72_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst230 * (fConst233 * fRec73[i] + fConst234 * fRec73[faust_wrap_sub(i, 1)] + fConst233 * fRec73[faust_wrap_sub(i, 2)]) - fConst235 * (fConst236 * fRec72[faust_wrap_sub(i, 2)] + fConst237 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec72_perm[j193] = fRec72_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Vectorizable loop 176 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec111[i] = fConst235 * (fConst238 * fRec72[i] + fConst239 * fRec72[faust_wrap_sub(i, 1)] + fConst238 * fRec72[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec81_tmp[j202] = fRec81_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fZec111[i] - fConst262 * (fConst263 * fRec81[faust_wrap_sub(i, 2)] + fConst264 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec81_perm[j203] = fRec81_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec80_tmp[j204] = fRec80_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fConst262 * (fConst266 * fRec81[i] + fConst267 * fRec81[faust_wrap_sub(i, 1)] + fConst266 * fRec81[faust_wrap_sub(i, 2)]) - fConst268 * (fConst269 * fRec80[faust_wrap_sub(i, 2)] + fConst270 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec80_perm[j205] = fRec80_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec79_tmp[j206] = fRec79_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst268 * (fConst271 * fRec80[i] + fConst272 * fRec80[faust_wrap_sub(i, 1)] + fConst271 * fRec80[faust_wrap_sub(i, 2)]) - fConst273 * (fConst274 * fRec79[faust_wrap_sub(i, 2)] + fConst275 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec79_perm[j207] = fRec79_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Vectorizable loop 180 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec112[i] = fConst273 * (fConst276 * fRec79[i] + fConst277 * fRec79[faust_wrap_sub(i, 1)] + fConst276 * fRec79[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec88_tmp[j216] = fRec88_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fZec112[i] - fConst300 * (fConst301 * fRec88[faust_wrap_sub(i, 2)] + fConst302 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec88_perm[j217] = fRec88_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec87_tmp[j218] = fRec87_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fConst300 * (fConst304 * fRec88[i] + fConst305 * fRec88[faust_wrap_sub(i, 1)] + fConst304 * fRec88[faust_wrap_sub(i, 2)]) - fConst306 * (fConst307 * fRec87[faust_wrap_sub(i, 2)] + fConst308 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec87_perm[j219] = fRec87_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec86_tmp[j220] = fRec86_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst306 * (fConst309 * fRec87[i] + fConst310 * fRec87[faust_wrap_sub(i, 1)] + fConst309 * fRec87[faust_wrap_sub(i, 2)]) - fConst311 * (fConst312 * fRec86[faust_wrap_sub(i, 2)] + fConst313 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec86_perm[j221] = fRec86_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Vectorizable loop 184 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec113[i] = fConst311 * (fConst314 * fRec86[i] + fConst315 * fRec86[faust_wrap_sub(i, 1)] + fConst314 * fRec86[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec85_tmp[j222] = fRec85_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fZec113[i] - fConst318 * (fConst319 * fRec85[faust_wrap_sub(i, 2)] + fConst322 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec85_perm[j223] = fRec85_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec84_tmp[j224] = fRec84_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fConst318 * (fConst324 * fRec85[i] + fConst325 * fRec85[faust_wrap_sub(i, 1)] + fConst324 * fRec85[faust_wrap_sub(i, 2)]) - fConst326 * (fConst327 * fRec84[faust_wrap_sub(i, 2)] + fConst328 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec84_perm[j225] = fRec84_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec83_tmp[j226] = fRec83_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst326 * (fConst330 * fRec84[i] + fConst331 * fRec84[faust_wrap_sub(i, 1)] + fConst330 * fRec84[faust_wrap_sub(i, 2)]) - fConst332 * (fConst333 * fRec83[faust_wrap_sub(i, 2)] + fConst334 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec83_perm[j227] = fRec83_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec82_tmp[j228] = fRec82_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fSlow39 * fRec82[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst332 * (fConst336 * fRec83[i] + fConst337 * fRec83[faust_wrap_sub(i, 1)] + fConst336 * fRec83[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec82_perm[j229] = fRec82_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec95_tmp[j230] = fRec95_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fZec113[i] - fConst338 * (fConst339 * fRec95[faust_wrap_sub(i, 2)] + fConst340 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec95_perm[j231] = fRec95_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 190 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec94_tmp[j232] = fRec94_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fConst338 * (fConst342 * fRec95[i] + fConst343 * fRec95[faust_wrap_sub(i, 1)] + fConst342 * fRec95[faust_wrap_sub(i, 2)]) - fConst344 * (fConst345 * fRec94[faust_wrap_sub(i, 2)] + fConst346 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec94_perm[j233] = fRec94_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec93_tmp[j234] = fRec93_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst344 * (fConst347 * fRec94[i] + fConst348 * fRec94[faust_wrap_sub(i, 1)] + fConst347 * fRec94[faust_wrap_sub(i, 2)]) - fConst349 * (fConst350 * fRec93[faust_wrap_sub(i, 2)] + fConst351 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec93_perm[j235] = fRec93_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Vectorizable loop 192 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec114[i] = fConst349 * (fConst352 * fRec93[i] + fConst353 * fRec93[faust_wrap_sub(i, 1)] + fConst352 * fRec93[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec92_tmp[j236] = fRec92_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fZec114[i] - fConst356 * (fConst357 * fRec92[faust_wrap_sub(i, 2)] + fConst360 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec92_perm[j237] = fRec92_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec91_tmp[j238] = fRec91_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fConst356 * (fConst362 * fRec92[i] + fConst363 * fRec92[faust_wrap_sub(i, 1)] + fConst362 * fRec92[faust_wrap_sub(i, 2)]) - fConst364 * (fConst365 * fRec91[faust_wrap_sub(i, 2)] + fConst366 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec91_perm[j239] = fRec91_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec90_tmp[j240] = fRec90_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst364 * (fConst368 * fRec91[i] + fConst369 * fRec91[faust_wrap_sub(i, 1)] + fConst368 * fRec91[faust_wrap_sub(i, 2)]) - fConst370 * (fConst371 * fRec90[faust_wrap_sub(i, 2)] + fConst372 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec90_perm[j241] = fRec90_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec89_tmp[j242] = fRec89_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fSlow39 * fRec89[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst370 * (fConst374 * fRec90[i] + fConst375 * fRec90[faust_wrap_sub(i, 1)] + fConst374 * fRec90[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec89_perm[j243] = fRec89_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec102_tmp[j244] = fRec102_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fZec114[i] - fConst376 * (fConst377 * fRec102[faust_wrap_sub(i, 2)] + fConst378 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec102_perm[j245] = fRec102_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 198 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec101_tmp[j246] = fRec101_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fConst376 * (fConst380 * fRec102[i] + fConst381 * fRec102[faust_wrap_sub(i, 1)] + fConst380 * fRec102[faust_wrap_sub(i, 2)]) - fConst382 * (fConst383 * fRec101[faust_wrap_sub(i, 2)] + fConst384 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec101_perm[j247] = fRec101_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec100_tmp[j248] = fRec100_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst382 * (fConst385 * fRec101[i] + fConst386 * fRec101[faust_wrap_sub(i, 1)] + fConst385 * fRec101[faust_wrap_sub(i, 2)]) - fConst387 * (fConst388 * fRec100[faust_wrap_sub(i, 2)] + fConst389 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec100_perm[j249] = fRec100_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Vectorizable loop 200 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec115[i] = fConst387 * (fConst390 * fRec100[i] + fConst391 * fRec100[faust_wrap_sub(i, 1)] + fConst390 * fRec100[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec99_tmp[j250] = fRec99_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fZec115[i] - fConst394 * (fConst395 * fRec99[faust_wrap_sub(i, 2)] + fConst398 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec99_perm[j251] = fRec99_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec98_tmp[j252] = fRec98_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fConst394 * (fConst400 * fRec99[i] + fConst401 * fRec99[faust_wrap_sub(i, 1)] + fConst400 * fRec99[faust_wrap_sub(i, 2)]) - fConst402 * (fConst403 * fRec98[faust_wrap_sub(i, 2)] + fConst404 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec98_perm[j253] = fRec98_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec97_tmp[j254] = fRec97_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst402 * (fConst406 * fRec98[i] + fConst407 * fRec98[faust_wrap_sub(i, 1)] + fConst406 * fRec98[faust_wrap_sub(i, 2)]) - fConst408 * (fConst409 * fRec97[faust_wrap_sub(i, 2)] + fConst410 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec97_perm[j255] = fRec97_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec96_tmp[j256] = fRec96_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fSlow39 * fRec96[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst408 * (fConst412 * fRec97[i] + fConst413 * fRec97[faust_wrap_sub(i, 1)] + fConst412 * fRec97[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec96_perm[j257] = fRec96_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec109_tmp[j258] = fRec109_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fZec115[i] - fConst414 * (fConst415 * fRec109[faust_wrap_sub(i, 2)] + fConst416 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec109_perm[j259] = fRec109_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec108_tmp[j260] = fRec108_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fConst414 * (fConst418 * fRec109[i] + fConst419 * fRec109[faust_wrap_sub(i, 1)] + fConst418 * fRec109[faust_wrap_sub(i, 2)]) - fConst420 * (fConst421 * fRec108[faust_wrap_sub(i, 2)] + fConst422 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec108_perm[j261] = fRec108_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 207 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec107_tmp[j262] = fRec107_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst420 * (fConst423 * fRec108[i] + fConst424 * fRec108[faust_wrap_sub(i, 1)] + fConst423 * fRec108[faust_wrap_sub(i, 2)]) - fConst425 * (fConst426 * fRec107[faust_wrap_sub(i, 2)] + fConst427 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec107_perm[j263] = fRec107_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Vectorizable loop 208 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec116[i] = fConst425 * (fConst428 * fRec107[i] + fConst429 * fRec107[faust_wrap_sub(i, 1)] + fConst428 * fRec107[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 209 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec106_tmp[j264] = fRec106_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fZec116[i] - fConst432 * (fConst433 * fRec106[faust_wrap_sub(i, 2)] + fConst436 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec106_perm[j265] = fRec106_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Recursive loop 210 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec105_tmp[j266] = fRec105_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fConst432 * (fConst438 * fRec106[i] + fConst439 * fRec106[faust_wrap_sub(i, 1)] + fConst438 * fRec106[faust_wrap_sub(i, 2)]) - fConst440 * (fConst441 * fRec105[faust_wrap_sub(i, 2)] + fConst442 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec105_perm[j267] = fRec105_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 211 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec104_tmp[j268] = fRec104_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst440 * (fConst444 * fRec105[i] + fConst445 * fRec105[faust_wrap_sub(i, 1)] + fConst444 * fRec105[faust_wrap_sub(i, 2)]) - fConst446 * (fConst447 * fRec104[faust_wrap_sub(i, 2)] + fConst448 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec104_perm[j269] = fRec104_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 212 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec103_tmp[j270] = fRec103_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fSlow39 * fRec103[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst446 * (fConst450 * fRec104[i] + fConst451 * fRec104[faust_wrap_sub(i, 1)] + fConst450 * fRec104[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec103_perm[j271] = fRec103_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 213 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec116_tmp[j272] = fRec116_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fZec116[i] - fConst452 * (fConst453 * fRec116[faust_wrap_sub(i, 2)] + fConst454 * fRec116[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec116_perm[j273] = fRec116_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 214 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec115_tmp[j274] = fRec115_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fConst452 * (fConst456 * fRec116[i] + fConst457 * fRec116[faust_wrap_sub(i, 1)] + fConst456 * fRec116[faust_wrap_sub(i, 2)]) - fConst458 * (fConst459 * fRec115[faust_wrap_sub(i, 2)] + fConst460 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec115_perm[j275] = fRec115_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 215 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec114_tmp[j276] = fRec114_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst458 * (fConst461 * fRec115[i] + fConst462 * fRec115[faust_wrap_sub(i, 1)] + fConst461 * fRec115[faust_wrap_sub(i, 2)]) - fConst463 * (fConst464 * fRec114[faust_wrap_sub(i, 2)] + fConst465 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec114_perm[j277] = fRec114_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Vectorizable loop 216 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec117[i] = fConst463 * (fConst466 * fRec114[i] + fConst467 * fRec114[faust_wrap_sub(i, 1)] + fConst466 * fRec114[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 217 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec113_tmp[j278] = fRec113_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fZec117[i] - fConst470 * (fConst471 * fRec113[faust_wrap_sub(i, 2)] + fConst474 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec113_perm[j279] = fRec113_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Recursive loop 218 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec112_tmp[j280] = fRec112_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fConst470 * (fConst476 * fRec113[i] + fConst477 * fRec113[faust_wrap_sub(i, 1)] + fConst476 * fRec113[faust_wrap_sub(i, 2)]) - fConst478 * (fConst479 * fRec112[faust_wrap_sub(i, 2)] + fConst480 * fRec112[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec112_perm[j281] = fRec112_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 219 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec111_tmp[j282] = fRec111_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fConst478 * (fConst482 * fRec112[i] + fConst483 * fRec112[faust_wrap_sub(i, 1)] + fConst482 * fRec112[faust_wrap_sub(i, 2)]) - fConst484 * (fConst485 * fRec111[faust_wrap_sub(i, 2)] + fConst486 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec111_perm[j283] = fRec111_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 220 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec110_tmp[j284] = fRec110_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fSlow39 * fRec110[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst484 * (fConst488 * fRec111[i] + fConst489 * fRec111[faust_wrap_sub(i, 1)] + fConst488 * fRec111[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec110_perm[j285] = fRec110_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 221 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec123_tmp[j286] = fRec123_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fZec117[i] - fConst490 * (fConst491 * fRec123[faust_wrap_sub(i, 2)] + fConst492 * fRec123[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec123_perm[j287] = fRec123_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 222 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec122_tmp[j288] = fRec122_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fConst490 * (fConst494 * fRec123[i] + fConst495 * fRec123[faust_wrap_sub(i, 1)] + fConst494 * fRec123[faust_wrap_sub(i, 2)]) - fConst496 * (fConst497 * fRec122[faust_wrap_sub(i, 2)] + fConst498 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec122_perm[j289] = fRec122_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 223 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec121_tmp[j290] = fRec121_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst496 * (fConst499 * fRec122[i] + fConst500 * fRec122[faust_wrap_sub(i, 1)] + fConst499 * fRec122[faust_wrap_sub(i, 2)]) - fConst501 * (fConst502 * fRec121[faust_wrap_sub(i, 2)] + fConst503 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec121_perm[j291] = fRec121_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Vectorizable loop 224 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec118[i] = fConst501 * (fConst504 * fRec121[i] + fConst505 * fRec121[faust_wrap_sub(i, 1)] + fConst504 * fRec121[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 225 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec120_tmp[j292] = fRec120_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fZec118[i] - fConst508 * (fConst509 * fRec120[faust_wrap_sub(i, 2)] + fConst512 * fRec120[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec120_perm[j293] = fRec120_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Recursive loop 226 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec119_tmp[j294] = fRec119_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fConst508 * (fConst514 * fRec120[i] + fConst515 * fRec120[faust_wrap_sub(i, 1)] + fConst514 * fRec120[faust_wrap_sub(i, 2)]) - fConst516 * (fConst517 * fRec119[faust_wrap_sub(i, 2)] + fConst518 * fRec119[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec119_perm[j295] = fRec119_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Recursive loop 227 */
			/* Pre code */
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec118_tmp[j296] = fRec118_perm[j296];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fConst516 * (fConst520 * fRec119[i] + fConst521 * fRec119[faust_wrap_sub(i, 1)] + fConst520 * fRec119[faust_wrap_sub(i, 2)]) - fConst522 * (fConst523 * fRec118[faust_wrap_sub(i, 2)] + fConst524 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec118_perm[j297] = fRec118_tmp[faust_wrap_add(vsize, j297)];
			}
			/* Recursive loop 228 */
			/* Pre code */
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec117_tmp[j298] = fRec117_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fSlow39 * fRec117[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst522 * (fConst526 * fRec118[i] + fConst527 * fRec118[faust_wrap_sub(i, 1)] + fConst526 * fRec118[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec117_perm[j299] = fRec117_tmp[faust_wrap_add(vsize, j299)];
			}
			/* Recursive loop 229 */
			/* Pre code */
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec127_tmp[j300] = fRec127_perm[j300];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fZec118[i] - fConst528 * (fConst529 * fRec127[faust_wrap_sub(i, 2)] + fConst530 * fRec127[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec127_perm[j301] = fRec127_tmp[faust_wrap_add(vsize, j301)];
			}
			/* Recursive loop 230 */
			/* Pre code */
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec126_tmp[j302] = fRec126_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fConst528 * (fConst532 * fRec127[i] + fConst533 * fRec127[faust_wrap_sub(i, 1)] + fConst532 * fRec127[faust_wrap_sub(i, 2)]) - fConst534 * (fConst535 * fRec126[faust_wrap_sub(i, 2)] + fConst536 * fRec126[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec126_perm[j303] = fRec126_tmp[faust_wrap_add(vsize, j303)];
			}
			/* Recursive loop 231 */
			/* Pre code */
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec125_tmp[j304] = fRec125_perm[j304];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fConst534 * (fConst537 * fRec126[i] + fConst538 * fRec126[faust_wrap_sub(i, 1)] + fConst537 * fRec126[faust_wrap_sub(i, 2)]) - fConst539 * (fConst540 * fRec125[faust_wrap_sub(i, 2)] + fConst541 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec125_perm[j305] = fRec125_tmp[faust_wrap_add(vsize, j305)];
			}
			/* Recursive loop 232 */
			/* Pre code */
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec124_tmp[j306] = fRec124_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fSlow39 * fRec124[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst539 * (fConst542 * fRec125[i] + fConst543 * fRec125[faust_wrap_sub(i, 1)] + fConst542 * fRec125[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec124_perm[j307] = fRec124_tmp[faust_wrap_add(vsize, j307)];
			}
			/* Recursive loop 233 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec32_tmp[j110] = fRec32_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fZec105[i] - fConst13 * (fConst14 * fRec32[faust_wrap_sub(i, 2)] + fConst17 * fRec32[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec32_perm[j111] = fRec32_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 234 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec31_tmp[j112] = fRec31_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fConst13 * (fConst19 * fRec32[i] + fConst20 * fRec32[faust_wrap_sub(i, 1)] + fConst19 * fRec32[faust_wrap_sub(i, 2)]) - fConst21 * (fConst22 * fRec31[faust_wrap_sub(i, 2)] + fConst23 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec31_perm[j113] = fRec31_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 235 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec30_tmp[j114] = fRec30_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst21 * (fConst25 * fRec31[i] + fConst26 * fRec31[faust_wrap_sub(i, 1)] + fConst25 * fRec31[faust_wrap_sub(i, 2)]) - fConst27 * (fConst28 * fRec30[faust_wrap_sub(i, 2)] + fConst29 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec30_perm[j115] = fRec30_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 236 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec29_tmp[j116] = fRec29_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fRec29[faust_wrap_sub(i, 1)] * fSlow39 + std::fabs(fConst27 * (fConst32 * fRec30[i] + fConst33 * fRec30[faust_wrap_sub(i, 1)] + fConst32 * fRec30[faust_wrap_sub(i, 2)])) * fSlow40;
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec29_perm[j117] = fRec29_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 237 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec36_tmp[j124] = fRec36_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fZec106[i] - fConst52 * (fConst53 * fRec36[faust_wrap_sub(i, 2)] + fConst56 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec36_perm[j125] = fRec36_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 238 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec35_tmp[j126] = fRec35_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fConst52 * (fConst58 * fRec36[i] + fConst59 * fRec36[faust_wrap_sub(i, 1)] + fConst58 * fRec36[faust_wrap_sub(i, 2)]) - fConst60 * (fConst61 * fRec35[faust_wrap_sub(i, 2)] + fConst62 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec35_perm[j127] = fRec35_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 239 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec34_tmp[j128] = fRec34_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst60 * (fConst64 * fRec35[i] + fConst65 * fRec35[faust_wrap_sub(i, 1)] + fConst64 * fRec35[faust_wrap_sub(i, 2)]) - fConst66 * (fConst67 * fRec34[faust_wrap_sub(i, 2)] + fConst68 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec34_perm[j129] = fRec34_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 240 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec33_tmp[j130] = fRec33_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fSlow39 * fRec33[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst66 * (fConst70 * fRec34[i] + fConst71 * fRec34[faust_wrap_sub(i, 1)] + fConst70 * fRec34[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec33_perm[j131] = fRec33_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 241 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec43_tmp[j138] = fRec43_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fZec107[i] - fConst90 * (fConst91 * fRec43[faust_wrap_sub(i, 2)] + fConst94 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec43_perm[j139] = fRec43_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 242 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec42_tmp[j140] = fRec42_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fConst90 * (fConst96 * fRec43[i] + fConst97 * fRec43[faust_wrap_sub(i, 1)] + fConst96 * fRec43[faust_wrap_sub(i, 2)]) - fConst98 * (fConst99 * fRec42[faust_wrap_sub(i, 2)] + fConst100 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec42_perm[j141] = fRec42_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 243 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec41_tmp[j142] = fRec41_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst98 * (fConst102 * fRec42[i] + fConst103 * fRec42[faust_wrap_sub(i, 1)] + fConst102 * fRec42[faust_wrap_sub(i, 2)]) - fConst104 * (fConst105 * fRec41[faust_wrap_sub(i, 2)] + fConst106 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec41_perm[j143] = fRec41_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 244 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec40_tmp[j144] = fRec40_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fSlow39 * fRec40[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst104 * (fConst108 * fRec41[i] + fConst109 * fRec41[faust_wrap_sub(i, 1)] + fConst108 * fRec41[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec40_perm[j145] = fRec40_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 245 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec50_tmp[j152] = fRec50_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fZec108[i] - fConst128 * (fConst129 * fRec50[faust_wrap_sub(i, 2)] + fConst132 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec50_perm[j153] = fRec50_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 246 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec49_tmp[j154] = fRec49_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fConst128 * (fConst134 * fRec50[i] + fConst135 * fRec50[faust_wrap_sub(i, 1)] + fConst134 * fRec50[faust_wrap_sub(i, 2)]) - fConst136 * (fConst137 * fRec49[faust_wrap_sub(i, 2)] + fConst138 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec49_perm[j155] = fRec49_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 247 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec48_tmp[j156] = fRec48_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst136 * (fConst140 * fRec49[i] + fConst141 * fRec49[faust_wrap_sub(i, 1)] + fConst140 * fRec49[faust_wrap_sub(i, 2)]) - fConst142 * (fConst143 * fRec48[faust_wrap_sub(i, 2)] + fConst144 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec48_perm[j157] = fRec48_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 248 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec47_tmp[j158] = fRec47_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fSlow39 * fRec47[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst142 * (fConst146 * fRec48[i] + fConst147 * fRec48[faust_wrap_sub(i, 1)] + fConst146 * fRec48[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec47_perm[j159] = fRec47_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 249 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec57_tmp[j166] = fRec57_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fZec109[i] - fConst166 * (fConst167 * fRec57[faust_wrap_sub(i, 2)] + fConst170 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec57_perm[j167] = fRec57_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 250 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec56_tmp[j168] = fRec56_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fConst166 * (fConst172 * fRec57[i] + fConst173 * fRec57[faust_wrap_sub(i, 1)] + fConst172 * fRec57[faust_wrap_sub(i, 2)]) - fConst174 * (fConst175 * fRec56[faust_wrap_sub(i, 2)] + fConst176 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec56_perm[j169] = fRec56_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 251 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec55_tmp[j170] = fRec55_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst174 * (fConst178 * fRec56[i] + fConst179 * fRec56[faust_wrap_sub(i, 1)] + fConst178 * fRec56[faust_wrap_sub(i, 2)]) - fConst180 * (fConst181 * fRec55[faust_wrap_sub(i, 2)] + fConst182 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec55_perm[j171] = fRec55_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 252 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec54_tmp[j172] = fRec54_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fSlow39 * fRec54[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst180 * (fConst184 * fRec55[i] + fConst185 * fRec55[faust_wrap_sub(i, 1)] + fConst184 * fRec55[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec54_perm[j173] = fRec54_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 253 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec64_tmp[j180] = fRec64_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fZec110[i] - fConst204 * (fConst205 * fRec64[faust_wrap_sub(i, 2)] + fConst208 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec64_perm[j181] = fRec64_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 254 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec63_tmp[j182] = fRec63_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fConst204 * (fConst210 * fRec64[i] + fConst211 * fRec64[faust_wrap_sub(i, 1)] + fConst210 * fRec64[faust_wrap_sub(i, 2)]) - fConst212 * (fConst213 * fRec63[faust_wrap_sub(i, 2)] + fConst214 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec63_perm[j183] = fRec63_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 255 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec62_tmp[j184] = fRec62_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst212 * (fConst216 * fRec63[i] + fConst217 * fRec63[faust_wrap_sub(i, 1)] + fConst216 * fRec63[faust_wrap_sub(i, 2)]) - fConst218 * (fConst219 * fRec62[faust_wrap_sub(i, 2)] + fConst220 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec62_perm[j185] = fRec62_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 256 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec61_tmp[j186] = fRec61_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fSlow39 * fRec61[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst218 * (fConst222 * fRec62[i] + fConst223 * fRec62[faust_wrap_sub(i, 1)] + fConst222 * fRec62[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec61_perm[j187] = fRec61_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 257 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec71_tmp[j194] = fRec71_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fZec111[i] - fConst242 * (fConst243 * fRec71[faust_wrap_sub(i, 2)] + fConst246 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec71_perm[j195] = fRec71_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 258 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec70_tmp[j196] = fRec70_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fConst242 * (fConst248 * fRec71[i] + fConst249 * fRec71[faust_wrap_sub(i, 1)] + fConst248 * fRec71[faust_wrap_sub(i, 2)]) - fConst250 * (fConst251 * fRec70[faust_wrap_sub(i, 2)] + fConst252 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec70_perm[j197] = fRec70_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 259 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec69_tmp[j198] = fRec69_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst250 * (fConst254 * fRec70[i] + fConst255 * fRec70[faust_wrap_sub(i, 1)] + fConst254 * fRec70[faust_wrap_sub(i, 2)]) - fConst256 * (fConst257 * fRec69[faust_wrap_sub(i, 2)] + fConst258 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec69_perm[j199] = fRec69_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 260 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec68_tmp[j200] = fRec68_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fSlow39 * fRec68[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst256 * (fConst260 * fRec69[i] + fConst261 * fRec69[faust_wrap_sub(i, 1)] + fConst260 * fRec69[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec68_perm[j201] = fRec68_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 261 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec78_tmp[j208] = fRec78_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fZec112[i] - fConst280 * (fConst281 * fRec78[faust_wrap_sub(i, 2)] + fConst284 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec78_perm[j209] = fRec78_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 262 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec77_tmp[j210] = fRec77_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fConst280 * (fConst286 * fRec78[i] + fConst287 * fRec78[faust_wrap_sub(i, 1)] + fConst286 * fRec78[faust_wrap_sub(i, 2)]) - fConst288 * (fConst289 * fRec77[faust_wrap_sub(i, 2)] + fConst290 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec77_perm[j211] = fRec77_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 263 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec76_tmp[j212] = fRec76_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst288 * (fConst292 * fRec77[i] + fConst293 * fRec77[faust_wrap_sub(i, 1)] + fConst292 * fRec77[faust_wrap_sub(i, 2)]) - fConst294 * (fConst295 * fRec76[faust_wrap_sub(i, 2)] + fConst296 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec76_perm[j213] = fRec76_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 264 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec75_tmp[j214] = fRec75_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fSlow39 * fRec75[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst294 * (fConst298 * fRec76[i] + fConst299 * fRec76[faust_wrap_sub(i, 1)] + fConst298 * fRec76[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec75_perm[j215] = fRec75_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Vectorizable loop 265 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec29[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec33[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec40[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec47[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec54[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec61[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec68[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec75[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec82[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec89[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec96[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec103[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec110[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec117[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec124[i]));
				fZec119[i] = fZec105[i];
			}
			/* Vectorizable loop 266 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec119[i]);
			}
			/* Vectorizable loop 267 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec119[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fSlow0 + 0.999 * fRec0[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec0_perm[j1] = fRec0_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec6_tmp[j2] = fRec6_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fSlow1 + 0.999 * fRec6[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec6_perm[j3] = fRec6_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec7_tmp[j4] = fRec7_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fSlow2 + 0.999 * fRec7[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec7_perm[j5] = fRec7_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec9_tmp[j6] = fRec9_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fRec9[faust_wrap_sub(i, 1)] * fSlow4 + fSlow5;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec9_perm[j7] = fRec9_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec9[i]));
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec8_tmp[j8] = fRec8_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec8[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec8[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec8_perm[j9] = fRec8_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fSlow6 * fRec9[i];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = std::max<double>(2e+01, std::fabs(fZec2[i]));
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec10_tmp[j10] = fRec10_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fRec10[faust_wrap_sub(i, 1)] + fConst1 * fZec3[i];
				fRec10[i] = fZec4[i] - std::floor(fZec4[i]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec10_perm[j11] = fRec10_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fSlow7 * fRec9[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = std::max<double>(2e+01, std::fabs(fZec5[i]));
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec11_tmp[j12] = fRec11_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fRec11[faust_wrap_sub(i, 1)] + fConst1 * fZec6[i];
				fRec11[i] = fZec7[i] - std::floor(fZec7[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec11_perm[j13] = fRec11_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = std::max<double>(fRec9[i], 23.44894968246214);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = std::max<double>(2e+01, std::fabs(fZec8[i]));
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec12_tmp[j14] = fRec12_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fRec12[faust_wrap_sub(i, 1)] + fConst1 * fZec9[i];
				fRec12[i] = fZec10[i] - std::floor(fZec10[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec12_perm[j15] = fRec12_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = std::max<double>(fZec2[i], 23.44894968246214);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = std::max<double>(2e+01, std::fabs(fZec11[i]));
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec13_tmp[j16] = fRec13_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = fRec13[faust_wrap_sub(i, 1)] + fConst1 * fZec12[i];
				fRec13[i] = fZec13[i] - std::floor(fZec13[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec13_perm[j17] = fRec13_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = std::max<double>(fZec5[i], 23.44894968246214);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = std::max<double>(2e+01, std::fabs(fZec14[i]));
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec14_tmp[j18] = fRec14_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fRec14[faust_wrap_sub(i, 1)] + fConst1 * fZec15[i];
				fRec14[i] = fZec16[i] - std::floor(fZec16[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec14_perm[j19] = fRec14_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				iVec0_tmp[j20] = iVec0_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				iVec0_perm[j21] = iVec0_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = 2.0 * fRec12[i];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fZec18[i] + -1.0;
			}
			/* Vectorizable loop 25 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fYec0_tmp[j22] = fYec0_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = mydsp_faustpower2_f(fZec19[i]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fYec0_perm[j23] = fYec0_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			fYec1_idx = (faust_wrap_add(fYec1_idx, fYec1_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[(faust_wrap_add(i, fYec1_idx)) & 4095] = fZec17[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec9[i];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst3 / fZec8[i]));
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec21[i] = static_cast<int>(fZec20[i]);
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = static_cast<double>(iZec21[i]);
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fYec1[(faust_wrap_add(i, fYec1_idx)) & 4095] - fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec21[i])) & 4095] * (fZec22[i] + (1.0 - fZec20[i])) - (fZec20[i] - fZec22[i]) * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), faust_wrap_add(iZec21[i], 1))) & 4095];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec15_tmp[j24] = fRec15_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fConst2 * fZec23[i] + 0.999 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec15_perm[j25] = fRec15_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = 2.0 * fRec13[i];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = fZec24[i] + -1.0;
			}
			/* Vectorizable loop 34 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fYec2_tmp[j26] = fYec2_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[i] = mydsp_faustpower2_f(fZec25[i]);
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fYec2_perm[j27] = fYec2_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			fYec3_idx = (faust_wrap_add(fYec3_idx, fYec3_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] = fZec17[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec12[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst3 / fZec11[i]));
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec27[i] = static_cast<int>(fZec26[i]);
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = static_cast<double>(iZec27[i]);
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] - fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iZec27[i])) & 4095] * (fZec28[i] + (1.0 - fZec26[i])) - (fZec26[i] - fZec28[i]) * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), faust_wrap_add(iZec27[i], 1))) & 4095];
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec16_tmp[j28] = fRec16_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = fConst2 * fZec29[i] + 0.999 * fRec16[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec16_perm[j29] = fRec16_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = 2.0 * fRec14[i];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fZec30[i] + -1.0;
			}
			/* Vectorizable loop 43 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fYec4_tmp[j30] = fYec4_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[i] = mydsp_faustpower2_f(fZec31[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fYec4_perm[j31] = fYec4_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 44 */
			/* Pre code */
			fYec5_idx = (faust_wrap_add(fYec5_idx, fYec5_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[(faust_wrap_add(i, fYec5_idx)) & 4095] = fZec17[i] * (fYec4[i] - fYec4[faust_wrap_sub(i, 1)]) / fZec15[i];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst3 / fZec14[i]));
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec33[i] = static_cast<int>(fZec32[i]);
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = static_cast<double>(iZec33[i]);
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = fYec5[(faust_wrap_add(i, fYec5_idx)) & 4095] - fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iZec33[i])) & 4095] * (fZec34[i] + (1.0 - fZec32[i])) - (fZec32[i] - fZec34[i]) * fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), faust_wrap_add(iZec33[i], 1))) & 4095];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec17_tmp[j32] = fRec17_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fConst2 * fZec35[i] + 0.999 * fRec17[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec17_perm[j33] = fRec17_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec18_tmp[j34] = fRec18_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fSlow8 + 0.99 * fRec18[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec18_perm[j35] = fRec18_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 51 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				iRec20_tmp[j36] = iRec20_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec20[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec20[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				iRec20_perm[j37] = iRec20_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec19_tmp[j38] = fRec19_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = 0.5221894 * fRec19[faust_wrap_sub(i, 3)] + 4.656612875245797e-10 * static_cast<double>(iRec20[i]) + 2.494956002 * fRec19[faust_wrap_sub(i, 1)] - 2.017265875 * fRec19[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec19_perm[j39] = fRec19_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec36[i] = fConst4 * fRec6[i];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec37[i] = 1.0 - fZec36[i];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec38[i] = 2.0 * fRec8[i];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec39[i] = fZec38[i] + -1.0;
			}
			/* Vectorizable loop 57 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fYec6_tmp[j40] = fYec6_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[i] = mydsp_faustpower2_f(fZec39[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fYec6_perm[j41] = fYec6_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec40[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 2)]);
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = mydsp_faustpower3_f(fZec39[i]);
			}
			/* Vectorizable loop 60 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fYec7_tmp[j42] = fYec7_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[i] = fZec41[i] + (1.0 - fZec38[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fYec7_perm[j43] = fYec7_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 61 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec8_tmp[j44] = fYec8_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[i] = (fZec41[i] + (1.0 - (fZec38[i] + fYec7[faust_wrap_sub(i, 1)]))) / fZec0[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec8_perm[j45] = fYec8_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 3)]);
			}
			/* Vectorizable loop 63 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fYec9_tmp[j46] = fYec9_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fYec9_perm[j47] = fYec9_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Vectorizable loop 64 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fYec10_tmp[j48] = fYec10_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[i] = (fYec9[i] - fYec9[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fYec10_perm[j49] = fYec10_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 65 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fYec11_tmp[j50] = fYec11_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[i] = (fYec10[i] - fYec10[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fYec11_perm[j51] = fYec11_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = 2.0 * fRec10[i];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec44[i] = fZec43[i] + -1.0;
			}
			/* Vectorizable loop 68 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec12_tmp[j52] = fYec12_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[i] = mydsp_faustpower2_f(fZec44[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec12_perm[j53] = fYec12_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec45[i] = mydsp_faustpower3_f(fZec44[i]);
			}
			/* Vectorizable loop 70 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fYec13_tmp[j54] = fYec13_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[i] = fZec45[i] + (1.0 - fZec43[i]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fYec13_perm[j55] = fYec13_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 71 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fYec14_tmp[j56] = fYec14_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[i] = (fZec45[i] + (1.0 - (fZec43[i] + fYec13[faust_wrap_sub(i, 1)]))) / fZec3[i];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fYec14_perm[j57] = fYec14_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 72 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fYec15_tmp[j58] = fYec15_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fYec15_perm[j59] = fYec15_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Vectorizable loop 73 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fYec16_tmp[j60] = fYec16_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[i] = (fYec15[i] - fYec15[faust_wrap_sub(i, 1)]) / fZec3[i];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fYec16_perm[j61] = fYec16_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Vectorizable loop 74 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fYec17_tmp[j62] = fYec17_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[i] = (fYec16[i] - fYec16[faust_wrap_sub(i, 1)]) / fZec3[i];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fYec17_perm[j63] = fYec17_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec46[i] = 2.0 * fRec11[i];
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec47[i] = fZec46[i] + -1.0;
			}
			/* Vectorizable loop 77 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fYec18_tmp[j64] = fYec18_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[i] = mydsp_faustpower2_f(fZec47[i]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fYec18_perm[j65] = fYec18_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 78 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec48[i] = mydsp_faustpower3_f(fZec47[i]);
			}
			/* Vectorizable loop 79 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fYec19_tmp[j66] = fYec19_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[i] = fZec48[i] + (1.0 - fZec46[i]);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fYec19_perm[j67] = fYec19_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Vectorizable loop 80 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fYec20_tmp[j68] = fYec20_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec20[i] = (fZec48[i] + (1.0 - (fZec46[i] + fYec19[faust_wrap_sub(i, 1)]))) / fZec6[i];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fYec20_perm[j69] = fYec20_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 81 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fYec21_tmp[j70] = fYec21_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec21[i] = fYec18[i] * (fYec18[i] + -2.0);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fYec21_perm[j71] = fYec21_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Vectorizable loop 82 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fYec22_tmp[j72] = fYec22_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec22[i] = (fYec21[i] - fYec21[faust_wrap_sub(i, 1)]) / fZec6[i];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fYec22_perm[j73] = fYec22_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Vectorizable loop 83 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fYec23_tmp[j74] = fYec23_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec23[i] = (fYec22[i] - fYec22[faust_wrap_sub(i, 1)]) / fZec6[i];
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fYec23_perm[j75] = fYec23_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 84 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec49[i] = mydsp_faustpower3_f(fZec19[i]);
			}
			/* Vectorizable loop 85 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fYec24_tmp[j76] = fYec24_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec24[i] = fZec49[i] + (1.0 - fZec18[i]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fYec24_perm[j77] = fYec24_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Vectorizable loop 86 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fYec25_tmp[j78] = fYec25_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec25[i] = (fZec49[i] + (1.0 - (fZec18[i] + fYec24[faust_wrap_sub(i, 1)]))) / fZec9[i];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fYec25_perm[j79] = fYec25_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Vectorizable loop 87 */
			/* Pre code */
			fYec26_idx = (faust_wrap_add(fYec26_idx, fYec26_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec26[(faust_wrap_add(i, fYec26_idx)) & 4095] = fZec40[i] * (fYec25[i] - fYec25[faust_wrap_sub(i, 1)]) / fZec9[i];
			}
			/* Post code */
			fYec26_idx_save = vsize;
			/* Vectorizable loop 88 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec50[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst0 * (fRec18[i] / fZec8[i])));
			}
			/* Vectorizable loop 89 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec51[i] = static_cast<int>(fZec50[i]);
			}
			/* Vectorizable loop 90 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec52[i] = static_cast<double>(iZec51[i]);
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec53[i] = fZec52[i] + (1.0 - fZec50[i]);
			}
			/* Vectorizable loop 92 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec54[i] = fZec50[i] - fZec52[i];
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec55[i] = faust_wrap_add(iZec51[i], 1);
			}
			/* Vectorizable loop 94 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec56[i] = mydsp_faustpower3_f(fZec25[i]);
			}
			/* Vectorizable loop 95 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fYec27_tmp[j80] = fYec27_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec27[i] = fZec56[i] + (1.0 - fZec24[i]);
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fYec27_perm[j81] = fYec27_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Vectorizable loop 96 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fYec28_tmp[j82] = fYec28_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec28[i] = (fZec56[i] + (1.0 - (fZec24[i] + fYec27[faust_wrap_sub(i, 1)]))) / fZec12[i];
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fYec28_perm[j83] = fYec28_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 97 */
			/* Pre code */
			fYec29_idx = (faust_wrap_add(fYec29_idx, fYec29_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec29[(faust_wrap_add(i, fYec29_idx)) & 4095] = fZec40[i] * (fYec28[i] - fYec28[faust_wrap_sub(i, 1)]) / fZec12[i];
			}
			/* Post code */
			fYec29_idx_save = vsize;
			/* Vectorizable loop 98 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec57[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst0 * (fRec18[i] / fZec11[i])));
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec58[i] = static_cast<int>(fZec57[i]);
			}
			/* Vectorizable loop 100 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec59[i] = static_cast<double>(iZec58[i]);
			}
			/* Vectorizable loop 101 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec60[i] = fZec59[i] + (1.0 - fZec57[i]);
			}
			/* Vectorizable loop 102 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec61[i] = fZec57[i] - fZec59[i];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec62[i] = faust_wrap_add(iZec58[i], 1);
			}
			/* Vectorizable loop 104 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec63[i] = mydsp_faustpower3_f(fZec31[i]);
			}
			/* Vectorizable loop 105 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fYec30_tmp[j84] = fYec30_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec30[i] = fZec63[i] + (1.0 - fZec30[i]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fYec30_perm[j85] = fYec30_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Vectorizable loop 106 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fYec31_tmp[j86] = fYec31_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec31[i] = (fZec63[i] + (1.0 - (fZec30[i] + fYec30[faust_wrap_sub(i, 1)]))) / fZec15[i];
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fYec31_perm[j87] = fYec31_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 107 */
			/* Pre code */
			fYec32_idx = (faust_wrap_add(fYec32_idx, fYec32_idx_save)) & 4095;
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec32[(faust_wrap_add(i, fYec32_idx)) & 4095] = fZec40[i] * (fYec31[i] - fYec31[faust_wrap_sub(i, 1)]) / fZec15[i];
			}
			/* Post code */
			fYec32_idx_save = vsize;
			/* Vectorizable loop 108 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec64[i] = std::max<double>(0.0, std::min<double>(2047.0, fConst0 * (fRec18[i] / fZec14[i])));
			}
			/* Vectorizable loop 109 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec65[i] = static_cast<int>(fZec64[i]);
			}
			/* Vectorizable loop 110 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec66[i] = static_cast<double>(iZec65[i]);
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec67[i] = fZec66[i] + (1.0 - fZec64[i]);
			}
			/* Vectorizable loop 112 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec68[i] = fZec64[i] - fZec66[i];
			}
			/* Vectorizable loop 113 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec69[i] = faust_wrap_add(iZec65[i], 1);
			}
			/* Vectorizable loop 114 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec70[i] = fSlow10 * static_cast<double>(input0[i]) + fRec7[i] * (fSlow11 * (((iSlow13) ? ((iSlow15) ? fConst6 * (fZec42[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst5 * (fZec40[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow14) ? fConst2 * (fZec17[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec39[i])) + ((iSlow13) ? ((iSlow15) ? fConst6 * (fZec42[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec3[i]) : fConst5 * (fZec40[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec3[i])) : ((iSlow14) ? fConst2 * (fZec17[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec3[i]) : fZec44[i])) + ((iSlow13) ? ((iSlow15) ? fConst6 * (fZec42[i] * (fYec23[i] - fYec23[faust_wrap_sub(i, 1)]) / fZec6[i]) : fConst5 * (fZec40[i] * (fYec20[i] - fYec20[faust_wrap_sub(i, 1)]) / fZec6[i])) : ((iSlow14) ? fConst2 * (fZec17[i] * (fYec18[i] - fYec18[faust_wrap_sub(i, 1)]) / fZec6[i]) : fZec47[i]))) + fSlow16 * (fZec23[i] + fZec29[i] + fZec35[i]) + fSlow17 * fRec9[i] * (fRec15[i] + fSlow6 * fRec16[i] + fSlow7 * fRec17[i]) + fSlow18 * (fSlow20 * (fYec26[(faust_wrap_add(i, fYec26_idx)) & 4095] - fYec26[(faust_wrap_sub(faust_wrap_add(i, fYec26_idx), iZec51[i])) & 4095] * fZec53[i] - fZec54[i] * fYec26[(faust_wrap_sub(faust_wrap_add(i, fYec26_idx), iZec55[i])) & 4095] + (fYec29[(faust_wrap_add(i, fYec29_idx)) & 4095] - fYec29[(faust_wrap_sub(faust_wrap_add(i, fYec29_idx), iZec58[i])) & 4095] * fZec60[i] - fZec61[i] * fYec29[(faust_wrap_sub(faust_wrap_add(i, fYec29_idx), iZec62[i])) & 4095]) + (fYec32[(faust_wrap_add(i, fYec32_idx)) & 4095] - fYec32[(faust_wrap_sub(faust_wrap_add(i, fYec32_idx), iZec65[i])) & 4095] * fZec67[i] - fZec68[i] * fYec32[(faust_wrap_sub(faust_wrap_add(i, fYec32_idx), iZec69[i])) & 4095])) + fSlow21 * (fYec1[(faust_wrap_add(i, fYec1_idx)) & 4095] - fZec53[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec51[i])) & 4095] - fZec54[i] * fYec1[(faust_wrap_sub(faust_wrap_add(i, fYec1_idx), iZec55[i])) & 4095] + (fYec3[(faust_wrap_add(i, fYec3_idx)) & 4095] - fZec60[i] * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iZec58[i])) & 4095] - fZec61[i] * fYec3[(faust_wrap_sub(faust_wrap_add(i, fYec3_idx), iZec62[i])) & 4095]) + (fYec5[(faust_wrap_add(i, fYec5_idx)) & 4095] - fZec67[i] * fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iZec65[i])) & 4095] - fZec68[i] * fYec5[(faust_wrap_sub(faust_wrap_add(i, fYec5_idx), iZec69[i])) & 4095]))) + fSlow22 * (0.049922035 * fRec19[i] + 0.050612699 * fRec19[faust_wrap_sub(i, 2)] - (0.095993537 * fRec19[faust_wrap_sub(i, 1)] + 0.004408786 * fRec19[faust_wrap_sub(i, 3)])));
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec71[i] = ((iSlow9) ? 0.0 : fZec70[i]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec5_tmp[j88] = fRec5_perm[j88];
			}
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec4_tmp[j90] = fRec4_perm[j90];
			}
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec3_tmp[j92] = fRec3_perm[j92];
			}
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec2_tmp[j94] = fRec2_perm[j94];
			}
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec1_tmp[j96] = fRec1_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fZec37[i] * fRec5[faust_wrap_sub(i, 1)] + fZec71[i] - fSlow24 * fRec1[faust_wrap_sub(i, 1)];
				fRec4[i] = fRec5[i] + fZec37[i] * fRec4[faust_wrap_sub(i, 1)];
				fRec3[i] = fRec4[i] + fZec37[i] * fRec3[faust_wrap_sub(i, 1)];
				fRec2[i] = fRec3[i] + fRec2[faust_wrap_sub(i, 1)] * fZec37[i];
				fRec1[i] = fRec2[i] * mydsp_faustpower4_f(fZec36[i]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec5_perm[j89] = fRec5_tmp[faust_wrap_add(vsize, j89)];
			}
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec4_perm[j91] = fRec4_tmp[faust_wrap_add(vsize, j91)];
			}
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec3_perm[j93] = fRec3_tmp[faust_wrap_add(vsize, j93)];
			}
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec2_perm[j95] = fRec2_tmp[faust_wrap_add(vsize, j95)];
			}
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec1_perm[j97] = fRec1_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 117 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec72[i] = std::tan(fConst10 * std::max<double>(2e+01, std::min<double>(1e+04, fRec6[i])));
			}
			/* Vectorizable loop 118 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec73[i] = 1.0 / fZec72[i];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec74[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec72[i]);
			}
			/* Vectorizable loop 120 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec75[i] = fSlow28 + (fSlow29 + fZec73[i]) / fZec72[i] + 1.0;
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec22_tmp[j98] = fRec22_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fZec71[i] - (fRec22[faust_wrap_sub(i, 2)] * (fSlow28 + (fZec73[i] - fSlow29) / fZec72[i] + 1.0) + 2.0 * fRec22[faust_wrap_sub(i, 1)] * (fSlow28 + fZec74[i])) / fZec75[i];
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec22_perm[j99] = fRec22_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Vectorizable loop 122 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec76[i] = fSlow27 + ((fSlow30 + fZec73[i]) / fZec72[i] + 1.0 - fSlow26);
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec21_tmp[j100] = fRec21_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = (fRec22[faust_wrap_sub(i, 2)] + fRec22[i] + 2.0 * fRec22[faust_wrap_sub(i, 1)]) / fZec75[i] - (fRec21[faust_wrap_sub(i, 2)] * (fSlow27 + ((fZec73[i] - fSlow30) / fZec72[i] + 1.0 - fSlow26)) + 2.0 * fRec21[faust_wrap_sub(i, 1)] * (fSlow27 + (fZec74[i] - fSlow26))) / fZec76[i];
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec21_perm[j101] = fRec21_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Vectorizable loop 124 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec77[i] = std::tan(fConst10 * std::max<double>(fRec6[i], 2e+01));
			}
			/* Vectorizable loop 125 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec78[i] = 1.0 / fZec77[i];
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec79[i] = fSlow33 + (fSlow34 + fZec78[i]) / fZec77[i] + 1.0;
			}
			/* Vectorizable loop 127 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec85[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec77[i]);
			}
			/* Vectorizable loop 128 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec80[i] = (fSlow33 + (1.0 - (fSlow34 - fZec78[i]) / fZec77[i])) / fZec79[i];
			}
			/* Vectorizable loop 129 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec81[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec80[i]));
			}
			/* Vectorizable loop 130 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec82[i] = 1.0 - mydsp_faustpower2_f(fZec81[i]);
			}
			/* Vectorizable loop 131 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec83[i] = std::sqrt(std::max<double>(0.0, fZec82[i]));
			}
			/* Vectorizable loop 132 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec86[i] = fSlow33 + fZec85[i];
			}
			/* Vectorizable loop 133 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec87[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec86[i] / (fZec79[i] * (fZec80[i] + 1.0)))));
			}
			/* Vectorizable loop 134 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec88[i] = 1.0 - mydsp_faustpower2_f(fZec87[i]);
			}
			/* Vectorizable loop 135 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec89[i] = std::sqrt(std::max<double>(0.0, fZec88[i]));
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec25_tmp[j102] = fRec25_perm[j102];
			}
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec23_tmp[j104] = fRec23_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec84[i] = fZec71[i] * fZec83[i] - fZec81[i] * fRec23[faust_wrap_sub(i, 1)];
				fRec25[i] = fZec84[i] * fZec89[i] - fZec87[i] * fRec25[faust_wrap_sub(i, 1)];
				fRec23[i] = fZec84[i] * fZec87[i] + fRec25[faust_wrap_sub(i, 1)] * fZec89[i];
				fRec24[i] = fRec25[i];
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec25_perm[j103] = fRec25_tmp[faust_wrap_add(vsize, j103)];
			}
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec23_perm[j105] = fRec23_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Vectorizable loop 137 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec90[i] = 1.0 - fZec86[i] / fZec79[i];
			}
			/* Vectorizable loop 138 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec91[i] = std::sqrt(fZec82[i]);
			}
			/* Vectorizable loop 139 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec92[i] = fZec71[i] * fZec81[i] + fRec23[faust_wrap_sub(i, 1)] * fZec83[i] + 2.0 * (fRec23[i] * fZec90[i] / fZec91[i]) + fRec24[i] * (1.0 - fZec80[i] - 2.0 * fZec87[i] * fZec90[i]) / (fZec91[i] * std::sqrt(fZec88[i]));
			}
			/* Vectorizable loop 140 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec93[i] = fSlow31 + ((fSlow35 + fZec78[i]) / fZec77[i] + 1.0 - fSlow32);
			}
			/* Vectorizable loop 141 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec94[i] = (fSlow31 + ((fZec78[i] - fSlow35) / fZec77[i] + 1.0 - fSlow32)) / fZec93[i];
			}
			/* Vectorizable loop 142 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec95[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec94[i]));
			}
			/* Vectorizable loop 143 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec96[i] = 1.0 - mydsp_faustpower2_f(fZec95[i]);
			}
			/* Vectorizable loop 144 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec97[i] = std::sqrt(std::max<double>(0.0, fZec96[i]));
			}
			/* Vectorizable loop 145 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec99[i] = fSlow31 + (fZec85[i] - fSlow32);
			}
			/* Vectorizable loop 146 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec100[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec99[i] / (fZec93[i] * (fZec94[i] + 1.0)))));
			}
			/* Vectorizable loop 147 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec101[i] = 1.0 - mydsp_faustpower2_f(fZec100[i]);
			}
			/* Vectorizable loop 148 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec102[i] = std::sqrt(std::max<double>(0.0, fZec101[i]));
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec28_tmp[j106] = fRec28_perm[j106];
			}
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec26_tmp[j108] = fRec26_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec98[i] = fZec92[i] * fZec97[i] / fZec79[i] - fZec95[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec28[i] = fZec98[i] * fZec102[i] - fZec100[i] * fRec28[faust_wrap_sub(i, 1)];
				fRec26[i] = fZec98[i] * fZec100[i] + fRec28[faust_wrap_sub(i, 1)] * fZec102[i];
				fRec27[i] = fRec28[i];
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec28_perm[j107] = fRec28_tmp[faust_wrap_add(vsize, j107)];
			}
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec26_perm[j109] = fRec26_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Vectorizable loop 150 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec103[i] = 1.0 - fZec99[i] / fZec93[i];
			}
			/* Vectorizable loop 151 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec104[i] = std::sqrt(fZec96[i]);
			}
			/* Vectorizable loop 152 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec105[i] = ((iSlow9) ? fZec70[i] : fRec0[i] * ((iSlow36) ? ((iSlow37) ? (fZec92[i] * fZec95[i] / fZec79[i] + fRec26[faust_wrap_sub(i, 1)] * fZec97[i] + 2.0 * (fRec26[i] * fZec103[i] / fZec104[i]) + fRec27[i] * (1.0 - fZec94[i] - 2.0 * fZec100[i] * fZec103[i]) / (fZec104[i] * std::sqrt(fZec101[i]))) / fZec93[i] : (fRec21[faust_wrap_sub(i, 2)] + fRec21[i] + 2.0 * fRec21[faust_wrap_sub(i, 1)]) / fZec76[i]) : fRec1[i]));
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec39_tmp[j118] = fRec39_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fZec105[i] - fConst34 * (fConst35 * fRec39[faust_wrap_sub(i, 2)] + fConst36 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec39_perm[j119] = fRec39_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec38_tmp[j120] = fRec38_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fConst34 * (fConst38 * fRec39[i] + fConst39 * fRec39[faust_wrap_sub(i, 1)] + fConst38 * fRec39[faust_wrap_sub(i, 2)]) - fConst40 * (fConst41 * fRec38[faust_wrap_sub(i, 2)] + fConst42 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec38_perm[j121] = fRec38_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec37_tmp[j122] = fRec37_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst40 * (fConst43 * fRec38[i] + fConst44 * fRec38[faust_wrap_sub(i, 1)] + fConst43 * fRec38[faust_wrap_sub(i, 2)]) - fConst45 * (fConst46 * fRec37[faust_wrap_sub(i, 2)] + fConst47 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec37_perm[j123] = fRec37_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Vectorizable loop 156 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec106[i] = fConst45 * (fConst48 * fRec37[i] + fConst49 * fRec37[faust_wrap_sub(i, 1)] + fConst48 * fRec37[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec46_tmp[j132] = fRec46_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fZec106[i] - fConst72 * (fConst73 * fRec46[faust_wrap_sub(i, 2)] + fConst74 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec46_perm[j133] = fRec46_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec45_tmp[j134] = fRec45_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fConst72 * (fConst76 * fRec46[i] + fConst77 * fRec46[faust_wrap_sub(i, 1)] + fConst76 * fRec46[faust_wrap_sub(i, 2)]) - fConst78 * (fConst79 * fRec45[faust_wrap_sub(i, 2)] + fConst80 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec45_perm[j135] = fRec45_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec44_tmp[j136] = fRec44_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst78 * (fConst81 * fRec45[i] + fConst82 * fRec45[faust_wrap_sub(i, 1)] + fConst81 * fRec45[faust_wrap_sub(i, 2)]) - fConst83 * (fConst84 * fRec44[faust_wrap_sub(i, 2)] + fConst85 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec44_perm[j137] = fRec44_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Vectorizable loop 160 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec107[i] = fConst83 * (fConst86 * fRec44[i] + fConst87 * fRec44[faust_wrap_sub(i, 1)] + fConst86 * fRec44[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec53_tmp[j146] = fRec53_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fZec107[i] - fConst110 * (fConst111 * fRec53[faust_wrap_sub(i, 2)] + fConst112 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec53_perm[j147] = fRec53_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec52_tmp[j148] = fRec52_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fConst110 * (fConst114 * fRec53[i] + fConst115 * fRec53[faust_wrap_sub(i, 1)] + fConst114 * fRec53[faust_wrap_sub(i, 2)]) - fConst116 * (fConst117 * fRec52[faust_wrap_sub(i, 2)] + fConst118 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec52_perm[j149] = fRec52_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec51_tmp[j150] = fRec51_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst116 * (fConst119 * fRec52[i] + fConst120 * fRec52[faust_wrap_sub(i, 1)] + fConst119 * fRec52[faust_wrap_sub(i, 2)]) - fConst121 * (fConst122 * fRec51[faust_wrap_sub(i, 2)] + fConst123 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec51_perm[j151] = fRec51_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Vectorizable loop 164 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec108[i] = fConst121 * (fConst124 * fRec51[i] + fConst125 * fRec51[faust_wrap_sub(i, 1)] + fConst124 * fRec51[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec60_tmp[j160] = fRec60_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fZec108[i] - fConst148 * (fConst149 * fRec60[faust_wrap_sub(i, 2)] + fConst150 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec60_perm[j161] = fRec60_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec59_tmp[j162] = fRec59_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fConst148 * (fConst152 * fRec60[i] + fConst153 * fRec60[faust_wrap_sub(i, 1)] + fConst152 * fRec60[faust_wrap_sub(i, 2)]) - fConst154 * (fConst155 * fRec59[faust_wrap_sub(i, 2)] + fConst156 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec59_perm[j163] = fRec59_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec58_tmp[j164] = fRec58_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst154 * (fConst157 * fRec59[i] + fConst158 * fRec59[faust_wrap_sub(i, 1)] + fConst157 * fRec59[faust_wrap_sub(i, 2)]) - fConst159 * (fConst160 * fRec58[faust_wrap_sub(i, 2)] + fConst161 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec58_perm[j165] = fRec58_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Vectorizable loop 168 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec109[i] = fConst159 * (fConst162 * fRec58[i] + fConst163 * fRec58[faust_wrap_sub(i, 1)] + fConst162 * fRec58[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec67_tmp[j174] = fRec67_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fZec109[i] - fConst186 * (fConst187 * fRec67[faust_wrap_sub(i, 2)] + fConst188 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec67_perm[j175] = fRec67_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec66_tmp[j176] = fRec66_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fConst186 * (fConst190 * fRec67[i] + fConst191 * fRec67[faust_wrap_sub(i, 1)] + fConst190 * fRec67[faust_wrap_sub(i, 2)]) - fConst192 * (fConst193 * fRec66[faust_wrap_sub(i, 2)] + fConst194 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec66_perm[j177] = fRec66_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec65_tmp[j178] = fRec65_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst192 * (fConst195 * fRec66[i] + fConst196 * fRec66[faust_wrap_sub(i, 1)] + fConst195 * fRec66[faust_wrap_sub(i, 2)]) - fConst197 * (fConst198 * fRec65[faust_wrap_sub(i, 2)] + fConst199 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec65_perm[j179] = fRec65_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Vectorizable loop 172 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec110[i] = fConst197 * (fConst200 * fRec65[i] + fConst201 * fRec65[faust_wrap_sub(i, 1)] + fConst200 * fRec65[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec74_tmp[j188] = fRec74_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fZec110[i] - fConst224 * (fConst225 * fRec74[faust_wrap_sub(i, 2)] + fConst226 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec74_perm[j189] = fRec74_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec73_tmp[j190] = fRec73_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fConst224 * (fConst228 * fRec74[i] + fConst229 * fRec74[faust_wrap_sub(i, 1)] + fConst228 * fRec74[faust_wrap_sub(i, 2)]) - fConst230 * (fConst231 * fRec73[faust_wrap_sub(i, 2)] + fConst232 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec73_perm[j191] = fRec73_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec72_tmp[j192] = fRec72_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst230 * (fConst233 * fRec73[i] + fConst234 * fRec73[faust_wrap_sub(i, 1)] + fConst233 * fRec73[faust_wrap_sub(i, 2)]) - fConst235 * (fConst236 * fRec72[faust_wrap_sub(i, 2)] + fConst237 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec72_perm[j193] = fRec72_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Vectorizable loop 176 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec111[i] = fConst235 * (fConst238 * fRec72[i] + fConst239 * fRec72[faust_wrap_sub(i, 1)] + fConst238 * fRec72[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec81_tmp[j202] = fRec81_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fZec111[i] - fConst262 * (fConst263 * fRec81[faust_wrap_sub(i, 2)] + fConst264 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec81_perm[j203] = fRec81_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec80_tmp[j204] = fRec80_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fConst262 * (fConst266 * fRec81[i] + fConst267 * fRec81[faust_wrap_sub(i, 1)] + fConst266 * fRec81[faust_wrap_sub(i, 2)]) - fConst268 * (fConst269 * fRec80[faust_wrap_sub(i, 2)] + fConst270 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec80_perm[j205] = fRec80_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec79_tmp[j206] = fRec79_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst268 * (fConst271 * fRec80[i] + fConst272 * fRec80[faust_wrap_sub(i, 1)] + fConst271 * fRec80[faust_wrap_sub(i, 2)]) - fConst273 * (fConst274 * fRec79[faust_wrap_sub(i, 2)] + fConst275 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec79_perm[j207] = fRec79_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Vectorizable loop 180 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec112[i] = fConst273 * (fConst276 * fRec79[i] + fConst277 * fRec79[faust_wrap_sub(i, 1)] + fConst276 * fRec79[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec88_tmp[j216] = fRec88_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fZec112[i] - fConst300 * (fConst301 * fRec88[faust_wrap_sub(i, 2)] + fConst302 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec88_perm[j217] = fRec88_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec87_tmp[j218] = fRec87_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fConst300 * (fConst304 * fRec88[i] + fConst305 * fRec88[faust_wrap_sub(i, 1)] + fConst304 * fRec88[faust_wrap_sub(i, 2)]) - fConst306 * (fConst307 * fRec87[faust_wrap_sub(i, 2)] + fConst308 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec87_perm[j219] = fRec87_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec86_tmp[j220] = fRec86_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst306 * (fConst309 * fRec87[i] + fConst310 * fRec87[faust_wrap_sub(i, 1)] + fConst309 * fRec87[faust_wrap_sub(i, 2)]) - fConst311 * (fConst312 * fRec86[faust_wrap_sub(i, 2)] + fConst313 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec86_perm[j221] = fRec86_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Vectorizable loop 184 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec113[i] = fConst311 * (fConst314 * fRec86[i] + fConst315 * fRec86[faust_wrap_sub(i, 1)] + fConst314 * fRec86[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec85_tmp[j222] = fRec85_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fZec113[i] - fConst318 * (fConst319 * fRec85[faust_wrap_sub(i, 2)] + fConst322 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec85_perm[j223] = fRec85_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec84_tmp[j224] = fRec84_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fConst318 * (fConst324 * fRec85[i] + fConst325 * fRec85[faust_wrap_sub(i, 1)] + fConst324 * fRec85[faust_wrap_sub(i, 2)]) - fConst326 * (fConst327 * fRec84[faust_wrap_sub(i, 2)] + fConst328 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec84_perm[j225] = fRec84_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec83_tmp[j226] = fRec83_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst326 * (fConst330 * fRec84[i] + fConst331 * fRec84[faust_wrap_sub(i, 1)] + fConst330 * fRec84[faust_wrap_sub(i, 2)]) - fConst332 * (fConst333 * fRec83[faust_wrap_sub(i, 2)] + fConst334 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec83_perm[j227] = fRec83_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec82_tmp[j228] = fRec82_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fSlow39 * fRec82[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst332 * (fConst336 * fRec83[i] + fConst337 * fRec83[faust_wrap_sub(i, 1)] + fConst336 * fRec83[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec82_perm[j229] = fRec82_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec95_tmp[j230] = fRec95_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fZec113[i] - fConst338 * (fConst339 * fRec95[faust_wrap_sub(i, 2)] + fConst340 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec95_perm[j231] = fRec95_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 190 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec94_tmp[j232] = fRec94_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fConst338 * (fConst342 * fRec95[i] + fConst343 * fRec95[faust_wrap_sub(i, 1)] + fConst342 * fRec95[faust_wrap_sub(i, 2)]) - fConst344 * (fConst345 * fRec94[faust_wrap_sub(i, 2)] + fConst346 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec94_perm[j233] = fRec94_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec93_tmp[j234] = fRec93_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst344 * (fConst347 * fRec94[i] + fConst348 * fRec94[faust_wrap_sub(i, 1)] + fConst347 * fRec94[faust_wrap_sub(i, 2)]) - fConst349 * (fConst350 * fRec93[faust_wrap_sub(i, 2)] + fConst351 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec93_perm[j235] = fRec93_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Vectorizable loop 192 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec114[i] = fConst349 * (fConst352 * fRec93[i] + fConst353 * fRec93[faust_wrap_sub(i, 1)] + fConst352 * fRec93[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec92_tmp[j236] = fRec92_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fZec114[i] - fConst356 * (fConst357 * fRec92[faust_wrap_sub(i, 2)] + fConst360 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec92_perm[j237] = fRec92_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec91_tmp[j238] = fRec91_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fConst356 * (fConst362 * fRec92[i] + fConst363 * fRec92[faust_wrap_sub(i, 1)] + fConst362 * fRec92[faust_wrap_sub(i, 2)]) - fConst364 * (fConst365 * fRec91[faust_wrap_sub(i, 2)] + fConst366 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec91_perm[j239] = fRec91_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec90_tmp[j240] = fRec90_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst364 * (fConst368 * fRec91[i] + fConst369 * fRec91[faust_wrap_sub(i, 1)] + fConst368 * fRec91[faust_wrap_sub(i, 2)]) - fConst370 * (fConst371 * fRec90[faust_wrap_sub(i, 2)] + fConst372 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec90_perm[j241] = fRec90_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec89_tmp[j242] = fRec89_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fSlow39 * fRec89[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst370 * (fConst374 * fRec90[i] + fConst375 * fRec90[faust_wrap_sub(i, 1)] + fConst374 * fRec90[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec89_perm[j243] = fRec89_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec102_tmp[j244] = fRec102_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fZec114[i] - fConst376 * (fConst377 * fRec102[faust_wrap_sub(i, 2)] + fConst378 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec102_perm[j245] = fRec102_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 198 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec101_tmp[j246] = fRec101_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fConst376 * (fConst380 * fRec102[i] + fConst381 * fRec102[faust_wrap_sub(i, 1)] + fConst380 * fRec102[faust_wrap_sub(i, 2)]) - fConst382 * (fConst383 * fRec101[faust_wrap_sub(i, 2)] + fConst384 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec101_perm[j247] = fRec101_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec100_tmp[j248] = fRec100_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst382 * (fConst385 * fRec101[i] + fConst386 * fRec101[faust_wrap_sub(i, 1)] + fConst385 * fRec101[faust_wrap_sub(i, 2)]) - fConst387 * (fConst388 * fRec100[faust_wrap_sub(i, 2)] + fConst389 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec100_perm[j249] = fRec100_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Vectorizable loop 200 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec115[i] = fConst387 * (fConst390 * fRec100[i] + fConst391 * fRec100[faust_wrap_sub(i, 1)] + fConst390 * fRec100[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec99_tmp[j250] = fRec99_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fZec115[i] - fConst394 * (fConst395 * fRec99[faust_wrap_sub(i, 2)] + fConst398 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec99_perm[j251] = fRec99_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec98_tmp[j252] = fRec98_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fConst394 * (fConst400 * fRec99[i] + fConst401 * fRec99[faust_wrap_sub(i, 1)] + fConst400 * fRec99[faust_wrap_sub(i, 2)]) - fConst402 * (fConst403 * fRec98[faust_wrap_sub(i, 2)] + fConst404 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec98_perm[j253] = fRec98_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec97_tmp[j254] = fRec97_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst402 * (fConst406 * fRec98[i] + fConst407 * fRec98[faust_wrap_sub(i, 1)] + fConst406 * fRec98[faust_wrap_sub(i, 2)]) - fConst408 * (fConst409 * fRec97[faust_wrap_sub(i, 2)] + fConst410 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec97_perm[j255] = fRec97_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec96_tmp[j256] = fRec96_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fSlow39 * fRec96[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst408 * (fConst412 * fRec97[i] + fConst413 * fRec97[faust_wrap_sub(i, 1)] + fConst412 * fRec97[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec96_perm[j257] = fRec96_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec109_tmp[j258] = fRec109_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fZec115[i] - fConst414 * (fConst415 * fRec109[faust_wrap_sub(i, 2)] + fConst416 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec109_perm[j259] = fRec109_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec108_tmp[j260] = fRec108_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fConst414 * (fConst418 * fRec109[i] + fConst419 * fRec109[faust_wrap_sub(i, 1)] + fConst418 * fRec109[faust_wrap_sub(i, 2)]) - fConst420 * (fConst421 * fRec108[faust_wrap_sub(i, 2)] + fConst422 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec108_perm[j261] = fRec108_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 207 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec107_tmp[j262] = fRec107_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst420 * (fConst423 * fRec108[i] + fConst424 * fRec108[faust_wrap_sub(i, 1)] + fConst423 * fRec108[faust_wrap_sub(i, 2)]) - fConst425 * (fConst426 * fRec107[faust_wrap_sub(i, 2)] + fConst427 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec107_perm[j263] = fRec107_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Vectorizable loop 208 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec116[i] = fConst425 * (fConst428 * fRec107[i] + fConst429 * fRec107[faust_wrap_sub(i, 1)] + fConst428 * fRec107[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 209 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec106_tmp[j264] = fRec106_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fZec116[i] - fConst432 * (fConst433 * fRec106[faust_wrap_sub(i, 2)] + fConst436 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec106_perm[j265] = fRec106_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Recursive loop 210 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec105_tmp[j266] = fRec105_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fConst432 * (fConst438 * fRec106[i] + fConst439 * fRec106[faust_wrap_sub(i, 1)] + fConst438 * fRec106[faust_wrap_sub(i, 2)]) - fConst440 * (fConst441 * fRec105[faust_wrap_sub(i, 2)] + fConst442 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec105_perm[j267] = fRec105_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 211 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec104_tmp[j268] = fRec104_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst440 * (fConst444 * fRec105[i] + fConst445 * fRec105[faust_wrap_sub(i, 1)] + fConst444 * fRec105[faust_wrap_sub(i, 2)]) - fConst446 * (fConst447 * fRec104[faust_wrap_sub(i, 2)] + fConst448 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec104_perm[j269] = fRec104_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 212 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec103_tmp[j270] = fRec103_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fSlow39 * fRec103[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst446 * (fConst450 * fRec104[i] + fConst451 * fRec104[faust_wrap_sub(i, 1)] + fConst450 * fRec104[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec103_perm[j271] = fRec103_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 213 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec116_tmp[j272] = fRec116_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fZec116[i] - fConst452 * (fConst453 * fRec116[faust_wrap_sub(i, 2)] + fConst454 * fRec116[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec116_perm[j273] = fRec116_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 214 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec115_tmp[j274] = fRec115_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fConst452 * (fConst456 * fRec116[i] + fConst457 * fRec116[faust_wrap_sub(i, 1)] + fConst456 * fRec116[faust_wrap_sub(i, 2)]) - fConst458 * (fConst459 * fRec115[faust_wrap_sub(i, 2)] + fConst460 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec115_perm[j275] = fRec115_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 215 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec114_tmp[j276] = fRec114_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst458 * (fConst461 * fRec115[i] + fConst462 * fRec115[faust_wrap_sub(i, 1)] + fConst461 * fRec115[faust_wrap_sub(i, 2)]) - fConst463 * (fConst464 * fRec114[faust_wrap_sub(i, 2)] + fConst465 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec114_perm[j277] = fRec114_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Vectorizable loop 216 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec117[i] = fConst463 * (fConst466 * fRec114[i] + fConst467 * fRec114[faust_wrap_sub(i, 1)] + fConst466 * fRec114[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 217 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec113_tmp[j278] = fRec113_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fZec117[i] - fConst470 * (fConst471 * fRec113[faust_wrap_sub(i, 2)] + fConst474 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec113_perm[j279] = fRec113_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Recursive loop 218 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec112_tmp[j280] = fRec112_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fConst470 * (fConst476 * fRec113[i] + fConst477 * fRec113[faust_wrap_sub(i, 1)] + fConst476 * fRec113[faust_wrap_sub(i, 2)]) - fConst478 * (fConst479 * fRec112[faust_wrap_sub(i, 2)] + fConst480 * fRec112[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec112_perm[j281] = fRec112_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 219 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec111_tmp[j282] = fRec111_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fConst478 * (fConst482 * fRec112[i] + fConst483 * fRec112[faust_wrap_sub(i, 1)] + fConst482 * fRec112[faust_wrap_sub(i, 2)]) - fConst484 * (fConst485 * fRec111[faust_wrap_sub(i, 2)] + fConst486 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec111_perm[j283] = fRec111_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 220 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec110_tmp[j284] = fRec110_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fSlow39 * fRec110[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst484 * (fConst488 * fRec111[i] + fConst489 * fRec111[faust_wrap_sub(i, 1)] + fConst488 * fRec111[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec110_perm[j285] = fRec110_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 221 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec123_tmp[j286] = fRec123_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fZec117[i] - fConst490 * (fConst491 * fRec123[faust_wrap_sub(i, 2)] + fConst492 * fRec123[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec123_perm[j287] = fRec123_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 222 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec122_tmp[j288] = fRec122_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fConst490 * (fConst494 * fRec123[i] + fConst495 * fRec123[faust_wrap_sub(i, 1)] + fConst494 * fRec123[faust_wrap_sub(i, 2)]) - fConst496 * (fConst497 * fRec122[faust_wrap_sub(i, 2)] + fConst498 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec122_perm[j289] = fRec122_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 223 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec121_tmp[j290] = fRec121_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst496 * (fConst499 * fRec122[i] + fConst500 * fRec122[faust_wrap_sub(i, 1)] + fConst499 * fRec122[faust_wrap_sub(i, 2)]) - fConst501 * (fConst502 * fRec121[faust_wrap_sub(i, 2)] + fConst503 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec121_perm[j291] = fRec121_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Vectorizable loop 224 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec118[i] = fConst501 * (fConst504 * fRec121[i] + fConst505 * fRec121[faust_wrap_sub(i, 1)] + fConst504 * fRec121[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 225 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec120_tmp[j292] = fRec120_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fZec118[i] - fConst508 * (fConst509 * fRec120[faust_wrap_sub(i, 2)] + fConst512 * fRec120[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec120_perm[j293] = fRec120_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Recursive loop 226 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec119_tmp[j294] = fRec119_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fConst508 * (fConst514 * fRec120[i] + fConst515 * fRec120[faust_wrap_sub(i, 1)] + fConst514 * fRec120[faust_wrap_sub(i, 2)]) - fConst516 * (fConst517 * fRec119[faust_wrap_sub(i, 2)] + fConst518 * fRec119[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec119_perm[j295] = fRec119_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Recursive loop 227 */
			/* Pre code */
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec118_tmp[j296] = fRec118_perm[j296];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fConst516 * (fConst520 * fRec119[i] + fConst521 * fRec119[faust_wrap_sub(i, 1)] + fConst520 * fRec119[faust_wrap_sub(i, 2)]) - fConst522 * (fConst523 * fRec118[faust_wrap_sub(i, 2)] + fConst524 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec118_perm[j297] = fRec118_tmp[faust_wrap_add(vsize, j297)];
			}
			/* Recursive loop 228 */
			/* Pre code */
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec117_tmp[j298] = fRec117_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fSlow39 * fRec117[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst522 * (fConst526 * fRec118[i] + fConst527 * fRec118[faust_wrap_sub(i, 1)] + fConst526 * fRec118[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec117_perm[j299] = fRec117_tmp[faust_wrap_add(vsize, j299)];
			}
			/* Recursive loop 229 */
			/* Pre code */
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec127_tmp[j300] = fRec127_perm[j300];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fZec118[i] - fConst528 * (fConst529 * fRec127[faust_wrap_sub(i, 2)] + fConst530 * fRec127[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec127_perm[j301] = fRec127_tmp[faust_wrap_add(vsize, j301)];
			}
			/* Recursive loop 230 */
			/* Pre code */
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec126_tmp[j302] = fRec126_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fConst528 * (fConst532 * fRec127[i] + fConst533 * fRec127[faust_wrap_sub(i, 1)] + fConst532 * fRec127[faust_wrap_sub(i, 2)]) - fConst534 * (fConst535 * fRec126[faust_wrap_sub(i, 2)] + fConst536 * fRec126[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec126_perm[j303] = fRec126_tmp[faust_wrap_add(vsize, j303)];
			}
			/* Recursive loop 231 */
			/* Pre code */
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec125_tmp[j304] = fRec125_perm[j304];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fConst534 * (fConst537 * fRec126[i] + fConst538 * fRec126[faust_wrap_sub(i, 1)] + fConst537 * fRec126[faust_wrap_sub(i, 2)]) - fConst539 * (fConst540 * fRec125[faust_wrap_sub(i, 2)] + fConst541 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec125_perm[j305] = fRec125_tmp[faust_wrap_add(vsize, j305)];
			}
			/* Recursive loop 232 */
			/* Pre code */
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec124_tmp[j306] = fRec124_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fSlow39 * fRec124[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst539 * (fConst542 * fRec125[i] + fConst543 * fRec125[faust_wrap_sub(i, 1)] + fConst542 * fRec125[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec124_perm[j307] = fRec124_tmp[faust_wrap_add(vsize, j307)];
			}
			/* Recursive loop 233 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec32_tmp[j110] = fRec32_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fZec105[i] - fConst13 * (fConst14 * fRec32[faust_wrap_sub(i, 2)] + fConst17 * fRec32[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec32_perm[j111] = fRec32_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 234 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec31_tmp[j112] = fRec31_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fConst13 * (fConst19 * fRec32[i] + fConst20 * fRec32[faust_wrap_sub(i, 1)] + fConst19 * fRec32[faust_wrap_sub(i, 2)]) - fConst21 * (fConst22 * fRec31[faust_wrap_sub(i, 2)] + fConst23 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec31_perm[j113] = fRec31_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 235 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec30_tmp[j114] = fRec30_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst21 * (fConst25 * fRec31[i] + fConst26 * fRec31[faust_wrap_sub(i, 1)] + fConst25 * fRec31[faust_wrap_sub(i, 2)]) - fConst27 * (fConst28 * fRec30[faust_wrap_sub(i, 2)] + fConst29 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec30_perm[j115] = fRec30_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 236 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec29_tmp[j116] = fRec29_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fRec29[faust_wrap_sub(i, 1)] * fSlow39 + std::fabs(fConst27 * (fConst32 * fRec30[i] + fConst33 * fRec30[faust_wrap_sub(i, 1)] + fConst32 * fRec30[faust_wrap_sub(i, 2)])) * fSlow40;
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec29_perm[j117] = fRec29_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 237 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec36_tmp[j124] = fRec36_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fZec106[i] - fConst52 * (fConst53 * fRec36[faust_wrap_sub(i, 2)] + fConst56 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec36_perm[j125] = fRec36_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 238 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec35_tmp[j126] = fRec35_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fConst52 * (fConst58 * fRec36[i] + fConst59 * fRec36[faust_wrap_sub(i, 1)] + fConst58 * fRec36[faust_wrap_sub(i, 2)]) - fConst60 * (fConst61 * fRec35[faust_wrap_sub(i, 2)] + fConst62 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec35_perm[j127] = fRec35_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 239 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec34_tmp[j128] = fRec34_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst60 * (fConst64 * fRec35[i] + fConst65 * fRec35[faust_wrap_sub(i, 1)] + fConst64 * fRec35[faust_wrap_sub(i, 2)]) - fConst66 * (fConst67 * fRec34[faust_wrap_sub(i, 2)] + fConst68 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec34_perm[j129] = fRec34_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 240 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec33_tmp[j130] = fRec33_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fSlow39 * fRec33[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst66 * (fConst70 * fRec34[i] + fConst71 * fRec34[faust_wrap_sub(i, 1)] + fConst70 * fRec34[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec33_perm[j131] = fRec33_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 241 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec43_tmp[j138] = fRec43_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fZec107[i] - fConst90 * (fConst91 * fRec43[faust_wrap_sub(i, 2)] + fConst94 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec43_perm[j139] = fRec43_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 242 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec42_tmp[j140] = fRec42_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fConst90 * (fConst96 * fRec43[i] + fConst97 * fRec43[faust_wrap_sub(i, 1)] + fConst96 * fRec43[faust_wrap_sub(i, 2)]) - fConst98 * (fConst99 * fRec42[faust_wrap_sub(i, 2)] + fConst100 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec42_perm[j141] = fRec42_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 243 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec41_tmp[j142] = fRec41_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst98 * (fConst102 * fRec42[i] + fConst103 * fRec42[faust_wrap_sub(i, 1)] + fConst102 * fRec42[faust_wrap_sub(i, 2)]) - fConst104 * (fConst105 * fRec41[faust_wrap_sub(i, 2)] + fConst106 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec41_perm[j143] = fRec41_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 244 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec40_tmp[j144] = fRec40_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fSlow39 * fRec40[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst104 * (fConst108 * fRec41[i] + fConst109 * fRec41[faust_wrap_sub(i, 1)] + fConst108 * fRec41[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec40_perm[j145] = fRec40_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 245 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec50_tmp[j152] = fRec50_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fZec108[i] - fConst128 * (fConst129 * fRec50[faust_wrap_sub(i, 2)] + fConst132 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec50_perm[j153] = fRec50_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 246 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec49_tmp[j154] = fRec49_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fConst128 * (fConst134 * fRec50[i] + fConst135 * fRec50[faust_wrap_sub(i, 1)] + fConst134 * fRec50[faust_wrap_sub(i, 2)]) - fConst136 * (fConst137 * fRec49[faust_wrap_sub(i, 2)] + fConst138 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec49_perm[j155] = fRec49_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 247 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec48_tmp[j156] = fRec48_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst136 * (fConst140 * fRec49[i] + fConst141 * fRec49[faust_wrap_sub(i, 1)] + fConst140 * fRec49[faust_wrap_sub(i, 2)]) - fConst142 * (fConst143 * fRec48[faust_wrap_sub(i, 2)] + fConst144 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec48_perm[j157] = fRec48_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 248 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec47_tmp[j158] = fRec47_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fSlow39 * fRec47[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst142 * (fConst146 * fRec48[i] + fConst147 * fRec48[faust_wrap_sub(i, 1)] + fConst146 * fRec48[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec47_perm[j159] = fRec47_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 249 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec57_tmp[j166] = fRec57_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fZec109[i] - fConst166 * (fConst167 * fRec57[faust_wrap_sub(i, 2)] + fConst170 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec57_perm[j167] = fRec57_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 250 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec56_tmp[j168] = fRec56_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fConst166 * (fConst172 * fRec57[i] + fConst173 * fRec57[faust_wrap_sub(i, 1)] + fConst172 * fRec57[faust_wrap_sub(i, 2)]) - fConst174 * (fConst175 * fRec56[faust_wrap_sub(i, 2)] + fConst176 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec56_perm[j169] = fRec56_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 251 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec55_tmp[j170] = fRec55_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst174 * (fConst178 * fRec56[i] + fConst179 * fRec56[faust_wrap_sub(i, 1)] + fConst178 * fRec56[faust_wrap_sub(i, 2)]) - fConst180 * (fConst181 * fRec55[faust_wrap_sub(i, 2)] + fConst182 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec55_perm[j171] = fRec55_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 252 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec54_tmp[j172] = fRec54_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fSlow39 * fRec54[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst180 * (fConst184 * fRec55[i] + fConst185 * fRec55[faust_wrap_sub(i, 1)] + fConst184 * fRec55[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec54_perm[j173] = fRec54_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 253 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec64_tmp[j180] = fRec64_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fZec110[i] - fConst204 * (fConst205 * fRec64[faust_wrap_sub(i, 2)] + fConst208 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec64_perm[j181] = fRec64_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 254 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec63_tmp[j182] = fRec63_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fConst204 * (fConst210 * fRec64[i] + fConst211 * fRec64[faust_wrap_sub(i, 1)] + fConst210 * fRec64[faust_wrap_sub(i, 2)]) - fConst212 * (fConst213 * fRec63[faust_wrap_sub(i, 2)] + fConst214 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec63_perm[j183] = fRec63_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 255 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec62_tmp[j184] = fRec62_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst212 * (fConst216 * fRec63[i] + fConst217 * fRec63[faust_wrap_sub(i, 1)] + fConst216 * fRec63[faust_wrap_sub(i, 2)]) - fConst218 * (fConst219 * fRec62[faust_wrap_sub(i, 2)] + fConst220 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec62_perm[j185] = fRec62_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 256 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec61_tmp[j186] = fRec61_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fSlow39 * fRec61[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst218 * (fConst222 * fRec62[i] + fConst223 * fRec62[faust_wrap_sub(i, 1)] + fConst222 * fRec62[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec61_perm[j187] = fRec61_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 257 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec71_tmp[j194] = fRec71_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fZec111[i] - fConst242 * (fConst243 * fRec71[faust_wrap_sub(i, 2)] + fConst246 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec71_perm[j195] = fRec71_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 258 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec70_tmp[j196] = fRec70_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fConst242 * (fConst248 * fRec71[i] + fConst249 * fRec71[faust_wrap_sub(i, 1)] + fConst248 * fRec71[faust_wrap_sub(i, 2)]) - fConst250 * (fConst251 * fRec70[faust_wrap_sub(i, 2)] + fConst252 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec70_perm[j197] = fRec70_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 259 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec69_tmp[j198] = fRec69_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst250 * (fConst254 * fRec70[i] + fConst255 * fRec70[faust_wrap_sub(i, 1)] + fConst254 * fRec70[faust_wrap_sub(i, 2)]) - fConst256 * (fConst257 * fRec69[faust_wrap_sub(i, 2)] + fConst258 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec69_perm[j199] = fRec69_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 260 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec68_tmp[j200] = fRec68_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fSlow39 * fRec68[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst256 * (fConst260 * fRec69[i] + fConst261 * fRec69[faust_wrap_sub(i, 1)] + fConst260 * fRec69[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec68_perm[j201] = fRec68_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 261 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec78_tmp[j208] = fRec78_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fZec112[i] - fConst280 * (fConst281 * fRec78[faust_wrap_sub(i, 2)] + fConst284 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec78_perm[j209] = fRec78_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 262 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec77_tmp[j210] = fRec77_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fConst280 * (fConst286 * fRec78[i] + fConst287 * fRec78[faust_wrap_sub(i, 1)] + fConst286 * fRec78[faust_wrap_sub(i, 2)]) - fConst288 * (fConst289 * fRec77[faust_wrap_sub(i, 2)] + fConst290 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec77_perm[j211] = fRec77_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 263 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec76_tmp[j212] = fRec76_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst288 * (fConst292 * fRec77[i] + fConst293 * fRec77[faust_wrap_sub(i, 1)] + fConst292 * fRec77[faust_wrap_sub(i, 2)]) - fConst294 * (fConst295 * fRec76[faust_wrap_sub(i, 2)] + fConst296 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec76_perm[j213] = fRec76_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 264 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec75_tmp[j214] = fRec75_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fSlow39 * fRec75[faust_wrap_sub(i, 1)] + fSlow40 * std::fabs(fConst294 * (fConst298 * fRec76[i] + fConst299 * fRec76[faust_wrap_sub(i, 1)] + fConst298 * fRec76[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec75_perm[j215] = fRec75_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Vectorizable loop 265 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec29[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec33[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec40[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec47[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec54[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec61[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec68[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec75[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec82[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec89[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec96[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec103[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec110[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec117[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow41 + 2e+01 * std::log10(fRec124[i]));
				fZec119[i] = fZec105[i];
			}
			/* Vectorizable loop 266 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec119[i]);
			}
			/* Vectorizable loop 267 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec119[i]);
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
