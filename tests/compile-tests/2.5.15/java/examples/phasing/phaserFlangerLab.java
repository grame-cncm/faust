/* ------------------------------------------------------------
name: "phaserFlangerLab"
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
	float fCheckbox1;
	float fHslider3;
	float fConst14;
	float fHslider4;
	float fRec4[] = new float[2];
	float fRec5[] = new float[2];
	float fHbargraph0;
	float fVslider0;
	float fRec6[] = new float[2];
	float fCheckbox2;
	float fCheckbox3;
	float fEntry0;
	float fConst15;
	float fVslider1;
	float fVslider2;
	float fRec8[] = new float[2];
	float fVec1[] = new float[2];
	float fRec7[] = new float[2];
	float fConst16;
	float fVec2[] = new float[2];
	float fConst17;
	float fVec3[] = new float[2];
	float fVec4[] = new float[2];
	float fConst18;
	float fVec5[] = new float[2];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2];
	float fVslider3;
	float fVec8[] = new float[2];
	float fRec9[] = new float[2];
	float fVec9[] = new float[2];
	float fVec10[] = new float[2];
	float fVec11[] = new float[2];
	float fVec12[] = new float[2];
	float fVec13[] = new float[2];
	float fVec14[] = new float[2];
	float fVslider4;
	float fVec15[] = new float[2];
	float fRec10[] = new float[2];
	float fVec16[] = new float[2];
	float fVec17[] = new float[2];
	float fVec18[] = new float[2];
	float fVec19[] = new float[2];
	float fVec20[] = new float[2];
	float fVec21[] = new float[2];
	float fCheckbox4;
	int iRec11[] = new int[2];
	float fRec12[] = new float[4];
	float fCheckbox5;
	float fHslider5;
	float fHslider6;
	int IOTA;
	float fVec22[] = new float[4096];
	float fHslider7;
	float fHslider8;
	float fRec13[] = new float[2];
	float fCheckbox6;
	float fHslider9;
	float fHslider10;
	float fHslider11;
	float fHslider12;
	float fHslider13;
	float fHslider14;
	float fHslider15;
	float fRec19[] = new float[2];
	float fRec20[] = new float[2];
	float fRec18[] = new float[3];
	float fRec17[] = new float[3];
	float fRec16[] = new float[3];
	float fRec15[] = new float[3];
	float fRec14[] = new float[2];
	float fCheckbox7;
	float fVec23[] = new float[4096];
	float fRec21[] = new float[2];
	float fRec26[] = new float[3];
	float fRec25[] = new float[3];
	float fRec24[] = new float[3];
	float fRec23[] = new float[3];
	float fRec22[] = new float[2];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec3[] = new float[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec2[] = new float[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec1[] = new float[3];
	float fConst28;
	float fRec0[] = new float[2];
	float fVbargraph0;
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
	float fRec33[] = new float[3];
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec32[] = new float[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec31[] = new float[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec30[] = new float[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec29[] = new float[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec28[] = new float[3];
	float fConst66;
	float fRec27[] = new float[2];
	float fVbargraph1;
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
	float fRec40[] = new float[3];
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec39[] = new float[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec38[] = new float[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec37[] = new float[3];
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec36[] = new float[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec35[] = new float[3];
	float fConst104;
	float fRec34[] = new float[2];
	float fVbargraph2;
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
	float fConst124;
	float fConst125;
	float fRec47[] = new float[3];
	float fConst126;
	float fConst127;
	float fConst128;
	float fRec46[] = new float[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec45[] = new float[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec44[] = new float[3];
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec43[] = new float[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec42[] = new float[3];
	float fConst142;
	float fRec41[] = new float[2];
	float fVbargraph3;
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
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec54[] = new float[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec53[] = new float[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec52[] = new float[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fRec51[] = new float[3];
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec50[] = new float[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec49[] = new float[3];
	float fConst180;
	float fRec48[] = new float[2];
	float fVbargraph4;
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
	float fConst197;
	float fConst198;
	float fConst199;
	float fConst200;
	float fConst201;
	float fRec61[] = new float[3];
	float fConst202;
	float fConst203;
	float fConst204;
	float fRec60[] = new float[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec59[] = new float[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fRec58[] = new float[3];
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec57[] = new float[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec56[] = new float[3];
	float fConst218;
	float fRec55[] = new float[2];
	float fVbargraph5;
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
	float fConst235;
	float fConst236;
	float fConst237;
	float fConst238;
	float fConst239;
	float fRec68[] = new float[3];
	float fConst240;
	float fConst241;
	float fConst242;
	float fRec67[] = new float[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec66[] = new float[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fConst249;
	float fRec65[] = new float[3];
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec64[] = new float[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec63[] = new float[3];
	float fConst256;
	float fRec62[] = new float[2];
	float fVbargraph6;
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
	float fConst273;
	float fConst274;
	float fConst275;
	float fConst276;
	float fConst277;
	float fRec75[] = new float[3];
	float fConst278;
	float fConst279;
	float fConst280;
	float fRec74[] = new float[3];
	float fConst281;
	float fConst282;
	float fConst283;
	float fRec73[] = new float[3];
	float fConst284;
	float fConst285;
	float fConst286;
	float fConst287;
	float fRec72[] = new float[3];
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec71[] = new float[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec70[] = new float[3];
	float fConst294;
	float fRec69[] = new float[2];
	float fVbargraph7;
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
	float fConst311;
	float fConst312;
	float fConst313;
	float fConst314;
	float fConst315;
	float fRec82[] = new float[3];
	float fConst316;
	float fConst317;
	float fConst318;
	float fRec81[] = new float[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec80[] = new float[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fConst325;
	float fRec79[] = new float[3];
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec78[] = new float[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec77[] = new float[3];
	float fConst332;
	float fRec76[] = new float[2];
	float fVbargraph8;
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
	float fConst349;
	float fConst350;
	float fConst351;
	float fConst352;
	float fConst353;
	float fRec89[] = new float[3];
	float fConst354;
	float fConst355;
	float fConst356;
	float fRec88[] = new float[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec87[] = new float[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fConst363;
	float fRec86[] = new float[3];
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec85[] = new float[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec84[] = new float[3];
	float fConst370;
	float fRec83[] = new float[2];
	float fVbargraph9;
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
	float fConst387;
	float fConst388;
	float fConst389;
	float fConst390;
	float fConst391;
	float fRec96[] = new float[3];
	float fConst392;
	float fConst393;
	float fConst394;
	float fRec95[] = new float[3];
	float fConst395;
	float fConst396;
	float fConst397;
	float fRec94[] = new float[3];
	float fConst398;
	float fConst399;
	float fConst400;
	float fConst401;
	float fRec93[] = new float[3];
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec92[] = new float[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec91[] = new float[3];
	float fConst408;
	float fRec90[] = new float[2];
	float fVbargraph10;
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
	float fRec103[] = new float[3];
	float fConst430;
	float fConst431;
	float fConst432;
	float fRec102[] = new float[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec101[] = new float[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fRec100[] = new float[3];
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec99[] = new float[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec98[] = new float[3];
	float fConst446;
	float fRec97[] = new float[2];
	float fVbargraph11;
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
	float fRec110[] = new float[3];
	float fConst468;
	float fConst469;
	float fConst470;
	float fRec109[] = new float[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec108[] = new float[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fRec107[] = new float[3];
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec106[] = new float[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec105[] = new float[3];
	float fConst484;
	float fRec104[] = new float[2];
	float fVbargraph12;
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
	float fRec117[] = new float[3];
	float fConst506;
	float fConst507;
	float fConst508;
	float fRec116[] = new float[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec115[] = new float[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fRec114[] = new float[3];
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec113[] = new float[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec112[] = new float[3];
	float fConst522;
	float fRec111[] = new float[2];
	float fVbargraph13;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fRec121[] = new float[3];
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec120[] = new float[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec119[] = new float[3];
	float fConst538;
	float fRec118[] = new float[2];
	float fVbargraph14;
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "phaserFlangerLab");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m.declare("phaflangers.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
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
		fConst14 = (6.28318548f / fConst0);
		fConst15 = (1.0f / fConst0);
		fConst16 = (0.25f * fConst0);
		fConst17 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst18 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst19 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst20 = (1.0f / fConst5);
		fConst21 = (2.0f * (4.07678175f - fConst20));
		fConst22 = (fConst12 + 0.000407678192f);
		fConst23 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst24 = (2.0f * (1.4500711f - fConst20));
		fConst25 = (fConst9 + 1.4500711f);
		fConst26 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst27 = (2.0f * (0.935140193f - fConst20));
		fConst28 = (fConst6 + 0.935140193f);
		fConst29 = (float)java.lang.Math.tan((31665.2695f / fConst0));
		fConst30 = (1.0f / fConst29);
		fConst31 = (1.0f / (((fConst30 + 0.157482162f) / fConst29) + 0.935140193f));
		fConst32 = mydsp_faustpower2_f(fConst29);
		fConst33 = (50.0638084f / fConst32);
		fConst34 = (2.0f * (0.935140193f - fConst33));
		fConst35 = (1.0f / (((fConst30 + 0.743130445f) / fConst29) + 1.4500711f));
		fConst36 = (11.0520525f / fConst32);
		fConst37 = (2.0f * (1.4500711f - fConst36));
		fConst38 = (1.0f / (((fConst30 + 3.18972731f) / fConst29) + 4.07678175f));
		fConst39 = (0.00176617282f / fConst32);
		fConst40 = (2.0f * (0.000407678192f - fConst39));
		fConst41 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst42 = (2.0f * (53.5361519f - fConst20));
		fConst43 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst44 = (2.0f * (7.62173128f - fConst20));
		fConst45 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst46 = (9.99999975e-05f / fConst5);
		fConst47 = (2.0f * (0.000433227193f - fConst46));
		fConst48 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst49 = (2.0f * (0.245291501f - fConst20));
		fConst50 = (fConst46 + 0.000433227193f);
		fConst51 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst52 = (2.0f * (0.689621389f - fConst20));
		fConst53 = (fConst20 + 7.62173128f);
		fConst54 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst55 = (2.0f * (1.06935835f - fConst20));
		fConst56 = (fConst20 + 53.5361519f);
		fConst57 = (((fConst30 + -3.18972731f) / fConst29) + 4.07678175f);
		fConst58 = (1.0f / fConst32);
		fConst59 = (2.0f * (4.07678175f - fConst58));
		fConst60 = (fConst39 + 0.000407678192f);
		fConst61 = (((fConst30 + -0.743130445f) / fConst29) + 1.4500711f);
		fConst62 = (2.0f * (1.4500711f - fConst58));
		fConst63 = (fConst36 + 1.4500711f);
		fConst64 = (((fConst30 + -0.157482162f) / fConst29) + 0.935140193f);
		fConst65 = (2.0f * (0.935140193f - fConst58));
		fConst66 = (fConst33 + 0.935140193f);
		fConst67 = (float)java.lang.Math.tan((19947.8691f / fConst0));
		fConst68 = (1.0f / fConst67);
		fConst69 = (1.0f / (((fConst68 + 0.157482162f) / fConst67) + 0.935140193f));
		fConst70 = mydsp_faustpower2_f(fConst67);
		fConst71 = (50.0638084f / fConst70);
		fConst72 = (2.0f * (0.935140193f - fConst71));
		fConst73 = (1.0f / (((fConst68 + 0.743130445f) / fConst67) + 1.4500711f));
		fConst74 = (11.0520525f / fConst70);
		fConst75 = (2.0f * (1.4500711f - fConst74));
		fConst76 = (1.0f / (((fConst68 + 3.18972731f) / fConst67) + 4.07678175f));
		fConst77 = (0.00176617282f / fConst70);
		fConst78 = (2.0f * (0.000407678192f - fConst77));
		fConst79 = (1.0f / (((fConst30 + 0.168404877f) / fConst29) + 1.06935835f));
		fConst80 = (2.0f * (53.5361519f - fConst58));
		fConst81 = (1.0f / (((fConst30 + 0.51247865f) / fConst29) + 0.689621389f));
		fConst82 = (2.0f * (7.62173128f - fConst58));
		fConst83 = (1.0f / (((fConst30 + 0.782413065f) / fConst29) + 0.245291501f));
		fConst84 = (9.99999975e-05f / fConst32);
		fConst85 = (2.0f * (0.000433227193f - fConst84));
		fConst86 = (((fConst30 + -0.782413065f) / fConst29) + 0.245291501f);
		fConst87 = (2.0f * (0.245291501f - fConst58));
		fConst88 = (fConst84 + 0.000433227193f);
		fConst89 = (((fConst30 + -0.51247865f) / fConst29) + 0.689621389f);
		fConst90 = (2.0f * (0.689621389f - fConst58));
		fConst91 = (fConst58 + 7.62173128f);
		fConst92 = (((fConst30 + -0.168404877f) / fConst29) + 1.06935835f);
		fConst93 = (2.0f * (1.06935835f - fConst58));
		fConst94 = (fConst58 + 53.5361519f);
		fConst95 = (((fConst68 + -3.18972731f) / fConst67) + 4.07678175f);
		fConst96 = (1.0f / fConst70);
		fConst97 = (2.0f * (4.07678175f - fConst96));
		fConst98 = (fConst77 + 0.000407678192f);
		fConst99 = (((fConst68 + -0.743130445f) / fConst67) + 1.4500711f);
		fConst100 = (2.0f * (1.4500711f - fConst96));
		fConst101 = (fConst74 + 1.4500711f);
		fConst102 = (((fConst68 + -0.157482162f) / fConst67) + 0.935140193f);
		fConst103 = (2.0f * (0.935140193f - fConst96));
		fConst104 = (fConst71 + 0.935140193f);
		fConst105 = (float)java.lang.Math.tan((12566.3711f / fConst0));
		fConst106 = (1.0f / fConst105);
		fConst107 = (1.0f / (((fConst106 + 0.157482162f) / fConst105) + 0.935140193f));
		fConst108 = mydsp_faustpower2_f(fConst105);
		fConst109 = (50.0638084f / fConst108);
		fConst110 = (2.0f * (0.935140193f - fConst109));
		fConst111 = (1.0f / (((fConst106 + 0.743130445f) / fConst105) + 1.4500711f));
		fConst112 = (11.0520525f / fConst108);
		fConst113 = (2.0f * (1.4500711f - fConst112));
		fConst114 = (1.0f / (((fConst106 + 3.18972731f) / fConst105) + 4.07678175f));
		fConst115 = (0.00176617282f / fConst108);
		fConst116 = (2.0f * (0.000407678192f - fConst115));
		fConst117 = (1.0f / (((fConst68 + 0.168404877f) / fConst67) + 1.06935835f));
		fConst118 = (2.0f * (53.5361519f - fConst96));
		fConst119 = (1.0f / (((fConst68 + 0.51247865f) / fConst67) + 0.689621389f));
		fConst120 = (2.0f * (7.62173128f - fConst96));
		fConst121 = (1.0f / (((fConst68 + 0.782413065f) / fConst67) + 0.245291501f));
		fConst122 = (9.99999975e-05f / fConst70);
		fConst123 = (2.0f * (0.000433227193f - fConst122));
		fConst124 = (((fConst68 + -0.782413065f) / fConst67) + 0.245291501f);
		fConst125 = (2.0f * (0.245291501f - fConst96));
		fConst126 = (fConst122 + 0.000433227193f);
		fConst127 = (((fConst68 + -0.51247865f) / fConst67) + 0.689621389f);
		fConst128 = (2.0f * (0.689621389f - fConst96));
		fConst129 = (fConst96 + 7.62173128f);
		fConst130 = (((fConst68 + -0.168404877f) / fConst67) + 1.06935835f);
		fConst131 = (2.0f * (1.06935835f - fConst96));
		fConst132 = (fConst96 + 53.5361519f);
		fConst133 = (((fConst106 + -3.18972731f) / fConst105) + 4.07678175f);
		fConst134 = (1.0f / fConst108);
		fConst135 = (2.0f * (4.07678175f - fConst134));
		fConst136 = (fConst115 + 0.000407678192f);
		fConst137 = (((fConst106 + -0.743130445f) / fConst105) + 1.4500711f);
		fConst138 = (2.0f * (1.4500711f - fConst134));
		fConst139 = (fConst112 + 1.4500711f);
		fConst140 = (((fConst106 + -0.157482162f) / fConst105) + 0.935140193f);
		fConst141 = (2.0f * (0.935140193f - fConst134));
		fConst142 = (fConst109 + 0.935140193f);
		fConst143 = (float)java.lang.Math.tan((7916.31738f / fConst0));
		fConst144 = (1.0f / fConst143);
		fConst145 = (1.0f / (((fConst144 + 0.157482162f) / fConst143) + 0.935140193f));
		fConst146 = mydsp_faustpower2_f(fConst143);
		fConst147 = (50.0638084f / fConst146);
		fConst148 = (2.0f * (0.935140193f - fConst147));
		fConst149 = (1.0f / (((fConst144 + 0.743130445f) / fConst143) + 1.4500711f));
		fConst150 = (11.0520525f / fConst146);
		fConst151 = (2.0f * (1.4500711f - fConst150));
		fConst152 = (1.0f / (((fConst144 + 3.18972731f) / fConst143) + 4.07678175f));
		fConst153 = (0.00176617282f / fConst146);
		fConst154 = (2.0f * (0.000407678192f - fConst153));
		fConst155 = (1.0f / (((fConst106 + 0.168404877f) / fConst105) + 1.06935835f));
		fConst156 = (2.0f * (53.5361519f - fConst134));
		fConst157 = (1.0f / (((fConst106 + 0.51247865f) / fConst105) + 0.689621389f));
		fConst158 = (2.0f * (7.62173128f - fConst134));
		fConst159 = (1.0f / (((fConst106 + 0.782413065f) / fConst105) + 0.245291501f));
		fConst160 = (9.99999975e-05f / fConst108);
		fConst161 = (2.0f * (0.000433227193f - fConst160));
		fConst162 = (((fConst106 + -0.782413065f) / fConst105) + 0.245291501f);
		fConst163 = (2.0f * (0.245291501f - fConst134));
		fConst164 = (fConst160 + 0.000433227193f);
		fConst165 = (((fConst106 + -0.51247865f) / fConst105) + 0.689621389f);
		fConst166 = (2.0f * (0.689621389f - fConst134));
		fConst167 = (fConst134 + 7.62173128f);
		fConst168 = (((fConst106 + -0.168404877f) / fConst105) + 1.06935835f);
		fConst169 = (2.0f * (1.06935835f - fConst134));
		fConst170 = (fConst134 + 53.5361519f);
		fConst171 = (((fConst144 + -3.18972731f) / fConst143) + 4.07678175f);
		fConst172 = (1.0f / fConst146);
		fConst173 = (2.0f * (4.07678175f - fConst172));
		fConst174 = (fConst153 + 0.000407678192f);
		fConst175 = (((fConst144 + -0.743130445f) / fConst143) + 1.4500711f);
		fConst176 = (2.0f * (1.4500711f - fConst172));
		fConst177 = (fConst150 + 1.4500711f);
		fConst178 = (((fConst144 + -0.157482162f) / fConst143) + 0.935140193f);
		fConst179 = (2.0f * (0.935140193f - fConst172));
		fConst180 = (fConst147 + 0.935140193f);
		fConst181 = (float)java.lang.Math.tan((4986.96729f / fConst0));
		fConst182 = (1.0f / fConst181);
		fConst183 = (1.0f / (((fConst182 + 0.157482162f) / fConst181) + 0.935140193f));
		fConst184 = mydsp_faustpower2_f(fConst181);
		fConst185 = (50.0638084f / fConst184);
		fConst186 = (2.0f * (0.935140193f - fConst185));
		fConst187 = (1.0f / (((fConst182 + 0.743130445f) / fConst181) + 1.4500711f));
		fConst188 = (11.0520525f / fConst184);
		fConst189 = (2.0f * (1.4500711f - fConst188));
		fConst190 = (1.0f / (((fConst182 + 3.18972731f) / fConst181) + 4.07678175f));
		fConst191 = (0.00176617282f / fConst184);
		fConst192 = (2.0f * (0.000407678192f - fConst191));
		fConst193 = (1.0f / (((fConst144 + 0.168404877f) / fConst143) + 1.06935835f));
		fConst194 = (2.0f * (53.5361519f - fConst172));
		fConst195 = (1.0f / (((fConst144 + 0.51247865f) / fConst143) + 0.689621389f));
		fConst196 = (2.0f * (7.62173128f - fConst172));
		fConst197 = (1.0f / (((fConst144 + 0.782413065f) / fConst143) + 0.245291501f));
		fConst198 = (9.99999975e-05f / fConst146);
		fConst199 = (2.0f * (0.000433227193f - fConst198));
		fConst200 = (((fConst144 + -0.782413065f) / fConst143) + 0.245291501f);
		fConst201 = (2.0f * (0.245291501f - fConst172));
		fConst202 = (fConst198 + 0.000433227193f);
		fConst203 = (((fConst144 + -0.51247865f) / fConst143) + 0.689621389f);
		fConst204 = (2.0f * (0.689621389f - fConst172));
		fConst205 = (fConst172 + 7.62173128f);
		fConst206 = (((fConst144 + -0.168404877f) / fConst143) + 1.06935835f);
		fConst207 = (2.0f * (1.06935835f - fConst172));
		fConst208 = (fConst172 + 53.5361519f);
		fConst209 = (((fConst182 + -3.18972731f) / fConst181) + 4.07678175f);
		fConst210 = (1.0f / fConst184);
		fConst211 = (2.0f * (4.07678175f - fConst210));
		fConst212 = (fConst191 + 0.000407678192f);
		fConst213 = (((fConst182 + -0.743130445f) / fConst181) + 1.4500711f);
		fConst214 = (2.0f * (1.4500711f - fConst210));
		fConst215 = (fConst188 + 1.4500711f);
		fConst216 = (((fConst182 + -0.157482162f) / fConst181) + 0.935140193f);
		fConst217 = (2.0f * (0.935140193f - fConst210));
		fConst218 = (fConst185 + 0.935140193f);
		fConst219 = (float)java.lang.Math.tan((3141.59277f / fConst0));
		fConst220 = (1.0f / fConst219);
		fConst221 = (1.0f / (((fConst220 + 0.157482162f) / fConst219) + 0.935140193f));
		fConst222 = mydsp_faustpower2_f(fConst219);
		fConst223 = (50.0638084f / fConst222);
		fConst224 = (2.0f * (0.935140193f - fConst223));
		fConst225 = (1.0f / (((fConst220 + 0.743130445f) / fConst219) + 1.4500711f));
		fConst226 = (11.0520525f / fConst222);
		fConst227 = (2.0f * (1.4500711f - fConst226));
		fConst228 = (1.0f / (((fConst220 + 3.18972731f) / fConst219) + 4.07678175f));
		fConst229 = (0.00176617282f / fConst222);
		fConst230 = (2.0f * (0.000407678192f - fConst229));
		fConst231 = (1.0f / (((fConst182 + 0.168404877f) / fConst181) + 1.06935835f));
		fConst232 = (2.0f * (53.5361519f - fConst210));
		fConst233 = (1.0f / (((fConst182 + 0.51247865f) / fConst181) + 0.689621389f));
		fConst234 = (2.0f * (7.62173128f - fConst210));
		fConst235 = (1.0f / (((fConst182 + 0.782413065f) / fConst181) + 0.245291501f));
		fConst236 = (9.99999975e-05f / fConst184);
		fConst237 = (2.0f * (0.000433227193f - fConst236));
		fConst238 = (((fConst182 + -0.782413065f) / fConst181) + 0.245291501f);
		fConst239 = (2.0f * (0.245291501f - fConst210));
		fConst240 = (fConst236 + 0.000433227193f);
		fConst241 = (((fConst182 + -0.51247865f) / fConst181) + 0.689621389f);
		fConst242 = (2.0f * (0.689621389f - fConst210));
		fConst243 = (fConst210 + 7.62173128f);
		fConst244 = (((fConst182 + -0.168404877f) / fConst181) + 1.06935835f);
		fConst245 = (2.0f * (1.06935835f - fConst210));
		fConst246 = (fConst210 + 53.5361519f);
		fConst247 = (((fConst220 + -3.18972731f) / fConst219) + 4.07678175f);
		fConst248 = (1.0f / fConst222);
		fConst249 = (2.0f * (4.07678175f - fConst248));
		fConst250 = (fConst229 + 0.000407678192f);
		fConst251 = (((fConst220 + -0.743130445f) / fConst219) + 1.4500711f);
		fConst252 = (2.0f * (1.4500711f - fConst248));
		fConst253 = (fConst226 + 1.4500711f);
		fConst254 = (((fConst220 + -0.157482162f) / fConst219) + 0.935140193f);
		fConst255 = (2.0f * (0.935140193f - fConst248));
		fConst256 = (fConst223 + 0.935140193f);
		fConst257 = (float)java.lang.Math.tan((1979.07935f / fConst0));
		fConst258 = (1.0f / fConst257);
		fConst259 = (1.0f / (((fConst258 + 0.157482162f) / fConst257) + 0.935140193f));
		fConst260 = mydsp_faustpower2_f(fConst257);
		fConst261 = (50.0638084f / fConst260);
		fConst262 = (2.0f * (0.935140193f - fConst261));
		fConst263 = (1.0f / (((fConst258 + 0.743130445f) / fConst257) + 1.4500711f));
		fConst264 = (11.0520525f / fConst260);
		fConst265 = (2.0f * (1.4500711f - fConst264));
		fConst266 = (1.0f / (((fConst258 + 3.18972731f) / fConst257) + 4.07678175f));
		fConst267 = (0.00176617282f / fConst260);
		fConst268 = (2.0f * (0.000407678192f - fConst267));
		fConst269 = (1.0f / (((fConst220 + 0.168404877f) / fConst219) + 1.06935835f));
		fConst270 = (2.0f * (53.5361519f - fConst248));
		fConst271 = (1.0f / (((fConst220 + 0.51247865f) / fConst219) + 0.689621389f));
		fConst272 = (2.0f * (7.62173128f - fConst248));
		fConst273 = (1.0f / (((fConst220 + 0.782413065f) / fConst219) + 0.245291501f));
		fConst274 = (9.99999975e-05f / fConst222);
		fConst275 = (2.0f * (0.000433227193f - fConst274));
		fConst276 = (((fConst220 + -0.782413065f) / fConst219) + 0.245291501f);
		fConst277 = (2.0f * (0.245291501f - fConst248));
		fConst278 = (fConst274 + 0.000433227193f);
		fConst279 = (((fConst220 + -0.51247865f) / fConst219) + 0.689621389f);
		fConst280 = (2.0f * (0.689621389f - fConst248));
		fConst281 = (fConst248 + 7.62173128f);
		fConst282 = (((fConst220 + -0.168404877f) / fConst219) + 1.06935835f);
		fConst283 = (2.0f * (1.06935835f - fConst248));
		fConst284 = (fConst248 + 53.5361519f);
		fConst285 = (((fConst258 + -3.18972731f) / fConst257) + 4.07678175f);
		fConst286 = (1.0f / fConst260);
		fConst287 = (2.0f * (4.07678175f - fConst286));
		fConst288 = (fConst267 + 0.000407678192f);
		fConst289 = (((fConst258 + -0.743130445f) / fConst257) + 1.4500711f);
		fConst290 = (2.0f * (1.4500711f - fConst286));
		fConst291 = (fConst264 + 1.4500711f);
		fConst292 = (((fConst258 + -0.157482162f) / fConst257) + 0.935140193f);
		fConst293 = (2.0f * (0.935140193f - fConst286));
		fConst294 = (fConst261 + 0.935140193f);
		fConst295 = (float)java.lang.Math.tan((1246.74182f / fConst0));
		fConst296 = (1.0f / fConst295);
		fConst297 = (1.0f / (((fConst296 + 0.157482162f) / fConst295) + 0.935140193f));
		fConst298 = mydsp_faustpower2_f(fConst295);
		fConst299 = (50.0638084f / fConst298);
		fConst300 = (2.0f * (0.935140193f - fConst299));
		fConst301 = (1.0f / (((fConst296 + 0.743130445f) / fConst295) + 1.4500711f));
		fConst302 = (11.0520525f / fConst298);
		fConst303 = (2.0f * (1.4500711f - fConst302));
		fConst304 = (1.0f / (((fConst296 + 3.18972731f) / fConst295) + 4.07678175f));
		fConst305 = (0.00176617282f / fConst298);
		fConst306 = (2.0f * (0.000407678192f - fConst305));
		fConst307 = (1.0f / (((fConst258 + 0.168404877f) / fConst257) + 1.06935835f));
		fConst308 = (2.0f * (53.5361519f - fConst286));
		fConst309 = (1.0f / (((fConst258 + 0.51247865f) / fConst257) + 0.689621389f));
		fConst310 = (2.0f * (7.62173128f - fConst286));
		fConst311 = (1.0f / (((fConst258 + 0.782413065f) / fConst257) + 0.245291501f));
		fConst312 = (9.99999975e-05f / fConst260);
		fConst313 = (2.0f * (0.000433227193f - fConst312));
		fConst314 = (((fConst258 + -0.782413065f) / fConst257) + 0.245291501f);
		fConst315 = (2.0f * (0.245291501f - fConst286));
		fConst316 = (fConst312 + 0.000433227193f);
		fConst317 = (((fConst258 + -0.51247865f) / fConst257) + 0.689621389f);
		fConst318 = (2.0f * (0.689621389f - fConst286));
		fConst319 = (fConst286 + 7.62173128f);
		fConst320 = (((fConst258 + -0.168404877f) / fConst257) + 1.06935835f);
		fConst321 = (2.0f * (1.06935835f - fConst286));
		fConst322 = (fConst286 + 53.5361519f);
		fConst323 = (((fConst296 + -3.18972731f) / fConst295) + 4.07678175f);
		fConst324 = (1.0f / fConst298);
		fConst325 = (2.0f * (4.07678175f - fConst324));
		fConst326 = (fConst305 + 0.000407678192f);
		fConst327 = (((fConst296 + -0.743130445f) / fConst295) + 1.4500711f);
		fConst328 = (2.0f * (1.4500711f - fConst324));
		fConst329 = (fConst302 + 1.4500711f);
		fConst330 = (((fConst296 + -0.157482162f) / fConst295) + 0.935140193f);
		fConst331 = (2.0f * (0.935140193f - fConst324));
		fConst332 = (fConst299 + 0.935140193f);
		fConst333 = (float)java.lang.Math.tan((785.398193f / fConst0));
		fConst334 = (1.0f / fConst333);
		fConst335 = (1.0f / (((fConst334 + 0.157482162f) / fConst333) + 0.935140193f));
		fConst336 = mydsp_faustpower2_f(fConst333);
		fConst337 = (50.0638084f / fConst336);
		fConst338 = (2.0f * (0.935140193f - fConst337));
		fConst339 = (1.0f / (((fConst334 + 0.743130445f) / fConst333) + 1.4500711f));
		fConst340 = (11.0520525f / fConst336);
		fConst341 = (2.0f * (1.4500711f - fConst340));
		fConst342 = (1.0f / (((fConst334 + 3.18972731f) / fConst333) + 4.07678175f));
		fConst343 = (0.00176617282f / fConst336);
		fConst344 = (2.0f * (0.000407678192f - fConst343));
		fConst345 = (1.0f / (((fConst296 + 0.168404877f) / fConst295) + 1.06935835f));
		fConst346 = (2.0f * (53.5361519f - fConst324));
		fConst347 = (1.0f / (((fConst296 + 0.51247865f) / fConst295) + 0.689621389f));
		fConst348 = (2.0f * (7.62173128f - fConst324));
		fConst349 = (1.0f / (((fConst296 + 0.782413065f) / fConst295) + 0.245291501f));
		fConst350 = (9.99999975e-05f / fConst298);
		fConst351 = (2.0f * (0.000433227193f - fConst350));
		fConst352 = (((fConst296 + -0.782413065f) / fConst295) + 0.245291501f);
		fConst353 = (2.0f * (0.245291501f - fConst324));
		fConst354 = (fConst350 + 0.000433227193f);
		fConst355 = (((fConst296 + -0.51247865f) / fConst295) + 0.689621389f);
		fConst356 = (2.0f * (0.689621389f - fConst324));
		fConst357 = (fConst324 + 7.62173128f);
		fConst358 = (((fConst296 + -0.168404877f) / fConst295) + 1.06935835f);
		fConst359 = (2.0f * (1.06935835f - fConst324));
		fConst360 = (fConst324 + 53.5361519f);
		fConst361 = (((fConst334 + -3.18972731f) / fConst333) + 4.07678175f);
		fConst362 = (1.0f / fConst336);
		fConst363 = (2.0f * (4.07678175f - fConst362));
		fConst364 = (fConst343 + 0.000407678192f);
		fConst365 = (((fConst334 + -0.743130445f) / fConst333) + 1.4500711f);
		fConst366 = (2.0f * (1.4500711f - fConst362));
		fConst367 = (fConst340 + 1.4500711f);
		fConst368 = (((fConst334 + -0.157482162f) / fConst333) + 0.935140193f);
		fConst369 = (2.0f * (0.935140193f - fConst362));
		fConst370 = (fConst337 + 0.935140193f);
		fConst371 = (float)java.lang.Math.tan((494.769836f / fConst0));
		fConst372 = (1.0f / fConst371);
		fConst373 = (1.0f / (((fConst372 + 0.157482162f) / fConst371) + 0.935140193f));
		fConst374 = mydsp_faustpower2_f(fConst371);
		fConst375 = (50.0638084f / fConst374);
		fConst376 = (2.0f * (0.935140193f - fConst375));
		fConst377 = (1.0f / (((fConst372 + 0.743130445f) / fConst371) + 1.4500711f));
		fConst378 = (11.0520525f / fConst374);
		fConst379 = (2.0f * (1.4500711f - fConst378));
		fConst380 = (1.0f / (((fConst372 + 3.18972731f) / fConst371) + 4.07678175f));
		fConst381 = (0.00176617282f / fConst374);
		fConst382 = (2.0f * (0.000407678192f - fConst381));
		fConst383 = (1.0f / (((fConst334 + 0.168404877f) / fConst333) + 1.06935835f));
		fConst384 = (2.0f * (53.5361519f - fConst362));
		fConst385 = (1.0f / (((fConst334 + 0.51247865f) / fConst333) + 0.689621389f));
		fConst386 = (2.0f * (7.62173128f - fConst362));
		fConst387 = (1.0f / (((fConst334 + 0.782413065f) / fConst333) + 0.245291501f));
		fConst388 = (9.99999975e-05f / fConst336);
		fConst389 = (2.0f * (0.000433227193f - fConst388));
		fConst390 = (((fConst334 + -0.782413065f) / fConst333) + 0.245291501f);
		fConst391 = (2.0f * (0.245291501f - fConst362));
		fConst392 = (fConst388 + 0.000433227193f);
		fConst393 = (((fConst334 + -0.51247865f) / fConst333) + 0.689621389f);
		fConst394 = (2.0f * (0.689621389f - fConst362));
		fConst395 = (fConst362 + 7.62173128f);
		fConst396 = (((fConst334 + -0.168404877f) / fConst333) + 1.06935835f);
		fConst397 = (2.0f * (1.06935835f - fConst362));
		fConst398 = (fConst362 + 53.5361519f);
		fConst399 = (((fConst372 + -3.18972731f) / fConst371) + 4.07678175f);
		fConst400 = (1.0f / fConst374);
		fConst401 = (2.0f * (4.07678175f - fConst400));
		fConst402 = (fConst381 + 0.000407678192f);
		fConst403 = (((fConst372 + -0.743130445f) / fConst371) + 1.4500711f);
		fConst404 = (2.0f * (1.4500711f - fConst400));
		fConst405 = (fConst378 + 1.4500711f);
		fConst406 = (((fConst372 + -0.157482162f) / fConst371) + 0.935140193f);
		fConst407 = (2.0f * (0.935140193f - fConst400));
		fConst408 = (fConst375 + 0.935140193f);
		fConst409 = (float)java.lang.Math.tan((311.685455f / fConst0));
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
		fConst421 = (1.0f / (((fConst372 + 0.168404877f) / fConst371) + 1.06935835f));
		fConst422 = (2.0f * (53.5361519f - fConst400));
		fConst423 = (1.0f / (((fConst372 + 0.51247865f) / fConst371) + 0.689621389f));
		fConst424 = (2.0f * (7.62173128f - fConst400));
		fConst425 = (1.0f / (((fConst372 + 0.782413065f) / fConst371) + 0.245291501f));
		fConst426 = (9.99999975e-05f / fConst374);
		fConst427 = (2.0f * (0.000433227193f - fConst426));
		fConst428 = (((fConst372 + -0.782413065f) / fConst371) + 0.245291501f);
		fConst429 = (2.0f * (0.245291501f - fConst400));
		fConst430 = (fConst426 + 0.000433227193f);
		fConst431 = (((fConst372 + -0.51247865f) / fConst371) + 0.689621389f);
		fConst432 = (2.0f * (0.689621389f - fConst400));
		fConst433 = (fConst400 + 7.62173128f);
		fConst434 = (((fConst372 + -0.168404877f) / fConst371) + 1.06935835f);
		fConst435 = (2.0f * (1.06935835f - fConst400));
		fConst436 = (fConst400 + 53.5361519f);
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
		fConst447 = (float)java.lang.Math.tan((196.349548f / fConst0));
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
		fConst485 = (float)java.lang.Math.tan((123.692459f / fConst0));
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
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)50.0f;
		fHslider1 = (float)100.0f;
		fCheckbox0 = (float)0.0f;
		fHslider2 = (float)0.0f;
		fCheckbox1 = (float)0.0f;
		fHslider3 = (float)0.0f;
		fHslider4 = (float)0.5f;
		fVslider0 = (float)-20.0f;
		fCheckbox2 = (float)0.0f;
		fCheckbox3 = (float)0.0f;
		fEntry0 = (float)2.0f;
		fVslider1 = (float)49.0f;
		fVslider2 = (float)0.10000000000000001f;
		fVslider3 = (float)-0.10000000000000001f;
		fVslider4 = (float)0.10000000000000001f;
		fCheckbox4 = (float)0.0f;
		fCheckbox5 = (float)0.0f;
		fHslider5 = (float)1.0f;
		fHslider6 = (float)0.0f;
		fHslider7 = (float)1.0f;
		fHslider8 = (float)10.0f;
		fCheckbox6 = (float)0.0f;
		fHslider9 = (float)1.0f;
		fHslider10 = (float)1000.0f;
		fHslider11 = (float)0.0f;
		fHslider12 = (float)1.5f;
		fHslider13 = (float)100.0f;
		fHslider14 = (float)800.0f;
		fHslider15 = (float)0.5f;
		fCheckbox7 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec4[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec5[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec6[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec8[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
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
			fRec9[l14] = 0.0f;
			
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
			fRec10[l22] = 0.0f;
			
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
			iRec11[l29] = 0;
			
		}
		for (int l30 = 0; (l30 < 4); l30 = (l30 + 1)) {
			fRec12[l30] = 0.0f;
			
		}
		IOTA = 0;
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec22[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec13[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec19[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec20[l34] = 0.0f;
			
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
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec14[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 4096); l40 = (l40 + 1)) {
			fVec23[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec21[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec26[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec25[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec24[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec23[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec22[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec3[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec2[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec1[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec0[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec33[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec32[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec31[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec30[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec29[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec28[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec27[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec40[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec39[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec38[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec37[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec36[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec35[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec34[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec47[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec46[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec45[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec44[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec43[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec42[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec41[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec54[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec53[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec52[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec51[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec50[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec49[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec48[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec61[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec60[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec59[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec58[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec57[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec56[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec55[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec68[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec67[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec66[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec65[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec64[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec63[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec62[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec75[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec74[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec73[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec72[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec71[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec70[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec69[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec82[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec81[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec80[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec79[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec78[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec77[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec76[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec89[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec88[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec87[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec86[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec85[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec84[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec83[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec96[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec95[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec94[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec93[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec92[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec91[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec90[l120] = 0.0f;
			
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
		ui_interface.openVerticalBox("phaserFlangerLab");
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's oscillators.lib   for documentation and references");
		ui_interface.openVerticalBox("SAWTOOTH OSCILLATOR");
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.declare("fVslider0", "style", "knob");
		ui_interface.declare("fVslider0", "tooltip", "Sawtooth   waveform amplitude");
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("Amplitude", new FaustVarAccess() {
				public String getId() { return "fVslider0"; }
				public void set(float val) { fVslider0 = val; }
				public float get() { return (float)fVslider0; }
			}
			, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider1", "2", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface.declare("fVslider1", "unit", "PK");
		ui_interface.addVerticalSlider("Frequency", new FaustVarAccess() {
				public String getId() { return "fVslider1"; }
				public void set(float val) { fVslider1 = val; }
				public float get() { return (float)fVslider1; }
			}
			, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface.declare("fVslider3", "3", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Percentange frequency-shift  up or down for second oscillator");
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
		ui_interface.declare("fEntry0", "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface.addNumEntry("Saw Order", new FaustVarAccess() {
				public String getId() { return "fEntry0"; }
				public void set(float val) { fEntry0 = val; }
				public float get() { return (float)fEntry0; }
			}
			, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface.declare("0", "7", "");
		ui_interface.openVerticalBox("Alternate Signals");
		ui_interface.declare("fCheckbox3", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", new FaustVarAccess() {
				public String getId() { return "fCheckbox3"; }
				public void set(float val) { fCheckbox3 = val; }
				public float get() { return (float)fCheckbox3; }
			}
			);
		ui_interface.declare("fCheckbox4", "1", "");
		ui_interface.declare("fCheckbox4", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", new FaustVarAccess() {
				public String getId() { return "fCheckbox4"; }
				public void set(float val) { fCheckbox4 = val; }
				public float get() { return (float)fCheckbox4; }
			}
			);
		ui_interface.declare("fCheckbox2", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface.openVerticalBox("FLANGER");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox1", "0", "");
		ui_interface.declare("fCheckbox1", "tooltip", "When this is checked, the flanger   has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.declare("fCheckbox5", "1", "");
		ui_interface.addCheckButton("Invert Flange Sum", new FaustVarAccess() {
				public String getId() { return "fCheckbox5"; }
				public void set(float val) { fCheckbox5 = val; }
				public float get() { return (float)fCheckbox5; }
			}
			);
		ui_interface.declare("fHbargraph0", "2", "");
		ui_interface.declare("fHbargraph0", "style", "led");
		ui_interface.declare("fHbargraph0", "tooltip", "Display sum of flange delays");
		ui_interface.addHorizontalBargraph("Flange LFO", new FaustVarAccess() {
				public String getId() { return "fHbargraph0"; }
				public void set(float val) { fHbargraph0 = val; }
				public float get() { return (float)fHbargraph0; }
			}
			, -1.5f, 1.5f);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.5f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("Depth", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Delay Controls");
		ui_interface.declare("fHslider8", "1", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.declare("fHslider8", "unit", "ms");
		ui_interface.addHorizontalSlider("Flange Delay", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 10.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface.declare("fHslider7", "2", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.declare("fHslider7", "unit", "ms");
		ui_interface.addHorizontalSlider("Delay Offset", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 1.0f, 0.0f, 20.0f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider3", "unit", "dB");
		ui_interface.addHorizontalSlider("Flanger Output Level", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 0.0f, -60.0f, 10.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface.openVerticalBox("PHASER2");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the phaser   has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.declare("fCheckbox7", "1", "");
		ui_interface.addCheckButton("Invert Internal Phaser Sum", new FaustVarAccess() {
				public String getId() { return "fCheckbox7"; }
				public void set(float val) { fCheckbox7 = val; }
				public float get() { return (float)fCheckbox7; }
			}
			);
		ui_interface.declare("fCheckbox6", "2", "");
		ui_interface.addCheckButton("Vibrato Mode", new FaustVarAccess() {
				public String getId() { return "fCheckbox6"; }
				public void set(float val) { fCheckbox6 = val; }
				public float get() { return (float)fCheckbox6; }
			}
			);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider15", "1", "");
		ui_interface.declare("fHslider15", "style", "knob");
		ui_interface.declare("fHslider15", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", new FaustVarAccess() {
				public String getId() { return "fHslider15"; }
				public void set(float val) { fHslider15 = val; }
				public float get() { return (float)fHslider15; }
			}
			, 0.5f, 0.0f, 10.0f, 0.00100000005f);
		ui_interface.declare("fHslider9", "2", "");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("Notch Depth (Intensity)", new FaustVarAccess() {
				public String getId() { return "fHslider9"; }
				public void set(float val) { fHslider9 = val; }
				public float get() { return (float)fHslider9; }
			}
			, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface.declare("fHslider11", "3", "");
		ui_interface.declare("fHslider11", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback Gain", new FaustVarAccess() {
				public String getId() { return "fHslider11"; }
				public void set(float val) { fHslider11 = val; }
				public float get() { return (float)fHslider11; }
			}
			, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider10", "1", "");
		ui_interface.declare("fHslider10", "scale", "log");
		ui_interface.declare("fHslider10", "style", "knob");
		ui_interface.declare("fHslider10", "unit", "Hz");
		ui_interface.addHorizontalSlider("Notch width", new FaustVarAccess() {
				public String getId() { return "fHslider10"; }
				public void set(float val) { fHslider10 = val; }
				public float get() { return (float)fHslider10; }
			}
			, 1000.0f, 10.0f, 5000.0f, 1.0f);
		ui_interface.declare("fHslider13", "2", "");
		ui_interface.declare("fHslider13", "scale", "log");
		ui_interface.declare("fHslider13", "style", "knob");
		ui_interface.declare("fHslider13", "unit", "Hz");
		ui_interface.addHorizontalSlider("Min Notch1 Freq", new FaustVarAccess() {
				public String getId() { return "fHslider13"; }
				public void set(float val) { fHslider13 = val; }
				public float get() { return (float)fHslider13; }
			}
			, 100.0f, 20.0f, 5000.0f, 1.0f);
		ui_interface.declare("fHslider14", "3", "");
		ui_interface.declare("fHslider14", "scale", "log");
		ui_interface.declare("fHslider14", "style", "knob");
		ui_interface.declare("fHslider14", "unit", "Hz");
		ui_interface.addHorizontalSlider("Max Notch1 Freq", new FaustVarAccess() {
				public String getId() { return "fHslider14"; }
				public void set(float val) { fHslider14 = val; }
				public float get() { return (float)fHslider14; }
			}
			, 800.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface.declare("fHslider12", "4", "");
		ui_interface.declare("fHslider12", "style", "knob");
		ui_interface.addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", new FaustVarAccess() {
				public String getId() { return "fHslider12"; }
				public void set(float val) { fHslider12 = val; }
				public float get() { return (float)fHslider12; }
			}
			, 1.5f, 1.10000002f, 4.0f, 0.00100000005f);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("Phaser Output Level", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 0.0f, -60.0f, 10.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph14", "0", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a16f840", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a15de30", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a13bc30", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a119a30", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a0f38b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a0d16b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a0af4b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a08d2b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a06b0b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a048eb0", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a026cb0", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba5a004ab0", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba59fde930", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba59fbc730", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fba59f994a0", new FaustVarAccess() {
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
		float fSlow4 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider2));
		int iSlow5 = (int)fCheckbox1;
		float fSlow6 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider3));
		float fSlow7 = (fConst14 * fHslider4);
		float fSlow8 = (float)java.lang.Math.sin(fSlow7);
		float fSlow9 = (float)java.lang.Math.cos(fSlow7);
		float fSlow10 = (0.0f - fSlow8);
		float fSlow11 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		int iSlow12 = (int)fCheckbox2;
		int iSlow13 = (int)fCheckbox3;
		int iSlow14 = (int)(fEntry0 + -1.0f);
		int iSlow15 = (iSlow14 >= 2);
		int iSlow16 = (iSlow14 >= 1);
		float fSlow17 = (float)java.lang.Math.exp((0.0f - (fConst15 / fVslider2)));
		float fSlow18 = (440.0f * ((float)java.lang.Math.pow(2.0f, (0.0833333358f * (fVslider1 + -49.0f))) * (1.0f - fSlow17)));
		int iSlow19 = (iSlow14 >= 3);
		float fSlow20 = ((0.00999999978f * fVslider3) + 1.0f);
		float fSlow21 = ((0.00999999978f * fVslider4) + 1.0f);
		int iSlow22 = (int)fCheckbox4;
		float fSlow23 = fHslider5;
		float fSlow24 = ((((int)fCheckbox5==0)?true:false)?(0.0f - fSlow23):fSlow23);
		float fSlow25 = fHslider6;
		float fSlow26 = (0.00100000005f * fHslider7);
		float fSlow27 = (0.000500000024f * fHslider8);
		float fSlow28 = (0.5f * ((((int)fCheckbox6==0)?true:false)?2.0f:fHslider9));
		float fSlow29 = (1.0f - fSlow28);
		float fSlow30 = (float)java.lang.Math.exp((fConst15 * (0.0f - (3.14159274f * fHslider10))));
		float fSlow31 = mydsp_faustpower2_f(fSlow30);
		float fSlow32 = fHslider11;
		float fSlow33 = (0.0f - (2.0f * fSlow30));
		float fSlow34 = fHslider12;
		float fSlow35 = fHslider13;
		float fSlow36 = (fConst14 * fSlow35);
		float fSlow37 = (0.5f * (0.0f - (fConst14 * (fSlow35 - (float)java.lang.Math.max(fSlow35, fHslider14)))));
		float fSlow38 = (fConst14 * fHslider15);
		float fSlow39 = (float)java.lang.Math.sin(fSlow38);
		float fSlow40 = (float)java.lang.Math.cos(fSlow38);
		float fSlow41 = (0.0f - fSlow39);
		float fSlow42 = mydsp_faustpower2_f(fSlow34);
		float fSlow43 = mydsp_faustpower3_f(fSlow34);
		float fSlow44 = mydsp_faustpower4_f(fSlow34);
		float fSlow45 = ((((int)fCheckbox7==0)?true:false)?(0.0f - fSlow28):fSlow28);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec4[0] = ((fSlow8 * fRec5[1]) + (fSlow9 * fRec4[1]));
			int iTemp0 = (1 - iVec0[1]);
			fRec5[0] = (((fSlow9 * fRec5[1]) + (fSlow10 * fRec4[1])) + (float)iTemp0);
			fHbargraph0 = (fRec5[0] + fRec4[0]);
			fRec6[0] = (fSlow11 + (0.999000013f * fRec6[1]));
			fRec8[0] = (fSlow18 + (fSlow17 * fRec8[1]));
			float fTemp1 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fRec8[0]));
			fVec1[0] = fTemp1;
			float fTemp2 = (fRec7[1] + (fConst15 * fVec1[1]));
			fRec7[0] = (fTemp2 - (float)java.lang.Math.floor(fTemp2));
			float fTemp3 = (2.0f * fRec7[0]);
			float fTemp4 = (fTemp3 + -1.0f);
			float fTemp5 = mydsp_faustpower2_f(fTemp4);
			fVec2[0] = fTemp5;
			float fTemp6 = mydsp_faustpower3_f(fTemp4);
			fVec3[0] = (fTemp6 + (1.0f - fTemp3));
			float fTemp7 = ((fTemp6 + (1.0f - (fTemp3 + fVec3[1]))) / fTemp1);
			fVec4[0] = fTemp7;
			float fTemp8 = (fTemp5 * (fTemp5 + -2.0f));
			fVec5[0] = fTemp8;
			float fTemp9 = ((fTemp8 - fVec5[1]) / fTemp1);
			fVec6[0] = fTemp9;
			float fTemp10 = ((fTemp9 - fVec6[1]) / fTemp1);
			fVec7[0] = fTemp10;
			float fTemp11 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow20 * fRec8[0])));
			fVec8[0] = fTemp11;
			float fTemp12 = (fRec9[1] + (fConst15 * fVec8[1]));
			fRec9[0] = (fTemp12 - (float)java.lang.Math.floor(fTemp12));
			float fTemp13 = (2.0f * fRec9[0]);
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
			float fTemp21 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow21 * fRec8[0])));
			fVec15[0] = fTemp21;
			float fTemp22 = (fRec10[1] + (fConst15 * fVec15[1]));
			fRec10[0] = (fTemp22 - (float)java.lang.Math.floor(fTemp22));
			float fTemp23 = (2.0f * fRec10[0]);
			float fTemp24 = (fTemp23 + -1.0f);
			float fTemp25 = mydsp_faustpower2_f(fTemp24);
			fVec16[0] = fTemp25;
			float fTemp26 = mydsp_faustpower3_f(fTemp24);
			fVec17[0] = (fTemp26 + (1.0f - fTemp23));
			float fTemp27 = ((fTemp26 + (1.0f - (fTemp23 + fVec17[1]))) / fTemp21);
			fVec18[0] = fTemp27;
			float fTemp28 = (fTemp25 * (fTemp25 + -2.0f));
			fVec19[0] = fTemp28;
			float fTemp29 = ((fTemp28 - fVec19[1]) / fTemp21);
			fVec20[0] = fTemp29;
			float fTemp30 = ((fTemp29 - fVec20[1]) / fTemp21);
			fVec21[0] = fTemp30;
			iRec11[0] = ((1103515245 * iRec11[1]) + 12345);
			float fTemp31 = (4.65661287e-10f * (float)iRec11[0]);
			fRec12[0] = (((0.522189379f * fRec12[3]) + (fTemp31 + (2.49495602f * fRec12[1]))) - (2.0172658f * fRec12[2]));
			float fTemp32 = (fRec6[0] * (((iSlow12==0)?true:false)?input0[i]:(((iSlow13==0)?true:false)?(((iSlow22==0)?true:false)?(((0.0499220341f * fRec12[0]) + (0.0506126992f * fRec12[2])) - ((0.0959935337f * fRec12[1]) + (0.00440878607f * fRec12[3]))):fTemp31):(0.333333343f * (fRec6[0] * (((((iSlow15==0)?true:false)?(((iSlow19==0)?true:false)?(fConst18 * (((float)iVec0[3] * (fTemp10 - fVec7[1])) / fTemp1)):(fConst17 * (((float)iVec0[2] * (fTemp7 - fVec4[1])) / fTemp1))):(((iSlow16==0)?true:false)?(fConst16 * (((float)iVec0[1] * (fTemp5 - fVec2[1])) / fTemp1)):fTemp4)) + (((iSlow15==0)?true:false)?(((iSlow19==0)?true:false)?(fConst18 * (((float)iVec0[3] * (fTemp20 - fVec14[1])) / fTemp11)):(fConst17 * (((float)iVec0[2] * (fTemp17 - fVec11[1])) / fTemp11))):(((iSlow16==0)?true:false)?(fConst16 * (((float)iVec0[1] * (fTemp15 - fVec9[1])) / fTemp11)):fTemp14))) + (((iSlow15==0)?true:false)?(((iSlow19==0)?true:false)?(fConst18 * (((float)iVec0[3] * (fTemp30 - fVec21[1])) / fTemp21)):(fConst17 * (((float)iVec0[2] * (fTemp27 - fVec18[1])) / fTemp21))):(((iSlow16==0)?true:false)?(fConst16 * (((float)iVec0[1] * (fTemp25 - fVec16[1])) / fTemp21)):fTemp24))))))));
			float fTemp33 = (((iSlow5==0)?true:false)?0.0f:fTemp32);
			float fTemp34 = (fSlow6 * fTemp33);
			float fTemp35 = ((fSlow25 * fRec13[1]) - fTemp34);
			fVec22[(IOTA & 4095)] = fTemp35;
			float fTemp36 = (fConst0 * (fSlow26 + (fSlow27 * (fRec4[0] + 1.0f))));
			int iTemp37 = (int)fTemp36;
			float fTemp38 = (float)java.lang.Math.floor(fTemp36);
			fRec13[0] = ((fVec22[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, iTemp37))) & 4095)] * (fTemp38 + (1.0f - fTemp36))) + ((fTemp36 - fTemp38) * fVec22[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, (iTemp37 + 1)))) & 4095)]));
			float fTemp39 = (((iSlow5==0)?true:false)?fTemp32:(0.5f * (fTemp34 + (fSlow24 * fRec13[0]))));
			float fTemp40 = (((iSlow3==0)?true:false)?0.0f:fTemp39);
			fRec19[0] = ((fSlow39 * fRec20[1]) + (fSlow40 * fRec19[1]));
			fRec20[0] = (((fSlow40 * fRec20[1]) + (fSlow41 * fRec19[1])) + (float)iTemp0);
			float fTemp41 = (fSlow36 + (fSlow37 * (1.0f - fRec19[0])));
			float fTemp42 = (fRec18[1] * (float)java.lang.Math.cos((fSlow34 * fTemp41)));
			fRec18[0] = (((fSlow4 * fTemp40) + (fSlow32 * fRec14[1])) - ((fSlow33 * fTemp42) + (fSlow31 * fRec18[2])));
			float fTemp43 = (fRec17[1] * (float)java.lang.Math.cos((fSlow42 * fTemp41)));
			fRec17[0] = ((fRec18[2] + (fSlow33 * (fTemp42 - fTemp43))) + (fSlow31 * (fRec18[0] - fRec17[2])));
			float fTemp44 = (fRec16[1] * (float)java.lang.Math.cos((fSlow43 * fTemp41)));
			fRec16[0] = ((fRec17[2] + (fSlow33 * (fTemp43 - fTemp44))) + (fSlow31 * (fRec17[0] - fRec16[2])));
			float fTemp45 = (fRec15[1] * (float)java.lang.Math.cos((fSlow44 * fTemp41)));
			fRec15[0] = ((fRec16[2] + (fSlow33 * (fTemp44 - fTemp45))) + (fSlow31 * (fRec16[0] - fRec15[2])));
			fRec14[0] = ((fSlow31 * fRec15[0]) + ((fSlow33 * fTemp45) + fRec15[2]));
			float fTemp46 = (((iSlow3==0)?true:false)?fTemp39:((fSlow4 * (fTemp40 * fSlow29)) + (fRec14[0] * fSlow45)));
			float fTemp47 = (fSlow6 * fTemp33);
			float fTemp48 = ((fSlow25 * fRec21[1]) - fTemp47);
			fVec23[(IOTA & 4095)] = fTemp48;
			float fTemp49 = (fConst0 * (fSlow26 + (fSlow27 * (fRec5[0] + 1.0f))));
			int iTemp50 = (int)fTemp49;
			float fTemp51 = (float)java.lang.Math.floor(fTemp49);
			fRec21[0] = ((fVec23[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, iTemp50))) & 4095)] * (fTemp51 + (1.0f - fTemp49))) + ((fTemp49 - fTemp51) * fVec23[((IOTA - java.lang.Math.min(2049, java.lang.Math.max(0, (iTemp50 + 1)))) & 4095)]));
			float fTemp52 = (((iSlow5==0)?true:false)?fTemp32:(0.5f * (fTemp47 + (fSlow24 * fRec21[0]))));
			float fTemp53 = (((iSlow3==0)?true:false)?0.0f:fTemp52);
			float fTemp54 = (fSlow36 + (fSlow37 * (1.0f - fRec20[0])));
			float fTemp55 = (fRec26[1] * (float)java.lang.Math.cos((fSlow34 * fTemp54)));
			fRec26[0] = (((fSlow4 * fTemp53) + (fSlow32 * fRec22[1])) - ((fSlow33 * fTemp55) + (fSlow31 * fRec26[2])));
			float fTemp56 = (fRec25[1] * (float)java.lang.Math.cos((fSlow42 * fTemp54)));
			fRec25[0] = ((fRec26[2] + (fSlow33 * (fTemp55 - fTemp56))) + (fSlow31 * (fRec26[0] - fRec25[2])));
			float fTemp57 = (fRec24[1] * (float)java.lang.Math.cos((fSlow43 * fTemp54)));
			fRec24[0] = ((fRec25[2] + (fSlow33 * (fTemp56 - fTemp57))) + (fSlow31 * (fRec25[0] - fRec24[2])));
			float fTemp58 = (fRec23[1] * (float)java.lang.Math.cos((fSlow44 * fTemp54)));
			fRec23[0] = ((fRec24[2] + (fSlow33 * (fTemp57 - fTemp58))) + (fSlow31 * (fRec24[0] - fRec23[2])));
			fRec22[0] = ((fSlow31 * fRec23[0]) + ((fSlow33 * fTemp58) + fRec23[2]));
			float fTemp59 = (((iSlow3==0)?true:false)?fTemp52:((fSlow4 * (fSlow29 * fTemp53)) + (fRec22[0] * fSlow45)));
			float fTemp60 = (fTemp46 + fTemp59);
			fRec3[0] = (fTemp60 - (fConst11 * ((fConst19 * fRec3[2]) + (fConst21 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst22 * fRec3[0])) + (fConst22 * fRec3[2]))) - (fConst8 * ((fConst23 * fRec2[2]) + (fConst24 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst25 * fRec2[0])) + (fConst25 * fRec2[2]))) - (fConst4 * ((fConst26 * fRec1[2]) + (fConst27 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst4 * (((fConst7 * fRec1[1]) + (fConst28 * fRec1[0])) + (fConst28 * fRec1[2]))))));
			fVbargraph0 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec0[0]))));
			fRec33[0] = (fTemp60 - (fConst45 * ((fConst48 * fRec33[2]) + (fConst49 * fRec33[1]))));
			fRec32[0] = ((fConst45 * (((fConst47 * fRec33[1]) + (fConst50 * fRec33[0])) + (fConst50 * fRec33[2]))) - (fConst43 * ((fConst51 * fRec32[2]) + (fConst52 * fRec32[1]))));
			fRec31[0] = ((fConst43 * (((fConst44 * fRec32[1]) + (fConst53 * fRec32[0])) + (fConst53 * fRec32[2]))) - (fConst41 * ((fConst54 * fRec31[2]) + (fConst55 * fRec31[1]))));
			float fTemp61 = (fConst41 * (((fConst42 * fRec31[1]) + (fConst56 * fRec31[0])) + (fConst56 * fRec31[2])));
			fRec30[0] = (fTemp61 - (fConst38 * ((fConst57 * fRec30[2]) + (fConst59 * fRec30[1]))));
			fRec29[0] = ((fConst38 * (((fConst40 * fRec30[1]) + (fConst60 * fRec30[0])) + (fConst60 * fRec30[2]))) - (fConst35 * ((fConst61 * fRec29[2]) + (fConst62 * fRec29[1]))));
			fRec28[0] = ((fConst35 * (((fConst37 * fRec29[1]) + (fConst63 * fRec29[0])) + (fConst63 * fRec29[2]))) - (fConst31 * ((fConst64 * fRec28[2]) + (fConst65 * fRec28[1]))));
			fRec27[0] = ((fSlow1 * fRec27[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst31 * (((fConst34 * fRec28[1]) + (fConst66 * fRec28[0])) + (fConst66 * fRec28[2]))))));
			fVbargraph1 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec27[0]))));
			fRec40[0] = (fTemp61 - (fConst83 * ((fConst86 * fRec40[2]) + (fConst87 * fRec40[1]))));
			fRec39[0] = ((fConst83 * (((fConst85 * fRec40[1]) + (fConst88 * fRec40[0])) + (fConst88 * fRec40[2]))) - (fConst81 * ((fConst89 * fRec39[2]) + (fConst90 * fRec39[1]))));
			fRec38[0] = ((fConst81 * (((fConst82 * fRec39[1]) + (fConst91 * fRec39[0])) + (fConst91 * fRec39[2]))) - (fConst79 * ((fConst92 * fRec38[2]) + (fConst93 * fRec38[1]))));
			float fTemp62 = (fConst79 * (((fConst80 * fRec38[1]) + (fConst94 * fRec38[0])) + (fConst94 * fRec38[2])));
			fRec37[0] = (fTemp62 - (fConst76 * ((fConst95 * fRec37[2]) + (fConst97 * fRec37[1]))));
			fRec36[0] = ((fConst76 * (((fConst78 * fRec37[1]) + (fConst98 * fRec37[0])) + (fConst98 * fRec37[2]))) - (fConst73 * ((fConst99 * fRec36[2]) + (fConst100 * fRec36[1]))));
			fRec35[0] = ((fConst73 * (((fConst75 * fRec36[1]) + (fConst101 * fRec36[0])) + (fConst101 * fRec36[2]))) - (fConst69 * ((fConst102 * fRec35[2]) + (fConst103 * fRec35[1]))));
			fRec34[0] = ((fSlow1 * fRec34[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst69 * (((fConst72 * fRec35[1]) + (fConst104 * fRec35[0])) + (fConst104 * fRec35[2]))))));
			fVbargraph2 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec34[0]))));
			fRec47[0] = (fTemp62 - (fConst121 * ((fConst124 * fRec47[2]) + (fConst125 * fRec47[1]))));
			fRec46[0] = ((fConst121 * (((fConst123 * fRec47[1]) + (fConst126 * fRec47[0])) + (fConst126 * fRec47[2]))) - (fConst119 * ((fConst127 * fRec46[2]) + (fConst128 * fRec46[1]))));
			fRec45[0] = ((fConst119 * (((fConst120 * fRec46[1]) + (fConst129 * fRec46[0])) + (fConst129 * fRec46[2]))) - (fConst117 * ((fConst130 * fRec45[2]) + (fConst131 * fRec45[1]))));
			float fTemp63 = (fConst117 * (((fConst118 * fRec45[1]) + (fConst132 * fRec45[0])) + (fConst132 * fRec45[2])));
			fRec44[0] = (fTemp63 - (fConst114 * ((fConst133 * fRec44[2]) + (fConst135 * fRec44[1]))));
			fRec43[0] = ((fConst114 * (((fConst116 * fRec44[1]) + (fConst136 * fRec44[0])) + (fConst136 * fRec44[2]))) - (fConst111 * ((fConst137 * fRec43[2]) + (fConst138 * fRec43[1]))));
			fRec42[0] = ((fConst111 * (((fConst113 * fRec43[1]) + (fConst139 * fRec43[0])) + (fConst139 * fRec43[2]))) - (fConst107 * ((fConst140 * fRec42[2]) + (fConst141 * fRec42[1]))));
			fRec41[0] = ((fSlow1 * fRec41[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst107 * (((fConst110 * fRec42[1]) + (fConst142 * fRec42[0])) + (fConst142 * fRec42[2]))))));
			fVbargraph3 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec41[0]))));
			fRec54[0] = (fTemp63 - (fConst159 * ((fConst162 * fRec54[2]) + (fConst163 * fRec54[1]))));
			fRec53[0] = ((fConst159 * (((fConst161 * fRec54[1]) + (fConst164 * fRec54[0])) + (fConst164 * fRec54[2]))) - (fConst157 * ((fConst165 * fRec53[2]) + (fConst166 * fRec53[1]))));
			fRec52[0] = ((fConst157 * (((fConst158 * fRec53[1]) + (fConst167 * fRec53[0])) + (fConst167 * fRec53[2]))) - (fConst155 * ((fConst168 * fRec52[2]) + (fConst169 * fRec52[1]))));
			float fTemp64 = (fConst155 * (((fConst156 * fRec52[1]) + (fConst170 * fRec52[0])) + (fConst170 * fRec52[2])));
			fRec51[0] = (fTemp64 - (fConst152 * ((fConst171 * fRec51[2]) + (fConst173 * fRec51[1]))));
			fRec50[0] = ((fConst152 * (((fConst154 * fRec51[1]) + (fConst174 * fRec51[0])) + (fConst174 * fRec51[2]))) - (fConst149 * ((fConst175 * fRec50[2]) + (fConst176 * fRec50[1]))));
			fRec49[0] = ((fConst149 * (((fConst151 * fRec50[1]) + (fConst177 * fRec50[0])) + (fConst177 * fRec50[2]))) - (fConst145 * ((fConst178 * fRec49[2]) + (fConst179 * fRec49[1]))));
			fRec48[0] = ((fSlow1 * fRec48[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst145 * (((fConst148 * fRec49[1]) + (fConst180 * fRec49[0])) + (fConst180 * fRec49[2]))))));
			fVbargraph4 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec48[0]))));
			fRec61[0] = (fTemp64 - (fConst197 * ((fConst200 * fRec61[2]) + (fConst201 * fRec61[1]))));
			fRec60[0] = ((fConst197 * (((fConst199 * fRec61[1]) + (fConst202 * fRec61[0])) + (fConst202 * fRec61[2]))) - (fConst195 * ((fConst203 * fRec60[2]) + (fConst204 * fRec60[1]))));
			fRec59[0] = ((fConst195 * (((fConst196 * fRec60[1]) + (fConst205 * fRec60[0])) + (fConst205 * fRec60[2]))) - (fConst193 * ((fConst206 * fRec59[2]) + (fConst207 * fRec59[1]))));
			float fTemp65 = (fConst193 * (((fConst194 * fRec59[1]) + (fConst208 * fRec59[0])) + (fConst208 * fRec59[2])));
			fRec58[0] = (fTemp65 - (fConst190 * ((fConst209 * fRec58[2]) + (fConst211 * fRec58[1]))));
			fRec57[0] = ((fConst190 * (((fConst192 * fRec58[1]) + (fConst212 * fRec58[0])) + (fConst212 * fRec58[2]))) - (fConst187 * ((fConst213 * fRec57[2]) + (fConst214 * fRec57[1]))));
			fRec56[0] = ((fConst187 * (((fConst189 * fRec57[1]) + (fConst215 * fRec57[0])) + (fConst215 * fRec57[2]))) - (fConst183 * ((fConst216 * fRec56[2]) + (fConst217 * fRec56[1]))));
			fRec55[0] = ((fSlow1 * fRec55[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst183 * (((fConst186 * fRec56[1]) + (fConst218 * fRec56[0])) + (fConst218 * fRec56[2]))))));
			fVbargraph5 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec55[0]))));
			fRec68[0] = (fTemp65 - (fConst235 * ((fConst238 * fRec68[2]) + (fConst239 * fRec68[1]))));
			fRec67[0] = ((fConst235 * (((fConst237 * fRec68[1]) + (fConst240 * fRec68[0])) + (fConst240 * fRec68[2]))) - (fConst233 * ((fConst241 * fRec67[2]) + (fConst242 * fRec67[1]))));
			fRec66[0] = ((fConst233 * (((fConst234 * fRec67[1]) + (fConst243 * fRec67[0])) + (fConst243 * fRec67[2]))) - (fConst231 * ((fConst244 * fRec66[2]) + (fConst245 * fRec66[1]))));
			float fTemp66 = (fConst231 * (((fConst232 * fRec66[1]) + (fConst246 * fRec66[0])) + (fConst246 * fRec66[2])));
			fRec65[0] = (fTemp66 - (fConst228 * ((fConst247 * fRec65[2]) + (fConst249 * fRec65[1]))));
			fRec64[0] = ((fConst228 * (((fConst230 * fRec65[1]) + (fConst250 * fRec65[0])) + (fConst250 * fRec65[2]))) - (fConst225 * ((fConst251 * fRec64[2]) + (fConst252 * fRec64[1]))));
			fRec63[0] = ((fConst225 * (((fConst227 * fRec64[1]) + (fConst253 * fRec64[0])) + (fConst253 * fRec64[2]))) - (fConst221 * ((fConst254 * fRec63[2]) + (fConst255 * fRec63[1]))));
			fRec62[0] = ((fSlow1 * fRec62[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst221 * (((fConst224 * fRec63[1]) + (fConst256 * fRec63[0])) + (fConst256 * fRec63[2]))))));
			fVbargraph6 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec62[0]))));
			fRec75[0] = (fTemp66 - (fConst273 * ((fConst276 * fRec75[2]) + (fConst277 * fRec75[1]))));
			fRec74[0] = ((fConst273 * (((fConst275 * fRec75[1]) + (fConst278 * fRec75[0])) + (fConst278 * fRec75[2]))) - (fConst271 * ((fConst279 * fRec74[2]) + (fConst280 * fRec74[1]))));
			fRec73[0] = ((fConst271 * (((fConst272 * fRec74[1]) + (fConst281 * fRec74[0])) + (fConst281 * fRec74[2]))) - (fConst269 * ((fConst282 * fRec73[2]) + (fConst283 * fRec73[1]))));
			float fTemp67 = (fConst269 * (((fConst270 * fRec73[1]) + (fConst284 * fRec73[0])) + (fConst284 * fRec73[2])));
			fRec72[0] = (fTemp67 - (fConst266 * ((fConst285 * fRec72[2]) + (fConst287 * fRec72[1]))));
			fRec71[0] = ((fConst266 * (((fConst268 * fRec72[1]) + (fConst288 * fRec72[0])) + (fConst288 * fRec72[2]))) - (fConst263 * ((fConst289 * fRec71[2]) + (fConst290 * fRec71[1]))));
			fRec70[0] = ((fConst263 * (((fConst265 * fRec71[1]) + (fConst291 * fRec71[0])) + (fConst291 * fRec71[2]))) - (fConst259 * ((fConst292 * fRec70[2]) + (fConst293 * fRec70[1]))));
			fRec69[0] = ((fSlow1 * fRec69[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst259 * (((fConst262 * fRec70[1]) + (fConst294 * fRec70[0])) + (fConst294 * fRec70[2]))))));
			fVbargraph7 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec69[0]))));
			fRec82[0] = (fTemp67 - (fConst311 * ((fConst314 * fRec82[2]) + (fConst315 * fRec82[1]))));
			fRec81[0] = ((fConst311 * (((fConst313 * fRec82[1]) + (fConst316 * fRec82[0])) + (fConst316 * fRec82[2]))) - (fConst309 * ((fConst317 * fRec81[2]) + (fConst318 * fRec81[1]))));
			fRec80[0] = ((fConst309 * (((fConst310 * fRec81[1]) + (fConst319 * fRec81[0])) + (fConst319 * fRec81[2]))) - (fConst307 * ((fConst320 * fRec80[2]) + (fConst321 * fRec80[1]))));
			float fTemp68 = (fConst307 * (((fConst308 * fRec80[1]) + (fConst322 * fRec80[0])) + (fConst322 * fRec80[2])));
			fRec79[0] = (fTemp68 - (fConst304 * ((fConst323 * fRec79[2]) + (fConst325 * fRec79[1]))));
			fRec78[0] = ((fConst304 * (((fConst306 * fRec79[1]) + (fConst326 * fRec79[0])) + (fConst326 * fRec79[2]))) - (fConst301 * ((fConst327 * fRec78[2]) + (fConst328 * fRec78[1]))));
			fRec77[0] = ((fConst301 * (((fConst303 * fRec78[1]) + (fConst329 * fRec78[0])) + (fConst329 * fRec78[2]))) - (fConst297 * ((fConst330 * fRec77[2]) + (fConst331 * fRec77[1]))));
			fRec76[0] = ((fSlow1 * fRec76[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst297 * (((fConst300 * fRec77[1]) + (fConst332 * fRec77[0])) + (fConst332 * fRec77[2]))))));
			fVbargraph8 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec76[0]))));
			fRec89[0] = (fTemp68 - (fConst349 * ((fConst352 * fRec89[2]) + (fConst353 * fRec89[1]))));
			fRec88[0] = ((fConst349 * (((fConst351 * fRec89[1]) + (fConst354 * fRec89[0])) + (fConst354 * fRec89[2]))) - (fConst347 * ((fConst355 * fRec88[2]) + (fConst356 * fRec88[1]))));
			fRec87[0] = ((fConst347 * (((fConst348 * fRec88[1]) + (fConst357 * fRec88[0])) + (fConst357 * fRec88[2]))) - (fConst345 * ((fConst358 * fRec87[2]) + (fConst359 * fRec87[1]))));
			float fTemp69 = (fConst345 * (((fConst346 * fRec87[1]) + (fConst360 * fRec87[0])) + (fConst360 * fRec87[2])));
			fRec86[0] = (fTemp69 - (fConst342 * ((fConst361 * fRec86[2]) + (fConst363 * fRec86[1]))));
			fRec85[0] = ((fConst342 * (((fConst344 * fRec86[1]) + (fConst364 * fRec86[0])) + (fConst364 * fRec86[2]))) - (fConst339 * ((fConst365 * fRec85[2]) + (fConst366 * fRec85[1]))));
			fRec84[0] = ((fConst339 * (((fConst341 * fRec85[1]) + (fConst367 * fRec85[0])) + (fConst367 * fRec85[2]))) - (fConst335 * ((fConst368 * fRec84[2]) + (fConst369 * fRec84[1]))));
			fRec83[0] = ((fSlow1 * fRec83[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst335 * (((fConst338 * fRec84[1]) + (fConst370 * fRec84[0])) + (fConst370 * fRec84[2]))))));
			fVbargraph9 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec83[0]))));
			fRec96[0] = (fTemp69 - (fConst387 * ((fConst390 * fRec96[2]) + (fConst391 * fRec96[1]))));
			fRec95[0] = ((fConst387 * (((fConst389 * fRec96[1]) + (fConst392 * fRec96[0])) + (fConst392 * fRec96[2]))) - (fConst385 * ((fConst393 * fRec95[2]) + (fConst394 * fRec95[1]))));
			fRec94[0] = ((fConst385 * (((fConst386 * fRec95[1]) + (fConst395 * fRec95[0])) + (fConst395 * fRec95[2]))) - (fConst383 * ((fConst396 * fRec94[2]) + (fConst397 * fRec94[1]))));
			float fTemp70 = (fConst383 * (((fConst384 * fRec94[1]) + (fConst398 * fRec94[0])) + (fConst398 * fRec94[2])));
			fRec93[0] = (fTemp70 - (fConst380 * ((fConst399 * fRec93[2]) + (fConst401 * fRec93[1]))));
			fRec92[0] = ((fConst380 * (((fConst382 * fRec93[1]) + (fConst402 * fRec93[0])) + (fConst402 * fRec93[2]))) - (fConst377 * ((fConst403 * fRec92[2]) + (fConst404 * fRec92[1]))));
			fRec91[0] = ((fConst377 * (((fConst379 * fRec92[1]) + (fConst405 * fRec92[0])) + (fConst405 * fRec92[2]))) - (fConst373 * ((fConst406 * fRec91[2]) + (fConst407 * fRec91[1]))));
			fRec90[0] = ((fSlow1 * fRec90[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst373 * (((fConst376 * fRec91[1]) + (fConst408 * fRec91[0])) + (fConst408 * fRec91[2]))))));
			fVbargraph10 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec90[0]))));
			fRec103[0] = (fTemp70 - (fConst425 * ((fConst428 * fRec103[2]) + (fConst429 * fRec103[1]))));
			fRec102[0] = ((fConst425 * (((fConst427 * fRec103[1]) + (fConst430 * fRec103[0])) + (fConst430 * fRec103[2]))) - (fConst423 * ((fConst431 * fRec102[2]) + (fConst432 * fRec102[1]))));
			fRec101[0] = ((fConst423 * (((fConst424 * fRec102[1]) + (fConst433 * fRec102[0])) + (fConst433 * fRec102[2]))) - (fConst421 * ((fConst434 * fRec101[2]) + (fConst435 * fRec101[1]))));
			float fTemp71 = (fConst421 * (((fConst422 * fRec101[1]) + (fConst436 * fRec101[0])) + (fConst436 * fRec101[2])));
			fRec100[0] = (fTemp71 - (fConst418 * ((fConst437 * fRec100[2]) + (fConst439 * fRec100[1]))));
			fRec99[0] = ((fConst418 * (((fConst420 * fRec100[1]) + (fConst440 * fRec100[0])) + (fConst440 * fRec100[2]))) - (fConst415 * ((fConst441 * fRec99[2]) + (fConst442 * fRec99[1]))));
			fRec98[0] = ((fConst415 * (((fConst417 * fRec99[1]) + (fConst443 * fRec99[0])) + (fConst443 * fRec99[2]))) - (fConst411 * ((fConst444 * fRec98[2]) + (fConst445 * fRec98[1]))));
			fRec97[0] = ((fSlow1 * fRec97[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst411 * (((fConst414 * fRec98[1]) + (fConst446 * fRec98[0])) + (fConst446 * fRec98[2]))))));
			fVbargraph11 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec97[0]))));
			fRec110[0] = (fTemp71 - (fConst463 * ((fConst466 * fRec110[2]) + (fConst467 * fRec110[1]))));
			fRec109[0] = ((fConst463 * (((fConst465 * fRec110[1]) + (fConst468 * fRec110[0])) + (fConst468 * fRec110[2]))) - (fConst461 * ((fConst469 * fRec109[2]) + (fConst470 * fRec109[1]))));
			fRec108[0] = ((fConst461 * (((fConst462 * fRec109[1]) + (fConst471 * fRec109[0])) + (fConst471 * fRec109[2]))) - (fConst459 * ((fConst472 * fRec108[2]) + (fConst473 * fRec108[1]))));
			float fTemp72 = (fConst459 * (((fConst460 * fRec108[1]) + (fConst474 * fRec108[0])) + (fConst474 * fRec108[2])));
			fRec107[0] = (fTemp72 - (fConst456 * ((fConst475 * fRec107[2]) + (fConst477 * fRec107[1]))));
			fRec106[0] = ((fConst456 * (((fConst458 * fRec107[1]) + (fConst478 * fRec107[0])) + (fConst478 * fRec107[2]))) - (fConst453 * ((fConst479 * fRec106[2]) + (fConst480 * fRec106[1]))));
			fRec105[0] = ((fConst453 * (((fConst455 * fRec106[1]) + (fConst481 * fRec106[0])) + (fConst481 * fRec106[2]))) - (fConst449 * ((fConst482 * fRec105[2]) + (fConst483 * fRec105[1]))));
			fRec104[0] = ((fSlow1 * fRec104[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst449 * (((fConst452 * fRec105[1]) + (fConst484 * fRec105[0])) + (fConst484 * fRec105[2]))))));
			fVbargraph12 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec104[0]))));
			fRec117[0] = (fTemp72 - (fConst501 * ((fConst504 * fRec117[2]) + (fConst505 * fRec117[1]))));
			fRec116[0] = ((fConst501 * (((fConst503 * fRec117[1]) + (fConst506 * fRec117[0])) + (fConst506 * fRec117[2]))) - (fConst499 * ((fConst507 * fRec116[2]) + (fConst508 * fRec116[1]))));
			fRec115[0] = ((fConst499 * (((fConst500 * fRec116[1]) + (fConst509 * fRec116[0])) + (fConst509 * fRec116[2]))) - (fConst497 * ((fConst510 * fRec115[2]) + (fConst511 * fRec115[1]))));
			float fTemp73 = (fConst497 * (((fConst498 * fRec115[1]) + (fConst512 * fRec115[0])) + (fConst512 * fRec115[2])));
			fRec114[0] = (fTemp73 - (fConst494 * ((fConst513 * fRec114[2]) + (fConst515 * fRec114[1]))));
			fRec113[0] = ((fConst494 * (((fConst496 * fRec114[1]) + (fConst516 * fRec114[0])) + (fConst516 * fRec114[2]))) - (fConst491 * ((fConst517 * fRec113[2]) + (fConst518 * fRec113[1]))));
			fRec112[0] = ((fConst491 * (((fConst493 * fRec113[1]) + (fConst519 * fRec113[0])) + (fConst519 * fRec113[2]))) - (fConst487 * ((fConst520 * fRec112[2]) + (fConst521 * fRec112[1]))));
			fRec111[0] = ((fSlow1 * fRec111[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst487 * (((fConst490 * fRec112[1]) + (fConst522 * fRec112[0])) + (fConst522 * fRec112[2]))))));
			fVbargraph13 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec111[0]))));
			fRec121[0] = (fTemp73 - (fConst527 * ((fConst530 * fRec121[2]) + (fConst531 * fRec121[1]))));
			fRec120[0] = ((fConst527 * (((fConst529 * fRec121[1]) + (fConst532 * fRec121[0])) + (fConst532 * fRec121[2]))) - (fConst525 * ((fConst533 * fRec120[2]) + (fConst534 * fRec120[1]))));
			fRec119[0] = ((fConst525 * (((fConst526 * fRec120[1]) + (fConst535 * fRec120[0])) + (fConst535 * fRec120[2]))) - (fConst523 * ((fConst536 * fRec119[2]) + (fConst537 * fRec119[1]))));
			fRec118[0] = ((fSlow1 * fRec118[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst523 * (((fConst524 * fRec119[1]) + (fConst538 * fRec119[0])) + (fConst538 * fRec119[2]))))));
			fVbargraph14 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec118[0]))));
			output0[i] = fTemp46;
			output1[i] = fTemp59;
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec8[1] = fRec8[0];
			fVec1[1] = fVec1[0];
			fRec7[1] = fRec7[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec9[1] = fRec9[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec10[1] = fRec10[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			iRec11[1] = iRec11[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec12[j1] = fRec12[(j1 - 1)];
				
			}
			IOTA = (IOTA + 1);
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

