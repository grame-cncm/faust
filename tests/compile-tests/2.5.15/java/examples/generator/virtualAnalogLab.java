/* ------------------------------------------------------------
name: "virtualAnalogLab"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
	float mydsp_faustpower2_f(float value) {
		return (value * value);
		
	}
	float mydsp_faustpower3_f(float value) {
		return ((value * value) * value);
		
	}
	float mydsp_faustpower4_f(float value) {
		return (((value * value) * value) * value);
		
	}
	
	float fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fHslider1;
	int iVec0[] = new int[4];
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
	float fCheckbox0;
	float fHslider2;
	float fRec4[] = new float[2];
	float fCheckbox1;
	float fVslider0;
	float fHslider3;
	float fRec10[] = new float[2];
	float fVslider1;
	float fEntry0;
	float fConst14;
	float fHslider4;
	float fVslider2;
	float fRec12[] = new float[2];
	float fVec1[] = new float[2];
	float fRec11[] = new float[2];
	float fConst15;
	float fVec2[] = new float[2];
	float fConst16;
	float fVec3[] = new float[2];
	float fVec4[] = new float[2];
	float fConst17;
	float fVec5[] = new float[2];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2];
	float fVslider3;
	float fVec8[] = new float[2];
	float fRec13[] = new float[2];
	float fVec9[] = new float[2];
	float fVec10[] = new float[2];
	float fVec11[] = new float[2];
	float fVec12[] = new float[2];
	float fVec13[] = new float[2];
	float fVec14[] = new float[2];
	float fVslider4;
	float fVec15[] = new float[2];
	float fRec14[] = new float[2];
	float fVec16[] = new float[2];
	float fVec17[] = new float[2];
	float fVec18[] = new float[2];
	float fVec19[] = new float[2];
	float fVec20[] = new float[2];
	float fVec21[] = new float[2];
	float fConst18;
	float fVslider5;
	float fVec22[] = new float[2];
	float fRec15[] = new float[2];
	float fVec23[] = new float[2];
	int IOTA;
	float fVec24[] = new float[4096];
	float fConst19;
	float fVec25[] = new float[2];
	float fRec16[] = new float[2];
	float fVec26[] = new float[2];
	float fVec27[] = new float[4096];
	float fVec28[] = new float[2];
	float fRec17[] = new float[2];
	float fVec29[] = new float[2];
	float fVec30[] = new float[4096];
	float fConst20;
	float fVslider6;
	float fRec18[] = new float[2];
	float fRec19[] = new float[2];
	float fRec20[] = new float[2];
	float fVslider7;
	float fCheckbox2;
	float fVslider8;
	float fRec21[] = new float[2];
	float fConst21;
	float fVec31[] = new float[2];
	float fVec32[] = new float[2];
	float fVec33[] = new float[4096];
	float fVec34[] = new float[2];
	float fVec35[] = new float[2];
	float fVec36[] = new float[4096];
	float fVec37[] = new float[2];
	float fVec38[] = new float[2];
	float fVec39[] = new float[4096];
	float fVslider9;
	int iRec23[] = new int[2];
	float fRec22[] = new float[4];
	float fConst22;
	float fHslider5;
	float fRec24[] = new float[2];
	float fHslider6;
	float fRec9[] = new float[2];
	float fRec8[] = new float[2];
	float fRec7[] = new float[2];
	float fRec6[] = new float[2];
	float fRec5[] = new float[2];
	float fCheckbox3;
	float fConst23;
	float fRec27[] = new float[2];
	float fRec26[] = new float[3];
	float fRec25[] = new float[3];
	float fRec30[] = new float[2];
	float fRec28[] = new float[2];
	float fRec33[] = new float[2];
	float fRec31[] = new float[2];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec3[] = new float[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec2[] = new float[3];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec1[] = new float[3];
	float fConst33;
	float fRec0[] = new float[2];
	float fVbargraph0;
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
	float fRec40[] = new float[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec39[] = new float[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec38[] = new float[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec37[] = new float[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec36[] = new float[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec35[] = new float[3];
	float fConst71;
	float fRec34[] = new float[2];
	float fVbargraph1;
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
	float fRec47[] = new float[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec46[] = new float[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec45[] = new float[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fRec44[] = new float[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec43[] = new float[3];
	float fConst106;
	float fConst107;
	float fConst108;
	float fRec42[] = new float[3];
	float fConst109;
	float fRec41[] = new float[2];
	float fVbargraph2;
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
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec54[] = new float[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec53[] = new float[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec52[] = new float[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec51[] = new float[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec50[] = new float[3];
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec49[] = new float[3];
	float fConst147;
	float fRec48[] = new float[2];
	float fVbargraph3;
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
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec61[] = new float[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec60[] = new float[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec59[] = new float[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fRec58[] = new float[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec57[] = new float[3];
	float fConst182;
	float fConst183;
	float fConst184;
	float fRec56[] = new float[3];
	float fConst185;
	float fRec55[] = new float[2];
	float fVbargraph4;
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
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec68[] = new float[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec67[] = new float[3];
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec66[] = new float[3];
	float fConst213;
	float fConst214;
	float fConst215;
	float fConst216;
	float fRec65[] = new float[3];
	float fConst217;
	float fConst218;
	float fConst219;
	float fRec64[] = new float[3];
	float fConst220;
	float fConst221;
	float fConst222;
	float fRec63[] = new float[3];
	float fConst223;
	float fRec62[] = new float[2];
	float fVbargraph5;
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
	float fConst243;
	float fConst244;
	float fRec75[] = new float[3];
	float fConst245;
	float fConst246;
	float fConst247;
	float fRec74[] = new float[3];
	float fConst248;
	float fConst249;
	float fConst250;
	float fRec73[] = new float[3];
	float fConst251;
	float fConst252;
	float fConst253;
	float fConst254;
	float fRec72[] = new float[3];
	float fConst255;
	float fConst256;
	float fConst257;
	float fRec71[] = new float[3];
	float fConst258;
	float fConst259;
	float fConst260;
	float fRec70[] = new float[3];
	float fConst261;
	float fRec69[] = new float[2];
	float fVbargraph6;
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
	float fConst281;
	float fConst282;
	float fRec82[] = new float[3];
	float fConst283;
	float fConst284;
	float fConst285;
	float fRec81[] = new float[3];
	float fConst286;
	float fConst287;
	float fConst288;
	float fRec80[] = new float[3];
	float fConst289;
	float fConst290;
	float fConst291;
	float fConst292;
	float fRec79[] = new float[3];
	float fConst293;
	float fConst294;
	float fConst295;
	float fRec78[] = new float[3];
	float fConst296;
	float fConst297;
	float fConst298;
	float fRec77[] = new float[3];
	float fConst299;
	float fRec76[] = new float[2];
	float fVbargraph7;
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
	float fConst319;
	float fConst320;
	float fRec89[] = new float[3];
	float fConst321;
	float fConst322;
	float fConst323;
	float fRec88[] = new float[3];
	float fConst324;
	float fConst325;
	float fConst326;
	float fRec87[] = new float[3];
	float fConst327;
	float fConst328;
	float fConst329;
	float fConst330;
	float fRec86[] = new float[3];
	float fConst331;
	float fConst332;
	float fConst333;
	float fRec85[] = new float[3];
	float fConst334;
	float fConst335;
	float fConst336;
	float fRec84[] = new float[3];
	float fConst337;
	float fRec83[] = new float[2];
	float fVbargraph8;
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
	float fConst357;
	float fConst358;
	float fRec96[] = new float[3];
	float fConst359;
	float fConst360;
	float fConst361;
	float fRec95[] = new float[3];
	float fConst362;
	float fConst363;
	float fConst364;
	float fRec94[] = new float[3];
	float fConst365;
	float fConst366;
	float fConst367;
	float fConst368;
	float fRec93[] = new float[3];
	float fConst369;
	float fConst370;
	float fConst371;
	float fRec92[] = new float[3];
	float fConst372;
	float fConst373;
	float fConst374;
	float fRec91[] = new float[3];
	float fConst375;
	float fRec90[] = new float[2];
	float fVbargraph9;
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
	float fConst395;
	float fConst396;
	float fRec103[] = new float[3];
	float fConst397;
	float fConst398;
	float fConst399;
	float fRec102[] = new float[3];
	float fConst400;
	float fConst401;
	float fConst402;
	float fRec101[] = new float[3];
	float fConst403;
	float fConst404;
	float fConst405;
	float fConst406;
	float fRec100[] = new float[3];
	float fConst407;
	float fConst408;
	float fConst409;
	float fRec99[] = new float[3];
	float fConst410;
	float fConst411;
	float fConst412;
	float fRec98[] = new float[3];
	float fConst413;
	float fRec97[] = new float[2];
	float fVbargraph10;
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
	float fConst433;
	float fConst434;
	float fRec110[] = new float[3];
	float fConst435;
	float fConst436;
	float fConst437;
	float fRec109[] = new float[3];
	float fConst438;
	float fConst439;
	float fConst440;
	float fRec108[] = new float[3];
	float fConst441;
	float fConst442;
	float fConst443;
	float fConst444;
	float fRec107[] = new float[3];
	float fConst445;
	float fConst446;
	float fConst447;
	float fRec106[] = new float[3];
	float fConst448;
	float fConst449;
	float fConst450;
	float fRec105[] = new float[3];
	float fConst451;
	float fRec104[] = new float[2];
	float fVbargraph11;
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
	float fConst471;
	float fConst472;
	float fRec117[] = new float[3];
	float fConst473;
	float fConst474;
	float fConst475;
	float fRec116[] = new float[3];
	float fConst476;
	float fConst477;
	float fConst478;
	float fRec115[] = new float[3];
	float fConst479;
	float fConst480;
	float fConst481;
	float fConst482;
	float fRec114[] = new float[3];
	float fConst483;
	float fConst484;
	float fConst485;
	float fRec113[] = new float[3];
	float fConst486;
	float fConst487;
	float fConst488;
	float fRec112[] = new float[3];
	float fConst489;
	float fRec111[] = new float[2];
	float fVbargraph12;
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
	float fConst509;
	float fConst510;
	float fRec124[] = new float[3];
	float fConst511;
	float fConst512;
	float fConst513;
	float fRec123[] = new float[3];
	float fConst514;
	float fConst515;
	float fConst516;
	float fRec122[] = new float[3];
	float fConst517;
	float fConst518;
	float fConst519;
	float fConst520;
	float fRec121[] = new float[3];
	float fConst521;
	float fConst522;
	float fConst523;
	float fRec120[] = new float[3];
	float fConst524;
	float fConst525;
	float fConst526;
	float fRec119[] = new float[3];
	float fConst527;
	float fRec118[] = new float[2];
	float fVbargraph13;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fConst535;
	float fConst536;
	float fRec128[] = new float[3];
	float fConst537;
	float fConst538;
	float fConst539;
	float fRec127[] = new float[3];
	float fConst540;
	float fConst541;
	float fConst542;
	float fRec126[] = new float[3];
	float fConst543;
	float fRec125[] = new float[2];
	float fVbargraph14;
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "virtualAnalogLab");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m.declare("vaeffects.lib/version", "0.0");
	}

	int getNumInputs() {
		return 1;
		
	}
	int getNumOutputs() {
		return 2;
		
	}
	int getInputRate(int channel) {
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
	int getOutputRate(int channel) {
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
	
	public void classInit(int samplingFreq) {
		
	}
	
	public void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (float)java.lang.Math.min(192000.0f, (float)java.lang.Math.max(1.0f, (float)fSamplingFreq));
		fConst1 = (1000.0f / fConst0);
		fConst2 = (float)java.lang.Math.tan((50265.4844f / fConst0));
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
		fConst14 = (1.0f / fConst0);
		fConst15 = (0.25f * fConst0);
		fConst16 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst17 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst18 = (0.0833333358f * fConst0);
		fConst19 = (0.5f * fConst0);
		fConst20 = (1.33333337f / fConst0);
		fConst21 = (0.013888889f * fConst0);
		fConst22 = (6.28318548f / fConst0);
		fConst23 = (3.14159274f / fConst0);
		fConst24 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst25 = (1.0f / fConst5);
		fConst26 = (2.0f * (4.07678175f - fConst25));
		fConst27 = (fConst12 + 0.000407678192f);
		fConst28 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst29 = (2.0f * (1.4500711f - fConst25));
		fConst30 = (fConst9 + 1.4500711f);
		fConst31 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst32 = (2.0f * (0.935140193f - fConst25));
		fConst33 = (fConst6 + 0.935140193f);
		fConst34 = (float)java.lang.Math.tan((31665.2695f / fConst0));
		fConst35 = (1.0f / fConst34);
		fConst36 = (1.0f / (((fConst35 + 0.157482162f) / fConst34) + 0.935140193f));
		fConst37 = mydsp_faustpower2_f(fConst34);
		fConst38 = (50.0638084f / fConst37);
		fConst39 = (2.0f * (0.935140193f - fConst38));
		fConst40 = (1.0f / (((fConst35 + 0.743130445f) / fConst34) + 1.4500711f));
		fConst41 = (11.0520525f / fConst37);
		fConst42 = (2.0f * (1.4500711f - fConst41));
		fConst43 = (1.0f / (((fConst35 + 3.18972731f) / fConst34) + 4.07678175f));
		fConst44 = (0.00176617282f / fConst37);
		fConst45 = (2.0f * (0.000407678192f - fConst44));
		fConst46 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst47 = (2.0f * (53.5361519f - fConst25));
		fConst48 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst49 = (2.0f * (7.62173128f - fConst25));
		fConst50 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst51 = (9.99999975e-05f / fConst5);
		fConst52 = (2.0f * (0.000433227193f - fConst51));
		fConst53 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst54 = (2.0f * (0.245291501f - fConst25));
		fConst55 = (fConst51 + 0.000433227193f);
		fConst56 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst57 = (2.0f * (0.689621389f - fConst25));
		fConst58 = (fConst25 + 7.62173128f);
		fConst59 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst60 = (2.0f * (1.06935835f - fConst25));
		fConst61 = (fConst25 + 53.5361519f);
		fConst62 = (((fConst35 + -3.18972731f) / fConst34) + 4.07678175f);
		fConst63 = (1.0f / fConst37);
		fConst64 = (2.0f * (4.07678175f - fConst63));
		fConst65 = (fConst44 + 0.000407678192f);
		fConst66 = (((fConst35 + -0.743130445f) / fConst34) + 1.4500711f);
		fConst67 = (2.0f * (1.4500711f - fConst63));
		fConst68 = (fConst41 + 1.4500711f);
		fConst69 = (((fConst35 + -0.157482162f) / fConst34) + 0.935140193f);
		fConst70 = (2.0f * (0.935140193f - fConst63));
		fConst71 = (fConst38 + 0.935140193f);
		fConst72 = (float)java.lang.Math.tan((19947.8691f / fConst0));
		fConst73 = (1.0f / fConst72);
		fConst74 = (1.0f / (((fConst73 + 0.157482162f) / fConst72) + 0.935140193f));
		fConst75 = mydsp_faustpower2_f(fConst72);
		fConst76 = (50.0638084f / fConst75);
		fConst77 = (2.0f * (0.935140193f - fConst76));
		fConst78 = (1.0f / (((fConst73 + 0.743130445f) / fConst72) + 1.4500711f));
		fConst79 = (11.0520525f / fConst75);
		fConst80 = (2.0f * (1.4500711f - fConst79));
		fConst81 = (1.0f / (((fConst73 + 3.18972731f) / fConst72) + 4.07678175f));
		fConst82 = (0.00176617282f / fConst75);
		fConst83 = (2.0f * (0.000407678192f - fConst82));
		fConst84 = (1.0f / (((fConst35 + 0.168404877f) / fConst34) + 1.06935835f));
		fConst85 = (2.0f * (53.5361519f - fConst63));
		fConst86 = (1.0f / (((fConst35 + 0.51247865f) / fConst34) + 0.689621389f));
		fConst87 = (2.0f * (7.62173128f - fConst63));
		fConst88 = (1.0f / (((fConst35 + 0.782413065f) / fConst34) + 0.245291501f));
		fConst89 = (9.99999975e-05f / fConst37);
		fConst90 = (2.0f * (0.000433227193f - fConst89));
		fConst91 = (((fConst35 + -0.782413065f) / fConst34) + 0.245291501f);
		fConst92 = (2.0f * (0.245291501f - fConst63));
		fConst93 = (fConst89 + 0.000433227193f);
		fConst94 = (((fConst35 + -0.51247865f) / fConst34) + 0.689621389f);
		fConst95 = (2.0f * (0.689621389f - fConst63));
		fConst96 = (fConst63 + 7.62173128f);
		fConst97 = (((fConst35 + -0.168404877f) / fConst34) + 1.06935835f);
		fConst98 = (2.0f * (1.06935835f - fConst63));
		fConst99 = (fConst63 + 53.5361519f);
		fConst100 = (((fConst73 + -3.18972731f) / fConst72) + 4.07678175f);
		fConst101 = (1.0f / fConst75);
		fConst102 = (2.0f * (4.07678175f - fConst101));
		fConst103 = (fConst82 + 0.000407678192f);
		fConst104 = (((fConst73 + -0.743130445f) / fConst72) + 1.4500711f);
		fConst105 = (2.0f * (1.4500711f - fConst101));
		fConst106 = (fConst79 + 1.4500711f);
		fConst107 = (((fConst73 + -0.157482162f) / fConst72) + 0.935140193f);
		fConst108 = (2.0f * (0.935140193f - fConst101));
		fConst109 = (fConst76 + 0.935140193f);
		fConst110 = (float)java.lang.Math.tan((12566.3711f / fConst0));
		fConst111 = (1.0f / fConst110);
		fConst112 = (1.0f / (((fConst111 + 0.157482162f) / fConst110) + 0.935140193f));
		fConst113 = mydsp_faustpower2_f(fConst110);
		fConst114 = (50.0638084f / fConst113);
		fConst115 = (2.0f * (0.935140193f - fConst114));
		fConst116 = (1.0f / (((fConst111 + 0.743130445f) / fConst110) + 1.4500711f));
		fConst117 = (11.0520525f / fConst113);
		fConst118 = (2.0f * (1.4500711f - fConst117));
		fConst119 = (1.0f / (((fConst111 + 3.18972731f) / fConst110) + 4.07678175f));
		fConst120 = (0.00176617282f / fConst113);
		fConst121 = (2.0f * (0.000407678192f - fConst120));
		fConst122 = (1.0f / (((fConst73 + 0.168404877f) / fConst72) + 1.06935835f));
		fConst123 = (2.0f * (53.5361519f - fConst101));
		fConst124 = (1.0f / (((fConst73 + 0.51247865f) / fConst72) + 0.689621389f));
		fConst125 = (2.0f * (7.62173128f - fConst101));
		fConst126 = (1.0f / (((fConst73 + 0.782413065f) / fConst72) + 0.245291501f));
		fConst127 = (9.99999975e-05f / fConst75);
		fConst128 = (2.0f * (0.000433227193f - fConst127));
		fConst129 = (((fConst73 + -0.782413065f) / fConst72) + 0.245291501f);
		fConst130 = (2.0f * (0.245291501f - fConst101));
		fConst131 = (fConst127 + 0.000433227193f);
		fConst132 = (((fConst73 + -0.51247865f) / fConst72) + 0.689621389f);
		fConst133 = (2.0f * (0.689621389f - fConst101));
		fConst134 = (fConst101 + 7.62173128f);
		fConst135 = (((fConst73 + -0.168404877f) / fConst72) + 1.06935835f);
		fConst136 = (2.0f * (1.06935835f - fConst101));
		fConst137 = (fConst101 + 53.5361519f);
		fConst138 = (((fConst111 + -3.18972731f) / fConst110) + 4.07678175f);
		fConst139 = (1.0f / fConst113);
		fConst140 = (2.0f * (4.07678175f - fConst139));
		fConst141 = (fConst120 + 0.000407678192f);
		fConst142 = (((fConst111 + -0.743130445f) / fConst110) + 1.4500711f);
		fConst143 = (2.0f * (1.4500711f - fConst139));
		fConst144 = (fConst117 + 1.4500711f);
		fConst145 = (((fConst111 + -0.157482162f) / fConst110) + 0.935140193f);
		fConst146 = (2.0f * (0.935140193f - fConst139));
		fConst147 = (fConst114 + 0.935140193f);
		fConst148 = (float)java.lang.Math.tan((7916.31738f / fConst0));
		fConst149 = (1.0f / fConst148);
		fConst150 = (1.0f / (((fConst149 + 0.157482162f) / fConst148) + 0.935140193f));
		fConst151 = mydsp_faustpower2_f(fConst148);
		fConst152 = (50.0638084f / fConst151);
		fConst153 = (2.0f * (0.935140193f - fConst152));
		fConst154 = (1.0f / (((fConst149 + 0.743130445f) / fConst148) + 1.4500711f));
		fConst155 = (11.0520525f / fConst151);
		fConst156 = (2.0f * (1.4500711f - fConst155));
		fConst157 = (1.0f / (((fConst149 + 3.18972731f) / fConst148) + 4.07678175f));
		fConst158 = (0.00176617282f / fConst151);
		fConst159 = (2.0f * (0.000407678192f - fConst158));
		fConst160 = (1.0f / (((fConst111 + 0.168404877f) / fConst110) + 1.06935835f));
		fConst161 = (2.0f * (53.5361519f - fConst139));
		fConst162 = (1.0f / (((fConst111 + 0.51247865f) / fConst110) + 0.689621389f));
		fConst163 = (2.0f * (7.62173128f - fConst139));
		fConst164 = (1.0f / (((fConst111 + 0.782413065f) / fConst110) + 0.245291501f));
		fConst165 = (9.99999975e-05f / fConst113);
		fConst166 = (2.0f * (0.000433227193f - fConst165));
		fConst167 = (((fConst111 + -0.782413065f) / fConst110) + 0.245291501f);
		fConst168 = (2.0f * (0.245291501f - fConst139));
		fConst169 = (fConst165 + 0.000433227193f);
		fConst170 = (((fConst111 + -0.51247865f) / fConst110) + 0.689621389f);
		fConst171 = (2.0f * (0.689621389f - fConst139));
		fConst172 = (fConst139 + 7.62173128f);
		fConst173 = (((fConst111 + -0.168404877f) / fConst110) + 1.06935835f);
		fConst174 = (2.0f * (1.06935835f - fConst139));
		fConst175 = (fConst139 + 53.5361519f);
		fConst176 = (((fConst149 + -3.18972731f) / fConst148) + 4.07678175f);
		fConst177 = (1.0f / fConst151);
		fConst178 = (2.0f * (4.07678175f - fConst177));
		fConst179 = (fConst158 + 0.000407678192f);
		fConst180 = (((fConst149 + -0.743130445f) / fConst148) + 1.4500711f);
		fConst181 = (2.0f * (1.4500711f - fConst177));
		fConst182 = (fConst155 + 1.4500711f);
		fConst183 = (((fConst149 + -0.157482162f) / fConst148) + 0.935140193f);
		fConst184 = (2.0f * (0.935140193f - fConst177));
		fConst185 = (fConst152 + 0.935140193f);
		fConst186 = (float)java.lang.Math.tan((4986.96729f / fConst0));
		fConst187 = (1.0f / fConst186);
		fConst188 = (1.0f / (((fConst187 + 0.157482162f) / fConst186) + 0.935140193f));
		fConst189 = mydsp_faustpower2_f(fConst186);
		fConst190 = (50.0638084f / fConst189);
		fConst191 = (2.0f * (0.935140193f - fConst190));
		fConst192 = (1.0f / (((fConst187 + 0.743130445f) / fConst186) + 1.4500711f));
		fConst193 = (11.0520525f / fConst189);
		fConst194 = (2.0f * (1.4500711f - fConst193));
		fConst195 = (1.0f / (((fConst187 + 3.18972731f) / fConst186) + 4.07678175f));
		fConst196 = (0.00176617282f / fConst189);
		fConst197 = (2.0f * (0.000407678192f - fConst196));
		fConst198 = (1.0f / (((fConst149 + 0.168404877f) / fConst148) + 1.06935835f));
		fConst199 = (2.0f * (53.5361519f - fConst177));
		fConst200 = (1.0f / (((fConst149 + 0.51247865f) / fConst148) + 0.689621389f));
		fConst201 = (2.0f * (7.62173128f - fConst177));
		fConst202 = (1.0f / (((fConst149 + 0.782413065f) / fConst148) + 0.245291501f));
		fConst203 = (9.99999975e-05f / fConst151);
		fConst204 = (2.0f * (0.000433227193f - fConst203));
		fConst205 = (((fConst149 + -0.782413065f) / fConst148) + 0.245291501f);
		fConst206 = (2.0f * (0.245291501f - fConst177));
		fConst207 = (fConst203 + 0.000433227193f);
		fConst208 = (((fConst149 + -0.51247865f) / fConst148) + 0.689621389f);
		fConst209 = (2.0f * (0.689621389f - fConst177));
		fConst210 = (fConst177 + 7.62173128f);
		fConst211 = (((fConst149 + -0.168404877f) / fConst148) + 1.06935835f);
		fConst212 = (2.0f * (1.06935835f - fConst177));
		fConst213 = (fConst177 + 53.5361519f);
		fConst214 = (((fConst187 + -3.18972731f) / fConst186) + 4.07678175f);
		fConst215 = (1.0f / fConst189);
		fConst216 = (2.0f * (4.07678175f - fConst215));
		fConst217 = (fConst196 + 0.000407678192f);
		fConst218 = (((fConst187 + -0.743130445f) / fConst186) + 1.4500711f);
		fConst219 = (2.0f * (1.4500711f - fConst215));
		fConst220 = (fConst193 + 1.4500711f);
		fConst221 = (((fConst187 + -0.157482162f) / fConst186) + 0.935140193f);
		fConst222 = (2.0f * (0.935140193f - fConst215));
		fConst223 = (fConst190 + 0.935140193f);
		fConst224 = (float)java.lang.Math.tan((3141.59277f / fConst0));
		fConst225 = (1.0f / fConst224);
		fConst226 = (1.0f / (((fConst225 + 0.157482162f) / fConst224) + 0.935140193f));
		fConst227 = mydsp_faustpower2_f(fConst224);
		fConst228 = (50.0638084f / fConst227);
		fConst229 = (2.0f * (0.935140193f - fConst228));
		fConst230 = (1.0f / (((fConst225 + 0.743130445f) / fConst224) + 1.4500711f));
		fConst231 = (11.0520525f / fConst227);
		fConst232 = (2.0f * (1.4500711f - fConst231));
		fConst233 = (1.0f / (((fConst225 + 3.18972731f) / fConst224) + 4.07678175f));
		fConst234 = (0.00176617282f / fConst227);
		fConst235 = (2.0f * (0.000407678192f - fConst234));
		fConst236 = (1.0f / (((fConst187 + 0.168404877f) / fConst186) + 1.06935835f));
		fConst237 = (2.0f * (53.5361519f - fConst215));
		fConst238 = (1.0f / (((fConst187 + 0.51247865f) / fConst186) + 0.689621389f));
		fConst239 = (2.0f * (7.62173128f - fConst215));
		fConst240 = (1.0f / (((fConst187 + 0.782413065f) / fConst186) + 0.245291501f));
		fConst241 = (9.99999975e-05f / fConst189);
		fConst242 = (2.0f * (0.000433227193f - fConst241));
		fConst243 = (((fConst187 + -0.782413065f) / fConst186) + 0.245291501f);
		fConst244 = (2.0f * (0.245291501f - fConst215));
		fConst245 = (fConst241 + 0.000433227193f);
		fConst246 = (((fConst187 + -0.51247865f) / fConst186) + 0.689621389f);
		fConst247 = (2.0f * (0.689621389f - fConst215));
		fConst248 = (fConst215 + 7.62173128f);
		fConst249 = (((fConst187 + -0.168404877f) / fConst186) + 1.06935835f);
		fConst250 = (2.0f * (1.06935835f - fConst215));
		fConst251 = (fConst215 + 53.5361519f);
		fConst252 = (((fConst225 + -3.18972731f) / fConst224) + 4.07678175f);
		fConst253 = (1.0f / fConst227);
		fConst254 = (2.0f * (4.07678175f - fConst253));
		fConst255 = (fConst234 + 0.000407678192f);
		fConst256 = (((fConst225 + -0.743130445f) / fConst224) + 1.4500711f);
		fConst257 = (2.0f * (1.4500711f - fConst253));
		fConst258 = (fConst231 + 1.4500711f);
		fConst259 = (((fConst225 + -0.157482162f) / fConst224) + 0.935140193f);
		fConst260 = (2.0f * (0.935140193f - fConst253));
		fConst261 = (fConst228 + 0.935140193f);
		fConst262 = (float)java.lang.Math.tan((1979.07935f / fConst0));
		fConst263 = (1.0f / fConst262);
		fConst264 = (1.0f / (((fConst263 + 0.157482162f) / fConst262) + 0.935140193f));
		fConst265 = mydsp_faustpower2_f(fConst262);
		fConst266 = (50.0638084f / fConst265);
		fConst267 = (2.0f * (0.935140193f - fConst266));
		fConst268 = (1.0f / (((fConst263 + 0.743130445f) / fConst262) + 1.4500711f));
		fConst269 = (11.0520525f / fConst265);
		fConst270 = (2.0f * (1.4500711f - fConst269));
		fConst271 = (1.0f / (((fConst263 + 3.18972731f) / fConst262) + 4.07678175f));
		fConst272 = (0.00176617282f / fConst265);
		fConst273 = (2.0f * (0.000407678192f - fConst272));
		fConst274 = (1.0f / (((fConst225 + 0.168404877f) / fConst224) + 1.06935835f));
		fConst275 = (2.0f * (53.5361519f - fConst253));
		fConst276 = (1.0f / (((fConst225 + 0.51247865f) / fConst224) + 0.689621389f));
		fConst277 = (2.0f * (7.62173128f - fConst253));
		fConst278 = (1.0f / (((fConst225 + 0.782413065f) / fConst224) + 0.245291501f));
		fConst279 = (9.99999975e-05f / fConst227);
		fConst280 = (2.0f * (0.000433227193f - fConst279));
		fConst281 = (((fConst225 + -0.782413065f) / fConst224) + 0.245291501f);
		fConst282 = (2.0f * (0.245291501f - fConst253));
		fConst283 = (fConst279 + 0.000433227193f);
		fConst284 = (((fConst225 + -0.51247865f) / fConst224) + 0.689621389f);
		fConst285 = (2.0f * (0.689621389f - fConst253));
		fConst286 = (fConst253 + 7.62173128f);
		fConst287 = (((fConst225 + -0.168404877f) / fConst224) + 1.06935835f);
		fConst288 = (2.0f * (1.06935835f - fConst253));
		fConst289 = (fConst253 + 53.5361519f);
		fConst290 = (((fConst263 + -3.18972731f) / fConst262) + 4.07678175f);
		fConst291 = (1.0f / fConst265);
		fConst292 = (2.0f * (4.07678175f - fConst291));
		fConst293 = (fConst272 + 0.000407678192f);
		fConst294 = (((fConst263 + -0.743130445f) / fConst262) + 1.4500711f);
		fConst295 = (2.0f * (1.4500711f - fConst291));
		fConst296 = (fConst269 + 1.4500711f);
		fConst297 = (((fConst263 + -0.157482162f) / fConst262) + 0.935140193f);
		fConst298 = (2.0f * (0.935140193f - fConst291));
		fConst299 = (fConst266 + 0.935140193f);
		fConst300 = (float)java.lang.Math.tan((1246.74182f / fConst0));
		fConst301 = (1.0f / fConst300);
		fConst302 = (1.0f / (((fConst301 + 0.157482162f) / fConst300) + 0.935140193f));
		fConst303 = mydsp_faustpower2_f(fConst300);
		fConst304 = (50.0638084f / fConst303);
		fConst305 = (2.0f * (0.935140193f - fConst304));
		fConst306 = (1.0f / (((fConst301 + 0.743130445f) / fConst300) + 1.4500711f));
		fConst307 = (11.0520525f / fConst303);
		fConst308 = (2.0f * (1.4500711f - fConst307));
		fConst309 = (1.0f / (((fConst301 + 3.18972731f) / fConst300) + 4.07678175f));
		fConst310 = (0.00176617282f / fConst303);
		fConst311 = (2.0f * (0.000407678192f - fConst310));
		fConst312 = (1.0f / (((fConst263 + 0.168404877f) / fConst262) + 1.06935835f));
		fConst313 = (2.0f * (53.5361519f - fConst291));
		fConst314 = (1.0f / (((fConst263 + 0.51247865f) / fConst262) + 0.689621389f));
		fConst315 = (2.0f * (7.62173128f - fConst291));
		fConst316 = (1.0f / (((fConst263 + 0.782413065f) / fConst262) + 0.245291501f));
		fConst317 = (9.99999975e-05f / fConst265);
		fConst318 = (2.0f * (0.000433227193f - fConst317));
		fConst319 = (((fConst263 + -0.782413065f) / fConst262) + 0.245291501f);
		fConst320 = (2.0f * (0.245291501f - fConst291));
		fConst321 = (fConst317 + 0.000433227193f);
		fConst322 = (((fConst263 + -0.51247865f) / fConst262) + 0.689621389f);
		fConst323 = (2.0f * (0.689621389f - fConst291));
		fConst324 = (fConst291 + 7.62173128f);
		fConst325 = (((fConst263 + -0.168404877f) / fConst262) + 1.06935835f);
		fConst326 = (2.0f * (1.06935835f - fConst291));
		fConst327 = (fConst291 + 53.5361519f);
		fConst328 = (((fConst301 + -3.18972731f) / fConst300) + 4.07678175f);
		fConst329 = (1.0f / fConst303);
		fConst330 = (2.0f * (4.07678175f - fConst329));
		fConst331 = (fConst310 + 0.000407678192f);
		fConst332 = (((fConst301 + -0.743130445f) / fConst300) + 1.4500711f);
		fConst333 = (2.0f * (1.4500711f - fConst329));
		fConst334 = (fConst307 + 1.4500711f);
		fConst335 = (((fConst301 + -0.157482162f) / fConst300) + 0.935140193f);
		fConst336 = (2.0f * (0.935140193f - fConst329));
		fConst337 = (fConst304 + 0.935140193f);
		fConst338 = (float)java.lang.Math.tan((785.398193f / fConst0));
		fConst339 = (1.0f / fConst338);
		fConst340 = (1.0f / (((fConst339 + 0.157482162f) / fConst338) + 0.935140193f));
		fConst341 = mydsp_faustpower2_f(fConst338);
		fConst342 = (50.0638084f / fConst341);
		fConst343 = (2.0f * (0.935140193f - fConst342));
		fConst344 = (1.0f / (((fConst339 + 0.743130445f) / fConst338) + 1.4500711f));
		fConst345 = (11.0520525f / fConst341);
		fConst346 = (2.0f * (1.4500711f - fConst345));
		fConst347 = (1.0f / (((fConst339 + 3.18972731f) / fConst338) + 4.07678175f));
		fConst348 = (0.00176617282f / fConst341);
		fConst349 = (2.0f * (0.000407678192f - fConst348));
		fConst350 = (1.0f / (((fConst301 + 0.168404877f) / fConst300) + 1.06935835f));
		fConst351 = (2.0f * (53.5361519f - fConst329));
		fConst352 = (1.0f / (((fConst301 + 0.51247865f) / fConst300) + 0.689621389f));
		fConst353 = (2.0f * (7.62173128f - fConst329));
		fConst354 = (1.0f / (((fConst301 + 0.782413065f) / fConst300) + 0.245291501f));
		fConst355 = (9.99999975e-05f / fConst303);
		fConst356 = (2.0f * (0.000433227193f - fConst355));
		fConst357 = (((fConst301 + -0.782413065f) / fConst300) + 0.245291501f);
		fConst358 = (2.0f * (0.245291501f - fConst329));
		fConst359 = (fConst355 + 0.000433227193f);
		fConst360 = (((fConst301 + -0.51247865f) / fConst300) + 0.689621389f);
		fConst361 = (2.0f * (0.689621389f - fConst329));
		fConst362 = (fConst329 + 7.62173128f);
		fConst363 = (((fConst301 + -0.168404877f) / fConst300) + 1.06935835f);
		fConst364 = (2.0f * (1.06935835f - fConst329));
		fConst365 = (fConst329 + 53.5361519f);
		fConst366 = (((fConst339 + -3.18972731f) / fConst338) + 4.07678175f);
		fConst367 = (1.0f / fConst341);
		fConst368 = (2.0f * (4.07678175f - fConst367));
		fConst369 = (fConst348 + 0.000407678192f);
		fConst370 = (((fConst339 + -0.743130445f) / fConst338) + 1.4500711f);
		fConst371 = (2.0f * (1.4500711f - fConst367));
		fConst372 = (fConst345 + 1.4500711f);
		fConst373 = (((fConst339 + -0.157482162f) / fConst338) + 0.935140193f);
		fConst374 = (2.0f * (0.935140193f - fConst367));
		fConst375 = (fConst342 + 0.935140193f);
		fConst376 = (float)java.lang.Math.tan((494.769836f / fConst0));
		fConst377 = (1.0f / fConst376);
		fConst378 = (1.0f / (((fConst377 + 0.157482162f) / fConst376) + 0.935140193f));
		fConst379 = mydsp_faustpower2_f(fConst376);
		fConst380 = (50.0638084f / fConst379);
		fConst381 = (2.0f * (0.935140193f - fConst380));
		fConst382 = (1.0f / (((fConst377 + 0.743130445f) / fConst376) + 1.4500711f));
		fConst383 = (11.0520525f / fConst379);
		fConst384 = (2.0f * (1.4500711f - fConst383));
		fConst385 = (1.0f / (((fConst377 + 3.18972731f) / fConst376) + 4.07678175f));
		fConst386 = (0.00176617282f / fConst379);
		fConst387 = (2.0f * (0.000407678192f - fConst386));
		fConst388 = (1.0f / (((fConst339 + 0.168404877f) / fConst338) + 1.06935835f));
		fConst389 = (2.0f * (53.5361519f - fConst367));
		fConst390 = (1.0f / (((fConst339 + 0.51247865f) / fConst338) + 0.689621389f));
		fConst391 = (2.0f * (7.62173128f - fConst367));
		fConst392 = (1.0f / (((fConst339 + 0.782413065f) / fConst338) + 0.245291501f));
		fConst393 = (9.99999975e-05f / fConst341);
		fConst394 = (2.0f * (0.000433227193f - fConst393));
		fConst395 = (((fConst339 + -0.782413065f) / fConst338) + 0.245291501f);
		fConst396 = (2.0f * (0.245291501f - fConst367));
		fConst397 = (fConst393 + 0.000433227193f);
		fConst398 = (((fConst339 + -0.51247865f) / fConst338) + 0.689621389f);
		fConst399 = (2.0f * (0.689621389f - fConst367));
		fConst400 = (fConst367 + 7.62173128f);
		fConst401 = (((fConst339 + -0.168404877f) / fConst338) + 1.06935835f);
		fConst402 = (2.0f * (1.06935835f - fConst367));
		fConst403 = (fConst367 + 53.5361519f);
		fConst404 = (((fConst377 + -3.18972731f) / fConst376) + 4.07678175f);
		fConst405 = (1.0f / fConst379);
		fConst406 = (2.0f * (4.07678175f - fConst405));
		fConst407 = (fConst386 + 0.000407678192f);
		fConst408 = (((fConst377 + -0.743130445f) / fConst376) + 1.4500711f);
		fConst409 = (2.0f * (1.4500711f - fConst405));
		fConst410 = (fConst383 + 1.4500711f);
		fConst411 = (((fConst377 + -0.157482162f) / fConst376) + 0.935140193f);
		fConst412 = (2.0f * (0.935140193f - fConst405));
		fConst413 = (fConst380 + 0.935140193f);
		fConst414 = (float)java.lang.Math.tan((311.685455f / fConst0));
		fConst415 = (1.0f / fConst414);
		fConst416 = (1.0f / (((fConst415 + 0.157482162f) / fConst414) + 0.935140193f));
		fConst417 = mydsp_faustpower2_f(fConst414);
		fConst418 = (50.0638084f / fConst417);
		fConst419 = (2.0f * (0.935140193f - fConst418));
		fConst420 = (1.0f / (((fConst415 + 0.743130445f) / fConst414) + 1.4500711f));
		fConst421 = (11.0520525f / fConst417);
		fConst422 = (2.0f * (1.4500711f - fConst421));
		fConst423 = (1.0f / (((fConst415 + 3.18972731f) / fConst414) + 4.07678175f));
		fConst424 = (0.00176617282f / fConst417);
		fConst425 = (2.0f * (0.000407678192f - fConst424));
		fConst426 = (1.0f / (((fConst377 + 0.168404877f) / fConst376) + 1.06935835f));
		fConst427 = (2.0f * (53.5361519f - fConst405));
		fConst428 = (1.0f / (((fConst377 + 0.51247865f) / fConst376) + 0.689621389f));
		fConst429 = (2.0f * (7.62173128f - fConst405));
		fConst430 = (1.0f / (((fConst377 + 0.782413065f) / fConst376) + 0.245291501f));
		fConst431 = (9.99999975e-05f / fConst379);
		fConst432 = (2.0f * (0.000433227193f - fConst431));
		fConst433 = (((fConst377 + -0.782413065f) / fConst376) + 0.245291501f);
		fConst434 = (2.0f * (0.245291501f - fConst405));
		fConst435 = (fConst431 + 0.000433227193f);
		fConst436 = (((fConst377 + -0.51247865f) / fConst376) + 0.689621389f);
		fConst437 = (2.0f * (0.689621389f - fConst405));
		fConst438 = (fConst405 + 7.62173128f);
		fConst439 = (((fConst377 + -0.168404877f) / fConst376) + 1.06935835f);
		fConst440 = (2.0f * (1.06935835f - fConst405));
		fConst441 = (fConst405 + 53.5361519f);
		fConst442 = (((fConst415 + -3.18972731f) / fConst414) + 4.07678175f);
		fConst443 = (1.0f / fConst417);
		fConst444 = (2.0f * (4.07678175f - fConst443));
		fConst445 = (fConst424 + 0.000407678192f);
		fConst446 = (((fConst415 + -0.743130445f) / fConst414) + 1.4500711f);
		fConst447 = (2.0f * (1.4500711f - fConst443));
		fConst448 = (fConst421 + 1.4500711f);
		fConst449 = (((fConst415 + -0.157482162f) / fConst414) + 0.935140193f);
		fConst450 = (2.0f * (0.935140193f - fConst443));
		fConst451 = (fConst418 + 0.935140193f);
		fConst452 = (float)java.lang.Math.tan((196.349548f / fConst0));
		fConst453 = (1.0f / fConst452);
		fConst454 = (1.0f / (((fConst453 + 0.157482162f) / fConst452) + 0.935140193f));
		fConst455 = mydsp_faustpower2_f(fConst452);
		fConst456 = (50.0638084f / fConst455);
		fConst457 = (2.0f * (0.935140193f - fConst456));
		fConst458 = (1.0f / (((fConst453 + 0.743130445f) / fConst452) + 1.4500711f));
		fConst459 = (11.0520525f / fConst455);
		fConst460 = (2.0f * (1.4500711f - fConst459));
		fConst461 = (1.0f / (((fConst453 + 3.18972731f) / fConst452) + 4.07678175f));
		fConst462 = (0.00176617282f / fConst455);
		fConst463 = (2.0f * (0.000407678192f - fConst462));
		fConst464 = (1.0f / (((fConst415 + 0.168404877f) / fConst414) + 1.06935835f));
		fConst465 = (2.0f * (53.5361519f - fConst443));
		fConst466 = (1.0f / (((fConst415 + 0.51247865f) / fConst414) + 0.689621389f));
		fConst467 = (2.0f * (7.62173128f - fConst443));
		fConst468 = (1.0f / (((fConst415 + 0.782413065f) / fConst414) + 0.245291501f));
		fConst469 = (9.99999975e-05f / fConst417);
		fConst470 = (2.0f * (0.000433227193f - fConst469));
		fConst471 = (((fConst415 + -0.782413065f) / fConst414) + 0.245291501f);
		fConst472 = (2.0f * (0.245291501f - fConst443));
		fConst473 = (fConst469 + 0.000433227193f);
		fConst474 = (((fConst415 + -0.51247865f) / fConst414) + 0.689621389f);
		fConst475 = (2.0f * (0.689621389f - fConst443));
		fConst476 = (fConst443 + 7.62173128f);
		fConst477 = (((fConst415 + -0.168404877f) / fConst414) + 1.06935835f);
		fConst478 = (2.0f * (1.06935835f - fConst443));
		fConst479 = (fConst443 + 53.5361519f);
		fConst480 = (((fConst453 + -3.18972731f) / fConst452) + 4.07678175f);
		fConst481 = (1.0f / fConst455);
		fConst482 = (2.0f * (4.07678175f - fConst481));
		fConst483 = (fConst462 + 0.000407678192f);
		fConst484 = (((fConst453 + -0.743130445f) / fConst452) + 1.4500711f);
		fConst485 = (2.0f * (1.4500711f - fConst481));
		fConst486 = (fConst459 + 1.4500711f);
		fConst487 = (((fConst453 + -0.157482162f) / fConst452) + 0.935140193f);
		fConst488 = (2.0f * (0.935140193f - fConst481));
		fConst489 = (fConst456 + 0.935140193f);
		fConst490 = (float)java.lang.Math.tan((123.692459f / fConst0));
		fConst491 = (1.0f / fConst490);
		fConst492 = (1.0f / (((fConst491 + 0.157482162f) / fConst490) + 0.935140193f));
		fConst493 = mydsp_faustpower2_f(fConst490);
		fConst494 = (50.0638084f / fConst493);
		fConst495 = (2.0f * (0.935140193f - fConst494));
		fConst496 = (1.0f / (((fConst491 + 0.743130445f) / fConst490) + 1.4500711f));
		fConst497 = (11.0520525f / fConst493);
		fConst498 = (2.0f * (1.4500711f - fConst497));
		fConst499 = (1.0f / (((fConst491 + 3.18972731f) / fConst490) + 4.07678175f));
		fConst500 = (0.00176617282f / fConst493);
		fConst501 = (2.0f * (0.000407678192f - fConst500));
		fConst502 = (1.0f / (((fConst453 + 0.168404877f) / fConst452) + 1.06935835f));
		fConst503 = (2.0f * (53.5361519f - fConst481));
		fConst504 = (1.0f / (((fConst453 + 0.51247865f) / fConst452) + 0.689621389f));
		fConst505 = (2.0f * (7.62173128f - fConst481));
		fConst506 = (1.0f / (((fConst453 + 0.782413065f) / fConst452) + 0.245291501f));
		fConst507 = (9.99999975e-05f / fConst455);
		fConst508 = (2.0f * (0.000433227193f - fConst507));
		fConst509 = (((fConst453 + -0.782413065f) / fConst452) + 0.245291501f);
		fConst510 = (2.0f * (0.245291501f - fConst481));
		fConst511 = (fConst507 + 0.000433227193f);
		fConst512 = (((fConst453 + -0.51247865f) / fConst452) + 0.689621389f);
		fConst513 = (2.0f * (0.689621389f - fConst481));
		fConst514 = (fConst481 + 7.62173128f);
		fConst515 = (((fConst453 + -0.168404877f) / fConst452) + 1.06935835f);
		fConst516 = (2.0f * (1.06935835f - fConst481));
		fConst517 = (fConst481 + 53.5361519f);
		fConst518 = (((fConst491 + -3.18972731f) / fConst490) + 4.07678175f);
		fConst519 = (1.0f / fConst493);
		fConst520 = (2.0f * (4.07678175f - fConst519));
		fConst521 = (fConst500 + 0.000407678192f);
		fConst522 = (((fConst491 + -0.743130445f) / fConst490) + 1.4500711f);
		fConst523 = (2.0f * (1.4500711f - fConst519));
		fConst524 = (fConst497 + 1.4500711f);
		fConst525 = (((fConst491 + -0.157482162f) / fConst490) + 0.935140193f);
		fConst526 = (2.0f * (0.935140193f - fConst519));
		fConst527 = (fConst494 + 0.935140193f);
		fConst528 = (1.0f / (((fConst491 + 0.168404877f) / fConst490) + 1.06935835f));
		fConst529 = (2.0f * (53.5361519f - fConst519));
		fConst530 = (1.0f / (((fConst491 + 0.51247865f) / fConst490) + 0.689621389f));
		fConst531 = (2.0f * (7.62173128f - fConst519));
		fConst532 = (1.0f / (((fConst491 + 0.782413065f) / fConst490) + 0.245291501f));
		fConst533 = (9.99999975e-05f / fConst493);
		fConst534 = (2.0f * (0.000433227193f - fConst533));
		fConst535 = (((fConst491 + -0.782413065f) / fConst490) + 0.245291501f);
		fConst536 = (2.0f * (0.245291501f - fConst519));
		fConst537 = (fConst533 + 0.000433227193f);
		fConst538 = (((fConst491 + -0.51247865f) / fConst490) + 0.689621389f);
		fConst539 = (2.0f * (0.689621389f - fConst519));
		fConst540 = (fConst519 + 7.62173128f);
		fConst541 = (((fConst491 + -0.168404877f) / fConst490) + 1.06935835f);
		fConst542 = (2.0f * (1.06935835f - fConst519));
		fConst543 = (fConst519 + 53.5361519f);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)50.0f;
		fHslider1 = (float)100.0f;
		fCheckbox0 = (float)0.0f;
		fHslider2 = (float)5.0f;
		fCheckbox1 = (float)0.0f;
		fVslider0 = (float)0.0f;
		fHslider3 = (float)-20.0f;
		fVslider1 = (float)1.0f;
		fEntry0 = (float)2.0f;
		fHslider4 = (float)49.0f;
		fVslider2 = (float)0.10000000000000001f;
		fVslider3 = (float)-0.10000000000000001f;
		fVslider4 = (float)0.10000000000000001f;
		fVslider5 = (float)0.0f;
		fVslider6 = (float)0.0f;
		fVslider7 = (float)0.0f;
		fCheckbox2 = (float)0.0f;
		fVslider8 = (float)0.5f;
		fVslider9 = (float)0.0f;
		fHslider5 = (float)25.0f;
		fHslider6 = (float)0.90000000000000002f;
		fCheckbox3 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec4[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec10[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec12[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec11[l5] = 0.0f;
			
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
			fRec13[l13] = 0.0f;
			
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
			fRec14[l21] = 0.0f;
			
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
			fVec22[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec15[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec23[l30] = 0.0f;
			
		}
		IOTA = 0;
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec24[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fVec25[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec16[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fVec26[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 4096); l35 = (l35 + 1)) {
			fVec27[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec28[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec17[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fVec29[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			fVec30[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec18[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec19[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec20[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec21[l43] = 0.0f;
			
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
			fVec34[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec35[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 4096); l49 = (l49 + 1)) {
			fVec36[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec37[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fVec38[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 4096); l52 = (l52 + 1)) {
			fVec39[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			iRec23[l53] = 0;
			
		}
		for (int l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			fRec22[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec24[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec9[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec8[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec7[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec6[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec5[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec27[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec26[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec25[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec30[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec28[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec33[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec31[l67] = 0.0f;
			
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
			fRec40[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec39[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec38[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec37[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec36[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec35[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec34[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec47[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec46[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec45[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec44[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec43[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec42[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec41[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec54[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec53[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec52[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec51[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec50[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec49[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec48[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec61[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec60[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec59[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec58[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec57[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec56[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec55[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec68[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec67[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec66[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec65[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec64[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec63[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec62[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec75[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec74[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec73[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec72[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec71[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec70[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec69[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec82[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec81[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec80[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec79[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec78[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec77[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec76[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec89[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec88[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec87[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec86[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec85[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec84[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec83[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec96[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec95[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec94[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec93[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec92[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec91[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec90[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec103[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec102[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec101[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec100[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec99[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec98[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec97[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec110[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec109[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec108[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec107[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec106[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			fRec105[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			fRec104[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec117[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			fRec116[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec115[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			fRec114[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec113[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			fRec112[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			fRec111[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			fRec124[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			fRec123[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			fRec122[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			fRec121[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			fRec120[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			fRec119[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fRec118[l162] = 0.0f;
			
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
	
	public void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	public void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	public void buildUserInterface(UI ui_interface) {
		ui_interface.openVerticalBox("virtualAnalogLab");
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's oscillators.lib for documentation and references");
		ui_interface.openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("Signal Levels");
		ui_interface.declare("fVslider1", "0", "");
		ui_interface.declare("fVslider1", "style", "vslider");
		ui_interface.addVerticalSlider("Sawtooth", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Pulse Train");
		ui_interface.declare("fCheckbox2", "0", "");
		ui_interface.declare("fCheckbox2", "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface.addCheckButton("Order 3", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.declare("fVslider7", "1", "");
		ui_interface.declare("fVslider7", "style", "vslider");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "style", "knob");
		ui_interface.addVerticalSlider("Duty Cycle", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.declare("fVslider5", "2", "");
		ui_interface.declare("fVslider5", "style", "vslider");
		ui_interface.addVerticalSlider("Square", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fVslider6", "3", "");
		ui_interface.declare("fVslider6", "style", "vslider");
		ui_interface.addVerticalSlider("Triangle", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fVslider9", "4", "");
		ui_interface.declare("fVslider9", "style", "vslider");
		ui_interface.declare("fVslider9", "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface.addVerticalSlider("Pink Noise", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fVslider0", "5", "");
		ui_interface.declare("fVslider0", "style", "vslider");
		ui_interface.addVerticalSlider("Ext Input", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("Signal Parameters");
		ui_interface.declare("0", "0", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "style", "hslider");
		ui_interface.declare("fHslider3", "tooltip", "Sawtooth waveform amplitude");
		ui_interface.declare("fHslider3", "unit", "dB");
		ui_interface.addHorizontalSlider("Mix Amplitude", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "hslider");
		ui_interface.declare("fHslider4", "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface.declare("fHslider4", "unit", "PK");
		ui_interface.addHorizontalSlider("Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.declare("fVslider3", "3", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Percentange frequency-shift up or down for second oscillator");
		ui_interface.declare("fVslider3", "unit", "%%");
		ui_interface.addVerticalSlider("Detuning 1", new FaustVarAccess() {
				public String getId() { return "fVslider3"; }
				public void set(float val) { fVslider3 = val; }
				public float get() { return (float)fVslider3; }
			}
			, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fVslider4", "4", "");
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.declare("fVslider4", "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface.declare("fVslider4", "unit", "%%");
		ui_interface.addVerticalSlider("Detuning 2", new FaustVarAccess() {
				public String getId() { return "fVslider4"; }
				public void set(float val) { fVslider4 = val; }
				public float get() { return (float)fVslider4; }
			}
			, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fVslider2", "5", "");
		ui_interface.declare("fVslider2", "scale", "log");
		ui_interface.declare("fVslider2", "style", "knob");
		ui_interface.declare("fVslider2", "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface.declare("fVslider2", "unit", "sec");
		ui_interface.addVerticalSlider("Portamento", new FaustVarAccess() {
				public String getId() { return "fVslider2"; }
				public void set(float val) { fVslider2 = val; }
				public float get() { return (float)fVslider2; }
			}
			, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface.declare("fEntry0", "6", "");
		ui_interface.declare("fEntry0", "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface.addNumEntry("Saw Order", new FaustVarAccess() {
				public String getId() { return "fEntry0"; }
				public void set(float val) { fEntry0 = val; }
				public float get() { return (float)fEntry0; }
			}
			, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "See Faust's   vaeffects.lib for info and references");
		ui_interface.openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the Moog VCF   has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fCheckbox1", "1", "");
		ui_interface.declare("fCheckbox1", "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface.addCheckButton("Use Biquads", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.declare("fCheckbox3", "2", "");
		ui_interface.declare("fCheckbox3", "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface.addCheckButton("Normalized Ladders", new FaustVarAccess() {
				public String getId() { return "fCheckbox3"; }
				public void set(float val) { fCheckbox3 = val; }
				public float get() { return (float)fCheckbox3; }
			}
			);
		ui_interface.closeBox();
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface.declare("fHslider5", "unit", "PK");
		ui_interface.addHorizontalSlider("Corner Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 25.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface.declare("fHslider6", "2", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface.addHorizontalSlider("Corner Resonance", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.899999976f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "output level in decibels");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("VCF Output Level", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 5.0f, -60.0f, 20.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph14", "0", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67d6c740", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67d5ade0", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67d38c90", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67d16b40", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67cf0a70", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67cce920", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67cac7d0", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67c8a680", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67c68530", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67c463e0", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67c24290", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67c02140", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67bdc070", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67bb9f20", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fab67b96d40", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, -50.0f, 10.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "tooltip", "band-level averaging time in milliseconds");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("Level Averaging Time", new FaustVarAccess() {
				public String getId() { return "fHslider1"; }
				public void set(float val) { fHslider1 = val; }
				public float get() { return (float)fHslider1; }
			}
			, 100.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "tooltip", "Level offset in decibels");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Level dB Offset", new FaustVarAccess() {
				public String getId() { return "fHslider0"; }
				public void set(float val) { fHslider0 = val; }
				public float get() { return (float)fHslider0; }
			}
			, 50.0f, -50.0f, 100.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	public void compute(int count, float[][] inputs, float[][] outputs) {
		float[] input0 = inputs[0];
		float[] output0 = outputs[0];
		float[] output1 = outputs[1];
		float fSlow0 = fHslider0;
		float fSlow1 = (float)java.lang.Math.exp((0.0f - (fConst1 / fHslider1)));
		float fSlow2 = (1.0f - fSlow1);
		int iSlow3 = (int)fCheckbox0;
		float fSlow4 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider2)));
		int iSlow5 = (int)fCheckbox1;
		float fSlow6 = fVslider0;
		float fSlow7 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider3)));
		float fSlow8 = (0.333333343f * fVslider1);
		int iSlow9 = (int)(fEntry0 + -1.0f);
		int iSlow10 = (iSlow9 >= 2);
		int iSlow11 = (iSlow9 >= 1);
		float fSlow12 = (float)java.lang.Math.exp((0.0f - (fConst14 / fVslider2)));
		float fSlow13 = (440.0f * ((float)java.lang.Math.pow(2.0f, (0.0833333358f * (fHslider4 + -49.0f))) * (1.0f - fSlow12)));
		int iSlow14 = (iSlow9 >= 3);
		float fSlow15 = (1.0f - (0.00999999978f * fVslider3));
		float fSlow16 = ((0.00999999978f * fVslider4) + 1.0f);
		float fSlow17 = (fConst18 * fVslider5);
		float fSlow18 = (fConst20 * fVslider6);
		float fSlow19 = (fConst0 * fVslider7);
		float fSlow20 = fCheckbox2;
		float fSlow21 = (0.0833333358f * (1.0f - fSlow20));
		float fSlow22 = (0.00999999978f * fVslider8);
		float fSlow23 = (fConst21 * fSlow20);
		float fSlow24 = fVslider9;
		float fSlow25 = (0.439999998f * (float)java.lang.Math.pow(2.0f, (0.0833333358f * (fHslider5 + -49.0f))));
		float fSlow26 = fHslider6;
		float fSlow27 = (0.0f - (4.0f * (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(mydsp_faustpower4_f(fSlow26), 0.999998987f))));
		int iSlow28 = (int)fCheckbox3;
		float fSlow29 = (float)java.lang.Math.min(1.41419947f, (1.41421354f * fSlow26));
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
			fRec4[0] = (fSlow4 + (0.999000013f * fRec4[1]));
			fRec10[0] = (fSlow7 + (0.999000013f * fRec10[1]));
			fRec12[0] = (fSlow13 + (fSlow12 * fRec12[1]));
			float fTemp0 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fRec12[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec11[1] + (fConst14 * fVec1[1]));
			fRec11[0] = (fTemp1 - (float)java.lang.Math.floor(fTemp1));
			float fTemp2 = (2.0f * fRec11[0]);
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
			float fTemp10 = (fSlow15 * fRec12[0]);
			float fTemp11 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fTemp10));
			fVec8[0] = fTemp11;
			float fTemp12 = (fRec13[1] + (fConst14 * fVec8[1]));
			fRec13[0] = (fTemp12 - (float)java.lang.Math.floor(fTemp12));
			float fTemp13 = (2.0f * fRec13[0]);
			float fTemp14 = (fTemp13 + -1.0f);
			float fTemp15 = mydsp_faustpower2_f(fTemp14);
			fVec9[0] = fTemp15;
			float fTemp16 = mydsp_faustpower3_f(fTemp14);
			fVec10[0] = (fTemp16 + (1.0f - fTemp13));
			float fTemp17 = ((fTemp16 + (1.0f - (fTemp13 + fVec10[1]))) / fTemp11);
			fVec11[0] = fTemp17;
			float fTemp18 = (fTemp15 * (fTemp15 + -2.0f));
			fVec12[0] = fTemp18;
			float fTemp19 = ((fTemp18 - fVec12[1]) / fTemp11);
			fVec13[0] = fTemp19;
			float fTemp20 = ((fTemp19 - fVec13[1]) / fTemp11);
			fVec14[0] = fTemp20;
			float fTemp21 = (fSlow16 * fRec12[0]);
			float fTemp22 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fTemp21));
			fVec15[0] = fTemp22;
			float fTemp23 = (fRec14[1] + (fConst14 * fVec15[1]));
			fRec14[0] = (fTemp23 - (float)java.lang.Math.floor(fTemp23));
			float fTemp24 = (2.0f * fRec14[0]);
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
			float fTemp32 = (float)java.lang.Math.max(fRec12[0], 23.4489498f);
			float fTemp33 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fTemp32));
			fVec22[0] = fTemp33;
			float fTemp34 = (fRec15[1] + (fConst14 * fVec22[1]));
			fRec15[0] = (fTemp34 - (float)java.lang.Math.floor(fTemp34));
			float fTemp35 = (2.0f * fRec15[0]);
			float fTemp36 = (fTemp35 + -1.0f);
			float fTemp37 = mydsp_faustpower2_f(fTemp36);
			fVec23[0] = fTemp37;
			float fTemp38 = (((float)iVec0[1] * (fTemp37 - fVec23[1])) / fTemp33);
			fVec24[(IOTA & 4095)] = fTemp38;
			float fTemp39 = (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(2047.0f, (fConst19 / fTemp32)));
			int iTemp40 = (int)fTemp39;
			float fTemp41 = (float)java.lang.Math.floor(fTemp39);
			float fTemp42 = ((fTemp38 - (fVec24[((IOTA - iTemp40) & 4095)] * (fTemp41 + (1.0f - fTemp39)))) - ((fTemp39 - fTemp41) * fVec24[((IOTA - (iTemp40 + 1)) & 4095)]));
			float fTemp43 = (float)java.lang.Math.max(fTemp10, 23.4489498f);
			float fTemp44 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fTemp43));
			fVec25[0] = fTemp44;
			float fTemp45 = (fRec16[1] + (fConst14 * fVec25[1]));
			fRec16[0] = (fTemp45 - (float)java.lang.Math.floor(fTemp45));
			float fTemp46 = (2.0f * fRec16[0]);
			float fTemp47 = (fTemp46 + -1.0f);
			float fTemp48 = mydsp_faustpower2_f(fTemp47);
			fVec26[0] = fTemp48;
			float fTemp49 = (((float)iVec0[1] * (fTemp48 - fVec26[1])) / fTemp44);
			fVec27[(IOTA & 4095)] = fTemp49;
			float fTemp50 = (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(2047.0f, (fConst19 / fTemp43)));
			int iTemp51 = (int)fTemp50;
			float fTemp52 = (float)java.lang.Math.floor(fTemp50);
			float fTemp53 = ((fTemp49 - (fVec27[((IOTA - iTemp51) & 4095)] * (fTemp52 + (1.0f - fTemp50)))) - ((fTemp50 - fTemp52) * fVec27[((IOTA - (iTemp51 + 1)) & 4095)]));
			float fTemp54 = (float)java.lang.Math.max(fTemp21, 23.4489498f);
			float fTemp55 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fTemp54));
			fVec28[0] = fTemp55;
			float fTemp56 = (fRec17[1] + (fConst14 * fVec28[1]));
			fRec17[0] = (fTemp56 - (float)java.lang.Math.floor(fTemp56));
			float fTemp57 = (2.0f * fRec17[0]);
			float fTemp58 = (fTemp57 + -1.0f);
			float fTemp59 = mydsp_faustpower2_f(fTemp58);
			fVec29[0] = fTemp59;
			float fTemp60 = (((float)iVec0[1] * (fTemp59 - fVec29[1])) / fTemp55);
			fVec30[(IOTA & 4095)] = fTemp60;
			float fTemp61 = (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(2047.0f, (fConst19 / fTemp54)));
			int iTemp62 = (int)fTemp61;
			float fTemp63 = (float)java.lang.Math.floor(fTemp61);
			float fTemp64 = ((fTemp60 - (fVec30[((IOTA - iTemp62) & 4095)] * (fTemp63 + (1.0f - fTemp61)))) - ((fTemp61 - fTemp63) * fVec30[((IOTA - (iTemp62 + 1)) & 4095)]));
			fRec18[0] = ((fConst15 * fTemp42) + (0.999000013f * fRec18[1]));
			fRec19[0] = ((fConst15 * fTemp53) + (0.999000013f * fRec19[1]));
			fRec20[0] = ((fConst15 * fTemp64) + (0.999000013f * fRec20[1]));
			fRec21[0] = (fSlow22 + (0.99000001f * fRec21[1]));
			float fTemp65 = (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(2047.0f, (fConst0 * (fRec21[0] / fTemp32))));
			float fTemp66 = (float)java.lang.Math.floor(fTemp65);
			float fTemp67 = (fTemp66 + (1.0f - fTemp65));
			int iTemp68 = (int)fTemp65;
			float fTemp69 = (fTemp65 - fTemp66);
			int iTemp70 = (iTemp68 + 1);
			float fTemp71 = (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(2047.0f, (fConst0 * (fRec21[0] / fTemp43))));
			float fTemp72 = (float)java.lang.Math.floor(fTemp71);
			float fTemp73 = (fTemp72 + (1.0f - fTemp71));
			int iTemp74 = (int)fTemp71;
			float fTemp75 = (fTemp71 - fTemp72);
			int iTemp76 = (iTemp74 + 1);
			float fTemp77 = (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(2047.0f, (fConst0 * (fRec21[0] / fTemp54))));
			float fTemp78 = (float)java.lang.Math.floor(fTemp77);
			float fTemp79 = (fTemp78 + (1.0f - fTemp77));
			int iTemp80 = (int)fTemp77;
			float fTemp81 = (fTemp77 - fTemp78);
			int iTemp82 = (iTemp80 + 1);
			float fTemp83 = mydsp_faustpower3_f(fTemp36);
			fVec31[0] = (fTemp83 + (1.0f - fTemp35));
			float fTemp84 = ((fTemp83 + (1.0f - (fTemp35 + fVec31[1]))) / fTemp33);
			fVec32[0] = fTemp84;
			float fTemp85 = (((float)iVec0[2] * (fTemp84 - fVec32[1])) / fTemp33);
			fVec33[(IOTA & 4095)] = fTemp85;
			float fTemp86 = mydsp_faustpower3_f(fTemp47);
			fVec34[0] = (fTemp86 + (1.0f - fTemp46));
			float fTemp87 = ((fTemp86 + (1.0f - (fTemp46 + fVec34[1]))) / fTemp44);
			fVec35[0] = fTemp87;
			float fTemp88 = (((float)iVec0[2] * (fTemp87 - fVec35[1])) / fTemp44);
			fVec36[(IOTA & 4095)] = fTemp88;
			float fTemp89 = mydsp_faustpower3_f(fTemp58);
			fVec37[0] = (fTemp89 + (1.0f - fTemp57));
			float fTemp90 = ((fTemp89 + (1.0f - (fTemp57 + fVec37[1]))) / fTemp55);
			fVec38[0] = fTemp90;
			float fTemp91 = (((float)iVec0[2] * (fTemp90 - fVec38[1])) / fTemp55);
			fVec39[(IOTA & 4095)] = fTemp91;
			iRec23[0] = ((1103515245 * iRec23[1]) + 12345);
			fRec22[0] = (((0.522189379f * fRec22[3]) + ((4.65661287e-10f * (float)iRec23[0]) + (2.49495602f * fRec22[1]))) - (2.0172658f * fRec22[2]));
			float fTemp92 = ((fSlow6 * input0[i]) + (fRec10[0] * (((((fSlow8 * (((((iSlow10==0)?true:false)?(((iSlow14==0)?true:false)?(fConst17 * (((float)iVec0[3] * (fTemp9 - fVec7[1])) / fTemp0)):(fConst16 * (((float)iVec0[2] * (fTemp6 - fVec4[1])) / fTemp0))):(((iSlow11==0)?true:false)?(fConst15 * (((float)iVec0[1] * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (((iSlow10==0)?true:false)?(((iSlow14==0)?true:false)?(fConst17 * (((float)iVec0[3] * (fTemp20 - fVec14[1])) / fTemp11)):(fConst16 * (((float)iVec0[2] * (fTemp17 - fVec11[1])) / fTemp11))):(((iSlow11==0)?true:false)?(fConst15 * (((float)iVec0[1] * (fTemp15 - fVec9[1])) / fTemp11)):fTemp14))) + (((iSlow10==0)?true:false)?(((iSlow14==0)?true:false)?(fConst17 * (((float)iVec0[3] * (fTemp31 - fVec21[1])) / fTemp22)):(fConst16 * (((float)iVec0[2] * (fTemp28 - fVec18[1])) / fTemp22))):(((iSlow11==0)?true:false)?(fConst15 * (((float)iVec0[1] * (fTemp26 - fVec16[1])) / fTemp22)):fTemp25)))) + (fSlow17 * ((fTemp42 + fTemp53) + fTemp64))) + (fSlow18 * (fRec12[0] * ((fRec18[0] + (fSlow15 * fRec19[0])) + (fSlow16 * fRec20[0]))))) + (fSlow19 * ((fSlow21 * ((((fTemp38 - (fTemp67 * fVec24[((IOTA - iTemp68) & 4095)])) - (fTemp69 * fVec24[((IOTA - iTemp70) & 4095)])) + ((fTemp49 - (fTemp73 * fVec27[((IOTA - iTemp74) & 4095)])) - (fTemp75 * fVec27[((IOTA - iTemp76) & 4095)]))) + ((fTemp60 - (fTemp79 * fVec30[((IOTA - iTemp80) & 4095)])) - (fTemp81 * fVec30[((IOTA - iTemp82) & 4095)])))) + (fSlow23 * ((((fTemp85 - (fVec33[((IOTA - iTemp68) & 4095)] * fTemp67)) - (fTemp69 * fVec33[((IOTA - iTemp70) & 4095)])) + ((fTemp88 - (fVec36[((IOTA - iTemp74) & 4095)] * fTemp73)) - (fTemp75 * fVec36[((IOTA - iTemp76) & 4095)]))) + ((fTemp91 - (fVec39[((IOTA - iTemp80) & 4095)] * fTemp79)) - (fTemp81 * fVec39[((IOTA - iTemp82) & 4095)]))))))) + (fSlow24 * (((0.0499220341f * fRec22[0]) + (0.0506126992f * fRec22[2])) - ((0.0959935337f * fRec22[1]) + (0.00440878607f * fRec22[3])))))));
			float fTemp93 = (((iSlow3==0)?true:false)?0.0f:fTemp92);
			fRec24[0] = (fSlow25 + (0.999000013f * fRec24[1]));
			float fTemp94 = (fConst22 * fRec24[0]);
			float fTemp95 = (1.0f - fTemp94);
			fRec9[0] = (fTemp93 + ((fTemp95 * fRec9[1]) + (fSlow27 * fRec5[1])));
			fRec8[0] = (fRec9[0] + (fTemp95 * fRec8[1]));
			fRec7[0] = (fRec8[0] + (fTemp95 * fRec7[1]));
			fRec6[0] = (fRec7[0] + (fRec6[1] * fTemp95));
			fRec5[0] = (fRec6[0] * (float)java.lang.Math.pow(fTemp94, 4.0f));
			fRec27[0] = (fSlow25 + (0.999000013f * fRec27[1]));
			float fTemp96 = (float)java.lang.Math.tan((fConst23 * (float)java.lang.Math.max(20.0f, (float)java.lang.Math.min(10000.0f, fRec27[0]))));
			float fTemp97 = (1.0f / fTemp96);
			float fTemp98 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp96)));
			float fTemp99 = (fSlow30 + (((fSlow32 + fTemp97) / fTemp96) + 1.0f));
			fRec26[0] = (fTemp93 - (((fRec26[2] * (fSlow30 + (((fTemp97 - fSlow32) / fTemp96) + 1.0f))) + (2.0f * (fRec26[1] * (fSlow30 + fTemp98)))) / fTemp99));
			float fTemp100 = (fSlow33 + (((fSlow34 + fTemp97) / fTemp96) + 1.0f));
			fRec25[0] = (((fRec26[2] + (fRec26[0] + (2.0f * fRec26[1]))) / fTemp99) - (((fRec25[2] * (fSlow33 + (((fTemp97 - fSlow34) / fTemp96) + 1.0f))) + (2.0f * (fRec25[1] * (fSlow33 + fTemp98)))) / fTemp100));
			float fTemp101 = (float)java.lang.Math.tan((fConst23 * (float)java.lang.Math.max(fRec27[0], 20.0f)));
			float fTemp102 = (1.0f / fTemp101);
			float fTemp103 = (fSlow37 + (((fSlow38 + fTemp102) / fTemp101) + 1.0f));
			float fTemp104 = ((fSlow37 + (1.0f - ((fSlow38 - fTemp102) / fTemp101))) / fTemp103);
			float fTemp105 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, fTemp104));
			float fTemp106 = (1.0f - mydsp_faustpower2_f(fTemp105));
			float fTemp107 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp106));
			float fTemp108 = ((fRec28[1] * (0.0f - fTemp105)) + (fTemp93 * fTemp107));
			float fTemp109 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp101)));
			float fTemp110 = (fSlow37 + fTemp109);
			float fTemp111 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, (2.0f * (fTemp110 / (fTemp103 * (fTemp104 + 1.0f))))));
			float fTemp112 = (1.0f - mydsp_faustpower2_f(fTemp111));
			float fTemp113 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp112));
			fRec30[0] = ((fRec30[1] * (0.0f - fTemp111)) + (fTemp108 * fTemp113));
			fRec28[0] = ((fTemp108 * fTemp111) + (fRec30[1] * fTemp113));
			float fRec29 = fRec30[0];
			float fTemp114 = (1.0f - (fTemp110 / fTemp103));
			float fTemp115 = (float)java.lang.Math.sqrt(fTemp106);
			float fTemp116 = ((((fTemp93 * fTemp105) + (fRec28[1] * fTemp107)) + (2.0f * ((fRec28[0] * fTemp114) / fTemp115))) + ((fRec29 * ((1.0f - fTemp104) - (2.0f * (fTemp111 * fTemp114)))) / (fTemp115 * (float)java.lang.Math.sqrt(fTemp112))));
			float fTemp117 = (fSlow35 + ((((fSlow39 + fTemp102) / fTemp101) + 1.0f) - fSlow36));
			float fTemp118 = ((fSlow35 + ((((fTemp102 - fSlow39) / fTemp101) + 1.0f) - fSlow36)) / fTemp117);
			float fTemp119 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, fTemp118));
			float fTemp120 = (1.0f - mydsp_faustpower2_f(fTemp119));
			float fTemp121 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp120));
			float fTemp122 = ((fRec31[1] * (0.0f - fTemp119)) + ((fTemp116 * fTemp121) / fTemp103));
			float fTemp123 = (fSlow35 + (fTemp109 - fSlow36));
			float fTemp124 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, (2.0f * (fTemp123 / (fTemp117 * (fTemp118 + 1.0f))))));
			float fTemp125 = (1.0f - mydsp_faustpower2_f(fTemp124));
			float fTemp126 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp125));
			fRec33[0] = ((fRec33[1] * (0.0f - fTemp124)) + (fTemp122 * fTemp126));
			fRec31[0] = ((fTemp122 * fTemp124) + (fRec33[1] * fTemp126));
			float fRec32 = fRec33[0];
			float fTemp127 = (1.0f - (fTemp123 / fTemp117));
			float fTemp128 = (float)java.lang.Math.sqrt(fTemp120);
			float fTemp129 = (((iSlow3==0)?true:false)?fTemp92:(fRec4[0] * (((iSlow5==0)?true:false)?(((iSlow28==0)?true:false)?((((((fTemp116 * fTemp119) / fTemp103) + (fRec31[1] * fTemp121)) + (2.0f * ((fRec31[0] * fTemp127) / fTemp128))) + ((fRec32 * ((1.0f - fTemp118) - (2.0f * (fTemp124 * fTemp127)))) / (fTemp128 * (float)java.lang.Math.sqrt(fTemp125)))) / fTemp117):((fRec25[2] + (fRec25[0] + (2.0f * fRec25[1]))) / fTemp100)):fRec5[0])));
			fRec3[0] = (fTemp129 - (fConst11 * ((fConst24 * fRec3[2]) + (fConst26 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst27 * fRec3[0])) + (fConst27 * fRec3[2]))) - (fConst8 * ((fConst28 * fRec2[2]) + (fConst29 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst30 * fRec2[0])) + (fConst30 * fRec2[2]))) - (fConst4 * ((fConst31 * fRec1[2]) + (fConst32 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst4 * (((fConst7 * fRec1[1]) + (fConst33 * fRec1[0])) + (fConst33 * fRec1[2]))))));
			fVbargraph0 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec0[0]))));
			fRec40[0] = (fTemp129 - (fConst50 * ((fConst53 * fRec40[2]) + (fConst54 * fRec40[1]))));
			fRec39[0] = ((fConst50 * (((fConst52 * fRec40[1]) + (fConst55 * fRec40[0])) + (fConst55 * fRec40[2]))) - (fConst48 * ((fConst56 * fRec39[2]) + (fConst57 * fRec39[1]))));
			fRec38[0] = ((fConst48 * (((fConst49 * fRec39[1]) + (fConst58 * fRec39[0])) + (fConst58 * fRec39[2]))) - (fConst46 * ((fConst59 * fRec38[2]) + (fConst60 * fRec38[1]))));
			float fTemp130 = (fConst46 * (((fConst47 * fRec38[1]) + (fConst61 * fRec38[0])) + (fConst61 * fRec38[2])));
			fRec37[0] = (fTemp130 - (fConst43 * ((fConst62 * fRec37[2]) + (fConst64 * fRec37[1]))));
			fRec36[0] = ((fConst43 * (((fConst45 * fRec37[1]) + (fConst65 * fRec37[0])) + (fConst65 * fRec37[2]))) - (fConst40 * ((fConst66 * fRec36[2]) + (fConst67 * fRec36[1]))));
			fRec35[0] = ((fConst40 * (((fConst42 * fRec36[1]) + (fConst68 * fRec36[0])) + (fConst68 * fRec36[2]))) - (fConst36 * ((fConst69 * fRec35[2]) + (fConst70 * fRec35[1]))));
			fRec34[0] = ((fSlow1 * fRec34[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst36 * (((fConst39 * fRec35[1]) + (fConst71 * fRec35[0])) + (fConst71 * fRec35[2]))))));
			fVbargraph1 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec34[0]))));
			fRec47[0] = (fTemp130 - (fConst88 * ((fConst91 * fRec47[2]) + (fConst92 * fRec47[1]))));
			fRec46[0] = ((fConst88 * (((fConst90 * fRec47[1]) + (fConst93 * fRec47[0])) + (fConst93 * fRec47[2]))) - (fConst86 * ((fConst94 * fRec46[2]) + (fConst95 * fRec46[1]))));
			fRec45[0] = ((fConst86 * (((fConst87 * fRec46[1]) + (fConst96 * fRec46[0])) + (fConst96 * fRec46[2]))) - (fConst84 * ((fConst97 * fRec45[2]) + (fConst98 * fRec45[1]))));
			float fTemp131 = (fConst84 * (((fConst85 * fRec45[1]) + (fConst99 * fRec45[0])) + (fConst99 * fRec45[2])));
			fRec44[0] = (fTemp131 - (fConst81 * ((fConst100 * fRec44[2]) + (fConst102 * fRec44[1]))));
			fRec43[0] = ((fConst81 * (((fConst83 * fRec44[1]) + (fConst103 * fRec44[0])) + (fConst103 * fRec44[2]))) - (fConst78 * ((fConst104 * fRec43[2]) + (fConst105 * fRec43[1]))));
			fRec42[0] = ((fConst78 * (((fConst80 * fRec43[1]) + (fConst106 * fRec43[0])) + (fConst106 * fRec43[2]))) - (fConst74 * ((fConst107 * fRec42[2]) + (fConst108 * fRec42[1]))));
			fRec41[0] = ((fSlow1 * fRec41[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst74 * (((fConst77 * fRec42[1]) + (fConst109 * fRec42[0])) + (fConst109 * fRec42[2]))))));
			fVbargraph2 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec41[0]))));
			fRec54[0] = (fTemp131 - (fConst126 * ((fConst129 * fRec54[2]) + (fConst130 * fRec54[1]))));
			fRec53[0] = ((fConst126 * (((fConst128 * fRec54[1]) + (fConst131 * fRec54[0])) + (fConst131 * fRec54[2]))) - (fConst124 * ((fConst132 * fRec53[2]) + (fConst133 * fRec53[1]))));
			fRec52[0] = ((fConst124 * (((fConst125 * fRec53[1]) + (fConst134 * fRec53[0])) + (fConst134 * fRec53[2]))) - (fConst122 * ((fConst135 * fRec52[2]) + (fConst136 * fRec52[1]))));
			float fTemp132 = (fConst122 * (((fConst123 * fRec52[1]) + (fConst137 * fRec52[0])) + (fConst137 * fRec52[2])));
			fRec51[0] = (fTemp132 - (fConst119 * ((fConst138 * fRec51[2]) + (fConst140 * fRec51[1]))));
			fRec50[0] = ((fConst119 * (((fConst121 * fRec51[1]) + (fConst141 * fRec51[0])) + (fConst141 * fRec51[2]))) - (fConst116 * ((fConst142 * fRec50[2]) + (fConst143 * fRec50[1]))));
			fRec49[0] = ((fConst116 * (((fConst118 * fRec50[1]) + (fConst144 * fRec50[0])) + (fConst144 * fRec50[2]))) - (fConst112 * ((fConst145 * fRec49[2]) + (fConst146 * fRec49[1]))));
			fRec48[0] = ((fSlow1 * fRec48[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst112 * (((fConst115 * fRec49[1]) + (fConst147 * fRec49[0])) + (fConst147 * fRec49[2]))))));
			fVbargraph3 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec48[0]))));
			fRec61[0] = (fTemp132 - (fConst164 * ((fConst167 * fRec61[2]) + (fConst168 * fRec61[1]))));
			fRec60[0] = ((fConst164 * (((fConst166 * fRec61[1]) + (fConst169 * fRec61[0])) + (fConst169 * fRec61[2]))) - (fConst162 * ((fConst170 * fRec60[2]) + (fConst171 * fRec60[1]))));
			fRec59[0] = ((fConst162 * (((fConst163 * fRec60[1]) + (fConst172 * fRec60[0])) + (fConst172 * fRec60[2]))) - (fConst160 * ((fConst173 * fRec59[2]) + (fConst174 * fRec59[1]))));
			float fTemp133 = (fConst160 * (((fConst161 * fRec59[1]) + (fConst175 * fRec59[0])) + (fConst175 * fRec59[2])));
			fRec58[0] = (fTemp133 - (fConst157 * ((fConst176 * fRec58[2]) + (fConst178 * fRec58[1]))));
			fRec57[0] = ((fConst157 * (((fConst159 * fRec58[1]) + (fConst179 * fRec58[0])) + (fConst179 * fRec58[2]))) - (fConst154 * ((fConst180 * fRec57[2]) + (fConst181 * fRec57[1]))));
			fRec56[0] = ((fConst154 * (((fConst156 * fRec57[1]) + (fConst182 * fRec57[0])) + (fConst182 * fRec57[2]))) - (fConst150 * ((fConst183 * fRec56[2]) + (fConst184 * fRec56[1]))));
			fRec55[0] = ((fSlow1 * fRec55[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst150 * (((fConst153 * fRec56[1]) + (fConst185 * fRec56[0])) + (fConst185 * fRec56[2]))))));
			fVbargraph4 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec55[0]))));
			fRec68[0] = (fTemp133 - (fConst202 * ((fConst205 * fRec68[2]) + (fConst206 * fRec68[1]))));
			fRec67[0] = ((fConst202 * (((fConst204 * fRec68[1]) + (fConst207 * fRec68[0])) + (fConst207 * fRec68[2]))) - (fConst200 * ((fConst208 * fRec67[2]) + (fConst209 * fRec67[1]))));
			fRec66[0] = ((fConst200 * (((fConst201 * fRec67[1]) + (fConst210 * fRec67[0])) + (fConst210 * fRec67[2]))) - (fConst198 * ((fConst211 * fRec66[2]) + (fConst212 * fRec66[1]))));
			float fTemp134 = (fConst198 * (((fConst199 * fRec66[1]) + (fConst213 * fRec66[0])) + (fConst213 * fRec66[2])));
			fRec65[0] = (fTemp134 - (fConst195 * ((fConst214 * fRec65[2]) + (fConst216 * fRec65[1]))));
			fRec64[0] = ((fConst195 * (((fConst197 * fRec65[1]) + (fConst217 * fRec65[0])) + (fConst217 * fRec65[2]))) - (fConst192 * ((fConst218 * fRec64[2]) + (fConst219 * fRec64[1]))));
			fRec63[0] = ((fConst192 * (((fConst194 * fRec64[1]) + (fConst220 * fRec64[0])) + (fConst220 * fRec64[2]))) - (fConst188 * ((fConst221 * fRec63[2]) + (fConst222 * fRec63[1]))));
			fRec62[0] = ((fSlow1 * fRec62[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst188 * (((fConst191 * fRec63[1]) + (fConst223 * fRec63[0])) + (fConst223 * fRec63[2]))))));
			fVbargraph5 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec62[0]))));
			fRec75[0] = (fTemp134 - (fConst240 * ((fConst243 * fRec75[2]) + (fConst244 * fRec75[1]))));
			fRec74[0] = ((fConst240 * (((fConst242 * fRec75[1]) + (fConst245 * fRec75[0])) + (fConst245 * fRec75[2]))) - (fConst238 * ((fConst246 * fRec74[2]) + (fConst247 * fRec74[1]))));
			fRec73[0] = ((fConst238 * (((fConst239 * fRec74[1]) + (fConst248 * fRec74[0])) + (fConst248 * fRec74[2]))) - (fConst236 * ((fConst249 * fRec73[2]) + (fConst250 * fRec73[1]))));
			float fTemp135 = (fConst236 * (((fConst237 * fRec73[1]) + (fConst251 * fRec73[0])) + (fConst251 * fRec73[2])));
			fRec72[0] = (fTemp135 - (fConst233 * ((fConst252 * fRec72[2]) + (fConst254 * fRec72[1]))));
			fRec71[0] = ((fConst233 * (((fConst235 * fRec72[1]) + (fConst255 * fRec72[0])) + (fConst255 * fRec72[2]))) - (fConst230 * ((fConst256 * fRec71[2]) + (fConst257 * fRec71[1]))));
			fRec70[0] = ((fConst230 * (((fConst232 * fRec71[1]) + (fConst258 * fRec71[0])) + (fConst258 * fRec71[2]))) - (fConst226 * ((fConst259 * fRec70[2]) + (fConst260 * fRec70[1]))));
			fRec69[0] = ((fSlow1 * fRec69[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst226 * (((fConst229 * fRec70[1]) + (fConst261 * fRec70[0])) + (fConst261 * fRec70[2]))))));
			fVbargraph6 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec69[0]))));
			fRec82[0] = (fTemp135 - (fConst278 * ((fConst281 * fRec82[2]) + (fConst282 * fRec82[1]))));
			fRec81[0] = ((fConst278 * (((fConst280 * fRec82[1]) + (fConst283 * fRec82[0])) + (fConst283 * fRec82[2]))) - (fConst276 * ((fConst284 * fRec81[2]) + (fConst285 * fRec81[1]))));
			fRec80[0] = ((fConst276 * (((fConst277 * fRec81[1]) + (fConst286 * fRec81[0])) + (fConst286 * fRec81[2]))) - (fConst274 * ((fConst287 * fRec80[2]) + (fConst288 * fRec80[1]))));
			float fTemp136 = (fConst274 * (((fConst275 * fRec80[1]) + (fConst289 * fRec80[0])) + (fConst289 * fRec80[2])));
			fRec79[0] = (fTemp136 - (fConst271 * ((fConst290 * fRec79[2]) + (fConst292 * fRec79[1]))));
			fRec78[0] = ((fConst271 * (((fConst273 * fRec79[1]) + (fConst293 * fRec79[0])) + (fConst293 * fRec79[2]))) - (fConst268 * ((fConst294 * fRec78[2]) + (fConst295 * fRec78[1]))));
			fRec77[0] = ((fConst268 * (((fConst270 * fRec78[1]) + (fConst296 * fRec78[0])) + (fConst296 * fRec78[2]))) - (fConst264 * ((fConst297 * fRec77[2]) + (fConst298 * fRec77[1]))));
			fRec76[0] = ((fSlow1 * fRec76[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst264 * (((fConst267 * fRec77[1]) + (fConst299 * fRec77[0])) + (fConst299 * fRec77[2]))))));
			fVbargraph7 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec76[0]))));
			fRec89[0] = (fTemp136 - (fConst316 * ((fConst319 * fRec89[2]) + (fConst320 * fRec89[1]))));
			fRec88[0] = ((fConst316 * (((fConst318 * fRec89[1]) + (fConst321 * fRec89[0])) + (fConst321 * fRec89[2]))) - (fConst314 * ((fConst322 * fRec88[2]) + (fConst323 * fRec88[1]))));
			fRec87[0] = ((fConst314 * (((fConst315 * fRec88[1]) + (fConst324 * fRec88[0])) + (fConst324 * fRec88[2]))) - (fConst312 * ((fConst325 * fRec87[2]) + (fConst326 * fRec87[1]))));
			float fTemp137 = (fConst312 * (((fConst313 * fRec87[1]) + (fConst327 * fRec87[0])) + (fConst327 * fRec87[2])));
			fRec86[0] = (fTemp137 - (fConst309 * ((fConst328 * fRec86[2]) + (fConst330 * fRec86[1]))));
			fRec85[0] = ((fConst309 * (((fConst311 * fRec86[1]) + (fConst331 * fRec86[0])) + (fConst331 * fRec86[2]))) - (fConst306 * ((fConst332 * fRec85[2]) + (fConst333 * fRec85[1]))));
			fRec84[0] = ((fConst306 * (((fConst308 * fRec85[1]) + (fConst334 * fRec85[0])) + (fConst334 * fRec85[2]))) - (fConst302 * ((fConst335 * fRec84[2]) + (fConst336 * fRec84[1]))));
			fRec83[0] = ((fSlow1 * fRec83[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst302 * (((fConst305 * fRec84[1]) + (fConst337 * fRec84[0])) + (fConst337 * fRec84[2]))))));
			fVbargraph8 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec83[0]))));
			fRec96[0] = (fTemp137 - (fConst354 * ((fConst357 * fRec96[2]) + (fConst358 * fRec96[1]))));
			fRec95[0] = ((fConst354 * (((fConst356 * fRec96[1]) + (fConst359 * fRec96[0])) + (fConst359 * fRec96[2]))) - (fConst352 * ((fConst360 * fRec95[2]) + (fConst361 * fRec95[1]))));
			fRec94[0] = ((fConst352 * (((fConst353 * fRec95[1]) + (fConst362 * fRec95[0])) + (fConst362 * fRec95[2]))) - (fConst350 * ((fConst363 * fRec94[2]) + (fConst364 * fRec94[1]))));
			float fTemp138 = (fConst350 * (((fConst351 * fRec94[1]) + (fConst365 * fRec94[0])) + (fConst365 * fRec94[2])));
			fRec93[0] = (fTemp138 - (fConst347 * ((fConst366 * fRec93[2]) + (fConst368 * fRec93[1]))));
			fRec92[0] = ((fConst347 * (((fConst349 * fRec93[1]) + (fConst369 * fRec93[0])) + (fConst369 * fRec93[2]))) - (fConst344 * ((fConst370 * fRec92[2]) + (fConst371 * fRec92[1]))));
			fRec91[0] = ((fConst344 * (((fConst346 * fRec92[1]) + (fConst372 * fRec92[0])) + (fConst372 * fRec92[2]))) - (fConst340 * ((fConst373 * fRec91[2]) + (fConst374 * fRec91[1]))));
			fRec90[0] = ((fSlow1 * fRec90[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst340 * (((fConst343 * fRec91[1]) + (fConst375 * fRec91[0])) + (fConst375 * fRec91[2]))))));
			fVbargraph9 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec90[0]))));
			fRec103[0] = (fTemp138 - (fConst392 * ((fConst395 * fRec103[2]) + (fConst396 * fRec103[1]))));
			fRec102[0] = ((fConst392 * (((fConst394 * fRec103[1]) + (fConst397 * fRec103[0])) + (fConst397 * fRec103[2]))) - (fConst390 * ((fConst398 * fRec102[2]) + (fConst399 * fRec102[1]))));
			fRec101[0] = ((fConst390 * (((fConst391 * fRec102[1]) + (fConst400 * fRec102[0])) + (fConst400 * fRec102[2]))) - (fConst388 * ((fConst401 * fRec101[2]) + (fConst402 * fRec101[1]))));
			float fTemp139 = (fConst388 * (((fConst389 * fRec101[1]) + (fConst403 * fRec101[0])) + (fConst403 * fRec101[2])));
			fRec100[0] = (fTemp139 - (fConst385 * ((fConst404 * fRec100[2]) + (fConst406 * fRec100[1]))));
			fRec99[0] = ((fConst385 * (((fConst387 * fRec100[1]) + (fConst407 * fRec100[0])) + (fConst407 * fRec100[2]))) - (fConst382 * ((fConst408 * fRec99[2]) + (fConst409 * fRec99[1]))));
			fRec98[0] = ((fConst382 * (((fConst384 * fRec99[1]) + (fConst410 * fRec99[0])) + (fConst410 * fRec99[2]))) - (fConst378 * ((fConst411 * fRec98[2]) + (fConst412 * fRec98[1]))));
			fRec97[0] = ((fSlow1 * fRec97[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst378 * (((fConst381 * fRec98[1]) + (fConst413 * fRec98[0])) + (fConst413 * fRec98[2]))))));
			fVbargraph10 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec97[0]))));
			fRec110[0] = (fTemp139 - (fConst430 * ((fConst433 * fRec110[2]) + (fConst434 * fRec110[1]))));
			fRec109[0] = ((fConst430 * (((fConst432 * fRec110[1]) + (fConst435 * fRec110[0])) + (fConst435 * fRec110[2]))) - (fConst428 * ((fConst436 * fRec109[2]) + (fConst437 * fRec109[1]))));
			fRec108[0] = ((fConst428 * (((fConst429 * fRec109[1]) + (fConst438 * fRec109[0])) + (fConst438 * fRec109[2]))) - (fConst426 * ((fConst439 * fRec108[2]) + (fConst440 * fRec108[1]))));
			float fTemp140 = (fConst426 * (((fConst427 * fRec108[1]) + (fConst441 * fRec108[0])) + (fConst441 * fRec108[2])));
			fRec107[0] = (fTemp140 - (fConst423 * ((fConst442 * fRec107[2]) + (fConst444 * fRec107[1]))));
			fRec106[0] = ((fConst423 * (((fConst425 * fRec107[1]) + (fConst445 * fRec107[0])) + (fConst445 * fRec107[2]))) - (fConst420 * ((fConst446 * fRec106[2]) + (fConst447 * fRec106[1]))));
			fRec105[0] = ((fConst420 * (((fConst422 * fRec106[1]) + (fConst448 * fRec106[0])) + (fConst448 * fRec106[2]))) - (fConst416 * ((fConst449 * fRec105[2]) + (fConst450 * fRec105[1]))));
			fRec104[0] = ((fSlow1 * fRec104[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst416 * (((fConst419 * fRec105[1]) + (fConst451 * fRec105[0])) + (fConst451 * fRec105[2]))))));
			fVbargraph11 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec104[0]))));
			fRec117[0] = (fTemp140 - (fConst468 * ((fConst471 * fRec117[2]) + (fConst472 * fRec117[1]))));
			fRec116[0] = ((fConst468 * (((fConst470 * fRec117[1]) + (fConst473 * fRec117[0])) + (fConst473 * fRec117[2]))) - (fConst466 * ((fConst474 * fRec116[2]) + (fConst475 * fRec116[1]))));
			fRec115[0] = ((fConst466 * (((fConst467 * fRec116[1]) + (fConst476 * fRec116[0])) + (fConst476 * fRec116[2]))) - (fConst464 * ((fConst477 * fRec115[2]) + (fConst478 * fRec115[1]))));
			float fTemp141 = (fConst464 * (((fConst465 * fRec115[1]) + (fConst479 * fRec115[0])) + (fConst479 * fRec115[2])));
			fRec114[0] = (fTemp141 - (fConst461 * ((fConst480 * fRec114[2]) + (fConst482 * fRec114[1]))));
			fRec113[0] = ((fConst461 * (((fConst463 * fRec114[1]) + (fConst483 * fRec114[0])) + (fConst483 * fRec114[2]))) - (fConst458 * ((fConst484 * fRec113[2]) + (fConst485 * fRec113[1]))));
			fRec112[0] = ((fConst458 * (((fConst460 * fRec113[1]) + (fConst486 * fRec113[0])) + (fConst486 * fRec113[2]))) - (fConst454 * ((fConst487 * fRec112[2]) + (fConst488 * fRec112[1]))));
			fRec111[0] = ((fSlow1 * fRec111[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst454 * (((fConst457 * fRec112[1]) + (fConst489 * fRec112[0])) + (fConst489 * fRec112[2]))))));
			fVbargraph12 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec111[0]))));
			fRec124[0] = (fTemp141 - (fConst506 * ((fConst509 * fRec124[2]) + (fConst510 * fRec124[1]))));
			fRec123[0] = ((fConst506 * (((fConst508 * fRec124[1]) + (fConst511 * fRec124[0])) + (fConst511 * fRec124[2]))) - (fConst504 * ((fConst512 * fRec123[2]) + (fConst513 * fRec123[1]))));
			fRec122[0] = ((fConst504 * (((fConst505 * fRec123[1]) + (fConst514 * fRec123[0])) + (fConst514 * fRec123[2]))) - (fConst502 * ((fConst515 * fRec122[2]) + (fConst516 * fRec122[1]))));
			float fTemp142 = (fConst502 * (((fConst503 * fRec122[1]) + (fConst517 * fRec122[0])) + (fConst517 * fRec122[2])));
			fRec121[0] = (fTemp142 - (fConst499 * ((fConst518 * fRec121[2]) + (fConst520 * fRec121[1]))));
			fRec120[0] = ((fConst499 * (((fConst501 * fRec121[1]) + (fConst521 * fRec121[0])) + (fConst521 * fRec121[2]))) - (fConst496 * ((fConst522 * fRec120[2]) + (fConst523 * fRec120[1]))));
			fRec119[0] = ((fConst496 * (((fConst498 * fRec120[1]) + (fConst524 * fRec120[0])) + (fConst524 * fRec120[2]))) - (fConst492 * ((fConst525 * fRec119[2]) + (fConst526 * fRec119[1]))));
			fRec118[0] = ((fSlow1 * fRec118[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst492 * (((fConst495 * fRec119[1]) + (fConst527 * fRec119[0])) + (fConst527 * fRec119[2]))))));
			fVbargraph13 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec118[0]))));
			fRec128[0] = (fTemp142 - (fConst532 * ((fConst535 * fRec128[2]) + (fConst536 * fRec128[1]))));
			fRec127[0] = ((fConst532 * (((fConst534 * fRec128[1]) + (fConst537 * fRec128[0])) + (fConst537 * fRec128[2]))) - (fConst530 * ((fConst538 * fRec127[2]) + (fConst539 * fRec127[1]))));
			fRec126[0] = ((fConst530 * (((fConst531 * fRec127[1]) + (fConst540 * fRec127[0])) + (fConst540 * fRec127[2]))) - (fConst528 * ((fConst541 * fRec126[2]) + (fConst542 * fRec126[1]))));
			fRec125[0] = ((fSlow1 * fRec125[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst528 * (((fConst529 * fRec126[1]) + (fConst543 * fRec126[0])) + (fConst543 * fRec126[2]))))));
			fVbargraph14 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec125[0]))));
			output0[i] = fTemp129;
			output1[i] = fTemp129;
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec4[1] = fRec4[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fVec1[1] = fVec1[0];
			fRec11[1] = fRec11[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec13[1] = fRec13[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec14[1] = fRec14[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec15[1] = fRec15[0];
			fVec23[1] = fVec23[0];
			IOTA = (IOTA + 1);
			fVec25[1] = fVec25[0];
			fRec16[1] = fRec16[0];
			fVec26[1] = fVec26[0];
			fVec28[1] = fVec28[0];
			fRec17[1] = fRec17[0];
			fVec29[1] = fVec29[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fVec31[1] = fVec31[0];
			fVec32[1] = fVec32[0];
			fVec34[1] = fVec34[0];
			fVec35[1] = fVec35[0];
			fVec37[1] = fVec37[0];
			fVec38[1] = fVec38[0];
			iRec23[1] = iRec23[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec22[j1] = fRec22[(j1 - 1)];
				
			}
			fRec24[1] = fRec24[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec33[1] = fRec33[0];
			fRec31[1] = fRec31[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
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
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fRec119[2] = fRec119[1];
			fRec119[1] = fRec119[0];
			fRec118[1] = fRec118[0];
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

