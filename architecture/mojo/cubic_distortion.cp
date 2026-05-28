/* ------------------------------------------------------------
name: "cubic_distortion"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -a ../_bench/arch/cpp/inspect.cpp -lang cpp -fpga-mem-th 4 -ct 1 -cn CubicDistortion -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __CubicDistortion_H__
#define  __CubicDistortion_H__

// architecture/inspect.cpp

#include "common.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS CubicDistortion
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

static double CubicDistortion_faustpower2_f(double value) {
	return value * value;
}

class CubicDistortion : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider2;
	double fRec5[2];
	FAUSTFLOAT fHslider3;
	double fRec6[2];
	double fConst14;
	FAUSTFLOAT fHslider4;
	double fConst15;
	FAUSTFLOAT fHslider5;
	double fRec9[2];
	double fRec7[2];
	double fRec8[2];
	FAUSTFLOAT fHslider6;
	double fRec10[2];
	double fVec1[2];
	double fRec4[2];
	double fConst16;
	double fConst17;
	double fConst18;
	double fRec3[3];
	double fConst19;
	double fConst20;
	double fConst21;
	double fRec2[3];
	double fConst22;
	double fConst23;
	double fConst24;
	double fRec1[3];
	double fConst25;
	double fRec0[2];
	FAUSTFLOAT fVbargraph0;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fRec17[3];
	double fConst47;
	double fConst48;
	double fConst49;
	double fRec16[3];
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec15[3];
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec14[3];
	double fConst57;
	double fConst58;
	double fConst59;
	double fRec13[3];
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec12[3];
	double fConst63;
	double fRec11[2];
	FAUSTFLOAT fVbargraph1;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fRec24[3];
	double fConst85;
	double fConst86;
	double fConst87;
	double fRec23[3];
	double fConst88;
	double fConst89;
	double fConst90;
	double fRec22[3];
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fRec21[3];
	double fConst95;
	double fConst96;
	double fConst97;
	double fRec20[3];
	double fConst98;
	double fConst99;
	double fConst100;
	double fRec19[3];
	double fConst101;
	double fRec18[2];
	FAUSTFLOAT fVbargraph2;
	double fConst102;
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fRec31[3];
	double fConst123;
	double fConst124;
	double fConst125;
	double fRec30[3];
	double fConst126;
	double fConst127;
	double fConst128;
	double fRec29[3];
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fRec28[3];
	double fConst133;
	double fConst134;
	double fConst135;
	double fRec27[3];
	double fConst136;
	double fConst137;
	double fConst138;
	double fRec26[3];
	double fConst139;
	double fRec25[2];
	FAUSTFLOAT fVbargraph3;
	double fConst140;
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fConst145;
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fRec38[3];
	double fConst161;
	double fConst162;
	double fConst163;
	double fRec37[3];
	double fConst164;
	double fConst165;
	double fConst166;
	double fRec36[3];
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fRec35[3];
	double fConst171;
	double fConst172;
	double fConst173;
	double fRec34[3];
	double fConst174;
	double fConst175;
	double fConst176;
	double fRec33[3];
	double fConst177;
	double fRec32[2];
	FAUSTFLOAT fVbargraph4;
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fConst197;
	double fConst198;
	double fRec45[3];
	double fConst199;
	double fConst200;
	double fConst201;
	double fRec44[3];
	double fConst202;
	double fConst203;
	double fConst204;
	double fRec43[3];
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fRec42[3];
	double fConst209;
	double fConst210;
	double fConst211;
	double fRec41[3];
	double fConst212;
	double fConst213;
	double fConst214;
	double fRec40[3];
	double fConst215;
	double fRec39[2];
	FAUSTFLOAT fVbargraph5;
	double fConst216;
	double fConst217;
	double fConst218;
	double fConst219;
	double fConst220;
	double fConst221;
	double fConst222;
	double fConst223;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fRec52[3];
	double fConst237;
	double fConst238;
	double fConst239;
	double fRec51[3];
	double fConst240;
	double fConst241;
	double fConst242;
	double fRec50[3];
	double fConst243;
	double fConst244;
	double fConst245;
	double fConst246;
	double fRec49[3];
	double fConst247;
	double fConst248;
	double fConst249;
	double fRec48[3];
	double fConst250;
	double fConst251;
	double fConst252;
	double fRec47[3];
	double fConst253;
	double fRec46[2];
	FAUSTFLOAT fVbargraph6;
	double fConst254;
	double fConst255;
	double fConst256;
	double fConst257;
	double fConst258;
	double fConst259;
	double fConst260;
	double fConst261;
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fConst273;
	double fConst274;
	double fRec59[3];
	double fConst275;
	double fConst276;
	double fConst277;
	double fRec58[3];
	double fConst278;
	double fConst279;
	double fConst280;
	double fRec57[3];
	double fConst281;
	double fConst282;
	double fConst283;
	double fConst284;
	double fRec56[3];
	double fConst285;
	double fConst286;
	double fConst287;
	double fRec55[3];
	double fConst288;
	double fConst289;
	double fConst290;
	double fRec54[3];
	double fConst291;
	double fRec53[2];
	FAUSTFLOAT fVbargraph7;
	double fConst292;
	double fConst293;
	double fConst294;
	double fConst295;
	double fConst296;
	double fConst297;
	double fConst298;
	double fConst299;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst308;
	double fConst309;
	double fConst310;
	double fConst311;
	double fConst312;
	double fRec66[3];
	double fConst313;
	double fConst314;
	double fConst315;
	double fRec65[3];
	double fConst316;
	double fConst317;
	double fConst318;
	double fRec64[3];
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fRec63[3];
	double fConst323;
	double fConst324;
	double fConst325;
	double fRec62[3];
	double fConst326;
	double fConst327;
	double fConst328;
	double fRec61[3];
	double fConst329;
	double fRec60[2];
	FAUSTFLOAT fVbargraph8;
	double fConst330;
	double fConst331;
	double fConst332;
	double fConst333;
	double fConst334;
	double fConst335;
	double fConst336;
	double fConst337;
	double fConst338;
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fRec73[3];
	double fConst351;
	double fConst352;
	double fConst353;
	double fRec72[3];
	double fConst354;
	double fConst355;
	double fConst356;
	double fRec71[3];
	double fConst357;
	double fConst358;
	double fConst359;
	double fConst360;
	double fRec70[3];
	double fConst361;
	double fConst362;
	double fConst363;
	double fRec69[3];
	double fConst364;
	double fConst365;
	double fConst366;
	double fRec68[3];
	double fConst367;
	double fRec67[2];
	FAUSTFLOAT fVbargraph9;
	double fConst368;
	double fConst369;
	double fConst370;
	double fConst371;
	double fConst372;
	double fConst373;
	double fConst374;
	double fConst375;
	double fConst376;
	double fConst377;
	double fConst378;
	double fConst379;
	double fConst380;
	double fConst381;
	double fConst382;
	double fConst383;
	double fConst384;
	double fConst385;
	double fConst386;
	double fConst387;
	double fConst388;
	double fRec80[3];
	double fConst389;
	double fConst390;
	double fConst391;
	double fRec79[3];
	double fConst392;
	double fConst393;
	double fConst394;
	double fRec78[3];
	double fConst395;
	double fConst396;
	double fConst397;
	double fConst398;
	double fRec77[3];
	double fConst399;
	double fConst400;
	double fConst401;
	double fRec76[3];
	double fConst402;
	double fConst403;
	double fConst404;
	double fRec75[3];
	double fConst405;
	double fRec74[2];
	FAUSTFLOAT fVbargraph10;
	double fConst406;
	double fConst407;
	double fConst408;
	double fConst409;
	double fConst410;
	double fConst411;
	double fConst412;
	double fConst413;
	double fConst414;
	double fConst415;
	double fConst416;
	double fConst417;
	double fConst418;
	double fConst419;
	double fConst420;
	double fConst421;
	double fConst422;
	double fConst423;
	double fConst424;
	double fConst425;
	double fConst426;
	double fRec87[3];
	double fConst427;
	double fConst428;
	double fConst429;
	double fRec86[3];
	double fConst430;
	double fConst431;
	double fConst432;
	double fRec85[3];
	double fConst433;
	double fConst434;
	double fConst435;
	double fConst436;
	double fRec84[3];
	double fConst437;
	double fConst438;
	double fConst439;
	double fRec83[3];
	double fConst440;
	double fConst441;
	double fConst442;
	double fRec82[3];
	double fConst443;
	double fRec81[2];
	FAUSTFLOAT fVbargraph11;
	double fConst444;
	double fConst445;
	double fConst446;
	double fConst447;
	double fConst448;
	double fConst449;
	double fConst450;
	double fConst451;
	double fConst452;
	double fConst453;
	double fConst454;
	double fConst455;
	double fConst456;
	double fConst457;
	double fConst458;
	double fConst459;
	double fConst460;
	double fConst461;
	double fConst462;
	double fConst463;
	double fConst464;
	double fRec94[3];
	double fConst465;
	double fConst466;
	double fConst467;
	double fRec93[3];
	double fConst468;
	double fConst469;
	double fConst470;
	double fRec92[3];
	double fConst471;
	double fConst472;
	double fConst473;
	double fConst474;
	double fRec91[3];
	double fConst475;
	double fConst476;
	double fConst477;
	double fRec90[3];
	double fConst478;
	double fConst479;
	double fConst480;
	double fRec89[3];
	double fConst481;
	double fRec88[2];
	FAUSTFLOAT fVbargraph12;
	double fConst482;
	double fConst483;
	double fConst484;
	double fConst485;
	double fConst486;
	double fConst487;
	double fConst488;
	double fConst489;
	double fConst490;
	double fConst491;
	double fConst492;
	double fConst493;
	double fConst494;
	double fConst495;
	double fConst496;
	double fConst497;
	double fConst498;
	double fConst499;
	double fConst500;
	double fConst501;
	double fConst502;
	double fRec101[3];
	double fConst503;
	double fConst504;
	double fConst505;
	double fRec100[3];
	double fConst506;
	double fConst507;
	double fConst508;
	double fRec99[3];
	double fConst509;
	double fConst510;
	double fConst511;
	double fConst512;
	double fRec98[3];
	double fConst513;
	double fConst514;
	double fConst515;
	double fRec97[3];
	double fConst516;
	double fConst517;
	double fConst518;
	double fRec96[3];
	double fConst519;
	double fRec95[2];
	FAUSTFLOAT fVbargraph13;
	double fConst520;
	double fConst521;
	double fConst522;
	double fConst523;
	double fConst524;
	double fConst525;
	double fConst526;
	double fConst527;
	double fConst528;
	double fRec105[3];
	double fConst529;
	double fConst530;
	double fConst531;
	double fRec104[3];
	double fConst532;
	double fConst533;
	double fConst534;
	double fRec103[3];
	double fConst535;
	double fRec102[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	CubicDistortion() {
	}
	
	CubicDistortion(const CubicDistortion&) = default;
	
	virtual ~CubicDistortion() = default;
	
	CubicDistortion& operator=(const CubicDistortion&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a ../_bench/arch/cpp/inspect.cpp -lang cpp -fpga-mem-th 4 -ct 1 -cn CubicDistortion -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0");
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
		m->declare("filename", "cubic_distortion.dsp");
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
		m->declare("name", "cubic_distortion");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
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
		fConst1 = 1e+03 / fConst0;
		fConst2 = std::tan(50265.48245743669 / fConst0);
		fConst3 = 1.0 / fConst2;
		fConst4 = 1.0 / ((fConst3 + 0.157482159302087) / fConst2 + 0.9351401670315425);
		fConst5 = CubicDistortion_faustpower2_f(fConst2);
		fConst6 = 50.063807016150385 / fConst5;
		fConst7 = fConst6 + 0.9351401670315425;
		fConst8 = 1.0 / ((fConst3 + 0.7431304601070396) / fConst2 + 1.450071084655647);
		fConst9 = 11.052052171507189 / fConst5;
		fConst10 = fConst9 + 1.450071084655647;
		fConst11 = 1.0 / ((fConst3 + 3.1897274020965583) / fConst2 + 4.076781969643807);
		fConst12 = 0.0017661728399818856 / fConst5;
		fConst13 = fConst12 + 0.00040767818495825777;
		fConst14 = 6.283185307179586 / fConst0;
		fConst15 = 1.0 / fConst0;
		fConst16 = (fConst3 + -3.1897274020965583) / fConst2 + 4.076781969643807;
		fConst17 = 1.0 / fConst5;
		fConst18 = 2.0 * (4.076781969643807 - fConst17);
		fConst19 = 2.0 * (0.00040767818495825777 - fConst12);
		fConst20 = (fConst3 + -0.7431304601070396) / fConst2 + 1.450071084655647;
		fConst21 = 2.0 * (1.450071084655647 - fConst17);
		fConst22 = 2.0 * (1.450071084655647 - fConst9);
		fConst23 = (fConst3 + -0.157482159302087) / fConst2 + 0.9351401670315425;
		fConst24 = 2.0 * (0.9351401670315425 - fConst17);
		fConst25 = 2.0 * (0.9351401670315425 - fConst6);
		fConst26 = std::tan(31665.269715622984 / fConst0);
		fConst27 = 1.0 / fConst26;
		fConst28 = 1.0 / ((fConst27 + 0.157482159302087) / fConst26 + 0.9351401670315425);
		fConst29 = CubicDistortion_faustpower2_f(fConst26);
		fConst30 = 50.063807016150385 / fConst29;
		fConst31 = fConst30 + 0.9351401670315425;
		fConst32 = 1.0 / ((fConst27 + 0.7431304601070396) / fConst26 + 1.450071084655647);
		fConst33 = 11.052052171507189 / fConst29;
		fConst34 = fConst33 + 1.450071084655647;
		fConst35 = 1.0 / ((fConst27 + 3.1897274020965583) / fConst26 + 4.076781969643807);
		fConst36 = 0.0017661728399818856 / fConst29;
		fConst37 = fConst36 + 0.00040767818495825777;
		fConst38 = 1.0 / ((fConst3 + 0.168404871113589) / fConst2 + 1.069358407707312);
		fConst39 = fConst17 + 53.53615295455673;
		fConst40 = 1.0 / ((fConst3 + 0.512478641889141) / fConst2 + 0.689621364484675);
		fConst41 = fConst17 + 7.621731298870603;
		fConst42 = 1.0 / ((fConst3 + 0.782413046821645) / fConst2 + 0.24529150870616);
		fConst43 = 9.9999997055e-05 / fConst5;
		fConst44 = fConst43 + 0.000433227200555;
		fConst45 = (fConst3 + -0.782413046821645) / fConst2 + 0.24529150870616;
		fConst46 = 2.0 * (0.24529150870616 - fConst17);
		fConst47 = 2.0 * (0.000433227200555 - fConst43);
		fConst48 = (fConst3 + -0.512478641889141) / fConst2 + 0.689621364484675;
		fConst49 = 2.0 * (0.689621364484675 - fConst17);
		fConst50 = 2.0 * (7.621731298870603 - fConst17);
		fConst51 = (fConst3 + -0.168404871113589) / fConst2 + 1.069358407707312;
		fConst52 = 2.0 * (1.069358407707312 - fConst17);
		fConst53 = 2.0 * (53.53615295455673 - fConst17);
		fConst54 = (fConst27 + -3.1897274020965583) / fConst26 + 4.076781969643807;
		fConst55 = 1.0 / fConst29;
		fConst56 = 2.0 * (4.076781969643807 - fConst55);
		fConst57 = 2.0 * (0.00040767818495825777 - fConst36);
		fConst58 = (fConst27 + -0.7431304601070396) / fConst26 + 1.450071084655647;
		fConst59 = 2.0 * (1.450071084655647 - fConst55);
		fConst60 = 2.0 * (1.450071084655647 - fConst33);
		fConst61 = (fConst27 + -0.157482159302087) / fConst26 + 0.9351401670315425;
		fConst62 = 2.0 * (0.9351401670315425 - fConst55);
		fConst63 = 2.0 * (0.9351401670315425 - fConst30);
		fConst64 = std::tan(19947.869932656024 / fConst0);
		fConst65 = 1.0 / fConst64;
		fConst66 = 1.0 / ((fConst65 + 0.157482159302087) / fConst64 + 0.9351401670315425);
		fConst67 = CubicDistortion_faustpower2_f(fConst64);
		fConst68 = 50.063807016150385 / fConst67;
		fConst69 = fConst68 + 0.9351401670315425;
		fConst70 = 1.0 / ((fConst65 + 0.7431304601070396) / fConst64 + 1.450071084655647);
		fConst71 = 11.052052171507189 / fConst67;
		fConst72 = fConst71 + 1.450071084655647;
		fConst73 = 1.0 / ((fConst65 + 3.1897274020965583) / fConst64 + 4.076781969643807);
		fConst74 = 0.0017661728399818856 / fConst67;
		fConst75 = fConst74 + 0.00040767818495825777;
		fConst76 = 1.0 / ((fConst27 + 0.168404871113589) / fConst26 + 1.069358407707312);
		fConst77 = fConst55 + 53.53615295455673;
		fConst78 = 1.0 / ((fConst27 + 0.512478641889141) / fConst26 + 0.689621364484675);
		fConst79 = fConst55 + 7.621731298870603;
		fConst80 = 1.0 / ((fConst27 + 0.782413046821645) / fConst26 + 0.24529150870616);
		fConst81 = 9.9999997055e-05 / fConst29;
		fConst82 = fConst81 + 0.000433227200555;
		fConst83 = (fConst27 + -0.782413046821645) / fConst26 + 0.24529150870616;
		fConst84 = 2.0 * (0.24529150870616 - fConst55);
		fConst85 = 2.0 * (0.000433227200555 - fConst81);
		fConst86 = (fConst27 + -0.512478641889141) / fConst26 + 0.689621364484675;
		fConst87 = 2.0 * (0.689621364484675 - fConst55);
		fConst88 = 2.0 * (7.621731298870603 - fConst55);
		fConst89 = (fConst27 + -0.168404871113589) / fConst26 + 1.069358407707312;
		fConst90 = 2.0 * (1.069358407707312 - fConst55);
		fConst91 = 2.0 * (53.53615295455673 - fConst55);
		fConst92 = (fConst65 + -3.1897274020965583) / fConst64 + 4.076781969643807;
		fConst93 = 1.0 / fConst67;
		fConst94 = 2.0 * (4.076781969643807 - fConst93);
		fConst95 = 2.0 * (0.00040767818495825777 - fConst74);
		fConst96 = (fConst65 + -0.7431304601070396) / fConst64 + 1.450071084655647;
		fConst97 = 2.0 * (1.450071084655647 - fConst93);
		fConst98 = 2.0 * (1.450071084655647 - fConst71);
		fConst99 = (fConst65 + -0.157482159302087) / fConst64 + 0.9351401670315425;
		fConst100 = 2.0 * (0.9351401670315425 - fConst93);
		fConst101 = 2.0 * (0.9351401670315425 - fConst68);
		fConst102 = std::tan(12566.370614359172 / fConst0);
		fConst103 = 1.0 / fConst102;
		fConst104 = 1.0 / ((fConst103 + 0.157482159302087) / fConst102 + 0.9351401670315425);
		fConst105 = CubicDistortion_faustpower2_f(fConst102);
		fConst106 = 50.063807016150385 / fConst105;
		fConst107 = fConst106 + 0.9351401670315425;
		fConst108 = 1.0 / ((fConst103 + 0.7431304601070396) / fConst102 + 1.450071084655647);
		fConst109 = 11.052052171507189 / fConst105;
		fConst110 = fConst109 + 1.450071084655647;
		fConst111 = 1.0 / ((fConst103 + 3.1897274020965583) / fConst102 + 4.076781969643807);
		fConst112 = 0.0017661728399818856 / fConst105;
		fConst113 = fConst112 + 0.00040767818495825777;
		fConst114 = 1.0 / ((fConst65 + 0.168404871113589) / fConst64 + 1.069358407707312);
		fConst115 = fConst93 + 53.53615295455673;
		fConst116 = 1.0 / ((fConst65 + 0.512478641889141) / fConst64 + 0.689621364484675);
		fConst117 = fConst93 + 7.621731298870603;
		fConst118 = 1.0 / ((fConst65 + 0.782413046821645) / fConst64 + 0.24529150870616);
		fConst119 = 9.9999997055e-05 / fConst67;
		fConst120 = fConst119 + 0.000433227200555;
		fConst121 = (fConst65 + -0.782413046821645) / fConst64 + 0.24529150870616;
		fConst122 = 2.0 * (0.24529150870616 - fConst93);
		fConst123 = 2.0 * (0.000433227200555 - fConst119);
		fConst124 = (fConst65 + -0.512478641889141) / fConst64 + 0.689621364484675;
		fConst125 = 2.0 * (0.689621364484675 - fConst93);
		fConst126 = 2.0 * (7.621731298870603 - fConst93);
		fConst127 = (fConst65 + -0.168404871113589) / fConst64 + 1.069358407707312;
		fConst128 = 2.0 * (1.069358407707312 - fConst93);
		fConst129 = 2.0 * (53.53615295455673 - fConst93);
		fConst130 = (fConst103 + -3.1897274020965583) / fConst102 + 4.076781969643807;
		fConst131 = 1.0 / fConst105;
		fConst132 = 2.0 * (4.076781969643807 - fConst131);
		fConst133 = 2.0 * (0.00040767818495825777 - fConst112);
		fConst134 = (fConst103 + -0.7431304601070396) / fConst102 + 1.450071084655647;
		fConst135 = 2.0 * (1.450071084655647 - fConst131);
		fConst136 = 2.0 * (1.450071084655647 - fConst109);
		fConst137 = (fConst103 + -0.157482159302087) / fConst102 + 0.9351401670315425;
		fConst138 = 2.0 * (0.9351401670315425 - fConst131);
		fConst139 = 2.0 * (0.9351401670315425 - fConst106);
		fConst140 = std::tan(7916.317428905746 / fConst0);
		fConst141 = 1.0 / fConst140;
		fConst142 = 1.0 / ((fConst141 + 0.157482159302087) / fConst140 + 0.9351401670315425);
		fConst143 = CubicDistortion_faustpower2_f(fConst140);
		fConst144 = 50.063807016150385 / fConst143;
		fConst145 = fConst144 + 0.9351401670315425;
		fConst146 = 1.0 / ((fConst141 + 0.7431304601070396) / fConst140 + 1.450071084655647);
		fConst147 = 11.052052171507189 / fConst143;
		fConst148 = fConst147 + 1.450071084655647;
		fConst149 = 1.0 / ((fConst141 + 3.1897274020965583) / fConst140 + 4.076781969643807);
		fConst150 = 0.0017661728399818856 / fConst143;
		fConst151 = fConst150 + 0.00040767818495825777;
		fConst152 = 1.0 / ((fConst103 + 0.168404871113589) / fConst102 + 1.069358407707312);
		fConst153 = fConst131 + 53.53615295455673;
		fConst154 = 1.0 / ((fConst103 + 0.512478641889141) / fConst102 + 0.689621364484675);
		fConst155 = fConst131 + 7.621731298870603;
		fConst156 = 1.0 / ((fConst103 + 0.782413046821645) / fConst102 + 0.24529150870616);
		fConst157 = 9.9999997055e-05 / fConst105;
		fConst158 = fConst157 + 0.000433227200555;
		fConst159 = (fConst103 + -0.782413046821645) / fConst102 + 0.24529150870616;
		fConst160 = 2.0 * (0.24529150870616 - fConst131);
		fConst161 = 2.0 * (0.000433227200555 - fConst157);
		fConst162 = (fConst103 + -0.512478641889141) / fConst102 + 0.689621364484675;
		fConst163 = 2.0 * (0.689621364484675 - fConst131);
		fConst164 = 2.0 * (7.621731298870603 - fConst131);
		fConst165 = (fConst103 + -0.168404871113589) / fConst102 + 1.069358407707312;
		fConst166 = 2.0 * (1.069358407707312 - fConst131);
		fConst167 = 2.0 * (53.53615295455673 - fConst131);
		fConst168 = (fConst141 + -3.1897274020965583) / fConst140 + 4.076781969643807;
		fConst169 = 1.0 / fConst143;
		fConst170 = 2.0 * (4.076781969643807 - fConst169);
		fConst171 = 2.0 * (0.00040767818495825777 - fConst150);
		fConst172 = (fConst141 + -0.7431304601070396) / fConst140 + 1.450071084655647;
		fConst173 = 2.0 * (1.450071084655647 - fConst169);
		fConst174 = 2.0 * (1.450071084655647 - fConst147);
		fConst175 = (fConst141 + -0.157482159302087) / fConst140 + 0.9351401670315425;
		fConst176 = 2.0 * (0.9351401670315425 - fConst169);
		fConst177 = 2.0 * (0.9351401670315425 - fConst144);
		fConst178 = std::tan(4986.967483164005 / fConst0);
		fConst179 = 1.0 / fConst178;
		fConst180 = 1.0 / ((fConst179 + 0.157482159302087) / fConst178 + 0.9351401670315425);
		fConst181 = CubicDistortion_faustpower2_f(fConst178);
		fConst182 = 50.063807016150385 / fConst181;
		fConst183 = fConst182 + 0.9351401670315425;
		fConst184 = 1.0 / ((fConst179 + 0.7431304601070396) / fConst178 + 1.450071084655647);
		fConst185 = 11.052052171507189 / fConst181;
		fConst186 = fConst185 + 1.450071084655647;
		fConst187 = 1.0 / ((fConst179 + 3.1897274020965583) / fConst178 + 4.076781969643807);
		fConst188 = 0.0017661728399818856 / fConst181;
		fConst189 = fConst188 + 0.00040767818495825777;
		fConst190 = 1.0 / ((fConst141 + 0.168404871113589) / fConst140 + 1.069358407707312);
		fConst191 = fConst169 + 53.53615295455673;
		fConst192 = 1.0 / ((fConst141 + 0.512478641889141) / fConst140 + 0.689621364484675);
		fConst193 = fConst169 + 7.621731298870603;
		fConst194 = 1.0 / ((fConst141 + 0.782413046821645) / fConst140 + 0.24529150870616);
		fConst195 = 9.9999997055e-05 / fConst143;
		fConst196 = fConst195 + 0.000433227200555;
		fConst197 = (fConst141 + -0.782413046821645) / fConst140 + 0.24529150870616;
		fConst198 = 2.0 * (0.24529150870616 - fConst169);
		fConst199 = 2.0 * (0.000433227200555 - fConst195);
		fConst200 = (fConst141 + -0.512478641889141) / fConst140 + 0.689621364484675;
		fConst201 = 2.0 * (0.689621364484675 - fConst169);
		fConst202 = 2.0 * (7.621731298870603 - fConst169);
		fConst203 = (fConst141 + -0.168404871113589) / fConst140 + 1.069358407707312;
		fConst204 = 2.0 * (1.069358407707312 - fConst169);
		fConst205 = 2.0 * (53.53615295455673 - fConst169);
		fConst206 = (fConst179 + -3.1897274020965583) / fConst178 + 4.076781969643807;
		fConst207 = 1.0 / fConst181;
		fConst208 = 2.0 * (4.076781969643807 - fConst207);
		fConst209 = 2.0 * (0.00040767818495825777 - fConst188);
		fConst210 = (fConst179 + -0.7431304601070396) / fConst178 + 1.450071084655647;
		fConst211 = 2.0 * (1.450071084655647 - fConst207);
		fConst212 = 2.0 * (1.450071084655647 - fConst185);
		fConst213 = (fConst179 + -0.157482159302087) / fConst178 + 0.9351401670315425;
		fConst214 = 2.0 * (0.9351401670315425 - fConst207);
		fConst215 = 2.0 * (0.9351401670315425 - fConst182);
		fConst216 = std::tan(3141.592653589793 / fConst0);
		fConst217 = 1.0 / fConst216;
		fConst218 = 1.0 / ((fConst217 + 0.157482159302087) / fConst216 + 0.9351401670315425);
		fConst219 = CubicDistortion_faustpower2_f(fConst216);
		fConst220 = 50.063807016150385 / fConst219;
		fConst221 = fConst220 + 0.9351401670315425;
		fConst222 = 1.0 / ((fConst217 + 0.7431304601070396) / fConst216 + 1.450071084655647);
		fConst223 = 11.052052171507189 / fConst219;
		fConst224 = fConst223 + 1.450071084655647;
		fConst225 = 1.0 / ((fConst217 + 3.1897274020965583) / fConst216 + 4.076781969643807);
		fConst226 = 0.0017661728399818856 / fConst219;
		fConst227 = fConst226 + 0.00040767818495825777;
		fConst228 = 1.0 / ((fConst179 + 0.168404871113589) / fConst178 + 1.069358407707312);
		fConst229 = fConst207 + 53.53615295455673;
		fConst230 = 1.0 / ((fConst179 + 0.512478641889141) / fConst178 + 0.689621364484675);
		fConst231 = fConst207 + 7.621731298870603;
		fConst232 = 1.0 / ((fConst179 + 0.782413046821645) / fConst178 + 0.24529150870616);
		fConst233 = 9.9999997055e-05 / fConst181;
		fConst234 = fConst233 + 0.000433227200555;
		fConst235 = (fConst179 + -0.782413046821645) / fConst178 + 0.24529150870616;
		fConst236 = 2.0 * (0.24529150870616 - fConst207);
		fConst237 = 2.0 * (0.000433227200555 - fConst233);
		fConst238 = (fConst179 + -0.512478641889141) / fConst178 + 0.689621364484675;
		fConst239 = 2.0 * (0.689621364484675 - fConst207);
		fConst240 = 2.0 * (7.621731298870603 - fConst207);
		fConst241 = (fConst179 + -0.168404871113589) / fConst178 + 1.069358407707312;
		fConst242 = 2.0 * (1.069358407707312 - fConst207);
		fConst243 = 2.0 * (53.53615295455673 - fConst207);
		fConst244 = (fConst217 + -3.1897274020965583) / fConst216 + 4.076781969643807;
		fConst245 = 1.0 / fConst219;
		fConst246 = 2.0 * (4.076781969643807 - fConst245);
		fConst247 = 2.0 * (0.00040767818495825777 - fConst226);
		fConst248 = (fConst217 + -0.7431304601070396) / fConst216 + 1.450071084655647;
		fConst249 = 2.0 * (1.450071084655647 - fConst245);
		fConst250 = 2.0 * (1.450071084655647 - fConst223);
		fConst251 = (fConst217 + -0.157482159302087) / fConst216 + 0.9351401670315425;
		fConst252 = 2.0 * (0.9351401670315425 - fConst245);
		fConst253 = 2.0 * (0.9351401670315425 - fConst220);
		fConst254 = std::tan(1979.079357226436 / fConst0);
		fConst255 = 1.0 / fConst254;
		fConst256 = 1.0 / ((fConst255 + 0.157482159302087) / fConst254 + 0.9351401670315425);
		fConst257 = CubicDistortion_faustpower2_f(fConst254);
		fConst258 = 50.063807016150385 / fConst257;
		fConst259 = fConst258 + 0.9351401670315425;
		fConst260 = 1.0 / ((fConst255 + 0.7431304601070396) / fConst254 + 1.450071084655647);
		fConst261 = 11.052052171507189 / fConst257;
		fConst262 = fConst261 + 1.450071084655647;
		fConst263 = 1.0 / ((fConst255 + 3.1897274020965583) / fConst254 + 4.076781969643807);
		fConst264 = 0.0017661728399818856 / fConst257;
		fConst265 = fConst264 + 0.00040767818495825777;
		fConst266 = 1.0 / ((fConst217 + 0.168404871113589) / fConst216 + 1.069358407707312);
		fConst267 = fConst245 + 53.53615295455673;
		fConst268 = 1.0 / ((fConst217 + 0.512478641889141) / fConst216 + 0.689621364484675);
		fConst269 = fConst245 + 7.621731298870603;
		fConst270 = 1.0 / ((fConst217 + 0.782413046821645) / fConst216 + 0.24529150870616);
		fConst271 = 9.9999997055e-05 / fConst219;
		fConst272 = fConst271 + 0.000433227200555;
		fConst273 = (fConst217 + -0.782413046821645) / fConst216 + 0.24529150870616;
		fConst274 = 2.0 * (0.24529150870616 - fConst245);
		fConst275 = 2.0 * (0.000433227200555 - fConst271);
		fConst276 = (fConst217 + -0.512478641889141) / fConst216 + 0.689621364484675;
		fConst277 = 2.0 * (0.689621364484675 - fConst245);
		fConst278 = 2.0 * (7.621731298870603 - fConst245);
		fConst279 = (fConst217 + -0.168404871113589) / fConst216 + 1.069358407707312;
		fConst280 = 2.0 * (1.069358407707312 - fConst245);
		fConst281 = 2.0 * (53.53615295455673 - fConst245);
		fConst282 = (fConst255 + -3.1897274020965583) / fConst254 + 4.076781969643807;
		fConst283 = 1.0 / fConst257;
		fConst284 = 2.0 * (4.076781969643807 - fConst283);
		fConst285 = 2.0 * (0.00040767818495825777 - fConst264);
		fConst286 = (fConst255 + -0.7431304601070396) / fConst254 + 1.450071084655647;
		fConst287 = 2.0 * (1.450071084655647 - fConst283);
		fConst288 = 2.0 * (1.450071084655647 - fConst261);
		fConst289 = (fConst255 + -0.157482159302087) / fConst254 + 0.9351401670315425;
		fConst290 = 2.0 * (0.9351401670315425 - fConst283);
		fConst291 = 2.0 * (0.9351401670315425 - fConst258);
		fConst292 = std::tan(1246.7418707910015 / fConst0);
		fConst293 = 1.0 / fConst292;
		fConst294 = 1.0 / ((fConst293 + 0.157482159302087) / fConst292 + 0.9351401670315425);
		fConst295 = CubicDistortion_faustpower2_f(fConst292);
		fConst296 = 50.063807016150385 / fConst295;
		fConst297 = fConst296 + 0.9351401670315425;
		fConst298 = 1.0 / ((fConst293 + 0.7431304601070396) / fConst292 + 1.450071084655647);
		fConst299 = 11.052052171507189 / fConst295;
		fConst300 = fConst299 + 1.450071084655647;
		fConst301 = 1.0 / ((fConst293 + 3.1897274020965583) / fConst292 + 4.076781969643807);
		fConst302 = 0.0017661728399818856 / fConst295;
		fConst303 = fConst302 + 0.00040767818495825777;
		fConst304 = 1.0 / ((fConst255 + 0.168404871113589) / fConst254 + 1.069358407707312);
		fConst305 = fConst283 + 53.53615295455673;
		fConst306 = 1.0 / ((fConst255 + 0.512478641889141) / fConst254 + 0.689621364484675);
		fConst307 = fConst283 + 7.621731298870603;
		fConst308 = 1.0 / ((fConst255 + 0.782413046821645) / fConst254 + 0.24529150870616);
		fConst309 = 9.9999997055e-05 / fConst257;
		fConst310 = fConst309 + 0.000433227200555;
		fConst311 = (fConst255 + -0.782413046821645) / fConst254 + 0.24529150870616;
		fConst312 = 2.0 * (0.24529150870616 - fConst283);
		fConst313 = 2.0 * (0.000433227200555 - fConst309);
		fConst314 = (fConst255 + -0.512478641889141) / fConst254 + 0.689621364484675;
		fConst315 = 2.0 * (0.689621364484675 - fConst283);
		fConst316 = 2.0 * (7.621731298870603 - fConst283);
		fConst317 = (fConst255 + -0.168404871113589) / fConst254 + 1.069358407707312;
		fConst318 = 2.0 * (1.069358407707312 - fConst283);
		fConst319 = 2.0 * (53.53615295455673 - fConst283);
		fConst320 = (fConst293 + -3.1897274020965583) / fConst292 + 4.076781969643807;
		fConst321 = 1.0 / fConst295;
		fConst322 = 2.0 * (4.076781969643807 - fConst321);
		fConst323 = 2.0 * (0.00040767818495825777 - fConst302);
		fConst324 = (fConst293 + -0.7431304601070396) / fConst292 + 1.450071084655647;
		fConst325 = 2.0 * (1.450071084655647 - fConst321);
		fConst326 = 2.0 * (1.450071084655647 - fConst299);
		fConst327 = (fConst293 + -0.157482159302087) / fConst292 + 0.9351401670315425;
		fConst328 = 2.0 * (0.9351401670315425 - fConst321);
		fConst329 = 2.0 * (0.9351401670315425 - fConst296);
		fConst330 = std::tan(785.3981633974482 / fConst0);
		fConst331 = 1.0 / fConst330;
		fConst332 = 1.0 / ((fConst331 + 0.157482159302087) / fConst330 + 0.9351401670315425);
		fConst333 = CubicDistortion_faustpower2_f(fConst330);
		fConst334 = 50.063807016150385 / fConst333;
		fConst335 = fConst334 + 0.9351401670315425;
		fConst336 = 1.0 / ((fConst331 + 0.7431304601070396) / fConst330 + 1.450071084655647);
		fConst337 = 11.052052171507189 / fConst333;
		fConst338 = fConst337 + 1.450071084655647;
		fConst339 = 1.0 / ((fConst331 + 3.1897274020965583) / fConst330 + 4.076781969643807);
		fConst340 = 0.0017661728399818856 / fConst333;
		fConst341 = fConst340 + 0.00040767818495825777;
		fConst342 = 1.0 / ((fConst293 + 0.168404871113589) / fConst292 + 1.069358407707312);
		fConst343 = fConst321 + 53.53615295455673;
		fConst344 = 1.0 / ((fConst293 + 0.512478641889141) / fConst292 + 0.689621364484675);
		fConst345 = fConst321 + 7.621731298870603;
		fConst346 = 1.0 / ((fConst293 + 0.782413046821645) / fConst292 + 0.24529150870616);
		fConst347 = 9.9999997055e-05 / fConst295;
		fConst348 = fConst347 + 0.000433227200555;
		fConst349 = (fConst293 + -0.782413046821645) / fConst292 + 0.24529150870616;
		fConst350 = 2.0 * (0.24529150870616 - fConst321);
		fConst351 = 2.0 * (0.000433227200555 - fConst347);
		fConst352 = (fConst293 + -0.512478641889141) / fConst292 + 0.689621364484675;
		fConst353 = 2.0 * (0.689621364484675 - fConst321);
		fConst354 = 2.0 * (7.621731298870603 - fConst321);
		fConst355 = (fConst293 + -0.168404871113589) / fConst292 + 1.069358407707312;
		fConst356 = 2.0 * (1.069358407707312 - fConst321);
		fConst357 = 2.0 * (53.53615295455673 - fConst321);
		fConst358 = (fConst331 + -3.1897274020965583) / fConst330 + 4.076781969643807;
		fConst359 = 1.0 / fConst333;
		fConst360 = 2.0 * (4.076781969643807 - fConst359);
		fConst361 = 2.0 * (0.00040767818495825777 - fConst340);
		fConst362 = (fConst331 + -0.7431304601070396) / fConst330 + 1.450071084655647;
		fConst363 = 2.0 * (1.450071084655647 - fConst359);
		fConst364 = 2.0 * (1.450071084655647 - fConst337);
		fConst365 = (fConst331 + -0.157482159302087) / fConst330 + 0.9351401670315425;
		fConst366 = 2.0 * (0.9351401670315425 - fConst359);
		fConst367 = 2.0 * (0.9351401670315425 - fConst334);
		fConst368 = std::tan(494.769839306609 / fConst0);
		fConst369 = 1.0 / fConst368;
		fConst370 = 1.0 / ((fConst369 + 0.157482159302087) / fConst368 + 0.9351401670315425);
		fConst371 = CubicDistortion_faustpower2_f(fConst368);
		fConst372 = 50.063807016150385 / fConst371;
		fConst373 = fConst372 + 0.9351401670315425;
		fConst374 = 1.0 / ((fConst369 + 0.7431304601070396) / fConst368 + 1.450071084655647);
		fConst375 = 11.052052171507189 / fConst371;
		fConst376 = fConst375 + 1.450071084655647;
		fConst377 = 1.0 / ((fConst369 + 3.1897274020965583) / fConst368 + 4.076781969643807);
		fConst378 = 0.0017661728399818856 / fConst371;
		fConst379 = fConst378 + 0.00040767818495825777;
		fConst380 = 1.0 / ((fConst331 + 0.168404871113589) / fConst330 + 1.069358407707312);
		fConst381 = fConst359 + 53.53615295455673;
		fConst382 = 1.0 / ((fConst331 + 0.512478641889141) / fConst330 + 0.689621364484675);
		fConst383 = fConst359 + 7.621731298870603;
		fConst384 = 1.0 / ((fConst331 + 0.782413046821645) / fConst330 + 0.24529150870616);
		fConst385 = 9.9999997055e-05 / fConst333;
		fConst386 = fConst385 + 0.000433227200555;
		fConst387 = (fConst331 + -0.782413046821645) / fConst330 + 0.24529150870616;
		fConst388 = 2.0 * (0.24529150870616 - fConst359);
		fConst389 = 2.0 * (0.000433227200555 - fConst385);
		fConst390 = (fConst331 + -0.512478641889141) / fConst330 + 0.689621364484675;
		fConst391 = 2.0 * (0.689621364484675 - fConst359);
		fConst392 = 2.0 * (7.621731298870603 - fConst359);
		fConst393 = (fConst331 + -0.168404871113589) / fConst330 + 1.069358407707312;
		fConst394 = 2.0 * (1.069358407707312 - fConst359);
		fConst395 = 2.0 * (53.53615295455673 - fConst359);
		fConst396 = (fConst369 + -3.1897274020965583) / fConst368 + 4.076781969643807;
		fConst397 = 1.0 / fConst371;
		fConst398 = 2.0 * (4.076781969643807 - fConst397);
		fConst399 = 2.0 * (0.00040767818495825777 - fConst378);
		fConst400 = (fConst369 + -0.7431304601070396) / fConst368 + 1.450071084655647;
		fConst401 = 2.0 * (1.450071084655647 - fConst397);
		fConst402 = 2.0 * (1.450071084655647 - fConst375);
		fConst403 = (fConst369 + -0.157482159302087) / fConst368 + 0.9351401670315425;
		fConst404 = 2.0 * (0.9351401670315425 - fConst397);
		fConst405 = 2.0 * (0.9351401670315425 - fConst372);
		fConst406 = std::tan(311.68546769775037 / fConst0);
		fConst407 = 1.0 / fConst406;
		fConst408 = 1.0 / ((fConst407 + 0.157482159302087) / fConst406 + 0.9351401670315425);
		fConst409 = CubicDistortion_faustpower2_f(fConst406);
		fConst410 = 50.063807016150385 / fConst409;
		fConst411 = fConst410 + 0.9351401670315425;
		fConst412 = 1.0 / ((fConst407 + 0.7431304601070396) / fConst406 + 1.450071084655647);
		fConst413 = 11.052052171507189 / fConst409;
		fConst414 = fConst413 + 1.450071084655647;
		fConst415 = 1.0 / ((fConst407 + 3.1897274020965583) / fConst406 + 4.076781969643807);
		fConst416 = 0.0017661728399818856 / fConst409;
		fConst417 = fConst416 + 0.00040767818495825777;
		fConst418 = 1.0 / ((fConst369 + 0.168404871113589) / fConst368 + 1.069358407707312);
		fConst419 = fConst397 + 53.53615295455673;
		fConst420 = 1.0 / ((fConst369 + 0.512478641889141) / fConst368 + 0.689621364484675);
		fConst421 = fConst397 + 7.621731298870603;
		fConst422 = 1.0 / ((fConst369 + 0.782413046821645) / fConst368 + 0.24529150870616);
		fConst423 = 9.9999997055e-05 / fConst371;
		fConst424 = fConst423 + 0.000433227200555;
		fConst425 = (fConst369 + -0.782413046821645) / fConst368 + 0.24529150870616;
		fConst426 = 2.0 * (0.24529150870616 - fConst397);
		fConst427 = 2.0 * (0.000433227200555 - fConst423);
		fConst428 = (fConst369 + -0.512478641889141) / fConst368 + 0.689621364484675;
		fConst429 = 2.0 * (0.689621364484675 - fConst397);
		fConst430 = 2.0 * (7.621731298870603 - fConst397);
		fConst431 = (fConst369 + -0.168404871113589) / fConst368 + 1.069358407707312;
		fConst432 = 2.0 * (1.069358407707312 - fConst397);
		fConst433 = 2.0 * (53.53615295455673 - fConst397);
		fConst434 = (fConst407 + -3.1897274020965583) / fConst406 + 4.076781969643807;
		fConst435 = 1.0 / fConst409;
		fConst436 = 2.0 * (4.076781969643807 - fConst435);
		fConst437 = 2.0 * (0.00040767818495825777 - fConst416);
		fConst438 = (fConst407 + -0.7431304601070396) / fConst406 + 1.450071084655647;
		fConst439 = 2.0 * (1.450071084655647 - fConst435);
		fConst440 = 2.0 * (1.450071084655647 - fConst413);
		fConst441 = (fConst407 + -0.157482159302087) / fConst406 + 0.9351401670315425;
		fConst442 = 2.0 * (0.9351401670315425 - fConst435);
		fConst443 = 2.0 * (0.9351401670315425 - fConst410);
		fConst444 = std::tan(196.34954084936206 / fConst0);
		fConst445 = 1.0 / fConst444;
		fConst446 = 1.0 / ((fConst445 + 0.157482159302087) / fConst444 + 0.9351401670315425);
		fConst447 = CubicDistortion_faustpower2_f(fConst444);
		fConst448 = 50.063807016150385 / fConst447;
		fConst449 = fConst448 + 0.9351401670315425;
		fConst450 = 1.0 / ((fConst445 + 0.7431304601070396) / fConst444 + 1.450071084655647);
		fConst451 = 11.052052171507189 / fConst447;
		fConst452 = fConst451 + 1.450071084655647;
		fConst453 = 1.0 / ((fConst445 + 3.1897274020965583) / fConst444 + 4.076781969643807);
		fConst454 = 0.0017661728399818856 / fConst447;
		fConst455 = fConst454 + 0.00040767818495825777;
		fConst456 = 1.0 / ((fConst407 + 0.168404871113589) / fConst406 + 1.069358407707312);
		fConst457 = fConst435 + 53.53615295455673;
		fConst458 = 1.0 / ((fConst407 + 0.512478641889141) / fConst406 + 0.689621364484675);
		fConst459 = fConst435 + 7.621731298870603;
		fConst460 = 1.0 / ((fConst407 + 0.782413046821645) / fConst406 + 0.24529150870616);
		fConst461 = 9.9999997055e-05 / fConst409;
		fConst462 = fConst461 + 0.000433227200555;
		fConst463 = (fConst407 + -0.782413046821645) / fConst406 + 0.24529150870616;
		fConst464 = 2.0 * (0.24529150870616 - fConst435);
		fConst465 = 2.0 * (0.000433227200555 - fConst461);
		fConst466 = (fConst407 + -0.512478641889141) / fConst406 + 0.689621364484675;
		fConst467 = 2.0 * (0.689621364484675 - fConst435);
		fConst468 = 2.0 * (7.621731298870603 - fConst435);
		fConst469 = (fConst407 + -0.168404871113589) / fConst406 + 1.069358407707312;
		fConst470 = 2.0 * (1.069358407707312 - fConst435);
		fConst471 = 2.0 * (53.53615295455673 - fConst435);
		fConst472 = (fConst445 + -3.1897274020965583) / fConst444 + 4.076781969643807;
		fConst473 = 1.0 / fConst447;
		fConst474 = 2.0 * (4.076781969643807 - fConst473);
		fConst475 = 2.0 * (0.00040767818495825777 - fConst454);
		fConst476 = (fConst445 + -0.7431304601070396) / fConst444 + 1.450071084655647;
		fConst477 = 2.0 * (1.450071084655647 - fConst473);
		fConst478 = 2.0 * (1.450071084655647 - fConst451);
		fConst479 = (fConst445 + -0.157482159302087) / fConst444 + 0.9351401670315425;
		fConst480 = 2.0 * (0.9351401670315425 - fConst473);
		fConst481 = 2.0 * (0.9351401670315425 - fConst448);
		fConst482 = std::tan(123.69245982665232 / fConst0);
		fConst483 = 1.0 / fConst482;
		fConst484 = 1.0 / ((fConst483 + 0.157482159302087) / fConst482 + 0.9351401670315425);
		fConst485 = CubicDistortion_faustpower2_f(fConst482);
		fConst486 = 50.063807016150385 / fConst485;
		fConst487 = fConst486 + 0.9351401670315425;
		fConst488 = 1.0 / ((fConst483 + 0.7431304601070396) / fConst482 + 1.450071084655647);
		fConst489 = 11.052052171507189 / fConst485;
		fConst490 = fConst489 + 1.450071084655647;
		fConst491 = 1.0 / ((fConst483 + 3.1897274020965583) / fConst482 + 4.076781969643807);
		fConst492 = 0.0017661728399818856 / fConst485;
		fConst493 = fConst492 + 0.00040767818495825777;
		fConst494 = 1.0 / ((fConst445 + 0.168404871113589) / fConst444 + 1.069358407707312);
		fConst495 = fConst473 + 53.53615295455673;
		fConst496 = 1.0 / ((fConst445 + 0.512478641889141) / fConst444 + 0.689621364484675);
		fConst497 = fConst473 + 7.621731298870603;
		fConst498 = 1.0 / ((fConst445 + 0.782413046821645) / fConst444 + 0.24529150870616);
		fConst499 = 9.9999997055e-05 / fConst447;
		fConst500 = fConst499 + 0.000433227200555;
		fConst501 = (fConst445 + -0.782413046821645) / fConst444 + 0.24529150870616;
		fConst502 = 2.0 * (0.24529150870616 - fConst473);
		fConst503 = 2.0 * (0.000433227200555 - fConst499);
		fConst504 = (fConst445 + -0.512478641889141) / fConst444 + 0.689621364484675;
		fConst505 = 2.0 * (0.689621364484675 - fConst473);
		fConst506 = 2.0 * (7.621731298870603 - fConst473);
		fConst507 = (fConst445 + -0.168404871113589) / fConst444 + 1.069358407707312;
		fConst508 = 2.0 * (1.069358407707312 - fConst473);
		fConst509 = 2.0 * (53.53615295455673 - fConst473);
		fConst510 = (fConst483 + -3.1897274020965583) / fConst482 + 4.076781969643807;
		fConst511 = 1.0 / fConst485;
		fConst512 = 2.0 * (4.076781969643807 - fConst511);
		fConst513 = 2.0 * (0.00040767818495825777 - fConst492);
		fConst514 = (fConst483 + -0.7431304601070396) / fConst482 + 1.450071084655647;
		fConst515 = 2.0 * (1.450071084655647 - fConst511);
		fConst516 = 2.0 * (1.450071084655647 - fConst489);
		fConst517 = (fConst483 + -0.157482159302087) / fConst482 + 0.9351401670315425;
		fConst518 = 2.0 * (0.9351401670315425 - fConst511);
		fConst519 = 2.0 * (0.9351401670315425 - fConst486);
		fConst520 = 1.0 / ((fConst483 + 0.168404871113589) / fConst482 + 1.069358407707312);
		fConst521 = fConst511 + 53.53615295455673;
		fConst522 = 1.0 / ((fConst483 + 0.512478641889141) / fConst482 + 0.689621364484675);
		fConst523 = fConst511 + 7.621731298870603;
		fConst524 = 1.0 / ((fConst483 + 0.782413046821645) / fConst482 + 0.24529150870616);
		fConst525 = 9.9999997055e-05 / fConst485;
		fConst526 = fConst525 + 0.000433227200555;
		fConst527 = (fConst483 + -0.782413046821645) / fConst482 + 0.24529150870616;
		fConst528 = 2.0 * (0.24529150870616 - fConst511);
		fConst529 = 2.0 * (0.000433227200555 - fConst525);
		fConst530 = (fConst483 + -0.512478641889141) / fConst482 + 0.689621364484675;
		fConst531 = 2.0 * (0.689621364484675 - fConst511);
		fConst532 = 2.0 * (7.621731298870603 - fConst511);
		fConst533 = (fConst483 + -0.168404871113589) / fConst482 + 1.069358407707312;
		fConst534 = 2.0 * (1.069358407707312 - fConst511);
		fConst535 = 2.0 * (53.53615295455673 - fConst511);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(5e+01);
		fHslider1 = static_cast<FAUSTFLOAT>(1e+02);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0);
		fHslider3 = static_cast<FAUSTFLOAT>(-2e+01);
		fHslider4 = static_cast<FAUSTFLOAT>(0.1);
		fHslider5 = static_cast<FAUSTFLOAT>(49.0);
		fHslider6 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec6[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec9[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec7[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec8[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec10[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fVec1[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec4[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec3[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec2[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec1[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec0[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec17[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec16[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec15[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec14[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec13[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec12[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec11[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec24[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec23[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec22[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec21[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec20[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec19[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec18[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec31[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec30[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec29[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec28[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec27[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec26[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec25[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec38[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec37[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec36[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec35[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec34[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec33[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec32[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec45[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec44[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 3; l43 = l43 + 1) {
			fRec43[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec42[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec41[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec40[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec39[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec52[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec51[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec50[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec49[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec48[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec47[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec46[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec59[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec58[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec57[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 3; l58 = l58 + 1) {
			fRec56[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 3; l59 = l59 + 1) {
			fRec55[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 3; l60 = l60 + 1) {
			fRec54[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec53[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 3; l62 = l62 + 1) {
			fRec66[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 3; l63 = l63 + 1) {
			fRec65[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 3; l64 = l64 + 1) {
			fRec64[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 3; l65 = l65 + 1) {
			fRec63[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 3; l66 = l66 + 1) {
			fRec62[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 3; l67 = l67 + 1) {
			fRec61[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec60[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 3; l69 = l69 + 1) {
			fRec73[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 3; l70 = l70 + 1) {
			fRec72[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 3; l71 = l71 + 1) {
			fRec71[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec70[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 3; l73 = l73 + 1) {
			fRec69[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 3; l74 = l74 + 1) {
			fRec68[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec67[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 3; l76 = l76 + 1) {
			fRec80[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 3; l77 = l77 + 1) {
			fRec79[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 3; l78 = l78 + 1) {
			fRec78[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 3; l79 = l79 + 1) {
			fRec77[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 3; l80 = l80 + 1) {
			fRec76[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec75[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec74[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 3; l83 = l83 + 1) {
			fRec87[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec86[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 3; l85 = l85 + 1) {
			fRec85[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 3; l86 = l86 + 1) {
			fRec84[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 3; l87 = l87 + 1) {
			fRec83[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 3; l88 = l88 + 1) {
			fRec82[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec81[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec94[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 3; l91 = l91 + 1) {
			fRec93[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec92[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 3; l93 = l93 + 1) {
			fRec91[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 3; l94 = l94 + 1) {
			fRec90[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 3; l95 = l95 + 1) {
			fRec89[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec88[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 3; l97 = l97 + 1) {
			fRec101[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 3; l98 = l98 + 1) {
			fRec100[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 3; l99 = l99 + 1) {
			fRec99[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 3; l100 = l100 + 1) {
			fRec98[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 3; l101 = l101 + 1) {
			fRec97[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 3; l102 = l102 + 1) {
			fRec96[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec95[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 3; l104 = l104 + 1) {
			fRec105[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 3; l105 = l105 + 1) {
			fRec104[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 3; l106 = l106 + 1) {
			fRec103[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec102[l107] = 0.0;
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
	
	virtual CubicDistortion* clone() {
		return new CubicDistortion(*this);
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
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Amplitude", &fHslider3, FAUSTFLOAT(-2e+01), FAUSTFLOAT(-1.2e+02), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)");
		ui_interface->declare(&fHslider5, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider5, FAUSTFLOAT(49.0), FAUSTFLOAT(1.0), FAUSTFLOAT(88.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->declare(&fHslider4, "scale", "log");
		ui_interface->declare(&fHslider4, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fHslider4, "unit", "sec");
		ui_interface->addHorizontalSlider("Portamento", &fHslider4, FAUSTFLOAT(0.1), FAUSTFLOAT(0.001), FAUSTFLOAT(1e+01), FAUSTFLOAT(0.001));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html");
		ui_interface->openVerticalBox("CUBIC NONLINEARITY cubicnl");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the nonlinearity has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "tooltip", "Amount of distortion");
		ui_interface->addHorizontalSlider("Drive", &fHslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "tooltip", "Brings in even harmonics");
		ui_interface->addHorizontalSlider("Offset", &fHslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.01));
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
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		double fSlow0 = static_cast<double>(fHslider0);
		double fSlow1 = static_cast<double>(fHslider1);
		double fSlow2 = (((0.001 * fSlow1) > 0.0) ? std::exp(-(fConst1 / fSlow1)) : 0.0);
		int iSlow3 = static_cast<int>(static_cast<double>(fCheckbox0));
		double fSlow4 = 0.0010000000000000009 * static_cast<double>(fHslider2);
		double fSlow5 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fHslider3));
		double fSlow6 = static_cast<double>(fHslider4);
		double fSlow7 = ((fSlow6 > 0.0) ? std::exp(-(fConst15 / fSlow6)) : 0.0);
		double fSlow8 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fHslider5) + -49.0)) * (1.0 - fSlow7);
		double fSlow9 = 0.0010000000000000009 * static_cast<double>(fHslider6);
		double fSlow10 = 1.0 - fSlow2;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec5[0] = fSlow4 + 0.999 * fRec5[1];
			fRec6[0] = fSlow5 + 0.999 * fRec6[1];
			fRec9[0] = fRec9[1] * fSlow7 + fSlow8;
			double fTemp0 = fConst14 * fRec9[0];
			double fTemp1 = std::sin(fTemp0);
			double fTemp2 = std::cos(fTemp0);
			fRec7[0] = fRec8[1] * fTemp1 + fRec7[1] * fTemp2;
			fRec8[0] = static_cast<double>(1 - iVec0[1]) + fRec8[1] * fTemp2 - fTemp1 * fRec7[1];
			double fTemp3 = fRec6[0] * fRec7[0];
			fRec10[0] = fSlow9 + 0.999 * fRec10[1];
			double fTemp4 = std::max<double>(-1.0, std::min<double>(1.0, fRec5[0] + ((iSlow3) ? 0.0 : fTemp3) * std::pow(1e+01, 2.0 * fRec10[0])));
			double fTemp5 = fTemp4 * (1.0 - 0.3333333333333333 * CubicDistortion_faustpower2_f(fTemp4));
			fVec1[0] = fTemp5;
			fRec4[0] = 0.995 * fRec4[1] + fTemp5 - fVec1[1];
			double fTemp6 = ((iSlow3) ? fTemp3 : fRec4[0]);
			fRec3[0] = fTemp6 - fConst11 * (fConst16 * fRec3[2] + fConst18 * fRec3[1]);
			fRec2[0] = fConst11 * (fConst13 * fRec3[0] + fConst19 * fRec3[1] + fConst13 * fRec3[2]) - fConst8 * (fConst20 * fRec2[2] + fConst21 * fRec2[1]);
			fRec1[0] = fConst8 * (fConst10 * fRec2[0] + fConst22 * fRec2[1] + fConst10 * fRec2[2]) - fConst4 * (fConst23 * fRec1[2] + fConst24 * fRec1[1]);
			fRec0[0] = fRec0[1] * fSlow2 + std::fabs(fConst4 * (fConst7 * fRec1[0] + fConst25 * fRec1[1] + fConst7 * fRec1[2])) * fSlow10;
			fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec0[0]));
			fRec17[0] = fTemp6 - fConst42 * (fConst45 * fRec17[2] + fConst46 * fRec17[1]);
			fRec16[0] = fConst42 * (fConst44 * fRec17[0] + fConst47 * fRec17[1] + fConst44 * fRec17[2]) - fConst40 * (fConst48 * fRec16[2] + fConst49 * fRec16[1]);
			fRec15[0] = fConst40 * (fConst41 * fRec16[0] + fConst50 * fRec16[1] + fConst41 * fRec16[2]) - fConst38 * (fConst51 * fRec15[2] + fConst52 * fRec15[1]);
			double fTemp7 = fConst38 * (fConst39 * fRec15[0] + fConst53 * fRec15[1] + fConst39 * fRec15[2]);
			fRec14[0] = fTemp7 - fConst35 * (fConst54 * fRec14[2] + fConst56 * fRec14[1]);
			fRec13[0] = fConst35 * (fConst37 * fRec14[0] + fConst57 * fRec14[1] + fConst37 * fRec14[2]) - fConst32 * (fConst58 * fRec13[2] + fConst59 * fRec13[1]);
			fRec12[0] = fConst32 * (fConst34 * fRec13[0] + fConst60 * fRec13[1] + fConst34 * fRec13[2]) - fConst28 * (fConst61 * fRec12[2] + fConst62 * fRec12[1]);
			fRec11[0] = fSlow2 * fRec11[1] + fSlow10 * std::fabs(fConst28 * (fConst31 * fRec12[0] + fConst63 * fRec12[1] + fConst31 * fRec12[2]));
			fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec11[0]));
			fRec24[0] = fTemp7 - fConst80 * (fConst83 * fRec24[2] + fConst84 * fRec24[1]);
			fRec23[0] = fConst80 * (fConst82 * fRec24[0] + fConst85 * fRec24[1] + fConst82 * fRec24[2]) - fConst78 * (fConst86 * fRec23[2] + fConst87 * fRec23[1]);
			fRec22[0] = fConst78 * (fConst79 * fRec23[0] + fConst88 * fRec23[1] + fConst79 * fRec23[2]) - fConst76 * (fConst89 * fRec22[2] + fConst90 * fRec22[1]);
			double fTemp8 = fConst76 * (fConst77 * fRec22[0] + fConst91 * fRec22[1] + fConst77 * fRec22[2]);
			fRec21[0] = fTemp8 - fConst73 * (fConst92 * fRec21[2] + fConst94 * fRec21[1]);
			fRec20[0] = fConst73 * (fConst75 * fRec21[0] + fConst95 * fRec21[1] + fConst75 * fRec21[2]) - fConst70 * (fConst96 * fRec20[2] + fConst97 * fRec20[1]);
			fRec19[0] = fConst70 * (fConst72 * fRec20[0] + fConst98 * fRec20[1] + fConst72 * fRec20[2]) - fConst66 * (fConst99 * fRec19[2] + fConst100 * fRec19[1]);
			fRec18[0] = fSlow2 * fRec18[1] + fSlow10 * std::fabs(fConst66 * (fConst69 * fRec19[0] + fConst101 * fRec19[1] + fConst69 * fRec19[2]));
			fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec18[0]));
			fRec31[0] = fTemp8 - fConst118 * (fConst121 * fRec31[2] + fConst122 * fRec31[1]);
			fRec30[0] = fConst118 * (fConst120 * fRec31[0] + fConst123 * fRec31[1] + fConst120 * fRec31[2]) - fConst116 * (fConst124 * fRec30[2] + fConst125 * fRec30[1]);
			fRec29[0] = fConst116 * (fConst117 * fRec30[0] + fConst126 * fRec30[1] + fConst117 * fRec30[2]) - fConst114 * (fConst127 * fRec29[2] + fConst128 * fRec29[1]);
			double fTemp9 = fConst114 * (fConst115 * fRec29[0] + fConst129 * fRec29[1] + fConst115 * fRec29[2]);
			fRec28[0] = fTemp9 - fConst111 * (fConst130 * fRec28[2] + fConst132 * fRec28[1]);
			fRec27[0] = fConst111 * (fConst113 * fRec28[0] + fConst133 * fRec28[1] + fConst113 * fRec28[2]) - fConst108 * (fConst134 * fRec27[2] + fConst135 * fRec27[1]);
			fRec26[0] = fConst108 * (fConst110 * fRec27[0] + fConst136 * fRec27[1] + fConst110 * fRec27[2]) - fConst104 * (fConst137 * fRec26[2] + fConst138 * fRec26[1]);
			fRec25[0] = fSlow2 * fRec25[1] + fSlow10 * std::fabs(fConst104 * (fConst107 * fRec26[0] + fConst139 * fRec26[1] + fConst107 * fRec26[2]));
			fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec25[0]));
			fRec38[0] = fTemp9 - fConst156 * (fConst159 * fRec38[2] + fConst160 * fRec38[1]);
			fRec37[0] = fConst156 * (fConst158 * fRec38[0] + fConst161 * fRec38[1] + fConst158 * fRec38[2]) - fConst154 * (fConst162 * fRec37[2] + fConst163 * fRec37[1]);
			fRec36[0] = fConst154 * (fConst155 * fRec37[0] + fConst164 * fRec37[1] + fConst155 * fRec37[2]) - fConst152 * (fConst165 * fRec36[2] + fConst166 * fRec36[1]);
			double fTemp10 = fConst152 * (fConst153 * fRec36[0] + fConst167 * fRec36[1] + fConst153 * fRec36[2]);
			fRec35[0] = fTemp10 - fConst149 * (fConst168 * fRec35[2] + fConst170 * fRec35[1]);
			fRec34[0] = fConst149 * (fConst151 * fRec35[0] + fConst171 * fRec35[1] + fConst151 * fRec35[2]) - fConst146 * (fConst172 * fRec34[2] + fConst173 * fRec34[1]);
			fRec33[0] = fConst146 * (fConst148 * fRec34[0] + fConst174 * fRec34[1] + fConst148 * fRec34[2]) - fConst142 * (fConst175 * fRec33[2] + fConst176 * fRec33[1]);
			fRec32[0] = fSlow2 * fRec32[1] + fSlow10 * std::fabs(fConst142 * (fConst145 * fRec33[0] + fConst177 * fRec33[1] + fConst145 * fRec33[2]));
			fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec32[0]));
			fRec45[0] = fTemp10 - fConst194 * (fConst197 * fRec45[2] + fConst198 * fRec45[1]);
			fRec44[0] = fConst194 * (fConst196 * fRec45[0] + fConst199 * fRec45[1] + fConst196 * fRec45[2]) - fConst192 * (fConst200 * fRec44[2] + fConst201 * fRec44[1]);
			fRec43[0] = fConst192 * (fConst193 * fRec44[0] + fConst202 * fRec44[1] + fConst193 * fRec44[2]) - fConst190 * (fConst203 * fRec43[2] + fConst204 * fRec43[1]);
			double fTemp11 = fConst190 * (fConst191 * fRec43[0] + fConst205 * fRec43[1] + fConst191 * fRec43[2]);
			fRec42[0] = fTemp11 - fConst187 * (fConst206 * fRec42[2] + fConst208 * fRec42[1]);
			fRec41[0] = fConst187 * (fConst189 * fRec42[0] + fConst209 * fRec42[1] + fConst189 * fRec42[2]) - fConst184 * (fConst210 * fRec41[2] + fConst211 * fRec41[1]);
			fRec40[0] = fConst184 * (fConst186 * fRec41[0] + fConst212 * fRec41[1] + fConst186 * fRec41[2]) - fConst180 * (fConst213 * fRec40[2] + fConst214 * fRec40[1]);
			fRec39[0] = fSlow2 * fRec39[1] + fSlow10 * std::fabs(fConst180 * (fConst183 * fRec40[0] + fConst215 * fRec40[1] + fConst183 * fRec40[2]));
			fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec39[0]));
			fRec52[0] = fTemp11 - fConst232 * (fConst235 * fRec52[2] + fConst236 * fRec52[1]);
			fRec51[0] = fConst232 * (fConst234 * fRec52[0] + fConst237 * fRec52[1] + fConst234 * fRec52[2]) - fConst230 * (fConst238 * fRec51[2] + fConst239 * fRec51[1]);
			fRec50[0] = fConst230 * (fConst231 * fRec51[0] + fConst240 * fRec51[1] + fConst231 * fRec51[2]) - fConst228 * (fConst241 * fRec50[2] + fConst242 * fRec50[1]);
			double fTemp12 = fConst228 * (fConst229 * fRec50[0] + fConst243 * fRec50[1] + fConst229 * fRec50[2]);
			fRec49[0] = fTemp12 - fConst225 * (fConst244 * fRec49[2] + fConst246 * fRec49[1]);
			fRec48[0] = fConst225 * (fConst227 * fRec49[0] + fConst247 * fRec49[1] + fConst227 * fRec49[2]) - fConst222 * (fConst248 * fRec48[2] + fConst249 * fRec48[1]);
			fRec47[0] = fConst222 * (fConst224 * fRec48[0] + fConst250 * fRec48[1] + fConst224 * fRec48[2]) - fConst218 * (fConst251 * fRec47[2] + fConst252 * fRec47[1]);
			fRec46[0] = fSlow2 * fRec46[1] + fSlow10 * std::fabs(fConst218 * (fConst221 * fRec47[0] + fConst253 * fRec47[1] + fConst221 * fRec47[2]));
			fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec46[0]));
			fRec59[0] = fTemp12 - fConst270 * (fConst273 * fRec59[2] + fConst274 * fRec59[1]);
			fRec58[0] = fConst270 * (fConst272 * fRec59[0] + fConst275 * fRec59[1] + fConst272 * fRec59[2]) - fConst268 * (fConst276 * fRec58[2] + fConst277 * fRec58[1]);
			fRec57[0] = fConst268 * (fConst269 * fRec58[0] + fConst278 * fRec58[1] + fConst269 * fRec58[2]) - fConst266 * (fConst279 * fRec57[2] + fConst280 * fRec57[1]);
			double fTemp13 = fConst266 * (fConst267 * fRec57[0] + fConst281 * fRec57[1] + fConst267 * fRec57[2]);
			fRec56[0] = fTemp13 - fConst263 * (fConst282 * fRec56[2] + fConst284 * fRec56[1]);
			fRec55[0] = fConst263 * (fConst265 * fRec56[0] + fConst285 * fRec56[1] + fConst265 * fRec56[2]) - fConst260 * (fConst286 * fRec55[2] + fConst287 * fRec55[1]);
			fRec54[0] = fConst260 * (fConst262 * fRec55[0] + fConst288 * fRec55[1] + fConst262 * fRec55[2]) - fConst256 * (fConst289 * fRec54[2] + fConst290 * fRec54[1]);
			fRec53[0] = fSlow2 * fRec53[1] + fSlow10 * std::fabs(fConst256 * (fConst259 * fRec54[0] + fConst291 * fRec54[1] + fConst259 * fRec54[2]));
			fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec53[0]));
			fRec66[0] = fTemp13 - fConst308 * (fConst311 * fRec66[2] + fConst312 * fRec66[1]);
			fRec65[0] = fConst308 * (fConst310 * fRec66[0] + fConst313 * fRec66[1] + fConst310 * fRec66[2]) - fConst306 * (fConst314 * fRec65[2] + fConst315 * fRec65[1]);
			fRec64[0] = fConst306 * (fConst307 * fRec65[0] + fConst316 * fRec65[1] + fConst307 * fRec65[2]) - fConst304 * (fConst317 * fRec64[2] + fConst318 * fRec64[1]);
			double fTemp14 = fConst304 * (fConst305 * fRec64[0] + fConst319 * fRec64[1] + fConst305 * fRec64[2]);
			fRec63[0] = fTemp14 - fConst301 * (fConst320 * fRec63[2] + fConst322 * fRec63[1]);
			fRec62[0] = fConst301 * (fConst303 * fRec63[0] + fConst323 * fRec63[1] + fConst303 * fRec63[2]) - fConst298 * (fConst324 * fRec62[2] + fConst325 * fRec62[1]);
			fRec61[0] = fConst298 * (fConst300 * fRec62[0] + fConst326 * fRec62[1] + fConst300 * fRec62[2]) - fConst294 * (fConst327 * fRec61[2] + fConst328 * fRec61[1]);
			fRec60[0] = fSlow2 * fRec60[1] + fSlow10 * std::fabs(fConst294 * (fConst297 * fRec61[0] + fConst329 * fRec61[1] + fConst297 * fRec61[2]));
			fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec60[0]));
			fRec73[0] = fTemp14 - fConst346 * (fConst349 * fRec73[2] + fConst350 * fRec73[1]);
			fRec72[0] = fConst346 * (fConst348 * fRec73[0] + fConst351 * fRec73[1] + fConst348 * fRec73[2]) - fConst344 * (fConst352 * fRec72[2] + fConst353 * fRec72[1]);
			fRec71[0] = fConst344 * (fConst345 * fRec72[0] + fConst354 * fRec72[1] + fConst345 * fRec72[2]) - fConst342 * (fConst355 * fRec71[2] + fConst356 * fRec71[1]);
			double fTemp15 = fConst342 * (fConst343 * fRec71[0] + fConst357 * fRec71[1] + fConst343 * fRec71[2]);
			fRec70[0] = fTemp15 - fConst339 * (fConst358 * fRec70[2] + fConst360 * fRec70[1]);
			fRec69[0] = fConst339 * (fConst341 * fRec70[0] + fConst361 * fRec70[1] + fConst341 * fRec70[2]) - fConst336 * (fConst362 * fRec69[2] + fConst363 * fRec69[1]);
			fRec68[0] = fConst336 * (fConst338 * fRec69[0] + fConst364 * fRec69[1] + fConst338 * fRec69[2]) - fConst332 * (fConst365 * fRec68[2] + fConst366 * fRec68[1]);
			fRec67[0] = fSlow2 * fRec67[1] + fSlow10 * std::fabs(fConst332 * (fConst335 * fRec68[0] + fConst367 * fRec68[1] + fConst335 * fRec68[2]));
			fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec67[0]));
			fRec80[0] = fTemp15 - fConst384 * (fConst387 * fRec80[2] + fConst388 * fRec80[1]);
			fRec79[0] = fConst384 * (fConst386 * fRec80[0] + fConst389 * fRec80[1] + fConst386 * fRec80[2]) - fConst382 * (fConst390 * fRec79[2] + fConst391 * fRec79[1]);
			fRec78[0] = fConst382 * (fConst383 * fRec79[0] + fConst392 * fRec79[1] + fConst383 * fRec79[2]) - fConst380 * (fConst393 * fRec78[2] + fConst394 * fRec78[1]);
			double fTemp16 = fConst380 * (fConst381 * fRec78[0] + fConst395 * fRec78[1] + fConst381 * fRec78[2]);
			fRec77[0] = fTemp16 - fConst377 * (fConst396 * fRec77[2] + fConst398 * fRec77[1]);
			fRec76[0] = fConst377 * (fConst379 * fRec77[0] + fConst399 * fRec77[1] + fConst379 * fRec77[2]) - fConst374 * (fConst400 * fRec76[2] + fConst401 * fRec76[1]);
			fRec75[0] = fConst374 * (fConst376 * fRec76[0] + fConst402 * fRec76[1] + fConst376 * fRec76[2]) - fConst370 * (fConst403 * fRec75[2] + fConst404 * fRec75[1]);
			fRec74[0] = fSlow2 * fRec74[1] + fSlow10 * std::fabs(fConst370 * (fConst373 * fRec75[0] + fConst405 * fRec75[1] + fConst373 * fRec75[2]));
			fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec74[0]));
			fRec87[0] = fTemp16 - fConst422 * (fConst425 * fRec87[2] + fConst426 * fRec87[1]);
			fRec86[0] = fConst422 * (fConst424 * fRec87[0] + fConst427 * fRec87[1] + fConst424 * fRec87[2]) - fConst420 * (fConst428 * fRec86[2] + fConst429 * fRec86[1]);
			fRec85[0] = fConst420 * (fConst421 * fRec86[0] + fConst430 * fRec86[1] + fConst421 * fRec86[2]) - fConst418 * (fConst431 * fRec85[2] + fConst432 * fRec85[1]);
			double fTemp17 = fConst418 * (fConst419 * fRec85[0] + fConst433 * fRec85[1] + fConst419 * fRec85[2]);
			fRec84[0] = fTemp17 - fConst415 * (fConst434 * fRec84[2] + fConst436 * fRec84[1]);
			fRec83[0] = fConst415 * (fConst417 * fRec84[0] + fConst437 * fRec84[1] + fConst417 * fRec84[2]) - fConst412 * (fConst438 * fRec83[2] + fConst439 * fRec83[1]);
			fRec82[0] = fConst412 * (fConst414 * fRec83[0] + fConst440 * fRec83[1] + fConst414 * fRec83[2]) - fConst408 * (fConst441 * fRec82[2] + fConst442 * fRec82[1]);
			fRec81[0] = fSlow2 * fRec81[1] + fSlow10 * std::fabs(fConst408 * (fConst411 * fRec82[0] + fConst443 * fRec82[1] + fConst411 * fRec82[2]));
			fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec81[0]));
			fRec94[0] = fTemp17 - fConst460 * (fConst463 * fRec94[2] + fConst464 * fRec94[1]);
			fRec93[0] = fConst460 * (fConst462 * fRec94[0] + fConst465 * fRec94[1] + fConst462 * fRec94[2]) - fConst458 * (fConst466 * fRec93[2] + fConst467 * fRec93[1]);
			fRec92[0] = fConst458 * (fConst459 * fRec93[0] + fConst468 * fRec93[1] + fConst459 * fRec93[2]) - fConst456 * (fConst469 * fRec92[2] + fConst470 * fRec92[1]);
			double fTemp18 = fConst456 * (fConst457 * fRec92[0] + fConst471 * fRec92[1] + fConst457 * fRec92[2]);
			fRec91[0] = fTemp18 - fConst453 * (fConst472 * fRec91[2] + fConst474 * fRec91[1]);
			fRec90[0] = fConst453 * (fConst455 * fRec91[0] + fConst475 * fRec91[1] + fConst455 * fRec91[2]) - fConst450 * (fConst476 * fRec90[2] + fConst477 * fRec90[1]);
			fRec89[0] = fConst450 * (fConst452 * fRec90[0] + fConst478 * fRec90[1] + fConst452 * fRec90[2]) - fConst446 * (fConst479 * fRec89[2] + fConst480 * fRec89[1]);
			fRec88[0] = fSlow2 * fRec88[1] + fSlow10 * std::fabs(fConst446 * (fConst449 * fRec89[0] + fConst481 * fRec89[1] + fConst449 * fRec89[2]));
			fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec88[0]));
			fRec101[0] = fTemp18 - fConst498 * (fConst501 * fRec101[2] + fConst502 * fRec101[1]);
			fRec100[0] = fConst498 * (fConst500 * fRec101[0] + fConst503 * fRec101[1] + fConst500 * fRec101[2]) - fConst496 * (fConst504 * fRec100[2] + fConst505 * fRec100[1]);
			fRec99[0] = fConst496 * (fConst497 * fRec100[0] + fConst506 * fRec100[1] + fConst497 * fRec100[2]) - fConst494 * (fConst507 * fRec99[2] + fConst508 * fRec99[1]);
			double fTemp19 = fConst494 * (fConst495 * fRec99[0] + fConst509 * fRec99[1] + fConst495 * fRec99[2]);
			fRec98[0] = fTemp19 - fConst491 * (fConst510 * fRec98[2] + fConst512 * fRec98[1]);
			fRec97[0] = fConst491 * (fConst493 * fRec98[0] + fConst513 * fRec98[1] + fConst493 * fRec98[2]) - fConst488 * (fConst514 * fRec97[2] + fConst515 * fRec97[1]);
			fRec96[0] = fConst488 * (fConst490 * fRec97[0] + fConst516 * fRec97[1] + fConst490 * fRec97[2]) - fConst484 * (fConst517 * fRec96[2] + fConst518 * fRec96[1]);
			fRec95[0] = fSlow2 * fRec95[1] + fSlow10 * std::fabs(fConst484 * (fConst487 * fRec96[0] + fConst519 * fRec96[1] + fConst487 * fRec96[2]));
			fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec95[0]));
			fRec105[0] = fTemp19 - fConst524 * (fConst527 * fRec105[2] + fConst528 * fRec105[1]);
			fRec104[0] = fConst524 * (fConst526 * fRec105[0] + fConst529 * fRec105[1] + fConst526 * fRec105[2]) - fConst522 * (fConst530 * fRec104[2] + fConst531 * fRec104[1]);
			fRec103[0] = fConst522 * (fConst523 * fRec104[0] + fConst532 * fRec104[1] + fConst523 * fRec104[2]) - fConst520 * (fConst533 * fRec103[2] + fConst534 * fRec103[1]);
			fRec102[0] = fSlow2 * fRec102[1] + fSlow10 * std::fabs(fConst520 * (fConst521 * fRec103[0] + fConst535 * fRec103[1] + fConst521 * fRec103[2]));
			fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow0 + 2e+01 * std::log10(fRec102[0]));
			double fTemp20 = fTemp6;
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp20);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp20);
			iVec0[1] = iVec0[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec9[1] = fRec9[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[1] = fRec81[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[1] = fRec88[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[1] = fRec102[0];
		}
	}

};

bench_no_inline void inspect_compute(CubicDistortion& dsp, Real** inputs, Real** outputs);

int main() {
    CubicDistortion* dsp = new CubicDistortion();
    dsp->init(SAMP_RATE);
    
    s32 n_ins = dsp->getNumInputs();
    s32 n_outs = dsp->getNumOutputs();
    auto [base, err] = make_buffers(n_ins, n_outs);
    if (err) {
        printf("Critical allocation error: %d\n", err);
        exit(err);
    }

    Real** inputs = (Real**)base;
    Real** outputs = inputs + n_ins;
    
    inspect_compute(*dsp, inputs, outputs);
    free_buffers(base);
    delete dsp;
    return 0;
}

bench_no_inline bench_export
void inspect_compute(CubicDistortion& dsp, Real** inputs, Real** outputs)
{
    for (int i = 0; i < COMPUTE_ITERS; i++) {
        _do_not_optimize(inputs);
        _do_not_optimize(outputs);
        dsp.compute(BUFF_SIZE, inputs, outputs);
        _clobber_memory();
    }
}

#endif
