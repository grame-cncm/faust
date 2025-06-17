/* ------------------------------------------------------------
name: "phaserFlangerLab"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

//include for cpp logging
#include <iostream>

//includes for the clap helpers glue
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>

//guarded MapUI subclass to prevent accidental param writes
struct GuardedUI : public MapUI {
    bool allowWrite = false;
    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        if (!allowWrite) {
            std::abort(); //catch unintended writes early
        }
        MapUI::setParamValue(path, val);
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }
};


struct GuardedScope {
    GuardedUI& ui;
    const char* tag;

    GuardedScope(GuardedUI& ui, const char* src = "unknown") : ui(ui), tag(src) {
        ui.allowWrite = true;
    }

    ~GuardedScope() {
        ui.allowWrite = false;
    }
};

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

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

static float mydsp_faustpower2_f(float value) {
	return value * value;
}
static float mydsp_faustpower3_f(float value) {
	return value * value * value;
}
static float mydsp_faustpower4_f(float value) {
	return value * value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	float fConst1;
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
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider3;
	float fConst14;
	FAUSTFLOAT fHslider4;
	int iVec0[4];
	float fRec4[2];
	float fRec5[2];
	FAUSTFLOAT fHbargraph0;
	float fConst15;
	FAUSTFLOAT fVslider0;
	float fConst16;
	float fRec6[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec8[2];
	float fRec7[2];
	float fConst17;
	float fVec1[2];
	float fConst18;
	float fVec2[2];
	float fVec3[2];
	float fConst19;
	float fVec4[2];
	float fVec5[2];
	float fVec6[2];
	FAUSTFLOAT fVslider3;
	float fRec9[2];
	float fVec7[2];
	float fVec8[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	FAUSTFLOAT fVslider4;
	float fRec10[2];
	float fVec13[2];
	float fVec14[2];
	float fVec15[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	FAUSTFLOAT fCheckbox4;
	int iRec11[2];
	float fRec12[4];
	FAUSTFLOAT fHslider5;
	int IOTA0;
	float fVec19[4096];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fRec13[2];
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fHslider10;
	float fConst20;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	float fRec19[2];
	float fRec20[2];
	float fRec18[3];
	float fRec17[3];
	float fRec16[3];
	float fRec15[3];
	float fRec14[2];
	FAUSTFLOAT fCheckbox7;
	float fVec20[4096];
	float fRec21[2];
	float fRec26[3];
	float fRec25[3];
	float fRec24[3];
	float fRec23[3];
	float fRec22[2];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec3[3];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec2[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec1[3];
	float fConst30;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
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
	float fRec33[3];
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec32[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec31[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec30[3];
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec29[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec28[3];
	float fConst68;
	float fRec27[2];
	FAUSTFLOAT fVbargraph1;
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
	float fRec40[3];
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec39[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec38[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec37[3];
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec36[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec35[3];
	float fConst106;
	float fRec34[2];
	FAUSTFLOAT fVbargraph2;
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
	float fConst127;
	float fRec47[3];
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec46[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec45[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec44[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec43[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec42[3];
	float fConst144;
	float fRec41[2];
	FAUSTFLOAT fVbargraph3;
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
	float fConst165;
	float fRec54[3];
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec53[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec52[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec51[3];
	float fConst176;
	float fConst177;
	float fConst178;
	float fRec50[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec49[3];
	float fConst182;
	float fRec48[2];
	FAUSTFLOAT fVbargraph4;
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
	float fConst203;
	float fRec61[3];
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec60[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec59[3];
	float fConst210;
	float fConst211;
	float fConst212;
	float fConst213;
	float fRec58[3];
	float fConst214;
	float fConst215;
	float fConst216;
	float fRec57[3];
	float fConst217;
	float fConst218;
	float fConst219;
	float fRec56[3];
	float fConst220;
	float fRec55[2];
	FAUSTFLOAT fVbargraph5;
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
	float fConst241;
	float fRec68[3];
	float fConst242;
	float fConst243;
	float fConst244;
	float fRec67[3];
	float fConst245;
	float fConst246;
	float fConst247;
	float fRec66[3];
	float fConst248;
	float fConst249;
	float fConst250;
	float fConst251;
	float fRec65[3];
	float fConst252;
	float fConst253;
	float fConst254;
	float fRec64[3];
	float fConst255;
	float fConst256;
	float fConst257;
	float fRec63[3];
	float fConst258;
	float fRec62[2];
	FAUSTFLOAT fVbargraph6;
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
	float fConst279;
	float fRec75[3];
	float fConst280;
	float fConst281;
	float fConst282;
	float fRec74[3];
	float fConst283;
	float fConst284;
	float fConst285;
	float fRec73[3];
	float fConst286;
	float fConst287;
	float fConst288;
	float fConst289;
	float fRec72[3];
	float fConst290;
	float fConst291;
	float fConst292;
	float fRec71[3];
	float fConst293;
	float fConst294;
	float fConst295;
	float fRec70[3];
	float fConst296;
	float fRec69[2];
	FAUSTFLOAT fVbargraph7;
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
	float fConst317;
	float fRec82[3];
	float fConst318;
	float fConst319;
	float fConst320;
	float fRec81[3];
	float fConst321;
	float fConst322;
	float fConst323;
	float fRec80[3];
	float fConst324;
	float fConst325;
	float fConst326;
	float fConst327;
	float fRec79[3];
	float fConst328;
	float fConst329;
	float fConst330;
	float fRec78[3];
	float fConst331;
	float fConst332;
	float fConst333;
	float fRec77[3];
	float fConst334;
	float fRec76[2];
	FAUSTFLOAT fVbargraph8;
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
	float fConst355;
	float fRec89[3];
	float fConst356;
	float fConst357;
	float fConst358;
	float fRec88[3];
	float fConst359;
	float fConst360;
	float fConst361;
	float fRec87[3];
	float fConst362;
	float fConst363;
	float fConst364;
	float fConst365;
	float fRec86[3];
	float fConst366;
	float fConst367;
	float fConst368;
	float fRec85[3];
	float fConst369;
	float fConst370;
	float fConst371;
	float fRec84[3];
	float fConst372;
	float fRec83[2];
	FAUSTFLOAT fVbargraph9;
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
	float fConst393;
	float fRec96[3];
	float fConst394;
	float fConst395;
	float fConst396;
	float fRec95[3];
	float fConst397;
	float fConst398;
	float fConst399;
	float fRec94[3];
	float fConst400;
	float fConst401;
	float fConst402;
	float fConst403;
	float fRec93[3];
	float fConst404;
	float fConst405;
	float fConst406;
	float fRec92[3];
	float fConst407;
	float fConst408;
	float fConst409;
	float fRec91[3];
	float fConst410;
	float fRec90[2];
	FAUSTFLOAT fVbargraph10;
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
	float fConst431;
	float fRec103[3];
	float fConst432;
	float fConst433;
	float fConst434;
	float fRec102[3];
	float fConst435;
	float fConst436;
	float fConst437;
	float fRec101[3];
	float fConst438;
	float fConst439;
	float fConst440;
	float fConst441;
	float fRec100[3];
	float fConst442;
	float fConst443;
	float fConst444;
	float fRec99[3];
	float fConst445;
	float fConst446;
	float fConst447;
	float fRec98[3];
	float fConst448;
	float fRec97[2];
	FAUSTFLOAT fVbargraph11;
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
	float fConst469;
	float fRec110[3];
	float fConst470;
	float fConst471;
	float fConst472;
	float fRec109[3];
	float fConst473;
	float fConst474;
	float fConst475;
	float fRec108[3];
	float fConst476;
	float fConst477;
	float fConst478;
	float fConst479;
	float fRec107[3];
	float fConst480;
	float fConst481;
	float fConst482;
	float fRec106[3];
	float fConst483;
	float fConst484;
	float fConst485;
	float fRec105[3];
	float fConst486;
	float fRec104[2];
	FAUSTFLOAT fVbargraph12;
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
	float fConst507;
	float fRec117[3];
	float fConst508;
	float fConst509;
	float fConst510;
	float fRec116[3];
	float fConst511;
	float fConst512;
	float fConst513;
	float fRec115[3];
	float fConst514;
	float fConst515;
	float fConst516;
	float fConst517;
	float fRec114[3];
	float fConst518;
	float fConst519;
	float fConst520;
	float fRec113[3];
	float fConst521;
	float fConst522;
	float fConst523;
	float fRec112[3];
	float fConst524;
	float fRec111[2];
	FAUSTFLOAT fVbargraph13;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fRec121[3];
	float fConst534;
	float fConst535;
	float fConst536;
	float fRec120[3];
	float fConst537;
	float fConst538;
	float fConst539;
	float fRec119[3];
	float fConst540;
	float fRec118[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.2.0");
		m->declare("basics.lib/bypass2:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("demos.lib/flanger_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/flanger_demo:licence", "MIT");
		m->declare("demos.lib/mth_octave_spectral_level_demo:author", "Julius O. Smith III and Yann Orlarey");
		m->declare("demos.lib/mth_octave_spectral_level_demo:licence", "MIT");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/phaser2_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/phaser2_demo:licence", "MIT");
		m->declare("demos.lib/sawtooth_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/sawtooth_demo:licence", "MIT");
		m->declare("demos.lib/version", "1.2.0");
		m->declare("filename", "phaserFlangerLab.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass6e:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass6e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highpass6e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass6e:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass6e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass6e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "phaserFlangerLab");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/sawN:author", "Julius O. Smith III");
		m->declare("oscillators.lib/sawN:license", "STK-4.3");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "1.1.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 1.0f / fConst0;
		fConst2 = std::tan(50265.484f / fConst0);
		fConst3 = 1.0f / fConst2;
		fConst4 = 1.0f / ((fConst3 + 0.15748216f) / fConst2 + 0.9351402f);
		fConst5 = mydsp_faustpower2_f(fConst2);
		fConst6 = 50.06381f / fConst5;
		fConst7 = fConst6 + 0.9351402f;
		fConst8 = 1.0f / ((fConst3 + 0.74313045f) / fConst2 + 1.4500711f);
		fConst9 = 11.0520525f / fConst5;
		fConst10 = fConst9 + 1.4500711f;
		fConst11 = 1.0f / ((fConst3 + 3.1897273f) / fConst2 + 4.0767817f);
		fConst12 = 0.0017661728f / fConst5;
		fConst13 = fConst12 + 0.0004076782f;
		fConst14 = 6.2831855f / fConst0;
		fConst15 = 44.1f / fConst0;
		fConst16 = 1.0f - fConst15;
		fConst17 = 0.25f * fConst0;
		fConst18 = 0.041666668f * mydsp_faustpower2_f(fConst0);
		fConst19 = 0.0052083335f * mydsp_faustpower3_f(fConst0);
		fConst20 = 3.1415927f / fConst0;
		fConst21 = (fConst3 + -3.1897273f) / fConst2 + 4.0767817f;
		fConst22 = 1.0f / fConst5;
		fConst23 = 2.0f * (4.0767817f - fConst22);
		fConst24 = 2.0f * (0.0004076782f - fConst12);
		fConst25 = (fConst3 + -0.74313045f) / fConst2 + 1.4500711f;
		fConst26 = 2.0f * (1.4500711f - fConst22);
		fConst27 = 2.0f * (1.4500711f - fConst9);
		fConst28 = (fConst3 + -0.15748216f) / fConst2 + 0.9351402f;
		fConst29 = 2.0f * (0.9351402f - fConst22);
		fConst30 = 2.0f * (0.9351402f - fConst6);
		fConst31 = std::tan(31665.27f / fConst0);
		fConst32 = 1.0f / fConst31;
		fConst33 = 1.0f / ((fConst32 + 0.15748216f) / fConst31 + 0.9351402f);
		fConst34 = mydsp_faustpower2_f(fConst31);
		fConst35 = 50.06381f / fConst34;
		fConst36 = fConst35 + 0.9351402f;
		fConst37 = 1.0f / ((fConst32 + 0.74313045f) / fConst31 + 1.4500711f);
		fConst38 = 11.0520525f / fConst34;
		fConst39 = fConst38 + 1.4500711f;
		fConst40 = 1.0f / ((fConst32 + 3.1897273f) / fConst31 + 4.0767817f);
		fConst41 = 0.0017661728f / fConst34;
		fConst42 = fConst41 + 0.0004076782f;
		fConst43 = 1.0f / ((fConst3 + 0.16840488f) / fConst2 + 1.0693583f);
		fConst44 = fConst22 + 53.53615f;
		fConst45 = 1.0f / ((fConst3 + 0.51247865f) / fConst2 + 0.6896214f);
		fConst46 = fConst22 + 7.6217313f;
		fConst47 = 1.0f / ((fConst3 + 0.78241307f) / fConst2 + 0.2452915f);
		fConst48 = 0.0001f / fConst5;
		fConst49 = fConst48 + 0.0004332272f;
		fConst50 = (fConst3 + -0.78241307f) / fConst2 + 0.2452915f;
		fConst51 = 2.0f * (0.2452915f - fConst22);
		fConst52 = 2.0f * (0.0004332272f - fConst48);
		fConst53 = (fConst3 + -0.51247865f) / fConst2 + 0.6896214f;
		fConst54 = 2.0f * (0.6896214f - fConst22);
		fConst55 = 2.0f * (7.6217313f - fConst22);
		fConst56 = (fConst3 + -0.16840488f) / fConst2 + 1.0693583f;
		fConst57 = 2.0f * (1.0693583f - fConst22);
		fConst58 = 2.0f * (53.53615f - fConst22);
		fConst59 = (fConst32 + -3.1897273f) / fConst31 + 4.0767817f;
		fConst60 = 1.0f / fConst34;
		fConst61 = 2.0f * (4.0767817f - fConst60);
		fConst62 = 2.0f * (0.0004076782f - fConst41);
		fConst63 = (fConst32 + -0.74313045f) / fConst31 + 1.4500711f;
		fConst64 = 2.0f * (1.4500711f - fConst60);
		fConst65 = 2.0f * (1.4500711f - fConst38);
		fConst66 = (fConst32 + -0.15748216f) / fConst31 + 0.9351402f;
		fConst67 = 2.0f * (0.9351402f - fConst60);
		fConst68 = 2.0f * (0.9351402f - fConst35);
		fConst69 = std::tan(19947.87f / fConst0);
		fConst70 = 1.0f / fConst69;
		fConst71 = 1.0f / ((fConst70 + 0.15748216f) / fConst69 + 0.9351402f);
		fConst72 = mydsp_faustpower2_f(fConst69);
		fConst73 = 50.06381f / fConst72;
		fConst74 = fConst73 + 0.9351402f;
		fConst75 = 1.0f / ((fConst70 + 0.74313045f) / fConst69 + 1.4500711f);
		fConst76 = 11.0520525f / fConst72;
		fConst77 = fConst76 + 1.4500711f;
		fConst78 = 1.0f / ((fConst70 + 3.1897273f) / fConst69 + 4.0767817f);
		fConst79 = 0.0017661728f / fConst72;
		fConst80 = fConst79 + 0.0004076782f;
		fConst81 = 1.0f / ((fConst32 + 0.16840488f) / fConst31 + 1.0693583f);
		fConst82 = fConst60 + 53.53615f;
		fConst83 = 1.0f / ((fConst32 + 0.51247865f) / fConst31 + 0.6896214f);
		fConst84 = fConst60 + 7.6217313f;
		fConst85 = 1.0f / ((fConst32 + 0.78241307f) / fConst31 + 0.2452915f);
		fConst86 = 0.0001f / fConst34;
		fConst87 = fConst86 + 0.0004332272f;
		fConst88 = (fConst32 + -0.78241307f) / fConst31 + 0.2452915f;
		fConst89 = 2.0f * (0.2452915f - fConst60);
		fConst90 = 2.0f * (0.0004332272f - fConst86);
		fConst91 = (fConst32 + -0.51247865f) / fConst31 + 0.6896214f;
		fConst92 = 2.0f * (0.6896214f - fConst60);
		fConst93 = 2.0f * (7.6217313f - fConst60);
		fConst94 = (fConst32 + -0.16840488f) / fConst31 + 1.0693583f;
		fConst95 = 2.0f * (1.0693583f - fConst60);
		fConst96 = 2.0f * (53.53615f - fConst60);
		fConst97 = (fConst70 + -3.1897273f) / fConst69 + 4.0767817f;
		fConst98 = 1.0f / fConst72;
		fConst99 = 2.0f * (4.0767817f - fConst98);
		fConst100 = 2.0f * (0.0004076782f - fConst79);
		fConst101 = (fConst70 + -0.74313045f) / fConst69 + 1.4500711f;
		fConst102 = 2.0f * (1.4500711f - fConst98);
		fConst103 = 2.0f * (1.4500711f - fConst76);
		fConst104 = (fConst70 + -0.15748216f) / fConst69 + 0.9351402f;
		fConst105 = 2.0f * (0.9351402f - fConst98);
		fConst106 = 2.0f * (0.9351402f - fConst73);
		fConst107 = std::tan(12566.371f / fConst0);
		fConst108 = 1.0f / fConst107;
		fConst109 = 1.0f / ((fConst108 + 0.15748216f) / fConst107 + 0.9351402f);
		fConst110 = mydsp_faustpower2_f(fConst107);
		fConst111 = 50.06381f / fConst110;
		fConst112 = fConst111 + 0.9351402f;
		fConst113 = 1.0f / ((fConst108 + 0.74313045f) / fConst107 + 1.4500711f);
		fConst114 = 11.0520525f / fConst110;
		fConst115 = fConst114 + 1.4500711f;
		fConst116 = 1.0f / ((fConst108 + 3.1897273f) / fConst107 + 4.0767817f);
		fConst117 = 0.0017661728f / fConst110;
		fConst118 = fConst117 + 0.0004076782f;
		fConst119 = 1.0f / ((fConst70 + 0.16840488f) / fConst69 + 1.0693583f);
		fConst120 = fConst98 + 53.53615f;
		fConst121 = 1.0f / ((fConst70 + 0.51247865f) / fConst69 + 0.6896214f);
		fConst122 = fConst98 + 7.6217313f;
		fConst123 = 1.0f / ((fConst70 + 0.78241307f) / fConst69 + 0.2452915f);
		fConst124 = 0.0001f / fConst72;
		fConst125 = fConst124 + 0.0004332272f;
		fConst126 = (fConst70 + -0.78241307f) / fConst69 + 0.2452915f;
		fConst127 = 2.0f * (0.2452915f - fConst98);
		fConst128 = 2.0f * (0.0004332272f - fConst124);
		fConst129 = (fConst70 + -0.51247865f) / fConst69 + 0.6896214f;
		fConst130 = 2.0f * (0.6896214f - fConst98);
		fConst131 = 2.0f * (7.6217313f - fConst98);
		fConst132 = (fConst70 + -0.16840488f) / fConst69 + 1.0693583f;
		fConst133 = 2.0f * (1.0693583f - fConst98);
		fConst134 = 2.0f * (53.53615f - fConst98);
		fConst135 = (fConst108 + -3.1897273f) / fConst107 + 4.0767817f;
		fConst136 = 1.0f / fConst110;
		fConst137 = 2.0f * (4.0767817f - fConst136);
		fConst138 = 2.0f * (0.0004076782f - fConst117);
		fConst139 = (fConst108 + -0.74313045f) / fConst107 + 1.4500711f;
		fConst140 = 2.0f * (1.4500711f - fConst136);
		fConst141 = 2.0f * (1.4500711f - fConst114);
		fConst142 = (fConst108 + -0.15748216f) / fConst107 + 0.9351402f;
		fConst143 = 2.0f * (0.9351402f - fConst136);
		fConst144 = 2.0f * (0.9351402f - fConst111);
		fConst145 = std::tan(7916.3174f / fConst0);
		fConst146 = 1.0f / fConst145;
		fConst147 = 1.0f / ((fConst146 + 0.15748216f) / fConst145 + 0.9351402f);
		fConst148 = mydsp_faustpower2_f(fConst145);
		fConst149 = 50.06381f / fConst148;
		fConst150 = fConst149 + 0.9351402f;
		fConst151 = 1.0f / ((fConst146 + 0.74313045f) / fConst145 + 1.4500711f);
		fConst152 = 11.0520525f / fConst148;
		fConst153 = fConst152 + 1.4500711f;
		fConst154 = 1.0f / ((fConst146 + 3.1897273f) / fConst145 + 4.0767817f);
		fConst155 = 0.0017661728f / fConst148;
		fConst156 = fConst155 + 0.0004076782f;
		fConst157 = 1.0f / ((fConst108 + 0.16840488f) / fConst107 + 1.0693583f);
		fConst158 = fConst136 + 53.53615f;
		fConst159 = 1.0f / ((fConst108 + 0.51247865f) / fConst107 + 0.6896214f);
		fConst160 = fConst136 + 7.6217313f;
		fConst161 = 1.0f / ((fConst108 + 0.78241307f) / fConst107 + 0.2452915f);
		fConst162 = 0.0001f / fConst110;
		fConst163 = fConst162 + 0.0004332272f;
		fConst164 = (fConst108 + -0.78241307f) / fConst107 + 0.2452915f;
		fConst165 = 2.0f * (0.2452915f - fConst136);
		fConst166 = 2.0f * (0.0004332272f - fConst162);
		fConst167 = (fConst108 + -0.51247865f) / fConst107 + 0.6896214f;
		fConst168 = 2.0f * (0.6896214f - fConst136);
		fConst169 = 2.0f * (7.6217313f - fConst136);
		fConst170 = (fConst108 + -0.16840488f) / fConst107 + 1.0693583f;
		fConst171 = 2.0f * (1.0693583f - fConst136);
		fConst172 = 2.0f * (53.53615f - fConst136);
		fConst173 = (fConst146 + -3.1897273f) / fConst145 + 4.0767817f;
		fConst174 = 1.0f / fConst148;
		fConst175 = 2.0f * (4.0767817f - fConst174);
		fConst176 = 2.0f * (0.0004076782f - fConst155);
		fConst177 = (fConst146 + -0.74313045f) / fConst145 + 1.4500711f;
		fConst178 = 2.0f * (1.4500711f - fConst174);
		fConst179 = 2.0f * (1.4500711f - fConst152);
		fConst180 = (fConst146 + -0.15748216f) / fConst145 + 0.9351402f;
		fConst181 = 2.0f * (0.9351402f - fConst174);
		fConst182 = 2.0f * (0.9351402f - fConst149);
		fConst183 = std::tan(4986.9673f / fConst0);
		fConst184 = 1.0f / fConst183;
		fConst185 = 1.0f / ((fConst184 + 0.15748216f) / fConst183 + 0.9351402f);
		fConst186 = mydsp_faustpower2_f(fConst183);
		fConst187 = 50.06381f / fConst186;
		fConst188 = fConst187 + 0.9351402f;
		fConst189 = 1.0f / ((fConst184 + 0.74313045f) / fConst183 + 1.4500711f);
		fConst190 = 11.0520525f / fConst186;
		fConst191 = fConst190 + 1.4500711f;
		fConst192 = 1.0f / ((fConst184 + 3.1897273f) / fConst183 + 4.0767817f);
		fConst193 = 0.0017661728f / fConst186;
		fConst194 = fConst193 + 0.0004076782f;
		fConst195 = 1.0f / ((fConst146 + 0.16840488f) / fConst145 + 1.0693583f);
		fConst196 = fConst174 + 53.53615f;
		fConst197 = 1.0f / ((fConst146 + 0.51247865f) / fConst145 + 0.6896214f);
		fConst198 = fConst174 + 7.6217313f;
		fConst199 = 1.0f / ((fConst146 + 0.78241307f) / fConst145 + 0.2452915f);
		fConst200 = 0.0001f / fConst148;
		fConst201 = fConst200 + 0.0004332272f;
		fConst202 = (fConst146 + -0.78241307f) / fConst145 + 0.2452915f;
		fConst203 = 2.0f * (0.2452915f - fConst174);
		fConst204 = 2.0f * (0.0004332272f - fConst200);
		fConst205 = (fConst146 + -0.51247865f) / fConst145 + 0.6896214f;
		fConst206 = 2.0f * (0.6896214f - fConst174);
		fConst207 = 2.0f * (7.6217313f - fConst174);
		fConst208 = (fConst146 + -0.16840488f) / fConst145 + 1.0693583f;
		fConst209 = 2.0f * (1.0693583f - fConst174);
		fConst210 = 2.0f * (53.53615f - fConst174);
		fConst211 = (fConst184 + -3.1897273f) / fConst183 + 4.0767817f;
		fConst212 = 1.0f / fConst186;
		fConst213 = 2.0f * (4.0767817f - fConst212);
		fConst214 = 2.0f * (0.0004076782f - fConst193);
		fConst215 = (fConst184 + -0.74313045f) / fConst183 + 1.4500711f;
		fConst216 = 2.0f * (1.4500711f - fConst212);
		fConst217 = 2.0f * (1.4500711f - fConst190);
		fConst218 = (fConst184 + -0.15748216f) / fConst183 + 0.9351402f;
		fConst219 = 2.0f * (0.9351402f - fConst212);
		fConst220 = 2.0f * (0.9351402f - fConst187);
		fConst221 = std::tan(3141.5928f / fConst0);
		fConst222 = 1.0f / fConst221;
		fConst223 = 1.0f / ((fConst222 + 0.15748216f) / fConst221 + 0.9351402f);
		fConst224 = mydsp_faustpower2_f(fConst221);
		fConst225 = 50.06381f / fConst224;
		fConst226 = fConst225 + 0.9351402f;
		fConst227 = 1.0f / ((fConst222 + 0.74313045f) / fConst221 + 1.4500711f);
		fConst228 = 11.0520525f / fConst224;
		fConst229 = fConst228 + 1.4500711f;
		fConst230 = 1.0f / ((fConst222 + 3.1897273f) / fConst221 + 4.0767817f);
		fConst231 = 0.0017661728f / fConst224;
		fConst232 = fConst231 + 0.0004076782f;
		fConst233 = 1.0f / ((fConst184 + 0.16840488f) / fConst183 + 1.0693583f);
		fConst234 = fConst212 + 53.53615f;
		fConst235 = 1.0f / ((fConst184 + 0.51247865f) / fConst183 + 0.6896214f);
		fConst236 = fConst212 + 7.6217313f;
		fConst237 = 1.0f / ((fConst184 + 0.78241307f) / fConst183 + 0.2452915f);
		fConst238 = 0.0001f / fConst186;
		fConst239 = fConst238 + 0.0004332272f;
		fConst240 = (fConst184 + -0.78241307f) / fConst183 + 0.2452915f;
		fConst241 = 2.0f * (0.2452915f - fConst212);
		fConst242 = 2.0f * (0.0004332272f - fConst238);
		fConst243 = (fConst184 + -0.51247865f) / fConst183 + 0.6896214f;
		fConst244 = 2.0f * (0.6896214f - fConst212);
		fConst245 = 2.0f * (7.6217313f - fConst212);
		fConst246 = (fConst184 + -0.16840488f) / fConst183 + 1.0693583f;
		fConst247 = 2.0f * (1.0693583f - fConst212);
		fConst248 = 2.0f * (53.53615f - fConst212);
		fConst249 = (fConst222 + -3.1897273f) / fConst221 + 4.0767817f;
		fConst250 = 1.0f / fConst224;
		fConst251 = 2.0f * (4.0767817f - fConst250);
		fConst252 = 2.0f * (0.0004076782f - fConst231);
		fConst253 = (fConst222 + -0.74313045f) / fConst221 + 1.4500711f;
		fConst254 = 2.0f * (1.4500711f - fConst250);
		fConst255 = 2.0f * (1.4500711f - fConst228);
		fConst256 = (fConst222 + -0.15748216f) / fConst221 + 0.9351402f;
		fConst257 = 2.0f * (0.9351402f - fConst250);
		fConst258 = 2.0f * (0.9351402f - fConst225);
		fConst259 = std::tan(1979.0793f / fConst0);
		fConst260 = 1.0f / fConst259;
		fConst261 = 1.0f / ((fConst260 + 0.15748216f) / fConst259 + 0.9351402f);
		fConst262 = mydsp_faustpower2_f(fConst259);
		fConst263 = 50.06381f / fConst262;
		fConst264 = fConst263 + 0.9351402f;
		fConst265 = 1.0f / ((fConst260 + 0.74313045f) / fConst259 + 1.4500711f);
		fConst266 = 11.0520525f / fConst262;
		fConst267 = fConst266 + 1.4500711f;
		fConst268 = 1.0f / ((fConst260 + 3.1897273f) / fConst259 + 4.0767817f);
		fConst269 = 0.0017661728f / fConst262;
		fConst270 = fConst269 + 0.0004076782f;
		fConst271 = 1.0f / ((fConst222 + 0.16840488f) / fConst221 + 1.0693583f);
		fConst272 = fConst250 + 53.53615f;
		fConst273 = 1.0f / ((fConst222 + 0.51247865f) / fConst221 + 0.6896214f);
		fConst274 = fConst250 + 7.6217313f;
		fConst275 = 1.0f / ((fConst222 + 0.78241307f) / fConst221 + 0.2452915f);
		fConst276 = 0.0001f / fConst224;
		fConst277 = fConst276 + 0.0004332272f;
		fConst278 = (fConst222 + -0.78241307f) / fConst221 + 0.2452915f;
		fConst279 = 2.0f * (0.2452915f - fConst250);
		fConst280 = 2.0f * (0.0004332272f - fConst276);
		fConst281 = (fConst222 + -0.51247865f) / fConst221 + 0.6896214f;
		fConst282 = 2.0f * (0.6896214f - fConst250);
		fConst283 = 2.0f * (7.6217313f - fConst250);
		fConst284 = (fConst222 + -0.16840488f) / fConst221 + 1.0693583f;
		fConst285 = 2.0f * (1.0693583f - fConst250);
		fConst286 = 2.0f * (53.53615f - fConst250);
		fConst287 = (fConst260 + -3.1897273f) / fConst259 + 4.0767817f;
		fConst288 = 1.0f / fConst262;
		fConst289 = 2.0f * (4.0767817f - fConst288);
		fConst290 = 2.0f * (0.0004076782f - fConst269);
		fConst291 = (fConst260 + -0.74313045f) / fConst259 + 1.4500711f;
		fConst292 = 2.0f * (1.4500711f - fConst288);
		fConst293 = 2.0f * (1.4500711f - fConst266);
		fConst294 = (fConst260 + -0.15748216f) / fConst259 + 0.9351402f;
		fConst295 = 2.0f * (0.9351402f - fConst288);
		fConst296 = 2.0f * (0.9351402f - fConst263);
		fConst297 = std::tan(1246.7418f / fConst0);
		fConst298 = 1.0f / fConst297;
		fConst299 = 1.0f / ((fConst298 + 0.15748216f) / fConst297 + 0.9351402f);
		fConst300 = mydsp_faustpower2_f(fConst297);
		fConst301 = 50.06381f / fConst300;
		fConst302 = fConst301 + 0.9351402f;
		fConst303 = 1.0f / ((fConst298 + 0.74313045f) / fConst297 + 1.4500711f);
		fConst304 = 11.0520525f / fConst300;
		fConst305 = fConst304 + 1.4500711f;
		fConst306 = 1.0f / ((fConst298 + 3.1897273f) / fConst297 + 4.0767817f);
		fConst307 = 0.0017661728f / fConst300;
		fConst308 = fConst307 + 0.0004076782f;
		fConst309 = 1.0f / ((fConst260 + 0.16840488f) / fConst259 + 1.0693583f);
		fConst310 = fConst288 + 53.53615f;
		fConst311 = 1.0f / ((fConst260 + 0.51247865f) / fConst259 + 0.6896214f);
		fConst312 = fConst288 + 7.6217313f;
		fConst313 = 1.0f / ((fConst260 + 0.78241307f) / fConst259 + 0.2452915f);
		fConst314 = 0.0001f / fConst262;
		fConst315 = fConst314 + 0.0004332272f;
		fConst316 = (fConst260 + -0.78241307f) / fConst259 + 0.2452915f;
		fConst317 = 2.0f * (0.2452915f - fConst288);
		fConst318 = 2.0f * (0.0004332272f - fConst314);
		fConst319 = (fConst260 + -0.51247865f) / fConst259 + 0.6896214f;
		fConst320 = 2.0f * (0.6896214f - fConst288);
		fConst321 = 2.0f * (7.6217313f - fConst288);
		fConst322 = (fConst260 + -0.16840488f) / fConst259 + 1.0693583f;
		fConst323 = 2.0f * (1.0693583f - fConst288);
		fConst324 = 2.0f * (53.53615f - fConst288);
		fConst325 = (fConst298 + -3.1897273f) / fConst297 + 4.0767817f;
		fConst326 = 1.0f / fConst300;
		fConst327 = 2.0f * (4.0767817f - fConst326);
		fConst328 = 2.0f * (0.0004076782f - fConst307);
		fConst329 = (fConst298 + -0.74313045f) / fConst297 + 1.4500711f;
		fConst330 = 2.0f * (1.4500711f - fConst326);
		fConst331 = 2.0f * (1.4500711f - fConst304);
		fConst332 = (fConst298 + -0.15748216f) / fConst297 + 0.9351402f;
		fConst333 = 2.0f * (0.9351402f - fConst326);
		fConst334 = 2.0f * (0.9351402f - fConst301);
		fConst335 = std::tan(785.3982f / fConst0);
		fConst336 = 1.0f / fConst335;
		fConst337 = 1.0f / ((fConst336 + 0.15748216f) / fConst335 + 0.9351402f);
		fConst338 = mydsp_faustpower2_f(fConst335);
		fConst339 = 50.06381f / fConst338;
		fConst340 = fConst339 + 0.9351402f;
		fConst341 = 1.0f / ((fConst336 + 0.74313045f) / fConst335 + 1.4500711f);
		fConst342 = 11.0520525f / fConst338;
		fConst343 = fConst342 + 1.4500711f;
		fConst344 = 1.0f / ((fConst336 + 3.1897273f) / fConst335 + 4.0767817f);
		fConst345 = 0.0017661728f / fConst338;
		fConst346 = fConst345 + 0.0004076782f;
		fConst347 = 1.0f / ((fConst298 + 0.16840488f) / fConst297 + 1.0693583f);
		fConst348 = fConst326 + 53.53615f;
		fConst349 = 1.0f / ((fConst298 + 0.51247865f) / fConst297 + 0.6896214f);
		fConst350 = fConst326 + 7.6217313f;
		fConst351 = 1.0f / ((fConst298 + 0.78241307f) / fConst297 + 0.2452915f);
		fConst352 = 0.0001f / fConst300;
		fConst353 = fConst352 + 0.0004332272f;
		fConst354 = (fConst298 + -0.78241307f) / fConst297 + 0.2452915f;
		fConst355 = 2.0f * (0.2452915f - fConst326);
		fConst356 = 2.0f * (0.0004332272f - fConst352);
		fConst357 = (fConst298 + -0.51247865f) / fConst297 + 0.6896214f;
		fConst358 = 2.0f * (0.6896214f - fConst326);
		fConst359 = 2.0f * (7.6217313f - fConst326);
		fConst360 = (fConst298 + -0.16840488f) / fConst297 + 1.0693583f;
		fConst361 = 2.0f * (1.0693583f - fConst326);
		fConst362 = 2.0f * (53.53615f - fConst326);
		fConst363 = (fConst336 + -3.1897273f) / fConst335 + 4.0767817f;
		fConst364 = 1.0f / fConst338;
		fConst365 = 2.0f * (4.0767817f - fConst364);
		fConst366 = 2.0f * (0.0004076782f - fConst345);
		fConst367 = (fConst336 + -0.74313045f) / fConst335 + 1.4500711f;
		fConst368 = 2.0f * (1.4500711f - fConst364);
		fConst369 = 2.0f * (1.4500711f - fConst342);
		fConst370 = (fConst336 + -0.15748216f) / fConst335 + 0.9351402f;
		fConst371 = 2.0f * (0.9351402f - fConst364);
		fConst372 = 2.0f * (0.9351402f - fConst339);
		fConst373 = std::tan(494.76984f / fConst0);
		fConst374 = 1.0f / fConst373;
		fConst375 = 1.0f / ((fConst374 + 0.15748216f) / fConst373 + 0.9351402f);
		fConst376 = mydsp_faustpower2_f(fConst373);
		fConst377 = 50.06381f / fConst376;
		fConst378 = fConst377 + 0.9351402f;
		fConst379 = 1.0f / ((fConst374 + 0.74313045f) / fConst373 + 1.4500711f);
		fConst380 = 11.0520525f / fConst376;
		fConst381 = fConst380 + 1.4500711f;
		fConst382 = 1.0f / ((fConst374 + 3.1897273f) / fConst373 + 4.0767817f);
		fConst383 = 0.0017661728f / fConst376;
		fConst384 = fConst383 + 0.0004076782f;
		fConst385 = 1.0f / ((fConst336 + 0.16840488f) / fConst335 + 1.0693583f);
		fConst386 = fConst364 + 53.53615f;
		fConst387 = 1.0f / ((fConst336 + 0.51247865f) / fConst335 + 0.6896214f);
		fConst388 = fConst364 + 7.6217313f;
		fConst389 = 1.0f / ((fConst336 + 0.78241307f) / fConst335 + 0.2452915f);
		fConst390 = 0.0001f / fConst338;
		fConst391 = fConst390 + 0.0004332272f;
		fConst392 = (fConst336 + -0.78241307f) / fConst335 + 0.2452915f;
		fConst393 = 2.0f * (0.2452915f - fConst364);
		fConst394 = 2.0f * (0.0004332272f - fConst390);
		fConst395 = (fConst336 + -0.51247865f) / fConst335 + 0.6896214f;
		fConst396 = 2.0f * (0.6896214f - fConst364);
		fConst397 = 2.0f * (7.6217313f - fConst364);
		fConst398 = (fConst336 + -0.16840488f) / fConst335 + 1.0693583f;
		fConst399 = 2.0f * (1.0693583f - fConst364);
		fConst400 = 2.0f * (53.53615f - fConst364);
		fConst401 = (fConst374 + -3.1897273f) / fConst373 + 4.0767817f;
		fConst402 = 1.0f / fConst376;
		fConst403 = 2.0f * (4.0767817f - fConst402);
		fConst404 = 2.0f * (0.0004076782f - fConst383);
		fConst405 = (fConst374 + -0.74313045f) / fConst373 + 1.4500711f;
		fConst406 = 2.0f * (1.4500711f - fConst402);
		fConst407 = 2.0f * (1.4500711f - fConst380);
		fConst408 = (fConst374 + -0.15748216f) / fConst373 + 0.9351402f;
		fConst409 = 2.0f * (0.9351402f - fConst402);
		fConst410 = 2.0f * (0.9351402f - fConst377);
		fConst411 = std::tan(311.68546f / fConst0);
		fConst412 = 1.0f / fConst411;
		fConst413 = 1.0f / ((fConst412 + 0.15748216f) / fConst411 + 0.9351402f);
		fConst414 = mydsp_faustpower2_f(fConst411);
		fConst415 = 50.06381f / fConst414;
		fConst416 = fConst415 + 0.9351402f;
		fConst417 = 1.0f / ((fConst412 + 0.74313045f) / fConst411 + 1.4500711f);
		fConst418 = 11.0520525f / fConst414;
		fConst419 = fConst418 + 1.4500711f;
		fConst420 = 1.0f / ((fConst412 + 3.1897273f) / fConst411 + 4.0767817f);
		fConst421 = 0.0017661728f / fConst414;
		fConst422 = fConst421 + 0.0004076782f;
		fConst423 = 1.0f / ((fConst374 + 0.16840488f) / fConst373 + 1.0693583f);
		fConst424 = fConst402 + 53.53615f;
		fConst425 = 1.0f / ((fConst374 + 0.51247865f) / fConst373 + 0.6896214f);
		fConst426 = fConst402 + 7.6217313f;
		fConst427 = 1.0f / ((fConst374 + 0.78241307f) / fConst373 + 0.2452915f);
		fConst428 = 0.0001f / fConst376;
		fConst429 = fConst428 + 0.0004332272f;
		fConst430 = (fConst374 + -0.78241307f) / fConst373 + 0.2452915f;
		fConst431 = 2.0f * (0.2452915f - fConst402);
		fConst432 = 2.0f * (0.0004332272f - fConst428);
		fConst433 = (fConst374 + -0.51247865f) / fConst373 + 0.6896214f;
		fConst434 = 2.0f * (0.6896214f - fConst402);
		fConst435 = 2.0f * (7.6217313f - fConst402);
		fConst436 = (fConst374 + -0.16840488f) / fConst373 + 1.0693583f;
		fConst437 = 2.0f * (1.0693583f - fConst402);
		fConst438 = 2.0f * (53.53615f - fConst402);
		fConst439 = (fConst412 + -3.1897273f) / fConst411 + 4.0767817f;
		fConst440 = 1.0f / fConst414;
		fConst441 = 2.0f * (4.0767817f - fConst440);
		fConst442 = 2.0f * (0.0004076782f - fConst421);
		fConst443 = (fConst412 + -0.74313045f) / fConst411 + 1.4500711f;
		fConst444 = 2.0f * (1.4500711f - fConst440);
		fConst445 = 2.0f * (1.4500711f - fConst418);
		fConst446 = (fConst412 + -0.15748216f) / fConst411 + 0.9351402f;
		fConst447 = 2.0f * (0.9351402f - fConst440);
		fConst448 = 2.0f * (0.9351402f - fConst415);
		fConst449 = std::tan(196.34955f / fConst0);
		fConst450 = 1.0f / fConst449;
		fConst451 = 1.0f / ((fConst450 + 0.15748216f) / fConst449 + 0.9351402f);
		fConst452 = mydsp_faustpower2_f(fConst449);
		fConst453 = 50.06381f / fConst452;
		fConst454 = fConst453 + 0.9351402f;
		fConst455 = 1.0f / ((fConst450 + 0.74313045f) / fConst449 + 1.4500711f);
		fConst456 = 11.0520525f / fConst452;
		fConst457 = fConst456 + 1.4500711f;
		fConst458 = 1.0f / ((fConst450 + 3.1897273f) / fConst449 + 4.0767817f);
		fConst459 = 0.0017661728f / fConst452;
		fConst460 = fConst459 + 0.0004076782f;
		fConst461 = 1.0f / ((fConst412 + 0.16840488f) / fConst411 + 1.0693583f);
		fConst462 = fConst440 + 53.53615f;
		fConst463 = 1.0f / ((fConst412 + 0.51247865f) / fConst411 + 0.6896214f);
		fConst464 = fConst440 + 7.6217313f;
		fConst465 = 1.0f / ((fConst412 + 0.78241307f) / fConst411 + 0.2452915f);
		fConst466 = 0.0001f / fConst414;
		fConst467 = fConst466 + 0.0004332272f;
		fConst468 = (fConst412 + -0.78241307f) / fConst411 + 0.2452915f;
		fConst469 = 2.0f * (0.2452915f - fConst440);
		fConst470 = 2.0f * (0.0004332272f - fConst466);
		fConst471 = (fConst412 + -0.51247865f) / fConst411 + 0.6896214f;
		fConst472 = 2.0f * (0.6896214f - fConst440);
		fConst473 = 2.0f * (7.6217313f - fConst440);
		fConst474 = (fConst412 + -0.16840488f) / fConst411 + 1.0693583f;
		fConst475 = 2.0f * (1.0693583f - fConst440);
		fConst476 = 2.0f * (53.53615f - fConst440);
		fConst477 = (fConst450 + -3.1897273f) / fConst449 + 4.0767817f;
		fConst478 = 1.0f / fConst452;
		fConst479 = 2.0f * (4.0767817f - fConst478);
		fConst480 = 2.0f * (0.0004076782f - fConst459);
		fConst481 = (fConst450 + -0.74313045f) / fConst449 + 1.4500711f;
		fConst482 = 2.0f * (1.4500711f - fConst478);
		fConst483 = 2.0f * (1.4500711f - fConst456);
		fConst484 = (fConst450 + -0.15748216f) / fConst449 + 0.9351402f;
		fConst485 = 2.0f * (0.9351402f - fConst478);
		fConst486 = 2.0f * (0.9351402f - fConst453);
		fConst487 = std::tan(123.69246f / fConst0);
		fConst488 = 1.0f / fConst487;
		fConst489 = 1.0f / ((fConst488 + 0.15748216f) / fConst487 + 0.9351402f);
		fConst490 = mydsp_faustpower2_f(fConst487);
		fConst491 = 50.06381f / fConst490;
		fConst492 = fConst491 + 0.9351402f;
		fConst493 = 1.0f / ((fConst488 + 0.74313045f) / fConst487 + 1.4500711f);
		fConst494 = 11.0520525f / fConst490;
		fConst495 = fConst494 + 1.4500711f;
		fConst496 = 1.0f / ((fConst488 + 3.1897273f) / fConst487 + 4.0767817f);
		fConst497 = 0.0017661728f / fConst490;
		fConst498 = fConst497 + 0.0004076782f;
		fConst499 = 1.0f / ((fConst450 + 0.16840488f) / fConst449 + 1.0693583f);
		fConst500 = fConst478 + 53.53615f;
		fConst501 = 1.0f / ((fConst450 + 0.51247865f) / fConst449 + 0.6896214f);
		fConst502 = fConst478 + 7.6217313f;
		fConst503 = 1.0f / ((fConst450 + 0.78241307f) / fConst449 + 0.2452915f);
		fConst504 = 0.0001f / fConst452;
		fConst505 = fConst504 + 0.0004332272f;
		fConst506 = (fConst450 + -0.78241307f) / fConst449 + 0.2452915f;
		fConst507 = 2.0f * (0.2452915f - fConst478);
		fConst508 = 2.0f * (0.0004332272f - fConst504);
		fConst509 = (fConst450 + -0.51247865f) / fConst449 + 0.6896214f;
		fConst510 = 2.0f * (0.6896214f - fConst478);
		fConst511 = 2.0f * (7.6217313f - fConst478);
		fConst512 = (fConst450 + -0.16840488f) / fConst449 + 1.0693583f;
		fConst513 = 2.0f * (1.0693583f - fConst478);
		fConst514 = 2.0f * (53.53615f - fConst478);
		fConst515 = (fConst488 + -3.1897273f) / fConst487 + 4.0767817f;
		fConst516 = 1.0f / fConst490;
		fConst517 = 2.0f * (4.0767817f - fConst516);
		fConst518 = 2.0f * (0.0004076782f - fConst497);
		fConst519 = (fConst488 + -0.74313045f) / fConst487 + 1.4500711f;
		fConst520 = 2.0f * (1.4500711f - fConst516);
		fConst521 = 2.0f * (1.4500711f - fConst494);
		fConst522 = (fConst488 + -0.15748216f) / fConst487 + 0.9351402f;
		fConst523 = 2.0f * (0.9351402f - fConst516);
		fConst524 = 2.0f * (0.9351402f - fConst491);
		fConst525 = 1.0f / ((fConst488 + 0.16840488f) / fConst487 + 1.0693583f);
		fConst526 = fConst516 + 53.53615f;
		fConst527 = 1.0f / ((fConst488 + 0.51247865f) / fConst487 + 0.6896214f);
		fConst528 = fConst516 + 7.6217313f;
		fConst529 = 1.0f / ((fConst488 + 0.78241307f) / fConst487 + 0.2452915f);
		fConst530 = 0.0001f / fConst490;
		fConst531 = fConst530 + 0.0004332272f;
		fConst532 = (fConst488 + -0.78241307f) / fConst487 + 0.2452915f;
		fConst533 = 2.0f * (0.2452915f - fConst516);
		fConst534 = 2.0f * (0.0004332272f - fConst530);
		fConst535 = (fConst488 + -0.51247865f) / fConst487 + 0.6896214f;
		fConst536 = 2.0f * (0.6896214f - fConst516);
		fConst537 = 2.0f * (7.6217313f - fConst516);
		fConst538 = (fConst488 + -0.16840488f) / fConst487 + 1.0693583f;
		fConst539 = 2.0f * (1.0693583f - fConst516);
		fConst540 = 2.0f * (53.53615f - fConst516);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(5e+01f);
		fHslider1 = FAUSTFLOAT(1e+02f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.5f);
		fVslider0 = FAUSTFLOAT(-2e+01f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fVslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.1f);
		fVslider3 = FAUSTFLOAT(-0.1f);
		fVslider4 = FAUSTFLOAT(0.1f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(1.0f);
		fHslider7 = FAUSTFLOAT(1e+01f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fHslider9 = FAUSTFLOAT(1.0f);
		fHslider10 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(1e+03f);
		fHslider12 = FAUSTFLOAT(1.5f);
		fHslider13 = FAUSTFLOAT(1e+02f);
		fHslider14 = FAUSTFLOAT(8e+02f);
		fHslider15 = FAUSTFLOAT(0.5f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec5[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec6[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec8[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec7[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fVec2[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fVec3[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fVec4[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec5[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fVec6[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec9[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fVec7[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fVec8[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fVec9[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fVec10[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fVec11[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fVec12[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec10[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fVec13[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fVec14[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fVec15[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fVec16[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fVec17[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fVec18[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			iRec11[l26] = 0;
		}
		for (int l27 = 0; l27 < 4; l27 = l27 + 1) {
			fRec12[l27] = 0.0f;
		}
		IOTA0 = 0;
		for (int l28 = 0; l28 < 4096; l28 = l28 + 1) {
			fVec19[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec13[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec19[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec20[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec18[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec17[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec16[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec15[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec14[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 4096; l37 = l37 + 1) {
			fVec20[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec21[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec26[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec25[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec24[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec23[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec22[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec3[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec2[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec1[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec0[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec33[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec32[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec31[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec30[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec29[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec28[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec27[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec40[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec39[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec38[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 3; l58 = l58 + 1) {
			fRec37[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 3; l59 = l59 + 1) {
			fRec36[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 3; l60 = l60 + 1) {
			fRec35[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec34[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 3; l62 = l62 + 1) {
			fRec47[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 3; l63 = l63 + 1) {
			fRec46[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 3; l64 = l64 + 1) {
			fRec45[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 3; l65 = l65 + 1) {
			fRec44[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 3; l66 = l66 + 1) {
			fRec43[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 3; l67 = l67 + 1) {
			fRec42[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec41[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 3; l69 = l69 + 1) {
			fRec54[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 3; l70 = l70 + 1) {
			fRec53[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 3; l71 = l71 + 1) {
			fRec52[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec51[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 3; l73 = l73 + 1) {
			fRec50[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 3; l74 = l74 + 1) {
			fRec49[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec48[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 3; l76 = l76 + 1) {
			fRec61[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 3; l77 = l77 + 1) {
			fRec60[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 3; l78 = l78 + 1) {
			fRec59[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 3; l79 = l79 + 1) {
			fRec58[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 3; l80 = l80 + 1) {
			fRec57[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec56[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec55[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 3; l83 = l83 + 1) {
			fRec68[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec67[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 3; l85 = l85 + 1) {
			fRec66[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 3; l86 = l86 + 1) {
			fRec65[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 3; l87 = l87 + 1) {
			fRec64[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 3; l88 = l88 + 1) {
			fRec63[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec62[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec75[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 3; l91 = l91 + 1) {
			fRec74[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec73[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 3; l93 = l93 + 1) {
			fRec72[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 3; l94 = l94 + 1) {
			fRec71[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 3; l95 = l95 + 1) {
			fRec70[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec69[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 3; l97 = l97 + 1) {
			fRec82[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 3; l98 = l98 + 1) {
			fRec81[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 3; l99 = l99 + 1) {
			fRec80[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 3; l100 = l100 + 1) {
			fRec79[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 3; l101 = l101 + 1) {
			fRec78[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 3; l102 = l102 + 1) {
			fRec77[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec76[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 3; l104 = l104 + 1) {
			fRec89[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 3; l105 = l105 + 1) {
			fRec88[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 3; l106 = l106 + 1) {
			fRec87[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 3; l107 = l107 + 1) {
			fRec86[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 3; l108 = l108 + 1) {
			fRec85[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 3; l109 = l109 + 1) {
			fRec84[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec83[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 3; l111 = l111 + 1) {
			fRec96[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 3; l112 = l112 + 1) {
			fRec95[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 3; l113 = l113 + 1) {
			fRec94[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 3; l114 = l114 + 1) {
			fRec93[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 3; l115 = l115 + 1) {
			fRec92[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 3; l116 = l116 + 1) {
			fRec91[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 2; l117 = l117 + 1) {
			fRec90[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 3; l118 = l118 + 1) {
			fRec103[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 3; l119 = l119 + 1) {
			fRec102[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 3; l120 = l120 + 1) {
			fRec101[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 3; l121 = l121 + 1) {
			fRec100[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 3; l122 = l122 + 1) {
			fRec99[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 3; l123 = l123 + 1) {
			fRec98[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fRec97[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 3; l125 = l125 + 1) {
			fRec110[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 3; l126 = l126 + 1) {
			fRec109[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 3; l127 = l127 + 1) {
			fRec108[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 3; l128 = l128 + 1) {
			fRec107[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 3; l129 = l129 + 1) {
			fRec106[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 3; l130 = l130 + 1) {
			fRec105[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fRec104[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 3; l132 = l132 + 1) {
			fRec117[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 3; l133 = l133 + 1) {
			fRec116[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 3; l134 = l134 + 1) {
			fRec115[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 3; l135 = l135 + 1) {
			fRec114[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 3; l136 = l136 + 1) {
			fRec113[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 3; l137 = l137 + 1) {
			fRec112[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec111[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 3; l139 = l139 + 1) {
			fRec121[l139] = 0.0f;
		}
		for (int l140 = 0; l140 < 3; l140 = l140 + 1) {
			fRec120[l140] = 0.0f;
		}
		for (int l141 = 0; l141 < 3; l141 = l141 + 1) {
			fRec119[l141] = 0.0f;
		}
		for (int l142 = 0; l142 < 2; l142 = l142 + 1) {
			fRec118[l142] = 0.0f;
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
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("phaserFlangerLab");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib         for documentation and references");
		ui_interface->openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Sawtooth         waveform amplitude");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Amplitude", &fVslider0, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-1.2e+02f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider1, "2", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Sawtooth         frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fVslider1, "unit", "PK");
		ui_interface->addVerticalSlider("Frequency", &fVslider1, FAUSTFLOAT(49.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(88.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentage frequency-shift     up or down for second oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider3, FAUSTFLOAT(-0.1f), FAUSTFLOAT(-1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider4, "4", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider4, FAUSTFLOAT(0.1f), FAUSTFLOAT(-1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider2, "5", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider2, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtootn aliasing         suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(4.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(0, "7", "");
		ui_interface->openVerticalBox("Alternate Signals");
		ui_interface->declare(&fCheckbox3, "0", "");
		ui_interface->addCheckButton("Noise (White or Pink - uses only Amplitude control on         the left)", &fCheckbox3);
		ui_interface->declare(&fCheckbox4, "1", "");
		ui_interface->declare(&fCheckbox4, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the         same total power in every octave");
		ui_interface->addCheckButton("Pink instead of White Noise (also called 1/f Noise)", &fCheckbox4);
		ui_interface->declare(&fCheckbox2, "2", "");
		ui_interface->addCheckButton("External Signal Input (overrides Sawtooth/Noise         selection above)", &fCheckbox2);
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
		ui_interface->declare(&fCheckbox1, "tooltip", "When this is checked, the flanger         has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox1);
		ui_interface->declare(&fCheckbox5, "1", "");
		ui_interface->addCheckButton("Invert Flange Sum", &fCheckbox5);
		ui_interface->declare(&fHbargraph0, "2", "");
		ui_interface->declare(&fHbargraph0, "style", "led");
		ui_interface->declare(&fHbargraph0, "tooltip", "Display sum of flange delays");
		ui_interface->addHorizontalBargraph("Flange LFO", &fHbargraph0, FAUSTFLOAT(-1.5f), FAUSTFLOAT(1.5f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider4, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider8, "2", "");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("Depth", &fHslider8, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider5, "3", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(-0.999f), FAUSTFLOAT(0.999f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Delay Controls");
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "ms");
		ui_interface->addHorizontalSlider("Flange Delay", &fHslider7, FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider6, "2", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Offset", &fHslider6, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Flanger Output Level", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("PHASER2");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the phaser         has no effect");
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
		ui_interface->addHorizontalSlider("Speed", &fHslider15, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider9, "2", "");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Depth (Intensity)", &fHslider9, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider10, "3", "");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback Gain", &fHslider10, FAUSTFLOAT(0.0f), FAUSTFLOAT(-0.999f), FAUSTFLOAT(0.999f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider11, "1", "");
		ui_interface->declare(&fHslider11, "scale", "log");
		ui_interface->declare(&fHslider11, "style", "knob");
		ui_interface->declare(&fHslider11, "unit", "Hz");
		ui_interface->addHorizontalSlider("Notch width", &fHslider11, FAUSTFLOAT(1e+03f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider13, "2", "");
		ui_interface->declare(&fHslider13, "scale", "log");
		ui_interface->declare(&fHslider13, "style", "knob");
		ui_interface->declare(&fHslider13, "unit", "Hz");
		ui_interface->addHorizontalSlider("Min Notch1 Freq", &fHslider13, FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider14, "3", "");
		ui_interface->declare(&fHslider14, "scale", "log");
		ui_interface->declare(&fHslider14, "style", "knob");
		ui_interface->declare(&fHslider14, "unit", "Hz");
		ui_interface->addHorizontalSlider("Max Notch1 Freq", &fHslider14, FAUSTFLOAT(8e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider12, "4", "");
		ui_interface->declare(&fHslider12, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &fHslider12, FAUSTFLOAT(1.5f), FAUSTFLOAT(1.1f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Phaser Output Level", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
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
		ui_interface->addVerticalBargraph("vbargraph0", &fVbargraph14, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph1", &fVbargraph13, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph2", &fVbargraph12, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph3", &fVbargraph11, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph10, "4", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph4", &fVbargraph10, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph9, "5", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph5", &fVbargraph9, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph8, "6", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph6", &fVbargraph8, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph7", &fVbargraph7, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph6, "8", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph8", &fVbargraph6, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph5, "9", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph9", &fVbargraph5, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph4, "10", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph10", &fVbargraph4, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph3, "11", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph11", &fVbargraph3, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph2, "12", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph12", &fVbargraph2, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph1, "13", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph13", &fVbargraph1, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fVbargraph0, "14", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("vbargraph14", &fVbargraph0, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, FAUSTFLOAT(5e+01f), FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = 0.001f * float(fHslider1);
		int iSlow2 = std::fabs(fSlow1) < 1.1920929e-07f;
		float fSlow3 = ((iSlow2) ? 0.0f : std::exp(-(fConst1 / ((iSlow2) ? 1.0f : fSlow1))));
		float fSlow4 = 1.0f - fSlow3;
		int iSlow5 = int(float(fCheckbox0));
		float fSlow6 = std::pow(1e+01f, 0.05f * float(fHslider2));
		int iSlow7 = int(float(fCheckbox1));
		float fSlow8 = std::pow(1e+01f, 0.05f * float(fHslider3));
		float fSlow9 = fConst14 * float(fHslider4);
		float fSlow10 = std::sin(fSlow9);
		float fSlow11 = std::cos(fSlow9);
		float fSlow12 = fConst15 * std::pow(1e+01f, 0.05f * float(fVslider0));
		int iSlow13 = int(float(fCheckbox2));
		int iSlow14 = int(float(fCheckbox3));
		int iSlow15 = int(float(fEntry0) + -1.0f);
		int iSlow16 = iSlow15 >= 2;
		int iSlow17 = iSlow15 >= 1;
		float fSlow18 = float(fVslider2);
		int iSlow19 = std::fabs(fSlow18) < 1.1920929e-07f;
		float fSlow20 = ((iSlow19) ? 0.0f : std::exp(-(fConst1 / ((iSlow19) ? 1.0f : fSlow18))));
		float fSlow21 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (float(fVslider1) + -49.0f)) * (1.0f - fSlow20);
		int iSlow22 = iSlow15 >= 3;
		float fSlow23 = 0.01f * float(fVslider3) + 1.0f;
		float fSlow24 = 0.01f * float(fVslider4) + 1.0f;
		int iSlow25 = int(float(fCheckbox4));
		float fSlow26 = float(fHslider5);
		float fSlow27 = 0.001f * float(fHslider6);
		float fSlow28 = 0.0005f * float(fHslider7);
		float fSlow29 = float(fHslider8);
		float fSlow30 = ((int(float(fCheckbox5))) ? -fSlow29 : fSlow29);
		float fSlow31 = 0.5f * ((int(float(fCheckbox6))) ? 2.0f : float(fHslider9));
		float fSlow32 = 1.0f - fSlow31;
		float fSlow33 = float(fHslider10);
		float fSlow34 = std::exp(-(fConst20 * float(fHslider11)));
		float fSlow35 = 2.0f * fSlow34;
		float fSlow36 = float(fHslider12);
		float fSlow37 = fConst1 * fSlow36;
		float fSlow38 = float(fHslider13);
		float fSlow39 = 6.2831855f * fSlow38;
		float fSlow40 = 3.1415927f * (fSlow38 - std::max<float>(fSlow38, float(fHslider14)));
		float fSlow41 = fConst14 * float(fHslider15);
		float fSlow42 = std::sin(fSlow41);
		float fSlow43 = std::cos(fSlow41);
		float fSlow44 = mydsp_faustpower2_f(fSlow34);
		float fSlow45 = fConst1 * mydsp_faustpower2_f(fSlow36);
		float fSlow46 = fConst1 * mydsp_faustpower3_f(fSlow36);
		float fSlow47 = fConst1 * mydsp_faustpower4_f(fSlow36);
		float fSlow48 = ((int(float(fCheckbox7))) ? -fSlow31 : fSlow31);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec4[0] = fSlow10 * fRec5[1] + fSlow11 * fRec4[1];
			int iTemp0 = 1 - iVec0[1];
			float fTemp1 = float(iTemp0);
			fRec5[0] = fTemp1 + fSlow11 * fRec5[1] - fSlow10 * fRec4[1];
			fHbargraph0 = FAUSTFLOAT(fRec5[0] + fRec4[0]);
			fRec6[0] = fSlow12 + fConst16 * fRec6[1];
			fRec8[0] = fSlow21 + fSlow20 * fRec8[1];
			float fTemp2 = std::max<float>(2e+01f, std::fabs(fRec8[0]));
			float fTemp3 = ((iTemp0) ? 0.0f : fRec7[1] + fConst1 * fTemp2);
			fRec7[0] = fTemp3 - std::floor(fTemp3);
			float fTemp4 = 2.0f * fRec7[0];
			float fTemp5 = fTemp4 + -1.0f;
			float fTemp6 = float(iVec0[1]);
			float fTemp7 = mydsp_faustpower2_f(fTemp5);
			fVec1[0] = fTemp7;
			float fTemp8 = float(iVec0[2]);
			float fTemp9 = mydsp_faustpower3_f(fTemp5);
			fVec2[0] = fTemp9 + (1.0f - fTemp4);
			float fTemp10 = (fTemp9 + (1.0f - (fTemp4 + fVec2[1]))) / fTemp2;
			fVec3[0] = fTemp10;
			float fTemp11 = float(iVec0[3]);
			float fTemp12 = fTemp7 * (fTemp7 + -2.0f);
			fVec4[0] = fTemp12;
			float fTemp13 = (fTemp12 - fVec4[1]) / fTemp2;
			fVec5[0] = fTemp13;
			float fTemp14 = (fTemp13 - fVec5[1]) / fTemp2;
			fVec6[0] = fTemp14;
			float fTemp15 = std::max<float>(2e+01f, std::fabs(fSlow23 * fRec8[0]));
			float fTemp16 = ((iTemp0) ? 0.0f : fRec9[1] + fConst1 * fTemp15);
			fRec9[0] = fTemp16 - std::floor(fTemp16);
			float fTemp17 = 2.0f * fRec9[0];
			float fTemp18 = fTemp17 + -1.0f;
			float fTemp19 = mydsp_faustpower2_f(fTemp18);
			fVec7[0] = fTemp19;
			float fTemp20 = mydsp_faustpower3_f(fTemp18);
			fVec8[0] = fTemp20 + (1.0f - fTemp17);
			float fTemp21 = (fTemp20 + (1.0f - (fTemp17 + fVec8[1]))) / fTemp15;
			fVec9[0] = fTemp21;
			float fTemp22 = fTemp19 * (fTemp19 + -2.0f);
			fVec10[0] = fTemp22;
			float fTemp23 = (fTemp22 - fVec10[1]) / fTemp15;
			fVec11[0] = fTemp23;
			float fTemp24 = (fTemp23 - fVec11[1]) / fTemp15;
			fVec12[0] = fTemp24;
			float fTemp25 = std::max<float>(2e+01f, std::fabs(fSlow24 * fRec8[0]));
			float fTemp26 = ((iTemp0) ? 0.0f : fRec10[1] + fConst1 * fTemp25);
			fRec10[0] = fTemp26 - std::floor(fTemp26);
			float fTemp27 = 2.0f * fRec10[0];
			float fTemp28 = fTemp27 + -1.0f;
			float fTemp29 = mydsp_faustpower2_f(fTemp28);
			fVec13[0] = fTemp29;
			float fTemp30 = mydsp_faustpower3_f(fTemp28);
			fVec14[0] = fTemp30 + (1.0f - fTemp27);
			float fTemp31 = (fTemp30 + (1.0f - (fTemp27 + fVec14[1]))) / fTemp25;
			fVec15[0] = fTemp31;
			float fTemp32 = fTemp29 * (fTemp29 + -2.0f);
			fVec16[0] = fTemp32;
			float fTemp33 = (fTemp32 - fVec16[1]) / fTemp25;
			fVec17[0] = fTemp33;
			float fTemp34 = (fTemp33 - fVec17[1]) / fTemp25;
			fVec18[0] = fTemp34;
			iRec11[0] = 1103515245 * iRec11[1] + 12345;
			float fTemp35 = 4.656613e-10f * float(iRec11[0]);
			fRec12[0] = 0.5221894f * fRec12[3] + fTemp35 + 2.494956f * fRec12[1] - 2.0172658f * fRec12[2];
			float fTemp36 = fRec6[0] * ((iSlow13) ? float(input0[i0]) : ((iSlow14) ? ((iSlow25) ? 0.049922034f * fRec12[0] + 0.0506127f * fRec12[2] - (0.095993534f * fRec12[1] + 0.004408786f * fRec12[3]) : fTemp35) : 0.33333334f * fRec6[0] * (((iSlow16) ? ((iSlow22) ? fConst19 * (fTemp11 * (fTemp14 - fVec6[1]) / fTemp2) : fConst18 * (fTemp8 * (fTemp10 - fVec3[1]) / fTemp2)) : ((iSlow17) ? fConst17 * (fTemp6 * (fTemp7 - fVec1[1]) / fTemp2) : fTemp5)) + ((iSlow16) ? ((iSlow22) ? fConst19 * (fTemp11 * (fTemp24 - fVec12[1]) / fTemp15) : fConst18 * (fTemp8 * (fTemp21 - fVec9[1]) / fTemp15)) : ((iSlow17) ? fConst17 * (fTemp6 * (fTemp19 - fVec7[1]) / fTemp15) : fTemp18)) + ((iSlow16) ? ((iSlow22) ? fConst19 * (fTemp11 * (fTemp34 - fVec18[1]) / fTemp25) : fConst18 * (fTemp8 * (fTemp31 - fVec15[1]) / fTemp25)) : ((iSlow17) ? fConst17 * (fTemp6 * (fTemp29 - fVec13[1]) / fTemp25) : fTemp28)))));
			float fTemp37 = ((iSlow7) ? 0.0f : fTemp36);
			float fTemp38 = fSlow8 * fTemp37;
			float fTemp39 = fSlow26 * fRec13[1] - fTemp38;
			fVec19[IOTA0 & 4095] = fTemp39;
			float fTemp40 = fConst0 * (fSlow27 + fSlow28 * (fRec4[0] + 1.0f));
			int iTemp41 = int(fTemp40);
			float fTemp42 = std::floor(fTemp40);
			fRec13[0] = fVec19[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp41))) & 4095] * (fTemp42 + (1.0f - fTemp40)) + (fTemp40 - fTemp42) * fVec19[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp41 + 1))) & 4095];
			float fTemp43 = ((iSlow7) ? fTemp36 : 0.5f * (fTemp38 + fRec13[0] * fSlow30));
			float fTemp44 = ((iSlow5) ? 0.0f : fTemp43);
			fRec19[0] = fSlow42 * fRec20[1] + fSlow43 * fRec19[1];
			fRec20[0] = fTemp1 + fSlow43 * fRec20[1] - fSlow42 * fRec19[1];
			float fTemp45 = fSlow39 - fSlow40 * (1.0f - fRec19[0]);
			float fTemp46 = fRec18[1] * std::cos(fSlow37 * fTemp45);
			fRec18[0] = fSlow6 * fTemp44 + fSlow33 * fRec14[1] + fSlow35 * fTemp46 - fSlow44 * fRec18[2];
			float fTemp47 = fRec17[1] * std::cos(fSlow45 * fTemp45);
			fRec17[0] = fRec18[2] + fSlow44 * (fRec18[0] - fRec17[2]) - fSlow35 * (fTemp46 - fTemp47);
			float fTemp48 = fRec16[1] * std::cos(fSlow46 * fTemp45);
			fRec16[0] = fRec17[2] + fSlow44 * (fRec17[0] - fRec16[2]) - fSlow35 * (fTemp47 - fTemp48);
			float fTemp49 = fRec15[1] * std::cos(fSlow47 * fTemp45);
			fRec15[0] = fRec16[2] + fSlow44 * (fRec16[0] - fRec15[2]) - fSlow35 * (fTemp48 - fTemp49);
			fRec14[0] = fRec15[2] + fSlow44 * fRec15[0] - fSlow35 * fTemp49;
			float fTemp50 = ((iSlow5) ? fTemp43 : fSlow6 * fTemp44 * fSlow32 + fRec14[0] * fSlow48);
			float fTemp51 = fSlow8 * fTemp37;
			float fTemp52 = fSlow26 * fRec21[1] - fTemp51;
			fVec20[IOTA0 & 4095] = fTemp52;
			float fTemp53 = fConst0 * (fSlow27 + fSlow28 * (fRec5[0] + 1.0f));
			int iTemp54 = int(fTemp53);
			float fTemp55 = std::floor(fTemp53);
			fRec21[0] = fVec20[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp54))) & 4095] * (fTemp55 + (1.0f - fTemp53)) + (fTemp53 - fTemp55) * fVec20[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp54 + 1))) & 4095];
			float fTemp56 = ((iSlow7) ? fTemp36 : 0.5f * (fTemp51 + fRec21[0] * fSlow30));
			float fTemp57 = ((iSlow5) ? 0.0f : fTemp56);
			float fTemp58 = fSlow39 - fSlow40 * (1.0f - fRec20[0]);
			float fTemp59 = fRec26[1] * std::cos(fSlow37 * fTemp58);
			fRec26[0] = fSlow6 * fTemp57 + fSlow33 * fRec22[1] + fSlow35 * fTemp59 - fSlow44 * fRec26[2];
			float fTemp60 = fRec25[1] * std::cos(fSlow45 * fTemp58);
			fRec25[0] = fRec26[2] + fSlow44 * (fRec26[0] - fRec25[2]) - fSlow35 * (fTemp59 - fTemp60);
			float fTemp61 = fRec24[1] * std::cos(fSlow46 * fTemp58);
			fRec24[0] = fRec25[2] + fSlow44 * (fRec25[0] - fRec24[2]) - fSlow35 * (fTemp60 - fTemp61);
			float fTemp62 = fRec23[1] * std::cos(fSlow47 * fTemp58);
			fRec23[0] = fRec24[2] + fSlow44 * (fRec24[0] - fRec23[2]) - fSlow35 * (fTemp61 - fTemp62);
			fRec22[0] = fRec23[2] + fSlow44 * fRec23[0] - fSlow35 * fTemp62;
			float fTemp63 = ((iSlow5) ? fTemp56 : fSlow6 * fSlow32 * fTemp57 + fRec22[0] * fSlow48);
			float fTemp64 = fTemp50 + fTemp63;
			fRec3[0] = fTemp64 - fConst11 * (fConst21 * fRec3[2] + fConst23 * fRec3[1]);
			fRec2[0] = fConst11 * (fConst13 * fRec3[0] + fConst24 * fRec3[1] + fConst13 * fRec3[2]) - fConst8 * (fConst25 * fRec2[2] + fConst26 * fRec2[1]);
			fRec1[0] = fConst8 * (fConst10 * fRec2[0] + fConst27 * fRec2[1] + fConst10 * fRec2[2]) - fConst4 * (fConst28 * fRec1[2] + fConst29 * fRec1[1]);
			fRec0[0] = fSlow4 * std::fabs(fConst4 * (fConst7 * fRec1[0] + fConst30 * fRec1[1] + fConst7 * fRec1[2])) + fSlow3 * fRec0[1];
			fVbargraph0 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec0[0]))));
			fRec33[0] = fTemp64 - fConst47 * (fConst50 * fRec33[2] + fConst51 * fRec33[1]);
			fRec32[0] = fConst47 * (fConst49 * fRec33[0] + fConst52 * fRec33[1] + fConst49 * fRec33[2]) - fConst45 * (fConst53 * fRec32[2] + fConst54 * fRec32[1]);
			fRec31[0] = fConst45 * (fConst46 * fRec32[0] + fConst55 * fRec32[1] + fConst46 * fRec32[2]) - fConst43 * (fConst56 * fRec31[2] + fConst57 * fRec31[1]);
			float fTemp65 = fConst43 * (fConst44 * fRec31[0] + fConst58 * fRec31[1] + fConst44 * fRec31[2]);
			fRec30[0] = fTemp65 - fConst40 * (fConst59 * fRec30[2] + fConst61 * fRec30[1]);
			fRec29[0] = fConst40 * (fConst42 * fRec30[0] + fConst62 * fRec30[1] + fConst42 * fRec30[2]) - fConst37 * (fConst63 * fRec29[2] + fConst64 * fRec29[1]);
			fRec28[0] = fConst37 * (fConst39 * fRec29[0] + fConst65 * fRec29[1] + fConst39 * fRec29[2]) - fConst33 * (fConst66 * fRec28[2] + fConst67 * fRec28[1]);
			fRec27[0] = fSlow4 * std::fabs(fConst33 * (fConst36 * fRec28[0] + fConst68 * fRec28[1] + fConst36 * fRec28[2])) + fSlow3 * fRec27[1];
			fVbargraph1 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec27[0]))));
			fRec40[0] = fTemp65 - fConst85 * (fConst88 * fRec40[2] + fConst89 * fRec40[1]);
			fRec39[0] = fConst85 * (fConst87 * fRec40[0] + fConst90 * fRec40[1] + fConst87 * fRec40[2]) - fConst83 * (fConst91 * fRec39[2] + fConst92 * fRec39[1]);
			fRec38[0] = fConst83 * (fConst84 * fRec39[0] + fConst93 * fRec39[1] + fConst84 * fRec39[2]) - fConst81 * (fConst94 * fRec38[2] + fConst95 * fRec38[1]);
			float fTemp66 = fConst81 * (fConst82 * fRec38[0] + fConst96 * fRec38[1] + fConst82 * fRec38[2]);
			fRec37[0] = fTemp66 - fConst78 * (fConst97 * fRec37[2] + fConst99 * fRec37[1]);
			fRec36[0] = fConst78 * (fConst80 * fRec37[0] + fConst100 * fRec37[1] + fConst80 * fRec37[2]) - fConst75 * (fConst101 * fRec36[2] + fConst102 * fRec36[1]);
			fRec35[0] = fConst75 * (fConst77 * fRec36[0] + fConst103 * fRec36[1] + fConst77 * fRec36[2]) - fConst71 * (fConst104 * fRec35[2] + fConst105 * fRec35[1]);
			fRec34[0] = fSlow4 * std::fabs(fConst71 * (fConst74 * fRec35[0] + fConst106 * fRec35[1] + fConst74 * fRec35[2])) + fSlow3 * fRec34[1];
			fVbargraph2 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec34[0]))));
			fRec47[0] = fTemp66 - fConst123 * (fConst126 * fRec47[2] + fConst127 * fRec47[1]);
			fRec46[0] = fConst123 * (fConst125 * fRec47[0] + fConst128 * fRec47[1] + fConst125 * fRec47[2]) - fConst121 * (fConst129 * fRec46[2] + fConst130 * fRec46[1]);
			fRec45[0] = fConst121 * (fConst122 * fRec46[0] + fConst131 * fRec46[1] + fConst122 * fRec46[2]) - fConst119 * (fConst132 * fRec45[2] + fConst133 * fRec45[1]);
			float fTemp67 = fConst119 * (fConst120 * fRec45[0] + fConst134 * fRec45[1] + fConst120 * fRec45[2]);
			fRec44[0] = fTemp67 - fConst116 * (fConst135 * fRec44[2] + fConst137 * fRec44[1]);
			fRec43[0] = fConst116 * (fConst118 * fRec44[0] + fConst138 * fRec44[1] + fConst118 * fRec44[2]) - fConst113 * (fConst139 * fRec43[2] + fConst140 * fRec43[1]);
			fRec42[0] = fConst113 * (fConst115 * fRec43[0] + fConst141 * fRec43[1] + fConst115 * fRec43[2]) - fConst109 * (fConst142 * fRec42[2] + fConst143 * fRec42[1]);
			fRec41[0] = fSlow4 * std::fabs(fConst109 * (fConst112 * fRec42[0] + fConst144 * fRec42[1] + fConst112 * fRec42[2])) + fSlow3 * fRec41[1];
			fVbargraph3 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec41[0]))));
			fRec54[0] = fTemp67 - fConst161 * (fConst164 * fRec54[2] + fConst165 * fRec54[1]);
			fRec53[0] = fConst161 * (fConst163 * fRec54[0] + fConst166 * fRec54[1] + fConst163 * fRec54[2]) - fConst159 * (fConst167 * fRec53[2] + fConst168 * fRec53[1]);
			fRec52[0] = fConst159 * (fConst160 * fRec53[0] + fConst169 * fRec53[1] + fConst160 * fRec53[2]) - fConst157 * (fConst170 * fRec52[2] + fConst171 * fRec52[1]);
			float fTemp68 = fConst157 * (fConst158 * fRec52[0] + fConst172 * fRec52[1] + fConst158 * fRec52[2]);
			fRec51[0] = fTemp68 - fConst154 * (fConst173 * fRec51[2] + fConst175 * fRec51[1]);
			fRec50[0] = fConst154 * (fConst156 * fRec51[0] + fConst176 * fRec51[1] + fConst156 * fRec51[2]) - fConst151 * (fConst177 * fRec50[2] + fConst178 * fRec50[1]);
			fRec49[0] = fConst151 * (fConst153 * fRec50[0] + fConst179 * fRec50[1] + fConst153 * fRec50[2]) - fConst147 * (fConst180 * fRec49[2] + fConst181 * fRec49[1]);
			fRec48[0] = fSlow4 * std::fabs(fConst147 * (fConst150 * fRec49[0] + fConst182 * fRec49[1] + fConst150 * fRec49[2])) + fSlow3 * fRec48[1];
			fVbargraph4 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec48[0]))));
			fRec61[0] = fTemp68 - fConst199 * (fConst202 * fRec61[2] + fConst203 * fRec61[1]);
			fRec60[0] = fConst199 * (fConst201 * fRec61[0] + fConst204 * fRec61[1] + fConst201 * fRec61[2]) - fConst197 * (fConst205 * fRec60[2] + fConst206 * fRec60[1]);
			fRec59[0] = fConst197 * (fConst198 * fRec60[0] + fConst207 * fRec60[1] + fConst198 * fRec60[2]) - fConst195 * (fConst208 * fRec59[2] + fConst209 * fRec59[1]);
			float fTemp69 = fConst195 * (fConst196 * fRec59[0] + fConst210 * fRec59[1] + fConst196 * fRec59[2]);
			fRec58[0] = fTemp69 - fConst192 * (fConst211 * fRec58[2] + fConst213 * fRec58[1]);
			fRec57[0] = fConst192 * (fConst194 * fRec58[0] + fConst214 * fRec58[1] + fConst194 * fRec58[2]) - fConst189 * (fConst215 * fRec57[2] + fConst216 * fRec57[1]);
			fRec56[0] = fConst189 * (fConst191 * fRec57[0] + fConst217 * fRec57[1] + fConst191 * fRec57[2]) - fConst185 * (fConst218 * fRec56[2] + fConst219 * fRec56[1]);
			fRec55[0] = fSlow4 * std::fabs(fConst185 * (fConst188 * fRec56[0] + fConst220 * fRec56[1] + fConst188 * fRec56[2])) + fSlow3 * fRec55[1];
			fVbargraph5 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec55[0]))));
			fRec68[0] = fTemp69 - fConst237 * (fConst240 * fRec68[2] + fConst241 * fRec68[1]);
			fRec67[0] = fConst237 * (fConst239 * fRec68[0] + fConst242 * fRec68[1] + fConst239 * fRec68[2]) - fConst235 * (fConst243 * fRec67[2] + fConst244 * fRec67[1]);
			fRec66[0] = fConst235 * (fConst236 * fRec67[0] + fConst245 * fRec67[1] + fConst236 * fRec67[2]) - fConst233 * (fConst246 * fRec66[2] + fConst247 * fRec66[1]);
			float fTemp70 = fConst233 * (fConst234 * fRec66[0] + fConst248 * fRec66[1] + fConst234 * fRec66[2]);
			fRec65[0] = fTemp70 - fConst230 * (fConst249 * fRec65[2] + fConst251 * fRec65[1]);
			fRec64[0] = fConst230 * (fConst232 * fRec65[0] + fConst252 * fRec65[1] + fConst232 * fRec65[2]) - fConst227 * (fConst253 * fRec64[2] + fConst254 * fRec64[1]);
			fRec63[0] = fConst227 * (fConst229 * fRec64[0] + fConst255 * fRec64[1] + fConst229 * fRec64[2]) - fConst223 * (fConst256 * fRec63[2] + fConst257 * fRec63[1]);
			fRec62[0] = fSlow4 * std::fabs(fConst223 * (fConst226 * fRec63[0] + fConst258 * fRec63[1] + fConst226 * fRec63[2])) + fSlow3 * fRec62[1];
			fVbargraph6 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec62[0]))));
			fRec75[0] = fTemp70 - fConst275 * (fConst278 * fRec75[2] + fConst279 * fRec75[1]);
			fRec74[0] = fConst275 * (fConst277 * fRec75[0] + fConst280 * fRec75[1] + fConst277 * fRec75[2]) - fConst273 * (fConst281 * fRec74[2] + fConst282 * fRec74[1]);
			fRec73[0] = fConst273 * (fConst274 * fRec74[0] + fConst283 * fRec74[1] + fConst274 * fRec74[2]) - fConst271 * (fConst284 * fRec73[2] + fConst285 * fRec73[1]);
			float fTemp71 = fConst271 * (fConst272 * fRec73[0] + fConst286 * fRec73[1] + fConst272 * fRec73[2]);
			fRec72[0] = fTemp71 - fConst268 * (fConst287 * fRec72[2] + fConst289 * fRec72[1]);
			fRec71[0] = fConst268 * (fConst270 * fRec72[0] + fConst290 * fRec72[1] + fConst270 * fRec72[2]) - fConst265 * (fConst291 * fRec71[2] + fConst292 * fRec71[1]);
			fRec70[0] = fConst265 * (fConst267 * fRec71[0] + fConst293 * fRec71[1] + fConst267 * fRec71[2]) - fConst261 * (fConst294 * fRec70[2] + fConst295 * fRec70[1]);
			fRec69[0] = fSlow4 * std::fabs(fConst261 * (fConst264 * fRec70[0] + fConst296 * fRec70[1] + fConst264 * fRec70[2])) + fSlow3 * fRec69[1];
			fVbargraph7 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec69[0]))));
			fRec82[0] = fTemp71 - fConst313 * (fConst316 * fRec82[2] + fConst317 * fRec82[1]);
			fRec81[0] = fConst313 * (fConst315 * fRec82[0] + fConst318 * fRec82[1] + fConst315 * fRec82[2]) - fConst311 * (fConst319 * fRec81[2] + fConst320 * fRec81[1]);
			fRec80[0] = fConst311 * (fConst312 * fRec81[0] + fConst321 * fRec81[1] + fConst312 * fRec81[2]) - fConst309 * (fConst322 * fRec80[2] + fConst323 * fRec80[1]);
			float fTemp72 = fConst309 * (fConst310 * fRec80[0] + fConst324 * fRec80[1] + fConst310 * fRec80[2]);
			fRec79[0] = fTemp72 - fConst306 * (fConst325 * fRec79[2] + fConst327 * fRec79[1]);
			fRec78[0] = fConst306 * (fConst308 * fRec79[0] + fConst328 * fRec79[1] + fConst308 * fRec79[2]) - fConst303 * (fConst329 * fRec78[2] + fConst330 * fRec78[1]);
			fRec77[0] = fConst303 * (fConst305 * fRec78[0] + fConst331 * fRec78[1] + fConst305 * fRec78[2]) - fConst299 * (fConst332 * fRec77[2] + fConst333 * fRec77[1]);
			fRec76[0] = fSlow4 * std::fabs(fConst299 * (fConst302 * fRec77[0] + fConst334 * fRec77[1] + fConst302 * fRec77[2])) + fSlow3 * fRec76[1];
			fVbargraph8 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec76[0]))));
			fRec89[0] = fTemp72 - fConst351 * (fConst354 * fRec89[2] + fConst355 * fRec89[1]);
			fRec88[0] = fConst351 * (fConst353 * fRec89[0] + fConst356 * fRec89[1] + fConst353 * fRec89[2]) - fConst349 * (fConst357 * fRec88[2] + fConst358 * fRec88[1]);
			fRec87[0] = fConst349 * (fConst350 * fRec88[0] + fConst359 * fRec88[1] + fConst350 * fRec88[2]) - fConst347 * (fConst360 * fRec87[2] + fConst361 * fRec87[1]);
			float fTemp73 = fConst347 * (fConst348 * fRec87[0] + fConst362 * fRec87[1] + fConst348 * fRec87[2]);
			fRec86[0] = fTemp73 - fConst344 * (fConst363 * fRec86[2] + fConst365 * fRec86[1]);
			fRec85[0] = fConst344 * (fConst346 * fRec86[0] + fConst366 * fRec86[1] + fConst346 * fRec86[2]) - fConst341 * (fConst367 * fRec85[2] + fConst368 * fRec85[1]);
			fRec84[0] = fConst341 * (fConst343 * fRec85[0] + fConst369 * fRec85[1] + fConst343 * fRec85[2]) - fConst337 * (fConst370 * fRec84[2] + fConst371 * fRec84[1]);
			fRec83[0] = fSlow4 * std::fabs(fConst337 * (fConst340 * fRec84[0] + fConst372 * fRec84[1] + fConst340 * fRec84[2])) + fSlow3 * fRec83[1];
			fVbargraph9 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec83[0]))));
			fRec96[0] = fTemp73 - fConst389 * (fConst392 * fRec96[2] + fConst393 * fRec96[1]);
			fRec95[0] = fConst389 * (fConst391 * fRec96[0] + fConst394 * fRec96[1] + fConst391 * fRec96[2]) - fConst387 * (fConst395 * fRec95[2] + fConst396 * fRec95[1]);
			fRec94[0] = fConst387 * (fConst388 * fRec95[0] + fConst397 * fRec95[1] + fConst388 * fRec95[2]) - fConst385 * (fConst398 * fRec94[2] + fConst399 * fRec94[1]);
			float fTemp74 = fConst385 * (fConst386 * fRec94[0] + fConst400 * fRec94[1] + fConst386 * fRec94[2]);
			fRec93[0] = fTemp74 - fConst382 * (fConst401 * fRec93[2] + fConst403 * fRec93[1]);
			fRec92[0] = fConst382 * (fConst384 * fRec93[0] + fConst404 * fRec93[1] + fConst384 * fRec93[2]) - fConst379 * (fConst405 * fRec92[2] + fConst406 * fRec92[1]);
			fRec91[0] = fConst379 * (fConst381 * fRec92[0] + fConst407 * fRec92[1] + fConst381 * fRec92[2]) - fConst375 * (fConst408 * fRec91[2] + fConst409 * fRec91[1]);
			fRec90[0] = fSlow4 * std::fabs(fConst375 * (fConst378 * fRec91[0] + fConst410 * fRec91[1] + fConst378 * fRec91[2])) + fSlow3 * fRec90[1];
			fVbargraph10 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec90[0]))));
			fRec103[0] = fTemp74 - fConst427 * (fConst430 * fRec103[2] + fConst431 * fRec103[1]);
			fRec102[0] = fConst427 * (fConst429 * fRec103[0] + fConst432 * fRec103[1] + fConst429 * fRec103[2]) - fConst425 * (fConst433 * fRec102[2] + fConst434 * fRec102[1]);
			fRec101[0] = fConst425 * (fConst426 * fRec102[0] + fConst435 * fRec102[1] + fConst426 * fRec102[2]) - fConst423 * (fConst436 * fRec101[2] + fConst437 * fRec101[1]);
			float fTemp75 = fConst423 * (fConst424 * fRec101[0] + fConst438 * fRec101[1] + fConst424 * fRec101[2]);
			fRec100[0] = fTemp75 - fConst420 * (fConst439 * fRec100[2] + fConst441 * fRec100[1]);
			fRec99[0] = fConst420 * (fConst422 * fRec100[0] + fConst442 * fRec100[1] + fConst422 * fRec100[2]) - fConst417 * (fConst443 * fRec99[2] + fConst444 * fRec99[1]);
			fRec98[0] = fConst417 * (fConst419 * fRec99[0] + fConst445 * fRec99[1] + fConst419 * fRec99[2]) - fConst413 * (fConst446 * fRec98[2] + fConst447 * fRec98[1]);
			fRec97[0] = fSlow4 * std::fabs(fConst413 * (fConst416 * fRec98[0] + fConst448 * fRec98[1] + fConst416 * fRec98[2])) + fSlow3 * fRec97[1];
			fVbargraph11 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec97[0]))));
			fRec110[0] = fTemp75 - fConst465 * (fConst468 * fRec110[2] + fConst469 * fRec110[1]);
			fRec109[0] = fConst465 * (fConst467 * fRec110[0] + fConst470 * fRec110[1] + fConst467 * fRec110[2]) - fConst463 * (fConst471 * fRec109[2] + fConst472 * fRec109[1]);
			fRec108[0] = fConst463 * (fConst464 * fRec109[0] + fConst473 * fRec109[1] + fConst464 * fRec109[2]) - fConst461 * (fConst474 * fRec108[2] + fConst475 * fRec108[1]);
			float fTemp76 = fConst461 * (fConst462 * fRec108[0] + fConst476 * fRec108[1] + fConst462 * fRec108[2]);
			fRec107[0] = fTemp76 - fConst458 * (fConst477 * fRec107[2] + fConst479 * fRec107[1]);
			fRec106[0] = fConst458 * (fConst460 * fRec107[0] + fConst480 * fRec107[1] + fConst460 * fRec107[2]) - fConst455 * (fConst481 * fRec106[2] + fConst482 * fRec106[1]);
			fRec105[0] = fConst455 * (fConst457 * fRec106[0] + fConst483 * fRec106[1] + fConst457 * fRec106[2]) - fConst451 * (fConst484 * fRec105[2] + fConst485 * fRec105[1]);
			fRec104[0] = fSlow4 * std::fabs(fConst451 * (fConst454 * fRec105[0] + fConst486 * fRec105[1] + fConst454 * fRec105[2])) + fSlow3 * fRec104[1];
			fVbargraph12 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec104[0]))));
			fRec117[0] = fTemp76 - fConst503 * (fConst506 * fRec117[2] + fConst507 * fRec117[1]);
			fRec116[0] = fConst503 * (fConst505 * fRec117[0] + fConst508 * fRec117[1] + fConst505 * fRec117[2]) - fConst501 * (fConst509 * fRec116[2] + fConst510 * fRec116[1]);
			fRec115[0] = fConst501 * (fConst502 * fRec116[0] + fConst511 * fRec116[1] + fConst502 * fRec116[2]) - fConst499 * (fConst512 * fRec115[2] + fConst513 * fRec115[1]);
			float fTemp77 = fConst499 * (fConst500 * fRec115[0] + fConst514 * fRec115[1] + fConst500 * fRec115[2]);
			fRec114[0] = fTemp77 - fConst496 * (fConst515 * fRec114[2] + fConst517 * fRec114[1]);
			fRec113[0] = fConst496 * (fConst498 * fRec114[0] + fConst518 * fRec114[1] + fConst498 * fRec114[2]) - fConst493 * (fConst519 * fRec113[2] + fConst520 * fRec113[1]);
			fRec112[0] = fConst493 * (fConst495 * fRec113[0] + fConst521 * fRec113[1] + fConst495 * fRec113[2]) - fConst489 * (fConst522 * fRec112[2] + fConst523 * fRec112[1]);
			fRec111[0] = fSlow4 * std::fabs(fConst489 * (fConst492 * fRec112[0] + fConst524 * fRec112[1] + fConst492 * fRec112[2])) + fSlow3 * fRec111[1];
			fVbargraph13 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec111[0]))));
			fRec121[0] = fTemp77 - fConst529 * (fConst532 * fRec121[2] + fConst533 * fRec121[1]);
			fRec120[0] = fConst529 * (fConst531 * fRec121[0] + fConst534 * fRec121[1] + fConst531 * fRec121[2]) - fConst527 * (fConst535 * fRec120[2] + fConst536 * fRec120[1]);
			fRec119[0] = fConst527 * (fConst528 * fRec120[0] + fConst537 * fRec120[1] + fConst528 * fRec120[2]) - fConst525 * (fConst538 * fRec119[2] + fConst539 * fRec119[1]);
			fRec118[0] = fSlow4 * std::fabs(fConst525 * (fConst526 * fRec119[0] + fConst540 * fRec119[1] + fConst526 * fRec119[2])) + fSlow3 * fRec118[1];
			fVbargraph14 = FAUSTFLOAT(fSlow0 + 2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::max<float>(1.1920929e-07f, fRec118[0]))));
			output0[i0] = FAUSTFLOAT(fTemp50);
			output1[i0] = FAUSTFLOAT(fTemp63);
			for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
				iVec0[j0] = iVec0[j0 - 1];
			}
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fRec9[1] = fRec9[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fRec10[1] = fRec10[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			iRec11[1] = iRec11[0];
			for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
				fRec12[j1] = fRec12[j1 - 1];
			}
			IOTA0 = IOTA0 + 1;
			fRec13[1] = fRec13[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec21[1] = fRec21[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
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
			fRec27[1] = fRec27[0];
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
			fRec34[1] = fRec34[0];
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
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
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
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
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
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[1] = fRec55[0];
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
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
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
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[1] = fRec69[0];
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
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[1] = fRec76[0];
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
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[1] = fRec83[0];
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
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[1] = fRec90[0];
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

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

static const clap_plugin_descriptor_t gain_desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "org.faust.gain",
    .name = "Faust Gain",
    .vendor = "faust",
    .url = "https://faust.grame.fr",
    .manual_url = "",
    .support_url = "",
    .version = "1.0.0",
    .description = "Simple gain plugin generated from Faust",
    .features = (const char*[]) { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr }
};

class GainPlugin final : public Base {
public:
    int fNumInputs = 0;
    int fNumOutputs = 0;
    mydsp fDSP;
    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    bool fHasFlushed = false;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
    : Base(desc, host) {}

    bool init() noexcept override {
        fDSP.buildUserInterface(&fUI);
        fParamAddresses.clear();
        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            auto shortname = fUI.getParamShortname(i);
            fParamAddresses.push_back(shortname);
            float actual = fUI.getParamValue(shortname);
            fExpectedValues.push_back(actual);
        }
        return true;
    }

    bool startProcessing() noexcept override {
        return Base::startProcessing(); //set status to processing
    }

    void stopProcessing() noexcept override {
        Base::stopProcessing(); //resets status to activated
    }

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP.init(sampleRate);
        fNumInputs = fDSP.getNumInputs();
        fNumOutputs = fDSP.getNumOutputs();
        std::cerr << "[activate] Sample rate: " << sampleRate << std::endl;
        std::cerr << "[activate] Input channels: " << fNumInputs << ", Output channels: " << fNumOutputs << std::endl;
        return true;
    }


    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) {
            return false;
        }

        if (hdr->type != CLAP_EVENT_PARAM_VALUE) return false;

        const auto* evParam = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        if (evParam->param_id >= fParamAddresses.size()) return false;

        GuardedScope guard(fUI, "applyParamEventIfValid");
        fUI.setParamValue(fParamAddresses[evParam->param_id], evParam->value);
        fExpectedValues[evParam->param_id] = evParam->value;

        return true;
    }



    clap_process_status process(const clap_process_t* process) noexcept override {
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        const auto& inBuffer  = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];

        //skip processing gracefully if no audio channels are connected
        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        if (inBuffer.channel_count < fNumInputs ||
            outBuffer.channel_count < fNumOutputs) {
            std::cerr << "[error] Channel count mismatch: in="
                      << inBuffer.channel_count << ", expected="
                      << fNumInputs << " / out=" << outBuffer.channel_count
                      << ", expected=" << fNumOutputs << "\n";
            return CLAP_PROCESS_ERROR;
            }

        //apply param events
        if (auto events = process->in_events) {
            for (uint32_t i = 0, N = events->size(events); i < N; ++i) {
                applyParamEventIfValid(events->get(events, i));
            }
        }

        //prepare pointers
        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        //process audio
        GuardedScope guard(fUI, "full-buffer");
        fDSP.compute(process->frames_count, inputs, outputs);

        return CLAP_PROCESS_CONTINUE;
    }


    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override {
        return 1; //still 1 port, but could change if faust generates multiple ports
    }
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? fNumInputs : fNumOutputs;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type = nullptr;
        return true;
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= fParamAddresses.size()) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        const char* addr = fParamAddresses[index].c_str();
        if (addr[0] == '/') addr += 1;
        snprintf(info->name, sizeof(info->name), "%s", addr);
        info->min_value = 0.f;
        info->max_value = 1.f;
        info->default_value = 0.5f;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (id >= fExpectedValues.size()) return false;
        *value = fExpectedValues[id];
        return true;
    }

    bool paramsTextToValue(clap_id, const char*, double*) noexcept override { return false; }
    bool paramsValueToText(clap_id, double, char*, uint32_t) noexcept override { return false; }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;

        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!applyParamEventIfValid(hdr)) {
            }
        }
    }
    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        return GainPlugin::create(host);
    }
    return nullptr;
}
static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};
static bool entry_init(const char* path) { return true; }
static void entry_deinit() {}

extern "C" {
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}

#endif
