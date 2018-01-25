
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}
this.mydsp_faustpower4_f = function(value) {
	return (((value * value) * value) * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.iVec0 = new Int32Array(4);
	this.fConst2;
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fConst6;
	this.fConst7;
	this.fConst8;
	this.fConst9;
	this.fConst10;
	this.fConst11;
	this.fConst12;
	this.fConst13;
	this.fCheckbox0;
	this.fHslider2;
	this.fRec4 = new Float32Array(2);
	this.fCheckbox1;
	this.fCheckbox2;
	this.fConst14;
	this.fHslider3;
	this.fRec15 = new Float32Array(2);
	this.fCheckbox3;
	this.fHslider4;
	this.fRec17 = new Float32Array(2);
	this.fVslider0;
	this.fRec18 = new Float32Array(2);
	this.fCheckbox4;
	this.fCheckbox5;
	this.fEntry0;
	this.fConst15;
	this.fVslider1;
	this.fVslider2;
	this.fRec20 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fConst16;
	this.fVec2 = new Float32Array(2);
	this.fConst17;
	this.fVec3 = new Float32Array(2);
	this.fVec4 = new Float32Array(2);
	this.fConst18;
	this.fVec5 = new Float32Array(2);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2);
	this.fVslider3;
	this.fVec8 = new Float32Array(2);
	this.fRec21 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fCheckbox6;
	this.iRec23 = new Int32Array(2);
	this.fRec24 = new Float32Array(4);
	this.fConst19;
	this.fConst20;
	this.fRec25 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fRec16 = new Float32Array(3);
	this.fRec14 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fHslider5;
	this.fRec27 = new Float32Array(2);
	this.fHslider6;
	this.fRec9 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fCheckbox7;
	this.fConst21;
	this.fRec30 = new Float32Array(2);
	this.fRec29 = new Float32Array(3);
	this.fRec28 = new Float32Array(3);
	this.fRec33 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fRec36 = new Float32Array(2);
	this.fRec34 = new Float32Array(2);
	this.fConst22;
	this.fConst23;
	this.fConst24;
	this.fRec3 = new Float32Array(3);
	this.fConst25;
	this.fConst26;
	this.fConst27;
	this.fRec2 = new Float32Array(3);
	this.fConst28;
	this.fConst29;
	this.fConst30;
	this.fRec1 = new Float32Array(3);
	this.fConst31;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.fConst32;
	this.fConst33;
	this.fConst34;
	this.fConst35;
	this.fConst36;
	this.fConst37;
	this.fConst38;
	this.fConst39;
	this.fConst40;
	this.fConst41;
	this.fConst42;
	this.fConst43;
	this.fConst44;
	this.fConst45;
	this.fConst46;
	this.fConst47;
	this.fConst48;
	this.fConst49;
	this.fConst50;
	this.fConst51;
	this.fConst52;
	this.fRec43 = new Float32Array(3);
	this.fConst53;
	this.fConst54;
	this.fConst55;
	this.fRec42 = new Float32Array(3);
	this.fConst56;
	this.fConst57;
	this.fConst58;
	this.fRec41 = new Float32Array(3);
	this.fConst59;
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fRec40 = new Float32Array(3);
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fRec39 = new Float32Array(3);
	this.fConst66;
	this.fConst67;
	this.fConst68;
	this.fRec38 = new Float32Array(3);
	this.fConst69;
	this.fRec37 = new Float32Array(2);
	this.fVbargraph1;
	this.fConst70;
	this.fConst71;
	this.fConst72;
	this.fConst73;
	this.fConst74;
	this.fConst75;
	this.fConst76;
	this.fConst77;
	this.fConst78;
	this.fConst79;
	this.fConst80;
	this.fConst81;
	this.fConst82;
	this.fConst83;
	this.fConst84;
	this.fConst85;
	this.fConst86;
	this.fConst87;
	this.fConst88;
	this.fConst89;
	this.fConst90;
	this.fRec50 = new Float32Array(3);
	this.fConst91;
	this.fConst92;
	this.fConst93;
	this.fRec49 = new Float32Array(3);
	this.fConst94;
	this.fConst95;
	this.fConst96;
	this.fRec48 = new Float32Array(3);
	this.fConst97;
	this.fConst98;
	this.fConst99;
	this.fConst100;
	this.fRec47 = new Float32Array(3);
	this.fConst101;
	this.fConst102;
	this.fConst103;
	this.fRec46 = new Float32Array(3);
	this.fConst104;
	this.fConst105;
	this.fConst106;
	this.fRec45 = new Float32Array(3);
	this.fConst107;
	this.fRec44 = new Float32Array(2);
	this.fVbargraph2;
	this.fConst108;
	this.fConst109;
	this.fConst110;
	this.fConst111;
	this.fConst112;
	this.fConst113;
	this.fConst114;
	this.fConst115;
	this.fConst116;
	this.fConst117;
	this.fConst118;
	this.fConst119;
	this.fConst120;
	this.fConst121;
	this.fConst122;
	this.fConst123;
	this.fConst124;
	this.fConst125;
	this.fConst126;
	this.fConst127;
	this.fConst128;
	this.fRec57 = new Float32Array(3);
	this.fConst129;
	this.fConst130;
	this.fConst131;
	this.fRec56 = new Float32Array(3);
	this.fConst132;
	this.fConst133;
	this.fConst134;
	this.fRec55 = new Float32Array(3);
	this.fConst135;
	this.fConst136;
	this.fConst137;
	this.fConst138;
	this.fRec54 = new Float32Array(3);
	this.fConst139;
	this.fConst140;
	this.fConst141;
	this.fRec53 = new Float32Array(3);
	this.fConst142;
	this.fConst143;
	this.fConst144;
	this.fRec52 = new Float32Array(3);
	this.fConst145;
	this.fRec51 = new Float32Array(2);
	this.fVbargraph3;
	this.fConst146;
	this.fConst147;
	this.fConst148;
	this.fConst149;
	this.fConst150;
	this.fConst151;
	this.fConst152;
	this.fConst153;
	this.fConst154;
	this.fConst155;
	this.fConst156;
	this.fConst157;
	this.fConst158;
	this.fConst159;
	this.fConst160;
	this.fConst161;
	this.fConst162;
	this.fConst163;
	this.fConst164;
	this.fConst165;
	this.fConst166;
	this.fRec64 = new Float32Array(3);
	this.fConst167;
	this.fConst168;
	this.fConst169;
	this.fRec63 = new Float32Array(3);
	this.fConst170;
	this.fConst171;
	this.fConst172;
	this.fRec62 = new Float32Array(3);
	this.fConst173;
	this.fConst174;
	this.fConst175;
	this.fConst176;
	this.fRec61 = new Float32Array(3);
	this.fConst177;
	this.fConst178;
	this.fConst179;
	this.fRec60 = new Float32Array(3);
	this.fConst180;
	this.fConst181;
	this.fConst182;
	this.fRec59 = new Float32Array(3);
	this.fConst183;
	this.fRec58 = new Float32Array(2);
	this.fVbargraph4;
	this.fConst184;
	this.fConst185;
	this.fConst186;
	this.fConst187;
	this.fConst188;
	this.fConst189;
	this.fConst190;
	this.fConst191;
	this.fConst192;
	this.fConst193;
	this.fConst194;
	this.fConst195;
	this.fConst196;
	this.fConst197;
	this.fConst198;
	this.fConst199;
	this.fConst200;
	this.fConst201;
	this.fConst202;
	this.fConst203;
	this.fConst204;
	this.fRec71 = new Float32Array(3);
	this.fConst205;
	this.fConst206;
	this.fConst207;
	this.fRec70 = new Float32Array(3);
	this.fConst208;
	this.fConst209;
	this.fConst210;
	this.fRec69 = new Float32Array(3);
	this.fConst211;
	this.fConst212;
	this.fConst213;
	this.fConst214;
	this.fRec68 = new Float32Array(3);
	this.fConst215;
	this.fConst216;
	this.fConst217;
	this.fRec67 = new Float32Array(3);
	this.fConst218;
	this.fConst219;
	this.fConst220;
	this.fRec66 = new Float32Array(3);
	this.fConst221;
	this.fRec65 = new Float32Array(2);
	this.fVbargraph5;
	this.fConst222;
	this.fConst223;
	this.fConst224;
	this.fConst225;
	this.fConst226;
	this.fConst227;
	this.fConst228;
	this.fConst229;
	this.fConst230;
	this.fConst231;
	this.fConst232;
	this.fConst233;
	this.fConst234;
	this.fConst235;
	this.fConst236;
	this.fConst237;
	this.fConst238;
	this.fConst239;
	this.fConst240;
	this.fConst241;
	this.fConst242;
	this.fRec78 = new Float32Array(3);
	this.fConst243;
	this.fConst244;
	this.fConst245;
	this.fRec77 = new Float32Array(3);
	this.fConst246;
	this.fConst247;
	this.fConst248;
	this.fRec76 = new Float32Array(3);
	this.fConst249;
	this.fConst250;
	this.fConst251;
	this.fConst252;
	this.fRec75 = new Float32Array(3);
	this.fConst253;
	this.fConst254;
	this.fConst255;
	this.fRec74 = new Float32Array(3);
	this.fConst256;
	this.fConst257;
	this.fConst258;
	this.fRec73 = new Float32Array(3);
	this.fConst259;
	this.fRec72 = new Float32Array(2);
	this.fVbargraph6;
	this.fConst260;
	this.fConst261;
	this.fConst262;
	this.fConst263;
	this.fConst264;
	this.fConst265;
	this.fConst266;
	this.fConst267;
	this.fConst268;
	this.fConst269;
	this.fConst270;
	this.fConst271;
	this.fConst272;
	this.fConst273;
	this.fConst274;
	this.fConst275;
	this.fConst276;
	this.fConst277;
	this.fConst278;
	this.fConst279;
	this.fConst280;
	this.fRec85 = new Float32Array(3);
	this.fConst281;
	this.fConst282;
	this.fConst283;
	this.fRec84 = new Float32Array(3);
	this.fConst284;
	this.fConst285;
	this.fConst286;
	this.fRec83 = new Float32Array(3);
	this.fConst287;
	this.fConst288;
	this.fConst289;
	this.fConst290;
	this.fRec82 = new Float32Array(3);
	this.fConst291;
	this.fConst292;
	this.fConst293;
	this.fRec81 = new Float32Array(3);
	this.fConst294;
	this.fConst295;
	this.fConst296;
	this.fRec80 = new Float32Array(3);
	this.fConst297;
	this.fRec79 = new Float32Array(2);
	this.fVbargraph7;
	this.fConst298;
	this.fConst299;
	this.fConst300;
	this.fConst301;
	this.fConst302;
	this.fConst303;
	this.fConst304;
	this.fConst305;
	this.fConst306;
	this.fConst307;
	this.fConst308;
	this.fConst309;
	this.fConst310;
	this.fConst311;
	this.fConst312;
	this.fConst313;
	this.fConst314;
	this.fConst315;
	this.fConst316;
	this.fConst317;
	this.fConst318;
	this.fRec92 = new Float32Array(3);
	this.fConst319;
	this.fConst320;
	this.fConst321;
	this.fRec91 = new Float32Array(3);
	this.fConst322;
	this.fConst323;
	this.fConst324;
	this.fRec90 = new Float32Array(3);
	this.fConst325;
	this.fConst326;
	this.fConst327;
	this.fConst328;
	this.fRec89 = new Float32Array(3);
	this.fConst329;
	this.fConst330;
	this.fConst331;
	this.fRec88 = new Float32Array(3);
	this.fConst332;
	this.fConst333;
	this.fConst334;
	this.fRec87 = new Float32Array(3);
	this.fConst335;
	this.fRec86 = new Float32Array(2);
	this.fVbargraph8;
	this.fConst336;
	this.fConst337;
	this.fConst338;
	this.fConst339;
	this.fConst340;
	this.fConst341;
	this.fConst342;
	this.fConst343;
	this.fConst344;
	this.fConst345;
	this.fConst346;
	this.fConst347;
	this.fConst348;
	this.fConst349;
	this.fConst350;
	this.fConst351;
	this.fConst352;
	this.fConst353;
	this.fConst354;
	this.fConst355;
	this.fConst356;
	this.fRec99 = new Float32Array(3);
	this.fConst357;
	this.fConst358;
	this.fConst359;
	this.fRec98 = new Float32Array(3);
	this.fConst360;
	this.fConst361;
	this.fConst362;
	this.fRec97 = new Float32Array(3);
	this.fConst363;
	this.fConst364;
	this.fConst365;
	this.fConst366;
	this.fRec96 = new Float32Array(3);
	this.fConst367;
	this.fConst368;
	this.fConst369;
	this.fRec95 = new Float32Array(3);
	this.fConst370;
	this.fConst371;
	this.fConst372;
	this.fRec94 = new Float32Array(3);
	this.fConst373;
	this.fRec93 = new Float32Array(2);
	this.fVbargraph9;
	this.fConst374;
	this.fConst375;
	this.fConst376;
	this.fConst377;
	this.fConst378;
	this.fConst379;
	this.fConst380;
	this.fConst381;
	this.fConst382;
	this.fConst383;
	this.fConst384;
	this.fConst385;
	this.fConst386;
	this.fConst387;
	this.fConst388;
	this.fConst389;
	this.fConst390;
	this.fConst391;
	this.fConst392;
	this.fConst393;
	this.fConst394;
	this.fRec106 = new Float32Array(3);
	this.fConst395;
	this.fConst396;
	this.fConst397;
	this.fRec105 = new Float32Array(3);
	this.fConst398;
	this.fConst399;
	this.fConst400;
	this.fRec104 = new Float32Array(3);
	this.fConst401;
	this.fConst402;
	this.fConst403;
	this.fConst404;
	this.fRec103 = new Float32Array(3);
	this.fConst405;
	this.fConst406;
	this.fConst407;
	this.fRec102 = new Float32Array(3);
	this.fConst408;
	this.fConst409;
	this.fConst410;
	this.fRec101 = new Float32Array(3);
	this.fConst411;
	this.fRec100 = new Float32Array(2);
	this.fVbargraph10;
	this.fConst412;
	this.fConst413;
	this.fConst414;
	this.fConst415;
	this.fConst416;
	this.fConst417;
	this.fConst418;
	this.fConst419;
	this.fConst420;
	this.fConst421;
	this.fConst422;
	this.fConst423;
	this.fConst424;
	this.fConst425;
	this.fConst426;
	this.fConst427;
	this.fConst428;
	this.fConst429;
	this.fConst430;
	this.fConst431;
	this.fConst432;
	this.fRec113 = new Float32Array(3);
	this.fConst433;
	this.fConst434;
	this.fConst435;
	this.fRec112 = new Float32Array(3);
	this.fConst436;
	this.fConst437;
	this.fConst438;
	this.fRec111 = new Float32Array(3);
	this.fConst439;
	this.fConst440;
	this.fConst441;
	this.fConst442;
	this.fRec110 = new Float32Array(3);
	this.fConst443;
	this.fConst444;
	this.fConst445;
	this.fRec109 = new Float32Array(3);
	this.fConst446;
	this.fConst447;
	this.fConst448;
	this.fRec108 = new Float32Array(3);
	this.fConst449;
	this.fRec107 = new Float32Array(2);
	this.fVbargraph11;
	this.fConst450;
	this.fConst451;
	this.fConst452;
	this.fConst453;
	this.fConst454;
	this.fConst455;
	this.fConst456;
	this.fConst457;
	this.fConst458;
	this.fConst459;
	this.fConst460;
	this.fConst461;
	this.fConst462;
	this.fConst463;
	this.fConst464;
	this.fConst465;
	this.fConst466;
	this.fConst467;
	this.fConst468;
	this.fConst469;
	this.fConst470;
	this.fRec120 = new Float32Array(3);
	this.fConst471;
	this.fConst472;
	this.fConst473;
	this.fRec119 = new Float32Array(3);
	this.fConst474;
	this.fConst475;
	this.fConst476;
	this.fRec118 = new Float32Array(3);
	this.fConst477;
	this.fConst478;
	this.fConst479;
	this.fConst480;
	this.fRec117 = new Float32Array(3);
	this.fConst481;
	this.fConst482;
	this.fConst483;
	this.fRec116 = new Float32Array(3);
	this.fConst484;
	this.fConst485;
	this.fConst486;
	this.fRec115 = new Float32Array(3);
	this.fConst487;
	this.fRec114 = new Float32Array(2);
	this.fVbargraph12;
	this.fConst488;
	this.fConst489;
	this.fConst490;
	this.fConst491;
	this.fConst492;
	this.fConst493;
	this.fConst494;
	this.fConst495;
	this.fConst496;
	this.fConst497;
	this.fConst498;
	this.fConst499;
	this.fConst500;
	this.fConst501;
	this.fConst502;
	this.fConst503;
	this.fConst504;
	this.fConst505;
	this.fConst506;
	this.fConst507;
	this.fConst508;
	this.fRec127 = new Float32Array(3);
	this.fConst509;
	this.fConst510;
	this.fConst511;
	this.fRec126 = new Float32Array(3);
	this.fConst512;
	this.fConst513;
	this.fConst514;
	this.fRec125 = new Float32Array(3);
	this.fConst515;
	this.fConst516;
	this.fConst517;
	this.fConst518;
	this.fRec124 = new Float32Array(3);
	this.fConst519;
	this.fConst520;
	this.fConst521;
	this.fRec123 = new Float32Array(3);
	this.fConst522;
	this.fConst523;
	this.fConst524;
	this.fRec122 = new Float32Array(3);
	this.fConst525;
	this.fRec121 = new Float32Array(2);
	this.fVbargraph13;
	this.fConst526;
	this.fConst527;
	this.fConst528;
	this.fConst529;
	this.fConst530;
	this.fConst531;
	this.fConst532;
	this.fConst533;
	this.fConst534;
	this.fRec131 = new Float32Array(3);
	this.fConst535;
	this.fConst536;
	this.fConst537;
	this.fRec130 = new Float32Array(3);
	this.fConst538;
	this.fConst539;
	this.fConst540;
	this.fRec129 = new Float32Array(3);
	this.fConst541;
	this.fRec128 = new Float32Array(2);
	this.fVbargraph14;
	
	this.metadata = function(m) { 
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

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
		var rate;
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
	this.getOutputRate = function(channel) {
		var rate;
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
	
	this.classInit = function(samplingFreq) {
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (1000 / this.fConst0);
		this.fConst2 = Math.tan((50265.5 / this.fConst0));
		this.fConst3 = (1 / this.fConst2);
		this.fConst4 = (1 / (((this.fConst3 + 0.157482) / this.fConst2) + 0.93514));
		this.fConst5 = mydsp_faustpower2_f(this.fConst2);
		this.fConst6 = (50.0638 / this.fConst5);
		this.fConst7 = (2 * (0.93514 - this.fConst6));
		this.fConst8 = (1 / (((this.fConst3 + 0.74313) / this.fConst2) + 1.45007));
		this.fConst9 = (11.0521 / this.fConst5);
		this.fConst10 = (2 * (1.45007 - this.fConst9));
		this.fConst11 = (1 / (((this.fConst3 + 3.18973) / this.fConst2) + 4.07678));
		this.fConst12 = (0.00176617 / this.fConst5);
		this.fConst13 = (2 * (0.000407678 - this.fConst12));
		this.fConst14 = (6.28319 / this.fConst0);
		this.fConst15 = (1 / this.fConst0);
		this.fConst16 = (0.25 * this.fConst0);
		this.fConst17 = (0.0416667 * mydsp_faustpower2_f(this.fConst0));
		this.fConst18 = (0.00520833 * mydsp_faustpower3_f(this.fConst0));
		this.fConst19 = (1413.72 / this.fConst0);
		this.fConst20 = (2827.43 / this.fConst0);
		this.fConst21 = (3.14159 / this.fConst0);
		this.fConst22 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst23 = (1 / this.fConst5);
		this.fConst24 = (2 * (4.07678 - this.fConst23));
		this.fConst25 = (this.fConst12 + 0.000407678);
		this.fConst26 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst27 = (2 * (1.45007 - this.fConst23));
		this.fConst28 = (this.fConst9 + 1.45007);
		this.fConst29 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst30 = (2 * (0.93514 - this.fConst23));
		this.fConst31 = (this.fConst6 + 0.93514);
		this.fConst32 = Math.tan((31665.3 / this.fConst0));
		this.fConst33 = (1 / this.fConst32);
		this.fConst34 = (1 / (((this.fConst33 + 0.157482) / this.fConst32) + 0.93514));
		this.fConst35 = mydsp_faustpower2_f(this.fConst32);
		this.fConst36 = (50.0638 / this.fConst35);
		this.fConst37 = (2 * (0.93514 - this.fConst36));
		this.fConst38 = (1 / (((this.fConst33 + 0.74313) / this.fConst32) + 1.45007));
		this.fConst39 = (11.0521 / this.fConst35);
		this.fConst40 = (2 * (1.45007 - this.fConst39));
		this.fConst41 = (1 / (((this.fConst33 + 3.18973) / this.fConst32) + 4.07678));
		this.fConst42 = (0.00176617 / this.fConst35);
		this.fConst43 = (2 * (0.000407678 - this.fConst42));
		this.fConst44 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst45 = (2 * (53.5362 - this.fConst23));
		this.fConst46 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst47 = (2 * (7.62173 - this.fConst23));
		this.fConst48 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst49 = (0.0001 / this.fConst5);
		this.fConst50 = (2 * (0.000433227 - this.fConst49));
		this.fConst51 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst52 = (2 * (0.245292 - this.fConst23));
		this.fConst53 = (this.fConst49 + 0.000433227);
		this.fConst54 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst55 = (2 * (0.689621 - this.fConst23));
		this.fConst56 = (this.fConst23 + 7.62173);
		this.fConst57 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst58 = (2 * (1.06936 - this.fConst23));
		this.fConst59 = (this.fConst23 + 53.5362);
		this.fConst60 = (((this.fConst33 + -3.18973) / this.fConst32) + 4.07678);
		this.fConst61 = (1 / this.fConst35);
		this.fConst62 = (2 * (4.07678 - this.fConst61));
		this.fConst63 = (this.fConst42 + 0.000407678);
		this.fConst64 = (((this.fConst33 + -0.74313) / this.fConst32) + 1.45007);
		this.fConst65 = (2 * (1.45007 - this.fConst61));
		this.fConst66 = (this.fConst39 + 1.45007);
		this.fConst67 = (((this.fConst33 + -0.157482) / this.fConst32) + 0.93514);
		this.fConst68 = (2 * (0.93514 - this.fConst61));
		this.fConst69 = (this.fConst36 + 0.93514);
		this.fConst70 = Math.tan((19947.9 / this.fConst0));
		this.fConst71 = (1 / this.fConst70);
		this.fConst72 = (1 / (((this.fConst71 + 0.157482) / this.fConst70) + 0.93514));
		this.fConst73 = mydsp_faustpower2_f(this.fConst70);
		this.fConst74 = (50.0638 / this.fConst73);
		this.fConst75 = (2 * (0.93514 - this.fConst74));
		this.fConst76 = (1 / (((this.fConst71 + 0.74313) / this.fConst70) + 1.45007));
		this.fConst77 = (11.0521 / this.fConst73);
		this.fConst78 = (2 * (1.45007 - this.fConst77));
		this.fConst79 = (1 / (((this.fConst71 + 3.18973) / this.fConst70) + 4.07678));
		this.fConst80 = (0.00176617 / this.fConst73);
		this.fConst81 = (2 * (0.000407678 - this.fConst80));
		this.fConst82 = (1 / (((this.fConst33 + 0.168405) / this.fConst32) + 1.06936));
		this.fConst83 = (2 * (53.5362 - this.fConst61));
		this.fConst84 = (1 / (((this.fConst33 + 0.512479) / this.fConst32) + 0.689621));
		this.fConst85 = (2 * (7.62173 - this.fConst61));
		this.fConst86 = (1 / (((this.fConst33 + 0.782413) / this.fConst32) + 0.245292));
		this.fConst87 = (0.0001 / this.fConst35);
		this.fConst88 = (2 * (0.000433227 - this.fConst87));
		this.fConst89 = (((this.fConst33 + -0.782413) / this.fConst32) + 0.245292);
		this.fConst90 = (2 * (0.245292 - this.fConst61));
		this.fConst91 = (this.fConst87 + 0.000433227);
		this.fConst92 = (((this.fConst33 + -0.512479) / this.fConst32) + 0.689621);
		this.fConst93 = (2 * (0.689621 - this.fConst61));
		this.fConst94 = (this.fConst61 + 7.62173);
		this.fConst95 = (((this.fConst33 + -0.168405) / this.fConst32) + 1.06936);
		this.fConst96 = (2 * (1.06936 - this.fConst61));
		this.fConst97 = (this.fConst61 + 53.5362);
		this.fConst98 = (((this.fConst71 + -3.18973) / this.fConst70) + 4.07678);
		this.fConst99 = (1 / this.fConst73);
		this.fConst100 = (2 * (4.07678 - this.fConst99));
		this.fConst101 = (this.fConst80 + 0.000407678);
		this.fConst102 = (((this.fConst71 + -0.74313) / this.fConst70) + 1.45007);
		this.fConst103 = (2 * (1.45007 - this.fConst99));
		this.fConst104 = (this.fConst77 + 1.45007);
		this.fConst105 = (((this.fConst71 + -0.157482) / this.fConst70) + 0.93514);
		this.fConst106 = (2 * (0.93514 - this.fConst99));
		this.fConst107 = (this.fConst74 + 0.93514);
		this.fConst108 = Math.tan((12566.4 / this.fConst0));
		this.fConst109 = (1 / this.fConst108);
		this.fConst110 = (1 / (((this.fConst109 + 0.157482) / this.fConst108) + 0.93514));
		this.fConst111 = mydsp_faustpower2_f(this.fConst108);
		this.fConst112 = (50.0638 / this.fConst111);
		this.fConst113 = (2 * (0.93514 - this.fConst112));
		this.fConst114 = (1 / (((this.fConst109 + 0.74313) / this.fConst108) + 1.45007));
		this.fConst115 = (11.0521 / this.fConst111);
		this.fConst116 = (2 * (1.45007 - this.fConst115));
		this.fConst117 = (1 / (((this.fConst109 + 3.18973) / this.fConst108) + 4.07678));
		this.fConst118 = (0.00176617 / this.fConst111);
		this.fConst119 = (2 * (0.000407678 - this.fConst118));
		this.fConst120 = (1 / (((this.fConst71 + 0.168405) / this.fConst70) + 1.06936));
		this.fConst121 = (2 * (53.5362 - this.fConst99));
		this.fConst122 = (1 / (((this.fConst71 + 0.512479) / this.fConst70) + 0.689621));
		this.fConst123 = (2 * (7.62173 - this.fConst99));
		this.fConst124 = (1 / (((this.fConst71 + 0.782413) / this.fConst70) + 0.245292));
		this.fConst125 = (0.0001 / this.fConst73);
		this.fConst126 = (2 * (0.000433227 - this.fConst125));
		this.fConst127 = (((this.fConst71 + -0.782413) / this.fConst70) + 0.245292);
		this.fConst128 = (2 * (0.245292 - this.fConst99));
		this.fConst129 = (this.fConst125 + 0.000433227);
		this.fConst130 = (((this.fConst71 + -0.512479) / this.fConst70) + 0.689621);
		this.fConst131 = (2 * (0.689621 - this.fConst99));
		this.fConst132 = (this.fConst99 + 7.62173);
		this.fConst133 = (((this.fConst71 + -0.168405) / this.fConst70) + 1.06936);
		this.fConst134 = (2 * (1.06936 - this.fConst99));
		this.fConst135 = (this.fConst99 + 53.5362);
		this.fConst136 = (((this.fConst109 + -3.18973) / this.fConst108) + 4.07678);
		this.fConst137 = (1 / this.fConst111);
		this.fConst138 = (2 * (4.07678 - this.fConst137));
		this.fConst139 = (this.fConst118 + 0.000407678);
		this.fConst140 = (((this.fConst109 + -0.74313) / this.fConst108) + 1.45007);
		this.fConst141 = (2 * (1.45007 - this.fConst137));
		this.fConst142 = (this.fConst115 + 1.45007);
		this.fConst143 = (((this.fConst109 + -0.157482) / this.fConst108) + 0.93514);
		this.fConst144 = (2 * (0.93514 - this.fConst137));
		this.fConst145 = (this.fConst112 + 0.93514);
		this.fConst146 = Math.tan((7916.32 / this.fConst0));
		this.fConst147 = (1 / this.fConst146);
		this.fConst148 = (1 / (((this.fConst147 + 0.157482) / this.fConst146) + 0.93514));
		this.fConst149 = mydsp_faustpower2_f(this.fConst146);
		this.fConst150 = (50.0638 / this.fConst149);
		this.fConst151 = (2 * (0.93514 - this.fConst150));
		this.fConst152 = (1 / (((this.fConst147 + 0.74313) / this.fConst146) + 1.45007));
		this.fConst153 = (11.0521 / this.fConst149);
		this.fConst154 = (2 * (1.45007 - this.fConst153));
		this.fConst155 = (1 / (((this.fConst147 + 3.18973) / this.fConst146) + 4.07678));
		this.fConst156 = (0.00176617 / this.fConst149);
		this.fConst157 = (2 * (0.000407678 - this.fConst156));
		this.fConst158 = (1 / (((this.fConst109 + 0.168405) / this.fConst108) + 1.06936));
		this.fConst159 = (2 * (53.5362 - this.fConst137));
		this.fConst160 = (1 / (((this.fConst109 + 0.512479) / this.fConst108) + 0.689621));
		this.fConst161 = (2 * (7.62173 - this.fConst137));
		this.fConst162 = (1 / (((this.fConst109 + 0.782413) / this.fConst108) + 0.245292));
		this.fConst163 = (0.0001 / this.fConst111);
		this.fConst164 = (2 * (0.000433227 - this.fConst163));
		this.fConst165 = (((this.fConst109 + -0.782413) / this.fConst108) + 0.245292);
		this.fConst166 = (2 * (0.245292 - this.fConst137));
		this.fConst167 = (this.fConst163 + 0.000433227);
		this.fConst168 = (((this.fConst109 + -0.512479) / this.fConst108) + 0.689621);
		this.fConst169 = (2 * (0.689621 - this.fConst137));
		this.fConst170 = (this.fConst137 + 7.62173);
		this.fConst171 = (((this.fConst109 + -0.168405) / this.fConst108) + 1.06936);
		this.fConst172 = (2 * (1.06936 - this.fConst137));
		this.fConst173 = (this.fConst137 + 53.5362);
		this.fConst174 = (((this.fConst147 + -3.18973) / this.fConst146) + 4.07678);
		this.fConst175 = (1 / this.fConst149);
		this.fConst176 = (2 * (4.07678 - this.fConst175));
		this.fConst177 = (this.fConst156 + 0.000407678);
		this.fConst178 = (((this.fConst147 + -0.74313) / this.fConst146) + 1.45007);
		this.fConst179 = (2 * (1.45007 - this.fConst175));
		this.fConst180 = (this.fConst153 + 1.45007);
		this.fConst181 = (((this.fConst147 + -0.157482) / this.fConst146) + 0.93514);
		this.fConst182 = (2 * (0.93514 - this.fConst175));
		this.fConst183 = (this.fConst150 + 0.93514);
		this.fConst184 = Math.tan((4986.97 / this.fConst0));
		this.fConst185 = (1 / this.fConst184);
		this.fConst186 = (1 / (((this.fConst185 + 0.157482) / this.fConst184) + 0.93514));
		this.fConst187 = mydsp_faustpower2_f(this.fConst184);
		this.fConst188 = (50.0638 / this.fConst187);
		this.fConst189 = (2 * (0.93514 - this.fConst188));
		this.fConst190 = (1 / (((this.fConst185 + 0.74313) / this.fConst184) + 1.45007));
		this.fConst191 = (11.0521 / this.fConst187);
		this.fConst192 = (2 * (1.45007 - this.fConst191));
		this.fConst193 = (1 / (((this.fConst185 + 3.18973) / this.fConst184) + 4.07678));
		this.fConst194 = (0.00176617 / this.fConst187);
		this.fConst195 = (2 * (0.000407678 - this.fConst194));
		this.fConst196 = (1 / (((this.fConst147 + 0.168405) / this.fConst146) + 1.06936));
		this.fConst197 = (2 * (53.5362 - this.fConst175));
		this.fConst198 = (1 / (((this.fConst147 + 0.512479) / this.fConst146) + 0.689621));
		this.fConst199 = (2 * (7.62173 - this.fConst175));
		this.fConst200 = (1 / (((this.fConst147 + 0.782413) / this.fConst146) + 0.245292));
		this.fConst201 = (0.0001 / this.fConst149);
		this.fConst202 = (2 * (0.000433227 - this.fConst201));
		this.fConst203 = (((this.fConst147 + -0.782413) / this.fConst146) + 0.245292);
		this.fConst204 = (2 * (0.245292 - this.fConst175));
		this.fConst205 = (this.fConst201 + 0.000433227);
		this.fConst206 = (((this.fConst147 + -0.512479) / this.fConst146) + 0.689621);
		this.fConst207 = (2 * (0.689621 - this.fConst175));
		this.fConst208 = (this.fConst175 + 7.62173);
		this.fConst209 = (((this.fConst147 + -0.168405) / this.fConst146) + 1.06936);
		this.fConst210 = (2 * (1.06936 - this.fConst175));
		this.fConst211 = (this.fConst175 + 53.5362);
		this.fConst212 = (((this.fConst185 + -3.18973) / this.fConst184) + 4.07678);
		this.fConst213 = (1 / this.fConst187);
		this.fConst214 = (2 * (4.07678 - this.fConst213));
		this.fConst215 = (this.fConst194 + 0.000407678);
		this.fConst216 = (((this.fConst185 + -0.74313) / this.fConst184) + 1.45007);
		this.fConst217 = (2 * (1.45007 - this.fConst213));
		this.fConst218 = (this.fConst191 + 1.45007);
		this.fConst219 = (((this.fConst185 + -0.157482) / this.fConst184) + 0.93514);
		this.fConst220 = (2 * (0.93514 - this.fConst213));
		this.fConst221 = (this.fConst188 + 0.93514);
		this.fConst222 = Math.tan((3141.59 / this.fConst0));
		this.fConst223 = (1 / this.fConst222);
		this.fConst224 = (1 / (((this.fConst223 + 0.157482) / this.fConst222) + 0.93514));
		this.fConst225 = mydsp_faustpower2_f(this.fConst222);
		this.fConst226 = (50.0638 / this.fConst225);
		this.fConst227 = (2 * (0.93514 - this.fConst226));
		this.fConst228 = (1 / (((this.fConst223 + 0.74313) / this.fConst222) + 1.45007));
		this.fConst229 = (11.0521 / this.fConst225);
		this.fConst230 = (2 * (1.45007 - this.fConst229));
		this.fConst231 = (1 / (((this.fConst223 + 3.18973) / this.fConst222) + 4.07678));
		this.fConst232 = (0.00176617 / this.fConst225);
		this.fConst233 = (2 * (0.000407678 - this.fConst232));
		this.fConst234 = (1 / (((this.fConst185 + 0.168405) / this.fConst184) + 1.06936));
		this.fConst235 = (2 * (53.5362 - this.fConst213));
		this.fConst236 = (1 / (((this.fConst185 + 0.512479) / this.fConst184) + 0.689621));
		this.fConst237 = (2 * (7.62173 - this.fConst213));
		this.fConst238 = (1 / (((this.fConst185 + 0.782413) / this.fConst184) + 0.245292));
		this.fConst239 = (0.0001 / this.fConst187);
		this.fConst240 = (2 * (0.000433227 - this.fConst239));
		this.fConst241 = (((this.fConst185 + -0.782413) / this.fConst184) + 0.245292);
		this.fConst242 = (2 * (0.245292 - this.fConst213));
		this.fConst243 = (this.fConst239 + 0.000433227);
		this.fConst244 = (((this.fConst185 + -0.512479) / this.fConst184) + 0.689621);
		this.fConst245 = (2 * (0.689621 - this.fConst213));
		this.fConst246 = (this.fConst213 + 7.62173);
		this.fConst247 = (((this.fConst185 + -0.168405) / this.fConst184) + 1.06936);
		this.fConst248 = (2 * (1.06936 - this.fConst213));
		this.fConst249 = (this.fConst213 + 53.5362);
		this.fConst250 = (((this.fConst223 + -3.18973) / this.fConst222) + 4.07678);
		this.fConst251 = (1 / this.fConst225);
		this.fConst252 = (2 * (4.07678 - this.fConst251));
		this.fConst253 = (this.fConst232 + 0.000407678);
		this.fConst254 = (((this.fConst223 + -0.74313) / this.fConst222) + 1.45007);
		this.fConst255 = (2 * (1.45007 - this.fConst251));
		this.fConst256 = (this.fConst229 + 1.45007);
		this.fConst257 = (((this.fConst223 + -0.157482) / this.fConst222) + 0.93514);
		this.fConst258 = (2 * (0.93514 - this.fConst251));
		this.fConst259 = (this.fConst226 + 0.93514);
		this.fConst260 = Math.tan((1979.08 / this.fConst0));
		this.fConst261 = (1 / this.fConst260);
		this.fConst262 = (1 / (((this.fConst261 + 0.157482) / this.fConst260) + 0.93514));
		this.fConst263 = mydsp_faustpower2_f(this.fConst260);
		this.fConst264 = (50.0638 / this.fConst263);
		this.fConst265 = (2 * (0.93514 - this.fConst264));
		this.fConst266 = (1 / (((this.fConst261 + 0.74313) / this.fConst260) + 1.45007));
		this.fConst267 = (11.0521 / this.fConst263);
		this.fConst268 = (2 * (1.45007 - this.fConst267));
		this.fConst269 = (1 / (((this.fConst261 + 3.18973) / this.fConst260) + 4.07678));
		this.fConst270 = (0.00176617 / this.fConst263);
		this.fConst271 = (2 * (0.000407678 - this.fConst270));
		this.fConst272 = (1 / (((this.fConst223 + 0.168405) / this.fConst222) + 1.06936));
		this.fConst273 = (2 * (53.5362 - this.fConst251));
		this.fConst274 = (1 / (((this.fConst223 + 0.512479) / this.fConst222) + 0.689621));
		this.fConst275 = (2 * (7.62173 - this.fConst251));
		this.fConst276 = (1 / (((this.fConst223 + 0.782413) / this.fConst222) + 0.245292));
		this.fConst277 = (0.0001 / this.fConst225);
		this.fConst278 = (2 * (0.000433227 - this.fConst277));
		this.fConst279 = (((this.fConst223 + -0.782413) / this.fConst222) + 0.245292);
		this.fConst280 = (2 * (0.245292 - this.fConst251));
		this.fConst281 = (this.fConst277 + 0.000433227);
		this.fConst282 = (((this.fConst223 + -0.512479) / this.fConst222) + 0.689621);
		this.fConst283 = (2 * (0.689621 - this.fConst251));
		this.fConst284 = (this.fConst251 + 7.62173);
		this.fConst285 = (((this.fConst223 + -0.168405) / this.fConst222) + 1.06936);
		this.fConst286 = (2 * (1.06936 - this.fConst251));
		this.fConst287 = (this.fConst251 + 53.5362);
		this.fConst288 = (((this.fConst261 + -3.18973) / this.fConst260) + 4.07678);
		this.fConst289 = (1 / this.fConst263);
		this.fConst290 = (2 * (4.07678 - this.fConst289));
		this.fConst291 = (this.fConst270 + 0.000407678);
		this.fConst292 = (((this.fConst261 + -0.74313) / this.fConst260) + 1.45007);
		this.fConst293 = (2 * (1.45007 - this.fConst289));
		this.fConst294 = (this.fConst267 + 1.45007);
		this.fConst295 = (((this.fConst261 + -0.157482) / this.fConst260) + 0.93514);
		this.fConst296 = (2 * (0.93514 - this.fConst289));
		this.fConst297 = (this.fConst264 + 0.93514);
		this.fConst298 = Math.tan((1246.74 / this.fConst0));
		this.fConst299 = (1 / this.fConst298);
		this.fConst300 = (1 / (((this.fConst299 + 0.157482) / this.fConst298) + 0.93514));
		this.fConst301 = mydsp_faustpower2_f(this.fConst298);
		this.fConst302 = (50.0638 / this.fConst301);
		this.fConst303 = (2 * (0.93514 - this.fConst302));
		this.fConst304 = (1 / (((this.fConst299 + 0.74313) / this.fConst298) + 1.45007));
		this.fConst305 = (11.0521 / this.fConst301);
		this.fConst306 = (2 * (1.45007 - this.fConst305));
		this.fConst307 = (1 / (((this.fConst299 + 3.18973) / this.fConst298) + 4.07678));
		this.fConst308 = (0.00176617 / this.fConst301);
		this.fConst309 = (2 * (0.000407678 - this.fConst308));
		this.fConst310 = (1 / (((this.fConst261 + 0.168405) / this.fConst260) + 1.06936));
		this.fConst311 = (2 * (53.5362 - this.fConst289));
		this.fConst312 = (1 / (((this.fConst261 + 0.512479) / this.fConst260) + 0.689621));
		this.fConst313 = (2 * (7.62173 - this.fConst289));
		this.fConst314 = (1 / (((this.fConst261 + 0.782413) / this.fConst260) + 0.245292));
		this.fConst315 = (0.0001 / this.fConst263);
		this.fConst316 = (2 * (0.000433227 - this.fConst315));
		this.fConst317 = (((this.fConst261 + -0.782413) / this.fConst260) + 0.245292);
		this.fConst318 = (2 * (0.245292 - this.fConst289));
		this.fConst319 = (this.fConst315 + 0.000433227);
		this.fConst320 = (((this.fConst261 + -0.512479) / this.fConst260) + 0.689621);
		this.fConst321 = (2 * (0.689621 - this.fConst289));
		this.fConst322 = (this.fConst289 + 7.62173);
		this.fConst323 = (((this.fConst261 + -0.168405) / this.fConst260) + 1.06936);
		this.fConst324 = (2 * (1.06936 - this.fConst289));
		this.fConst325 = (this.fConst289 + 53.5362);
		this.fConst326 = (((this.fConst299 + -3.18973) / this.fConst298) + 4.07678);
		this.fConst327 = (1 / this.fConst301);
		this.fConst328 = (2 * (4.07678 - this.fConst327));
		this.fConst329 = (this.fConst308 + 0.000407678);
		this.fConst330 = (((this.fConst299 + -0.74313) / this.fConst298) + 1.45007);
		this.fConst331 = (2 * (1.45007 - this.fConst327));
		this.fConst332 = (this.fConst305 + 1.45007);
		this.fConst333 = (((this.fConst299 + -0.157482) / this.fConst298) + 0.93514);
		this.fConst334 = (2 * (0.93514 - this.fConst327));
		this.fConst335 = (this.fConst302 + 0.93514);
		this.fConst336 = Math.tan((785.398 / this.fConst0));
		this.fConst337 = (1 / this.fConst336);
		this.fConst338 = (1 / (((this.fConst337 + 0.157482) / this.fConst336) + 0.93514));
		this.fConst339 = mydsp_faustpower2_f(this.fConst336);
		this.fConst340 = (50.0638 / this.fConst339);
		this.fConst341 = (2 * (0.93514 - this.fConst340));
		this.fConst342 = (1 / (((this.fConst337 + 0.74313) / this.fConst336) + 1.45007));
		this.fConst343 = (11.0521 / this.fConst339);
		this.fConst344 = (2 * (1.45007 - this.fConst343));
		this.fConst345 = (1 / (((this.fConst337 + 3.18973) / this.fConst336) + 4.07678));
		this.fConst346 = (0.00176617 / this.fConst339);
		this.fConst347 = (2 * (0.000407678 - this.fConst346));
		this.fConst348 = (1 / (((this.fConst299 + 0.168405) / this.fConst298) + 1.06936));
		this.fConst349 = (2 * (53.5362 - this.fConst327));
		this.fConst350 = (1 / (((this.fConst299 + 0.512479) / this.fConst298) + 0.689621));
		this.fConst351 = (2 * (7.62173 - this.fConst327));
		this.fConst352 = (1 / (((this.fConst299 + 0.782413) / this.fConst298) + 0.245292));
		this.fConst353 = (0.0001 / this.fConst301);
		this.fConst354 = (2 * (0.000433227 - this.fConst353));
		this.fConst355 = (((this.fConst299 + -0.782413) / this.fConst298) + 0.245292);
		this.fConst356 = (2 * (0.245292 - this.fConst327));
		this.fConst357 = (this.fConst353 + 0.000433227);
		this.fConst358 = (((this.fConst299 + -0.512479) / this.fConst298) + 0.689621);
		this.fConst359 = (2 * (0.689621 - this.fConst327));
		this.fConst360 = (this.fConst327 + 7.62173);
		this.fConst361 = (((this.fConst299 + -0.168405) / this.fConst298) + 1.06936);
		this.fConst362 = (2 * (1.06936 - this.fConst327));
		this.fConst363 = (this.fConst327 + 53.5362);
		this.fConst364 = (((this.fConst337 + -3.18973) / this.fConst336) + 4.07678);
		this.fConst365 = (1 / this.fConst339);
		this.fConst366 = (2 * (4.07678 - this.fConst365));
		this.fConst367 = (this.fConst346 + 0.000407678);
		this.fConst368 = (((this.fConst337 + -0.74313) / this.fConst336) + 1.45007);
		this.fConst369 = (2 * (1.45007 - this.fConst365));
		this.fConst370 = (this.fConst343 + 1.45007);
		this.fConst371 = (((this.fConst337 + -0.157482) / this.fConst336) + 0.93514);
		this.fConst372 = (2 * (0.93514 - this.fConst365));
		this.fConst373 = (this.fConst340 + 0.93514);
		this.fConst374 = Math.tan((494.77 / this.fConst0));
		this.fConst375 = (1 / this.fConst374);
		this.fConst376 = (1 / (((this.fConst375 + 0.157482) / this.fConst374) + 0.93514));
		this.fConst377 = mydsp_faustpower2_f(this.fConst374);
		this.fConst378 = (50.0638 / this.fConst377);
		this.fConst379 = (2 * (0.93514 - this.fConst378));
		this.fConst380 = (1 / (((this.fConst375 + 0.74313) / this.fConst374) + 1.45007));
		this.fConst381 = (11.0521 / this.fConst377);
		this.fConst382 = (2 * (1.45007 - this.fConst381));
		this.fConst383 = (1 / (((this.fConst375 + 3.18973) / this.fConst374) + 4.07678));
		this.fConst384 = (0.00176617 / this.fConst377);
		this.fConst385 = (2 * (0.000407678 - this.fConst384));
		this.fConst386 = (1 / (((this.fConst337 + 0.168405) / this.fConst336) + 1.06936));
		this.fConst387 = (2 * (53.5362 - this.fConst365));
		this.fConst388 = (1 / (((this.fConst337 + 0.512479) / this.fConst336) + 0.689621));
		this.fConst389 = (2 * (7.62173 - this.fConst365));
		this.fConst390 = (1 / (((this.fConst337 + 0.782413) / this.fConst336) + 0.245292));
		this.fConst391 = (0.0001 / this.fConst339);
		this.fConst392 = (2 * (0.000433227 - this.fConst391));
		this.fConst393 = (((this.fConst337 + -0.782413) / this.fConst336) + 0.245292);
		this.fConst394 = (2 * (0.245292 - this.fConst365));
		this.fConst395 = (this.fConst391 + 0.000433227);
		this.fConst396 = (((this.fConst337 + -0.512479) / this.fConst336) + 0.689621);
		this.fConst397 = (2 * (0.689621 - this.fConst365));
		this.fConst398 = (this.fConst365 + 7.62173);
		this.fConst399 = (((this.fConst337 + -0.168405) / this.fConst336) + 1.06936);
		this.fConst400 = (2 * (1.06936 - this.fConst365));
		this.fConst401 = (this.fConst365 + 53.5362);
		this.fConst402 = (((this.fConst375 + -3.18973) / this.fConst374) + 4.07678);
		this.fConst403 = (1 / this.fConst377);
		this.fConst404 = (2 * (4.07678 - this.fConst403));
		this.fConst405 = (this.fConst384 + 0.000407678);
		this.fConst406 = (((this.fConst375 + -0.74313) / this.fConst374) + 1.45007);
		this.fConst407 = (2 * (1.45007 - this.fConst403));
		this.fConst408 = (this.fConst381 + 1.45007);
		this.fConst409 = (((this.fConst375 + -0.157482) / this.fConst374) + 0.93514);
		this.fConst410 = (2 * (0.93514 - this.fConst403));
		this.fConst411 = (this.fConst378 + 0.93514);
		this.fConst412 = Math.tan((311.685 / this.fConst0));
		this.fConst413 = (1 / this.fConst412);
		this.fConst414 = (1 / (((this.fConst413 + 0.157482) / this.fConst412) + 0.93514));
		this.fConst415 = mydsp_faustpower2_f(this.fConst412);
		this.fConst416 = (50.0638 / this.fConst415);
		this.fConst417 = (2 * (0.93514 - this.fConst416));
		this.fConst418 = (1 / (((this.fConst413 + 0.74313) / this.fConst412) + 1.45007));
		this.fConst419 = (11.0521 / this.fConst415);
		this.fConst420 = (2 * (1.45007 - this.fConst419));
		this.fConst421 = (1 / (((this.fConst413 + 3.18973) / this.fConst412) + 4.07678));
		this.fConst422 = (0.00176617 / this.fConst415);
		this.fConst423 = (2 * (0.000407678 - this.fConst422));
		this.fConst424 = (1 / (((this.fConst375 + 0.168405) / this.fConst374) + 1.06936));
		this.fConst425 = (2 * (53.5362 - this.fConst403));
		this.fConst426 = (1 / (((this.fConst375 + 0.512479) / this.fConst374) + 0.689621));
		this.fConst427 = (2 * (7.62173 - this.fConst403));
		this.fConst428 = (1 / (((this.fConst375 + 0.782413) / this.fConst374) + 0.245292));
		this.fConst429 = (0.0001 / this.fConst377);
		this.fConst430 = (2 * (0.000433227 - this.fConst429));
		this.fConst431 = (((this.fConst375 + -0.782413) / this.fConst374) + 0.245292);
		this.fConst432 = (2 * (0.245292 - this.fConst403));
		this.fConst433 = (this.fConst429 + 0.000433227);
		this.fConst434 = (((this.fConst375 + -0.512479) / this.fConst374) + 0.689621);
		this.fConst435 = (2 * (0.689621 - this.fConst403));
		this.fConst436 = (this.fConst403 + 7.62173);
		this.fConst437 = (((this.fConst375 + -0.168405) / this.fConst374) + 1.06936);
		this.fConst438 = (2 * (1.06936 - this.fConst403));
		this.fConst439 = (this.fConst403 + 53.5362);
		this.fConst440 = (((this.fConst413 + -3.18973) / this.fConst412) + 4.07678);
		this.fConst441 = (1 / this.fConst415);
		this.fConst442 = (2 * (4.07678 - this.fConst441));
		this.fConst443 = (this.fConst422 + 0.000407678);
		this.fConst444 = (((this.fConst413 + -0.74313) / this.fConst412) + 1.45007);
		this.fConst445 = (2 * (1.45007 - this.fConst441));
		this.fConst446 = (this.fConst419 + 1.45007);
		this.fConst447 = (((this.fConst413 + -0.157482) / this.fConst412) + 0.93514);
		this.fConst448 = (2 * (0.93514 - this.fConst441));
		this.fConst449 = (this.fConst416 + 0.93514);
		this.fConst450 = Math.tan((196.35 / this.fConst0));
		this.fConst451 = (1 / this.fConst450);
		this.fConst452 = (1 / (((this.fConst451 + 0.157482) / this.fConst450) + 0.93514));
		this.fConst453 = mydsp_faustpower2_f(this.fConst450);
		this.fConst454 = (50.0638 / this.fConst453);
		this.fConst455 = (2 * (0.93514 - this.fConst454));
		this.fConst456 = (1 / (((this.fConst451 + 0.74313) / this.fConst450) + 1.45007));
		this.fConst457 = (11.0521 / this.fConst453);
		this.fConst458 = (2 * (1.45007 - this.fConst457));
		this.fConst459 = (1 / (((this.fConst451 + 3.18973) / this.fConst450) + 4.07678));
		this.fConst460 = (0.00176617 / this.fConst453);
		this.fConst461 = (2 * (0.000407678 - this.fConst460));
		this.fConst462 = (1 / (((this.fConst413 + 0.168405) / this.fConst412) + 1.06936));
		this.fConst463 = (2 * (53.5362 - this.fConst441));
		this.fConst464 = (1 / (((this.fConst413 + 0.512479) / this.fConst412) + 0.689621));
		this.fConst465 = (2 * (7.62173 - this.fConst441));
		this.fConst466 = (1 / (((this.fConst413 + 0.782413) / this.fConst412) + 0.245292));
		this.fConst467 = (0.0001 / this.fConst415);
		this.fConst468 = (2 * (0.000433227 - this.fConst467));
		this.fConst469 = (((this.fConst413 + -0.782413) / this.fConst412) + 0.245292);
		this.fConst470 = (2 * (0.245292 - this.fConst441));
		this.fConst471 = (this.fConst467 + 0.000433227);
		this.fConst472 = (((this.fConst413 + -0.512479) / this.fConst412) + 0.689621);
		this.fConst473 = (2 * (0.689621 - this.fConst441));
		this.fConst474 = (this.fConst441 + 7.62173);
		this.fConst475 = (((this.fConst413 + -0.168405) / this.fConst412) + 1.06936);
		this.fConst476 = (2 * (1.06936 - this.fConst441));
		this.fConst477 = (this.fConst441 + 53.5362);
		this.fConst478 = (((this.fConst451 + -3.18973) / this.fConst450) + 4.07678);
		this.fConst479 = (1 / this.fConst453);
		this.fConst480 = (2 * (4.07678 - this.fConst479));
		this.fConst481 = (this.fConst460 + 0.000407678);
		this.fConst482 = (((this.fConst451 + -0.74313) / this.fConst450) + 1.45007);
		this.fConst483 = (2 * (1.45007 - this.fConst479));
		this.fConst484 = (this.fConst457 + 1.45007);
		this.fConst485 = (((this.fConst451 + -0.157482) / this.fConst450) + 0.93514);
		this.fConst486 = (2 * (0.93514 - this.fConst479));
		this.fConst487 = (this.fConst454 + 0.93514);
		this.fConst488 = Math.tan((123.692 / this.fConst0));
		this.fConst489 = (1 / this.fConst488);
		this.fConst490 = (1 / (((this.fConst489 + 0.157482) / this.fConst488) + 0.93514));
		this.fConst491 = mydsp_faustpower2_f(this.fConst488);
		this.fConst492 = (50.0638 / this.fConst491);
		this.fConst493 = (2 * (0.93514 - this.fConst492));
		this.fConst494 = (1 / (((this.fConst489 + 0.74313) / this.fConst488) + 1.45007));
		this.fConst495 = (11.0521 / this.fConst491);
		this.fConst496 = (2 * (1.45007 - this.fConst495));
		this.fConst497 = (1 / (((this.fConst489 + 3.18973) / this.fConst488) + 4.07678));
		this.fConst498 = (0.00176617 / this.fConst491);
		this.fConst499 = (2 * (0.000407678 - this.fConst498));
		this.fConst500 = (1 / (((this.fConst451 + 0.168405) / this.fConst450) + 1.06936));
		this.fConst501 = (2 * (53.5362 - this.fConst479));
		this.fConst502 = (1 / (((this.fConst451 + 0.512479) / this.fConst450) + 0.689621));
		this.fConst503 = (2 * (7.62173 - this.fConst479));
		this.fConst504 = (1 / (((this.fConst451 + 0.782413) / this.fConst450) + 0.245292));
		this.fConst505 = (0.0001 / this.fConst453);
		this.fConst506 = (2 * (0.000433227 - this.fConst505));
		this.fConst507 = (((this.fConst451 + -0.782413) / this.fConst450) + 0.245292);
		this.fConst508 = (2 * (0.245292 - this.fConst479));
		this.fConst509 = (this.fConst505 + 0.000433227);
		this.fConst510 = (((this.fConst451 + -0.512479) / this.fConst450) + 0.689621);
		this.fConst511 = (2 * (0.689621 - this.fConst479));
		this.fConst512 = (this.fConst479 + 7.62173);
		this.fConst513 = (((this.fConst451 + -0.168405) / this.fConst450) + 1.06936);
		this.fConst514 = (2 * (1.06936 - this.fConst479));
		this.fConst515 = (this.fConst479 + 53.5362);
		this.fConst516 = (((this.fConst489 + -3.18973) / this.fConst488) + 4.07678);
		this.fConst517 = (1 / this.fConst491);
		this.fConst518 = (2 * (4.07678 - this.fConst517));
		this.fConst519 = (this.fConst498 + 0.000407678);
		this.fConst520 = (((this.fConst489 + -0.74313) / this.fConst488) + 1.45007);
		this.fConst521 = (2 * (1.45007 - this.fConst517));
		this.fConst522 = (this.fConst495 + 1.45007);
		this.fConst523 = (((this.fConst489 + -0.157482) / this.fConst488) + 0.93514);
		this.fConst524 = (2 * (0.93514 - this.fConst517));
		this.fConst525 = (this.fConst492 + 0.93514);
		this.fConst526 = (1 / (((this.fConst489 + 0.168405) / this.fConst488) + 1.06936));
		this.fConst527 = (2 * (53.5362 - this.fConst517));
		this.fConst528 = (1 / (((this.fConst489 + 0.512479) / this.fConst488) + 0.689621));
		this.fConst529 = (2 * (7.62173 - this.fConst517));
		this.fConst530 = (1 / (((this.fConst489 + 0.782413) / this.fConst488) + 0.245292));
		this.fConst531 = (0.0001 / this.fConst491);
		this.fConst532 = (2 * (0.000433227 - this.fConst531));
		this.fConst533 = (((this.fConst489 + -0.782413) / this.fConst488) + 0.245292);
		this.fConst534 = (2 * (0.245292 - this.fConst517));
		this.fConst535 = (this.fConst531 + 0.000433227);
		this.fConst536 = (((this.fConst489 + -0.512479) / this.fConst488) + 0.689621);
		this.fConst537 = (2 * (0.689621 - this.fConst517));
		this.fConst538 = (this.fConst517 + 7.62173);
		this.fConst539 = (((this.fConst489 + -0.168405) / this.fConst488) + 1.06936);
		this.fConst540 = (2 * (1.06936 - this.fConst517));
		this.fConst541 = (this.fConst517 + 53.5362);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		this.fCheckbox0 = 0;
		this.fHslider2 = 5;
		this.fCheckbox1 = 0;
		this.fCheckbox2 = 0;
		this.fHslider3 = 200;
		this.fCheckbox3 = 0;
		this.fHslider4 = 0.8;
		this.fVslider0 = -20;
		this.fCheckbox4 = 0;
		this.fCheckbox5 = 0;
		this.fEntry0 = 2;
		this.fVslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fCheckbox6 = 0;
		this.fHslider5 = 25;
		this.fHslider6 = 0.9;
		this.fCheckbox7 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec4[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec15[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec17[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec18[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec20[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fVec1[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fRec19[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fVec2[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec3[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fVec4[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec5[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec6[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fVec7[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fVec8[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fRec21[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fVec9[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fVec10[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fVec11[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fVec12[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fVec13[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fVec14[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fVec15[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fRec22[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fVec16[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec17[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fVec18[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fVec19[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fVec20[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fVec21[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.iRec23[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			this.fRec24[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec25[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec26[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			this.fRec16[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fRec14[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec13[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec12[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec11[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec10[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec27[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec9[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec8[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec7[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fRec6[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fRec5[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec30[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec29[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec28[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fRec33[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fRec31[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			this.fRec36[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.fRec34[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec3[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec2[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec1[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			this.fRec0[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			this.fRec43[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			this.fRec42[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec41[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec40[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec39[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec38[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			this.fRec37[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			this.fRec50[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			this.fRec49[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			this.fRec48[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec47[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec46[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			this.fRec45[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			this.fRec44[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			this.fRec57[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec56[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			this.fRec55[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec54[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec53[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec52[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			this.fRec51[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			this.fRec64[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec63[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec62[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			this.fRec61[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec60[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec59[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			this.fRec58[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			this.fRec71[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec70[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			this.fRec69[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec68[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec67[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec66[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			this.fRec65[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			this.fRec78[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec77[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec76[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec75[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec74[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			this.fRec73[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			this.fRec72[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			this.fRec85[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec84[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			this.fRec83[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec82[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec81[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			this.fRec80[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			this.fRec79[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			this.fRec92[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec91[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			this.fRec90[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			this.fRec89[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			this.fRec88[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			this.fRec87[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			this.fRec86[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			this.fRec99[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			this.fRec98[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			this.fRec97[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec96[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			this.fRec95[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			this.fRec94[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			this.fRec93[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			this.fRec106[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			this.fRec105[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			this.fRec104[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec103[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec102[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			this.fRec101[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			this.fRec100[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			this.fRec113[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			this.fRec112[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			this.fRec111[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			this.fRec110[l130] = 0;
			
		}
		for (var l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			this.fRec109[l131] = 0;
			
		}
		for (var l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			this.fRec108[l132] = 0;
			
		}
		for (var l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			this.fRec107[l133] = 0;
			
		}
		for (var l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			this.fRec120[l134] = 0;
			
		}
		for (var l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			this.fRec119[l135] = 0;
			
		}
		for (var l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			this.fRec118[l136] = 0;
			
		}
		for (var l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			this.fRec117[l137] = 0;
			
		}
		for (var l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			this.fRec116[l138] = 0;
			
		}
		for (var l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			this.fRec115[l139] = 0;
			
		}
		for (var l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			this.fRec114[l140] = 0;
			
		}
		for (var l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			this.fRec127[l141] = 0;
			
		}
		for (var l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			this.fRec126[l142] = 0;
			
		}
		for (var l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			this.fRec125[l143] = 0;
			
		}
		for (var l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			this.fRec124[l144] = 0;
			
		}
		for (var l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			this.fRec123[l145] = 0;
			
		}
		for (var l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			this.fRec122[l146] = 0;
			
		}
		for (var l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			this.fRec121[l147] = 0;
			
		}
		for (var l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			this.fRec131[l148] = 0;
			
		}
		for (var l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			this.fRec130[l149] = 0;
			
		}
		for (var l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			this.fRec129[l150] = 0;
			
		}
		for (var l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			this.fRec128[l151] = 0;
			
		}
		
	}
	
	this.init = function(samplingFreq) {
		this.classInit(samplingFreq);
		this.instanceInit(samplingFreq);
	}
	
	this.instanceInit = function(samplingFreq) {
		this.instanceConstants(samplingFreq);
		this.instanceResetUserInterface();
		this.instanceClear();
	}
	
	this.buildUserInterface = function(ui_interface) {
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
		ui_interface.addVerticalSlider("Amplitude", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), -20, -120, 10, 0.1);
		ui_interface.declare("fVslider1", "2", "");
		ui_interface.declare("fVslider1", "style", "knob");
		ui_interface.declare("fVslider1", "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface.declare("fVslider1", "unit", "PK");
		ui_interface.addVerticalSlider("Frequency", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 49, 1, 88, 0.01);
		ui_interface.declare("fVslider3", "3", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Percentange frequency-shift  up or down for second oscillator");
		ui_interface.declare("fVslider3", "unit", "%%");
		ui_interface.addVerticalSlider("Detuning 1", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), -0.1, -10, 10, 0.01);
		ui_interface.declare("fVslider4", "4", "");
		ui_interface.declare("fVslider4", "style", "knob");
		ui_interface.declare("fVslider4", "tooltip", "Percentange frequency-shift up or down for third detuned oscillator");
		ui_interface.declare("fVslider4", "unit", "%%");
		ui_interface.addVerticalSlider("Detuning 2", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), 0.1, -10, 10, 0.01);
		ui_interface.declare("fVslider2", "5", "");
		ui_interface.declare("fVslider2", "scale", "log");
		ui_interface.declare("fVslider2", "style", "knob");
		ui_interface.declare("fVslider2", "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface.declare("fVslider2", "unit", "sec");
		ui_interface.addVerticalSlider("Portamento", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), 0.1, 0.001, 10, 0.001);
		ui_interface.declare("fEntry0", "6", "");
		ui_interface.declare("fEntry0", "tooltip", "Order of sawtootn aliasing   suppression");
		ui_interface.addNumEntry("Saw Order", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 2, 1, 4, 1);
		ui_interface.declare("0", "7", "");
		ui_interface.openVerticalBox("Alternate Signals");
		ui_interface.declare("fCheckbox5", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", function handler(obj) { function setval(val) { obj.fCheckbox5 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox6", "1", "");
		ui_interface.declare("fCheckbox6", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", function handler(obj) { function setval(val) { obj.fCheckbox6 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox4", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", function handler(obj) { function setval(val) { obj.fCheckbox4 = val; } return setval; }(this));
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
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox3 = val; } return setval; }(this));
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.declare("fHslider4", "tooltip", "wah pedal angle between   0 (rocked back) and 1 (rocked forward)");
		ui_interface.addHorizontalSlider("Wah parameter", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.8, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "Fourth-order wah effect made using moog_vcf");
		ui_interface.openHorizontalBox("WAH4");
		ui_interface.declare("fCheckbox2", "0", "");
		ui_interface.declare("fCheckbox2", "tooltip", "When this is checked, the wah pedal has   no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "tooltip", "wah resonance   frequency in Hz");
		ui_interface.addHorizontalSlider("Resonance Frequency", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 200, 100, 2000, 1);
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
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "1", "");
		ui_interface.declare("fCheckbox1", "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface.addCheckButton("Use Biquads", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox7", "2", "");
		ui_interface.declare("fCheckbox7", "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface.addCheckButton("Normalized Ladders", function handler(obj) { function setval(val) { obj.fCheckbox7 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.");
		ui_interface.declare("fHslider5", "unit", "PK");
		ui_interface.addHorizontalSlider("Corner Frequency", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 25, 1, 88, 0.01);
		ui_interface.declare("fHslider6", "2", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface.addHorizontalSlider("Corner Resonance", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0.9, 0, 1, 0.01);
		ui_interface.declare("fHslider2", "3", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "output level in decibels");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("VCF Output Level", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 5, -60, 20, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "5", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph14", "0", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb85289d0", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8516f10", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb84f0ce0", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb84cea30", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb84ac780", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb848a4d0", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8468220", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8445f70", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8423cc0", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8401a10", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb83db7e0", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb83b9530", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8397280", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8374fd0", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fceb8351c90", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "scale", "log");
		ui_interface.declare("fHslider1", "tooltip", "band-level averaging time in milliseconds");
		ui_interface.declare("fHslider1", "unit", "ms");
		ui_interface.addHorizontalSlider("Level Averaging Time", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 100, 1, 10000, 1);
		ui_interface.declare("fHslider0", "1", "");
		ui_interface.declare("fHslider0", "tooltip", "Level offset in decibels");
		ui_interface.declare("fHslider0", "unit", "dB");
		ui_interface.addHorizontalSlider("Level dB Offset", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 50, -50, 100, 1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = Math.exp((0 - (this.fConst1 / this.fHslider1)));
		var fSlow2 = (1 - fSlow1);
		var iSlow3 = this.fCheckbox0;
		var fSlow4 = (0.001 * Math.pow(10, (0.05 * this.fHslider2)));
		var iSlow5 = this.fCheckbox1;
		var iSlow6 = this.fCheckbox2;
		var fSlow7 = (0.001 * this.fHslider3);
		var iSlow8 = this.fCheckbox3;
		var fSlow9 = this.fHslider4;
		var fSlow10 = (0.0001 * Math.pow(4, fSlow9));
		var fSlow11 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var iSlow12 = this.fCheckbox4;
		var iSlow13 = this.fCheckbox5;
		var iSlow14 = (this.fEntry0 + -1);
		var iSlow15 = (iSlow14 >= 2);
		var iSlow16 = (iSlow14 >= 1);
		var fSlow17 = Math.exp((0 - (this.fConst15 / this.fVslider2)));
		var fSlow18 = (440 * (Math.pow(2, (0.0833333 * (this.fVslider1 + -49))) * (1 - fSlow17)));
		var iSlow19 = (iSlow14 >= 3);
		var fSlow20 = ((0.01 * this.fVslider3) + 1);
		var fSlow21 = ((0.01 * this.fVslider4) + 1);
		var iSlow22 = this.fCheckbox6;
		var fSlow23 = Math.pow(2, (2.3 * fSlow9));
		var fSlow24 = (1 - (this.fConst19 * (fSlow23 / Math.pow(2, ((2 * (1 - fSlow9)) + 1)))));
		var fSlow25 = (0.001 * (0 - (2 * (fSlow24 * Math.cos((this.fConst20 * fSlow23))))));
		var fSlow26 = (0.001 * mydsp_faustpower2_f(fSlow24));
		var fSlow27 = (0.44 * Math.pow(2, (0.0833333 * (this.fHslider5 + -49))));
		var fSlow28 = this.fHslider6;
		var fSlow29 = (0 - (4 * max_f(0, min_f(mydsp_faustpower4_f(fSlow28), 0.999999))));
		var iSlow30 = this.fCheckbox7;
		var fSlow31 = min_f(1.4142, (1.41421 * fSlow28));
		var fSlow32 = (fSlow31 * (fSlow31 + 1.41421));
		var fSlow33 = (1.41421 * fSlow31);
		var fSlow34 = (fSlow33 + 2);
		var fSlow35 = (fSlow31 * (fSlow31 + -1.41421));
		var fSlow36 = (2 - fSlow33);
		var fSlow37 = mydsp_faustpower2_f((1.4142 * fSlow28));
		var fSlow38 = (1.99998 * fSlow28);
		var fSlow39 = (fSlow37 + fSlow38);
		var fSlow40 = (fSlow38 + 2);
		var fSlow41 = (2 - fSlow38);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec4[0] = (fSlow4 + (0.999 * this.fRec4[1]));
			this.fRec15[0] = (fSlow7 + (0.999 * this.fRec15[1]));
			var fTemp0 = (this.fConst14 * this.fRec15[0]);
			var fTemp1 = (1 - fTemp0);
			this.fRec17[0] = (fSlow10 + (0.999 * this.fRec17[1]));
			this.fRec18[0] = (fSlow11 + (0.999 * this.fRec18[1]));
			this.fRec20[0] = (fSlow18 + (fSlow17 * this.fRec20[1]));
			var fTemp2 = max_f(20, Math.abs(this.fRec20[0]));
			this.fVec1[0] = fTemp2;
			var fTemp3 = (this.fRec19[1] + (this.fConst15 * this.fVec1[1]));
			this.fRec19[0] = (fTemp3 - Math.floor(fTemp3));
			var fTemp4 = (2 * this.fRec19[0]);
			var fTemp5 = (fTemp4 + -1);
			var fTemp6 = mydsp_faustpower2_f(fTemp5);
			this.fVec2[0] = fTemp6;
			var fTemp7 = mydsp_faustpower3_f(fTemp5);
			this.fVec3[0] = (fTemp7 + (1 - fTemp4));
			var fTemp8 = ((fTemp7 + (1 - (fTemp4 + this.fVec3[1]))) / fTemp2);
			this.fVec4[0] = fTemp8;
			var fTemp9 = (fTemp6 * (fTemp6 + -2));
			this.fVec5[0] = fTemp9;
			var fTemp10 = ((fTemp9 - this.fVec5[1]) / fTemp2);
			this.fVec6[0] = fTemp10;
			var fTemp11 = ((fTemp10 - this.fVec6[1]) / fTemp2);
			this.fVec7[0] = fTemp11;
			var fTemp12 = max_f(20, Math.abs((fSlow20 * this.fRec20[0])));
			this.fVec8[0] = fTemp12;
			var fTemp13 = (this.fRec21[1] + (this.fConst15 * this.fVec8[1]));
			this.fRec21[0] = (fTemp13 - Math.floor(fTemp13));
			var fTemp14 = (2 * this.fRec21[0]);
			var fTemp15 = (fTemp14 + -1);
			var fTemp16 = mydsp_faustpower2_f(fTemp15);
			this.fVec9[0] = fTemp16;
			var fTemp17 = mydsp_faustpower3_f(fTemp15);
			this.fVec10[0] = (fTemp17 + (1 - fTemp14));
			var fTemp18 = ((fTemp17 + (1 - (fTemp14 + this.fVec10[1]))) / fTemp12);
			this.fVec11[0] = fTemp18;
			var fTemp19 = (fTemp16 * (fTemp16 + -2));
			this.fVec12[0] = fTemp19;
			var fTemp20 = ((fTemp19 - this.fVec12[1]) / fTemp12);
			this.fVec13[0] = fTemp20;
			var fTemp21 = ((fTemp20 - this.fVec13[1]) / fTemp12);
			this.fVec14[0] = fTemp21;
			var fTemp22 = max_f(20, Math.abs((fSlow21 * this.fRec20[0])));
			this.fVec15[0] = fTemp22;
			var fTemp23 = (this.fRec22[1] + (this.fConst15 * this.fVec15[1]));
			this.fRec22[0] = (fTemp23 - Math.floor(fTemp23));
			var fTemp24 = (2 * this.fRec22[0]);
			var fTemp25 = (fTemp24 + -1);
			var fTemp26 = mydsp_faustpower2_f(fTemp25);
			this.fVec16[0] = fTemp26;
			var fTemp27 = mydsp_faustpower3_f(fTemp25);
			this.fVec17[0] = (fTemp27 + (1 - fTemp24));
			var fTemp28 = ((fTemp27 + (1 - (fTemp24 + this.fVec17[1]))) / fTemp22);
			this.fVec18[0] = fTemp28;
			var fTemp29 = (fTemp26 * (fTemp26 + -2));
			this.fVec19[0] = fTemp29;
			var fTemp30 = ((fTemp29 - this.fVec19[1]) / fTemp22);
			this.fVec20[0] = fTemp30;
			var fTemp31 = ((fTemp30 - this.fVec20[1]) / fTemp22);
			this.fVec21[0] = fTemp31;
			this.iRec23[0] = ((1103515245 * this.iRec23[1]) + 12345);
			var fTemp32 = (4.65661e-10 * this.iRec23[0]);
			this.fRec24[0] = (((0.522189 * this.fRec24[3]) + (fTemp32 + (2.49496 * this.fRec24[1]))) - (2.01727 * this.fRec24[2]));
			var fTemp33 = (this.fRec18[0] * (iSlow12?input0[i]:(iSlow13?(iSlow22?(((0.049922 * this.fRec24[0]) + (0.0506127 * this.fRec24[2])) - ((0.0959935 * this.fRec24[1]) + (0.00440879 * this.fRec24[3]))):fTemp32):(0.333333 * (this.fRec18[0] * (((iSlow15?(iSlow19?(this.fConst18 * ((this.iVec0[3] * (fTemp11 - this.fVec7[1])) / fTemp2)):(this.fConst17 * ((this.iVec0[2] * (fTemp8 - this.fVec4[1])) / fTemp2))):(iSlow16?(this.fConst16 * ((this.iVec0[1] * (fTemp6 - this.fVec2[1])) / fTemp2)):fTemp5)) + (iSlow15?(iSlow19?(this.fConst18 * ((this.iVec0[3] * (fTemp21 - this.fVec14[1])) / fTemp12)):(this.fConst17 * ((this.iVec0[2] * (fTemp18 - this.fVec11[1])) / fTemp12))):(iSlow16?(this.fConst16 * ((this.iVec0[1] * (fTemp16 - this.fVec9[1])) / fTemp12)):fTemp15))) + (iSlow15?(iSlow19?(this.fConst18 * ((this.iVec0[3] * (fTemp31 - this.fVec21[1])) / fTemp22)):(this.fConst17 * ((this.iVec0[2] * (fTemp28 - this.fVec18[1])) / fTemp22))):(iSlow16?(this.fConst16 * ((this.iVec0[1] * (fTemp26 - this.fVec16[1])) / fTemp22)):fTemp25))))))));
			this.fRec25[0] = (fSlow25 + (0.999 * this.fRec25[1]));
			this.fRec26[0] = (fSlow26 + (0.999 * this.fRec26[1]));
			this.fRec16[0] = ((this.fRec17[0] * (iSlow8?0:fTemp33)) - ((this.fRec25[0] * this.fRec16[1]) + (this.fRec26[0] * this.fRec16[2])));
			var fTemp34 = (iSlow8?fTemp33:(this.fRec16[0] - this.fRec16[1]));
			this.fRec14[0] = (((fTemp1 * this.fRec14[1]) + (iSlow6?0:fTemp34)) - (3.2 * this.fRec10[1]));
			this.fRec13[0] = (this.fRec14[0] + (fTemp1 * this.fRec13[1]));
			this.fRec12[0] = (this.fRec13[0] + (fTemp1 * this.fRec12[1]));
			this.fRec11[0] = (this.fRec12[0] + (this.fRec11[1] * fTemp1));
			this.fRec10[0] = (this.fRec11[0] * Math.pow(fTemp0, 4));
			var fTemp35 = (iSlow6?fTemp34:(4 * this.fRec10[0]));
			var fTemp36 = (iSlow3?0:fTemp35);
			this.fRec27[0] = (fSlow27 + (0.999 * this.fRec27[1]));
			var fTemp37 = (this.fConst14 * this.fRec27[0]);
			var fTemp38 = (1 - fTemp37);
			this.fRec9[0] = (fTemp36 + ((fTemp38 * this.fRec9[1]) + (fSlow29 * this.fRec5[1])));
			this.fRec8[0] = (this.fRec9[0] + (fTemp38 * this.fRec8[1]));
			this.fRec7[0] = (this.fRec8[0] + (fTemp38 * this.fRec7[1]));
			this.fRec6[0] = (this.fRec7[0] + (this.fRec6[1] * fTemp38));
			this.fRec5[0] = (this.fRec6[0] * Math.pow(fTemp37, 4));
			this.fRec30[0] = (fSlow27 + (0.999 * this.fRec30[1]));
			var fTemp39 = Math.tan((this.fConst21 * max_f(20, min_f(10000, this.fRec30[0]))));
			var fTemp40 = (1 / fTemp39);
			var fTemp41 = (1 - (1 / mydsp_faustpower2_f(fTemp39)));
			var fTemp42 = (fSlow32 + (((fSlow34 + fTemp40) / fTemp39) + 1));
			this.fRec29[0] = (fTemp36 - (((this.fRec29[2] * (fSlow32 + (((fTemp40 - fSlow34) / fTemp39) + 1))) + (2 * (this.fRec29[1] * (fSlow32 + fTemp41)))) / fTemp42));
			var fTemp43 = (fSlow35 + (((fSlow36 + fTemp40) / fTemp39) + 1));
			this.fRec28[0] = (((this.fRec29[2] + (this.fRec29[0] + (2 * this.fRec29[1]))) / fTemp42) - (((this.fRec28[2] * (fSlow35 + (((fTemp40 - fSlow36) / fTemp39) + 1))) + (2 * (this.fRec28[1] * (fSlow35 + fTemp41)))) / fTemp43));
			var fTemp44 = Math.tan((this.fConst21 * max_f(this.fRec30[0], 20)));
			var fTemp45 = (1 / fTemp44);
			var fTemp46 = (fSlow39 + (((fSlow40 + fTemp45) / fTemp44) + 1));
			var fTemp47 = ((fSlow39 + (1 - ((fSlow40 - fTemp45) / fTemp44))) / fTemp46);
			var fTemp48 = max_f(-0.9999, min_f(0.9999, fTemp47));
			var fTemp49 = (1 - mydsp_faustpower2_f(fTemp48));
			var fTemp50 = Math.sqrt(max_f(0, fTemp49));
			var fTemp51 = ((this.fRec31[1] * (0 - fTemp48)) + (fTemp36 * fTemp50));
			var fTemp52 = (1 - (1 / mydsp_faustpower2_f(fTemp44)));
			var fTemp53 = (fSlow39 + fTemp52);
			var fTemp54 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp53 / (fTemp46 * (fTemp47 + 1))))));
			var fTemp55 = (1 - mydsp_faustpower2_f(fTemp54));
			var fTemp56 = Math.sqrt(max_f(0, fTemp55));
			this.fRec33[0] = ((this.fRec33[1] * (0 - fTemp54)) + (fTemp51 * fTemp56));
			this.fRec31[0] = ((fTemp51 * fTemp54) + (this.fRec33[1] * fTemp56));
			var fRec32 = this.fRec33[0];
			var fTemp57 = (1 - (fTemp53 / fTemp46));
			var fTemp58 = Math.sqrt(fTemp49);
			var fTemp59 = ((((fTemp36 * fTemp48) + (this.fRec31[1] * fTemp50)) + (2 * ((this.fRec31[0] * fTemp57) / fTemp58))) + ((fRec32 * ((1 - fTemp47) - (2 * (fTemp54 * fTemp57)))) / (fTemp58 * Math.sqrt(fTemp55))));
			var fTemp60 = (fSlow37 + ((((fSlow41 + fTemp45) / fTemp44) + 1) - fSlow38));
			var fTemp61 = ((fSlow37 + ((((fTemp45 - fSlow41) / fTemp44) + 1) - fSlow38)) / fTemp60);
			var fTemp62 = max_f(-0.9999, min_f(0.9999, fTemp61));
			var fTemp63 = (1 - mydsp_faustpower2_f(fTemp62));
			var fTemp64 = Math.sqrt(max_f(0, fTemp63));
			var fTemp65 = ((this.fRec34[1] * (0 - fTemp62)) + ((fTemp59 * fTemp64) / fTemp46));
			var fTemp66 = (fSlow37 + (fTemp52 - fSlow38));
			var fTemp67 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp66 / (fTemp60 * (fTemp61 + 1))))));
			var fTemp68 = (1 - mydsp_faustpower2_f(fTemp67));
			var fTemp69 = Math.sqrt(max_f(0, fTemp68));
			this.fRec36[0] = ((this.fRec36[1] * (0 - fTemp67)) + (fTemp65 * fTemp69));
			this.fRec34[0] = ((fTemp65 * fTemp67) + (this.fRec36[1] * fTemp69));
			var fRec35 = this.fRec36[0];
			var fTemp70 = (1 - (fTemp66 / fTemp60));
			var fTemp71 = Math.sqrt(fTemp63);
			var fTemp72 = (iSlow3?fTemp35:(this.fRec4[0] * (iSlow5?(iSlow30?((((((fTemp59 * fTemp62) / fTemp46) + (this.fRec34[1] * fTemp64)) + (2 * ((this.fRec34[0] * fTemp70) / fTemp71))) + ((fRec35 * ((1 - fTemp61) - (2 * (fTemp67 * fTemp70)))) / (fTemp71 * Math.sqrt(fTemp68)))) / fTemp60):((this.fRec28[2] + (this.fRec28[0] + (2 * this.fRec28[1]))) / fTemp43)):this.fRec5[0])));
			this.fRec3[0] = (fTemp72 - (this.fConst11 * ((this.fConst22 * this.fRec3[2]) + (this.fConst24 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[1]) + (this.fConst25 * this.fRec3[0])) + (this.fConst25 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst26 * this.fRec2[2]) + (this.fConst27 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst28 * this.fRec2[0])) + (this.fConst28 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst29 * this.fRec1[2]) + (this.fConst30 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst31 * this.fRec1[0])) + (this.fConst31 * this.fRec1[2]))))));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec43[0] = (fTemp72 - (this.fConst48 * ((this.fConst51 * this.fRec43[2]) + (this.fConst52 * this.fRec43[1]))));
			this.fRec42[0] = ((this.fConst48 * (((this.fConst50 * this.fRec43[1]) + (this.fConst53 * this.fRec43[0])) + (this.fConst53 * this.fRec43[2]))) - (this.fConst46 * ((this.fConst54 * this.fRec42[2]) + (this.fConst55 * this.fRec42[1]))));
			this.fRec41[0] = ((this.fConst46 * (((this.fConst47 * this.fRec42[1]) + (this.fConst56 * this.fRec42[0])) + (this.fConst56 * this.fRec42[2]))) - (this.fConst44 * ((this.fConst57 * this.fRec41[2]) + (this.fConst58 * this.fRec41[1]))));
			var fTemp73 = (this.fConst44 * (((this.fConst45 * this.fRec41[1]) + (this.fConst59 * this.fRec41[0])) + (this.fConst59 * this.fRec41[2])));
			this.fRec40[0] = (fTemp73 - (this.fConst41 * ((this.fConst60 * this.fRec40[2]) + (this.fConst62 * this.fRec40[1]))));
			this.fRec39[0] = ((this.fConst41 * (((this.fConst43 * this.fRec40[1]) + (this.fConst63 * this.fRec40[0])) + (this.fConst63 * this.fRec40[2]))) - (this.fConst38 * ((this.fConst64 * this.fRec39[2]) + (this.fConst65 * this.fRec39[1]))));
			this.fRec38[0] = ((this.fConst38 * (((this.fConst40 * this.fRec39[1]) + (this.fConst66 * this.fRec39[0])) + (this.fConst66 * this.fRec39[2]))) - (this.fConst34 * ((this.fConst67 * this.fRec38[2]) + (this.fConst68 * this.fRec38[1]))));
			this.fRec37[0] = ((fSlow1 * this.fRec37[1]) + (fSlow2 * Math.abs((this.fConst34 * (((this.fConst37 * this.fRec38[1]) + (this.fConst69 * this.fRec38[0])) + (this.fConst69 * this.fRec38[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec37[0]))));
			this.fRec50[0] = (fTemp73 - (this.fConst86 * ((this.fConst89 * this.fRec50[2]) + (this.fConst90 * this.fRec50[1]))));
			this.fRec49[0] = ((this.fConst86 * (((this.fConst88 * this.fRec50[1]) + (this.fConst91 * this.fRec50[0])) + (this.fConst91 * this.fRec50[2]))) - (this.fConst84 * ((this.fConst92 * this.fRec49[2]) + (this.fConst93 * this.fRec49[1]))));
			this.fRec48[0] = ((this.fConst84 * (((this.fConst85 * this.fRec49[1]) + (this.fConst94 * this.fRec49[0])) + (this.fConst94 * this.fRec49[2]))) - (this.fConst82 * ((this.fConst95 * this.fRec48[2]) + (this.fConst96 * this.fRec48[1]))));
			var fTemp74 = (this.fConst82 * (((this.fConst83 * this.fRec48[1]) + (this.fConst97 * this.fRec48[0])) + (this.fConst97 * this.fRec48[2])));
			this.fRec47[0] = (fTemp74 - (this.fConst79 * ((this.fConst98 * this.fRec47[2]) + (this.fConst100 * this.fRec47[1]))));
			this.fRec46[0] = ((this.fConst79 * (((this.fConst81 * this.fRec47[1]) + (this.fConst101 * this.fRec47[0])) + (this.fConst101 * this.fRec47[2]))) - (this.fConst76 * ((this.fConst102 * this.fRec46[2]) + (this.fConst103 * this.fRec46[1]))));
			this.fRec45[0] = ((this.fConst76 * (((this.fConst78 * this.fRec46[1]) + (this.fConst104 * this.fRec46[0])) + (this.fConst104 * this.fRec46[2]))) - (this.fConst72 * ((this.fConst105 * this.fRec45[2]) + (this.fConst106 * this.fRec45[1]))));
			this.fRec44[0] = ((fSlow1 * this.fRec44[1]) + (fSlow2 * Math.abs((this.fConst72 * (((this.fConst75 * this.fRec45[1]) + (this.fConst107 * this.fRec45[0])) + (this.fConst107 * this.fRec45[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec44[0]))));
			this.fRec57[0] = (fTemp74 - (this.fConst124 * ((this.fConst127 * this.fRec57[2]) + (this.fConst128 * this.fRec57[1]))));
			this.fRec56[0] = ((this.fConst124 * (((this.fConst126 * this.fRec57[1]) + (this.fConst129 * this.fRec57[0])) + (this.fConst129 * this.fRec57[2]))) - (this.fConst122 * ((this.fConst130 * this.fRec56[2]) + (this.fConst131 * this.fRec56[1]))));
			this.fRec55[0] = ((this.fConst122 * (((this.fConst123 * this.fRec56[1]) + (this.fConst132 * this.fRec56[0])) + (this.fConst132 * this.fRec56[2]))) - (this.fConst120 * ((this.fConst133 * this.fRec55[2]) + (this.fConst134 * this.fRec55[1]))));
			var fTemp75 = (this.fConst120 * (((this.fConst121 * this.fRec55[1]) + (this.fConst135 * this.fRec55[0])) + (this.fConst135 * this.fRec55[2])));
			this.fRec54[0] = (fTemp75 - (this.fConst117 * ((this.fConst136 * this.fRec54[2]) + (this.fConst138 * this.fRec54[1]))));
			this.fRec53[0] = ((this.fConst117 * (((this.fConst119 * this.fRec54[1]) + (this.fConst139 * this.fRec54[0])) + (this.fConst139 * this.fRec54[2]))) - (this.fConst114 * ((this.fConst140 * this.fRec53[2]) + (this.fConst141 * this.fRec53[1]))));
			this.fRec52[0] = ((this.fConst114 * (((this.fConst116 * this.fRec53[1]) + (this.fConst142 * this.fRec53[0])) + (this.fConst142 * this.fRec53[2]))) - (this.fConst110 * ((this.fConst143 * this.fRec52[2]) + (this.fConst144 * this.fRec52[1]))));
			this.fRec51[0] = ((fSlow1 * this.fRec51[1]) + (fSlow2 * Math.abs((this.fConst110 * (((this.fConst113 * this.fRec52[1]) + (this.fConst145 * this.fRec52[0])) + (this.fConst145 * this.fRec52[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec51[0]))));
			this.fRec64[0] = (fTemp75 - (this.fConst162 * ((this.fConst165 * this.fRec64[2]) + (this.fConst166 * this.fRec64[1]))));
			this.fRec63[0] = ((this.fConst162 * (((this.fConst164 * this.fRec64[1]) + (this.fConst167 * this.fRec64[0])) + (this.fConst167 * this.fRec64[2]))) - (this.fConst160 * ((this.fConst168 * this.fRec63[2]) + (this.fConst169 * this.fRec63[1]))));
			this.fRec62[0] = ((this.fConst160 * (((this.fConst161 * this.fRec63[1]) + (this.fConst170 * this.fRec63[0])) + (this.fConst170 * this.fRec63[2]))) - (this.fConst158 * ((this.fConst171 * this.fRec62[2]) + (this.fConst172 * this.fRec62[1]))));
			var fTemp76 = (this.fConst158 * (((this.fConst159 * this.fRec62[1]) + (this.fConst173 * this.fRec62[0])) + (this.fConst173 * this.fRec62[2])));
			this.fRec61[0] = (fTemp76 - (this.fConst155 * ((this.fConst174 * this.fRec61[2]) + (this.fConst176 * this.fRec61[1]))));
			this.fRec60[0] = ((this.fConst155 * (((this.fConst157 * this.fRec61[1]) + (this.fConst177 * this.fRec61[0])) + (this.fConst177 * this.fRec61[2]))) - (this.fConst152 * ((this.fConst178 * this.fRec60[2]) + (this.fConst179 * this.fRec60[1]))));
			this.fRec59[0] = ((this.fConst152 * (((this.fConst154 * this.fRec60[1]) + (this.fConst180 * this.fRec60[0])) + (this.fConst180 * this.fRec60[2]))) - (this.fConst148 * ((this.fConst181 * this.fRec59[2]) + (this.fConst182 * this.fRec59[1]))));
			this.fRec58[0] = ((fSlow1 * this.fRec58[1]) + (fSlow2 * Math.abs((this.fConst148 * (((this.fConst151 * this.fRec59[1]) + (this.fConst183 * this.fRec59[0])) + (this.fConst183 * this.fRec59[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec58[0]))));
			this.fRec71[0] = (fTemp76 - (this.fConst200 * ((this.fConst203 * this.fRec71[2]) + (this.fConst204 * this.fRec71[1]))));
			this.fRec70[0] = ((this.fConst200 * (((this.fConst202 * this.fRec71[1]) + (this.fConst205 * this.fRec71[0])) + (this.fConst205 * this.fRec71[2]))) - (this.fConst198 * ((this.fConst206 * this.fRec70[2]) + (this.fConst207 * this.fRec70[1]))));
			this.fRec69[0] = ((this.fConst198 * (((this.fConst199 * this.fRec70[1]) + (this.fConst208 * this.fRec70[0])) + (this.fConst208 * this.fRec70[2]))) - (this.fConst196 * ((this.fConst209 * this.fRec69[2]) + (this.fConst210 * this.fRec69[1]))));
			var fTemp77 = (this.fConst196 * (((this.fConst197 * this.fRec69[1]) + (this.fConst211 * this.fRec69[0])) + (this.fConst211 * this.fRec69[2])));
			this.fRec68[0] = (fTemp77 - (this.fConst193 * ((this.fConst212 * this.fRec68[2]) + (this.fConst214 * this.fRec68[1]))));
			this.fRec67[0] = ((this.fConst193 * (((this.fConst195 * this.fRec68[1]) + (this.fConst215 * this.fRec68[0])) + (this.fConst215 * this.fRec68[2]))) - (this.fConst190 * ((this.fConst216 * this.fRec67[2]) + (this.fConst217 * this.fRec67[1]))));
			this.fRec66[0] = ((this.fConst190 * (((this.fConst192 * this.fRec67[1]) + (this.fConst218 * this.fRec67[0])) + (this.fConst218 * this.fRec67[2]))) - (this.fConst186 * ((this.fConst219 * this.fRec66[2]) + (this.fConst220 * this.fRec66[1]))));
			this.fRec65[0] = ((fSlow1 * this.fRec65[1]) + (fSlow2 * Math.abs((this.fConst186 * (((this.fConst189 * this.fRec66[1]) + (this.fConst221 * this.fRec66[0])) + (this.fConst221 * this.fRec66[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec65[0]))));
			this.fRec78[0] = (fTemp77 - (this.fConst238 * ((this.fConst241 * this.fRec78[2]) + (this.fConst242 * this.fRec78[1]))));
			this.fRec77[0] = ((this.fConst238 * (((this.fConst240 * this.fRec78[1]) + (this.fConst243 * this.fRec78[0])) + (this.fConst243 * this.fRec78[2]))) - (this.fConst236 * ((this.fConst244 * this.fRec77[2]) + (this.fConst245 * this.fRec77[1]))));
			this.fRec76[0] = ((this.fConst236 * (((this.fConst237 * this.fRec77[1]) + (this.fConst246 * this.fRec77[0])) + (this.fConst246 * this.fRec77[2]))) - (this.fConst234 * ((this.fConst247 * this.fRec76[2]) + (this.fConst248 * this.fRec76[1]))));
			var fTemp78 = (this.fConst234 * (((this.fConst235 * this.fRec76[1]) + (this.fConst249 * this.fRec76[0])) + (this.fConst249 * this.fRec76[2])));
			this.fRec75[0] = (fTemp78 - (this.fConst231 * ((this.fConst250 * this.fRec75[2]) + (this.fConst252 * this.fRec75[1]))));
			this.fRec74[0] = ((this.fConst231 * (((this.fConst233 * this.fRec75[1]) + (this.fConst253 * this.fRec75[0])) + (this.fConst253 * this.fRec75[2]))) - (this.fConst228 * ((this.fConst254 * this.fRec74[2]) + (this.fConst255 * this.fRec74[1]))));
			this.fRec73[0] = ((this.fConst228 * (((this.fConst230 * this.fRec74[1]) + (this.fConst256 * this.fRec74[0])) + (this.fConst256 * this.fRec74[2]))) - (this.fConst224 * ((this.fConst257 * this.fRec73[2]) + (this.fConst258 * this.fRec73[1]))));
			this.fRec72[0] = ((fSlow1 * this.fRec72[1]) + (fSlow2 * Math.abs((this.fConst224 * (((this.fConst227 * this.fRec73[1]) + (this.fConst259 * this.fRec73[0])) + (this.fConst259 * this.fRec73[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec72[0]))));
			this.fRec85[0] = (fTemp78 - (this.fConst276 * ((this.fConst279 * this.fRec85[2]) + (this.fConst280 * this.fRec85[1]))));
			this.fRec84[0] = ((this.fConst276 * (((this.fConst278 * this.fRec85[1]) + (this.fConst281 * this.fRec85[0])) + (this.fConst281 * this.fRec85[2]))) - (this.fConst274 * ((this.fConst282 * this.fRec84[2]) + (this.fConst283 * this.fRec84[1]))));
			this.fRec83[0] = ((this.fConst274 * (((this.fConst275 * this.fRec84[1]) + (this.fConst284 * this.fRec84[0])) + (this.fConst284 * this.fRec84[2]))) - (this.fConst272 * ((this.fConst285 * this.fRec83[2]) + (this.fConst286 * this.fRec83[1]))));
			var fTemp79 = (this.fConst272 * (((this.fConst273 * this.fRec83[1]) + (this.fConst287 * this.fRec83[0])) + (this.fConst287 * this.fRec83[2])));
			this.fRec82[0] = (fTemp79 - (this.fConst269 * ((this.fConst288 * this.fRec82[2]) + (this.fConst290 * this.fRec82[1]))));
			this.fRec81[0] = ((this.fConst269 * (((this.fConst271 * this.fRec82[1]) + (this.fConst291 * this.fRec82[0])) + (this.fConst291 * this.fRec82[2]))) - (this.fConst266 * ((this.fConst292 * this.fRec81[2]) + (this.fConst293 * this.fRec81[1]))));
			this.fRec80[0] = ((this.fConst266 * (((this.fConst268 * this.fRec81[1]) + (this.fConst294 * this.fRec81[0])) + (this.fConst294 * this.fRec81[2]))) - (this.fConst262 * ((this.fConst295 * this.fRec80[2]) + (this.fConst296 * this.fRec80[1]))));
			this.fRec79[0] = ((fSlow1 * this.fRec79[1]) + (fSlow2 * Math.abs((this.fConst262 * (((this.fConst265 * this.fRec80[1]) + (this.fConst297 * this.fRec80[0])) + (this.fConst297 * this.fRec80[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec79[0]))));
			this.fRec92[0] = (fTemp79 - (this.fConst314 * ((this.fConst317 * this.fRec92[2]) + (this.fConst318 * this.fRec92[1]))));
			this.fRec91[0] = ((this.fConst314 * (((this.fConst316 * this.fRec92[1]) + (this.fConst319 * this.fRec92[0])) + (this.fConst319 * this.fRec92[2]))) - (this.fConst312 * ((this.fConst320 * this.fRec91[2]) + (this.fConst321 * this.fRec91[1]))));
			this.fRec90[0] = ((this.fConst312 * (((this.fConst313 * this.fRec91[1]) + (this.fConst322 * this.fRec91[0])) + (this.fConst322 * this.fRec91[2]))) - (this.fConst310 * ((this.fConst323 * this.fRec90[2]) + (this.fConst324 * this.fRec90[1]))));
			var fTemp80 = (this.fConst310 * (((this.fConst311 * this.fRec90[1]) + (this.fConst325 * this.fRec90[0])) + (this.fConst325 * this.fRec90[2])));
			this.fRec89[0] = (fTemp80 - (this.fConst307 * ((this.fConst326 * this.fRec89[2]) + (this.fConst328 * this.fRec89[1]))));
			this.fRec88[0] = ((this.fConst307 * (((this.fConst309 * this.fRec89[1]) + (this.fConst329 * this.fRec89[0])) + (this.fConst329 * this.fRec89[2]))) - (this.fConst304 * ((this.fConst330 * this.fRec88[2]) + (this.fConst331 * this.fRec88[1]))));
			this.fRec87[0] = ((this.fConst304 * (((this.fConst306 * this.fRec88[1]) + (this.fConst332 * this.fRec88[0])) + (this.fConst332 * this.fRec88[2]))) - (this.fConst300 * ((this.fConst333 * this.fRec87[2]) + (this.fConst334 * this.fRec87[1]))));
			this.fRec86[0] = ((fSlow1 * this.fRec86[1]) + (fSlow2 * Math.abs((this.fConst300 * (((this.fConst303 * this.fRec87[1]) + (this.fConst335 * this.fRec87[0])) + (this.fConst335 * this.fRec87[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec86[0]))));
			this.fRec99[0] = (fTemp80 - (this.fConst352 * ((this.fConst355 * this.fRec99[2]) + (this.fConst356 * this.fRec99[1]))));
			this.fRec98[0] = ((this.fConst352 * (((this.fConst354 * this.fRec99[1]) + (this.fConst357 * this.fRec99[0])) + (this.fConst357 * this.fRec99[2]))) - (this.fConst350 * ((this.fConst358 * this.fRec98[2]) + (this.fConst359 * this.fRec98[1]))));
			this.fRec97[0] = ((this.fConst350 * (((this.fConst351 * this.fRec98[1]) + (this.fConst360 * this.fRec98[0])) + (this.fConst360 * this.fRec98[2]))) - (this.fConst348 * ((this.fConst361 * this.fRec97[2]) + (this.fConst362 * this.fRec97[1]))));
			var fTemp81 = (this.fConst348 * (((this.fConst349 * this.fRec97[1]) + (this.fConst363 * this.fRec97[0])) + (this.fConst363 * this.fRec97[2])));
			this.fRec96[0] = (fTemp81 - (this.fConst345 * ((this.fConst364 * this.fRec96[2]) + (this.fConst366 * this.fRec96[1]))));
			this.fRec95[0] = ((this.fConst345 * (((this.fConst347 * this.fRec96[1]) + (this.fConst367 * this.fRec96[0])) + (this.fConst367 * this.fRec96[2]))) - (this.fConst342 * ((this.fConst368 * this.fRec95[2]) + (this.fConst369 * this.fRec95[1]))));
			this.fRec94[0] = ((this.fConst342 * (((this.fConst344 * this.fRec95[1]) + (this.fConst370 * this.fRec95[0])) + (this.fConst370 * this.fRec95[2]))) - (this.fConst338 * ((this.fConst371 * this.fRec94[2]) + (this.fConst372 * this.fRec94[1]))));
			this.fRec93[0] = ((fSlow1 * this.fRec93[1]) + (fSlow2 * Math.abs((this.fConst338 * (((this.fConst341 * this.fRec94[1]) + (this.fConst373 * this.fRec94[0])) + (this.fConst373 * this.fRec94[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec93[0]))));
			this.fRec106[0] = (fTemp81 - (this.fConst390 * ((this.fConst393 * this.fRec106[2]) + (this.fConst394 * this.fRec106[1]))));
			this.fRec105[0] = ((this.fConst390 * (((this.fConst392 * this.fRec106[1]) + (this.fConst395 * this.fRec106[0])) + (this.fConst395 * this.fRec106[2]))) - (this.fConst388 * ((this.fConst396 * this.fRec105[2]) + (this.fConst397 * this.fRec105[1]))));
			this.fRec104[0] = ((this.fConst388 * (((this.fConst389 * this.fRec105[1]) + (this.fConst398 * this.fRec105[0])) + (this.fConst398 * this.fRec105[2]))) - (this.fConst386 * ((this.fConst399 * this.fRec104[2]) + (this.fConst400 * this.fRec104[1]))));
			var fTemp82 = (this.fConst386 * (((this.fConst387 * this.fRec104[1]) + (this.fConst401 * this.fRec104[0])) + (this.fConst401 * this.fRec104[2])));
			this.fRec103[0] = (fTemp82 - (this.fConst383 * ((this.fConst402 * this.fRec103[2]) + (this.fConst404 * this.fRec103[1]))));
			this.fRec102[0] = ((this.fConst383 * (((this.fConst385 * this.fRec103[1]) + (this.fConst405 * this.fRec103[0])) + (this.fConst405 * this.fRec103[2]))) - (this.fConst380 * ((this.fConst406 * this.fRec102[2]) + (this.fConst407 * this.fRec102[1]))));
			this.fRec101[0] = ((this.fConst380 * (((this.fConst382 * this.fRec102[1]) + (this.fConst408 * this.fRec102[0])) + (this.fConst408 * this.fRec102[2]))) - (this.fConst376 * ((this.fConst409 * this.fRec101[2]) + (this.fConst410 * this.fRec101[1]))));
			this.fRec100[0] = ((fSlow1 * this.fRec100[1]) + (fSlow2 * Math.abs((this.fConst376 * (((this.fConst379 * this.fRec101[1]) + (this.fConst411 * this.fRec101[0])) + (this.fConst411 * this.fRec101[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec100[0]))));
			this.fRec113[0] = (fTemp82 - (this.fConst428 * ((this.fConst431 * this.fRec113[2]) + (this.fConst432 * this.fRec113[1]))));
			this.fRec112[0] = ((this.fConst428 * (((this.fConst430 * this.fRec113[1]) + (this.fConst433 * this.fRec113[0])) + (this.fConst433 * this.fRec113[2]))) - (this.fConst426 * ((this.fConst434 * this.fRec112[2]) + (this.fConst435 * this.fRec112[1]))));
			this.fRec111[0] = ((this.fConst426 * (((this.fConst427 * this.fRec112[1]) + (this.fConst436 * this.fRec112[0])) + (this.fConst436 * this.fRec112[2]))) - (this.fConst424 * ((this.fConst437 * this.fRec111[2]) + (this.fConst438 * this.fRec111[1]))));
			var fTemp83 = (this.fConst424 * (((this.fConst425 * this.fRec111[1]) + (this.fConst439 * this.fRec111[0])) + (this.fConst439 * this.fRec111[2])));
			this.fRec110[0] = (fTemp83 - (this.fConst421 * ((this.fConst440 * this.fRec110[2]) + (this.fConst442 * this.fRec110[1]))));
			this.fRec109[0] = ((this.fConst421 * (((this.fConst423 * this.fRec110[1]) + (this.fConst443 * this.fRec110[0])) + (this.fConst443 * this.fRec110[2]))) - (this.fConst418 * ((this.fConst444 * this.fRec109[2]) + (this.fConst445 * this.fRec109[1]))));
			this.fRec108[0] = ((this.fConst418 * (((this.fConst420 * this.fRec109[1]) + (this.fConst446 * this.fRec109[0])) + (this.fConst446 * this.fRec109[2]))) - (this.fConst414 * ((this.fConst447 * this.fRec108[2]) + (this.fConst448 * this.fRec108[1]))));
			this.fRec107[0] = ((fSlow1 * this.fRec107[1]) + (fSlow2 * Math.abs((this.fConst414 * (((this.fConst417 * this.fRec108[1]) + (this.fConst449 * this.fRec108[0])) + (this.fConst449 * this.fRec108[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec107[0]))));
			this.fRec120[0] = (fTemp83 - (this.fConst466 * ((this.fConst469 * this.fRec120[2]) + (this.fConst470 * this.fRec120[1]))));
			this.fRec119[0] = ((this.fConst466 * (((this.fConst468 * this.fRec120[1]) + (this.fConst471 * this.fRec120[0])) + (this.fConst471 * this.fRec120[2]))) - (this.fConst464 * ((this.fConst472 * this.fRec119[2]) + (this.fConst473 * this.fRec119[1]))));
			this.fRec118[0] = ((this.fConst464 * (((this.fConst465 * this.fRec119[1]) + (this.fConst474 * this.fRec119[0])) + (this.fConst474 * this.fRec119[2]))) - (this.fConst462 * ((this.fConst475 * this.fRec118[2]) + (this.fConst476 * this.fRec118[1]))));
			var fTemp84 = (this.fConst462 * (((this.fConst463 * this.fRec118[1]) + (this.fConst477 * this.fRec118[0])) + (this.fConst477 * this.fRec118[2])));
			this.fRec117[0] = (fTemp84 - (this.fConst459 * ((this.fConst478 * this.fRec117[2]) + (this.fConst480 * this.fRec117[1]))));
			this.fRec116[0] = ((this.fConst459 * (((this.fConst461 * this.fRec117[1]) + (this.fConst481 * this.fRec117[0])) + (this.fConst481 * this.fRec117[2]))) - (this.fConst456 * ((this.fConst482 * this.fRec116[2]) + (this.fConst483 * this.fRec116[1]))));
			this.fRec115[0] = ((this.fConst456 * (((this.fConst458 * this.fRec116[1]) + (this.fConst484 * this.fRec116[0])) + (this.fConst484 * this.fRec116[2]))) - (this.fConst452 * ((this.fConst485 * this.fRec115[2]) + (this.fConst486 * this.fRec115[1]))));
			this.fRec114[0] = ((fSlow1 * this.fRec114[1]) + (fSlow2 * Math.abs((this.fConst452 * (((this.fConst455 * this.fRec115[1]) + (this.fConst487 * this.fRec115[0])) + (this.fConst487 * this.fRec115[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec114[0]))));
			this.fRec127[0] = (fTemp84 - (this.fConst504 * ((this.fConst507 * this.fRec127[2]) + (this.fConst508 * this.fRec127[1]))));
			this.fRec126[0] = ((this.fConst504 * (((this.fConst506 * this.fRec127[1]) + (this.fConst509 * this.fRec127[0])) + (this.fConst509 * this.fRec127[2]))) - (this.fConst502 * ((this.fConst510 * this.fRec126[2]) + (this.fConst511 * this.fRec126[1]))));
			this.fRec125[0] = ((this.fConst502 * (((this.fConst503 * this.fRec126[1]) + (this.fConst512 * this.fRec126[0])) + (this.fConst512 * this.fRec126[2]))) - (this.fConst500 * ((this.fConst513 * this.fRec125[2]) + (this.fConst514 * this.fRec125[1]))));
			var fTemp85 = (this.fConst500 * (((this.fConst501 * this.fRec125[1]) + (this.fConst515 * this.fRec125[0])) + (this.fConst515 * this.fRec125[2])));
			this.fRec124[0] = (fTemp85 - (this.fConst497 * ((this.fConst516 * this.fRec124[2]) + (this.fConst518 * this.fRec124[1]))));
			this.fRec123[0] = ((this.fConst497 * (((this.fConst499 * this.fRec124[1]) + (this.fConst519 * this.fRec124[0])) + (this.fConst519 * this.fRec124[2]))) - (this.fConst494 * ((this.fConst520 * this.fRec123[2]) + (this.fConst521 * this.fRec123[1]))));
			this.fRec122[0] = ((this.fConst494 * (((this.fConst496 * this.fRec123[1]) + (this.fConst522 * this.fRec123[0])) + (this.fConst522 * this.fRec123[2]))) - (this.fConst490 * ((this.fConst523 * this.fRec122[2]) + (this.fConst524 * this.fRec122[1]))));
			this.fRec121[0] = ((fSlow1 * this.fRec121[1]) + (fSlow2 * Math.abs((this.fConst490 * (((this.fConst493 * this.fRec122[1]) + (this.fConst525 * this.fRec122[0])) + (this.fConst525 * this.fRec122[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec121[0]))));
			this.fRec131[0] = (fTemp85 - (this.fConst530 * ((this.fConst533 * this.fRec131[2]) + (this.fConst534 * this.fRec131[1]))));
			this.fRec130[0] = ((this.fConst530 * (((this.fConst532 * this.fRec131[1]) + (this.fConst535 * this.fRec131[0])) + (this.fConst535 * this.fRec131[2]))) - (this.fConst528 * ((this.fConst536 * this.fRec130[2]) + (this.fConst537 * this.fRec130[1]))));
			this.fRec129[0] = ((this.fConst528 * (((this.fConst529 * this.fRec130[1]) + (this.fConst538 * this.fRec130[0])) + (this.fConst538 * this.fRec130[2]))) - (this.fConst526 * ((this.fConst539 * this.fRec129[2]) + (this.fConst540 * this.fRec129[1]))));
			this.fRec128[0] = ((fSlow1 * this.fRec128[1]) + (fSlow2 * Math.abs((this.fConst526 * (((this.fConst527 * this.fRec129[1]) + (this.fConst541 * this.fRec129[0])) + (this.fConst541 * this.fRec129[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec128[0]))));
			output0[i] = fTemp72;
			output1[i] = fTemp72;
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec4[1] = this.fRec4[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec20[1] = this.fRec20[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec19[1] = this.fRec19[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec21[1] = this.fRec21[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec22[1] = this.fRec22[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.iRec23[1] = this.iRec23[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec24[j1] = this.fRec24[(j1 - 1)];
				
			}
			this.fRec25[1] = this.fRec25[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec16[2] = this.fRec16[1];
			this.fRec16[1] = this.fRec16[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec29[2] = this.fRec29[1];
			this.fRec29[1] = this.fRec29[0];
			this.fRec28[2] = this.fRec28[1];
			this.fRec28[1] = this.fRec28[0];
			this.fRec33[1] = this.fRec33[0];
			this.fRec31[1] = this.fRec31[0];
			this.fRec36[1] = this.fRec36[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec43[2] = this.fRec43[1];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[2] = this.fRec42[1];
			this.fRec42[1] = this.fRec42[0];
			this.fRec41[2] = this.fRec41[1];
			this.fRec41[1] = this.fRec41[0];
			this.fRec40[2] = this.fRec40[1];
			this.fRec40[1] = this.fRec40[0];
			this.fRec39[2] = this.fRec39[1];
			this.fRec39[1] = this.fRec39[0];
			this.fRec38[2] = this.fRec38[1];
			this.fRec38[1] = this.fRec38[0];
			this.fRec37[1] = this.fRec37[0];
			this.fRec50[2] = this.fRec50[1];
			this.fRec50[1] = this.fRec50[0];
			this.fRec49[2] = this.fRec49[1];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[2] = this.fRec48[1];
			this.fRec48[1] = this.fRec48[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[2] = this.fRec46[1];
			this.fRec46[1] = this.fRec46[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[1] = this.fRec44[0];
			this.fRec57[2] = this.fRec57[1];
			this.fRec57[1] = this.fRec57[0];
			this.fRec56[2] = this.fRec56[1];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[2] = this.fRec55[1];
			this.fRec55[1] = this.fRec55[0];
			this.fRec54[2] = this.fRec54[1];
			this.fRec54[1] = this.fRec54[0];
			this.fRec53[2] = this.fRec53[1];
			this.fRec53[1] = this.fRec53[0];
			this.fRec52[2] = this.fRec52[1];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[1] = this.fRec51[0];
			this.fRec64[2] = this.fRec64[1];
			this.fRec64[1] = this.fRec64[0];
			this.fRec63[2] = this.fRec63[1];
			this.fRec63[1] = this.fRec63[0];
			this.fRec62[2] = this.fRec62[1];
			this.fRec62[1] = this.fRec62[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fRec60[2] = this.fRec60[1];
			this.fRec60[1] = this.fRec60[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[1] = this.fRec58[0];
			this.fRec71[2] = this.fRec71[1];
			this.fRec71[1] = this.fRec71[0];
			this.fRec70[2] = this.fRec70[1];
			this.fRec70[1] = this.fRec70[0];
			this.fRec69[2] = this.fRec69[1];
			this.fRec69[1] = this.fRec69[0];
			this.fRec68[2] = this.fRec68[1];
			this.fRec68[1] = this.fRec68[0];
			this.fRec67[2] = this.fRec67[1];
			this.fRec67[1] = this.fRec67[0];
			this.fRec66[2] = this.fRec66[1];
			this.fRec66[1] = this.fRec66[0];
			this.fRec65[1] = this.fRec65[0];
			this.fRec78[2] = this.fRec78[1];
			this.fRec78[1] = this.fRec78[0];
			this.fRec77[2] = this.fRec77[1];
			this.fRec77[1] = this.fRec77[0];
			this.fRec76[2] = this.fRec76[1];
			this.fRec76[1] = this.fRec76[0];
			this.fRec75[2] = this.fRec75[1];
			this.fRec75[1] = this.fRec75[0];
			this.fRec74[2] = this.fRec74[1];
			this.fRec74[1] = this.fRec74[0];
			this.fRec73[2] = this.fRec73[1];
			this.fRec73[1] = this.fRec73[0];
			this.fRec72[1] = this.fRec72[0];
			this.fRec85[2] = this.fRec85[1];
			this.fRec85[1] = this.fRec85[0];
			this.fRec84[2] = this.fRec84[1];
			this.fRec84[1] = this.fRec84[0];
			this.fRec83[2] = this.fRec83[1];
			this.fRec83[1] = this.fRec83[0];
			this.fRec82[2] = this.fRec82[1];
			this.fRec82[1] = this.fRec82[0];
			this.fRec81[2] = this.fRec81[1];
			this.fRec81[1] = this.fRec81[0];
			this.fRec80[2] = this.fRec80[1];
			this.fRec80[1] = this.fRec80[0];
			this.fRec79[1] = this.fRec79[0];
			this.fRec92[2] = this.fRec92[1];
			this.fRec92[1] = this.fRec92[0];
			this.fRec91[2] = this.fRec91[1];
			this.fRec91[1] = this.fRec91[0];
			this.fRec90[2] = this.fRec90[1];
			this.fRec90[1] = this.fRec90[0];
			this.fRec89[2] = this.fRec89[1];
			this.fRec89[1] = this.fRec89[0];
			this.fRec88[2] = this.fRec88[1];
			this.fRec88[1] = this.fRec88[0];
			this.fRec87[2] = this.fRec87[1];
			this.fRec87[1] = this.fRec87[0];
			this.fRec86[1] = this.fRec86[0];
			this.fRec99[2] = this.fRec99[1];
			this.fRec99[1] = this.fRec99[0];
			this.fRec98[2] = this.fRec98[1];
			this.fRec98[1] = this.fRec98[0];
			this.fRec97[2] = this.fRec97[1];
			this.fRec97[1] = this.fRec97[0];
			this.fRec96[2] = this.fRec96[1];
			this.fRec96[1] = this.fRec96[0];
			this.fRec95[2] = this.fRec95[1];
			this.fRec95[1] = this.fRec95[0];
			this.fRec94[2] = this.fRec94[1];
			this.fRec94[1] = this.fRec94[0];
			this.fRec93[1] = this.fRec93[0];
			this.fRec106[2] = this.fRec106[1];
			this.fRec106[1] = this.fRec106[0];
			this.fRec105[2] = this.fRec105[1];
			this.fRec105[1] = this.fRec105[0];
			this.fRec104[2] = this.fRec104[1];
			this.fRec104[1] = this.fRec104[0];
			this.fRec103[2] = this.fRec103[1];
			this.fRec103[1] = this.fRec103[0];
			this.fRec102[2] = this.fRec102[1];
			this.fRec102[1] = this.fRec102[0];
			this.fRec101[2] = this.fRec101[1];
			this.fRec101[1] = this.fRec101[0];
			this.fRec100[1] = this.fRec100[0];
			this.fRec113[2] = this.fRec113[1];
			this.fRec113[1] = this.fRec113[0];
			this.fRec112[2] = this.fRec112[1];
			this.fRec112[1] = this.fRec112[0];
			this.fRec111[2] = this.fRec111[1];
			this.fRec111[1] = this.fRec111[0];
			this.fRec110[2] = this.fRec110[1];
			this.fRec110[1] = this.fRec110[0];
			this.fRec109[2] = this.fRec109[1];
			this.fRec109[1] = this.fRec109[0];
			this.fRec108[2] = this.fRec108[1];
			this.fRec108[1] = this.fRec108[0];
			this.fRec107[1] = this.fRec107[0];
			this.fRec120[2] = this.fRec120[1];
			this.fRec120[1] = this.fRec120[0];
			this.fRec119[2] = this.fRec119[1];
			this.fRec119[1] = this.fRec119[0];
			this.fRec118[2] = this.fRec118[1];
			this.fRec118[1] = this.fRec118[0];
			this.fRec117[2] = this.fRec117[1];
			this.fRec117[1] = this.fRec117[0];
			this.fRec116[2] = this.fRec116[1];
			this.fRec116[1] = this.fRec116[0];
			this.fRec115[2] = this.fRec115[1];
			this.fRec115[1] = this.fRec115[0];
			this.fRec114[1] = this.fRec114[0];
			this.fRec127[2] = this.fRec127[1];
			this.fRec127[1] = this.fRec127[0];
			this.fRec126[2] = this.fRec126[1];
			this.fRec126[1] = this.fRec126[0];
			this.fRec125[2] = this.fRec125[1];
			this.fRec125[1] = this.fRec125[0];
			this.fRec124[2] = this.fRec124[1];
			this.fRec124[1] = this.fRec124[0];
			this.fRec123[2] = this.fRec123[1];
			this.fRec123[1] = this.fRec123[0];
			this.fRec122[2] = this.fRec122[1];
			this.fRec122[1] = this.fRec122[0];
			this.fRec121[1] = this.fRec121[0];
			this.fRec131[2] = this.fRec131[1];
			this.fRec131[1] = this.fRec131[0];
			this.fRec130[2] = this.fRec130[1];
			this.fRec130[1] = this.fRec130[0];
			this.fRec129[2] = this.fRec129[1];
			this.fRec129[1] = this.fRec129[0];
			this.fRec128[1] = this.fRec128[0];
			
		}
		
	}
	
}

