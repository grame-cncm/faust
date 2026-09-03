/* ------------------------------------------------------------
name: "vcf_wah_pedals"
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
	double fRec12_perm[4];
	FAUSTFLOAT fHslider3;
	double fRec14_perm[4];
	FAUSTFLOAT fVslider0;
	double fRec15_perm[4];
	FAUSTFLOAT fVslider1;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider2;
	double fRec17_perm[4];
	double fRec16_perm[4];
	FAUSTFLOAT fVslider3;
	double fRec18_perm[4];
	FAUSTFLOAT fVslider4;
	double fRec19_perm[4];
	int iRec20_perm[4];
	double fRec21_perm[4];
	double fConst2;
	double fConst3;
	double fRec22_perm[4];
	double fRec23_perm[4];
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
	double fRec13_perm[4];
	double fConst7;
	FAUSTFLOAT fCheckbox4;
	double fRec11_perm[4];
	double fRec10_perm[4];
	double fRec9_perm[4];
	double fRec8_perm[4];
	double fRec7_perm[4];
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHslider4;
	double fRec5_perm[4];
	double fRec4_perm[4];
	double fRec3_perm[4];
	double fRec2_perm[4];
	double fRec1_perm[4];
	double fConst8;
	double fRec25_perm[4];
	double fRec24_perm[4];
	double fRec28_perm[4];
	double fRec26_perm[4];
	double fRec31_perm[4];
	double fRec29_perm[4];
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fCheckbox7;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fRec35_perm[4];
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fRec34_perm[4];
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fRec33_perm[4];
	FAUSTFLOAT fHslider5;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec32_perm[4];
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec42_perm[4];
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fRec41_perm[4];
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec40_perm[4];
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fRec39_perm[4];
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec38_perm[4];
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fRec37_perm[4];
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec36_perm[4];
	double fConst70;
	double fConst71;
	double fConst72;
	double fRec49_perm[4];
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fRec48_perm[4];
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fRec47_perm[4];
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fRec46_perm[4];
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fRec45_perm[4];
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fConst104;
	double fRec44_perm[4];
	double fConst105;
	double fConst106;
	double fConst107;
	double fRec43_perm[4];
	double fConst108;
	double fConst109;
	double fConst110;
	double fRec56_perm[4];
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fConst116;
	double fRec55_perm[4];
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fRec54_perm[4];
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fConst130;
	double fRec53_perm[4];
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fConst135;
	double fConst136;
	double fRec52_perm[4];
	double fConst137;
	double fConst138;
	double fConst139;
	double fConst140;
	double fConst141;
	double fConst142;
	double fRec51_perm[4];
	double fConst143;
	double fConst144;
	double fConst145;
	double fRec50_perm[4];
	double fConst146;
	double fConst147;
	double fConst148;
	double fRec63_perm[4];
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fConst154;
	double fRec62_perm[4];
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fRec61_perm[4];
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fRec60_perm[4];
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fConst173;
	double fConst174;
	double fRec59_perm[4];
	double fConst175;
	double fConst176;
	double fConst177;
	double fConst178;
	double fConst179;
	double fConst180;
	double fRec58_perm[4];
	double fConst181;
	double fConst182;
	double fConst183;
	double fRec57_perm[4];
	double fConst184;
	double fConst185;
	double fConst186;
	double fRec70_perm[4];
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst191;
	double fConst192;
	double fRec69_perm[4];
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fConst197;
	double fRec68_perm[4];
	double fConst198;
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fConst206;
	double fRec67_perm[4];
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fConst211;
	double fConst212;
	double fRec66_perm[4];
	double fConst213;
	double fConst214;
	double fConst215;
	double fConst216;
	double fConst217;
	double fConst218;
	double fRec65_perm[4];
	double fConst219;
	double fConst220;
	double fConst221;
	double fRec64_perm[4];
	double fConst222;
	double fConst223;
	double fConst224;
	double fRec77_perm[4];
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fConst229;
	double fConst230;
	double fRec76_perm[4];
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fRec75_perm[4];
	double fConst236;
	double fConst237;
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fConst243;
	double fConst244;
	double fRec74_perm[4];
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fConst249;
	double fConst250;
	double fRec73_perm[4];
	double fConst251;
	double fConst252;
	double fConst253;
	double fConst254;
	double fConst255;
	double fConst256;
	double fRec72_perm[4];
	double fConst257;
	double fConst258;
	double fConst259;
	double fRec71_perm[4];
	double fConst260;
	double fConst261;
	double fConst262;
	double fRec84_perm[4];
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fConst267;
	double fConst268;
	double fRec83_perm[4];
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fConst273;
	double fRec82_perm[4];
	double fConst274;
	double fConst275;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fConst281;
	double fConst282;
	double fRec81_perm[4];
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fConst287;
	double fConst288;
	double fRec80_perm[4];
	double fConst289;
	double fConst290;
	double fConst291;
	double fConst292;
	double fConst293;
	double fConst294;
	double fRec79_perm[4];
	double fConst295;
	double fConst296;
	double fConst297;
	double fRec78_perm[4];
	double fConst298;
	double fConst299;
	double fConst300;
	double fRec91_perm[4];
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fConst306;
	double fRec90_perm[4];
	double fConst307;
	double fConst308;
	double fConst309;
	double fConst310;
	double fConst311;
	double fRec89_perm[4];
	double fConst312;
	double fConst313;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fConst319;
	double fConst320;
	double fRec88_perm[4];
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fConst325;
	double fConst326;
	double fRec87_perm[4];
	double fConst327;
	double fConst328;
	double fConst329;
	double fConst330;
	double fConst331;
	double fConst332;
	double fRec86_perm[4];
	double fConst333;
	double fConst334;
	double fConst335;
	double fRec85_perm[4];
	double fConst336;
	double fConst337;
	double fConst338;
	double fRec98_perm[4];
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fConst343;
	double fConst344;
	double fRec97_perm[4];
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fConst349;
	double fRec96_perm[4];
	double fConst350;
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fConst357;
	double fConst358;
	double fRec95_perm[4];
	double fConst359;
	double fConst360;
	double fConst361;
	double fConst362;
	double fConst363;
	double fConst364;
	double fRec94_perm[4];
	double fConst365;
	double fConst366;
	double fConst367;
	double fConst368;
	double fConst369;
	double fConst370;
	double fRec93_perm[4];
	double fConst371;
	double fConst372;
	double fConst373;
	double fRec92_perm[4];
	double fConst374;
	double fConst375;
	double fConst376;
	double fRec105_perm[4];
	double fConst377;
	double fConst378;
	double fConst379;
	double fConst380;
	double fConst381;
	double fConst382;
	double fRec104_perm[4];
	double fConst383;
	double fConst384;
	double fConst385;
	double fConst386;
	double fConst387;
	double fRec103_perm[4];
	double fConst388;
	double fConst389;
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fConst395;
	double fConst396;
	double fRec102_perm[4];
	double fConst397;
	double fConst398;
	double fConst399;
	double fConst400;
	double fConst401;
	double fConst402;
	double fRec101_perm[4];
	double fConst403;
	double fConst404;
	double fConst405;
	double fConst406;
	double fConst407;
	double fConst408;
	double fRec100_perm[4];
	double fConst409;
	double fConst410;
	double fConst411;
	double fRec99_perm[4];
	double fConst412;
	double fConst413;
	double fConst414;
	double fRec112_perm[4];
	double fConst415;
	double fConst416;
	double fConst417;
	double fConst418;
	double fConst419;
	double fConst420;
	double fRec111_perm[4];
	double fConst421;
	double fConst422;
	double fConst423;
	double fConst424;
	double fConst425;
	double fRec110_perm[4];
	double fConst426;
	double fConst427;
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fConst433;
	double fConst434;
	double fRec109_perm[4];
	double fConst435;
	double fConst436;
	double fConst437;
	double fConst438;
	double fConst439;
	double fConst440;
	double fRec108_perm[4];
	double fConst441;
	double fConst442;
	double fConst443;
	double fConst444;
	double fConst445;
	double fConst446;
	double fRec107_perm[4];
	double fConst447;
	double fConst448;
	double fConst449;
	double fRec106_perm[4];
	double fConst450;
	double fConst451;
	double fConst452;
	double fRec119_perm[4];
	double fConst453;
	double fConst454;
	double fConst455;
	double fConst456;
	double fConst457;
	double fConst458;
	double fRec118_perm[4];
	double fConst459;
	double fConst460;
	double fConst461;
	double fConst462;
	double fConst463;
	double fRec117_perm[4];
	double fConst464;
	double fConst465;
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fConst470;
	double fConst471;
	double fConst472;
	double fRec116_perm[4];
	double fConst473;
	double fConst474;
	double fConst475;
	double fConst476;
	double fConst477;
	double fConst478;
	double fRec115_perm[4];
	double fConst479;
	double fConst480;
	double fConst481;
	double fConst482;
	double fConst483;
	double fConst484;
	double fRec114_perm[4];
	double fConst485;
	double fConst486;
	double fConst487;
	double fRec113_perm[4];
	double fConst488;
	double fConst489;
	double fConst490;
	double fRec126_perm[4];
	double fConst491;
	double fConst492;
	double fConst493;
	double fConst494;
	double fConst495;
	double fConst496;
	double fRec125_perm[4];
	double fConst497;
	double fConst498;
	double fConst499;
	double fConst500;
	double fConst501;
	double fRec124_perm[4];
	double fConst502;
	double fConst503;
	double fConst504;
	double fConst505;
	double fConst506;
	double fConst507;
	double fConst508;
	double fConst509;
	double fConst510;
	double fRec123_perm[4];
	double fConst511;
	double fConst512;
	double fConst513;
	double fConst514;
	double fConst515;
	double fConst516;
	double fRec122_perm[4];
	double fConst517;
	double fConst518;
	double fConst519;
	double fConst520;
	double fConst521;
	double fConst522;
	double fRec121_perm[4];
	double fConst523;
	double fConst524;
	double fConst525;
	double fRec120_perm[4];
	double fConst526;
	double fConst527;
	double fConst528;
	double fRec130_perm[4];
	double fConst529;
	double fConst530;
	double fConst531;
	double fConst532;
	double fConst533;
	double fConst534;
	double fRec129_perm[4];
	double fConst535;
	double fConst536;
	double fConst537;
	double fConst538;
	double fConst539;
	double fRec128_perm[4];
	double fConst540;
	double fConst541;
	double fRec127_perm[4];
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
		m->declare("effect.lib/crybaby:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/crybaby:copyright", "Julius O. Smith III");
		m->declare("effect.lib/crybaby:license", "STK-4.3");
		m->declare("effect.lib/crybaby_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/crybaby_demo:copyright", "Julius O. Smith III");
		m->declare("effect.lib/crybaby_demo:license", "STK-4.3");
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
		m->declare("effect.lib/wah4:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/wah4:copyright", "Julius O. Smith III");
		m->declare("effect.lib/wah4:license", "STK-4.3");
		m->declare("effect.lib/wah4_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/wah4_demo:copyright", "Julius O. Smith III");
		m->declare("effect.lib/wah4_demo:license", "STK-4.3");
		m->declare("filename", "vcf_wah_pedals.dsp");
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
		m->declare("name", "vcf_wah_pedals");
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
		fConst2 = 1413.7166941154069 / fConst0;
		fConst3 = 2827.4333882308138 / fConst0;
		fConst4 = 0.25 * fConst0;
		fConst5 = 0.041666666666666664 * mydsp_faustpower2_f(fConst0);
		fConst6 = 0.005208333333333333 * mydsp_faustpower3_f(fConst0);
		fConst7 = 6.283185307179586 / fConst0;
		fConst8 = 3.141592653589793 / fConst0;
		fConst9 = std::tan(50265.48245743669 / fConst0);
		fConst10 = 1.0 / fConst9;
		fConst11 = 1.0 / ((fConst10 + 3.1897274020965583) / fConst9 + 4.076781969643807);
		fConst12 = (fConst10 + -3.1897274020965583) / fConst9 + 4.076781969643807;
		fConst13 = mydsp_faustpower2_f(fConst9);
		fConst14 = 1.0 / fConst13;
		fConst15 = 2.0 * (4.076781969643807 - fConst14);
		fConst16 = 0.0017661728399818856 / fConst13;
		fConst17 = fConst16 + 0.00040767818495825777;
		fConst18 = 2.0 * (0.00040767818495825777 - fConst16);
		fConst19 = 1.0 / ((fConst10 + 0.7431304601070396) / fConst9 + 1.450071084655647);
		fConst20 = (fConst10 + -0.7431304601070396) / fConst9 + 1.450071084655647;
		fConst21 = 2.0 * (1.450071084655647 - fConst14);
		fConst22 = 11.052052171507189 / fConst13;
		fConst23 = fConst22 + 1.450071084655647;
		fConst24 = 2.0 * (1.450071084655647 - fConst22);
		fConst25 = 1.0 / ((fConst10 + 0.157482159302087) / fConst9 + 0.9351401670315425);
		fConst26 = (fConst10 + -0.157482159302087) / fConst9 + 0.9351401670315425;
		fConst27 = 2.0 * (0.9351401670315425 - fConst14);
		fConst28 = 1e+03 / fConst0;
		fConst29 = 50.063807016150385 / fConst13;
		fConst30 = fConst29 + 0.9351401670315425;
		fConst31 = 2.0 * (0.9351401670315425 - fConst29);
		fConst32 = 1.0 / ((fConst10 + 0.782413046821645) / fConst9 + 0.24529150870616);
		fConst33 = (fConst10 + -0.782413046821645) / fConst9 + 0.24529150870616;
		fConst34 = 2.0 * (0.24529150870616 - fConst14);
		fConst35 = 9.9999997055e-05 / fConst13;
		fConst36 = fConst35 + 0.000433227200555;
		fConst37 = 2.0 * (0.000433227200555 - fConst35);
		fConst38 = 1.0 / ((fConst10 + 0.512478641889141) / fConst9 + 0.689621364484675);
		fConst39 = (fConst10 + -0.512478641889141) / fConst9 + 0.689621364484675;
		fConst40 = 2.0 * (0.689621364484675 - fConst14);
		fConst41 = fConst14 + 7.621731298870603;
		fConst42 = 2.0 * (7.621731298870603 - fConst14);
		fConst43 = 1.0 / ((fConst10 + 0.168404871113589) / fConst9 + 1.069358407707312);
		fConst44 = (fConst10 + -0.168404871113589) / fConst9 + 1.069358407707312;
		fConst45 = 2.0 * (1.069358407707312 - fConst14);
		fConst46 = fConst14 + 53.53615295455673;
		fConst47 = 2.0 * (53.53615295455673 - fConst14);
		fConst48 = std::tan(31665.269715622984 / fConst0);
		fConst49 = 1.0 / fConst48;
		fConst50 = 1.0 / ((fConst49 + 3.1897274020965583) / fConst48 + 4.076781969643807);
		fConst51 = (fConst49 + -3.1897274020965583) / fConst48 + 4.076781969643807;
		fConst52 = mydsp_faustpower2_f(fConst48);
		fConst53 = 1.0 / fConst52;
		fConst54 = 2.0 * (4.076781969643807 - fConst53);
		fConst55 = 0.0017661728399818856 / fConst52;
		fConst56 = fConst55 + 0.00040767818495825777;
		fConst57 = 2.0 * (0.00040767818495825777 - fConst55);
		fConst58 = 1.0 / ((fConst49 + 0.7431304601070396) / fConst48 + 1.450071084655647);
		fConst59 = (fConst49 + -0.7431304601070396) / fConst48 + 1.450071084655647;
		fConst60 = 2.0 * (1.450071084655647 - fConst53);
		fConst61 = 11.052052171507189 / fConst52;
		fConst62 = fConst61 + 1.450071084655647;
		fConst63 = 2.0 * (1.450071084655647 - fConst61);
		fConst64 = 1.0 / ((fConst49 + 0.157482159302087) / fConst48 + 0.9351401670315425);
		fConst65 = (fConst49 + -0.157482159302087) / fConst48 + 0.9351401670315425;
		fConst66 = 2.0 * (0.9351401670315425 - fConst53);
		fConst67 = 50.063807016150385 / fConst52;
		fConst68 = fConst67 + 0.9351401670315425;
		fConst69 = 2.0 * (0.9351401670315425 - fConst67);
		fConst70 = 1.0 / ((fConst49 + 0.782413046821645) / fConst48 + 0.24529150870616);
		fConst71 = (fConst49 + -0.782413046821645) / fConst48 + 0.24529150870616;
		fConst72 = 2.0 * (0.24529150870616 - fConst53);
		fConst73 = 9.9999997055e-05 / fConst52;
		fConst74 = fConst73 + 0.000433227200555;
		fConst75 = 2.0 * (0.000433227200555 - fConst73);
		fConst76 = 1.0 / ((fConst49 + 0.512478641889141) / fConst48 + 0.689621364484675);
		fConst77 = (fConst49 + -0.512478641889141) / fConst48 + 0.689621364484675;
		fConst78 = 2.0 * (0.689621364484675 - fConst53);
		fConst79 = fConst53 + 7.621731298870603;
		fConst80 = 2.0 * (7.621731298870603 - fConst53);
		fConst81 = 1.0 / ((fConst49 + 0.168404871113589) / fConst48 + 1.069358407707312);
		fConst82 = (fConst49 + -0.168404871113589) / fConst48 + 1.069358407707312;
		fConst83 = 2.0 * (1.069358407707312 - fConst53);
		fConst84 = fConst53 + 53.53615295455673;
		fConst85 = 2.0 * (53.53615295455673 - fConst53);
		fConst86 = std::tan(19947.869932656024 / fConst0);
		fConst87 = 1.0 / fConst86;
		fConst88 = 1.0 / ((fConst87 + 3.1897274020965583) / fConst86 + 4.076781969643807);
		fConst89 = (fConst87 + -3.1897274020965583) / fConst86 + 4.076781969643807;
		fConst90 = mydsp_faustpower2_f(fConst86);
		fConst91 = 1.0 / fConst90;
		fConst92 = 2.0 * (4.076781969643807 - fConst91);
		fConst93 = 0.0017661728399818856 / fConst90;
		fConst94 = fConst93 + 0.00040767818495825777;
		fConst95 = 2.0 * (0.00040767818495825777 - fConst93);
		fConst96 = 1.0 / ((fConst87 + 0.7431304601070396) / fConst86 + 1.450071084655647);
		fConst97 = (fConst87 + -0.7431304601070396) / fConst86 + 1.450071084655647;
		fConst98 = 2.0 * (1.450071084655647 - fConst91);
		fConst99 = 11.052052171507189 / fConst90;
		fConst100 = fConst99 + 1.450071084655647;
		fConst101 = 2.0 * (1.450071084655647 - fConst99);
		fConst102 = 1.0 / ((fConst87 + 0.157482159302087) / fConst86 + 0.9351401670315425);
		fConst103 = (fConst87 + -0.157482159302087) / fConst86 + 0.9351401670315425;
		fConst104 = 2.0 * (0.9351401670315425 - fConst91);
		fConst105 = 50.063807016150385 / fConst90;
		fConst106 = fConst105 + 0.9351401670315425;
		fConst107 = 2.0 * (0.9351401670315425 - fConst105);
		fConst108 = 1.0 / ((fConst87 + 0.782413046821645) / fConst86 + 0.24529150870616);
		fConst109 = (fConst87 + -0.782413046821645) / fConst86 + 0.24529150870616;
		fConst110 = 2.0 * (0.24529150870616 - fConst91);
		fConst111 = 9.9999997055e-05 / fConst90;
		fConst112 = fConst111 + 0.000433227200555;
		fConst113 = 2.0 * (0.000433227200555 - fConst111);
		fConst114 = 1.0 / ((fConst87 + 0.512478641889141) / fConst86 + 0.689621364484675);
		fConst115 = (fConst87 + -0.512478641889141) / fConst86 + 0.689621364484675;
		fConst116 = 2.0 * (0.689621364484675 - fConst91);
		fConst117 = fConst91 + 7.621731298870603;
		fConst118 = 2.0 * (7.621731298870603 - fConst91);
		fConst119 = 1.0 / ((fConst87 + 0.168404871113589) / fConst86 + 1.069358407707312);
		fConst120 = (fConst87 + -0.168404871113589) / fConst86 + 1.069358407707312;
		fConst121 = 2.0 * (1.069358407707312 - fConst91);
		fConst122 = fConst91 + 53.53615295455673;
		fConst123 = 2.0 * (53.53615295455673 - fConst91);
		fConst124 = std::tan(12566.370614359172 / fConst0);
		fConst125 = 1.0 / fConst124;
		fConst126 = 1.0 / ((fConst125 + 3.1897274020965583) / fConst124 + 4.076781969643807);
		fConst127 = (fConst125 + -3.1897274020965583) / fConst124 + 4.076781969643807;
		fConst128 = mydsp_faustpower2_f(fConst124);
		fConst129 = 1.0 / fConst128;
		fConst130 = 2.0 * (4.076781969643807 - fConst129);
		fConst131 = 0.0017661728399818856 / fConst128;
		fConst132 = fConst131 + 0.00040767818495825777;
		fConst133 = 2.0 * (0.00040767818495825777 - fConst131);
		fConst134 = 1.0 / ((fConst125 + 0.7431304601070396) / fConst124 + 1.450071084655647);
		fConst135 = (fConst125 + -0.7431304601070396) / fConst124 + 1.450071084655647;
		fConst136 = 2.0 * (1.450071084655647 - fConst129);
		fConst137 = 11.052052171507189 / fConst128;
		fConst138 = fConst137 + 1.450071084655647;
		fConst139 = 2.0 * (1.450071084655647 - fConst137);
		fConst140 = 1.0 / ((fConst125 + 0.157482159302087) / fConst124 + 0.9351401670315425);
		fConst141 = (fConst125 + -0.157482159302087) / fConst124 + 0.9351401670315425;
		fConst142 = 2.0 * (0.9351401670315425 - fConst129);
		fConst143 = 50.063807016150385 / fConst128;
		fConst144 = fConst143 + 0.9351401670315425;
		fConst145 = 2.0 * (0.9351401670315425 - fConst143);
		fConst146 = 1.0 / ((fConst125 + 0.782413046821645) / fConst124 + 0.24529150870616);
		fConst147 = (fConst125 + -0.782413046821645) / fConst124 + 0.24529150870616;
		fConst148 = 2.0 * (0.24529150870616 - fConst129);
		fConst149 = 9.9999997055e-05 / fConst128;
		fConst150 = fConst149 + 0.000433227200555;
		fConst151 = 2.0 * (0.000433227200555 - fConst149);
		fConst152 = 1.0 / ((fConst125 + 0.512478641889141) / fConst124 + 0.689621364484675);
		fConst153 = (fConst125 + -0.512478641889141) / fConst124 + 0.689621364484675;
		fConst154 = 2.0 * (0.689621364484675 - fConst129);
		fConst155 = fConst129 + 7.621731298870603;
		fConst156 = 2.0 * (7.621731298870603 - fConst129);
		fConst157 = 1.0 / ((fConst125 + 0.168404871113589) / fConst124 + 1.069358407707312);
		fConst158 = (fConst125 + -0.168404871113589) / fConst124 + 1.069358407707312;
		fConst159 = 2.0 * (1.069358407707312 - fConst129);
		fConst160 = fConst129 + 53.53615295455673;
		fConst161 = 2.0 * (53.53615295455673 - fConst129);
		fConst162 = std::tan(7916.317428905746 / fConst0);
		fConst163 = 1.0 / fConst162;
		fConst164 = 1.0 / ((fConst163 + 3.1897274020965583) / fConst162 + 4.076781969643807);
		fConst165 = (fConst163 + -3.1897274020965583) / fConst162 + 4.076781969643807;
		fConst166 = mydsp_faustpower2_f(fConst162);
		fConst167 = 1.0 / fConst166;
		fConst168 = 2.0 * (4.076781969643807 - fConst167);
		fConst169 = 0.0017661728399818856 / fConst166;
		fConst170 = fConst169 + 0.00040767818495825777;
		fConst171 = 2.0 * (0.00040767818495825777 - fConst169);
		fConst172 = 1.0 / ((fConst163 + 0.7431304601070396) / fConst162 + 1.450071084655647);
		fConst173 = (fConst163 + -0.7431304601070396) / fConst162 + 1.450071084655647;
		fConst174 = 2.0 * (1.450071084655647 - fConst167);
		fConst175 = 11.052052171507189 / fConst166;
		fConst176 = fConst175 + 1.450071084655647;
		fConst177 = 2.0 * (1.450071084655647 - fConst175);
		fConst178 = 1.0 / ((fConst163 + 0.157482159302087) / fConst162 + 0.9351401670315425);
		fConst179 = (fConst163 + -0.157482159302087) / fConst162 + 0.9351401670315425;
		fConst180 = 2.0 * (0.9351401670315425 - fConst167);
		fConst181 = 50.063807016150385 / fConst166;
		fConst182 = fConst181 + 0.9351401670315425;
		fConst183 = 2.0 * (0.9351401670315425 - fConst181);
		fConst184 = 1.0 / ((fConst163 + 0.782413046821645) / fConst162 + 0.24529150870616);
		fConst185 = (fConst163 + -0.782413046821645) / fConst162 + 0.24529150870616;
		fConst186 = 2.0 * (0.24529150870616 - fConst167);
		fConst187 = 9.9999997055e-05 / fConst166;
		fConst188 = fConst187 + 0.000433227200555;
		fConst189 = 2.0 * (0.000433227200555 - fConst187);
		fConst190 = 1.0 / ((fConst163 + 0.512478641889141) / fConst162 + 0.689621364484675);
		fConst191 = (fConst163 + -0.512478641889141) / fConst162 + 0.689621364484675;
		fConst192 = 2.0 * (0.689621364484675 - fConst167);
		fConst193 = fConst167 + 7.621731298870603;
		fConst194 = 2.0 * (7.621731298870603 - fConst167);
		fConst195 = 1.0 / ((fConst163 + 0.168404871113589) / fConst162 + 1.069358407707312);
		fConst196 = (fConst163 + -0.168404871113589) / fConst162 + 1.069358407707312;
		fConst197 = 2.0 * (1.069358407707312 - fConst167);
		fConst198 = fConst167 + 53.53615295455673;
		fConst199 = 2.0 * (53.53615295455673 - fConst167);
		fConst200 = std::tan(4986.967483164005 / fConst0);
		fConst201 = 1.0 / fConst200;
		fConst202 = 1.0 / ((fConst201 + 3.1897274020965583) / fConst200 + 4.076781969643807);
		fConst203 = (fConst201 + -3.1897274020965583) / fConst200 + 4.076781969643807;
		fConst204 = mydsp_faustpower2_f(fConst200);
		fConst205 = 1.0 / fConst204;
		fConst206 = 2.0 * (4.076781969643807 - fConst205);
		fConst207 = 0.0017661728399818856 / fConst204;
		fConst208 = fConst207 + 0.00040767818495825777;
		fConst209 = 2.0 * (0.00040767818495825777 - fConst207);
		fConst210 = 1.0 / ((fConst201 + 0.7431304601070396) / fConst200 + 1.450071084655647);
		fConst211 = (fConst201 + -0.7431304601070396) / fConst200 + 1.450071084655647;
		fConst212 = 2.0 * (1.450071084655647 - fConst205);
		fConst213 = 11.052052171507189 / fConst204;
		fConst214 = fConst213 + 1.450071084655647;
		fConst215 = 2.0 * (1.450071084655647 - fConst213);
		fConst216 = 1.0 / ((fConst201 + 0.157482159302087) / fConst200 + 0.9351401670315425);
		fConst217 = (fConst201 + -0.157482159302087) / fConst200 + 0.9351401670315425;
		fConst218 = 2.0 * (0.9351401670315425 - fConst205);
		fConst219 = 50.063807016150385 / fConst204;
		fConst220 = fConst219 + 0.9351401670315425;
		fConst221 = 2.0 * (0.9351401670315425 - fConst219);
		fConst222 = 1.0 / ((fConst201 + 0.782413046821645) / fConst200 + 0.24529150870616);
		fConst223 = (fConst201 + -0.782413046821645) / fConst200 + 0.24529150870616;
		fConst224 = 2.0 * (0.24529150870616 - fConst205);
		fConst225 = 9.9999997055e-05 / fConst204;
		fConst226 = fConst225 + 0.000433227200555;
		fConst227 = 2.0 * (0.000433227200555 - fConst225);
		fConst228 = 1.0 / ((fConst201 + 0.512478641889141) / fConst200 + 0.689621364484675);
		fConst229 = (fConst201 + -0.512478641889141) / fConst200 + 0.689621364484675;
		fConst230 = 2.0 * (0.689621364484675 - fConst205);
		fConst231 = fConst205 + 7.621731298870603;
		fConst232 = 2.0 * (7.621731298870603 - fConst205);
		fConst233 = 1.0 / ((fConst201 + 0.168404871113589) / fConst200 + 1.069358407707312);
		fConst234 = (fConst201 + -0.168404871113589) / fConst200 + 1.069358407707312;
		fConst235 = 2.0 * (1.069358407707312 - fConst205);
		fConst236 = fConst205 + 53.53615295455673;
		fConst237 = 2.0 * (53.53615295455673 - fConst205);
		fConst238 = std::tan(3141.592653589793 / fConst0);
		fConst239 = 1.0 / fConst238;
		fConst240 = 1.0 / ((fConst239 + 3.1897274020965583) / fConst238 + 4.076781969643807);
		fConst241 = (fConst239 + -3.1897274020965583) / fConst238 + 4.076781969643807;
		fConst242 = mydsp_faustpower2_f(fConst238);
		fConst243 = 1.0 / fConst242;
		fConst244 = 2.0 * (4.076781969643807 - fConst243);
		fConst245 = 0.0017661728399818856 / fConst242;
		fConst246 = fConst245 + 0.00040767818495825777;
		fConst247 = 2.0 * (0.00040767818495825777 - fConst245);
		fConst248 = 1.0 / ((fConst239 + 0.7431304601070396) / fConst238 + 1.450071084655647);
		fConst249 = (fConst239 + -0.7431304601070396) / fConst238 + 1.450071084655647;
		fConst250 = 2.0 * (1.450071084655647 - fConst243);
		fConst251 = 11.052052171507189 / fConst242;
		fConst252 = fConst251 + 1.450071084655647;
		fConst253 = 2.0 * (1.450071084655647 - fConst251);
		fConst254 = 1.0 / ((fConst239 + 0.157482159302087) / fConst238 + 0.9351401670315425);
		fConst255 = (fConst239 + -0.157482159302087) / fConst238 + 0.9351401670315425;
		fConst256 = 2.0 * (0.9351401670315425 - fConst243);
		fConst257 = 50.063807016150385 / fConst242;
		fConst258 = fConst257 + 0.9351401670315425;
		fConst259 = 2.0 * (0.9351401670315425 - fConst257);
		fConst260 = 1.0 / ((fConst239 + 0.782413046821645) / fConst238 + 0.24529150870616);
		fConst261 = (fConst239 + -0.782413046821645) / fConst238 + 0.24529150870616;
		fConst262 = 2.0 * (0.24529150870616 - fConst243);
		fConst263 = 9.9999997055e-05 / fConst242;
		fConst264 = fConst263 + 0.000433227200555;
		fConst265 = 2.0 * (0.000433227200555 - fConst263);
		fConst266 = 1.0 / ((fConst239 + 0.512478641889141) / fConst238 + 0.689621364484675);
		fConst267 = (fConst239 + -0.512478641889141) / fConst238 + 0.689621364484675;
		fConst268 = 2.0 * (0.689621364484675 - fConst243);
		fConst269 = fConst243 + 7.621731298870603;
		fConst270 = 2.0 * (7.621731298870603 - fConst243);
		fConst271 = 1.0 / ((fConst239 + 0.168404871113589) / fConst238 + 1.069358407707312);
		fConst272 = (fConst239 + -0.168404871113589) / fConst238 + 1.069358407707312;
		fConst273 = 2.0 * (1.069358407707312 - fConst243);
		fConst274 = fConst243 + 53.53615295455673;
		fConst275 = 2.0 * (53.53615295455673 - fConst243);
		fConst276 = std::tan(1979.079357226436 / fConst0);
		fConst277 = 1.0 / fConst276;
		fConst278 = 1.0 / ((fConst277 + 3.1897274020965583) / fConst276 + 4.076781969643807);
		fConst279 = (fConst277 + -3.1897274020965583) / fConst276 + 4.076781969643807;
		fConst280 = mydsp_faustpower2_f(fConst276);
		fConst281 = 1.0 / fConst280;
		fConst282 = 2.0 * (4.076781969643807 - fConst281);
		fConst283 = 0.0017661728399818856 / fConst280;
		fConst284 = fConst283 + 0.00040767818495825777;
		fConst285 = 2.0 * (0.00040767818495825777 - fConst283);
		fConst286 = 1.0 / ((fConst277 + 0.7431304601070396) / fConst276 + 1.450071084655647);
		fConst287 = (fConst277 + -0.7431304601070396) / fConst276 + 1.450071084655647;
		fConst288 = 2.0 * (1.450071084655647 - fConst281);
		fConst289 = 11.052052171507189 / fConst280;
		fConst290 = fConst289 + 1.450071084655647;
		fConst291 = 2.0 * (1.450071084655647 - fConst289);
		fConst292 = 1.0 / ((fConst277 + 0.157482159302087) / fConst276 + 0.9351401670315425);
		fConst293 = (fConst277 + -0.157482159302087) / fConst276 + 0.9351401670315425;
		fConst294 = 2.0 * (0.9351401670315425 - fConst281);
		fConst295 = 50.063807016150385 / fConst280;
		fConst296 = fConst295 + 0.9351401670315425;
		fConst297 = 2.0 * (0.9351401670315425 - fConst295);
		fConst298 = 1.0 / ((fConst277 + 0.782413046821645) / fConst276 + 0.24529150870616);
		fConst299 = (fConst277 + -0.782413046821645) / fConst276 + 0.24529150870616;
		fConst300 = 2.0 * (0.24529150870616 - fConst281);
		fConst301 = 9.9999997055e-05 / fConst280;
		fConst302 = fConst301 + 0.000433227200555;
		fConst303 = 2.0 * (0.000433227200555 - fConst301);
		fConst304 = 1.0 / ((fConst277 + 0.512478641889141) / fConst276 + 0.689621364484675);
		fConst305 = (fConst277 + -0.512478641889141) / fConst276 + 0.689621364484675;
		fConst306 = 2.0 * (0.689621364484675 - fConst281);
		fConst307 = fConst281 + 7.621731298870603;
		fConst308 = 2.0 * (7.621731298870603 - fConst281);
		fConst309 = 1.0 / ((fConst277 + 0.168404871113589) / fConst276 + 1.069358407707312);
		fConst310 = (fConst277 + -0.168404871113589) / fConst276 + 1.069358407707312;
		fConst311 = 2.0 * (1.069358407707312 - fConst281);
		fConst312 = fConst281 + 53.53615295455673;
		fConst313 = 2.0 * (53.53615295455673 - fConst281);
		fConst314 = std::tan(1246.7418707910015 / fConst0);
		fConst315 = 1.0 / fConst314;
		fConst316 = 1.0 / ((fConst315 + 3.1897274020965583) / fConst314 + 4.076781969643807);
		fConst317 = (fConst315 + -3.1897274020965583) / fConst314 + 4.076781969643807;
		fConst318 = mydsp_faustpower2_f(fConst314);
		fConst319 = 1.0 / fConst318;
		fConst320 = 2.0 * (4.076781969643807 - fConst319);
		fConst321 = 0.0017661728399818856 / fConst318;
		fConst322 = fConst321 + 0.00040767818495825777;
		fConst323 = 2.0 * (0.00040767818495825777 - fConst321);
		fConst324 = 1.0 / ((fConst315 + 0.7431304601070396) / fConst314 + 1.450071084655647);
		fConst325 = (fConst315 + -0.7431304601070396) / fConst314 + 1.450071084655647;
		fConst326 = 2.0 * (1.450071084655647 - fConst319);
		fConst327 = 11.052052171507189 / fConst318;
		fConst328 = fConst327 + 1.450071084655647;
		fConst329 = 2.0 * (1.450071084655647 - fConst327);
		fConst330 = 1.0 / ((fConst315 + 0.157482159302087) / fConst314 + 0.9351401670315425);
		fConst331 = (fConst315 + -0.157482159302087) / fConst314 + 0.9351401670315425;
		fConst332 = 2.0 * (0.9351401670315425 - fConst319);
		fConst333 = 50.063807016150385 / fConst318;
		fConst334 = fConst333 + 0.9351401670315425;
		fConst335 = 2.0 * (0.9351401670315425 - fConst333);
		fConst336 = 1.0 / ((fConst315 + 0.782413046821645) / fConst314 + 0.24529150870616);
		fConst337 = (fConst315 + -0.782413046821645) / fConst314 + 0.24529150870616;
		fConst338 = 2.0 * (0.24529150870616 - fConst319);
		fConst339 = 9.9999997055e-05 / fConst318;
		fConst340 = fConst339 + 0.000433227200555;
		fConst341 = 2.0 * (0.000433227200555 - fConst339);
		fConst342 = 1.0 / ((fConst315 + 0.512478641889141) / fConst314 + 0.689621364484675);
		fConst343 = (fConst315 + -0.512478641889141) / fConst314 + 0.689621364484675;
		fConst344 = 2.0 * (0.689621364484675 - fConst319);
		fConst345 = fConst319 + 7.621731298870603;
		fConst346 = 2.0 * (7.621731298870603 - fConst319);
		fConst347 = 1.0 / ((fConst315 + 0.168404871113589) / fConst314 + 1.069358407707312);
		fConst348 = (fConst315 + -0.168404871113589) / fConst314 + 1.069358407707312;
		fConst349 = 2.0 * (1.069358407707312 - fConst319);
		fConst350 = fConst319 + 53.53615295455673;
		fConst351 = 2.0 * (53.53615295455673 - fConst319);
		fConst352 = std::tan(785.3981633974482 / fConst0);
		fConst353 = 1.0 / fConst352;
		fConst354 = 1.0 / ((fConst353 + 3.1897274020965583) / fConst352 + 4.076781969643807);
		fConst355 = (fConst353 + -3.1897274020965583) / fConst352 + 4.076781969643807;
		fConst356 = mydsp_faustpower2_f(fConst352);
		fConst357 = 1.0 / fConst356;
		fConst358 = 2.0 * (4.076781969643807 - fConst357);
		fConst359 = 0.0017661728399818856 / fConst356;
		fConst360 = fConst359 + 0.00040767818495825777;
		fConst361 = 2.0 * (0.00040767818495825777 - fConst359);
		fConst362 = 1.0 / ((fConst353 + 0.7431304601070396) / fConst352 + 1.450071084655647);
		fConst363 = (fConst353 + -0.7431304601070396) / fConst352 + 1.450071084655647;
		fConst364 = 2.0 * (1.450071084655647 - fConst357);
		fConst365 = 11.052052171507189 / fConst356;
		fConst366 = fConst365 + 1.450071084655647;
		fConst367 = 2.0 * (1.450071084655647 - fConst365);
		fConst368 = 1.0 / ((fConst353 + 0.157482159302087) / fConst352 + 0.9351401670315425);
		fConst369 = (fConst353 + -0.157482159302087) / fConst352 + 0.9351401670315425;
		fConst370 = 2.0 * (0.9351401670315425 - fConst357);
		fConst371 = 50.063807016150385 / fConst356;
		fConst372 = fConst371 + 0.9351401670315425;
		fConst373 = 2.0 * (0.9351401670315425 - fConst371);
		fConst374 = 1.0 / ((fConst353 + 0.782413046821645) / fConst352 + 0.24529150870616);
		fConst375 = (fConst353 + -0.782413046821645) / fConst352 + 0.24529150870616;
		fConst376 = 2.0 * (0.24529150870616 - fConst357);
		fConst377 = 9.9999997055e-05 / fConst356;
		fConst378 = fConst377 + 0.000433227200555;
		fConst379 = 2.0 * (0.000433227200555 - fConst377);
		fConst380 = 1.0 / ((fConst353 + 0.512478641889141) / fConst352 + 0.689621364484675);
		fConst381 = (fConst353 + -0.512478641889141) / fConst352 + 0.689621364484675;
		fConst382 = 2.0 * (0.689621364484675 - fConst357);
		fConst383 = fConst357 + 7.621731298870603;
		fConst384 = 2.0 * (7.621731298870603 - fConst357);
		fConst385 = 1.0 / ((fConst353 + 0.168404871113589) / fConst352 + 1.069358407707312);
		fConst386 = (fConst353 + -0.168404871113589) / fConst352 + 1.069358407707312;
		fConst387 = 2.0 * (1.069358407707312 - fConst357);
		fConst388 = fConst357 + 53.53615295455673;
		fConst389 = 2.0 * (53.53615295455673 - fConst357);
		fConst390 = std::tan(494.769839306609 / fConst0);
		fConst391 = 1.0 / fConst390;
		fConst392 = 1.0 / ((fConst391 + 3.1897274020965583) / fConst390 + 4.076781969643807);
		fConst393 = (fConst391 + -3.1897274020965583) / fConst390 + 4.076781969643807;
		fConst394 = mydsp_faustpower2_f(fConst390);
		fConst395 = 1.0 / fConst394;
		fConst396 = 2.0 * (4.076781969643807 - fConst395);
		fConst397 = 0.0017661728399818856 / fConst394;
		fConst398 = fConst397 + 0.00040767818495825777;
		fConst399 = 2.0 * (0.00040767818495825777 - fConst397);
		fConst400 = 1.0 / ((fConst391 + 0.7431304601070396) / fConst390 + 1.450071084655647);
		fConst401 = (fConst391 + -0.7431304601070396) / fConst390 + 1.450071084655647;
		fConst402 = 2.0 * (1.450071084655647 - fConst395);
		fConst403 = 11.052052171507189 / fConst394;
		fConst404 = fConst403 + 1.450071084655647;
		fConst405 = 2.0 * (1.450071084655647 - fConst403);
		fConst406 = 1.0 / ((fConst391 + 0.157482159302087) / fConst390 + 0.9351401670315425);
		fConst407 = (fConst391 + -0.157482159302087) / fConst390 + 0.9351401670315425;
		fConst408 = 2.0 * (0.9351401670315425 - fConst395);
		fConst409 = 50.063807016150385 / fConst394;
		fConst410 = fConst409 + 0.9351401670315425;
		fConst411 = 2.0 * (0.9351401670315425 - fConst409);
		fConst412 = 1.0 / ((fConst391 + 0.782413046821645) / fConst390 + 0.24529150870616);
		fConst413 = (fConst391 + -0.782413046821645) / fConst390 + 0.24529150870616;
		fConst414 = 2.0 * (0.24529150870616 - fConst395);
		fConst415 = 9.9999997055e-05 / fConst394;
		fConst416 = fConst415 + 0.000433227200555;
		fConst417 = 2.0 * (0.000433227200555 - fConst415);
		fConst418 = 1.0 / ((fConst391 + 0.512478641889141) / fConst390 + 0.689621364484675);
		fConst419 = (fConst391 + -0.512478641889141) / fConst390 + 0.689621364484675;
		fConst420 = 2.0 * (0.689621364484675 - fConst395);
		fConst421 = fConst395 + 7.621731298870603;
		fConst422 = 2.0 * (7.621731298870603 - fConst395);
		fConst423 = 1.0 / ((fConst391 + 0.168404871113589) / fConst390 + 1.069358407707312);
		fConst424 = (fConst391 + -0.168404871113589) / fConst390 + 1.069358407707312;
		fConst425 = 2.0 * (1.069358407707312 - fConst395);
		fConst426 = fConst395 + 53.53615295455673;
		fConst427 = 2.0 * (53.53615295455673 - fConst395);
		fConst428 = std::tan(311.68546769775037 / fConst0);
		fConst429 = 1.0 / fConst428;
		fConst430 = 1.0 / ((fConst429 + 3.1897274020965583) / fConst428 + 4.076781969643807);
		fConst431 = (fConst429 + -3.1897274020965583) / fConst428 + 4.076781969643807;
		fConst432 = mydsp_faustpower2_f(fConst428);
		fConst433 = 1.0 / fConst432;
		fConst434 = 2.0 * (4.076781969643807 - fConst433);
		fConst435 = 0.0017661728399818856 / fConst432;
		fConst436 = fConst435 + 0.00040767818495825777;
		fConst437 = 2.0 * (0.00040767818495825777 - fConst435);
		fConst438 = 1.0 / ((fConst429 + 0.7431304601070396) / fConst428 + 1.450071084655647);
		fConst439 = (fConst429 + -0.7431304601070396) / fConst428 + 1.450071084655647;
		fConst440 = 2.0 * (1.450071084655647 - fConst433);
		fConst441 = 11.052052171507189 / fConst432;
		fConst442 = fConst441 + 1.450071084655647;
		fConst443 = 2.0 * (1.450071084655647 - fConst441);
		fConst444 = 1.0 / ((fConst429 + 0.157482159302087) / fConst428 + 0.9351401670315425);
		fConst445 = (fConst429 + -0.157482159302087) / fConst428 + 0.9351401670315425;
		fConst446 = 2.0 * (0.9351401670315425 - fConst433);
		fConst447 = 50.063807016150385 / fConst432;
		fConst448 = fConst447 + 0.9351401670315425;
		fConst449 = 2.0 * (0.9351401670315425 - fConst447);
		fConst450 = 1.0 / ((fConst429 + 0.782413046821645) / fConst428 + 0.24529150870616);
		fConst451 = (fConst429 + -0.782413046821645) / fConst428 + 0.24529150870616;
		fConst452 = 2.0 * (0.24529150870616 - fConst433);
		fConst453 = 9.9999997055e-05 / fConst432;
		fConst454 = fConst453 + 0.000433227200555;
		fConst455 = 2.0 * (0.000433227200555 - fConst453);
		fConst456 = 1.0 / ((fConst429 + 0.512478641889141) / fConst428 + 0.689621364484675);
		fConst457 = (fConst429 + -0.512478641889141) / fConst428 + 0.689621364484675;
		fConst458 = 2.0 * (0.689621364484675 - fConst433);
		fConst459 = fConst433 + 7.621731298870603;
		fConst460 = 2.0 * (7.621731298870603 - fConst433);
		fConst461 = 1.0 / ((fConst429 + 0.168404871113589) / fConst428 + 1.069358407707312);
		fConst462 = (fConst429 + -0.168404871113589) / fConst428 + 1.069358407707312;
		fConst463 = 2.0 * (1.069358407707312 - fConst433);
		fConst464 = fConst433 + 53.53615295455673;
		fConst465 = 2.0 * (53.53615295455673 - fConst433);
		fConst466 = std::tan(196.34954084936206 / fConst0);
		fConst467 = 1.0 / fConst466;
		fConst468 = 1.0 / ((fConst467 + 3.1897274020965583) / fConst466 + 4.076781969643807);
		fConst469 = (fConst467 + -3.1897274020965583) / fConst466 + 4.076781969643807;
		fConst470 = mydsp_faustpower2_f(fConst466);
		fConst471 = 1.0 / fConst470;
		fConst472 = 2.0 * (4.076781969643807 - fConst471);
		fConst473 = 0.0017661728399818856 / fConst470;
		fConst474 = fConst473 + 0.00040767818495825777;
		fConst475 = 2.0 * (0.00040767818495825777 - fConst473);
		fConst476 = 1.0 / ((fConst467 + 0.7431304601070396) / fConst466 + 1.450071084655647);
		fConst477 = (fConst467 + -0.7431304601070396) / fConst466 + 1.450071084655647;
		fConst478 = 2.0 * (1.450071084655647 - fConst471);
		fConst479 = 11.052052171507189 / fConst470;
		fConst480 = fConst479 + 1.450071084655647;
		fConst481 = 2.0 * (1.450071084655647 - fConst479);
		fConst482 = 1.0 / ((fConst467 + 0.157482159302087) / fConst466 + 0.9351401670315425);
		fConst483 = (fConst467 + -0.157482159302087) / fConst466 + 0.9351401670315425;
		fConst484 = 2.0 * (0.9351401670315425 - fConst471);
		fConst485 = 50.063807016150385 / fConst470;
		fConst486 = fConst485 + 0.9351401670315425;
		fConst487 = 2.0 * (0.9351401670315425 - fConst485);
		fConst488 = 1.0 / ((fConst467 + 0.782413046821645) / fConst466 + 0.24529150870616);
		fConst489 = (fConst467 + -0.782413046821645) / fConst466 + 0.24529150870616;
		fConst490 = 2.0 * (0.24529150870616 - fConst471);
		fConst491 = 9.9999997055e-05 / fConst470;
		fConst492 = fConst491 + 0.000433227200555;
		fConst493 = 2.0 * (0.000433227200555 - fConst491);
		fConst494 = 1.0 / ((fConst467 + 0.512478641889141) / fConst466 + 0.689621364484675);
		fConst495 = (fConst467 + -0.512478641889141) / fConst466 + 0.689621364484675;
		fConst496 = 2.0 * (0.689621364484675 - fConst471);
		fConst497 = fConst471 + 7.621731298870603;
		fConst498 = 2.0 * (7.621731298870603 - fConst471);
		fConst499 = 1.0 / ((fConst467 + 0.168404871113589) / fConst466 + 1.069358407707312);
		fConst500 = (fConst467 + -0.168404871113589) / fConst466 + 1.069358407707312;
		fConst501 = 2.0 * (1.069358407707312 - fConst471);
		fConst502 = fConst471 + 53.53615295455673;
		fConst503 = 2.0 * (53.53615295455673 - fConst471);
		fConst504 = std::tan(123.69245982665232 / fConst0);
		fConst505 = 1.0 / fConst504;
		fConst506 = 1.0 / ((fConst505 + 3.1897274020965583) / fConst504 + 4.076781969643807);
		fConst507 = (fConst505 + -3.1897274020965583) / fConst504 + 4.076781969643807;
		fConst508 = mydsp_faustpower2_f(fConst504);
		fConst509 = 1.0 / fConst508;
		fConst510 = 2.0 * (4.076781969643807 - fConst509);
		fConst511 = 0.0017661728399818856 / fConst508;
		fConst512 = fConst511 + 0.00040767818495825777;
		fConst513 = 2.0 * (0.00040767818495825777 - fConst511);
		fConst514 = 1.0 / ((fConst505 + 0.7431304601070396) / fConst504 + 1.450071084655647);
		fConst515 = (fConst505 + -0.7431304601070396) / fConst504 + 1.450071084655647;
		fConst516 = 2.0 * (1.450071084655647 - fConst509);
		fConst517 = 11.052052171507189 / fConst508;
		fConst518 = fConst517 + 1.450071084655647;
		fConst519 = 2.0 * (1.450071084655647 - fConst517);
		fConst520 = 1.0 / ((fConst505 + 0.157482159302087) / fConst504 + 0.9351401670315425);
		fConst521 = (fConst505 + -0.157482159302087) / fConst504 + 0.9351401670315425;
		fConst522 = 2.0 * (0.9351401670315425 - fConst509);
		fConst523 = 50.063807016150385 / fConst508;
		fConst524 = fConst523 + 0.9351401670315425;
		fConst525 = 2.0 * (0.9351401670315425 - fConst523);
		fConst526 = 1.0 / ((fConst505 + 0.782413046821645) / fConst504 + 0.24529150870616);
		fConst527 = (fConst505 + -0.782413046821645) / fConst504 + 0.24529150870616;
		fConst528 = 2.0 * (0.24529150870616 - fConst509);
		fConst529 = 9.9999997055e-05 / fConst508;
		fConst530 = fConst529 + 0.000433227200555;
		fConst531 = 2.0 * (0.000433227200555 - fConst529);
		fConst532 = 1.0 / ((fConst505 + 0.512478641889141) / fConst504 + 0.689621364484675);
		fConst533 = (fConst505 + -0.512478641889141) / fConst504 + 0.689621364484675;
		fConst534 = 2.0 * (0.689621364484675 - fConst509);
		fConst535 = fConst509 + 7.621731298870603;
		fConst536 = 2.0 * (7.621731298870603 - fConst509);
		fConst537 = 1.0 / ((fConst505 + 0.168404871113589) / fConst504 + 1.069358407707312);
		fConst538 = (fConst505 + -0.168404871113589) / fConst504 + 1.069358407707312;
		fConst539 = 2.0 * (1.069358407707312 - fConst509);
		fConst540 = fConst509 + 53.53615295455673;
		fConst541 = 2.0 * (53.53615295455673 - fConst509);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(5.0);
		fHslider1 = static_cast<FAUSTFLOAT>(25.0);
		fHslider2 = static_cast<FAUSTFLOAT>(2e+02);
		fHslider3 = static_cast<FAUSTFLOAT>(0.8);
		fVslider0 = static_cast<FAUSTFLOAT>(-2e+01);
		fVslider1 = static_cast<FAUSTFLOAT>(0.1);
		fVslider2 = static_cast<FAUSTFLOAT>(49.0);
		fVslider3 = static_cast<FAUSTFLOAT>(-0.1);
		fVslider4 = static_cast<FAUSTFLOAT>(0.1);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry0 = static_cast<FAUSTFLOAT>(2.0);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox4 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox5 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(0.9);
		fCheckbox6 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox7 = static_cast<FAUSTFLOAT>(0.0);
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
			fRec12_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec14_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec15_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec17_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec16_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec18_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec19_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			iRec20_perm[l9] = 0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec21_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec22_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec23_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			iVec0_perm[l13] = 0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fYec0_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fYec1_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fYec2_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fYec3_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fYec4_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fYec5_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fYec6_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fYec7_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fYec8_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fYec9_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fYec10_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fYec11_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fYec12_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fYec13_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fYec14_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fYec15_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fYec16_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fYec17_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec13_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec11_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec10_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec9_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec8_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec7_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec5_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec4_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec3_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec2_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec1_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec25_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec24_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec28_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec26_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec31_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec29_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec35_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec34_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec33_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec32_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec42_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec41_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec40_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec39_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec38_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec37_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec36_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec49_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec48_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec47_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec46_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec45_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec44_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec43_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec56_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec55_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec54_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec53_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec52_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fRec51_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec50_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec63_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec62_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec61_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec60_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec59_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec58_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec57_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec70_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec69_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec68_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec67_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec66_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec65_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec64_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec77_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec76_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec75_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec74_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec73_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec72_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec71_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec84_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec83_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fRec82_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec81_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec80_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec79_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec78_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec91_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec90_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec89_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec88_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec87_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec86_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = faust_wrap_add(l108, 1)) {
			fRec85_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = faust_wrap_add(l109, 1)) {
			fRec98_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = faust_wrap_add(l110, 1)) {
			fRec97_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = faust_wrap_add(l111, 1)) {
			fRec96_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = faust_wrap_add(l112, 1)) {
			fRec95_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = faust_wrap_add(l113, 1)) {
			fRec94_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = faust_wrap_add(l114, 1)) {
			fRec93_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = faust_wrap_add(l115, 1)) {
			fRec92_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = faust_wrap_add(l116, 1)) {
			fRec105_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = faust_wrap_add(l117, 1)) {
			fRec104_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = faust_wrap_add(l118, 1)) {
			fRec103_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = faust_wrap_add(l119, 1)) {
			fRec102_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = faust_wrap_add(l120, 1)) {
			fRec101_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = faust_wrap_add(l121, 1)) {
			fRec100_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = faust_wrap_add(l122, 1)) {
			fRec99_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = faust_wrap_add(l123, 1)) {
			fRec112_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = faust_wrap_add(l124, 1)) {
			fRec111_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = faust_wrap_add(l125, 1)) {
			fRec110_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = faust_wrap_add(l126, 1)) {
			fRec109_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = faust_wrap_add(l127, 1)) {
			fRec108_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = faust_wrap_add(l128, 1)) {
			fRec107_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = faust_wrap_add(l129, 1)) {
			fRec106_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = faust_wrap_add(l130, 1)) {
			fRec119_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = faust_wrap_add(l131, 1)) {
			fRec118_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = faust_wrap_add(l132, 1)) {
			fRec117_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = faust_wrap_add(l133, 1)) {
			fRec116_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = faust_wrap_add(l134, 1)) {
			fRec115_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = faust_wrap_add(l135, 1)) {
			fRec114_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = faust_wrap_add(l136, 1)) {
			fRec113_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = faust_wrap_add(l137, 1)) {
			fRec126_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = faust_wrap_add(l138, 1)) {
			fRec125_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = faust_wrap_add(l139, 1)) {
			fRec124_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = faust_wrap_add(l140, 1)) {
			fRec123_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = faust_wrap_add(l141, 1)) {
			fRec122_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 4; l142 = faust_wrap_add(l142, 1)) {
			fRec121_perm[l142] = 0.0;
		}
		for (int l143 = 0; l143 < 4; l143 = faust_wrap_add(l143, 1)) {
			fRec120_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = faust_wrap_add(l144, 1)) {
			fRec130_perm[l144] = 0.0;
		}
		for (int l145 = 0; l145 < 4; l145 = faust_wrap_add(l145, 1)) {
			fRec129_perm[l145] = 0.0;
		}
		for (int l146 = 0; l146 < 4; l146 = faust_wrap_add(l146, 1)) {
			fRec128_perm[l146] = 0.0;
		}
		for (int l147 = 0; l147 < 4; l147 = faust_wrap_add(l147, 1)) {
			fRec127_perm[l147] = 0.0;
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
		ui_interface->openVerticalBox("vcf_wah_pedals");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
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
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/vegf.html");
		ui_interface->openHorizontalBox("CRYBABY");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the wah pedal has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "tooltip", "wah pedal angle between 0 (rocked back) and 1 (rocked forward)");
		ui_interface->addHorizontalSlider("Wah parameter", &fHslider3, FAUSTFLOAT(0.8), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Fourth-order wah effect made using moog_vcf");
		ui_interface->openHorizontalBox("WAH4");
		ui_interface->declare(&fCheckbox4, "0", "");
		ui_interface->declare(&fCheckbox4, "tooltip", "When this is checked, the wah pedal has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox4);
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "tooltip", "wah resonance frequency in Hz");
		ui_interface->addHorizontalSlider("Resonance Frequency", &fHslider2, FAUSTFLOAT(2e+02), FAUSTFLOAT(1e+02), FAUSTFLOAT(2e+03), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "See Faust's effect.lib for info and references");
		ui_interface->openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox5, "0", "");
		ui_interface->declare(&fCheckbox5, "tooltip", "When this is checked, the Moog VCF has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox5);
		ui_interface->declare(&fCheckbox6, "1", "");
		ui_interface->declare(&fCheckbox6, "tooltip", "Select moog_vcf_2b (two-biquad) implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface->addCheckButton("Use Biquads", &fCheckbox6);
		ui_interface->declare(&fCheckbox7, "2", "");
		ui_interface->declare(&fCheckbox7, "tooltip", "If using biquads, make them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fCheckbox7);
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
		ui_interface->declare(0, "5", "");
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
		double fSlow2 = 0.0010000000000000009 * static_cast<double>(fHslider2);
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fSlow3 = static_cast<double>(fHslider3);
		double fSlow4 = 0.0001000000000000001 * std::pow(4.0, fSlow3);
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fSlow5 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fSlow6 = static_cast<double>(fVslider1);
		double fSlow7 = ((fSlow6 > 0.0) ? std::exp(-(fConst1 / fSlow6)) : 0.0);
		double fSlow8 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fVslider2) + -49.0)) * (1.0 - fSlow7);
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fZec0[4];
		double fZec1[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fSlow9 = 0.01 * static_cast<double>(fVslider3) + 1.0;
		double fZec2[4];
		double fZec3[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fSlow10 = 0.01 * static_cast<double>(fVslider4) + 1.0;
		double fZec4[4];
		double fZec5[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		int iRec20_tmp[8];
		int* iRec20 = &iRec20_tmp[4];
		double fZec6[4];
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fSlow11 = std::pow(2.0, 2.3 * fSlow3);
		double fSlow12 = 1.0 - fConst2 * (fSlow11 / std::pow(2.0, 2.0 * (1.0 - fSlow3) + 1.0));
		double fSlow13 = 0.0020000000000000018 * fSlow12 * std::cos(fConst3 * fSlow11);
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fSlow14 = 0.0010000000000000009 * mydsp_faustpower2_f(fSlow12);
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		int iSlow15 = static_cast<int>(static_cast<double>(fCheckbox0));
		int iSlow16 = static_cast<int>(static_cast<double>(fCheckbox1));
		int iSlow17 = static_cast<int>(static_cast<double>(fCheckbox2));
		int iSlow18 = static_cast<int>(static_cast<double>(fEntry0) + -1.0);
		int iSlow19 = iSlow18 >= 2;
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		int iSlow20 = iSlow18 >= 1;
		double fZec7[4];
		double fZec8[4];
		double fZec9[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		int iSlow21 = iSlow18 >= 3;
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
		int iSlow22 = static_cast<int>(static_cast<double>(fCheckbox3));
		double fZec19[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fZec20[4];
		double fZec21[4];
		int iSlow23 = static_cast<int>(static_cast<double>(fCheckbox4));
		double fZec22[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fZec23[4];
		double fZec24[4];
		int iSlow24 = static_cast<int>(static_cast<double>(fCheckbox5));
		double fZec25[4];
		double fZec26[4];
		double fSlow25 = static_cast<double>(fHslider4);
		double fSlow26 = 4.0 * std::max<double>(0.0, std::min<double>(mydsp_faustpower4_f(fSlow25), 0.999999));
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
		double fSlow27 = std::min<double>(1.412799348810722, 1.4142135623730951 * fSlow25);
		double fSlow28 = 1.4142135623730951 * fSlow27;
		double fSlow29 = mydsp_faustpower2_f(fSlow27);
		double fSlow30 = fSlow28 + fSlow29;
		double fZec27[4];
		double fZec28[4];
		double fSlow31 = fSlow28 + 2.0;
		double fZec29[4];
		double fZec30[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fSlow32 = 2.0 - fSlow28;
		double fZec31[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fSlow33 = mydsp_faustpower2_f(1.412799348810722 * fSlow25);
		double fSlow34 = 1.9980000000000002 * fSlow25;
		double fSlow35 = fSlow33 + fSlow34;
		double fSlow36 = fSlow34 + 2.0;
		double fZec32[4];
		double fZec33[4];
		double fZec34[4];
		double fZec35[4];
		double fZec36[4];
		double fZec37[4];
		double fZec38[4];
		double fZec39[4];
		double fZec40[4];
		double fZec41[4];
		double fZec42[4];
		double fZec43[4];
		double fZec44[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec27[4];
		double fZec45[4];
		double fZec46[4];
		double fZec47[4];
		double fSlow37 = 2.0 - fSlow34;
		double fZec48[4];
		double fZec49[4];
		double fZec50[4];
		double fZec51[4];
		double fZec52[4];
		double fZec53[4];
		double fZec54[4];
		double fZec55[4];
		double fZec56[4];
		double fZec57[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		double fRec30[4];
		int iSlow38 = static_cast<int>(static_cast<double>(fCheckbox6));
		int iSlow39 = static_cast<int>(static_cast<double>(fCheckbox7));
		double fZec58[4];
		double fZec59[4];
		double fZec60[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fSlow40 = static_cast<double>(fHslider5);
		double fSlow41 = (((0.001 * fSlow40) > 0.0) ? std::exp(-(fConst28 / fSlow40)) : 0.0);
		double fSlow42 = 1.0 - fSlow41;
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fZec61[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fRec49_tmp[8];
		double* fRec49 = &fRec49_tmp[4];
		double fRec48_tmp[8];
		double* fRec48 = &fRec48_tmp[4];
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		double fZec62[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fRec56_tmp[8];
		double* fRec56 = &fRec56_tmp[4];
		double fRec55_tmp[8];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[8];
		double* fRec54 = &fRec54_tmp[4];
		double fZec63[4];
		double fRec53_tmp[8];
		double* fRec53 = &fRec53_tmp[4];
		double fRec52_tmp[8];
		double* fRec52 = &fRec52_tmp[4];
		double fRec51_tmp[8];
		double* fRec51 = &fRec51_tmp[4];
		double fRec50_tmp[8];
		double* fRec50 = &fRec50_tmp[4];
		double fRec63_tmp[8];
		double* fRec63 = &fRec63_tmp[4];
		double fRec62_tmp[8];
		double* fRec62 = &fRec62_tmp[4];
		double fRec61_tmp[8];
		double* fRec61 = &fRec61_tmp[4];
		double fZec64[4];
		double fRec60_tmp[8];
		double* fRec60 = &fRec60_tmp[4];
		double fRec59_tmp[8];
		double* fRec59 = &fRec59_tmp[4];
		double fRec58_tmp[8];
		double* fRec58 = &fRec58_tmp[4];
		double fRec57_tmp[8];
		double* fRec57 = &fRec57_tmp[4];
		double fRec70_tmp[8];
		double* fRec70 = &fRec70_tmp[4];
		double fRec69_tmp[8];
		double* fRec69 = &fRec69_tmp[4];
		double fRec68_tmp[8];
		double* fRec68 = &fRec68_tmp[4];
		double fZec65[4];
		double fRec67_tmp[8];
		double* fRec67 = &fRec67_tmp[4];
		double fRec66_tmp[8];
		double* fRec66 = &fRec66_tmp[4];
		double fRec65_tmp[8];
		double* fRec65 = &fRec65_tmp[4];
		double fRec64_tmp[8];
		double* fRec64 = &fRec64_tmp[4];
		double fRec77_tmp[8];
		double* fRec77 = &fRec77_tmp[4];
		double fRec76_tmp[8];
		double* fRec76 = &fRec76_tmp[4];
		double fRec75_tmp[8];
		double* fRec75 = &fRec75_tmp[4];
		double fZec66[4];
		double fRec74_tmp[8];
		double* fRec74 = &fRec74_tmp[4];
		double fRec73_tmp[8];
		double* fRec73 = &fRec73_tmp[4];
		double fRec72_tmp[8];
		double* fRec72 = &fRec72_tmp[4];
		double fRec71_tmp[8];
		double* fRec71 = &fRec71_tmp[4];
		double fRec84_tmp[8];
		double* fRec84 = &fRec84_tmp[4];
		double fRec83_tmp[8];
		double* fRec83 = &fRec83_tmp[4];
		double fRec82_tmp[8];
		double* fRec82 = &fRec82_tmp[4];
		double fZec67[4];
		double fRec81_tmp[8];
		double* fRec81 = &fRec81_tmp[4];
		double fRec80_tmp[8];
		double* fRec80 = &fRec80_tmp[4];
		double fRec79_tmp[8];
		double* fRec79 = &fRec79_tmp[4];
		double fRec78_tmp[8];
		double* fRec78 = &fRec78_tmp[4];
		double fRec91_tmp[8];
		double* fRec91 = &fRec91_tmp[4];
		double fRec90_tmp[8];
		double* fRec90 = &fRec90_tmp[4];
		double fRec89_tmp[8];
		double* fRec89 = &fRec89_tmp[4];
		double fZec68[4];
		double fRec88_tmp[8];
		double* fRec88 = &fRec88_tmp[4];
		double fRec87_tmp[8];
		double* fRec87 = &fRec87_tmp[4];
		double fRec86_tmp[8];
		double* fRec86 = &fRec86_tmp[4];
		double fRec85_tmp[8];
		double* fRec85 = &fRec85_tmp[4];
		double fRec98_tmp[8];
		double* fRec98 = &fRec98_tmp[4];
		double fRec97_tmp[8];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[8];
		double* fRec96 = &fRec96_tmp[4];
		double fZec69[4];
		double fRec95_tmp[8];
		double* fRec95 = &fRec95_tmp[4];
		double fRec94_tmp[8];
		double* fRec94 = &fRec94_tmp[4];
		double fRec93_tmp[8];
		double* fRec93 = &fRec93_tmp[4];
		double fRec92_tmp[8];
		double* fRec92 = &fRec92_tmp[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[8];
		double* fRec104 = &fRec104_tmp[4];
		double fRec103_tmp[8];
		double* fRec103 = &fRec103_tmp[4];
		double fZec70[4];
		double fRec102_tmp[8];
		double* fRec102 = &fRec102_tmp[4];
		double fRec101_tmp[8];
		double* fRec101 = &fRec101_tmp[4];
		double fRec100_tmp[8];
		double* fRec100 = &fRec100_tmp[4];
		double fRec99_tmp[8];
		double* fRec99 = &fRec99_tmp[4];
		double fRec112_tmp[8];
		double* fRec112 = &fRec112_tmp[4];
		double fRec111_tmp[8];
		double* fRec111 = &fRec111_tmp[4];
		double fRec110_tmp[8];
		double* fRec110 = &fRec110_tmp[4];
		double fZec71[4];
		double fRec109_tmp[8];
		double* fRec109 = &fRec109_tmp[4];
		double fRec108_tmp[8];
		double* fRec108 = &fRec108_tmp[4];
		double fRec107_tmp[8];
		double* fRec107 = &fRec107_tmp[4];
		double fRec106_tmp[8];
		double* fRec106 = &fRec106_tmp[4];
		double fRec119_tmp[8];
		double* fRec119 = &fRec119_tmp[4];
		double fRec118_tmp[8];
		double* fRec118 = &fRec118_tmp[4];
		double fRec117_tmp[8];
		double* fRec117 = &fRec117_tmp[4];
		double fZec72[4];
		double fRec116_tmp[8];
		double* fRec116 = &fRec116_tmp[4];
		double fRec115_tmp[8];
		double* fRec115 = &fRec115_tmp[4];
		double fRec114_tmp[8];
		double* fRec114 = &fRec114_tmp[4];
		double fRec113_tmp[8];
		double* fRec113 = &fRec113_tmp[4];
		double fRec126_tmp[8];
		double* fRec126 = &fRec126_tmp[4];
		double fRec125_tmp[8];
		double* fRec125 = &fRec125_tmp[4];
		double fRec124_tmp[8];
		double* fRec124 = &fRec124_tmp[4];
		double fZec73[4];
		double fRec123_tmp[8];
		double* fRec123 = &fRec123_tmp[4];
		double fRec122_tmp[8];
		double* fRec122 = &fRec122_tmp[4];
		double fRec121_tmp[8];
		double* fRec121 = &fRec121_tmp[4];
		double fRec120_tmp[8];
		double* fRec120 = &fRec120_tmp[4];
		double fRec130_tmp[8];
		double* fRec130 = &fRec130_tmp[4];
		double fRec129_tmp[8];
		double* fRec129 = &fRec129_tmp[4];
		double fRec128_tmp[8];
		double* fRec128 = &fRec128_tmp[4];
		double fRec127_tmp[8];
		double* fRec127 = &fRec127_tmp[4];
		double fSlow43 = static_cast<double>(fHslider6);
		double fZec74[4];
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
				fRec12_tmp[j4] = fRec12_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fSlow2 + 0.999 * fRec12[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec12_perm[j5] = fRec12_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec14_tmp[j6] = fRec14_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fSlow4 + 0.999 * fRec14[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec14_perm[j7] = fRec14_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec15_tmp[j8] = fRec15_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fSlow5 + 0.999 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec15_perm[j9] = fRec15_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec17_tmp[j10] = fRec17_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] * fSlow7 + fSlow8;
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec17_perm[j11] = fRec17_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec17[i]));
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec16_tmp[j12] = fRec16_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec16[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec16[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec16_perm[j13] = fRec16_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow9 * fRec17[i]));
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec18_tmp[j14] = fRec18_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec18[faust_wrap_sub(i, 1)] + fConst1 * fZec2[i];
				fRec18[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec18_perm[j15] = fRec18_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow10 * fRec17[i]));
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec19_tmp[j16] = fRec19_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fRec19[faust_wrap_sub(i, 1)] + fConst1 * fZec4[i];
				fRec19[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec19_perm[j17] = fRec19_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				iRec20_tmp[j18] = iRec20_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec20[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec20[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				iRec20_perm[j19] = iRec20_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec20[i]);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec21_tmp[j20] = fRec21_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = 0.5221894 * fRec21[faust_wrap_sub(i, 3)] + fZec6[i] + 2.494956002 * fRec21[faust_wrap_sub(i, 1)] - 2.017265875 * fRec21[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec21_perm[j21] = fRec21_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec22_tmp[j22] = fRec22_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = 0.999 * fRec22[faust_wrap_sub(i, 1)] - fSlow13;
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec22_perm[j23] = fRec22_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec23_tmp[j24] = fRec23_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fSlow14 + 0.999 * fRec23[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec23_perm[j25] = fRec23_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Vectorizable loop 17 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				iVec0_tmp[j26] = iVec0_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				iVec0_perm[j27] = iVec0_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 2.0 * fRec16[i];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fZec7[i] + -1.0;
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fYec0_tmp[j28] = fYec0_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = mydsp_faustpower2_f(fZec8[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fYec0_perm[j29] = fYec0_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 2)]);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = mydsp_faustpower3_f(fZec8[i]);
			}
			/* Vectorizable loop 24 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fYec1_tmp[j30] = fYec1_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fZec11[i] + (1.0 - fZec7[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fYec1_perm[j31] = fYec1_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 25 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fYec2_tmp[j32] = fYec2_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[i] = (fZec11[i] + (1.0 - (fZec7[i] + fYec1[faust_wrap_sub(i, 1)]))) / fZec0[i];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fYec2_perm[j33] = fYec2_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 3)]);
			}
			/* Vectorizable loop 27 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fYec3_tmp[j34] = fYec3_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fYec3_perm[j35] = fYec3_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fYec4_tmp[j36] = fYec4_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[i] = (fYec3[i] - fYec3[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fYec4_perm[j37] = fYec4_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fYec5_tmp[j38] = fYec5_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[i] = (fYec4[i] - fYec4[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fYec5_perm[j39] = fYec5_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = 2.0 * fRec18[i];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fZec13[i] + -1.0;
			}
			/* Vectorizable loop 32 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fYec6_tmp[j40] = fYec6_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[i] = mydsp_faustpower2_f(fZec14[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fYec6_perm[j41] = fYec6_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = mydsp_faustpower3_f(fZec14[i]);
			}
			/* Vectorizable loop 34 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fYec7_tmp[j42] = fYec7_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[i] = fZec15[i] + (1.0 - fZec13[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fYec7_perm[j43] = fYec7_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec8_tmp[j44] = fYec8_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[i] = (fZec15[i] + (1.0 - (fZec13[i] + fYec7[faust_wrap_sub(i, 1)]))) / fZec2[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec8_perm[j45] = fYec8_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 36 */
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
			/* Vectorizable loop 37 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fYec10_tmp[j48] = fYec10_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[i] = (fYec9[i] - fYec9[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fYec10_perm[j49] = fYec10_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 38 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fYec11_tmp[j50] = fYec11_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[i] = (fYec10[i] - fYec10[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fYec11_perm[j51] = fYec11_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = 2.0 * fRec19[i];
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fZec16[i] + -1.0;
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec12_tmp[j52] = fYec12_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[i] = mydsp_faustpower2_f(fZec17[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec12_perm[j53] = fYec12_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = mydsp_faustpower3_f(fZec17[i]);
			}
			/* Vectorizable loop 43 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fYec13_tmp[j54] = fYec13_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[i] = fZec18[i] + (1.0 - fZec16[i]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fYec13_perm[j55] = fYec13_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 44 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fYec14_tmp[j56] = fYec14_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[i] = (fZec18[i] + (1.0 - (fZec16[i] + fYec13[faust_wrap_sub(i, 1)]))) / fZec4[i];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fYec14_perm[j57] = fYec14_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 45 */
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
			/* Vectorizable loop 46 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fYec16_tmp[j60] = fYec16_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[i] = (fYec15[i] - fYec15[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fYec16_perm[j61] = fYec16_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fYec17_tmp[j62] = fYec17_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[i] = (fYec16[i] - fYec16[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fYec17_perm[j63] = fYec17_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fRec15[i] * ((iSlow16) ? static_cast<double>(input0[i]) : ((iSlow17) ? ((iSlow22) ? 0.049922035 * fRec21[i] + 0.050612699 * fRec21[faust_wrap_sub(i, 2)] - (0.095993537 * fRec21[faust_wrap_sub(i, 1)] + 0.004408786 * fRec21[faust_wrap_sub(i, 3)]) : fZec6[i]) : 0.3333333333333333 * fRec15[i] * (((iSlow19) ? ((iSlow21) ? fConst6 * (fZec12[i] * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst5 * (fZec10[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow20) ? fConst4 * (fZec9[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec8[i])) + ((iSlow19) ? ((iSlow21) ? fConst6 * (fZec12[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec2[i]) : fConst5 * (fZec10[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec2[i])) : ((iSlow20) ? fConst4 * (fZec9[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec2[i]) : fZec14[i])) + ((iSlow19) ? ((iSlow21) ? fConst6 * (fZec12[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec4[i]) : fConst5 * (fZec10[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec4[i])) : ((iSlow20) ? fConst4 * (fZec9[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec4[i]) : fZec17[i])))));
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec13_tmp[j64] = fRec13_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fRec14[i] * ((iSlow15) ? 0.0 : fZec19[i]) - (fRec22[i] * fRec13[faust_wrap_sub(i, 1)] + fRec23[i] * fRec13[faust_wrap_sub(i, 2)]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec13_perm[j65] = fRec13_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = fConst7 * fRec12[i];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = 1.0 - fZec20[i];
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = ((iSlow15) ? fZec19[i] : fRec13[i] - fRec13[faust_wrap_sub(i, 1)]);
			}
			/* Recursive loop 53 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec11_tmp[j66] = fRec11_perm[j66];
			}
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec10_tmp[j68] = fRec10_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec9_tmp[j70] = fRec9_perm[j70];
			}
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec8_tmp[j72] = fRec8_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec7_tmp[j74] = fRec7_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fZec21[i] * fRec11[faust_wrap_sub(i, 1)] + ((iSlow23) ? 0.0 : fZec22[i]) - 3.2 * fRec7[faust_wrap_sub(i, 1)];
				fRec10[i] = fRec11[i] + fZec21[i] * fRec10[faust_wrap_sub(i, 1)];
				fRec9[i] = fRec10[i] + fZec21[i] * fRec9[faust_wrap_sub(i, 1)];
				fRec8[i] = fRec9[i] + fRec8[faust_wrap_sub(i, 1)] * fZec21[i];
				fRec7[i] = fRec8[i] * mydsp_faustpower4_f(fZec20[i]);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec11_perm[j67] = fRec11_tmp[faust_wrap_add(vsize, j67)];
			}
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec10_perm[j69] = fRec10_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec9_perm[j71] = fRec9_tmp[faust_wrap_add(vsize, j71)];
			}
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec8_perm[j73] = fRec8_tmp[faust_wrap_add(vsize, j73)];
			}
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec7_perm[j75] = fRec7_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fConst7 * fRec6[i];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = 1.0 - fZec23[i];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = ((iSlow23) ? fZec22[i] : 4.0 * fRec7[i]);
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = ((iSlow24) ? 0.0 : fZec25[i]);
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec5_tmp[j76] = fRec5_perm[j76];
			}
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec4_tmp[j78] = fRec4_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec3_tmp[j80] = fRec3_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec2_tmp[j82] = fRec2_perm[j82];
			}
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec1_tmp[j84] = fRec1_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fZec24[i] * fRec5[faust_wrap_sub(i, 1)] + fZec26[i] - fSlow26 * fRec1[faust_wrap_sub(i, 1)];
				fRec4[i] = fRec5[i] + fZec24[i] * fRec4[faust_wrap_sub(i, 1)];
				fRec3[i] = fRec4[i] + fZec24[i] * fRec3[faust_wrap_sub(i, 1)];
				fRec2[i] = fRec3[i] + fRec2[faust_wrap_sub(i, 1)] * fZec24[i];
				fRec1[i] = fRec2[i] * mydsp_faustpower4_f(fZec23[i]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec5_perm[j77] = fRec5_tmp[faust_wrap_add(vsize, j77)];
			}
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec4_perm[j79] = fRec4_tmp[faust_wrap_add(vsize, j79)];
			}
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec3_perm[j81] = fRec3_tmp[faust_wrap_add(vsize, j81)];
			}
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec2_perm[j83] = fRec2_tmp[faust_wrap_add(vsize, j83)];
			}
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec1_perm[j85] = fRec1_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = std::tan(fConst8 * std::max<double>(2e+01, std::min<double>(1e+04, fRec6[i])));
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = 1.0 / fZec27[i];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec27[i]);
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = fSlow30 + (fSlow31 + fZec28[i]) / fZec27[i] + 1.0;
			}
			/* Recursive loop 63 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec25_tmp[j86] = fRec25_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fZec26[i] - (fRec25[faust_wrap_sub(i, 2)] * (fSlow30 + (fZec28[i] - fSlow31) / fZec27[i] + 1.0) + 2.0 * fRec25[faust_wrap_sub(i, 1)] * (fSlow30 + fZec29[i])) / fZec30[i];
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec25_perm[j87] = fRec25_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fSlow29 + ((fSlow32 + fZec28[i]) / fZec27[i] + 1.0 - fSlow28);
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec24_tmp[j88] = fRec24_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = (fRec25[faust_wrap_sub(i, 2)] + fRec25[i] + 2.0 * fRec25[faust_wrap_sub(i, 1)]) / fZec30[i] - (fRec24[faust_wrap_sub(i, 2)] * (fSlow29 + ((fZec28[i] - fSlow32) / fZec27[i] + 1.0 - fSlow28)) + 2.0 * fRec24[faust_wrap_sub(i, 1)] * (fSlow29 + (fZec29[i] - fSlow28))) / fZec31[i];
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec24_perm[j89] = fRec24_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = std::tan(fConst8 * std::max<double>(fRec6[i], 2e+01));
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = 1.0 / fZec32[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = fSlow35 + (fSlow36 + fZec33[i]) / fZec32[i] + 1.0;
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = (fSlow35 + (1.0 - (fSlow36 - fZec33[i]) / fZec32[i])) / fZec34[i];
			}
			/* Vectorizable loop 70 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec36[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec35[i]));
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec37[i] = 1.0 - mydsp_faustpower2_f(fZec36[i]);
			}
			/* Vectorizable loop 72 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec38[i] = std::sqrt(std::max<double>(0.0, fZec37[i]));
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec40[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec32[i]);
			}
			/* Vectorizable loop 74 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = fSlow35 + fZec40[i];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec41[i] / (fZec34[i] * (fZec35[i] + 1.0)))));
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = 1.0 - mydsp_faustpower2_f(fZec42[i]);
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec44[i] = std::sqrt(std::max<double>(0.0, fZec43[i]));
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec28_tmp[j90] = fRec28_perm[j90];
			}
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec26_tmp[j92] = fRec26_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec39[i] = fZec26[i] * fZec38[i] - fZec36[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec28[i] = fZec39[i] * fZec44[i] - fZec42[i] * fRec28[faust_wrap_sub(i, 1)];
				fRec26[i] = fZec39[i] * fZec42[i] + fRec28[faust_wrap_sub(i, 1)] * fZec44[i];
				fRec27[i] = fRec28[i];
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec28_perm[j91] = fRec28_tmp[faust_wrap_add(vsize, j91)];
			}
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec26_perm[j93] = fRec26_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec45[i] = 1.0 - fZec41[i] / fZec34[i];
			}
			/* Vectorizable loop 80 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec46[i] = std::sqrt(fZec37[i]);
			}
			/* Vectorizable loop 81 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec47[i] = fZec26[i] * fZec36[i] + fRec26[faust_wrap_sub(i, 1)] * fZec38[i] + 2.0 * (fRec26[i] * fZec45[i] / fZec46[i]) + fRec27[i] * (1.0 - fZec35[i] - 2.0 * fZec42[i] * fZec45[i]) / (fZec46[i] * std::sqrt(fZec43[i]));
			}
			/* Vectorizable loop 82 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec48[i] = fSlow33 + ((fSlow37 + fZec33[i]) / fZec32[i] + 1.0 - fSlow34);
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec49[i] = (fSlow33 + ((fZec33[i] - fSlow37) / fZec32[i] + 1.0 - fSlow34)) / fZec48[i];
			}
			/* Vectorizable loop 84 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec50[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec49[i]));
			}
			/* Vectorizable loop 85 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec51[i] = 1.0 - mydsp_faustpower2_f(fZec50[i]);
			}
			/* Vectorizable loop 86 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec52[i] = std::sqrt(std::max<double>(0.0, fZec51[i]));
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec54[i] = fSlow33 + (fZec40[i] - fSlow34);
			}
			/* Vectorizable loop 88 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec55[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec54[i] / (fZec48[i] * (fZec49[i] + 1.0)))));
			}
			/* Vectorizable loop 89 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec56[i] = 1.0 - mydsp_faustpower2_f(fZec55[i]);
			}
			/* Vectorizable loop 90 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec57[i] = std::sqrt(std::max<double>(0.0, fZec56[i]));
			}
			/* Recursive loop 91 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec31_tmp[j94] = fRec31_perm[j94];
			}
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec29_tmp[j96] = fRec29_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec53[i] = fZec47[i] * fZec52[i] / fZec34[i] - fZec50[i] * fRec29[faust_wrap_sub(i, 1)];
				fRec31[i] = fZec53[i] * fZec57[i] - fZec55[i] * fRec31[faust_wrap_sub(i, 1)];
				fRec29[i] = fZec53[i] * fZec55[i] + fRec31[faust_wrap_sub(i, 1)] * fZec57[i];
				fRec30[i] = fRec31[i];
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec31_perm[j95] = fRec31_tmp[faust_wrap_add(vsize, j95)];
			}
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec29_perm[j97] = fRec29_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 92 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec58[i] = 1.0 - fZec54[i] / fZec48[i];
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec59[i] = std::sqrt(fZec51[i]);
			}
			/* Vectorizable loop 94 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec60[i] = ((iSlow24) ? fZec25[i] : fRec0[i] * ((iSlow38) ? ((iSlow39) ? (fZec47[i] * fZec50[i] / fZec34[i] + fRec29[faust_wrap_sub(i, 1)] * fZec52[i] + 2.0 * (fRec29[i] * fZec58[i] / fZec59[i]) + fRec30[i] * (1.0 - fZec49[i] - 2.0 * fZec55[i] * fZec58[i]) / (fZec59[i] * std::sqrt(fZec56[i]))) / fZec48[i] : (fRec24[faust_wrap_sub(i, 2)] + fRec24[i] + 2.0 * fRec24[faust_wrap_sub(i, 1)]) / fZec31[i]) : fRec1[i]));
			}
			/* Recursive loop 95 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec35_tmp[j98] = fRec35_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fZec60[i] - fConst11 * (fConst12 * fRec35[faust_wrap_sub(i, 2)] + fConst15 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec35_perm[j99] = fRec35_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec34_tmp[j100] = fRec34_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst11 * (fConst17 * fRec35[i] + fConst18 * fRec35[faust_wrap_sub(i, 1)] + fConst17 * fRec35[faust_wrap_sub(i, 2)]) - fConst19 * (fConst20 * fRec34[faust_wrap_sub(i, 2)] + fConst21 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec34_perm[j101] = fRec34_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec33_tmp[j102] = fRec33_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst19 * (fConst23 * fRec34[i] + fConst24 * fRec34[faust_wrap_sub(i, 1)] + fConst23 * fRec34[faust_wrap_sub(i, 2)]) - fConst25 * (fConst26 * fRec33[faust_wrap_sub(i, 2)] + fConst27 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec33_perm[j103] = fRec33_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec32_tmp[j104] = fRec32_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fRec32[faust_wrap_sub(i, 1)] * fSlow41 + std::fabs(fConst25 * (fConst30 * fRec33[i] + fConst31 * fRec33[faust_wrap_sub(i, 1)] + fConst30 * fRec33[faust_wrap_sub(i, 2)])) * fSlow42;
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec32_perm[j105] = fRec32_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 99 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec42_tmp[j106] = fRec42_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fZec60[i] - fConst32 * (fConst33 * fRec42[faust_wrap_sub(i, 2)] + fConst34 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec42_perm[j107] = fRec42_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec41_tmp[j108] = fRec41_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst32 * (fConst36 * fRec42[i] + fConst37 * fRec42[faust_wrap_sub(i, 1)] + fConst36 * fRec42[faust_wrap_sub(i, 2)]) - fConst38 * (fConst39 * fRec41[faust_wrap_sub(i, 2)] + fConst40 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec41_perm[j109] = fRec41_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec40_tmp[j110] = fRec40_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst38 * (fConst41 * fRec41[i] + fConst42 * fRec41[faust_wrap_sub(i, 1)] + fConst41 * fRec41[faust_wrap_sub(i, 2)]) - fConst43 * (fConst44 * fRec40[faust_wrap_sub(i, 2)] + fConst45 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec40_perm[j111] = fRec40_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Vectorizable loop 102 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec61[i] = fConst43 * (fConst46 * fRec40[i] + fConst47 * fRec40[faust_wrap_sub(i, 1)] + fConst46 * fRec40[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 103 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec39_tmp[j112] = fRec39_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fZec61[i] - fConst50 * (fConst51 * fRec39[faust_wrap_sub(i, 2)] + fConst54 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec39_perm[j113] = fRec39_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec38_tmp[j114] = fRec38_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fConst50 * (fConst56 * fRec39[i] + fConst57 * fRec39[faust_wrap_sub(i, 1)] + fConst56 * fRec39[faust_wrap_sub(i, 2)]) - fConst58 * (fConst59 * fRec38[faust_wrap_sub(i, 2)] + fConst60 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec38_perm[j115] = fRec38_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec37_tmp[j116] = fRec37_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst58 * (fConst62 * fRec38[i] + fConst63 * fRec38[faust_wrap_sub(i, 1)] + fConst62 * fRec38[faust_wrap_sub(i, 2)]) - fConst64 * (fConst65 * fRec37[faust_wrap_sub(i, 2)] + fConst66 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec37_perm[j117] = fRec37_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec36_tmp[j118] = fRec36_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fSlow41 * fRec36[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst64 * (fConst68 * fRec37[i] + fConst69 * fRec37[faust_wrap_sub(i, 1)] + fConst68 * fRec37[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec36_perm[j119] = fRec36_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 107 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec49_tmp[j120] = fRec49_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fZec61[i] - fConst70 * (fConst71 * fRec49[faust_wrap_sub(i, 2)] + fConst72 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec49_perm[j121] = fRec49_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec48_tmp[j122] = fRec48_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst70 * (fConst74 * fRec49[i] + fConst75 * fRec49[faust_wrap_sub(i, 1)] + fConst74 * fRec49[faust_wrap_sub(i, 2)]) - fConst76 * (fConst77 * fRec48[faust_wrap_sub(i, 2)] + fConst78 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec48_perm[j123] = fRec48_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec47_tmp[j124] = fRec47_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst76 * (fConst79 * fRec48[i] + fConst80 * fRec48[faust_wrap_sub(i, 1)] + fConst79 * fRec48[faust_wrap_sub(i, 2)]) - fConst81 * (fConst82 * fRec47[faust_wrap_sub(i, 2)] + fConst83 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec47_perm[j125] = fRec47_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Vectorizable loop 110 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec62[i] = fConst81 * (fConst84 * fRec47[i] + fConst85 * fRec47[faust_wrap_sub(i, 1)] + fConst84 * fRec47[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 111 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec46_tmp[j126] = fRec46_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fZec62[i] - fConst88 * (fConst89 * fRec46[faust_wrap_sub(i, 2)] + fConst92 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec46_perm[j127] = fRec46_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec45_tmp[j128] = fRec45_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fConst88 * (fConst94 * fRec46[i] + fConst95 * fRec46[faust_wrap_sub(i, 1)] + fConst94 * fRec46[faust_wrap_sub(i, 2)]) - fConst96 * (fConst97 * fRec45[faust_wrap_sub(i, 2)] + fConst98 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec45_perm[j129] = fRec45_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec44_tmp[j130] = fRec44_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst96 * (fConst100 * fRec45[i] + fConst101 * fRec45[faust_wrap_sub(i, 1)] + fConst100 * fRec45[faust_wrap_sub(i, 2)]) - fConst102 * (fConst103 * fRec44[faust_wrap_sub(i, 2)] + fConst104 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec44_perm[j131] = fRec44_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec43_tmp[j132] = fRec43_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fSlow41 * fRec43[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst102 * (fConst106 * fRec44[i] + fConst107 * fRec44[faust_wrap_sub(i, 1)] + fConst106 * fRec44[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec43_perm[j133] = fRec43_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 115 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec56_tmp[j134] = fRec56_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fZec62[i] - fConst108 * (fConst109 * fRec56[faust_wrap_sub(i, 2)] + fConst110 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec56_perm[j135] = fRec56_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec55_tmp[j136] = fRec55_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst108 * (fConst112 * fRec56[i] + fConst113 * fRec56[faust_wrap_sub(i, 1)] + fConst112 * fRec56[faust_wrap_sub(i, 2)]) - fConst114 * (fConst115 * fRec55[faust_wrap_sub(i, 2)] + fConst116 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec55_perm[j137] = fRec55_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec54_tmp[j138] = fRec54_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst114 * (fConst117 * fRec55[i] + fConst118 * fRec55[faust_wrap_sub(i, 1)] + fConst117 * fRec55[faust_wrap_sub(i, 2)]) - fConst119 * (fConst120 * fRec54[faust_wrap_sub(i, 2)] + fConst121 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec54_perm[j139] = fRec54_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Vectorizable loop 118 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec63[i] = fConst119 * (fConst122 * fRec54[i] + fConst123 * fRec54[faust_wrap_sub(i, 1)] + fConst122 * fRec54[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 119 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec53_tmp[j140] = fRec53_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fZec63[i] - fConst126 * (fConst127 * fRec53[faust_wrap_sub(i, 2)] + fConst130 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec53_perm[j141] = fRec53_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec52_tmp[j142] = fRec52_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fConst126 * (fConst132 * fRec53[i] + fConst133 * fRec53[faust_wrap_sub(i, 1)] + fConst132 * fRec53[faust_wrap_sub(i, 2)]) - fConst134 * (fConst135 * fRec52[faust_wrap_sub(i, 2)] + fConst136 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec52_perm[j143] = fRec52_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec51_tmp[j144] = fRec51_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst134 * (fConst138 * fRec52[i] + fConst139 * fRec52[faust_wrap_sub(i, 1)] + fConst138 * fRec52[faust_wrap_sub(i, 2)]) - fConst140 * (fConst141 * fRec51[faust_wrap_sub(i, 2)] + fConst142 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec51_perm[j145] = fRec51_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec50_tmp[j146] = fRec50_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fSlow41 * fRec50[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst140 * (fConst144 * fRec51[i] + fConst145 * fRec51[faust_wrap_sub(i, 1)] + fConst144 * fRec51[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec50_perm[j147] = fRec50_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec63_tmp[j148] = fRec63_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fZec63[i] - fConst146 * (fConst147 * fRec63[faust_wrap_sub(i, 2)] + fConst148 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec63_perm[j149] = fRec63_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec62_tmp[j150] = fRec62_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst146 * (fConst150 * fRec63[i] + fConst151 * fRec63[faust_wrap_sub(i, 1)] + fConst150 * fRec63[faust_wrap_sub(i, 2)]) - fConst152 * (fConst153 * fRec62[faust_wrap_sub(i, 2)] + fConst154 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec62_perm[j151] = fRec62_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec61_tmp[j152] = fRec61_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst152 * (fConst155 * fRec62[i] + fConst156 * fRec62[faust_wrap_sub(i, 1)] + fConst155 * fRec62[faust_wrap_sub(i, 2)]) - fConst157 * (fConst158 * fRec61[faust_wrap_sub(i, 2)] + fConst159 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec61_perm[j153] = fRec61_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec64[i] = fConst157 * (fConst160 * fRec61[i] + fConst161 * fRec61[faust_wrap_sub(i, 1)] + fConst160 * fRec61[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec60_tmp[j154] = fRec60_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fZec64[i] - fConst164 * (fConst165 * fRec60[faust_wrap_sub(i, 2)] + fConst168 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec60_perm[j155] = fRec60_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec59_tmp[j156] = fRec59_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fConst164 * (fConst170 * fRec60[i] + fConst171 * fRec60[faust_wrap_sub(i, 1)] + fConst170 * fRec60[faust_wrap_sub(i, 2)]) - fConst172 * (fConst173 * fRec59[faust_wrap_sub(i, 2)] + fConst174 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec59_perm[j157] = fRec59_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec58_tmp[j158] = fRec58_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst172 * (fConst176 * fRec59[i] + fConst177 * fRec59[faust_wrap_sub(i, 1)] + fConst176 * fRec59[faust_wrap_sub(i, 2)]) - fConst178 * (fConst179 * fRec58[faust_wrap_sub(i, 2)] + fConst180 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec58_perm[j159] = fRec58_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec57_tmp[j160] = fRec57_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fSlow41 * fRec57[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst178 * (fConst182 * fRec58[i] + fConst183 * fRec58[faust_wrap_sub(i, 1)] + fConst182 * fRec58[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec57_perm[j161] = fRec57_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec70_tmp[j162] = fRec70_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fZec64[i] - fConst184 * (fConst185 * fRec70[faust_wrap_sub(i, 2)] + fConst186 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec70_perm[j163] = fRec70_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec69_tmp[j164] = fRec69_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst184 * (fConst188 * fRec70[i] + fConst189 * fRec70[faust_wrap_sub(i, 1)] + fConst188 * fRec70[faust_wrap_sub(i, 2)]) - fConst190 * (fConst191 * fRec69[faust_wrap_sub(i, 2)] + fConst192 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec69_perm[j165] = fRec69_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec68_tmp[j166] = fRec68_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst190 * (fConst193 * fRec69[i] + fConst194 * fRec69[faust_wrap_sub(i, 1)] + fConst193 * fRec69[faust_wrap_sub(i, 2)]) - fConst195 * (fConst196 * fRec68[faust_wrap_sub(i, 2)] + fConst197 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec68_perm[j167] = fRec68_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Vectorizable loop 134 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec65[i] = fConst195 * (fConst198 * fRec68[i] + fConst199 * fRec68[faust_wrap_sub(i, 1)] + fConst198 * fRec68[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec67_tmp[j168] = fRec67_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fZec65[i] - fConst202 * (fConst203 * fRec67[faust_wrap_sub(i, 2)] + fConst206 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec67_perm[j169] = fRec67_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec66_tmp[j170] = fRec66_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fConst202 * (fConst208 * fRec67[i] + fConst209 * fRec67[faust_wrap_sub(i, 1)] + fConst208 * fRec67[faust_wrap_sub(i, 2)]) - fConst210 * (fConst211 * fRec66[faust_wrap_sub(i, 2)] + fConst212 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec66_perm[j171] = fRec66_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec65_tmp[j172] = fRec65_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst210 * (fConst214 * fRec66[i] + fConst215 * fRec66[faust_wrap_sub(i, 1)] + fConst214 * fRec66[faust_wrap_sub(i, 2)]) - fConst216 * (fConst217 * fRec65[faust_wrap_sub(i, 2)] + fConst218 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec65_perm[j173] = fRec65_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec64_tmp[j174] = fRec64_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fSlow41 * fRec64[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst216 * (fConst220 * fRec65[i] + fConst221 * fRec65[faust_wrap_sub(i, 1)] + fConst220 * fRec65[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec64_perm[j175] = fRec64_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec77_tmp[j176] = fRec77_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fZec65[i] - fConst222 * (fConst223 * fRec77[faust_wrap_sub(i, 2)] + fConst224 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec77_perm[j177] = fRec77_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec76_tmp[j178] = fRec76_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst222 * (fConst226 * fRec77[i] + fConst227 * fRec77[faust_wrap_sub(i, 1)] + fConst226 * fRec77[faust_wrap_sub(i, 2)]) - fConst228 * (fConst229 * fRec76[faust_wrap_sub(i, 2)] + fConst230 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec76_perm[j179] = fRec76_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec75_tmp[j180] = fRec75_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst228 * (fConst231 * fRec76[i] + fConst232 * fRec76[faust_wrap_sub(i, 1)] + fConst231 * fRec76[faust_wrap_sub(i, 2)]) - fConst233 * (fConst234 * fRec75[faust_wrap_sub(i, 2)] + fConst235 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec75_perm[j181] = fRec75_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Vectorizable loop 142 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec66[i] = fConst233 * (fConst236 * fRec75[i] + fConst237 * fRec75[faust_wrap_sub(i, 1)] + fConst236 * fRec75[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec74_tmp[j182] = fRec74_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fZec66[i] - fConst240 * (fConst241 * fRec74[faust_wrap_sub(i, 2)] + fConst244 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec74_perm[j183] = fRec74_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec73_tmp[j184] = fRec73_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fConst240 * (fConst246 * fRec74[i] + fConst247 * fRec74[faust_wrap_sub(i, 1)] + fConst246 * fRec74[faust_wrap_sub(i, 2)]) - fConst248 * (fConst249 * fRec73[faust_wrap_sub(i, 2)] + fConst250 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec73_perm[j185] = fRec73_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec72_tmp[j186] = fRec72_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst248 * (fConst252 * fRec73[i] + fConst253 * fRec73[faust_wrap_sub(i, 1)] + fConst252 * fRec73[faust_wrap_sub(i, 2)]) - fConst254 * (fConst255 * fRec72[faust_wrap_sub(i, 2)] + fConst256 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec72_perm[j187] = fRec72_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec71_tmp[j188] = fRec71_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fSlow41 * fRec71[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst254 * (fConst258 * fRec72[i] + fConst259 * fRec72[faust_wrap_sub(i, 1)] + fConst258 * fRec72[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec71_perm[j189] = fRec71_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec84_tmp[j190] = fRec84_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fZec66[i] - fConst260 * (fConst261 * fRec84[faust_wrap_sub(i, 2)] + fConst262 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec84_perm[j191] = fRec84_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec83_tmp[j192] = fRec83_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst260 * (fConst264 * fRec84[i] + fConst265 * fRec84[faust_wrap_sub(i, 1)] + fConst264 * fRec84[faust_wrap_sub(i, 2)]) - fConst266 * (fConst267 * fRec83[faust_wrap_sub(i, 2)] + fConst268 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec83_perm[j193] = fRec83_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec82_tmp[j194] = fRec82_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst266 * (fConst269 * fRec83[i] + fConst270 * fRec83[faust_wrap_sub(i, 1)] + fConst269 * fRec83[faust_wrap_sub(i, 2)]) - fConst271 * (fConst272 * fRec82[faust_wrap_sub(i, 2)] + fConst273 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec82_perm[j195] = fRec82_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Vectorizable loop 150 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec67[i] = fConst271 * (fConst274 * fRec82[i] + fConst275 * fRec82[faust_wrap_sub(i, 1)] + fConst274 * fRec82[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec81_tmp[j196] = fRec81_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fZec67[i] - fConst278 * (fConst279 * fRec81[faust_wrap_sub(i, 2)] + fConst282 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec81_perm[j197] = fRec81_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec80_tmp[j198] = fRec80_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fConst278 * (fConst284 * fRec81[i] + fConst285 * fRec81[faust_wrap_sub(i, 1)] + fConst284 * fRec81[faust_wrap_sub(i, 2)]) - fConst286 * (fConst287 * fRec80[faust_wrap_sub(i, 2)] + fConst288 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec80_perm[j199] = fRec80_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec79_tmp[j200] = fRec79_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst286 * (fConst290 * fRec80[i] + fConst291 * fRec80[faust_wrap_sub(i, 1)] + fConst290 * fRec80[faust_wrap_sub(i, 2)]) - fConst292 * (fConst293 * fRec79[faust_wrap_sub(i, 2)] + fConst294 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec79_perm[j201] = fRec79_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec78_tmp[j202] = fRec78_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fSlow41 * fRec78[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst292 * (fConst296 * fRec79[i] + fConst297 * fRec79[faust_wrap_sub(i, 1)] + fConst296 * fRec79[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec78_perm[j203] = fRec78_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec91_tmp[j204] = fRec91_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fZec67[i] - fConst298 * (fConst299 * fRec91[faust_wrap_sub(i, 2)] + fConst300 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec91_perm[j205] = fRec91_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec90_tmp[j206] = fRec90_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst298 * (fConst302 * fRec91[i] + fConst303 * fRec91[faust_wrap_sub(i, 1)] + fConst302 * fRec91[faust_wrap_sub(i, 2)]) - fConst304 * (fConst305 * fRec90[faust_wrap_sub(i, 2)] + fConst306 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec90_perm[j207] = fRec90_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec89_tmp[j208] = fRec89_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst304 * (fConst307 * fRec90[i] + fConst308 * fRec90[faust_wrap_sub(i, 1)] + fConst307 * fRec90[faust_wrap_sub(i, 2)]) - fConst309 * (fConst310 * fRec89[faust_wrap_sub(i, 2)] + fConst311 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec89_perm[j209] = fRec89_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Vectorizable loop 158 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec68[i] = fConst309 * (fConst312 * fRec89[i] + fConst313 * fRec89[faust_wrap_sub(i, 1)] + fConst312 * fRec89[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec88_tmp[j210] = fRec88_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fZec68[i] - fConst316 * (fConst317 * fRec88[faust_wrap_sub(i, 2)] + fConst320 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec88_perm[j211] = fRec88_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec87_tmp[j212] = fRec87_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fConst316 * (fConst322 * fRec88[i] + fConst323 * fRec88[faust_wrap_sub(i, 1)] + fConst322 * fRec88[faust_wrap_sub(i, 2)]) - fConst324 * (fConst325 * fRec87[faust_wrap_sub(i, 2)] + fConst326 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec87_perm[j213] = fRec87_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec86_tmp[j214] = fRec86_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst324 * (fConst328 * fRec87[i] + fConst329 * fRec87[faust_wrap_sub(i, 1)] + fConst328 * fRec87[faust_wrap_sub(i, 2)]) - fConst330 * (fConst331 * fRec86[faust_wrap_sub(i, 2)] + fConst332 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec86_perm[j215] = fRec86_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec85_tmp[j216] = fRec85_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fSlow41 * fRec85[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst330 * (fConst334 * fRec86[i] + fConst335 * fRec86[faust_wrap_sub(i, 1)] + fConst334 * fRec86[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec85_perm[j217] = fRec85_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec98_tmp[j218] = fRec98_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fZec68[i] - fConst336 * (fConst337 * fRec98[faust_wrap_sub(i, 2)] + fConst338 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec98_perm[j219] = fRec98_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec97_tmp[j220] = fRec97_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst336 * (fConst340 * fRec98[i] + fConst341 * fRec98[faust_wrap_sub(i, 1)] + fConst340 * fRec98[faust_wrap_sub(i, 2)]) - fConst342 * (fConst343 * fRec97[faust_wrap_sub(i, 2)] + fConst344 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec97_perm[j221] = fRec97_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec96_tmp[j222] = fRec96_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst342 * (fConst345 * fRec97[i] + fConst346 * fRec97[faust_wrap_sub(i, 1)] + fConst345 * fRec97[faust_wrap_sub(i, 2)]) - fConst347 * (fConst348 * fRec96[faust_wrap_sub(i, 2)] + fConst349 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec96_perm[j223] = fRec96_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Vectorizable loop 166 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec69[i] = fConst347 * (fConst350 * fRec96[i] + fConst351 * fRec96[faust_wrap_sub(i, 1)] + fConst350 * fRec96[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec95_tmp[j224] = fRec95_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fZec69[i] - fConst354 * (fConst355 * fRec95[faust_wrap_sub(i, 2)] + fConst358 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec95_perm[j225] = fRec95_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec94_tmp[j226] = fRec94_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fConst354 * (fConst360 * fRec95[i] + fConst361 * fRec95[faust_wrap_sub(i, 1)] + fConst360 * fRec95[faust_wrap_sub(i, 2)]) - fConst362 * (fConst363 * fRec94[faust_wrap_sub(i, 2)] + fConst364 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec94_perm[j227] = fRec94_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec93_tmp[j228] = fRec93_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst362 * (fConst366 * fRec94[i] + fConst367 * fRec94[faust_wrap_sub(i, 1)] + fConst366 * fRec94[faust_wrap_sub(i, 2)]) - fConst368 * (fConst369 * fRec93[faust_wrap_sub(i, 2)] + fConst370 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec93_perm[j229] = fRec93_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec92_tmp[j230] = fRec92_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fSlow41 * fRec92[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst368 * (fConst372 * fRec93[i] + fConst373 * fRec93[faust_wrap_sub(i, 1)] + fConst372 * fRec93[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec92_perm[j231] = fRec92_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec105_tmp[j232] = fRec105_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fZec69[i] - fConst374 * (fConst375 * fRec105[faust_wrap_sub(i, 2)] + fConst376 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec105_perm[j233] = fRec105_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec104_tmp[j234] = fRec104_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst374 * (fConst378 * fRec105[i] + fConst379 * fRec105[faust_wrap_sub(i, 1)] + fConst378 * fRec105[faust_wrap_sub(i, 2)]) - fConst380 * (fConst381 * fRec104[faust_wrap_sub(i, 2)] + fConst382 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec104_perm[j235] = fRec104_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec103_tmp[j236] = fRec103_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst380 * (fConst383 * fRec104[i] + fConst384 * fRec104[faust_wrap_sub(i, 1)] + fConst383 * fRec104[faust_wrap_sub(i, 2)]) - fConst385 * (fConst386 * fRec103[faust_wrap_sub(i, 2)] + fConst387 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec103_perm[j237] = fRec103_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Vectorizable loop 174 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec70[i] = fConst385 * (fConst388 * fRec103[i] + fConst389 * fRec103[faust_wrap_sub(i, 1)] + fConst388 * fRec103[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec102_tmp[j238] = fRec102_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fZec70[i] - fConst392 * (fConst393 * fRec102[faust_wrap_sub(i, 2)] + fConst396 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec102_perm[j239] = fRec102_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec101_tmp[j240] = fRec101_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fConst392 * (fConst398 * fRec102[i] + fConst399 * fRec102[faust_wrap_sub(i, 1)] + fConst398 * fRec102[faust_wrap_sub(i, 2)]) - fConst400 * (fConst401 * fRec101[faust_wrap_sub(i, 2)] + fConst402 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec101_perm[j241] = fRec101_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec100_tmp[j242] = fRec100_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst400 * (fConst404 * fRec101[i] + fConst405 * fRec101[faust_wrap_sub(i, 1)] + fConst404 * fRec101[faust_wrap_sub(i, 2)]) - fConst406 * (fConst407 * fRec100[faust_wrap_sub(i, 2)] + fConst408 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec100_perm[j243] = fRec100_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec99_tmp[j244] = fRec99_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fSlow41 * fRec99[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst406 * (fConst410 * fRec100[i] + fConst411 * fRec100[faust_wrap_sub(i, 1)] + fConst410 * fRec100[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec99_perm[j245] = fRec99_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec112_tmp[j246] = fRec112_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fZec70[i] - fConst412 * (fConst413 * fRec112[faust_wrap_sub(i, 2)] + fConst414 * fRec112[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec112_perm[j247] = fRec112_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec111_tmp[j248] = fRec111_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fConst412 * (fConst416 * fRec112[i] + fConst417 * fRec112[faust_wrap_sub(i, 1)] + fConst416 * fRec112[faust_wrap_sub(i, 2)]) - fConst418 * (fConst419 * fRec111[faust_wrap_sub(i, 2)] + fConst420 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec111_perm[j249] = fRec111_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec110_tmp[j250] = fRec110_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst418 * (fConst421 * fRec111[i] + fConst422 * fRec111[faust_wrap_sub(i, 1)] + fConst421 * fRec111[faust_wrap_sub(i, 2)]) - fConst423 * (fConst424 * fRec110[faust_wrap_sub(i, 2)] + fConst425 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec110_perm[j251] = fRec110_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Vectorizable loop 182 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec71[i] = fConst423 * (fConst426 * fRec110[i] + fConst427 * fRec110[faust_wrap_sub(i, 1)] + fConst426 * fRec110[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec109_tmp[j252] = fRec109_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fZec71[i] - fConst430 * (fConst431 * fRec109[faust_wrap_sub(i, 2)] + fConst434 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec109_perm[j253] = fRec109_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 184 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec108_tmp[j254] = fRec108_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fConst430 * (fConst436 * fRec109[i] + fConst437 * fRec109[faust_wrap_sub(i, 1)] + fConst436 * fRec109[faust_wrap_sub(i, 2)]) - fConst438 * (fConst439 * fRec108[faust_wrap_sub(i, 2)] + fConst440 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec108_perm[j255] = fRec108_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec107_tmp[j256] = fRec107_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst438 * (fConst442 * fRec108[i] + fConst443 * fRec108[faust_wrap_sub(i, 1)] + fConst442 * fRec108[faust_wrap_sub(i, 2)]) - fConst444 * (fConst445 * fRec107[faust_wrap_sub(i, 2)] + fConst446 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec107_perm[j257] = fRec107_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec106_tmp[j258] = fRec106_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fSlow41 * fRec106[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst444 * (fConst448 * fRec107[i] + fConst449 * fRec107[faust_wrap_sub(i, 1)] + fConst448 * fRec107[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec106_perm[j259] = fRec106_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec119_tmp[j260] = fRec119_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fZec71[i] - fConst450 * (fConst451 * fRec119[faust_wrap_sub(i, 2)] + fConst452 * fRec119[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec119_perm[j261] = fRec119_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec118_tmp[j262] = fRec118_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fConst450 * (fConst454 * fRec119[i] + fConst455 * fRec119[faust_wrap_sub(i, 1)] + fConst454 * fRec119[faust_wrap_sub(i, 2)]) - fConst456 * (fConst457 * fRec118[faust_wrap_sub(i, 2)] + fConst458 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec118_perm[j263] = fRec118_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec117_tmp[j264] = fRec117_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fConst456 * (fConst459 * fRec118[i] + fConst460 * fRec118[faust_wrap_sub(i, 1)] + fConst459 * fRec118[faust_wrap_sub(i, 2)]) - fConst461 * (fConst462 * fRec117[faust_wrap_sub(i, 2)] + fConst463 * fRec117[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec117_perm[j265] = fRec117_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Vectorizable loop 190 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec72[i] = fConst461 * (fConst464 * fRec117[i] + fConst465 * fRec117[faust_wrap_sub(i, 1)] + fConst464 * fRec117[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec116_tmp[j266] = fRec116_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fZec72[i] - fConst468 * (fConst469 * fRec116[faust_wrap_sub(i, 2)] + fConst472 * fRec116[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec116_perm[j267] = fRec116_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 192 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec115_tmp[j268] = fRec115_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fConst468 * (fConst474 * fRec116[i] + fConst475 * fRec116[faust_wrap_sub(i, 1)] + fConst474 * fRec116[faust_wrap_sub(i, 2)]) - fConst476 * (fConst477 * fRec115[faust_wrap_sub(i, 2)] + fConst478 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec115_perm[j269] = fRec115_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec114_tmp[j270] = fRec114_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst476 * (fConst480 * fRec115[i] + fConst481 * fRec115[faust_wrap_sub(i, 1)] + fConst480 * fRec115[faust_wrap_sub(i, 2)]) - fConst482 * (fConst483 * fRec114[faust_wrap_sub(i, 2)] + fConst484 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec114_perm[j271] = fRec114_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec113_tmp[j272] = fRec113_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fSlow41 * fRec113[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst482 * (fConst486 * fRec114[i] + fConst487 * fRec114[faust_wrap_sub(i, 1)] + fConst486 * fRec114[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec113_perm[j273] = fRec113_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec126_tmp[j274] = fRec126_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fZec72[i] - fConst488 * (fConst489 * fRec126[faust_wrap_sub(i, 2)] + fConst490 * fRec126[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec126_perm[j275] = fRec126_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec125_tmp[j276] = fRec125_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fConst488 * (fConst492 * fRec126[i] + fConst493 * fRec126[faust_wrap_sub(i, 1)] + fConst492 * fRec126[faust_wrap_sub(i, 2)]) - fConst494 * (fConst495 * fRec125[faust_wrap_sub(i, 2)] + fConst496 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec125_perm[j277] = fRec125_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec124_tmp[j278] = fRec124_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fConst494 * (fConst497 * fRec125[i] + fConst498 * fRec125[faust_wrap_sub(i, 1)] + fConst497 * fRec125[faust_wrap_sub(i, 2)]) - fConst499 * (fConst500 * fRec124[faust_wrap_sub(i, 2)] + fConst501 * fRec124[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec124_perm[j279] = fRec124_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Vectorizable loop 198 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec73[i] = fConst499 * (fConst502 * fRec124[i] + fConst503 * fRec124[faust_wrap_sub(i, 1)] + fConst502 * fRec124[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec123_tmp[j280] = fRec123_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fZec73[i] - fConst506 * (fConst507 * fRec123[faust_wrap_sub(i, 2)] + fConst510 * fRec123[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec123_perm[j281] = fRec123_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 200 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec122_tmp[j282] = fRec122_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fConst506 * (fConst512 * fRec123[i] + fConst513 * fRec123[faust_wrap_sub(i, 1)] + fConst512 * fRec123[faust_wrap_sub(i, 2)]) - fConst514 * (fConst515 * fRec122[faust_wrap_sub(i, 2)] + fConst516 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec122_perm[j283] = fRec122_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec121_tmp[j284] = fRec121_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst514 * (fConst518 * fRec122[i] + fConst519 * fRec122[faust_wrap_sub(i, 1)] + fConst518 * fRec122[faust_wrap_sub(i, 2)]) - fConst520 * (fConst521 * fRec121[faust_wrap_sub(i, 2)] + fConst522 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec121_perm[j285] = fRec121_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec120_tmp[j286] = fRec120_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fSlow41 * fRec120[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst520 * (fConst524 * fRec121[i] + fConst525 * fRec121[faust_wrap_sub(i, 1)] + fConst524 * fRec121[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec120_perm[j287] = fRec120_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec130_tmp[j288] = fRec130_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec130[i] = fZec73[i] - fConst526 * (fConst527 * fRec130[faust_wrap_sub(i, 2)] + fConst528 * fRec130[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec130_perm[j289] = fRec130_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec129_tmp[j290] = fRec129_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec129[i] = fConst526 * (fConst530 * fRec130[i] + fConst531 * fRec130[faust_wrap_sub(i, 1)] + fConst530 * fRec130[faust_wrap_sub(i, 2)]) - fConst532 * (fConst533 * fRec129[faust_wrap_sub(i, 2)] + fConst534 * fRec129[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec129_perm[j291] = fRec129_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec128_tmp[j292] = fRec128_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec128[i] = fConst532 * (fConst535 * fRec129[i] + fConst536 * fRec129[faust_wrap_sub(i, 1)] + fConst535 * fRec129[faust_wrap_sub(i, 2)]) - fConst537 * (fConst538 * fRec128[faust_wrap_sub(i, 2)] + fConst539 * fRec128[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec128_perm[j293] = fRec128_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec127_tmp[j294] = fRec127_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fSlow41 * fRec127[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst537 * (fConst540 * fRec128[i] + fConst541 * fRec128[faust_wrap_sub(i, 1)] + fConst540 * fRec128[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec127_perm[j295] = fRec127_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Vectorizable loop 207 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec32[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec36[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec43[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec50[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec57[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec64[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec71[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec78[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec85[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec92[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec99[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec106[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec113[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec120[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec127[i]));
				fZec74[i] = fZec60[i];
			}
			/* Vectorizable loop 208 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec74[i]);
			}
			/* Vectorizable loop 209 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec74[i]);
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
				fRec12_tmp[j4] = fRec12_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fSlow2 + 0.999 * fRec12[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec12_perm[j5] = fRec12_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec14_tmp[j6] = fRec14_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fSlow4 + 0.999 * fRec14[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec14_perm[j7] = fRec14_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec15_tmp[j8] = fRec15_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fSlow5 + 0.999 * fRec15[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec15_perm[j9] = fRec15_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec17_tmp[j10] = fRec17_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] * fSlow7 + fSlow8;
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec17_perm[j11] = fRec17_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec17[i]));
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec16_tmp[j12] = fRec16_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec16[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec16[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec16_perm[j13] = fRec16_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow9 * fRec17[i]));
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec18_tmp[j14] = fRec18_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec18[faust_wrap_sub(i, 1)] + fConst1 * fZec2[i];
				fRec18[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec18_perm[j15] = fRec18_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow10 * fRec17[i]));
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec19_tmp[j16] = fRec19_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fRec19[faust_wrap_sub(i, 1)] + fConst1 * fZec4[i];
				fRec19[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec19_perm[j17] = fRec19_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				iRec20_tmp[j18] = iRec20_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec20[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec20[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				iRec20_perm[j19] = iRec20_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec20[i]);
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec21_tmp[j20] = fRec21_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = 0.5221894 * fRec21[faust_wrap_sub(i, 3)] + fZec6[i] + 2.494956002 * fRec21[faust_wrap_sub(i, 1)] - 2.017265875 * fRec21[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec21_perm[j21] = fRec21_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec22_tmp[j22] = fRec22_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = 0.999 * fRec22[faust_wrap_sub(i, 1)] - fSlow13;
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec22_perm[j23] = fRec22_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec23_tmp[j24] = fRec23_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fSlow14 + 0.999 * fRec23[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec23_perm[j25] = fRec23_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Vectorizable loop 17 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				iVec0_tmp[j26] = iVec0_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				iVec0_perm[j27] = iVec0_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = 2.0 * fRec16[i];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fZec7[i] + -1.0;
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 1)]);
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fYec0_tmp[j28] = fYec0_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec0[i] = mydsp_faustpower2_f(fZec8[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fYec0_perm[j29] = fYec0_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 2)]);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = mydsp_faustpower3_f(fZec8[i]);
			}
			/* Vectorizable loop 24 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fYec1_tmp[j30] = fYec1_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec1[i] = fZec11[i] + (1.0 - fZec7[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fYec1_perm[j31] = fYec1_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Vectorizable loop 25 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fYec2_tmp[j32] = fYec2_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec2[i] = (fZec11[i] + (1.0 - (fZec7[i] + fYec1[faust_wrap_sub(i, 1)]))) / fZec0[i];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fYec2_perm[j33] = fYec2_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = static_cast<double>(iVec0[faust_wrap_sub(i, 3)]);
			}
			/* Vectorizable loop 27 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fYec3_tmp[j34] = fYec3_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fYec3_perm[j35] = fYec3_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fYec4_tmp[j36] = fYec4_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec4[i] = (fYec3[i] - fYec3[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fYec4_perm[j37] = fYec4_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fYec5_tmp[j38] = fYec5_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec5[i] = (fYec4[i] - fYec4[faust_wrap_sub(i, 1)]) / fZec0[i];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fYec5_perm[j39] = fYec5_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = 2.0 * fRec18[i];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fZec13[i] + -1.0;
			}
			/* Vectorizable loop 32 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fYec6_tmp[j40] = fYec6_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec6[i] = mydsp_faustpower2_f(fZec14[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fYec6_perm[j41] = fYec6_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = mydsp_faustpower3_f(fZec14[i]);
			}
			/* Vectorizable loop 34 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fYec7_tmp[j42] = fYec7_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec7[i] = fZec15[i] + (1.0 - fZec13[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fYec7_perm[j43] = fYec7_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec8_tmp[j44] = fYec8_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec8[i] = (fZec15[i] + (1.0 - (fZec13[i] + fYec7[faust_wrap_sub(i, 1)]))) / fZec2[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec8_perm[j45] = fYec8_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Vectorizable loop 36 */
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
			/* Vectorizable loop 37 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fYec10_tmp[j48] = fYec10_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec10[i] = (fYec9[i] - fYec9[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fYec10_perm[j49] = fYec10_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Vectorizable loop 38 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fYec11_tmp[j50] = fYec11_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec11[i] = (fYec10[i] - fYec10[faust_wrap_sub(i, 1)]) / fZec2[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fYec11_perm[j51] = fYec11_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = 2.0 * fRec19[i];
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fZec16[i] + -1.0;
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec12_tmp[j52] = fYec12_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec12[i] = mydsp_faustpower2_f(fZec17[i]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec12_perm[j53] = fYec12_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = mydsp_faustpower3_f(fZec17[i]);
			}
			/* Vectorizable loop 43 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fYec13_tmp[j54] = fYec13_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec13[i] = fZec18[i] + (1.0 - fZec16[i]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fYec13_perm[j55] = fYec13_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 44 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fYec14_tmp[j56] = fYec14_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec14[i] = (fZec18[i] + (1.0 - (fZec16[i] + fYec13[faust_wrap_sub(i, 1)]))) / fZec4[i];
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fYec14_perm[j57] = fYec14_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Vectorizable loop 45 */
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
			/* Vectorizable loop 46 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fYec16_tmp[j60] = fYec16_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec16[i] = (fYec15[i] - fYec15[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fYec16_perm[j61] = fYec16_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fYec17_tmp[j62] = fYec17_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec17[i] = (fYec16[i] - fYec16[faust_wrap_sub(i, 1)]) / fZec4[i];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fYec17_perm[j63] = fYec17_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fRec15[i] * ((iSlow16) ? static_cast<double>(input0[i]) : ((iSlow17) ? ((iSlow22) ? 0.049922035 * fRec21[i] + 0.050612699 * fRec21[faust_wrap_sub(i, 2)] - (0.095993537 * fRec21[faust_wrap_sub(i, 1)] + 0.004408786 * fRec21[faust_wrap_sub(i, 3)]) : fZec6[i]) : 0.3333333333333333 * fRec15[i] * (((iSlow19) ? ((iSlow21) ? fConst6 * (fZec12[i] * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst5 * (fZec10[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow20) ? fConst4 * (fZec9[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec8[i])) + ((iSlow19) ? ((iSlow21) ? fConst6 * (fZec12[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec2[i]) : fConst5 * (fZec10[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec2[i])) : ((iSlow20) ? fConst4 * (fZec9[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec2[i]) : fZec14[i])) + ((iSlow19) ? ((iSlow21) ? fConst6 * (fZec12[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec4[i]) : fConst5 * (fZec10[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec4[i])) : ((iSlow20) ? fConst4 * (fZec9[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec4[i]) : fZec17[i])))));
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec13_tmp[j64] = fRec13_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fRec14[i] * ((iSlow15) ? 0.0 : fZec19[i]) - (fRec22[i] * fRec13[faust_wrap_sub(i, 1)] + fRec23[i] * fRec13[faust_wrap_sub(i, 2)]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec13_perm[j65] = fRec13_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = fConst7 * fRec12[i];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = 1.0 - fZec20[i];
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = ((iSlow15) ? fZec19[i] : fRec13[i] - fRec13[faust_wrap_sub(i, 1)]);
			}
			/* Recursive loop 53 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec11_tmp[j66] = fRec11_perm[j66];
			}
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec10_tmp[j68] = fRec10_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec9_tmp[j70] = fRec9_perm[j70];
			}
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec8_tmp[j72] = fRec8_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec7_tmp[j74] = fRec7_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fZec21[i] * fRec11[faust_wrap_sub(i, 1)] + ((iSlow23) ? 0.0 : fZec22[i]) - 3.2 * fRec7[faust_wrap_sub(i, 1)];
				fRec10[i] = fRec11[i] + fZec21[i] * fRec10[faust_wrap_sub(i, 1)];
				fRec9[i] = fRec10[i] + fZec21[i] * fRec9[faust_wrap_sub(i, 1)];
				fRec8[i] = fRec9[i] + fRec8[faust_wrap_sub(i, 1)] * fZec21[i];
				fRec7[i] = fRec8[i] * mydsp_faustpower4_f(fZec20[i]);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec11_perm[j67] = fRec11_tmp[faust_wrap_add(vsize, j67)];
			}
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec10_perm[j69] = fRec10_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec9_perm[j71] = fRec9_tmp[faust_wrap_add(vsize, j71)];
			}
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec8_perm[j73] = fRec8_tmp[faust_wrap_add(vsize, j73)];
			}
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec7_perm[j75] = fRec7_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fConst7 * fRec6[i];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = 1.0 - fZec23[i];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = ((iSlow23) ? fZec22[i] : 4.0 * fRec7[i]);
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = ((iSlow24) ? 0.0 : fZec25[i]);
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec5_tmp[j76] = fRec5_perm[j76];
			}
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec4_tmp[j78] = fRec4_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec3_tmp[j80] = fRec3_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec2_tmp[j82] = fRec2_perm[j82];
			}
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec1_tmp[j84] = fRec1_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fZec24[i] * fRec5[faust_wrap_sub(i, 1)] + fZec26[i] - fSlow26 * fRec1[faust_wrap_sub(i, 1)];
				fRec4[i] = fRec5[i] + fZec24[i] * fRec4[faust_wrap_sub(i, 1)];
				fRec3[i] = fRec4[i] + fZec24[i] * fRec3[faust_wrap_sub(i, 1)];
				fRec2[i] = fRec3[i] + fRec2[faust_wrap_sub(i, 1)] * fZec24[i];
				fRec1[i] = fRec2[i] * mydsp_faustpower4_f(fZec23[i]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec5_perm[j77] = fRec5_tmp[faust_wrap_add(vsize, j77)];
			}
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec4_perm[j79] = fRec4_tmp[faust_wrap_add(vsize, j79)];
			}
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec3_perm[j81] = fRec3_tmp[faust_wrap_add(vsize, j81)];
			}
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec2_perm[j83] = fRec2_tmp[faust_wrap_add(vsize, j83)];
			}
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec1_perm[j85] = fRec1_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = std::tan(fConst8 * std::max<double>(2e+01, std::min<double>(1e+04, fRec6[i])));
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = 1.0 / fZec27[i];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec27[i]);
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = fSlow30 + (fSlow31 + fZec28[i]) / fZec27[i] + 1.0;
			}
			/* Recursive loop 63 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec25_tmp[j86] = fRec25_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fZec26[i] - (fRec25[faust_wrap_sub(i, 2)] * (fSlow30 + (fZec28[i] - fSlow31) / fZec27[i] + 1.0) + 2.0 * fRec25[faust_wrap_sub(i, 1)] * (fSlow30 + fZec29[i])) / fZec30[i];
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec25_perm[j87] = fRec25_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fSlow29 + ((fSlow32 + fZec28[i]) / fZec27[i] + 1.0 - fSlow28);
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec24_tmp[j88] = fRec24_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = (fRec25[faust_wrap_sub(i, 2)] + fRec25[i] + 2.0 * fRec25[faust_wrap_sub(i, 1)]) / fZec30[i] - (fRec24[faust_wrap_sub(i, 2)] * (fSlow29 + ((fZec28[i] - fSlow32) / fZec27[i] + 1.0 - fSlow28)) + 2.0 * fRec24[faust_wrap_sub(i, 1)] * (fSlow29 + (fZec29[i] - fSlow28))) / fZec31[i];
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec24_perm[j89] = fRec24_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = std::tan(fConst8 * std::max<double>(fRec6[i], 2e+01));
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = 1.0 / fZec32[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = fSlow35 + (fSlow36 + fZec33[i]) / fZec32[i] + 1.0;
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = (fSlow35 + (1.0 - (fSlow36 - fZec33[i]) / fZec32[i])) / fZec34[i];
			}
			/* Vectorizable loop 70 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec36[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec35[i]));
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec37[i] = 1.0 - mydsp_faustpower2_f(fZec36[i]);
			}
			/* Vectorizable loop 72 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec38[i] = std::sqrt(std::max<double>(0.0, fZec37[i]));
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec40[i] = 1.0 - 1.0 / mydsp_faustpower2_f(fZec32[i]);
			}
			/* Vectorizable loop 74 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = fSlow35 + fZec40[i];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec41[i] / (fZec34[i] * (fZec35[i] + 1.0)))));
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = 1.0 - mydsp_faustpower2_f(fZec42[i]);
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec44[i] = std::sqrt(std::max<double>(0.0, fZec43[i]));
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec28_tmp[j90] = fRec28_perm[j90];
			}
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec26_tmp[j92] = fRec26_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec39[i] = fZec26[i] * fZec38[i] - fZec36[i] * fRec26[faust_wrap_sub(i, 1)];
				fRec28[i] = fZec39[i] * fZec44[i] - fZec42[i] * fRec28[faust_wrap_sub(i, 1)];
				fRec26[i] = fZec39[i] * fZec42[i] + fRec28[faust_wrap_sub(i, 1)] * fZec44[i];
				fRec27[i] = fRec28[i];
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec28_perm[j91] = fRec28_tmp[faust_wrap_add(vsize, j91)];
			}
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec26_perm[j93] = fRec26_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec45[i] = 1.0 - fZec41[i] / fZec34[i];
			}
			/* Vectorizable loop 80 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec46[i] = std::sqrt(fZec37[i]);
			}
			/* Vectorizable loop 81 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec47[i] = fZec26[i] * fZec36[i] + fRec26[faust_wrap_sub(i, 1)] * fZec38[i] + 2.0 * (fRec26[i] * fZec45[i] / fZec46[i]) + fRec27[i] * (1.0 - fZec35[i] - 2.0 * fZec42[i] * fZec45[i]) / (fZec46[i] * std::sqrt(fZec43[i]));
			}
			/* Vectorizable loop 82 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec48[i] = fSlow33 + ((fSlow37 + fZec33[i]) / fZec32[i] + 1.0 - fSlow34);
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec49[i] = (fSlow33 + ((fZec33[i] - fSlow37) / fZec32[i] + 1.0 - fSlow34)) / fZec48[i];
			}
			/* Vectorizable loop 84 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec50[i] = std::max<double>(-0.9999, std::min<double>(0.9999, fZec49[i]));
			}
			/* Vectorizable loop 85 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec51[i] = 1.0 - mydsp_faustpower2_f(fZec50[i]);
			}
			/* Vectorizable loop 86 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec52[i] = std::sqrt(std::max<double>(0.0, fZec51[i]));
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec54[i] = fSlow33 + (fZec40[i] - fSlow34);
			}
			/* Vectorizable loop 88 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec55[i] = std::max<double>(-0.9999, std::min<double>(0.9999, 2.0 * (fZec54[i] / (fZec48[i] * (fZec49[i] + 1.0)))));
			}
			/* Vectorizable loop 89 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec56[i] = 1.0 - mydsp_faustpower2_f(fZec55[i]);
			}
			/* Vectorizable loop 90 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec57[i] = std::sqrt(std::max<double>(0.0, fZec56[i]));
			}
			/* Recursive loop 91 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec31_tmp[j94] = fRec31_perm[j94];
			}
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec29_tmp[j96] = fRec29_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec53[i] = fZec47[i] * fZec52[i] / fZec34[i] - fZec50[i] * fRec29[faust_wrap_sub(i, 1)];
				fRec31[i] = fZec53[i] * fZec57[i] - fZec55[i] * fRec31[faust_wrap_sub(i, 1)];
				fRec29[i] = fZec53[i] * fZec55[i] + fRec31[faust_wrap_sub(i, 1)] * fZec57[i];
				fRec30[i] = fRec31[i];
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec31_perm[j95] = fRec31_tmp[faust_wrap_add(vsize, j95)];
			}
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec29_perm[j97] = fRec29_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 92 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec58[i] = 1.0 - fZec54[i] / fZec48[i];
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec59[i] = std::sqrt(fZec51[i]);
			}
			/* Vectorizable loop 94 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec60[i] = ((iSlow24) ? fZec25[i] : fRec0[i] * ((iSlow38) ? ((iSlow39) ? (fZec47[i] * fZec50[i] / fZec34[i] + fRec29[faust_wrap_sub(i, 1)] * fZec52[i] + 2.0 * (fRec29[i] * fZec58[i] / fZec59[i]) + fRec30[i] * (1.0 - fZec49[i] - 2.0 * fZec55[i] * fZec58[i]) / (fZec59[i] * std::sqrt(fZec56[i]))) / fZec48[i] : (fRec24[faust_wrap_sub(i, 2)] + fRec24[i] + 2.0 * fRec24[faust_wrap_sub(i, 1)]) / fZec31[i]) : fRec1[i]));
			}
			/* Recursive loop 95 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec35_tmp[j98] = fRec35_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fZec60[i] - fConst11 * (fConst12 * fRec35[faust_wrap_sub(i, 2)] + fConst15 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec35_perm[j99] = fRec35_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec34_tmp[j100] = fRec34_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst11 * (fConst17 * fRec35[i] + fConst18 * fRec35[faust_wrap_sub(i, 1)] + fConst17 * fRec35[faust_wrap_sub(i, 2)]) - fConst19 * (fConst20 * fRec34[faust_wrap_sub(i, 2)] + fConst21 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec34_perm[j101] = fRec34_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec33_tmp[j102] = fRec33_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst19 * (fConst23 * fRec34[i] + fConst24 * fRec34[faust_wrap_sub(i, 1)] + fConst23 * fRec34[faust_wrap_sub(i, 2)]) - fConst25 * (fConst26 * fRec33[faust_wrap_sub(i, 2)] + fConst27 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec33_perm[j103] = fRec33_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec32_tmp[j104] = fRec32_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fRec32[faust_wrap_sub(i, 1)] * fSlow41 + std::fabs(fConst25 * (fConst30 * fRec33[i] + fConst31 * fRec33[faust_wrap_sub(i, 1)] + fConst30 * fRec33[faust_wrap_sub(i, 2)])) * fSlow42;
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec32_perm[j105] = fRec32_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 99 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec42_tmp[j106] = fRec42_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fZec60[i] - fConst32 * (fConst33 * fRec42[faust_wrap_sub(i, 2)] + fConst34 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec42_perm[j107] = fRec42_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec41_tmp[j108] = fRec41_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst32 * (fConst36 * fRec42[i] + fConst37 * fRec42[faust_wrap_sub(i, 1)] + fConst36 * fRec42[faust_wrap_sub(i, 2)]) - fConst38 * (fConst39 * fRec41[faust_wrap_sub(i, 2)] + fConst40 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec41_perm[j109] = fRec41_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec40_tmp[j110] = fRec40_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst38 * (fConst41 * fRec41[i] + fConst42 * fRec41[faust_wrap_sub(i, 1)] + fConst41 * fRec41[faust_wrap_sub(i, 2)]) - fConst43 * (fConst44 * fRec40[faust_wrap_sub(i, 2)] + fConst45 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec40_perm[j111] = fRec40_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Vectorizable loop 102 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec61[i] = fConst43 * (fConst46 * fRec40[i] + fConst47 * fRec40[faust_wrap_sub(i, 1)] + fConst46 * fRec40[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 103 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec39_tmp[j112] = fRec39_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fZec61[i] - fConst50 * (fConst51 * fRec39[faust_wrap_sub(i, 2)] + fConst54 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec39_perm[j113] = fRec39_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec38_tmp[j114] = fRec38_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fConst50 * (fConst56 * fRec39[i] + fConst57 * fRec39[faust_wrap_sub(i, 1)] + fConst56 * fRec39[faust_wrap_sub(i, 2)]) - fConst58 * (fConst59 * fRec38[faust_wrap_sub(i, 2)] + fConst60 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec38_perm[j115] = fRec38_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec37_tmp[j116] = fRec37_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst58 * (fConst62 * fRec38[i] + fConst63 * fRec38[faust_wrap_sub(i, 1)] + fConst62 * fRec38[faust_wrap_sub(i, 2)]) - fConst64 * (fConst65 * fRec37[faust_wrap_sub(i, 2)] + fConst66 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec37_perm[j117] = fRec37_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec36_tmp[j118] = fRec36_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fSlow41 * fRec36[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst64 * (fConst68 * fRec37[i] + fConst69 * fRec37[faust_wrap_sub(i, 1)] + fConst68 * fRec37[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec36_perm[j119] = fRec36_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 107 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec49_tmp[j120] = fRec49_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fZec61[i] - fConst70 * (fConst71 * fRec49[faust_wrap_sub(i, 2)] + fConst72 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec49_perm[j121] = fRec49_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec48_tmp[j122] = fRec48_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst70 * (fConst74 * fRec49[i] + fConst75 * fRec49[faust_wrap_sub(i, 1)] + fConst74 * fRec49[faust_wrap_sub(i, 2)]) - fConst76 * (fConst77 * fRec48[faust_wrap_sub(i, 2)] + fConst78 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec48_perm[j123] = fRec48_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec47_tmp[j124] = fRec47_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst76 * (fConst79 * fRec48[i] + fConst80 * fRec48[faust_wrap_sub(i, 1)] + fConst79 * fRec48[faust_wrap_sub(i, 2)]) - fConst81 * (fConst82 * fRec47[faust_wrap_sub(i, 2)] + fConst83 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec47_perm[j125] = fRec47_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Vectorizable loop 110 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec62[i] = fConst81 * (fConst84 * fRec47[i] + fConst85 * fRec47[faust_wrap_sub(i, 1)] + fConst84 * fRec47[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 111 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec46_tmp[j126] = fRec46_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fZec62[i] - fConst88 * (fConst89 * fRec46[faust_wrap_sub(i, 2)] + fConst92 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec46_perm[j127] = fRec46_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec45_tmp[j128] = fRec45_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fConst88 * (fConst94 * fRec46[i] + fConst95 * fRec46[faust_wrap_sub(i, 1)] + fConst94 * fRec46[faust_wrap_sub(i, 2)]) - fConst96 * (fConst97 * fRec45[faust_wrap_sub(i, 2)] + fConst98 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec45_perm[j129] = fRec45_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec44_tmp[j130] = fRec44_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst96 * (fConst100 * fRec45[i] + fConst101 * fRec45[faust_wrap_sub(i, 1)] + fConst100 * fRec45[faust_wrap_sub(i, 2)]) - fConst102 * (fConst103 * fRec44[faust_wrap_sub(i, 2)] + fConst104 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec44_perm[j131] = fRec44_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec43_tmp[j132] = fRec43_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fSlow41 * fRec43[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst102 * (fConst106 * fRec44[i] + fConst107 * fRec44[faust_wrap_sub(i, 1)] + fConst106 * fRec44[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec43_perm[j133] = fRec43_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 115 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec56_tmp[j134] = fRec56_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fZec62[i] - fConst108 * (fConst109 * fRec56[faust_wrap_sub(i, 2)] + fConst110 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec56_perm[j135] = fRec56_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec55_tmp[j136] = fRec55_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst108 * (fConst112 * fRec56[i] + fConst113 * fRec56[faust_wrap_sub(i, 1)] + fConst112 * fRec56[faust_wrap_sub(i, 2)]) - fConst114 * (fConst115 * fRec55[faust_wrap_sub(i, 2)] + fConst116 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec55_perm[j137] = fRec55_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec54_tmp[j138] = fRec54_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst114 * (fConst117 * fRec55[i] + fConst118 * fRec55[faust_wrap_sub(i, 1)] + fConst117 * fRec55[faust_wrap_sub(i, 2)]) - fConst119 * (fConst120 * fRec54[faust_wrap_sub(i, 2)] + fConst121 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec54_perm[j139] = fRec54_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Vectorizable loop 118 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec63[i] = fConst119 * (fConst122 * fRec54[i] + fConst123 * fRec54[faust_wrap_sub(i, 1)] + fConst122 * fRec54[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 119 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec53_tmp[j140] = fRec53_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fZec63[i] - fConst126 * (fConst127 * fRec53[faust_wrap_sub(i, 2)] + fConst130 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec53_perm[j141] = fRec53_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec52_tmp[j142] = fRec52_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fConst126 * (fConst132 * fRec53[i] + fConst133 * fRec53[faust_wrap_sub(i, 1)] + fConst132 * fRec53[faust_wrap_sub(i, 2)]) - fConst134 * (fConst135 * fRec52[faust_wrap_sub(i, 2)] + fConst136 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec52_perm[j143] = fRec52_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec51_tmp[j144] = fRec51_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst134 * (fConst138 * fRec52[i] + fConst139 * fRec52[faust_wrap_sub(i, 1)] + fConst138 * fRec52[faust_wrap_sub(i, 2)]) - fConst140 * (fConst141 * fRec51[faust_wrap_sub(i, 2)] + fConst142 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec51_perm[j145] = fRec51_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec50_tmp[j146] = fRec50_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fSlow41 * fRec50[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst140 * (fConst144 * fRec51[i] + fConst145 * fRec51[faust_wrap_sub(i, 1)] + fConst144 * fRec51[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec50_perm[j147] = fRec50_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec63_tmp[j148] = fRec63_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fZec63[i] - fConst146 * (fConst147 * fRec63[faust_wrap_sub(i, 2)] + fConst148 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec63_perm[j149] = fRec63_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec62_tmp[j150] = fRec62_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst146 * (fConst150 * fRec63[i] + fConst151 * fRec63[faust_wrap_sub(i, 1)] + fConst150 * fRec63[faust_wrap_sub(i, 2)]) - fConst152 * (fConst153 * fRec62[faust_wrap_sub(i, 2)] + fConst154 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec62_perm[j151] = fRec62_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec61_tmp[j152] = fRec61_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst152 * (fConst155 * fRec62[i] + fConst156 * fRec62[faust_wrap_sub(i, 1)] + fConst155 * fRec62[faust_wrap_sub(i, 2)]) - fConst157 * (fConst158 * fRec61[faust_wrap_sub(i, 2)] + fConst159 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec61_perm[j153] = fRec61_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec64[i] = fConst157 * (fConst160 * fRec61[i] + fConst161 * fRec61[faust_wrap_sub(i, 1)] + fConst160 * fRec61[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec60_tmp[j154] = fRec60_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fZec64[i] - fConst164 * (fConst165 * fRec60[faust_wrap_sub(i, 2)] + fConst168 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec60_perm[j155] = fRec60_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec59_tmp[j156] = fRec59_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fConst164 * (fConst170 * fRec60[i] + fConst171 * fRec60[faust_wrap_sub(i, 1)] + fConst170 * fRec60[faust_wrap_sub(i, 2)]) - fConst172 * (fConst173 * fRec59[faust_wrap_sub(i, 2)] + fConst174 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec59_perm[j157] = fRec59_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec58_tmp[j158] = fRec58_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst172 * (fConst176 * fRec59[i] + fConst177 * fRec59[faust_wrap_sub(i, 1)] + fConst176 * fRec59[faust_wrap_sub(i, 2)]) - fConst178 * (fConst179 * fRec58[faust_wrap_sub(i, 2)] + fConst180 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec58_perm[j159] = fRec58_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec57_tmp[j160] = fRec57_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fSlow41 * fRec57[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst178 * (fConst182 * fRec58[i] + fConst183 * fRec58[faust_wrap_sub(i, 1)] + fConst182 * fRec58[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec57_perm[j161] = fRec57_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec70_tmp[j162] = fRec70_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fZec64[i] - fConst184 * (fConst185 * fRec70[faust_wrap_sub(i, 2)] + fConst186 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec70_perm[j163] = fRec70_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec69_tmp[j164] = fRec69_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst184 * (fConst188 * fRec70[i] + fConst189 * fRec70[faust_wrap_sub(i, 1)] + fConst188 * fRec70[faust_wrap_sub(i, 2)]) - fConst190 * (fConst191 * fRec69[faust_wrap_sub(i, 2)] + fConst192 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec69_perm[j165] = fRec69_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec68_tmp[j166] = fRec68_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst190 * (fConst193 * fRec69[i] + fConst194 * fRec69[faust_wrap_sub(i, 1)] + fConst193 * fRec69[faust_wrap_sub(i, 2)]) - fConst195 * (fConst196 * fRec68[faust_wrap_sub(i, 2)] + fConst197 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec68_perm[j167] = fRec68_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Vectorizable loop 134 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec65[i] = fConst195 * (fConst198 * fRec68[i] + fConst199 * fRec68[faust_wrap_sub(i, 1)] + fConst198 * fRec68[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec67_tmp[j168] = fRec67_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fZec65[i] - fConst202 * (fConst203 * fRec67[faust_wrap_sub(i, 2)] + fConst206 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec67_perm[j169] = fRec67_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec66_tmp[j170] = fRec66_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fConst202 * (fConst208 * fRec67[i] + fConst209 * fRec67[faust_wrap_sub(i, 1)] + fConst208 * fRec67[faust_wrap_sub(i, 2)]) - fConst210 * (fConst211 * fRec66[faust_wrap_sub(i, 2)] + fConst212 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec66_perm[j171] = fRec66_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec65_tmp[j172] = fRec65_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst210 * (fConst214 * fRec66[i] + fConst215 * fRec66[faust_wrap_sub(i, 1)] + fConst214 * fRec66[faust_wrap_sub(i, 2)]) - fConst216 * (fConst217 * fRec65[faust_wrap_sub(i, 2)] + fConst218 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec65_perm[j173] = fRec65_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec64_tmp[j174] = fRec64_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fSlow41 * fRec64[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst216 * (fConst220 * fRec65[i] + fConst221 * fRec65[faust_wrap_sub(i, 1)] + fConst220 * fRec65[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec64_perm[j175] = fRec64_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec77_tmp[j176] = fRec77_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fZec65[i] - fConst222 * (fConst223 * fRec77[faust_wrap_sub(i, 2)] + fConst224 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec77_perm[j177] = fRec77_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec76_tmp[j178] = fRec76_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst222 * (fConst226 * fRec77[i] + fConst227 * fRec77[faust_wrap_sub(i, 1)] + fConst226 * fRec77[faust_wrap_sub(i, 2)]) - fConst228 * (fConst229 * fRec76[faust_wrap_sub(i, 2)] + fConst230 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec76_perm[j179] = fRec76_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec75_tmp[j180] = fRec75_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst228 * (fConst231 * fRec76[i] + fConst232 * fRec76[faust_wrap_sub(i, 1)] + fConst231 * fRec76[faust_wrap_sub(i, 2)]) - fConst233 * (fConst234 * fRec75[faust_wrap_sub(i, 2)] + fConst235 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec75_perm[j181] = fRec75_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Vectorizable loop 142 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec66[i] = fConst233 * (fConst236 * fRec75[i] + fConst237 * fRec75[faust_wrap_sub(i, 1)] + fConst236 * fRec75[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec74_tmp[j182] = fRec74_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fZec66[i] - fConst240 * (fConst241 * fRec74[faust_wrap_sub(i, 2)] + fConst244 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec74_perm[j183] = fRec74_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec73_tmp[j184] = fRec73_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fConst240 * (fConst246 * fRec74[i] + fConst247 * fRec74[faust_wrap_sub(i, 1)] + fConst246 * fRec74[faust_wrap_sub(i, 2)]) - fConst248 * (fConst249 * fRec73[faust_wrap_sub(i, 2)] + fConst250 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec73_perm[j185] = fRec73_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec72_tmp[j186] = fRec72_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst248 * (fConst252 * fRec73[i] + fConst253 * fRec73[faust_wrap_sub(i, 1)] + fConst252 * fRec73[faust_wrap_sub(i, 2)]) - fConst254 * (fConst255 * fRec72[faust_wrap_sub(i, 2)] + fConst256 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec72_perm[j187] = fRec72_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec71_tmp[j188] = fRec71_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fSlow41 * fRec71[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst254 * (fConst258 * fRec72[i] + fConst259 * fRec72[faust_wrap_sub(i, 1)] + fConst258 * fRec72[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec71_perm[j189] = fRec71_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec84_tmp[j190] = fRec84_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fZec66[i] - fConst260 * (fConst261 * fRec84[faust_wrap_sub(i, 2)] + fConst262 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec84_perm[j191] = fRec84_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec83_tmp[j192] = fRec83_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst260 * (fConst264 * fRec84[i] + fConst265 * fRec84[faust_wrap_sub(i, 1)] + fConst264 * fRec84[faust_wrap_sub(i, 2)]) - fConst266 * (fConst267 * fRec83[faust_wrap_sub(i, 2)] + fConst268 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec83_perm[j193] = fRec83_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec82_tmp[j194] = fRec82_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst266 * (fConst269 * fRec83[i] + fConst270 * fRec83[faust_wrap_sub(i, 1)] + fConst269 * fRec83[faust_wrap_sub(i, 2)]) - fConst271 * (fConst272 * fRec82[faust_wrap_sub(i, 2)] + fConst273 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec82_perm[j195] = fRec82_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Vectorizable loop 150 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec67[i] = fConst271 * (fConst274 * fRec82[i] + fConst275 * fRec82[faust_wrap_sub(i, 1)] + fConst274 * fRec82[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec81_tmp[j196] = fRec81_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fZec67[i] - fConst278 * (fConst279 * fRec81[faust_wrap_sub(i, 2)] + fConst282 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec81_perm[j197] = fRec81_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec80_tmp[j198] = fRec80_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fConst278 * (fConst284 * fRec81[i] + fConst285 * fRec81[faust_wrap_sub(i, 1)] + fConst284 * fRec81[faust_wrap_sub(i, 2)]) - fConst286 * (fConst287 * fRec80[faust_wrap_sub(i, 2)] + fConst288 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec80_perm[j199] = fRec80_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec79_tmp[j200] = fRec79_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst286 * (fConst290 * fRec80[i] + fConst291 * fRec80[faust_wrap_sub(i, 1)] + fConst290 * fRec80[faust_wrap_sub(i, 2)]) - fConst292 * (fConst293 * fRec79[faust_wrap_sub(i, 2)] + fConst294 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec79_perm[j201] = fRec79_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec78_tmp[j202] = fRec78_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fSlow41 * fRec78[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst292 * (fConst296 * fRec79[i] + fConst297 * fRec79[faust_wrap_sub(i, 1)] + fConst296 * fRec79[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec78_perm[j203] = fRec78_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec91_tmp[j204] = fRec91_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fZec67[i] - fConst298 * (fConst299 * fRec91[faust_wrap_sub(i, 2)] + fConst300 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec91_perm[j205] = fRec91_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec90_tmp[j206] = fRec90_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst298 * (fConst302 * fRec91[i] + fConst303 * fRec91[faust_wrap_sub(i, 1)] + fConst302 * fRec91[faust_wrap_sub(i, 2)]) - fConst304 * (fConst305 * fRec90[faust_wrap_sub(i, 2)] + fConst306 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec90_perm[j207] = fRec90_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec89_tmp[j208] = fRec89_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst304 * (fConst307 * fRec90[i] + fConst308 * fRec90[faust_wrap_sub(i, 1)] + fConst307 * fRec90[faust_wrap_sub(i, 2)]) - fConst309 * (fConst310 * fRec89[faust_wrap_sub(i, 2)] + fConst311 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec89_perm[j209] = fRec89_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Vectorizable loop 158 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec68[i] = fConst309 * (fConst312 * fRec89[i] + fConst313 * fRec89[faust_wrap_sub(i, 1)] + fConst312 * fRec89[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec88_tmp[j210] = fRec88_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fZec68[i] - fConst316 * (fConst317 * fRec88[faust_wrap_sub(i, 2)] + fConst320 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec88_perm[j211] = fRec88_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec87_tmp[j212] = fRec87_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fConst316 * (fConst322 * fRec88[i] + fConst323 * fRec88[faust_wrap_sub(i, 1)] + fConst322 * fRec88[faust_wrap_sub(i, 2)]) - fConst324 * (fConst325 * fRec87[faust_wrap_sub(i, 2)] + fConst326 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec87_perm[j213] = fRec87_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec86_tmp[j214] = fRec86_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst324 * (fConst328 * fRec87[i] + fConst329 * fRec87[faust_wrap_sub(i, 1)] + fConst328 * fRec87[faust_wrap_sub(i, 2)]) - fConst330 * (fConst331 * fRec86[faust_wrap_sub(i, 2)] + fConst332 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec86_perm[j215] = fRec86_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec85_tmp[j216] = fRec85_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fSlow41 * fRec85[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst330 * (fConst334 * fRec86[i] + fConst335 * fRec86[faust_wrap_sub(i, 1)] + fConst334 * fRec86[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec85_perm[j217] = fRec85_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec98_tmp[j218] = fRec98_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fZec68[i] - fConst336 * (fConst337 * fRec98[faust_wrap_sub(i, 2)] + fConst338 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec98_perm[j219] = fRec98_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec97_tmp[j220] = fRec97_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst336 * (fConst340 * fRec98[i] + fConst341 * fRec98[faust_wrap_sub(i, 1)] + fConst340 * fRec98[faust_wrap_sub(i, 2)]) - fConst342 * (fConst343 * fRec97[faust_wrap_sub(i, 2)] + fConst344 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec97_perm[j221] = fRec97_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec96_tmp[j222] = fRec96_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst342 * (fConst345 * fRec97[i] + fConst346 * fRec97[faust_wrap_sub(i, 1)] + fConst345 * fRec97[faust_wrap_sub(i, 2)]) - fConst347 * (fConst348 * fRec96[faust_wrap_sub(i, 2)] + fConst349 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec96_perm[j223] = fRec96_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Vectorizable loop 166 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec69[i] = fConst347 * (fConst350 * fRec96[i] + fConst351 * fRec96[faust_wrap_sub(i, 1)] + fConst350 * fRec96[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec95_tmp[j224] = fRec95_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fZec69[i] - fConst354 * (fConst355 * fRec95[faust_wrap_sub(i, 2)] + fConst358 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec95_perm[j225] = fRec95_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec94_tmp[j226] = fRec94_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fConst354 * (fConst360 * fRec95[i] + fConst361 * fRec95[faust_wrap_sub(i, 1)] + fConst360 * fRec95[faust_wrap_sub(i, 2)]) - fConst362 * (fConst363 * fRec94[faust_wrap_sub(i, 2)] + fConst364 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec94_perm[j227] = fRec94_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec93_tmp[j228] = fRec93_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst362 * (fConst366 * fRec94[i] + fConst367 * fRec94[faust_wrap_sub(i, 1)] + fConst366 * fRec94[faust_wrap_sub(i, 2)]) - fConst368 * (fConst369 * fRec93[faust_wrap_sub(i, 2)] + fConst370 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec93_perm[j229] = fRec93_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec92_tmp[j230] = fRec92_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fSlow41 * fRec92[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst368 * (fConst372 * fRec93[i] + fConst373 * fRec93[faust_wrap_sub(i, 1)] + fConst372 * fRec93[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec92_perm[j231] = fRec92_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec105_tmp[j232] = fRec105_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fZec69[i] - fConst374 * (fConst375 * fRec105[faust_wrap_sub(i, 2)] + fConst376 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec105_perm[j233] = fRec105_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec104_tmp[j234] = fRec104_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst374 * (fConst378 * fRec105[i] + fConst379 * fRec105[faust_wrap_sub(i, 1)] + fConst378 * fRec105[faust_wrap_sub(i, 2)]) - fConst380 * (fConst381 * fRec104[faust_wrap_sub(i, 2)] + fConst382 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec104_perm[j235] = fRec104_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec103_tmp[j236] = fRec103_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst380 * (fConst383 * fRec104[i] + fConst384 * fRec104[faust_wrap_sub(i, 1)] + fConst383 * fRec104[faust_wrap_sub(i, 2)]) - fConst385 * (fConst386 * fRec103[faust_wrap_sub(i, 2)] + fConst387 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec103_perm[j237] = fRec103_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Vectorizable loop 174 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec70[i] = fConst385 * (fConst388 * fRec103[i] + fConst389 * fRec103[faust_wrap_sub(i, 1)] + fConst388 * fRec103[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec102_tmp[j238] = fRec102_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fZec70[i] - fConst392 * (fConst393 * fRec102[faust_wrap_sub(i, 2)] + fConst396 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec102_perm[j239] = fRec102_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec101_tmp[j240] = fRec101_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fConst392 * (fConst398 * fRec102[i] + fConst399 * fRec102[faust_wrap_sub(i, 1)] + fConst398 * fRec102[faust_wrap_sub(i, 2)]) - fConst400 * (fConst401 * fRec101[faust_wrap_sub(i, 2)] + fConst402 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec101_perm[j241] = fRec101_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec100_tmp[j242] = fRec100_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst400 * (fConst404 * fRec101[i] + fConst405 * fRec101[faust_wrap_sub(i, 1)] + fConst404 * fRec101[faust_wrap_sub(i, 2)]) - fConst406 * (fConst407 * fRec100[faust_wrap_sub(i, 2)] + fConst408 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec100_perm[j243] = fRec100_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec99_tmp[j244] = fRec99_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fSlow41 * fRec99[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst406 * (fConst410 * fRec100[i] + fConst411 * fRec100[faust_wrap_sub(i, 1)] + fConst410 * fRec100[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec99_perm[j245] = fRec99_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec112_tmp[j246] = fRec112_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fZec70[i] - fConst412 * (fConst413 * fRec112[faust_wrap_sub(i, 2)] + fConst414 * fRec112[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec112_perm[j247] = fRec112_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec111_tmp[j248] = fRec111_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fConst412 * (fConst416 * fRec112[i] + fConst417 * fRec112[faust_wrap_sub(i, 1)] + fConst416 * fRec112[faust_wrap_sub(i, 2)]) - fConst418 * (fConst419 * fRec111[faust_wrap_sub(i, 2)] + fConst420 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec111_perm[j249] = fRec111_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec110_tmp[j250] = fRec110_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst418 * (fConst421 * fRec111[i] + fConst422 * fRec111[faust_wrap_sub(i, 1)] + fConst421 * fRec111[faust_wrap_sub(i, 2)]) - fConst423 * (fConst424 * fRec110[faust_wrap_sub(i, 2)] + fConst425 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec110_perm[j251] = fRec110_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Vectorizable loop 182 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec71[i] = fConst423 * (fConst426 * fRec110[i] + fConst427 * fRec110[faust_wrap_sub(i, 1)] + fConst426 * fRec110[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec109_tmp[j252] = fRec109_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fZec71[i] - fConst430 * (fConst431 * fRec109[faust_wrap_sub(i, 2)] + fConst434 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec109_perm[j253] = fRec109_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 184 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec108_tmp[j254] = fRec108_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fConst430 * (fConst436 * fRec109[i] + fConst437 * fRec109[faust_wrap_sub(i, 1)] + fConst436 * fRec109[faust_wrap_sub(i, 2)]) - fConst438 * (fConst439 * fRec108[faust_wrap_sub(i, 2)] + fConst440 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec108_perm[j255] = fRec108_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec107_tmp[j256] = fRec107_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst438 * (fConst442 * fRec108[i] + fConst443 * fRec108[faust_wrap_sub(i, 1)] + fConst442 * fRec108[faust_wrap_sub(i, 2)]) - fConst444 * (fConst445 * fRec107[faust_wrap_sub(i, 2)] + fConst446 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec107_perm[j257] = fRec107_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec106_tmp[j258] = fRec106_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fSlow41 * fRec106[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst444 * (fConst448 * fRec107[i] + fConst449 * fRec107[faust_wrap_sub(i, 1)] + fConst448 * fRec107[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec106_perm[j259] = fRec106_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec119_tmp[j260] = fRec119_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fZec71[i] - fConst450 * (fConst451 * fRec119[faust_wrap_sub(i, 2)] + fConst452 * fRec119[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec119_perm[j261] = fRec119_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec118_tmp[j262] = fRec118_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fConst450 * (fConst454 * fRec119[i] + fConst455 * fRec119[faust_wrap_sub(i, 1)] + fConst454 * fRec119[faust_wrap_sub(i, 2)]) - fConst456 * (fConst457 * fRec118[faust_wrap_sub(i, 2)] + fConst458 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec118_perm[j263] = fRec118_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec117_tmp[j264] = fRec117_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fConst456 * (fConst459 * fRec118[i] + fConst460 * fRec118[faust_wrap_sub(i, 1)] + fConst459 * fRec118[faust_wrap_sub(i, 2)]) - fConst461 * (fConst462 * fRec117[faust_wrap_sub(i, 2)] + fConst463 * fRec117[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec117_perm[j265] = fRec117_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Vectorizable loop 190 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec72[i] = fConst461 * (fConst464 * fRec117[i] + fConst465 * fRec117[faust_wrap_sub(i, 1)] + fConst464 * fRec117[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec116_tmp[j266] = fRec116_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fZec72[i] - fConst468 * (fConst469 * fRec116[faust_wrap_sub(i, 2)] + fConst472 * fRec116[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec116_perm[j267] = fRec116_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 192 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec115_tmp[j268] = fRec115_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fConst468 * (fConst474 * fRec116[i] + fConst475 * fRec116[faust_wrap_sub(i, 1)] + fConst474 * fRec116[faust_wrap_sub(i, 2)]) - fConst476 * (fConst477 * fRec115[faust_wrap_sub(i, 2)] + fConst478 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec115_perm[j269] = fRec115_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec114_tmp[j270] = fRec114_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst476 * (fConst480 * fRec115[i] + fConst481 * fRec115[faust_wrap_sub(i, 1)] + fConst480 * fRec115[faust_wrap_sub(i, 2)]) - fConst482 * (fConst483 * fRec114[faust_wrap_sub(i, 2)] + fConst484 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec114_perm[j271] = fRec114_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec113_tmp[j272] = fRec113_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fSlow41 * fRec113[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst482 * (fConst486 * fRec114[i] + fConst487 * fRec114[faust_wrap_sub(i, 1)] + fConst486 * fRec114[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec113_perm[j273] = fRec113_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec126_tmp[j274] = fRec126_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fZec72[i] - fConst488 * (fConst489 * fRec126[faust_wrap_sub(i, 2)] + fConst490 * fRec126[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec126_perm[j275] = fRec126_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec125_tmp[j276] = fRec125_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fConst488 * (fConst492 * fRec126[i] + fConst493 * fRec126[faust_wrap_sub(i, 1)] + fConst492 * fRec126[faust_wrap_sub(i, 2)]) - fConst494 * (fConst495 * fRec125[faust_wrap_sub(i, 2)] + fConst496 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec125_perm[j277] = fRec125_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec124_tmp[j278] = fRec124_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fConst494 * (fConst497 * fRec125[i] + fConst498 * fRec125[faust_wrap_sub(i, 1)] + fConst497 * fRec125[faust_wrap_sub(i, 2)]) - fConst499 * (fConst500 * fRec124[faust_wrap_sub(i, 2)] + fConst501 * fRec124[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec124_perm[j279] = fRec124_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Vectorizable loop 198 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec73[i] = fConst499 * (fConst502 * fRec124[i] + fConst503 * fRec124[faust_wrap_sub(i, 1)] + fConst502 * fRec124[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec123_tmp[j280] = fRec123_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fZec73[i] - fConst506 * (fConst507 * fRec123[faust_wrap_sub(i, 2)] + fConst510 * fRec123[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec123_perm[j281] = fRec123_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 200 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec122_tmp[j282] = fRec122_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fConst506 * (fConst512 * fRec123[i] + fConst513 * fRec123[faust_wrap_sub(i, 1)] + fConst512 * fRec123[faust_wrap_sub(i, 2)]) - fConst514 * (fConst515 * fRec122[faust_wrap_sub(i, 2)] + fConst516 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec122_perm[j283] = fRec122_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec121_tmp[j284] = fRec121_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst514 * (fConst518 * fRec122[i] + fConst519 * fRec122[faust_wrap_sub(i, 1)] + fConst518 * fRec122[faust_wrap_sub(i, 2)]) - fConst520 * (fConst521 * fRec121[faust_wrap_sub(i, 2)] + fConst522 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec121_perm[j285] = fRec121_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec120_tmp[j286] = fRec120_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fSlow41 * fRec120[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst520 * (fConst524 * fRec121[i] + fConst525 * fRec121[faust_wrap_sub(i, 1)] + fConst524 * fRec121[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec120_perm[j287] = fRec120_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec130_tmp[j288] = fRec130_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec130[i] = fZec73[i] - fConst526 * (fConst527 * fRec130[faust_wrap_sub(i, 2)] + fConst528 * fRec130[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec130_perm[j289] = fRec130_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec129_tmp[j290] = fRec129_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec129[i] = fConst526 * (fConst530 * fRec130[i] + fConst531 * fRec130[faust_wrap_sub(i, 1)] + fConst530 * fRec130[faust_wrap_sub(i, 2)]) - fConst532 * (fConst533 * fRec129[faust_wrap_sub(i, 2)] + fConst534 * fRec129[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec129_perm[j291] = fRec129_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec128_tmp[j292] = fRec128_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec128[i] = fConst532 * (fConst535 * fRec129[i] + fConst536 * fRec129[faust_wrap_sub(i, 1)] + fConst535 * fRec129[faust_wrap_sub(i, 2)]) - fConst537 * (fConst538 * fRec128[faust_wrap_sub(i, 2)] + fConst539 * fRec128[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec128_perm[j293] = fRec128_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec127_tmp[j294] = fRec127_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fSlow41 * fRec127[faust_wrap_sub(i, 1)] + fSlow42 * std::fabs(fConst537 * (fConst540 * fRec128[i] + fConst541 * fRec128[faust_wrap_sub(i, 1)] + fConst540 * fRec128[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec127_perm[j295] = fRec127_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Vectorizable loop 207 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec32[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec36[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec43[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec50[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec57[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec64[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec71[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec78[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec85[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec92[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec99[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec106[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec113[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec120[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow43 + 2e+01 * std::log10(fRec127[i]));
				fZec74[i] = fZec60[i];
			}
			/* Vectorizable loop 208 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec74[i]);
			}
			/* Vectorizable loop 209 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec74[i]);
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
