/* ------------------------------------------------------------
name: "parametricEqLab"
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
	float fConst14;
	float fHslider2;
	float fHslider3;
	float fVslider0;
	float fRec9[] = new float[2];
	float fCheckbox0;
	float fCheckbox1;
	float fEntry0;
	float fConst15;
	float fVslider1;
	float fVslider2;
	float fRec11[] = new float[2];
	float fVec1[] = new float[2];
	float fRec10[] = new float[2];
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
	float fRec12[] = new float[2];
	float fVec9[] = new float[2];
	float fVec10[] = new float[2];
	float fVec11[] = new float[2];
	float fVec12[] = new float[2];
	float fVec13[] = new float[2];
	float fVec14[] = new float[2];
	float fVslider4;
	float fVec15[] = new float[2];
	float fRec13[] = new float[2];
	float fVec16[] = new float[2];
	float fVec17[] = new float[2];
	float fVec18[] = new float[2];
	float fVec19[] = new float[2];
	float fVec20[] = new float[2];
	float fVec21[] = new float[2];
	float fCheckbox2;
	int iRec14[] = new int[2];
	float fRec15[] = new float[4];
	float fVec22[] = new float[2];
	float fRec8[] = new float[2];
	float fRec7[] = new float[3];
	float fHslider4;
	float fRec17[] = new float[2];
	float fRec16[] = new float[3];
	float fConst19;
	float fHslider5;
	float fRec18[] = new float[2];
	float fHslider6;
	float fConst20;
	float fHslider7;
	float fConst21;
	float fRec6[] = new float[3];
	float fVec23[] = new float[2];
	float fRec5[] = new float[2];
	float fRec4[] = new float[3];
	float fHslider8;
	float fRec20[] = new float[2];
	float fRec19[] = new float[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec3[] = new float[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec2[] = new float[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec1[] = new float[3];
	float fConst31;
	float fRec0[] = new float[2];
	float fVbargraph0;
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
	float fRec27[] = new float[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec26[] = new float[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec25[] = new float[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec24[] = new float[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec23[] = new float[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec22[] = new float[3];
	float fConst69;
	float fRec21[] = new float[2];
	float fVbargraph1;
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
	float fRec34[] = new float[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec33[] = new float[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec32[] = new float[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec31[] = new float[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec30[] = new float[3];
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec29[] = new float[3];
	float fConst107;
	float fRec28[] = new float[2];
	float fVbargraph2;
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
	float fRec41[] = new float[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec40[] = new float[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec39[] = new float[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec38[] = new float[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec37[] = new float[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fRec36[] = new float[3];
	float fConst145;
	float fRec35[] = new float[2];
	float fVbargraph3;
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
	float fConst166;
	float fRec48[] = new float[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec47[] = new float[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fRec46[] = new float[3];
	float fConst173;
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec45[] = new float[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec44[] = new float[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec43[] = new float[3];
	float fConst183;
	float fRec42[] = new float[2];
	float fVbargraph4;
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
	float fConst204;
	float fRec55[] = new float[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec54[] = new float[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec53[] = new float[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec52[] = new float[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec51[] = new float[3];
	float fConst218;
	float fConst219;
	float fConst220;
	float fRec50[] = new float[3];
	float fConst221;
	float fRec49[] = new float[2];
	float fVbargraph5;
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
	float fRec62[] = new float[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec61[] = new float[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fRec60[] = new float[3];
	float fConst249;
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec59[] = new float[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec58[] = new float[3];
	float fConst256;
	float fConst257;
	float fConst258;
	float fRec57[] = new float[3];
	float fConst259;
	float fRec56[] = new float[2];
	float fVbargraph6;
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
	float fRec69[] = new float[3];
	float fConst281;
	float fConst282;
	float fConst283;
	float fRec68[] = new float[3];
	float fConst284;
	float fConst285;
	float fConst286;
	float fRec67[] = new float[3];
	float fConst287;
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec66[] = new float[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec65[] = new float[3];
	float fConst294;
	float fConst295;
	float fConst296;
	float fRec64[] = new float[3];
	float fConst297;
	float fRec63[] = new float[2];
	float fVbargraph7;
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
	float fRec76[] = new float[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec75[] = new float[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fRec74[] = new float[3];
	float fConst325;
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec73[] = new float[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec72[] = new float[3];
	float fConst332;
	float fConst333;
	float fConst334;
	float fRec71[] = new float[3];
	float fConst335;
	float fRec70[] = new float[2];
	float fVbargraph8;
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
	float fRec83[] = new float[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec82[] = new float[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fRec81[] = new float[3];
	float fConst363;
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec80[] = new float[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec79[] = new float[3];
	float fConst370;
	float fConst371;
	float fConst372;
	float fRec78[] = new float[3];
	float fConst373;
	float fRec77[] = new float[2];
	float fVbargraph9;
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
	float fRec90[] = new float[3];
	float fConst395;
	float fConst396;
	float fConst397;
	float fRec89[] = new float[3];
	float fConst398;
	float fConst399;
	float fConst400;
	float fRec88[] = new float[3];
	float fConst401;
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec87[] = new float[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec86[] = new float[3];
	float fConst408;
	float fConst409;
	float fConst410;
	float fRec85[] = new float[3];
	float fConst411;
	float fRec84[] = new float[2];
	float fVbargraph10;
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
	float fRec97[] = new float[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec96[] = new float[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fRec95[] = new float[3];
	float fConst439;
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec94[] = new float[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec93[] = new float[3];
	float fConst446;
	float fConst447;
	float fConst448;
	float fRec92[] = new float[3];
	float fConst449;
	float fRec91[] = new float[2];
	float fVbargraph11;
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
	float fRec104[] = new float[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec103[] = new float[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fRec102[] = new float[3];
	float fConst477;
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec101[] = new float[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec100[] = new float[3];
	float fConst484;
	float fConst485;
	float fConst486;
	float fRec99[] = new float[3];
	float fConst487;
	float fRec98[] = new float[2];
	float fVbargraph12;
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
	float fRec111[] = new float[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec110[] = new float[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fRec109[] = new float[3];
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec108[] = new float[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec107[] = new float[3];
	float fConst522;
	float fConst523;
	float fConst524;
	float fRec106[] = new float[3];
	float fConst525;
	float fRec105[] = new float[2];
	float fVbargraph13;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fConst535;
	float fConst536;
	float fConst537;
	float fConst538;
	float fConst539;
	float fConst540;
	float fConst541;
	float fConst542;
	float fConst543;
	float fConst544;
	float fConst545;
	float fConst546;
	float fRec118[] = new float[3];
	float fConst547;
	float fConst548;
	float fConst549;
	float fRec117[] = new float[3];
	float fConst550;
	float fConst551;
	float fConst552;
	float fRec116[] = new float[3];
	float fConst553;
	float fConst554;
	float fConst555;
	float fConst556;
	float fRec115[] = new float[3];
	float fConst557;
	float fConst558;
	float fConst559;
	float fRec114[] = new float[3];
	float fConst560;
	float fConst561;
	float fConst562;
	float fRec113[] = new float[3];
	float fConst563;
	float fRec112[] = new float[2];
	float fVbargraph14;
	float fConst564;
	float fConst565;
	float fConst566;
	float fConst567;
	float fConst568;
	float fConst569;
	float fConst570;
	float fConst571;
	float fConst572;
	float fConst573;
	float fConst574;
	float fConst575;
	float fConst576;
	float fConst577;
	float fConst578;
	float fConst579;
	float fConst580;
	float fConst581;
	float fConst582;
	float fConst583;
	float fConst584;
	float fRec125[] = new float[3];
	float fConst585;
	float fConst586;
	float fConst587;
	float fRec124[] = new float[3];
	float fConst588;
	float fConst589;
	float fConst590;
	float fRec123[] = new float[3];
	float fConst591;
	float fConst592;
	float fConst593;
	float fConst594;
	float fRec122[] = new float[3];
	float fConst595;
	float fConst596;
	float fConst597;
	float fRec121[] = new float[3];
	float fConst598;
	float fConst599;
	float fConst600;
	float fRec120[] = new float[3];
	float fConst601;
	float fRec119[] = new float[2];
	float fVbargraph15;
	float fConst602;
	float fConst603;
	float fConst604;
	float fConst605;
	float fConst606;
	float fConst607;
	float fConst608;
	float fConst609;
	float fConst610;
	float fConst611;
	float fConst612;
	float fConst613;
	float fConst614;
	float fConst615;
	float fConst616;
	float fConst617;
	float fConst618;
	float fConst619;
	float fConst620;
	float fConst621;
	float fConst622;
	float fRec132[] = new float[3];
	float fConst623;
	float fConst624;
	float fConst625;
	float fRec131[] = new float[3];
	float fConst626;
	float fConst627;
	float fConst628;
	float fRec130[] = new float[3];
	float fConst629;
	float fConst630;
	float fConst631;
	float fConst632;
	float fRec129[] = new float[3];
	float fConst633;
	float fConst634;
	float fConst635;
	float fRec128[] = new float[3];
	float fConst636;
	float fConst637;
	float fConst638;
	float fRec127[] = new float[3];
	float fConst639;
	float fRec126[] = new float[2];
	float fVbargraph16;
	float fConst640;
	float fConst641;
	float fConst642;
	float fConst643;
	float fConst644;
	float fConst645;
	float fConst646;
	float fConst647;
	float fConst648;
	float fConst649;
	float fConst650;
	float fConst651;
	float fConst652;
	float fConst653;
	float fConst654;
	float fConst655;
	float fConst656;
	float fConst657;
	float fConst658;
	float fConst659;
	float fConst660;
	float fRec139[] = new float[3];
	float fConst661;
	float fConst662;
	float fConst663;
	float fRec138[] = new float[3];
	float fConst664;
	float fConst665;
	float fConst666;
	float fRec137[] = new float[3];
	float fConst667;
	float fConst668;
	float fConst669;
	float fConst670;
	float fRec136[] = new float[3];
	float fConst671;
	float fConst672;
	float fConst673;
	float fRec135[] = new float[3];
	float fConst674;
	float fConst675;
	float fConst676;
	float fRec134[] = new float[3];
	float fConst677;
	float fRec133[] = new float[2];
	float fVbargraph17;
	float fConst678;
	float fConst679;
	float fConst680;
	float fConst681;
	float fConst682;
	float fConst683;
	float fConst684;
	float fConst685;
	float fConst686;
	float fConst687;
	float fConst688;
	float fConst689;
	float fConst690;
	float fConst691;
	float fConst692;
	float fConst693;
	float fConst694;
	float fConst695;
	float fConst696;
	float fConst697;
	float fConst698;
	float fRec146[] = new float[3];
	float fConst699;
	float fConst700;
	float fConst701;
	float fRec145[] = new float[3];
	float fConst702;
	float fConst703;
	float fConst704;
	float fRec144[] = new float[3];
	float fConst705;
	float fConst706;
	float fConst707;
	float fConst708;
	float fRec143[] = new float[3];
	float fConst709;
	float fConst710;
	float fConst711;
	float fRec142[] = new float[3];
	float fConst712;
	float fConst713;
	float fConst714;
	float fRec141[] = new float[3];
	float fConst715;
	float fRec140[] = new float[2];
	float fVbargraph18;
	float fConst716;
	float fConst717;
	float fConst718;
	float fConst719;
	float fConst720;
	float fConst721;
	float fConst722;
	float fConst723;
	float fConst724;
	float fRec150[] = new float[3];
	float fConst725;
	float fConst726;
	float fConst727;
	float fRec149[] = new float[3];
	float fConst728;
	float fConst729;
	float fConst730;
	float fRec148[] = new float[3];
	float fConst731;
	float fRec147[] = new float[2];
	float fVbargraph19;
	
	public void metadata(Meta m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Demonstrate the Parametric Equalizer sections on test signals with spectrum analysis display");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "parametricEqLab");
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
		fConst14 = (3.14159274f / fConst0);
		fConst15 = (1.0f / fConst0);
		fConst16 = (0.25f * fConst0);
		fConst17 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst18 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst19 = (1382.30078f / fConst0);
		fConst20 = (1382.30078f * fConst15);
		fConst21 = (2764.60156f * fConst15);
		fConst22 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst23 = (1.0f / fConst5);
		fConst24 = (2.0f * (4.07678175f - fConst23));
		fConst25 = (fConst12 + 0.000407678192f);
		fConst26 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst27 = (2.0f * (1.4500711f - fConst23));
		fConst28 = (fConst9 + 1.4500711f);
		fConst29 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst30 = (2.0f * (0.935140193f - fConst23));
		fConst31 = (fConst6 + 0.935140193f);
		fConst32 = (float)java.lang.Math.tan((35543.0625f / fConst0));
		fConst33 = (1.0f / fConst32);
		fConst34 = (1.0f / (((fConst33 + 0.157482162f) / fConst32) + 0.935140193f));
		fConst35 = mydsp_faustpower2_f(fConst32);
		fConst36 = (50.0638084f / fConst35);
		fConst37 = (2.0f * (0.935140193f - fConst36));
		fConst38 = (1.0f / (((fConst33 + 0.743130445f) / fConst32) + 1.4500711f));
		fConst39 = (11.0520525f / fConst35);
		fConst40 = (2.0f * (1.4500711f - fConst39));
		fConst41 = (1.0f / (((fConst33 + 3.18972731f) / fConst32) + 4.07678175f));
		fConst42 = (0.00176617282f / fConst35);
		fConst43 = (2.0f * (0.000407678192f - fConst42));
		fConst44 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst45 = (2.0f * (53.5361519f - fConst23));
		fConst46 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst47 = (2.0f * (7.62173128f - fConst23));
		fConst48 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst49 = (9.99999975e-05f / fConst5);
		fConst50 = (2.0f * (0.000433227193f - fConst49));
		fConst51 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst52 = (2.0f * (0.245291501f - fConst23));
		fConst53 = (fConst49 + 0.000433227193f);
		fConst54 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst55 = (2.0f * (0.689621389f - fConst23));
		fConst56 = (fConst23 + 7.62173128f);
		fConst57 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst58 = (2.0f * (1.06935835f - fConst23));
		fConst59 = (fConst23 + 53.5361519f);
		fConst60 = (((fConst33 + -3.18972731f) / fConst32) + 4.07678175f);
		fConst61 = (1.0f / fConst35);
		fConst62 = (2.0f * (4.07678175f - fConst61));
		fConst63 = (fConst42 + 0.000407678192f);
		fConst64 = (((fConst33 + -0.743130445f) / fConst32) + 1.4500711f);
		fConst65 = (2.0f * (1.4500711f - fConst61));
		fConst66 = (fConst39 + 1.4500711f);
		fConst67 = (((fConst33 + -0.157482162f) / fConst32) + 0.935140193f);
		fConst68 = (2.0f * (0.935140193f - fConst61));
		fConst69 = (fConst36 + 0.935140193f);
		fConst70 = (float)java.lang.Math.tan((25132.7422f / fConst0));
		fConst71 = (1.0f / fConst70);
		fConst72 = (1.0f / (((fConst71 + 0.157482162f) / fConst70) + 0.935140193f));
		fConst73 = mydsp_faustpower2_f(fConst70);
		fConst74 = (50.0638084f / fConst73);
		fConst75 = (2.0f * (0.935140193f - fConst74));
		fConst76 = (1.0f / (((fConst71 + 0.743130445f) / fConst70) + 1.4500711f));
		fConst77 = (11.0520525f / fConst73);
		fConst78 = (2.0f * (1.4500711f - fConst77));
		fConst79 = (1.0f / (((fConst71 + 3.18972731f) / fConst70) + 4.07678175f));
		fConst80 = (0.00176617282f / fConst73);
		fConst81 = (2.0f * (0.000407678192f - fConst80));
		fConst82 = (1.0f / (((fConst33 + 0.168404877f) / fConst32) + 1.06935835f));
		fConst83 = (2.0f * (53.5361519f - fConst61));
		fConst84 = (1.0f / (((fConst33 + 0.51247865f) / fConst32) + 0.689621389f));
		fConst85 = (2.0f * (7.62173128f - fConst61));
		fConst86 = (1.0f / (((fConst33 + 0.782413065f) / fConst32) + 0.245291501f));
		fConst87 = (9.99999975e-05f / fConst35);
		fConst88 = (2.0f * (0.000433227193f - fConst87));
		fConst89 = (((fConst33 + -0.782413065f) / fConst32) + 0.245291501f);
		fConst90 = (2.0f * (0.245291501f - fConst61));
		fConst91 = (fConst87 + 0.000433227193f);
		fConst92 = (((fConst33 + -0.51247865f) / fConst32) + 0.689621389f);
		fConst93 = (2.0f * (0.689621389f - fConst61));
		fConst94 = (fConst61 + 7.62173128f);
		fConst95 = (((fConst33 + -0.168404877f) / fConst32) + 1.06935835f);
		fConst96 = (2.0f * (1.06935835f - fConst61));
		fConst97 = (fConst61 + 53.5361519f);
		fConst98 = (((fConst71 + -3.18972731f) / fConst70) + 4.07678175f);
		fConst99 = (1.0f / fConst73);
		fConst100 = (2.0f * (4.07678175f - fConst99));
		fConst101 = (fConst80 + 0.000407678192f);
		fConst102 = (((fConst71 + -0.743130445f) / fConst70) + 1.4500711f);
		fConst103 = (2.0f * (1.4500711f - fConst99));
		fConst104 = (fConst77 + 1.4500711f);
		fConst105 = (((fConst71 + -0.157482162f) / fConst70) + 0.935140193f);
		fConst106 = (2.0f * (0.935140193f - fConst99));
		fConst107 = (fConst74 + 0.935140193f);
		fConst108 = (float)java.lang.Math.tan((17771.5312f / fConst0));
		fConst109 = (1.0f / fConst108);
		fConst110 = (1.0f / (((fConst109 + 0.157482162f) / fConst108) + 0.935140193f));
		fConst111 = mydsp_faustpower2_f(fConst108);
		fConst112 = (50.0638084f / fConst111);
		fConst113 = (2.0f * (0.935140193f - fConst112));
		fConst114 = (1.0f / (((fConst109 + 0.743130445f) / fConst108) + 1.4500711f));
		fConst115 = (11.0520525f / fConst111);
		fConst116 = (2.0f * (1.4500711f - fConst115));
		fConst117 = (1.0f / (((fConst109 + 3.18972731f) / fConst108) + 4.07678175f));
		fConst118 = (0.00176617282f / fConst111);
		fConst119 = (2.0f * (0.000407678192f - fConst118));
		fConst120 = (1.0f / (((fConst71 + 0.168404877f) / fConst70) + 1.06935835f));
		fConst121 = (2.0f * (53.5361519f - fConst99));
		fConst122 = (1.0f / (((fConst71 + 0.51247865f) / fConst70) + 0.689621389f));
		fConst123 = (2.0f * (7.62173128f - fConst99));
		fConst124 = (1.0f / (((fConst71 + 0.782413065f) / fConst70) + 0.245291501f));
		fConst125 = (9.99999975e-05f / fConst73);
		fConst126 = (2.0f * (0.000433227193f - fConst125));
		fConst127 = (((fConst71 + -0.782413065f) / fConst70) + 0.245291501f);
		fConst128 = (2.0f * (0.245291501f - fConst99));
		fConst129 = (fConst125 + 0.000433227193f);
		fConst130 = (((fConst71 + -0.51247865f) / fConst70) + 0.689621389f);
		fConst131 = (2.0f * (0.689621389f - fConst99));
		fConst132 = (fConst99 + 7.62173128f);
		fConst133 = (((fConst71 + -0.168404877f) / fConst70) + 1.06935835f);
		fConst134 = (2.0f * (1.06935835f - fConst99));
		fConst135 = (fConst99 + 53.5361519f);
		fConst136 = (((fConst109 + -3.18972731f) / fConst108) + 4.07678175f);
		fConst137 = (1.0f / fConst111);
		fConst138 = (2.0f * (4.07678175f - fConst137));
		fConst139 = (fConst118 + 0.000407678192f);
		fConst140 = (((fConst109 + -0.743130445f) / fConst108) + 1.4500711f);
		fConst141 = (2.0f * (1.4500711f - fConst137));
		fConst142 = (fConst115 + 1.4500711f);
		fConst143 = (((fConst109 + -0.157482162f) / fConst108) + 0.935140193f);
		fConst144 = (2.0f * (0.935140193f - fConst137));
		fConst145 = (fConst112 + 0.935140193f);
		fConst146 = (float)java.lang.Math.tan((12566.3711f / fConst0));
		fConst147 = (1.0f / fConst146);
		fConst148 = (1.0f / (((fConst147 + 0.157482162f) / fConst146) + 0.935140193f));
		fConst149 = mydsp_faustpower2_f(fConst146);
		fConst150 = (50.0638084f / fConst149);
		fConst151 = (2.0f * (0.935140193f - fConst150));
		fConst152 = (1.0f / (((fConst147 + 0.743130445f) / fConst146) + 1.4500711f));
		fConst153 = (11.0520525f / fConst149);
		fConst154 = (2.0f * (1.4500711f - fConst153));
		fConst155 = (1.0f / (((fConst147 + 3.18972731f) / fConst146) + 4.07678175f));
		fConst156 = (0.00176617282f / fConst149);
		fConst157 = (2.0f * (0.000407678192f - fConst156));
		fConst158 = (1.0f / (((fConst109 + 0.168404877f) / fConst108) + 1.06935835f));
		fConst159 = (2.0f * (53.5361519f - fConst137));
		fConst160 = (1.0f / (((fConst109 + 0.51247865f) / fConst108) + 0.689621389f));
		fConst161 = (2.0f * (7.62173128f - fConst137));
		fConst162 = (1.0f / (((fConst109 + 0.782413065f) / fConst108) + 0.245291501f));
		fConst163 = (9.99999975e-05f / fConst111);
		fConst164 = (2.0f * (0.000433227193f - fConst163));
		fConst165 = (((fConst109 + -0.782413065f) / fConst108) + 0.245291501f);
		fConst166 = (2.0f * (0.245291501f - fConst137));
		fConst167 = (fConst163 + 0.000433227193f);
		fConst168 = (((fConst109 + -0.51247865f) / fConst108) + 0.689621389f);
		fConst169 = (2.0f * (0.689621389f - fConst137));
		fConst170 = (fConst137 + 7.62173128f);
		fConst171 = (((fConst109 + -0.168404877f) / fConst108) + 1.06935835f);
		fConst172 = (2.0f * (1.06935835f - fConst137));
		fConst173 = (fConst137 + 53.5361519f);
		fConst174 = (((fConst147 + -3.18972731f) / fConst146) + 4.07678175f);
		fConst175 = (1.0f / fConst149);
		fConst176 = (2.0f * (4.07678175f - fConst175));
		fConst177 = (fConst156 + 0.000407678192f);
		fConst178 = (((fConst147 + -0.743130445f) / fConst146) + 1.4500711f);
		fConst179 = (2.0f * (1.4500711f - fConst175));
		fConst180 = (fConst153 + 1.4500711f);
		fConst181 = (((fConst147 + -0.157482162f) / fConst146) + 0.935140193f);
		fConst182 = (2.0f * (0.935140193f - fConst175));
		fConst183 = (fConst150 + 0.935140193f);
		fConst184 = (float)java.lang.Math.tan((8885.76562f / fConst0));
		fConst185 = (1.0f / fConst184);
		fConst186 = (1.0f / (((fConst185 + 0.157482162f) / fConst184) + 0.935140193f));
		fConst187 = mydsp_faustpower2_f(fConst184);
		fConst188 = (50.0638084f / fConst187);
		fConst189 = (2.0f * (0.935140193f - fConst188));
		fConst190 = (1.0f / (((fConst185 + 0.743130445f) / fConst184) + 1.4500711f));
		fConst191 = (11.0520525f / fConst187);
		fConst192 = (2.0f * (1.4500711f - fConst191));
		fConst193 = (1.0f / (((fConst185 + 3.18972731f) / fConst184) + 4.07678175f));
		fConst194 = (0.00176617282f / fConst187);
		fConst195 = (2.0f * (0.000407678192f - fConst194));
		fConst196 = (1.0f / (((fConst147 + 0.168404877f) / fConst146) + 1.06935835f));
		fConst197 = (2.0f * (53.5361519f - fConst175));
		fConst198 = (1.0f / (((fConst147 + 0.51247865f) / fConst146) + 0.689621389f));
		fConst199 = (2.0f * (7.62173128f - fConst175));
		fConst200 = (1.0f / (((fConst147 + 0.782413065f) / fConst146) + 0.245291501f));
		fConst201 = (9.99999975e-05f / fConst149);
		fConst202 = (2.0f * (0.000433227193f - fConst201));
		fConst203 = (((fConst147 + -0.782413065f) / fConst146) + 0.245291501f);
		fConst204 = (2.0f * (0.245291501f - fConst175));
		fConst205 = (fConst201 + 0.000433227193f);
		fConst206 = (((fConst147 + -0.51247865f) / fConst146) + 0.689621389f);
		fConst207 = (2.0f * (0.689621389f - fConst175));
		fConst208 = (fConst175 + 7.62173128f);
		fConst209 = (((fConst147 + -0.168404877f) / fConst146) + 1.06935835f);
		fConst210 = (2.0f * (1.06935835f - fConst175));
		fConst211 = (fConst175 + 53.5361519f);
		fConst212 = (((fConst185 + -3.18972731f) / fConst184) + 4.07678175f);
		fConst213 = (1.0f / fConst187);
		fConst214 = (2.0f * (4.07678175f - fConst213));
		fConst215 = (fConst194 + 0.000407678192f);
		fConst216 = (((fConst185 + -0.743130445f) / fConst184) + 1.4500711f);
		fConst217 = (2.0f * (1.4500711f - fConst213));
		fConst218 = (fConst191 + 1.4500711f);
		fConst219 = (((fConst185 + -0.157482162f) / fConst184) + 0.935140193f);
		fConst220 = (2.0f * (0.935140193f - fConst213));
		fConst221 = (fConst188 + 0.935140193f);
		fConst222 = (float)java.lang.Math.tan((6283.18555f / fConst0));
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
		fConst234 = (1.0f / (((fConst185 + 0.168404877f) / fConst184) + 1.06935835f));
		fConst235 = (2.0f * (53.5361519f - fConst213));
		fConst236 = (1.0f / (((fConst185 + 0.51247865f) / fConst184) + 0.689621389f));
		fConst237 = (2.0f * (7.62173128f - fConst213));
		fConst238 = (1.0f / (((fConst185 + 0.782413065f) / fConst184) + 0.245291501f));
		fConst239 = (9.99999975e-05f / fConst187);
		fConst240 = (2.0f * (0.000433227193f - fConst239));
		fConst241 = (((fConst185 + -0.782413065f) / fConst184) + 0.245291501f);
		fConst242 = (2.0f * (0.245291501f - fConst213));
		fConst243 = (fConst239 + 0.000433227193f);
		fConst244 = (((fConst185 + -0.51247865f) / fConst184) + 0.689621389f);
		fConst245 = (2.0f * (0.689621389f - fConst213));
		fConst246 = (fConst213 + 7.62173128f);
		fConst247 = (((fConst185 + -0.168404877f) / fConst184) + 1.06935835f);
		fConst248 = (2.0f * (1.06935835f - fConst213));
		fConst249 = (fConst213 + 53.5361519f);
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
		fConst260 = (float)java.lang.Math.tan((4442.88281f / fConst0));
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
		fConst298 = (float)java.lang.Math.tan((3141.59277f / fConst0));
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
		fConst336 = (float)java.lang.Math.tan((2221.44141f / fConst0));
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
		fConst374 = (float)java.lang.Math.tan((1570.79639f / fConst0));
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
		fConst412 = (float)java.lang.Math.tan((1110.7207f / fConst0));
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
		fConst450 = (float)java.lang.Math.tan((785.398193f / fConst0));
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
		fConst488 = (float)java.lang.Math.tan((555.360352f / fConst0));
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
		fConst526 = (float)java.lang.Math.tan((392.699097f / fConst0));
		fConst527 = (1.0f / fConst526);
		fConst528 = (1.0f / (((fConst527 + 0.157482162f) / fConst526) + 0.935140193f));
		fConst529 = mydsp_faustpower2_f(fConst526);
		fConst530 = (50.0638084f / fConst529);
		fConst531 = (2.0f * (0.935140193f - fConst530));
		fConst532 = (1.0f / (((fConst527 + 0.743130445f) / fConst526) + 1.4500711f));
		fConst533 = (11.0520525f / fConst529);
		fConst534 = (2.0f * (1.4500711f - fConst533));
		fConst535 = (1.0f / (((fConst527 + 3.18972731f) / fConst526) + 4.07678175f));
		fConst536 = (0.00176617282f / fConst529);
		fConst537 = (2.0f * (0.000407678192f - fConst536));
		fConst538 = (1.0f / (((fConst489 + 0.168404877f) / fConst488) + 1.06935835f));
		fConst539 = (2.0f * (53.5361519f - fConst517));
		fConst540 = (1.0f / (((fConst489 + 0.51247865f) / fConst488) + 0.689621389f));
		fConst541 = (2.0f * (7.62173128f - fConst517));
		fConst542 = (1.0f / (((fConst489 + 0.782413065f) / fConst488) + 0.245291501f));
		fConst543 = (9.99999975e-05f / fConst491);
		fConst544 = (2.0f * (0.000433227193f - fConst543));
		fConst545 = (((fConst489 + -0.782413065f) / fConst488) + 0.245291501f);
		fConst546 = (2.0f * (0.245291501f - fConst517));
		fConst547 = (fConst543 + 0.000433227193f);
		fConst548 = (((fConst489 + -0.51247865f) / fConst488) + 0.689621389f);
		fConst549 = (2.0f * (0.689621389f - fConst517));
		fConst550 = (fConst517 + 7.62173128f);
		fConst551 = (((fConst489 + -0.168404877f) / fConst488) + 1.06935835f);
		fConst552 = (2.0f * (1.06935835f - fConst517));
		fConst553 = (fConst517 + 53.5361519f);
		fConst554 = (((fConst527 + -3.18972731f) / fConst526) + 4.07678175f);
		fConst555 = (1.0f / fConst529);
		fConst556 = (2.0f * (4.07678175f - fConst555));
		fConst557 = (fConst536 + 0.000407678192f);
		fConst558 = (((fConst527 + -0.743130445f) / fConst526) + 1.4500711f);
		fConst559 = (2.0f * (1.4500711f - fConst555));
		fConst560 = (fConst533 + 1.4500711f);
		fConst561 = (((fConst527 + -0.157482162f) / fConst526) + 0.935140193f);
		fConst562 = (2.0f * (0.935140193f - fConst555));
		fConst563 = (fConst530 + 0.935140193f);
		fConst564 = (float)java.lang.Math.tan((277.680176f / fConst0));
		fConst565 = (1.0f / fConst564);
		fConst566 = (1.0f / (((fConst565 + 0.157482162f) / fConst564) + 0.935140193f));
		fConst567 = mydsp_faustpower2_f(fConst564);
		fConst568 = (50.0638084f / fConst567);
		fConst569 = (2.0f * (0.935140193f - fConst568));
		fConst570 = (1.0f / (((fConst565 + 0.743130445f) / fConst564) + 1.4500711f));
		fConst571 = (11.0520525f / fConst567);
		fConst572 = (2.0f * (1.4500711f - fConst571));
		fConst573 = (1.0f / (((fConst565 + 3.18972731f) / fConst564) + 4.07678175f));
		fConst574 = (0.00176617282f / fConst567);
		fConst575 = (2.0f * (0.000407678192f - fConst574));
		fConst576 = (1.0f / (((fConst527 + 0.168404877f) / fConst526) + 1.06935835f));
		fConst577 = (2.0f * (53.5361519f - fConst555));
		fConst578 = (1.0f / (((fConst527 + 0.51247865f) / fConst526) + 0.689621389f));
		fConst579 = (2.0f * (7.62173128f - fConst555));
		fConst580 = (1.0f / (((fConst527 + 0.782413065f) / fConst526) + 0.245291501f));
		fConst581 = (9.99999975e-05f / fConst529);
		fConst582 = (2.0f * (0.000433227193f - fConst581));
		fConst583 = (((fConst527 + -0.782413065f) / fConst526) + 0.245291501f);
		fConst584 = (2.0f * (0.245291501f - fConst555));
		fConst585 = (fConst581 + 0.000433227193f);
		fConst586 = (((fConst527 + -0.51247865f) / fConst526) + 0.689621389f);
		fConst587 = (2.0f * (0.689621389f - fConst555));
		fConst588 = (fConst555 + 7.62173128f);
		fConst589 = (((fConst527 + -0.168404877f) / fConst526) + 1.06935835f);
		fConst590 = (2.0f * (1.06935835f - fConst555));
		fConst591 = (fConst555 + 53.5361519f);
		fConst592 = (((fConst565 + -3.18972731f) / fConst564) + 4.07678175f);
		fConst593 = (1.0f / fConst567);
		fConst594 = (2.0f * (4.07678175f - fConst593));
		fConst595 = (fConst574 + 0.000407678192f);
		fConst596 = (((fConst565 + -0.743130445f) / fConst564) + 1.4500711f);
		fConst597 = (2.0f * (1.4500711f - fConst593));
		fConst598 = (fConst571 + 1.4500711f);
		fConst599 = (((fConst565 + -0.157482162f) / fConst564) + 0.935140193f);
		fConst600 = (2.0f * (0.935140193f - fConst593));
		fConst601 = (fConst568 + 0.935140193f);
		fConst602 = (float)java.lang.Math.tan((196.349548f / fConst0));
		fConst603 = (1.0f / fConst602);
		fConst604 = (1.0f / (((fConst603 + 0.157482162f) / fConst602) + 0.935140193f));
		fConst605 = mydsp_faustpower2_f(fConst602);
		fConst606 = (50.0638084f / fConst605);
		fConst607 = (2.0f * (0.935140193f - fConst606));
		fConst608 = (1.0f / (((fConst603 + 0.743130445f) / fConst602) + 1.4500711f));
		fConst609 = (11.0520525f / fConst605);
		fConst610 = (2.0f * (1.4500711f - fConst609));
		fConst611 = (1.0f / (((fConst603 + 3.18972731f) / fConst602) + 4.07678175f));
		fConst612 = (0.00176617282f / fConst605);
		fConst613 = (2.0f * (0.000407678192f - fConst612));
		fConst614 = (1.0f / (((fConst565 + 0.168404877f) / fConst564) + 1.06935835f));
		fConst615 = (2.0f * (53.5361519f - fConst593));
		fConst616 = (1.0f / (((fConst565 + 0.51247865f) / fConst564) + 0.689621389f));
		fConst617 = (2.0f * (7.62173128f - fConst593));
		fConst618 = (1.0f / (((fConst565 + 0.782413065f) / fConst564) + 0.245291501f));
		fConst619 = (9.99999975e-05f / fConst567);
		fConst620 = (2.0f * (0.000433227193f - fConst619));
		fConst621 = (((fConst565 + -0.782413065f) / fConst564) + 0.245291501f);
		fConst622 = (2.0f * (0.245291501f - fConst593));
		fConst623 = (fConst619 + 0.000433227193f);
		fConst624 = (((fConst565 + -0.51247865f) / fConst564) + 0.689621389f);
		fConst625 = (2.0f * (0.689621389f - fConst593));
		fConst626 = (fConst593 + 7.62173128f);
		fConst627 = (((fConst565 + -0.168404877f) / fConst564) + 1.06935835f);
		fConst628 = (2.0f * (1.06935835f - fConst593));
		fConst629 = (fConst593 + 53.5361519f);
		fConst630 = (((fConst603 + -3.18972731f) / fConst602) + 4.07678175f);
		fConst631 = (1.0f / fConst605);
		fConst632 = (2.0f * (4.07678175f - fConst631));
		fConst633 = (fConst612 + 0.000407678192f);
		fConst634 = (((fConst603 + -0.743130445f) / fConst602) + 1.4500711f);
		fConst635 = (2.0f * (1.4500711f - fConst631));
		fConst636 = (fConst609 + 1.4500711f);
		fConst637 = (((fConst603 + -0.157482162f) / fConst602) + 0.935140193f);
		fConst638 = (2.0f * (0.935140193f - fConst631));
		fConst639 = (fConst606 + 0.935140193f);
		fConst640 = (float)java.lang.Math.tan((138.840088f / fConst0));
		fConst641 = (1.0f / fConst640);
		fConst642 = (1.0f / (((fConst641 + 0.157482162f) / fConst640) + 0.935140193f));
		fConst643 = mydsp_faustpower2_f(fConst640);
		fConst644 = (50.0638084f / fConst643);
		fConst645 = (2.0f * (0.935140193f - fConst644));
		fConst646 = (1.0f / (((fConst641 + 0.743130445f) / fConst640) + 1.4500711f));
		fConst647 = (11.0520525f / fConst643);
		fConst648 = (2.0f * (1.4500711f - fConst647));
		fConst649 = (1.0f / (((fConst641 + 3.18972731f) / fConst640) + 4.07678175f));
		fConst650 = (0.00176617282f / fConst643);
		fConst651 = (2.0f * (0.000407678192f - fConst650));
		fConst652 = (1.0f / (((fConst603 + 0.168404877f) / fConst602) + 1.06935835f));
		fConst653 = (2.0f * (53.5361519f - fConst631));
		fConst654 = (1.0f / (((fConst603 + 0.51247865f) / fConst602) + 0.689621389f));
		fConst655 = (2.0f * (7.62173128f - fConst631));
		fConst656 = (1.0f / (((fConst603 + 0.782413065f) / fConst602) + 0.245291501f));
		fConst657 = (9.99999975e-05f / fConst605);
		fConst658 = (2.0f * (0.000433227193f - fConst657));
		fConst659 = (((fConst603 + -0.782413065f) / fConst602) + 0.245291501f);
		fConst660 = (2.0f * (0.245291501f - fConst631));
		fConst661 = (fConst657 + 0.000433227193f);
		fConst662 = (((fConst603 + -0.51247865f) / fConst602) + 0.689621389f);
		fConst663 = (2.0f * (0.689621389f - fConst631));
		fConst664 = (fConst631 + 7.62173128f);
		fConst665 = (((fConst603 + -0.168404877f) / fConst602) + 1.06935835f);
		fConst666 = (2.0f * (1.06935835f - fConst631));
		fConst667 = (fConst631 + 53.5361519f);
		fConst668 = (((fConst641 + -3.18972731f) / fConst640) + 4.07678175f);
		fConst669 = (1.0f / fConst643);
		fConst670 = (2.0f * (4.07678175f - fConst669));
		fConst671 = (fConst650 + 0.000407678192f);
		fConst672 = (((fConst641 + -0.743130445f) / fConst640) + 1.4500711f);
		fConst673 = (2.0f * (1.4500711f - fConst669));
		fConst674 = (fConst647 + 1.4500711f);
		fConst675 = (((fConst641 + -0.157482162f) / fConst640) + 0.935140193f);
		fConst676 = (2.0f * (0.935140193f - fConst669));
		fConst677 = (fConst644 + 0.935140193f);
		fConst678 = (float)java.lang.Math.tan((98.1747742f / fConst0));
		fConst679 = (1.0f / fConst678);
		fConst680 = (1.0f / (((fConst679 + 0.157482162f) / fConst678) + 0.935140193f));
		fConst681 = mydsp_faustpower2_f(fConst678);
		fConst682 = (50.0638084f / fConst681);
		fConst683 = (2.0f * (0.935140193f - fConst682));
		fConst684 = (1.0f / (((fConst679 + 0.743130445f) / fConst678) + 1.4500711f));
		fConst685 = (11.0520525f / fConst681);
		fConst686 = (2.0f * (1.4500711f - fConst685));
		fConst687 = (1.0f / (((fConst679 + 3.18972731f) / fConst678) + 4.07678175f));
		fConst688 = (0.00176617282f / fConst681);
		fConst689 = (2.0f * (0.000407678192f - fConst688));
		fConst690 = (1.0f / (((fConst641 + 0.168404877f) / fConst640) + 1.06935835f));
		fConst691 = (2.0f * (53.5361519f - fConst669));
		fConst692 = (1.0f / (((fConst641 + 0.51247865f) / fConst640) + 0.689621389f));
		fConst693 = (2.0f * (7.62173128f - fConst669));
		fConst694 = (1.0f / (((fConst641 + 0.782413065f) / fConst640) + 0.245291501f));
		fConst695 = (9.99999975e-05f / fConst643);
		fConst696 = (2.0f * (0.000433227193f - fConst695));
		fConst697 = (((fConst641 + -0.782413065f) / fConst640) + 0.245291501f);
		fConst698 = (2.0f * (0.245291501f - fConst669));
		fConst699 = (fConst695 + 0.000433227193f);
		fConst700 = (((fConst641 + -0.51247865f) / fConst640) + 0.689621389f);
		fConst701 = (2.0f * (0.689621389f - fConst669));
		fConst702 = (fConst669 + 7.62173128f);
		fConst703 = (((fConst641 + -0.168404877f) / fConst640) + 1.06935835f);
		fConst704 = (2.0f * (1.06935835f - fConst669));
		fConst705 = (fConst669 + 53.5361519f);
		fConst706 = (((fConst679 + -3.18972731f) / fConst678) + 4.07678175f);
		fConst707 = (1.0f / fConst681);
		fConst708 = (2.0f * (4.07678175f - fConst707));
		fConst709 = (fConst688 + 0.000407678192f);
		fConst710 = (((fConst679 + -0.743130445f) / fConst678) + 1.4500711f);
		fConst711 = (2.0f * (1.4500711f - fConst707));
		fConst712 = (fConst685 + 1.4500711f);
		fConst713 = (((fConst679 + -0.157482162f) / fConst678) + 0.935140193f);
		fConst714 = (2.0f * (0.935140193f - fConst707));
		fConst715 = (fConst682 + 0.935140193f);
		fConst716 = (1.0f / (((fConst679 + 0.168404877f) / fConst678) + 1.06935835f));
		fConst717 = (2.0f * (53.5361519f - fConst707));
		fConst718 = (1.0f / (((fConst679 + 0.51247865f) / fConst678) + 0.689621389f));
		fConst719 = (2.0f * (7.62173128f - fConst707));
		fConst720 = (1.0f / (((fConst679 + 0.782413065f) / fConst678) + 0.245291501f));
		fConst721 = (9.99999975e-05f / fConst681);
		fConst722 = (2.0f * (0.000433227193f - fConst721));
		fConst723 = (((fConst679 + -0.782413065f) / fConst678) + 0.245291501f);
		fConst724 = (2.0f * (0.245291501f - fConst707));
		fConst725 = (fConst721 + 0.000433227193f);
		fConst726 = (((fConst679 + -0.51247865f) / fConst678) + 0.689621389f);
		fConst727 = (2.0f * (0.689621389f - fConst707));
		fConst728 = (fConst707 + 7.62173128f);
		fConst729 = (((fConst679 + -0.168404877f) / fConst678) + 1.06935835f);
		fConst730 = (2.0f * (1.06935835f - fConst707));
		fConst731 = (fConst707 + 53.5361519f);
		
	}
	
	public void instanceResetUserInterface() {
		fHslider0 = (float)50.0f;
		fHslider1 = (float)100.0f;
		fHslider2 = (float)8000.0f;
		fHslider3 = (float)200.0f;
		fVslider0 = (float)-20.0f;
		fCheckbox0 = (float)0.0f;
		fCheckbox1 = (float)0.0f;
		fEntry0 = (float)2.0f;
		fVslider1 = (float)49.0f;
		fVslider2 = (float)0.10000000000000001f;
		fVslider3 = (float)-0.10000000000000001f;
		fVslider4 = (float)0.10000000000000001f;
		fCheckbox2 = (float)0.0f;
		fHslider4 = (float)0.0f;
		fHslider5 = (float)49.0f;
		fHslider6 = (float)0.0f;
		fHslider7 = (float)40.0f;
		fHslider8 = (float)0.0f;
		
	}
	
	public void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec9[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec11[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec10[l4] = 0.0f;
			
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
			fRec12[l12] = 0.0f;
			
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
			fRec13[l20] = 0.0f;
			
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
			iRec14[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec15[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec22[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec8[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec7[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec17[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec16[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec18[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec6[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec23[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec5[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec4[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec20[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec19[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec3[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec2[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec1[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec0[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec27[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec26[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec25[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec24[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec23[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec22[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec21[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec34[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec33[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec32[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec31[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec30[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec29[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec28[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec41[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec40[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec39[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec38[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec37[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec36[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec35[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec48[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec47[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec46[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec45[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec44[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec43[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec42[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec55[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec54[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec53[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec52[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec51[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec50[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec49[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec62[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec61[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec60[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec59[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec58[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec57[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec56[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec69[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec68[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec67[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec66[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec65[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec64[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec63[l93] = 0.0f;
			
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
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec72[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec71[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec70[l100] = 0.0f;
			
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
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec79[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec78[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec77[l107] = 0.0f;
			
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
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec86[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec85[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec84[l114] = 0.0f;
			
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
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec93[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec92[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fRec91[l121] = 0.0f;
			
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
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec100[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec99[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec98[l128] = 0.0f;
			
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
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec107[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec106[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec105[l135] = 0.0f;
			
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
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec114[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec113[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			fRec112[l142] = 0.0f;
			
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
		for (int l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			fRec121[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			fRec120[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			fRec119[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			fRec132[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec131[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			fRec130[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec129[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			fRec128[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 3); l155 = (l155 + 1)) {
			fRec127[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) {
			fRec126[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			fRec139[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			fRec138[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			fRec137[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			fRec136[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			fRec135[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 3); l162 = (l162 + 1)) {
			fRec134[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			fRec133[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			fRec146[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			fRec145[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 3); l166 = (l166 + 1)) {
			fRec144[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			fRec143[l167] = 0.0f;
			
		}
		for (int l168 = 0; (l168 < 3); l168 = (l168 + 1)) {
			fRec142[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 3); l169 = (l169 + 1)) {
			fRec141[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 2); l170 = (l170 + 1)) {
			fRec140[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			fRec150[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 3); l172 = (l172 + 1)) {
			fRec149[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			fRec148[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fRec147[l174] = 0.0f;
			
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
		ui_interface.openVerticalBox("parametricEqLab");
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
		ui_interface.declare("fCheckbox1", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", new FaustVarAccess() {
				public String getId() { return "fCheckbox1"; }
				public void set(float val) { fCheckbox1 = val; }
				public float get() { return (float)fCheckbox1; }
			}
			);
		ui_interface.declare("fCheckbox2", "1", "");
		ui_interface.declare("fCheckbox2", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", new FaustVarAccess() {
				public String getId() { return "fCheckbox2"; }
				public void set(float val) { fCheckbox2 = val; }
				public float get() { return (float)fCheckbox2; }
			}
			);
		ui_interface.declare("fCheckbox0", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", new FaustVarAccess() {
				public String getId() { return "fCheckbox0"; }
				public void set(float val) { fCheckbox0 = val; }
				public float get() { return (float)fCheckbox0; }
			}
			);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib   for info and pointers");
		ui_interface.openHorizontalBox("PARAMETRIC EQ SECTIONS");
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Low Shelf");
		ui_interface.declare("fHslider4", "0", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "Amount of low-frequency boost or cut in decibels");
		ui_interface.declare("fHslider4", "unit", "dB");
		ui_interface.addHorizontalSlider("Low Boost|Cut", new FaustVarAccess() {
				public String getId() { return "fHslider4"; }
				public void set(float val) { fHslider4 = val; }
				public float get() { return (float)fHslider4; }
			}
			, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface.declare("fHslider3", "unit", "Hz");
		ui_interface.addHorizontalSlider("Transition Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider3"; }
				public void set(float val) { fHslider3 = val; }
				public float get() { return (float)fHslider3; }
			}
			, 200.0f, 1.0f, 5000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.declare("0", "tooltip", "Parametric Equalizer   sections from filters.lib");
		ui_interface.openVerticalBox("Peaking Equalizer");
		ui_interface.declare("fHslider6", "0", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "Amount of   local boost or cut in decibels");
		ui_interface.declare("fHslider6", "unit", "dB");
		ui_interface.addHorizontalSlider("Peak Boost|Cut", new FaustVarAccess() {
				public String getId() { return "fHslider6"; }
				public void set(float val) { fHslider6 = val; }
				public float get() { return (float)fHslider6; }
			}
			, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "tooltip", "Peak   Frequency in Piano Key (PK) units (A440 = 49PK)");
		ui_interface.declare("fHslider5", "unit", "PK");
		ui_interface.addHorizontalSlider("Peak Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider5"; }
				public void set(float val) { fHslider5 = val; }
				public float get() { return (float)fHslider5; }
			}
			, 49.0f, 1.0f, 100.0f, 1.0f);
		ui_interface.declare("fHslider7", "2", "");
		ui_interface.declare("fHslider7", "scale", "log");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.declare("fHslider7", "tooltip", "Quality factor   (Q) of the peak = center-frequency/bandwidth");
		ui_interface.addHorizontalSlider("Peak Q", new FaustVarAccess() {
				public String getId() { return "fHslider7"; }
				public void set(float val) { fHslider7 = val; }
				public float get() { return (float)fHslider7; }
			}
			, 40.0f, 1.0f, 1000.0f, 0.100000001f);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.declare("0", "tooltip", "A high shelf provides a boost   or cut above some frequency");
		ui_interface.openVerticalBox("High Shelf");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.declare("fHslider8", "tooltip", "Amount of   high-frequency boost or cut in decibels");
		ui_interface.declare("fHslider8", "unit", "dB");
		ui_interface.addHorizontalSlider("High Boost|Cut", new FaustVarAccess() {
				public String getId() { return "fHslider8"; }
				public void set(float val) { fHslider8 = val; }
				public float get() { return (float)fHslider8; }
			}
			, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "scale", "log");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "Transition-frequency from boost (cut) to unity gain");
		ui_interface.declare("fHslider2", "unit", "Hz");
		ui_interface.addHorizontalSlider("Transition Frequency", new FaustVarAccess() {
				public String getId() { return "fHslider2"; }
				public void set(float val) { fHslider2 = val; }
				public float get() { return (float)fHslider2; }
			}
			, 8000.0f, 20.0f, 10000.0f, 1.0f);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 20 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph19", "0", "");
		ui_interface.declare("fVbargraph19", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph19", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbaec7810", new FaustVarAccess() {
				public String getId() { return "fVbargraph19"; }
				public void set(float val) { fVbargraph19 = val; }
				public float get() { return (float)fVbargraph19; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph18", "1", "");
		ui_interface.declare("fVbargraph18", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph18", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbaeb5eb0", new FaustVarAccess() {
				public String getId() { return "fVbargraph18"; }
				public void set(float val) { fVbargraph18 = val; }
				public float get() { return (float)fVbargraph18; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph17", "2", "");
		ui_interface.declare("fVbargraph17", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph17", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbae93d60", new FaustVarAccess() {
				public String getId() { return "fVbargraph17"; }
				public void set(float val) { fVbargraph17 = val; }
				public float get() { return (float)fVbargraph17; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph16", "3", "");
		ui_interface.declare("fVbargraph16", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph16", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbae71c10", new FaustVarAccess() {
				public String getId() { return "fVbargraph16"; }
				public void set(float val) { fVbargraph16 = val; }
				public float get() { return (float)fVbargraph16; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph15", "4", "");
		ui_interface.declare("fVbargraph15", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph15", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbae4fac0", new FaustVarAccess() {
				public String getId() { return "fVbargraph15"; }
				public void set(float val) { fVbargraph15 = val; }
				public float get() { return (float)fVbargraph15; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph14", "5", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbae2d970", new FaustVarAccess() {
				public String getId() { return "fVbargraph14"; }
				public void set(float val) { fVbargraph14 = val; }
				public float get() { return (float)fVbargraph14; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph13", "6", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbae0b820", new FaustVarAccess() {
				public String getId() { return "fVbargraph13"; }
				public void set(float val) { fVbargraph13 = val; }
				public float get() { return (float)fVbargraph13; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph12", "7", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbade5750", new FaustVarAccess() {
				public String getId() { return "fVbargraph12"; }
				public void set(float val) { fVbargraph12 = val; }
				public float get() { return (float)fVbargraph12; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph11", "8", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbadc3600", new FaustVarAccess() {
				public String getId() { return "fVbargraph11"; }
				public void set(float val) { fVbargraph11 = val; }
				public float get() { return (float)fVbargraph11; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph10", "9", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbada14b0", new FaustVarAccess() {
				public String getId() { return "fVbargraph10"; }
				public void set(float val) { fVbargraph10 = val; }
				public float get() { return (float)fVbargraph10; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph9", "10", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbad7f360", new FaustVarAccess() {
				public String getId() { return "fVbargraph9"; }
				public void set(float val) { fVbargraph9 = val; }
				public float get() { return (float)fVbargraph9; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph8", "11", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbad5d210", new FaustVarAccess() {
				public String getId() { return "fVbargraph8"; }
				public void set(float val) { fVbargraph8 = val; }
				public float get() { return (float)fVbargraph8; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph7", "12", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbad3b0c0", new FaustVarAccess() {
				public String getId() { return "fVbargraph7"; }
				public void set(float val) { fVbargraph7 = val; }
				public float get() { return (float)fVbargraph7; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph6", "13", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbad18f70", new FaustVarAccess() {
				public String getId() { return "fVbargraph6"; }
				public void set(float val) { fVbargraph6 = val; }
				public float get() { return (float)fVbargraph6; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph5", "14", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbacf2ea0", new FaustVarAccess() {
				public String getId() { return "fVbargraph5"; }
				public void set(float val) { fVbargraph5 = val; }
				public float get() { return (float)fVbargraph5; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph4", "15", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbacd0d50", new FaustVarAccess() {
				public String getId() { return "fVbargraph4"; }
				public void set(float val) { fVbargraph4 = val; }
				public float get() { return (float)fVbargraph4; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph3", "16", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbacaec00", new FaustVarAccess() {
				public String getId() { return "fVbargraph3"; }
				public void set(float val) { fVbargraph3 = val; }
				public float get() { return (float)fVbargraph3; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph2", "17", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbac8cab0", new FaustVarAccess() {
				public String getId() { return "fVbargraph2"; }
				public void set(float val) { fVbargraph2 = val; }
				public float get() { return (float)fVbargraph2; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph1", "18", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbac6a960", new FaustVarAccess() {
				public String getId() { return "fVbargraph1"; }
				public void set(float val) { fVbargraph1 = val; }
				public float get() { return (float)fVbargraph1; }
			}
			, -50.0f, 10.0f);
		ui_interface.declare("fVbargraph0", "19", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7febbac47780", new FaustVarAccess() {
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
		float fSlow3 = (float)java.lang.Math.tan((fConst14 * fHslider2));
		float fSlow4 = (1.0f / fSlow3);
		float fSlow5 = (1.0f / (((fSlow4 + 1.0f) / fSlow3) + 1.0f));
		float fSlow6 = (fSlow4 + 1.0f);
		float fSlow7 = (0.0f - ((1.0f - fSlow4) / fSlow6));
		float fSlow8 = (1.0f / fSlow6);
		float fSlow9 = (float)java.lang.Math.tan((fConst14 * fHslider3));
		float fSlow10 = (1.0f / fSlow9);
		float fSlow11 = (1.0f / (((fSlow10 + 1.0f) / fSlow9) + 1.0f));
		float fSlow12 = (1.0f / mydsp_faustpower2_f(fSlow9));
		float fSlow13 = (2.0f * (0.0f - fSlow12));
		float fSlow14 = (fSlow10 + 1.0f);
		float fSlow15 = (0.0f - ((1.0f - fSlow10) / fSlow14));
		float fSlow16 = (1.0f / fSlow14);
		float fSlow17 = (0.0f - fSlow10);
		float fSlow18 = (0.00100000005f * (float)java.lang.Math.pow(10.0f, (0.0500000007f * fVslider0)));
		int iSlow19 = (int)fCheckbox0;
		int iSlow20 = (int)fCheckbox1;
		int iSlow21 = (int)(fEntry0 + -1.0f);
		int iSlow22 = (iSlow21 >= 2);
		int iSlow23 = (iSlow21 >= 1);
		float fSlow24 = (float)java.lang.Math.exp((0.0f - (fConst15 / fVslider2)));
		float fSlow25 = (440.0f * ((float)java.lang.Math.pow(2.0f, (0.0833333358f * (fVslider1 + -49.0f))) * (1.0f - fSlow24)));
		int iSlow26 = (iSlow21 >= 3);
		float fSlow27 = ((0.00999999978f * fVslider3) + 1.0f);
		float fSlow28 = ((0.00999999978f * fVslider4) + 1.0f);
		int iSlow29 = (int)fCheckbox2;
		float fSlow30 = (((fSlow10 + -1.0f) / fSlow9) + 1.0f);
		float fSlow31 = (2.0f * (1.0f - fSlow12));
		float fSlow32 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider4));
		float fSlow33 = (0.00100000005f * fHslider5);
		float fSlow34 = fHslider6;
		int iSlow35 = (fSlow34 > 0.0f);
		float fSlow36 = fHslider7;
		float fSlow37 = (fConst20 * ((float)java.lang.Math.pow(10.0f, (0.0500000007f * (float)java.lang.Math.abs(fSlow34))) / fSlow36));
		float fSlow38 = (fConst20 / fSlow36);
		float fSlow39 = (1.0f / mydsp_faustpower2_f(fSlow3));
		float fSlow40 = (2.0f * (1.0f - fSlow39));
		float fSlow41 = (((fSlow4 + -1.0f) / fSlow3) + 1.0f);
		float fSlow42 = (float)java.lang.Math.pow(10.0f, (0.0500000007f * fHslider8));
		float fSlow43 = (2.0f * (0.0f - fSlow39));
		float fSlow44 = (0.0f - fSlow4);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec9[0] = (fSlow18 + (0.999000013f * fRec9[1]));
			fRec11[0] = (fSlow25 + (fSlow24 * fRec11[1]));
			float fTemp0 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs(fRec11[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec10[1] + (fConst15 * fVec1[1]));
			fRec10[0] = (fTemp1 - (float)java.lang.Math.floor(fTemp1));
			float fTemp2 = (2.0f * fRec10[0]);
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
			float fTemp10 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow27 * fRec11[0])));
			fVec8[0] = fTemp10;
			float fTemp11 = (fRec12[1] + (fConst15 * fVec8[1]));
			fRec12[0] = (fTemp11 - (float)java.lang.Math.floor(fTemp11));
			float fTemp12 = (2.0f * fRec12[0]);
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
			float fTemp20 = (float)java.lang.Math.max(20.0f, (float)java.lang.Math.abs((fSlow28 * fRec11[0])));
			fVec15[0] = fTemp20;
			float fTemp21 = (fRec13[1] + (fConst15 * fVec15[1]));
			fRec13[0] = (fTemp21 - (float)java.lang.Math.floor(fTemp21));
			float fTemp22 = (2.0f * fRec13[0]);
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
			iRec14[0] = ((1103515245 * iRec14[1]) + 12345);
			float fTemp30 = (4.65661287e-10f * (float)iRec14[0]);
			fRec15[0] = (((0.522189379f * fRec15[3]) + (fTemp30 + (2.49495602f * fRec15[1]))) - (2.0172658f * fRec15[2]));
			float fTemp31 = (fRec9[0] * (((iSlow19==0)?true:false)?input0[i]:(((iSlow20==0)?true:false)?(((iSlow29==0)?true:false)?(((0.0499220341f * fRec15[0]) + (0.0506126992f * fRec15[2])) - ((0.0959935337f * fRec15[1]) + (0.00440878607f * fRec15[3]))):fTemp30):(0.333333343f * (fRec9[0] * (((((iSlow22==0)?true:false)?(((iSlow26==0)?true:false)?(fConst18 * (((float)iVec0[3] * (fTemp9 - fVec7[1])) / fTemp0)):(fConst17 * (((float)iVec0[2] * (fTemp6 - fVec4[1])) / fTemp0))):(((iSlow23==0)?true:false)?(fConst16 * (((float)iVec0[1] * (fTemp4 - fVec2[1])) / fTemp0)):fTemp3)) + (((iSlow22==0)?true:false)?(((iSlow26==0)?true:false)?(fConst18 * (((float)iVec0[3] * (fTemp19 - fVec14[1])) / fTemp10)):(fConst17 * (((float)iVec0[2] * (fTemp16 - fVec11[1])) / fTemp10))):(((iSlow23==0)?true:false)?(fConst16 * (((float)iVec0[1] * (fTemp14 - fVec9[1])) / fTemp10)):fTemp13))) + (((iSlow22==0)?true:false)?(((iSlow26==0)?true:false)?(fConst18 * (((float)iVec0[3] * (fTemp29 - fVec21[1])) / fTemp20)):(fConst17 * (((float)iVec0[2] * (fTemp26 - fVec18[1])) / fTemp20))):(((iSlow23==0)?true:false)?(fConst16 * (((float)iVec0[1] * (fTemp24 - fVec16[1])) / fTemp20)):fTemp23))))))));
			fVec22[0] = fTemp31;
			fRec8[0] = ((fSlow15 * fRec8[1]) + (fSlow16 * ((fSlow17 * fVec22[1]) + (fSlow10 * fTemp31))));
			fRec7[0] = (fRec8[0] - (fSlow11 * ((fSlow30 * fRec7[2]) + (fSlow31 * fRec7[1]))));
			fRec17[0] = ((fSlow15 * fRec17[1]) + (fSlow16 * (fTemp31 + fVec22[1])));
			fRec16[0] = (fRec17[0] - (fSlow11 * ((fSlow31 * fRec16[1]) + (fSlow30 * fRec16[2]))));
			fRec18[0] = (fSlow33 + (0.999000013f * fRec18[1]));
			float fTemp32 = (float)java.lang.Math.pow(2.0f, (0.0833333358f * (fRec18[0] + -49.0f)));
			float fTemp33 = (float)java.lang.Math.tan((fConst19 * fTemp32));
			float fTemp34 = (1.0f / fTemp33);
			float fTemp35 = (fTemp32 / (float)java.lang.Math.sin((fConst21 * fTemp32)));
			float fTemp36 = (fSlow37 * fTemp35);
			float fTemp37 = (fSlow38 * fTemp35);
			float fTemp38 = (((iSlow35==0)?true:false)?fTemp37:fTemp36);
			float fTemp39 = (2.0f * (fRec6[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp33)))));
			float fTemp40 = (((fTemp34 + fTemp38) / fTemp33) + 1.0f);
			fRec6[0] = ((fSlow11 * ((((fSlow13 * fRec7[1]) + (fSlow12 * fRec7[0])) + (fSlow12 * fRec7[2])) + (fSlow32 * (fRec16[2] + (fRec16[0] + (2.0f * fRec16[1])))))) - (((fRec6[2] * (((fTemp34 - fTemp38) / fTemp33) + 1.0f)) + fTemp39) / fTemp40));
			float fTemp41 = (((iSlow35==0)?true:false)?fTemp36:fTemp37);
			float fTemp42 = (((fTemp39 + (fRec6[0] * (((fTemp34 + fTemp41) / fTemp33) + 1.0f))) + (fRec6[2] * (((fTemp34 - fTemp41) / fTemp33) + 1.0f))) / fTemp40);
			fVec23[0] = fTemp42;
			fRec5[0] = ((fSlow7 * fRec5[1]) + (fSlow8 * (fTemp42 + fVec23[1])));
			fRec4[0] = (fRec5[0] - (fSlow5 * ((fSlow40 * fRec4[1]) + (fSlow41 * fRec4[2]))));
			fRec20[0] = ((fSlow7 * fRec20[1]) + (fSlow8 * ((fSlow44 * fVec23[1]) + (fSlow4 * fTemp42))));
			fRec19[0] = (fRec20[0] - (fSlow5 * ((fSlow41 * fRec19[2]) + (fSlow40 * fRec19[1]))));
			float fTemp43 = (fSlow5 * ((fRec4[2] + (fRec4[0] + (2.0f * fRec4[1]))) + (fSlow42 * (((fSlow43 * fRec19[1]) + (fSlow39 * fRec19[0])) + (fSlow39 * fRec19[2])))));
			fRec3[0] = (fTemp43 - (fConst11 * ((fConst22 * fRec3[2]) + (fConst24 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[1]) + (fConst25 * fRec3[0])) + (fConst25 * fRec3[2]))) - (fConst8 * ((fConst26 * fRec2[2]) + (fConst27 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[1]) + (fConst28 * fRec2[0])) + (fConst28 * fRec2[2]))) - (fConst4 * ((fConst29 * fRec1[2]) + (fConst30 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst4 * (((fConst7 * fRec1[1]) + (fConst31 * fRec1[0])) + (fConst31 * fRec1[2]))))));
			fVbargraph0 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec0[0]))));
			fRec27[0] = (fTemp43 - (fConst48 * ((fConst51 * fRec27[2]) + (fConst52 * fRec27[1]))));
			fRec26[0] = ((fConst48 * (((fConst50 * fRec27[1]) + (fConst53 * fRec27[0])) + (fConst53 * fRec27[2]))) - (fConst46 * ((fConst54 * fRec26[2]) + (fConst55 * fRec26[1]))));
			fRec25[0] = ((fConst46 * (((fConst47 * fRec26[1]) + (fConst56 * fRec26[0])) + (fConst56 * fRec26[2]))) - (fConst44 * ((fConst57 * fRec25[2]) + (fConst58 * fRec25[1]))));
			float fTemp44 = (fConst44 * (((fConst45 * fRec25[1]) + (fConst59 * fRec25[0])) + (fConst59 * fRec25[2])));
			fRec24[0] = (fTemp44 - (fConst41 * ((fConst60 * fRec24[2]) + (fConst62 * fRec24[1]))));
			fRec23[0] = ((fConst41 * (((fConst43 * fRec24[1]) + (fConst63 * fRec24[0])) + (fConst63 * fRec24[2]))) - (fConst38 * ((fConst64 * fRec23[2]) + (fConst65 * fRec23[1]))));
			fRec22[0] = ((fConst38 * (((fConst40 * fRec23[1]) + (fConst66 * fRec23[0])) + (fConst66 * fRec23[2]))) - (fConst34 * ((fConst67 * fRec22[2]) + (fConst68 * fRec22[1]))));
			fRec21[0] = ((fSlow1 * fRec21[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst34 * (((fConst37 * fRec22[1]) + (fConst69 * fRec22[0])) + (fConst69 * fRec22[2]))))));
			fVbargraph1 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec21[0]))));
			fRec34[0] = (fTemp44 - (fConst86 * ((fConst89 * fRec34[2]) + (fConst90 * fRec34[1]))));
			fRec33[0] = ((fConst86 * (((fConst88 * fRec34[1]) + (fConst91 * fRec34[0])) + (fConst91 * fRec34[2]))) - (fConst84 * ((fConst92 * fRec33[2]) + (fConst93 * fRec33[1]))));
			fRec32[0] = ((fConst84 * (((fConst85 * fRec33[1]) + (fConst94 * fRec33[0])) + (fConst94 * fRec33[2]))) - (fConst82 * ((fConst95 * fRec32[2]) + (fConst96 * fRec32[1]))));
			float fTemp45 = (fConst82 * (((fConst83 * fRec32[1]) + (fConst97 * fRec32[0])) + (fConst97 * fRec32[2])));
			fRec31[0] = (fTemp45 - (fConst79 * ((fConst98 * fRec31[2]) + (fConst100 * fRec31[1]))));
			fRec30[0] = ((fConst79 * (((fConst81 * fRec31[1]) + (fConst101 * fRec31[0])) + (fConst101 * fRec31[2]))) - (fConst76 * ((fConst102 * fRec30[2]) + (fConst103 * fRec30[1]))));
			fRec29[0] = ((fConst76 * (((fConst78 * fRec30[1]) + (fConst104 * fRec30[0])) + (fConst104 * fRec30[2]))) - (fConst72 * ((fConst105 * fRec29[2]) + (fConst106 * fRec29[1]))));
			fRec28[0] = ((fSlow1 * fRec28[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst72 * (((fConst75 * fRec29[1]) + (fConst107 * fRec29[0])) + (fConst107 * fRec29[2]))))));
			fVbargraph2 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec28[0]))));
			fRec41[0] = (fTemp45 - (fConst124 * ((fConst127 * fRec41[2]) + (fConst128 * fRec41[1]))));
			fRec40[0] = ((fConst124 * (((fConst126 * fRec41[1]) + (fConst129 * fRec41[0])) + (fConst129 * fRec41[2]))) - (fConst122 * ((fConst130 * fRec40[2]) + (fConst131 * fRec40[1]))));
			fRec39[0] = ((fConst122 * (((fConst123 * fRec40[1]) + (fConst132 * fRec40[0])) + (fConst132 * fRec40[2]))) - (fConst120 * ((fConst133 * fRec39[2]) + (fConst134 * fRec39[1]))));
			float fTemp46 = (fConst120 * (((fConst121 * fRec39[1]) + (fConst135 * fRec39[0])) + (fConst135 * fRec39[2])));
			fRec38[0] = (fTemp46 - (fConst117 * ((fConst136 * fRec38[2]) + (fConst138 * fRec38[1]))));
			fRec37[0] = ((fConst117 * (((fConst119 * fRec38[1]) + (fConst139 * fRec38[0])) + (fConst139 * fRec38[2]))) - (fConst114 * ((fConst140 * fRec37[2]) + (fConst141 * fRec37[1]))));
			fRec36[0] = ((fConst114 * (((fConst116 * fRec37[1]) + (fConst142 * fRec37[0])) + (fConst142 * fRec37[2]))) - (fConst110 * ((fConst143 * fRec36[2]) + (fConst144 * fRec36[1]))));
			fRec35[0] = ((fSlow1 * fRec35[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst110 * (((fConst113 * fRec36[1]) + (fConst145 * fRec36[0])) + (fConst145 * fRec36[2]))))));
			fVbargraph3 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec35[0]))));
			fRec48[0] = (fTemp46 - (fConst162 * ((fConst165 * fRec48[2]) + (fConst166 * fRec48[1]))));
			fRec47[0] = ((fConst162 * (((fConst164 * fRec48[1]) + (fConst167 * fRec48[0])) + (fConst167 * fRec48[2]))) - (fConst160 * ((fConst168 * fRec47[2]) + (fConst169 * fRec47[1]))));
			fRec46[0] = ((fConst160 * (((fConst161 * fRec47[1]) + (fConst170 * fRec47[0])) + (fConst170 * fRec47[2]))) - (fConst158 * ((fConst171 * fRec46[2]) + (fConst172 * fRec46[1]))));
			float fTemp47 = (fConst158 * (((fConst159 * fRec46[1]) + (fConst173 * fRec46[0])) + (fConst173 * fRec46[2])));
			fRec45[0] = (fTemp47 - (fConst155 * ((fConst174 * fRec45[2]) + (fConst176 * fRec45[1]))));
			fRec44[0] = ((fConst155 * (((fConst157 * fRec45[1]) + (fConst177 * fRec45[0])) + (fConst177 * fRec45[2]))) - (fConst152 * ((fConst178 * fRec44[2]) + (fConst179 * fRec44[1]))));
			fRec43[0] = ((fConst152 * (((fConst154 * fRec44[1]) + (fConst180 * fRec44[0])) + (fConst180 * fRec44[2]))) - (fConst148 * ((fConst181 * fRec43[2]) + (fConst182 * fRec43[1]))));
			fRec42[0] = ((fSlow1 * fRec42[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst148 * (((fConst151 * fRec43[1]) + (fConst183 * fRec43[0])) + (fConst183 * fRec43[2]))))));
			fVbargraph4 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec42[0]))));
			fRec55[0] = (fTemp47 - (fConst200 * ((fConst203 * fRec55[2]) + (fConst204 * fRec55[1]))));
			fRec54[0] = ((fConst200 * (((fConst202 * fRec55[1]) + (fConst205 * fRec55[0])) + (fConst205 * fRec55[2]))) - (fConst198 * ((fConst206 * fRec54[2]) + (fConst207 * fRec54[1]))));
			fRec53[0] = ((fConst198 * (((fConst199 * fRec54[1]) + (fConst208 * fRec54[0])) + (fConst208 * fRec54[2]))) - (fConst196 * ((fConst209 * fRec53[2]) + (fConst210 * fRec53[1]))));
			float fTemp48 = (fConst196 * (((fConst197 * fRec53[1]) + (fConst211 * fRec53[0])) + (fConst211 * fRec53[2])));
			fRec52[0] = (fTemp48 - (fConst193 * ((fConst212 * fRec52[2]) + (fConst214 * fRec52[1]))));
			fRec51[0] = ((fConst193 * (((fConst195 * fRec52[1]) + (fConst215 * fRec52[0])) + (fConst215 * fRec52[2]))) - (fConst190 * ((fConst216 * fRec51[2]) + (fConst217 * fRec51[1]))));
			fRec50[0] = ((fConst190 * (((fConst192 * fRec51[1]) + (fConst218 * fRec51[0])) + (fConst218 * fRec51[2]))) - (fConst186 * ((fConst219 * fRec50[2]) + (fConst220 * fRec50[1]))));
			fRec49[0] = ((fSlow1 * fRec49[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst186 * (((fConst189 * fRec50[1]) + (fConst221 * fRec50[0])) + (fConst221 * fRec50[2]))))));
			fVbargraph5 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec49[0]))));
			fRec62[0] = (fTemp48 - (fConst238 * ((fConst241 * fRec62[2]) + (fConst242 * fRec62[1]))));
			fRec61[0] = ((fConst238 * (((fConst240 * fRec62[1]) + (fConst243 * fRec62[0])) + (fConst243 * fRec62[2]))) - (fConst236 * ((fConst244 * fRec61[2]) + (fConst245 * fRec61[1]))));
			fRec60[0] = ((fConst236 * (((fConst237 * fRec61[1]) + (fConst246 * fRec61[0])) + (fConst246 * fRec61[2]))) - (fConst234 * ((fConst247 * fRec60[2]) + (fConst248 * fRec60[1]))));
			float fTemp49 = (fConst234 * (((fConst235 * fRec60[1]) + (fConst249 * fRec60[0])) + (fConst249 * fRec60[2])));
			fRec59[0] = (fTemp49 - (fConst231 * ((fConst250 * fRec59[2]) + (fConst252 * fRec59[1]))));
			fRec58[0] = ((fConst231 * (((fConst233 * fRec59[1]) + (fConst253 * fRec59[0])) + (fConst253 * fRec59[2]))) - (fConst228 * ((fConst254 * fRec58[2]) + (fConst255 * fRec58[1]))));
			fRec57[0] = ((fConst228 * (((fConst230 * fRec58[1]) + (fConst256 * fRec58[0])) + (fConst256 * fRec58[2]))) - (fConst224 * ((fConst257 * fRec57[2]) + (fConst258 * fRec57[1]))));
			fRec56[0] = ((fSlow1 * fRec56[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst224 * (((fConst227 * fRec57[1]) + (fConst259 * fRec57[0])) + (fConst259 * fRec57[2]))))));
			fVbargraph6 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec56[0]))));
			fRec69[0] = (fTemp49 - (fConst276 * ((fConst279 * fRec69[2]) + (fConst280 * fRec69[1]))));
			fRec68[0] = ((fConst276 * (((fConst278 * fRec69[1]) + (fConst281 * fRec69[0])) + (fConst281 * fRec69[2]))) - (fConst274 * ((fConst282 * fRec68[2]) + (fConst283 * fRec68[1]))));
			fRec67[0] = ((fConst274 * (((fConst275 * fRec68[1]) + (fConst284 * fRec68[0])) + (fConst284 * fRec68[2]))) - (fConst272 * ((fConst285 * fRec67[2]) + (fConst286 * fRec67[1]))));
			float fTemp50 = (fConst272 * (((fConst273 * fRec67[1]) + (fConst287 * fRec67[0])) + (fConst287 * fRec67[2])));
			fRec66[0] = (fTemp50 - (fConst269 * ((fConst288 * fRec66[2]) + (fConst290 * fRec66[1]))));
			fRec65[0] = ((fConst269 * (((fConst271 * fRec66[1]) + (fConst291 * fRec66[0])) + (fConst291 * fRec66[2]))) - (fConst266 * ((fConst292 * fRec65[2]) + (fConst293 * fRec65[1]))));
			fRec64[0] = ((fConst266 * (((fConst268 * fRec65[1]) + (fConst294 * fRec65[0])) + (fConst294 * fRec65[2]))) - (fConst262 * ((fConst295 * fRec64[2]) + (fConst296 * fRec64[1]))));
			fRec63[0] = ((fSlow1 * fRec63[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst262 * (((fConst265 * fRec64[1]) + (fConst297 * fRec64[0])) + (fConst297 * fRec64[2]))))));
			fVbargraph7 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec63[0]))));
			fRec76[0] = (fTemp50 - (fConst314 * ((fConst317 * fRec76[2]) + (fConst318 * fRec76[1]))));
			fRec75[0] = ((fConst314 * (((fConst316 * fRec76[1]) + (fConst319 * fRec76[0])) + (fConst319 * fRec76[2]))) - (fConst312 * ((fConst320 * fRec75[2]) + (fConst321 * fRec75[1]))));
			fRec74[0] = ((fConst312 * (((fConst313 * fRec75[1]) + (fConst322 * fRec75[0])) + (fConst322 * fRec75[2]))) - (fConst310 * ((fConst323 * fRec74[2]) + (fConst324 * fRec74[1]))));
			float fTemp51 = (fConst310 * (((fConst311 * fRec74[1]) + (fConst325 * fRec74[0])) + (fConst325 * fRec74[2])));
			fRec73[0] = (fTemp51 - (fConst307 * ((fConst326 * fRec73[2]) + (fConst328 * fRec73[1]))));
			fRec72[0] = ((fConst307 * (((fConst309 * fRec73[1]) + (fConst329 * fRec73[0])) + (fConst329 * fRec73[2]))) - (fConst304 * ((fConst330 * fRec72[2]) + (fConst331 * fRec72[1]))));
			fRec71[0] = ((fConst304 * (((fConst306 * fRec72[1]) + (fConst332 * fRec72[0])) + (fConst332 * fRec72[2]))) - (fConst300 * ((fConst333 * fRec71[2]) + (fConst334 * fRec71[1]))));
			fRec70[0] = ((fSlow1 * fRec70[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst300 * (((fConst303 * fRec71[1]) + (fConst335 * fRec71[0])) + (fConst335 * fRec71[2]))))));
			fVbargraph8 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec70[0]))));
			fRec83[0] = (fTemp51 - (fConst352 * ((fConst355 * fRec83[2]) + (fConst356 * fRec83[1]))));
			fRec82[0] = ((fConst352 * (((fConst354 * fRec83[1]) + (fConst357 * fRec83[0])) + (fConst357 * fRec83[2]))) - (fConst350 * ((fConst358 * fRec82[2]) + (fConst359 * fRec82[1]))));
			fRec81[0] = ((fConst350 * (((fConst351 * fRec82[1]) + (fConst360 * fRec82[0])) + (fConst360 * fRec82[2]))) - (fConst348 * ((fConst361 * fRec81[2]) + (fConst362 * fRec81[1]))));
			float fTemp52 = (fConst348 * (((fConst349 * fRec81[1]) + (fConst363 * fRec81[0])) + (fConst363 * fRec81[2])));
			fRec80[0] = (fTemp52 - (fConst345 * ((fConst364 * fRec80[2]) + (fConst366 * fRec80[1]))));
			fRec79[0] = ((fConst345 * (((fConst347 * fRec80[1]) + (fConst367 * fRec80[0])) + (fConst367 * fRec80[2]))) - (fConst342 * ((fConst368 * fRec79[2]) + (fConst369 * fRec79[1]))));
			fRec78[0] = ((fConst342 * (((fConst344 * fRec79[1]) + (fConst370 * fRec79[0])) + (fConst370 * fRec79[2]))) - (fConst338 * ((fConst371 * fRec78[2]) + (fConst372 * fRec78[1]))));
			fRec77[0] = ((fSlow1 * fRec77[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst338 * (((fConst341 * fRec78[1]) + (fConst373 * fRec78[0])) + (fConst373 * fRec78[2]))))));
			fVbargraph9 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec77[0]))));
			fRec90[0] = (fTemp52 - (fConst390 * ((fConst393 * fRec90[2]) + (fConst394 * fRec90[1]))));
			fRec89[0] = ((fConst390 * (((fConst392 * fRec90[1]) + (fConst395 * fRec90[0])) + (fConst395 * fRec90[2]))) - (fConst388 * ((fConst396 * fRec89[2]) + (fConst397 * fRec89[1]))));
			fRec88[0] = ((fConst388 * (((fConst389 * fRec89[1]) + (fConst398 * fRec89[0])) + (fConst398 * fRec89[2]))) - (fConst386 * ((fConst399 * fRec88[2]) + (fConst400 * fRec88[1]))));
			float fTemp53 = (fConst386 * (((fConst387 * fRec88[1]) + (fConst401 * fRec88[0])) + (fConst401 * fRec88[2])));
			fRec87[0] = (fTemp53 - (fConst383 * ((fConst402 * fRec87[2]) + (fConst404 * fRec87[1]))));
			fRec86[0] = ((fConst383 * (((fConst385 * fRec87[1]) + (fConst405 * fRec87[0])) + (fConst405 * fRec87[2]))) - (fConst380 * ((fConst406 * fRec86[2]) + (fConst407 * fRec86[1]))));
			fRec85[0] = ((fConst380 * (((fConst382 * fRec86[1]) + (fConst408 * fRec86[0])) + (fConst408 * fRec86[2]))) - (fConst376 * ((fConst409 * fRec85[2]) + (fConst410 * fRec85[1]))));
			fRec84[0] = ((fSlow1 * fRec84[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst376 * (((fConst379 * fRec85[1]) + (fConst411 * fRec85[0])) + (fConst411 * fRec85[2]))))));
			fVbargraph10 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec84[0]))));
			fRec97[0] = (fTemp53 - (fConst428 * ((fConst431 * fRec97[2]) + (fConst432 * fRec97[1]))));
			fRec96[0] = ((fConst428 * (((fConst430 * fRec97[1]) + (fConst433 * fRec97[0])) + (fConst433 * fRec97[2]))) - (fConst426 * ((fConst434 * fRec96[2]) + (fConst435 * fRec96[1]))));
			fRec95[0] = ((fConst426 * (((fConst427 * fRec96[1]) + (fConst436 * fRec96[0])) + (fConst436 * fRec96[2]))) - (fConst424 * ((fConst437 * fRec95[2]) + (fConst438 * fRec95[1]))));
			float fTemp54 = (fConst424 * (((fConst425 * fRec95[1]) + (fConst439 * fRec95[0])) + (fConst439 * fRec95[2])));
			fRec94[0] = (fTemp54 - (fConst421 * ((fConst440 * fRec94[2]) + (fConst442 * fRec94[1]))));
			fRec93[0] = ((fConst421 * (((fConst423 * fRec94[1]) + (fConst443 * fRec94[0])) + (fConst443 * fRec94[2]))) - (fConst418 * ((fConst444 * fRec93[2]) + (fConst445 * fRec93[1]))));
			fRec92[0] = ((fConst418 * (((fConst420 * fRec93[1]) + (fConst446 * fRec93[0])) + (fConst446 * fRec93[2]))) - (fConst414 * ((fConst447 * fRec92[2]) + (fConst448 * fRec92[1]))));
			fRec91[0] = ((fSlow1 * fRec91[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst414 * (((fConst417 * fRec92[1]) + (fConst449 * fRec92[0])) + (fConst449 * fRec92[2]))))));
			fVbargraph11 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec91[0]))));
			fRec104[0] = (fTemp54 - (fConst466 * ((fConst469 * fRec104[2]) + (fConst470 * fRec104[1]))));
			fRec103[0] = ((fConst466 * (((fConst468 * fRec104[1]) + (fConst471 * fRec104[0])) + (fConst471 * fRec104[2]))) - (fConst464 * ((fConst472 * fRec103[2]) + (fConst473 * fRec103[1]))));
			fRec102[0] = ((fConst464 * (((fConst465 * fRec103[1]) + (fConst474 * fRec103[0])) + (fConst474 * fRec103[2]))) - (fConst462 * ((fConst475 * fRec102[2]) + (fConst476 * fRec102[1]))));
			float fTemp55 = (fConst462 * (((fConst463 * fRec102[1]) + (fConst477 * fRec102[0])) + (fConst477 * fRec102[2])));
			fRec101[0] = (fTemp55 - (fConst459 * ((fConst478 * fRec101[2]) + (fConst480 * fRec101[1]))));
			fRec100[0] = ((fConst459 * (((fConst461 * fRec101[1]) + (fConst481 * fRec101[0])) + (fConst481 * fRec101[2]))) - (fConst456 * ((fConst482 * fRec100[2]) + (fConst483 * fRec100[1]))));
			fRec99[0] = ((fConst456 * (((fConst458 * fRec100[1]) + (fConst484 * fRec100[0])) + (fConst484 * fRec100[2]))) - (fConst452 * ((fConst485 * fRec99[2]) + (fConst486 * fRec99[1]))));
			fRec98[0] = ((fSlow1 * fRec98[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst452 * (((fConst455 * fRec99[1]) + (fConst487 * fRec99[0])) + (fConst487 * fRec99[2]))))));
			fVbargraph12 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec98[0]))));
			fRec111[0] = (fTemp55 - (fConst504 * ((fConst507 * fRec111[2]) + (fConst508 * fRec111[1]))));
			fRec110[0] = ((fConst504 * (((fConst506 * fRec111[1]) + (fConst509 * fRec111[0])) + (fConst509 * fRec111[2]))) - (fConst502 * ((fConst510 * fRec110[2]) + (fConst511 * fRec110[1]))));
			fRec109[0] = ((fConst502 * (((fConst503 * fRec110[1]) + (fConst512 * fRec110[0])) + (fConst512 * fRec110[2]))) - (fConst500 * ((fConst513 * fRec109[2]) + (fConst514 * fRec109[1]))));
			float fTemp56 = (fConst500 * (((fConst501 * fRec109[1]) + (fConst515 * fRec109[0])) + (fConst515 * fRec109[2])));
			fRec108[0] = (fTemp56 - (fConst497 * ((fConst516 * fRec108[2]) + (fConst518 * fRec108[1]))));
			fRec107[0] = ((fConst497 * (((fConst499 * fRec108[1]) + (fConst519 * fRec108[0])) + (fConst519 * fRec108[2]))) - (fConst494 * ((fConst520 * fRec107[2]) + (fConst521 * fRec107[1]))));
			fRec106[0] = ((fConst494 * (((fConst496 * fRec107[1]) + (fConst522 * fRec107[0])) + (fConst522 * fRec107[2]))) - (fConst490 * ((fConst523 * fRec106[2]) + (fConst524 * fRec106[1]))));
			fRec105[0] = ((fSlow1 * fRec105[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst490 * (((fConst493 * fRec106[1]) + (fConst525 * fRec106[0])) + (fConst525 * fRec106[2]))))));
			fVbargraph13 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec105[0]))));
			fRec118[0] = (fTemp56 - (fConst542 * ((fConst545 * fRec118[2]) + (fConst546 * fRec118[1]))));
			fRec117[0] = ((fConst542 * (((fConst544 * fRec118[1]) + (fConst547 * fRec118[0])) + (fConst547 * fRec118[2]))) - (fConst540 * ((fConst548 * fRec117[2]) + (fConst549 * fRec117[1]))));
			fRec116[0] = ((fConst540 * (((fConst541 * fRec117[1]) + (fConst550 * fRec117[0])) + (fConst550 * fRec117[2]))) - (fConst538 * ((fConst551 * fRec116[2]) + (fConst552 * fRec116[1]))));
			float fTemp57 = (fConst538 * (((fConst539 * fRec116[1]) + (fConst553 * fRec116[0])) + (fConst553 * fRec116[2])));
			fRec115[0] = (fTemp57 - (fConst535 * ((fConst554 * fRec115[2]) + (fConst556 * fRec115[1]))));
			fRec114[0] = ((fConst535 * (((fConst537 * fRec115[1]) + (fConst557 * fRec115[0])) + (fConst557 * fRec115[2]))) - (fConst532 * ((fConst558 * fRec114[2]) + (fConst559 * fRec114[1]))));
			fRec113[0] = ((fConst532 * (((fConst534 * fRec114[1]) + (fConst560 * fRec114[0])) + (fConst560 * fRec114[2]))) - (fConst528 * ((fConst561 * fRec113[2]) + (fConst562 * fRec113[1]))));
			fRec112[0] = ((fSlow1 * fRec112[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst528 * (((fConst531 * fRec113[1]) + (fConst563 * fRec113[0])) + (fConst563 * fRec113[2]))))));
			fVbargraph14 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec112[0]))));
			fRec125[0] = (fTemp57 - (fConst580 * ((fConst583 * fRec125[2]) + (fConst584 * fRec125[1]))));
			fRec124[0] = ((fConst580 * (((fConst582 * fRec125[1]) + (fConst585 * fRec125[0])) + (fConst585 * fRec125[2]))) - (fConst578 * ((fConst586 * fRec124[2]) + (fConst587 * fRec124[1]))));
			fRec123[0] = ((fConst578 * (((fConst579 * fRec124[1]) + (fConst588 * fRec124[0])) + (fConst588 * fRec124[2]))) - (fConst576 * ((fConst589 * fRec123[2]) + (fConst590 * fRec123[1]))));
			float fTemp58 = (fConst576 * (((fConst577 * fRec123[1]) + (fConst591 * fRec123[0])) + (fConst591 * fRec123[2])));
			fRec122[0] = (fTemp58 - (fConst573 * ((fConst592 * fRec122[2]) + (fConst594 * fRec122[1]))));
			fRec121[0] = ((fConst573 * (((fConst575 * fRec122[1]) + (fConst595 * fRec122[0])) + (fConst595 * fRec122[2]))) - (fConst570 * ((fConst596 * fRec121[2]) + (fConst597 * fRec121[1]))));
			fRec120[0] = ((fConst570 * (((fConst572 * fRec121[1]) + (fConst598 * fRec121[0])) + (fConst598 * fRec121[2]))) - (fConst566 * ((fConst599 * fRec120[2]) + (fConst600 * fRec120[1]))));
			fRec119[0] = ((fSlow1 * fRec119[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst566 * (((fConst569 * fRec120[1]) + (fConst601 * fRec120[0])) + (fConst601 * fRec120[2]))))));
			fVbargraph15 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec119[0]))));
			fRec132[0] = (fTemp58 - (fConst618 * ((fConst621 * fRec132[2]) + (fConst622 * fRec132[1]))));
			fRec131[0] = ((fConst618 * (((fConst620 * fRec132[1]) + (fConst623 * fRec132[0])) + (fConst623 * fRec132[2]))) - (fConst616 * ((fConst624 * fRec131[2]) + (fConst625 * fRec131[1]))));
			fRec130[0] = ((fConst616 * (((fConst617 * fRec131[1]) + (fConst626 * fRec131[0])) + (fConst626 * fRec131[2]))) - (fConst614 * ((fConst627 * fRec130[2]) + (fConst628 * fRec130[1]))));
			float fTemp59 = (fConst614 * (((fConst615 * fRec130[1]) + (fConst629 * fRec130[0])) + (fConst629 * fRec130[2])));
			fRec129[0] = (fTemp59 - (fConst611 * ((fConst630 * fRec129[2]) + (fConst632 * fRec129[1]))));
			fRec128[0] = ((fConst611 * (((fConst613 * fRec129[1]) + (fConst633 * fRec129[0])) + (fConst633 * fRec129[2]))) - (fConst608 * ((fConst634 * fRec128[2]) + (fConst635 * fRec128[1]))));
			fRec127[0] = ((fConst608 * (((fConst610 * fRec128[1]) + (fConst636 * fRec128[0])) + (fConst636 * fRec128[2]))) - (fConst604 * ((fConst637 * fRec127[2]) + (fConst638 * fRec127[1]))));
			fRec126[0] = ((fSlow1 * fRec126[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst604 * (((fConst607 * fRec127[1]) + (fConst639 * fRec127[0])) + (fConst639 * fRec127[2]))))));
			fVbargraph16 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec126[0]))));
			fRec139[0] = (fTemp59 - (fConst656 * ((fConst659 * fRec139[2]) + (fConst660 * fRec139[1]))));
			fRec138[0] = ((fConst656 * (((fConst658 * fRec139[1]) + (fConst661 * fRec139[0])) + (fConst661 * fRec139[2]))) - (fConst654 * ((fConst662 * fRec138[2]) + (fConst663 * fRec138[1]))));
			fRec137[0] = ((fConst654 * (((fConst655 * fRec138[1]) + (fConst664 * fRec138[0])) + (fConst664 * fRec138[2]))) - (fConst652 * ((fConst665 * fRec137[2]) + (fConst666 * fRec137[1]))));
			float fTemp60 = (fConst652 * (((fConst653 * fRec137[1]) + (fConst667 * fRec137[0])) + (fConst667 * fRec137[2])));
			fRec136[0] = (fTemp60 - (fConst649 * ((fConst668 * fRec136[2]) + (fConst670 * fRec136[1]))));
			fRec135[0] = ((fConst649 * (((fConst651 * fRec136[1]) + (fConst671 * fRec136[0])) + (fConst671 * fRec136[2]))) - (fConst646 * ((fConst672 * fRec135[2]) + (fConst673 * fRec135[1]))));
			fRec134[0] = ((fConst646 * (((fConst648 * fRec135[1]) + (fConst674 * fRec135[0])) + (fConst674 * fRec135[2]))) - (fConst642 * ((fConst675 * fRec134[2]) + (fConst676 * fRec134[1]))));
			fRec133[0] = ((fSlow1 * fRec133[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst642 * (((fConst645 * fRec134[1]) + (fConst677 * fRec134[0])) + (fConst677 * fRec134[2]))))));
			fVbargraph17 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec133[0]))));
			fRec146[0] = (fTemp60 - (fConst694 * ((fConst697 * fRec146[2]) + (fConst698 * fRec146[1]))));
			fRec145[0] = ((fConst694 * (((fConst696 * fRec146[1]) + (fConst699 * fRec146[0])) + (fConst699 * fRec146[2]))) - (fConst692 * ((fConst700 * fRec145[2]) + (fConst701 * fRec145[1]))));
			fRec144[0] = ((fConst692 * (((fConst693 * fRec145[1]) + (fConst702 * fRec145[0])) + (fConst702 * fRec145[2]))) - (fConst690 * ((fConst703 * fRec144[2]) + (fConst704 * fRec144[1]))));
			float fTemp61 = (fConst690 * (((fConst691 * fRec144[1]) + (fConst705 * fRec144[0])) + (fConst705 * fRec144[2])));
			fRec143[0] = (fTemp61 - (fConst687 * ((fConst706 * fRec143[2]) + (fConst708 * fRec143[1]))));
			fRec142[0] = ((fConst687 * (((fConst689 * fRec143[1]) + (fConst709 * fRec143[0])) + (fConst709 * fRec143[2]))) - (fConst684 * ((fConst710 * fRec142[2]) + (fConst711 * fRec142[1]))));
			fRec141[0] = ((fConst684 * (((fConst686 * fRec142[1]) + (fConst712 * fRec142[0])) + (fConst712 * fRec142[2]))) - (fConst680 * ((fConst713 * fRec141[2]) + (fConst714 * fRec141[1]))));
			fRec140[0] = ((fSlow1 * fRec140[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst680 * (((fConst683 * fRec141[1]) + (fConst715 * fRec141[0])) + (fConst715 * fRec141[2]))))));
			fVbargraph18 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec140[0]))));
			fRec150[0] = (fTemp61 - (fConst720 * ((fConst723 * fRec150[2]) + (fConst724 * fRec150[1]))));
			fRec149[0] = ((fConst720 * (((fConst722 * fRec150[1]) + (fConst725 * fRec150[0])) + (fConst725 * fRec150[2]))) - (fConst718 * ((fConst726 * fRec149[2]) + (fConst727 * fRec149[1]))));
			fRec148[0] = ((fConst718 * (((fConst719 * fRec149[1]) + (fConst728 * fRec149[0])) + (fConst728 * fRec149[2]))) - (fConst716 * ((fConst729 * fRec148[2]) + (fConst730 * fRec148[1]))));
			fRec147[0] = ((fSlow1 * fRec147[1]) + (fSlow2 * (float)java.lang.Math.abs((fConst716 * (((fConst717 * fRec148[1]) + (fConst731 * fRec148[0])) + (fConst731 * fRec148[2]))))));
			fVbargraph19 = (fSlow0 + (20.0f * (float)java.lang.Math.log10((float)java.lang.Math.max(1.00000001e-07f, fRec147[0]))));
			output0[i] = fTemp43;
			output1[i] = fTemp43;
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
				
			}
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fVec1[1] = fVec1[0];
			fRec10[1] = fRec10[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec12[1] = fRec12[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec13[1] = fRec13[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			iRec14[1] = iRec14[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec15[j1] = fRec15[(j1 - 1)];
				
			}
			fVec22[1] = fVec22[0];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fVec23[1] = fVec23[0];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
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
			fRec118[2] = fRec118[1];
			fRec118[1] = fRec118[0];
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
			fRec112[1] = fRec112[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
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
			fRec119[1] = fRec119[0];
			fRec132[2] = fRec132[1];
			fRec132[1] = fRec132[0];
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
			fRec126[1] = fRec126[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
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
			fRec133[1] = fRec133[0];
			fRec146[2] = fRec146[1];
			fRec146[1] = fRec146[0];
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
			fRec140[1] = fRec140[0];
			fRec150[2] = fRec150[1];
			fRec150[1] = fRec150[0];
			fRec149[2] = fRec149[1];
			fRec149[1] = fRec149[0];
			fRec148[2] = fRec148[1];
			fRec148[1] = fRec148[0];
			fRec147[1] = fRec147[0];
			
		}
		
	}
	
};

