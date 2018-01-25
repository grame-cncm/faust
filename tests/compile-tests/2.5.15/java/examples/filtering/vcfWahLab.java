/* ------------------------------------------------------------
name: "vcfWahLab"
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
	float fConst124;
	float fConst125;
	float fConst126;
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
	float fCheckbox0;
	float fHslider2;
	int iVec0[] = new int[4];
	float fRec40[] = new float[2];
	float fCheckbox1;
	float fCheckbox2;
	float fConst146;
	float fHslider3;
	float fRec51[] = new float[2];
	float fCheckbox3;
	float fHslider4;
	float fRec53[] = new float[2];
	float fVslider0;
	float fRec54[] = new float[2];
	float fCheckbox4;
	float fCheckbox5;
	float fEntry0;
	float fConst147;
	float fVslider1;
	float fVslider2;
	float fRec56[] = new float[2];
	float fVec1[] = new float[2];
	float fRec55[] = new float[2];
	float fConst148;
	float fVec2[] = new float[2];
	float fConst149;
	float fVec3[] = new float[2];
	float fVec4[] = new float[2];
	float fConst150;
	float fVec5[] = new float[2];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2];
	float fVslider3;
	float fVec8[] = new float[2];
	float fRec57[] = new float[2];
	float fVec9[] = new float[2];
	float fVec10[] = new float[2];
	float fVec11[] = new float[2];
	float fVec12[] = new float[2];
	float fVec13[] = new float[2];
	float fVec14[] = new float[2];
	float fVslider4;
	float fVec15[] = new float[2];
	float fRec58[] = new float[2];
	float fVec16[] = new float[2];
	float fVec17[] = new float[2];
	float fVec18[] = new float[2];
	float fVec19[] = new float[2];
	float fVec20[] = new float[2];
	float fVec21[] = new float[2];
	float fCheckbox6;
	int iRec59[] = new int[2];
	float fRec60[] = new float[4];
	float fConst151;
	float fConst152;
	float fRec61[] = new float[2];
	float fRec62[] = new float[2];
	float fRec52[] = new float[3];
	float fRec50[] = new float[2];
	float fRec49[] = new float[2];
	float fRec48[] = new float[2];
	float fRec47[] = new float[2];
	float fRec46[] = new float[2];
	float fHslider5;
	float fRec63[] = new float[2];
	float fHslider6;
	float fRec45[] = new float[2];
	float fRec44[] = new float[2];
	float fRec43[] = new float[2];
	float fRec42[] = new float[2];
	float fRec41[] = new float[2];
	float fCheckbox7;
	float fConst153;
	float fRec66[] = new float[2];
	float fRec65[] = new float[3];
	float fRec64[] = new float[3];
	float fRec69[] = new float[2];
	float fRec67[] = new float[2];
	float fRec72[] = new float[2];
	float fRec70[] = new float[2];
	float fConst154;
	float fConst155;
	float fRec39[] = new float[3];
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec38[] = new float[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec37[] = new float[3];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec36[] = new float[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec35[] = new float[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fRec34[] = new float[3];
	float fConst171;
	float fConst172;
	float fConst173;
	float fRec33[] = new float[3];
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec32[] = new float[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec31[] = new float[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec30[] = new float[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fRec29[] = new float[3];
	float fConst186;
	float fConst187;
	float fConst188;
	float fRec28[] = new float[3];
	float fConst189;
	float fConst190;
	float fConst191;
	float fRec27[] = new float[3];
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec26[] = new float[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec25[] = new float[3];
	float fConst198;
	float fConst199;
	float fConst200;
	float fRec24[] = new float[3];
	float fConst201;
	float fConst202;
	float fConst203;
	float fRec23[] = new float[3];
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec22[] = new float[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec21[] = new float[3];
	float fConst210;
	float fConst211;
	float fConst212;
	float fRec20[] = new float[3];
	float fConst213;
	float fConst214;
	float fConst215;
	float fRec19[] = new float[3];
	float fConst216;
	float fConst217;
	float fConst218;
	float fRec18[] = new float[3];
	float fConst219;
	float fConst220;
	float fConst221;
	float fRec17[] = new float[3];
	float fConst222;
	float fConst223;
	float fConst224;
	float fRec16[] = new float[3];
	float fConst225;
	float fConst226;
	float fConst227;
	float fRec15[] = new float[3];
	float fConst228;
	float fConst229;
	float fConst230;
	float fRec14[] = new float[3];
	float fConst231;
	float fConst232;
	float fConst233;
	float fRec13[] = new float[3];
	float fConst234;
	float fConst235;
	float fConst236;
	float fRec12[] = new float[3];
	float fConst237;
	float fConst238;
	float fConst239;
	float fRec11[] = new float[3];
	float fConst240;
	float fConst241;
	float fConst242;
	float fRec10[] = new float[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec9[] = new float[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fRec8[] = new float[3];
	float fConst249;
	float fConst250;
	float fConst251;
	float fRec7[] = new float[3];
	float fConst252;
	float fConst253;
	float fConst254;
	float fRec6[] = new float[3];
	float fConst255;
	float fConst256;
	float fConst257;
	float fRec5[] = new float[3];
	float fConst258;
	float fConst259;
	float fConst260;
	float fRec4[] = new float[3];
	float fConst261;
	float fConst262;
	float fConst263;
	float fConst264;
	float fRec3[] = new float[3];
	float fConst265;
	float fConst266;
	float fConst267;
	float fRec2[] = new float[3];
	float fConst268;
	float fConst269;
	float fConst270;
	float fRec1[] = new float[3];
	float fConst271;
	float fRec0[] = new float[2];
	float fVbargraph0;
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
	float fConst300;
	float fConst301;
	float fConst302;
	float fRec76[] = new float[3];
	float fConst303;
	float fConst304;
	float fConst305;
	float fRec75[] = new float[3];
	float fConst306;
	float fConst307;
	float fConst308;
	float fRec74[] = new float[3];
	float fConst309;
	float fRec73[] = new float[2];
	float fVbargraph1;
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fConst314;
	float fConst315;
	float fConst316;
	float fConst317;
	float fConst318;
	float fRec83[] = new float[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec82[] = new float[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fRec81[] = new float[3];
	float fConst325;
	float fRec80[] = new float[2];
	float fVbargraph2;
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
	float fRec87[] = new float[3];
	float fConst337;
	float fConst338;
	float fConst339;
	float fRec86[] = new float[3];
	float fConst340;
	float fConst341;
	float fConst342;
	float fRec85[] = new float[3];
	float fConst343;
	float fRec84[] = new float[2];
	float fVbargraph3;
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
	float fRec91[] = new float[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fRec90[] = new float[3];
	float fConst358;
	float fConst359;
	float fConst360;
	float fRec89[] = new float[3];
	float fConst361;
	float fRec88[] = new float[2];
	float fVbargraph4;
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
	float fRec95[] = new float[3];
	float fConst373;
	float fConst374;
	float fConst375;
	float fRec94[] = new float[3];
	float fConst376;
	float fConst377;
	float fConst378;
	float fRec93[] = new float[3];
	float fConst379;
	float fRec92[] = new float[2];
	float fVbargraph5;
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
	float fRec99[] = new float[3];
	float fConst391;
	float fConst392;
	float fConst393;
	float fRec98[] = new float[3];
	float fConst394;
	float fConst395;
	float fConst396;
	float fRec97[] = new float[3];
	float fConst397;
	float fRec96[] = new float[2];
	float fVbargraph6;
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
	float fRec103[] = new float[3];
	float fConst409;
	float fConst410;
	float fConst411;
	float fRec102[] = new float[3];
	float fConst412;
	float fConst413;
	float fConst414;
	float fRec101[] = new float[3];
	float fConst415;
	float fRec100[] = new float[2];
	float fVbargraph7;
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
	float fRec107[] = new float[3];
	float fConst427;
	float fConst428;
	float fConst429;
	float fRec106[] = new float[3];
	float fConst430;
	float fConst431;
	float fConst432;
	float fRec105[] = new float[3];
	float fConst433;
	float fRec104[] = new float[2];
	float fVbargraph8;
	float fConst434;
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
	float fRec111[] = new float[3];
	float fConst445;
	float fConst446;
	float fConst447;
	float fRec110[] = new float[3];
	float fConst448;
	float fConst449;
	float fConst450;
	float fRec109[] = new float[3];
	float fConst451;
	float fRec108[] = new float[2];
	float fVbargraph9;
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
	float fRec115[] = new float[3];
	float fConst463;
	float fConst464;
	float fConst465;
	float fRec114[] = new float[3];
	float fConst466;
	float fConst467;
	float fConst468;
	float fRec113[] = new float[3];
	float fConst469;
	float fRec112[] = new float[2];
	float fVbargraph10;
	float fConst470;
	float fConst471;
	float fConst472;
	float fConst473;
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec119[] = new float[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec118[] = new float[3];
	float fConst484;
	float fConst485;
	float fConst486;
	float fRec117[] = new float[3];
	float fConst487;
	float fRec116[] = new float[2];
	float fVbargraph11;
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
	float fRec123[] = new float[3];
	float fConst499;
	float fConst500;
	float fConst501;
	float fRec122[] = new float[3];
	float fConst502;
	float fConst503;
	float fConst504;
	float fRec121[] = new float[3];
	float fConst505;
	float fRec120[] = new float[2];
	float fVbargraph12;
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
	float fConst516;
	float fRec127[] = new float[3];
	float fConst517;
	float fConst518;
	float fConst519;
	float fRec126[] = new float[3];
	float fConst520;
	float fConst521;
	float fConst522;
	float fRec125[] = new float[3];
	float fConst523;
	float fRec124[] = new float[2];
	float fVbargraph13;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec131[] = new float[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec130[] = new float[3];
	float fConst538;
	float fConst539;
	float fConst540;
	float fRec129[] = new float[3];
	float fConst541;
	float fRec128[] = new float[2];
	float fVbargraph14;
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Demonstrate competing variable-lowpass-filter effects on test signals with spectrum analysis display");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "vcfWahLab");
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
		fConst2 = (float)java.lang.Math.tan((196.349548f / fConst0));
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
		fConst14 = (float)java.lang.Math.tan((311.685455f / fConst0));
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
		fConst25 = (float)java.lang.Math.tan((494.769836f / fConst0));
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
		fConst36 = (float)java.lang.Math.tan((785.398193f / fConst0));
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
		fConst47 = (float)java.lang.Math.tan((1246.74182f / fConst0));
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
		fConst58 = (float)java.lang.Math.tan((1979.07935f / fConst0));
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
		fConst69 = (float)java.lang.Math.tan((3141.59277f / fConst0));
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
		fConst80 = (float)java.lang.Math.tan((4986.96729f / fConst0));
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
		fConst91 = (float)java.lang.Math.tan((7916.31738f / fConst0));
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
		fConst102 = (float)java.lang.Math.tan((12566.3711f / fConst0));
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
		fConst113 = (float)java.lang.Math.tan((19947.8691f / fConst0));
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
		fConst124 = (float)java.lang.Math.tan((31665.2695f / fConst0));
		fConst125 = (1.0f / fConst124);
		fConst126 = (1.0f / (((fConst125 + 0.168404877f) / fConst124) + 1.06935835f));
		fConst127 = mydsp_faustpower2_f(fConst124);
		fConst128 = (1.0f / fConst127);
		fConst129 = (2.0f * (53.5361519f - fConst128));
		fConst130 = (1.0f / (((fConst125 + 0.51247865f) / fConst124) + 0.689621389f));
		fConst131 = (2.0f * (7.62173128f - fConst128));
		fConst132 = (1.0f / (((fConst125 + 0.782413065f) / fConst124) + 0.245291501f));
		fConst133 = (9.99999975e-05f / fConst127);
		fConst134 = (2.0f * (0.000433227193f - fConst133));
		fConst135 = (float)java.lang.Math.tan((50265.4844f / fConst0));
		fConst136 = (1.0f / fConst135);
		fConst137 = (1.0f / (((fConst136 + 0.168404877f) / fConst135) + 1.06935835f));
		fConst138 = mydsp_faustpower2_f(fConst135);
		fConst139 = (1.0f / fConst138);
		fConst140 = (2.0f * (53.5361519f - fConst139));
		fConst141 = (1.0f / (((fConst136 + 0.51247865f) / fConst135) + 0.689621389f));
		fConst142 = (2.0f * (7.62173128f - fConst139));
		fConst143 = (1.0f / (((fConst136 + 0.782413065f) / fConst135) + 0.245291501f));
		fConst144 = (9.99999975e-05f / fConst138);
		fConst145 = (2.0f * (0.000433227193f - fConst144));
		fConst146 = (6.28318548f / fConst0);
		fConst147 = (1.0f / fConst0);
		fConst148 = (0.25f * fConst0);
		fConst149 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst150 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst151 = (1413.71667f / fConst0);
		fConst152 = (2827.43335f / fConst0);
		fConst153 = (3.14159274f / fConst0);
		fConst154 = (((fConst136 + -0.782413065f) / fConst135) + 0.245291501f);
		fConst155 = (2.0f * (0.245291501f - fConst139));
		fConst156 = (fConst144 + 0.000433227193f);
		fConst157 = (((fConst136 + -0.51247865f) / fConst135) + 0.689621389f);
		fConst158 = (2.0f * (0.689621389f - fConst139));
		fConst159 = (fConst139 + 7.62173128f);
		fConst160 = (((fConst136 + -0.168404877f) / fConst135) + 1.06935835f);
		fConst161 = (2.0f * (1.06935835f - fConst139));
		fConst162 = (fConst139 + 53.5361519f);
		fConst163 = (((fConst125 + -0.782413065f) / fConst124) + 0.245291501f);
		fConst164 = (2.0f * (0.245291501f - fConst128));
		fConst165 = (fConst133 + 0.000433227193f);
		fConst166 = (((fConst125 + -0.51247865f) / fConst124) + 0.689621389f);
		fConst167 = (2.0f * (0.689621389f - fConst128));
		fConst168 = (fConst128 + 7.62173128f);
		fConst169 = (((fConst125 + -0.168404877f) / fConst124) + 1.06935835f);
		fConst170 = (2.0f * (1.06935835f - fConst128));
		fConst171 = (fConst128 + 53.5361519f);
		fConst172 = (((fConst114 + -0.782413065f) / fConst113) + 0.245291501f);
		fConst173 = (2.0f * (0.245291501f - fConst117));
		fConst174 = (fConst122 + 0.000433227193f);
		fConst175 = (((fConst114 + -0.51247865f) / fConst113) + 0.689621389f);
		fConst176 = (2.0f * (0.689621389f - fConst117));
		fConst177 = (fConst117 + 7.62173128f);
		fConst178 = (((fConst114 + -0.168404877f) / fConst113) + 1.06935835f);
		fConst179 = (2.0f * (1.06935835f - fConst117));
		fConst180 = (fConst117 + 53.5361519f);
		fConst181 = (((fConst103 + -0.782413065f) / fConst102) + 0.245291501f);
		fConst182 = (2.0f * (0.245291501f - fConst106));
		fConst183 = (fConst111 + 0.000433227193f);
		fConst184 = (((fConst103 + -0.51247865f) / fConst102) + 0.689621389f);
		fConst185 = (2.0f * (0.689621389f - fConst106));
		fConst186 = (fConst106 + 7.62173128f);
		fConst187 = (((fConst103 + -0.168404877f) / fConst102) + 1.06935835f);
		fConst188 = (2.0f * (1.06935835f - fConst106));
		fConst189 = (fConst106 + 53.5361519f);
		fConst190 = (((fConst92 + -0.782413065f) / fConst91) + 0.245291501f);
		fConst191 = (2.0f * (0.245291501f - fConst95));
		fConst192 = (fConst100 + 0.000433227193f);
		fConst193 = (((fConst92 + -0.51247865f) / fConst91) + 0.689621389f);
		fConst194 = (2.0f * (0.689621389f - fConst95));
		fConst195 = (fConst95 + 7.62173128f);
		fConst196 = (((fConst92 + -0.168404877f) / fConst91) + 1.06935835f);
		fConst197 = (2.0f * (1.06935835f - fConst95));
		fConst198 = (fConst95 + 53.5361519f);
		fConst199 = (((fConst81 + -0.782413065f) / fConst80) + 0.245291501f);
		fConst200 = (2.0f * (0.245291501f - fConst84));
		fConst201 = (fConst89 + 0.000433227193f);
		fConst202 = (((fConst81 + -0.51247865f) / fConst80) + 0.689621389f);
		fConst203 = (2.0f * (0.689621389f - fConst84));
		fConst204 = (fConst84 + 7.62173128f);
		fConst205 = (((fConst81 + -0.168404877f) / fConst80) + 1.06935835f);
		fConst206 = (2.0f * (1.06935835f - fConst84));
		fConst207 = (fConst84 + 53.5361519f);
		fConst208 = (((fConst70 + -0.782413065f) / fConst69) + 0.245291501f);
		fConst209 = (2.0f * (0.245291501f - fConst73));
		fConst210 = (fConst78 + 0.000433227193f);
		fConst211 = (((fConst70 + -0.51247865f) / fConst69) + 0.689621389f);
		fConst212 = (2.0f * (0.689621389f - fConst73));
		fConst213 = (fConst73 + 7.62173128f);
		fConst214 = (((fConst70 + -0.168404877f) / fConst69) + 1.06935835f);
		fConst215 = (2.0f * (1.06935835f - fConst73));
		fConst216 = (fConst73 + 53.5361519f);
		fConst217 = (((fConst59 + -0.782413065f) / fConst58) + 0.245291501f);
		fConst218 = (2.0f * (0.245291501f - fConst62));
		fConst219 = (fConst67 + 0.000433227193f);
		fConst220 = (((fConst59 + -0.51247865f) / fConst58) + 0.689621389f);
		fConst221 = (2.0f * (0.689621389f - fConst62));
		fConst222 = (fConst62 + 7.62173128f);
		fConst223 = (((fConst59 + -0.168404877f) / fConst58) + 1.06935835f);
		fConst224 = (2.0f * (1.06935835f - fConst62));
		fConst225 = (fConst62 + 53.5361519f);
		fConst226 = (((fConst48 + -0.782413065f) / fConst47) + 0.245291501f);
		fConst227 = (2.0f * (0.245291501f - fConst51));
		fConst228 = (fConst56 + 0.000433227193f);
		fConst229 = (((fConst48 + -0.51247865f) / fConst47) + 0.689621389f);
		fConst230 = (2.0f * (0.689621389f - fConst51));
		fConst231 = (fConst51 + 7.62173128f);
		fConst232 = (((fConst48 + -0.168404877f) / fConst47) + 1.06935835f);
		fConst233 = (2.0f * (1.06935835f - fConst51));
		fConst234 = (fConst51 + 53.5361519f);
		fConst235 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst236 = (2.0f * (0.245291501f - fConst40));
		fConst237 = (fConst45 + 0.000433227193f);
		fConst238 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst239 = (2.0f * (0.689621389f - fConst40));
		fConst240 = (fConst40 + 7.62173128f);
		fConst241 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst242 = (2.0f * (1.06935835f - fConst40));
		fConst243 = (fConst40 + 53.5361519f);
		fConst244 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst245 = (2.0f * (0.245291501f - fConst29));
		fConst246 = (fConst34 + 0.000433227193f);
		fConst247 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst248 = (2.0f * (0.689621389f - fConst29));
		fConst249 = (fConst29 + 7.62173128f);
		fConst250 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst251 = (2.0f * (1.06935835f - fConst29));
		fConst252 = (fConst29 + 53.5361519f);
		fConst253 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst254 = (2.0f * (0.245291501f - fConst18));
		fConst255 = (fConst23 + 0.000433227193f);
		fConst256 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst257 = (2.0f * (0.689621389f - fConst18));
		fConst258 = (fConst18 + 7.62173128f);
		fConst259 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst260 = (2.0f * (1.06935835f - fConst18));
		fConst261 = (fConst18 + 53.5361519f);
		fConst262 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst263 = (1.0f / fConst5);
		fConst264 = (2.0f * (4.07678175f - fConst263));
		fConst265 = (fConst12 + 0.000407678192f);
		fConst266 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst267 = (2.0f * (1.4500711f - fConst263));
		fConst268 = (fConst9 + 1.4500711f);
		fConst269 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst270 = (2.0f * (0.935140193f - fConst263));
		fConst271 = (fConst6 + 0.935140193f);
		fConst272 = (float)java.lang.Math.tan((123.692459f / fConst0));
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
		fConst284 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst285 = (2.0f * (53.5361519f - fConst263));
		fConst286 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst287 = (2.0f * (7.62173128f - fConst263));
		fConst288 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst289 = (9.99999975e-05f / fConst5);
		fConst290 = (2.0f * (0.000433227193f - fConst289));
		fConst291 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst292 = (2.0f * (0.245291501f - fConst263));
		fConst293 = (fConst289 + 0.000433227193f);
		fConst294 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst295 = (2.0f * (0.689621389f - fConst263));
		fConst296 = (fConst263 + 7.62173128f);
		fConst297 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
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
		fConst310 = (1.0f / (((fConst273 + 0.168404877f) / fConst272) + 1.06935835f));
		fConst311 = (2.0f * (53.5361519f - fConst301));
		fConst312 = (1.0f / (((fConst273 + 0.51247865f) / fConst272) + 0.689621389f));
		fConst313 = (2.0f * (7.62173128f - fConst301));
		fConst314 = (1.0f / (((fConst273 + 0.782413065f) / fConst272) + 0.245291501f));
		fConst315 = (9.99999975e-05f / fConst275);
		fConst316 = (2.0f * (0.000433227193f - fConst315));
		fConst317 = (((fConst273 + -0.782413065f) / fConst272) + 0.245291501f);
		fConst318 = (2.0f * (0.245291501f - fConst301));
		fConst319 = (fConst315 + 0.000433227193f);
		fConst320 = (((fConst273 + -0.51247865f) / fConst272) + 0.689621389f);
		fConst321 = (2.0f * (0.689621389f - fConst301));
		fConst322 = (fConst301 + 7.62173128f);
		fConst323 = (((fConst273 + -0.168404877f) / fConst272) + 1.06935835f);
		fConst324 = (2.0f * (1.06935835f - fConst301));
		fConst325 = (fConst301 + 53.5361519f);
		fConst326 = (1.0f / (((fConst136 + 0.157482162f) / fConst135) + 0.935140193f));
		fConst327 = (50.0638084f / fConst138);
		fConst328 = (2.0f * (0.935140193f - fConst327));
		fConst329 = (1.0f / (((fConst136 + 0.743130445f) / fConst135) + 1.4500711f));
		fConst330 = (11.0520525f / fConst138);
		fConst331 = (2.0f * (1.4500711f - fConst330));
		fConst332 = (1.0f / (((fConst136 + 3.18972731f) / fConst135) + 4.07678175f));
		fConst333 = (0.00176617282f / fConst138);
		fConst334 = (2.0f * (0.000407678192f - fConst333));
		fConst335 = (((fConst136 + -3.18972731f) / fConst135) + 4.07678175f);
		fConst336 = (2.0f * (4.07678175f - fConst139));
		fConst337 = (fConst333 + 0.000407678192f);
		fConst338 = (((fConst136 + -0.743130445f) / fConst135) + 1.4500711f);
		fConst339 = (2.0f * (1.4500711f - fConst139));
		fConst340 = (fConst330 + 1.4500711f);
		fConst341 = (((fConst136 + -0.157482162f) / fConst135) + 0.935140193f);
		fConst342 = (2.0f * (0.935140193f - fConst139));
		fConst343 = (fConst327 + 0.935140193f);
		fConst344 = (1.0f / (((fConst125 + 0.157482162f) / fConst124) + 0.935140193f));
		fConst345 = (50.0638084f / fConst127);
		fConst346 = (2.0f * (0.935140193f - fConst345));
		fConst347 = (1.0f / (((fConst125 + 0.743130445f) / fConst124) + 1.4500711f));
		fConst348 = (11.0520525f / fConst127);
		fConst349 = (2.0f * (1.4500711f - fConst348));
		fConst350 = (1.0f / (((fConst125 + 3.18972731f) / fConst124) + 4.07678175f));
		fConst351 = (0.00176617282f / fConst127);
		fConst352 = (2.0f * (0.000407678192f - fConst351));
		fConst353 = (((fConst125 + -3.18972731f) / fConst124) + 4.07678175f);
		fConst354 = (2.0f * (4.07678175f - fConst128));
		fConst355 = (fConst351 + 0.000407678192f);
		fConst356 = (((fConst125 + -0.743130445f) / fConst124) + 1.4500711f);
		fConst357 = (2.0f * (1.4500711f - fConst128));
		fConst358 = (fConst348 + 1.4500711f);
		fConst359 = (((fConst125 + -0.157482162f) / fConst124) + 0.935140193f);
		fConst360 = (2.0f * (0.935140193f - fConst128));
		fConst361 = (fConst345 + 0.935140193f);
		fConst362 = (1.0f / (((fConst114 + 0.157482162f) / fConst113) + 0.935140193f));
		fConst363 = (50.0638084f / fConst116);
		fConst364 = (2.0f * (0.935140193f - fConst363));
		fConst365 = (1.0f / (((fConst114 + 0.743130445f) / fConst113) + 1.4500711f));
		fConst366 = (11.0520525f / fConst116);
		fConst367 = (2.0f * (1.4500711f - fConst366));
		fConst368 = (1.0f / (((fConst114 + 3.18972731f) / fConst113) + 4.07678175f));
		fConst369 = (0.00176617282f / fConst116);
		fConst370 = (2.0f * (0.000407678192f - fConst369));
		fConst371 = (((fConst114 + -3.18972731f) / fConst113) + 4.07678175f);
		fConst372 = (2.0f * (4.07678175f - fConst117));
		fConst373 = (fConst369 + 0.000407678192f);
		fConst374 = (((fConst114 + -0.743130445f) / fConst113) + 1.4500711f);
		fConst375 = (2.0f * (1.4500711f - fConst117));
		fConst376 = (fConst366 + 1.4500711f);
		fConst377 = (((fConst114 + -0.157482162f) / fConst113) + 0.935140193f);
		fConst378 = (2.0f * (0.935140193f - fConst117));
		fConst379 = (fConst363 + 0.935140193f);
		fConst380 = (1.0f / (((fConst103 + 0.157482162f) / fConst102) + 0.935140193f));
		fConst381 = (50.0638084f / fConst105);
		fConst382 = (2.0f * (0.935140193f - fConst381));
		fConst383 = (1.0f / (((fConst103 + 0.743130445f) / fConst102) + 1.4500711f));
		fConst384 = (11.0520525f / fConst105);
		fConst385 = (2.0f * (1.4500711f - fConst384));
		fConst386 = (1.0f / (((fConst103 + 3.18972731f) / fConst102) + 4.07678175f));
		fConst387 = (0.00176617282f / fConst105);
		fConst388 = (2.0f * (0.000407678192f - fConst387));
		fConst389 = (((fConst103 + -3.18972731f) / fConst102) + 4.07678175f);
		fConst390 = (2.0f * (4.07678175f - fConst106));
		fConst391 = (fConst387 + 0.000407678192f);
		fConst392 = (((fConst103 + -0.743130445f) / fConst102) + 1.4500711f);
		fConst393 = (2.0f * (1.4500711f - fConst106));
		fConst394 = (fConst384 + 1.4500711f);
		fConst395 = (((fConst103 + -0.157482162f) / fConst102) + 0.935140193f);
		fConst396 = (2.0f * (0.935140193f - fConst106));
		fConst397 = (fConst381 + 0.935140193f);
		fConst398 = (1.0f / (((fConst92 + 0.157482162f) / fConst91) + 0.935140193f));
		fConst399 = (50.0638084f / fConst94);
		fConst400 = (2.0f * (0.935140193f - fConst399));
		fConst401 = (1.0f / (((fConst92 + 0.743130445f) / fConst91) + 1.4500711f));
		fConst402 = (11.0520525f / fConst94);
		fConst403 = (2.0f * (1.4500711f - fConst402));
		fConst404 = (1.0f / (((fConst92 + 3.18972731f) / fConst91) + 4.07678175f));
		fConst405 = (0.00176617282f / fConst94);
		fConst406 = (2.0f * (0.000407678192f - fConst405));
		fConst407 = (((fConst92 + -3.18972731f) / fConst91) + 4.07678175f);
		fConst408 = (2.0f * (4.07678175f - fConst95));
		fConst409 = (fConst405 + 0.000407678192f);
		fConst410 = (((fConst92 + -0.743130445f) / fConst91) + 1.4500711f);
		fConst411 = (2.0f * (1.4500711f - fConst95));
		fConst412 = (fConst402 + 1.4500711f);
		fConst413 = (((fConst92 + -0.157482162f) / fConst91) + 0.935140193f);
		fConst414 = (2.0f * (0.935140193f - fConst95));
		fConst415 = (fConst399 + 0.935140193f);
		fConst416 = (1.0f / (((fConst81 + 0.157482162f) / fConst80) + 0.935140193f));
		fConst417 = (50.0638084f / fConst83);
		fConst418 = (2.0f * (0.935140193f - fConst417));
		fConst419 = (1.0f / (((fConst81 + 0.743130445f) / fConst80) + 1.4500711f));
		fConst420 = (11.0520525f / fConst83);
		fConst421 = (2.0f * (1.4500711f - fConst420));
		fConst422 = (1.0f / (((fConst81 + 3.18972731f) / fConst80) + 4.07678175f));
		fConst423 = (0.00176617282f / fConst83);
		fConst424 = (2.0f * (0.000407678192f - fConst423));
		fConst425 = (((fConst81 + -3.18972731f) / fConst80) + 4.07678175f);
		fConst426 = (2.0f * (4.07678175f - fConst84));
		fConst427 = (fConst423 + 0.000407678192f);
		fConst428 = (((fConst81 + -0.743130445f) / fConst80) + 1.4500711f);
		fConst429 = (2.0f * (1.4500711f - fConst84));
		fConst430 = (fConst420 + 1.4500711f);
		fConst431 = (((fConst81 + -0.157482162f) / fConst80) + 0.935140193f);
		fConst432 = (2.0f * (0.935140193f - fConst84));
		fConst433 = (fConst417 + 0.935140193f);
		fConst434 = (1.0f / (((fConst70 + 0.157482162f) / fConst69) + 0.935140193f));
		fConst435 = (50.0638084f / fConst72);
		fConst436 = (2.0f * (0.935140193f - fConst435));
		fConst437 = (1.0f / (((fConst70 + 0.743130445f) / fConst69) + 1.4500711f));
		fConst438 = (11.0520525f / fConst72);
		fConst439 = (2.0f * (1.4500711f - fConst438));
		fConst440 = (1.0f / (((fConst70 + 3.18972731f) / fConst69) + 4.07678175f));
		fConst441 = (0.00176617282f / fConst72);
		fConst442 = (2.0f * (0.000407678192f - fConst441));
		fConst443 = (((fConst70 + -3.18972731f) / fConst69) + 4.07678175f);
		fConst444 = (2.0f * (4.07678175f - fConst73));
		fConst445 = (fConst441 + 0.000407678192f);
		fConst446 = (((fConst70 + -0.743130445f) / fConst69) + 1.4500711f);
		fConst447 = (2.0f * (1.4500711f - fConst73));
		fConst448 = (fConst438 + 1.4500711f);
		fConst449 = (((fConst70 + -0.157482162f) / fConst69) + 0.935140193f);
		fConst450 = (2.0f * (0.935140193f - fConst73));
		fConst451 = (fConst435 + 0.935140193f);
		fConst452 = (1.0f / (((fConst59 + 0.157482162f) / fConst58) + 0.935140193f));
		fConst453 = (50.0638084f / fConst61);
		fConst454 = (2.0f * (0.935140193f - fConst453));
		fConst455 = (1.0f / (((fConst59 + 0.743130445f) / fConst58) + 1.4500711f));
		fConst456 = (11.0520525f / fConst61);
		fConst457 = (2.0f * (1.4500711f - fConst456));
		fConst458 = (1.0f / (((fConst59 + 3.18972731f) / fConst58) + 4.07678175f));
		fConst459 = (0.00176617282f / fConst61);
		fConst460 = (2.0f * (0.000407678192f - fConst459));
		fConst461 = (((fConst59 + -3.18972731f) / fConst58) + 4.07678175f);
		fConst462 = (2.0f * (4.07678175f - fConst62));
		fConst463 = (fConst459 + 0.000407678192f);
		fConst464 = (((fConst59 + -0.743130445f) / fConst58) + 1.4500711f);
		fConst465 = (2.0f * (1.4500711f - fConst62));
		fConst466 = (fConst456 + 1.4500711f);
		fConst467 = (((fConst59 + -0.157482162f) / fConst58) + 0.935140193f);
		fConst468 = (2.0f * (0.935140193f - fConst62));
		fConst469 = (fConst453 + 0.935140193f);
		fConst470 = (1.0f / (((fConst48 + 0.157482162f) / fConst47) + 0.935140193f));
		fConst471 = (50.0638084f / fConst50);
		fConst472 = (2.0f * (0.935140193f - fConst471));
		fConst473 = (1.0f / (((fConst48 + 0.743130445f) / fConst47) + 1.4500711f));
		fConst474 = (11.0520525f / fConst50);
		fConst475 = (2.0f * (1.4500711f - fConst474));
		fConst476 = (1.0f / (((fConst48 + 3.18972731f) / fConst47) + 4.07678175f));
		fConst477 = (0.00176617282f / fConst50);
		fConst478 = (2.0f * (0.000407678192f - fConst477));
		fConst479 = (((fConst48 + -3.18972731f) / fConst47) + 4.07678175f);
		fConst480 = (2.0f * (4.07678175f - fConst51));
		fConst481 = (fConst477 + 0.000407678192f);
		fConst482 = (((fConst48 + -0.743130445f) / fConst47) + 1.4500711f);
		fConst483 = (2.0f * (1.4500711f - fConst51));
		fConst484 = (fConst474 + 1.4500711f);
		fConst485 = (((fConst48 + -0.157482162f) / fConst47) + 0.935140193f);
		fConst486 = (2.0f * (0.935140193f - fConst51));
		fConst487 = (fConst471 + 0.935140193f);
		fConst488 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst489 = (50.0638084f / fConst39);
		fConst490 = (2.0f * (0.935140193f - fConst489));
		fConst491 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst492 = (11.0520525f / fConst39);
		fConst493 = (2.0f * (1.4500711f - fConst492));
		fConst494 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst495 = (0.00176617282f / fConst39);
		fConst496 = (2.0f * (0.000407678192f - fConst495));
		fConst497 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst498 = (2.0f * (4.07678175f - fConst40));
		fConst499 = (fConst495 + 0.000407678192f);
		fConst500 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst501 = (2.0f * (1.4500711f - fConst40));
		fConst502 = (fConst492 + 1.4500711f);
		fConst503 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst504 = (2.0f * (0.935140193f - fConst40));
		fConst505 = (fConst489 + 0.935140193f);
		fConst506 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst507 = (50.0638084f / fConst28);
		fConst508 = (2.0f * (0.935140193f - fConst507));
		fConst509 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst510 = (11.0520525f / fConst28);
		fConst511 = (2.0f * (1.4500711f - fConst510));
		fConst512 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst513 = (0.00176617282f / fConst28);
		fConst514 = (2.0f * (0.000407678192f - fConst513));
		fConst515 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst516 = (2.0f * (4.07678175f - fConst29));
		fConst517 = (fConst513 + 0.000407678192f);
		fConst518 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst519 = (2.0f * (1.4500711f - fConst29));
		fConst520 = (fConst510 + 1.4500711f);
		fConst521 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst522 = (2.0f * (0.935140193f - fConst29));
		fConst523 = (fConst507 + 0.935140193f);
		fConst524 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst525 = (50.0638084f / fConst17);
		fConst526 = (2.0f * (0.935140193f - fConst525));
		fConst527 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst528 = (11.0520525f / fConst17);
		fConst529 = (2.0f * (1.4500711f - fConst528));
		fConst530 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst531 = (0.00176617282f / fConst17);
		fConst532 = (2.0f * (0.000407678192f - fConst531));
		fConst533 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst534 = (2.0f * (4.07678175f - fConst18));
		fConst535 = (fConst531 + 0.000407678192f);
		fConst536 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst537 = (2.0f * (1.4500711f - fConst18));
		fConst538 = (fConst528 + 1.4500711f);
		fConst539 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst540 = (2.0f * (0.935140193f - fConst18));
		fConst541 = (fConst525 + 0.935140193f);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)50.0f;
		fHslider1 = (float)100.0f;
		fCheckbox0 = (float)0.0f;
		fHslider2 = (float)5.0f;
		fCheckbox1 = (float)0.0f;
		fCheckbox2 = (float)0.0f;
		fHslider3 = (float)200.0f;
		fCheckbox3 = (float)0.0f;
		fHslider4 = (float)0.80000000000000004f;
		fVslider0 = (float)-20.0f;
		fCheckbox4 = (float)0.0f;
		fCheckbox5 = (float)0.0f;
		fEntry0 = (float)2.0f;
		fVslider1 = (float)49.0f;
		fVslider2 = (float)0.10000000000000001f;
		fVslider3 = (float)-0.10000000000000001f;
		fVslider4 = (float)0.10000000000000001f;
		fCheckbox6 = (float)0.0f;
		fHslider5 = (float)25.0f;
		fHslider6 = (float)0.90000000000000002f;
		fCheckbox7 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec40[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec51[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec53[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec54[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec56[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec55[l7] = 0.0f;
			
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
			fRec57[l15] = 0.0f;
			
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
			fRec58[l23] = 0.0f;
			
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
			iRec59[l30] = 0;
			
		}
		for (int l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			fRec60[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec61[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec62[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec52[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec50[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec49[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec48[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec47[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec46[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec63[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec45[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec44[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec43[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec42[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec41[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec66[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec65[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec64[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec69[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec67[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec72[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec70[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec39[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec38[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec37[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec36[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec35[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec34[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec33[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec32[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec31[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec30[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec29[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec28[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec27[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec26[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec25[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec24[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec23[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec22[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec21[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec20[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec19[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec18[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec17[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec16[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec15[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec14[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec13[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec12[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec11[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec10[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec9[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec8[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec7[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec6[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec5[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec4[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec3[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec2[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec1[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec0[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec79[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec78[l94] = 0.0f;
			
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
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec73[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec83[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec82[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec81[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			fRec80[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec87[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec86[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec85[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec84[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec91[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec90[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec89[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec88[l111] = 0.0f;
			
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
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec92[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec99[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec98[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec97[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec96[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec103[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec102[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec101[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec100[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec107[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec106[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec105[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec104[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec111[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec110[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec109[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			fRec108[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec115[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec114[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec113[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec112[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec119[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec118[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec117[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			fRec116[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec123[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec122[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec121[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec120[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec127[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec126[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec125[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec124[l147] = 0.0f;
			
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
		ui_interface.openVerticalBox("vcfWahLab");
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
		ui_interface.declare("fCheckbox5", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", new FaustVarAccess() {
				public String getId() { return "fCheckbox5"; }
				public void set(float val) { fCheckbox5 = val; }
				public float get() { return (float)fCheckbox5; }
			}
			);
		ui_interface.declare("fCheckbox6", "1", "");
		ui_interface.declare("fCheckbox6", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", new FaustVarAccess() {
				public String getId() { return "fCheckbox6"; }
				public void set(float val) { fCheckbox6 = val; }
				public float get() { return (float)fCheckbox6; }
			}
			);
		ui_interface.declare("fCheckbox4", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", new FaustVarAccess() {
				public String getId() { return "fCheckbox4"; }
				public void set(float val) { fCheckbox4 = val; }
				public float get() { return (float)fCheckbox4; }
			}
			);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/vegf.html");
		ui_interface.openHorizontalBox("CRYBABY");
		ui_interface.declare("fCheckbox3", "0", "");
		ui_interface.declare("fCheckbox3", "tooltip", "When this is checked, the wah   pedal has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox3"; }
				public void set(float val) { fCheckbox3 = val; }
				public float get() { return (float)fCheckbox3; }
			}
			);
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.declare("fHslider4", "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)");
		ui_interface.addHorizontalSlider("Wah parameter", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "Fourth-order wah effect made using moog_vcf");
		ui_interface.openHorizontalBox("WAH4");
		ui_interface.declare("fCheckbox2", "0", "");
		ui_interface.declare("fCheckbox2", "tooltip", "When this is checked, the wah pedal has   no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "tooltip", "wah resonance   frequency in Hz");
		ui_interface.addHorizontalSlider("Resonance Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 200.0f, 100.0f, 2000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
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
		ui_interface.declare("fCheckbox7", "2", "");
		ui_interface.declare("fCheckbox7", "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface.addCheckButton("Normalized Ladders", new FaustVarAccess() {
				public String getId() { return "fCheckbox7"; }
				public void set(float val) { fCheckbox7 = val; }
				public float get() { return (float)fCheckbox7; }
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
		ui_interface.declare("0", "5", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph2", "0", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab35acad0", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph1", "1", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab359b010", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph0", "2", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab3578f80", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph14", "3", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab368c680", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph13", "4", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab367a150", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph12", "5", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab3667c20", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph11", "6", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab36556f0", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph10", "7", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab36431c0", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph9", "8", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab3630c90", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph8", "9", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab361e760", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph7", "10", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab360c230", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph6", "11", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab35f5d80", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph5", "12", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab35e3850", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph4", "13", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab35d1320", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph3", "14", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fdab35bedf0", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
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
		int iSlow6 = (int)fCheckbox2;
		float fSlow7 = (0.00100000005f * fHslider3);
		int iSlow8 = (int)fCheckbox3;
		float fSlow9 = fHslider4;
		float fSlow10 = (9.99999975e-05f * (float)java.lang.Math.pow(4.0f, fSlow9));
		float fSlow11 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		int iSlow12 = (int)fCheckbox4;
		int iSlow13 = (int)fCheckbox5;
		int iSlow14 = (int)(fEntry0 + -1.0f);
		int iSlow15 = (iSlow14 >= 2);
		int iSlow16 = (iSlow14 >= 1);
		float fSlow17 = (float)java.lang.Math.exp((0.0f - (fConst147 / fVslider2)));
		float fSlow18 = (440.0f * ((float)java.lang.Math.pow(2.0f, (0.0833333358f * (fVslider1 + -49.0f))) * (1.0f - fSlow17)));
		int iSlow19 = (iSlow14 >= 3);
		float fSlow20 = ((0.00999999978f * fVslider3) + 1.0f);
		float fSlow21 = ((0.00999999978f * fVslider4) + 1.0f);
		int iSlow22 = (int)fCheckbox6;
		float fSlow23 = (float)java.lang.Math.pow(2.0f, (2.29999995f * fSlow9));
		float fSlow24 = (1.0f - (fConst151 * (fSlow23 / (float)java.lang.Math.pow(2.0f, ((2.0f * (1.0f - fSlow9)) + 1.0f)))));
		float fSlow25 = (0.00100000005f * (0.0f - (2.0f * (fSlow24 * (float)java.lang.Math.cos((fConst152 * fSlow23))))));
		float fSlow26 = (0.00100000005f * mydsp_faustpower2_f(fSlow24));
		float fSlow27 = (0.439999998f * (float)java.lang.Math.pow(2.0f, (0.0833333358f * (fHslider5 + -49.0f))));
		float fSlow28 = fHslider6;
		float fSlow29 = (0.0f - (4.0f * (float)java.lang.Math.max(0.0f, (float)java.lang.Math.min(mydsp_faustpower4_f(fSlow28), 0.999998987f))));
		int iSlow30 = (int)fCheckbox7;
		float fSlow31 = (float)java.lang.Math.min(1.41419947f, (1.41421354f * fSlow28));
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
			fRec40[0] = (fSlow4 + (0.999000013f * fRec40[1]));
			fRec51[0] = (fSlow7 + (0.999000013f * fRec51[1]));
			float fTemp0 = (fConst146 * fRec51[0]);
			float fTemp1 = (1.0f - fTemp0);
			fRec53[0] = (fSlow10 + (0.999000013f * fRec53[1]));
			fRec54[0] = (fSlow11 + (0.999000013f * fRec54[1]));
			fRec56[0] = (fSlow18 + (fSlow17 * fRec56[1]));
			float fTemp2 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fRec56[0]));
			fVec1[0] = fTemp2;
			float fTemp3 = (fRec55[1] + (fConst147 * fVec1[1]));
			fRec55[0] = (fTemp3 - (float)java.lang.Math.floor(fTemp3));
			float fTemp4 = (2.0f * fRec55[0]);
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
			float fTemp12 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow20 * fRec56[0])));
			fVec8[0] = fTemp12;
			float fTemp13 = (fRec57[1] + (fConst147 * fVec8[1]));
			fRec57[0] = (fTemp13 - (float)java.lang.Math.floor(fTemp13));
			float fTemp14 = (2.0f * fRec57[0]);
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
			float fTemp22 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow21 * fRec56[0])));
			fVec15[0] = fTemp22;
			float fTemp23 = (fRec58[1] + (fConst147 * fVec15[1]));
			fRec58[0] = (fTemp23 - (float)java.lang.Math.floor(fTemp23));
			float fTemp24 = (2.0f * fRec58[0]);
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
			iRec59[0] = ((1103515245 * iRec59[1]) + 12345);
			float fTemp32 = (4.65661287e-10f * (float)iRec59[0]);
			fRec60[0] = (((0.522189379f * fRec60[3]) + (fTemp32 + (2.49495602f * fRec60[1]))) - (2.0172658f * fRec60[2]));
			float fTemp33 = (fRec54[0] * (((iSlow12==0)?true:false)?input0[i]:(((iSlow13==0)?true:false)?(((iSlow22==0)?true:false)?(((0.0499220341f * fRec60[0]) + (0.0506126992f * fRec60[2])) - ((0.0959935337f * fRec60[1]) + (0.00440878607f * fRec60[3]))):fTemp32):(0.333333343f * (fRec54[0] * (((((iSlow15==0)?true:false)?(((iSlow19==0)?true:false)?(fConst150 * (((float)iVec0[3] * (fTemp11 - fVec7[1])) / fTemp2)):(fConst149 * (((float)iVec0[2] * (fTemp8 - fVec4[1])) / fTemp2))):(((iSlow16==0)?true:false)?(fConst148 * (((float)iVec0[1] * (fTemp6 - fVec2[1])) / fTemp2)):fTemp5)) + (((iSlow15==0)?true:false)?(((iSlow19==0)?true:false)?(fConst150 * (((float)iVec0[3] * (fTemp21 - fVec14[1])) / fTemp12)):(fConst149 * (((float)iVec0[2] * (fTemp18 - fVec11[1])) / fTemp12))):(((iSlow16==0)?true:false)?(fConst148 * (((float)iVec0[1] * (fTemp16 - fVec9[1])) / fTemp12)):fTemp15))) + (((iSlow15==0)?true:false)?(((iSlow19==0)?true:false)?(fConst150 * (((float)iVec0[3] * (fTemp31 - fVec21[1])) / fTemp22)):(fConst149 * (((float)iVec0[2] * (fTemp28 - fVec18[1])) / fTemp22))):(((iSlow16==0)?true:false)?(fConst148 * (((float)iVec0[1] * (fTemp26 - fVec16[1])) / fTemp22)):fTemp25))))))));
			fRec61[0] = (fSlow25 + (0.999000013f * fRec61[1]));
			fRec62[0] = (fSlow26 + (0.999000013f * fRec62[1]));
			fRec52[0] = ((fRec53[0] * (((iSlow8==0)?true:false)?0.0f:fTemp33)) - ((fRec61[0] * fRec52[1]) + (fRec62[0] * fRec52[2])));
			float fTemp34 = (((iSlow8==0)?true:false)?fTemp33:(fRec52[0] - fRec52[1]));
			fRec50[0] = (((fTemp1 * fRec50[1]) + (((iSlow6==0)?true:false)?0.0f:fTemp34)) - (3.20000005f * fRec46[1]));
			fRec49[0] = (fRec50[0] + (fTemp1 * fRec49[1]));
			fRec48[0] = (fRec49[0] + (fTemp1 * fRec48[1]));
			fRec47[0] = (fRec48[0] + (fRec47[1] * fTemp1));
			fRec46[0] = (fRec47[0] * (float)java.lang.Math.pow(fTemp0, 4.0f));
			float fTemp35 = (((iSlow6==0)?true:false)?fTemp34:(4.0f * fRec46[0]));
			float fTemp36 = (((iSlow3==0)?true:false)?0.0f:fTemp35);
			fRec63[0] = (fSlow27 + (0.999000013f * fRec63[1]));
			float fTemp37 = (fConst146 * fRec63[0]);
			float fTemp38 = (1.0f - fTemp37);
			fRec45[0] = (fTemp36 + ((fTemp38 * fRec45[1]) + (fSlow29 * fRec41[1])));
			fRec44[0] = (fRec45[0] + (fTemp38 * fRec44[1]));
			fRec43[0] = (fRec44[0] + (fTemp38 * fRec43[1]));
			fRec42[0] = (fRec43[0] + (fRec42[1] * fTemp38));
			fRec41[0] = (fRec42[0] * (float)java.lang.Math.pow(fTemp37, 4.0f));
			fRec66[0] = (fSlow27 + (0.999000013f * fRec66[1]));
			float fTemp39 = (float)java.lang.Math.tan((fConst153 * (float)java.lang.Math.max(20.0f, (float)java.lang.Math.min(10000.0f, fRec66[0]))));
			float fTemp40 = (1.0f / fTemp39);
			float fTemp41 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp39)));
			float fTemp42 = (fSlow32 + (((fSlow34 + fTemp40) / fTemp39) + 1.0f));
			fRec65[0] = (fTemp36 - (((fRec65[2] * (fSlow32 + (((fTemp40 - fSlow34) / fTemp39) + 1.0f))) + (2.0f * (fRec65[1] * (fSlow32 + fTemp41)))) / fTemp42));
			float fTemp43 = (fSlow35 + (((fSlow36 + fTemp40) / fTemp39) + 1.0f));
			fRec64[0] = (((fRec65[2] + (fRec65[0] + (2.0f * fRec65[1]))) / fTemp42) - (((fRec64[2] * (fSlow35 + (((fTemp40 - fSlow36) / fTemp39) + 1.0f))) + (2.0f * (fRec64[1] * (fSlow35 + fTemp41)))) / fTemp43));
			float fTemp44 = (float)java.lang.Math.tan((fConst153 * (float)java.lang.Math.max(fRec66[0], 20.0f)));
			float fTemp45 = (1.0f / fTemp44);
			float fTemp46 = (fSlow39 + (((fSlow40 + fTemp45) / fTemp44) + 1.0f));
			float fTemp47 = ((fSlow39 + (1.0f - ((fSlow40 - fTemp45) / fTemp44))) / fTemp46);
			float fTemp48 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, fTemp47));
			float fTemp49 = (1.0f - mydsp_faustpower2_f(fTemp48));
			float fTemp50 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp49));
			float fTemp51 = ((fRec67[1] * (0.0f - fTemp48)) + (fTemp36 * fTemp50));
			float fTemp52 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp44)));
			float fTemp53 = (fSlow39 + fTemp52);
			float fTemp54 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, (2.0f * (fTemp53 / (fTemp46 * (fTemp47 + 1.0f))))));
			float fTemp55 = (1.0f - mydsp_faustpower2_f(fTemp54));
			float fTemp56 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp55));
			fRec69[0] = ((fRec69[1] * (0.0f - fTemp54)) + (fTemp51 * fTemp56));
			fRec67[0] = ((fTemp51 * fTemp54) + (fRec69[1] * fTemp56));
			float fRec68 = fRec69[0];
			float fTemp57 = (1.0f - (fTemp53 / fTemp46));
			float fTemp58 = (float)java.lang.Math.sqrt(fTemp49);
			float fTemp59 = ((((fTemp36 * fTemp48) + (fRec67[1] * fTemp50)) + (2.0f * ((fRec67[0] * fTemp57) / fTemp58))) + ((fRec68 * ((1.0f - fTemp47) - (2.0f * (fTemp54 * fTemp57)))) / (fTemp58 * (float)java.lang.Math.sqrt(fTemp55))));
			float fTemp60 = (fSlow37 + ((((fSlow41 + fTemp45) / fTemp44) + 1.0f) - fSlow38));
			float fTemp61 = ((fSlow37 + ((((fTemp45 - fSlow41) / fTemp44) + 1.0f) - fSlow38)) / fTemp60);
			float fTemp62 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, fTemp61));
			float fTemp63 = (1.0f - mydsp_faustpower2_f(fTemp62));
			float fTemp64 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp63));
			float fTemp65 = ((fRec70[1] * (0.0f - fTemp62)) + ((fTemp59 * fTemp64) / fTemp46));
			float fTemp66 = (fSlow37 + (fTemp52 - fSlow38));
			float fTemp67 = (float)java.lang.Math.max(-0.999899983f, (float)java.lang.Math.min(0.999899983f, (2.0f * (fTemp66 / (fTemp60 * (fTemp61 + 1.0f))))));
			float fTemp68 = (1.0f - mydsp_faustpower2_f(fTemp67));
			float fTemp69 = (float)java.lang.Math.sqrt((float)java.lang.Math.max(0.0f, fTemp68));
			fRec72[0] = ((fRec72[1] * (0.0f - fTemp67)) + (fTemp65 * fTemp69));
			fRec70[0] = ((fTemp65 * fTemp67) + (fRec72[1] * fTemp69));
			float fRec71 = fRec72[0];
			float fTemp70 = (1.0f - (fTemp66 / fTemp60));
			float fTemp71 = (float)java.lang.Math.sqrt(fTemp63);
			float fTemp72 = (((iSlow3==0)?true:false)?fTemp35:(fRec40[0] * (((iSlow5==0)?true:false)?(((iSlow30==0)?true:false)?((((((fTemp59 * fTemp62) / fTemp46) + (fRec70[1] * fTemp64)) + (2.0f * ((fRec70[0] * fTemp70) / fTemp71))) + ((fRec71 * ((1.0f - fTemp61) - (2.0f * (fTemp67 * fTemp70)))) / (fTemp71 * (float)java.lang.Math.sqrt(fTemp68)))) / fTemp60):((fRec64[2] + (fRec64[0] + (2.0f * fRec64[1]))) / fTemp43)):fRec41[0])));
			fRec39[0] = (fTemp72 - (fConst143 * ((fConst154 * fRec39[2]) + (fConst155 * fRec39[1]))));
			fRec38[0] = ((fConst143 * (((fConst145 * fRec39[1]) + (fConst156 * fRec39[0])) + (fConst156 * fRec39[2]))) - (fConst141 * ((fConst157 * fRec38[2]) + (fConst158 * fRec38[1]))));
			fRec37[0] = ((fConst141 * (((fConst142 * fRec38[1]) + (fConst159 * fRec38[0])) + (fConst159 * fRec38[2]))) - (fConst137 * ((fConst160 * fRec37[2]) + (fConst161 * fRec37[1]))));
			float fTemp73 = (fConst137 * (((fConst140 * fRec37[1]) + (fConst162 * fRec37[0])) + (fConst162 * fRec37[2])));
			fRec36[0] = (fTemp73 - (fConst132 * ((fConst163 * fRec36[2]) + (fConst164 * fRec36[1]))));
			fRec35[0] = ((fConst132 * (((fConst134 * fRec36[1]) + (fConst165 * fRec36[0])) + (fConst165 * fRec36[2]))) - (fConst130 * ((fConst166 * fRec35[2]) + (fConst167 * fRec35[1]))));
			fRec34[0] = ((fConst130 * (((fConst131 * fRec35[1]) + (fConst168 * fRec35[0])) + (fConst168 * fRec35[2]))) - (fConst126 * ((fConst169 * fRec34[2]) + (fConst170 * fRec34[1]))));
			float fTemp74 = (fConst126 * (((fConst129 * fRec34[1]) + (fConst171 * fRec34[0])) + (fConst171 * fRec34[2])));
			fRec33[0] = (fTemp74 - (fConst121 * ((fConst172 * fRec33[2]) + (fConst173 * fRec33[1]))));
			fRec32[0] = ((fConst121 * (((fConst123 * fRec33[1]) + (fConst174 * fRec33[0])) + (fConst174 * fRec33[2]))) - (fConst119 * ((fConst175 * fRec32[2]) + (fConst176 * fRec32[1]))));
			fRec31[0] = ((fConst119 * (((fConst120 * fRec32[1]) + (fConst177 * fRec32[0])) + (fConst177 * fRec32[2]))) - (fConst115 * ((fConst178 * fRec31[2]) + (fConst179 * fRec31[1]))));
			float fTemp75 = (fConst115 * (((fConst118 * fRec31[1]) + (fConst180 * fRec31[0])) + (fConst180 * fRec31[2])));
			fRec30[0] = (fTemp75 - (fConst110 * ((fConst181 * fRec30[2]) + (fConst182 * fRec30[1]))));
			fRec29[0] = ((fConst110 * (((fConst112 * fRec30[1]) + (fConst183 * fRec30[0])) + (fConst183 * fRec30[2]))) - (fConst108 * ((fConst184 * fRec29[2]) + (fConst185 * fRec29[1]))));
			fRec28[0] = ((fConst108 * (((fConst109 * fRec29[1]) + (fConst186 * fRec29[0])) + (fConst186 * fRec29[2]))) - (fConst104 * ((fConst187 * fRec28[2]) + (fConst188 * fRec28[1]))));
			float fTemp76 = (fConst104 * (((fConst107 * fRec28[1]) + (fConst189 * fRec28[0])) + (fConst189 * fRec28[2])));
			fRec27[0] = (fTemp76 - (fConst99 * ((fConst190 * fRec27[2]) + (fConst191 * fRec27[1]))));
			fRec26[0] = ((fConst99 * (((fConst101 * fRec27[1]) + (fConst192 * fRec27[0])) + (fConst192 * fRec27[2]))) - (fConst97 * ((fConst193 * fRec26[2]) + (fConst194 * fRec26[1]))));
			fRec25[0] = ((fConst97 * (((fConst98 * fRec26[1]) + (fConst195 * fRec26[0])) + (fConst195 * fRec26[2]))) - (fConst93 * ((fConst196 * fRec25[2]) + (fConst197 * fRec25[1]))));
			float fTemp77 = (fConst93 * (((fConst96 * fRec25[1]) + (fConst198 * fRec25[0])) + (fConst198 * fRec25[2])));
			fRec24[0] = (fTemp77 - (fConst88 * ((fConst199 * fRec24[2]) + (fConst200 * fRec24[1]))));
			fRec23[0] = ((fConst88 * (((fConst90 * fRec24[1]) + (fConst201 * fRec24[0])) + (fConst201 * fRec24[2]))) - (fConst86 * ((fConst202 * fRec23[2]) + (fConst203 * fRec23[1]))));
			fRec22[0] = ((fConst86 * (((fConst87 * fRec23[1]) + (fConst204 * fRec23[0])) + (fConst204 * fRec23[2]))) - (fConst82 * ((fConst205 * fRec22[2]) + (fConst206 * fRec22[1]))));
			float fTemp78 = (fConst82 * (((fConst85 * fRec22[1]) + (fConst207 * fRec22[0])) + (fConst207 * fRec22[2])));
			fRec21[0] = (fTemp78 - (fConst77 * ((fConst208 * fRec21[2]) + (fConst209 * fRec21[1]))));
			fRec20[0] = ((fConst77 * (((fConst79 * fRec21[1]) + (fConst210 * fRec21[0])) + (fConst210 * fRec21[2]))) - (fConst75 * ((fConst211 * fRec20[2]) + (fConst212 * fRec20[1]))));
			fRec19[0] = ((fConst75 * (((fConst76 * fRec20[1]) + (fConst213 * fRec20[0])) + (fConst213 * fRec20[2]))) - (fConst71 * ((fConst214 * fRec19[2]) + (fConst215 * fRec19[1]))));
			float fTemp79 = (fConst71 * (((fConst74 * fRec19[1]) + (fConst216 * fRec19[0])) + (fConst216 * fRec19[2])));
			fRec18[0] = (fTemp79 - (fConst66 * ((fConst217 * fRec18[2]) + (fConst218 * fRec18[1]))));
			fRec17[0] = ((fConst66 * (((fConst68 * fRec18[1]) + (fConst219 * fRec18[0])) + (fConst219 * fRec18[2]))) - (fConst64 * ((fConst220 * fRec17[2]) + (fConst221 * fRec17[1]))));
			fRec16[0] = ((fConst64 * (((fConst65 * fRec17[1]) + (fConst222 * fRec17[0])) + (fConst222 * fRec17[2]))) - (fConst60 * ((fConst223 * fRec16[2]) + (fConst224 * fRec16[1]))));
			float fTemp80 = (fConst60 * (((fConst63 * fRec16[1]) + (fConst225 * fRec16[0])) + (fConst225 * fRec16[2])));
			fRec15[0] = (fTemp80 - (fConst55 * ((fConst226 * fRec15[2]) + (fConst227 * fRec15[1]))));
			fRec14[0] = ((fConst55 * (((fConst57 * fRec15[1]) + (fConst228 * fRec15[0])) + (fConst228 * fRec15[2]))) - (fConst53 * ((fConst229 * fRec14[2]) + (fConst230 * fRec14[1]))));
			fRec13[0] = ((fConst53 * (((fConst54 * fRec14[1]) + (fConst231 * fRec14[0])) + (fConst231 * fRec14[2]))) - (fConst49 * ((fConst232 * fRec13[2]) + (fConst233 * fRec13[1]))));
			float fTemp81 = (fConst49 * (((fConst52 * fRec13[1]) + (fConst234 * fRec13[0])) + (fConst234 * fRec13[2])));
			fRec12[0] = (fTemp81 - (fConst44 * ((fConst235 * fRec12[2]) + (fConst236 * fRec12[1]))));
			fRec11[0] = ((fConst44 * (((fConst46 * fRec12[1]) + (fConst237 * fRec12[0])) + (fConst237 * fRec12[2]))) - (fConst42 * ((fConst238 * fRec11[2]) + (fConst239 * fRec11[1]))));
			fRec10[0] = ((fConst42 * (((fConst43 * fRec11[1]) + (fConst240 * fRec11[0])) + (fConst240 * fRec11[2]))) - (fConst38 * ((fConst241 * fRec10[2]) + (fConst242 * fRec10[1]))));
			float fTemp82 = (fConst38 * (((fConst41 * fRec10[1]) + (fConst243 * fRec10[0])) + (fConst243 * fRec10[2])));
			fRec9[0] = (fTemp82 - (fConst33 * ((fConst244 * fRec9[2]) + (fConst245 * fRec9[1]))));
			fRec8[0] = ((fConst33 * (((fConst35 * fRec9[1]) + (fConst246 * fRec9[0])) + (fConst246 * fRec9[2]))) - (fConst31 * ((fConst247 * fRec8[2]) + (fConst248 * fRec8[1]))));
			fRec7[0] = ((fConst31 * (((fConst32 * fRec8[1]) + (fConst249 * fRec8[0])) + (fConst249 * fRec8[2]))) - (fConst27 * ((fConst250 * fRec7[2]) + (fConst251 * fRec7[1]))));
			float fTemp83 = (fConst27 * (((fConst30 * fRec7[1]) + (fConst252 * fRec7[0])) + (fConst252 * fRec7[2])));
			fRec6[0] = (fTemp83 - (fConst22 * ((fConst253 * fRec6[2]) + (fConst254 * fRec6[1]))));
			fRec5[0] = ((fConst22 * (((fConst24 * fRec6[1]) + (fConst255 * fRec6[0])) + (fConst255 * fRec6[2]))) - (fConst20 * ((fConst256 * fRec5[2]) + (fConst257 * fRec5[1]))));
			fRec4[0] = ((fConst20 * (((fConst21 * fRec5[1]) + (fConst258 * fRec5[0])) + (fConst258 * fRec5[2]))) - (fConst16 * ((fConst259 * fRec4[2]) + (fConst260 * fRec4[1]))));
			float fTemp84 = (fConst16 * (((fConst19 * fRec4[1]) + (fConst261 * fRec4[0])) + (fConst261 * fRec4[2])));
			fRec3[0] = (fTemp84 - (fConst11 * ((fConst262 * fRec3[2]) + (fConst264 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst265 * fRec3[0])) + (fConst265 * fRec3[2]))) - (fConst8 * ((fConst266 * fRec2[2]) + (fConst267 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst268 * fRec2[0])) + (fConst268 * fRec2[2]))) - (fConst4 * ((fConst269 * fRec1[2]) + (fConst270 * fRec1[1]))));
			fRec0[0] = ((fSlow2 * (float)java.lang.Math.abs((fConst4 * (((fConst7 * fRec1[1]) + (fConst271 * fRec1[0])) + (fConst271 * fRec1[2]))))) + (fSlow1 * fRec0[1]));
			fVbargraph0 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec0[0]))));
			fRec79[0] = (fTemp84 - (fConst288 * ((fConst291 * fRec79[2]) + (fConst292 * fRec79[1]))));
			fRec78[0] = ((fConst288 * (((fConst290 * fRec79[1]) + (fConst293 * fRec79[0])) + (fConst293 * fRec79[2]))) - (fConst286 * ((fConst294 * fRec78[2]) + (fConst295 * fRec78[1]))));
			fRec77[0] = ((fConst286 * (((fConst287 * fRec78[1]) + (fConst296 * fRec78[0])) + (fConst296 * fRec78[2]))) - (fConst284 * ((fConst297 * fRec77[2]) + (fConst298 * fRec77[1]))));
			float fTemp85 = (fConst284 * (((fConst285 * fRec77[1]) + (fConst299 * fRec77[0])) + (fConst299 * fRec77[2])));
			fRec76[0] = (fTemp85 - (fConst281 * ((fConst300 * fRec76[2]) + (fConst302 * fRec76[1]))));
			fRec75[0] = ((fConst281 * (((fConst283 * fRec76[1]) + (fConst303 * fRec76[0])) + (fConst303 * fRec76[2]))) - (fConst278 * ((fConst304 * fRec75[2]) + (fConst305 * fRec75[1]))));
			fRec74[0] = ((fConst278 * (((fConst280 * fRec75[1]) + (fConst306 * fRec75[0])) + (fConst306 * fRec75[2]))) - (fConst274 * ((fConst307 * fRec74[2]) + (fConst308 * fRec74[1]))));
			fRec73[0] = ((fSlow1 * fRec73[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst274 * (((fConst277 * fRec74[1]) + (fConst309 * fRec74[0])) + (fConst309 * fRec74[2]))))));
			fVbargraph1 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec73[0]))));
			fRec83[0] = (fTemp85 - (fConst314 * ((fConst317 * fRec83[2]) + (fConst318 * fRec83[1]))));
			fRec82[0] = ((fConst314 * (((fConst316 * fRec83[1]) + (fConst319 * fRec83[0])) + (fConst319 * fRec83[2]))) - (fConst312 * ((fConst320 * fRec82[2]) + (fConst321 * fRec82[1]))));
			fRec81[0] = ((fConst312 * (((fConst313 * fRec82[1]) + (fConst322 * fRec82[0])) + (fConst322 * fRec82[2]))) - (fConst310 * ((fConst323 * fRec81[2]) + (fConst324 * fRec81[1]))));
			fRec80[0] = ((fSlow1 * fRec80[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst310 * (((fConst311 * fRec81[1]) + (fConst325 * fRec81[0])) + (fConst325 * fRec81[2]))))));
			fVbargraph2 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec80[0]))));
			fRec87[0] = (fTemp72 - (fConst332 * ((fConst335 * fRec87[2]) + (fConst336 * fRec87[1]))));
			fRec86[0] = ((fConst332 * (((fConst334 * fRec87[1]) + (fConst337 * fRec87[0])) + (fConst337 * fRec87[2]))) - (fConst329 * ((fConst338 * fRec86[2]) + (fConst339 * fRec86[1]))));
			fRec85[0] = ((fConst329 * (((fConst331 * fRec86[1]) + (fConst340 * fRec86[0])) + (fConst340 * fRec86[2]))) - (fConst326 * ((fConst341 * fRec85[2]) + (fConst342 * fRec85[1]))));
			fRec84[0] = ((fSlow1 * fRec84[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst326 * (((fConst328 * fRec85[1]) + (fConst343 * fRec85[0])) + (fConst343 * fRec85[2]))))));
			fVbargraph3 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec84[0]))));
			fRec91[0] = (fTemp73 - (fConst350 * ((fConst353 * fRec91[2]) + (fConst354 * fRec91[1]))));
			fRec90[0] = ((fConst350 * (((fConst352 * fRec91[1]) + (fConst355 * fRec91[0])) + (fConst355 * fRec91[2]))) - (fConst347 * ((fConst356 * fRec90[2]) + (fConst357 * fRec90[1]))));
			fRec89[0] = ((fConst347 * (((fConst349 * fRec90[1]) + (fConst358 * fRec90[0])) + (fConst358 * fRec90[2]))) - (fConst344 * ((fConst359 * fRec89[2]) + (fConst360 * fRec89[1]))));
			fRec88[0] = ((fSlow1 * fRec88[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst344 * (((fConst346 * fRec89[1]) + (fConst361 * fRec89[0])) + (fConst361 * fRec89[2]))))));
			fVbargraph4 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec88[0]))));
			fRec95[0] = (fTemp74 - (fConst368 * ((fConst371 * fRec95[2]) + (fConst372 * fRec95[1]))));
			fRec94[0] = ((fConst368 * (((fConst370 * fRec95[1]) + (fConst373 * fRec95[0])) + (fConst373 * fRec95[2]))) - (fConst365 * ((fConst374 * fRec94[2]) + (fConst375 * fRec94[1]))));
			fRec93[0] = ((fConst365 * (((fConst367 * fRec94[1]) + (fConst376 * fRec94[0])) + (fConst376 * fRec94[2]))) - (fConst362 * ((fConst377 * fRec93[2]) + (fConst378 * fRec93[1]))));
			fRec92[0] = ((fSlow1 * fRec92[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst362 * (((fConst364 * fRec93[1]) + (fConst379 * fRec93[0])) + (fConst379 * fRec93[2]))))));
			fVbargraph5 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec92[0]))));
			fRec99[0] = (fTemp75 - (fConst386 * ((fConst389 * fRec99[2]) + (fConst390 * fRec99[1]))));
			fRec98[0] = ((fConst386 * (((fConst388 * fRec99[1]) + (fConst391 * fRec99[0])) + (fConst391 * fRec99[2]))) - (fConst383 * ((fConst392 * fRec98[2]) + (fConst393 * fRec98[1]))));
			fRec97[0] = ((fConst383 * (((fConst385 * fRec98[1]) + (fConst394 * fRec98[0])) + (fConst394 * fRec98[2]))) - (fConst380 * ((fConst395 * fRec97[2]) + (fConst396 * fRec97[1]))));
			fRec96[0] = ((fSlow1 * fRec96[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst380 * (((fConst382 * fRec97[1]) + (fConst397 * fRec97[0])) + (fConst397 * fRec97[2]))))));
			fVbargraph6 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec96[0]))));
			fRec103[0] = (fTemp76 - (fConst404 * ((fConst407 * fRec103[2]) + (fConst408 * fRec103[1]))));
			fRec102[0] = ((fConst404 * (((fConst406 * fRec103[1]) + (fConst409 * fRec103[0])) + (fConst409 * fRec103[2]))) - (fConst401 * ((fConst410 * fRec102[2]) + (fConst411 * fRec102[1]))));
			fRec101[0] = ((fConst401 * (((fConst403 * fRec102[1]) + (fConst412 * fRec102[0])) + (fConst412 * fRec102[2]))) - (fConst398 * ((fConst413 * fRec101[2]) + (fConst414 * fRec101[1]))));
			fRec100[0] = ((fSlow1 * fRec100[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst398 * (((fConst400 * fRec101[1]) + (fConst415 * fRec101[0])) + (fConst415 * fRec101[2]))))));
			fVbargraph7 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec100[0]))));
			fRec107[0] = (fTemp77 - (fConst422 * ((fConst425 * fRec107[2]) + (fConst426 * fRec107[1]))));
			fRec106[0] = ((fConst422 * (((fConst424 * fRec107[1]) + (fConst427 * fRec107[0])) + (fConst427 * fRec107[2]))) - (fConst419 * ((fConst428 * fRec106[2]) + (fConst429 * fRec106[1]))));
			fRec105[0] = ((fConst419 * (((fConst421 * fRec106[1]) + (fConst430 * fRec106[0])) + (fConst430 * fRec106[2]))) - (fConst416 * ((fConst431 * fRec105[2]) + (fConst432 * fRec105[1]))));
			fRec104[0] = ((fSlow1 * fRec104[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst416 * (((fConst418 * fRec105[1]) + (fConst433 * fRec105[0])) + (fConst433 * fRec105[2]))))));
			fVbargraph8 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec104[0]))));
			fRec111[0] = (fTemp78 - (fConst440 * ((fConst443 * fRec111[2]) + (fConst444 * fRec111[1]))));
			fRec110[0] = ((fConst440 * (((fConst442 * fRec111[1]) + (fConst445 * fRec111[0])) + (fConst445 * fRec111[2]))) - (fConst437 * ((fConst446 * fRec110[2]) + (fConst447 * fRec110[1]))));
			fRec109[0] = ((fConst437 * (((fConst439 * fRec110[1]) + (fConst448 * fRec110[0])) + (fConst448 * fRec110[2]))) - (fConst434 * ((fConst449 * fRec109[2]) + (fConst450 * fRec109[1]))));
			fRec108[0] = ((fSlow1 * fRec108[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst434 * (((fConst436 * fRec109[1]) + (fConst451 * fRec109[0])) + (fConst451 * fRec109[2]))))));
			fVbargraph9 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec108[0]))));
			fRec115[0] = (fTemp79 - (fConst458 * ((fConst461 * fRec115[2]) + (fConst462 * fRec115[1]))));
			fRec114[0] = ((fConst458 * (((fConst460 * fRec115[1]) + (fConst463 * fRec115[0])) + (fConst463 * fRec115[2]))) - (fConst455 * ((fConst464 * fRec114[2]) + (fConst465 * fRec114[1]))));
			fRec113[0] = ((fConst455 * (((fConst457 * fRec114[1]) + (fConst466 * fRec114[0])) + (fConst466 * fRec114[2]))) - (fConst452 * ((fConst467 * fRec113[2]) + (fConst468 * fRec113[1]))));
			fRec112[0] = ((fSlow1 * fRec112[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst452 * (((fConst454 * fRec113[1]) + (fConst469 * fRec113[0])) + (fConst469 * fRec113[2]))))));
			fVbargraph10 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec112[0]))));
			fRec119[0] = (fTemp80 - (fConst476 * ((fConst479 * fRec119[2]) + (fConst480 * fRec119[1]))));
			fRec118[0] = ((fConst476 * (((fConst478 * fRec119[1]) + (fConst481 * fRec119[0])) + (fConst481 * fRec119[2]))) - (fConst473 * ((fConst482 * fRec118[2]) + (fConst483 * fRec118[1]))));
			fRec117[0] = ((fConst473 * (((fConst475 * fRec118[1]) + (fConst484 * fRec118[0])) + (fConst484 * fRec118[2]))) - (fConst470 * ((fConst485 * fRec117[2]) + (fConst486 * fRec117[1]))));
			fRec116[0] = ((fSlow1 * fRec116[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst470 * (((fConst472 * fRec117[1]) + (fConst487 * fRec117[0])) + (fConst487 * fRec117[2]))))));
			fVbargraph11 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec116[0]))));
			fRec123[0] = (fTemp81 - (fConst494 * ((fConst497 * fRec123[2]) + (fConst498 * fRec123[1]))));
			fRec122[0] = ((fConst494 * (((fConst496 * fRec123[1]) + (fConst499 * fRec123[0])) + (fConst499 * fRec123[2]))) - (fConst491 * ((fConst500 * fRec122[2]) + (fConst501 * fRec122[1]))));
			fRec121[0] = ((fConst491 * (((fConst493 * fRec122[1]) + (fConst502 * fRec122[0])) + (fConst502 * fRec122[2]))) - (fConst488 * ((fConst503 * fRec121[2]) + (fConst504 * fRec121[1]))));
			fRec120[0] = ((fSlow1 * fRec120[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst488 * (((fConst490 * fRec121[1]) + (fConst505 * fRec121[0])) + (fConst505 * fRec121[2]))))));
			fVbargraph12 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec120[0]))));
			fRec127[0] = (fTemp82 - (fConst512 * ((fConst515 * fRec127[2]) + (fConst516 * fRec127[1]))));
			fRec126[0] = ((fConst512 * (((fConst514 * fRec127[1]) + (fConst517 * fRec127[0])) + (fConst517 * fRec127[2]))) - (fConst509 * ((fConst518 * fRec126[2]) + (fConst519 * fRec126[1]))));
			fRec125[0] = ((fConst509 * (((fConst511 * fRec126[1]) + (fConst520 * fRec126[0])) + (fConst520 * fRec126[2]))) - (fConst506 * ((fConst521 * fRec125[2]) + (fConst522 * fRec125[1]))));
			fRec124[0] = ((fSlow1 * fRec124[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst506 * (((fConst508 * fRec125[1]) + (fConst523 * fRec125[0])) + (fConst523 * fRec125[2]))))));
			fVbargraph13 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec124[0]))));
			fRec131[0] = (fTemp83 - (fConst530 * ((fConst533 * fRec131[2]) + (fConst534 * fRec131[1]))));
			fRec130[0] = ((fConst530 * (((fConst532 * fRec131[1]) + (fConst535 * fRec131[0])) + (fConst535 * fRec131[2]))) - (fConst527 * ((fConst536 * fRec130[2]) + (fConst537 * fRec130[1]))));
			fRec129[0] = ((fConst527 * (((fConst529 * fRec130[1]) + (fConst538 * fRec130[0])) + (fConst538 * fRec130[2]))) - (fConst524 * ((fConst539 * fRec129[2]) + (fConst540 * fRec129[1]))));
			fRec128[0] = ((fSlow1 * fRec128[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst524 * (((fConst526 * fRec129[1]) + (fConst541 * fRec129[0])) + (fConst541 * fRec129[2]))))));
			fVbargraph14 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec128[0]))));
			output0[i] = fTemp72;
			output1[i] = fTemp72;
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec40[1] = fRec40[0];
			fRec51[1] = fRec51[0];
			fRec53[1] = fRec53[0];
			fRec54[1] = fRec54[0];
			fRec56[1] = fRec56[0];
			fVec1[1] = fVec1[0];
			fRec55[1] = fRec55[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec57[1] = fRec57[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec58[1] = fRec58[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			iRec59[1] = iRec59[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec60[j1] = fRec60[(j1 - 1)];
				
			}
			fRec61[1] = fRec61[0];
			fRec62[1] = fRec62[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec50[1] = fRec50[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec63[1] = fRec63[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec69[1] = fRec69[0];
			fRec67[1] = fRec67[0];
			fRec72[1] = fRec72[0];
			fRec70[1] = fRec70[0];
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
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[1] = fRec73[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[1] = fRec80[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[1] = fRec84[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[1] = fRec88[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[1] = fRec92[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[1] = fRec96[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[1] = fRec100[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[1] = fRec104[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[1] = fRec108[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec114[2] = fRec114[1];
			fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[1] = fRec112[0];
			fRec119[2] = fRec119[1];
			fRec119[1] = fRec119[0];
			fRec118[2] = fRec118[1];
			fRec118[1] = fRec118[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[1] = fRec116[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[1] = fRec120[0];
			fRec127[2] = fRec127[1];
			fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec124[1] = fRec124[0];
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

