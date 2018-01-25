/* ------------------------------------------------------------
name: "phaserFlangerLab"
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
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider3;
	float fConst47;
	FAUSTFLOAT fHslider4;
	int iVec0[4];
	float fRec13[2];
	float fRec14[2];
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fEntry0;
	float fConst48;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	float fRec16[2];
	float fVec1[2];
	float fRec15[2];
	float fConst49;
	float fVec2[2];
	float fConst50;
	float fVec3[2];
	float fVec4[2];
	float fConst51;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider2;
	float fVec8[2];
	float fRec17[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider3;
	float fVec15[2];
	float fRec18[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fVslider4;
	float fRec19[2];
	FAUSTFLOAT fCheckbox4;
	int iRec20[2];
	float fRec21[4];
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	int IOTA;
	float fVec22[4096];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec22[2];
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	float fRec28[2];
	float fRec29[2];
	float fRec27[3];
	float fRec26[3];
	float fRec25[3];
	float fRec24[3];
	float fRec23[2];
	float fVec23[4096];
	float fRec30[2];
	float fRec35[3];
	float fRec34[3];
	float fRec33[3];
	float fRec32[3];
	float fRec31[2];
	float fConst52;
	float fConst53;
	float fRec12[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec11[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec10[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec9[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec8[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec7[3];
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec6[3];
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec5[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec4[3];
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec3[3];
	float fConst82;
	float fConst83;
	float fConst84;
	float fRec2[3];
	float fConst85;
	float fConst86;
	float fConst87;
	float fRec1[3];
	float fConst88;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fRec42[3];
	float fConst110;
	float fConst111;
	float fConst112;
	float fRec41[3];
	float fConst113;
	float fConst114;
	float fConst115;
	float fRec40[3];
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec39[3];
	float fConst120;
	float fConst121;
	float fConst122;
	float fRec38[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fRec37[3];
	float fConst126;
	float fRec36[2];
	FAUSTFLOAT fVbargraph1;
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fConst131;
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
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fRec49[3];
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec48[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fRec47[3];
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fRec46[3];
	float fConst158;
	float fConst159;
	float fConst160;
	float fRec45[3];
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec44[3];
	float fConst164;
	float fRec43[2];
	FAUSTFLOAT fVbargraph2;
	float fConst165;
	float fConst166;
	float fConst167;
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
	float fConst179;
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fConst184;
	float fConst185;
	float fRec56[3];
	float fConst186;
	float fConst187;
	float fConst188;
	float fRec55[3];
	float fConst189;
	float fConst190;
	float fConst191;
	float fRec54[3];
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec53[3];
	float fConst196;
	float fConst197;
	float fConst198;
	float fRec52[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fRec51[3];
	float fConst202;
	float fRec50[2];
	FAUSTFLOAT fVbargraph3;
	float fConst203;
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
	float fConst215;
	float fConst216;
	float fConst217;
	float fConst218;
	float fConst219;
	float fConst220;
	float fConst221;
	float fConst222;
	float fConst223;
	float fRec63[3];
	float fConst224;
	float fConst225;
	float fConst226;
	float fRec62[3];
	float fConst227;
	float fConst228;
	float fConst229;
	float fRec61[3];
	float fConst230;
	float fConst231;
	float fConst232;
	float fConst233;
	float fRec60[3];
	float fConst234;
	float fConst235;
	float fConst236;
	float fRec59[3];
	float fConst237;
	float fConst238;
	float fConst239;
	float fRec58[3];
	float fConst240;
	float fRec57[2];
	FAUSTFLOAT fVbargraph4;
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
	float fConst255;
	float fConst256;
	float fConst257;
	float fConst258;
	float fConst259;
	float fConst260;
	float fConst261;
	float fRec70[3];
	float fConst262;
	float fConst263;
	float fConst264;
	float fRec69[3];
	float fConst265;
	float fConst266;
	float fConst267;
	float fRec68[3];
	float fConst268;
	float fConst269;
	float fConst270;
	float fConst271;
	float fRec67[3];
	float fConst272;
	float fConst273;
	float fConst274;
	float fRec66[3];
	float fConst275;
	float fConst276;
	float fConst277;
	float fRec65[3];
	float fConst278;
	float fRec64[2];
	FAUSTFLOAT fVbargraph5;
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
	float fConst293;
	float fConst294;
	float fConst295;
	float fConst296;
	float fConst297;
	float fConst298;
	float fConst299;
	float fRec77[3];
	float fConst300;
	float fConst301;
	float fConst302;
	float fRec76[3];
	float fConst303;
	float fConst304;
	float fConst305;
	float fRec75[3];
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fRec74[3];
	float fConst310;
	float fConst311;
	float fConst312;
	float fRec73[3];
	float fConst313;
	float fConst314;
	float fConst315;
	float fRec72[3];
	float fConst316;
	float fRec71[2];
	FAUSTFLOAT fVbargraph6;
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
	float fConst331;
	float fConst332;
	float fConst333;
	float fConst334;
	float fConst335;
	float fConst336;
	float fConst337;
	float fRec84[3];
	float fConst338;
	float fConst339;
	float fConst340;
	float fRec83[3];
	float fConst341;
	float fConst342;
	float fConst343;
	float fRec82[3];
	float fConst344;
	float fConst345;
	float fConst346;
	float fConst347;
	float fRec81[3];
	float fConst348;
	float fConst349;
	float fConst350;
	float fRec80[3];
	float fConst351;
	float fConst352;
	float fConst353;
	float fRec79[3];
	float fConst354;
	float fRec78[2];
	FAUSTFLOAT fVbargraph7;
	float fConst355;
	float fConst356;
	float fConst357;
	float fConst358;
	float fConst359;
	float fConst360;
	float fConst361;
	float fConst362;
	float fConst363;
	float fConst364;
	float fConst365;
	float fRec88[3];
	float fConst366;
	float fConst367;
	float fConst368;
	float fRec87[3];
	float fConst369;
	float fConst370;
	float fConst371;
	float fRec86[3];
	float fConst372;
	float fRec85[2];
	FAUSTFLOAT fVbargraph8;
	float fConst373;
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
	float fRec92[3];
	float fConst384;
	float fConst385;
	float fConst386;
	float fRec91[3];
	float fConst387;
	float fConst388;
	float fConst389;
	float fRec90[3];
	float fConst390;
	float fRec89[2];
	FAUSTFLOAT fVbargraph9;
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
	float fRec96[3];
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec95[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec94[3];
	float fConst408;
	float fRec93[2];
	FAUSTFLOAT fVbargraph10;
	float fConst409;
	float fConst410;
	float fConst411;
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
	float fRec103[3];
	float fConst430;
	float fConst431;
	float fConst432;
	float fRec102[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec101[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fRec100[3];
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec99[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec98[3];
	float fConst446;
	float fRec97[2];
	FAUSTFLOAT fVbargraph11;
	float fConst447;
	float fConst448;
	float fConst449;
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
	float fRec110[3];
	float fConst468;
	float fConst469;
	float fConst470;
	float fRec109[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec108[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fRec107[3];
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec106[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec105[3];
	float fConst484;
	float fRec104[2];
	FAUSTFLOAT fVbargraph12;
	float fConst485;
	float fConst486;
	float fConst487;
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
	float fRec117[3];
	float fConst506;
	float fConst507;
	float fConst508;
	float fRec116[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec115[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fRec114[3];
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec113[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec112[3];
	float fConst522;
	float fRec111[2];
	FAUSTFLOAT fVbargraph13;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fRec121[3];
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec120[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec119[3];
	float fConst538;
	float fRec118[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "phaserFlangerLab");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
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
		fConst47 = (6.28318548f / fConst0);
		fConst48 = (1.0f / fConst0);
		fConst49 = (0.25f * fConst0);
		fConst50 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst51 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst52 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst53 = (2.0f * (0.245291501f - fConst40));
		fConst54 = (fConst45 + 0.000433227193f);
		fConst55 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst56 = (2.0f * (0.689621389f - fConst40));
		fConst57 = (fConst40 + 7.62173128f);
		fConst58 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst59 = (2.0f * (1.06935835f - fConst40));
		fConst60 = (fConst40 + 53.5361519f);
		fConst61 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst62 = (2.0f * (0.245291501f - fConst29));
		fConst63 = (fConst34 + 0.000433227193f);
		fConst64 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst65 = (2.0f * (0.689621389f - fConst29));
		fConst66 = (fConst29 + 7.62173128f);
		fConst67 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst68 = (2.0f * (1.06935835f - fConst29));
		fConst69 = (fConst29 + 53.5361519f);
		fConst70 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst71 = (2.0f * (0.245291501f - fConst18));
		fConst72 = (fConst23 + 0.000433227193f);
		fConst73 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst74 = (2.0f * (0.689621389f - fConst18));
		fConst75 = (fConst18 + 7.62173128f);
		fConst76 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst77 = (2.0f * (1.06935835f - fConst18));
		fConst78 = (fConst18 + 53.5361519f);
		fConst79 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst80 = (1.0f / fConst5);
		fConst81 = (2.0f * (4.07678175f - fConst80));
		fConst82 = (fConst12 + 0.000407678192f);
		fConst83 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst84 = (2.0f * (1.4500711f - fConst80));
		fConst85 = (fConst9 + 1.4500711f);
		fConst86 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst87 = (2.0f * (0.935140193f - fConst80));
		fConst88 = (fConst6 + 0.935140193f);
		fConst89 = tanf((7916.31738f / fConst0));
		fConst90 = (1.0f / fConst89);
		fConst91 = (1.0f / (((fConst90 + 0.157482162f) / fConst89) + 0.935140193f));
		fConst92 = mydsp_faustpower2_f(fConst89);
		fConst93 = (50.0638084f / fConst92);
		fConst94 = (2.0f * (0.935140193f - fConst93));
		fConst95 = (1.0f / (((fConst90 + 0.743130445f) / fConst89) + 1.4500711f));
		fConst96 = (11.0520525f / fConst92);
		fConst97 = (2.0f * (1.4500711f - fConst96));
		fConst98 = (1.0f / (((fConst90 + 3.18972731f) / fConst89) + 4.07678175f));
		fConst99 = (0.00176617282f / fConst92);
		fConst100 = (2.0f * (0.000407678192f - fConst99));
		fConst101 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst102 = (2.0f * (53.5361519f - fConst80));
		fConst103 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst104 = (2.0f * (7.62173128f - fConst80));
		fConst105 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst106 = (9.99999975e-05f / fConst5);
		fConst107 = (fConst106 + 0.000433227193f);
		fConst108 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst109 = (2.0f * (0.245291501f - fConst80));
		fConst110 = (2.0f * (0.000433227193f - fConst106));
		fConst111 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst112 = (2.0f * (0.689621389f - fConst80));
		fConst113 = (fConst80 + 7.62173128f);
		fConst114 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst115 = (2.0f * (1.06935835f - fConst80));
		fConst116 = (fConst80 + 53.5361519f);
		fConst117 = (((fConst90 + -3.18972731f) / fConst89) + 4.07678175f);
		fConst118 = (1.0f / fConst92);
		fConst119 = (2.0f * (4.07678175f - fConst118));
		fConst120 = (fConst99 + 0.000407678192f);
		fConst121 = (((fConst90 + -0.743130445f) / fConst89) + 1.4500711f);
		fConst122 = (2.0f * (1.4500711f - fConst118));
		fConst123 = (fConst96 + 1.4500711f);
		fConst124 = (((fConst90 + -0.157482162f) / fConst89) + 0.935140193f);
		fConst125 = (2.0f * (0.935140193f - fConst118));
		fConst126 = (fConst93 + 0.935140193f);
		fConst127 = tanf((4986.96729f / fConst0));
		fConst128 = (1.0f / fConst127);
		fConst129 = (1.0f / (((fConst128 + 0.157482162f) / fConst127) + 0.935140193f));
		fConst130 = mydsp_faustpower2_f(fConst127);
		fConst131 = (50.0638084f / fConst130);
		fConst132 = (2.0f * (0.935140193f - fConst131));
		fConst133 = (1.0f / (((fConst128 + 0.743130445f) / fConst127) + 1.4500711f));
		fConst134 = (11.0520525f / fConst130);
		fConst135 = (2.0f * (1.4500711f - fConst134));
		fConst136 = (1.0f / (((fConst128 + 3.18972731f) / fConst127) + 4.07678175f));
		fConst137 = (0.00176617282f / fConst130);
		fConst138 = (2.0f * (0.000407678192f - fConst137));
		fConst139 = (1.0f / (((fConst90 + 0.168404877f) / fConst89) + 1.06935835f));
		fConst140 = (2.0f * (53.5361519f - fConst118));
		fConst141 = (1.0f / (((fConst90 + 0.51247865f) / fConst89) + 0.689621389f));
		fConst142 = (2.0f * (7.62173128f - fConst118));
		fConst143 = (1.0f / (((fConst90 + 0.782413065f) / fConst89) + 0.245291501f));
		fConst144 = (9.99999975e-05f / fConst92);
		fConst145 = (2.0f * (0.000433227193f - fConst144));
		fConst146 = (((fConst90 + -0.782413065f) / fConst89) + 0.245291501f);
		fConst147 = (2.0f * (0.245291501f - fConst118));
		fConst148 = (fConst144 + 0.000433227193f);
		fConst149 = (((fConst90 + -0.51247865f) / fConst89) + 0.689621389f);
		fConst150 = (2.0f * (0.689621389f - fConst118));
		fConst151 = (fConst118 + 7.62173128f);
		fConst152 = (((fConst90 + -0.168404877f) / fConst89) + 1.06935835f);
		fConst153 = (2.0f * (1.06935835f - fConst118));
		fConst154 = (fConst118 + 53.5361519f);
		fConst155 = (((fConst128 + -3.18972731f) / fConst127) + 4.07678175f);
		fConst156 = (1.0f / fConst130);
		fConst157 = (2.0f * (4.07678175f - fConst156));
		fConst158 = (fConst137 + 0.000407678192f);
		fConst159 = (((fConst128 + -0.743130445f) / fConst127) + 1.4500711f);
		fConst160 = (2.0f * (1.4500711f - fConst156));
		fConst161 = (fConst134 + 1.4500711f);
		fConst162 = (((fConst128 + -0.157482162f) / fConst127) + 0.935140193f);
		fConst163 = (2.0f * (0.935140193f - fConst156));
		fConst164 = (fConst131 + 0.935140193f);
		fConst165 = tanf((3141.59277f / fConst0));
		fConst166 = (1.0f / fConst165);
		fConst167 = (1.0f / (((fConst166 + 0.157482162f) / fConst165) + 0.935140193f));
		fConst168 = mydsp_faustpower2_f(fConst165);
		fConst169 = (50.0638084f / fConst168);
		fConst170 = (2.0f * (0.935140193f - fConst169));
		fConst171 = (1.0f / (((fConst166 + 0.743130445f) / fConst165) + 1.4500711f));
		fConst172 = (11.0520525f / fConst168);
		fConst173 = (2.0f * (1.4500711f - fConst172));
		fConst174 = (1.0f / (((fConst166 + 3.18972731f) / fConst165) + 4.07678175f));
		fConst175 = (0.00176617282f / fConst168);
		fConst176 = (2.0f * (0.000407678192f - fConst175));
		fConst177 = (1.0f / (((fConst128 + 0.168404877f) / fConst127) + 1.06935835f));
		fConst178 = (2.0f * (53.5361519f - fConst156));
		fConst179 = (1.0f / (((fConst128 + 0.51247865f) / fConst127) + 0.689621389f));
		fConst180 = (2.0f * (7.62173128f - fConst156));
		fConst181 = (1.0f / (((fConst128 + 0.782413065f) / fConst127) + 0.245291501f));
		fConst182 = (9.99999975e-05f / fConst130);
		fConst183 = (2.0f * (0.000433227193f - fConst182));
		fConst184 = (((fConst128 + -0.782413065f) / fConst127) + 0.245291501f);
		fConst185 = (2.0f * (0.245291501f - fConst156));
		fConst186 = (fConst182 + 0.000433227193f);
		fConst187 = (((fConst128 + -0.51247865f) / fConst127) + 0.689621389f);
		fConst188 = (2.0f * (0.689621389f - fConst156));
		fConst189 = (fConst156 + 7.62173128f);
		fConst190 = (((fConst128 + -0.168404877f) / fConst127) + 1.06935835f);
		fConst191 = (2.0f * (1.06935835f - fConst156));
		fConst192 = (fConst156 + 53.5361519f);
		fConst193 = (((fConst166 + -3.18972731f) / fConst165) + 4.07678175f);
		fConst194 = (1.0f / fConst168);
		fConst195 = (2.0f * (4.07678175f - fConst194));
		fConst196 = (fConst175 + 0.000407678192f);
		fConst197 = (((fConst166 + -0.743130445f) / fConst165) + 1.4500711f);
		fConst198 = (2.0f * (1.4500711f - fConst194));
		fConst199 = (fConst172 + 1.4500711f);
		fConst200 = (((fConst166 + -0.157482162f) / fConst165) + 0.935140193f);
		fConst201 = (2.0f * (0.935140193f - fConst194));
		fConst202 = (fConst169 + 0.935140193f);
		fConst203 = tanf((1979.07935f / fConst0));
		fConst204 = (1.0f / fConst203);
		fConst205 = (1.0f / (((fConst204 + 0.157482162f) / fConst203) + 0.935140193f));
		fConst206 = mydsp_faustpower2_f(fConst203);
		fConst207 = (50.0638084f / fConst206);
		fConst208 = (2.0f * (0.935140193f - fConst207));
		fConst209 = (1.0f / (((fConst204 + 0.743130445f) / fConst203) + 1.4500711f));
		fConst210 = (11.0520525f / fConst206);
		fConst211 = (2.0f * (1.4500711f - fConst210));
		fConst212 = (1.0f / (((fConst204 + 3.18972731f) / fConst203) + 4.07678175f));
		fConst213 = (0.00176617282f / fConst206);
		fConst214 = (2.0f * (0.000407678192f - fConst213));
		fConst215 = (1.0f / (((fConst166 + 0.168404877f) / fConst165) + 1.06935835f));
		fConst216 = (2.0f * (53.5361519f - fConst194));
		fConst217 = (1.0f / (((fConst166 + 0.51247865f) / fConst165) + 0.689621389f));
		fConst218 = (2.0f * (7.62173128f - fConst194));
		fConst219 = (1.0f / (((fConst166 + 0.782413065f) / fConst165) + 0.245291501f));
		fConst220 = (9.99999975e-05f / fConst168);
		fConst221 = (2.0f * (0.000433227193f - fConst220));
		fConst222 = (((fConst166 + -0.782413065f) / fConst165) + 0.245291501f);
		fConst223 = (2.0f * (0.245291501f - fConst194));
		fConst224 = (fConst220 + 0.000433227193f);
		fConst225 = (((fConst166 + -0.51247865f) / fConst165) + 0.689621389f);
		fConst226 = (2.0f * (0.689621389f - fConst194));
		fConst227 = (fConst194 + 7.62173128f);
		fConst228 = (((fConst166 + -0.168404877f) / fConst165) + 1.06935835f);
		fConst229 = (2.0f * (1.06935835f - fConst194));
		fConst230 = (fConst194 + 53.5361519f);
		fConst231 = (((fConst204 + -3.18972731f) / fConst203) + 4.07678175f);
		fConst232 = (1.0f / fConst206);
		fConst233 = (2.0f * (4.07678175f - fConst232));
		fConst234 = (fConst213 + 0.000407678192f);
		fConst235 = (((fConst204 + -0.743130445f) / fConst203) + 1.4500711f);
		fConst236 = (2.0f * (1.4500711f - fConst232));
		fConst237 = (fConst210 + 1.4500711f);
		fConst238 = (((fConst204 + -0.157482162f) / fConst203) + 0.935140193f);
		fConst239 = (2.0f * (0.935140193f - fConst232));
		fConst240 = (fConst207 + 0.935140193f);
		fConst241 = tanf((1246.74182f / fConst0));
		fConst242 = (1.0f / fConst241);
		fConst243 = (1.0f / (((fConst242 + 0.157482162f) / fConst241) + 0.935140193f));
		fConst244 = mydsp_faustpower2_f(fConst241);
		fConst245 = (50.0638084f / fConst244);
		fConst246 = (2.0f * (0.935140193f - fConst245));
		fConst247 = (1.0f / (((fConst242 + 0.743130445f) / fConst241) + 1.4500711f));
		fConst248 = (11.0520525f / fConst244);
		fConst249 = (2.0f * (1.4500711f - fConst248));
		fConst250 = (1.0f / (((fConst242 + 3.18972731f) / fConst241) + 4.07678175f));
		fConst251 = (0.00176617282f / fConst244);
		fConst252 = (2.0f * (0.000407678192f - fConst251));
		fConst253 = (1.0f / (((fConst204 + 0.168404877f) / fConst203) + 1.06935835f));
		fConst254 = (2.0f * (53.5361519f - fConst232));
		fConst255 = (1.0f / (((fConst204 + 0.51247865f) / fConst203) + 0.689621389f));
		fConst256 = (2.0f * (7.62173128f - fConst232));
		fConst257 = (1.0f / (((fConst204 + 0.782413065f) / fConst203) + 0.245291501f));
		fConst258 = (9.99999975e-05f / fConst206);
		fConst259 = (2.0f * (0.000433227193f - fConst258));
		fConst260 = (((fConst204 + -0.782413065f) / fConst203) + 0.245291501f);
		fConst261 = (2.0f * (0.245291501f - fConst232));
		fConst262 = (fConst258 + 0.000433227193f);
		fConst263 = (((fConst204 + -0.51247865f) / fConst203) + 0.689621389f);
		fConst264 = (2.0f * (0.689621389f - fConst232));
		fConst265 = (fConst232 + 7.62173128f);
		fConst266 = (((fConst204 + -0.168404877f) / fConst203) + 1.06935835f);
		fConst267 = (2.0f * (1.06935835f - fConst232));
		fConst268 = (fConst232 + 53.5361519f);
		fConst269 = (((fConst242 + -3.18972731f) / fConst241) + 4.07678175f);
		fConst270 = (1.0f / fConst244);
		fConst271 = (2.0f * (4.07678175f - fConst270));
		fConst272 = (fConst251 + 0.000407678192f);
		fConst273 = (((fConst242 + -0.743130445f) / fConst241) + 1.4500711f);
		fConst274 = (2.0f * (1.4500711f - fConst270));
		fConst275 = (fConst248 + 1.4500711f);
		fConst276 = (((fConst242 + -0.157482162f) / fConst241) + 0.935140193f);
		fConst277 = (2.0f * (0.935140193f - fConst270));
		fConst278 = (fConst245 + 0.935140193f);
		fConst279 = tanf((785.398193f / fConst0));
		fConst280 = (1.0f / fConst279);
		fConst281 = (1.0f / (((fConst280 + 0.157482162f) / fConst279) + 0.935140193f));
		fConst282 = mydsp_faustpower2_f(fConst279);
		fConst283 = (50.0638084f / fConst282);
		fConst284 = (2.0f * (0.935140193f - fConst283));
		fConst285 = (1.0f / (((fConst280 + 0.743130445f) / fConst279) + 1.4500711f));
		fConst286 = (11.0520525f / fConst282);
		fConst287 = (2.0f * (1.4500711f - fConst286));
		fConst288 = (1.0f / (((fConst280 + 3.18972731f) / fConst279) + 4.07678175f));
		fConst289 = (0.00176617282f / fConst282);
		fConst290 = (2.0f * (0.000407678192f - fConst289));
		fConst291 = (1.0f / (((fConst242 + 0.168404877f) / fConst241) + 1.06935835f));
		fConst292 = (2.0f * (53.5361519f - fConst270));
		fConst293 = (1.0f / (((fConst242 + 0.51247865f) / fConst241) + 0.689621389f));
		fConst294 = (2.0f * (7.62173128f - fConst270));
		fConst295 = (1.0f / (((fConst242 + 0.782413065f) / fConst241) + 0.245291501f));
		fConst296 = (9.99999975e-05f / fConst244);
		fConst297 = (2.0f * (0.000433227193f - fConst296));
		fConst298 = (((fConst242 + -0.782413065f) / fConst241) + 0.245291501f);
		fConst299 = (2.0f * (0.245291501f - fConst270));
		fConst300 = (fConst296 + 0.000433227193f);
		fConst301 = (((fConst242 + -0.51247865f) / fConst241) + 0.689621389f);
		fConst302 = (2.0f * (0.689621389f - fConst270));
		fConst303 = (fConst270 + 7.62173128f);
		fConst304 = (((fConst242 + -0.168404877f) / fConst241) + 1.06935835f);
		fConst305 = (2.0f * (1.06935835f - fConst270));
		fConst306 = (fConst270 + 53.5361519f);
		fConst307 = (((fConst280 + -3.18972731f) / fConst279) + 4.07678175f);
		fConst308 = (1.0f / fConst282);
		fConst309 = (2.0f * (4.07678175f - fConst308));
		fConst310 = (fConst289 + 0.000407678192f);
		fConst311 = (((fConst280 + -0.743130445f) / fConst279) + 1.4500711f);
		fConst312 = (2.0f * (1.4500711f - fConst308));
		fConst313 = (fConst286 + 1.4500711f);
		fConst314 = (((fConst280 + -0.157482162f) / fConst279) + 0.935140193f);
		fConst315 = (2.0f * (0.935140193f - fConst308));
		fConst316 = (fConst283 + 0.935140193f);
		fConst317 = tanf((494.769836f / fConst0));
		fConst318 = (1.0f / fConst317);
		fConst319 = (1.0f / (((fConst318 + 0.157482162f) / fConst317) + 0.935140193f));
		fConst320 = mydsp_faustpower2_f(fConst317);
		fConst321 = (50.0638084f / fConst320);
		fConst322 = (2.0f * (0.935140193f - fConst321));
		fConst323 = (1.0f / (((fConst318 + 0.743130445f) / fConst317) + 1.4500711f));
		fConst324 = (11.0520525f / fConst320);
		fConst325 = (2.0f * (1.4500711f - fConst324));
		fConst326 = (1.0f / (((fConst318 + 3.18972731f) / fConst317) + 4.07678175f));
		fConst327 = (0.00176617282f / fConst320);
		fConst328 = (2.0f * (0.000407678192f - fConst327));
		fConst329 = (1.0f / (((fConst280 + 0.168404877f) / fConst279) + 1.06935835f));
		fConst330 = (2.0f * (53.5361519f - fConst308));
		fConst331 = (1.0f / (((fConst280 + 0.51247865f) / fConst279) + 0.689621389f));
		fConst332 = (2.0f * (7.62173128f - fConst308));
		fConst333 = (1.0f / (((fConst280 + 0.782413065f) / fConst279) + 0.245291501f));
		fConst334 = (9.99999975e-05f / fConst282);
		fConst335 = (2.0f * (0.000433227193f - fConst334));
		fConst336 = (((fConst280 + -0.782413065f) / fConst279) + 0.245291501f);
		fConst337 = (2.0f * (0.245291501f - fConst308));
		fConst338 = (fConst334 + 0.000433227193f);
		fConst339 = (((fConst280 + -0.51247865f) / fConst279) + 0.689621389f);
		fConst340 = (2.0f * (0.689621389f - fConst308));
		fConst341 = (fConst308 + 7.62173128f);
		fConst342 = (((fConst280 + -0.168404877f) / fConst279) + 1.06935835f);
		fConst343 = (2.0f * (1.06935835f - fConst308));
		fConst344 = (fConst308 + 53.5361519f);
		fConst345 = (((fConst318 + -3.18972731f) / fConst317) + 4.07678175f);
		fConst346 = (1.0f / fConst320);
		fConst347 = (2.0f * (4.07678175f - fConst346));
		fConst348 = (fConst327 + 0.000407678192f);
		fConst349 = (((fConst318 + -0.743130445f) / fConst317) + 1.4500711f);
		fConst350 = (2.0f * (1.4500711f - fConst346));
		fConst351 = (fConst324 + 1.4500711f);
		fConst352 = (((fConst318 + -0.157482162f) / fConst317) + 0.935140193f);
		fConst353 = (2.0f * (0.935140193f - fConst346));
		fConst354 = (fConst321 + 0.935140193f);
		fConst355 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst356 = (50.0638084f / fConst39);
		fConst357 = (2.0f * (0.935140193f - fConst356));
		fConst358 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst359 = (11.0520525f / fConst39);
		fConst360 = (2.0f * (1.4500711f - fConst359));
		fConst361 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst362 = (0.00176617282f / fConst39);
		fConst363 = (2.0f * (0.000407678192f - fConst362));
		fConst364 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst365 = (2.0f * (4.07678175f - fConst40));
		fConst366 = (fConst362 + 0.000407678192f);
		fConst367 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst368 = (2.0f * (1.4500711f - fConst40));
		fConst369 = (fConst359 + 1.4500711f);
		fConst370 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst371 = (2.0f * (0.935140193f - fConst40));
		fConst372 = (fConst356 + 0.935140193f);
		fConst373 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst374 = (50.0638084f / fConst28);
		fConst375 = (2.0f * (0.935140193f - fConst374));
		fConst376 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst377 = (11.0520525f / fConst28);
		fConst378 = (2.0f * (1.4500711f - fConst377));
		fConst379 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst380 = (0.00176617282f / fConst28);
		fConst381 = (2.0f * (0.000407678192f - fConst380));
		fConst382 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst383 = (2.0f * (4.07678175f - fConst29));
		fConst384 = (fConst380 + 0.000407678192f);
		fConst385 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst386 = (2.0f * (1.4500711f - fConst29));
		fConst387 = (fConst377 + 1.4500711f);
		fConst388 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst389 = (2.0f * (0.935140193f - fConst29));
		fConst390 = (fConst374 + 0.935140193f);
		fConst391 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst392 = (50.0638084f / fConst17);
		fConst393 = (2.0f * (0.935140193f - fConst392));
		fConst394 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst395 = (11.0520525f / fConst17);
		fConst396 = (2.0f * (1.4500711f - fConst395));
		fConst397 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst398 = (0.00176617282f / fConst17);
		fConst399 = (2.0f * (0.000407678192f - fConst398));
		fConst400 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst401 = (2.0f * (4.07678175f - fConst18));
		fConst402 = (fConst398 + 0.000407678192f);
		fConst403 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst404 = (2.0f * (1.4500711f - fConst18));
		fConst405 = (fConst395 + 1.4500711f);
		fConst406 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst407 = (2.0f * (0.935140193f - fConst18));
		fConst408 = (fConst392 + 0.935140193f);
		fConst409 = tanf((311.685455f / fConst0));
		fConst410 = (1.0f / fConst409);
		fConst411 = (1.0f / (((fConst410 + 0.157482162f) / fConst409) + 0.935140193f));
		fConst412 = mydsp_faustpower2_f(fConst409);
		fConst413 = (50.0638084f / fConst412);
		fConst414 = (2.0f * (0.935140193f - fConst413));
		fConst415 = (1.0f / (((fConst410 + 0.743130445f) / fConst409) + 1.4500711f));
		fConst416 = (11.0520525f / fConst412);
		fConst417 = (2.0f * (1.4500711f - fConst416));
		fConst418 = (1.0f / (((fConst410 + 3.18972731f) / fConst409) + 4.07678175f));
		fConst419 = (0.00176617282f / fConst412);
		fConst420 = (2.0f * (0.000407678192f - fConst419));
		fConst421 = (1.0f / (((fConst318 + 0.168404877f) / fConst317) + 1.06935835f));
		fConst422 = (2.0f * (53.5361519f - fConst346));
		fConst423 = (1.0f / (((fConst318 + 0.51247865f) / fConst317) + 0.689621389f));
		fConst424 = (2.0f * (7.62173128f - fConst346));
		fConst425 = (1.0f / (((fConst318 + 0.782413065f) / fConst317) + 0.245291501f));
		fConst426 = (9.99999975e-05f / fConst320);
		fConst427 = (2.0f * (0.000433227193f - fConst426));
		fConst428 = (((fConst318 + -0.782413065f) / fConst317) + 0.245291501f);
		fConst429 = (2.0f * (0.245291501f - fConst346));
		fConst430 = (fConst426 + 0.000433227193f);
		fConst431 = (((fConst318 + -0.51247865f) / fConst317) + 0.689621389f);
		fConst432 = (2.0f * (0.689621389f - fConst346));
		fConst433 = (fConst346 + 7.62173128f);
		fConst434 = (((fConst318 + -0.168404877f) / fConst317) + 1.06935835f);
		fConst435 = (2.0f * (1.06935835f - fConst346));
		fConst436 = (fConst346 + 53.5361519f);
		fConst437 = (((fConst410 + -3.18972731f) / fConst409) + 4.07678175f);
		fConst438 = (1.0f / fConst412);
		fConst439 = (2.0f * (4.07678175f - fConst438));
		fConst440 = (fConst419 + 0.000407678192f);
		fConst441 = (((fConst410 + -0.743130445f) / fConst409) + 1.4500711f);
		fConst442 = (2.0f * (1.4500711f - fConst438));
		fConst443 = (fConst416 + 1.4500711f);
		fConst444 = (((fConst410 + -0.157482162f) / fConst409) + 0.935140193f);
		fConst445 = (2.0f * (0.935140193f - fConst438));
		fConst446 = (fConst413 + 0.935140193f);
		fConst447 = tanf((196.349548f / fConst0));
		fConst448 = (1.0f / fConst447);
		fConst449 = (1.0f / (((fConst448 + 0.157482162f) / fConst447) + 0.935140193f));
		fConst450 = mydsp_faustpower2_f(fConst447);
		fConst451 = (50.0638084f / fConst450);
		fConst452 = (2.0f * (0.935140193f - fConst451));
		fConst453 = (1.0f / (((fConst448 + 0.743130445f) / fConst447) + 1.4500711f));
		fConst454 = (11.0520525f / fConst450);
		fConst455 = (2.0f * (1.4500711f - fConst454));
		fConst456 = (1.0f / (((fConst448 + 3.18972731f) / fConst447) + 4.07678175f));
		fConst457 = (0.00176617282f / fConst450);
		fConst458 = (2.0f * (0.000407678192f - fConst457));
		fConst459 = (1.0f / (((fConst410 + 0.168404877f) / fConst409) + 1.06935835f));
		fConst460 = (2.0f * (53.5361519f - fConst438));
		fConst461 = (1.0f / (((fConst410 + 0.51247865f) / fConst409) + 0.689621389f));
		fConst462 = (2.0f * (7.62173128f - fConst438));
		fConst463 = (1.0f / (((fConst410 + 0.782413065f) / fConst409) + 0.245291501f));
		fConst464 = (9.99999975e-05f / fConst412);
		fConst465 = (2.0f * (0.000433227193f - fConst464));
		fConst466 = (((fConst410 + -0.782413065f) / fConst409) + 0.245291501f);
		fConst467 = (2.0f * (0.245291501f - fConst438));
		fConst468 = (fConst464 + 0.000433227193f);
		fConst469 = (((fConst410 + -0.51247865f) / fConst409) + 0.689621389f);
		fConst470 = (2.0f * (0.689621389f - fConst438));
		fConst471 = (fConst438 + 7.62173128f);
		fConst472 = (((fConst410 + -0.168404877f) / fConst409) + 1.06935835f);
		fConst473 = (2.0f * (1.06935835f - fConst438));
		fConst474 = (fConst438 + 53.5361519f);
		fConst475 = (((fConst448 + -3.18972731f) / fConst447) + 4.07678175f);
		fConst476 = (1.0f / fConst450);
		fConst477 = (2.0f * (4.07678175f - fConst476));
		fConst478 = (fConst457 + 0.000407678192f);
		fConst479 = (((fConst448 + -0.743130445f) / fConst447) + 1.4500711f);
		fConst480 = (2.0f * (1.4500711f - fConst476));
		fConst481 = (fConst454 + 1.4500711f);
		fConst482 = (((fConst448 + -0.157482162f) / fConst447) + 0.935140193f);
		fConst483 = (2.0f * (0.935140193f - fConst476));
		fConst484 = (fConst451 + 0.935140193f);
		fConst485 = tanf((123.692459f / fConst0));
		fConst486 = (1.0f / fConst485);
		fConst487 = (1.0f / (((fConst486 + 0.157482162f) / fConst485) + 0.935140193f));
		fConst488 = mydsp_faustpower2_f(fConst485);
		fConst489 = (50.0638084f / fConst488);
		fConst490 = (2.0f * (0.935140193f - fConst489));
		fConst491 = (1.0f / (((fConst486 + 0.743130445f) / fConst485) + 1.4500711f));
		fConst492 = (11.0520525f / fConst488);
		fConst493 = (2.0f * (1.4500711f - fConst492));
		fConst494 = (1.0f / (((fConst486 + 3.18972731f) / fConst485) + 4.07678175f));
		fConst495 = (0.00176617282f / fConst488);
		fConst496 = (2.0f * (0.000407678192f - fConst495));
		fConst497 = (1.0f / (((fConst448 + 0.168404877f) / fConst447) + 1.06935835f));
		fConst498 = (2.0f * (53.5361519f - fConst476));
		fConst499 = (1.0f / (((fConst448 + 0.51247865f) / fConst447) + 0.689621389f));
		fConst500 = (2.0f * (7.62173128f - fConst476));
		fConst501 = (1.0f / (((fConst448 + 0.782413065f) / fConst447) + 0.245291501f));
		fConst502 = (9.99999975e-05f / fConst450);
		fConst503 = (2.0f * (0.000433227193f - fConst502));
		fConst504 = (((fConst448 + -0.782413065f) / fConst447) + 0.245291501f);
		fConst505 = (2.0f * (0.245291501f - fConst476));
		fConst506 = (fConst502 + 0.000433227193f);
		fConst507 = (((fConst448 + -0.51247865f) / fConst447) + 0.689621389f);
		fConst508 = (2.0f * (0.689621389f - fConst476));
		fConst509 = (fConst476 + 7.62173128f);
		fConst510 = (((fConst448 + -0.168404877f) / fConst447) + 1.06935835f);
		fConst511 = (2.0f * (1.06935835f - fConst476));
		fConst512 = (fConst476 + 53.5361519f);
		fConst513 = (((fConst486 + -3.18972731f) / fConst485) + 4.07678175f);
		fConst514 = (1.0f / fConst488);
		fConst515 = (2.0f * (4.07678175f - fConst514));
		fConst516 = (fConst495 + 0.000407678192f);
		fConst517 = (((fConst486 + -0.743130445f) / fConst485) + 1.4500711f);
		fConst518 = (2.0f * (1.4500711f - fConst514));
		fConst519 = (fConst492 + 1.4500711f);
		fConst520 = (((fConst486 + -0.157482162f) / fConst485) + 0.935140193f);
		fConst521 = (2.0f * (0.935140193f - fConst514));
		fConst522 = (fConst489 + 0.935140193f);
		fConst523 = (1.0f / (((fConst486 + 0.168404877f) / fConst485) + 1.06935835f));
		fConst524 = (2.0f * (53.5361519f - fConst514));
		fConst525 = (1.0f / (((fConst486 + 0.51247865f) / fConst485) + 0.689621389f));
		fConst526 = (2.0f * (7.62173128f - fConst514));
		fConst527 = (1.0f / (((fConst486 + 0.782413065f) / fConst485) + 0.245291501f));
		fConst528 = (9.99999975e-05f / fConst488);
		fConst529 = (2.0f * (0.000433227193f - fConst528));
		fConst530 = (((fConst486 + -0.782413065f) / fConst485) + 0.245291501f);
		fConst531 = (2.0f * (0.245291501f - fConst514));
		fConst532 = (fConst528 + 0.000433227193f);
		fConst533 = (((fConst486 + -0.51247865f) / fConst485) + 0.689621389f);
		fConst534 = (2.0f * (0.689621389f - fConst514));
		fConst535 = (fConst514 + 7.62173128f);
		fConst536 = (((fConst486 + -0.168404877f) / fConst485) + 1.06935835f);
		fConst537 = (2.0f * (1.06935835f - fConst514));
		fConst538 = (fConst514 + 53.5361519f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.5f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider0 = FAUSTFLOAT(49.0f);
		fVslider1 = FAUSTFLOAT(0.10000000000000001f);
		fVslider2 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(-20.0f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(1.0f);
		fHslider8 = FAUSTFLOAT(10.0f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fHslider9 = FAUSTFLOAT(1.0f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
		fHslider10 = FAUSTFLOAT(1000.0f);
		fHslider11 = FAUSTFLOAT(0.0f);
		fHslider12 = FAUSTFLOAT(1.5f);
		fHslider13 = FAUSTFLOAT(100.0f);
		fHslider14 = FAUSTFLOAT(800.0f);
		fHslider15 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec13[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec14[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec16[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec15[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec3[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec4[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec5[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec6[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec7[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec8[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec17[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec9[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec10[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec12[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec13[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec14[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec15[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec18[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec16[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec17[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec18[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec19[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec20[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec21[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec19[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			iRec20[l29] = 0;
			
		}
		for (int l30 = 0; (l30 < 4); l30 = (l30 + 1)) {
			fRec21[l30] = 0.0f;
			
		}
		IOTA = 0;
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec22[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec22[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec28[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec29[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec27[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec26[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec25[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec24[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec23[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 4096); l40 = (l40 + 1)) {
			fVec23[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec30[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec35[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec34[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec33[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec32[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec31[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec12[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec11[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec10[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec9[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec8[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec7[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec6[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec5[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec4[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec3[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec2[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec1[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec0[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec42[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec41[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec40[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec39[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec38[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec37[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec36[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec49[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec48[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec47[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec46[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec45[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec44[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec43[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec56[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec55[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec54[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec53[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec52[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec51[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec50[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec63[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec62[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec61[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec60[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec59[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec58[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec57[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec70[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec69[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec68[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec67[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec66[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec65[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec64[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec77[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec76[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec75[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec74[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec73[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec72[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec71[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec84[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec83[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec82[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec81[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec80[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec79[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec78[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec88[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec87[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec86[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fRec85[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec92[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec91[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec90[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fRec89[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec96[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec95[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec94[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec93[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec103[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec102[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec101[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec100[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec99[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec98[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec97[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec110[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec109[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec108[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec107[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec106[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec105[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec104[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec117[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec116[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec115[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec114[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec113[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec112[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec111[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec121[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec120[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec119[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			fRec118[l145] = 0.0f;
			
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
		ui_interface->openVerticalBox("phaserFlangerLab");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib   for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider4, "1", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Sawtooth   waveform amplitude");
		ui_interface->declare(&fVslider4, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fVslider4, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fVslider0, "2", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fVslider0, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fVslider0, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fVslider2, "3", "");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Percentange frequency-shift  up or down for second oscillator");
		ui_interface->declare(&fVslider2, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider2, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider3, "4", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider3, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider1, "5", "");
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider1, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider1, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fCheckbox3, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", &fCheckbox3);
		ui_interface->declare(&fCheckbox4, "1", "");
		ui_interface->declare(&fCheckbox4, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox4);
		ui_interface->declare(&fCheckbox2, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", &fCheckbox2);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("FLANGER");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox1, "0", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "When this is checked, the flanger   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox1);
		ui_interface->declare(&fCheckbox5, "1", "");
		ui_interface->addCheckButton("Invert Flange Sum", &fCheckbox5);
		ui_interface->declare(&fHbargraph0, "2", "");
		ui_interface->declare(&fHbargraph0, "style", "led");
		ui_interface->declare(&fHbargraph0, "tooltip", "Display sum of flange delays");
		ui_interface->addHorizontalBargraph("Flange LFO", &fHbargraph0, -1.5f, 1.5f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider4, 0.5f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("Depth", &fHslider5, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback", &fHslider6, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Delay Controls");
		ui_interface->declare(&fHslider8, "1", "");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->declare(&fHslider8, "unit", "ms");
		ui_interface->addHorizontalSlider("Flange Delay", &fHslider8, 10.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface->declare(&fHslider7, "2", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Offset", &fHslider7, 1.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Flanger Output Level", &fHslider3, 0.0f, -60.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("PHASER2");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the phaser   has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox7, "1", "");
		ui_interface->addCheckButton("Invert Internal Phaser Sum", &fCheckbox7);
		ui_interface->declare(&fCheckbox6, "2", "");
		ui_interface->addCheckButton("Vibrato Mode", &fCheckbox6);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider15, "1", "");
		ui_interface->declare(&fHslider15, "style", "knob");
		ui_interface->declare(&fHslider15, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider15, 0.5f, 0.0f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fHslider9, "2", "");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Depth (Intensity)", &fHslider9, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider11, "3", "");
		ui_interface->declare(&fHslider11, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback Gain", &fHslider11, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "scale", "log");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->declare(&fHslider10, "unit", "Hz");
		ui_interface->addHorizontalSlider("Notch width", &fHslider10, 1000.0f, 10.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fHslider13, "2", "");
		ui_interface->declare(&fHslider13, "scale", "log");
		ui_interface->declare(&fHslider13, "style", "knob");
		ui_interface->declare(&fHslider13, "unit", "Hz");
		ui_interface->addHorizontalSlider("Min Notch1 Freq", &fHslider13, 100.0f, 20.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fHslider14, "3", "");
		ui_interface->declare(&fHslider14, "scale", "log");
		ui_interface->declare(&fHslider14, "style", "knob");
		ui_interface->declare(&fHslider14, "unit", "Hz");
		ui_interface->addHorizontalSlider("Max Notch1 Freq", &fHslider14, 800.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider12, "4", "");
		ui_interface->declare(&fHslider12, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &fHslider12, 1.5f, 1.10000002f, 4.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Phaser Output Level", &fHslider2, 0.0f, -60.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph14, "0", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d31be550", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d31acb40", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d318a940", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d3168740", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "4", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d310ed70", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "5", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d30e8bf0", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "6", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d30c69f0", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "7", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d30a47f0", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "8", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d30825f0", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "9", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d30603f0", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "10", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d303e1f0", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "11", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d301c330", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "12", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d3145fc0", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "13", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d31337d0", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "14", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fa4d3120fe0", &fVbargraph8, -50.0f, 10.0f);
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
		float fSlow4 = powf(10.0f, (0.0500000007f * float(fHslider2)));
		int iSlow5 = int(float(fCheckbox1));
		float fSlow6 = powf(10.0f, (0.0500000007f * float(fHslider3)));
		float fSlow7 = (fConst47 * float(fHslider4));
		float fSlow8 = sinf(fSlow7);
		float fSlow9 = cosf(fSlow7);
		float fSlow10 = (0.0f - fSlow8);
		int iSlow11 = int(float(fCheckbox2));
		int iSlow12 = int(float(fCheckbox3));
		int iSlow13 = int((float(fEntry0) + -1.0f));
		int iSlow14 = (iSlow13 >= 2);
		int iSlow15 = (iSlow13 >= 1);
		float fSlow16 = expf((0.0f - (fConst48 / float(fVslider1))));
		float fSlow17 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fVslider0) + -49.0f))) * (1.0f - fSlow16)));
		int iSlow18 = (iSlow13 >= 3);
		float fSlow19 = ((0.00999999978f * float(fVslider2)) + 1.0f);
		float fSlow20 = ((0.00999999978f * float(fVslider3)) + 1.0f);
		float fSlow21 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider4))));
		int iSlow22 = int(float(fCheckbox4));
		float fSlow23 = float(fHslider5);
		float fSlow24 = (int(float(fCheckbox5))?(0.0f - fSlow23):fSlow23);
		float fSlow25 = float(fHslider6);
		float fSlow26 = (0.00100000005f * float(fHslider7));
		float fSlow27 = (0.000500000024f * float(fHslider8));
		float fSlow28 = (0.5f * (int(float(fCheckbox6))?2.0f:float(fHslider9)));
		float fSlow29 = (1.0f - fSlow28);
		float fSlow30 = (int(float(fCheckbox7))?(0.0f - fSlow28):fSlow28);
		float fSlow31 = expf((fConst48 * (0.0f - (3.14159274f * float(fHslider10)))));
		float fSlow32 = mydsp_faustpower2_f(fSlow31);
		float fSlow33 = float(fHslider11);
		float fSlow34 = (0.0f - (2.0f * fSlow31));
		float fSlow35 = float(fHslider12);
		float fSlow36 = float(fHslider13);
		float fSlow37 = (fConst47 * fSlow36);
		float fSlow38 = (0.5f * (0.0f - (fConst47 * (fSlow36 - max(fSlow36, float(fHslider14))))));
		float fSlow39 = (fConst47 * float(fHslider15));
		float fSlow40 = sinf(fSlow39);
		float fSlow41 = cosf(fSlow39);
		float fSlow42 = (0.0f - fSlow40);
		float fSlow43 = mydsp_faustpower2_f(fSlow35);
		float fSlow44 = mydsp_faustpower3_f(fSlow35);
		float fSlow45 = mydsp_faustpower4_f(fSlow35);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec13[0] = ((fSlow8 * fRec14[1]) + (fSlow9 * fRec13[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec14[0] = (((fSlow9 * fRec14[1]) + (fSlow10 * fRec13[1])) + float(iTemp0));
			fHbargraph0 = FAUSTFLOAT((fRec14[0] + fRec13[0]));
			fRec16[0] = (fSlow17 + (fSlow16 * fRec16[1]));
			float fTemp1 = max(20.0f, fabsf(fRec16[0]));
			fVec1[0] = fTemp1;
			float fTemp2 = (fRec15[1] + (fConst48 * fVec1[1]));
			fRec15[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = (2.0f * fRec15[0]);
			float fTemp4 = (fTemp3 + -1.0f);
			float fTemp5 = mydsp_faustpower2_f(fTemp4);
			fVec2[0] = fTemp5;
			float fTemp6 = mydsp_faustpower3_f(fTemp4);
			fVec3[0] = (fTemp6 + (1.0f - fTemp3));
			float fTemp7 = ((fTemp6 + (1.0f - (fVec3[1] + fTemp3))) / fTemp1);
			fVec4[0] = fTemp7;
			float fTemp8 = (fTemp5 * (fTemp5 + -2.0f));
			fVec5[0] = fTemp8;
			float fTemp9 = ((fTemp8 - fVec5[1]) / fTemp1);
			fVec6[0] = fTemp9;
			float fTemp10 = ((fTemp9 - fVec6[1]) / fTemp1);
			fVec7[0] = fTemp10;
			float fTemp11 = max(20.0f, fabsf((fSlow19 * fRec16[0])));
			fVec8[0] = fTemp11;
			float fTemp12 = (fRec17[1] + (fConst48 * fVec8[1]));
			fRec17[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (2.0f * fRec17[0]);
			float fTemp14 = (fTemp13 + -1.0f);
			float fTemp15 = mydsp_faustpower2_f(fTemp14);
			fVec9[0] = fTemp15;
			float fTemp16 = mydsp_faustpower3_f(fTemp14);
			fVec10[0] = (fTemp16 + (1.0f - fTemp13));
			float fTemp17 = ((fTemp16 + (1.0f - (fVec10[1] + fTemp13))) / fTemp11);
			fVec11[0] = fTemp17;
			float fTemp18 = (fTemp15 * (fTemp15 + -2.0f));
			fVec12[0] = fTemp18;
			float fTemp19 = ((fTemp18 - fVec12[1]) / fTemp11);
			fVec13[0] = fTemp19;
			float fTemp20 = ((fTemp19 - fVec13[1]) / fTemp11);
			fVec14[0] = fTemp20;
			float fTemp21 = max(20.0f, fabsf((fSlow20 * fRec16[0])));
			fVec15[0] = fTemp21;
			float fTemp22 = (fRec18[1] + (fConst48 * fVec15[1]));
			fRec18[0] = (fTemp22 - floorf(fTemp22));
			float fTemp23 = (2.0f * fRec18[0]);
			float fTemp24 = (fTemp23 + -1.0f);
			float fTemp25 = mydsp_faustpower2_f(fTemp24);
			fVec16[0] = fTemp25;
			float fTemp26 = mydsp_faustpower3_f(fTemp24);
			fVec17[0] = (fTemp26 + (1.0f - fTemp23));
			float fTemp27 = ((fTemp26 + (1.0f - (fVec17[1] + fTemp23))) / fTemp21);
			fVec18[0] = fTemp27;
			float fTemp28 = (fTemp25 * (fTemp25 + -2.0f));
			fVec19[0] = fTemp28;
			float fTemp29 = ((fTemp28 - fVec19[1]) / fTemp21);
			fVec20[0] = fTemp29;
			float fTemp30 = ((fTemp29 - fVec20[1]) / fTemp21);
			fVec21[0] = fTemp30;
			fRec19[0] = (fSlow21 + (0.999000013f * fRec19[1]));
			iRec20[0] = ((1103515245 * iRec20[1]) + 12345);
			float fTemp31 = (4.65661287e-10f * float(iRec20[0]));
			fRec21[0] = ((fTemp31 + ((2.49495602f * fRec21[1]) + (0.522189379f * fRec21[3]))) - (2.0172658f * fRec21[2]));
			float fTemp32 = ((iSlow11?float(input0[i]):(iSlow12?(iSlow22?(((0.0499220341f * fRec21[0]) + (0.0506126992f * fRec21[2])) - ((0.0959935337f * fRec21[1]) + (0.00440878607f * fRec21[3]))):fTemp31):(0.333333343f * ((((iSlow14?(iSlow18?(fConst51 * ((float(iVec0[3]) * (fTemp10 - fVec7[1])) / fTemp1)):(fConst50 * ((float(iVec0[2]) * (fTemp7 - fVec4[1])) / fTemp1))):(iSlow15?(fConst49 * ((float(iVec0[1]) * (fTemp5 - fVec2[1])) / fTemp1)):fTemp4)) + (iSlow14?(iSlow18?(fConst51 * ((float(iVec0[3]) * (fTemp20 - fVec14[1])) / fTemp11)):(fConst50 * ((float(iVec0[2]) * (fTemp17 - fVec11[1])) / fTemp11))):(iSlow15?(fConst49 * ((float(iVec0[1]) * (fTemp15 - fVec9[1])) / fTemp11)):fTemp14))) + (iSlow14?(iSlow18?(fConst51 * ((float(iVec0[3]) * (fTemp30 - fVec21[1])) / fTemp21)):(fConst50 * ((float(iVec0[2]) * (fTemp27 - fVec18[1])) / fTemp21))):(iSlow15?(fConst49 * ((float(iVec0[1]) * (fTemp25 - fVec16[1])) / fTemp21)):fTemp24))) * fRec19[0])))) * fRec19[0]);
			float fTemp33 = (iSlow5?0.0f:fTemp32);
			float fTemp34 = (fSlow6 * fTemp33);
			float fTemp35 = ((fSlow25 * fRec22[1]) - fTemp34);
			fVec22[(IOTA & 4095)] = fTemp35;
			float fTemp36 = (fConst0 * (fSlow26 + (fSlow27 * (fRec13[0] + 1.0f))));
			int iTemp37 = int(fTemp36);
			float fTemp38 = floorf(fTemp36);
			fRec22[0] = ((fVec22[((IOTA - min(2049, max(0, iTemp37))) & 4095)] * (fTemp38 + (1.0f - fTemp36))) + ((fTemp36 - fTemp38) * fVec22[((IOTA - min(2049, max(0, (iTemp37 + 1)))) & 4095)]));
			float fTemp39 = (iSlow5?fTemp32:(0.5f * (fTemp34 + (fSlow24 * fRec22[0]))));
			float fTemp40 = (iSlow3?0.0f:fTemp39);
			fRec28[0] = ((fSlow40 * fRec29[1]) + (fSlow41 * fRec28[1]));
			fRec29[0] = (((fSlow41 * fRec29[1]) + (fSlow42 * fRec28[1])) + float(iTemp0));
			float fTemp41 = (fSlow37 + (fSlow38 * (1.0f - fRec28[0])));
			float fTemp42 = (fRec27[1] * cosf((fSlow35 * fTemp41)));
			fRec27[0] = (((fSlow4 * fTemp40) + (fSlow33 * fRec23[1])) - ((fSlow34 * fTemp42) + (fSlow32 * fRec27[2])));
			float fTemp43 = (fRec26[1] * cosf((fSlow43 * fTemp41)));
			fRec26[0] = ((fRec27[2] + (fSlow34 * (fTemp42 - fTemp43))) + (fSlow32 * (fRec27[0] - fRec26[2])));
			float fTemp44 = (fRec25[1] * cosf((fSlow44 * fTemp41)));
			fRec25[0] = ((fRec26[2] + (fSlow34 * (fTemp43 - fTemp44))) + (fSlow32 * (fRec26[0] - fRec25[2])));
			float fTemp45 = (fRec24[1] * cosf((fSlow45 * fTemp41)));
			fRec24[0] = ((fRec25[2] + (fSlow34 * (fTemp44 - fTemp45))) + (fSlow32 * (fRec25[0] - fRec24[2])));
			fRec23[0] = ((fSlow32 * fRec24[0]) + ((fSlow34 * fTemp45) + fRec24[2]));
			float fTemp46 = (iSlow3?fTemp39:((fSlow4 * (fTemp40 * fSlow29)) + (fSlow30 * fRec23[0])));
			float fTemp47 = (fSlow6 * fTemp33);
			float fTemp48 = ((fSlow25 * fRec30[1]) - fTemp47);
			fVec23[(IOTA & 4095)] = fTemp48;
			float fTemp49 = (fConst0 * (fSlow26 + (fSlow27 * (fRec14[0] + 1.0f))));
			int iTemp50 = int(fTemp49);
			float fTemp51 = floorf(fTemp49);
			fRec30[0] = ((fVec23[((IOTA - min(2049, max(0, iTemp50))) & 4095)] * (fTemp51 + (1.0f - fTemp49))) + ((fTemp49 - fTemp51) * fVec23[((IOTA - min(2049, max(0, (iTemp50 + 1)))) & 4095)]));
			float fTemp52 = (iSlow5?fTemp32:(0.5f * (fTemp47 + (fSlow24 * fRec30[0]))));
			float fTemp53 = (iSlow3?0.0f:fTemp52);
			float fTemp54 = (fSlow37 + (fSlow38 * (1.0f - fRec29[0])));
			float fTemp55 = (fRec35[1] * cosf((fSlow35 * fTemp54)));
			fRec35[0] = (((fSlow4 * fTemp53) + (fSlow33 * fRec31[1])) - ((fSlow34 * fTemp55) + (fSlow32 * fRec35[2])));
			float fTemp56 = (fRec34[1] * cosf((fSlow43 * fTemp54)));
			fRec34[0] = ((fRec35[2] + (fSlow34 * (fTemp55 - fTemp56))) + (fSlow32 * (fRec35[0] - fRec34[2])));
			float fTemp57 = (fRec33[1] * cosf((fSlow44 * fTemp54)));
			fRec33[0] = ((fRec34[2] + (fSlow34 * (fTemp56 - fTemp57))) + (fSlow32 * (fRec34[0] - fRec33[2])));
			float fTemp58 = (fRec32[1] * cosf((fSlow45 * fTemp54)));
			fRec32[0] = ((fRec33[2] + (fSlow34 * (fTemp57 - fTemp58))) + (fSlow32 * (fRec33[0] - fRec32[2])));
			fRec31[0] = ((fSlow32 * fRec32[0]) + ((fSlow34 * fTemp58) + fRec32[2]));
			float fTemp59 = (iSlow3?fTemp52:((fSlow4 * (fSlow29 * fTemp53)) + (fSlow30 * fRec31[0])));
			float fTemp60 = (fTemp46 + fTemp59);
			fRec12[0] = (fTemp60 - (fConst44 * ((fConst52 * fRec12[2]) + (fConst53 * fRec12[1]))));
			fRec11[0] = ((fConst44 * (((fConst46 * fRec12[1]) + (fConst54 * fRec12[0])) + (fConst54 * fRec12[2]))) - (fConst42 * ((fConst55 * fRec11[2]) + (fConst56 * fRec11[1]))));
			fRec10[0] = ((fConst42 * (((fConst43 * fRec11[1]) + (fConst57 * fRec11[0])) + (fConst57 * fRec11[2]))) - (fConst38 * ((fConst58 * fRec10[2]) + (fConst59 * fRec10[1]))));
			float fTemp61 = (fConst38 * (((fConst41 * fRec10[1]) + (fConst60 * fRec10[0])) + (fConst60 * fRec10[2])));
			fRec9[0] = (fTemp61 - (fConst33 * ((fConst61 * fRec9[2]) + (fConst62 * fRec9[1]))));
			fRec8[0] = ((fConst33 * (((fConst35 * fRec9[1]) + (fConst63 * fRec9[0])) + (fConst63 * fRec9[2]))) - (fConst31 * ((fConst64 * fRec8[2]) + (fConst65 * fRec8[1]))));
			fRec7[0] = ((fConst31 * (((fConst32 * fRec8[1]) + (fConst66 * fRec8[0])) + (fConst66 * fRec8[2]))) - (fConst27 * ((fConst67 * fRec7[2]) + (fConst68 * fRec7[1]))));
			float fTemp62 = (fConst27 * (((fConst30 * fRec7[1]) + (fConst69 * fRec7[0])) + (fConst69 * fRec7[2])));
			fRec6[0] = (fTemp62 - (fConst22 * ((fConst70 * fRec6[2]) + (fConst71 * fRec6[1]))));
			fRec5[0] = ((fConst22 * (((fConst24 * fRec6[1]) + (fConst72 * fRec6[0])) + (fConst72 * fRec6[2]))) - (fConst20 * ((fConst73 * fRec5[2]) + (fConst74 * fRec5[1]))));
			fRec4[0] = ((fConst20 * (((fConst21 * fRec5[1]) + (fConst75 * fRec5[0])) + (fConst75 * fRec5[2]))) - (fConst16 * ((fConst76 * fRec4[2]) + (fConst77 * fRec4[1]))));
			float fTemp63 = (fConst16 * (((fConst19 * fRec4[1]) + (fConst78 * fRec4[0])) + (fConst78 * fRec4[2])));
			fRec3[0] = (fTemp63 - (fConst11 * ((fConst79 * fRec3[2]) + (fConst81 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst82 * fRec3[0])) + (fConst82 * fRec3[2]))) - (fConst8 * ((fConst83 * fRec2[2]) + (fConst84 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst85 * fRec2[0])) + (fConst85 * fRec2[2]))) - (fConst4 * ((fConst86 * fRec1[2]) + (fConst87 * fRec1[1]))));
			fRec0[0] = ((fSlow2 * fabsf((fConst4 * (((fConst7 * fRec1[1]) + (fConst88 * fRec1[0])) + (fConst88 * fRec1[2]))))) + (fSlow1 * fRec0[1]));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec0[0])))));
			fRec42[0] = (fTemp63 - (fConst105 * ((fConst108 * fRec42[2]) + (fConst109 * fRec42[1]))));
			fRec41[0] = ((fConst105 * (((fConst107 * fRec42[0]) + (fConst110 * fRec42[1])) + (fConst107 * fRec42[2]))) - (fConst103 * ((fConst111 * fRec41[2]) + (fConst112 * fRec41[1]))));
			fRec40[0] = ((fConst103 * (((fConst104 * fRec41[1]) + (fConst113 * fRec41[0])) + (fConst113 * fRec41[2]))) - (fConst101 * ((fConst114 * fRec40[2]) + (fConst115 * fRec40[1]))));
			float fTemp64 = (fConst101 * (((fConst102 * fRec40[1]) + (fConst116 * fRec40[0])) + (fConst116 * fRec40[2])));
			fRec39[0] = (fTemp64 - (fConst98 * ((fConst117 * fRec39[2]) + (fConst119 * fRec39[1]))));
			fRec38[0] = ((fConst98 * (((fConst100 * fRec39[1]) + (fConst120 * fRec39[0])) + (fConst120 * fRec39[2]))) - (fConst95 * ((fConst121 * fRec38[2]) + (fConst122 * fRec38[1]))));
			fRec37[0] = ((fConst95 * (((fConst97 * fRec38[1]) + (fConst123 * fRec38[0])) + (fConst123 * fRec38[2]))) - (fConst91 * ((fConst124 * fRec37[2]) + (fConst125 * fRec37[1]))));
			fRec36[0] = ((fSlow1 * fRec36[1]) + (fSlow2 * fabsf((fConst91 * (((fConst94 * fRec37[1]) + (fConst126 * fRec37[0])) + (fConst126 * fRec37[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec36[0])))));
			fRec49[0] = (fTemp64 - (fConst143 * ((fConst146 * fRec49[2]) + (fConst147 * fRec49[1]))));
			fRec48[0] = ((fConst143 * (((fConst145 * fRec49[1]) + (fConst148 * fRec49[0])) + (fConst148 * fRec49[2]))) - (fConst141 * ((fConst149 * fRec48[2]) + (fConst150 * fRec48[1]))));
			fRec47[0] = ((fConst141 * (((fConst142 * fRec48[1]) + (fConst151 * fRec48[0])) + (fConst151 * fRec48[2]))) - (fConst139 * ((fConst152 * fRec47[2]) + (fConst153 * fRec47[1]))));
			float fTemp65 = (fConst139 * (((fConst140 * fRec47[1]) + (fConst154 * fRec47[0])) + (fConst154 * fRec47[2])));
			fRec46[0] = (fTemp65 - (fConst136 * ((fConst155 * fRec46[2]) + (fConst157 * fRec46[1]))));
			fRec45[0] = ((fConst136 * (((fConst138 * fRec46[1]) + (fConst158 * fRec46[0])) + (fConst158 * fRec46[2]))) - (fConst133 * ((fConst159 * fRec45[2]) + (fConst160 * fRec45[1]))));
			fRec44[0] = ((fConst133 * (((fConst135 * fRec45[1]) + (fConst161 * fRec45[0])) + (fConst161 * fRec45[2]))) - (fConst129 * ((fConst162 * fRec44[2]) + (fConst163 * fRec44[1]))));
			fRec43[0] = ((fSlow1 * fRec43[1]) + (fSlow2 * fabsf((fConst129 * (((fConst132 * fRec44[1]) + (fConst164 * fRec44[0])) + (fConst164 * fRec44[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec43[0])))));
			fRec56[0] = (fTemp65 - (fConst181 * ((fConst184 * fRec56[2]) + (fConst185 * fRec56[1]))));
			fRec55[0] = ((fConst181 * (((fConst183 * fRec56[1]) + (fConst186 * fRec56[0])) + (fConst186 * fRec56[2]))) - (fConst179 * ((fConst187 * fRec55[2]) + (fConst188 * fRec55[1]))));
			fRec54[0] = ((fConst179 * (((fConst180 * fRec55[1]) + (fConst189 * fRec55[0])) + (fConst189 * fRec55[2]))) - (fConst177 * ((fConst190 * fRec54[2]) + (fConst191 * fRec54[1]))));
			float fTemp66 = (fConst177 * (((fConst178 * fRec54[1]) + (fConst192 * fRec54[0])) + (fConst192 * fRec54[2])));
			fRec53[0] = (fTemp66 - (fConst174 * ((fConst193 * fRec53[2]) + (fConst195 * fRec53[1]))));
			fRec52[0] = ((fConst174 * (((fConst176 * fRec53[1]) + (fConst196 * fRec53[0])) + (fConst196 * fRec53[2]))) - (fConst171 * ((fConst197 * fRec52[2]) + (fConst198 * fRec52[1]))));
			fRec51[0] = ((fConst171 * (((fConst173 * fRec52[1]) + (fConst199 * fRec52[0])) + (fConst199 * fRec52[2]))) - (fConst167 * ((fConst200 * fRec51[2]) + (fConst201 * fRec51[1]))));
			fRec50[0] = ((fSlow1 * fRec50[1]) + (fSlow2 * fabsf((fConst167 * (((fConst170 * fRec51[1]) + (fConst202 * fRec51[0])) + (fConst202 * fRec51[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec50[0])))));
			fRec63[0] = (fTemp66 - (fConst219 * ((fConst222 * fRec63[2]) + (fConst223 * fRec63[1]))));
			fRec62[0] = ((fConst219 * (((fConst221 * fRec63[1]) + (fConst224 * fRec63[0])) + (fConst224 * fRec63[2]))) - (fConst217 * ((fConst225 * fRec62[2]) + (fConst226 * fRec62[1]))));
			fRec61[0] = ((fConst217 * (((fConst218 * fRec62[1]) + (fConst227 * fRec62[0])) + (fConst227 * fRec62[2]))) - (fConst215 * ((fConst228 * fRec61[2]) + (fConst229 * fRec61[1]))));
			float fTemp67 = (fConst215 * (((fConst216 * fRec61[1]) + (fConst230 * fRec61[0])) + (fConst230 * fRec61[2])));
			fRec60[0] = (fTemp67 - (fConst212 * ((fConst231 * fRec60[2]) + (fConst233 * fRec60[1]))));
			fRec59[0] = ((fConst212 * (((fConst214 * fRec60[1]) + (fConst234 * fRec60[0])) + (fConst234 * fRec60[2]))) - (fConst209 * ((fConst235 * fRec59[2]) + (fConst236 * fRec59[1]))));
			fRec58[0] = ((fConst209 * (((fConst211 * fRec59[1]) + (fConst237 * fRec59[0])) + (fConst237 * fRec59[2]))) - (fConst205 * ((fConst238 * fRec58[2]) + (fConst239 * fRec58[1]))));
			fRec57[0] = ((fSlow1 * fRec57[1]) + (fSlow2 * fabsf((fConst205 * (((fConst208 * fRec58[1]) + (fConst240 * fRec58[0])) + (fConst240 * fRec58[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec57[0])))));
			fRec70[0] = (fTemp67 - (fConst257 * ((fConst260 * fRec70[2]) + (fConst261 * fRec70[1]))));
			fRec69[0] = ((fConst257 * (((fConst259 * fRec70[1]) + (fConst262 * fRec70[0])) + (fConst262 * fRec70[2]))) - (fConst255 * ((fConst263 * fRec69[2]) + (fConst264 * fRec69[1]))));
			fRec68[0] = ((fConst255 * (((fConst256 * fRec69[1]) + (fConst265 * fRec69[0])) + (fConst265 * fRec69[2]))) - (fConst253 * ((fConst266 * fRec68[2]) + (fConst267 * fRec68[1]))));
			float fTemp68 = (fConst253 * (((fConst254 * fRec68[1]) + (fConst268 * fRec68[0])) + (fConst268 * fRec68[2])));
			fRec67[0] = (fTemp68 - (fConst250 * ((fConst269 * fRec67[2]) + (fConst271 * fRec67[1]))));
			fRec66[0] = ((fConst250 * (((fConst252 * fRec67[1]) + (fConst272 * fRec67[0])) + (fConst272 * fRec67[2]))) - (fConst247 * ((fConst273 * fRec66[2]) + (fConst274 * fRec66[1]))));
			fRec65[0] = ((fConst247 * (((fConst249 * fRec66[1]) + (fConst275 * fRec66[0])) + (fConst275 * fRec66[2]))) - (fConst243 * ((fConst276 * fRec65[2]) + (fConst277 * fRec65[1]))));
			fRec64[0] = ((fSlow1 * fRec64[1]) + (fSlow2 * fabsf((fConst243 * (((fConst246 * fRec65[1]) + (fConst278 * fRec65[0])) + (fConst278 * fRec65[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec64[0])))));
			fRec77[0] = (fTemp68 - (fConst295 * ((fConst298 * fRec77[2]) + (fConst299 * fRec77[1]))));
			fRec76[0] = ((fConst295 * (((fConst297 * fRec77[1]) + (fConst300 * fRec77[0])) + (fConst300 * fRec77[2]))) - (fConst293 * ((fConst301 * fRec76[2]) + (fConst302 * fRec76[1]))));
			fRec75[0] = ((fConst293 * (((fConst294 * fRec76[1]) + (fConst303 * fRec76[0])) + (fConst303 * fRec76[2]))) - (fConst291 * ((fConst304 * fRec75[2]) + (fConst305 * fRec75[1]))));
			float fTemp69 = (fConst291 * (((fConst292 * fRec75[1]) + (fConst306 * fRec75[0])) + (fConst306 * fRec75[2])));
			fRec74[0] = (fTemp69 - (fConst288 * ((fConst307 * fRec74[2]) + (fConst309 * fRec74[1]))));
			fRec73[0] = ((fConst288 * (((fConst290 * fRec74[1]) + (fConst310 * fRec74[0])) + (fConst310 * fRec74[2]))) - (fConst285 * ((fConst311 * fRec73[2]) + (fConst312 * fRec73[1]))));
			fRec72[0] = ((fConst285 * (((fConst287 * fRec73[1]) + (fConst313 * fRec73[0])) + (fConst313 * fRec73[2]))) - (fConst281 * ((fConst314 * fRec72[2]) + (fConst315 * fRec72[1]))));
			fRec71[0] = ((fSlow1 * fRec71[1]) + (fSlow2 * fabsf((fConst281 * (((fConst284 * fRec72[1]) + (fConst316 * fRec72[0])) + (fConst316 * fRec72[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec71[0])))));
			fRec84[0] = (fTemp69 - (fConst333 * ((fConst336 * fRec84[2]) + (fConst337 * fRec84[1]))));
			fRec83[0] = ((fConst333 * (((fConst335 * fRec84[1]) + (fConst338 * fRec84[0])) + (fConst338 * fRec84[2]))) - (fConst331 * ((fConst339 * fRec83[2]) + (fConst340 * fRec83[1]))));
			fRec82[0] = ((fConst331 * (((fConst332 * fRec83[1]) + (fConst341 * fRec83[0])) + (fConst341 * fRec83[2]))) - (fConst329 * ((fConst342 * fRec82[2]) + (fConst343 * fRec82[1]))));
			float fTemp70 = (fConst329 * (((fConst330 * fRec82[1]) + (fConst344 * fRec82[0])) + (fConst344 * fRec82[2])));
			fRec81[0] = (fTemp70 - (fConst326 * ((fConst345 * fRec81[2]) + (fConst347 * fRec81[1]))));
			fRec80[0] = ((fConst326 * (((fConst328 * fRec81[1]) + (fConst348 * fRec81[0])) + (fConst348 * fRec81[2]))) - (fConst323 * ((fConst349 * fRec80[2]) + (fConst350 * fRec80[1]))));
			fRec79[0] = ((fConst323 * (((fConst325 * fRec80[1]) + (fConst351 * fRec80[0])) + (fConst351 * fRec80[2]))) - (fConst319 * ((fConst352 * fRec79[2]) + (fConst353 * fRec79[1]))));
			fRec78[0] = ((fSlow1 * fRec78[1]) + (fSlow2 * fabsf((fConst319 * (((fConst322 * fRec79[1]) + (fConst354 * fRec79[0])) + (fConst354 * fRec79[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec78[0])))));
			fRec88[0] = (fTemp60 - (fConst361 * ((fConst364 * fRec88[2]) + (fConst365 * fRec88[1]))));
			fRec87[0] = ((fConst361 * (((fConst363 * fRec88[1]) + (fConst366 * fRec88[0])) + (fConst366 * fRec88[2]))) - (fConst358 * ((fConst367 * fRec87[2]) + (fConst368 * fRec87[1]))));
			fRec86[0] = ((fConst358 * (((fConst360 * fRec87[1]) + (fConst369 * fRec87[0])) + (fConst369 * fRec87[2]))) - (fConst355 * ((fConst370 * fRec86[2]) + (fConst371 * fRec86[1]))));
			fRec85[0] = ((fSlow1 * fRec85[1]) + (fSlow2 * fabsf((fConst355 * (((fConst357 * fRec86[1]) + (fConst372 * fRec86[0])) + (fConst372 * fRec86[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec85[0])))));
			fRec92[0] = (fTemp61 - (fConst379 * ((fConst382 * fRec92[2]) + (fConst383 * fRec92[1]))));
			fRec91[0] = ((fConst379 * (((fConst381 * fRec92[1]) + (fConst384 * fRec92[0])) + (fConst384 * fRec92[2]))) - (fConst376 * ((fConst385 * fRec91[2]) + (fConst386 * fRec91[1]))));
			fRec90[0] = ((fConst376 * (((fConst378 * fRec91[1]) + (fConst387 * fRec91[0])) + (fConst387 * fRec91[2]))) - (fConst373 * ((fConst388 * fRec90[2]) + (fConst389 * fRec90[1]))));
			fRec89[0] = ((fSlow1 * fRec89[1]) + (fSlow2 * fabsf((fConst373 * (((fConst375 * fRec90[1]) + (fConst390 * fRec90[0])) + (fConst390 * fRec90[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec89[0])))));
			fRec96[0] = (fTemp62 - (fConst397 * ((fConst400 * fRec96[2]) + (fConst401 * fRec96[1]))));
			fRec95[0] = ((fConst397 * (((fConst399 * fRec96[1]) + (fConst402 * fRec96[0])) + (fConst402 * fRec96[2]))) - (fConst394 * ((fConst403 * fRec95[2]) + (fConst404 * fRec95[1]))));
			fRec94[0] = ((fConst394 * (((fConst396 * fRec95[1]) + (fConst405 * fRec95[0])) + (fConst405 * fRec95[2]))) - (fConst391 * ((fConst406 * fRec94[2]) + (fConst407 * fRec94[1]))));
			fRec93[0] = ((fSlow1 * fRec93[1]) + (fSlow2 * fabsf((fConst391 * (((fConst393 * fRec94[1]) + (fConst408 * fRec94[0])) + (fConst408 * fRec94[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec93[0])))));
			fRec103[0] = (fTemp70 - (fConst425 * ((fConst428 * fRec103[2]) + (fConst429 * fRec103[1]))));
			fRec102[0] = ((fConst425 * (((fConst427 * fRec103[1]) + (fConst430 * fRec103[0])) + (fConst430 * fRec103[2]))) - (fConst423 * ((fConst431 * fRec102[2]) + (fConst432 * fRec102[1]))));
			fRec101[0] = ((fConst423 * (((fConst424 * fRec102[1]) + (fConst433 * fRec102[0])) + (fConst433 * fRec102[2]))) - (fConst421 * ((fConst434 * fRec101[2]) + (fConst435 * fRec101[1]))));
			float fTemp71 = (fConst421 * (((fConst422 * fRec101[1]) + (fConst436 * fRec101[0])) + (fConst436 * fRec101[2])));
			fRec100[0] = (fTemp71 - (fConst418 * ((fConst437 * fRec100[2]) + (fConst439 * fRec100[1]))));
			fRec99[0] = ((fConst418 * (((fConst420 * fRec100[1]) + (fConst440 * fRec100[0])) + (fConst440 * fRec100[2]))) - (fConst415 * ((fConst441 * fRec99[2]) + (fConst442 * fRec99[1]))));
			fRec98[0] = ((fConst415 * (((fConst417 * fRec99[1]) + (fConst443 * fRec99[0])) + (fConst443 * fRec99[2]))) - (fConst411 * ((fConst444 * fRec98[2]) + (fConst445 * fRec98[1]))));
			fRec97[0] = ((fSlow1 * fRec97[1]) + (fSlow2 * fabsf((fConst411 * (((fConst414 * fRec98[1]) + (fConst446 * fRec98[0])) + (fConst446 * fRec98[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec97[0])))));
			fRec110[0] = (fTemp71 - (fConst463 * ((fConst466 * fRec110[2]) + (fConst467 * fRec110[1]))));
			fRec109[0] = ((fConst463 * (((fConst465 * fRec110[1]) + (fConst468 * fRec110[0])) + (fConst468 * fRec110[2]))) - (fConst461 * ((fConst469 * fRec109[2]) + (fConst470 * fRec109[1]))));
			fRec108[0] = ((fConst461 * (((fConst462 * fRec109[1]) + (fConst471 * fRec109[0])) + (fConst471 * fRec109[2]))) - (fConst459 * ((fConst472 * fRec108[2]) + (fConst473 * fRec108[1]))));
			float fTemp72 = (fConst459 * (((fConst460 * fRec108[1]) + (fConst474 * fRec108[0])) + (fConst474 * fRec108[2])));
			fRec107[0] = (fTemp72 - (fConst456 * ((fConst475 * fRec107[2]) + (fConst477 * fRec107[1]))));
			fRec106[0] = ((fConst456 * (((fConst458 * fRec107[1]) + (fConst478 * fRec107[0])) + (fConst478 * fRec107[2]))) - (fConst453 * ((fConst479 * fRec106[2]) + (fConst480 * fRec106[1]))));
			fRec105[0] = ((fConst453 * (((fConst455 * fRec106[1]) + (fConst481 * fRec106[0])) + (fConst481 * fRec106[2]))) - (fConst449 * ((fConst482 * fRec105[2]) + (fConst483 * fRec105[1]))));
			fRec104[0] = ((fSlow1 * fRec104[1]) + (fSlow2 * fabsf((fConst449 * (((fConst452 * fRec105[1]) + (fConst484 * fRec105[0])) + (fConst484 * fRec105[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec104[0])))));
			fRec117[0] = (fTemp72 - (fConst501 * ((fConst504 * fRec117[2]) + (fConst505 * fRec117[1]))));
			fRec116[0] = ((fConst501 * (((fConst503 * fRec117[1]) + (fConst506 * fRec117[0])) + (fConst506 * fRec117[2]))) - (fConst499 * ((fConst507 * fRec116[2]) + (fConst508 * fRec116[1]))));
			fRec115[0] = ((fConst499 * (((fConst500 * fRec116[1]) + (fConst509 * fRec116[0])) + (fConst509 * fRec116[2]))) - (fConst497 * ((fConst510 * fRec115[2]) + (fConst511 * fRec115[1]))));
			float fTemp73 = (fConst497 * (((fConst498 * fRec115[1]) + (fConst512 * fRec115[0])) + (fConst512 * fRec115[2])));
			fRec114[0] = (fTemp73 - (fConst494 * ((fConst513 * fRec114[2]) + (fConst515 * fRec114[1]))));
			fRec113[0] = ((fConst494 * (((fConst496 * fRec114[1]) + (fConst516 * fRec114[0])) + (fConst516 * fRec114[2]))) - (fConst491 * ((fConst517 * fRec113[2]) + (fConst518 * fRec113[1]))));
			fRec112[0] = ((fConst491 * (((fConst493 * fRec113[1]) + (fConst519 * fRec113[0])) + (fConst519 * fRec113[2]))) - (fConst487 * ((fConst520 * fRec112[2]) + (fConst521 * fRec112[1]))));
			fRec111[0] = ((fSlow1 * fRec111[1]) + (fSlow2 * fabsf((fConst487 * (((fConst490 * fRec112[1]) + (fConst522 * fRec112[0])) + (fConst522 * fRec112[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec111[0])))));
			fRec121[0] = (fTemp73 - (fConst527 * ((fConst530 * fRec121[2]) + (fConst531 * fRec121[1]))));
			fRec120[0] = ((fConst527 * (((fConst529 * fRec121[1]) + (fConst532 * fRec121[0])) + (fConst532 * fRec121[2]))) - (fConst525 * ((fConst533 * fRec120[2]) + (fConst534 * fRec120[1]))));
			fRec119[0] = ((fConst525 * (((fConst526 * fRec120[1]) + (fConst535 * fRec120[0])) + (fConst535 * fRec120[2]))) - (fConst523 * ((fConst536 * fRec119[2]) + (fConst537 * fRec119[1]))));
			fRec118[0] = ((fSlow1 * fRec118[1]) + (fSlow2 * fabsf((fConst523 * (((fConst524 * fRec119[1]) + (fConst538 * fRec119[0])) + (fConst538 * fRec119[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec118[0])))));
			output0[i] = FAUSTFLOAT(fTemp46);
			output1[i] = FAUSTFLOAT(fTemp59);
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fVec1[1] = fVec1[0];
			fRec15[1] = fRec15[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec17[1] = fRec17[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec18[1] = fRec18[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			fRec19[1] = fRec19[0];
			iRec20[1] = iRec20[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec21[j1] = fRec21[(j1 - 1)];
				
			}
			IOTA = (IOTA + 1);
			fRec22[1] = fRec22[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec30[1] = fRec30[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
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
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
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
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[1] = fRec57[0];
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
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[1] = fRec97[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[1] = fRec104[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[2] = fRec116[1];
			fRec116[1] = fRec116[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec114[2] = fRec114[1];
			fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[1] = fRec111[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fRec119[2] = fRec119[1];
			fRec119[1] = fRec119[0];
			fRec118[1] = fRec118[0];
			
		}
		
	}

	
};

#endif
