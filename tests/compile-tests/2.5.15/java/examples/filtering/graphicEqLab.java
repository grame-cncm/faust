/* ------------------------------------------------------------
name: "graphicEqLab"
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
	float fVslider0;
	float fRec21[] = new float[2];
	float fCheckbox1;
	float fCheckbox2;
	float fEntry0;
	float fConst44;
	float fVslider1;
	float fVslider2;
	float fRec23[] = new float[2];
	float fVec1[] = new float[2];
	float fRec22[] = new float[2];
	float fConst45;
	float fVec2[] = new float[2];
	float fConst46;
	float fVec3[] = new float[2];
	float fVec4[] = new float[2];
	float fConst47;
	float fVec5[] = new float[2];
	float fVec6[] = new float[2];
	float fVec7[] = new float[2];
	float fVslider3;
	float fVec8[] = new float[2];
	float fRec24[] = new float[2];
	float fVec9[] = new float[2];
	float fVec10[] = new float[2];
	float fVec11[] = new float[2];
	float fVec12[] = new float[2];
	float fVec13[] = new float[2];
	float fVec14[] = new float[2];
	float fVslider4;
	float fVec15[] = new float[2];
	float fRec25[] = new float[2];
	float fVec16[] = new float[2];
	float fVec17[] = new float[2];
	float fVec18[] = new float[2];
	float fVec19[] = new float[2];
	float fVec20[] = new float[2];
	float fVec21[] = new float[2];
	float fCheckbox3;
	int iRec26[] = new int[2];
	float fRec27[] = new float[4];
	float fVec22[] = new float[2];
	float fRec20[] = new float[2];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec19[] = new float[3];
	float fConst51;
	float fConst52;
	float fRec18[] = new float[3];
	float fVec23[] = new float[2];
	float fRec17[] = new float[2];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec16[] = new float[3];
	float fConst56;
	float fConst57;
	float fRec15[] = new float[3];
	float fVec24[] = new float[2];
	float fRec14[] = new float[2];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec13[] = new float[3];
	float fConst61;
	float fConst62;
	float fRec12[] = new float[3];
	float fVec25[] = new float[2];
	float fConst63;
	float fConst64;
	float fRec11[] = new float[2];
	float fConst65;
	float fConst66;
	float fRec10[] = new float[3];
	float fConst67;
	float fRec9[] = new float[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec8[] = new float[3];
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec7[] = new float[3];
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec6[] = new float[3];
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec5[] = new float[3];
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec4[] = new float[3];
	float fVslider5;
	float fRec28[] = new float[2];
	float fConst98;
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fRec38[] = new float[2];
	float fRec37[] = new float[3];
	float fRec36[] = new float[3];
	float fVec26[] = new float[2];
	float fConst105;
	float fRec35[] = new float[2];
	float fConst106;
	float fRec34[] = new float[3];
	float fConst107;
	float fRec33[] = new float[3];
	float fRec32[] = new float[3];
	float fRec31[] = new float[3];
	float fRec30[] = new float[3];
	float fRec29[] = new float[3];
	float fVslider6;
	float fRec39[] = new float[2];
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec48[] = new float[2];
	float fRec47[] = new float[3];
	float fRec46[] = new float[3];
	float fVec27[] = new float[2];
	float fConst115;
	float fRec45[] = new float[2];
	float fConst116;
	float fRec44[] = new float[3];
	float fConst117;
	float fRec43[] = new float[3];
	float fRec42[] = new float[3];
	float fRec41[] = new float[3];
	float fRec40[] = new float[3];
	float fVslider7;
	float fRec49[] = new float[2];
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec57[] = new float[2];
	float fRec56[] = new float[3];
	float fRec55[] = new float[3];
	float fVec28[] = new float[2];
	float fConst125;
	float fRec54[] = new float[2];
	float fConst126;
	float fRec53[] = new float[3];
	float fConst127;
	float fRec52[] = new float[3];
	float fRec51[] = new float[3];
	float fRec50[] = new float[3];
	float fVslider8;
	float fRec58[] = new float[2];
	float fConst128;
	float fConst129;
	float fConst130;
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec65[] = new float[2];
	float fRec64[] = new float[3];
	float fRec63[] = new float[3];
	float fVec29[] = new float[2];
	float fConst135;
	float fRec62[] = new float[2];
	float fConst136;
	float fRec61[] = new float[3];
	float fConst137;
	float fRec60[] = new float[3];
	float fRec59[] = new float[3];
	float fVslider9;
	float fRec66[] = new float[2];
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec72[] = new float[2];
	float fRec71[] = new float[3];
	float fRec70[] = new float[3];
	float fVec30[] = new float[2];
	float fConst144;
	float fRec69[] = new float[2];
	float fConst145;
	float fRec68[] = new float[3];
	float fConst146;
	float fRec67[] = new float[3];
	float fVslider10;
	float fRec73[] = new float[2];
	float fRec76[] = new float[2];
	float fRec75[] = new float[3];
	float fRec74[] = new float[3];
	float fVslider11;
	float fRec77[] = new float[2];
	float fConst147;
	float fConst148;
	float fRec88[] = new float[2];
	float fRec87[] = new float[3];
	float fRec86[] = new float[3];
	float fRec85[] = new float[3];
	float fRec84[] = new float[3];
	float fRec83[] = new float[3];
	float fRec82[] = new float[3];
	float fRec81[] = new float[3];
	float fConst149;
	float fConst150;
	float fRec80[] = new float[3];
	float fConst151;
	float fConst152;
	float fRec79[] = new float[3];
	float fConst153;
	float fConst154;
	float fRec78[] = new float[3];
	float fVslider12;
	float fRec89[] = new float[2];
	float fConst155;
	float fConst156;
	float fRec99[] = new float[2];
	float fRec98[] = new float[3];
	float fRec97[] = new float[3];
	float fRec96[] = new float[3];
	float fRec95[] = new float[3];
	float fRec94[] = new float[3];
	float fRec93[] = new float[3];
	float fRec92[] = new float[3];
	float fRec91[] = new float[3];
	float fRec90[] = new float[3];
	float fVslider13;
	float fRec100[] = new float[2];
	float fConst157;
	float fConst158;
	float fRec109[] = new float[2];
	float fRec108[] = new float[3];
	float fRec107[] = new float[3];
	float fRec106[] = new float[3];
	float fRec105[] = new float[3];
	float fRec104[] = new float[3];
	float fRec103[] = new float[3];
	float fRec102[] = new float[3];
	float fRec101[] = new float[3];
	float fVslider14;
	float fRec110[] = new float[2];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec3[] = new float[3];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec2[] = new float[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec1[] = new float[3];
	float fConst168;
	float fRec0[] = new float[2];
	float fVbargraph0;
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
	float fConst186;
	float fConst187;
	float fConst188;
	float fConst189;
	float fRec117[] = new float[3];
	float fConst190;
	float fConst191;
	float fConst192;
	float fRec116[] = new float[3];
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec115[] = new float[3];
	float fConst196;
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec114[] = new float[3];
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec113[] = new float[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec112[] = new float[3];
	float fConst206;
	float fRec111[] = new float[2];
	float fVbargraph1;
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
	float fConst224;
	float fConst225;
	float fConst226;
	float fConst227;
	float fRec124[] = new float[3];
	float fConst228;
	float fConst229;
	float fConst230;
	float fRec123[] = new float[3];
	float fConst231;
	float fConst232;
	float fConst233;
	float fRec122[] = new float[3];
	float fConst234;
	float fConst235;
	float fConst236;
	float fConst237;
	float fRec121[] = new float[3];
	float fConst238;
	float fConst239;
	float fConst240;
	float fRec120[] = new float[3];
	float fConst241;
	float fConst242;
	float fConst243;
	float fRec119[] = new float[3];
	float fConst244;
	float fRec118[] = new float[2];
	float fVbargraph2;
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
	float fConst262;
	float fConst263;
	float fConst264;
	float fConst265;
	float fRec131[] = new float[3];
	float fConst266;
	float fConst267;
	float fConst268;
	float fRec130[] = new float[3];
	float fConst269;
	float fConst270;
	float fConst271;
	float fRec129[] = new float[3];
	float fConst272;
	float fConst273;
	float fConst274;
	float fConst275;
	float fRec128[] = new float[3];
	float fConst276;
	float fConst277;
	float fConst278;
	float fRec127[] = new float[3];
	float fConst279;
	float fConst280;
	float fConst281;
	float fRec126[] = new float[3];
	float fConst282;
	float fRec125[] = new float[2];
	float fVbargraph3;
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
	float fConst300;
	float fConst301;
	float fConst302;
	float fConst303;
	float fRec138[] = new float[3];
	float fConst304;
	float fConst305;
	float fConst306;
	float fRec137[] = new float[3];
	float fConst307;
	float fConst308;
	float fConst309;
	float fRec136[] = new float[3];
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fRec135[] = new float[3];
	float fConst314;
	float fConst315;
	float fConst316;
	float fRec134[] = new float[3];
	float fConst317;
	float fConst318;
	float fConst319;
	float fRec133[] = new float[3];
	float fConst320;
	float fRec132[] = new float[2];
	float fVbargraph4;
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
	float fConst338;
	float fConst339;
	float fConst340;
	float fConst341;
	float fRec145[] = new float[3];
	float fConst342;
	float fConst343;
	float fConst344;
	float fRec144[] = new float[3];
	float fConst345;
	float fConst346;
	float fConst347;
	float fRec143[] = new float[3];
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fRec142[] = new float[3];
	float fConst352;
	float fConst353;
	float fConst354;
	float fRec141[] = new float[3];
	float fConst355;
	float fConst356;
	float fConst357;
	float fRec140[] = new float[3];
	float fConst358;
	float fRec139[] = new float[2];
	float fVbargraph5;
	float fConst359;
	float fConst360;
	float fConst361;
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
	float fConst373;
	float fConst374;
	float fConst375;
	float fConst376;
	float fConst377;
	float fConst378;
	float fConst379;
	float fRec152[] = new float[3];
	float fConst380;
	float fConst381;
	float fConst382;
	float fRec151[] = new float[3];
	float fConst383;
	float fConst384;
	float fConst385;
	float fRec150[] = new float[3];
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fRec149[] = new float[3];
	float fConst390;
	float fConst391;
	float fConst392;
	float fRec148[] = new float[3];
	float fConst393;
	float fConst394;
	float fConst395;
	float fRec147[] = new float[3];
	float fConst396;
	float fRec146[] = new float[2];
	float fVbargraph6;
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
	float fRec159[] = new float[3];
	float fConst418;
	float fConst419;
	float fConst420;
	float fRec158[] = new float[3];
	float fConst421;
	float fConst422;
	float fConst423;
	float fRec157[] = new float[3];
	float fConst424;
	float fConst425;
	float fConst426;
	float fConst427;
	float fRec156[] = new float[3];
	float fConst428;
	float fConst429;
	float fConst430;
	float fRec155[] = new float[3];
	float fConst431;
	float fConst432;
	float fConst433;
	float fRec154[] = new float[3];
	float fConst434;
	float fRec153[] = new float[2];
	float fVbargraph7;
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
	float fRec166[] = new float[3];
	float fConst456;
	float fConst457;
	float fConst458;
	float fRec165[] = new float[3];
	float fConst459;
	float fConst460;
	float fConst461;
	float fRec164[] = new float[3];
	float fConst462;
	float fConst463;
	float fConst464;
	float fConst465;
	float fRec163[] = new float[3];
	float fConst466;
	float fConst467;
	float fConst468;
	float fRec162[] = new float[3];
	float fConst469;
	float fConst470;
	float fConst471;
	float fRec161[] = new float[3];
	float fConst472;
	float fRec160[] = new float[2];
	float fVbargraph8;
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
	float fRec173[] = new float[3];
	float fConst494;
	float fConst495;
	float fConst496;
	float fRec172[] = new float[3];
	float fConst497;
	float fConst498;
	float fConst499;
	float fRec171[] = new float[3];
	float fConst500;
	float fConst501;
	float fConst502;
	float fConst503;
	float fRec170[] = new float[3];
	float fConst504;
	float fConst505;
	float fConst506;
	float fRec169[] = new float[3];
	float fConst507;
	float fConst508;
	float fConst509;
	float fRec168[] = new float[3];
	float fConst510;
	float fRec167[] = new float[2];
	float fVbargraph9;
	float fConst511;
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fConst519;
	float fConst520;
	float fConst521;
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
	float fRec180[] = new float[3];
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec179[] = new float[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec178[] = new float[3];
	float fConst538;
	float fConst539;
	float fConst540;
	float fConst541;
	float fRec177[] = new float[3];
	float fConst542;
	float fConst543;
	float fConst544;
	float fRec176[] = new float[3];
	float fConst545;
	float fConst546;
	float fConst547;
	float fRec175[] = new float[3];
	float fConst548;
	float fRec174[] = new float[2];
	float fVbargraph10;
	float fConst549;
	float fConst550;
	float fConst551;
	float fConst552;
	float fConst553;
	float fConst554;
	float fConst555;
	float fConst556;
	float fConst557;
	float fConst558;
	float fConst559;
	float fConst560;
	float fConst561;
	float fConst562;
	float fConst563;
	float fConst564;
	float fConst565;
	float fConst566;
	float fConst567;
	float fConst568;
	float fConst569;
	float fRec187[] = new float[3];
	float fConst570;
	float fConst571;
	float fConst572;
	float fRec186[] = new float[3];
	float fConst573;
	float fConst574;
	float fConst575;
	float fRec185[] = new float[3];
	float fConst576;
	float fConst577;
	float fConst578;
	float fConst579;
	float fRec184[] = new float[3];
	float fConst580;
	float fConst581;
	float fConst582;
	float fRec183[] = new float[3];
	float fConst583;
	float fConst584;
	float fConst585;
	float fRec182[] = new float[3];
	float fConst586;
	float fRec181[] = new float[2];
	float fVbargraph11;
	float fConst587;
	float fConst588;
	float fConst589;
	float fConst590;
	float fConst591;
	float fConst592;
	float fConst593;
	float fConst594;
	float fConst595;
	float fConst596;
	float fConst597;
	float fConst598;
	float fConst599;
	float fConst600;
	float fConst601;
	float fConst602;
	float fConst603;
	float fConst604;
	float fConst605;
	float fConst606;
	float fConst607;
	float fRec194[] = new float[3];
	float fConst608;
	float fConst609;
	float fConst610;
	float fRec193[] = new float[3];
	float fConst611;
	float fConst612;
	float fConst613;
	float fRec192[] = new float[3];
	float fConst614;
	float fConst615;
	float fConst616;
	float fConst617;
	float fRec191[] = new float[3];
	float fConst618;
	float fConst619;
	float fConst620;
	float fRec190[] = new float[3];
	float fConst621;
	float fConst622;
	float fConst623;
	float fRec189[] = new float[3];
	float fConst624;
	float fRec188[] = new float[2];
	float fVbargraph12;
	float fConst625;
	float fConst626;
	float fConst627;
	float fConst628;
	float fConst629;
	float fConst630;
	float fConst631;
	float fConst632;
	float fConst633;
	float fConst634;
	float fConst635;
	float fConst636;
	float fConst637;
	float fConst638;
	float fConst639;
	float fConst640;
	float fConst641;
	float fConst642;
	float fConst643;
	float fConst644;
	float fConst645;
	float fRec201[] = new float[3];
	float fConst646;
	float fConst647;
	float fConst648;
	float fRec200[] = new float[3];
	float fConst649;
	float fConst650;
	float fConst651;
	float fRec199[] = new float[3];
	float fConst652;
	float fConst653;
	float fConst654;
	float fConst655;
	float fRec198[] = new float[3];
	float fConst656;
	float fConst657;
	float fConst658;
	float fRec197[] = new float[3];
	float fConst659;
	float fConst660;
	float fConst661;
	float fRec196[] = new float[3];
	float fConst662;
	float fRec195[] = new float[2];
	float fVbargraph13;
	float fConst663;
	float fConst664;
	float fConst665;
	float fConst666;
	float fConst667;
	float fConst668;
	float fConst669;
	float fConst670;
	float fConst671;
	float fRec205[] = new float[3];
	float fConst672;
	float fConst673;
	float fConst674;
	float fRec204[] = new float[3];
	float fConst675;
	float fConst676;
	float fConst677;
	float fRec203[] = new float[3];
	float fConst678;
	float fRec202[] = new float[2];
	float fVbargraph14;
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Signal generators through a filter bank with spectrum analysis display");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "graphicEqLab");
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
		fConst14 = (float)java.lang.Math.tan((3926.99072f / fConst0));
		fConst15 = (1.0f / fConst14);
		fConst16 = (((fConst15 + 0.618034005f) / fConst14) + 1.0f);
		fConst17 = (1.0f / fConst16);
		fConst18 = (1.0f / mydsp_faustpower2_f(fConst14));
		fConst19 = (2.0f * (0.0f - fConst18));
		fConst20 = (1.0f / (((fConst15 + 1.61803401f) / fConst14) + 1.0f));
		fConst21 = (float)java.lang.Math.tan((7853.98145f / fConst0));
		fConst22 = (1.0f / fConst21);
		fConst23 = (((fConst22 + 0.618034005f) / fConst21) + 1.0f);
		fConst24 = (fConst15 + 1.0f);
		fConst25 = (1.0f / (fConst23 * fConst24));
		fConst26 = (1.0f / (((fConst22 + 1.61803401f) / fConst21) + 1.0f));
		fConst27 = (fConst22 + 1.0f);
		fConst28 = (0.0f - ((1.0f - fConst22) / fConst27));
		fConst29 = (float)java.lang.Math.tan((15707.9629f / fConst0));
		fConst30 = (1.0f / fConst29);
		fConst31 = (((fConst30 + 0.618034005f) / fConst29) + 1.0f);
		fConst32 = (1.0f / (fConst31 * fConst27));
		fConst33 = (1.0f / (((fConst30 + 1.61803401f) / fConst29) + 1.0f));
		fConst34 = (fConst30 + 1.0f);
		fConst35 = (0.0f - ((1.0f - fConst30) / fConst34));
		fConst36 = (float)java.lang.Math.tan((31415.9258f / fConst0));
		fConst37 = (1.0f / fConst36);
		fConst38 = (((fConst37 + 0.618034005f) / fConst36) + 1.0f);
		fConst39 = (1.0f / (fConst38 * fConst34));
		fConst40 = (1.0f / (((fConst37 + 1.61803401f) / fConst36) + 1.0f));
		fConst41 = (fConst37 + 1.0f);
		fConst42 = (0.0f - ((1.0f - fConst37) / fConst41));
		fConst43 = (1.0f / fConst41);
		fConst44 = (1.0f / fConst0);
		fConst45 = (0.25f * fConst0);
		fConst46 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst47 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst48 = (1.0f / mydsp_faustpower2_f(fConst36));
		fConst49 = (2.0f * (1.0f - fConst48));
		fConst50 = (((fConst37 + -1.61803401f) / fConst36) + 1.0f);
		fConst51 = (1.0f / fConst38);
		fConst52 = (((fConst37 + -0.618034005f) / fConst36) + 1.0f);
		fConst53 = (1.0f / mydsp_faustpower2_f(fConst29));
		fConst54 = (2.0f * (1.0f - fConst53));
		fConst55 = (((fConst30 + -1.61803401f) / fConst29) + 1.0f);
		fConst56 = (1.0f / fConst31);
		fConst57 = (((fConst30 + -0.618034005f) / fConst29) + 1.0f);
		fConst58 = (1.0f / mydsp_faustpower2_f(fConst21));
		fConst59 = (2.0f * (1.0f - fConst58));
		fConst60 = (((fConst22 + -1.61803401f) / fConst21) + 1.0f);
		fConst61 = (1.0f / fConst23);
		fConst62 = (((fConst22 + -0.618034005f) / fConst21) + 1.0f);
		fConst63 = (0.0f - fConst15);
		fConst64 = (0.0f - ((1.0f - fConst15) / fConst24));
		fConst65 = (2.0f * (1.0f - fConst18));
		fConst66 = (((fConst15 + -1.61803401f) / fConst14) + 1.0f);
		fConst67 = (((fConst15 + -0.618034005f) / fConst14) + 1.0f);
		fConst68 = (float)java.lang.Math.tan((122.71846f / fConst0));
		fConst69 = (1.0f / fConst68);
		fConst70 = (1.0f / (((fConst69 + 1.61803401f) / fConst68) + 1.0f));
		fConst71 = (1.0f / mydsp_faustpower2_f(fConst68));
		fConst72 = (2.0f * (1.0f - fConst71));
		fConst73 = (((fConst69 + -1.61803401f) / fConst68) + 1.0f);
		fConst74 = (float)java.lang.Math.tan((245.43692f / fConst0));
		fConst75 = (1.0f / fConst74);
		fConst76 = (1.0f / (((fConst75 + 1.61803401f) / fConst74) + 1.0f));
		fConst77 = (1.0f / mydsp_faustpower2_f(fConst74));
		fConst78 = (2.0f * (1.0f - fConst77));
		fConst79 = (((fConst75 + -1.61803401f) / fConst74) + 1.0f);
		fConst80 = (float)java.lang.Math.tan((490.87384f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (1.0f / (((fConst81 + 1.61803401f) / fConst80) + 1.0f));
		fConst83 = (1.0f / mydsp_faustpower2_f(fConst80));
		fConst84 = (2.0f * (1.0f - fConst83));
		fConst85 = (((fConst81 + -1.61803401f) / fConst80) + 1.0f);
		fConst86 = (float)java.lang.Math.tan((981.747681f / fConst0));
		fConst87 = (1.0f / fConst86);
		fConst88 = (1.0f / (((fConst87 + 1.61803401f) / fConst86) + 1.0f));
		fConst89 = (1.0f / mydsp_faustpower2_f(fConst86));
		fConst90 = (2.0f * (1.0f - fConst89));
		fConst91 = (((fConst87 + -1.61803401f) / fConst86) + 1.0f);
		fConst92 = (float)java.lang.Math.tan((1963.49536f / fConst0));
		fConst93 = (1.0f / fConst92);
		fConst94 = (1.0f / (((fConst93 + 1.61803401f) / fConst92) + 1.0f));
		fConst95 = (1.0f / mydsp_faustpower2_f(fConst92));
		fConst96 = (2.0f * (1.0f - fConst95));
		fConst97 = (((fConst93 + -1.61803401f) / fConst92) + 1.0f);
		fConst98 = (((fConst93 + 0.618034005f) / fConst92) + 1.0f);
		fConst99 = (1.0f / fConst98);
		fConst100 = (2.0f * (0.0f - fConst95));
		fConst101 = (1.0f / (((fConst93 + 1.61803401f) / fConst92) + 1.0f));
		fConst102 = (fConst93 + 1.0f);
		fConst103 = (0.0f - ((1.0f - fConst93) / fConst102));
		fConst104 = (1.0f / (fConst16 * fConst102));
		fConst105 = (0.0f - fConst93);
		fConst106 = (((fConst93 + -1.61803401f) / fConst92) + 1.0f);
		fConst107 = (((fConst93 + -0.618034005f) / fConst92) + 1.0f);
		fConst108 = (((fConst87 + 0.618034005f) / fConst86) + 1.0f);
		fConst109 = (1.0f / fConst108);
		fConst110 = (2.0f * (0.0f - fConst89));
		fConst111 = (1.0f / (((fConst87 + 1.61803401f) / fConst86) + 1.0f));
		fConst112 = (fConst87 + 1.0f);
		fConst113 = (0.0f - ((1.0f - fConst87) / fConst112));
		fConst114 = (1.0f / (fConst112 * fConst98));
		fConst115 = (0.0f - fConst87);
		fConst116 = (((fConst87 + -1.61803401f) / fConst86) + 1.0f);
		fConst117 = (((fConst87 + -0.618034005f) / fConst86) + 1.0f);
		fConst118 = (((fConst81 + 0.618034005f) / fConst80) + 1.0f);
		fConst119 = (1.0f / fConst118);
		fConst120 = (2.0f * (0.0f - fConst83));
		fConst121 = (1.0f / (((fConst81 + 1.61803401f) / fConst80) + 1.0f));
		fConst122 = (fConst81 + 1.0f);
		fConst123 = (0.0f - ((1.0f - fConst81) / fConst122));
		fConst124 = (1.0f / (fConst122 * fConst108));
		fConst125 = (0.0f - fConst81);
		fConst126 = (((fConst81 + -1.61803401f) / fConst80) + 1.0f);
		fConst127 = (((fConst81 + -0.618034005f) / fConst80) + 1.0f);
		fConst128 = (((fConst75 + 0.618034005f) / fConst74) + 1.0f);
		fConst129 = (1.0f / fConst128);
		fConst130 = (2.0f * (0.0f - fConst77));
		fConst131 = (1.0f / (((fConst75 + 1.61803401f) / fConst74) + 1.0f));
		fConst132 = (fConst75 + 1.0f);
		fConst133 = (0.0f - ((1.0f - fConst75) / fConst132));
		fConst134 = (1.0f / (fConst118 * fConst132));
		fConst135 = (0.0f - fConst75);
		fConst136 = (((fConst75 + -1.61803401f) / fConst74) + 1.0f);
		fConst137 = (((fConst75 + -0.618034005f) / fConst74) + 1.0f);
		fConst138 = (1.0f / (((fConst69 + 0.618034005f) / fConst68) + 1.0f));
		fConst139 = (2.0f * (0.0f - fConst71));
		fConst140 = (1.0f / (((fConst69 + 1.61803401f) / fConst68) + 1.0f));
		fConst141 = (fConst69 + 1.0f);
		fConst142 = (0.0f - ((1.0f - fConst69) / fConst141));
		fConst143 = (1.0f / (fConst128 * fConst141));
		fConst144 = (0.0f - fConst69);
		fConst145 = (((fConst69 + -1.61803401f) / fConst68) + 1.0f);
		fConst146 = (((fConst69 + -0.618034005f) / fConst68) + 1.0f);
		fConst147 = (2.0f * (0.0f - fConst48));
		fConst148 = (0.0f - fConst37);
		fConst149 = (1.0f / (((fConst15 + 1.61803401f) / fConst14) + 1.0f));
		fConst150 = (((fConst15 + -1.61803401f) / fConst14) + 1.0f);
		fConst151 = (1.0f / (((fConst22 + 1.61803401f) / fConst21) + 1.0f));
		fConst152 = (((fConst22 + -1.61803401f) / fConst21) + 1.0f);
		fConst153 = (1.0f / (((fConst30 + 1.61803401f) / fConst29) + 1.0f));
		fConst154 = (((fConst30 + -1.61803401f) / fConst29) + 1.0f);
		fConst155 = (2.0f * (0.0f - fConst53));
		fConst156 = (0.0f - fConst30);
		fConst157 = (2.0f * (0.0f - fConst58));
		fConst158 = (0.0f - fConst22);
		fConst159 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst160 = (1.0f / fConst5);
		fConst161 = (2.0f * (4.07678175f - fConst160));
		fConst162 = (fConst12 + 0.000407678192f);
		fConst163 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst164 = (2.0f * (1.4500711f - fConst160));
		fConst165 = (fConst9 + 1.4500711f);
		fConst166 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst167 = (2.0f * (0.935140193f - fConst160));
		fConst168 = (fConst6 + 0.935140193f);
		fConst169 = (float)java.lang.Math.tan((31665.2695f / fConst0));
		fConst170 = (1.0f / fConst169);
		fConst171 = (1.0f / (((fConst170 + 0.157482162f) / fConst169) + 0.935140193f));
		fConst172 = mydsp_faustpower2_f(fConst169);
		fConst173 = (50.0638084f / fConst172);
		fConst174 = (2.0f * (0.935140193f - fConst173));
		fConst175 = (1.0f / (((fConst170 + 0.743130445f) / fConst169) + 1.4500711f));
		fConst176 = (11.0520525f / fConst172);
		fConst177 = (2.0f * (1.4500711f - fConst176));
		fConst178 = (1.0f / (((fConst170 + 3.18972731f) / fConst169) + 4.07678175f));
		fConst179 = (0.00176617282f / fConst172);
		fConst180 = (2.0f * (0.000407678192f - fConst179));
		fConst181 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst182 = (2.0f * (53.5361519f - fConst160));
		fConst183 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst184 = (2.0f * (7.62173128f - fConst160));
		fConst185 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst186 = (9.99999975e-05f / fConst5);
		fConst187 = (2.0f * (0.000433227193f - fConst186));
		fConst188 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst189 = (2.0f * (0.245291501f - fConst160));
		fConst190 = (fConst186 + 0.000433227193f);
		fConst191 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst192 = (2.0f * (0.689621389f - fConst160));
		fConst193 = (fConst160 + 7.62173128f);
		fConst194 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst195 = (2.0f * (1.06935835f - fConst160));
		fConst196 = (fConst160 + 53.5361519f);
		fConst197 = (((fConst170 + -3.18972731f) / fConst169) + 4.07678175f);
		fConst198 = (1.0f / fConst172);
		fConst199 = (2.0f * (4.07678175f - fConst198));
		fConst200 = (fConst179 + 0.000407678192f);
		fConst201 = (((fConst170 + -0.743130445f) / fConst169) + 1.4500711f);
		fConst202 = (2.0f * (1.4500711f - fConst198));
		fConst203 = (fConst176 + 1.4500711f);
		fConst204 = (((fConst170 + -0.157482162f) / fConst169) + 0.935140193f);
		fConst205 = (2.0f * (0.935140193f - fConst198));
		fConst206 = (fConst173 + 0.935140193f);
		fConst207 = (float)java.lang.Math.tan((19947.8691f / fConst0));
		fConst208 = (1.0f / fConst207);
		fConst209 = (1.0f / (((fConst208 + 0.157482162f) / fConst207) + 0.935140193f));
		fConst210 = mydsp_faustpower2_f(fConst207);
		fConst211 = (50.0638084f / fConst210);
		fConst212 = (2.0f * (0.935140193f - fConst211));
		fConst213 = (1.0f / (((fConst208 + 0.743130445f) / fConst207) + 1.4500711f));
		fConst214 = (11.0520525f / fConst210);
		fConst215 = (2.0f * (1.4500711f - fConst214));
		fConst216 = (1.0f / (((fConst208 + 3.18972731f) / fConst207) + 4.07678175f));
		fConst217 = (0.00176617282f / fConst210);
		fConst218 = (2.0f * (0.000407678192f - fConst217));
		fConst219 = (1.0f / (((fConst170 + 0.168404877f) / fConst169) + 1.06935835f));
		fConst220 = (2.0f * (53.5361519f - fConst198));
		fConst221 = (1.0f / (((fConst170 + 0.51247865f) / fConst169) + 0.689621389f));
		fConst222 = (2.0f * (7.62173128f - fConst198));
		fConst223 = (1.0f / (((fConst170 + 0.782413065f) / fConst169) + 0.245291501f));
		fConst224 = (9.99999975e-05f / fConst172);
		fConst225 = (2.0f * (0.000433227193f - fConst224));
		fConst226 = (((fConst170 + -0.782413065f) / fConst169) + 0.245291501f);
		fConst227 = (2.0f * (0.245291501f - fConst198));
		fConst228 = (fConst224 + 0.000433227193f);
		fConst229 = (((fConst170 + -0.51247865f) / fConst169) + 0.689621389f);
		fConst230 = (2.0f * (0.689621389f - fConst198));
		fConst231 = (fConst198 + 7.62173128f);
		fConst232 = (((fConst170 + -0.168404877f) / fConst169) + 1.06935835f);
		fConst233 = (2.0f * (1.06935835f - fConst198));
		fConst234 = (fConst198 + 53.5361519f);
		fConst235 = (((fConst208 + -3.18972731f) / fConst207) + 4.07678175f);
		fConst236 = (1.0f / fConst210);
		fConst237 = (2.0f * (4.07678175f - fConst236));
		fConst238 = (fConst217 + 0.000407678192f);
		fConst239 = (((fConst208 + -0.743130445f) / fConst207) + 1.4500711f);
		fConst240 = (2.0f * (1.4500711f - fConst236));
		fConst241 = (fConst214 + 1.4500711f);
		fConst242 = (((fConst208 + -0.157482162f) / fConst207) + 0.935140193f);
		fConst243 = (2.0f * (0.935140193f - fConst236));
		fConst244 = (fConst211 + 0.935140193f);
		fConst245 = (float)java.lang.Math.tan((12566.3711f / fConst0));
		fConst246 = (1.0f / fConst245);
		fConst247 = (1.0f / (((fConst246 + 0.157482162f) / fConst245) + 0.935140193f));
		fConst248 = mydsp_faustpower2_f(fConst245);
		fConst249 = (50.0638084f / fConst248);
		fConst250 = (2.0f * (0.935140193f - fConst249));
		fConst251 = (1.0f / (((fConst246 + 0.743130445f) / fConst245) + 1.4500711f));
		fConst252 = (11.0520525f / fConst248);
		fConst253 = (2.0f * (1.4500711f - fConst252));
		fConst254 = (1.0f / (((fConst246 + 3.18972731f) / fConst245) + 4.07678175f));
		fConst255 = (0.00176617282f / fConst248);
		fConst256 = (2.0f * (0.000407678192f - fConst255));
		fConst257 = (1.0f / (((fConst208 + 0.168404877f) / fConst207) + 1.06935835f));
		fConst258 = (2.0f * (53.5361519f - fConst236));
		fConst259 = (1.0f / (((fConst208 + 0.51247865f) / fConst207) + 0.689621389f));
		fConst260 = (2.0f * (7.62173128f - fConst236));
		fConst261 = (1.0f / (((fConst208 + 0.782413065f) / fConst207) + 0.245291501f));
		fConst262 = (9.99999975e-05f / fConst210);
		fConst263 = (2.0f * (0.000433227193f - fConst262));
		fConst264 = (((fConst208 + -0.782413065f) / fConst207) + 0.245291501f);
		fConst265 = (2.0f * (0.245291501f - fConst236));
		fConst266 = (fConst262 + 0.000433227193f);
		fConst267 = (((fConst208 + -0.51247865f) / fConst207) + 0.689621389f);
		fConst268 = (2.0f * (0.689621389f - fConst236));
		fConst269 = (fConst236 + 7.62173128f);
		fConst270 = (((fConst208 + -0.168404877f) / fConst207) + 1.06935835f);
		fConst271 = (2.0f * (1.06935835f - fConst236));
		fConst272 = (fConst236 + 53.5361519f);
		fConst273 = (((fConst246 + -3.18972731f) / fConst245) + 4.07678175f);
		fConst274 = (1.0f / fConst248);
		fConst275 = (2.0f * (4.07678175f - fConst274));
		fConst276 = (fConst255 + 0.000407678192f);
		fConst277 = (((fConst246 + -0.743130445f) / fConst245) + 1.4500711f);
		fConst278 = (2.0f * (1.4500711f - fConst274));
		fConst279 = (fConst252 + 1.4500711f);
		fConst280 = (((fConst246 + -0.157482162f) / fConst245) + 0.935140193f);
		fConst281 = (2.0f * (0.935140193f - fConst274));
		fConst282 = (fConst249 + 0.935140193f);
		fConst283 = (float)java.lang.Math.tan((7916.31738f / fConst0));
		fConst284 = (1.0f / fConst283);
		fConst285 = (1.0f / (((fConst284 + 0.157482162f) / fConst283) + 0.935140193f));
		fConst286 = mydsp_faustpower2_f(fConst283);
		fConst287 = (50.0638084f / fConst286);
		fConst288 = (2.0f * (0.935140193f - fConst287));
		fConst289 = (1.0f / (((fConst284 + 0.743130445f) / fConst283) + 1.4500711f));
		fConst290 = (11.0520525f / fConst286);
		fConst291 = (2.0f * (1.4500711f - fConst290));
		fConst292 = (1.0f / (((fConst284 + 3.18972731f) / fConst283) + 4.07678175f));
		fConst293 = (0.00176617282f / fConst286);
		fConst294 = (2.0f * (0.000407678192f - fConst293));
		fConst295 = (1.0f / (((fConst246 + 0.168404877f) / fConst245) + 1.06935835f));
		fConst296 = (2.0f * (53.5361519f - fConst274));
		fConst297 = (1.0f / (((fConst246 + 0.51247865f) / fConst245) + 0.689621389f));
		fConst298 = (2.0f * (7.62173128f - fConst274));
		fConst299 = (1.0f / (((fConst246 + 0.782413065f) / fConst245) + 0.245291501f));
		fConst300 = (9.99999975e-05f / fConst248);
		fConst301 = (2.0f * (0.000433227193f - fConst300));
		fConst302 = (((fConst246 + -0.782413065f) / fConst245) + 0.245291501f);
		fConst303 = (2.0f * (0.245291501f - fConst274));
		fConst304 = (fConst300 + 0.000433227193f);
		fConst305 = (((fConst246 + -0.51247865f) / fConst245) + 0.689621389f);
		fConst306 = (2.0f * (0.689621389f - fConst274));
		fConst307 = (fConst274 + 7.62173128f);
		fConst308 = (((fConst246 + -0.168404877f) / fConst245) + 1.06935835f);
		fConst309 = (2.0f * (1.06935835f - fConst274));
		fConst310 = (fConst274 + 53.5361519f);
		fConst311 = (((fConst284 + -3.18972731f) / fConst283) + 4.07678175f);
		fConst312 = (1.0f / fConst286);
		fConst313 = (2.0f * (4.07678175f - fConst312));
		fConst314 = (fConst293 + 0.000407678192f);
		fConst315 = (((fConst284 + -0.743130445f) / fConst283) + 1.4500711f);
		fConst316 = (2.0f * (1.4500711f - fConst312));
		fConst317 = (fConst290 + 1.4500711f);
		fConst318 = (((fConst284 + -0.157482162f) / fConst283) + 0.935140193f);
		fConst319 = (2.0f * (0.935140193f - fConst312));
		fConst320 = (fConst287 + 0.935140193f);
		fConst321 = (float)java.lang.Math.tan((4986.96729f / fConst0));
		fConst322 = (1.0f / fConst321);
		fConst323 = (1.0f / (((fConst322 + 0.157482162f) / fConst321) + 0.935140193f));
		fConst324 = mydsp_faustpower2_f(fConst321);
		fConst325 = (50.0638084f / fConst324);
		fConst326 = (2.0f * (0.935140193f - fConst325));
		fConst327 = (1.0f / (((fConst322 + 0.743130445f) / fConst321) + 1.4500711f));
		fConst328 = (11.0520525f / fConst324);
		fConst329 = (2.0f * (1.4500711f - fConst328));
		fConst330 = (1.0f / (((fConst322 + 3.18972731f) / fConst321) + 4.07678175f));
		fConst331 = (0.00176617282f / fConst324);
		fConst332 = (2.0f * (0.000407678192f - fConst331));
		fConst333 = (1.0f / (((fConst284 + 0.168404877f) / fConst283) + 1.06935835f));
		fConst334 = (2.0f * (53.5361519f - fConst312));
		fConst335 = (1.0f / (((fConst284 + 0.51247865f) / fConst283) + 0.689621389f));
		fConst336 = (2.0f * (7.62173128f - fConst312));
		fConst337 = (1.0f / (((fConst284 + 0.782413065f) / fConst283) + 0.245291501f));
		fConst338 = (9.99999975e-05f / fConst286);
		fConst339 = (2.0f * (0.000433227193f - fConst338));
		fConst340 = (((fConst284 + -0.782413065f) / fConst283) + 0.245291501f);
		fConst341 = (2.0f * (0.245291501f - fConst312));
		fConst342 = (fConst338 + 0.000433227193f);
		fConst343 = (((fConst284 + -0.51247865f) / fConst283) + 0.689621389f);
		fConst344 = (2.0f * (0.689621389f - fConst312));
		fConst345 = (fConst312 + 7.62173128f);
		fConst346 = (((fConst284 + -0.168404877f) / fConst283) + 1.06935835f);
		fConst347 = (2.0f * (1.06935835f - fConst312));
		fConst348 = (fConst312 + 53.5361519f);
		fConst349 = (((fConst322 + -3.18972731f) / fConst321) + 4.07678175f);
		fConst350 = (1.0f / fConst324);
		fConst351 = (2.0f * (4.07678175f - fConst350));
		fConst352 = (fConst331 + 0.000407678192f);
		fConst353 = (((fConst322 + -0.743130445f) / fConst321) + 1.4500711f);
		fConst354 = (2.0f * (1.4500711f - fConst350));
		fConst355 = (fConst328 + 1.4500711f);
		fConst356 = (((fConst322 + -0.157482162f) / fConst321) + 0.935140193f);
		fConst357 = (2.0f * (0.935140193f - fConst350));
		fConst358 = (fConst325 + 0.935140193f);
		fConst359 = (float)java.lang.Math.tan((3141.59277f / fConst0));
		fConst360 = (1.0f / fConst359);
		fConst361 = (1.0f / (((fConst360 + 0.157482162f) / fConst359) + 0.935140193f));
		fConst362 = mydsp_faustpower2_f(fConst359);
		fConst363 = (50.0638084f / fConst362);
		fConst364 = (2.0f * (0.935140193f - fConst363));
		fConst365 = (1.0f / (((fConst360 + 0.743130445f) / fConst359) + 1.4500711f));
		fConst366 = (11.0520525f / fConst362);
		fConst367 = (2.0f * (1.4500711f - fConst366));
		fConst368 = (1.0f / (((fConst360 + 3.18972731f) / fConst359) + 4.07678175f));
		fConst369 = (0.00176617282f / fConst362);
		fConst370 = (2.0f * (0.000407678192f - fConst369));
		fConst371 = (1.0f / (((fConst322 + 0.168404877f) / fConst321) + 1.06935835f));
		fConst372 = (2.0f * (53.5361519f - fConst350));
		fConst373 = (1.0f / (((fConst322 + 0.51247865f) / fConst321) + 0.689621389f));
		fConst374 = (2.0f * (7.62173128f - fConst350));
		fConst375 = (1.0f / (((fConst322 + 0.782413065f) / fConst321) + 0.245291501f));
		fConst376 = (9.99999975e-05f / fConst324);
		fConst377 = (2.0f * (0.000433227193f - fConst376));
		fConst378 = (((fConst322 + -0.782413065f) / fConst321) + 0.245291501f);
		fConst379 = (2.0f * (0.245291501f - fConst350));
		fConst380 = (fConst376 + 0.000433227193f);
		fConst381 = (((fConst322 + -0.51247865f) / fConst321) + 0.689621389f);
		fConst382 = (2.0f * (0.689621389f - fConst350));
		fConst383 = (fConst350 + 7.62173128f);
		fConst384 = (((fConst322 + -0.168404877f) / fConst321) + 1.06935835f);
		fConst385 = (2.0f * (1.06935835f - fConst350));
		fConst386 = (fConst350 + 53.5361519f);
		fConst387 = (((fConst360 + -3.18972731f) / fConst359) + 4.07678175f);
		fConst388 = (1.0f / fConst362);
		fConst389 = (2.0f * (4.07678175f - fConst388));
		fConst390 = (fConst369 + 0.000407678192f);
		fConst391 = (((fConst360 + -0.743130445f) / fConst359) + 1.4500711f);
		fConst392 = (2.0f * (1.4500711f - fConst388));
		fConst393 = (fConst366 + 1.4500711f);
		fConst394 = (((fConst360 + -0.157482162f) / fConst359) + 0.935140193f);
		fConst395 = (2.0f * (0.935140193f - fConst388));
		fConst396 = (fConst363 + 0.935140193f);
		fConst397 = (float)java.lang.Math.tan((1979.07935f / fConst0));
		fConst398 = (1.0f / fConst397);
		fConst399 = (1.0f / (((fConst398 + 0.157482162f) / fConst397) + 0.935140193f));
		fConst400 = mydsp_faustpower2_f(fConst397);
		fConst401 = (50.0638084f / fConst400);
		fConst402 = (2.0f * (0.935140193f - fConst401));
		fConst403 = (1.0f / (((fConst398 + 0.743130445f) / fConst397) + 1.4500711f));
		fConst404 = (11.0520525f / fConst400);
		fConst405 = (2.0f * (1.4500711f - fConst404));
		fConst406 = (1.0f / (((fConst398 + 3.18972731f) / fConst397) + 4.07678175f));
		fConst407 = (0.00176617282f / fConst400);
		fConst408 = (2.0f * (0.000407678192f - fConst407));
		fConst409 = (1.0f / (((fConst360 + 0.168404877f) / fConst359) + 1.06935835f));
		fConst410 = (2.0f * (53.5361519f - fConst388));
		fConst411 = (1.0f / (((fConst360 + 0.51247865f) / fConst359) + 0.689621389f));
		fConst412 = (2.0f * (7.62173128f - fConst388));
		fConst413 = (1.0f / (((fConst360 + 0.782413065f) / fConst359) + 0.245291501f));
		fConst414 = (9.99999975e-05f / fConst362);
		fConst415 = (2.0f * (0.000433227193f - fConst414));
		fConst416 = (((fConst360 + -0.782413065f) / fConst359) + 0.245291501f);
		fConst417 = (2.0f * (0.245291501f - fConst388));
		fConst418 = (fConst414 + 0.000433227193f);
		fConst419 = (((fConst360 + -0.51247865f) / fConst359) + 0.689621389f);
		fConst420 = (2.0f * (0.689621389f - fConst388));
		fConst421 = (fConst388 + 7.62173128f);
		fConst422 = (((fConst360 + -0.168404877f) / fConst359) + 1.06935835f);
		fConst423 = (2.0f * (1.06935835f - fConst388));
		fConst424 = (fConst388 + 53.5361519f);
		fConst425 = (((fConst398 + -3.18972731f) / fConst397) + 4.07678175f);
		fConst426 = (1.0f / fConst400);
		fConst427 = (2.0f * (4.07678175f - fConst426));
		fConst428 = (fConst407 + 0.000407678192f);
		fConst429 = (((fConst398 + -0.743130445f) / fConst397) + 1.4500711f);
		fConst430 = (2.0f * (1.4500711f - fConst426));
		fConst431 = (fConst404 + 1.4500711f);
		fConst432 = (((fConst398 + -0.157482162f) / fConst397) + 0.935140193f);
		fConst433 = (2.0f * (0.935140193f - fConst426));
		fConst434 = (fConst401 + 0.935140193f);
		fConst435 = (float)java.lang.Math.tan((1246.74182f / fConst0));
		fConst436 = (1.0f / fConst435);
		fConst437 = (1.0f / (((fConst436 + 0.157482162f) / fConst435) + 0.935140193f));
		fConst438 = mydsp_faustpower2_f(fConst435);
		fConst439 = (50.0638084f / fConst438);
		fConst440 = (2.0f * (0.935140193f - fConst439));
		fConst441 = (1.0f / (((fConst436 + 0.743130445f) / fConst435) + 1.4500711f));
		fConst442 = (11.0520525f / fConst438);
		fConst443 = (2.0f * (1.4500711f - fConst442));
		fConst444 = (1.0f / (((fConst436 + 3.18972731f) / fConst435) + 4.07678175f));
		fConst445 = (0.00176617282f / fConst438);
		fConst446 = (2.0f * (0.000407678192f - fConst445));
		fConst447 = (1.0f / (((fConst398 + 0.168404877f) / fConst397) + 1.06935835f));
		fConst448 = (2.0f * (53.5361519f - fConst426));
		fConst449 = (1.0f / (((fConst398 + 0.51247865f) / fConst397) + 0.689621389f));
		fConst450 = (2.0f * (7.62173128f - fConst426));
		fConst451 = (1.0f / (((fConst398 + 0.782413065f) / fConst397) + 0.245291501f));
		fConst452 = (9.99999975e-05f / fConst400);
		fConst453 = (2.0f * (0.000433227193f - fConst452));
		fConst454 = (((fConst398 + -0.782413065f) / fConst397) + 0.245291501f);
		fConst455 = (2.0f * (0.245291501f - fConst426));
		fConst456 = (fConst452 + 0.000433227193f);
		fConst457 = (((fConst398 + -0.51247865f) / fConst397) + 0.689621389f);
		fConst458 = (2.0f * (0.689621389f - fConst426));
		fConst459 = (fConst426 + 7.62173128f);
		fConst460 = (((fConst398 + -0.168404877f) / fConst397) + 1.06935835f);
		fConst461 = (2.0f * (1.06935835f - fConst426));
		fConst462 = (fConst426 + 53.5361519f);
		fConst463 = (((fConst436 + -3.18972731f) / fConst435) + 4.07678175f);
		fConst464 = (1.0f / fConst438);
		fConst465 = (2.0f * (4.07678175f - fConst464));
		fConst466 = (fConst445 + 0.000407678192f);
		fConst467 = (((fConst436 + -0.743130445f) / fConst435) + 1.4500711f);
		fConst468 = (2.0f * (1.4500711f - fConst464));
		fConst469 = (fConst442 + 1.4500711f);
		fConst470 = (((fConst436 + -0.157482162f) / fConst435) + 0.935140193f);
		fConst471 = (2.0f * (0.935140193f - fConst464));
		fConst472 = (fConst439 + 0.935140193f);
		fConst473 = (float)java.lang.Math.tan((785.398193f / fConst0));
		fConst474 = (1.0f / fConst473);
		fConst475 = (1.0f / (((fConst474 + 0.157482162f) / fConst473) + 0.935140193f));
		fConst476 = mydsp_faustpower2_f(fConst473);
		fConst477 = (50.0638084f / fConst476);
		fConst478 = (2.0f * (0.935140193f - fConst477));
		fConst479 = (1.0f / (((fConst474 + 0.743130445f) / fConst473) + 1.4500711f));
		fConst480 = (11.0520525f / fConst476);
		fConst481 = (2.0f * (1.4500711f - fConst480));
		fConst482 = (1.0f / (((fConst474 + 3.18972731f) / fConst473) + 4.07678175f));
		fConst483 = (0.00176617282f / fConst476);
		fConst484 = (2.0f * (0.000407678192f - fConst483));
		fConst485 = (1.0f / (((fConst436 + 0.168404877f) / fConst435) + 1.06935835f));
		fConst486 = (2.0f * (53.5361519f - fConst464));
		fConst487 = (1.0f / (((fConst436 + 0.51247865f) / fConst435) + 0.689621389f));
		fConst488 = (2.0f * (7.62173128f - fConst464));
		fConst489 = (1.0f / (((fConst436 + 0.782413065f) / fConst435) + 0.245291501f));
		fConst490 = (9.99999975e-05f / fConst438);
		fConst491 = (2.0f * (0.000433227193f - fConst490));
		fConst492 = (((fConst436 + -0.782413065f) / fConst435) + 0.245291501f);
		fConst493 = (2.0f * (0.245291501f - fConst464));
		fConst494 = (fConst490 + 0.000433227193f);
		fConst495 = (((fConst436 + -0.51247865f) / fConst435) + 0.689621389f);
		fConst496 = (2.0f * (0.689621389f - fConst464));
		fConst497 = (fConst464 + 7.62173128f);
		fConst498 = (((fConst436 + -0.168404877f) / fConst435) + 1.06935835f);
		fConst499 = (2.0f * (1.06935835f - fConst464));
		fConst500 = (fConst464 + 53.5361519f);
		fConst501 = (((fConst474 + -3.18972731f) / fConst473) + 4.07678175f);
		fConst502 = (1.0f / fConst476);
		fConst503 = (2.0f * (4.07678175f - fConst502));
		fConst504 = (fConst483 + 0.000407678192f);
		fConst505 = (((fConst474 + -0.743130445f) / fConst473) + 1.4500711f);
		fConst506 = (2.0f * (1.4500711f - fConst502));
		fConst507 = (fConst480 + 1.4500711f);
		fConst508 = (((fConst474 + -0.157482162f) / fConst473) + 0.935140193f);
		fConst509 = (2.0f * (0.935140193f - fConst502));
		fConst510 = (fConst477 + 0.935140193f);
		fConst511 = (float)java.lang.Math.tan((494.769836f / fConst0));
		fConst512 = (1.0f / fConst511);
		fConst513 = (1.0f / (((fConst512 + 0.157482162f) / fConst511) + 0.935140193f));
		fConst514 = mydsp_faustpower2_f(fConst511);
		fConst515 = (50.0638084f / fConst514);
		fConst516 = (2.0f * (0.935140193f - fConst515));
		fConst517 = (1.0f / (((fConst512 + 0.743130445f) / fConst511) + 1.4500711f));
		fConst518 = (11.0520525f / fConst514);
		fConst519 = (2.0f * (1.4500711f - fConst518));
		fConst520 = (1.0f / (((fConst512 + 3.18972731f) / fConst511) + 4.07678175f));
		fConst521 = (0.00176617282f / fConst514);
		fConst522 = (2.0f * (0.000407678192f - fConst521));
		fConst523 = (1.0f / (((fConst474 + 0.168404877f) / fConst473) + 1.06935835f));
		fConst524 = (2.0f * (53.5361519f - fConst502));
		fConst525 = (1.0f / (((fConst474 + 0.51247865f) / fConst473) + 0.689621389f));
		fConst526 = (2.0f * (7.62173128f - fConst502));
		fConst527 = (1.0f / (((fConst474 + 0.782413065f) / fConst473) + 0.245291501f));
		fConst528 = (9.99999975e-05f / fConst476);
		fConst529 = (2.0f * (0.000433227193f - fConst528));
		fConst530 = (((fConst474 + -0.782413065f) / fConst473) + 0.245291501f);
		fConst531 = (2.0f * (0.245291501f - fConst502));
		fConst532 = (fConst528 + 0.000433227193f);
		fConst533 = (((fConst474 + -0.51247865f) / fConst473) + 0.689621389f);
		fConst534 = (2.0f * (0.689621389f - fConst502));
		fConst535 = (fConst502 + 7.62173128f);
		fConst536 = (((fConst474 + -0.168404877f) / fConst473) + 1.06935835f);
		fConst537 = (2.0f * (1.06935835f - fConst502));
		fConst538 = (fConst502 + 53.5361519f);
		fConst539 = (((fConst512 + -3.18972731f) / fConst511) + 4.07678175f);
		fConst540 = (1.0f / fConst514);
		fConst541 = (2.0f * (4.07678175f - fConst540));
		fConst542 = (fConst521 + 0.000407678192f);
		fConst543 = (((fConst512 + -0.743130445f) / fConst511) + 1.4500711f);
		fConst544 = (2.0f * (1.4500711f - fConst540));
		fConst545 = (fConst518 + 1.4500711f);
		fConst546 = (((fConst512 + -0.157482162f) / fConst511) + 0.935140193f);
		fConst547 = (2.0f * (0.935140193f - fConst540));
		fConst548 = (fConst515 + 0.935140193f);
		fConst549 = (float)java.lang.Math.tan((311.685455f / fConst0));
		fConst550 = (1.0f / fConst549);
		fConst551 = (1.0f / (((fConst550 + 0.157482162f) / fConst549) + 0.935140193f));
		fConst552 = mydsp_faustpower2_f(fConst549);
		fConst553 = (50.0638084f / fConst552);
		fConst554 = (2.0f * (0.935140193f - fConst553));
		fConst555 = (1.0f / (((fConst550 + 0.743130445f) / fConst549) + 1.4500711f));
		fConst556 = (11.0520525f / fConst552);
		fConst557 = (2.0f * (1.4500711f - fConst556));
		fConst558 = (1.0f / (((fConst550 + 3.18972731f) / fConst549) + 4.07678175f));
		fConst559 = (0.00176617282f / fConst552);
		fConst560 = (2.0f * (0.000407678192f - fConst559));
		fConst561 = (1.0f / (((fConst512 + 0.168404877f) / fConst511) + 1.06935835f));
		fConst562 = (2.0f * (53.5361519f - fConst540));
		fConst563 = (1.0f / (((fConst512 + 0.51247865f) / fConst511) + 0.689621389f));
		fConst564 = (2.0f * (7.62173128f - fConst540));
		fConst565 = (1.0f / (((fConst512 + 0.782413065f) / fConst511) + 0.245291501f));
		fConst566 = (9.99999975e-05f / fConst514);
		fConst567 = (2.0f * (0.000433227193f - fConst566));
		fConst568 = (((fConst512 + -0.782413065f) / fConst511) + 0.245291501f);
		fConst569 = (2.0f * (0.245291501f - fConst540));
		fConst570 = (fConst566 + 0.000433227193f);
		fConst571 = (((fConst512 + -0.51247865f) / fConst511) + 0.689621389f);
		fConst572 = (2.0f * (0.689621389f - fConst540));
		fConst573 = (fConst540 + 7.62173128f);
		fConst574 = (((fConst512 + -0.168404877f) / fConst511) + 1.06935835f);
		fConst575 = (2.0f * (1.06935835f - fConst540));
		fConst576 = (fConst540 + 53.5361519f);
		fConst577 = (((fConst550 + -3.18972731f) / fConst549) + 4.07678175f);
		fConst578 = (1.0f / fConst552);
		fConst579 = (2.0f * (4.07678175f - fConst578));
		fConst580 = (fConst559 + 0.000407678192f);
		fConst581 = (((fConst550 + -0.743130445f) / fConst549) + 1.4500711f);
		fConst582 = (2.0f * (1.4500711f - fConst578));
		fConst583 = (fConst556 + 1.4500711f);
		fConst584 = (((fConst550 + -0.157482162f) / fConst549) + 0.935140193f);
		fConst585 = (2.0f * (0.935140193f - fConst578));
		fConst586 = (fConst553 + 0.935140193f);
		fConst587 = (float)java.lang.Math.tan((196.349548f / fConst0));
		fConst588 = (1.0f / fConst587);
		fConst589 = (1.0f / (((fConst588 + 0.157482162f) / fConst587) + 0.935140193f));
		fConst590 = mydsp_faustpower2_f(fConst587);
		fConst591 = (50.0638084f / fConst590);
		fConst592 = (2.0f * (0.935140193f - fConst591));
		fConst593 = (1.0f / (((fConst588 + 0.743130445f) / fConst587) + 1.4500711f));
		fConst594 = (11.0520525f / fConst590);
		fConst595 = (2.0f * (1.4500711f - fConst594));
		fConst596 = (1.0f / (((fConst588 + 3.18972731f) / fConst587) + 4.07678175f));
		fConst597 = (0.00176617282f / fConst590);
		fConst598 = (2.0f * (0.000407678192f - fConst597));
		fConst599 = (1.0f / (((fConst550 + 0.168404877f) / fConst549) + 1.06935835f));
		fConst600 = (2.0f * (53.5361519f - fConst578));
		fConst601 = (1.0f / (((fConst550 + 0.51247865f) / fConst549) + 0.689621389f));
		fConst602 = (2.0f * (7.62173128f - fConst578));
		fConst603 = (1.0f / (((fConst550 + 0.782413065f) / fConst549) + 0.245291501f));
		fConst604 = (9.99999975e-05f / fConst552);
		fConst605 = (2.0f * (0.000433227193f - fConst604));
		fConst606 = (((fConst550 + -0.782413065f) / fConst549) + 0.245291501f);
		fConst607 = (2.0f * (0.245291501f - fConst578));
		fConst608 = (fConst604 + 0.000433227193f);
		fConst609 = (((fConst550 + -0.51247865f) / fConst549) + 0.689621389f);
		fConst610 = (2.0f * (0.689621389f - fConst578));
		fConst611 = (fConst578 + 7.62173128f);
		fConst612 = (((fConst550 + -0.168404877f) / fConst549) + 1.06935835f);
		fConst613 = (2.0f * (1.06935835f - fConst578));
		fConst614 = (fConst578 + 53.5361519f);
		fConst615 = (((fConst588 + -3.18972731f) / fConst587) + 4.07678175f);
		fConst616 = (1.0f / fConst590);
		fConst617 = (2.0f * (4.07678175f - fConst616));
		fConst618 = (fConst597 + 0.000407678192f);
		fConst619 = (((fConst588 + -0.743130445f) / fConst587) + 1.4500711f);
		fConst620 = (2.0f * (1.4500711f - fConst616));
		fConst621 = (fConst594 + 1.4500711f);
		fConst622 = (((fConst588 + -0.157482162f) / fConst587) + 0.935140193f);
		fConst623 = (2.0f * (0.935140193f - fConst616));
		fConst624 = (fConst591 + 0.935140193f);
		fConst625 = (float)java.lang.Math.tan((123.692459f / fConst0));
		fConst626 = (1.0f / fConst625);
		fConst627 = (1.0f / (((fConst626 + 0.157482162f) / fConst625) + 0.935140193f));
		fConst628 = mydsp_faustpower2_f(fConst625);
		fConst629 = (50.0638084f / fConst628);
		fConst630 = (2.0f * (0.935140193f - fConst629));
		fConst631 = (1.0f / (((fConst626 + 0.743130445f) / fConst625) + 1.4500711f));
		fConst632 = (11.0520525f / fConst628);
		fConst633 = (2.0f * (1.4500711f - fConst632));
		fConst634 = (1.0f / (((fConst626 + 3.18972731f) / fConst625) + 4.07678175f));
		fConst635 = (0.00176617282f / fConst628);
		fConst636 = (2.0f * (0.000407678192f - fConst635));
		fConst637 = (1.0f / (((fConst588 + 0.168404877f) / fConst587) + 1.06935835f));
		fConst638 = (2.0f * (53.5361519f - fConst616));
		fConst639 = (1.0f / (((fConst588 + 0.51247865f) / fConst587) + 0.689621389f));
		fConst640 = (2.0f * (7.62173128f - fConst616));
		fConst641 = (1.0f / (((fConst588 + 0.782413065f) / fConst587) + 0.245291501f));
		fConst642 = (9.99999975e-05f / fConst590);
		fConst643 = (2.0f * (0.000433227193f - fConst642));
		fConst644 = (((fConst588 + -0.782413065f) / fConst587) + 0.245291501f);
		fConst645 = (2.0f * (0.245291501f - fConst616));
		fConst646 = (fConst642 + 0.000433227193f);
		fConst647 = (((fConst588 + -0.51247865f) / fConst587) + 0.689621389f);
		fConst648 = (2.0f * (0.689621389f - fConst616));
		fConst649 = (fConst616 + 7.62173128f);
		fConst650 = (((fConst588 + -0.168404877f) / fConst587) + 1.06935835f);
		fConst651 = (2.0f * (1.06935835f - fConst616));
		fConst652 = (fConst616 + 53.5361519f);
		fConst653 = (((fConst626 + -3.18972731f) / fConst625) + 4.07678175f);
		fConst654 = (1.0f / fConst628);
		fConst655 = (2.0f * (4.07678175f - fConst654));
		fConst656 = (fConst635 + 0.000407678192f);
		fConst657 = (((fConst626 + -0.743130445f) / fConst625) + 1.4500711f);
		fConst658 = (2.0f * (1.4500711f - fConst654));
		fConst659 = (fConst632 + 1.4500711f);
		fConst660 = (((fConst626 + -0.157482162f) / fConst625) + 0.935140193f);
		fConst661 = (2.0f * (0.935140193f - fConst654));
		fConst662 = (fConst629 + 0.935140193f);
		fConst663 = (1.0f / (((fConst626 + 0.168404877f) / fConst625) + 1.06935835f));
		fConst664 = (2.0f * (53.5361519f - fConst654));
		fConst665 = (1.0f / (((fConst626 + 0.51247865f) / fConst625) + 0.689621389f));
		fConst666 = (2.0f * (7.62173128f - fConst654));
		fConst667 = (1.0f / (((fConst626 + 0.782413065f) / fConst625) + 0.245291501f));
		fConst668 = (9.99999975e-05f / fConst628);
		fConst669 = (2.0f * (0.000433227193f - fConst668));
		fConst670 = (((fConst626 + -0.782413065f) / fConst625) + 0.245291501f);
		fConst671 = (2.0f * (0.245291501f - fConst654));
		fConst672 = (fConst668 + 0.000433227193f);
		fConst673 = (((fConst626 + -0.51247865f) / fConst625) + 0.689621389f);
		fConst674 = (2.0f * (0.689621389f - fConst654));
		fConst675 = (fConst654 + 7.62173128f);
		fConst676 = (((fConst626 + -0.168404877f) / fConst625) + 1.06935835f);
		fConst677 = (2.0f * (1.06935835f - fConst654));
		fConst678 = (fConst654 + 53.5361519f);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)50.0f;
		fHslider1 = (float)100.0f;
		fCheckbox0 = (float)0.0f;
		fVslider0 = (float)-20.0f;
		fCheckbox1 = (float)0.0f;
		fCheckbox2 = (float)0.0f;
		fEntry0 = (float)2.0f;
		fVslider1 = (float)49.0f;
		fVslider2 = (float)0.10000000000000001f;
		fVslider3 = (float)-0.10000000000000001f;
		fVslider4 = (float)0.10000000000000001f;
		fCheckbox3 = (float)0.0f;
		fVslider5 = (float)-10.0f;
		fVslider6 = (float)-10.0f;
		fVslider7 = (float)-10.0f;
		fVslider8 = (float)-10.0f;
		fVslider9 = (float)-10.0f;
		fVslider10 = (float)-10.0f;
		fVslider11 = (float)-10.0f;
		fVslider12 = (float)-10.0f;
		fVslider13 = (float)-10.0f;
		fVslider14 = (float)-10.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec21[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec23[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec22[l4] = 0.0f;
			
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
			fRec24[l12] = 0.0f;
			
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
			fRec25[l20] = 0.0f;
			
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
			iRec26[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec27[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec22[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec20[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec19[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec18[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec23[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec17[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec16[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec15[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec24[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec14[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec13[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec12[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fVec25[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec11[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec10[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec9[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec8[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec7[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec6[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec5[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec4[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec28[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec38[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec37[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec36[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fVec26[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec35[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec34[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec33[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec32[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec31[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec30[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec29[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec39[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec48[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec47[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec46[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fVec27[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
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
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec41[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec40[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec49[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec57[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec56[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec55[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fVec28[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec54[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec53[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec52[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec51[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec50[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec58[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec65[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec64[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec63[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fVec29[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
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
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec66[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec72[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec71[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec70[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fVec30[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec69[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec68[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec67[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec73[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec76[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec75[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec74[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec77[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec88[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec87[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec86[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec85[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec84[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec83[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec82[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec81[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec80[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec79[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec78[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fRec89[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec99[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec98[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec97[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec96[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec95[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec94[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec93[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec92[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec91[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec90[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec100[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec109[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec108[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec107[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec106[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec105[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec104[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec103[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec102[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec101[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			fRec110[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec3[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec2[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec1[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec0[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec117[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec116[l143] = 0.0f;
			
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
		for (int l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			fRec112[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			fRec111[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec124[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			fRec123[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec122[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			fRec121[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec120[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			fRec119[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			fRec118[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			fRec131[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			fRec130[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			fRec129[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			fRec128[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			fRec127[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			fRec126[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fRec125[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			fRec138[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			fRec137[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			fRec136[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 3); l166 = (l166 + 1)) {
			fRec135[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			fRec134[l167] = 0.0f;
			
		}
		for (int l168 = 0; (l168 < 3); l168 = (l168 + 1)) {
			fRec133[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			fRec132[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			fRec145[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			fRec144[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 3); l172 = (l172 + 1)) {
			fRec143[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			fRec142[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 3); l174 = (l174 + 1)) {
			fRec141[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 3); l175 = (l175 + 1)) {
			fRec140[l175] = 0.0f;
			
		}
		for (int l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			fRec139[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 3); l177 = (l177 + 1)) {
			fRec152[l177] = 0.0f;
			
		}
		for (int l178 = 0; (l178 < 3); l178 = (l178 + 1)) {
			fRec151[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 3); l179 = (l179 + 1)) {
			fRec150[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 3); l180 = (l180 + 1)) {
			fRec149[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 3); l181 = (l181 + 1)) {
			fRec148[l181] = 0.0f;
			
		}
		for (int l182 = 0; (l182 < 3); l182 = (l182 + 1)) {
			fRec147[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			fRec146[l183] = 0.0f;
			
		}
		for (int l184 = 0; (l184 < 3); l184 = (l184 + 1)) {
			fRec159[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			fRec158[l185] = 0.0f;
			
		}
		for (int l186 = 0; (l186 < 3); l186 = (l186 + 1)) {
			fRec157[l186] = 0.0f;
			
		}
		for (int l187 = 0; (l187 < 3); l187 = (l187 + 1)) {
			fRec156[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			fRec155[l188] = 0.0f;
			
		}
		for (int l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			fRec154[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			fRec153[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 3); l191 = (l191 + 1)) {
			fRec166[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 3); l192 = (l192 + 1)) {
			fRec165[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 3); l193 = (l193 + 1)) {
			fRec164[l193] = 0.0f;
			
		}
		for (int l194 = 0; (l194 < 3); l194 = (l194 + 1)) {
			fRec163[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 3); l195 = (l195 + 1)) {
			fRec162[l195] = 0.0f;
			
		}
		for (int l196 = 0; (l196 < 3); l196 = (l196 + 1)) {
			fRec161[l196] = 0.0f;
			
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			fRec160[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 3); l198 = (l198 + 1)) {
			fRec173[l198] = 0.0f;
			
		}
		for (int l199 = 0; (l199 < 3); l199 = (l199 + 1)) {
			fRec172[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 3); l200 = (l200 + 1)) {
			fRec171[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 3); l201 = (l201 + 1)) {
			fRec170[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 3); l202 = (l202 + 1)) {
			fRec169[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			fRec168[l203] = 0.0f;
			
		}
		for (int l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			fRec167[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 3); l205 = (l205 + 1)) {
			fRec180[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 3); l206 = (l206 + 1)) {
			fRec179[l206] = 0.0f;
			
		}
		for (int l207 = 0; (l207 < 3); l207 = (l207 + 1)) {
			fRec178[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 3); l208 = (l208 + 1)) {
			fRec177[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 3); l209 = (l209 + 1)) {
			fRec176[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 3); l210 = (l210 + 1)) {
			fRec175[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			fRec174[l211] = 0.0f;
			
		}
		for (int l212 = 0; (l212 < 3); l212 = (l212 + 1)) {
			fRec187[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 3); l213 = (l213 + 1)) {
			fRec186[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 3); l214 = (l214 + 1)) {
			fRec185[l214] = 0.0f;
			
		}
		for (int l215 = 0; (l215 < 3); l215 = (l215 + 1)) {
			fRec184[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 3); l216 = (l216 + 1)) {
			fRec183[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 3); l217 = (l217 + 1)) {
			fRec182[l217] = 0.0f;
			
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fRec181[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 3); l219 = (l219 + 1)) {
			fRec194[l219] = 0.0f;
			
		}
		for (int l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			fRec193[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			fRec192[l221] = 0.0f;
			
		}
		for (int l222 = 0; (l222 < 3); l222 = (l222 + 1)) {
			fRec191[l222] = 0.0f;
			
		}
		for (int l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			fRec190[l223] = 0.0f;
			
		}
		for (int l224 = 0; (l224 < 3); l224 = (l224 + 1)) {
			fRec189[l224] = 0.0f;
			
		}
		for (int l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			fRec188[l225] = 0.0f;
			
		}
		for (int l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			fRec201[l226] = 0.0f;
			
		}
		for (int l227 = 0; (l227 < 3); l227 = (l227 + 1)) {
			fRec200[l227] = 0.0f;
			
		}
		for (int l228 = 0; (l228 < 3); l228 = (l228 + 1)) {
			fRec199[l228] = 0.0f;
			
		}
		for (int l229 = 0; (l229 < 3); l229 = (l229 + 1)) {
			fRec198[l229] = 0.0f;
			
		}
		for (int l230 = 0; (l230 < 3); l230 = (l230 + 1)) {
			fRec197[l230] = 0.0f;
			
		}
		for (int l231 = 0; (l231 < 3); l231 = (l231 + 1)) {
			fRec196[l231] = 0.0f;
			
		}
		for (int l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			fRec195[l232] = 0.0f;
			
		}
		for (int l233 = 0; (l233 < 3); l233 = (l233 + 1)) {
			fRec205[l233] = 0.0f;
			
		}
		for (int l234 = 0; (l234 < 3); l234 = (l234 + 1)) {
			fRec204[l234] = 0.0f;
			
		}
		for (int l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			fRec203[l235] = 0.0f;
			
		}
		for (int l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			fRec202[l236] = 0.0f;
			
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
		ui_interface.openVerticalBox("graphicEqLab");
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
		ui_interface.declare("0", "2", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openVerticalBox("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the filter-bank has no effect");
		ui_interface.addCheckButton("Bypass", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider11", "1", "");
		ui_interface.declare("fVslider11", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider11", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider11"; }
				public void set(float val) { fVslider11 = val; }
				public float get() { return (float)fVslider11; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider10", "2", "");
		ui_interface.declare("fVslider10", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider10", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider10"; }
				public void set(float val) { fVslider10 = val; }
				public float get() { return (float)fVslider10; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider9", "3", "");
		ui_interface.declare("fVslider9", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider9", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider9"; }
				public void set(float val) { fVslider9 = val; }
				public float get() { return (float)fVslider9; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider8", "4", "");
		ui_interface.declare("fVslider8", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider8", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider8"; }
				public void set(float val) { fVslider8 = val; }
				public float get() { return (float)fVslider8; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider7", "5", "");
		ui_interface.declare("fVslider7", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider7", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider7"; }
				public void set(float val) { fVslider7 = val; }
				public float get() { return (float)fVslider7; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider6", "6", "");
		ui_interface.declare("fVslider6", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider6", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider6"; }
				public void set(float val) { fVslider6 = val; }
				public float get() { return (float)fVslider6; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider5", "7", "");
		ui_interface.declare("fVslider5", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider5"; }
				public void set(float val) { fVslider5 = val; }
				public float get() { return (float)fVslider5; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider14", "8", "");
		ui_interface.declare("fVslider14", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider14", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider14"; }
				public void set(float val) { fVslider14 = val; }
				public float get() { return (float)fVslider14; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider13", "9", "");
		ui_interface.declare("fVslider13", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider13", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider13"; }
				public void set(float val) { fVslider13 = val; }
				public float get() { return (float)fVslider13; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.declare("fVslider12", "10", "");
		ui_interface.declare("fVslider12", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider12", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", new FaustVarAccess() {
				public String getId() { return "fVslider12"; }
				public void set(float val) { fVslider12 = val; }
				public float get() { return (float)fVslider12; }
			}
			, -10.0f, -70.0f, 10.0f, 0.100000001f);
		ui_interface.closeBox();
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
		ui_interface.addVerticalBargraph("0x7fc36f128140", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f1167e0", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f0f0710", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f0ce5c0", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f0ac470", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f08a320", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f0681d0", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f046080", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f023f30", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36f001de0", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36efdbd10", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36efb9bc0", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36ef97a70", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36ef75920", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc36ef52740", new FaustVarAccess() {
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
		float fSlow4 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		int iSlow5 = (int)fCheckbox1;
		int iSlow6 = (int)fCheckbox2;
		int iSlow7 = (int)(fEntry0 + -1.0f);
		int iSlow8 = (iSlow7 >= 2);
		int iSlow9 = (iSlow7 >= 1);
		float fSlow10 = (float)java.lang.Math.exp((0.0f - (fConst44 / fVslider2)));
		float fSlow11 = (440.0f * ((float)java.lang.Math.pow(2.0f, (0.0833333358f * (fVslider1 + -49.0f))) * (1.0f - fSlow10)));
		int iSlow12 = (iSlow7 >= 3);
		float fSlow13 = ((0.00999999978f * fVslider3) + 1.0f);
		float fSlow14 = ((0.00999999978f * fVslider4) + 1.0f);
		int iSlow15 = (int)fCheckbox3;
		float fSlow16 = (0.00100000005f * fVslider5);
		float fSlow17 = (0.00100000005f * fVslider6);
		float fSlow18 = (0.00100000005f * fVslider7);
		float fSlow19 = (0.00100000005f * fVslider8);
		float fSlow20 = (0.00100000005f * fVslider9);
		float fSlow21 = (0.00100000005f * fVslider10);
		float fSlow22 = (0.00100000005f * fVslider11);
		float fSlow23 = (0.00100000005f * fVslider12);
		float fSlow24 = (0.00100000005f * fVslider13);
		float fSlow25 = (0.00100000005f * fVslider14);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec21[0] = (fSlow4 + (0.999000013f * fRec21[1]));
			fRec23[0] = (fSlow11 + (fSlow10 * fRec23[1]));
			float fTemp0 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fRec23[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec22[1] + (fConst44 * fVec1[1]));
			fRec22[0] = (fTemp1 - (float)java.lang.Math.floor(fTemp1));
			float fTemp2 = (2.0f * fRec22[0]);
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
			float fTemp10 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow13 * fRec23[0])));
			fVec8[0] = fTemp10;
			float fTemp11 = (fRec24[1] + (fConst44 * fVec8[1]));
			fRec24[0] = (fTemp11 - (float)java.lang.Math.floor(fTemp11));
			float fTemp12 = (2.0f * fRec24[0]);
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
			float fTemp20 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow14 * fRec23[0])));
			fVec15[0] = fTemp20;
			float fTemp21 = (fRec25[1] + (fConst44 * fVec15[1]));
			fRec25[0] = (fTemp21 - (float)java.lang.Math.floor(fTemp21));
			float fTemp22 = (2.0f * fRec25[0]);
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
			iRec26[0] = ((1103515245 * iRec26[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * (float)iRec26[0]);
			fRec27[0] = (((0.522189379f * fRec27[3]) + (fTemp30 + (2.49495602f * fRec27[1]))) - (2.0172658f * fRec27[2]));
			float fTemp31 = (fRec21[0] * (((iSlow5==0)?true:false)?input0[i]:(((iSlow6==0)?true:false)?(((iSlow15==0)?true:false)?(((0.0499220341f * fRec27[0]) + (0.0506126992f * fRec27[2])) - ((0.0959935337f * fRec27[1]) + (0.00440878607f * fRec27[3]))):fTemp30):(0.333333343f * (fRec21[0] * (((((iSlow8==0)?true:false)?(((iSlow12==0)?true:false)?(fConst47 * (((float)iVec0[3] * (fTemp9 - fVec7[1])) / fTemp0)):(fConst46 * (((float)iVec0[2] * (fTemp6 - fVec4[1])) / fTemp0))):(((iSlow9==0)?true:false)?(fConst45 * (((float)iVec0[1] * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (((iSlow8==0)?true:false)?(((iSlow12==0)?true:false)?(fConst47 * (((float)iVec0[3] * (fTemp19 - fVec14[1])) / fTemp10)):(fConst46 * (((float)iVec0[2] * (fTemp16 - fVec11[1])) / fTemp10))):(((iSlow9==0)?true:false)?(fConst45 * (((float)iVec0[1] * (fTemp14 - fVec9[1])) / fTemp10)):fTemp13))) + (((iSlow8==0)?true:false)?(((iSlow12==0)?true:false)?(fConst47 * (((float)iVec0[3] * (fTemp29 - fVec21[1])) / fTemp20)):(fConst46 * (((float)iVec0[2] * (fTemp26 - fVec18[1])) / fTemp20))):(((iSlow9==0)?true:false)?(fConst45 * (((float)iVec0[1] * (fTemp24 - fVec16[1])) / fTemp20)):fTemp23))))))));
			float fTemp32 = (((iSlow3==0)?true:false)?0.0f:fTemp31);
			fVec22[0] = fTemp32;
			fRec20[0] = ((fConst42 * fRec20[1]) + (fConst43 * (fTemp32 + fVec22[1])));
			fRec19[0] = (fRec20[0] - (fConst40 * ((fConst49 * fRec19[1]) + (fConst50 * fRec19[2]))));
			fRec18[0] = ((fConst40 * (fRec19[2] + (fRec19[0] + (2.0f * fRec19[1])))) - (fConst51 * ((fConst49 * fRec18[1]) + (fConst52 * fRec18[2]))));
			float fTemp33 = (fRec18[2] + (fRec18[0] + (2.0f * fRec18[1])));
			fVec23[0] = fTemp33;
			fRec17[0] = ((fConst35 * fRec17[1]) + (fConst39 * (fTemp33 + fVec23[1])));
			fRec16[0] = (fRec17[0] - (fConst33 * ((fConst54 * fRec16[1]) + (fConst55 * fRec16[2]))));
			fRec15[0] = ((fConst33 * (fRec16[2] + (fRec16[0] + (2.0f * fRec16[1])))) - (fConst56 * ((fConst54 * fRec15[1]) + (fConst57 * fRec15[2]))));
			float fTemp34 = (fRec15[2] + (fRec15[0] + (2.0f * fRec15[1])));
			fVec24[0] = fTemp34;
			fRec14[0] = ((fConst28 * fRec14[1]) + (fConst32 * (fTemp34 + fVec24[1])));
			fRec13[0] = (fRec14[0] - (fConst26 * ((fConst59 * fRec13[1]) + (fConst60 * fRec13[2]))));
			fRec12[0] = ((fConst26 * (fRec13[2] + ((2.0f * fRec13[1]) + fRec13[0]))) - (fConst61 * ((fConst59 * fRec12[1]) + (fConst62 * fRec12[2]))));
			float fTemp35 = (fRec12[2] + ((2.0f * fRec12[1]) + fRec12[0]));
			fVec25[0] = fTemp35;
			fRec11[0] = ((fConst25 * ((fConst15 * fTemp35) + (fConst63 * fVec25[1]))) + (fConst64 * fRec11[1]));
			fRec10[0] = (fRec11[0] - (fConst20 * ((fConst65 * fRec10[1]) + (fConst66 * fRec10[2]))));
			fRec9[0] = ((fConst20 * (((fConst18 * fRec10[0]) + (fConst19 * fRec10[1])) + (fConst18 * fRec10[2]))) - (fConst17 * ((fConst65 * fRec9[1]) + (fConst67 * fRec9[2]))));
			float fTemp36 = (fConst72 * fRec8[1]);
			fRec8[0] = ((fConst17 * (((fConst19 * fRec9[1]) + (fConst18 * fRec9[0])) + (fConst18 * fRec9[2]))) - (fConst70 * (fTemp36 + (fConst73 * fRec8[2]))));
			float fTemp37 = (fConst78 * fRec7[1]);
			fRec7[0] = ((fRec8[2] + (fConst70 * (fTemp36 + (fConst73 * fRec8[0])))) - (fConst76 * (fTemp37 + (fConst79 * fRec7[2]))));
			float fTemp38 = (fConst84 * fRec6[1]);
			fRec6[0] = ((fRec7[2] + (fConst76 * (fTemp37 + (fConst79 * fRec7[0])))) - (fConst82 * (fTemp38 + (fConst85 * fRec6[2]))));
			float fTemp39 = (fConst90 * fRec5[1]);
			fRec5[0] = ((fRec6[2] + (fConst82 * (fTemp38 + (fConst85 * fRec6[0])))) - (fConst88 * (fTemp39 + (fConst91 * fRec5[2]))));
			float fTemp40 = (fConst96 * fRec4[1]);
			fRec4[0] = ((fRec5[2] + (fConst88 * (fTemp39 + (fConst91 * fRec5[0])))) - (fConst94 * (fTemp40 + (fConst97 * fRec4[2]))));
			fRec28[0] = (fSlow16 + (0.999000013f * fRec28[1]));
			fRec38[0] = ((fConst64 * fRec38[1]) + (fConst25 * (fTemp35 + fVec25[1])));
			fRec37[0] = (fRec38[0] - (fConst20 * ((fConst65 * fRec37[1]) + (fConst66 * fRec37[2]))));
			fRec36[0] = ((fConst20 * (fRec37[2] + ((2.0f * fRec37[1]) + fRec37[0]))) - (fConst17 * ((fConst65 * fRec36[1]) + (fConst67 * fRec36[2]))));
			float fTemp41 = (fRec36[2] + ((2.0f * fRec36[1]) + fRec36[0]));
			fVec26[0] = fTemp41;
			fRec35[0] = ((fConst103 * fRec35[1]) + (fConst104 * ((fConst93 * fTemp41) + (fConst105 * fVec26[1]))));
			fRec34[0] = (fRec35[0] - (fConst101 * ((fConst96 * fRec34[1]) + (fConst106 * fRec34[2]))));
			fRec33[0] = ((fConst101 * (((fConst95 * fRec34[0]) + (fConst100 * fRec34[1])) + (fConst95 * fRec34[2]))) - (fConst99 * ((fConst96 * fRec33[1]) + (fConst107 * fRec33[2]))));
			float fTemp42 = (fConst72 * fRec32[1]);
			fRec32[0] = ((fConst99 * (((fConst100 * fRec33[1]) + (fConst95 * fRec33[0])) + (fConst95 * fRec33[2]))) - (fConst70 * (fTemp42 + (fConst73 * fRec32[2]))));
			float fTemp43 = (fConst78 * fRec31[1]);
			fRec31[0] = ((fRec32[2] + (fConst70 * (fTemp42 + (fConst73 * fRec32[0])))) - (fConst76 * (fTemp43 + (fConst79 * fRec31[2]))));
			float fTemp44 = (fConst84 * fRec30[1]);
			fRec30[0] = ((fRec31[2] + (fConst76 * (fTemp43 + (fConst79 * fRec31[0])))) - (fConst82 * (fTemp44 + (fConst85 * fRec30[2]))));
			float fTemp45 = (fConst90 * fRec29[1]);
			fRec29[0] = ((fRec30[2] + (fConst82 * (fTemp44 + (fConst85 * fRec30[0])))) - (fConst88 * (fTemp45 + (fConst91 * fRec29[2]))));
			fRec39[0] = (fSlow17 + (0.999000013f * fRec39[1]));
			fRec48[0] = ((fConst103 * fRec48[1]) + (fConst104 * (fTemp41 + fVec26[1])));
			fRec47[0] = (fRec48[0] - (fConst101 * ((fConst96 * fRec47[1]) + (fConst106 * fRec47[2]))));
			fRec46[0] = ((fConst101 * (fRec47[2] + ((2.0f * fRec47[1]) + fRec47[0]))) - (fConst99 * ((fConst96 * fRec46[1]) + (fConst107 * fRec46[2]))));
			float fTemp46 = (fRec46[2] + ((2.0f * fRec46[1]) + fRec46[0]));
			fVec27[0] = fTemp46;
			fRec45[0] = ((fConst113 * fRec45[1]) + (fConst114 * ((fConst87 * fTemp46) + (fConst115 * fVec27[1]))));
			fRec44[0] = (fRec45[0] - (fConst111 * ((fConst90 * fRec44[1]) + (fConst116 * fRec44[2]))));
			fRec43[0] = ((fConst111 * (((fConst89 * fRec44[0]) + (fConst110 * fRec44[1])) + (fConst89 * fRec44[2]))) - (fConst109 * ((fConst90 * fRec43[1]) + (fConst117 * fRec43[2]))));
			float fTemp47 = (fConst72 * fRec42[1]);
			fRec42[0] = ((fConst109 * (((fConst110 * fRec43[1]) + (fConst89 * fRec43[0])) + (fConst89 * fRec43[2]))) - (fConst70 * (fTemp47 + (fConst73 * fRec42[2]))));
			float fTemp48 = (fConst78 * fRec41[1]);
			fRec41[0] = ((fRec42[2] + (fConst70 * (fTemp47 + (fConst73 * fRec42[0])))) - (fConst76 * (fTemp48 + (fConst79 * fRec41[2]))));
			float fTemp49 = (fConst84 * fRec40[1]);
			fRec40[0] = ((fRec41[2] + (fConst76 * (fTemp48 + (fConst79 * fRec41[0])))) - (fConst82 * (fTemp49 + (fConst85 * fRec40[2]))));
			fRec49[0] = (fSlow18 + (0.999000013f * fRec49[1]));
			fRec57[0] = ((fConst113 * fRec57[1]) + (fConst114 * (fTemp46 + fVec27[1])));
			fRec56[0] = (fRec57[0] - (fConst111 * ((fConst90 * fRec56[1]) + (fConst116 * fRec56[2]))));
			fRec55[0] = ((fConst111 * (fRec56[2] + ((2.0f * fRec56[1]) + fRec56[0]))) - (fConst109 * ((fConst90 * fRec55[1]) + (fConst117 * fRec55[2]))));
			float fTemp50 = (fRec55[2] + ((2.0f * fRec55[1]) + fRec55[0]));
			fVec28[0] = fTemp50;
			fRec54[0] = ((fConst123 * fRec54[1]) + (fConst124 * ((fConst81 * fTemp50) + (fConst125 * fVec28[1]))));
			fRec53[0] = (fRec54[0] - (fConst121 * ((fConst84 * fRec53[1]) + (fConst126 * fRec53[2]))));
			fRec52[0] = ((fConst121 * (((fConst83 * fRec53[0]) + (fConst120 * fRec53[1])) + (fConst83 * fRec53[2]))) - (fConst119 * ((fConst84 * fRec52[1]) + (fConst127 * fRec52[2]))));
			float fTemp51 = (fConst72 * fRec51[1]);
			fRec51[0] = ((fConst119 * (((fConst120 * fRec52[1]) + (fConst83 * fRec52[0])) + (fConst83 * fRec52[2]))) - (fConst70 * (fTemp51 + (fConst73 * fRec51[2]))));
			float fTemp52 = (fConst78 * fRec50[1]);
			fRec50[0] = ((fRec51[2] + (fConst70 * (fTemp51 + (fConst73 * fRec51[0])))) - (fConst76 * (fTemp52 + (fConst79 * fRec50[2]))));
			fRec58[0] = (fSlow19 + (0.999000013f * fRec58[1]));
			fRec65[0] = ((fConst123 * fRec65[1]) + (fConst124 * (fTemp50 + fVec28[1])));
			fRec64[0] = (fRec65[0] - (fConst121 * ((fConst84 * fRec64[1]) + (fConst126 * fRec64[2]))));
			fRec63[0] = ((fConst121 * (fRec64[2] + ((2.0f * fRec64[1]) + fRec64[0]))) - (fConst119 * ((fConst84 * fRec63[1]) + (fConst127 * fRec63[2]))));
			float fTemp53 = (fRec63[2] + ((2.0f * fRec63[1]) + fRec63[0]));
			fVec29[0] = fTemp53;
			fRec62[0] = ((fConst133 * fRec62[1]) + (fConst134 * ((fConst75 * fTemp53) + (fConst135 * fVec29[1]))));
			fRec61[0] = (fRec62[0] - (fConst131 * ((fConst78 * fRec61[1]) + (fConst136 * fRec61[2]))));
			fRec60[0] = ((fConst131 * (((fConst130 * fRec61[1]) + (fConst77 * fRec61[0])) + (fConst77 * fRec61[2]))) - (fConst129 * ((fConst78 * fRec60[1]) + (fConst137 * fRec60[2]))));
			float fTemp54 = (fConst72 * fRec59[1]);
			fRec59[0] = ((fConst129 * (((fConst130 * fRec60[1]) + (fConst77 * fRec60[0])) + (fConst77 * fRec60[2]))) - (fConst70 * (fTemp54 + (fConst73 * fRec59[2]))));
			fRec66[0] = (fSlow20 + (0.999000013f * fRec66[1]));
			fRec72[0] = ((fConst133 * fRec72[1]) + (fConst134 * (fTemp53 + fVec29[1])));
			fRec71[0] = (fRec72[0] - (fConst131 * ((fConst78 * fRec71[1]) + (fConst136 * fRec71[2]))));
			fRec70[0] = ((fConst131 * (fRec71[2] + ((2.0f * fRec71[1]) + fRec71[0]))) - (fConst129 * ((fConst78 * fRec70[1]) + (fConst137 * fRec70[2]))));
			float fTemp55 = (fRec70[2] + ((2.0f * fRec70[1]) + fRec70[0]));
			fVec30[0] = fTemp55;
			fRec69[0] = ((fConst142 * fRec69[1]) + (fConst143 * ((fConst69 * fTemp55) + (fConst144 * fVec30[1]))));
			fRec68[0] = (fRec69[0] - (fConst140 * ((fConst72 * fRec68[1]) + (fConst145 * fRec68[2]))));
			fRec67[0] = ((fConst140 * (((fConst139 * fRec68[1]) + (fConst71 * fRec68[0])) + (fConst71 * fRec68[2]))) - (fConst138 * ((fConst72 * fRec67[1]) + (fConst146 * fRec67[2]))));
			fRec73[0] = (fSlow21 + (0.999000013f * fRec73[1]));
			fRec76[0] = ((fConst142 * fRec76[1]) + (fConst143 * (fTemp55 + fVec30[1])));
			fRec75[0] = (fRec76[0] - (fConst140 * ((fConst72 * fRec75[1]) + (fConst145 * fRec75[2]))));
			fRec74[0] = ((fConst140 * (fRec75[2] + ((2.0f * fRec75[1]) + fRec75[0]))) - (fConst138 * ((fConst72 * fRec74[1]) + (fConst146 * fRec74[2]))));
			fRec77[0] = (fSlow22 + (0.999000013f * fRec77[1]));
			fRec88[0] = ((fConst42 * fRec88[1]) + (fConst43 * ((fConst37 * fTemp32) + (fConst148 * fVec22[1]))));
			fRec87[0] = (fRec88[0] - (fConst40 * ((fConst49 * fRec87[1]) + (fConst50 * fRec87[2]))));
			fRec86[0] = ((fConst40 * (((fConst147 * fRec87[1]) + (fConst48 * fRec87[0])) + (fConst48 * fRec87[2]))) - (fConst51 * ((fConst49 * fRec86[1]) + (fConst52 * fRec86[2]))));
			float fTemp56 = (fConst72 * fRec85[1]);
			fRec85[0] = ((fConst51 * (((fConst147 * fRec86[1]) + (fConst48 * fRec86[0])) + (fConst48 * fRec86[2]))) - (fConst70 * ((fConst73 * fRec85[2]) + fTemp56)));
			float fTemp57 = (fConst78 * fRec84[1]);
			fRec84[0] = ((fRec85[2] + (fConst70 * (fTemp56 + (fConst73 * fRec85[0])))) - (fConst76 * ((fConst79 * fRec84[2]) + fTemp57)));
			float fTemp58 = (fConst84 * fRec83[1]);
			fRec83[0] = ((fRec84[2] + (fConst76 * (fTemp57 + (fConst79 * fRec84[0])))) - (fConst82 * ((fConst85 * fRec83[2]) + fTemp58)));
			float fTemp59 = (fConst90 * fRec82[1]);
			fRec82[0] = ((fRec83[2] + (fConst82 * (fTemp58 + (fConst85 * fRec83[0])))) - (fConst88 * ((fConst91 * fRec82[2]) + fTemp59)));
			float fTemp60 = (fConst96 * fRec81[1]);
			fRec81[0] = ((fRec82[2] + (fConst88 * (fTemp59 + (fConst91 * fRec82[0])))) - (fConst94 * ((fConst97 * fRec81[2]) + fTemp60)));
			float fTemp61 = (fConst65 * fRec80[1]);
			fRec80[0] = ((fRec81[2] + (fConst94 * (fTemp60 + (fConst97 * fRec81[0])))) - (fConst149 * ((fConst150 * fRec80[2]) + fTemp61)));
			float fTemp62 = (fConst59 * fRec79[1]);
			fRec79[0] = ((fRec80[2] + (fConst149 * (fTemp61 + (fConst150 * fRec80[0])))) - (fConst151 * ((fConst152 * fRec79[2]) + fTemp62)));
			float fTemp63 = (fConst54 * fRec78[1]);
			fRec78[0] = ((fRec79[2] + (fConst151 * (fTemp62 + (fConst152 * fRec79[0])))) - (fConst153 * ((fConst154 * fRec78[2]) + fTemp63)));
			fRec89[0] = (fSlow23 + (0.999000013f * fRec89[1]));
			fRec99[0] = ((fConst35 * fRec99[1]) + (fConst39 * ((fConst30 * fTemp33) + (fConst156 * fVec23[1]))));
			fRec98[0] = (fRec99[0] - (fConst33 * ((fConst54 * fRec98[1]) + (fConst55 * fRec98[2]))));
			fRec97[0] = ((fConst33 * (((fConst53 * fRec98[0]) + (fConst155 * fRec98[1])) + (fConst53 * fRec98[2]))) - (fConst56 * ((fConst54 * fRec97[1]) + (fConst57 * fRec97[2]))));
			float fTemp64 = (fConst72 * fRec96[1]);
			fRec96[0] = ((fConst56 * (((fConst155 * fRec97[1]) + (fConst53 * fRec97[0])) + (fConst53 * fRec97[2]))) - (fConst70 * (fTemp64 + (fConst73 * fRec96[2]))));
			float fTemp65 = (fConst78 * fRec95[1]);
			fRec95[0] = ((fRec96[2] + (fConst70 * (fTemp64 + (fConst73 * fRec96[0])))) - (fConst76 * (fTemp65 + (fConst79 * fRec95[2]))));
			float fTemp66 = (fConst84 * fRec94[1]);
			fRec94[0] = ((fRec95[2] + (fConst76 * (fTemp65 + (fConst79 * fRec95[0])))) - (fConst82 * (fTemp66 + (fConst85 * fRec94[2]))));
			float fTemp67 = (fConst90 * fRec93[1]);
			fRec93[0] = ((fRec94[2] + (fConst82 * (fTemp66 + (fConst85 * fRec94[0])))) - (fConst88 * (fTemp67 + (fConst91 * fRec93[2]))));
			float fTemp68 = (fConst96 * fRec92[1]);
			fRec92[0] = ((fRec93[2] + (fConst88 * (fTemp67 + (fConst91 * fRec93[0])))) - (fConst94 * (fTemp68 + (fConst97 * fRec92[2]))));
			float fTemp69 = (fConst65 * fRec91[1]);
			fRec91[0] = ((fRec92[2] + (fConst94 * (fTemp68 + (fConst97 * fRec92[0])))) - (fConst149 * (fTemp69 + (fConst150 * fRec91[2]))));
			float fTemp70 = (fConst59 * fRec90[1]);
			fRec90[0] = ((fRec91[2] + (fConst149 * (fTemp69 + (fConst150 * fRec91[0])))) - (fConst151 * (fTemp70 + (fConst152 * fRec90[2]))));
			fRec100[0] = (fSlow24 + (0.999000013f * fRec100[1]));
			fRec109[0] = ((fConst28 * fRec109[1]) + (fConst32 * ((fConst22 * fTemp34) + (fConst158 * fVec24[1]))));
			fRec108[0] = (fRec109[0] - (fConst26 * ((fConst59 * fRec108[1]) + (fConst60 * fRec108[2]))));
			fRec107[0] = ((fConst26 * (((fConst58 * fRec108[0]) + (fConst157 * fRec108[1])) + (fConst58 * fRec108[2]))) - (fConst61 * ((fConst59 * fRec107[1]) + (fConst62 * fRec107[2]))));
			float fTemp71 = (fConst72 * fRec106[1]);
			fRec106[0] = ((fConst61 * (((fConst157 * fRec107[1]) + (fConst58 * fRec107[0])) + (fConst58 * fRec107[2]))) - (fConst70 * (fTemp71 + (fConst73 * fRec106[2]))));
			float fTemp72 = (fConst78 * fRec105[1]);
			fRec105[0] = ((fRec106[2] + (fConst70 * (fTemp71 + (fConst73 * fRec106[0])))) - (fConst76 * (fTemp72 + (fConst79 * fRec105[2]))));
			float fTemp73 = (fConst84 * fRec104[1]);
			fRec104[0] = ((fRec105[2] + (fConst76 * (fTemp72 + (fConst79 * fRec105[0])))) - (fConst82 * (fTemp73 + (fConst85 * fRec104[2]))));
			float fTemp74 = (fConst90 * fRec103[1]);
			fRec103[0] = ((fRec104[2] + (fConst82 * (fTemp73 + (fConst85 * fRec104[0])))) - (fConst88 * (fTemp74 + (fConst91 * fRec103[2]))));
			float fTemp75 = (fConst96 * fRec102[1]);
			fRec102[0] = ((fRec103[2] + (fConst88 * (fTemp74 + (fConst91 * fRec103[0])))) - (fConst94 * (fTemp75 + (fConst97 * fRec102[2]))));
			float fTemp76 = (fConst65 * fRec101[1]);
			fRec101[0] = ((fRec102[2] + (fConst94 * (fTemp75 + (fConst97 * fRec102[0])))) - (fConst149 * (fTemp76 + (fConst150 * fRec101[2]))));
			fRec110[0] = (fSlow25 + (0.999000013f * fRec110[1]));
			float fTemp77 = (((iSlow3==0)?true:false)?fTemp31:((((((((((fRec4[2] + (fConst94 * (fTemp40 + (fConst97 * fRec4[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec28[0]))) + ((fRec29[2] + (fConst88 * (fTemp45 + (fConst91 * fRec29[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec39[0])))) + ((fRec40[2] + (fConst82 * (fTemp49 + (fConst85 * fRec40[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec49[0])))) + ((fRec50[2] + (fConst76 * (fTemp52 + (fConst79 * fRec50[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec58[0])))) + ((fRec59[2] + (fConst70 * (fTemp54 + (fConst73 * fRec59[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec66[0])))) + (fConst138 * (((((fConst139 * fRec67[1]) + (fConst71 * fRec67[0])) + (fConst71 * fRec67[2])) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec73[0]))) + ((fRec74[2] + ((2.0f * fRec74[1]) + fRec74[0])) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec77[0])))))) + ((fRec78[2] + (fConst153 * (fTemp63 + (fConst154 * fRec78[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec89[0])))) + ((fRec90[2] + (fConst151 * (fTemp70 + (fConst152 * fRec90[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec100[0])))) + ((fRec101[2] + (fConst149 * (fTemp76 + (fConst150 * fRec101[0])))) * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fRec110[0])))));
			fRec3[0] = (fTemp77 - (fConst11 * ((fConst159 * fRec3[2]) + (fConst161 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst162 * fRec3[0])) + (fConst162 * fRec3[2]))) - (fConst8 * ((fConst163 * fRec2[2]) + (fConst164 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst165 * fRec2[0])) + (fConst165 * fRec2[2]))) - (fConst4 * ((fConst166 * fRec1[2]) + (fConst167 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst4 * (((fConst7 * fRec1[1]) + (fConst168 * fRec1[0])) + (fConst168 * fRec1[2]))))));
			fVbargraph0 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec0[0]))));
			fRec117[0] = (fTemp77 - (fConst185 * ((fConst188 * fRec117[2]) + (fConst189 * fRec117[1]))));
			fRec116[0] = ((fConst185 * (((fConst187 * fRec117[1]) + (fConst190 * fRec117[0])) + (fConst190 * fRec117[2]))) - (fConst183 * ((fConst191 * fRec116[2]) + (fConst192 * fRec116[1]))));
			fRec115[0] = ((fConst183 * (((fConst184 * fRec116[1]) + (fConst193 * fRec116[0])) + (fConst193 * fRec116[2]))) - (fConst181 * ((fConst194 * fRec115[2]) + (fConst195 * fRec115[1]))));
			float fTemp78 = (fConst181 * (((fConst182 * fRec115[1]) + (fConst196 * fRec115[0])) + (fConst196 * fRec115[2])));
			fRec114[0] = (fTemp78 - (fConst178 * ((fConst197 * fRec114[2]) + (fConst199 * fRec114[1]))));
			fRec113[0] = ((fConst178 * (((fConst180 * fRec114[1]) + (fConst200 * fRec114[0])) + (fConst200 * fRec114[2]))) - (fConst175 * ((fConst201 * fRec113[2]) + (fConst202 * fRec113[1]))));
			fRec112[0] = ((fConst175 * (((fConst177 * fRec113[1]) + (fConst203 * fRec113[0])) + (fConst203 * fRec113[2]))) - (fConst171 * ((fConst204 * fRec112[2]) + (fConst205 * fRec112[1]))));
			fRec111[0] = ((fSlow1 * fRec111[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst171 * (((fConst174 * fRec112[1]) + (fConst206 * fRec112[0])) + (fConst206 * fRec112[2]))))));
			fVbargraph1 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec111[0]))));
			fRec124[0] = (fTemp78 - (fConst223 * ((fConst226 * fRec124[2]) + (fConst227 * fRec124[1]))));
			fRec123[0] = ((fConst223 * (((fConst225 * fRec124[1]) + (fConst228 * fRec124[0])) + (fConst228 * fRec124[2]))) - (fConst221 * ((fConst229 * fRec123[2]) + (fConst230 * fRec123[1]))));
			fRec122[0] = ((fConst221 * (((fConst222 * fRec123[1]) + (fConst231 * fRec123[0])) + (fConst231 * fRec123[2]))) - (fConst219 * ((fConst232 * fRec122[2]) + (fConst233 * fRec122[1]))));
			float fTemp79 = (fConst219 * (((fConst220 * fRec122[1]) + (fConst234 * fRec122[0])) + (fConst234 * fRec122[2])));
			fRec121[0] = (fTemp79 - (fConst216 * ((fConst235 * fRec121[2]) + (fConst237 * fRec121[1]))));
			fRec120[0] = ((fConst216 * (((fConst218 * fRec121[1]) + (fConst238 * fRec121[0])) + (fConst238 * fRec121[2]))) - (fConst213 * ((fConst239 * fRec120[2]) + (fConst240 * fRec120[1]))));
			fRec119[0] = ((fConst213 * (((fConst215 * fRec120[1]) + (fConst241 * fRec120[0])) + (fConst241 * fRec120[2]))) - (fConst209 * ((fConst242 * fRec119[2]) + (fConst243 * fRec119[1]))));
			fRec118[0] = ((fSlow1 * fRec118[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst209 * (((fConst212 * fRec119[1]) + (fConst244 * fRec119[0])) + (fConst244 * fRec119[2]))))));
			fVbargraph2 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec118[0]))));
			fRec131[0] = (fTemp79 - (fConst261 * ((fConst264 * fRec131[2]) + (fConst265 * fRec131[1]))));
			fRec130[0] = ((fConst261 * (((fConst263 * fRec131[1]) + (fConst266 * fRec131[0])) + (fConst266 * fRec131[2]))) - (fConst259 * ((fConst267 * fRec130[2]) + (fConst268 * fRec130[1]))));
			fRec129[0] = ((fConst259 * (((fConst260 * fRec130[1]) + (fConst269 * fRec130[0])) + (fConst269 * fRec130[2]))) - (fConst257 * ((fConst270 * fRec129[2]) + (fConst271 * fRec129[1]))));
			float fTemp80 = (fConst257 * (((fConst258 * fRec129[1]) + (fConst272 * fRec129[0])) + (fConst272 * fRec129[2])));
			fRec128[0] = (fTemp80 - (fConst254 * ((fConst273 * fRec128[2]) + (fConst275 * fRec128[1]))));
			fRec127[0] = ((fConst254 * (((fConst256 * fRec128[1]) + (fConst276 * fRec128[0])) + (fConst276 * fRec128[2]))) - (fConst251 * ((fConst277 * fRec127[2]) + (fConst278 * fRec127[1]))));
			fRec126[0] = ((fConst251 * (((fConst253 * fRec127[1]) + (fConst279 * fRec127[0])) + (fConst279 * fRec127[2]))) - (fConst247 * ((fConst280 * fRec126[2]) + (fConst281 * fRec126[1]))));
			fRec125[0] = ((fSlow1 * fRec125[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst247 * (((fConst250 * fRec126[1]) + (fConst282 * fRec126[0])) + (fConst282 * fRec126[2]))))));
			fVbargraph3 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec125[0]))));
			fRec138[0] = (fTemp80 - (fConst299 * ((fConst302 * fRec138[2]) + (fConst303 * fRec138[1]))));
			fRec137[0] = ((fConst299 * (((fConst301 * fRec138[1]) + (fConst304 * fRec138[0])) + (fConst304 * fRec138[2]))) - (fConst297 * ((fConst305 * fRec137[2]) + (fConst306 * fRec137[1]))));
			fRec136[0] = ((fConst297 * (((fConst298 * fRec137[1]) + (fConst307 * fRec137[0])) + (fConst307 * fRec137[2]))) - (fConst295 * ((fConst308 * fRec136[2]) + (fConst309 * fRec136[1]))));
			float fTemp81 = (fConst295 * (((fConst296 * fRec136[1]) + (fConst310 * fRec136[0])) + (fConst310 * fRec136[2])));
			fRec135[0] = (fTemp81 - (fConst292 * ((fConst311 * fRec135[2]) + (fConst313 * fRec135[1]))));
			fRec134[0] = ((fConst292 * (((fConst294 * fRec135[1]) + (fConst314 * fRec135[0])) + (fConst314 * fRec135[2]))) - (fConst289 * ((fConst315 * fRec134[2]) + (fConst316 * fRec134[1]))));
			fRec133[0] = ((fConst289 * (((fConst291 * fRec134[1]) + (fConst317 * fRec134[0])) + (fConst317 * fRec134[2]))) - (fConst285 * ((fConst318 * fRec133[2]) + (fConst319 * fRec133[1]))));
			fRec132[0] = ((fSlow1 * fRec132[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst285 * (((fConst288 * fRec133[1]) + (fConst320 * fRec133[0])) + (fConst320 * fRec133[2]))))));
			fVbargraph4 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec132[0]))));
			fRec145[0] = (fTemp81 - (fConst337 * ((fConst340 * fRec145[2]) + (fConst341 * fRec145[1]))));
			fRec144[0] = ((fConst337 * (((fConst339 * fRec145[1]) + (fConst342 * fRec145[0])) + (fConst342 * fRec145[2]))) - (fConst335 * ((fConst343 * fRec144[2]) + (fConst344 * fRec144[1]))));
			fRec143[0] = ((fConst335 * (((fConst336 * fRec144[1]) + (fConst345 * fRec144[0])) + (fConst345 * fRec144[2]))) - (fConst333 * ((fConst346 * fRec143[2]) + (fConst347 * fRec143[1]))));
			float fTemp82 = (fConst333 * (((fConst334 * fRec143[1]) + (fConst348 * fRec143[0])) + (fConst348 * fRec143[2])));
			fRec142[0] = (fTemp82 - (fConst330 * ((fConst349 * fRec142[2]) + (fConst351 * fRec142[1]))));
			fRec141[0] = ((fConst330 * (((fConst332 * fRec142[1]) + (fConst352 * fRec142[0])) + (fConst352 * fRec142[2]))) - (fConst327 * ((fConst353 * fRec141[2]) + (fConst354 * fRec141[1]))));
			fRec140[0] = ((fConst327 * (((fConst329 * fRec141[1]) + (fConst355 * fRec141[0])) + (fConst355 * fRec141[2]))) - (fConst323 * ((fConst356 * fRec140[2]) + (fConst357 * fRec140[1]))));
			fRec139[0] = ((fSlow1 * fRec139[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst323 * (((fConst326 * fRec140[1]) + (fConst358 * fRec140[0])) + (fConst358 * fRec140[2]))))));
			fVbargraph5 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec139[0]))));
			fRec152[0] = (fTemp82 - (fConst375 * ((fConst378 * fRec152[2]) + (fConst379 * fRec152[1]))));
			fRec151[0] = ((fConst375 * (((fConst377 * fRec152[1]) + (fConst380 * fRec152[0])) + (fConst380 * fRec152[2]))) - (fConst373 * ((fConst381 * fRec151[2]) + (fConst382 * fRec151[1]))));
			fRec150[0] = ((fConst373 * (((fConst374 * fRec151[1]) + (fConst383 * fRec151[0])) + (fConst383 * fRec151[2]))) - (fConst371 * ((fConst384 * fRec150[2]) + (fConst385 * fRec150[1]))));
			float fTemp83 = (fConst371 * (((fConst372 * fRec150[1]) + (fConst386 * fRec150[0])) + (fConst386 * fRec150[2])));
			fRec149[0] = (fTemp83 - (fConst368 * ((fConst387 * fRec149[2]) + (fConst389 * fRec149[1]))));
			fRec148[0] = ((fConst368 * (((fConst370 * fRec149[1]) + (fConst390 * fRec149[0])) + (fConst390 * fRec149[2]))) - (fConst365 * ((fConst391 * fRec148[2]) + (fConst392 * fRec148[1]))));
			fRec147[0] = ((fConst365 * (((fConst367 * fRec148[1]) + (fConst393 * fRec148[0])) + (fConst393 * fRec148[2]))) - (fConst361 * ((fConst394 * fRec147[2]) + (fConst395 * fRec147[1]))));
			fRec146[0] = ((fSlow1 * fRec146[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst361 * (((fConst364 * fRec147[1]) + (fConst396 * fRec147[0])) + (fConst396 * fRec147[2]))))));
			fVbargraph6 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec146[0]))));
			fRec159[0] = (fTemp83 - (fConst413 * ((fConst416 * fRec159[2]) + (fConst417 * fRec159[1]))));
			fRec158[0] = ((fConst413 * (((fConst415 * fRec159[1]) + (fConst418 * fRec159[0])) + (fConst418 * fRec159[2]))) - (fConst411 * ((fConst419 * fRec158[2]) + (fConst420 * fRec158[1]))));
			fRec157[0] = ((fConst411 * (((fConst412 * fRec158[1]) + (fConst421 * fRec158[0])) + (fConst421 * fRec158[2]))) - (fConst409 * ((fConst422 * fRec157[2]) + (fConst423 * fRec157[1]))));
			float fTemp84 = (fConst409 * (((fConst410 * fRec157[1]) + (fConst424 * fRec157[0])) + (fConst424 * fRec157[2])));
			fRec156[0] = (fTemp84 - (fConst406 * ((fConst425 * fRec156[2]) + (fConst427 * fRec156[1]))));
			fRec155[0] = ((fConst406 * (((fConst408 * fRec156[1]) + (fConst428 * fRec156[0])) + (fConst428 * fRec156[2]))) - (fConst403 * ((fConst429 * fRec155[2]) + (fConst430 * fRec155[1]))));
			fRec154[0] = ((fConst403 * (((fConst405 * fRec155[1]) + (fConst431 * fRec155[0])) + (fConst431 * fRec155[2]))) - (fConst399 * ((fConst432 * fRec154[2]) + (fConst433 * fRec154[1]))));
			fRec153[0] = ((fSlow1 * fRec153[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst399 * (((fConst402 * fRec154[1]) + (fConst434 * fRec154[0])) + (fConst434 * fRec154[2]))))));
			fVbargraph7 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec153[0]))));
			fRec166[0] = (fTemp84 - (fConst451 * ((fConst454 * fRec166[2]) + (fConst455 * fRec166[1]))));
			fRec165[0] = ((fConst451 * (((fConst453 * fRec166[1]) + (fConst456 * fRec166[0])) + (fConst456 * fRec166[2]))) - (fConst449 * ((fConst457 * fRec165[2]) + (fConst458 * fRec165[1]))));
			fRec164[0] = ((fConst449 * (((fConst450 * fRec165[1]) + (fConst459 * fRec165[0])) + (fConst459 * fRec165[2]))) - (fConst447 * ((fConst460 * fRec164[2]) + (fConst461 * fRec164[1]))));
			float fTemp85 = (fConst447 * (((fConst448 * fRec164[1]) + (fConst462 * fRec164[0])) + (fConst462 * fRec164[2])));
			fRec163[0] = (fTemp85 - (fConst444 * ((fConst463 * fRec163[2]) + (fConst465 * fRec163[1]))));
			fRec162[0] = ((fConst444 * (((fConst446 * fRec163[1]) + (fConst466 * fRec163[0])) + (fConst466 * fRec163[2]))) - (fConst441 * ((fConst467 * fRec162[2]) + (fConst468 * fRec162[1]))));
			fRec161[0] = ((fConst441 * (((fConst443 * fRec162[1]) + (fConst469 * fRec162[0])) + (fConst469 * fRec162[2]))) - (fConst437 * ((fConst470 * fRec161[2]) + (fConst471 * fRec161[1]))));
			fRec160[0] = ((fSlow1 * fRec160[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst437 * (((fConst440 * fRec161[1]) + (fConst472 * fRec161[0])) + (fConst472 * fRec161[2]))))));
			fVbargraph8 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec160[0]))));
			fRec173[0] = (fTemp85 - (fConst489 * ((fConst492 * fRec173[2]) + (fConst493 * fRec173[1]))));
			fRec172[0] = ((fConst489 * (((fConst491 * fRec173[1]) + (fConst494 * fRec173[0])) + (fConst494 * fRec173[2]))) - (fConst487 * ((fConst495 * fRec172[2]) + (fConst496 * fRec172[1]))));
			fRec171[0] = ((fConst487 * (((fConst488 * fRec172[1]) + (fConst497 * fRec172[0])) + (fConst497 * fRec172[2]))) - (fConst485 * ((fConst498 * fRec171[2]) + (fConst499 * fRec171[1]))));
			float fTemp86 = (fConst485 * (((fConst486 * fRec171[1]) + (fConst500 * fRec171[0])) + (fConst500 * fRec171[2])));
			fRec170[0] = (fTemp86 - (fConst482 * ((fConst501 * fRec170[2]) + (fConst503 * fRec170[1]))));
			fRec169[0] = ((fConst482 * (((fConst484 * fRec170[1]) + (fConst504 * fRec170[0])) + (fConst504 * fRec170[2]))) - (fConst479 * ((fConst505 * fRec169[2]) + (fConst506 * fRec169[1]))));
			fRec168[0] = ((fConst479 * (((fConst481 * fRec169[1]) + (fConst507 * fRec169[0])) + (fConst507 * fRec169[2]))) - (fConst475 * ((fConst508 * fRec168[2]) + (fConst509 * fRec168[1]))));
			fRec167[0] = ((fSlow1 * fRec167[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst475 * (((fConst478 * fRec168[1]) + (fConst510 * fRec168[0])) + (fConst510 * fRec168[2]))))));
			fVbargraph9 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec167[0]))));
			fRec180[0] = (fTemp86 - (fConst527 * ((fConst530 * fRec180[2]) + (fConst531 * fRec180[1]))));
			fRec179[0] = ((fConst527 * (((fConst529 * fRec180[1]) + (fConst532 * fRec180[0])) + (fConst532 * fRec180[2]))) - (fConst525 * ((fConst533 * fRec179[2]) + (fConst534 * fRec179[1]))));
			fRec178[0] = ((fConst525 * (((fConst526 * fRec179[1]) + (fConst535 * fRec179[0])) + (fConst535 * fRec179[2]))) - (fConst523 * ((fConst536 * fRec178[2]) + (fConst537 * fRec178[1]))));
			float fTemp87 = (fConst523 * (((fConst524 * fRec178[1]) + (fConst538 * fRec178[0])) + (fConst538 * fRec178[2])));
			fRec177[0] = (fTemp87 - (fConst520 * ((fConst539 * fRec177[2]) + (fConst541 * fRec177[1]))));
			fRec176[0] = ((fConst520 * (((fConst522 * fRec177[1]) + (fConst542 * fRec177[0])) + (fConst542 * fRec177[2]))) - (fConst517 * ((fConst543 * fRec176[2]) + (fConst544 * fRec176[1]))));
			fRec175[0] = ((fConst517 * (((fConst519 * fRec176[1]) + (fConst545 * fRec176[0])) + (fConst545 * fRec176[2]))) - (fConst513 * ((fConst546 * fRec175[2]) + (fConst547 * fRec175[1]))));
			fRec174[0] = ((fSlow1 * fRec174[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst513 * (((fConst516 * fRec175[1]) + (fConst548 * fRec175[0])) + (fConst548 * fRec175[2]))))));
			fVbargraph10 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec174[0]))));
			fRec187[0] = (fTemp87 - (fConst565 * ((fConst568 * fRec187[2]) + (fConst569 * fRec187[1]))));
			fRec186[0] = ((fConst565 * (((fConst567 * fRec187[1]) + (fConst570 * fRec187[0])) + (fConst570 * fRec187[2]))) - (fConst563 * ((fConst571 * fRec186[2]) + (fConst572 * fRec186[1]))));
			fRec185[0] = ((fConst563 * (((fConst564 * fRec186[1]) + (fConst573 * fRec186[0])) + (fConst573 * fRec186[2]))) - (fConst561 * ((fConst574 * fRec185[2]) + (fConst575 * fRec185[1]))));
			float fTemp88 = (fConst561 * (((fConst562 * fRec185[1]) + (fConst576 * fRec185[0])) + (fConst576 * fRec185[2])));
			fRec184[0] = (fTemp88 - (fConst558 * ((fConst577 * fRec184[2]) + (fConst579 * fRec184[1]))));
			fRec183[0] = ((fConst558 * (((fConst560 * fRec184[1]) + (fConst580 * fRec184[0])) + (fConst580 * fRec184[2]))) - (fConst555 * ((fConst581 * fRec183[2]) + (fConst582 * fRec183[1]))));
			fRec182[0] = ((fConst555 * (((fConst557 * fRec183[1]) + (fConst583 * fRec183[0])) + (fConst583 * fRec183[2]))) - (fConst551 * ((fConst584 * fRec182[2]) + (fConst585 * fRec182[1]))));
			fRec181[0] = ((fSlow1 * fRec181[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst551 * (((fConst554 * fRec182[1]) + (fConst586 * fRec182[0])) + (fConst586 * fRec182[2]))))));
			fVbargraph11 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec181[0]))));
			fRec194[0] = (fTemp88 - (fConst603 * ((fConst606 * fRec194[2]) + (fConst607 * fRec194[1]))));
			fRec193[0] = ((fConst603 * (((fConst605 * fRec194[1]) + (fConst608 * fRec194[0])) + (fConst608 * fRec194[2]))) - (fConst601 * ((fConst609 * fRec193[2]) + (fConst610 * fRec193[1]))));
			fRec192[0] = ((fConst601 * (((fConst602 * fRec193[1]) + (fConst611 * fRec193[0])) + (fConst611 * fRec193[2]))) - (fConst599 * ((fConst612 * fRec192[2]) + (fConst613 * fRec192[1]))));
			float fTemp89 = (fConst599 * (((fConst600 * fRec192[1]) + (fConst614 * fRec192[0])) + (fConst614 * fRec192[2])));
			fRec191[0] = (fTemp89 - (fConst596 * ((fConst615 * fRec191[2]) + (fConst617 * fRec191[1]))));
			fRec190[0] = ((fConst596 * (((fConst598 * fRec191[1]) + (fConst618 * fRec191[0])) + (fConst618 * fRec191[2]))) - (fConst593 * ((fConst619 * fRec190[2]) + (fConst620 * fRec190[1]))));
			fRec189[0] = ((fConst593 * (((fConst595 * fRec190[1]) + (fConst621 * fRec190[0])) + (fConst621 * fRec190[2]))) - (fConst589 * ((fConst622 * fRec189[2]) + (fConst623 * fRec189[1]))));
			fRec188[0] = ((fSlow1 * fRec188[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst589 * (((fConst592 * fRec189[1]) + (fConst624 * fRec189[0])) + (fConst624 * fRec189[2]))))));
			fVbargraph12 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec188[0]))));
			fRec201[0] = (fTemp89 - (fConst641 * ((fConst644 * fRec201[2]) + (fConst645 * fRec201[1]))));
			fRec200[0] = ((fConst641 * (((fConst643 * fRec201[1]) + (fConst646 * fRec201[0])) + (fConst646 * fRec201[2]))) - (fConst639 * ((fConst647 * fRec200[2]) + (fConst648 * fRec200[1]))));
			fRec199[0] = ((fConst639 * (((fConst640 * fRec200[1]) + (fConst649 * fRec200[0])) + (fConst649 * fRec200[2]))) - (fConst637 * ((fConst650 * fRec199[2]) + (fConst651 * fRec199[1]))));
			float fTemp90 = (fConst637 * (((fConst638 * fRec199[1]) + (fConst652 * fRec199[0])) + (fConst652 * fRec199[2])));
			fRec198[0] = (fTemp90 - (fConst634 * ((fConst653 * fRec198[2]) + (fConst655 * fRec198[1]))));
			fRec197[0] = ((fConst634 * (((fConst636 * fRec198[1]) + (fConst656 * fRec198[0])) + (fConst656 * fRec198[2]))) - (fConst631 * ((fConst657 * fRec197[2]) + (fConst658 * fRec197[1]))));
			fRec196[0] = ((fConst631 * (((fConst633 * fRec197[1]) + (fConst659 * fRec197[0])) + (fConst659 * fRec197[2]))) - (fConst627 * ((fConst660 * fRec196[2]) + (fConst661 * fRec196[1]))));
			fRec195[0] = ((fSlow1 * fRec195[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst627 * (((fConst630 * fRec196[1]) + (fConst662 * fRec196[0])) + (fConst662 * fRec196[2]))))));
			fVbargraph13 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec195[0]))));
			fRec205[0] = (fTemp90 - (fConst667 * ((fConst670 * fRec205[2]) + (fConst671 * fRec205[1]))));
			fRec204[0] = ((fConst667 * (((fConst669 * fRec205[1]) + (fConst672 * fRec205[0])) + (fConst672 * fRec205[2]))) - (fConst665 * ((fConst673 * fRec204[2]) + (fConst674 * fRec204[1]))));
			fRec203[0] = ((fConst665 * (((fConst666 * fRec204[1]) + (fConst675 * fRec204[0])) + (fConst675 * fRec204[2]))) - (fConst663 * ((fConst676 * fRec203[2]) + (fConst677 * fRec203[1]))));
			fRec202[0] = ((fSlow1 * fRec202[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst663 * (((fConst664 * fRec203[1]) + (fConst678 * fRec203[0])) + (fConst678 * fRec203[2]))))));
			fVbargraph14 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec202[0]))));
			output0[i] = fTemp77;
			output1[i] = fTemp77;
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fVec1[1] = fVec1[0];
			fRec22[1] = fRec22[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec24[1] = fRec24[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec25[1] = fRec25[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			iRec26[1] = iRec26[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec27[j1] = fRec27[(j1 - 1)];
				
			}
			fVec22[1] = fVec22[0];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fVec23[1] = fVec23[0];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fVec24[1] = fVec24[0];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fVec25[1] = fVec25[0];
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
			fRec28[1] = fRec28[0];
			fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fVec26[1] = fVec26[0];
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
			fRec39[1] = fRec39[0];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fVec27[1] = fVec27[0];
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
			fRec49[1] = fRec49[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fVec28[1] = fVec28[0];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec58[1] = fRec58[0];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fVec29[1] = fVec29[0];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec66[1] = fRec66[0];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fVec30[1] = fVec30[0];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec73[1] = fRec73[0];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec77[1] = fRec77[0];
			fRec88[1] = fRec88[0];
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
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec89[1] = fRec89[0];
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
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec100[1] = fRec100[0];
			fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
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
			fRec110[1] = fRec110[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
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
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1];
			fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			fRec127[2] = fRec127[1];
			fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec125[1] = fRec125[0];
			fRec138[2] = fRec138[1];
			fRec138[1] = fRec138[0];
			fRec137[2] = fRec137[1];
			fRec137[1] = fRec137[0];
			fRec136[2] = fRec136[1];
			fRec136[1] = fRec136[0];
			fRec135[2] = fRec135[1];
			fRec135[1] = fRec135[0];
			fRec134[2] = fRec134[1];
			fRec134[1] = fRec134[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec132[1] = fRec132[0];
			fRec145[2] = fRec145[1];
			fRec145[1] = fRec145[0];
			fRec144[2] = fRec144[1];
			fRec144[1] = fRec144[0];
			fRec143[2] = fRec143[1];
			fRec143[1] = fRec143[0];
			fRec142[2] = fRec142[1];
			fRec142[1] = fRec142[0];
			fRec141[2] = fRec141[1];
			fRec141[1] = fRec141[0];
			fRec140[2] = fRec140[1];
			fRec140[1] = fRec140[0];
			fRec139[1] = fRec139[0];
			fRec152[2] = fRec152[1];
			fRec152[1] = fRec152[0];
			fRec151[2] = fRec151[1];
			fRec151[1] = fRec151[0];
			fRec150[2] = fRec150[1];
			fRec150[1] = fRec150[0];
			fRec149[2] = fRec149[1];
			fRec149[1] = fRec149[0];
			fRec148[2] = fRec148[1];
			fRec148[1] = fRec148[0];
			fRec147[2] = fRec147[1];
			fRec147[1] = fRec147[0];
			fRec146[1] = fRec146[0];
			fRec159[2] = fRec159[1];
			fRec159[1] = fRec159[0];
			fRec158[2] = fRec158[1];
			fRec158[1] = fRec158[0];
			fRec157[2] = fRec157[1];
			fRec157[1] = fRec157[0];
			fRec156[2] = fRec156[1];
			fRec156[1] = fRec156[0];
			fRec155[2] = fRec155[1];
			fRec155[1] = fRec155[0];
			fRec154[2] = fRec154[1];
			fRec154[1] = fRec154[0];
			fRec153[1] = fRec153[0];
			fRec166[2] = fRec166[1];
			fRec166[1] = fRec166[0];
			fRec165[2] = fRec165[1];
			fRec165[1] = fRec165[0];
			fRec164[2] = fRec164[1];
			fRec164[1] = fRec164[0];
			fRec163[2] = fRec163[1];
			fRec163[1] = fRec163[0];
			fRec162[2] = fRec162[1];
			fRec162[1] = fRec162[0];
			fRec161[2] = fRec161[1];
			fRec161[1] = fRec161[0];
			fRec160[1] = fRec160[0];
			fRec173[2] = fRec173[1];
			fRec173[1] = fRec173[0];
			fRec172[2] = fRec172[1];
			fRec172[1] = fRec172[0];
			fRec171[2] = fRec171[1];
			fRec171[1] = fRec171[0];
			fRec170[2] = fRec170[1];
			fRec170[1] = fRec170[0];
			fRec169[2] = fRec169[1];
			fRec169[1] = fRec169[0];
			fRec168[2] = fRec168[1];
			fRec168[1] = fRec168[0];
			fRec167[1] = fRec167[0];
			fRec180[2] = fRec180[1];
			fRec180[1] = fRec180[0];
			fRec179[2] = fRec179[1];
			fRec179[1] = fRec179[0];
			fRec178[2] = fRec178[1];
			fRec178[1] = fRec178[0];
			fRec177[2] = fRec177[1];
			fRec177[1] = fRec177[0];
			fRec176[2] = fRec176[1];
			fRec176[1] = fRec176[0];
			fRec175[2] = fRec175[1];
			fRec175[1] = fRec175[0];
			fRec174[1] = fRec174[0];
			fRec187[2] = fRec187[1];
			fRec187[1] = fRec187[0];
			fRec186[2] = fRec186[1];
			fRec186[1] = fRec186[0];
			fRec185[2] = fRec185[1];
			fRec185[1] = fRec185[0];
			fRec184[2] = fRec184[1];
			fRec184[1] = fRec184[0];
			fRec183[2] = fRec183[1];
			fRec183[1] = fRec183[0];
			fRec182[2] = fRec182[1];
			fRec182[1] = fRec182[0];
			fRec181[1] = fRec181[0];
			fRec194[2] = fRec194[1];
			fRec194[1] = fRec194[0];
			fRec193[2] = fRec193[1];
			fRec193[1] = fRec193[0];
			fRec192[2] = fRec192[1];
			fRec192[1] = fRec192[0];
			fRec191[2] = fRec191[1];
			fRec191[1] = fRec191[0];
			fRec190[2] = fRec190[1];
			fRec190[1] = fRec190[0];
			fRec189[2] = fRec189[1];
			fRec189[1] = fRec189[0];
			fRec188[1] = fRec188[0];
			fRec201[2] = fRec201[1];
			fRec201[1] = fRec201[0];
			fRec200[2] = fRec200[1];
			fRec200[1] = fRec200[0];
			fRec199[2] = fRec199[1];
			fRec199[1] = fRec199[0];
			fRec198[2] = fRec198[1];
			fRec198[1] = fRec198[0];
			fRec197[2] = fRec197[1];
			fRec197[1] = fRec197[0];
			fRec196[2] = fRec196[1];
			fRec196[1] = fRec196[0];
			fRec195[1] = fRec195[0];
			fRec205[2] = fRec205[1];
			fRec205[1] = fRec205[0];
			fRec204[2] = fRec204[1];
			fRec204[1] = fRec204[0];
			fRec203[2] = fRec203[1];
			fRec203[1] = fRec203[0];
			fRec202[1] = fRec202[0];
			
		}
		
	}
	
};

