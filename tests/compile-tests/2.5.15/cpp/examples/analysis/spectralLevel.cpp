/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "spectralLevel"
version: "0.0"
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
	float fRec3[3];
	float fConst17;
	float fConst18;
	float fConst19;
	float fRec2[3];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec1[3];
	float fConst23;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fRec10[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec9[3];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec8[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec7[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec6[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec5[3];
	float fConst61;
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
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
	float fRec17[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec16[3];
	float fConst86;
	float fConst87;
	float fConst88;
	float fRec15[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec14[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec13[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec12[3];
	float fConst99;
	float fRec11[2];
	FAUSTFLOAT fVbargraph2;
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
	float fRec24[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec23[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec22[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec21[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec20[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec19[3];
	float fConst137;
	float fRec18[2];
	FAUSTFLOAT fVbargraph3;
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
	float fRec31[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec30[3];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec29[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec28[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec27[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec26[3];
	float fConst175;
	float fRec25[2];
	FAUSTFLOAT fVbargraph4;
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
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fConst196;
	float fRec38[3];
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec37[3];
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec36[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec35[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec34[3];
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec33[3];
	float fConst213;
	float fRec32[2];
	FAUSTFLOAT fVbargraph5;
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
	float fConst228;
	float fConst229;
	float fConst230;
	float fConst231;
	float fConst232;
	float fConst233;
	float fConst234;
	float fRec45[3];
	float fConst235;
	float fConst236;
	float fConst237;
	float fRec44[3];
	float fConst238;
	float fConst239;
	float fConst240;
	float fRec43[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fConst244;
	float fRec42[3];
	float fConst245;
	float fConst246;
	float fConst247;
	float fRec41[3];
	float fConst248;
	float fConst249;
	float fConst250;
	float fRec40[3];
	float fConst251;
	float fRec39[2];
	FAUSTFLOAT fVbargraph6;
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
	float fConst266;
	float fConst267;
	float fConst268;
	float fConst269;
	float fConst270;
	float fConst271;
	float fConst272;
	float fRec52[3];
	float fConst273;
	float fConst274;
	float fConst275;
	float fRec51[3];
	float fConst276;
	float fConst277;
	float fConst278;
	float fRec50[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fConst282;
	float fRec49[3];
	float fConst283;
	float fConst284;
	float fConst285;
	float fRec48[3];
	float fConst286;
	float fConst287;
	float fConst288;
	float fRec47[3];
	float fConst289;
	float fRec46[2];
	FAUSTFLOAT fVbargraph7;
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
	float fConst304;
	float fConst305;
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fConst310;
	float fRec59[3];
	float fConst311;
	float fConst312;
	float fConst313;
	float fRec58[3];
	float fConst314;
	float fConst315;
	float fConst316;
	float fRec57[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fConst320;
	float fRec56[3];
	float fConst321;
	float fConst322;
	float fConst323;
	float fRec55[3];
	float fConst324;
	float fConst325;
	float fConst326;
	float fRec54[3];
	float fConst327;
	float fRec53[2];
	FAUSTFLOAT fVbargraph8;
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
	float fConst342;
	float fConst343;
	float fConst344;
	float fConst345;
	float fConst346;
	float fConst347;
	float fConst348;
	float fRec66[3];
	float fConst349;
	float fConst350;
	float fConst351;
	float fRec65[3];
	float fConst352;
	float fConst353;
	float fConst354;
	float fRec64[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fConst358;
	float fRec63[3];
	float fConst359;
	float fConst360;
	float fConst361;
	float fRec62[3];
	float fConst362;
	float fConst363;
	float fConst364;
	float fRec61[3];
	float fConst365;
	float fRec60[2];
	FAUSTFLOAT fVbargraph9;
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
	float fConst380;
	float fConst381;
	float fConst382;
	float fConst383;
	float fConst384;
	float fConst385;
	float fConst386;
	float fRec73[3];
	float fConst387;
	float fConst388;
	float fConst389;
	float fRec72[3];
	float fConst390;
	float fConst391;
	float fConst392;
	float fRec71[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fConst396;
	float fRec70[3];
	float fConst397;
	float fConst398;
	float fConst399;
	float fRec69[3];
	float fConst400;
	float fConst401;
	float fConst402;
	float fRec68[3];
	float fConst403;
	float fRec67[2];
	FAUSTFLOAT fVbargraph10;
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
	float fConst418;
	float fConst419;
	float fConst420;
	float fConst421;
	float fConst422;
	float fConst423;
	float fConst424;
	float fRec80[3];
	float fConst425;
	float fConst426;
	float fConst427;
	float fRec79[3];
	float fConst428;
	float fConst429;
	float fConst430;
	float fRec78[3];
	float fConst431;
	float fConst432;
	float fConst433;
	float fConst434;
	float fRec77[3];
	float fConst435;
	float fConst436;
	float fConst437;
	float fRec76[3];
	float fConst438;
	float fConst439;
	float fConst440;
	float fRec75[3];
	float fConst441;
	float fRec74[2];
	FAUSTFLOAT fVbargraph11;
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
	float fConst456;
	float fConst457;
	float fConst458;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fRec87[3];
	float fConst463;
	float fConst464;
	float fConst465;
	float fRec86[3];
	float fConst466;
	float fConst467;
	float fConst468;
	float fRec85[3];
	float fConst469;
	float fConst470;
	float fConst471;
	float fConst472;
	float fRec84[3];
	float fConst473;
	float fConst474;
	float fConst475;
	float fRec83[3];
	float fConst476;
	float fConst477;
	float fConst478;
	float fRec82[3];
	float fConst479;
	float fRec81[2];
	FAUSTFLOAT fVbargraph12;
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
	float fConst494;
	float fConst495;
	float fConst496;
	float fConst497;
	float fConst498;
	float fConst499;
	float fConst500;
	float fRec94[3];
	float fConst501;
	float fConst502;
	float fConst503;
	float fRec93[3];
	float fConst504;
	float fConst505;
	float fConst506;
	float fRec92[3];
	float fConst507;
	float fConst508;
	float fConst509;
	float fConst510;
	float fRec91[3];
	float fConst511;
	float fConst512;
	float fConst513;
	float fRec90[3];
	float fConst514;
	float fConst515;
	float fConst516;
	float fRec89[3];
	float fConst517;
	float fRec88[2];
	FAUSTFLOAT fVbargraph13;
	float fConst518;
	float fConst519;
	float fConst520;
	float fConst521;
	float fConst522;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fRec98[3];
	float fConst527;
	float fConst528;
	float fConst529;
	float fRec97[3];
	float fConst530;
	float fConst531;
	float fConst532;
	float fRec96[3];
	float fConst533;
	float fRec95[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("description", "Demonstrates mth_octave_spectral_level in a standalone GUI.");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "spectralLevel");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.0");
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
		fConst14 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst15 = (1.0f / fConst5);
		fConst16 = (2.0f * (4.07678175f - fConst15));
		fConst17 = (fConst12 + 0.000407678192f);
		fConst18 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst19 = (2.0f * (1.4500711f - fConst15));
		fConst20 = (fConst9 + 1.4500711f);
		fConst21 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst22 = (2.0f * (0.935140193f - fConst15));
		fConst23 = (fConst6 + 0.935140193f);
		fConst24 = tanf((31665.2695f / fConst0));
		fConst25 = (1.0f / fConst24);
		fConst26 = (1.0f / (((fConst25 + 0.157482162f) / fConst24) + 0.935140193f));
		fConst27 = mydsp_faustpower2_f(fConst24);
		fConst28 = (50.0638084f / fConst27);
		fConst29 = (2.0f * (0.935140193f - fConst28));
		fConst30 = (1.0f / (((fConst25 + 0.743130445f) / fConst24) + 1.4500711f));
		fConst31 = (11.0520525f / fConst27);
		fConst32 = (2.0f * (1.4500711f - fConst31));
		fConst33 = (1.0f / (((fConst25 + 3.18972731f) / fConst24) + 4.07678175f));
		fConst34 = (0.00176617282f / fConst27);
		fConst35 = (2.0f * (0.000407678192f - fConst34));
		fConst36 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst37 = (2.0f * (53.5361519f - fConst15));
		fConst38 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst39 = (2.0f * (7.62173128f - fConst15));
		fConst40 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst41 = (9.99999975e-05f / fConst5);
		fConst42 = (2.0f * (0.000433227193f - fConst41));
		fConst43 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst44 = (2.0f * (0.245291501f - fConst15));
		fConst45 = (fConst41 + 0.000433227193f);
		fConst46 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst47 = (2.0f * (0.689621389f - fConst15));
		fConst48 = (fConst15 + 7.62173128f);
		fConst49 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst50 = (2.0f * (1.06935835f - fConst15));
		fConst51 = (fConst15 + 53.5361519f);
		fConst52 = (((fConst25 + -3.18972731f) / fConst24) + 4.07678175f);
		fConst53 = (1.0f / fConst27);
		fConst54 = (2.0f * (4.07678175f - fConst53));
		fConst55 = (fConst34 + 0.000407678192f);
		fConst56 = (((fConst25 + -0.743130445f) / fConst24) + 1.4500711f);
		fConst57 = (2.0f * (1.4500711f - fConst53));
		fConst58 = (fConst31 + 1.4500711f);
		fConst59 = (((fConst25 + -0.157482162f) / fConst24) + 0.935140193f);
		fConst60 = (2.0f * (0.935140193f - fConst53));
		fConst61 = (fConst28 + 0.935140193f);
		fConst62 = tanf((19947.8691f / fConst0));
		fConst63 = (1.0f / fConst62);
		fConst64 = (1.0f / (((fConst63 + 0.157482162f) / fConst62) + 0.935140193f));
		fConst65 = mydsp_faustpower2_f(fConst62);
		fConst66 = (50.0638084f / fConst65);
		fConst67 = (2.0f * (0.935140193f - fConst66));
		fConst68 = (1.0f / (((fConst63 + 0.743130445f) / fConst62) + 1.4500711f));
		fConst69 = (11.0520525f / fConst65);
		fConst70 = (2.0f * (1.4500711f - fConst69));
		fConst71 = (1.0f / (((fConst63 + 3.18972731f) / fConst62) + 4.07678175f));
		fConst72 = (0.00176617282f / fConst65);
		fConst73 = (2.0f * (0.000407678192f - fConst72));
		fConst74 = (1.0f / (((fConst25 + 0.168404877f) / fConst24) + 1.06935835f));
		fConst75 = (2.0f * (53.5361519f - fConst53));
		fConst76 = (1.0f / (((fConst25 + 0.51247865f) / fConst24) + 0.689621389f));
		fConst77 = (2.0f * (7.62173128f - fConst53));
		fConst78 = (1.0f / (((fConst25 + 0.782413065f) / fConst24) + 0.245291501f));
		fConst79 = (9.99999975e-05f / fConst27);
		fConst80 = (2.0f * (0.000433227193f - fConst79));
		fConst81 = (((fConst25 + -0.782413065f) / fConst24) + 0.245291501f);
		fConst82 = (2.0f * (0.245291501f - fConst53));
		fConst83 = (fConst79 + 0.000433227193f);
		fConst84 = (((fConst25 + -0.51247865f) / fConst24) + 0.689621389f);
		fConst85 = (2.0f * (0.689621389f - fConst53));
		fConst86 = (fConst53 + 7.62173128f);
		fConst87 = (((fConst25 + -0.168404877f) / fConst24) + 1.06935835f);
		fConst88 = (2.0f * (1.06935835f - fConst53));
		fConst89 = (fConst53 + 53.5361519f);
		fConst90 = (((fConst63 + -3.18972731f) / fConst62) + 4.07678175f);
		fConst91 = (1.0f / fConst65);
		fConst92 = (2.0f * (4.07678175f - fConst91));
		fConst93 = (fConst72 + 0.000407678192f);
		fConst94 = (((fConst63 + -0.743130445f) / fConst62) + 1.4500711f);
		fConst95 = (2.0f * (1.4500711f - fConst91));
		fConst96 = (fConst69 + 1.4500711f);
		fConst97 = (((fConst63 + -0.157482162f) / fConst62) + 0.935140193f);
		fConst98 = (2.0f * (0.935140193f - fConst91));
		fConst99 = (fConst66 + 0.935140193f);
		fConst100 = tanf((12566.3711f / fConst0));
		fConst101 = (1.0f / fConst100);
		fConst102 = (1.0f / (((fConst101 + 0.157482162f) / fConst100) + 0.935140193f));
		fConst103 = mydsp_faustpower2_f(fConst100);
		fConst104 = (50.0638084f / fConst103);
		fConst105 = (2.0f * (0.935140193f - fConst104));
		fConst106 = (1.0f / (((fConst101 + 0.743130445f) / fConst100) + 1.4500711f));
		fConst107 = (11.0520525f / fConst103);
		fConst108 = (2.0f * (1.4500711f - fConst107));
		fConst109 = (1.0f / (((fConst101 + 3.18972731f) / fConst100) + 4.07678175f));
		fConst110 = (0.00176617282f / fConst103);
		fConst111 = (2.0f * (0.000407678192f - fConst110));
		fConst112 = (1.0f / (((fConst63 + 0.168404877f) / fConst62) + 1.06935835f));
		fConst113 = (2.0f * (53.5361519f - fConst91));
		fConst114 = (1.0f / (((fConst63 + 0.51247865f) / fConst62) + 0.689621389f));
		fConst115 = (2.0f * (7.62173128f - fConst91));
		fConst116 = (1.0f / (((fConst63 + 0.782413065f) / fConst62) + 0.245291501f));
		fConst117 = (9.99999975e-05f / fConst65);
		fConst118 = (2.0f * (0.000433227193f - fConst117));
		fConst119 = (((fConst63 + -0.782413065f) / fConst62) + 0.245291501f);
		fConst120 = (2.0f * (0.245291501f - fConst91));
		fConst121 = (fConst117 + 0.000433227193f);
		fConst122 = (((fConst63 + -0.51247865f) / fConst62) + 0.689621389f);
		fConst123 = (2.0f * (0.689621389f - fConst91));
		fConst124 = (fConst91 + 7.62173128f);
		fConst125 = (((fConst63 + -0.168404877f) / fConst62) + 1.06935835f);
		fConst126 = (2.0f * (1.06935835f - fConst91));
		fConst127 = (fConst91 + 53.5361519f);
		fConst128 = (((fConst101 + -3.18972731f) / fConst100) + 4.07678175f);
		fConst129 = (1.0f / fConst103);
		fConst130 = (2.0f * (4.07678175f - fConst129));
		fConst131 = (fConst110 + 0.000407678192f);
		fConst132 = (((fConst101 + -0.743130445f) / fConst100) + 1.4500711f);
		fConst133 = (2.0f * (1.4500711f - fConst129));
		fConst134 = (fConst107 + 1.4500711f);
		fConst135 = (((fConst101 + -0.157482162f) / fConst100) + 0.935140193f);
		fConst136 = (2.0f * (0.935140193f - fConst129));
		fConst137 = (fConst104 + 0.935140193f);
		fConst138 = tanf((7916.31738f / fConst0));
		fConst139 = (1.0f / fConst138);
		fConst140 = (1.0f / (((fConst139 + 0.157482162f) / fConst138) + 0.935140193f));
		fConst141 = mydsp_faustpower2_f(fConst138);
		fConst142 = (50.0638084f / fConst141);
		fConst143 = (2.0f * (0.935140193f - fConst142));
		fConst144 = (1.0f / (((fConst139 + 0.743130445f) / fConst138) + 1.4500711f));
		fConst145 = (11.0520525f / fConst141);
		fConst146 = (2.0f * (1.4500711f - fConst145));
		fConst147 = (1.0f / (((fConst139 + 3.18972731f) / fConst138) + 4.07678175f));
		fConst148 = (0.00176617282f / fConst141);
		fConst149 = (2.0f * (0.000407678192f - fConst148));
		fConst150 = (1.0f / (((fConst101 + 0.168404877f) / fConst100) + 1.06935835f));
		fConst151 = (2.0f * (53.5361519f - fConst129));
		fConst152 = (1.0f / (((fConst101 + 0.51247865f) / fConst100) + 0.689621389f));
		fConst153 = (2.0f * (7.62173128f - fConst129));
		fConst154 = (1.0f / (((fConst101 + 0.782413065f) / fConst100) + 0.245291501f));
		fConst155 = (9.99999975e-05f / fConst103);
		fConst156 = (2.0f * (0.000433227193f - fConst155));
		fConst157 = (((fConst101 + -0.782413065f) / fConst100) + 0.245291501f);
		fConst158 = (2.0f * (0.245291501f - fConst129));
		fConst159 = (fConst155 + 0.000433227193f);
		fConst160 = (((fConst101 + -0.51247865f) / fConst100) + 0.689621389f);
		fConst161 = (2.0f * (0.689621389f - fConst129));
		fConst162 = (fConst129 + 7.62173128f);
		fConst163 = (((fConst101 + -0.168404877f) / fConst100) + 1.06935835f);
		fConst164 = (2.0f * (1.06935835f - fConst129));
		fConst165 = (fConst129 + 53.5361519f);
		fConst166 = (((fConst139 + -3.18972731f) / fConst138) + 4.07678175f);
		fConst167 = (1.0f / fConst141);
		fConst168 = (2.0f * (4.07678175f - fConst167));
		fConst169 = (fConst148 + 0.000407678192f);
		fConst170 = (((fConst139 + -0.743130445f) / fConst138) + 1.4500711f);
		fConst171 = (2.0f * (1.4500711f - fConst167));
		fConst172 = (fConst145 + 1.4500711f);
		fConst173 = (((fConst139 + -0.157482162f) / fConst138) + 0.935140193f);
		fConst174 = (2.0f * (0.935140193f - fConst167));
		fConst175 = (fConst142 + 0.935140193f);
		fConst176 = tanf((4986.96729f / fConst0));
		fConst177 = (1.0f / fConst176);
		fConst178 = (1.0f / (((fConst177 + 0.157482162f) / fConst176) + 0.935140193f));
		fConst179 = mydsp_faustpower2_f(fConst176);
		fConst180 = (50.0638084f / fConst179);
		fConst181 = (2.0f * (0.935140193f - fConst180));
		fConst182 = (1.0f / (((fConst177 + 0.743130445f) / fConst176) + 1.4500711f));
		fConst183 = (11.0520525f / fConst179);
		fConst184 = (2.0f * (1.4500711f - fConst183));
		fConst185 = (1.0f / (((fConst177 + 3.18972731f) / fConst176) + 4.07678175f));
		fConst186 = (0.00176617282f / fConst179);
		fConst187 = (2.0f * (0.000407678192f - fConst186));
		fConst188 = (1.0f / (((fConst139 + 0.168404877f) / fConst138) + 1.06935835f));
		fConst189 = (2.0f * (53.5361519f - fConst167));
		fConst190 = (1.0f / (((fConst139 + 0.51247865f) / fConst138) + 0.689621389f));
		fConst191 = (2.0f * (7.62173128f - fConst167));
		fConst192 = (1.0f / (((fConst139 + 0.782413065f) / fConst138) + 0.245291501f));
		fConst193 = (9.99999975e-05f / fConst141);
		fConst194 = (2.0f * (0.000433227193f - fConst193));
		fConst195 = (((fConst139 + -0.782413065f) / fConst138) + 0.245291501f);
		fConst196 = (2.0f * (0.245291501f - fConst167));
		fConst197 = (fConst193 + 0.000433227193f);
		fConst198 = (((fConst139 + -0.51247865f) / fConst138) + 0.689621389f);
		fConst199 = (2.0f * (0.689621389f - fConst167));
		fConst200 = (fConst167 + 7.62173128f);
		fConst201 = (((fConst139 + -0.168404877f) / fConst138) + 1.06935835f);
		fConst202 = (2.0f * (1.06935835f - fConst167));
		fConst203 = (fConst167 + 53.5361519f);
		fConst204 = (((fConst177 + -3.18972731f) / fConst176) + 4.07678175f);
		fConst205 = (1.0f / fConst179);
		fConst206 = (2.0f * (4.07678175f - fConst205));
		fConst207 = (fConst186 + 0.000407678192f);
		fConst208 = (((fConst177 + -0.743130445f) / fConst176) + 1.4500711f);
		fConst209 = (2.0f * (1.4500711f - fConst205));
		fConst210 = (fConst183 + 1.4500711f);
		fConst211 = (((fConst177 + -0.157482162f) / fConst176) + 0.935140193f);
		fConst212 = (2.0f * (0.935140193f - fConst205));
		fConst213 = (fConst180 + 0.935140193f);
		fConst214 = tanf((3141.59277f / fConst0));
		fConst215 = (1.0f / fConst214);
		fConst216 = (1.0f / (((fConst215 + 0.157482162f) / fConst214) + 0.935140193f));
		fConst217 = mydsp_faustpower2_f(fConst214);
		fConst218 = (50.0638084f / fConst217);
		fConst219 = (2.0f * (0.935140193f - fConst218));
		fConst220 = (1.0f / (((fConst215 + 0.743130445f) / fConst214) + 1.4500711f));
		fConst221 = (11.0520525f / fConst217);
		fConst222 = (2.0f * (1.4500711f - fConst221));
		fConst223 = (1.0f / (((fConst215 + 3.18972731f) / fConst214) + 4.07678175f));
		fConst224 = (0.00176617282f / fConst217);
		fConst225 = (2.0f * (0.000407678192f - fConst224));
		fConst226 = (1.0f / (((fConst177 + 0.168404877f) / fConst176) + 1.06935835f));
		fConst227 = (2.0f * (53.5361519f - fConst205));
		fConst228 = (1.0f / (((fConst177 + 0.51247865f) / fConst176) + 0.689621389f));
		fConst229 = (2.0f * (7.62173128f - fConst205));
		fConst230 = (1.0f / (((fConst177 + 0.782413065f) / fConst176) + 0.245291501f));
		fConst231 = (9.99999975e-05f / fConst179);
		fConst232 = (2.0f * (0.000433227193f - fConst231));
		fConst233 = (((fConst177 + -0.782413065f) / fConst176) + 0.245291501f);
		fConst234 = (2.0f * (0.245291501f - fConst205));
		fConst235 = (fConst231 + 0.000433227193f);
		fConst236 = (((fConst177 + -0.51247865f) / fConst176) + 0.689621389f);
		fConst237 = (2.0f * (0.689621389f - fConst205));
		fConst238 = (fConst205 + 7.62173128f);
		fConst239 = (((fConst177 + -0.168404877f) / fConst176) + 1.06935835f);
		fConst240 = (2.0f * (1.06935835f - fConst205));
		fConst241 = (fConst205 + 53.5361519f);
		fConst242 = (((fConst215 + -3.18972731f) / fConst214) + 4.07678175f);
		fConst243 = (1.0f / fConst217);
		fConst244 = (2.0f * (4.07678175f - fConst243));
		fConst245 = (fConst224 + 0.000407678192f);
		fConst246 = (((fConst215 + -0.743130445f) / fConst214) + 1.4500711f);
		fConst247 = (2.0f * (1.4500711f - fConst243));
		fConst248 = (fConst221 + 1.4500711f);
		fConst249 = (((fConst215 + -0.157482162f) / fConst214) + 0.935140193f);
		fConst250 = (2.0f * (0.935140193f - fConst243));
		fConst251 = (fConst218 + 0.935140193f);
		fConst252 = tanf((1979.07935f / fConst0));
		fConst253 = (1.0f / fConst252);
		fConst254 = (1.0f / (((fConst253 + 0.157482162f) / fConst252) + 0.935140193f));
		fConst255 = mydsp_faustpower2_f(fConst252);
		fConst256 = (50.0638084f / fConst255);
		fConst257 = (2.0f * (0.935140193f - fConst256));
		fConst258 = (1.0f / (((fConst253 + 0.743130445f) / fConst252) + 1.4500711f));
		fConst259 = (11.0520525f / fConst255);
		fConst260 = (2.0f * (1.4500711f - fConst259));
		fConst261 = (1.0f / (((fConst253 + 3.18972731f) / fConst252) + 4.07678175f));
		fConst262 = (0.00176617282f / fConst255);
		fConst263 = (2.0f * (0.000407678192f - fConst262));
		fConst264 = (1.0f / (((fConst215 + 0.168404877f) / fConst214) + 1.06935835f));
		fConst265 = (2.0f * (53.5361519f - fConst243));
		fConst266 = (1.0f / (((fConst215 + 0.51247865f) / fConst214) + 0.689621389f));
		fConst267 = (2.0f * (7.62173128f - fConst243));
		fConst268 = (1.0f / (((fConst215 + 0.782413065f) / fConst214) + 0.245291501f));
		fConst269 = (9.99999975e-05f / fConst217);
		fConst270 = (2.0f * (0.000433227193f - fConst269));
		fConst271 = (((fConst215 + -0.782413065f) / fConst214) + 0.245291501f);
		fConst272 = (2.0f * (0.245291501f - fConst243));
		fConst273 = (fConst269 + 0.000433227193f);
		fConst274 = (((fConst215 + -0.51247865f) / fConst214) + 0.689621389f);
		fConst275 = (2.0f * (0.689621389f - fConst243));
		fConst276 = (fConst243 + 7.62173128f);
		fConst277 = (((fConst215 + -0.168404877f) / fConst214) + 1.06935835f);
		fConst278 = (2.0f * (1.06935835f - fConst243));
		fConst279 = (fConst243 + 53.5361519f);
		fConst280 = (((fConst253 + -3.18972731f) / fConst252) + 4.07678175f);
		fConst281 = (1.0f / fConst255);
		fConst282 = (2.0f * (4.07678175f - fConst281));
		fConst283 = (fConst262 + 0.000407678192f);
		fConst284 = (((fConst253 + -0.743130445f) / fConst252) + 1.4500711f);
		fConst285 = (2.0f * (1.4500711f - fConst281));
		fConst286 = (fConst259 + 1.4500711f);
		fConst287 = (((fConst253 + -0.157482162f) / fConst252) + 0.935140193f);
		fConst288 = (2.0f * (0.935140193f - fConst281));
		fConst289 = (fConst256 + 0.935140193f);
		fConst290 = tanf((1246.74182f / fConst0));
		fConst291 = (1.0f / fConst290);
		fConst292 = (1.0f / (((fConst291 + 0.157482162f) / fConst290) + 0.935140193f));
		fConst293 = mydsp_faustpower2_f(fConst290);
		fConst294 = (50.0638084f / fConst293);
		fConst295 = (2.0f * (0.935140193f - fConst294));
		fConst296 = (1.0f / (((fConst291 + 0.743130445f) / fConst290) + 1.4500711f));
		fConst297 = (11.0520525f / fConst293);
		fConst298 = (2.0f * (1.4500711f - fConst297));
		fConst299 = (1.0f / (((fConst291 + 3.18972731f) / fConst290) + 4.07678175f));
		fConst300 = (0.00176617282f / fConst293);
		fConst301 = (2.0f * (0.000407678192f - fConst300));
		fConst302 = (1.0f / (((fConst253 + 0.168404877f) / fConst252) + 1.06935835f));
		fConst303 = (2.0f * (53.5361519f - fConst281));
		fConst304 = (1.0f / (((fConst253 + 0.51247865f) / fConst252) + 0.689621389f));
		fConst305 = (2.0f * (7.62173128f - fConst281));
		fConst306 = (1.0f / (((fConst253 + 0.782413065f) / fConst252) + 0.245291501f));
		fConst307 = (9.99999975e-05f / fConst255);
		fConst308 = (2.0f * (0.000433227193f - fConst307));
		fConst309 = (((fConst253 + -0.782413065f) / fConst252) + 0.245291501f);
		fConst310 = (2.0f * (0.245291501f - fConst281));
		fConst311 = (fConst307 + 0.000433227193f);
		fConst312 = (((fConst253 + -0.51247865f) / fConst252) + 0.689621389f);
		fConst313 = (2.0f * (0.689621389f - fConst281));
		fConst314 = (fConst281 + 7.62173128f);
		fConst315 = (((fConst253 + -0.168404877f) / fConst252) + 1.06935835f);
		fConst316 = (2.0f * (1.06935835f - fConst281));
		fConst317 = (fConst281 + 53.5361519f);
		fConst318 = (((fConst291 + -3.18972731f) / fConst290) + 4.07678175f);
		fConst319 = (1.0f / fConst293);
		fConst320 = (2.0f * (4.07678175f - fConst319));
		fConst321 = (fConst300 + 0.000407678192f);
		fConst322 = (((fConst291 + -0.743130445f) / fConst290) + 1.4500711f);
		fConst323 = (2.0f * (1.4500711f - fConst319));
		fConst324 = (fConst297 + 1.4500711f);
		fConst325 = (((fConst291 + -0.157482162f) / fConst290) + 0.935140193f);
		fConst326 = (2.0f * (0.935140193f - fConst319));
		fConst327 = (fConst294 + 0.935140193f);
		fConst328 = tanf((785.398193f / fConst0));
		fConst329 = (1.0f / fConst328);
		fConst330 = (1.0f / (((fConst329 + 0.157482162f) / fConst328) + 0.935140193f));
		fConst331 = mydsp_faustpower2_f(fConst328);
		fConst332 = (50.0638084f / fConst331);
		fConst333 = (2.0f * (0.935140193f - fConst332));
		fConst334 = (1.0f / (((fConst329 + 0.743130445f) / fConst328) + 1.4500711f));
		fConst335 = (11.0520525f / fConst331);
		fConst336 = (2.0f * (1.4500711f - fConst335));
		fConst337 = (1.0f / (((fConst329 + 3.18972731f) / fConst328) + 4.07678175f));
		fConst338 = (0.00176617282f / fConst331);
		fConst339 = (2.0f * (0.000407678192f - fConst338));
		fConst340 = (1.0f / (((fConst291 + 0.168404877f) / fConst290) + 1.06935835f));
		fConst341 = (2.0f * (53.5361519f - fConst319));
		fConst342 = (1.0f / (((fConst291 + 0.51247865f) / fConst290) + 0.689621389f));
		fConst343 = (2.0f * (7.62173128f - fConst319));
		fConst344 = (1.0f / (((fConst291 + 0.782413065f) / fConst290) + 0.245291501f));
		fConst345 = (9.99999975e-05f / fConst293);
		fConst346 = (2.0f * (0.000433227193f - fConst345));
		fConst347 = (((fConst291 + -0.782413065f) / fConst290) + 0.245291501f);
		fConst348 = (2.0f * (0.245291501f - fConst319));
		fConst349 = (fConst345 + 0.000433227193f);
		fConst350 = (((fConst291 + -0.51247865f) / fConst290) + 0.689621389f);
		fConst351 = (2.0f * (0.689621389f - fConst319));
		fConst352 = (fConst319 + 7.62173128f);
		fConst353 = (((fConst291 + -0.168404877f) / fConst290) + 1.06935835f);
		fConst354 = (2.0f * (1.06935835f - fConst319));
		fConst355 = (fConst319 + 53.5361519f);
		fConst356 = (((fConst329 + -3.18972731f) / fConst328) + 4.07678175f);
		fConst357 = (1.0f / fConst331);
		fConst358 = (2.0f * (4.07678175f - fConst357));
		fConst359 = (fConst338 + 0.000407678192f);
		fConst360 = (((fConst329 + -0.743130445f) / fConst328) + 1.4500711f);
		fConst361 = (2.0f * (1.4500711f - fConst357));
		fConst362 = (fConst335 + 1.4500711f);
		fConst363 = (((fConst329 + -0.157482162f) / fConst328) + 0.935140193f);
		fConst364 = (2.0f * (0.935140193f - fConst357));
		fConst365 = (fConst332 + 0.935140193f);
		fConst366 = tanf((494.769836f / fConst0));
		fConst367 = (1.0f / fConst366);
		fConst368 = (1.0f / (((fConst367 + 0.157482162f) / fConst366) + 0.935140193f));
		fConst369 = mydsp_faustpower2_f(fConst366);
		fConst370 = (50.0638084f / fConst369);
		fConst371 = (2.0f * (0.935140193f - fConst370));
		fConst372 = (1.0f / (((fConst367 + 0.743130445f) / fConst366) + 1.4500711f));
		fConst373 = (11.0520525f / fConst369);
		fConst374 = (2.0f * (1.4500711f - fConst373));
		fConst375 = (1.0f / (((fConst367 + 3.18972731f) / fConst366) + 4.07678175f));
		fConst376 = (0.00176617282f / fConst369);
		fConst377 = (2.0f * (0.000407678192f - fConst376));
		fConst378 = (1.0f / (((fConst329 + 0.168404877f) / fConst328) + 1.06935835f));
		fConst379 = (2.0f * (53.5361519f - fConst357));
		fConst380 = (1.0f / (((fConst329 + 0.51247865f) / fConst328) + 0.689621389f));
		fConst381 = (2.0f * (7.62173128f - fConst357));
		fConst382 = (1.0f / (((fConst329 + 0.782413065f) / fConst328) + 0.245291501f));
		fConst383 = (9.99999975e-05f / fConst331);
		fConst384 = (2.0f * (0.000433227193f - fConst383));
		fConst385 = (((fConst329 + -0.782413065f) / fConst328) + 0.245291501f);
		fConst386 = (2.0f * (0.245291501f - fConst357));
		fConst387 = (fConst383 + 0.000433227193f);
		fConst388 = (((fConst329 + -0.51247865f) / fConst328) + 0.689621389f);
		fConst389 = (2.0f * (0.689621389f - fConst357));
		fConst390 = (fConst357 + 7.62173128f);
		fConst391 = (((fConst329 + -0.168404877f) / fConst328) + 1.06935835f);
		fConst392 = (2.0f * (1.06935835f - fConst357));
		fConst393 = (fConst357 + 53.5361519f);
		fConst394 = (((fConst367 + -3.18972731f) / fConst366) + 4.07678175f);
		fConst395 = (1.0f / fConst369);
		fConst396 = (2.0f * (4.07678175f - fConst395));
		fConst397 = (fConst376 + 0.000407678192f);
		fConst398 = (((fConst367 + -0.743130445f) / fConst366) + 1.4500711f);
		fConst399 = (2.0f * (1.4500711f - fConst395));
		fConst400 = (fConst373 + 1.4500711f);
		fConst401 = (((fConst367 + -0.157482162f) / fConst366) + 0.935140193f);
		fConst402 = (2.0f * (0.935140193f - fConst395));
		fConst403 = (fConst370 + 0.935140193f);
		fConst404 = tanf((311.685455f / fConst0));
		fConst405 = (1.0f / fConst404);
		fConst406 = (1.0f / (((fConst405 + 0.157482162f) / fConst404) + 0.935140193f));
		fConst407 = mydsp_faustpower2_f(fConst404);
		fConst408 = (50.0638084f / fConst407);
		fConst409 = (2.0f * (0.935140193f - fConst408));
		fConst410 = (1.0f / (((fConst405 + 0.743130445f) / fConst404) + 1.4500711f));
		fConst411 = (11.0520525f / fConst407);
		fConst412 = (2.0f * (1.4500711f - fConst411));
		fConst413 = (1.0f / (((fConst405 + 3.18972731f) / fConst404) + 4.07678175f));
		fConst414 = (0.00176617282f / fConst407);
		fConst415 = (2.0f * (0.000407678192f - fConst414));
		fConst416 = (1.0f / (((fConst367 + 0.168404877f) / fConst366) + 1.06935835f));
		fConst417 = (2.0f * (53.5361519f - fConst395));
		fConst418 = (1.0f / (((fConst367 + 0.51247865f) / fConst366) + 0.689621389f));
		fConst419 = (2.0f * (7.62173128f - fConst395));
		fConst420 = (1.0f / (((fConst367 + 0.782413065f) / fConst366) + 0.245291501f));
		fConst421 = (9.99999975e-05f / fConst369);
		fConst422 = (2.0f * (0.000433227193f - fConst421));
		fConst423 = (((fConst367 + -0.782413065f) / fConst366) + 0.245291501f);
		fConst424 = (2.0f * (0.245291501f - fConst395));
		fConst425 = (fConst421 + 0.000433227193f);
		fConst426 = (((fConst367 + -0.51247865f) / fConst366) + 0.689621389f);
		fConst427 = (2.0f * (0.689621389f - fConst395));
		fConst428 = (fConst395 + 7.62173128f);
		fConst429 = (((fConst367 + -0.168404877f) / fConst366) + 1.06935835f);
		fConst430 = (2.0f * (1.06935835f - fConst395));
		fConst431 = (fConst395 + 53.5361519f);
		fConst432 = (((fConst405 + -3.18972731f) / fConst404) + 4.07678175f);
		fConst433 = (1.0f / fConst407);
		fConst434 = (2.0f * (4.07678175f - fConst433));
		fConst435 = (fConst414 + 0.000407678192f);
		fConst436 = (((fConst405 + -0.743130445f) / fConst404) + 1.4500711f);
		fConst437 = (2.0f * (1.4500711f - fConst433));
		fConst438 = (fConst411 + 1.4500711f);
		fConst439 = (((fConst405 + -0.157482162f) / fConst404) + 0.935140193f);
		fConst440 = (2.0f * (0.935140193f - fConst433));
		fConst441 = (fConst408 + 0.935140193f);
		fConst442 = tanf((196.349548f / fConst0));
		fConst443 = (1.0f / fConst442);
		fConst444 = (1.0f / (((fConst443 + 0.157482162f) / fConst442) + 0.935140193f));
		fConst445 = mydsp_faustpower2_f(fConst442);
		fConst446 = (50.0638084f / fConst445);
		fConst447 = (2.0f * (0.935140193f - fConst446));
		fConst448 = (1.0f / (((fConst443 + 0.743130445f) / fConst442) + 1.4500711f));
		fConst449 = (11.0520525f / fConst445);
		fConst450 = (2.0f * (1.4500711f - fConst449));
		fConst451 = (1.0f / (((fConst443 + 3.18972731f) / fConst442) + 4.07678175f));
		fConst452 = (0.00176617282f / fConst445);
		fConst453 = (2.0f * (0.000407678192f - fConst452));
		fConst454 = (1.0f / (((fConst405 + 0.168404877f) / fConst404) + 1.06935835f));
		fConst455 = (2.0f * (53.5361519f - fConst433));
		fConst456 = (1.0f / (((fConst405 + 0.51247865f) / fConst404) + 0.689621389f));
		fConst457 = (2.0f * (7.62173128f - fConst433));
		fConst458 = (1.0f / (((fConst405 + 0.782413065f) / fConst404) + 0.245291501f));
		fConst459 = (9.99999975e-05f / fConst407);
		fConst460 = (2.0f * (0.000433227193f - fConst459));
		fConst461 = (((fConst405 + -0.782413065f) / fConst404) + 0.245291501f);
		fConst462 = (2.0f * (0.245291501f - fConst433));
		fConst463 = (fConst459 + 0.000433227193f);
		fConst464 = (((fConst405 + -0.51247865f) / fConst404) + 0.689621389f);
		fConst465 = (2.0f * (0.689621389f - fConst433));
		fConst466 = (fConst433 + 7.62173128f);
		fConst467 = (((fConst405 + -0.168404877f) / fConst404) + 1.06935835f);
		fConst468 = (2.0f * (1.06935835f - fConst433));
		fConst469 = (fConst433 + 53.5361519f);
		fConst470 = (((fConst443 + -3.18972731f) / fConst442) + 4.07678175f);
		fConst471 = (1.0f / fConst445);
		fConst472 = (2.0f * (4.07678175f - fConst471));
		fConst473 = (fConst452 + 0.000407678192f);
		fConst474 = (((fConst443 + -0.743130445f) / fConst442) + 1.4500711f);
		fConst475 = (2.0f * (1.4500711f - fConst471));
		fConst476 = (fConst449 + 1.4500711f);
		fConst477 = (((fConst443 + -0.157482162f) / fConst442) + 0.935140193f);
		fConst478 = (2.0f * (0.935140193f - fConst471));
		fConst479 = (fConst446 + 0.935140193f);
		fConst480 = tanf((123.692459f / fConst0));
		fConst481 = (1.0f / fConst480);
		fConst482 = (1.0f / (((fConst481 + 0.157482162f) / fConst480) + 0.935140193f));
		fConst483 = mydsp_faustpower2_f(fConst480);
		fConst484 = (50.0638084f / fConst483);
		fConst485 = (2.0f * (0.935140193f - fConst484));
		fConst486 = (1.0f / (((fConst481 + 0.743130445f) / fConst480) + 1.4500711f));
		fConst487 = (11.0520525f / fConst483);
		fConst488 = (2.0f * (1.4500711f - fConst487));
		fConst489 = (1.0f / (((fConst481 + 3.18972731f) / fConst480) + 4.07678175f));
		fConst490 = (0.00176617282f / fConst483);
		fConst491 = (2.0f * (0.000407678192f - fConst490));
		fConst492 = (1.0f / (((fConst443 + 0.168404877f) / fConst442) + 1.06935835f));
		fConst493 = (2.0f * (53.5361519f - fConst471));
		fConst494 = (1.0f / (((fConst443 + 0.51247865f) / fConst442) + 0.689621389f));
		fConst495 = (2.0f * (7.62173128f - fConst471));
		fConst496 = (1.0f / (((fConst443 + 0.782413065f) / fConst442) + 0.245291501f));
		fConst497 = (9.99999975e-05f / fConst445);
		fConst498 = (2.0f * (0.000433227193f - fConst497));
		fConst499 = (((fConst443 + -0.782413065f) / fConst442) + 0.245291501f);
		fConst500 = (2.0f * (0.245291501f - fConst471));
		fConst501 = (fConst497 + 0.000433227193f);
		fConst502 = (((fConst443 + -0.51247865f) / fConst442) + 0.689621389f);
		fConst503 = (2.0f * (0.689621389f - fConst471));
		fConst504 = (fConst471 + 7.62173128f);
		fConst505 = (((fConst443 + -0.168404877f) / fConst442) + 1.06935835f);
		fConst506 = (2.0f * (1.06935835f - fConst471));
		fConst507 = (fConst471 + 53.5361519f);
		fConst508 = (((fConst481 + -3.18972731f) / fConst480) + 4.07678175f);
		fConst509 = (1.0f / fConst483);
		fConst510 = (2.0f * (4.07678175f - fConst509));
		fConst511 = (fConst490 + 0.000407678192f);
		fConst512 = (((fConst481 + -0.743130445f) / fConst480) + 1.4500711f);
		fConst513 = (2.0f * (1.4500711f - fConst509));
		fConst514 = (fConst487 + 1.4500711f);
		fConst515 = (((fConst481 + -0.157482162f) / fConst480) + 0.935140193f);
		fConst516 = (2.0f * (0.935140193f - fConst509));
		fConst517 = (fConst484 + 0.935140193f);
		fConst518 = (1.0f / (((fConst481 + 0.168404877f) / fConst480) + 1.06935835f));
		fConst519 = (2.0f * (53.5361519f - fConst509));
		fConst520 = (1.0f / (((fConst481 + 0.51247865f) / fConst480) + 0.689621389f));
		fConst521 = (2.0f * (7.62173128f - fConst509));
		fConst522 = (1.0f / (((fConst481 + 0.782413065f) / fConst480) + 0.245291501f));
		fConst523 = (9.99999975e-05f / fConst483);
		fConst524 = (2.0f * (0.000433227193f - fConst523));
		fConst525 = (((fConst481 + -0.782413065f) / fConst480) + 0.245291501f);
		fConst526 = (2.0f * (0.245291501f - fConst509));
		fConst527 = (fConst523 + 0.000433227193f);
		fConst528 = (((fConst481 + -0.51247865f) / fConst480) + 0.689621389f);
		fConst529 = (2.0f * (0.689621389f - fConst509));
		fConst530 = (fConst509 + 7.62173128f);
		fConst531 = (((fConst481 + -0.168404877f) / fConst480) + 1.06935835f);
		fConst532 = (2.0f * (1.06935835f - fConst509));
		fConst533 = (fConst509 + 53.5361519f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec3[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec10[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec9[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec8[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec5[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec4[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec17[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec16[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec15[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec14[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec13[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec12[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec24[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec23[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec22[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec21[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec19[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec18[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec31[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec30[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec29[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec28[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec27[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec26[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec25[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec38[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec37[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec36[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec35[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec34[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec33[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec32[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec45[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec44[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec43[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec42[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec41[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec40[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec39[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec52[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec51[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec50[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec49[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec48[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec47[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec46[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec59[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec58[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec57[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec56[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec55[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec54[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec53[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec66[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec65[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec64[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec63[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec62[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec61[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec60[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec73[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec72[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec71[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec70[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec69[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec68[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec67[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec80[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec79[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec78[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec77[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec76[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec75[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec74[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec87[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec86[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec85[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec84[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec83[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec82[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec81[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec94[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec93[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec92[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec91[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec90[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec89[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec88[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec98[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec97[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec96[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec95[l98] = 0.0f;
			
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
		ui_interface->openVerticalBox("spectralLevel");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph14, "0", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f9510430d70", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f951041f780", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95103f9a20", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95103d7c40", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "4", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95103b5e60", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "5", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f9510394080", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "6", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95103722a0", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95103504c0", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "8", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f951032e6e0", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "9", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f951030c900", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "10", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95102e6ba0", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "11", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95102c4dc0", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "12", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f95102a2fe0", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "13", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f9510281200", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "14", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7f951025e250", &fVbargraph0, -50.0f, 10.0f);
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
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = expf((0.0f - (fConst1 / float(fHslider1))));
		float fSlow2 = (1.0f - fSlow1);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec3[0] = (fTemp0 - (fConst11 * ((fConst14 * fRec3[2]) + (fConst16 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst17 * fRec3[0])) + (fConst17 * fRec3[2]))) - (fConst8 * ((fConst18 * fRec2[2]) + (fConst19 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst20 * fRec2[0])) + (fConst20 * fRec2[2]))) - (fConst4 * ((fConst21 * fRec1[2]) + (fConst22 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * fabsf((fConst4 * (((fConst7 * fRec1[1]) + (fConst23 * fRec1[0])) + (fConst23 * fRec1[2]))))));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec0[0])))));
			fRec10[0] = (fTemp0 - (fConst40 * ((fConst43 * fRec10[2]) + (fConst44 * fRec10[1]))));
			fRec9[0] = ((fConst40 * (((fConst42 * fRec10[1]) + (fConst45 * fRec10[0])) + (fConst45 * fRec10[2]))) - (fConst38 * ((fConst46 * fRec9[2]) + (fConst47 * fRec9[1]))));
			fRec8[0] = ((fConst38 * (((fConst39 * fRec9[1]) + (fConst48 * fRec9[0])) + (fConst48 * fRec9[2]))) - (fConst36 * ((fConst49 * fRec8[2]) + (fConst50 * fRec8[1]))));
			float fTemp1 = (fConst36 * (((fConst37 * fRec8[1]) + (fConst51 * fRec8[0])) + (fConst51 * fRec8[2])));
			fRec7[0] = (fTemp1 - (fConst33 * ((fConst52 * fRec7[2]) + (fConst54 * fRec7[1]))));
			fRec6[0] = ((fConst33 * (((fConst35 * fRec7[1]) + (fConst55 * fRec7[0])) + (fConst55 * fRec7[2]))) - (fConst30 * ((fConst56 * fRec6[2]) + (fConst57 * fRec6[1]))));
			fRec5[0] = ((fConst30 * (((fConst32 * fRec6[1]) + (fConst58 * fRec6[0])) + (fConst58 * fRec6[2]))) - (fConst26 * ((fConst59 * fRec5[2]) + (fConst60 * fRec5[1]))));
			fRec4[0] = ((fSlow1 * fRec4[1]) + (fSlow2 * fabsf((fConst26 * (((fConst29 * fRec5[1]) + (fConst61 * fRec5[0])) + (fConst61 * fRec5[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec4[0])))));
			fRec17[0] = (fTemp1 - (fConst78 * ((fConst81 * fRec17[2]) + (fConst82 * fRec17[1]))));
			fRec16[0] = ((fConst78 * (((fConst80 * fRec17[1]) + (fConst83 * fRec17[0])) + (fConst83 * fRec17[2]))) - (fConst76 * ((fConst84 * fRec16[2]) + (fConst85 * fRec16[1]))));
			fRec15[0] = ((fConst76 * (((fConst77 * fRec16[1]) + (fConst86 * fRec16[0])) + (fConst86 * fRec16[2]))) - (fConst74 * ((fConst87 * fRec15[2]) + (fConst88 * fRec15[1]))));
			float fTemp2 = (fConst74 * (((fConst75 * fRec15[1]) + (fConst89 * fRec15[0])) + (fConst89 * fRec15[2])));
			fRec14[0] = (fTemp2 - (fConst71 * ((fConst90 * fRec14[2]) + (fConst92 * fRec14[1]))));
			fRec13[0] = ((fConst71 * (((fConst73 * fRec14[1]) + (fConst93 * fRec14[0])) + (fConst93 * fRec14[2]))) - (fConst68 * ((fConst94 * fRec13[2]) + (fConst95 * fRec13[1]))));
			fRec12[0] = ((fConst68 * (((fConst70 * fRec13[1]) + (fConst96 * fRec13[0])) + (fConst96 * fRec13[2]))) - (fConst64 * ((fConst97 * fRec12[2]) + (fConst98 * fRec12[1]))));
			fRec11[0] = ((fSlow1 * fRec11[1]) + (fSlow2 * fabsf((fConst64 * (((fConst67 * fRec12[1]) + (fConst99 * fRec12[0])) + (fConst99 * fRec12[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec11[0])))));
			fRec24[0] = (fTemp2 - (fConst116 * ((fConst119 * fRec24[2]) + (fConst120 * fRec24[1]))));
			fRec23[0] = ((fConst116 * (((fConst118 * fRec24[1]) + (fConst121 * fRec24[0])) + (fConst121 * fRec24[2]))) - (fConst114 * ((fConst122 * fRec23[2]) + (fConst123 * fRec23[1]))));
			fRec22[0] = ((fConst114 * (((fConst115 * fRec23[1]) + (fConst124 * fRec23[0])) + (fConst124 * fRec23[2]))) - (fConst112 * ((fConst125 * fRec22[2]) + (fConst126 * fRec22[1]))));
			float fTemp3 = (fConst112 * (((fConst113 * fRec22[1]) + (fConst127 * fRec22[0])) + (fConst127 * fRec22[2])));
			fRec21[0] = (fTemp3 - (fConst109 * ((fConst128 * fRec21[2]) + (fConst130 * fRec21[1]))));
			fRec20[0] = ((fConst109 * (((fConst111 * fRec21[1]) + (fConst131 * fRec21[0])) + (fConst131 * fRec21[2]))) - (fConst106 * ((fConst132 * fRec20[2]) + (fConst133 * fRec20[1]))));
			fRec19[0] = ((fConst106 * (((fConst108 * fRec20[1]) + (fConst134 * fRec20[0])) + (fConst134 * fRec20[2]))) - (fConst102 * ((fConst135 * fRec19[2]) + (fConst136 * fRec19[1]))));
			fRec18[0] = ((fSlow1 * fRec18[1]) + (fSlow2 * fabsf((fConst102 * (((fConst105 * fRec19[1]) + (fConst137 * fRec19[0])) + (fConst137 * fRec19[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec18[0])))));
			fRec31[0] = (fTemp3 - (fConst154 * ((fConst157 * fRec31[2]) + (fConst158 * fRec31[1]))));
			fRec30[0] = ((fConst154 * (((fConst156 * fRec31[1]) + (fConst159 * fRec31[0])) + (fConst159 * fRec31[2]))) - (fConst152 * ((fConst160 * fRec30[2]) + (fConst161 * fRec30[1]))));
			fRec29[0] = ((fConst152 * (((fConst153 * fRec30[1]) + (fConst162 * fRec30[0])) + (fConst162 * fRec30[2]))) - (fConst150 * ((fConst163 * fRec29[2]) + (fConst164 * fRec29[1]))));
			float fTemp4 = (fConst150 * (((fConst151 * fRec29[1]) + (fConst165 * fRec29[0])) + (fConst165 * fRec29[2])));
			fRec28[0] = (fTemp4 - (fConst147 * ((fConst166 * fRec28[2]) + (fConst168 * fRec28[1]))));
			fRec27[0] = ((fConst147 * (((fConst149 * fRec28[1]) + (fConst169 * fRec28[0])) + (fConst169 * fRec28[2]))) - (fConst144 * ((fConst170 * fRec27[2]) + (fConst171 * fRec27[1]))));
			fRec26[0] = ((fConst144 * (((fConst146 * fRec27[1]) + (fConst172 * fRec27[0])) + (fConst172 * fRec27[2]))) - (fConst140 * ((fConst173 * fRec26[2]) + (fConst174 * fRec26[1]))));
			fRec25[0] = ((fSlow1 * fRec25[1]) + (fSlow2 * fabsf((fConst140 * (((fConst143 * fRec26[1]) + (fConst175 * fRec26[0])) + (fConst175 * fRec26[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec25[0])))));
			fRec38[0] = (fTemp4 - (fConst192 * ((fConst195 * fRec38[2]) + (fConst196 * fRec38[1]))));
			fRec37[0] = ((fConst192 * (((fConst194 * fRec38[1]) + (fConst197 * fRec38[0])) + (fConst197 * fRec38[2]))) - (fConst190 * ((fConst198 * fRec37[2]) + (fConst199 * fRec37[1]))));
			fRec36[0] = ((fConst190 * (((fConst191 * fRec37[1]) + (fConst200 * fRec37[0])) + (fConst200 * fRec37[2]))) - (fConst188 * ((fConst201 * fRec36[2]) + (fConst202 * fRec36[1]))));
			float fTemp5 = (fConst188 * (((fConst189 * fRec36[1]) + (fConst203 * fRec36[0])) + (fConst203 * fRec36[2])));
			fRec35[0] = (fTemp5 - (fConst185 * ((fConst204 * fRec35[2]) + (fConst206 * fRec35[1]))));
			fRec34[0] = ((fConst185 * (((fConst187 * fRec35[1]) + (fConst207 * fRec35[0])) + (fConst207 * fRec35[2]))) - (fConst182 * ((fConst208 * fRec34[2]) + (fConst209 * fRec34[1]))));
			fRec33[0] = ((fConst182 * (((fConst184 * fRec34[1]) + (fConst210 * fRec34[0])) + (fConst210 * fRec34[2]))) - (fConst178 * ((fConst211 * fRec33[2]) + (fConst212 * fRec33[1]))));
			fRec32[0] = ((fSlow1 * fRec32[1]) + (fSlow2 * fabsf((fConst178 * (((fConst181 * fRec33[1]) + (fConst213 * fRec33[0])) + (fConst213 * fRec33[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec32[0])))));
			fRec45[0] = (fTemp5 - (fConst230 * ((fConst233 * fRec45[2]) + (fConst234 * fRec45[1]))));
			fRec44[0] = ((fConst230 * (((fConst232 * fRec45[1]) + (fConst235 * fRec45[0])) + (fConst235 * fRec45[2]))) - (fConst228 * ((fConst236 * fRec44[2]) + (fConst237 * fRec44[1]))));
			fRec43[0] = ((fConst228 * (((fConst229 * fRec44[1]) + (fConst238 * fRec44[0])) + (fConst238 * fRec44[2]))) - (fConst226 * ((fConst239 * fRec43[2]) + (fConst240 * fRec43[1]))));
			float fTemp6 = (fConst226 * (((fConst227 * fRec43[1]) + (fConst241 * fRec43[0])) + (fConst241 * fRec43[2])));
			fRec42[0] = (fTemp6 - (fConst223 * ((fConst242 * fRec42[2]) + (fConst244 * fRec42[1]))));
			fRec41[0] = ((fConst223 * (((fConst225 * fRec42[1]) + (fConst245 * fRec42[0])) + (fConst245 * fRec42[2]))) - (fConst220 * ((fConst246 * fRec41[2]) + (fConst247 * fRec41[1]))));
			fRec40[0] = ((fConst220 * (((fConst222 * fRec41[1]) + (fConst248 * fRec41[0])) + (fConst248 * fRec41[2]))) - (fConst216 * ((fConst249 * fRec40[2]) + (fConst250 * fRec40[1]))));
			fRec39[0] = ((fSlow1 * fRec39[1]) + (fSlow2 * fabsf((fConst216 * (((fConst219 * fRec40[1]) + (fConst251 * fRec40[0])) + (fConst251 * fRec40[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec39[0])))));
			fRec52[0] = (fTemp6 - (fConst268 * ((fConst271 * fRec52[2]) + (fConst272 * fRec52[1]))));
			fRec51[0] = ((fConst268 * (((fConst270 * fRec52[1]) + (fConst273 * fRec52[0])) + (fConst273 * fRec52[2]))) - (fConst266 * ((fConst274 * fRec51[2]) + (fConst275 * fRec51[1]))));
			fRec50[0] = ((fConst266 * (((fConst267 * fRec51[1]) + (fConst276 * fRec51[0])) + (fConst276 * fRec51[2]))) - (fConst264 * ((fConst277 * fRec50[2]) + (fConst278 * fRec50[1]))));
			float fTemp7 = (fConst264 * (((fConst265 * fRec50[1]) + (fConst279 * fRec50[0])) + (fConst279 * fRec50[2])));
			fRec49[0] = (fTemp7 - (fConst261 * ((fConst280 * fRec49[2]) + (fConst282 * fRec49[1]))));
			fRec48[0] = ((fConst261 * (((fConst263 * fRec49[1]) + (fConst283 * fRec49[0])) + (fConst283 * fRec49[2]))) - (fConst258 * ((fConst284 * fRec48[2]) + (fConst285 * fRec48[1]))));
			fRec47[0] = ((fConst258 * (((fConst260 * fRec48[1]) + (fConst286 * fRec48[0])) + (fConst286 * fRec48[2]))) - (fConst254 * ((fConst287 * fRec47[2]) + (fConst288 * fRec47[1]))));
			fRec46[0] = ((fSlow1 * fRec46[1]) + (fSlow2 * fabsf((fConst254 * (((fConst257 * fRec47[1]) + (fConst289 * fRec47[0])) + (fConst289 * fRec47[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec46[0])))));
			fRec59[0] = (fTemp7 - (fConst306 * ((fConst309 * fRec59[2]) + (fConst310 * fRec59[1]))));
			fRec58[0] = ((fConst306 * (((fConst308 * fRec59[1]) + (fConst311 * fRec59[0])) + (fConst311 * fRec59[2]))) - (fConst304 * ((fConst312 * fRec58[2]) + (fConst313 * fRec58[1]))));
			fRec57[0] = ((fConst304 * (((fConst305 * fRec58[1]) + (fConst314 * fRec58[0])) + (fConst314 * fRec58[2]))) - (fConst302 * ((fConst315 * fRec57[2]) + (fConst316 * fRec57[1]))));
			float fTemp8 = (fConst302 * (((fConst303 * fRec57[1]) + (fConst317 * fRec57[0])) + (fConst317 * fRec57[2])));
			fRec56[0] = (fTemp8 - (fConst299 * ((fConst318 * fRec56[2]) + (fConst320 * fRec56[1]))));
			fRec55[0] = ((fConst299 * (((fConst301 * fRec56[1]) + (fConst321 * fRec56[0])) + (fConst321 * fRec56[2]))) - (fConst296 * ((fConst322 * fRec55[2]) + (fConst323 * fRec55[1]))));
			fRec54[0] = ((fConst296 * (((fConst298 * fRec55[1]) + (fConst324 * fRec55[0])) + (fConst324 * fRec55[2]))) - (fConst292 * ((fConst325 * fRec54[2]) + (fConst326 * fRec54[1]))));
			fRec53[0] = ((fSlow1 * fRec53[1]) + (fSlow2 * fabsf((fConst292 * (((fConst295 * fRec54[1]) + (fConst327 * fRec54[0])) + (fConst327 * fRec54[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec53[0])))));
			fRec66[0] = (fTemp8 - (fConst344 * ((fConst347 * fRec66[2]) + (fConst348 * fRec66[1]))));
			fRec65[0] = ((fConst344 * (((fConst346 * fRec66[1]) + (fConst349 * fRec66[0])) + (fConst349 * fRec66[2]))) - (fConst342 * ((fConst350 * fRec65[2]) + (fConst351 * fRec65[1]))));
			fRec64[0] = ((fConst342 * (((fConst343 * fRec65[1]) + (fConst352 * fRec65[0])) + (fConst352 * fRec65[2]))) - (fConst340 * ((fConst353 * fRec64[2]) + (fConst354 * fRec64[1]))));
			float fTemp9 = (fConst340 * (((fConst341 * fRec64[1]) + (fConst355 * fRec64[0])) + (fConst355 * fRec64[2])));
			fRec63[0] = (fTemp9 - (fConst337 * ((fConst356 * fRec63[2]) + (fConst358 * fRec63[1]))));
			fRec62[0] = ((fConst337 * (((fConst339 * fRec63[1]) + (fConst359 * fRec63[0])) + (fConst359 * fRec63[2]))) - (fConst334 * ((fConst360 * fRec62[2]) + (fConst361 * fRec62[1]))));
			fRec61[0] = ((fConst334 * (((fConst336 * fRec62[1]) + (fConst362 * fRec62[0])) + (fConst362 * fRec62[2]))) - (fConst330 * ((fConst363 * fRec61[2]) + (fConst364 * fRec61[1]))));
			fRec60[0] = ((fSlow1 * fRec60[1]) + (fSlow2 * fabsf((fConst330 * (((fConst333 * fRec61[1]) + (fConst365 * fRec61[0])) + (fConst365 * fRec61[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec60[0])))));
			fRec73[0] = (fTemp9 - (fConst382 * ((fConst385 * fRec73[2]) + (fConst386 * fRec73[1]))));
			fRec72[0] = ((fConst382 * (((fConst384 * fRec73[1]) + (fConst387 * fRec73[0])) + (fConst387 * fRec73[2]))) - (fConst380 * ((fConst388 * fRec72[2]) + (fConst389 * fRec72[1]))));
			fRec71[0] = ((fConst380 * (((fConst381 * fRec72[1]) + (fConst390 * fRec72[0])) + (fConst390 * fRec72[2]))) - (fConst378 * ((fConst391 * fRec71[2]) + (fConst392 * fRec71[1]))));
			float fTemp10 = (fConst378 * (((fConst379 * fRec71[1]) + (fConst393 * fRec71[0])) + (fConst393 * fRec71[2])));
			fRec70[0] = (fTemp10 - (fConst375 * ((fConst394 * fRec70[2]) + (fConst396 * fRec70[1]))));
			fRec69[0] = ((fConst375 * (((fConst377 * fRec70[1]) + (fConst397 * fRec70[0])) + (fConst397 * fRec70[2]))) - (fConst372 * ((fConst398 * fRec69[2]) + (fConst399 * fRec69[1]))));
			fRec68[0] = ((fConst372 * (((fConst374 * fRec69[1]) + (fConst400 * fRec69[0])) + (fConst400 * fRec69[2]))) - (fConst368 * ((fConst401 * fRec68[2]) + (fConst402 * fRec68[1]))));
			fRec67[0] = ((fSlow1 * fRec67[1]) + (fSlow2 * fabsf((fConst368 * (((fConst371 * fRec68[1]) + (fConst403 * fRec68[0])) + (fConst403 * fRec68[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec67[0])))));
			fRec80[0] = (fTemp10 - (fConst420 * ((fConst423 * fRec80[2]) + (fConst424 * fRec80[1]))));
			fRec79[0] = ((fConst420 * (((fConst422 * fRec80[1]) + (fConst425 * fRec80[0])) + (fConst425 * fRec80[2]))) - (fConst418 * ((fConst426 * fRec79[2]) + (fConst427 * fRec79[1]))));
			fRec78[0] = ((fConst418 * (((fConst419 * fRec79[1]) + (fConst428 * fRec79[0])) + (fConst428 * fRec79[2]))) - (fConst416 * ((fConst429 * fRec78[2]) + (fConst430 * fRec78[1]))));
			float fTemp11 = (fConst416 * (((fConst417 * fRec78[1]) + (fConst431 * fRec78[0])) + (fConst431 * fRec78[2])));
			fRec77[0] = (fTemp11 - (fConst413 * ((fConst432 * fRec77[2]) + (fConst434 * fRec77[1]))));
			fRec76[0] = ((fConst413 * (((fConst415 * fRec77[1]) + (fConst435 * fRec77[0])) + (fConst435 * fRec77[2]))) - (fConst410 * ((fConst436 * fRec76[2]) + (fConst437 * fRec76[1]))));
			fRec75[0] = ((fConst410 * (((fConst412 * fRec76[1]) + (fConst438 * fRec76[0])) + (fConst438 * fRec76[2]))) - (fConst406 * ((fConst439 * fRec75[2]) + (fConst440 * fRec75[1]))));
			fRec74[0] = ((fSlow1 * fRec74[1]) + (fSlow2 * fabsf((fConst406 * (((fConst409 * fRec75[1]) + (fConst441 * fRec75[0])) + (fConst441 * fRec75[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec74[0])))));
			fRec87[0] = (fTemp11 - (fConst458 * ((fConst461 * fRec87[2]) + (fConst462 * fRec87[1]))));
			fRec86[0] = ((fConst458 * (((fConst460 * fRec87[1]) + (fConst463 * fRec87[0])) + (fConst463 * fRec87[2]))) - (fConst456 * ((fConst464 * fRec86[2]) + (fConst465 * fRec86[1]))));
			fRec85[0] = ((fConst456 * (((fConst457 * fRec86[1]) + (fConst466 * fRec86[0])) + (fConst466 * fRec86[2]))) - (fConst454 * ((fConst467 * fRec85[2]) + (fConst468 * fRec85[1]))));
			float fTemp12 = (fConst454 * (((fConst455 * fRec85[1]) + (fConst469 * fRec85[0])) + (fConst469 * fRec85[2])));
			fRec84[0] = (fTemp12 - (fConst451 * ((fConst470 * fRec84[2]) + (fConst472 * fRec84[1]))));
			fRec83[0] = ((fConst451 * (((fConst453 * fRec84[1]) + (fConst473 * fRec84[0])) + (fConst473 * fRec84[2]))) - (fConst448 * ((fConst474 * fRec83[2]) + (fConst475 * fRec83[1]))));
			fRec82[0] = ((fConst448 * (((fConst450 * fRec83[1]) + (fConst476 * fRec83[0])) + (fConst476 * fRec83[2]))) - (fConst444 * ((fConst477 * fRec82[2]) + (fConst478 * fRec82[1]))));
			fRec81[0] = ((fSlow1 * fRec81[1]) + (fSlow2 * fabsf((fConst444 * (((fConst447 * fRec82[1]) + (fConst479 * fRec82[0])) + (fConst479 * fRec82[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec81[0])))));
			fRec94[0] = (fTemp12 - (fConst496 * ((fConst499 * fRec94[2]) + (fConst500 * fRec94[1]))));
			fRec93[0] = ((fConst496 * (((fConst498 * fRec94[1]) + (fConst501 * fRec94[0])) + (fConst501 * fRec94[2]))) - (fConst494 * ((fConst502 * fRec93[2]) + (fConst503 * fRec93[1]))));
			fRec92[0] = ((fConst494 * (((fConst495 * fRec93[1]) + (fConst504 * fRec93[0])) + (fConst504 * fRec93[2]))) - (fConst492 * ((fConst505 * fRec92[2]) + (fConst506 * fRec92[1]))));
			float fTemp13 = (fConst492 * (((fConst493 * fRec92[1]) + (fConst507 * fRec92[0])) + (fConst507 * fRec92[2])));
			fRec91[0] = (fTemp13 - (fConst489 * ((fConst508 * fRec91[2]) + (fConst510 * fRec91[1]))));
			fRec90[0] = ((fConst489 * (((fConst491 * fRec91[1]) + (fConst511 * fRec91[0])) + (fConst511 * fRec91[2]))) - (fConst486 * ((fConst512 * fRec90[2]) + (fConst513 * fRec90[1]))));
			fRec89[0] = ((fConst486 * (((fConst488 * fRec90[1]) + (fConst514 * fRec90[0])) + (fConst514 * fRec90[2]))) - (fConst482 * ((fConst515 * fRec89[2]) + (fConst516 * fRec89[1]))));
			fRec88[0] = ((fSlow1 * fRec88[1]) + (fSlow2 * fabsf((fConst482 * (((fConst485 * fRec89[1]) + (fConst517 * fRec89[0])) + (fConst517 * fRec89[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec88[0])))));
			fRec98[0] = (fTemp13 - (fConst522 * ((fConst525 * fRec98[2]) + (fConst526 * fRec98[1]))));
			fRec97[0] = ((fConst522 * (((fConst524 * fRec98[1]) + (fConst527 * fRec98[0])) + (fConst527 * fRec98[2]))) - (fConst520 * ((fConst528 * fRec97[2]) + (fConst529 * fRec97[1]))));
			fRec96[0] = ((fConst520 * (((fConst521 * fRec97[1]) + (fConst530 * fRec97[0])) + (fConst530 * fRec97[2]))) - (fConst518 * ((fConst531 * fRec96[2]) + (fConst532 * fRec96[1]))));
			fRec95[0] = ((fSlow1 * fRec95[1]) + (fSlow2 * fabsf((fConst518 * (((fConst519 * fRec96[1]) + (fConst533 * fRec96[0])) + (fConst533 * fRec96[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(max(1.00000001e-07f, fRec95[0])))));
			output0[i] = FAUSTFLOAT(fTemp0);
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
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
			fRec4[1] = fRec4[0];
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
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			
		}
		
	}

	
};

#endif
