
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}
this.max_i = function(dummy0, dummy1);
this.min_i = function(dummy0, dummy1);
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
	this.fCheckbox1;
	this.fHslider3;
	this.fConst14;
	this.fHslider4;
	this.fRec4 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fHbargraph0;
	this.fCheckbox2;
	this.fCheckbox3;
	this.fVslider0;
	this.fRec6 = new Float32Array(2);
	this.fEntry0;
	this.fConst15;
	this.fVslider1;
	this.fVslider2;
	this.fRec8 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
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
	this.fRec9 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fCheckbox4;
	this.iRec11 = new Int32Array(2);
	this.fRec12 = new Float32Array(4);
	this.fCheckbox5;
	this.fHslider5;
	this.fHslider6;
	this.IOTA;
	this.fVec22 = new Float32Array(4096);
	this.fHslider7;
	this.fHslider8;
	this.fRec13 = new Float32Array(2);
	this.fCheckbox6;
	this.fHslider9;
	this.fCheckbox7;
	this.fHslider10;
	this.fHslider11;
	this.fHslider12;
	this.fHslider13;
	this.fHslider14;
	this.fHslider15;
	this.fRec19 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fRec18 = new Float32Array(3);
	this.fRec17 = new Float32Array(3);
	this.fRec16 = new Float32Array(3);
	this.fRec15 = new Float32Array(3);
	this.fRec14 = new Float32Array(2);
	this.fVec23 = new Float32Array(4096);
	this.fRec21 = new Float32Array(2);
	this.fRec26 = new Float32Array(3);
	this.fRec25 = new Float32Array(3);
	this.fRec24 = new Float32Array(3);
	this.fRec23 = new Float32Array(3);
	this.fRec22 = new Float32Array(2);
	this.fConst19;
	this.fConst20;
	this.fConst21;
	this.fRec3 = new Float32Array(3);
	this.fConst22;
	this.fConst23;
	this.fConst24;
	this.fRec2 = new Float32Array(3);
	this.fConst25;
	this.fConst26;
	this.fConst27;
	this.fRec1 = new Float32Array(3);
	this.fConst28;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.fConst29;
	this.fConst30;
	this.fConst31;
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
	this.fRec33 = new Float32Array(3);
	this.fConst50;
	this.fConst51;
	this.fConst52;
	this.fRec32 = new Float32Array(3);
	this.fConst53;
	this.fConst54;
	this.fConst55;
	this.fRec31 = new Float32Array(3);
	this.fConst56;
	this.fConst57;
	this.fConst58;
	this.fConst59;
	this.fRec30 = new Float32Array(3);
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fRec29 = new Float32Array(3);
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fRec28 = new Float32Array(3);
	this.fConst66;
	this.fRec27 = new Float32Array(2);
	this.fVbargraph1;
	this.fConst67;
	this.fConst68;
	this.fConst69;
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
	this.fRec40 = new Float32Array(3);
	this.fConst88;
	this.fConst89;
	this.fConst90;
	this.fRec39 = new Float32Array(3);
	this.fConst91;
	this.fConst92;
	this.fConst93;
	this.fRec38 = new Float32Array(3);
	this.fConst94;
	this.fConst95;
	this.fConst96;
	this.fConst97;
	this.fRec37 = new Float32Array(3);
	this.fConst98;
	this.fConst99;
	this.fConst100;
	this.fRec36 = new Float32Array(3);
	this.fConst101;
	this.fConst102;
	this.fConst103;
	this.fRec35 = new Float32Array(3);
	this.fConst104;
	this.fRec34 = new Float32Array(2);
	this.fVbargraph2;
	this.fConst105;
	this.fConst106;
	this.fConst107;
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
	this.fRec47 = new Float32Array(3);
	this.fConst126;
	this.fConst127;
	this.fConst128;
	this.fRec46 = new Float32Array(3);
	this.fConst129;
	this.fConst130;
	this.fConst131;
	this.fRec45 = new Float32Array(3);
	this.fConst132;
	this.fConst133;
	this.fConst134;
	this.fConst135;
	this.fRec44 = new Float32Array(3);
	this.fConst136;
	this.fConst137;
	this.fConst138;
	this.fRec43 = new Float32Array(3);
	this.fConst139;
	this.fConst140;
	this.fConst141;
	this.fRec42 = new Float32Array(3);
	this.fConst142;
	this.fRec41 = new Float32Array(2);
	this.fVbargraph3;
	this.fConst143;
	this.fConst144;
	this.fConst145;
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
	this.fRec54 = new Float32Array(3);
	this.fConst164;
	this.fConst165;
	this.fConst166;
	this.fRec53 = new Float32Array(3);
	this.fConst167;
	this.fConst168;
	this.fConst169;
	this.fRec52 = new Float32Array(3);
	this.fConst170;
	this.fConst171;
	this.fConst172;
	this.fConst173;
	this.fRec51 = new Float32Array(3);
	this.fConst174;
	this.fConst175;
	this.fConst176;
	this.fRec50 = new Float32Array(3);
	this.fConst177;
	this.fConst178;
	this.fConst179;
	this.fRec49 = new Float32Array(3);
	this.fConst180;
	this.fRec48 = new Float32Array(2);
	this.fVbargraph4;
	this.fConst181;
	this.fConst182;
	this.fConst183;
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
	this.fRec61 = new Float32Array(3);
	this.fConst202;
	this.fConst203;
	this.fConst204;
	this.fRec60 = new Float32Array(3);
	this.fConst205;
	this.fConst206;
	this.fConst207;
	this.fRec59 = new Float32Array(3);
	this.fConst208;
	this.fConst209;
	this.fConst210;
	this.fConst211;
	this.fRec58 = new Float32Array(3);
	this.fConst212;
	this.fConst213;
	this.fConst214;
	this.fRec57 = new Float32Array(3);
	this.fConst215;
	this.fConst216;
	this.fConst217;
	this.fRec56 = new Float32Array(3);
	this.fConst218;
	this.fRec55 = new Float32Array(2);
	this.fVbargraph5;
	this.fConst219;
	this.fConst220;
	this.fConst221;
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
	this.fRec68 = new Float32Array(3);
	this.fConst240;
	this.fConst241;
	this.fConst242;
	this.fRec67 = new Float32Array(3);
	this.fConst243;
	this.fConst244;
	this.fConst245;
	this.fRec66 = new Float32Array(3);
	this.fConst246;
	this.fConst247;
	this.fConst248;
	this.fConst249;
	this.fRec65 = new Float32Array(3);
	this.fConst250;
	this.fConst251;
	this.fConst252;
	this.fRec64 = new Float32Array(3);
	this.fConst253;
	this.fConst254;
	this.fConst255;
	this.fRec63 = new Float32Array(3);
	this.fConst256;
	this.fRec62 = new Float32Array(2);
	this.fVbargraph6;
	this.fConst257;
	this.fConst258;
	this.fConst259;
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
	this.fRec75 = new Float32Array(3);
	this.fConst278;
	this.fConst279;
	this.fConst280;
	this.fRec74 = new Float32Array(3);
	this.fConst281;
	this.fConst282;
	this.fConst283;
	this.fRec73 = new Float32Array(3);
	this.fConst284;
	this.fConst285;
	this.fConst286;
	this.fConst287;
	this.fRec72 = new Float32Array(3);
	this.fConst288;
	this.fConst289;
	this.fConst290;
	this.fRec71 = new Float32Array(3);
	this.fConst291;
	this.fConst292;
	this.fConst293;
	this.fRec70 = new Float32Array(3);
	this.fConst294;
	this.fRec69 = new Float32Array(2);
	this.fVbargraph7;
	this.fConst295;
	this.fConst296;
	this.fConst297;
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
	this.fRec82 = new Float32Array(3);
	this.fConst316;
	this.fConst317;
	this.fConst318;
	this.fRec81 = new Float32Array(3);
	this.fConst319;
	this.fConst320;
	this.fConst321;
	this.fRec80 = new Float32Array(3);
	this.fConst322;
	this.fConst323;
	this.fConst324;
	this.fConst325;
	this.fRec79 = new Float32Array(3);
	this.fConst326;
	this.fConst327;
	this.fConst328;
	this.fRec78 = new Float32Array(3);
	this.fConst329;
	this.fConst330;
	this.fConst331;
	this.fRec77 = new Float32Array(3);
	this.fConst332;
	this.fRec76 = new Float32Array(2);
	this.fVbargraph8;
	this.fConst333;
	this.fConst334;
	this.fConst335;
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
	this.fRec89 = new Float32Array(3);
	this.fConst354;
	this.fConst355;
	this.fConst356;
	this.fRec88 = new Float32Array(3);
	this.fConst357;
	this.fConst358;
	this.fConst359;
	this.fRec87 = new Float32Array(3);
	this.fConst360;
	this.fConst361;
	this.fConst362;
	this.fConst363;
	this.fRec86 = new Float32Array(3);
	this.fConst364;
	this.fConst365;
	this.fConst366;
	this.fRec85 = new Float32Array(3);
	this.fConst367;
	this.fConst368;
	this.fConst369;
	this.fRec84 = new Float32Array(3);
	this.fConst370;
	this.fRec83 = new Float32Array(2);
	this.fVbargraph9;
	this.fConst371;
	this.fConst372;
	this.fConst373;
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
	this.fRec96 = new Float32Array(3);
	this.fConst392;
	this.fConst393;
	this.fConst394;
	this.fRec95 = new Float32Array(3);
	this.fConst395;
	this.fConst396;
	this.fConst397;
	this.fRec94 = new Float32Array(3);
	this.fConst398;
	this.fConst399;
	this.fConst400;
	this.fConst401;
	this.fRec93 = new Float32Array(3);
	this.fConst402;
	this.fConst403;
	this.fConst404;
	this.fRec92 = new Float32Array(3);
	this.fConst405;
	this.fConst406;
	this.fConst407;
	this.fRec91 = new Float32Array(3);
	this.fConst408;
	this.fRec90 = new Float32Array(2);
	this.fVbargraph10;
	this.fConst409;
	this.fConst410;
	this.fConst411;
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
	this.fRec103 = new Float32Array(3);
	this.fConst430;
	this.fConst431;
	this.fConst432;
	this.fRec102 = new Float32Array(3);
	this.fConst433;
	this.fConst434;
	this.fConst435;
	this.fRec101 = new Float32Array(3);
	this.fConst436;
	this.fConst437;
	this.fConst438;
	this.fConst439;
	this.fRec100 = new Float32Array(3);
	this.fConst440;
	this.fConst441;
	this.fConst442;
	this.fRec99 = new Float32Array(3);
	this.fConst443;
	this.fConst444;
	this.fConst445;
	this.fRec98 = new Float32Array(3);
	this.fConst446;
	this.fRec97 = new Float32Array(2);
	this.fVbargraph11;
	this.fConst447;
	this.fConst448;
	this.fConst449;
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
	this.fRec110 = new Float32Array(3);
	this.fConst468;
	this.fConst469;
	this.fConst470;
	this.fRec109 = new Float32Array(3);
	this.fConst471;
	this.fConst472;
	this.fConst473;
	this.fRec108 = new Float32Array(3);
	this.fConst474;
	this.fConst475;
	this.fConst476;
	this.fConst477;
	this.fRec107 = new Float32Array(3);
	this.fConst478;
	this.fConst479;
	this.fConst480;
	this.fRec106 = new Float32Array(3);
	this.fConst481;
	this.fConst482;
	this.fConst483;
	this.fRec105 = new Float32Array(3);
	this.fConst484;
	this.fRec104 = new Float32Array(2);
	this.fVbargraph12;
	this.fConst485;
	this.fConst486;
	this.fConst487;
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
	this.fRec117 = new Float32Array(3);
	this.fConst506;
	this.fConst507;
	this.fConst508;
	this.fRec116 = new Float32Array(3);
	this.fConst509;
	this.fConst510;
	this.fConst511;
	this.fRec115 = new Float32Array(3);
	this.fConst512;
	this.fConst513;
	this.fConst514;
	this.fConst515;
	this.fRec114 = new Float32Array(3);
	this.fConst516;
	this.fConst517;
	this.fConst518;
	this.fRec113 = new Float32Array(3);
	this.fConst519;
	this.fConst520;
	this.fConst521;
	this.fRec112 = new Float32Array(3);
	this.fConst522;
	this.fRec111 = new Float32Array(2);
	this.fVbargraph13;
	this.fConst523;
	this.fConst524;
	this.fConst525;
	this.fConst526;
	this.fConst527;
	this.fConst528;
	this.fConst529;
	this.fConst530;
	this.fConst531;
	this.fRec121 = new Float32Array(3);
	this.fConst532;
	this.fConst533;
	this.fConst534;
	this.fRec120 = new Float32Array(3);
	this.fConst535;
	this.fConst536;
	this.fConst537;
	this.fRec119 = new Float32Array(3);
	this.fConst538;
	this.fRec118 = new Float32Array(2);
	this.fVbargraph14;
	
	this.metadata = function(m) { 
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
		this.fConst19 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst20 = (1 / this.fConst5);
		this.fConst21 = (2 * (4.07678 - this.fConst20));
		this.fConst22 = (this.fConst12 + 0.000407678);
		this.fConst23 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst24 = (2 * (1.45007 - this.fConst20));
		this.fConst25 = (this.fConst9 + 1.45007);
		this.fConst26 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst27 = (2 * (0.93514 - this.fConst20));
		this.fConst28 = (this.fConst6 + 0.93514);
		this.fConst29 = Math.tan((31665.3 / this.fConst0));
		this.fConst30 = (1 / this.fConst29);
		this.fConst31 = (1 / (((this.fConst30 + 0.157482) / this.fConst29) + 0.93514));
		this.fConst32 = mydsp_faustpower2_f(this.fConst29);
		this.fConst33 = (50.0638 / this.fConst32);
		this.fConst34 = (2 * (0.93514 - this.fConst33));
		this.fConst35 = (1 / (((this.fConst30 + 0.74313) / this.fConst29) + 1.45007));
		this.fConst36 = (11.0521 / this.fConst32);
		this.fConst37 = (2 * (1.45007 - this.fConst36));
		this.fConst38 = (1 / (((this.fConst30 + 3.18973) / this.fConst29) + 4.07678));
		this.fConst39 = (0.00176617 / this.fConst32);
		this.fConst40 = (2 * (0.000407678 - this.fConst39));
		this.fConst41 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst42 = (2 * (53.5362 - this.fConst20));
		this.fConst43 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst44 = (2 * (7.62173 - this.fConst20));
		this.fConst45 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst46 = (0.0001 / this.fConst5);
		this.fConst47 = (2 * (0.000433227 - this.fConst46));
		this.fConst48 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst49 = (2 * (0.245292 - this.fConst20));
		this.fConst50 = (this.fConst46 + 0.000433227);
		this.fConst51 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst52 = (2 * (0.689621 - this.fConst20));
		this.fConst53 = (this.fConst20 + 7.62173);
		this.fConst54 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst55 = (2 * (1.06936 - this.fConst20));
		this.fConst56 = (this.fConst20 + 53.5362);
		this.fConst57 = (((this.fConst30 + -3.18973) / this.fConst29) + 4.07678);
		this.fConst58 = (1 / this.fConst32);
		this.fConst59 = (2 * (4.07678 - this.fConst58));
		this.fConst60 = (this.fConst39 + 0.000407678);
		this.fConst61 = (((this.fConst30 + -0.74313) / this.fConst29) + 1.45007);
		this.fConst62 = (2 * (1.45007 - this.fConst58));
		this.fConst63 = (this.fConst36 + 1.45007);
		this.fConst64 = (((this.fConst30 + -0.157482) / this.fConst29) + 0.93514);
		this.fConst65 = (2 * (0.93514 - this.fConst58));
		this.fConst66 = (this.fConst33 + 0.93514);
		this.fConst67 = Math.tan((19947.9 / this.fConst0));
		this.fConst68 = (1 / this.fConst67);
		this.fConst69 = (1 / (((this.fConst68 + 0.157482) / this.fConst67) + 0.93514));
		this.fConst70 = mydsp_faustpower2_f(this.fConst67);
		this.fConst71 = (50.0638 / this.fConst70);
		this.fConst72 = (2 * (0.93514 - this.fConst71));
		this.fConst73 = (1 / (((this.fConst68 + 0.74313) / this.fConst67) + 1.45007));
		this.fConst74 = (11.0521 / this.fConst70);
		this.fConst75 = (2 * (1.45007 - this.fConst74));
		this.fConst76 = (1 / (((this.fConst68 + 3.18973) / this.fConst67) + 4.07678));
		this.fConst77 = (0.00176617 / this.fConst70);
		this.fConst78 = (2 * (0.000407678 - this.fConst77));
		this.fConst79 = (1 / (((this.fConst30 + 0.168405) / this.fConst29) + 1.06936));
		this.fConst80 = (2 * (53.5362 - this.fConst58));
		this.fConst81 = (1 / (((this.fConst30 + 0.512479) / this.fConst29) + 0.689621));
		this.fConst82 = (2 * (7.62173 - this.fConst58));
		this.fConst83 = (1 / (((this.fConst30 + 0.782413) / this.fConst29) + 0.245292));
		this.fConst84 = (0.0001 / this.fConst32);
		this.fConst85 = (2 * (0.000433227 - this.fConst84));
		this.fConst86 = (((this.fConst30 + -0.782413) / this.fConst29) + 0.245292);
		this.fConst87 = (2 * (0.245292 - this.fConst58));
		this.fConst88 = (this.fConst84 + 0.000433227);
		this.fConst89 = (((this.fConst30 + -0.512479) / this.fConst29) + 0.689621);
		this.fConst90 = (2 * (0.689621 - this.fConst58));
		this.fConst91 = (this.fConst58 + 7.62173);
		this.fConst92 = (((this.fConst30 + -0.168405) / this.fConst29) + 1.06936);
		this.fConst93 = (2 * (1.06936 - this.fConst58));
		this.fConst94 = (this.fConst58 + 53.5362);
		this.fConst95 = (((this.fConst68 + -3.18973) / this.fConst67) + 4.07678);
		this.fConst96 = (1 / this.fConst70);
		this.fConst97 = (2 * (4.07678 - this.fConst96));
		this.fConst98 = (this.fConst77 + 0.000407678);
		this.fConst99 = (((this.fConst68 + -0.74313) / this.fConst67) + 1.45007);
		this.fConst100 = (2 * (1.45007 - this.fConst96));
		this.fConst101 = (this.fConst74 + 1.45007);
		this.fConst102 = (((this.fConst68 + -0.157482) / this.fConst67) + 0.93514);
		this.fConst103 = (2 * (0.93514 - this.fConst96));
		this.fConst104 = (this.fConst71 + 0.93514);
		this.fConst105 = Math.tan((12566.4 / this.fConst0));
		this.fConst106 = (1 / this.fConst105);
		this.fConst107 = (1 / (((this.fConst106 + 0.157482) / this.fConst105) + 0.93514));
		this.fConst108 = mydsp_faustpower2_f(this.fConst105);
		this.fConst109 = (50.0638 / this.fConst108);
		this.fConst110 = (2 * (0.93514 - this.fConst109));
		this.fConst111 = (1 / (((this.fConst106 + 0.74313) / this.fConst105) + 1.45007));
		this.fConst112 = (11.0521 / this.fConst108);
		this.fConst113 = (2 * (1.45007 - this.fConst112));
		this.fConst114 = (1 / (((this.fConst106 + 3.18973) / this.fConst105) + 4.07678));
		this.fConst115 = (0.00176617 / this.fConst108);
		this.fConst116 = (2 * (0.000407678 - this.fConst115));
		this.fConst117 = (1 / (((this.fConst68 + 0.168405) / this.fConst67) + 1.06936));
		this.fConst118 = (2 * (53.5362 - this.fConst96));
		this.fConst119 = (1 / (((this.fConst68 + 0.512479) / this.fConst67) + 0.689621));
		this.fConst120 = (2 * (7.62173 - this.fConst96));
		this.fConst121 = (1 / (((this.fConst68 + 0.782413) / this.fConst67) + 0.245292));
		this.fConst122 = (0.0001 / this.fConst70);
		this.fConst123 = (2 * (0.000433227 - this.fConst122));
		this.fConst124 = (((this.fConst68 + -0.782413) / this.fConst67) + 0.245292);
		this.fConst125 = (2 * (0.245292 - this.fConst96));
		this.fConst126 = (this.fConst122 + 0.000433227);
		this.fConst127 = (((this.fConst68 + -0.512479) / this.fConst67) + 0.689621);
		this.fConst128 = (2 * (0.689621 - this.fConst96));
		this.fConst129 = (this.fConst96 + 7.62173);
		this.fConst130 = (((this.fConst68 + -0.168405) / this.fConst67) + 1.06936);
		this.fConst131 = (2 * (1.06936 - this.fConst96));
		this.fConst132 = (this.fConst96 + 53.5362);
		this.fConst133 = (((this.fConst106 + -3.18973) / this.fConst105) + 4.07678);
		this.fConst134 = (1 / this.fConst108);
		this.fConst135 = (2 * (4.07678 - this.fConst134));
		this.fConst136 = (this.fConst115 + 0.000407678);
		this.fConst137 = (((this.fConst106 + -0.74313) / this.fConst105) + 1.45007);
		this.fConst138 = (2 * (1.45007 - this.fConst134));
		this.fConst139 = (this.fConst112 + 1.45007);
		this.fConst140 = (((this.fConst106 + -0.157482) / this.fConst105) + 0.93514);
		this.fConst141 = (2 * (0.93514 - this.fConst134));
		this.fConst142 = (this.fConst109 + 0.93514);
		this.fConst143 = Math.tan((7916.32 / this.fConst0));
		this.fConst144 = (1 / this.fConst143);
		this.fConst145 = (1 / (((this.fConst144 + 0.157482) / this.fConst143) + 0.93514));
		this.fConst146 = mydsp_faustpower2_f(this.fConst143);
		this.fConst147 = (50.0638 / this.fConst146);
		this.fConst148 = (2 * (0.93514 - this.fConst147));
		this.fConst149 = (1 / (((this.fConst144 + 0.74313) / this.fConst143) + 1.45007));
		this.fConst150 = (11.0521 / this.fConst146);
		this.fConst151 = (2 * (1.45007 - this.fConst150));
		this.fConst152 = (1 / (((this.fConst144 + 3.18973) / this.fConst143) + 4.07678));
		this.fConst153 = (0.00176617 / this.fConst146);
		this.fConst154 = (2 * (0.000407678 - this.fConst153));
		this.fConst155 = (1 / (((this.fConst106 + 0.168405) / this.fConst105) + 1.06936));
		this.fConst156 = (2 * (53.5362 - this.fConst134));
		this.fConst157 = (1 / (((this.fConst106 + 0.512479) / this.fConst105) + 0.689621));
		this.fConst158 = (2 * (7.62173 - this.fConst134));
		this.fConst159 = (1 / (((this.fConst106 + 0.782413) / this.fConst105) + 0.245292));
		this.fConst160 = (0.0001 / this.fConst108);
		this.fConst161 = (2 * (0.000433227 - this.fConst160));
		this.fConst162 = (((this.fConst106 + -0.782413) / this.fConst105) + 0.245292);
		this.fConst163 = (2 * (0.245292 - this.fConst134));
		this.fConst164 = (this.fConst160 + 0.000433227);
		this.fConst165 = (((this.fConst106 + -0.512479) / this.fConst105) + 0.689621);
		this.fConst166 = (2 * (0.689621 - this.fConst134));
		this.fConst167 = (this.fConst134 + 7.62173);
		this.fConst168 = (((this.fConst106 + -0.168405) / this.fConst105) + 1.06936);
		this.fConst169 = (2 * (1.06936 - this.fConst134));
		this.fConst170 = (this.fConst134 + 53.5362);
		this.fConst171 = (((this.fConst144 + -3.18973) / this.fConst143) + 4.07678);
		this.fConst172 = (1 / this.fConst146);
		this.fConst173 = (2 * (4.07678 - this.fConst172));
		this.fConst174 = (this.fConst153 + 0.000407678);
		this.fConst175 = (((this.fConst144 + -0.74313) / this.fConst143) + 1.45007);
		this.fConst176 = (2 * (1.45007 - this.fConst172));
		this.fConst177 = (this.fConst150 + 1.45007);
		this.fConst178 = (((this.fConst144 + -0.157482) / this.fConst143) + 0.93514);
		this.fConst179 = (2 * (0.93514 - this.fConst172));
		this.fConst180 = (this.fConst147 + 0.93514);
		this.fConst181 = Math.tan((4986.97 / this.fConst0));
		this.fConst182 = (1 / this.fConst181);
		this.fConst183 = (1 / (((this.fConst182 + 0.157482) / this.fConst181) + 0.93514));
		this.fConst184 = mydsp_faustpower2_f(this.fConst181);
		this.fConst185 = (50.0638 / this.fConst184);
		this.fConst186 = (2 * (0.93514 - this.fConst185));
		this.fConst187 = (1 / (((this.fConst182 + 0.74313) / this.fConst181) + 1.45007));
		this.fConst188 = (11.0521 / this.fConst184);
		this.fConst189 = (2 * (1.45007 - this.fConst188));
		this.fConst190 = (1 / (((this.fConst182 + 3.18973) / this.fConst181) + 4.07678));
		this.fConst191 = (0.00176617 / this.fConst184);
		this.fConst192 = (2 * (0.000407678 - this.fConst191));
		this.fConst193 = (1 / (((this.fConst144 + 0.168405) / this.fConst143) + 1.06936));
		this.fConst194 = (2 * (53.5362 - this.fConst172));
		this.fConst195 = (1 / (((this.fConst144 + 0.512479) / this.fConst143) + 0.689621));
		this.fConst196 = (2 * (7.62173 - this.fConst172));
		this.fConst197 = (1 / (((this.fConst144 + 0.782413) / this.fConst143) + 0.245292));
		this.fConst198 = (0.0001 / this.fConst146);
		this.fConst199 = (2 * (0.000433227 - this.fConst198));
		this.fConst200 = (((this.fConst144 + -0.782413) / this.fConst143) + 0.245292);
		this.fConst201 = (2 * (0.245292 - this.fConst172));
		this.fConst202 = (this.fConst198 + 0.000433227);
		this.fConst203 = (((this.fConst144 + -0.512479) / this.fConst143) + 0.689621);
		this.fConst204 = (2 * (0.689621 - this.fConst172));
		this.fConst205 = (this.fConst172 + 7.62173);
		this.fConst206 = (((this.fConst144 + -0.168405) / this.fConst143) + 1.06936);
		this.fConst207 = (2 * (1.06936 - this.fConst172));
		this.fConst208 = (this.fConst172 + 53.5362);
		this.fConst209 = (((this.fConst182 + -3.18973) / this.fConst181) + 4.07678);
		this.fConst210 = (1 / this.fConst184);
		this.fConst211 = (2 * (4.07678 - this.fConst210));
		this.fConst212 = (this.fConst191 + 0.000407678);
		this.fConst213 = (((this.fConst182 + -0.74313) / this.fConst181) + 1.45007);
		this.fConst214 = (2 * (1.45007 - this.fConst210));
		this.fConst215 = (this.fConst188 + 1.45007);
		this.fConst216 = (((this.fConst182 + -0.157482) / this.fConst181) + 0.93514);
		this.fConst217 = (2 * (0.93514 - this.fConst210));
		this.fConst218 = (this.fConst185 + 0.93514);
		this.fConst219 = Math.tan((3141.59 / this.fConst0));
		this.fConst220 = (1 / this.fConst219);
		this.fConst221 = (1 / (((this.fConst220 + 0.157482) / this.fConst219) + 0.93514));
		this.fConst222 = mydsp_faustpower2_f(this.fConst219);
		this.fConst223 = (50.0638 / this.fConst222);
		this.fConst224 = (2 * (0.93514 - this.fConst223));
		this.fConst225 = (1 / (((this.fConst220 + 0.74313) / this.fConst219) + 1.45007));
		this.fConst226 = (11.0521 / this.fConst222);
		this.fConst227 = (2 * (1.45007 - this.fConst226));
		this.fConst228 = (1 / (((this.fConst220 + 3.18973) / this.fConst219) + 4.07678));
		this.fConst229 = (0.00176617 / this.fConst222);
		this.fConst230 = (2 * (0.000407678 - this.fConst229));
		this.fConst231 = (1 / (((this.fConst182 + 0.168405) / this.fConst181) + 1.06936));
		this.fConst232 = (2 * (53.5362 - this.fConst210));
		this.fConst233 = (1 / (((this.fConst182 + 0.512479) / this.fConst181) + 0.689621));
		this.fConst234 = (2 * (7.62173 - this.fConst210));
		this.fConst235 = (1 / (((this.fConst182 + 0.782413) / this.fConst181) + 0.245292));
		this.fConst236 = (0.0001 / this.fConst184);
		this.fConst237 = (2 * (0.000433227 - this.fConst236));
		this.fConst238 = (((this.fConst182 + -0.782413) / this.fConst181) + 0.245292);
		this.fConst239 = (2 * (0.245292 - this.fConst210));
		this.fConst240 = (this.fConst236 + 0.000433227);
		this.fConst241 = (((this.fConst182 + -0.512479) / this.fConst181) + 0.689621);
		this.fConst242 = (2 * (0.689621 - this.fConst210));
		this.fConst243 = (this.fConst210 + 7.62173);
		this.fConst244 = (((this.fConst182 + -0.168405) / this.fConst181) + 1.06936);
		this.fConst245 = (2 * (1.06936 - this.fConst210));
		this.fConst246 = (this.fConst210 + 53.5362);
		this.fConst247 = (((this.fConst220 + -3.18973) / this.fConst219) + 4.07678);
		this.fConst248 = (1 / this.fConst222);
		this.fConst249 = (2 * (4.07678 - this.fConst248));
		this.fConst250 = (this.fConst229 + 0.000407678);
		this.fConst251 = (((this.fConst220 + -0.74313) / this.fConst219) + 1.45007);
		this.fConst252 = (2 * (1.45007 - this.fConst248));
		this.fConst253 = (this.fConst226 + 1.45007);
		this.fConst254 = (((this.fConst220 + -0.157482) / this.fConst219) + 0.93514);
		this.fConst255 = (2 * (0.93514 - this.fConst248));
		this.fConst256 = (this.fConst223 + 0.93514);
		this.fConst257 = Math.tan((1979.08 / this.fConst0));
		this.fConst258 = (1 / this.fConst257);
		this.fConst259 = (1 / (((this.fConst258 + 0.157482) / this.fConst257) + 0.93514));
		this.fConst260 = mydsp_faustpower2_f(this.fConst257);
		this.fConst261 = (50.0638 / this.fConst260);
		this.fConst262 = (2 * (0.93514 - this.fConst261));
		this.fConst263 = (1 / (((this.fConst258 + 0.74313) / this.fConst257) + 1.45007));
		this.fConst264 = (11.0521 / this.fConst260);
		this.fConst265 = (2 * (1.45007 - this.fConst264));
		this.fConst266 = (1 / (((this.fConst258 + 3.18973) / this.fConst257) + 4.07678));
		this.fConst267 = (0.00176617 / this.fConst260);
		this.fConst268 = (2 * (0.000407678 - this.fConst267));
		this.fConst269 = (1 / (((this.fConst220 + 0.168405) / this.fConst219) + 1.06936));
		this.fConst270 = (2 * (53.5362 - this.fConst248));
		this.fConst271 = (1 / (((this.fConst220 + 0.512479) / this.fConst219) + 0.689621));
		this.fConst272 = (2 * (7.62173 - this.fConst248));
		this.fConst273 = (1 / (((this.fConst220 + 0.782413) / this.fConst219) + 0.245292));
		this.fConst274 = (0.0001 / this.fConst222);
		this.fConst275 = (2 * (0.000433227 - this.fConst274));
		this.fConst276 = (((this.fConst220 + -0.782413) / this.fConst219) + 0.245292);
		this.fConst277 = (2 * (0.245292 - this.fConst248));
		this.fConst278 = (this.fConst274 + 0.000433227);
		this.fConst279 = (((this.fConst220 + -0.512479) / this.fConst219) + 0.689621);
		this.fConst280 = (2 * (0.689621 - this.fConst248));
		this.fConst281 = (this.fConst248 + 7.62173);
		this.fConst282 = (((this.fConst220 + -0.168405) / this.fConst219) + 1.06936);
		this.fConst283 = (2 * (1.06936 - this.fConst248));
		this.fConst284 = (this.fConst248 + 53.5362);
		this.fConst285 = (((this.fConst258 + -3.18973) / this.fConst257) + 4.07678);
		this.fConst286 = (1 / this.fConst260);
		this.fConst287 = (2 * (4.07678 - this.fConst286));
		this.fConst288 = (this.fConst267 + 0.000407678);
		this.fConst289 = (((this.fConst258 + -0.74313) / this.fConst257) + 1.45007);
		this.fConst290 = (2 * (1.45007 - this.fConst286));
		this.fConst291 = (this.fConst264 + 1.45007);
		this.fConst292 = (((this.fConst258 + -0.157482) / this.fConst257) + 0.93514);
		this.fConst293 = (2 * (0.93514 - this.fConst286));
		this.fConst294 = (this.fConst261 + 0.93514);
		this.fConst295 = Math.tan((1246.74 / this.fConst0));
		this.fConst296 = (1 / this.fConst295);
		this.fConst297 = (1 / (((this.fConst296 + 0.157482) / this.fConst295) + 0.93514));
		this.fConst298 = mydsp_faustpower2_f(this.fConst295);
		this.fConst299 = (50.0638 / this.fConst298);
		this.fConst300 = (2 * (0.93514 - this.fConst299));
		this.fConst301 = (1 / (((this.fConst296 + 0.74313) / this.fConst295) + 1.45007));
		this.fConst302 = (11.0521 / this.fConst298);
		this.fConst303 = (2 * (1.45007 - this.fConst302));
		this.fConst304 = (1 / (((this.fConst296 + 3.18973) / this.fConst295) + 4.07678));
		this.fConst305 = (0.00176617 / this.fConst298);
		this.fConst306 = (2 * (0.000407678 - this.fConst305));
		this.fConst307 = (1 / (((this.fConst258 + 0.168405) / this.fConst257) + 1.06936));
		this.fConst308 = (2 * (53.5362 - this.fConst286));
		this.fConst309 = (1 / (((this.fConst258 + 0.512479) / this.fConst257) + 0.689621));
		this.fConst310 = (2 * (7.62173 - this.fConst286));
		this.fConst311 = (1 / (((this.fConst258 + 0.782413) / this.fConst257) + 0.245292));
		this.fConst312 = (0.0001 / this.fConst260);
		this.fConst313 = (2 * (0.000433227 - this.fConst312));
		this.fConst314 = (((this.fConst258 + -0.782413) / this.fConst257) + 0.245292);
		this.fConst315 = (2 * (0.245292 - this.fConst286));
		this.fConst316 = (this.fConst312 + 0.000433227);
		this.fConst317 = (((this.fConst258 + -0.512479) / this.fConst257) + 0.689621);
		this.fConst318 = (2 * (0.689621 - this.fConst286));
		this.fConst319 = (this.fConst286 + 7.62173);
		this.fConst320 = (((this.fConst258 + -0.168405) / this.fConst257) + 1.06936);
		this.fConst321 = (2 * (1.06936 - this.fConst286));
		this.fConst322 = (this.fConst286 + 53.5362);
		this.fConst323 = (((this.fConst296 + -3.18973) / this.fConst295) + 4.07678);
		this.fConst324 = (1 / this.fConst298);
		this.fConst325 = (2 * (4.07678 - this.fConst324));
		this.fConst326 = (this.fConst305 + 0.000407678);
		this.fConst327 = (((this.fConst296 + -0.74313) / this.fConst295) + 1.45007);
		this.fConst328 = (2 * (1.45007 - this.fConst324));
		this.fConst329 = (this.fConst302 + 1.45007);
		this.fConst330 = (((this.fConst296 + -0.157482) / this.fConst295) + 0.93514);
		this.fConst331 = (2 * (0.93514 - this.fConst324));
		this.fConst332 = (this.fConst299 + 0.93514);
		this.fConst333 = Math.tan((785.398 / this.fConst0));
		this.fConst334 = (1 / this.fConst333);
		this.fConst335 = (1 / (((this.fConst334 + 0.157482) / this.fConst333) + 0.93514));
		this.fConst336 = mydsp_faustpower2_f(this.fConst333);
		this.fConst337 = (50.0638 / this.fConst336);
		this.fConst338 = (2 * (0.93514 - this.fConst337));
		this.fConst339 = (1 / (((this.fConst334 + 0.74313) / this.fConst333) + 1.45007));
		this.fConst340 = (11.0521 / this.fConst336);
		this.fConst341 = (2 * (1.45007 - this.fConst340));
		this.fConst342 = (1 / (((this.fConst334 + 3.18973) / this.fConst333) + 4.07678));
		this.fConst343 = (0.00176617 / this.fConst336);
		this.fConst344 = (2 * (0.000407678 - this.fConst343));
		this.fConst345 = (1 / (((this.fConst296 + 0.168405) / this.fConst295) + 1.06936));
		this.fConst346 = (2 * (53.5362 - this.fConst324));
		this.fConst347 = (1 / (((this.fConst296 + 0.512479) / this.fConst295) + 0.689621));
		this.fConst348 = (2 * (7.62173 - this.fConst324));
		this.fConst349 = (1 / (((this.fConst296 + 0.782413) / this.fConst295) + 0.245292));
		this.fConst350 = (0.0001 / this.fConst298);
		this.fConst351 = (2 * (0.000433227 - this.fConst350));
		this.fConst352 = (((this.fConst296 + -0.782413) / this.fConst295) + 0.245292);
		this.fConst353 = (2 * (0.245292 - this.fConst324));
		this.fConst354 = (this.fConst350 + 0.000433227);
		this.fConst355 = (((this.fConst296 + -0.512479) / this.fConst295) + 0.689621);
		this.fConst356 = (2 * (0.689621 - this.fConst324));
		this.fConst357 = (this.fConst324 + 7.62173);
		this.fConst358 = (((this.fConst296 + -0.168405) / this.fConst295) + 1.06936);
		this.fConst359 = (2 * (1.06936 - this.fConst324));
		this.fConst360 = (this.fConst324 + 53.5362);
		this.fConst361 = (((this.fConst334 + -3.18973) / this.fConst333) + 4.07678);
		this.fConst362 = (1 / this.fConst336);
		this.fConst363 = (2 * (4.07678 - this.fConst362));
		this.fConst364 = (this.fConst343 + 0.000407678);
		this.fConst365 = (((this.fConst334 + -0.74313) / this.fConst333) + 1.45007);
		this.fConst366 = (2 * (1.45007 - this.fConst362));
		this.fConst367 = (this.fConst340 + 1.45007);
		this.fConst368 = (((this.fConst334 + -0.157482) / this.fConst333) + 0.93514);
		this.fConst369 = (2 * (0.93514 - this.fConst362));
		this.fConst370 = (this.fConst337 + 0.93514);
		this.fConst371 = Math.tan((494.77 / this.fConst0));
		this.fConst372 = (1 / this.fConst371);
		this.fConst373 = (1 / (((this.fConst372 + 0.157482) / this.fConst371) + 0.93514));
		this.fConst374 = mydsp_faustpower2_f(this.fConst371);
		this.fConst375 = (50.0638 / this.fConst374);
		this.fConst376 = (2 * (0.93514 - this.fConst375));
		this.fConst377 = (1 / (((this.fConst372 + 0.74313) / this.fConst371) + 1.45007));
		this.fConst378 = (11.0521 / this.fConst374);
		this.fConst379 = (2 * (1.45007 - this.fConst378));
		this.fConst380 = (1 / (((this.fConst372 + 3.18973) / this.fConst371) + 4.07678));
		this.fConst381 = (0.00176617 / this.fConst374);
		this.fConst382 = (2 * (0.000407678 - this.fConst381));
		this.fConst383 = (1 / (((this.fConst334 + 0.168405) / this.fConst333) + 1.06936));
		this.fConst384 = (2 * (53.5362 - this.fConst362));
		this.fConst385 = (1 / (((this.fConst334 + 0.512479) / this.fConst333) + 0.689621));
		this.fConst386 = (2 * (7.62173 - this.fConst362));
		this.fConst387 = (1 / (((this.fConst334 + 0.782413) / this.fConst333) + 0.245292));
		this.fConst388 = (0.0001 / this.fConst336);
		this.fConst389 = (2 * (0.000433227 - this.fConst388));
		this.fConst390 = (((this.fConst334 + -0.782413) / this.fConst333) + 0.245292);
		this.fConst391 = (2 * (0.245292 - this.fConst362));
		this.fConst392 = (this.fConst388 + 0.000433227);
		this.fConst393 = (((this.fConst334 + -0.512479) / this.fConst333) + 0.689621);
		this.fConst394 = (2 * (0.689621 - this.fConst362));
		this.fConst395 = (this.fConst362 + 7.62173);
		this.fConst396 = (((this.fConst334 + -0.168405) / this.fConst333) + 1.06936);
		this.fConst397 = (2 * (1.06936 - this.fConst362));
		this.fConst398 = (this.fConst362 + 53.5362);
		this.fConst399 = (((this.fConst372 + -3.18973) / this.fConst371) + 4.07678);
		this.fConst400 = (1 / this.fConst374);
		this.fConst401 = (2 * (4.07678 - this.fConst400));
		this.fConst402 = (this.fConst381 + 0.000407678);
		this.fConst403 = (((this.fConst372 + -0.74313) / this.fConst371) + 1.45007);
		this.fConst404 = (2 * (1.45007 - this.fConst400));
		this.fConst405 = (this.fConst378 + 1.45007);
		this.fConst406 = (((this.fConst372 + -0.157482) / this.fConst371) + 0.93514);
		this.fConst407 = (2 * (0.93514 - this.fConst400));
		this.fConst408 = (this.fConst375 + 0.93514);
		this.fConst409 = Math.tan((311.685 / this.fConst0));
		this.fConst410 = (1 / this.fConst409);
		this.fConst411 = (1 / (((this.fConst410 + 0.157482) / this.fConst409) + 0.93514));
		this.fConst412 = mydsp_faustpower2_f(this.fConst409);
		this.fConst413 = (50.0638 / this.fConst412);
		this.fConst414 = (2 * (0.93514 - this.fConst413));
		this.fConst415 = (1 / (((this.fConst410 + 0.74313) / this.fConst409) + 1.45007));
		this.fConst416 = (11.0521 / this.fConst412);
		this.fConst417 = (2 * (1.45007 - this.fConst416));
		this.fConst418 = (1 / (((this.fConst410 + 3.18973) / this.fConst409) + 4.07678));
		this.fConst419 = (0.00176617 / this.fConst412);
		this.fConst420 = (2 * (0.000407678 - this.fConst419));
		this.fConst421 = (1 / (((this.fConst372 + 0.168405) / this.fConst371) + 1.06936));
		this.fConst422 = (2 * (53.5362 - this.fConst400));
		this.fConst423 = (1 / (((this.fConst372 + 0.512479) / this.fConst371) + 0.689621));
		this.fConst424 = (2 * (7.62173 - this.fConst400));
		this.fConst425 = (1 / (((this.fConst372 + 0.782413) / this.fConst371) + 0.245292));
		this.fConst426 = (0.0001 / this.fConst374);
		this.fConst427 = (2 * (0.000433227 - this.fConst426));
		this.fConst428 = (((this.fConst372 + -0.782413) / this.fConst371) + 0.245292);
		this.fConst429 = (2 * (0.245292 - this.fConst400));
		this.fConst430 = (this.fConst426 + 0.000433227);
		this.fConst431 = (((this.fConst372 + -0.512479) / this.fConst371) + 0.689621);
		this.fConst432 = (2 * (0.689621 - this.fConst400));
		this.fConst433 = (this.fConst400 + 7.62173);
		this.fConst434 = (((this.fConst372 + -0.168405) / this.fConst371) + 1.06936);
		this.fConst435 = (2 * (1.06936 - this.fConst400));
		this.fConst436 = (this.fConst400 + 53.5362);
		this.fConst437 = (((this.fConst410 + -3.18973) / this.fConst409) + 4.07678);
		this.fConst438 = (1 / this.fConst412);
		this.fConst439 = (2 * (4.07678 - this.fConst438));
		this.fConst440 = (this.fConst419 + 0.000407678);
		this.fConst441 = (((this.fConst410 + -0.74313) / this.fConst409) + 1.45007);
		this.fConst442 = (2 * (1.45007 - this.fConst438));
		this.fConst443 = (this.fConst416 + 1.45007);
		this.fConst444 = (((this.fConst410 + -0.157482) / this.fConst409) + 0.93514);
		this.fConst445 = (2 * (0.93514 - this.fConst438));
		this.fConst446 = (this.fConst413 + 0.93514);
		this.fConst447 = Math.tan((196.35 / this.fConst0));
		this.fConst448 = (1 / this.fConst447);
		this.fConst449 = (1 / (((this.fConst448 + 0.157482) / this.fConst447) + 0.93514));
		this.fConst450 = mydsp_faustpower2_f(this.fConst447);
		this.fConst451 = (50.0638 / this.fConst450);
		this.fConst452 = (2 * (0.93514 - this.fConst451));
		this.fConst453 = (1 / (((this.fConst448 + 0.74313) / this.fConst447) + 1.45007));
		this.fConst454 = (11.0521 / this.fConst450);
		this.fConst455 = (2 * (1.45007 - this.fConst454));
		this.fConst456 = (1 / (((this.fConst448 + 3.18973) / this.fConst447) + 4.07678));
		this.fConst457 = (0.00176617 / this.fConst450);
		this.fConst458 = (2 * (0.000407678 - this.fConst457));
		this.fConst459 = (1 / (((this.fConst410 + 0.168405) / this.fConst409) + 1.06936));
		this.fConst460 = (2 * (53.5362 - this.fConst438));
		this.fConst461 = (1 / (((this.fConst410 + 0.512479) / this.fConst409) + 0.689621));
		this.fConst462 = (2 * (7.62173 - this.fConst438));
		this.fConst463 = (1 / (((this.fConst410 + 0.782413) / this.fConst409) + 0.245292));
		this.fConst464 = (0.0001 / this.fConst412);
		this.fConst465 = (2 * (0.000433227 - this.fConst464));
		this.fConst466 = (((this.fConst410 + -0.782413) / this.fConst409) + 0.245292);
		this.fConst467 = (2 * (0.245292 - this.fConst438));
		this.fConst468 = (this.fConst464 + 0.000433227);
		this.fConst469 = (((this.fConst410 + -0.512479) / this.fConst409) + 0.689621);
		this.fConst470 = (2 * (0.689621 - this.fConst438));
		this.fConst471 = (this.fConst438 + 7.62173);
		this.fConst472 = (((this.fConst410 + -0.168405) / this.fConst409) + 1.06936);
		this.fConst473 = (2 * (1.06936 - this.fConst438));
		this.fConst474 = (this.fConst438 + 53.5362);
		this.fConst475 = (((this.fConst448 + -3.18973) / this.fConst447) + 4.07678);
		this.fConst476 = (1 / this.fConst450);
		this.fConst477 = (2 * (4.07678 - this.fConst476));
		this.fConst478 = (this.fConst457 + 0.000407678);
		this.fConst479 = (((this.fConst448 + -0.74313) / this.fConst447) + 1.45007);
		this.fConst480 = (2 * (1.45007 - this.fConst476));
		this.fConst481 = (this.fConst454 + 1.45007);
		this.fConst482 = (((this.fConst448 + -0.157482) / this.fConst447) + 0.93514);
		this.fConst483 = (2 * (0.93514 - this.fConst476));
		this.fConst484 = (this.fConst451 + 0.93514);
		this.fConst485 = Math.tan((123.692 / this.fConst0));
		this.fConst486 = (1 / this.fConst485);
		this.fConst487 = (1 / (((this.fConst486 + 0.157482) / this.fConst485) + 0.93514));
		this.fConst488 = mydsp_faustpower2_f(this.fConst485);
		this.fConst489 = (50.0638 / this.fConst488);
		this.fConst490 = (2 * (0.93514 - this.fConst489));
		this.fConst491 = (1 / (((this.fConst486 + 0.74313) / this.fConst485) + 1.45007));
		this.fConst492 = (11.0521 / this.fConst488);
		this.fConst493 = (2 * (1.45007 - this.fConst492));
		this.fConst494 = (1 / (((this.fConst486 + 3.18973) / this.fConst485) + 4.07678));
		this.fConst495 = (0.00176617 / this.fConst488);
		this.fConst496 = (2 * (0.000407678 - this.fConst495));
		this.fConst497 = (1 / (((this.fConst448 + 0.168405) / this.fConst447) + 1.06936));
		this.fConst498 = (2 * (53.5362 - this.fConst476));
		this.fConst499 = (1 / (((this.fConst448 + 0.512479) / this.fConst447) + 0.689621));
		this.fConst500 = (2 * (7.62173 - this.fConst476));
		this.fConst501 = (1 / (((this.fConst448 + 0.782413) / this.fConst447) + 0.245292));
		this.fConst502 = (0.0001 / this.fConst450);
		this.fConst503 = (2 * (0.000433227 - this.fConst502));
		this.fConst504 = (((this.fConst448 + -0.782413) / this.fConst447) + 0.245292);
		this.fConst505 = (2 * (0.245292 - this.fConst476));
		this.fConst506 = (this.fConst502 + 0.000433227);
		this.fConst507 = (((this.fConst448 + -0.512479) / this.fConst447) + 0.689621);
		this.fConst508 = (2 * (0.689621 - this.fConst476));
		this.fConst509 = (this.fConst476 + 7.62173);
		this.fConst510 = (((this.fConst448 + -0.168405) / this.fConst447) + 1.06936);
		this.fConst511 = (2 * (1.06936 - this.fConst476));
		this.fConst512 = (this.fConst476 + 53.5362);
		this.fConst513 = (((this.fConst486 + -3.18973) / this.fConst485) + 4.07678);
		this.fConst514 = (1 / this.fConst488);
		this.fConst515 = (2 * (4.07678 - this.fConst514));
		this.fConst516 = (this.fConst495 + 0.000407678);
		this.fConst517 = (((this.fConst486 + -0.74313) / this.fConst485) + 1.45007);
		this.fConst518 = (2 * (1.45007 - this.fConst514));
		this.fConst519 = (this.fConst492 + 1.45007);
		this.fConst520 = (((this.fConst486 + -0.157482) / this.fConst485) + 0.93514);
		this.fConst521 = (2 * (0.93514 - this.fConst514));
		this.fConst522 = (this.fConst489 + 0.93514);
		this.fConst523 = (1 / (((this.fConst486 + 0.168405) / this.fConst485) + 1.06936));
		this.fConst524 = (2 * (53.5362 - this.fConst514));
		this.fConst525 = (1 / (((this.fConst486 + 0.512479) / this.fConst485) + 0.689621));
		this.fConst526 = (2 * (7.62173 - this.fConst514));
		this.fConst527 = (1 / (((this.fConst486 + 0.782413) / this.fConst485) + 0.245292));
		this.fConst528 = (0.0001 / this.fConst488);
		this.fConst529 = (2 * (0.000433227 - this.fConst528));
		this.fConst530 = (((this.fConst486 + -0.782413) / this.fConst485) + 0.245292);
		this.fConst531 = (2 * (0.245292 - this.fConst514));
		this.fConst532 = (this.fConst528 + 0.000433227);
		this.fConst533 = (((this.fConst486 + -0.512479) / this.fConst485) + 0.689621);
		this.fConst534 = (2 * (0.689621 - this.fConst514));
		this.fConst535 = (this.fConst514 + 7.62173);
		this.fConst536 = (((this.fConst486 + -0.168405) / this.fConst485) + 1.06936);
		this.fConst537 = (2 * (1.06936 - this.fConst514));
		this.fConst538 = (this.fConst514 + 53.5362);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		this.fCheckbox0 = 0;
		this.fHslider2 = 0;
		this.fCheckbox1 = 0;
		this.fHslider3 = 0;
		this.fHslider4 = 0.5;
		this.fCheckbox2 = 0;
		this.fCheckbox3 = 0;
		this.fVslider0 = -20;
		this.fEntry0 = 2;
		this.fVslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fCheckbox4 = 0;
		this.fCheckbox5 = 0;
		this.fHslider5 = 1;
		this.fHslider6 = 0;
		this.fHslider7 = 1;
		this.fHslider8 = 10;
		this.fCheckbox6 = 0;
		this.fHslider9 = 1;
		this.fCheckbox7 = 0;
		this.fHslider10 = 1000;
		this.fHslider11 = 0;
		this.fHslider12 = 1.5;
		this.fHslider13 = 100;
		this.fHslider14 = 800;
		this.fHslider15 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec4[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec5[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec6[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec8[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec1[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fRec7[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec2[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fVec3[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec4[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fVec5[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec6[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec7[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fVec8[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec9[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fVec9[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fVec10[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fVec11[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fVec12[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fVec13[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fVec14[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fVec15[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec10[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fVec16[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fVec17[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec18[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fVec19[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fVec20[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fVec21[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.iRec11[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 4); l30 = (l30 + 1)) {
			this.fRec12[l30] = 0;
			
		}
		this.IOTA = 0;
		for (var l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			this.fVec22[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec13[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec19[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec20[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			this.fRec18[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			this.fRec17[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			this.fRec16[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			this.fRec15[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec14[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 4096); l40 = (l40 + 1)) {
			this.fVec23[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec21[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			this.fRec26[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec25[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec24[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			this.fRec23[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec22[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec3[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec2[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec1[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fRec0[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec33[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec32[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec31[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec30[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec29[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec28[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec27[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			this.fRec40[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec39[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec38[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec37[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec36[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec35[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			this.fRec34[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			this.fRec47[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			this.fRec46[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec45[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec44[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			this.fRec43[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			this.fRec42[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			this.fRec41[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec54[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			this.fRec53[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec52[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec51[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec50[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			this.fRec49[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			this.fRec48[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec61[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec60[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			this.fRec59[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec58[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec57[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec56[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			this.fRec55[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec68[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			this.fRec67[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec66[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec65[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec64[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			this.fRec63[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			this.fRec62[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec75[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec74[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec73[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec72[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			this.fRec71[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			this.fRec70[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			this.fRec69[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec82[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			this.fRec81[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec80[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec79[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			this.fRec78[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			this.fRec77[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			this.fRec76[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec89[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			this.fRec88[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			this.fRec87[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			this.fRec86[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			this.fRec85[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			this.fRec84[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			this.fRec83[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			this.fRec96[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			this.fRec95[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec94[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			this.fRec93[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			this.fRec92[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			this.fRec91[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			this.fRec90[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			this.fRec103[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			this.fRec102[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec101[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec100[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			this.fRec99[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			this.fRec98[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			this.fRec97[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			this.fRec110[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			this.fRec109[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			this.fRec108[l130] = 0;
			
		}
		for (var l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			this.fRec107[l131] = 0;
			
		}
		for (var l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			this.fRec106[l132] = 0;
			
		}
		for (var l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			this.fRec105[l133] = 0;
			
		}
		for (var l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			this.fRec104[l134] = 0;
			
		}
		for (var l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			this.fRec117[l135] = 0;
			
		}
		for (var l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			this.fRec116[l136] = 0;
			
		}
		for (var l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			this.fRec115[l137] = 0;
			
		}
		for (var l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			this.fRec114[l138] = 0;
			
		}
		for (var l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			this.fRec113[l139] = 0;
			
		}
		for (var l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			this.fRec112[l140] = 0;
			
		}
		for (var l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			this.fRec111[l141] = 0;
			
		}
		for (var l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			this.fRec121[l142] = 0;
			
		}
		for (var l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			this.fRec120[l143] = 0;
			
		}
		for (var l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			this.fRec119[l144] = 0;
			
		}
		for (var l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			this.fRec118[l145] = 0;
			
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
		ui_interface.declare("fCheckbox3", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", function handler(obj) { function setval(val) { obj.fCheckbox3 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox4", "1", "");
		ui_interface.declare("fCheckbox4", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", function handler(obj) { function setval(val) { obj.fCheckbox4 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox2", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
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
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox5", "1", "");
		ui_interface.addCheckButton("Invert Flange Sum", function handler(obj) { function setval(val) { obj.fCheckbox5 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "2", "");
		ui_interface.declare("fHbargraph0", "style", "led");
		ui_interface.declare("fHbargraph0", "tooltip", "Display sum of flange delays");
		ui_interface.addHorizontalBargraph("Flange LFO", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -1.5, 1.5);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.5, 0, 10, 0.01);
		ui_interface.declare("fHslider5", "2", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.addHorizontalSlider("Depth", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), 1, 0, 1, 0.001);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 0, -0.999, 0.999, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("Delay Controls");
		ui_interface.declare("fHslider8", "1", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.declare("fHslider8", "unit", "ms");
		ui_interface.addHorizontalSlider("Flange Delay", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 10, 0, 20, 0.001);
		ui_interface.declare("fHslider7", "2", "");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.declare("fHslider7", "unit", "ms");
		ui_interface.addHorizontalSlider("Delay Offset", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 1, 0, 20, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider3", "unit", "dB");
		ui_interface.addHorizontalSlider("Flanger Output Level", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 0, -60, 10, 0.1);
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
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox7", "1", "");
		ui_interface.addCheckButton("Invert Internal Phaser Sum", function handler(obj) { function setval(val) { obj.fCheckbox7 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox6", "2", "");
		ui_interface.addCheckButton("Vibrato Mode", function handler(obj) { function setval(val) { obj.fCheckbox6 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider15", "1", "");
		ui_interface.declare("fHslider15", "style", "knob");
		ui_interface.declare("fHslider15", "unit", "Hz");
		ui_interface.addHorizontalSlider("Speed", function handler(obj) { function setval(val) { obj.fHslider15 = val; } return setval; }(this), 0.5, 0, 10, 0.001);
		ui_interface.declare("fHslider9", "2", "");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.addHorizontalSlider("Notch Depth (Intensity)", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 1, 0, 1, 0.001);
		ui_interface.declare("fHslider11", "3", "");
		ui_interface.declare("fHslider11", "style", "knob");
		ui_interface.addHorizontalSlider("Feedback Gain", function handler(obj) { function setval(val) { obj.fHslider11 = val; } return setval; }(this), 0, -0.999, 0.999, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "2", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider10", "1", "");
		ui_interface.declare("fHslider10", "scale", "log");
		ui_interface.declare("fHslider10", "style", "knob");
		ui_interface.declare("fHslider10", "unit", "Hz");
		ui_interface.addHorizontalSlider("Notch width", function handler(obj) { function setval(val) { obj.fHslider10 = val; } return setval; }(this), 1000, 10, 5000, 1);
		ui_interface.declare("fHslider13", "2", "");
		ui_interface.declare("fHslider13", "scale", "log");
		ui_interface.declare("fHslider13", "style", "knob");
		ui_interface.declare("fHslider13", "unit", "Hz");
		ui_interface.addHorizontalSlider("Min Notch1 Freq", function handler(obj) { function setval(val) { obj.fHslider13 = val; } return setval; }(this), 100, 20, 5000, 1);
		ui_interface.declare("fHslider14", "3", "");
		ui_interface.declare("fHslider14", "scale", "log");
		ui_interface.declare("fHslider14", "style", "knob");
		ui_interface.declare("fHslider14", "unit", "Hz");
		ui_interface.addHorizontalSlider("Max Notch1 Freq", function handler(obj) { function setval(val) { obj.fHslider14 = val; } return setval; }(this), 800, 20, 10000, 1);
		ui_interface.declare("fHslider12", "4", "");
		ui_interface.declare("fHslider12", "style", "knob");
		ui_interface.addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", function handler(obj) { function setval(val) { obj.fHslider12 = val; } return setval; }(this), 1.5, 1.1, 4, 0.001);
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("Phaser Output Level", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 0, -60, 10, 0.1);
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
		ui_interface.addVerticalBargraph("0x7fc6ce1cd890", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce1bbe80", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce199c80", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce177a80", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce155880", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce133680", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce111480", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce0eb300", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce0c9100", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce0a6f00", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce084d00", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce062b00", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce040900", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6ce01e700", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fc6cdff74f0", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
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
		var fSlow4 = Math.pow(10, (0.05 * this.fHslider2));
		var iSlow5 = this.fCheckbox1;
		var fSlow6 = Math.pow(10, (0.05 * this.fHslider3));
		var fSlow7 = (this.fConst14 * this.fHslider4);
		var fSlow8 = Math.sin(fSlow7);
		var fSlow9 = Math.cos(fSlow7);
		var fSlow10 = (0 - fSlow8);
		var iSlow11 = this.fCheckbox2;
		var iSlow12 = this.fCheckbox3;
		var fSlow13 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var iSlow14 = (this.fEntry0 + -1);
		var iSlow15 = (iSlow14 >= 2);
		var iSlow16 = (iSlow14 >= 1);
		var fSlow17 = Math.exp((0 - (this.fConst15 / this.fVslider2)));
		var fSlow18 = (440 * (Math.pow(2, (0.0833333 * (this.fVslider1 + -49))) * (1 - fSlow17)));
		var iSlow19 = (iSlow14 >= 3);
		var fSlow20 = ((0.01 * this.fVslider3) + 1);
		var fSlow21 = ((0.01 * this.fVslider4) + 1);
		var iSlow22 = this.fCheckbox4;
		var fSlow23 = this.fHslider5;
		var fSlow24 = (this.fCheckbox5?(0 - fSlow23):fSlow23);
		var fSlow25 = this.fHslider6;
		var fSlow26 = (0.001 * this.fHslider7);
		var fSlow27 = (0.0005 * this.fHslider8);
		var fSlow28 = (0.5 * (this.fCheckbox6?2:this.fHslider9));
		var fSlow29 = (1 - fSlow28);
		var fSlow30 = (this.fCheckbox7?(0 - fSlow28):fSlow28);
		var fSlow31 = Math.exp((this.fConst15 * (0 - (3.14159 * this.fHslider10))));
		var fSlow32 = mydsp_faustpower2_f(fSlow31);
		var fSlow33 = this.fHslider11;
		var fSlow34 = (0 - (2 * fSlow31));
		var fSlow35 = this.fHslider12;
		var fSlow36 = this.fHslider13;
		var fSlow37 = (this.fConst14 * fSlow36);
		var fSlow38 = (0.5 * (0 - (this.fConst14 * (fSlow36 - max_f(fSlow36, this.fHslider14)))));
		var fSlow39 = (this.fConst14 * this.fHslider15);
		var fSlow40 = Math.sin(fSlow39);
		var fSlow41 = Math.cos(fSlow39);
		var fSlow42 = (0 - fSlow40);
		var fSlow43 = mydsp_faustpower2_f(fSlow35);
		var fSlow44 = mydsp_faustpower3_f(fSlow35);
		var fSlow45 = mydsp_faustpower4_f(fSlow35);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec4[0] = ((fSlow8 * this.fRec5[1]) + (fSlow9 * this.fRec4[1]));
			var iTemp0 = (1 - this.iVec0[1]);
			this.fRec5[0] = (((fSlow9 * this.fRec5[1]) + (fSlow10 * this.fRec4[1])) + iTemp0);
			this.fHbargraph0 = (this.fRec5[0] + this.fRec4[0]);
			this.fRec6[0] = (fSlow13 + (0.999 * this.fRec6[1]));
			this.fRec8[0] = (fSlow18 + (fSlow17 * this.fRec8[1]));
			var fTemp1 = max_f(20, Math.abs(this.fRec8[0]));
			this.fVec1[0] = fTemp1;
			var fTemp2 = (this.fRec7[1] + (this.fConst15 * this.fVec1[1]));
			this.fRec7[0] = (fTemp2 - Math.floor(fTemp2));
			var fTemp3 = (2 * this.fRec7[0]);
			var fTemp4 = (fTemp3 + -1);
			var fTemp5 = mydsp_faustpower2_f(fTemp4);
			this.fVec2[0] = fTemp5;
			var fTemp6 = mydsp_faustpower3_f(fTemp4);
			this.fVec3[0] = (fTemp6 + (1 - fTemp3));
			var fTemp7 = ((fTemp6 + (1 - (fTemp3 + this.fVec3[1]))) / fTemp1);
			this.fVec4[0] = fTemp7;
			var fTemp8 = (fTemp5 * (fTemp5 + -2));
			this.fVec5[0] = fTemp8;
			var fTemp9 = ((fTemp8 - this.fVec5[1]) / fTemp1);
			this.fVec6[0] = fTemp9;
			var fTemp10 = ((fTemp9 - this.fVec6[1]) / fTemp1);
			this.fVec7[0] = fTemp10;
			var fTemp11 = max_f(20, Math.abs((fSlow20 * this.fRec8[0])));
			this.fVec8[0] = fTemp11;
			var fTemp12 = (this.fRec9[1] + (this.fConst15 * this.fVec8[1]));
			this.fRec9[0] = (fTemp12 - Math.floor(fTemp12));
			var fTemp13 = (2 * this.fRec9[0]);
			var fTemp14 = (fTemp13 + -1);
			var fTemp15 = mydsp_faustpower2_f(fTemp14);
			this.fVec9[0] = fTemp15;
			var fTemp16 = mydsp_faustpower3_f(fTemp14);
			this.fVec10[0] = (fTemp16 + (1 - fTemp13));
			var fTemp17 = ((fTemp16 + (1 - (fTemp13 + this.fVec10[1]))) / fTemp11);
			this.fVec11[0] = fTemp17;
			var fTemp18 = (fTemp15 * (fTemp15 + -2));
			this.fVec12[0] = fTemp18;
			var fTemp19 = ((fTemp18 - this.fVec12[1]) / fTemp11);
			this.fVec13[0] = fTemp19;
			var fTemp20 = ((fTemp19 - this.fVec13[1]) / fTemp11);
			this.fVec14[0] = fTemp20;
			var fTemp21 = max_f(20, Math.abs((fSlow21 * this.fRec8[0])));
			this.fVec15[0] = fTemp21;
			var fTemp22 = (this.fRec10[1] + (this.fConst15 * this.fVec15[1]));
			this.fRec10[0] = (fTemp22 - Math.floor(fTemp22));
			var fTemp23 = (2 * this.fRec10[0]);
			var fTemp24 = (fTemp23 + -1);
			var fTemp25 = mydsp_faustpower2_f(fTemp24);
			this.fVec16[0] = fTemp25;
			var fTemp26 = mydsp_faustpower3_f(fTemp24);
			this.fVec17[0] = (fTemp26 + (1 - fTemp23));
			var fTemp27 = ((fTemp26 + (1 - (fTemp23 + this.fVec17[1]))) / fTemp21);
			this.fVec18[0] = fTemp27;
			var fTemp28 = (fTemp25 * (fTemp25 + -2));
			this.fVec19[0] = fTemp28;
			var fTemp29 = ((fTemp28 - this.fVec19[1]) / fTemp21);
			this.fVec20[0] = fTemp29;
			var fTemp30 = ((fTemp29 - this.fVec20[1]) / fTemp21);
			this.fVec21[0] = fTemp30;
			this.iRec11[0] = ((1103515245 * this.iRec11[1]) + 12345);
			var fTemp31 = (4.65661e-10 * this.iRec11[0]);
			this.fRec12[0] = (((fTemp31 + (2.49496 * this.fRec12[1])) + (0.522189 * this.fRec12[3])) - (2.01727 * this.fRec12[2]));
			var fTemp32 = ((iSlow11?input0[i]:(iSlow12?(iSlow22?(((0.049922 * this.fRec12[0]) + (0.0506127 * this.fRec12[2])) - ((0.0959935 * this.fRec12[1]) + (0.00440879 * this.fRec12[3]))):fTemp31):(0.333333 * (this.fRec6[0] * (((iSlow15?(iSlow19?(this.fConst18 * ((this.iVec0[3] * (fTemp10 - this.fVec7[1])) / fTemp1)):(this.fConst17 * ((this.iVec0[2] * (fTemp7 - this.fVec4[1])) / fTemp1))):(iSlow16?(this.fConst16 * ((this.iVec0[1] * (fTemp5 - this.fVec2[1])) / fTemp1)):fTemp4)) + (iSlow15?(iSlow19?(this.fConst18 * ((this.iVec0[3] * (fTemp20 - this.fVec14[1])) / fTemp11)):(this.fConst17 * ((this.iVec0[2] * (fTemp17 - this.fVec11[1])) / fTemp11))):(iSlow16?(this.fConst16 * ((this.iVec0[1] * (fTemp15 - this.fVec9[1])) / fTemp11)):fTemp14))) + (iSlow15?(iSlow19?(this.fConst18 * ((this.iVec0[3] * (fTemp30 - this.fVec21[1])) / fTemp21)):(this.fConst17 * ((this.iVec0[2] * (fTemp27 - this.fVec18[1])) / fTemp21))):(iSlow16?(this.fConst16 * ((this.iVec0[1] * (fTemp25 - this.fVec16[1])) / fTemp21)):fTemp24))))))) * this.fRec6[0]);
			var fTemp33 = (iSlow5?0:fTemp32);
			var fTemp34 = (fSlow6 * fTemp33);
			var fTemp35 = ((fSlow25 * this.fRec13[1]) - fTemp34);
			this.fVec22[(this.IOTA & 4095)] = fTemp35;
			var fTemp36 = (this.fConst0 * (fSlow26 + (fSlow27 * (this.fRec4[0] + 1))));
			var iTemp37 = fTemp36;
			var fTemp38 = Math.floor(fTemp36);
			this.fRec13[0] = ((this.fVec22[((this.IOTA - min_i(2049, max_i(0, iTemp37))) & 4095)] * (fTemp38 + (1 - fTemp36))) + ((fTemp36 - fTemp38) * this.fVec22[((this.IOTA - min_i(2049, max_i(0, (iTemp37 + 1)))) & 4095)]));
			var fTemp39 = (iSlow5?fTemp32:(0.5 * (fTemp34 + (fSlow24 * this.fRec13[0]))));
			var fTemp40 = (iSlow3?0:fTemp39);
			this.fRec19[0] = ((fSlow40 * this.fRec20[1]) + (fSlow41 * this.fRec19[1]));
			this.fRec20[0] = (((fSlow41 * this.fRec20[1]) + (fSlow42 * this.fRec19[1])) + iTemp0);
			var fTemp41 = (fSlow37 + (fSlow38 * (1 - this.fRec19[0])));
			var fTemp42 = (this.fRec18[1] * Math.cos((fSlow35 * fTemp41)));
			this.fRec18[0] = (((fSlow4 * fTemp40) + (fSlow33 * this.fRec14[1])) - ((fSlow34 * fTemp42) + (fSlow32 * this.fRec18[2])));
			var fTemp43 = (this.fRec17[1] * Math.cos((fSlow43 * fTemp41)));
			this.fRec17[0] = ((this.fRec18[2] + (fSlow34 * (fTemp42 - fTemp43))) + (fSlow32 * (this.fRec18[0] - this.fRec17[2])));
			var fTemp44 = (this.fRec16[1] * Math.cos((fSlow44 * fTemp41)));
			this.fRec16[0] = ((this.fRec17[2] + (fSlow34 * (fTemp43 - fTemp44))) + (fSlow32 * (this.fRec17[0] - this.fRec16[2])));
			var fTemp45 = (this.fRec15[1] * Math.cos((fSlow45 * fTemp41)));
			this.fRec15[0] = ((this.fRec16[2] + (fSlow34 * (fTemp44 - fTemp45))) + (fSlow32 * (this.fRec16[0] - this.fRec15[2])));
			this.fRec14[0] = ((fSlow32 * this.fRec15[0]) + ((fSlow34 * fTemp45) + this.fRec15[2]));
			var fTemp46 = (iSlow3?fTemp39:((fSlow4 * (fTemp40 * fSlow29)) + (fSlow30 * this.fRec14[0])));
			var fTemp47 = (fSlow6 * fTemp33);
			var fTemp48 = ((fSlow25 * this.fRec21[1]) - fTemp47);
			this.fVec23[(this.IOTA & 4095)] = fTemp48;
			var fTemp49 = (this.fConst0 * (fSlow26 + (fSlow27 * (this.fRec5[0] + 1))));
			var iTemp50 = fTemp49;
			var fTemp51 = Math.floor(fTemp49);
			this.fRec21[0] = ((this.fVec23[((this.IOTA - min_i(2049, max_i(0, iTemp50))) & 4095)] * (fTemp51 + (1 - fTemp49))) + ((fTemp49 - fTemp51) * this.fVec23[((this.IOTA - min_i(2049, max_i(0, (iTemp50 + 1)))) & 4095)]));
			var fTemp52 = (iSlow5?fTemp32:(0.5 * (fTemp47 + (fSlow24 * this.fRec21[0]))));
			var fTemp53 = (iSlow3?0:fTemp52);
			var fTemp54 = (fSlow37 + (fSlow38 * (1 - this.fRec20[0])));
			var fTemp55 = (this.fRec26[1] * Math.cos((fSlow35 * fTemp54)));
			this.fRec26[0] = (((fSlow4 * fTemp53) + (fSlow33 * this.fRec22[1])) - ((fSlow34 * fTemp55) + (fSlow32 * this.fRec26[2])));
			var fTemp56 = (this.fRec25[1] * Math.cos((fSlow43 * fTemp54)));
			this.fRec25[0] = ((this.fRec26[2] + (fSlow34 * (fTemp55 - fTemp56))) + (fSlow32 * (this.fRec26[0] - this.fRec25[2])));
			var fTemp57 = (this.fRec24[1] * Math.cos((fSlow44 * fTemp54)));
			this.fRec24[0] = ((this.fRec25[2] + (fSlow34 * (fTemp56 - fTemp57))) + (fSlow32 * (this.fRec25[0] - this.fRec24[2])));
			var fTemp58 = (this.fRec23[1] * Math.cos((fSlow45 * fTemp54)));
			this.fRec23[0] = ((this.fRec24[2] + (fSlow34 * (fTemp57 - fTemp58))) + (fSlow32 * (this.fRec24[0] - this.fRec23[2])));
			this.fRec22[0] = ((fSlow32 * this.fRec23[0]) + ((fSlow34 * fTemp58) + this.fRec23[2]));
			var fTemp59 = (iSlow3?fTemp52:((fSlow4 * (fSlow29 * fTemp53)) + (fSlow30 * this.fRec22[0])));
			var fTemp60 = (fTemp46 + fTemp59);
			this.fRec3[0] = (fTemp60 - (this.fConst11 * ((this.fConst19 * this.fRec3[2]) + (this.fConst21 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[1]) + (this.fConst22 * this.fRec3[0])) + (this.fConst22 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst23 * this.fRec2[2]) + (this.fConst24 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst25 * this.fRec2[0])) + (this.fConst25 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst26 * this.fRec1[2]) + (this.fConst27 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst28 * this.fRec1[0])) + (this.fConst28 * this.fRec1[2]))))));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec33[0] = (fTemp60 - (this.fConst45 * ((this.fConst48 * this.fRec33[2]) + (this.fConst49 * this.fRec33[1]))));
			this.fRec32[0] = ((this.fConst45 * (((this.fConst47 * this.fRec33[1]) + (this.fConst50 * this.fRec33[0])) + (this.fConst50 * this.fRec33[2]))) - (this.fConst43 * ((this.fConst51 * this.fRec32[2]) + (this.fConst52 * this.fRec32[1]))));
			this.fRec31[0] = ((this.fConst43 * (((this.fConst44 * this.fRec32[1]) + (this.fConst53 * this.fRec32[0])) + (this.fConst53 * this.fRec32[2]))) - (this.fConst41 * ((this.fConst54 * this.fRec31[2]) + (this.fConst55 * this.fRec31[1]))));
			var fTemp61 = (this.fConst41 * (((this.fConst42 * this.fRec31[1]) + (this.fConst56 * this.fRec31[0])) + (this.fConst56 * this.fRec31[2])));
			this.fRec30[0] = (fTemp61 - (this.fConst38 * ((this.fConst57 * this.fRec30[2]) + (this.fConst59 * this.fRec30[1]))));
			this.fRec29[0] = ((this.fConst38 * (((this.fConst40 * this.fRec30[1]) + (this.fConst60 * this.fRec30[0])) + (this.fConst60 * this.fRec30[2]))) - (this.fConst35 * ((this.fConst61 * this.fRec29[2]) + (this.fConst62 * this.fRec29[1]))));
			this.fRec28[0] = ((this.fConst35 * (((this.fConst37 * this.fRec29[1]) + (this.fConst63 * this.fRec29[0])) + (this.fConst63 * this.fRec29[2]))) - (this.fConst31 * ((this.fConst64 * this.fRec28[2]) + (this.fConst65 * this.fRec28[1]))));
			this.fRec27[0] = ((fSlow1 * this.fRec27[1]) + (fSlow2 * Math.abs((this.fConst31 * (((this.fConst34 * this.fRec28[1]) + (this.fConst66 * this.fRec28[0])) + (this.fConst66 * this.fRec28[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec27[0]))));
			this.fRec40[0] = (fTemp61 - (this.fConst83 * ((this.fConst86 * this.fRec40[2]) + (this.fConst87 * this.fRec40[1]))));
			this.fRec39[0] = ((this.fConst83 * (((this.fConst85 * this.fRec40[1]) + (this.fConst88 * this.fRec40[0])) + (this.fConst88 * this.fRec40[2]))) - (this.fConst81 * ((this.fConst89 * this.fRec39[2]) + (this.fConst90 * this.fRec39[1]))));
			this.fRec38[0] = ((this.fConst81 * (((this.fConst82 * this.fRec39[1]) + (this.fConst91 * this.fRec39[0])) + (this.fConst91 * this.fRec39[2]))) - (this.fConst79 * ((this.fConst92 * this.fRec38[2]) + (this.fConst93 * this.fRec38[1]))));
			var fTemp62 = (this.fConst79 * (((this.fConst80 * this.fRec38[1]) + (this.fConst94 * this.fRec38[0])) + (this.fConst94 * this.fRec38[2])));
			this.fRec37[0] = (fTemp62 - (this.fConst76 * ((this.fConst95 * this.fRec37[2]) + (this.fConst97 * this.fRec37[1]))));
			this.fRec36[0] = ((this.fConst76 * (((this.fConst78 * this.fRec37[1]) + (this.fConst98 * this.fRec37[0])) + (this.fConst98 * this.fRec37[2]))) - (this.fConst73 * ((this.fConst99 * this.fRec36[2]) + (this.fConst100 * this.fRec36[1]))));
			this.fRec35[0] = ((this.fConst73 * (((this.fConst75 * this.fRec36[1]) + (this.fConst101 * this.fRec36[0])) + (this.fConst101 * this.fRec36[2]))) - (this.fConst69 * ((this.fConst102 * this.fRec35[2]) + (this.fConst103 * this.fRec35[1]))));
			this.fRec34[0] = ((fSlow1 * this.fRec34[1]) + (fSlow2 * Math.abs((this.fConst69 * (((this.fConst72 * this.fRec35[1]) + (this.fConst104 * this.fRec35[0])) + (this.fConst104 * this.fRec35[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec34[0]))));
			this.fRec47[0] = (fTemp62 - (this.fConst121 * ((this.fConst124 * this.fRec47[2]) + (this.fConst125 * this.fRec47[1]))));
			this.fRec46[0] = ((this.fConst121 * (((this.fConst123 * this.fRec47[1]) + (this.fConst126 * this.fRec47[0])) + (this.fConst126 * this.fRec47[2]))) - (this.fConst119 * ((this.fConst127 * this.fRec46[2]) + (this.fConst128 * this.fRec46[1]))));
			this.fRec45[0] = ((this.fConst119 * (((this.fConst120 * this.fRec46[1]) + (this.fConst129 * this.fRec46[0])) + (this.fConst129 * this.fRec46[2]))) - (this.fConst117 * ((this.fConst130 * this.fRec45[2]) + (this.fConst131 * this.fRec45[1]))));
			var fTemp63 = (this.fConst117 * (((this.fConst118 * this.fRec45[1]) + (this.fConst132 * this.fRec45[0])) + (this.fConst132 * this.fRec45[2])));
			this.fRec44[0] = (fTemp63 - (this.fConst114 * ((this.fConst133 * this.fRec44[2]) + (this.fConst135 * this.fRec44[1]))));
			this.fRec43[0] = ((this.fConst114 * (((this.fConst116 * this.fRec44[1]) + (this.fConst136 * this.fRec44[0])) + (this.fConst136 * this.fRec44[2]))) - (this.fConst111 * ((this.fConst137 * this.fRec43[2]) + (this.fConst138 * this.fRec43[1]))));
			this.fRec42[0] = ((this.fConst111 * (((this.fConst113 * this.fRec43[1]) + (this.fConst139 * this.fRec43[0])) + (this.fConst139 * this.fRec43[2]))) - (this.fConst107 * ((this.fConst140 * this.fRec42[2]) + (this.fConst141 * this.fRec42[1]))));
			this.fRec41[0] = ((fSlow1 * this.fRec41[1]) + (fSlow2 * Math.abs((this.fConst107 * (((this.fConst110 * this.fRec42[1]) + (this.fConst142 * this.fRec42[0])) + (this.fConst142 * this.fRec42[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec41[0]))));
			this.fRec54[0] = (fTemp63 - (this.fConst159 * ((this.fConst162 * this.fRec54[2]) + (this.fConst163 * this.fRec54[1]))));
			this.fRec53[0] = ((this.fConst159 * (((this.fConst161 * this.fRec54[1]) + (this.fConst164 * this.fRec54[0])) + (this.fConst164 * this.fRec54[2]))) - (this.fConst157 * ((this.fConst165 * this.fRec53[2]) + (this.fConst166 * this.fRec53[1]))));
			this.fRec52[0] = ((this.fConst157 * (((this.fConst158 * this.fRec53[1]) + (this.fConst167 * this.fRec53[0])) + (this.fConst167 * this.fRec53[2]))) - (this.fConst155 * ((this.fConst168 * this.fRec52[2]) + (this.fConst169 * this.fRec52[1]))));
			var fTemp64 = (this.fConst155 * (((this.fConst156 * this.fRec52[1]) + (this.fConst170 * this.fRec52[0])) + (this.fConst170 * this.fRec52[2])));
			this.fRec51[0] = (fTemp64 - (this.fConst152 * ((this.fConst171 * this.fRec51[2]) + (this.fConst173 * this.fRec51[1]))));
			this.fRec50[0] = ((this.fConst152 * (((this.fConst154 * this.fRec51[1]) + (this.fConst174 * this.fRec51[0])) + (this.fConst174 * this.fRec51[2]))) - (this.fConst149 * ((this.fConst175 * this.fRec50[2]) + (this.fConst176 * this.fRec50[1]))));
			this.fRec49[0] = ((this.fConst149 * (((this.fConst151 * this.fRec50[1]) + (this.fConst177 * this.fRec50[0])) + (this.fConst177 * this.fRec50[2]))) - (this.fConst145 * ((this.fConst178 * this.fRec49[2]) + (this.fConst179 * this.fRec49[1]))));
			this.fRec48[0] = ((fSlow1 * this.fRec48[1]) + (fSlow2 * Math.abs((this.fConst145 * (((this.fConst148 * this.fRec49[1]) + (this.fConst180 * this.fRec49[0])) + (this.fConst180 * this.fRec49[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec48[0]))));
			this.fRec61[0] = (fTemp64 - (this.fConst197 * ((this.fConst200 * this.fRec61[2]) + (this.fConst201 * this.fRec61[1]))));
			this.fRec60[0] = ((this.fConst197 * (((this.fConst199 * this.fRec61[1]) + (this.fConst202 * this.fRec61[0])) + (this.fConst202 * this.fRec61[2]))) - (this.fConst195 * ((this.fConst203 * this.fRec60[2]) + (this.fConst204 * this.fRec60[1]))));
			this.fRec59[0] = ((this.fConst195 * (((this.fConst196 * this.fRec60[1]) + (this.fConst205 * this.fRec60[0])) + (this.fConst205 * this.fRec60[2]))) - (this.fConst193 * ((this.fConst206 * this.fRec59[2]) + (this.fConst207 * this.fRec59[1]))));
			var fTemp65 = (this.fConst193 * (((this.fConst194 * this.fRec59[1]) + (this.fConst208 * this.fRec59[0])) + (this.fConst208 * this.fRec59[2])));
			this.fRec58[0] = (fTemp65 - (this.fConst190 * ((this.fConst209 * this.fRec58[2]) + (this.fConst211 * this.fRec58[1]))));
			this.fRec57[0] = ((this.fConst190 * (((this.fConst192 * this.fRec58[1]) + (this.fConst212 * this.fRec58[0])) + (this.fConst212 * this.fRec58[2]))) - (this.fConst187 * ((this.fConst213 * this.fRec57[2]) + (this.fConst214 * this.fRec57[1]))));
			this.fRec56[0] = ((this.fConst187 * (((this.fConst189 * this.fRec57[1]) + (this.fConst215 * this.fRec57[0])) + (this.fConst215 * this.fRec57[2]))) - (this.fConst183 * ((this.fConst216 * this.fRec56[2]) + (this.fConst217 * this.fRec56[1]))));
			this.fRec55[0] = ((fSlow1 * this.fRec55[1]) + (fSlow2 * Math.abs((this.fConst183 * (((this.fConst186 * this.fRec56[1]) + (this.fConst218 * this.fRec56[0])) + (this.fConst218 * this.fRec56[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec55[0]))));
			this.fRec68[0] = (fTemp65 - (this.fConst235 * ((this.fConst238 * this.fRec68[2]) + (this.fConst239 * this.fRec68[1]))));
			this.fRec67[0] = ((this.fConst235 * (((this.fConst237 * this.fRec68[1]) + (this.fConst240 * this.fRec68[0])) + (this.fConst240 * this.fRec68[2]))) - (this.fConst233 * ((this.fConst241 * this.fRec67[2]) + (this.fConst242 * this.fRec67[1]))));
			this.fRec66[0] = ((this.fConst233 * (((this.fConst234 * this.fRec67[1]) + (this.fConst243 * this.fRec67[0])) + (this.fConst243 * this.fRec67[2]))) - (this.fConst231 * ((this.fConst244 * this.fRec66[2]) + (this.fConst245 * this.fRec66[1]))));
			var fTemp66 = (this.fConst231 * (((this.fConst232 * this.fRec66[1]) + (this.fConst246 * this.fRec66[0])) + (this.fConst246 * this.fRec66[2])));
			this.fRec65[0] = (fTemp66 - (this.fConst228 * ((this.fConst247 * this.fRec65[2]) + (this.fConst249 * this.fRec65[1]))));
			this.fRec64[0] = ((this.fConst228 * (((this.fConst230 * this.fRec65[1]) + (this.fConst250 * this.fRec65[0])) + (this.fConst250 * this.fRec65[2]))) - (this.fConst225 * ((this.fConst251 * this.fRec64[2]) + (this.fConst252 * this.fRec64[1]))));
			this.fRec63[0] = ((this.fConst225 * (((this.fConst227 * this.fRec64[1]) + (this.fConst253 * this.fRec64[0])) + (this.fConst253 * this.fRec64[2]))) - (this.fConst221 * ((this.fConst254 * this.fRec63[2]) + (this.fConst255 * this.fRec63[1]))));
			this.fRec62[0] = ((fSlow1 * this.fRec62[1]) + (fSlow2 * Math.abs((this.fConst221 * (((this.fConst224 * this.fRec63[1]) + (this.fConst256 * this.fRec63[0])) + (this.fConst256 * this.fRec63[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec62[0]))));
			this.fRec75[0] = (fTemp66 - (this.fConst273 * ((this.fConst276 * this.fRec75[2]) + (this.fConst277 * this.fRec75[1]))));
			this.fRec74[0] = ((this.fConst273 * (((this.fConst275 * this.fRec75[1]) + (this.fConst278 * this.fRec75[0])) + (this.fConst278 * this.fRec75[2]))) - (this.fConst271 * ((this.fConst279 * this.fRec74[2]) + (this.fConst280 * this.fRec74[1]))));
			this.fRec73[0] = ((this.fConst271 * (((this.fConst272 * this.fRec74[1]) + (this.fConst281 * this.fRec74[0])) + (this.fConst281 * this.fRec74[2]))) - (this.fConst269 * ((this.fConst282 * this.fRec73[2]) + (this.fConst283 * this.fRec73[1]))));
			var fTemp67 = (this.fConst269 * (((this.fConst270 * this.fRec73[1]) + (this.fConst284 * this.fRec73[0])) + (this.fConst284 * this.fRec73[2])));
			this.fRec72[0] = (fTemp67 - (this.fConst266 * ((this.fConst285 * this.fRec72[2]) + (this.fConst287 * this.fRec72[1]))));
			this.fRec71[0] = ((this.fConst266 * (((this.fConst268 * this.fRec72[1]) + (this.fConst288 * this.fRec72[0])) + (this.fConst288 * this.fRec72[2]))) - (this.fConst263 * ((this.fConst289 * this.fRec71[2]) + (this.fConst290 * this.fRec71[1]))));
			this.fRec70[0] = ((this.fConst263 * (((this.fConst265 * this.fRec71[1]) + (this.fConst291 * this.fRec71[0])) + (this.fConst291 * this.fRec71[2]))) - (this.fConst259 * ((this.fConst292 * this.fRec70[2]) + (this.fConst293 * this.fRec70[1]))));
			this.fRec69[0] = ((fSlow1 * this.fRec69[1]) + (fSlow2 * Math.abs((this.fConst259 * (((this.fConst262 * this.fRec70[1]) + (this.fConst294 * this.fRec70[0])) + (this.fConst294 * this.fRec70[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec69[0]))));
			this.fRec82[0] = (fTemp67 - (this.fConst311 * ((this.fConst314 * this.fRec82[2]) + (this.fConst315 * this.fRec82[1]))));
			this.fRec81[0] = ((this.fConst311 * (((this.fConst313 * this.fRec82[1]) + (this.fConst316 * this.fRec82[0])) + (this.fConst316 * this.fRec82[2]))) - (this.fConst309 * ((this.fConst317 * this.fRec81[2]) + (this.fConst318 * this.fRec81[1]))));
			this.fRec80[0] = ((this.fConst309 * (((this.fConst310 * this.fRec81[1]) + (this.fConst319 * this.fRec81[0])) + (this.fConst319 * this.fRec81[2]))) - (this.fConst307 * ((this.fConst320 * this.fRec80[2]) + (this.fConst321 * this.fRec80[1]))));
			var fTemp68 = (this.fConst307 * (((this.fConst308 * this.fRec80[1]) + (this.fConst322 * this.fRec80[0])) + (this.fConst322 * this.fRec80[2])));
			this.fRec79[0] = (fTemp68 - (this.fConst304 * ((this.fConst323 * this.fRec79[2]) + (this.fConst325 * this.fRec79[1]))));
			this.fRec78[0] = ((this.fConst304 * (((this.fConst306 * this.fRec79[1]) + (this.fConst326 * this.fRec79[0])) + (this.fConst326 * this.fRec79[2]))) - (this.fConst301 * ((this.fConst327 * this.fRec78[2]) + (this.fConst328 * this.fRec78[1]))));
			this.fRec77[0] = ((this.fConst301 * (((this.fConst303 * this.fRec78[1]) + (this.fConst329 * this.fRec78[0])) + (this.fConst329 * this.fRec78[2]))) - (this.fConst297 * ((this.fConst330 * this.fRec77[2]) + (this.fConst331 * this.fRec77[1]))));
			this.fRec76[0] = ((fSlow1 * this.fRec76[1]) + (fSlow2 * Math.abs((this.fConst297 * (((this.fConst300 * this.fRec77[1]) + (this.fConst332 * this.fRec77[0])) + (this.fConst332 * this.fRec77[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec76[0]))));
			this.fRec89[0] = (fTemp68 - (this.fConst349 * ((this.fConst352 * this.fRec89[2]) + (this.fConst353 * this.fRec89[1]))));
			this.fRec88[0] = ((this.fConst349 * (((this.fConst351 * this.fRec89[1]) + (this.fConst354 * this.fRec89[0])) + (this.fConst354 * this.fRec89[2]))) - (this.fConst347 * ((this.fConst355 * this.fRec88[2]) + (this.fConst356 * this.fRec88[1]))));
			this.fRec87[0] = ((this.fConst347 * (((this.fConst348 * this.fRec88[1]) + (this.fConst357 * this.fRec88[0])) + (this.fConst357 * this.fRec88[2]))) - (this.fConst345 * ((this.fConst358 * this.fRec87[2]) + (this.fConst359 * this.fRec87[1]))));
			var fTemp69 = (this.fConst345 * (((this.fConst346 * this.fRec87[1]) + (this.fConst360 * this.fRec87[0])) + (this.fConst360 * this.fRec87[2])));
			this.fRec86[0] = (fTemp69 - (this.fConst342 * ((this.fConst361 * this.fRec86[2]) + (this.fConst363 * this.fRec86[1]))));
			this.fRec85[0] = ((this.fConst342 * (((this.fConst344 * this.fRec86[1]) + (this.fConst364 * this.fRec86[0])) + (this.fConst364 * this.fRec86[2]))) - (this.fConst339 * ((this.fConst365 * this.fRec85[2]) + (this.fConst366 * this.fRec85[1]))));
			this.fRec84[0] = ((this.fConst339 * (((this.fConst341 * this.fRec85[1]) + (this.fConst367 * this.fRec85[0])) + (this.fConst367 * this.fRec85[2]))) - (this.fConst335 * ((this.fConst368 * this.fRec84[2]) + (this.fConst369 * this.fRec84[1]))));
			this.fRec83[0] = ((fSlow1 * this.fRec83[1]) + (fSlow2 * Math.abs((this.fConst335 * (((this.fConst338 * this.fRec84[1]) + (this.fConst370 * this.fRec84[0])) + (this.fConst370 * this.fRec84[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec83[0]))));
			this.fRec96[0] = (fTemp69 - (this.fConst387 * ((this.fConst390 * this.fRec96[2]) + (this.fConst391 * this.fRec96[1]))));
			this.fRec95[0] = ((this.fConst387 * (((this.fConst389 * this.fRec96[1]) + (this.fConst392 * this.fRec96[0])) + (this.fConst392 * this.fRec96[2]))) - (this.fConst385 * ((this.fConst393 * this.fRec95[2]) + (this.fConst394 * this.fRec95[1]))));
			this.fRec94[0] = ((this.fConst385 * (((this.fConst386 * this.fRec95[1]) + (this.fConst395 * this.fRec95[0])) + (this.fConst395 * this.fRec95[2]))) - (this.fConst383 * ((this.fConst396 * this.fRec94[2]) + (this.fConst397 * this.fRec94[1]))));
			var fTemp70 = (this.fConst383 * (((this.fConst384 * this.fRec94[1]) + (this.fConst398 * this.fRec94[0])) + (this.fConst398 * this.fRec94[2])));
			this.fRec93[0] = (fTemp70 - (this.fConst380 * ((this.fConst399 * this.fRec93[2]) + (this.fConst401 * this.fRec93[1]))));
			this.fRec92[0] = ((this.fConst380 * (((this.fConst382 * this.fRec93[1]) + (this.fConst402 * this.fRec93[0])) + (this.fConst402 * this.fRec93[2]))) - (this.fConst377 * ((this.fConst403 * this.fRec92[2]) + (this.fConst404 * this.fRec92[1]))));
			this.fRec91[0] = ((this.fConst377 * (((this.fConst379 * this.fRec92[1]) + (this.fConst405 * this.fRec92[0])) + (this.fConst405 * this.fRec92[2]))) - (this.fConst373 * ((this.fConst406 * this.fRec91[2]) + (this.fConst407 * this.fRec91[1]))));
			this.fRec90[0] = ((fSlow1 * this.fRec90[1]) + (fSlow2 * Math.abs((this.fConst373 * (((this.fConst376 * this.fRec91[1]) + (this.fConst408 * this.fRec91[0])) + (this.fConst408 * this.fRec91[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec90[0]))));
			this.fRec103[0] = (fTemp70 - (this.fConst425 * ((this.fConst428 * this.fRec103[2]) + (this.fConst429 * this.fRec103[1]))));
			this.fRec102[0] = ((this.fConst425 * (((this.fConst427 * this.fRec103[1]) + (this.fConst430 * this.fRec103[0])) + (this.fConst430 * this.fRec103[2]))) - (this.fConst423 * ((this.fConst431 * this.fRec102[2]) + (this.fConst432 * this.fRec102[1]))));
			this.fRec101[0] = ((this.fConst423 * (((this.fConst424 * this.fRec102[1]) + (this.fConst433 * this.fRec102[0])) + (this.fConst433 * this.fRec102[2]))) - (this.fConst421 * ((this.fConst434 * this.fRec101[2]) + (this.fConst435 * this.fRec101[1]))));
			var fTemp71 = (this.fConst421 * (((this.fConst422 * this.fRec101[1]) + (this.fConst436 * this.fRec101[0])) + (this.fConst436 * this.fRec101[2])));
			this.fRec100[0] = (fTemp71 - (this.fConst418 * ((this.fConst437 * this.fRec100[2]) + (this.fConst439 * this.fRec100[1]))));
			this.fRec99[0] = ((this.fConst418 * (((this.fConst420 * this.fRec100[1]) + (this.fConst440 * this.fRec100[0])) + (this.fConst440 * this.fRec100[2]))) - (this.fConst415 * ((this.fConst441 * this.fRec99[2]) + (this.fConst442 * this.fRec99[1]))));
			this.fRec98[0] = ((this.fConst415 * (((this.fConst417 * this.fRec99[1]) + (this.fConst443 * this.fRec99[0])) + (this.fConst443 * this.fRec99[2]))) - (this.fConst411 * ((this.fConst444 * this.fRec98[2]) + (this.fConst445 * this.fRec98[1]))));
			this.fRec97[0] = ((fSlow1 * this.fRec97[1]) + (fSlow2 * Math.abs((this.fConst411 * (((this.fConst414 * this.fRec98[1]) + (this.fConst446 * this.fRec98[0])) + (this.fConst446 * this.fRec98[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec97[0]))));
			this.fRec110[0] = (fTemp71 - (this.fConst463 * ((this.fConst466 * this.fRec110[2]) + (this.fConst467 * this.fRec110[1]))));
			this.fRec109[0] = ((this.fConst463 * (((this.fConst465 * this.fRec110[1]) + (this.fConst468 * this.fRec110[0])) + (this.fConst468 * this.fRec110[2]))) - (this.fConst461 * ((this.fConst469 * this.fRec109[2]) + (this.fConst470 * this.fRec109[1]))));
			this.fRec108[0] = ((this.fConst461 * (((this.fConst462 * this.fRec109[1]) + (this.fConst471 * this.fRec109[0])) + (this.fConst471 * this.fRec109[2]))) - (this.fConst459 * ((this.fConst472 * this.fRec108[2]) + (this.fConst473 * this.fRec108[1]))));
			var fTemp72 = (this.fConst459 * (((this.fConst460 * this.fRec108[1]) + (this.fConst474 * this.fRec108[0])) + (this.fConst474 * this.fRec108[2])));
			this.fRec107[0] = (fTemp72 - (this.fConst456 * ((this.fConst475 * this.fRec107[2]) + (this.fConst477 * this.fRec107[1]))));
			this.fRec106[0] = ((this.fConst456 * (((this.fConst458 * this.fRec107[1]) + (this.fConst478 * this.fRec107[0])) + (this.fConst478 * this.fRec107[2]))) - (this.fConst453 * ((this.fConst479 * this.fRec106[2]) + (this.fConst480 * this.fRec106[1]))));
			this.fRec105[0] = ((this.fConst453 * (((this.fConst455 * this.fRec106[1]) + (this.fConst481 * this.fRec106[0])) + (this.fConst481 * this.fRec106[2]))) - (this.fConst449 * ((this.fConst482 * this.fRec105[2]) + (this.fConst483 * this.fRec105[1]))));
			this.fRec104[0] = ((fSlow1 * this.fRec104[1]) + (fSlow2 * Math.abs((this.fConst449 * (((this.fConst452 * this.fRec105[1]) + (this.fConst484 * this.fRec105[0])) + (this.fConst484 * this.fRec105[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec104[0]))));
			this.fRec117[0] = (fTemp72 - (this.fConst501 * ((this.fConst504 * this.fRec117[2]) + (this.fConst505 * this.fRec117[1]))));
			this.fRec116[0] = ((this.fConst501 * (((this.fConst503 * this.fRec117[1]) + (this.fConst506 * this.fRec117[0])) + (this.fConst506 * this.fRec117[2]))) - (this.fConst499 * ((this.fConst507 * this.fRec116[2]) + (this.fConst508 * this.fRec116[1]))));
			this.fRec115[0] = ((this.fConst499 * (((this.fConst500 * this.fRec116[1]) + (this.fConst509 * this.fRec116[0])) + (this.fConst509 * this.fRec116[2]))) - (this.fConst497 * ((this.fConst510 * this.fRec115[2]) + (this.fConst511 * this.fRec115[1]))));
			var fTemp73 = (this.fConst497 * (((this.fConst498 * this.fRec115[1]) + (this.fConst512 * this.fRec115[0])) + (this.fConst512 * this.fRec115[2])));
			this.fRec114[0] = (fTemp73 - (this.fConst494 * ((this.fConst513 * this.fRec114[2]) + (this.fConst515 * this.fRec114[1]))));
			this.fRec113[0] = ((this.fConst494 * (((this.fConst496 * this.fRec114[1]) + (this.fConst516 * this.fRec114[0])) + (this.fConst516 * this.fRec114[2]))) - (this.fConst491 * ((this.fConst517 * this.fRec113[2]) + (this.fConst518 * this.fRec113[1]))));
			this.fRec112[0] = ((this.fConst491 * (((this.fConst493 * this.fRec113[1]) + (this.fConst519 * this.fRec113[0])) + (this.fConst519 * this.fRec113[2]))) - (this.fConst487 * ((this.fConst520 * this.fRec112[2]) + (this.fConst521 * this.fRec112[1]))));
			this.fRec111[0] = ((fSlow1 * this.fRec111[1]) + (fSlow2 * Math.abs((this.fConst487 * (((this.fConst490 * this.fRec112[1]) + (this.fConst522 * this.fRec112[0])) + (this.fConst522 * this.fRec112[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec111[0]))));
			this.fRec121[0] = (fTemp73 - (this.fConst527 * ((this.fConst530 * this.fRec121[2]) + (this.fConst531 * this.fRec121[1]))));
			this.fRec120[0] = ((this.fConst527 * (((this.fConst529 * this.fRec121[1]) + (this.fConst532 * this.fRec121[0])) + (this.fConst532 * this.fRec121[2]))) - (this.fConst525 * ((this.fConst533 * this.fRec120[2]) + (this.fConst534 * this.fRec120[1]))));
			this.fRec119[0] = ((this.fConst525 * (((this.fConst526 * this.fRec120[1]) + (this.fConst535 * this.fRec120[0])) + (this.fConst535 * this.fRec120[2]))) - (this.fConst523 * ((this.fConst536 * this.fRec119[2]) + (this.fConst537 * this.fRec119[1]))));
			this.fRec118[0] = ((fSlow1 * this.fRec118[1]) + (fSlow2 * Math.abs((this.fConst523 * (((this.fConst524 * this.fRec119[1]) + (this.fConst538 * this.fRec119[0])) + (this.fConst538 * this.fRec119[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec118[0]))));
			output0[i] = fTemp46;
			output1[i] = fTemp59;
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec4[1] = this.fRec4[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec8[1] = this.fRec8[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec7[1] = this.fRec7[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec9[1] = this.fRec9[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec10[1] = this.fRec10[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.iRec11[1] = this.iRec11[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec12[j1] = this.fRec12[(j1 - 1)];
				
			}
			this.IOTA = (this.IOTA + 1);
			this.fRec13[1] = this.fRec13[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec17[2] = this.fRec17[1];
			this.fRec17[1] = this.fRec17[0];
			this.fRec16[2] = this.fRec16[1];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[2] = this.fRec15[1];
			this.fRec15[1] = this.fRec15[0];
			this.fRec14[1] = this.fRec14[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec25[2] = this.fRec25[1];
			this.fRec25[1] = this.fRec25[0];
			this.fRec24[2] = this.fRec24[1];
			this.fRec24[1] = this.fRec24[0];
			this.fRec23[2] = this.fRec23[1];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec33[2] = this.fRec33[1];
			this.fRec33[1] = this.fRec33[0];
			this.fRec32[2] = this.fRec32[1];
			this.fRec32[1] = this.fRec32[0];
			this.fRec31[2] = this.fRec31[1];
			this.fRec31[1] = this.fRec31[0];
			this.fRec30[2] = this.fRec30[1];
			this.fRec30[1] = this.fRec30[0];
			this.fRec29[2] = this.fRec29[1];
			this.fRec29[1] = this.fRec29[0];
			this.fRec28[2] = this.fRec28[1];
			this.fRec28[1] = this.fRec28[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec40[2] = this.fRec40[1];
			this.fRec40[1] = this.fRec40[0];
			this.fRec39[2] = this.fRec39[1];
			this.fRec39[1] = this.fRec39[0];
			this.fRec38[2] = this.fRec38[1];
			this.fRec38[1] = this.fRec38[0];
			this.fRec37[2] = this.fRec37[1];
			this.fRec37[1] = this.fRec37[0];
			this.fRec36[2] = this.fRec36[1];
			this.fRec36[1] = this.fRec36[0];
			this.fRec35[2] = this.fRec35[1];
			this.fRec35[1] = this.fRec35[0];
			this.fRec34[1] = this.fRec34[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[2] = this.fRec46[1];
			this.fRec46[1] = this.fRec46[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[2] = this.fRec44[1];
			this.fRec44[1] = this.fRec44[0];
			this.fRec43[2] = this.fRec43[1];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[2] = this.fRec42[1];
			this.fRec42[1] = this.fRec42[0];
			this.fRec41[1] = this.fRec41[0];
			this.fRec54[2] = this.fRec54[1];
			this.fRec54[1] = this.fRec54[0];
			this.fRec53[2] = this.fRec53[1];
			this.fRec53[1] = this.fRec53[0];
			this.fRec52[2] = this.fRec52[1];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[2] = this.fRec51[1];
			this.fRec51[1] = this.fRec51[0];
			this.fRec50[2] = this.fRec50[1];
			this.fRec50[1] = this.fRec50[0];
			this.fRec49[2] = this.fRec49[1];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[1] = this.fRec48[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fRec60[2] = this.fRec60[1];
			this.fRec60[1] = this.fRec60[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[2] = this.fRec58[1];
			this.fRec58[1] = this.fRec58[0];
			this.fRec57[2] = this.fRec57[1];
			this.fRec57[1] = this.fRec57[0];
			this.fRec56[2] = this.fRec56[1];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[1] = this.fRec55[0];
			this.fRec68[2] = this.fRec68[1];
			this.fRec68[1] = this.fRec68[0];
			this.fRec67[2] = this.fRec67[1];
			this.fRec67[1] = this.fRec67[0];
			this.fRec66[2] = this.fRec66[1];
			this.fRec66[1] = this.fRec66[0];
			this.fRec65[2] = this.fRec65[1];
			this.fRec65[1] = this.fRec65[0];
			this.fRec64[2] = this.fRec64[1];
			this.fRec64[1] = this.fRec64[0];
			this.fRec63[2] = this.fRec63[1];
			this.fRec63[1] = this.fRec63[0];
			this.fRec62[1] = this.fRec62[0];
			this.fRec75[2] = this.fRec75[1];
			this.fRec75[1] = this.fRec75[0];
			this.fRec74[2] = this.fRec74[1];
			this.fRec74[1] = this.fRec74[0];
			this.fRec73[2] = this.fRec73[1];
			this.fRec73[1] = this.fRec73[0];
			this.fRec72[2] = this.fRec72[1];
			this.fRec72[1] = this.fRec72[0];
			this.fRec71[2] = this.fRec71[1];
			this.fRec71[1] = this.fRec71[0];
			this.fRec70[2] = this.fRec70[1];
			this.fRec70[1] = this.fRec70[0];
			this.fRec69[1] = this.fRec69[0];
			this.fRec82[2] = this.fRec82[1];
			this.fRec82[1] = this.fRec82[0];
			this.fRec81[2] = this.fRec81[1];
			this.fRec81[1] = this.fRec81[0];
			this.fRec80[2] = this.fRec80[1];
			this.fRec80[1] = this.fRec80[0];
			this.fRec79[2] = this.fRec79[1];
			this.fRec79[1] = this.fRec79[0];
			this.fRec78[2] = this.fRec78[1];
			this.fRec78[1] = this.fRec78[0];
			this.fRec77[2] = this.fRec77[1];
			this.fRec77[1] = this.fRec77[0];
			this.fRec76[1] = this.fRec76[0];
			this.fRec89[2] = this.fRec89[1];
			this.fRec89[1] = this.fRec89[0];
			this.fRec88[2] = this.fRec88[1];
			this.fRec88[1] = this.fRec88[0];
			this.fRec87[2] = this.fRec87[1];
			this.fRec87[1] = this.fRec87[0];
			this.fRec86[2] = this.fRec86[1];
			this.fRec86[1] = this.fRec86[0];
			this.fRec85[2] = this.fRec85[1];
			this.fRec85[1] = this.fRec85[0];
			this.fRec84[2] = this.fRec84[1];
			this.fRec84[1] = this.fRec84[0];
			this.fRec83[1] = this.fRec83[0];
			this.fRec96[2] = this.fRec96[1];
			this.fRec96[1] = this.fRec96[0];
			this.fRec95[2] = this.fRec95[1];
			this.fRec95[1] = this.fRec95[0];
			this.fRec94[2] = this.fRec94[1];
			this.fRec94[1] = this.fRec94[0];
			this.fRec93[2] = this.fRec93[1];
			this.fRec93[1] = this.fRec93[0];
			this.fRec92[2] = this.fRec92[1];
			this.fRec92[1] = this.fRec92[0];
			this.fRec91[2] = this.fRec91[1];
			this.fRec91[1] = this.fRec91[0];
			this.fRec90[1] = this.fRec90[0];
			this.fRec103[2] = this.fRec103[1];
			this.fRec103[1] = this.fRec103[0];
			this.fRec102[2] = this.fRec102[1];
			this.fRec102[1] = this.fRec102[0];
			this.fRec101[2] = this.fRec101[1];
			this.fRec101[1] = this.fRec101[0];
			this.fRec100[2] = this.fRec100[1];
			this.fRec100[1] = this.fRec100[0];
			this.fRec99[2] = this.fRec99[1];
			this.fRec99[1] = this.fRec99[0];
			this.fRec98[2] = this.fRec98[1];
			this.fRec98[1] = this.fRec98[0];
			this.fRec97[1] = this.fRec97[0];
			this.fRec110[2] = this.fRec110[1];
			this.fRec110[1] = this.fRec110[0];
			this.fRec109[2] = this.fRec109[1];
			this.fRec109[1] = this.fRec109[0];
			this.fRec108[2] = this.fRec108[1];
			this.fRec108[1] = this.fRec108[0];
			this.fRec107[2] = this.fRec107[1];
			this.fRec107[1] = this.fRec107[0];
			this.fRec106[2] = this.fRec106[1];
			this.fRec106[1] = this.fRec106[0];
			this.fRec105[2] = this.fRec105[1];
			this.fRec105[1] = this.fRec105[0];
			this.fRec104[1] = this.fRec104[0];
			this.fRec117[2] = this.fRec117[1];
			this.fRec117[1] = this.fRec117[0];
			this.fRec116[2] = this.fRec116[1];
			this.fRec116[1] = this.fRec116[0];
			this.fRec115[2] = this.fRec115[1];
			this.fRec115[1] = this.fRec115[0];
			this.fRec114[2] = this.fRec114[1];
			this.fRec114[1] = this.fRec114[0];
			this.fRec113[2] = this.fRec113[1];
			this.fRec113[1] = this.fRec113[0];
			this.fRec112[2] = this.fRec112[1];
			this.fRec112[1] = this.fRec112[0];
			this.fRec111[1] = this.fRec111[0];
			this.fRec121[2] = this.fRec121[1];
			this.fRec121[1] = this.fRec121[0];
			this.fRec120[2] = this.fRec120[1];
			this.fRec120[1] = this.fRec120[0];
			this.fRec119[2] = this.fRec119[1];
			this.fRec119[1] = this.fRec119[0];
			this.fRec118[1] = this.fRec118[0];
			
		}
		
	}
	
}

