/* ------------------------------------------------------------
name: "spectralTiltLab"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: java, -scal -ftz 0
------------------------------------------------------------ */

public class mydsp extends dsp {
	
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
	float fCheckbox0;
	float fConst113;
	float fHslider2;
	float fHslider3;
	float fHslider4;
	float fConst114;
	int iVec0[] = new int[4];
	float fVslider0;
	float fRec41[] = new float[2];
	float fCheckbox1;
	float fCheckbox2;
	float fEntry0;
	float fConst115;
	float fVslider1;
	float fVslider2;
	float fRec43[] = new float[2];
	float fVec1[] = new float[2];
	float fRec42[] = new float[2];
	float fConst116;
	float fVec2[] = new float[2];
	float fConst117;
	float fVec3[] = new float[2];
	float fVec4[] = new float[2];
	float fConst118;
	float fVec5[] = new float[2];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2];
	float fVslider3;
	float fVec8[] = new float[2];
	float fRec44[] = new float[2];
	float fVec9[] = new float[2];
	float fVec10[] = new float[2];
	float fVec11[] = new float[2];
	float fVec12[] = new float[2];
	float fVec13[] = new float[2];
	float fVec14[] = new float[2];
	float fVslider4;
	float fVec15[] = new float[2];
	float fRec45[] = new float[2];
	float fVec16[] = new float[2];
	float fVec17[] = new float[2];
	float fVec18[] = new float[2];
	float fVec19[] = new float[2];
	float fVec20[] = new float[2];
	float fVec21[] = new float[2];
	float fCheckbox3;
	int iRec46[] = new int[2];
	float fRec47[] = new float[4];
	float fVec22[] = new float[2];
	float fRec40[] = new float[2];
	float fVec23[] = new float[2];
	float fRec39[] = new float[2];
	float fVec24[] = new float[2];
	float fRec38[] = new float[2];
	float fVec25[] = new float[2];
	float fRec37[] = new float[2];
	float fVec26[] = new float[2];
	float fRec36[] = new float[2];
	float fVec27[] = new float[2];
	float fRec35[] = new float[2];
	float fVec28[] = new float[2];
	float fRec34[] = new float[2];
	float fVec29[] = new float[2];
	float fRec33[] = new float[2];
	float fVec30[] = new float[2];
	float fRec32[] = new float[2];
	float fVec31[] = new float[2];
	float fRec31[] = new float[2];
	float fConst119;
	float fConst120;
	float fRec30[] = new float[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec29[] = new float[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec28[] = new float[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec27[] = new float[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec26[] = new float[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec25[] = new float[3];
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec24[] = new float[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec23[] = new float[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fRec22[] = new float[3];
	float fConst145;
	float fConst146;
	float fConst147;
	float fRec21[] = new float[3];
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec20[] = new float[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fRec19[] = new float[3];
	float fConst154;
	float fConst155;
	float fConst156;
	float fRec18[] = new float[3];
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec17[] = new float[3];
	float fConst160;
	float fConst161;
	float fConst162;
	float fRec16[] = new float[3];
	float fConst163;
	float fConst164;
	float fConst165;
	float fRec15[] = new float[3];
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec14[] = new float[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec13[] = new float[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec12[] = new float[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec11[] = new float[3];
	float fConst178;
	float fConst179;
	float fConst180;
	float fRec10[] = new float[3];
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec9[] = new float[3];
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec8[] = new float[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fRec7[] = new float[3];
	float fConst190;
	float fConst191;
	float fConst192;
	float fRec6[] = new float[3];
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec5[] = new float[3];
	float fConst196;
	float fConst197;
	float fConst198;
	float fRec4[] = new float[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec3[] = new float[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec2[] = new float[3];
	float fConst206;
	float fConst207;
	float fConst208;
	float fRec1[] = new float[3];
	float fConst209;
	float fRec0[] = new float[2];
	float fVbargraph0;
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
	float fConst224;
	float fConst225;
	float fConst226;
	float fConst227;
	float fConst228;
	float fConst229;
	float fConst230;
	float fRec54[] = new float[3];
	float fConst231;
	float fConst232;
	float fConst233;
	float fRec53[] = new float[3];
	float fConst234;
	float fConst235;
	float fConst236;
	float fRec52[] = new float[3];
	float fConst237;
	float fConst238;
	float fConst239;
	float fConst240;
	float fRec51[] = new float[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fRec50[] = new float[3];
	float fConst244;
	float fConst245;
	float fConst246;
	float fRec49[] = new float[3];
	float fConst247;
	float fRec48[] = new float[2];
	float fVbargraph1;
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
	float fConst262;
	float fConst263;
	float fConst264;
	float fConst265;
	float fConst266;
	float fConst267;
	float fConst268;
	float fRec61[] = new float[3];
	float fConst269;
	float fConst270;
	float fConst271;
	float fRec60[] = new float[3];
	float fConst272;
	float fConst273;
	float fConst274;
	float fRec59[] = new float[3];
	float fConst275;
	float fConst276;
	float fConst277;
	float fConst278;
	float fRec58[] = new float[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fRec57[] = new float[3];
	float fConst282;
	float fConst283;
	float fConst284;
	float fRec56[] = new float[3];
	float fConst285;
	float fRec55[] = new float[2];
	float fVbargraph2;
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
	float fConst300;
	float fConst301;
	float fConst302;
	float fConst303;
	float fConst304;
	float fConst305;
	float fConst306;
	float fRec68[] = new float[3];
	float fConst307;
	float fConst308;
	float fConst309;
	float fRec67[] = new float[3];
	float fConst310;
	float fConst311;
	float fConst312;
	float fRec66[] = new float[3];
	float fConst313;
	float fConst314;
	float fConst315;
	float fConst316;
	float fRec65[] = new float[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fRec64[] = new float[3];
	float fConst320;
	float fConst321;
	float fConst322;
	float fRec63[] = new float[3];
	float fConst323;
	float fRec62[] = new float[2];
	float fVbargraph3;
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
	float fConst338;
	float fConst339;
	float fConst340;
	float fConst341;
	float fConst342;
	float fConst343;
	float fConst344;
	float fRec75[] = new float[3];
	float fConst345;
	float fConst346;
	float fConst347;
	float fRec74[] = new float[3];
	float fConst348;
	float fConst349;
	float fConst350;
	float fRec73[] = new float[3];
	float fConst351;
	float fConst352;
	float fConst353;
	float fConst354;
	float fRec72[] = new float[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fRec71[] = new float[3];
	float fConst358;
	float fConst359;
	float fConst360;
	float fRec70[] = new float[3];
	float fConst361;
	float fRec69[] = new float[2];
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
	float fRec79[] = new float[3];
	float fConst371;
	float fConst372;
	float fConst373;
	float fRec78[] = new float[3];
	float fConst374;
	float fConst375;
	float fConst376;
	float fRec77[] = new float[3];
	float fConst377;
	float fRec76[] = new float[2];
	float fVbargraph5;
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
	float fRec83[] = new float[3];
	float fConst389;
	float fConst390;
	float fConst391;
	float fRec82[] = new float[3];
	float fConst392;
	float fConst393;
	float fConst394;
	float fRec81[] = new float[3];
	float fConst395;
	float fRec80[] = new float[2];
	float fVbargraph6;
	float fConst396;
	float fConst397;
	float fConst398;
	float fConst399;
	float fConst400;
	float fConst401;
	float fConst402;
	float fConst403;
	float fConst404;
	float fConst405;
	float fConst406;
	float fRec87[] = new float[3];
	float fConst407;
	float fConst408;
	float fConst409;
	float fRec86[] = new float[3];
	float fConst410;
	float fConst411;
	float fConst412;
	float fRec85[] = new float[3];
	float fConst413;
	float fRec84[] = new float[2];
	float fVbargraph7;
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
	float fRec91[] = new float[3];
	float fConst425;
	float fConst426;
	float fConst427;
	float fRec90[] = new float[3];
	float fConst428;
	float fConst429;
	float fConst430;
	float fRec89[] = new float[3];
	float fConst431;
	float fRec88[] = new float[2];
	float fVbargraph8;
	float fConst432;
	float fConst433;
	float fConst434;
	float fConst435;
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec95[] = new float[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec94[] = new float[3];
	float fConst446;
	float fConst447;
	float fConst448;
	float fRec93[] = new float[3];
	float fConst449;
	float fRec92[] = new float[2];
	float fVbargraph9;
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
	float fRec99[] = new float[3];
	float fConst461;
	float fConst462;
	float fConst463;
	float fRec98[] = new float[3];
	float fConst464;
	float fConst465;
	float fConst466;
	float fRec97[] = new float[3];
	float fConst467;
	float fRec96[] = new float[2];
	float fVbargraph10;
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
	float fConst478;
	float fRec103[] = new float[3];
	float fConst479;
	float fConst480;
	float fConst481;
	float fRec102[] = new float[3];
	float fConst482;
	float fConst483;
	float fConst484;
	float fRec101[] = new float[3];
	float fConst485;
	float fRec100[] = new float[2];
	float fVbargraph11;
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
	float fRec107[] = new float[3];
	float fConst497;
	float fConst498;
	float fConst499;
	float fRec106[] = new float[3];
	float fConst500;
	float fConst501;
	float fConst502;
	float fRec105[] = new float[3];
	float fConst503;
	float fRec104[] = new float[2];
	float fVbargraph12;
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
	float fRec111[] = new float[3];
	float fConst515;
	float fConst516;
	float fConst517;
	float fRec110[] = new float[3];
	float fConst518;
	float fConst519;
	float fConst520;
	float fRec109[] = new float[3];
	float fConst521;
	float fRec108[] = new float[2];
	float fVbargraph13;
	float fConst522;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fRec115[] = new float[3];
	float fConst533;
	float fConst534;
	float fConst535;
	float fRec114[] = new float[3];
	float fConst536;
	float fConst537;
	float fConst538;
	float fRec113[] = new float[3];
	float fConst539;
	float fRec112[] = new float[2];
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
		m.declare("name", "spectralTiltLab");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	int getNumInputs() {
		return 1;
		
	}
	int getNumOutputs() {
		return 1;
		
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
		fConst2 = (float)java.lang.Math.tan((785.398193f / fConst0));
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
		fConst14 = (float)java.lang.Math.tan((1246.74182f / fConst0));
		fConst15 = (1.0f / fConst14);
		fConst16 = (1.0f / (((fConst15 + 0.168404877f) / fConst14) + 1.06935835f));
		fConst17 = mydsp_faustpower2_f(fConst14);
		fConst18 = (1.0f / fConst17);
		fConst19 = (2.0f * (53.5361519f - fConst18));
		fConst20 = (1.0f / (((fConst15 + 0.51247865f) / fConst14) + 0.689621389f));
		fConst21 = (2.0f * (7.62173128f - fConst18));
		fConst22 = (1.0f / (((fConst15 + 0.782413065f) / fConst14) + 0.245291501f));
		fConst23 = (9.99999975e-05f / fConst17);
		fConst24 = (fConst23 + 0.000433227193f);
		fConst25 = (float)java.lang.Math.tan((1979.07935f / fConst0));
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
		fConst36 = (float)java.lang.Math.tan((3141.59277f / fConst0));
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
		fConst47 = (float)java.lang.Math.tan((4986.96729f / fConst0));
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
		fConst58 = (float)java.lang.Math.tan((7916.31738f / fConst0));
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
		fConst69 = (float)java.lang.Math.tan((12566.3711f / fConst0));
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
		fConst80 = (float)java.lang.Math.tan((19947.8691f / fConst0));
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
		fConst91 = (float)java.lang.Math.tan((31665.2695f / fConst0));
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
		fConst102 = (float)java.lang.Math.tan((50265.4844f / fConst0));
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
		fConst113 = (3.14159274f / fConst0);
		fConst114 = (1.0f / (float)java.lang.Math.tan((0.5f / fConst0)));
		fConst115 = (1.0f / fConst0);
		fConst116 = (0.25f * fConst0);
		fConst117 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst118 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst119 = (((fConst103 + -0.782413065f) / fConst102) + 0.245291501f);
		fConst120 = (2.0f * (0.245291501f - fConst106));
		fConst121 = (fConst111 + 0.000433227193f);
		fConst122 = (((fConst103 + -0.51247865f) / fConst102) + 0.689621389f);
		fConst123 = (2.0f * (0.689621389f - fConst106));
		fConst124 = (fConst106 + 7.62173128f);
		fConst125 = (((fConst103 + -0.168404877f) / fConst102) + 1.06935835f);
		fConst126 = (2.0f * (1.06935835f - fConst106));
		fConst127 = (fConst106 + 53.5361519f);
		fConst128 = (((fConst92 + -0.782413065f) / fConst91) + 0.245291501f);
		fConst129 = (2.0f * (0.245291501f - fConst95));
		fConst130 = (fConst100 + 0.000433227193f);
		fConst131 = (((fConst92 + -0.51247865f) / fConst91) + 0.689621389f);
		fConst132 = (2.0f * (0.689621389f - fConst95));
		fConst133 = (fConst95 + 7.62173128f);
		fConst134 = (((fConst92 + -0.168404877f) / fConst91) + 1.06935835f);
		fConst135 = (2.0f * (1.06935835f - fConst95));
		fConst136 = (fConst95 + 53.5361519f);
		fConst137 = (((fConst81 + -0.782413065f) / fConst80) + 0.245291501f);
		fConst138 = (2.0f * (0.245291501f - fConst84));
		fConst139 = (fConst89 + 0.000433227193f);
		fConst140 = (((fConst81 + -0.51247865f) / fConst80) + 0.689621389f);
		fConst141 = (2.0f * (0.689621389f - fConst84));
		fConst142 = (fConst84 + 7.62173128f);
		fConst143 = (((fConst81 + -0.168404877f) / fConst80) + 1.06935835f);
		fConst144 = (2.0f * (1.06935835f - fConst84));
		fConst145 = (fConst84 + 53.5361519f);
		fConst146 = (((fConst70 + -0.782413065f) / fConst69) + 0.245291501f);
		fConst147 = (2.0f * (0.245291501f - fConst73));
		fConst148 = (fConst78 + 0.000433227193f);
		fConst149 = (((fConst70 + -0.51247865f) / fConst69) + 0.689621389f);
		fConst150 = (2.0f * (0.689621389f - fConst73));
		fConst151 = (fConst73 + 7.62173128f);
		fConst152 = (((fConst70 + -0.168404877f) / fConst69) + 1.06935835f);
		fConst153 = (2.0f * (1.06935835f - fConst73));
		fConst154 = (fConst73 + 53.5361519f);
		fConst155 = (((fConst59 + -0.782413065f) / fConst58) + 0.245291501f);
		fConst156 = (2.0f * (0.245291501f - fConst62));
		fConst157 = (fConst67 + 0.000433227193f);
		fConst158 = (((fConst59 + -0.51247865f) / fConst58) + 0.689621389f);
		fConst159 = (2.0f * (0.689621389f - fConst62));
		fConst160 = (fConst62 + 7.62173128f);
		fConst161 = (((fConst59 + -0.168404877f) / fConst58) + 1.06935835f);
		fConst162 = (2.0f * (1.06935835f - fConst62));
		fConst163 = (fConst62 + 53.5361519f);
		fConst164 = (((fConst48 + -0.782413065f) / fConst47) + 0.245291501f);
		fConst165 = (2.0f * (0.245291501f - fConst51));
		fConst166 = (fConst56 + 0.000433227193f);
		fConst167 = (((fConst48 + -0.51247865f) / fConst47) + 0.689621389f);
		fConst168 = (2.0f * (0.689621389f - fConst51));
		fConst169 = (fConst51 + 7.62173128f);
		fConst170 = (((fConst48 + -0.168404877f) / fConst47) + 1.06935835f);
		fConst171 = (2.0f * (1.06935835f - fConst51));
		fConst172 = (fConst51 + 53.5361519f);
		fConst173 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst174 = (2.0f * (0.245291501f - fConst40));
		fConst175 = (fConst45 + 0.000433227193f);
		fConst176 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst177 = (2.0f * (0.689621389f - fConst40));
		fConst178 = (fConst40 + 7.62173128f);
		fConst179 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst180 = (2.0f * (1.06935835f - fConst40));
		fConst181 = (fConst40 + 53.5361519f);
		fConst182 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst183 = (2.0f * (0.245291501f - fConst29));
		fConst184 = (fConst34 + 0.000433227193f);
		fConst185 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst186 = (2.0f * (0.689621389f - fConst29));
		fConst187 = (fConst29 + 7.62173128f);
		fConst188 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst189 = (2.0f * (1.06935835f - fConst29));
		fConst190 = (fConst29 + 53.5361519f);
		fConst191 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst192 = (2.0f * (0.245291501f - fConst18));
		fConst193 = (2.0f * (0.000433227193f - fConst23));
		fConst194 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst195 = (2.0f * (0.689621389f - fConst18));
		fConst196 = (fConst18 + 7.62173128f);
		fConst197 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst198 = (2.0f * (1.06935835f - fConst18));
		fConst199 = (fConst18 + 53.5361519f);
		fConst200 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst201 = (1.0f / fConst5);
		fConst202 = (2.0f * (4.07678175f - fConst201));
		fConst203 = (fConst12 + 0.000407678192f);
		fConst204 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst205 = (2.0f * (1.4500711f - fConst201));
		fConst206 = (fConst9 + 1.4500711f);
		fConst207 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst208 = (2.0f * (0.935140193f - fConst201));
		fConst209 = (fConst6 + 0.935140193f);
		fConst210 = (float)java.lang.Math.tan((494.769836f / fConst0));
		fConst211 = (1.0f / fConst210);
		fConst212 = (1.0f / (((fConst211 + 0.157482162f) / fConst210) + 0.935140193f));
		fConst213 = mydsp_faustpower2_f(fConst210);
		fConst214 = (50.0638084f / fConst213);
		fConst215 = (2.0f * (0.935140193f - fConst214));
		fConst216 = (1.0f / (((fConst211 + 0.743130445f) / fConst210) + 1.4500711f));
		fConst217 = (11.0520525f / fConst213);
		fConst218 = (2.0f * (1.4500711f - fConst217));
		fConst219 = (1.0f / (((fConst211 + 3.18972731f) / fConst210) + 4.07678175f));
		fConst220 = (0.00176617282f / fConst213);
		fConst221 = (2.0f * (0.000407678192f - fConst220));
		fConst222 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst223 = (2.0f * (53.5361519f - fConst201));
		fConst224 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst225 = (2.0f * (7.62173128f - fConst201));
		fConst226 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst227 = (9.99999975e-05f / fConst5);
		fConst228 = (2.0f * (0.000433227193f - fConst227));
		fConst229 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst230 = (2.0f * (0.245291501f - fConst201));
		fConst231 = (fConst227 + 0.000433227193f);
		fConst232 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst233 = (2.0f * (0.689621389f - fConst201));
		fConst234 = (fConst201 + 7.62173128f);
		fConst235 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst236 = (2.0f * (1.06935835f - fConst201));
		fConst237 = (fConst201 + 53.5361519f);
		fConst238 = (((fConst211 + -3.18972731f) / fConst210) + 4.07678175f);
		fConst239 = (1.0f / fConst213);
		fConst240 = (2.0f * (4.07678175f - fConst239));
		fConst241 = (fConst220 + 0.000407678192f);
		fConst242 = (((fConst211 + -0.743130445f) / fConst210) + 1.4500711f);
		fConst243 = (2.0f * (1.4500711f - fConst239));
		fConst244 = (fConst217 + 1.4500711f);
		fConst245 = (((fConst211 + -0.157482162f) / fConst210) + 0.935140193f);
		fConst246 = (2.0f * (0.935140193f - fConst239));
		fConst247 = (fConst214 + 0.935140193f);
		fConst248 = (float)java.lang.Math.tan((311.685455f / fConst0));
		fConst249 = (1.0f / fConst248);
		fConst250 = (1.0f / (((fConst249 + 0.157482162f) / fConst248) + 0.935140193f));
		fConst251 = mydsp_faustpower2_f(fConst248);
		fConst252 = (50.0638084f / fConst251);
		fConst253 = (2.0f * (0.935140193f - fConst252));
		fConst254 = (1.0f / (((fConst249 + 0.743130445f) / fConst248) + 1.4500711f));
		fConst255 = (11.0520525f / fConst251);
		fConst256 = (2.0f * (1.4500711f - fConst255));
		fConst257 = (1.0f / (((fConst249 + 3.18972731f) / fConst248) + 4.07678175f));
		fConst258 = (0.00176617282f / fConst251);
		fConst259 = (2.0f * (0.000407678192f - fConst258));
		fConst260 = (1.0f / (((fConst211 + 0.168404877f) / fConst210) + 1.06935835f));
		fConst261 = (2.0f * (53.5361519f - fConst239));
		fConst262 = (1.0f / (((fConst211 + 0.51247865f) / fConst210) + 0.689621389f));
		fConst263 = (2.0f * (7.62173128f - fConst239));
		fConst264 = (1.0f / (((fConst211 + 0.782413065f) / fConst210) + 0.245291501f));
		fConst265 = (9.99999975e-05f / fConst213);
		fConst266 = (2.0f * (0.000433227193f - fConst265));
		fConst267 = (((fConst211 + -0.782413065f) / fConst210) + 0.245291501f);
		fConst268 = (2.0f * (0.245291501f - fConst239));
		fConst269 = (fConst265 + 0.000433227193f);
		fConst270 = (((fConst211 + -0.51247865f) / fConst210) + 0.689621389f);
		fConst271 = (2.0f * (0.689621389f - fConst239));
		fConst272 = (fConst239 + 7.62173128f);
		fConst273 = (((fConst211 + -0.168404877f) / fConst210) + 1.06935835f);
		fConst274 = (2.0f * (1.06935835f - fConst239));
		fConst275 = (fConst239 + 53.5361519f);
		fConst276 = (((fConst249 + -3.18972731f) / fConst248) + 4.07678175f);
		fConst277 = (1.0f / fConst251);
		fConst278 = (2.0f * (4.07678175f - fConst277));
		fConst279 = (fConst258 + 0.000407678192f);
		fConst280 = (((fConst249 + -0.743130445f) / fConst248) + 1.4500711f);
		fConst281 = (2.0f * (1.4500711f - fConst277));
		fConst282 = (fConst255 + 1.4500711f);
		fConst283 = (((fConst249 + -0.157482162f) / fConst248) + 0.935140193f);
		fConst284 = (2.0f * (0.935140193f - fConst277));
		fConst285 = (fConst252 + 0.935140193f);
		fConst286 = (float)java.lang.Math.tan((196.349548f / fConst0));
		fConst287 = (1.0f / fConst286);
		fConst288 = (1.0f / (((fConst287 + 0.157482162f) / fConst286) + 0.935140193f));
		fConst289 = mydsp_faustpower2_f(fConst286);
		fConst290 = (50.0638084f / fConst289);
		fConst291 = (2.0f * (0.935140193f - fConst290));
		fConst292 = (1.0f / (((fConst287 + 0.743130445f) / fConst286) + 1.4500711f));
		fConst293 = (11.0520525f / fConst289);
		fConst294 = (2.0f * (1.4500711f - fConst293));
		fConst295 = (1.0f / (((fConst287 + 3.18972731f) / fConst286) + 4.07678175f));
		fConst296 = (0.00176617282f / fConst289);
		fConst297 = (2.0f * (0.000407678192f - fConst296));
		fConst298 = (1.0f / (((fConst249 + 0.168404877f) / fConst248) + 1.06935835f));
		fConst299 = (2.0f * (53.5361519f - fConst277));
		fConst300 = (1.0f / (((fConst249 + 0.51247865f) / fConst248) + 0.689621389f));
		fConst301 = (2.0f * (7.62173128f - fConst277));
		fConst302 = (1.0f / (((fConst249 + 0.782413065f) / fConst248) + 0.245291501f));
		fConst303 = (9.99999975e-05f / fConst251);
		fConst304 = (2.0f * (0.000433227193f - fConst303));
		fConst305 = (((fConst249 + -0.782413065f) / fConst248) + 0.245291501f);
		fConst306 = (2.0f * (0.245291501f - fConst277));
		fConst307 = (fConst303 + 0.000433227193f);
		fConst308 = (((fConst249 + -0.51247865f) / fConst248) + 0.689621389f);
		fConst309 = (2.0f * (0.689621389f - fConst277));
		fConst310 = (fConst277 + 7.62173128f);
		fConst311 = (((fConst249 + -0.168404877f) / fConst248) + 1.06935835f);
		fConst312 = (2.0f * (1.06935835f - fConst277));
		fConst313 = (fConst277 + 53.5361519f);
		fConst314 = (((fConst287 + -3.18972731f) / fConst286) + 4.07678175f);
		fConst315 = (1.0f / fConst289);
		fConst316 = (2.0f * (4.07678175f - fConst315));
		fConst317 = (fConst296 + 0.000407678192f);
		fConst318 = (((fConst287 + -0.743130445f) / fConst286) + 1.4500711f);
		fConst319 = (2.0f * (1.4500711f - fConst315));
		fConst320 = (fConst293 + 1.4500711f);
		fConst321 = (((fConst287 + -0.157482162f) / fConst286) + 0.935140193f);
		fConst322 = (2.0f * (0.935140193f - fConst315));
		fConst323 = (fConst290 + 0.935140193f);
		fConst324 = (float)java.lang.Math.tan((123.692459f / fConst0));
		fConst325 = (1.0f / fConst324);
		fConst326 = (1.0f / (((fConst325 + 0.157482162f) / fConst324) + 0.935140193f));
		fConst327 = mydsp_faustpower2_f(fConst324);
		fConst328 = (50.0638084f / fConst327);
		fConst329 = (2.0f * (0.935140193f - fConst328));
		fConst330 = (1.0f / (((fConst325 + 0.743130445f) / fConst324) + 1.4500711f));
		fConst331 = (11.0520525f / fConst327);
		fConst332 = (2.0f * (1.4500711f - fConst331));
		fConst333 = (1.0f / (((fConst325 + 3.18972731f) / fConst324) + 4.07678175f));
		fConst334 = (0.00176617282f / fConst327);
		fConst335 = (2.0f * (0.000407678192f - fConst334));
		fConst336 = (1.0f / (((fConst287 + 0.168404877f) / fConst286) + 1.06935835f));
		fConst337 = (2.0f * (53.5361519f - fConst315));
		fConst338 = (1.0f / (((fConst287 + 0.51247865f) / fConst286) + 0.689621389f));
		fConst339 = (2.0f * (7.62173128f - fConst315));
		fConst340 = (1.0f / (((fConst287 + 0.782413065f) / fConst286) + 0.245291501f));
		fConst341 = (9.99999975e-05f / fConst289);
		fConst342 = (2.0f * (0.000433227193f - fConst341));
		fConst343 = (((fConst287 + -0.782413065f) / fConst286) + 0.245291501f);
		fConst344 = (2.0f * (0.245291501f - fConst315));
		fConst345 = (fConst341 + 0.000433227193f);
		fConst346 = (((fConst287 + -0.51247865f) / fConst286) + 0.689621389f);
		fConst347 = (2.0f * (0.689621389f - fConst315));
		fConst348 = (fConst315 + 7.62173128f);
		fConst349 = (((fConst287 + -0.168404877f) / fConst286) + 1.06935835f);
		fConst350 = (2.0f * (1.06935835f - fConst315));
		fConst351 = (fConst315 + 53.5361519f);
		fConst352 = (((fConst325 + -3.18972731f) / fConst324) + 4.07678175f);
		fConst353 = (1.0f / fConst327);
		fConst354 = (2.0f * (4.07678175f - fConst353));
		fConst355 = (fConst334 + 0.000407678192f);
		fConst356 = (((fConst325 + -0.743130445f) / fConst324) + 1.4500711f);
		fConst357 = (2.0f * (1.4500711f - fConst353));
		fConst358 = (fConst331 + 1.4500711f);
		fConst359 = (((fConst325 + -0.157482162f) / fConst324) + 0.935140193f);
		fConst360 = (2.0f * (0.935140193f - fConst353));
		fConst361 = (fConst328 + 0.935140193f);
		fConst362 = (1.0f / (((fConst325 + 0.168404877f) / fConst324) + 1.06935835f));
		fConst363 = (2.0f * (53.5361519f - fConst353));
		fConst364 = (1.0f / (((fConst325 + 0.51247865f) / fConst324) + 0.689621389f));
		fConst365 = (2.0f * (7.62173128f - fConst353));
		fConst366 = (1.0f / (((fConst325 + 0.782413065f) / fConst324) + 0.245291501f));
		fConst367 = (9.99999975e-05f / fConst327);
		fConst368 = (2.0f * (0.000433227193f - fConst367));
		fConst369 = (((fConst325 + -0.782413065f) / fConst324) + 0.245291501f);
		fConst370 = (2.0f * (0.245291501f - fConst353));
		fConst371 = (fConst367 + 0.000433227193f);
		fConst372 = (((fConst325 + -0.51247865f) / fConst324) + 0.689621389f);
		fConst373 = (2.0f * (0.689621389f - fConst353));
		fConst374 = (fConst353 + 7.62173128f);
		fConst375 = (((fConst325 + -0.168404877f) / fConst324) + 1.06935835f);
		fConst376 = (2.0f * (1.06935835f - fConst353));
		fConst377 = (fConst353 + 53.5361519f);
		fConst378 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst379 = (50.0638084f / fConst39);
		fConst380 = (2.0f * (0.935140193f - fConst379));
		fConst381 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst382 = (11.0520525f / fConst39);
		fConst383 = (2.0f * (1.4500711f - fConst382));
		fConst384 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst385 = (0.00176617282f / fConst39);
		fConst386 = (2.0f * (0.000407678192f - fConst385));
		fConst387 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst388 = (2.0f * (4.07678175f - fConst40));
		fConst389 = (fConst385 + 0.000407678192f);
		fConst390 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst391 = (2.0f * (1.4500711f - fConst40));
		fConst392 = (fConst382 + 1.4500711f);
		fConst393 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst394 = (2.0f * (0.935140193f - fConst40));
		fConst395 = (fConst379 + 0.935140193f);
		fConst396 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst397 = (50.0638084f / fConst28);
		fConst398 = (2.0f * (0.935140193f - fConst397));
		fConst399 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst400 = (11.0520525f / fConst28);
		fConst401 = (2.0f * (1.4500711f - fConst400));
		fConst402 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst403 = (0.00176617282f / fConst28);
		fConst404 = (2.0f * (0.000407678192f - fConst403));
		fConst405 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst406 = (2.0f * (4.07678175f - fConst29));
		fConst407 = (fConst403 + 0.000407678192f);
		fConst408 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst409 = (2.0f * (1.4500711f - fConst29));
		fConst410 = (fConst400 + 1.4500711f);
		fConst411 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst412 = (2.0f * (0.935140193f - fConst29));
		fConst413 = (fConst397 + 0.935140193f);
		fConst414 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst415 = (50.0638084f / fConst17);
		fConst416 = (2.0f * (0.935140193f - fConst415));
		fConst417 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst418 = (11.0520525f / fConst17);
		fConst419 = (2.0f * (1.4500711f - fConst418));
		fConst420 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst421 = (0.00176617282f / fConst17);
		fConst422 = (2.0f * (0.000407678192f - fConst421));
		fConst423 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst424 = (2.0f * (4.07678175f - fConst18));
		fConst425 = (fConst421 + 0.000407678192f);
		fConst426 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst427 = (2.0f * (1.4500711f - fConst18));
		fConst428 = (fConst418 + 1.4500711f);
		fConst429 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst430 = (2.0f * (0.935140193f - fConst18));
		fConst431 = (fConst415 + 0.935140193f);
		fConst432 = (1.0f / (((fConst103 + 0.157482162f) / fConst102) + 0.935140193f));
		fConst433 = (50.0638084f / fConst105);
		fConst434 = (2.0f * (0.935140193f - fConst433));
		fConst435 = (1.0f / (((fConst103 + 0.743130445f) / fConst102) + 1.4500711f));
		fConst436 = (11.0520525f / fConst105);
		fConst437 = (2.0f * (1.4500711f - fConst436));
		fConst438 = (1.0f / (((fConst103 + 3.18972731f) / fConst102) + 4.07678175f));
		fConst439 = (0.00176617282f / fConst105);
		fConst440 = (2.0f * (0.000407678192f - fConst439));
		fConst441 = (((fConst103 + -3.18972731f) / fConst102) + 4.07678175f);
		fConst442 = (2.0f * (4.07678175f - fConst106));
		fConst443 = (fConst439 + 0.000407678192f);
		fConst444 = (((fConst103 + -0.743130445f) / fConst102) + 1.4500711f);
		fConst445 = (2.0f * (1.4500711f - fConst106));
		fConst446 = (fConst436 + 1.4500711f);
		fConst447 = (((fConst103 + -0.157482162f) / fConst102) + 0.935140193f);
		fConst448 = (2.0f * (0.935140193f - fConst106));
		fConst449 = (fConst433 + 0.935140193f);
		fConst450 = (1.0f / (((fConst92 + 0.157482162f) / fConst91) + 0.935140193f));
		fConst451 = (50.0638084f / fConst94);
		fConst452 = (2.0f * (0.935140193f - fConst451));
		fConst453 = (1.0f / (((fConst92 + 0.743130445f) / fConst91) + 1.4500711f));
		fConst454 = (11.0520525f / fConst94);
		fConst455 = (2.0f * (1.4500711f - fConst454));
		fConst456 = (1.0f / (((fConst92 + 3.18972731f) / fConst91) + 4.07678175f));
		fConst457 = (0.00176617282f / fConst94);
		fConst458 = (2.0f * (0.000407678192f - fConst457));
		fConst459 = (((fConst92 + -3.18972731f) / fConst91) + 4.07678175f);
		fConst460 = (2.0f * (4.07678175f - fConst95));
		fConst461 = (fConst457 + 0.000407678192f);
		fConst462 = (((fConst92 + -0.743130445f) / fConst91) + 1.4500711f);
		fConst463 = (2.0f * (1.4500711f - fConst95));
		fConst464 = (fConst454 + 1.4500711f);
		fConst465 = (((fConst92 + -0.157482162f) / fConst91) + 0.935140193f);
		fConst466 = (2.0f * (0.935140193f - fConst95));
		fConst467 = (fConst451 + 0.935140193f);
		fConst468 = (1.0f / (((fConst81 + 0.157482162f) / fConst80) + 0.935140193f));
		fConst469 = (50.0638084f / fConst83);
		fConst470 = (2.0f * (0.935140193f - fConst469));
		fConst471 = (1.0f / (((fConst81 + 0.743130445f) / fConst80) + 1.4500711f));
		fConst472 = (11.0520525f / fConst83);
		fConst473 = (2.0f * (1.4500711f - fConst472));
		fConst474 = (1.0f / (((fConst81 + 3.18972731f) / fConst80) + 4.07678175f));
		fConst475 = (0.00176617282f / fConst83);
		fConst476 = (2.0f * (0.000407678192f - fConst475));
		fConst477 = (((fConst81 + -3.18972731f) / fConst80) + 4.07678175f);
		fConst478 = (2.0f * (4.07678175f - fConst84));
		fConst479 = (fConst475 + 0.000407678192f);
		fConst480 = (((fConst81 + -0.743130445f) / fConst80) + 1.4500711f);
		fConst481 = (2.0f * (1.4500711f - fConst84));
		fConst482 = (fConst472 + 1.4500711f);
		fConst483 = (((fConst81 + -0.157482162f) / fConst80) + 0.935140193f);
		fConst484 = (2.0f * (0.935140193f - fConst84));
		fConst485 = (fConst469 + 0.935140193f);
		fConst486 = (1.0f / (((fConst70 + 0.157482162f) / fConst69) + 0.935140193f));
		fConst487 = (50.0638084f / fConst72);
		fConst488 = (2.0f * (0.935140193f - fConst487));
		fConst489 = (1.0f / (((fConst70 + 0.743130445f) / fConst69) + 1.4500711f));
		fConst490 = (11.0520525f / fConst72);
		fConst491 = (2.0f * (1.4500711f - fConst490));
		fConst492 = (1.0f / (((fConst70 + 3.18972731f) / fConst69) + 4.07678175f));
		fConst493 = (0.00176617282f / fConst72);
		fConst494 = (2.0f * (0.000407678192f - fConst493));
		fConst495 = (((fConst70 + -3.18972731f) / fConst69) + 4.07678175f);
		fConst496 = (2.0f * (4.07678175f - fConst73));
		fConst497 = (fConst493 + 0.000407678192f);
		fConst498 = (((fConst70 + -0.743130445f) / fConst69) + 1.4500711f);
		fConst499 = (2.0f * (1.4500711f - fConst73));
		fConst500 = (fConst490 + 1.4500711f);
		fConst501 = (((fConst70 + -0.157482162f) / fConst69) + 0.935140193f);
		fConst502 = (2.0f * (0.935140193f - fConst73));
		fConst503 = (fConst487 + 0.935140193f);
		fConst504 = (1.0f / (((fConst59 + 0.157482162f) / fConst58) + 0.935140193f));
		fConst505 = (50.0638084f / fConst61);
		fConst506 = (2.0f * (0.935140193f - fConst505));
		fConst507 = (1.0f / (((fConst59 + 0.743130445f) / fConst58) + 1.4500711f));
		fConst508 = (11.0520525f / fConst61);
		fConst509 = (2.0f * (1.4500711f - fConst508));
		fConst510 = (1.0f / (((fConst59 + 3.18972731f) / fConst58) + 4.07678175f));
		fConst511 = (0.00176617282f / fConst61);
		fConst512 = (2.0f * (0.000407678192f - fConst511));
		fConst513 = (((fConst59 + -3.18972731f) / fConst58) + 4.07678175f);
		fConst514 = (2.0f * (4.07678175f - fConst62));
		fConst515 = (fConst511 + 0.000407678192f);
		fConst516 = (((fConst59 + -0.743130445f) / fConst58) + 1.4500711f);
		fConst517 = (2.0f * (1.4500711f - fConst62));
		fConst518 = (fConst508 + 1.4500711f);
		fConst519 = (((fConst59 + -0.157482162f) / fConst58) + 0.935140193f);
		fConst520 = (2.0f * (0.935140193f - fConst62));
		fConst521 = (fConst505 + 0.935140193f);
		fConst522 = (1.0f / (((fConst48 + 0.157482162f) / fConst47) + 0.935140193f));
		fConst523 = (50.0638084f / fConst50);
		fConst524 = (2.0f * (0.935140193f - fConst523));
		fConst525 = (1.0f / (((fConst48 + 0.743130445f) / fConst47) + 1.4500711f));
		fConst526 = (11.0520525f / fConst50);
		fConst527 = (2.0f * (1.4500711f - fConst526));
		fConst528 = (1.0f / (((fConst48 + 3.18972731f) / fConst47) + 4.07678175f));
		fConst529 = (0.00176617282f / fConst50);
		fConst530 = (2.0f * (0.000407678192f - fConst529));
		fConst531 = (((fConst48 + -3.18972731f) / fConst47) + 4.07678175f);
		fConst532 = (2.0f * (4.07678175f - fConst51));
		fConst533 = (fConst529 + 0.000407678192f);
		fConst534 = (((fConst48 + -0.743130445f) / fConst47) + 1.4500711f);
		fConst535 = (2.0f * (1.4500711f - fConst51));
		fConst536 = (fConst526 + 1.4500711f);
		fConst537 = (((fConst48 + -0.157482162f) / fConst47) + 0.935140193f);
		fConst538 = (2.0f * (0.935140193f - fConst51));
		fConst539 = (fConst523 + 0.935140193f);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)50.0f;
		fHslider1 = (float)100.0f;
		fCheckbox0 = (float)0.0f;
		fHslider2 = (float)100.0f;
		fHslider3 = (float)5000.0f;
		fHslider4 = (float)-0.5f;
		fVslider0 = (float)-20.0f;
		fCheckbox1 = (float)0.0f;
		fCheckbox2 = (float)0.0f;
		fEntry0 = (float)2.0f;
		fVslider1 = (float)49.0f;
		fVslider2 = (float)0.10000000000000001f;
		fVslider3 = (float)-0.10000000000000001f;
		fVslider4 = (float)0.10000000000000001f;
		fCheckbox3 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec41[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec43[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec42[l4] = 0.0f;
			
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
			fRec44[l12] = 0.0f;
			
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
			fRec45[l20] = 0.0f;
			
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
			iRec46[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec47[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec22[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec40[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec23[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec39[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec24[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec38[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec25[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec37[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec26[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec36[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fVec27[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec35[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fVec28[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec34[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec29[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec33[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec30[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec32[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec31[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec31[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec30[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec29[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec28[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec27[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec26[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec25[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec24[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec23[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec22[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec21[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec20[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec19[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec18[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec17[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec16[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec15[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec14[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec13[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec12[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec11[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec10[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec9[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec8[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec7[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec6[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec5[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec4[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec3[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec2[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec1[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec0[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec54[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec53[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec52[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec51[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec50[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec49[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec48[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec61[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec60[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec59[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec58[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec57[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec56[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec55[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec68[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec67[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec66[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec65[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec64[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec63[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec62[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec75[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec74[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec73[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec72[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec71[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec70[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec69[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec79[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec78[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec77[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec76[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec83[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec82[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec81[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec80[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec87[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec86[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec85[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec84[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec91[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec90[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec89[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec88[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec95[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec94[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec93[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec92[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec99[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec98[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec97[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			fRec96[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec103[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec102[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec101[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec100[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec107[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec106[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec105[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			fRec104[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec111[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec110[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec109[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec108[l143] = 0.0f;
			
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
		ui_interface.openVerticalBox("spectralTiltLab");
		ui_interface.declare("0", "1", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
		ui_interface.openVerticalBox("Spectral Tilt Filter");
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.addHorizontalSlider("Slope of Spectral Tilt across Band", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, -0.5f, -1.0f, 1.0f, 0.00100000005f);
		ui_interface.declare("0", "1", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
		ui_interface.openVerticalBox("Spectral Tilt Filter");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.addCheckButton("Bypass Spectral Tilt", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.closeBox();
		ui_interface.declare("fHslider2", "2", "");
		ui_interface.declare("fHslider2", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Start Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 100.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Width", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 5000.0f, 100.0f, 10000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.declare("0", "tooltip", "See Faust's oscillator.lib for sawtooth_demo");
		ui_interface.openVerticalBox("Test Signal");
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
		ui_interface.declare("fCheckbox2", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.declare("fCheckbox3", "1", "");
		ui_interface.declare("fCheckbox3", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", new FaustVarAccess() {
				public String getId() { return "fCheckbox3"; }
				public void set(float val) { fCheckbox3 = val; }
				public float get() { return (float)fCheckbox3; }
			}
			);
		ui_interface.declare("fCheckbox1", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for spectral_level_demo");
		ui_interface.openVerticalBox("Spectrum Analyzer");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph5", "0", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe09579fa00", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph4", "1", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe09578e0a0", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph3", "2", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe09576bf50", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph2", "3", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe095749e00", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph1", "4", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe095727cb0", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph0", "5", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe095705d80", new FaustVarAccess() {
				public String getId() { return "fVbargraph0"; }
				public void set(float val) { fVbargraph0 = val; }
				public float get() { return (float)fVbargraph0; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe0957d6780", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe0957c41a0", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe0957b1bc0", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph14", "9", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe095849490", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph13", "10", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe095836ca0", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph12", "11", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe0958244b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph11", "12", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe095811cc0", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph10", "13", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe0957fb550", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph9", "14", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe0957e8d60", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
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
		float fSlow0 = fHslider0;
		float fSlow1 = (float)java.lang.Math.exp((0.0f - (fConst1 / fHslider1)));
		float fSlow2 = (1.0f - fSlow1);
		int iSlow3 = (int)fCheckbox0;
		float fSlow4 = fHslider2;
		float fSlow5 = (float)java.lang.Math.pow(((fSlow4 + fHslider3) / fSlow4), 0.111111112f);
		float fSlow6 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower9_f(fSlow5))));
		float fSlow7 = fHslider4;
		float fSlow8 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (9.0f - fSlow7)))));
		float fSlow9 = (fSlow6 / fSlow8);
		float fSlow10 = (float)java.lang.Math.tan((fConst113 * fSlow4));
		float fSlow11 = (6.28318548f * ((fSlow4 * fSlow6) / fSlow10));
		float fSlow12 = (fConst114 + fSlow11);
		float fSlow13 = (0.0f - ((fSlow11 - fConst114) / fSlow12));
		float fSlow14 = (1.0f / fSlow12);
		float fSlow15 = (6.28318548f * ((fSlow4 * fSlow8) / fSlow10));
		float fSlow16 = (fSlow15 - fConst114);
		float fSlow17 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower8_f(fSlow5))));
		float fSlow18 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (8.0f - fSlow7)))));
		float fSlow19 = (fSlow17 / fSlow18);
		float fSlow20 = (6.28318548f * ((fSlow4 * fSlow17) / fSlow10));
		float fSlow21 = (fConst114 + fSlow20);
		float fSlow22 = (0.0f - ((fSlow20 - fConst114) / fSlow21));
		float fSlow23 = (1.0f / fSlow21);
		float fSlow24 = (6.28318548f * ((fSlow4 * fSlow18) / fSlow10));
		float fSlow25 = (fSlow24 - fConst114);
		float fSlow26 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower7_f(fSlow5))));
		float fSlow27 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (7.0f - fSlow7)))));
		float fSlow28 = (fSlow26 / fSlow27);
		float fSlow29 = (6.28318548f * ((fSlow4 * fSlow26) / fSlow10));
		float fSlow30 = (fConst114 + fSlow29);
		float fSlow31 = (0.0f - ((fSlow29 - fConst114) / fSlow30));
		float fSlow32 = (1.0f / fSlow30);
		float fSlow33 = (6.28318548f * ((fSlow4 * fSlow27) / fSlow10));
		float fSlow34 = (fSlow33 - fConst114);
		float fSlow35 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower6_f(fSlow5))));
		float fSlow36 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (6.0f - fSlow7)))));
		float fSlow37 = (fSlow35 / fSlow36);
		float fSlow38 = (6.28318548f * ((fSlow4 * fSlow35) / fSlow10));
		float fSlow39 = (fConst114 + fSlow38);
		float fSlow40 = (0.0f - ((fSlow38 - fConst114) / fSlow39));
		float fSlow41 = (1.0f / fSlow39);
		float fSlow42 = (6.28318548f * ((fSlow4 * fSlow36) / fSlow10));
		float fSlow43 = (fSlow42 - fConst114);
		float fSlow44 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower5_f(fSlow5))));
		float fSlow45 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (5.0f - fSlow7)))));
		float fSlow46 = (fSlow44 / fSlow45);
		float fSlow47 = (6.28318548f * ((fSlow4 * fSlow44) / fSlow10));
		float fSlow48 = (fConst114 + fSlow47);
		float fSlow49 = (0.0f - ((fSlow47 - fConst114) / fSlow48));
		float fSlow50 = (1.0f / fSlow48);
		float fSlow51 = (6.28318548f * ((fSlow4 * fSlow45) / fSlow10));
		float fSlow52 = (fSlow51 - fConst114);
		float fSlow53 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower4_f(fSlow5))));
		float fSlow54 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (4.0f - fSlow7)))));
		float fSlow55 = (fSlow53 / fSlow54);
		float fSlow56 = (6.28318548f * ((fSlow4 * fSlow53) / fSlow10));
		float fSlow57 = (fConst114 + fSlow56);
		float fSlow58 = (0.0f - ((fSlow56 - fConst114) / fSlow57));
		float fSlow59 = (1.0f / fSlow57);
		float fSlow60 = (6.28318548f * ((fSlow4 * fSlow54) / fSlow10));
		float fSlow61 = (fSlow60 - fConst114);
		float fSlow62 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower3_f(fSlow5))));
		float fSlow63 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (3.0f - fSlow7)))));
		float fSlow64 = (fSlow62 / fSlow63);
		float fSlow65 = (6.28318548f * ((fSlow4 * fSlow62) / fSlow10));
		float fSlow66 = (fConst114 + fSlow65);
		float fSlow67 = (0.0f - ((fSlow65 - fConst114) / fSlow66));
		float fSlow68 = (1.0f / fSlow66);
		float fSlow69 = (6.28318548f * ((fSlow4 * fSlow63) / fSlow10));
		float fSlow70 = (fSlow69 - fConst114);
		float fSlow71 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * mydsp_faustpower2_f(fSlow5))));
		float fSlow72 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (2.0f - fSlow7)))));
		float fSlow73 = (fSlow71 / fSlow72);
		float fSlow74 = (6.28318548f * ((fSlow4 * fSlow71) / fSlow10));
		float fSlow75 = (fConst114 + fSlow74);
		float fSlow76 = (0.0f - ((fSlow74 - fConst114) / fSlow75));
		float fSlow77 = (1.0f / fSlow75);
		float fSlow78 = (6.28318548f * ((fSlow4 * fSlow72) / fSlow10));
		float fSlow79 = (fSlow78 - fConst114);
		float fSlow80 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * fSlow5)));
		float fSlow81 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (1.0f - fSlow7)))));
		float fSlow82 = (fSlow80 / fSlow81);
		float fSlow83 = (6.28318548f * ((fSlow4 * fSlow80) / fSlow10));
		float fSlow84 = (fConst114 + fSlow83);
		float fSlow85 = (0.0f - ((fSlow83 - fConst114) / fSlow84));
		float fSlow86 = (1.0f / fSlow84);
		float fSlow87 = (6.28318548f * ((fSlow4 * fSlow81) / fSlow10));
		float fSlow88 = (fSlow87 - fConst114);
		float fSlow89 = (float)java.lang.Math.tan((fConst113 * (fSlow4 * (float)java.lang.Math.pow(fSlow5, (0.0f - fSlow7)))));
		float fSlow90 = (fSlow10 / fSlow89);
		float fSlow91 = (6.28318548f * fSlow4);
		float fSlow92 = (fConst114 + fSlow91);
		float fSlow93 = (0.0f - ((fSlow91 - fConst114) / fSlow92));
		float fSlow94 = (1.0f / fSlow92);
		float fSlow95 = (6.28318548f * ((fSlow4 * fSlow89) / fSlow10));
		float fSlow96 = (fConst114 + fSlow95);
		float fSlow97 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		int iSlow98 = (int)fCheckbox1;
		int iSlow99 = (int)fCheckbox2;
		int iSlow100 = (int)(fEntry0 + -1.0f);
		int iSlow101 = (iSlow100 >= 2);
		int iSlow102 = (iSlow100 >= 1);
		float fSlow103 = (float)java.lang.Math.exp((0.0f - (fConst115 / fVslider2)));
		float fSlow104 = (440.0f * ((float)java.lang.Math.pow(2.0f, (0.0833333358f * (fVslider1 + -49.0f))) * (1.0f - fSlow103)));
		int iSlow105 = (iSlow100 >= 3);
		float fSlow106 = ((0.00999999978f * fVslider3) + 1.0f);
		float fSlow107 = ((0.00999999978f * fVslider4) + 1.0f);
		int iSlow108 = (int)fCheckbox3;
		float fSlow109 = (fSlow95 - fConst114);
		float fSlow110 = ((fSlow10 * (fConst114 + fSlow87)) / fSlow89);
		float fSlow111 = ((fSlow80 * (fConst114 + fSlow78)) / fSlow81);
		float fSlow112 = ((fSlow71 * (fConst114 + fSlow69)) / fSlow72);
		float fSlow113 = ((fSlow62 * (fConst114 + fSlow60)) / fSlow63);
		float fSlow114 = ((fSlow53 * (fConst114 + fSlow51)) / fSlow54);
		float fSlow115 = ((fSlow44 * (fConst114 + fSlow42)) / fSlow45);
		float fSlow116 = ((fSlow35 * (fConst114 + fSlow33)) / fSlow36);
		float fSlow117 = ((fSlow26 * (fConst114 + fSlow24)) / fSlow27);
		float fSlow118 = ((fSlow17 * (fConst114 + fSlow15)) / fSlow18);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec41[0] = (fSlow97 + (0.999000013f * fRec41[1]));
			fRec43[0] = (fSlow104 + (fSlow103 * fRec43[1]));
			float fTemp0 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fRec43[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec42[1] + (fConst115 * fVec1[1]));
			fRec42[0] = (fTemp1 - (float)java.lang.Math.floor(fTemp1));
			float fTemp2 = (2.0f * fRec42[0]);
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
			float fTemp10 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow106 * fRec43[0])));
			fVec8[0] = fTemp10;
			float fTemp11 = (fRec44[1] + (fConst115 * fVec8[1]));
			fRec44[0] = (fTemp11 - (float)java.lang.Math.floor(fTemp11));
			float fTemp12 = (2.0f * fRec44[0]);
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
			float fTemp20 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow107 * fRec43[0])));
			fVec15[0] = fTemp20;
			float fTemp21 = (fRec45[1] + (fConst115 * fVec15[1]));
			fRec45[0] = (fTemp21 - (float)java.lang.Math.floor(fTemp21));
			float fTemp22 = (2.0f * fRec45[0]);
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
			iRec46[0] = ((1103515245 * iRec46[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * (float)iRec46[0]);
			fRec47[0] = (((0.522189379f * fRec47[3]) + (fTemp30 + (2.49495602f * fRec47[1]))) - (2.0172658f * fRec47[2]));
			float fTemp31 = (fRec41[0] * (((iSlow98==0)?true:false)?input0[i]:(((iSlow99==0)?true:false)?(((iSlow108==0)?true:false)?(((0.0499220341f * fRec47[0]) + (0.0506126992f * fRec47[2])) - ((0.0959935337f * fRec47[1]) + (0.00440878607f * fRec47[3]))):fTemp30):(0.333333343f * (fRec41[0] * (((((iSlow101==0)?true:false)?(((iSlow105==0)?true:false)?(fConst118 * (((float)iVec0[3] * (fTemp9 - fVec7[1])) / fTemp0)):(fConst117 * (((float)iVec0[2] * (fTemp6 - fVec4[1])) / fTemp0))):(((iSlow102==0)?true:false)?(fConst116 * (((float)iVec0[1] * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (((iSlow101==0)?true:false)?(((iSlow105==0)?true:false)?(fConst118 * (((float)iVec0[3] * (fTemp19 - fVec14[1])) / fTemp10)):(fConst117 * (((float)iVec0[2] * (fTemp16 - fVec11[1])) / fTemp10))):(((iSlow102==0)?true:false)?(fConst116 * (((float)iVec0[1] * (fTemp14 - fVec9[1])) / fTemp10)):fTemp13))) + (((iSlow101==0)?true:false)?(((iSlow105==0)?true:false)?(fConst118 * (((float)iVec0[3] * (fTemp29 - fVec21[1])) / fTemp20)):(fConst117 * (((float)iVec0[2] * (fTemp26 - fVec18[1])) / fTemp20))):(((iSlow102==0)?true:false)?(fConst116 * (((float)iVec0[1] * (fTemp24 - fVec16[1])) / fTemp20)):fTemp23))))))));
			float fTemp32 = (((iSlow3==0)?true:false)?0.0f:fTemp31);
			fVec22[0] = fTemp32;
			fRec40[0] = ((fSlow93 * fRec40[1]) + (fSlow94 * ((fSlow96 * fTemp32) + (fSlow109 * fVec22[1]))));
			fVec23[0] = (fSlow90 * fRec40[0]);
			fRec39[0] = ((fSlow85 * fRec39[1]) + (fSlow86 * ((fSlow88 * fVec23[1]) + (fSlow110 * fRec40[0]))));
			fVec24[0] = (fSlow82 * fRec39[0]);
			fRec38[0] = ((fSlow76 * fRec38[1]) + (fSlow77 * ((fSlow79 * fVec24[1]) + (fSlow111 * fRec39[0]))));
			fVec25[0] = (fSlow73 * fRec38[0]);
			fRec37[0] = ((fSlow67 * fRec37[1]) + (fSlow68 * ((fSlow70 * fVec25[1]) + (fSlow112 * fRec38[0]))));
			fVec26[0] = (fSlow64 * fRec37[0]);
			fRec36[0] = ((fSlow58 * fRec36[1]) + (fSlow59 * ((fSlow61 * fVec26[1]) + (fSlow113 * fRec37[0]))));
			fVec27[0] = (fSlow55 * fRec36[0]);
			fRec35[0] = ((fSlow49 * fRec35[1]) + (fSlow50 * ((fSlow52 * fVec27[1]) + (fSlow114 * fRec36[0]))));
			fVec28[0] = (fSlow46 * fRec35[0]);
			fRec34[0] = ((fSlow40 * fRec34[1]) + (fSlow41 * ((fSlow43 * fVec28[1]) + (fSlow115 * fRec35[0]))));
			fVec29[0] = (fSlow37 * fRec34[0]);
			fRec33[0] = ((fSlow31 * fRec33[1]) + (fSlow32 * ((fSlow34 * fVec29[1]) + (fSlow116 * fRec34[0]))));
			fVec30[0] = (fSlow28 * fRec33[0]);
			fRec32[0] = ((fSlow22 * fRec32[1]) + (fSlow23 * ((fSlow25 * fVec30[1]) + (fSlow117 * fRec33[0]))));
			fVec31[0] = (fSlow19 * fRec32[0]);
			fRec31[0] = ((fSlow13 * fRec31[1]) + (fSlow14 * ((fSlow16 * fVec31[1]) + (fSlow118 * fRec32[0]))));
			float fTemp33 = (((iSlow3==0)?true:false)?fTemp31:(fSlow9 * fRec31[0]));
			fRec30[0] = (fTemp33 - (fConst110 * ((fConst119 * fRec30[2]) + (fConst120 * fRec30[1]))));
			fRec29[0] = ((fConst110 * (((fConst112 * fRec30[1]) + (fConst121 * fRec30[0])) + (fConst121 * fRec30[2]))) - (fConst108 * ((fConst122 * fRec29[2]) + (fConst123 * fRec29[1]))));
			fRec28[0] = ((fConst108 * (((fConst109 * fRec29[1]) + (fConst124 * fRec29[0])) + (fConst124 * fRec29[2]))) - (fConst104 * ((fConst125 * fRec28[2]) + (fConst126 * fRec28[1]))));
			float fTemp34 = (fConst104 * (((fConst107 * fRec28[1]) + (fConst127 * fRec28[0])) + (fConst127 * fRec28[2])));
			fRec27[0] = (fTemp34 - (fConst99 * ((fConst128 * fRec27[2]) + (fConst129 * fRec27[1]))));
			fRec26[0] = ((fConst99 * (((fConst101 * fRec27[1]) + (fConst130 * fRec27[0])) + (fConst130 * fRec27[2]))) - (fConst97 * ((fConst131 * fRec26[2]) + (fConst132 * fRec26[1]))));
			fRec25[0] = ((fConst97 * (((fConst98 * fRec26[1]) + (fConst133 * fRec26[0])) + (fConst133 * fRec26[2]))) - (fConst93 * ((fConst134 * fRec25[2]) + (fConst135 * fRec25[1]))));
			float fTemp35 = (fConst93 * (((fConst96 * fRec25[1]) + (fConst136 * fRec25[0])) + (fConst136 * fRec25[2])));
			fRec24[0] = (fTemp35 - (fConst88 * ((fConst137 * fRec24[2]) + (fConst138 * fRec24[1]))));
			fRec23[0] = ((fConst88 * (((fConst90 * fRec24[1]) + (fConst139 * fRec24[0])) + (fConst139 * fRec24[2]))) - (fConst86 * ((fConst140 * fRec23[2]) + (fConst141 * fRec23[1]))));
			fRec22[0] = ((fConst86 * (((fConst87 * fRec23[1]) + (fConst142 * fRec23[0])) + (fConst142 * fRec23[2]))) - (fConst82 * ((fConst143 * fRec22[2]) + (fConst144 * fRec22[1]))));
			float fTemp36 = (fConst82 * (((fConst85 * fRec22[1]) + (fConst145 * fRec22[0])) + (fConst145 * fRec22[2])));
			fRec21[0] = (fTemp36 - (fConst77 * ((fConst146 * fRec21[2]) + (fConst147 * fRec21[1]))));
			fRec20[0] = ((fConst77 * (((fConst79 * fRec21[1]) + (fConst148 * fRec21[0])) + (fConst148 * fRec21[2]))) - (fConst75 * ((fConst149 * fRec20[2]) + (fConst150 * fRec20[1]))));
			fRec19[0] = ((fConst75 * (((fConst76 * fRec20[1]) + (fConst151 * fRec20[0])) + (fConst151 * fRec20[2]))) - (fConst71 * ((fConst152 * fRec19[2]) + (fConst153 * fRec19[1]))));
			float fTemp37 = (fConst71 * (((fConst74 * fRec19[1]) + (fConst154 * fRec19[0])) + (fConst154 * fRec19[2])));
			fRec18[0] = (fTemp37 - (fConst66 * ((fConst155 * fRec18[2]) + (fConst156 * fRec18[1]))));
			fRec17[0] = ((fConst66 * (((fConst68 * fRec18[1]) + (fConst157 * fRec18[0])) + (fConst157 * fRec18[2]))) - (fConst64 * ((fConst158 * fRec17[2]) + (fConst159 * fRec17[1]))));
			fRec16[0] = ((fConst64 * (((fConst65 * fRec17[1]) + (fConst160 * fRec17[0])) + (fConst160 * fRec17[2]))) - (fConst60 * ((fConst161 * fRec16[2]) + (fConst162 * fRec16[1]))));
			float fTemp38 = (fConst60 * (((fConst63 * fRec16[1]) + (fConst163 * fRec16[0])) + (fConst163 * fRec16[2])));
			fRec15[0] = (fTemp38 - (fConst55 * ((fConst164 * fRec15[2]) + (fConst165 * fRec15[1]))));
			fRec14[0] = ((fConst55 * (((fConst57 * fRec15[1]) + (fConst166 * fRec15[0])) + (fConst166 * fRec15[2]))) - (fConst53 * ((fConst167 * fRec14[2]) + (fConst168 * fRec14[1]))));
			fRec13[0] = ((fConst53 * (((fConst54 * fRec14[1]) + (fConst169 * fRec14[0])) + (fConst169 * fRec14[2]))) - (fConst49 * ((fConst170 * fRec13[2]) + (fConst171 * fRec13[1]))));
			float fTemp39 = (fConst49 * (((fConst52 * fRec13[1]) + (fConst172 * fRec13[0])) + (fConst172 * fRec13[2])));
			fRec12[0] = (fTemp39 - (fConst44 * ((fConst173 * fRec12[2]) + (fConst174 * fRec12[1]))));
			fRec11[0] = ((fConst44 * (((fConst46 * fRec12[1]) + (fConst175 * fRec12[0])) + (fConst175 * fRec12[2]))) - (fConst42 * ((fConst176 * fRec11[2]) + (fConst177 * fRec11[1]))));
			fRec10[0] = ((fConst42 * (((fConst43 * fRec11[1]) + (fConst178 * fRec11[0])) + (fConst178 * fRec11[2]))) - (fConst38 * ((fConst179 * fRec10[2]) + (fConst180 * fRec10[1]))));
			float fTemp40 = (fConst38 * (((fConst41 * fRec10[1]) + (fConst181 * fRec10[0])) + (fConst181 * fRec10[2])));
			fRec9[0] = (fTemp40 - (fConst33 * ((fConst182 * fRec9[2]) + (fConst183 * fRec9[1]))));
			fRec8[0] = ((fConst33 * (((fConst35 * fRec9[1]) + (fConst184 * fRec9[0])) + (fConst184 * fRec9[2]))) - (fConst31 * ((fConst185 * fRec8[2]) + (fConst186 * fRec8[1]))));
			fRec7[0] = ((fConst31 * (((fConst32 * fRec8[1]) + (fConst187 * fRec8[0])) + (fConst187 * fRec8[2]))) - (fConst27 * ((fConst188 * fRec7[2]) + (fConst189 * fRec7[1]))));
			float fTemp41 = (fConst27 * (((fConst30 * fRec7[1]) + (fConst190 * fRec7[0])) + (fConst190 * fRec7[2])));
			fRec6[0] = (fTemp41 - (fConst22 * ((fConst191 * fRec6[2]) + (fConst192 * fRec6[1]))));
			fRec5[0] = ((fConst22 * (((fConst24 * fRec6[0]) + (fConst193 * fRec6[1])) + (fConst24 * fRec6[2]))) - (fConst20 * ((fConst194 * fRec5[2]) + (fConst195 * fRec5[1]))));
			fRec4[0] = ((fConst20 * (((fConst21 * fRec5[1]) + (fConst196 * fRec5[0])) + (fConst196 * fRec5[2]))) - (fConst16 * ((fConst197 * fRec4[2]) + (fConst198 * fRec4[1]))));
			float fTemp42 = (fConst16 * (((fConst19 * fRec4[1]) + (fConst199 * fRec4[0])) + (fConst199 * fRec4[2])));
			fRec3[0] = (fTemp42 - (fConst11 * ((fConst200 * fRec3[2]) + (fConst202 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst203 * fRec3[0])) + (fConst203 * fRec3[2]))) - (fConst8 * ((fConst204 * fRec2[2]) + (fConst205 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst206 * fRec2[0])) + (fConst206 * fRec2[2]))) - (fConst4 * ((fConst207 * fRec1[2]) + (fConst208 * fRec1[1]))));
			fRec0[0] = ((fSlow2 * (float)java.lang.Math.abs((fConst4 * (((fConst7 * fRec1[1]) + (fConst209 * fRec1[0])) + (fConst209 * fRec1[2]))))) + (fSlow1 * fRec0[1]));
			fVbargraph0 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec0[0]))));
			fRec54[0] = (fTemp42 - (fConst226 * ((fConst229 * fRec54[2]) + (fConst230 * fRec54[1]))));
			fRec53[0] = ((fConst226 * (((fConst228 * fRec54[1]) + (fConst231 * fRec54[0])) + (fConst231 * fRec54[2]))) - (fConst224 * ((fConst232 * fRec53[2]) + (fConst233 * fRec53[1]))));
			fRec52[0] = ((fConst224 * (((fConst225 * fRec53[1]) + (fConst234 * fRec53[0])) + (fConst234 * fRec53[2]))) - (fConst222 * ((fConst235 * fRec52[2]) + (fConst236 * fRec52[1]))));
			float fTemp43 = (fConst222 * (((fConst223 * fRec52[1]) + (fConst237 * fRec52[0])) + (fConst237 * fRec52[2])));
			fRec51[0] = (fTemp43 - (fConst219 * ((fConst238 * fRec51[2]) + (fConst240 * fRec51[1]))));
			fRec50[0] = ((fConst219 * (((fConst221 * fRec51[1]) + (fConst241 * fRec51[0])) + (fConst241 * fRec51[2]))) - (fConst216 * ((fConst242 * fRec50[2]) + (fConst243 * fRec50[1]))));
			fRec49[0] = ((fConst216 * (((fConst218 * fRec50[1]) + (fConst244 * fRec50[0])) + (fConst244 * fRec50[2]))) - (fConst212 * ((fConst245 * fRec49[2]) + (fConst246 * fRec49[1]))));
			fRec48[0] = ((fSlow1 * fRec48[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst212 * (((fConst215 * fRec49[1]) + (fConst247 * fRec49[0])) + (fConst247 * fRec49[2]))))));
			fVbargraph1 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec48[0]))));
			fRec61[0] = (fTemp43 - (fConst264 * ((fConst267 * fRec61[2]) + (fConst268 * fRec61[1]))));
			fRec60[0] = ((fConst264 * (((fConst266 * fRec61[1]) + (fConst269 * fRec61[0])) + (fConst269 * fRec61[2]))) - (fConst262 * ((fConst270 * fRec60[2]) + (fConst271 * fRec60[1]))));
			fRec59[0] = ((fConst262 * (((fConst263 * fRec60[1]) + (fConst272 * fRec60[0])) + (fConst272 * fRec60[2]))) - (fConst260 * ((fConst273 * fRec59[2]) + (fConst274 * fRec59[1]))));
			float fTemp44 = (fConst260 * (((fConst261 * fRec59[1]) + (fConst275 * fRec59[0])) + (fConst275 * fRec59[2])));
			fRec58[0] = (fTemp44 - (fConst257 * ((fConst276 * fRec58[2]) + (fConst278 * fRec58[1]))));
			fRec57[0] = ((fConst257 * (((fConst259 * fRec58[1]) + (fConst279 * fRec58[0])) + (fConst279 * fRec58[2]))) - (fConst254 * ((fConst280 * fRec57[2]) + (fConst281 * fRec57[1]))));
			fRec56[0] = ((fConst254 * (((fConst256 * fRec57[1]) + (fConst282 * fRec57[0])) + (fConst282 * fRec57[2]))) - (fConst250 * ((fConst283 * fRec56[2]) + (fConst284 * fRec56[1]))));
			fRec55[0] = ((fSlow1 * fRec55[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst250 * (((fConst253 * fRec56[1]) + (fConst285 * fRec56[0])) + (fConst285 * fRec56[2]))))));
			fVbargraph2 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec55[0]))));
			fRec68[0] = (fTemp44 - (fConst302 * ((fConst305 * fRec68[2]) + (fConst306 * fRec68[1]))));
			fRec67[0] = ((fConst302 * (((fConst304 * fRec68[1]) + (fConst307 * fRec68[0])) + (fConst307 * fRec68[2]))) - (fConst300 * ((fConst308 * fRec67[2]) + (fConst309 * fRec67[1]))));
			fRec66[0] = ((fConst300 * (((fConst301 * fRec67[1]) + (fConst310 * fRec67[0])) + (fConst310 * fRec67[2]))) - (fConst298 * ((fConst311 * fRec66[2]) + (fConst312 * fRec66[1]))));
			float fTemp45 = (fConst298 * (((fConst299 * fRec66[1]) + (fConst313 * fRec66[0])) + (fConst313 * fRec66[2])));
			fRec65[0] = (fTemp45 - (fConst295 * ((fConst314 * fRec65[2]) + (fConst316 * fRec65[1]))));
			fRec64[0] = ((fConst295 * (((fConst297 * fRec65[1]) + (fConst317 * fRec65[0])) + (fConst317 * fRec65[2]))) - (fConst292 * ((fConst318 * fRec64[2]) + (fConst319 * fRec64[1]))));
			fRec63[0] = ((fConst292 * (((fConst294 * fRec64[1]) + (fConst320 * fRec64[0])) + (fConst320 * fRec64[2]))) - (fConst288 * ((fConst321 * fRec63[2]) + (fConst322 * fRec63[1]))));
			fRec62[0] = ((fSlow1 * fRec62[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst288 * (((fConst291 * fRec63[1]) + (fConst323 * fRec63[0])) + (fConst323 * fRec63[2]))))));
			fVbargraph3 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec62[0]))));
			fRec75[0] = (fTemp45 - (fConst340 * ((fConst343 * fRec75[2]) + (fConst344 * fRec75[1]))));
			fRec74[0] = ((fConst340 * (((fConst342 * fRec75[1]) + (fConst345 * fRec75[0])) + (fConst345 * fRec75[2]))) - (fConst338 * ((fConst346 * fRec74[2]) + (fConst347 * fRec74[1]))));
			fRec73[0] = ((fConst338 * (((fConst339 * fRec74[1]) + (fConst348 * fRec74[0])) + (fConst348 * fRec74[2]))) - (fConst336 * ((fConst349 * fRec73[2]) + (fConst350 * fRec73[1]))));
			float fTemp46 = (fConst336 * (((fConst337 * fRec73[1]) + (fConst351 * fRec73[0])) + (fConst351 * fRec73[2])));
			fRec72[0] = (fTemp46 - (fConst333 * ((fConst352 * fRec72[2]) + (fConst354 * fRec72[1]))));
			fRec71[0] = ((fConst333 * (((fConst335 * fRec72[1]) + (fConst355 * fRec72[0])) + (fConst355 * fRec72[2]))) - (fConst330 * ((fConst356 * fRec71[2]) + (fConst357 * fRec71[1]))));
			fRec70[0] = ((fConst330 * (((fConst332 * fRec71[1]) + (fConst358 * fRec71[0])) + (fConst358 * fRec71[2]))) - (fConst326 * ((fConst359 * fRec70[2]) + (fConst360 * fRec70[1]))));
			fRec69[0] = ((fSlow1 * fRec69[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst326 * (((fConst329 * fRec70[1]) + (fConst361 * fRec70[0])) + (fConst361 * fRec70[2]))))));
			fVbargraph4 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec69[0]))));
			fRec79[0] = (fTemp46 - (fConst366 * ((fConst369 * fRec79[2]) + (fConst370 * fRec79[1]))));
			fRec78[0] = ((fConst366 * (((fConst368 * fRec79[1]) + (fConst371 * fRec79[0])) + (fConst371 * fRec79[2]))) - (fConst364 * ((fConst372 * fRec78[2]) + (fConst373 * fRec78[1]))));
			fRec77[0] = ((fConst364 * (((fConst365 * fRec78[1]) + (fConst374 * fRec78[0])) + (fConst374 * fRec78[2]))) - (fConst362 * ((fConst375 * fRec77[2]) + (fConst376 * fRec77[1]))));
			fRec76[0] = ((fSlow1 * fRec76[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst362 * (((fConst363 * fRec77[1]) + (fConst377 * fRec77[0])) + (fConst377 * fRec77[2]))))));
			fVbargraph5 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec76[0]))));
			fRec83[0] = (fTemp39 - (fConst384 * ((fConst387 * fRec83[2]) + (fConst388 * fRec83[1]))));
			fRec82[0] = ((fConst384 * (((fConst386 * fRec83[1]) + (fConst389 * fRec83[0])) + (fConst389 * fRec83[2]))) - (fConst381 * ((fConst390 * fRec82[2]) + (fConst391 * fRec82[1]))));
			fRec81[0] = ((fConst381 * (((fConst383 * fRec82[1]) + (fConst392 * fRec82[0])) + (fConst392 * fRec82[2]))) - (fConst378 * ((fConst393 * fRec81[2]) + (fConst394 * fRec81[1]))));
			fRec80[0] = ((fSlow2 * (float)java.lang.Math.abs((fConst378 * (((fConst380 * fRec81[1]) + (fConst395 * fRec81[0])) + (fConst395 * fRec81[2]))))) + (fSlow1 * fRec80[1]));
			fVbargraph6 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec80[0]))));
			fRec87[0] = (fTemp40 - (fConst402 * ((fConst405 * fRec87[2]) + (fConst406 * fRec87[1]))));
			fRec86[0] = ((fConst402 * (((fConst404 * fRec87[1]) + (fConst407 * fRec87[0])) + (fConst407 * fRec87[2]))) - (fConst399 * ((fConst408 * fRec86[2]) + (fConst409 * fRec86[1]))));
			fRec85[0] = ((fConst399 * (((fConst401 * fRec86[1]) + (fConst410 * fRec86[0])) + (fConst410 * fRec86[2]))) - (fConst396 * ((fConst411 * fRec85[2]) + (fConst412 * fRec85[1]))));
			fRec84[0] = ((fSlow1 * fRec84[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst396 * (((fConst398 * fRec85[1]) + (fConst413 * fRec85[0])) + (fConst413 * fRec85[2]))))));
			fVbargraph7 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec84[0]))));
			fRec91[0] = (fTemp41 - (fConst420 * ((fConst423 * fRec91[2]) + (fConst424 * fRec91[1]))));
			fRec90[0] = ((fConst420 * (((fConst422 * fRec91[1]) + (fConst425 * fRec91[0])) + (fConst425 * fRec91[2]))) - (fConst417 * ((fConst426 * fRec90[2]) + (fConst427 * fRec90[1]))));
			fRec89[0] = ((fConst417 * (((fConst419 * fRec90[1]) + (fConst428 * fRec90[0])) + (fConst428 * fRec90[2]))) - (fConst414 * ((fConst429 * fRec89[2]) + (fConst430 * fRec89[1]))));
			fRec88[0] = ((fSlow1 * fRec88[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst414 * (((fConst416 * fRec89[1]) + (fConst431 * fRec89[0])) + (fConst431 * fRec89[2]))))));
			fVbargraph8 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec88[0]))));
			fRec95[0] = (fTemp33 - (fConst438 * ((fConst441 * fRec95[2]) + (fConst442 * fRec95[1]))));
			fRec94[0] = ((fConst438 * (((fConst440 * fRec95[1]) + (fConst443 * fRec95[0])) + (fConst443 * fRec95[2]))) - (fConst435 * ((fConst444 * fRec94[2]) + (fConst445 * fRec94[1]))));
			fRec93[0] = ((fConst435 * (((fConst437 * fRec94[1]) + (fConst446 * fRec94[0])) + (fConst446 * fRec94[2]))) - (fConst432 * ((fConst447 * fRec93[2]) + (fConst448 * fRec93[1]))));
			fRec92[0] = ((fSlow1 * fRec92[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst432 * (((fConst434 * fRec93[1]) + (fConst449 * fRec93[0])) + (fConst449 * fRec93[2]))))));
			fVbargraph9 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec92[0]))));
			fRec99[0] = (fTemp34 - (fConst456 * ((fConst459 * fRec99[2]) + (fConst460 * fRec99[1]))));
			fRec98[0] = ((fConst456 * (((fConst458 * fRec99[1]) + (fConst461 * fRec99[0])) + (fConst461 * fRec99[2]))) - (fConst453 * ((fConst462 * fRec98[2]) + (fConst463 * fRec98[1]))));
			fRec97[0] = ((fConst453 * (((fConst455 * fRec98[1]) + (fConst464 * fRec98[0])) + (fConst464 * fRec98[2]))) - (fConst450 * ((fConst465 * fRec97[2]) + (fConst466 * fRec97[1]))));
			fRec96[0] = ((fSlow1 * fRec96[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst450 * (((fConst452 * fRec97[1]) + (fConst467 * fRec97[0])) + (fConst467 * fRec97[2]))))));
			fVbargraph10 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec96[0]))));
			fRec103[0] = (fTemp35 - (fConst474 * ((fConst477 * fRec103[2]) + (fConst478 * fRec103[1]))));
			fRec102[0] = ((fConst474 * (((fConst476 * fRec103[1]) + (fConst479 * fRec103[0])) + (fConst479 * fRec103[2]))) - (fConst471 * ((fConst480 * fRec102[2]) + (fConst481 * fRec102[1]))));
			fRec101[0] = ((fConst471 * (((fConst473 * fRec102[1]) + (fConst482 * fRec102[0])) + (fConst482 * fRec102[2]))) - (fConst468 * ((fConst483 * fRec101[2]) + (fConst484 * fRec101[1]))));
			fRec100[0] = ((fSlow1 * fRec100[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst468 * (((fConst470 * fRec101[1]) + (fConst485 * fRec101[0])) + (fConst485 * fRec101[2]))))));
			fVbargraph11 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec100[0]))));
			fRec107[0] = (fTemp36 - (fConst492 * ((fConst495 * fRec107[2]) + (fConst496 * fRec107[1]))));
			fRec106[0] = ((fConst492 * (((fConst494 * fRec107[1]) + (fConst497 * fRec107[0])) + (fConst497 * fRec107[2]))) - (fConst489 * ((fConst498 * fRec106[2]) + (fConst499 * fRec106[1]))));
			fRec105[0] = ((fConst489 * (((fConst491 * fRec106[1]) + (fConst500 * fRec106[0])) + (fConst500 * fRec106[2]))) - (fConst486 * ((fConst501 * fRec105[2]) + (fConst502 * fRec105[1]))));
			fRec104[0] = ((fSlow1 * fRec104[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst486 * (((fConst488 * fRec105[1]) + (fConst503 * fRec105[0])) + (fConst503 * fRec105[2]))))));
			fVbargraph12 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec104[0]))));
			fRec111[0] = (fTemp37 - (fConst510 * ((fConst513 * fRec111[2]) + (fConst514 * fRec111[1]))));
			fRec110[0] = ((fConst510 * (((fConst512 * fRec111[1]) + (fConst515 * fRec111[0])) + (fConst515 * fRec111[2]))) - (fConst507 * ((fConst516 * fRec110[2]) + (fConst517 * fRec110[1]))));
			fRec109[0] = ((fConst507 * (((fConst509 * fRec110[1]) + (fConst518 * fRec110[0])) + (fConst518 * fRec110[2]))) - (fConst504 * ((fConst519 * fRec109[2]) + (fConst520 * fRec109[1]))));
			fRec108[0] = ((fSlow1 * fRec108[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst504 * (((fConst506 * fRec109[1]) + (fConst521 * fRec109[0])) + (fConst521 * fRec109[2]))))));
			fVbargraph13 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec108[0]))));
			fRec115[0] = (fTemp38 - (fConst528 * ((fConst531 * fRec115[2]) + (fConst532 * fRec115[1]))));
			fRec114[0] = ((fConst528 * (((fConst530 * fRec115[1]) + (fConst533 * fRec115[0])) + (fConst533 * fRec115[2]))) - (fConst525 * ((fConst534 * fRec114[2]) + (fConst535 * fRec114[1]))));
			fRec113[0] = ((fConst525 * (((fConst527 * fRec114[1]) + (fConst536 * fRec114[0])) + (fConst536 * fRec114[2]))) - (fConst522 * ((fConst537 * fRec113[2]) + (fConst538 * fRec113[1]))));
			fRec112[0] = ((fSlow1 * fRec112[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst522 * (((fConst524 * fRec113[1]) + (fConst539 * fRec113[0])) + (fConst539 * fRec113[2]))))));
			fVbargraph14 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec112[0]))));
			output0[i] = fTemp33;
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
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
			iRec46[1] = iRec46[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec47[j1] = fRec47[(j1 - 1)];
				
			}
			fVec22[1] = fVec22[0];
			fRec40[1] = fRec40[0];
			fVec23[1] = fVec23[0];
			fRec39[1] = fRec39[0];
			fVec24[1] = fVec24[0];
			fRec38[1] = fRec38[0];
			fVec25[1] = fVec25[0];
			fRec37[1] = fRec37[0];
			fVec26[1] = fVec26[0];
			fRec36[1] = fRec36[0];
			fVec27[1] = fVec27[0];
			fRec35[1] = fRec35[0];
			fVec28[1] = fVec28[0];
			fRec34[1] = fRec34[0];
			fVec29[1] = fVec29[0];
			fRec33[1] = fRec33[0];
			fVec30[1] = fVec30[0];
			fRec32[1] = fRec32[0];
			fVec31[1] = fVec31[0];
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
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[1] = fRec76[0];
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
			
		}
		
	}
	
};

