/* ------------------------------------------------------------
name: "vcfWahLab"
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
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider2;
	float fRec19[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	float fConst69;
	FAUSTFLOAT fHslider3;
	float fRec30[2];
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHslider4;
	float fRec32[2];
	FAUSTFLOAT fVslider0;
	float fRec33[2];
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fEntry0;
	float fConst70;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec35[2];
	float fVec1[2];
	float fRec34[2];
	float fConst71;
	float fVec2[2];
	float fConst72;
	float fVec3[2];
	float fVec4[2];
	float fConst73;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec36[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec37[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox6;
	int iRec38[2];
	float fRec39[4];
	float fConst74;
	float fConst75;
	float fRec40[2];
	float fRec41[2];
	float fRec31[3];
	float fRec29[2];
	float fRec28[2];
	float fRec27[2];
	float fRec26[2];
	float fRec25[2];
	FAUSTFLOAT fHslider5;
	float fRec42[2];
	FAUSTFLOAT fHslider6;
	float fRec24[2];
	float fRec23[2];
	float fRec22[2];
	float fRec21[2];
	float fRec20[2];
	FAUSTFLOAT fCheckbox7;
	float fConst76;
	float fRec45[2];
	float fRec44[3];
	float fRec43[3];
	float fRec48[2];
	float fRec46[2];
	float fRec51[2];
	float fRec49[2];
	float fConst77;
	float fConst78;
	float fRec18[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec17[3];
	float fConst82;
	float fConst83;
	float fConst84;
	float fRec16[3];
	float fConst85;
	float fConst86;
	float fConst87;
	float fRec15[3];
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec14[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec13[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec12[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec11[3];
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec10[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec9[3];
	float fConst106;
	float fConst107;
	float fConst108;
	float fRec8[3];
	float fConst109;
	float fConst110;
	float fConst111;
	float fRec7[3];
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec6[3];
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec5[3];
	float fConst118;
	float fConst119;
	float fConst120;
	float fRec4[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec3[3];
	float fConst125;
	float fConst126;
	float fConst127;
	float fRec2[3];
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec1[3];
	float fConst131;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec55[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec54[3];
	float fConst146;
	float fConst147;
	float fConst148;
	float fRec53[3];
	float fConst149;
	float fRec52[2];
	FAUSTFLOAT fVbargraph1;
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fConst160;
	float fRec59[3];
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec58[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec57[3];
	float fConst167;
	float fRec56[2];
	FAUSTFLOAT fVbargraph2;
	float fConst168;
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
	float fRec63[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec62[3];
	float fConst182;
	float fConst183;
	float fConst184;
	float fRec61[3];
	float fConst185;
	float fRec60[2];
	FAUSTFLOAT fVbargraph3;
	float fConst186;
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fConst196;
	float fRec67[3];
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec66[3];
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec65[3];
	float fConst203;
	float fRec64[2];
	FAUSTFLOAT fVbargraph4;
	float fConst204;
	float fConst205;
	float fConst206;
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec71[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec70[3];
	float fConst218;
	float fConst219;
	float fConst220;
	float fRec69[3];
	float fConst221;
	float fRec68[2];
	FAUSTFLOAT fVbargraph5;
	float fConst222;
	float fConst223;
	float fConst224;
	float fConst225;
	float fConst226;
	float fConst227;
	float fConst228;
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
	float fRec78[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec77[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fRec76[3];
	float fConst249;
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec75[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec74[3];
	float fConst256;
	float fConst257;
	float fConst258;
	float fRec73[3];
	float fConst259;
	float fRec72[2];
	FAUSTFLOAT fVbargraph6;
	float fConst260;
	float fConst261;
	float fConst262;
	float fConst263;
	float fConst264;
	float fConst265;
	float fConst266;
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
	float fRec85[3];
	float fConst281;
	float fConst282;
	float fConst283;
	float fRec84[3];
	float fConst284;
	float fConst285;
	float fConst286;
	float fRec83[3];
	float fConst287;
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec82[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec81[3];
	float fConst294;
	float fConst295;
	float fConst296;
	float fRec80[3];
	float fConst297;
	float fRec79[2];
	FAUSTFLOAT fVbargraph7;
	float fConst298;
	float fConst299;
	float fConst300;
	float fConst301;
	float fConst302;
	float fConst303;
	float fConst304;
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
	float fRec92[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec91[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fRec90[3];
	float fConst325;
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec89[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec88[3];
	float fConst332;
	float fConst333;
	float fConst334;
	float fRec87[3];
	float fConst335;
	float fRec86[2];
	FAUSTFLOAT fVbargraph8;
	float fConst336;
	float fConst337;
	float fConst338;
	float fConst339;
	float fConst340;
	float fConst341;
	float fConst342;
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
	float fRec99[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec98[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fRec97[3];
	float fConst363;
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec96[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec95[3];
	float fConst370;
	float fConst371;
	float fConst372;
	float fRec94[3];
	float fConst373;
	float fRec93[2];
	FAUSTFLOAT fVbargraph9;
	float fConst374;
	float fConst375;
	float fConst376;
	float fConst377;
	float fConst378;
	float fConst379;
	float fConst380;
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
	float fRec106[3];
	float fConst395;
	float fConst396;
	float fConst397;
	float fRec105[3];
	float fConst398;
	float fConst399;
	float fConst400;
	float fRec104[3];
	float fConst401;
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec103[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec102[3];
	float fConst408;
	float fConst409;
	float fConst410;
	float fRec101[3];
	float fConst411;
	float fRec100[2];
	FAUSTFLOAT fVbargraph10;
	float fConst412;
	float fConst413;
	float fConst414;
	float fConst415;
	float fConst416;
	float fConst417;
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
	float fConst429;
	float fConst430;
	float fConst431;
	float fConst432;
	float fRec113[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec112[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fRec111[3];
	float fConst439;
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec110[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec109[3];
	float fConst446;
	float fConst447;
	float fConst448;
	float fRec108[3];
	float fConst449;
	float fRec107[2];
	FAUSTFLOAT fVbargraph11;
	float fConst450;
	float fConst451;
	float fConst452;
	float fConst453;
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
	float fConst465;
	float fConst466;
	float fConst467;
	float fConst468;
	float fConst469;
	float fConst470;
	float fRec120[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec119[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fRec118[3];
	float fConst477;
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec117[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec116[3];
	float fConst484;
	float fConst485;
	float fConst486;
	float fRec115[3];
	float fConst487;
	float fRec114[2];
	FAUSTFLOAT fVbargraph12;
	float fConst488;
	float fConst489;
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
	float fConst501;
	float fConst502;
	float fConst503;
	float fConst504;
	float fConst505;
	float fConst506;
	float fConst507;
	float fConst508;
	float fRec127[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec126[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fRec125[3];
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
	float fRec131[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec130[3];
	float fConst538;
	float fConst539;
	float fConst540;
	float fRec129[3];
	float fConst541;
	float fRec128[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Demonstrate competing variable-lowpass-filter effects on test signals with spectrum analysis display");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "vcfWahLab");
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
		fConst2 = tanf((4986.96729f / fConst0));
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
		fConst14 = tanf((7916.31738f / fConst0));
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
		fConst25 = tanf((12566.3711f / fConst0));
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
		fConst36 = tanf((19947.8691f / fConst0));
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
		fConst47 = tanf((31665.2695f / fConst0));
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
		fConst58 = tanf((50265.4844f / fConst0));
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
		fConst69 = (6.28318548f / fConst0);
		fConst70 = (1.0f / fConst0);
		fConst71 = (0.25f * fConst0);
		fConst72 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst73 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst74 = (1413.71667f / fConst0);
		fConst75 = (2827.43335f / fConst0);
		fConst76 = (3.14159274f / fConst0);
		fConst77 = (((fConst59 + -0.782413065f) / fConst58) + 0.245291501f);
		fConst78 = (2.0f * (0.245291501f - fConst62));
		fConst79 = (fConst67 + 0.000433227193f);
		fConst80 = (((fConst59 + -0.51247865f) / fConst58) + 0.689621389f);
		fConst81 = (2.0f * (0.689621389f - fConst62));
		fConst82 = (fConst62 + 7.62173128f);
		fConst83 = (((fConst59 + -0.168404877f) / fConst58) + 1.06935835f);
		fConst84 = (2.0f * (1.06935835f - fConst62));
		fConst85 = (fConst62 + 53.5361519f);
		fConst86 = (((fConst48 + -0.782413065f) / fConst47) + 0.245291501f);
		fConst87 = (2.0f * (0.245291501f - fConst51));
		fConst88 = (fConst56 + 0.000433227193f);
		fConst89 = (((fConst48 + -0.51247865f) / fConst47) + 0.689621389f);
		fConst90 = (2.0f * (0.689621389f - fConst51));
		fConst91 = (fConst51 + 7.62173128f);
		fConst92 = (((fConst48 + -0.168404877f) / fConst47) + 1.06935835f);
		fConst93 = (2.0f * (1.06935835f - fConst51));
		fConst94 = (fConst51 + 53.5361519f);
		fConst95 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst96 = (2.0f * (0.245291501f - fConst40));
		fConst97 = (fConst45 + 0.000433227193f);
		fConst98 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst99 = (2.0f * (0.689621389f - fConst40));
		fConst100 = (fConst40 + 7.62173128f);
		fConst101 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst102 = (2.0f * (1.06935835f - fConst40));
		fConst103 = (fConst40 + 53.5361519f);
		fConst104 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst105 = (2.0f * (0.245291501f - fConst29));
		fConst106 = (fConst34 + 0.000433227193f);
		fConst107 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst108 = (2.0f * (0.689621389f - fConst29));
		fConst109 = (fConst29 + 7.62173128f);
		fConst110 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst111 = (2.0f * (1.06935835f - fConst29));
		fConst112 = (fConst29 + 53.5361519f);
		fConst113 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst114 = (2.0f * (0.245291501f - fConst18));
		fConst115 = (fConst23 + 0.000433227193f);
		fConst116 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst117 = (2.0f * (0.689621389f - fConst18));
		fConst118 = (fConst18 + 7.62173128f);
		fConst119 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst120 = (2.0f * (1.06935835f - fConst18));
		fConst121 = (fConst18 + 53.5361519f);
		fConst122 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst123 = (1.0f / fConst5);
		fConst124 = (2.0f * (4.07678175f - fConst123));
		fConst125 = (fConst12 + 0.000407678192f);
		fConst126 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst127 = (2.0f * (1.4500711f - fConst123));
		fConst128 = (fConst9 + 1.4500711f);
		fConst129 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst130 = (2.0f * (0.935140193f - fConst123));
		fConst131 = (fConst6 + 0.935140193f);
		fConst132 = (1.0f / (((fConst59 + 0.157482162f) / fConst58) + 0.935140193f));
		fConst133 = (50.0638084f / fConst61);
		fConst134 = (2.0f * (0.935140193f - fConst133));
		fConst135 = (1.0f / (((fConst59 + 0.743130445f) / fConst58) + 1.4500711f));
		fConst136 = (11.0520525f / fConst61);
		fConst137 = (2.0f * (1.4500711f - fConst136));
		fConst138 = (1.0f / (((fConst59 + 3.18972731f) / fConst58) + 4.07678175f));
		fConst139 = (0.00176617282f / fConst61);
		fConst140 = (2.0f * (0.000407678192f - fConst139));
		fConst141 = (((fConst59 + -3.18972731f) / fConst58) + 4.07678175f);
		fConst142 = (2.0f * (4.07678175f - fConst62));
		fConst143 = (fConst139 + 0.000407678192f);
		fConst144 = (((fConst59 + -0.743130445f) / fConst58) + 1.4500711f);
		fConst145 = (2.0f * (1.4500711f - fConst62));
		fConst146 = (fConst136 + 1.4500711f);
		fConst147 = (((fConst59 + -0.157482162f) / fConst58) + 0.935140193f);
		fConst148 = (2.0f * (0.935140193f - fConst62));
		fConst149 = (fConst133 + 0.935140193f);
		fConst150 = (1.0f / (((fConst48 + 0.157482162f) / fConst47) + 0.935140193f));
		fConst151 = (50.0638084f / fConst50);
		fConst152 = (2.0f * (0.935140193f - fConst151));
		fConst153 = (1.0f / (((fConst48 + 0.743130445f) / fConst47) + 1.4500711f));
		fConst154 = (11.0520525f / fConst50);
		fConst155 = (2.0f * (1.4500711f - fConst154));
		fConst156 = (1.0f / (((fConst48 + 3.18972731f) / fConst47) + 4.07678175f));
		fConst157 = (0.00176617282f / fConst50);
		fConst158 = (2.0f * (0.000407678192f - fConst157));
		fConst159 = (((fConst48 + -3.18972731f) / fConst47) + 4.07678175f);
		fConst160 = (2.0f * (4.07678175f - fConst51));
		fConst161 = (fConst157 + 0.000407678192f);
		fConst162 = (((fConst48 + -0.743130445f) / fConst47) + 1.4500711f);
		fConst163 = (2.0f * (1.4500711f - fConst51));
		fConst164 = (fConst154 + 1.4500711f);
		fConst165 = (((fConst48 + -0.157482162f) / fConst47) + 0.935140193f);
		fConst166 = (2.0f * (0.935140193f - fConst51));
		fConst167 = (fConst151 + 0.935140193f);
		fConst168 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst169 = (50.0638084f / fConst39);
		fConst170 = (2.0f * (0.935140193f - fConst169));
		fConst171 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst172 = (11.0520525f / fConst39);
		fConst173 = (2.0f * (1.4500711f - fConst172));
		fConst174 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst175 = (0.00176617282f / fConst39);
		fConst176 = (2.0f * (0.000407678192f - fConst175));
		fConst177 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst178 = (2.0f * (4.07678175f - fConst40));
		fConst179 = (fConst175 + 0.000407678192f);
		fConst180 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst181 = (2.0f * (1.4500711f - fConst40));
		fConst182 = (fConst172 + 1.4500711f);
		fConst183 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst184 = (2.0f * (0.935140193f - fConst40));
		fConst185 = (fConst169 + 0.935140193f);
		fConst186 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst187 = (50.0638084f / fConst28);
		fConst188 = (2.0f * (0.935140193f - fConst187));
		fConst189 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst190 = (11.0520525f / fConst28);
		fConst191 = (2.0f * (1.4500711f - fConst190));
		fConst192 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst193 = (0.00176617282f / fConst28);
		fConst194 = (2.0f * (0.000407678192f - fConst193));
		fConst195 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst196 = (2.0f * (4.07678175f - fConst29));
		fConst197 = (fConst193 + 0.000407678192f);
		fConst198 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst199 = (2.0f * (1.4500711f - fConst29));
		fConst200 = (fConst190 + 1.4500711f);
		fConst201 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst202 = (2.0f * (0.935140193f - fConst29));
		fConst203 = (fConst187 + 0.935140193f);
		fConst204 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst205 = (50.0638084f / fConst17);
		fConst206 = (2.0f * (0.935140193f - fConst205));
		fConst207 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst208 = (11.0520525f / fConst17);
		fConst209 = (2.0f * (1.4500711f - fConst208));
		fConst210 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst211 = (0.00176617282f / fConst17);
		fConst212 = (2.0f * (0.000407678192f - fConst211));
		fConst213 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst214 = (2.0f * (4.07678175f - fConst18));
		fConst215 = (fConst211 + 0.000407678192f);
		fConst216 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst217 = (2.0f * (1.4500711f - fConst18));
		fConst218 = (fConst208 + 1.4500711f);
		fConst219 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst220 = (2.0f * (0.935140193f - fConst18));
		fConst221 = (fConst205 + 0.935140193f);
		fConst222 = tanf((3141.59277f / fConst0));
		fConst223 = (1.0f / fConst222);
		fConst224 = (1.0f / (((fConst223 + 0.157482162f) / fConst222) + 0.935140193f));
		fConst225 = mydsp_faustpower2_f(fConst222);
		fConst226 = (50.0638084f / fConst225);
		fConst227 = (2.0f * (0.935140193f - fConst226));
		fConst228 = (1.0f / (((fConst223 + 0.743130445f) / fConst222) + 1.4500711f));
		fConst229 = (11.0520525f / fConst225);
		fConst230 = (2.0f * (1.4500711f - fConst229));
		fConst231 = (1.0f / (((fConst223 + 3.18972731f) / fConst222) + 4.07678175f));
		fConst232 = (0.00176617282f / fConst225);
		fConst233 = (2.0f * (0.000407678192f - fConst232));
		fConst234 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst235 = (2.0f * (53.5361519f - fConst123));
		fConst236 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst237 = (2.0f * (7.62173128f - fConst123));
		fConst238 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst239 = (9.99999975e-05f / fConst5);
		fConst240 = (2.0f * (0.000433227193f - fConst239));
		fConst241 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst242 = (2.0f * (0.245291501f - fConst123));
		fConst243 = (fConst239 + 0.000433227193f);
		fConst244 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst245 = (2.0f * (0.689621389f - fConst123));
		fConst246 = (fConst123 + 7.62173128f);
		fConst247 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst248 = (2.0f * (1.06935835f - fConst123));
		fConst249 = (fConst123 + 53.5361519f);
		fConst250 = (((fConst223 + -3.18972731f) / fConst222) + 4.07678175f);
		fConst251 = (1.0f / fConst225);
		fConst252 = (2.0f * (4.07678175f - fConst251));
		fConst253 = (fConst232 + 0.000407678192f);
		fConst254 = (((fConst223 + -0.743130445f) / fConst222) + 1.4500711f);
		fConst255 = (2.0f * (1.4500711f - fConst251));
		fConst256 = (fConst229 + 1.4500711f);
		fConst257 = (((fConst223 + -0.157482162f) / fConst222) + 0.935140193f);
		fConst258 = (2.0f * (0.935140193f - fConst251));
		fConst259 = (fConst226 + 0.935140193f);
		fConst260 = tanf((1979.07935f / fConst0));
		fConst261 = (1.0f / fConst260);
		fConst262 = (1.0f / (((fConst261 + 0.157482162f) / fConst260) + 0.935140193f));
		fConst263 = mydsp_faustpower2_f(fConst260);
		fConst264 = (50.0638084f / fConst263);
		fConst265 = (2.0f * (0.935140193f - fConst264));
		fConst266 = (1.0f / (((fConst261 + 0.743130445f) / fConst260) + 1.4500711f));
		fConst267 = (11.0520525f / fConst263);
		fConst268 = (2.0f * (1.4500711f - fConst267));
		fConst269 = (1.0f / (((fConst261 + 3.18972731f) / fConst260) + 4.07678175f));
		fConst270 = (0.00176617282f / fConst263);
		fConst271 = (2.0f * (0.000407678192f - fConst270));
		fConst272 = (1.0f / (((fConst223 + 0.168404877f) / fConst222) + 1.06935835f));
		fConst273 = (2.0f * (53.5361519f - fConst251));
		fConst274 = (1.0f / (((fConst223 + 0.51247865f) / fConst222) + 0.689621389f));
		fConst275 = (2.0f * (7.62173128f - fConst251));
		fConst276 = (1.0f / (((fConst223 + 0.782413065f) / fConst222) + 0.245291501f));
		fConst277 = (9.99999975e-05f / fConst225);
		fConst278 = (2.0f * (0.000433227193f - fConst277));
		fConst279 = (((fConst223 + -0.782413065f) / fConst222) + 0.245291501f);
		fConst280 = (2.0f * (0.245291501f - fConst251));
		fConst281 = (fConst277 + 0.000433227193f);
		fConst282 = (((fConst223 + -0.51247865f) / fConst222) + 0.689621389f);
		fConst283 = (2.0f * (0.689621389f - fConst251));
		fConst284 = (fConst251 + 7.62173128f);
		fConst285 = (((fConst223 + -0.168404877f) / fConst222) + 1.06935835f);
		fConst286 = (2.0f * (1.06935835f - fConst251));
		fConst287 = (fConst251 + 53.5361519f);
		fConst288 = (((fConst261 + -3.18972731f) / fConst260) + 4.07678175f);
		fConst289 = (1.0f / fConst263);
		fConst290 = (2.0f * (4.07678175f - fConst289));
		fConst291 = (fConst270 + 0.000407678192f);
		fConst292 = (((fConst261 + -0.743130445f) / fConst260) + 1.4500711f);
		fConst293 = (2.0f * (1.4500711f - fConst289));
		fConst294 = (fConst267 + 1.4500711f);
		fConst295 = (((fConst261 + -0.157482162f) / fConst260) + 0.935140193f);
		fConst296 = (2.0f * (0.935140193f - fConst289));
		fConst297 = (fConst264 + 0.935140193f);
		fConst298 = tanf((1246.74182f / fConst0));
		fConst299 = (1.0f / fConst298);
		fConst300 = (1.0f / (((fConst299 + 0.157482162f) / fConst298) + 0.935140193f));
		fConst301 = mydsp_faustpower2_f(fConst298);
		fConst302 = (50.0638084f / fConst301);
		fConst303 = (2.0f * (0.935140193f - fConst302));
		fConst304 = (1.0f / (((fConst299 + 0.743130445f) / fConst298) + 1.4500711f));
		fConst305 = (11.0520525f / fConst301);
		fConst306 = (2.0f * (1.4500711f - fConst305));
		fConst307 = (1.0f / (((fConst299 + 3.18972731f) / fConst298) + 4.07678175f));
		fConst308 = (0.00176617282f / fConst301);
		fConst309 = (2.0f * (0.000407678192f - fConst308));
		fConst310 = (1.0f / (((fConst261 + 0.168404877f) / fConst260) + 1.06935835f));
		fConst311 = (2.0f * (53.5361519f - fConst289));
		fConst312 = (1.0f / (((fConst261 + 0.51247865f) / fConst260) + 0.689621389f));
		fConst313 = (2.0f * (7.62173128f - fConst289));
		fConst314 = (1.0f / (((fConst261 + 0.782413065f) / fConst260) + 0.245291501f));
		fConst315 = (9.99999975e-05f / fConst263);
		fConst316 = (2.0f * (0.000433227193f - fConst315));
		fConst317 = (((fConst261 + -0.782413065f) / fConst260) + 0.245291501f);
		fConst318 = (2.0f * (0.245291501f - fConst289));
		fConst319 = (fConst315 + 0.000433227193f);
		fConst320 = (((fConst261 + -0.51247865f) / fConst260) + 0.689621389f);
		fConst321 = (2.0f * (0.689621389f - fConst289));
		fConst322 = (fConst289 + 7.62173128f);
		fConst323 = (((fConst261 + -0.168404877f) / fConst260) + 1.06935835f);
		fConst324 = (2.0f * (1.06935835f - fConst289));
		fConst325 = (fConst289 + 53.5361519f);
		fConst326 = (((fConst299 + -3.18972731f) / fConst298) + 4.07678175f);
		fConst327 = (1.0f / fConst301);
		fConst328 = (2.0f * (4.07678175f - fConst327));
		fConst329 = (fConst308 + 0.000407678192f);
		fConst330 = (((fConst299 + -0.743130445f) / fConst298) + 1.4500711f);
		fConst331 = (2.0f * (1.4500711f - fConst327));
		fConst332 = (fConst305 + 1.4500711f);
		fConst333 = (((fConst299 + -0.157482162f) / fConst298) + 0.935140193f);
		fConst334 = (2.0f * (0.935140193f - fConst327));
		fConst335 = (fConst302 + 0.935140193f);
		fConst336 = tanf((785.398193f / fConst0));
		fConst337 = (1.0f / fConst336);
		fConst338 = (1.0f / (((fConst337 + 0.157482162f) / fConst336) + 0.935140193f));
		fConst339 = mydsp_faustpower2_f(fConst336);
		fConst340 = (50.0638084f / fConst339);
		fConst341 = (2.0f * (0.935140193f - fConst340));
		fConst342 = (1.0f / (((fConst337 + 0.743130445f) / fConst336) + 1.4500711f));
		fConst343 = (11.0520525f / fConst339);
		fConst344 = (2.0f * (1.4500711f - fConst343));
		fConst345 = (1.0f / (((fConst337 + 3.18972731f) / fConst336) + 4.07678175f));
		fConst346 = (0.00176617282f / fConst339);
		fConst347 = (2.0f * (0.000407678192f - fConst346));
		fConst348 = (1.0f / (((fConst299 + 0.168404877f) / fConst298) + 1.06935835f));
		fConst349 = (2.0f * (53.5361519f - fConst327));
		fConst350 = (1.0f / (((fConst299 + 0.51247865f) / fConst298) + 0.689621389f));
		fConst351 = (2.0f * (7.62173128f - fConst327));
		fConst352 = (1.0f / (((fConst299 + 0.782413065f) / fConst298) + 0.245291501f));
		fConst353 = (9.99999975e-05f / fConst301);
		fConst354 = (2.0f * (0.000433227193f - fConst353));
		fConst355 = (((fConst299 + -0.782413065f) / fConst298) + 0.245291501f);
		fConst356 = (2.0f * (0.245291501f - fConst327));
		fConst357 = (fConst353 + 0.000433227193f);
		fConst358 = (((fConst299 + -0.51247865f) / fConst298) + 0.689621389f);
		fConst359 = (2.0f * (0.689621389f - fConst327));
		fConst360 = (fConst327 + 7.62173128f);
		fConst361 = (((fConst299 + -0.168404877f) / fConst298) + 1.06935835f);
		fConst362 = (2.0f * (1.06935835f - fConst327));
		fConst363 = (fConst327 + 53.5361519f);
		fConst364 = (((fConst337 + -3.18972731f) / fConst336) + 4.07678175f);
		fConst365 = (1.0f / fConst339);
		fConst366 = (2.0f * (4.07678175f - fConst365));
		fConst367 = (fConst346 + 0.000407678192f);
		fConst368 = (((fConst337 + -0.743130445f) / fConst336) + 1.4500711f);
		fConst369 = (2.0f * (1.4500711f - fConst365));
		fConst370 = (fConst343 + 1.4500711f);
		fConst371 = (((fConst337 + -0.157482162f) / fConst336) + 0.935140193f);
		fConst372 = (2.0f * (0.935140193f - fConst365));
		fConst373 = (fConst340 + 0.935140193f);
		fConst374 = tanf((494.769836f / fConst0));
		fConst375 = (1.0f / fConst374);
		fConst376 = (1.0f / (((fConst375 + 0.157482162f) / fConst374) + 0.935140193f));
		fConst377 = mydsp_faustpower2_f(fConst374);
		fConst378 = (50.0638084f / fConst377);
		fConst379 = (2.0f * (0.935140193f - fConst378));
		fConst380 = (1.0f / (((fConst375 + 0.743130445f) / fConst374) + 1.4500711f));
		fConst381 = (11.0520525f / fConst377);
		fConst382 = (2.0f * (1.4500711f - fConst381));
		fConst383 = (1.0f / (((fConst375 + 3.18972731f) / fConst374) + 4.07678175f));
		fConst384 = (0.00176617282f / fConst377);
		fConst385 = (2.0f * (0.000407678192f - fConst384));
		fConst386 = (1.0f / (((fConst337 + 0.168404877f) / fConst336) + 1.06935835f));
		fConst387 = (2.0f * (53.5361519f - fConst365));
		fConst388 = (1.0f / (((fConst337 + 0.51247865f) / fConst336) + 0.689621389f));
		fConst389 = (2.0f * (7.62173128f - fConst365));
		fConst390 = (1.0f / (((fConst337 + 0.782413065f) / fConst336) + 0.245291501f));
		fConst391 = (9.99999975e-05f / fConst339);
		fConst392 = (2.0f * (0.000433227193f - fConst391));
		fConst393 = (((fConst337 + -0.782413065f) / fConst336) + 0.245291501f);
		fConst394 = (2.0f * (0.245291501f - fConst365));
		fConst395 = (fConst391 + 0.000433227193f);
		fConst396 = (((fConst337 + -0.51247865f) / fConst336) + 0.689621389f);
		fConst397 = (2.0f * (0.689621389f - fConst365));
		fConst398 = (fConst365 + 7.62173128f);
		fConst399 = (((fConst337 + -0.168404877f) / fConst336) + 1.06935835f);
		fConst400 = (2.0f * (1.06935835f - fConst365));
		fConst401 = (fConst365 + 53.5361519f);
		fConst402 = (((fConst375 + -3.18972731f) / fConst374) + 4.07678175f);
		fConst403 = (1.0f / fConst377);
		fConst404 = (2.0f * (4.07678175f - fConst403));
		fConst405 = (fConst384 + 0.000407678192f);
		fConst406 = (((fConst375 + -0.743130445f) / fConst374) + 1.4500711f);
		fConst407 = (2.0f * (1.4500711f - fConst403));
		fConst408 = (fConst381 + 1.4500711f);
		fConst409 = (((fConst375 + -0.157482162f) / fConst374) + 0.935140193f);
		fConst410 = (2.0f * (0.935140193f - fConst403));
		fConst411 = (fConst378 + 0.935140193f);
		fConst412 = tanf((311.685455f / fConst0));
		fConst413 = (1.0f / fConst412);
		fConst414 = (1.0f / (((fConst413 + 0.157482162f) / fConst412) + 0.935140193f));
		fConst415 = mydsp_faustpower2_f(fConst412);
		fConst416 = (50.0638084f / fConst415);
		fConst417 = (2.0f * (0.935140193f - fConst416));
		fConst418 = (1.0f / (((fConst413 + 0.743130445f) / fConst412) + 1.4500711f));
		fConst419 = (11.0520525f / fConst415);
		fConst420 = (2.0f * (1.4500711f - fConst419));
		fConst421 = (1.0f / (((fConst413 + 3.18972731f) / fConst412) + 4.07678175f));
		fConst422 = (0.00176617282f / fConst415);
		fConst423 = (2.0f * (0.000407678192f - fConst422));
		fConst424 = (1.0f / (((fConst375 + 0.168404877f) / fConst374) + 1.06935835f));
		fConst425 = (2.0f * (53.5361519f - fConst403));
		fConst426 = (1.0f / (((fConst375 + 0.51247865f) / fConst374) + 0.689621389f));
		fConst427 = (2.0f * (7.62173128f - fConst403));
		fConst428 = (1.0f / (((fConst375 + 0.782413065f) / fConst374) + 0.245291501f));
		fConst429 = (9.99999975e-05f / fConst377);
		fConst430 = (2.0f * (0.000433227193f - fConst429));
		fConst431 = (((fConst375 + -0.782413065f) / fConst374) + 0.245291501f);
		fConst432 = (2.0f * (0.245291501f - fConst403));
		fConst433 = (fConst429 + 0.000433227193f);
		fConst434 = (((fConst375 + -0.51247865f) / fConst374) + 0.689621389f);
		fConst435 = (2.0f * (0.689621389f - fConst403));
		fConst436 = (fConst403 + 7.62173128f);
		fConst437 = (((fConst375 + -0.168404877f) / fConst374) + 1.06935835f);
		fConst438 = (2.0f * (1.06935835f - fConst403));
		fConst439 = (fConst403 + 53.5361519f);
		fConst440 = (((fConst413 + -3.18972731f) / fConst412) + 4.07678175f);
		fConst441 = (1.0f / fConst415);
		fConst442 = (2.0f * (4.07678175f - fConst441));
		fConst443 = (fConst422 + 0.000407678192f);
		fConst444 = (((fConst413 + -0.743130445f) / fConst412) + 1.4500711f);
		fConst445 = (2.0f * (1.4500711f - fConst441));
		fConst446 = (fConst419 + 1.4500711f);
		fConst447 = (((fConst413 + -0.157482162f) / fConst412) + 0.935140193f);
		fConst448 = (2.0f * (0.935140193f - fConst441));
		fConst449 = (fConst416 + 0.935140193f);
		fConst450 = tanf((196.349548f / fConst0));
		fConst451 = (1.0f / fConst450);
		fConst452 = (1.0f / (((fConst451 + 0.157482162f) / fConst450) + 0.935140193f));
		fConst453 = mydsp_faustpower2_f(fConst450);
		fConst454 = (50.0638084f / fConst453);
		fConst455 = (2.0f * (0.935140193f - fConst454));
		fConst456 = (1.0f / (((fConst451 + 0.743130445f) / fConst450) + 1.4500711f));
		fConst457 = (11.0520525f / fConst453);
		fConst458 = (2.0f * (1.4500711f - fConst457));
		fConst459 = (1.0f / (((fConst451 + 3.18972731f) / fConst450) + 4.07678175f));
		fConst460 = (0.00176617282f / fConst453);
		fConst461 = (2.0f * (0.000407678192f - fConst460));
		fConst462 = (1.0f / (((fConst413 + 0.168404877f) / fConst412) + 1.06935835f));
		fConst463 = (2.0f * (53.5361519f - fConst441));
		fConst464 = (1.0f / (((fConst413 + 0.51247865f) / fConst412) + 0.689621389f));
		fConst465 = (2.0f * (7.62173128f - fConst441));
		fConst466 = (1.0f / (((fConst413 + 0.782413065f) / fConst412) + 0.245291501f));
		fConst467 = (9.99999975e-05f / fConst415);
		fConst468 = (2.0f * (0.000433227193f - fConst467));
		fConst469 = (((fConst413 + -0.782413065f) / fConst412) + 0.245291501f);
		fConst470 = (2.0f * (0.245291501f - fConst441));
		fConst471 = (fConst467 + 0.000433227193f);
		fConst472 = (((fConst413 + -0.51247865f) / fConst412) + 0.689621389f);
		fConst473 = (2.0f * (0.689621389f - fConst441));
		fConst474 = (fConst441 + 7.62173128f);
		fConst475 = (((fConst413 + -0.168404877f) / fConst412) + 1.06935835f);
		fConst476 = (2.0f * (1.06935835f - fConst441));
		fConst477 = (fConst441 + 53.5361519f);
		fConst478 = (((fConst451 + -3.18972731f) / fConst450) + 4.07678175f);
		fConst479 = (1.0f / fConst453);
		fConst480 = (2.0f * (4.07678175f - fConst479));
		fConst481 = (fConst460 + 0.000407678192f);
		fConst482 = (((fConst451 + -0.743130445f) / fConst450) + 1.4500711f);
		fConst483 = (2.0f * (1.4500711f - fConst479));
		fConst484 = (fConst457 + 1.4500711f);
		fConst485 = (((fConst451 + -0.157482162f) / fConst450) + 0.935140193f);
		fConst486 = (2.0f * (0.935140193f - fConst479));
		fConst487 = (fConst454 + 0.935140193f);
		fConst488 = tanf((123.692459f / fConst0));
		fConst489 = (1.0f / fConst488);
		fConst490 = (1.0f / (((fConst489 + 0.157482162f) / fConst488) + 0.935140193f));
		fConst491 = mydsp_faustpower2_f(fConst488);
		fConst492 = (50.0638084f / fConst491);
		fConst493 = (2.0f * (0.935140193f - fConst492));
		fConst494 = (1.0f / (((fConst489 + 0.743130445f) / fConst488) + 1.4500711f));
		fConst495 = (11.0520525f / fConst491);
		fConst496 = (2.0f * (1.4500711f - fConst495));
		fConst497 = (1.0f / (((fConst489 + 3.18972731f) / fConst488) + 4.07678175f));
		fConst498 = (0.00176617282f / fConst491);
		fConst499 = (2.0f * (0.000407678192f - fConst498));
		fConst500 = (1.0f / (((fConst451 + 0.168404877f) / fConst450) + 1.06935835f));
		fConst501 = (2.0f * (53.5361519f - fConst479));
		fConst502 = (1.0f / (((fConst451 + 0.51247865f) / fConst450) + 0.689621389f));
		fConst503 = (2.0f * (7.62173128f - fConst479));
		fConst504 = (1.0f / (((fConst451 + 0.782413065f) / fConst450) + 0.245291501f));
		fConst505 = (9.99999975e-05f / fConst453);
		fConst506 = (2.0f * (0.000433227193f - fConst505));
		fConst507 = (((fConst451 + -0.782413065f) / fConst450) + 0.245291501f);
		fConst508 = (2.0f * (0.245291501f - fConst479));
		fConst509 = (fConst505 + 0.000433227193f);
		fConst510 = (((fConst451 + -0.51247865f) / fConst450) + 0.689621389f);
		fConst511 = (2.0f * (0.689621389f - fConst479));
		fConst512 = (fConst479 + 7.62173128f);
		fConst513 = (((fConst451 + -0.168404877f) / fConst450) + 1.06935835f);
		fConst514 = (2.0f * (1.06935835f - fConst479));
		fConst515 = (fConst479 + 53.5361519f);
		fConst516 = (((fConst489 + -3.18972731f) / fConst488) + 4.07678175f);
		fConst517 = (1.0f / fConst491);
		fConst518 = (2.0f * (4.07678175f - fConst517));
		fConst519 = (fConst498 + 0.000407678192f);
		fConst520 = (((fConst489 + -0.743130445f) / fConst488) + 1.4500711f);
		fConst521 = (2.0f * (1.4500711f - fConst517));
		fConst522 = (fConst495 + 1.4500711f);
		fConst523 = (((fConst489 + -0.157482162f) / fConst488) + 0.935140193f);
		fConst524 = (2.0f * (0.935140193f - fConst517));
		fConst525 = (fConst492 + 0.935140193f);
		fConst526 = (1.0f / (((fConst489 + 0.168404877f) / fConst488) + 1.06935835f));
		fConst527 = (2.0f * (53.5361519f - fConst517));
		fConst528 = (1.0f / (((fConst489 + 0.51247865f) / fConst488) + 0.689621389f));
		fConst529 = (2.0f * (7.62173128f - fConst517));
		fConst530 = (1.0f / (((fConst489 + 0.782413065f) / fConst488) + 0.245291501f));
		fConst531 = (9.99999975e-05f / fConst491);
		fConst532 = (2.0f * (0.000433227193f - fConst531));
		fConst533 = (((fConst489 + -0.782413065f) / fConst488) + 0.245291501f);
		fConst534 = (2.0f * (0.245291501f - fConst517));
		fConst535 = (fConst531 + 0.000433227193f);
		fConst536 = (((fConst489 + -0.51247865f) / fConst488) + 0.689621389f);
		fConst537 = (2.0f * (0.689621389f - fConst517));
		fConst538 = (fConst517 + 7.62173128f);
		fConst539 = (((fConst489 + -0.168404877f) / fConst488) + 1.06935835f);
		fConst540 = (2.0f * (1.06935835f - fConst517));
		fConst541 = (fConst517 + 53.5361519f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(5.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(200.0f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.80000000000000004f);
		fVslider0 = FAUSTFLOAT(-20.0f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(25.0f);
		fHslider6 = FAUSTFLOAT(0.90000000000000002f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec19[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec30[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec32[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec33[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec35[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec34[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec2[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec3[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec4[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec5[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec6[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec7[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec8[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec36[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec9[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec10[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec11[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec12[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec13[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec14[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec15[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec37[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec16[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec17[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec18[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec19[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fVec20[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec21[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			iRec38[l30] = 0;
			
		}
		for (int l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			fRec39[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec40[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec41[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec31[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec29[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec28[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec27[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec26[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec25[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec42[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec24[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec23[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec22[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec21[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec20[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec45[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec44[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec43[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec48[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec46[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec51[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec49[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec18[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec17[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec16[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec15[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec14[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec13[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec12[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec11[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec10[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec9[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec8[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec7[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec6[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec5[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec4[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec3[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec2[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec1[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec0[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec55[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec54[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec53[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec52[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec59[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec58[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec57[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec56[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec63[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec62[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec61[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec60[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec67[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec66[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec65[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec64[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec71[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec70[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec69[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fRec68[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec78[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec77[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec76[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec75[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec74[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec73[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec72[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec85[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec84[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec83[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec82[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec81[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec80[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec79[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec92[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec91[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec90[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec89[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec88[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec87[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fRec86[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec99[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec98[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec97[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec96[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec95[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec94[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec93[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec106[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec105[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec104[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec103[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec102[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec101[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec100[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec113[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec112[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec111[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec110[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec109[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec108[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec107[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec120[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec119[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec118[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec117[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec116[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec115[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			fRec114[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec127[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec126[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec125[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec124[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec123[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec122[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec121[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			fRec131[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec130[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			fRec129[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			fRec128[l151] = 0.0f;
			
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
		ui_interface->openVerticalBox("vcfWahLab");
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
		ui_interface->declare(&fCheckbox5, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", &fCheckbox5);
		ui_interface->declare(&fCheckbox6, "1", "");
		ui_interface->declare(&fCheckbox6, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox6);
		ui_interface->declare(&fCheckbox4, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", &fCheckbox4);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html");
		ui_interface->openHorizontalBox("CRYBABY");
		ui_interface->declare(&fCheckbox3, "0", "");
		ui_interface->declare(&fCheckbox3, "tooltip", "When this is checked, the wah   pedal has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox3);
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)");
		ui_interface->addHorizontalSlider("Wah parameter", &fHslider4, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Fourth-order wah effect made using moog_vcf");
		ui_interface->openHorizontalBox("WAH4");
		ui_interface->declare(&fCheckbox2, "0", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "When this is checked, the wah pedal has   no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox2);
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "tooltip", "wah resonance   frequency in Hz");
		ui_interface->addHorizontalSlider("Resonance Frequency", &fHslider3, 200.0f, 100.0f, 2000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
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
		ui_interface->declare(&fCheckbox7, "2", "");
		ui_interface->declare(&fCheckbox7, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fCheckbox7);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface->declare(&fHslider5, "unit", "PK");
		ui_interface->addHorizontalSlider("Corner Frequency", &fHslider5, 25.0f, 1.0f, 88.0f, 0.00999999978f);
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
		ui_interface->declare(0, "5", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph14, "0", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58e47330", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58e35870", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58e135c0", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58ded390", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "4", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58dcb0e0", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "5", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58da8e30", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "6", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58d86b80", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58d648d0", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "8", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58d42620", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "9", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58cc1300", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "10", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58d202c0", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "11", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58d0def0", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "12", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58cf7ba0", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "13", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58ce57d0", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "14", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffd58cd3400", &fVbargraph1, -50.0f, 10.0f);
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
		int iSlow6 = int(float(fCheckbox2));
		float fSlow7 = (0.00100000005f * float(fHslider3));
		int iSlow8 = int(float(fCheckbox3));
		float fSlow9 = float(fHslider4);
		float fSlow10 = (9.99999975e-05f * powf(4.0f, fSlow9));
		float fSlow11 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider0))));
		int iSlow12 = int(float(fCheckbox4));
		int iSlow13 = int(float(fCheckbox5));
		int iSlow14 = int((float(fEntry0) + -1.0f));
		int iSlow15 = (iSlow14 >= 2);
		int iSlow16 = (iSlow14 >= 1);
		float fSlow17 = expf((0.0f - (fConst70 / float(fVslider2))));
		float fSlow18 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fVslider1) + -49.0f))) * (1.0f - fSlow17)));
		int iSlow19 = (iSlow14 >= 3);
		float fSlow20 = ((0.00999999978f * float(fVslider3)) + 1.0f);
		float fSlow21 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		int iSlow22 = int(float(fCheckbox6));
		float fSlow23 = powf(2.0f, (2.29999995f * fSlow9));
		float fSlow24 = (1.0f - (fConst74 * (fSlow23 / powf(2.0f, ((2.0f * (1.0f - fSlow9)) + 1.0f)))));
		float fSlow25 = (0.00100000005f * (0.0f - (2.0f * (fSlow24 * cosf((fConst75 * fSlow23))))));
		float fSlow26 = (0.00100000005f * mydsp_faustpower2_f(fSlow24));
		float fSlow27 = (0.439999998f * powf(2.0f, (0.0833333358f * (float(fHslider5) + -49.0f))));
		float fSlow28 = float(fHslider6);
		float fSlow29 = (0.0f - (4.0f * max(0.0f, min(mydsp_faustpower4_f(fSlow28), 0.999998987f))));
		int iSlow30 = int(float(fCheckbox7));
		float fSlow31 = min(1.41419947f, (1.41421354f * fSlow28));
		float fSlow32 = (fSlow31 * (fSlow31 + 1.41421354f));
		float fSlow33 = (1.41421354f * fSlow31);
		float fSlow34 = (fSlow33 + 2.0f);
		float fSlow35 = (fSlow31 * (fSlow31 + -1.41421354f));
		float fSlow36 = (2.0f - fSlow33);
		float fSlow37 = mydsp_faustpower2_f((1.41419947f * fSlow28));
		float fSlow38 = (1.99997997f * fSlow28);
		float fSlow39 = (fSlow37 + fSlow38);
		float fSlow40 = (fSlow38 + 2.0f);
		float fSlow41 = (2.0f - fSlow38);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec19[0] = (fSlow4 + (0.999000013f * fRec19[1]));
			fRec30[0] = (fSlow7 + (0.999000013f * fRec30[1]));
			float fTemp0 = (fConst69 * fRec30[0]);
			float fTemp1 = (1.0f - fTemp0);
			fRec32[0] = (fSlow10 + (0.999000013f * fRec32[1]));
			fRec33[0] = (fSlow11 + (0.999000013f * fRec33[1]));
			fRec35[0] = (fSlow18 + (fSlow17 * fRec35[1]));
			float fTemp2 = max(20.0f, fabsf(fRec35[0]));
			fVec1[0] = fTemp2;
			float fTemp3 = (fRec34[1] + (fConst70 * fVec1[1]));
			fRec34[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = (2.0f * fRec34[0]);
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
			float fTemp12 = max(20.0f, fabsf((fSlow20 * fRec35[0])));
			fVec8[0] = fTemp12;
			float fTemp13 = (fRec36[1] + (fConst70 * fVec8[1]));
			fRec36[0] = (fTemp13 - floorf(fTemp13));
			float fTemp14 = (2.0f * fRec36[0]);
			float fTemp15 = (fTemp14 + -1.0f);
			float fTemp16 = mydsp_faustpower2_f(fTemp15);
			fVec9[0] = fTemp16;
			float fTemp17 = mydsp_faustpower3_f(fTemp15);
			fVec10[0] = (fTemp17 + (1.0f - fTemp14));
			float fTemp18 = ((fTemp17 + (1.0f - (fTemp14 + fVec10[1]))) / fTemp12);
			fVec11[0] = fTemp18;
			float fTemp19 = (fTemp16 * (fTemp16 + -2.0f));
			fVec12[0] = fTemp19;
			float fTemp20 = ((fTemp19 - fVec12[1]) / fTemp12);
			fVec13[0] = fTemp20;
			float fTemp21 = ((fTemp20 - fVec13[1]) / fTemp12);
			fVec14[0] = fTemp21;
			float fTemp22 = max(20.0f, fabsf((fSlow21 * fRec35[0])));
			fVec15[0] = fTemp22;
			float fTemp23 = (fRec37[1] + (fConst70 * fVec15[1]));
			fRec37[0] = (fTemp23 - floorf(fTemp23));
			float fTemp24 = (2.0f * fRec37[0]);
			float fTemp25 = (fTemp24 + -1.0f);
			float fTemp26 = mydsp_faustpower2_f(fTemp25);
			fVec16[0] = fTemp26;
			float fTemp27 = mydsp_faustpower3_f(fTemp25);
			fVec17[0] = (fTemp27 + (1.0f - fTemp24));
			float fTemp28 = ((fTemp27 + (1.0f - (fTemp24 + fVec17[1]))) / fTemp22);
			fVec18[0] = fTemp28;
			float fTemp29 = (fTemp26 * (fTemp26 + -2.0f));
			fVec19[0] = fTemp29;
			float fTemp30 = ((fTemp29 - fVec19[1]) / fTemp22);
			fVec20[0] = fTemp30;
			float fTemp31 = ((fTemp30 - fVec20[1]) / fTemp22);
			fVec21[0] = fTemp31;
			iRec38[0] = ((1103515245 * iRec38[1]) + 12345);
			float fTemp32 = (4.65661287e-10f * float(iRec38[0]));
			fRec39[0] = (((0.522189379f * fRec39[3]) + (fTemp32 + (2.49495602f * fRec39[1]))) - (2.0172658f * fRec39[2]));
			float fTemp33 = (fRec33[0] * (iSlow12?float(input0[i]):(iSlow13?(iSlow22?(((0.0499220341f * fRec39[0]) + (0.0506126992f * fRec39[2])) - ((0.0959935337f * fRec39[1]) + (0.00440878607f * fRec39[3]))):fTemp32):(0.333333343f * (fRec33[0] * (((iSlow15?(iSlow19?(fConst73 * ((float(iVec0[3]) * (fTemp11 - fVec7[1])) / fTemp2)):(fConst72 * ((float(iVec0[2]) * (fTemp8 - fVec4[1])) / fTemp2))):(iSlow16?(fConst71 * ((float(iVec0[1]) * (fTemp6 - fVec2[1])) / fTemp2)):fTemp5)) + (iSlow15?(iSlow19?(fConst73 * ((float(iVec0[3]) * (fTemp21 - fVec14[1])) / fTemp12)):(fConst72 * ((float(iVec0[2]) * (fTemp18 - fVec11[1])) / fTemp12))):(iSlow16?(fConst71 * ((float(iVec0[1]) * (fTemp16 - fVec9[1])) / fTemp12)):fTemp15))) + (iSlow15?(iSlow19?(fConst73 * ((float(iVec0[3]) * (fTemp31 - fVec21[1])) / fTemp22)):(fConst72 * ((float(iVec0[2]) * (fTemp28 - fVec18[1])) / fTemp22))):(iSlow16?(fConst71 * ((float(iVec0[1]) * (fTemp26 - fVec16[1])) / fTemp22)):fTemp25))))))));
			fRec40[0] = (fSlow25 + (0.999000013f * fRec40[1]));
			fRec41[0] = (fSlow26 + (0.999000013f * fRec41[1]));
			fRec31[0] = ((fRec32[0] * (iSlow8?0.0f:fTemp33)) - ((fRec40[0] * fRec31[1]) + (fRec41[0] * fRec31[2])));
			float fTemp34 = (iSlow8?fTemp33:(fRec31[0] - fRec31[1]));
			fRec29[0] = (((fTemp1 * fRec29[1]) + (iSlow6?0.0f:fTemp34)) - (3.20000005f * fRec25[1]));
			fRec28[0] = (fRec29[0] + (fTemp1 * fRec28[1]));
			fRec27[0] = (fRec28[0] + (fTemp1 * fRec27[1]));
			fRec26[0] = (fRec27[0] + (fRec26[1] * fTemp1));
			fRec25[0] = (fRec26[0] * powf(fTemp0, 4.0f));
			float fTemp35 = (iSlow6?fTemp34:(4.0f * fRec25[0]));
			float fTemp36 = (iSlow3?0.0f:fTemp35);
			fRec42[0] = (fSlow27 + (0.999000013f * fRec42[1]));
			float fTemp37 = (fConst69 * fRec42[0]);
			float fTemp38 = (1.0f - fTemp37);
			fRec24[0] = (fTemp36 + ((fTemp38 * fRec24[1]) + (fSlow29 * fRec20[1])));
			fRec23[0] = (fRec24[0] + (fTemp38 * fRec23[1]));
			fRec22[0] = (fRec23[0] + (fTemp38 * fRec22[1]));
			fRec21[0] = (fRec22[0] + (fRec21[1] * fTemp38));
			fRec20[0] = (fRec21[0] * powf(fTemp37, 4.0f));
			fRec45[0] = (fSlow27 + (0.999000013f * fRec45[1]));
			float fTemp39 = tanf((fConst76 * max(20.0f, min(10000.0f, fRec45[0]))));
			float fTemp40 = (1.0f / fTemp39);
			float fTemp41 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp39)));
			float fTemp42 = (fSlow32 + (((fSlow34 + fTemp40) / fTemp39) + 1.0f));
			fRec44[0] = (fTemp36 - (((fRec44[2] * (fSlow32 + (((fTemp40 - fSlow34) / fTemp39) + 1.0f))) + (2.0f * (fRec44[1] * (fSlow32 + fTemp41)))) / fTemp42));
			float fTemp43 = (fSlow35 + (((fSlow36 + fTemp40) / fTemp39) + 1.0f));
			fRec43[0] = (((fRec44[2] + (fRec44[0] + (2.0f * fRec44[1]))) / fTemp42) - (((fRec43[2] * (fSlow35 + (((fTemp40 - fSlow36) / fTemp39) + 1.0f))) + (2.0f * (fRec43[1] * (fSlow35 + fTemp41)))) / fTemp43));
			float fTemp44 = tanf((fConst76 * max(fRec45[0], 20.0f)));
			float fTemp45 = (1.0f / fTemp44);
			float fTemp46 = (fSlow39 + (((fSlow40 + fTemp45) / fTemp44) + 1.0f));
			float fTemp47 = ((fSlow39 + (1.0f - ((fSlow40 - fTemp45) / fTemp44))) / fTemp46);
			float fTemp48 = max(-0.999899983f, min(0.999899983f, fTemp47));
			float fTemp49 = (1.0f - mydsp_faustpower2_f(fTemp48));
			float fTemp50 = sqrtf(max(0.0f, fTemp49));
			float fTemp51 = ((fRec46[1] * (0.0f - fTemp48)) + (fTemp36 * fTemp50));
			float fTemp52 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp44)));
			float fTemp53 = (fSlow39 + fTemp52);
			float fTemp54 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp53 / (fTemp46 * (fTemp47 + 1.0f))))));
			float fTemp55 = (1.0f - mydsp_faustpower2_f(fTemp54));
			float fTemp56 = sqrtf(max(0.0f, fTemp55));
			fRec48[0] = ((fRec48[1] * (0.0f - fTemp54)) + (fTemp51 * fTemp56));
			fRec46[0] = ((fTemp51 * fTemp54) + (fRec48[1] * fTemp56));
			float fRec47 = fRec48[0];
			float fTemp57 = (1.0f - (fTemp53 / fTemp46));
			float fTemp58 = sqrtf(fTemp49);
			float fTemp59 = ((((fTemp36 * fTemp48) + (fRec46[1] * fTemp50)) + (2.0f * ((fRec46[0] * fTemp57) / fTemp58))) + ((fRec47 * ((1.0f - fTemp47) - (2.0f * (fTemp54 * fTemp57)))) / (fTemp58 * sqrtf(fTemp55))));
			float fTemp60 = (fSlow37 + ((((fSlow41 + fTemp45) / fTemp44) + 1.0f) - fSlow38));
			float fTemp61 = ((fSlow37 + ((((fTemp45 - fSlow41) / fTemp44) + 1.0f) - fSlow38)) / fTemp60);
			float fTemp62 = max(-0.999899983f, min(0.999899983f, fTemp61));
			float fTemp63 = (1.0f - mydsp_faustpower2_f(fTemp62));
			float fTemp64 = sqrtf(max(0.0f, fTemp63));
			float fTemp65 = ((fRec49[1] * (0.0f - fTemp62)) + ((fTemp59 * fTemp64) / fTemp46));
			float fTemp66 = (fSlow37 + (fTemp52 - fSlow38));
			float fTemp67 = max(-0.999899983f, min(0.999899983f, (2.0f * (fTemp66 / (fTemp60 * (fTemp61 + 1.0f))))));
			float fTemp68 = (1.0f - mydsp_faustpower2_f(fTemp67));
			float fTemp69 = sqrtf(max(0.0f, fTemp68));
			fRec51[0] = ((fRec51[1] * (0.0f - fTemp67)) + (fTemp65 * fTemp69));
			fRec49[0] = ((fTemp65 * fTemp67) + (fRec51[1] * fTemp69));
			float fRec50 = fRec51[0];
			float fTemp70 = (1.0f - (fTemp66 / fTemp60));
			float fTemp71 = sqrtf(fTemp63);
			float fTemp72 = (iSlow3?fTemp35:(fRec19[0] * (iSlow5?(iSlow30?((((((fTemp59 * fTemp62) / fTemp46) + (fRec49[1] * fTemp64)) + (2.0f * ((fRec49[0] * fTemp70) / fTemp71))) + ((fRec50 * ((1.0f - fTemp61) - (2.0f * (fTemp67 * fTemp70)))) / (fTemp71 * sqrtf(fTemp68)))) / fTemp60):((fRec43[2] + (fRec43[0] + (2.0f * fRec43[1]))) / fTemp43)):fRec20[0])));
			fRec18[0] = (fTemp72 - (fConst66 * ((fConst77 * fRec18[2]) + (fConst78 * fRec18[1]))));
			fRec17[0] = ((fConst66 * (((fConst68 * fRec18[1]) + (fConst79 * fRec18[0])) + (fConst79 * fRec18[2]))) - (fConst64 * ((fConst80 * fRec17[2]) + (fConst81 * fRec17[1]))));
			fRec16[0] = ((fConst64 * (((fConst65 * fRec17[1]) + (fConst82 * fRec17[0])) + (fConst82 * fRec17[2]))) - (fConst60 * ((fConst83 * fRec16[2]) + (fConst84 * fRec16[1]))));
			float fTemp73 = (fConst60 * (((fConst63 * fRec16[1]) + (fConst85 * fRec16[0])) + (fConst85 * fRec16[2])));
			fRec15[0] = (fTemp73 - (fConst55 * ((fConst86 * fRec15[2]) + (fConst87 * fRec15[1]))));
			fRec14[0] = ((fConst55 * (((fConst57 * fRec15[1]) + (fConst88 * fRec15[0])) + (fConst88 * fRec15[2]))) - (fConst53 * ((fConst89 * fRec14[2]) + (fConst90 * fRec14[1]))));
			fRec13[0] = ((fConst53 * (((fConst54 * fRec14[1]) + (fConst91 * fRec14[0])) + (fConst91 * fRec14[2]))) - (fConst49 * ((fConst92 * fRec13[2]) + (fConst93 * fRec13[1]))));
			float fTemp74 = (fConst49 * (((fConst52 * fRec13[1]) + (fConst94 * fRec13[0])) + (fConst94 * fRec13[2])));
			fRec12[0] = (fTemp74 - (fConst44 * ((fConst95 * fRec12[2]) + (fConst96 * fRec12[1]))));
			fRec11[0] = ((fConst44 * (((fConst46 * fRec12[1]) + (fConst97 * fRec12[0])) + (fConst97 * fRec12[2]))) - (fConst42 * ((fConst98 * fRec11[2]) + (fConst99 * fRec11[1]))));
			fRec10[0] = ((fConst42 * (((fConst43 * fRec11[1]) + (fConst100 * fRec11[0])) + (fConst100 * fRec11[2]))) - (fConst38 * ((fConst101 * fRec10[2]) + (fConst102 * fRec10[1]))));
			float fTemp75 = (fConst38 * (((fConst41 * fRec10[1]) + (fConst103 * fRec10[0])) + (fConst103 * fRec10[2])));
			fRec9[0] = (fTemp75 - (fConst33 * ((fConst104 * fRec9[2]) + (fConst105 * fRec9[1]))));
			fRec8[0] = ((fConst33 * (((fConst35 * fRec9[1]) + (fConst106 * fRec9[0])) + (fConst106 * fRec9[2]))) - (fConst31 * ((fConst107 * fRec8[2]) + (fConst108 * fRec8[1]))));
			fRec7[0] = ((fConst31 * (((fConst32 * fRec8[1]) + (fConst109 * fRec8[0])) + (fConst109 * fRec8[2]))) - (fConst27 * ((fConst110 * fRec7[2]) + (fConst111 * fRec7[1]))));
			float fTemp76 = (fConst27 * (((fConst30 * fRec7[1]) + (fConst112 * fRec7[0])) + (fConst112 * fRec7[2])));
			fRec6[0] = (fTemp76 - (fConst22 * ((fConst113 * fRec6[2]) + (fConst114 * fRec6[1]))));
			fRec5[0] = ((fConst22 * (((fConst24 * fRec6[1]) + (fConst115 * fRec6[0])) + (fConst115 * fRec6[2]))) - (fConst20 * ((fConst116 * fRec5[2]) + (fConst117 * fRec5[1]))));
			fRec4[0] = ((fConst20 * (((fConst21 * fRec5[1]) + (fConst118 * fRec5[0])) + (fConst118 * fRec5[2]))) - (fConst16 * ((fConst119 * fRec4[2]) + (fConst120 * fRec4[1]))));
			float fTemp77 = (fConst16 * (((fConst19 * fRec4[1]) + (fConst121 * fRec4[0])) + (fConst121 * fRec4[2])));
			fRec3[0] = (fTemp77 - (fConst11 * ((fConst122 * fRec3[2]) + (fConst124 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst125 * fRec3[0])) + (fConst125 * fRec3[2]))) - (fConst8 * ((fConst126 * fRec2[2]) + (fConst127 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst128 * fRec2[0])) + (fConst128 * fRec2[2]))) - (fConst4 * ((fConst129 * fRec1[2]) + (fConst130 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * fabsf((fConst4 * (((fConst7 * fRec1[1]) + (fConst131 * fRec1[0])) + (fConst131 * fRec1[2]))))));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec0[0])))));
			fRec55[0] = (fTemp72 - (fConst138 * ((fConst141 * fRec55[2]) + (fConst142 * fRec55[1]))));
			fRec54[0] = ((fConst138 * (((fConst140 * fRec55[1]) + (fConst143 * fRec55[0])) + (fConst143 * fRec55[2]))) - (fConst135 * ((fConst144 * fRec54[2]) + (fConst145 * fRec54[1]))));
			fRec53[0] = ((fConst135 * (((fConst137 * fRec54[1]) + (fConst146 * fRec54[0])) + (fConst146 * fRec54[2]))) - (fConst132 * ((fConst147 * fRec53[2]) + (fConst148 * fRec53[1]))));
			fRec52[0] = ((fSlow1 * fRec52[1]) + (fSlow2 * fabsf((fConst132 * (((fConst134 * fRec53[1]) + (fConst149 * fRec53[0])) + (fConst149 * fRec53[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec52[0])))));
			fRec59[0] = (fTemp73 - (fConst156 * ((fConst159 * fRec59[2]) + (fConst160 * fRec59[1]))));
			fRec58[0] = ((fConst156 * (((fConst158 * fRec59[1]) + (fConst161 * fRec59[0])) + (fConst161 * fRec59[2]))) - (fConst153 * ((fConst162 * fRec58[2]) + (fConst163 * fRec58[1]))));
			fRec57[0] = ((fConst153 * (((fConst155 * fRec58[1]) + (fConst164 * fRec58[0])) + (fConst164 * fRec58[2]))) - (fConst150 * ((fConst165 * fRec57[2]) + (fConst166 * fRec57[1]))));
			fRec56[0] = ((fSlow1 * fRec56[1]) + (fSlow2 * fabsf((fConst150 * (((fConst152 * fRec57[1]) + (fConst167 * fRec57[0])) + (fConst167 * fRec57[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec56[0])))));
			fRec63[0] = (fTemp74 - (fConst174 * ((fConst177 * fRec63[2]) + (fConst178 * fRec63[1]))));
			fRec62[0] = ((fConst174 * (((fConst176 * fRec63[1]) + (fConst179 * fRec63[0])) + (fConst179 * fRec63[2]))) - (fConst171 * ((fConst180 * fRec62[2]) + (fConst181 * fRec62[1]))));
			fRec61[0] = ((fConst171 * (((fConst173 * fRec62[1]) + (fConst182 * fRec62[0])) + (fConst182 * fRec62[2]))) - (fConst168 * ((fConst183 * fRec61[2]) + (fConst184 * fRec61[1]))));
			fRec60[0] = ((fSlow1 * fRec60[1]) + (fSlow2 * fabsf((fConst168 * (((fConst170 * fRec61[1]) + (fConst185 * fRec61[0])) + (fConst185 * fRec61[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec60[0])))));
			fRec67[0] = (fTemp75 - (fConst192 * ((fConst195 * fRec67[2]) + (fConst196 * fRec67[1]))));
			fRec66[0] = ((fConst192 * (((fConst194 * fRec67[1]) + (fConst197 * fRec67[0])) + (fConst197 * fRec67[2]))) - (fConst189 * ((fConst198 * fRec66[2]) + (fConst199 * fRec66[1]))));
			fRec65[0] = ((fConst189 * (((fConst191 * fRec66[1]) + (fConst200 * fRec66[0])) + (fConst200 * fRec66[2]))) - (fConst186 * ((fConst201 * fRec65[2]) + (fConst202 * fRec65[1]))));
			fRec64[0] = ((fSlow1 * fRec64[1]) + (fSlow2 * fabsf((fConst186 * (((fConst188 * fRec65[1]) + (fConst203 * fRec65[0])) + (fConst203 * fRec65[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec64[0])))));
			fRec71[0] = (fTemp76 - (fConst210 * ((fConst213 * fRec71[2]) + (fConst214 * fRec71[1]))));
			fRec70[0] = ((fConst210 * (((fConst212 * fRec71[1]) + (fConst215 * fRec71[0])) + (fConst215 * fRec71[2]))) - (fConst207 * ((fConst216 * fRec70[2]) + (fConst217 * fRec70[1]))));
			fRec69[0] = ((fConst207 * (((fConst209 * fRec70[1]) + (fConst218 * fRec70[0])) + (fConst218 * fRec70[2]))) - (fConst204 * ((fConst219 * fRec69[2]) + (fConst220 * fRec69[1]))));
			fRec68[0] = ((fSlow1 * fRec68[1]) + (fSlow2 * fabsf((fConst204 * (((fConst206 * fRec69[1]) + (fConst221 * fRec69[0])) + (fConst221 * fRec69[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec68[0])))));
			fRec78[0] = (fTemp77 - (fConst238 * ((fConst241 * fRec78[2]) + (fConst242 * fRec78[1]))));
			fRec77[0] = ((fConst238 * (((fConst240 * fRec78[1]) + (fConst243 * fRec78[0])) + (fConst243 * fRec78[2]))) - (fConst236 * ((fConst244 * fRec77[2]) + (fConst245 * fRec77[1]))));
			fRec76[0] = ((fConst236 * (((fConst237 * fRec77[1]) + (fConst246 * fRec77[0])) + (fConst246 * fRec77[2]))) - (fConst234 * ((fConst247 * fRec76[2]) + (fConst248 * fRec76[1]))));
			float fTemp78 = (fConst234 * (((fConst235 * fRec76[1]) + (fConst249 * fRec76[0])) + (fConst249 * fRec76[2])));
			fRec75[0] = (fTemp78 - (fConst231 * ((fConst250 * fRec75[2]) + (fConst252 * fRec75[1]))));
			fRec74[0] = ((fConst231 * (((fConst233 * fRec75[1]) + (fConst253 * fRec75[0])) + (fConst253 * fRec75[2]))) - (fConst228 * ((fConst254 * fRec74[2]) + (fConst255 * fRec74[1]))));
			fRec73[0] = ((fConst228 * (((fConst230 * fRec74[1]) + (fConst256 * fRec74[0])) + (fConst256 * fRec74[2]))) - (fConst224 * ((fConst257 * fRec73[2]) + (fConst258 * fRec73[1]))));
			fRec72[0] = ((fSlow1 * fRec72[1]) + (fSlow2 * fabsf((fConst224 * (((fConst227 * fRec73[1]) + (fConst259 * fRec73[0])) + (fConst259 * fRec73[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec72[0])))));
			fRec85[0] = (fTemp78 - (fConst276 * ((fConst279 * fRec85[2]) + (fConst280 * fRec85[1]))));
			fRec84[0] = ((fConst276 * (((fConst278 * fRec85[1]) + (fConst281 * fRec85[0])) + (fConst281 * fRec85[2]))) - (fConst274 * ((fConst282 * fRec84[2]) + (fConst283 * fRec84[1]))));
			fRec83[0] = ((fConst274 * (((fConst275 * fRec84[1]) + (fConst284 * fRec84[0])) + (fConst284 * fRec84[2]))) - (fConst272 * ((fConst285 * fRec83[2]) + (fConst286 * fRec83[1]))));
			float fTemp79 = (fConst272 * (((fConst273 * fRec83[1]) + (fConst287 * fRec83[0])) + (fConst287 * fRec83[2])));
			fRec82[0] = (fTemp79 - (fConst269 * ((fConst288 * fRec82[2]) + (fConst290 * fRec82[1]))));
			fRec81[0] = ((fConst269 * (((fConst271 * fRec82[1]) + (fConst291 * fRec82[0])) + (fConst291 * fRec82[2]))) - (fConst266 * ((fConst292 * fRec81[2]) + (fConst293 * fRec81[1]))));
			fRec80[0] = ((fConst266 * (((fConst268 * fRec81[1]) + (fConst294 * fRec81[0])) + (fConst294 * fRec81[2]))) - (fConst262 * ((fConst295 * fRec80[2]) + (fConst296 * fRec80[1]))));
			fRec79[0] = ((fSlow1 * fRec79[1]) + (fSlow2 * fabsf((fConst262 * (((fConst265 * fRec80[1]) + (fConst297 * fRec80[0])) + (fConst297 * fRec80[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec79[0])))));
			fRec92[0] = (fTemp79 - (fConst314 * ((fConst317 * fRec92[2]) + (fConst318 * fRec92[1]))));
			fRec91[0] = ((fConst314 * (((fConst316 * fRec92[1]) + (fConst319 * fRec92[0])) + (fConst319 * fRec92[2]))) - (fConst312 * ((fConst320 * fRec91[2]) + (fConst321 * fRec91[1]))));
			fRec90[0] = ((fConst312 * (((fConst313 * fRec91[1]) + (fConst322 * fRec91[0])) + (fConst322 * fRec91[2]))) - (fConst310 * ((fConst323 * fRec90[2]) + (fConst324 * fRec90[1]))));
			float fTemp80 = (fConst310 * (((fConst311 * fRec90[1]) + (fConst325 * fRec90[0])) + (fConst325 * fRec90[2])));
			fRec89[0] = (fTemp80 - (fConst307 * ((fConst326 * fRec89[2]) + (fConst328 * fRec89[1]))));
			fRec88[0] = ((fConst307 * (((fConst309 * fRec89[1]) + (fConst329 * fRec89[0])) + (fConst329 * fRec89[2]))) - (fConst304 * ((fConst330 * fRec88[2]) + (fConst331 * fRec88[1]))));
			fRec87[0] = ((fConst304 * (((fConst306 * fRec88[1]) + (fConst332 * fRec88[0])) + (fConst332 * fRec88[2]))) - (fConst300 * ((fConst333 * fRec87[2]) + (fConst334 * fRec87[1]))));
			fRec86[0] = ((fSlow1 * fRec86[1]) + (fSlow2 * fabsf((fConst300 * (((fConst303 * fRec87[1]) + (fConst335 * fRec87[0])) + (fConst335 * fRec87[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec86[0])))));
			fRec99[0] = (fTemp80 - (fConst352 * ((fConst355 * fRec99[2]) + (fConst356 * fRec99[1]))));
			fRec98[0] = ((fConst352 * (((fConst354 * fRec99[1]) + (fConst357 * fRec99[0])) + (fConst357 * fRec99[2]))) - (fConst350 * ((fConst358 * fRec98[2]) + (fConst359 * fRec98[1]))));
			fRec97[0] = ((fConst350 * (((fConst351 * fRec98[1]) + (fConst360 * fRec98[0])) + (fConst360 * fRec98[2]))) - (fConst348 * ((fConst361 * fRec97[2]) + (fConst362 * fRec97[1]))));
			float fTemp81 = (fConst348 * (((fConst349 * fRec97[1]) + (fConst363 * fRec97[0])) + (fConst363 * fRec97[2])));
			fRec96[0] = (fTemp81 - (fConst345 * ((fConst364 * fRec96[2]) + (fConst366 * fRec96[1]))));
			fRec95[0] = ((fConst345 * (((fConst347 * fRec96[1]) + (fConst367 * fRec96[0])) + (fConst367 * fRec96[2]))) - (fConst342 * ((fConst368 * fRec95[2]) + (fConst369 * fRec95[1]))));
			fRec94[0] = ((fConst342 * (((fConst344 * fRec95[1]) + (fConst370 * fRec95[0])) + (fConst370 * fRec95[2]))) - (fConst338 * ((fConst371 * fRec94[2]) + (fConst372 * fRec94[1]))));
			fRec93[0] = ((fSlow1 * fRec93[1]) + (fSlow2 * fabsf((fConst338 * (((fConst341 * fRec94[1]) + (fConst373 * fRec94[0])) + (fConst373 * fRec94[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec93[0])))));
			fRec106[0] = (fTemp81 - (fConst390 * ((fConst393 * fRec106[2]) + (fConst394 * fRec106[1]))));
			fRec105[0] = ((fConst390 * (((fConst392 * fRec106[1]) + (fConst395 * fRec106[0])) + (fConst395 * fRec106[2]))) - (fConst388 * ((fConst396 * fRec105[2]) + (fConst397 * fRec105[1]))));
			fRec104[0] = ((fConst388 * (((fConst389 * fRec105[1]) + (fConst398 * fRec105[0])) + (fConst398 * fRec105[2]))) - (fConst386 * ((fConst399 * fRec104[2]) + (fConst400 * fRec104[1]))));
			float fTemp82 = (fConst386 * (((fConst387 * fRec104[1]) + (fConst401 * fRec104[0])) + (fConst401 * fRec104[2])));
			fRec103[0] = (fTemp82 - (fConst383 * ((fConst402 * fRec103[2]) + (fConst404 * fRec103[1]))));
			fRec102[0] = ((fConst383 * (((fConst385 * fRec103[1]) + (fConst405 * fRec103[0])) + (fConst405 * fRec103[2]))) - (fConst380 * ((fConst406 * fRec102[2]) + (fConst407 * fRec102[1]))));
			fRec101[0] = ((fConst380 * (((fConst382 * fRec102[1]) + (fConst408 * fRec102[0])) + (fConst408 * fRec102[2]))) - (fConst376 * ((fConst409 * fRec101[2]) + (fConst410 * fRec101[1]))));
			fRec100[0] = ((fSlow1 * fRec100[1]) + (fSlow2 * fabsf((fConst376 * (((fConst379 * fRec101[1]) + (fConst411 * fRec101[0])) + (fConst411 * fRec101[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec100[0])))));
			fRec113[0] = (fTemp82 - (fConst428 * ((fConst431 * fRec113[2]) + (fConst432 * fRec113[1]))));
			fRec112[0] = ((fConst428 * (((fConst430 * fRec113[1]) + (fConst433 * fRec113[0])) + (fConst433 * fRec113[2]))) - (fConst426 * ((fConst434 * fRec112[2]) + (fConst435 * fRec112[1]))));
			fRec111[0] = ((fConst426 * (((fConst427 * fRec112[1]) + (fConst436 * fRec112[0])) + (fConst436 * fRec112[2]))) - (fConst424 * ((fConst437 * fRec111[2]) + (fConst438 * fRec111[1]))));
			float fTemp83 = (fConst424 * (((fConst425 * fRec111[1]) + (fConst439 * fRec111[0])) + (fConst439 * fRec111[2])));
			fRec110[0] = (fTemp83 - (fConst421 * ((fConst440 * fRec110[2]) + (fConst442 * fRec110[1]))));
			fRec109[0] = ((fConst421 * (((fConst423 * fRec110[1]) + (fConst443 * fRec110[0])) + (fConst443 * fRec110[2]))) - (fConst418 * ((fConst444 * fRec109[2]) + (fConst445 * fRec109[1]))));
			fRec108[0] = ((fConst418 * (((fConst420 * fRec109[1]) + (fConst446 * fRec109[0])) + (fConst446 * fRec109[2]))) - (fConst414 * ((fConst447 * fRec108[2]) + (fConst448 * fRec108[1]))));
			fRec107[0] = ((fSlow1 * fRec107[1]) + (fSlow2 * fabsf((fConst414 * (((fConst417 * fRec108[1]) + (fConst449 * fRec108[0])) + (fConst449 * fRec108[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec107[0])))));
			fRec120[0] = (fTemp83 - (fConst466 * ((fConst469 * fRec120[2]) + (fConst470 * fRec120[1]))));
			fRec119[0] = ((fConst466 * (((fConst468 * fRec120[1]) + (fConst471 * fRec120[0])) + (fConst471 * fRec120[2]))) - (fConst464 * ((fConst472 * fRec119[2]) + (fConst473 * fRec119[1]))));
			fRec118[0] = ((fConst464 * (((fConst465 * fRec119[1]) + (fConst474 * fRec119[0])) + (fConst474 * fRec119[2]))) - (fConst462 * ((fConst475 * fRec118[2]) + (fConst476 * fRec118[1]))));
			float fTemp84 = (fConst462 * (((fConst463 * fRec118[1]) + (fConst477 * fRec118[0])) + (fConst477 * fRec118[2])));
			fRec117[0] = (fTemp84 - (fConst459 * ((fConst478 * fRec117[2]) + (fConst480 * fRec117[1]))));
			fRec116[0] = ((fConst459 * (((fConst461 * fRec117[1]) + (fConst481 * fRec117[0])) + (fConst481 * fRec117[2]))) - (fConst456 * ((fConst482 * fRec116[2]) + (fConst483 * fRec116[1]))));
			fRec115[0] = ((fConst456 * (((fConst458 * fRec116[1]) + (fConst484 * fRec116[0])) + (fConst484 * fRec116[2]))) - (fConst452 * ((fConst485 * fRec115[2]) + (fConst486 * fRec115[1]))));
			fRec114[0] = ((fSlow1 * fRec114[1]) + (fSlow2 * fabsf((fConst452 * (((fConst455 * fRec115[1]) + (fConst487 * fRec115[0])) + (fConst487 * fRec115[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec114[0])))));
			fRec127[0] = (fTemp84 - (fConst504 * ((fConst507 * fRec127[2]) + (fConst508 * fRec127[1]))));
			fRec126[0] = ((fConst504 * (((fConst506 * fRec127[1]) + (fConst509 * fRec127[0])) + (fConst509 * fRec127[2]))) - (fConst502 * ((fConst510 * fRec126[2]) + (fConst511 * fRec126[1]))));
			fRec125[0] = ((fConst502 * (((fConst503 * fRec126[1]) + (fConst512 * fRec126[0])) + (fConst512 * fRec126[2]))) - (fConst500 * ((fConst513 * fRec125[2]) + (fConst514 * fRec125[1]))));
			float fTemp85 = (fConst500 * (((fConst501 * fRec125[1]) + (fConst515 * fRec125[0])) + (fConst515 * fRec125[2])));
			fRec124[0] = (fTemp85 - (fConst497 * ((fConst516 * fRec124[2]) + (fConst518 * fRec124[1]))));
			fRec123[0] = ((fConst497 * (((fConst499 * fRec124[1]) + (fConst519 * fRec124[0])) + (fConst519 * fRec124[2]))) - (fConst494 * ((fConst520 * fRec123[2]) + (fConst521 * fRec123[1]))));
			fRec122[0] = ((fConst494 * (((fConst496 * fRec123[1]) + (fConst522 * fRec123[0])) + (fConst522 * fRec123[2]))) - (fConst490 * ((fConst523 * fRec122[2]) + (fConst524 * fRec122[1]))));
			fRec121[0] = ((fSlow1 * fRec121[1]) + (fSlow2 * fabsf((fConst490 * (((fConst493 * fRec122[1]) + (fConst525 * fRec122[0])) + (fConst525 * fRec122[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec121[0])))));
			fRec131[0] = (fTemp85 - (fConst530 * ((fConst533 * fRec131[2]) + (fConst534 * fRec131[1]))));
			fRec130[0] = ((fConst530 * (((fConst532 * fRec131[1]) + (fConst535 * fRec131[0])) + (fConst535 * fRec131[2]))) - (fConst528 * ((fConst536 * fRec130[2]) + (fConst537 * fRec130[1]))));
			fRec129[0] = ((fConst528 * (((fConst529 * fRec130[1]) + (fConst538 * fRec130[0])) + (fConst538 * fRec130[2]))) - (fConst526 * ((fConst539 * fRec129[2]) + (fConst540 * fRec129[1]))));
			fRec128[0] = ((fSlow1 * fRec128[1]) + (fSlow2 * fabsf((fConst526 * (((fConst527 * fRec129[1]) + (fConst541 * fRec129[0])) + (fConst541 * fRec129[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec128[0])))));
			output0[i] = FAUSTFLOAT(fTemp72);
			output1[i] = FAUSTFLOAT(fTemp72);
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec19[1] = fRec19[0];
			fRec30[1] = fRec30[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec35[1] = fRec35[0];
			fVec1[1] = fVec1[0];
			fRec34[1] = fRec34[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec36[1] = fRec36[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec37[1] = fRec37[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			iRec38[1] = iRec38[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec39[j1] = fRec39[(j1 - 1)];
				
			}
			fRec40[1] = fRec40[0];
			fRec41[1] = fRec41[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec42[1] = fRec42[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec48[1] = fRec48[0];
			fRec46[1] = fRec46[0];
			fRec51[1] = fRec51[0];
			fRec49[1] = fRec49[0];
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
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[1] = fRec52[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[1] = fRec56[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[1] = fRec64[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[1] = fRec68[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
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
			fRec72[1] = fRec72[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
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
			fRec79[1] = fRec79[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[1] = fRec86[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[1] = fRec93[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[1] = fRec100[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[1] = fRec107[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fRec119[2] = fRec119[1];
			fRec119[1] = fRec119[0];
			fRec118[2] = fRec118[1];
			fRec118[1] = fRec118[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[2] = fRec116[1];
			fRec116[1] = fRec116[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec114[1] = fRec114[0];
			fRec127[2] = fRec127[1];
			fRec127[1] = fRec127[0];
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
			fRec121[1] = fRec121[0];
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1];
			fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec128[1] = fRec128[0];
			
		}
		
	}

	
};

#endif
