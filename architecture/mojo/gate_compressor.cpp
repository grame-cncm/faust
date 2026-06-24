/* ------------------------------------------------------------
name: "gate_compressor"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

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

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	double fRec4_perm[4];
	FAUSTFLOAT fVslider1;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider2;
	double fRec6_perm[4];
	double fRec5_perm[4];
	FAUSTFLOAT fVslider3;
	double fRec7_perm[4];
	FAUSTFLOAT fVslider4;
	double fRec8_perm[4];
	int iRec9_perm[4];
	double fRec10_perm[4];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fEntry0;
	int iVec0_perm[4];
	double fConst2;
	double fYec0_perm[4];
	double fConst3;
	double fYec1_perm[4];
	double fYec2_perm[4];
	double fConst4;
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
	double fRec14_perm[4];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int iYec18_perm[4];
	int iRec15_perm[4];
	double fRec12_perm[4];
	double fRec11_perm[4];
	FAUSTFLOAT fHbargraph0;
	double fRec3_perm[4];
	int iYec19_perm[4];
	int iRec16_perm[4];
	double fRec1_perm[4];
	double fRec0_perm[4];
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	double fRec19_perm[4];
	double fRec18_perm[4];
	double fConst5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	double fRec17_perm[4];
	double fRec22_perm[4];
	double fRec21_perm[4];
	double fRec20_perm[4];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHbargraph1;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec26_perm[4];
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fRec25_perm[4];
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fRec24_perm[4];
	FAUSTFLOAT fHslider9;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fRec23_perm[4];
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec33_perm[4];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec32_perm[4];
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec31_perm[4];
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fRec30_perm[4];
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fRec29_perm[4];
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fRec28_perm[4];
	double fConst64;
	double fConst65;
	double fConst66;
	double fRec27_perm[4];
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec40_perm[4];
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fRec39_perm[4];
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fRec38_perm[4];
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fRec37_perm[4];
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fRec36_perm[4];
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fRec35_perm[4];
	double fConst102;
	double fConst103;
	double fConst104;
	double fRec34_perm[4];
	double fConst105;
	double fConst106;
	double fConst107;
	double fRec47_perm[4];
	double fConst108;
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fRec46_perm[4];
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fRec45_perm[4];
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fRec44_perm[4];
	double fConst128;
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst133;
	double fRec43_perm[4];
	double fConst134;
	double fConst135;
	double fConst136;
	double fConst137;
	double fConst138;
	double fConst139;
	double fRec42_perm[4];
	double fConst140;
	double fConst141;
	double fConst142;
	double fRec41_perm[4];
	double fConst143;
	double fConst144;
	double fConst145;
	double fRec54_perm[4];
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fRec53_perm[4];
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fRec52_perm[4];
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fRec51_perm[4];
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fRec50_perm[4];
	double fConst172;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fConst177;
	double fRec49_perm[4];
	double fConst178;
	double fConst179;
	double fConst180;
	double fRec48_perm[4];
	double fConst181;
	double fConst182;
	double fConst183;
	double fRec61_perm[4];
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fRec60_perm[4];
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fRec59_perm[4];
	double fConst195;
	double fConst196;
	double fConst197;
	double fConst198;
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fRec58_perm[4];
	double fConst204;
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fRec57_perm[4];
	double fConst210;
	double fConst211;
	double fConst212;
	double fConst213;
	double fConst214;
	double fConst215;
	double fRec56_perm[4];
	double fConst216;
	double fConst217;
	double fConst218;
	double fRec55_perm[4];
	double fConst219;
	double fConst220;
	double fConst221;
	double fRec68_perm[4];
	double fConst222;
	double fConst223;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fRec67_perm[4];
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fRec66_perm[4];
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst237;
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fRec65_perm[4];
	double fConst242;
	double fConst243;
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fRec64_perm[4];
	double fConst248;
	double fConst249;
	double fConst250;
	double fConst251;
	double fConst252;
	double fConst253;
	double fRec63_perm[4];
	double fConst254;
	double fConst255;
	double fConst256;
	double fRec62_perm[4];
	double fConst257;
	double fConst258;
	double fConst259;
	double fRec75_perm[4];
	double fConst260;
	double fConst261;
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fRec74_perm[4];
	double fConst266;
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fRec73_perm[4];
	double fConst271;
	double fConst272;
	double fConst273;
	double fConst274;
	double fConst275;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fRec72_perm[4];
	double fConst280;
	double fConst281;
	double fConst282;
	double fConst283;
	double fConst284;
	double fConst285;
	double fRec71_perm[4];
	double fConst286;
	double fConst287;
	double fConst288;
	double fConst289;
	double fConst290;
	double fConst291;
	double fRec70_perm[4];
	double fConst292;
	double fConst293;
	double fConst294;
	double fRec69_perm[4];
	double fConst295;
	double fConst296;
	double fConst297;
	double fRec82_perm[4];
	double fConst298;
	double fConst299;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fRec81_perm[4];
	double fConst304;
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst308;
	double fRec80_perm[4];
	double fConst309;
	double fConst310;
	double fConst311;
	double fConst312;
	double fConst313;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fRec79_perm[4];
	double fConst318;
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fConst323;
	double fRec78_perm[4];
	double fConst324;
	double fConst325;
	double fConst326;
	double fConst327;
	double fConst328;
	double fConst329;
	double fRec77_perm[4];
	double fConst330;
	double fConst331;
	double fConst332;
	double fRec76_perm[4];
	double fConst333;
	double fConst334;
	double fConst335;
	double fRec89_perm[4];
	double fConst336;
	double fConst337;
	double fConst338;
	double fConst339;
	double fConst340;
	double fConst341;
	double fRec88_perm[4];
	double fConst342;
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fRec87_perm[4];
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fRec86_perm[4];
	double fConst356;
	double fConst357;
	double fConst358;
	double fConst359;
	double fConst360;
	double fConst361;
	double fRec85_perm[4];
	double fConst362;
	double fConst363;
	double fConst364;
	double fConst365;
	double fConst366;
	double fConst367;
	double fRec84_perm[4];
	double fConst368;
	double fConst369;
	double fConst370;
	double fRec83_perm[4];
	double fConst371;
	double fConst372;
	double fConst373;
	double fRec96_perm[4];
	double fConst374;
	double fConst375;
	double fConst376;
	double fConst377;
	double fConst378;
	double fConst379;
	double fRec95_perm[4];
	double fConst380;
	double fConst381;
	double fConst382;
	double fConst383;
	double fConst384;
	double fRec94_perm[4];
	double fConst385;
	double fConst386;
	double fConst387;
	double fConst388;
	double fConst389;
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fRec93_perm[4];
	double fConst394;
	double fConst395;
	double fConst396;
	double fConst397;
	double fConst398;
	double fConst399;
	double fRec92_perm[4];
	double fConst400;
	double fConst401;
	double fConst402;
	double fConst403;
	double fConst404;
	double fConst405;
	double fRec91_perm[4];
	double fConst406;
	double fConst407;
	double fConst408;
	double fRec90_perm[4];
	double fConst409;
	double fConst410;
	double fConst411;
	double fRec103_perm[4];
	double fConst412;
	double fConst413;
	double fConst414;
	double fConst415;
	double fConst416;
	double fConst417;
	double fRec102_perm[4];
	double fConst418;
	double fConst419;
	double fConst420;
	double fConst421;
	double fConst422;
	double fRec101_perm[4];
	double fConst423;
	double fConst424;
	double fConst425;
	double fConst426;
	double fConst427;
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fRec100_perm[4];
	double fConst432;
	double fConst433;
	double fConst434;
	double fConst435;
	double fConst436;
	double fConst437;
	double fRec99_perm[4];
	double fConst438;
	double fConst439;
	double fConst440;
	double fConst441;
	double fConst442;
	double fConst443;
	double fRec98_perm[4];
	double fConst444;
	double fConst445;
	double fConst446;
	double fRec97_perm[4];
	double fConst447;
	double fConst448;
	double fConst449;
	double fRec110_perm[4];
	double fConst450;
	double fConst451;
	double fConst452;
	double fConst453;
	double fConst454;
	double fConst455;
	double fRec109_perm[4];
	double fConst456;
	double fConst457;
	double fConst458;
	double fConst459;
	double fConst460;
	double fRec108_perm[4];
	double fConst461;
	double fConst462;
	double fConst463;
	double fConst464;
	double fConst465;
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fRec107_perm[4];
	double fConst470;
	double fConst471;
	double fConst472;
	double fConst473;
	double fConst474;
	double fConst475;
	double fRec106_perm[4];
	double fConst476;
	double fConst477;
	double fConst478;
	double fConst479;
	double fConst480;
	double fConst481;
	double fRec105_perm[4];
	double fConst482;
	double fConst483;
	double fConst484;
	double fRec104_perm[4];
	double fConst485;
	double fConst486;
	double fConst487;
	double fRec117_perm[4];
	double fConst488;
	double fConst489;
	double fConst490;
	double fConst491;
	double fConst492;
	double fConst493;
	double fRec116_perm[4];
	double fConst494;
	double fConst495;
	double fConst496;
	double fConst497;
	double fConst498;
	double fRec115_perm[4];
	double fConst499;
	double fConst500;
	double fConst501;
	double fConst502;
	double fConst503;
	double fConst504;
	double fConst505;
	double fConst506;
	double fConst507;
	double fRec114_perm[4];
	double fConst508;
	double fConst509;
	double fConst510;
	double fConst511;
	double fConst512;
	double fConst513;
	double fRec113_perm[4];
	double fConst514;
	double fConst515;
	double fConst516;
	double fConst517;
	double fConst518;
	double fConst519;
	double fRec112_perm[4];
	double fConst520;
	double fConst521;
	double fConst522;
	double fRec111_perm[4];
	double fConst523;
	double fConst524;
	double fConst525;
	double fRec121_perm[4];
	double fConst526;
	double fConst527;
	double fConst528;
	double fConst529;
	double fConst530;
	double fConst531;
	double fRec120_perm[4];
	double fConst532;
	double fConst533;
	double fConst534;
	double fConst535;
	double fConst536;
	double fRec119_perm[4];
	double fConst537;
	double fConst538;
	double fRec118_perm[4];
	FAUSTFLOAT fHslider10;
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
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32");
		m->declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/copyright", "Julius O. Smith III");
		m->declare("effect.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)");
		m->declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("effect.lib/exciter_license", "MIT License (MIT)");
		m->declare("effect.lib/exciter_name", "Harmonic Exciter");
		m->declare("effect.lib/exciter_version", "1.0");
		m->declare("effect.lib/license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/version", "1.33");
		m->declare("filename", "gate_compressor.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
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
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "gate_compressor");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
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
		fConst3 = 0.041666666666666664 * mydsp_faustpower2_f(fConst0);
		fConst4 = 0.005208333333333333 * mydsp_faustpower3_f(fConst0);
		fConst5 = 2.0 / fConst0;
		fConst6 = std::tan(50265.48245743669 / fConst0);
		fConst7 = 1.0 / fConst6;
		fConst8 = 1.0 / ((fConst7 + 3.1897274020965583) / fConst6 + 4.076781969643807);
		fConst9 = (fConst7 + -3.1897274020965583) / fConst6 + 4.076781969643807;
		fConst10 = mydsp_faustpower2_f(fConst6);
		fConst11 = 1.0 / fConst10;
		fConst12 = 2.0 * (4.076781969643807 - fConst11);
		fConst13 = 0.0017661728399818856 / fConst10;
		fConst14 = fConst13 + 0.00040767818495825777;
		fConst15 = 2.0 * (0.00040767818495825777 - fConst13);
		fConst16 = 1.0 / ((fConst7 + 0.7431304601070396) / fConst6 + 1.450071084655647);
		fConst17 = (fConst7 + -0.7431304601070396) / fConst6 + 1.450071084655647;
		fConst18 = 2.0 * (1.450071084655647 - fConst11);
		fConst19 = 11.052052171507189 / fConst10;
		fConst20 = fConst19 + 1.450071084655647;
		fConst21 = 2.0 * (1.450071084655647 - fConst19);
		fConst22 = 1.0 / ((fConst7 + 0.157482159302087) / fConst6 + 0.9351401670315425);
		fConst23 = (fConst7 + -0.157482159302087) / fConst6 + 0.9351401670315425;
		fConst24 = 2.0 * (0.9351401670315425 - fConst11);
		fConst25 = 1e+03 / fConst0;
		fConst26 = 50.063807016150385 / fConst10;
		fConst27 = fConst26 + 0.9351401670315425;
		fConst28 = 2.0 * (0.9351401670315425 - fConst26);
		fConst29 = 1.0 / ((fConst7 + 0.782413046821645) / fConst6 + 0.24529150870616);
		fConst30 = (fConst7 + -0.782413046821645) / fConst6 + 0.24529150870616;
		fConst31 = 2.0 * (0.24529150870616 - fConst11);
		fConst32 = 9.9999997055e-05 / fConst10;
		fConst33 = fConst32 + 0.000433227200555;
		fConst34 = 2.0 * (0.000433227200555 - fConst32);
		fConst35 = 1.0 / ((fConst7 + 0.512478641889141) / fConst6 + 0.689621364484675);
		fConst36 = (fConst7 + -0.512478641889141) / fConst6 + 0.689621364484675;
		fConst37 = 2.0 * (0.689621364484675 - fConst11);
		fConst38 = fConst11 + 7.621731298870603;
		fConst39 = 2.0 * (7.621731298870603 - fConst11);
		fConst40 = 1.0 / ((fConst7 + 0.168404871113589) / fConst6 + 1.069358407707312);
		fConst41 = (fConst7 + -0.168404871113589) / fConst6 + 1.069358407707312;
		fConst42 = 2.0 * (1.069358407707312 - fConst11);
		fConst43 = fConst11 + 53.53615295455673;
		fConst44 = 2.0 * (53.53615295455673 - fConst11);
		fConst45 = std::tan(31665.269715622984 / fConst0);
		fConst46 = 1.0 / fConst45;
		fConst47 = 1.0 / ((fConst46 + 3.1897274020965583) / fConst45 + 4.076781969643807);
		fConst48 = (fConst46 + -3.1897274020965583) / fConst45 + 4.076781969643807;
		fConst49 = mydsp_faustpower2_f(fConst45);
		fConst50 = 1.0 / fConst49;
		fConst51 = 2.0 * (4.076781969643807 - fConst50);
		fConst52 = 0.0017661728399818856 / fConst49;
		fConst53 = fConst52 + 0.00040767818495825777;
		fConst54 = 2.0 * (0.00040767818495825777 - fConst52);
		fConst55 = 1.0 / ((fConst46 + 0.7431304601070396) / fConst45 + 1.450071084655647);
		fConst56 = (fConst46 + -0.7431304601070396) / fConst45 + 1.450071084655647;
		fConst57 = 2.0 * (1.450071084655647 - fConst50);
		fConst58 = 11.052052171507189 / fConst49;
		fConst59 = fConst58 + 1.450071084655647;
		fConst60 = 2.0 * (1.450071084655647 - fConst58);
		fConst61 = 1.0 / ((fConst46 + 0.157482159302087) / fConst45 + 0.9351401670315425);
		fConst62 = (fConst46 + -0.157482159302087) / fConst45 + 0.9351401670315425;
		fConst63 = 2.0 * (0.9351401670315425 - fConst50);
		fConst64 = 50.063807016150385 / fConst49;
		fConst65 = fConst64 + 0.9351401670315425;
		fConst66 = 2.0 * (0.9351401670315425 - fConst64);
		fConst67 = 1.0 / ((fConst46 + 0.782413046821645) / fConst45 + 0.24529150870616);
		fConst68 = (fConst46 + -0.782413046821645) / fConst45 + 0.24529150870616;
		fConst69 = 2.0 * (0.24529150870616 - fConst50);
		fConst70 = 9.9999997055e-05 / fConst49;
		fConst71 = fConst70 + 0.000433227200555;
		fConst72 = 2.0 * (0.000433227200555 - fConst70);
		fConst73 = 1.0 / ((fConst46 + 0.512478641889141) / fConst45 + 0.689621364484675);
		fConst74 = (fConst46 + -0.512478641889141) / fConst45 + 0.689621364484675;
		fConst75 = 2.0 * (0.689621364484675 - fConst50);
		fConst76 = fConst50 + 7.621731298870603;
		fConst77 = 2.0 * (7.621731298870603 - fConst50);
		fConst78 = 1.0 / ((fConst46 + 0.168404871113589) / fConst45 + 1.069358407707312);
		fConst79 = (fConst46 + -0.168404871113589) / fConst45 + 1.069358407707312;
		fConst80 = 2.0 * (1.069358407707312 - fConst50);
		fConst81 = fConst50 + 53.53615295455673;
		fConst82 = 2.0 * (53.53615295455673 - fConst50);
		fConst83 = std::tan(19947.869932656024 / fConst0);
		fConst84 = 1.0 / fConst83;
		fConst85 = 1.0 / ((fConst84 + 3.1897274020965583) / fConst83 + 4.076781969643807);
		fConst86 = (fConst84 + -3.1897274020965583) / fConst83 + 4.076781969643807;
		fConst87 = mydsp_faustpower2_f(fConst83);
		fConst88 = 1.0 / fConst87;
		fConst89 = 2.0 * (4.076781969643807 - fConst88);
		fConst90 = 0.0017661728399818856 / fConst87;
		fConst91 = fConst90 + 0.00040767818495825777;
		fConst92 = 2.0 * (0.00040767818495825777 - fConst90);
		fConst93 = 1.0 / ((fConst84 + 0.7431304601070396) / fConst83 + 1.450071084655647);
		fConst94 = (fConst84 + -0.7431304601070396) / fConst83 + 1.450071084655647;
		fConst95 = 2.0 * (1.450071084655647 - fConst88);
		fConst96 = 11.052052171507189 / fConst87;
		fConst97 = fConst96 + 1.450071084655647;
		fConst98 = 2.0 * (1.450071084655647 - fConst96);
		fConst99 = 1.0 / ((fConst84 + 0.157482159302087) / fConst83 + 0.9351401670315425);
		fConst100 = (fConst84 + -0.157482159302087) / fConst83 + 0.9351401670315425;
		fConst101 = 2.0 * (0.9351401670315425 - fConst88);
		fConst102 = 50.063807016150385 / fConst87;
		fConst103 = fConst102 + 0.9351401670315425;
		fConst104 = 2.0 * (0.9351401670315425 - fConst102);
		fConst105 = 1.0 / ((fConst84 + 0.782413046821645) / fConst83 + 0.24529150870616);
		fConst106 = (fConst84 + -0.782413046821645) / fConst83 + 0.24529150870616;
		fConst107 = 2.0 * (0.24529150870616 - fConst88);
		fConst108 = 9.9999997055e-05 / fConst87;
		fConst109 = fConst108 + 0.000433227200555;
		fConst110 = 2.0 * (0.000433227200555 - fConst108);
		fConst111 = 1.0 / ((fConst84 + 0.512478641889141) / fConst83 + 0.689621364484675);
		fConst112 = (fConst84 + -0.512478641889141) / fConst83 + 0.689621364484675;
		fConst113 = 2.0 * (0.689621364484675 - fConst88);
		fConst114 = fConst88 + 7.621731298870603;
		fConst115 = 2.0 * (7.621731298870603 - fConst88);
		fConst116 = 1.0 / ((fConst84 + 0.168404871113589) / fConst83 + 1.069358407707312);
		fConst117 = (fConst84 + -0.168404871113589) / fConst83 + 1.069358407707312;
		fConst118 = 2.0 * (1.069358407707312 - fConst88);
		fConst119 = fConst88 + 53.53615295455673;
		fConst120 = 2.0 * (53.53615295455673 - fConst88);
		fConst121 = std::tan(12566.370614359172 / fConst0);
		fConst122 = 1.0 / fConst121;
		fConst123 = 1.0 / ((fConst122 + 3.1897274020965583) / fConst121 + 4.076781969643807);
		fConst124 = (fConst122 + -3.1897274020965583) / fConst121 + 4.076781969643807;
		fConst125 = mydsp_faustpower2_f(fConst121);
		fConst126 = 1.0 / fConst125;
		fConst127 = 2.0 * (4.076781969643807 - fConst126);
		fConst128 = 0.0017661728399818856 / fConst125;
		fConst129 = fConst128 + 0.00040767818495825777;
		fConst130 = 2.0 * (0.00040767818495825777 - fConst128);
		fConst131 = 1.0 / ((fConst122 + 0.7431304601070396) / fConst121 + 1.450071084655647);
		fConst132 = (fConst122 + -0.7431304601070396) / fConst121 + 1.450071084655647;
		fConst133 = 2.0 * (1.450071084655647 - fConst126);
		fConst134 = 11.052052171507189 / fConst125;
		fConst135 = fConst134 + 1.450071084655647;
		fConst136 = 2.0 * (1.450071084655647 - fConst134);
		fConst137 = 1.0 / ((fConst122 + 0.157482159302087) / fConst121 + 0.9351401670315425);
		fConst138 = (fConst122 + -0.157482159302087) / fConst121 + 0.9351401670315425;
		fConst139 = 2.0 * (0.9351401670315425 - fConst126);
		fConst140 = 50.063807016150385 / fConst125;
		fConst141 = fConst140 + 0.9351401670315425;
		fConst142 = 2.0 * (0.9351401670315425 - fConst140);
		fConst143 = 1.0 / ((fConst122 + 0.782413046821645) / fConst121 + 0.24529150870616);
		fConst144 = (fConst122 + -0.782413046821645) / fConst121 + 0.24529150870616;
		fConst145 = 2.0 * (0.24529150870616 - fConst126);
		fConst146 = 9.9999997055e-05 / fConst125;
		fConst147 = fConst146 + 0.000433227200555;
		fConst148 = 2.0 * (0.000433227200555 - fConst146);
		fConst149 = 1.0 / ((fConst122 + 0.512478641889141) / fConst121 + 0.689621364484675);
		fConst150 = (fConst122 + -0.512478641889141) / fConst121 + 0.689621364484675;
		fConst151 = 2.0 * (0.689621364484675 - fConst126);
		fConst152 = fConst126 + 7.621731298870603;
		fConst153 = 2.0 * (7.621731298870603 - fConst126);
		fConst154 = 1.0 / ((fConst122 + 0.168404871113589) / fConst121 + 1.069358407707312);
		fConst155 = (fConst122 + -0.168404871113589) / fConst121 + 1.069358407707312;
		fConst156 = 2.0 * (1.069358407707312 - fConst126);
		fConst157 = fConst126 + 53.53615295455673;
		fConst158 = 2.0 * (53.53615295455673 - fConst126);
		fConst159 = std::tan(7916.317428905746 / fConst0);
		fConst160 = 1.0 / fConst159;
		fConst161 = 1.0 / ((fConst160 + 3.1897274020965583) / fConst159 + 4.076781969643807);
		fConst162 = (fConst160 + -3.1897274020965583) / fConst159 + 4.076781969643807;
		fConst163 = mydsp_faustpower2_f(fConst159);
		fConst164 = 1.0 / fConst163;
		fConst165 = 2.0 * (4.076781969643807 - fConst164);
		fConst166 = 0.0017661728399818856 / fConst163;
		fConst167 = fConst166 + 0.00040767818495825777;
		fConst168 = 2.0 * (0.00040767818495825777 - fConst166);
		fConst169 = 1.0 / ((fConst160 + 0.7431304601070396) / fConst159 + 1.450071084655647);
		fConst170 = (fConst160 + -0.7431304601070396) / fConst159 + 1.450071084655647;
		fConst171 = 2.0 * (1.450071084655647 - fConst164);
		fConst172 = 11.052052171507189 / fConst163;
		fConst173 = fConst172 + 1.450071084655647;
		fConst174 = 2.0 * (1.450071084655647 - fConst172);
		fConst175 = 1.0 / ((fConst160 + 0.157482159302087) / fConst159 + 0.9351401670315425);
		fConst176 = (fConst160 + -0.157482159302087) / fConst159 + 0.9351401670315425;
		fConst177 = 2.0 * (0.9351401670315425 - fConst164);
		fConst178 = 50.063807016150385 / fConst163;
		fConst179 = fConst178 + 0.9351401670315425;
		fConst180 = 2.0 * (0.9351401670315425 - fConst178);
		fConst181 = 1.0 / ((fConst160 + 0.782413046821645) / fConst159 + 0.24529150870616);
		fConst182 = (fConst160 + -0.782413046821645) / fConst159 + 0.24529150870616;
		fConst183 = 2.0 * (0.24529150870616 - fConst164);
		fConst184 = 9.9999997055e-05 / fConst163;
		fConst185 = fConst184 + 0.000433227200555;
		fConst186 = 2.0 * (0.000433227200555 - fConst184);
		fConst187 = 1.0 / ((fConst160 + 0.512478641889141) / fConst159 + 0.689621364484675);
		fConst188 = (fConst160 + -0.512478641889141) / fConst159 + 0.689621364484675;
		fConst189 = 2.0 * (0.689621364484675 - fConst164);
		fConst190 = fConst164 + 7.621731298870603;
		fConst191 = 2.0 * (7.621731298870603 - fConst164);
		fConst192 = 1.0 / ((fConst160 + 0.168404871113589) / fConst159 + 1.069358407707312);
		fConst193 = (fConst160 + -0.168404871113589) / fConst159 + 1.069358407707312;
		fConst194 = 2.0 * (1.069358407707312 - fConst164);
		fConst195 = fConst164 + 53.53615295455673;
		fConst196 = 2.0 * (53.53615295455673 - fConst164);
		fConst197 = std::tan(4986.967483164005 / fConst0);
		fConst198 = 1.0 / fConst197;
		fConst199 = 1.0 / ((fConst198 + 3.1897274020965583) / fConst197 + 4.076781969643807);
		fConst200 = (fConst198 + -3.1897274020965583) / fConst197 + 4.076781969643807;
		fConst201 = mydsp_faustpower2_f(fConst197);
		fConst202 = 1.0 / fConst201;
		fConst203 = 2.0 * (4.076781969643807 - fConst202);
		fConst204 = 0.0017661728399818856 / fConst201;
		fConst205 = fConst204 + 0.00040767818495825777;
		fConst206 = 2.0 * (0.00040767818495825777 - fConst204);
		fConst207 = 1.0 / ((fConst198 + 0.7431304601070396) / fConst197 + 1.450071084655647);
		fConst208 = (fConst198 + -0.7431304601070396) / fConst197 + 1.450071084655647;
		fConst209 = 2.0 * (1.450071084655647 - fConst202);
		fConst210 = 11.052052171507189 / fConst201;
		fConst211 = fConst210 + 1.450071084655647;
		fConst212 = 2.0 * (1.450071084655647 - fConst210);
		fConst213 = 1.0 / ((fConst198 + 0.157482159302087) / fConst197 + 0.9351401670315425);
		fConst214 = (fConst198 + -0.157482159302087) / fConst197 + 0.9351401670315425;
		fConst215 = 2.0 * (0.9351401670315425 - fConst202);
		fConst216 = 50.063807016150385 / fConst201;
		fConst217 = fConst216 + 0.9351401670315425;
		fConst218 = 2.0 * (0.9351401670315425 - fConst216);
		fConst219 = 1.0 / ((fConst198 + 0.782413046821645) / fConst197 + 0.24529150870616);
		fConst220 = (fConst198 + -0.782413046821645) / fConst197 + 0.24529150870616;
		fConst221 = 2.0 * (0.24529150870616 - fConst202);
		fConst222 = 9.9999997055e-05 / fConst201;
		fConst223 = fConst222 + 0.000433227200555;
		fConst224 = 2.0 * (0.000433227200555 - fConst222);
		fConst225 = 1.0 / ((fConst198 + 0.512478641889141) / fConst197 + 0.689621364484675);
		fConst226 = (fConst198 + -0.512478641889141) / fConst197 + 0.689621364484675;
		fConst227 = 2.0 * (0.689621364484675 - fConst202);
		fConst228 = fConst202 + 7.621731298870603;
		fConst229 = 2.0 * (7.621731298870603 - fConst202);
		fConst230 = 1.0 / ((fConst198 + 0.168404871113589) / fConst197 + 1.069358407707312);
		fConst231 = (fConst198 + -0.168404871113589) / fConst197 + 1.069358407707312;
		fConst232 = 2.0 * (1.069358407707312 - fConst202);
		fConst233 = fConst202 + 53.53615295455673;
		fConst234 = 2.0 * (53.53615295455673 - fConst202);
		fConst235 = std::tan(3141.592653589793 / fConst0);
		fConst236 = 1.0 / fConst235;
		fConst237 = 1.0 / ((fConst236 + 3.1897274020965583) / fConst235 + 4.076781969643807);
		fConst238 = (fConst236 + -3.1897274020965583) / fConst235 + 4.076781969643807;
		fConst239 = mydsp_faustpower2_f(fConst235);
		fConst240 = 1.0 / fConst239;
		fConst241 = 2.0 * (4.076781969643807 - fConst240);
		fConst242 = 0.0017661728399818856 / fConst239;
		fConst243 = fConst242 + 0.00040767818495825777;
		fConst244 = 2.0 * (0.00040767818495825777 - fConst242);
		fConst245 = 1.0 / ((fConst236 + 0.7431304601070396) / fConst235 + 1.450071084655647);
		fConst246 = (fConst236 + -0.7431304601070396) / fConst235 + 1.450071084655647;
		fConst247 = 2.0 * (1.450071084655647 - fConst240);
		fConst248 = 11.052052171507189 / fConst239;
		fConst249 = fConst248 + 1.450071084655647;
		fConst250 = 2.0 * (1.450071084655647 - fConst248);
		fConst251 = 1.0 / ((fConst236 + 0.157482159302087) / fConst235 + 0.9351401670315425);
		fConst252 = (fConst236 + -0.157482159302087) / fConst235 + 0.9351401670315425;
		fConst253 = 2.0 * (0.9351401670315425 - fConst240);
		fConst254 = 50.063807016150385 / fConst239;
		fConst255 = fConst254 + 0.9351401670315425;
		fConst256 = 2.0 * (0.9351401670315425 - fConst254);
		fConst257 = 1.0 / ((fConst236 + 0.782413046821645) / fConst235 + 0.24529150870616);
		fConst258 = (fConst236 + -0.782413046821645) / fConst235 + 0.24529150870616;
		fConst259 = 2.0 * (0.24529150870616 - fConst240);
		fConst260 = 9.9999997055e-05 / fConst239;
		fConst261 = fConst260 + 0.000433227200555;
		fConst262 = 2.0 * (0.000433227200555 - fConst260);
		fConst263 = 1.0 / ((fConst236 + 0.512478641889141) / fConst235 + 0.689621364484675);
		fConst264 = (fConst236 + -0.512478641889141) / fConst235 + 0.689621364484675;
		fConst265 = 2.0 * (0.689621364484675 - fConst240);
		fConst266 = fConst240 + 7.621731298870603;
		fConst267 = 2.0 * (7.621731298870603 - fConst240);
		fConst268 = 1.0 / ((fConst236 + 0.168404871113589) / fConst235 + 1.069358407707312);
		fConst269 = (fConst236 + -0.168404871113589) / fConst235 + 1.069358407707312;
		fConst270 = 2.0 * (1.069358407707312 - fConst240);
		fConst271 = fConst240 + 53.53615295455673;
		fConst272 = 2.0 * (53.53615295455673 - fConst240);
		fConst273 = std::tan(1979.079357226436 / fConst0);
		fConst274 = 1.0 / fConst273;
		fConst275 = 1.0 / ((fConst274 + 3.1897274020965583) / fConst273 + 4.076781969643807);
		fConst276 = (fConst274 + -3.1897274020965583) / fConst273 + 4.076781969643807;
		fConst277 = mydsp_faustpower2_f(fConst273);
		fConst278 = 1.0 / fConst277;
		fConst279 = 2.0 * (4.076781969643807 - fConst278);
		fConst280 = 0.0017661728399818856 / fConst277;
		fConst281 = fConst280 + 0.00040767818495825777;
		fConst282 = 2.0 * (0.00040767818495825777 - fConst280);
		fConst283 = 1.0 / ((fConst274 + 0.7431304601070396) / fConst273 + 1.450071084655647);
		fConst284 = (fConst274 + -0.7431304601070396) / fConst273 + 1.450071084655647;
		fConst285 = 2.0 * (1.450071084655647 - fConst278);
		fConst286 = 11.052052171507189 / fConst277;
		fConst287 = fConst286 + 1.450071084655647;
		fConst288 = 2.0 * (1.450071084655647 - fConst286);
		fConst289 = 1.0 / ((fConst274 + 0.157482159302087) / fConst273 + 0.9351401670315425);
		fConst290 = (fConst274 + -0.157482159302087) / fConst273 + 0.9351401670315425;
		fConst291 = 2.0 * (0.9351401670315425 - fConst278);
		fConst292 = 50.063807016150385 / fConst277;
		fConst293 = fConst292 + 0.9351401670315425;
		fConst294 = 2.0 * (0.9351401670315425 - fConst292);
		fConst295 = 1.0 / ((fConst274 + 0.782413046821645) / fConst273 + 0.24529150870616);
		fConst296 = (fConst274 + -0.782413046821645) / fConst273 + 0.24529150870616;
		fConst297 = 2.0 * (0.24529150870616 - fConst278);
		fConst298 = 9.9999997055e-05 / fConst277;
		fConst299 = fConst298 + 0.000433227200555;
		fConst300 = 2.0 * (0.000433227200555 - fConst298);
		fConst301 = 1.0 / ((fConst274 + 0.512478641889141) / fConst273 + 0.689621364484675);
		fConst302 = (fConst274 + -0.512478641889141) / fConst273 + 0.689621364484675;
		fConst303 = 2.0 * (0.689621364484675 - fConst278);
		fConst304 = fConst278 + 7.621731298870603;
		fConst305 = 2.0 * (7.621731298870603 - fConst278);
		fConst306 = 1.0 / ((fConst274 + 0.168404871113589) / fConst273 + 1.069358407707312);
		fConst307 = (fConst274 + -0.168404871113589) / fConst273 + 1.069358407707312;
		fConst308 = 2.0 * (1.069358407707312 - fConst278);
		fConst309 = fConst278 + 53.53615295455673;
		fConst310 = 2.0 * (53.53615295455673 - fConst278);
		fConst311 = std::tan(1246.7418707910015 / fConst0);
		fConst312 = 1.0 / fConst311;
		fConst313 = 1.0 / ((fConst312 + 3.1897274020965583) / fConst311 + 4.076781969643807);
		fConst314 = (fConst312 + -3.1897274020965583) / fConst311 + 4.076781969643807;
		fConst315 = mydsp_faustpower2_f(fConst311);
		fConst316 = 1.0 / fConst315;
		fConst317 = 2.0 * (4.076781969643807 - fConst316);
		fConst318 = 0.0017661728399818856 / fConst315;
		fConst319 = fConst318 + 0.00040767818495825777;
		fConst320 = 2.0 * (0.00040767818495825777 - fConst318);
		fConst321 = 1.0 / ((fConst312 + 0.7431304601070396) / fConst311 + 1.450071084655647);
		fConst322 = (fConst312 + -0.7431304601070396) / fConst311 + 1.450071084655647;
		fConst323 = 2.0 * (1.450071084655647 - fConst316);
		fConst324 = 11.052052171507189 / fConst315;
		fConst325 = fConst324 + 1.450071084655647;
		fConst326 = 2.0 * (1.450071084655647 - fConst324);
		fConst327 = 1.0 / ((fConst312 + 0.157482159302087) / fConst311 + 0.9351401670315425);
		fConst328 = (fConst312 + -0.157482159302087) / fConst311 + 0.9351401670315425;
		fConst329 = 2.0 * (0.9351401670315425 - fConst316);
		fConst330 = 50.063807016150385 / fConst315;
		fConst331 = fConst330 + 0.9351401670315425;
		fConst332 = 2.0 * (0.9351401670315425 - fConst330);
		fConst333 = 1.0 / ((fConst312 + 0.782413046821645) / fConst311 + 0.24529150870616);
		fConst334 = (fConst312 + -0.782413046821645) / fConst311 + 0.24529150870616;
		fConst335 = 2.0 * (0.24529150870616 - fConst316);
		fConst336 = 9.9999997055e-05 / fConst315;
		fConst337 = fConst336 + 0.000433227200555;
		fConst338 = 2.0 * (0.000433227200555 - fConst336);
		fConst339 = 1.0 / ((fConst312 + 0.512478641889141) / fConst311 + 0.689621364484675);
		fConst340 = (fConst312 + -0.512478641889141) / fConst311 + 0.689621364484675;
		fConst341 = 2.0 * (0.689621364484675 - fConst316);
		fConst342 = fConst316 + 7.621731298870603;
		fConst343 = 2.0 * (7.621731298870603 - fConst316);
		fConst344 = 1.0 / ((fConst312 + 0.168404871113589) / fConst311 + 1.069358407707312);
		fConst345 = (fConst312 + -0.168404871113589) / fConst311 + 1.069358407707312;
		fConst346 = 2.0 * (1.069358407707312 - fConst316);
		fConst347 = fConst316 + 53.53615295455673;
		fConst348 = 2.0 * (53.53615295455673 - fConst316);
		fConst349 = std::tan(785.3981633974482 / fConst0);
		fConst350 = 1.0 / fConst349;
		fConst351 = 1.0 / ((fConst350 + 3.1897274020965583) / fConst349 + 4.076781969643807);
		fConst352 = (fConst350 + -3.1897274020965583) / fConst349 + 4.076781969643807;
		fConst353 = mydsp_faustpower2_f(fConst349);
		fConst354 = 1.0 / fConst353;
		fConst355 = 2.0 * (4.076781969643807 - fConst354);
		fConst356 = 0.0017661728399818856 / fConst353;
		fConst357 = fConst356 + 0.00040767818495825777;
		fConst358 = 2.0 * (0.00040767818495825777 - fConst356);
		fConst359 = 1.0 / ((fConst350 + 0.7431304601070396) / fConst349 + 1.450071084655647);
		fConst360 = (fConst350 + -0.7431304601070396) / fConst349 + 1.450071084655647;
		fConst361 = 2.0 * (1.450071084655647 - fConst354);
		fConst362 = 11.052052171507189 / fConst353;
		fConst363 = fConst362 + 1.450071084655647;
		fConst364 = 2.0 * (1.450071084655647 - fConst362);
		fConst365 = 1.0 / ((fConst350 + 0.157482159302087) / fConst349 + 0.9351401670315425);
		fConst366 = (fConst350 + -0.157482159302087) / fConst349 + 0.9351401670315425;
		fConst367 = 2.0 * (0.9351401670315425 - fConst354);
		fConst368 = 50.063807016150385 / fConst353;
		fConst369 = fConst368 + 0.9351401670315425;
		fConst370 = 2.0 * (0.9351401670315425 - fConst368);
		fConst371 = 1.0 / ((fConst350 + 0.782413046821645) / fConst349 + 0.24529150870616);
		fConst372 = (fConst350 + -0.782413046821645) / fConst349 + 0.24529150870616;
		fConst373 = 2.0 * (0.24529150870616 - fConst354);
		fConst374 = 9.9999997055e-05 / fConst353;
		fConst375 = fConst374 + 0.000433227200555;
		fConst376 = 2.0 * (0.000433227200555 - fConst374);
		fConst377 = 1.0 / ((fConst350 + 0.512478641889141) / fConst349 + 0.689621364484675);
		fConst378 = (fConst350 + -0.512478641889141) / fConst349 + 0.689621364484675;
		fConst379 = 2.0 * (0.689621364484675 - fConst354);
		fConst380 = fConst354 + 7.621731298870603;
		fConst381 = 2.0 * (7.621731298870603 - fConst354);
		fConst382 = 1.0 / ((fConst350 + 0.168404871113589) / fConst349 + 1.069358407707312);
		fConst383 = (fConst350 + -0.168404871113589) / fConst349 + 1.069358407707312;
		fConst384 = 2.0 * (1.069358407707312 - fConst354);
		fConst385 = fConst354 + 53.53615295455673;
		fConst386 = 2.0 * (53.53615295455673 - fConst354);
		fConst387 = std::tan(494.769839306609 / fConst0);
		fConst388 = 1.0 / fConst387;
		fConst389 = 1.0 / ((fConst388 + 3.1897274020965583) / fConst387 + 4.076781969643807);
		fConst390 = (fConst388 + -3.1897274020965583) / fConst387 + 4.076781969643807;
		fConst391 = mydsp_faustpower2_f(fConst387);
		fConst392 = 1.0 / fConst391;
		fConst393 = 2.0 * (4.076781969643807 - fConst392);
		fConst394 = 0.0017661728399818856 / fConst391;
		fConst395 = fConst394 + 0.00040767818495825777;
		fConst396 = 2.0 * (0.00040767818495825777 - fConst394);
		fConst397 = 1.0 / ((fConst388 + 0.7431304601070396) / fConst387 + 1.450071084655647);
		fConst398 = (fConst388 + -0.7431304601070396) / fConst387 + 1.450071084655647;
		fConst399 = 2.0 * (1.450071084655647 - fConst392);
		fConst400 = 11.052052171507189 / fConst391;
		fConst401 = fConst400 + 1.450071084655647;
		fConst402 = 2.0 * (1.450071084655647 - fConst400);
		fConst403 = 1.0 / ((fConst388 + 0.157482159302087) / fConst387 + 0.9351401670315425);
		fConst404 = (fConst388 + -0.157482159302087) / fConst387 + 0.9351401670315425;
		fConst405 = 2.0 * (0.9351401670315425 - fConst392);
		fConst406 = 50.063807016150385 / fConst391;
		fConst407 = fConst406 + 0.9351401670315425;
		fConst408 = 2.0 * (0.9351401670315425 - fConst406);
		fConst409 = 1.0 / ((fConst388 + 0.782413046821645) / fConst387 + 0.24529150870616);
		fConst410 = (fConst388 + -0.782413046821645) / fConst387 + 0.24529150870616;
		fConst411 = 2.0 * (0.24529150870616 - fConst392);
		fConst412 = 9.9999997055e-05 / fConst391;
		fConst413 = fConst412 + 0.000433227200555;
		fConst414 = 2.0 * (0.000433227200555 - fConst412);
		fConst415 = 1.0 / ((fConst388 + 0.512478641889141) / fConst387 + 0.689621364484675);
		fConst416 = (fConst388 + -0.512478641889141) / fConst387 + 0.689621364484675;
		fConst417 = 2.0 * (0.689621364484675 - fConst392);
		fConst418 = fConst392 + 7.621731298870603;
		fConst419 = 2.0 * (7.621731298870603 - fConst392);
		fConst420 = 1.0 / ((fConst388 + 0.168404871113589) / fConst387 + 1.069358407707312);
		fConst421 = (fConst388 + -0.168404871113589) / fConst387 + 1.069358407707312;
		fConst422 = 2.0 * (1.069358407707312 - fConst392);
		fConst423 = fConst392 + 53.53615295455673;
		fConst424 = 2.0 * (53.53615295455673 - fConst392);
		fConst425 = std::tan(311.68546769775037 / fConst0);
		fConst426 = 1.0 / fConst425;
		fConst427 = 1.0 / ((fConst426 + 3.1897274020965583) / fConst425 + 4.076781969643807);
		fConst428 = (fConst426 + -3.1897274020965583) / fConst425 + 4.076781969643807;
		fConst429 = mydsp_faustpower2_f(fConst425);
		fConst430 = 1.0 / fConst429;
		fConst431 = 2.0 * (4.076781969643807 - fConst430);
		fConst432 = 0.0017661728399818856 / fConst429;
		fConst433 = fConst432 + 0.00040767818495825777;
		fConst434 = 2.0 * (0.00040767818495825777 - fConst432);
		fConst435 = 1.0 / ((fConst426 + 0.7431304601070396) / fConst425 + 1.450071084655647);
		fConst436 = (fConst426 + -0.7431304601070396) / fConst425 + 1.450071084655647;
		fConst437 = 2.0 * (1.450071084655647 - fConst430);
		fConst438 = 11.052052171507189 / fConst429;
		fConst439 = fConst438 + 1.450071084655647;
		fConst440 = 2.0 * (1.450071084655647 - fConst438);
		fConst441 = 1.0 / ((fConst426 + 0.157482159302087) / fConst425 + 0.9351401670315425);
		fConst442 = (fConst426 + -0.157482159302087) / fConst425 + 0.9351401670315425;
		fConst443 = 2.0 * (0.9351401670315425 - fConst430);
		fConst444 = 50.063807016150385 / fConst429;
		fConst445 = fConst444 + 0.9351401670315425;
		fConst446 = 2.0 * (0.9351401670315425 - fConst444);
		fConst447 = 1.0 / ((fConst426 + 0.782413046821645) / fConst425 + 0.24529150870616);
		fConst448 = (fConst426 + -0.782413046821645) / fConst425 + 0.24529150870616;
		fConst449 = 2.0 * (0.24529150870616 - fConst430);
		fConst450 = 9.9999997055e-05 / fConst429;
		fConst451 = fConst450 + 0.000433227200555;
		fConst452 = 2.0 * (0.000433227200555 - fConst450);
		fConst453 = 1.0 / ((fConst426 + 0.512478641889141) / fConst425 + 0.689621364484675);
		fConst454 = (fConst426 + -0.512478641889141) / fConst425 + 0.689621364484675;
		fConst455 = 2.0 * (0.689621364484675 - fConst430);
		fConst456 = fConst430 + 7.621731298870603;
		fConst457 = 2.0 * (7.621731298870603 - fConst430);
		fConst458 = 1.0 / ((fConst426 + 0.168404871113589) / fConst425 + 1.069358407707312);
		fConst459 = (fConst426 + -0.168404871113589) / fConst425 + 1.069358407707312;
		fConst460 = 2.0 * (1.069358407707312 - fConst430);
		fConst461 = fConst430 + 53.53615295455673;
		fConst462 = 2.0 * (53.53615295455673 - fConst430);
		fConst463 = std::tan(196.34954084936206 / fConst0);
		fConst464 = 1.0 / fConst463;
		fConst465 = 1.0 / ((fConst464 + 3.1897274020965583) / fConst463 + 4.076781969643807);
		fConst466 = (fConst464 + -3.1897274020965583) / fConst463 + 4.076781969643807;
		fConst467 = mydsp_faustpower2_f(fConst463);
		fConst468 = 1.0 / fConst467;
		fConst469 = 2.0 * (4.076781969643807 - fConst468);
		fConst470 = 0.0017661728399818856 / fConst467;
		fConst471 = fConst470 + 0.00040767818495825777;
		fConst472 = 2.0 * (0.00040767818495825777 - fConst470);
		fConst473 = 1.0 / ((fConst464 + 0.7431304601070396) / fConst463 + 1.450071084655647);
		fConst474 = (fConst464 + -0.7431304601070396) / fConst463 + 1.450071084655647;
		fConst475 = 2.0 * (1.450071084655647 - fConst468);
		fConst476 = 11.052052171507189 / fConst467;
		fConst477 = fConst476 + 1.450071084655647;
		fConst478 = 2.0 * (1.450071084655647 - fConst476);
		fConst479 = 1.0 / ((fConst464 + 0.157482159302087) / fConst463 + 0.9351401670315425);
		fConst480 = (fConst464 + -0.157482159302087) / fConst463 + 0.9351401670315425;
		fConst481 = 2.0 * (0.9351401670315425 - fConst468);
		fConst482 = 50.063807016150385 / fConst467;
		fConst483 = fConst482 + 0.9351401670315425;
		fConst484 = 2.0 * (0.9351401670315425 - fConst482);
		fConst485 = 1.0 / ((fConst464 + 0.782413046821645) / fConst463 + 0.24529150870616);
		fConst486 = (fConst464 + -0.782413046821645) / fConst463 + 0.24529150870616;
		fConst487 = 2.0 * (0.24529150870616 - fConst468);
		fConst488 = 9.9999997055e-05 / fConst467;
		fConst489 = fConst488 + 0.000433227200555;
		fConst490 = 2.0 * (0.000433227200555 - fConst488);
		fConst491 = 1.0 / ((fConst464 + 0.512478641889141) / fConst463 + 0.689621364484675);
		fConst492 = (fConst464 + -0.512478641889141) / fConst463 + 0.689621364484675;
		fConst493 = 2.0 * (0.689621364484675 - fConst468);
		fConst494 = fConst468 + 7.621731298870603;
		fConst495 = 2.0 * (7.621731298870603 - fConst468);
		fConst496 = 1.0 / ((fConst464 + 0.168404871113589) / fConst463 + 1.069358407707312);
		fConst497 = (fConst464 + -0.168404871113589) / fConst463 + 1.069358407707312;
		fConst498 = 2.0 * (1.069358407707312 - fConst468);
		fConst499 = fConst468 + 53.53615295455673;
		fConst500 = 2.0 * (53.53615295455673 - fConst468);
		fConst501 = std::tan(123.69245982665232 / fConst0);
		fConst502 = 1.0 / fConst501;
		fConst503 = 1.0 / ((fConst502 + 3.1897274020965583) / fConst501 + 4.076781969643807);
		fConst504 = (fConst502 + -3.1897274020965583) / fConst501 + 4.076781969643807;
		fConst505 = mydsp_faustpower2_f(fConst501);
		fConst506 = 1.0 / fConst505;
		fConst507 = 2.0 * (4.076781969643807 - fConst506);
		fConst508 = 0.0017661728399818856 / fConst505;
		fConst509 = fConst508 + 0.00040767818495825777;
		fConst510 = 2.0 * (0.00040767818495825777 - fConst508);
		fConst511 = 1.0 / ((fConst502 + 0.7431304601070396) / fConst501 + 1.450071084655647);
		fConst512 = (fConst502 + -0.7431304601070396) / fConst501 + 1.450071084655647;
		fConst513 = 2.0 * (1.450071084655647 - fConst506);
		fConst514 = 11.052052171507189 / fConst505;
		fConst515 = fConst514 + 1.450071084655647;
		fConst516 = 2.0 * (1.450071084655647 - fConst514);
		fConst517 = 1.0 / ((fConst502 + 0.157482159302087) / fConst501 + 0.9351401670315425);
		fConst518 = (fConst502 + -0.157482159302087) / fConst501 + 0.9351401670315425;
		fConst519 = 2.0 * (0.9351401670315425 - fConst506);
		fConst520 = 50.063807016150385 / fConst505;
		fConst521 = fConst520 + 0.9351401670315425;
		fConst522 = 2.0 * (0.9351401670315425 - fConst520);
		fConst523 = 1.0 / ((fConst502 + 0.782413046821645) / fConst501 + 0.24529150870616);
		fConst524 = (fConst502 + -0.782413046821645) / fConst501 + 0.24529150870616;
		fConst525 = 2.0 * (0.24529150870616 - fConst506);
		fConst526 = 9.9999997055e-05 / fConst505;
		fConst527 = fConst526 + 0.000433227200555;
		fConst528 = 2.0 * (0.000433227200555 - fConst526);
		fConst529 = 1.0 / ((fConst502 + 0.512478641889141) / fConst501 + 0.689621364484675);
		fConst530 = (fConst502 + -0.512478641889141) / fConst501 + 0.689621364484675;
		fConst531 = 2.0 * (0.689621364484675 - fConst506);
		fConst532 = fConst506 + 7.621731298870603;
		fConst533 = 2.0 * (7.621731298870603 - fConst506);
		fConst534 = 1.0 / ((fConst502 + 0.168404871113589) / fConst501 + 1.069358407707312);
		fConst535 = (fConst502 + -0.168404871113589) / fConst501 + 1.069358407707312;
		fConst536 = 2.0 * (1.069358407707312 - fConst506);
		fConst537 = fConst506 + 53.53615295455673;
		fConst538 = 2.0 * (53.53615295455673 - fConst506);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(-2e+01);
		fVslider1 = static_cast<FAUSTFLOAT>(0.1);
		fVslider2 = static_cast<FAUSTFLOAT>(49.0);
		fVslider3 = static_cast<FAUSTFLOAT>(-0.1);
		fVslider4 = static_cast<FAUSTFLOAT>(0.1);
		fHslider0 = static_cast<FAUSTFLOAT>(1e+01);
		fHslider1 = static_cast<FAUSTFLOAT>(1e+02);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry0 = static_cast<FAUSTFLOAT>(2.0);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider2 = static_cast<FAUSTFLOAT>(2e+02);
		fHslider3 = static_cast<FAUSTFLOAT>(-3e+01);
		fCheckbox4 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(5e+01);
		fHslider5 = static_cast<FAUSTFLOAT>(5e+02);
		fHslider6 = static_cast<FAUSTFLOAT>(5.0);
		fHslider7 = static_cast<FAUSTFLOAT>(-3e+01);
		fHslider8 = static_cast<FAUSTFLOAT>(4e+01);
		fHslider9 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider10 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = l0 + 1) {
			fRec4_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = l1 + 1) {
			fRec6_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = l2 + 1) {
			fRec5_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = l3 + 1) {
			fRec7_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = l4 + 1) {
			fRec8_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = l5 + 1) {
			iRec9_perm[l5] = 0;
		}
		for (int l6 = 0; l6 < 4; l6 = l6 + 1) {
			fRec10_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = l7 + 1) {
			iVec0_perm[l7] = 0;
		}
		for (int l8 = 0; l8 < 4; l8 = l8 + 1) {
			fYec0_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = l9 + 1) {
			fYec1_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = l10 + 1) {
			fYec2_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = l11 + 1) {
			fYec3_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = l12 + 1) {
			fYec4_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = l13 + 1) {
			fYec5_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = l14 + 1) {
			fYec6_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = l15 + 1) {
			fYec7_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = l16 + 1) {
			fYec8_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = l17 + 1) {
			fYec9_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = l18 + 1) {
			fYec10_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = l19 + 1) {
			fYec11_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = l20 + 1) {
			fYec12_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = l21 + 1) {
			fYec13_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = l22 + 1) {
			fYec14_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = l23 + 1) {
			fYec15_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = l24 + 1) {
			fYec16_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = l25 + 1) {
			fYec17_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = l26 + 1) {
			fRec14_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = l27 + 1) {
			iYec18_perm[l27] = 0;
		}
		for (int l28 = 0; l28 < 4; l28 = l28 + 1) {
			iRec15_perm[l28] = 0;
		}
		for (int l29 = 0; l29 < 4; l29 = l29 + 1) {
			fRec12_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = l30 + 1) {
			fRec11_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = l31 + 1) {
			fRec3_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = l32 + 1) {
			iYec19_perm[l32] = 0;
		}
		for (int l33 = 0; l33 < 4; l33 = l33 + 1) {
			iRec16_perm[l33] = 0;
		}
		for (int l34 = 0; l34 < 4; l34 = l34 + 1) {
			fRec1_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = l35 + 1) {
			fRec0_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = l36 + 1) {
			fRec19_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = l37 + 1) {
			fRec18_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = l38 + 1) {
			fRec17_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = l39 + 1) {
			fRec22_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = l40 + 1) {
			fRec21_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = l41 + 1) {
			fRec20_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = l42 + 1) {
			fRec26_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = l43 + 1) {
			fRec25_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = l44 + 1) {
			fRec24_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = l45 + 1) {
			fRec23_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = l46 + 1) {
			fRec33_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = l47 + 1) {
			fRec32_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = l48 + 1) {
			fRec31_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = l49 + 1) {
			fRec30_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = l50 + 1) {
			fRec29_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = l51 + 1) {
			fRec28_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = l52 + 1) {
			fRec27_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = l53 + 1) {
			fRec40_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = l54 + 1) {
			fRec39_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = l55 + 1) {
			fRec38_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = l56 + 1) {
			fRec37_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = l57 + 1) {
			fRec36_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = l58 + 1) {
			fRec35_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = l59 + 1) {
			fRec34_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = l60 + 1) {
			fRec47_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = l61 + 1) {
			fRec46_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = l62 + 1) {
			fRec45_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = l63 + 1) {
			fRec44_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = l64 + 1) {
			fRec43_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = l65 + 1) {
			fRec42_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = l66 + 1) {
			fRec41_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = l67 + 1) {
			fRec54_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = l68 + 1) {
			fRec53_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = l69 + 1) {
			fRec52_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = l70 + 1) {
			fRec51_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = l71 + 1) {
			fRec50_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = l72 + 1) {
			fRec49_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = l73 + 1) {
			fRec48_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = l74 + 1) {
			fRec61_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = l75 + 1) {
			fRec60_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = l76 + 1) {
			fRec59_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = l77 + 1) {
			fRec58_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = l78 + 1) {
			fRec57_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = l79 + 1) {
			fRec56_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = l80 + 1) {
			fRec55_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = l81 + 1) {
			fRec68_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = l82 + 1) {
			fRec67_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = l83 + 1) {
			fRec66_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = l84 + 1) {
			fRec65_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = l85 + 1) {
			fRec64_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = l86 + 1) {
			fRec63_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = l87 + 1) {
			fRec62_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = l88 + 1) {
			fRec75_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = l89 + 1) {
			fRec74_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = l90 + 1) {
			fRec73_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = l91 + 1) {
			fRec72_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = l92 + 1) {
			fRec71_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = l93 + 1) {
			fRec70_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = l94 + 1) {
			fRec69_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = l95 + 1) {
			fRec82_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = l96 + 1) {
			fRec81_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = l97 + 1) {
			fRec80_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = l98 + 1) {
			fRec79_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = l99 + 1) {
			fRec78_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = l100 + 1) {
			fRec77_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = l101 + 1) {
			fRec76_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = l102 + 1) {
			fRec89_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = l103 + 1) {
			fRec88_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = l104 + 1) {
			fRec87_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = l105 + 1) {
			fRec86_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = l106 + 1) {
			fRec85_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = l107 + 1) {
			fRec84_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = l108 + 1) {
			fRec83_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = l109 + 1) {
			fRec96_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = l110 + 1) {
			fRec95_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = l111 + 1) {
			fRec94_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = l112 + 1) {
			fRec93_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = l113 + 1) {
			fRec92_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = l114 + 1) {
			fRec91_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = l115 + 1) {
			fRec90_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = l116 + 1) {
			fRec103_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = l117 + 1) {
			fRec102_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = l118 + 1) {
			fRec101_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = l119 + 1) {
			fRec100_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = l120 + 1) {
			fRec99_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = l121 + 1) {
			fRec98_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = l122 + 1) {
			fRec97_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = l123 + 1) {
			fRec110_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = l124 + 1) {
			fRec109_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = l125 + 1) {
			fRec108_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = l126 + 1) {
			fRec107_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = l127 + 1) {
			fRec106_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = l128 + 1) {
			fRec105_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = l129 + 1) {
			fRec104_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = l130 + 1) {
			fRec117_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = l131 + 1) {
			fRec116_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = l132 + 1) {
			fRec115_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = l133 + 1) {
			fRec114_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = l134 + 1) {
			fRec113_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = l135 + 1) {
			fRec112_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = l136 + 1) {
			fRec111_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = l137 + 1) {
			fRec121_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = l138 + 1) {
			fRec120_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = l139 + 1) {
			fRec119_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = l140 + 1) {
			fRec118_perm[l140] = 0.0;
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
		ui_interface->openVerticalBox("gate_compressor");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("sawtooth");
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
		ui_interface->openVerticalBox("gate");
		ui_interface->declare(0, "tooltip", "Reference: http://en.wikipedia.org/wiki/Noise_gate");
		ui_interface->openVerticalBox("GATE");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the gate has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "1", "");
		ui_interface->declare(&fHbargraph0, "tooltip", "Current gain of the gate in dB");
		ui_interface->declare(&fHbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Gate Gain", &fHbargraph0, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "When the signal level falls below the Threshold (expressed in dB), the signal is muted");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider3, FAUSTFLOAT(-3e+01), FAUSTFLOAT(-1.2e+02), FAUSTFLOAT(0.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate gain to go (exponentially) from 0 (muted) to 1 (unmuted)");
		ui_interface->declare(&fHslider0, "unit", "us");
		ui_interface->addHorizontalSlider("Attack", &fHslider0, FAUSTFLOAT(1e+01), FAUSTFLOAT(1e+01), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Time in ms to keep the gate open (no muting) after the signal level falls below the Threshold");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Hold", &fHslider2, FAUSTFLOAT(2e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go (exponentially) from 1 (unmuted) to 0 (muted)");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider1, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("compressor");
		ui_interface->declare(0, "tooltip", "Reference: http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox4, "0", "");
		ui_interface->declare(&fCheckbox4, "tooltip", "When this is checked, the compressor has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox4);
		ui_interface->declare(&fHbargraph1, "1", "");
		ui_interface->declare(&fHbargraph1, "tooltip", "Current gain of the compressor in dB");
		ui_interface->declare(&fHbargraph1, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fHbargraph1, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fHslider6, "0", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "tooltip", "A compression Ratio of N means that for each N dB increase in input signal level above Threshold, the output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fHslider6, FAUSTFLOAT(5.0), FAUSTFLOAT(1.0), FAUSTFLOAT(2e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed according to the Ratio");
		ui_interface->declare(&fHslider7, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider7, FAUSTFLOAT(-3e+01), FAUSTFLOAT(-1e+02), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "scale", "log");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach (exponentially) a new lower target level (the compression `kicking in')");
		ui_interface->declare(&fHslider4, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack", &fHslider4, FAUSTFLOAT(5e+01), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach (exponentially) a new higher target level (the compression 'releasing')");
		ui_interface->declare(&fHslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider5, FAUSTFLOAT(5e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fHslider8, "5", "");
		ui_interface->declare(&fHslider8, "tooltip", "The compressed-signal output level is increased by this amount (in dB) to make up for the level lost due to compression");
		ui_interface->declare(&fHslider8, "unit", "dB");
		ui_interface->addHorizontalSlider("Makeup Gain", &fHslider8, FAUSTFLOAT(4e+01), FAUSTFLOAT(-96.0), FAUSTFLOAT(96.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("spectral");
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
		ui_interface->declare(&fHslider9, "0", "");
		ui_interface->declare(&fHslider9, "scale", "log");
		ui_interface->declare(&fHslider9, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider9, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider9, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider10, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider10, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fRec4_tmp[36];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow1 = static_cast<double>(fVslider1);
		double fSlow2 = ((fSlow1 > 0.0) ? std::exp(-(fConst1 / fSlow1)) : 0.0);
		double fSlow3 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fVslider2) + -49.0)) * (1.0 - fSlow2);
		double fRec6_tmp[36];
		double* fRec6 = &fRec6_tmp[4];
		double fZec0[32];
		double fZec1[32];
		double fRec5_tmp[36];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow4 = 0.01 * static_cast<double>(fVslider3) + 1.0;
		double fZec2[32];
		double fZec3[32];
		double fRec7_tmp[36];
		double* fRec7 = &fRec7_tmp[4];
		double fSlow5 = 0.01 * static_cast<double>(fVslider4) + 1.0;
		double fZec4[32];
		double fZec5[32];
		double fRec8_tmp[36];
		double* fRec8 = &fRec8_tmp[4];
		int iRec9_tmp[36];
		int* iRec9 = &iRec9_tmp[4];
		double fZec6[32];
		double fRec10_tmp[36];
		double* fRec10 = &fRec10_tmp[4];
		double fSlow6 = std::max<double>(fConst1, 1e-06 * static_cast<double>(fHslider0));
		double fSlow7 = std::max<double>(fConst1, 0.001 * static_cast<double>(fHslider1));
		double fSlow8 = std::min<double>(fSlow6, fSlow7);
		double fSlow9 = ((fSlow8 > 0.0) ? std::exp(-(fConst1 / fSlow8)) : 0.0);
		int iSlow10 = static_cast<int>(static_cast<double>(fCheckbox0));
		int iSlow11 = static_cast<int>(static_cast<double>(fCheckbox1));
		int iSlow12 = static_cast<int>(static_cast<double>(fCheckbox2));
		int iSlow13 = static_cast<int>(static_cast<double>(fEntry0) + -1.0);
		int iSlow14 = iSlow13 >= 2;
		int iVec0_tmp[36];
		int* iVec0 = &iVec0_tmp[4];
		int iSlow15 = iSlow13 >= 1;
		double fZec7[32];
		double fZec8[32];
		double fZec9[32];
		double fYec0_tmp[36];
		double* fYec0 = &fYec0_tmp[4];
		int iSlow16 = iSlow13 >= 3;
		double fZec10[32];
		double fZec11[32];
		double fYec1_tmp[36];
		double* fYec1 = &fYec1_tmp[4];
		double fYec2_tmp[36];
		double* fYec2 = &fYec2_tmp[4];
		double fZec12[32];
		double fYec3_tmp[36];
		double* fYec3 = &fYec3_tmp[4];
		double fYec4_tmp[36];
		double* fYec4 = &fYec4_tmp[4];
		double fYec5_tmp[36];
		double* fYec5 = &fYec5_tmp[4];
		double fZec13[32];
		double fZec14[32];
		double fYec6_tmp[36];
		double* fYec6 = &fYec6_tmp[4];
		double fZec15[32];
		double fYec7_tmp[36];
		double* fYec7 = &fYec7_tmp[4];
		double fYec8_tmp[36];
		double* fYec8 = &fYec8_tmp[4];
		double fYec9_tmp[36];
		double* fYec9 = &fYec9_tmp[4];
		double fYec10_tmp[36];
		double* fYec10 = &fYec10_tmp[4];
		double fYec11_tmp[36];
		double* fYec11 = &fYec11_tmp[4];
		double fZec16[32];
		double fZec17[32];
		double fYec12_tmp[36];
		double* fYec12 = &fYec12_tmp[4];
		double fZec18[32];
		double fYec13_tmp[36];
		double* fYec13 = &fYec13_tmp[4];
		double fYec14_tmp[36];
		double* fYec14 = &fYec14_tmp[4];
		double fYec15_tmp[36];
		double* fYec15 = &fYec15_tmp[4];
		double fYec16_tmp[36];
		double* fYec16 = &fYec16_tmp[4];
		double fYec17_tmp[36];
		double* fYec17 = &fYec17_tmp[4];
		int iSlow17 = static_cast<int>(static_cast<double>(fCheckbox3));
		double fZec19[32];
		double fZec20[32];
		double fZec21[32];
		double fSlow18 = 1.0 - fSlow9;
		double fRec14_tmp[36];
		double* fRec14 = &fRec14_tmp[4];
		double fRec13[32];
		int iSlow19 = static_cast<int>(fConst0 * std::max<double>(fConst1, 0.001 * static_cast<double>(fHslider2)));
		double fSlow20 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider3));
		int iYec18_tmp[36];
		int* iYec18 = &iYec18_tmp[4];
		int iRec15_tmp[36];
		int* iRec15 = &iRec15_tmp[4];
		double fZec22[32];
		double fSlow21 = ((fSlow6 > 0.0) ? std::exp(-(fConst1 / fSlow6)) : 0.0);
		double fSlow22 = ((fSlow7 > 0.0) ? std::exp(-(fConst1 / fSlow7)) : 0.0);
		double fZec23[32];
		double fRec12_tmp[36];
		double* fRec12 = &fRec12_tmp[4];
		double fRec11_tmp[36];
		double* fRec11 = &fRec11_tmp[4];
		double fZec24[32];
		double fRec3_tmp[36];
		double* fRec3 = &fRec3_tmp[4];
		double fRec2[32];
		int iYec19_tmp[36];
		int* iYec19 = &iYec19_tmp[4];
		int iRec16_tmp[36];
		int* iRec16 = &iRec16_tmp[4];
		double fZec25[32];
		double fZec26[32];
		double fRec1_tmp[36];
		double* fRec1 = &fRec1_tmp[4];
		double fRec0_tmp[36];
		double* fRec0 = &fRec0_tmp[4];
		int iSlow23 = static_cast<int>(static_cast<double>(fCheckbox4));
		double fZec27[32];
		double fZec28[32];
		double fZec29[32];
		double fZec30[32];
		double fZec31[32];
		double fSlow24 = std::max<double>(fConst1, 0.001 * static_cast<double>(fHslider4));
		double fSlow25 = ((fSlow24 > 0.0) ? std::exp(-(fConst1 / fSlow24)) : 0.0);
		double fSlow26 = std::max<double>(fConst1, 0.001 * static_cast<double>(fHslider5));
		double fSlow27 = ((fSlow26 > 0.0) ? std::exp(-(fConst1 / fSlow26)) : 0.0);
		double fZec32[32];
		double fRec19_tmp[36];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[36];
		double* fRec18 = &fRec18_tmp[4];
		double fSlow28 = (((0.5 * fSlow24) > 0.0) ? std::exp(-(fConst5 / fSlow24)) : 0.0);
		double fSlow29 = 1.0 / static_cast<double>(fHslider6) + -1.0;
		double fSlow30 = static_cast<double>(fHslider7);
		double fSlow31 = 1.0 - fSlow28;
		double fRec17_tmp[36];
		double* fRec17 = &fRec17_tmp[4];
		double fZec33[32];
		double fZec34[32];
		double fZec35[32];
		double fZec36[32];
		double fZec37[32];
		double fRec22_tmp[36];
		double* fRec22 = &fRec22_tmp[4];
		double fRec21_tmp[36];
		double* fRec21 = &fRec21_tmp[4];
		double fRec20_tmp[36];
		double* fRec20 = &fRec20_tmp[4];
		double fSlow32 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider8));
		double fZec38[32];
		double fRec26_tmp[36];
		double* fRec26 = &fRec26_tmp[4];
		double fRec25_tmp[36];
		double* fRec25 = &fRec25_tmp[4];
		double fRec24_tmp[36];
		double* fRec24 = &fRec24_tmp[4];
		double fSlow33 = static_cast<double>(fHslider9);
		double fSlow34 = (((0.001 * fSlow33) > 0.0) ? std::exp(-(fConst25 / fSlow33)) : 0.0);
		double fSlow35 = 1.0 - fSlow34;
		double fRec23_tmp[36];
		double* fRec23 = &fRec23_tmp[4];
		double fRec33_tmp[36];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[36];
		double* fRec32 = &fRec32_tmp[4];
		double fRec31_tmp[36];
		double* fRec31 = &fRec31_tmp[4];
		double fZec39[32];
		double fRec30_tmp[36];
		double* fRec30 = &fRec30_tmp[4];
		double fRec29_tmp[36];
		double* fRec29 = &fRec29_tmp[4];
		double fRec28_tmp[36];
		double* fRec28 = &fRec28_tmp[4];
		double fRec27_tmp[36];
		double* fRec27 = &fRec27_tmp[4];
		double fRec40_tmp[36];
		double* fRec40 = &fRec40_tmp[4];
		double fRec39_tmp[36];
		double* fRec39 = &fRec39_tmp[4];
		double fRec38_tmp[36];
		double* fRec38 = &fRec38_tmp[4];
		double fZec40[32];
		double fRec37_tmp[36];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[36];
		double* fRec36 = &fRec36_tmp[4];
		double fRec35_tmp[36];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[36];
		double* fRec34 = &fRec34_tmp[4];
		double fRec47_tmp[36];
		double* fRec47 = &fRec47_tmp[4];
		double fRec46_tmp[36];
		double* fRec46 = &fRec46_tmp[4];
		double fRec45_tmp[36];
		double* fRec45 = &fRec45_tmp[4];
		double fZec41[32];
		double fRec44_tmp[36];
		double* fRec44 = &fRec44_tmp[4];
		double fRec43_tmp[36];
		double* fRec43 = &fRec43_tmp[4];
		double fRec42_tmp[36];
		double* fRec42 = &fRec42_tmp[4];
		double fRec41_tmp[36];
		double* fRec41 = &fRec41_tmp[4];
		double fRec54_tmp[36];
		double* fRec54 = &fRec54_tmp[4];
		double fRec53_tmp[36];
		double* fRec53 = &fRec53_tmp[4];
		double fRec52_tmp[36];
		double* fRec52 = &fRec52_tmp[4];
		double fZec42[32];
		double fRec51_tmp[36];
		double* fRec51 = &fRec51_tmp[4];
		double fRec50_tmp[36];
		double* fRec50 = &fRec50_tmp[4];
		double fRec49_tmp[36];
		double* fRec49 = &fRec49_tmp[4];
		double fRec48_tmp[36];
		double* fRec48 = &fRec48_tmp[4];
		double fRec61_tmp[36];
		double* fRec61 = &fRec61_tmp[4];
		double fRec60_tmp[36];
		double* fRec60 = &fRec60_tmp[4];
		double fRec59_tmp[36];
		double* fRec59 = &fRec59_tmp[4];
		double fZec43[32];
		double fRec58_tmp[36];
		double* fRec58 = &fRec58_tmp[4];
		double fRec57_tmp[36];
		double* fRec57 = &fRec57_tmp[4];
		double fRec56_tmp[36];
		double* fRec56 = &fRec56_tmp[4];
		double fRec55_tmp[36];
		double* fRec55 = &fRec55_tmp[4];
		double fRec68_tmp[36];
		double* fRec68 = &fRec68_tmp[4];
		double fRec67_tmp[36];
		double* fRec67 = &fRec67_tmp[4];
		double fRec66_tmp[36];
		double* fRec66 = &fRec66_tmp[4];
		double fZec44[32];
		double fRec65_tmp[36];
		double* fRec65 = &fRec65_tmp[4];
		double fRec64_tmp[36];
		double* fRec64 = &fRec64_tmp[4];
		double fRec63_tmp[36];
		double* fRec63 = &fRec63_tmp[4];
		double fRec62_tmp[36];
		double* fRec62 = &fRec62_tmp[4];
		double fRec75_tmp[36];
		double* fRec75 = &fRec75_tmp[4];
		double fRec74_tmp[36];
		double* fRec74 = &fRec74_tmp[4];
		double fRec73_tmp[36];
		double* fRec73 = &fRec73_tmp[4];
		double fZec45[32];
		double fRec72_tmp[36];
		double* fRec72 = &fRec72_tmp[4];
		double fRec71_tmp[36];
		double* fRec71 = &fRec71_tmp[4];
		double fRec70_tmp[36];
		double* fRec70 = &fRec70_tmp[4];
		double fRec69_tmp[36];
		double* fRec69 = &fRec69_tmp[4];
		double fRec82_tmp[36];
		double* fRec82 = &fRec82_tmp[4];
		double fRec81_tmp[36];
		double* fRec81 = &fRec81_tmp[4];
		double fRec80_tmp[36];
		double* fRec80 = &fRec80_tmp[4];
		double fZec46[32];
		double fRec79_tmp[36];
		double* fRec79 = &fRec79_tmp[4];
		double fRec78_tmp[36];
		double* fRec78 = &fRec78_tmp[4];
		double fRec77_tmp[36];
		double* fRec77 = &fRec77_tmp[4];
		double fRec76_tmp[36];
		double* fRec76 = &fRec76_tmp[4];
		double fRec89_tmp[36];
		double* fRec89 = &fRec89_tmp[4];
		double fRec88_tmp[36];
		double* fRec88 = &fRec88_tmp[4];
		double fRec87_tmp[36];
		double* fRec87 = &fRec87_tmp[4];
		double fZec47[32];
		double fRec86_tmp[36];
		double* fRec86 = &fRec86_tmp[4];
		double fRec85_tmp[36];
		double* fRec85 = &fRec85_tmp[4];
		double fRec84_tmp[36];
		double* fRec84 = &fRec84_tmp[4];
		double fRec83_tmp[36];
		double* fRec83 = &fRec83_tmp[4];
		double fRec96_tmp[36];
		double* fRec96 = &fRec96_tmp[4];
		double fRec95_tmp[36];
		double* fRec95 = &fRec95_tmp[4];
		double fRec94_tmp[36];
		double* fRec94 = &fRec94_tmp[4];
		double fZec48[32];
		double fRec93_tmp[36];
		double* fRec93 = &fRec93_tmp[4];
		double fRec92_tmp[36];
		double* fRec92 = &fRec92_tmp[4];
		double fRec91_tmp[36];
		double* fRec91 = &fRec91_tmp[4];
		double fRec90_tmp[36];
		double* fRec90 = &fRec90_tmp[4];
		double fRec103_tmp[36];
		double* fRec103 = &fRec103_tmp[4];
		double fRec102_tmp[36];
		double* fRec102 = &fRec102_tmp[4];
		double fRec101_tmp[36];
		double* fRec101 = &fRec101_tmp[4];
		double fZec49[32];
		double fRec100_tmp[36];
		double* fRec100 = &fRec100_tmp[4];
		double fRec99_tmp[36];
		double* fRec99 = &fRec99_tmp[4];
		double fRec98_tmp[36];
		double* fRec98 = &fRec98_tmp[4];
		double fRec97_tmp[36];
		double* fRec97 = &fRec97_tmp[4];
		double fRec110_tmp[36];
		double* fRec110 = &fRec110_tmp[4];
		double fRec109_tmp[36];
		double* fRec109 = &fRec109_tmp[4];
		double fRec108_tmp[36];
		double* fRec108 = &fRec108_tmp[4];
		double fZec50[32];
		double fRec107_tmp[36];
		double* fRec107 = &fRec107_tmp[4];
		double fRec106_tmp[36];
		double* fRec106 = &fRec106_tmp[4];
		double fRec105_tmp[36];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[36];
		double* fRec104 = &fRec104_tmp[4];
		double fRec117_tmp[36];
		double* fRec117 = &fRec117_tmp[4];
		double fRec116_tmp[36];
		double* fRec116 = &fRec116_tmp[4];
		double fRec115_tmp[36];
		double* fRec115 = &fRec115_tmp[4];
		double fZec51[32];
		double fRec114_tmp[36];
		double* fRec114 = &fRec114_tmp[4];
		double fRec113_tmp[36];
		double* fRec113 = &fRec113_tmp[4];
		double fRec112_tmp[36];
		double* fRec112 = &fRec112_tmp[4];
		double fRec111_tmp[36];
		double* fRec111 = &fRec111_tmp[4];
		double fRec121_tmp[36];
		double* fRec121 = &fRec121_tmp[4];
		double fRec120_tmp[36];
		double* fRec120 = &fRec120_tmp[4];
		double fRec119_tmp[36];
		double* fRec119 = &fRec119_tmp[4];
		double fRec118_tmp[36];
		double* fRec118 = &fRec118_tmp[4];
		double fSlow36 = static_cast<double>(fHslider10);
		double fZec52[32];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec6_tmp[j2] = fRec6_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec6[i] = fRec6[i - 1] * fSlow2 + fSlow3;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec6_perm[j3] = fRec6_tmp[vsize + j3];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec6[i]));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec6[i]));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec6[i]));
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				fRec5_tmp[j4] = fRec5_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fRec5[i - 1] + fConst1 * fZec0[i];
				fRec5[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				fRec5_perm[j5] = fRec5_tmp[vsize + j5];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fRec7_tmp[j6] = fRec7_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = fRec7[i - 1] + fConst1 * fZec2[i];
				fRec7[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fRec7_perm[j7] = fRec7_tmp[vsize + j7];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fRec8_tmp[j8] = fRec8_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = fRec8[i - 1] + fConst1 * fZec4[i];
				fRec8[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fRec8_perm[j9] = fRec8_tmp[vsize + j9];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = 2.0 * fRec5[i];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec13[i] = 2.0 * fRec7[i];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec16[i] = 2.0 * fRec8[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = fZec7[i] + -1.0;
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec14[i] = fZec13[i] + -1.0;
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec17[i] = fZec16[i] + -1.0;
			}
			/* Vectorizable loop 13 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fYec0_tmp[j16] = fYec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[i] = mydsp_faustpower2_f(fZec8[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fYec0_perm[j17] = fYec0_tmp[vsize + j17];
			}
			/* Vectorizable loop 14 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
				fYec6_tmp[j28] = fYec6_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec6[i] = mydsp_faustpower2_f(fZec14[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
				fYec6_perm[j29] = fYec6_tmp[vsize + j29];
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
				fYec12_tmp[j40] = fYec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec12[i] = mydsp_faustpower2_f(fZec17[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
				fYec12_perm[j41] = fYec12_tmp[vsize + j41];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				iRec9_tmp[j10] = iRec9_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iRec9[i] = 1103515245 * iRec9[i - 1] + 12345;
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				iRec9_perm[j11] = iRec9_tmp[vsize + j11];
			}
			/* Vectorizable loop 17 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				iVec0_tmp[j14] = iVec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				iVec0_perm[j15] = iVec0_tmp[vsize + j15];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec11[i] = mydsp_faustpower3_f(fZec8[i]);
			}
			/* Vectorizable loop 19 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
				fYec3_tmp[j22] = fYec3_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
				fYec3_perm[j23] = fYec3_tmp[vsize + j23];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec15[i] = mydsp_faustpower3_f(fZec14[i]);
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
				fYec9_tmp[j34] = fYec9_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
				fYec9_perm[j35] = fYec9_tmp[vsize + j35];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec18[i] = mydsp_faustpower3_f(fZec17[i]);
			}
			/* Vectorizable loop 23 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
				fYec15_tmp[j46] = fYec15_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
				fYec15_perm[j47] = fYec15_tmp[vsize + j47];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec9[i]);
			}
			/* Vectorizable loop 25 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fYec1_tmp[j18] = fYec1_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[i] = fZec11[i] + (1.0 - fZec7[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fYec1_perm[j19] = fYec1_tmp[vsize + j19];
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
				fYec4_tmp[j24] = fYec4_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec4[i] = (fYec3[i] - fYec3[i - 1]) / fZec0[i];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
				fYec4_perm[j25] = fYec4_tmp[vsize + j25];
			}
			/* Vectorizable loop 27 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
				fYec7_tmp[j30] = fYec7_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec7[i] = fZec15[i] + (1.0 - fZec13[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
				fYec7_perm[j31] = fYec7_tmp[vsize + j31];
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
				fYec10_tmp[j36] = fYec10_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec10[i] = (fYec9[i] - fYec9[i - 1]) / fZec2[i];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
				fYec10_perm[j37] = fYec10_tmp[vsize + j37];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
				fYec13_tmp[j42] = fYec13_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec13[i] = fZec18[i] + (1.0 - fZec16[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
				fYec13_perm[j43] = fYec13_tmp[vsize + j43];
			}
			/* Vectorizable loop 30 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
				fYec16_tmp[j48] = fYec16_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec16[i] = (fYec15[i] - fYec15[i - 1]) / fZec4[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
				fYec16_perm[j49] = fYec16_tmp[vsize + j49];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fRec4_tmp[j0] = fRec4_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec4[i] = fSlow0 + 0.999 * fRec4[i - 1];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fRec4_perm[j1] = fRec4_tmp[vsize + j1];
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fRec10_tmp[j12] = fRec10_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec10[i] = 0.5221894 * fRec10[i - 3] + fZec6[i] + 2.494956002 * fRec10[i - 1] - 2.017265875 * fRec10[i - 2];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fRec10_perm[j13] = fRec10_tmp[vsize + j13];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = static_cast<double>(iVec0[i - 1]);
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec10[i] = static_cast<double>(iVec0[i - 2]);
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
				fYec2_tmp[j20] = fYec2_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[i] = (fZec11[i] + (1.0 - (fZec7[i] + fYec1[i - 1]))) / fZec0[i];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
				fYec2_perm[j21] = fYec2_tmp[vsize + j21];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec12[i] = static_cast<double>(iVec0[i - 3]);
			}
			/* Vectorizable loop 37 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
				fYec5_tmp[j26] = fYec5_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec5[i] = (fYec4[i] - fYec4[i - 1]) / fZec0[i];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
				fYec5_perm[j27] = fYec5_tmp[vsize + j27];
			}
			/* Vectorizable loop 38 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
				fYec8_tmp[j32] = fYec8_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec8[i] = (fZec15[i] + (1.0 - (fZec13[i] + fYec7[i - 1]))) / fZec2[i];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
				fYec8_perm[j33] = fYec8_tmp[vsize + j33];
			}
			/* Vectorizable loop 39 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
				fYec11_tmp[j38] = fYec11_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec11[i] = (fYec10[i] - fYec10[i - 1]) / fZec2[i];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
				fYec11_perm[j39] = fYec11_tmp[vsize + j39];
			}
			/* Vectorizable loop 40 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
				fYec14_tmp[j44] = fYec14_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec14[i] = (fZec18[i] + (1.0 - (fZec16[i] + fYec13[i - 1]))) / fZec4[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
				fYec14_perm[j45] = fYec14_tmp[vsize + j45];
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
				fYec17_tmp[j50] = fYec17_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec17[i] = (fYec16[i] - fYec16[i - 1]) / fZec4[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
				fYec17_perm[j51] = fYec17_tmp[vsize + j51];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec19[i] = fRec4[i] * ((iSlow11) ? static_cast<double>(input0[i]) : ((iSlow12) ? ((iSlow17) ? 0.049922035 * fRec10[i] + 0.050612699 * fRec10[i - 2] - (0.095993537 * fRec10[i - 1] + 0.004408786 * fRec10[i - 3]) : fZec6[i]) : 0.3333333333333333 * fRec4[i] * (((iSlow14) ? ((iSlow16) ? fConst4 * (fZec12[i] * (fYec5[i] - fYec5[i - 1]) / fZec0[i]) : fConst3 * (fZec10[i] * (fYec2[i] - fYec2[i - 1]) / fZec0[i])) : ((iSlow15) ? fConst2 * (fZec9[i] * (fYec0[i] - fYec0[i - 1]) / fZec0[i]) : fZec8[i])) + ((iSlow14) ? ((iSlow16) ? fConst4 * (fZec12[i] * (fYec11[i] - fYec11[i - 1]) / fZec2[i]) : fConst3 * (fZec10[i] * (fYec8[i] - fYec8[i - 1]) / fZec2[i])) : ((iSlow15) ? fConst2 * (fZec9[i] * (fYec6[i] - fYec6[i - 1]) / fZec2[i]) : fZec14[i])) + ((iSlow14) ? ((iSlow16) ? fConst4 * (fZec12[i] * (fYec17[i] - fYec17[i - 1]) / fZec4[i]) : fConst3 * (fZec10[i] * (fYec14[i] - fYec14[i - 1]) / fZec4[i])) : ((iSlow15) ? fConst2 * (fZec9[i] * (fYec12[i] - fYec12[i - 1]) / fZec4[i]) : fZec17[i])))));
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec20[i] = ((iSlow10) ? 0.0 : fZec19[i]);
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec21[i] = std::fabs(fZec20[i]);
			}
			/* Recursive loop 45 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
				fRec14_tmp[j52] = fRec14_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec14[i] = fRec14[i - 1] * fSlow9 + std::fabs(2.0 * fZec21[i]) * fSlow18;
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
				fRec14_perm[j53] = fRec14_tmp[vsize + j53];
			}
			/* Recursive loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec13[i] = fRec14[i];
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
				iYec18_tmp[j54] = iYec18_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iYec18[i] = fRec13[i] > fSlow20;
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
				iYec18_perm[j55] = iYec18_tmp[vsize + j55];
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
				iRec15_tmp[j56] = iRec15_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iRec15[i] = std::max<int>(iSlow19 * (iYec18[i] < iYec18[i - 1]), iRec15[i - 1] + -1);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
				iRec15_perm[j57] = iRec15_tmp[vsize + j57];
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec22[i] = std::fabs(std::max<double>(static_cast<double>(iYec18[i]), static_cast<double>(iRec15[i] > 0)));
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
				fRec12_tmp[j58] = fRec12_perm[j58];
			}
			for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
				fRec11_tmp[j60] = fRec11_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec23[i] = ((fRec11[i - 1] > fZec22[i]) ? fSlow22 : fSlow21);
				fRec12[i] = fRec12[i - 1] * fZec23[i] + fZec22[i] * (1.0 - fZec23[i]);
				fRec11[i] = fRec12[i];
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
				fRec12_perm[j59] = fRec12_tmp[vsize + j59];
			}
			for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
				fRec11_perm[j61] = fRec11_tmp[vsize + j61];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fHbargraph0 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(fRec11[i]));
				fZec24[i] = fZec20[i];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
				fRec3_tmp[j62] = fRec3_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec3[i] = fRec3[i - 1] * fSlow9 + fSlow18 * std::fabs(fZec21[i] + std::fabs(fZec24[i]));
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
				fRec3_perm[j63] = fRec3_tmp[vsize + j63];
			}
			/* Recursive loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec2[i] = fRec3[i];
			}
			/* Vectorizable loop 54 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
				iYec19_tmp[j64] = iYec19_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iYec19[i] = fRec2[i] > fSlow20;
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
				iYec19_perm[j65] = iYec19_tmp[vsize + j65];
			}
			/* Recursive loop 55 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
				iRec16_tmp[j66] = iRec16_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iRec16[i] = std::max<int>(iSlow19 * (iYec19[i] < iYec19[i - 1]), iRec16[i - 1] + -1);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
				iRec16_perm[j67] = iRec16_tmp[vsize + j67];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec25[i] = std::fabs(std::max<double>(static_cast<double>(iYec19[i]), static_cast<double>(iRec16[i] > 0)));
			}
			/* Recursive loop 57 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
				fRec1_tmp[j68] = fRec1_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
				fRec0_tmp[j70] = fRec0_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec26[i] = ((fRec0[i - 1] > fZec25[i]) ? fSlow22 : fSlow21);
				fRec1[i] = fRec1[i - 1] * fZec26[i] + fZec25[i] * (1.0 - fZec26[i]);
				fRec0[i] = fRec1[i];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
				fRec1_perm[j69] = fRec1_tmp[vsize + j69];
			}
			for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
				fRec0_perm[j71] = fRec0_tmp[vsize + j71];
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec27[i] = ((iSlow10) ? fZec19[i] : fRec0[i] * fZec24[i]);
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec29[i] = ((iSlow10) ? fZec19[i] : fRec0[i] * fZec20[i]);
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec28[i] = ((iSlow23) ? 0.0 : fZec27[i]);
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec30[i] = ((iSlow23) ? 0.0 : fZec29[i]);
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec31[i] = std::fabs(std::fabs(fZec28[i]) + std::fabs(fZec30[i]));
			}
			/* Recursive loop 63 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
				fRec19_tmp[j72] = fRec19_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
				fRec18_tmp[j74] = fRec18_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec32[i] = ((fRec18[i - 1] > fZec31[i]) ? fSlow27 : fSlow25);
				fRec19[i] = fRec19[i - 1] * fZec32[i] + fZec31[i] * (1.0 - fZec32[i]);
				fRec18[i] = fRec19[i];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
				fRec19_perm[j73] = fRec19_tmp[vsize + j73];
			}
			for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
				fRec18_perm[j75] = fRec18_tmp[vsize + j75];
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
				fRec17_tmp[j76] = fRec17_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec17[i] = fRec17[i - 1] * fSlow28 + fSlow29 * std::max<double>(2e+01 * std::log10(fRec18[i]) - fSlow30, 0.0) * fSlow31;
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
				fRec17_perm[j77] = fRec17_tmp[vsize + j77];
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec33[i] = std::pow(1e+01, 0.05 * fRec17[i]);
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec34[i] = fZec28[i] * fZec33[i];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec35[i] = fZec30[i] * fZec33[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec36[i] = std::fabs(std::fabs(fZec34[i]) + std::fabs(fZec35[i]));
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
				fRec22_tmp[j78] = fRec22_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = j80 + 1) {
				fRec21_tmp[j80] = fRec21_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec37[i] = ((fRec21[i - 1] > fZec36[i]) ? fSlow27 : fSlow25);
				fRec22[i] = fRec22[i - 1] * fZec37[i] + fZec36[i] * (1.0 - fZec37[i]);
				fRec21[i] = fRec22[i];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
				fRec22_perm[j79] = fRec22_tmp[vsize + j79];
			}
			for (int j81 = 0; j81 < 4; j81 = j81 + 1) {
				fRec21_perm[j81] = fRec21_tmp[vsize + j81];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = j82 + 1) {
				fRec20_tmp[j82] = fRec20_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec20[i] = fSlow28 * fRec20[i - 1] + fSlow29 * std::max<double>(2e+01 * std::log10(fRec21[i]) - fSlow30, 0.0) * fSlow31;
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = j83 + 1) {
				fRec20_perm[j83] = fRec20_tmp[vsize + j83];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fHbargraph1 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::pow(1e+01, 0.05 * fRec20[i])));
				fZec38[i] = ((iSlow23) ? fZec27[i] : fSlow32 * fZec34[i]) + ((iSlow23) ? fZec29[i] : fSlow32 * fZec35[i]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = j92 + 1) {
				fRec33_tmp[j92] = fRec33_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec33[i] = fZec38[i] - fConst29 * (fConst30 * fRec33[i - 2] + fConst31 * fRec33[i - 1]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = j93 + 1) {
				fRec33_perm[j93] = fRec33_tmp[vsize + j93];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = j94 + 1) {
				fRec32_tmp[j94] = fRec32_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec32[i] = fConst29 * (fConst33 * fRec33[i] + fConst34 * fRec33[i - 1] + fConst33 * fRec33[i - 2]) - fConst35 * (fConst36 * fRec32[i - 2] + fConst37 * fRec32[i - 1]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = j95 + 1) {
				fRec32_perm[j95] = fRec32_tmp[vsize + j95];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = j96 + 1) {
				fRec31_tmp[j96] = fRec31_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec31[i] = fConst35 * (fConst38 * fRec32[i] + fConst39 * fRec32[i - 1] + fConst38 * fRec32[i - 2]) - fConst40 * (fConst41 * fRec31[i - 2] + fConst42 * fRec31[i - 1]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = j97 + 1) {
				fRec31_perm[j97] = fRec31_tmp[vsize + j97];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec39[i] = fConst40 * (fConst43 * fRec31[i] + fConst44 * fRec31[i - 1] + fConst43 * fRec31[i - 2]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = j106 + 1) {
				fRec40_tmp[j106] = fRec40_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec40[i] = fZec39[i] - fConst67 * (fConst68 * fRec40[i - 2] + fConst69 * fRec40[i - 1]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = j107 + 1) {
				fRec40_perm[j107] = fRec40_tmp[vsize + j107];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = j108 + 1) {
				fRec39_tmp[j108] = fRec39_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec39[i] = fConst67 * (fConst71 * fRec40[i] + fConst72 * fRec40[i - 1] + fConst71 * fRec40[i - 2]) - fConst73 * (fConst74 * fRec39[i - 2] + fConst75 * fRec39[i - 1]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = j109 + 1) {
				fRec39_perm[j109] = fRec39_tmp[vsize + j109];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = j110 + 1) {
				fRec38_tmp[j110] = fRec38_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec38[i] = fConst73 * (fConst76 * fRec39[i] + fConst77 * fRec39[i - 1] + fConst76 * fRec39[i - 2]) - fConst78 * (fConst79 * fRec38[i - 2] + fConst80 * fRec38[i - 1]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = j111 + 1) {
				fRec38_perm[j111] = fRec38_tmp[vsize + j111];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec40[i] = fConst78 * (fConst81 * fRec38[i] + fConst82 * fRec38[i - 1] + fConst81 * fRec38[i - 2]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = j120 + 1) {
				fRec47_tmp[j120] = fRec47_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec47[i] = fZec40[i] - fConst105 * (fConst106 * fRec47[i - 2] + fConst107 * fRec47[i - 1]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = j121 + 1) {
				fRec47_perm[j121] = fRec47_tmp[vsize + j121];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = j122 + 1) {
				fRec46_tmp[j122] = fRec46_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec46[i] = fConst105 * (fConst109 * fRec47[i] + fConst110 * fRec47[i - 1] + fConst109 * fRec47[i - 2]) - fConst111 * (fConst112 * fRec46[i - 2] + fConst113 * fRec46[i - 1]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = j123 + 1) {
				fRec46_perm[j123] = fRec46_tmp[vsize + j123];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = j124 + 1) {
				fRec45_tmp[j124] = fRec45_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec45[i] = fConst111 * (fConst114 * fRec46[i] + fConst115 * fRec46[i - 1] + fConst114 * fRec46[i - 2]) - fConst116 * (fConst117 * fRec45[i - 2] + fConst118 * fRec45[i - 1]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = j125 + 1) {
				fRec45_perm[j125] = fRec45_tmp[vsize + j125];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec41[i] = fConst116 * (fConst119 * fRec45[i] + fConst120 * fRec45[i - 1] + fConst119 * fRec45[i - 2]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = j134 + 1) {
				fRec54_tmp[j134] = fRec54_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec54[i] = fZec41[i] - fConst143 * (fConst144 * fRec54[i - 2] + fConst145 * fRec54[i - 1]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = j135 + 1) {
				fRec54_perm[j135] = fRec54_tmp[vsize + j135];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = j136 + 1) {
				fRec53_tmp[j136] = fRec53_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec53[i] = fConst143 * (fConst147 * fRec54[i] + fConst148 * fRec54[i - 1] + fConst147 * fRec54[i - 2]) - fConst149 * (fConst150 * fRec53[i - 2] + fConst151 * fRec53[i - 1]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = j137 + 1) {
				fRec53_perm[j137] = fRec53_tmp[vsize + j137];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = j138 + 1) {
				fRec52_tmp[j138] = fRec52_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec52[i] = fConst149 * (fConst152 * fRec53[i] + fConst153 * fRec53[i - 1] + fConst152 * fRec53[i - 2]) - fConst154 * (fConst155 * fRec52[i - 2] + fConst156 * fRec52[i - 1]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = j139 + 1) {
				fRec52_perm[j139] = fRec52_tmp[vsize + j139];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec42[i] = fConst154 * (fConst157 * fRec52[i] + fConst158 * fRec52[i - 1] + fConst157 * fRec52[i - 2]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = j148 + 1) {
				fRec61_tmp[j148] = fRec61_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec61[i] = fZec42[i] - fConst181 * (fConst182 * fRec61[i - 2] + fConst183 * fRec61[i - 1]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = j149 + 1) {
				fRec61_perm[j149] = fRec61_tmp[vsize + j149];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = j150 + 1) {
				fRec60_tmp[j150] = fRec60_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec60[i] = fConst181 * (fConst185 * fRec61[i] + fConst186 * fRec61[i - 1] + fConst185 * fRec61[i - 2]) - fConst187 * (fConst188 * fRec60[i - 2] + fConst189 * fRec60[i - 1]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = j151 + 1) {
				fRec60_perm[j151] = fRec60_tmp[vsize + j151];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = j152 + 1) {
				fRec59_tmp[j152] = fRec59_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec59[i] = fConst187 * (fConst190 * fRec60[i] + fConst191 * fRec60[i - 1] + fConst190 * fRec60[i - 2]) - fConst192 * (fConst193 * fRec59[i - 2] + fConst194 * fRec59[i - 1]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = j153 + 1) {
				fRec59_perm[j153] = fRec59_tmp[vsize + j153];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec43[i] = fConst192 * (fConst195 * fRec59[i] + fConst196 * fRec59[i - 1] + fConst195 * fRec59[i - 2]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = j162 + 1) {
				fRec68_tmp[j162] = fRec68_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec68[i] = fZec43[i] - fConst219 * (fConst220 * fRec68[i - 2] + fConst221 * fRec68[i - 1]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = j163 + 1) {
				fRec68_perm[j163] = fRec68_tmp[vsize + j163];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = j164 + 1) {
				fRec67_tmp[j164] = fRec67_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec67[i] = fConst219 * (fConst223 * fRec68[i] + fConst224 * fRec68[i - 1] + fConst223 * fRec68[i - 2]) - fConst225 * (fConst226 * fRec67[i - 2] + fConst227 * fRec67[i - 1]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = j165 + 1) {
				fRec67_perm[j165] = fRec67_tmp[vsize + j165];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = j166 + 1) {
				fRec66_tmp[j166] = fRec66_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec66[i] = fConst225 * (fConst228 * fRec67[i] + fConst229 * fRec67[i - 1] + fConst228 * fRec67[i - 2]) - fConst230 * (fConst231 * fRec66[i - 2] + fConst232 * fRec66[i - 1]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = j167 + 1) {
				fRec66_perm[j167] = fRec66_tmp[vsize + j167];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec44[i] = fConst230 * (fConst233 * fRec66[i] + fConst234 * fRec66[i - 1] + fConst233 * fRec66[i - 2]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = j176 + 1) {
				fRec75_tmp[j176] = fRec75_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec75[i] = fZec44[i] - fConst257 * (fConst258 * fRec75[i - 2] + fConst259 * fRec75[i - 1]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = j177 + 1) {
				fRec75_perm[j177] = fRec75_tmp[vsize + j177];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = j178 + 1) {
				fRec74_tmp[j178] = fRec74_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec74[i] = fConst257 * (fConst261 * fRec75[i] + fConst262 * fRec75[i - 1] + fConst261 * fRec75[i - 2]) - fConst263 * (fConst264 * fRec74[i - 2] + fConst265 * fRec74[i - 1]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = j179 + 1) {
				fRec74_perm[j179] = fRec74_tmp[vsize + j179];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = j180 + 1) {
				fRec73_tmp[j180] = fRec73_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec73[i] = fConst263 * (fConst266 * fRec74[i] + fConst267 * fRec74[i - 1] + fConst266 * fRec74[i - 2]) - fConst268 * (fConst269 * fRec73[i - 2] + fConst270 * fRec73[i - 1]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = j181 + 1) {
				fRec73_perm[j181] = fRec73_tmp[vsize + j181];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec45[i] = fConst268 * (fConst271 * fRec73[i] + fConst272 * fRec73[i - 1] + fConst271 * fRec73[i - 2]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = j190 + 1) {
				fRec82_tmp[j190] = fRec82_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec82[i] = fZec45[i] - fConst295 * (fConst296 * fRec82[i - 2] + fConst297 * fRec82[i - 1]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = j191 + 1) {
				fRec82_perm[j191] = fRec82_tmp[vsize + j191];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = j192 + 1) {
				fRec81_tmp[j192] = fRec81_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec81[i] = fConst295 * (fConst299 * fRec82[i] + fConst300 * fRec82[i - 1] + fConst299 * fRec82[i - 2]) - fConst301 * (fConst302 * fRec81[i - 2] + fConst303 * fRec81[i - 1]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = j193 + 1) {
				fRec81_perm[j193] = fRec81_tmp[vsize + j193];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = j194 + 1) {
				fRec80_tmp[j194] = fRec80_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec80[i] = fConst301 * (fConst304 * fRec81[i] + fConst305 * fRec81[i - 1] + fConst304 * fRec81[i - 2]) - fConst306 * (fConst307 * fRec80[i - 2] + fConst308 * fRec80[i - 1]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = j195 + 1) {
				fRec80_perm[j195] = fRec80_tmp[vsize + j195];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec46[i] = fConst306 * (fConst309 * fRec80[i] + fConst310 * fRec80[i - 1] + fConst309 * fRec80[i - 2]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = j204 + 1) {
				fRec89_tmp[j204] = fRec89_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec89[i] = fZec46[i] - fConst333 * (fConst334 * fRec89[i - 2] + fConst335 * fRec89[i - 1]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = j205 + 1) {
				fRec89_perm[j205] = fRec89_tmp[vsize + j205];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = j206 + 1) {
				fRec88_tmp[j206] = fRec88_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec88[i] = fConst333 * (fConst337 * fRec89[i] + fConst338 * fRec89[i - 1] + fConst337 * fRec89[i - 2]) - fConst339 * (fConst340 * fRec88[i - 2] + fConst341 * fRec88[i - 1]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = j207 + 1) {
				fRec88_perm[j207] = fRec88_tmp[vsize + j207];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = j208 + 1) {
				fRec87_tmp[j208] = fRec87_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec87[i] = fConst339 * (fConst342 * fRec88[i] + fConst343 * fRec88[i - 1] + fConst342 * fRec88[i - 2]) - fConst344 * (fConst345 * fRec87[i - 2] + fConst346 * fRec87[i - 1]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = j209 + 1) {
				fRec87_perm[j209] = fRec87_tmp[vsize + j209];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec47[i] = fConst344 * (fConst347 * fRec87[i] + fConst348 * fRec87[i - 1] + fConst347 * fRec87[i - 2]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = j218 + 1) {
				fRec96_tmp[j218] = fRec96_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec96[i] = fZec47[i] - fConst371 * (fConst372 * fRec96[i - 2] + fConst373 * fRec96[i - 1]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = j219 + 1) {
				fRec96_perm[j219] = fRec96_tmp[vsize + j219];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = j220 + 1) {
				fRec95_tmp[j220] = fRec95_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec95[i] = fConst371 * (fConst375 * fRec96[i] + fConst376 * fRec96[i - 1] + fConst375 * fRec96[i - 2]) - fConst377 * (fConst378 * fRec95[i - 2] + fConst379 * fRec95[i - 1]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = j221 + 1) {
				fRec95_perm[j221] = fRec95_tmp[vsize + j221];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = j222 + 1) {
				fRec94_tmp[j222] = fRec94_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec94[i] = fConst377 * (fConst380 * fRec95[i] + fConst381 * fRec95[i - 1] + fConst380 * fRec95[i - 2]) - fConst382 * (fConst383 * fRec94[i - 2] + fConst384 * fRec94[i - 1]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = j223 + 1) {
				fRec94_perm[j223] = fRec94_tmp[vsize + j223];
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec48[i] = fConst382 * (fConst385 * fRec94[i] + fConst386 * fRec94[i - 1] + fConst385 * fRec94[i - 2]);
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = j232 + 1) {
				fRec103_tmp[j232] = fRec103_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec103[i] = fZec48[i] - fConst409 * (fConst410 * fRec103[i - 2] + fConst411 * fRec103[i - 1]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = j233 + 1) {
				fRec103_perm[j233] = fRec103_tmp[vsize + j233];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = j234 + 1) {
				fRec102_tmp[j234] = fRec102_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec102[i] = fConst409 * (fConst413 * fRec103[i] + fConst414 * fRec103[i - 1] + fConst413 * fRec103[i - 2]) - fConst415 * (fConst416 * fRec102[i - 2] + fConst417 * fRec102[i - 1]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = j235 + 1) {
				fRec102_perm[j235] = fRec102_tmp[vsize + j235];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = j236 + 1) {
				fRec101_tmp[j236] = fRec101_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec101[i] = fConst415 * (fConst418 * fRec102[i] + fConst419 * fRec102[i - 1] + fConst418 * fRec102[i - 2]) - fConst420 * (fConst421 * fRec101[i - 2] + fConst422 * fRec101[i - 1]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = j237 + 1) {
				fRec101_perm[j237] = fRec101_tmp[vsize + j237];
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec49[i] = fConst420 * (fConst423 * fRec101[i] + fConst424 * fRec101[i - 1] + fConst423 * fRec101[i - 2]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = j246 + 1) {
				fRec110_tmp[j246] = fRec110_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec110[i] = fZec49[i] - fConst447 * (fConst448 * fRec110[i - 2] + fConst449 * fRec110[i - 1]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = j247 + 1) {
				fRec110_perm[j247] = fRec110_tmp[vsize + j247];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = j248 + 1) {
				fRec109_tmp[j248] = fRec109_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec109[i] = fConst447 * (fConst451 * fRec110[i] + fConst452 * fRec110[i - 1] + fConst451 * fRec110[i - 2]) - fConst453 * (fConst454 * fRec109[i - 2] + fConst455 * fRec109[i - 1]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = j249 + 1) {
				fRec109_perm[j249] = fRec109_tmp[vsize + j249];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = j250 + 1) {
				fRec108_tmp[j250] = fRec108_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec108[i] = fConst453 * (fConst456 * fRec109[i] + fConst457 * fRec109[i - 1] + fConst456 * fRec109[i - 2]) - fConst458 * (fConst459 * fRec108[i - 2] + fConst460 * fRec108[i - 1]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = j251 + 1) {
				fRec108_perm[j251] = fRec108_tmp[vsize + j251];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec50[i] = fConst458 * (fConst461 * fRec108[i] + fConst462 * fRec108[i - 1] + fConst461 * fRec108[i - 2]);
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = j260 + 1) {
				fRec117_tmp[j260] = fRec117_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec117[i] = fZec50[i] - fConst485 * (fConst486 * fRec117[i - 2] + fConst487 * fRec117[i - 1]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = j261 + 1) {
				fRec117_perm[j261] = fRec117_tmp[vsize + j261];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = j262 + 1) {
				fRec116_tmp[j262] = fRec116_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec116[i] = fConst485 * (fConst489 * fRec117[i] + fConst490 * fRec117[i - 1] + fConst489 * fRec117[i - 2]) - fConst491 * (fConst492 * fRec116[i - 2] + fConst493 * fRec116[i - 1]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = j263 + 1) {
				fRec116_perm[j263] = fRec116_tmp[vsize + j263];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = j264 + 1) {
				fRec115_tmp[j264] = fRec115_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec115[i] = fConst491 * (fConst494 * fRec116[i] + fConst495 * fRec116[i - 1] + fConst494 * fRec116[i - 2]) - fConst496 * (fConst497 * fRec115[i - 2] + fConst498 * fRec115[i - 1]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = j265 + 1) {
				fRec115_perm[j265] = fRec115_tmp[vsize + j265];
			}
			/* Vectorizable loop 123 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec51[i] = fConst496 * (fConst499 * fRec115[i] + fConst500 * fRec115[i - 1] + fConst499 * fRec115[i - 2]);
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = j84 + 1) {
				fRec26_tmp[j84] = fRec26_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec26[i] = fZec38[i] - fConst8 * (fConst9 * fRec26[i - 2] + fConst12 * fRec26[i - 1]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = j85 + 1) {
				fRec26_perm[j85] = fRec26_tmp[vsize + j85];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = j98 + 1) {
				fRec30_tmp[j98] = fRec30_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec30[i] = fZec39[i] - fConst47 * (fConst48 * fRec30[i - 2] + fConst51 * fRec30[i - 1]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = j99 + 1) {
				fRec30_perm[j99] = fRec30_tmp[vsize + j99];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = j112 + 1) {
				fRec37_tmp[j112] = fRec37_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec37[i] = fZec40[i] - fConst85 * (fConst86 * fRec37[i - 2] + fConst89 * fRec37[i - 1]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = j113 + 1) {
				fRec37_perm[j113] = fRec37_tmp[vsize + j113];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = j126 + 1) {
				fRec44_tmp[j126] = fRec44_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec44[i] = fZec41[i] - fConst123 * (fConst124 * fRec44[i - 2] + fConst127 * fRec44[i - 1]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = j127 + 1) {
				fRec44_perm[j127] = fRec44_tmp[vsize + j127];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = j140 + 1) {
				fRec51_tmp[j140] = fRec51_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec51[i] = fZec42[i] - fConst161 * (fConst162 * fRec51[i - 2] + fConst165 * fRec51[i - 1]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = j141 + 1) {
				fRec51_perm[j141] = fRec51_tmp[vsize + j141];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = j154 + 1) {
				fRec58_tmp[j154] = fRec58_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec58[i] = fZec43[i] - fConst199 * (fConst200 * fRec58[i - 2] + fConst203 * fRec58[i - 1]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = j155 + 1) {
				fRec58_perm[j155] = fRec58_tmp[vsize + j155];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = j168 + 1) {
				fRec65_tmp[j168] = fRec65_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec65[i] = fZec44[i] - fConst237 * (fConst238 * fRec65[i - 2] + fConst241 * fRec65[i - 1]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = j169 + 1) {
				fRec65_perm[j169] = fRec65_tmp[vsize + j169];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = j182 + 1) {
				fRec72_tmp[j182] = fRec72_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec72[i] = fZec45[i] - fConst275 * (fConst276 * fRec72[i - 2] + fConst279 * fRec72[i - 1]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = j183 + 1) {
				fRec72_perm[j183] = fRec72_tmp[vsize + j183];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = j196 + 1) {
				fRec79_tmp[j196] = fRec79_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec79[i] = fZec46[i] - fConst313 * (fConst314 * fRec79[i - 2] + fConst317 * fRec79[i - 1]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = j197 + 1) {
				fRec79_perm[j197] = fRec79_tmp[vsize + j197];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = j210 + 1) {
				fRec86_tmp[j210] = fRec86_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec86[i] = fZec47[i] - fConst351 * (fConst352 * fRec86[i - 2] + fConst355 * fRec86[i - 1]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = j211 + 1) {
				fRec86_perm[j211] = fRec86_tmp[vsize + j211];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = j224 + 1) {
				fRec93_tmp[j224] = fRec93_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec93[i] = fZec48[i] - fConst389 * (fConst390 * fRec93[i - 2] + fConst393 * fRec93[i - 1]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = j225 + 1) {
				fRec93_perm[j225] = fRec93_tmp[vsize + j225];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = j238 + 1) {
				fRec100_tmp[j238] = fRec100_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec100[i] = fZec49[i] - fConst427 * (fConst428 * fRec100[i - 2] + fConst431 * fRec100[i - 1]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = j239 + 1) {
				fRec100_perm[j239] = fRec100_tmp[vsize + j239];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = j252 + 1) {
				fRec107_tmp[j252] = fRec107_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec107[i] = fZec50[i] - fConst465 * (fConst466 * fRec107[i - 2] + fConst469 * fRec107[i - 1]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = j253 + 1) {
				fRec107_perm[j253] = fRec107_tmp[vsize + j253];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = j266 + 1) {
				fRec114_tmp[j266] = fRec114_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec114[i] = fZec51[i] - fConst503 * (fConst504 * fRec114[i - 2] + fConst507 * fRec114[i - 1]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = j267 + 1) {
				fRec114_perm[j267] = fRec114_tmp[vsize + j267];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = j274 + 1) {
				fRec121_tmp[j274] = fRec121_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec121[i] = fZec51[i] - fConst523 * (fConst524 * fRec121[i - 2] + fConst525 * fRec121[i - 1]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = j275 + 1) {
				fRec121_perm[j275] = fRec121_tmp[vsize + j275];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = j86 + 1) {
				fRec25_tmp[j86] = fRec25_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec25[i] = fConst8 * (fConst14 * fRec26[i] + fConst15 * fRec26[i - 1] + fConst14 * fRec26[i - 2]) - fConst16 * (fConst17 * fRec25[i - 2] + fConst18 * fRec25[i - 1]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = j87 + 1) {
				fRec25_perm[j87] = fRec25_tmp[vsize + j87];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = j100 + 1) {
				fRec29_tmp[j100] = fRec29_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec29[i] = fConst47 * (fConst53 * fRec30[i] + fConst54 * fRec30[i - 1] + fConst53 * fRec30[i - 2]) - fConst55 * (fConst56 * fRec29[i - 2] + fConst57 * fRec29[i - 1]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = j101 + 1) {
				fRec29_perm[j101] = fRec29_tmp[vsize + j101];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = j114 + 1) {
				fRec36_tmp[j114] = fRec36_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec36[i] = fConst85 * (fConst91 * fRec37[i] + fConst92 * fRec37[i - 1] + fConst91 * fRec37[i - 2]) - fConst93 * (fConst94 * fRec36[i - 2] + fConst95 * fRec36[i - 1]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = j115 + 1) {
				fRec36_perm[j115] = fRec36_tmp[vsize + j115];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = j128 + 1) {
				fRec43_tmp[j128] = fRec43_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec43[i] = fConst123 * (fConst129 * fRec44[i] + fConst130 * fRec44[i - 1] + fConst129 * fRec44[i - 2]) - fConst131 * (fConst132 * fRec43[i - 2] + fConst133 * fRec43[i - 1]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = j129 + 1) {
				fRec43_perm[j129] = fRec43_tmp[vsize + j129];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = j142 + 1) {
				fRec50_tmp[j142] = fRec50_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec50[i] = fConst161 * (fConst167 * fRec51[i] + fConst168 * fRec51[i - 1] + fConst167 * fRec51[i - 2]) - fConst169 * (fConst170 * fRec50[i - 2] + fConst171 * fRec50[i - 1]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = j143 + 1) {
				fRec50_perm[j143] = fRec50_tmp[vsize + j143];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = j156 + 1) {
				fRec57_tmp[j156] = fRec57_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec57[i] = fConst199 * (fConst205 * fRec58[i] + fConst206 * fRec58[i - 1] + fConst205 * fRec58[i - 2]) - fConst207 * (fConst208 * fRec57[i - 2] + fConst209 * fRec57[i - 1]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = j157 + 1) {
				fRec57_perm[j157] = fRec57_tmp[vsize + j157];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = j170 + 1) {
				fRec64_tmp[j170] = fRec64_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec64[i] = fConst237 * (fConst243 * fRec65[i] + fConst244 * fRec65[i - 1] + fConst243 * fRec65[i - 2]) - fConst245 * (fConst246 * fRec64[i - 2] + fConst247 * fRec64[i - 1]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = j171 + 1) {
				fRec64_perm[j171] = fRec64_tmp[vsize + j171];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = j184 + 1) {
				fRec71_tmp[j184] = fRec71_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec71[i] = fConst275 * (fConst281 * fRec72[i] + fConst282 * fRec72[i - 1] + fConst281 * fRec72[i - 2]) - fConst283 * (fConst284 * fRec71[i - 2] + fConst285 * fRec71[i - 1]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = j185 + 1) {
				fRec71_perm[j185] = fRec71_tmp[vsize + j185];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = j198 + 1) {
				fRec78_tmp[j198] = fRec78_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec78[i] = fConst313 * (fConst319 * fRec79[i] + fConst320 * fRec79[i - 1] + fConst319 * fRec79[i - 2]) - fConst321 * (fConst322 * fRec78[i - 2] + fConst323 * fRec78[i - 1]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = j199 + 1) {
				fRec78_perm[j199] = fRec78_tmp[vsize + j199];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = j212 + 1) {
				fRec85_tmp[j212] = fRec85_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec85[i] = fConst351 * (fConst357 * fRec86[i] + fConst358 * fRec86[i - 1] + fConst357 * fRec86[i - 2]) - fConst359 * (fConst360 * fRec85[i - 2] + fConst361 * fRec85[i - 1]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = j213 + 1) {
				fRec85_perm[j213] = fRec85_tmp[vsize + j213];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = j226 + 1) {
				fRec92_tmp[j226] = fRec92_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec92[i] = fConst389 * (fConst395 * fRec93[i] + fConst396 * fRec93[i - 1] + fConst395 * fRec93[i - 2]) - fConst397 * (fConst398 * fRec92[i - 2] + fConst399 * fRec92[i - 1]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = j227 + 1) {
				fRec92_perm[j227] = fRec92_tmp[vsize + j227];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = j240 + 1) {
				fRec99_tmp[j240] = fRec99_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec99[i] = fConst427 * (fConst433 * fRec100[i] + fConst434 * fRec100[i - 1] + fConst433 * fRec100[i - 2]) - fConst435 * (fConst436 * fRec99[i - 2] + fConst437 * fRec99[i - 1]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = j241 + 1) {
				fRec99_perm[j241] = fRec99_tmp[vsize + j241];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = j254 + 1) {
				fRec106_tmp[j254] = fRec106_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec106[i] = fConst465 * (fConst471 * fRec107[i] + fConst472 * fRec107[i - 1] + fConst471 * fRec107[i - 2]) - fConst473 * (fConst474 * fRec106[i - 2] + fConst475 * fRec106[i - 1]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = j255 + 1) {
				fRec106_perm[j255] = fRec106_tmp[vsize + j255];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = j268 + 1) {
				fRec113_tmp[j268] = fRec113_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec113[i] = fConst503 * (fConst509 * fRec114[i] + fConst510 * fRec114[i - 1] + fConst509 * fRec114[i - 2]) - fConst511 * (fConst512 * fRec113[i - 2] + fConst513 * fRec113[i - 1]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = j269 + 1) {
				fRec113_perm[j269] = fRec113_tmp[vsize + j269];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = j276 + 1) {
				fRec120_tmp[j276] = fRec120_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec120[i] = fConst523 * (fConst527 * fRec121[i] + fConst528 * fRec121[i - 1] + fConst527 * fRec121[i - 2]) - fConst529 * (fConst530 * fRec120[i - 2] + fConst531 * fRec120[i - 1]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = j277 + 1) {
				fRec120_perm[j277] = fRec120_tmp[vsize + j277];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = j88 + 1) {
				fRec24_tmp[j88] = fRec24_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec24[i] = fConst16 * (fConst20 * fRec25[i] + fConst21 * fRec25[i - 1] + fConst20 * fRec25[i - 2]) - fConst22 * (fConst23 * fRec24[i - 2] + fConst24 * fRec24[i - 1]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = j89 + 1) {
				fRec24_perm[j89] = fRec24_tmp[vsize + j89];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = j102 + 1) {
				fRec28_tmp[j102] = fRec28_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec28[i] = fConst55 * (fConst59 * fRec29[i] + fConst60 * fRec29[i - 1] + fConst59 * fRec29[i - 2]) - fConst61 * (fConst62 * fRec28[i - 2] + fConst63 * fRec28[i - 1]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = j103 + 1) {
				fRec28_perm[j103] = fRec28_tmp[vsize + j103];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = j116 + 1) {
				fRec35_tmp[j116] = fRec35_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec35[i] = fConst93 * (fConst97 * fRec36[i] + fConst98 * fRec36[i - 1] + fConst97 * fRec36[i - 2]) - fConst99 * (fConst100 * fRec35[i - 2] + fConst101 * fRec35[i - 1]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = j117 + 1) {
				fRec35_perm[j117] = fRec35_tmp[vsize + j117];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = j130 + 1) {
				fRec42_tmp[j130] = fRec42_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec42[i] = fConst131 * (fConst135 * fRec43[i] + fConst136 * fRec43[i - 1] + fConst135 * fRec43[i - 2]) - fConst137 * (fConst138 * fRec42[i - 2] + fConst139 * fRec42[i - 1]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = j131 + 1) {
				fRec42_perm[j131] = fRec42_tmp[vsize + j131];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = j144 + 1) {
				fRec49_tmp[j144] = fRec49_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec49[i] = fConst169 * (fConst173 * fRec50[i] + fConst174 * fRec50[i - 1] + fConst173 * fRec50[i - 2]) - fConst175 * (fConst176 * fRec49[i - 2] + fConst177 * fRec49[i - 1]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = j145 + 1) {
				fRec49_perm[j145] = fRec49_tmp[vsize + j145];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = j158 + 1) {
				fRec56_tmp[j158] = fRec56_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec56[i] = fConst207 * (fConst211 * fRec57[i] + fConst212 * fRec57[i - 1] + fConst211 * fRec57[i - 2]) - fConst213 * (fConst214 * fRec56[i - 2] + fConst215 * fRec56[i - 1]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = j159 + 1) {
				fRec56_perm[j159] = fRec56_tmp[vsize + j159];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = j172 + 1) {
				fRec63_tmp[j172] = fRec63_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec63[i] = fConst245 * (fConst249 * fRec64[i] + fConst250 * fRec64[i - 1] + fConst249 * fRec64[i - 2]) - fConst251 * (fConst252 * fRec63[i - 2] + fConst253 * fRec63[i - 1]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = j173 + 1) {
				fRec63_perm[j173] = fRec63_tmp[vsize + j173];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = j186 + 1) {
				fRec70_tmp[j186] = fRec70_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec70[i] = fConst283 * (fConst287 * fRec71[i] + fConst288 * fRec71[i - 1] + fConst287 * fRec71[i - 2]) - fConst289 * (fConst290 * fRec70[i - 2] + fConst291 * fRec70[i - 1]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = j187 + 1) {
				fRec70_perm[j187] = fRec70_tmp[vsize + j187];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = j200 + 1) {
				fRec77_tmp[j200] = fRec77_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec77[i] = fConst321 * (fConst325 * fRec78[i] + fConst326 * fRec78[i - 1] + fConst325 * fRec78[i - 2]) - fConst327 * (fConst328 * fRec77[i - 2] + fConst329 * fRec77[i - 1]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = j201 + 1) {
				fRec77_perm[j201] = fRec77_tmp[vsize + j201];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = j214 + 1) {
				fRec84_tmp[j214] = fRec84_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec84[i] = fConst359 * (fConst363 * fRec85[i] + fConst364 * fRec85[i - 1] + fConst363 * fRec85[i - 2]) - fConst365 * (fConst366 * fRec84[i - 2] + fConst367 * fRec84[i - 1]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = j215 + 1) {
				fRec84_perm[j215] = fRec84_tmp[vsize + j215];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = j228 + 1) {
				fRec91_tmp[j228] = fRec91_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec91[i] = fConst397 * (fConst401 * fRec92[i] + fConst402 * fRec92[i - 1] + fConst401 * fRec92[i - 2]) - fConst403 * (fConst404 * fRec91[i - 2] + fConst405 * fRec91[i - 1]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = j229 + 1) {
				fRec91_perm[j229] = fRec91_tmp[vsize + j229];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = j242 + 1) {
				fRec98_tmp[j242] = fRec98_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec98[i] = fConst435 * (fConst439 * fRec99[i] + fConst440 * fRec99[i - 1] + fConst439 * fRec99[i - 2]) - fConst441 * (fConst442 * fRec98[i - 2] + fConst443 * fRec98[i - 1]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = j243 + 1) {
				fRec98_perm[j243] = fRec98_tmp[vsize + j243];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = j256 + 1) {
				fRec105_tmp[j256] = fRec105_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec105[i] = fConst473 * (fConst477 * fRec106[i] + fConst478 * fRec106[i - 1] + fConst477 * fRec106[i - 2]) - fConst479 * (fConst480 * fRec105[i - 2] + fConst481 * fRec105[i - 1]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = j257 + 1) {
				fRec105_perm[j257] = fRec105_tmp[vsize + j257];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = j270 + 1) {
				fRec112_tmp[j270] = fRec112_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec112[i] = fConst511 * (fConst515 * fRec113[i] + fConst516 * fRec113[i - 1] + fConst515 * fRec113[i - 2]) - fConst517 * (fConst518 * fRec112[i - 2] + fConst519 * fRec112[i - 1]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = j271 + 1) {
				fRec112_perm[j271] = fRec112_tmp[vsize + j271];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = j278 + 1) {
				fRec119_tmp[j278] = fRec119_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec119[i] = fConst529 * (fConst532 * fRec120[i] + fConst533 * fRec120[i - 1] + fConst532 * fRec120[i - 2]) - fConst534 * (fConst535 * fRec119[i - 2] + fConst536 * fRec119[i - 1]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = j279 + 1) {
				fRec119_perm[j279] = fRec119_tmp[vsize + j279];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = j90 + 1) {
				fRec23_tmp[j90] = fRec23_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec23[i] = fRec23[i - 1] * fSlow34 + std::fabs(fConst22 * (fConst27 * fRec24[i] + fConst28 * fRec24[i - 1] + fConst27 * fRec24[i - 2])) * fSlow35;
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = j91 + 1) {
				fRec23_perm[j91] = fRec23_tmp[vsize + j91];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = j104 + 1) {
				fRec27_tmp[j104] = fRec27_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec27[i] = fSlow34 * fRec27[i - 1] + fSlow35 * std::fabs(fConst61 * (fConst65 * fRec28[i] + fConst66 * fRec28[i - 1] + fConst65 * fRec28[i - 2]));
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = j105 + 1) {
				fRec27_perm[j105] = fRec27_tmp[vsize + j105];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = j118 + 1) {
				fRec34_tmp[j118] = fRec34_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec34[i] = fSlow34 * fRec34[i - 1] + fSlow35 * std::fabs(fConst99 * (fConst103 * fRec35[i] + fConst104 * fRec35[i - 1] + fConst103 * fRec35[i - 2]));
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = j119 + 1) {
				fRec34_perm[j119] = fRec34_tmp[vsize + j119];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = j132 + 1) {
				fRec41_tmp[j132] = fRec41_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec41[i] = fSlow34 * fRec41[i - 1] + fSlow35 * std::fabs(fConst137 * (fConst141 * fRec42[i] + fConst142 * fRec42[i - 1] + fConst141 * fRec42[i - 2]));
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = j133 + 1) {
				fRec41_perm[j133] = fRec41_tmp[vsize + j133];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = j146 + 1) {
				fRec48_tmp[j146] = fRec48_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec48[i] = fSlow34 * fRec48[i - 1] + fSlow35 * std::fabs(fConst175 * (fConst179 * fRec49[i] + fConst180 * fRec49[i - 1] + fConst179 * fRec49[i - 2]));
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = j147 + 1) {
				fRec48_perm[j147] = fRec48_tmp[vsize + j147];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = j160 + 1) {
				fRec55_tmp[j160] = fRec55_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec55[i] = fSlow34 * fRec55[i - 1] + fSlow35 * std::fabs(fConst213 * (fConst217 * fRec56[i] + fConst218 * fRec56[i - 1] + fConst217 * fRec56[i - 2]));
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = j161 + 1) {
				fRec55_perm[j161] = fRec55_tmp[vsize + j161];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = j174 + 1) {
				fRec62_tmp[j174] = fRec62_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec62[i] = fSlow34 * fRec62[i - 1] + fSlow35 * std::fabs(fConst251 * (fConst255 * fRec63[i] + fConst256 * fRec63[i - 1] + fConst255 * fRec63[i - 2]));
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = j175 + 1) {
				fRec62_perm[j175] = fRec62_tmp[vsize + j175];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = j188 + 1) {
				fRec69_tmp[j188] = fRec69_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec69[i] = fSlow34 * fRec69[i - 1] + fSlow35 * std::fabs(fConst289 * (fConst293 * fRec70[i] + fConst294 * fRec70[i - 1] + fConst293 * fRec70[i - 2]));
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = j189 + 1) {
				fRec69_perm[j189] = fRec69_tmp[vsize + j189];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = j202 + 1) {
				fRec76_tmp[j202] = fRec76_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec76[i] = fSlow34 * fRec76[i - 1] + fSlow35 * std::fabs(fConst327 * (fConst331 * fRec77[i] + fConst332 * fRec77[i - 1] + fConst331 * fRec77[i - 2]));
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = j203 + 1) {
				fRec76_perm[j203] = fRec76_tmp[vsize + j203];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = j216 + 1) {
				fRec83_tmp[j216] = fRec83_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec83[i] = fSlow34 * fRec83[i - 1] + fSlow35 * std::fabs(fConst365 * (fConst369 * fRec84[i] + fConst370 * fRec84[i - 1] + fConst369 * fRec84[i - 2]));
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = j217 + 1) {
				fRec83_perm[j217] = fRec83_tmp[vsize + j217];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = j230 + 1) {
				fRec90_tmp[j230] = fRec90_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec90[i] = fSlow34 * fRec90[i - 1] + fSlow35 * std::fabs(fConst403 * (fConst407 * fRec91[i] + fConst408 * fRec91[i - 1] + fConst407 * fRec91[i - 2]));
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = j231 + 1) {
				fRec90_perm[j231] = fRec90_tmp[vsize + j231];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = j244 + 1) {
				fRec97_tmp[j244] = fRec97_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec97[i] = fSlow34 * fRec97[i - 1] + fSlow35 * std::fabs(fConst441 * (fConst445 * fRec98[i] + fConst446 * fRec98[i - 1] + fConst445 * fRec98[i - 2]));
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = j245 + 1) {
				fRec97_perm[j245] = fRec97_tmp[vsize + j245];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = j258 + 1) {
				fRec104_tmp[j258] = fRec104_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec104[i] = fSlow34 * fRec104[i - 1] + fSlow35 * std::fabs(fConst479 * (fConst483 * fRec105[i] + fConst484 * fRec105[i - 1] + fConst483 * fRec105[i - 2]));
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = j259 + 1) {
				fRec104_perm[j259] = fRec104_tmp[vsize + j259];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = j272 + 1) {
				fRec111_tmp[j272] = fRec111_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec111[i] = fSlow34 * fRec111[i - 1] + fSlow35 * std::fabs(fConst517 * (fConst521 * fRec112[i] + fConst522 * fRec112[i - 1] + fConst521 * fRec112[i - 2]));
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = j273 + 1) {
				fRec111_perm[j273] = fRec111_tmp[vsize + j273];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = j280 + 1) {
				fRec118_tmp[j280] = fRec118_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec118[i] = fSlow34 * fRec118[i - 1] + fSlow35 * std::fabs(fConst534 * (fConst537 * fRec119[i] + fConst538 * fRec119[i - 1] + fConst537 * fRec119[i - 2]));
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = j281 + 1) {
				fRec118_perm[j281] = fRec118_tmp[vsize + j281];
			}
			/* Vectorizable loop 184 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec23[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec27[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec34[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec41[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec48[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec55[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec62[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec69[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec76[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec83[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec90[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec97[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec104[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec111[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec118[i]));
				fZec52[i] = fZec38[i];
			}
			/* Vectorizable loop 185 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec52[i]);
			}
			/* Vectorizable loop 186 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec52[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = count - vindex;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec6_tmp[j2] = fRec6_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec6[i] = fRec6[i - 1] * fSlow2 + fSlow3;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec6_perm[j3] = fRec6_tmp[vsize + j3];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec6[i]));
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec6[i]));
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec6[i]));
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				fRec5_tmp[j4] = fRec5_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fRec5[i - 1] + fConst1 * fZec0[i];
				fRec5[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				fRec5_perm[j5] = fRec5_tmp[vsize + j5];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fRec7_tmp[j6] = fRec7_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = fRec7[i - 1] + fConst1 * fZec2[i];
				fRec7[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fRec7_perm[j7] = fRec7_tmp[vsize + j7];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fRec8_tmp[j8] = fRec8_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = fRec8[i - 1] + fConst1 * fZec4[i];
				fRec8[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fRec8_perm[j9] = fRec8_tmp[vsize + j9];
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = 2.0 * fRec5[i];
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec13[i] = 2.0 * fRec7[i];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec16[i] = 2.0 * fRec8[i];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = fZec7[i] + -1.0;
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec14[i] = fZec13[i] + -1.0;
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec17[i] = fZec16[i] + -1.0;
			}
			/* Vectorizable loop 13 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fYec0_tmp[j16] = fYec0_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[i] = mydsp_faustpower2_f(fZec8[i]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fYec0_perm[j17] = fYec0_tmp[vsize + j17];
			}
			/* Vectorizable loop 14 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
				fYec6_tmp[j28] = fYec6_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec6[i] = mydsp_faustpower2_f(fZec14[i]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
				fYec6_perm[j29] = fYec6_tmp[vsize + j29];
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
				fYec12_tmp[j40] = fYec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec12[i] = mydsp_faustpower2_f(fZec17[i]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
				fYec12_perm[j41] = fYec12_tmp[vsize + j41];
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				iRec9_tmp[j10] = iRec9_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iRec9[i] = 1103515245 * iRec9[i - 1] + 12345;
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				iRec9_perm[j11] = iRec9_tmp[vsize + j11];
			}
			/* Vectorizable loop 17 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				iVec0_tmp[j14] = iVec0_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iVec0[i] = 1;
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				iVec0_perm[j15] = iVec0_tmp[vsize + j15];
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec11[i] = mydsp_faustpower3_f(fZec8[i]);
			}
			/* Vectorizable loop 19 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
				fYec3_tmp[j22] = fYec3_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
				fYec3_perm[j23] = fYec3_tmp[vsize + j23];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec15[i] = mydsp_faustpower3_f(fZec14[i]);
			}
			/* Vectorizable loop 21 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
				fYec9_tmp[j34] = fYec9_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
				fYec9_perm[j35] = fYec9_tmp[vsize + j35];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec18[i] = mydsp_faustpower3_f(fZec17[i]);
			}
			/* Vectorizable loop 23 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
				fYec15_tmp[j46] = fYec15_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
				fYec15_perm[j47] = fYec15_tmp[vsize + j47];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec9[i]);
			}
			/* Vectorizable loop 25 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fYec1_tmp[j18] = fYec1_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[i] = fZec11[i] + (1.0 - fZec7[i]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fYec1_perm[j19] = fYec1_tmp[vsize + j19];
			}
			/* Vectorizable loop 26 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
				fYec4_tmp[j24] = fYec4_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec4[i] = (fYec3[i] - fYec3[i - 1]) / fZec0[i];
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
				fYec4_perm[j25] = fYec4_tmp[vsize + j25];
			}
			/* Vectorizable loop 27 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
				fYec7_tmp[j30] = fYec7_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec7[i] = fZec15[i] + (1.0 - fZec13[i]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
				fYec7_perm[j31] = fYec7_tmp[vsize + j31];
			}
			/* Vectorizable loop 28 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
				fYec10_tmp[j36] = fYec10_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec10[i] = (fYec9[i] - fYec9[i - 1]) / fZec2[i];
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
				fYec10_perm[j37] = fYec10_tmp[vsize + j37];
			}
			/* Vectorizable loop 29 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
				fYec13_tmp[j42] = fYec13_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec13[i] = fZec18[i] + (1.0 - fZec16[i]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
				fYec13_perm[j43] = fYec13_tmp[vsize + j43];
			}
			/* Vectorizable loop 30 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
				fYec16_tmp[j48] = fYec16_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec16[i] = (fYec15[i] - fYec15[i - 1]) / fZec4[i];
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
				fYec16_perm[j49] = fYec16_tmp[vsize + j49];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fRec4_tmp[j0] = fRec4_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec4[i] = fSlow0 + 0.999 * fRec4[i - 1];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fRec4_perm[j1] = fRec4_tmp[vsize + j1];
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fRec10_tmp[j12] = fRec10_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec10[i] = 0.5221894 * fRec10[i - 3] + fZec6[i] + 2.494956002 * fRec10[i - 1] - 2.017265875 * fRec10[i - 2];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fRec10_perm[j13] = fRec10_tmp[vsize + j13];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = static_cast<double>(iVec0[i - 1]);
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec10[i] = static_cast<double>(iVec0[i - 2]);
			}
			/* Vectorizable loop 35 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
				fYec2_tmp[j20] = fYec2_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[i] = (fZec11[i] + (1.0 - (fZec7[i] + fYec1[i - 1]))) / fZec0[i];
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
				fYec2_perm[j21] = fYec2_tmp[vsize + j21];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec12[i] = static_cast<double>(iVec0[i - 3]);
			}
			/* Vectorizable loop 37 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
				fYec5_tmp[j26] = fYec5_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec5[i] = (fYec4[i] - fYec4[i - 1]) / fZec0[i];
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
				fYec5_perm[j27] = fYec5_tmp[vsize + j27];
			}
			/* Vectorizable loop 38 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
				fYec8_tmp[j32] = fYec8_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec8[i] = (fZec15[i] + (1.0 - (fZec13[i] + fYec7[i - 1]))) / fZec2[i];
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
				fYec8_perm[j33] = fYec8_tmp[vsize + j33];
			}
			/* Vectorizable loop 39 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
				fYec11_tmp[j38] = fYec11_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec11[i] = (fYec10[i] - fYec10[i - 1]) / fZec2[i];
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
				fYec11_perm[j39] = fYec11_tmp[vsize + j39];
			}
			/* Vectorizable loop 40 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
				fYec14_tmp[j44] = fYec14_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec14[i] = (fZec18[i] + (1.0 - (fZec16[i] + fYec13[i - 1]))) / fZec4[i];
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
				fYec14_perm[j45] = fYec14_tmp[vsize + j45];
			}
			/* Vectorizable loop 41 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
				fYec17_tmp[j50] = fYec17_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec17[i] = (fYec16[i] - fYec16[i - 1]) / fZec4[i];
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
				fYec17_perm[j51] = fYec17_tmp[vsize + j51];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec19[i] = fRec4[i] * ((iSlow11) ? static_cast<double>(input0[i]) : ((iSlow12) ? ((iSlow17) ? 0.049922035 * fRec10[i] + 0.050612699 * fRec10[i - 2] - (0.095993537 * fRec10[i - 1] + 0.004408786 * fRec10[i - 3]) : fZec6[i]) : 0.3333333333333333 * fRec4[i] * (((iSlow14) ? ((iSlow16) ? fConst4 * (fZec12[i] * (fYec5[i] - fYec5[i - 1]) / fZec0[i]) : fConst3 * (fZec10[i] * (fYec2[i] - fYec2[i - 1]) / fZec0[i])) : ((iSlow15) ? fConst2 * (fZec9[i] * (fYec0[i] - fYec0[i - 1]) / fZec0[i]) : fZec8[i])) + ((iSlow14) ? ((iSlow16) ? fConst4 * (fZec12[i] * (fYec11[i] - fYec11[i - 1]) / fZec2[i]) : fConst3 * (fZec10[i] * (fYec8[i] - fYec8[i - 1]) / fZec2[i])) : ((iSlow15) ? fConst2 * (fZec9[i] * (fYec6[i] - fYec6[i - 1]) / fZec2[i]) : fZec14[i])) + ((iSlow14) ? ((iSlow16) ? fConst4 * (fZec12[i] * (fYec17[i] - fYec17[i - 1]) / fZec4[i]) : fConst3 * (fZec10[i] * (fYec14[i] - fYec14[i - 1]) / fZec4[i])) : ((iSlow15) ? fConst2 * (fZec9[i] * (fYec12[i] - fYec12[i - 1]) / fZec4[i]) : fZec17[i])))));
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec20[i] = ((iSlow10) ? 0.0 : fZec19[i]);
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec21[i] = std::fabs(fZec20[i]);
			}
			/* Recursive loop 45 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
				fRec14_tmp[j52] = fRec14_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec14[i] = fRec14[i - 1] * fSlow9 + std::fabs(2.0 * fZec21[i]) * fSlow18;
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
				fRec14_perm[j53] = fRec14_tmp[vsize + j53];
			}
			/* Recursive loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec13[i] = fRec14[i];
			}
			/* Vectorizable loop 47 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
				iYec18_tmp[j54] = iYec18_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iYec18[i] = fRec13[i] > fSlow20;
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
				iYec18_perm[j55] = iYec18_tmp[vsize + j55];
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
				iRec15_tmp[j56] = iRec15_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iRec15[i] = std::max<int>(iSlow19 * (iYec18[i] < iYec18[i - 1]), iRec15[i - 1] + -1);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
				iRec15_perm[j57] = iRec15_tmp[vsize + j57];
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec22[i] = std::fabs(std::max<double>(static_cast<double>(iYec18[i]), static_cast<double>(iRec15[i] > 0)));
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
				fRec12_tmp[j58] = fRec12_perm[j58];
			}
			for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
				fRec11_tmp[j60] = fRec11_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec23[i] = ((fRec11[i - 1] > fZec22[i]) ? fSlow22 : fSlow21);
				fRec12[i] = fRec12[i - 1] * fZec23[i] + fZec22[i] * (1.0 - fZec23[i]);
				fRec11[i] = fRec12[i];
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
				fRec12_perm[j59] = fRec12_tmp[vsize + j59];
			}
			for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
				fRec11_perm[j61] = fRec11_tmp[vsize + j61];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fHbargraph0 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(fRec11[i]));
				fZec24[i] = fZec20[i];
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
				fRec3_tmp[j62] = fRec3_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec3[i] = fRec3[i - 1] * fSlow9 + fSlow18 * std::fabs(fZec21[i] + std::fabs(fZec24[i]));
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
				fRec3_perm[j63] = fRec3_tmp[vsize + j63];
			}
			/* Recursive loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec2[i] = fRec3[i];
			}
			/* Vectorizable loop 54 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
				iYec19_tmp[j64] = iYec19_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iYec19[i] = fRec2[i] > fSlow20;
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
				iYec19_perm[j65] = iYec19_tmp[vsize + j65];
			}
			/* Recursive loop 55 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
				iRec16_tmp[j66] = iRec16_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iRec16[i] = std::max<int>(iSlow19 * (iYec19[i] < iYec19[i - 1]), iRec16[i - 1] + -1);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
				iRec16_perm[j67] = iRec16_tmp[vsize + j67];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec25[i] = std::fabs(std::max<double>(static_cast<double>(iYec19[i]), static_cast<double>(iRec16[i] > 0)));
			}
			/* Recursive loop 57 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
				fRec1_tmp[j68] = fRec1_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
				fRec0_tmp[j70] = fRec0_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec26[i] = ((fRec0[i - 1] > fZec25[i]) ? fSlow22 : fSlow21);
				fRec1[i] = fRec1[i - 1] * fZec26[i] + fZec25[i] * (1.0 - fZec26[i]);
				fRec0[i] = fRec1[i];
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
				fRec1_perm[j69] = fRec1_tmp[vsize + j69];
			}
			for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
				fRec0_perm[j71] = fRec0_tmp[vsize + j71];
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec27[i] = ((iSlow10) ? fZec19[i] : fRec0[i] * fZec24[i]);
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec29[i] = ((iSlow10) ? fZec19[i] : fRec0[i] * fZec20[i]);
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec28[i] = ((iSlow23) ? 0.0 : fZec27[i]);
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec30[i] = ((iSlow23) ? 0.0 : fZec29[i]);
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec31[i] = std::fabs(std::fabs(fZec28[i]) + std::fabs(fZec30[i]));
			}
			/* Recursive loop 63 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
				fRec19_tmp[j72] = fRec19_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
				fRec18_tmp[j74] = fRec18_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec32[i] = ((fRec18[i - 1] > fZec31[i]) ? fSlow27 : fSlow25);
				fRec19[i] = fRec19[i - 1] * fZec32[i] + fZec31[i] * (1.0 - fZec32[i]);
				fRec18[i] = fRec19[i];
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
				fRec19_perm[j73] = fRec19_tmp[vsize + j73];
			}
			for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
				fRec18_perm[j75] = fRec18_tmp[vsize + j75];
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
				fRec17_tmp[j76] = fRec17_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec17[i] = fRec17[i - 1] * fSlow28 + fSlow29 * std::max<double>(2e+01 * std::log10(fRec18[i]) - fSlow30, 0.0) * fSlow31;
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
				fRec17_perm[j77] = fRec17_tmp[vsize + j77];
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec33[i] = std::pow(1e+01, 0.05 * fRec17[i]);
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec34[i] = fZec28[i] * fZec33[i];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec35[i] = fZec30[i] * fZec33[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec36[i] = std::fabs(std::fabs(fZec34[i]) + std::fabs(fZec35[i]));
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
				fRec22_tmp[j78] = fRec22_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = j80 + 1) {
				fRec21_tmp[j80] = fRec21_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec37[i] = ((fRec21[i - 1] > fZec36[i]) ? fSlow27 : fSlow25);
				fRec22[i] = fRec22[i - 1] * fZec37[i] + fZec36[i] * (1.0 - fZec37[i]);
				fRec21[i] = fRec22[i];
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
				fRec22_perm[j79] = fRec22_tmp[vsize + j79];
			}
			for (int j81 = 0; j81 < 4; j81 = j81 + 1) {
				fRec21_perm[j81] = fRec21_tmp[vsize + j81];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = j82 + 1) {
				fRec20_tmp[j82] = fRec20_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec20[i] = fSlow28 * fRec20[i - 1] + fSlow29 * std::max<double>(2e+01 * std::log10(fRec21[i]) - fSlow30, 0.0) * fSlow31;
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = j83 + 1) {
				fRec20_perm[j83] = fRec20_tmp[vsize + j83];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fHbargraph1 = static_cast<FAUSTFLOAT>(2e+01 * std::log10(std::pow(1e+01, 0.05 * fRec20[i])));
				fZec38[i] = ((iSlow23) ? fZec27[i] : fSlow32 * fZec34[i]) + ((iSlow23) ? fZec29[i] : fSlow32 * fZec35[i]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = j92 + 1) {
				fRec33_tmp[j92] = fRec33_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec33[i] = fZec38[i] - fConst29 * (fConst30 * fRec33[i - 2] + fConst31 * fRec33[i - 1]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = j93 + 1) {
				fRec33_perm[j93] = fRec33_tmp[vsize + j93];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = j94 + 1) {
				fRec32_tmp[j94] = fRec32_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec32[i] = fConst29 * (fConst33 * fRec33[i] + fConst34 * fRec33[i - 1] + fConst33 * fRec33[i - 2]) - fConst35 * (fConst36 * fRec32[i - 2] + fConst37 * fRec32[i - 1]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = j95 + 1) {
				fRec32_perm[j95] = fRec32_tmp[vsize + j95];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = j96 + 1) {
				fRec31_tmp[j96] = fRec31_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec31[i] = fConst35 * (fConst38 * fRec32[i] + fConst39 * fRec32[i - 1] + fConst38 * fRec32[i - 2]) - fConst40 * (fConst41 * fRec31[i - 2] + fConst42 * fRec31[i - 1]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = j97 + 1) {
				fRec31_perm[j97] = fRec31_tmp[vsize + j97];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec39[i] = fConst40 * (fConst43 * fRec31[i] + fConst44 * fRec31[i - 1] + fConst43 * fRec31[i - 2]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = j106 + 1) {
				fRec40_tmp[j106] = fRec40_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec40[i] = fZec39[i] - fConst67 * (fConst68 * fRec40[i - 2] + fConst69 * fRec40[i - 1]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = j107 + 1) {
				fRec40_perm[j107] = fRec40_tmp[vsize + j107];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = j108 + 1) {
				fRec39_tmp[j108] = fRec39_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec39[i] = fConst67 * (fConst71 * fRec40[i] + fConst72 * fRec40[i - 1] + fConst71 * fRec40[i - 2]) - fConst73 * (fConst74 * fRec39[i - 2] + fConst75 * fRec39[i - 1]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = j109 + 1) {
				fRec39_perm[j109] = fRec39_tmp[vsize + j109];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = j110 + 1) {
				fRec38_tmp[j110] = fRec38_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec38[i] = fConst73 * (fConst76 * fRec39[i] + fConst77 * fRec39[i - 1] + fConst76 * fRec39[i - 2]) - fConst78 * (fConst79 * fRec38[i - 2] + fConst80 * fRec38[i - 1]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = j111 + 1) {
				fRec38_perm[j111] = fRec38_tmp[vsize + j111];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec40[i] = fConst78 * (fConst81 * fRec38[i] + fConst82 * fRec38[i - 1] + fConst81 * fRec38[i - 2]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = j120 + 1) {
				fRec47_tmp[j120] = fRec47_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec47[i] = fZec40[i] - fConst105 * (fConst106 * fRec47[i - 2] + fConst107 * fRec47[i - 1]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = j121 + 1) {
				fRec47_perm[j121] = fRec47_tmp[vsize + j121];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = j122 + 1) {
				fRec46_tmp[j122] = fRec46_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec46[i] = fConst105 * (fConst109 * fRec47[i] + fConst110 * fRec47[i - 1] + fConst109 * fRec47[i - 2]) - fConst111 * (fConst112 * fRec46[i - 2] + fConst113 * fRec46[i - 1]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = j123 + 1) {
				fRec46_perm[j123] = fRec46_tmp[vsize + j123];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = j124 + 1) {
				fRec45_tmp[j124] = fRec45_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec45[i] = fConst111 * (fConst114 * fRec46[i] + fConst115 * fRec46[i - 1] + fConst114 * fRec46[i - 2]) - fConst116 * (fConst117 * fRec45[i - 2] + fConst118 * fRec45[i - 1]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = j125 + 1) {
				fRec45_perm[j125] = fRec45_tmp[vsize + j125];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec41[i] = fConst116 * (fConst119 * fRec45[i] + fConst120 * fRec45[i - 1] + fConst119 * fRec45[i - 2]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = j134 + 1) {
				fRec54_tmp[j134] = fRec54_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec54[i] = fZec41[i] - fConst143 * (fConst144 * fRec54[i - 2] + fConst145 * fRec54[i - 1]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = j135 + 1) {
				fRec54_perm[j135] = fRec54_tmp[vsize + j135];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = j136 + 1) {
				fRec53_tmp[j136] = fRec53_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec53[i] = fConst143 * (fConst147 * fRec54[i] + fConst148 * fRec54[i - 1] + fConst147 * fRec54[i - 2]) - fConst149 * (fConst150 * fRec53[i - 2] + fConst151 * fRec53[i - 1]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = j137 + 1) {
				fRec53_perm[j137] = fRec53_tmp[vsize + j137];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = j138 + 1) {
				fRec52_tmp[j138] = fRec52_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec52[i] = fConst149 * (fConst152 * fRec53[i] + fConst153 * fRec53[i - 1] + fConst152 * fRec53[i - 2]) - fConst154 * (fConst155 * fRec52[i - 2] + fConst156 * fRec52[i - 1]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = j139 + 1) {
				fRec52_perm[j139] = fRec52_tmp[vsize + j139];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec42[i] = fConst154 * (fConst157 * fRec52[i] + fConst158 * fRec52[i - 1] + fConst157 * fRec52[i - 2]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = j148 + 1) {
				fRec61_tmp[j148] = fRec61_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec61[i] = fZec42[i] - fConst181 * (fConst182 * fRec61[i - 2] + fConst183 * fRec61[i - 1]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = j149 + 1) {
				fRec61_perm[j149] = fRec61_tmp[vsize + j149];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = j150 + 1) {
				fRec60_tmp[j150] = fRec60_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec60[i] = fConst181 * (fConst185 * fRec61[i] + fConst186 * fRec61[i - 1] + fConst185 * fRec61[i - 2]) - fConst187 * (fConst188 * fRec60[i - 2] + fConst189 * fRec60[i - 1]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = j151 + 1) {
				fRec60_perm[j151] = fRec60_tmp[vsize + j151];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = j152 + 1) {
				fRec59_tmp[j152] = fRec59_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec59[i] = fConst187 * (fConst190 * fRec60[i] + fConst191 * fRec60[i - 1] + fConst190 * fRec60[i - 2]) - fConst192 * (fConst193 * fRec59[i - 2] + fConst194 * fRec59[i - 1]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = j153 + 1) {
				fRec59_perm[j153] = fRec59_tmp[vsize + j153];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec43[i] = fConst192 * (fConst195 * fRec59[i] + fConst196 * fRec59[i - 1] + fConst195 * fRec59[i - 2]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = j162 + 1) {
				fRec68_tmp[j162] = fRec68_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec68[i] = fZec43[i] - fConst219 * (fConst220 * fRec68[i - 2] + fConst221 * fRec68[i - 1]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = j163 + 1) {
				fRec68_perm[j163] = fRec68_tmp[vsize + j163];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = j164 + 1) {
				fRec67_tmp[j164] = fRec67_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec67[i] = fConst219 * (fConst223 * fRec68[i] + fConst224 * fRec68[i - 1] + fConst223 * fRec68[i - 2]) - fConst225 * (fConst226 * fRec67[i - 2] + fConst227 * fRec67[i - 1]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = j165 + 1) {
				fRec67_perm[j165] = fRec67_tmp[vsize + j165];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = j166 + 1) {
				fRec66_tmp[j166] = fRec66_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec66[i] = fConst225 * (fConst228 * fRec67[i] + fConst229 * fRec67[i - 1] + fConst228 * fRec67[i - 2]) - fConst230 * (fConst231 * fRec66[i - 2] + fConst232 * fRec66[i - 1]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = j167 + 1) {
				fRec66_perm[j167] = fRec66_tmp[vsize + j167];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec44[i] = fConst230 * (fConst233 * fRec66[i] + fConst234 * fRec66[i - 1] + fConst233 * fRec66[i - 2]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = j176 + 1) {
				fRec75_tmp[j176] = fRec75_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec75[i] = fZec44[i] - fConst257 * (fConst258 * fRec75[i - 2] + fConst259 * fRec75[i - 1]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = j177 + 1) {
				fRec75_perm[j177] = fRec75_tmp[vsize + j177];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = j178 + 1) {
				fRec74_tmp[j178] = fRec74_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec74[i] = fConst257 * (fConst261 * fRec75[i] + fConst262 * fRec75[i - 1] + fConst261 * fRec75[i - 2]) - fConst263 * (fConst264 * fRec74[i - 2] + fConst265 * fRec74[i - 1]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = j179 + 1) {
				fRec74_perm[j179] = fRec74_tmp[vsize + j179];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = j180 + 1) {
				fRec73_tmp[j180] = fRec73_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec73[i] = fConst263 * (fConst266 * fRec74[i] + fConst267 * fRec74[i - 1] + fConst266 * fRec74[i - 2]) - fConst268 * (fConst269 * fRec73[i - 2] + fConst270 * fRec73[i - 1]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = j181 + 1) {
				fRec73_perm[j181] = fRec73_tmp[vsize + j181];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec45[i] = fConst268 * (fConst271 * fRec73[i] + fConst272 * fRec73[i - 1] + fConst271 * fRec73[i - 2]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = j190 + 1) {
				fRec82_tmp[j190] = fRec82_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec82[i] = fZec45[i] - fConst295 * (fConst296 * fRec82[i - 2] + fConst297 * fRec82[i - 1]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = j191 + 1) {
				fRec82_perm[j191] = fRec82_tmp[vsize + j191];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = j192 + 1) {
				fRec81_tmp[j192] = fRec81_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec81[i] = fConst295 * (fConst299 * fRec82[i] + fConst300 * fRec82[i - 1] + fConst299 * fRec82[i - 2]) - fConst301 * (fConst302 * fRec81[i - 2] + fConst303 * fRec81[i - 1]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = j193 + 1) {
				fRec81_perm[j193] = fRec81_tmp[vsize + j193];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = j194 + 1) {
				fRec80_tmp[j194] = fRec80_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec80[i] = fConst301 * (fConst304 * fRec81[i] + fConst305 * fRec81[i - 1] + fConst304 * fRec81[i - 2]) - fConst306 * (fConst307 * fRec80[i - 2] + fConst308 * fRec80[i - 1]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = j195 + 1) {
				fRec80_perm[j195] = fRec80_tmp[vsize + j195];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec46[i] = fConst306 * (fConst309 * fRec80[i] + fConst310 * fRec80[i - 1] + fConst309 * fRec80[i - 2]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = j204 + 1) {
				fRec89_tmp[j204] = fRec89_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec89[i] = fZec46[i] - fConst333 * (fConst334 * fRec89[i - 2] + fConst335 * fRec89[i - 1]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = j205 + 1) {
				fRec89_perm[j205] = fRec89_tmp[vsize + j205];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = j206 + 1) {
				fRec88_tmp[j206] = fRec88_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec88[i] = fConst333 * (fConst337 * fRec89[i] + fConst338 * fRec89[i - 1] + fConst337 * fRec89[i - 2]) - fConst339 * (fConst340 * fRec88[i - 2] + fConst341 * fRec88[i - 1]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = j207 + 1) {
				fRec88_perm[j207] = fRec88_tmp[vsize + j207];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = j208 + 1) {
				fRec87_tmp[j208] = fRec87_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec87[i] = fConst339 * (fConst342 * fRec88[i] + fConst343 * fRec88[i - 1] + fConst342 * fRec88[i - 2]) - fConst344 * (fConst345 * fRec87[i - 2] + fConst346 * fRec87[i - 1]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = j209 + 1) {
				fRec87_perm[j209] = fRec87_tmp[vsize + j209];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec47[i] = fConst344 * (fConst347 * fRec87[i] + fConst348 * fRec87[i - 1] + fConst347 * fRec87[i - 2]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = j218 + 1) {
				fRec96_tmp[j218] = fRec96_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec96[i] = fZec47[i] - fConst371 * (fConst372 * fRec96[i - 2] + fConst373 * fRec96[i - 1]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = j219 + 1) {
				fRec96_perm[j219] = fRec96_tmp[vsize + j219];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = j220 + 1) {
				fRec95_tmp[j220] = fRec95_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec95[i] = fConst371 * (fConst375 * fRec96[i] + fConst376 * fRec96[i - 1] + fConst375 * fRec96[i - 2]) - fConst377 * (fConst378 * fRec95[i - 2] + fConst379 * fRec95[i - 1]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = j221 + 1) {
				fRec95_perm[j221] = fRec95_tmp[vsize + j221];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = j222 + 1) {
				fRec94_tmp[j222] = fRec94_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec94[i] = fConst377 * (fConst380 * fRec95[i] + fConst381 * fRec95[i - 1] + fConst380 * fRec95[i - 2]) - fConst382 * (fConst383 * fRec94[i - 2] + fConst384 * fRec94[i - 1]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = j223 + 1) {
				fRec94_perm[j223] = fRec94_tmp[vsize + j223];
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec48[i] = fConst382 * (fConst385 * fRec94[i] + fConst386 * fRec94[i - 1] + fConst385 * fRec94[i - 2]);
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = j232 + 1) {
				fRec103_tmp[j232] = fRec103_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec103[i] = fZec48[i] - fConst409 * (fConst410 * fRec103[i - 2] + fConst411 * fRec103[i - 1]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = j233 + 1) {
				fRec103_perm[j233] = fRec103_tmp[vsize + j233];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = j234 + 1) {
				fRec102_tmp[j234] = fRec102_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec102[i] = fConst409 * (fConst413 * fRec103[i] + fConst414 * fRec103[i - 1] + fConst413 * fRec103[i - 2]) - fConst415 * (fConst416 * fRec102[i - 2] + fConst417 * fRec102[i - 1]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = j235 + 1) {
				fRec102_perm[j235] = fRec102_tmp[vsize + j235];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = j236 + 1) {
				fRec101_tmp[j236] = fRec101_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec101[i] = fConst415 * (fConst418 * fRec102[i] + fConst419 * fRec102[i - 1] + fConst418 * fRec102[i - 2]) - fConst420 * (fConst421 * fRec101[i - 2] + fConst422 * fRec101[i - 1]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = j237 + 1) {
				fRec101_perm[j237] = fRec101_tmp[vsize + j237];
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec49[i] = fConst420 * (fConst423 * fRec101[i] + fConst424 * fRec101[i - 1] + fConst423 * fRec101[i - 2]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = j246 + 1) {
				fRec110_tmp[j246] = fRec110_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec110[i] = fZec49[i] - fConst447 * (fConst448 * fRec110[i - 2] + fConst449 * fRec110[i - 1]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = j247 + 1) {
				fRec110_perm[j247] = fRec110_tmp[vsize + j247];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = j248 + 1) {
				fRec109_tmp[j248] = fRec109_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec109[i] = fConst447 * (fConst451 * fRec110[i] + fConst452 * fRec110[i - 1] + fConst451 * fRec110[i - 2]) - fConst453 * (fConst454 * fRec109[i - 2] + fConst455 * fRec109[i - 1]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = j249 + 1) {
				fRec109_perm[j249] = fRec109_tmp[vsize + j249];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = j250 + 1) {
				fRec108_tmp[j250] = fRec108_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec108[i] = fConst453 * (fConst456 * fRec109[i] + fConst457 * fRec109[i - 1] + fConst456 * fRec109[i - 2]) - fConst458 * (fConst459 * fRec108[i - 2] + fConst460 * fRec108[i - 1]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = j251 + 1) {
				fRec108_perm[j251] = fRec108_tmp[vsize + j251];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec50[i] = fConst458 * (fConst461 * fRec108[i] + fConst462 * fRec108[i - 1] + fConst461 * fRec108[i - 2]);
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = j260 + 1) {
				fRec117_tmp[j260] = fRec117_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec117[i] = fZec50[i] - fConst485 * (fConst486 * fRec117[i - 2] + fConst487 * fRec117[i - 1]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = j261 + 1) {
				fRec117_perm[j261] = fRec117_tmp[vsize + j261];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = j262 + 1) {
				fRec116_tmp[j262] = fRec116_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec116[i] = fConst485 * (fConst489 * fRec117[i] + fConst490 * fRec117[i - 1] + fConst489 * fRec117[i - 2]) - fConst491 * (fConst492 * fRec116[i - 2] + fConst493 * fRec116[i - 1]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = j263 + 1) {
				fRec116_perm[j263] = fRec116_tmp[vsize + j263];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = j264 + 1) {
				fRec115_tmp[j264] = fRec115_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec115[i] = fConst491 * (fConst494 * fRec116[i] + fConst495 * fRec116[i - 1] + fConst494 * fRec116[i - 2]) - fConst496 * (fConst497 * fRec115[i - 2] + fConst498 * fRec115[i - 1]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = j265 + 1) {
				fRec115_perm[j265] = fRec115_tmp[vsize + j265];
			}
			/* Vectorizable loop 123 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec51[i] = fConst496 * (fConst499 * fRec115[i] + fConst500 * fRec115[i - 1] + fConst499 * fRec115[i - 2]);
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = j84 + 1) {
				fRec26_tmp[j84] = fRec26_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec26[i] = fZec38[i] - fConst8 * (fConst9 * fRec26[i - 2] + fConst12 * fRec26[i - 1]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = j85 + 1) {
				fRec26_perm[j85] = fRec26_tmp[vsize + j85];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = j98 + 1) {
				fRec30_tmp[j98] = fRec30_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec30[i] = fZec39[i] - fConst47 * (fConst48 * fRec30[i - 2] + fConst51 * fRec30[i - 1]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = j99 + 1) {
				fRec30_perm[j99] = fRec30_tmp[vsize + j99];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = j112 + 1) {
				fRec37_tmp[j112] = fRec37_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec37[i] = fZec40[i] - fConst85 * (fConst86 * fRec37[i - 2] + fConst89 * fRec37[i - 1]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = j113 + 1) {
				fRec37_perm[j113] = fRec37_tmp[vsize + j113];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = j126 + 1) {
				fRec44_tmp[j126] = fRec44_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec44[i] = fZec41[i] - fConst123 * (fConst124 * fRec44[i - 2] + fConst127 * fRec44[i - 1]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = j127 + 1) {
				fRec44_perm[j127] = fRec44_tmp[vsize + j127];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = j140 + 1) {
				fRec51_tmp[j140] = fRec51_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec51[i] = fZec42[i] - fConst161 * (fConst162 * fRec51[i - 2] + fConst165 * fRec51[i - 1]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = j141 + 1) {
				fRec51_perm[j141] = fRec51_tmp[vsize + j141];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = j154 + 1) {
				fRec58_tmp[j154] = fRec58_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec58[i] = fZec43[i] - fConst199 * (fConst200 * fRec58[i - 2] + fConst203 * fRec58[i - 1]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = j155 + 1) {
				fRec58_perm[j155] = fRec58_tmp[vsize + j155];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = j168 + 1) {
				fRec65_tmp[j168] = fRec65_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec65[i] = fZec44[i] - fConst237 * (fConst238 * fRec65[i - 2] + fConst241 * fRec65[i - 1]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = j169 + 1) {
				fRec65_perm[j169] = fRec65_tmp[vsize + j169];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = j182 + 1) {
				fRec72_tmp[j182] = fRec72_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec72[i] = fZec45[i] - fConst275 * (fConst276 * fRec72[i - 2] + fConst279 * fRec72[i - 1]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = j183 + 1) {
				fRec72_perm[j183] = fRec72_tmp[vsize + j183];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = j196 + 1) {
				fRec79_tmp[j196] = fRec79_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec79[i] = fZec46[i] - fConst313 * (fConst314 * fRec79[i - 2] + fConst317 * fRec79[i - 1]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = j197 + 1) {
				fRec79_perm[j197] = fRec79_tmp[vsize + j197];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = j210 + 1) {
				fRec86_tmp[j210] = fRec86_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec86[i] = fZec47[i] - fConst351 * (fConst352 * fRec86[i - 2] + fConst355 * fRec86[i - 1]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = j211 + 1) {
				fRec86_perm[j211] = fRec86_tmp[vsize + j211];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = j224 + 1) {
				fRec93_tmp[j224] = fRec93_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec93[i] = fZec48[i] - fConst389 * (fConst390 * fRec93[i - 2] + fConst393 * fRec93[i - 1]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = j225 + 1) {
				fRec93_perm[j225] = fRec93_tmp[vsize + j225];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = j238 + 1) {
				fRec100_tmp[j238] = fRec100_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec100[i] = fZec49[i] - fConst427 * (fConst428 * fRec100[i - 2] + fConst431 * fRec100[i - 1]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = j239 + 1) {
				fRec100_perm[j239] = fRec100_tmp[vsize + j239];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = j252 + 1) {
				fRec107_tmp[j252] = fRec107_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec107[i] = fZec50[i] - fConst465 * (fConst466 * fRec107[i - 2] + fConst469 * fRec107[i - 1]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = j253 + 1) {
				fRec107_perm[j253] = fRec107_tmp[vsize + j253];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = j266 + 1) {
				fRec114_tmp[j266] = fRec114_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec114[i] = fZec51[i] - fConst503 * (fConst504 * fRec114[i - 2] + fConst507 * fRec114[i - 1]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = j267 + 1) {
				fRec114_perm[j267] = fRec114_tmp[vsize + j267];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = j274 + 1) {
				fRec121_tmp[j274] = fRec121_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec121[i] = fZec51[i] - fConst523 * (fConst524 * fRec121[i - 2] + fConst525 * fRec121[i - 1]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = j275 + 1) {
				fRec121_perm[j275] = fRec121_tmp[vsize + j275];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = j86 + 1) {
				fRec25_tmp[j86] = fRec25_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec25[i] = fConst8 * (fConst14 * fRec26[i] + fConst15 * fRec26[i - 1] + fConst14 * fRec26[i - 2]) - fConst16 * (fConst17 * fRec25[i - 2] + fConst18 * fRec25[i - 1]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = j87 + 1) {
				fRec25_perm[j87] = fRec25_tmp[vsize + j87];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = j100 + 1) {
				fRec29_tmp[j100] = fRec29_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec29[i] = fConst47 * (fConst53 * fRec30[i] + fConst54 * fRec30[i - 1] + fConst53 * fRec30[i - 2]) - fConst55 * (fConst56 * fRec29[i - 2] + fConst57 * fRec29[i - 1]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = j101 + 1) {
				fRec29_perm[j101] = fRec29_tmp[vsize + j101];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = j114 + 1) {
				fRec36_tmp[j114] = fRec36_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec36[i] = fConst85 * (fConst91 * fRec37[i] + fConst92 * fRec37[i - 1] + fConst91 * fRec37[i - 2]) - fConst93 * (fConst94 * fRec36[i - 2] + fConst95 * fRec36[i - 1]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = j115 + 1) {
				fRec36_perm[j115] = fRec36_tmp[vsize + j115];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = j128 + 1) {
				fRec43_tmp[j128] = fRec43_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec43[i] = fConst123 * (fConst129 * fRec44[i] + fConst130 * fRec44[i - 1] + fConst129 * fRec44[i - 2]) - fConst131 * (fConst132 * fRec43[i - 2] + fConst133 * fRec43[i - 1]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = j129 + 1) {
				fRec43_perm[j129] = fRec43_tmp[vsize + j129];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = j142 + 1) {
				fRec50_tmp[j142] = fRec50_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec50[i] = fConst161 * (fConst167 * fRec51[i] + fConst168 * fRec51[i - 1] + fConst167 * fRec51[i - 2]) - fConst169 * (fConst170 * fRec50[i - 2] + fConst171 * fRec50[i - 1]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = j143 + 1) {
				fRec50_perm[j143] = fRec50_tmp[vsize + j143];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = j156 + 1) {
				fRec57_tmp[j156] = fRec57_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec57[i] = fConst199 * (fConst205 * fRec58[i] + fConst206 * fRec58[i - 1] + fConst205 * fRec58[i - 2]) - fConst207 * (fConst208 * fRec57[i - 2] + fConst209 * fRec57[i - 1]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = j157 + 1) {
				fRec57_perm[j157] = fRec57_tmp[vsize + j157];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = j170 + 1) {
				fRec64_tmp[j170] = fRec64_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec64[i] = fConst237 * (fConst243 * fRec65[i] + fConst244 * fRec65[i - 1] + fConst243 * fRec65[i - 2]) - fConst245 * (fConst246 * fRec64[i - 2] + fConst247 * fRec64[i - 1]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = j171 + 1) {
				fRec64_perm[j171] = fRec64_tmp[vsize + j171];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = j184 + 1) {
				fRec71_tmp[j184] = fRec71_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec71[i] = fConst275 * (fConst281 * fRec72[i] + fConst282 * fRec72[i - 1] + fConst281 * fRec72[i - 2]) - fConst283 * (fConst284 * fRec71[i - 2] + fConst285 * fRec71[i - 1]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = j185 + 1) {
				fRec71_perm[j185] = fRec71_tmp[vsize + j185];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = j198 + 1) {
				fRec78_tmp[j198] = fRec78_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec78[i] = fConst313 * (fConst319 * fRec79[i] + fConst320 * fRec79[i - 1] + fConst319 * fRec79[i - 2]) - fConst321 * (fConst322 * fRec78[i - 2] + fConst323 * fRec78[i - 1]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = j199 + 1) {
				fRec78_perm[j199] = fRec78_tmp[vsize + j199];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = j212 + 1) {
				fRec85_tmp[j212] = fRec85_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec85[i] = fConst351 * (fConst357 * fRec86[i] + fConst358 * fRec86[i - 1] + fConst357 * fRec86[i - 2]) - fConst359 * (fConst360 * fRec85[i - 2] + fConst361 * fRec85[i - 1]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = j213 + 1) {
				fRec85_perm[j213] = fRec85_tmp[vsize + j213];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = j226 + 1) {
				fRec92_tmp[j226] = fRec92_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec92[i] = fConst389 * (fConst395 * fRec93[i] + fConst396 * fRec93[i - 1] + fConst395 * fRec93[i - 2]) - fConst397 * (fConst398 * fRec92[i - 2] + fConst399 * fRec92[i - 1]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = j227 + 1) {
				fRec92_perm[j227] = fRec92_tmp[vsize + j227];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = j240 + 1) {
				fRec99_tmp[j240] = fRec99_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec99[i] = fConst427 * (fConst433 * fRec100[i] + fConst434 * fRec100[i - 1] + fConst433 * fRec100[i - 2]) - fConst435 * (fConst436 * fRec99[i - 2] + fConst437 * fRec99[i - 1]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = j241 + 1) {
				fRec99_perm[j241] = fRec99_tmp[vsize + j241];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = j254 + 1) {
				fRec106_tmp[j254] = fRec106_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec106[i] = fConst465 * (fConst471 * fRec107[i] + fConst472 * fRec107[i - 1] + fConst471 * fRec107[i - 2]) - fConst473 * (fConst474 * fRec106[i - 2] + fConst475 * fRec106[i - 1]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = j255 + 1) {
				fRec106_perm[j255] = fRec106_tmp[vsize + j255];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = j268 + 1) {
				fRec113_tmp[j268] = fRec113_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec113[i] = fConst503 * (fConst509 * fRec114[i] + fConst510 * fRec114[i - 1] + fConst509 * fRec114[i - 2]) - fConst511 * (fConst512 * fRec113[i - 2] + fConst513 * fRec113[i - 1]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = j269 + 1) {
				fRec113_perm[j269] = fRec113_tmp[vsize + j269];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = j276 + 1) {
				fRec120_tmp[j276] = fRec120_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec120[i] = fConst523 * (fConst527 * fRec121[i] + fConst528 * fRec121[i - 1] + fConst527 * fRec121[i - 2]) - fConst529 * (fConst530 * fRec120[i - 2] + fConst531 * fRec120[i - 1]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = j277 + 1) {
				fRec120_perm[j277] = fRec120_tmp[vsize + j277];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = j88 + 1) {
				fRec24_tmp[j88] = fRec24_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec24[i] = fConst16 * (fConst20 * fRec25[i] + fConst21 * fRec25[i - 1] + fConst20 * fRec25[i - 2]) - fConst22 * (fConst23 * fRec24[i - 2] + fConst24 * fRec24[i - 1]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = j89 + 1) {
				fRec24_perm[j89] = fRec24_tmp[vsize + j89];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = j102 + 1) {
				fRec28_tmp[j102] = fRec28_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec28[i] = fConst55 * (fConst59 * fRec29[i] + fConst60 * fRec29[i - 1] + fConst59 * fRec29[i - 2]) - fConst61 * (fConst62 * fRec28[i - 2] + fConst63 * fRec28[i - 1]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = j103 + 1) {
				fRec28_perm[j103] = fRec28_tmp[vsize + j103];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = j116 + 1) {
				fRec35_tmp[j116] = fRec35_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec35[i] = fConst93 * (fConst97 * fRec36[i] + fConst98 * fRec36[i - 1] + fConst97 * fRec36[i - 2]) - fConst99 * (fConst100 * fRec35[i - 2] + fConst101 * fRec35[i - 1]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = j117 + 1) {
				fRec35_perm[j117] = fRec35_tmp[vsize + j117];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = j130 + 1) {
				fRec42_tmp[j130] = fRec42_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec42[i] = fConst131 * (fConst135 * fRec43[i] + fConst136 * fRec43[i - 1] + fConst135 * fRec43[i - 2]) - fConst137 * (fConst138 * fRec42[i - 2] + fConst139 * fRec42[i - 1]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = j131 + 1) {
				fRec42_perm[j131] = fRec42_tmp[vsize + j131];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = j144 + 1) {
				fRec49_tmp[j144] = fRec49_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec49[i] = fConst169 * (fConst173 * fRec50[i] + fConst174 * fRec50[i - 1] + fConst173 * fRec50[i - 2]) - fConst175 * (fConst176 * fRec49[i - 2] + fConst177 * fRec49[i - 1]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = j145 + 1) {
				fRec49_perm[j145] = fRec49_tmp[vsize + j145];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = j158 + 1) {
				fRec56_tmp[j158] = fRec56_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec56[i] = fConst207 * (fConst211 * fRec57[i] + fConst212 * fRec57[i - 1] + fConst211 * fRec57[i - 2]) - fConst213 * (fConst214 * fRec56[i - 2] + fConst215 * fRec56[i - 1]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = j159 + 1) {
				fRec56_perm[j159] = fRec56_tmp[vsize + j159];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = j172 + 1) {
				fRec63_tmp[j172] = fRec63_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec63[i] = fConst245 * (fConst249 * fRec64[i] + fConst250 * fRec64[i - 1] + fConst249 * fRec64[i - 2]) - fConst251 * (fConst252 * fRec63[i - 2] + fConst253 * fRec63[i - 1]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = j173 + 1) {
				fRec63_perm[j173] = fRec63_tmp[vsize + j173];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = j186 + 1) {
				fRec70_tmp[j186] = fRec70_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec70[i] = fConst283 * (fConst287 * fRec71[i] + fConst288 * fRec71[i - 1] + fConst287 * fRec71[i - 2]) - fConst289 * (fConst290 * fRec70[i - 2] + fConst291 * fRec70[i - 1]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = j187 + 1) {
				fRec70_perm[j187] = fRec70_tmp[vsize + j187];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = j200 + 1) {
				fRec77_tmp[j200] = fRec77_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec77[i] = fConst321 * (fConst325 * fRec78[i] + fConst326 * fRec78[i - 1] + fConst325 * fRec78[i - 2]) - fConst327 * (fConst328 * fRec77[i - 2] + fConst329 * fRec77[i - 1]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = j201 + 1) {
				fRec77_perm[j201] = fRec77_tmp[vsize + j201];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = j214 + 1) {
				fRec84_tmp[j214] = fRec84_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec84[i] = fConst359 * (fConst363 * fRec85[i] + fConst364 * fRec85[i - 1] + fConst363 * fRec85[i - 2]) - fConst365 * (fConst366 * fRec84[i - 2] + fConst367 * fRec84[i - 1]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = j215 + 1) {
				fRec84_perm[j215] = fRec84_tmp[vsize + j215];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = j228 + 1) {
				fRec91_tmp[j228] = fRec91_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec91[i] = fConst397 * (fConst401 * fRec92[i] + fConst402 * fRec92[i - 1] + fConst401 * fRec92[i - 2]) - fConst403 * (fConst404 * fRec91[i - 2] + fConst405 * fRec91[i - 1]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = j229 + 1) {
				fRec91_perm[j229] = fRec91_tmp[vsize + j229];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = j242 + 1) {
				fRec98_tmp[j242] = fRec98_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec98[i] = fConst435 * (fConst439 * fRec99[i] + fConst440 * fRec99[i - 1] + fConst439 * fRec99[i - 2]) - fConst441 * (fConst442 * fRec98[i - 2] + fConst443 * fRec98[i - 1]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = j243 + 1) {
				fRec98_perm[j243] = fRec98_tmp[vsize + j243];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = j256 + 1) {
				fRec105_tmp[j256] = fRec105_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec105[i] = fConst473 * (fConst477 * fRec106[i] + fConst478 * fRec106[i - 1] + fConst477 * fRec106[i - 2]) - fConst479 * (fConst480 * fRec105[i - 2] + fConst481 * fRec105[i - 1]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = j257 + 1) {
				fRec105_perm[j257] = fRec105_tmp[vsize + j257];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = j270 + 1) {
				fRec112_tmp[j270] = fRec112_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec112[i] = fConst511 * (fConst515 * fRec113[i] + fConst516 * fRec113[i - 1] + fConst515 * fRec113[i - 2]) - fConst517 * (fConst518 * fRec112[i - 2] + fConst519 * fRec112[i - 1]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = j271 + 1) {
				fRec112_perm[j271] = fRec112_tmp[vsize + j271];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = j278 + 1) {
				fRec119_tmp[j278] = fRec119_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec119[i] = fConst529 * (fConst532 * fRec120[i] + fConst533 * fRec120[i - 1] + fConst532 * fRec120[i - 2]) - fConst534 * (fConst535 * fRec119[i - 2] + fConst536 * fRec119[i - 1]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = j279 + 1) {
				fRec119_perm[j279] = fRec119_tmp[vsize + j279];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = j90 + 1) {
				fRec23_tmp[j90] = fRec23_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec23[i] = fRec23[i - 1] * fSlow34 + std::fabs(fConst22 * (fConst27 * fRec24[i] + fConst28 * fRec24[i - 1] + fConst27 * fRec24[i - 2])) * fSlow35;
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = j91 + 1) {
				fRec23_perm[j91] = fRec23_tmp[vsize + j91];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = j104 + 1) {
				fRec27_tmp[j104] = fRec27_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec27[i] = fSlow34 * fRec27[i - 1] + fSlow35 * std::fabs(fConst61 * (fConst65 * fRec28[i] + fConst66 * fRec28[i - 1] + fConst65 * fRec28[i - 2]));
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = j105 + 1) {
				fRec27_perm[j105] = fRec27_tmp[vsize + j105];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = j118 + 1) {
				fRec34_tmp[j118] = fRec34_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec34[i] = fSlow34 * fRec34[i - 1] + fSlow35 * std::fabs(fConst99 * (fConst103 * fRec35[i] + fConst104 * fRec35[i - 1] + fConst103 * fRec35[i - 2]));
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = j119 + 1) {
				fRec34_perm[j119] = fRec34_tmp[vsize + j119];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = j132 + 1) {
				fRec41_tmp[j132] = fRec41_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec41[i] = fSlow34 * fRec41[i - 1] + fSlow35 * std::fabs(fConst137 * (fConst141 * fRec42[i] + fConst142 * fRec42[i - 1] + fConst141 * fRec42[i - 2]));
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = j133 + 1) {
				fRec41_perm[j133] = fRec41_tmp[vsize + j133];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = j146 + 1) {
				fRec48_tmp[j146] = fRec48_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec48[i] = fSlow34 * fRec48[i - 1] + fSlow35 * std::fabs(fConst175 * (fConst179 * fRec49[i] + fConst180 * fRec49[i - 1] + fConst179 * fRec49[i - 2]));
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = j147 + 1) {
				fRec48_perm[j147] = fRec48_tmp[vsize + j147];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = j160 + 1) {
				fRec55_tmp[j160] = fRec55_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec55[i] = fSlow34 * fRec55[i - 1] + fSlow35 * std::fabs(fConst213 * (fConst217 * fRec56[i] + fConst218 * fRec56[i - 1] + fConst217 * fRec56[i - 2]));
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = j161 + 1) {
				fRec55_perm[j161] = fRec55_tmp[vsize + j161];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = j174 + 1) {
				fRec62_tmp[j174] = fRec62_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec62[i] = fSlow34 * fRec62[i - 1] + fSlow35 * std::fabs(fConst251 * (fConst255 * fRec63[i] + fConst256 * fRec63[i - 1] + fConst255 * fRec63[i - 2]));
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = j175 + 1) {
				fRec62_perm[j175] = fRec62_tmp[vsize + j175];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = j188 + 1) {
				fRec69_tmp[j188] = fRec69_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec69[i] = fSlow34 * fRec69[i - 1] + fSlow35 * std::fabs(fConst289 * (fConst293 * fRec70[i] + fConst294 * fRec70[i - 1] + fConst293 * fRec70[i - 2]));
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = j189 + 1) {
				fRec69_perm[j189] = fRec69_tmp[vsize + j189];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = j202 + 1) {
				fRec76_tmp[j202] = fRec76_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec76[i] = fSlow34 * fRec76[i - 1] + fSlow35 * std::fabs(fConst327 * (fConst331 * fRec77[i] + fConst332 * fRec77[i - 1] + fConst331 * fRec77[i - 2]));
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = j203 + 1) {
				fRec76_perm[j203] = fRec76_tmp[vsize + j203];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = j216 + 1) {
				fRec83_tmp[j216] = fRec83_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec83[i] = fSlow34 * fRec83[i - 1] + fSlow35 * std::fabs(fConst365 * (fConst369 * fRec84[i] + fConst370 * fRec84[i - 1] + fConst369 * fRec84[i - 2]));
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = j217 + 1) {
				fRec83_perm[j217] = fRec83_tmp[vsize + j217];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = j230 + 1) {
				fRec90_tmp[j230] = fRec90_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec90[i] = fSlow34 * fRec90[i - 1] + fSlow35 * std::fabs(fConst403 * (fConst407 * fRec91[i] + fConst408 * fRec91[i - 1] + fConst407 * fRec91[i - 2]));
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = j231 + 1) {
				fRec90_perm[j231] = fRec90_tmp[vsize + j231];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = j244 + 1) {
				fRec97_tmp[j244] = fRec97_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec97[i] = fSlow34 * fRec97[i - 1] + fSlow35 * std::fabs(fConst441 * (fConst445 * fRec98[i] + fConst446 * fRec98[i - 1] + fConst445 * fRec98[i - 2]));
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = j245 + 1) {
				fRec97_perm[j245] = fRec97_tmp[vsize + j245];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = j258 + 1) {
				fRec104_tmp[j258] = fRec104_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec104[i] = fSlow34 * fRec104[i - 1] + fSlow35 * std::fabs(fConst479 * (fConst483 * fRec105[i] + fConst484 * fRec105[i - 1] + fConst483 * fRec105[i - 2]));
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = j259 + 1) {
				fRec104_perm[j259] = fRec104_tmp[vsize + j259];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = j272 + 1) {
				fRec111_tmp[j272] = fRec111_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec111[i] = fSlow34 * fRec111[i - 1] + fSlow35 * std::fabs(fConst517 * (fConst521 * fRec112[i] + fConst522 * fRec112[i - 1] + fConst521 * fRec112[i - 2]));
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = j273 + 1) {
				fRec111_perm[j273] = fRec111_tmp[vsize + j273];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = j280 + 1) {
				fRec118_tmp[j280] = fRec118_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec118[i] = fSlow34 * fRec118[i - 1] + fSlow35 * std::fabs(fConst534 * (fConst537 * fRec119[i] + fConst538 * fRec119[i - 1] + fConst537 * fRec119[i - 2]));
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = j281 + 1) {
				fRec118_perm[j281] = fRec118_tmp[vsize + j281];
			}
			/* Vectorizable loop 184 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec23[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec27[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec34[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec41[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec48[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec55[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec62[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec69[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec76[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec83[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec90[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec97[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec104[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec111[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow36 + 2e+01 * std::log10(fRec118[i]));
				fZec52[i] = fZec38[i];
			}
			/* Vectorizable loop 185 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec52[i]);
			}
			/* Vectorizable loop 186 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec52[i]);
			}
		}
	}

};

#endif
