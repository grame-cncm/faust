/* ------------------------------------------------------------
name: "graphicEqLab"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <cmath>
#include <math.h>

float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}
float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
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
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
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
	float fConst45;
	float fConst46;
	FAUSTFLOAT fCheckbox0;
	float fConst47;
	float fConst48;
	int iVec0[4];
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	FAUSTFLOAT fVslider0;
	float fRec24[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fEntry0;
	float fConst61;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec26[2];
	float fVec1[2];
	float fRec25[2];
	float fConst62;
	float fVec2[2];
	float fConst63;
	float fVec3[2];
	float fVec4[2];
	float fConst64;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec27[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec28[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox3;
	int iRec29[2];
	float fRec30[4];
	float fVec22[2];
	float fConst65;
	float fRec23[2];
	float fConst66;
	float fConst67;
	float fRec22[3];
	float fConst68;
	float fRec21[3];
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec20[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fRec19[3];
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec18[3];
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec17[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec16[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fRec15[3];
	float fConst105;
	float fConst106;
	float fRec14[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fRec13[3];
	FAUSTFLOAT fVslider5;
	float fRec31[2];
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec44[2];
	float fRec43[3];
	float fRec42[3];
	float fVec23[2];
	float fConst120;
	float fRec41[2];
	float fConst121;
	float fRec40[3];
	float fConst122;
	float fRec39[3];
	float fRec38[3];
	float fRec37[3];
	float fRec36[3];
	float fRec35[3];
	float fRec34[3];
	float fRec33[3];
	float fRec32[3];
	FAUSTFLOAT fVslider6;
	float fRec45[2];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec57[2];
	float fRec56[3];
	float fRec55[3];
	float fVec24[2];
	float fConst130;
	float fRec54[2];
	float fConst131;
	float fRec53[3];
	float fConst132;
	float fRec52[3];
	float fRec51[3];
	float fRec50[3];
	float fRec49[3];
	float fRec48[3];
	float fRec47[3];
	float fRec46[3];
	FAUSTFLOAT fVslider7;
	float fRec58[2];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec69[2];
	float fRec68[3];
	float fRec67[3];
	float fVec25[2];
	float fConst140;
	float fRec66[2];
	float fConst141;
	float fRec65[3];
	float fConst142;
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fRec60[3];
	float fRec59[3];
	FAUSTFLOAT fVslider8;
	float fRec70[2];
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec80[2];
	float fRec79[3];
	float fRec78[3];
	float fVec26[2];
	float fConst150;
	float fRec77[2];
	float fConst151;
	float fRec76[3];
	float fConst152;
	float fRec75[3];
	float fRec74[3];
	float fRec73[3];
	float fRec72[3];
	float fRec71[3];
	FAUSTFLOAT fVslider9;
	float fRec81[2];
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec90[2];
	float fRec89[3];
	float fRec88[3];
	float fVec27[2];
	float fConst160;
	float fRec87[2];
	float fConst161;
	float fRec86[3];
	float fConst162;
	float fRec85[3];
	float fRec84[3];
	float fRec83[3];
	float fRec82[3];
	FAUSTFLOAT fVslider10;
	float fRec91[2];
	float fConst163;
	float fConst164;
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec99[2];
	float fRec98[3];
	float fRec97[3];
	float fVec28[2];
	float fConst170;
	float fRec96[2];
	float fConst171;
	float fRec95[3];
	float fConst172;
	float fRec94[3];
	float fRec93[3];
	float fRec92[3];
	FAUSTFLOAT fVslider11;
	float fRec100[2];
	float fConst173;
	float fConst174;
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec107[2];
	float fRec106[3];
	float fRec105[3];
	float fVec29[2];
	float fConst180;
	float fRec104[2];
	float fConst181;
	float fRec103[3];
	float fConst182;
	float fRec102[3];
	float fRec101[3];
	FAUSTFLOAT fVslider12;
	float fRec108[2];
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fConst188;
	float fRec114[2];
	float fRec113[3];
	float fRec112[3];
	float fVec30[2];
	float fConst189;
	float fRec111[2];
	float fConst190;
	float fRec110[3];
	float fConst191;
	float fRec109[3];
	FAUSTFLOAT fVslider13;
	float fRec115[2];
	float fRec118[2];
	float fRec117[3];
	float fRec116[3];
	FAUSTFLOAT fVslider14;
	float fRec119[2];
	float fConst192;
	float fConst193;
	float fRec12[3];
	float fConst194;
	float fConst195;
	float fConst196;
	float fRec11[3];
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec10[3];
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec9[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec8[3];
	float fConst206;
	float fConst207;
	float fConst208;
	float fRec7[3];
	float fConst209;
	float fConst210;
	float fConst211;
	float fRec6[3];
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec5[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec4[3];
	float fConst218;
	float fConst219;
	float fConst220;
	float fConst221;
	float fRec3[3];
	float fConst222;
	float fConst223;
	float fConst224;
	float fRec2[3];
	float fConst225;
	float fConst226;
	float fConst227;
	float fRec1[3];
	float fConst228;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst229;
	float fConst230;
	float fConst231;
	float fConst232;
	float fConst233;
	float fConst234;
	float fConst235;
	float fConst236;
	float fConst237;
	float fConst238;
	float fConst239;
	float fConst240;
	float fConst241;
	float fConst242;
	float fConst243;
	float fConst244;
	float fConst245;
	float fConst246;
	float fConst247;
	float fConst248;
	float fConst249;
	float fRec126[3];
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec125[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec124[3];
	float fConst256;
	float fConst257;
	float fConst258;
	float fConst259;
	float fRec123[3];
	float fConst260;
	float fConst261;
	float fConst262;
	float fRec122[3];
	float fConst263;
	float fConst264;
	float fConst265;
	float fRec121[3];
	float fConst266;
	float fRec120[2];
	FAUSTFLOAT fVbargraph1;
	float fConst267;
	float fConst268;
	float fConst269;
	float fConst270;
	float fConst271;
	float fConst272;
	float fConst273;
	float fConst274;
	float fConst275;
	float fConst276;
	float fConst277;
	float fConst278;
	float fConst279;
	float fConst280;
	float fConst281;
	float fConst282;
	float fConst283;
	float fConst284;
	float fConst285;
	float fConst286;
	float fConst287;
	float fRec133[3];
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec132[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec131[3];
	float fConst294;
	float fConst295;
	float fConst296;
	float fConst297;
	float fRec130[3];
	float fConst298;
	float fConst299;
	float fConst300;
	float fRec129[3];
	float fConst301;
	float fConst302;
	float fConst303;
	float fRec128[3];
	float fConst304;
	float fRec127[2];
	FAUSTFLOAT fVbargraph2;
	float fConst305;
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fConst314;
	float fConst315;
	float fConst316;
	float fConst317;
	float fConst318;
	float fConst319;
	float fConst320;
	float fConst321;
	float fConst322;
	float fConst323;
	float fConst324;
	float fConst325;
	float fRec140[3];
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec139[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec138[3];
	float fConst332;
	float fConst333;
	float fConst334;
	float fConst335;
	float fRec137[3];
	float fConst336;
	float fConst337;
	float fConst338;
	float fRec136[3];
	float fConst339;
	float fConst340;
	float fConst341;
	float fRec135[3];
	float fConst342;
	float fRec134[2];
	FAUSTFLOAT fVbargraph3;
	float fConst343;
	float fConst344;
	float fConst345;
	float fConst346;
	float fConst347;
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fConst352;
	float fConst353;
	float fConst354;
	float fConst355;
	float fConst356;
	float fConst357;
	float fConst358;
	float fConst359;
	float fConst360;
	float fConst361;
	float fConst362;
	float fConst363;
	float fRec147[3];
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec146[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec145[3];
	float fConst370;
	float fConst371;
	float fConst372;
	float fConst373;
	float fRec144[3];
	float fConst374;
	float fConst375;
	float fConst376;
	float fRec143[3];
	float fConst377;
	float fConst378;
	float fConst379;
	float fRec142[3];
	float fConst380;
	float fRec141[2];
	FAUSTFLOAT fVbargraph4;
	float fConst381;
	float fConst382;
	float fConst383;
	float fConst384;
	float fConst385;
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fConst390;
	float fConst391;
	float fConst392;
	float fConst393;
	float fConst394;
	float fConst395;
	float fConst396;
	float fConst397;
	float fConst398;
	float fConst399;
	float fConst400;
	float fConst401;
	float fRec154[3];
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec153[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec152[3];
	float fConst408;
	float fConst409;
	float fConst410;
	float fConst411;
	float fRec151[3];
	float fConst412;
	float fConst413;
	float fConst414;
	float fRec150[3];
	float fConst415;
	float fConst416;
	float fConst417;
	float fRec149[3];
	float fConst418;
	float fRec148[2];
	FAUSTFLOAT fVbargraph5;
	float fConst419;
	float fConst420;
	float fConst421;
	float fConst422;
	float fConst423;
	float fConst424;
	float fConst425;
	float fConst426;
	float fConst427;
	float fConst428;
	float fConst429;
	float fConst430;
	float fConst431;
	float fConst432;
	float fConst433;
	float fConst434;
	float fConst435;
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fRec161[3];
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec160[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec159[3];
	float fConst446;
	float fConst447;
	float fConst448;
	float fConst449;
	float fRec158[3];
	float fConst450;
	float fConst451;
	float fConst452;
	float fRec157[3];
	float fConst453;
	float fConst454;
	float fConst455;
	float fRec156[3];
	float fConst456;
	float fRec155[2];
	FAUSTFLOAT fVbargraph6;
	float fConst457;
	float fConst458;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fConst463;
	float fConst464;
	float fConst465;
	float fConst466;
	float fConst467;
	float fConst468;
	float fConst469;
	float fConst470;
	float fConst471;
	float fConst472;
	float fConst473;
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fRec168[3];
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec167[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec166[3];
	float fConst484;
	float fConst485;
	float fConst486;
	float fConst487;
	float fRec165[3];
	float fConst488;
	float fConst489;
	float fConst490;
	float fRec164[3];
	float fConst491;
	float fConst492;
	float fConst493;
	float fRec163[3];
	float fConst494;
	float fRec162[2];
	FAUSTFLOAT fVbargraph7;
	float fConst495;
	float fConst496;
	float fConst497;
	float fConst498;
	float fConst499;
	float fConst500;
	float fConst501;
	float fConst502;
	float fConst503;
	float fConst504;
	float fConst505;
	float fConst506;
	float fConst507;
	float fConst508;
	float fConst509;
	float fConst510;
	float fConst511;
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fRec175[3];
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec174[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec173[3];
	float fConst522;
	float fConst523;
	float fConst524;
	float fConst525;
	float fRec172[3];
	float fConst526;
	float fConst527;
	float fConst528;
	float fRec171[3];
	float fConst529;
	float fConst530;
	float fConst531;
	float fRec170[3];
	float fConst532;
	float fRec169[2];
	FAUSTFLOAT fVbargraph8;
	float fConst533;
	float fConst534;
	float fConst535;
	float fConst536;
	float fConst537;
	float fConst538;
	float fConst539;
	float fConst540;
	float fConst541;
	float fConst542;
	float fConst543;
	float fConst544;
	float fConst545;
	float fConst546;
	float fConst547;
	float fConst548;
	float fConst549;
	float fConst550;
	float fConst551;
	float fConst552;
	float fConst553;
	float fRec182[3];
	float fConst554;
	float fConst555;
	float fConst556;
	float fRec181[3];
	float fConst557;
	float fConst558;
	float fConst559;
	float fRec180[3];
	float fConst560;
	float fConst561;
	float fConst562;
	float fConst563;
	float fRec179[3];
	float fConst564;
	float fConst565;
	float fConst566;
	float fRec178[3];
	float fConst567;
	float fConst568;
	float fConst569;
	float fRec177[3];
	float fConst570;
	float fRec176[2];
	FAUSTFLOAT fVbargraph9;
	float fConst571;
	float fConst572;
	float fConst573;
	float fConst574;
	float fConst575;
	float fConst576;
	float fConst577;
	float fConst578;
	float fConst579;
	float fConst580;
	float fConst581;
	float fConst582;
	float fConst583;
	float fConst584;
	float fConst585;
	float fConst586;
	float fConst587;
	float fConst588;
	float fConst589;
	float fConst590;
	float fConst591;
	float fRec189[3];
	float fConst592;
	float fConst593;
	float fConst594;
	float fRec188[3];
	float fConst595;
	float fConst596;
	float fConst597;
	float fRec187[3];
	float fConst598;
	float fConst599;
	float fConst600;
	float fConst601;
	float fRec186[3];
	float fConst602;
	float fConst603;
	float fConst604;
	float fRec185[3];
	float fConst605;
	float fConst606;
	float fConst607;
	float fRec184[3];
	float fConst608;
	float fRec183[2];
	FAUSTFLOAT fVbargraph10;
	float fConst609;
	float fConst610;
	float fConst611;
	float fConst612;
	float fConst613;
	float fConst614;
	float fConst615;
	float fConst616;
	float fConst617;
	float fRec193[3];
	float fConst618;
	float fConst619;
	float fConst620;
	float fRec192[3];
	float fConst621;
	float fConst622;
	float fConst623;
	float fRec191[3];
	float fConst624;
	float fRec190[2];
	FAUSTFLOAT fVbargraph11;
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
	float fRec197[3];
	float fConst636;
	float fConst637;
	float fConst638;
	float fRec196[3];
	float fConst639;
	float fConst640;
	float fConst641;
	float fRec195[3];
	float fConst642;
	float fRec194[2];
	FAUSTFLOAT fVbargraph12;
	float fConst643;
	float fConst644;
	float fConst645;
	float fConst646;
	float fConst647;
	float fConst648;
	float fConst649;
	float fConst650;
	float fConst651;
	float fConst652;
	float fConst653;
	float fRec201[3];
	float fConst654;
	float fConst655;
	float fConst656;
	float fRec200[3];
	float fConst657;
	float fConst658;
	float fConst659;
	float fRec199[3];
	float fConst660;
	float fRec198[2];
	FAUSTFLOAT fVbargraph13;
	float fConst661;
	float fConst662;
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
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Signal generators through a filter bank with spectrum analysis display");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "graphicEqLab");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
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
	virtual int getOutputRate(int channel) {
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
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (1000.0f / fConst0);
		fConst2 = tanf((12566.3711f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 0.157482162f) / fConst2) + 0.935140193f));
		fConst5 = mydsp_faustpower2_f(fConst2);
		fConst6 = (50.0638084f / fConst5);
		fConst7 = (2.0f * (0.935140193f - fConst6));
		fConst8 = (1.0f / (((fConst3 + 0.743130445f) / fConst2) + 1.4500711f));
		fConst9 = (11.0520525f / fConst5);
		fConst10 = (2.0f * (1.4500711f - fConst9));
		fConst11 = (1.0f / (((fConst3 + 3.18972731f) / fConst2) + 4.07678175f));
		fConst12 = (0.00176617282f / fConst5);
		fConst13 = (2.0f * (0.000407678192f - fConst12));
		fConst14 = tanf((19947.8691f / fConst0));
		fConst15 = (1.0f / fConst14);
		fConst16 = (1.0f / (((fConst15 + 0.168404877f) / fConst14) + 1.06935835f));
		fConst17 = mydsp_faustpower2_f(fConst14);
		fConst18 = (1.0f / fConst17);
		fConst19 = (2.0f * (53.5361519f - fConst18));
		fConst20 = (1.0f / (((fConst15 + 0.51247865f) / fConst14) + 0.689621389f));
		fConst21 = (2.0f * (7.62173128f - fConst18));
		fConst22 = (1.0f / (((fConst15 + 0.782413065f) / fConst14) + 0.245291501f));
		fConst23 = (9.99999975e-05f / fConst17);
		fConst24 = (2.0f * (0.000433227193f - fConst23));
		fConst25 = tanf((31665.2695f / fConst0));
		fConst26 = (1.0f / fConst25);
		fConst27 = (1.0f / (((fConst26 + 0.168404877f) / fConst25) + 1.06935835f));
		fConst28 = mydsp_faustpower2_f(fConst25);
		fConst29 = (1.0f / fConst28);
		fConst30 = (2.0f * (53.5361519f - fConst29));
		fConst31 = (1.0f / (((fConst26 + 0.51247865f) / fConst25) + 0.689621389f));
		fConst32 = (2.0f * (7.62173128f - fConst29));
		fConst33 = (1.0f / (((fConst26 + 0.782413065f) / fConst25) + 0.245291501f));
		fConst34 = (9.99999975e-05f / fConst28);
		fConst35 = (2.0f * (0.000433227193f - fConst34));
		fConst36 = tanf((50265.4844f / fConst0));
		fConst37 = (1.0f / fConst36);
		fConst38 = (1.0f / (((fConst37 + 0.168404877f) / fConst36) + 1.06935835f));
		fConst39 = mydsp_faustpower2_f(fConst36);
		fConst40 = (1.0f / fConst39);
		fConst41 = (2.0f * (53.5361519f - fConst40));
		fConst42 = (1.0f / (((fConst37 + 0.51247865f) / fConst36) + 0.689621389f));
		fConst43 = (2.0f * (7.62173128f - fConst40));
		fConst44 = (1.0f / (((fConst37 + 0.782413065f) / fConst36) + 0.245291501f));
		fConst45 = (9.99999975e-05f / fConst39);
		fConst46 = (2.0f * (0.000433227193f - fConst45));
		fConst47 = tanf((7853.98145f / fConst0));
		fConst48 = (1.0f / fConst47);
		fConst49 = (1.0f / (((fConst48 + 1.61803401f) / fConst47) + 1.0f));
		fConst50 = (((fConst48 + -1.61803401f) / fConst47) + 1.0f);
		fConst51 = tanf((31415.9258f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (((fConst52 + 0.618034005f) / fConst51) + 1.0f);
		fConst54 = (1.0f / fConst53);
		fConst55 = (1.0f / mydsp_faustpower2_f(fConst51));
		fConst56 = (2.0f * (0.0f - fConst55));
		fConst57 = (1.0f / (((fConst52 + 1.61803401f) / fConst51) + 1.0f));
		fConst58 = (fConst52 + 1.0f);
		fConst59 = (0.0f - ((1.0f - fConst52) / fConst58));
		fConst60 = (1.0f / fConst58);
		fConst61 = (1.0f / fConst0);
		fConst62 = (0.25f * fConst0);
		fConst63 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst64 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst65 = (0.0f - fConst52);
		fConst66 = (2.0f * (1.0f - fConst55));
		fConst67 = (((fConst52 + -1.61803401f) / fConst51) + 1.0f);
		fConst68 = (((fConst52 + -0.618034005f) / fConst51) + 1.0f);
		fConst69 = tanf((122.71846f / fConst0));
		fConst70 = (1.0f / fConst69);
		fConst71 = (1.0f / (((fConst70 + 1.61803401f) / fConst69) + 1.0f));
		fConst72 = (((fConst70 + -1.61803401f) / fConst69) + 1.0f);
		fConst73 = (1.0f / mydsp_faustpower2_f(fConst69));
		fConst74 = (2.0f * (1.0f - fConst73));
		fConst75 = tanf((245.43692f / fConst0));
		fConst76 = (1.0f / fConst75);
		fConst77 = (1.0f / (((fConst76 + 1.61803401f) / fConst75) + 1.0f));
		fConst78 = (((fConst76 + -1.61803401f) / fConst75) + 1.0f);
		fConst79 = (1.0f / mydsp_faustpower2_f(fConst75));
		fConst80 = (2.0f * (1.0f - fConst79));
		fConst81 = tanf((490.87384f / fConst0));
		fConst82 = (1.0f / fConst81);
		fConst83 = (1.0f / (((fConst82 + 1.61803401f) / fConst81) + 1.0f));
		fConst84 = (((fConst82 + -1.61803401f) / fConst81) + 1.0f);
		fConst85 = (1.0f / mydsp_faustpower2_f(fConst81));
		fConst86 = (2.0f * (1.0f - fConst85));
		fConst87 = tanf((981.747681f / fConst0));
		fConst88 = (1.0f / fConst87);
		fConst89 = (1.0f / (((fConst88 + 1.61803401f) / fConst87) + 1.0f));
		fConst90 = (((fConst88 + -1.61803401f) / fConst87) + 1.0f);
		fConst91 = (1.0f / mydsp_faustpower2_f(fConst87));
		fConst92 = (2.0f * (1.0f - fConst91));
		fConst93 = tanf((1963.49536f / fConst0));
		fConst94 = (1.0f / fConst93);
		fConst95 = (1.0f / (((fConst94 + 1.61803401f) / fConst93) + 1.0f));
		fConst96 = (((fConst94 + -1.61803401f) / fConst93) + 1.0f);
		fConst97 = (1.0f / mydsp_faustpower2_f(fConst93));
		fConst98 = (2.0f * (1.0f - fConst97));
		fConst99 = tanf((3926.99072f / fConst0));
		fConst100 = (1.0f / fConst99);
		fConst101 = (1.0f / (((fConst100 + 1.61803401f) / fConst99) + 1.0f));
		fConst102 = (((fConst100 + -1.61803401f) / fConst99) + 1.0f);
		fConst103 = (1.0f / mydsp_faustpower2_f(fConst99));
		fConst104 = (2.0f * (1.0f - fConst103));
		fConst105 = (1.0f / mydsp_faustpower2_f(fConst47));
		fConst106 = (2.0f * (1.0f - fConst105));
		fConst107 = tanf((15707.9629f / fConst0));
		fConst108 = (1.0f / fConst107);
		fConst109 = (1.0f / (((fConst108 + 1.61803401f) / fConst107) + 1.0f));
		fConst110 = (((fConst108 + -1.61803401f) / fConst107) + 1.0f);
		fConst111 = (1.0f / mydsp_faustpower2_f(fConst107));
		fConst112 = (2.0f * (1.0f - fConst111));
		fConst113 = (((fConst108 + 0.618034005f) / fConst107) + 1.0f);
		fConst114 = (1.0f / fConst113);
		fConst115 = (2.0f * (0.0f - fConst111));
		fConst116 = (1.0f / (((fConst108 + 1.61803401f) / fConst107) + 1.0f));
		fConst117 = (fConst108 + 1.0f);
		fConst118 = (0.0f - ((1.0f - fConst108) / fConst117));
		fConst119 = (1.0f / (fConst53 * fConst117));
		fConst120 = (0.0f - fConst108);
		fConst121 = (((fConst108 + -1.61803401f) / fConst107) + 1.0f);
		fConst122 = (((fConst108 + -0.618034005f) / fConst107) + 1.0f);
		fConst123 = (((fConst48 + 0.618034005f) / fConst47) + 1.0f);
		fConst124 = (1.0f / fConst123);
		fConst125 = (2.0f * (0.0f - fConst105));
		fConst126 = (1.0f / (((fConst48 + 1.61803401f) / fConst47) + 1.0f));
		fConst127 = (fConst48 + 1.0f);
		fConst128 = (0.0f - ((1.0f - fConst48) / fConst127));
		fConst129 = (1.0f / (fConst113 * fConst127));
		fConst130 = (0.0f - fConst48);
		fConst131 = (((fConst48 + -1.61803401f) / fConst47) + 1.0f);
		fConst132 = (((fConst48 + -0.618034005f) / fConst47) + 1.0f);
		fConst133 = (((fConst100 + 0.618034005f) / fConst99) + 1.0f);
		fConst134 = (1.0f / fConst133);
		fConst135 = (2.0f * (0.0f - fConst103));
		fConst136 = (1.0f / (((fConst100 + 1.61803401f) / fConst99) + 1.0f));
		fConst137 = (fConst100 + 1.0f);
		fConst138 = (0.0f - ((1.0f - fConst100) / fConst137));
		fConst139 = (1.0f / (fConst123 * fConst137));
		fConst140 = (0.0f - fConst100);
		fConst141 = (((fConst100 + -1.61803401f) / fConst99) + 1.0f);
		fConst142 = (((fConst100 + -0.618034005f) / fConst99) + 1.0f);
		fConst143 = (((fConst94 + 0.618034005f) / fConst93) + 1.0f);
		fConst144 = (1.0f / fConst143);
		fConst145 = (2.0f * (0.0f - fConst97));
		fConst146 = (1.0f / (((fConst94 + 1.61803401f) / fConst93) + 1.0f));
		fConst147 = (fConst94 + 1.0f);
		fConst148 = (0.0f - ((1.0f - fConst94) / fConst147));
		fConst149 = (1.0f / (fConst133 * fConst147));
		fConst150 = (0.0f - fConst94);
		fConst151 = (((fConst94 + -1.61803401f) / fConst93) + 1.0f);
		fConst152 = (((fConst94 + -0.618034005f) / fConst93) + 1.0f);
		fConst153 = (((fConst88 + 0.618034005f) / fConst87) + 1.0f);
		fConst154 = (1.0f / fConst153);
		fConst155 = (2.0f * (0.0f - fConst91));
		fConst156 = (1.0f / (((fConst88 + 1.61803401f) / fConst87) + 1.0f));
		fConst157 = (fConst88 + 1.0f);
		fConst158 = (0.0f - ((1.0f - fConst88) / fConst157));
		fConst159 = (1.0f / (fConst143 * fConst157));
		fConst160 = (0.0f - fConst88);
		fConst161 = (((fConst88 + -1.61803401f) / fConst87) + 1.0f);
		fConst162 = (((fConst88 + -0.618034005f) / fConst87) + 1.0f);
		fConst163 = (((fConst82 + 0.618034005f) / fConst81) + 1.0f);
		fConst164 = (1.0f / fConst163);
		fConst165 = (2.0f * (0.0f - fConst85));
		fConst166 = (1.0f / (((fConst82 + 1.61803401f) / fConst81) + 1.0f));
		fConst167 = (fConst82 + 1.0f);
		fConst168 = (0.0f - ((1.0f - fConst82) / fConst167));
		fConst169 = (1.0f / (fConst153 * fConst167));
		fConst170 = (0.0f - fConst82);
		fConst171 = (((fConst82 + -1.61803401f) / fConst81) + 1.0f);
		fConst172 = (((fConst82 + -0.618034005f) / fConst81) + 1.0f);
		fConst173 = (((fConst76 + 0.618034005f) / fConst75) + 1.0f);
		fConst174 = (1.0f / fConst173);
		fConst175 = (2.0f * (0.0f - fConst79));
		fConst176 = (1.0f / (((fConst76 + 1.61803401f) / fConst75) + 1.0f));
		fConst177 = (fConst76 + 1.0f);
		fConst178 = (0.0f - ((1.0f - fConst76) / fConst177));
		fConst179 = (1.0f / (fConst163 * fConst177));
		fConst180 = (0.0f - fConst76);
		fConst181 = (((fConst76 + -1.61803401f) / fConst75) + 1.0f);
		fConst182 = (((fConst76 + -0.618034005f) / fConst75) + 1.0f);
		fConst183 = (1.0f / (((fConst70 + 0.618034005f) / fConst69) + 1.0f));
		fConst184 = (2.0f * (0.0f - fConst73));
		fConst185 = (1.0f / (((fConst70 + 1.61803401f) / fConst69) + 1.0f));
		fConst186 = (fConst70 + 1.0f);
		fConst187 = (0.0f - ((1.0f - fConst70) / fConst186));
		fConst188 = (1.0f / (fConst173 * fConst186));
		fConst189 = (0.0f - fConst70);
		fConst190 = (((fConst70 + -1.61803401f) / fConst69) + 1.0f);
		fConst191 = (((fConst70 + -0.618034005f) / fConst69) + 1.0f);
		fConst192 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst193 = (2.0f * (0.245291501f - fConst40));
		fConst194 = (fConst45 + 0.000433227193f);
		fConst195 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst196 = (2.0f * (0.689621389f - fConst40));
		fConst197 = (fConst40 + 7.62173128f);
		fConst198 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst199 = (2.0f * (1.06935835f - fConst40));
		fConst200 = (fConst40 + 53.5361519f);
		fConst201 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst202 = (2.0f * (0.245291501f - fConst29));
		fConst203 = (fConst34 + 0.000433227193f);
		fConst204 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst205 = (2.0f * (0.689621389f - fConst29));
		fConst206 = (fConst29 + 7.62173128f);
		fConst207 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst208 = (2.0f * (1.06935835f - fConst29));
		fConst209 = (fConst29 + 53.5361519f);
		fConst210 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst211 = (2.0f * (0.245291501f - fConst18));
		fConst212 = (fConst23 + 0.000433227193f);
		fConst213 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst214 = (2.0f * (0.689621389f - fConst18));
		fConst215 = (fConst18 + 7.62173128f);
		fConst216 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst217 = (2.0f * (1.06935835f - fConst18));
		fConst218 = (fConst18 + 53.5361519f);
		fConst219 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst220 = (1.0f / fConst5);
		fConst221 = (2.0f * (4.07678175f - fConst220));
		fConst222 = (fConst12 + 0.000407678192f);
		fConst223 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst224 = (2.0f * (1.4500711f - fConst220));
		fConst225 = (fConst9 + 1.4500711f);
		fConst226 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst227 = (2.0f * (0.935140193f - fConst220));
		fConst228 = (fConst6 + 0.935140193f);
		fConst229 = tanf((7916.31738f / fConst0));
		fConst230 = (1.0f / fConst229);
		fConst231 = (1.0f / (((fConst230 + 0.157482162f) / fConst229) + 0.935140193f));
		fConst232 = mydsp_faustpower2_f(fConst229);
		fConst233 = (50.0638084f / fConst232);
		fConst234 = (2.0f * (0.935140193f - fConst233));
		fConst235 = (1.0f / (((fConst230 + 0.743130445f) / fConst229) + 1.4500711f));
		fConst236 = (11.0520525f / fConst232);
		fConst237 = (2.0f * (1.4500711f - fConst236));
		fConst238 = (1.0f / (((fConst230 + 3.18972731f) / fConst229) + 4.07678175f));
		fConst239 = (0.00176617282f / fConst232);
		fConst240 = (2.0f * (0.000407678192f - fConst239));
		fConst241 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst242 = (2.0f * (53.5361519f - fConst220));
		fConst243 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst244 = (2.0f * (7.62173128f - fConst220));
		fConst245 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst246 = (9.99999975e-05f / fConst5);
		fConst247 = (2.0f * (0.000433227193f - fConst246));
		fConst248 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst249 = (2.0f * (0.245291501f - fConst220));
		fConst250 = (fConst246 + 0.000433227193f);
		fConst251 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst252 = (2.0f * (0.689621389f - fConst220));
		fConst253 = (fConst220 + 7.62173128f);
		fConst254 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst255 = (2.0f * (1.06935835f - fConst220));
		fConst256 = (fConst220 + 53.5361519f);
		fConst257 = (((fConst230 + -3.18972731f) / fConst229) + 4.07678175f);
		fConst258 = (1.0f / fConst232);
		fConst259 = (2.0f * (4.07678175f - fConst258));
		fConst260 = (fConst239 + 0.000407678192f);
		fConst261 = (((fConst230 + -0.743130445f) / fConst229) + 1.4500711f);
		fConst262 = (2.0f * (1.4500711f - fConst258));
		fConst263 = (fConst236 + 1.4500711f);
		fConst264 = (((fConst230 + -0.157482162f) / fConst229) + 0.935140193f);
		fConst265 = (2.0f * (0.935140193f - fConst258));
		fConst266 = (fConst233 + 0.935140193f);
		fConst267 = tanf((4986.96729f / fConst0));
		fConst268 = (1.0f / fConst267);
		fConst269 = (1.0f / (((fConst268 + 0.157482162f) / fConst267) + 0.935140193f));
		fConst270 = mydsp_faustpower2_f(fConst267);
		fConst271 = (50.0638084f / fConst270);
		fConst272 = (2.0f * (0.935140193f - fConst271));
		fConst273 = (1.0f / (((fConst268 + 0.743130445f) / fConst267) + 1.4500711f));
		fConst274 = (11.0520525f / fConst270);
		fConst275 = (2.0f * (1.4500711f - fConst274));
		fConst276 = (1.0f / (((fConst268 + 3.18972731f) / fConst267) + 4.07678175f));
		fConst277 = (0.00176617282f / fConst270);
		fConst278 = (2.0f * (0.000407678192f - fConst277));
		fConst279 = (1.0f / (((fConst230 + 0.168404877f) / fConst229) + 1.06935835f));
		fConst280 = (2.0f * (53.5361519f - fConst258));
		fConst281 = (1.0f / (((fConst230 + 0.51247865f) / fConst229) + 0.689621389f));
		fConst282 = (2.0f * (7.62173128f - fConst258));
		fConst283 = (1.0f / (((fConst230 + 0.782413065f) / fConst229) + 0.245291501f));
		fConst284 = (9.99999975e-05f / fConst232);
		fConst285 = (2.0f * (0.000433227193f - fConst284));
		fConst286 = (((fConst230 + -0.782413065f) / fConst229) + 0.245291501f);
		fConst287 = (2.0f * (0.245291501f - fConst258));
		fConst288 = (fConst284 + 0.000433227193f);
		fConst289 = (((fConst230 + -0.51247865f) / fConst229) + 0.689621389f);
		fConst290 = (2.0f * (0.689621389f - fConst258));
		fConst291 = (fConst258 + 7.62173128f);
		fConst292 = (((fConst230 + -0.168404877f) / fConst229) + 1.06935835f);
		fConst293 = (2.0f * (1.06935835f - fConst258));
		fConst294 = (fConst258 + 53.5361519f);
		fConst295 = (((fConst268 + -3.18972731f) / fConst267) + 4.07678175f);
		fConst296 = (1.0f / fConst270);
		fConst297 = (2.0f * (4.07678175f - fConst296));
		fConst298 = (fConst277 + 0.000407678192f);
		fConst299 = (((fConst268 + -0.743130445f) / fConst267) + 1.4500711f);
		fConst300 = (2.0f * (1.4500711f - fConst296));
		fConst301 = (fConst274 + 1.4500711f);
		fConst302 = (((fConst268 + -0.157482162f) / fConst267) + 0.935140193f);
		fConst303 = (2.0f * (0.935140193f - fConst296));
		fConst304 = (fConst271 + 0.935140193f);
		fConst305 = tanf((3141.59277f / fConst0));
		fConst306 = (1.0f / fConst305);
		fConst307 = (1.0f / (((fConst306 + 0.157482162f) / fConst305) + 0.935140193f));
		fConst308 = mydsp_faustpower2_f(fConst305);
		fConst309 = (50.0638084f / fConst308);
		fConst310 = (2.0f * (0.935140193f - fConst309));
		fConst311 = (1.0f / (((fConst306 + 0.743130445f) / fConst305) + 1.4500711f));
		fConst312 = (11.0520525f / fConst308);
		fConst313 = (2.0f * (1.4500711f - fConst312));
		fConst314 = (1.0f / (((fConst306 + 3.18972731f) / fConst305) + 4.07678175f));
		fConst315 = (0.00176617282f / fConst308);
		fConst316 = (2.0f * (0.000407678192f - fConst315));
		fConst317 = (1.0f / (((fConst268 + 0.168404877f) / fConst267) + 1.06935835f));
		fConst318 = (2.0f * (53.5361519f - fConst296));
		fConst319 = (1.0f / (((fConst268 + 0.51247865f) / fConst267) + 0.689621389f));
		fConst320 = (2.0f * (7.62173128f - fConst296));
		fConst321 = (1.0f / (((fConst268 + 0.782413065f) / fConst267) + 0.245291501f));
		fConst322 = (9.99999975e-05f / fConst270);
		fConst323 = (2.0f * (0.000433227193f - fConst322));
		fConst324 = (((fConst268 + -0.782413065f) / fConst267) + 0.245291501f);
		fConst325 = (2.0f * (0.245291501f - fConst296));
		fConst326 = (fConst322 + 0.000433227193f);
		fConst327 = (((fConst268 + -0.51247865f) / fConst267) + 0.689621389f);
		fConst328 = (2.0f * (0.689621389f - fConst296));
		fConst329 = (fConst296 + 7.62173128f);
		fConst330 = (((fConst268 + -0.168404877f) / fConst267) + 1.06935835f);
		fConst331 = (2.0f * (1.06935835f - fConst296));
		fConst332 = (fConst296 + 53.5361519f);
		fConst333 = (((fConst306 + -3.18972731f) / fConst305) + 4.07678175f);
		fConst334 = (1.0f / fConst308);
		fConst335 = (2.0f * (4.07678175f - fConst334));
		fConst336 = (fConst315 + 0.000407678192f);
		fConst337 = (((fConst306 + -0.743130445f) / fConst305) + 1.4500711f);
		fConst338 = (2.0f * (1.4500711f - fConst334));
		fConst339 = (fConst312 + 1.4500711f);
		fConst340 = (((fConst306 + -0.157482162f) / fConst305) + 0.935140193f);
		fConst341 = (2.0f * (0.935140193f - fConst334));
		fConst342 = (fConst309 + 0.935140193f);
		fConst343 = tanf((1979.07935f / fConst0));
		fConst344 = (1.0f / fConst343);
		fConst345 = (1.0f / (((fConst344 + 0.157482162f) / fConst343) + 0.935140193f));
		fConst346 = mydsp_faustpower2_f(fConst343);
		fConst347 = (50.0638084f / fConst346);
		fConst348 = (2.0f * (0.935140193f - fConst347));
		fConst349 = (1.0f / (((fConst344 + 0.743130445f) / fConst343) + 1.4500711f));
		fConst350 = (11.0520525f / fConst346);
		fConst351 = (2.0f * (1.4500711f - fConst350));
		fConst352 = (1.0f / (((fConst344 + 3.18972731f) / fConst343) + 4.07678175f));
		fConst353 = (0.00176617282f / fConst346);
		fConst354 = (2.0f * (0.000407678192f - fConst353));
		fConst355 = (1.0f / (((fConst306 + 0.168404877f) / fConst305) + 1.06935835f));
		fConst356 = (2.0f * (53.5361519f - fConst334));
		fConst357 = (1.0f / (((fConst306 + 0.51247865f) / fConst305) + 0.689621389f));
		fConst358 = (2.0f * (7.62173128f - fConst334));
		fConst359 = (1.0f / (((fConst306 + 0.782413065f) / fConst305) + 0.245291501f));
		fConst360 = (9.99999975e-05f / fConst308);
		fConst361 = (2.0f * (0.000433227193f - fConst360));
		fConst362 = (((fConst306 + -0.782413065f) / fConst305) + 0.245291501f);
		fConst363 = (2.0f * (0.245291501f - fConst334));
		fConst364 = (fConst360 + 0.000433227193f);
		fConst365 = (((fConst306 + -0.51247865f) / fConst305) + 0.689621389f);
		fConst366 = (2.0f * (0.689621389f - fConst334));
		fConst367 = (fConst334 + 7.62173128f);
		fConst368 = (((fConst306 + -0.168404877f) / fConst305) + 1.06935835f);
		fConst369 = (2.0f * (1.06935835f - fConst334));
		fConst370 = (fConst334 + 53.5361519f);
		fConst371 = (((fConst344 + -3.18972731f) / fConst343) + 4.07678175f);
		fConst372 = (1.0f / fConst346);
		fConst373 = (2.0f * (4.07678175f - fConst372));
		fConst374 = (fConst353 + 0.000407678192f);
		fConst375 = (((fConst344 + -0.743130445f) / fConst343) + 1.4500711f);
		fConst376 = (2.0f * (1.4500711f - fConst372));
		fConst377 = (fConst350 + 1.4500711f);
		fConst378 = (((fConst344 + -0.157482162f) / fConst343) + 0.935140193f);
		fConst379 = (2.0f * (0.935140193f - fConst372));
		fConst380 = (fConst347 + 0.935140193f);
		fConst381 = tanf((1246.74182f / fConst0));
		fConst382 = (1.0f / fConst381);
		fConst383 = (1.0f / (((fConst382 + 0.157482162f) / fConst381) + 0.935140193f));
		fConst384 = mydsp_faustpower2_f(fConst381);
		fConst385 = (50.0638084f / fConst384);
		fConst386 = (2.0f * (0.935140193f - fConst385));
		fConst387 = (1.0f / (((fConst382 + 0.743130445f) / fConst381) + 1.4500711f));
		fConst388 = (11.0520525f / fConst384);
		fConst389 = (2.0f * (1.4500711f - fConst388));
		fConst390 = (1.0f / (((fConst382 + 3.18972731f) / fConst381) + 4.07678175f));
		fConst391 = (0.00176617282f / fConst384);
		fConst392 = (2.0f * (0.000407678192f - fConst391));
		fConst393 = (1.0f / (((fConst344 + 0.168404877f) / fConst343) + 1.06935835f));
		fConst394 = (2.0f * (53.5361519f - fConst372));
		fConst395 = (1.0f / (((fConst344 + 0.51247865f) / fConst343) + 0.689621389f));
		fConst396 = (2.0f * (7.62173128f - fConst372));
		fConst397 = (1.0f / (((fConst344 + 0.782413065f) / fConst343) + 0.245291501f));
		fConst398 = (9.99999975e-05f / fConst346);
		fConst399 = (2.0f * (0.000433227193f - fConst398));
		fConst400 = (((fConst344 + -0.782413065f) / fConst343) + 0.245291501f);
		fConst401 = (2.0f * (0.245291501f - fConst372));
		fConst402 = (fConst398 + 0.000433227193f);
		fConst403 = (((fConst344 + -0.51247865f) / fConst343) + 0.689621389f);
		fConst404 = (2.0f * (0.689621389f - fConst372));
		fConst405 = (fConst372 + 7.62173128f);
		fConst406 = (((fConst344 + -0.168404877f) / fConst343) + 1.06935835f);
		fConst407 = (2.0f * (1.06935835f - fConst372));
		fConst408 = (fConst372 + 53.5361519f);
		fConst409 = (((fConst382 + -3.18972731f) / fConst381) + 4.07678175f);
		fConst410 = (1.0f / fConst384);
		fConst411 = (2.0f * (4.07678175f - fConst410));
		fConst412 = (fConst391 + 0.000407678192f);
		fConst413 = (((fConst382 + -0.743130445f) / fConst381) + 1.4500711f);
		fConst414 = (2.0f * (1.4500711f - fConst410));
		fConst415 = (fConst388 + 1.4500711f);
		fConst416 = (((fConst382 + -0.157482162f) / fConst381) + 0.935140193f);
		fConst417 = (2.0f * (0.935140193f - fConst410));
		fConst418 = (fConst385 + 0.935140193f);
		fConst419 = tanf((785.398193f / fConst0));
		fConst420 = (1.0f / fConst419);
		fConst421 = (1.0f / (((fConst420 + 0.157482162f) / fConst419) + 0.935140193f));
		fConst422 = mydsp_faustpower2_f(fConst419);
		fConst423 = (50.0638084f / fConst422);
		fConst424 = (2.0f * (0.935140193f - fConst423));
		fConst425 = (1.0f / (((fConst420 + 0.743130445f) / fConst419) + 1.4500711f));
		fConst426 = (11.0520525f / fConst422);
		fConst427 = (2.0f * (1.4500711f - fConst426));
		fConst428 = (1.0f / (((fConst420 + 3.18972731f) / fConst419) + 4.07678175f));
		fConst429 = (0.00176617282f / fConst422);
		fConst430 = (2.0f * (0.000407678192f - fConst429));
		fConst431 = (1.0f / (((fConst382 + 0.168404877f) / fConst381) + 1.06935835f));
		fConst432 = (2.0f * (53.5361519f - fConst410));
		fConst433 = (1.0f / (((fConst382 + 0.51247865f) / fConst381) + 0.689621389f));
		fConst434 = (2.0f * (7.62173128f - fConst410));
		fConst435 = (1.0f / (((fConst382 + 0.782413065f) / fConst381) + 0.245291501f));
		fConst436 = (9.99999975e-05f / fConst384);
		fConst437 = (2.0f * (0.000433227193f - fConst436));
		fConst438 = (((fConst382 + -0.782413065f) / fConst381) + 0.245291501f);
		fConst439 = (2.0f * (0.245291501f - fConst410));
		fConst440 = (fConst436 + 0.000433227193f);
		fConst441 = (((fConst382 + -0.51247865f) / fConst381) + 0.689621389f);
		fConst442 = (2.0f * (0.689621389f - fConst410));
		fConst443 = (fConst410 + 7.62173128f);
		fConst444 = (((fConst382 + -0.168404877f) / fConst381) + 1.06935835f);
		fConst445 = (2.0f * (1.06935835f - fConst410));
		fConst446 = (fConst410 + 53.5361519f);
		fConst447 = (((fConst420 + -3.18972731f) / fConst419) + 4.07678175f);
		fConst448 = (1.0f / fConst422);
		fConst449 = (2.0f * (4.07678175f - fConst448));
		fConst450 = (fConst429 + 0.000407678192f);
		fConst451 = (((fConst420 + -0.743130445f) / fConst419) + 1.4500711f);
		fConst452 = (2.0f * (1.4500711f - fConst448));
		fConst453 = (fConst426 + 1.4500711f);
		fConst454 = (((fConst420 + -0.157482162f) / fConst419) + 0.935140193f);
		fConst455 = (2.0f * (0.935140193f - fConst448));
		fConst456 = (fConst423 + 0.935140193f);
		fConst457 = tanf((494.769836f / fConst0));
		fConst458 = (1.0f / fConst457);
		fConst459 = (1.0f / (((fConst458 + 0.157482162f) / fConst457) + 0.935140193f));
		fConst460 = mydsp_faustpower2_f(fConst457);
		fConst461 = (50.0638084f / fConst460);
		fConst462 = (2.0f * (0.935140193f - fConst461));
		fConst463 = (1.0f / (((fConst458 + 0.743130445f) / fConst457) + 1.4500711f));
		fConst464 = (11.0520525f / fConst460);
		fConst465 = (2.0f * (1.4500711f - fConst464));
		fConst466 = (1.0f / (((fConst458 + 3.18972731f) / fConst457) + 4.07678175f));
		fConst467 = (0.00176617282f / fConst460);
		fConst468 = (2.0f * (0.000407678192f - fConst467));
		fConst469 = (1.0f / (((fConst420 + 0.168404877f) / fConst419) + 1.06935835f));
		fConst470 = (2.0f * (53.5361519f - fConst448));
		fConst471 = (1.0f / (((fConst420 + 0.51247865f) / fConst419) + 0.689621389f));
		fConst472 = (2.0f * (7.62173128f - fConst448));
		fConst473 = (1.0f / (((fConst420 + 0.782413065f) / fConst419) + 0.245291501f));
		fConst474 = (9.99999975e-05f / fConst422);
		fConst475 = (2.0f * (0.000433227193f - fConst474));
		fConst476 = (((fConst420 + -0.782413065f) / fConst419) + 0.245291501f);
		fConst477 = (2.0f * (0.245291501f - fConst448));
		fConst478 = (fConst474 + 0.000433227193f);
		fConst479 = (((fConst420 + -0.51247865f) / fConst419) + 0.689621389f);
		fConst480 = (2.0f * (0.689621389f - fConst448));
		fConst481 = (fConst448 + 7.62173128f);
		fConst482 = (((fConst420 + -0.168404877f) / fConst419) + 1.06935835f);
		fConst483 = (2.0f * (1.06935835f - fConst448));
		fConst484 = (fConst448 + 53.5361519f);
		fConst485 = (((fConst458 + -3.18972731f) / fConst457) + 4.07678175f);
		fConst486 = (1.0f / fConst460);
		fConst487 = (2.0f * (4.07678175f - fConst486));
		fConst488 = (fConst467 + 0.000407678192f);
		fConst489 = (((fConst458 + -0.743130445f) / fConst457) + 1.4500711f);
		fConst490 = (2.0f * (1.4500711f - fConst486));
		fConst491 = (fConst464 + 1.4500711f);
		fConst492 = (((fConst458 + -0.157482162f) / fConst457) + 0.935140193f);
		fConst493 = (2.0f * (0.935140193f - fConst486));
		fConst494 = (fConst461 + 0.935140193f);
		fConst495 = tanf((311.685455f / fConst0));
		fConst496 = (1.0f / fConst495);
		fConst497 = (1.0f / (((fConst496 + 0.157482162f) / fConst495) + 0.935140193f));
		fConst498 = mydsp_faustpower2_f(fConst495);
		fConst499 = (50.0638084f / fConst498);
		fConst500 = (2.0f * (0.935140193f - fConst499));
		fConst501 = (1.0f / (((fConst496 + 0.743130445f) / fConst495) + 1.4500711f));
		fConst502 = (11.0520525f / fConst498);
		fConst503 = (2.0f * (1.4500711f - fConst502));
		fConst504 = (1.0f / (((fConst496 + 3.18972731f) / fConst495) + 4.07678175f));
		fConst505 = (0.00176617282f / fConst498);
		fConst506 = (2.0f * (0.000407678192f - fConst505));
		fConst507 = (1.0f / (((fConst458 + 0.168404877f) / fConst457) + 1.06935835f));
		fConst508 = (2.0f * (53.5361519f - fConst486));
		fConst509 = (1.0f / (((fConst458 + 0.51247865f) / fConst457) + 0.689621389f));
		fConst510 = (2.0f * (7.62173128f - fConst486));
		fConst511 = (1.0f / (((fConst458 + 0.782413065f) / fConst457) + 0.245291501f));
		fConst512 = (9.99999975e-05f / fConst460);
		fConst513 = (2.0f * (0.000433227193f - fConst512));
		fConst514 = (((fConst458 + -0.782413065f) / fConst457) + 0.245291501f);
		fConst515 = (2.0f * (0.245291501f - fConst486));
		fConst516 = (fConst512 + 0.000433227193f);
		fConst517 = (((fConst458 + -0.51247865f) / fConst457) + 0.689621389f);
		fConst518 = (2.0f * (0.689621389f - fConst486));
		fConst519 = (fConst486 + 7.62173128f);
		fConst520 = (((fConst458 + -0.168404877f) / fConst457) + 1.06935835f);
		fConst521 = (2.0f * (1.06935835f - fConst486));
		fConst522 = (fConst486 + 53.5361519f);
		fConst523 = (((fConst496 + -3.18972731f) / fConst495) + 4.07678175f);
		fConst524 = (1.0f / fConst498);
		fConst525 = (2.0f * (4.07678175f - fConst524));
		fConst526 = (fConst505 + 0.000407678192f);
		fConst527 = (((fConst496 + -0.743130445f) / fConst495) + 1.4500711f);
		fConst528 = (2.0f * (1.4500711f - fConst524));
		fConst529 = (fConst502 + 1.4500711f);
		fConst530 = (((fConst496 + -0.157482162f) / fConst495) + 0.935140193f);
		fConst531 = (2.0f * (0.935140193f - fConst524));
		fConst532 = (fConst499 + 0.935140193f);
		fConst533 = tanf((196.349548f / fConst0));
		fConst534 = (1.0f / fConst533);
		fConst535 = (1.0f / (((fConst534 + 0.157482162f) / fConst533) + 0.935140193f));
		fConst536 = mydsp_faustpower2_f(fConst533);
		fConst537 = (50.0638084f / fConst536);
		fConst538 = (2.0f * (0.935140193f - fConst537));
		fConst539 = (1.0f / (((fConst534 + 0.743130445f) / fConst533) + 1.4500711f));
		fConst540 = (11.0520525f / fConst536);
		fConst541 = (2.0f * (1.4500711f - fConst540));
		fConst542 = (1.0f / (((fConst534 + 3.18972731f) / fConst533) + 4.07678175f));
		fConst543 = (0.00176617282f / fConst536);
		fConst544 = (2.0f * (0.000407678192f - fConst543));
		fConst545 = (1.0f / (((fConst496 + 0.168404877f) / fConst495) + 1.06935835f));
		fConst546 = (2.0f * (53.5361519f - fConst524));
		fConst547 = (1.0f / (((fConst496 + 0.51247865f) / fConst495) + 0.689621389f));
		fConst548 = (2.0f * (7.62173128f - fConst524));
		fConst549 = (1.0f / (((fConst496 + 0.782413065f) / fConst495) + 0.245291501f));
		fConst550 = (9.99999975e-05f / fConst498);
		fConst551 = (2.0f * (0.000433227193f - fConst550));
		fConst552 = (((fConst496 + -0.782413065f) / fConst495) + 0.245291501f);
		fConst553 = (2.0f * (0.245291501f - fConst524));
		fConst554 = (fConst550 + 0.000433227193f);
		fConst555 = (((fConst496 + -0.51247865f) / fConst495) + 0.689621389f);
		fConst556 = (2.0f * (0.689621389f - fConst524));
		fConst557 = (fConst524 + 7.62173128f);
		fConst558 = (((fConst496 + -0.168404877f) / fConst495) + 1.06935835f);
		fConst559 = (2.0f * (1.06935835f - fConst524));
		fConst560 = (fConst524 + 53.5361519f);
		fConst561 = (((fConst534 + -3.18972731f) / fConst533) + 4.07678175f);
		fConst562 = (1.0f / fConst536);
		fConst563 = (2.0f * (4.07678175f - fConst562));
		fConst564 = (fConst543 + 0.000407678192f);
		fConst565 = (((fConst534 + -0.743130445f) / fConst533) + 1.4500711f);
		fConst566 = (2.0f * (1.4500711f - fConst562));
		fConst567 = (fConst540 + 1.4500711f);
		fConst568 = (((fConst534 + -0.157482162f) / fConst533) + 0.935140193f);
		fConst569 = (2.0f * (0.935140193f - fConst562));
		fConst570 = (fConst537 + 0.935140193f);
		fConst571 = tanf((123.692459f / fConst0));
		fConst572 = (1.0f / fConst571);
		fConst573 = (1.0f / (((fConst572 + 0.157482162f) / fConst571) + 0.935140193f));
		fConst574 = mydsp_faustpower2_f(fConst571);
		fConst575 = (50.0638084f / fConst574);
		fConst576 = (2.0f * (0.935140193f - fConst575));
		fConst577 = (1.0f / (((fConst572 + 0.743130445f) / fConst571) + 1.4500711f));
		fConst578 = (11.0520525f / fConst574);
		fConst579 = (2.0f * (1.4500711f - fConst578));
		fConst580 = (1.0f / (((fConst572 + 3.18972731f) / fConst571) + 4.07678175f));
		fConst581 = (0.00176617282f / fConst574);
		fConst582 = (2.0f * (0.000407678192f - fConst581));
		fConst583 = (1.0f / (((fConst534 + 0.168404877f) / fConst533) + 1.06935835f));
		fConst584 = (2.0f * (53.5361519f - fConst562));
		fConst585 = (1.0f / (((fConst534 + 0.51247865f) / fConst533) + 0.689621389f));
		fConst586 = (2.0f * (7.62173128f - fConst562));
		fConst587 = (1.0f / (((fConst534 + 0.782413065f) / fConst533) + 0.245291501f));
		fConst588 = (9.99999975e-05f / fConst536);
		fConst589 = (2.0f * (0.000433227193f - fConst588));
		fConst590 = (((fConst534 + -0.782413065f) / fConst533) + 0.245291501f);
		fConst591 = (2.0f * (0.245291501f - fConst562));
		fConst592 = (fConst588 + 0.000433227193f);
		fConst593 = (((fConst534 + -0.51247865f) / fConst533) + 0.689621389f);
		fConst594 = (2.0f * (0.689621389f - fConst562));
		fConst595 = (fConst562 + 7.62173128f);
		fConst596 = (((fConst534 + -0.168404877f) / fConst533) + 1.06935835f);
		fConst597 = (2.0f * (1.06935835f - fConst562));
		fConst598 = (fConst562 + 53.5361519f);
		fConst599 = (((fConst572 + -3.18972731f) / fConst571) + 4.07678175f);
		fConst600 = (1.0f / fConst574);
		fConst601 = (2.0f * (4.07678175f - fConst600));
		fConst602 = (fConst581 + 0.000407678192f);
		fConst603 = (((fConst572 + -0.743130445f) / fConst571) + 1.4500711f);
		fConst604 = (2.0f * (1.4500711f - fConst600));
		fConst605 = (fConst578 + 1.4500711f);
		fConst606 = (((fConst572 + -0.157482162f) / fConst571) + 0.935140193f);
		fConst607 = (2.0f * (0.935140193f - fConst600));
		fConst608 = (fConst575 + 0.935140193f);
		fConst609 = (1.0f / (((fConst572 + 0.168404877f) / fConst571) + 1.06935835f));
		fConst610 = (2.0f * (53.5361519f - fConst600));
		fConst611 = (1.0f / (((fConst572 + 0.51247865f) / fConst571) + 0.689621389f));
		fConst612 = (2.0f * (7.62173128f - fConst600));
		fConst613 = (1.0f / (((fConst572 + 0.782413065f) / fConst571) + 0.245291501f));
		fConst614 = (9.99999975e-05f / fConst574);
		fConst615 = (2.0f * (0.000433227193f - fConst614));
		fConst616 = (((fConst572 + -0.782413065f) / fConst571) + 0.245291501f);
		fConst617 = (2.0f * (0.245291501f - fConst600));
		fConst618 = (fConst614 + 0.000433227193f);
		fConst619 = (((fConst572 + -0.51247865f) / fConst571) + 0.689621389f);
		fConst620 = (2.0f * (0.689621389f - fConst600));
		fConst621 = (fConst600 + 7.62173128f);
		fConst622 = (((fConst572 + -0.168404877f) / fConst571) + 1.06935835f);
		fConst623 = (2.0f * (1.06935835f - fConst600));
		fConst624 = (fConst600 + 53.5361519f);
		fConst625 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst626 = (50.0638084f / fConst39);
		fConst627 = (2.0f * (0.935140193f - fConst626));
		fConst628 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst629 = (11.0520525f / fConst39);
		fConst630 = (2.0f * (1.4500711f - fConst629));
		fConst631 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst632 = (0.00176617282f / fConst39);
		fConst633 = (2.0f * (0.000407678192f - fConst632));
		fConst634 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst635 = (2.0f * (4.07678175f - fConst40));
		fConst636 = (fConst632 + 0.000407678192f);
		fConst637 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst638 = (2.0f * (1.4500711f - fConst40));
		fConst639 = (fConst629 + 1.4500711f);
		fConst640 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst641 = (2.0f * (0.935140193f - fConst40));
		fConst642 = (fConst626 + 0.935140193f);
		fConst643 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst644 = (50.0638084f / fConst28);
		fConst645 = (2.0f * (0.935140193f - fConst644));
		fConst646 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst647 = (11.0520525f / fConst28);
		fConst648 = (2.0f * (1.4500711f - fConst647));
		fConst649 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst650 = (0.00176617282f / fConst28);
		fConst651 = (2.0f * (0.000407678192f - fConst650));
		fConst652 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst653 = (2.0f * (4.07678175f - fConst29));
		fConst654 = (fConst650 + 0.000407678192f);
		fConst655 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst656 = (2.0f * (1.4500711f - fConst29));
		fConst657 = (fConst647 + 1.4500711f);
		fConst658 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst659 = (2.0f * (0.935140193f - fConst29));
		fConst660 = (fConst644 + 0.935140193f);
		fConst661 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst662 = (50.0638084f / fConst17);
		fConst663 = (2.0f * (0.935140193f - fConst662));
		fConst664 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst665 = (11.0520525f / fConst17);
		fConst666 = (2.0f * (1.4500711f - fConst665));
		fConst667 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst668 = (0.00176617282f / fConst17);
		fConst669 = (2.0f * (0.000407678192f - fConst668));
		fConst670 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst671 = (2.0f * (4.07678175f - fConst18));
		fConst672 = (fConst668 + 0.000407678192f);
		fConst673 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst674 = (2.0f * (1.4500711f - fConst18));
		fConst675 = (fConst665 + 1.4500711f);
		fConst676 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst677 = (2.0f * (0.935140193f - fConst18));
		fConst678 = (fConst662 + 0.935140193f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(-20.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fVslider5 = FAUSTFLOAT(-10.0f);
		fVslider6 = FAUSTFLOAT(-10.0f);
		fVslider7 = FAUSTFLOAT(-10.0f);
		fVslider8 = FAUSTFLOAT(-10.0f);
		fVslider9 = FAUSTFLOAT(-10.0f);
		fVslider10 = FAUSTFLOAT(-10.0f);
		fVslider11 = FAUSTFLOAT(-10.0f);
		fVslider12 = FAUSTFLOAT(-10.0f);
		fVslider13 = FAUSTFLOAT(-10.0f);
		fVslider14 = FAUSTFLOAT(-10.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec24[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec26[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec25[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec4[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec5[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec6[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec7[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec8[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec27[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec9[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec10[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec11[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec12[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec13[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec14[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec15[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec28[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec16[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec17[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec18[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec19[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec20[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec21[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			iRec29[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec30[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec22[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec23[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec22[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec21[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec20[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec19[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec18[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec17[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec16[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec15[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec14[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec13[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec31[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec44[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec43[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec42[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec23[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec41[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec40[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec39[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec38[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec37[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec36[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec35[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec34[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec33[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec32[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec45[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec57[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec56[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec55[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec24[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec54[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec53[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec52[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec51[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec50[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec49[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec48[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec47[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec46[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec58[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec69[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec68[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec67[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fVec25[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec66[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec65[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec64[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec63[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec62[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec61[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec60[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec59[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec70[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec80[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec79[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec78[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fVec26[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec77[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec76[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec75[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec74[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec73[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec72[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec71[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			fRec81[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec90[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec89[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec88[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fVec27[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec87[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec86[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec85[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec84[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec83[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec82[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec91[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec99[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec98[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec97[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fVec28[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec96[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec95[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec94[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec93[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec92[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fRec100[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec107[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec106[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec105[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fVec29[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fRec104[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec103[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec102[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec101[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec108[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec114[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec113[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec112[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fVec30[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec111[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec110[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec109[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec115[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec118[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec117[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec116[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			fRec119[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec12[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec11[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec10[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec9[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec8[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec7[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec6[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec5[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec4[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			fRec3[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			fRec2[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec1[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			fRec0[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec126[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			fRec125[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec124[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			fRec123[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 3); l155 = (l155 + 1)) {
			fRec122[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			fRec121[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 2); l157 = (l157 + 1)) {
			fRec120[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			fRec133[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			fRec132[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			fRec131[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			fRec130[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 3); l162 = (l162 + 1)) {
			fRec129[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			fRec128[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 2); l164 = (l164 + 1)) {
			fRec127[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			fRec140[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 3); l166 = (l166 + 1)) {
			fRec139[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			fRec138[l167] = 0.0f;
			
		}
		for (int l168 = 0; (l168 < 3); l168 = (l168 + 1)) {
			fRec137[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 3); l169 = (l169 + 1)) {
			fRec136[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			fRec135[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) {
			fRec134[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 3); l172 = (l172 + 1)) {
			fRec147[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			fRec146[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 3); l174 = (l174 + 1)) {
			fRec145[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 3); l175 = (l175 + 1)) {
			fRec144[l175] = 0.0f;
			
		}
		for (int l176 = 0; (l176 < 3); l176 = (l176 + 1)) {
			fRec143[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 3); l177 = (l177 + 1)) {
			fRec142[l177] = 0.0f;
			
		}
		for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) {
			fRec141[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 3); l179 = (l179 + 1)) {
			fRec154[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 3); l180 = (l180 + 1)) {
			fRec153[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 3); l181 = (l181 + 1)) {
			fRec152[l181] = 0.0f;
			
		}
		for (int l182 = 0; (l182 < 3); l182 = (l182 + 1)) {
			fRec151[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 3); l183 = (l183 + 1)) {
			fRec150[l183] = 0.0f;
			
		}
		for (int l184 = 0; (l184 < 3); l184 = (l184 + 1)) {
			fRec149[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 2); l185 = (l185 + 1)) {
			fRec148[l185] = 0.0f;
			
		}
		for (int l186 = 0; (l186 < 3); l186 = (l186 + 1)) {
			fRec161[l186] = 0.0f;
			
		}
		for (int l187 = 0; (l187 < 3); l187 = (l187 + 1)) {
			fRec160[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			fRec159[l188] = 0.0f;
			
		}
		for (int l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			fRec158[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 3); l190 = (l190 + 1)) {
			fRec157[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 3); l191 = (l191 + 1)) {
			fRec156[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			fRec155[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 3); l193 = (l193 + 1)) {
			fRec168[l193] = 0.0f;
			
		}
		for (int l194 = 0; (l194 < 3); l194 = (l194 + 1)) {
			fRec167[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 3); l195 = (l195 + 1)) {
			fRec166[l195] = 0.0f;
			
		}
		for (int l196 = 0; (l196 < 3); l196 = (l196 + 1)) {
			fRec165[l196] = 0.0f;
			
		}
		for (int l197 = 0; (l197 < 3); l197 = (l197 + 1)) {
			fRec164[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 3); l198 = (l198 + 1)) {
			fRec163[l198] = 0.0f;
			
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			fRec162[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 3); l200 = (l200 + 1)) {
			fRec175[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 3); l201 = (l201 + 1)) {
			fRec174[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 3); l202 = (l202 + 1)) {
			fRec173[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			fRec172[l203] = 0.0f;
			
		}
		for (int l204 = 0; (l204 < 3); l204 = (l204 + 1)) {
			fRec171[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 3); l205 = (l205 + 1)) {
			fRec170[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 2); l206 = (l206 + 1)) {
			fRec169[l206] = 0.0f;
			
		}
		for (int l207 = 0; (l207 < 3); l207 = (l207 + 1)) {
			fRec182[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 3); l208 = (l208 + 1)) {
			fRec181[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 3); l209 = (l209 + 1)) {
			fRec180[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 3); l210 = (l210 + 1)) {
			fRec179[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 3); l211 = (l211 + 1)) {
			fRec178[l211] = 0.0f;
			
		}
		for (int l212 = 0; (l212 < 3); l212 = (l212 + 1)) {
			fRec177[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 2); l213 = (l213 + 1)) {
			fRec176[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 3); l214 = (l214 + 1)) {
			fRec189[l214] = 0.0f;
			
		}
		for (int l215 = 0; (l215 < 3); l215 = (l215 + 1)) {
			fRec188[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 3); l216 = (l216 + 1)) {
			fRec187[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 3); l217 = (l217 + 1)) {
			fRec186[l217] = 0.0f;
			
		}
		for (int l218 = 0; (l218 < 3); l218 = (l218 + 1)) {
			fRec185[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 3); l219 = (l219 + 1)) {
			fRec184[l219] = 0.0f;
			
		}
		for (int l220 = 0; (l220 < 2); l220 = (l220 + 1)) {
			fRec183[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			fRec193[l221] = 0.0f;
			
		}
		for (int l222 = 0; (l222 < 3); l222 = (l222 + 1)) {
			fRec192[l222] = 0.0f;
			
		}
		for (int l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			fRec191[l223] = 0.0f;
			
		}
		for (int l224 = 0; (l224 < 2); l224 = (l224 + 1)) {
			fRec190[l224] = 0.0f;
			
		}
		for (int l225 = 0; (l225 < 3); l225 = (l225 + 1)) {
			fRec197[l225] = 0.0f;
			
		}
		for (int l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			fRec196[l226] = 0.0f;
			
		}
		for (int l227 = 0; (l227 < 3); l227 = (l227 + 1)) {
			fRec195[l227] = 0.0f;
			
		}
		for (int l228 = 0; (l228 < 2); l228 = (l228 + 1)) {
			fRec194[l228] = 0.0f;
			
		}
		for (int l229 = 0; (l229 < 3); l229 = (l229 + 1)) {
			fRec201[l229] = 0.0f;
			
		}
		for (int l230 = 0; (l230 < 3); l230 = (l230 + 1)) {
			fRec200[l230] = 0.0f;
			
		}
		for (int l231 = 0; (l231 < 3); l231 = (l231 + 1)) {
			fRec199[l231] = 0.0f;
			
		}
		for (int l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			fRec198[l232] = 0.0f;
			
		}
		for (int l233 = 0; (l233 < 3); l233 = (l233 + 1)) {
			fRec205[l233] = 0.0f;
			
		}
		for (int l234 = 0; (l234 < 3); l234 = (l234 + 1)) {
			fRec204[l234] = 0.0f;
			
		}
		for (int l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			fRec203[l235] = 0.0f;
			
		}
		for (int l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			fRec202[l236] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("graphicEqLab");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Sawtooth   waveform amplitude");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fVslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider1, "2", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fVslider1, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fVslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider4, "4", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider2, "5", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider2, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fCheckbox2, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", &fCheckbox2);
		ui_interface->declare(&fCheckbox3, "1", "");
		ui_interface->declare(&fCheckbox3, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox3);
		ui_interface->declare(&fCheckbox1, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openVerticalBox("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the filter-bank has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider14, "1", "");
		ui_interface->declare(&fVslider14, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider14, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider14, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider13, "2", "");
		ui_interface->declare(&fVslider13, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider13, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider13, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider12, "3", "");
		ui_interface->declare(&fVslider12, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider12, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider12, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider11, "4", "");
		ui_interface->declare(&fVslider11, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider11, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider11, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider10, "5", "");
		ui_interface->declare(&fVslider10, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider10, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider10, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider9, "6", "");
		ui_interface->declare(&fVslider9, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider9, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider9, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider8, "7", "");
		ui_interface->declare(&fVslider8, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider8, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider8, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider7, "8", "");
		ui_interface->declare(&fVslider7, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider7, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider7, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider6, "9", "");
		ui_interface->declare(&fVslider6, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider6, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider6, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider5, "10", "");
		ui_interface->declare(&fVslider5, "tooltip", "Bandpass filter   gain in dB");
		ui_interface->declare(&fVslider5, "unit", "dB");
		ui_interface->addVerticalSlider("0x00", &fVslider5, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph11, "0", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba312c36b0", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "1", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba312b1d50", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "2", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba3128fc00", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "3", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba3126dab0", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "4", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba3124b960", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "5", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba31229810", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "6", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba312076c0", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "7", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba311e15f0", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "8", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba311bf4a0", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "9", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba3119d350", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "10", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba3117b200", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "11", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba311592d0", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph14, "12", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba312fac70", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "13", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba312e8270", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "14", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fba312d5870", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, 50.0f, -50.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = expf((0.0f - (fConst1 / float(fHslider1))));
		float fSlow2 = (1.0f - fSlow1);
		int iSlow3 = int(float(fCheckbox0));
		float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider0))));
		int iSlow5 = int(float(fCheckbox1));
		int iSlow6 = int(float(fCheckbox2));
		int iSlow7 = int((float(fEntry0) + -1.0f));
		int iSlow8 = (iSlow7 >= 2);
		int iSlow9 = (iSlow7 >= 1);
		float fSlow10 = expf((0.0f - (fConst61 / float(fVslider2))));
		float fSlow11 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fVslider1) + -49.0f))) * (1.0f - fSlow10)));
		int iSlow12 = (iSlow7 >= 3);
		float fSlow13 = ((0.00999999978f * float(fVslider3)) + 1.0f);
		float fSlow14 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		int iSlow15 = int(float(fCheckbox3));
		float fSlow16 = (0.00100000005f * float(fVslider5));
		float fSlow17 = (0.00100000005f * float(fVslider6));
		float fSlow18 = (0.00100000005f * float(fVslider7));
		float fSlow19 = (0.00100000005f * float(fVslider8));
		float fSlow20 = (0.00100000005f * float(fVslider9));
		float fSlow21 = (0.00100000005f * float(fVslider10));
		float fSlow22 = (0.00100000005f * float(fVslider11));
		float fSlow23 = (0.00100000005f * float(fVslider12));
		float fSlow24 = (0.00100000005f * float(fVslider13));
		float fSlow25 = (0.00100000005f * float(fVslider14));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec24[0] = (fSlow4 + (0.999000013f * fRec24[1]));
			fRec26[0] = (fSlow11 + (fSlow10 * fRec26[1]));
			float fTemp0 = max(20.0f, fabsf(fRec26[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec25[1] + (fConst61 * fVec1[1]));
			fRec25[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * fRec25[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = mydsp_faustpower2_f(fTemp3);
			fVec2[0] = fTemp4;
			float fTemp5 = mydsp_faustpower3_f(fTemp3);
			fVec3[0] = (fTemp5 + (1.0f - fTemp2));
			float fTemp6 = ((fTemp5 + (1.0f - (fVec3[1] + fTemp2))) / fTemp0);
			fVec4[0] = fTemp6;
			float fTemp7 = (fTemp4 * (fTemp4 + -2.0f));
			fVec5[0] = fTemp7;
			float fTemp8 = ((fTemp7 - fVec5[1]) / fTemp0);
			fVec6[0] = fTemp8;
			float fTemp9 = ((fTemp8 - fVec6[1]) / fTemp0);
			fVec7[0] = fTemp9;
			float fTemp10 = max(20.0f, fabsf((fSlow13 * fRec26[0])));
			fVec8[0] = fTemp10;
			float fTemp11 = (fRec27[1] + (fConst61 * fVec8[1]));
			fRec27[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (2.0f * fRec27[0]);
			float fTemp13 = (fTemp12 + -1.0f);
			float fTemp14 = mydsp_faustpower2_f(fTemp13);
			fVec9[0] = fTemp14;
			float fTemp15 = mydsp_faustpower3_f(fTemp13);
			fVec10[0] = (fTemp15 + (1.0f - fTemp12));
			float fTemp16 = ((fTemp15 + (1.0f - (fVec10[1] + fTemp12))) / fTemp10);
			fVec11[0] = fTemp16;
			float fTemp17 = (fTemp14 * (fTemp14 + -2.0f));
			fVec12[0] = fTemp17;
			float fTemp18 = ((fTemp17 - fVec12[1]) / fTemp10);
			fVec13[0] = fTemp18;
			float fTemp19 = ((fTemp18 - fVec13[1]) / fTemp10);
			fVec14[0] = fTemp19;
			float fTemp20 = max(20.0f, fabsf((fSlow14 * fRec26[0])));
			fVec15[0] = fTemp20;
			float fTemp21 = (fRec28[1] + (fConst61 * fVec15[1]));
			fRec28[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (2.0f * fRec28[0]);
			float fTemp23 = (fTemp22 + -1.0f);
			float fTemp24 = mydsp_faustpower2_f(fTemp23);
			fVec16[0] = fTemp24;
			float fTemp25 = mydsp_faustpower3_f(fTemp23);
			fVec17[0] = (fTemp25 + (1.0f - fTemp22));
			float fTemp26 = ((fTemp25 + (1.0f - (fVec17[1] + fTemp22))) / fTemp20);
			fVec18[0] = fTemp26;
			float fTemp27 = (fTemp24 * (fTemp24 + -2.0f));
			fVec19[0] = fTemp27;
			float fTemp28 = ((fTemp27 - fVec19[1]) / fTemp20);
			fVec20[0] = fTemp28;
			float fTemp29 = ((fTemp28 - fVec20[1]) / fTemp20);
			fVec21[0] = fTemp29;
			iRec29[0] = ((1103515245 * iRec29[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * float(iRec29[0]));
			fRec30[0] = (((0.522189379f * fRec30[3]) + (fTemp30 + (2.49495602f * fRec30[1]))) - (2.0172658f * fRec30[2]));
			float fTemp31 = (fRec24[0] * (iSlow5?float(input0[i]):(iSlow6?(iSlow15?(((0.0499220341f * fRec30[0]) + (0.0506126992f * fRec30[2])) - ((0.0959935337f * fRec30[1]) + (0.00440878607f * fRec30[3]))):fTemp30):(0.333333343f * (fRec24[0] * (((iSlow8?(iSlow12?(fConst64 * ((float(iVec0[3]) * (fTemp9 - fVec7[1])) / fTemp0)):(fConst63 * ((float(iVec0[2]) * (fTemp6 - fVec4[1])) / fTemp0))):(iSlow9?(fConst62 * ((float(iVec0[1]) * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (iSlow8?(iSlow12?(fConst64 * ((float(iVec0[3]) * (fTemp19 - fVec14[1])) / fTemp10)):(fConst63 * ((float(iVec0[2]) * (fTemp16 - fVec11[1])) / fTemp10))):(iSlow9?(fConst62 * ((float(iVec0[1]) * (fTemp14 - fVec9[1])) / fTemp10)):fTemp13))) + (iSlow8?(iSlow12?(fConst64 * ((float(iVec0[3]) * (fTemp29 - fVec21[1])) / fTemp20)):(fConst63 * ((float(iVec0[2]) * (fTemp26 - fVec18[1])) / fTemp20))):(iSlow9?(fConst62 * ((float(iVec0[1]) * (fTemp24 - fVec16[1])) / fTemp20)):fTemp23))))))));
			float fTemp32 = (iSlow3?0.0f:fTemp31);
			fVec22[0] = fTemp32;
			fRec23[0] = ((fConst59 * fRec23[1]) + (fConst60 * ((fConst52 * fTemp32) + (fConst65 * fVec22[1]))));
			fRec22[0] = (fRec23[0] - (fConst57 * ((fConst66 * fRec22[1]) + (fConst67 * fRec22[2]))));
			fRec21[0] = ((fConst57 * (((fConst55 * fRec22[0]) + (fConst56 * fRec22[1])) + (fConst55 * fRec22[2]))) - (fConst54 * ((fConst66 * fRec21[1]) + (fConst68 * fRec21[2]))));
			float fTemp33 = (fConst74 * fRec20[1]);
			fRec20[0] = ((fConst54 * (((fConst56 * fRec21[1]) + (fConst55 * fRec21[0])) + (fConst55 * fRec21[2]))) - (fConst71 * ((fConst72 * fRec20[2]) + fTemp33)));
			float fTemp34 = (fConst80 * fRec19[1]);
			fRec19[0] = ((fRec20[2] + (fConst71 * (fTemp33 + (fConst72 * fRec20[0])))) - (fConst77 * ((fConst78 * fRec19[2]) + fTemp34)));
			float fTemp35 = (fConst86 * fRec18[1]);
			fRec18[0] = ((fRec19[2] + (fConst77 * (fTemp34 + (fConst78 * fRec19[0])))) - (fConst83 * ((fConst84 * fRec18[2]) + fTemp35)));
			float fTemp36 = (fConst92 * fRec17[1]);
			fRec17[0] = ((fRec18[2] + (fConst83 * (fTemp35 + (fConst84 * fRec18[0])))) - (fConst89 * ((fConst90 * fRec17[2]) + fTemp36)));
			float fTemp37 = (fConst98 * fRec16[1]);
			fRec16[0] = ((fRec17[2] + (fConst89 * (fTemp36 + (fConst90 * fRec17[0])))) - (fConst95 * ((fConst96 * fRec16[2]) + fTemp37)));
			float fTemp38 = (fConst104 * fRec15[1]);
			fRec15[0] = ((fRec16[2] + (fConst95 * (fTemp37 + (fConst96 * fRec16[0])))) - (fConst101 * ((fConst102 * fRec15[2]) + fTemp38)));
			float fTemp39 = (fConst106 * fRec14[1]);
			fRec14[0] = ((fRec15[2] + (fConst101 * (fTemp38 + (fConst102 * fRec15[0])))) - (fConst49 * ((fConst50 * fRec14[2]) + fTemp39)));
			float fTemp40 = (fConst112 * fRec13[1]);
			fRec13[0] = (((fConst49 * ((fConst50 * fRec14[0]) + fTemp39)) + fRec14[2]) - (fConst109 * ((fConst110 * fRec13[2]) + fTemp40)));
			fRec31[0] = (fSlow16 + (0.999000013f * fRec31[1]));
			fRec44[0] = ((fConst59 * fRec44[1]) + (fConst60 * (fTemp32 + fVec22[1])));
			fRec43[0] = (fRec44[0] - (fConst57 * ((fConst66 * fRec43[1]) + (fConst67 * fRec43[2]))));
			fRec42[0] = ((fConst57 * (fRec43[2] + ((2.0f * fRec43[1]) + fRec43[0]))) - (fConst54 * ((fConst66 * fRec42[1]) + (fConst68 * fRec42[2]))));
			float fTemp41 = (fRec42[2] + ((2.0f * fRec42[1]) + fRec42[0]));
			fVec23[0] = fTemp41;
			fRec41[0] = ((fConst118 * fRec41[1]) + (fConst119 * ((fConst108 * fTemp41) + (fConst120 * fVec23[1]))));
			fRec40[0] = (fRec41[0] - (fConst116 * ((fConst112 * fRec40[1]) + (fConst121 * fRec40[2]))));
			fRec39[0] = ((fConst116 * (((fConst111 * fRec40[0]) + (fConst115 * fRec40[1])) + (fConst111 * fRec40[2]))) - (fConst114 * ((fConst112 * fRec39[1]) + (fConst122 * fRec39[2]))));
			float fTemp42 = (fConst74 * fRec38[1]);
			fRec38[0] = ((fConst114 * (((fConst115 * fRec39[1]) + (fConst111 * fRec39[0])) + (fConst111 * fRec39[2]))) - (fConst71 * (fTemp42 + (fConst72 * fRec38[2]))));
			float fTemp43 = (fConst80 * fRec37[1]);
			fRec37[0] = ((fRec38[2] + (fConst71 * (fTemp42 + (fConst72 * fRec38[0])))) - (fConst77 * (fTemp43 + (fConst78 * fRec37[2]))));
			float fTemp44 = (fConst86 * fRec36[1]);
			fRec36[0] = ((fRec37[2] + (fConst77 * (fTemp43 + (fConst78 * fRec37[0])))) - (fConst83 * (fTemp44 + (fConst84 * fRec36[2]))));
			float fTemp45 = (fConst92 * fRec35[1]);
			fRec35[0] = ((fRec36[2] + (fConst83 * (fTemp44 + (fConst84 * fRec36[0])))) - (fConst89 * (fTemp45 + (fConst90 * fRec35[2]))));
			float fTemp46 = (fConst98 * fRec34[1]);
			fRec34[0] = ((fRec35[2] + (fConst89 * (fTemp45 + (fConst90 * fRec35[0])))) - (fConst95 * (fTemp46 + (fConst96 * fRec34[2]))));
			float fTemp47 = (fConst104 * fRec33[1]);
			fRec33[0] = ((fRec34[2] + (fConst95 * (fTemp46 + (fConst96 * fRec34[0])))) - (fConst101 * (fTemp47 + (fConst102 * fRec33[2]))));
			float fTemp48 = (fConst106 * fRec32[1]);
			fRec32[0] = ((fRec33[2] + (fConst101 * (fTemp47 + (fConst102 * fRec33[0])))) - (fConst49 * (fTemp48 + (fConst50 * fRec32[2]))));
			fRec45[0] = (fSlow17 + (0.999000013f * fRec45[1]));
			fRec57[0] = ((fConst118 * fRec57[1]) + (fConst119 * (fTemp41 + fVec23[1])));
			fRec56[0] = (fRec57[0] - (fConst116 * ((fConst112 * fRec56[1]) + (fConst121 * fRec56[2]))));
			fRec55[0] = ((fConst116 * (fRec56[2] + ((2.0f * fRec56[1]) + fRec56[0]))) - (fConst114 * ((fConst112 * fRec55[1]) + (fConst122 * fRec55[2]))));
			float fTemp49 = (fRec55[2] + ((2.0f * fRec55[1]) + fRec55[0]));
			fVec24[0] = fTemp49;
			fRec54[0] = ((fConst128 * fRec54[1]) + (fConst129 * ((fConst48 * fTemp49) + (fConst130 * fVec24[1]))));
			fRec53[0] = (fRec54[0] - (fConst126 * ((fConst106 * fRec53[1]) + (fConst131 * fRec53[2]))));
			fRec52[0] = ((fConst126 * (((fConst105 * fRec53[0]) + (fConst125 * fRec53[1])) + (fConst105 * fRec53[2]))) - (fConst124 * ((fConst106 * fRec52[1]) + (fConst132 * fRec52[2]))));
			float fTemp50 = (fConst74 * fRec51[1]);
			fRec51[0] = ((fConst124 * (((fConst125 * fRec52[1]) + (fConst105 * fRec52[0])) + (fConst105 * fRec52[2]))) - (fConst71 * (fTemp50 + (fConst72 * fRec51[2]))));
			float fTemp51 = (fConst80 * fRec50[1]);
			fRec50[0] = ((fRec51[2] + (fConst71 * (fTemp50 + (fConst72 * fRec51[0])))) - (fConst77 * (fTemp51 + (fConst78 * fRec50[2]))));
			float fTemp52 = (fConst86 * fRec49[1]);
			fRec49[0] = ((fRec50[2] + (fConst77 * (fTemp51 + (fConst78 * fRec50[0])))) - (fConst83 * (fTemp52 + (fConst84 * fRec49[2]))));
			float fTemp53 = (fConst92 * fRec48[1]);
			fRec48[0] = ((fRec49[2] + (fConst83 * (fTemp52 + (fConst84 * fRec49[0])))) - (fConst89 * (fTemp53 + (fConst90 * fRec48[2]))));
			float fTemp54 = (fConst98 * fRec47[1]);
			fRec47[0] = ((fRec48[2] + (fConst89 * (fTemp53 + (fConst90 * fRec48[0])))) - (fConst95 * (fTemp54 + (fConst96 * fRec47[2]))));
			float fTemp55 = (fConst104 * fRec46[1]);
			fRec46[0] = ((fRec47[2] + (fConst95 * (fTemp54 + (fConst96 * fRec47[0])))) - (fConst101 * (fTemp55 + (fConst102 * fRec46[2]))));
			fRec58[0] = (fSlow18 + (0.999000013f * fRec58[1]));
			fRec69[0] = ((fConst128 * fRec69[1]) + (fConst129 * (fTemp49 + fVec24[1])));
			fRec68[0] = (fRec69[0] - (fConst126 * ((fConst106 * fRec68[1]) + (fConst131 * fRec68[2]))));
			fRec67[0] = ((fConst126 * (fRec68[2] + ((2.0f * fRec68[1]) + fRec68[0]))) - (fConst124 * ((fConst106 * fRec67[1]) + (fConst132 * fRec67[2]))));
			float fTemp56 = (fRec67[2] + ((2.0f * fRec67[1]) + fRec67[0]));
			fVec25[0] = fTemp56;
			fRec66[0] = ((fConst138 * fRec66[1]) + (fConst139 * ((fConst100 * fTemp56) + (fConst140 * fVec25[1]))));
			fRec65[0] = (fRec66[0] - (fConst136 * ((fConst104 * fRec65[1]) + (fConst141 * fRec65[2]))));
			fRec64[0] = ((fConst136 * (((fConst103 * fRec65[0]) + (fConst135 * fRec65[1])) + (fConst103 * fRec65[2]))) - (fConst134 * ((fConst104 * fRec64[1]) + (fConst142 * fRec64[2]))));
			float fTemp57 = (fConst74 * fRec63[1]);
			fRec63[0] = ((fConst134 * (((fConst135 * fRec64[1]) + (fConst103 * fRec64[0])) + (fConst103 * fRec64[2]))) - (fConst71 * (fTemp57 + (fConst72 * fRec63[2]))));
			float fTemp58 = (fConst80 * fRec62[1]);
			fRec62[0] = ((fRec63[2] + (fConst71 * (fTemp57 + (fConst72 * fRec63[0])))) - (fConst77 * (fTemp58 + (fConst78 * fRec62[2]))));
			float fTemp59 = (fConst86 * fRec61[1]);
			fRec61[0] = ((fRec62[2] + (fConst77 * (fTemp58 + (fConst78 * fRec62[0])))) - (fConst83 * (fTemp59 + (fConst84 * fRec61[2]))));
			float fTemp60 = (fConst92 * fRec60[1]);
			fRec60[0] = ((fRec61[2] + (fConst83 * (fTemp59 + (fConst84 * fRec61[0])))) - (fConst89 * (fTemp60 + (fConst90 * fRec60[2]))));
			float fTemp61 = (fConst98 * fRec59[1]);
			fRec59[0] = ((fRec60[2] + (fConst89 * (fTemp60 + (fConst90 * fRec60[0])))) - (fConst95 * (fTemp61 + (fConst96 * fRec59[2]))));
			fRec70[0] = (fSlow19 + (0.999000013f * fRec70[1]));
			fRec80[0] = ((fConst138 * fRec80[1]) + (fConst139 * (fTemp56 + fVec25[1])));
			fRec79[0] = (fRec80[0] - (fConst136 * ((fConst104 * fRec79[1]) + (fConst141 * fRec79[2]))));
			fRec78[0] = ((fConst136 * (fRec79[2] + ((2.0f * fRec79[1]) + fRec79[0]))) - (fConst134 * ((fConst104 * fRec78[1]) + (fConst142 * fRec78[2]))));
			float fTemp62 = (fRec78[2] + ((2.0f * fRec78[1]) + fRec78[0]));
			fVec26[0] = fTemp62;
			fRec77[0] = ((fConst148 * fRec77[1]) + (fConst149 * ((fConst94 * fTemp62) + (fConst150 * fVec26[1]))));
			fRec76[0] = (fRec77[0] - (fConst146 * ((fConst98 * fRec76[1]) + (fConst151 * fRec76[2]))));
			fRec75[0] = ((fConst146 * (((fConst97 * fRec76[0]) + (fConst145 * fRec76[1])) + (fConst97 * fRec76[2]))) - (fConst144 * ((fConst98 * fRec75[1]) + (fConst152 * fRec75[2]))));
			float fTemp63 = (fConst74 * fRec74[1]);
			fRec74[0] = ((fConst144 * (((fConst145 * fRec75[1]) + (fConst97 * fRec75[0])) + (fConst97 * fRec75[2]))) - (fConst71 * (fTemp63 + (fConst72 * fRec74[2]))));
			float fTemp64 = (fConst80 * fRec73[1]);
			fRec73[0] = ((fRec74[2] + (fConst71 * (fTemp63 + (fConst72 * fRec74[0])))) - (fConst77 * (fTemp64 + (fConst78 * fRec73[2]))));
			float fTemp65 = (fConst86 * fRec72[1]);
			fRec72[0] = ((fRec73[2] + (fConst77 * (fTemp64 + (fConst78 * fRec73[0])))) - (fConst83 * (fTemp65 + (fConst84 * fRec72[2]))));
			float fTemp66 = (fConst92 * fRec71[1]);
			fRec71[0] = ((fRec72[2] + (fConst83 * (fTemp65 + (fConst84 * fRec72[0])))) - (fConst89 * (fTemp66 + (fConst90 * fRec71[2]))));
			fRec81[0] = (fSlow20 + (0.999000013f * fRec81[1]));
			fRec90[0] = ((fConst148 * fRec90[1]) + (fConst149 * (fTemp62 + fVec26[1])));
			fRec89[0] = (fRec90[0] - (fConst146 * ((fConst98 * fRec89[1]) + (fConst151 * fRec89[2]))));
			fRec88[0] = ((fConst146 * (fRec89[2] + ((2.0f * fRec89[1]) + fRec89[0]))) - (fConst144 * ((fConst98 * fRec88[1]) + (fConst152 * fRec88[2]))));
			float fTemp67 = (fRec88[2] + ((2.0f * fRec88[1]) + fRec88[0]));
			fVec27[0] = fTemp67;
			fRec87[0] = ((fConst158 * fRec87[1]) + (fConst159 * ((fConst88 * fTemp67) + (fConst160 * fVec27[1]))));
			fRec86[0] = (fRec87[0] - (fConst156 * ((fConst92 * fRec86[1]) + (fConst161 * fRec86[2]))));
			fRec85[0] = ((fConst156 * (((fConst91 * fRec86[0]) + (fConst155 * fRec86[1])) + (fConst91 * fRec86[2]))) - (fConst154 * ((fConst92 * fRec85[1]) + (fConst162 * fRec85[2]))));
			float fTemp68 = (fConst74 * fRec84[1]);
			fRec84[0] = ((fConst154 * (((fConst155 * fRec85[1]) + (fConst91 * fRec85[0])) + (fConst91 * fRec85[2]))) - (fConst71 * (fTemp68 + (fConst72 * fRec84[2]))));
			float fTemp69 = (fConst80 * fRec83[1]);
			fRec83[0] = ((fRec84[2] + (fConst71 * (fTemp68 + (fConst72 * fRec84[0])))) - (fConst77 * (fTemp69 + (fConst78 * fRec83[2]))));
			float fTemp70 = (fConst86 * fRec82[1]);
			fRec82[0] = ((fRec83[2] + (fConst77 * (fTemp69 + (fConst78 * fRec83[0])))) - (fConst83 * (fTemp70 + (fConst84 * fRec82[2]))));
			fRec91[0] = (fSlow21 + (0.999000013f * fRec91[1]));
			fRec99[0] = ((fConst158 * fRec99[1]) + (fConst159 * (fTemp67 + fVec27[1])));
			fRec98[0] = (fRec99[0] - (fConst156 * ((fConst92 * fRec98[1]) + (fConst161 * fRec98[2]))));
			fRec97[0] = ((fConst156 * (fRec98[2] + ((2.0f * fRec98[1]) + fRec98[0]))) - (fConst154 * ((fConst92 * fRec97[1]) + (fConst162 * fRec97[2]))));
			float fTemp71 = (fRec97[2] + ((2.0f * fRec97[1]) + fRec97[0]));
			fVec28[0] = fTemp71;
			fRec96[0] = ((fConst168 * fRec96[1]) + (fConst169 * ((fConst82 * fTemp71) + (fConst170 * fVec28[1]))));
			fRec95[0] = (fRec96[0] - (fConst166 * ((fConst86 * fRec95[1]) + (fConst171 * fRec95[2]))));
			fRec94[0] = ((fConst166 * (((fConst85 * fRec95[0]) + (fConst165 * fRec95[1])) + (fConst85 * fRec95[2]))) - (fConst164 * ((fConst86 * fRec94[1]) + (fConst172 * fRec94[2]))));
			float fTemp72 = (fConst74 * fRec93[1]);
			fRec93[0] = ((fConst164 * (((fConst165 * fRec94[1]) + (fConst85 * fRec94[0])) + (fConst85 * fRec94[2]))) - (fConst71 * (fTemp72 + (fConst72 * fRec93[2]))));
			float fTemp73 = (fConst80 * fRec92[1]);
			fRec92[0] = ((fRec93[2] + (fConst71 * (fTemp72 + (fConst72 * fRec93[0])))) - (fConst77 * (fTemp73 + (fConst78 * fRec92[2]))));
			fRec100[0] = (fSlow22 + (0.999000013f * fRec100[1]));
			fRec107[0] = ((fConst168 * fRec107[1]) + (fConst169 * (fTemp71 + fVec28[1])));
			fRec106[0] = (fRec107[0] - (fConst166 * ((fConst86 * fRec106[1]) + (fConst171 * fRec106[2]))));
			fRec105[0] = ((fConst166 * (fRec106[2] + ((2.0f * fRec106[1]) + fRec106[0]))) - (fConst164 * ((fConst86 * fRec105[1]) + (fConst172 * fRec105[2]))));
			float fTemp74 = (fRec105[2] + ((2.0f * fRec105[1]) + fRec105[0]));
			fVec29[0] = fTemp74;
			fRec104[0] = ((fConst178 * fRec104[1]) + (fConst179 * ((fConst76 * fTemp74) + (fConst180 * fVec29[1]))));
			fRec103[0] = (fRec104[0] - (fConst176 * ((fConst80 * fRec103[1]) + (fConst181 * fRec103[2]))));
			fRec102[0] = ((fConst176 * (((fConst79 * fRec103[0]) + (fConst175 * fRec103[1])) + (fConst79 * fRec103[2]))) - (fConst174 * ((fConst80 * fRec102[1]) + (fConst182 * fRec102[2]))));
			float fTemp75 = (fConst74 * fRec101[1]);
			fRec101[0] = ((fConst174 * (((fConst175 * fRec102[1]) + (fConst79 * fRec102[0])) + (fConst79 * fRec102[2]))) - (fConst71 * (fTemp75 + (fConst72 * fRec101[2]))));
			fRec108[0] = (fSlow23 + (0.999000013f * fRec108[1]));
			fRec114[0] = ((fConst178 * fRec114[1]) + (fConst179 * (fTemp74 + fVec29[1])));
			fRec113[0] = (fRec114[0] - (fConst176 * ((fConst80 * fRec113[1]) + (fConst181 * fRec113[2]))));
			fRec112[0] = ((fConst176 * (fRec113[2] + ((2.0f * fRec113[1]) + fRec113[0]))) - (fConst174 * ((fConst80 * fRec112[1]) + (fConst182 * fRec112[2]))));
			float fTemp76 = (fRec112[2] + ((2.0f * fRec112[1]) + fRec112[0]));
			fVec30[0] = fTemp76;
			fRec111[0] = ((fConst187 * fRec111[1]) + (fConst188 * ((fConst70 * fTemp76) + (fConst189 * fVec30[1]))));
			fRec110[0] = (fRec111[0] - (fConst185 * ((fConst74 * fRec110[1]) + (fConst190 * fRec110[2]))));
			fRec109[0] = ((fConst185 * (((fConst73 * fRec110[0]) + (fConst184 * fRec110[1])) + (fConst73 * fRec110[2]))) - (fConst183 * ((fConst74 * fRec109[1]) + (fConst191 * fRec109[2]))));
			fRec115[0] = (fSlow24 + (0.999000013f * fRec115[1]));
			fRec118[0] = ((fConst187 * fRec118[1]) + (fConst188 * (fTemp76 + fVec30[1])));
			fRec117[0] = (fRec118[0] - (fConst185 * ((fConst74 * fRec117[1]) + (fConst190 * fRec117[2]))));
			fRec116[0] = ((fConst185 * (fRec117[2] + ((2.0f * fRec117[1]) + fRec117[0]))) - (fConst183 * ((fConst74 * fRec116[1]) + (fConst191 * fRec116[2]))));
			fRec119[0] = (fSlow25 + (0.999000013f * fRec119[1]));
			float fTemp77 = (iSlow3?fTemp31:((((((((((fRec13[2] + (fConst109 * (fTemp40 + (fConst110 * fRec13[0])))) * powf(10.0f, (0.0500000007f * fRec31[0]))) + ((fRec32[2] + (fConst49 * (fTemp48 + (fConst50 * fRec32[0])))) * powf(10.0f, (0.0500000007f * fRec45[0])))) + ((fRec46[2] + (fConst101 * (fTemp55 + (fConst102 * fRec46[0])))) * powf(10.0f, (0.0500000007f * fRec58[0])))) + ((fRec59[2] + (fConst95 * (fTemp61 + (fConst96 * fRec59[0])))) * powf(10.0f, (0.0500000007f * fRec70[0])))) + ((fRec71[2] + (fConst89 * (fTemp66 + (fConst90 * fRec71[0])))) * powf(10.0f, (0.0500000007f * fRec81[0])))) + ((fRec82[2] + (fConst83 * (fTemp70 + (fConst84 * fRec82[0])))) * powf(10.0f, (0.0500000007f * fRec91[0])))) + ((fRec92[2] + (fConst77 * (fTemp73 + (fConst78 * fRec92[0])))) * powf(10.0f, (0.0500000007f * fRec100[0])))) + ((fRec101[2] + (fConst71 * (fTemp75 + (fConst72 * fRec101[0])))) * powf(10.0f, (0.0500000007f * fRec108[0])))) + (fConst183 * (((((fConst184 * fRec109[1]) + (fConst73 * fRec109[0])) + (fConst73 * fRec109[2])) * powf(10.0f, (0.0500000007f * fRec115[0]))) + ((fRec116[2] + ((2.0f * fRec116[1]) + fRec116[0])) * powf(10.0f, (0.0500000007f * fRec119[0])))))));
			fRec12[0] = (fTemp77 - (fConst44 * ((fConst192 * fRec12[2]) + (fConst193 * fRec12[1]))));
			fRec11[0] = ((fConst44 * (((fConst46 * fRec12[1]) + (fConst194 * fRec12[0])) + (fConst194 * fRec12[2]))) - (fConst42 * ((fConst195 * fRec11[2]) + (fConst196 * fRec11[1]))));
			fRec10[0] = ((fConst42 * (((fConst43 * fRec11[1]) + (fConst197 * fRec11[0])) + (fConst197 * fRec11[2]))) - (fConst38 * ((fConst198 * fRec10[2]) + (fConst199 * fRec10[1]))));
			float fTemp78 = (fConst38 * (((fConst41 * fRec10[1]) + (fConst200 * fRec10[0])) + (fConst200 * fRec10[2])));
			fRec9[0] = (fTemp78 - (fConst33 * ((fConst201 * fRec9[2]) + (fConst202 * fRec9[1]))));
			fRec8[0] = ((fConst33 * (((fConst35 * fRec9[1]) + (fConst203 * fRec9[0])) + (fConst203 * fRec9[2]))) - (fConst31 * ((fConst204 * fRec8[2]) + (fConst205 * fRec8[1]))));
			fRec7[0] = ((fConst31 * (((fConst32 * fRec8[1]) + (fConst206 * fRec8[0])) + (fConst206 * fRec8[2]))) - (fConst27 * ((fConst207 * fRec7[2]) + (fConst208 * fRec7[1]))));
			float fTemp79 = (fConst27 * (((fConst30 * fRec7[1]) + (fConst209 * fRec7[0])) + (fConst209 * fRec7[2])));
			fRec6[0] = (fTemp79 - (fConst22 * ((fConst210 * fRec6[2]) + (fConst211 * fRec6[1]))));
			fRec5[0] = ((fConst22 * (((fConst24 * fRec6[1]) + (fConst212 * fRec6[0])) + (fConst212 * fRec6[2]))) - (fConst20 * ((fConst213 * fRec5[2]) + (fConst214 * fRec5[1]))));
			fRec4[0] = ((fConst20 * (((fConst21 * fRec5[1]) + (fConst215 * fRec5[0])) + (fConst215 * fRec5[2]))) - (fConst16 * ((fConst216 * fRec4[2]) + (fConst217 * fRec4[1]))));
			float fTemp80 = (fConst16 * (((fConst19 * fRec4[1]) + (fConst218 * fRec4[0])) + (fConst218 * fRec4[2])));
			fRec3[0] = (fTemp80 - (fConst11 * ((fConst219 * fRec3[2]) + (fConst221 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst222 * fRec3[0])) + (fConst222 * fRec3[2]))) - (fConst8 * ((fConst223 * fRec2[2]) + (fConst224 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst225 * fRec2[0])) + (fConst225 * fRec2[2]))) - (fConst4 * ((fConst226 * fRec1[2]) + (fConst227 * fRec1[1]))));
			fRec0[0] = ((fSlow2 * fabsf((fConst4 * (((fConst7 * fRec1[1]) + (fConst228 * fRec1[0])) + (fConst228 * fRec1[2]))))) + (fSlow1 * fRec0[1]));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec0[0])))));
			fRec126[0] = (fTemp80 - (fConst245 * ((fConst248 * fRec126[2]) + (fConst249 * fRec126[1]))));
			fRec125[0] = ((fConst245 * (((fConst247 * fRec126[1]) + (fConst250 * fRec126[0])) + (fConst250 * fRec126[2]))) - (fConst243 * ((fConst251 * fRec125[2]) + (fConst252 * fRec125[1]))));
			fRec124[0] = ((fConst243 * (((fConst244 * fRec125[1]) + (fConst253 * fRec125[0])) + (fConst253 * fRec125[2]))) - (fConst241 * ((fConst254 * fRec124[2]) + (fConst255 * fRec124[1]))));
			float fTemp81 = (fConst241 * (((fConst242 * fRec124[1]) + (fConst256 * fRec124[0])) + (fConst256 * fRec124[2])));
			fRec123[0] = (fTemp81 - (fConst238 * ((fConst257 * fRec123[2]) + (fConst259 * fRec123[1]))));
			fRec122[0] = ((fConst238 * (((fConst240 * fRec123[1]) + (fConst260 * fRec123[0])) + (fConst260 * fRec123[2]))) - (fConst235 * ((fConst261 * fRec122[2]) + (fConst262 * fRec122[1]))));
			fRec121[0] = ((fConst235 * (((fConst237 * fRec122[1]) + (fConst263 * fRec122[0])) + (fConst263 * fRec122[2]))) - (fConst231 * ((fConst264 * fRec121[2]) + (fConst265 * fRec121[1]))));
			fRec120[0] = ((fSlow1 * fRec120[1]) + (fSlow2 * fabsf((fConst231 * (((fConst234 * fRec121[1]) + (fConst266 * fRec121[0])) + (fConst266 * fRec121[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec120[0])))));
			fRec133[0] = (fTemp81 - (fConst283 * ((fConst286 * fRec133[2]) + (fConst287 * fRec133[1]))));
			fRec132[0] = ((fConst283 * (((fConst285 * fRec133[1]) + (fConst288 * fRec133[0])) + (fConst288 * fRec133[2]))) - (fConst281 * ((fConst289 * fRec132[2]) + (fConst290 * fRec132[1]))));
			fRec131[0] = ((fConst281 * (((fConst282 * fRec132[1]) + (fConst291 * fRec132[0])) + (fConst291 * fRec132[2]))) - (fConst279 * ((fConst292 * fRec131[2]) + (fConst293 * fRec131[1]))));
			float fTemp82 = (fConst279 * (((fConst280 * fRec131[1]) + (fConst294 * fRec131[0])) + (fConst294 * fRec131[2])));
			fRec130[0] = (fTemp82 - (fConst276 * ((fConst295 * fRec130[2]) + (fConst297 * fRec130[1]))));
			fRec129[0] = ((fConst276 * (((fConst278 * fRec130[1]) + (fConst298 * fRec130[0])) + (fConst298 * fRec130[2]))) - (fConst273 * ((fConst299 * fRec129[2]) + (fConst300 * fRec129[1]))));
			fRec128[0] = ((fConst273 * (((fConst275 * fRec129[1]) + (fConst301 * fRec129[0])) + (fConst301 * fRec129[2]))) - (fConst269 * ((fConst302 * fRec128[2]) + (fConst303 * fRec128[1]))));
			fRec127[0] = ((fSlow1 * fRec127[1]) + (fSlow2 * fabsf((fConst269 * (((fConst272 * fRec128[1]) + (fConst304 * fRec128[0])) + (fConst304 * fRec128[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec127[0])))));
			fRec140[0] = (fTemp82 - (fConst321 * ((fConst324 * fRec140[2]) + (fConst325 * fRec140[1]))));
			fRec139[0] = ((fConst321 * (((fConst323 * fRec140[1]) + (fConst326 * fRec140[0])) + (fConst326 * fRec140[2]))) - (fConst319 * ((fConst327 * fRec139[2]) + (fConst328 * fRec139[1]))));
			fRec138[0] = ((fConst319 * (((fConst320 * fRec139[1]) + (fConst329 * fRec139[0])) + (fConst329 * fRec139[2]))) - (fConst317 * ((fConst330 * fRec138[2]) + (fConst331 * fRec138[1]))));
			float fTemp83 = (fConst317 * (((fConst318 * fRec138[1]) + (fConst332 * fRec138[0])) + (fConst332 * fRec138[2])));
			fRec137[0] = (fTemp83 - (fConst314 * ((fConst333 * fRec137[2]) + (fConst335 * fRec137[1]))));
			fRec136[0] = ((fConst314 * (((fConst316 * fRec137[1]) + (fConst336 * fRec137[0])) + (fConst336 * fRec137[2]))) - (fConst311 * ((fConst337 * fRec136[2]) + (fConst338 * fRec136[1]))));
			fRec135[0] = ((fConst311 * (((fConst313 * fRec136[1]) + (fConst339 * fRec136[0])) + (fConst339 * fRec136[2]))) - (fConst307 * ((fConst340 * fRec135[2]) + (fConst341 * fRec135[1]))));
			fRec134[0] = ((fSlow1 * fRec134[1]) + (fSlow2 * fabsf((fConst307 * (((fConst310 * fRec135[1]) + (fConst342 * fRec135[0])) + (fConst342 * fRec135[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec134[0])))));
			fRec147[0] = (fTemp83 - (fConst359 * ((fConst362 * fRec147[2]) + (fConst363 * fRec147[1]))));
			fRec146[0] = ((fConst359 * (((fConst361 * fRec147[1]) + (fConst364 * fRec147[0])) + (fConst364 * fRec147[2]))) - (fConst357 * ((fConst365 * fRec146[2]) + (fConst366 * fRec146[1]))));
			fRec145[0] = ((fConst357 * (((fConst358 * fRec146[1]) + (fConst367 * fRec146[0])) + (fConst367 * fRec146[2]))) - (fConst355 * ((fConst368 * fRec145[2]) + (fConst369 * fRec145[1]))));
			float fTemp84 = (fConst355 * (((fConst356 * fRec145[1]) + (fConst370 * fRec145[0])) + (fConst370 * fRec145[2])));
			fRec144[0] = (fTemp84 - (fConst352 * ((fConst371 * fRec144[2]) + (fConst373 * fRec144[1]))));
			fRec143[0] = ((fConst352 * (((fConst354 * fRec144[1]) + (fConst374 * fRec144[0])) + (fConst374 * fRec144[2]))) - (fConst349 * ((fConst375 * fRec143[2]) + (fConst376 * fRec143[1]))));
			fRec142[0] = ((fConst349 * (((fConst351 * fRec143[1]) + (fConst377 * fRec143[0])) + (fConst377 * fRec143[2]))) - (fConst345 * ((fConst378 * fRec142[2]) + (fConst379 * fRec142[1]))));
			fRec141[0] = ((fSlow1 * fRec141[1]) + (fSlow2 * fabsf((fConst345 * (((fConst348 * fRec142[1]) + (fConst380 * fRec142[0])) + (fConst380 * fRec142[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec141[0])))));
			fRec154[0] = (fTemp84 - (fConst397 * ((fConst400 * fRec154[2]) + (fConst401 * fRec154[1]))));
			fRec153[0] = ((fConst397 * (((fConst399 * fRec154[1]) + (fConst402 * fRec154[0])) + (fConst402 * fRec154[2]))) - (fConst395 * ((fConst403 * fRec153[2]) + (fConst404 * fRec153[1]))));
			fRec152[0] = ((fConst395 * (((fConst396 * fRec153[1]) + (fConst405 * fRec153[0])) + (fConst405 * fRec153[2]))) - (fConst393 * ((fConst406 * fRec152[2]) + (fConst407 * fRec152[1]))));
			float fTemp85 = (fConst393 * (((fConst394 * fRec152[1]) + (fConst408 * fRec152[0])) + (fConst408 * fRec152[2])));
			fRec151[0] = (fTemp85 - (fConst390 * ((fConst409 * fRec151[2]) + (fConst411 * fRec151[1]))));
			fRec150[0] = ((fConst390 * (((fConst392 * fRec151[1]) + (fConst412 * fRec151[0])) + (fConst412 * fRec151[2]))) - (fConst387 * ((fConst413 * fRec150[2]) + (fConst414 * fRec150[1]))));
			fRec149[0] = ((fConst387 * (((fConst389 * fRec150[1]) + (fConst415 * fRec150[0])) + (fConst415 * fRec150[2]))) - (fConst383 * ((fConst416 * fRec149[2]) + (fConst417 * fRec149[1]))));
			fRec148[0] = ((fSlow1 * fRec148[1]) + (fSlow2 * fabsf((fConst383 * (((fConst386 * fRec149[1]) + (fConst418 * fRec149[0])) + (fConst418 * fRec149[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec148[0])))));
			fRec161[0] = (fTemp85 - (fConst435 * ((fConst438 * fRec161[2]) + (fConst439 * fRec161[1]))));
			fRec160[0] = ((fConst435 * (((fConst437 * fRec161[1]) + (fConst440 * fRec161[0])) + (fConst440 * fRec161[2]))) - (fConst433 * ((fConst441 * fRec160[2]) + (fConst442 * fRec160[1]))));
			fRec159[0] = ((fConst433 * (((fConst434 * fRec160[1]) + (fConst443 * fRec160[0])) + (fConst443 * fRec160[2]))) - (fConst431 * ((fConst444 * fRec159[2]) + (fConst445 * fRec159[1]))));
			float fTemp86 = (fConst431 * (((fConst432 * fRec159[1]) + (fConst446 * fRec159[0])) + (fConst446 * fRec159[2])));
			fRec158[0] = (fTemp86 - (fConst428 * ((fConst447 * fRec158[2]) + (fConst449 * fRec158[1]))));
			fRec157[0] = ((fConst428 * (((fConst430 * fRec158[1]) + (fConst450 * fRec158[0])) + (fConst450 * fRec158[2]))) - (fConst425 * ((fConst451 * fRec157[2]) + (fConst452 * fRec157[1]))));
			fRec156[0] = ((fConst425 * (((fConst427 * fRec157[1]) + (fConst453 * fRec157[0])) + (fConst453 * fRec157[2]))) - (fConst421 * ((fConst454 * fRec156[2]) + (fConst455 * fRec156[1]))));
			fRec155[0] = ((fSlow1 * fRec155[1]) + (fSlow2 * fabsf((fConst421 * (((fConst424 * fRec156[1]) + (fConst456 * fRec156[0])) + (fConst456 * fRec156[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec155[0])))));
			fRec168[0] = (fTemp86 - (fConst473 * ((fConst476 * fRec168[2]) + (fConst477 * fRec168[1]))));
			fRec167[0] = ((fConst473 * (((fConst475 * fRec168[1]) + (fConst478 * fRec168[0])) + (fConst478 * fRec168[2]))) - (fConst471 * ((fConst479 * fRec167[2]) + (fConst480 * fRec167[1]))));
			fRec166[0] = ((fConst471 * (((fConst472 * fRec167[1]) + (fConst481 * fRec167[0])) + (fConst481 * fRec167[2]))) - (fConst469 * ((fConst482 * fRec166[2]) + (fConst483 * fRec166[1]))));
			float fTemp87 = (fConst469 * (((fConst470 * fRec166[1]) + (fConst484 * fRec166[0])) + (fConst484 * fRec166[2])));
			fRec165[0] = (fTemp87 - (fConst466 * ((fConst485 * fRec165[2]) + (fConst487 * fRec165[1]))));
			fRec164[0] = ((fConst466 * (((fConst468 * fRec165[1]) + (fConst488 * fRec165[0])) + (fConst488 * fRec165[2]))) - (fConst463 * ((fConst489 * fRec164[2]) + (fConst490 * fRec164[1]))));
			fRec163[0] = ((fConst463 * (((fConst465 * fRec164[1]) + (fConst491 * fRec164[0])) + (fConst491 * fRec164[2]))) - (fConst459 * ((fConst492 * fRec163[2]) + (fConst493 * fRec163[1]))));
			fRec162[0] = ((fSlow1 * fRec162[1]) + (fSlow2 * fabsf((fConst459 * (((fConst462 * fRec163[1]) + (fConst494 * fRec163[0])) + (fConst494 * fRec163[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec162[0])))));
			fRec175[0] = (fTemp87 - (fConst511 * ((fConst514 * fRec175[2]) + (fConst515 * fRec175[1]))));
			fRec174[0] = ((fConst511 * (((fConst513 * fRec175[1]) + (fConst516 * fRec175[0])) + (fConst516 * fRec175[2]))) - (fConst509 * ((fConst517 * fRec174[2]) + (fConst518 * fRec174[1]))));
			fRec173[0] = ((fConst509 * (((fConst510 * fRec174[1]) + (fConst519 * fRec174[0])) + (fConst519 * fRec174[2]))) - (fConst507 * ((fConst520 * fRec173[2]) + (fConst521 * fRec173[1]))));
			float fTemp88 = (fConst507 * (((fConst508 * fRec173[1]) + (fConst522 * fRec173[0])) + (fConst522 * fRec173[2])));
			fRec172[0] = (fTemp88 - (fConst504 * ((fConst523 * fRec172[2]) + (fConst525 * fRec172[1]))));
			fRec171[0] = ((fConst504 * (((fConst506 * fRec172[1]) + (fConst526 * fRec172[0])) + (fConst526 * fRec172[2]))) - (fConst501 * ((fConst527 * fRec171[2]) + (fConst528 * fRec171[1]))));
			fRec170[0] = ((fConst501 * (((fConst503 * fRec171[1]) + (fConst529 * fRec171[0])) + (fConst529 * fRec171[2]))) - (fConst497 * ((fConst530 * fRec170[2]) + (fConst531 * fRec170[1]))));
			fRec169[0] = ((fSlow1 * fRec169[1]) + (fSlow2 * fabsf((fConst497 * (((fConst500 * fRec170[1]) + (fConst532 * fRec170[0])) + (fConst532 * fRec170[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec169[0])))));
			fRec182[0] = (fTemp88 - (fConst549 * ((fConst552 * fRec182[2]) + (fConst553 * fRec182[1]))));
			fRec181[0] = ((fConst549 * (((fConst551 * fRec182[1]) + (fConst554 * fRec182[0])) + (fConst554 * fRec182[2]))) - (fConst547 * ((fConst555 * fRec181[2]) + (fConst556 * fRec181[1]))));
			fRec180[0] = ((fConst547 * (((fConst548 * fRec181[1]) + (fConst557 * fRec181[0])) + (fConst557 * fRec181[2]))) - (fConst545 * ((fConst558 * fRec180[2]) + (fConst559 * fRec180[1]))));
			float fTemp89 = (fConst545 * (((fConst546 * fRec180[1]) + (fConst560 * fRec180[0])) + (fConst560 * fRec180[2])));
			fRec179[0] = (fTemp89 - (fConst542 * ((fConst561 * fRec179[2]) + (fConst563 * fRec179[1]))));
			fRec178[0] = ((fConst542 * (((fConst544 * fRec179[1]) + (fConst564 * fRec179[0])) + (fConst564 * fRec179[2]))) - (fConst539 * ((fConst565 * fRec178[2]) + (fConst566 * fRec178[1]))));
			fRec177[0] = ((fConst539 * (((fConst541 * fRec178[1]) + (fConst567 * fRec178[0])) + (fConst567 * fRec178[2]))) - (fConst535 * ((fConst568 * fRec177[2]) + (fConst569 * fRec177[1]))));
			fRec176[0] = ((fSlow1 * fRec176[1]) + (fSlow2 * fabsf((fConst535 * (((fConst538 * fRec177[1]) + (fConst570 * fRec177[0])) + (fConst570 * fRec177[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec176[0])))));
			fRec189[0] = (fTemp89 - (fConst587 * ((fConst590 * fRec189[2]) + (fConst591 * fRec189[1]))));
			fRec188[0] = ((fConst587 * (((fConst589 * fRec189[1]) + (fConst592 * fRec189[0])) + (fConst592 * fRec189[2]))) - (fConst585 * ((fConst593 * fRec188[2]) + (fConst594 * fRec188[1]))));
			fRec187[0] = ((fConst585 * (((fConst586 * fRec188[1]) + (fConst595 * fRec188[0])) + (fConst595 * fRec188[2]))) - (fConst583 * ((fConst596 * fRec187[2]) + (fConst597 * fRec187[1]))));
			float fTemp90 = (fConst583 * (((fConst584 * fRec187[1]) + (fConst598 * fRec187[0])) + (fConst598 * fRec187[2])));
			fRec186[0] = (fTemp90 - (fConst580 * ((fConst599 * fRec186[2]) + (fConst601 * fRec186[1]))));
			fRec185[0] = ((fConst580 * (((fConst582 * fRec186[1]) + (fConst602 * fRec186[0])) + (fConst602 * fRec186[2]))) - (fConst577 * ((fConst603 * fRec185[2]) + (fConst604 * fRec185[1]))));
			fRec184[0] = ((fConst577 * (((fConst579 * fRec185[1]) + (fConst605 * fRec185[0])) + (fConst605 * fRec185[2]))) - (fConst573 * ((fConst606 * fRec184[2]) + (fConst607 * fRec184[1]))));
			fRec183[0] = ((fSlow1 * fRec183[1]) + (fSlow2 * fabsf((fConst573 * (((fConst576 * fRec184[1]) + (fConst608 * fRec184[0])) + (fConst608 * fRec184[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec183[0])))));
			fRec193[0] = (fTemp90 - (fConst613 * ((fConst616 * fRec193[2]) + (fConst617 * fRec193[1]))));
			fRec192[0] = ((fConst613 * (((fConst615 * fRec193[1]) + (fConst618 * fRec193[0])) + (fConst618 * fRec193[2]))) - (fConst611 * ((fConst619 * fRec192[2]) + (fConst620 * fRec192[1]))));
			fRec191[0] = ((fConst611 * (((fConst612 * fRec192[1]) + (fConst621 * fRec192[0])) + (fConst621 * fRec192[2]))) - (fConst609 * ((fConst622 * fRec191[2]) + (fConst623 * fRec191[1]))));
			fRec190[0] = ((fSlow1 * fRec190[1]) + (fSlow2 * fabsf((fConst609 * (((fConst610 * fRec191[1]) + (fConst624 * fRec191[0])) + (fConst624 * fRec191[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec190[0])))));
			fRec197[0] = (fTemp77 - (fConst631 * ((fConst634 * fRec197[2]) + (fConst635 * fRec197[1]))));
			fRec196[0] = ((fConst631 * (((fConst633 * fRec197[1]) + (fConst636 * fRec197[0])) + (fConst636 * fRec197[2]))) - (fConst628 * ((fConst637 * fRec196[2]) + (fConst638 * fRec196[1]))));
			fRec195[0] = ((fConst628 * (((fConst630 * fRec196[1]) + (fConst639 * fRec196[0])) + (fConst639 * fRec196[2]))) - (fConst625 * ((fConst640 * fRec195[2]) + (fConst641 * fRec195[1]))));
			fRec194[0] = ((fSlow1 * fRec194[1]) + (fSlow2 * fabsf((fConst625 * (((fConst627 * fRec195[1]) + (fConst642 * fRec195[0])) + (fConst642 * fRec195[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec194[0])))));
			fRec201[0] = (fTemp78 - (fConst649 * ((fConst652 * fRec201[2]) + (fConst653 * fRec201[1]))));
			fRec200[0] = ((fConst649 * (((fConst651 * fRec201[1]) + (fConst654 * fRec201[0])) + (fConst654 * fRec201[2]))) - (fConst646 * ((fConst655 * fRec200[2]) + (fConst656 * fRec200[1]))));
			fRec199[0] = ((fConst646 * (((fConst648 * fRec200[1]) + (fConst657 * fRec200[0])) + (fConst657 * fRec200[2]))) - (fConst643 * ((fConst658 * fRec199[2]) + (fConst659 * fRec199[1]))));
			fRec198[0] = ((fSlow1 * fRec198[1]) + (fSlow2 * fabsf((fConst643 * (((fConst645 * fRec199[1]) + (fConst660 * fRec199[0])) + (fConst660 * fRec199[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec198[0])))));
			fRec205[0] = (fTemp79 - (fConst667 * ((fConst670 * fRec205[2]) + (fConst671 * fRec205[1]))));
			fRec204[0] = ((fConst667 * (((fConst669 * fRec205[1]) + (fConst672 * fRec205[0])) + (fConst672 * fRec205[2]))) - (fConst664 * ((fConst673 * fRec204[2]) + (fConst674 * fRec204[1]))));
			fRec203[0] = ((fConst664 * (((fConst666 * fRec204[1]) + (fConst675 * fRec204[0])) + (fConst675 * fRec204[2]))) - (fConst661 * ((fConst676 * fRec203[2]) + (fConst677 * fRec203[1]))));
			fRec202[0] = ((fSlow1 * fRec202[1]) + (fSlow2 * fabsf((fConst661 * (((fConst663 * fRec203[1]) + (fConst678 * fRec203[0])) + (fConst678 * fRec203[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec202[0])))));
			output0[i] = FAUSTFLOAT(fTemp77);
			output1[i] = FAUSTFLOAT(fTemp77);
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fVec1[1] = fVec1[0];
			fRec25[1] = fRec25[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec27[1] = fRec27[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec28[1] = fRec28[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			iRec29[1] = iRec29[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec30[j1] = fRec30[(j1 - 1)];
				
			}
			fVec22[1] = fVec22[0];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
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
			fRec31[1] = fRec31[0];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fVec23[1] = fVec23[0];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
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
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec45[1] = fRec45[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fVec24[1] = fVec24[0];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
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
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec58[1] = fRec58[0];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fVec25[1] = fVec25[0];
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
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec70[1] = fRec70[0];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fVec26[1] = fVec26[0];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec81[1] = fRec81[0];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fVec27[1] = fVec27[0];
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
			fRec91[1] = fRec91[0];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fVec28[1] = fVec28[0];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec100[1] = fRec100[0];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fVec29[1] = fVec29[0];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec108[1] = fRec108[0];
			fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fVec30[1] = fVec30[0];
			fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec115[1] = fRec115[0];
			fRec118[1] = fRec118[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[2] = fRec116[1];
			fRec116[1] = fRec116[0];
			fRec119[1] = fRec119[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[1] = fRec120[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec132[2] = fRec132[1];
			fRec132[1] = fRec132[0];
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1];
			fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			fRec127[1] = fRec127[0];
			fRec140[2] = fRec140[1];
			fRec140[1] = fRec140[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
			fRec138[2] = fRec138[1];
			fRec138[1] = fRec138[0];
			fRec137[2] = fRec137[1];
			fRec137[1] = fRec137[0];
			fRec136[2] = fRec136[1];
			fRec136[1] = fRec136[0];
			fRec135[2] = fRec135[1];
			fRec135[1] = fRec135[0];
			fRec134[1] = fRec134[0];
			fRec147[2] = fRec147[1];
			fRec147[1] = fRec147[0];
			fRec146[2] = fRec146[1];
			fRec146[1] = fRec146[0];
			fRec145[2] = fRec145[1];
			fRec145[1] = fRec145[0];
			fRec144[2] = fRec144[1];
			fRec144[1] = fRec144[0];
			fRec143[2] = fRec143[1];
			fRec143[1] = fRec143[0];
			fRec142[2] = fRec142[1];
			fRec142[1] = fRec142[0];
			fRec141[1] = fRec141[0];
			fRec154[2] = fRec154[1];
			fRec154[1] = fRec154[0];
			fRec153[2] = fRec153[1];
			fRec153[1] = fRec153[0];
			fRec152[2] = fRec152[1];
			fRec152[1] = fRec152[0];
			fRec151[2] = fRec151[1];
			fRec151[1] = fRec151[0];
			fRec150[2] = fRec150[1];
			fRec150[1] = fRec150[0];
			fRec149[2] = fRec149[1];
			fRec149[1] = fRec149[0];
			fRec148[1] = fRec148[0];
			fRec161[2] = fRec161[1];
			fRec161[1] = fRec161[0];
			fRec160[2] = fRec160[1];
			fRec160[1] = fRec160[0];
			fRec159[2] = fRec159[1];
			fRec159[1] = fRec159[0];
			fRec158[2] = fRec158[1];
			fRec158[1] = fRec158[0];
			fRec157[2] = fRec157[1];
			fRec157[1] = fRec157[0];
			fRec156[2] = fRec156[1];
			fRec156[1] = fRec156[0];
			fRec155[1] = fRec155[0];
			fRec168[2] = fRec168[1];
			fRec168[1] = fRec168[0];
			fRec167[2] = fRec167[1];
			fRec167[1] = fRec167[0];
			fRec166[2] = fRec166[1];
			fRec166[1] = fRec166[0];
			fRec165[2] = fRec165[1];
			fRec165[1] = fRec165[0];
			fRec164[2] = fRec164[1];
			fRec164[1] = fRec164[0];
			fRec163[2] = fRec163[1];
			fRec163[1] = fRec163[0];
			fRec162[1] = fRec162[0];
			fRec175[2] = fRec175[1];
			fRec175[1] = fRec175[0];
			fRec174[2] = fRec174[1];
			fRec174[1] = fRec174[0];
			fRec173[2] = fRec173[1];
			fRec173[1] = fRec173[0];
			fRec172[2] = fRec172[1];
			fRec172[1] = fRec172[0];
			fRec171[2] = fRec171[1];
			fRec171[1] = fRec171[0];
			fRec170[2] = fRec170[1];
			fRec170[1] = fRec170[0];
			fRec169[1] = fRec169[0];
			fRec182[2] = fRec182[1];
			fRec182[1] = fRec182[0];
			fRec181[2] = fRec181[1];
			fRec181[1] = fRec181[0];
			fRec180[2] = fRec180[1];
			fRec180[1] = fRec180[0];
			fRec179[2] = fRec179[1];
			fRec179[1] = fRec179[0];
			fRec178[2] = fRec178[1];
			fRec178[1] = fRec178[0];
			fRec177[2] = fRec177[1];
			fRec177[1] = fRec177[0];
			fRec176[1] = fRec176[0];
			fRec189[2] = fRec189[1];
			fRec189[1] = fRec189[0];
			fRec188[2] = fRec188[1];
			fRec188[1] = fRec188[0];
			fRec187[2] = fRec187[1];
			fRec187[1] = fRec187[0];
			fRec186[2] = fRec186[1];
			fRec186[1] = fRec186[0];
			fRec185[2] = fRec185[1];
			fRec185[1] = fRec185[0];
			fRec184[2] = fRec184[1];
			fRec184[1] = fRec184[0];
			fRec183[1] = fRec183[0];
			fRec193[2] = fRec193[1];
			fRec193[1] = fRec193[0];
			fRec192[2] = fRec192[1];
			fRec192[1] = fRec192[0];
			fRec191[2] = fRec191[1];
			fRec191[1] = fRec191[0];
			fRec190[1] = fRec190[0];
			fRec197[2] = fRec197[1];
			fRec197[1] = fRec197[0];
			fRec196[2] = fRec196[1];
			fRec196[1] = fRec196[0];
			fRec195[2] = fRec195[1];
			fRec195[1] = fRec195[0];
			fRec194[1] = fRec194[0];
			fRec201[2] = fRec201[1];
			fRec201[1] = fRec201[0];
			fRec200[2] = fRec200[1];
			fRec200[1] = fRec200[0];
			fRec199[2] = fRec199[1];
			fRec199[1] = fRec199[0];
			fRec198[1] = fRec198[0];
			fRec205[2] = fRec205[1];
			fRec205[1] = fRec205[0];
			fRec204[2] = fRec204[1];
			fRec204[1] = fRec204[0];
			fRec203[2] = fRec203[1];
			fRec203[1] = fRec203[0];
			fRec202[1] = fRec202[0];
			
		}
		
	}

	
};

#endif
