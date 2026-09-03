/* ------------------------------------------------------------
name: "spectral_level"
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
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fRec3_perm[4];
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fRec2_perm[4];
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fRec1_perm[4];
	FAUSTFLOAT fHslider0;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fRec0_perm[4];
	double fConst24;
	double fConst25;
	double fConst26;
	double fRec10_perm[4];
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec9_perm[4];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec8_perm[4];
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fRec7_perm[4];
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec6_perm[4];
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec5_perm[4];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec4_perm[4];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec17_perm[4];
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fRec16_perm[4];
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fRec15_perm[4];
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fRec14_perm[4];
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fRec13_perm[4];
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fRec12_perm[4];
	double fConst97;
	double fConst98;
	double fConst99;
	double fRec11_perm[4];
	double fConst100;
	double fConst101;
	double fConst102;
	double fRec24_perm[4];
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fRec23_perm[4];
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fRec22_perm[4];
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fRec21_perm[4];
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fRec20_perm[4];
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst133;
	double fConst134;
	double fRec19_perm[4];
	double fConst135;
	double fConst136;
	double fConst137;
	double fRec18_perm[4];
	double fConst138;
	double fConst139;
	double fConst140;
	double fRec31_perm[4];
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fConst145;
	double fConst146;
	double fRec30_perm[4];
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fRec29_perm[4];
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fRec28_perm[4];
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fRec27_perm[4];
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fRec26_perm[4];
	double fConst173;
	double fConst174;
	double fConst175;
	double fRec25_perm[4];
	double fConst176;
	double fConst177;
	double fConst178;
	double fRec38_perm[4];
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fRec37_perm[4];
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fRec36_perm[4];
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fConst197;
	double fConst198;
	double fRec35_perm[4];
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fRec34_perm[4];
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fRec33_perm[4];
	double fConst211;
	double fConst212;
	double fConst213;
	double fRec32_perm[4];
	double fConst214;
	double fConst215;
	double fConst216;
	double fRec45_perm[4];
	double fConst217;
	double fConst218;
	double fConst219;
	double fConst220;
	double fConst221;
	double fConst222;
	double fRec44_perm[4];
	double fConst223;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fRec43_perm[4];
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fRec42_perm[4];
	double fConst237;
	double fConst238;
	double fConst239;
	double fConst240;
	double fConst241;
	double fConst242;
	double fRec41_perm[4];
	double fConst243;
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fRec40_perm[4];
	double fConst249;
	double fConst250;
	double fConst251;
	double fRec39_perm[4];
	double fConst252;
	double fConst253;
	double fConst254;
	double fRec52_perm[4];
	double fConst255;
	double fConst256;
	double fConst257;
	double fConst258;
	double fConst259;
	double fConst260;
	double fRec51_perm[4];
	double fConst261;
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fRec50_perm[4];
	double fConst266;
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fConst273;
	double fConst274;
	double fRec49_perm[4];
	double fConst275;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst279;
	double fConst280;
	double fRec48_perm[4];
	double fConst281;
	double fConst282;
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fRec47_perm[4];
	double fConst287;
	double fConst288;
	double fConst289;
	double fRec46_perm[4];
	double fConst290;
	double fConst291;
	double fConst292;
	double fRec59_perm[4];
	double fConst293;
	double fConst294;
	double fConst295;
	double fConst296;
	double fConst297;
	double fConst298;
	double fRec58_perm[4];
	double fConst299;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fRec57_perm[4];
	double fConst304;
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst308;
	double fConst309;
	double fConst310;
	double fConst311;
	double fConst312;
	double fRec56_perm[4];
	double fConst313;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fRec55_perm[4];
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fRec54_perm[4];
	double fConst325;
	double fConst326;
	double fConst327;
	double fRec53_perm[4];
	double fConst328;
	double fConst329;
	double fConst330;
	double fRec66_perm[4];
	double fConst331;
	double fConst332;
	double fConst333;
	double fConst334;
	double fConst335;
	double fConst336;
	double fRec65_perm[4];
	double fConst337;
	double fConst338;
	double fConst339;
	double fConst340;
	double fConst341;
	double fRec64_perm[4];
	double fConst342;
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fRec63_perm[4];
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fRec62_perm[4];
	double fConst357;
	double fConst358;
	double fConst359;
	double fConst360;
	double fConst361;
	double fConst362;
	double fRec61_perm[4];
	double fConst363;
	double fConst364;
	double fConst365;
	double fRec60_perm[4];
	double fConst366;
	double fConst367;
	double fConst368;
	double fRec73_perm[4];
	double fConst369;
	double fConst370;
	double fConst371;
	double fConst372;
	double fConst373;
	double fConst374;
	double fRec72_perm[4];
	double fConst375;
	double fConst376;
	double fConst377;
	double fConst378;
	double fConst379;
	double fRec71_perm[4];
	double fConst380;
	double fConst381;
	double fConst382;
	double fConst383;
	double fConst384;
	double fConst385;
	double fConst386;
	double fConst387;
	double fConst388;
	double fRec70_perm[4];
	double fConst389;
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fRec69_perm[4];
	double fConst395;
	double fConst396;
	double fConst397;
	double fConst398;
	double fConst399;
	double fConst400;
	double fRec68_perm[4];
	double fConst401;
	double fConst402;
	double fConst403;
	double fRec67_perm[4];
	double fConst404;
	double fConst405;
	double fConst406;
	double fRec80_perm[4];
	double fConst407;
	double fConst408;
	double fConst409;
	double fConst410;
	double fConst411;
	double fConst412;
	double fRec79_perm[4];
	double fConst413;
	double fConst414;
	double fConst415;
	double fConst416;
	double fConst417;
	double fRec78_perm[4];
	double fConst418;
	double fConst419;
	double fConst420;
	double fConst421;
	double fConst422;
	double fConst423;
	double fConst424;
	double fConst425;
	double fConst426;
	double fRec77_perm[4];
	double fConst427;
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fRec76_perm[4];
	double fConst433;
	double fConst434;
	double fConst435;
	double fConst436;
	double fConst437;
	double fConst438;
	double fRec75_perm[4];
	double fConst439;
	double fConst440;
	double fConst441;
	double fRec74_perm[4];
	double fConst442;
	double fConst443;
	double fConst444;
	double fRec87_perm[4];
	double fConst445;
	double fConst446;
	double fConst447;
	double fConst448;
	double fConst449;
	double fConst450;
	double fRec86_perm[4];
	double fConst451;
	double fConst452;
	double fConst453;
	double fConst454;
	double fConst455;
	double fRec85_perm[4];
	double fConst456;
	double fConst457;
	double fConst458;
	double fConst459;
	double fConst460;
	double fConst461;
	double fConst462;
	double fConst463;
	double fConst464;
	double fRec84_perm[4];
	double fConst465;
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fConst470;
	double fRec83_perm[4];
	double fConst471;
	double fConst472;
	double fConst473;
	double fConst474;
	double fConst475;
	double fConst476;
	double fRec82_perm[4];
	double fConst477;
	double fConst478;
	double fConst479;
	double fRec81_perm[4];
	double fConst480;
	double fConst481;
	double fConst482;
	double fRec94_perm[4];
	double fConst483;
	double fConst484;
	double fConst485;
	double fConst486;
	double fConst487;
	double fConst488;
	double fRec93_perm[4];
	double fConst489;
	double fConst490;
	double fConst491;
	double fConst492;
	double fConst493;
	double fRec92_perm[4];
	double fConst494;
	double fConst495;
	double fConst496;
	double fConst497;
	double fConst498;
	double fConst499;
	double fConst500;
	double fConst501;
	double fConst502;
	double fRec91_perm[4];
	double fConst503;
	double fConst504;
	double fConst505;
	double fConst506;
	double fConst507;
	double fConst508;
	double fRec90_perm[4];
	double fConst509;
	double fConst510;
	double fConst511;
	double fConst512;
	double fConst513;
	double fConst514;
	double fRec89_perm[4];
	double fConst515;
	double fConst516;
	double fConst517;
	double fRec88_perm[4];
	double fConst518;
	double fConst519;
	double fConst520;
	double fRec101_perm[4];
	double fConst521;
	double fConst522;
	double fConst523;
	double fConst524;
	double fConst525;
	double fConst526;
	double fRec100_perm[4];
	double fConst527;
	double fConst528;
	double fConst529;
	double fConst530;
	double fConst531;
	double fRec99_perm[4];
	double fConst532;
	double fConst533;
	double fConst534;
	double fConst535;
	double fConst536;
	double fConst537;
	double fConst538;
	double fConst539;
	double fConst540;
	double fRec98_perm[4];
	double fConst541;
	double fConst542;
	double fConst543;
	double fConst544;
	double fConst545;
	double fConst546;
	double fRec97_perm[4];
	double fConst547;
	double fConst548;
	double fConst549;
	double fConst550;
	double fConst551;
	double fConst552;
	double fRec96_perm[4];
	double fConst553;
	double fConst554;
	double fConst555;
	double fRec95_perm[4];
	double fConst556;
	double fConst557;
	double fConst558;
	double fRec108_perm[4];
	double fConst559;
	double fConst560;
	double fConst561;
	double fConst562;
	double fConst563;
	double fConst564;
	double fRec107_perm[4];
	double fConst565;
	double fConst566;
	double fConst567;
	double fConst568;
	double fConst569;
	double fRec106_perm[4];
	double fConst570;
	double fConst571;
	double fConst572;
	double fConst573;
	double fConst574;
	double fConst575;
	double fConst576;
	double fConst577;
	double fConst578;
	double fRec105_perm[4];
	double fConst579;
	double fConst580;
	double fConst581;
	double fConst582;
	double fConst583;
	double fConst584;
	double fRec104_perm[4];
	double fConst585;
	double fConst586;
	double fConst587;
	double fConst588;
	double fConst589;
	double fConst590;
	double fRec103_perm[4];
	double fConst591;
	double fConst592;
	double fConst593;
	double fRec102_perm[4];
	double fConst594;
	double fConst595;
	double fConst596;
	double fRec115_perm[4];
	double fConst597;
	double fConst598;
	double fConst599;
	double fConst600;
	double fConst601;
	double fConst602;
	double fRec114_perm[4];
	double fConst603;
	double fConst604;
	double fConst605;
	double fConst606;
	double fConst607;
	double fRec113_perm[4];
	double fConst608;
	double fConst609;
	double fConst610;
	double fConst611;
	double fConst612;
	double fConst613;
	double fConst614;
	double fConst615;
	double fConst616;
	double fRec112_perm[4];
	double fConst617;
	double fConst618;
	double fConst619;
	double fConst620;
	double fConst621;
	double fConst622;
	double fRec111_perm[4];
	double fConst623;
	double fConst624;
	double fConst625;
	double fConst626;
	double fConst627;
	double fConst628;
	double fRec110_perm[4];
	double fConst629;
	double fConst630;
	double fConst631;
	double fRec109_perm[4];
	double fConst632;
	double fConst633;
	double fConst634;
	double fRec122_perm[4];
	double fConst635;
	double fConst636;
	double fConst637;
	double fConst638;
	double fConst639;
	double fConst640;
	double fRec121_perm[4];
	double fConst641;
	double fConst642;
	double fConst643;
	double fConst644;
	double fConst645;
	double fRec120_perm[4];
	double fConst646;
	double fConst647;
	double fConst648;
	double fConst649;
	double fConst650;
	double fConst651;
	double fConst652;
	double fConst653;
	double fConst654;
	double fRec119_perm[4];
	double fConst655;
	double fConst656;
	double fConst657;
	double fConst658;
	double fConst659;
	double fConst660;
	double fRec118_perm[4];
	double fConst661;
	double fConst662;
	double fConst663;
	double fConst664;
	double fConst665;
	double fConst666;
	double fRec117_perm[4];
	double fConst667;
	double fConst668;
	double fConst669;
	double fRec116_perm[4];
	double fConst670;
	double fConst671;
	double fConst672;
	double fRec129_perm[4];
	double fConst673;
	double fConst674;
	double fConst675;
	double fConst676;
	double fConst677;
	double fConst678;
	double fRec128_perm[4];
	double fConst679;
	double fConst680;
	double fConst681;
	double fConst682;
	double fConst683;
	double fRec127_perm[4];
	double fConst684;
	double fConst685;
	double fConst686;
	double fConst687;
	double fConst688;
	double fConst689;
	double fConst690;
	double fConst691;
	double fConst692;
	double fRec126_perm[4];
	double fConst693;
	double fConst694;
	double fConst695;
	double fConst696;
	double fConst697;
	double fConst698;
	double fRec125_perm[4];
	double fConst699;
	double fConst700;
	double fConst701;
	double fConst702;
	double fConst703;
	double fConst704;
	double fRec124_perm[4];
	double fConst705;
	double fConst706;
	double fConst707;
	double fRec123_perm[4];
	double fConst708;
	double fConst709;
	double fConst710;
	double fRec136_perm[4];
	double fConst711;
	double fConst712;
	double fConst713;
	double fConst714;
	double fConst715;
	double fConst716;
	double fRec135_perm[4];
	double fConst717;
	double fConst718;
	double fConst719;
	double fConst720;
	double fConst721;
	double fRec134_perm[4];
	double fConst722;
	double fConst723;
	double fConst724;
	double fConst725;
	double fConst726;
	double fConst727;
	double fConst728;
	double fConst729;
	double fConst730;
	double fRec133_perm[4];
	double fConst731;
	double fConst732;
	double fConst733;
	double fConst734;
	double fConst735;
	double fConst736;
	double fRec132_perm[4];
	double fConst737;
	double fConst738;
	double fConst739;
	double fConst740;
	double fConst741;
	double fConst742;
	double fRec131_perm[4];
	double fConst743;
	double fConst744;
	double fConst745;
	double fRec130_perm[4];
	double fConst746;
	double fConst747;
	double fConst748;
	double fRec143_perm[4];
	double fConst749;
	double fConst750;
	double fConst751;
	double fConst752;
	double fConst753;
	double fConst754;
	double fRec142_perm[4];
	double fConst755;
	double fConst756;
	double fConst757;
	double fConst758;
	double fConst759;
	double fRec141_perm[4];
	double fConst760;
	double fConst761;
	double fConst762;
	double fConst763;
	double fConst764;
	double fConst765;
	double fConst766;
	double fConst767;
	double fConst768;
	double fRec140_perm[4];
	double fConst769;
	double fConst770;
	double fConst771;
	double fConst772;
	double fConst773;
	double fConst774;
	double fRec139_perm[4];
	double fConst775;
	double fConst776;
	double fConst777;
	double fConst778;
	double fConst779;
	double fConst780;
	double fRec138_perm[4];
	double fConst781;
	double fConst782;
	double fConst783;
	double fRec137_perm[4];
	double fConst784;
	double fConst785;
	double fConst786;
	double fRec150_perm[4];
	double fConst787;
	double fConst788;
	double fConst789;
	double fConst790;
	double fConst791;
	double fConst792;
	double fRec149_perm[4];
	double fConst793;
	double fConst794;
	double fConst795;
	double fConst796;
	double fConst797;
	double fRec148_perm[4];
	double fConst798;
	double fConst799;
	double fConst800;
	double fConst801;
	double fConst802;
	double fConst803;
	double fConst804;
	double fConst805;
	double fConst806;
	double fRec147_perm[4];
	double fConst807;
	double fConst808;
	double fConst809;
	double fConst810;
	double fConst811;
	double fConst812;
	double fRec146_perm[4];
	double fConst813;
	double fConst814;
	double fConst815;
	double fConst816;
	double fConst817;
	double fConst818;
	double fRec145_perm[4];
	double fConst819;
	double fConst820;
	double fConst821;
	double fRec144_perm[4];
	double fConst822;
	double fConst823;
	double fConst824;
	double fRec157_perm[4];
	double fConst825;
	double fConst826;
	double fConst827;
	double fConst828;
	double fConst829;
	double fConst830;
	double fRec156_perm[4];
	double fConst831;
	double fConst832;
	double fConst833;
	double fConst834;
	double fConst835;
	double fRec155_perm[4];
	double fConst836;
	double fConst837;
	double fConst838;
	double fConst839;
	double fConst840;
	double fConst841;
	double fConst842;
	double fConst843;
	double fConst844;
	double fRec154_perm[4];
	double fConst845;
	double fConst846;
	double fConst847;
	double fConst848;
	double fConst849;
	double fConst850;
	double fRec153_perm[4];
	double fConst851;
	double fConst852;
	double fConst853;
	double fConst854;
	double fConst855;
	double fConst856;
	double fRec152_perm[4];
	double fConst857;
	double fConst858;
	double fConst859;
	double fRec151_perm[4];
	double fConst860;
	double fConst861;
	double fConst862;
	double fRec164_perm[4];
	double fConst863;
	double fConst864;
	double fConst865;
	double fConst866;
	double fConst867;
	double fConst868;
	double fRec163_perm[4];
	double fConst869;
	double fConst870;
	double fConst871;
	double fConst872;
	double fConst873;
	double fRec162_perm[4];
	double fConst874;
	double fConst875;
	double fConst876;
	double fConst877;
	double fConst878;
	double fConst879;
	double fConst880;
	double fConst881;
	double fConst882;
	double fRec161_perm[4];
	double fConst883;
	double fConst884;
	double fConst885;
	double fConst886;
	double fConst887;
	double fConst888;
	double fRec160_perm[4];
	double fConst889;
	double fConst890;
	double fConst891;
	double fConst892;
	double fConst893;
	double fConst894;
	double fRec159_perm[4];
	double fConst895;
	double fConst896;
	double fConst897;
	double fRec158_perm[4];
	double fConst898;
	double fConst899;
	double fConst900;
	double fRec171_perm[4];
	double fConst901;
	double fConst902;
	double fConst903;
	double fConst904;
	double fConst905;
	double fConst906;
	double fRec170_perm[4];
	double fConst907;
	double fConst908;
	double fConst909;
	double fConst910;
	double fConst911;
	double fRec169_perm[4];
	double fConst912;
	double fConst913;
	double fConst914;
	double fConst915;
	double fConst916;
	double fConst917;
	double fConst918;
	double fConst919;
	double fConst920;
	double fRec168_perm[4];
	double fConst921;
	double fConst922;
	double fConst923;
	double fConst924;
	double fConst925;
	double fConst926;
	double fRec167_perm[4];
	double fConst927;
	double fConst928;
	double fConst929;
	double fConst930;
	double fConst931;
	double fConst932;
	double fRec166_perm[4];
	double fConst933;
	double fConst934;
	double fConst935;
	double fRec165_perm[4];
	double fConst936;
	double fConst937;
	double fConst938;
	double fRec178_perm[4];
	double fConst939;
	double fConst940;
	double fConst941;
	double fConst942;
	double fConst943;
	double fConst944;
	double fRec177_perm[4];
	double fConst945;
	double fConst946;
	double fConst947;
	double fConst948;
	double fConst949;
	double fRec176_perm[4];
	double fConst950;
	double fConst951;
	double fConst952;
	double fConst953;
	double fConst954;
	double fConst955;
	double fConst956;
	double fConst957;
	double fConst958;
	double fRec175_perm[4];
	double fConst959;
	double fConst960;
	double fConst961;
	double fConst962;
	double fConst963;
	double fConst964;
	double fRec174_perm[4];
	double fConst965;
	double fConst966;
	double fConst967;
	double fConst968;
	double fConst969;
	double fConst970;
	double fRec173_perm[4];
	double fConst971;
	double fConst972;
	double fConst973;
	double fRec172_perm[4];
	double fConst974;
	double fConst975;
	double fConst976;
	double fRec185_perm[4];
	double fConst977;
	double fConst978;
	double fConst979;
	double fConst980;
	double fConst981;
	double fConst982;
	double fRec184_perm[4];
	double fConst983;
	double fConst984;
	double fConst985;
	double fConst986;
	double fConst987;
	double fRec183_perm[4];
	double fConst988;
	double fConst989;
	double fConst990;
	double fConst991;
	double fConst992;
	double fConst993;
	double fConst994;
	double fConst995;
	double fConst996;
	double fRec182_perm[4];
	double fConst997;
	double fConst998;
	double fConst999;
	double fConst1000;
	double fConst1001;
	double fConst1002;
	double fRec181_perm[4];
	double fConst1003;
	double fConst1004;
	double fConst1005;
	double fConst1006;
	double fConst1007;
	double fConst1008;
	double fRec180_perm[4];
	double fConst1009;
	double fConst1010;
	double fConst1011;
	double fRec179_perm[4];
	double fConst1012;
	double fConst1013;
	double fConst1014;
	double fRec192_perm[4];
	double fConst1015;
	double fConst1016;
	double fConst1017;
	double fConst1018;
	double fConst1019;
	double fConst1020;
	double fRec191_perm[4];
	double fConst1021;
	double fConst1022;
	double fConst1023;
	double fConst1024;
	double fConst1025;
	double fRec190_perm[4];
	double fConst1026;
	double fConst1027;
	double fConst1028;
	double fConst1029;
	double fConst1030;
	double fConst1031;
	double fConst1032;
	double fConst1033;
	double fConst1034;
	double fRec189_perm[4];
	double fConst1035;
	double fConst1036;
	double fConst1037;
	double fConst1038;
	double fConst1039;
	double fConst1040;
	double fRec188_perm[4];
	double fConst1041;
	double fConst1042;
	double fConst1043;
	double fConst1044;
	double fConst1045;
	double fConst1046;
	double fRec187_perm[4];
	double fConst1047;
	double fConst1048;
	double fConst1049;
	double fRec186_perm[4];
	double fConst1050;
	double fConst1051;
	double fConst1052;
	double fRec199_perm[4];
	double fConst1053;
	double fConst1054;
	double fConst1055;
	double fConst1056;
	double fConst1057;
	double fConst1058;
	double fRec198_perm[4];
	double fConst1059;
	double fConst1060;
	double fConst1061;
	double fConst1062;
	double fConst1063;
	double fRec197_perm[4];
	double fConst1064;
	double fConst1065;
	double fConst1066;
	double fConst1067;
	double fConst1068;
	double fConst1069;
	double fConst1070;
	double fConst1071;
	double fConst1072;
	double fRec196_perm[4];
	double fConst1073;
	double fConst1074;
	double fConst1075;
	double fConst1076;
	double fConst1077;
	double fConst1078;
	double fRec195_perm[4];
	double fConst1079;
	double fConst1080;
	double fConst1081;
	double fConst1082;
	double fConst1083;
	double fConst1084;
	double fRec194_perm[4];
	double fConst1085;
	double fConst1086;
	double fConst1087;
	double fRec193_perm[4];
	double fConst1088;
	double fConst1089;
	double fConst1090;
	double fRec203_perm[4];
	double fConst1091;
	double fConst1092;
	double fConst1093;
	double fConst1094;
	double fConst1095;
	double fConst1096;
	double fRec202_perm[4];
	double fConst1097;
	double fConst1098;
	double fConst1099;
	double fConst1100;
	double fConst1101;
	double fRec201_perm[4];
	double fConst1102;
	double fConst1103;
	double fRec200_perm[4];
	FAUSTFLOAT fHslider1;
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
	FAUSTFLOAT fVbargraph20;
	FAUSTFLOAT fVbargraph21;
	FAUSTFLOAT fVbargraph22;
	FAUSTFLOAT fVbargraph23;
	FAUSTFLOAT fVbargraph24;
	FAUSTFLOAT fVbargraph25;
	FAUSTFLOAT fVbargraph26;
	FAUSTFLOAT fVbargraph27;
	FAUSTFLOAT fVbargraph28;
	FAUSTFLOAT fVbargraph29;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("filename", "spectral_level.dsp");
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
		m->declare("name", "spectral_level");
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
		fConst1 = std::tan(50265.48245743669 / fConst0);
		fConst2 = 1.0 / fConst1;
		fConst3 = 1.0 / ((fConst2 + 3.1897274020965583) / fConst1 + 4.076781969643807);
		fConst4 = (fConst2 + -3.1897274020965583) / fConst1 + 4.076781969643807;
		fConst5 = mydsp_faustpower2_f(fConst1);
		fConst6 = 1.0 / fConst5;
		fConst7 = 2.0 * (4.076781969643807 - fConst6);
		fConst8 = 0.0017661728399818856 / fConst5;
		fConst9 = fConst8 + 0.00040767818495825777;
		fConst10 = 2.0 * (0.00040767818495825777 - fConst8);
		fConst11 = 1.0 / ((fConst2 + 0.7431304601070396) / fConst1 + 1.450071084655647);
		fConst12 = (fConst2 + -0.7431304601070396) / fConst1 + 1.450071084655647;
		fConst13 = 2.0 * (1.450071084655647 - fConst6);
		fConst14 = 11.052052171507189 / fConst5;
		fConst15 = fConst14 + 1.450071084655647;
		fConst16 = 2.0 * (1.450071084655647 - fConst14);
		fConst17 = 1.0 / ((fConst2 + 0.157482159302087) / fConst1 + 0.9351401670315425);
		fConst18 = (fConst2 + -0.157482159302087) / fConst1 + 0.9351401670315425;
		fConst19 = 2.0 * (0.9351401670315425 - fConst6);
		fConst20 = 1e+03 / fConst0;
		fConst21 = 50.063807016150385 / fConst5;
		fConst22 = fConst21 + 0.9351401670315425;
		fConst23 = 2.0 * (0.9351401670315425 - fConst21);
		fConst24 = 1.0 / ((fConst2 + 0.782413046821645) / fConst1 + 0.24529150870616);
		fConst25 = (fConst2 + -0.782413046821645) / fConst1 + 0.24529150870616;
		fConst26 = 2.0 * (0.24529150870616 - fConst6);
		fConst27 = 9.9999997055e-05 / fConst5;
		fConst28 = fConst27 + 0.000433227200555;
		fConst29 = 2.0 * (0.000433227200555 - fConst27);
		fConst30 = 1.0 / ((fConst2 + 0.512478641889141) / fConst1 + 0.689621364484675);
		fConst31 = (fConst2 + -0.512478641889141) / fConst1 + 0.689621364484675;
		fConst32 = 2.0 * (0.689621364484675 - fConst6);
		fConst33 = fConst6 + 7.621731298870603;
		fConst34 = 2.0 * (7.621731298870603 - fConst6);
		fConst35 = 1.0 / ((fConst2 + 0.168404871113589) / fConst1 + 1.069358407707312);
		fConst36 = (fConst2 + -0.168404871113589) / fConst1 + 1.069358407707312;
		fConst37 = 2.0 * (1.069358407707312 - fConst6);
		fConst38 = fConst6 + 53.53615295455673;
		fConst39 = 2.0 * (53.53615295455673 - fConst6);
		fConst40 = std::tan(39895.73986531205 / fConst0);
		fConst41 = 1.0 / fConst40;
		fConst42 = 1.0 / ((fConst41 + 3.1897274020965583) / fConst40 + 4.076781969643807);
		fConst43 = (fConst41 + -3.1897274020965583) / fConst40 + 4.076781969643807;
		fConst44 = mydsp_faustpower2_f(fConst40);
		fConst45 = 1.0 / fConst44;
		fConst46 = 2.0 * (4.076781969643807 - fConst45);
		fConst47 = 0.0017661728399818856 / fConst44;
		fConst48 = fConst47 + 0.00040767818495825777;
		fConst49 = 2.0 * (0.00040767818495825777 - fConst47);
		fConst50 = 1.0 / ((fConst41 + 0.7431304601070396) / fConst40 + 1.450071084655647);
		fConst51 = (fConst41 + -0.7431304601070396) / fConst40 + 1.450071084655647;
		fConst52 = 2.0 * (1.450071084655647 - fConst45);
		fConst53 = 11.052052171507189 / fConst44;
		fConst54 = fConst53 + 1.450071084655647;
		fConst55 = 2.0 * (1.450071084655647 - fConst53);
		fConst56 = 1.0 / ((fConst41 + 0.157482159302087) / fConst40 + 0.9351401670315425);
		fConst57 = (fConst41 + -0.157482159302087) / fConst40 + 0.9351401670315425;
		fConst58 = 2.0 * (0.9351401670315425 - fConst45);
		fConst59 = 50.063807016150385 / fConst44;
		fConst60 = fConst59 + 0.9351401670315425;
		fConst61 = 2.0 * (0.9351401670315425 - fConst59);
		fConst62 = 1.0 / ((fConst41 + 0.782413046821645) / fConst40 + 0.24529150870616);
		fConst63 = (fConst41 + -0.782413046821645) / fConst40 + 0.24529150870616;
		fConst64 = 2.0 * (0.24529150870616 - fConst45);
		fConst65 = 9.9999997055e-05 / fConst44;
		fConst66 = fConst65 + 0.000433227200555;
		fConst67 = 2.0 * (0.000433227200555 - fConst65);
		fConst68 = 1.0 / ((fConst41 + 0.512478641889141) / fConst40 + 0.689621364484675);
		fConst69 = (fConst41 + -0.512478641889141) / fConst40 + 0.689621364484675;
		fConst70 = 2.0 * (0.689621364484675 - fConst45);
		fConst71 = fConst45 + 7.621731298870603;
		fConst72 = 2.0 * (7.621731298870603 - fConst45);
		fConst73 = 1.0 / ((fConst41 + 0.168404871113589) / fConst40 + 1.069358407707312);
		fConst74 = (fConst41 + -0.168404871113589) / fConst40 + 1.069358407707312;
		fConst75 = 2.0 * (1.069358407707312 - fConst45);
		fConst76 = fConst45 + 53.53615295455673;
		fConst77 = 2.0 * (53.53615295455673 - fConst45);
		fConst78 = std::tan(31665.269715622984 / fConst0);
		fConst79 = 1.0 / fConst78;
		fConst80 = 1.0 / ((fConst79 + 3.1897274020965583) / fConst78 + 4.076781969643807);
		fConst81 = (fConst79 + -3.1897274020965583) / fConst78 + 4.076781969643807;
		fConst82 = mydsp_faustpower2_f(fConst78);
		fConst83 = 1.0 / fConst82;
		fConst84 = 2.0 * (4.076781969643807 - fConst83);
		fConst85 = 0.0017661728399818856 / fConst82;
		fConst86 = fConst85 + 0.00040767818495825777;
		fConst87 = 2.0 * (0.00040767818495825777 - fConst85);
		fConst88 = 1.0 / ((fConst79 + 0.7431304601070396) / fConst78 + 1.450071084655647);
		fConst89 = (fConst79 + -0.7431304601070396) / fConst78 + 1.450071084655647;
		fConst90 = 2.0 * (1.450071084655647 - fConst83);
		fConst91 = 11.052052171507189 / fConst82;
		fConst92 = fConst91 + 1.450071084655647;
		fConst93 = 2.0 * (1.450071084655647 - fConst91);
		fConst94 = 1.0 / ((fConst79 + 0.157482159302087) / fConst78 + 0.9351401670315425);
		fConst95 = (fConst79 + -0.157482159302087) / fConst78 + 0.9351401670315425;
		fConst96 = 2.0 * (0.9351401670315425 - fConst83);
		fConst97 = 50.063807016150385 / fConst82;
		fConst98 = fConst97 + 0.9351401670315425;
		fConst99 = 2.0 * (0.9351401670315425 - fConst97);
		fConst100 = 1.0 / ((fConst79 + 0.782413046821645) / fConst78 + 0.24529150870616);
		fConst101 = (fConst79 + -0.782413046821645) / fConst78 + 0.24529150870616;
		fConst102 = 2.0 * (0.24529150870616 - fConst83);
		fConst103 = 9.9999997055e-05 / fConst82;
		fConst104 = fConst103 + 0.000433227200555;
		fConst105 = 2.0 * (0.000433227200555 - fConst103);
		fConst106 = 1.0 / ((fConst79 + 0.512478641889141) / fConst78 + 0.689621364484675);
		fConst107 = (fConst79 + -0.512478641889141) / fConst78 + 0.689621364484675;
		fConst108 = 2.0 * (0.689621364484675 - fConst83);
		fConst109 = fConst83 + 7.621731298870603;
		fConst110 = 2.0 * (7.621731298870603 - fConst83);
		fConst111 = 1.0 / ((fConst79 + 0.168404871113589) / fConst78 + 1.069358407707312);
		fConst112 = (fConst79 + -0.168404871113589) / fConst78 + 1.069358407707312;
		fConst113 = 2.0 * (1.069358407707312 - fConst83);
		fConst114 = fConst83 + 53.53615295455673;
		fConst115 = 2.0 * (53.53615295455673 - fConst83);
		fConst116 = std::tan(25132.741228718343 / fConst0);
		fConst117 = 1.0 / fConst116;
		fConst118 = 1.0 / ((fConst117 + 3.1897274020965583) / fConst116 + 4.076781969643807);
		fConst119 = (fConst117 + -3.1897274020965583) / fConst116 + 4.076781969643807;
		fConst120 = mydsp_faustpower2_f(fConst116);
		fConst121 = 1.0 / fConst120;
		fConst122 = 2.0 * (4.076781969643807 - fConst121);
		fConst123 = 0.0017661728399818856 / fConst120;
		fConst124 = fConst123 + 0.00040767818495825777;
		fConst125 = 2.0 * (0.00040767818495825777 - fConst123);
		fConst126 = 1.0 / ((fConst117 + 0.7431304601070396) / fConst116 + 1.450071084655647);
		fConst127 = (fConst117 + -0.7431304601070396) / fConst116 + 1.450071084655647;
		fConst128 = 2.0 * (1.450071084655647 - fConst121);
		fConst129 = 11.052052171507189 / fConst120;
		fConst130 = fConst129 + 1.450071084655647;
		fConst131 = 2.0 * (1.450071084655647 - fConst129);
		fConst132 = 1.0 / ((fConst117 + 0.157482159302087) / fConst116 + 0.9351401670315425);
		fConst133 = (fConst117 + -0.157482159302087) / fConst116 + 0.9351401670315425;
		fConst134 = 2.0 * (0.9351401670315425 - fConst121);
		fConst135 = 50.063807016150385 / fConst120;
		fConst136 = fConst135 + 0.9351401670315425;
		fConst137 = 2.0 * (0.9351401670315425 - fConst135);
		fConst138 = 1.0 / ((fConst117 + 0.782413046821645) / fConst116 + 0.24529150870616);
		fConst139 = (fConst117 + -0.782413046821645) / fConst116 + 0.24529150870616;
		fConst140 = 2.0 * (0.24529150870616 - fConst121);
		fConst141 = 9.9999997055e-05 / fConst120;
		fConst142 = fConst141 + 0.000433227200555;
		fConst143 = 2.0 * (0.000433227200555 - fConst141);
		fConst144 = 1.0 / ((fConst117 + 0.512478641889141) / fConst116 + 0.689621364484675);
		fConst145 = (fConst117 + -0.512478641889141) / fConst116 + 0.689621364484675;
		fConst146 = 2.0 * (0.689621364484675 - fConst121);
		fConst147 = fConst121 + 7.621731298870603;
		fConst148 = 2.0 * (7.621731298870603 - fConst121);
		fConst149 = 1.0 / ((fConst117 + 0.168404871113589) / fConst116 + 1.069358407707312);
		fConst150 = (fConst117 + -0.168404871113589) / fConst116 + 1.069358407707312;
		fConst151 = 2.0 * (1.069358407707312 - fConst121);
		fConst152 = fConst121 + 53.53615295455673;
		fConst153 = 2.0 * (53.53615295455673 - fConst121);
		fConst154 = std::tan(19947.869932656024 / fConst0);
		fConst155 = 1.0 / fConst154;
		fConst156 = 1.0 / ((fConst155 + 3.1897274020965583) / fConst154 + 4.076781969643807);
		fConst157 = (fConst155 + -3.1897274020965583) / fConst154 + 4.076781969643807;
		fConst158 = mydsp_faustpower2_f(fConst154);
		fConst159 = 1.0 / fConst158;
		fConst160 = 2.0 * (4.076781969643807 - fConst159);
		fConst161 = 0.0017661728399818856 / fConst158;
		fConst162 = fConst161 + 0.00040767818495825777;
		fConst163 = 2.0 * (0.00040767818495825777 - fConst161);
		fConst164 = 1.0 / ((fConst155 + 0.7431304601070396) / fConst154 + 1.450071084655647);
		fConst165 = (fConst155 + -0.7431304601070396) / fConst154 + 1.450071084655647;
		fConst166 = 2.0 * (1.450071084655647 - fConst159);
		fConst167 = 11.052052171507189 / fConst158;
		fConst168 = fConst167 + 1.450071084655647;
		fConst169 = 2.0 * (1.450071084655647 - fConst167);
		fConst170 = 1.0 / ((fConst155 + 0.157482159302087) / fConst154 + 0.9351401670315425);
		fConst171 = (fConst155 + -0.157482159302087) / fConst154 + 0.9351401670315425;
		fConst172 = 2.0 * (0.9351401670315425 - fConst159);
		fConst173 = 50.063807016150385 / fConst158;
		fConst174 = fConst173 + 0.9351401670315425;
		fConst175 = 2.0 * (0.9351401670315425 - fConst173);
		fConst176 = 1.0 / ((fConst155 + 0.782413046821645) / fConst154 + 0.24529150870616);
		fConst177 = (fConst155 + -0.782413046821645) / fConst154 + 0.24529150870616;
		fConst178 = 2.0 * (0.24529150870616 - fConst159);
		fConst179 = 9.9999997055e-05 / fConst158;
		fConst180 = fConst179 + 0.000433227200555;
		fConst181 = 2.0 * (0.000433227200555 - fConst179);
		fConst182 = 1.0 / ((fConst155 + 0.512478641889141) / fConst154 + 0.689621364484675);
		fConst183 = (fConst155 + -0.512478641889141) / fConst154 + 0.689621364484675;
		fConst184 = 2.0 * (0.689621364484675 - fConst159);
		fConst185 = fConst159 + 7.621731298870603;
		fConst186 = 2.0 * (7.621731298870603 - fConst159);
		fConst187 = 1.0 / ((fConst155 + 0.168404871113589) / fConst154 + 1.069358407707312);
		fConst188 = (fConst155 + -0.168404871113589) / fConst154 + 1.069358407707312;
		fConst189 = 2.0 * (1.069358407707312 - fConst159);
		fConst190 = fConst159 + 53.53615295455673;
		fConst191 = 2.0 * (53.53615295455673 - fConst159);
		fConst192 = std::tan(15832.634857811492 / fConst0);
		fConst193 = 1.0 / fConst192;
		fConst194 = 1.0 / ((fConst193 + 3.1897274020965583) / fConst192 + 4.076781969643807);
		fConst195 = (fConst193 + -3.1897274020965583) / fConst192 + 4.076781969643807;
		fConst196 = mydsp_faustpower2_f(fConst192);
		fConst197 = 1.0 / fConst196;
		fConst198 = 2.0 * (4.076781969643807 - fConst197);
		fConst199 = 0.0017661728399818856 / fConst196;
		fConst200 = fConst199 + 0.00040767818495825777;
		fConst201 = 2.0 * (0.00040767818495825777 - fConst199);
		fConst202 = 1.0 / ((fConst193 + 0.7431304601070396) / fConst192 + 1.450071084655647);
		fConst203 = (fConst193 + -0.7431304601070396) / fConst192 + 1.450071084655647;
		fConst204 = 2.0 * (1.450071084655647 - fConst197);
		fConst205 = 11.052052171507189 / fConst196;
		fConst206 = fConst205 + 1.450071084655647;
		fConst207 = 2.0 * (1.450071084655647 - fConst205);
		fConst208 = 1.0 / ((fConst193 + 0.157482159302087) / fConst192 + 0.9351401670315425);
		fConst209 = (fConst193 + -0.157482159302087) / fConst192 + 0.9351401670315425;
		fConst210 = 2.0 * (0.9351401670315425 - fConst197);
		fConst211 = 50.063807016150385 / fConst196;
		fConst212 = fConst211 + 0.9351401670315425;
		fConst213 = 2.0 * (0.9351401670315425 - fConst211);
		fConst214 = 1.0 / ((fConst193 + 0.782413046821645) / fConst192 + 0.24529150870616);
		fConst215 = (fConst193 + -0.782413046821645) / fConst192 + 0.24529150870616;
		fConst216 = 2.0 * (0.24529150870616 - fConst197);
		fConst217 = 9.9999997055e-05 / fConst196;
		fConst218 = fConst217 + 0.000433227200555;
		fConst219 = 2.0 * (0.000433227200555 - fConst217);
		fConst220 = 1.0 / ((fConst193 + 0.512478641889141) / fConst192 + 0.689621364484675);
		fConst221 = (fConst193 + -0.512478641889141) / fConst192 + 0.689621364484675;
		fConst222 = 2.0 * (0.689621364484675 - fConst197);
		fConst223 = fConst197 + 7.621731298870603;
		fConst224 = 2.0 * (7.621731298870603 - fConst197);
		fConst225 = 1.0 / ((fConst193 + 0.168404871113589) / fConst192 + 1.069358407707312);
		fConst226 = (fConst193 + -0.168404871113589) / fConst192 + 1.069358407707312;
		fConst227 = 2.0 * (1.069358407707312 - fConst197);
		fConst228 = fConst197 + 53.53615295455673;
		fConst229 = 2.0 * (53.53615295455673 - fConst197);
		fConst230 = std::tan(12566.370614359172 / fConst0);
		fConst231 = 1.0 / fConst230;
		fConst232 = 1.0 / ((fConst231 + 3.1897274020965583) / fConst230 + 4.076781969643807);
		fConst233 = (fConst231 + -3.1897274020965583) / fConst230 + 4.076781969643807;
		fConst234 = mydsp_faustpower2_f(fConst230);
		fConst235 = 1.0 / fConst234;
		fConst236 = 2.0 * (4.076781969643807 - fConst235);
		fConst237 = 0.0017661728399818856 / fConst234;
		fConst238 = fConst237 + 0.00040767818495825777;
		fConst239 = 2.0 * (0.00040767818495825777 - fConst237);
		fConst240 = 1.0 / ((fConst231 + 0.7431304601070396) / fConst230 + 1.450071084655647);
		fConst241 = (fConst231 + -0.7431304601070396) / fConst230 + 1.450071084655647;
		fConst242 = 2.0 * (1.450071084655647 - fConst235);
		fConst243 = 11.052052171507189 / fConst234;
		fConst244 = fConst243 + 1.450071084655647;
		fConst245 = 2.0 * (1.450071084655647 - fConst243);
		fConst246 = 1.0 / ((fConst231 + 0.157482159302087) / fConst230 + 0.9351401670315425);
		fConst247 = (fConst231 + -0.157482159302087) / fConst230 + 0.9351401670315425;
		fConst248 = 2.0 * (0.9351401670315425 - fConst235);
		fConst249 = 50.063807016150385 / fConst234;
		fConst250 = fConst249 + 0.9351401670315425;
		fConst251 = 2.0 * (0.9351401670315425 - fConst249);
		fConst252 = 1.0 / ((fConst231 + 0.782413046821645) / fConst230 + 0.24529150870616);
		fConst253 = (fConst231 + -0.782413046821645) / fConst230 + 0.24529150870616;
		fConst254 = 2.0 * (0.24529150870616 - fConst235);
		fConst255 = 9.9999997055e-05 / fConst234;
		fConst256 = fConst255 + 0.000433227200555;
		fConst257 = 2.0 * (0.000433227200555 - fConst255);
		fConst258 = 1.0 / ((fConst231 + 0.512478641889141) / fConst230 + 0.689621364484675);
		fConst259 = (fConst231 + -0.512478641889141) / fConst230 + 0.689621364484675;
		fConst260 = 2.0 * (0.689621364484675 - fConst235);
		fConst261 = fConst235 + 7.621731298870603;
		fConst262 = 2.0 * (7.621731298870603 - fConst235);
		fConst263 = 1.0 / ((fConst231 + 0.168404871113589) / fConst230 + 1.069358407707312);
		fConst264 = (fConst231 + -0.168404871113589) / fConst230 + 1.069358407707312;
		fConst265 = 2.0 * (1.069358407707312 - fConst235);
		fConst266 = fConst235 + 53.53615295455673;
		fConst267 = 2.0 * (53.53615295455673 - fConst235);
		fConst268 = std::tan(9973.93496632801 / fConst0);
		fConst269 = 1.0 / fConst268;
		fConst270 = 1.0 / ((fConst269 + 3.1897274020965583) / fConst268 + 4.076781969643807);
		fConst271 = (fConst269 + -3.1897274020965583) / fConst268 + 4.076781969643807;
		fConst272 = mydsp_faustpower2_f(fConst268);
		fConst273 = 1.0 / fConst272;
		fConst274 = 2.0 * (4.076781969643807 - fConst273);
		fConst275 = 0.0017661728399818856 / fConst272;
		fConst276 = fConst275 + 0.00040767818495825777;
		fConst277 = 2.0 * (0.00040767818495825777 - fConst275);
		fConst278 = 1.0 / ((fConst269 + 0.7431304601070396) / fConst268 + 1.450071084655647);
		fConst279 = (fConst269 + -0.7431304601070396) / fConst268 + 1.450071084655647;
		fConst280 = 2.0 * (1.450071084655647 - fConst273);
		fConst281 = 11.052052171507189 / fConst272;
		fConst282 = fConst281 + 1.450071084655647;
		fConst283 = 2.0 * (1.450071084655647 - fConst281);
		fConst284 = 1.0 / ((fConst269 + 0.157482159302087) / fConst268 + 0.9351401670315425);
		fConst285 = (fConst269 + -0.157482159302087) / fConst268 + 0.9351401670315425;
		fConst286 = 2.0 * (0.9351401670315425 - fConst273);
		fConst287 = 50.063807016150385 / fConst272;
		fConst288 = fConst287 + 0.9351401670315425;
		fConst289 = 2.0 * (0.9351401670315425 - fConst287);
		fConst290 = 1.0 / ((fConst269 + 0.782413046821645) / fConst268 + 0.24529150870616);
		fConst291 = (fConst269 + -0.782413046821645) / fConst268 + 0.24529150870616;
		fConst292 = 2.0 * (0.24529150870616 - fConst273);
		fConst293 = 9.9999997055e-05 / fConst272;
		fConst294 = fConst293 + 0.000433227200555;
		fConst295 = 2.0 * (0.000433227200555 - fConst293);
		fConst296 = 1.0 / ((fConst269 + 0.512478641889141) / fConst268 + 0.689621364484675);
		fConst297 = (fConst269 + -0.512478641889141) / fConst268 + 0.689621364484675;
		fConst298 = 2.0 * (0.689621364484675 - fConst273);
		fConst299 = fConst273 + 7.621731298870603;
		fConst300 = 2.0 * (7.621731298870603 - fConst273);
		fConst301 = 1.0 / ((fConst269 + 0.168404871113589) / fConst268 + 1.069358407707312);
		fConst302 = (fConst269 + -0.168404871113589) / fConst268 + 1.069358407707312;
		fConst303 = 2.0 * (1.069358407707312 - fConst273);
		fConst304 = fConst273 + 53.53615295455673;
		fConst305 = 2.0 * (53.53615295455673 - fConst273);
		fConst306 = std::tan(7916.317428905746 / fConst0);
		fConst307 = 1.0 / fConst306;
		fConst308 = 1.0 / ((fConst307 + 3.1897274020965583) / fConst306 + 4.076781969643807);
		fConst309 = (fConst307 + -3.1897274020965583) / fConst306 + 4.076781969643807;
		fConst310 = mydsp_faustpower2_f(fConst306);
		fConst311 = 1.0 / fConst310;
		fConst312 = 2.0 * (4.076781969643807 - fConst311);
		fConst313 = 0.0017661728399818856 / fConst310;
		fConst314 = fConst313 + 0.00040767818495825777;
		fConst315 = 2.0 * (0.00040767818495825777 - fConst313);
		fConst316 = 1.0 / ((fConst307 + 0.7431304601070396) / fConst306 + 1.450071084655647);
		fConst317 = (fConst307 + -0.7431304601070396) / fConst306 + 1.450071084655647;
		fConst318 = 2.0 * (1.450071084655647 - fConst311);
		fConst319 = 11.052052171507189 / fConst310;
		fConst320 = fConst319 + 1.450071084655647;
		fConst321 = 2.0 * (1.450071084655647 - fConst319);
		fConst322 = 1.0 / ((fConst307 + 0.157482159302087) / fConst306 + 0.9351401670315425);
		fConst323 = (fConst307 + -0.157482159302087) / fConst306 + 0.9351401670315425;
		fConst324 = 2.0 * (0.9351401670315425 - fConst311);
		fConst325 = 50.063807016150385 / fConst310;
		fConst326 = fConst325 + 0.9351401670315425;
		fConst327 = 2.0 * (0.9351401670315425 - fConst325);
		fConst328 = 1.0 / ((fConst307 + 0.782413046821645) / fConst306 + 0.24529150870616);
		fConst329 = (fConst307 + -0.782413046821645) / fConst306 + 0.24529150870616;
		fConst330 = 2.0 * (0.24529150870616 - fConst311);
		fConst331 = 9.9999997055e-05 / fConst310;
		fConst332 = fConst331 + 0.000433227200555;
		fConst333 = 2.0 * (0.000433227200555 - fConst331);
		fConst334 = 1.0 / ((fConst307 + 0.512478641889141) / fConst306 + 0.689621364484675);
		fConst335 = (fConst307 + -0.512478641889141) / fConst306 + 0.689621364484675;
		fConst336 = 2.0 * (0.689621364484675 - fConst311);
		fConst337 = fConst311 + 7.621731298870603;
		fConst338 = 2.0 * (7.621731298870603 - fConst311);
		fConst339 = 1.0 / ((fConst307 + 0.168404871113589) / fConst306 + 1.069358407707312);
		fConst340 = (fConst307 + -0.168404871113589) / fConst306 + 1.069358407707312;
		fConst341 = 2.0 * (1.069358407707312 - fConst311);
		fConst342 = fConst311 + 53.53615295455673;
		fConst343 = 2.0 * (53.53615295455673 - fConst311);
		fConst344 = std::tan(6283.185307179586 / fConst0);
		fConst345 = 1.0 / fConst344;
		fConst346 = 1.0 / ((fConst345 + 3.1897274020965583) / fConst344 + 4.076781969643807);
		fConst347 = (fConst345 + -3.1897274020965583) / fConst344 + 4.076781969643807;
		fConst348 = mydsp_faustpower2_f(fConst344);
		fConst349 = 1.0 / fConst348;
		fConst350 = 2.0 * (4.076781969643807 - fConst349);
		fConst351 = 0.0017661728399818856 / fConst348;
		fConst352 = fConst351 + 0.00040767818495825777;
		fConst353 = 2.0 * (0.00040767818495825777 - fConst351);
		fConst354 = 1.0 / ((fConst345 + 0.7431304601070396) / fConst344 + 1.450071084655647);
		fConst355 = (fConst345 + -0.7431304601070396) / fConst344 + 1.450071084655647;
		fConst356 = 2.0 * (1.450071084655647 - fConst349);
		fConst357 = 11.052052171507189 / fConst348;
		fConst358 = fConst357 + 1.450071084655647;
		fConst359 = 2.0 * (1.450071084655647 - fConst357);
		fConst360 = 1.0 / ((fConst345 + 0.157482159302087) / fConst344 + 0.9351401670315425);
		fConst361 = (fConst345 + -0.157482159302087) / fConst344 + 0.9351401670315425;
		fConst362 = 2.0 * (0.9351401670315425 - fConst349);
		fConst363 = 50.063807016150385 / fConst348;
		fConst364 = fConst363 + 0.9351401670315425;
		fConst365 = 2.0 * (0.9351401670315425 - fConst363);
		fConst366 = 1.0 / ((fConst345 + 0.782413046821645) / fConst344 + 0.24529150870616);
		fConst367 = (fConst345 + -0.782413046821645) / fConst344 + 0.24529150870616;
		fConst368 = 2.0 * (0.24529150870616 - fConst349);
		fConst369 = 9.9999997055e-05 / fConst348;
		fConst370 = fConst369 + 0.000433227200555;
		fConst371 = 2.0 * (0.000433227200555 - fConst369);
		fConst372 = 1.0 / ((fConst345 + 0.512478641889141) / fConst344 + 0.689621364484675);
		fConst373 = (fConst345 + -0.512478641889141) / fConst344 + 0.689621364484675;
		fConst374 = 2.0 * (0.689621364484675 - fConst349);
		fConst375 = fConst349 + 7.621731298870603;
		fConst376 = 2.0 * (7.621731298870603 - fConst349);
		fConst377 = 1.0 / ((fConst345 + 0.168404871113589) / fConst344 + 1.069358407707312);
		fConst378 = (fConst345 + -0.168404871113589) / fConst344 + 1.069358407707312;
		fConst379 = 2.0 * (1.069358407707312 - fConst349);
		fConst380 = fConst349 + 53.53615295455673;
		fConst381 = 2.0 * (53.53615295455673 - fConst349);
		fConst382 = std::tan(4986.967483164005 / fConst0);
		fConst383 = 1.0 / fConst382;
		fConst384 = 1.0 / ((fConst383 + 3.1897274020965583) / fConst382 + 4.076781969643807);
		fConst385 = (fConst383 + -3.1897274020965583) / fConst382 + 4.076781969643807;
		fConst386 = mydsp_faustpower2_f(fConst382);
		fConst387 = 1.0 / fConst386;
		fConst388 = 2.0 * (4.076781969643807 - fConst387);
		fConst389 = 0.0017661728399818856 / fConst386;
		fConst390 = fConst389 + 0.00040767818495825777;
		fConst391 = 2.0 * (0.00040767818495825777 - fConst389);
		fConst392 = 1.0 / ((fConst383 + 0.7431304601070396) / fConst382 + 1.450071084655647);
		fConst393 = (fConst383 + -0.7431304601070396) / fConst382 + 1.450071084655647;
		fConst394 = 2.0 * (1.450071084655647 - fConst387);
		fConst395 = 11.052052171507189 / fConst386;
		fConst396 = fConst395 + 1.450071084655647;
		fConst397 = 2.0 * (1.450071084655647 - fConst395);
		fConst398 = 1.0 / ((fConst383 + 0.157482159302087) / fConst382 + 0.9351401670315425);
		fConst399 = (fConst383 + -0.157482159302087) / fConst382 + 0.9351401670315425;
		fConst400 = 2.0 * (0.9351401670315425 - fConst387);
		fConst401 = 50.063807016150385 / fConst386;
		fConst402 = fConst401 + 0.9351401670315425;
		fConst403 = 2.0 * (0.9351401670315425 - fConst401);
		fConst404 = 1.0 / ((fConst383 + 0.782413046821645) / fConst382 + 0.24529150870616);
		fConst405 = (fConst383 + -0.782413046821645) / fConst382 + 0.24529150870616;
		fConst406 = 2.0 * (0.24529150870616 - fConst387);
		fConst407 = 9.9999997055e-05 / fConst386;
		fConst408 = fConst407 + 0.000433227200555;
		fConst409 = 2.0 * (0.000433227200555 - fConst407);
		fConst410 = 1.0 / ((fConst383 + 0.512478641889141) / fConst382 + 0.689621364484675);
		fConst411 = (fConst383 + -0.512478641889141) / fConst382 + 0.689621364484675;
		fConst412 = 2.0 * (0.689621364484675 - fConst387);
		fConst413 = fConst387 + 7.621731298870603;
		fConst414 = 2.0 * (7.621731298870603 - fConst387);
		fConst415 = 1.0 / ((fConst383 + 0.168404871113589) / fConst382 + 1.069358407707312);
		fConst416 = (fConst383 + -0.168404871113589) / fConst382 + 1.069358407707312;
		fConst417 = 2.0 * (1.069358407707312 - fConst387);
		fConst418 = fConst387 + 53.53615295455673;
		fConst419 = 2.0 * (53.53615295455673 - fConst387);
		fConst420 = std::tan(3958.158714452873 / fConst0);
		fConst421 = 1.0 / fConst420;
		fConst422 = 1.0 / ((fConst421 + 3.1897274020965583) / fConst420 + 4.076781969643807);
		fConst423 = (fConst421 + -3.1897274020965583) / fConst420 + 4.076781969643807;
		fConst424 = mydsp_faustpower2_f(fConst420);
		fConst425 = 1.0 / fConst424;
		fConst426 = 2.0 * (4.076781969643807 - fConst425);
		fConst427 = 0.0017661728399818856 / fConst424;
		fConst428 = fConst427 + 0.00040767818495825777;
		fConst429 = 2.0 * (0.00040767818495825777 - fConst427);
		fConst430 = 1.0 / ((fConst421 + 0.7431304601070396) / fConst420 + 1.450071084655647);
		fConst431 = (fConst421 + -0.7431304601070396) / fConst420 + 1.450071084655647;
		fConst432 = 2.0 * (1.450071084655647 - fConst425);
		fConst433 = 11.052052171507189 / fConst424;
		fConst434 = fConst433 + 1.450071084655647;
		fConst435 = 2.0 * (1.450071084655647 - fConst433);
		fConst436 = 1.0 / ((fConst421 + 0.157482159302087) / fConst420 + 0.9351401670315425);
		fConst437 = (fConst421 + -0.157482159302087) / fConst420 + 0.9351401670315425;
		fConst438 = 2.0 * (0.9351401670315425 - fConst425);
		fConst439 = 50.063807016150385 / fConst424;
		fConst440 = fConst439 + 0.9351401670315425;
		fConst441 = 2.0 * (0.9351401670315425 - fConst439);
		fConst442 = 1.0 / ((fConst421 + 0.782413046821645) / fConst420 + 0.24529150870616);
		fConst443 = (fConst421 + -0.782413046821645) / fConst420 + 0.24529150870616;
		fConst444 = 2.0 * (0.24529150870616 - fConst425);
		fConst445 = 9.9999997055e-05 / fConst424;
		fConst446 = fConst445 + 0.000433227200555;
		fConst447 = 2.0 * (0.000433227200555 - fConst445);
		fConst448 = 1.0 / ((fConst421 + 0.512478641889141) / fConst420 + 0.689621364484675);
		fConst449 = (fConst421 + -0.512478641889141) / fConst420 + 0.689621364484675;
		fConst450 = 2.0 * (0.689621364484675 - fConst425);
		fConst451 = fConst425 + 7.621731298870603;
		fConst452 = 2.0 * (7.621731298870603 - fConst425);
		fConst453 = 1.0 / ((fConst421 + 0.168404871113589) / fConst420 + 1.069358407707312);
		fConst454 = (fConst421 + -0.168404871113589) / fConst420 + 1.069358407707312;
		fConst455 = 2.0 * (1.069358407707312 - fConst425);
		fConst456 = fConst425 + 53.53615295455673;
		fConst457 = 2.0 * (53.53615295455673 - fConst425);
		fConst458 = std::tan(3141.592653589793 / fConst0);
		fConst459 = 1.0 / fConst458;
		fConst460 = 1.0 / ((fConst459 + 3.1897274020965583) / fConst458 + 4.076781969643807);
		fConst461 = (fConst459 + -3.1897274020965583) / fConst458 + 4.076781969643807;
		fConst462 = mydsp_faustpower2_f(fConst458);
		fConst463 = 1.0 / fConst462;
		fConst464 = 2.0 * (4.076781969643807 - fConst463);
		fConst465 = 0.0017661728399818856 / fConst462;
		fConst466 = fConst465 + 0.00040767818495825777;
		fConst467 = 2.0 * (0.00040767818495825777 - fConst465);
		fConst468 = 1.0 / ((fConst459 + 0.7431304601070396) / fConst458 + 1.450071084655647);
		fConst469 = (fConst459 + -0.7431304601070396) / fConst458 + 1.450071084655647;
		fConst470 = 2.0 * (1.450071084655647 - fConst463);
		fConst471 = 11.052052171507189 / fConst462;
		fConst472 = fConst471 + 1.450071084655647;
		fConst473 = 2.0 * (1.450071084655647 - fConst471);
		fConst474 = 1.0 / ((fConst459 + 0.157482159302087) / fConst458 + 0.9351401670315425);
		fConst475 = (fConst459 + -0.157482159302087) / fConst458 + 0.9351401670315425;
		fConst476 = 2.0 * (0.9351401670315425 - fConst463);
		fConst477 = 50.063807016150385 / fConst462;
		fConst478 = fConst477 + 0.9351401670315425;
		fConst479 = 2.0 * (0.9351401670315425 - fConst477);
		fConst480 = 1.0 / ((fConst459 + 0.782413046821645) / fConst458 + 0.24529150870616);
		fConst481 = (fConst459 + -0.782413046821645) / fConst458 + 0.24529150870616;
		fConst482 = 2.0 * (0.24529150870616 - fConst463);
		fConst483 = 9.9999997055e-05 / fConst462;
		fConst484 = fConst483 + 0.000433227200555;
		fConst485 = 2.0 * (0.000433227200555 - fConst483);
		fConst486 = 1.0 / ((fConst459 + 0.512478641889141) / fConst458 + 0.689621364484675);
		fConst487 = (fConst459 + -0.512478641889141) / fConst458 + 0.689621364484675;
		fConst488 = 2.0 * (0.689621364484675 - fConst463);
		fConst489 = fConst463 + 7.621731298870603;
		fConst490 = 2.0 * (7.621731298870603 - fConst463);
		fConst491 = 1.0 / ((fConst459 + 0.168404871113589) / fConst458 + 1.069358407707312);
		fConst492 = (fConst459 + -0.168404871113589) / fConst458 + 1.069358407707312;
		fConst493 = 2.0 * (1.069358407707312 - fConst463);
		fConst494 = fConst463 + 53.53615295455673;
		fConst495 = 2.0 * (53.53615295455673 - fConst463);
		fConst496 = std::tan(2493.483741582003 / fConst0);
		fConst497 = 1.0 / fConst496;
		fConst498 = 1.0 / ((fConst497 + 3.1897274020965583) / fConst496 + 4.076781969643807);
		fConst499 = (fConst497 + -3.1897274020965583) / fConst496 + 4.076781969643807;
		fConst500 = mydsp_faustpower2_f(fConst496);
		fConst501 = 1.0 / fConst500;
		fConst502 = 2.0 * (4.076781969643807 - fConst501);
		fConst503 = 0.0017661728399818856 / fConst500;
		fConst504 = fConst503 + 0.00040767818495825777;
		fConst505 = 2.0 * (0.00040767818495825777 - fConst503);
		fConst506 = 1.0 / ((fConst497 + 0.7431304601070396) / fConst496 + 1.450071084655647);
		fConst507 = (fConst497 + -0.7431304601070396) / fConst496 + 1.450071084655647;
		fConst508 = 2.0 * (1.450071084655647 - fConst501);
		fConst509 = 11.052052171507189 / fConst500;
		fConst510 = fConst509 + 1.450071084655647;
		fConst511 = 2.0 * (1.450071084655647 - fConst509);
		fConst512 = 1.0 / ((fConst497 + 0.157482159302087) / fConst496 + 0.9351401670315425);
		fConst513 = (fConst497 + -0.157482159302087) / fConst496 + 0.9351401670315425;
		fConst514 = 2.0 * (0.9351401670315425 - fConst501);
		fConst515 = 50.063807016150385 / fConst500;
		fConst516 = fConst515 + 0.9351401670315425;
		fConst517 = 2.0 * (0.9351401670315425 - fConst515);
		fConst518 = 1.0 / ((fConst497 + 0.782413046821645) / fConst496 + 0.24529150870616);
		fConst519 = (fConst497 + -0.782413046821645) / fConst496 + 0.24529150870616;
		fConst520 = 2.0 * (0.24529150870616 - fConst501);
		fConst521 = 9.9999997055e-05 / fConst500;
		fConst522 = fConst521 + 0.000433227200555;
		fConst523 = 2.0 * (0.000433227200555 - fConst521);
		fConst524 = 1.0 / ((fConst497 + 0.512478641889141) / fConst496 + 0.689621364484675);
		fConst525 = (fConst497 + -0.512478641889141) / fConst496 + 0.689621364484675;
		fConst526 = 2.0 * (0.689621364484675 - fConst501);
		fConst527 = fConst501 + 7.621731298870603;
		fConst528 = 2.0 * (7.621731298870603 - fConst501);
		fConst529 = 1.0 / ((fConst497 + 0.168404871113589) / fConst496 + 1.069358407707312);
		fConst530 = (fConst497 + -0.168404871113589) / fConst496 + 1.069358407707312;
		fConst531 = 2.0 * (1.069358407707312 - fConst501);
		fConst532 = fConst501 + 53.53615295455673;
		fConst533 = 2.0 * (53.53615295455673 - fConst501);
		fConst534 = std::tan(1979.079357226436 / fConst0);
		fConst535 = 1.0 / fConst534;
		fConst536 = 1.0 / ((fConst535 + 3.1897274020965583) / fConst534 + 4.076781969643807);
		fConst537 = (fConst535 + -3.1897274020965583) / fConst534 + 4.076781969643807;
		fConst538 = mydsp_faustpower2_f(fConst534);
		fConst539 = 1.0 / fConst538;
		fConst540 = 2.0 * (4.076781969643807 - fConst539);
		fConst541 = 0.0017661728399818856 / fConst538;
		fConst542 = fConst541 + 0.00040767818495825777;
		fConst543 = 2.0 * (0.00040767818495825777 - fConst541);
		fConst544 = 1.0 / ((fConst535 + 0.7431304601070396) / fConst534 + 1.450071084655647);
		fConst545 = (fConst535 + -0.7431304601070396) / fConst534 + 1.450071084655647;
		fConst546 = 2.0 * (1.450071084655647 - fConst539);
		fConst547 = 11.052052171507189 / fConst538;
		fConst548 = fConst547 + 1.450071084655647;
		fConst549 = 2.0 * (1.450071084655647 - fConst547);
		fConst550 = 1.0 / ((fConst535 + 0.157482159302087) / fConst534 + 0.9351401670315425);
		fConst551 = (fConst535 + -0.157482159302087) / fConst534 + 0.9351401670315425;
		fConst552 = 2.0 * (0.9351401670315425 - fConst539);
		fConst553 = 50.063807016150385 / fConst538;
		fConst554 = fConst553 + 0.9351401670315425;
		fConst555 = 2.0 * (0.9351401670315425 - fConst553);
		fConst556 = 1.0 / ((fConst535 + 0.782413046821645) / fConst534 + 0.24529150870616);
		fConst557 = (fConst535 + -0.782413046821645) / fConst534 + 0.24529150870616;
		fConst558 = 2.0 * (0.24529150870616 - fConst539);
		fConst559 = 9.9999997055e-05 / fConst538;
		fConst560 = fConst559 + 0.000433227200555;
		fConst561 = 2.0 * (0.000433227200555 - fConst559);
		fConst562 = 1.0 / ((fConst535 + 0.512478641889141) / fConst534 + 0.689621364484675);
		fConst563 = (fConst535 + -0.512478641889141) / fConst534 + 0.689621364484675;
		fConst564 = 2.0 * (0.689621364484675 - fConst539);
		fConst565 = fConst539 + 7.621731298870603;
		fConst566 = 2.0 * (7.621731298870603 - fConst539);
		fConst567 = 1.0 / ((fConst535 + 0.168404871113589) / fConst534 + 1.069358407707312);
		fConst568 = (fConst535 + -0.168404871113589) / fConst534 + 1.069358407707312;
		fConst569 = 2.0 * (1.069358407707312 - fConst539);
		fConst570 = fConst539 + 53.53615295455673;
		fConst571 = 2.0 * (53.53615295455673 - fConst539);
		fConst572 = std::tan(1570.7963267948965 / fConst0);
		fConst573 = 1.0 / fConst572;
		fConst574 = 1.0 / ((fConst573 + 3.1897274020965583) / fConst572 + 4.076781969643807);
		fConst575 = (fConst573 + -3.1897274020965583) / fConst572 + 4.076781969643807;
		fConst576 = mydsp_faustpower2_f(fConst572);
		fConst577 = 1.0 / fConst576;
		fConst578 = 2.0 * (4.076781969643807 - fConst577);
		fConst579 = 0.0017661728399818856 / fConst576;
		fConst580 = fConst579 + 0.00040767818495825777;
		fConst581 = 2.0 * (0.00040767818495825777 - fConst579);
		fConst582 = 1.0 / ((fConst573 + 0.7431304601070396) / fConst572 + 1.450071084655647);
		fConst583 = (fConst573 + -0.7431304601070396) / fConst572 + 1.450071084655647;
		fConst584 = 2.0 * (1.450071084655647 - fConst577);
		fConst585 = 11.052052171507189 / fConst576;
		fConst586 = fConst585 + 1.450071084655647;
		fConst587 = 2.0 * (1.450071084655647 - fConst585);
		fConst588 = 1.0 / ((fConst573 + 0.157482159302087) / fConst572 + 0.9351401670315425);
		fConst589 = (fConst573 + -0.157482159302087) / fConst572 + 0.9351401670315425;
		fConst590 = 2.0 * (0.9351401670315425 - fConst577);
		fConst591 = 50.063807016150385 / fConst576;
		fConst592 = fConst591 + 0.9351401670315425;
		fConst593 = 2.0 * (0.9351401670315425 - fConst591);
		fConst594 = 1.0 / ((fConst573 + 0.782413046821645) / fConst572 + 0.24529150870616);
		fConst595 = (fConst573 + -0.782413046821645) / fConst572 + 0.24529150870616;
		fConst596 = 2.0 * (0.24529150870616 - fConst577);
		fConst597 = 9.9999997055e-05 / fConst576;
		fConst598 = fConst597 + 0.000433227200555;
		fConst599 = 2.0 * (0.000433227200555 - fConst597);
		fConst600 = 1.0 / ((fConst573 + 0.512478641889141) / fConst572 + 0.689621364484675);
		fConst601 = (fConst573 + -0.512478641889141) / fConst572 + 0.689621364484675;
		fConst602 = 2.0 * (0.689621364484675 - fConst577);
		fConst603 = fConst577 + 7.621731298870603;
		fConst604 = 2.0 * (7.621731298870603 - fConst577);
		fConst605 = 1.0 / ((fConst573 + 0.168404871113589) / fConst572 + 1.069358407707312);
		fConst606 = (fConst573 + -0.168404871113589) / fConst572 + 1.069358407707312;
		fConst607 = 2.0 * (1.069358407707312 - fConst577);
		fConst608 = fConst577 + 53.53615295455673;
		fConst609 = 2.0 * (53.53615295455673 - fConst577);
		fConst610 = std::tan(1246.7418707910015 / fConst0);
		fConst611 = 1.0 / fConst610;
		fConst612 = 1.0 / ((fConst611 + 3.1897274020965583) / fConst610 + 4.076781969643807);
		fConst613 = (fConst611 + -3.1897274020965583) / fConst610 + 4.076781969643807;
		fConst614 = mydsp_faustpower2_f(fConst610);
		fConst615 = 1.0 / fConst614;
		fConst616 = 2.0 * (4.076781969643807 - fConst615);
		fConst617 = 0.0017661728399818856 / fConst614;
		fConst618 = fConst617 + 0.00040767818495825777;
		fConst619 = 2.0 * (0.00040767818495825777 - fConst617);
		fConst620 = 1.0 / ((fConst611 + 0.7431304601070396) / fConst610 + 1.450071084655647);
		fConst621 = (fConst611 + -0.7431304601070396) / fConst610 + 1.450071084655647;
		fConst622 = 2.0 * (1.450071084655647 - fConst615);
		fConst623 = 11.052052171507189 / fConst614;
		fConst624 = fConst623 + 1.450071084655647;
		fConst625 = 2.0 * (1.450071084655647 - fConst623);
		fConst626 = 1.0 / ((fConst611 + 0.157482159302087) / fConst610 + 0.9351401670315425);
		fConst627 = (fConst611 + -0.157482159302087) / fConst610 + 0.9351401670315425;
		fConst628 = 2.0 * (0.9351401670315425 - fConst615);
		fConst629 = 50.063807016150385 / fConst614;
		fConst630 = fConst629 + 0.9351401670315425;
		fConst631 = 2.0 * (0.9351401670315425 - fConst629);
		fConst632 = 1.0 / ((fConst611 + 0.782413046821645) / fConst610 + 0.24529150870616);
		fConst633 = (fConst611 + -0.782413046821645) / fConst610 + 0.24529150870616;
		fConst634 = 2.0 * (0.24529150870616 - fConst615);
		fConst635 = 9.9999997055e-05 / fConst614;
		fConst636 = fConst635 + 0.000433227200555;
		fConst637 = 2.0 * (0.000433227200555 - fConst635);
		fConst638 = 1.0 / ((fConst611 + 0.512478641889141) / fConst610 + 0.689621364484675);
		fConst639 = (fConst611 + -0.512478641889141) / fConst610 + 0.689621364484675;
		fConst640 = 2.0 * (0.689621364484675 - fConst615);
		fConst641 = fConst615 + 7.621731298870603;
		fConst642 = 2.0 * (7.621731298870603 - fConst615);
		fConst643 = 1.0 / ((fConst611 + 0.168404871113589) / fConst610 + 1.069358407707312);
		fConst644 = (fConst611 + -0.168404871113589) / fConst610 + 1.069358407707312;
		fConst645 = 2.0 * (1.069358407707312 - fConst615);
		fConst646 = fConst615 + 53.53615295455673;
		fConst647 = 2.0 * (53.53615295455673 - fConst615);
		fConst648 = std::tan(989.539678613218 / fConst0);
		fConst649 = 1.0 / fConst648;
		fConst650 = 1.0 / ((fConst649 + 3.1897274020965583) / fConst648 + 4.076781969643807);
		fConst651 = (fConst649 + -3.1897274020965583) / fConst648 + 4.076781969643807;
		fConst652 = mydsp_faustpower2_f(fConst648);
		fConst653 = 1.0 / fConst652;
		fConst654 = 2.0 * (4.076781969643807 - fConst653);
		fConst655 = 0.0017661728399818856 / fConst652;
		fConst656 = fConst655 + 0.00040767818495825777;
		fConst657 = 2.0 * (0.00040767818495825777 - fConst655);
		fConst658 = 1.0 / ((fConst649 + 0.7431304601070396) / fConst648 + 1.450071084655647);
		fConst659 = (fConst649 + -0.7431304601070396) / fConst648 + 1.450071084655647;
		fConst660 = 2.0 * (1.450071084655647 - fConst653);
		fConst661 = 11.052052171507189 / fConst652;
		fConst662 = fConst661 + 1.450071084655647;
		fConst663 = 2.0 * (1.450071084655647 - fConst661);
		fConst664 = 1.0 / ((fConst649 + 0.157482159302087) / fConst648 + 0.9351401670315425);
		fConst665 = (fConst649 + -0.157482159302087) / fConst648 + 0.9351401670315425;
		fConst666 = 2.0 * (0.9351401670315425 - fConst653);
		fConst667 = 50.063807016150385 / fConst652;
		fConst668 = fConst667 + 0.9351401670315425;
		fConst669 = 2.0 * (0.9351401670315425 - fConst667);
		fConst670 = 1.0 / ((fConst649 + 0.782413046821645) / fConst648 + 0.24529150870616);
		fConst671 = (fConst649 + -0.782413046821645) / fConst648 + 0.24529150870616;
		fConst672 = 2.0 * (0.24529150870616 - fConst653);
		fConst673 = 9.9999997055e-05 / fConst652;
		fConst674 = fConst673 + 0.000433227200555;
		fConst675 = 2.0 * (0.000433227200555 - fConst673);
		fConst676 = 1.0 / ((fConst649 + 0.512478641889141) / fConst648 + 0.689621364484675);
		fConst677 = (fConst649 + -0.512478641889141) / fConst648 + 0.689621364484675;
		fConst678 = 2.0 * (0.689621364484675 - fConst653);
		fConst679 = fConst653 + 7.621731298870603;
		fConst680 = 2.0 * (7.621731298870603 - fConst653);
		fConst681 = 1.0 / ((fConst649 + 0.168404871113589) / fConst648 + 1.069358407707312);
		fConst682 = (fConst649 + -0.168404871113589) / fConst648 + 1.069358407707312;
		fConst683 = 2.0 * (1.069358407707312 - fConst653);
		fConst684 = fConst653 + 53.53615295455673;
		fConst685 = 2.0 * (53.53615295455673 - fConst653);
		fConst686 = std::tan(785.3981633974482 / fConst0);
		fConst687 = 1.0 / fConst686;
		fConst688 = 1.0 / ((fConst687 + 3.1897274020965583) / fConst686 + 4.076781969643807);
		fConst689 = (fConst687 + -3.1897274020965583) / fConst686 + 4.076781969643807;
		fConst690 = mydsp_faustpower2_f(fConst686);
		fConst691 = 1.0 / fConst690;
		fConst692 = 2.0 * (4.076781969643807 - fConst691);
		fConst693 = 0.0017661728399818856 / fConst690;
		fConst694 = fConst693 + 0.00040767818495825777;
		fConst695 = 2.0 * (0.00040767818495825777 - fConst693);
		fConst696 = 1.0 / ((fConst687 + 0.7431304601070396) / fConst686 + 1.450071084655647);
		fConst697 = (fConst687 + -0.7431304601070396) / fConst686 + 1.450071084655647;
		fConst698 = 2.0 * (1.450071084655647 - fConst691);
		fConst699 = 11.052052171507189 / fConst690;
		fConst700 = fConst699 + 1.450071084655647;
		fConst701 = 2.0 * (1.450071084655647 - fConst699);
		fConst702 = 1.0 / ((fConst687 + 0.157482159302087) / fConst686 + 0.9351401670315425);
		fConst703 = (fConst687 + -0.157482159302087) / fConst686 + 0.9351401670315425;
		fConst704 = 2.0 * (0.9351401670315425 - fConst691);
		fConst705 = 50.063807016150385 / fConst690;
		fConst706 = fConst705 + 0.9351401670315425;
		fConst707 = 2.0 * (0.9351401670315425 - fConst705);
		fConst708 = 1.0 / ((fConst687 + 0.782413046821645) / fConst686 + 0.24529150870616);
		fConst709 = (fConst687 + -0.782413046821645) / fConst686 + 0.24529150870616;
		fConst710 = 2.0 * (0.24529150870616 - fConst691);
		fConst711 = 9.9999997055e-05 / fConst690;
		fConst712 = fConst711 + 0.000433227200555;
		fConst713 = 2.0 * (0.000433227200555 - fConst711);
		fConst714 = 1.0 / ((fConst687 + 0.512478641889141) / fConst686 + 0.689621364484675);
		fConst715 = (fConst687 + -0.512478641889141) / fConst686 + 0.689621364484675;
		fConst716 = 2.0 * (0.689621364484675 - fConst691);
		fConst717 = fConst691 + 7.621731298870603;
		fConst718 = 2.0 * (7.621731298870603 - fConst691);
		fConst719 = 1.0 / ((fConst687 + 0.168404871113589) / fConst686 + 1.069358407707312);
		fConst720 = (fConst687 + -0.168404871113589) / fConst686 + 1.069358407707312;
		fConst721 = 2.0 * (1.069358407707312 - fConst691);
		fConst722 = fConst691 + 53.53615295455673;
		fConst723 = 2.0 * (53.53615295455673 - fConst691);
		fConst724 = std::tan(623.3709353955007 / fConst0);
		fConst725 = 1.0 / fConst724;
		fConst726 = 1.0 / ((fConst725 + 3.1897274020965583) / fConst724 + 4.076781969643807);
		fConst727 = (fConst725 + -3.1897274020965583) / fConst724 + 4.076781969643807;
		fConst728 = mydsp_faustpower2_f(fConst724);
		fConst729 = 1.0 / fConst728;
		fConst730 = 2.0 * (4.076781969643807 - fConst729);
		fConst731 = 0.0017661728399818856 / fConst728;
		fConst732 = fConst731 + 0.00040767818495825777;
		fConst733 = 2.0 * (0.00040767818495825777 - fConst731);
		fConst734 = 1.0 / ((fConst725 + 0.7431304601070396) / fConst724 + 1.450071084655647);
		fConst735 = (fConst725 + -0.7431304601070396) / fConst724 + 1.450071084655647;
		fConst736 = 2.0 * (1.450071084655647 - fConst729);
		fConst737 = 11.052052171507189 / fConst728;
		fConst738 = fConst737 + 1.450071084655647;
		fConst739 = 2.0 * (1.450071084655647 - fConst737);
		fConst740 = 1.0 / ((fConst725 + 0.157482159302087) / fConst724 + 0.9351401670315425);
		fConst741 = (fConst725 + -0.157482159302087) / fConst724 + 0.9351401670315425;
		fConst742 = 2.0 * (0.9351401670315425 - fConst729);
		fConst743 = 50.063807016150385 / fConst728;
		fConst744 = fConst743 + 0.9351401670315425;
		fConst745 = 2.0 * (0.9351401670315425 - fConst743);
		fConst746 = 1.0 / ((fConst725 + 0.782413046821645) / fConst724 + 0.24529150870616);
		fConst747 = (fConst725 + -0.782413046821645) / fConst724 + 0.24529150870616;
		fConst748 = 2.0 * (0.24529150870616 - fConst729);
		fConst749 = 9.9999997055e-05 / fConst728;
		fConst750 = fConst749 + 0.000433227200555;
		fConst751 = 2.0 * (0.000433227200555 - fConst749);
		fConst752 = 1.0 / ((fConst725 + 0.512478641889141) / fConst724 + 0.689621364484675);
		fConst753 = (fConst725 + -0.512478641889141) / fConst724 + 0.689621364484675;
		fConst754 = 2.0 * (0.689621364484675 - fConst729);
		fConst755 = fConst729 + 7.621731298870603;
		fConst756 = 2.0 * (7.621731298870603 - fConst729);
		fConst757 = 1.0 / ((fConst725 + 0.168404871113589) / fConst724 + 1.069358407707312);
		fConst758 = (fConst725 + -0.168404871113589) / fConst724 + 1.069358407707312;
		fConst759 = 2.0 * (1.069358407707312 - fConst729);
		fConst760 = fConst729 + 53.53615295455673;
		fConst761 = 2.0 * (53.53615295455673 - fConst729);
		fConst762 = std::tan(494.769839306609 / fConst0);
		fConst763 = 1.0 / fConst762;
		fConst764 = 1.0 / ((fConst763 + 3.1897274020965583) / fConst762 + 4.076781969643807);
		fConst765 = (fConst763 + -3.1897274020965583) / fConst762 + 4.076781969643807;
		fConst766 = mydsp_faustpower2_f(fConst762);
		fConst767 = 1.0 / fConst766;
		fConst768 = 2.0 * (4.076781969643807 - fConst767);
		fConst769 = 0.0017661728399818856 / fConst766;
		fConst770 = fConst769 + 0.00040767818495825777;
		fConst771 = 2.0 * (0.00040767818495825777 - fConst769);
		fConst772 = 1.0 / ((fConst763 + 0.7431304601070396) / fConst762 + 1.450071084655647);
		fConst773 = (fConst763 + -0.7431304601070396) / fConst762 + 1.450071084655647;
		fConst774 = 2.0 * (1.450071084655647 - fConst767);
		fConst775 = 11.052052171507189 / fConst766;
		fConst776 = fConst775 + 1.450071084655647;
		fConst777 = 2.0 * (1.450071084655647 - fConst775);
		fConst778 = 1.0 / ((fConst763 + 0.157482159302087) / fConst762 + 0.9351401670315425);
		fConst779 = (fConst763 + -0.157482159302087) / fConst762 + 0.9351401670315425;
		fConst780 = 2.0 * (0.9351401670315425 - fConst767);
		fConst781 = 50.063807016150385 / fConst766;
		fConst782 = fConst781 + 0.9351401670315425;
		fConst783 = 2.0 * (0.9351401670315425 - fConst781);
		fConst784 = 1.0 / ((fConst763 + 0.782413046821645) / fConst762 + 0.24529150870616);
		fConst785 = (fConst763 + -0.782413046821645) / fConst762 + 0.24529150870616;
		fConst786 = 2.0 * (0.24529150870616 - fConst767);
		fConst787 = 9.9999997055e-05 / fConst766;
		fConst788 = fConst787 + 0.000433227200555;
		fConst789 = 2.0 * (0.000433227200555 - fConst787);
		fConst790 = 1.0 / ((fConst763 + 0.512478641889141) / fConst762 + 0.689621364484675);
		fConst791 = (fConst763 + -0.512478641889141) / fConst762 + 0.689621364484675;
		fConst792 = 2.0 * (0.689621364484675 - fConst767);
		fConst793 = fConst767 + 7.621731298870603;
		fConst794 = 2.0 * (7.621731298870603 - fConst767);
		fConst795 = 1.0 / ((fConst763 + 0.168404871113589) / fConst762 + 1.069358407707312);
		fConst796 = (fConst763 + -0.168404871113589) / fConst762 + 1.069358407707312;
		fConst797 = 2.0 * (1.069358407707312 - fConst767);
		fConst798 = fConst767 + 53.53615295455673;
		fConst799 = 2.0 * (53.53615295455673 - fConst767);
		fConst800 = std::tan(392.6990816987241 / fConst0);
		fConst801 = 1.0 / fConst800;
		fConst802 = 1.0 / ((fConst801 + 3.1897274020965583) / fConst800 + 4.076781969643807);
		fConst803 = (fConst801 + -3.1897274020965583) / fConst800 + 4.076781969643807;
		fConst804 = mydsp_faustpower2_f(fConst800);
		fConst805 = 1.0 / fConst804;
		fConst806 = 2.0 * (4.076781969643807 - fConst805);
		fConst807 = 0.0017661728399818856 / fConst804;
		fConst808 = fConst807 + 0.00040767818495825777;
		fConst809 = 2.0 * (0.00040767818495825777 - fConst807);
		fConst810 = 1.0 / ((fConst801 + 0.7431304601070396) / fConst800 + 1.450071084655647);
		fConst811 = (fConst801 + -0.7431304601070396) / fConst800 + 1.450071084655647;
		fConst812 = 2.0 * (1.450071084655647 - fConst805);
		fConst813 = 11.052052171507189 / fConst804;
		fConst814 = fConst813 + 1.450071084655647;
		fConst815 = 2.0 * (1.450071084655647 - fConst813);
		fConst816 = 1.0 / ((fConst801 + 0.157482159302087) / fConst800 + 0.9351401670315425);
		fConst817 = (fConst801 + -0.157482159302087) / fConst800 + 0.9351401670315425;
		fConst818 = 2.0 * (0.9351401670315425 - fConst805);
		fConst819 = 50.063807016150385 / fConst804;
		fConst820 = fConst819 + 0.9351401670315425;
		fConst821 = 2.0 * (0.9351401670315425 - fConst819);
		fConst822 = 1.0 / ((fConst801 + 0.782413046821645) / fConst800 + 0.24529150870616);
		fConst823 = (fConst801 + -0.782413046821645) / fConst800 + 0.24529150870616;
		fConst824 = 2.0 * (0.24529150870616 - fConst805);
		fConst825 = 9.9999997055e-05 / fConst804;
		fConst826 = fConst825 + 0.000433227200555;
		fConst827 = 2.0 * (0.000433227200555 - fConst825);
		fConst828 = 1.0 / ((fConst801 + 0.512478641889141) / fConst800 + 0.689621364484675);
		fConst829 = (fConst801 + -0.512478641889141) / fConst800 + 0.689621364484675;
		fConst830 = 2.0 * (0.689621364484675 - fConst805);
		fConst831 = fConst805 + 7.621731298870603;
		fConst832 = 2.0 * (7.621731298870603 - fConst805);
		fConst833 = 1.0 / ((fConst801 + 0.168404871113589) / fConst800 + 1.069358407707312);
		fConst834 = (fConst801 + -0.168404871113589) / fConst800 + 1.069358407707312;
		fConst835 = 2.0 * (1.069358407707312 - fConst805);
		fConst836 = fConst805 + 53.53615295455673;
		fConst837 = 2.0 * (53.53615295455673 - fConst805);
		fConst838 = std::tan(311.68546769775037 / fConst0);
		fConst839 = 1.0 / fConst838;
		fConst840 = 1.0 / ((fConst839 + 3.1897274020965583) / fConst838 + 4.076781969643807);
		fConst841 = (fConst839 + -3.1897274020965583) / fConst838 + 4.076781969643807;
		fConst842 = mydsp_faustpower2_f(fConst838);
		fConst843 = 1.0 / fConst842;
		fConst844 = 2.0 * (4.076781969643807 - fConst843);
		fConst845 = 0.0017661728399818856 / fConst842;
		fConst846 = fConst845 + 0.00040767818495825777;
		fConst847 = 2.0 * (0.00040767818495825777 - fConst845);
		fConst848 = 1.0 / ((fConst839 + 0.7431304601070396) / fConst838 + 1.450071084655647);
		fConst849 = (fConst839 + -0.7431304601070396) / fConst838 + 1.450071084655647;
		fConst850 = 2.0 * (1.450071084655647 - fConst843);
		fConst851 = 11.052052171507189 / fConst842;
		fConst852 = fConst851 + 1.450071084655647;
		fConst853 = 2.0 * (1.450071084655647 - fConst851);
		fConst854 = 1.0 / ((fConst839 + 0.157482159302087) / fConst838 + 0.9351401670315425);
		fConst855 = (fConst839 + -0.157482159302087) / fConst838 + 0.9351401670315425;
		fConst856 = 2.0 * (0.9351401670315425 - fConst843);
		fConst857 = 50.063807016150385 / fConst842;
		fConst858 = fConst857 + 0.9351401670315425;
		fConst859 = 2.0 * (0.9351401670315425 - fConst857);
		fConst860 = 1.0 / ((fConst839 + 0.782413046821645) / fConst838 + 0.24529150870616);
		fConst861 = (fConst839 + -0.782413046821645) / fConst838 + 0.24529150870616;
		fConst862 = 2.0 * (0.24529150870616 - fConst843);
		fConst863 = 9.9999997055e-05 / fConst842;
		fConst864 = fConst863 + 0.000433227200555;
		fConst865 = 2.0 * (0.000433227200555 - fConst863);
		fConst866 = 1.0 / ((fConst839 + 0.512478641889141) / fConst838 + 0.689621364484675);
		fConst867 = (fConst839 + -0.512478641889141) / fConst838 + 0.689621364484675;
		fConst868 = 2.0 * (0.689621364484675 - fConst843);
		fConst869 = fConst843 + 7.621731298870603;
		fConst870 = 2.0 * (7.621731298870603 - fConst843);
		fConst871 = 1.0 / ((fConst839 + 0.168404871113589) / fConst838 + 1.069358407707312);
		fConst872 = (fConst839 + -0.168404871113589) / fConst838 + 1.069358407707312;
		fConst873 = 2.0 * (1.069358407707312 - fConst843);
		fConst874 = fConst843 + 53.53615295455673;
		fConst875 = 2.0 * (53.53615295455673 - fConst843);
		fConst876 = std::tan(247.3849196533045 / fConst0);
		fConst877 = 1.0 / fConst876;
		fConst878 = 1.0 / ((fConst877 + 3.1897274020965583) / fConst876 + 4.076781969643807);
		fConst879 = (fConst877 + -3.1897274020965583) / fConst876 + 4.076781969643807;
		fConst880 = mydsp_faustpower2_f(fConst876);
		fConst881 = 1.0 / fConst880;
		fConst882 = 2.0 * (4.076781969643807 - fConst881);
		fConst883 = 0.0017661728399818856 / fConst880;
		fConst884 = fConst883 + 0.00040767818495825777;
		fConst885 = 2.0 * (0.00040767818495825777 - fConst883);
		fConst886 = 1.0 / ((fConst877 + 0.7431304601070396) / fConst876 + 1.450071084655647);
		fConst887 = (fConst877 + -0.7431304601070396) / fConst876 + 1.450071084655647;
		fConst888 = 2.0 * (1.450071084655647 - fConst881);
		fConst889 = 11.052052171507189 / fConst880;
		fConst890 = fConst889 + 1.450071084655647;
		fConst891 = 2.0 * (1.450071084655647 - fConst889);
		fConst892 = 1.0 / ((fConst877 + 0.157482159302087) / fConst876 + 0.9351401670315425);
		fConst893 = (fConst877 + -0.157482159302087) / fConst876 + 0.9351401670315425;
		fConst894 = 2.0 * (0.9351401670315425 - fConst881);
		fConst895 = 50.063807016150385 / fConst880;
		fConst896 = fConst895 + 0.9351401670315425;
		fConst897 = 2.0 * (0.9351401670315425 - fConst895);
		fConst898 = 1.0 / ((fConst877 + 0.782413046821645) / fConst876 + 0.24529150870616);
		fConst899 = (fConst877 + -0.782413046821645) / fConst876 + 0.24529150870616;
		fConst900 = 2.0 * (0.24529150870616 - fConst881);
		fConst901 = 9.9999997055e-05 / fConst880;
		fConst902 = fConst901 + 0.000433227200555;
		fConst903 = 2.0 * (0.000433227200555 - fConst901);
		fConst904 = 1.0 / ((fConst877 + 0.512478641889141) / fConst876 + 0.689621364484675);
		fConst905 = (fConst877 + -0.512478641889141) / fConst876 + 0.689621364484675;
		fConst906 = 2.0 * (0.689621364484675 - fConst881);
		fConst907 = fConst881 + 7.621731298870603;
		fConst908 = 2.0 * (7.621731298870603 - fConst881);
		fConst909 = 1.0 / ((fConst877 + 0.168404871113589) / fConst876 + 1.069358407707312);
		fConst910 = (fConst877 + -0.168404871113589) / fConst876 + 1.069358407707312;
		fConst911 = 2.0 * (1.069358407707312 - fConst881);
		fConst912 = fConst881 + 53.53615295455673;
		fConst913 = 2.0 * (53.53615295455673 - fConst881);
		fConst914 = std::tan(196.34954084936206 / fConst0);
		fConst915 = 1.0 / fConst914;
		fConst916 = 1.0 / ((fConst915 + 3.1897274020965583) / fConst914 + 4.076781969643807);
		fConst917 = (fConst915 + -3.1897274020965583) / fConst914 + 4.076781969643807;
		fConst918 = mydsp_faustpower2_f(fConst914);
		fConst919 = 1.0 / fConst918;
		fConst920 = 2.0 * (4.076781969643807 - fConst919);
		fConst921 = 0.0017661728399818856 / fConst918;
		fConst922 = fConst921 + 0.00040767818495825777;
		fConst923 = 2.0 * (0.00040767818495825777 - fConst921);
		fConst924 = 1.0 / ((fConst915 + 0.7431304601070396) / fConst914 + 1.450071084655647);
		fConst925 = (fConst915 + -0.7431304601070396) / fConst914 + 1.450071084655647;
		fConst926 = 2.0 * (1.450071084655647 - fConst919);
		fConst927 = 11.052052171507189 / fConst918;
		fConst928 = fConst927 + 1.450071084655647;
		fConst929 = 2.0 * (1.450071084655647 - fConst927);
		fConst930 = 1.0 / ((fConst915 + 0.157482159302087) / fConst914 + 0.9351401670315425);
		fConst931 = (fConst915 + -0.157482159302087) / fConst914 + 0.9351401670315425;
		fConst932 = 2.0 * (0.9351401670315425 - fConst919);
		fConst933 = 50.063807016150385 / fConst918;
		fConst934 = fConst933 + 0.9351401670315425;
		fConst935 = 2.0 * (0.9351401670315425 - fConst933);
		fConst936 = 1.0 / ((fConst915 + 0.782413046821645) / fConst914 + 0.24529150870616);
		fConst937 = (fConst915 + -0.782413046821645) / fConst914 + 0.24529150870616;
		fConst938 = 2.0 * (0.24529150870616 - fConst919);
		fConst939 = 9.9999997055e-05 / fConst918;
		fConst940 = fConst939 + 0.000433227200555;
		fConst941 = 2.0 * (0.000433227200555 - fConst939);
		fConst942 = 1.0 / ((fConst915 + 0.512478641889141) / fConst914 + 0.689621364484675);
		fConst943 = (fConst915 + -0.512478641889141) / fConst914 + 0.689621364484675;
		fConst944 = 2.0 * (0.689621364484675 - fConst919);
		fConst945 = fConst919 + 7.621731298870603;
		fConst946 = 2.0 * (7.621731298870603 - fConst919);
		fConst947 = 1.0 / ((fConst915 + 0.168404871113589) / fConst914 + 1.069358407707312);
		fConst948 = (fConst915 + -0.168404871113589) / fConst914 + 1.069358407707312;
		fConst949 = 2.0 * (1.069358407707312 - fConst919);
		fConst950 = fConst919 + 53.53615295455673;
		fConst951 = 2.0 * (53.53615295455673 - fConst919);
		fConst952 = std::tan(155.8427338488751 / fConst0);
		fConst953 = 1.0 / fConst952;
		fConst954 = 1.0 / ((fConst953 + 3.1897274020965583) / fConst952 + 4.076781969643807);
		fConst955 = (fConst953 + -3.1897274020965583) / fConst952 + 4.076781969643807;
		fConst956 = mydsp_faustpower2_f(fConst952);
		fConst957 = 1.0 / fConst956;
		fConst958 = 2.0 * (4.076781969643807 - fConst957);
		fConst959 = 0.0017661728399818856 / fConst956;
		fConst960 = fConst959 + 0.00040767818495825777;
		fConst961 = 2.0 * (0.00040767818495825777 - fConst959);
		fConst962 = 1.0 / ((fConst953 + 0.7431304601070396) / fConst952 + 1.450071084655647);
		fConst963 = (fConst953 + -0.7431304601070396) / fConst952 + 1.450071084655647;
		fConst964 = 2.0 * (1.450071084655647 - fConst957);
		fConst965 = 11.052052171507189 / fConst956;
		fConst966 = fConst965 + 1.450071084655647;
		fConst967 = 2.0 * (1.450071084655647 - fConst965);
		fConst968 = 1.0 / ((fConst953 + 0.157482159302087) / fConst952 + 0.9351401670315425);
		fConst969 = (fConst953 + -0.157482159302087) / fConst952 + 0.9351401670315425;
		fConst970 = 2.0 * (0.9351401670315425 - fConst957);
		fConst971 = 50.063807016150385 / fConst956;
		fConst972 = fConst971 + 0.9351401670315425;
		fConst973 = 2.0 * (0.9351401670315425 - fConst971);
		fConst974 = 1.0 / ((fConst953 + 0.782413046821645) / fConst952 + 0.24529150870616);
		fConst975 = (fConst953 + -0.782413046821645) / fConst952 + 0.24529150870616;
		fConst976 = 2.0 * (0.24529150870616 - fConst957);
		fConst977 = 9.9999997055e-05 / fConst956;
		fConst978 = fConst977 + 0.000433227200555;
		fConst979 = 2.0 * (0.000433227200555 - fConst977);
		fConst980 = 1.0 / ((fConst953 + 0.512478641889141) / fConst952 + 0.689621364484675);
		fConst981 = (fConst953 + -0.512478641889141) / fConst952 + 0.689621364484675;
		fConst982 = 2.0 * (0.689621364484675 - fConst957);
		fConst983 = fConst957 + 7.621731298870603;
		fConst984 = 2.0 * (7.621731298870603 - fConst957);
		fConst985 = 1.0 / ((fConst953 + 0.168404871113589) / fConst952 + 1.069358407707312);
		fConst986 = (fConst953 + -0.168404871113589) / fConst952 + 1.069358407707312;
		fConst987 = 2.0 * (1.069358407707312 - fConst957);
		fConst988 = fConst957 + 53.53615295455673;
		fConst989 = 2.0 * (53.53615295455673 - fConst957);
		fConst990 = std::tan(123.69245982665232 / fConst0);
		fConst991 = 1.0 / fConst990;
		fConst992 = 1.0 / ((fConst991 + 3.1897274020965583) / fConst990 + 4.076781969643807);
		fConst993 = (fConst991 + -3.1897274020965583) / fConst990 + 4.076781969643807;
		fConst994 = mydsp_faustpower2_f(fConst990);
		fConst995 = 1.0 / fConst994;
		fConst996 = 2.0 * (4.076781969643807 - fConst995);
		fConst997 = 0.0017661728399818856 / fConst994;
		fConst998 = fConst997 + 0.00040767818495825777;
		fConst999 = 2.0 * (0.00040767818495825777 - fConst997);
		fConst1000 = 1.0 / ((fConst991 + 0.7431304601070396) / fConst990 + 1.450071084655647);
		fConst1001 = (fConst991 + -0.7431304601070396) / fConst990 + 1.450071084655647;
		fConst1002 = 2.0 * (1.450071084655647 - fConst995);
		fConst1003 = 11.052052171507189 / fConst994;
		fConst1004 = fConst1003 + 1.450071084655647;
		fConst1005 = 2.0 * (1.450071084655647 - fConst1003);
		fConst1006 = 1.0 / ((fConst991 + 0.157482159302087) / fConst990 + 0.9351401670315425);
		fConst1007 = (fConst991 + -0.157482159302087) / fConst990 + 0.9351401670315425;
		fConst1008 = 2.0 * (0.9351401670315425 - fConst995);
		fConst1009 = 50.063807016150385 / fConst994;
		fConst1010 = fConst1009 + 0.9351401670315425;
		fConst1011 = 2.0 * (0.9351401670315425 - fConst1009);
		fConst1012 = 1.0 / ((fConst991 + 0.782413046821645) / fConst990 + 0.24529150870616);
		fConst1013 = (fConst991 + -0.782413046821645) / fConst990 + 0.24529150870616;
		fConst1014 = 2.0 * (0.24529150870616 - fConst995);
		fConst1015 = 9.9999997055e-05 / fConst994;
		fConst1016 = fConst1015 + 0.000433227200555;
		fConst1017 = 2.0 * (0.000433227200555 - fConst1015);
		fConst1018 = 1.0 / ((fConst991 + 0.512478641889141) / fConst990 + 0.689621364484675);
		fConst1019 = (fConst991 + -0.512478641889141) / fConst990 + 0.689621364484675;
		fConst1020 = 2.0 * (0.689621364484675 - fConst995);
		fConst1021 = fConst995 + 7.621731298870603;
		fConst1022 = 2.0 * (7.621731298870603 - fConst995);
		fConst1023 = 1.0 / ((fConst991 + 0.168404871113589) / fConst990 + 1.069358407707312);
		fConst1024 = (fConst991 + -0.168404871113589) / fConst990 + 1.069358407707312;
		fConst1025 = 2.0 * (1.069358407707312 - fConst995);
		fConst1026 = fConst995 + 53.53615295455673;
		fConst1027 = 2.0 * (53.53615295455673 - fConst995);
		fConst1028 = std::tan(98.17477042468103 / fConst0);
		fConst1029 = 1.0 / fConst1028;
		fConst1030 = 1.0 / ((fConst1029 + 3.1897274020965583) / fConst1028 + 4.076781969643807);
		fConst1031 = (fConst1029 + -3.1897274020965583) / fConst1028 + 4.076781969643807;
		fConst1032 = mydsp_faustpower2_f(fConst1028);
		fConst1033 = 1.0 / fConst1032;
		fConst1034 = 2.0 * (4.076781969643807 - fConst1033);
		fConst1035 = 0.0017661728399818856 / fConst1032;
		fConst1036 = fConst1035 + 0.00040767818495825777;
		fConst1037 = 2.0 * (0.00040767818495825777 - fConst1035);
		fConst1038 = 1.0 / ((fConst1029 + 0.7431304601070396) / fConst1028 + 1.450071084655647);
		fConst1039 = (fConst1029 + -0.7431304601070396) / fConst1028 + 1.450071084655647;
		fConst1040 = 2.0 * (1.450071084655647 - fConst1033);
		fConst1041 = 11.052052171507189 / fConst1032;
		fConst1042 = fConst1041 + 1.450071084655647;
		fConst1043 = 2.0 * (1.450071084655647 - fConst1041);
		fConst1044 = 1.0 / ((fConst1029 + 0.157482159302087) / fConst1028 + 0.9351401670315425);
		fConst1045 = (fConst1029 + -0.157482159302087) / fConst1028 + 0.9351401670315425;
		fConst1046 = 2.0 * (0.9351401670315425 - fConst1033);
		fConst1047 = 50.063807016150385 / fConst1032;
		fConst1048 = fConst1047 + 0.9351401670315425;
		fConst1049 = 2.0 * (0.9351401670315425 - fConst1047);
		fConst1050 = 1.0 / ((fConst1029 + 0.782413046821645) / fConst1028 + 0.24529150870616);
		fConst1051 = (fConst1029 + -0.782413046821645) / fConst1028 + 0.24529150870616;
		fConst1052 = 2.0 * (0.24529150870616 - fConst1033);
		fConst1053 = 9.9999997055e-05 / fConst1032;
		fConst1054 = fConst1053 + 0.000433227200555;
		fConst1055 = 2.0 * (0.000433227200555 - fConst1053);
		fConst1056 = 1.0 / ((fConst1029 + 0.512478641889141) / fConst1028 + 0.689621364484675);
		fConst1057 = (fConst1029 + -0.512478641889141) / fConst1028 + 0.689621364484675;
		fConst1058 = 2.0 * (0.689621364484675 - fConst1033);
		fConst1059 = fConst1033 + 7.621731298870603;
		fConst1060 = 2.0 * (7.621731298870603 - fConst1033);
		fConst1061 = 1.0 / ((fConst1029 + 0.168404871113589) / fConst1028 + 1.069358407707312);
		fConst1062 = (fConst1029 + -0.168404871113589) / fConst1028 + 1.069358407707312;
		fConst1063 = 2.0 * (1.069358407707312 - fConst1033);
		fConst1064 = fConst1033 + 53.53615295455673;
		fConst1065 = 2.0 * (53.53615295455673 - fConst1033);
		fConst1066 = std::tan(77.92136692443755 / fConst0);
		fConst1067 = 1.0 / fConst1066;
		fConst1068 = 1.0 / ((fConst1067 + 3.1897274020965583) / fConst1066 + 4.076781969643807);
		fConst1069 = (fConst1067 + -3.1897274020965583) / fConst1066 + 4.076781969643807;
		fConst1070 = mydsp_faustpower2_f(fConst1066);
		fConst1071 = 1.0 / fConst1070;
		fConst1072 = 2.0 * (4.076781969643807 - fConst1071);
		fConst1073 = 0.0017661728399818856 / fConst1070;
		fConst1074 = fConst1073 + 0.00040767818495825777;
		fConst1075 = 2.0 * (0.00040767818495825777 - fConst1073);
		fConst1076 = 1.0 / ((fConst1067 + 0.7431304601070396) / fConst1066 + 1.450071084655647);
		fConst1077 = (fConst1067 + -0.7431304601070396) / fConst1066 + 1.450071084655647;
		fConst1078 = 2.0 * (1.450071084655647 - fConst1071);
		fConst1079 = 11.052052171507189 / fConst1070;
		fConst1080 = fConst1079 + 1.450071084655647;
		fConst1081 = 2.0 * (1.450071084655647 - fConst1079);
		fConst1082 = 1.0 / ((fConst1067 + 0.157482159302087) / fConst1066 + 0.9351401670315425);
		fConst1083 = (fConst1067 + -0.157482159302087) / fConst1066 + 0.9351401670315425;
		fConst1084 = 2.0 * (0.9351401670315425 - fConst1071);
		fConst1085 = 50.063807016150385 / fConst1070;
		fConst1086 = fConst1085 + 0.9351401670315425;
		fConst1087 = 2.0 * (0.9351401670315425 - fConst1085);
		fConst1088 = 1.0 / ((fConst1067 + 0.782413046821645) / fConst1066 + 0.24529150870616);
		fConst1089 = (fConst1067 + -0.782413046821645) / fConst1066 + 0.24529150870616;
		fConst1090 = 2.0 * (0.24529150870616 - fConst1071);
		fConst1091 = 9.9999997055e-05 / fConst1070;
		fConst1092 = fConst1091 + 0.000433227200555;
		fConst1093 = 2.0 * (0.000433227200555 - fConst1091);
		fConst1094 = 1.0 / ((fConst1067 + 0.512478641889141) / fConst1066 + 0.689621364484675);
		fConst1095 = (fConst1067 + -0.512478641889141) / fConst1066 + 0.689621364484675;
		fConst1096 = 2.0 * (0.689621364484675 - fConst1071);
		fConst1097 = fConst1071 + 7.621731298870603;
		fConst1098 = 2.0 * (7.621731298870603 - fConst1071);
		fConst1099 = 1.0 / ((fConst1067 + 0.168404871113589) / fConst1066 + 1.069358407707312);
		fConst1100 = (fConst1067 + -0.168404871113589) / fConst1066 + 1.069358407707312;
		fConst1101 = 2.0 * (1.069358407707312 - fConst1071);
		fConst1102 = fConst1071 + 53.53615295455673;
		fConst1103 = 2.0 * (53.53615295455673 - fConst1071);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1e+02);
		fHslider1 = static_cast<FAUSTFLOAT>(5e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			fRec3_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec2_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec1_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec0_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec10_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec9_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec8_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec7_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec6_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fRec5_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec4_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec17_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec16_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec15_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec14_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec13_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fRec12_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec11_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec24_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec23_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec22_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec21_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fRec20_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec19_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec18_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec31_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fRec30_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec29_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec28_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec27_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec26_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec25_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec38_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec37_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fRec36_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec35_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec34_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec33_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec32_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec45_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec44_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fRec43_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec42_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec41_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec40_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec39_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec52_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fRec51_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec50_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec49_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec48_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec47_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec46_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec59_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec58_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec57_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec56_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec55_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec54_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fRec53_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec66_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec65_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec64_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec63_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec62_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec61_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fRec60_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec73_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec72_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec71_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec70_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec69_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fRec68_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec67_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec80_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec79_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec78_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec77_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec76_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec75_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec74_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec87_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec86_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec85_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fRec84_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec83_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec82_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec81_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec94_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec93_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec92_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fRec91_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec90_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec89_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec88_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec101_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec100_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fRec99_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec98_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec97_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec96_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec95_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec108_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec107_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec106_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec105_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec104_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec103_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = faust_wrap_add(l108, 1)) {
			fRec102_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = faust_wrap_add(l109, 1)) {
			fRec115_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = faust_wrap_add(l110, 1)) {
			fRec114_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = faust_wrap_add(l111, 1)) {
			fRec113_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = faust_wrap_add(l112, 1)) {
			fRec112_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = faust_wrap_add(l113, 1)) {
			fRec111_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = faust_wrap_add(l114, 1)) {
			fRec110_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = faust_wrap_add(l115, 1)) {
			fRec109_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = faust_wrap_add(l116, 1)) {
			fRec122_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = faust_wrap_add(l117, 1)) {
			fRec121_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = faust_wrap_add(l118, 1)) {
			fRec120_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = faust_wrap_add(l119, 1)) {
			fRec119_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = faust_wrap_add(l120, 1)) {
			fRec118_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = faust_wrap_add(l121, 1)) {
			fRec117_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = faust_wrap_add(l122, 1)) {
			fRec116_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = faust_wrap_add(l123, 1)) {
			fRec129_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = faust_wrap_add(l124, 1)) {
			fRec128_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = faust_wrap_add(l125, 1)) {
			fRec127_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = faust_wrap_add(l126, 1)) {
			fRec126_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = faust_wrap_add(l127, 1)) {
			fRec125_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = faust_wrap_add(l128, 1)) {
			fRec124_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = faust_wrap_add(l129, 1)) {
			fRec123_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = faust_wrap_add(l130, 1)) {
			fRec136_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = faust_wrap_add(l131, 1)) {
			fRec135_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = faust_wrap_add(l132, 1)) {
			fRec134_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = faust_wrap_add(l133, 1)) {
			fRec133_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = faust_wrap_add(l134, 1)) {
			fRec132_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = faust_wrap_add(l135, 1)) {
			fRec131_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = faust_wrap_add(l136, 1)) {
			fRec130_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = faust_wrap_add(l137, 1)) {
			fRec143_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = faust_wrap_add(l138, 1)) {
			fRec142_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = faust_wrap_add(l139, 1)) {
			fRec141_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = faust_wrap_add(l140, 1)) {
			fRec140_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = faust_wrap_add(l141, 1)) {
			fRec139_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 4; l142 = faust_wrap_add(l142, 1)) {
			fRec138_perm[l142] = 0.0;
		}
		for (int l143 = 0; l143 < 4; l143 = faust_wrap_add(l143, 1)) {
			fRec137_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = faust_wrap_add(l144, 1)) {
			fRec150_perm[l144] = 0.0;
		}
		for (int l145 = 0; l145 < 4; l145 = faust_wrap_add(l145, 1)) {
			fRec149_perm[l145] = 0.0;
		}
		for (int l146 = 0; l146 < 4; l146 = faust_wrap_add(l146, 1)) {
			fRec148_perm[l146] = 0.0;
		}
		for (int l147 = 0; l147 < 4; l147 = faust_wrap_add(l147, 1)) {
			fRec147_perm[l147] = 0.0;
		}
		for (int l148 = 0; l148 < 4; l148 = faust_wrap_add(l148, 1)) {
			fRec146_perm[l148] = 0.0;
		}
		for (int l149 = 0; l149 < 4; l149 = faust_wrap_add(l149, 1)) {
			fRec145_perm[l149] = 0.0;
		}
		for (int l150 = 0; l150 < 4; l150 = faust_wrap_add(l150, 1)) {
			fRec144_perm[l150] = 0.0;
		}
		for (int l151 = 0; l151 < 4; l151 = faust_wrap_add(l151, 1)) {
			fRec157_perm[l151] = 0.0;
		}
		for (int l152 = 0; l152 < 4; l152 = faust_wrap_add(l152, 1)) {
			fRec156_perm[l152] = 0.0;
		}
		for (int l153 = 0; l153 < 4; l153 = faust_wrap_add(l153, 1)) {
			fRec155_perm[l153] = 0.0;
		}
		for (int l154 = 0; l154 < 4; l154 = faust_wrap_add(l154, 1)) {
			fRec154_perm[l154] = 0.0;
		}
		for (int l155 = 0; l155 < 4; l155 = faust_wrap_add(l155, 1)) {
			fRec153_perm[l155] = 0.0;
		}
		for (int l156 = 0; l156 < 4; l156 = faust_wrap_add(l156, 1)) {
			fRec152_perm[l156] = 0.0;
		}
		for (int l157 = 0; l157 < 4; l157 = faust_wrap_add(l157, 1)) {
			fRec151_perm[l157] = 0.0;
		}
		for (int l158 = 0; l158 < 4; l158 = faust_wrap_add(l158, 1)) {
			fRec164_perm[l158] = 0.0;
		}
		for (int l159 = 0; l159 < 4; l159 = faust_wrap_add(l159, 1)) {
			fRec163_perm[l159] = 0.0;
		}
		for (int l160 = 0; l160 < 4; l160 = faust_wrap_add(l160, 1)) {
			fRec162_perm[l160] = 0.0;
		}
		for (int l161 = 0; l161 < 4; l161 = faust_wrap_add(l161, 1)) {
			fRec161_perm[l161] = 0.0;
		}
		for (int l162 = 0; l162 < 4; l162 = faust_wrap_add(l162, 1)) {
			fRec160_perm[l162] = 0.0;
		}
		for (int l163 = 0; l163 < 4; l163 = faust_wrap_add(l163, 1)) {
			fRec159_perm[l163] = 0.0;
		}
		for (int l164 = 0; l164 < 4; l164 = faust_wrap_add(l164, 1)) {
			fRec158_perm[l164] = 0.0;
		}
		for (int l165 = 0; l165 < 4; l165 = faust_wrap_add(l165, 1)) {
			fRec171_perm[l165] = 0.0;
		}
		for (int l166 = 0; l166 < 4; l166 = faust_wrap_add(l166, 1)) {
			fRec170_perm[l166] = 0.0;
		}
		for (int l167 = 0; l167 < 4; l167 = faust_wrap_add(l167, 1)) {
			fRec169_perm[l167] = 0.0;
		}
		for (int l168 = 0; l168 < 4; l168 = faust_wrap_add(l168, 1)) {
			fRec168_perm[l168] = 0.0;
		}
		for (int l169 = 0; l169 < 4; l169 = faust_wrap_add(l169, 1)) {
			fRec167_perm[l169] = 0.0;
		}
		for (int l170 = 0; l170 < 4; l170 = faust_wrap_add(l170, 1)) {
			fRec166_perm[l170] = 0.0;
		}
		for (int l171 = 0; l171 < 4; l171 = faust_wrap_add(l171, 1)) {
			fRec165_perm[l171] = 0.0;
		}
		for (int l172 = 0; l172 < 4; l172 = faust_wrap_add(l172, 1)) {
			fRec178_perm[l172] = 0.0;
		}
		for (int l173 = 0; l173 < 4; l173 = faust_wrap_add(l173, 1)) {
			fRec177_perm[l173] = 0.0;
		}
		for (int l174 = 0; l174 < 4; l174 = faust_wrap_add(l174, 1)) {
			fRec176_perm[l174] = 0.0;
		}
		for (int l175 = 0; l175 < 4; l175 = faust_wrap_add(l175, 1)) {
			fRec175_perm[l175] = 0.0;
		}
		for (int l176 = 0; l176 < 4; l176 = faust_wrap_add(l176, 1)) {
			fRec174_perm[l176] = 0.0;
		}
		for (int l177 = 0; l177 < 4; l177 = faust_wrap_add(l177, 1)) {
			fRec173_perm[l177] = 0.0;
		}
		for (int l178 = 0; l178 < 4; l178 = faust_wrap_add(l178, 1)) {
			fRec172_perm[l178] = 0.0;
		}
		for (int l179 = 0; l179 < 4; l179 = faust_wrap_add(l179, 1)) {
			fRec185_perm[l179] = 0.0;
		}
		for (int l180 = 0; l180 < 4; l180 = faust_wrap_add(l180, 1)) {
			fRec184_perm[l180] = 0.0;
		}
		for (int l181 = 0; l181 < 4; l181 = faust_wrap_add(l181, 1)) {
			fRec183_perm[l181] = 0.0;
		}
		for (int l182 = 0; l182 < 4; l182 = faust_wrap_add(l182, 1)) {
			fRec182_perm[l182] = 0.0;
		}
		for (int l183 = 0; l183 < 4; l183 = faust_wrap_add(l183, 1)) {
			fRec181_perm[l183] = 0.0;
		}
		for (int l184 = 0; l184 < 4; l184 = faust_wrap_add(l184, 1)) {
			fRec180_perm[l184] = 0.0;
		}
		for (int l185 = 0; l185 < 4; l185 = faust_wrap_add(l185, 1)) {
			fRec179_perm[l185] = 0.0;
		}
		for (int l186 = 0; l186 < 4; l186 = faust_wrap_add(l186, 1)) {
			fRec192_perm[l186] = 0.0;
		}
		for (int l187 = 0; l187 < 4; l187 = faust_wrap_add(l187, 1)) {
			fRec191_perm[l187] = 0.0;
		}
		for (int l188 = 0; l188 < 4; l188 = faust_wrap_add(l188, 1)) {
			fRec190_perm[l188] = 0.0;
		}
		for (int l189 = 0; l189 < 4; l189 = faust_wrap_add(l189, 1)) {
			fRec189_perm[l189] = 0.0;
		}
		for (int l190 = 0; l190 < 4; l190 = faust_wrap_add(l190, 1)) {
			fRec188_perm[l190] = 0.0;
		}
		for (int l191 = 0; l191 < 4; l191 = faust_wrap_add(l191, 1)) {
			fRec187_perm[l191] = 0.0;
		}
		for (int l192 = 0; l192 < 4; l192 = faust_wrap_add(l192, 1)) {
			fRec186_perm[l192] = 0.0;
		}
		for (int l193 = 0; l193 < 4; l193 = faust_wrap_add(l193, 1)) {
			fRec199_perm[l193] = 0.0;
		}
		for (int l194 = 0; l194 < 4; l194 = faust_wrap_add(l194, 1)) {
			fRec198_perm[l194] = 0.0;
		}
		for (int l195 = 0; l195 < 4; l195 = faust_wrap_add(l195, 1)) {
			fRec197_perm[l195] = 0.0;
		}
		for (int l196 = 0; l196 < 4; l196 = faust_wrap_add(l196, 1)) {
			fRec196_perm[l196] = 0.0;
		}
		for (int l197 = 0; l197 < 4; l197 = faust_wrap_add(l197, 1)) {
			fRec195_perm[l197] = 0.0;
		}
		for (int l198 = 0; l198 < 4; l198 = faust_wrap_add(l198, 1)) {
			fRec194_perm[l198] = 0.0;
		}
		for (int l199 = 0; l199 < 4; l199 = faust_wrap_add(l199, 1)) {
			fRec193_perm[l199] = 0.0;
		}
		for (int l200 = 0; l200 < 4; l200 = faust_wrap_add(l200, 1)) {
			fRec203_perm[l200] = 0.0;
		}
		for (int l201 = 0; l201 < 4; l201 = faust_wrap_add(l201, 1)) {
			fRec202_perm[l201] = 0.0;
		}
		for (int l202 = 0; l202 < 4; l202 = faust_wrap_add(l202, 1)) {
			fRec201_perm[l202] = 0.0;
		}
		for (int l203 = 0; l203 < 4; l203 = faust_wrap_add(l203, 1)) {
			fRec200_perm[l203] = 0.0;
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
		ui_interface->openVerticalBox("spectral_level");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 30 bands spanning LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph29, "0", "");
		ui_interface->declare(&fVbargraph29, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph29, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph29, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph28, "1", "");
		ui_interface->declare(&fVbargraph28, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph28, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph28, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph27, "2", "");
		ui_interface->declare(&fVbargraph27, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph27, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph27, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph26, "3", "");
		ui_interface->declare(&fVbargraph26, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph26, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph26, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph25, "4", "");
		ui_interface->declare(&fVbargraph25, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph25, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph25, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph24, "5", "");
		ui_interface->declare(&fVbargraph24, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph24, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph24, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph23, "6", "");
		ui_interface->declare(&fVbargraph23, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph23, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph23, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph22, "7", "");
		ui_interface->declare(&fVbargraph22, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph22, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph22, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph21, "8", "");
		ui_interface->declare(&fVbargraph21, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph21, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph8", &fVbargraph21, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph20, "9", "");
		ui_interface->declare(&fVbargraph20, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph20, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph9", &fVbargraph20, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph19, "10", "");
		ui_interface->declare(&fVbargraph19, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph19, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph10", &fVbargraph19, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph18, "11", "");
		ui_interface->declare(&fVbargraph18, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph18, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph11", &fVbargraph18, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph17, "12", "");
		ui_interface->declare(&fVbargraph17, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph17, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph12", &fVbargraph17, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph16, "13", "");
		ui_interface->declare(&fVbargraph16, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph16, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph13", &fVbargraph16, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph15, "14", "");
		ui_interface->declare(&fVbargraph15, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph15, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph14", &fVbargraph15, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph14, "15", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph15", &fVbargraph14, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph13, "16", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph16", &fVbargraph13, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph12, "17", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph17", &fVbargraph12, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph11, "18", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph18", &fVbargraph11, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph10, "19", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph19", &fVbargraph10, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph9, "20", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph20", &fVbargraph9, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph8, "21", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph21", &fVbargraph8, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph7, "22", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph22", &fVbargraph7, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph6, "23", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph23", &fVbargraph6, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph5, "24", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph24", &fVbargraph5, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph4, "25", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph25", &fVbargraph4, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph3, "26", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph26", &fVbargraph3, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph2, "27", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph27", &fVbargraph2, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph1, "28", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph28", &fVbargraph1, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->declare(&fVbargraph0, "29", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph29", &fVbargraph0, FAUSTFLOAT(-5e+01), FAUSTFLOAT(1e+01));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider0, "0", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider0, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider0, FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider1, FAUSTFLOAT(5e+01), FAUSTFLOAT(0.0), FAUSTFLOAT(1e+02), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fSlow0 = static_cast<double>(fHslider0);
		double fSlow1 = (((0.001 * fSlow0) > 0.0) ? std::exp(-(fConst20 / fSlow0)) : 0.0);
		double fSlow2 = 1.0 - fSlow1;
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		double fZec0[4];
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		double fRec17_tmp[8];
		double* fRec17 = &fRec17_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fZec1[4];
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
		double fZec2[4];
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
		double fZec3[4];
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
		double fZec4[4];
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
		double fZec5[4];
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
		double fZec6[4];
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
		double fZec7[4];
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
		double fZec8[4];
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
		double fZec9[4];
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
		double fZec10[4];
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
		double fZec11[4];
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
		double fZec12[4];
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
		double fZec13[4];
		double fRec98_tmp[8];
		double* fRec98 = &fRec98_tmp[4];
		double fRec97_tmp[8];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[8];
		double* fRec96 = &fRec96_tmp[4];
		double fRec95_tmp[8];
		double* fRec95 = &fRec95_tmp[4];
		double fRec108_tmp[8];
		double* fRec108 = &fRec108_tmp[4];
		double fRec107_tmp[8];
		double* fRec107 = &fRec107_tmp[4];
		double fRec106_tmp[8];
		double* fRec106 = &fRec106_tmp[4];
		double fZec14[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[8];
		double* fRec104 = &fRec104_tmp[4];
		double fRec103_tmp[8];
		double* fRec103 = &fRec103_tmp[4];
		double fRec102_tmp[8];
		double* fRec102 = &fRec102_tmp[4];
		double fRec115_tmp[8];
		double* fRec115 = &fRec115_tmp[4];
		double fRec114_tmp[8];
		double* fRec114 = &fRec114_tmp[4];
		double fRec113_tmp[8];
		double* fRec113 = &fRec113_tmp[4];
		double fZec15[4];
		double fRec112_tmp[8];
		double* fRec112 = &fRec112_tmp[4];
		double fRec111_tmp[8];
		double* fRec111 = &fRec111_tmp[4];
		double fRec110_tmp[8];
		double* fRec110 = &fRec110_tmp[4];
		double fRec109_tmp[8];
		double* fRec109 = &fRec109_tmp[4];
		double fRec122_tmp[8];
		double* fRec122 = &fRec122_tmp[4];
		double fRec121_tmp[8];
		double* fRec121 = &fRec121_tmp[4];
		double fRec120_tmp[8];
		double* fRec120 = &fRec120_tmp[4];
		double fZec16[4];
		double fRec119_tmp[8];
		double* fRec119 = &fRec119_tmp[4];
		double fRec118_tmp[8];
		double* fRec118 = &fRec118_tmp[4];
		double fRec117_tmp[8];
		double* fRec117 = &fRec117_tmp[4];
		double fRec116_tmp[8];
		double* fRec116 = &fRec116_tmp[4];
		double fRec129_tmp[8];
		double* fRec129 = &fRec129_tmp[4];
		double fRec128_tmp[8];
		double* fRec128 = &fRec128_tmp[4];
		double fRec127_tmp[8];
		double* fRec127 = &fRec127_tmp[4];
		double fZec17[4];
		double fRec126_tmp[8];
		double* fRec126 = &fRec126_tmp[4];
		double fRec125_tmp[8];
		double* fRec125 = &fRec125_tmp[4];
		double fRec124_tmp[8];
		double* fRec124 = &fRec124_tmp[4];
		double fRec123_tmp[8];
		double* fRec123 = &fRec123_tmp[4];
		double fRec136_tmp[8];
		double* fRec136 = &fRec136_tmp[4];
		double fRec135_tmp[8];
		double* fRec135 = &fRec135_tmp[4];
		double fRec134_tmp[8];
		double* fRec134 = &fRec134_tmp[4];
		double fZec18[4];
		double fRec133_tmp[8];
		double* fRec133 = &fRec133_tmp[4];
		double fRec132_tmp[8];
		double* fRec132 = &fRec132_tmp[4];
		double fRec131_tmp[8];
		double* fRec131 = &fRec131_tmp[4];
		double fRec130_tmp[8];
		double* fRec130 = &fRec130_tmp[4];
		double fRec143_tmp[8];
		double* fRec143 = &fRec143_tmp[4];
		double fRec142_tmp[8];
		double* fRec142 = &fRec142_tmp[4];
		double fRec141_tmp[8];
		double* fRec141 = &fRec141_tmp[4];
		double fZec19[4];
		double fRec140_tmp[8];
		double* fRec140 = &fRec140_tmp[4];
		double fRec139_tmp[8];
		double* fRec139 = &fRec139_tmp[4];
		double fRec138_tmp[8];
		double* fRec138 = &fRec138_tmp[4];
		double fRec137_tmp[8];
		double* fRec137 = &fRec137_tmp[4];
		double fRec150_tmp[8];
		double* fRec150 = &fRec150_tmp[4];
		double fRec149_tmp[8];
		double* fRec149 = &fRec149_tmp[4];
		double fRec148_tmp[8];
		double* fRec148 = &fRec148_tmp[4];
		double fZec20[4];
		double fRec147_tmp[8];
		double* fRec147 = &fRec147_tmp[4];
		double fRec146_tmp[8];
		double* fRec146 = &fRec146_tmp[4];
		double fRec145_tmp[8];
		double* fRec145 = &fRec145_tmp[4];
		double fRec144_tmp[8];
		double* fRec144 = &fRec144_tmp[4];
		double fRec157_tmp[8];
		double* fRec157 = &fRec157_tmp[4];
		double fRec156_tmp[8];
		double* fRec156 = &fRec156_tmp[4];
		double fRec155_tmp[8];
		double* fRec155 = &fRec155_tmp[4];
		double fZec21[4];
		double fRec154_tmp[8];
		double* fRec154 = &fRec154_tmp[4];
		double fRec153_tmp[8];
		double* fRec153 = &fRec153_tmp[4];
		double fRec152_tmp[8];
		double* fRec152 = &fRec152_tmp[4];
		double fRec151_tmp[8];
		double* fRec151 = &fRec151_tmp[4];
		double fRec164_tmp[8];
		double* fRec164 = &fRec164_tmp[4];
		double fRec163_tmp[8];
		double* fRec163 = &fRec163_tmp[4];
		double fRec162_tmp[8];
		double* fRec162 = &fRec162_tmp[4];
		double fZec22[4];
		double fRec161_tmp[8];
		double* fRec161 = &fRec161_tmp[4];
		double fRec160_tmp[8];
		double* fRec160 = &fRec160_tmp[4];
		double fRec159_tmp[8];
		double* fRec159 = &fRec159_tmp[4];
		double fRec158_tmp[8];
		double* fRec158 = &fRec158_tmp[4];
		double fRec171_tmp[8];
		double* fRec171 = &fRec171_tmp[4];
		double fRec170_tmp[8];
		double* fRec170 = &fRec170_tmp[4];
		double fRec169_tmp[8];
		double* fRec169 = &fRec169_tmp[4];
		double fZec23[4];
		double fRec168_tmp[8];
		double* fRec168 = &fRec168_tmp[4];
		double fRec167_tmp[8];
		double* fRec167 = &fRec167_tmp[4];
		double fRec166_tmp[8];
		double* fRec166 = &fRec166_tmp[4];
		double fRec165_tmp[8];
		double* fRec165 = &fRec165_tmp[4];
		double fRec178_tmp[8];
		double* fRec178 = &fRec178_tmp[4];
		double fRec177_tmp[8];
		double* fRec177 = &fRec177_tmp[4];
		double fRec176_tmp[8];
		double* fRec176 = &fRec176_tmp[4];
		double fZec24[4];
		double fRec175_tmp[8];
		double* fRec175 = &fRec175_tmp[4];
		double fRec174_tmp[8];
		double* fRec174 = &fRec174_tmp[4];
		double fRec173_tmp[8];
		double* fRec173 = &fRec173_tmp[4];
		double fRec172_tmp[8];
		double* fRec172 = &fRec172_tmp[4];
		double fRec185_tmp[8];
		double* fRec185 = &fRec185_tmp[4];
		double fRec184_tmp[8];
		double* fRec184 = &fRec184_tmp[4];
		double fRec183_tmp[8];
		double* fRec183 = &fRec183_tmp[4];
		double fZec25[4];
		double fRec182_tmp[8];
		double* fRec182 = &fRec182_tmp[4];
		double fRec181_tmp[8];
		double* fRec181 = &fRec181_tmp[4];
		double fRec180_tmp[8];
		double* fRec180 = &fRec180_tmp[4];
		double fRec179_tmp[8];
		double* fRec179 = &fRec179_tmp[4];
		double fRec192_tmp[8];
		double* fRec192 = &fRec192_tmp[4];
		double fRec191_tmp[8];
		double* fRec191 = &fRec191_tmp[4];
		double fRec190_tmp[8];
		double* fRec190 = &fRec190_tmp[4];
		double fZec26[4];
		double fRec189_tmp[8];
		double* fRec189 = &fRec189_tmp[4];
		double fRec188_tmp[8];
		double* fRec188 = &fRec188_tmp[4];
		double fRec187_tmp[8];
		double* fRec187 = &fRec187_tmp[4];
		double fRec186_tmp[8];
		double* fRec186 = &fRec186_tmp[4];
		double fRec199_tmp[8];
		double* fRec199 = &fRec199_tmp[4];
		double fRec198_tmp[8];
		double* fRec198 = &fRec198_tmp[4];
		double fRec197_tmp[8];
		double* fRec197 = &fRec197_tmp[4];
		double fZec27[4];
		double fRec196_tmp[8];
		double* fRec196 = &fRec196_tmp[4];
		double fRec195_tmp[8];
		double* fRec195 = &fRec195_tmp[4];
		double fRec194_tmp[8];
		double* fRec194 = &fRec194_tmp[4];
		double fRec193_tmp[8];
		double* fRec193 = &fRec193_tmp[4];
		double fRec203_tmp[8];
		double* fRec203 = &fRec203_tmp[4];
		double fRec202_tmp[8];
		double* fRec202 = &fRec202_tmp[4];
		double fRec201_tmp[8];
		double* fRec201 = &fRec201_tmp[4];
		double fRec200_tmp[8];
		double* fRec200 = &fRec200_tmp[4];
		double fSlow3 = static_cast<double>(fHslider1);
		double fZec28[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec10_tmp[j8] = fRec10_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = static_cast<double>(input0[i]) - fConst24 * (fConst25 * fRec10[faust_wrap_sub(i, 2)] + fConst26 * fRec10[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec10_perm[j9] = fRec10_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec9_tmp[j10] = fRec9_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fConst24 * (fConst28 * fRec10[i] + fConst29 * fRec10[faust_wrap_sub(i, 1)] + fConst28 * fRec10[faust_wrap_sub(i, 2)]) - fConst30 * (fConst31 * fRec9[faust_wrap_sub(i, 2)] + fConst32 * fRec9[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec9_perm[j11] = fRec9_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec8_tmp[j12] = fRec8_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = fConst30 * (fConst33 * fRec9[i] + fConst34 * fRec9[faust_wrap_sub(i, 1)] + fConst33 * fRec9[faust_wrap_sub(i, 2)]) - fConst35 * (fConst36 * fRec8[faust_wrap_sub(i, 2)] + fConst37 * fRec8[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec8_perm[j13] = fRec8_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst35 * (fConst38 * fRec8[i] + fConst39 * fRec8[faust_wrap_sub(i, 1)] + fConst38 * fRec8[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fZec0[i] - fConst42 * (fConst43 * fRec7[faust_wrap_sub(i, 2)] + fConst46 * fRec7[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec6_tmp[j16] = fRec6_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fConst42 * (fConst48 * fRec7[i] + fConst49 * fRec7[faust_wrap_sub(i, 1)] + fConst48 * fRec7[faust_wrap_sub(i, 2)]) - fConst50 * (fConst51 * fRec6[faust_wrap_sub(i, 2)] + fConst52 * fRec6[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec6_perm[j17] = fRec6_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec5_tmp[j18] = fRec5_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fConst50 * (fConst54 * fRec6[i] + fConst55 * fRec6[faust_wrap_sub(i, 1)] + fConst54 * fRec6[faust_wrap_sub(i, 2)]) - fConst56 * (fConst57 * fRec5[faust_wrap_sub(i, 2)] + fConst58 * fRec5[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec5_perm[j19] = fRec5_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec4_tmp[j20] = fRec4_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fSlow1 * fRec4[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst56 * (fConst60 * fRec5[i] + fConst61 * fRec5[faust_wrap_sub(i, 1)] + fConst60 * fRec5[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec4_perm[j21] = fRec4_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec3_tmp[j0] = fRec3_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = static_cast<double>(input0[i]) - fConst3 * (fConst4 * fRec3[faust_wrap_sub(i, 2)] + fConst7 * fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec3_perm[j1] = fRec3_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fConst3 * (fConst9 * fRec3[i] + fConst10 * fRec3[faust_wrap_sub(i, 1)] + fConst9 * fRec3[faust_wrap_sub(i, 2)]) - fConst11 * (fConst12 * fRec2[faust_wrap_sub(i, 2)] + fConst13 * fRec2[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec1_tmp[j4] = fRec1_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fConst11 * (fConst15 * fRec2[i] + fConst16 * fRec2[faust_wrap_sub(i, 1)] + fConst15 * fRec2[faust_wrap_sub(i, 2)]) - fConst17 * (fConst18 * fRec1[faust_wrap_sub(i, 2)] + fConst19 * fRec1[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec1_perm[j5] = fRec1_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec0_tmp[j6] = fRec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fRec0[faust_wrap_sub(i, 1)] * fSlow1 + std::fabs(fConst17 * (fConst22 * fRec1[i] + fConst23 * fRec1[faust_wrap_sub(i, 1)] + fConst22 * fRec1[faust_wrap_sub(i, 2)])) * fSlow2;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec0_perm[j7] = fRec0_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec17_tmp[j22] = fRec17_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fZec0[i] - fConst62 * (fConst63 * fRec17[faust_wrap_sub(i, 2)] + fConst64 * fRec17[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec17_perm[j23] = fRec17_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec16_tmp[j24] = fRec16_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = fConst62 * (fConst66 * fRec17[i] + fConst67 * fRec17[faust_wrap_sub(i, 1)] + fConst66 * fRec17[faust_wrap_sub(i, 2)]) - fConst68 * (fConst69 * fRec16[faust_wrap_sub(i, 2)] + fConst70 * fRec16[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec16_perm[j25] = fRec16_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec15_tmp[j26] = fRec15_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fConst68 * (fConst71 * fRec16[i] + fConst72 * fRec16[faust_wrap_sub(i, 1)] + fConst71 * fRec16[faust_wrap_sub(i, 2)]) - fConst73 * (fConst74 * fRec15[faust_wrap_sub(i, 2)] + fConst75 * fRec15[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec15_perm[j27] = fRec15_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fConst73 * (fConst76 * fRec15[i] + fConst77 * fRec15[faust_wrap_sub(i, 1)] + fConst76 * fRec15[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec24_tmp[j36] = fRec24_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec1[i] - fConst100 * (fConst101 * fRec24[faust_wrap_sub(i, 2)] + fConst102 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec24_perm[j37] = fRec24_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec23_tmp[j38] = fRec23_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst100 * (fConst104 * fRec24[i] + fConst105 * fRec24[faust_wrap_sub(i, 1)] + fConst104 * fRec24[faust_wrap_sub(i, 2)]) - fConst106 * (fConst107 * fRec23[faust_wrap_sub(i, 2)] + fConst108 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec23_perm[j39] = fRec23_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec22_tmp[j40] = fRec22_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst106 * (fConst109 * fRec23[i] + fConst110 * fRec23[faust_wrap_sub(i, 1)] + fConst109 * fRec23[faust_wrap_sub(i, 2)]) - fConst111 * (fConst112 * fRec22[faust_wrap_sub(i, 2)] + fConst113 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec22_perm[j41] = fRec22_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fConst111 * (fConst114 * fRec22[i] + fConst115 * fRec22[faust_wrap_sub(i, 1)] + fConst114 * fRec22[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec31_tmp[j50] = fRec31_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec2[i] - fConst138 * (fConst139 * fRec31[faust_wrap_sub(i, 2)] + fConst140 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec31_perm[j51] = fRec31_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec30_tmp[j52] = fRec30_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst138 * (fConst142 * fRec31[i] + fConst143 * fRec31[faust_wrap_sub(i, 1)] + fConst142 * fRec31[faust_wrap_sub(i, 2)]) - fConst144 * (fConst145 * fRec30[faust_wrap_sub(i, 2)] + fConst146 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec30_perm[j53] = fRec30_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec29_tmp[j54] = fRec29_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst144 * (fConst147 * fRec30[i] + fConst148 * fRec30[faust_wrap_sub(i, 1)] + fConst147 * fRec30[faust_wrap_sub(i, 2)]) - fConst149 * (fConst150 * fRec29[faust_wrap_sub(i, 2)] + fConst151 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec29_perm[j55] = fRec29_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fConst149 * (fConst152 * fRec29[i] + fConst153 * fRec29[faust_wrap_sub(i, 1)] + fConst152 * fRec29[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec38_tmp[j64] = fRec38_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec3[i] - fConst176 * (fConst177 * fRec38[faust_wrap_sub(i, 2)] + fConst178 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec38_perm[j65] = fRec38_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec37_tmp[j66] = fRec37_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst176 * (fConst180 * fRec38[i] + fConst181 * fRec38[faust_wrap_sub(i, 1)] + fConst180 * fRec38[faust_wrap_sub(i, 2)]) - fConst182 * (fConst183 * fRec37[faust_wrap_sub(i, 2)] + fConst184 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec37_perm[j67] = fRec37_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec36_tmp[j68] = fRec36_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst182 * (fConst185 * fRec37[i] + fConst186 * fRec37[faust_wrap_sub(i, 1)] + fConst185 * fRec37[faust_wrap_sub(i, 2)]) - fConst187 * (fConst188 * fRec36[faust_wrap_sub(i, 2)] + fConst189 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec36_perm[j69] = fRec36_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fConst187 * (fConst190 * fRec36[i] + fConst191 * fRec36[faust_wrap_sub(i, 1)] + fConst190 * fRec36[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec45_tmp[j78] = fRec45_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec4[i] - fConst214 * (fConst215 * fRec45[faust_wrap_sub(i, 2)] + fConst216 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec45_perm[j79] = fRec45_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Recursive loop 29 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec44_tmp[j80] = fRec44_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst214 * (fConst218 * fRec45[i] + fConst219 * fRec45[faust_wrap_sub(i, 1)] + fConst218 * fRec45[faust_wrap_sub(i, 2)]) - fConst220 * (fConst221 * fRec44[faust_wrap_sub(i, 2)] + fConst222 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec44_perm[j81] = fRec44_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec43_tmp[j82] = fRec43_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst220 * (fConst223 * fRec44[i] + fConst224 * fRec44[faust_wrap_sub(i, 1)] + fConst223 * fRec44[faust_wrap_sub(i, 2)]) - fConst225 * (fConst226 * fRec43[faust_wrap_sub(i, 2)] + fConst227 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec43_perm[j83] = fRec43_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fConst225 * (fConst228 * fRec43[i] + fConst229 * fRec43[faust_wrap_sub(i, 1)] + fConst228 * fRec43[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec52_tmp[j92] = fRec52_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec5[i] - fConst252 * (fConst253 * fRec52[faust_wrap_sub(i, 2)] + fConst254 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec52_perm[j93] = fRec52_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec51_tmp[j94] = fRec51_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst252 * (fConst256 * fRec52[i] + fConst257 * fRec52[faust_wrap_sub(i, 1)] + fConst256 * fRec52[faust_wrap_sub(i, 2)]) - fConst258 * (fConst259 * fRec51[faust_wrap_sub(i, 2)] + fConst260 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec51_perm[j95] = fRec51_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec50_tmp[j96] = fRec50_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst258 * (fConst261 * fRec51[i] + fConst262 * fRec51[faust_wrap_sub(i, 1)] + fConst261 * fRec51[faust_wrap_sub(i, 2)]) - fConst263 * (fConst264 * fRec50[faust_wrap_sub(i, 2)] + fConst265 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec50_perm[j97] = fRec50_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = fConst263 * (fConst266 * fRec50[i] + fConst267 * fRec50[faust_wrap_sub(i, 1)] + fConst266 * fRec50[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec59_tmp[j106] = fRec59_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec6[i] - fConst290 * (fConst291 * fRec59[faust_wrap_sub(i, 2)] + fConst292 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec59_perm[j107] = fRec59_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 37 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec58_tmp[j108] = fRec58_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst290 * (fConst294 * fRec59[i] + fConst295 * fRec59[faust_wrap_sub(i, 1)] + fConst294 * fRec59[faust_wrap_sub(i, 2)]) - fConst296 * (fConst297 * fRec58[faust_wrap_sub(i, 2)] + fConst298 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec58_perm[j109] = fRec58_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 38 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec57_tmp[j110] = fRec57_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst296 * (fConst299 * fRec58[i] + fConst300 * fRec58[faust_wrap_sub(i, 1)] + fConst299 * fRec58[faust_wrap_sub(i, 2)]) - fConst301 * (fConst302 * fRec57[faust_wrap_sub(i, 2)] + fConst303 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec57_perm[j111] = fRec57_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fConst301 * (fConst304 * fRec57[i] + fConst305 * fRec57[faust_wrap_sub(i, 1)] + fConst304 * fRec57[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec66_tmp[j120] = fRec66_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec7[i] - fConst328 * (fConst329 * fRec66[faust_wrap_sub(i, 2)] + fConst330 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec66_perm[j121] = fRec66_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 41 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec65_tmp[j122] = fRec65_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst328 * (fConst332 * fRec66[i] + fConst333 * fRec66[faust_wrap_sub(i, 1)] + fConst332 * fRec66[faust_wrap_sub(i, 2)]) - fConst334 * (fConst335 * fRec65[faust_wrap_sub(i, 2)] + fConst336 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec65_perm[j123] = fRec65_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec64_tmp[j124] = fRec64_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst334 * (fConst337 * fRec65[i] + fConst338 * fRec65[faust_wrap_sub(i, 1)] + fConst337 * fRec65[faust_wrap_sub(i, 2)]) - fConst339 * (fConst340 * fRec64[faust_wrap_sub(i, 2)] + fConst341 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec64_perm[j125] = fRec64_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fConst339 * (fConst342 * fRec64[i] + fConst343 * fRec64[faust_wrap_sub(i, 1)] + fConst342 * fRec64[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec73_tmp[j134] = fRec73_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec8[i] - fConst366 * (fConst367 * fRec73[faust_wrap_sub(i, 2)] + fConst368 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec73_perm[j135] = fRec73_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 45 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec72_tmp[j136] = fRec72_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst366 * (fConst370 * fRec73[i] + fConst371 * fRec73[faust_wrap_sub(i, 1)] + fConst370 * fRec73[faust_wrap_sub(i, 2)]) - fConst372 * (fConst373 * fRec72[faust_wrap_sub(i, 2)] + fConst374 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec72_perm[j137] = fRec72_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec71_tmp[j138] = fRec71_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst372 * (fConst375 * fRec72[i] + fConst376 * fRec72[faust_wrap_sub(i, 1)] + fConst375 * fRec72[faust_wrap_sub(i, 2)]) - fConst377 * (fConst378 * fRec71[faust_wrap_sub(i, 2)] + fConst379 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec71_perm[j139] = fRec71_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = fConst377 * (fConst380 * fRec71[i] + fConst381 * fRec71[faust_wrap_sub(i, 1)] + fConst380 * fRec71[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec80_tmp[j148] = fRec80_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec9[i] - fConst404 * (fConst405 * fRec80[faust_wrap_sub(i, 2)] + fConst406 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec80_perm[j149] = fRec80_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec79_tmp[j150] = fRec79_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst404 * (fConst408 * fRec80[i] + fConst409 * fRec80[faust_wrap_sub(i, 1)] + fConst408 * fRec80[faust_wrap_sub(i, 2)]) - fConst410 * (fConst411 * fRec79[faust_wrap_sub(i, 2)] + fConst412 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec79_perm[j151] = fRec79_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec78_tmp[j152] = fRec78_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst410 * (fConst413 * fRec79[i] + fConst414 * fRec79[faust_wrap_sub(i, 1)] + fConst413 * fRec79[faust_wrap_sub(i, 2)]) - fConst415 * (fConst416 * fRec78[faust_wrap_sub(i, 2)] + fConst417 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec78_perm[j153] = fRec78_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fConst415 * (fConst418 * fRec78[i] + fConst419 * fRec78[faust_wrap_sub(i, 1)] + fConst418 * fRec78[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec87_tmp[j162] = fRec87_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec10[i] - fConst442 * (fConst443 * fRec87[faust_wrap_sub(i, 2)] + fConst444 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec87_perm[j163] = fRec87_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 53 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec86_tmp[j164] = fRec86_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst442 * (fConst446 * fRec87[i] + fConst447 * fRec87[faust_wrap_sub(i, 1)] + fConst446 * fRec87[faust_wrap_sub(i, 2)]) - fConst448 * (fConst449 * fRec86[faust_wrap_sub(i, 2)] + fConst450 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec86_perm[j165] = fRec86_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec85_tmp[j166] = fRec85_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst448 * (fConst451 * fRec86[i] + fConst452 * fRec86[faust_wrap_sub(i, 1)] + fConst451 * fRec86[faust_wrap_sub(i, 2)]) - fConst453 * (fConst454 * fRec85[faust_wrap_sub(i, 2)] + fConst455 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec85_perm[j167] = fRec85_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = fConst453 * (fConst456 * fRec85[i] + fConst457 * fRec85[faust_wrap_sub(i, 1)] + fConst456 * fRec85[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec94_tmp[j176] = fRec94_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec11[i] - fConst480 * (fConst481 * fRec94[faust_wrap_sub(i, 2)] + fConst482 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec94_perm[j177] = fRec94_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 57 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec93_tmp[j178] = fRec93_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst480 * (fConst484 * fRec94[i] + fConst485 * fRec94[faust_wrap_sub(i, 1)] + fConst484 * fRec94[faust_wrap_sub(i, 2)]) - fConst486 * (fConst487 * fRec93[faust_wrap_sub(i, 2)] + fConst488 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec93_perm[j179] = fRec93_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec92_tmp[j180] = fRec92_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst486 * (fConst489 * fRec93[i] + fConst490 * fRec93[faust_wrap_sub(i, 1)] + fConst489 * fRec93[faust_wrap_sub(i, 2)]) - fConst491 * (fConst492 * fRec92[faust_wrap_sub(i, 2)] + fConst493 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec92_perm[j181] = fRec92_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = fConst491 * (fConst494 * fRec92[i] + fConst495 * fRec92[faust_wrap_sub(i, 1)] + fConst494 * fRec92[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec101_tmp[j190] = fRec101_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec12[i] - fConst518 * (fConst519 * fRec101[faust_wrap_sub(i, 2)] + fConst520 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec101_perm[j191] = fRec101_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 61 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec100_tmp[j192] = fRec100_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst518 * (fConst522 * fRec101[i] + fConst523 * fRec101[faust_wrap_sub(i, 1)] + fConst522 * fRec101[faust_wrap_sub(i, 2)]) - fConst524 * (fConst525 * fRec100[faust_wrap_sub(i, 2)] + fConst526 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec100_perm[j193] = fRec100_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec99_tmp[j194] = fRec99_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst524 * (fConst527 * fRec100[i] + fConst528 * fRec100[faust_wrap_sub(i, 1)] + fConst527 * fRec100[faust_wrap_sub(i, 2)]) - fConst529 * (fConst530 * fRec99[faust_wrap_sub(i, 2)] + fConst531 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec99_perm[j195] = fRec99_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = fConst529 * (fConst532 * fRec99[i] + fConst533 * fRec99[faust_wrap_sub(i, 1)] + fConst532 * fRec99[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec108_tmp[j204] = fRec108_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fZec13[i] - fConst556 * (fConst557 * fRec108[faust_wrap_sub(i, 2)] + fConst558 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec108_perm[j205] = fRec108_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec107_tmp[j206] = fRec107_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst556 * (fConst560 * fRec108[i] + fConst561 * fRec108[faust_wrap_sub(i, 1)] + fConst560 * fRec108[faust_wrap_sub(i, 2)]) - fConst562 * (fConst563 * fRec107[faust_wrap_sub(i, 2)] + fConst564 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec107_perm[j207] = fRec107_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec106_tmp[j208] = fRec106_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fConst562 * (fConst565 * fRec107[i] + fConst566 * fRec107[faust_wrap_sub(i, 1)] + fConst565 * fRec107[faust_wrap_sub(i, 2)]) - fConst567 * (fConst568 * fRec106[faust_wrap_sub(i, 2)] + fConst569 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec106_perm[j209] = fRec106_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fConst567 * (fConst570 * fRec106[i] + fConst571 * fRec106[faust_wrap_sub(i, 1)] + fConst570 * fRec106[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec115_tmp[j218] = fRec115_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fZec14[i] - fConst594 * (fConst595 * fRec115[faust_wrap_sub(i, 2)] + fConst596 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec115_perm[j219] = fRec115_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec114_tmp[j220] = fRec114_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst594 * (fConst598 * fRec115[i] + fConst599 * fRec115[faust_wrap_sub(i, 1)] + fConst598 * fRec115[faust_wrap_sub(i, 2)]) - fConst600 * (fConst601 * fRec114[faust_wrap_sub(i, 2)] + fConst602 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec114_perm[j221] = fRec114_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec113_tmp[j222] = fRec113_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fConst600 * (fConst603 * fRec114[i] + fConst604 * fRec114[faust_wrap_sub(i, 1)] + fConst603 * fRec114[faust_wrap_sub(i, 2)]) - fConst605 * (fConst606 * fRec113[faust_wrap_sub(i, 2)] + fConst607 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec113_perm[j223] = fRec113_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = fConst605 * (fConst608 * fRec113[i] + fConst609 * fRec113[faust_wrap_sub(i, 1)] + fConst608 * fRec113[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec122_tmp[j232] = fRec122_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fZec15[i] - fConst632 * (fConst633 * fRec122[faust_wrap_sub(i, 2)] + fConst634 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec122_perm[j233] = fRec122_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec121_tmp[j234] = fRec121_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst632 * (fConst636 * fRec122[i] + fConst637 * fRec122[faust_wrap_sub(i, 1)] + fConst636 * fRec122[faust_wrap_sub(i, 2)]) - fConst638 * (fConst639 * fRec121[faust_wrap_sub(i, 2)] + fConst640 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec121_perm[j235] = fRec121_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec120_tmp[j236] = fRec120_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fConst638 * (fConst641 * fRec121[i] + fConst642 * fRec121[faust_wrap_sub(i, 1)] + fConst641 * fRec121[faust_wrap_sub(i, 2)]) - fConst643 * (fConst644 * fRec120[faust_wrap_sub(i, 2)] + fConst645 * fRec120[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec120_perm[j237] = fRec120_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fConst643 * (fConst646 * fRec120[i] + fConst647 * fRec120[faust_wrap_sub(i, 1)] + fConst646 * fRec120[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec129_tmp[j246] = fRec129_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec129[i] = fZec16[i] - fConst670 * (fConst671 * fRec129[faust_wrap_sub(i, 2)] + fConst672 * fRec129[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec129_perm[j247] = fRec129_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec128_tmp[j248] = fRec128_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec128[i] = fConst670 * (fConst674 * fRec129[i] + fConst675 * fRec129[faust_wrap_sub(i, 1)] + fConst674 * fRec129[faust_wrap_sub(i, 2)]) - fConst676 * (fConst677 * fRec128[faust_wrap_sub(i, 2)] + fConst678 * fRec128[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec128_perm[j249] = fRec128_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec127_tmp[j250] = fRec127_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fConst676 * (fConst679 * fRec128[i] + fConst680 * fRec128[faust_wrap_sub(i, 1)] + fConst679 * fRec128[faust_wrap_sub(i, 2)]) - fConst681 * (fConst682 * fRec127[faust_wrap_sub(i, 2)] + fConst683 * fRec127[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec127_perm[j251] = fRec127_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fConst681 * (fConst684 * fRec127[i] + fConst685 * fRec127[faust_wrap_sub(i, 1)] + fConst684 * fRec127[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec136_tmp[j260] = fRec136_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec136[i] = fZec17[i] - fConst708 * (fConst709 * fRec136[faust_wrap_sub(i, 2)] + fConst710 * fRec136[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec136_perm[j261] = fRec136_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec135_tmp[j262] = fRec135_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec135[i] = fConst708 * (fConst712 * fRec136[i] + fConst713 * fRec136[faust_wrap_sub(i, 1)] + fConst712 * fRec136[faust_wrap_sub(i, 2)]) - fConst714 * (fConst715 * fRec135[faust_wrap_sub(i, 2)] + fConst716 * fRec135[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec135_perm[j263] = fRec135_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec134_tmp[j264] = fRec134_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec134[i] = fConst714 * (fConst717 * fRec135[i] + fConst718 * fRec135[faust_wrap_sub(i, 1)] + fConst717 * fRec135[faust_wrap_sub(i, 2)]) - fConst719 * (fConst720 * fRec134[faust_wrap_sub(i, 2)] + fConst721 * fRec134[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec134_perm[j265] = fRec134_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = fConst719 * (fConst722 * fRec134[i] + fConst723 * fRec134[faust_wrap_sub(i, 1)] + fConst722 * fRec134[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec143_tmp[j274] = fRec143_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec143[i] = fZec18[i] - fConst746 * (fConst747 * fRec143[faust_wrap_sub(i, 2)] + fConst748 * fRec143[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec143_perm[j275] = fRec143_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec142_tmp[j276] = fRec142_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec142[i] = fConst746 * (fConst750 * fRec143[i] + fConst751 * fRec143[faust_wrap_sub(i, 1)] + fConst750 * fRec143[faust_wrap_sub(i, 2)]) - fConst752 * (fConst753 * fRec142[faust_wrap_sub(i, 2)] + fConst754 * fRec142[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec142_perm[j277] = fRec142_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec141_tmp[j278] = fRec141_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec141[i] = fConst752 * (fConst755 * fRec142[i] + fConst756 * fRec142[faust_wrap_sub(i, 1)] + fConst755 * fRec142[faust_wrap_sub(i, 2)]) - fConst757 * (fConst758 * fRec141[faust_wrap_sub(i, 2)] + fConst759 * fRec141[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec141_perm[j279] = fRec141_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fConst757 * (fConst760 * fRec141[i] + fConst761 * fRec141[faust_wrap_sub(i, 1)] + fConst760 * fRec141[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec150_tmp[j288] = fRec150_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec150[i] = fZec19[i] - fConst784 * (fConst785 * fRec150[faust_wrap_sub(i, 2)] + fConst786 * fRec150[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec150_perm[j289] = fRec150_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec149_tmp[j290] = fRec149_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec149[i] = fConst784 * (fConst788 * fRec150[i] + fConst789 * fRec150[faust_wrap_sub(i, 1)] + fConst788 * fRec150[faust_wrap_sub(i, 2)]) - fConst790 * (fConst791 * fRec149[faust_wrap_sub(i, 2)] + fConst792 * fRec149[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec149_perm[j291] = fRec149_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec148_tmp[j292] = fRec148_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec148[i] = fConst790 * (fConst793 * fRec149[i] + fConst794 * fRec149[faust_wrap_sub(i, 1)] + fConst793 * fRec149[faust_wrap_sub(i, 2)]) - fConst795 * (fConst796 * fRec148[faust_wrap_sub(i, 2)] + fConst797 * fRec148[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec148_perm[j293] = fRec148_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = fConst795 * (fConst798 * fRec148[i] + fConst799 * fRec148[faust_wrap_sub(i, 1)] + fConst798 * fRec148[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec157_tmp[j302] = fRec157_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec157[i] = fZec20[i] - fConst822 * (fConst823 * fRec157[faust_wrap_sub(i, 2)] + fConst824 * fRec157[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec157_perm[j303] = fRec157_tmp[faust_wrap_add(vsize, j303)];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec156_tmp[j304] = fRec156_perm[j304];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec156[i] = fConst822 * (fConst826 * fRec157[i] + fConst827 * fRec157[faust_wrap_sub(i, 1)] + fConst826 * fRec157[faust_wrap_sub(i, 2)]) - fConst828 * (fConst829 * fRec156[faust_wrap_sub(i, 2)] + fConst830 * fRec156[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec156_perm[j305] = fRec156_tmp[faust_wrap_add(vsize, j305)];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec155_tmp[j306] = fRec155_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec155[i] = fConst828 * (fConst831 * fRec156[i] + fConst832 * fRec156[faust_wrap_sub(i, 1)] + fConst831 * fRec156[faust_wrap_sub(i, 2)]) - fConst833 * (fConst834 * fRec155[faust_wrap_sub(i, 2)] + fConst835 * fRec155[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec155_perm[j307] = fRec155_tmp[faust_wrap_add(vsize, j307)];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = fConst833 * (fConst836 * fRec155[i] + fConst837 * fRec155[faust_wrap_sub(i, 1)] + fConst836 * fRec155[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j316 = 0; j316 < 4; j316 = faust_wrap_add(j316, 1)) {
				fRec164_tmp[j316] = fRec164_perm[j316];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec164[i] = fZec21[i] - fConst860 * (fConst861 * fRec164[faust_wrap_sub(i, 2)] + fConst862 * fRec164[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j317 = 0; j317 < 4; j317 = faust_wrap_add(j317, 1)) {
				fRec164_perm[j317] = fRec164_tmp[faust_wrap_add(vsize, j317)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j318 = 0; j318 < 4; j318 = faust_wrap_add(j318, 1)) {
				fRec163_tmp[j318] = fRec163_perm[j318];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec163[i] = fConst860 * (fConst864 * fRec164[i] + fConst865 * fRec164[faust_wrap_sub(i, 1)] + fConst864 * fRec164[faust_wrap_sub(i, 2)]) - fConst866 * (fConst867 * fRec163[faust_wrap_sub(i, 2)] + fConst868 * fRec163[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j319 = 0; j319 < 4; j319 = faust_wrap_add(j319, 1)) {
				fRec163_perm[j319] = fRec163_tmp[faust_wrap_add(vsize, j319)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j320 = 0; j320 < 4; j320 = faust_wrap_add(j320, 1)) {
				fRec162_tmp[j320] = fRec162_perm[j320];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec162[i] = fConst866 * (fConst869 * fRec163[i] + fConst870 * fRec163[faust_wrap_sub(i, 1)] + fConst869 * fRec163[faust_wrap_sub(i, 2)]) - fConst871 * (fConst872 * fRec162[faust_wrap_sub(i, 2)] + fConst873 * fRec162[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j321 = 0; j321 < 4; j321 = faust_wrap_add(j321, 1)) {
				fRec162_perm[j321] = fRec162_tmp[faust_wrap_add(vsize, j321)];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fConst871 * (fConst874 * fRec162[i] + fConst875 * fRec162[faust_wrap_sub(i, 1)] + fConst874 * fRec162[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j330 = 0; j330 < 4; j330 = faust_wrap_add(j330, 1)) {
				fRec171_tmp[j330] = fRec171_perm[j330];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec171[i] = fZec22[i] - fConst898 * (fConst899 * fRec171[faust_wrap_sub(i, 2)] + fConst900 * fRec171[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j331 = 0; j331 < 4; j331 = faust_wrap_add(j331, 1)) {
				fRec171_perm[j331] = fRec171_tmp[faust_wrap_add(vsize, j331)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j332 = 0; j332 < 4; j332 = faust_wrap_add(j332, 1)) {
				fRec170_tmp[j332] = fRec170_perm[j332];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec170[i] = fConst898 * (fConst902 * fRec171[i] + fConst903 * fRec171[faust_wrap_sub(i, 1)] + fConst902 * fRec171[faust_wrap_sub(i, 2)]) - fConst904 * (fConst905 * fRec170[faust_wrap_sub(i, 2)] + fConst906 * fRec170[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j333 = 0; j333 < 4; j333 = faust_wrap_add(j333, 1)) {
				fRec170_perm[j333] = fRec170_tmp[faust_wrap_add(vsize, j333)];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j334 = 0; j334 < 4; j334 = faust_wrap_add(j334, 1)) {
				fRec169_tmp[j334] = fRec169_perm[j334];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec169[i] = fConst904 * (fConst907 * fRec170[i] + fConst908 * fRec170[faust_wrap_sub(i, 1)] + fConst907 * fRec170[faust_wrap_sub(i, 2)]) - fConst909 * (fConst910 * fRec169[faust_wrap_sub(i, 2)] + fConst911 * fRec169[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j335 = 0; j335 < 4; j335 = faust_wrap_add(j335, 1)) {
				fRec169_perm[j335] = fRec169_tmp[faust_wrap_add(vsize, j335)];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fConst909 * (fConst912 * fRec169[i] + fConst913 * fRec169[faust_wrap_sub(i, 1)] + fConst912 * fRec169[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j344 = 0; j344 < 4; j344 = faust_wrap_add(j344, 1)) {
				fRec178_tmp[j344] = fRec178_perm[j344];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec178[i] = fZec23[i] - fConst936 * (fConst937 * fRec178[faust_wrap_sub(i, 2)] + fConst938 * fRec178[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j345 = 0; j345 < 4; j345 = faust_wrap_add(j345, 1)) {
				fRec178_perm[j345] = fRec178_tmp[faust_wrap_add(vsize, j345)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j346 = 0; j346 < 4; j346 = faust_wrap_add(j346, 1)) {
				fRec177_tmp[j346] = fRec177_perm[j346];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec177[i] = fConst936 * (fConst940 * fRec178[i] + fConst941 * fRec178[faust_wrap_sub(i, 1)] + fConst940 * fRec178[faust_wrap_sub(i, 2)]) - fConst942 * (fConst943 * fRec177[faust_wrap_sub(i, 2)] + fConst944 * fRec177[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j347 = 0; j347 < 4; j347 = faust_wrap_add(j347, 1)) {
				fRec177_perm[j347] = fRec177_tmp[faust_wrap_add(vsize, j347)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j348 = 0; j348 < 4; j348 = faust_wrap_add(j348, 1)) {
				fRec176_tmp[j348] = fRec176_perm[j348];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec176[i] = fConst942 * (fConst945 * fRec177[i] + fConst946 * fRec177[faust_wrap_sub(i, 1)] + fConst945 * fRec177[faust_wrap_sub(i, 2)]) - fConst947 * (fConst948 * fRec176[faust_wrap_sub(i, 2)] + fConst949 * fRec176[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j349 = 0; j349 < 4; j349 = faust_wrap_add(j349, 1)) {
				fRec176_perm[j349] = fRec176_tmp[faust_wrap_add(vsize, j349)];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fConst947 * (fConst950 * fRec176[i] + fConst951 * fRec176[faust_wrap_sub(i, 1)] + fConst950 * fRec176[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j358 = 0; j358 < 4; j358 = faust_wrap_add(j358, 1)) {
				fRec185_tmp[j358] = fRec185_perm[j358];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec185[i] = fZec24[i] - fConst974 * (fConst975 * fRec185[faust_wrap_sub(i, 2)] + fConst976 * fRec185[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j359 = 0; j359 < 4; j359 = faust_wrap_add(j359, 1)) {
				fRec185_perm[j359] = fRec185_tmp[faust_wrap_add(vsize, j359)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j360 = 0; j360 < 4; j360 = faust_wrap_add(j360, 1)) {
				fRec184_tmp[j360] = fRec184_perm[j360];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec184[i] = fConst974 * (fConst978 * fRec185[i] + fConst979 * fRec185[faust_wrap_sub(i, 1)] + fConst978 * fRec185[faust_wrap_sub(i, 2)]) - fConst980 * (fConst981 * fRec184[faust_wrap_sub(i, 2)] + fConst982 * fRec184[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j361 = 0; j361 < 4; j361 = faust_wrap_add(j361, 1)) {
				fRec184_perm[j361] = fRec184_tmp[faust_wrap_add(vsize, j361)];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j362 = 0; j362 < 4; j362 = faust_wrap_add(j362, 1)) {
				fRec183_tmp[j362] = fRec183_perm[j362];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec183[i] = fConst980 * (fConst983 * fRec184[i] + fConst984 * fRec184[faust_wrap_sub(i, 1)] + fConst983 * fRec184[faust_wrap_sub(i, 2)]) - fConst985 * (fConst986 * fRec183[faust_wrap_sub(i, 2)] + fConst987 * fRec183[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j363 = 0; j363 < 4; j363 = faust_wrap_add(j363, 1)) {
				fRec183_perm[j363] = fRec183_tmp[faust_wrap_add(vsize, j363)];
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = fConst985 * (fConst988 * fRec183[i] + fConst989 * fRec183[faust_wrap_sub(i, 1)] + fConst988 * fRec183[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j372 = 0; j372 < 4; j372 = faust_wrap_add(j372, 1)) {
				fRec192_tmp[j372] = fRec192_perm[j372];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec192[i] = fZec25[i] - fConst1012 * (fConst1013 * fRec192[faust_wrap_sub(i, 2)] + fConst1014 * fRec192[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j373 = 0; j373 < 4; j373 = faust_wrap_add(j373, 1)) {
				fRec192_perm[j373] = fRec192_tmp[faust_wrap_add(vsize, j373)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j374 = 0; j374 < 4; j374 = faust_wrap_add(j374, 1)) {
				fRec191_tmp[j374] = fRec191_perm[j374];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec191[i] = fConst1012 * (fConst1016 * fRec192[i] + fConst1017 * fRec192[faust_wrap_sub(i, 1)] + fConst1016 * fRec192[faust_wrap_sub(i, 2)]) - fConst1018 * (fConst1019 * fRec191[faust_wrap_sub(i, 2)] + fConst1020 * fRec191[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j375 = 0; j375 < 4; j375 = faust_wrap_add(j375, 1)) {
				fRec191_perm[j375] = fRec191_tmp[faust_wrap_add(vsize, j375)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j376 = 0; j376 < 4; j376 = faust_wrap_add(j376, 1)) {
				fRec190_tmp[j376] = fRec190_perm[j376];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec190[i] = fConst1018 * (fConst1021 * fRec191[i] + fConst1022 * fRec191[faust_wrap_sub(i, 1)] + fConst1021 * fRec191[faust_wrap_sub(i, 2)]) - fConst1023 * (fConst1024 * fRec190[faust_wrap_sub(i, 2)] + fConst1025 * fRec190[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j377 = 0; j377 < 4; j377 = faust_wrap_add(j377, 1)) {
				fRec190_perm[j377] = fRec190_tmp[faust_wrap_add(vsize, j377)];
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fConst1023 * (fConst1026 * fRec190[i] + fConst1027 * fRec190[faust_wrap_sub(i, 1)] + fConst1026 * fRec190[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j386 = 0; j386 < 4; j386 = faust_wrap_add(j386, 1)) {
				fRec199_tmp[j386] = fRec199_perm[j386];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec199[i] = fZec26[i] - fConst1050 * (fConst1051 * fRec199[faust_wrap_sub(i, 2)] + fConst1052 * fRec199[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j387 = 0; j387 < 4; j387 = faust_wrap_add(j387, 1)) {
				fRec199_perm[j387] = fRec199_tmp[faust_wrap_add(vsize, j387)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j388 = 0; j388 < 4; j388 = faust_wrap_add(j388, 1)) {
				fRec198_tmp[j388] = fRec198_perm[j388];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec198[i] = fConst1050 * (fConst1054 * fRec199[i] + fConst1055 * fRec199[faust_wrap_sub(i, 1)] + fConst1054 * fRec199[faust_wrap_sub(i, 2)]) - fConst1056 * (fConst1057 * fRec198[faust_wrap_sub(i, 2)] + fConst1058 * fRec198[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j389 = 0; j389 < 4; j389 = faust_wrap_add(j389, 1)) {
				fRec198_perm[j389] = fRec198_tmp[faust_wrap_add(vsize, j389)];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j390 = 0; j390 < 4; j390 = faust_wrap_add(j390, 1)) {
				fRec197_tmp[j390] = fRec197_perm[j390];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec197[i] = fConst1056 * (fConst1059 * fRec198[i] + fConst1060 * fRec198[faust_wrap_sub(i, 1)] + fConst1059 * fRec198[faust_wrap_sub(i, 2)]) - fConst1061 * (fConst1062 * fRec197[faust_wrap_sub(i, 2)] + fConst1063 * fRec197[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j391 = 0; j391 < 4; j391 = faust_wrap_add(j391, 1)) {
				fRec197_perm[j391] = fRec197_tmp[faust_wrap_add(vsize, j391)];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = fConst1061 * (fConst1064 * fRec197[i] + fConst1065 * fRec197[faust_wrap_sub(i, 1)] + fConst1064 * fRec197[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j400 = 0; j400 < 4; j400 = faust_wrap_add(j400, 1)) {
				fRec203_tmp[j400] = fRec203_perm[j400];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec203[i] = fZec27[i] - fConst1088 * (fConst1089 * fRec203[faust_wrap_sub(i, 2)] + fConst1090 * fRec203[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j401 = 0; j401 < 4; j401 = faust_wrap_add(j401, 1)) {
				fRec203_perm[j401] = fRec203_tmp[faust_wrap_add(vsize, j401)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j402 = 0; j402 < 4; j402 = faust_wrap_add(j402, 1)) {
				fRec202_tmp[j402] = fRec202_perm[j402];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec202[i] = fConst1088 * (fConst1092 * fRec203[i] + fConst1093 * fRec203[faust_wrap_sub(i, 1)] + fConst1092 * fRec203[faust_wrap_sub(i, 2)]) - fConst1094 * (fConst1095 * fRec202[faust_wrap_sub(i, 2)] + fConst1096 * fRec202[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j403 = 0; j403 < 4; j403 = faust_wrap_add(j403, 1)) {
				fRec202_perm[j403] = fRec202_tmp[faust_wrap_add(vsize, j403)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j404 = 0; j404 < 4; j404 = faust_wrap_add(j404, 1)) {
				fRec201_tmp[j404] = fRec201_perm[j404];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec201[i] = fConst1094 * (fConst1097 * fRec202[i] + fConst1098 * fRec202[faust_wrap_sub(i, 1)] + fConst1097 * fRec202[faust_wrap_sub(i, 2)]) - fConst1099 * (fConst1100 * fRec201[faust_wrap_sub(i, 2)] + fConst1101 * fRec201[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j405 = 0; j405 < 4; j405 = faust_wrap_add(j405, 1)) {
				fRec201_perm[j405] = fRec201_tmp[faust_wrap_add(vsize, j405)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j406 = 0; j406 < 4; j406 = faust_wrap_add(j406, 1)) {
				fRec200_tmp[j406] = fRec200_perm[j406];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec200[i] = fSlow1 * fRec200[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1099 * (fConst1102 * fRec201[i] + fConst1103 * fRec201[faust_wrap_sub(i, 1)] + fConst1102 * fRec201[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j407 = 0; j407 < 4; j407 = faust_wrap_add(j407, 1)) {
				fRec200_perm[j407] = fRec200_tmp[faust_wrap_add(vsize, j407)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec14_tmp[j28] = fRec14_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fZec1[i] - fConst80 * (fConst81 * fRec14[faust_wrap_sub(i, 2)] + fConst84 * fRec14[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec14_perm[j29] = fRec14_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec13_tmp[j30] = fRec13_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fConst80 * (fConst86 * fRec14[i] + fConst87 * fRec14[faust_wrap_sub(i, 1)] + fConst86 * fRec14[faust_wrap_sub(i, 2)]) - fConst88 * (fConst89 * fRec13[faust_wrap_sub(i, 2)] + fConst90 * fRec13[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec13_perm[j31] = fRec13_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec12_tmp[j32] = fRec12_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fConst88 * (fConst92 * fRec13[i] + fConst93 * fRec13[faust_wrap_sub(i, 1)] + fConst92 * fRec13[faust_wrap_sub(i, 2)]) - fConst94 * (fConst95 * fRec12[faust_wrap_sub(i, 2)] + fConst96 * fRec12[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec12_perm[j33] = fRec12_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec11_tmp[j34] = fRec11_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow1 * fRec11[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst94 * (fConst98 * fRec12[i] + fConst99 * fRec12[faust_wrap_sub(i, 1)] + fConst98 * fRec12[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec11_perm[j35] = fRec11_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec21_tmp[j42] = fRec21_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fZec2[i] - fConst118 * (fConst119 * fRec21[faust_wrap_sub(i, 2)] + fConst122 * fRec21[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec21_perm[j43] = fRec21_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec20_tmp[j44] = fRec20_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fConst118 * (fConst124 * fRec21[i] + fConst125 * fRec21[faust_wrap_sub(i, 1)] + fConst124 * fRec21[faust_wrap_sub(i, 2)]) - fConst126 * (fConst127 * fRec20[faust_wrap_sub(i, 2)] + fConst128 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec20_perm[j45] = fRec20_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec19_tmp[j46] = fRec19_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst126 * (fConst130 * fRec20[i] + fConst131 * fRec20[faust_wrap_sub(i, 1)] + fConst130 * fRec20[faust_wrap_sub(i, 2)]) - fConst132 * (fConst133 * fRec19[faust_wrap_sub(i, 2)] + fConst134 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec19_perm[j47] = fRec19_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec18_tmp[j48] = fRec18_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fSlow1 * fRec18[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst132 * (fConst136 * fRec19[i] + fConst137 * fRec19[faust_wrap_sub(i, 1)] + fConst136 * fRec19[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec18_perm[j49] = fRec18_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec28_tmp[j56] = fRec28_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fZec3[i] - fConst156 * (fConst157 * fRec28[faust_wrap_sub(i, 2)] + fConst160 * fRec28[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec28_perm[j57] = fRec28_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec27_tmp[j58] = fRec27_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fConst156 * (fConst162 * fRec28[i] + fConst163 * fRec28[faust_wrap_sub(i, 1)] + fConst162 * fRec28[faust_wrap_sub(i, 2)]) - fConst164 * (fConst165 * fRec27[faust_wrap_sub(i, 2)] + fConst166 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec27_perm[j59] = fRec27_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec26_tmp[j60] = fRec26_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst164 * (fConst168 * fRec27[i] + fConst169 * fRec27[faust_wrap_sub(i, 1)] + fConst168 * fRec27[faust_wrap_sub(i, 2)]) - fConst170 * (fConst171 * fRec26[faust_wrap_sub(i, 2)] + fConst172 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec26_perm[j61] = fRec26_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec25_tmp[j62] = fRec25_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fSlow1 * fRec25[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst170 * (fConst174 * fRec26[i] + fConst175 * fRec26[faust_wrap_sub(i, 1)] + fConst174 * fRec26[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec25_perm[j63] = fRec25_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec35_tmp[j70] = fRec35_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fZec4[i] - fConst194 * (fConst195 * fRec35[faust_wrap_sub(i, 2)] + fConst198 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec35_perm[j71] = fRec35_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec34_tmp[j72] = fRec34_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst194 * (fConst200 * fRec35[i] + fConst201 * fRec35[faust_wrap_sub(i, 1)] + fConst200 * fRec35[faust_wrap_sub(i, 2)]) - fConst202 * (fConst203 * fRec34[faust_wrap_sub(i, 2)] + fConst204 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec34_perm[j73] = fRec34_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec33_tmp[j74] = fRec33_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst202 * (fConst206 * fRec34[i] + fConst207 * fRec34[faust_wrap_sub(i, 1)] + fConst206 * fRec34[faust_wrap_sub(i, 2)]) - fConst208 * (fConst209 * fRec33[faust_wrap_sub(i, 2)] + fConst210 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec33_perm[j75] = fRec33_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec32_tmp[j76] = fRec32_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fSlow1 * fRec32[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst208 * (fConst212 * fRec33[i] + fConst213 * fRec33[faust_wrap_sub(i, 1)] + fConst212 * fRec33[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec32_perm[j77] = fRec32_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec42_tmp[j84] = fRec42_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fZec5[i] - fConst232 * (fConst233 * fRec42[faust_wrap_sub(i, 2)] + fConst236 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec42_perm[j85] = fRec42_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec41_tmp[j86] = fRec41_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst232 * (fConst238 * fRec42[i] + fConst239 * fRec42[faust_wrap_sub(i, 1)] + fConst238 * fRec42[faust_wrap_sub(i, 2)]) - fConst240 * (fConst241 * fRec41[faust_wrap_sub(i, 2)] + fConst242 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec41_perm[j87] = fRec41_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec40_tmp[j88] = fRec40_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst240 * (fConst244 * fRec41[i] + fConst245 * fRec41[faust_wrap_sub(i, 1)] + fConst244 * fRec41[faust_wrap_sub(i, 2)]) - fConst246 * (fConst247 * fRec40[faust_wrap_sub(i, 2)] + fConst248 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec40_perm[j89] = fRec40_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec39_tmp[j90] = fRec39_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fSlow1 * fRec39[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst246 * (fConst250 * fRec40[i] + fConst251 * fRec40[faust_wrap_sub(i, 1)] + fConst250 * fRec40[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec39_perm[j91] = fRec39_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec49_tmp[j98] = fRec49_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fZec6[i] - fConst270 * (fConst271 * fRec49[faust_wrap_sub(i, 2)] + fConst274 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec49_perm[j99] = fRec49_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec48_tmp[j100] = fRec48_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst270 * (fConst276 * fRec49[i] + fConst277 * fRec49[faust_wrap_sub(i, 1)] + fConst276 * fRec49[faust_wrap_sub(i, 2)]) - fConst278 * (fConst279 * fRec48[faust_wrap_sub(i, 2)] + fConst280 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec48_perm[j101] = fRec48_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec47_tmp[j102] = fRec47_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst278 * (fConst282 * fRec48[i] + fConst283 * fRec48[faust_wrap_sub(i, 1)] + fConst282 * fRec48[faust_wrap_sub(i, 2)]) - fConst284 * (fConst285 * fRec47[faust_wrap_sub(i, 2)] + fConst286 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec47_perm[j103] = fRec47_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec46_tmp[j104] = fRec46_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fSlow1 * fRec46[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst284 * (fConst288 * fRec47[i] + fConst289 * fRec47[faust_wrap_sub(i, 1)] + fConst288 * fRec47[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec46_perm[j105] = fRec46_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec56_tmp[j112] = fRec56_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fZec7[i] - fConst308 * (fConst309 * fRec56[faust_wrap_sub(i, 2)] + fConst312 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec56_perm[j113] = fRec56_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec55_tmp[j114] = fRec55_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst308 * (fConst314 * fRec56[i] + fConst315 * fRec56[faust_wrap_sub(i, 1)] + fConst314 * fRec56[faust_wrap_sub(i, 2)]) - fConst316 * (fConst317 * fRec55[faust_wrap_sub(i, 2)] + fConst318 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec55_perm[j115] = fRec55_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec54_tmp[j116] = fRec54_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst316 * (fConst320 * fRec55[i] + fConst321 * fRec55[faust_wrap_sub(i, 1)] + fConst320 * fRec55[faust_wrap_sub(i, 2)]) - fConst322 * (fConst323 * fRec54[faust_wrap_sub(i, 2)] + fConst324 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec54_perm[j117] = fRec54_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec53_tmp[j118] = fRec53_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fSlow1 * fRec53[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst322 * (fConst326 * fRec54[i] + fConst327 * fRec54[faust_wrap_sub(i, 1)] + fConst326 * fRec54[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec53_perm[j119] = fRec53_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec63_tmp[j126] = fRec63_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fZec8[i] - fConst346 * (fConst347 * fRec63[faust_wrap_sub(i, 2)] + fConst350 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec63_perm[j127] = fRec63_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec62_tmp[j128] = fRec62_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst346 * (fConst352 * fRec63[i] + fConst353 * fRec63[faust_wrap_sub(i, 1)] + fConst352 * fRec63[faust_wrap_sub(i, 2)]) - fConst354 * (fConst355 * fRec62[faust_wrap_sub(i, 2)] + fConst356 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec62_perm[j129] = fRec62_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec61_tmp[j130] = fRec61_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst354 * (fConst358 * fRec62[i] + fConst359 * fRec62[faust_wrap_sub(i, 1)] + fConst358 * fRec62[faust_wrap_sub(i, 2)]) - fConst360 * (fConst361 * fRec61[faust_wrap_sub(i, 2)] + fConst362 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec61_perm[j131] = fRec61_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec60_tmp[j132] = fRec60_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fSlow1 * fRec60[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst360 * (fConst364 * fRec61[i] + fConst365 * fRec61[faust_wrap_sub(i, 1)] + fConst364 * fRec61[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec60_perm[j133] = fRec60_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec70_tmp[j140] = fRec70_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fZec9[i] - fConst384 * (fConst385 * fRec70[faust_wrap_sub(i, 2)] + fConst388 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec70_perm[j141] = fRec70_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec69_tmp[j142] = fRec69_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst384 * (fConst390 * fRec70[i] + fConst391 * fRec70[faust_wrap_sub(i, 1)] + fConst390 * fRec70[faust_wrap_sub(i, 2)]) - fConst392 * (fConst393 * fRec69[faust_wrap_sub(i, 2)] + fConst394 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec69_perm[j143] = fRec69_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec68_tmp[j144] = fRec68_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst392 * (fConst396 * fRec69[i] + fConst397 * fRec69[faust_wrap_sub(i, 1)] + fConst396 * fRec69[faust_wrap_sub(i, 2)]) - fConst398 * (fConst399 * fRec68[faust_wrap_sub(i, 2)] + fConst400 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec68_perm[j145] = fRec68_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec67_tmp[j146] = fRec67_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fSlow1 * fRec67[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst398 * (fConst402 * fRec68[i] + fConst403 * fRec68[faust_wrap_sub(i, 1)] + fConst402 * fRec68[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec67_perm[j147] = fRec67_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec77_tmp[j154] = fRec77_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fZec10[i] - fConst422 * (fConst423 * fRec77[faust_wrap_sub(i, 2)] + fConst426 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec77_perm[j155] = fRec77_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec76_tmp[j156] = fRec76_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst422 * (fConst428 * fRec77[i] + fConst429 * fRec77[faust_wrap_sub(i, 1)] + fConst428 * fRec77[faust_wrap_sub(i, 2)]) - fConst430 * (fConst431 * fRec76[faust_wrap_sub(i, 2)] + fConst432 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec76_perm[j157] = fRec76_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec75_tmp[j158] = fRec75_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst430 * (fConst434 * fRec76[i] + fConst435 * fRec76[faust_wrap_sub(i, 1)] + fConst434 * fRec76[faust_wrap_sub(i, 2)]) - fConst436 * (fConst437 * fRec75[faust_wrap_sub(i, 2)] + fConst438 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec75_perm[j159] = fRec75_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec74_tmp[j160] = fRec74_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fSlow1 * fRec74[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst436 * (fConst440 * fRec75[i] + fConst441 * fRec75[faust_wrap_sub(i, 1)] + fConst440 * fRec75[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec74_perm[j161] = fRec74_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec84_tmp[j168] = fRec84_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fZec11[i] - fConst460 * (fConst461 * fRec84[faust_wrap_sub(i, 2)] + fConst464 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec84_perm[j169] = fRec84_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec83_tmp[j170] = fRec83_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst460 * (fConst466 * fRec84[i] + fConst467 * fRec84[faust_wrap_sub(i, 1)] + fConst466 * fRec84[faust_wrap_sub(i, 2)]) - fConst468 * (fConst469 * fRec83[faust_wrap_sub(i, 2)] + fConst470 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec83_perm[j171] = fRec83_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec82_tmp[j172] = fRec82_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst468 * (fConst472 * fRec83[i] + fConst473 * fRec83[faust_wrap_sub(i, 1)] + fConst472 * fRec83[faust_wrap_sub(i, 2)]) - fConst474 * (fConst475 * fRec82[faust_wrap_sub(i, 2)] + fConst476 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec82_perm[j173] = fRec82_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec81_tmp[j174] = fRec81_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fSlow1 * fRec81[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst474 * (fConst478 * fRec82[i] + fConst479 * fRec82[faust_wrap_sub(i, 1)] + fConst478 * fRec82[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec81_perm[j175] = fRec81_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec91_tmp[j182] = fRec91_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fZec12[i] - fConst498 * (fConst499 * fRec91[faust_wrap_sub(i, 2)] + fConst502 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec91_perm[j183] = fRec91_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec90_tmp[j184] = fRec90_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst498 * (fConst504 * fRec91[i] + fConst505 * fRec91[faust_wrap_sub(i, 1)] + fConst504 * fRec91[faust_wrap_sub(i, 2)]) - fConst506 * (fConst507 * fRec90[faust_wrap_sub(i, 2)] + fConst508 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec90_perm[j185] = fRec90_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec89_tmp[j186] = fRec89_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst506 * (fConst510 * fRec90[i] + fConst511 * fRec90[faust_wrap_sub(i, 1)] + fConst510 * fRec90[faust_wrap_sub(i, 2)]) - fConst512 * (fConst513 * fRec89[faust_wrap_sub(i, 2)] + fConst514 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec89_perm[j187] = fRec89_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec88_tmp[j188] = fRec88_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fSlow1 * fRec88[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst512 * (fConst516 * fRec89[i] + fConst517 * fRec89[faust_wrap_sub(i, 1)] + fConst516 * fRec89[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec88_perm[j189] = fRec88_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec98_tmp[j196] = fRec98_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fZec13[i] - fConst536 * (fConst537 * fRec98[faust_wrap_sub(i, 2)] + fConst540 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec98_perm[j197] = fRec98_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec97_tmp[j198] = fRec97_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst536 * (fConst542 * fRec98[i] + fConst543 * fRec98[faust_wrap_sub(i, 1)] + fConst542 * fRec98[faust_wrap_sub(i, 2)]) - fConst544 * (fConst545 * fRec97[faust_wrap_sub(i, 2)] + fConst546 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec97_perm[j199] = fRec97_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec96_tmp[j200] = fRec96_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst544 * (fConst548 * fRec97[i] + fConst549 * fRec97[faust_wrap_sub(i, 1)] + fConst548 * fRec97[faust_wrap_sub(i, 2)]) - fConst550 * (fConst551 * fRec96[faust_wrap_sub(i, 2)] + fConst552 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec96_perm[j201] = fRec96_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec95_tmp[j202] = fRec95_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fSlow1 * fRec95[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst550 * (fConst554 * fRec96[i] + fConst555 * fRec96[faust_wrap_sub(i, 1)] + fConst554 * fRec96[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec95_perm[j203] = fRec95_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec105_tmp[j210] = fRec105_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fZec14[i] - fConst574 * (fConst575 * fRec105[faust_wrap_sub(i, 2)] + fConst578 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec105_perm[j211] = fRec105_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec104_tmp[j212] = fRec104_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst574 * (fConst580 * fRec105[i] + fConst581 * fRec105[faust_wrap_sub(i, 1)] + fConst580 * fRec105[faust_wrap_sub(i, 2)]) - fConst582 * (fConst583 * fRec104[faust_wrap_sub(i, 2)] + fConst584 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec104_perm[j213] = fRec104_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec103_tmp[j214] = fRec103_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst582 * (fConst586 * fRec104[i] + fConst587 * fRec104[faust_wrap_sub(i, 1)] + fConst586 * fRec104[faust_wrap_sub(i, 2)]) - fConst588 * (fConst589 * fRec103[faust_wrap_sub(i, 2)] + fConst590 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec103_perm[j215] = fRec103_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec102_tmp[j216] = fRec102_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fSlow1 * fRec102[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst588 * (fConst592 * fRec103[i] + fConst593 * fRec103[faust_wrap_sub(i, 1)] + fConst592 * fRec103[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec102_perm[j217] = fRec102_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec112_tmp[j224] = fRec112_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fZec15[i] - fConst612 * (fConst613 * fRec112[faust_wrap_sub(i, 2)] + fConst616 * fRec112[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec112_perm[j225] = fRec112_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec111_tmp[j226] = fRec111_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fConst612 * (fConst618 * fRec112[i] + fConst619 * fRec112[faust_wrap_sub(i, 1)] + fConst618 * fRec112[faust_wrap_sub(i, 2)]) - fConst620 * (fConst621 * fRec111[faust_wrap_sub(i, 2)] + fConst622 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec111_perm[j227] = fRec111_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec110_tmp[j228] = fRec110_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst620 * (fConst624 * fRec111[i] + fConst625 * fRec111[faust_wrap_sub(i, 1)] + fConst624 * fRec111[faust_wrap_sub(i, 2)]) - fConst626 * (fConst627 * fRec110[faust_wrap_sub(i, 2)] + fConst628 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec110_perm[j229] = fRec110_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec109_tmp[j230] = fRec109_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fSlow1 * fRec109[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst626 * (fConst630 * fRec110[i] + fConst631 * fRec110[faust_wrap_sub(i, 1)] + fConst630 * fRec110[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec109_perm[j231] = fRec109_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 184 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec119_tmp[j238] = fRec119_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fZec16[i] - fConst650 * (fConst651 * fRec119[faust_wrap_sub(i, 2)] + fConst654 * fRec119[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec119_perm[j239] = fRec119_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec118_tmp[j240] = fRec118_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fConst650 * (fConst656 * fRec119[i] + fConst657 * fRec119[faust_wrap_sub(i, 1)] + fConst656 * fRec119[faust_wrap_sub(i, 2)]) - fConst658 * (fConst659 * fRec118[faust_wrap_sub(i, 2)] + fConst660 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec118_perm[j241] = fRec118_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec117_tmp[j242] = fRec117_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fConst658 * (fConst662 * fRec118[i] + fConst663 * fRec118[faust_wrap_sub(i, 1)] + fConst662 * fRec118[faust_wrap_sub(i, 2)]) - fConst664 * (fConst665 * fRec117[faust_wrap_sub(i, 2)] + fConst666 * fRec117[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec117_perm[j243] = fRec117_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec116_tmp[j244] = fRec116_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fSlow1 * fRec116[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst664 * (fConst668 * fRec117[i] + fConst669 * fRec117[faust_wrap_sub(i, 1)] + fConst668 * fRec117[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec116_perm[j245] = fRec116_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec126_tmp[j252] = fRec126_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fZec17[i] - fConst688 * (fConst689 * fRec126[faust_wrap_sub(i, 2)] + fConst692 * fRec126[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec126_perm[j253] = fRec126_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec125_tmp[j254] = fRec125_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fConst688 * (fConst694 * fRec126[i] + fConst695 * fRec126[faust_wrap_sub(i, 1)] + fConst694 * fRec126[faust_wrap_sub(i, 2)]) - fConst696 * (fConst697 * fRec125[faust_wrap_sub(i, 2)] + fConst698 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec125_perm[j255] = fRec125_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 190 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec124_tmp[j256] = fRec124_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fConst696 * (fConst700 * fRec125[i] + fConst701 * fRec125[faust_wrap_sub(i, 1)] + fConst700 * fRec125[faust_wrap_sub(i, 2)]) - fConst702 * (fConst703 * fRec124[faust_wrap_sub(i, 2)] + fConst704 * fRec124[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec124_perm[j257] = fRec124_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec123_tmp[j258] = fRec123_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fSlow1 * fRec123[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst702 * (fConst706 * fRec124[i] + fConst707 * fRec124[faust_wrap_sub(i, 1)] + fConst706 * fRec124[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec123_perm[j259] = fRec123_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 192 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec133_tmp[j266] = fRec133_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec133[i] = fZec18[i] - fConst726 * (fConst727 * fRec133[faust_wrap_sub(i, 2)] + fConst730 * fRec133[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec133_perm[j267] = fRec133_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec132_tmp[j268] = fRec132_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec132[i] = fConst726 * (fConst732 * fRec133[i] + fConst733 * fRec133[faust_wrap_sub(i, 1)] + fConst732 * fRec133[faust_wrap_sub(i, 2)]) - fConst734 * (fConst735 * fRec132[faust_wrap_sub(i, 2)] + fConst736 * fRec132[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec132_perm[j269] = fRec132_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec131_tmp[j270] = fRec131_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec131[i] = fConst734 * (fConst738 * fRec132[i] + fConst739 * fRec132[faust_wrap_sub(i, 1)] + fConst738 * fRec132[faust_wrap_sub(i, 2)]) - fConst740 * (fConst741 * fRec131[faust_wrap_sub(i, 2)] + fConst742 * fRec131[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec131_perm[j271] = fRec131_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec130_tmp[j272] = fRec130_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec130[i] = fSlow1 * fRec130[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst740 * (fConst744 * fRec131[i] + fConst745 * fRec131[faust_wrap_sub(i, 1)] + fConst744 * fRec131[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec130_perm[j273] = fRec130_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec140_tmp[j280] = fRec140_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec140[i] = fZec19[i] - fConst764 * (fConst765 * fRec140[faust_wrap_sub(i, 2)] + fConst768 * fRec140[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec140_perm[j281] = fRec140_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec139_tmp[j282] = fRec139_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec139[i] = fConst764 * (fConst770 * fRec140[i] + fConst771 * fRec140[faust_wrap_sub(i, 1)] + fConst770 * fRec140[faust_wrap_sub(i, 2)]) - fConst772 * (fConst773 * fRec139[faust_wrap_sub(i, 2)] + fConst774 * fRec139[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec139_perm[j283] = fRec139_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 198 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec138_tmp[j284] = fRec138_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec138[i] = fConst772 * (fConst776 * fRec139[i] + fConst777 * fRec139[faust_wrap_sub(i, 1)] + fConst776 * fRec139[faust_wrap_sub(i, 2)]) - fConst778 * (fConst779 * fRec138[faust_wrap_sub(i, 2)] + fConst780 * fRec138[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec138_perm[j285] = fRec138_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec137_tmp[j286] = fRec137_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec137[i] = fSlow1 * fRec137[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst778 * (fConst782 * fRec138[i] + fConst783 * fRec138[faust_wrap_sub(i, 1)] + fConst782 * fRec138[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec137_perm[j287] = fRec137_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 200 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec147_tmp[j294] = fRec147_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec147[i] = fZec20[i] - fConst802 * (fConst803 * fRec147[faust_wrap_sub(i, 2)] + fConst806 * fRec147[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec147_perm[j295] = fRec147_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec146_tmp[j296] = fRec146_perm[j296];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec146[i] = fConst802 * (fConst808 * fRec147[i] + fConst809 * fRec147[faust_wrap_sub(i, 1)] + fConst808 * fRec147[faust_wrap_sub(i, 2)]) - fConst810 * (fConst811 * fRec146[faust_wrap_sub(i, 2)] + fConst812 * fRec146[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec146_perm[j297] = fRec146_tmp[faust_wrap_add(vsize, j297)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec145_tmp[j298] = fRec145_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec145[i] = fConst810 * (fConst814 * fRec146[i] + fConst815 * fRec146[faust_wrap_sub(i, 1)] + fConst814 * fRec146[faust_wrap_sub(i, 2)]) - fConst816 * (fConst817 * fRec145[faust_wrap_sub(i, 2)] + fConst818 * fRec145[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec145_perm[j299] = fRec145_tmp[faust_wrap_add(vsize, j299)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec144_tmp[j300] = fRec144_perm[j300];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec144[i] = fSlow1 * fRec144[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst816 * (fConst820 * fRec145[i] + fConst821 * fRec145[faust_wrap_sub(i, 1)] + fConst820 * fRec145[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec144_perm[j301] = fRec144_tmp[faust_wrap_add(vsize, j301)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j308 = 0; j308 < 4; j308 = faust_wrap_add(j308, 1)) {
				fRec154_tmp[j308] = fRec154_perm[j308];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec154[i] = fZec21[i] - fConst840 * (fConst841 * fRec154[faust_wrap_sub(i, 2)] + fConst844 * fRec154[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j309 = 0; j309 < 4; j309 = faust_wrap_add(j309, 1)) {
				fRec154_perm[j309] = fRec154_tmp[faust_wrap_add(vsize, j309)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j310 = 0; j310 < 4; j310 = faust_wrap_add(j310, 1)) {
				fRec153_tmp[j310] = fRec153_perm[j310];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec153[i] = fConst840 * (fConst846 * fRec154[i] + fConst847 * fRec154[faust_wrap_sub(i, 1)] + fConst846 * fRec154[faust_wrap_sub(i, 2)]) - fConst848 * (fConst849 * fRec153[faust_wrap_sub(i, 2)] + fConst850 * fRec153[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j311 = 0; j311 < 4; j311 = faust_wrap_add(j311, 1)) {
				fRec153_perm[j311] = fRec153_tmp[faust_wrap_add(vsize, j311)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j312 = 0; j312 < 4; j312 = faust_wrap_add(j312, 1)) {
				fRec152_tmp[j312] = fRec152_perm[j312];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec152[i] = fConst848 * (fConst852 * fRec153[i] + fConst853 * fRec153[faust_wrap_sub(i, 1)] + fConst852 * fRec153[faust_wrap_sub(i, 2)]) - fConst854 * (fConst855 * fRec152[faust_wrap_sub(i, 2)] + fConst856 * fRec152[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j313 = 0; j313 < 4; j313 = faust_wrap_add(j313, 1)) {
				fRec152_perm[j313] = fRec152_tmp[faust_wrap_add(vsize, j313)];
			}
			/* Recursive loop 207 */
			/* Pre code */
			for (int j314 = 0; j314 < 4; j314 = faust_wrap_add(j314, 1)) {
				fRec151_tmp[j314] = fRec151_perm[j314];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec151[i] = fSlow1 * fRec151[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst854 * (fConst858 * fRec152[i] + fConst859 * fRec152[faust_wrap_sub(i, 1)] + fConst858 * fRec152[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j315 = 0; j315 < 4; j315 = faust_wrap_add(j315, 1)) {
				fRec151_perm[j315] = fRec151_tmp[faust_wrap_add(vsize, j315)];
			}
			/* Recursive loop 208 */
			/* Pre code */
			for (int j322 = 0; j322 < 4; j322 = faust_wrap_add(j322, 1)) {
				fRec161_tmp[j322] = fRec161_perm[j322];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec161[i] = fZec22[i] - fConst878 * (fConst879 * fRec161[faust_wrap_sub(i, 2)] + fConst882 * fRec161[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j323 = 0; j323 < 4; j323 = faust_wrap_add(j323, 1)) {
				fRec161_perm[j323] = fRec161_tmp[faust_wrap_add(vsize, j323)];
			}
			/* Recursive loop 209 */
			/* Pre code */
			for (int j324 = 0; j324 < 4; j324 = faust_wrap_add(j324, 1)) {
				fRec160_tmp[j324] = fRec160_perm[j324];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec160[i] = fConst878 * (fConst884 * fRec161[i] + fConst885 * fRec161[faust_wrap_sub(i, 1)] + fConst884 * fRec161[faust_wrap_sub(i, 2)]) - fConst886 * (fConst887 * fRec160[faust_wrap_sub(i, 2)] + fConst888 * fRec160[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j325 = 0; j325 < 4; j325 = faust_wrap_add(j325, 1)) {
				fRec160_perm[j325] = fRec160_tmp[faust_wrap_add(vsize, j325)];
			}
			/* Recursive loop 210 */
			/* Pre code */
			for (int j326 = 0; j326 < 4; j326 = faust_wrap_add(j326, 1)) {
				fRec159_tmp[j326] = fRec159_perm[j326];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec159[i] = fConst886 * (fConst890 * fRec160[i] + fConst891 * fRec160[faust_wrap_sub(i, 1)] + fConst890 * fRec160[faust_wrap_sub(i, 2)]) - fConst892 * (fConst893 * fRec159[faust_wrap_sub(i, 2)] + fConst894 * fRec159[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j327 = 0; j327 < 4; j327 = faust_wrap_add(j327, 1)) {
				fRec159_perm[j327] = fRec159_tmp[faust_wrap_add(vsize, j327)];
			}
			/* Recursive loop 211 */
			/* Pre code */
			for (int j328 = 0; j328 < 4; j328 = faust_wrap_add(j328, 1)) {
				fRec158_tmp[j328] = fRec158_perm[j328];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec158[i] = fSlow1 * fRec158[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst892 * (fConst896 * fRec159[i] + fConst897 * fRec159[faust_wrap_sub(i, 1)] + fConst896 * fRec159[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j329 = 0; j329 < 4; j329 = faust_wrap_add(j329, 1)) {
				fRec158_perm[j329] = fRec158_tmp[faust_wrap_add(vsize, j329)];
			}
			/* Recursive loop 212 */
			/* Pre code */
			for (int j336 = 0; j336 < 4; j336 = faust_wrap_add(j336, 1)) {
				fRec168_tmp[j336] = fRec168_perm[j336];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec168[i] = fZec23[i] - fConst916 * (fConst917 * fRec168[faust_wrap_sub(i, 2)] + fConst920 * fRec168[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j337 = 0; j337 < 4; j337 = faust_wrap_add(j337, 1)) {
				fRec168_perm[j337] = fRec168_tmp[faust_wrap_add(vsize, j337)];
			}
			/* Recursive loop 213 */
			/* Pre code */
			for (int j338 = 0; j338 < 4; j338 = faust_wrap_add(j338, 1)) {
				fRec167_tmp[j338] = fRec167_perm[j338];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec167[i] = fConst916 * (fConst922 * fRec168[i] + fConst923 * fRec168[faust_wrap_sub(i, 1)] + fConst922 * fRec168[faust_wrap_sub(i, 2)]) - fConst924 * (fConst925 * fRec167[faust_wrap_sub(i, 2)] + fConst926 * fRec167[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j339 = 0; j339 < 4; j339 = faust_wrap_add(j339, 1)) {
				fRec167_perm[j339] = fRec167_tmp[faust_wrap_add(vsize, j339)];
			}
			/* Recursive loop 214 */
			/* Pre code */
			for (int j340 = 0; j340 < 4; j340 = faust_wrap_add(j340, 1)) {
				fRec166_tmp[j340] = fRec166_perm[j340];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec166[i] = fConst924 * (fConst928 * fRec167[i] + fConst929 * fRec167[faust_wrap_sub(i, 1)] + fConst928 * fRec167[faust_wrap_sub(i, 2)]) - fConst930 * (fConst931 * fRec166[faust_wrap_sub(i, 2)] + fConst932 * fRec166[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j341 = 0; j341 < 4; j341 = faust_wrap_add(j341, 1)) {
				fRec166_perm[j341] = fRec166_tmp[faust_wrap_add(vsize, j341)];
			}
			/* Recursive loop 215 */
			/* Pre code */
			for (int j342 = 0; j342 < 4; j342 = faust_wrap_add(j342, 1)) {
				fRec165_tmp[j342] = fRec165_perm[j342];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec165[i] = fSlow1 * fRec165[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst930 * (fConst934 * fRec166[i] + fConst935 * fRec166[faust_wrap_sub(i, 1)] + fConst934 * fRec166[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j343 = 0; j343 < 4; j343 = faust_wrap_add(j343, 1)) {
				fRec165_perm[j343] = fRec165_tmp[faust_wrap_add(vsize, j343)];
			}
			/* Recursive loop 216 */
			/* Pre code */
			for (int j350 = 0; j350 < 4; j350 = faust_wrap_add(j350, 1)) {
				fRec175_tmp[j350] = fRec175_perm[j350];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec175[i] = fZec24[i] - fConst954 * (fConst955 * fRec175[faust_wrap_sub(i, 2)] + fConst958 * fRec175[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j351 = 0; j351 < 4; j351 = faust_wrap_add(j351, 1)) {
				fRec175_perm[j351] = fRec175_tmp[faust_wrap_add(vsize, j351)];
			}
			/* Recursive loop 217 */
			/* Pre code */
			for (int j352 = 0; j352 < 4; j352 = faust_wrap_add(j352, 1)) {
				fRec174_tmp[j352] = fRec174_perm[j352];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec174[i] = fConst954 * (fConst960 * fRec175[i] + fConst961 * fRec175[faust_wrap_sub(i, 1)] + fConst960 * fRec175[faust_wrap_sub(i, 2)]) - fConst962 * (fConst963 * fRec174[faust_wrap_sub(i, 2)] + fConst964 * fRec174[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j353 = 0; j353 < 4; j353 = faust_wrap_add(j353, 1)) {
				fRec174_perm[j353] = fRec174_tmp[faust_wrap_add(vsize, j353)];
			}
			/* Recursive loop 218 */
			/* Pre code */
			for (int j354 = 0; j354 < 4; j354 = faust_wrap_add(j354, 1)) {
				fRec173_tmp[j354] = fRec173_perm[j354];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec173[i] = fConst962 * (fConst966 * fRec174[i] + fConst967 * fRec174[faust_wrap_sub(i, 1)] + fConst966 * fRec174[faust_wrap_sub(i, 2)]) - fConst968 * (fConst969 * fRec173[faust_wrap_sub(i, 2)] + fConst970 * fRec173[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j355 = 0; j355 < 4; j355 = faust_wrap_add(j355, 1)) {
				fRec173_perm[j355] = fRec173_tmp[faust_wrap_add(vsize, j355)];
			}
			/* Recursive loop 219 */
			/* Pre code */
			for (int j356 = 0; j356 < 4; j356 = faust_wrap_add(j356, 1)) {
				fRec172_tmp[j356] = fRec172_perm[j356];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec172[i] = fSlow1 * fRec172[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst968 * (fConst972 * fRec173[i] + fConst973 * fRec173[faust_wrap_sub(i, 1)] + fConst972 * fRec173[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j357 = 0; j357 < 4; j357 = faust_wrap_add(j357, 1)) {
				fRec172_perm[j357] = fRec172_tmp[faust_wrap_add(vsize, j357)];
			}
			/* Recursive loop 220 */
			/* Pre code */
			for (int j364 = 0; j364 < 4; j364 = faust_wrap_add(j364, 1)) {
				fRec182_tmp[j364] = fRec182_perm[j364];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec182[i] = fZec25[i] - fConst992 * (fConst993 * fRec182[faust_wrap_sub(i, 2)] + fConst996 * fRec182[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j365 = 0; j365 < 4; j365 = faust_wrap_add(j365, 1)) {
				fRec182_perm[j365] = fRec182_tmp[faust_wrap_add(vsize, j365)];
			}
			/* Recursive loop 221 */
			/* Pre code */
			for (int j366 = 0; j366 < 4; j366 = faust_wrap_add(j366, 1)) {
				fRec181_tmp[j366] = fRec181_perm[j366];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec181[i] = fConst992 * (fConst998 * fRec182[i] + fConst999 * fRec182[faust_wrap_sub(i, 1)] + fConst998 * fRec182[faust_wrap_sub(i, 2)]) - fConst1000 * (fConst1001 * fRec181[faust_wrap_sub(i, 2)] + fConst1002 * fRec181[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j367 = 0; j367 < 4; j367 = faust_wrap_add(j367, 1)) {
				fRec181_perm[j367] = fRec181_tmp[faust_wrap_add(vsize, j367)];
			}
			/* Recursive loop 222 */
			/* Pre code */
			for (int j368 = 0; j368 < 4; j368 = faust_wrap_add(j368, 1)) {
				fRec180_tmp[j368] = fRec180_perm[j368];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec180[i] = fConst1000 * (fConst1004 * fRec181[i] + fConst1005 * fRec181[faust_wrap_sub(i, 1)] + fConst1004 * fRec181[faust_wrap_sub(i, 2)]) - fConst1006 * (fConst1007 * fRec180[faust_wrap_sub(i, 2)] + fConst1008 * fRec180[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j369 = 0; j369 < 4; j369 = faust_wrap_add(j369, 1)) {
				fRec180_perm[j369] = fRec180_tmp[faust_wrap_add(vsize, j369)];
			}
			/* Recursive loop 223 */
			/* Pre code */
			for (int j370 = 0; j370 < 4; j370 = faust_wrap_add(j370, 1)) {
				fRec179_tmp[j370] = fRec179_perm[j370];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec179[i] = fSlow1 * fRec179[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1006 * (fConst1010 * fRec180[i] + fConst1011 * fRec180[faust_wrap_sub(i, 1)] + fConst1010 * fRec180[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j371 = 0; j371 < 4; j371 = faust_wrap_add(j371, 1)) {
				fRec179_perm[j371] = fRec179_tmp[faust_wrap_add(vsize, j371)];
			}
			/* Recursive loop 224 */
			/* Pre code */
			for (int j378 = 0; j378 < 4; j378 = faust_wrap_add(j378, 1)) {
				fRec189_tmp[j378] = fRec189_perm[j378];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec189[i] = fZec26[i] - fConst1030 * (fConst1031 * fRec189[faust_wrap_sub(i, 2)] + fConst1034 * fRec189[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j379 = 0; j379 < 4; j379 = faust_wrap_add(j379, 1)) {
				fRec189_perm[j379] = fRec189_tmp[faust_wrap_add(vsize, j379)];
			}
			/* Recursive loop 225 */
			/* Pre code */
			for (int j380 = 0; j380 < 4; j380 = faust_wrap_add(j380, 1)) {
				fRec188_tmp[j380] = fRec188_perm[j380];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec188[i] = fConst1030 * (fConst1036 * fRec189[i] + fConst1037 * fRec189[faust_wrap_sub(i, 1)] + fConst1036 * fRec189[faust_wrap_sub(i, 2)]) - fConst1038 * (fConst1039 * fRec188[faust_wrap_sub(i, 2)] + fConst1040 * fRec188[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j381 = 0; j381 < 4; j381 = faust_wrap_add(j381, 1)) {
				fRec188_perm[j381] = fRec188_tmp[faust_wrap_add(vsize, j381)];
			}
			/* Recursive loop 226 */
			/* Pre code */
			for (int j382 = 0; j382 < 4; j382 = faust_wrap_add(j382, 1)) {
				fRec187_tmp[j382] = fRec187_perm[j382];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec187[i] = fConst1038 * (fConst1042 * fRec188[i] + fConst1043 * fRec188[faust_wrap_sub(i, 1)] + fConst1042 * fRec188[faust_wrap_sub(i, 2)]) - fConst1044 * (fConst1045 * fRec187[faust_wrap_sub(i, 2)] + fConst1046 * fRec187[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j383 = 0; j383 < 4; j383 = faust_wrap_add(j383, 1)) {
				fRec187_perm[j383] = fRec187_tmp[faust_wrap_add(vsize, j383)];
			}
			/* Recursive loop 227 */
			/* Pre code */
			for (int j384 = 0; j384 < 4; j384 = faust_wrap_add(j384, 1)) {
				fRec186_tmp[j384] = fRec186_perm[j384];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec186[i] = fSlow1 * fRec186[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1044 * (fConst1048 * fRec187[i] + fConst1049 * fRec187[faust_wrap_sub(i, 1)] + fConst1048 * fRec187[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j385 = 0; j385 < 4; j385 = faust_wrap_add(j385, 1)) {
				fRec186_perm[j385] = fRec186_tmp[faust_wrap_add(vsize, j385)];
			}
			/* Recursive loop 228 */
			/* Pre code */
			for (int j392 = 0; j392 < 4; j392 = faust_wrap_add(j392, 1)) {
				fRec196_tmp[j392] = fRec196_perm[j392];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec196[i] = fZec27[i] - fConst1068 * (fConst1069 * fRec196[faust_wrap_sub(i, 2)] + fConst1072 * fRec196[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j393 = 0; j393 < 4; j393 = faust_wrap_add(j393, 1)) {
				fRec196_perm[j393] = fRec196_tmp[faust_wrap_add(vsize, j393)];
			}
			/* Recursive loop 229 */
			/* Pre code */
			for (int j394 = 0; j394 < 4; j394 = faust_wrap_add(j394, 1)) {
				fRec195_tmp[j394] = fRec195_perm[j394];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec195[i] = fConst1068 * (fConst1074 * fRec196[i] + fConst1075 * fRec196[faust_wrap_sub(i, 1)] + fConst1074 * fRec196[faust_wrap_sub(i, 2)]) - fConst1076 * (fConst1077 * fRec195[faust_wrap_sub(i, 2)] + fConst1078 * fRec195[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j395 = 0; j395 < 4; j395 = faust_wrap_add(j395, 1)) {
				fRec195_perm[j395] = fRec195_tmp[faust_wrap_add(vsize, j395)];
			}
			/* Recursive loop 230 */
			/* Pre code */
			for (int j396 = 0; j396 < 4; j396 = faust_wrap_add(j396, 1)) {
				fRec194_tmp[j396] = fRec194_perm[j396];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec194[i] = fConst1076 * (fConst1080 * fRec195[i] + fConst1081 * fRec195[faust_wrap_sub(i, 1)] + fConst1080 * fRec195[faust_wrap_sub(i, 2)]) - fConst1082 * (fConst1083 * fRec194[faust_wrap_sub(i, 2)] + fConst1084 * fRec194[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j397 = 0; j397 < 4; j397 = faust_wrap_add(j397, 1)) {
				fRec194_perm[j397] = fRec194_tmp[faust_wrap_add(vsize, j397)];
			}
			/* Recursive loop 231 */
			/* Pre code */
			for (int j398 = 0; j398 < 4; j398 = faust_wrap_add(j398, 1)) {
				fRec193_tmp[j398] = fRec193_perm[j398];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec193[i] = fSlow1 * fRec193[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1082 * (fConst1086 * fRec194[i] + fConst1087 * fRec194[faust_wrap_sub(i, 1)] + fConst1086 * fRec194[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j399 = 0; j399 < 4; j399 = faust_wrap_add(j399, 1)) {
				fRec193_perm[j399] = fRec193_tmp[faust_wrap_add(vsize, j399)];
			}
			/* Vectorizable loop 232 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec0[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec4[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec11[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec18[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec25[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec32[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec39[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec46[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec53[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec60[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec67[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec74[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec81[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec88[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec95[i]));
				fVbargraph15 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec102[i]));
				fVbargraph16 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec109[i]));
				fVbargraph17 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec116[i]));
				fVbargraph18 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec123[i]));
				fVbargraph19 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec130[i]));
				fVbargraph20 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec137[i]));
				fVbargraph21 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec144[i]));
				fVbargraph22 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec151[i]));
				fVbargraph23 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec158[i]));
				fVbargraph24 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec165[i]));
				fVbargraph25 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec172[i]));
				fVbargraph26 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec179[i]));
				fVbargraph27 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec186[i]));
				fVbargraph28 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec193[i]));
				fVbargraph29 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec200[i]));
				fZec28[i] = static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 233 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec28[i]);
			}
			/* Vectorizable loop 234 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec28[i]);
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
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec10_tmp[j8] = fRec10_perm[j8];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec10[i] = static_cast<double>(input0[i]) - fConst24 * (fConst25 * fRec10[faust_wrap_sub(i, 2)] + fConst26 * fRec10[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec10_perm[j9] = fRec10_tmp[faust_wrap_add(vsize, j9)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec9_tmp[j10] = fRec9_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec9[i] = fConst24 * (fConst28 * fRec10[i] + fConst29 * fRec10[faust_wrap_sub(i, 1)] + fConst28 * fRec10[faust_wrap_sub(i, 2)]) - fConst30 * (fConst31 * fRec9[faust_wrap_sub(i, 2)] + fConst32 * fRec9[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec9_perm[j11] = fRec9_tmp[faust_wrap_add(vsize, j11)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec8_tmp[j12] = fRec8_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec8[i] = fConst30 * (fConst33 * fRec9[i] + fConst34 * fRec9[faust_wrap_sub(i, 1)] + fConst33 * fRec9[faust_wrap_sub(i, 2)]) - fConst35 * (fConst36 * fRec8[faust_wrap_sub(i, 2)] + fConst37 * fRec8[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec8_perm[j13] = fRec8_tmp[faust_wrap_add(vsize, j13)];
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec0[i] = fConst35 * (fConst38 * fRec8[i] + fConst39 * fRec8[faust_wrap_sub(i, 1)] + fConst38 * fRec8[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec7[i] = fZec0[i] - fConst42 * (fConst43 * fRec7[faust_wrap_sub(i, 2)] + fConst46 * fRec7[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec7_perm[j15] = fRec7_tmp[faust_wrap_add(vsize, j15)];
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec6_tmp[j16] = fRec6_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec6[i] = fConst42 * (fConst48 * fRec7[i] + fConst49 * fRec7[faust_wrap_sub(i, 1)] + fConst48 * fRec7[faust_wrap_sub(i, 2)]) - fConst50 * (fConst51 * fRec6[faust_wrap_sub(i, 2)] + fConst52 * fRec6[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec6_perm[j17] = fRec6_tmp[faust_wrap_add(vsize, j17)];
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fRec5_tmp[j18] = fRec5_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec5[i] = fConst50 * (fConst54 * fRec6[i] + fConst55 * fRec6[faust_wrap_sub(i, 1)] + fConst54 * fRec6[faust_wrap_sub(i, 2)]) - fConst56 * (fConst57 * fRec5[faust_wrap_sub(i, 2)] + fConst58 * fRec5[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fRec5_perm[j19] = fRec5_tmp[faust_wrap_add(vsize, j19)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec4_tmp[j20] = fRec4_perm[j20];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec4[i] = fSlow1 * fRec4[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst56 * (fConst60 * fRec5[i] + fConst61 * fRec5[faust_wrap_sub(i, 1)] + fConst60 * fRec5[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec4_perm[j21] = fRec4_tmp[faust_wrap_add(vsize, j21)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				fRec3_tmp[j0] = fRec3_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec3[i] = static_cast<double>(input0[i]) - fConst3 * (fConst4 * fRec3[faust_wrap_sub(i, 2)] + fConst7 * fRec3[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				fRec3_perm[j1] = fRec3_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec2_tmp[j2] = fRec2_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec2[i] = fConst3 * (fConst9 * fRec3[i] + fConst10 * fRec3[faust_wrap_sub(i, 1)] + fConst9 * fRec3[faust_wrap_sub(i, 2)]) - fConst11 * (fConst12 * fRec2[faust_wrap_sub(i, 2)] + fConst13 * fRec2[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec2_perm[j3] = fRec2_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec1_tmp[j4] = fRec1_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec1[i] = fConst11 * (fConst15 * fRec2[i] + fConst16 * fRec2[faust_wrap_sub(i, 1)] + fConst15 * fRec2[faust_wrap_sub(i, 2)]) - fConst17 * (fConst18 * fRec1[faust_wrap_sub(i, 2)] + fConst19 * fRec1[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec1_perm[j5] = fRec1_tmp[faust_wrap_add(vsize, j5)];
			}
			/* Recursive loop 11 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec0_tmp[j6] = fRec0_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec0[i] = fRec0[faust_wrap_sub(i, 1)] * fSlow1 + std::fabs(fConst17 * (fConst22 * fRec1[i] + fConst23 * fRec1[faust_wrap_sub(i, 1)] + fConst22 * fRec1[faust_wrap_sub(i, 2)])) * fSlow2;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec0_perm[j7] = fRec0_tmp[faust_wrap_add(vsize, j7)];
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec17_tmp[j22] = fRec17_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec17[i] = fZec0[i] - fConst62 * (fConst63 * fRec17[faust_wrap_sub(i, 2)] + fConst64 * fRec17[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec17_perm[j23] = fRec17_tmp[faust_wrap_add(vsize, j23)];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec16_tmp[j24] = fRec16_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = fConst62 * (fConst66 * fRec17[i] + fConst67 * fRec17[faust_wrap_sub(i, 1)] + fConst66 * fRec17[faust_wrap_sub(i, 2)]) - fConst68 * (fConst69 * fRec16[faust_wrap_sub(i, 2)] + fConst70 * fRec16[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec16_perm[j25] = fRec16_tmp[faust_wrap_add(vsize, j25)];
			}
			/* Recursive loop 14 */
			/* Pre code */
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec15_tmp[j26] = fRec15_perm[j26];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec15[i] = fConst68 * (fConst71 * fRec16[i] + fConst72 * fRec16[faust_wrap_sub(i, 1)] + fConst71 * fRec16[faust_wrap_sub(i, 2)]) - fConst73 * (fConst74 * fRec15[faust_wrap_sub(i, 2)] + fConst75 * fRec15[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec15_perm[j27] = fRec15_tmp[faust_wrap_add(vsize, j27)];
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec1[i] = fConst73 * (fConst76 * fRec15[i] + fConst77 * fRec15[faust_wrap_sub(i, 1)] + fConst76 * fRec15[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 16 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec24_tmp[j36] = fRec24_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec24[i] = fZec1[i] - fConst100 * (fConst101 * fRec24[faust_wrap_sub(i, 2)] + fConst102 * fRec24[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec24_perm[j37] = fRec24_tmp[faust_wrap_add(vsize, j37)];
			}
			/* Recursive loop 17 */
			/* Pre code */
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec23_tmp[j38] = fRec23_perm[j38];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec23[i] = fConst100 * (fConst104 * fRec24[i] + fConst105 * fRec24[faust_wrap_sub(i, 1)] + fConst104 * fRec24[faust_wrap_sub(i, 2)]) - fConst106 * (fConst107 * fRec23[faust_wrap_sub(i, 2)] + fConst108 * fRec23[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec23_perm[j39] = fRec23_tmp[faust_wrap_add(vsize, j39)];
			}
			/* Recursive loop 18 */
			/* Pre code */
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec22_tmp[j40] = fRec22_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = fConst106 * (fConst109 * fRec23[i] + fConst110 * fRec23[faust_wrap_sub(i, 1)] + fConst109 * fRec23[faust_wrap_sub(i, 2)]) - fConst111 * (fConst112 * fRec22[faust_wrap_sub(i, 2)] + fConst113 * fRec22[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec22_perm[j41] = fRec22_tmp[faust_wrap_add(vsize, j41)];
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec2[i] = fConst111 * (fConst114 * fRec22[i] + fConst115 * fRec22[faust_wrap_sub(i, 1)] + fConst114 * fRec22[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 20 */
			/* Pre code */
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec31_tmp[j50] = fRec31_perm[j50];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec31[i] = fZec2[i] - fConst138 * (fConst139 * fRec31[faust_wrap_sub(i, 2)] + fConst140 * fRec31[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec31_perm[j51] = fRec31_tmp[faust_wrap_add(vsize, j51)];
			}
			/* Recursive loop 21 */
			/* Pre code */
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec30_tmp[j52] = fRec30_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec30[i] = fConst138 * (fConst142 * fRec31[i] + fConst143 * fRec31[faust_wrap_sub(i, 1)] + fConst142 * fRec31[faust_wrap_sub(i, 2)]) - fConst144 * (fConst145 * fRec30[faust_wrap_sub(i, 2)] + fConst146 * fRec30[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec30_perm[j53] = fRec30_tmp[faust_wrap_add(vsize, j53)];
			}
			/* Recursive loop 22 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec29_tmp[j54] = fRec29_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec29[i] = fConst144 * (fConst147 * fRec30[i] + fConst148 * fRec30[faust_wrap_sub(i, 1)] + fConst147 * fRec30[faust_wrap_sub(i, 2)]) - fConst149 * (fConst150 * fRec29[faust_wrap_sub(i, 2)] + fConst151 * fRec29[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec29_perm[j55] = fRec29_tmp[faust_wrap_add(vsize, j55)];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec3[i] = fConst149 * (fConst152 * fRec29[i] + fConst153 * fRec29[faust_wrap_sub(i, 1)] + fConst152 * fRec29[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec38_tmp[j64] = fRec38_perm[j64];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec38[i] = fZec3[i] - fConst176 * (fConst177 * fRec38[faust_wrap_sub(i, 2)] + fConst178 * fRec38[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec38_perm[j65] = fRec38_tmp[faust_wrap_add(vsize, j65)];
			}
			/* Recursive loop 25 */
			/* Pre code */
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec37_tmp[j66] = fRec37_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec37[i] = fConst176 * (fConst180 * fRec38[i] + fConst181 * fRec38[faust_wrap_sub(i, 1)] + fConst180 * fRec38[faust_wrap_sub(i, 2)]) - fConst182 * (fConst183 * fRec37[faust_wrap_sub(i, 2)] + fConst184 * fRec37[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec37_perm[j67] = fRec37_tmp[faust_wrap_add(vsize, j67)];
			}
			/* Recursive loop 26 */
			/* Pre code */
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fRec36_tmp[j68] = fRec36_perm[j68];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec36[i] = fConst182 * (fConst185 * fRec37[i] + fConst186 * fRec37[faust_wrap_sub(i, 1)] + fConst185 * fRec37[faust_wrap_sub(i, 2)]) - fConst187 * (fConst188 * fRec36[faust_wrap_sub(i, 2)] + fConst189 * fRec36[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fRec36_perm[j69] = fRec36_tmp[faust_wrap_add(vsize, j69)];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec4[i] = fConst187 * (fConst190 * fRec36[i] + fConst191 * fRec36[faust_wrap_sub(i, 1)] + fConst190 * fRec36[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec45_tmp[j78] = fRec45_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec45[i] = fZec4[i] - fConst214 * (fConst215 * fRec45[faust_wrap_sub(i, 2)] + fConst216 * fRec45[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec45_perm[j79] = fRec45_tmp[faust_wrap_add(vsize, j79)];
			}
			/* Recursive loop 29 */
			/* Pre code */
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec44_tmp[j80] = fRec44_perm[j80];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec44[i] = fConst214 * (fConst218 * fRec45[i] + fConst219 * fRec45[faust_wrap_sub(i, 1)] + fConst218 * fRec45[faust_wrap_sub(i, 2)]) - fConst220 * (fConst221 * fRec44[faust_wrap_sub(i, 2)] + fConst222 * fRec44[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec44_perm[j81] = fRec44_tmp[faust_wrap_add(vsize, j81)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fRec43_tmp[j82] = fRec43_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec43[i] = fConst220 * (fConst223 * fRec44[i] + fConst224 * fRec44[faust_wrap_sub(i, 1)] + fConst223 * fRec44[faust_wrap_sub(i, 2)]) - fConst225 * (fConst226 * fRec43[faust_wrap_sub(i, 2)] + fConst227 * fRec43[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fRec43_perm[j83] = fRec43_tmp[faust_wrap_add(vsize, j83)];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec5[i] = fConst225 * (fConst228 * fRec43[i] + fConst229 * fRec43[faust_wrap_sub(i, 1)] + fConst228 * fRec43[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec52_tmp[j92] = fRec52_perm[j92];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec52[i] = fZec5[i] - fConst252 * (fConst253 * fRec52[faust_wrap_sub(i, 2)] + fConst254 * fRec52[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec52_perm[j93] = fRec52_tmp[faust_wrap_add(vsize, j93)];
			}
			/* Recursive loop 33 */
			/* Pre code */
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fRec51_tmp[j94] = fRec51_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec51[i] = fConst252 * (fConst256 * fRec52[i] + fConst257 * fRec52[faust_wrap_sub(i, 1)] + fConst256 * fRec52[faust_wrap_sub(i, 2)]) - fConst258 * (fConst259 * fRec51[faust_wrap_sub(i, 2)] + fConst260 * fRec51[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fRec51_perm[j95] = fRec51_tmp[faust_wrap_add(vsize, j95)];
			}
			/* Recursive loop 34 */
			/* Pre code */
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec50_tmp[j96] = fRec50_perm[j96];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec50[i] = fConst258 * (fConst261 * fRec51[i] + fConst262 * fRec51[faust_wrap_sub(i, 1)] + fConst261 * fRec51[faust_wrap_sub(i, 2)]) - fConst263 * (fConst264 * fRec50[faust_wrap_sub(i, 2)] + fConst265 * fRec50[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec50_perm[j97] = fRec50_tmp[faust_wrap_add(vsize, j97)];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec6[i] = fConst263 * (fConst266 * fRec50[i] + fConst267 * fRec50[faust_wrap_sub(i, 1)] + fConst266 * fRec50[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 36 */
			/* Pre code */
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec59_tmp[j106] = fRec59_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec59[i] = fZec6[i] - fConst290 * (fConst291 * fRec59[faust_wrap_sub(i, 2)] + fConst292 * fRec59[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec59_perm[j107] = fRec59_tmp[faust_wrap_add(vsize, j107)];
			}
			/* Recursive loop 37 */
			/* Pre code */
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec58_tmp[j108] = fRec58_perm[j108];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec58[i] = fConst290 * (fConst294 * fRec59[i] + fConst295 * fRec59[faust_wrap_sub(i, 1)] + fConst294 * fRec59[faust_wrap_sub(i, 2)]) - fConst296 * (fConst297 * fRec58[faust_wrap_sub(i, 2)] + fConst298 * fRec58[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec58_perm[j109] = fRec58_tmp[faust_wrap_add(vsize, j109)];
			}
			/* Recursive loop 38 */
			/* Pre code */
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec57_tmp[j110] = fRec57_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec57[i] = fConst296 * (fConst299 * fRec58[i] + fConst300 * fRec58[faust_wrap_sub(i, 1)] + fConst299 * fRec58[faust_wrap_sub(i, 2)]) - fConst301 * (fConst302 * fRec57[faust_wrap_sub(i, 2)] + fConst303 * fRec57[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec57_perm[j111] = fRec57_tmp[faust_wrap_add(vsize, j111)];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec7[i] = fConst301 * (fConst304 * fRec57[i] + fConst305 * fRec57[faust_wrap_sub(i, 1)] + fConst304 * fRec57[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 40 */
			/* Pre code */
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec66_tmp[j120] = fRec66_perm[j120];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec66[i] = fZec7[i] - fConst328 * (fConst329 * fRec66[faust_wrap_sub(i, 2)] + fConst330 * fRec66[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec66_perm[j121] = fRec66_tmp[faust_wrap_add(vsize, j121)];
			}
			/* Recursive loop 41 */
			/* Pre code */
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec65_tmp[j122] = fRec65_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec65[i] = fConst328 * (fConst332 * fRec66[i] + fConst333 * fRec66[faust_wrap_sub(i, 1)] + fConst332 * fRec66[faust_wrap_sub(i, 2)]) - fConst334 * (fConst335 * fRec65[faust_wrap_sub(i, 2)] + fConst336 * fRec65[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec65_perm[j123] = fRec65_tmp[faust_wrap_add(vsize, j123)];
			}
			/* Recursive loop 42 */
			/* Pre code */
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec64_tmp[j124] = fRec64_perm[j124];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec64[i] = fConst334 * (fConst337 * fRec65[i] + fConst338 * fRec65[faust_wrap_sub(i, 1)] + fConst337 * fRec65[faust_wrap_sub(i, 2)]) - fConst339 * (fConst340 * fRec64[faust_wrap_sub(i, 2)] + fConst341 * fRec64[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec64_perm[j125] = fRec64_tmp[faust_wrap_add(vsize, j125)];
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec8[i] = fConst339 * (fConst342 * fRec64[i] + fConst343 * fRec64[faust_wrap_sub(i, 1)] + fConst342 * fRec64[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 44 */
			/* Pre code */
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec73_tmp[j134] = fRec73_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec73[i] = fZec8[i] - fConst366 * (fConst367 * fRec73[faust_wrap_sub(i, 2)] + fConst368 * fRec73[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec73_perm[j135] = fRec73_tmp[faust_wrap_add(vsize, j135)];
			}
			/* Recursive loop 45 */
			/* Pre code */
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec72_tmp[j136] = fRec72_perm[j136];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec72[i] = fConst366 * (fConst370 * fRec73[i] + fConst371 * fRec73[faust_wrap_sub(i, 1)] + fConst370 * fRec73[faust_wrap_sub(i, 2)]) - fConst372 * (fConst373 * fRec72[faust_wrap_sub(i, 2)] + fConst374 * fRec72[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec72_perm[j137] = fRec72_tmp[faust_wrap_add(vsize, j137)];
			}
			/* Recursive loop 46 */
			/* Pre code */
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec71_tmp[j138] = fRec71_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec71[i] = fConst372 * (fConst375 * fRec72[i] + fConst376 * fRec72[faust_wrap_sub(i, 1)] + fConst375 * fRec72[faust_wrap_sub(i, 2)]) - fConst377 * (fConst378 * fRec71[faust_wrap_sub(i, 2)] + fConst379 * fRec71[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec71_perm[j139] = fRec71_tmp[faust_wrap_add(vsize, j139)];
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec9[i] = fConst377 * (fConst380 * fRec71[i] + fConst381 * fRec71[faust_wrap_sub(i, 1)] + fConst380 * fRec71[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 48 */
			/* Pre code */
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec80_tmp[j148] = fRec80_perm[j148];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec80[i] = fZec9[i] - fConst404 * (fConst405 * fRec80[faust_wrap_sub(i, 2)] + fConst406 * fRec80[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec80_perm[j149] = fRec80_tmp[faust_wrap_add(vsize, j149)];
			}
			/* Recursive loop 49 */
			/* Pre code */
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec79_tmp[j150] = fRec79_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec79[i] = fConst404 * (fConst408 * fRec80[i] + fConst409 * fRec80[faust_wrap_sub(i, 1)] + fConst408 * fRec80[faust_wrap_sub(i, 2)]) - fConst410 * (fConst411 * fRec79[faust_wrap_sub(i, 2)] + fConst412 * fRec79[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec79_perm[j151] = fRec79_tmp[faust_wrap_add(vsize, j151)];
			}
			/* Recursive loop 50 */
			/* Pre code */
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec78_tmp[j152] = fRec78_perm[j152];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec78[i] = fConst410 * (fConst413 * fRec79[i] + fConst414 * fRec79[faust_wrap_sub(i, 1)] + fConst413 * fRec79[faust_wrap_sub(i, 2)]) - fConst415 * (fConst416 * fRec78[faust_wrap_sub(i, 2)] + fConst417 * fRec78[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec78_perm[j153] = fRec78_tmp[faust_wrap_add(vsize, j153)];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec10[i] = fConst415 * (fConst418 * fRec78[i] + fConst419 * fRec78[faust_wrap_sub(i, 1)] + fConst418 * fRec78[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 52 */
			/* Pre code */
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec87_tmp[j162] = fRec87_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec87[i] = fZec10[i] - fConst442 * (fConst443 * fRec87[faust_wrap_sub(i, 2)] + fConst444 * fRec87[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec87_perm[j163] = fRec87_tmp[faust_wrap_add(vsize, j163)];
			}
			/* Recursive loop 53 */
			/* Pre code */
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec86_tmp[j164] = fRec86_perm[j164];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec86[i] = fConst442 * (fConst446 * fRec87[i] + fConst447 * fRec87[faust_wrap_sub(i, 1)] + fConst446 * fRec87[faust_wrap_sub(i, 2)]) - fConst448 * (fConst449 * fRec86[faust_wrap_sub(i, 2)] + fConst450 * fRec86[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec86_perm[j165] = fRec86_tmp[faust_wrap_add(vsize, j165)];
			}
			/* Recursive loop 54 */
			/* Pre code */
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec85_tmp[j166] = fRec85_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec85[i] = fConst448 * (fConst451 * fRec86[i] + fConst452 * fRec86[faust_wrap_sub(i, 1)] + fConst451 * fRec86[faust_wrap_sub(i, 2)]) - fConst453 * (fConst454 * fRec85[faust_wrap_sub(i, 2)] + fConst455 * fRec85[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec85_perm[j167] = fRec85_tmp[faust_wrap_add(vsize, j167)];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec11[i] = fConst453 * (fConst456 * fRec85[i] + fConst457 * fRec85[faust_wrap_sub(i, 1)] + fConst456 * fRec85[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 56 */
			/* Pre code */
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec94_tmp[j176] = fRec94_perm[j176];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec94[i] = fZec11[i] - fConst480 * (fConst481 * fRec94[faust_wrap_sub(i, 2)] + fConst482 * fRec94[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec94_perm[j177] = fRec94_tmp[faust_wrap_add(vsize, j177)];
			}
			/* Recursive loop 57 */
			/* Pre code */
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec93_tmp[j178] = fRec93_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec93[i] = fConst480 * (fConst484 * fRec94[i] + fConst485 * fRec94[faust_wrap_sub(i, 1)] + fConst484 * fRec94[faust_wrap_sub(i, 2)]) - fConst486 * (fConst487 * fRec93[faust_wrap_sub(i, 2)] + fConst488 * fRec93[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec93_perm[j179] = fRec93_tmp[faust_wrap_add(vsize, j179)];
			}
			/* Recursive loop 58 */
			/* Pre code */
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec92_tmp[j180] = fRec92_perm[j180];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec92[i] = fConst486 * (fConst489 * fRec93[i] + fConst490 * fRec93[faust_wrap_sub(i, 1)] + fConst489 * fRec93[faust_wrap_sub(i, 2)]) - fConst491 * (fConst492 * fRec92[faust_wrap_sub(i, 2)] + fConst493 * fRec92[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec92_perm[j181] = fRec92_tmp[faust_wrap_add(vsize, j181)];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec12[i] = fConst491 * (fConst494 * fRec92[i] + fConst495 * fRec92[faust_wrap_sub(i, 1)] + fConst494 * fRec92[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 60 */
			/* Pre code */
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec101_tmp[j190] = fRec101_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec101[i] = fZec12[i] - fConst518 * (fConst519 * fRec101[faust_wrap_sub(i, 2)] + fConst520 * fRec101[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec101_perm[j191] = fRec101_tmp[faust_wrap_add(vsize, j191)];
			}
			/* Recursive loop 61 */
			/* Pre code */
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec100_tmp[j192] = fRec100_perm[j192];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec100[i] = fConst518 * (fConst522 * fRec101[i] + fConst523 * fRec101[faust_wrap_sub(i, 1)] + fConst522 * fRec101[faust_wrap_sub(i, 2)]) - fConst524 * (fConst525 * fRec100[faust_wrap_sub(i, 2)] + fConst526 * fRec100[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec100_perm[j193] = fRec100_tmp[faust_wrap_add(vsize, j193)];
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fRec99_tmp[j194] = fRec99_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec99[i] = fConst524 * (fConst527 * fRec100[i] + fConst528 * fRec100[faust_wrap_sub(i, 1)] + fConst527 * fRec100[faust_wrap_sub(i, 2)]) - fConst529 * (fConst530 * fRec99[faust_wrap_sub(i, 2)] + fConst531 * fRec99[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fRec99_perm[j195] = fRec99_tmp[faust_wrap_add(vsize, j195)];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec13[i] = fConst529 * (fConst532 * fRec99[i] + fConst533 * fRec99[faust_wrap_sub(i, 1)] + fConst532 * fRec99[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 64 */
			/* Pre code */
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec108_tmp[j204] = fRec108_perm[j204];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec108[i] = fZec13[i] - fConst556 * (fConst557 * fRec108[faust_wrap_sub(i, 2)] + fConst558 * fRec108[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec108_perm[j205] = fRec108_tmp[faust_wrap_add(vsize, j205)];
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec107_tmp[j206] = fRec107_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec107[i] = fConst556 * (fConst560 * fRec108[i] + fConst561 * fRec108[faust_wrap_sub(i, 1)] + fConst560 * fRec108[faust_wrap_sub(i, 2)]) - fConst562 * (fConst563 * fRec107[faust_wrap_sub(i, 2)] + fConst564 * fRec107[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec107_perm[j207] = fRec107_tmp[faust_wrap_add(vsize, j207)];
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec106_tmp[j208] = fRec106_perm[j208];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec106[i] = fConst562 * (fConst565 * fRec107[i] + fConst566 * fRec107[faust_wrap_sub(i, 1)] + fConst565 * fRec107[faust_wrap_sub(i, 2)]) - fConst567 * (fConst568 * fRec106[faust_wrap_sub(i, 2)] + fConst569 * fRec106[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec106_perm[j209] = fRec106_tmp[faust_wrap_add(vsize, j209)];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec14[i] = fConst567 * (fConst570 * fRec106[i] + fConst571 * fRec106[faust_wrap_sub(i, 1)] + fConst570 * fRec106[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 68 */
			/* Pre code */
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fRec115_tmp[j218] = fRec115_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec115[i] = fZec14[i] - fConst594 * (fConst595 * fRec115[faust_wrap_sub(i, 2)] + fConst596 * fRec115[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fRec115_perm[j219] = fRec115_tmp[faust_wrap_add(vsize, j219)];
			}
			/* Recursive loop 69 */
			/* Pre code */
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec114_tmp[j220] = fRec114_perm[j220];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec114[i] = fConst594 * (fConst598 * fRec115[i] + fConst599 * fRec115[faust_wrap_sub(i, 1)] + fConst598 * fRec115[faust_wrap_sub(i, 2)]) - fConst600 * (fConst601 * fRec114[faust_wrap_sub(i, 2)] + fConst602 * fRec114[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec114_perm[j221] = fRec114_tmp[faust_wrap_add(vsize, j221)];
			}
			/* Recursive loop 70 */
			/* Pre code */
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec113_tmp[j222] = fRec113_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec113[i] = fConst600 * (fConst603 * fRec114[i] + fConst604 * fRec114[faust_wrap_sub(i, 1)] + fConst603 * fRec114[faust_wrap_sub(i, 2)]) - fConst605 * (fConst606 * fRec113[faust_wrap_sub(i, 2)] + fConst607 * fRec113[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec113_perm[j223] = fRec113_tmp[faust_wrap_add(vsize, j223)];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec15[i] = fConst605 * (fConst608 * fRec113[i] + fConst609 * fRec113[faust_wrap_sub(i, 1)] + fConst608 * fRec113[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 72 */
			/* Pre code */
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fRec122_tmp[j232] = fRec122_perm[j232];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec122[i] = fZec15[i] - fConst632 * (fConst633 * fRec122[faust_wrap_sub(i, 2)] + fConst634 * fRec122[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fRec122_perm[j233] = fRec122_tmp[faust_wrap_add(vsize, j233)];
			}
			/* Recursive loop 73 */
			/* Pre code */
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec121_tmp[j234] = fRec121_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec121[i] = fConst632 * (fConst636 * fRec122[i] + fConst637 * fRec122[faust_wrap_sub(i, 1)] + fConst636 * fRec122[faust_wrap_sub(i, 2)]) - fConst638 * (fConst639 * fRec121[faust_wrap_sub(i, 2)] + fConst640 * fRec121[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec121_perm[j235] = fRec121_tmp[faust_wrap_add(vsize, j235)];
			}
			/* Recursive loop 74 */
			/* Pre code */
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec120_tmp[j236] = fRec120_perm[j236];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec120[i] = fConst638 * (fConst641 * fRec121[i] + fConst642 * fRec121[faust_wrap_sub(i, 1)] + fConst641 * fRec121[faust_wrap_sub(i, 2)]) - fConst643 * (fConst644 * fRec120[faust_wrap_sub(i, 2)] + fConst645 * fRec120[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec120_perm[j237] = fRec120_tmp[faust_wrap_add(vsize, j237)];
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec16[i] = fConst643 * (fConst646 * fRec120[i] + fConst647 * fRec120[faust_wrap_sub(i, 1)] + fConst646 * fRec120[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 76 */
			/* Pre code */
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec129_tmp[j246] = fRec129_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec129[i] = fZec16[i] - fConst670 * (fConst671 * fRec129[faust_wrap_sub(i, 2)] + fConst672 * fRec129[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec129_perm[j247] = fRec129_tmp[faust_wrap_add(vsize, j247)];
			}
			/* Recursive loop 77 */
			/* Pre code */
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec128_tmp[j248] = fRec128_perm[j248];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec128[i] = fConst670 * (fConst674 * fRec129[i] + fConst675 * fRec129[faust_wrap_sub(i, 1)] + fConst674 * fRec129[faust_wrap_sub(i, 2)]) - fConst676 * (fConst677 * fRec128[faust_wrap_sub(i, 2)] + fConst678 * fRec128[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec128_perm[j249] = fRec128_tmp[faust_wrap_add(vsize, j249)];
			}
			/* Recursive loop 78 */
			/* Pre code */
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec127_tmp[j250] = fRec127_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec127[i] = fConst676 * (fConst679 * fRec128[i] + fConst680 * fRec128[faust_wrap_sub(i, 1)] + fConst679 * fRec128[faust_wrap_sub(i, 2)]) - fConst681 * (fConst682 * fRec127[faust_wrap_sub(i, 2)] + fConst683 * fRec127[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec127_perm[j251] = fRec127_tmp[faust_wrap_add(vsize, j251)];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec17[i] = fConst681 * (fConst684 * fRec127[i] + fConst685 * fRec127[faust_wrap_sub(i, 1)] + fConst684 * fRec127[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 80 */
			/* Pre code */
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec136_tmp[j260] = fRec136_perm[j260];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec136[i] = fZec17[i] - fConst708 * (fConst709 * fRec136[faust_wrap_sub(i, 2)] + fConst710 * fRec136[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec136_perm[j261] = fRec136_tmp[faust_wrap_add(vsize, j261)];
			}
			/* Recursive loop 81 */
			/* Pre code */
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec135_tmp[j262] = fRec135_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec135[i] = fConst708 * (fConst712 * fRec136[i] + fConst713 * fRec136[faust_wrap_sub(i, 1)] + fConst712 * fRec136[faust_wrap_sub(i, 2)]) - fConst714 * (fConst715 * fRec135[faust_wrap_sub(i, 2)] + fConst716 * fRec135[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec135_perm[j263] = fRec135_tmp[faust_wrap_add(vsize, j263)];
			}
			/* Recursive loop 82 */
			/* Pre code */
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec134_tmp[j264] = fRec134_perm[j264];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec134[i] = fConst714 * (fConst717 * fRec135[i] + fConst718 * fRec135[faust_wrap_sub(i, 1)] + fConst717 * fRec135[faust_wrap_sub(i, 2)]) - fConst719 * (fConst720 * fRec134[faust_wrap_sub(i, 2)] + fConst721 * fRec134[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec134_perm[j265] = fRec134_tmp[faust_wrap_add(vsize, j265)];
			}
			/* Vectorizable loop 83 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec18[i] = fConst719 * (fConst722 * fRec134[i] + fConst723 * fRec134[faust_wrap_sub(i, 1)] + fConst722 * fRec134[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 84 */
			/* Pre code */
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec143_tmp[j274] = fRec143_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec143[i] = fZec18[i] - fConst746 * (fConst747 * fRec143[faust_wrap_sub(i, 2)] + fConst748 * fRec143[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec143_perm[j275] = fRec143_tmp[faust_wrap_add(vsize, j275)];
			}
			/* Recursive loop 85 */
			/* Pre code */
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec142_tmp[j276] = fRec142_perm[j276];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec142[i] = fConst746 * (fConst750 * fRec143[i] + fConst751 * fRec143[faust_wrap_sub(i, 1)] + fConst750 * fRec143[faust_wrap_sub(i, 2)]) - fConst752 * (fConst753 * fRec142[faust_wrap_sub(i, 2)] + fConst754 * fRec142[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec142_perm[j277] = fRec142_tmp[faust_wrap_add(vsize, j277)];
			}
			/* Recursive loop 86 */
			/* Pre code */
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec141_tmp[j278] = fRec141_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec141[i] = fConst752 * (fConst755 * fRec142[i] + fConst756 * fRec142[faust_wrap_sub(i, 1)] + fConst755 * fRec142[faust_wrap_sub(i, 2)]) - fConst757 * (fConst758 * fRec141[faust_wrap_sub(i, 2)] + fConst759 * fRec141[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec141_perm[j279] = fRec141_tmp[faust_wrap_add(vsize, j279)];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec19[i] = fConst757 * (fConst760 * fRec141[i] + fConst761 * fRec141[faust_wrap_sub(i, 1)] + fConst760 * fRec141[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 88 */
			/* Pre code */
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec150_tmp[j288] = fRec150_perm[j288];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec150[i] = fZec19[i] - fConst784 * (fConst785 * fRec150[faust_wrap_sub(i, 2)] + fConst786 * fRec150[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec150_perm[j289] = fRec150_tmp[faust_wrap_add(vsize, j289)];
			}
			/* Recursive loop 89 */
			/* Pre code */
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec149_tmp[j290] = fRec149_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec149[i] = fConst784 * (fConst788 * fRec150[i] + fConst789 * fRec150[faust_wrap_sub(i, 1)] + fConst788 * fRec150[faust_wrap_sub(i, 2)]) - fConst790 * (fConst791 * fRec149[faust_wrap_sub(i, 2)] + fConst792 * fRec149[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec149_perm[j291] = fRec149_tmp[faust_wrap_add(vsize, j291)];
			}
			/* Recursive loop 90 */
			/* Pre code */
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec148_tmp[j292] = fRec148_perm[j292];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec148[i] = fConst790 * (fConst793 * fRec149[i] + fConst794 * fRec149[faust_wrap_sub(i, 1)] + fConst793 * fRec149[faust_wrap_sub(i, 2)]) - fConst795 * (fConst796 * fRec148[faust_wrap_sub(i, 2)] + fConst797 * fRec148[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec148_perm[j293] = fRec148_tmp[faust_wrap_add(vsize, j293)];
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec20[i] = fConst795 * (fConst798 * fRec148[i] + fConst799 * fRec148[faust_wrap_sub(i, 1)] + fConst798 * fRec148[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 92 */
			/* Pre code */
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec157_tmp[j302] = fRec157_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec157[i] = fZec20[i] - fConst822 * (fConst823 * fRec157[faust_wrap_sub(i, 2)] + fConst824 * fRec157[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec157_perm[j303] = fRec157_tmp[faust_wrap_add(vsize, j303)];
			}
			/* Recursive loop 93 */
			/* Pre code */
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec156_tmp[j304] = fRec156_perm[j304];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec156[i] = fConst822 * (fConst826 * fRec157[i] + fConst827 * fRec157[faust_wrap_sub(i, 1)] + fConst826 * fRec157[faust_wrap_sub(i, 2)]) - fConst828 * (fConst829 * fRec156[faust_wrap_sub(i, 2)] + fConst830 * fRec156[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec156_perm[j305] = fRec156_tmp[faust_wrap_add(vsize, j305)];
			}
			/* Recursive loop 94 */
			/* Pre code */
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec155_tmp[j306] = fRec155_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec155[i] = fConst828 * (fConst831 * fRec156[i] + fConst832 * fRec156[faust_wrap_sub(i, 1)] + fConst831 * fRec156[faust_wrap_sub(i, 2)]) - fConst833 * (fConst834 * fRec155[faust_wrap_sub(i, 2)] + fConst835 * fRec155[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec155_perm[j307] = fRec155_tmp[faust_wrap_add(vsize, j307)];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec21[i] = fConst833 * (fConst836 * fRec155[i] + fConst837 * fRec155[faust_wrap_sub(i, 1)] + fConst836 * fRec155[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 96 */
			/* Pre code */
			for (int j316 = 0; j316 < 4; j316 = faust_wrap_add(j316, 1)) {
				fRec164_tmp[j316] = fRec164_perm[j316];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec164[i] = fZec21[i] - fConst860 * (fConst861 * fRec164[faust_wrap_sub(i, 2)] + fConst862 * fRec164[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j317 = 0; j317 < 4; j317 = faust_wrap_add(j317, 1)) {
				fRec164_perm[j317] = fRec164_tmp[faust_wrap_add(vsize, j317)];
			}
			/* Recursive loop 97 */
			/* Pre code */
			for (int j318 = 0; j318 < 4; j318 = faust_wrap_add(j318, 1)) {
				fRec163_tmp[j318] = fRec163_perm[j318];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec163[i] = fConst860 * (fConst864 * fRec164[i] + fConst865 * fRec164[faust_wrap_sub(i, 1)] + fConst864 * fRec164[faust_wrap_sub(i, 2)]) - fConst866 * (fConst867 * fRec163[faust_wrap_sub(i, 2)] + fConst868 * fRec163[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j319 = 0; j319 < 4; j319 = faust_wrap_add(j319, 1)) {
				fRec163_perm[j319] = fRec163_tmp[faust_wrap_add(vsize, j319)];
			}
			/* Recursive loop 98 */
			/* Pre code */
			for (int j320 = 0; j320 < 4; j320 = faust_wrap_add(j320, 1)) {
				fRec162_tmp[j320] = fRec162_perm[j320];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec162[i] = fConst866 * (fConst869 * fRec163[i] + fConst870 * fRec163[faust_wrap_sub(i, 1)] + fConst869 * fRec163[faust_wrap_sub(i, 2)]) - fConst871 * (fConst872 * fRec162[faust_wrap_sub(i, 2)] + fConst873 * fRec162[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j321 = 0; j321 < 4; j321 = faust_wrap_add(j321, 1)) {
				fRec162_perm[j321] = fRec162_tmp[faust_wrap_add(vsize, j321)];
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec22[i] = fConst871 * (fConst874 * fRec162[i] + fConst875 * fRec162[faust_wrap_sub(i, 1)] + fConst874 * fRec162[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 100 */
			/* Pre code */
			for (int j330 = 0; j330 < 4; j330 = faust_wrap_add(j330, 1)) {
				fRec171_tmp[j330] = fRec171_perm[j330];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec171[i] = fZec22[i] - fConst898 * (fConst899 * fRec171[faust_wrap_sub(i, 2)] + fConst900 * fRec171[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j331 = 0; j331 < 4; j331 = faust_wrap_add(j331, 1)) {
				fRec171_perm[j331] = fRec171_tmp[faust_wrap_add(vsize, j331)];
			}
			/* Recursive loop 101 */
			/* Pre code */
			for (int j332 = 0; j332 < 4; j332 = faust_wrap_add(j332, 1)) {
				fRec170_tmp[j332] = fRec170_perm[j332];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec170[i] = fConst898 * (fConst902 * fRec171[i] + fConst903 * fRec171[faust_wrap_sub(i, 1)] + fConst902 * fRec171[faust_wrap_sub(i, 2)]) - fConst904 * (fConst905 * fRec170[faust_wrap_sub(i, 2)] + fConst906 * fRec170[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j333 = 0; j333 < 4; j333 = faust_wrap_add(j333, 1)) {
				fRec170_perm[j333] = fRec170_tmp[faust_wrap_add(vsize, j333)];
			}
			/* Recursive loop 102 */
			/* Pre code */
			for (int j334 = 0; j334 < 4; j334 = faust_wrap_add(j334, 1)) {
				fRec169_tmp[j334] = fRec169_perm[j334];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec169[i] = fConst904 * (fConst907 * fRec170[i] + fConst908 * fRec170[faust_wrap_sub(i, 1)] + fConst907 * fRec170[faust_wrap_sub(i, 2)]) - fConst909 * (fConst910 * fRec169[faust_wrap_sub(i, 2)] + fConst911 * fRec169[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j335 = 0; j335 < 4; j335 = faust_wrap_add(j335, 1)) {
				fRec169_perm[j335] = fRec169_tmp[faust_wrap_add(vsize, j335)];
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec23[i] = fConst909 * (fConst912 * fRec169[i] + fConst913 * fRec169[faust_wrap_sub(i, 1)] + fConst912 * fRec169[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 104 */
			/* Pre code */
			for (int j344 = 0; j344 < 4; j344 = faust_wrap_add(j344, 1)) {
				fRec178_tmp[j344] = fRec178_perm[j344];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec178[i] = fZec23[i] - fConst936 * (fConst937 * fRec178[faust_wrap_sub(i, 2)] + fConst938 * fRec178[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j345 = 0; j345 < 4; j345 = faust_wrap_add(j345, 1)) {
				fRec178_perm[j345] = fRec178_tmp[faust_wrap_add(vsize, j345)];
			}
			/* Recursive loop 105 */
			/* Pre code */
			for (int j346 = 0; j346 < 4; j346 = faust_wrap_add(j346, 1)) {
				fRec177_tmp[j346] = fRec177_perm[j346];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec177[i] = fConst936 * (fConst940 * fRec178[i] + fConst941 * fRec178[faust_wrap_sub(i, 1)] + fConst940 * fRec178[faust_wrap_sub(i, 2)]) - fConst942 * (fConst943 * fRec177[faust_wrap_sub(i, 2)] + fConst944 * fRec177[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j347 = 0; j347 < 4; j347 = faust_wrap_add(j347, 1)) {
				fRec177_perm[j347] = fRec177_tmp[faust_wrap_add(vsize, j347)];
			}
			/* Recursive loop 106 */
			/* Pre code */
			for (int j348 = 0; j348 < 4; j348 = faust_wrap_add(j348, 1)) {
				fRec176_tmp[j348] = fRec176_perm[j348];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec176[i] = fConst942 * (fConst945 * fRec177[i] + fConst946 * fRec177[faust_wrap_sub(i, 1)] + fConst945 * fRec177[faust_wrap_sub(i, 2)]) - fConst947 * (fConst948 * fRec176[faust_wrap_sub(i, 2)] + fConst949 * fRec176[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j349 = 0; j349 < 4; j349 = faust_wrap_add(j349, 1)) {
				fRec176_perm[j349] = fRec176_tmp[faust_wrap_add(vsize, j349)];
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec24[i] = fConst947 * (fConst950 * fRec176[i] + fConst951 * fRec176[faust_wrap_sub(i, 1)] + fConst950 * fRec176[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 108 */
			/* Pre code */
			for (int j358 = 0; j358 < 4; j358 = faust_wrap_add(j358, 1)) {
				fRec185_tmp[j358] = fRec185_perm[j358];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec185[i] = fZec24[i] - fConst974 * (fConst975 * fRec185[faust_wrap_sub(i, 2)] + fConst976 * fRec185[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j359 = 0; j359 < 4; j359 = faust_wrap_add(j359, 1)) {
				fRec185_perm[j359] = fRec185_tmp[faust_wrap_add(vsize, j359)];
			}
			/* Recursive loop 109 */
			/* Pre code */
			for (int j360 = 0; j360 < 4; j360 = faust_wrap_add(j360, 1)) {
				fRec184_tmp[j360] = fRec184_perm[j360];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec184[i] = fConst974 * (fConst978 * fRec185[i] + fConst979 * fRec185[faust_wrap_sub(i, 1)] + fConst978 * fRec185[faust_wrap_sub(i, 2)]) - fConst980 * (fConst981 * fRec184[faust_wrap_sub(i, 2)] + fConst982 * fRec184[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j361 = 0; j361 < 4; j361 = faust_wrap_add(j361, 1)) {
				fRec184_perm[j361] = fRec184_tmp[faust_wrap_add(vsize, j361)];
			}
			/* Recursive loop 110 */
			/* Pre code */
			for (int j362 = 0; j362 < 4; j362 = faust_wrap_add(j362, 1)) {
				fRec183_tmp[j362] = fRec183_perm[j362];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec183[i] = fConst980 * (fConst983 * fRec184[i] + fConst984 * fRec184[faust_wrap_sub(i, 1)] + fConst983 * fRec184[faust_wrap_sub(i, 2)]) - fConst985 * (fConst986 * fRec183[faust_wrap_sub(i, 2)] + fConst987 * fRec183[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j363 = 0; j363 < 4; j363 = faust_wrap_add(j363, 1)) {
				fRec183_perm[j363] = fRec183_tmp[faust_wrap_add(vsize, j363)];
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec25[i] = fConst985 * (fConst988 * fRec183[i] + fConst989 * fRec183[faust_wrap_sub(i, 1)] + fConst988 * fRec183[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 112 */
			/* Pre code */
			for (int j372 = 0; j372 < 4; j372 = faust_wrap_add(j372, 1)) {
				fRec192_tmp[j372] = fRec192_perm[j372];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec192[i] = fZec25[i] - fConst1012 * (fConst1013 * fRec192[faust_wrap_sub(i, 2)] + fConst1014 * fRec192[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j373 = 0; j373 < 4; j373 = faust_wrap_add(j373, 1)) {
				fRec192_perm[j373] = fRec192_tmp[faust_wrap_add(vsize, j373)];
			}
			/* Recursive loop 113 */
			/* Pre code */
			for (int j374 = 0; j374 < 4; j374 = faust_wrap_add(j374, 1)) {
				fRec191_tmp[j374] = fRec191_perm[j374];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec191[i] = fConst1012 * (fConst1016 * fRec192[i] + fConst1017 * fRec192[faust_wrap_sub(i, 1)] + fConst1016 * fRec192[faust_wrap_sub(i, 2)]) - fConst1018 * (fConst1019 * fRec191[faust_wrap_sub(i, 2)] + fConst1020 * fRec191[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j375 = 0; j375 < 4; j375 = faust_wrap_add(j375, 1)) {
				fRec191_perm[j375] = fRec191_tmp[faust_wrap_add(vsize, j375)];
			}
			/* Recursive loop 114 */
			/* Pre code */
			for (int j376 = 0; j376 < 4; j376 = faust_wrap_add(j376, 1)) {
				fRec190_tmp[j376] = fRec190_perm[j376];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec190[i] = fConst1018 * (fConst1021 * fRec191[i] + fConst1022 * fRec191[faust_wrap_sub(i, 1)] + fConst1021 * fRec191[faust_wrap_sub(i, 2)]) - fConst1023 * (fConst1024 * fRec190[faust_wrap_sub(i, 2)] + fConst1025 * fRec190[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j377 = 0; j377 < 4; j377 = faust_wrap_add(j377, 1)) {
				fRec190_perm[j377] = fRec190_tmp[faust_wrap_add(vsize, j377)];
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec26[i] = fConst1023 * (fConst1026 * fRec190[i] + fConst1027 * fRec190[faust_wrap_sub(i, 1)] + fConst1026 * fRec190[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 116 */
			/* Pre code */
			for (int j386 = 0; j386 < 4; j386 = faust_wrap_add(j386, 1)) {
				fRec199_tmp[j386] = fRec199_perm[j386];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec199[i] = fZec26[i] - fConst1050 * (fConst1051 * fRec199[faust_wrap_sub(i, 2)] + fConst1052 * fRec199[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j387 = 0; j387 < 4; j387 = faust_wrap_add(j387, 1)) {
				fRec199_perm[j387] = fRec199_tmp[faust_wrap_add(vsize, j387)];
			}
			/* Recursive loop 117 */
			/* Pre code */
			for (int j388 = 0; j388 < 4; j388 = faust_wrap_add(j388, 1)) {
				fRec198_tmp[j388] = fRec198_perm[j388];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec198[i] = fConst1050 * (fConst1054 * fRec199[i] + fConst1055 * fRec199[faust_wrap_sub(i, 1)] + fConst1054 * fRec199[faust_wrap_sub(i, 2)]) - fConst1056 * (fConst1057 * fRec198[faust_wrap_sub(i, 2)] + fConst1058 * fRec198[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j389 = 0; j389 < 4; j389 = faust_wrap_add(j389, 1)) {
				fRec198_perm[j389] = fRec198_tmp[faust_wrap_add(vsize, j389)];
			}
			/* Recursive loop 118 */
			/* Pre code */
			for (int j390 = 0; j390 < 4; j390 = faust_wrap_add(j390, 1)) {
				fRec197_tmp[j390] = fRec197_perm[j390];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec197[i] = fConst1056 * (fConst1059 * fRec198[i] + fConst1060 * fRec198[faust_wrap_sub(i, 1)] + fConst1059 * fRec198[faust_wrap_sub(i, 2)]) - fConst1061 * (fConst1062 * fRec197[faust_wrap_sub(i, 2)] + fConst1063 * fRec197[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j391 = 0; j391 < 4; j391 = faust_wrap_add(j391, 1)) {
				fRec197_perm[j391] = fRec197_tmp[faust_wrap_add(vsize, j391)];
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec27[i] = fConst1061 * (fConst1064 * fRec197[i] + fConst1065 * fRec197[faust_wrap_sub(i, 1)] + fConst1064 * fRec197[faust_wrap_sub(i, 2)]);
			}
			/* Recursive loop 120 */
			/* Pre code */
			for (int j400 = 0; j400 < 4; j400 = faust_wrap_add(j400, 1)) {
				fRec203_tmp[j400] = fRec203_perm[j400];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec203[i] = fZec27[i] - fConst1088 * (fConst1089 * fRec203[faust_wrap_sub(i, 2)] + fConst1090 * fRec203[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j401 = 0; j401 < 4; j401 = faust_wrap_add(j401, 1)) {
				fRec203_perm[j401] = fRec203_tmp[faust_wrap_add(vsize, j401)];
			}
			/* Recursive loop 121 */
			/* Pre code */
			for (int j402 = 0; j402 < 4; j402 = faust_wrap_add(j402, 1)) {
				fRec202_tmp[j402] = fRec202_perm[j402];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec202[i] = fConst1088 * (fConst1092 * fRec203[i] + fConst1093 * fRec203[faust_wrap_sub(i, 1)] + fConst1092 * fRec203[faust_wrap_sub(i, 2)]) - fConst1094 * (fConst1095 * fRec202[faust_wrap_sub(i, 2)] + fConst1096 * fRec202[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j403 = 0; j403 < 4; j403 = faust_wrap_add(j403, 1)) {
				fRec202_perm[j403] = fRec202_tmp[faust_wrap_add(vsize, j403)];
			}
			/* Recursive loop 122 */
			/* Pre code */
			for (int j404 = 0; j404 < 4; j404 = faust_wrap_add(j404, 1)) {
				fRec201_tmp[j404] = fRec201_perm[j404];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec201[i] = fConst1094 * (fConst1097 * fRec202[i] + fConst1098 * fRec202[faust_wrap_sub(i, 1)] + fConst1097 * fRec202[faust_wrap_sub(i, 2)]) - fConst1099 * (fConst1100 * fRec201[faust_wrap_sub(i, 2)] + fConst1101 * fRec201[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j405 = 0; j405 < 4; j405 = faust_wrap_add(j405, 1)) {
				fRec201_perm[j405] = fRec201_tmp[faust_wrap_add(vsize, j405)];
			}
			/* Recursive loop 123 */
			/* Pre code */
			for (int j406 = 0; j406 < 4; j406 = faust_wrap_add(j406, 1)) {
				fRec200_tmp[j406] = fRec200_perm[j406];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec200[i] = fSlow1 * fRec200[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1099 * (fConst1102 * fRec201[i] + fConst1103 * fRec201[faust_wrap_sub(i, 1)] + fConst1102 * fRec201[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j407 = 0; j407 < 4; j407 = faust_wrap_add(j407, 1)) {
				fRec200_perm[j407] = fRec200_tmp[faust_wrap_add(vsize, j407)];
			}
			/* Recursive loop 124 */
			/* Pre code */
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec14_tmp[j28] = fRec14_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec14[i] = fZec1[i] - fConst80 * (fConst81 * fRec14[faust_wrap_sub(i, 2)] + fConst84 * fRec14[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec14_perm[j29] = fRec14_tmp[faust_wrap_add(vsize, j29)];
			}
			/* Recursive loop 125 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec13_tmp[j30] = fRec13_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec13[i] = fConst80 * (fConst86 * fRec14[i] + fConst87 * fRec14[faust_wrap_sub(i, 1)] + fConst86 * fRec14[faust_wrap_sub(i, 2)]) - fConst88 * (fConst89 * fRec13[faust_wrap_sub(i, 2)] + fConst90 * fRec13[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec13_perm[j31] = fRec13_tmp[faust_wrap_add(vsize, j31)];
			}
			/* Recursive loop 126 */
			/* Pre code */
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fRec12_tmp[j32] = fRec12_perm[j32];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec12[i] = fConst88 * (fConst92 * fRec13[i] + fConst93 * fRec13[faust_wrap_sub(i, 1)] + fConst92 * fRec13[faust_wrap_sub(i, 2)]) - fConst94 * (fConst95 * fRec12[faust_wrap_sub(i, 2)] + fConst96 * fRec12[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fRec12_perm[j33] = fRec12_tmp[faust_wrap_add(vsize, j33)];
			}
			/* Recursive loop 127 */
			/* Pre code */
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec11_tmp[j34] = fRec11_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec11[i] = fSlow1 * fRec11[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst94 * (fConst98 * fRec12[i] + fConst99 * fRec12[faust_wrap_sub(i, 1)] + fConst98 * fRec12[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec11_perm[j35] = fRec11_tmp[faust_wrap_add(vsize, j35)];
			}
			/* Recursive loop 128 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec21_tmp[j42] = fRec21_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec21[i] = fZec2[i] - fConst118 * (fConst119 * fRec21[faust_wrap_sub(i, 2)] + fConst122 * fRec21[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec21_perm[j43] = fRec21_tmp[faust_wrap_add(vsize, j43)];
			}
			/* Recursive loop 129 */
			/* Pre code */
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fRec20_tmp[j44] = fRec20_perm[j44];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec20[i] = fConst118 * (fConst124 * fRec21[i] + fConst125 * fRec21[faust_wrap_sub(i, 1)] + fConst124 * fRec21[faust_wrap_sub(i, 2)]) - fConst126 * (fConst127 * fRec20[faust_wrap_sub(i, 2)] + fConst128 * fRec20[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fRec20_perm[j45] = fRec20_tmp[faust_wrap_add(vsize, j45)];
			}
			/* Recursive loop 130 */
			/* Pre code */
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec19_tmp[j46] = fRec19_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec19[i] = fConst126 * (fConst130 * fRec20[i] + fConst131 * fRec20[faust_wrap_sub(i, 1)] + fConst130 * fRec20[faust_wrap_sub(i, 2)]) - fConst132 * (fConst133 * fRec19[faust_wrap_sub(i, 2)] + fConst134 * fRec19[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec19_perm[j47] = fRec19_tmp[faust_wrap_add(vsize, j47)];
			}
			/* Recursive loop 131 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec18_tmp[j48] = fRec18_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec18[i] = fSlow1 * fRec18[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst132 * (fConst136 * fRec19[i] + fConst137 * fRec19[faust_wrap_sub(i, 1)] + fConst136 * fRec19[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec18_perm[j49] = fRec18_tmp[faust_wrap_add(vsize, j49)];
			}
			/* Recursive loop 132 */
			/* Pre code */
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec28_tmp[j56] = fRec28_perm[j56];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec28[i] = fZec3[i] - fConst156 * (fConst157 * fRec28[faust_wrap_sub(i, 2)] + fConst160 * fRec28[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec28_perm[j57] = fRec28_tmp[faust_wrap_add(vsize, j57)];
			}
			/* Recursive loop 133 */
			/* Pre code */
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec27_tmp[j58] = fRec27_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec27[i] = fConst156 * (fConst162 * fRec28[i] + fConst163 * fRec28[faust_wrap_sub(i, 1)] + fConst162 * fRec28[faust_wrap_sub(i, 2)]) - fConst164 * (fConst165 * fRec27[faust_wrap_sub(i, 2)] + fConst166 * fRec27[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec27_perm[j59] = fRec27_tmp[faust_wrap_add(vsize, j59)];
			}
			/* Recursive loop 134 */
			/* Pre code */
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec26_tmp[j60] = fRec26_perm[j60];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec26[i] = fConst164 * (fConst168 * fRec27[i] + fConst169 * fRec27[faust_wrap_sub(i, 1)] + fConst168 * fRec27[faust_wrap_sub(i, 2)]) - fConst170 * (fConst171 * fRec26[faust_wrap_sub(i, 2)] + fConst172 * fRec26[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec26_perm[j61] = fRec26_tmp[faust_wrap_add(vsize, j61)];
			}
			/* Recursive loop 135 */
			/* Pre code */
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec25_tmp[j62] = fRec25_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec25[i] = fSlow1 * fRec25[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst170 * (fConst174 * fRec26[i] + fConst175 * fRec26[faust_wrap_sub(i, 1)] + fConst174 * fRec26[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec25_perm[j63] = fRec25_tmp[faust_wrap_add(vsize, j63)];
			}
			/* Recursive loop 136 */
			/* Pre code */
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec35_tmp[j70] = fRec35_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec35[i] = fZec4[i] - fConst194 * (fConst195 * fRec35[faust_wrap_sub(i, 2)] + fConst198 * fRec35[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec35_perm[j71] = fRec35_tmp[faust_wrap_add(vsize, j71)];
			}
			/* Recursive loop 137 */
			/* Pre code */
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec34_tmp[j72] = fRec34_perm[j72];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec34[i] = fConst194 * (fConst200 * fRec35[i] + fConst201 * fRec35[faust_wrap_sub(i, 1)] + fConst200 * fRec35[faust_wrap_sub(i, 2)]) - fConst202 * (fConst203 * fRec34[faust_wrap_sub(i, 2)] + fConst204 * fRec34[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec34_perm[j73] = fRec34_tmp[faust_wrap_add(vsize, j73)];
			}
			/* Recursive loop 138 */
			/* Pre code */
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec33_tmp[j74] = fRec33_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec33[i] = fConst202 * (fConst206 * fRec34[i] + fConst207 * fRec34[faust_wrap_sub(i, 1)] + fConst206 * fRec34[faust_wrap_sub(i, 2)]) - fConst208 * (fConst209 * fRec33[faust_wrap_sub(i, 2)] + fConst210 * fRec33[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec33_perm[j75] = fRec33_tmp[faust_wrap_add(vsize, j75)];
			}
			/* Recursive loop 139 */
			/* Pre code */
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec32_tmp[j76] = fRec32_perm[j76];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec32[i] = fSlow1 * fRec32[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst208 * (fConst212 * fRec33[i] + fConst213 * fRec33[faust_wrap_sub(i, 1)] + fConst212 * fRec33[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec32_perm[j77] = fRec32_tmp[faust_wrap_add(vsize, j77)];
			}
			/* Recursive loop 140 */
			/* Pre code */
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec42_tmp[j84] = fRec42_perm[j84];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec42[i] = fZec5[i] - fConst232 * (fConst233 * fRec42[faust_wrap_sub(i, 2)] + fConst236 * fRec42[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec42_perm[j85] = fRec42_tmp[faust_wrap_add(vsize, j85)];
			}
			/* Recursive loop 141 */
			/* Pre code */
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec41_tmp[j86] = fRec41_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec41[i] = fConst232 * (fConst238 * fRec42[i] + fConst239 * fRec42[faust_wrap_sub(i, 1)] + fConst238 * fRec42[faust_wrap_sub(i, 2)]) - fConst240 * (fConst241 * fRec41[faust_wrap_sub(i, 2)] + fConst242 * fRec41[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec41_perm[j87] = fRec41_tmp[faust_wrap_add(vsize, j87)];
			}
			/* Recursive loop 142 */
			/* Pre code */
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec40_tmp[j88] = fRec40_perm[j88];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec40[i] = fConst240 * (fConst244 * fRec41[i] + fConst245 * fRec41[faust_wrap_sub(i, 1)] + fConst244 * fRec41[faust_wrap_sub(i, 2)]) - fConst246 * (fConst247 * fRec40[faust_wrap_sub(i, 2)] + fConst248 * fRec40[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec40_perm[j89] = fRec40_tmp[faust_wrap_add(vsize, j89)];
			}
			/* Recursive loop 143 */
			/* Pre code */
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec39_tmp[j90] = fRec39_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec39[i] = fSlow1 * fRec39[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst246 * (fConst250 * fRec40[i] + fConst251 * fRec40[faust_wrap_sub(i, 1)] + fConst250 * fRec40[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec39_perm[j91] = fRec39_tmp[faust_wrap_add(vsize, j91)];
			}
			/* Recursive loop 144 */
			/* Pre code */
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec49_tmp[j98] = fRec49_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec49[i] = fZec6[i] - fConst270 * (fConst271 * fRec49[faust_wrap_sub(i, 2)] + fConst274 * fRec49[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec49_perm[j99] = fRec49_tmp[faust_wrap_add(vsize, j99)];
			}
			/* Recursive loop 145 */
			/* Pre code */
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec48_tmp[j100] = fRec48_perm[j100];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec48[i] = fConst270 * (fConst276 * fRec49[i] + fConst277 * fRec49[faust_wrap_sub(i, 1)] + fConst276 * fRec49[faust_wrap_sub(i, 2)]) - fConst278 * (fConst279 * fRec48[faust_wrap_sub(i, 2)] + fConst280 * fRec48[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec48_perm[j101] = fRec48_tmp[faust_wrap_add(vsize, j101)];
			}
			/* Recursive loop 146 */
			/* Pre code */
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec47_tmp[j102] = fRec47_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec47[i] = fConst278 * (fConst282 * fRec48[i] + fConst283 * fRec48[faust_wrap_sub(i, 1)] + fConst282 * fRec48[faust_wrap_sub(i, 2)]) - fConst284 * (fConst285 * fRec47[faust_wrap_sub(i, 2)] + fConst286 * fRec47[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec47_perm[j103] = fRec47_tmp[faust_wrap_add(vsize, j103)];
			}
			/* Recursive loop 147 */
			/* Pre code */
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec46_tmp[j104] = fRec46_perm[j104];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec46[i] = fSlow1 * fRec46[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst284 * (fConst288 * fRec47[i] + fConst289 * fRec47[faust_wrap_sub(i, 1)] + fConst288 * fRec47[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec46_perm[j105] = fRec46_tmp[faust_wrap_add(vsize, j105)];
			}
			/* Recursive loop 148 */
			/* Pre code */
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec56_tmp[j112] = fRec56_perm[j112];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec56[i] = fZec7[i] - fConst308 * (fConst309 * fRec56[faust_wrap_sub(i, 2)] + fConst312 * fRec56[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec56_perm[j113] = fRec56_tmp[faust_wrap_add(vsize, j113)];
			}
			/* Recursive loop 149 */
			/* Pre code */
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec55_tmp[j114] = fRec55_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec55[i] = fConst308 * (fConst314 * fRec56[i] + fConst315 * fRec56[faust_wrap_sub(i, 1)] + fConst314 * fRec56[faust_wrap_sub(i, 2)]) - fConst316 * (fConst317 * fRec55[faust_wrap_sub(i, 2)] + fConst318 * fRec55[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec55_perm[j115] = fRec55_tmp[faust_wrap_add(vsize, j115)];
			}
			/* Recursive loop 150 */
			/* Pre code */
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec54_tmp[j116] = fRec54_perm[j116];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec54[i] = fConst316 * (fConst320 * fRec55[i] + fConst321 * fRec55[faust_wrap_sub(i, 1)] + fConst320 * fRec55[faust_wrap_sub(i, 2)]) - fConst322 * (fConst323 * fRec54[faust_wrap_sub(i, 2)] + fConst324 * fRec54[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec54_perm[j117] = fRec54_tmp[faust_wrap_add(vsize, j117)];
			}
			/* Recursive loop 151 */
			/* Pre code */
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fRec53_tmp[j118] = fRec53_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec53[i] = fSlow1 * fRec53[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst322 * (fConst326 * fRec54[i] + fConst327 * fRec54[faust_wrap_sub(i, 1)] + fConst326 * fRec54[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fRec53_perm[j119] = fRec53_tmp[faust_wrap_add(vsize, j119)];
			}
			/* Recursive loop 152 */
			/* Pre code */
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec63_tmp[j126] = fRec63_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec63[i] = fZec8[i] - fConst346 * (fConst347 * fRec63[faust_wrap_sub(i, 2)] + fConst350 * fRec63[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec63_perm[j127] = fRec63_tmp[faust_wrap_add(vsize, j127)];
			}
			/* Recursive loop 153 */
			/* Pre code */
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec62_tmp[j128] = fRec62_perm[j128];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec62[i] = fConst346 * (fConst352 * fRec63[i] + fConst353 * fRec63[faust_wrap_sub(i, 1)] + fConst352 * fRec63[faust_wrap_sub(i, 2)]) - fConst354 * (fConst355 * fRec62[faust_wrap_sub(i, 2)] + fConst356 * fRec62[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec62_perm[j129] = fRec62_tmp[faust_wrap_add(vsize, j129)];
			}
			/* Recursive loop 154 */
			/* Pre code */
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec61_tmp[j130] = fRec61_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec61[i] = fConst354 * (fConst358 * fRec62[i] + fConst359 * fRec62[faust_wrap_sub(i, 1)] + fConst358 * fRec62[faust_wrap_sub(i, 2)]) - fConst360 * (fConst361 * fRec61[faust_wrap_sub(i, 2)] + fConst362 * fRec61[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec61_perm[j131] = fRec61_tmp[faust_wrap_add(vsize, j131)];
			}
			/* Recursive loop 155 */
			/* Pre code */
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fRec60_tmp[j132] = fRec60_perm[j132];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec60[i] = fSlow1 * fRec60[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst360 * (fConst364 * fRec61[i] + fConst365 * fRec61[faust_wrap_sub(i, 1)] + fConst364 * fRec61[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fRec60_perm[j133] = fRec60_tmp[faust_wrap_add(vsize, j133)];
			}
			/* Recursive loop 156 */
			/* Pre code */
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec70_tmp[j140] = fRec70_perm[j140];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec70[i] = fZec9[i] - fConst384 * (fConst385 * fRec70[faust_wrap_sub(i, 2)] + fConst388 * fRec70[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec70_perm[j141] = fRec70_tmp[faust_wrap_add(vsize, j141)];
			}
			/* Recursive loop 157 */
			/* Pre code */
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec69_tmp[j142] = fRec69_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec69[i] = fConst384 * (fConst390 * fRec70[i] + fConst391 * fRec70[faust_wrap_sub(i, 1)] + fConst390 * fRec70[faust_wrap_sub(i, 2)]) - fConst392 * (fConst393 * fRec69[faust_wrap_sub(i, 2)] + fConst394 * fRec69[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec69_perm[j143] = fRec69_tmp[faust_wrap_add(vsize, j143)];
			}
			/* Recursive loop 158 */
			/* Pre code */
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fRec68_tmp[j144] = fRec68_perm[j144];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec68[i] = fConst392 * (fConst396 * fRec69[i] + fConst397 * fRec69[faust_wrap_sub(i, 1)] + fConst396 * fRec69[faust_wrap_sub(i, 2)]) - fConst398 * (fConst399 * fRec68[faust_wrap_sub(i, 2)] + fConst400 * fRec68[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fRec68_perm[j145] = fRec68_tmp[faust_wrap_add(vsize, j145)];
			}
			/* Recursive loop 159 */
			/* Pre code */
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec67_tmp[j146] = fRec67_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec67[i] = fSlow1 * fRec67[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst398 * (fConst402 * fRec68[i] + fConst403 * fRec68[faust_wrap_sub(i, 1)] + fConst402 * fRec68[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec67_perm[j147] = fRec67_tmp[faust_wrap_add(vsize, j147)];
			}
			/* Recursive loop 160 */
			/* Pre code */
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec77_tmp[j154] = fRec77_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec77[i] = fZec10[i] - fConst422 * (fConst423 * fRec77[faust_wrap_sub(i, 2)] + fConst426 * fRec77[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec77_perm[j155] = fRec77_tmp[faust_wrap_add(vsize, j155)];
			}
			/* Recursive loop 161 */
			/* Pre code */
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec76_tmp[j156] = fRec76_perm[j156];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec76[i] = fConst422 * (fConst428 * fRec77[i] + fConst429 * fRec77[faust_wrap_sub(i, 1)] + fConst428 * fRec77[faust_wrap_sub(i, 2)]) - fConst430 * (fConst431 * fRec76[faust_wrap_sub(i, 2)] + fConst432 * fRec76[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec76_perm[j157] = fRec76_tmp[faust_wrap_add(vsize, j157)];
			}
			/* Recursive loop 162 */
			/* Pre code */
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec75_tmp[j158] = fRec75_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec75[i] = fConst430 * (fConst434 * fRec76[i] + fConst435 * fRec76[faust_wrap_sub(i, 1)] + fConst434 * fRec76[faust_wrap_sub(i, 2)]) - fConst436 * (fConst437 * fRec75[faust_wrap_sub(i, 2)] + fConst438 * fRec75[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec75_perm[j159] = fRec75_tmp[faust_wrap_add(vsize, j159)];
			}
			/* Recursive loop 163 */
			/* Pre code */
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec74_tmp[j160] = fRec74_perm[j160];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec74[i] = fSlow1 * fRec74[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst436 * (fConst440 * fRec75[i] + fConst441 * fRec75[faust_wrap_sub(i, 1)] + fConst440 * fRec75[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec74_perm[j161] = fRec74_tmp[faust_wrap_add(vsize, j161)];
			}
			/* Recursive loop 164 */
			/* Pre code */
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fRec84_tmp[j168] = fRec84_perm[j168];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec84[i] = fZec11[i] - fConst460 * (fConst461 * fRec84[faust_wrap_sub(i, 2)] + fConst464 * fRec84[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fRec84_perm[j169] = fRec84_tmp[faust_wrap_add(vsize, j169)];
			}
			/* Recursive loop 165 */
			/* Pre code */
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec83_tmp[j170] = fRec83_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec83[i] = fConst460 * (fConst466 * fRec84[i] + fConst467 * fRec84[faust_wrap_sub(i, 1)] + fConst466 * fRec84[faust_wrap_sub(i, 2)]) - fConst468 * (fConst469 * fRec83[faust_wrap_sub(i, 2)] + fConst470 * fRec83[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec83_perm[j171] = fRec83_tmp[faust_wrap_add(vsize, j171)];
			}
			/* Recursive loop 166 */
			/* Pre code */
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec82_tmp[j172] = fRec82_perm[j172];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec82[i] = fConst468 * (fConst472 * fRec83[i] + fConst473 * fRec83[faust_wrap_sub(i, 1)] + fConst472 * fRec83[faust_wrap_sub(i, 2)]) - fConst474 * (fConst475 * fRec82[faust_wrap_sub(i, 2)] + fConst476 * fRec82[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec82_perm[j173] = fRec82_tmp[faust_wrap_add(vsize, j173)];
			}
			/* Recursive loop 167 */
			/* Pre code */
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec81_tmp[j174] = fRec81_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec81[i] = fSlow1 * fRec81[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst474 * (fConst478 * fRec82[i] + fConst479 * fRec82[faust_wrap_sub(i, 1)] + fConst478 * fRec82[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec81_perm[j175] = fRec81_tmp[faust_wrap_add(vsize, j175)];
			}
			/* Recursive loop 168 */
			/* Pre code */
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fRec91_tmp[j182] = fRec91_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec91[i] = fZec12[i] - fConst498 * (fConst499 * fRec91[faust_wrap_sub(i, 2)] + fConst502 * fRec91[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fRec91_perm[j183] = fRec91_tmp[faust_wrap_add(vsize, j183)];
			}
			/* Recursive loop 169 */
			/* Pre code */
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec90_tmp[j184] = fRec90_perm[j184];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec90[i] = fConst498 * (fConst504 * fRec91[i] + fConst505 * fRec91[faust_wrap_sub(i, 1)] + fConst504 * fRec91[faust_wrap_sub(i, 2)]) - fConst506 * (fConst507 * fRec90[faust_wrap_sub(i, 2)] + fConst508 * fRec90[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec90_perm[j185] = fRec90_tmp[faust_wrap_add(vsize, j185)];
			}
			/* Recursive loop 170 */
			/* Pre code */
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec89_tmp[j186] = fRec89_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec89[i] = fConst506 * (fConst510 * fRec90[i] + fConst511 * fRec90[faust_wrap_sub(i, 1)] + fConst510 * fRec90[faust_wrap_sub(i, 2)]) - fConst512 * (fConst513 * fRec89[faust_wrap_sub(i, 2)] + fConst514 * fRec89[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec89_perm[j187] = fRec89_tmp[faust_wrap_add(vsize, j187)];
			}
			/* Recursive loop 171 */
			/* Pre code */
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec88_tmp[j188] = fRec88_perm[j188];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec88[i] = fSlow1 * fRec88[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst512 * (fConst516 * fRec89[i] + fConst517 * fRec89[faust_wrap_sub(i, 1)] + fConst516 * fRec89[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec88_perm[j189] = fRec88_tmp[faust_wrap_add(vsize, j189)];
			}
			/* Recursive loop 172 */
			/* Pre code */
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec98_tmp[j196] = fRec98_perm[j196];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec98[i] = fZec13[i] - fConst536 * (fConst537 * fRec98[faust_wrap_sub(i, 2)] + fConst540 * fRec98[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec98_perm[j197] = fRec98_tmp[faust_wrap_add(vsize, j197)];
			}
			/* Recursive loop 173 */
			/* Pre code */
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec97_tmp[j198] = fRec97_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec97[i] = fConst536 * (fConst542 * fRec98[i] + fConst543 * fRec98[faust_wrap_sub(i, 1)] + fConst542 * fRec98[faust_wrap_sub(i, 2)]) - fConst544 * (fConst545 * fRec97[faust_wrap_sub(i, 2)] + fConst546 * fRec97[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec97_perm[j199] = fRec97_tmp[faust_wrap_add(vsize, j199)];
			}
			/* Recursive loop 174 */
			/* Pre code */
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec96_tmp[j200] = fRec96_perm[j200];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec96[i] = fConst544 * (fConst548 * fRec97[i] + fConst549 * fRec97[faust_wrap_sub(i, 1)] + fConst548 * fRec97[faust_wrap_sub(i, 2)]) - fConst550 * (fConst551 * fRec96[faust_wrap_sub(i, 2)] + fConst552 * fRec96[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec96_perm[j201] = fRec96_tmp[faust_wrap_add(vsize, j201)];
			}
			/* Recursive loop 175 */
			/* Pre code */
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec95_tmp[j202] = fRec95_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec95[i] = fSlow1 * fRec95[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst550 * (fConst554 * fRec96[i] + fConst555 * fRec96[faust_wrap_sub(i, 1)] + fConst554 * fRec96[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec95_perm[j203] = fRec95_tmp[faust_wrap_add(vsize, j203)];
			}
			/* Recursive loop 176 */
			/* Pre code */
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec105_tmp[j210] = fRec105_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec105[i] = fZec14[i] - fConst574 * (fConst575 * fRec105[faust_wrap_sub(i, 2)] + fConst578 * fRec105[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec105_perm[j211] = fRec105_tmp[faust_wrap_add(vsize, j211)];
			}
			/* Recursive loop 177 */
			/* Pre code */
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec104_tmp[j212] = fRec104_perm[j212];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec104[i] = fConst574 * (fConst580 * fRec105[i] + fConst581 * fRec105[faust_wrap_sub(i, 1)] + fConst580 * fRec105[faust_wrap_sub(i, 2)]) - fConst582 * (fConst583 * fRec104[faust_wrap_sub(i, 2)] + fConst584 * fRec104[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec104_perm[j213] = fRec104_tmp[faust_wrap_add(vsize, j213)];
			}
			/* Recursive loop 178 */
			/* Pre code */
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec103_tmp[j214] = fRec103_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec103[i] = fConst582 * (fConst586 * fRec104[i] + fConst587 * fRec104[faust_wrap_sub(i, 1)] + fConst586 * fRec104[faust_wrap_sub(i, 2)]) - fConst588 * (fConst589 * fRec103[faust_wrap_sub(i, 2)] + fConst590 * fRec103[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec103_perm[j215] = fRec103_tmp[faust_wrap_add(vsize, j215)];
			}
			/* Recursive loop 179 */
			/* Pre code */
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec102_tmp[j216] = fRec102_perm[j216];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec102[i] = fSlow1 * fRec102[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst588 * (fConst592 * fRec103[i] + fConst593 * fRec103[faust_wrap_sub(i, 1)] + fConst592 * fRec103[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec102_perm[j217] = fRec102_tmp[faust_wrap_add(vsize, j217)];
			}
			/* Recursive loop 180 */
			/* Pre code */
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec112_tmp[j224] = fRec112_perm[j224];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec112[i] = fZec15[i] - fConst612 * (fConst613 * fRec112[faust_wrap_sub(i, 2)] + fConst616 * fRec112[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec112_perm[j225] = fRec112_tmp[faust_wrap_add(vsize, j225)];
			}
			/* Recursive loop 181 */
			/* Pre code */
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec111_tmp[j226] = fRec111_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec111[i] = fConst612 * (fConst618 * fRec112[i] + fConst619 * fRec112[faust_wrap_sub(i, 1)] + fConst618 * fRec112[faust_wrap_sub(i, 2)]) - fConst620 * (fConst621 * fRec111[faust_wrap_sub(i, 2)] + fConst622 * fRec111[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec111_perm[j227] = fRec111_tmp[faust_wrap_add(vsize, j227)];
			}
			/* Recursive loop 182 */
			/* Pre code */
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec110_tmp[j228] = fRec110_perm[j228];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec110[i] = fConst620 * (fConst624 * fRec111[i] + fConst625 * fRec111[faust_wrap_sub(i, 1)] + fConst624 * fRec111[faust_wrap_sub(i, 2)]) - fConst626 * (fConst627 * fRec110[faust_wrap_sub(i, 2)] + fConst628 * fRec110[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec110_perm[j229] = fRec110_tmp[faust_wrap_add(vsize, j229)];
			}
			/* Recursive loop 183 */
			/* Pre code */
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec109_tmp[j230] = fRec109_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec109[i] = fSlow1 * fRec109[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst626 * (fConst630 * fRec110[i] + fConst631 * fRec110[faust_wrap_sub(i, 1)] + fConst630 * fRec110[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec109_perm[j231] = fRec109_tmp[faust_wrap_add(vsize, j231)];
			}
			/* Recursive loop 184 */
			/* Pre code */
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec119_tmp[j238] = fRec119_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec119[i] = fZec16[i] - fConst650 * (fConst651 * fRec119[faust_wrap_sub(i, 2)] + fConst654 * fRec119[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec119_perm[j239] = fRec119_tmp[faust_wrap_add(vsize, j239)];
			}
			/* Recursive loop 185 */
			/* Pre code */
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec118_tmp[j240] = fRec118_perm[j240];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec118[i] = fConst650 * (fConst656 * fRec119[i] + fConst657 * fRec119[faust_wrap_sub(i, 1)] + fConst656 * fRec119[faust_wrap_sub(i, 2)]) - fConst658 * (fConst659 * fRec118[faust_wrap_sub(i, 2)] + fConst660 * fRec118[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec118_perm[j241] = fRec118_tmp[faust_wrap_add(vsize, j241)];
			}
			/* Recursive loop 186 */
			/* Pre code */
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec117_tmp[j242] = fRec117_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec117[i] = fConst658 * (fConst662 * fRec118[i] + fConst663 * fRec118[faust_wrap_sub(i, 1)] + fConst662 * fRec118[faust_wrap_sub(i, 2)]) - fConst664 * (fConst665 * fRec117[faust_wrap_sub(i, 2)] + fConst666 * fRec117[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec117_perm[j243] = fRec117_tmp[faust_wrap_add(vsize, j243)];
			}
			/* Recursive loop 187 */
			/* Pre code */
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fRec116_tmp[j244] = fRec116_perm[j244];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec116[i] = fSlow1 * fRec116[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst664 * (fConst668 * fRec117[i] + fConst669 * fRec117[faust_wrap_sub(i, 1)] + fConst668 * fRec117[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fRec116_perm[j245] = fRec116_tmp[faust_wrap_add(vsize, j245)];
			}
			/* Recursive loop 188 */
			/* Pre code */
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec126_tmp[j252] = fRec126_perm[j252];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec126[i] = fZec17[i] - fConst688 * (fConst689 * fRec126[faust_wrap_sub(i, 2)] + fConst692 * fRec126[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec126_perm[j253] = fRec126_tmp[faust_wrap_add(vsize, j253)];
			}
			/* Recursive loop 189 */
			/* Pre code */
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec125_tmp[j254] = fRec125_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec125[i] = fConst688 * (fConst694 * fRec126[i] + fConst695 * fRec126[faust_wrap_sub(i, 1)] + fConst694 * fRec126[faust_wrap_sub(i, 2)]) - fConst696 * (fConst697 * fRec125[faust_wrap_sub(i, 2)] + fConst698 * fRec125[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec125_perm[j255] = fRec125_tmp[faust_wrap_add(vsize, j255)];
			}
			/* Recursive loop 190 */
			/* Pre code */
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec124_tmp[j256] = fRec124_perm[j256];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec124[i] = fConst696 * (fConst700 * fRec125[i] + fConst701 * fRec125[faust_wrap_sub(i, 1)] + fConst700 * fRec125[faust_wrap_sub(i, 2)]) - fConst702 * (fConst703 * fRec124[faust_wrap_sub(i, 2)] + fConst704 * fRec124[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec124_perm[j257] = fRec124_tmp[faust_wrap_add(vsize, j257)];
			}
			/* Recursive loop 191 */
			/* Pre code */
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec123_tmp[j258] = fRec123_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec123[i] = fSlow1 * fRec123[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst702 * (fConst706 * fRec124[i] + fConst707 * fRec124[faust_wrap_sub(i, 1)] + fConst706 * fRec124[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec123_perm[j259] = fRec123_tmp[faust_wrap_add(vsize, j259)];
			}
			/* Recursive loop 192 */
			/* Pre code */
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec133_tmp[j266] = fRec133_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec133[i] = fZec18[i] - fConst726 * (fConst727 * fRec133[faust_wrap_sub(i, 2)] + fConst730 * fRec133[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec133_perm[j267] = fRec133_tmp[faust_wrap_add(vsize, j267)];
			}
			/* Recursive loop 193 */
			/* Pre code */
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fRec132_tmp[j268] = fRec132_perm[j268];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec132[i] = fConst726 * (fConst732 * fRec133[i] + fConst733 * fRec133[faust_wrap_sub(i, 1)] + fConst732 * fRec133[faust_wrap_sub(i, 2)]) - fConst734 * (fConst735 * fRec132[faust_wrap_sub(i, 2)] + fConst736 * fRec132[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fRec132_perm[j269] = fRec132_tmp[faust_wrap_add(vsize, j269)];
			}
			/* Recursive loop 194 */
			/* Pre code */
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec131_tmp[j270] = fRec131_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec131[i] = fConst734 * (fConst738 * fRec132[i] + fConst739 * fRec132[faust_wrap_sub(i, 1)] + fConst738 * fRec132[faust_wrap_sub(i, 2)]) - fConst740 * (fConst741 * fRec131[faust_wrap_sub(i, 2)] + fConst742 * fRec131[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec131_perm[j271] = fRec131_tmp[faust_wrap_add(vsize, j271)];
			}
			/* Recursive loop 195 */
			/* Pre code */
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec130_tmp[j272] = fRec130_perm[j272];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec130[i] = fSlow1 * fRec130[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst740 * (fConst744 * fRec131[i] + fConst745 * fRec131[faust_wrap_sub(i, 1)] + fConst744 * fRec131[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec130_perm[j273] = fRec130_tmp[faust_wrap_add(vsize, j273)];
			}
			/* Recursive loop 196 */
			/* Pre code */
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec140_tmp[j280] = fRec140_perm[j280];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec140[i] = fZec19[i] - fConst764 * (fConst765 * fRec140[faust_wrap_sub(i, 2)] + fConst768 * fRec140[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec140_perm[j281] = fRec140_tmp[faust_wrap_add(vsize, j281)];
			}
			/* Recursive loop 197 */
			/* Pre code */
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fRec139_tmp[j282] = fRec139_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec139[i] = fConst764 * (fConst770 * fRec140[i] + fConst771 * fRec140[faust_wrap_sub(i, 1)] + fConst770 * fRec140[faust_wrap_sub(i, 2)]) - fConst772 * (fConst773 * fRec139[faust_wrap_sub(i, 2)] + fConst774 * fRec139[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fRec139_perm[j283] = fRec139_tmp[faust_wrap_add(vsize, j283)];
			}
			/* Recursive loop 198 */
			/* Pre code */
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec138_tmp[j284] = fRec138_perm[j284];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec138[i] = fConst772 * (fConst776 * fRec139[i] + fConst777 * fRec139[faust_wrap_sub(i, 1)] + fConst776 * fRec139[faust_wrap_sub(i, 2)]) - fConst778 * (fConst779 * fRec138[faust_wrap_sub(i, 2)] + fConst780 * fRec138[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec138_perm[j285] = fRec138_tmp[faust_wrap_add(vsize, j285)];
			}
			/* Recursive loop 199 */
			/* Pre code */
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec137_tmp[j286] = fRec137_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec137[i] = fSlow1 * fRec137[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst778 * (fConst782 * fRec138[i] + fConst783 * fRec138[faust_wrap_sub(i, 1)] + fConst782 * fRec138[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec137_perm[j287] = fRec137_tmp[faust_wrap_add(vsize, j287)];
			}
			/* Recursive loop 200 */
			/* Pre code */
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fRec147_tmp[j294] = fRec147_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec147[i] = fZec20[i] - fConst802 * (fConst803 * fRec147[faust_wrap_sub(i, 2)] + fConst806 * fRec147[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fRec147_perm[j295] = fRec147_tmp[faust_wrap_add(vsize, j295)];
			}
			/* Recursive loop 201 */
			/* Pre code */
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec146_tmp[j296] = fRec146_perm[j296];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec146[i] = fConst802 * (fConst808 * fRec147[i] + fConst809 * fRec147[faust_wrap_sub(i, 1)] + fConst808 * fRec147[faust_wrap_sub(i, 2)]) - fConst810 * (fConst811 * fRec146[faust_wrap_sub(i, 2)] + fConst812 * fRec146[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec146_perm[j297] = fRec146_tmp[faust_wrap_add(vsize, j297)];
			}
			/* Recursive loop 202 */
			/* Pre code */
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec145_tmp[j298] = fRec145_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec145[i] = fConst810 * (fConst814 * fRec146[i] + fConst815 * fRec146[faust_wrap_sub(i, 1)] + fConst814 * fRec146[faust_wrap_sub(i, 2)]) - fConst816 * (fConst817 * fRec145[faust_wrap_sub(i, 2)] + fConst818 * fRec145[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec145_perm[j299] = fRec145_tmp[faust_wrap_add(vsize, j299)];
			}
			/* Recursive loop 203 */
			/* Pre code */
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec144_tmp[j300] = fRec144_perm[j300];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec144[i] = fSlow1 * fRec144[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst816 * (fConst820 * fRec145[i] + fConst821 * fRec145[faust_wrap_sub(i, 1)] + fConst820 * fRec145[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec144_perm[j301] = fRec144_tmp[faust_wrap_add(vsize, j301)];
			}
			/* Recursive loop 204 */
			/* Pre code */
			for (int j308 = 0; j308 < 4; j308 = faust_wrap_add(j308, 1)) {
				fRec154_tmp[j308] = fRec154_perm[j308];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec154[i] = fZec21[i] - fConst840 * (fConst841 * fRec154[faust_wrap_sub(i, 2)] + fConst844 * fRec154[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j309 = 0; j309 < 4; j309 = faust_wrap_add(j309, 1)) {
				fRec154_perm[j309] = fRec154_tmp[faust_wrap_add(vsize, j309)];
			}
			/* Recursive loop 205 */
			/* Pre code */
			for (int j310 = 0; j310 < 4; j310 = faust_wrap_add(j310, 1)) {
				fRec153_tmp[j310] = fRec153_perm[j310];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec153[i] = fConst840 * (fConst846 * fRec154[i] + fConst847 * fRec154[faust_wrap_sub(i, 1)] + fConst846 * fRec154[faust_wrap_sub(i, 2)]) - fConst848 * (fConst849 * fRec153[faust_wrap_sub(i, 2)] + fConst850 * fRec153[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j311 = 0; j311 < 4; j311 = faust_wrap_add(j311, 1)) {
				fRec153_perm[j311] = fRec153_tmp[faust_wrap_add(vsize, j311)];
			}
			/* Recursive loop 206 */
			/* Pre code */
			for (int j312 = 0; j312 < 4; j312 = faust_wrap_add(j312, 1)) {
				fRec152_tmp[j312] = fRec152_perm[j312];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec152[i] = fConst848 * (fConst852 * fRec153[i] + fConst853 * fRec153[faust_wrap_sub(i, 1)] + fConst852 * fRec153[faust_wrap_sub(i, 2)]) - fConst854 * (fConst855 * fRec152[faust_wrap_sub(i, 2)] + fConst856 * fRec152[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j313 = 0; j313 < 4; j313 = faust_wrap_add(j313, 1)) {
				fRec152_perm[j313] = fRec152_tmp[faust_wrap_add(vsize, j313)];
			}
			/* Recursive loop 207 */
			/* Pre code */
			for (int j314 = 0; j314 < 4; j314 = faust_wrap_add(j314, 1)) {
				fRec151_tmp[j314] = fRec151_perm[j314];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec151[i] = fSlow1 * fRec151[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst854 * (fConst858 * fRec152[i] + fConst859 * fRec152[faust_wrap_sub(i, 1)] + fConst858 * fRec152[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j315 = 0; j315 < 4; j315 = faust_wrap_add(j315, 1)) {
				fRec151_perm[j315] = fRec151_tmp[faust_wrap_add(vsize, j315)];
			}
			/* Recursive loop 208 */
			/* Pre code */
			for (int j322 = 0; j322 < 4; j322 = faust_wrap_add(j322, 1)) {
				fRec161_tmp[j322] = fRec161_perm[j322];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec161[i] = fZec22[i] - fConst878 * (fConst879 * fRec161[faust_wrap_sub(i, 2)] + fConst882 * fRec161[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j323 = 0; j323 < 4; j323 = faust_wrap_add(j323, 1)) {
				fRec161_perm[j323] = fRec161_tmp[faust_wrap_add(vsize, j323)];
			}
			/* Recursive loop 209 */
			/* Pre code */
			for (int j324 = 0; j324 < 4; j324 = faust_wrap_add(j324, 1)) {
				fRec160_tmp[j324] = fRec160_perm[j324];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec160[i] = fConst878 * (fConst884 * fRec161[i] + fConst885 * fRec161[faust_wrap_sub(i, 1)] + fConst884 * fRec161[faust_wrap_sub(i, 2)]) - fConst886 * (fConst887 * fRec160[faust_wrap_sub(i, 2)] + fConst888 * fRec160[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j325 = 0; j325 < 4; j325 = faust_wrap_add(j325, 1)) {
				fRec160_perm[j325] = fRec160_tmp[faust_wrap_add(vsize, j325)];
			}
			/* Recursive loop 210 */
			/* Pre code */
			for (int j326 = 0; j326 < 4; j326 = faust_wrap_add(j326, 1)) {
				fRec159_tmp[j326] = fRec159_perm[j326];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec159[i] = fConst886 * (fConst890 * fRec160[i] + fConst891 * fRec160[faust_wrap_sub(i, 1)] + fConst890 * fRec160[faust_wrap_sub(i, 2)]) - fConst892 * (fConst893 * fRec159[faust_wrap_sub(i, 2)] + fConst894 * fRec159[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j327 = 0; j327 < 4; j327 = faust_wrap_add(j327, 1)) {
				fRec159_perm[j327] = fRec159_tmp[faust_wrap_add(vsize, j327)];
			}
			/* Recursive loop 211 */
			/* Pre code */
			for (int j328 = 0; j328 < 4; j328 = faust_wrap_add(j328, 1)) {
				fRec158_tmp[j328] = fRec158_perm[j328];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec158[i] = fSlow1 * fRec158[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst892 * (fConst896 * fRec159[i] + fConst897 * fRec159[faust_wrap_sub(i, 1)] + fConst896 * fRec159[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j329 = 0; j329 < 4; j329 = faust_wrap_add(j329, 1)) {
				fRec158_perm[j329] = fRec158_tmp[faust_wrap_add(vsize, j329)];
			}
			/* Recursive loop 212 */
			/* Pre code */
			for (int j336 = 0; j336 < 4; j336 = faust_wrap_add(j336, 1)) {
				fRec168_tmp[j336] = fRec168_perm[j336];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec168[i] = fZec23[i] - fConst916 * (fConst917 * fRec168[faust_wrap_sub(i, 2)] + fConst920 * fRec168[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j337 = 0; j337 < 4; j337 = faust_wrap_add(j337, 1)) {
				fRec168_perm[j337] = fRec168_tmp[faust_wrap_add(vsize, j337)];
			}
			/* Recursive loop 213 */
			/* Pre code */
			for (int j338 = 0; j338 < 4; j338 = faust_wrap_add(j338, 1)) {
				fRec167_tmp[j338] = fRec167_perm[j338];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec167[i] = fConst916 * (fConst922 * fRec168[i] + fConst923 * fRec168[faust_wrap_sub(i, 1)] + fConst922 * fRec168[faust_wrap_sub(i, 2)]) - fConst924 * (fConst925 * fRec167[faust_wrap_sub(i, 2)] + fConst926 * fRec167[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j339 = 0; j339 < 4; j339 = faust_wrap_add(j339, 1)) {
				fRec167_perm[j339] = fRec167_tmp[faust_wrap_add(vsize, j339)];
			}
			/* Recursive loop 214 */
			/* Pre code */
			for (int j340 = 0; j340 < 4; j340 = faust_wrap_add(j340, 1)) {
				fRec166_tmp[j340] = fRec166_perm[j340];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec166[i] = fConst924 * (fConst928 * fRec167[i] + fConst929 * fRec167[faust_wrap_sub(i, 1)] + fConst928 * fRec167[faust_wrap_sub(i, 2)]) - fConst930 * (fConst931 * fRec166[faust_wrap_sub(i, 2)] + fConst932 * fRec166[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j341 = 0; j341 < 4; j341 = faust_wrap_add(j341, 1)) {
				fRec166_perm[j341] = fRec166_tmp[faust_wrap_add(vsize, j341)];
			}
			/* Recursive loop 215 */
			/* Pre code */
			for (int j342 = 0; j342 < 4; j342 = faust_wrap_add(j342, 1)) {
				fRec165_tmp[j342] = fRec165_perm[j342];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec165[i] = fSlow1 * fRec165[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst930 * (fConst934 * fRec166[i] + fConst935 * fRec166[faust_wrap_sub(i, 1)] + fConst934 * fRec166[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j343 = 0; j343 < 4; j343 = faust_wrap_add(j343, 1)) {
				fRec165_perm[j343] = fRec165_tmp[faust_wrap_add(vsize, j343)];
			}
			/* Recursive loop 216 */
			/* Pre code */
			for (int j350 = 0; j350 < 4; j350 = faust_wrap_add(j350, 1)) {
				fRec175_tmp[j350] = fRec175_perm[j350];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec175[i] = fZec24[i] - fConst954 * (fConst955 * fRec175[faust_wrap_sub(i, 2)] + fConst958 * fRec175[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j351 = 0; j351 < 4; j351 = faust_wrap_add(j351, 1)) {
				fRec175_perm[j351] = fRec175_tmp[faust_wrap_add(vsize, j351)];
			}
			/* Recursive loop 217 */
			/* Pre code */
			for (int j352 = 0; j352 < 4; j352 = faust_wrap_add(j352, 1)) {
				fRec174_tmp[j352] = fRec174_perm[j352];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec174[i] = fConst954 * (fConst960 * fRec175[i] + fConst961 * fRec175[faust_wrap_sub(i, 1)] + fConst960 * fRec175[faust_wrap_sub(i, 2)]) - fConst962 * (fConst963 * fRec174[faust_wrap_sub(i, 2)] + fConst964 * fRec174[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j353 = 0; j353 < 4; j353 = faust_wrap_add(j353, 1)) {
				fRec174_perm[j353] = fRec174_tmp[faust_wrap_add(vsize, j353)];
			}
			/* Recursive loop 218 */
			/* Pre code */
			for (int j354 = 0; j354 < 4; j354 = faust_wrap_add(j354, 1)) {
				fRec173_tmp[j354] = fRec173_perm[j354];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec173[i] = fConst962 * (fConst966 * fRec174[i] + fConst967 * fRec174[faust_wrap_sub(i, 1)] + fConst966 * fRec174[faust_wrap_sub(i, 2)]) - fConst968 * (fConst969 * fRec173[faust_wrap_sub(i, 2)] + fConst970 * fRec173[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j355 = 0; j355 < 4; j355 = faust_wrap_add(j355, 1)) {
				fRec173_perm[j355] = fRec173_tmp[faust_wrap_add(vsize, j355)];
			}
			/* Recursive loop 219 */
			/* Pre code */
			for (int j356 = 0; j356 < 4; j356 = faust_wrap_add(j356, 1)) {
				fRec172_tmp[j356] = fRec172_perm[j356];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec172[i] = fSlow1 * fRec172[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst968 * (fConst972 * fRec173[i] + fConst973 * fRec173[faust_wrap_sub(i, 1)] + fConst972 * fRec173[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j357 = 0; j357 < 4; j357 = faust_wrap_add(j357, 1)) {
				fRec172_perm[j357] = fRec172_tmp[faust_wrap_add(vsize, j357)];
			}
			/* Recursive loop 220 */
			/* Pre code */
			for (int j364 = 0; j364 < 4; j364 = faust_wrap_add(j364, 1)) {
				fRec182_tmp[j364] = fRec182_perm[j364];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec182[i] = fZec25[i] - fConst992 * (fConst993 * fRec182[faust_wrap_sub(i, 2)] + fConst996 * fRec182[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j365 = 0; j365 < 4; j365 = faust_wrap_add(j365, 1)) {
				fRec182_perm[j365] = fRec182_tmp[faust_wrap_add(vsize, j365)];
			}
			/* Recursive loop 221 */
			/* Pre code */
			for (int j366 = 0; j366 < 4; j366 = faust_wrap_add(j366, 1)) {
				fRec181_tmp[j366] = fRec181_perm[j366];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec181[i] = fConst992 * (fConst998 * fRec182[i] + fConst999 * fRec182[faust_wrap_sub(i, 1)] + fConst998 * fRec182[faust_wrap_sub(i, 2)]) - fConst1000 * (fConst1001 * fRec181[faust_wrap_sub(i, 2)] + fConst1002 * fRec181[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j367 = 0; j367 < 4; j367 = faust_wrap_add(j367, 1)) {
				fRec181_perm[j367] = fRec181_tmp[faust_wrap_add(vsize, j367)];
			}
			/* Recursive loop 222 */
			/* Pre code */
			for (int j368 = 0; j368 < 4; j368 = faust_wrap_add(j368, 1)) {
				fRec180_tmp[j368] = fRec180_perm[j368];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec180[i] = fConst1000 * (fConst1004 * fRec181[i] + fConst1005 * fRec181[faust_wrap_sub(i, 1)] + fConst1004 * fRec181[faust_wrap_sub(i, 2)]) - fConst1006 * (fConst1007 * fRec180[faust_wrap_sub(i, 2)] + fConst1008 * fRec180[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j369 = 0; j369 < 4; j369 = faust_wrap_add(j369, 1)) {
				fRec180_perm[j369] = fRec180_tmp[faust_wrap_add(vsize, j369)];
			}
			/* Recursive loop 223 */
			/* Pre code */
			for (int j370 = 0; j370 < 4; j370 = faust_wrap_add(j370, 1)) {
				fRec179_tmp[j370] = fRec179_perm[j370];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec179[i] = fSlow1 * fRec179[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1006 * (fConst1010 * fRec180[i] + fConst1011 * fRec180[faust_wrap_sub(i, 1)] + fConst1010 * fRec180[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j371 = 0; j371 < 4; j371 = faust_wrap_add(j371, 1)) {
				fRec179_perm[j371] = fRec179_tmp[faust_wrap_add(vsize, j371)];
			}
			/* Recursive loop 224 */
			/* Pre code */
			for (int j378 = 0; j378 < 4; j378 = faust_wrap_add(j378, 1)) {
				fRec189_tmp[j378] = fRec189_perm[j378];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec189[i] = fZec26[i] - fConst1030 * (fConst1031 * fRec189[faust_wrap_sub(i, 2)] + fConst1034 * fRec189[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j379 = 0; j379 < 4; j379 = faust_wrap_add(j379, 1)) {
				fRec189_perm[j379] = fRec189_tmp[faust_wrap_add(vsize, j379)];
			}
			/* Recursive loop 225 */
			/* Pre code */
			for (int j380 = 0; j380 < 4; j380 = faust_wrap_add(j380, 1)) {
				fRec188_tmp[j380] = fRec188_perm[j380];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec188[i] = fConst1030 * (fConst1036 * fRec189[i] + fConst1037 * fRec189[faust_wrap_sub(i, 1)] + fConst1036 * fRec189[faust_wrap_sub(i, 2)]) - fConst1038 * (fConst1039 * fRec188[faust_wrap_sub(i, 2)] + fConst1040 * fRec188[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j381 = 0; j381 < 4; j381 = faust_wrap_add(j381, 1)) {
				fRec188_perm[j381] = fRec188_tmp[faust_wrap_add(vsize, j381)];
			}
			/* Recursive loop 226 */
			/* Pre code */
			for (int j382 = 0; j382 < 4; j382 = faust_wrap_add(j382, 1)) {
				fRec187_tmp[j382] = fRec187_perm[j382];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec187[i] = fConst1038 * (fConst1042 * fRec188[i] + fConst1043 * fRec188[faust_wrap_sub(i, 1)] + fConst1042 * fRec188[faust_wrap_sub(i, 2)]) - fConst1044 * (fConst1045 * fRec187[faust_wrap_sub(i, 2)] + fConst1046 * fRec187[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j383 = 0; j383 < 4; j383 = faust_wrap_add(j383, 1)) {
				fRec187_perm[j383] = fRec187_tmp[faust_wrap_add(vsize, j383)];
			}
			/* Recursive loop 227 */
			/* Pre code */
			for (int j384 = 0; j384 < 4; j384 = faust_wrap_add(j384, 1)) {
				fRec186_tmp[j384] = fRec186_perm[j384];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec186[i] = fSlow1 * fRec186[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1044 * (fConst1048 * fRec187[i] + fConst1049 * fRec187[faust_wrap_sub(i, 1)] + fConst1048 * fRec187[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j385 = 0; j385 < 4; j385 = faust_wrap_add(j385, 1)) {
				fRec186_perm[j385] = fRec186_tmp[faust_wrap_add(vsize, j385)];
			}
			/* Recursive loop 228 */
			/* Pre code */
			for (int j392 = 0; j392 < 4; j392 = faust_wrap_add(j392, 1)) {
				fRec196_tmp[j392] = fRec196_perm[j392];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec196[i] = fZec27[i] - fConst1068 * (fConst1069 * fRec196[faust_wrap_sub(i, 2)] + fConst1072 * fRec196[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j393 = 0; j393 < 4; j393 = faust_wrap_add(j393, 1)) {
				fRec196_perm[j393] = fRec196_tmp[faust_wrap_add(vsize, j393)];
			}
			/* Recursive loop 229 */
			/* Pre code */
			for (int j394 = 0; j394 < 4; j394 = faust_wrap_add(j394, 1)) {
				fRec195_tmp[j394] = fRec195_perm[j394];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec195[i] = fConst1068 * (fConst1074 * fRec196[i] + fConst1075 * fRec196[faust_wrap_sub(i, 1)] + fConst1074 * fRec196[faust_wrap_sub(i, 2)]) - fConst1076 * (fConst1077 * fRec195[faust_wrap_sub(i, 2)] + fConst1078 * fRec195[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j395 = 0; j395 < 4; j395 = faust_wrap_add(j395, 1)) {
				fRec195_perm[j395] = fRec195_tmp[faust_wrap_add(vsize, j395)];
			}
			/* Recursive loop 230 */
			/* Pre code */
			for (int j396 = 0; j396 < 4; j396 = faust_wrap_add(j396, 1)) {
				fRec194_tmp[j396] = fRec194_perm[j396];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec194[i] = fConst1076 * (fConst1080 * fRec195[i] + fConst1081 * fRec195[faust_wrap_sub(i, 1)] + fConst1080 * fRec195[faust_wrap_sub(i, 2)]) - fConst1082 * (fConst1083 * fRec194[faust_wrap_sub(i, 2)] + fConst1084 * fRec194[faust_wrap_sub(i, 1)]);
			}
			/* Post code */
			for (int j397 = 0; j397 < 4; j397 = faust_wrap_add(j397, 1)) {
				fRec194_perm[j397] = fRec194_tmp[faust_wrap_add(vsize, j397)];
			}
			/* Recursive loop 231 */
			/* Pre code */
			for (int j398 = 0; j398 < 4; j398 = faust_wrap_add(j398, 1)) {
				fRec193_tmp[j398] = fRec193_perm[j398];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec193[i] = fSlow1 * fRec193[faust_wrap_sub(i, 1)] + fSlow2 * std::fabs(fConst1082 * (fConst1086 * fRec194[i] + fConst1087 * fRec194[faust_wrap_sub(i, 1)] + fConst1086 * fRec194[faust_wrap_sub(i, 2)]));
			}
			/* Post code */
			for (int j399 = 0; j399 < 4; j399 = faust_wrap_add(j399, 1)) {
				fRec193_perm[j399] = fRec193_tmp[faust_wrap_add(vsize, j399)];
			}
			/* Vectorizable loop 232 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVbargraph0 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec0[i]));
				fVbargraph1 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec4[i]));
				fVbargraph2 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec11[i]));
				fVbargraph3 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec18[i]));
				fVbargraph4 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec25[i]));
				fVbargraph5 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec32[i]));
				fVbargraph6 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec39[i]));
				fVbargraph7 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec46[i]));
				fVbargraph8 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec53[i]));
				fVbargraph9 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec60[i]));
				fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec67[i]));
				fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec74[i]));
				fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec81[i]));
				fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec88[i]));
				fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec95[i]));
				fVbargraph15 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec102[i]));
				fVbargraph16 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec109[i]));
				fVbargraph17 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec116[i]));
				fVbargraph18 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec123[i]));
				fVbargraph19 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec130[i]));
				fVbargraph20 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec137[i]));
				fVbargraph21 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec144[i]));
				fVbargraph22 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec151[i]));
				fVbargraph23 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec158[i]));
				fVbargraph24 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec165[i]));
				fVbargraph25 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec172[i]));
				fVbargraph26 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec179[i]));
				fVbargraph27 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec186[i]));
				fVbargraph28 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec193[i]));
				fVbargraph29 = static_cast<FAUSTFLOAT>(fSlow3 + 2e+01 * std::log10(fRec200[i]));
				fZec28[i] = static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 233 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fZec28[i]);
			}
			/* Vectorizable loop 234 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fZec28[i]);
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
