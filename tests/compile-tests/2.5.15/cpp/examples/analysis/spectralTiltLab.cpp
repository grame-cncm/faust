/* ------------------------------------------------------------
name: "spectralTiltLab"
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
float mydsp_faustpower9_f(float value) {
	return ((((((((value * value) * value) * value) * value) * value) * value) * value) * value);
	
}
float mydsp_faustpower8_f(float value) {
	return (((((((value * value) * value) * value) * value) * value) * value) * value);
	
}
float mydsp_faustpower7_f(float value) {
	return ((((((value * value) * value) * value) * value) * value) * value);
	
}
float mydsp_faustpower6_f(float value) {
	return (((((value * value) * value) * value) * value) * value);
	
}
float mydsp_faustpower5_f(float value) {
	return ((((value * value) * value) * value) * value);
	
}
float mydsp_faustpower4_f(float value) {
	return (((value * value) * value) * value);
	
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
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fConst15;
	FAUSTFLOAT fVslider0;
	float fRec14[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fEntry0;
	float fConst16;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec16[2];
	float fVec1[2];
	float fRec15[2];
	float fConst17;
	float fVec2[2];
	float fConst18;
	float fVec3[2];
	float fVec4[2];
	float fConst19;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec17[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec18[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	FAUSTFLOAT fCheckbox3;
	int iRec19[2];
	float fRec20[4];
	float fVec22[2];
	float fRec13[2];
	float fVec23[2];
	float fRec12[2];
	float fVec24[2];
	float fRec11[2];
	float fVec25[2];
	float fRec10[2];
	float fVec26[2];
	float fRec9[2];
	float fVec27[2];
	float fRec8[2];
	float fVec28[2];
	float fRec7[2];
	float fVec29[2];
	float fRec6[2];
	float fVec30[2];
	float fRec5[2];
	float fVec31[2];
	float fRec4[2];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec3[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec2[3];
	float fConst26;
	float fConst27;
	float fConst28;
	float fRec1[3];
	float fConst29;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fRec27[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec26[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec25[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec24[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec23[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec22[3];
	float fConst67;
	float fRec21[2];
	FAUSTFLOAT fVbargraph1;
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
	float fRec34[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec33[3];
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec32[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec31[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec30[3];
	float fConst102;
	float fConst103;
	float fConst104;
	float fRec29[3];
	float fConst105;
	float fRec28[2];
	FAUSTFLOAT fVbargraph2;
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
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec41[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec40[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec39[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec38[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec37[3];
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec36[3];
	float fConst143;
	float fRec35[2];
	FAUSTFLOAT fVbargraph3;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
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
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec48[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec47[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fRec46[3];
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec45[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec44[3];
	float fConst178;
	float fConst179;
	float fConst180;
	float fRec43[3];
	float fConst181;
	float fRec42[2];
	FAUSTFLOAT fVbargraph4;
	float fConst182;
	float fConst183;
	float fConst184;
	float fConst185;
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
	float fConst197;
	float fConst198;
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec55[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec54[3];
	float fConst206;
	float fConst207;
	float fConst208;
	float fRec53[3];
	float fConst209;
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec52[3];
	float fConst213;
	float fConst214;
	float fConst215;
	float fRec51[3];
	float fConst216;
	float fConst217;
	float fConst218;
	float fRec50[3];
	float fConst219;
	float fRec49[2];
	FAUSTFLOAT fVbargraph5;
	float fConst220;
	float fConst221;
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
	float fRec62[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fRec61[3];
	float fConst244;
	float fConst245;
	float fConst246;
	float fRec60[3];
	float fConst247;
	float fConst248;
	float fConst249;
	float fConst250;
	float fRec59[3];
	float fConst251;
	float fConst252;
	float fConst253;
	float fRec58[3];
	float fConst254;
	float fConst255;
	float fConst256;
	float fRec57[3];
	float fConst257;
	float fRec56[2];
	FAUSTFLOAT fVbargraph6;
	float fConst258;
	float fConst259;
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
	float fRec69[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fRec68[3];
	float fConst282;
	float fConst283;
	float fConst284;
	float fRec67[3];
	float fConst285;
	float fConst286;
	float fConst287;
	float fConst288;
	float fRec66[3];
	float fConst289;
	float fConst290;
	float fConst291;
	float fRec65[3];
	float fConst292;
	float fConst293;
	float fConst294;
	float fRec64[3];
	float fConst295;
	float fRec63[2];
	FAUSTFLOAT fVbargraph7;
	float fConst296;
	float fConst297;
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
	float fRec76[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fRec75[3];
	float fConst320;
	float fConst321;
	float fConst322;
	float fRec74[3];
	float fConst323;
	float fConst324;
	float fConst325;
	float fConst326;
	float fRec73[3];
	float fConst327;
	float fConst328;
	float fConst329;
	float fRec72[3];
	float fConst330;
	float fConst331;
	float fConst332;
	float fRec71[3];
	float fConst333;
	float fRec70[2];
	FAUSTFLOAT fVbargraph8;
	float fConst334;
	float fConst335;
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
	float fRec83[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fRec82[3];
	float fConst358;
	float fConst359;
	float fConst360;
	float fRec81[3];
	float fConst361;
	float fConst362;
	float fConst363;
	float fConst364;
	float fRec80[3];
	float fConst365;
	float fConst366;
	float fConst367;
	float fRec79[3];
	float fConst368;
	float fConst369;
	float fConst370;
	float fRec78[3];
	float fConst371;
	float fRec77[2];
	FAUSTFLOAT fVbargraph9;
	float fConst372;
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
	float fConst384;
	float fConst385;
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fConst390;
	float fConst391;
	float fConst392;
	float fRec90[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fRec89[3];
	float fConst396;
	float fConst397;
	float fConst398;
	float fRec88[3];
	float fConst399;
	float fConst400;
	float fConst401;
	float fConst402;
	float fRec87[3];
	float fConst403;
	float fConst404;
	float fConst405;
	float fRec86[3];
	float fConst406;
	float fConst407;
	float fConst408;
	float fRec85[3];
	float fConst409;
	float fRec84[2];
	FAUSTFLOAT fVbargraph10;
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
	float fConst430;
	float fRec97[3];
	float fConst431;
	float fConst432;
	float fConst433;
	float fRec96[3];
	float fConst434;
	float fConst435;
	float fConst436;
	float fRec95[3];
	float fConst437;
	float fConst438;
	float fConst439;
	float fConst440;
	float fRec94[3];
	float fConst441;
	float fConst442;
	float fConst443;
	float fRec93[3];
	float fConst444;
	float fConst445;
	float fConst446;
	float fRec92[3];
	float fConst447;
	float fRec91[2];
	FAUSTFLOAT fVbargraph11;
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
	float fConst468;
	float fRec104[3];
	float fConst469;
	float fConst470;
	float fConst471;
	float fRec103[3];
	float fConst472;
	float fConst473;
	float fConst474;
	float fRec102[3];
	float fConst475;
	float fConst476;
	float fConst477;
	float fConst478;
	float fRec101[3];
	float fConst479;
	float fConst480;
	float fConst481;
	float fRec100[3];
	float fConst482;
	float fConst483;
	float fConst484;
	float fRec99[3];
	float fConst485;
	float fRec98[2];
	FAUSTFLOAT fVbargraph12;
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
	float fConst506;
	float fRec111[3];
	float fConst507;
	float fConst508;
	float fConst509;
	float fRec110[3];
	float fConst510;
	float fConst511;
	float fConst512;
	float fRec109[3];
	float fConst513;
	float fConst514;
	float fConst515;
	float fConst516;
	float fRec108[3];
	float fConst517;
	float fConst518;
	float fConst519;
	float fRec107[3];
	float fConst520;
	float fConst521;
	float fConst522;
	float fRec106[3];
	float fConst523;
	float fRec105[2];
	FAUSTFLOAT fVbargraph13;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fRec115[3];
	float fConst533;
	float fConst534;
	float fConst535;
	float fRec114[3];
	float fConst536;
	float fConst537;
	float fConst538;
	float fRec113[3];
	float fConst539;
	float fRec112[2];
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
		m->declare("name", "spectralTiltLab");
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
		return 1;
		
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
		fConst2 = tanf((50265.4844f / fConst0));
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
		fConst14 = (3.14159274f / fConst0);
		fConst15 = (1.0f / tanf((0.5f / fConst0)));
		fConst16 = (1.0f / fConst0);
		fConst17 = (0.25f * fConst0);
		fConst18 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst19 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst20 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst21 = (1.0f / fConst5);
		fConst22 = (2.0f * (4.07678175f - fConst21));
		fConst23 = (fConst12 + 0.000407678192f);
		fConst24 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst25 = (2.0f * (1.4500711f - fConst21));
		fConst26 = (fConst9 + 1.4500711f);
		fConst27 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst28 = (2.0f * (0.935140193f - fConst21));
		fConst29 = (fConst6 + 0.935140193f);
		fConst30 = tanf((31665.2695f / fConst0));
		fConst31 = (1.0f / fConst30);
		fConst32 = (1.0f / (((fConst31 + 0.157482162f) / fConst30) + 0.935140193f));
		fConst33 = mydsp_faustpower2_f(fConst30);
		fConst34 = (50.0638084f / fConst33);
		fConst35 = (2.0f * (0.935140193f - fConst34));
		fConst36 = (1.0f / (((fConst31 + 0.743130445f) / fConst30) + 1.4500711f));
		fConst37 = (11.0520525f / fConst33);
		fConst38 = (2.0f * (1.4500711f - fConst37));
		fConst39 = (1.0f / (((fConst31 + 3.18972731f) / fConst30) + 4.07678175f));
		fConst40 = (0.00176617282f / fConst33);
		fConst41 = (2.0f * (0.000407678192f - fConst40));
		fConst42 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst43 = (2.0f * (53.5361519f - fConst21));
		fConst44 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst45 = (2.0f * (7.62173128f - fConst21));
		fConst46 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst47 = (9.99999975e-05f / fConst5);
		fConst48 = (2.0f * (0.000433227193f - fConst47));
		fConst49 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst50 = (2.0f * (0.245291501f - fConst21));
		fConst51 = (fConst47 + 0.000433227193f);
		fConst52 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst53 = (2.0f * (0.689621389f - fConst21));
		fConst54 = (fConst21 + 7.62173128f);
		fConst55 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst56 = (2.0f * (1.06935835f - fConst21));
		fConst57 = (fConst21 + 53.5361519f);
		fConst58 = (((fConst31 + -3.18972731f) / fConst30) + 4.07678175f);
		fConst59 = (1.0f / fConst33);
		fConst60 = (2.0f * (4.07678175f - fConst59));
		fConst61 = (fConst40 + 0.000407678192f);
		fConst62 = (((fConst31 + -0.743130445f) / fConst30) + 1.4500711f);
		fConst63 = (2.0f * (1.4500711f - fConst59));
		fConst64 = (fConst37 + 1.4500711f);
		fConst65 = (((fConst31 + -0.157482162f) / fConst30) + 0.935140193f);
		fConst66 = (2.0f * (0.935140193f - fConst59));
		fConst67 = (fConst34 + 0.935140193f);
		fConst68 = tanf((19947.8691f / fConst0));
		fConst69 = (1.0f / fConst68);
		fConst70 = (1.0f / (((fConst69 + 0.157482162f) / fConst68) + 0.935140193f));
		fConst71 = mydsp_faustpower2_f(fConst68);
		fConst72 = (50.0638084f / fConst71);
		fConst73 = (2.0f * (0.935140193f - fConst72));
		fConst74 = (1.0f / (((fConst69 + 0.743130445f) / fConst68) + 1.4500711f));
		fConst75 = (11.0520525f / fConst71);
		fConst76 = (2.0f * (1.4500711f - fConst75));
		fConst77 = (1.0f / (((fConst69 + 3.18972731f) / fConst68) + 4.07678175f));
		fConst78 = (0.00176617282f / fConst71);
		fConst79 = (2.0f * (0.000407678192f - fConst78));
		fConst80 = (1.0f / (((fConst31 + 0.168404877f) / fConst30) + 1.06935835f));
		fConst81 = (2.0f * (53.5361519f - fConst59));
		fConst82 = (1.0f / (((fConst31 + 0.51247865f) / fConst30) + 0.689621389f));
		fConst83 = (2.0f * (7.62173128f - fConst59));
		fConst84 = (1.0f / (((fConst31 + 0.782413065f) / fConst30) + 0.245291501f));
		fConst85 = (9.99999975e-05f / fConst33);
		fConst86 = (2.0f * (0.000433227193f - fConst85));
		fConst87 = (((fConst31 + -0.782413065f) / fConst30) + 0.245291501f);
		fConst88 = (2.0f * (0.245291501f - fConst59));
		fConst89 = (fConst85 + 0.000433227193f);
		fConst90 = (((fConst31 + -0.51247865f) / fConst30) + 0.689621389f);
		fConst91 = (2.0f * (0.689621389f - fConst59));
		fConst92 = (fConst59 + 7.62173128f);
		fConst93 = (((fConst31 + -0.168404877f) / fConst30) + 1.06935835f);
		fConst94 = (2.0f * (1.06935835f - fConst59));
		fConst95 = (fConst59 + 53.5361519f);
		fConst96 = (((fConst69 + -3.18972731f) / fConst68) + 4.07678175f);
		fConst97 = (1.0f / fConst71);
		fConst98 = (2.0f * (4.07678175f - fConst97));
		fConst99 = (fConst78 + 0.000407678192f);
		fConst100 = (((fConst69 + -0.743130445f) / fConst68) + 1.4500711f);
		fConst101 = (2.0f * (1.4500711f - fConst97));
		fConst102 = (fConst75 + 1.4500711f);
		fConst103 = (((fConst69 + -0.157482162f) / fConst68) + 0.935140193f);
		fConst104 = (2.0f * (0.935140193f - fConst97));
		fConst105 = (fConst72 + 0.935140193f);
		fConst106 = tanf((12566.3711f / fConst0));
		fConst107 = (1.0f / fConst106);
		fConst108 = (1.0f / (((fConst107 + 0.157482162f) / fConst106) + 0.935140193f));
		fConst109 = mydsp_faustpower2_f(fConst106);
		fConst110 = (50.0638084f / fConst109);
		fConst111 = (2.0f * (0.935140193f - fConst110));
		fConst112 = (1.0f / (((fConst107 + 0.743130445f) / fConst106) + 1.4500711f));
		fConst113 = (11.0520525f / fConst109);
		fConst114 = (2.0f * (1.4500711f - fConst113));
		fConst115 = (1.0f / (((fConst107 + 3.18972731f) / fConst106) + 4.07678175f));
		fConst116 = (0.00176617282f / fConst109);
		fConst117 = (2.0f * (0.000407678192f - fConst116));
		fConst118 = (1.0f / (((fConst69 + 0.168404877f) / fConst68) + 1.06935835f));
		fConst119 = (2.0f * (53.5361519f - fConst97));
		fConst120 = (1.0f / (((fConst69 + 0.51247865f) / fConst68) + 0.689621389f));
		fConst121 = (2.0f * (7.62173128f - fConst97));
		fConst122 = (1.0f / (((fConst69 + 0.782413065f) / fConst68) + 0.245291501f));
		fConst123 = (9.99999975e-05f / fConst71);
		fConst124 = (2.0f * (0.000433227193f - fConst123));
		fConst125 = (((fConst69 + -0.782413065f) / fConst68) + 0.245291501f);
		fConst126 = (2.0f * (0.245291501f - fConst97));
		fConst127 = (fConst123 + 0.000433227193f);
		fConst128 = (((fConst69 + -0.51247865f) / fConst68) + 0.689621389f);
		fConst129 = (2.0f * (0.689621389f - fConst97));
		fConst130 = (fConst97 + 7.62173128f);
		fConst131 = (((fConst69 + -0.168404877f) / fConst68) + 1.06935835f);
		fConst132 = (2.0f * (1.06935835f - fConst97));
		fConst133 = (fConst97 + 53.5361519f);
		fConst134 = (((fConst107 + -3.18972731f) / fConst106) + 4.07678175f);
		fConst135 = (1.0f / fConst109);
		fConst136 = (2.0f * (4.07678175f - fConst135));
		fConst137 = (fConst116 + 0.000407678192f);
		fConst138 = (((fConst107 + -0.743130445f) / fConst106) + 1.4500711f);
		fConst139 = (2.0f * (1.4500711f - fConst135));
		fConst140 = (fConst113 + 1.4500711f);
		fConst141 = (((fConst107 + -0.157482162f) / fConst106) + 0.935140193f);
		fConst142 = (2.0f * (0.935140193f - fConst135));
		fConst143 = (fConst110 + 0.935140193f);
		fConst144 = tanf((7916.31738f / fConst0));
		fConst145 = (1.0f / fConst144);
		fConst146 = (1.0f / (((fConst145 + 0.157482162f) / fConst144) + 0.935140193f));
		fConst147 = mydsp_faustpower2_f(fConst144);
		fConst148 = (50.0638084f / fConst147);
		fConst149 = (2.0f * (0.935140193f - fConst148));
		fConst150 = (1.0f / (((fConst145 + 0.743130445f) / fConst144) + 1.4500711f));
		fConst151 = (11.0520525f / fConst147);
		fConst152 = (2.0f * (1.4500711f - fConst151));
		fConst153 = (1.0f / (((fConst145 + 3.18972731f) / fConst144) + 4.07678175f));
		fConst154 = (0.00176617282f / fConst147);
		fConst155 = (2.0f * (0.000407678192f - fConst154));
		fConst156 = (1.0f / (((fConst107 + 0.168404877f) / fConst106) + 1.06935835f));
		fConst157 = (2.0f * (53.5361519f - fConst135));
		fConst158 = (1.0f / (((fConst107 + 0.51247865f) / fConst106) + 0.689621389f));
		fConst159 = (2.0f * (7.62173128f - fConst135));
		fConst160 = (1.0f / (((fConst107 + 0.782413065f) / fConst106) + 0.245291501f));
		fConst161 = (9.99999975e-05f / fConst109);
		fConst162 = (2.0f * (0.000433227193f - fConst161));
		fConst163 = (((fConst107 + -0.782413065f) / fConst106) + 0.245291501f);
		fConst164 = (2.0f * (0.245291501f - fConst135));
		fConst165 = (fConst161 + 0.000433227193f);
		fConst166 = (((fConst107 + -0.51247865f) / fConst106) + 0.689621389f);
		fConst167 = (2.0f * (0.689621389f - fConst135));
		fConst168 = (fConst135 + 7.62173128f);
		fConst169 = (((fConst107 + -0.168404877f) / fConst106) + 1.06935835f);
		fConst170 = (2.0f * (1.06935835f - fConst135));
		fConst171 = (fConst135 + 53.5361519f);
		fConst172 = (((fConst145 + -3.18972731f) / fConst144) + 4.07678175f);
		fConst173 = (1.0f / fConst147);
		fConst174 = (2.0f * (4.07678175f - fConst173));
		fConst175 = (fConst154 + 0.000407678192f);
		fConst176 = (((fConst145 + -0.743130445f) / fConst144) + 1.4500711f);
		fConst177 = (2.0f * (1.4500711f - fConst173));
		fConst178 = (fConst151 + 1.4500711f);
		fConst179 = (((fConst145 + -0.157482162f) / fConst144) + 0.935140193f);
		fConst180 = (2.0f * (0.935140193f - fConst173));
		fConst181 = (fConst148 + 0.935140193f);
		fConst182 = tanf((4986.96729f / fConst0));
		fConst183 = (1.0f / fConst182);
		fConst184 = (1.0f / (((fConst183 + 0.157482162f) / fConst182) + 0.935140193f));
		fConst185 = mydsp_faustpower2_f(fConst182);
		fConst186 = (50.0638084f / fConst185);
		fConst187 = (2.0f * (0.935140193f - fConst186));
		fConst188 = (1.0f / (((fConst183 + 0.743130445f) / fConst182) + 1.4500711f));
		fConst189 = (11.0520525f / fConst185);
		fConst190 = (2.0f * (1.4500711f - fConst189));
		fConst191 = (1.0f / (((fConst183 + 3.18972731f) / fConst182) + 4.07678175f));
		fConst192 = (0.00176617282f / fConst185);
		fConst193 = (2.0f * (0.000407678192f - fConst192));
		fConst194 = (1.0f / (((fConst145 + 0.168404877f) / fConst144) + 1.06935835f));
		fConst195 = (2.0f * (53.5361519f - fConst173));
		fConst196 = (1.0f / (((fConst145 + 0.51247865f) / fConst144) + 0.689621389f));
		fConst197 = (2.0f * (7.62173128f - fConst173));
		fConst198 = (1.0f / (((fConst145 + 0.782413065f) / fConst144) + 0.245291501f));
		fConst199 = (9.99999975e-05f / fConst147);
		fConst200 = (2.0f * (0.000433227193f - fConst199));
		fConst201 = (((fConst145 + -0.782413065f) / fConst144) + 0.245291501f);
		fConst202 = (2.0f * (0.245291501f - fConst173));
		fConst203 = (fConst199 + 0.000433227193f);
		fConst204 = (((fConst145 + -0.51247865f) / fConst144) + 0.689621389f);
		fConst205 = (2.0f * (0.689621389f - fConst173));
		fConst206 = (fConst173 + 7.62173128f);
		fConst207 = (((fConst145 + -0.168404877f) / fConst144) + 1.06935835f);
		fConst208 = (2.0f * (1.06935835f - fConst173));
		fConst209 = (fConst173 + 53.5361519f);
		fConst210 = (((fConst183 + -3.18972731f) / fConst182) + 4.07678175f);
		fConst211 = (1.0f / fConst185);
		fConst212 = (2.0f * (4.07678175f - fConst211));
		fConst213 = (fConst192 + 0.000407678192f);
		fConst214 = (((fConst183 + -0.743130445f) / fConst182) + 1.4500711f);
		fConst215 = (2.0f * (1.4500711f - fConst211));
		fConst216 = (fConst189 + 1.4500711f);
		fConst217 = (((fConst183 + -0.157482162f) / fConst182) + 0.935140193f);
		fConst218 = (2.0f * (0.935140193f - fConst211));
		fConst219 = (fConst186 + 0.935140193f);
		fConst220 = tanf((3141.59277f / fConst0));
		fConst221 = (1.0f / fConst220);
		fConst222 = (1.0f / (((fConst221 + 0.157482162f) / fConst220) + 0.935140193f));
		fConst223 = mydsp_faustpower2_f(fConst220);
		fConst224 = (50.0638084f / fConst223);
		fConst225 = (2.0f * (0.935140193f - fConst224));
		fConst226 = (1.0f / (((fConst221 + 0.743130445f) / fConst220) + 1.4500711f));
		fConst227 = (11.0520525f / fConst223);
		fConst228 = (2.0f * (1.4500711f - fConst227));
		fConst229 = (1.0f / (((fConst221 + 3.18972731f) / fConst220) + 4.07678175f));
		fConst230 = (0.00176617282f / fConst223);
		fConst231 = (2.0f * (0.000407678192f - fConst230));
		fConst232 = (1.0f / (((fConst183 + 0.168404877f) / fConst182) + 1.06935835f));
		fConst233 = (2.0f * (53.5361519f - fConst211));
		fConst234 = (1.0f / (((fConst183 + 0.51247865f) / fConst182) + 0.689621389f));
		fConst235 = (2.0f * (7.62173128f - fConst211));
		fConst236 = (1.0f / (((fConst183 + 0.782413065f) / fConst182) + 0.245291501f));
		fConst237 = (9.99999975e-05f / fConst185);
		fConst238 = (2.0f * (0.000433227193f - fConst237));
		fConst239 = (((fConst183 + -0.782413065f) / fConst182) + 0.245291501f);
		fConst240 = (2.0f * (0.245291501f - fConst211));
		fConst241 = (fConst237 + 0.000433227193f);
		fConst242 = (((fConst183 + -0.51247865f) / fConst182) + 0.689621389f);
		fConst243 = (2.0f * (0.689621389f - fConst211));
		fConst244 = (fConst211 + 7.62173128f);
		fConst245 = (((fConst183 + -0.168404877f) / fConst182) + 1.06935835f);
		fConst246 = (2.0f * (1.06935835f - fConst211));
		fConst247 = (fConst211 + 53.5361519f);
		fConst248 = (((fConst221 + -3.18972731f) / fConst220) + 4.07678175f);
		fConst249 = (1.0f / fConst223);
		fConst250 = (2.0f * (4.07678175f - fConst249));
		fConst251 = (fConst230 + 0.000407678192f);
		fConst252 = (((fConst221 + -0.743130445f) / fConst220) + 1.4500711f);
		fConst253 = (2.0f * (1.4500711f - fConst249));
		fConst254 = (fConst227 + 1.4500711f);
		fConst255 = (((fConst221 + -0.157482162f) / fConst220) + 0.935140193f);
		fConst256 = (2.0f * (0.935140193f - fConst249));
		fConst257 = (fConst224 + 0.935140193f);
		fConst258 = tanf((1979.07935f / fConst0));
		fConst259 = (1.0f / fConst258);
		fConst260 = (1.0f / (((fConst259 + 0.157482162f) / fConst258) + 0.935140193f));
		fConst261 = mydsp_faustpower2_f(fConst258);
		fConst262 = (50.0638084f / fConst261);
		fConst263 = (2.0f * (0.935140193f - fConst262));
		fConst264 = (1.0f / (((fConst259 + 0.743130445f) / fConst258) + 1.4500711f));
		fConst265 = (11.0520525f / fConst261);
		fConst266 = (2.0f * (1.4500711f - fConst265));
		fConst267 = (1.0f / (((fConst259 + 3.18972731f) / fConst258) + 4.07678175f));
		fConst268 = (0.00176617282f / fConst261);
		fConst269 = (2.0f * (0.000407678192f - fConst268));
		fConst270 = (1.0f / (((fConst221 + 0.168404877f) / fConst220) + 1.06935835f));
		fConst271 = (2.0f * (53.5361519f - fConst249));
		fConst272 = (1.0f / (((fConst221 + 0.51247865f) / fConst220) + 0.689621389f));
		fConst273 = (2.0f * (7.62173128f - fConst249));
		fConst274 = (1.0f / (((fConst221 + 0.782413065f) / fConst220) + 0.245291501f));
		fConst275 = (9.99999975e-05f / fConst223);
		fConst276 = (2.0f * (0.000433227193f - fConst275));
		fConst277 = (((fConst221 + -0.782413065f) / fConst220) + 0.245291501f);
		fConst278 = (2.0f * (0.245291501f - fConst249));
		fConst279 = (fConst275 + 0.000433227193f);
		fConst280 = (((fConst221 + -0.51247865f) / fConst220) + 0.689621389f);
		fConst281 = (2.0f * (0.689621389f - fConst249));
		fConst282 = (fConst249 + 7.62173128f);
		fConst283 = (((fConst221 + -0.168404877f) / fConst220) + 1.06935835f);
		fConst284 = (2.0f * (1.06935835f - fConst249));
		fConst285 = (fConst249 + 53.5361519f);
		fConst286 = (((fConst259 + -3.18972731f) / fConst258) + 4.07678175f);
		fConst287 = (1.0f / fConst261);
		fConst288 = (2.0f * (4.07678175f - fConst287));
		fConst289 = (fConst268 + 0.000407678192f);
		fConst290 = (((fConst259 + -0.743130445f) / fConst258) + 1.4500711f);
		fConst291 = (2.0f * (1.4500711f - fConst287));
		fConst292 = (fConst265 + 1.4500711f);
		fConst293 = (((fConst259 + -0.157482162f) / fConst258) + 0.935140193f);
		fConst294 = (2.0f * (0.935140193f - fConst287));
		fConst295 = (fConst262 + 0.935140193f);
		fConst296 = tanf((1246.74182f / fConst0));
		fConst297 = (1.0f / fConst296);
		fConst298 = (1.0f / (((fConst297 + 0.157482162f) / fConst296) + 0.935140193f));
		fConst299 = mydsp_faustpower2_f(fConst296);
		fConst300 = (50.0638084f / fConst299);
		fConst301 = (2.0f * (0.935140193f - fConst300));
		fConst302 = (1.0f / (((fConst297 + 0.743130445f) / fConst296) + 1.4500711f));
		fConst303 = (11.0520525f / fConst299);
		fConst304 = (2.0f * (1.4500711f - fConst303));
		fConst305 = (1.0f / (((fConst297 + 3.18972731f) / fConst296) + 4.07678175f));
		fConst306 = (0.00176617282f / fConst299);
		fConst307 = (2.0f * (0.000407678192f - fConst306));
		fConst308 = (1.0f / (((fConst259 + 0.168404877f) / fConst258) + 1.06935835f));
		fConst309 = (2.0f * (53.5361519f - fConst287));
		fConst310 = (1.0f / (((fConst259 + 0.51247865f) / fConst258) + 0.689621389f));
		fConst311 = (2.0f * (7.62173128f - fConst287));
		fConst312 = (1.0f / (((fConst259 + 0.782413065f) / fConst258) + 0.245291501f));
		fConst313 = (9.99999975e-05f / fConst261);
		fConst314 = (2.0f * (0.000433227193f - fConst313));
		fConst315 = (((fConst259 + -0.782413065f) / fConst258) + 0.245291501f);
		fConst316 = (2.0f * (0.245291501f - fConst287));
		fConst317 = (fConst313 + 0.000433227193f);
		fConst318 = (((fConst259 + -0.51247865f) / fConst258) + 0.689621389f);
		fConst319 = (2.0f * (0.689621389f - fConst287));
		fConst320 = (fConst287 + 7.62173128f);
		fConst321 = (((fConst259 + -0.168404877f) / fConst258) + 1.06935835f);
		fConst322 = (2.0f * (1.06935835f - fConst287));
		fConst323 = (fConst287 + 53.5361519f);
		fConst324 = (((fConst297 + -3.18972731f) / fConst296) + 4.07678175f);
		fConst325 = (1.0f / fConst299);
		fConst326 = (2.0f * (4.07678175f - fConst325));
		fConst327 = (fConst306 + 0.000407678192f);
		fConst328 = (((fConst297 + -0.743130445f) / fConst296) + 1.4500711f);
		fConst329 = (2.0f * (1.4500711f - fConst325));
		fConst330 = (fConst303 + 1.4500711f);
		fConst331 = (((fConst297 + -0.157482162f) / fConst296) + 0.935140193f);
		fConst332 = (2.0f * (0.935140193f - fConst325));
		fConst333 = (fConst300 + 0.935140193f);
		fConst334 = tanf((785.398193f / fConst0));
		fConst335 = (1.0f / fConst334);
		fConst336 = (1.0f / (((fConst335 + 0.157482162f) / fConst334) + 0.935140193f));
		fConst337 = mydsp_faustpower2_f(fConst334);
		fConst338 = (50.0638084f / fConst337);
		fConst339 = (2.0f * (0.935140193f - fConst338));
		fConst340 = (1.0f / (((fConst335 + 0.743130445f) / fConst334) + 1.4500711f));
		fConst341 = (11.0520525f / fConst337);
		fConst342 = (2.0f * (1.4500711f - fConst341));
		fConst343 = (1.0f / (((fConst335 + 3.18972731f) / fConst334) + 4.07678175f));
		fConst344 = (0.00176617282f / fConst337);
		fConst345 = (2.0f * (0.000407678192f - fConst344));
		fConst346 = (1.0f / (((fConst297 + 0.168404877f) / fConst296) + 1.06935835f));
		fConst347 = (2.0f * (53.5361519f - fConst325));
		fConst348 = (1.0f / (((fConst297 + 0.51247865f) / fConst296) + 0.689621389f));
		fConst349 = (2.0f * (7.62173128f - fConst325));
		fConst350 = (1.0f / (((fConst297 + 0.782413065f) / fConst296) + 0.245291501f));
		fConst351 = (9.99999975e-05f / fConst299);
		fConst352 = (2.0f * (0.000433227193f - fConst351));
		fConst353 = (((fConst297 + -0.782413065f) / fConst296) + 0.245291501f);
		fConst354 = (2.0f * (0.245291501f - fConst325));
		fConst355 = (fConst351 + 0.000433227193f);
		fConst356 = (((fConst297 + -0.51247865f) / fConst296) + 0.689621389f);
		fConst357 = (2.0f * (0.689621389f - fConst325));
		fConst358 = (fConst325 + 7.62173128f);
		fConst359 = (((fConst297 + -0.168404877f) / fConst296) + 1.06935835f);
		fConst360 = (2.0f * (1.06935835f - fConst325));
		fConst361 = (fConst325 + 53.5361519f);
		fConst362 = (((fConst335 + -3.18972731f) / fConst334) + 4.07678175f);
		fConst363 = (1.0f / fConst337);
		fConst364 = (2.0f * (4.07678175f - fConst363));
		fConst365 = (fConst344 + 0.000407678192f);
		fConst366 = (((fConst335 + -0.743130445f) / fConst334) + 1.4500711f);
		fConst367 = (2.0f * (1.4500711f - fConst363));
		fConst368 = (fConst341 + 1.4500711f);
		fConst369 = (((fConst335 + -0.157482162f) / fConst334) + 0.935140193f);
		fConst370 = (2.0f * (0.935140193f - fConst363));
		fConst371 = (fConst338 + 0.935140193f);
		fConst372 = tanf((494.769836f / fConst0));
		fConst373 = (1.0f / fConst372);
		fConst374 = (1.0f / (((fConst373 + 0.157482162f) / fConst372) + 0.935140193f));
		fConst375 = mydsp_faustpower2_f(fConst372);
		fConst376 = (50.0638084f / fConst375);
		fConst377 = (2.0f * (0.935140193f - fConst376));
		fConst378 = (1.0f / (((fConst373 + 0.743130445f) / fConst372) + 1.4500711f));
		fConst379 = (11.0520525f / fConst375);
		fConst380 = (2.0f * (1.4500711f - fConst379));
		fConst381 = (1.0f / (((fConst373 + 3.18972731f) / fConst372) + 4.07678175f));
		fConst382 = (0.00176617282f / fConst375);
		fConst383 = (2.0f * (0.000407678192f - fConst382));
		fConst384 = (1.0f / (((fConst335 + 0.168404877f) / fConst334) + 1.06935835f));
		fConst385 = (2.0f * (53.5361519f - fConst363));
		fConst386 = (1.0f / (((fConst335 + 0.51247865f) / fConst334) + 0.689621389f));
		fConst387 = (2.0f * (7.62173128f - fConst363));
		fConst388 = (1.0f / (((fConst335 + 0.782413065f) / fConst334) + 0.245291501f));
		fConst389 = (9.99999975e-05f / fConst337);
		fConst390 = (2.0f * (0.000433227193f - fConst389));
		fConst391 = (((fConst335 + -0.782413065f) / fConst334) + 0.245291501f);
		fConst392 = (2.0f * (0.245291501f - fConst363));
		fConst393 = (fConst389 + 0.000433227193f);
		fConst394 = (((fConst335 + -0.51247865f) / fConst334) + 0.689621389f);
		fConst395 = (2.0f * (0.689621389f - fConst363));
		fConst396 = (fConst363 + 7.62173128f);
		fConst397 = (((fConst335 + -0.168404877f) / fConst334) + 1.06935835f);
		fConst398 = (2.0f * (1.06935835f - fConst363));
		fConst399 = (fConst363 + 53.5361519f);
		fConst400 = (((fConst373 + -3.18972731f) / fConst372) + 4.07678175f);
		fConst401 = (1.0f / fConst375);
		fConst402 = (2.0f * (4.07678175f - fConst401));
		fConst403 = (fConst382 + 0.000407678192f);
		fConst404 = (((fConst373 + -0.743130445f) / fConst372) + 1.4500711f);
		fConst405 = (2.0f * (1.4500711f - fConst401));
		fConst406 = (fConst379 + 1.4500711f);
		fConst407 = (((fConst373 + -0.157482162f) / fConst372) + 0.935140193f);
		fConst408 = (2.0f * (0.935140193f - fConst401));
		fConst409 = (fConst376 + 0.935140193f);
		fConst410 = tanf((311.685455f / fConst0));
		fConst411 = (1.0f / fConst410);
		fConst412 = (1.0f / (((fConst411 + 0.157482162f) / fConst410) + 0.935140193f));
		fConst413 = mydsp_faustpower2_f(fConst410);
		fConst414 = (50.0638084f / fConst413);
		fConst415 = (2.0f * (0.935140193f - fConst414));
		fConst416 = (1.0f / (((fConst411 + 0.743130445f) / fConst410) + 1.4500711f));
		fConst417 = (11.0520525f / fConst413);
		fConst418 = (2.0f * (1.4500711f - fConst417));
		fConst419 = (1.0f / (((fConst411 + 3.18972731f) / fConst410) + 4.07678175f));
		fConst420 = (0.00176617282f / fConst413);
		fConst421 = (2.0f * (0.000407678192f - fConst420));
		fConst422 = (1.0f / (((fConst373 + 0.168404877f) / fConst372) + 1.06935835f));
		fConst423 = (2.0f * (53.5361519f - fConst401));
		fConst424 = (1.0f / (((fConst373 + 0.51247865f) / fConst372) + 0.689621389f));
		fConst425 = (2.0f * (7.62173128f - fConst401));
		fConst426 = (1.0f / (((fConst373 + 0.782413065f) / fConst372) + 0.245291501f));
		fConst427 = (9.99999975e-05f / fConst375);
		fConst428 = (2.0f * (0.000433227193f - fConst427));
		fConst429 = (((fConst373 + -0.782413065f) / fConst372) + 0.245291501f);
		fConst430 = (2.0f * (0.245291501f - fConst401));
		fConst431 = (fConst427 + 0.000433227193f);
		fConst432 = (((fConst373 + -0.51247865f) / fConst372) + 0.689621389f);
		fConst433 = (2.0f * (0.689621389f - fConst401));
		fConst434 = (fConst401 + 7.62173128f);
		fConst435 = (((fConst373 + -0.168404877f) / fConst372) + 1.06935835f);
		fConst436 = (2.0f * (1.06935835f - fConst401));
		fConst437 = (fConst401 + 53.5361519f);
		fConst438 = (((fConst411 + -3.18972731f) / fConst410) + 4.07678175f);
		fConst439 = (1.0f / fConst413);
		fConst440 = (2.0f * (4.07678175f - fConst439));
		fConst441 = (fConst420 + 0.000407678192f);
		fConst442 = (((fConst411 + -0.743130445f) / fConst410) + 1.4500711f);
		fConst443 = (2.0f * (1.4500711f - fConst439));
		fConst444 = (fConst417 + 1.4500711f);
		fConst445 = (((fConst411 + -0.157482162f) / fConst410) + 0.935140193f);
		fConst446 = (2.0f * (0.935140193f - fConst439));
		fConst447 = (fConst414 + 0.935140193f);
		fConst448 = tanf((196.349548f / fConst0));
		fConst449 = (1.0f / fConst448);
		fConst450 = (1.0f / (((fConst449 + 0.157482162f) / fConst448) + 0.935140193f));
		fConst451 = mydsp_faustpower2_f(fConst448);
		fConst452 = (50.0638084f / fConst451);
		fConst453 = (2.0f * (0.935140193f - fConst452));
		fConst454 = (1.0f / (((fConst449 + 0.743130445f) / fConst448) + 1.4500711f));
		fConst455 = (11.0520525f / fConst451);
		fConst456 = (2.0f * (1.4500711f - fConst455));
		fConst457 = (1.0f / (((fConst449 + 3.18972731f) / fConst448) + 4.07678175f));
		fConst458 = (0.00176617282f / fConst451);
		fConst459 = (2.0f * (0.000407678192f - fConst458));
		fConst460 = (1.0f / (((fConst411 + 0.168404877f) / fConst410) + 1.06935835f));
		fConst461 = (2.0f * (53.5361519f - fConst439));
		fConst462 = (1.0f / (((fConst411 + 0.51247865f) / fConst410) + 0.689621389f));
		fConst463 = (2.0f * (7.62173128f - fConst439));
		fConst464 = (1.0f / (((fConst411 + 0.782413065f) / fConst410) + 0.245291501f));
		fConst465 = (9.99999975e-05f / fConst413);
		fConst466 = (2.0f * (0.000433227193f - fConst465));
		fConst467 = (((fConst411 + -0.782413065f) / fConst410) + 0.245291501f);
		fConst468 = (2.0f * (0.245291501f - fConst439));
		fConst469 = (fConst465 + 0.000433227193f);
		fConst470 = (((fConst411 + -0.51247865f) / fConst410) + 0.689621389f);
		fConst471 = (2.0f * (0.689621389f - fConst439));
		fConst472 = (fConst439 + 7.62173128f);
		fConst473 = (((fConst411 + -0.168404877f) / fConst410) + 1.06935835f);
		fConst474 = (2.0f * (1.06935835f - fConst439));
		fConst475 = (fConst439 + 53.5361519f);
		fConst476 = (((fConst449 + -3.18972731f) / fConst448) + 4.07678175f);
		fConst477 = (1.0f / fConst451);
		fConst478 = (2.0f * (4.07678175f - fConst477));
		fConst479 = (fConst458 + 0.000407678192f);
		fConst480 = (((fConst449 + -0.743130445f) / fConst448) + 1.4500711f);
		fConst481 = (2.0f * (1.4500711f - fConst477));
		fConst482 = (fConst455 + 1.4500711f);
		fConst483 = (((fConst449 + -0.157482162f) / fConst448) + 0.935140193f);
		fConst484 = (2.0f * (0.935140193f - fConst477));
		fConst485 = (fConst452 + 0.935140193f);
		fConst486 = tanf((123.692459f / fConst0));
		fConst487 = (1.0f / fConst486);
		fConst488 = (1.0f / (((fConst487 + 0.157482162f) / fConst486) + 0.935140193f));
		fConst489 = mydsp_faustpower2_f(fConst486);
		fConst490 = (50.0638084f / fConst489);
		fConst491 = (2.0f * (0.935140193f - fConst490));
		fConst492 = (1.0f / (((fConst487 + 0.743130445f) / fConst486) + 1.4500711f));
		fConst493 = (11.0520525f / fConst489);
		fConst494 = (2.0f * (1.4500711f - fConst493));
		fConst495 = (1.0f / (((fConst487 + 3.18972731f) / fConst486) + 4.07678175f));
		fConst496 = (0.00176617282f / fConst489);
		fConst497 = (2.0f * (0.000407678192f - fConst496));
		fConst498 = (1.0f / (((fConst449 + 0.168404877f) / fConst448) + 1.06935835f));
		fConst499 = (2.0f * (53.5361519f - fConst477));
		fConst500 = (1.0f / (((fConst449 + 0.51247865f) / fConst448) + 0.689621389f));
		fConst501 = (2.0f * (7.62173128f - fConst477));
		fConst502 = (1.0f / (((fConst449 + 0.782413065f) / fConst448) + 0.245291501f));
		fConst503 = (9.99999975e-05f / fConst451);
		fConst504 = (2.0f * (0.000433227193f - fConst503));
		fConst505 = (((fConst449 + -0.782413065f) / fConst448) + 0.245291501f);
		fConst506 = (2.0f * (0.245291501f - fConst477));
		fConst507 = (fConst503 + 0.000433227193f);
		fConst508 = (((fConst449 + -0.51247865f) / fConst448) + 0.689621389f);
		fConst509 = (2.0f * (0.689621389f - fConst477));
		fConst510 = (fConst477 + 7.62173128f);
		fConst511 = (((fConst449 + -0.168404877f) / fConst448) + 1.06935835f);
		fConst512 = (2.0f * (1.06935835f - fConst477));
		fConst513 = (fConst477 + 53.5361519f);
		fConst514 = (((fConst487 + -3.18972731f) / fConst486) + 4.07678175f);
		fConst515 = (1.0f / fConst489);
		fConst516 = (2.0f * (4.07678175f - fConst515));
		fConst517 = (fConst496 + 0.000407678192f);
		fConst518 = (((fConst487 + -0.743130445f) / fConst486) + 1.4500711f);
		fConst519 = (2.0f * (1.4500711f - fConst515));
		fConst520 = (fConst493 + 1.4500711f);
		fConst521 = (((fConst487 + -0.157482162f) / fConst486) + 0.935140193f);
		fConst522 = (2.0f * (0.935140193f - fConst515));
		fConst523 = (fConst490 + 0.935140193f);
		fConst524 = (1.0f / (((fConst487 + 0.168404877f) / fConst486) + 1.06935835f));
		fConst525 = (2.0f * (53.5361519f - fConst515));
		fConst526 = (1.0f / (((fConst487 + 0.51247865f) / fConst486) + 0.689621389f));
		fConst527 = (2.0f * (7.62173128f - fConst515));
		fConst528 = (1.0f / (((fConst487 + 0.782413065f) / fConst486) + 0.245291501f));
		fConst529 = (9.99999975e-05f / fConst489);
		fConst530 = (2.0f * (0.000433227193f - fConst529));
		fConst531 = (((fConst487 + -0.782413065f) / fConst486) + 0.245291501f);
		fConst532 = (2.0f * (0.245291501f - fConst515));
		fConst533 = (fConst529 + 0.000433227193f);
		fConst534 = (((fConst487 + -0.51247865f) / fConst486) + 0.689621389f);
		fConst535 = (2.0f * (0.689621389f - fConst515));
		fConst536 = (fConst515 + 7.62173128f);
		fConst537 = (((fConst487 + -0.168404877f) / fConst486) + 1.06935835f);
		fConst538 = (2.0f * (1.06935835f - fConst515));
		fConst539 = (fConst515 + 53.5361519f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(100.0f);
		fHslider3 = FAUSTFLOAT(5000.0f);
		fHslider4 = FAUSTFLOAT(-0.5f);
		fVslider0 = FAUSTFLOAT(-20.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec14[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec16[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec15[l4] = 0.0f;
			
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
			fRec17[l12] = 0.0f;
			
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
			fRec18[l20] = 0.0f;
			
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
			iRec19[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec20[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec22[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec13[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec23[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec12[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec24[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec11[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec25[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec10[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec26[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec9[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fVec27[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec8[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fVec28[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec7[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec29[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec6[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec30[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec5[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec31[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec4[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec3[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec2[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec1[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec0[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec27[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec26[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec25[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec24[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec23[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec22[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec21[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec34[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec33[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec32[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec31[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec30[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec29[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec28[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec41[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec40[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec39[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec38[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec37[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec36[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec35[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec48[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec47[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec46[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec45[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec44[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec43[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec42[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec55[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec54[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec53[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec52[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec51[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec50[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec49[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec62[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec61[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec60[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec59[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec58[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec57[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec56[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec69[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec68[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec67[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec66[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec65[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec64[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec63[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec76[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec75[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec74[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec73[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec72[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec71[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec70[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec83[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec82[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec81[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec80[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec79[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec78[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec77[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec90[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec89[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec88[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec87[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec86[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec85[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec84[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec97[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec96[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec95[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec94[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec93[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec92[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec91[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec104[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec103[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec102[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec101[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec100[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec99[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fRec98[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec111[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec110[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec109[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec108[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec107[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec106[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec105[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec115[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec114[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec113[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec112[l147] = 0.0f;
			
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
		ui_interface->openVerticalBox("spectralTiltLab");
		ui_interface->declare(0, "1", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
		ui_interface->openVerticalBox("Spectral Tilt Filter");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->addHorizontalSlider("Slope of Spectral Tilt across Band", &fHslider4, -0.5f, -1.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(0, "1", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
		ui_interface->openVerticalBox("Spectral Tilt Filter");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->addCheckButton("Bypass Spectral Tilt", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Start Frequency", &fHslider2, 100.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band Width", &fHslider3, 5000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillator.lib for sawtooth_demo");
		ui_interface->openVerticalBox("Test Signal");
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
		ui_interface->declare(0, "4", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for spectral_level_demo");
		ui_interface->openVerticalBox("Spectrum Analyzer");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph14, "0", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33f203e0", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33f0ea80", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33ee89b0", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33ec6860", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "4", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33ea4710", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "5", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33e825c0", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "6", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33e60470", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33e3e320", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "8", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33e1c1d0", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "9", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33df6100", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "10", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33dd3fb0", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "11", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33db1e60", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "12", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33d8fd10", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "13", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33d6dbc0", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "14", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7fdb33d4a9e0", &fVbargraph0, -50.0f, 10.0f);
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
		float fSlow0 = float(fHslider0);
		float fSlow1 = expf((0.0f - (fConst1 / float(fHslider1))));
		float fSlow2 = (1.0f - fSlow1);
		int iSlow3 = int(float(fCheckbox0));
		float fSlow4 = float(fHslider2);
		float fSlow5 = powf(((fSlow4 + float(fHslider3)) / fSlow4), 0.111111112f);
		float fSlow6 = tanf((fConst14 * (fSlow4 * mydsp_faustpower9_f(fSlow5))));
		float fSlow7 = float(fHslider4);
		float fSlow8 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (9.0f - fSlow7)))));
		float fSlow9 = (fSlow6 / fSlow8);
		float fSlow10 = tanf((fConst14 * fSlow4));
		float fSlow11 = (6.28318548f * ((fSlow4 * fSlow6) / fSlow10));
		float fSlow12 = (fConst15 + fSlow11);
		float fSlow13 = (0.0f - ((fSlow11 - fConst15) / fSlow12));
		float fSlow14 = (1.0f / fSlow12);
		float fSlow15 = (6.28318548f * ((fSlow4 * fSlow8) / fSlow10));
		float fSlow16 = (fSlow15 - fConst15);
		float fSlow17 = tanf((fConst14 * (fSlow4 * mydsp_faustpower8_f(fSlow5))));
		float fSlow18 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (8.0f - fSlow7)))));
		float fSlow19 = (fSlow17 / fSlow18);
		float fSlow20 = (6.28318548f * ((fSlow4 * fSlow17) / fSlow10));
		float fSlow21 = (fConst15 + fSlow20);
		float fSlow22 = (0.0f - ((fSlow20 - fConst15) / fSlow21));
		float fSlow23 = (1.0f / fSlow21);
		float fSlow24 = (6.28318548f * ((fSlow4 * fSlow18) / fSlow10));
		float fSlow25 = (fSlow24 - fConst15);
		float fSlow26 = tanf((fConst14 * (fSlow4 * mydsp_faustpower7_f(fSlow5))));
		float fSlow27 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (7.0f - fSlow7)))));
		float fSlow28 = (fSlow26 / fSlow27);
		float fSlow29 = (6.28318548f * ((fSlow4 * fSlow26) / fSlow10));
		float fSlow30 = (fConst15 + fSlow29);
		float fSlow31 = (0.0f - ((fSlow29 - fConst15) / fSlow30));
		float fSlow32 = (1.0f / fSlow30);
		float fSlow33 = (6.28318548f * ((fSlow4 * fSlow27) / fSlow10));
		float fSlow34 = (fSlow33 - fConst15);
		float fSlow35 = tanf((fConst14 * (fSlow4 * mydsp_faustpower6_f(fSlow5))));
		float fSlow36 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (6.0f - fSlow7)))));
		float fSlow37 = (fSlow35 / fSlow36);
		float fSlow38 = (6.28318548f * ((fSlow4 * fSlow35) / fSlow10));
		float fSlow39 = (fConst15 + fSlow38);
		float fSlow40 = (0.0f - ((fSlow38 - fConst15) / fSlow39));
		float fSlow41 = (1.0f / fSlow39);
		float fSlow42 = (6.28318548f * ((fSlow4 * fSlow36) / fSlow10));
		float fSlow43 = (fSlow42 - fConst15);
		float fSlow44 = tanf((fConst14 * (fSlow4 * mydsp_faustpower5_f(fSlow5))));
		float fSlow45 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (5.0f - fSlow7)))));
		float fSlow46 = (fSlow44 / fSlow45);
		float fSlow47 = (6.28318548f * ((fSlow4 * fSlow44) / fSlow10));
		float fSlow48 = (fConst15 + fSlow47);
		float fSlow49 = (0.0f - ((fSlow47 - fConst15) / fSlow48));
		float fSlow50 = (1.0f / fSlow48);
		float fSlow51 = (6.28318548f * ((fSlow4 * fSlow45) / fSlow10));
		float fSlow52 = (fSlow51 - fConst15);
		float fSlow53 = tanf((fConst14 * (fSlow4 * mydsp_faustpower4_f(fSlow5))));
		float fSlow54 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (4.0f - fSlow7)))));
		float fSlow55 = (fSlow53 / fSlow54);
		float fSlow56 = (6.28318548f * ((fSlow4 * fSlow53) / fSlow10));
		float fSlow57 = (fConst15 + fSlow56);
		float fSlow58 = (0.0f - ((fSlow56 - fConst15) / fSlow57));
		float fSlow59 = (1.0f / fSlow57);
		float fSlow60 = (6.28318548f * ((fSlow4 * fSlow54) / fSlow10));
		float fSlow61 = (fSlow60 - fConst15);
		float fSlow62 = tanf((fConst14 * (fSlow4 * mydsp_faustpower3_f(fSlow5))));
		float fSlow63 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (3.0f - fSlow7)))));
		float fSlow64 = (fSlow62 / fSlow63);
		float fSlow65 = (6.28318548f * ((fSlow4 * fSlow62) / fSlow10));
		float fSlow66 = (fConst15 + fSlow65);
		float fSlow67 = (0.0f - ((fSlow65 - fConst15) / fSlow66));
		float fSlow68 = (1.0f / fSlow66);
		float fSlow69 = (6.28318548f * ((fSlow4 * fSlow63) / fSlow10));
		float fSlow70 = (fSlow69 - fConst15);
		float fSlow71 = tanf((fConst14 * (fSlow4 * mydsp_faustpower2_f(fSlow5))));
		float fSlow72 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (2.0f - fSlow7)))));
		float fSlow73 = (fSlow71 / fSlow72);
		float fSlow74 = (6.28318548f * ((fSlow4 * fSlow71) / fSlow10));
		float fSlow75 = (fConst15 + fSlow74);
		float fSlow76 = (0.0f - ((fSlow74 - fConst15) / fSlow75));
		float fSlow77 = (1.0f / fSlow75);
		float fSlow78 = (6.28318548f * ((fSlow4 * fSlow72) / fSlow10));
		float fSlow79 = (fSlow78 - fConst15);
		float fSlow80 = tanf((fConst14 * (fSlow4 * fSlow5)));
		float fSlow81 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (1.0f - fSlow7)))));
		float fSlow82 = (fSlow80 / fSlow81);
		float fSlow83 = (6.28318548f * ((fSlow4 * fSlow80) / fSlow10));
		float fSlow84 = (fConst15 + fSlow83);
		float fSlow85 = (0.0f - ((fSlow83 - fConst15) / fSlow84));
		float fSlow86 = (1.0f / fSlow84);
		float fSlow87 = (6.28318548f * ((fSlow4 * fSlow81) / fSlow10));
		float fSlow88 = (fSlow87 - fConst15);
		float fSlow89 = tanf((fConst14 * (fSlow4 * powf(fSlow5, (0.0f - fSlow7)))));
		float fSlow90 = (fSlow10 / fSlow89);
		float fSlow91 = (6.28318548f * fSlow4);
		float fSlow92 = (fConst15 + fSlow91);
		float fSlow93 = (0.0f - ((fSlow91 - fConst15) / fSlow92));
		float fSlow94 = (1.0f / fSlow92);
		float fSlow95 = (6.28318548f * ((fSlow4 * fSlow89) / fSlow10));
		float fSlow96 = (fConst15 + fSlow95);
		float fSlow97 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fVslider0))));
		int iSlow98 = int(float(fCheckbox1));
		int iSlow99 = int(float(fCheckbox2));
		int iSlow100 = int((float(fEntry0) + -1.0f));
		int iSlow101 = (iSlow100 >= 2);
		int iSlow102 = (iSlow100 >= 1);
		float fSlow103 = expf((0.0f - (fConst16 / float(fVslider2))));
		float fSlow104 = (440.0f * (powf(2.0f, (0.0833333358f * (float(fVslider1) + -49.0f))) * (1.0f - fSlow103)));
		int iSlow105 = (iSlow100 >= 3);
		float fSlow106 = ((0.00999999978f * float(fVslider3)) + 1.0f);
		float fSlow107 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		int iSlow108 = int(float(fCheckbox3));
		float fSlow109 = (fSlow95 - fConst15);
		float fSlow110 = ((fSlow10 * (fConst15 + fSlow87)) / fSlow89);
		float fSlow111 = ((fSlow80 * (fConst15 + fSlow78)) / fSlow81);
		float fSlow112 = ((fSlow71 * (fConst15 + fSlow69)) / fSlow72);
		float fSlow113 = ((fSlow62 * (fConst15 + fSlow60)) / fSlow63);
		float fSlow114 = ((fSlow53 * (fConst15 + fSlow51)) / fSlow54);
		float fSlow115 = ((fSlow44 * (fConst15 + fSlow42)) / fSlow45);
		float fSlow116 = ((fSlow35 * (fConst15 + fSlow33)) / fSlow36);
		float fSlow117 = ((fSlow26 * (fConst15 + fSlow24)) / fSlow27);
		float fSlow118 = ((fSlow17 * (fConst15 + fSlow15)) / fSlow18);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec14[0] = (fSlow97 + (0.999000013f * fRec14[1]));
			fRec16[0] = (fSlow104 + (fSlow103 * fRec16[1]));
			float fTemp0 = max(20.0f, fabsf(fRec16[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec15[1] + (fConst16 * fVec1[1]));
			fRec15[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (2.0f * fRec15[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = mydsp_faustpower2_f(fTemp3);
			fVec2[0] = fTemp4;
			float fTemp5 = mydsp_faustpower3_f(fTemp3);
			fVec3[0] = (fTemp5 + (1.0f - fTemp2));
			float fTemp6 = ((fTemp5 + (1.0f - (fTemp2 + fVec3[1]))) / fTemp0);
			fVec4[0] = fTemp6;
			float fTemp7 = (fTemp4 * (fTemp4 + -2.0f));
			fVec5[0] = fTemp7;
			float fTemp8 = ((fTemp7 - fVec5[1]) / fTemp0);
			fVec6[0] = fTemp8;
			float fTemp9 = ((fTemp8 - fVec6[1]) / fTemp0);
			fVec7[0] = fTemp9;
			float fTemp10 = max(20.0f, fabsf((fSlow106 * fRec16[0])));
			fVec8[0] = fTemp10;
			float fTemp11 = (fRec17[1] + (fConst16 * fVec8[1]));
			fRec17[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (2.0f * fRec17[0]);
			float fTemp13 = (fTemp12 + -1.0f);
			float fTemp14 = mydsp_faustpower2_f(fTemp13);
			fVec9[0] = fTemp14;
			float fTemp15 = mydsp_faustpower3_f(fTemp13);
			fVec10[0] = (fTemp15 + (1.0f - fTemp12));
			float fTemp16 = ((fTemp15 + (1.0f - (fTemp12 + fVec10[1]))) / fTemp10);
			fVec11[0] = fTemp16;
			float fTemp17 = (fTemp14 * (fTemp14 + -2.0f));
			fVec12[0] = fTemp17;
			float fTemp18 = ((fTemp17 - fVec12[1]) / fTemp10);
			fVec13[0] = fTemp18;
			float fTemp19 = ((fTemp18 - fVec13[1]) / fTemp10);
			fVec14[0] = fTemp19;
			float fTemp20 = max(20.0f, fabsf((fSlow107 * fRec16[0])));
			fVec15[0] = fTemp20;
			float fTemp21 = (fRec18[1] + (fConst16 * fVec15[1]));
			fRec18[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (2.0f * fRec18[0]);
			float fTemp23 = (fTemp22 + -1.0f);
			float fTemp24 = mydsp_faustpower2_f(fTemp23);
			fVec16[0] = fTemp24;
			float fTemp25 = mydsp_faustpower3_f(fTemp23);
			fVec17[0] = (fTemp25 + (1.0f - fTemp22));
			float fTemp26 = ((fTemp25 + (1.0f - (fTemp22 + fVec17[1]))) / fTemp20);
			fVec18[0] = fTemp26;
			float fTemp27 = (fTemp24 * (fTemp24 + -2.0f));
			fVec19[0] = fTemp27;
			float fTemp28 = ((fTemp27 - fVec19[1]) / fTemp20);
			fVec20[0] = fTemp28;
			float fTemp29 = ((fTemp28 - fVec20[1]) / fTemp20);
			fVec21[0] = fTemp29;
			iRec19[0] = ((1103515245 * iRec19[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * float(iRec19[0]));
			fRec20[0] = (((0.522189379f * fRec20[3]) + (fTemp30 + (2.49495602f * fRec20[1]))) - (2.0172658f * fRec20[2]));
			float fTemp31 = (fRec14[0] * (iSlow98?float(input0[i]):(iSlow99?(iSlow108?(((0.0499220341f * fRec20[0]) + (0.0506126992f * fRec20[2])) - ((0.0959935337f * fRec20[1]) + (0.00440878607f * fRec20[3]))):fTemp30):(0.333333343f * (fRec14[0] * (((iSlow101?(iSlow105?(fConst19 * ((float(iVec0[3]) * (fTemp9 - fVec7[1])) / fTemp0)):(fConst18 * ((float(iVec0[2]) * (fTemp6 - fVec4[1])) / fTemp0))):(iSlow102?(fConst17 * ((float(iVec0[1]) * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (iSlow101?(iSlow105?(fConst19 * ((float(iVec0[3]) * (fTemp19 - fVec14[1])) / fTemp10)):(fConst18 * ((float(iVec0[2]) * (fTemp16 - fVec11[1])) / fTemp10))):(iSlow102?(fConst17 * ((float(iVec0[1]) * (fTemp14 - fVec9[1])) / fTemp10)):fTemp13))) + (iSlow101?(iSlow105?(fConst19 * ((float(iVec0[3]) * (fTemp29 - fVec21[1])) / fTemp20)):(fConst18 * ((float(iVec0[2]) * (fTemp26 - fVec18[1])) / fTemp20))):(iSlow102?(fConst17 * ((float(iVec0[1]) * (fTemp24 - fVec16[1])) / fTemp20)):fTemp23))))))));
			float fTemp32 = (iSlow3?0.0f:fTemp31);
			fVec22[0] = fTemp32;
			fRec13[0] = ((fSlow93 * fRec13[1]) + (fSlow94 * ((fSlow96 * fTemp32) + (fSlow109 * fVec22[1]))));
			fVec23[0] = (fSlow90 * fRec13[0]);
			fRec12[0] = ((fSlow85 * fRec12[1]) + (fSlow86 * ((fSlow88 * fVec23[1]) + (fSlow110 * fRec13[0]))));
			fVec24[0] = (fSlow82 * fRec12[0]);
			fRec11[0] = ((fSlow76 * fRec11[1]) + (fSlow77 * ((fSlow79 * fVec24[1]) + (fSlow111 * fRec12[0]))));
			fVec25[0] = (fSlow73 * fRec11[0]);
			fRec10[0] = ((fSlow67 * fRec10[1]) + (fSlow68 * ((fSlow70 * fVec25[1]) + (fSlow112 * fRec11[0]))));
			fVec26[0] = (fSlow64 * fRec10[0]);
			fRec9[0] = ((fSlow58 * fRec9[1]) + (fSlow59 * ((fSlow61 * fVec26[1]) + (fSlow113 * fRec10[0]))));
			fVec27[0] = (fSlow55 * fRec9[0]);
			fRec8[0] = ((fSlow49 * fRec8[1]) + (fSlow50 * ((fSlow52 * fVec27[1]) + (fSlow114 * fRec9[0]))));
			fVec28[0] = (fSlow46 * fRec8[0]);
			fRec7[0] = ((fSlow40 * fRec7[1]) + (fSlow41 * ((fSlow43 * fVec28[1]) + (fSlow115 * fRec8[0]))));
			fVec29[0] = (fSlow37 * fRec7[0]);
			fRec6[0] = ((fSlow31 * fRec6[1]) + (fSlow32 * ((fSlow34 * fVec29[1]) + (fSlow116 * fRec7[0]))));
			fVec30[0] = (fSlow28 * fRec6[0]);
			fRec5[0] = ((fSlow22 * fRec5[1]) + (fSlow23 * ((fSlow25 * fVec30[1]) + (fSlow117 * fRec6[0]))));
			fVec31[0] = (fSlow19 * fRec5[0]);
			fRec4[0] = ((fSlow13 * fRec4[1]) + (fSlow14 * ((fSlow16 * fVec31[1]) + (fSlow118 * fRec5[0]))));
			float fTemp33 = (iSlow3?fTemp31:(fSlow9 * fRec4[0]));
			fRec3[0] = (fTemp33 - (fConst11 * ((fConst20 * fRec3[2]) + (fConst22 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst23 * fRec3[0])) + (fConst23 * fRec3[2]))) - (fConst8 * ((fConst24 * fRec2[2]) + (fConst25 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst26 * fRec2[0])) + (fConst26 * fRec2[2]))) - (fConst4 * ((fConst27 * fRec1[2]) + (fConst28 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * fabsf((fConst4 * (((fConst7 * fRec1[1]) + (fConst29 * fRec1[0])) + (fConst29 * fRec1[2]))))));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec0[0])))));
			fRec27[0] = (fTemp33 - (fConst46 * ((fConst49 * fRec27[2]) + (fConst50 * fRec27[1]))));
			fRec26[0] = ((fConst46 * (((fConst48 * fRec27[1]) + (fConst51 * fRec27[0])) + (fConst51 * fRec27[2]))) - (fConst44 * ((fConst52 * fRec26[2]) + (fConst53 * fRec26[1]))));
			fRec25[0] = ((fConst44 * (((fConst45 * fRec26[1]) + (fConst54 * fRec26[0])) + (fConst54 * fRec26[2]))) - (fConst42 * ((fConst55 * fRec25[2]) + (fConst56 * fRec25[1]))));
			float fTemp34 = (fConst42 * (((fConst43 * fRec25[1]) + (fConst57 * fRec25[0])) + (fConst57 * fRec25[2])));
			fRec24[0] = (fTemp34 - (fConst39 * ((fConst58 * fRec24[2]) + (fConst60 * fRec24[1]))));
			fRec23[0] = ((fConst39 * (((fConst41 * fRec24[1]) + (fConst61 * fRec24[0])) + (fConst61 * fRec24[2]))) - (fConst36 * ((fConst62 * fRec23[2]) + (fConst63 * fRec23[1]))));
			fRec22[0] = ((fConst36 * (((fConst38 * fRec23[1]) + (fConst64 * fRec23[0])) + (fConst64 * fRec23[2]))) - (fConst32 * ((fConst65 * fRec22[2]) + (fConst66 * fRec22[1]))));
			fRec21[0] = ((fSlow1 * fRec21[1]) + (fSlow2 * fabsf((fConst32 * (((fConst35 * fRec22[1]) + (fConst67 * fRec22[0])) + (fConst67 * fRec22[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec21[0])))));
			fRec34[0] = (fTemp34 - (fConst84 * ((fConst87 * fRec34[2]) + (fConst88 * fRec34[1]))));
			fRec33[0] = ((fConst84 * (((fConst86 * fRec34[1]) + (fConst89 * fRec34[0])) + (fConst89 * fRec34[2]))) - (fConst82 * ((fConst90 * fRec33[2]) + (fConst91 * fRec33[1]))));
			fRec32[0] = ((fConst82 * (((fConst83 * fRec33[1]) + (fConst92 * fRec33[0])) + (fConst92 * fRec33[2]))) - (fConst80 * ((fConst93 * fRec32[2]) + (fConst94 * fRec32[1]))));
			float fTemp35 = (fConst80 * (((fConst81 * fRec32[1]) + (fConst95 * fRec32[0])) + (fConst95 * fRec32[2])));
			fRec31[0] = (fTemp35 - (fConst77 * ((fConst96 * fRec31[2]) + (fConst98 * fRec31[1]))));
			fRec30[0] = ((fConst77 * (((fConst79 * fRec31[1]) + (fConst99 * fRec31[0])) + (fConst99 * fRec31[2]))) - (fConst74 * ((fConst100 * fRec30[2]) + (fConst101 * fRec30[1]))));
			fRec29[0] = ((fConst74 * (((fConst76 * fRec30[1]) + (fConst102 * fRec30[0])) + (fConst102 * fRec30[2]))) - (fConst70 * ((fConst103 * fRec29[2]) + (fConst104 * fRec29[1]))));
			fRec28[0] = ((fSlow1 * fRec28[1]) + (fSlow2 * fabsf((fConst70 * (((fConst73 * fRec29[1]) + (fConst105 * fRec29[0])) + (fConst105 * fRec29[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec28[0])))));
			fRec41[0] = (fTemp35 - (fConst122 * ((fConst125 * fRec41[2]) + (fConst126 * fRec41[1]))));
			fRec40[0] = ((fConst122 * (((fConst124 * fRec41[1]) + (fConst127 * fRec41[0])) + (fConst127 * fRec41[2]))) - (fConst120 * ((fConst128 * fRec40[2]) + (fConst129 * fRec40[1]))));
			fRec39[0] = ((fConst120 * (((fConst121 * fRec40[1]) + (fConst130 * fRec40[0])) + (fConst130 * fRec40[2]))) - (fConst118 * ((fConst131 * fRec39[2]) + (fConst132 * fRec39[1]))));
			float fTemp36 = (fConst118 * (((fConst119 * fRec39[1]) + (fConst133 * fRec39[0])) + (fConst133 * fRec39[2])));
			fRec38[0] = (fTemp36 - (fConst115 * ((fConst134 * fRec38[2]) + (fConst136 * fRec38[1]))));
			fRec37[0] = ((fConst115 * (((fConst117 * fRec38[1]) + (fConst137 * fRec38[0])) + (fConst137 * fRec38[2]))) - (fConst112 * ((fConst138 * fRec37[2]) + (fConst139 * fRec37[1]))));
			fRec36[0] = ((fConst112 * (((fConst114 * fRec37[1]) + (fConst140 * fRec37[0])) + (fConst140 * fRec37[2]))) - (fConst108 * ((fConst141 * fRec36[2]) + (fConst142 * fRec36[1]))));
			fRec35[0] = ((fSlow1 * fRec35[1]) + (fSlow2 * fabsf((fConst108 * (((fConst111 * fRec36[1]) + (fConst143 * fRec36[0])) + (fConst143 * fRec36[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec35[0])))));
			fRec48[0] = (fTemp36 - (fConst160 * ((fConst163 * fRec48[2]) + (fConst164 * fRec48[1]))));
			fRec47[0] = ((fConst160 * (((fConst162 * fRec48[1]) + (fConst165 * fRec48[0])) + (fConst165 * fRec48[2]))) - (fConst158 * ((fConst166 * fRec47[2]) + (fConst167 * fRec47[1]))));
			fRec46[0] = ((fConst158 * (((fConst159 * fRec47[1]) + (fConst168 * fRec47[0])) + (fConst168 * fRec47[2]))) - (fConst156 * ((fConst169 * fRec46[2]) + (fConst170 * fRec46[1]))));
			float fTemp37 = (fConst156 * (((fConst157 * fRec46[1]) + (fConst171 * fRec46[0])) + (fConst171 * fRec46[2])));
			fRec45[0] = (fTemp37 - (fConst153 * ((fConst172 * fRec45[2]) + (fConst174 * fRec45[1]))));
			fRec44[0] = ((fConst153 * (((fConst155 * fRec45[1]) + (fConst175 * fRec45[0])) + (fConst175 * fRec45[2]))) - (fConst150 * ((fConst176 * fRec44[2]) + (fConst177 * fRec44[1]))));
			fRec43[0] = ((fConst150 * (((fConst152 * fRec44[1]) + (fConst178 * fRec44[0])) + (fConst178 * fRec44[2]))) - (fConst146 * ((fConst179 * fRec43[2]) + (fConst180 * fRec43[1]))));
			fRec42[0] = ((fSlow1 * fRec42[1]) + (fSlow2 * fabsf((fConst146 * (((fConst149 * fRec43[1]) + (fConst181 * fRec43[0])) + (fConst181 * fRec43[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec42[0])))));
			fRec55[0] = (fTemp37 - (fConst198 * ((fConst201 * fRec55[2]) + (fConst202 * fRec55[1]))));
			fRec54[0] = ((fConst198 * (((fConst200 * fRec55[1]) + (fConst203 * fRec55[0])) + (fConst203 * fRec55[2]))) - (fConst196 * ((fConst204 * fRec54[2]) + (fConst205 * fRec54[1]))));
			fRec53[0] = ((fConst196 * (((fConst197 * fRec54[1]) + (fConst206 * fRec54[0])) + (fConst206 * fRec54[2]))) - (fConst194 * ((fConst207 * fRec53[2]) + (fConst208 * fRec53[1]))));
			float fTemp38 = (fConst194 * (((fConst195 * fRec53[1]) + (fConst209 * fRec53[0])) + (fConst209 * fRec53[2])));
			fRec52[0] = (fTemp38 - (fConst191 * ((fConst210 * fRec52[2]) + (fConst212 * fRec52[1]))));
			fRec51[0] = ((fConst191 * (((fConst193 * fRec52[1]) + (fConst213 * fRec52[0])) + (fConst213 * fRec52[2]))) - (fConst188 * ((fConst214 * fRec51[2]) + (fConst215 * fRec51[1]))));
			fRec50[0] = ((fConst188 * (((fConst190 * fRec51[1]) + (fConst216 * fRec51[0])) + (fConst216 * fRec51[2]))) - (fConst184 * ((fConst217 * fRec50[2]) + (fConst218 * fRec50[1]))));
			fRec49[0] = ((fSlow1 * fRec49[1]) + (fSlow2 * fabsf((fConst184 * (((fConst187 * fRec50[1]) + (fConst219 * fRec50[0])) + (fConst219 * fRec50[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec49[0])))));
			fRec62[0] = (fTemp38 - (fConst236 * ((fConst239 * fRec62[2]) + (fConst240 * fRec62[1]))));
			fRec61[0] = ((fConst236 * (((fConst238 * fRec62[1]) + (fConst241 * fRec62[0])) + (fConst241 * fRec62[2]))) - (fConst234 * ((fConst242 * fRec61[2]) + (fConst243 * fRec61[1]))));
			fRec60[0] = ((fConst234 * (((fConst235 * fRec61[1]) + (fConst244 * fRec61[0])) + (fConst244 * fRec61[2]))) - (fConst232 * ((fConst245 * fRec60[2]) + (fConst246 * fRec60[1]))));
			float fTemp39 = (fConst232 * (((fConst233 * fRec60[1]) + (fConst247 * fRec60[0])) + (fConst247 * fRec60[2])));
			fRec59[0] = (fTemp39 - (fConst229 * ((fConst248 * fRec59[2]) + (fConst250 * fRec59[1]))));
			fRec58[0] = ((fConst229 * (((fConst231 * fRec59[1]) + (fConst251 * fRec59[0])) + (fConst251 * fRec59[2]))) - (fConst226 * ((fConst252 * fRec58[2]) + (fConst253 * fRec58[1]))));
			fRec57[0] = ((fConst226 * (((fConst228 * fRec58[1]) + (fConst254 * fRec58[0])) + (fConst254 * fRec58[2]))) - (fConst222 * ((fConst255 * fRec57[2]) + (fConst256 * fRec57[1]))));
			fRec56[0] = ((fSlow1 * fRec56[1]) + (fSlow2 * fabsf((fConst222 * (((fConst225 * fRec57[1]) + (fConst257 * fRec57[0])) + (fConst257 * fRec57[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec56[0])))));
			fRec69[0] = (fTemp39 - (fConst274 * ((fConst277 * fRec69[2]) + (fConst278 * fRec69[1]))));
			fRec68[0] = ((fConst274 * (((fConst276 * fRec69[1]) + (fConst279 * fRec69[0])) + (fConst279 * fRec69[2]))) - (fConst272 * ((fConst280 * fRec68[2]) + (fConst281 * fRec68[1]))));
			fRec67[0] = ((fConst272 * (((fConst273 * fRec68[1]) + (fConst282 * fRec68[0])) + (fConst282 * fRec68[2]))) - (fConst270 * ((fConst283 * fRec67[2]) + (fConst284 * fRec67[1]))));
			float fTemp40 = (fConst270 * (((fConst271 * fRec67[1]) + (fConst285 * fRec67[0])) + (fConst285 * fRec67[2])));
			fRec66[0] = (fTemp40 - (fConst267 * ((fConst286 * fRec66[2]) + (fConst288 * fRec66[1]))));
			fRec65[0] = ((fConst267 * (((fConst269 * fRec66[1]) + (fConst289 * fRec66[0])) + (fConst289 * fRec66[2]))) - (fConst264 * ((fConst290 * fRec65[2]) + (fConst291 * fRec65[1]))));
			fRec64[0] = ((fConst264 * (((fConst266 * fRec65[1]) + (fConst292 * fRec65[0])) + (fConst292 * fRec65[2]))) - (fConst260 * ((fConst293 * fRec64[2]) + (fConst294 * fRec64[1]))));
			fRec63[0] = ((fSlow1 * fRec63[1]) + (fSlow2 * fabsf((fConst260 * (((fConst263 * fRec64[1]) + (fConst295 * fRec64[0])) + (fConst295 * fRec64[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec63[0])))));
			fRec76[0] = (fTemp40 - (fConst312 * ((fConst315 * fRec76[2]) + (fConst316 * fRec76[1]))));
			fRec75[0] = ((fConst312 * (((fConst314 * fRec76[1]) + (fConst317 * fRec76[0])) + (fConst317 * fRec76[2]))) - (fConst310 * ((fConst318 * fRec75[2]) + (fConst319 * fRec75[1]))));
			fRec74[0] = ((fConst310 * (((fConst311 * fRec75[1]) + (fConst320 * fRec75[0])) + (fConst320 * fRec75[2]))) - (fConst308 * ((fConst321 * fRec74[2]) + (fConst322 * fRec74[1]))));
			float fTemp41 = (fConst308 * (((fConst309 * fRec74[1]) + (fConst323 * fRec74[0])) + (fConst323 * fRec74[2])));
			fRec73[0] = (fTemp41 - (fConst305 * ((fConst324 * fRec73[2]) + (fConst326 * fRec73[1]))));
			fRec72[0] = ((fConst305 * (((fConst307 * fRec73[1]) + (fConst327 * fRec73[0])) + (fConst327 * fRec73[2]))) - (fConst302 * ((fConst328 * fRec72[2]) + (fConst329 * fRec72[1]))));
			fRec71[0] = ((fConst302 * (((fConst304 * fRec72[1]) + (fConst330 * fRec72[0])) + (fConst330 * fRec72[2]))) - (fConst298 * ((fConst331 * fRec71[2]) + (fConst332 * fRec71[1]))));
			fRec70[0] = ((fSlow1 * fRec70[1]) + (fSlow2 * fabsf((fConst298 * (((fConst301 * fRec71[1]) + (fConst333 * fRec71[0])) + (fConst333 * fRec71[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec70[0])))));
			fRec83[0] = (fTemp41 - (fConst350 * ((fConst353 * fRec83[2]) + (fConst354 * fRec83[1]))));
			fRec82[0] = ((fConst350 * (((fConst352 * fRec83[1]) + (fConst355 * fRec83[0])) + (fConst355 * fRec83[2]))) - (fConst348 * ((fConst356 * fRec82[2]) + (fConst357 * fRec82[1]))));
			fRec81[0] = ((fConst348 * (((fConst349 * fRec82[1]) + (fConst358 * fRec82[0])) + (fConst358 * fRec82[2]))) - (fConst346 * ((fConst359 * fRec81[2]) + (fConst360 * fRec81[1]))));
			float fTemp42 = (fConst346 * (((fConst347 * fRec81[1]) + (fConst361 * fRec81[0])) + (fConst361 * fRec81[2])));
			fRec80[0] = (fTemp42 - (fConst343 * ((fConst362 * fRec80[2]) + (fConst364 * fRec80[1]))));
			fRec79[0] = ((fConst343 * (((fConst345 * fRec80[1]) + (fConst365 * fRec80[0])) + (fConst365 * fRec80[2]))) - (fConst340 * ((fConst366 * fRec79[2]) + (fConst367 * fRec79[1]))));
			fRec78[0] = ((fConst340 * (((fConst342 * fRec79[1]) + (fConst368 * fRec79[0])) + (fConst368 * fRec79[2]))) - (fConst336 * ((fConst369 * fRec78[2]) + (fConst370 * fRec78[1]))));
			fRec77[0] = ((fSlow1 * fRec77[1]) + (fSlow2 * fabsf((fConst336 * (((fConst339 * fRec78[1]) + (fConst371 * fRec78[0])) + (fConst371 * fRec78[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec77[0])))));
			fRec90[0] = (fTemp42 - (fConst388 * ((fConst391 * fRec90[2]) + (fConst392 * fRec90[1]))));
			fRec89[0] = ((fConst388 * (((fConst390 * fRec90[1]) + (fConst393 * fRec90[0])) + (fConst393 * fRec90[2]))) - (fConst386 * ((fConst394 * fRec89[2]) + (fConst395 * fRec89[1]))));
			fRec88[0] = ((fConst386 * (((fConst387 * fRec89[1]) + (fConst396 * fRec89[0])) + (fConst396 * fRec89[2]))) - (fConst384 * ((fConst397 * fRec88[2]) + (fConst398 * fRec88[1]))));
			float fTemp43 = (fConst384 * (((fConst385 * fRec88[1]) + (fConst399 * fRec88[0])) + (fConst399 * fRec88[2])));
			fRec87[0] = (fTemp43 - (fConst381 * ((fConst400 * fRec87[2]) + (fConst402 * fRec87[1]))));
			fRec86[0] = ((fConst381 * (((fConst383 * fRec87[1]) + (fConst403 * fRec87[0])) + (fConst403 * fRec87[2]))) - (fConst378 * ((fConst404 * fRec86[2]) + (fConst405 * fRec86[1]))));
			fRec85[0] = ((fConst378 * (((fConst380 * fRec86[1]) + (fConst406 * fRec86[0])) + (fConst406 * fRec86[2]))) - (fConst374 * ((fConst407 * fRec85[2]) + (fConst408 * fRec85[1]))));
			fRec84[0] = ((fSlow1 * fRec84[1]) + (fSlow2 * fabsf((fConst374 * (((fConst377 * fRec85[1]) + (fConst409 * fRec85[0])) + (fConst409 * fRec85[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec84[0])))));
			fRec97[0] = (fTemp43 - (fConst426 * ((fConst429 * fRec97[2]) + (fConst430 * fRec97[1]))));
			fRec96[0] = ((fConst426 * (((fConst428 * fRec97[1]) + (fConst431 * fRec97[0])) + (fConst431 * fRec97[2]))) - (fConst424 * ((fConst432 * fRec96[2]) + (fConst433 * fRec96[1]))));
			fRec95[0] = ((fConst424 * (((fConst425 * fRec96[1]) + (fConst434 * fRec96[0])) + (fConst434 * fRec96[2]))) - (fConst422 * ((fConst435 * fRec95[2]) + (fConst436 * fRec95[1]))));
			float fTemp44 = (fConst422 * (((fConst423 * fRec95[1]) + (fConst437 * fRec95[0])) + (fConst437 * fRec95[2])));
			fRec94[0] = (fTemp44 - (fConst419 * ((fConst438 * fRec94[2]) + (fConst440 * fRec94[1]))));
			fRec93[0] = ((fConst419 * (((fConst421 * fRec94[1]) + (fConst441 * fRec94[0])) + (fConst441 * fRec94[2]))) - (fConst416 * ((fConst442 * fRec93[2]) + (fConst443 * fRec93[1]))));
			fRec92[0] = ((fConst416 * (((fConst418 * fRec93[1]) + (fConst444 * fRec93[0])) + (fConst444 * fRec93[2]))) - (fConst412 * ((fConst445 * fRec92[2]) + (fConst446 * fRec92[1]))));
			fRec91[0] = ((fSlow1 * fRec91[1]) + (fSlow2 * fabsf((fConst412 * (((fConst415 * fRec92[1]) + (fConst447 * fRec92[0])) + (fConst447 * fRec92[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec91[0])))));
			fRec104[0] = (fTemp44 - (fConst464 * ((fConst467 * fRec104[2]) + (fConst468 * fRec104[1]))));
			fRec103[0] = ((fConst464 * (((fConst466 * fRec104[1]) + (fConst469 * fRec104[0])) + (fConst469 * fRec104[2]))) - (fConst462 * ((fConst470 * fRec103[2]) + (fConst471 * fRec103[1]))));
			fRec102[0] = ((fConst462 * (((fConst463 * fRec103[1]) + (fConst472 * fRec103[0])) + (fConst472 * fRec103[2]))) - (fConst460 * ((fConst473 * fRec102[2]) + (fConst474 * fRec102[1]))));
			float fTemp45 = (fConst460 * (((fConst461 * fRec102[1]) + (fConst475 * fRec102[0])) + (fConst475 * fRec102[2])));
			fRec101[0] = (fTemp45 - (fConst457 * ((fConst476 * fRec101[2]) + (fConst478 * fRec101[1]))));
			fRec100[0] = ((fConst457 * (((fConst459 * fRec101[1]) + (fConst479 * fRec101[0])) + (fConst479 * fRec101[2]))) - (fConst454 * ((fConst480 * fRec100[2]) + (fConst481 * fRec100[1]))));
			fRec99[0] = ((fConst454 * (((fConst456 * fRec100[1]) + (fConst482 * fRec100[0])) + (fConst482 * fRec100[2]))) - (fConst450 * ((fConst483 * fRec99[2]) + (fConst484 * fRec99[1]))));
			fRec98[0] = ((fSlow1 * fRec98[1]) + (fSlow2 * fabsf((fConst450 * (((fConst453 * fRec99[1]) + (fConst485 * fRec99[0])) + (fConst485 * fRec99[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec98[0])))));
			fRec111[0] = (fTemp45 - (fConst502 * ((fConst505 * fRec111[2]) + (fConst506 * fRec111[1]))));
			fRec110[0] = ((fConst502 * (((fConst504 * fRec111[1]) + (fConst507 * fRec111[0])) + (fConst507 * fRec111[2]))) - (fConst500 * ((fConst508 * fRec110[2]) + (fConst509 * fRec110[1]))));
			fRec109[0] = ((fConst500 * (((fConst501 * fRec110[1]) + (fConst510 * fRec110[0])) + (fConst510 * fRec110[2]))) - (fConst498 * ((fConst511 * fRec109[2]) + (fConst512 * fRec109[1]))));
			float fTemp46 = (fConst498 * (((fConst499 * fRec109[1]) + (fConst513 * fRec109[0])) + (fConst513 * fRec109[2])));
			fRec108[0] = (fTemp46 - (fConst495 * ((fConst514 * fRec108[2]) + (fConst516 * fRec108[1]))));
			fRec107[0] = ((fConst495 * (((fConst497 * fRec108[1]) + (fConst517 * fRec108[0])) + (fConst517 * fRec108[2]))) - (fConst492 * ((fConst518 * fRec107[2]) + (fConst519 * fRec107[1]))));
			fRec106[0] = ((fConst492 * (((fConst494 * fRec107[1]) + (fConst520 * fRec107[0])) + (fConst520 * fRec107[2]))) - (fConst488 * ((fConst521 * fRec106[2]) + (fConst522 * fRec106[1]))));
			fRec105[0] = ((fSlow1 * fRec105[1]) + (fSlow2 * fabsf((fConst488 * (((fConst491 * fRec106[1]) + (fConst523 * fRec106[0])) + (fConst523 * fRec106[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec105[0])))));
			fRec115[0] = (fTemp46 - (fConst528 * ((fConst531 * fRec115[2]) + (fConst532 * fRec115[1]))));
			fRec114[0] = ((fConst528 * (((fConst530 * fRec115[1]) + (fConst533 * fRec115[0])) + (fConst533 * fRec115[2]))) - (fConst526 * ((fConst534 * fRec114[2]) + (fConst535 * fRec114[1]))));
			fRec113[0] = ((fConst526 * (((fConst527 * fRec114[1]) + (fConst536 * fRec114[0])) + (fConst536 * fRec114[2]))) - (fConst524 * ((fConst537 * fRec113[2]) + (fConst538 * fRec113[1]))));
			fRec112[0] = ((fSlow1 * fRec112[1]) + (fSlow2 * fabsf((fConst524 * (((fConst525 * fRec113[1]) + (fConst539 * fRec113[0])) + (fConst539 * fRec113[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec112[0])))));
			output0[i] = FAUSTFLOAT(fTemp33);
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
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
			iRec19[1] = iRec19[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec20[j1] = fRec20[(j1 - 1)];
				
			}
			fVec22[1] = fVec22[0];
			fRec13[1] = fRec13[0];
			fVec23[1] = fVec23[0];
			fRec12[1] = fRec12[0];
			fVec24[1] = fVec24[0];
			fRec11[1] = fRec11[0];
			fVec25[1] = fVec25[0];
			fRec10[1] = fRec10[0];
			fVec26[1] = fVec26[0];
			fRec9[1] = fRec9[0];
			fVec27[1] = fVec27[0];
			fRec8[1] = fRec8[0];
			fVec28[1] = fVec28[0];
			fRec7[1] = fRec7[0];
			fVec29[1] = fVec29[0];
			fRec6[1] = fRec6[0];
			fVec30[1] = fVec30[0];
			fRec5[1] = fRec5[0];
			fVec31[1] = fVec31[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
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
			fRec21[1] = fRec21[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
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
			fRec28[1] = fRec28[0];
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
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
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
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
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
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[1] = fRec49[0];
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
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[1] = fRec56[0];
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
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[1] = fRec63[0];
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
			fRec70[1] = fRec70[0];
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
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[1] = fRec77[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[1] = fRec84[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[1] = fRec91[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
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
			fRec98[1] = fRec98[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
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
			fRec105[1] = fRec105[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec114[2] = fRec114[1];
			fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[1] = fRec112[0];
			
		}
		
	}

	
};

#endif
