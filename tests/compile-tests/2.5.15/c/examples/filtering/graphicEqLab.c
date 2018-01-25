/* ------------------------------------------------------------
name: "graphicEqLab"
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
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	FAUSTFLOAT fVslider0;
	float fRec15[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fEntry0;
	float fConst24;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec17[2];
	float fVec1[2];
	float fRec16[2];
	float fConst25;
	float fVec2[2];
	float fConst26;
	float fVec3[2];
	float fVec4[2];
	float fConst27;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec18[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec19[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox3;
	int iRec20[2];
	float fRec21[4];
	float fVec22[2];
	float fConst28;
	float fRec14[2];
	float fConst29;
	float fConst30;
	float fRec13[3];
	float fConst31;
	float fRec12[3];
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec11[3];
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec10[3];
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec9[3];
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec8[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec7[3];
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec6[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec5[3];
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec4[3];
	FAUSTFLOAT fVslider5;
	float fRec22[2];
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec35[2];
	float fRec34[3];
	float fRec33[3];
	float fVec23[2];
	float fConst87;
	float fRec32[2];
	float fConst88;
	float fRec31[3];
	float fConst89;
	float fRec30[3];
	float fRec29[3];
	float fRec28[3];
	float fRec27[3];
	float fRec26[3];
	float fRec25[3];
	float fRec24[3];
	float fRec23[3];
	FAUSTFLOAT fVslider6;
	float fRec36[2];
	float fConst90;
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec48[2];
	float fRec47[3];
	float fRec46[3];
	float fVec24[2];
	float fConst97;
	float fRec45[2];
	float fConst98;
	float fRec44[3];
	float fConst99;
	float fRec43[3];
	float fRec42[3];
	float fRec41[3];
	float fRec40[3];
	float fRec39[3];
	float fRec38[3];
	float fRec37[3];
	FAUSTFLOAT fVslider7;
	float fRec49[2];
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec60[2];
	float fRec59[3];
	float fRec58[3];
	float fVec25[2];
	float fConst107;
	float fRec57[2];
	float fConst108;
	float fRec56[3];
	float fConst109;
	float fRec55[3];
	float fRec54[3];
	float fRec53[3];
	float fRec52[3];
	float fRec51[3];
	float fRec50[3];
	FAUSTFLOAT fVslider8;
	float fRec61[2];
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fRec71[2];
	float fRec70[3];
	float fRec69[3];
	float fVec26[2];
	float fConst117;
	float fRec68[2];
	float fConst118;
	float fRec67[3];
	float fConst119;
	float fRec66[3];
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	FAUSTFLOAT fVslider9;
	float fRec72[2];
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec81[2];
	float fRec80[3];
	float fRec79[3];
	float fVec27[2];
	float fConst127;
	float fRec78[2];
	float fConst128;
	float fRec77[3];
	float fConst129;
	float fRec76[3];
	float fRec75[3];
	float fRec74[3];
	float fRec73[3];
	FAUSTFLOAT fVslider10;
	float fRec82[2];
	float fConst130;
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec90[2];
	float fRec89[3];
	float fRec88[3];
	float fVec28[2];
	float fConst137;
	float fRec87[2];
	float fConst138;
	float fRec86[3];
	float fConst139;
	float fRec85[3];
	float fRec84[3];
	float fRec83[3];
	FAUSTFLOAT fVslider11;
	float fRec91[2];
	float fConst140;
	float fConst141;
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec98[2];
	float fRec97[3];
	float fRec96[3];
	float fVec29[2];
	float fConst147;
	float fRec95[2];
	float fConst148;
	float fRec94[3];
	float fConst149;
	float fRec93[3];
	float fRec92[3];
	FAUSTFLOAT fVslider12;
	float fRec99[2];
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec105[2];
	float fRec104[3];
	float fRec103[3];
	float fVec30[2];
	float fConst156;
	float fRec102[2];
	float fConst157;
	float fRec101[3];
	float fConst158;
	float fRec100[3];
	FAUSTFLOAT fVslider13;
	float fRec106[2];
	float fRec109[2];
	float fRec108[3];
	float fRec107[3];
	FAUSTFLOAT fVslider14;
	float fRec110[2];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec3[3];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec2[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec1[3];
	float fConst168;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst169;
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
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
	float fRec117[3];
	float fConst190;
	float fConst191;
	float fConst192;
	float fRec116[3];
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec115[3];
	float fConst196;
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec114[3];
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec113[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec112[3];
	float fConst206;
	float fRec111[2];
	FAUSTFLOAT fVbargraph1;
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fConst212;
	float fConst213;
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
	float fRec124[3];
	float fConst228;
	float fConst229;
	float fConst230;
	float fRec123[3];
	float fConst231;
	float fConst232;
	float fConst233;
	float fRec122[3];
	float fConst234;
	float fConst235;
	float fConst236;
	float fConst237;
	float fRec121[3];
	float fConst238;
	float fConst239;
	float fConst240;
	float fRec120[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fRec119[3];
	float fConst244;
	float fRec118[2];
	FAUSTFLOAT fVbargraph2;
	float fConst245;
	float fConst246;
	float fConst247;
	float fConst248;
	float fConst249;
	float fConst250;
	float fConst251;
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
	float fRec131[3];
	float fConst266;
	float fConst267;
	float fConst268;
	float fRec130[3];
	float fConst269;
	float fConst270;
	float fConst271;
	float fRec129[3];
	float fConst272;
	float fConst273;
	float fConst274;
	float fConst275;
	float fRec128[3];
	float fConst276;
	float fConst277;
	float fConst278;
	float fRec127[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fRec126[3];
	float fConst282;
	float fRec125[2];
	FAUSTFLOAT fVbargraph3;
	float fConst283;
	float fConst284;
	float fConst285;
	float fConst286;
	float fConst287;
	float fConst288;
	float fConst289;
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
	float fRec138[3];
	float fConst304;
	float fConst305;
	float fConst306;
	float fRec137[3];
	float fConst307;
	float fConst308;
	float fConst309;
	float fRec136[3];
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fRec135[3];
	float fConst314;
	float fConst315;
	float fConst316;
	float fRec134[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fRec133[3];
	float fConst320;
	float fRec132[2];
	FAUSTFLOAT fVbargraph4;
	float fConst321;
	float fConst322;
	float fConst323;
	float fConst324;
	float fConst325;
	float fConst326;
	float fConst327;
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
	float fRec145[3];
	float fConst342;
	float fConst343;
	float fConst344;
	float fRec144[3];
	float fConst345;
	float fConst346;
	float fConst347;
	float fRec143[3];
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fRec142[3];
	float fConst352;
	float fConst353;
	float fConst354;
	float fRec141[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fRec140[3];
	float fConst358;
	float fRec139[2];
	FAUSTFLOAT fVbargraph5;
	float fConst359;
	float fConst360;
	float fConst361;
	float fConst362;
	float fConst363;
	float fConst364;
	float fConst365;
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
	float fRec152[3];
	float fConst380;
	float fConst381;
	float fConst382;
	float fRec151[3];
	float fConst383;
	float fConst384;
	float fConst385;
	float fRec150[3];
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fRec149[3];
	float fConst390;
	float fConst391;
	float fConst392;
	float fRec148[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fRec147[3];
	float fConst396;
	float fRec146[2];
	FAUSTFLOAT fVbargraph6;
	float fConst397;
	float fConst398;
	float fConst399;
	float fConst400;
	float fConst401;
	float fConst402;
	float fConst403;
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
	float fRec159[3];
	float fConst418;
	float fConst419;
	float fConst420;
	float fRec158[3];
	float fConst421;
	float fConst422;
	float fConst423;
	float fRec157[3];
	float fConst424;
	float fConst425;
	float fConst426;
	float fConst427;
	float fRec156[3];
	float fConst428;
	float fConst429;
	float fConst430;
	float fRec155[3];
	float fConst431;
	float fConst432;
	float fConst433;
	float fRec154[3];
	float fConst434;
	float fRec153[2];
	FAUSTFLOAT fVbargraph7;
	float fConst435;
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fConst440;
	float fConst441;
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
	float fRec166[3];
	float fConst456;
	float fConst457;
	float fConst458;
	float fRec165[3];
	float fConst459;
	float fConst460;
	float fConst461;
	float fRec164[3];
	float fConst462;
	float fConst463;
	float fConst464;
	float fConst465;
	float fRec163[3];
	float fConst466;
	float fConst467;
	float fConst468;
	float fRec162[3];
	float fConst469;
	float fConst470;
	float fConst471;
	float fRec161[3];
	float fConst472;
	float fRec160[2];
	FAUSTFLOAT fVbargraph8;
	float fConst473;
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fConst478;
	float fConst479;
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
	float fRec173[3];
	float fConst494;
	float fConst495;
	float fConst496;
	float fRec172[3];
	float fConst497;
	float fConst498;
	float fConst499;
	float fRec171[3];
	float fConst500;
	float fConst501;
	float fConst502;
	float fConst503;
	float fRec170[3];
	float fConst504;
	float fConst505;
	float fConst506;
	float fRec169[3];
	float fConst507;
	float fConst508;
	float fConst509;
	float fRec168[3];
	float fConst510;
	float fRec167[2];
	FAUSTFLOAT fVbargraph9;
	float fConst511;
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fConst519;
	float fConst520;
	float fConst521;
	float fConst522;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fRec180[3];
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec179[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec178[3];
	float fConst538;
	float fConst539;
	float fConst540;
	float fConst541;
	float fRec177[3];
	float fConst542;
	float fConst543;
	float fConst544;
	float fRec176[3];
	float fConst545;
	float fConst546;
	float fConst547;
	float fRec175[3];
	float fConst548;
	float fRec174[2];
	FAUSTFLOAT fVbargraph10;
	float fConst549;
	float fConst550;
	float fConst551;
	float fConst552;
	float fConst553;
	float fConst554;
	float fConst555;
	float fConst556;
	float fConst557;
	float fConst558;
	float fConst559;
	float fConst560;
	float fConst561;
	float fConst562;
	float fConst563;
	float fConst564;
	float fConst565;
	float fConst566;
	float fConst567;
	float fConst568;
	float fConst569;
	float fRec187[3];
	float fConst570;
	float fConst571;
	float fConst572;
	float fRec186[3];
	float fConst573;
	float fConst574;
	float fConst575;
	float fRec185[3];
	float fConst576;
	float fConst577;
	float fConst578;
	float fConst579;
	float fRec184[3];
	float fConst580;
	float fConst581;
	float fConst582;
	float fRec183[3];
	float fConst583;
	float fConst584;
	float fConst585;
	float fRec182[3];
	float fConst586;
	float fRec181[2];
	FAUSTFLOAT fVbargraph11;
	float fConst587;
	float fConst588;
	float fConst589;
	float fConst590;
	float fConst591;
	float fConst592;
	float fConst593;
	float fConst594;
	float fConst595;
	float fConst596;
	float fConst597;
	float fConst598;
	float fConst599;
	float fConst600;
	float fConst601;
	float fConst602;
	float fConst603;
	float fConst604;
	float fConst605;
	float fConst606;
	float fConst607;
	float fRec194[3];
	float fConst608;
	float fConst609;
	float fConst610;
	float fRec193[3];
	float fConst611;
	float fConst612;
	float fConst613;
	float fRec192[3];
	float fConst614;
	float fConst615;
	float fConst616;
	float fConst617;
	float fRec191[3];
	float fConst618;
	float fConst619;
	float fConst620;
	float fRec190[3];
	float fConst621;
	float fConst622;
	float fConst623;
	float fRec189[3];
	float fConst624;
	float fRec188[2];
	FAUSTFLOAT fVbargraph12;
	float fConst625;
	float fConst626;
	float fConst627;
	float fConst628;
	float fConst629;
	float fConst630;
	float fConst631;
	float fConst632;
	float fConst633;
	float fConst634;
	float fConst635;
	float fConst636;
	float fConst637;
	float fConst638;
	float fConst639;
	float fConst640;
	float fConst641;
	float fConst642;
	float fConst643;
	float fConst644;
	float fConst645;
	float fRec201[3];
	float fConst646;
	float fConst647;
	float fConst648;
	float fRec200[3];
	float fConst649;
	float fConst650;
	float fConst651;
	float fRec199[3];
	float fConst652;
	float fConst653;
	float fConst654;
	float fConst655;
	float fRec198[3];
	float fConst656;
	float fConst657;
	float fConst658;
	float fRec197[3];
	float fConst659;
	float fConst660;
	float fConst661;
	float fRec196[3];
	float fConst662;
	float fRec195[2];
	FAUSTFLOAT fVbargraph13;
	float fConst663;
	float fConst664;
	float fConst665;
	float fConst666;
	float fConst667;
	float fConst668;
	float fConst669;
	float fConst670;
	float fConst671;
	float fRec205[3];
	float fConst672;
	float fConst673;
	float fConst674;
	float fRec204[3];
	float fConst675;
	float fConst676;
	float fConst677;
	float fRec203[3];
	float fConst678;
	float fRec202[2];
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
	m->declare(m->metaInterface, "description", "Signal generators through a filter bank with spectrum analysis display");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "graphicEqLab");
	m->declare(m->metaInterface, "noises.lib/name", "Faust Noise Generator Library");
	m->declare(m->metaInterface, "noises.lib/version", "0.0");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
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
	dsp->fVslider0 = (FAUSTFLOAT)-20.0f;
	dsp->fCheckbox1 = (FAUSTFLOAT)0.0f;
	dsp->fCheckbox2 = (FAUSTFLOAT)0.0f;
	dsp->fEntry0 = (FAUSTFLOAT)2.0f;
	dsp->fVslider1 = (FAUSTFLOAT)49.0f;
	dsp->fVslider2 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fVslider3 = (FAUSTFLOAT)-0.10000000000000001f;
	dsp->fVslider4 = (FAUSTFLOAT)0.10000000000000001f;
	dsp->fCheckbox3 = (FAUSTFLOAT)0.0f;
	dsp->fVslider5 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider6 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider7 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider8 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider9 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider10 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider11 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider12 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider13 = (FAUSTFLOAT)-10.0f;
	dsp->fVslider14 = (FAUSTFLOAT)-10.0f;
	
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
			dsp->fRec15[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec17[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec16[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fVec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fVec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fVec5[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fVec6[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fVec7[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fVec8[l11] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec18[l12] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fVec9[l13] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fVec10[l14] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fVec11[l15] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fVec12[l16] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fVec13[l17] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fVec14[l18] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fVec15[l19] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec19[l20] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fVec16[l21] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fVec17[l22] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fVec18[l23] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			dsp->fVec19[l24] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fVec20[l25] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fVec21[l26] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->iRec20[l27] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			dsp->fRec21[l28] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fVec22[l29] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			dsp->fRec14[l30] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			dsp->fRec13[l31] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			dsp->fRec12[l32] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			dsp->fRec11[l33] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			dsp->fRec10[l34] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			dsp->fRec9[l35] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			dsp->fRec8[l36] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			dsp->fRec7[l37] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			dsp->fRec6[l38] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			dsp->fRec5[l39] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			dsp->fRec4[l40] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec22[l41] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			dsp->fRec35[l42] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			dsp->fRec34[l43] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			dsp->fRec33[l44] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			dsp->fVec23[l45] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec32[l46] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			dsp->fRec31[l47] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			dsp->fRec30[l48] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			dsp->fRec29[l49] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			dsp->fRec28[l50] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			dsp->fRec27[l51] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			dsp->fRec26[l52] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			dsp->fRec25[l53] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			dsp->fRec24[l54] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			dsp->fRec23[l55] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			dsp->fRec36[l56] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec48[l57] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			dsp->fRec47[l58] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			dsp->fRec46[l59] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			dsp->fVec24[l60] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec45[l61] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			dsp->fRec44[l62] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			dsp->fRec43[l63] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l64;
		for (l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			dsp->fRec42[l64] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l65;
		for (l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			dsp->fRec41[l65] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l66;
		for (l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			dsp->fRec40[l66] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l67;
		for (l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			dsp->fRec39[l67] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l68;
		for (l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			dsp->fRec38[l68] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l69;
		for (l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			dsp->fRec37[l69] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l70;
		for (l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			dsp->fRec49[l70] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l71;
		for (l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			dsp->fRec60[l71] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l72;
		for (l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			dsp->fRec59[l72] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l73;
		for (l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			dsp->fRec58[l73] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l74;
		for (l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			dsp->fVec25[l74] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l75;
		for (l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			dsp->fRec57[l75] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l76;
		for (l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			dsp->fRec56[l76] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l77;
		for (l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			dsp->fRec55[l77] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l78;
		for (l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			dsp->fRec54[l78] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l79;
		for (l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			dsp->fRec53[l79] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l80;
		for (l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			dsp->fRec52[l80] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l81;
		for (l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			dsp->fRec51[l81] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l82;
		for (l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			dsp->fRec50[l82] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l83;
		for (l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			dsp->fRec61[l83] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l84;
		for (l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			dsp->fRec71[l84] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l85;
		for (l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			dsp->fRec70[l85] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l86;
		for (l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			dsp->fRec69[l86] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l87;
		for (l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			dsp->fVec26[l87] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l88;
		for (l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			dsp->fRec68[l88] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l89;
		for (l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			dsp->fRec67[l89] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l90;
		for (l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			dsp->fRec66[l90] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l91;
		for (l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			dsp->fRec65[l91] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l92;
		for (l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			dsp->fRec64[l92] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l93;
		for (l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			dsp->fRec63[l93] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l94;
		for (l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			dsp->fRec62[l94] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l95;
		for (l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			dsp->fRec72[l95] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l96;
		for (l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			dsp->fRec81[l96] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l97;
		for (l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			dsp->fRec80[l97] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l98;
		for (l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			dsp->fRec79[l98] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l99;
		for (l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			dsp->fVec27[l99] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l100;
		for (l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			dsp->fRec78[l100] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l101;
		for (l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			dsp->fRec77[l101] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l102;
		for (l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			dsp->fRec76[l102] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l103;
		for (l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			dsp->fRec75[l103] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l104;
		for (l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			dsp->fRec74[l104] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l105;
		for (l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			dsp->fRec73[l105] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l106;
		for (l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			dsp->fRec82[l106] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l107;
		for (l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			dsp->fRec90[l107] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l108;
		for (l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			dsp->fRec89[l108] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l109;
		for (l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			dsp->fRec88[l109] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l110;
		for (l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			dsp->fVec28[l110] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l111;
		for (l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			dsp->fRec87[l111] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l112;
		for (l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			dsp->fRec86[l112] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l113;
		for (l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			dsp->fRec85[l113] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l114;
		for (l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			dsp->fRec84[l114] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l115;
		for (l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			dsp->fRec83[l115] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l116;
		for (l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			dsp->fRec91[l116] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l117;
		for (l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			dsp->fRec98[l117] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l118;
		for (l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			dsp->fRec97[l118] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l119;
		for (l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			dsp->fRec96[l119] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l120;
		for (l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			dsp->fVec29[l120] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l121;
		for (l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			dsp->fRec95[l121] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l122;
		for (l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			dsp->fRec94[l122] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l123;
		for (l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			dsp->fRec93[l123] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l124;
		for (l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			dsp->fRec92[l124] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l125;
		for (l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			dsp->fRec99[l125] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l126;
		for (l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			dsp->fRec105[l126] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l127;
		for (l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			dsp->fRec104[l127] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l128;
		for (l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			dsp->fRec103[l128] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l129;
		for (l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			dsp->fVec30[l129] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l130;
		for (l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			dsp->fRec102[l130] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l131;
		for (l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			dsp->fRec101[l131] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l132;
		for (l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			dsp->fRec100[l132] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l133;
		for (l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			dsp->fRec106[l133] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l134;
		for (l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			dsp->fRec109[l134] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l135;
		for (l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			dsp->fRec108[l135] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l136;
		for (l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			dsp->fRec107[l136] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l137;
		for (l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			dsp->fRec110[l137] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l138;
		for (l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			dsp->fRec3[l138] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l139;
		for (l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			dsp->fRec2[l139] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l140;
		for (l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			dsp->fRec1[l140] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l141;
		for (l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			dsp->fRec0[l141] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l142;
		for (l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			dsp->fRec117[l142] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l143;
		for (l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			dsp->fRec116[l143] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l144;
		for (l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			dsp->fRec115[l144] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l145;
		for (l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			dsp->fRec114[l145] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l146;
		for (l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			dsp->fRec113[l146] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l147;
		for (l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			dsp->fRec112[l147] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l148;
		for (l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			dsp->fRec111[l148] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l149;
		for (l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			dsp->fRec124[l149] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l150;
		for (l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			dsp->fRec123[l150] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l151;
		for (l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			dsp->fRec122[l151] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l152;
		for (l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			dsp->fRec121[l152] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l153;
		for (l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			dsp->fRec120[l153] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l154;
		for (l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			dsp->fRec119[l154] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l155;
		for (l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			dsp->fRec118[l155] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l156;
		for (l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			dsp->fRec131[l156] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l157;
		for (l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			dsp->fRec130[l157] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l158;
		for (l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			dsp->fRec129[l158] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l159;
		for (l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			dsp->fRec128[l159] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l160;
		for (l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			dsp->fRec127[l160] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l161;
		for (l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			dsp->fRec126[l161] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l162;
		for (l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			dsp->fRec125[l162] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l163;
		for (l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			dsp->fRec138[l163] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l164;
		for (l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			dsp->fRec137[l164] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l165;
		for (l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			dsp->fRec136[l165] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l166;
		for (l166 = 0; (l166 < 3); l166 = (l166 + 1)) {
			dsp->fRec135[l166] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l167;
		for (l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			dsp->fRec134[l167] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l168;
		for (l168 = 0; (l168 < 3); l168 = (l168 + 1)) {
			dsp->fRec133[l168] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l169;
		for (l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			dsp->fRec132[l169] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l170;
		for (l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			dsp->fRec145[l170] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l171;
		for (l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			dsp->fRec144[l171] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l172;
		for (l172 = 0; (l172 < 3); l172 = (l172 + 1)) {
			dsp->fRec143[l172] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l173;
		for (l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			dsp->fRec142[l173] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l174;
		for (l174 = 0; (l174 < 3); l174 = (l174 + 1)) {
			dsp->fRec141[l174] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l175;
		for (l175 = 0; (l175 < 3); l175 = (l175 + 1)) {
			dsp->fRec140[l175] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l176;
		for (l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			dsp->fRec139[l176] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l177;
		for (l177 = 0; (l177 < 3); l177 = (l177 + 1)) {
			dsp->fRec152[l177] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l178;
		for (l178 = 0; (l178 < 3); l178 = (l178 + 1)) {
			dsp->fRec151[l178] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l179;
		for (l179 = 0; (l179 < 3); l179 = (l179 + 1)) {
			dsp->fRec150[l179] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l180;
		for (l180 = 0; (l180 < 3); l180 = (l180 + 1)) {
			dsp->fRec149[l180] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l181;
		for (l181 = 0; (l181 < 3); l181 = (l181 + 1)) {
			dsp->fRec148[l181] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l182;
		for (l182 = 0; (l182 < 3); l182 = (l182 + 1)) {
			dsp->fRec147[l182] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l183;
		for (l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			dsp->fRec146[l183] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l184;
		for (l184 = 0; (l184 < 3); l184 = (l184 + 1)) {
			dsp->fRec159[l184] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l185;
		for (l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			dsp->fRec158[l185] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l186;
		for (l186 = 0; (l186 < 3); l186 = (l186 + 1)) {
			dsp->fRec157[l186] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l187;
		for (l187 = 0; (l187 < 3); l187 = (l187 + 1)) {
			dsp->fRec156[l187] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l188;
		for (l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			dsp->fRec155[l188] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l189;
		for (l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			dsp->fRec154[l189] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l190;
		for (l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			dsp->fRec153[l190] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l191;
		for (l191 = 0; (l191 < 3); l191 = (l191 + 1)) {
			dsp->fRec166[l191] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l192;
		for (l192 = 0; (l192 < 3); l192 = (l192 + 1)) {
			dsp->fRec165[l192] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l193;
		for (l193 = 0; (l193 < 3); l193 = (l193 + 1)) {
			dsp->fRec164[l193] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l194;
		for (l194 = 0; (l194 < 3); l194 = (l194 + 1)) {
			dsp->fRec163[l194] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l195;
		for (l195 = 0; (l195 < 3); l195 = (l195 + 1)) {
			dsp->fRec162[l195] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l196;
		for (l196 = 0; (l196 < 3); l196 = (l196 + 1)) {
			dsp->fRec161[l196] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l197;
		for (l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			dsp->fRec160[l197] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l198;
		for (l198 = 0; (l198 < 3); l198 = (l198 + 1)) {
			dsp->fRec173[l198] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l199;
		for (l199 = 0; (l199 < 3); l199 = (l199 + 1)) {
			dsp->fRec172[l199] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l200;
		for (l200 = 0; (l200 < 3); l200 = (l200 + 1)) {
			dsp->fRec171[l200] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l201;
		for (l201 = 0; (l201 < 3); l201 = (l201 + 1)) {
			dsp->fRec170[l201] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l202;
		for (l202 = 0; (l202 < 3); l202 = (l202 + 1)) {
			dsp->fRec169[l202] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l203;
		for (l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			dsp->fRec168[l203] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l204;
		for (l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			dsp->fRec167[l204] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l205;
		for (l205 = 0; (l205 < 3); l205 = (l205 + 1)) {
			dsp->fRec180[l205] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l206;
		for (l206 = 0; (l206 < 3); l206 = (l206 + 1)) {
			dsp->fRec179[l206] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l207;
		for (l207 = 0; (l207 < 3); l207 = (l207 + 1)) {
			dsp->fRec178[l207] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l208;
		for (l208 = 0; (l208 < 3); l208 = (l208 + 1)) {
			dsp->fRec177[l208] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l209;
		for (l209 = 0; (l209 < 3); l209 = (l209 + 1)) {
			dsp->fRec176[l209] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l210;
		for (l210 = 0; (l210 < 3); l210 = (l210 + 1)) {
			dsp->fRec175[l210] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l211;
		for (l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			dsp->fRec174[l211] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l212;
		for (l212 = 0; (l212 < 3); l212 = (l212 + 1)) {
			dsp->fRec187[l212] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l213;
		for (l213 = 0; (l213 < 3); l213 = (l213 + 1)) {
			dsp->fRec186[l213] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l214;
		for (l214 = 0; (l214 < 3); l214 = (l214 + 1)) {
			dsp->fRec185[l214] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l215;
		for (l215 = 0; (l215 < 3); l215 = (l215 + 1)) {
			dsp->fRec184[l215] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l216;
		for (l216 = 0; (l216 < 3); l216 = (l216 + 1)) {
			dsp->fRec183[l216] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l217;
		for (l217 = 0; (l217 < 3); l217 = (l217 + 1)) {
			dsp->fRec182[l217] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l218;
		for (l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			dsp->fRec181[l218] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l219;
		for (l219 = 0; (l219 < 3); l219 = (l219 + 1)) {
			dsp->fRec194[l219] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l220;
		for (l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			dsp->fRec193[l220] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l221;
		for (l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			dsp->fRec192[l221] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l222;
		for (l222 = 0; (l222 < 3); l222 = (l222 + 1)) {
			dsp->fRec191[l222] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l223;
		for (l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			dsp->fRec190[l223] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l224;
		for (l224 = 0; (l224 < 3); l224 = (l224 + 1)) {
			dsp->fRec189[l224] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l225;
		for (l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			dsp->fRec188[l225] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l226;
		for (l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			dsp->fRec201[l226] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l227;
		for (l227 = 0; (l227 < 3); l227 = (l227 + 1)) {
			dsp->fRec200[l227] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l228;
		for (l228 = 0; (l228 < 3); l228 = (l228 + 1)) {
			dsp->fRec199[l228] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l229;
		for (l229 = 0; (l229 < 3); l229 = (l229 + 1)) {
			dsp->fRec198[l229] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l230;
		for (l230 = 0; (l230 < 3); l230 = (l230 + 1)) {
			dsp->fRec197[l230] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l231;
		for (l231 = 0; (l231 < 3); l231 = (l231 + 1)) {
			dsp->fRec196[l231] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l232;
		for (l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			dsp->fRec195[l232] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l233;
		for (l233 = 0; (l233 < 3); l233 = (l233 + 1)) {
			dsp->fRec205[l233] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l234;
		for (l234 = 0; (l234 < 3); l234 = (l234 + 1)) {
			dsp->fRec204[l234] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l235;
		for (l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			dsp->fRec203[l235] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l236;
		for (l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			dsp->fRec202[l236] = 0.0f;
			
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
	dsp->fConst14 = tanf((31415.9258f / dsp->fConst0));
	dsp->fConst15 = (1.0f / dsp->fConst14);
	dsp->fConst16 = (((dsp->fConst15 + 0.618034005f) / dsp->fConst14) + 1.0f);
	dsp->fConst17 = (1.0f / dsp->fConst16);
	dsp->fConst18 = (1.0f / mydsp_faustpower2_f(dsp->fConst14));
	dsp->fConst19 = (2.0f * (0.0f - dsp->fConst18));
	dsp->fConst20 = (1.0f / (((dsp->fConst15 + 1.61803401f) / dsp->fConst14) + 1.0f));
	dsp->fConst21 = (dsp->fConst15 + 1.0f);
	dsp->fConst22 = (0.0f - ((1.0f - dsp->fConst15) / dsp->fConst21));
	dsp->fConst23 = (1.0f / dsp->fConst21);
	dsp->fConst24 = (1.0f / dsp->fConst0);
	dsp->fConst25 = (0.25f * dsp->fConst0);
	dsp->fConst26 = (0.0416666679f * mydsp_faustpower2_f(dsp->fConst0));
	dsp->fConst27 = (0.00520833349f * mydsp_faustpower3_f(dsp->fConst0));
	dsp->fConst28 = (0.0f - dsp->fConst15);
	dsp->fConst29 = (2.0f * (1.0f - dsp->fConst18));
	dsp->fConst30 = (((dsp->fConst15 + -1.61803401f) / dsp->fConst14) + 1.0f);
	dsp->fConst31 = (((dsp->fConst15 + -0.618034005f) / dsp->fConst14) + 1.0f);
	dsp->fConst32 = tanf((122.71846f / dsp->fConst0));
	dsp->fConst33 = (1.0f / dsp->fConst32);
	dsp->fConst34 = (1.0f / (((dsp->fConst33 + 1.61803401f) / dsp->fConst32) + 1.0f));
	dsp->fConst35 = (((dsp->fConst33 + -1.61803401f) / dsp->fConst32) + 1.0f);
	dsp->fConst36 = (1.0f / mydsp_faustpower2_f(dsp->fConst32));
	dsp->fConst37 = (2.0f * (1.0f - dsp->fConst36));
	dsp->fConst38 = tanf((245.43692f / dsp->fConst0));
	dsp->fConst39 = (1.0f / dsp->fConst38);
	dsp->fConst40 = (1.0f / (((dsp->fConst39 + 1.61803401f) / dsp->fConst38) + 1.0f));
	dsp->fConst41 = (((dsp->fConst39 + -1.61803401f) / dsp->fConst38) + 1.0f);
	dsp->fConst42 = (1.0f / mydsp_faustpower2_f(dsp->fConst38));
	dsp->fConst43 = (2.0f * (1.0f - dsp->fConst42));
	dsp->fConst44 = tanf((490.87384f / dsp->fConst0));
	dsp->fConst45 = (1.0f / dsp->fConst44);
	dsp->fConst46 = (1.0f / (((dsp->fConst45 + 1.61803401f) / dsp->fConst44) + 1.0f));
	dsp->fConst47 = (((dsp->fConst45 + -1.61803401f) / dsp->fConst44) + 1.0f);
	dsp->fConst48 = (1.0f / mydsp_faustpower2_f(dsp->fConst44));
	dsp->fConst49 = (2.0f * (1.0f - dsp->fConst48));
	dsp->fConst50 = tanf((981.747681f / dsp->fConst0));
	dsp->fConst51 = (1.0f / dsp->fConst50);
	dsp->fConst52 = (1.0f / (((dsp->fConst51 + 1.61803401f) / dsp->fConst50) + 1.0f));
	dsp->fConst53 = (((dsp->fConst51 + -1.61803401f) / dsp->fConst50) + 1.0f);
	dsp->fConst54 = (1.0f / mydsp_faustpower2_f(dsp->fConst50));
	dsp->fConst55 = (2.0f * (1.0f - dsp->fConst54));
	dsp->fConst56 = tanf((1963.49536f / dsp->fConst0));
	dsp->fConst57 = (1.0f / dsp->fConst56);
	dsp->fConst58 = (1.0f / (((dsp->fConst57 + 1.61803401f) / dsp->fConst56) + 1.0f));
	dsp->fConst59 = (((dsp->fConst57 + -1.61803401f) / dsp->fConst56) + 1.0f);
	dsp->fConst60 = (1.0f / mydsp_faustpower2_f(dsp->fConst56));
	dsp->fConst61 = (2.0f * (1.0f - dsp->fConst60));
	dsp->fConst62 = tanf((3926.99072f / dsp->fConst0));
	dsp->fConst63 = (1.0f / dsp->fConst62);
	dsp->fConst64 = (1.0f / (((dsp->fConst63 + 1.61803401f) / dsp->fConst62) + 1.0f));
	dsp->fConst65 = (((dsp->fConst63 + -1.61803401f) / dsp->fConst62) + 1.0f);
	dsp->fConst66 = (1.0f / mydsp_faustpower2_f(dsp->fConst62));
	dsp->fConst67 = (2.0f * (1.0f - dsp->fConst66));
	dsp->fConst68 = tanf((7853.98145f / dsp->fConst0));
	dsp->fConst69 = (1.0f / dsp->fConst68);
	dsp->fConst70 = (1.0f / (((dsp->fConst69 + 1.61803401f) / dsp->fConst68) + 1.0f));
	dsp->fConst71 = (((dsp->fConst69 + -1.61803401f) / dsp->fConst68) + 1.0f);
	dsp->fConst72 = (1.0f / mydsp_faustpower2_f(dsp->fConst68));
	dsp->fConst73 = (2.0f * (1.0f - dsp->fConst72));
	dsp->fConst74 = tanf((15707.9629f / dsp->fConst0));
	dsp->fConst75 = (1.0f / dsp->fConst74);
	dsp->fConst76 = (1.0f / (((dsp->fConst75 + 1.61803401f) / dsp->fConst74) + 1.0f));
	dsp->fConst77 = (((dsp->fConst75 + -1.61803401f) / dsp->fConst74) + 1.0f);
	dsp->fConst78 = (1.0f / mydsp_faustpower2_f(dsp->fConst74));
	dsp->fConst79 = (2.0f * (1.0f - dsp->fConst78));
	dsp->fConst80 = (((dsp->fConst75 + 0.618034005f) / dsp->fConst74) + 1.0f);
	dsp->fConst81 = (1.0f / dsp->fConst80);
	dsp->fConst82 = (2.0f * (0.0f - dsp->fConst78));
	dsp->fConst83 = (1.0f / (((dsp->fConst75 + 1.61803401f) / dsp->fConst74) + 1.0f));
	dsp->fConst84 = (dsp->fConst75 + 1.0f);
	dsp->fConst85 = (0.0f - ((1.0f - dsp->fConst75) / dsp->fConst84));
	dsp->fConst86 = (1.0f / (dsp->fConst84 * dsp->fConst16));
	dsp->fConst87 = (0.0f - dsp->fConst75);
	dsp->fConst88 = (((dsp->fConst75 + -1.61803401f) / dsp->fConst74) + 1.0f);
	dsp->fConst89 = (((dsp->fConst75 + -0.618034005f) / dsp->fConst74) + 1.0f);
	dsp->fConst90 = (((dsp->fConst69 + 0.618034005f) / dsp->fConst68) + 1.0f);
	dsp->fConst91 = (1.0f / dsp->fConst90);
	dsp->fConst92 = (2.0f * (0.0f - dsp->fConst72));
	dsp->fConst93 = (1.0f / (((dsp->fConst69 + 1.61803401f) / dsp->fConst68) + 1.0f));
	dsp->fConst94 = (dsp->fConst69 + 1.0f);
	dsp->fConst95 = (0.0f - ((1.0f - dsp->fConst69) / dsp->fConst94));
	dsp->fConst96 = (1.0f / (dsp->fConst80 * dsp->fConst94));
	dsp->fConst97 = (0.0f - dsp->fConst69);
	dsp->fConst98 = (((dsp->fConst69 + -1.61803401f) / dsp->fConst68) + 1.0f);
	dsp->fConst99 = (((dsp->fConst69 + -0.618034005f) / dsp->fConst68) + 1.0f);
	dsp->fConst100 = (((dsp->fConst63 + 0.618034005f) / dsp->fConst62) + 1.0f);
	dsp->fConst101 = (1.0f / dsp->fConst100);
	dsp->fConst102 = (2.0f * (0.0f - dsp->fConst66));
	dsp->fConst103 = (1.0f / (((dsp->fConst63 + 1.61803401f) / dsp->fConst62) + 1.0f));
	dsp->fConst104 = (dsp->fConst63 + 1.0f);
	dsp->fConst105 = (0.0f - ((1.0f - dsp->fConst63) / dsp->fConst104));
	dsp->fConst106 = (1.0f / (dsp->fConst90 * dsp->fConst104));
	dsp->fConst107 = (0.0f - dsp->fConst63);
	dsp->fConst108 = (((dsp->fConst63 + -1.61803401f) / dsp->fConst62) + 1.0f);
	dsp->fConst109 = (((dsp->fConst63 + -0.618034005f) / dsp->fConst62) + 1.0f);
	dsp->fConst110 = (((dsp->fConst57 + 0.618034005f) / dsp->fConst56) + 1.0f);
	dsp->fConst111 = (1.0f / dsp->fConst110);
	dsp->fConst112 = (2.0f * (0.0f - dsp->fConst60));
	dsp->fConst113 = (1.0f / (((dsp->fConst57 + 1.61803401f) / dsp->fConst56) + 1.0f));
	dsp->fConst114 = (dsp->fConst57 + 1.0f);
	dsp->fConst115 = (0.0f - ((1.0f - dsp->fConst57) / dsp->fConst114));
	dsp->fConst116 = (1.0f / (dsp->fConst100 * dsp->fConst114));
	dsp->fConst117 = (0.0f - dsp->fConst57);
	dsp->fConst118 = (((dsp->fConst57 + -1.61803401f) / dsp->fConst56) + 1.0f);
	dsp->fConst119 = (((dsp->fConst57 + -0.618034005f) / dsp->fConst56) + 1.0f);
	dsp->fConst120 = (((dsp->fConst51 + 0.618034005f) / dsp->fConst50) + 1.0f);
	dsp->fConst121 = (1.0f / dsp->fConst120);
	dsp->fConst122 = (2.0f * (0.0f - dsp->fConst54));
	dsp->fConst123 = (1.0f / (((dsp->fConst51 + 1.61803401f) / dsp->fConst50) + 1.0f));
	dsp->fConst124 = (dsp->fConst51 + 1.0f);
	dsp->fConst125 = (0.0f - ((1.0f - dsp->fConst51) / dsp->fConst124));
	dsp->fConst126 = (1.0f / (dsp->fConst110 * dsp->fConst124));
	dsp->fConst127 = (0.0f - dsp->fConst51);
	dsp->fConst128 = (((dsp->fConst51 + -1.61803401f) / dsp->fConst50) + 1.0f);
	dsp->fConst129 = (((dsp->fConst51 + -0.618034005f) / dsp->fConst50) + 1.0f);
	dsp->fConst130 = (((dsp->fConst45 + 0.618034005f) / dsp->fConst44) + 1.0f);
	dsp->fConst131 = (1.0f / dsp->fConst130);
	dsp->fConst132 = (2.0f * (0.0f - dsp->fConst48));
	dsp->fConst133 = (1.0f / (((dsp->fConst45 + 1.61803401f) / dsp->fConst44) + 1.0f));
	dsp->fConst134 = (dsp->fConst45 + 1.0f);
	dsp->fConst135 = (0.0f - ((1.0f - dsp->fConst45) / dsp->fConst134));
	dsp->fConst136 = (1.0f / (dsp->fConst120 * dsp->fConst134));
	dsp->fConst137 = (0.0f - dsp->fConst45);
	dsp->fConst138 = (((dsp->fConst45 + -1.61803401f) / dsp->fConst44) + 1.0f);
	dsp->fConst139 = (((dsp->fConst45 + -0.618034005f) / dsp->fConst44) + 1.0f);
	dsp->fConst140 = (((dsp->fConst39 + 0.618034005f) / dsp->fConst38) + 1.0f);
	dsp->fConst141 = (1.0f / dsp->fConst140);
	dsp->fConst142 = (2.0f * (0.0f - dsp->fConst42));
	dsp->fConst143 = (1.0f / (((dsp->fConst39 + 1.61803401f) / dsp->fConst38) + 1.0f));
	dsp->fConst144 = (dsp->fConst39 + 1.0f);
	dsp->fConst145 = (0.0f - ((1.0f - dsp->fConst39) / dsp->fConst144));
	dsp->fConst146 = (1.0f / (dsp->fConst130 * dsp->fConst144));
	dsp->fConst147 = (0.0f - dsp->fConst39);
	dsp->fConst148 = (((dsp->fConst39 + -1.61803401f) / dsp->fConst38) + 1.0f);
	dsp->fConst149 = (((dsp->fConst39 + -0.618034005f) / dsp->fConst38) + 1.0f);
	dsp->fConst150 = (1.0f / (((dsp->fConst33 + 0.618034005f) / dsp->fConst32) + 1.0f));
	dsp->fConst151 = (2.0f * (0.0f - dsp->fConst36));
	dsp->fConst152 = (1.0f / (((dsp->fConst33 + 1.61803401f) / dsp->fConst32) + 1.0f));
	dsp->fConst153 = (dsp->fConst33 + 1.0f);
	dsp->fConst154 = (0.0f - ((1.0f - dsp->fConst33) / dsp->fConst153));
	dsp->fConst155 = (1.0f / (dsp->fConst140 * dsp->fConst153));
	dsp->fConst156 = (0.0f - dsp->fConst33);
	dsp->fConst157 = (((dsp->fConst33 + -1.61803401f) / dsp->fConst32) + 1.0f);
	dsp->fConst158 = (((dsp->fConst33 + -0.618034005f) / dsp->fConst32) + 1.0f);
	dsp->fConst159 = (((dsp->fConst3 + -3.18972731f) / dsp->fConst2) + 4.07678175f);
	dsp->fConst160 = (1.0f / dsp->fConst5);
	dsp->fConst161 = (2.0f * (4.07678175f - dsp->fConst160));
	dsp->fConst162 = (dsp->fConst12 + 0.000407678192f);
	dsp->fConst163 = (((dsp->fConst3 + -0.743130445f) / dsp->fConst2) + 1.4500711f);
	dsp->fConst164 = (2.0f * (1.4500711f - dsp->fConst160));
	dsp->fConst165 = (dsp->fConst9 + 1.4500711f);
	dsp->fConst166 = (((dsp->fConst3 + -0.157482162f) / dsp->fConst2) + 0.935140193f);
	dsp->fConst167 = (2.0f * (0.935140193f - dsp->fConst160));
	dsp->fConst168 = (dsp->fConst6 + 0.935140193f);
	dsp->fConst169 = tanf((31665.2695f / dsp->fConst0));
	dsp->fConst170 = (1.0f / dsp->fConst169);
	dsp->fConst171 = (1.0f / (((dsp->fConst170 + 0.157482162f) / dsp->fConst169) + 0.935140193f));
	dsp->fConst172 = mydsp_faustpower2_f(dsp->fConst169);
	dsp->fConst173 = (50.0638084f / dsp->fConst172);
	dsp->fConst174 = (2.0f * (0.935140193f - dsp->fConst173));
	dsp->fConst175 = (1.0f / (((dsp->fConst170 + 0.743130445f) / dsp->fConst169) + 1.4500711f));
	dsp->fConst176 = (11.0520525f / dsp->fConst172);
	dsp->fConst177 = (2.0f * (1.4500711f - dsp->fConst176));
	dsp->fConst178 = (1.0f / (((dsp->fConst170 + 3.18972731f) / dsp->fConst169) + 4.07678175f));
	dsp->fConst179 = (0.00176617282f / dsp->fConst172);
	dsp->fConst180 = (2.0f * (0.000407678192f - dsp->fConst179));
	dsp->fConst181 = (1.0f / (((dsp->fConst3 + 0.168404877f) / dsp->fConst2) + 1.06935835f));
	dsp->fConst182 = (2.0f * (53.5361519f - dsp->fConst160));
	dsp->fConst183 = (1.0f / (((dsp->fConst3 + 0.51247865f) / dsp->fConst2) + 0.689621389f));
	dsp->fConst184 = (2.0f * (7.62173128f - dsp->fConst160));
	dsp->fConst185 = (1.0f / (((dsp->fConst3 + 0.782413065f) / dsp->fConst2) + 0.245291501f));
	dsp->fConst186 = (9.99999975e-05f / dsp->fConst5);
	dsp->fConst187 = (2.0f * (0.000433227193f - dsp->fConst186));
	dsp->fConst188 = (((dsp->fConst3 + -0.782413065f) / dsp->fConst2) + 0.245291501f);
	dsp->fConst189 = (2.0f * (0.245291501f - dsp->fConst160));
	dsp->fConst190 = (dsp->fConst186 + 0.000433227193f);
	dsp->fConst191 = (((dsp->fConst3 + -0.51247865f) / dsp->fConst2) + 0.689621389f);
	dsp->fConst192 = (2.0f * (0.689621389f - dsp->fConst160));
	dsp->fConst193 = (dsp->fConst160 + 7.62173128f);
	dsp->fConst194 = (((dsp->fConst3 + -0.168404877f) / dsp->fConst2) + 1.06935835f);
	dsp->fConst195 = (2.0f * (1.06935835f - dsp->fConst160));
	dsp->fConst196 = (dsp->fConst160 + 53.5361519f);
	dsp->fConst197 = (((dsp->fConst170 + -3.18972731f) / dsp->fConst169) + 4.07678175f);
	dsp->fConst198 = (1.0f / dsp->fConst172);
	dsp->fConst199 = (2.0f * (4.07678175f - dsp->fConst198));
	dsp->fConst200 = (dsp->fConst179 + 0.000407678192f);
	dsp->fConst201 = (((dsp->fConst170 + -0.743130445f) / dsp->fConst169) + 1.4500711f);
	dsp->fConst202 = (2.0f * (1.4500711f - dsp->fConst198));
	dsp->fConst203 = (dsp->fConst176 + 1.4500711f);
	dsp->fConst204 = (((dsp->fConst170 + -0.157482162f) / dsp->fConst169) + 0.935140193f);
	dsp->fConst205 = (2.0f * (0.935140193f - dsp->fConst198));
	dsp->fConst206 = (dsp->fConst173 + 0.935140193f);
	dsp->fConst207 = tanf((19947.8691f / dsp->fConst0));
	dsp->fConst208 = (1.0f / dsp->fConst207);
	dsp->fConst209 = (1.0f / (((dsp->fConst208 + 0.157482162f) / dsp->fConst207) + 0.935140193f));
	dsp->fConst210 = mydsp_faustpower2_f(dsp->fConst207);
	dsp->fConst211 = (50.0638084f / dsp->fConst210);
	dsp->fConst212 = (2.0f * (0.935140193f - dsp->fConst211));
	dsp->fConst213 = (1.0f / (((dsp->fConst208 + 0.743130445f) / dsp->fConst207) + 1.4500711f));
	dsp->fConst214 = (11.0520525f / dsp->fConst210);
	dsp->fConst215 = (2.0f * (1.4500711f - dsp->fConst214));
	dsp->fConst216 = (1.0f / (((dsp->fConst208 + 3.18972731f) / dsp->fConst207) + 4.07678175f));
	dsp->fConst217 = (0.00176617282f / dsp->fConst210);
	dsp->fConst218 = (2.0f * (0.000407678192f - dsp->fConst217));
	dsp->fConst219 = (1.0f / (((dsp->fConst170 + 0.168404877f) / dsp->fConst169) + 1.06935835f));
	dsp->fConst220 = (2.0f * (53.5361519f - dsp->fConst198));
	dsp->fConst221 = (1.0f / (((dsp->fConst170 + 0.51247865f) / dsp->fConst169) + 0.689621389f));
	dsp->fConst222 = (2.0f * (7.62173128f - dsp->fConst198));
	dsp->fConst223 = (1.0f / (((dsp->fConst170 + 0.782413065f) / dsp->fConst169) + 0.245291501f));
	dsp->fConst224 = (9.99999975e-05f / dsp->fConst172);
	dsp->fConst225 = (2.0f * (0.000433227193f - dsp->fConst224));
	dsp->fConst226 = (((dsp->fConst170 + -0.782413065f) / dsp->fConst169) + 0.245291501f);
	dsp->fConst227 = (2.0f * (0.245291501f - dsp->fConst198));
	dsp->fConst228 = (dsp->fConst224 + 0.000433227193f);
	dsp->fConst229 = (((dsp->fConst170 + -0.51247865f) / dsp->fConst169) + 0.689621389f);
	dsp->fConst230 = (2.0f * (0.689621389f - dsp->fConst198));
	dsp->fConst231 = (dsp->fConst198 + 7.62173128f);
	dsp->fConst232 = (((dsp->fConst170 + -0.168404877f) / dsp->fConst169) + 1.06935835f);
	dsp->fConst233 = (2.0f * (1.06935835f - dsp->fConst198));
	dsp->fConst234 = (dsp->fConst198 + 53.5361519f);
	dsp->fConst235 = (((dsp->fConst208 + -3.18972731f) / dsp->fConst207) + 4.07678175f);
	dsp->fConst236 = (1.0f / dsp->fConst210);
	dsp->fConst237 = (2.0f * (4.07678175f - dsp->fConst236));
	dsp->fConst238 = (dsp->fConst217 + 0.000407678192f);
	dsp->fConst239 = (((dsp->fConst208 + -0.743130445f) / dsp->fConst207) + 1.4500711f);
	dsp->fConst240 = (2.0f * (1.4500711f - dsp->fConst236));
	dsp->fConst241 = (dsp->fConst214 + 1.4500711f);
	dsp->fConst242 = (((dsp->fConst208 + -0.157482162f) / dsp->fConst207) + 0.935140193f);
	dsp->fConst243 = (2.0f * (0.935140193f - dsp->fConst236));
	dsp->fConst244 = (dsp->fConst211 + 0.935140193f);
	dsp->fConst245 = tanf((12566.3711f / dsp->fConst0));
	dsp->fConst246 = (1.0f / dsp->fConst245);
	dsp->fConst247 = (1.0f / (((dsp->fConst246 + 0.157482162f) / dsp->fConst245) + 0.935140193f));
	dsp->fConst248 = mydsp_faustpower2_f(dsp->fConst245);
	dsp->fConst249 = (50.0638084f / dsp->fConst248);
	dsp->fConst250 = (2.0f * (0.935140193f - dsp->fConst249));
	dsp->fConst251 = (1.0f / (((dsp->fConst246 + 0.743130445f) / dsp->fConst245) + 1.4500711f));
	dsp->fConst252 = (11.0520525f / dsp->fConst248);
	dsp->fConst253 = (2.0f * (1.4500711f - dsp->fConst252));
	dsp->fConst254 = (1.0f / (((dsp->fConst246 + 3.18972731f) / dsp->fConst245) + 4.07678175f));
	dsp->fConst255 = (0.00176617282f / dsp->fConst248);
	dsp->fConst256 = (2.0f * (0.000407678192f - dsp->fConst255));
	dsp->fConst257 = (1.0f / (((dsp->fConst208 + 0.168404877f) / dsp->fConst207) + 1.06935835f));
	dsp->fConst258 = (2.0f * (53.5361519f - dsp->fConst236));
	dsp->fConst259 = (1.0f / (((dsp->fConst208 + 0.51247865f) / dsp->fConst207) + 0.689621389f));
	dsp->fConst260 = (2.0f * (7.62173128f - dsp->fConst236));
	dsp->fConst261 = (1.0f / (((dsp->fConst208 + 0.782413065f) / dsp->fConst207) + 0.245291501f));
	dsp->fConst262 = (9.99999975e-05f / dsp->fConst210);
	dsp->fConst263 = (2.0f * (0.000433227193f - dsp->fConst262));
	dsp->fConst264 = (((dsp->fConst208 + -0.782413065f) / dsp->fConst207) + 0.245291501f);
	dsp->fConst265 = (2.0f * (0.245291501f - dsp->fConst236));
	dsp->fConst266 = (dsp->fConst262 + 0.000433227193f);
	dsp->fConst267 = (((dsp->fConst208 + -0.51247865f) / dsp->fConst207) + 0.689621389f);
	dsp->fConst268 = (2.0f * (0.689621389f - dsp->fConst236));
	dsp->fConst269 = (dsp->fConst236 + 7.62173128f);
	dsp->fConst270 = (((dsp->fConst208 + -0.168404877f) / dsp->fConst207) + 1.06935835f);
	dsp->fConst271 = (2.0f * (1.06935835f - dsp->fConst236));
	dsp->fConst272 = (dsp->fConst236 + 53.5361519f);
	dsp->fConst273 = (((dsp->fConst246 + -3.18972731f) / dsp->fConst245) + 4.07678175f);
	dsp->fConst274 = (1.0f / dsp->fConst248);
	dsp->fConst275 = (2.0f * (4.07678175f - dsp->fConst274));
	dsp->fConst276 = (dsp->fConst255 + 0.000407678192f);
	dsp->fConst277 = (((dsp->fConst246 + -0.743130445f) / dsp->fConst245) + 1.4500711f);
	dsp->fConst278 = (2.0f * (1.4500711f - dsp->fConst274));
	dsp->fConst279 = (dsp->fConst252 + 1.4500711f);
	dsp->fConst280 = (((dsp->fConst246 + -0.157482162f) / dsp->fConst245) + 0.935140193f);
	dsp->fConst281 = (2.0f * (0.935140193f - dsp->fConst274));
	dsp->fConst282 = (dsp->fConst249 + 0.935140193f);
	dsp->fConst283 = tanf((7916.31738f / dsp->fConst0));
	dsp->fConst284 = (1.0f / dsp->fConst283);
	dsp->fConst285 = (1.0f / (((dsp->fConst284 + 0.157482162f) / dsp->fConst283) + 0.935140193f));
	dsp->fConst286 = mydsp_faustpower2_f(dsp->fConst283);
	dsp->fConst287 = (50.0638084f / dsp->fConst286);
	dsp->fConst288 = (2.0f * (0.935140193f - dsp->fConst287));
	dsp->fConst289 = (1.0f / (((dsp->fConst284 + 0.743130445f) / dsp->fConst283) + 1.4500711f));
	dsp->fConst290 = (11.0520525f / dsp->fConst286);
	dsp->fConst291 = (2.0f * (1.4500711f - dsp->fConst290));
	dsp->fConst292 = (1.0f / (((dsp->fConst284 + 3.18972731f) / dsp->fConst283) + 4.07678175f));
	dsp->fConst293 = (0.00176617282f / dsp->fConst286);
	dsp->fConst294 = (2.0f * (0.000407678192f - dsp->fConst293));
	dsp->fConst295 = (1.0f / (((dsp->fConst246 + 0.168404877f) / dsp->fConst245) + 1.06935835f));
	dsp->fConst296 = (2.0f * (53.5361519f - dsp->fConst274));
	dsp->fConst297 = (1.0f / (((dsp->fConst246 + 0.51247865f) / dsp->fConst245) + 0.689621389f));
	dsp->fConst298 = (2.0f * (7.62173128f - dsp->fConst274));
	dsp->fConst299 = (1.0f / (((dsp->fConst246 + 0.782413065f) / dsp->fConst245) + 0.245291501f));
	dsp->fConst300 = (9.99999975e-05f / dsp->fConst248);
	dsp->fConst301 = (2.0f * (0.000433227193f - dsp->fConst300));
	dsp->fConst302 = (((dsp->fConst246 + -0.782413065f) / dsp->fConst245) + 0.245291501f);
	dsp->fConst303 = (2.0f * (0.245291501f - dsp->fConst274));
	dsp->fConst304 = (dsp->fConst300 + 0.000433227193f);
	dsp->fConst305 = (((dsp->fConst246 + -0.51247865f) / dsp->fConst245) + 0.689621389f);
	dsp->fConst306 = (2.0f * (0.689621389f - dsp->fConst274));
	dsp->fConst307 = (dsp->fConst274 + 7.62173128f);
	dsp->fConst308 = (((dsp->fConst246 + -0.168404877f) / dsp->fConst245) + 1.06935835f);
	dsp->fConst309 = (2.0f * (1.06935835f - dsp->fConst274));
	dsp->fConst310 = (dsp->fConst274 + 53.5361519f);
	dsp->fConst311 = (((dsp->fConst284 + -3.18972731f) / dsp->fConst283) + 4.07678175f);
	dsp->fConst312 = (1.0f / dsp->fConst286);
	dsp->fConst313 = (2.0f * (4.07678175f - dsp->fConst312));
	dsp->fConst314 = (dsp->fConst293 + 0.000407678192f);
	dsp->fConst315 = (((dsp->fConst284 + -0.743130445f) / dsp->fConst283) + 1.4500711f);
	dsp->fConst316 = (2.0f * (1.4500711f - dsp->fConst312));
	dsp->fConst317 = (dsp->fConst290 + 1.4500711f);
	dsp->fConst318 = (((dsp->fConst284 + -0.157482162f) / dsp->fConst283) + 0.935140193f);
	dsp->fConst319 = (2.0f * (0.935140193f - dsp->fConst312));
	dsp->fConst320 = (dsp->fConst287 + 0.935140193f);
	dsp->fConst321 = tanf((4986.96729f / dsp->fConst0));
	dsp->fConst322 = (1.0f / dsp->fConst321);
	dsp->fConst323 = (1.0f / (((dsp->fConst322 + 0.157482162f) / dsp->fConst321) + 0.935140193f));
	dsp->fConst324 = mydsp_faustpower2_f(dsp->fConst321);
	dsp->fConst325 = (50.0638084f / dsp->fConst324);
	dsp->fConst326 = (2.0f * (0.935140193f - dsp->fConst325));
	dsp->fConst327 = (1.0f / (((dsp->fConst322 + 0.743130445f) / dsp->fConst321) + 1.4500711f));
	dsp->fConst328 = (11.0520525f / dsp->fConst324);
	dsp->fConst329 = (2.0f * (1.4500711f - dsp->fConst328));
	dsp->fConst330 = (1.0f / (((dsp->fConst322 + 3.18972731f) / dsp->fConst321) + 4.07678175f));
	dsp->fConst331 = (0.00176617282f / dsp->fConst324);
	dsp->fConst332 = (2.0f * (0.000407678192f - dsp->fConst331));
	dsp->fConst333 = (1.0f / (((dsp->fConst284 + 0.168404877f) / dsp->fConst283) + 1.06935835f));
	dsp->fConst334 = (2.0f * (53.5361519f - dsp->fConst312));
	dsp->fConst335 = (1.0f / (((dsp->fConst284 + 0.51247865f) / dsp->fConst283) + 0.689621389f));
	dsp->fConst336 = (2.0f * (7.62173128f - dsp->fConst312));
	dsp->fConst337 = (1.0f / (((dsp->fConst284 + 0.782413065f) / dsp->fConst283) + 0.245291501f));
	dsp->fConst338 = (9.99999975e-05f / dsp->fConst286);
	dsp->fConst339 = (2.0f * (0.000433227193f - dsp->fConst338));
	dsp->fConst340 = (((dsp->fConst284 + -0.782413065f) / dsp->fConst283) + 0.245291501f);
	dsp->fConst341 = (2.0f * (0.245291501f - dsp->fConst312));
	dsp->fConst342 = (dsp->fConst338 + 0.000433227193f);
	dsp->fConst343 = (((dsp->fConst284 + -0.51247865f) / dsp->fConst283) + 0.689621389f);
	dsp->fConst344 = (2.0f * (0.689621389f - dsp->fConst312));
	dsp->fConst345 = (dsp->fConst312 + 7.62173128f);
	dsp->fConst346 = (((dsp->fConst284 + -0.168404877f) / dsp->fConst283) + 1.06935835f);
	dsp->fConst347 = (2.0f * (1.06935835f - dsp->fConst312));
	dsp->fConst348 = (dsp->fConst312 + 53.5361519f);
	dsp->fConst349 = (((dsp->fConst322 + -3.18972731f) / dsp->fConst321) + 4.07678175f);
	dsp->fConst350 = (1.0f / dsp->fConst324);
	dsp->fConst351 = (2.0f * (4.07678175f - dsp->fConst350));
	dsp->fConst352 = (dsp->fConst331 + 0.000407678192f);
	dsp->fConst353 = (((dsp->fConst322 + -0.743130445f) / dsp->fConst321) + 1.4500711f);
	dsp->fConst354 = (2.0f * (1.4500711f - dsp->fConst350));
	dsp->fConst355 = (dsp->fConst328 + 1.4500711f);
	dsp->fConst356 = (((dsp->fConst322 + -0.157482162f) / dsp->fConst321) + 0.935140193f);
	dsp->fConst357 = (2.0f * (0.935140193f - dsp->fConst350));
	dsp->fConst358 = (dsp->fConst325 + 0.935140193f);
	dsp->fConst359 = tanf((3141.59277f / dsp->fConst0));
	dsp->fConst360 = (1.0f / dsp->fConst359);
	dsp->fConst361 = (1.0f / (((dsp->fConst360 + 0.157482162f) / dsp->fConst359) + 0.935140193f));
	dsp->fConst362 = mydsp_faustpower2_f(dsp->fConst359);
	dsp->fConst363 = (50.0638084f / dsp->fConst362);
	dsp->fConst364 = (2.0f * (0.935140193f - dsp->fConst363));
	dsp->fConst365 = (1.0f / (((dsp->fConst360 + 0.743130445f) / dsp->fConst359) + 1.4500711f));
	dsp->fConst366 = (11.0520525f / dsp->fConst362);
	dsp->fConst367 = (2.0f * (1.4500711f - dsp->fConst366));
	dsp->fConst368 = (1.0f / (((dsp->fConst360 + 3.18972731f) / dsp->fConst359) + 4.07678175f));
	dsp->fConst369 = (0.00176617282f / dsp->fConst362);
	dsp->fConst370 = (2.0f * (0.000407678192f - dsp->fConst369));
	dsp->fConst371 = (1.0f / (((dsp->fConst322 + 0.168404877f) / dsp->fConst321) + 1.06935835f));
	dsp->fConst372 = (2.0f * (53.5361519f - dsp->fConst350));
	dsp->fConst373 = (1.0f / (((dsp->fConst322 + 0.51247865f) / dsp->fConst321) + 0.689621389f));
	dsp->fConst374 = (2.0f * (7.62173128f - dsp->fConst350));
	dsp->fConst375 = (1.0f / (((dsp->fConst322 + 0.782413065f) / dsp->fConst321) + 0.245291501f));
	dsp->fConst376 = (9.99999975e-05f / dsp->fConst324);
	dsp->fConst377 = (2.0f * (0.000433227193f - dsp->fConst376));
	dsp->fConst378 = (((dsp->fConst322 + -0.782413065f) / dsp->fConst321) + 0.245291501f);
	dsp->fConst379 = (2.0f * (0.245291501f - dsp->fConst350));
	dsp->fConst380 = (dsp->fConst376 + 0.000433227193f);
	dsp->fConst381 = (((dsp->fConst322 + -0.51247865f) / dsp->fConst321) + 0.689621389f);
	dsp->fConst382 = (2.0f * (0.689621389f - dsp->fConst350));
	dsp->fConst383 = (dsp->fConst350 + 7.62173128f);
	dsp->fConst384 = (((dsp->fConst322 + -0.168404877f) / dsp->fConst321) + 1.06935835f);
	dsp->fConst385 = (2.0f * (1.06935835f - dsp->fConst350));
	dsp->fConst386 = (dsp->fConst350 + 53.5361519f);
	dsp->fConst387 = (((dsp->fConst360 + -3.18972731f) / dsp->fConst359) + 4.07678175f);
	dsp->fConst388 = (1.0f / dsp->fConst362);
	dsp->fConst389 = (2.0f * (4.07678175f - dsp->fConst388));
	dsp->fConst390 = (dsp->fConst369 + 0.000407678192f);
	dsp->fConst391 = (((dsp->fConst360 + -0.743130445f) / dsp->fConst359) + 1.4500711f);
	dsp->fConst392 = (2.0f * (1.4500711f - dsp->fConst388));
	dsp->fConst393 = (dsp->fConst366 + 1.4500711f);
	dsp->fConst394 = (((dsp->fConst360 + -0.157482162f) / dsp->fConst359) + 0.935140193f);
	dsp->fConst395 = (2.0f * (0.935140193f - dsp->fConst388));
	dsp->fConst396 = (dsp->fConst363 + 0.935140193f);
	dsp->fConst397 = tanf((1979.07935f / dsp->fConst0));
	dsp->fConst398 = (1.0f / dsp->fConst397);
	dsp->fConst399 = (1.0f / (((dsp->fConst398 + 0.157482162f) / dsp->fConst397) + 0.935140193f));
	dsp->fConst400 = mydsp_faustpower2_f(dsp->fConst397);
	dsp->fConst401 = (50.0638084f / dsp->fConst400);
	dsp->fConst402 = (2.0f * (0.935140193f - dsp->fConst401));
	dsp->fConst403 = (1.0f / (((dsp->fConst398 + 0.743130445f) / dsp->fConst397) + 1.4500711f));
	dsp->fConst404 = (11.0520525f / dsp->fConst400);
	dsp->fConst405 = (2.0f * (1.4500711f - dsp->fConst404));
	dsp->fConst406 = (1.0f / (((dsp->fConst398 + 3.18972731f) / dsp->fConst397) + 4.07678175f));
	dsp->fConst407 = (0.00176617282f / dsp->fConst400);
	dsp->fConst408 = (2.0f * (0.000407678192f - dsp->fConst407));
	dsp->fConst409 = (1.0f / (((dsp->fConst360 + 0.168404877f) / dsp->fConst359) + 1.06935835f));
	dsp->fConst410 = (2.0f * (53.5361519f - dsp->fConst388));
	dsp->fConst411 = (1.0f / (((dsp->fConst360 + 0.51247865f) / dsp->fConst359) + 0.689621389f));
	dsp->fConst412 = (2.0f * (7.62173128f - dsp->fConst388));
	dsp->fConst413 = (1.0f / (((dsp->fConst360 + 0.782413065f) / dsp->fConst359) + 0.245291501f));
	dsp->fConst414 = (9.99999975e-05f / dsp->fConst362);
	dsp->fConst415 = (2.0f * (0.000433227193f - dsp->fConst414));
	dsp->fConst416 = (((dsp->fConst360 + -0.782413065f) / dsp->fConst359) + 0.245291501f);
	dsp->fConst417 = (2.0f * (0.245291501f - dsp->fConst388));
	dsp->fConst418 = (dsp->fConst414 + 0.000433227193f);
	dsp->fConst419 = (((dsp->fConst360 + -0.51247865f) / dsp->fConst359) + 0.689621389f);
	dsp->fConst420 = (2.0f * (0.689621389f - dsp->fConst388));
	dsp->fConst421 = (dsp->fConst388 + 7.62173128f);
	dsp->fConst422 = (((dsp->fConst360 + -0.168404877f) / dsp->fConst359) + 1.06935835f);
	dsp->fConst423 = (2.0f * (1.06935835f - dsp->fConst388));
	dsp->fConst424 = (dsp->fConst388 + 53.5361519f);
	dsp->fConst425 = (((dsp->fConst398 + -3.18972731f) / dsp->fConst397) + 4.07678175f);
	dsp->fConst426 = (1.0f / dsp->fConst400);
	dsp->fConst427 = (2.0f * (4.07678175f - dsp->fConst426));
	dsp->fConst428 = (dsp->fConst407 + 0.000407678192f);
	dsp->fConst429 = (((dsp->fConst398 + -0.743130445f) / dsp->fConst397) + 1.4500711f);
	dsp->fConst430 = (2.0f * (1.4500711f - dsp->fConst426));
	dsp->fConst431 = (dsp->fConst404 + 1.4500711f);
	dsp->fConst432 = (((dsp->fConst398 + -0.157482162f) / dsp->fConst397) + 0.935140193f);
	dsp->fConst433 = (2.0f * (0.935140193f - dsp->fConst426));
	dsp->fConst434 = (dsp->fConst401 + 0.935140193f);
	dsp->fConst435 = tanf((1246.74182f / dsp->fConst0));
	dsp->fConst436 = (1.0f / dsp->fConst435);
	dsp->fConst437 = (1.0f / (((dsp->fConst436 + 0.157482162f) / dsp->fConst435) + 0.935140193f));
	dsp->fConst438 = mydsp_faustpower2_f(dsp->fConst435);
	dsp->fConst439 = (50.0638084f / dsp->fConst438);
	dsp->fConst440 = (2.0f * (0.935140193f - dsp->fConst439));
	dsp->fConst441 = (1.0f / (((dsp->fConst436 + 0.743130445f) / dsp->fConst435) + 1.4500711f));
	dsp->fConst442 = (11.0520525f / dsp->fConst438);
	dsp->fConst443 = (2.0f * (1.4500711f - dsp->fConst442));
	dsp->fConst444 = (1.0f / (((dsp->fConst436 + 3.18972731f) / dsp->fConst435) + 4.07678175f));
	dsp->fConst445 = (0.00176617282f / dsp->fConst438);
	dsp->fConst446 = (2.0f * (0.000407678192f - dsp->fConst445));
	dsp->fConst447 = (1.0f / (((dsp->fConst398 + 0.168404877f) / dsp->fConst397) + 1.06935835f));
	dsp->fConst448 = (2.0f * (53.5361519f - dsp->fConst426));
	dsp->fConst449 = (1.0f / (((dsp->fConst398 + 0.51247865f) / dsp->fConst397) + 0.689621389f));
	dsp->fConst450 = (2.0f * (7.62173128f - dsp->fConst426));
	dsp->fConst451 = (1.0f / (((dsp->fConst398 + 0.782413065f) / dsp->fConst397) + 0.245291501f));
	dsp->fConst452 = (9.99999975e-05f / dsp->fConst400);
	dsp->fConst453 = (2.0f * (0.000433227193f - dsp->fConst452));
	dsp->fConst454 = (((dsp->fConst398 + -0.782413065f) / dsp->fConst397) + 0.245291501f);
	dsp->fConst455 = (2.0f * (0.245291501f - dsp->fConst426));
	dsp->fConst456 = (dsp->fConst452 + 0.000433227193f);
	dsp->fConst457 = (((dsp->fConst398 + -0.51247865f) / dsp->fConst397) + 0.689621389f);
	dsp->fConst458 = (2.0f * (0.689621389f - dsp->fConst426));
	dsp->fConst459 = (dsp->fConst426 + 7.62173128f);
	dsp->fConst460 = (((dsp->fConst398 + -0.168404877f) / dsp->fConst397) + 1.06935835f);
	dsp->fConst461 = (2.0f * (1.06935835f - dsp->fConst426));
	dsp->fConst462 = (dsp->fConst426 + 53.5361519f);
	dsp->fConst463 = (((dsp->fConst436 + -3.18972731f) / dsp->fConst435) + 4.07678175f);
	dsp->fConst464 = (1.0f / dsp->fConst438);
	dsp->fConst465 = (2.0f * (4.07678175f - dsp->fConst464));
	dsp->fConst466 = (dsp->fConst445 + 0.000407678192f);
	dsp->fConst467 = (((dsp->fConst436 + -0.743130445f) / dsp->fConst435) + 1.4500711f);
	dsp->fConst468 = (2.0f * (1.4500711f - dsp->fConst464));
	dsp->fConst469 = (dsp->fConst442 + 1.4500711f);
	dsp->fConst470 = (((dsp->fConst436 + -0.157482162f) / dsp->fConst435) + 0.935140193f);
	dsp->fConst471 = (2.0f * (0.935140193f - dsp->fConst464));
	dsp->fConst472 = (dsp->fConst439 + 0.935140193f);
	dsp->fConst473 = tanf((785.398193f / dsp->fConst0));
	dsp->fConst474 = (1.0f / dsp->fConst473);
	dsp->fConst475 = (1.0f / (((dsp->fConst474 + 0.157482162f) / dsp->fConst473) + 0.935140193f));
	dsp->fConst476 = mydsp_faustpower2_f(dsp->fConst473);
	dsp->fConst477 = (50.0638084f / dsp->fConst476);
	dsp->fConst478 = (2.0f * (0.935140193f - dsp->fConst477));
	dsp->fConst479 = (1.0f / (((dsp->fConst474 + 0.743130445f) / dsp->fConst473) + 1.4500711f));
	dsp->fConst480 = (11.0520525f / dsp->fConst476);
	dsp->fConst481 = (2.0f * (1.4500711f - dsp->fConst480));
	dsp->fConst482 = (1.0f / (((dsp->fConst474 + 3.18972731f) / dsp->fConst473) + 4.07678175f));
	dsp->fConst483 = (0.00176617282f / dsp->fConst476);
	dsp->fConst484 = (2.0f * (0.000407678192f - dsp->fConst483));
	dsp->fConst485 = (1.0f / (((dsp->fConst436 + 0.168404877f) / dsp->fConst435) + 1.06935835f));
	dsp->fConst486 = (2.0f * (53.5361519f - dsp->fConst464));
	dsp->fConst487 = (1.0f / (((dsp->fConst436 + 0.51247865f) / dsp->fConst435) + 0.689621389f));
	dsp->fConst488 = (2.0f * (7.62173128f - dsp->fConst464));
	dsp->fConst489 = (1.0f / (((dsp->fConst436 + 0.782413065f) / dsp->fConst435) + 0.245291501f));
	dsp->fConst490 = (9.99999975e-05f / dsp->fConst438);
	dsp->fConst491 = (2.0f * (0.000433227193f - dsp->fConst490));
	dsp->fConst492 = (((dsp->fConst436 + -0.782413065f) / dsp->fConst435) + 0.245291501f);
	dsp->fConst493 = (2.0f * (0.245291501f - dsp->fConst464));
	dsp->fConst494 = (dsp->fConst490 + 0.000433227193f);
	dsp->fConst495 = (((dsp->fConst436 + -0.51247865f) / dsp->fConst435) + 0.689621389f);
	dsp->fConst496 = (2.0f * (0.689621389f - dsp->fConst464));
	dsp->fConst497 = (dsp->fConst464 + 7.62173128f);
	dsp->fConst498 = (((dsp->fConst436 + -0.168404877f) / dsp->fConst435) + 1.06935835f);
	dsp->fConst499 = (2.0f * (1.06935835f - dsp->fConst464));
	dsp->fConst500 = (dsp->fConst464 + 53.5361519f);
	dsp->fConst501 = (((dsp->fConst474 + -3.18972731f) / dsp->fConst473) + 4.07678175f);
	dsp->fConst502 = (1.0f / dsp->fConst476);
	dsp->fConst503 = (2.0f * (4.07678175f - dsp->fConst502));
	dsp->fConst504 = (dsp->fConst483 + 0.000407678192f);
	dsp->fConst505 = (((dsp->fConst474 + -0.743130445f) / dsp->fConst473) + 1.4500711f);
	dsp->fConst506 = (2.0f * (1.4500711f - dsp->fConst502));
	dsp->fConst507 = (dsp->fConst480 + 1.4500711f);
	dsp->fConst508 = (((dsp->fConst474 + -0.157482162f) / dsp->fConst473) + 0.935140193f);
	dsp->fConst509 = (2.0f * (0.935140193f - dsp->fConst502));
	dsp->fConst510 = (dsp->fConst477 + 0.935140193f);
	dsp->fConst511 = tanf((494.769836f / dsp->fConst0));
	dsp->fConst512 = (1.0f / dsp->fConst511);
	dsp->fConst513 = (1.0f / (((dsp->fConst512 + 0.157482162f) / dsp->fConst511) + 0.935140193f));
	dsp->fConst514 = mydsp_faustpower2_f(dsp->fConst511);
	dsp->fConst515 = (50.0638084f / dsp->fConst514);
	dsp->fConst516 = (2.0f * (0.935140193f - dsp->fConst515));
	dsp->fConst517 = (1.0f / (((dsp->fConst512 + 0.743130445f) / dsp->fConst511) + 1.4500711f));
	dsp->fConst518 = (11.0520525f / dsp->fConst514);
	dsp->fConst519 = (2.0f * (1.4500711f - dsp->fConst518));
	dsp->fConst520 = (1.0f / (((dsp->fConst512 + 3.18972731f) / dsp->fConst511) + 4.07678175f));
	dsp->fConst521 = (0.00176617282f / dsp->fConst514);
	dsp->fConst522 = (2.0f * (0.000407678192f - dsp->fConst521));
	dsp->fConst523 = (1.0f / (((dsp->fConst474 + 0.168404877f) / dsp->fConst473) + 1.06935835f));
	dsp->fConst524 = (2.0f * (53.5361519f - dsp->fConst502));
	dsp->fConst525 = (1.0f / (((dsp->fConst474 + 0.51247865f) / dsp->fConst473) + 0.689621389f));
	dsp->fConst526 = (2.0f * (7.62173128f - dsp->fConst502));
	dsp->fConst527 = (1.0f / (((dsp->fConst474 + 0.782413065f) / dsp->fConst473) + 0.245291501f));
	dsp->fConst528 = (9.99999975e-05f / dsp->fConst476);
	dsp->fConst529 = (2.0f * (0.000433227193f - dsp->fConst528));
	dsp->fConst530 = (((dsp->fConst474 + -0.782413065f) / dsp->fConst473) + 0.245291501f);
	dsp->fConst531 = (2.0f * (0.245291501f - dsp->fConst502));
	dsp->fConst532 = (dsp->fConst528 + 0.000433227193f);
	dsp->fConst533 = (((dsp->fConst474 + -0.51247865f) / dsp->fConst473) + 0.689621389f);
	dsp->fConst534 = (2.0f * (0.689621389f - dsp->fConst502));
	dsp->fConst535 = (dsp->fConst502 + 7.62173128f);
	dsp->fConst536 = (((dsp->fConst474 + -0.168404877f) / dsp->fConst473) + 1.06935835f);
	dsp->fConst537 = (2.0f * (1.06935835f - dsp->fConst502));
	dsp->fConst538 = (dsp->fConst502 + 53.5361519f);
	dsp->fConst539 = (((dsp->fConst512 + -3.18972731f) / dsp->fConst511) + 4.07678175f);
	dsp->fConst540 = (1.0f / dsp->fConst514);
	dsp->fConst541 = (2.0f * (4.07678175f - dsp->fConst540));
	dsp->fConst542 = (dsp->fConst521 + 0.000407678192f);
	dsp->fConst543 = (((dsp->fConst512 + -0.743130445f) / dsp->fConst511) + 1.4500711f);
	dsp->fConst544 = (2.0f * (1.4500711f - dsp->fConst540));
	dsp->fConst545 = (dsp->fConst518 + 1.4500711f);
	dsp->fConst546 = (((dsp->fConst512 + -0.157482162f) / dsp->fConst511) + 0.935140193f);
	dsp->fConst547 = (2.0f * (0.935140193f - dsp->fConst540));
	dsp->fConst548 = (dsp->fConst515 + 0.935140193f);
	dsp->fConst549 = tanf((311.685455f / dsp->fConst0));
	dsp->fConst550 = (1.0f / dsp->fConst549);
	dsp->fConst551 = (1.0f / (((dsp->fConst550 + 0.157482162f) / dsp->fConst549) + 0.935140193f));
	dsp->fConst552 = mydsp_faustpower2_f(dsp->fConst549);
	dsp->fConst553 = (50.0638084f / dsp->fConst552);
	dsp->fConst554 = (2.0f * (0.935140193f - dsp->fConst553));
	dsp->fConst555 = (1.0f / (((dsp->fConst550 + 0.743130445f) / dsp->fConst549) + 1.4500711f));
	dsp->fConst556 = (11.0520525f / dsp->fConst552);
	dsp->fConst557 = (2.0f * (1.4500711f - dsp->fConst556));
	dsp->fConst558 = (1.0f / (((dsp->fConst550 + 3.18972731f) / dsp->fConst549) + 4.07678175f));
	dsp->fConst559 = (0.00176617282f / dsp->fConst552);
	dsp->fConst560 = (2.0f * (0.000407678192f - dsp->fConst559));
	dsp->fConst561 = (1.0f / (((dsp->fConst512 + 0.168404877f) / dsp->fConst511) + 1.06935835f));
	dsp->fConst562 = (2.0f * (53.5361519f - dsp->fConst540));
	dsp->fConst563 = (1.0f / (((dsp->fConst512 + 0.51247865f) / dsp->fConst511) + 0.689621389f));
	dsp->fConst564 = (2.0f * (7.62173128f - dsp->fConst540));
	dsp->fConst565 = (1.0f / (((dsp->fConst512 + 0.782413065f) / dsp->fConst511) + 0.245291501f));
	dsp->fConst566 = (9.99999975e-05f / dsp->fConst514);
	dsp->fConst567 = (2.0f * (0.000433227193f - dsp->fConst566));
	dsp->fConst568 = (((dsp->fConst512 + -0.782413065f) / dsp->fConst511) + 0.245291501f);
	dsp->fConst569 = (2.0f * (0.245291501f - dsp->fConst540));
	dsp->fConst570 = (dsp->fConst566 + 0.000433227193f);
	dsp->fConst571 = (((dsp->fConst512 + -0.51247865f) / dsp->fConst511) + 0.689621389f);
	dsp->fConst572 = (2.0f * (0.689621389f - dsp->fConst540));
	dsp->fConst573 = (dsp->fConst540 + 7.62173128f);
	dsp->fConst574 = (((dsp->fConst512 + -0.168404877f) / dsp->fConst511) + 1.06935835f);
	dsp->fConst575 = (2.0f * (1.06935835f - dsp->fConst540));
	dsp->fConst576 = (dsp->fConst540 + 53.5361519f);
	dsp->fConst577 = (((dsp->fConst550 + -3.18972731f) / dsp->fConst549) + 4.07678175f);
	dsp->fConst578 = (1.0f / dsp->fConst552);
	dsp->fConst579 = (2.0f * (4.07678175f - dsp->fConst578));
	dsp->fConst580 = (dsp->fConst559 + 0.000407678192f);
	dsp->fConst581 = (((dsp->fConst550 + -0.743130445f) / dsp->fConst549) + 1.4500711f);
	dsp->fConst582 = (2.0f * (1.4500711f - dsp->fConst578));
	dsp->fConst583 = (dsp->fConst556 + 1.4500711f);
	dsp->fConst584 = (((dsp->fConst550 + -0.157482162f) / dsp->fConst549) + 0.935140193f);
	dsp->fConst585 = (2.0f * (0.935140193f - dsp->fConst578));
	dsp->fConst586 = (dsp->fConst553 + 0.935140193f);
	dsp->fConst587 = tanf((196.349548f / dsp->fConst0));
	dsp->fConst588 = (1.0f / dsp->fConst587);
	dsp->fConst589 = (1.0f / (((dsp->fConst588 + 0.157482162f) / dsp->fConst587) + 0.935140193f));
	dsp->fConst590 = mydsp_faustpower2_f(dsp->fConst587);
	dsp->fConst591 = (50.0638084f / dsp->fConst590);
	dsp->fConst592 = (2.0f * (0.935140193f - dsp->fConst591));
	dsp->fConst593 = (1.0f / (((dsp->fConst588 + 0.743130445f) / dsp->fConst587) + 1.4500711f));
	dsp->fConst594 = (11.0520525f / dsp->fConst590);
	dsp->fConst595 = (2.0f * (1.4500711f - dsp->fConst594));
	dsp->fConst596 = (1.0f / (((dsp->fConst588 + 3.18972731f) / dsp->fConst587) + 4.07678175f));
	dsp->fConst597 = (0.00176617282f / dsp->fConst590);
	dsp->fConst598 = (2.0f * (0.000407678192f - dsp->fConst597));
	dsp->fConst599 = (1.0f / (((dsp->fConst550 + 0.168404877f) / dsp->fConst549) + 1.06935835f));
	dsp->fConst600 = (2.0f * (53.5361519f - dsp->fConst578));
	dsp->fConst601 = (1.0f / (((dsp->fConst550 + 0.51247865f) / dsp->fConst549) + 0.689621389f));
	dsp->fConst602 = (2.0f * (7.62173128f - dsp->fConst578));
	dsp->fConst603 = (1.0f / (((dsp->fConst550 + 0.782413065f) / dsp->fConst549) + 0.245291501f));
	dsp->fConst604 = (9.99999975e-05f / dsp->fConst552);
	dsp->fConst605 = (2.0f * (0.000433227193f - dsp->fConst604));
	dsp->fConst606 = (((dsp->fConst550 + -0.782413065f) / dsp->fConst549) + 0.245291501f);
	dsp->fConst607 = (2.0f * (0.245291501f - dsp->fConst578));
	dsp->fConst608 = (dsp->fConst604 + 0.000433227193f);
	dsp->fConst609 = (((dsp->fConst550 + -0.51247865f) / dsp->fConst549) + 0.689621389f);
	dsp->fConst610 = (2.0f * (0.689621389f - dsp->fConst578));
	dsp->fConst611 = (dsp->fConst578 + 7.62173128f);
	dsp->fConst612 = (((dsp->fConst550 + -0.168404877f) / dsp->fConst549) + 1.06935835f);
	dsp->fConst613 = (2.0f * (1.06935835f - dsp->fConst578));
	dsp->fConst614 = (dsp->fConst578 + 53.5361519f);
	dsp->fConst615 = (((dsp->fConst588 + -3.18972731f) / dsp->fConst587) + 4.07678175f);
	dsp->fConst616 = (1.0f / dsp->fConst590);
	dsp->fConst617 = (2.0f * (4.07678175f - dsp->fConst616));
	dsp->fConst618 = (dsp->fConst597 + 0.000407678192f);
	dsp->fConst619 = (((dsp->fConst588 + -0.743130445f) / dsp->fConst587) + 1.4500711f);
	dsp->fConst620 = (2.0f * (1.4500711f - dsp->fConst616));
	dsp->fConst621 = (dsp->fConst594 + 1.4500711f);
	dsp->fConst622 = (((dsp->fConst588 + -0.157482162f) / dsp->fConst587) + 0.935140193f);
	dsp->fConst623 = (2.0f * (0.935140193f - dsp->fConst616));
	dsp->fConst624 = (dsp->fConst591 + 0.935140193f);
	dsp->fConst625 = tanf((123.692459f / dsp->fConst0));
	dsp->fConst626 = (1.0f / dsp->fConst625);
	dsp->fConst627 = (1.0f / (((dsp->fConst626 + 0.157482162f) / dsp->fConst625) + 0.935140193f));
	dsp->fConst628 = mydsp_faustpower2_f(dsp->fConst625);
	dsp->fConst629 = (50.0638084f / dsp->fConst628);
	dsp->fConst630 = (2.0f * (0.935140193f - dsp->fConst629));
	dsp->fConst631 = (1.0f / (((dsp->fConst626 + 0.743130445f) / dsp->fConst625) + 1.4500711f));
	dsp->fConst632 = (11.0520525f / dsp->fConst628);
	dsp->fConst633 = (2.0f * (1.4500711f - dsp->fConst632));
	dsp->fConst634 = (1.0f / (((dsp->fConst626 + 3.18972731f) / dsp->fConst625) + 4.07678175f));
	dsp->fConst635 = (0.00176617282f / dsp->fConst628);
	dsp->fConst636 = (2.0f * (0.000407678192f - dsp->fConst635));
	dsp->fConst637 = (1.0f / (((dsp->fConst588 + 0.168404877f) / dsp->fConst587) + 1.06935835f));
	dsp->fConst638 = (2.0f * (53.5361519f - dsp->fConst616));
	dsp->fConst639 = (1.0f / (((dsp->fConst588 + 0.51247865f) / dsp->fConst587) + 0.689621389f));
	dsp->fConst640 = (2.0f * (7.62173128f - dsp->fConst616));
	dsp->fConst641 = (1.0f / (((dsp->fConst588 + 0.782413065f) / dsp->fConst587) + 0.245291501f));
	dsp->fConst642 = (9.99999975e-05f / dsp->fConst590);
	dsp->fConst643 = (2.0f * (0.000433227193f - dsp->fConst642));
	dsp->fConst644 = (((dsp->fConst588 + -0.782413065f) / dsp->fConst587) + 0.245291501f);
	dsp->fConst645 = (2.0f * (0.245291501f - dsp->fConst616));
	dsp->fConst646 = (dsp->fConst642 + 0.000433227193f);
	dsp->fConst647 = (((dsp->fConst588 + -0.51247865f) / dsp->fConst587) + 0.689621389f);
	dsp->fConst648 = (2.0f * (0.689621389f - dsp->fConst616));
	dsp->fConst649 = (dsp->fConst616 + 7.62173128f);
	dsp->fConst650 = (((dsp->fConst588 + -0.168404877f) / dsp->fConst587) + 1.06935835f);
	dsp->fConst651 = (2.0f * (1.06935835f - dsp->fConst616));
	dsp->fConst652 = (dsp->fConst616 + 53.5361519f);
	dsp->fConst653 = (((dsp->fConst626 + -3.18972731f) / dsp->fConst625) + 4.07678175f);
	dsp->fConst654 = (1.0f / dsp->fConst628);
	dsp->fConst655 = (2.0f * (4.07678175f - dsp->fConst654));
	dsp->fConst656 = (dsp->fConst635 + 0.000407678192f);
	dsp->fConst657 = (((dsp->fConst626 + -0.743130445f) / dsp->fConst625) + 1.4500711f);
	dsp->fConst658 = (2.0f * (1.4500711f - dsp->fConst654));
	dsp->fConst659 = (dsp->fConst632 + 1.4500711f);
	dsp->fConst660 = (((dsp->fConst626 + -0.157482162f) / dsp->fConst625) + 0.935140193f);
	dsp->fConst661 = (2.0f * (0.935140193f - dsp->fConst654));
	dsp->fConst662 = (dsp->fConst629 + 0.935140193f);
	dsp->fConst663 = (1.0f / (((dsp->fConst626 + 0.168404877f) / dsp->fConst625) + 1.06935835f));
	dsp->fConst664 = (2.0f * (53.5361519f - dsp->fConst654));
	dsp->fConst665 = (1.0f / (((dsp->fConst626 + 0.51247865f) / dsp->fConst625) + 0.689621389f));
	dsp->fConst666 = (2.0f * (7.62173128f - dsp->fConst654));
	dsp->fConst667 = (1.0f / (((dsp->fConst626 + 0.782413065f) / dsp->fConst625) + 0.245291501f));
	dsp->fConst668 = (9.99999975e-05f / dsp->fConst628);
	dsp->fConst669 = (2.0f * (0.000433227193f - dsp->fConst668));
	dsp->fConst670 = (((dsp->fConst626 + -0.782413065f) / dsp->fConst625) + 0.245291501f);
	dsp->fConst671 = (2.0f * (0.245291501f - dsp->fConst654));
	dsp->fConst672 = (dsp->fConst668 + 0.000433227193f);
	dsp->fConst673 = (((dsp->fConst626 + -0.51247865f) / dsp->fConst625) + 0.689621389f);
	dsp->fConst674 = (2.0f * (0.689621389f - dsp->fConst654));
	dsp->fConst675 = (dsp->fConst654 + 7.62173128f);
	dsp->fConst676 = (((dsp->fConst626 + -0.168404877f) / dsp->fConst625) + 1.06935835f);
	dsp->fConst677 = (2.0f * (1.06935835f - dsp->fConst654));
	dsp->fConst678 = (dsp->fConst654 + 53.5361519f);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "graphicEqLab");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "SAWTOOTH OSCILLATOR");
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "tooltip", "Sawtooth   waveform amplitude");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider0, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Amplitude", &dsp->fVslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider1, "unit", "PK");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "Frequency", &dsp->fVslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "style", "knob");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
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
	ui_interface->declare(ui_interface->uiInterface, &dsp->fEntry0, "tooltip", "Order of sawtootn aliasing   suppression");
	ui_interface->addNumEntry(ui_interface->uiInterface, "Saw Order", &dsp->fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
	ui_interface->declare(ui_interface->uiInterface, 0, "7", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "Alternate Signals");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox2, "0", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Noise (White or Pink - uses only Amplitude control on   the left)", &dsp->fCheckbox2);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox3, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Pink instead of White Noise (also called 1/f Noise)", &dsp->fCheckbox3);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox1, "2", "");
	ui_interface->addCheckButton(ui_interface->uiInterface, "External Signal Input (overrides Sawtooth/Noise   selection above)", &dsp->fCheckbox1);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "2", "");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, 0, "tooltip", "See Faust's filters.lib for documentation and references");
	ui_interface->openVerticalBox(ui_interface->uiInterface, "CONSTANT-Q FILTER BANK (Butterworth dyadic tree)");
	ui_interface->declare(ui_interface->uiInterface, 0, "0", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "0", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fCheckbox0, "tooltip", "When this is checked, the filter-bank has no effect");
	ui_interface->addCheckButton(ui_interface->uiInterface, "Bypass", &dsp->fCheckbox0);
	ui_interface->closeBox(ui_interface->uiInterface);
	ui_interface->declare(ui_interface->uiInterface, 0, "1", "");
	ui_interface->openHorizontalBox(ui_interface->uiInterface, "0x00");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider14, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider14, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider14, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider14, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider13, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider13, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider13, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider13, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider12, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider12, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider12, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider12, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider11, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider11, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider11, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider11, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider10, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider10, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider9, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider9, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider8, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider8, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider7, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider7, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider6, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider6, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "tooltip", "Bandpass filter   gain in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVslider5, "unit", "dB");
	ui_interface->addVerticalSlider(ui_interface->uiInterface, "0x00", &dsp->fVslider5, -10.0f, -70.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
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
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2b0397a0", &dsp->fVbargraph14, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "1", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph13, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2b027e40", &dsp->fVbargraph13, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "2", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph12, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2b005cf0", &dsp->fVbargraph12, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "3", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph11, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2afdfc20", &dsp->fVbargraph11, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "4", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph10, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2afbdad0", &dsp->fVbargraph10, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "5", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph9, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2af9b980", &dsp->fVbargraph9, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "6", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph8, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2af79830", &dsp->fVbargraph8, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "7", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph7, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2af576e0", &dsp->fVbargraph7, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "8", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph6, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2af35590", &dsp->fVbargraph6, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "9", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph5, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2af13440", &dsp->fVbargraph5, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "10", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph4, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2aeed370", &dsp->fVbargraph4, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "11", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph3, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2aecb220", &dsp->fVbargraph3, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "12", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph2, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2aea90d0", &dsp->fVbargraph2, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "13", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph1, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2ae86f80", &dsp->fVbargraph1, -50.0f, 10.0f);
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "14", "");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "tooltip", "Spectral Band Level in dB");
	ui_interface->declare(ui_interface->uiInterface, &dsp->fVbargraph0, "unit", "dB");
	ui_interface->addVerticalBargraph(ui_interface->uiInterface, "0x7fcb2ae63da0", &dsp->fVbargraph0, -50.0f, 10.0f);
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
	float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * (float)dsp->fVslider0)));
	int iSlow5 = (int)(float)dsp->fCheckbox1;
	int iSlow6 = (int)(float)dsp->fCheckbox2;
	int iSlow7 = (int)((float)dsp->fEntry0 + -1.0f);
	int iSlow8 = (iSlow7 >= 2);
	int iSlow9 = (iSlow7 >= 1);
	float fSlow10 = expf((0.0f - (dsp->fConst24 / (float)dsp->fVslider2)));
	float fSlow11 = (440.0f * (powf(2.0f, (0.0833333358f * ((float)dsp->fVslider1 + -49.0f))) * (1.0f - fSlow10)));
	int iSlow12 = (iSlow7 >= 3);
	float fSlow13 = ((0.00999999978f * (float)dsp->fVslider3) + 1.0f);
	float fSlow14 = ((0.00999999978f * (float)dsp->fVslider4) + 1.0f);
	int iSlow15 = (int)(float)dsp->fCheckbox3;
	float fSlow16 = (0.00100000005f * (float)dsp->fVslider5);
	float fSlow17 = (0.00100000005f * (float)dsp->fVslider6);
	float fSlow18 = (0.00100000005f * (float)dsp->fVslider7);
	float fSlow19 = (0.00100000005f * (float)dsp->fVslider8);
	float fSlow20 = (0.00100000005f * (float)dsp->fVslider9);
	float fSlow21 = (0.00100000005f * (float)dsp->fVslider10);
	float fSlow22 = (0.00100000005f * (float)dsp->fVslider11);
	float fSlow23 = (0.00100000005f * (float)dsp->fVslider12);
	float fSlow24 = (0.00100000005f * (float)dsp->fVslider13);
	float fSlow25 = (0.00100000005f * (float)dsp->fVslider14);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec15[0] = (fSlow4 + (0.999000013f * dsp->fRec15[1]));
			dsp->fRec17[0] = (fSlow11 + (fSlow10 * dsp->fRec17[1]));
			float fTemp0 = max(20.0f, fabsf(dsp->fRec17[0]));
			dsp->fVec1[0] = fTemp0;
			float fTemp1 = (dsp->fRec16[1] + (dsp->fConst24 * dsp->fVec1[1]));
			dsp->fRec16[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * dsp->fRec16[0]);
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
			float fTemp10 = max(20.0f, fabsf((fSlow13 * dsp->fRec17[0])));
			dsp->fVec8[0] = fTemp10;
			float fTemp11 = (dsp->fRec18[1] + (dsp->fConst24 * dsp->fVec8[1]));
			dsp->fRec18[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (2.0f * dsp->fRec18[0]);
			float fTemp13 = (fTemp12 + -1.0f);
			float fTemp14 = mydsp_faustpower2_f(fTemp13);
			dsp->fVec9[0] = fTemp14;
			float fTemp15 = mydsp_faustpower3_f(fTemp13);
			dsp->fVec10[0] = (fTemp15 + (1.0f - fTemp12));
			float fTemp16 = ((fTemp15 + (1.0f - (fTemp12 + dsp->fVec10[1]))) / fTemp10);
			dsp->fVec11[0] = fTemp16;
			float fTemp17 = (fTemp14 * (fTemp14 + -2.0f));
			dsp->fVec12[0] = fTemp17;
			float fTemp18 = ((fTemp17 - dsp->fVec12[1]) / fTemp10);
			dsp->fVec13[0] = fTemp18;
			float fTemp19 = ((fTemp18 - dsp->fVec13[1]) / fTemp10);
			dsp->fVec14[0] = fTemp19;
			float fTemp20 = max(20.0f, fabsf((fSlow14 * dsp->fRec17[0])));
			dsp->fVec15[0] = fTemp20;
			float fTemp21 = (dsp->fRec19[1] + (dsp->fConst24 * dsp->fVec15[1]));
			dsp->fRec19[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (2.0f * dsp->fRec19[0]);
			float fTemp23 = (fTemp22 + -1.0f);
			float fTemp24 = mydsp_faustpower2_f(fTemp23);
			dsp->fVec16[0] = fTemp24;
			float fTemp25 = mydsp_faustpower3_f(fTemp23);
			dsp->fVec17[0] = (fTemp25 + (1.0f - fTemp22));
			float fTemp26 = ((fTemp25 + (1.0f - (fTemp22 + dsp->fVec17[1]))) / fTemp20);
			dsp->fVec18[0] = fTemp26;
			float fTemp27 = (fTemp24 * (fTemp24 + -2.0f));
			dsp->fVec19[0] = fTemp27;
			float fTemp28 = ((fTemp27 - dsp->fVec19[1]) / fTemp20);
			dsp->fVec20[0] = fTemp28;
			float fTemp29 = ((fTemp28 - dsp->fVec20[1]) / fTemp20);
			dsp->fVec21[0] = fTemp29;
			dsp->iRec20[0] = ((1103515245 * dsp->iRec20[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * (float)dsp->iRec20[0]);
			dsp->fRec21[0] = (((0.522189379f * dsp->fRec21[3]) + (fTemp30 + (2.49495602f * dsp->fRec21[1]))) - (2.0172658f * dsp->fRec21[2]));
			float fTemp31 = (dsp->fRec15[0] * (iSlow5?(float)input0[i]:(iSlow6?(iSlow15?(((0.0499220341f * dsp->fRec21[0]) + (0.0506126992f * dsp->fRec21[2])) - ((0.0959935337f * dsp->fRec21[1]) + (0.00440878607f * dsp->fRec21[3]))):fTemp30):(0.333333343f * (dsp->fRec15[0] * (((iSlow8?(iSlow12?(dsp->fConst27 * (((float)dsp->iVec0[3] * (fTemp9 - dsp->fVec7[1])) / fTemp0)):(dsp->fConst26 * (((float)dsp->iVec0[2] * (fTemp6 - dsp->fVec4[1])) / fTemp0))):(iSlow9?(dsp->fConst25 * (((float)dsp->iVec0[1] * (fTemp4 - dsp->fVec2[1])) / fTemp0)):fTemp3)) + (iSlow8?(iSlow12?(dsp->fConst27 * (((float)dsp->iVec0[3] * (fTemp19 - dsp->fVec14[1])) / fTemp10)):(dsp->fConst26 * (((float)dsp->iVec0[2] * (fTemp16 - dsp->fVec11[1])) / fTemp10))):(iSlow9?(dsp->fConst25 * (((float)dsp->iVec0[1] * (fTemp14 - dsp->fVec9[1])) / fTemp10)):fTemp13))) + (iSlow8?(iSlow12?(dsp->fConst27 * (((float)dsp->iVec0[3] * (fTemp29 - dsp->fVec21[1])) / fTemp20)):(dsp->fConst26 * (((float)dsp->iVec0[2] * (fTemp26 - dsp->fVec18[1])) / fTemp20))):(iSlow9?(dsp->fConst25 * (((float)dsp->iVec0[1] * (fTemp24 - dsp->fVec16[1])) / fTemp20)):fTemp23))))))));
			float fTemp32 = (iSlow3?0.0f:fTemp31);
			dsp->fVec22[0] = fTemp32;
			dsp->fRec14[0] = ((dsp->fConst22 * dsp->fRec14[1]) + (dsp->fConst23 * ((dsp->fConst15 * fTemp32) + (dsp->fConst28 * dsp->fVec22[1]))));
			dsp->fRec13[0] = (dsp->fRec14[0] - (dsp->fConst20 * ((dsp->fConst29 * dsp->fRec13[1]) + (dsp->fConst30 * dsp->fRec13[2]))));
			dsp->fRec12[0] = ((dsp->fConst20 * (((dsp->fConst19 * dsp->fRec13[1]) + (dsp->fConst18 * dsp->fRec13[0])) + (dsp->fConst18 * dsp->fRec13[2]))) - (dsp->fConst17 * ((dsp->fConst29 * dsp->fRec12[1]) + (dsp->fConst31 * dsp->fRec12[2]))));
			float fTemp33 = (dsp->fConst37 * dsp->fRec11[1]);
			dsp->fRec11[0] = ((dsp->fConst17 * (((dsp->fConst19 * dsp->fRec12[1]) + (dsp->fConst18 * dsp->fRec12[0])) + (dsp->fConst18 * dsp->fRec12[2]))) - (dsp->fConst34 * ((dsp->fConst35 * dsp->fRec11[2]) + fTemp33)));
			float fTemp34 = (dsp->fConst43 * dsp->fRec10[1]);
			dsp->fRec10[0] = ((dsp->fRec11[2] + (dsp->fConst34 * (fTemp33 + (dsp->fConst35 * dsp->fRec11[0])))) - (dsp->fConst40 * ((dsp->fConst41 * dsp->fRec10[2]) + fTemp34)));
			float fTemp35 = (dsp->fConst49 * dsp->fRec9[1]);
			dsp->fRec9[0] = ((dsp->fRec10[2] + (dsp->fConst40 * (fTemp34 + (dsp->fConst41 * dsp->fRec10[0])))) - (dsp->fConst46 * ((dsp->fConst47 * dsp->fRec9[2]) + fTemp35)));
			float fTemp36 = (dsp->fConst55 * dsp->fRec8[1]);
			dsp->fRec8[0] = ((dsp->fRec9[2] + (dsp->fConst46 * (fTemp35 + (dsp->fConst47 * dsp->fRec9[0])))) - (dsp->fConst52 * ((dsp->fConst53 * dsp->fRec8[2]) + fTemp36)));
			float fTemp37 = (dsp->fConst61 * dsp->fRec7[1]);
			dsp->fRec7[0] = ((dsp->fRec8[2] + (dsp->fConst52 * (fTemp36 + (dsp->fConst53 * dsp->fRec8[0])))) - (dsp->fConst58 * ((dsp->fConst59 * dsp->fRec7[2]) + fTemp37)));
			float fTemp38 = (dsp->fConst67 * dsp->fRec6[1]);
			dsp->fRec6[0] = ((dsp->fRec7[2] + (dsp->fConst58 * (fTemp37 + (dsp->fConst59 * dsp->fRec7[0])))) - (dsp->fConst64 * ((dsp->fConst65 * dsp->fRec6[2]) + fTemp38)));
			float fTemp39 = (dsp->fConst73 * dsp->fRec5[1]);
			dsp->fRec5[0] = ((dsp->fRec6[2] + (dsp->fConst64 * (fTemp38 + (dsp->fConst65 * dsp->fRec6[0])))) - (dsp->fConst70 * ((dsp->fConst71 * dsp->fRec5[2]) + fTemp39)));
			float fTemp40 = (dsp->fConst79 * dsp->fRec4[1]);
			dsp->fRec4[0] = ((dsp->fRec5[2] + (dsp->fConst70 * (fTemp39 + (dsp->fConst71 * dsp->fRec5[0])))) - (dsp->fConst76 * ((dsp->fConst77 * dsp->fRec4[2]) + fTemp40)));
			dsp->fRec22[0] = (fSlow16 + (0.999000013f * dsp->fRec22[1]));
			dsp->fRec35[0] = ((dsp->fConst22 * dsp->fRec35[1]) + (dsp->fConst23 * (fTemp32 + dsp->fVec22[1])));
			dsp->fRec34[0] = (dsp->fRec35[0] - (dsp->fConst20 * ((dsp->fConst29 * dsp->fRec34[1]) + (dsp->fConst30 * dsp->fRec34[2]))));
			dsp->fRec33[0] = ((dsp->fConst20 * (dsp->fRec34[2] + (dsp->fRec34[0] + (2.0f * dsp->fRec34[1])))) - (dsp->fConst17 * ((dsp->fConst29 * dsp->fRec33[1]) + (dsp->fConst31 * dsp->fRec33[2]))));
			float fTemp41 = (dsp->fRec33[2] + (dsp->fRec33[0] + (2.0f * dsp->fRec33[1])));
			dsp->fVec23[0] = fTemp41;
			dsp->fRec32[0] = ((dsp->fConst85 * dsp->fRec32[1]) + (dsp->fConst86 * ((dsp->fConst75 * fTemp41) + (dsp->fConst87 * dsp->fVec23[1]))));
			dsp->fRec31[0] = (dsp->fRec32[0] - (dsp->fConst83 * ((dsp->fConst79 * dsp->fRec31[1]) + (dsp->fConst88 * dsp->fRec31[2]))));
			dsp->fRec30[0] = ((dsp->fConst83 * (((dsp->fConst78 * dsp->fRec31[0]) + (dsp->fConst82 * dsp->fRec31[1])) + (dsp->fConst78 * dsp->fRec31[2]))) - (dsp->fConst81 * ((dsp->fConst79 * dsp->fRec30[1]) + (dsp->fConst89 * dsp->fRec30[2]))));
			float fTemp42 = (dsp->fConst37 * dsp->fRec29[1]);
			dsp->fRec29[0] = ((dsp->fConst81 * (((dsp->fConst82 * dsp->fRec30[1]) + (dsp->fConst78 * dsp->fRec30[0])) + (dsp->fConst78 * dsp->fRec30[2]))) - (dsp->fConst34 * (fTemp42 + (dsp->fConst35 * dsp->fRec29[2]))));
			float fTemp43 = (dsp->fConst43 * dsp->fRec28[1]);
			dsp->fRec28[0] = ((dsp->fRec29[2] + (dsp->fConst34 * (fTemp42 + (dsp->fConst35 * dsp->fRec29[0])))) - (dsp->fConst40 * (fTemp43 + (dsp->fConst41 * dsp->fRec28[2]))));
			float fTemp44 = (dsp->fConst49 * dsp->fRec27[1]);
			dsp->fRec27[0] = ((dsp->fRec28[2] + (dsp->fConst40 * (fTemp43 + (dsp->fConst41 * dsp->fRec28[0])))) - (dsp->fConst46 * (fTemp44 + (dsp->fConst47 * dsp->fRec27[2]))));
			float fTemp45 = (dsp->fConst55 * dsp->fRec26[1]);
			dsp->fRec26[0] = ((dsp->fRec27[2] + (dsp->fConst46 * (fTemp44 + (dsp->fConst47 * dsp->fRec27[0])))) - (dsp->fConst52 * (fTemp45 + (dsp->fConst53 * dsp->fRec26[2]))));
			float fTemp46 = (dsp->fConst61 * dsp->fRec25[1]);
			dsp->fRec25[0] = ((dsp->fRec26[2] + (dsp->fConst52 * (fTemp45 + (dsp->fConst53 * dsp->fRec26[0])))) - (dsp->fConst58 * (fTemp46 + (dsp->fConst59 * dsp->fRec25[2]))));
			float fTemp47 = (dsp->fConst67 * dsp->fRec24[1]);
			dsp->fRec24[0] = ((dsp->fRec25[2] + (dsp->fConst58 * (fTemp46 + (dsp->fConst59 * dsp->fRec25[0])))) - (dsp->fConst64 * (fTemp47 + (dsp->fConst65 * dsp->fRec24[2]))));
			float fTemp48 = (dsp->fConst73 * dsp->fRec23[1]);
			dsp->fRec23[0] = ((dsp->fRec24[2] + (dsp->fConst64 * (fTemp47 + (dsp->fConst65 * dsp->fRec24[0])))) - (dsp->fConst70 * (fTemp48 + (dsp->fConst71 * dsp->fRec23[2]))));
			dsp->fRec36[0] = (fSlow17 + (0.999000013f * dsp->fRec36[1]));
			dsp->fRec48[0] = ((dsp->fConst85 * dsp->fRec48[1]) + (dsp->fConst86 * (fTemp41 + dsp->fVec23[1])));
			dsp->fRec47[0] = (dsp->fRec48[0] - (dsp->fConst83 * ((dsp->fConst79 * dsp->fRec47[1]) + (dsp->fConst88 * dsp->fRec47[2]))));
			dsp->fRec46[0] = ((dsp->fConst83 * (dsp->fRec47[2] + (dsp->fRec47[0] + (2.0f * dsp->fRec47[1])))) - (dsp->fConst81 * ((dsp->fConst79 * dsp->fRec46[1]) + (dsp->fConst89 * dsp->fRec46[2]))));
			float fTemp49 = (dsp->fRec46[2] + (dsp->fRec46[0] + (2.0f * dsp->fRec46[1])));
			dsp->fVec24[0] = fTemp49;
			dsp->fRec45[0] = ((dsp->fConst95 * dsp->fRec45[1]) + (dsp->fConst96 * ((dsp->fConst69 * fTemp49) + (dsp->fConst97 * dsp->fVec24[1]))));
			dsp->fRec44[0] = (dsp->fRec45[0] - (dsp->fConst93 * ((dsp->fConst73 * dsp->fRec44[1]) + (dsp->fConst98 * dsp->fRec44[2]))));
			dsp->fRec43[0] = ((dsp->fConst93 * (((dsp->fConst72 * dsp->fRec44[0]) + (dsp->fConst92 * dsp->fRec44[1])) + (dsp->fConst72 * dsp->fRec44[2]))) - (dsp->fConst91 * ((dsp->fConst73 * dsp->fRec43[1]) + (dsp->fConst99 * dsp->fRec43[2]))));
			float fTemp50 = (dsp->fConst37 * dsp->fRec42[1]);
			dsp->fRec42[0] = ((dsp->fConst91 * (((dsp->fConst92 * dsp->fRec43[1]) + (dsp->fConst72 * dsp->fRec43[0])) + (dsp->fConst72 * dsp->fRec43[2]))) - (dsp->fConst34 * (fTemp50 + (dsp->fConst35 * dsp->fRec42[2]))));
			float fTemp51 = (dsp->fConst43 * dsp->fRec41[1]);
			dsp->fRec41[0] = ((dsp->fRec42[2] + (dsp->fConst34 * (fTemp50 + (dsp->fConst35 * dsp->fRec42[0])))) - (dsp->fConst40 * (fTemp51 + (dsp->fConst41 * dsp->fRec41[2]))));
			float fTemp52 = (dsp->fConst49 * dsp->fRec40[1]);
			dsp->fRec40[0] = ((dsp->fRec41[2] + (dsp->fConst40 * (fTemp51 + (dsp->fConst41 * dsp->fRec41[0])))) - (dsp->fConst46 * (fTemp52 + (dsp->fConst47 * dsp->fRec40[2]))));
			float fTemp53 = (dsp->fConst55 * dsp->fRec39[1]);
			dsp->fRec39[0] = ((dsp->fRec40[2] + (dsp->fConst46 * (fTemp52 + (dsp->fConst47 * dsp->fRec40[0])))) - (dsp->fConst52 * (fTemp53 + (dsp->fConst53 * dsp->fRec39[2]))));
			float fTemp54 = (dsp->fConst61 * dsp->fRec38[1]);
			dsp->fRec38[0] = ((dsp->fRec39[2] + (dsp->fConst52 * (fTemp53 + (dsp->fConst53 * dsp->fRec39[0])))) - (dsp->fConst58 * (fTemp54 + (dsp->fConst59 * dsp->fRec38[2]))));
			float fTemp55 = (dsp->fConst67 * dsp->fRec37[1]);
			dsp->fRec37[0] = ((dsp->fRec38[2] + (dsp->fConst58 * (fTemp54 + (dsp->fConst59 * dsp->fRec38[0])))) - (dsp->fConst64 * (fTemp55 + (dsp->fConst65 * dsp->fRec37[2]))));
			dsp->fRec49[0] = (fSlow18 + (0.999000013f * dsp->fRec49[1]));
			dsp->fRec60[0] = ((dsp->fConst95 * dsp->fRec60[1]) + (dsp->fConst96 * (fTemp49 + dsp->fVec24[1])));
			dsp->fRec59[0] = (dsp->fRec60[0] - (dsp->fConst93 * ((dsp->fConst73 * dsp->fRec59[1]) + (dsp->fConst98 * dsp->fRec59[2]))));
			dsp->fRec58[0] = ((dsp->fConst93 * (dsp->fRec59[2] + (dsp->fRec59[0] + (2.0f * dsp->fRec59[1])))) - (dsp->fConst91 * ((dsp->fConst73 * dsp->fRec58[1]) + (dsp->fConst99 * dsp->fRec58[2]))));
			float fTemp56 = (dsp->fRec58[2] + (dsp->fRec58[0] + (2.0f * dsp->fRec58[1])));
			dsp->fVec25[0] = fTemp56;
			dsp->fRec57[0] = ((dsp->fConst105 * dsp->fRec57[1]) + (dsp->fConst106 * ((dsp->fConst63 * fTemp56) + (dsp->fConst107 * dsp->fVec25[1]))));
			dsp->fRec56[0] = (dsp->fRec57[0] - (dsp->fConst103 * ((dsp->fConst67 * dsp->fRec56[1]) + (dsp->fConst108 * dsp->fRec56[2]))));
			dsp->fRec55[0] = ((dsp->fConst103 * (((dsp->fConst66 * dsp->fRec56[0]) + (dsp->fConst102 * dsp->fRec56[1])) + (dsp->fConst66 * dsp->fRec56[2]))) - (dsp->fConst101 * ((dsp->fConst67 * dsp->fRec55[1]) + (dsp->fConst109 * dsp->fRec55[2]))));
			float fTemp57 = (dsp->fConst37 * dsp->fRec54[1]);
			dsp->fRec54[0] = ((dsp->fConst101 * (((dsp->fConst102 * dsp->fRec55[1]) + (dsp->fConst66 * dsp->fRec55[0])) + (dsp->fConst66 * dsp->fRec55[2]))) - (dsp->fConst34 * (fTemp57 + (dsp->fConst35 * dsp->fRec54[2]))));
			float fTemp58 = (dsp->fConst43 * dsp->fRec53[1]);
			dsp->fRec53[0] = ((dsp->fRec54[2] + (dsp->fConst34 * (fTemp57 + (dsp->fConst35 * dsp->fRec54[0])))) - (dsp->fConst40 * (fTemp58 + (dsp->fConst41 * dsp->fRec53[2]))));
			float fTemp59 = (dsp->fConst49 * dsp->fRec52[1]);
			dsp->fRec52[0] = ((dsp->fRec53[2] + (dsp->fConst40 * (fTemp58 + (dsp->fConst41 * dsp->fRec53[0])))) - (dsp->fConst46 * (fTemp59 + (dsp->fConst47 * dsp->fRec52[2]))));
			float fTemp60 = (dsp->fConst55 * dsp->fRec51[1]);
			dsp->fRec51[0] = ((dsp->fRec52[2] + (dsp->fConst46 * (fTemp59 + (dsp->fConst47 * dsp->fRec52[0])))) - (dsp->fConst52 * (fTemp60 + (dsp->fConst53 * dsp->fRec51[2]))));
			float fTemp61 = (dsp->fConst61 * dsp->fRec50[1]);
			dsp->fRec50[0] = ((dsp->fRec51[2] + (dsp->fConst52 * (fTemp60 + (dsp->fConst53 * dsp->fRec51[0])))) - (dsp->fConst58 * (fTemp61 + (dsp->fConst59 * dsp->fRec50[2]))));
			dsp->fRec61[0] = (fSlow19 + (0.999000013f * dsp->fRec61[1]));
			dsp->fRec71[0] = ((dsp->fConst105 * dsp->fRec71[1]) + (dsp->fConst106 * (fTemp56 + dsp->fVec25[1])));
			dsp->fRec70[0] = (dsp->fRec71[0] - (dsp->fConst103 * ((dsp->fConst67 * dsp->fRec70[1]) + (dsp->fConst108 * dsp->fRec70[2]))));
			dsp->fRec69[0] = ((dsp->fConst103 * (dsp->fRec70[2] + (dsp->fRec70[0] + (2.0f * dsp->fRec70[1])))) - (dsp->fConst101 * ((dsp->fConst67 * dsp->fRec69[1]) + (dsp->fConst109 * dsp->fRec69[2]))));
			float fTemp62 = (dsp->fRec69[2] + (dsp->fRec69[0] + (2.0f * dsp->fRec69[1])));
			dsp->fVec26[0] = fTemp62;
			dsp->fRec68[0] = ((dsp->fConst115 * dsp->fRec68[1]) + (dsp->fConst116 * ((dsp->fConst57 * fTemp62) + (dsp->fConst117 * dsp->fVec26[1]))));
			dsp->fRec67[0] = (dsp->fRec68[0] - (dsp->fConst113 * ((dsp->fConst61 * dsp->fRec67[1]) + (dsp->fConst118 * dsp->fRec67[2]))));
			dsp->fRec66[0] = ((dsp->fConst113 * (((dsp->fConst60 * dsp->fRec67[0]) + (dsp->fConst112 * dsp->fRec67[1])) + (dsp->fConst60 * dsp->fRec67[2]))) - (dsp->fConst111 * ((dsp->fConst61 * dsp->fRec66[1]) + (dsp->fConst119 * dsp->fRec66[2]))));
			float fTemp63 = (dsp->fConst37 * dsp->fRec65[1]);
			dsp->fRec65[0] = ((dsp->fConst111 * (((dsp->fConst112 * dsp->fRec66[1]) + (dsp->fConst60 * dsp->fRec66[0])) + (dsp->fConst60 * dsp->fRec66[2]))) - (dsp->fConst34 * (fTemp63 + (dsp->fConst35 * dsp->fRec65[2]))));
			float fTemp64 = (dsp->fConst43 * dsp->fRec64[1]);
			dsp->fRec64[0] = ((dsp->fRec65[2] + (dsp->fConst34 * (fTemp63 + (dsp->fConst35 * dsp->fRec65[0])))) - (dsp->fConst40 * (fTemp64 + (dsp->fConst41 * dsp->fRec64[2]))));
			float fTemp65 = (dsp->fConst49 * dsp->fRec63[1]);
			dsp->fRec63[0] = ((dsp->fRec64[2] + (dsp->fConst40 * (fTemp64 + (dsp->fConst41 * dsp->fRec64[0])))) - (dsp->fConst46 * (fTemp65 + (dsp->fConst47 * dsp->fRec63[2]))));
			float fTemp66 = (dsp->fConst55 * dsp->fRec62[1]);
			dsp->fRec62[0] = ((dsp->fRec63[2] + (dsp->fConst46 * (fTemp65 + (dsp->fConst47 * dsp->fRec63[0])))) - (dsp->fConst52 * (fTemp66 + (dsp->fConst53 * dsp->fRec62[2]))));
			dsp->fRec72[0] = (fSlow20 + (0.999000013f * dsp->fRec72[1]));
			dsp->fRec81[0] = ((dsp->fConst115 * dsp->fRec81[1]) + (dsp->fConst116 * (fTemp62 + dsp->fVec26[1])));
			dsp->fRec80[0] = (dsp->fRec81[0] - (dsp->fConst113 * ((dsp->fConst61 * dsp->fRec80[1]) + (dsp->fConst118 * dsp->fRec80[2]))));
			dsp->fRec79[0] = ((dsp->fConst113 * (dsp->fRec80[2] + (dsp->fRec80[0] + (2.0f * dsp->fRec80[1])))) - (dsp->fConst111 * ((dsp->fConst61 * dsp->fRec79[1]) + (dsp->fConst119 * dsp->fRec79[2]))));
			float fTemp67 = (dsp->fRec79[2] + (dsp->fRec79[0] + (2.0f * dsp->fRec79[1])));
			dsp->fVec27[0] = fTemp67;
			dsp->fRec78[0] = ((dsp->fConst125 * dsp->fRec78[1]) + (dsp->fConst126 * ((dsp->fConst51 * fTemp67) + (dsp->fConst127 * dsp->fVec27[1]))));
			dsp->fRec77[0] = (dsp->fRec78[0] - (dsp->fConst123 * ((dsp->fConst55 * dsp->fRec77[1]) + (dsp->fConst128 * dsp->fRec77[2]))));
			dsp->fRec76[0] = ((dsp->fConst123 * (((dsp->fConst54 * dsp->fRec77[0]) + (dsp->fConst122 * dsp->fRec77[1])) + (dsp->fConst54 * dsp->fRec77[2]))) - (dsp->fConst121 * ((dsp->fConst55 * dsp->fRec76[1]) + (dsp->fConst129 * dsp->fRec76[2]))));
			float fTemp68 = (dsp->fConst37 * dsp->fRec75[1]);
			dsp->fRec75[0] = ((dsp->fConst121 * (((dsp->fConst122 * dsp->fRec76[1]) + (dsp->fConst54 * dsp->fRec76[0])) + (dsp->fConst54 * dsp->fRec76[2]))) - (dsp->fConst34 * (fTemp68 + (dsp->fConst35 * dsp->fRec75[2]))));
			float fTemp69 = (dsp->fConst43 * dsp->fRec74[1]);
			dsp->fRec74[0] = ((dsp->fRec75[2] + (dsp->fConst34 * (fTemp68 + (dsp->fConst35 * dsp->fRec75[0])))) - (dsp->fConst40 * (fTemp69 + (dsp->fConst41 * dsp->fRec74[2]))));
			float fTemp70 = (dsp->fConst49 * dsp->fRec73[1]);
			dsp->fRec73[0] = ((dsp->fRec74[2] + (dsp->fConst40 * (fTemp69 + (dsp->fConst41 * dsp->fRec74[0])))) - (dsp->fConst46 * (fTemp70 + (dsp->fConst47 * dsp->fRec73[2]))));
			dsp->fRec82[0] = (fSlow21 + (0.999000013f * dsp->fRec82[1]));
			dsp->fRec90[0] = ((dsp->fConst125 * dsp->fRec90[1]) + (dsp->fConst126 * (fTemp67 + dsp->fVec27[1])));
			dsp->fRec89[0] = (dsp->fRec90[0] - (dsp->fConst123 * ((dsp->fConst55 * dsp->fRec89[1]) + (dsp->fConst128 * dsp->fRec89[2]))));
			dsp->fRec88[0] = ((dsp->fConst123 * (dsp->fRec89[2] + (dsp->fRec89[0] + (2.0f * dsp->fRec89[1])))) - (dsp->fConst121 * ((dsp->fConst55 * dsp->fRec88[1]) + (dsp->fConst129 * dsp->fRec88[2]))));
			float fTemp71 = (dsp->fRec88[2] + (dsp->fRec88[0] + (2.0f * dsp->fRec88[1])));
			dsp->fVec28[0] = fTemp71;
			dsp->fRec87[0] = ((dsp->fConst135 * dsp->fRec87[1]) + (dsp->fConst136 * ((dsp->fConst45 * fTemp71) + (dsp->fConst137 * dsp->fVec28[1]))));
			dsp->fRec86[0] = (dsp->fRec87[0] - (dsp->fConst133 * ((dsp->fConst49 * dsp->fRec86[1]) + (dsp->fConst138 * dsp->fRec86[2]))));
			dsp->fRec85[0] = ((dsp->fConst133 * (((dsp->fConst48 * dsp->fRec86[0]) + (dsp->fConst132 * dsp->fRec86[1])) + (dsp->fConst48 * dsp->fRec86[2]))) - (dsp->fConst131 * ((dsp->fConst49 * dsp->fRec85[1]) + (dsp->fConst139 * dsp->fRec85[2]))));
			float fTemp72 = (dsp->fConst37 * dsp->fRec84[1]);
			dsp->fRec84[0] = ((dsp->fConst131 * (((dsp->fConst132 * dsp->fRec85[1]) + (dsp->fConst48 * dsp->fRec85[0])) + (dsp->fConst48 * dsp->fRec85[2]))) - (dsp->fConst34 * (fTemp72 + (dsp->fConst35 * dsp->fRec84[2]))));
			float fTemp73 = (dsp->fConst43 * dsp->fRec83[1]);
			dsp->fRec83[0] = ((dsp->fRec84[2] + (dsp->fConst34 * (fTemp72 + (dsp->fConst35 * dsp->fRec84[0])))) - (dsp->fConst40 * (fTemp73 + (dsp->fConst41 * dsp->fRec83[2]))));
			dsp->fRec91[0] = (fSlow22 + (0.999000013f * dsp->fRec91[1]));
			dsp->fRec98[0] = ((dsp->fConst135 * dsp->fRec98[1]) + (dsp->fConst136 * (fTemp71 + dsp->fVec28[1])));
			dsp->fRec97[0] = (dsp->fRec98[0] - (dsp->fConst133 * ((dsp->fConst49 * dsp->fRec97[1]) + (dsp->fConst138 * dsp->fRec97[2]))));
			dsp->fRec96[0] = ((dsp->fConst133 * (dsp->fRec97[2] + (dsp->fRec97[0] + (2.0f * dsp->fRec97[1])))) - (dsp->fConst131 * ((dsp->fConst49 * dsp->fRec96[1]) + (dsp->fConst139 * dsp->fRec96[2]))));
			float fTemp74 = (dsp->fRec96[2] + (dsp->fRec96[0] + (2.0f * dsp->fRec96[1])));
			dsp->fVec29[0] = fTemp74;
			dsp->fRec95[0] = ((dsp->fConst145 * dsp->fRec95[1]) + (dsp->fConst146 * ((dsp->fConst39 * fTemp74) + (dsp->fConst147 * dsp->fVec29[1]))));
			dsp->fRec94[0] = (dsp->fRec95[0] - (dsp->fConst143 * ((dsp->fConst43 * dsp->fRec94[1]) + (dsp->fConst148 * dsp->fRec94[2]))));
			dsp->fRec93[0] = ((dsp->fConst143 * (((dsp->fConst42 * dsp->fRec94[0]) + (dsp->fConst142 * dsp->fRec94[1])) + (dsp->fConst42 * dsp->fRec94[2]))) - (dsp->fConst141 * ((dsp->fConst43 * dsp->fRec93[1]) + (dsp->fConst149 * dsp->fRec93[2]))));
			float fTemp75 = (dsp->fConst37 * dsp->fRec92[1]);
			dsp->fRec92[0] = ((dsp->fConst141 * (((dsp->fConst142 * dsp->fRec93[1]) + (dsp->fConst42 * dsp->fRec93[0])) + (dsp->fConst42 * dsp->fRec93[2]))) - (dsp->fConst34 * (fTemp75 + (dsp->fConst35 * dsp->fRec92[2]))));
			dsp->fRec99[0] = (fSlow23 + (0.999000013f * dsp->fRec99[1]));
			dsp->fRec105[0] = ((dsp->fConst145 * dsp->fRec105[1]) + (dsp->fConst146 * (fTemp74 + dsp->fVec29[1])));
			dsp->fRec104[0] = (dsp->fRec105[0] - (dsp->fConst143 * ((dsp->fConst43 * dsp->fRec104[1]) + (dsp->fConst148 * dsp->fRec104[2]))));
			dsp->fRec103[0] = ((dsp->fConst143 * (dsp->fRec104[2] + (dsp->fRec104[0] + (2.0f * dsp->fRec104[1])))) - (dsp->fConst141 * ((dsp->fConst43 * dsp->fRec103[1]) + (dsp->fConst149 * dsp->fRec103[2]))));
			float fTemp76 = (dsp->fRec103[2] + (dsp->fRec103[0] + (2.0f * dsp->fRec103[1])));
			dsp->fVec30[0] = fTemp76;
			dsp->fRec102[0] = ((dsp->fConst154 * dsp->fRec102[1]) + (dsp->fConst155 * ((dsp->fConst33 * fTemp76) + (dsp->fConst156 * dsp->fVec30[1]))));
			dsp->fRec101[0] = (dsp->fRec102[0] - (dsp->fConst152 * ((dsp->fConst37 * dsp->fRec101[1]) + (dsp->fConst157 * dsp->fRec101[2]))));
			dsp->fRec100[0] = ((dsp->fConst152 * (((dsp->fConst36 * dsp->fRec101[0]) + (dsp->fConst151 * dsp->fRec101[1])) + (dsp->fConst36 * dsp->fRec101[2]))) - (dsp->fConst150 * ((dsp->fConst37 * dsp->fRec100[1]) + (dsp->fConst158 * dsp->fRec100[2]))));
			dsp->fRec106[0] = (fSlow24 + (0.999000013f * dsp->fRec106[1]));
			dsp->fRec109[0] = ((dsp->fConst154 * dsp->fRec109[1]) + (dsp->fConst155 * (fTemp76 + dsp->fVec30[1])));
			dsp->fRec108[0] = (dsp->fRec109[0] - (dsp->fConst152 * ((dsp->fConst37 * dsp->fRec108[1]) + (dsp->fConst157 * dsp->fRec108[2]))));
			dsp->fRec107[0] = ((dsp->fConst152 * (dsp->fRec108[2] + (dsp->fRec108[0] + (2.0f * dsp->fRec108[1])))) - (dsp->fConst150 * ((dsp->fConst37 * dsp->fRec107[1]) + (dsp->fConst158 * dsp->fRec107[2]))));
			dsp->fRec110[0] = (fSlow25 + (0.999000013f * dsp->fRec110[1]));
			float fTemp77 = (iSlow3?fTemp31:((((((((((dsp->fRec4[2] + (dsp->fConst76 * (fTemp40 + (dsp->fConst77 * dsp->fRec4[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec22[0]))) + ((dsp->fRec23[2] + (dsp->fConst70 * (fTemp48 + (dsp->fConst71 * dsp->fRec23[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec36[0])))) + ((dsp->fRec37[2] + (dsp->fConst64 * (fTemp55 + (dsp->fConst65 * dsp->fRec37[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec49[0])))) + ((dsp->fRec50[2] + (dsp->fConst58 * (fTemp61 + (dsp->fConst59 * dsp->fRec50[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec61[0])))) + ((dsp->fRec62[2] + (dsp->fConst52 * (fTemp66 + (dsp->fConst53 * dsp->fRec62[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec72[0])))) + ((dsp->fRec73[2] + (dsp->fConst46 * (fTemp70 + (dsp->fConst47 * dsp->fRec73[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec82[0])))) + ((dsp->fRec83[2] + (dsp->fConst40 * (fTemp73 + (dsp->fConst41 * dsp->fRec83[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec91[0])))) + ((dsp->fRec92[2] + (dsp->fConst34 * (fTemp75 + (dsp->fConst35 * dsp->fRec92[0])))) * powf(10.0f, (0.0500000007f * dsp->fRec99[0])))) + (dsp->fConst150 * (((((dsp->fConst151 * dsp->fRec100[1]) + (dsp->fConst36 * dsp->fRec100[0])) + (dsp->fConst36 * dsp->fRec100[2])) * powf(10.0f, (0.0500000007f * dsp->fRec106[0]))) + ((dsp->fRec107[2] + (dsp->fRec107[0] + (2.0f * dsp->fRec107[1]))) * powf(10.0f, (0.0500000007f * dsp->fRec110[0])))))));
			dsp->fRec3[0] = (fTemp77 - (dsp->fConst11 * ((dsp->fConst159 * dsp->fRec3[2]) + (dsp->fConst161 * dsp->fRec3[1]))));
			dsp->fRec2[0] = ((dsp->fConst11 * (((dsp->fConst13 * dsp->fRec3[1]) + (dsp->fConst162 * dsp->fRec3[0])) + (dsp->fConst162 * dsp->fRec3[2]))) - (dsp->fConst8 * ((dsp->fConst163 * dsp->fRec2[2]) + (dsp->fConst164 * dsp->fRec2[1]))));
			dsp->fRec1[0] = ((dsp->fConst8 * (((dsp->fConst10 * dsp->fRec2[1]) + (dsp->fConst165 * dsp->fRec2[0])) + (dsp->fConst165 * dsp->fRec2[2]))) - (dsp->fConst4 * ((dsp->fConst166 * dsp->fRec1[2]) + (dsp->fConst167 * dsp->fRec1[1]))));
			dsp->fRec0[0] = ((fSlow1 * dsp->fRec0[1]) + (fSlow2 * fabsf((dsp->fConst4 * (((dsp->fConst7 * dsp->fRec1[1]) + (dsp->fConst168 * dsp->fRec1[0])) + (dsp->fConst168 * dsp->fRec1[2]))))));
			dsp->fVbargraph0 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec0[0]))));
			dsp->fRec117[0] = (fTemp77 - (dsp->fConst185 * ((dsp->fConst188 * dsp->fRec117[2]) + (dsp->fConst189 * dsp->fRec117[1]))));
			dsp->fRec116[0] = ((dsp->fConst185 * (((dsp->fConst187 * dsp->fRec117[1]) + (dsp->fConst190 * dsp->fRec117[0])) + (dsp->fConst190 * dsp->fRec117[2]))) - (dsp->fConst183 * ((dsp->fConst191 * dsp->fRec116[2]) + (dsp->fConst192 * dsp->fRec116[1]))));
			dsp->fRec115[0] = ((dsp->fConst183 * (((dsp->fConst184 * dsp->fRec116[1]) + (dsp->fConst193 * dsp->fRec116[0])) + (dsp->fConst193 * dsp->fRec116[2]))) - (dsp->fConst181 * ((dsp->fConst194 * dsp->fRec115[2]) + (dsp->fConst195 * dsp->fRec115[1]))));
			float fTemp78 = (dsp->fConst181 * (((dsp->fConst182 * dsp->fRec115[1]) + (dsp->fConst196 * dsp->fRec115[0])) + (dsp->fConst196 * dsp->fRec115[2])));
			dsp->fRec114[0] = (fTemp78 - (dsp->fConst178 * ((dsp->fConst197 * dsp->fRec114[2]) + (dsp->fConst199 * dsp->fRec114[1]))));
			dsp->fRec113[0] = ((dsp->fConst178 * (((dsp->fConst180 * dsp->fRec114[1]) + (dsp->fConst200 * dsp->fRec114[0])) + (dsp->fConst200 * dsp->fRec114[2]))) - (dsp->fConst175 * ((dsp->fConst201 * dsp->fRec113[2]) + (dsp->fConst202 * dsp->fRec113[1]))));
			dsp->fRec112[0] = ((dsp->fConst175 * (((dsp->fConst177 * dsp->fRec113[1]) + (dsp->fConst203 * dsp->fRec113[0])) + (dsp->fConst203 * dsp->fRec113[2]))) - (dsp->fConst171 * ((dsp->fConst204 * dsp->fRec112[2]) + (dsp->fConst205 * dsp->fRec112[1]))));
			dsp->fRec111[0] = ((fSlow1 * dsp->fRec111[1]) + (fSlow2 * fabsf((dsp->fConst171 * (((dsp->fConst174 * dsp->fRec112[1]) + (dsp->fConst206 * dsp->fRec112[0])) + (dsp->fConst206 * dsp->fRec112[2]))))));
			dsp->fVbargraph1 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec111[0]))));
			dsp->fRec124[0] = (fTemp78 - (dsp->fConst223 * ((dsp->fConst226 * dsp->fRec124[2]) + (dsp->fConst227 * dsp->fRec124[1]))));
			dsp->fRec123[0] = ((dsp->fConst223 * (((dsp->fConst225 * dsp->fRec124[1]) + (dsp->fConst228 * dsp->fRec124[0])) + (dsp->fConst228 * dsp->fRec124[2]))) - (dsp->fConst221 * ((dsp->fConst229 * dsp->fRec123[2]) + (dsp->fConst230 * dsp->fRec123[1]))));
			dsp->fRec122[0] = ((dsp->fConst221 * (((dsp->fConst222 * dsp->fRec123[1]) + (dsp->fConst231 * dsp->fRec123[0])) + (dsp->fConst231 * dsp->fRec123[2]))) - (dsp->fConst219 * ((dsp->fConst232 * dsp->fRec122[2]) + (dsp->fConst233 * dsp->fRec122[1]))));
			float fTemp79 = (dsp->fConst219 * (((dsp->fConst220 * dsp->fRec122[1]) + (dsp->fConst234 * dsp->fRec122[0])) + (dsp->fConst234 * dsp->fRec122[2])));
			dsp->fRec121[0] = (fTemp79 - (dsp->fConst216 * ((dsp->fConst235 * dsp->fRec121[2]) + (dsp->fConst237 * dsp->fRec121[1]))));
			dsp->fRec120[0] = ((dsp->fConst216 * (((dsp->fConst218 * dsp->fRec121[1]) + (dsp->fConst238 * dsp->fRec121[0])) + (dsp->fConst238 * dsp->fRec121[2]))) - (dsp->fConst213 * ((dsp->fConst239 * dsp->fRec120[2]) + (dsp->fConst240 * dsp->fRec120[1]))));
			dsp->fRec119[0] = ((dsp->fConst213 * (((dsp->fConst215 * dsp->fRec120[1]) + (dsp->fConst241 * dsp->fRec120[0])) + (dsp->fConst241 * dsp->fRec120[2]))) - (dsp->fConst209 * ((dsp->fConst242 * dsp->fRec119[2]) + (dsp->fConst243 * dsp->fRec119[1]))));
			dsp->fRec118[0] = ((fSlow1 * dsp->fRec118[1]) + (fSlow2 * fabsf((dsp->fConst209 * (((dsp->fConst212 * dsp->fRec119[1]) + (dsp->fConst244 * dsp->fRec119[0])) + (dsp->fConst244 * dsp->fRec119[2]))))));
			dsp->fVbargraph2 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec118[0]))));
			dsp->fRec131[0] = (fTemp79 - (dsp->fConst261 * ((dsp->fConst264 * dsp->fRec131[2]) + (dsp->fConst265 * dsp->fRec131[1]))));
			dsp->fRec130[0] = ((dsp->fConst261 * (((dsp->fConst263 * dsp->fRec131[1]) + (dsp->fConst266 * dsp->fRec131[0])) + (dsp->fConst266 * dsp->fRec131[2]))) - (dsp->fConst259 * ((dsp->fConst267 * dsp->fRec130[2]) + (dsp->fConst268 * dsp->fRec130[1]))));
			dsp->fRec129[0] = ((dsp->fConst259 * (((dsp->fConst260 * dsp->fRec130[1]) + (dsp->fConst269 * dsp->fRec130[0])) + (dsp->fConst269 * dsp->fRec130[2]))) - (dsp->fConst257 * ((dsp->fConst270 * dsp->fRec129[2]) + (dsp->fConst271 * dsp->fRec129[1]))));
			float fTemp80 = (dsp->fConst257 * (((dsp->fConst258 * dsp->fRec129[1]) + (dsp->fConst272 * dsp->fRec129[0])) + (dsp->fConst272 * dsp->fRec129[2])));
			dsp->fRec128[0] = (fTemp80 - (dsp->fConst254 * ((dsp->fConst273 * dsp->fRec128[2]) + (dsp->fConst275 * dsp->fRec128[1]))));
			dsp->fRec127[0] = ((dsp->fConst254 * (((dsp->fConst256 * dsp->fRec128[1]) + (dsp->fConst276 * dsp->fRec128[0])) + (dsp->fConst276 * dsp->fRec128[2]))) - (dsp->fConst251 * ((dsp->fConst277 * dsp->fRec127[2]) + (dsp->fConst278 * dsp->fRec127[1]))));
			dsp->fRec126[0] = ((dsp->fConst251 * (((dsp->fConst253 * dsp->fRec127[1]) + (dsp->fConst279 * dsp->fRec127[0])) + (dsp->fConst279 * dsp->fRec127[2]))) - (dsp->fConst247 * ((dsp->fConst280 * dsp->fRec126[2]) + (dsp->fConst281 * dsp->fRec126[1]))));
			dsp->fRec125[0] = ((fSlow1 * dsp->fRec125[1]) + (fSlow2 * fabsf((dsp->fConst247 * (((dsp->fConst250 * dsp->fRec126[1]) + (dsp->fConst282 * dsp->fRec126[0])) + (dsp->fConst282 * dsp->fRec126[2]))))));
			dsp->fVbargraph3 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec125[0]))));
			dsp->fRec138[0] = (fTemp80 - (dsp->fConst299 * ((dsp->fConst302 * dsp->fRec138[2]) + (dsp->fConst303 * dsp->fRec138[1]))));
			dsp->fRec137[0] = ((dsp->fConst299 * (((dsp->fConst301 * dsp->fRec138[1]) + (dsp->fConst304 * dsp->fRec138[0])) + (dsp->fConst304 * dsp->fRec138[2]))) - (dsp->fConst297 * ((dsp->fConst305 * dsp->fRec137[2]) + (dsp->fConst306 * dsp->fRec137[1]))));
			dsp->fRec136[0] = ((dsp->fConst297 * (((dsp->fConst298 * dsp->fRec137[1]) + (dsp->fConst307 * dsp->fRec137[0])) + (dsp->fConst307 * dsp->fRec137[2]))) - (dsp->fConst295 * ((dsp->fConst308 * dsp->fRec136[2]) + (dsp->fConst309 * dsp->fRec136[1]))));
			float fTemp81 = (dsp->fConst295 * (((dsp->fConst296 * dsp->fRec136[1]) + (dsp->fConst310 * dsp->fRec136[0])) + (dsp->fConst310 * dsp->fRec136[2])));
			dsp->fRec135[0] = (fTemp81 - (dsp->fConst292 * ((dsp->fConst311 * dsp->fRec135[2]) + (dsp->fConst313 * dsp->fRec135[1]))));
			dsp->fRec134[0] = ((dsp->fConst292 * (((dsp->fConst294 * dsp->fRec135[1]) + (dsp->fConst314 * dsp->fRec135[0])) + (dsp->fConst314 * dsp->fRec135[2]))) - (dsp->fConst289 * ((dsp->fConst315 * dsp->fRec134[2]) + (dsp->fConst316 * dsp->fRec134[1]))));
			dsp->fRec133[0] = ((dsp->fConst289 * (((dsp->fConst291 * dsp->fRec134[1]) + (dsp->fConst317 * dsp->fRec134[0])) + (dsp->fConst317 * dsp->fRec134[2]))) - (dsp->fConst285 * ((dsp->fConst318 * dsp->fRec133[2]) + (dsp->fConst319 * dsp->fRec133[1]))));
			dsp->fRec132[0] = ((fSlow1 * dsp->fRec132[1]) + (fSlow2 * fabsf((dsp->fConst285 * (((dsp->fConst288 * dsp->fRec133[1]) + (dsp->fConst320 * dsp->fRec133[0])) + (dsp->fConst320 * dsp->fRec133[2]))))));
			dsp->fVbargraph4 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec132[0]))));
			dsp->fRec145[0] = (fTemp81 - (dsp->fConst337 * ((dsp->fConst340 * dsp->fRec145[2]) + (dsp->fConst341 * dsp->fRec145[1]))));
			dsp->fRec144[0] = ((dsp->fConst337 * (((dsp->fConst339 * dsp->fRec145[1]) + (dsp->fConst342 * dsp->fRec145[0])) + (dsp->fConst342 * dsp->fRec145[2]))) - (dsp->fConst335 * ((dsp->fConst343 * dsp->fRec144[2]) + (dsp->fConst344 * dsp->fRec144[1]))));
			dsp->fRec143[0] = ((dsp->fConst335 * (((dsp->fConst336 * dsp->fRec144[1]) + (dsp->fConst345 * dsp->fRec144[0])) + (dsp->fConst345 * dsp->fRec144[2]))) - (dsp->fConst333 * ((dsp->fConst346 * dsp->fRec143[2]) + (dsp->fConst347 * dsp->fRec143[1]))));
			float fTemp82 = (dsp->fConst333 * (((dsp->fConst334 * dsp->fRec143[1]) + (dsp->fConst348 * dsp->fRec143[0])) + (dsp->fConst348 * dsp->fRec143[2])));
			dsp->fRec142[0] = (fTemp82 - (dsp->fConst330 * ((dsp->fConst349 * dsp->fRec142[2]) + (dsp->fConst351 * dsp->fRec142[1]))));
			dsp->fRec141[0] = ((dsp->fConst330 * (((dsp->fConst332 * dsp->fRec142[1]) + (dsp->fConst352 * dsp->fRec142[0])) + (dsp->fConst352 * dsp->fRec142[2]))) - (dsp->fConst327 * ((dsp->fConst353 * dsp->fRec141[2]) + (dsp->fConst354 * dsp->fRec141[1]))));
			dsp->fRec140[0] = ((dsp->fConst327 * (((dsp->fConst329 * dsp->fRec141[1]) + (dsp->fConst355 * dsp->fRec141[0])) + (dsp->fConst355 * dsp->fRec141[2]))) - (dsp->fConst323 * ((dsp->fConst356 * dsp->fRec140[2]) + (dsp->fConst357 * dsp->fRec140[1]))));
			dsp->fRec139[0] = ((fSlow1 * dsp->fRec139[1]) + (fSlow2 * fabsf((dsp->fConst323 * (((dsp->fConst326 * dsp->fRec140[1]) + (dsp->fConst358 * dsp->fRec140[0])) + (dsp->fConst358 * dsp->fRec140[2]))))));
			dsp->fVbargraph5 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec139[0]))));
			dsp->fRec152[0] = (fTemp82 - (dsp->fConst375 * ((dsp->fConst378 * dsp->fRec152[2]) + (dsp->fConst379 * dsp->fRec152[1]))));
			dsp->fRec151[0] = ((dsp->fConst375 * (((dsp->fConst377 * dsp->fRec152[1]) + (dsp->fConst380 * dsp->fRec152[0])) + (dsp->fConst380 * dsp->fRec152[2]))) - (dsp->fConst373 * ((dsp->fConst381 * dsp->fRec151[2]) + (dsp->fConst382 * dsp->fRec151[1]))));
			dsp->fRec150[0] = ((dsp->fConst373 * (((dsp->fConst374 * dsp->fRec151[1]) + (dsp->fConst383 * dsp->fRec151[0])) + (dsp->fConst383 * dsp->fRec151[2]))) - (dsp->fConst371 * ((dsp->fConst384 * dsp->fRec150[2]) + (dsp->fConst385 * dsp->fRec150[1]))));
			float fTemp83 = (dsp->fConst371 * (((dsp->fConst372 * dsp->fRec150[1]) + (dsp->fConst386 * dsp->fRec150[0])) + (dsp->fConst386 * dsp->fRec150[2])));
			dsp->fRec149[0] = (fTemp83 - (dsp->fConst368 * ((dsp->fConst387 * dsp->fRec149[2]) + (dsp->fConst389 * dsp->fRec149[1]))));
			dsp->fRec148[0] = ((dsp->fConst368 * (((dsp->fConst370 * dsp->fRec149[1]) + (dsp->fConst390 * dsp->fRec149[0])) + (dsp->fConst390 * dsp->fRec149[2]))) - (dsp->fConst365 * ((dsp->fConst391 * dsp->fRec148[2]) + (dsp->fConst392 * dsp->fRec148[1]))));
			dsp->fRec147[0] = ((dsp->fConst365 * (((dsp->fConst367 * dsp->fRec148[1]) + (dsp->fConst393 * dsp->fRec148[0])) + (dsp->fConst393 * dsp->fRec148[2]))) - (dsp->fConst361 * ((dsp->fConst394 * dsp->fRec147[2]) + (dsp->fConst395 * dsp->fRec147[1]))));
			dsp->fRec146[0] = ((fSlow1 * dsp->fRec146[1]) + (fSlow2 * fabsf((dsp->fConst361 * (((dsp->fConst364 * dsp->fRec147[1]) + (dsp->fConst396 * dsp->fRec147[0])) + (dsp->fConst396 * dsp->fRec147[2]))))));
			dsp->fVbargraph6 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec146[0]))));
			dsp->fRec159[0] = (fTemp83 - (dsp->fConst413 * ((dsp->fConst416 * dsp->fRec159[2]) + (dsp->fConst417 * dsp->fRec159[1]))));
			dsp->fRec158[0] = ((dsp->fConst413 * (((dsp->fConst415 * dsp->fRec159[1]) + (dsp->fConst418 * dsp->fRec159[0])) + (dsp->fConst418 * dsp->fRec159[2]))) - (dsp->fConst411 * ((dsp->fConst419 * dsp->fRec158[2]) + (dsp->fConst420 * dsp->fRec158[1]))));
			dsp->fRec157[0] = ((dsp->fConst411 * (((dsp->fConst412 * dsp->fRec158[1]) + (dsp->fConst421 * dsp->fRec158[0])) + (dsp->fConst421 * dsp->fRec158[2]))) - (dsp->fConst409 * ((dsp->fConst422 * dsp->fRec157[2]) + (dsp->fConst423 * dsp->fRec157[1]))));
			float fTemp84 = (dsp->fConst409 * (((dsp->fConst410 * dsp->fRec157[1]) + (dsp->fConst424 * dsp->fRec157[0])) + (dsp->fConst424 * dsp->fRec157[2])));
			dsp->fRec156[0] = (fTemp84 - (dsp->fConst406 * ((dsp->fConst425 * dsp->fRec156[2]) + (dsp->fConst427 * dsp->fRec156[1]))));
			dsp->fRec155[0] = ((dsp->fConst406 * (((dsp->fConst408 * dsp->fRec156[1]) + (dsp->fConst428 * dsp->fRec156[0])) + (dsp->fConst428 * dsp->fRec156[2]))) - (dsp->fConst403 * ((dsp->fConst429 * dsp->fRec155[2]) + (dsp->fConst430 * dsp->fRec155[1]))));
			dsp->fRec154[0] = ((dsp->fConst403 * (((dsp->fConst405 * dsp->fRec155[1]) + (dsp->fConst431 * dsp->fRec155[0])) + (dsp->fConst431 * dsp->fRec155[2]))) - (dsp->fConst399 * ((dsp->fConst432 * dsp->fRec154[2]) + (dsp->fConst433 * dsp->fRec154[1]))));
			dsp->fRec153[0] = ((fSlow1 * dsp->fRec153[1]) + (fSlow2 * fabsf((dsp->fConst399 * (((dsp->fConst402 * dsp->fRec154[1]) + (dsp->fConst434 * dsp->fRec154[0])) + (dsp->fConst434 * dsp->fRec154[2]))))));
			dsp->fVbargraph7 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec153[0]))));
			dsp->fRec166[0] = (fTemp84 - (dsp->fConst451 * ((dsp->fConst454 * dsp->fRec166[2]) + (dsp->fConst455 * dsp->fRec166[1]))));
			dsp->fRec165[0] = ((dsp->fConst451 * (((dsp->fConst453 * dsp->fRec166[1]) + (dsp->fConst456 * dsp->fRec166[0])) + (dsp->fConst456 * dsp->fRec166[2]))) - (dsp->fConst449 * ((dsp->fConst457 * dsp->fRec165[2]) + (dsp->fConst458 * dsp->fRec165[1]))));
			dsp->fRec164[0] = ((dsp->fConst449 * (((dsp->fConst450 * dsp->fRec165[1]) + (dsp->fConst459 * dsp->fRec165[0])) + (dsp->fConst459 * dsp->fRec165[2]))) - (dsp->fConst447 * ((dsp->fConst460 * dsp->fRec164[2]) + (dsp->fConst461 * dsp->fRec164[1]))));
			float fTemp85 = (dsp->fConst447 * (((dsp->fConst448 * dsp->fRec164[1]) + (dsp->fConst462 * dsp->fRec164[0])) + (dsp->fConst462 * dsp->fRec164[2])));
			dsp->fRec163[0] = (fTemp85 - (dsp->fConst444 * ((dsp->fConst463 * dsp->fRec163[2]) + (dsp->fConst465 * dsp->fRec163[1]))));
			dsp->fRec162[0] = ((dsp->fConst444 * (((dsp->fConst446 * dsp->fRec163[1]) + (dsp->fConst466 * dsp->fRec163[0])) + (dsp->fConst466 * dsp->fRec163[2]))) - (dsp->fConst441 * ((dsp->fConst467 * dsp->fRec162[2]) + (dsp->fConst468 * dsp->fRec162[1]))));
			dsp->fRec161[0] = ((dsp->fConst441 * (((dsp->fConst443 * dsp->fRec162[1]) + (dsp->fConst469 * dsp->fRec162[0])) + (dsp->fConst469 * dsp->fRec162[2]))) - (dsp->fConst437 * ((dsp->fConst470 * dsp->fRec161[2]) + (dsp->fConst471 * dsp->fRec161[1]))));
			dsp->fRec160[0] = ((fSlow1 * dsp->fRec160[1]) + (fSlow2 * fabsf((dsp->fConst437 * (((dsp->fConst440 * dsp->fRec161[1]) + (dsp->fConst472 * dsp->fRec161[0])) + (dsp->fConst472 * dsp->fRec161[2]))))));
			dsp->fVbargraph8 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec160[0]))));
			dsp->fRec173[0] = (fTemp85 - (dsp->fConst489 * ((dsp->fConst492 * dsp->fRec173[2]) + (dsp->fConst493 * dsp->fRec173[1]))));
			dsp->fRec172[0] = ((dsp->fConst489 * (((dsp->fConst491 * dsp->fRec173[1]) + (dsp->fConst494 * dsp->fRec173[0])) + (dsp->fConst494 * dsp->fRec173[2]))) - (dsp->fConst487 * ((dsp->fConst495 * dsp->fRec172[2]) + (dsp->fConst496 * dsp->fRec172[1]))));
			dsp->fRec171[0] = ((dsp->fConst487 * (((dsp->fConst488 * dsp->fRec172[1]) + (dsp->fConst497 * dsp->fRec172[0])) + (dsp->fConst497 * dsp->fRec172[2]))) - (dsp->fConst485 * ((dsp->fConst498 * dsp->fRec171[2]) + (dsp->fConst499 * dsp->fRec171[1]))));
			float fTemp86 = (dsp->fConst485 * (((dsp->fConst486 * dsp->fRec171[1]) + (dsp->fConst500 * dsp->fRec171[0])) + (dsp->fConst500 * dsp->fRec171[2])));
			dsp->fRec170[0] = (fTemp86 - (dsp->fConst482 * ((dsp->fConst501 * dsp->fRec170[2]) + (dsp->fConst503 * dsp->fRec170[1]))));
			dsp->fRec169[0] = ((dsp->fConst482 * (((dsp->fConst484 * dsp->fRec170[1]) + (dsp->fConst504 * dsp->fRec170[0])) + (dsp->fConst504 * dsp->fRec170[2]))) - (dsp->fConst479 * ((dsp->fConst505 * dsp->fRec169[2]) + (dsp->fConst506 * dsp->fRec169[1]))));
			dsp->fRec168[0] = ((dsp->fConst479 * (((dsp->fConst481 * dsp->fRec169[1]) + (dsp->fConst507 * dsp->fRec169[0])) + (dsp->fConst507 * dsp->fRec169[2]))) - (dsp->fConst475 * ((dsp->fConst508 * dsp->fRec168[2]) + (dsp->fConst509 * dsp->fRec168[1]))));
			dsp->fRec167[0] = ((fSlow1 * dsp->fRec167[1]) + (fSlow2 * fabsf((dsp->fConst475 * (((dsp->fConst478 * dsp->fRec168[1]) + (dsp->fConst510 * dsp->fRec168[0])) + (dsp->fConst510 * dsp->fRec168[2]))))));
			dsp->fVbargraph9 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec167[0]))));
			dsp->fRec180[0] = (fTemp86 - (dsp->fConst527 * ((dsp->fConst530 * dsp->fRec180[2]) + (dsp->fConst531 * dsp->fRec180[1]))));
			dsp->fRec179[0] = ((dsp->fConst527 * (((dsp->fConst529 * dsp->fRec180[1]) + (dsp->fConst532 * dsp->fRec180[0])) + (dsp->fConst532 * dsp->fRec180[2]))) - (dsp->fConst525 * ((dsp->fConst533 * dsp->fRec179[2]) + (dsp->fConst534 * dsp->fRec179[1]))));
			dsp->fRec178[0] = ((dsp->fConst525 * (((dsp->fConst526 * dsp->fRec179[1]) + (dsp->fConst535 * dsp->fRec179[0])) + (dsp->fConst535 * dsp->fRec179[2]))) - (dsp->fConst523 * ((dsp->fConst536 * dsp->fRec178[2]) + (dsp->fConst537 * dsp->fRec178[1]))));
			float fTemp87 = (dsp->fConst523 * (((dsp->fConst524 * dsp->fRec178[1]) + (dsp->fConst538 * dsp->fRec178[0])) + (dsp->fConst538 * dsp->fRec178[2])));
			dsp->fRec177[0] = (fTemp87 - (dsp->fConst520 * ((dsp->fConst539 * dsp->fRec177[2]) + (dsp->fConst541 * dsp->fRec177[1]))));
			dsp->fRec176[0] = ((dsp->fConst520 * (((dsp->fConst522 * dsp->fRec177[1]) + (dsp->fConst542 * dsp->fRec177[0])) + (dsp->fConst542 * dsp->fRec177[2]))) - (dsp->fConst517 * ((dsp->fConst543 * dsp->fRec176[2]) + (dsp->fConst544 * dsp->fRec176[1]))));
			dsp->fRec175[0] = ((dsp->fConst517 * (((dsp->fConst519 * dsp->fRec176[1]) + (dsp->fConst545 * dsp->fRec176[0])) + (dsp->fConst545 * dsp->fRec176[2]))) - (dsp->fConst513 * ((dsp->fConst546 * dsp->fRec175[2]) + (dsp->fConst547 * dsp->fRec175[1]))));
			dsp->fRec174[0] = ((fSlow1 * dsp->fRec174[1]) + (fSlow2 * fabsf((dsp->fConst513 * (((dsp->fConst516 * dsp->fRec175[1]) + (dsp->fConst548 * dsp->fRec175[0])) + (dsp->fConst548 * dsp->fRec175[2]))))));
			dsp->fVbargraph10 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec174[0]))));
			dsp->fRec187[0] = (fTemp87 - (dsp->fConst565 * ((dsp->fConst568 * dsp->fRec187[2]) + (dsp->fConst569 * dsp->fRec187[1]))));
			dsp->fRec186[0] = ((dsp->fConst565 * (((dsp->fConst567 * dsp->fRec187[1]) + (dsp->fConst570 * dsp->fRec187[0])) + (dsp->fConst570 * dsp->fRec187[2]))) - (dsp->fConst563 * ((dsp->fConst571 * dsp->fRec186[2]) + (dsp->fConst572 * dsp->fRec186[1]))));
			dsp->fRec185[0] = ((dsp->fConst563 * (((dsp->fConst564 * dsp->fRec186[1]) + (dsp->fConst573 * dsp->fRec186[0])) + (dsp->fConst573 * dsp->fRec186[2]))) - (dsp->fConst561 * ((dsp->fConst574 * dsp->fRec185[2]) + (dsp->fConst575 * dsp->fRec185[1]))));
			float fTemp88 = (dsp->fConst561 * (((dsp->fConst562 * dsp->fRec185[1]) + (dsp->fConst576 * dsp->fRec185[0])) + (dsp->fConst576 * dsp->fRec185[2])));
			dsp->fRec184[0] = (fTemp88 - (dsp->fConst558 * ((dsp->fConst577 * dsp->fRec184[2]) + (dsp->fConst579 * dsp->fRec184[1]))));
			dsp->fRec183[0] = ((dsp->fConst558 * (((dsp->fConst560 * dsp->fRec184[1]) + (dsp->fConst580 * dsp->fRec184[0])) + (dsp->fConst580 * dsp->fRec184[2]))) - (dsp->fConst555 * ((dsp->fConst581 * dsp->fRec183[2]) + (dsp->fConst582 * dsp->fRec183[1]))));
			dsp->fRec182[0] = ((dsp->fConst555 * (((dsp->fConst557 * dsp->fRec183[1]) + (dsp->fConst583 * dsp->fRec183[0])) + (dsp->fConst583 * dsp->fRec183[2]))) - (dsp->fConst551 * ((dsp->fConst584 * dsp->fRec182[2]) + (dsp->fConst585 * dsp->fRec182[1]))));
			dsp->fRec181[0] = ((fSlow1 * dsp->fRec181[1]) + (fSlow2 * fabsf((dsp->fConst551 * (((dsp->fConst554 * dsp->fRec182[1]) + (dsp->fConst586 * dsp->fRec182[0])) + (dsp->fConst586 * dsp->fRec182[2]))))));
			dsp->fVbargraph11 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec181[0]))));
			dsp->fRec194[0] = (fTemp88 - (dsp->fConst603 * ((dsp->fConst606 * dsp->fRec194[2]) + (dsp->fConst607 * dsp->fRec194[1]))));
			dsp->fRec193[0] = ((dsp->fConst603 * (((dsp->fConst605 * dsp->fRec194[1]) + (dsp->fConst608 * dsp->fRec194[0])) + (dsp->fConst608 * dsp->fRec194[2]))) - (dsp->fConst601 * ((dsp->fConst609 * dsp->fRec193[2]) + (dsp->fConst610 * dsp->fRec193[1]))));
			dsp->fRec192[0] = ((dsp->fConst601 * (((dsp->fConst602 * dsp->fRec193[1]) + (dsp->fConst611 * dsp->fRec193[0])) + (dsp->fConst611 * dsp->fRec193[2]))) - (dsp->fConst599 * ((dsp->fConst612 * dsp->fRec192[2]) + (dsp->fConst613 * dsp->fRec192[1]))));
			float fTemp89 = (dsp->fConst599 * (((dsp->fConst600 * dsp->fRec192[1]) + (dsp->fConst614 * dsp->fRec192[0])) + (dsp->fConst614 * dsp->fRec192[2])));
			dsp->fRec191[0] = (fTemp89 - (dsp->fConst596 * ((dsp->fConst615 * dsp->fRec191[2]) + (dsp->fConst617 * dsp->fRec191[1]))));
			dsp->fRec190[0] = ((dsp->fConst596 * (((dsp->fConst598 * dsp->fRec191[1]) + (dsp->fConst618 * dsp->fRec191[0])) + (dsp->fConst618 * dsp->fRec191[2]))) - (dsp->fConst593 * ((dsp->fConst619 * dsp->fRec190[2]) + (dsp->fConst620 * dsp->fRec190[1]))));
			dsp->fRec189[0] = ((dsp->fConst593 * (((dsp->fConst595 * dsp->fRec190[1]) + (dsp->fConst621 * dsp->fRec190[0])) + (dsp->fConst621 * dsp->fRec190[2]))) - (dsp->fConst589 * ((dsp->fConst622 * dsp->fRec189[2]) + (dsp->fConst623 * dsp->fRec189[1]))));
			dsp->fRec188[0] = ((fSlow1 * dsp->fRec188[1]) + (fSlow2 * fabsf((dsp->fConst589 * (((dsp->fConst592 * dsp->fRec189[1]) + (dsp->fConst624 * dsp->fRec189[0])) + (dsp->fConst624 * dsp->fRec189[2]))))));
			dsp->fVbargraph12 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec188[0]))));
			dsp->fRec201[0] = (fTemp89 - (dsp->fConst641 * ((dsp->fConst644 * dsp->fRec201[2]) + (dsp->fConst645 * dsp->fRec201[1]))));
			dsp->fRec200[0] = ((dsp->fConst641 * (((dsp->fConst643 * dsp->fRec201[1]) + (dsp->fConst646 * dsp->fRec201[0])) + (dsp->fConst646 * dsp->fRec201[2]))) - (dsp->fConst639 * ((dsp->fConst647 * dsp->fRec200[2]) + (dsp->fConst648 * dsp->fRec200[1]))));
			dsp->fRec199[0] = ((dsp->fConst639 * (((dsp->fConst640 * dsp->fRec200[1]) + (dsp->fConst649 * dsp->fRec200[0])) + (dsp->fConst649 * dsp->fRec200[2]))) - (dsp->fConst637 * ((dsp->fConst650 * dsp->fRec199[2]) + (dsp->fConst651 * dsp->fRec199[1]))));
			float fTemp90 = (dsp->fConst637 * (((dsp->fConst638 * dsp->fRec199[1]) + (dsp->fConst652 * dsp->fRec199[0])) + (dsp->fConst652 * dsp->fRec199[2])));
			dsp->fRec198[0] = (fTemp90 - (dsp->fConst634 * ((dsp->fConst653 * dsp->fRec198[2]) + (dsp->fConst655 * dsp->fRec198[1]))));
			dsp->fRec197[0] = ((dsp->fConst634 * (((dsp->fConst636 * dsp->fRec198[1]) + (dsp->fConst656 * dsp->fRec198[0])) + (dsp->fConst656 * dsp->fRec198[2]))) - (dsp->fConst631 * ((dsp->fConst657 * dsp->fRec197[2]) + (dsp->fConst658 * dsp->fRec197[1]))));
			dsp->fRec196[0] = ((dsp->fConst631 * (((dsp->fConst633 * dsp->fRec197[1]) + (dsp->fConst659 * dsp->fRec197[0])) + (dsp->fConst659 * dsp->fRec197[2]))) - (dsp->fConst627 * ((dsp->fConst660 * dsp->fRec196[2]) + (dsp->fConst661 * dsp->fRec196[1]))));
			dsp->fRec195[0] = ((fSlow1 * dsp->fRec195[1]) + (fSlow2 * fabsf((dsp->fConst627 * (((dsp->fConst630 * dsp->fRec196[1]) + (dsp->fConst662 * dsp->fRec196[0])) + (dsp->fConst662 * dsp->fRec196[2]))))));
			dsp->fVbargraph13 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec195[0]))));
			dsp->fRec205[0] = (fTemp90 - (dsp->fConst667 * ((dsp->fConst670 * dsp->fRec205[2]) + (dsp->fConst671 * dsp->fRec205[1]))));
			dsp->fRec204[0] = ((dsp->fConst667 * (((dsp->fConst669 * dsp->fRec205[1]) + (dsp->fConst672 * dsp->fRec205[0])) + (dsp->fConst672 * dsp->fRec205[2]))) - (dsp->fConst665 * ((dsp->fConst673 * dsp->fRec204[2]) + (dsp->fConst674 * dsp->fRec204[1]))));
			dsp->fRec203[0] = ((dsp->fConst665 * (((dsp->fConst666 * dsp->fRec204[1]) + (dsp->fConst675 * dsp->fRec204[0])) + (dsp->fConst675 * dsp->fRec204[2]))) - (dsp->fConst663 * ((dsp->fConst676 * dsp->fRec203[2]) + (dsp->fConst677 * dsp->fRec203[1]))));
			dsp->fRec202[0] = ((fSlow1 * dsp->fRec202[1]) + (fSlow2 * fabsf((dsp->fConst663 * (((dsp->fConst664 * dsp->fRec203[1]) + (dsp->fConst678 * dsp->fRec203[0])) + (dsp->fConst678 * dsp->fRec203[2]))))));
			dsp->fVbargraph14 = (FAUSTFLOAT)(fSlow0 + (20.0f * log10f(max(1.00000001e-07f, dsp->fRec202[0]))));
			output0[i] = (FAUSTFLOAT)fTemp77;
			output1[i] = (FAUSTFLOAT)fTemp77;
			/* C99 loop */
			{
				int j0;
				for (j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
					dsp->iVec0[j0] = dsp->iVec0[(j0 - 1)];
					
				}
				
			}
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fVec1[1] = dsp->fVec1[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fVec2[1] = dsp->fVec2[0];
			dsp->fVec3[1] = dsp->fVec3[0];
			dsp->fVec4[1] = dsp->fVec4[0];
			dsp->fVec5[1] = dsp->fVec5[0];
			dsp->fVec6[1] = dsp->fVec6[0];
			dsp->fVec7[1] = dsp->fVec7[0];
			dsp->fVec8[1] = dsp->fVec8[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fVec9[1] = dsp->fVec9[0];
			dsp->fVec10[1] = dsp->fVec10[0];
			dsp->fVec11[1] = dsp->fVec11[0];
			dsp->fVec12[1] = dsp->fVec12[0];
			dsp->fVec13[1] = dsp->fVec13[0];
			dsp->fVec14[1] = dsp->fVec14[0];
			dsp->fVec15[1] = dsp->fVec15[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fVec16[1] = dsp->fVec16[0];
			dsp->fVec17[1] = dsp->fVec17[0];
			dsp->fVec18[1] = dsp->fVec18[0];
			dsp->fVec19[1] = dsp->fVec19[0];
			dsp->fVec20[1] = dsp->fVec20[0];
			dsp->fVec21[1] = dsp->fVec21[0];
			dsp->iRec20[1] = dsp->iRec20[0];
			/* C99 loop */
			{
				int j1;
				for (j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
					dsp->fRec21[j1] = dsp->fRec21[(j1 - 1)];
					
				}
				
			}
			dsp->fVec22[1] = dsp->fVec22[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[2] = dsp->fRec13[1];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
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
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[2] = dsp->fRec34[1];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec33[2] = dsp->fRec33[1];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fVec23[1] = dsp->fVec23[0];
			dsp->fRec32[1] = dsp->fRec32[0];
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
			dsp->fRec25[2] = dsp->fRec25[1];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[2] = dsp->fRec46[1];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fVec24[1] = dsp->fVec24[0];
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
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[2] = dsp->fRec38[1];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec37[2] = dsp->fRec37[1];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[2] = dsp->fRec58[1];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fVec25[1] = dsp->fVec25[0];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
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
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec70[2] = dsp->fRec70[1];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[2] = dsp->fRec69[1];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fVec26[1] = dsp->fVec26[0];
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
			dsp->fRec62[2] = dsp->fRec62[1];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec80[2] = dsp->fRec80[1];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec79[2] = dsp->fRec79[1];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fVec27[1] = dsp->fVec27[0];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec77[2] = dsp->fRec77[1];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec75[2] = dsp->fRec75[1];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[2] = dsp->fRec74[1];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[2] = dsp->fRec73[1];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[2] = dsp->fRec89[1];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec88[2] = dsp->fRec88[1];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fVec28[1] = dsp->fVec28[0];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[2] = dsp->fRec86[1];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[2] = dsp->fRec85[1];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec84[2] = dsp->fRec84[1];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec83[2] = dsp->fRec83[1];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[2] = dsp->fRec97[1];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fVec29[1] = dsp->fVec29[0];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec94[2] = dsp->fRec94[1];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[2] = dsp->fRec93[1];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec92[2] = dsp->fRec92[1];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec99[1] = dsp->fRec99[0];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec104[2] = dsp->fRec104[1];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec103[2] = dsp->fRec103[1];
			dsp->fRec103[1] = dsp->fRec103[0];
			dsp->fVec30[1] = dsp->fVec30[0];
			dsp->fRec102[1] = dsp->fRec102[0];
			dsp->fRec101[2] = dsp->fRec101[1];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->fRec100[2] = dsp->fRec100[1];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->fRec109[1] = dsp->fRec109[0];
			dsp->fRec108[2] = dsp->fRec108[1];
			dsp->fRec108[1] = dsp->fRec108[0];
			dsp->fRec107[2] = dsp->fRec107[1];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->fRec110[1] = dsp->fRec110[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[2] = dsp->fRec2[1];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[2] = dsp->fRec1[1];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
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
			dsp->fRec131[2] = dsp->fRec131[1];
			dsp->fRec131[1] = dsp->fRec131[0];
			dsp->fRec130[2] = dsp->fRec130[1];
			dsp->fRec130[1] = dsp->fRec130[0];
			dsp->fRec129[2] = dsp->fRec129[1];
			dsp->fRec129[1] = dsp->fRec129[0];
			dsp->fRec128[2] = dsp->fRec128[1];
			dsp->fRec128[1] = dsp->fRec128[0];
			dsp->fRec127[2] = dsp->fRec127[1];
			dsp->fRec127[1] = dsp->fRec127[0];
			dsp->fRec126[2] = dsp->fRec126[1];
			dsp->fRec126[1] = dsp->fRec126[0];
			dsp->fRec125[1] = dsp->fRec125[0];
			dsp->fRec138[2] = dsp->fRec138[1];
			dsp->fRec138[1] = dsp->fRec138[0];
			dsp->fRec137[2] = dsp->fRec137[1];
			dsp->fRec137[1] = dsp->fRec137[0];
			dsp->fRec136[2] = dsp->fRec136[1];
			dsp->fRec136[1] = dsp->fRec136[0];
			dsp->fRec135[2] = dsp->fRec135[1];
			dsp->fRec135[1] = dsp->fRec135[0];
			dsp->fRec134[2] = dsp->fRec134[1];
			dsp->fRec134[1] = dsp->fRec134[0];
			dsp->fRec133[2] = dsp->fRec133[1];
			dsp->fRec133[1] = dsp->fRec133[0];
			dsp->fRec132[1] = dsp->fRec132[0];
			dsp->fRec145[2] = dsp->fRec145[1];
			dsp->fRec145[1] = dsp->fRec145[0];
			dsp->fRec144[2] = dsp->fRec144[1];
			dsp->fRec144[1] = dsp->fRec144[0];
			dsp->fRec143[2] = dsp->fRec143[1];
			dsp->fRec143[1] = dsp->fRec143[0];
			dsp->fRec142[2] = dsp->fRec142[1];
			dsp->fRec142[1] = dsp->fRec142[0];
			dsp->fRec141[2] = dsp->fRec141[1];
			dsp->fRec141[1] = dsp->fRec141[0];
			dsp->fRec140[2] = dsp->fRec140[1];
			dsp->fRec140[1] = dsp->fRec140[0];
			dsp->fRec139[1] = dsp->fRec139[0];
			dsp->fRec152[2] = dsp->fRec152[1];
			dsp->fRec152[1] = dsp->fRec152[0];
			dsp->fRec151[2] = dsp->fRec151[1];
			dsp->fRec151[1] = dsp->fRec151[0];
			dsp->fRec150[2] = dsp->fRec150[1];
			dsp->fRec150[1] = dsp->fRec150[0];
			dsp->fRec149[2] = dsp->fRec149[1];
			dsp->fRec149[1] = dsp->fRec149[0];
			dsp->fRec148[2] = dsp->fRec148[1];
			dsp->fRec148[1] = dsp->fRec148[0];
			dsp->fRec147[2] = dsp->fRec147[1];
			dsp->fRec147[1] = dsp->fRec147[0];
			dsp->fRec146[1] = dsp->fRec146[0];
			dsp->fRec159[2] = dsp->fRec159[1];
			dsp->fRec159[1] = dsp->fRec159[0];
			dsp->fRec158[2] = dsp->fRec158[1];
			dsp->fRec158[1] = dsp->fRec158[0];
			dsp->fRec157[2] = dsp->fRec157[1];
			dsp->fRec157[1] = dsp->fRec157[0];
			dsp->fRec156[2] = dsp->fRec156[1];
			dsp->fRec156[1] = dsp->fRec156[0];
			dsp->fRec155[2] = dsp->fRec155[1];
			dsp->fRec155[1] = dsp->fRec155[0];
			dsp->fRec154[2] = dsp->fRec154[1];
			dsp->fRec154[1] = dsp->fRec154[0];
			dsp->fRec153[1] = dsp->fRec153[0];
			dsp->fRec166[2] = dsp->fRec166[1];
			dsp->fRec166[1] = dsp->fRec166[0];
			dsp->fRec165[2] = dsp->fRec165[1];
			dsp->fRec165[1] = dsp->fRec165[0];
			dsp->fRec164[2] = dsp->fRec164[1];
			dsp->fRec164[1] = dsp->fRec164[0];
			dsp->fRec163[2] = dsp->fRec163[1];
			dsp->fRec163[1] = dsp->fRec163[0];
			dsp->fRec162[2] = dsp->fRec162[1];
			dsp->fRec162[1] = dsp->fRec162[0];
			dsp->fRec161[2] = dsp->fRec161[1];
			dsp->fRec161[1] = dsp->fRec161[0];
			dsp->fRec160[1] = dsp->fRec160[0];
			dsp->fRec173[2] = dsp->fRec173[1];
			dsp->fRec173[1] = dsp->fRec173[0];
			dsp->fRec172[2] = dsp->fRec172[1];
			dsp->fRec172[1] = dsp->fRec172[0];
			dsp->fRec171[2] = dsp->fRec171[1];
			dsp->fRec171[1] = dsp->fRec171[0];
			dsp->fRec170[2] = dsp->fRec170[1];
			dsp->fRec170[1] = dsp->fRec170[0];
			dsp->fRec169[2] = dsp->fRec169[1];
			dsp->fRec169[1] = dsp->fRec169[0];
			dsp->fRec168[2] = dsp->fRec168[1];
			dsp->fRec168[1] = dsp->fRec168[0];
			dsp->fRec167[1] = dsp->fRec167[0];
			dsp->fRec180[2] = dsp->fRec180[1];
			dsp->fRec180[1] = dsp->fRec180[0];
			dsp->fRec179[2] = dsp->fRec179[1];
			dsp->fRec179[1] = dsp->fRec179[0];
			dsp->fRec178[2] = dsp->fRec178[1];
			dsp->fRec178[1] = dsp->fRec178[0];
			dsp->fRec177[2] = dsp->fRec177[1];
			dsp->fRec177[1] = dsp->fRec177[0];
			dsp->fRec176[2] = dsp->fRec176[1];
			dsp->fRec176[1] = dsp->fRec176[0];
			dsp->fRec175[2] = dsp->fRec175[1];
			dsp->fRec175[1] = dsp->fRec175[0];
			dsp->fRec174[1] = dsp->fRec174[0];
			dsp->fRec187[2] = dsp->fRec187[1];
			dsp->fRec187[1] = dsp->fRec187[0];
			dsp->fRec186[2] = dsp->fRec186[1];
			dsp->fRec186[1] = dsp->fRec186[0];
			dsp->fRec185[2] = dsp->fRec185[1];
			dsp->fRec185[1] = dsp->fRec185[0];
			dsp->fRec184[2] = dsp->fRec184[1];
			dsp->fRec184[1] = dsp->fRec184[0];
			dsp->fRec183[2] = dsp->fRec183[1];
			dsp->fRec183[1] = dsp->fRec183[0];
			dsp->fRec182[2] = dsp->fRec182[1];
			dsp->fRec182[1] = dsp->fRec182[0];
			dsp->fRec181[1] = dsp->fRec181[0];
			dsp->fRec194[2] = dsp->fRec194[1];
			dsp->fRec194[1] = dsp->fRec194[0];
			dsp->fRec193[2] = dsp->fRec193[1];
			dsp->fRec193[1] = dsp->fRec193[0];
			dsp->fRec192[2] = dsp->fRec192[1];
			dsp->fRec192[1] = dsp->fRec192[0];
			dsp->fRec191[2] = dsp->fRec191[1];
			dsp->fRec191[1] = dsp->fRec191[0];
			dsp->fRec190[2] = dsp->fRec190[1];
			dsp->fRec190[1] = dsp->fRec190[0];
			dsp->fRec189[2] = dsp->fRec189[1];
			dsp->fRec189[1] = dsp->fRec189[0];
			dsp->fRec188[1] = dsp->fRec188[0];
			dsp->fRec201[2] = dsp->fRec201[1];
			dsp->fRec201[1] = dsp->fRec201[0];
			dsp->fRec200[2] = dsp->fRec200[1];
			dsp->fRec200[1] = dsp->fRec200[0];
			dsp->fRec199[2] = dsp->fRec199[1];
			dsp->fRec199[1] = dsp->fRec199[0];
			dsp->fRec198[2] = dsp->fRec198[1];
			dsp->fRec198[1] = dsp->fRec198[0];
			dsp->fRec197[2] = dsp->fRec197[1];
			dsp->fRec197[1] = dsp->fRec197[0];
			dsp->fRec196[2] = dsp->fRec196[1];
			dsp->fRec196[1] = dsp->fRec196[0];
			dsp->fRec195[1] = dsp->fRec195[0];
			dsp->fRec205[2] = dsp->fRec205[1];
			dsp->fRec205[1] = dsp->fRec205[0];
			dsp->fRec204[2] = dsp->fRec204[1];
			dsp->fRec204[1] = dsp->fRec204[0];
			dsp->fRec203[2] = dsp->fRec203[1];
			dsp->fRec203[1] = dsp->fRec203[0];
			dsp->fRec202[1] = dsp->fRec202[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
