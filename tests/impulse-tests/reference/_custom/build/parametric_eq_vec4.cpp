/* ------------------------------------------------------------
name: "parametric_eq"
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

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	double fRec5_perm[4];
	FAUSTFLOAT fVslider1;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider2;
	double fRec7_perm[4];
	double fRec6_perm[4];
	FAUSTFLOAT fVslider3;
	double fRec8_perm[4];
	FAUSTFLOAT fVslider4;
	double fRec9_perm[4];
	int iRec10_perm[4];
	double fRec11_perm[4];
	double fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	int iVec0_perm[4];
	double fConst3;
	double fYec0_perm[4];
	double fConst4;
	double fYec1_perm[4];
	double fYec2_perm[4];
	double fConst5;
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
	FAUSTFLOAT fCheckbox2;
	double fYec18_perm[4];
	double fRec4_perm[4];
	double fRec3_perm[4];
	double fRec13_perm[4];
	double fRec12_perm[4];
	FAUSTFLOAT fHslider1;
	double fRec14_perm[4];
	FAUSTFLOAT fHslider2;
	double fConst6;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	double fConst7;
	double fRec2_perm[4];
	FAUSTFLOAT fHslider5;
	double fYec19_perm[4];
	double fRec1_perm[4];
	double fRec0_perm[4];
	double fRec16_perm[4];
	double fRec15_perm[4];
	FAUSTFLOAT fHslider6;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fRec20_perm[4];
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fRec19_perm[4];
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fRec18_perm[4];
	FAUSTFLOAT fHslider7;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fRec17_perm[4];
	double fConst31;
	double fConst32;
	double fConst33;
	double fRec27_perm[4];
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec26_perm[4];
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fRec25_perm[4];
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec24_perm[4];
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fRec23_perm[4];
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fRec22_perm[4];
	double fConst66;
	double fConst67;
	double fConst68;
	double fRec21_perm[4];
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec34_perm[4];
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fRec33_perm[4];
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fRec32_perm[4];
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fRec31_perm[4];
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fRec30_perm[4];
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fRec29_perm[4];
	double fConst104;
	double fConst105;
	double fConst106;
	double fRec28_perm[4];
	double fConst107;
	double fConst108;
	double fConst109;
	double fRec41_perm[4];
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fRec40_perm[4];
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fRec39_perm[4];
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fRec38_perm[4];
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fConst135;
	double fRec37_perm[4];
	double fConst136;
	double fConst137;
	double fConst138;
	double fConst139;
	double fConst140;
	double fConst141;
	double fRec36_perm[4];
	double fConst142;
	double fConst143;
	double fConst144;
	double fRec35_perm[4];
	double fConst145;
	double fConst146;
	double fConst147;
	double fRec48_perm[4];
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fRec47_perm[4];
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fRec46_perm[4];
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fRec45_perm[4];
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fConst173;
	double fRec44_perm[4];
	double fConst174;
	double fConst175;
	double fConst176;
	double fConst177;
	double fConst178;
	double fConst179;
	double fRec43_perm[4];
	double fConst180;
	double fConst181;
	double fConst182;
	double fRec42_perm[4];
	double fConst183;
	double fConst184;
	double fConst185;
	double fRec55_perm[4];
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst191;
	double fRec54_perm[4];
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fRec53_perm[4];
	double fConst197;
	double fConst198;
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fRec52_perm[4];
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fConst211;
	double fRec51_perm[4];
	double fConst212;
	double fConst213;
	double fConst214;
	double fConst215;
	double fConst216;
	double fConst217;
	double fRec50_perm[4];
	double fConst218;
	double fConst219;
	double fConst220;
	double fRec49_perm[4];
	double fConst221;
	double fConst222;
	double fConst223;
	double fRec62_perm[4];
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fConst229;
	double fRec61_perm[4];
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fRec60_perm[4];
	double fConst235;
	double fConst236;
	double fConst237;
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fConst243;
	double fRec59_perm[4];
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fConst249;
	double fRec58_perm[4];
	double fConst250;
	double fConst251;
	double fConst252;
	double fConst253;
	double fConst254;
	double fConst255;
	double fRec57_perm[4];
	double fConst256;
	double fConst257;
	double fConst258;
	double fRec56_perm[4];
	double fConst259;
	double fConst260;
	double fConst261;
	double fRec69_perm[4];
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fConst267;
	double fRec68_perm[4];
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fRec67_perm[4];
	double fConst273;
	double fConst274;
	double fConst275;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fConst281;
	double fRec66_perm[4];
	double fConst282;
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fConst287;
	double fRec65_perm[4];
	double fConst288;
	double fConst289;
	double fConst290;
	double fConst291;
	double fConst292;
	double fConst293;
	double fRec64_perm[4];
	double fConst294;
	double fConst295;
	double fConst296;
	double fRec63_perm[4];
	double fConst297;
	double fConst298;
	double fConst299;
	double fRec76_perm[4];
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fRec75_perm[4];
	double fConst306;
	double fConst307;
	double fConst308;
	double fConst309;
	double fConst310;
	double fRec74_perm[4];
	double fConst311;
	double fConst312;
	double fConst313;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fConst319;
	double fRec73_perm[4];
	double fConst320;
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fConst325;
	double fRec72_perm[4];
	double fConst326;
	double fConst327;
	double fConst328;
	double fConst329;
	double fConst330;
	double fConst331;
	double fRec71_perm[4];
	double fConst332;
	double fConst333;
	double fConst334;
	double fRec70_perm[4];
	double fConst335;
	double fConst336;
	double fConst337;
	double fRec83_perm[4];
	double fConst338;
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fConst343;
	double fRec82_perm[4];
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fRec81_perm[4];
	double fConst349;
	double fConst350;
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fConst357;
	double fRec80_perm[4];
	double fConst358;
	double fConst359;
	double fConst360;
	double fConst361;
	double fConst362;
	double fConst363;
	double fRec79_perm[4];
	double fConst364;
	double fConst365;
	double fConst366;
	double fConst367;
	double fConst368;
	double fConst369;
	double fRec78_perm[4];
	double fConst370;
	double fConst371;
	double fConst372;
	double fRec77_perm[4];
	double fConst373;
	double fConst374;
	double fConst375;
	double fRec90_perm[4];
	double fConst376;
	double fConst377;
	double fConst378;
	double fConst379;
	double fConst380;
	double fConst381;
	double fRec89_perm[4];
	double fConst382;
	double fConst383;
	double fConst384;
	double fConst385;
	double fConst386;
	double fRec88_perm[4];
	double fConst387;
	double fConst388;
	double fConst389;
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fConst395;
	double fRec87_perm[4];
	double fConst396;
	double fConst397;
	double fConst398;
	double fConst399;
	double fConst400;
	double fConst401;
	double fRec86_perm[4];
	double fConst402;
	double fConst403;
	double fConst404;
	double fConst405;
	double fConst406;
	double fConst407;
	double fRec85_perm[4];
	double fConst408;
	double fConst409;
	double fConst410;
	double fRec84_perm[4];
	double fConst411;
	double fConst412;
	double fConst413;
	double fRec97_perm[4];
	double fConst414;
	double fConst415;
	double fConst416;
	double fConst417;
	double fConst418;
	double fConst419;
	double fRec96_perm[4];
	double fConst420;
	double fConst421;
	double fConst422;
	double fConst423;
	double fConst424;
	double fRec95_perm[4];
	double fConst425;
	double fConst426;
	double fConst427;
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fConst433;
	double fRec94_perm[4];
	double fConst434;
	double fConst435;
	double fConst436;
	double fConst437;
	double fConst438;
	double fConst439;
	double fRec93_perm[4];
	double fConst440;
	double fConst441;
	double fConst442;
	double fConst443;
	double fConst444;
	double fConst445;
	double fRec92_perm[4];
	double fConst446;
	double fConst447;
	double fConst448;
	double fRec91_perm[4];
	double fConst449;
	double fConst450;
	double fConst451;
	double fRec104_perm[4];
	double fConst452;
	double fConst453;
	double fConst454;
	double fConst455;
	double fConst456;
	double fConst457;
	double fRec103_perm[4];
	double fConst458;
	double fConst459;
	double fConst460;
	double fConst461;
	double fConst462;
	double fRec102_perm[4];
	double fConst463;
	double fConst464;
	double fConst465;
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fConst470;
	double fConst471;
	double fRec101_perm[4];
	double fConst472;
	double fConst473;
	double fConst474;
	double fConst475;
	double fConst476;
	double fConst477;
	double fRec100_perm[4];
	double fConst478;
	double fConst479;
	double fConst480;
	double fConst481;
	double fConst482;
	double fConst483;
	double fRec99_perm[4];
	double fConst484;
	double fConst485;
	double fConst486;
	double fRec98_perm[4];
	double fConst487;
	double fConst488;
	double fConst489;
	double fRec111_perm[4];
	double fConst490;
	double fConst491;
	double fConst492;
	double fConst493;
	double fConst494;
	double fConst495;
	double fRec110_perm[4];
	double fConst496;
	double fConst497;
	double fConst498;
	double fConst499;
	double fConst500;
	double fRec109_perm[4];
	double fConst501;
	double fConst502;
	double fConst503;
	double fConst504;
	double fConst505;
	double fConst506;
	double fConst507;
	double fConst508;
	double fConst509;
	double fRec108_perm[4];
	double fConst510;
	double fConst511;
	double fConst512;
	double fConst513;
	double fConst514;
	double fConst515;
	double fRec107_perm[4];
	double fConst516;
	double fConst517;
	double fConst518;
	double fConst519;
	double fConst520;
	double fConst521;
	double fRec106_perm[4];
	double fConst522;
	double fConst523;
	double fConst524;
	double fRec105_perm[4];
	double fConst525;
	double fConst526;
	double fConst527;
	double fRec118_perm[4];
	double fConst528;
	double fConst529;
	double fConst530;
	double fConst531;
	double fConst532;
	double fConst533;
	double fRec117_perm[4];
	double fConst534;
	double fConst535;
	double fConst536;
	double fConst537;
	double fConst538;
	double fRec116_perm[4];
	double fConst539;
	double fConst540;
	double fConst541;
	double fConst542;
	double fConst543;
	double fConst544;
	double fConst545;
	double fConst546;
	double fConst547;
	double fRec115_perm[4];
	double fConst548;
	double fConst549;
	double fConst550;
	double fConst551;
	double fConst552;
	double fConst553;
	double fRec114_perm[4];
	double fConst554;
	double fConst555;
	double fConst556;
	double fConst557;
	double fConst558;
	double fConst559;
	double fRec113_perm[4];
	double fConst560;
	double fConst561;
	double fConst562;
	double fRec112_perm[4];
	double fConst563;
	double fConst564;
	double fConst565;
	double fRec125_perm[4];
	double fConst566;
	double fConst567;
	double fConst568;
	double fConst569;
	double fConst570;
	double fConst571;
	double fRec124_perm[4];
	double fConst572;
	double fConst573;
	double fConst574;
	double fConst575;
	double fConst576;
	double fRec123_perm[4];
	double fConst577;
	double fConst578;
	double fConst579;
	double fConst580;
	double fConst581;
	double fConst582;
	double fConst583;
	double fConst584;
	double fConst585;
	double fRec122_perm[4];
	double fConst586;
	double fConst587;
	double fConst588;
	double fConst589;
	double fConst590;
	double fConst591;
	double fRec121_perm[4];
	double fConst592;
	double fConst593;
	double fConst594;
	double fConst595;
	double fConst596;
	double fConst597;
	double fRec120_perm[4];
	double fConst598;
	double fConst599;
	double fConst600;
	double fRec119_perm[4];
	double fConst601;
	double fConst602;
	double fConst603;
	double fRec132_perm[4];
	double fConst604;
	double fConst605;
	double fConst606;
	double fConst607;
	double fConst608;
	double fConst609;
	double fRec131_perm[4];
	double fConst610;
	double fConst611;
	double fConst612;
	double fConst613;
	double fConst614;
	double fRec130_perm[4];
	double fConst615;
	double fConst616;
	double fConst617;
	double fConst618;
	double fConst619;
	double fConst620;
	double fConst621;
	double fConst622;
	double fConst623;
	double fRec129_perm[4];
	double fConst624;
	double fConst625;
	double fConst626;
	double fConst627;
	double fConst628;
	double fConst629;
	double fRec128_perm[4];
	double fConst630;
	double fConst631;
	double fConst632;
	double fConst633;
	double fConst634;
	double fConst635;
	double fRec127_perm[4];
	double fConst636;
	double fConst637;
	double fConst638;
	double fRec126_perm[4];
	double fConst639;
	double fConst640;
	double fConst641;
	double fRec139_perm[4];
	double fConst642;
	double fConst643;
	double fConst644;
	double fConst645;
	double fConst646;
	double fConst647;
	double fRec138_perm[4];
	double fConst648;
	double fConst649;
	double fConst650;
	double fConst651;
	double fConst652;
	double fRec137_perm[4];
	double fConst653;
	double fConst654;
	double fConst655;
	double fConst656;
	double fConst657;
	double fConst658;
	double fConst659;
	double fConst660;
	double fConst661;
	double fRec136_perm[4];
	double fConst662;
	double fConst663;
	double fConst664;
	double fConst665;
	double fConst666;
	double fConst667;
	double fRec135_perm[4];
	double fConst668;
	double fConst669;
	double fConst670;
	double fConst671;
	double fConst672;
	double fConst673;
	double fRec134_perm[4];
	double fConst674;
	double fConst675;
	double fConst676;
	double fRec133_perm[4];
	double fConst677;
	double fConst678;
	double fConst679;
	double fRec146_perm[4];
	double fConst680;
	double fConst681;
	double fConst682;
	double fConst683;
	double fConst684;
	double fConst685;
	double fRec145_perm[4];
	double fConst686;
	double fConst687;
	double fConst688;
	double fConst689;
	double fConst690;
	double fRec144_perm[4];
	double fConst691;
	double fConst692;
	double fConst693;
	double fConst694;
	double fConst695;
	double fConst696;
	double fConst697;
	double fConst698;
	double fConst699;
	double fRec143_perm[4];
	double fConst700;
	double fConst701;
	double fConst702;
	double fConst703;
	double fConst704;
	double fConst705;
	double fRec142_perm[4];
	double fConst706;
	double fConst707;
	double fConst708;
	double fConst709;
	double fConst710;
	double fConst711;
	double fRec141_perm[4];
	double fConst712;
	double fConst713;
	double fConst714;
	double fRec140_perm[4];
	double fConst715;
	double fConst716;
	double fConst717;
	double fRec150_perm[4];
	double fConst718;
	double fConst719;
	double fConst720;
	double fConst721;
	double fConst722;
	double fConst723;
	double fRec149_perm[4];
	double fConst724;
	double fConst725;
	double fConst726;
	double fConst727;
	double fConst728;
	double fRec148_perm[4];
	double fConst729;
	double fConst730;
	double fRec147_perm[4];
	FAUSTFLOAT fHslider8;
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
	FAUSTFLOAT fVbargraph15;
	FAUSTFLOAT fVbargraph16;
	FAUSTFLOAT fVbargraph17;
	FAUSTFLOAT fVbargraph18;
	FAUSTFLOAT fVbargraph19;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "parametric_eq.dsp");
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
		m->declare("name", "parametric_eq");
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
		fConst2 = 3.141592653589793 / fConst0;
		fConst3 = 0.25 * fConst0;
		fConst4 = 0.041666666666666664 * mydsp_faustpower2_f(fConst0);
		fConst5 = 0.005208333333333333 * mydsp_faustpower3_f(fConst0);
		fConst6 = 1382.300767579509 / fConst0;
		fConst7 = 2764.601535159018 / fConst0;
		fConst8 = std::tan(50265.48245743669 / fConst0);
		fConst9 = 1.0 / fConst8;
		fConst10 = 1.0 / ((fConst9 + 3.1897274020965583) / fConst8 + 4.076781969643807);
		fConst11 = (fConst9 + -3.1897274020965583) / fConst8 + 4.076781969643807;
		fConst12 = mydsp_faustpower2_f(fConst8);
		fConst13 = 1.0 / fConst12;
		fConst14 = 2.0 * (4.076781969643807 - fConst13);
		fConst15 = 0.0017661728399818856 / fConst12;
		fConst16 = fConst15 + 0.00040767818495825777;
		fConst17 = 2.0 * (0.00040767818495825777 - fConst15);
		fConst18 = 1.0 / ((fConst9 + 0.7431304601070396) / fConst8 + 1.450071084655647);
		fConst19 = (fConst9 + -0.7431304601070396) / fConst8 + 1.450071084655647;
		fConst20 = 2.0 * (1.450071084655647 - fConst13);
		fConst21 = 11.052052171507189 / fConst12;
		fConst22 = fConst21 + 1.450071084655647;
		fConst23 = 2.0 * (1.450071084655647 - fConst21);
		fConst24 = 1.0 / ((fConst9 + 0.157482159302087) / fConst8 + 0.9351401670315425);
		fConst25 = (fConst9 + -0.157482159302087) / fConst8 + 0.9351401670315425;
		fConst26 = 2.0 * (0.9351401670315425 - fConst13);
		fConst27 = 1e+03 / fConst0;
		fConst28 = 50.063807016150385 / fConst12;
		fConst29 = fConst28 + 0.9351401670315425;
		fConst30 = 2.0 * (0.9351401670315425 - fConst28);
		fConst31 = 1.0 / ((fConst9 + 0.782413046821645) / fConst8 + 0.24529150870616);
		fConst32 = (fConst9 + -0.782413046821645) / fConst8 + 0.24529150870616;
		fConst33 = 2.0 * (0.24529150870616 - fConst13);
		fConst34 = 9.9999997055e-05 / fConst12;
		fConst35 = fConst34 + 0.000433227200555;
		fConst36 = 2.0 * (0.000433227200555 - fConst34);
		fConst37 = 1.0 / ((fConst9 + 0.512478641889141) / fConst8 + 0.689621364484675);
		fConst38 = (fConst9 + -0.512478641889141) / fConst8 + 0.689621364484675;
		fConst39 = 2.0 * (0.689621364484675 - fConst13);
		fConst40 = fConst13 + 7.621731298870603;
		fConst41 = 2.0 * (7.621731298870603 - fConst13);
		fConst42 = 1.0 / ((fConst9 + 0.168404871113589) / fConst8 + 1.069358407707312);
		fConst43 = (fConst9 + -0.168404871113589) / fConst8 + 1.069358407707312;
		fConst44 = 2.0 * (1.069358407707312 - fConst13);
		fConst45 = fConst13 + 53.53615295455673;
		fConst46 = 2.0 * (53.53615295455673 - fConst13);
		fConst47 = std::tan(35543.06350526693 / fConst0);
		fConst48 = 1.0 / fConst47;
		fConst49 = 1.0 / ((fConst48 + 3.1897274020965583) / fConst47 + 4.076781969643807);
		fConst50 = (fConst48 + -3.1897274020965583) / fConst47 + 4.076781969643807;
		fConst51 = mydsp_faustpower2_f(fConst47);
		fConst52 = 1.0 / fConst51;
		fConst53 = 2.0 * (4.076781969643807 - fConst52);
		fConst54 = 0.0017661728399818856 / fConst51;
		fConst55 = fConst54 + 0.00040767818495825777;
		fConst56 = 2.0 * (0.00040767818495825777 - fConst54);
		fConst57 = 1.0 / ((fConst48 + 0.7431304601070396) / fConst47 + 1.450071084655647);
		fConst58 = (fConst48 + -0.7431304601070396) / fConst47 + 1.450071084655647;
		fConst59 = 2.0 * (1.450071084655647 - fConst52);
		fConst60 = 11.052052171507189 / fConst51;
		fConst61 = fConst60 + 1.450071084655647;
		fConst62 = 2.0 * (1.450071084655647 - fConst60);
		fConst63 = 1.0 / ((fConst48 + 0.157482159302087) / fConst47 + 0.9351401670315425);
		fConst64 = (fConst48 + -0.157482159302087) / fConst47 + 0.9351401670315425;
		fConst65 = 2.0 * (0.9351401670315425 - fConst52);
		fConst66 = 50.063807016150385 / fConst51;
		fConst67 = fConst66 + 0.9351401670315425;
		fConst68 = 2.0 * (0.9351401670315425 - fConst66);
		fConst69 = 1.0 / ((fConst48 + 0.782413046821645) / fConst47 + 0.24529150870616);
		fConst70 = (fConst48 + -0.782413046821645) / fConst47 + 0.24529150870616;
		fConst71 = 2.0 * (0.24529150870616 - fConst52);
		fConst72 = 9.9999997055e-05 / fConst51;
		fConst73 = fConst72 + 0.000433227200555;
		fConst74 = 2.0 * (0.000433227200555 - fConst72);
		fConst75 = 1.0 / ((fConst48 + 0.512478641889141) / fConst47 + 0.689621364484675);
		fConst76 = (fConst48 + -0.512478641889141) / fConst47 + 0.689621364484675;
		fConst77 = 2.0 * (0.689621364484675 - fConst52);
		fConst78 = fConst52 + 7.621731298870603;
		fConst79 = 2.0 * (7.621731298870603 - fConst52);
		fConst80 = 1.0 / ((fConst48 + 0.168404871113589) / fConst47 + 1.069358407707312);
		fConst81 = (fConst48 + -0.168404871113589) / fConst47 + 1.069358407707312;
		fConst82 = 2.0 * (1.069358407707312 - fConst52);
		fConst83 = fConst52 + 53.53615295455673;
		fConst84 = 2.0 * (53.53615295455673 - fConst52);
		fConst85 = std::tan(25132.741228718343 / fConst0);
		fConst86 = 1.0 / fConst85;
		fConst87 = 1.0 / ((fConst86 + 3.1897274020965583) / fConst85 + 4.076781969643807);
		fConst88 = (fConst86 + -3.1897274020965583) / fConst85 + 4.076781969643807;
		fConst89 = mydsp_faustpower2_f(fConst85);
		fConst90 = 1.0 / fConst89;
		fConst91 = 2.0 * (4.076781969643807 - fConst90);
		fConst92 = 0.0017661728399818856 / fConst89;
		fConst93 = fConst92 + 0.00040767818495825777;
		fConst94 = 2.0 * (0.00040767818495825777 - fConst92);
		fConst95 = 1.0 / ((fConst86 + 0.7431304601070396) / fConst85 + 1.450071084655647);
		fConst96 = (fConst86 + -0.7431304601070396) / fConst85 + 1.450071084655647;
		fConst97 = 2.0 * (1.450071084655647 - fConst90);
		fConst98 = 11.052052171507189 / fConst89;
		fConst99 = fConst98 + 1.450071084655647;
		fConst100 = 2.0 * (1.450071084655647 - fConst98);
		fConst101 = 1.0 / ((fConst86 + 0.157482159302087) / fConst85 + 0.9351401670315425);
		fConst102 = (fConst86 + -0.157482159302087) / fConst85 + 0.9351401670315425;
		fConst103 = 2.0 * (0.9351401670315425 - fConst90);
		fConst104 = 50.063807016150385 / fConst89;
		fConst105 = fConst104 + 0.9351401670315425;
		fConst106 = 2.0 * (0.9351401670315425 - fConst104);
		fConst107 = 1.0 / ((fConst86 + 0.782413046821645) / fConst85 + 0.24529150870616);
		fConst108 = (fConst86 + -0.782413046821645) / fConst85 + 0.24529150870616;
		fConst109 = 2.0 * (0.24529150870616 - fConst90);
		fConst110 = 9.9999997055e-05 / fConst89;
		fConst111 = fConst110 + 0.000433227200555;
		fConst112 = 2.0 * (0.000433227200555 - fConst110);
		fConst113 = 1.0 / ((fConst86 + 0.512478641889141) / fConst85 + 0.689621364484675);
		fConst114 = (fConst86 + -0.512478641889141) / fConst85 + 0.689621364484675;
		fConst115 = 2.0 * (0.689621364484675 - fConst90);
		fConst116 = fConst90 + 7.621731298870603;
		fConst117 = 2.0 * (7.621731298870603 - fConst90);
		fConst118 = 1.0 / ((fConst86 + 0.168404871113589) / fConst85 + 1.069358407707312);
		fConst119 = (fConst86 + -0.168404871113589) / fConst85 + 1.069358407707312;
		fConst120 = 2.0 * (1.069358407707312 - fConst90);
		fConst121 = fConst90 + 53.53615295455673;
		fConst122 = 2.0 * (53.53615295455673 - fConst90);
		fConst123 = std::tan(17771.531752633466 / fConst0);
		fConst124 = 1.0 / fConst123;
		fConst125 = 1.0 / ((fConst124 + 3.1897274020965583) / fConst123 + 4.076781969643807);
		fConst126 = (fConst124 + -3.1897274020965583) / fConst123 + 4.076781969643807;
		fConst127 = mydsp_faustpower2_f(fConst123);
		fConst128 = 1.0 / fConst127;
		fConst129 = 2.0 * (4.076781969643807 - fConst128);
		fConst130 = 0.0017661728399818856 / fConst127;
		fConst131 = fConst130 + 0.00040767818495825777;
		fConst132 = 2.0 * (0.00040767818495825777 - fConst130);
		fConst133 = 1.0 / ((fConst124 + 0.7431304601070396) / fConst123 + 1.450071084655647);
		fConst134 = (fConst124 + -0.7431304601070396) / fConst123 + 1.450071084655647;
		fConst135 = 2.0 * (1.450071084655647 - fConst128);
		fConst136 = 11.052052171507189 / fConst127;
		fConst137 = fConst136 + 1.450071084655647;
		fConst138 = 2.0 * (1.450071084655647 - fConst136);
		fConst139 = 1.0 / ((fConst124 + 0.157482159302087) / fConst123 + 0.9351401670315425);
		fConst140 = (fConst124 + -0.157482159302087) / fConst123 + 0.9351401670315425;
		fConst141 = 2.0 * (0.9351401670315425 - fConst128);
		fConst142 = 50.063807016150385 / fConst127;
		fConst143 = fConst142 + 0.9351401670315425;
		fConst144 = 2.0 * (0.9351401670315425 - fConst142);
		fConst145 = 1.0 / ((fConst124 + 0.782413046821645) / fConst123 + 0.24529150870616);
		fConst146 = (fConst124 + -0.782413046821645) / fConst123 + 0.24529150870616;
		fConst147 = 2.0 * (0.24529150870616 - fConst128);
		fConst148 = 9.9999997055e-05 / fConst127;
		fConst149 = fConst148 + 0.000433227200555;
		fConst150 = 2.0 * (0.000433227200555 - fConst148);
		fConst151 = 1.0 / ((fConst124 + 0.512478641889141) / fConst123 + 0.689621364484675);
		fConst152 = (fConst124 + -0.512478641889141) / fConst123 + 0.689621364484675;
		fConst153 = 2.0 * (0.689621364484675 - fConst128);
		fConst154 = fConst128 + 7.621731298870603;
		fConst155 = 2.0 * (7.621731298870603 - fConst128);
		fConst156 = 1.0 / ((fConst124 + 0.168404871113589) / fConst123 + 1.069358407707312);
		fConst157 = (fConst124 + -0.168404871113589) / fConst123 + 1.069358407707312;
		fConst158 = 2.0 * (1.069358407707312 - fConst128);
		fConst159 = fConst128 + 53.53615295455673;
		fConst160 = 2.0 * (53.53615295455673 - fConst128);
		fConst161 = std::tan(12566.370614359172 / fConst0);
		fConst162 = 1.0 / fConst161;
		fConst163 = 1.0 / ((fConst162 + 3.1897274020965583) / fConst161 + 4.076781969643807);
		fConst164 = (fConst162 + -3.1897274020965583) / fConst161 + 4.076781969643807;
		fConst165 = mydsp_faustpower2_f(fConst161);
		fConst166 = 1.0 / fConst165;
		fConst167 = 2.0 * (4.076781969643807 - fConst166);
		fConst168 = 0.0017661728399818856 / fConst165;
		fConst169 = fConst168 + 0.00040767818495825777;
		fConst170 = 2.0 * (0.00040767818495825777 - fConst168);
		fConst171 = 1.0 / ((fConst162 + 0.7431304601070396) / fConst161 + 1.450071084655647);
		fConst172 = (fConst162 + -0.7431304601070396) / fConst161 + 1.450071084655647;
		fConst173 = 2.0 * (1.450071084655647 - fConst166);
		fConst174 = 11.052052171507189 / fConst165;
		fConst175 = fConst174 + 1.450071084655647;
		fConst176 = 2.0 * (1.450071084655647 - fConst174);
		fConst177 = 1.0 / ((fConst162 + 0.157482159302087) / fConst161 + 0.9351401670315425);
		fConst178 = (fConst162 + -0.157482159302087) / fConst161 + 0.9351401670315425;
		fConst179 = 2.0 * (0.9351401670315425 - fConst166);
		fConst180 = 50.063807016150385 / fConst165;
		fConst181 = fConst180 + 0.9351401670315425;
		fConst182 = 2.0 * (0.9351401670315425 - fConst180);
		fConst183 = 1.0 / ((fConst162 + 0.782413046821645) / fConst161 + 0.24529150870616);
		fConst184 = (fConst162 + -0.782413046821645) / fConst161 + 0.24529150870616;
		fConst185 = 2.0 * (0.24529150870616 - fConst166);
		fConst186 = 9.9999997055e-05 / fConst165;
		fConst187 = fConst186 + 0.000433227200555;
		fConst188 = 2.0 * (0.000433227200555 - fConst186);
		fConst189 = 1.0 / ((fConst162 + 0.512478641889141) / fConst161 + 0.689621364484675);
		fConst190 = (fConst162 + -0.512478641889141) / fConst161 + 0.689621364484675;
		fConst191 = 2.0 * (0.689621364484675 - fConst166);
		fConst192 = fConst166 + 7.621731298870603;
		fConst193 = 2.0 * (7.621731298870603 - fConst166);
		fConst194 = 1.0 / ((fConst162 + 0.168404871113589) / fConst161 + 1.069358407707312);
		fConst195 = (fConst162 + -0.168404871113589) / fConst161 + 1.069358407707312;
		fConst196 = 2.0 * (1.069358407707312 - fConst166);
		fConst197 = fConst166 + 53.53615295455673;
		fConst198 = 2.0 * (53.53615295455673 - fConst166);
		fConst199 = std::tan(8885.765876316733 / fConst0);
		fConst200 = 1.0 / fConst199;
		fConst201 = 1.0 / ((fConst200 + 3.1897274020965583) / fConst199 + 4.076781969643807);
		fConst202 = (fConst200 + -3.1897274020965583) / fConst199 + 4.076781969643807;
		fConst203 = mydsp_faustpower2_f(fConst199);
		fConst204 = 1.0 / fConst203;
		fConst205 = 2.0 * (4.076781969643807 - fConst204);
		fConst206 = 0.0017661728399818856 / fConst203;
		fConst207 = fConst206 + 0.00040767818495825777;
		fConst208 = 2.0 * (0.00040767818495825777 - fConst206);
		fConst209 = 1.0 / ((fConst200 + 0.7431304601070396) / fConst199 + 1.450071084655647);
		fConst210 = (fConst200 + -0.7431304601070396) / fConst199 + 1.450071084655647;
		fConst211 = 2.0 * (1.450071084655647 - fConst204);
		fConst212 = 11.052052171507189 / fConst203;
		fConst213 = fConst212 + 1.450071084655647;
		fConst214 = 2.0 * (1.450071084655647 - fConst212);
		fConst215 = 1.0 / ((fConst200 + 0.157482159302087) / fConst199 + 0.9351401670315425);
		fConst216 = (fConst200 + -0.157482159302087) / fConst199 + 0.9351401670315425;
		fConst217 = 2.0 * (0.9351401670315425 - fConst204);
		fConst218 = 50.063807016150385 / fConst203;
		fConst219 = fConst218 + 0.9351401670315425;
		fConst220 = 2.0 * (0.9351401670315425 - fConst218);
		fConst221 = 1.0 / ((fConst200 + 0.782413046821645) / fConst199 + 0.24529150870616);
		fConst222 = (fConst200 + -0.782413046821645) / fConst199 + 0.24529150870616;
		fConst223 = 2.0 * (0.24529150870616 - fConst204);
		fConst224 = 9.9999997055e-05 / fConst203;
		fConst225 = fConst224 + 0.000433227200555;
		fConst226 = 2.0 * (0.000433227200555 - fConst224);
		fConst227 = 1.0 / ((fConst200 + 0.512478641889141) / fConst199 + 0.689621364484675);
		fConst228 = (fConst200 + -0.512478641889141) / fConst199 + 0.689621364484675;
		fConst229 = 2.0 * (0.689621364484675 - fConst204);
		fConst230 = fConst204 + 7.621731298870603;
		fConst231 = 2.0 * (7.621731298870603 - fConst204);
		fConst232 = 1.0 / ((fConst200 + 0.168404871113589) / fConst199 + 1.069358407707312);
		fConst233 = (fConst200 + -0.168404871113589) / fConst199 + 1.069358407707312;
		fConst234 = 2.0 * (1.069358407707312 - fConst204);
		fConst235 = fConst204 + 53.53615295455673;
		fConst236 = 2.0 * (53.53615295455673 - fConst204);
		fConst237 = std::tan(6283.185307179586 / fConst0);
		fConst238 = 1.0 / fConst237;
		fConst239 = 1.0 / ((fConst238 + 3.1897274020965583) / fConst237 + 4.076781969643807);
		fConst240 = (fConst238 + -3.1897274020965583) / fConst237 + 4.076781969643807;
		fConst241 = mydsp_faustpower2_f(fConst237);
		fConst242 = 1.0 / fConst241;
		fConst243 = 2.0 * (4.076781969643807 - fConst242);
		fConst244 = 0.0017661728399818856 / fConst241;
		fConst245 = fConst244 + 0.00040767818495825777;
		fConst246 = 2.0 * (0.00040767818495825777 - fConst244);
		fConst247 = 1.0 / ((fConst238 + 0.7431304601070396) / fConst237 + 1.450071084655647);
		fConst248 = (fConst238 + -0.7431304601070396) / fConst237 + 1.450071084655647;
		fConst249 = 2.0 * (1.450071084655647 - fConst242);
		fConst250 = 11.052052171507189 / fConst241;
		fConst251 = fConst250 + 1.450071084655647;
		fConst252 = 2.0 * (1.450071084655647 - fConst250);
		fConst253 = 1.0 / ((fConst238 + 0.157482159302087) / fConst237 + 0.9351401670315425);
		fConst254 = (fConst238 + -0.157482159302087) / fConst237 + 0.9351401670315425;
		fConst255 = 2.0 * (0.9351401670315425 - fConst242);
		fConst256 = 50.063807016150385 / fConst241;
		fConst257 = fConst256 + 0.9351401670315425;
		fConst258 = 2.0 * (0.9351401670315425 - fConst256);
		fConst259 = 1.0 / ((fConst238 + 0.782413046821645) / fConst237 + 0.24529150870616);
		fConst260 = (fConst238 + -0.782413046821645) / fConst237 + 0.24529150870616;
		fConst261 = 2.0 * (0.24529150870616 - fConst242);
		fConst262 = 9.9999997055e-05 / fConst241;
		fConst263 = fConst262 + 0.000433227200555;
		fConst264 = 2.0 * (0.000433227200555 - fConst262);
		fConst265 = 1.0 / ((fConst238 + 0.512478641889141) / fConst237 + 0.689621364484675);
		fConst266 = (fConst238 + -0.512478641889141) / fConst237 + 0.689621364484675;
		fConst267 = 2.0 * (0.689621364484675 - fConst242);
		fConst268 = fConst242 + 7.621731298870603;
		fConst269 = 2.0 * (7.621731298870603 - fConst242);
		fConst270 = 1.0 / ((fConst238 + 0.168404871113589) / fConst237 + 1.069358407707312);
		fConst271 = (fConst238 + -0.168404871113589) / fConst237 + 1.069358407707312;
		fConst272 = 2.0 * (1.069358407707312 - fConst242);
		fConst273 = fConst242 + 53.53615295455673;
		fConst274 = 2.0 * (53.53615295455673 - fConst242);
		fConst275 = std::tan(4442.882938158366 / fConst0);
		fConst276 = 1.0 / fConst275;
		fConst277 = 1.0 / ((fConst276 + 3.1897274020965583) / fConst275 + 4.076781969643807);
		fConst278 = (fConst276 + -3.1897274020965583) / fConst275 + 4.076781969643807;
		fConst279 = mydsp_faustpower2_f(fConst275);
		fConst280 = 1.0 / fConst279;
		fConst281 = 2.0 * (4.076781969643807 - fConst280);
		fConst282 = 0.0017661728399818856 / fConst279;
		fConst283 = fConst282 + 0.00040767818495825777;
		fConst284 = 2.0 * (0.00040767818495825777 - fConst282);
		fConst285 = 1.0 / ((fConst276 + 0.7431304601070396) / fConst275 + 1.450071084655647);
		fConst286 = (fConst276 + -0.7431304601070396) / fConst275 + 1.450071084655647;
		fConst287 = 2.0 * (1.450071084655647 - fConst280);
		fConst288 = 11.052052171507189 / fConst279;
		fConst289 = fConst288 + 1.450071084655647;
		fConst290 = 2.0 * (1.450071084655647 - fConst288);
		fConst291 = 1.0 / ((fConst276 + 0.157482159302087) / fConst275 + 0.9351401670315425);
		fConst292 = (fConst276 + -0.157482159302087) / fConst275 + 0.9351401670315425;
		fConst293 = 2.0 * (0.9351401670315425 - fConst280);
		fConst294 = 50.063807016150385 / fConst279;
		fConst295 = fConst294 + 0.9351401670315425;
		fConst296 = 2.0 * (0.9351401670315425 - fConst294);
		fConst297 = 1.0 / ((fConst276 + 0.782413046821645) / fConst275 + 0.24529150870616);
		fConst298 = (fConst276 + -0.782413046821645) / fConst275 + 0.24529150870616;
		fConst299 = 2.0 * (0.24529150870616 - fConst280);
		fConst300 = 9.9999997055e-05 / fConst279;
		fConst301 = fConst300 + 0.000433227200555;
		fConst302 = 2.0 * (0.000433227200555 - fConst300);
		fConst303 = 1.0 / ((fConst276 + 0.512478641889141) / fConst275 + 0.689621364484675);
		fConst304 = (fConst276 + -0.512478641889141) / fConst275 + 0.689621364484675;
		fConst305 = 2.0 * (0.689621364484675 - fConst280);
		fConst306 = fConst280 + 7.621731298870603;
		fConst307 = 2.0 * (7.621731298870603 - fConst280);
		fConst308 = 1.0 / ((fConst276 + 0.168404871113589) / fConst275 + 1.069358407707312);
		fConst309 = (fConst276 + -0.168404871113589) / fConst275 + 1.069358407707312;
		fConst310 = 2.0 * (1.069358407707312 - fConst280);
		fConst311 = fConst280 + 53.53615295455673;
		fConst312 = 2.0 * (53.53615295455673 - fConst280);
		fConst313 = std::tan(3141.592653589793 / fConst0);
		fConst314 = 1.0 / fConst313;
		fConst315 = 1.0 / ((fConst314 + 3.1897274020965583) / fConst313 + 4.076781969643807);
		fConst316 = (fConst314 + -3.1897274020965583) / fConst313 + 4.076781969643807;
		fConst317 = mydsp_faustpower2_f(fConst313);
		fConst318 = 1.0 / fConst317;
		fConst319 = 2.0 * (4.076781969643807 - fConst318);
		fConst320 = 0.0017661728399818856 / fConst317;
		fConst321 = fConst320 + 0.00040767818495825777;
		fConst322 = 2.0 * (0.00040767818495825777 - fConst320);
		fConst323 = 1.0 / ((fConst314 + 0.7431304601070396) / fConst313 + 1.450071084655647);
		fConst324 = (fConst314 + -0.7431304601070396) / fConst313 + 1.450071084655647;
		fConst325 = 2.0 * (1.450071084655647 - fConst318);
		fConst326 = 11.052052171507189 / fConst317;
		fConst327 = fConst326 + 1.450071084655647;
		fConst328 = 2.0 * (1.450071084655647 - fConst326);
		fConst329 = 1.0 / ((fConst314 + 0.157482159302087) / fConst313 + 0.9351401670315425);
		fConst330 = (fConst314 + -0.157482159302087) / fConst313 + 0.9351401670315425;
		fConst331 = 2.0 * (0.9351401670315425 - fConst318);
		fConst332 = 50.063807016150385 / fConst317;
		fConst333 = fConst332 + 0.9351401670315425;
		fConst334 = 2.0 * (0.9351401670315425 - fConst332);
		fConst335 = 1.0 / ((fConst314 + 0.782413046821645) / fConst313 + 0.24529150870616);
		fConst336 = (fConst314 + -0.782413046821645) / fConst313 + 0.24529150870616;
		fConst337 = 2.0 * (0.24529150870616 - fConst318);
		fConst338 = 9.9999997055e-05 / fConst317;
		fConst339 = fConst338 + 0.000433227200555;
		fConst340 = 2.0 * (0.000433227200555 - fConst338);
		fConst341 = 1.0 / ((fConst314 + 0.512478641889141) / fConst313 + 0.689621364484675);
		fConst342 = (fConst314 + -0.512478641889141) / fConst313 + 0.689621364484675;
		fConst343 = 2.0 * (0.689621364484675 - fConst318);
		fConst344 = fConst318 + 7.621731298870603;
		fConst345 = 2.0 * (7.621731298870603 - fConst318);
		fConst346 = 1.0 / ((fConst314 + 0.168404871113589) / fConst313 + 1.069358407707312);
		fConst347 = (fConst314 + -0.168404871113589) / fConst313 + 1.069358407707312;
		fConst348 = 2.0 * (1.069358407707312 - fConst318);
		fConst349 = fConst318 + 53.53615295455673;
		fConst350 = 2.0 * (53.53615295455673 - fConst318);
		fConst351 = std::tan(2221.441469079183 / fConst0);
		fConst352 = 1.0 / fConst351;
		fConst353 = 1.0 / ((fConst352 + 3.1897274020965583) / fConst351 + 4.076781969643807);
		fConst354 = (fConst352 + -3.1897274020965583) / fConst351 + 4.076781969643807;
		fConst355 = mydsp_faustpower2_f(fConst351);
		fConst356 = 1.0 / fConst355;
		fConst357 = 2.0 * (4.076781969643807 - fConst356);
		fConst358 = 0.0017661728399818856 / fConst355;
		fConst359 = fConst358 + 0.00040767818495825777;
		fConst360 = 2.0 * (0.00040767818495825777 - fConst358);
		fConst361 = 1.0 / ((fConst352 + 0.7431304601070396) / fConst351 + 1.450071084655647);
		fConst362 = (fConst352 + -0.7431304601070396) / fConst351 + 1.450071084655647;
		fConst363 = 2.0 * (1.450071084655647 - fConst356);
		fConst364 = 11.052052171507189 / fConst355;
		fConst365 = fConst364 + 1.450071084655647;
		fConst366 = 2.0 * (1.450071084655647 - fConst364);
		fConst367 = 1.0 / ((fConst352 + 0.157482159302087) / fConst351 + 0.9351401670315425);
		fConst368 = (fConst352 + -0.157482159302087) / fConst351 + 0.9351401670315425;
		fConst369 = 2.0 * (0.9351401670315425 - fConst356);
		fConst370 = 50.063807016150385 / fConst355;
		fConst371 = fConst370 + 0.9351401670315425;
		fConst372 = 2.0 * (0.9351401670315425 - fConst370);
		fConst373 = 1.0 / ((fConst352 + 0.782413046821645) / fConst351 + 0.24529150870616);
		fConst374 = (fConst352 + -0.782413046821645) / fConst351 + 0.24529150870616;
		fConst375 = 2.0 * (0.24529150870616 - fConst356);
		fConst376 = 9.9999997055e-05 / fConst355;
		fConst377 = fConst376 + 0.000433227200555;
		fConst378 = 2.0 * (0.000433227200555 - fConst376);
		fConst379 = 1.0 / ((fConst352 + 0.512478641889141) / fConst351 + 0.689621364484675);
		fConst380 = (fConst352 + -0.512478641889141) / fConst351 + 0.689621364484675;
		fConst381 = 2.0 * (0.689621364484675 - fConst356);
		fConst382 = fConst356 + 7.621731298870603;
		fConst383 = 2.0 * (7.621731298870603 - fConst356);
		fConst384 = 1.0 / ((fConst352 + 0.168404871113589) / fConst351 + 1.069358407707312);
		fConst385 = (fConst352 + -0.168404871113589) / fConst351 + 1.069358407707312;
		fConst386 = 2.0 * (1.069358407707312 - fConst356);
		fConst387 = fConst356 + 53.53615295455673;
		fConst388 = 2.0 * (53.53615295455673 - fConst356);
		fConst389 = std::tan(1570.7963267948965 / fConst0);
		fConst390 = 1.0 / fConst389;
		fConst391 = 1.0 / ((fConst390 + 3.1897274020965583) / fConst389 + 4.076781969643807);
		fConst392 = (fConst390 + -3.1897274020965583) / fConst389 + 4.076781969643807;
		fConst393 = mydsp_faustpower2_f(fConst389);
		fConst394 = 1.0 / fConst393;
		fConst395 = 2.0 * (4.076781969643807 - fConst394);
		fConst396 = 0.0017661728399818856 / fConst393;
		fConst397 = fConst396 + 0.00040767818495825777;
		fConst398 = 2.0 * (0.00040767818495825777 - fConst396);
		fConst399 = 1.0 / ((fConst390 + 0.7431304601070396) / fConst389 + 1.450071084655647);
		fConst400 = (fConst390 + -0.7431304601070396) / fConst389 + 1.450071084655647;
		fConst401 = 2.0 * (1.450071084655647 - fConst394);
		fConst402 = 11.052052171507189 / fConst393;
		fConst403 = fConst402 + 1.450071084655647;
		fConst404 = 2.0 * (1.450071084655647 - fConst402);
		fConst405 = 1.0 / ((fConst390 + 0.157482159302087) / fConst389 + 0.9351401670315425);
		fConst406 = (fConst390 + -0.157482159302087) / fConst389 + 0.9351401670315425;
		fConst407 = 2.0 * (0.9351401670315425 - fConst394);
		fConst408 = 50.063807016150385 / fConst393;
		fConst409 = fConst408 + 0.9351401670315425;
		fConst410 = 2.0 * (0.9351401670315425 - fConst408);
		fConst411 = 1.0 / ((fConst390 + 0.782413046821645) / fConst389 + 0.24529150870616);
		fConst412 = (fConst390 + -0.782413046821645) / fConst389 + 0.24529150870616;
		fConst413 = 2.0 * (0.24529150870616 - fConst394);
		fConst414 = 9.9999997055e-05 / fConst393;
		fConst415 = fConst414 + 0.000433227200555;
		fConst416 = 2.0 * (0.000433227200555 - fConst414);
		fConst417 = 1.0 / ((fConst390 + 0.512478641889141) / fConst389 + 0.689621364484675);
		fConst418 = (fConst390 + -0.512478641889141) / fConst389 + 0.689621364484675;
		fConst419 = 2.0 * (0.689621364484675 - fConst394);
		fConst420 = fConst394 + 7.621731298870603;
		fConst421 = 2.0 * (7.621731298870603 - fConst394);
		fConst422 = 1.0 / ((fConst390 + 0.168404871113589) / fConst389 + 1.069358407707312);
		fConst423 = (fConst390 + -0.168404871113589) / fConst389 + 1.069358407707312;
		fConst424 = 2.0 * (1.069358407707312 - fConst394);
		fConst425 = fConst394 + 53.53615295455673;
		fConst426 = 2.0 * (53.53615295455673 - fConst394);
		fConst427 = std::tan(1110.7207345395916 / fConst0);
		fConst428 = 1.0 / fConst427;
		fConst429 = 1.0 / ((fConst428 + 3.1897274020965583) / fConst427 + 4.076781969643807);
		fConst430 = (fConst428 + -3.1897274020965583) / fConst427 + 4.076781969643807;
		fConst431 = mydsp_faustpower2_f(fConst427);
		fConst432 = 1.0 / fConst431;
		fConst433 = 2.0 * (4.076781969643807 - fConst432);
		fConst434 = 0.0017661728399818856 / fConst431;
		fConst435 = fConst434 + 0.00040767818495825777;
		fConst436 = 2.0 * (0.00040767818495825777 - fConst434);
		fConst437 = 1.0 / ((fConst428 + 0.7431304601070396) / fConst427 + 1.450071084655647);
		fConst438 = (fConst428 + -0.7431304601070396) / fConst427 + 1.450071084655647;
		fConst439 = 2.0 * (1.450071084655647 - fConst432);
		fConst440 = 11.052052171507189 / fConst431;
		fConst441 = fConst440 + 1.450071084655647;
		fConst442 = 2.0 * (1.450071084655647 - fConst440);
		fConst443 = 1.0 / ((fConst428 + 0.157482159302087) / fConst427 + 0.9351401670315425);
		fConst444 = (fConst428 + -0.157482159302087) / fConst427 + 0.9351401670315425;
		fConst445 = 2.0 * (0.9351401670315425 - fConst432);
		fConst446 = 50.063807016150385 / fConst431;
		fConst447 = fConst446 + 0.9351401670315425;
		fConst448 = 2.0 * (0.9351401670315425 - fConst446);
		fConst449 = 1.0 / ((fConst428 + 0.782413046821645) / fConst427 + 0.24529150870616);
		fConst450 = (fConst428 + -0.782413046821645) / fConst427 + 0.24529150870616;
		fConst451 = 2.0 * (0.24529150870616 - fConst432);
		fConst452 = 9.9999997055e-05 / fConst431;
		fConst453 = fConst452 + 0.000433227200555;
		fConst454 = 2.0 * (0.000433227200555 - fConst452);
		fConst455 = 1.0 / ((fConst428 + 0.512478641889141) / fConst427 + 0.689621364484675);
		fConst456 = (fConst428 + -0.512478641889141) / fConst427 + 0.689621364484675;
		fConst457 = 2.0 * (0.689621364484675 - fConst432);
		fConst458 = fConst432 + 7.621731298870603;
		fConst459 = 2.0 * (7.621731298870603 - fConst432);
		fConst460 = 1.0 / ((fConst428 + 0.168404871113589) / fConst427 + 1.069358407707312);
		fConst461 = (fConst428 + -0.168404871113589) / fConst427 + 1.069358407707312;
		fConst462 = 2.0 * (1.069358407707312 - fConst432);
		fConst463 = fConst432 + 53.53615295455673;
		fConst464 = 2.0 * (53.53615295455673 - fConst432);
		fConst465 = std::tan(785.3981633974482 / fConst0);
		fConst466 = 1.0 / fConst465;
		fConst467 = 1.0 / ((fConst466 + 3.1897274020965583) / fConst465 + 4.076781969643807);
		fConst468 = (fConst466 + -3.1897274020965583) / fConst465 + 4.076781969643807;
		fConst469 = mydsp_faustpower2_f(fConst465);
		fConst470 = 1.0 / fConst469;
		fConst471 = 2.0 * (4.076781969643807 - fConst470);
		fConst472 = 0.0017661728399818856 / fConst469;
		fConst473 = fConst472 + 0.00040767818495825777;
		fConst474 = 2.0 * (0.00040767818495825777 - fConst472);
		fConst475 = 1.0 / ((fConst466 + 0.7431304601070396) / fConst465 + 1.450071084655647);
		fConst476 = (fConst466 + -0.7431304601070396) / fConst465 + 1.450071084655647;
		fConst477 = 2.0 * (1.450071084655647 - fConst470);
		fConst478 = 11.052052171507189 / fConst469;
		fConst479 = fConst478 + 1.450071084655647;
		fConst480 = 2.0 * (1.450071084655647 - fConst478);
		fConst481 = 1.0 / ((fConst466 + 0.157482159302087) / fConst465 + 0.9351401670315425);
		fConst482 = (fConst466 + -0.157482159302087) / fConst465 + 0.9351401670315425;
		fConst483 = 2.0 * (0.9351401670315425 - fConst470);
		fConst484 = 50.063807016150385 / fConst469;
		fConst485 = fConst484 + 0.9351401670315425;
		fConst486 = 2.0 * (0.9351401670315425 - fConst484);
		fConst487 = 1.0 / ((fConst466 + 0.782413046821645) / fConst465 + 0.24529150870616);
		fConst488 = (fConst466 + -0.782413046821645) / fConst465 + 0.24529150870616;
		fConst489 = 2.0 * (0.24529150870616 - fConst470);
		fConst490 = 9.9999997055e-05 / fConst469;
		fConst491 = fConst490 + 0.000433227200555;
		fConst492 = 2.0 * (0.000433227200555 - fConst490);
		fConst493 = 1.0 / ((fConst466 + 0.512478641889141) / fConst465 + 0.689621364484675);
		fConst494 = (fConst466 + -0.512478641889141) / fConst465 + 0.689621364484675;
		fConst495 = 2.0 * (0.689621364484675 - fConst470);
		fConst496 = fConst470 + 7.621731298870603;
		fConst497 = 2.0 * (7.621731298870603 - fConst470);
		fConst498 = 1.0 / ((fConst466 + 0.168404871113589) / fConst465 + 1.069358407707312);
		fConst499 = (fConst466 + -0.168404871113589) / fConst465 + 1.069358407707312;
		fConst500 = 2.0 * (1.069358407707312 - fConst470);
		fConst501 = fConst470 + 53.53615295455673;
		fConst502 = 2.0 * (53.53615295455673 - fConst470);
		fConst503 = std::tan(555.3603672697958 / fConst0);
		fConst504 = 1.0 / fConst503;
		fConst505 = 1.0 / ((fConst504 + 3.1897274020965583) / fConst503 + 4.076781969643807);
		fConst506 = (fConst504 + -3.1897274020965583) / fConst503 + 4.076781969643807;
		fConst507 = mydsp_faustpower2_f(fConst503);
		fConst508 = 1.0 / fConst507;
		fConst509 = 2.0 * (4.076781969643807 - fConst508);
		fConst510 = 0.0017661728399818856 / fConst507;
		fConst511 = fConst510 + 0.00040767818495825777;
		fConst512 = 2.0 * (0.00040767818495825777 - fConst510);
		fConst513 = 1.0 / ((fConst504 + 0.7431304601070396) / fConst503 + 1.450071084655647);
		fConst514 = (fConst504 + -0.7431304601070396) / fConst503 + 1.450071084655647;
		fConst515 = 2.0 * (1.450071084655647 - fConst508);
		fConst516 = 11.052052171507189 / fConst507;
		fConst517 = fConst516 + 1.450071084655647;
		fConst518 = 2.0 * (1.450071084655647 - fConst516);
		fConst519 = 1.0 / ((fConst504 + 0.157482159302087) / fConst503 + 0.9351401670315425);
		fConst520 = (fConst504 + -0.157482159302087) / fConst503 + 0.9351401670315425;
		fConst521 = 2.0 * (0.9351401670315425 - fConst508);
		fConst522 = 50.063807016150385 / fConst507;
		fConst523 = fConst522 + 0.9351401670315425;
		fConst524 = 2.0 * (0.9351401670315425 - fConst522);
		fConst525 = 1.0 / ((fConst504 + 0.782413046821645) / fConst503 + 0.24529150870616);
		fConst526 = (fConst504 + -0.782413046821645) / fConst503 + 0.24529150870616;
		fConst527 = 2.0 * (0.24529150870616 - fConst508);
		fConst528 = 9.9999997055e-05 / fConst507;
		fConst529 = fConst528 + 0.000433227200555;
		fConst530 = 2.0 * (0.000433227200555 - fConst528);
		fConst531 = 1.0 / ((fConst504 + 0.512478641889141) / fConst503 + 0.689621364484675);
		fConst532 = (fConst504 + -0.512478641889141) / fConst503 + 0.689621364484675;
		fConst533 = 2.0 * (0.689621364484675 - fConst508);
		fConst534 = fConst508 + 7.621731298870603;
		fConst535 = 2.0 * (7.621731298870603 - fConst508);
		fConst536 = 1.0 / ((fConst504 + 0.168404871113589) / fConst503 + 1.069358407707312);
		fConst537 = (fConst504 + -0.168404871113589) / fConst503 + 1.069358407707312;
		fConst538 = 2.0 * (1.069358407707312 - fConst508);
		fConst539 = fConst508 + 53.53615295455673;
		fConst540 = 2.0 * (53.53615295455673 - fConst508);
		fConst541 = std::tan(392.6990816987241 / fConst0);
		fConst542 = 1.0 / fConst541;
		fConst543 = 1.0 / ((fConst542 + 3.1897274020965583) / fConst541 + 4.076781969643807);
		fConst544 = (fConst542 + -3.1897274020965583) / fConst541 + 4.076781969643807;
		fConst545 = mydsp_faustpower2_f(fConst541);
		fConst546 = 1.0 / fConst545;
		fConst547 = 2.0 * (4.076781969643807 - fConst546);
		fConst548 = 0.0017661728399818856 / fConst545;
		fConst549 = fConst548 + 0.00040767818495825777;
		fConst550 = 2.0 * (0.00040767818495825777 - fConst548);
		fConst551 = 1.0 / ((fConst542 + 0.7431304601070396) / fConst541 + 1.450071084655647);
		fConst552 = (fConst542 + -0.7431304601070396) / fConst541 + 1.450071084655647;
		fConst553 = 2.0 * (1.450071084655647 - fConst546);
		fConst554 = 11.052052171507189 / fConst545;
		fConst555 = fConst554 + 1.450071084655647;
		fConst556 = 2.0 * (1.450071084655647 - fConst554);
		fConst557 = 1.0 / ((fConst542 + 0.157482159302087) / fConst541 + 0.9351401670315425);
		fConst558 = (fConst542 + -0.157482159302087) / fConst541 + 0.9351401670315425;
		fConst559 = 2.0 * (0.9351401670315425 - fConst546);
		fConst560 = 50.063807016150385 / fConst545;
		fConst561 = fConst560 + 0.9351401670315425;
		fConst562 = 2.0 * (0.9351401670315425 - fConst560);
		fConst563 = 1.0 / ((fConst542 + 0.782413046821645) / fConst541 + 0.24529150870616);
		fConst564 = (fConst542 + -0.782413046821645) / fConst541 + 0.24529150870616;
		fConst565 = 2.0 * (0.24529150870616 - fConst546);
		fConst566 = 9.9999997055e-05 / fConst545;
		fConst567 = fConst566 + 0.000433227200555;
		fConst568 = 2.0 * (0.000433227200555 - fConst566);
		fConst569 = 1.0 / ((fConst542 + 0.512478641889141) / fConst541 + 0.689621364484675);
		fConst570 = (fConst542 + -0.512478641889141) / fConst541 + 0.689621364484675;
		fConst571 = 2.0 * (0.689621364484675 - fConst546);
		fConst572 = fConst546 + 7.621731298870603;
		fConst573 = 2.0 * (7.621731298870603 - fConst546);
		fConst574 = 1.0 / ((fConst542 + 0.168404871113589) / fConst541 + 1.069358407707312);
		fConst575 = (fConst542 + -0.168404871113589) / fConst541 + 1.069358407707312;
		fConst576 = 2.0 * (1.069358407707312 - fConst546);
		fConst577 = fConst546 + 53.53615295455673;
		fConst578 = 2.0 * (53.53615295455673 - fConst546);
		fConst579 = std::tan(277.6801836348979 / fConst0);
		fConst580 = 1.0 / fConst579;
		fConst581 = 1.0 / ((fConst580 + 3.1897274020965583) / fConst579 + 4.076781969643807);
		fConst582 = (fConst580 + -3.1897274020965583) / fConst579 + 4.076781969643807;
		fConst583 = mydsp_faustpower2_f(fConst579);
		fConst584 = 1.0 / fConst583;
		fConst585 = 2.0 * (4.076781969643807 - fConst584);
		fConst586 = 0.0017661728399818856 / fConst583;
		fConst587 = fConst586 + 0.00040767818495825777;
		fConst588 = 2.0 * (0.00040767818495825777 - fConst586);
		fConst589 = 1.0 / ((fConst580 + 0.7431304601070396) / fConst579 + 1.450071084655647);
		fConst590 = (fConst580 + -0.7431304601070396) / fConst579 + 1.450071084655647;
		fConst591 = 2.0 * (1.450071084655647 - fConst584);
		fConst592 = 11.052052171507189 / fConst583;
		fConst593 = fConst592 + 1.450071084655647;
		fConst594 = 2.0 * (1.450071084655647 - fConst592);
		fConst595 = 1.0 / ((fConst580 + 0.157482159302087) / fConst579 + 0.9351401670315425);
		fConst596 = (fConst580 + -0.157482159302087) / fConst579 + 0.9351401670315425;
		fConst597 = 2.0 * (0.9351401670315425 - fConst584);
		fConst598 = 50.063807016150385 / fConst583;
		fConst599 = fConst598 + 0.9351401670315425;
		fConst600 = 2.0 * (0.9351401670315425 - fConst598);
		fConst601 = 1.0 / ((fConst580 + 0.782413046821645) / fConst579 + 0.24529150870616);
		fConst602 = (fConst580 + -0.782413046821645) / fConst579 + 0.24529150870616;
		fConst603 = 2.0 * (0.24529150870616 - fConst584);
		fConst604 = 9.9999997055e-05 / fConst583;
		fConst605 = fConst604 + 0.000433227200555;
		fConst606 = 2.0 * (0.000433227200555 - fConst604);
		fConst607 = 1.0 / ((fConst580 + 0.512478641889141) / fConst579 + 0.689621364484675);
		fConst608 = (fConst580 + -0.512478641889141) / fConst579 + 0.689621364484675;
		fConst609 = 2.0 * (0.689621364484675 - fConst584);
		fConst610 = fConst584 + 7.621731298870603;
		fConst611 = 2.0 * (7.621731298870603 - fConst584);
		fConst612 = 1.0 / ((fConst580 + 0.168404871113589) / fConst579 + 1.069358407707312);
		fConst613 = (fConst580 + -0.168404871113589) / fConst579 + 1.069358407707312;
		fConst614 = 2.0 * (1.069358407707312 - fConst584);
		fConst615 = fConst584 + 53.53615295455673;
		fConst616 = 2.0 * (53.53615295455673 - fConst584);
		fConst617 = std::tan(196.34954084936206 / fConst0);
		fConst618 = 1.0 / fConst617;
		fConst619 = 1.0 / ((fConst618 + 3.1897274020965583) / fConst617 + 4.076781969643807);
		fConst620 = (fConst618 + -3.1897274020965583) / fConst617 + 4.076781969643807;
		fConst621 = mydsp_faustpower2_f(fConst617);
		fConst622 = 1.0 / fConst621;
		fConst623 = 2.0 * (4.076781969643807 - fConst622);
		fConst624 = 0.0017661728399818856 / fConst621;
		fConst625 = fConst624 + 0.00040767818495825777;
		fConst626 = 2.0 * (0.00040767818495825777 - fConst624);
		fConst627 = 1.0 / ((fConst618 + 0.7431304601070396) / fConst617 + 1.450071084655647);
		fConst628 = (fConst618 + -0.7431304601070396) / fConst617 + 1.450071084655647;
		fConst629 = 2.0 * (1.450071084655647 - fConst622);
		fConst630 = 11.052052171507189 / fConst621;
		fConst631 = fConst630 + 1.450071084655647;
		fConst632 = 2.0 * (1.450071084655647 - fConst630);
		fConst633 = 1.0 / ((fConst618 + 0.157482159302087) / fConst617 + 0.9351401670315425);
		fConst634 = (fConst618 + -0.157482159302087) / fConst617 + 0.9351401670315425;
		fConst635 = 2.0 * (0.9351401670315425 - fConst622);
		fConst636 = 50.063807016150385 / fConst621;
		fConst637 = fConst636 + 0.9351401670315425;
		fConst638 = 2.0 * (0.9351401670315425 - fConst636);
		fConst639 = 1.0 / ((fConst618 + 0.782413046821645) / fConst617 + 0.24529150870616);
		fConst640 = (fConst618 + -0.782413046821645) / fConst617 + 0.24529150870616;
		fConst641 = 2.0 * (0.24529150870616 - fConst622);
		fConst642 = 9.9999997055e-05 / fConst621;
		fConst643 = fConst642 + 0.000433227200555;
		fConst644 = 2.0 * (0.000433227200555 - fConst642);
		fConst645 = 1.0 / ((fConst618 + 0.512478641889141) / fConst617 + 0.689621364484675);
		fConst646 = (fConst618 + -0.512478641889141) / fConst617 + 0.689621364484675;
		fConst647 = 2.0 * (0.689621364484675 - fConst622);
		fConst648 = fConst622 + 7.621731298870603;
		fConst649 = 2.0 * (7.621731298870603 - fConst622);
		fConst650 = 1.0 / ((fConst618 + 0.168404871113589) / fConst617 + 1.069358407707312);
		fConst651 = (fConst618 + -0.168404871113589) / fConst617 + 1.069358407707312;
		fConst652 = 2.0 * (1.069358407707312 - fConst622);
		fConst653 = fConst622 + 53.53615295455673;
		fConst654 = 2.0 * (53.53615295455673 - fConst622);
		fConst655 = std::tan(138.84009181744895 / fConst0);
		fConst656 = 1.0 / fConst655;
		fConst657 = 1.0 / ((fConst656 + 3.1897274020965583) / fConst655 + 4.076781969643807);
		fConst658 = (fConst656 + -3.1897274020965583) / fConst655 + 4.076781969643807;
		fConst659 = mydsp_faustpower2_f(fConst655);
		fConst660 = 1.0 / fConst659;
		fConst661 = 2.0 * (4.076781969643807 - fConst660);
		fConst662 = 0.0017661728399818856 / fConst659;
		fConst663 = fConst662 + 0.00040767818495825777;
		fConst664 = 2.0 * (0.00040767818495825777 - fConst662);
		fConst665 = 1.0 / ((fConst656 + 0.7431304601070396) / fConst655 + 1.450071084655647);
		fConst666 = (fConst656 + -0.7431304601070396) / fConst655 + 1.450071084655647;
		fConst667 = 2.0 * (1.450071084655647 - fConst660);
		fConst668 = 11.052052171507189 / fConst659;
		fConst669 = fConst668 + 1.450071084655647;
		fConst670 = 2.0 * (1.450071084655647 - fConst668);
		fConst671 = 1.0 / ((fConst656 + 0.157482159302087) / fConst655 + 0.9351401670315425);
		fConst672 = (fConst656 + -0.157482159302087) / fConst655 + 0.9351401670315425;
		fConst673 = 2.0 * (0.9351401670315425 - fConst660);
		fConst674 = 50.063807016150385 / fConst659;
		fConst675 = fConst674 + 0.9351401670315425;
		fConst676 = 2.0 * (0.9351401670315425 - fConst674);
		fConst677 = 1.0 / ((fConst656 + 0.782413046821645) / fConst655 + 0.24529150870616);
		fConst678 = (fConst656 + -0.782413046821645) / fConst655 + 0.24529150870616;
		fConst679 = 2.0 * (0.24529150870616 - fConst660);
		fConst680 = 9.9999997055e-05 / fConst659;
		fConst681 = fConst680 + 0.000433227200555;
		fConst682 = 2.0 * (0.000433227200555 - fConst680);
		fConst683 = 1.0 / ((fConst656 + 0.512478641889141) / fConst655 + 0.689621364484675);
		fConst684 = (fConst656 + -0.512478641889141) / fConst655 + 0.689621364484675;
		fConst685 = 2.0 * (0.689621364484675 - fConst660);
		fConst686 = fConst660 + 7.621731298870603;
		fConst687 = 2.0 * (7.621731298870603 - fConst660);
		fConst688 = 1.0 / ((fConst656 + 0.168404871113589) / fConst655 + 1.069358407707312);
		fConst689 = (fConst656 + -0.168404871113589) / fConst655 + 1.069358407707312;
		fConst690 = 2.0 * (1.069358407707312 - fConst660);
		fConst691 = fConst660 + 53.53615295455673;
		fConst692 = 2.0 * (53.53615295455673 - fConst660);
		fConst693 = std::tan(98.17477042468103 / fConst0);
		fConst694 = 1.0 / fConst693;
		fConst695 = 1.0 / ((fConst694 + 3.1897274020965583) / fConst693 + 4.076781969643807);
		fConst696 = (fConst694 + -3.1897274020965583) / fConst693 + 4.076781969643807;
		fConst697 = mydsp_faustpower2_f(fConst693);
		fConst698 = 1.0 / fConst697;
		fConst699 = 2.0 * (4.076781969643807 - fConst698);
		fConst700 = 0.0017661728399818856 / fConst697;
		fConst701 = fConst700 + 0.00040767818495825777;
		fConst702 = 2.0 * (0.00040767818495825777 - fConst700);
		fConst703 = 1.0 / ((fConst694 + 0.7431304601070396) / fConst693 + 1.450071084655647);
		fConst704 = (fConst694 + -0.7431304601070396) / fConst693 + 1.450071084655647;
		fConst705 = 2.0 * (1.450071084655647 - fConst698);
		fConst706 = 11.052052171507189 / fConst697;
		fConst707 = fConst706 + 1.450071084655647;
		fConst708 = 2.0 * (1.450071084655647 - fConst706);
		fConst709 = 1.0 / ((fConst694 + 0.157482159302087) / fConst693 + 0.9351401670315425);
		fConst710 = (fConst694 + -0.157482159302087) / fConst693 + 0.9351401670315425;
		fConst711 = 2.0 * (0.9351401670315425 - fConst698);
		fConst712 = 50.063807016150385 / fConst697;
		fConst713 = fConst712 + 0.9351401670315425;
		fConst714 = 2.0 * (0.9351401670315425 - fConst712);
		fConst715 = 1.0 / ((fConst694 + 0.782413046821645) / fConst693 + 0.24529150870616);
		fConst716 = (fConst694 + -0.782413046821645) / fConst693 + 0.24529150870616;
		fConst717 = 2.0 * (0.24529150870616 - fConst698);
		fConst718 = 9.9999997055e-05 / fConst697;
		fConst719 = fConst718 + 0.000433227200555;
		fConst720 = 2.0 * (0.000433227200555 - fConst718);
		fConst721 = 1.0 / ((fConst694 + 0.512478641889141) / fConst693 + 0.689621364484675);
		fConst722 = (fConst694 + -0.512478641889141) / fConst693 + 0.689621364484675;
		fConst723 = 2.0 * (0.689621364484675 - fConst698);
		fConst724 = fConst698 + 7.621731298870603;
		fConst725 = 2.0 * (7.621731298870603 - fConst698);
		fConst726 = 1.0 / ((fConst694 + 0.168404871113589) / fConst693 + 1.069358407707312);
		fConst727 = (fConst694 + -0.168404871113589) / fConst693 + 1.069358407707312;
		fConst728 = 2.0 * (1.069358407707312 - fConst698);
		fConst729 = fConst698 + 53.53615295455673;
		fConst730 = 2.0 * (53.53615295455673 - fConst698);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(-2e+01);
		fVslider1 = static_cast<FAUSTFLOAT>(0.1);
		fVslider2 = static_cast<FAUSTFLOAT>(49.0);
		fVslider3 = static_cast<FAUSTFLOAT>(-0.1);
		fVslider4 = static_cast<FAUSTFLOAT>(0.1);
		fHslider0 = static_cast<FAUSTFLOAT>(2e+02);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fEntry0 = static_cast<FAUSTFLOAT>(2.0);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0);
		fHslider1 = static_cast<FAUSTFLOAT>(49.0);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(4e+01);
		fHslider5 = static_cast<FAUSTFLOAT>(8e+03);
		fHslider6 = static_cast<FAUSTFLOAT>(0.0);
		fHslider7 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider8 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec5_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec7_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec6_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec8_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec9_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			iRec10_perm[l5] = 0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec11_perm[l6] = 0.0;
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
			fRec4_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec3_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec13_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec12_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec14_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec2_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fYec19_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec1_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec0_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec16_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec15_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec20_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec19_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec18_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec17_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec27_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec26_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec25_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec24_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec23_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec22_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec21_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec34_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec33_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec32_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec31_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec30_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec29_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec28_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec41_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec40_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec39_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec38_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec37_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec36_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec35_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec48_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec47_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec46_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec45_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec44_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec43_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec42_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec55_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec54_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fRec53_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec52_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec51_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec50_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec49_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec62_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec61_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec60_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec59_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec58_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec57_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec56_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec69_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec68_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec67_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec66_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec65_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec64_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec63_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec76_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec75_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec74_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec73_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec72_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec71_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fRec70_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec83_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec82_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec81_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec80_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec79_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec78_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec77_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec90_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec89_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec88_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = faust_wrap_add(l108, 1)) {
			fRec87_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = faust_wrap_add(l109, 1)) {
			fRec86_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = faust_wrap_add(l110, 1)) {
			fRec85_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = faust_wrap_add(l111, 1)) {
			fRec84_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = faust_wrap_add(l112, 1)) {
			fRec97_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = faust_wrap_add(l113, 1)) {
			fRec96_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = faust_wrap_add(l114, 1)) {
			fRec95_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = faust_wrap_add(l115, 1)) {
			fRec94_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = faust_wrap_add(l116, 1)) {
			fRec93_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = faust_wrap_add(l117, 1)) {
			fRec92_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = faust_wrap_add(l118, 1)) {
			fRec91_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = faust_wrap_add(l119, 1)) {
			fRec104_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = faust_wrap_add(l120, 1)) {
			fRec103_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = faust_wrap_add(l121, 1)) {
			fRec102_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = faust_wrap_add(l122, 1)) {
			fRec101_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = faust_wrap_add(l123, 1)) {
			fRec100_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = faust_wrap_add(l124, 1)) {
			fRec99_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = faust_wrap_add(l125, 1)) {
			fRec98_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = faust_wrap_add(l126, 1)) {
			fRec111_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = faust_wrap_add(l127, 1)) {
			fRec110_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = faust_wrap_add(l128, 1)) {
			fRec109_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = faust_wrap_add(l129, 1)) {
			fRec108_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = faust_wrap_add(l130, 1)) {
			fRec107_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = faust_wrap_add(l131, 1)) {
			fRec106_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = faust_wrap_add(l132, 1)) {
			fRec105_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = faust_wrap_add(l133, 1)) {
			fRec118_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = faust_wrap_add(l134, 1)) {
			fRec117_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = faust_wrap_add(l135, 1)) {
			fRec116_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = faust_wrap_add(l136, 1)) {
			fRec115_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = faust_wrap_add(l137, 1)) {
			fRec114_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = faust_wrap_add(l138, 1)) {
			fRec113_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = faust_wrap_add(l139, 1)) {
			fRec112_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = faust_wrap_add(l140, 1)) {
			fRec125_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = faust_wrap_add(l141, 1)) {
			fRec124_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 4; l142 = faust_wrap_add(l142, 1)) {
			fRec123_perm[l142] = 0.0;
		}
		for (int l143 = 0; l143 < 4; l143 = faust_wrap_add(l143, 1)) {
			fRec122_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = faust_wrap_add(l144, 1)) {
			fRec121_perm[l144] = 0.0;
		}
		for (int l145 = 0; l145 < 4; l145 = faust_wrap_add(l145, 1)) {
			fRec120_perm[l145] = 0.0;
		}
		for (int l146 = 0; l146 < 4; l146 = faust_wrap_add(l146, 1)) {
			fRec119_perm[l146] = 0.0;
		}
		for (int l147 = 0; l147 < 4; l147 = faust_wrap_add(l147, 1)) {
			fRec132_perm[l147] = 0.0;
		}
		for (int l148 = 0; l148 < 4; l148 = faust_wrap_add(l148, 1)) {
			fRec131_perm[l148] = 0.0;
		}
		for (int l149 = 0; l149 < 4; l149 = faust_wrap_add(l149, 1)) {
			fRec130_perm[l149] = 0.0;
		}
		for (int l150 = 0; l150 < 4; l150 = faust_wrap_add(l150, 1)) {
			fRec129_perm[l150] = 0.0;
		}
		for (int l151 = 0; l151 < 4; l151 = faust_wrap_add(l151, 1)) {
			fRec128_perm[l151] = 0.0;
		}
		for (int l152 = 0; l152 < 4; l152 = faust_wrap_add(l152, 1)) {
			fRec127_perm[l152] = 0.0;
		}
		for (int l153 = 0; l153 < 4; l153 = faust_wrap_add(l153, 1)) {
			fRec126_perm[l153] = 0.0;
		}
		for (int l154 = 0; l154 < 4; l154 = faust_wrap_add(l154, 1)) {
			fRec139_perm[l154] = 0.0;
		}
		for (int l155 = 0; l155 < 4; l155 = faust_wrap_add(l155, 1)) {
			fRec138_perm[l155] = 0.0;
		}
		for (int l156 = 0; l156 < 4; l156 = faust_wrap_add(l156, 1)) {
			fRec137_perm[l156] = 0.0;
		}
		for (int l157 = 0; l157 < 4; l157 = faust_wrap_add(l157, 1)) {
			fRec136_perm[l157] = 0.0;
		}
		for (int l158 = 0; l158 < 4; l158 = faust_wrap_add(l158, 1)) {
			fRec135_perm[l158] = 0.0;
		}
		for (int l159 = 0; l159 < 4; l159 = faust_wrap_add(l159, 1)) {
			fRec134_perm[l159] = 0.0;
		}
		for (int l160 = 0; l160 < 4; l160 = faust_wrap_add(l160, 1)) {
			fRec133_perm[l160] = 0.0;
		}
		for (int l161 = 0; l161 < 4; l161 = faust_wrap_add(l161, 1)) {
			fRec146_perm[l161] = 0.0;
		}
		for (int l162 = 0; l162 < 4; l162 = faust_wrap_add(l162, 1)) {
			fRec145_perm[l162] = 0.0;
		}
		for (int l163 = 0; l163 < 4; l163 = faust_wrap_add(l163, 1)) {
			fRec144_perm[l163] = 0.0;
		}
		for (int l164 = 0; l164 < 4; l164 = faust_wrap_add(l164, 1)) {
			fRec143_perm[l164] = 0.0;
		}
		for (int l165 = 0; l165 < 4; l165 = faust_wrap_add(l165, 1)) {
			fRec142_perm[l165] = 0.0;
		}
		for (int l166 = 0; l166 < 4; l166 = faust_wrap_add(l166, 1)) {
			fRec141_perm[l166] = 0.0;
		}
		for (int l167 = 0; l167 < 4; l167 = faust_wrap_add(l167, 1)) {
			fRec140_perm[l167] = 0.0;
		}
		for (int l168 = 0; l168 < 4; l168 = faust_wrap_add(l168, 1)) {
			fRec150_perm[l168] = 0.0;
		}
		for (int l169 = 0; l169 < 4; l169 = faust_wrap_add(l169, 1)) {
			fRec149_perm[l169] = 0.0;
		}
		for (int l170 = 0; l170 < 4; l170 = faust_wrap_add(l170, 1)) {
			fRec148_perm[l170] = 0.0;
		}
		for (int l171 = 0; l171 < 4; l171 = faust_wrap_add(l171, 1)) {
			fRec147_perm[l171] = 0.0;
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
		ui_interface->openVerticalBox("parametric_eq");
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
		ui_interface->declare(&fCheckbox1, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on the left)", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox2);
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise selection above)", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for info and pointers");
		ui_interface->openHorizontalBox("PARAMETRIC EQ SECTIONS");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Low Shelf");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Amount of low-frequency boost or cut in decibels");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Low Boost|Cut", &fHslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(-4e+01), FAUSTFLOAT(4e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Transition Frequency", &fHslider0, FAUSTFLOAT(2e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(5e+03), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->declare(0, "tooltip", "Parametric Equalizer sections from filter.lib");
		ui_interface->openVerticalBox("Peaking Equalizer");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "Amount of local boost or cut in decibels");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Peak Boost|Cut", &fHslider3, FAUSTFLOAT(0.0), FAUSTFLOAT(-4e+01), FAUSTFLOAT(4e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "Peak Frequency in Piano Key (PK) units (A440 = 49PK)");
		ui_interface->declare(&fHslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Peak Frequency", &fHslider1, FAUSTFLOAT(49.0), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "scale", "log");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "Quality factor (Q) of the peak = center-frequency/bandwidth");
		ui_interface->addHorizontalSlider("Peak Q", &fHslider4, FAUSTFLOAT(4e+01), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+03), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->declare(0, "tooltip", "A high shelf provides a boost or cut                            above some frequency");
		ui_interface->openVerticalBox("High Shelf");
		ui_interface->declare(&fHslider6, "0", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "tooltip", "Amount of high-frequency boost or cut in decibels");
		ui_interface->declare(&fHslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("High Boost|Cut", &fHslider6, FAUSTFLOAT(0.0), FAUSTFLOAT(-4e+01), FAUSTFLOAT(4e+01), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("Transition Frequency", &fHslider5, FAUSTFLOAT(8e+03), FAUSTFLOAT(2e+01), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 20 bands spanning LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph19, "0", "");
		ui_interface->declare(&fVbargraph19, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph19, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph19, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph18, "1", "");
		ui_interface->declare(&fVbargraph18, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph18, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph18, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph17, "2", "");
		ui_interface->declare(&fVbargraph17, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph17, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph17, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph16, "3", "");
		ui_interface->declare(&fVbargraph16, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph16, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph16, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph15, "4", "");
		ui_interface->declare(&fVbargraph15, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph15, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph15, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph14, "5", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph14, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph13, "6", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph13, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph12, "7", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph12, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph11, "8", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph8", &fVbargraph11, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph10, "9", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph9", &fVbargraph10, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph9, "10", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph10", &fVbargraph9, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph8, "11", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph11", &fVbargraph8, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph7, "12", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph12", &fVbargraph7, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph6, "13", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph13", &fVbargraph6, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph5, "14", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph14", &fVbargraph5, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph4, "15", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph15", &fVbargraph4, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph3, "16", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph16", &fVbargraph3, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph2, "17", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph17", &fVbargraph2, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph1, "18", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph18", &fVbargraph1, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph0, "19", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph19", &fVbargraph0, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider7, "0", "");
		ui_interface->declare(&fHslider7, "scale", "log");
		ui_interface->declare(&fHslider7, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider7, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider7, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider8, "1", "");
		ui_interface->declare(&fHslider8, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider8, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider8, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fSlow1 = static_cast<double>(fVslider1);
		double fSlow2 = ((fSlow1 > 0.0) ? std::exp(-(fConst1 / fSlow1)) : 0.0);
		double fSlow3 = 4.4e+02 * std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fVslider2) + -49.0)) * (1.0 - fSlow2);
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fZec0[4];
		double fZec1[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow4 = 0.01 * static_cast<double>(fVslider3) + 1.0;
		double fZec2[4];
		double fZec3[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow5 = 0.01 * static_cast<double>(fVslider4) + 1.0;
		double fZec4[4];
		double fZec5[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		int iRec10_tmp[8];
		int* iRec10 = &iRec10_tmp[4];
		double fZec6[4];
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fSlow6 = std::tan(fConst2 * static_cast<double>(fHslider0));
		double fSlow7 = 1.0 / fSlow6;
		double fSlow8 = 1.0 / (fSlow7 + 1.0);
		double fSlow9 = 1.0 - fSlow7;
		int iSlow10 = static_cast<int>(static_cast<double>(fCheckbox0));
		int iSlow11 = static_cast<int>(static_cast<double>(fCheckbox1));
		int iSlow12 = static_cast<int>(static_cast<double>(fEntry0) + -1.0);
		int iSlow13 = iSlow12 >= 2;
		int iVec0_tmp[8];
		int* iVec0 = &iVec0_tmp[4];
		int iSlow14 = iSlow12 >= 1;
		double fZec7[4];
		double fZec8[4];
		double fZec9[4];
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		int iSlow15 = iSlow12 >= 3;
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
		int iSlow16 = static_cast<int>(static_cast<double>(fCheckbox2));
		double fYec18_tmp[8];
		double* fYec18 = &fYec18_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow17 = 1.0 / ((fSlow7 + 1.0000000000000004) / fSlow6 + 1.0);
		double fSlow18 = (fSlow7 + -1.0000000000000004) / fSlow6 + 1.0;
		double fSlow19 = 1.0 / mydsp_faustpower2_f(fSlow6);
		double fSlow20 = 2.0 * (1.0 - fSlow19);
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		double fSlow21 = 0.0010000000000000009 * static_cast<double>(fHslider1);
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		double fSlow22 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider2));
		double fZec19[4];
		double fZec20[4];
		double fZec21[4];
		double fSlow23 = static_cast<double>(fHslider3);
		int iSlow24 = fSlow23 > 0.0;
		double fSlow25 = static_cast<double>(fHslider4);
		double fSlow26 = fConst6 * (std::pow(1e+01, 0.05 * std::fabs(fSlow23)) / fSlow25);
		double fZec22[4];
		double fZec23[4];
		double fSlow27 = fConst6 / fSlow25;
		double fZec24[4];
		double fZec25[4];
		double fZec26[4];
		double fZec27[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow28 = std::tan(fConst2 * static_cast<double>(fHslider5));
		double fSlow29 = 1.0 / fSlow28;
		double fSlow30 = 1.0 / (fSlow29 + 1.0);
		double fSlow31 = 1.0 - fSlow29;
		double fZec28[4];
		double fYec19_tmp[8];
		double* fYec19 = &fYec19_tmp[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow32 = 1.0 / ((fSlow29 + 1.0000000000000004) / fSlow28 + 1.0);
		double fSlow33 = (fSlow29 + -1.0000000000000004) / fSlow28 + 1.0;
		double fSlow34 = mydsp_faustpower2_f(fSlow28);
		double fSlow35 = 2.0 * (1.0 - 1.0 / fSlow34);
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fSlow36 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider6)) / fSlow34;
		double fZec29[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fSlow37 = static_cast<double>(fHslider7);
		double fSlow38 = (((0.001 * fSlow37) > 0.0) ? std::exp(-(fConst27 / fSlow37)) : 0.0);
		double fSlow39 = 1.0 - fSlow38;
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fZec30[4];
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
		double fZec31[4];
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
		double fZec32[4];
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
		double fZec33[4];
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
		double fZec34[4];
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
		double fZec35[4];
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
		double fZec36[4];
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
		double fZec37[4];
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
		double fZec38[4];
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
		double fZec39[4];
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
		double fZec40[4];
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
		double fZec41[4];
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
		double fZec42[4];
		double fRec108_tmp[8];
		double* fRec108 = &fRec108_tmp[4];
		double fRec107_tmp[8];
		double* fRec107 = &fRec107_tmp[4];
		double fRec106_tmp[8];
		double* fRec106 = &fRec106_tmp[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec118_tmp[8];
		double* fRec118 = &fRec118_tmp[4];
		double fRec117_tmp[8];
		double* fRec117 = &fRec117_tmp[4];
		double fRec116_tmp[8];
		double* fRec116 = &fRec116_tmp[4];
		double fZec43[4];
		double fRec115_tmp[8];
		double* fRec115 = &fRec115_tmp[4];
		double fRec114_tmp[8];
		double* fRec114 = &fRec114_tmp[4];
		double fRec113_tmp[8];
		double* fRec113 = &fRec113_tmp[4];
		double fRec112_tmp[8];
		double* fRec112 = &fRec112_tmp[4];
		double fRec125_tmp[8];
		double* fRec125 = &fRec125_tmp[4];
		double fRec124_tmp[8];
		double* fRec124 = &fRec124_tmp[4];
		double fRec123_tmp[8];
		double* fRec123 = &fRec123_tmp[4];
		double fZec44[4];
		double fRec122_tmp[8];
		double* fRec122 = &fRec122_tmp[4];
		double fRec121_tmp[8];
		double* fRec121 = &fRec121_tmp[4];
		double fRec120_tmp[8];
		double* fRec120 = &fRec120_tmp[4];
		double fRec119_tmp[8];
		double* fRec119 = &fRec119_tmp[4];
		double fRec132_tmp[8];
		double* fRec132 = &fRec132_tmp[4];
		double fRec131_tmp[8];
		double* fRec131 = &fRec131_tmp[4];
		double fRec130_tmp[8];
		double* fRec130 = &fRec130_tmp[4];
		double fZec45[4];
		double fRec129_tmp[8];
		double* fRec129 = &fRec129_tmp[4];
		double fRec128_tmp[8];
		double* fRec128 = &fRec128_tmp[4];
		double fRec127_tmp[8];
		double* fRec127 = &fRec127_tmp[4];
		double fRec126_tmp[8];
		double* fRec126 = &fRec126_tmp[4];
		double fRec139_tmp[8];
		double* fRec139 = &fRec139_tmp[4];
		double fRec138_tmp[8];
		double* fRec138 = &fRec138_tmp[4];
		double fRec137_tmp[8];
		double* fRec137 = &fRec137_tmp[4];
		double fZec46[4];
		double fRec136_tmp[8];
		double* fRec136 = &fRec136_tmp[4];
		double fRec135_tmp[8];
		double* fRec135 = &fRec135_tmp[4];
		double fRec134_tmp[8];
		double* fRec134 = &fRec134_tmp[4];
		double fRec133_tmp[8];
		double* fRec133 = &fRec133_tmp[4];
		double fRec146_tmp[8];
		double* fRec146 = &fRec146_tmp[4];
		double fRec145_tmp[8];
		double* fRec145 = &fRec145_tmp[4];
		double fRec144_tmp[8];
		double* fRec144 = &fRec144_tmp[4];
		double fZec47[4];
		double fRec143_tmp[8];
		double* fRec143 = &fRec143_tmp[4];
		double fRec142_tmp[8];
		double* fRec142 = &fRec142_tmp[4];
		double fRec141_tmp[8];
		double* fRec141 = &fRec141_tmp[4];
		double fRec140_tmp[8];
		double* fRec140 = &fRec140_tmp[4];
		double fRec150_tmp[8];
		double* fRec150 = &fRec150_tmp[4];
		double fRec149_tmp[8];
		double* fRec149 = &fRec149_tmp[4];
		double fRec148_tmp[8];
		double* fRec148 = &fRec148_tmp[4];
		double fRec147_tmp[8];
		double* fRec147 = &fRec147_tmp[4];
		double fSlow40 = static_cast<double>(fHslider8);
		double fZec48[4];
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
				fRec5_tmp[j0] = fRec5_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fSlow0 + 0.999 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec5_perm[j1] = fRec5_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec7_tmp[j2] = fRec7_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec7[faust_wrap_sub(i, 1)] * fSlow2 + fSlow3;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec7_perm[j3] = fRec7_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec7[i]));
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec6_tmp[j4] = fRec6_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec6[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec6[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec6_perm[j5] = fRec6_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec7[i]));
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec8_tmp[j6] = fRec8_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec8[faust_wrap_sub(i, 1)] + fConst1 * fZec2[i];
				fRec8[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec8_perm[j7] = fRec8_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec7[i]));
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec9_tmp[j8] = fRec9_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fRec9[faust_wrap_sub(i, 1)] + fConst1 * fZec4[i];
				fRec9[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec9_perm[j9] = fRec9_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iRec10_tmp[j10] = iRec10_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec10[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec10[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iRec10_perm[j11] = iRec10_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec10[i]);
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec11_tmp[j12] = fRec11_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = 0.5221894 * fRec11[faust_wrap_sub(i, 3)] + fZec6[i] + 2.494956002 * fRec11[faust_wrap_sub(i, 1)] - 2.017265875 * fRec11[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec11_perm[j13] = fRec11_tmp[faust_wrap_add(vsize, j13)];
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
				fZec7[i] = 2.0 * fRec6[i];
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
				fZec13[i] = 2.0 * fRec8[i];
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
				fZec16[i] = 2.0 * fRec9[i];
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
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec18_tmp[j52] = fYec18_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[i] = fRec5[i] * ((iSlow10) ? static_cast<double>(input0[i]) : ((iSlow11) ? ((iSlow16) ? 0.049922035 * fRec11[i] + 0.050612699 * fRec11[faust_wrap_sub(i, 2)] - (0.095993537 * fRec11[faust_wrap_sub(i, 1)] + 0.004408786 * fRec11[faust_wrap_sub(i, 3)]) : fZec6[i]) : 0.3333333333333333 * fRec5[i] * (((iSlow13) ? ((iSlow15) ? fConst5 * (fZec12[i] * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst4 * (fZec10[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow14) ? fConst3 * (fZec9[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec8[i])) + ((iSlow13) ? ((iSlow15) ? fConst5 * (fZec12[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec2[i]) : fConst4 * (fZec10[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec2[i])) : ((iSlow14) ? fConst3 * (fZec9[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec2[i]) : fZec14[i])) + ((iSlow13) ? ((iSlow15) ? fConst5 * (fZec12[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec4[i]) : fConst4 * (fZec10[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec4[i])) : ((iSlow14) ? fConst3 * (fZec9[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec4[i]) : fZec17[i])))));
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec18_perm[j53] = fYec18_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 43 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec4_tmp[j54] = fRec4_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = -(fSlow8 * (fSlow9 * fRec4[faust_wrap_sub(i, 1)] - fSlow7 * (fYec18[i] - fYec18[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec4_perm[j55] = fRec4_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec3_tmp[j56] = fRec3_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fRec4[i] - fSlow17 * (fSlow18 * fRec3[faust_wrap_sub(i, 2)] + fSlow20 * fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec3_perm[j57] = fRec3_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 45 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec13_tmp[j58] = fRec13_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = -(fSlow8 * (fSlow9 * fRec13[faust_wrap_sub(i, 1)] - (fYec18[i] + fYec18[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec13_perm[j59] = fRec13_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec12_tmp[j60] = fRec12_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fRec13[i] - fSlow17 * (fSlow18 * fRec12[faust_wrap_sub(i, 2)] + fSlow20 * fRec12[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec12_perm[j61] = fRec12_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 47 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec14_tmp[j62] = fRec14_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fSlow21 + 0.999 * fRec14[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec14_perm[j63] = fRec14_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = std::pow(2.0, 0.08333333333333333 * (fRec14[i] + -49.0));
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = std::tan(fConst6 * fZec19[i]);
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = 1.0 / fZec20[i];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fZec19[i] / std::sin(fConst7 * fZec19[i]);
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fSlow26 * fZec22[i];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fSlow27 * fZec22[i];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = ((iSlow24) ? fZec24[i] : fZec23[i]);
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = (fZec21[i] + fZec25[i]) / fZec20[i] + 1.0;
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec2_tmp[j64] = fRec2_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = 2.0 * fRec2[faust_wrap_sub(i, 1)] * (1.0 - 1.0 / mydsp_faustpower2_f(fZec20[i]));
				fRec2[i] = fSlow17 * (fSlow19 * (fRec3[faust_wrap_sub(i, 2)] + (fRec3[i] - 2.0 * fRec3[faust_wrap_sub(i, 1)])) + fSlow22 * (fRec12[faust_wrap_sub(i, 2)] + fRec12[i] + 2.0 * fRec12[faust_wrap_sub(i, 1)])) - (fRec2[faust_wrap_sub(i, 2)] * ((fZec21[i] - fZec25[i]) / fZec20[i] + 1.0) + fZec26[i]) / fZec27[i];
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec2_perm[j65] = fRec2_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = ((iSlow24) ? fZec23[i] : fZec24[i]);
			}
			/* Vectorizable loop 58 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fYec19_tmp[j66] = fYec19_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[i] = (fZec26[i] + fRec2[i] * ((fZec21[i] + fZec28[i]) / fZec20[i] + 1.0) + fRec2[faust_wrap_sub(i, 2)] * ((fZec21[i] - fZec28[i]) / fZec20[i] + 1.0)) / fZec27[i];
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fYec19_perm[j67] = fYec19_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 59 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec1_tmp[j68] = fRec1_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = -(fSlow30 * (fSlow31 * fRec1[faust_wrap_sub(i, 1)] - (fYec19[i] + fYec19[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec1_perm[j69] = fRec1_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec0_tmp[j70] = fRec0_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fRec1[i] - fSlow32 * (fSlow33 * fRec0[faust_wrap_sub(i, 2)] + fSlow35 * fRec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec0_perm[j71] = fRec0_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 61 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec16_tmp[j72] = fRec16_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = -(fSlow30 * (fSlow31 * fRec16[faust_wrap_sub(i, 1)] - fSlow29 * (fYec19[i] - fYec19[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec16_perm[j73] = fRec16_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec15_tmp[j74] = fRec15_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fRec16[i] - fSlow32 * (fSlow33 * fRec15[faust_wrap_sub(i, 2)] + fSlow35 * fRec15[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec15_perm[j75] = fRec15_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = fSlow32 * (fRec0[faust_wrap_sub(i, 2)] + fRec0[i] + 2.0 * fRec0[faust_wrap_sub(i, 1)] + fSlow36 * (fRec15[faust_wrap_sub(i, 2)] + (fRec15[i] - 2.0 * fRec15[faust_wrap_sub(i, 1)])));
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec27_tmp[j84] = fRec27_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fZec29[i] - fConst31 * (fConst32 * fRec27[faust_wrap_sub(i, 2)] + fConst33 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec27_perm[j85] = fRec27_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec26_tmp[j86] = fRec26_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst31 * (fConst35 * fRec27[i] + fConst36 * fRec27[faust_wrap_sub(i, 1)] + fConst35 * fRec27[faust_wrap_sub(i, 2)]) - fConst37 * (fConst38 * fRec26[faust_wrap_sub(i, 2)] + fConst39 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec26_perm[j87] = fRec26_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec25_tmp[j88] = fRec25_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fConst37 * (fConst40 * fRec26[i] + fConst41 * fRec26[faust_wrap_sub(i, 1)] + fConst40 * fRec26[faust_wrap_sub(i, 2)]) - fConst42 * (fConst43 * fRec25[faust_wrap_sub(i, 2)] + fConst44 * fRec25[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec25_perm[j89] = fRec25_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = fConst42 * (fConst45 * fRec25[i] + fConst46 * fRec25[faust_wrap_sub(i, 1)] + fConst45 * fRec25[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec34_tmp[j98] = fRec34_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fZec30[i] - fConst69 * (fConst70 * fRec34[faust_wrap_sub(i, 2)] + fConst71 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec34_perm[j99] = fRec34_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec33_tmp[j100] = fRec33_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst69 * (fConst73 * fRec34[i] + fConst74 * fRec34[faust_wrap_sub(i, 1)] + fConst73 * fRec34[faust_wrap_sub(i, 2)]) - fConst75 * (fConst76 * fRec33[faust_wrap_sub(i, 2)] + fConst77 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec33_perm[j101] = fRec33_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec32_tmp[j102] = fRec32_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fConst75 * (fConst78 * fRec33[i] + fConst79 * fRec33[faust_wrap_sub(i, 1)] + fConst78 * fRec33[faust_wrap_sub(i, 2)]) - fConst80 * (fConst81 * fRec32[faust_wrap_sub(i, 2)] + fConst82 * fRec32[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec32_perm[j103] = fRec32_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fConst80 * (fConst83 * fRec32[i] + fConst84 * fRec32[faust_wrap_sub(i, 1)] + fConst83 * fRec32[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec41_tmp[j112] = fRec41_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fZec31[i] - fConst107 * (fConst108 * fRec41[faust_wrap_sub(i, 2)] + fConst109 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec41_perm[j113] = fRec41_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec40_tmp[j114] = fRec40_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst107 * (fConst111 * fRec41[i] + fConst112 * fRec41[faust_wrap_sub(i, 1)] + fConst111 * fRec41[faust_wrap_sub(i, 2)]) - fConst113 * (fConst114 * fRec40[faust_wrap_sub(i, 2)] + fConst115 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec40_perm[j115] = fRec40_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec39_tmp[j116] = fRec39_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fConst113 * (fConst116 * fRec40[i] + fConst117 * fRec40[faust_wrap_sub(i, 1)] + fConst116 * fRec40[faust_wrap_sub(i, 2)]) - fConst118 * (fConst119 * fRec39[faust_wrap_sub(i, 2)] + fConst120 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec39_perm[j117] = fRec39_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = fConst118 * (fConst121 * fRec39[i] + fConst122 * fRec39[faust_wrap_sub(i, 1)] + fConst121 * fRec39[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec48_tmp[j126] = fRec48_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fZec32[i] - fConst145 * (fConst146 * fRec48[faust_wrap_sub(i, 2)] + fConst147 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec48_perm[j127] = fRec48_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec47_tmp[j128] = fRec47_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst145 * (fConst149 * fRec48[i] + fConst150 * fRec48[faust_wrap_sub(i, 1)] + fConst149 * fRec48[faust_wrap_sub(i, 2)]) - fConst151 * (fConst152 * fRec47[faust_wrap_sub(i, 2)] + fConst153 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec47_perm[j129] = fRec47_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec46_tmp[j130] = fRec46_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fConst151 * (fConst154 * fRec47[i] + fConst155 * fRec47[faust_wrap_sub(i, 1)] + fConst154 * fRec47[faust_wrap_sub(i, 2)]) - fConst156 * (fConst157 * fRec46[faust_wrap_sub(i, 2)] + fConst158 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec46_perm[j131] = fRec46_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = fConst156 * (fConst159 * fRec46[i] + fConst160 * fRec46[faust_wrap_sub(i, 1)] + fConst159 * fRec46[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec55_tmp[j140] = fRec55_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fZec33[i] - fConst183 * (fConst184 * fRec55[faust_wrap_sub(i, 2)] + fConst185 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec55_perm[j141] = fRec55_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec54_tmp[j142] = fRec54_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst183 * (fConst187 * fRec55[i] + fConst188 * fRec55[faust_wrap_sub(i, 1)] + fConst187 * fRec55[faust_wrap_sub(i, 2)]) - fConst189 * (fConst190 * fRec54[faust_wrap_sub(i, 2)] + fConst191 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec54_perm[j143] = fRec54_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec53_tmp[j144] = fRec53_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fConst189 * (fConst192 * fRec54[i] + fConst193 * fRec54[faust_wrap_sub(i, 1)] + fConst192 * fRec54[faust_wrap_sub(i, 2)]) - fConst194 * (fConst195 * fRec53[faust_wrap_sub(i, 2)] + fConst196 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec53_perm[j145] = fRec53_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = fConst194 * (fConst197 * fRec53[i] + fConst198 * fRec53[faust_wrap_sub(i, 1)] + fConst197 * fRec53[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec62_tmp[j154] = fRec62_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fZec34[i] - fConst221 * (fConst222 * fRec62[faust_wrap_sub(i, 2)] + fConst223 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec62_perm[j155] = fRec62_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec61_tmp[j156] = fRec61_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst221 * (fConst225 * fRec62[i] + fConst226 * fRec62[faust_wrap_sub(i, 1)] + fConst225 * fRec62[faust_wrap_sub(i, 2)]) - fConst227 * (fConst228 * fRec61[faust_wrap_sub(i, 2)] + fConst229 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec61_perm[j157] = fRec61_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec60_tmp[j158] = fRec60_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fConst227 * (fConst230 * fRec61[i] + fConst231 * fRec61[faust_wrap_sub(i, 1)] + fConst230 * fRec61[faust_wrap_sub(i, 2)]) - fConst232 * (fConst233 * fRec60[faust_wrap_sub(i, 2)] + fConst234 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec60_perm[j159] = fRec60_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = fConst232 * (fConst235 * fRec60[i] + fConst236 * fRec60[faust_wrap_sub(i, 1)] + fConst235 * fRec60[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec69_tmp[j168] = fRec69_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fZec35[i] - fConst259 * (fConst260 * fRec69[faust_wrap_sub(i, 2)] + fConst261 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec69_perm[j169] = fRec69_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec68_tmp[j170] = fRec68_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst259 * (fConst263 * fRec69[i] + fConst264 * fRec69[faust_wrap_sub(i, 1)] + fConst263 * fRec69[faust_wrap_sub(i, 2)]) - fConst265 * (fConst266 * fRec68[faust_wrap_sub(i, 2)] + fConst267 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec68_perm[j171] = fRec68_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec67_tmp[j172] = fRec67_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fConst265 * (fConst268 * fRec68[i] + fConst269 * fRec68[faust_wrap_sub(i, 1)] + fConst268 * fRec68[faust_wrap_sub(i, 2)]) - fConst270 * (fConst271 * fRec67[faust_wrap_sub(i, 2)] + fConst272 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec67_perm[j173] = fRec67_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec36[i] = fConst270 * (fConst273 * fRec67[i] + fConst274 * fRec67[faust_wrap_sub(i, 1)] + fConst273 * fRec67[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec76_tmp[j182] = fRec76_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fZec36[i] - fConst297 * (fConst298 * fRec76[faust_wrap_sub(i, 2)] + fConst299 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec76_perm[j183] = fRec76_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec75_tmp[j184] = fRec75_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst297 * (fConst301 * fRec76[i] + fConst302 * fRec76[faust_wrap_sub(i, 1)] + fConst301 * fRec76[faust_wrap_sub(i, 2)]) - fConst303 * (fConst304 * fRec75[faust_wrap_sub(i, 2)] + fConst305 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec75_perm[j185] = fRec75_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec74_tmp[j186] = fRec74_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fConst303 * (fConst306 * fRec75[i] + fConst307 * fRec75[faust_wrap_sub(i, 1)] + fConst306 * fRec75[faust_wrap_sub(i, 2)]) - fConst308 * (fConst309 * fRec74[faust_wrap_sub(i, 2)] + fConst310 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec74_perm[j187] = fRec74_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec37[i] = fConst308 * (fConst311 * fRec74[i] + fConst312 * fRec74[faust_wrap_sub(i, 1)] + fConst311 * fRec74[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec83_tmp[j196] = fRec83_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fZec37[i] - fConst335 * (fConst336 * fRec83[faust_wrap_sub(i, 2)] + fConst337 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec83_perm[j197] = fRec83_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec82_tmp[j198] = fRec82_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst335 * (fConst339 * fRec83[i] + fConst340 * fRec83[faust_wrap_sub(i, 1)] + fConst339 * fRec83[faust_wrap_sub(i, 2)]) - fConst341 * (fConst342 * fRec82[faust_wrap_sub(i, 2)] + fConst343 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec82_perm[j199] = fRec82_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec81_tmp[j200] = fRec81_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fConst341 * (fConst344 * fRec82[i] + fConst345 * fRec82[faust_wrap_sub(i, 1)] + fConst344 * fRec82[faust_wrap_sub(i, 2)]) - fConst346 * (fConst347 * fRec81[faust_wrap_sub(i, 2)] + fConst348 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec81_perm[j201] = fRec81_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec38[i] = fConst346 * (fConst349 * fRec81[i] + fConst350 * fRec81[faust_wrap_sub(i, 1)] + fConst349 * fRec81[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec90_tmp[j210] = fRec90_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fZec38[i] - fConst373 * (fConst374 * fRec90[faust_wrap_sub(i, 2)] + fConst375 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec90_perm[j211] = fRec90_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec89_tmp[j212] = fRec89_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst373 * (fConst377 * fRec90[i] + fConst378 * fRec90[faust_wrap_sub(i, 1)] + fConst377 * fRec90[faust_wrap_sub(i, 2)]) - fConst379 * (fConst380 * fRec89[faust_wrap_sub(i, 2)] + fConst381 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec89_perm[j213] = fRec89_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec88_tmp[j214] = fRec88_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fConst379 * (fConst382 * fRec89[i] + fConst383 * fRec89[faust_wrap_sub(i, 1)] + fConst382 * fRec89[faust_wrap_sub(i, 2)]) - fConst384 * (fConst385 * fRec88[faust_wrap_sub(i, 2)] + fConst386 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec88_perm[j215] = fRec88_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec39[i] = fConst384 * (fConst387 * fRec88[i] + fConst388 * fRec88[faust_wrap_sub(i, 1)] + fConst387 * fRec88[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec97_tmp[j224] = fRec97_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fZec39[i] - fConst411 * (fConst412 * fRec97[faust_wrap_sub(i, 2)] + fConst413 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec97_perm[j225] = fRec97_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec96_tmp[j226] = fRec96_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst411 * (fConst415 * fRec97[i] + fConst416 * fRec97[faust_wrap_sub(i, 1)] + fConst415 * fRec97[faust_wrap_sub(i, 2)]) - fConst417 * (fConst418 * fRec96[faust_wrap_sub(i, 2)] + fConst419 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec96_perm[j227] = fRec96_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec95_tmp[j228] = fRec95_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fConst417 * (fConst420 * fRec96[i] + fConst421 * fRec96[faust_wrap_sub(i, 1)] + fConst420 * fRec96[faust_wrap_sub(i, 2)]) - fConst422 * (fConst423 * fRec95[faust_wrap_sub(i, 2)] + fConst424 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec95_perm[j229] = fRec95_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec40[i] = fConst422 * (fConst425 * fRec95[i] + fConst426 * fRec95[faust_wrap_sub(i, 1)] + fConst425 * fRec95[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec94_tmp[j230] = fRec94_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec40[i] - fConst429 * (fConst430 * fRec94[faust_wrap_sub(i, 2)] + fConst433 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec94_perm[j231] = fRec94_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec93_tmp[j232] = fRec93_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst429 * (fConst435 * fRec94[i] + fConst436 * fRec94[faust_wrap_sub(i, 1)] + fConst435 * fRec94[faust_wrap_sub(i, 2)]) - fConst437 * (fConst438 * fRec93[faust_wrap_sub(i, 2)] + fConst439 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec93_perm[j233] = fRec93_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec92_tmp[j234] = fRec92_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst437 * (fConst441 * fRec93[i] + fConst442 * fRec93[faust_wrap_sub(i, 1)] + fConst441 * fRec93[faust_wrap_sub(i, 2)]) - fConst443 * (fConst444 * fRec92[faust_wrap_sub(i, 2)] + fConst445 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec92_perm[j235] = fRec92_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 111 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec91_tmp[j236] = fRec91_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fSlow38 * fRec91[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst443 * (fConst447 * fRec92[i] + fConst448 * fRec92[faust_wrap_sub(i, 1)] + fConst447 * fRec92[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec91_perm[j237] = fRec91_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec104_tmp[j238] = fRec104_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fZec40[i] - fConst449 * (fConst450 * fRec104[faust_wrap_sub(i, 2)] + fConst451 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec104_perm[j239] = fRec104_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec103_tmp[j240] = fRec103_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst449 * (fConst453 * fRec104[i] + fConst454 * fRec104[faust_wrap_sub(i, 1)] + fConst453 * fRec104[faust_wrap_sub(i, 2)]) - fConst455 * (fConst456 * fRec103[faust_wrap_sub(i, 2)] + fConst457 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec103_perm[j241] = fRec103_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec102_tmp[j242] = fRec102_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fConst455 * (fConst458 * fRec103[i] + fConst459 * fRec103[faust_wrap_sub(i, 1)] + fConst458 * fRec103[faust_wrap_sub(i, 2)]) - fConst460 * (fConst461 * fRec102[faust_wrap_sub(i, 2)] + fConst462 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec102_perm[j243] = fRec102_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = fConst460 * (fConst463 * fRec102[i] + fConst464 * fRec102[faust_wrap_sub(i, 1)] + fConst463 * fRec102[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec101_tmp[j244] = fRec101_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec41[i] - fConst467 * (fConst468 * fRec101[faust_wrap_sub(i, 2)] + fConst471 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec101_perm[j245] = fRec101_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec100_tmp[j246] = fRec100_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst467 * (fConst473 * fRec101[i] + fConst474 * fRec101[faust_wrap_sub(i, 1)] + fConst473 * fRec101[faust_wrap_sub(i, 2)]) - fConst475 * (fConst476 * fRec100[faust_wrap_sub(i, 2)] + fConst477 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec100_perm[j247] = fRec100_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec99_tmp[j248] = fRec99_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst475 * (fConst479 * fRec100[i] + fConst480 * fRec100[faust_wrap_sub(i, 1)] + fConst479 * fRec100[faust_wrap_sub(i, 2)]) - fConst481 * (fConst482 * fRec99[faust_wrap_sub(i, 2)] + fConst483 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec99_perm[j249] = fRec99_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 119 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec98_tmp[j250] = fRec98_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fSlow38 * fRec98[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst481 * (fConst485 * fRec99[i] + fConst486 * fRec99[faust_wrap_sub(i, 1)] + fConst485 * fRec99[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec98_perm[j251] = fRec98_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec111_tmp[j252] = fRec111_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fZec41[i] - fConst487 * (fConst488 * fRec111[faust_wrap_sub(i, 2)] + fConst489 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec111_perm[j253] = fRec111_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec110_tmp[j254] = fRec110_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst487 * (fConst491 * fRec111[i] + fConst492 * fRec111[faust_wrap_sub(i, 1)] + fConst491 * fRec111[faust_wrap_sub(i, 2)]) - fConst493 * (fConst494 * fRec110[faust_wrap_sub(i, 2)] + fConst495 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec110_perm[j255] = fRec110_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec109_tmp[j256] = fRec109_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fConst493 * (fConst496 * fRec110[i] + fConst497 * fRec110[faust_wrap_sub(i, 1)] + fConst496 * fRec110[faust_wrap_sub(i, 2)]) - fConst498 * (fConst499 * fRec109[faust_wrap_sub(i, 2)] + fConst500 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec109_perm[j257] = fRec109_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Vectorizable loop 123 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = fConst498 * (fConst501 * fRec109[i] + fConst502 * fRec109[faust_wrap_sub(i, 1)] + fConst501 * fRec109[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec108_tmp[j258] = fRec108_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fZec42[i] - fConst505 * (fConst506 * fRec108[faust_wrap_sub(i, 2)] + fConst509 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec108_perm[j259] = fRec108_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec107_tmp[j260] = fRec107_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst505 * (fConst511 * fRec108[i] + fConst512 * fRec108[faust_wrap_sub(i, 1)] + fConst511 * fRec108[faust_wrap_sub(i, 2)]) - fConst513 * (fConst514 * fRec107[faust_wrap_sub(i, 2)] + fConst515 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec107_perm[j261] = fRec107_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec106_tmp[j262] = fRec106_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fConst513 * (fConst517 * fRec107[i] + fConst518 * fRec107[faust_wrap_sub(i, 1)] + fConst517 * fRec107[faust_wrap_sub(i, 2)]) - fConst519 * (fConst520 * fRec106[faust_wrap_sub(i, 2)] + fConst521 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec106_perm[j263] = fRec106_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec105_tmp[j264] = fRec105_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fSlow38 * fRec105[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst519 * (fConst523 * fRec106[i] + fConst524 * fRec106[faust_wrap_sub(i, 1)] + fConst523 * fRec106[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec105_perm[j265] = fRec105_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec118_tmp[j266] = fRec118_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fZec42[i] - fConst525 * (fConst526 * fRec118[faust_wrap_sub(i, 2)] + fConst527 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec118_perm[j267] = fRec118_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec117_tmp[j268] = fRec117_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fConst525 * (fConst529 * fRec118[i] + fConst530 * fRec118[faust_wrap_sub(i, 1)] + fConst529 * fRec118[faust_wrap_sub(i, 2)]) - fConst531 * (fConst532 * fRec117[faust_wrap_sub(i, 2)] + fConst533 * fRec117[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec117_perm[j269] = fRec117_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec116_tmp[j270] = fRec116_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fConst531 * (fConst534 * fRec117[i] + fConst535 * fRec117[faust_wrap_sub(i, 1)] + fConst534 * fRec117[faust_wrap_sub(i, 2)]) - fConst536 * (fConst537 * fRec116[faust_wrap_sub(i, 2)] + fConst538 * fRec116[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec116_perm[j271] = fRec116_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Vectorizable loop 131 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = fConst536 * (fConst539 * fRec116[i] + fConst540 * fRec116[faust_wrap_sub(i, 1)] + fConst539 * fRec116[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec115_tmp[j272] = fRec115_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fZec43[i] - fConst543 * (fConst544 * fRec115[faust_wrap_sub(i, 2)] + fConst547 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec115_perm[j273] = fRec115_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec114_tmp[j274] = fRec114_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst543 * (fConst549 * fRec115[i] + fConst550 * fRec115[faust_wrap_sub(i, 1)] + fConst549 * fRec115[faust_wrap_sub(i, 2)]) - fConst551 * (fConst552 * fRec114[faust_wrap_sub(i, 2)] + fConst553 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec114_perm[j275] = fRec114_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec113_tmp[j276] = fRec113_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fConst551 * (fConst555 * fRec114[i] + fConst556 * fRec114[faust_wrap_sub(i, 1)] + fConst555 * fRec114[faust_wrap_sub(i, 2)]) - fConst557 * (fConst558 * fRec113[faust_wrap_sub(i, 2)] + fConst559 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec113_perm[j277] = fRec113_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec112_tmp[j278] = fRec112_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fSlow38 * fRec112[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst557 * (fConst561 * fRec113[i] + fConst562 * fRec113[faust_wrap_sub(i, 1)] + fConst561 * fRec113[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec112_perm[j279] = fRec112_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec125_tmp[j280] = fRec125_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fZec43[i] - fConst563 * (fConst564 * fRec125[faust_wrap_sub(i, 2)] + fConst565 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec125_perm[j281] = fRec125_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec124_tmp[j282] = fRec124_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fConst563 * (fConst567 * fRec125[i] + fConst568 * fRec125[faust_wrap_sub(i, 1)] + fConst567 * fRec125[faust_wrap_sub(i, 2)]) - fConst569 * (fConst570 * fRec124[faust_wrap_sub(i, 2)] + fConst571 * fRec124[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec124_perm[j283] = fRec124_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec123_tmp[j284] = fRec123_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fConst569 * (fConst572 * fRec124[i] + fConst573 * fRec124[faust_wrap_sub(i, 1)] + fConst572 * fRec124[faust_wrap_sub(i, 2)]) - fConst574 * (fConst575 * fRec123[faust_wrap_sub(i, 2)] + fConst576 * fRec123[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec123_perm[j285] = fRec123_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Vectorizable loop 139 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec44[i] = fConst574 * (fConst577 * fRec123[i] + fConst578 * fRec123[faust_wrap_sub(i, 1)] + fConst577 * fRec123[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec122_tmp[j286] = fRec122_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fZec44[i] - fConst581 * (fConst582 * fRec122[faust_wrap_sub(i, 2)] + fConst585 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec122_perm[j287] = fRec122_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec121_tmp[j288] = fRec121_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst581 * (fConst587 * fRec122[i] + fConst588 * fRec122[faust_wrap_sub(i, 1)] + fConst587 * fRec122[faust_wrap_sub(i, 2)]) - fConst589 * (fConst590 * fRec121[faust_wrap_sub(i, 2)] + fConst591 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec121_perm[j289] = fRec121_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec120_tmp[j290] = fRec120_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fConst589 * (fConst593 * fRec121[i] + fConst594 * fRec121[faust_wrap_sub(i, 1)] + fConst593 * fRec121[faust_wrap_sub(i, 2)]) - fConst595 * (fConst596 * fRec120[faust_wrap_sub(i, 2)] + fConst597 * fRec120[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec120_perm[j291] = fRec120_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec119_tmp[j292] = fRec119_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fSlow38 * fRec119[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst595 * (fConst599 * fRec120[i] + fConst600 * fRec120[faust_wrap_sub(i, 1)] + fConst599 * fRec120[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec119_perm[j293] = fRec119_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec132_tmp[j294] = fRec132_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec132[i] = fZec44[i] - fConst601 * (fConst602 * fRec132[faust_wrap_sub(i, 2)] + fConst603 * fRec132[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec132_perm[j295] = fRec132_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec131_tmp[j296] = fRec131_perm[j296];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec131[i] = fConst601 * (fConst605 * fRec132[i] + fConst606 * fRec132[faust_wrap_sub(i, 1)] + fConst605 * fRec132[faust_wrap_sub(i, 2)]) - fConst607 * (fConst608 * fRec131[faust_wrap_sub(i, 2)] + fConst609 * fRec131[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec131_perm[j297] = fRec131_tmp[faust_wrap_add(vsize, j297)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec130_tmp[j298] = fRec130_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec130[i] = fConst607 * (fConst610 * fRec131[i] + fConst611 * fRec131[faust_wrap_sub(i, 1)] + fConst610 * fRec131[faust_wrap_sub(i, 2)]) - fConst612 * (fConst613 * fRec130[faust_wrap_sub(i, 2)] + fConst614 * fRec130[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec130_perm[j299] = fRec130_tmp[faust_wrap_add(vsize, j299)];
			}
			/* Vectorizable loop 147 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec45[i] = fConst612 * (fConst615 * fRec130[i] + fConst616 * fRec130[faust_wrap_sub(i, 1)] + fConst615 * fRec130[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec129_tmp[j300] = fRec129_perm[j300];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec129[i] = fZec45[i] - fConst619 * (fConst620 * fRec129[faust_wrap_sub(i, 2)] + fConst623 * fRec129[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec129_perm[j301] = fRec129_tmp[faust_wrap_add(vsize, j301)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec128_tmp[j302] = fRec128_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec128[i] = fConst619 * (fConst625 * fRec129[i] + fConst626 * fRec129[faust_wrap_sub(i, 1)] + fConst625 * fRec129[faust_wrap_sub(i, 2)]) - fConst627 * (fConst628 * fRec128[faust_wrap_sub(i, 2)] + fConst629 * fRec128[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec128_perm[j303] = fRec128_tmp[faust_wrap_add(vsize, j303)];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec127_tmp[j304] = fRec127_perm[j304];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fConst627 * (fConst631 * fRec128[i] + fConst632 * fRec128[faust_wrap_sub(i, 1)] + fConst631 * fRec128[faust_wrap_sub(i, 2)]) - fConst633 * (fConst634 * fRec127[faust_wrap_sub(i, 2)] + fConst635 * fRec127[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec127_perm[j305] = fRec127_tmp[faust_wrap_add(vsize, j305)];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec126_tmp[j306] = fRec126_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fSlow38 * fRec126[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst633 * (fConst637 * fRec127[i] + fConst638 * fRec127[faust_wrap_sub(i, 1)] + fConst637 * fRec127[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec126_perm[j307] = fRec126_tmp[faust_wrap_add(vsize, j307)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j308 = 0; j308 < 4; j308 = faust_wrap_add(j308, 1)) {
				fRec139_tmp[j308] = fRec139_perm[j308];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec139[i] = fZec45[i] - fConst639 * (fConst640 * fRec139[faust_wrap_sub(i, 2)] + fConst641 * fRec139[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j309 = 0; j309 < 4; j309 = faust_wrap_add(j309, 1)) {
				fRec139_perm[j309] = fRec139_tmp[faust_wrap_add(vsize, j309)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j310 = 0; j310 < 4; j310 = faust_wrap_add(j310, 1)) {
				fRec138_tmp[j310] = fRec138_perm[j310];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec138[i] = fConst639 * (fConst643 * fRec139[i] + fConst644 * fRec139[faust_wrap_sub(i, 1)] + fConst643 * fRec139[faust_wrap_sub(i, 2)]) - fConst645 * (fConst646 * fRec138[faust_wrap_sub(i, 2)] + fConst647 * fRec138[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j311 = 0; j311 < 4; j311 = faust_wrap_add(j311, 1)) {
				fRec138_perm[j311] = fRec138_tmp[faust_wrap_add(vsize, j311)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j312 = 0; j312 < 4; j312 = faust_wrap_add(j312, 1)) {
				fRec137_tmp[j312] = fRec137_perm[j312];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec137[i] = fConst645 * (fConst648 * fRec138[i] + fConst649 * fRec138[faust_wrap_sub(i, 1)] + fConst648 * fRec138[faust_wrap_sub(i, 2)]) - fConst650 * (fConst651 * fRec137[faust_wrap_sub(i, 2)] + fConst652 * fRec137[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j313 = 0; j313 < 4; j313 = faust_wrap_add(j313, 1)) {
				fRec137_perm[j313] = fRec137_tmp[faust_wrap_add(vsize, j313)];
			}
			/* Vectorizable loop 155 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec46[i] = fConst650 * (fConst653 * fRec137[i] + fConst654 * fRec137[faust_wrap_sub(i, 1)] + fConst653 * fRec137[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j314 = 0; j314 < 4; j314 = faust_wrap_add(j314, 1)) {
				fRec136_tmp[j314] = fRec136_perm[j314];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec136[i] = fZec46[i] - fConst657 * (fConst658 * fRec136[faust_wrap_sub(i, 2)] + fConst661 * fRec136[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j315 = 0; j315 < 4; j315 = faust_wrap_add(j315, 1)) {
				fRec136_perm[j315] = fRec136_tmp[faust_wrap_add(vsize, j315)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j316 = 0; j316 < 4; j316 = faust_wrap_add(j316, 1)) {
				fRec135_tmp[j316] = fRec135_perm[j316];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec135[i] = fConst657 * (fConst663 * fRec136[i] + fConst664 * fRec136[faust_wrap_sub(i, 1)] + fConst663 * fRec136[faust_wrap_sub(i, 2)]) - fConst665 * (fConst666 * fRec135[faust_wrap_sub(i, 2)] + fConst667 * fRec135[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j317 = 0; j317 < 4; j317 = faust_wrap_add(j317, 1)) {
				fRec135_perm[j317] = fRec135_tmp[faust_wrap_add(vsize, j317)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j318 = 0; j318 < 4; j318 = faust_wrap_add(j318, 1)) {
				fRec134_tmp[j318] = fRec134_perm[j318];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec134[i] = fConst665 * (fConst669 * fRec135[i] + fConst670 * fRec135[faust_wrap_sub(i, 1)] + fConst669 * fRec135[faust_wrap_sub(i, 2)]) - fConst671 * (fConst672 * fRec134[faust_wrap_sub(i, 2)] + fConst673 * fRec134[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j319 = 0; j319 < 4; j319 = faust_wrap_add(j319, 1)) {
				fRec134_perm[j319] = fRec134_tmp[faust_wrap_add(vsize, j319)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j320 = 0; j320 < 4; j320 = faust_wrap_add(j320, 1)) {
				fRec133_tmp[j320] = fRec133_perm[j320];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec133[i] = fSlow38 * fRec133[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst671 * (fConst675 * fRec134[i] + fConst676 * fRec134[faust_wrap_sub(i, 1)] + fConst675 * fRec134[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j321 = 0; j321 < 4; j321 = faust_wrap_add(j321, 1)) {
				fRec133_perm[j321] = fRec133_tmp[faust_wrap_add(vsize, j321)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j322 = 0; j322 < 4; j322 = faust_wrap_add(j322, 1)) {
				fRec146_tmp[j322] = fRec146_perm[j322];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec146[i] = fZec46[i] - fConst677 * (fConst678 * fRec146[faust_wrap_sub(i, 2)] + fConst679 * fRec146[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j323 = 0; j323 < 4; j323 = faust_wrap_add(j323, 1)) {
				fRec146_perm[j323] = fRec146_tmp[faust_wrap_add(vsize, j323)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j324 = 0; j324 < 4; j324 = faust_wrap_add(j324, 1)) {
				fRec145_tmp[j324] = fRec145_perm[j324];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec145[i] = fConst677 * (fConst681 * fRec146[i] + fConst682 * fRec146[faust_wrap_sub(i, 1)] + fConst681 * fRec146[faust_wrap_sub(i, 2)]) - fConst683 * (fConst684 * fRec145[faust_wrap_sub(i, 2)] + fConst685 * fRec145[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j325 = 0; j325 < 4; j325 = faust_wrap_add(j325, 1)) {
				fRec145_perm[j325] = fRec145_tmp[faust_wrap_add(vsize, j325)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j326 = 0; j326 < 4; j326 = faust_wrap_add(j326, 1)) {
				fRec144_tmp[j326] = fRec144_perm[j326];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec144[i] = fConst683 * (fConst686 * fRec145[i] + fConst687 * fRec145[faust_wrap_sub(i, 1)] + fConst686 * fRec145[faust_wrap_sub(i, 2)]) - fConst688 * (fConst689 * fRec144[faust_wrap_sub(i, 2)] + fConst690 * fRec144[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j327 = 0; j327 < 4; j327 = faust_wrap_add(j327, 1)) {
				fRec144_perm[j327] = fRec144_tmp[faust_wrap_add(vsize, j327)];
			}
			/* Vectorizable loop 163 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec47[i] = fConst688 * (fConst691 * fRec144[i] + fConst692 * fRec144[faust_wrap_sub(i, 1)] + fConst691 * fRec144[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j328 = 0; j328 < 4; j328 = faust_wrap_add(j328, 1)) {
				fRec143_tmp[j328] = fRec143_perm[j328];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec143[i] = fZec47[i] - fConst695 * (fConst696 * fRec143[faust_wrap_sub(i, 2)] + fConst699 * fRec143[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j329 = 0; j329 < 4; j329 = faust_wrap_add(j329, 1)) {
				fRec143_perm[j329] = fRec143_tmp[faust_wrap_add(vsize, j329)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j330 = 0; j330 < 4; j330 = faust_wrap_add(j330, 1)) {
				fRec142_tmp[j330] = fRec142_perm[j330];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec142[i] = fConst695 * (fConst701 * fRec143[i] + fConst702 * fRec143[faust_wrap_sub(i, 1)] + fConst701 * fRec143[faust_wrap_sub(i, 2)]) - fConst703 * (fConst704 * fRec142[faust_wrap_sub(i, 2)] + fConst705 * fRec142[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j331 = 0; j331 < 4; j331 = faust_wrap_add(j331, 1)) {
				fRec142_perm[j331] = fRec142_tmp[faust_wrap_add(vsize, j331)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j332 = 0; j332 < 4; j332 = faust_wrap_add(j332, 1)) {
				fRec141_tmp[j332] = fRec141_perm[j332];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec141[i] = fConst703 * (fConst707 * fRec142[i] + fConst708 * fRec142[faust_wrap_sub(i, 1)] + fConst707 * fRec142[faust_wrap_sub(i, 2)]) - fConst709 * (fConst710 * fRec141[faust_wrap_sub(i, 2)] + fConst711 * fRec141[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j333 = 0; j333 < 4; j333 = faust_wrap_add(j333, 1)) {
				fRec141_perm[j333] = fRec141_tmp[faust_wrap_add(vsize, j333)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j334 = 0; j334 < 4; j334 = faust_wrap_add(j334, 1)) {
				fRec140_tmp[j334] = fRec140_perm[j334];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec140[i] = fSlow38 * fRec140[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst709 * (fConst713 * fRec141[i] + fConst714 * fRec141[faust_wrap_sub(i, 1)] + fConst713 * fRec141[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j335 = 0; j335 < 4; j335 = faust_wrap_add(j335, 1)) {
				fRec140_perm[j335] = fRec140_tmp[faust_wrap_add(vsize, j335)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j336 = 0; j336 < 4; j336 = faust_wrap_add(j336, 1)) {
				fRec150_tmp[j336] = fRec150_perm[j336];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec150[i] = fZec47[i] - fConst715 * (fConst716 * fRec150[faust_wrap_sub(i, 2)] + fConst717 * fRec150[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j337 = 0; j337 < 4; j337 = faust_wrap_add(j337, 1)) {
				fRec150_perm[j337] = fRec150_tmp[faust_wrap_add(vsize, j337)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j338 = 0; j338 < 4; j338 = faust_wrap_add(j338, 1)) {
				fRec149_tmp[j338] = fRec149_perm[j338];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec149[i] = fConst715 * (fConst719 * fRec150[i] + fConst720 * fRec150[faust_wrap_sub(i, 1)] + fConst719 * fRec150[faust_wrap_sub(i, 2)]) - fConst721 * (fConst722 * fRec149[faust_wrap_sub(i, 2)] + fConst723 * fRec149[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j339 = 0; j339 < 4; j339 = faust_wrap_add(j339, 1)) {
				fRec149_perm[j339] = fRec149_tmp[faust_wrap_add(vsize, j339)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j340 = 0; j340 < 4; j340 = faust_wrap_add(j340, 1)) {
				fRec148_tmp[j340] = fRec148_perm[j340];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec148[i] = fConst721 * (fConst724 * fRec149[i] + fConst725 * fRec149[faust_wrap_sub(i, 1)] + fConst724 * fRec149[faust_wrap_sub(i, 2)]) - fConst726 * (fConst727 * fRec148[faust_wrap_sub(i, 2)] + fConst728 * fRec148[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j341 = 0; j341 < 4; j341 = faust_wrap_add(j341, 1)) {
				fRec148_perm[j341] = fRec148_tmp[faust_wrap_add(vsize, j341)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j342 = 0; j342 < 4; j342 = faust_wrap_add(j342, 1)) {
				fRec147_tmp[j342] = fRec147_perm[j342];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec147[i] = fSlow38 * fRec147[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst726 * (fConst729 * fRec148[i] + fConst730 * fRec148[faust_wrap_sub(i, 1)] + fConst729 * fRec148[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j343 = 0; j343 < 4; j343 = faust_wrap_add(j343, 1)) {
				fRec147_perm[j343] = fRec147_tmp[faust_wrap_add(vsize, j343)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec20_tmp[j76] = fRec20_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fZec29[i] - fConst10 * (fConst11 * fRec20[faust_wrap_sub(i, 2)] + fConst14 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec20_perm[j77] = fRec20_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec19_tmp[j78] = fRec19_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst10 * (fConst16 * fRec20[i] + fConst17 * fRec20[faust_wrap_sub(i, 1)] + fConst16 * fRec20[faust_wrap_sub(i, 2)]) - fConst18 * (fConst19 * fRec19[faust_wrap_sub(i, 2)] + fConst20 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec19_perm[j79] = fRec19_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec18_tmp[j80] = fRec18_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fConst18 * (fConst22 * fRec19[i] + fConst23 * fRec19[faust_wrap_sub(i, 1)] + fConst22 * fRec19[faust_wrap_sub(i, 2)]) - fConst24 * (fConst25 * fRec18[faust_wrap_sub(i, 2)] + fConst26 * fRec18[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec18_perm[j81] = fRec18_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec17_tmp[j82] = fRec17_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] * fSlow38 + std::fabs(fConst24 * (fConst29 * fRec18[i] + fConst30 * fRec18[faust_wrap_sub(i, 1)] + fConst29 * fRec18[faust_wrap_sub(i, 2)])) * fSlow39;
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec17_perm[j83] = fRec17_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec24_tmp[j90] = fRec24_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec30[i] - fConst49 * (fConst50 * fRec24[faust_wrap_sub(i, 2)] + fConst53 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec24_perm[j91] = fRec24_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec23_tmp[j92] = fRec23_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst49 * (fConst55 * fRec24[i] + fConst56 * fRec24[faust_wrap_sub(i, 1)] + fConst55 * fRec24[faust_wrap_sub(i, 2)]) - fConst57 * (fConst58 * fRec23[faust_wrap_sub(i, 2)] + fConst59 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec23_perm[j93] = fRec23_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec22_tmp[j94] = fRec22_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst57 * (fConst61 * fRec23[i] + fConst62 * fRec23[faust_wrap_sub(i, 1)] + fConst61 * fRec23[faust_wrap_sub(i, 2)]) - fConst63 * (fConst64 * fRec22[faust_wrap_sub(i, 2)] + fConst65 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec22_perm[j95] = fRec22_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec21_tmp[j96] = fRec21_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fSlow38 * fRec21[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst63 * (fConst67 * fRec22[i] + fConst68 * fRec22[faust_wrap_sub(i, 1)] + fConst67 * fRec22[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec21_perm[j97] = fRec21_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec31_tmp[j104] = fRec31_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec31[i] - fConst87 * (fConst88 * fRec31[faust_wrap_sub(i, 2)] + fConst91 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec31_perm[j105] = fRec31_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec30_tmp[j106] = fRec30_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst87 * (fConst93 * fRec31[i] + fConst94 * fRec31[faust_wrap_sub(i, 1)] + fConst93 * fRec31[faust_wrap_sub(i, 2)]) - fConst95 * (fConst96 * fRec30[faust_wrap_sub(i, 2)] + fConst97 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec30_perm[j107] = fRec30_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec29_tmp[j108] = fRec29_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst95 * (fConst99 * fRec30[i] + fConst100 * fRec30[faust_wrap_sub(i, 1)] + fConst99 * fRec30[faust_wrap_sub(i, 2)]) - fConst101 * (fConst102 * fRec29[faust_wrap_sub(i, 2)] + fConst103 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec29_perm[j109] = fRec29_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec28_tmp[j110] = fRec28_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fSlow38 * fRec28[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst101 * (fConst105 * fRec29[i] + fConst106 * fRec29[faust_wrap_sub(i, 1)] + fConst105 * fRec29[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec28_perm[j111] = fRec28_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 184 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec38_tmp[j118] = fRec38_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec32[i] - fConst125 * (fConst126 * fRec38[faust_wrap_sub(i, 2)] + fConst129 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec38_perm[j119] = fRec38_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec37_tmp[j120] = fRec37_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst125 * (fConst131 * fRec38[i] + fConst132 * fRec38[faust_wrap_sub(i, 1)] + fConst131 * fRec38[faust_wrap_sub(i, 2)]) - fConst133 * (fConst134 * fRec37[faust_wrap_sub(i, 2)] + fConst135 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec37_perm[j121] = fRec37_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec36_tmp[j122] = fRec36_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst133 * (fConst137 * fRec37[i] + fConst138 * fRec37[faust_wrap_sub(i, 1)] + fConst137 * fRec37[faust_wrap_sub(i, 2)]) - fConst139 * (fConst140 * fRec36[faust_wrap_sub(i, 2)] + fConst141 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec36_perm[j123] = fRec36_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec35_tmp[j124] = fRec35_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fSlow38 * fRec35[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst139 * (fConst143 * fRec36[i] + fConst144 * fRec36[faust_wrap_sub(i, 1)] + fConst143 * fRec36[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec35_perm[j125] = fRec35_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec45_tmp[j132] = fRec45_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec33[i] - fConst163 * (fConst164 * fRec45[faust_wrap_sub(i, 2)] + fConst167 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec45_perm[j133] = fRec45_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec44_tmp[j134] = fRec44_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst163 * (fConst169 * fRec45[i] + fConst170 * fRec45[faust_wrap_sub(i, 1)] + fConst169 * fRec45[faust_wrap_sub(i, 2)]) - fConst171 * (fConst172 * fRec44[faust_wrap_sub(i, 2)] + fConst173 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec44_perm[j135] = fRec44_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 190 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec43_tmp[j136] = fRec43_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst171 * (fConst175 * fRec44[i] + fConst176 * fRec44[faust_wrap_sub(i, 1)] + fConst175 * fRec44[faust_wrap_sub(i, 2)]) - fConst177 * (fConst178 * fRec43[faust_wrap_sub(i, 2)] + fConst179 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec43_perm[j137] = fRec43_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec42_tmp[j138] = fRec42_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fSlow38 * fRec42[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst177 * (fConst181 * fRec43[i] + fConst182 * fRec43[faust_wrap_sub(i, 1)] + fConst181 * fRec43[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec42_perm[j139] = fRec42_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 192 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec52_tmp[j146] = fRec52_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec34[i] - fConst201 * (fConst202 * fRec52[faust_wrap_sub(i, 2)] + fConst205 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec52_perm[j147] = fRec52_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec51_tmp[j148] = fRec51_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst201 * (fConst207 * fRec52[i] + fConst208 * fRec52[faust_wrap_sub(i, 1)] + fConst207 * fRec52[faust_wrap_sub(i, 2)]) - fConst209 * (fConst210 * fRec51[faust_wrap_sub(i, 2)] + fConst211 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec51_perm[j149] = fRec51_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec50_tmp[j150] = fRec50_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst209 * (fConst213 * fRec51[i] + fConst214 * fRec51[faust_wrap_sub(i, 1)] + fConst213 * fRec51[faust_wrap_sub(i, 2)]) - fConst215 * (fConst216 * fRec50[faust_wrap_sub(i, 2)] + fConst217 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec50_perm[j151] = fRec50_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec49_tmp[j152] = fRec49_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fSlow38 * fRec49[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst215 * (fConst219 * fRec50[i] + fConst220 * fRec50[faust_wrap_sub(i, 1)] + fConst219 * fRec50[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec49_perm[j153] = fRec49_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec59_tmp[j160] = fRec59_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec35[i] - fConst239 * (fConst240 * fRec59[faust_wrap_sub(i, 2)] + fConst243 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec59_perm[j161] = fRec59_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec58_tmp[j162] = fRec58_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst239 * (fConst245 * fRec59[i] + fConst246 * fRec59[faust_wrap_sub(i, 1)] + fConst245 * fRec59[faust_wrap_sub(i, 2)]) - fConst247 * (fConst248 * fRec58[faust_wrap_sub(i, 2)] + fConst249 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec58_perm[j163] = fRec58_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 198 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec57_tmp[j164] = fRec57_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst247 * (fConst251 * fRec58[i] + fConst252 * fRec58[faust_wrap_sub(i, 1)] + fConst251 * fRec58[faust_wrap_sub(i, 2)]) - fConst253 * (fConst254 * fRec57[faust_wrap_sub(i, 2)] + fConst255 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec57_perm[j165] = fRec57_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec56_tmp[j166] = fRec56_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fSlow38 * fRec56[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst253 * (fConst257 * fRec57[i] + fConst258 * fRec57[faust_wrap_sub(i, 1)] + fConst257 * fRec57[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec56_perm[j167] = fRec56_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 200 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec66_tmp[j174] = fRec66_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec36[i] - fConst277 * (fConst278 * fRec66[faust_wrap_sub(i, 2)] + fConst281 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec66_perm[j175] = fRec66_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec65_tmp[j176] = fRec65_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst277 * (fConst283 * fRec66[i] + fConst284 * fRec66[faust_wrap_sub(i, 1)] + fConst283 * fRec66[faust_wrap_sub(i, 2)]) - fConst285 * (fConst286 * fRec65[faust_wrap_sub(i, 2)] + fConst287 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec65_perm[j177] = fRec65_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec64_tmp[j178] = fRec64_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst285 * (fConst289 * fRec65[i] + fConst290 * fRec65[faust_wrap_sub(i, 1)] + fConst289 * fRec65[faust_wrap_sub(i, 2)]) - fConst291 * (fConst292 * fRec64[faust_wrap_sub(i, 2)] + fConst293 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec64_perm[j179] = fRec64_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec63_tmp[j180] = fRec63_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fSlow38 * fRec63[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst291 * (fConst295 * fRec64[i] + fConst296 * fRec64[faust_wrap_sub(i, 1)] + fConst295 * fRec64[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec63_perm[j181] = fRec63_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec73_tmp[j188] = fRec73_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec37[i] - fConst315 * (fConst316 * fRec73[faust_wrap_sub(i, 2)] + fConst319 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec73_perm[j189] = fRec73_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec72_tmp[j190] = fRec72_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst315 * (fConst321 * fRec73[i] + fConst322 * fRec73[faust_wrap_sub(i, 1)] + fConst321 * fRec73[faust_wrap_sub(i, 2)]) - fConst323 * (fConst324 * fRec72[faust_wrap_sub(i, 2)] + fConst325 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec72_perm[j191] = fRec72_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec71_tmp[j192] = fRec71_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst323 * (fConst327 * fRec72[i] + fConst328 * fRec72[faust_wrap_sub(i, 1)] + fConst327 * fRec72[faust_wrap_sub(i, 2)]) - fConst329 * (fConst330 * fRec71[faust_wrap_sub(i, 2)] + fConst331 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec71_perm[j193] = fRec71_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 207 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec70_tmp[j194] = fRec70_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fSlow38 * fRec70[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst329 * (fConst333 * fRec71[i] + fConst334 * fRec71[faust_wrap_sub(i, 1)] + fConst333 * fRec71[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec70_perm[j195] = fRec70_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 208 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec80_tmp[j202] = fRec80_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec38[i] - fConst353 * (fConst354 * fRec80[faust_wrap_sub(i, 2)] + fConst357 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec80_perm[j203] = fRec80_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 209 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec79_tmp[j204] = fRec79_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst353 * (fConst359 * fRec80[i] + fConst360 * fRec80[faust_wrap_sub(i, 1)] + fConst359 * fRec80[faust_wrap_sub(i, 2)]) - fConst361 * (fConst362 * fRec79[faust_wrap_sub(i, 2)] + fConst363 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec79_perm[j205] = fRec79_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 210 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec78_tmp[j206] = fRec78_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst361 * (fConst365 * fRec79[i] + fConst366 * fRec79[faust_wrap_sub(i, 1)] + fConst365 * fRec79[faust_wrap_sub(i, 2)]) - fConst367 * (fConst368 * fRec78[faust_wrap_sub(i, 2)] + fConst369 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec78_perm[j207] = fRec78_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 211 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec77_tmp[j208] = fRec77_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fSlow38 * fRec77[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst367 * (fConst371 * fRec78[i] + fConst372 * fRec78[faust_wrap_sub(i, 1)] + fConst371 * fRec78[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec77_perm[j209] = fRec77_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 212 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec87_tmp[j216] = fRec87_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec39[i] - fConst391 * (fConst392 * fRec87[faust_wrap_sub(i, 2)] + fConst395 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec87_perm[j217] = fRec87_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 213 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec86_tmp[j218] = fRec86_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst391 * (fConst397 * fRec87[i] + fConst398 * fRec87[faust_wrap_sub(i, 1)] + fConst397 * fRec87[faust_wrap_sub(i, 2)]) - fConst399 * (fConst400 * fRec86[faust_wrap_sub(i, 2)] + fConst401 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec86_perm[j219] = fRec86_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 214 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec85_tmp[j220] = fRec85_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst399 * (fConst403 * fRec86[i] + fConst404 * fRec86[faust_wrap_sub(i, 1)] + fConst403 * fRec86[faust_wrap_sub(i, 2)]) - fConst405 * (fConst406 * fRec85[faust_wrap_sub(i, 2)] + fConst407 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec85_perm[j221] = fRec85_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 215 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec84_tmp[j222] = fRec84_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fSlow38 * fRec84[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst405 * (fConst409 * fRec85[i] + fConst410 * fRec85[faust_wrap_sub(i, 1)] + fConst409 * fRec85[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec84_perm[j223] = fRec84_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Vectorizable loop 216 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec17[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec21[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec28[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec35[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec42[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec49[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec56[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec63[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec70[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec77[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec84[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec91[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec98[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec105[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec112[i]));
				fVbargraph15 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec119[i]));
				fVbargraph16 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec126[i]));
				fVbargraph17 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec133[i]));
				fVbargraph18 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec140[i]));
				fVbargraph19 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec147[i]));
				fZec48[i] = fZec29[i];
			}
			/* Vectorizable loop 217 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec48[i]);
			}
			/* Vectorizable loop 218 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec48[i]);
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
				fRec5_tmp[j0] = fRec5_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fSlow0 + 0.999 * fRec5[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec5_perm[j1] = fRec5_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec7_tmp[j2] = fRec7_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fRec7[faust_wrap_sub(i, 1)] * fSlow2 + fSlow3;
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec7_perm[j3] = fRec7_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = std::max<double>(2e+01, std::fabs(fRec7[i]));
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec6_tmp[j4] = fRec6_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fRec6[faust_wrap_sub(i, 1)] + fConst1 * fZec0[i];
				fRec6[i] = fZec1[i] - std::floor(fZec1[i]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec6_perm[j5] = fRec6_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec7[i]));
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec8_tmp[j6] = fRec8_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fRec8[faust_wrap_sub(i, 1)] + fConst1 * fZec2[i];
				fRec8[i] = fZec3[i] - std::floor(fZec3[i]);
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec8_perm[j7] = fRec8_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec7[i]));
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec9_tmp[j8] = fRec9_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fRec9[faust_wrap_sub(i, 1)] + fConst1 * fZec4[i];
				fRec9[i] = fZec5[i] - std::floor(fZec5[i]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec9_perm[j9] = fRec9_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				iRec10_tmp[j10] = iRec10_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec10[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec10[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				iRec10_perm[j11] = iRec10_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec10[i]);
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec11_tmp[j12] = fRec11_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = 0.5221894 * fRec11[faust_wrap_sub(i, 3)] + fZec6[i] + 2.494956002 * fRec11[faust_wrap_sub(i, 1)] - 2.017265875 * fRec11[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec11_perm[j13] = fRec11_tmp[faust_wrap_add(vsize, j13)];
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
				fZec7[i] = 2.0 * fRec6[i];
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
				fZec13[i] = 2.0 * fRec8[i];
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
				fZec16[i] = 2.0 * fRec9[i];
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
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fYec18_tmp[j52] = fYec18_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec18[i] = fRec5[i] * ((iSlow10) ? static_cast<double>(input0[i]) : ((iSlow11) ? ((iSlow16) ? 0.049922035 * fRec11[i] + 0.050612699 * fRec11[faust_wrap_sub(i, 2)] - (0.095993537 * fRec11[faust_wrap_sub(i, 1)] + 0.004408786 * fRec11[faust_wrap_sub(i, 3)]) : fZec6[i]) : 0.3333333333333333 * fRec5[i] * (((iSlow13) ? ((iSlow15) ? fConst5 * (fZec12[i] * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)]) / fZec0[i]) : fConst4 * (fZec10[i] * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)]) / fZec0[i])) : ((iSlow14) ? fConst3 * (fZec9[i] * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)]) / fZec0[i]) : fZec8[i])) + ((iSlow13) ? ((iSlow15) ? fConst5 * (fZec12[i] * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)]) / fZec2[i]) : fConst4 * (fZec10[i] * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)]) / fZec2[i])) : ((iSlow14) ? fConst3 * (fZec9[i] * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)]) / fZec2[i]) : fZec14[i])) + ((iSlow13) ? ((iSlow15) ? fConst5 * (fZec12[i] * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)]) / fZec4[i]) : fConst4 * (fZec10[i] * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)]) / fZec4[i])) : ((iSlow14) ? fConst3 * (fZec9[i] * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)]) / fZec4[i]) : fZec17[i])))));
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fYec18_perm[j53] = fYec18_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 43 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec4_tmp[j54] = fRec4_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = -(fSlow8 * (fSlow9 * fRec4[faust_wrap_sub(i, 1)] - fSlow7 * (fYec18[i] - fYec18[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec4_perm[j55] = fRec4_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec3_tmp[j56] = fRec3_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = fRec4[i] - fSlow17 * (fSlow18 * fRec3[faust_wrap_sub(i, 2)] + fSlow20 * fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec3_perm[j57] = fRec3_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 45 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec13_tmp[j58] = fRec13_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = -(fSlow8 * (fSlow9 * fRec13[faust_wrap_sub(i, 1)] - (fYec18[i] + fYec18[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec13_perm[j59] = fRec13_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec12_tmp[j60] = fRec12_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fRec13[i] - fSlow17 * (fSlow18 * fRec12[faust_wrap_sub(i, 2)] + fSlow20 * fRec12[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec12_perm[j61] = fRec12_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 47 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec14_tmp[j62] = fRec14_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fSlow21 + 0.999 * fRec14[faust_wrap_sub(i, 1)];
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec14_perm[j63] = fRec14_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = std::pow(2.0, 0.08333333333333333 * (fRec14[i] + -49.0));
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = std::tan(fConst6 * fZec19[i]);
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = 1.0 / fZec20[i];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fZec19[i] / std::sin(fConst7 * fZec19[i]);
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fSlow26 * fZec22[i];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fSlow27 * fZec22[i];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = ((iSlow24) ? fZec24[i] : fZec23[i]);
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = (fZec21[i] + fZec25[i]) / fZec20[i] + 1.0;
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec2_tmp[j64] = fRec2_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = 2.0 * fRec2[faust_wrap_sub(i, 1)] * (1.0 - 1.0 / mydsp_faustpower2_f(fZec20[i]));
				fRec2[i] = fSlow17 * (fSlow19 * (fRec3[faust_wrap_sub(i, 2)] + (fRec3[i] - 2.0 * fRec3[faust_wrap_sub(i, 1)])) + fSlow22 * (fRec12[faust_wrap_sub(i, 2)] + fRec12[i] + 2.0 * fRec12[faust_wrap_sub(i, 1)])) - (fRec2[faust_wrap_sub(i, 2)] * ((fZec21[i] - fZec25[i]) / fZec20[i] + 1.0) + fZec26[i]) / fZec27[i];
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec2_perm[j65] = fRec2_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec28[i] = ((iSlow24) ? fZec23[i] : fZec24[i]);
			}
			/* Vectorizable loop 58 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fYec19_tmp[j66] = fYec19_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fYec19[i] = (fZec26[i] + fRec2[i] * ((fZec21[i] + fZec28[i]) / fZec20[i] + 1.0) + fRec2[faust_wrap_sub(i, 2)] * ((fZec21[i] - fZec28[i]) / fZec20[i] + 1.0)) / fZec27[i];
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fYec19_perm[j67] = fYec19_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 59 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec1_tmp[j68] = fRec1_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = -(fSlow30 * (fSlow31 * fRec1[faust_wrap_sub(i, 1)] - (fYec19[i] + fYec19[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec1_perm[j69] = fRec1_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec0_tmp[j70] = fRec0_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fRec1[i] - fSlow32 * (fSlow33 * fRec0[faust_wrap_sub(i, 2)] + fSlow35 * fRec0[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec0_perm[j71] = fRec0_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 61 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec16_tmp[j72] = fRec16_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = -(fSlow30 * (fSlow31 * fRec16[faust_wrap_sub(i, 1)] - fSlow29 * (fYec19[i] - fYec19[faust_wrap_sub(i, 1)])));
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec16_perm[j73] = fRec16_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec15_tmp[j74] = fRec15_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fRec16[i] - fSlow32 * (fSlow33 * fRec15[faust_wrap_sub(i, 2)] + fSlow35 * fRec15[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec15_perm[j75] = fRec15_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec29[i] = fSlow32 * (fRec0[faust_wrap_sub(i, 2)] + fRec0[i] + 2.0 * fRec0[faust_wrap_sub(i, 1)] + fSlow36 * (fRec15[faust_wrap_sub(i, 2)] + (fRec15[i] - 2.0 * fRec15[faust_wrap_sub(i, 1)])));
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec27_tmp[j84] = fRec27_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fZec29[i] - fConst31 * (fConst32 * fRec27[faust_wrap_sub(i, 2)] + fConst33 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec27_perm[j85] = fRec27_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec26_tmp[j86] = fRec26_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst31 * (fConst35 * fRec27[i] + fConst36 * fRec27[faust_wrap_sub(i, 1)] + fConst35 * fRec27[faust_wrap_sub(i, 2)]) - fConst37 * (fConst38 * fRec26[faust_wrap_sub(i, 2)] + fConst39 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec26_perm[j87] = fRec26_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec25_tmp[j88] = fRec25_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fConst37 * (fConst40 * fRec26[i] + fConst41 * fRec26[faust_wrap_sub(i, 1)] + fConst40 * fRec26[faust_wrap_sub(i, 2)]) - fConst42 * (fConst43 * fRec25[faust_wrap_sub(i, 2)] + fConst44 * fRec25[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec25_perm[j89] = fRec25_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec30[i] = fConst42 * (fConst45 * fRec25[i] + fConst46 * fRec25[faust_wrap_sub(i, 1)] + fConst45 * fRec25[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec34_tmp[j98] = fRec34_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fZec30[i] - fConst69 * (fConst70 * fRec34[faust_wrap_sub(i, 2)] + fConst71 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec34_perm[j99] = fRec34_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec33_tmp[j100] = fRec33_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst69 * (fConst73 * fRec34[i] + fConst74 * fRec34[faust_wrap_sub(i, 1)] + fConst73 * fRec34[faust_wrap_sub(i, 2)]) - fConst75 * (fConst76 * fRec33[faust_wrap_sub(i, 2)] + fConst77 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec33_perm[j101] = fRec33_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec32_tmp[j102] = fRec32_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fConst75 * (fConst78 * fRec33[i] + fConst79 * fRec33[faust_wrap_sub(i, 1)] + fConst78 * fRec33[faust_wrap_sub(i, 2)]) - fConst80 * (fConst81 * fRec32[faust_wrap_sub(i, 2)] + fConst82 * fRec32[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec32_perm[j103] = fRec32_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec31[i] = fConst80 * (fConst83 * fRec32[i] + fConst84 * fRec32[faust_wrap_sub(i, 1)] + fConst83 * fRec32[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec41_tmp[j112] = fRec41_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fZec31[i] - fConst107 * (fConst108 * fRec41[faust_wrap_sub(i, 2)] + fConst109 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec41_perm[j113] = fRec41_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec40_tmp[j114] = fRec40_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst107 * (fConst111 * fRec41[i] + fConst112 * fRec41[faust_wrap_sub(i, 1)] + fConst111 * fRec41[faust_wrap_sub(i, 2)]) - fConst113 * (fConst114 * fRec40[faust_wrap_sub(i, 2)] + fConst115 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec40_perm[j115] = fRec40_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec39_tmp[j116] = fRec39_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fConst113 * (fConst116 * fRec40[i] + fConst117 * fRec40[faust_wrap_sub(i, 1)] + fConst116 * fRec40[faust_wrap_sub(i, 2)]) - fConst118 * (fConst119 * fRec39[faust_wrap_sub(i, 2)] + fConst120 * fRec39[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec39_perm[j117] = fRec39_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec32[i] = fConst118 * (fConst121 * fRec39[i] + fConst122 * fRec39[faust_wrap_sub(i, 1)] + fConst121 * fRec39[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec48_tmp[j126] = fRec48_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fZec32[i] - fConst145 * (fConst146 * fRec48[faust_wrap_sub(i, 2)] + fConst147 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec48_perm[j127] = fRec48_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec47_tmp[j128] = fRec47_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst145 * (fConst149 * fRec48[i] + fConst150 * fRec48[faust_wrap_sub(i, 1)] + fConst149 * fRec48[faust_wrap_sub(i, 2)]) - fConst151 * (fConst152 * fRec47[faust_wrap_sub(i, 2)] + fConst153 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec47_perm[j129] = fRec47_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec46_tmp[j130] = fRec46_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fConst151 * (fConst154 * fRec47[i] + fConst155 * fRec47[faust_wrap_sub(i, 1)] + fConst154 * fRec47[faust_wrap_sub(i, 2)]) - fConst156 * (fConst157 * fRec46[faust_wrap_sub(i, 2)] + fConst158 * fRec46[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec46_perm[j131] = fRec46_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec33[i] = fConst156 * (fConst159 * fRec46[i] + fConst160 * fRec46[faust_wrap_sub(i, 1)] + fConst159 * fRec46[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec55_tmp[j140] = fRec55_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fZec33[i] - fConst183 * (fConst184 * fRec55[faust_wrap_sub(i, 2)] + fConst185 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec55_perm[j141] = fRec55_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec54_tmp[j142] = fRec54_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst183 * (fConst187 * fRec55[i] + fConst188 * fRec55[faust_wrap_sub(i, 1)] + fConst187 * fRec55[faust_wrap_sub(i, 2)]) - fConst189 * (fConst190 * fRec54[faust_wrap_sub(i, 2)] + fConst191 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec54_perm[j143] = fRec54_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec53_tmp[j144] = fRec53_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fConst189 * (fConst192 * fRec54[i] + fConst193 * fRec54[faust_wrap_sub(i, 1)] + fConst192 * fRec54[faust_wrap_sub(i, 2)]) - fConst194 * (fConst195 * fRec53[faust_wrap_sub(i, 2)] + fConst196 * fRec53[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec53_perm[j145] = fRec53_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec34[i] = fConst194 * (fConst197 * fRec53[i] + fConst198 * fRec53[faust_wrap_sub(i, 1)] + fConst197 * fRec53[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec62_tmp[j154] = fRec62_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fZec34[i] - fConst221 * (fConst222 * fRec62[faust_wrap_sub(i, 2)] + fConst223 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec62_perm[j155] = fRec62_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec61_tmp[j156] = fRec61_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst221 * (fConst225 * fRec62[i] + fConst226 * fRec62[faust_wrap_sub(i, 1)] + fConst225 * fRec62[faust_wrap_sub(i, 2)]) - fConst227 * (fConst228 * fRec61[faust_wrap_sub(i, 2)] + fConst229 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec61_perm[j157] = fRec61_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec60_tmp[j158] = fRec60_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fConst227 * (fConst230 * fRec61[i] + fConst231 * fRec61[faust_wrap_sub(i, 1)] + fConst230 * fRec61[faust_wrap_sub(i, 2)]) - fConst232 * (fConst233 * fRec60[faust_wrap_sub(i, 2)] + fConst234 * fRec60[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec60_perm[j159] = fRec60_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec35[i] = fConst232 * (fConst235 * fRec60[i] + fConst236 * fRec60[faust_wrap_sub(i, 1)] + fConst235 * fRec60[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec69_tmp[j168] = fRec69_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fZec35[i] - fConst259 * (fConst260 * fRec69[faust_wrap_sub(i, 2)] + fConst261 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec69_perm[j169] = fRec69_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec68_tmp[j170] = fRec68_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst259 * (fConst263 * fRec69[i] + fConst264 * fRec69[faust_wrap_sub(i, 1)] + fConst263 * fRec69[faust_wrap_sub(i, 2)]) - fConst265 * (fConst266 * fRec68[faust_wrap_sub(i, 2)] + fConst267 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec68_perm[j171] = fRec68_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec67_tmp[j172] = fRec67_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fConst265 * (fConst268 * fRec68[i] + fConst269 * fRec68[faust_wrap_sub(i, 1)] + fConst268 * fRec68[faust_wrap_sub(i, 2)]) - fConst270 * (fConst271 * fRec67[faust_wrap_sub(i, 2)] + fConst272 * fRec67[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec67_perm[j173] = fRec67_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec36[i] = fConst270 * (fConst273 * fRec67[i] + fConst274 * fRec67[faust_wrap_sub(i, 1)] + fConst273 * fRec67[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec76_tmp[j182] = fRec76_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fZec36[i] - fConst297 * (fConst298 * fRec76[faust_wrap_sub(i, 2)] + fConst299 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec76_perm[j183] = fRec76_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec75_tmp[j184] = fRec75_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst297 * (fConst301 * fRec76[i] + fConst302 * fRec76[faust_wrap_sub(i, 1)] + fConst301 * fRec76[faust_wrap_sub(i, 2)]) - fConst303 * (fConst304 * fRec75[faust_wrap_sub(i, 2)] + fConst305 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec75_perm[j185] = fRec75_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec74_tmp[j186] = fRec74_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fConst303 * (fConst306 * fRec75[i] + fConst307 * fRec75[faust_wrap_sub(i, 1)] + fConst306 * fRec75[faust_wrap_sub(i, 2)]) - fConst308 * (fConst309 * fRec74[faust_wrap_sub(i, 2)] + fConst310 * fRec74[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec74_perm[j187] = fRec74_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec37[i] = fConst308 * (fConst311 * fRec74[i] + fConst312 * fRec74[faust_wrap_sub(i, 1)] + fConst311 * fRec74[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec83_tmp[j196] = fRec83_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fZec37[i] - fConst335 * (fConst336 * fRec83[faust_wrap_sub(i, 2)] + fConst337 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec83_perm[j197] = fRec83_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec82_tmp[j198] = fRec82_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst335 * (fConst339 * fRec83[i] + fConst340 * fRec83[faust_wrap_sub(i, 1)] + fConst339 * fRec83[faust_wrap_sub(i, 2)]) - fConst341 * (fConst342 * fRec82[faust_wrap_sub(i, 2)] + fConst343 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec82_perm[j199] = fRec82_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec81_tmp[j200] = fRec81_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fConst341 * (fConst344 * fRec82[i] + fConst345 * fRec82[faust_wrap_sub(i, 1)] + fConst344 * fRec82[faust_wrap_sub(i, 2)]) - fConst346 * (fConst347 * fRec81[faust_wrap_sub(i, 2)] + fConst348 * fRec81[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec81_perm[j201] = fRec81_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec38[i] = fConst346 * (fConst349 * fRec81[i] + fConst350 * fRec81[faust_wrap_sub(i, 1)] + fConst349 * fRec81[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec90_tmp[j210] = fRec90_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fZec38[i] - fConst373 * (fConst374 * fRec90[faust_wrap_sub(i, 2)] + fConst375 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec90_perm[j211] = fRec90_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec89_tmp[j212] = fRec89_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst373 * (fConst377 * fRec90[i] + fConst378 * fRec90[faust_wrap_sub(i, 1)] + fConst377 * fRec90[faust_wrap_sub(i, 2)]) - fConst379 * (fConst380 * fRec89[faust_wrap_sub(i, 2)] + fConst381 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec89_perm[j213] = fRec89_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec88_tmp[j214] = fRec88_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fConst379 * (fConst382 * fRec89[i] + fConst383 * fRec89[faust_wrap_sub(i, 1)] + fConst382 * fRec89[faust_wrap_sub(i, 2)]) - fConst384 * (fConst385 * fRec88[faust_wrap_sub(i, 2)] + fConst386 * fRec88[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec88_perm[j215] = fRec88_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec39[i] = fConst384 * (fConst387 * fRec88[i] + fConst388 * fRec88[faust_wrap_sub(i, 1)] + fConst387 * fRec88[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec97_tmp[j224] = fRec97_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fZec39[i] - fConst411 * (fConst412 * fRec97[faust_wrap_sub(i, 2)] + fConst413 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec97_perm[j225] = fRec97_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec96_tmp[j226] = fRec96_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst411 * (fConst415 * fRec97[i] + fConst416 * fRec97[faust_wrap_sub(i, 1)] + fConst415 * fRec97[faust_wrap_sub(i, 2)]) - fConst417 * (fConst418 * fRec96[faust_wrap_sub(i, 2)] + fConst419 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec96_perm[j227] = fRec96_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec95_tmp[j228] = fRec95_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fConst417 * (fConst420 * fRec96[i] + fConst421 * fRec96[faust_wrap_sub(i, 1)] + fConst420 * fRec96[faust_wrap_sub(i, 2)]) - fConst422 * (fConst423 * fRec95[faust_wrap_sub(i, 2)] + fConst424 * fRec95[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec95_perm[j229] = fRec95_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec40[i] = fConst422 * (fConst425 * fRec95[i] + fConst426 * fRec95[faust_wrap_sub(i, 1)] + fConst425 * fRec95[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec94_tmp[j230] = fRec94_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec40[i] - fConst429 * (fConst430 * fRec94[faust_wrap_sub(i, 2)] + fConst433 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec94_perm[j231] = fRec94_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec93_tmp[j232] = fRec93_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst429 * (fConst435 * fRec94[i] + fConst436 * fRec94[faust_wrap_sub(i, 1)] + fConst435 * fRec94[faust_wrap_sub(i, 2)]) - fConst437 * (fConst438 * fRec93[faust_wrap_sub(i, 2)] + fConst439 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec93_perm[j233] = fRec93_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec92_tmp[j234] = fRec92_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst437 * (fConst441 * fRec93[i] + fConst442 * fRec93[faust_wrap_sub(i, 1)] + fConst441 * fRec93[faust_wrap_sub(i, 2)]) - fConst443 * (fConst444 * fRec92[faust_wrap_sub(i, 2)] + fConst445 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec92_perm[j235] = fRec92_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 111 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec91_tmp[j236] = fRec91_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fSlow38 * fRec91[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst443 * (fConst447 * fRec92[i] + fConst448 * fRec92[faust_wrap_sub(i, 1)] + fConst447 * fRec92[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec91_perm[j237] = fRec91_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec104_tmp[j238] = fRec104_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fZec40[i] - fConst449 * (fConst450 * fRec104[faust_wrap_sub(i, 2)] + fConst451 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec104_perm[j239] = fRec104_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec103_tmp[j240] = fRec103_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst449 * (fConst453 * fRec104[i] + fConst454 * fRec104[faust_wrap_sub(i, 1)] + fConst453 * fRec104[faust_wrap_sub(i, 2)]) - fConst455 * (fConst456 * fRec103[faust_wrap_sub(i, 2)] + fConst457 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec103_perm[j241] = fRec103_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec102_tmp[j242] = fRec102_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fConst455 * (fConst458 * fRec103[i] + fConst459 * fRec103[faust_wrap_sub(i, 1)] + fConst458 * fRec103[faust_wrap_sub(i, 2)]) - fConst460 * (fConst461 * fRec102[faust_wrap_sub(i, 2)] + fConst462 * fRec102[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec102_perm[j243] = fRec102_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec41[i] = fConst460 * (fConst463 * fRec102[i] + fConst464 * fRec102[faust_wrap_sub(i, 1)] + fConst463 * fRec102[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec101_tmp[j244] = fRec101_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec41[i] - fConst467 * (fConst468 * fRec101[faust_wrap_sub(i, 2)] + fConst471 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec101_perm[j245] = fRec101_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec100_tmp[j246] = fRec100_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst467 * (fConst473 * fRec101[i] + fConst474 * fRec101[faust_wrap_sub(i, 1)] + fConst473 * fRec101[faust_wrap_sub(i, 2)]) - fConst475 * (fConst476 * fRec100[faust_wrap_sub(i, 2)] + fConst477 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec100_perm[j247] = fRec100_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec99_tmp[j248] = fRec99_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst475 * (fConst479 * fRec100[i] + fConst480 * fRec100[faust_wrap_sub(i, 1)] + fConst479 * fRec100[faust_wrap_sub(i, 2)]) - fConst481 * (fConst482 * fRec99[faust_wrap_sub(i, 2)] + fConst483 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec99_perm[j249] = fRec99_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 119 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec98_tmp[j250] = fRec98_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fSlow38 * fRec98[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst481 * (fConst485 * fRec99[i] + fConst486 * fRec99[faust_wrap_sub(i, 1)] + fConst485 * fRec99[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec98_perm[j251] = fRec98_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec111_tmp[j252] = fRec111_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fZec41[i] - fConst487 * (fConst488 * fRec111[faust_wrap_sub(i, 2)] + fConst489 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec111_perm[j253] = fRec111_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec110_tmp[j254] = fRec110_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst487 * (fConst491 * fRec111[i] + fConst492 * fRec111[faust_wrap_sub(i, 1)] + fConst491 * fRec111[faust_wrap_sub(i, 2)]) - fConst493 * (fConst494 * fRec110[faust_wrap_sub(i, 2)] + fConst495 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec110_perm[j255] = fRec110_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec109_tmp[j256] = fRec109_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fConst493 * (fConst496 * fRec110[i] + fConst497 * fRec110[faust_wrap_sub(i, 1)] + fConst496 * fRec110[faust_wrap_sub(i, 2)]) - fConst498 * (fConst499 * fRec109[faust_wrap_sub(i, 2)] + fConst500 * fRec109[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec109_perm[j257] = fRec109_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Vectorizable loop 123 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec42[i] = fConst498 * (fConst501 * fRec109[i] + fConst502 * fRec109[faust_wrap_sub(i, 1)] + fConst501 * fRec109[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec108_tmp[j258] = fRec108_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fZec42[i] - fConst505 * (fConst506 * fRec108[faust_wrap_sub(i, 2)] + fConst509 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec108_perm[j259] = fRec108_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec107_tmp[j260] = fRec107_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst505 * (fConst511 * fRec108[i] + fConst512 * fRec108[faust_wrap_sub(i, 1)] + fConst511 * fRec108[faust_wrap_sub(i, 2)]) - fConst513 * (fConst514 * fRec107[faust_wrap_sub(i, 2)] + fConst515 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec107_perm[j261] = fRec107_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec106_tmp[j262] = fRec106_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fConst513 * (fConst517 * fRec107[i] + fConst518 * fRec107[faust_wrap_sub(i, 1)] + fConst517 * fRec107[faust_wrap_sub(i, 2)]) - fConst519 * (fConst520 * fRec106[faust_wrap_sub(i, 2)] + fConst521 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec106_perm[j263] = fRec106_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec105_tmp[j264] = fRec105_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fSlow38 * fRec105[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst519 * (fConst523 * fRec106[i] + fConst524 * fRec106[faust_wrap_sub(i, 1)] + fConst523 * fRec106[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec105_perm[j265] = fRec105_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec118_tmp[j266] = fRec118_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fZec42[i] - fConst525 * (fConst526 * fRec118[faust_wrap_sub(i, 2)] + fConst527 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec118_perm[j267] = fRec118_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec117_tmp[j268] = fRec117_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fConst525 * (fConst529 * fRec118[i] + fConst530 * fRec118[faust_wrap_sub(i, 1)] + fConst529 * fRec118[faust_wrap_sub(i, 2)]) - fConst531 * (fConst532 * fRec117[faust_wrap_sub(i, 2)] + fConst533 * fRec117[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec117_perm[j269] = fRec117_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec116_tmp[j270] = fRec116_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fConst531 * (fConst534 * fRec117[i] + fConst535 * fRec117[faust_wrap_sub(i, 1)] + fConst534 * fRec117[faust_wrap_sub(i, 2)]) - fConst536 * (fConst537 * fRec116[faust_wrap_sub(i, 2)] + fConst538 * fRec116[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec116_perm[j271] = fRec116_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Vectorizable loop 131 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec43[i] = fConst536 * (fConst539 * fRec116[i] + fConst540 * fRec116[faust_wrap_sub(i, 1)] + fConst539 * fRec116[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec115_tmp[j272] = fRec115_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fZec43[i] - fConst543 * (fConst544 * fRec115[faust_wrap_sub(i, 2)] + fConst547 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec115_perm[j273] = fRec115_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec114_tmp[j274] = fRec114_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst543 * (fConst549 * fRec115[i] + fConst550 * fRec115[faust_wrap_sub(i, 1)] + fConst549 * fRec115[faust_wrap_sub(i, 2)]) - fConst551 * (fConst552 * fRec114[faust_wrap_sub(i, 2)] + fConst553 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec114_perm[j275] = fRec114_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec113_tmp[j276] = fRec113_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fConst551 * (fConst555 * fRec114[i] + fConst556 * fRec114[faust_wrap_sub(i, 1)] + fConst555 * fRec114[faust_wrap_sub(i, 2)]) - fConst557 * (fConst558 * fRec113[faust_wrap_sub(i, 2)] + fConst559 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec113_perm[j277] = fRec113_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec112_tmp[j278] = fRec112_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fSlow38 * fRec112[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst557 * (fConst561 * fRec113[i] + fConst562 * fRec113[faust_wrap_sub(i, 1)] + fConst561 * fRec113[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec112_perm[j279] = fRec112_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec125_tmp[j280] = fRec125_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fZec43[i] - fConst563 * (fConst564 * fRec125[faust_wrap_sub(i, 2)] + fConst565 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec125_perm[j281] = fRec125_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec124_tmp[j282] = fRec124_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fConst563 * (fConst567 * fRec125[i] + fConst568 * fRec125[faust_wrap_sub(i, 1)] + fConst567 * fRec125[faust_wrap_sub(i, 2)]) - fConst569 * (fConst570 * fRec124[faust_wrap_sub(i, 2)] + fConst571 * fRec124[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec124_perm[j283] = fRec124_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec123_tmp[j284] = fRec123_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fConst569 * (fConst572 * fRec124[i] + fConst573 * fRec124[faust_wrap_sub(i, 1)] + fConst572 * fRec124[faust_wrap_sub(i, 2)]) - fConst574 * (fConst575 * fRec123[faust_wrap_sub(i, 2)] + fConst576 * fRec123[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec123_perm[j285] = fRec123_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Vectorizable loop 139 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec44[i] = fConst574 * (fConst577 * fRec123[i] + fConst578 * fRec123[faust_wrap_sub(i, 1)] + fConst577 * fRec123[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec122_tmp[j286] = fRec122_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fZec44[i] - fConst581 * (fConst582 * fRec122[faust_wrap_sub(i, 2)] + fConst585 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec122_perm[j287] = fRec122_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec121_tmp[j288] = fRec121_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst581 * (fConst587 * fRec122[i] + fConst588 * fRec122[faust_wrap_sub(i, 1)] + fConst587 * fRec122[faust_wrap_sub(i, 2)]) - fConst589 * (fConst590 * fRec121[faust_wrap_sub(i, 2)] + fConst591 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec121_perm[j289] = fRec121_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec120_tmp[j290] = fRec120_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fConst589 * (fConst593 * fRec121[i] + fConst594 * fRec121[faust_wrap_sub(i, 1)] + fConst593 * fRec121[faust_wrap_sub(i, 2)]) - fConst595 * (fConst596 * fRec120[faust_wrap_sub(i, 2)] + fConst597 * fRec120[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec120_perm[j291] = fRec120_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec119_tmp[j292] = fRec119_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fSlow38 * fRec119[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst595 * (fConst599 * fRec120[i] + fConst600 * fRec120[faust_wrap_sub(i, 1)] + fConst599 * fRec120[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec119_perm[j293] = fRec119_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec132_tmp[j294] = fRec132_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec132[i] = fZec44[i] - fConst601 * (fConst602 * fRec132[faust_wrap_sub(i, 2)] + fConst603 * fRec132[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec132_perm[j295] = fRec132_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec131_tmp[j296] = fRec131_perm[j296];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec131[i] = fConst601 * (fConst605 * fRec132[i] + fConst606 * fRec132[faust_wrap_sub(i, 1)] + fConst605 * fRec132[faust_wrap_sub(i, 2)]) - fConst607 * (fConst608 * fRec131[faust_wrap_sub(i, 2)] + fConst609 * fRec131[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec131_perm[j297] = fRec131_tmp[faust_wrap_add(vsize, j297)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec130_tmp[j298] = fRec130_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec130[i] = fConst607 * (fConst610 * fRec131[i] + fConst611 * fRec131[faust_wrap_sub(i, 1)] + fConst610 * fRec131[faust_wrap_sub(i, 2)]) - fConst612 * (fConst613 * fRec130[faust_wrap_sub(i, 2)] + fConst614 * fRec130[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec130_perm[j299] = fRec130_tmp[faust_wrap_add(vsize, j299)];
			}
			/* Vectorizable loop 147 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec45[i] = fConst612 * (fConst615 * fRec130[i] + fConst616 * fRec130[faust_wrap_sub(i, 1)] + fConst615 * fRec130[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec129_tmp[j300] = fRec129_perm[j300];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec129[i] = fZec45[i] - fConst619 * (fConst620 * fRec129[faust_wrap_sub(i, 2)] + fConst623 * fRec129[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec129_perm[j301] = fRec129_tmp[faust_wrap_add(vsize, j301)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec128_tmp[j302] = fRec128_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec128[i] = fConst619 * (fConst625 * fRec129[i] + fConst626 * fRec129[faust_wrap_sub(i, 1)] + fConst625 * fRec129[faust_wrap_sub(i, 2)]) - fConst627 * (fConst628 * fRec128[faust_wrap_sub(i, 2)] + fConst629 * fRec128[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec128_perm[j303] = fRec128_tmp[faust_wrap_add(vsize, j303)];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec127_tmp[j304] = fRec127_perm[j304];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fConst627 * (fConst631 * fRec128[i] + fConst632 * fRec128[faust_wrap_sub(i, 1)] + fConst631 * fRec128[faust_wrap_sub(i, 2)]) - fConst633 * (fConst634 * fRec127[faust_wrap_sub(i, 2)] + fConst635 * fRec127[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec127_perm[j305] = fRec127_tmp[faust_wrap_add(vsize, j305)];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec126_tmp[j306] = fRec126_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fSlow38 * fRec126[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst633 * (fConst637 * fRec127[i] + fConst638 * fRec127[faust_wrap_sub(i, 1)] + fConst637 * fRec127[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec126_perm[j307] = fRec126_tmp[faust_wrap_add(vsize, j307)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j308 = 0; j308 < 4; j308 = faust_wrap_add(j308, 1)) {
				fRec139_tmp[j308] = fRec139_perm[j308];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec139[i] = fZec45[i] - fConst639 * (fConst640 * fRec139[faust_wrap_sub(i, 2)] + fConst641 * fRec139[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j309 = 0; j309 < 4; j309 = faust_wrap_add(j309, 1)) {
				fRec139_perm[j309] = fRec139_tmp[faust_wrap_add(vsize, j309)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j310 = 0; j310 < 4; j310 = faust_wrap_add(j310, 1)) {
				fRec138_tmp[j310] = fRec138_perm[j310];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec138[i] = fConst639 * (fConst643 * fRec139[i] + fConst644 * fRec139[faust_wrap_sub(i, 1)] + fConst643 * fRec139[faust_wrap_sub(i, 2)]) - fConst645 * (fConst646 * fRec138[faust_wrap_sub(i, 2)] + fConst647 * fRec138[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j311 = 0; j311 < 4; j311 = faust_wrap_add(j311, 1)) {
				fRec138_perm[j311] = fRec138_tmp[faust_wrap_add(vsize, j311)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j312 = 0; j312 < 4; j312 = faust_wrap_add(j312, 1)) {
				fRec137_tmp[j312] = fRec137_perm[j312];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec137[i] = fConst645 * (fConst648 * fRec138[i] + fConst649 * fRec138[faust_wrap_sub(i, 1)] + fConst648 * fRec138[faust_wrap_sub(i, 2)]) - fConst650 * (fConst651 * fRec137[faust_wrap_sub(i, 2)] + fConst652 * fRec137[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j313 = 0; j313 < 4; j313 = faust_wrap_add(j313, 1)) {
				fRec137_perm[j313] = fRec137_tmp[faust_wrap_add(vsize, j313)];
			}
			/* Vectorizable loop 155 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec46[i] = fConst650 * (fConst653 * fRec137[i] + fConst654 * fRec137[faust_wrap_sub(i, 1)] + fConst653 * fRec137[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j314 = 0; j314 < 4; j314 = faust_wrap_add(j314, 1)) {
				fRec136_tmp[j314] = fRec136_perm[j314];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec136[i] = fZec46[i] - fConst657 * (fConst658 * fRec136[faust_wrap_sub(i, 2)] + fConst661 * fRec136[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j315 = 0; j315 < 4; j315 = faust_wrap_add(j315, 1)) {
				fRec136_perm[j315] = fRec136_tmp[faust_wrap_add(vsize, j315)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j316 = 0; j316 < 4; j316 = faust_wrap_add(j316, 1)) {
				fRec135_tmp[j316] = fRec135_perm[j316];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec135[i] = fConst657 * (fConst663 * fRec136[i] + fConst664 * fRec136[faust_wrap_sub(i, 1)] + fConst663 * fRec136[faust_wrap_sub(i, 2)]) - fConst665 * (fConst666 * fRec135[faust_wrap_sub(i, 2)] + fConst667 * fRec135[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j317 = 0; j317 < 4; j317 = faust_wrap_add(j317, 1)) {
				fRec135_perm[j317] = fRec135_tmp[faust_wrap_add(vsize, j317)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j318 = 0; j318 < 4; j318 = faust_wrap_add(j318, 1)) {
				fRec134_tmp[j318] = fRec134_perm[j318];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec134[i] = fConst665 * (fConst669 * fRec135[i] + fConst670 * fRec135[faust_wrap_sub(i, 1)] + fConst669 * fRec135[faust_wrap_sub(i, 2)]) - fConst671 * (fConst672 * fRec134[faust_wrap_sub(i, 2)] + fConst673 * fRec134[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j319 = 0; j319 < 4; j319 = faust_wrap_add(j319, 1)) {
				fRec134_perm[j319] = fRec134_tmp[faust_wrap_add(vsize, j319)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j320 = 0; j320 < 4; j320 = faust_wrap_add(j320, 1)) {
				fRec133_tmp[j320] = fRec133_perm[j320];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec133[i] = fSlow38 * fRec133[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst671 * (fConst675 * fRec134[i] + fConst676 * fRec134[faust_wrap_sub(i, 1)] + fConst675 * fRec134[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j321 = 0; j321 < 4; j321 = faust_wrap_add(j321, 1)) {
				fRec133_perm[j321] = fRec133_tmp[faust_wrap_add(vsize, j321)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j322 = 0; j322 < 4; j322 = faust_wrap_add(j322, 1)) {
				fRec146_tmp[j322] = fRec146_perm[j322];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec146[i] = fZec46[i] - fConst677 * (fConst678 * fRec146[faust_wrap_sub(i, 2)] + fConst679 * fRec146[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j323 = 0; j323 < 4; j323 = faust_wrap_add(j323, 1)) {
				fRec146_perm[j323] = fRec146_tmp[faust_wrap_add(vsize, j323)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j324 = 0; j324 < 4; j324 = faust_wrap_add(j324, 1)) {
				fRec145_tmp[j324] = fRec145_perm[j324];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec145[i] = fConst677 * (fConst681 * fRec146[i] + fConst682 * fRec146[faust_wrap_sub(i, 1)] + fConst681 * fRec146[faust_wrap_sub(i, 2)]) - fConst683 * (fConst684 * fRec145[faust_wrap_sub(i, 2)] + fConst685 * fRec145[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j325 = 0; j325 < 4; j325 = faust_wrap_add(j325, 1)) {
				fRec145_perm[j325] = fRec145_tmp[faust_wrap_add(vsize, j325)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j326 = 0; j326 < 4; j326 = faust_wrap_add(j326, 1)) {
				fRec144_tmp[j326] = fRec144_perm[j326];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec144[i] = fConst683 * (fConst686 * fRec145[i] + fConst687 * fRec145[faust_wrap_sub(i, 1)] + fConst686 * fRec145[faust_wrap_sub(i, 2)]) - fConst688 * (fConst689 * fRec144[faust_wrap_sub(i, 2)] + fConst690 * fRec144[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j327 = 0; j327 < 4; j327 = faust_wrap_add(j327, 1)) {
				fRec144_perm[j327] = fRec144_tmp[faust_wrap_add(vsize, j327)];
			}
			/* Vectorizable loop 163 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec47[i] = fConst688 * (fConst691 * fRec144[i] + fConst692 * fRec144[faust_wrap_sub(i, 1)] + fConst691 * fRec144[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j328 = 0; j328 < 4; j328 = faust_wrap_add(j328, 1)) {
				fRec143_tmp[j328] = fRec143_perm[j328];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec143[i] = fZec47[i] - fConst695 * (fConst696 * fRec143[faust_wrap_sub(i, 2)] + fConst699 * fRec143[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j329 = 0; j329 < 4; j329 = faust_wrap_add(j329, 1)) {
				fRec143_perm[j329] = fRec143_tmp[faust_wrap_add(vsize, j329)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j330 = 0; j330 < 4; j330 = faust_wrap_add(j330, 1)) {
				fRec142_tmp[j330] = fRec142_perm[j330];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec142[i] = fConst695 * (fConst701 * fRec143[i] + fConst702 * fRec143[faust_wrap_sub(i, 1)] + fConst701 * fRec143[faust_wrap_sub(i, 2)]) - fConst703 * (fConst704 * fRec142[faust_wrap_sub(i, 2)] + fConst705 * fRec142[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j331 = 0; j331 < 4; j331 = faust_wrap_add(j331, 1)) {
				fRec142_perm[j331] = fRec142_tmp[faust_wrap_add(vsize, j331)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j332 = 0; j332 < 4; j332 = faust_wrap_add(j332, 1)) {
				fRec141_tmp[j332] = fRec141_perm[j332];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec141[i] = fConst703 * (fConst707 * fRec142[i] + fConst708 * fRec142[faust_wrap_sub(i, 1)] + fConst707 * fRec142[faust_wrap_sub(i, 2)]) - fConst709 * (fConst710 * fRec141[faust_wrap_sub(i, 2)] + fConst711 * fRec141[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j333 = 0; j333 < 4; j333 = faust_wrap_add(j333, 1)) {
				fRec141_perm[j333] = fRec141_tmp[faust_wrap_add(vsize, j333)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j334 = 0; j334 < 4; j334 = faust_wrap_add(j334, 1)) {
				fRec140_tmp[j334] = fRec140_perm[j334];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec140[i] = fSlow38 * fRec140[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst709 * (fConst713 * fRec141[i] + fConst714 * fRec141[faust_wrap_sub(i, 1)] + fConst713 * fRec141[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j335 = 0; j335 < 4; j335 = faust_wrap_add(j335, 1)) {
				fRec140_perm[j335] = fRec140_tmp[faust_wrap_add(vsize, j335)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j336 = 0; j336 < 4; j336 = faust_wrap_add(j336, 1)) {
				fRec150_tmp[j336] = fRec150_perm[j336];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec150[i] = fZec47[i] - fConst715 * (fConst716 * fRec150[faust_wrap_sub(i, 2)] + fConst717 * fRec150[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j337 = 0; j337 < 4; j337 = faust_wrap_add(j337, 1)) {
				fRec150_perm[j337] = fRec150_tmp[faust_wrap_add(vsize, j337)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j338 = 0; j338 < 4; j338 = faust_wrap_add(j338, 1)) {
				fRec149_tmp[j338] = fRec149_perm[j338];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec149[i] = fConst715 * (fConst719 * fRec150[i] + fConst720 * fRec150[faust_wrap_sub(i, 1)] + fConst719 * fRec150[faust_wrap_sub(i, 2)]) - fConst721 * (fConst722 * fRec149[faust_wrap_sub(i, 2)] + fConst723 * fRec149[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j339 = 0; j339 < 4; j339 = faust_wrap_add(j339, 1)) {
				fRec149_perm[j339] = fRec149_tmp[faust_wrap_add(vsize, j339)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j340 = 0; j340 < 4; j340 = faust_wrap_add(j340, 1)) {
				fRec148_tmp[j340] = fRec148_perm[j340];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec148[i] = fConst721 * (fConst724 * fRec149[i] + fConst725 * fRec149[faust_wrap_sub(i, 1)] + fConst724 * fRec149[faust_wrap_sub(i, 2)]) - fConst726 * (fConst727 * fRec148[faust_wrap_sub(i, 2)] + fConst728 * fRec148[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j341 = 0; j341 < 4; j341 = faust_wrap_add(j341, 1)) {
				fRec148_perm[j341] = fRec148_tmp[faust_wrap_add(vsize, j341)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j342 = 0; j342 < 4; j342 = faust_wrap_add(j342, 1)) {
				fRec147_tmp[j342] = fRec147_perm[j342];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec147[i] = fSlow38 * fRec147[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst726 * (fConst729 * fRec148[i] + fConst730 * fRec148[faust_wrap_sub(i, 1)] + fConst729 * fRec148[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j343 = 0; j343 < 4; j343 = faust_wrap_add(j343, 1)) {
				fRec147_perm[j343] = fRec147_tmp[faust_wrap_add(vsize, j343)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec20_tmp[j76] = fRec20_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fZec29[i] - fConst10 * (fConst11 * fRec20[faust_wrap_sub(i, 2)] + fConst14 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec20_perm[j77] = fRec20_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec19_tmp[j78] = fRec19_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst10 * (fConst16 * fRec20[i] + fConst17 * fRec20[faust_wrap_sub(i, 1)] + fConst16 * fRec20[faust_wrap_sub(i, 2)]) - fConst18 * (fConst19 * fRec19[faust_wrap_sub(i, 2)] + fConst20 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec19_perm[j79] = fRec19_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec18_tmp[j80] = fRec18_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fConst18 * (fConst22 * fRec19[i] + fConst23 * fRec19[faust_wrap_sub(i, 1)] + fConst22 * fRec19[faust_wrap_sub(i, 2)]) - fConst24 * (fConst25 * fRec18[faust_wrap_sub(i, 2)] + fConst26 * fRec18[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec18_perm[j81] = fRec18_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec17_tmp[j82] = fRec17_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fRec17[faust_wrap_sub(i, 1)] * fSlow38 + std::fabs(fConst24 * (fConst29 * fRec18[i] + fConst30 * fRec18[faust_wrap_sub(i, 1)] + fConst29 * fRec18[faust_wrap_sub(i, 2)])) * fSlow39;
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec17_perm[j83] = fRec17_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec24_tmp[j90] = fRec24_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec30[i] - fConst49 * (fConst50 * fRec24[faust_wrap_sub(i, 2)] + fConst53 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec24_perm[j91] = fRec24_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec23_tmp[j92] = fRec23_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst49 * (fConst55 * fRec24[i] + fConst56 * fRec24[faust_wrap_sub(i, 1)] + fConst55 * fRec24[faust_wrap_sub(i, 2)]) - fConst57 * (fConst58 * fRec23[faust_wrap_sub(i, 2)] + fConst59 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec23_perm[j93] = fRec23_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec22_tmp[j94] = fRec22_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst57 * (fConst61 * fRec23[i] + fConst62 * fRec23[faust_wrap_sub(i, 1)] + fConst61 * fRec23[faust_wrap_sub(i, 2)]) - fConst63 * (fConst64 * fRec22[faust_wrap_sub(i, 2)] + fConst65 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec22_perm[j95] = fRec22_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec21_tmp[j96] = fRec21_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fSlow38 * fRec21[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst63 * (fConst67 * fRec22[i] + fConst68 * fRec22[faust_wrap_sub(i, 1)] + fConst67 * fRec22[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec21_perm[j97] = fRec21_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec31_tmp[j104] = fRec31_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec31[i] - fConst87 * (fConst88 * fRec31[faust_wrap_sub(i, 2)] + fConst91 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec31_perm[j105] = fRec31_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec30_tmp[j106] = fRec30_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst87 * (fConst93 * fRec31[i] + fConst94 * fRec31[faust_wrap_sub(i, 1)] + fConst93 * fRec31[faust_wrap_sub(i, 2)]) - fConst95 * (fConst96 * fRec30[faust_wrap_sub(i, 2)] + fConst97 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec30_perm[j107] = fRec30_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec29_tmp[j108] = fRec29_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst95 * (fConst99 * fRec30[i] + fConst100 * fRec30[faust_wrap_sub(i, 1)] + fConst99 * fRec30[faust_wrap_sub(i, 2)]) - fConst101 * (fConst102 * fRec29[faust_wrap_sub(i, 2)] + fConst103 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec29_perm[j109] = fRec29_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec28_tmp[j110] = fRec28_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fSlow38 * fRec28[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst101 * (fConst105 * fRec29[i] + fConst106 * fRec29[faust_wrap_sub(i, 1)] + fConst105 * fRec29[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec28_perm[j111] = fRec28_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Recursive loop 184 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec38_tmp[j118] = fRec38_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec32[i] - fConst125 * (fConst126 * fRec38[faust_wrap_sub(i, 2)] + fConst129 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec38_perm[j119] = fRec38_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec37_tmp[j120] = fRec37_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst125 * (fConst131 * fRec38[i] + fConst132 * fRec38[faust_wrap_sub(i, 1)] + fConst131 * fRec38[faust_wrap_sub(i, 2)]) - fConst133 * (fConst134 * fRec37[faust_wrap_sub(i, 2)] + fConst135 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec37_perm[j121] = fRec37_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec36_tmp[j122] = fRec36_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst133 * (fConst137 * fRec37[i] + fConst138 * fRec37[faust_wrap_sub(i, 1)] + fConst137 * fRec37[faust_wrap_sub(i, 2)]) - fConst139 * (fConst140 * fRec36[faust_wrap_sub(i, 2)] + fConst141 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec36_perm[j123] = fRec36_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec35_tmp[j124] = fRec35_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fSlow38 * fRec35[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst139 * (fConst143 * fRec36[i] + fConst144 * fRec36[faust_wrap_sub(i, 1)] + fConst143 * fRec36[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec35_perm[j125] = fRec35_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec45_tmp[j132] = fRec45_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec33[i] - fConst163 * (fConst164 * fRec45[faust_wrap_sub(i, 2)] + fConst167 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec45_perm[j133] = fRec45_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec44_tmp[j134] = fRec44_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst163 * (fConst169 * fRec45[i] + fConst170 * fRec45[faust_wrap_sub(i, 1)] + fConst169 * fRec45[faust_wrap_sub(i, 2)]) - fConst171 * (fConst172 * fRec44[faust_wrap_sub(i, 2)] + fConst173 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec44_perm[j135] = fRec44_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 190 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec43_tmp[j136] = fRec43_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst171 * (fConst175 * fRec44[i] + fConst176 * fRec44[faust_wrap_sub(i, 1)] + fConst175 * fRec44[faust_wrap_sub(i, 2)]) - fConst177 * (fConst178 * fRec43[faust_wrap_sub(i, 2)] + fConst179 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec43_perm[j137] = fRec43_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec42_tmp[j138] = fRec42_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fSlow38 * fRec42[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst177 * (fConst181 * fRec43[i] + fConst182 * fRec43[faust_wrap_sub(i, 1)] + fConst181 * fRec43[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec42_perm[j139] = fRec42_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Recursive loop 192 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec52_tmp[j146] = fRec52_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec34[i] - fConst201 * (fConst202 * fRec52[faust_wrap_sub(i, 2)] + fConst205 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec52_perm[j147] = fRec52_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec51_tmp[j148] = fRec51_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst201 * (fConst207 * fRec52[i] + fConst208 * fRec52[faust_wrap_sub(i, 1)] + fConst207 * fRec52[faust_wrap_sub(i, 2)]) - fConst209 * (fConst210 * fRec51[faust_wrap_sub(i, 2)] + fConst211 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec51_perm[j149] = fRec51_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec50_tmp[j150] = fRec50_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst209 * (fConst213 * fRec51[i] + fConst214 * fRec51[faust_wrap_sub(i, 1)] + fConst213 * fRec51[faust_wrap_sub(i, 2)]) - fConst215 * (fConst216 * fRec50[faust_wrap_sub(i, 2)] + fConst217 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec50_perm[j151] = fRec50_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec49_tmp[j152] = fRec49_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fSlow38 * fRec49[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst215 * (fConst219 * fRec50[i] + fConst220 * fRec50[faust_wrap_sub(i, 1)] + fConst219 * fRec50[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec49_perm[j153] = fRec49_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec59_tmp[j160] = fRec59_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec35[i] - fConst239 * (fConst240 * fRec59[faust_wrap_sub(i, 2)] + fConst243 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec59_perm[j161] = fRec59_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec58_tmp[j162] = fRec58_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst239 * (fConst245 * fRec59[i] + fConst246 * fRec59[faust_wrap_sub(i, 1)] + fConst245 * fRec59[faust_wrap_sub(i, 2)]) - fConst247 * (fConst248 * fRec58[faust_wrap_sub(i, 2)] + fConst249 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec58_perm[j163] = fRec58_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 198 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec57_tmp[j164] = fRec57_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst247 * (fConst251 * fRec58[i] + fConst252 * fRec58[faust_wrap_sub(i, 1)] + fConst251 * fRec58[faust_wrap_sub(i, 2)]) - fConst253 * (fConst254 * fRec57[faust_wrap_sub(i, 2)] + fConst255 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec57_perm[j165] = fRec57_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec56_tmp[j166] = fRec56_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fSlow38 * fRec56[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst253 * (fConst257 * fRec57[i] + fConst258 * fRec57[faust_wrap_sub(i, 1)] + fConst257 * fRec57[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec56_perm[j167] = fRec56_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Recursive loop 200 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec66_tmp[j174] = fRec66_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec36[i] - fConst277 * (fConst278 * fRec66[faust_wrap_sub(i, 2)] + fConst281 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec66_perm[j175] = fRec66_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec65_tmp[j176] = fRec65_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst277 * (fConst283 * fRec66[i] + fConst284 * fRec66[faust_wrap_sub(i, 1)] + fConst283 * fRec66[faust_wrap_sub(i, 2)]) - fConst285 * (fConst286 * fRec65[faust_wrap_sub(i, 2)] + fConst287 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec65_perm[j177] = fRec65_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec64_tmp[j178] = fRec64_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst285 * (fConst289 * fRec65[i] + fConst290 * fRec65[faust_wrap_sub(i, 1)] + fConst289 * fRec65[faust_wrap_sub(i, 2)]) - fConst291 * (fConst292 * fRec64[faust_wrap_sub(i, 2)] + fConst293 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec64_perm[j179] = fRec64_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec63_tmp[j180] = fRec63_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fSlow38 * fRec63[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst291 * (fConst295 * fRec64[i] + fConst296 * fRec64[faust_wrap_sub(i, 1)] + fConst295 * fRec64[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec63_perm[j181] = fRec63_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec73_tmp[j188] = fRec73_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec37[i] - fConst315 * (fConst316 * fRec73[faust_wrap_sub(i, 2)] + fConst319 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec73_perm[j189] = fRec73_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec72_tmp[j190] = fRec72_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst315 * (fConst321 * fRec73[i] + fConst322 * fRec73[faust_wrap_sub(i, 1)] + fConst321 * fRec73[faust_wrap_sub(i, 2)]) - fConst323 * (fConst324 * fRec72[faust_wrap_sub(i, 2)] + fConst325 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec72_perm[j191] = fRec72_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec71_tmp[j192] = fRec71_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst323 * (fConst327 * fRec72[i] + fConst328 * fRec72[faust_wrap_sub(i, 1)] + fConst327 * fRec72[faust_wrap_sub(i, 2)]) - fConst329 * (fConst330 * fRec71[faust_wrap_sub(i, 2)] + fConst331 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec71_perm[j193] = fRec71_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 207 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec70_tmp[j194] = fRec70_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fSlow38 * fRec70[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst329 * (fConst333 * fRec71[i] + fConst334 * fRec71[faust_wrap_sub(i, 1)] + fConst333 * fRec71[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec70_perm[j195] = fRec70_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Recursive loop 208 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec80_tmp[j202] = fRec80_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec38[i] - fConst353 * (fConst354 * fRec80[faust_wrap_sub(i, 2)] + fConst357 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec80_perm[j203] = fRec80_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 209 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec79_tmp[j204] = fRec79_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst353 * (fConst359 * fRec80[i] + fConst360 * fRec80[faust_wrap_sub(i, 1)] + fConst359 * fRec80[faust_wrap_sub(i, 2)]) - fConst361 * (fConst362 * fRec79[faust_wrap_sub(i, 2)] + fConst363 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec79_perm[j205] = fRec79_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 210 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec78_tmp[j206] = fRec78_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst361 * (fConst365 * fRec79[i] + fConst366 * fRec79[faust_wrap_sub(i, 1)] + fConst365 * fRec79[faust_wrap_sub(i, 2)]) - fConst367 * (fConst368 * fRec78[faust_wrap_sub(i, 2)] + fConst369 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec78_perm[j207] = fRec78_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 211 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec77_tmp[j208] = fRec77_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fSlow38 * fRec77[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst367 * (fConst371 * fRec78[i] + fConst372 * fRec78[faust_wrap_sub(i, 1)] + fConst371 * fRec78[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec77_perm[j209] = fRec77_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Recursive loop 212 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec87_tmp[j216] = fRec87_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec39[i] - fConst391 * (fConst392 * fRec87[faust_wrap_sub(i, 2)] + fConst395 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec87_perm[j217] = fRec87_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 213 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec86_tmp[j218] = fRec86_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst391 * (fConst397 * fRec87[i] + fConst398 * fRec87[faust_wrap_sub(i, 1)] + fConst397 * fRec87[faust_wrap_sub(i, 2)]) - fConst399 * (fConst400 * fRec86[faust_wrap_sub(i, 2)] + fConst401 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec86_perm[j219] = fRec86_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 214 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec85_tmp[j220] = fRec85_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst399 * (fConst403 * fRec86[i] + fConst404 * fRec86[faust_wrap_sub(i, 1)] + fConst403 * fRec86[faust_wrap_sub(i, 2)]) - fConst405 * (fConst406 * fRec85[faust_wrap_sub(i, 2)] + fConst407 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec85_perm[j221] = fRec85_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 215 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec84_tmp[j222] = fRec84_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fSlow38 * fRec84[faust_wrap_sub(i, 1)] + fSlow39 * std::fabs(fConst405 * (fConst409 * fRec85[i] + fConst410 * fRec85[faust_wrap_sub(i, 1)] + fConst409 * fRec85[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec84_perm[j223] = fRec84_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Vectorizable loop 216 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec17[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec21[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec28[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec35[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec42[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec49[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec56[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec63[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec70[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec77[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec84[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec91[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec98[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec105[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec112[i]));
				fVbargraph15 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec119[i]));
				fVbargraph16 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec126[i]));
				fVbargraph17 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec133[i]));
				fVbargraph18 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec140[i]));
				fVbargraph19 = static_cast<FAUSTFLOAT>(fSlow40 + 2e+01 * std::log10(fRec147[i]));
				fZec48[i] = fZec29[i];
			}
			/* Vectorizable loop 217 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec48[i]);
			}
			/* Vectorizable loop 218 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec48[i]);
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
