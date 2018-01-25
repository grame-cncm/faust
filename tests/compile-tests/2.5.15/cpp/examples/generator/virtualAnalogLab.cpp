/* ------------------------------------------------------------
name: "virtualAnalogLab"
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
float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
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
	float fConst47;
	float fConst48;
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
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider2;
	int iVec0[4];
	float fRec34[2];
	FAUSTFLOAT fCheckbox1;
	float fConst124;
	FAUSTFLOAT fHslider3;
	float fRec36[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider4;
	float fRec41[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry0;
	float fConst125;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fVslider2;
	float fRec43[2];
	float fVec1[2];
	float fRec42[2];
	float fConst126;
	float fVec2[2];
	float fConst127;
	float fVec3[2];
	float fVec4[2];
	float fConst128;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec44[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec45[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	float fConst129;
	FAUSTFLOAT fVslider5;
	float fVec22[2];
	float fRec46[2];
	float fVec23[2];
	int IOTA;
	float fVec24[4096];
	float fConst130;
	float fVec25[2];
	float fRec47[2];
	float fVec26[2];
	float fVec27[4096];
	float fVec28[2];
	float fRec48[2];
	float fVec29[2];
	float fVec30[4096];
	float fConst131;
	FAUSTFLOAT fVslider6;
	float fRec49[2];
	float fRec50[2];
	float fRec51[2];
	FAUSTFLOAT fVslider7;
	float fConst132;
	FAUSTFLOAT fCheckbox2;
	float fVec31[2];
	float fVec32[2];
	float fVec33[4096];
	FAUSTFLOAT fVslider8;
	float fRec52[2];
	float fVec34[2];
	float fVec35[2];
	float fVec36[4096];
	float fVec37[2];
	float fVec38[2];
	float fVec39[4096];
	FAUSTFLOAT fVslider9;
	int iRec54[2];
	float fRec53[4];
	FAUSTFLOAT fHslider6;
	float fRec40[2];
	float fRec39[2];
	float fRec38[2];
	float fRec37[2];
	float fRec35[2];
	FAUSTFLOAT fCheckbox3;
	float fConst133;
	float fRec57[2];
	float fRec56[3];
	float fRec55[3];
	float fRec60[2];
	float fRec58[2];
	float fRec63[2];
	float fRec61[2];
	float fConst134;
	float fConst135;
	float fRec33[3];
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec32[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec31[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fRec30[3];
	float fConst145;
	float fConst146;
	float fConst147;
	float fRec29[3];
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec28[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fRec27[3];
	float fConst154;
	float fConst155;
	float fConst156;
	float fRec26[3];
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec25[3];
	float fConst160;
	float fConst161;
	float fConst162;
	float fRec24[3];
	float fConst163;
	float fConst164;
	float fConst165;
	float fRec23[3];
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec22[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec21[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec20[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec19[3];
	float fConst178;
	float fConst179;
	float fConst180;
	float fRec18[3];
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec17[3];
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec16[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fRec15[3];
	float fConst190;
	float fConst191;
	float fConst192;
	float fRec14[3];
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec13[3];
	float fConst196;
	float fConst197;
	float fConst198;
	float fRec12[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fRec11[3];
	float fConst202;
	float fConst203;
	float fConst204;
	float fRec10[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec9[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec8[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fRec7[3];
	float fConst214;
	float fConst215;
	float fConst216;
	float fRec6[3];
	float fConst217;
	float fConst218;
	float fConst219;
	float fRec5[3];
	float fConst220;
	float fConst221;
	float fConst222;
	float fRec4[3];
	float fConst223;
	float fConst224;
	float fConst225;
	float fConst226;
	float fRec3[3];
	float fConst227;
	float fConst228;
	float fConst229;
	float fRec2[3];
	float fConst230;
	float fConst231;
	float fConst232;
	float fRec1[3];
	float fConst233;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fConst250;
	float fConst251;
	float fConst252;
	float fConst253;
	float fConst254;
	float fRec70[3];
	float fConst255;
	float fConst256;
	float fConst257;
	float fRec69[3];
	float fConst258;
	float fConst259;
	float fConst260;
	float fRec68[3];
	float fConst261;
	float fConst262;
	float fConst263;
	float fConst264;
	float fRec67[3];
	float fConst265;
	float fConst266;
	float fConst267;
	float fRec66[3];
	float fConst268;
	float fConst269;
	float fConst270;
	float fRec65[3];
	float fConst271;
	float fRec64[2];
	FAUSTFLOAT fVbargraph1;
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
	float fConst288;
	float fConst289;
	float fConst290;
	float fConst291;
	float fConst292;
	float fRec77[3];
	float fConst293;
	float fConst294;
	float fConst295;
	float fRec76[3];
	float fConst296;
	float fConst297;
	float fConst298;
	float fRec75[3];
	float fConst299;
	float fConst300;
	float fConst301;
	float fConst302;
	float fRec74[3];
	float fConst303;
	float fConst304;
	float fConst305;
	float fRec73[3];
	float fConst306;
	float fConst307;
	float fConst308;
	float fRec72[3];
	float fConst309;
	float fRec71[2];
	FAUSTFLOAT fVbargraph2;
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
	float fConst326;
	float fConst327;
	float fConst328;
	float fConst329;
	float fConst330;
	float fRec84[3];
	float fConst331;
	float fConst332;
	float fConst333;
	float fRec83[3];
	float fConst334;
	float fConst335;
	float fConst336;
	float fRec82[3];
	float fConst337;
	float fConst338;
	float fConst339;
	float fConst340;
	float fRec81[3];
	float fConst341;
	float fConst342;
	float fConst343;
	float fRec80[3];
	float fConst344;
	float fConst345;
	float fConst346;
	float fRec79[3];
	float fConst347;
	float fRec78[2];
	FAUSTFLOAT fVbargraph3;
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fConst352;
	float fConst353;
	float fConst354;
	float fConst355;
	float fConst356;
	float fRec88[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec87[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fRec86[3];
	float fConst363;
	float fRec85[2];
	FAUSTFLOAT fVbargraph4;
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
	float fRec92[3];
	float fConst375;
	float fConst376;
	float fConst377;
	float fRec91[3];
	float fConst378;
	float fConst379;
	float fConst380;
	float fRec90[3];
	float fConst381;
	float fRec89[2];
	FAUSTFLOAT fVbargraph5;
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
	float fRec96[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fRec95[3];
	float fConst396;
	float fConst397;
	float fConst398;
	float fRec94[3];
	float fConst399;
	float fRec93[2];
	FAUSTFLOAT fVbargraph6;
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
	float fRec100[3];
	float fConst411;
	float fConst412;
	float fConst413;
	float fRec99[3];
	float fConst414;
	float fConst415;
	float fConst416;
	float fRec98[3];
	float fConst417;
	float fRec97[2];
	FAUSTFLOAT fVbargraph7;
	float fConst418;
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
	float fRec104[3];
	float fConst429;
	float fConst430;
	float fConst431;
	float fRec103[3];
	float fConst432;
	float fConst433;
	float fConst434;
	float fRec102[3];
	float fConst435;
	float fRec101[2];
	FAUSTFLOAT fVbargraph8;
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
	float fRec108[3];
	float fConst447;
	float fConst448;
	float fConst449;
	float fRec107[3];
	float fConst450;
	float fConst451;
	float fConst452;
	float fRec106[3];
	float fConst453;
	float fRec105[2];
	FAUSTFLOAT fVbargraph9;
	float fConst454;
	float fConst455;
	float fConst456;
	float fConst457;
	float fConst458;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fConst463;
	float fConst464;
	float fRec112[3];
	float fConst465;
	float fConst466;
	float fConst467;
	float fRec111[3];
	float fConst468;
	float fConst469;
	float fConst470;
	float fRec110[3];
	float fConst471;
	float fRec109[2];
	FAUSTFLOAT fVbargraph10;
	float fConst472;
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
	float fRec116[3];
	float fConst483;
	float fConst484;
	float fConst485;
	float fRec115[3];
	float fConst486;
	float fConst487;
	float fConst488;
	float fRec114[3];
	float fConst489;
	float fRec113[2];
	FAUSTFLOAT fVbargraph11;
	float fConst490;
	float fConst491;
	float fConst492;
	float fConst493;
	float fConst494;
	float fConst495;
	float fConst496;
	float fConst497;
	float fConst498;
	float fConst499;
	float fConst500;
	float fRec120[3];
	float fConst501;
	float fConst502;
	float fConst503;
	float fRec119[3];
	float fConst504;
	float fConst505;
	float fConst506;
	float fRec118[3];
	float fConst507;
	float fRec117[2];
	FAUSTFLOAT fVbargraph12;
	float fConst508;
	float fConst509;
	float fConst510;
	float fConst511;
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec124[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec123[3];
	float fConst522;
	float fConst523;
	float fConst524;
	float fRec122[3];
	float fConst525;
	float fRec121[2];
	FAUSTFLOAT fVbargraph13;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fConst535;
	float fConst536;
	float fRec128[3];
	float fConst537;
	float fConst538;
	float fConst539;
	float fRec127[3];
	float fConst540;
	float fConst541;
	float fConst542;
	float fRec126[3];
	float fConst543;
	float fRec125[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "virtualAnalogLab");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "0.0");
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
		fConst2 = tanf((494.769836f / fConst0));
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
		fConst14 = tanf((785.398193f / fConst0));
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
		fConst25 = tanf((1246.74182f / fConst0));
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
		fConst36 = tanf((1979.07935f / fConst0));
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
		fConst47 = tanf((3141.59277f / fConst0));
		fConst48 = (1.0f / fConst47);
		fConst49 = (1.0f / (((fConst48 + 0.168404877f) / fConst47) + 1.06935835f));
		fConst50 = mydsp_faustpower2_f(fConst47);
		fConst51 = (1.0f / fConst50);
		fConst52 = (2.0f * (53.5361519f - fConst51));
		fConst53 = (1.0f / (((fConst48 + 0.51247865f) / fConst47) + 0.689621389f));
		fConst54 = (2.0f * (7.62173128f - fConst51));
		fConst55 = (1.0f / (((fConst48 + 0.782413065f) / fConst47) + 0.245291501f));
		fConst56 = (9.99999975e-05f / fConst50);
		fConst57 = (2.0f * (0.000433227193f - fConst56));
		fConst58 = tanf((4986.96729f / fConst0));
		fConst59 = (1.0f / fConst58);
		fConst60 = (1.0f / (((fConst59 + 0.168404877f) / fConst58) + 1.06935835f));
		fConst61 = mydsp_faustpower2_f(fConst58);
		fConst62 = (1.0f / fConst61);
		fConst63 = (2.0f * (53.5361519f - fConst62));
		fConst64 = (1.0f / (((fConst59 + 0.51247865f) / fConst58) + 0.689621389f));
		fConst65 = (2.0f * (7.62173128f - fConst62));
		fConst66 = (1.0f / (((fConst59 + 0.782413065f) / fConst58) + 0.245291501f));
		fConst67 = (9.99999975e-05f / fConst61);
		fConst68 = (2.0f * (0.000433227193f - fConst67));
		fConst69 = tanf((7916.31738f / fConst0));
		fConst70 = (1.0f / fConst69);
		fConst71 = (1.0f / (((fConst70 + 0.168404877f) / fConst69) + 1.06935835f));
		fConst72 = mydsp_faustpower2_f(fConst69);
		fConst73 = (1.0f / fConst72);
		fConst74 = (2.0f * (53.5361519f - fConst73));
		fConst75 = (1.0f / (((fConst70 + 0.51247865f) / fConst69) + 0.689621389f));
		fConst76 = (2.0f * (7.62173128f - fConst73));
		fConst77 = (1.0f / (((fConst70 + 0.782413065f) / fConst69) + 0.245291501f));
		fConst78 = (9.99999975e-05f / fConst72);
		fConst79 = (2.0f * (0.000433227193f - fConst78));
		fConst80 = tanf((12566.3711f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (1.0f / (((fConst81 + 0.168404877f) / fConst80) + 1.06935835f));
		fConst83 = mydsp_faustpower2_f(fConst80);
		fConst84 = (1.0f / fConst83);
		fConst85 = (2.0f * (53.5361519f - fConst84));
		fConst86 = (1.0f / (((fConst81 + 0.51247865f) / fConst80) + 0.689621389f));
		fConst87 = (2.0f * (7.62173128f - fConst84));
		fConst88 = (1.0f / (((fConst81 + 0.782413065f) / fConst80) + 0.245291501f));
		fConst89 = (9.99999975e-05f / fConst83);
		fConst90 = (2.0f * (0.000433227193f - fConst89));
		fConst91 = tanf((19947.8691f / fConst0));
		fConst92 = (1.0f / fConst91);
		fConst93 = (1.0f / (((fConst92 + 0.168404877f) / fConst91) + 1.06935835f));
		fConst94 = mydsp_faustpower2_f(fConst91);
		fConst95 = (1.0f / fConst94);
		fConst96 = (2.0f * (53.5361519f - fConst95));
		fConst97 = (1.0f / (((fConst92 + 0.51247865f) / fConst91) + 0.689621389f));
		fConst98 = (2.0f * (7.62173128f - fConst95));
		fConst99 = (1.0f / (((fConst92 + 0.782413065f) / fConst91) + 0.245291501f));
		fConst100 = (9.99999975e-05f / fConst94);
		fConst101 = (2.0f * (0.000433227193f - fConst100));
		fConst102 = tanf((31665.2695f / fConst0));
		fConst103 = (1.0f / fConst102);
		fConst104 = (1.0f / (((fConst103 + 0.168404877f) / fConst102) + 1.06935835f));
		fConst105 = mydsp_faustpower2_f(fConst102);
		fConst106 = (1.0f / fConst105);
		fConst107 = (2.0f * (53.5361519f - fConst106));
		fConst108 = (1.0f / (((fConst103 + 0.51247865f) / fConst102) + 0.689621389f));
		fConst109 = (2.0f * (7.62173128f - fConst106));
		fConst110 = (1.0f / (((fConst103 + 0.782413065f) / fConst102) + 0.245291501f));
		fConst111 = (9.99999975e-05f / fConst105);
		fConst112 = (2.0f * (0.000433227193f - fConst111));
		fConst113 = tanf((50265.4844f / fConst0));
		fConst114 = (1.0f / fConst113);
		fConst115 = (1.0f / (((fConst114 + 0.168404877f) / fConst113) + 1.06935835f));
		fConst116 = mydsp_faustpower2_f(fConst113);
		fConst117 = (1.0f / fConst116);
		fConst118 = (2.0f * (53.5361519f - fConst117));
		fConst119 = (1.0f / (((fConst114 + 0.51247865f) / fConst113) + 0.689621389f));
		fConst120 = (2.0f * (7.62173128f - fConst117));
		fConst121 = (1.0f / (((fConst114 + 0.782413065f) / fConst113) + 0.245291501f));
		fConst122 = (9.99999975e-05f / fConst116);
		fConst123 = (2.0f * (0.000433227193f - fConst122));
		fConst124 = (6.28318548f / fConst0);
		fConst125 = (1.0f / fConst0);
		fConst126 = (0.25f * fConst0);
		fConst127 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst128 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst129 = (0.0833333358f * fConst0);
		fConst130 = (0.5f * fConst0);
		fConst131 = (1.33333337f / fConst0);
		fConst132 = (0.013888889f * fConst0);
		fConst133 = (3.14159274f / fConst0);
		fConst134 = (((fConst114 + -0.782413065f) / fConst113) + 0.245291501f);
		fConst135 = (2.0f * (0.245291501f - fConst117));
		fConst136 = (fConst122 + 0.000433227193f);
		fConst137 = (((fConst114 + -0.51247865f) / fConst113) + 0.689621389f);
		fConst138 = (2.0f * (0.689621389f - fConst117));
		fConst139 = (fConst117 + 7.62173128f);
		fConst140 = (((fConst114 + -0.168404877f) / fConst113) + 1.06935835f);
		fConst141 = (2.0f * (1.06935835f - fConst117));
		fConst142 = (fConst117 + 53.5361519f);
		fConst143 = (((fConst103 + -0.782413065f) / fConst102) + 0.245291501f);
		fConst144 = (2.0f * (0.245291501f - fConst106));
		fConst145 = (fConst111 + 0.000433227193f);
		fConst146 = (((fConst103 + -0.51247865f) / fConst102) + 0.689621389f);
		fConst147 = (2.0f * (0.689621389f - fConst106));
		fConst148 = (fConst106 + 7.62173128f);
		fConst149 = (((fConst103 + -0.168404877f) / fConst102) + 1.06935835f);
		fConst150 = (2.0f * (1.06935835f - fConst106));
		fConst151 = (fConst106 + 53.5361519f);
		fConst152 = (((fConst92 + -0.782413065f) / fConst91) + 0.245291501f);
		fConst153 = (2.0f * (0.245291501f - fConst95));
		fConst154 = (fConst100 + 0.000433227193f);
		fConst155 = (((fConst92 + -0.51247865f) / fConst91) + 0.689621389f);
		fConst156 = (2.0f * (0.689621389f - fConst95));
		fConst157 = (fConst95 + 7.62173128f);
		fConst158 = (((fConst92 + -0.168404877f) / fConst91) + 1.06935835f);
		fConst159 = (2.0f * (1.06935835f - fConst95));
		fConst160 = (fConst95 + 53.5361519f);
		fConst161 = (((fConst81 + -0.782413065f) / fConst80) + 0.245291501f);
		fConst162 = (2.0f * (0.245291501f - fConst84));
		fConst163 = (fConst89 + 0.000433227193f);
		fConst164 = (((fConst81 + -0.51247865f) / fConst80) + 0.689621389f);
		fConst165 = (2.0f * (0.689621389f - fConst84));
		fConst166 = (fConst84 + 7.62173128f);
		fConst167 = (((fConst81 + -0.168404877f) / fConst80) + 1.06935835f);
		fConst168 = (2.0f * (1.06935835f - fConst84));
		fConst169 = (fConst84 + 53.5361519f);
		fConst170 = (((fConst70 + -0.782413065f) / fConst69) + 0.245291501f);
		fConst171 = (2.0f * (0.245291501f - fConst73));
		fConst172 = (fConst78 + 0.000433227193f);
		fConst173 = (((fConst70 + -0.51247865f) / fConst69) + 0.689621389f);
		fConst174 = (2.0f * (0.689621389f - fConst73));
		fConst175 = (fConst73 + 7.62173128f);
		fConst176 = (((fConst70 + -0.168404877f) / fConst69) + 1.06935835f);
		fConst177 = (2.0f * (1.06935835f - fConst73));
		fConst178 = (fConst73 + 53.5361519f);
		fConst179 = (((fConst59 + -0.782413065f) / fConst58) + 0.245291501f);
		fConst180 = (2.0f * (0.245291501f - fConst62));
		fConst181 = (fConst67 + 0.000433227193f);
		fConst182 = (((fConst59 + -0.51247865f) / fConst58) + 0.689621389f);
		fConst183 = (2.0f * (0.689621389f - fConst62));
		fConst184 = (fConst62 + 7.62173128f);
		fConst185 = (((fConst59 + -0.168404877f) / fConst58) + 1.06935835f);
		fConst186 = (2.0f * (1.06935835f - fConst62));
		fConst187 = (fConst62 + 53.5361519f);
		fConst188 = (((fConst48 + -0.782413065f) / fConst47) + 0.245291501f);
		fConst189 = (2.0f * (0.245291501f - fConst51));
		fConst190 = (fConst56 + 0.000433227193f);
		fConst191 = (((fConst48 + -0.51247865f) / fConst47) + 0.689621389f);
		fConst192 = (2.0f * (0.689621389f - fConst51));
		fConst193 = (fConst51 + 7.62173128f);
		fConst194 = (((fConst48 + -0.168404877f) / fConst47) + 1.06935835f);
		fConst195 = (2.0f * (1.06935835f - fConst51));
		fConst196 = (fConst51 + 53.5361519f);
		fConst197 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst198 = (2.0f * (0.245291501f - fConst40));
		fConst199 = (fConst45 + 0.000433227193f);
		fConst200 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst201 = (2.0f * (0.689621389f - fConst40));
		fConst202 = (fConst40 + 7.62173128f);
		fConst203 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst204 = (2.0f * (1.06935835f - fConst40));
		fConst205 = (fConst40 + 53.5361519f);
		fConst206 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst207 = (2.0f * (0.245291501f - fConst29));
		fConst208 = (fConst34 + 0.000433227193f);
		fConst209 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst210 = (2.0f * (0.689621389f - fConst29));
		fConst211 = (fConst29 + 7.62173128f);
		fConst212 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst213 = (2.0f * (1.06935835f - fConst29));
		fConst214 = (fConst29 + 53.5361519f);
		fConst215 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst216 = (2.0f * (0.245291501f - fConst18));
		fConst217 = (fConst23 + 0.000433227193f);
		fConst218 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst219 = (2.0f * (0.689621389f - fConst18));
		fConst220 = (fConst18 + 7.62173128f);
		fConst221 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst222 = (2.0f * (1.06935835f - fConst18));
		fConst223 = (fConst18 + 53.5361519f);
		fConst224 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst225 = (1.0f / fConst5);
		fConst226 = (2.0f * (4.07678175f - fConst225));
		fConst227 = (fConst12 + 0.000407678192f);
		fConst228 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst229 = (2.0f * (1.4500711f - fConst225));
		fConst230 = (fConst9 + 1.4500711f);
		fConst231 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst232 = (2.0f * (0.935140193f - fConst225));
		fConst233 = (fConst6 + 0.935140193f);
		fConst234 = tanf((311.685455f / fConst0));
		fConst235 = (1.0f / fConst234);
		fConst236 = (1.0f / (((fConst235 + 0.157482162f) / fConst234) + 0.935140193f));
		fConst237 = mydsp_faustpower2_f(fConst234);
		fConst238 = (50.0638084f / fConst237);
		fConst239 = (2.0f * (0.935140193f - fConst238));
		fConst240 = (1.0f / (((fConst235 + 0.743130445f) / fConst234) + 1.4500711f));
		fConst241 = (11.0520525f / fConst237);
		fConst242 = (2.0f * (1.4500711f - fConst241));
		fConst243 = (1.0f / (((fConst235 + 3.18972731f) / fConst234) + 4.07678175f));
		fConst244 = (0.00176617282f / fConst237);
		fConst245 = (2.0f * (0.000407678192f - fConst244));
		fConst246 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst247 = (2.0f * (53.5361519f - fConst225));
		fConst248 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst249 = (2.0f * (7.62173128f - fConst225));
		fConst250 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst251 = (9.99999975e-05f / fConst5);
		fConst252 = (2.0f * (0.000433227193f - fConst251));
		fConst253 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst254 = (2.0f * (0.245291501f - fConst225));
		fConst255 = (fConst251 + 0.000433227193f);
		fConst256 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst257 = (2.0f * (0.689621389f - fConst225));
		fConst258 = (fConst225 + 7.62173128f);
		fConst259 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst260 = (2.0f * (1.06935835f - fConst225));
		fConst261 = (fConst225 + 53.5361519f);
		fConst262 = (((fConst235 + -3.18972731f) / fConst234) + 4.07678175f);
		fConst263 = (1.0f / fConst237);
		fConst264 = (2.0f * (4.07678175f - fConst263));
		fConst265 = (fConst244 + 0.000407678192f);
		fConst266 = (((fConst235 + -0.743130445f) / fConst234) + 1.4500711f);
		fConst267 = (2.0f * (1.4500711f - fConst263));
		fConst268 = (fConst241 + 1.4500711f);
		fConst269 = (((fConst235 + -0.157482162f) / fConst234) + 0.935140193f);
		fConst270 = (2.0f * (0.935140193f - fConst263));
		fConst271 = (fConst238 + 0.935140193f);
		fConst272 = tanf((196.349548f / fConst0));
		fConst273 = (1.0f / fConst272);
		fConst274 = (1.0f / (((fConst273 + 0.157482162f) / fConst272) + 0.935140193f));
		fConst275 = mydsp_faustpower2_f(fConst272);
		fConst276 = (50.0638084f / fConst275);
		fConst277 = (2.0f * (0.935140193f - fConst276));
		fConst278 = (1.0f / (((fConst273 + 0.743130445f) / fConst272) + 1.4500711f));
		fConst279 = (11.0520525f / fConst275);
		fConst280 = (2.0f * (1.4500711f - fConst279));
		fConst281 = (1.0f / (((fConst273 + 3.18972731f) / fConst272) + 4.07678175f));
		fConst282 = (0.00176617282f / fConst275);
		fConst283 = (2.0f * (0.000407678192f - fConst282));
		fConst284 = (1.0f / (((fConst235 + 0.168404877f) / fConst234) + 1.06935835f));
		fConst285 = (2.0f * (53.5361519f - fConst263));
		fConst286 = (1.0f / (((fConst235 + 0.51247865f) / fConst234) + 0.689621389f));
		fConst287 = (2.0f * (7.62173128f - fConst263));
		fConst288 = (1.0f / (((fConst235 + 0.782413065f) / fConst234) + 0.245291501f));
		fConst289 = (9.99999975e-05f / fConst237);
		fConst290 = (2.0f * (0.000433227193f - fConst289));
		fConst291 = (((fConst235 + -0.782413065f) / fConst234) + 0.245291501f);
		fConst292 = (2.0f * (0.245291501f - fConst263));
		fConst293 = (fConst289 + 0.000433227193f);
		fConst294 = (((fConst235 + -0.51247865f) / fConst234) + 0.689621389f);
		fConst295 = (2.0f * (0.689621389f - fConst263));
		fConst296 = (fConst263 + 7.62173128f);
		fConst297 = (((fConst235 + -0.168404877f) / fConst234) + 1.06935835f);
		fConst298 = (2.0f * (1.06935835f - fConst263));
		fConst299 = (fConst263 + 53.5361519f);
		fConst300 = (((fConst273 + -3.18972731f) / fConst272) + 4.07678175f);
		fConst301 = (1.0f / fConst275);
		fConst302 = (2.0f * (4.07678175f - fConst301));
		fConst303 = (fConst282 + 0.000407678192f);
		fConst304 = (((fConst273 + -0.743130445f) / fConst272) + 1.4500711f);
		fConst305 = (2.0f * (1.4500711f - fConst301));
		fConst306 = (fConst279 + 1.4500711f);
		fConst307 = (((fConst273 + -0.157482162f) / fConst272) + 0.935140193f);
		fConst308 = (2.0f * (0.935140193f - fConst301));
		fConst309 = (fConst276 + 0.935140193f);
		fConst310 = tanf((123.692459f / fConst0));
		fConst311 = (1.0f / fConst310);
		fConst312 = (1.0f / (((fConst311 + 0.157482162f) / fConst310) + 0.935140193f));
		fConst313 = mydsp_faustpower2_f(fConst310);
		fConst314 = (50.0638084f / fConst313);
		fConst315 = (2.0f * (0.935140193f - fConst314));
		fConst316 = (1.0f / (((fConst311 + 0.743130445f) / fConst310) + 1.4500711f));
		fConst317 = (11.0520525f / fConst313);
		fConst318 = (2.0f * (1.4500711f - fConst317));
		fConst319 = (1.0f / (((fConst311 + 3.18972731f) / fConst310) + 4.07678175f));
		fConst320 = (0.00176617282f / fConst313);
		fConst321 = (2.0f * (0.000407678192f - fConst320));
		fConst322 = (1.0f / (((fConst273 + 0.168404877f) / fConst272) + 1.06935835f));
		fConst323 = (2.0f * (53.5361519f - fConst301));
		fConst324 = (1.0f / (((fConst273 + 0.51247865f) / fConst272) + 0.689621389f));
		fConst325 = (2.0f * (7.62173128f - fConst301));
		fConst326 = (1.0f / (((fConst273 + 0.782413065f) / fConst272) + 0.245291501f));
		fConst327 = (9.99999975e-05f / fConst275);
		fConst328 = (2.0f * (0.000433227193f - fConst327));
		fConst329 = (((fConst273 + -0.782413065f) / fConst272) + 0.245291501f);
		fConst330 = (2.0f * (0.245291501f - fConst301));
		fConst331 = (fConst327 + 0.000433227193f);
		fConst332 = (((fConst273 + -0.51247865f) / fConst272) + 0.689621389f);
		fConst333 = (2.0f * (0.689621389f - fConst301));
		fConst334 = (fConst301 + 7.62173128f);
		fConst335 = (((fConst273 + -0.168404877f) / fConst272) + 1.06935835f);
		fConst336 = (2.0f * (1.06935835f - fConst301));
		fConst337 = (fConst301 + 53.5361519f);
		fConst338 = (((fConst311 + -3.18972731f) / fConst310) + 4.07678175f);
		fConst339 = (1.0f / fConst313);
		fConst340 = (2.0f * (4.07678175f - fConst339));
		fConst341 = (fConst320 + 0.000407678192f);
		fConst342 = (((fConst311 + -0.743130445f) / fConst310) + 1.4500711f);
		fConst343 = (2.0f * (1.4500711f - fConst339));
		fConst344 = (fConst317 + 1.4500711f);
		fConst345 = (((fConst311 + -0.157482162f) / fConst310) + 0.935140193f);
		fConst346 = (2.0f * (0.935140193f - fConst339));
		fConst347 = (fConst314 + 0.935140193f);
		fConst348 = (1.0f / (((fConst311 + 0.168404877f) / fConst310) + 1.06935835f));
		fConst349 = (2.0f * (53.5361519f - fConst339));
		fConst350 = (1.0f / (((fConst311 + 0.51247865f) / fConst310) + 0.689621389f));
		fConst351 = (2.0f * (7.62173128f - fConst339));
		fConst352 = (1.0f / (((fConst311 + 0.782413065f) / fConst310) + 0.245291501f));
		fConst353 = (9.99999975e-05f / fConst313);
		fConst354 = (2.0f * (0.000433227193f - fConst353));
		fConst355 = (((fConst311 + -0.782413065f) / fConst310) + 0.245291501f);
		fConst356 = (2.0f * (0.245291501f - fConst339));
		fConst357 = (fConst353 + 0.000433227193f);
		fConst358 = (((fConst311 + -0.51247865f) / fConst310) + 0.689621389f);
		fConst359 = (2.0f * (0.689621389f - fConst339));
		fConst360 = (fConst339 + 7.62173128f);
		fConst361 = (((fConst311 + -0.168404877f) / fConst310) + 1.06935835f);
		fConst362 = (2.0f * (1.06935835f - fConst339));
		fConst363 = (fConst339 + 53.5361519f);
		fConst364 = (1.0f / (((fConst114 + 0.157482162f) / fConst113) + 0.935140193f));
		fConst365 = (50.0638084f / fConst116);
		fConst366 = (2.0f * (0.935140193f - fConst365));
		fConst367 = (1.0f / (((fConst114 + 0.743130445f) / fConst113) + 1.4500711f));
		fConst368 = (11.0520525f / fConst116);
		fConst369 = (2.0f * (1.4500711f - fConst368));
		fConst370 = (1.0f / (((fConst114 + 3.18972731f) / fConst113) + 4.07678175f));
		fConst371 = (0.00176617282f / fConst116);
		fConst372 = (2.0f * (0.000407678192f - fConst371));
		fConst373 = (((fConst114 + -3.18972731f) / fConst113) + 4.07678175f);
		fConst374 = (2.0f * (4.07678175f - fConst117));
		fConst375 = (fConst371 + 0.000407678192f);
		fConst376 = (((fConst114 + -0.743130445f) / fConst113) + 1.4500711f);
		fConst377 = (2.0f * (1.4500711f - fConst117));
		fConst378 = (fConst368 + 1.4500711f);
		fConst379 = (((fConst114 + -0.157482162f) / fConst113) + 0.935140193f);
		fConst380 = (2.0f * (0.935140193f - fConst117));
		fConst381 = (fConst365 + 0.935140193f);
		fConst382 = (1.0f / (((fConst103 + 0.157482162f) / fConst102) + 0.935140193f));
		fConst383 = (50.0638084f / fConst105);
		fConst384 = (2.0f * (0.935140193f - fConst383));
		fConst385 = (1.0f / (((fConst103 + 0.743130445f) / fConst102) + 1.4500711f));
		fConst386 = (11.0520525f / fConst105);
		fConst387 = (2.0f * (1.4500711f - fConst386));
		fConst388 = (1.0f / (((fConst103 + 3.18972731f) / fConst102) + 4.07678175f));
		fConst389 = (0.00176617282f / fConst105);
		fConst390 = (2.0f * (0.000407678192f - fConst389));
		fConst391 = (((fConst103 + -3.18972731f) / fConst102) + 4.07678175f);
		fConst392 = (2.0f * (4.07678175f - fConst106));
		fConst393 = (fConst389 + 0.000407678192f);
		fConst394 = (((fConst103 + -0.743130445f) / fConst102) + 1.4500711f);
		fConst395 = (2.0f * (1.4500711f - fConst106));
		fConst396 = (fConst386 + 1.4500711f);
		fConst397 = (((fConst103 + -0.157482162f) / fConst102) + 0.935140193f);
		fConst398 = (2.0f * (0.935140193f - fConst106));
		fConst399 = (fConst383 + 0.935140193f);
		fConst400 = (1.0f / (((fConst92 + 0.157482162f) / fConst91) + 0.935140193f));
		fConst401 = (50.0638084f / fConst94);
		fConst402 = (2.0f * (0.935140193f - fConst401));
		fConst403 = (1.0f / (((fConst92 + 0.743130445f) / fConst91) + 1.4500711f));
		fConst404 = (11.0520525f / fConst94);
		fConst405 = (2.0f * (1.4500711f - fConst404));
		fConst406 = (1.0f / (((fConst92 + 3.18972731f) / fConst91) + 4.07678175f));
		fConst407 = (0.00176617282f / fConst94);
		fConst408 = (2.0f * (0.000407678192f - fConst407));
		fConst409 = (((fConst92 + -3.18972731f) / fConst91) + 4.07678175f);
		fConst410 = (2.0f * (4.07678175f - fConst95));
		fConst411 = (fConst407 + 0.000407678192f);
		fConst412 = (((fConst92 + -0.743130445f) / fConst91) + 1.4500711f);
		fConst413 = (2.0f * (1.4500711f - fConst95));
		fConst414 = (fConst404 + 1.4500711f);
		fConst415 = (((fConst92 + -0.157482162f) / fConst91) + 0.935140193f);
		fConst416 = (2.0f * (0.935140193f - fConst95));
		fConst417 = (fConst401 + 0.935140193f);
		fConst418 = (1.0f / (((fConst81 + 0.157482162f) / fConst80) + 0.935140193f));
		fConst419 = (50.0638084f / fConst83);
		fConst420 = (2.0f * (0.935140193f - fConst419));
		fConst421 = (1.0f / (((fConst81 + 0.743130445f) / fConst80) + 1.4500711f));
		fConst422 = (11.0520525f / fConst83);
		fConst423 = (2.0f * (1.4500711f - fConst422));
		fConst424 = (1.0f / (((fConst81 + 3.18972731f) / fConst80) + 4.07678175f));
		fConst425 = (0.00176617282f / fConst83);
		fConst426 = (2.0f * (0.000407678192f - fConst425));
		fConst427 = (((fConst81 + -3.18972731f) / fConst80) + 4.07678175f);
		fConst428 = (2.0f * (4.07678175f - fConst84));
		fConst429 = (fConst425 + 0.000407678192f);
		fConst430 = (((fConst81 + -0.743130445f) / fConst80) + 1.4500711f);
		fConst431 = (2.0f * (1.4500711f - fConst84));
		fConst432 = (fConst422 + 1.4500711f);
		fConst433 = (((fConst81 + -0.157482162f) / fConst80) + 0.935140193f);
		fConst434 = (2.0f * (0.935140193f - fConst84));
		fConst435 = (fConst419 + 0.935140193f);
		fConst436 = (1.0f / (((fConst70 + 0.157482162f) / fConst69) + 0.935140193f));
		fConst437 = (50.0638084f / fConst72);
		fConst438 = (2.0f * (0.935140193f - fConst437));
		fConst439 = (1.0f / (((fConst70 + 0.743130445f) / fConst69) + 1.4500711f));
		fConst440 = (11.0520525f / fConst72);
		fConst441 = (2.0f * (1.4500711f - fConst440));
		fConst442 = (1.0f / (((fConst70 + 3.18972731f) / fConst69) + 4.07678175f));
		fConst443 = (0.00176617282f / fConst72);
		fConst444 = (2.0f * (0.000407678192f - fConst443));
		fConst445 = (((fConst70 + -3.18972731f) / fConst69) + 4.07678175f);
		fConst446 = (2.0f * (4.07678175f - fConst73));
		fConst447 = (fConst443 + 0.000407678192f);
		fConst448 = (((fConst70 + -0.743130445f) / fConst69) + 1.4500711f);
		fConst449 = (2.0f * (1.4500711f - fConst73));
		fConst450 = (fConst440 + 1.4500711f);
		fConst451 = (((fConst70 + -0.157482162f) / fConst69) + 0.935140193f);
		fConst452 = (2.0f * (0.935140193f - fConst73));
		fConst453 = (fConst437 + 0.935140193f);
		fConst454 = (1.0f / (((fConst59 + 0.157482162f) / fConst58) + 0.935140193f));
		fConst455 = (50.0638084f / fConst61);
		fConst456 = (2.0f * (0.935140193f - fConst455));
		fConst457 = (1.0f / (((fConst59 + 0.743130445f) / fConst58) + 1.4500711f));
		fConst458 = (11.0520525f / fConst61);
		fConst459 = (2.0f * (1.4500711f - fConst458));
		fConst460 = (1.0f / (((fConst59 + 3.18972731f) / fConst58) + 4.07678175f));
		fConst461 = (0.00176617282f / fConst61);
		fConst462 = (2.0f * (0.000407678192f - fConst461));
		fConst463 = (((fConst59 + -3.18972731f) / fConst58) + 4.07678175f);
		fConst464 = (2.0f * (4.07678175f - fConst62));
		fConst465 = (fConst461 + 0.000407678192f);
		fConst466 = (((fConst59 + -0.743130445f) / fConst58) + 1.4500711f);
		fConst467 = (2.0f * (1.4500711f - fConst62));
		fConst468 = (fConst458 + 1.4500711f);
		fConst469 = (((fConst59 + -0.157482162f) / fConst58) + 0.935140193f);
		fConst470 = (2.0f * (0.935140193f - fConst62));
		fConst471 = (fConst455 + 0.935140193f);
		fConst472 = (1.0f / (((fConst48 + 0.157482162f) / fConst47) + 0.935140193f));
		fConst473 = (50.0638084f / fConst50);
		fConst474 = (2.0f * (0.935140193f - fConst473));
		fConst475 = (1.0f / (((fConst48 + 0.743130445f) / fConst47) + 1.4500711f));
		fConst476 = (11.0520525f / fConst50);
		fConst477 = (2.0f * (1.4500711f - fConst476));
		fConst478 = (1.0f / (((fConst48 + 3.18972731f) / fConst47) + 4.07678175f));
		fConst479 = (0.00176617282f / fConst50);
		fConst480 = (2.0f * (0.000407678192f - fConst479));
		fConst481 = (((fConst48 + -3.18972731f) / fConst47) + 4.07678175f);
		fConst482 = (2.0f * (4.07678175f - fConst51));
		fConst483 = (fConst479 + 0.000407678192f);
		fConst484 = (((fConst48 + -0.743130445f) / fConst47) + 1.4500711f);
		fConst485 = (2.0f * (1.4500711f - fConst51));
		fConst486 = (fConst476 + 1.4500711f);
		fConst487 = (((fConst48 + -0.157482162f) / fConst47) + 0.935140193f);
		fConst488 = (2.0f * (0.935140193f - fConst51));
		fConst489 = (fConst473 + 0.935140193f);
		fConst490 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst491 = (50.0638084f / fConst39);
		fConst492 = (2.0f * (0.935140193f - fConst491));
		fConst493 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst494 = (11.0520525f / fConst39);
		fConst495 = (2.0f * (1.4500711f - fConst494));
		fConst496 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst497 = (0.00176617282f / fConst39);
		fConst498 = (2.0f * (0.000407678192f - fConst497));
		fConst499 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst500 = (2.0f * (4.07678175f - fConst40));
		fConst501 = (fConst497 + 0.000407678192f);
		fConst502 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst503 = (2.0f * (1.4500711f - fConst40));
		fConst504 = (fConst494 + 1.4500711f);
		fConst505 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst506 = (2.0f * (0.935140193f - fConst40));
		fConst507 = (fConst491 + 0.935140193f);
		fConst508 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst509 = (50.0638084f / fConst28);
		fConst510 = (2.0f * (0.935140193f - fConst509));
		fConst511 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst512 = (11.0520525f / fConst28);
		fConst513 = (2.0f * (1.4500711f - fConst512));
		fConst514 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst515 = (0.00176617282f / fConst28);
		fConst516 = (2.0f * (0.000407678192f - fConst515));
		fConst517 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst518 = (2.0f * (4.07678175f - fConst29));
		fConst519 = (fConst515 + 0.000407678192f);
		fConst520 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst521 = (2.0f * (1.4500711f - fConst29));
		fConst522 = (fConst512 + 1.4500711f);
		fConst523 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst524 = (2.0f * (0.935140193f - fConst29));
		fConst525 = (fConst509 + 0.935140193f);
		fConst526 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst527 = (50.0638084f / fConst17);
		fConst528 = (2.0f * (0.935140193f - fConst527));
		fConst529 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst530 = (11.0520525f / fConst17);
		fConst531 = (2.0f * (1.4500711f - fConst530));
		fConst532 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst533 = (0.00176617282f / fConst17);
		fConst534 = (2.0f * (0.000407678192f - fConst533));
		fConst535 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst536 = (2.0f * (4.07678175f - fConst18));
		fConst537 = (fConst533 + 0.000407678192f);
		fConst538 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst539 = (2.0f * (1.4500711f - fConst18));
		fConst540 = (fConst530 + 1.4500711f);
		fConst541 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst542 = (2.0f * (0.935140193f - fConst18));
		fConst543 = (fConst527 + 0.935140193f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(5.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(25.0f);
		fVslider0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(-20.0f);
		fVslider1 = FAUSTFLOAT(1.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fHslider5 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fVslider8 = FAUSTFLOAT(0.5f);
		fVslider9 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.90000000000000002f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec34[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec36[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec41[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec43[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec42[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec3[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec4[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec5[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec6[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec7[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec8[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec44[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec9[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec10[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec11[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec12[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec13[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec14[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec15[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec45[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec16[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec17[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec18[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec19[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec20[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fVec21[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec22[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec46[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec23[l31] = 0.0f;
			
		}
		IOTA = 0;
		for (int l32 = 0; (l32 < 4096); l32 = (l32 + 1)) {
			fVec24[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec25[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec47[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec26[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 4096); l36 = (l36 + 1)) {
			fVec27[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec28[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec48[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fVec29[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 4096); l40 = (l40 + 1)) {
			fVec30[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec49[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec50[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec51[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fVec31[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec32[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 4096); l46 = (l46 + 1)) {
			fVec33[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec52[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec34[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec35[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 4096); l50 = (l50 + 1)) {
			fVec36[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fVec37[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec38[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 4096); l53 = (l53 + 1)) {
			fVec39[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			iRec54[l54] = 0;
			
		}
		for (int l55 = 0; (l55 < 4); l55 = (l55 + 1)) {
			fRec53[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec40[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec39[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec38[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec37[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec35[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec57[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec56[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec55[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec60[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec58[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec63[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec61[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec33[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec32[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec31[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec30[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec29[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec28[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec27[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec26[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec25[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec24[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec23[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec22[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec21[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec20[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec19[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec18[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec17[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec16[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec15[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec14[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec13[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec12[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec11[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec10[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec9[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec8[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec7[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec6[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec5[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec4[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec3[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec2[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec1[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec0[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec70[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec69[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec68[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec67[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec66[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec65[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec64[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec77[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec76[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec75[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec74[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec73[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec72[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec71[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec84[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec83[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec82[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec81[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec80[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec79[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec78[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec88[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec87[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec86[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec85[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec92[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec91[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec90[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec89[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec96[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec95[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec94[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec93[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec100[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec99[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec98[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) {
			fRec97[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec104[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec103[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec102[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			fRec101[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec108[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec107[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec106[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 2); l146 = (l146 + 1)) {
			fRec105[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			fRec112[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			fRec111[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec110[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			fRec109[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec116[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			fRec115[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec114[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fRec113[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 3); l155 = (l155 + 1)) {
			fRec120[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			fRec119[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			fRec118[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) {
			fRec117[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			fRec124[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			fRec123[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			fRec122[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fRec121[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			fRec128[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			fRec127[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			fRec126[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			fRec125[l166] = 0.0f;
			
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
		ui_interface->openVerticalBox("virtualAnalogLab");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib for documentation and references");
		ui_interface->openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("Signal Levels");
		ui_interface->declare(&fVslider1, "0", "");
		ui_interface->declare(&fVslider1, "style", "vslider");
		ui_interface->addVerticalSlider("Sawtooth", &fVslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Pulse Train");
		ui_interface->declare(&fCheckbox2, "0", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface->addCheckButton("Order 3", &fCheckbox2);
		ui_interface->declare(&fVslider7, "1", "");
		ui_interface->declare(&fVslider7, "style", "vslider");
		ui_interface->addVerticalSlider("0x00", &fVslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider8, "2", "");
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->addVerticalSlider("Duty Cycle", &fVslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider5, "2", "");
		ui_interface->declare(&fVslider5, "style", "vslider");
		ui_interface->addVerticalSlider("Square", &fVslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider6, "3", "");
		ui_interface->declare(&fVslider6, "style", "vslider");
		ui_interface->addVerticalSlider("Triangle", &fVslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider9, "4", "");
		ui_interface->declare(&fVslider9, "style", "vslider");
		ui_interface->declare(&fVslider9, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface->addVerticalSlider("Pink Noise", &fVslider9, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider0, "5", "");
		ui_interface->declare(&fVslider0, "style", "vslider");
		ui_interface->addVerticalSlider("Ext Input", &fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Signal Parameters");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "hslider");
		ui_interface->declare(&fHslider4, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Mix Amplitude", &fHslider4, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "style", "hslider");
		ui_interface->declare(&fHslider5, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fHslider5, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider5, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentange frequency-shift up or down for second oscillator");
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
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "See Faust's   vaeffects.lib for info and references");
		ui_interface->openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the Moog VCF   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "1", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface->addCheckButton("Use Biquads", &fCheckbox1);
		ui_interface->declare(&fCheckbox3, "2", "");
		ui_interface->declare(&fCheckbox3, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fCheckbox3);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface->declare(&fHslider3, "unit", "PK");
		ui_interface->addHorizontalSlider("Corner Frequency", &fHslider3, 25.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fHslider6, "2", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface->addHorizontalSlider("Corner Resonance", &fHslider6, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "output level in decibels");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("VCF Output Level", &fHslider2, 5.0f, -60.0f, 20.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph4, "0", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe1ad90", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "1", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe09430", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "2", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fde3360", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "3", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fdc1210", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "4", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fd9f2e0", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph14, "5", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fab08a0", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "6", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fa9e9d0", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "7", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fead3a0", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "8", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe9ae70", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "9", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe88940", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "10", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe76410", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "11", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe63ee0", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "12", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe519b0", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "13", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe3f480", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "14", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ff81fe2cf50", &fVbargraph5, -50.0f, 10.0f);
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
		float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider2))));
		int iSlow5 = int(float(fCheckbox1));
		float fSlow6 = (0.439999998f * powf(2.0f, (0.0833333358f * (float(fHslider3) + -49.0f))));
		float fSlow7 = float(fVslider0);
		float fSlow8 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider4))));
		float fSlow9 = (0.333333343f * float(fVslider1));
		int iSlow10 = int((float(fEntry0) + -1.0f));
		int iSlow11 = (iSlow10 >= 2);
		int iSlow12 = (iSlow10 >= 1);
		float fSlow13 = expf((0.0f - (fConst125 / float(fVslider2))));
		float fSlow14 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fHslider5) + -49.0f))) * (1.0f - fSlow13)));
		int iSlow15 = (iSlow10 >= 3);
		float fSlow16 = (1.0f - (0.00999999978f * float(fVslider3)));
		float fSlow17 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		float fSlow18 = (fConst129 * float(fVslider5));
		float fSlow19 = (fConst131 * float(fVslider6));
		float fSlow20 = (fConst0 * float(fVslider7));
		float fSlow21 = float(fCheckbox2);
		float fSlow22 = (fConst132 * fSlow21);
		float fSlow23 = (0.00999999978f * float(fVslider8));
		float fSlow24 = (0.0833333358f * (1.0f - fSlow21));
		float fSlow25 = float(fVslider9);
		float fSlow26 = float(fHslider6);
		float fSlow27 = (0.0f - (4.0f * max(0.0f, min(mydsp_faustpower4_f(fSlow26), 0.999998987f))));
		int iSlow28 = int(float(fCheckbox3));
		float fSlow29 = min(1.41419947f, (1.41421354f * fSlow26));
		float fSlow30 = (fSlow29 * (fSlow29 + 1.41421354f));
		float fSlow31 = (1.41421354f * fSlow29);
		float fSlow32 = (fSlow31 + 2.0f);
		float fSlow33 = (fSlow29 * (fSlow29 + -1.41421354f));
		float fSlow34 = (2.0f - fSlow31);
		float fSlow35 = mydsp_faustpower2_f((1.41419947f * fSlow26));
		float fSlow36 = (1.99997997f * fSlow26);
		float fSlow37 = (fSlow35 + fSlow36);
		float fSlow38 = (fSlow36 + 2.0f);
		float fSlow39 = (2.0f - fSlow36);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec34[0] = (fSlow4 + (0.999000013f * fRec34[1]));
			fRec36[0] = (fSlow6 + (0.999000013f * fRec36[1]));
			float fTemp0 = (fConst124 * fRec36[0]);
			float fTemp1 = (1.0f - fTemp0);
			fRec41[0] = (fSlow8 + (0.999000013f * fRec41[1]));
			fRec43[0] = (fSlow14 + (fSlow13 * fRec43[1]));
			float fTemp2 = max(20.0f, fabsf(fRec43[0]));
			fVec1[0] = fTemp2;
			float fTemp3 = (fRec42[1] + (fConst125 * fVec1[1]));
			fRec42[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = (2.0f * fRec42[0]);
			float fTemp5 = (fTemp4 + -1.0f);
			float fTemp6 = mydsp_faustpower2_f(fTemp5);
			fVec2[0] = fTemp6;
			float fTemp7 = mydsp_faustpower3_f(fTemp5);
			fVec3[0] = (fTemp7 + (1.0f - fTemp4));
			float fTemp8 = ((fTemp7 + (1.0f - (fTemp4 + fVec3[1]))) / fTemp2);
			fVec4[0] = fTemp8;
			float fTemp9 = (fTemp6 * (fTemp6 + -2.0f));
			fVec5[0] = fTemp9;
			float fTemp10 = ((fTemp9 - fVec5[1]) / fTemp2);
			fVec6[0] = fTemp10;
			float fTemp11 = ((fTemp10 - fVec6[1]) / fTemp2);
			fVec7[0] = fTemp11;
			float fTemp12 = (fSlow16 * fRec43[0]);
			float fTemp13 = max(20.0f, fabsf(fTemp12));
			fVec8[0] = fTemp13;
			float fTemp14 = (fRec44[1] + (fConst125 * fVec8[1]));
			fRec44[0] = (fTemp14 - floorf(fTemp14));
			float fTemp15 = (2.0f * fRec44[0]);
			float fTemp16 = (fTemp15 + -1.0f);
			float fTemp17 = mydsp_faustpower2_f(fTemp16);
			fVec9[0] = fTemp17;
			float fTemp18 = mydsp_faustpower3_f(fTemp16);
			fVec10[0] = (fTemp18 + (1.0f - fTemp15));
			float fTemp19 = ((fTemp18 + (1.0f - (fTemp15 + fVec10[1]))) / fTemp13);
			fVec11[0] = fTemp19;
			float fTemp20 = (fTemp17 * (fTemp17 + -2.0f));
			fVec12[0] = fTemp20;
			float fTemp21 = ((fTemp20 - fVec12[1]) / fTemp13);
			fVec13[0] = fTemp21;
			float fTemp22 = ((fTemp21 - fVec13[1]) / fTemp13);
			fVec14[0] = fTemp22;
			float fTemp23 = (fSlow17 * fRec43[0]);
			float fTemp24 = max(20.0f, fabsf(fTemp23));
			fVec15[0] = fTemp24;
			float fTemp25 = (fRec45[1] + (fConst125 * fVec15[1]));
			fRec45[0] = (fTemp25 - floorf(fTemp25));
			float fTemp26 = (2.0f * fRec45[0]);
			float fTemp27 = (fTemp26 + -1.0f);
			float fTemp28 = mydsp_faustpower2_f(fTemp27);
			fVec16[0] = fTemp28;
			float fTemp29 = mydsp_faustpower3_f(fTemp27);
			fVec17[0] = (fTemp29 + (1.0f - fTemp26));
			float fTemp30 = ((fTemp29 + (1.0f - (fTemp26 + fVec17[1]))) / fTemp24);
			fVec18[0] = fTemp30;
			float fTemp31 = (fTemp28 * (fTemp28 + -2.0f));
			fVec19[0] = fTemp31;
			float fTemp32 = ((fTemp31 - fVec19[1]) / fTemp24);
			fVec20[0] = fTemp32;
			float fTemp33 = ((fTemp32 - fVec20[1]) / fTemp24);
			fVec21[0] = fTemp33;
			float fTemp34 = max(fRec43[0], 23.4489498f);
			float fTemp35 = max(20.0f, fabsf(fTemp34));
			fVec22[0] = fTemp35;
			float fTemp36 = (fRec46[1] + (fConst125 * fVec22[1]));
			fRec46[0] = (fTemp36 - floorf(fTemp36));
			float fTemp37 = (2.0f * fRec46[0]);
			float fTemp38 = (fTemp37 + -1.0f);
			float fTemp39 = mydsp_faustpower2_f(fTemp38);
			fVec23[0] = fTemp39;
			float fTemp40 = ((float(iVec0[1]) * (fTemp39 - fVec23[1])) / fTemp35);
			fVec24[(IOTA & 4095)] = fTemp40;
			float fTemp41 = max(0.0f, min(2047.0f, (fConst130 / fTemp34)));
			int iTemp42 = int(fTemp41);
			float fTemp43 = floorf(fTemp41);
			float fTemp44 = ((fTemp40 - (fVec24[((IOTA - iTemp42) & 4095)] * (fTemp43 + (1.0f - fTemp41)))) - ((fTemp41 - fTemp43) * fVec24[((IOTA - (iTemp42 + 1)) & 4095)]));
			float fTemp45 = max(fTemp12, 23.4489498f);
			float fTemp46 = max(20.0f, fabsf(fTemp45));
			fVec25[0] = fTemp46;
			float fTemp47 = (fRec47[1] + (fConst125 * fVec25[1]));
			fRec47[0] = (fTemp47 - floorf(fTemp47));
			float fTemp48 = (2.0f * fRec47[0]);
			float fTemp49 = (fTemp48 + -1.0f);
			float fTemp50 = mydsp_faustpower2_f(fTemp49);
			fVec26[0] = fTemp50;
			float fTemp51 = ((float(iVec0[1]) * (fTemp50 - fVec26[1])) / fTemp46);
			fVec27[(IOTA & 4095)] = fTemp51;
			float fTemp52 = max(0.0f, min(2047.0f, (fConst130 / fTemp45)));
			int iTemp53 = int(fTemp52);
			float fTemp54 = floorf(fTemp52);
			float fTemp55 = ((fTemp51 - (fVec27[((IOTA - iTemp53) & 4095)] * (fTemp54 + (1.0f - fTemp52)))) - ((fTemp52 - fTemp54) * fVec27[((IOTA - (iTemp53 + 1)) & 4095)]));
			float fTemp56 = max(fTemp23, 23.4489498f);
			float fTemp57 = max(20.0f, fabsf(fTemp56));
			fVec28[0] = fTemp57;
			float fTemp58 = (fRec48[1] + (fConst125 * fVec28[1]));
			fRec48[0] = (fTemp58 - floorf(fTemp58));
			float fTemp59 = (2.0f * fRec48[0]);
			float fTemp60 = (fTemp59 + -1.0f);
			float fTemp61 = mydsp_faustpower2_f(fTemp60);
			fVec29[0] = fTemp61;
			float fTemp62 = ((float(iVec0[1]) * (fTemp61 - fVec29[1])) / fTemp57);
			fVec30[(IOTA & 4095)] = fTemp62;
			float fTemp63 = max(0.0f, min(2047.0f, (fConst130 / fTemp56)));
			int iTemp64 = int(fTemp63);
			float fTemp65 = floorf(fTemp63);
			float fTemp66 = ((fTemp62 - (fVec30[((IOTA - iTemp64) & 4095)] * (fTemp65 + (1.0f - fTemp63)))) - ((fTemp63 - fTemp65) * fVec30[((IOTA - (iTemp64 + 1)) & 4095)]));
			fRec49[0] = ((fConst126 * fTemp44) + (0.999000013f * fRec49[1]));
			fRec50[0] = ((fConst126 * fTemp55) + (0.999000013f * fRec50[1]));
			fRec51[0] = ((fConst126 * fTemp66) + (0.999000013f * fRec51[1]));
			float fTemp67 = mydsp_faustpower3_f(fTemp38);
			fVec31[0] = (fTemp67 + (1.0f - fTemp37));
			float fTemp68 = ((fTemp67 + (1.0f - (fTemp37 + fVec31[1]))) / fTemp35);
			fVec32[0] = fTemp68;
			float fTemp69 = ((float(iVec0[2]) * (fTemp68 - fVec32[1])) / fTemp35);
			fVec33[(IOTA & 4095)] = fTemp69;
			fRec52[0] = (fSlow23 + (0.99000001f * fRec52[1]));
			float fTemp70 = max(0.0f, min(2047.0f, (fConst0 * (fRec52[0] / fTemp34))));
			int iTemp71 = int(fTemp70);
			float fTemp72 = floorf(fTemp70);
			float fTemp73 = (fTemp72 + (1.0f - fTemp70));
			float fTemp74 = (fTemp70 - fTemp72);
			int iTemp75 = (iTemp71 + 1);
			float fTemp76 = mydsp_faustpower3_f(fTemp49);
			fVec34[0] = (fTemp76 + (1.0f - fTemp48));
			float fTemp77 = ((fTemp76 + (1.0f - (fTemp48 + fVec34[1]))) / fTemp46);
			fVec35[0] = fTemp77;
			float fTemp78 = ((float(iVec0[2]) * (fTemp77 - fVec35[1])) / fTemp46);
			fVec36[(IOTA & 4095)] = fTemp78;
			float fTemp79 = max(0.0f, min(2047.0f, (fConst0 * (fRec52[0] / fTemp45))));
			int iTemp80 = int(fTemp79);
			float fTemp81 = floorf(fTemp79);
			float fTemp82 = (fTemp81 + (1.0f - fTemp79));
			float fTemp83 = (fTemp79 - fTemp81);
			int iTemp84 = (iTemp80 + 1);
			float fTemp85 = mydsp_faustpower3_f(fTemp60);
			fVec37[0] = (fTemp85 + (1.0f - fTemp59));
			float fTemp86 = ((fTemp85 + (1.0f - (fTemp59 + fVec37[1]))) / fTemp57);
			fVec38[0] = fTemp86;
			float fTemp87 = ((float(iVec0[2]) * (fTemp86 - fVec38[1])) / fTemp57);
			fVec39[(IOTA & 4095)] = fTemp87;
			float fTemp88 = max(0.0f, min(2047.0f, (fConst0 * (fRec52[0] / fTemp56))));
			int iTemp89 = int(fTemp88);
			float fTemp90 = floorf(fTemp88);
			float fTemp91 = (fTemp90 + (1.0f - fTemp88));
			float fTemp92 = (fTemp88 - fTemp90);
			int iTemp93 = (iTemp89 + 1);
			iRec54[0] = ((1103515245 * iRec54[1]) + 12345);
			fRec53[0] = (((4.65661287e-10f * float(iRec54[0])) + ((2.49495602f * fRec53[1]) + (0.522189379f * fRec53[3]))) - (2.0172658f * fRec53[2]));
			float fTemp94 = ((fSlow7 * float(input0[i])) + (fRec41[0] * (((((fSlow9 * (((iSlow11?(iSlow15?(fConst128 * ((float(iVec0[3]) * (fTemp11 - fVec7[1])) / fTemp2)):(fConst127 * ((float(iVec0[2]) * (fTemp8 - fVec4[1])) / fTemp2))):(iSlow12?(fConst126 * ((float(iVec0[1]) * (fTemp6 - fVec2[1])) / fTemp2)):fTemp5)) + (iSlow11?(iSlow15?(fConst128 * ((float(iVec0[3]) * (fTemp22 - fVec14[1])) / fTemp13)):(fConst127 * ((float(iVec0[2]) * (fTemp19 - fVec11[1])) / fTemp13))):(iSlow12?(fConst126 * ((float(iVec0[1]) * (fTemp17 - fVec9[1])) / fTemp13)):fTemp16))) + (iSlow11?(iSlow15?(fConst128 * ((float(iVec0[3]) * (fTemp33 - fVec21[1])) / fTemp24)):(fConst127 * ((float(iVec0[2]) * (fTemp30 - fVec18[1])) / fTemp24))):(iSlow12?(fConst126 * ((float(iVec0[1]) * (fTemp28 - fVec16[1])) / fTemp24)):fTemp27)))) + (fSlow18 * ((fTemp44 + fTemp55) + fTemp66))) + (fSlow19 * (fRec43[0] * ((fRec49[0] + (fSlow16 * fRec50[0])) + (fSlow17 * fRec51[0]))))) + (fSlow20 * ((fSlow22 * ((((fTemp69 - (fVec33[((IOTA - iTemp71) & 4095)] * fTemp73)) - (fTemp74 * fVec33[((IOTA - iTemp75) & 4095)])) + ((fTemp78 - (fVec36[((IOTA - iTemp80) & 4095)] * fTemp82)) - (fTemp83 * fVec36[((IOTA - iTemp84) & 4095)]))) + ((fTemp87 - (fVec39[((IOTA - iTemp89) & 4095)] * fTemp91)) - (fTemp92 * fVec39[((IOTA - iTemp93) & 4095)])))) + (fSlow24 * ((((fTemp40 - (fTemp73 * fVec24[((IOTA - iTemp71) & 4095)])) - (fTemp74 * fVec24[((IOTA - iTemp75) & 4095)])) + ((fTemp51 - (fTemp82 * fVec27[((IOTA - iTemp80) & 4095)])) - (fTemp83 * fVec27[((IOTA - iTemp84) & 4095)]))) + ((fTemp62 - (fTemp91 * fVec30[((IOTA - iTemp89) & 4095)])) - (fTemp92 * fVec30[((IOTA - iTemp93) & 4095)]))))))) + (fSlow25 * (((0.0499220341f * fRec53[0]) + (0.0506126992f * fRec53[2])) - ((0.0959935337f * fRec53[1]) + (0.00440878607f * fRec53[3])))))));
			float fTemp95 = (iSlow3?0.0f:fTemp94);
			fRec40[0] = (fTemp95 + ((fTemp1 * fRec40[1]) + (fSlow27 * fRec35[1])));
			fRec39[0] = ((fTemp1 * fRec39[1]) + fRec40[0]);
			fRec38[0] = ((fTemp1 * fRec38[1]) + fRec39[0]);
			fRec37[0] = ((fRec37[1] * fTemp1) + fRec38[0]);
			fRec35[0] = (powf(fTemp0, 4.0f) * fRec37[0]);
			fRec57[0] = (fSlow6 + (0.999000013f * fRec57[1]));
			float fTemp96 = tanf((fConst133 * max(20.0f, min(10000.0f, fRec57[0]))));
			float fTemp97 = (1.0f / fTemp96);
			float fTemp98 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp96)));
			float fTemp99 = (fSlow30 + (((fSlow32 + fTemp97) / fTemp96) + 1.0f));
			fRec56[0] = (fTemp95 - (((fRec56[2] * (fSlow30 + (((fTemp97 - fSlow32) / fTemp96) + 1.0f))) + (2.0f * (fRec56[1] * (fSlow30 + fTemp98)))) / fTemp99));
			float fTemp100 = (fSlow33 + (((fSlow34 + fTemp97) / fTemp96) + 1.0f));
			fRec55[0] = (((fRec56[2] + (fRec56[0] + (2.0f * fRec56[1]))) / fTemp99) - (((fRec55[2] * (fSlow33 + (((fTemp97 - fSlow34) / fTemp96) + 1.0f))) + (2.0f * (fRec55[1] * (fSlow33 + fTemp98)))) / fTemp100));
			float fTemp101 = tanf((fConst133 * max(fRec57[0], 20.0f)));
			float fTemp102 = (1.0f / fTemp101);
			float fTemp103 = (fSlow37 + (((fSlow38 + fTemp102) / fTemp101) + 1.0f));
			float fTemp104 = ((fSlow37 + (1.0f - ((fSlow38 - fTemp102) / fTemp101))) / fTemp103);
			float fTemp105 = max(-0.999899983f, min(0.999899983f, fTemp104));
			float fTemp106 = (1.0f - mydsp_faustpower2_f(fTemp105));
			float fTemp107 = sqrtf(max(0.0f, fTemp106));
			float fTemp108 = ((fRec58[1] * (0.0f - fTemp105)) + (fTemp95 * fTemp107));
			float fTemp109 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp101)));
			float fTemp110 = (fSlow37 + fTemp109);
			float fTemp111 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp110 / (fTemp103 * (fTemp104 + 1.0f))))));
			float fTemp112 = (1.0f - mydsp_faustpower2_f(fTemp111));
			float fTemp113 = sqrtf(max(0.0f, fTemp112));
			fRec60[0] = ((fRec60[1] * (0.0f - fTemp111)) + (fTemp108 * fTemp113));
			fRec58[0] = ((fTemp108 * fTemp111) + (fRec60[1] * fTemp113));
			float fRec59 = fRec60[0];
			float fTemp114 = (1.0f - (fTemp110 / fTemp103));
			float fTemp115 = sqrtf(fTemp106);
			float fTemp116 = ((((fTemp95 * fTemp105) + (fRec58[1] * fTemp107)) + (2.0f * ((fRec58[0] * fTemp114) / fTemp115))) + ((fRec59 * ((1.0f - fTemp104) - (2.0f * (fTemp111 * fTemp114)))) / (fTemp115 * sqrtf(fTemp112))));
			float fTemp117 = (fSlow35 + ((((fSlow39 + fTemp102) / fTemp101) + 1.0f) - fSlow36));
			float fTemp118 = ((fSlow35 + ((((fTemp102 - fSlow39) / fTemp101) + 1.0f) - fSlow36)) / fTemp117);
			float fTemp119 = max(-0.999899983f, min(0.999899983f, fTemp118));
			float fTemp120 = (1.0f - mydsp_faustpower2_f(fTemp119));
			float fTemp121 = sqrtf(max(0.0f, fTemp120));
			float fTemp122 = ((fRec61[1] * (0.0f - fTemp119)) + ((fTemp116 * fTemp121) / fTemp103));
			float fTemp123 = (fSlow35 + (fTemp109 - fSlow36));
			float fTemp124 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp123 / (fTemp117 * (fTemp118 + 1.0f))))));
			float fTemp125 = (1.0f - mydsp_faustpower2_f(fTemp124));
			float fTemp126 = sqrtf(max(0.0f, fTemp125));
			fRec63[0] = ((fRec63[1] * (0.0f - fTemp124)) + (fTemp122 * fTemp126));
			fRec61[0] = ((fTemp122 * fTemp124) + (fRec63[1] * fTemp126));
			float fRec62 = fRec63[0];
			float fTemp127 = (1.0f - (fTemp123 / fTemp117));
			float fTemp128 = sqrtf(fTemp120);
			float fTemp129 = (iSlow3?fTemp94:(fRec34[0] * (iSlow5?(iSlow28?((((((fTemp116 * fTemp119) / fTemp103) + (fRec61[1] * fTemp121)) + (2.0f * ((fRec61[0] * fTemp127) / fTemp128))) + ((fRec62 * ((1.0f - fTemp118) - (2.0f * (fTemp124 * fTemp127)))) / (fTemp128 * sqrtf(fTemp125)))) / fTemp117):((fRec55[2] + (fRec55[0] + (2.0f * fRec55[1]))) / fTemp100)):fRec35[0])));
			fRec33[0] = (fTemp129 - (fConst121 * ((fConst134 * fRec33[2]) + (fConst135 * fRec33[1]))));
			fRec32[0] = ((fConst121 * (((fConst123 * fRec33[1]) + (fConst136 * fRec33[0])) + (fConst136 * fRec33[2]))) - (fConst119 * ((fConst137 * fRec32[2]) + (fConst138 * fRec32[1]))));
			fRec31[0] = ((fConst119 * (((fConst120 * fRec32[1]) + (fConst139 * fRec32[0])) + (fConst139 * fRec32[2]))) - (fConst115 * ((fConst140 * fRec31[2]) + (fConst141 * fRec31[1]))));
			float fTemp130 = (fConst115 * (((fConst118 * fRec31[1]) + (fConst142 * fRec31[0])) + (fConst142 * fRec31[2])));
			fRec30[0] = (fTemp130 - (fConst110 * ((fConst143 * fRec30[2]) + (fConst144 * fRec30[1]))));
			fRec29[0] = ((fConst110 * (((fConst112 * fRec30[1]) + (fConst145 * fRec30[0])) + (fConst145 * fRec30[2]))) - (fConst108 * ((fConst146 * fRec29[2]) + (fConst147 * fRec29[1]))));
			fRec28[0] = ((fConst108 * (((fConst109 * fRec29[1]) + (fConst148 * fRec29[0])) + (fConst148 * fRec29[2]))) - (fConst104 * ((fConst149 * fRec28[2]) + (fConst150 * fRec28[1]))));
			float fTemp131 = (fConst104 * (((fConst107 * fRec28[1]) + (fConst151 * fRec28[0])) + (fConst151 * fRec28[2])));
			fRec27[0] = (fTemp131 - (fConst99 * ((fConst152 * fRec27[2]) + (fConst153 * fRec27[1]))));
			fRec26[0] = ((fConst99 * (((fConst101 * fRec27[1]) + (fConst154 * fRec27[0])) + (fConst154 * fRec27[2]))) - (fConst97 * ((fConst155 * fRec26[2]) + (fConst156 * fRec26[1]))));
			fRec25[0] = ((fConst97 * (((fConst98 * fRec26[1]) + (fConst157 * fRec26[0])) + (fConst157 * fRec26[2]))) - (fConst93 * ((fConst158 * fRec25[2]) + (fConst159 * fRec25[1]))));
			float fTemp132 = (fConst93 * (((fConst96 * fRec25[1]) + (fConst160 * fRec25[0])) + (fConst160 * fRec25[2])));
			fRec24[0] = (fTemp132 - (fConst88 * ((fConst161 * fRec24[2]) + (fConst162 * fRec24[1]))));
			fRec23[0] = ((fConst88 * (((fConst90 * fRec24[1]) + (fConst163 * fRec24[0])) + (fConst163 * fRec24[2]))) - (fConst86 * ((fConst164 * fRec23[2]) + (fConst165 * fRec23[1]))));
			fRec22[0] = ((fConst86 * (((fConst87 * fRec23[1]) + (fConst166 * fRec23[0])) + (fConst166 * fRec23[2]))) - (fConst82 * ((fConst167 * fRec22[2]) + (fConst168 * fRec22[1]))));
			float fTemp133 = (fConst82 * (((fConst85 * fRec22[1]) + (fConst169 * fRec22[0])) + (fConst169 * fRec22[2])));
			fRec21[0] = (fTemp133 - (fConst77 * ((fConst170 * fRec21[2]) + (fConst171 * fRec21[1]))));
			fRec20[0] = ((fConst77 * (((fConst79 * fRec21[1]) + (fConst172 * fRec21[0])) + (fConst172 * fRec21[2]))) - (fConst75 * ((fConst173 * fRec20[2]) + (fConst174 * fRec20[1]))));
			fRec19[0] = ((fConst75 * (((fConst76 * fRec20[1]) + (fConst175 * fRec20[0])) + (fConst175 * fRec20[2]))) - (fConst71 * ((fConst176 * fRec19[2]) + (fConst177 * fRec19[1]))));
			float fTemp134 = (fConst71 * (((fConst74 * fRec19[1]) + (fConst178 * fRec19[0])) + (fConst178 * fRec19[2])));
			fRec18[0] = (fTemp134 - (fConst66 * ((fConst179 * fRec18[2]) + (fConst180 * fRec18[1]))));
			fRec17[0] = ((fConst66 * (((fConst68 * fRec18[1]) + (fConst181 * fRec18[0])) + (fConst181 * fRec18[2]))) - (fConst64 * ((fConst182 * fRec17[2]) + (fConst183 * fRec17[1]))));
			fRec16[0] = ((fConst64 * (((fConst65 * fRec17[1]) + (fConst184 * fRec17[0])) + (fConst184 * fRec17[2]))) - (fConst60 * ((fConst185 * fRec16[2]) + (fConst186 * fRec16[1]))));
			float fTemp135 = (fConst60 * (((fConst63 * fRec16[1]) + (fConst187 * fRec16[0])) + (fConst187 * fRec16[2])));
			fRec15[0] = (fTemp135 - (fConst55 * ((fConst188 * fRec15[2]) + (fConst189 * fRec15[1]))));
			fRec14[0] = ((fConst55 * (((fConst57 * fRec15[1]) + (fConst190 * fRec15[0])) + (fConst190 * fRec15[2]))) - (fConst53 * ((fConst191 * fRec14[2]) + (fConst192 * fRec14[1]))));
			fRec13[0] = ((fConst53 * (((fConst54 * fRec14[1]) + (fConst193 * fRec14[0])) + (fConst193 * fRec14[2]))) - (fConst49 * ((fConst194 * fRec13[2]) + (fConst195 * fRec13[1]))));
			float fTemp136 = (fConst49 * (((fConst52 * fRec13[1]) + (fConst196 * fRec13[0])) + (fConst196 * fRec13[2])));
			fRec12[0] = (fTemp136 - (fConst44 * ((fConst197 * fRec12[2]) + (fConst198 * fRec12[1]))));
			fRec11[0] = ((fConst44 * (((fConst46 * fRec12[1]) + (fConst199 * fRec12[0])) + (fConst199 * fRec12[2]))) - (fConst42 * ((fConst200 * fRec11[2]) + (fConst201 * fRec11[1]))));
			fRec10[0] = ((fConst42 * (((fConst43 * fRec11[1]) + (fConst202 * fRec11[0])) + (fConst202 * fRec11[2]))) - (fConst38 * ((fConst203 * fRec10[2]) + (fConst204 * fRec10[1]))));
			float fTemp137 = (fConst38 * (((fConst41 * fRec10[1]) + (fConst205 * fRec10[0])) + (fConst205 * fRec10[2])));
			fRec9[0] = (fTemp137 - (fConst33 * ((fConst206 * fRec9[2]) + (fConst207 * fRec9[1]))));
			fRec8[0] = ((fConst33 * (((fConst35 * fRec9[1]) + (fConst208 * fRec9[0])) + (fConst208 * fRec9[2]))) - (fConst31 * ((fConst209 * fRec8[2]) + (fConst210 * fRec8[1]))));
			fRec7[0] = ((fConst31 * (((fConst32 * fRec8[1]) + (fConst211 * fRec8[0])) + (fConst211 * fRec8[2]))) - (fConst27 * ((fConst212 * fRec7[2]) + (fConst213 * fRec7[1]))));
			float fTemp138 = (fConst27 * (((fConst30 * fRec7[1]) + (fConst214 * fRec7[0])) + (fConst214 * fRec7[2])));
			fRec6[0] = (fTemp138 - (fConst22 * ((fConst215 * fRec6[2]) + (fConst216 * fRec6[1]))));
			fRec5[0] = ((fConst22 * (((fConst24 * fRec6[1]) + (fConst217 * fRec6[0])) + (fConst217 * fRec6[2]))) - (fConst20 * ((fConst218 * fRec5[2]) + (fConst219 * fRec5[1]))));
			fRec4[0] = ((fConst20 * (((fConst21 * fRec5[1]) + (fConst220 * fRec5[0])) + (fConst220 * fRec5[2]))) - (fConst16 * ((fConst221 * fRec4[2]) + (fConst222 * fRec4[1]))));
			float fTemp139 = (fConst16 * (((fConst19 * fRec4[1]) + (fConst223 * fRec4[0])) + (fConst223 * fRec4[2])));
			fRec3[0] = (fTemp139 - (fConst11 * ((fConst224 * fRec3[2]) + (fConst226 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst227 * fRec3[0])) + (fConst227 * fRec3[2]))) - (fConst8 * ((fConst228 * fRec2[2]) + (fConst229 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst230 * fRec2[0])) + (fConst230 * fRec2[2]))) - (fConst4 * ((fConst231 * fRec1[2]) + (fConst232 * fRec1[1]))));
			fRec0[0] = ((fSlow2 * fabsf((fConst4 * (((fConst7 * fRec1[1]) + (fConst233 * fRec1[0])) + (fConst233 * fRec1[2]))))) + (fSlow1 * fRec0[1]));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec0[0])))));
			fRec70[0] = (fTemp139 - (fConst250 * ((fConst253 * fRec70[2]) + (fConst254 * fRec70[1]))));
			fRec69[0] = ((fConst250 * (((fConst252 * fRec70[1]) + (fConst255 * fRec70[0])) + (fConst255 * fRec70[2]))) - (fConst248 * ((fConst256 * fRec69[2]) + (fConst257 * fRec69[1]))));
			fRec68[0] = ((fConst248 * (((fConst249 * fRec69[1]) + (fConst258 * fRec69[0])) + (fConst258 * fRec69[2]))) - (fConst246 * ((fConst259 * fRec68[2]) + (fConst260 * fRec68[1]))));
			float fTemp140 = (fConst246 * (((fConst247 * fRec68[1]) + (fConst261 * fRec68[0])) + (fConst261 * fRec68[2])));
			fRec67[0] = (fTemp140 - (fConst243 * ((fConst262 * fRec67[2]) + (fConst264 * fRec67[1]))));
			fRec66[0] = ((fConst243 * (((fConst245 * fRec67[1]) + (fConst265 * fRec67[0])) + (fConst265 * fRec67[2]))) - (fConst240 * ((fConst266 * fRec66[2]) + (fConst267 * fRec66[1]))));
			fRec65[0] = ((fConst240 * (((fConst242 * fRec66[1]) + (fConst268 * fRec66[0])) + (fConst268 * fRec66[2]))) - (fConst236 * ((fConst269 * fRec65[2]) + (fConst270 * fRec65[1]))));
			fRec64[0] = ((fSlow1 * fRec64[1]) + (fSlow2 * fabsf((fConst236 * (((fConst239 * fRec65[1]) + (fConst271 * fRec65[0])) + (fConst271 * fRec65[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec64[0])))));
			fRec77[0] = (fTemp140 - (fConst288 * ((fConst291 * fRec77[2]) + (fConst292 * fRec77[1]))));
			fRec76[0] = ((fConst288 * (((fConst290 * fRec77[1]) + (fConst293 * fRec77[0])) + (fConst293 * fRec77[2]))) - (fConst286 * ((fConst294 * fRec76[2]) + (fConst295 * fRec76[1]))));
			fRec75[0] = ((fConst286 * (((fConst287 * fRec76[1]) + (fConst296 * fRec76[0])) + (fConst296 * fRec76[2]))) - (fConst284 * ((fConst297 * fRec75[2]) + (fConst298 * fRec75[1]))));
			float fTemp141 = (fConst284 * (((fConst285 * fRec75[1]) + (fConst299 * fRec75[0])) + (fConst299 * fRec75[2])));
			fRec74[0] = (fTemp141 - (fConst281 * ((fConst300 * fRec74[2]) + (fConst302 * fRec74[1]))));
			fRec73[0] = ((fConst281 * (((fConst283 * fRec74[1]) + (fConst303 * fRec74[0])) + (fConst303 * fRec74[2]))) - (fConst278 * ((fConst304 * fRec73[2]) + (fConst305 * fRec73[1]))));
			fRec72[0] = ((fConst278 * (((fConst280 * fRec73[1]) + (fConst306 * fRec73[0])) + (fConst306 * fRec73[2]))) - (fConst274 * ((fConst307 * fRec72[2]) + (fConst308 * fRec72[1]))));
			fRec71[0] = ((fSlow1 * fRec71[1]) + (fSlow2 * fabsf((fConst274 * (((fConst277 * fRec72[1]) + (fConst309 * fRec72[0])) + (fConst309 * fRec72[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec71[0])))));
			fRec84[0] = (fTemp141 - (fConst326 * ((fConst329 * fRec84[2]) + (fConst330 * fRec84[1]))));
			fRec83[0] = ((fConst326 * (((fConst328 * fRec84[1]) + (fConst331 * fRec84[0])) + (fConst331 * fRec84[2]))) - (fConst324 * ((fConst332 * fRec83[2]) + (fConst333 * fRec83[1]))));
			fRec82[0] = ((fConst324 * (((fConst325 * fRec83[1]) + (fConst334 * fRec83[0])) + (fConst334 * fRec83[2]))) - (fConst322 * ((fConst335 * fRec82[2]) + (fConst336 * fRec82[1]))));
			float fTemp142 = (fConst322 * (((fConst323 * fRec82[1]) + (fConst337 * fRec82[0])) + (fConst337 * fRec82[2])));
			fRec81[0] = (fTemp142 - (fConst319 * ((fConst338 * fRec81[2]) + (fConst340 * fRec81[1]))));
			fRec80[0] = ((fConst319 * (((fConst321 * fRec81[1]) + (fConst341 * fRec81[0])) + (fConst341 * fRec81[2]))) - (fConst316 * ((fConst342 * fRec80[2]) + (fConst343 * fRec80[1]))));
			fRec79[0] = ((fConst316 * (((fConst318 * fRec80[1]) + (fConst344 * fRec80[0])) + (fConst344 * fRec80[2]))) - (fConst312 * ((fConst345 * fRec79[2]) + (fConst346 * fRec79[1]))));
			fRec78[0] = ((fSlow1 * fRec78[1]) + (fSlow2 * fabsf((fConst312 * (((fConst315 * fRec79[1]) + (fConst347 * fRec79[0])) + (fConst347 * fRec79[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec78[0])))));
			fRec88[0] = (fTemp142 - (fConst352 * ((fConst355 * fRec88[2]) + (fConst356 * fRec88[1]))));
			fRec87[0] = ((fConst352 * (((fConst354 * fRec88[1]) + (fConst357 * fRec88[0])) + (fConst357 * fRec88[2]))) - (fConst350 * ((fConst358 * fRec87[2]) + (fConst359 * fRec87[1]))));
			fRec86[0] = ((fConst350 * (((fConst351 * fRec87[1]) + (fConst360 * fRec87[0])) + (fConst360 * fRec87[2]))) - (fConst348 * ((fConst361 * fRec86[2]) + (fConst362 * fRec86[1]))));
			fRec85[0] = ((fSlow1 * fRec85[1]) + (fSlow2 * fabsf((fConst348 * (((fConst349 * fRec86[1]) + (fConst363 * fRec86[0])) + (fConst363 * fRec86[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec85[0])))));
			fRec92[0] = (fTemp129 - (fConst370 * ((fConst373 * fRec92[2]) + (fConst374 * fRec92[1]))));
			fRec91[0] = ((fConst370 * (((fConst372 * fRec92[1]) + (fConst375 * fRec92[0])) + (fConst375 * fRec92[2]))) - (fConst367 * ((fConst376 * fRec91[2]) + (fConst377 * fRec91[1]))));
			fRec90[0] = ((fConst367 * (((fConst369 * fRec91[1]) + (fConst378 * fRec91[0])) + (fConst378 * fRec91[2]))) - (fConst364 * ((fConst379 * fRec90[2]) + (fConst380 * fRec90[1]))));
			fRec89[0] = ((fSlow1 * fRec89[1]) + (fSlow2 * fabsf((fConst364 * (((fConst366 * fRec90[1]) + (fConst381 * fRec90[0])) + (fConst381 * fRec90[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec89[0])))));
			fRec96[0] = (fTemp130 - (fConst388 * ((fConst391 * fRec96[2]) + (fConst392 * fRec96[1]))));
			fRec95[0] = ((fConst388 * (((fConst390 * fRec96[1]) + (fConst393 * fRec96[0])) + (fConst393 * fRec96[2]))) - (fConst385 * ((fConst394 * fRec95[2]) + (fConst395 * fRec95[1]))));
			fRec94[0] = ((fConst385 * (((fConst387 * fRec95[1]) + (fConst396 * fRec95[0])) + (fConst396 * fRec95[2]))) - (fConst382 * ((fConst397 * fRec94[2]) + (fConst398 * fRec94[1]))));
			fRec93[0] = ((fSlow1 * fRec93[1]) + (fSlow2 * fabsf((fConst382 * (((fConst384 * fRec94[1]) + (fConst399 * fRec94[0])) + (fConst399 * fRec94[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec93[0])))));
			fRec100[0] = (fTemp131 - (fConst406 * ((fConst409 * fRec100[2]) + (fConst410 * fRec100[1]))));
			fRec99[0] = ((fConst406 * (((fConst408 * fRec100[1]) + (fConst411 * fRec100[0])) + (fConst411 * fRec100[2]))) - (fConst403 * ((fConst412 * fRec99[2]) + (fConst413 * fRec99[1]))));
			fRec98[0] = ((fConst403 * (((fConst405 * fRec99[1]) + (fConst414 * fRec99[0])) + (fConst414 * fRec99[2]))) - (fConst400 * ((fConst415 * fRec98[2]) + (fConst416 * fRec98[1]))));
			fRec97[0] = ((fSlow1 * fRec97[1]) + (fSlow2 * fabsf((fConst400 * (((fConst402 * fRec98[1]) + (fConst417 * fRec98[0])) + (fConst417 * fRec98[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec97[0])))));
			fRec104[0] = (fTemp132 - (fConst424 * ((fConst427 * fRec104[2]) + (fConst428 * fRec104[1]))));
			fRec103[0] = ((fConst424 * (((fConst426 * fRec104[1]) + (fConst429 * fRec104[0])) + (fConst429 * fRec104[2]))) - (fConst421 * ((fConst430 * fRec103[2]) + (fConst431 * fRec103[1]))));
			fRec102[0] = ((fConst421 * (((fConst423 * fRec103[1]) + (fConst432 * fRec103[0])) + (fConst432 * fRec103[2]))) - (fConst418 * ((fConst433 * fRec102[2]) + (fConst434 * fRec102[1]))));
			fRec101[0] = ((fSlow1 * fRec101[1]) + (fSlow2 * fabsf((fConst418 * (((fConst420 * fRec102[1]) + (fConst435 * fRec102[0])) + (fConst435 * fRec102[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec101[0])))));
			fRec108[0] = (fTemp133 - (fConst442 * ((fConst445 * fRec108[2]) + (fConst446 * fRec108[1]))));
			fRec107[0] = ((fConst442 * (((fConst444 * fRec108[1]) + (fConst447 * fRec108[0])) + (fConst447 * fRec108[2]))) - (fConst439 * ((fConst448 * fRec107[2]) + (fConst449 * fRec107[1]))));
			fRec106[0] = ((fConst439 * (((fConst441 * fRec107[1]) + (fConst450 * fRec107[0])) + (fConst450 * fRec107[2]))) - (fConst436 * ((fConst451 * fRec106[2]) + (fConst452 * fRec106[1]))));
			fRec105[0] = ((fSlow1 * fRec105[1]) + (fSlow2 * fabsf((fConst436 * (((fConst438 * fRec106[1]) + (fConst453 * fRec106[0])) + (fConst453 * fRec106[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec105[0])))));
			fRec112[0] = (fTemp134 - (fConst460 * ((fConst463 * fRec112[2]) + (fConst464 * fRec112[1]))));
			fRec111[0] = ((fConst460 * (((fConst462 * fRec112[1]) + (fConst465 * fRec112[0])) + (fConst465 * fRec112[2]))) - (fConst457 * ((fConst466 * fRec111[2]) + (fConst467 * fRec111[1]))));
			fRec110[0] = ((fConst457 * (((fConst459 * fRec111[1]) + (fConst468 * fRec111[0])) + (fConst468 * fRec111[2]))) - (fConst454 * ((fConst469 * fRec110[2]) + (fConst470 * fRec110[1]))));
			fRec109[0] = ((fSlow1 * fRec109[1]) + (fSlow2 * fabsf((fConst454 * (((fConst456 * fRec110[1]) + (fConst471 * fRec110[0])) + (fConst471 * fRec110[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec109[0])))));
			fRec116[0] = (fTemp135 - (fConst478 * ((fConst481 * fRec116[2]) + (fConst482 * fRec116[1]))));
			fRec115[0] = ((fConst478 * (((fConst480 * fRec116[1]) + (fConst483 * fRec116[0])) + (fConst483 * fRec116[2]))) - (fConst475 * ((fConst484 * fRec115[2]) + (fConst485 * fRec115[1]))));
			fRec114[0] = ((fConst475 * (((fConst477 * fRec115[1]) + (fConst486 * fRec115[0])) + (fConst486 * fRec115[2]))) - (fConst472 * ((fConst487 * fRec114[2]) + (fConst488 * fRec114[1]))));
			fRec113[0] = ((fSlow1 * fRec113[1]) + (fSlow2 * fabsf((fConst472 * (((fConst474 * fRec114[1]) + (fConst489 * fRec114[0])) + (fConst489 * fRec114[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec113[0])))));
			fRec120[0] = (fTemp136 - (fConst496 * ((fConst499 * fRec120[2]) + (fConst500 * fRec120[1]))));
			fRec119[0] = ((fConst496 * (((fConst498 * fRec120[1]) + (fConst501 * fRec120[0])) + (fConst501 * fRec120[2]))) - (fConst493 * ((fConst502 * fRec119[2]) + (fConst503 * fRec119[1]))));
			fRec118[0] = ((fConst493 * (((fConst495 * fRec119[1]) + (fConst504 * fRec119[0])) + (fConst504 * fRec119[2]))) - (fConst490 * ((fConst505 * fRec118[2]) + (fConst506 * fRec118[1]))));
			fRec117[0] = ((fSlow1 * fRec117[1]) + (fSlow2 * fabsf((fConst490 * (((fConst492 * fRec118[1]) + (fConst507 * fRec118[0])) + (fConst507 * fRec118[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec117[0])))));
			fRec124[0] = (fTemp137 - (fConst514 * ((fConst517 * fRec124[2]) + (fConst518 * fRec124[1]))));
			fRec123[0] = ((fConst514 * (((fConst516 * fRec124[1]) + (fConst519 * fRec124[0])) + (fConst519 * fRec124[2]))) - (fConst511 * ((fConst520 * fRec123[2]) + (fConst521 * fRec123[1]))));
			fRec122[0] = ((fConst511 * (((fConst513 * fRec123[1]) + (fConst522 * fRec123[0])) + (fConst522 * fRec123[2]))) - (fConst508 * ((fConst523 * fRec122[2]) + (fConst524 * fRec122[1]))));
			fRec121[0] = ((fSlow1 * fRec121[1]) + (fSlow2 * fabsf((fConst508 * (((fConst510 * fRec122[1]) + (fConst525 * fRec122[0])) + (fConst525 * fRec122[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec121[0])))));
			fRec128[0] = (fTemp138 - (fConst532 * ((fConst535 * fRec128[2]) + (fConst536 * fRec128[1]))));
			fRec127[0] = ((fConst532 * (((fConst534 * fRec128[1]) + (fConst537 * fRec128[0])) + (fConst537 * fRec128[2]))) - (fConst529 * ((fConst538 * fRec127[2]) + (fConst539 * fRec127[1]))));
			fRec126[0] = ((fConst529 * (((fConst531 * fRec127[1]) + (fConst540 * fRec127[0])) + (fConst540 * fRec127[2]))) - (fConst526 * ((fConst541 * fRec126[2]) + (fConst542 * fRec126[1]))));
			fRec125[0] = ((fSlow1 * fRec125[1]) + (fSlow2 * fabsf((fConst526 * (((fConst528 * fRec126[1]) + (fConst543 * fRec126[0])) + (fConst543 * fRec126[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec125[0])))));
			output0[i] = FAUSTFLOAT(fTemp129);
			output1[i] = FAUSTFLOAT(fTemp129);
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec34[1] = fRec34[0];
			fRec36[1] = fRec36[0];
			fRec41[1] = fRec41[0];
			fRec43[1] = fRec43[0];
			fVec1[1] = fVec1[0];
			fRec42[1] = fRec42[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec44[1] = fRec44[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec45[1] = fRec45[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec46[1] = fRec46[0];
			fVec23[1] = fVec23[0];
			IOTA = (IOTA + 1);
			fVec25[1] = fVec25[0];
			fRec47[1] = fRec47[0];
			fVec26[1] = fVec26[0];
			fVec28[1] = fVec28[0];
			fRec48[1] = fRec48[0];
			fVec29[1] = fVec29[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec51[1] = fRec51[0];
			fVec31[1] = fVec31[0];
			fVec32[1] = fVec32[0];
			fRec52[1] = fRec52[0];
			fVec34[1] = fVec34[0];
			fVec35[1] = fVec35[0];
			fVec37[1] = fVec37[0];
			fVec38[1] = fVec38[0];
			iRec54[1] = iRec54[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec53[j1] = fRec53[(j1 - 1)];
				
			}
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec35[1] = fRec35[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec60[1] = fRec60[0];
			fRec58[1] = fRec58[0];
			fRec63[1] = fRec63[0];
			fRec61[1] = fRec61[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
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
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
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
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[1] = fRec64[0];
			fRec77[2] = fRec77[1];
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
			fRec71[1] = fRec71[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[1] = fRec78[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[1] = fRec85[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[1] = fRec89[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[1] = fRec93[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[1] = fRec97[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fRec101[1] = fRec101[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec105[1] = fRec105[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec109[1] = fRec109[0];
			fRec116[2] = fRec116[1];
			fRec116[1] = fRec116[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec114[2] = fRec114[1];
			fRec114[1] = fRec114[0];
			fRec113[1] = fRec113[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fRec119[2] = fRec119[1];
			fRec119[1] = fRec119[0];
			fRec118[2] = fRec118[1];
			fRec118[1] = fRec118[0];
			fRec117[1] = fRec117[0];
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec121[1] = fRec121[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			fRec127[2] = fRec127[1];
			fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec125[1] = fRec125[0];
			
		}
		
	}

	
};

#endif
