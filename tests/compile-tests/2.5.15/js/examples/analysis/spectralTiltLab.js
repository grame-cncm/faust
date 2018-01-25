
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower9_f = function(value) {
	return ((((((((value * value) * value) * value) * value) * value) * value) * value) * value);
	
}
this.mydsp_faustpower8_f = function(value) {
	return (((((((value * value) * value) * value) * value) * value) * value) * value);
	
}
this.mydsp_faustpower7_f = function(value) {
	return ((((((value * value) * value) * value) * value) * value) * value);
	
}
this.mydsp_faustpower6_f = function(value) {
	return (((((value * value) * value) * value) * value) * value);
	
}
this.mydsp_faustpower5_f = function(value) {
	return ((((value * value) * value) * value) * value);
	
}
this.mydsp_faustpower4_f = function(value) {
	return (((value * value) * value) * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
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
	this.fConst14;
	this.fConst15;
	this.fConst16;
	this.fConst17;
	this.fConst18;
	this.fConst19;
	this.fConst20;
	this.fConst21;
	this.fConst22;
	this.fConst23;
	this.fConst24;
	this.fConst25;
	this.fConst26;
	this.fConst27;
	this.fConst28;
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
	this.fConst50;
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fConst54;
	this.fConst55;
	this.fConst56;
	this.fConst57;
	this.fConst58;
	this.fConst59;
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fConst66;
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
	this.fConst88;
	this.fConst89;
	this.fConst90;
	this.fCheckbox0;
	this.fConst91;
	this.fHslider2;
	this.fHslider3;
	this.fHslider4;
	this.fConst92;
	this.iVec0 = new Int32Array(4);
	this.fVslider0;
	this.fRec35 = new Float32Array(2);
	this.fCheckbox1;
	this.fCheckbox2;
	this.fEntry0;
	this.fConst93;
	this.fVslider1;
	this.fVslider2;
	this.fRec37 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec36 = new Float32Array(2);
	this.fConst94;
	this.fVec2 = new Float32Array(2);
	this.fConst95;
	this.fVec3 = new Float32Array(2);
	this.fVec4 = new Float32Array(2);
	this.fConst96;
	this.fVec5 = new Float32Array(2);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2);
	this.fVslider3;
	this.fVec8 = new Float32Array(2);
	this.fRec38 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec39 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fCheckbox3;
	this.iRec40 = new Int32Array(2);
	this.fRec41 = new Float32Array(4);
	this.fVec22 = new Float32Array(2);
	this.fRec34 = new Float32Array(2);
	this.fVec23 = new Float32Array(2);
	this.fRec33 = new Float32Array(2);
	this.fVec24 = new Float32Array(2);
	this.fRec32 = new Float32Array(2);
	this.fVec25 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fVec26 = new Float32Array(2);
	this.fRec30 = new Float32Array(2);
	this.fVec27 = new Float32Array(2);
	this.fRec29 = new Float32Array(2);
	this.fVec28 = new Float32Array(2);
	this.fRec28 = new Float32Array(2);
	this.fVec29 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fVec30 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fVec31 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fConst97;
	this.fConst98;
	this.fRec24 = new Float32Array(3);
	this.fConst99;
	this.fConst100;
	this.fConst101;
	this.fRec23 = new Float32Array(3);
	this.fConst102;
	this.fConst103;
	this.fConst104;
	this.fRec22 = new Float32Array(3);
	this.fConst105;
	this.fConst106;
	this.fConst107;
	this.fRec21 = new Float32Array(3);
	this.fConst108;
	this.fConst109;
	this.fConst110;
	this.fRec20 = new Float32Array(3);
	this.fConst111;
	this.fConst112;
	this.fConst113;
	this.fRec19 = new Float32Array(3);
	this.fConst114;
	this.fConst115;
	this.fConst116;
	this.fRec18 = new Float32Array(3);
	this.fConst117;
	this.fConst118;
	this.fConst119;
	this.fRec17 = new Float32Array(3);
	this.fConst120;
	this.fConst121;
	this.fConst122;
	this.fRec16 = new Float32Array(3);
	this.fConst123;
	this.fConst124;
	this.fConst125;
	this.fRec15 = new Float32Array(3);
	this.fConst126;
	this.fConst127;
	this.fConst128;
	this.fRec14 = new Float32Array(3);
	this.fConst129;
	this.fConst130;
	this.fConst131;
	this.fRec13 = new Float32Array(3);
	this.fConst132;
	this.fConst133;
	this.fConst134;
	this.fRec12 = new Float32Array(3);
	this.fConst135;
	this.fConst136;
	this.fConst137;
	this.fRec11 = new Float32Array(3);
	this.fConst138;
	this.fConst139;
	this.fConst140;
	this.fRec10 = new Float32Array(3);
	this.fConst141;
	this.fConst142;
	this.fConst143;
	this.fRec9 = new Float32Array(3);
	this.fConst144;
	this.fConst145;
	this.fConst146;
	this.fRec8 = new Float32Array(3);
	this.fConst147;
	this.fConst148;
	this.fConst149;
	this.fRec7 = new Float32Array(3);
	this.fConst150;
	this.fConst151;
	this.fConst152;
	this.fRec6 = new Float32Array(3);
	this.fConst153;
	this.fConst154;
	this.fConst155;
	this.fRec5 = new Float32Array(3);
	this.fConst156;
	this.fConst157;
	this.fConst158;
	this.fRec4 = new Float32Array(3);
	this.fConst159;
	this.fConst160;
	this.fConst161;
	this.fConst162;
	this.fRec3 = new Float32Array(3);
	this.fConst163;
	this.fConst164;
	this.fConst165;
	this.fRec2 = new Float32Array(3);
	this.fConst166;
	this.fConst167;
	this.fConst168;
	this.fRec1 = new Float32Array(3);
	this.fConst169;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.fConst170;
	this.fConst171;
	this.fConst172;
	this.fConst173;
	this.fConst174;
	this.fConst175;
	this.fConst176;
	this.fConst177;
	this.fConst178;
	this.fConst179;
	this.fConst180;
	this.fRec45 = new Float32Array(3);
	this.fConst181;
	this.fConst182;
	this.fConst183;
	this.fRec44 = new Float32Array(3);
	this.fConst184;
	this.fConst185;
	this.fConst186;
	this.fRec43 = new Float32Array(3);
	this.fConst187;
	this.fRec42 = new Float32Array(2);
	this.fVbargraph1;
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
	this.fRec49 = new Float32Array(3);
	this.fConst199;
	this.fConst200;
	this.fConst201;
	this.fRec48 = new Float32Array(3);
	this.fConst202;
	this.fConst203;
	this.fConst204;
	this.fRec47 = new Float32Array(3);
	this.fConst205;
	this.fRec46 = new Float32Array(2);
	this.fVbargraph2;
	this.fConst206;
	this.fConst207;
	this.fConst208;
	this.fConst209;
	this.fConst210;
	this.fConst211;
	this.fConst212;
	this.fConst213;
	this.fConst214;
	this.fConst215;
	this.fConst216;
	this.fRec53 = new Float32Array(3);
	this.fConst217;
	this.fConst218;
	this.fConst219;
	this.fRec52 = new Float32Array(3);
	this.fConst220;
	this.fConst221;
	this.fConst222;
	this.fRec51 = new Float32Array(3);
	this.fConst223;
	this.fRec50 = new Float32Array(2);
	this.fVbargraph3;
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
	this.fRec57 = new Float32Array(3);
	this.fConst235;
	this.fConst236;
	this.fConst237;
	this.fRec56 = new Float32Array(3);
	this.fConst238;
	this.fConst239;
	this.fConst240;
	this.fRec55 = new Float32Array(3);
	this.fConst241;
	this.fRec54 = new Float32Array(2);
	this.fVbargraph4;
	this.fConst242;
	this.fConst243;
	this.fConst244;
	this.fConst245;
	this.fConst246;
	this.fConst247;
	this.fConst248;
	this.fConst249;
	this.fConst250;
	this.fConst251;
	this.fConst252;
	this.fRec61 = new Float32Array(3);
	this.fConst253;
	this.fConst254;
	this.fConst255;
	this.fRec60 = new Float32Array(3);
	this.fConst256;
	this.fConst257;
	this.fConst258;
	this.fRec59 = new Float32Array(3);
	this.fConst259;
	this.fRec58 = new Float32Array(2);
	this.fVbargraph5;
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
	this.fRec65 = new Float32Array(3);
	this.fConst271;
	this.fConst272;
	this.fConst273;
	this.fRec64 = new Float32Array(3);
	this.fConst274;
	this.fConst275;
	this.fConst276;
	this.fRec63 = new Float32Array(3);
	this.fConst277;
	this.fRec62 = new Float32Array(2);
	this.fVbargraph6;
	this.fConst278;
	this.fConst279;
	this.fConst280;
	this.fConst281;
	this.fConst282;
	this.fConst283;
	this.fConst284;
	this.fConst285;
	this.fConst286;
	this.fConst287;
	this.fConst288;
	this.fRec69 = new Float32Array(3);
	this.fConst289;
	this.fConst290;
	this.fConst291;
	this.fRec68 = new Float32Array(3);
	this.fConst292;
	this.fConst293;
	this.fConst294;
	this.fRec67 = new Float32Array(3);
	this.fConst295;
	this.fRec66 = new Float32Array(2);
	this.fVbargraph7;
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
	this.fConst316;
	this.fRec76 = new Float32Array(3);
	this.fConst317;
	this.fConst318;
	this.fConst319;
	this.fRec75 = new Float32Array(3);
	this.fConst320;
	this.fConst321;
	this.fConst322;
	this.fRec74 = new Float32Array(3);
	this.fConst323;
	this.fConst324;
	this.fConst325;
	this.fConst326;
	this.fRec73 = new Float32Array(3);
	this.fConst327;
	this.fConst328;
	this.fConst329;
	this.fRec72 = new Float32Array(3);
	this.fConst330;
	this.fConst331;
	this.fConst332;
	this.fRec71 = new Float32Array(3);
	this.fConst333;
	this.fRec70 = new Float32Array(2);
	this.fVbargraph8;
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
	this.fConst354;
	this.fRec83 = new Float32Array(3);
	this.fConst355;
	this.fConst356;
	this.fConst357;
	this.fRec82 = new Float32Array(3);
	this.fConst358;
	this.fConst359;
	this.fConst360;
	this.fRec81 = new Float32Array(3);
	this.fConst361;
	this.fConst362;
	this.fConst363;
	this.fConst364;
	this.fRec80 = new Float32Array(3);
	this.fConst365;
	this.fConst366;
	this.fConst367;
	this.fRec79 = new Float32Array(3);
	this.fConst368;
	this.fConst369;
	this.fConst370;
	this.fRec78 = new Float32Array(3);
	this.fConst371;
	this.fRec77 = new Float32Array(2);
	this.fVbargraph9;
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
	this.fConst392;
	this.fRec90 = new Float32Array(3);
	this.fConst393;
	this.fConst394;
	this.fConst395;
	this.fRec89 = new Float32Array(3);
	this.fConst396;
	this.fConst397;
	this.fConst398;
	this.fRec88 = new Float32Array(3);
	this.fConst399;
	this.fConst400;
	this.fConst401;
	this.fConst402;
	this.fRec87 = new Float32Array(3);
	this.fConst403;
	this.fConst404;
	this.fConst405;
	this.fRec86 = new Float32Array(3);
	this.fConst406;
	this.fConst407;
	this.fConst408;
	this.fRec85 = new Float32Array(3);
	this.fConst409;
	this.fRec84 = new Float32Array(2);
	this.fVbargraph10;
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
	this.fConst430;
	this.fRec97 = new Float32Array(3);
	this.fConst431;
	this.fConst432;
	this.fConst433;
	this.fRec96 = new Float32Array(3);
	this.fConst434;
	this.fConst435;
	this.fConst436;
	this.fRec95 = new Float32Array(3);
	this.fConst437;
	this.fConst438;
	this.fConst439;
	this.fConst440;
	this.fRec94 = new Float32Array(3);
	this.fConst441;
	this.fConst442;
	this.fConst443;
	this.fRec93 = new Float32Array(3);
	this.fConst444;
	this.fConst445;
	this.fConst446;
	this.fRec92 = new Float32Array(3);
	this.fConst447;
	this.fRec91 = new Float32Array(2);
	this.fVbargraph11;
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
	this.fConst468;
	this.fRec104 = new Float32Array(3);
	this.fConst469;
	this.fConst470;
	this.fConst471;
	this.fRec103 = new Float32Array(3);
	this.fConst472;
	this.fConst473;
	this.fConst474;
	this.fRec102 = new Float32Array(3);
	this.fConst475;
	this.fConst476;
	this.fConst477;
	this.fConst478;
	this.fRec101 = new Float32Array(3);
	this.fConst479;
	this.fConst480;
	this.fConst481;
	this.fRec100 = new Float32Array(3);
	this.fConst482;
	this.fConst483;
	this.fConst484;
	this.fRec99 = new Float32Array(3);
	this.fConst485;
	this.fRec98 = new Float32Array(2);
	this.fVbargraph12;
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
	this.fConst506;
	this.fRec111 = new Float32Array(3);
	this.fConst507;
	this.fConst508;
	this.fConst509;
	this.fRec110 = new Float32Array(3);
	this.fConst510;
	this.fConst511;
	this.fConst512;
	this.fRec109 = new Float32Array(3);
	this.fConst513;
	this.fConst514;
	this.fConst515;
	this.fConst516;
	this.fRec108 = new Float32Array(3);
	this.fConst517;
	this.fConst518;
	this.fConst519;
	this.fRec107 = new Float32Array(3);
	this.fConst520;
	this.fConst521;
	this.fConst522;
	this.fRec106 = new Float32Array(3);
	this.fConst523;
	this.fRec105 = new Float32Array(2);
	this.fVbargraph13;
	this.fConst524;
	this.fConst525;
	this.fConst526;
	this.fConst527;
	this.fConst528;
	this.fConst529;
	this.fConst530;
	this.fConst531;
	this.fConst532;
	this.fRec115 = new Float32Array(3);
	this.fConst533;
	this.fConst534;
	this.fConst535;
	this.fRec114 = new Float32Array(3);
	this.fConst536;
	this.fConst537;
	this.fConst538;
	this.fRec113 = new Float32Array(3);
	this.fConst539;
	this.fRec112 = new Float32Array(2);
	this.fVbargraph14;
	
	this.metadata = function(m) { 
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

	this.getNumInputs = function() {
		return 1;
		
	}
	this.getNumOutputs = function() {
		return 1;
		
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
		this.fConst2 = Math.tan((1979.08 / this.fConst0));
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
		this.fConst14 = Math.tan((3141.59 / this.fConst0));
		this.fConst15 = (1 / this.fConst14);
		this.fConst16 = (1 / (((this.fConst15 + 0.168405) / this.fConst14) + 1.06936));
		this.fConst17 = mydsp_faustpower2_f(this.fConst14);
		this.fConst18 = (1 / this.fConst17);
		this.fConst19 = (2 * (53.5362 - this.fConst18));
		this.fConst20 = (1 / (((this.fConst15 + 0.512479) / this.fConst14) + 0.689621));
		this.fConst21 = (2 * (7.62173 - this.fConst18));
		this.fConst22 = (1 / (((this.fConst15 + 0.782413) / this.fConst14) + 0.245292));
		this.fConst23 = (0.0001 / this.fConst17);
		this.fConst24 = (2 * (0.000433227 - this.fConst23));
		this.fConst25 = Math.tan((4986.97 / this.fConst0));
		this.fConst26 = (1 / this.fConst25);
		this.fConst27 = (1 / (((this.fConst26 + 0.168405) / this.fConst25) + 1.06936));
		this.fConst28 = mydsp_faustpower2_f(this.fConst25);
		this.fConst29 = (1 / this.fConst28);
		this.fConst30 = (2 * (53.5362 - this.fConst29));
		this.fConst31 = (1 / (((this.fConst26 + 0.512479) / this.fConst25) + 0.689621));
		this.fConst32 = (2 * (7.62173 - this.fConst29));
		this.fConst33 = (1 / (((this.fConst26 + 0.782413) / this.fConst25) + 0.245292));
		this.fConst34 = (0.0001 / this.fConst28);
		this.fConst35 = (2 * (0.000433227 - this.fConst34));
		this.fConst36 = Math.tan((7916.32 / this.fConst0));
		this.fConst37 = (1 / this.fConst36);
		this.fConst38 = (1 / (((this.fConst37 + 0.168405) / this.fConst36) + 1.06936));
		this.fConst39 = mydsp_faustpower2_f(this.fConst36);
		this.fConst40 = (1 / this.fConst39);
		this.fConst41 = (2 * (53.5362 - this.fConst40));
		this.fConst42 = (1 / (((this.fConst37 + 0.512479) / this.fConst36) + 0.689621));
		this.fConst43 = (2 * (7.62173 - this.fConst40));
		this.fConst44 = (1 / (((this.fConst37 + 0.782413) / this.fConst36) + 0.245292));
		this.fConst45 = (0.0001 / this.fConst39);
		this.fConst46 = (2 * (0.000433227 - this.fConst45));
		this.fConst47 = Math.tan((12566.4 / this.fConst0));
		this.fConst48 = (1 / this.fConst47);
		this.fConst49 = (1 / (((this.fConst48 + 0.168405) / this.fConst47) + 1.06936));
		this.fConst50 = mydsp_faustpower2_f(this.fConst47);
		this.fConst51 = (1 / this.fConst50);
		this.fConst52 = (2 * (53.5362 - this.fConst51));
		this.fConst53 = (1 / (((this.fConst48 + 0.512479) / this.fConst47) + 0.689621));
		this.fConst54 = (2 * (7.62173 - this.fConst51));
		this.fConst55 = (1 / (((this.fConst48 + 0.782413) / this.fConst47) + 0.245292));
		this.fConst56 = (0.0001 / this.fConst50);
		this.fConst57 = (2 * (0.000433227 - this.fConst56));
		this.fConst58 = Math.tan((19947.9 / this.fConst0));
		this.fConst59 = (1 / this.fConst58);
		this.fConst60 = (1 / (((this.fConst59 + 0.168405) / this.fConst58) + 1.06936));
		this.fConst61 = mydsp_faustpower2_f(this.fConst58);
		this.fConst62 = (1 / this.fConst61);
		this.fConst63 = (2 * (53.5362 - this.fConst62));
		this.fConst64 = (1 / (((this.fConst59 + 0.512479) / this.fConst58) + 0.689621));
		this.fConst65 = (2 * (7.62173 - this.fConst62));
		this.fConst66 = (1 / (((this.fConst59 + 0.782413) / this.fConst58) + 0.245292));
		this.fConst67 = (0.0001 / this.fConst61);
		this.fConst68 = (2 * (0.000433227 - this.fConst67));
		this.fConst69 = Math.tan((31665.3 / this.fConst0));
		this.fConst70 = (1 / this.fConst69);
		this.fConst71 = (1 / (((this.fConst70 + 0.168405) / this.fConst69) + 1.06936));
		this.fConst72 = mydsp_faustpower2_f(this.fConst69);
		this.fConst73 = (1 / this.fConst72);
		this.fConst74 = (2 * (53.5362 - this.fConst73));
		this.fConst75 = (1 / (((this.fConst70 + 0.512479) / this.fConst69) + 0.689621));
		this.fConst76 = (2 * (7.62173 - this.fConst73));
		this.fConst77 = (1 / (((this.fConst70 + 0.782413) / this.fConst69) + 0.245292));
		this.fConst78 = (0.0001 / this.fConst72);
		this.fConst79 = (2 * (0.000433227 - this.fConst78));
		this.fConst80 = Math.tan((50265.5 / this.fConst0));
		this.fConst81 = (1 / this.fConst80);
		this.fConst82 = (1 / (((this.fConst81 + 0.168405) / this.fConst80) + 1.06936));
		this.fConst83 = mydsp_faustpower2_f(this.fConst80);
		this.fConst84 = (1 / this.fConst83);
		this.fConst85 = (2 * (53.5362 - this.fConst84));
		this.fConst86 = (1 / (((this.fConst81 + 0.512479) / this.fConst80) + 0.689621));
		this.fConst87 = (2 * (7.62173 - this.fConst84));
		this.fConst88 = (1 / (((this.fConst81 + 0.782413) / this.fConst80) + 0.245292));
		this.fConst89 = (0.0001 / this.fConst83);
		this.fConst90 = (2 * (0.000433227 - this.fConst89));
		this.fConst91 = (3.14159 / this.fConst0);
		this.fConst92 = (1 / Math.tan((0.5 / this.fConst0)));
		this.fConst93 = (1 / this.fConst0);
		this.fConst94 = (0.25 * this.fConst0);
		this.fConst95 = (0.0416667 * mydsp_faustpower2_f(this.fConst0));
		this.fConst96 = (0.00520833 * mydsp_faustpower3_f(this.fConst0));
		this.fConst97 = (((this.fConst81 + -0.782413) / this.fConst80) + 0.245292);
		this.fConst98 = (2 * (0.245292 - this.fConst84));
		this.fConst99 = (this.fConst89 + 0.000433227);
		this.fConst100 = (((this.fConst81 + -0.512479) / this.fConst80) + 0.689621);
		this.fConst101 = (2 * (0.689621 - this.fConst84));
		this.fConst102 = (this.fConst84 + 7.62173);
		this.fConst103 = (((this.fConst81 + -0.168405) / this.fConst80) + 1.06936);
		this.fConst104 = (2 * (1.06936 - this.fConst84));
		this.fConst105 = (this.fConst84 + 53.5362);
		this.fConst106 = (((this.fConst70 + -0.782413) / this.fConst69) + 0.245292);
		this.fConst107 = (2 * (0.245292 - this.fConst73));
		this.fConst108 = (this.fConst78 + 0.000433227);
		this.fConst109 = (((this.fConst70 + -0.512479) / this.fConst69) + 0.689621);
		this.fConst110 = (2 * (0.689621 - this.fConst73));
		this.fConst111 = (this.fConst73 + 7.62173);
		this.fConst112 = (((this.fConst70 + -0.168405) / this.fConst69) + 1.06936);
		this.fConst113 = (2 * (1.06936 - this.fConst73));
		this.fConst114 = (this.fConst73 + 53.5362);
		this.fConst115 = (((this.fConst59 + -0.782413) / this.fConst58) + 0.245292);
		this.fConst116 = (2 * (0.245292 - this.fConst62));
		this.fConst117 = (this.fConst67 + 0.000433227);
		this.fConst118 = (((this.fConst59 + -0.512479) / this.fConst58) + 0.689621);
		this.fConst119 = (2 * (0.689621 - this.fConst62));
		this.fConst120 = (this.fConst62 + 7.62173);
		this.fConst121 = (((this.fConst59 + -0.168405) / this.fConst58) + 1.06936);
		this.fConst122 = (2 * (1.06936 - this.fConst62));
		this.fConst123 = (this.fConst62 + 53.5362);
		this.fConst124 = (((this.fConst48 + -0.782413) / this.fConst47) + 0.245292);
		this.fConst125 = (2 * (0.245292 - this.fConst51));
		this.fConst126 = (this.fConst56 + 0.000433227);
		this.fConst127 = (((this.fConst48 + -0.512479) / this.fConst47) + 0.689621);
		this.fConst128 = (2 * (0.689621 - this.fConst51));
		this.fConst129 = (this.fConst51 + 7.62173);
		this.fConst130 = (((this.fConst48 + -0.168405) / this.fConst47) + 1.06936);
		this.fConst131 = (2 * (1.06936 - this.fConst51));
		this.fConst132 = (this.fConst51 + 53.5362);
		this.fConst133 = (((this.fConst37 + -0.782413) / this.fConst36) + 0.245292);
		this.fConst134 = (2 * (0.245292 - this.fConst40));
		this.fConst135 = (this.fConst45 + 0.000433227);
		this.fConst136 = (((this.fConst37 + -0.512479) / this.fConst36) + 0.689621);
		this.fConst137 = (2 * (0.689621 - this.fConst40));
		this.fConst138 = (this.fConst40 + 7.62173);
		this.fConst139 = (((this.fConst37 + -0.168405) / this.fConst36) + 1.06936);
		this.fConst140 = (2 * (1.06936 - this.fConst40));
		this.fConst141 = (this.fConst40 + 53.5362);
		this.fConst142 = (((this.fConst26 + -0.782413) / this.fConst25) + 0.245292);
		this.fConst143 = (2 * (0.245292 - this.fConst29));
		this.fConst144 = (this.fConst34 + 0.000433227);
		this.fConst145 = (((this.fConst26 + -0.512479) / this.fConst25) + 0.689621);
		this.fConst146 = (2 * (0.689621 - this.fConst29));
		this.fConst147 = (this.fConst29 + 7.62173);
		this.fConst148 = (((this.fConst26 + -0.168405) / this.fConst25) + 1.06936);
		this.fConst149 = (2 * (1.06936 - this.fConst29));
		this.fConst150 = (this.fConst29 + 53.5362);
		this.fConst151 = (((this.fConst15 + -0.782413) / this.fConst14) + 0.245292);
		this.fConst152 = (2 * (0.245292 - this.fConst18));
		this.fConst153 = (this.fConst23 + 0.000433227);
		this.fConst154 = (((this.fConst15 + -0.512479) / this.fConst14) + 0.689621);
		this.fConst155 = (2 * (0.689621 - this.fConst18));
		this.fConst156 = (this.fConst18 + 7.62173);
		this.fConst157 = (((this.fConst15 + -0.168405) / this.fConst14) + 1.06936);
		this.fConst158 = (2 * (1.06936 - this.fConst18));
		this.fConst159 = (this.fConst18 + 53.5362);
		this.fConst160 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst161 = (1 / this.fConst5);
		this.fConst162 = (2 * (4.07678 - this.fConst161));
		this.fConst163 = (this.fConst12 + 0.000407678);
		this.fConst164 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst165 = (2 * (1.45007 - this.fConst161));
		this.fConst166 = (this.fConst9 + 1.45007);
		this.fConst167 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst168 = (2 * (0.93514 - this.fConst161));
		this.fConst169 = (this.fConst6 + 0.93514);
		this.fConst170 = (1 / (((this.fConst81 + 0.157482) / this.fConst80) + 0.93514));
		this.fConst171 = (50.0638 / this.fConst83);
		this.fConst172 = (2 * (0.93514 - this.fConst171));
		this.fConst173 = (1 / (((this.fConst81 + 0.74313) / this.fConst80) + 1.45007));
		this.fConst174 = (11.0521 / this.fConst83);
		this.fConst175 = (2 * (1.45007 - this.fConst174));
		this.fConst176 = (1 / (((this.fConst81 + 3.18973) / this.fConst80) + 4.07678));
		this.fConst177 = (0.00176617 / this.fConst83);
		this.fConst178 = (2 * (0.000407678 - this.fConst177));
		this.fConst179 = (((this.fConst81 + -3.18973) / this.fConst80) + 4.07678);
		this.fConst180 = (2 * (4.07678 - this.fConst84));
		this.fConst181 = (this.fConst177 + 0.000407678);
		this.fConst182 = (((this.fConst81 + -0.74313) / this.fConst80) + 1.45007);
		this.fConst183 = (2 * (1.45007 - this.fConst84));
		this.fConst184 = (this.fConst174 + 1.45007);
		this.fConst185 = (((this.fConst81 + -0.157482) / this.fConst80) + 0.93514);
		this.fConst186 = (2 * (0.93514 - this.fConst84));
		this.fConst187 = (this.fConst171 + 0.93514);
		this.fConst188 = (1 / (((this.fConst70 + 0.157482) / this.fConst69) + 0.93514));
		this.fConst189 = (50.0638 / this.fConst72);
		this.fConst190 = (2 * (0.93514 - this.fConst189));
		this.fConst191 = (1 / (((this.fConst70 + 0.74313) / this.fConst69) + 1.45007));
		this.fConst192 = (11.0521 / this.fConst72);
		this.fConst193 = (2 * (1.45007 - this.fConst192));
		this.fConst194 = (1 / (((this.fConst70 + 3.18973) / this.fConst69) + 4.07678));
		this.fConst195 = (0.00176617 / this.fConst72);
		this.fConst196 = (2 * (0.000407678 - this.fConst195));
		this.fConst197 = (((this.fConst70 + -3.18973) / this.fConst69) + 4.07678);
		this.fConst198 = (2 * (4.07678 - this.fConst73));
		this.fConst199 = (this.fConst195 + 0.000407678);
		this.fConst200 = (((this.fConst70 + -0.74313) / this.fConst69) + 1.45007);
		this.fConst201 = (2 * (1.45007 - this.fConst73));
		this.fConst202 = (this.fConst192 + 1.45007);
		this.fConst203 = (((this.fConst70 + -0.157482) / this.fConst69) + 0.93514);
		this.fConst204 = (2 * (0.93514 - this.fConst73));
		this.fConst205 = (this.fConst189 + 0.93514);
		this.fConst206 = (1 / (((this.fConst59 + 0.157482) / this.fConst58) + 0.93514));
		this.fConst207 = (50.0638 / this.fConst61);
		this.fConst208 = (2 * (0.93514 - this.fConst207));
		this.fConst209 = (1 / (((this.fConst59 + 0.74313) / this.fConst58) + 1.45007));
		this.fConst210 = (11.0521 / this.fConst61);
		this.fConst211 = (2 * (1.45007 - this.fConst210));
		this.fConst212 = (1 / (((this.fConst59 + 3.18973) / this.fConst58) + 4.07678));
		this.fConst213 = (0.00176617 / this.fConst61);
		this.fConst214 = (2 * (0.000407678 - this.fConst213));
		this.fConst215 = (((this.fConst59 + -3.18973) / this.fConst58) + 4.07678);
		this.fConst216 = (2 * (4.07678 - this.fConst62));
		this.fConst217 = (this.fConst213 + 0.000407678);
		this.fConst218 = (((this.fConst59 + -0.74313) / this.fConst58) + 1.45007);
		this.fConst219 = (2 * (1.45007 - this.fConst62));
		this.fConst220 = (this.fConst210 + 1.45007);
		this.fConst221 = (((this.fConst59 + -0.157482) / this.fConst58) + 0.93514);
		this.fConst222 = (2 * (0.93514 - this.fConst62));
		this.fConst223 = (this.fConst207 + 0.93514);
		this.fConst224 = (1 / (((this.fConst48 + 0.157482) / this.fConst47) + 0.93514));
		this.fConst225 = (50.0638 / this.fConst50);
		this.fConst226 = (2 * (0.93514 - this.fConst225));
		this.fConst227 = (1 / (((this.fConst48 + 0.74313) / this.fConst47) + 1.45007));
		this.fConst228 = (11.0521 / this.fConst50);
		this.fConst229 = (2 * (1.45007 - this.fConst228));
		this.fConst230 = (1 / (((this.fConst48 + 3.18973) / this.fConst47) + 4.07678));
		this.fConst231 = (0.00176617 / this.fConst50);
		this.fConst232 = (2 * (0.000407678 - this.fConst231));
		this.fConst233 = (((this.fConst48 + -3.18973) / this.fConst47) + 4.07678);
		this.fConst234 = (2 * (4.07678 - this.fConst51));
		this.fConst235 = (this.fConst231 + 0.000407678);
		this.fConst236 = (((this.fConst48 + -0.74313) / this.fConst47) + 1.45007);
		this.fConst237 = (2 * (1.45007 - this.fConst51));
		this.fConst238 = (this.fConst228 + 1.45007);
		this.fConst239 = (((this.fConst48 + -0.157482) / this.fConst47) + 0.93514);
		this.fConst240 = (2 * (0.93514 - this.fConst51));
		this.fConst241 = (this.fConst225 + 0.93514);
		this.fConst242 = (1 / (((this.fConst37 + 0.157482) / this.fConst36) + 0.93514));
		this.fConst243 = (50.0638 / this.fConst39);
		this.fConst244 = (2 * (0.93514 - this.fConst243));
		this.fConst245 = (1 / (((this.fConst37 + 0.74313) / this.fConst36) + 1.45007));
		this.fConst246 = (11.0521 / this.fConst39);
		this.fConst247 = (2 * (1.45007 - this.fConst246));
		this.fConst248 = (1 / (((this.fConst37 + 3.18973) / this.fConst36) + 4.07678));
		this.fConst249 = (0.00176617 / this.fConst39);
		this.fConst250 = (2 * (0.000407678 - this.fConst249));
		this.fConst251 = (((this.fConst37 + -3.18973) / this.fConst36) + 4.07678);
		this.fConst252 = (2 * (4.07678 - this.fConst40));
		this.fConst253 = (this.fConst249 + 0.000407678);
		this.fConst254 = (((this.fConst37 + -0.74313) / this.fConst36) + 1.45007);
		this.fConst255 = (2 * (1.45007 - this.fConst40));
		this.fConst256 = (this.fConst246 + 1.45007);
		this.fConst257 = (((this.fConst37 + -0.157482) / this.fConst36) + 0.93514);
		this.fConst258 = (2 * (0.93514 - this.fConst40));
		this.fConst259 = (this.fConst243 + 0.93514);
		this.fConst260 = (1 / (((this.fConst26 + 0.157482) / this.fConst25) + 0.93514));
		this.fConst261 = (50.0638 / this.fConst28);
		this.fConst262 = (2 * (0.93514 - this.fConst261));
		this.fConst263 = (1 / (((this.fConst26 + 0.74313) / this.fConst25) + 1.45007));
		this.fConst264 = (11.0521 / this.fConst28);
		this.fConst265 = (2 * (1.45007 - this.fConst264));
		this.fConst266 = (1 / (((this.fConst26 + 3.18973) / this.fConst25) + 4.07678));
		this.fConst267 = (0.00176617 / this.fConst28);
		this.fConst268 = (2 * (0.000407678 - this.fConst267));
		this.fConst269 = (((this.fConst26 + -3.18973) / this.fConst25) + 4.07678);
		this.fConst270 = (2 * (4.07678 - this.fConst29));
		this.fConst271 = (this.fConst267 + 0.000407678);
		this.fConst272 = (((this.fConst26 + -0.74313) / this.fConst25) + 1.45007);
		this.fConst273 = (2 * (1.45007 - this.fConst29));
		this.fConst274 = (this.fConst264 + 1.45007);
		this.fConst275 = (((this.fConst26 + -0.157482) / this.fConst25) + 0.93514);
		this.fConst276 = (2 * (0.93514 - this.fConst29));
		this.fConst277 = (this.fConst261 + 0.93514);
		this.fConst278 = (1 / (((this.fConst15 + 0.157482) / this.fConst14) + 0.93514));
		this.fConst279 = (50.0638 / this.fConst17);
		this.fConst280 = (2 * (0.93514 - this.fConst279));
		this.fConst281 = (1 / (((this.fConst15 + 0.74313) / this.fConst14) + 1.45007));
		this.fConst282 = (11.0521 / this.fConst17);
		this.fConst283 = (2 * (1.45007 - this.fConst282));
		this.fConst284 = (1 / (((this.fConst15 + 3.18973) / this.fConst14) + 4.07678));
		this.fConst285 = (0.00176617 / this.fConst17);
		this.fConst286 = (2 * (0.000407678 - this.fConst285));
		this.fConst287 = (((this.fConst15 + -3.18973) / this.fConst14) + 4.07678);
		this.fConst288 = (2 * (4.07678 - this.fConst18));
		this.fConst289 = (this.fConst285 + 0.000407678);
		this.fConst290 = (((this.fConst15 + -0.74313) / this.fConst14) + 1.45007);
		this.fConst291 = (2 * (1.45007 - this.fConst18));
		this.fConst292 = (this.fConst282 + 1.45007);
		this.fConst293 = (((this.fConst15 + -0.157482) / this.fConst14) + 0.93514);
		this.fConst294 = (2 * (0.93514 - this.fConst18));
		this.fConst295 = (this.fConst279 + 0.93514);
		this.fConst296 = Math.tan((1246.74 / this.fConst0));
		this.fConst297 = (1 / this.fConst296);
		this.fConst298 = (1 / (((this.fConst297 + 0.157482) / this.fConst296) + 0.93514));
		this.fConst299 = mydsp_faustpower2_f(this.fConst296);
		this.fConst300 = (50.0638 / this.fConst299);
		this.fConst301 = (2 * (0.93514 - this.fConst300));
		this.fConst302 = (1 / (((this.fConst297 + 0.74313) / this.fConst296) + 1.45007));
		this.fConst303 = (11.0521 / this.fConst299);
		this.fConst304 = (2 * (1.45007 - this.fConst303));
		this.fConst305 = (1 / (((this.fConst297 + 3.18973) / this.fConst296) + 4.07678));
		this.fConst306 = (0.00176617 / this.fConst299);
		this.fConst307 = (2 * (0.000407678 - this.fConst306));
		this.fConst308 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst309 = (2 * (53.5362 - this.fConst161));
		this.fConst310 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst311 = (2 * (7.62173 - this.fConst161));
		this.fConst312 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst313 = (0.0001 / this.fConst5);
		this.fConst314 = (2 * (0.000433227 - this.fConst313));
		this.fConst315 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst316 = (2 * (0.245292 - this.fConst161));
		this.fConst317 = (this.fConst313 + 0.000433227);
		this.fConst318 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst319 = (2 * (0.689621 - this.fConst161));
		this.fConst320 = (this.fConst161 + 7.62173);
		this.fConst321 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst322 = (2 * (1.06936 - this.fConst161));
		this.fConst323 = (this.fConst161 + 53.5362);
		this.fConst324 = (((this.fConst297 + -3.18973) / this.fConst296) + 4.07678);
		this.fConst325 = (1 / this.fConst299);
		this.fConst326 = (2 * (4.07678 - this.fConst325));
		this.fConst327 = (this.fConst306 + 0.000407678);
		this.fConst328 = (((this.fConst297 + -0.74313) / this.fConst296) + 1.45007);
		this.fConst329 = (2 * (1.45007 - this.fConst325));
		this.fConst330 = (this.fConst303 + 1.45007);
		this.fConst331 = (((this.fConst297 + -0.157482) / this.fConst296) + 0.93514);
		this.fConst332 = (2 * (0.93514 - this.fConst325));
		this.fConst333 = (this.fConst300 + 0.93514);
		this.fConst334 = Math.tan((785.398 / this.fConst0));
		this.fConst335 = (1 / this.fConst334);
		this.fConst336 = (1 / (((this.fConst335 + 0.157482) / this.fConst334) + 0.93514));
		this.fConst337 = mydsp_faustpower2_f(this.fConst334);
		this.fConst338 = (50.0638 / this.fConst337);
		this.fConst339 = (2 * (0.93514 - this.fConst338));
		this.fConst340 = (1 / (((this.fConst335 + 0.74313) / this.fConst334) + 1.45007));
		this.fConst341 = (11.0521 / this.fConst337);
		this.fConst342 = (2 * (1.45007 - this.fConst341));
		this.fConst343 = (1 / (((this.fConst335 + 3.18973) / this.fConst334) + 4.07678));
		this.fConst344 = (0.00176617 / this.fConst337);
		this.fConst345 = (2 * (0.000407678 - this.fConst344));
		this.fConst346 = (1 / (((this.fConst297 + 0.168405) / this.fConst296) + 1.06936));
		this.fConst347 = (2 * (53.5362 - this.fConst325));
		this.fConst348 = (1 / (((this.fConst297 + 0.512479) / this.fConst296) + 0.689621));
		this.fConst349 = (2 * (7.62173 - this.fConst325));
		this.fConst350 = (1 / (((this.fConst297 + 0.782413) / this.fConst296) + 0.245292));
		this.fConst351 = (0.0001 / this.fConst299);
		this.fConst352 = (2 * (0.000433227 - this.fConst351));
		this.fConst353 = (((this.fConst297 + -0.782413) / this.fConst296) + 0.245292);
		this.fConst354 = (2 * (0.245292 - this.fConst325));
		this.fConst355 = (this.fConst351 + 0.000433227);
		this.fConst356 = (((this.fConst297 + -0.512479) / this.fConst296) + 0.689621);
		this.fConst357 = (2 * (0.689621 - this.fConst325));
		this.fConst358 = (this.fConst325 + 7.62173);
		this.fConst359 = (((this.fConst297 + -0.168405) / this.fConst296) + 1.06936);
		this.fConst360 = (2 * (1.06936 - this.fConst325));
		this.fConst361 = (this.fConst325 + 53.5362);
		this.fConst362 = (((this.fConst335 + -3.18973) / this.fConst334) + 4.07678);
		this.fConst363 = (1 / this.fConst337);
		this.fConst364 = (2 * (4.07678 - this.fConst363));
		this.fConst365 = (this.fConst344 + 0.000407678);
		this.fConst366 = (((this.fConst335 + -0.74313) / this.fConst334) + 1.45007);
		this.fConst367 = (2 * (1.45007 - this.fConst363));
		this.fConst368 = (this.fConst341 + 1.45007);
		this.fConst369 = (((this.fConst335 + -0.157482) / this.fConst334) + 0.93514);
		this.fConst370 = (2 * (0.93514 - this.fConst363));
		this.fConst371 = (this.fConst338 + 0.93514);
		this.fConst372 = Math.tan((494.77 / this.fConst0));
		this.fConst373 = (1 / this.fConst372);
		this.fConst374 = (1 / (((this.fConst373 + 0.157482) / this.fConst372) + 0.93514));
		this.fConst375 = mydsp_faustpower2_f(this.fConst372);
		this.fConst376 = (50.0638 / this.fConst375);
		this.fConst377 = (2 * (0.93514 - this.fConst376));
		this.fConst378 = (1 / (((this.fConst373 + 0.74313) / this.fConst372) + 1.45007));
		this.fConst379 = (11.0521 / this.fConst375);
		this.fConst380 = (2 * (1.45007 - this.fConst379));
		this.fConst381 = (1 / (((this.fConst373 + 3.18973) / this.fConst372) + 4.07678));
		this.fConst382 = (0.00176617 / this.fConst375);
		this.fConst383 = (2 * (0.000407678 - this.fConst382));
		this.fConst384 = (1 / (((this.fConst335 + 0.168405) / this.fConst334) + 1.06936));
		this.fConst385 = (2 * (53.5362 - this.fConst363));
		this.fConst386 = (1 / (((this.fConst335 + 0.512479) / this.fConst334) + 0.689621));
		this.fConst387 = (2 * (7.62173 - this.fConst363));
		this.fConst388 = (1 / (((this.fConst335 + 0.782413) / this.fConst334) + 0.245292));
		this.fConst389 = (0.0001 / this.fConst337);
		this.fConst390 = (2 * (0.000433227 - this.fConst389));
		this.fConst391 = (((this.fConst335 + -0.782413) / this.fConst334) + 0.245292);
		this.fConst392 = (2 * (0.245292 - this.fConst363));
		this.fConst393 = (this.fConst389 + 0.000433227);
		this.fConst394 = (((this.fConst335 + -0.512479) / this.fConst334) + 0.689621);
		this.fConst395 = (2 * (0.689621 - this.fConst363));
		this.fConst396 = (this.fConst363 + 7.62173);
		this.fConst397 = (((this.fConst335 + -0.168405) / this.fConst334) + 1.06936);
		this.fConst398 = (2 * (1.06936 - this.fConst363));
		this.fConst399 = (this.fConst363 + 53.5362);
		this.fConst400 = (((this.fConst373 + -3.18973) / this.fConst372) + 4.07678);
		this.fConst401 = (1 / this.fConst375);
		this.fConst402 = (2 * (4.07678 - this.fConst401));
		this.fConst403 = (this.fConst382 + 0.000407678);
		this.fConst404 = (((this.fConst373 + -0.74313) / this.fConst372) + 1.45007);
		this.fConst405 = (2 * (1.45007 - this.fConst401));
		this.fConst406 = (this.fConst379 + 1.45007);
		this.fConst407 = (((this.fConst373 + -0.157482) / this.fConst372) + 0.93514);
		this.fConst408 = (2 * (0.93514 - this.fConst401));
		this.fConst409 = (this.fConst376 + 0.93514);
		this.fConst410 = Math.tan((311.685 / this.fConst0));
		this.fConst411 = (1 / this.fConst410);
		this.fConst412 = (1 / (((this.fConst411 + 0.157482) / this.fConst410) + 0.93514));
		this.fConst413 = mydsp_faustpower2_f(this.fConst410);
		this.fConst414 = (50.0638 / this.fConst413);
		this.fConst415 = (2 * (0.93514 - this.fConst414));
		this.fConst416 = (1 / (((this.fConst411 + 0.74313) / this.fConst410) + 1.45007));
		this.fConst417 = (11.0521 / this.fConst413);
		this.fConst418 = (2 * (1.45007 - this.fConst417));
		this.fConst419 = (1 / (((this.fConst411 + 3.18973) / this.fConst410) + 4.07678));
		this.fConst420 = (0.00176617 / this.fConst413);
		this.fConst421 = (2 * (0.000407678 - this.fConst420));
		this.fConst422 = (1 / (((this.fConst373 + 0.168405) / this.fConst372) + 1.06936));
		this.fConst423 = (2 * (53.5362 - this.fConst401));
		this.fConst424 = (1 / (((this.fConst373 + 0.512479) / this.fConst372) + 0.689621));
		this.fConst425 = (2 * (7.62173 - this.fConst401));
		this.fConst426 = (1 / (((this.fConst373 + 0.782413) / this.fConst372) + 0.245292));
		this.fConst427 = (0.0001 / this.fConst375);
		this.fConst428 = (2 * (0.000433227 - this.fConst427));
		this.fConst429 = (((this.fConst373 + -0.782413) / this.fConst372) + 0.245292);
		this.fConst430 = (2 * (0.245292 - this.fConst401));
		this.fConst431 = (this.fConst427 + 0.000433227);
		this.fConst432 = (((this.fConst373 + -0.512479) / this.fConst372) + 0.689621);
		this.fConst433 = (2 * (0.689621 - this.fConst401));
		this.fConst434 = (this.fConst401 + 7.62173);
		this.fConst435 = (((this.fConst373 + -0.168405) / this.fConst372) + 1.06936);
		this.fConst436 = (2 * (1.06936 - this.fConst401));
		this.fConst437 = (this.fConst401 + 53.5362);
		this.fConst438 = (((this.fConst411 + -3.18973) / this.fConst410) + 4.07678);
		this.fConst439 = (1 / this.fConst413);
		this.fConst440 = (2 * (4.07678 - this.fConst439));
		this.fConst441 = (this.fConst420 + 0.000407678);
		this.fConst442 = (((this.fConst411 + -0.74313) / this.fConst410) + 1.45007);
		this.fConst443 = (2 * (1.45007 - this.fConst439));
		this.fConst444 = (this.fConst417 + 1.45007);
		this.fConst445 = (((this.fConst411 + -0.157482) / this.fConst410) + 0.93514);
		this.fConst446 = (2 * (0.93514 - this.fConst439));
		this.fConst447 = (this.fConst414 + 0.93514);
		this.fConst448 = Math.tan((196.35 / this.fConst0));
		this.fConst449 = (1 / this.fConst448);
		this.fConst450 = (1 / (((this.fConst449 + 0.157482) / this.fConst448) + 0.93514));
		this.fConst451 = mydsp_faustpower2_f(this.fConst448);
		this.fConst452 = (50.0638 / this.fConst451);
		this.fConst453 = (2 * (0.93514 - this.fConst452));
		this.fConst454 = (1 / (((this.fConst449 + 0.74313) / this.fConst448) + 1.45007));
		this.fConst455 = (11.0521 / this.fConst451);
		this.fConst456 = (2 * (1.45007 - this.fConst455));
		this.fConst457 = (1 / (((this.fConst449 + 3.18973) / this.fConst448) + 4.07678));
		this.fConst458 = (0.00176617 / this.fConst451);
		this.fConst459 = (2 * (0.000407678 - this.fConst458));
		this.fConst460 = (1 / (((this.fConst411 + 0.168405) / this.fConst410) + 1.06936));
		this.fConst461 = (2 * (53.5362 - this.fConst439));
		this.fConst462 = (1 / (((this.fConst411 + 0.512479) / this.fConst410) + 0.689621));
		this.fConst463 = (2 * (7.62173 - this.fConst439));
		this.fConst464 = (1 / (((this.fConst411 + 0.782413) / this.fConst410) + 0.245292));
		this.fConst465 = (0.0001 / this.fConst413);
		this.fConst466 = (2 * (0.000433227 - this.fConst465));
		this.fConst467 = (((this.fConst411 + -0.782413) / this.fConst410) + 0.245292);
		this.fConst468 = (2 * (0.245292 - this.fConst439));
		this.fConst469 = (this.fConst465 + 0.000433227);
		this.fConst470 = (((this.fConst411 + -0.512479) / this.fConst410) + 0.689621);
		this.fConst471 = (2 * (0.689621 - this.fConst439));
		this.fConst472 = (this.fConst439 + 7.62173);
		this.fConst473 = (((this.fConst411 + -0.168405) / this.fConst410) + 1.06936);
		this.fConst474 = (2 * (1.06936 - this.fConst439));
		this.fConst475 = (this.fConst439 + 53.5362);
		this.fConst476 = (((this.fConst449 + -3.18973) / this.fConst448) + 4.07678);
		this.fConst477 = (1 / this.fConst451);
		this.fConst478 = (2 * (4.07678 - this.fConst477));
		this.fConst479 = (this.fConst458 + 0.000407678);
		this.fConst480 = (((this.fConst449 + -0.74313) / this.fConst448) + 1.45007);
		this.fConst481 = (2 * (1.45007 - this.fConst477));
		this.fConst482 = (this.fConst455 + 1.45007);
		this.fConst483 = (((this.fConst449 + -0.157482) / this.fConst448) + 0.93514);
		this.fConst484 = (2 * (0.93514 - this.fConst477));
		this.fConst485 = (this.fConst452 + 0.93514);
		this.fConst486 = Math.tan((123.692 / this.fConst0));
		this.fConst487 = (1 / this.fConst486);
		this.fConst488 = (1 / (((this.fConst487 + 0.157482) / this.fConst486) + 0.93514));
		this.fConst489 = mydsp_faustpower2_f(this.fConst486);
		this.fConst490 = (50.0638 / this.fConst489);
		this.fConst491 = (2 * (0.93514 - this.fConst490));
		this.fConst492 = (1 / (((this.fConst487 + 0.74313) / this.fConst486) + 1.45007));
		this.fConst493 = (11.0521 / this.fConst489);
		this.fConst494 = (2 * (1.45007 - this.fConst493));
		this.fConst495 = (1 / (((this.fConst487 + 3.18973) / this.fConst486) + 4.07678));
		this.fConst496 = (0.00176617 / this.fConst489);
		this.fConst497 = (2 * (0.000407678 - this.fConst496));
		this.fConst498 = (1 / (((this.fConst449 + 0.168405) / this.fConst448) + 1.06936));
		this.fConst499 = (2 * (53.5362 - this.fConst477));
		this.fConst500 = (1 / (((this.fConst449 + 0.512479) / this.fConst448) + 0.689621));
		this.fConst501 = (2 * (7.62173 - this.fConst477));
		this.fConst502 = (1 / (((this.fConst449 + 0.782413) / this.fConst448) + 0.245292));
		this.fConst503 = (0.0001 / this.fConst451);
		this.fConst504 = (2 * (0.000433227 - this.fConst503));
		this.fConst505 = (((this.fConst449 + -0.782413) / this.fConst448) + 0.245292);
		this.fConst506 = (2 * (0.245292 - this.fConst477));
		this.fConst507 = (this.fConst503 + 0.000433227);
		this.fConst508 = (((this.fConst449 + -0.512479) / this.fConst448) + 0.689621);
		this.fConst509 = (2 * (0.689621 - this.fConst477));
		this.fConst510 = (this.fConst477 + 7.62173);
		this.fConst511 = (((this.fConst449 + -0.168405) / this.fConst448) + 1.06936);
		this.fConst512 = (2 * (1.06936 - this.fConst477));
		this.fConst513 = (this.fConst477 + 53.5362);
		this.fConst514 = (((this.fConst487 + -3.18973) / this.fConst486) + 4.07678);
		this.fConst515 = (1 / this.fConst489);
		this.fConst516 = (2 * (4.07678 - this.fConst515));
		this.fConst517 = (this.fConst496 + 0.000407678);
		this.fConst518 = (((this.fConst487 + -0.74313) / this.fConst486) + 1.45007);
		this.fConst519 = (2 * (1.45007 - this.fConst515));
		this.fConst520 = (this.fConst493 + 1.45007);
		this.fConst521 = (((this.fConst487 + -0.157482) / this.fConst486) + 0.93514);
		this.fConst522 = (2 * (0.93514 - this.fConst515));
		this.fConst523 = (this.fConst490 + 0.93514);
		this.fConst524 = (1 / (((this.fConst487 + 0.168405) / this.fConst486) + 1.06936));
		this.fConst525 = (2 * (53.5362 - this.fConst515));
		this.fConst526 = (1 / (((this.fConst487 + 0.512479) / this.fConst486) + 0.689621));
		this.fConst527 = (2 * (7.62173 - this.fConst515));
		this.fConst528 = (1 / (((this.fConst487 + 0.782413) / this.fConst486) + 0.245292));
		this.fConst529 = (0.0001 / this.fConst489);
		this.fConst530 = (2 * (0.000433227 - this.fConst529));
		this.fConst531 = (((this.fConst487 + -0.782413) / this.fConst486) + 0.245292);
		this.fConst532 = (2 * (0.245292 - this.fConst515));
		this.fConst533 = (this.fConst529 + 0.000433227);
		this.fConst534 = (((this.fConst487 + -0.512479) / this.fConst486) + 0.689621);
		this.fConst535 = (2 * (0.689621 - this.fConst515));
		this.fConst536 = (this.fConst515 + 7.62173);
		this.fConst537 = (((this.fConst487 + -0.168405) / this.fConst486) + 1.06936);
		this.fConst538 = (2 * (1.06936 - this.fConst515));
		this.fConst539 = (this.fConst515 + 53.5362);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		this.fCheckbox0 = 0;
		this.fHslider2 = 100;
		this.fHslider3 = 5000;
		this.fHslider4 = -0.5;
		this.fVslider0 = -20;
		this.fCheckbox1 = 0;
		this.fCheckbox2 = 0;
		this.fEntry0 = 2;
		this.fVslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fCheckbox3 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec35[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec37[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec36[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fVec2[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fVec3[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec4[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fVec5[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec6[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fVec7[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec8[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec38[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fVec9[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fVec10[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fVec11[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fVec12[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fVec13[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fVec14[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fVec15[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fRec39[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fVec16[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fVec17[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fVec18[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fVec19[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec20[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fVec21[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.iRec40[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			this.fRec41[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fVec22[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec34[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fVec23[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec33[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fVec24[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec32[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.fVec25[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fRec31[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fVec26[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec30[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fVec27[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec29[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fVec28[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec28[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fVec29[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fRec27[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fVec30[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec26[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fVec31[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			this.fRec25[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec24[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec23[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec22[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec21[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec20[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec19[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec18[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec17[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			this.fRec16[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			this.fRec15[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec14[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec13[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec12[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec11[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec10[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			this.fRec9[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			this.fRec8[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			this.fRec7[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec6[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec5[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			this.fRec4[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			this.fRec3[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			this.fRec2[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec1[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			this.fRec0[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec45[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec44[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec43[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			this.fRec42[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			this.fRec49[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec48[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec47[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			this.fRec46[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec53[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec52[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec51[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			this.fRec50[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec57[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			this.fRec56[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec55[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			this.fRec54[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec61[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			this.fRec60[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			this.fRec59[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			this.fRec58[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec65[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec64[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec63[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			this.fRec62[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			this.fRec69[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			this.fRec68[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec67[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			this.fRec66[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec76[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec75[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			this.fRec74[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			this.fRec73[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			this.fRec72[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec71[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			this.fRec70[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			this.fRec83[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			this.fRec82[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			this.fRec81[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			this.fRec80[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			this.fRec79[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			this.fRec78[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			this.fRec77[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec90[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			this.fRec89[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			this.fRec88[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			this.fRec87[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			this.fRec86[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			this.fRec85[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			this.fRec84[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec97[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec96[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			this.fRec95[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			this.fRec94[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			this.fRec93[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			this.fRec92[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			this.fRec91[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			this.fRec104[l130] = 0;
			
		}
		for (var l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			this.fRec103[l131] = 0;
			
		}
		for (var l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			this.fRec102[l132] = 0;
			
		}
		for (var l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			this.fRec101[l133] = 0;
			
		}
		for (var l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			this.fRec100[l134] = 0;
			
		}
		for (var l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			this.fRec99[l135] = 0;
			
		}
		for (var l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			this.fRec98[l136] = 0;
			
		}
		for (var l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			this.fRec111[l137] = 0;
			
		}
		for (var l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			this.fRec110[l138] = 0;
			
		}
		for (var l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			this.fRec109[l139] = 0;
			
		}
		for (var l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			this.fRec108[l140] = 0;
			
		}
		for (var l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			this.fRec107[l141] = 0;
			
		}
		for (var l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			this.fRec106[l142] = 0;
			
		}
		for (var l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			this.fRec105[l143] = 0;
			
		}
		for (var l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			this.fRec115[l144] = 0;
			
		}
		for (var l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			this.fRec114[l145] = 0;
			
		}
		for (var l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			this.fRec113[l146] = 0;
			
		}
		for (var l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			this.fRec112[l147] = 0;
			
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
		ui_interface.openVerticalBox("spectralTiltLab");
		ui_interface.declare("0", "1", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
		ui_interface.openVerticalBox("Spectral Tilt Filter");
		ui_interface.declare("fHslider4", "1", "");
		ui_interface.addHorizontalSlider("Slope of Spectral Tilt across Band", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), -0.5, -1, 1, 0.001);
		ui_interface.declare("0", "1", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for spectral_tilt_demo");
		ui_interface.openVerticalBox("Spectral Tilt Filter");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.addCheckButton("Bypass Spectral Tilt", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("fHslider2", "2", "");
		ui_interface.declare("fHslider2", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Start Frequency", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 100, 20, 10000, 1);
		ui_interface.declare("fHslider3", "3", "");
		ui_interface.declare("fHslider3", "unit", "Hz");
		ui_interface.addHorizontalSlider("Band Width", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 5000, 100, 10000, 1);
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
		ui_interface.declare("fCheckbox2", "0", "");
		ui_interface.addCheckButton("Noise (White or Pink - uses only Amplitude control on   the left)", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox3", "1", "");
		ui_interface.declare("fCheckbox3", "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave");
		ui_interface.addCheckButton("Pink instead of White Noise (also called 1/f Noise)", function handler(obj) { function setval(val) { obj.fCheckbox3 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "2", "");
		ui_interface.addCheckButton("External Signal Input (overrides Sawtooth/Noise   selection above)", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
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
		ui_interface.declare("fVbargraph14", "0", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2beeec820", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2beedaec0", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2beeb8d70", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bee96c20", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bee74ad0", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bee52980", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bee30830", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "7", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bed8b870", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "8", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bee0e630", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "9", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bedf8440", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "10", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bede61d0", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "11", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bedd3f60", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "12", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bedc1cf0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "13", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bedafa80", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "14", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fb2bed9d810", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
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
		var fSlow0 = this.fHslider0;
		var fSlow1 = Math.exp((0 - (this.fConst1 / this.fHslider1)));
		var fSlow2 = (1 - fSlow1);
		var iSlow3 = this.fCheckbox0;
		var fSlow4 = this.fHslider2;
		var fSlow5 = Math.pow(((fSlow4 + this.fHslider3) / fSlow4), 0.111111);
		var fSlow6 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower9_f(fSlow5))));
		var fSlow7 = this.fHslider4;
		var fSlow8 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (9 - fSlow7)))));
		var fSlow9 = (fSlow6 / fSlow8);
		var fSlow10 = Math.tan((this.fConst91 * fSlow4));
		var fSlow11 = (6.28319 * ((fSlow4 * fSlow6) / fSlow10));
		var fSlow12 = (this.fConst92 + fSlow11);
		var fSlow13 = (0 - ((fSlow11 - this.fConst92) / fSlow12));
		var fSlow14 = (1 / fSlow12);
		var fSlow15 = (6.28319 * ((fSlow4 * fSlow8) / fSlow10));
		var fSlow16 = (fSlow15 - this.fConst92);
		var fSlow17 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower8_f(fSlow5))));
		var fSlow18 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (8 - fSlow7)))));
		var fSlow19 = (fSlow17 / fSlow18);
		var fSlow20 = (6.28319 * ((fSlow4 * fSlow17) / fSlow10));
		var fSlow21 = (this.fConst92 + fSlow20);
		var fSlow22 = (0 - ((fSlow20 - this.fConst92) / fSlow21));
		var fSlow23 = (1 / fSlow21);
		var fSlow24 = (6.28319 * ((fSlow4 * fSlow18) / fSlow10));
		var fSlow25 = (fSlow24 - this.fConst92);
		var fSlow26 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower7_f(fSlow5))));
		var fSlow27 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (7 - fSlow7)))));
		var fSlow28 = (fSlow26 / fSlow27);
		var fSlow29 = (6.28319 * ((fSlow4 * fSlow26) / fSlow10));
		var fSlow30 = (this.fConst92 + fSlow29);
		var fSlow31 = (0 - ((fSlow29 - this.fConst92) / fSlow30));
		var fSlow32 = (1 / fSlow30);
		var fSlow33 = (6.28319 * ((fSlow4 * fSlow27) / fSlow10));
		var fSlow34 = (fSlow33 - this.fConst92);
		var fSlow35 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower6_f(fSlow5))));
		var fSlow36 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (6 - fSlow7)))));
		var fSlow37 = (fSlow35 / fSlow36);
		var fSlow38 = (6.28319 * ((fSlow4 * fSlow35) / fSlow10));
		var fSlow39 = (this.fConst92 + fSlow38);
		var fSlow40 = (0 - ((fSlow38 - this.fConst92) / fSlow39));
		var fSlow41 = (1 / fSlow39);
		var fSlow42 = (6.28319 * ((fSlow4 * fSlow36) / fSlow10));
		var fSlow43 = (fSlow42 - this.fConst92);
		var fSlow44 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower5_f(fSlow5))));
		var fSlow45 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (5 - fSlow7)))));
		var fSlow46 = (fSlow44 / fSlow45);
		var fSlow47 = (6.28319 * ((fSlow4 * fSlow44) / fSlow10));
		var fSlow48 = (this.fConst92 + fSlow47);
		var fSlow49 = (0 - ((fSlow47 - this.fConst92) / fSlow48));
		var fSlow50 = (1 / fSlow48);
		var fSlow51 = (6.28319 * ((fSlow4 * fSlow45) / fSlow10));
		var fSlow52 = (fSlow51 - this.fConst92);
		var fSlow53 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower4_f(fSlow5))));
		var fSlow54 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (4 - fSlow7)))));
		var fSlow55 = (fSlow53 / fSlow54);
		var fSlow56 = (6.28319 * ((fSlow4 * fSlow53) / fSlow10));
		var fSlow57 = (this.fConst92 + fSlow56);
		var fSlow58 = (0 - ((fSlow56 - this.fConst92) / fSlow57));
		var fSlow59 = (1 / fSlow57);
		var fSlow60 = (6.28319 * ((fSlow4 * fSlow54) / fSlow10));
		var fSlow61 = (fSlow60 - this.fConst92);
		var fSlow62 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower3_f(fSlow5))));
		var fSlow63 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (3 - fSlow7)))));
		var fSlow64 = (fSlow62 / fSlow63);
		var fSlow65 = (6.28319 * ((fSlow4 * fSlow62) / fSlow10));
		var fSlow66 = (this.fConst92 + fSlow65);
		var fSlow67 = (0 - ((fSlow65 - this.fConst92) / fSlow66));
		var fSlow68 = (1 / fSlow66);
		var fSlow69 = (6.28319 * ((fSlow4 * fSlow63) / fSlow10));
		var fSlow70 = (fSlow69 - this.fConst92);
		var fSlow71 = Math.tan((this.fConst91 * (fSlow4 * mydsp_faustpower2_f(fSlow5))));
		var fSlow72 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (2 - fSlow7)))));
		var fSlow73 = (fSlow71 / fSlow72);
		var fSlow74 = (6.28319 * ((fSlow4 * fSlow71) / fSlow10));
		var fSlow75 = (this.fConst92 + fSlow74);
		var fSlow76 = (0 - ((fSlow74 - this.fConst92) / fSlow75));
		var fSlow77 = (1 / fSlow75);
		var fSlow78 = (6.28319 * ((fSlow4 * fSlow72) / fSlow10));
		var fSlow79 = (fSlow78 - this.fConst92);
		var fSlow80 = Math.tan((this.fConst91 * (fSlow4 * fSlow5)));
		var fSlow81 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (1 - fSlow7)))));
		var fSlow82 = (fSlow80 / fSlow81);
		var fSlow83 = (6.28319 * ((fSlow4 * fSlow80) / fSlow10));
		var fSlow84 = (this.fConst92 + fSlow83);
		var fSlow85 = (0 - ((fSlow83 - this.fConst92) / fSlow84));
		var fSlow86 = (1 / fSlow84);
		var fSlow87 = (6.28319 * ((fSlow4 * fSlow81) / fSlow10));
		var fSlow88 = (fSlow87 - this.fConst92);
		var fSlow89 = Math.tan((this.fConst91 * (fSlow4 * Math.pow(fSlow5, (0 - fSlow7)))));
		var fSlow90 = (fSlow10 / fSlow89);
		var fSlow91 = (6.28319 * fSlow4);
		var fSlow92 = (this.fConst92 + fSlow91);
		var fSlow93 = (0 - ((fSlow91 - this.fConst92) / fSlow92));
		var fSlow94 = (1 / fSlow92);
		var fSlow95 = (6.28319 * ((fSlow4 * fSlow89) / fSlow10));
		var fSlow96 = (this.fConst92 + fSlow95);
		var fSlow97 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var iSlow98 = this.fCheckbox1;
		var iSlow99 = this.fCheckbox2;
		var iSlow100 = (this.fEntry0 + -1);
		var iSlow101 = (iSlow100 >= 2);
		var iSlow102 = (iSlow100 >= 1);
		var fSlow103 = Math.exp((0 - (this.fConst93 / this.fVslider2)));
		var fSlow104 = (440 * (Math.pow(2, (0.0833333 * (this.fVslider1 + -49))) * (1 - fSlow103)));
		var iSlow105 = (iSlow100 >= 3);
		var fSlow106 = ((0.01 * this.fVslider3) + 1);
		var fSlow107 = ((0.01 * this.fVslider4) + 1);
		var iSlow108 = this.fCheckbox3;
		var fSlow109 = (fSlow95 - this.fConst92);
		var fSlow110 = ((fSlow10 * (this.fConst92 + fSlow87)) / fSlow89);
		var fSlow111 = ((fSlow80 * (this.fConst92 + fSlow78)) / fSlow81);
		var fSlow112 = ((fSlow71 * (this.fConst92 + fSlow69)) / fSlow72);
		var fSlow113 = ((fSlow62 * (this.fConst92 + fSlow60)) / fSlow63);
		var fSlow114 = ((fSlow53 * (this.fConst92 + fSlow51)) / fSlow54);
		var fSlow115 = ((fSlow44 * (this.fConst92 + fSlow42)) / fSlow45);
		var fSlow116 = ((fSlow35 * (this.fConst92 + fSlow33)) / fSlow36);
		var fSlow117 = ((fSlow26 * (this.fConst92 + fSlow24)) / fSlow27);
		var fSlow118 = ((fSlow17 * (this.fConst92 + fSlow15)) / fSlow18);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec35[0] = (fSlow97 + (0.999 * this.fRec35[1]));
			this.fRec37[0] = (fSlow104 + (fSlow103 * this.fRec37[1]));
			var fTemp0 = max_f(20, Math.abs(this.fRec37[0]));
			this.fVec1[0] = fTemp0;
			var fTemp1 = (this.fRec36[1] + (this.fConst93 * this.fVec1[1]));
			this.fRec36[0] = (fTemp1 - Math.floor(fTemp1));
			var fTemp2 = (2 * this.fRec36[0]);
			var fTemp3 = (fTemp2 + -1);
			var fTemp4 = mydsp_faustpower2_f(fTemp3);
			this.fVec2[0] = fTemp4;
			var fTemp5 = mydsp_faustpower3_f(fTemp3);
			this.fVec3[0] = (fTemp5 + (1 - fTemp2));
			var fTemp6 = ((fTemp5 + (1 - (fTemp2 + this.fVec3[1]))) / fTemp0);
			this.fVec4[0] = fTemp6;
			var fTemp7 = (fTemp4 * (fTemp4 + -2));
			this.fVec5[0] = fTemp7;
			var fTemp8 = ((fTemp7 - this.fVec5[1]) / fTemp0);
			this.fVec6[0] = fTemp8;
			var fTemp9 = ((fTemp8 - this.fVec6[1]) / fTemp0);
			this.fVec7[0] = fTemp9;
			var fTemp10 = max_f(20, Math.abs((fSlow106 * this.fRec37[0])));
			this.fVec8[0] = fTemp10;
			var fTemp11 = (this.fRec38[1] + (this.fConst93 * this.fVec8[1]));
			this.fRec38[0] = (fTemp11 - Math.floor(fTemp11));
			var fTemp12 = (2 * this.fRec38[0]);
			var fTemp13 = (fTemp12 + -1);
			var fTemp14 = mydsp_faustpower2_f(fTemp13);
			this.fVec9[0] = fTemp14;
			var fTemp15 = mydsp_faustpower3_f(fTemp13);
			this.fVec10[0] = (fTemp15 + (1 - fTemp12));
			var fTemp16 = ((fTemp15 + (1 - (fTemp12 + this.fVec10[1]))) / fTemp10);
			this.fVec11[0] = fTemp16;
			var fTemp17 = (fTemp14 * (fTemp14 + -2));
			this.fVec12[0] = fTemp17;
			var fTemp18 = ((fTemp17 - this.fVec12[1]) / fTemp10);
			this.fVec13[0] = fTemp18;
			var fTemp19 = ((fTemp18 - this.fVec13[1]) / fTemp10);
			this.fVec14[0] = fTemp19;
			var fTemp20 = max_f(20, Math.abs((fSlow107 * this.fRec37[0])));
			this.fVec15[0] = fTemp20;
			var fTemp21 = (this.fRec39[1] + (this.fConst93 * this.fVec15[1]));
			this.fRec39[0] = (fTemp21 - Math.floor(fTemp21));
			var fTemp22 = (2 * this.fRec39[0]);
			var fTemp23 = (fTemp22 + -1);
			var fTemp24 = mydsp_faustpower2_f(fTemp23);
			this.fVec16[0] = fTemp24;
			var fTemp25 = mydsp_faustpower3_f(fTemp23);
			this.fVec17[0] = (fTemp25 + (1 - fTemp22));
			var fTemp26 = ((fTemp25 + (1 - (fTemp22 + this.fVec17[1]))) / fTemp20);
			this.fVec18[0] = fTemp26;
			var fTemp27 = (fTemp24 * (fTemp24 + -2));
			this.fVec19[0] = fTemp27;
			var fTemp28 = ((fTemp27 - this.fVec19[1]) / fTemp20);
			this.fVec20[0] = fTemp28;
			var fTemp29 = ((fTemp28 - this.fVec20[1]) / fTemp20);
			this.fVec21[0] = fTemp29;
			this.iRec40[0] = ((1103515245 * this.iRec40[1]) + 12345);
			var fTemp30 = (4.65661e-10 * this.iRec40[0]);
			this.fRec41[0] = (((0.522189 * this.fRec41[3]) + (fTemp30 + (2.49496 * this.fRec41[1]))) - (2.01727 * this.fRec41[2]));
			var fTemp31 = (this.fRec35[0] * (iSlow98?input0[i]:(iSlow99?(iSlow108?(((0.049922 * this.fRec41[0]) + (0.0506127 * this.fRec41[2])) - ((0.0959935 * this.fRec41[1]) + (0.00440879 * this.fRec41[3]))):fTemp30):(0.333333 * (this.fRec35[0] * (((iSlow101?(iSlow105?(this.fConst96 * ((this.iVec0[3] * (fTemp9 - this.fVec7[1])) / fTemp0)):(this.fConst95 * ((this.iVec0[2] * (fTemp6 - this.fVec4[1])) / fTemp0))):(iSlow102?(this.fConst94 * ((this.iVec0[1] * (fTemp4 - this.fVec2[1])) / fTemp0)):fTemp3)) + (iSlow101?(iSlow105?(this.fConst96 * ((this.iVec0[3] * (fTemp19 - this.fVec14[1])) / fTemp10)):(this.fConst95 * ((this.iVec0[2] * (fTemp16 - this.fVec11[1])) / fTemp10))):(iSlow102?(this.fConst94 * ((this.iVec0[1] * (fTemp14 - this.fVec9[1])) / fTemp10)):fTemp13))) + (iSlow101?(iSlow105?(this.fConst96 * ((this.iVec0[3] * (fTemp29 - this.fVec21[1])) / fTemp20)):(this.fConst95 * ((this.iVec0[2] * (fTemp26 - this.fVec18[1])) / fTemp20))):(iSlow102?(this.fConst94 * ((this.iVec0[1] * (fTemp24 - this.fVec16[1])) / fTemp20)):fTemp23))))))));
			var fTemp32 = (iSlow3?0:fTemp31);
			this.fVec22[0] = fTemp32;
			this.fRec34[0] = ((fSlow93 * this.fRec34[1]) + (fSlow94 * ((fSlow96 * fTemp32) + (fSlow109 * this.fVec22[1]))));
			this.fVec23[0] = (fSlow90 * this.fRec34[0]);
			this.fRec33[0] = ((fSlow85 * this.fRec33[1]) + (fSlow86 * ((fSlow88 * this.fVec23[1]) + (fSlow110 * this.fRec34[0]))));
			this.fVec24[0] = (fSlow82 * this.fRec33[0]);
			this.fRec32[0] = ((fSlow76 * this.fRec32[1]) + (fSlow77 * ((fSlow79 * this.fVec24[1]) + (fSlow111 * this.fRec33[0]))));
			this.fVec25[0] = (fSlow73 * this.fRec32[0]);
			this.fRec31[0] = ((fSlow67 * this.fRec31[1]) + (fSlow68 * ((fSlow70 * this.fVec25[1]) + (fSlow112 * this.fRec32[0]))));
			this.fVec26[0] = (fSlow64 * this.fRec31[0]);
			this.fRec30[0] = ((fSlow58 * this.fRec30[1]) + (fSlow59 * ((fSlow61 * this.fVec26[1]) + (fSlow113 * this.fRec31[0]))));
			this.fVec27[0] = (fSlow55 * this.fRec30[0]);
			this.fRec29[0] = ((fSlow49 * this.fRec29[1]) + (fSlow50 * ((fSlow52 * this.fVec27[1]) + (fSlow114 * this.fRec30[0]))));
			this.fVec28[0] = (fSlow46 * this.fRec29[0]);
			this.fRec28[0] = ((fSlow40 * this.fRec28[1]) + (fSlow41 * ((fSlow43 * this.fVec28[1]) + (fSlow115 * this.fRec29[0]))));
			this.fVec29[0] = (fSlow37 * this.fRec28[0]);
			this.fRec27[0] = ((fSlow31 * this.fRec27[1]) + (fSlow32 * ((fSlow34 * this.fVec29[1]) + (fSlow116 * this.fRec28[0]))));
			this.fVec30[0] = (fSlow28 * this.fRec27[0]);
			this.fRec26[0] = ((fSlow22 * this.fRec26[1]) + (fSlow23 * ((fSlow25 * this.fVec30[1]) + (fSlow117 * this.fRec27[0]))));
			this.fVec31[0] = (fSlow19 * this.fRec26[0]);
			this.fRec25[0] = ((fSlow13 * this.fRec25[1]) + (fSlow14 * ((fSlow16 * this.fVec31[1]) + (fSlow118 * this.fRec26[0]))));
			var fTemp33 = (iSlow3?fTemp31:(fSlow9 * this.fRec25[0]));
			this.fRec24[0] = (fTemp33 - (this.fConst88 * ((this.fConst97 * this.fRec24[2]) + (this.fConst98 * this.fRec24[1]))));
			this.fRec23[0] = ((this.fConst88 * (((this.fConst90 * this.fRec24[1]) + (this.fConst99 * this.fRec24[0])) + (this.fConst99 * this.fRec24[2]))) - (this.fConst86 * ((this.fConst100 * this.fRec23[2]) + (this.fConst101 * this.fRec23[1]))));
			this.fRec22[0] = ((this.fConst86 * (((this.fConst87 * this.fRec23[1]) + (this.fConst102 * this.fRec23[0])) + (this.fConst102 * this.fRec23[2]))) - (this.fConst82 * ((this.fConst103 * this.fRec22[2]) + (this.fConst104 * this.fRec22[1]))));
			var fTemp34 = (this.fConst82 * (((this.fConst85 * this.fRec22[1]) + (this.fConst105 * this.fRec22[0])) + (this.fConst105 * this.fRec22[2])));
			this.fRec21[0] = (fTemp34 - (this.fConst77 * ((this.fConst106 * this.fRec21[2]) + (this.fConst107 * this.fRec21[1]))));
			this.fRec20[0] = ((this.fConst77 * (((this.fConst79 * this.fRec21[1]) + (this.fConst108 * this.fRec21[0])) + (this.fConst108 * this.fRec21[2]))) - (this.fConst75 * ((this.fConst109 * this.fRec20[2]) + (this.fConst110 * this.fRec20[1]))));
			this.fRec19[0] = ((this.fConst75 * (((this.fConst76 * this.fRec20[1]) + (this.fConst111 * this.fRec20[0])) + (this.fConst111 * this.fRec20[2]))) - (this.fConst71 * ((this.fConst112 * this.fRec19[2]) + (this.fConst113 * this.fRec19[1]))));
			var fTemp35 = (this.fConst71 * (((this.fConst74 * this.fRec19[1]) + (this.fConst114 * this.fRec19[0])) + (this.fConst114 * this.fRec19[2])));
			this.fRec18[0] = (fTemp35 - (this.fConst66 * ((this.fConst115 * this.fRec18[2]) + (this.fConst116 * this.fRec18[1]))));
			this.fRec17[0] = ((this.fConst66 * (((this.fConst68 * this.fRec18[1]) + (this.fConst117 * this.fRec18[0])) + (this.fConst117 * this.fRec18[2]))) - (this.fConst64 * ((this.fConst118 * this.fRec17[2]) + (this.fConst119 * this.fRec17[1]))));
			this.fRec16[0] = ((this.fConst64 * (((this.fConst65 * this.fRec17[1]) + (this.fConst120 * this.fRec17[0])) + (this.fConst120 * this.fRec17[2]))) - (this.fConst60 * ((this.fConst121 * this.fRec16[2]) + (this.fConst122 * this.fRec16[1]))));
			var fTemp36 = (this.fConst60 * (((this.fConst63 * this.fRec16[1]) + (this.fConst123 * this.fRec16[0])) + (this.fConst123 * this.fRec16[2])));
			this.fRec15[0] = (fTemp36 - (this.fConst55 * ((this.fConst124 * this.fRec15[2]) + (this.fConst125 * this.fRec15[1]))));
			this.fRec14[0] = ((this.fConst55 * (((this.fConst57 * this.fRec15[1]) + (this.fConst126 * this.fRec15[0])) + (this.fConst126 * this.fRec15[2]))) - (this.fConst53 * ((this.fConst127 * this.fRec14[2]) + (this.fConst128 * this.fRec14[1]))));
			this.fRec13[0] = ((this.fConst53 * (((this.fConst54 * this.fRec14[1]) + (this.fConst129 * this.fRec14[0])) + (this.fConst129 * this.fRec14[2]))) - (this.fConst49 * ((this.fConst130 * this.fRec13[2]) + (this.fConst131 * this.fRec13[1]))));
			var fTemp37 = (this.fConst49 * (((this.fConst52 * this.fRec13[1]) + (this.fConst132 * this.fRec13[0])) + (this.fConst132 * this.fRec13[2])));
			this.fRec12[0] = (fTemp37 - (this.fConst44 * ((this.fConst133 * this.fRec12[2]) + (this.fConst134 * this.fRec12[1]))));
			this.fRec11[0] = ((this.fConst44 * (((this.fConst46 * this.fRec12[1]) + (this.fConst135 * this.fRec12[0])) + (this.fConst135 * this.fRec12[2]))) - (this.fConst42 * ((this.fConst136 * this.fRec11[2]) + (this.fConst137 * this.fRec11[1]))));
			this.fRec10[0] = ((this.fConst42 * (((this.fConst43 * this.fRec11[1]) + (this.fConst138 * this.fRec11[0])) + (this.fConst138 * this.fRec11[2]))) - (this.fConst38 * ((this.fConst139 * this.fRec10[2]) + (this.fConst140 * this.fRec10[1]))));
			var fTemp38 = (this.fConst38 * (((this.fConst41 * this.fRec10[1]) + (this.fConst141 * this.fRec10[0])) + (this.fConst141 * this.fRec10[2])));
			this.fRec9[0] = (fTemp38 - (this.fConst33 * ((this.fConst142 * this.fRec9[2]) + (this.fConst143 * this.fRec9[1]))));
			this.fRec8[0] = ((this.fConst33 * (((this.fConst35 * this.fRec9[1]) + (this.fConst144 * this.fRec9[0])) + (this.fConst144 * this.fRec9[2]))) - (this.fConst31 * ((this.fConst145 * this.fRec8[2]) + (this.fConst146 * this.fRec8[1]))));
			this.fRec7[0] = ((this.fConst31 * (((this.fConst32 * this.fRec8[1]) + (this.fConst147 * this.fRec8[0])) + (this.fConst147 * this.fRec8[2]))) - (this.fConst27 * ((this.fConst148 * this.fRec7[2]) + (this.fConst149 * this.fRec7[1]))));
			var fTemp39 = (this.fConst27 * (((this.fConst30 * this.fRec7[1]) + (this.fConst150 * this.fRec7[0])) + (this.fConst150 * this.fRec7[2])));
			this.fRec6[0] = (fTemp39 - (this.fConst22 * ((this.fConst151 * this.fRec6[2]) + (this.fConst152 * this.fRec6[1]))));
			this.fRec5[0] = ((this.fConst22 * (((this.fConst24 * this.fRec6[1]) + (this.fConst153 * this.fRec6[0])) + (this.fConst153 * this.fRec6[2]))) - (this.fConst20 * ((this.fConst154 * this.fRec5[2]) + (this.fConst155 * this.fRec5[1]))));
			this.fRec4[0] = ((this.fConst20 * (((this.fConst21 * this.fRec5[1]) + (this.fConst156 * this.fRec5[0])) + (this.fConst156 * this.fRec5[2]))) - (this.fConst16 * ((this.fConst157 * this.fRec4[2]) + (this.fConst158 * this.fRec4[1]))));
			var fTemp40 = (this.fConst16 * (((this.fConst19 * this.fRec4[1]) + (this.fConst159 * this.fRec4[0])) + (this.fConst159 * this.fRec4[2])));
			this.fRec3[0] = (fTemp40 - (this.fConst11 * ((this.fConst160 * this.fRec3[2]) + (this.fConst162 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[1]) + (this.fConst163 * this.fRec3[0])) + (this.fConst163 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst164 * this.fRec2[2]) + (this.fConst165 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst166 * this.fRec2[0])) + (this.fConst166 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst167 * this.fRec1[2]) + (this.fConst168 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst169 * this.fRec1[0])) + (this.fConst169 * this.fRec1[2]))))) + (fSlow1 * this.fRec0[1]));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec45[0] = (fTemp33 - (this.fConst176 * ((this.fConst179 * this.fRec45[2]) + (this.fConst180 * this.fRec45[1]))));
			this.fRec44[0] = ((this.fConst176 * (((this.fConst178 * this.fRec45[1]) + (this.fConst181 * this.fRec45[0])) + (this.fConst181 * this.fRec45[2]))) - (this.fConst173 * ((this.fConst182 * this.fRec44[2]) + (this.fConst183 * this.fRec44[1]))));
			this.fRec43[0] = ((this.fConst173 * (((this.fConst175 * this.fRec44[1]) + (this.fConst184 * this.fRec44[0])) + (this.fConst184 * this.fRec44[2]))) - (this.fConst170 * ((this.fConst185 * this.fRec43[2]) + (this.fConst186 * this.fRec43[1]))));
			this.fRec42[0] = ((fSlow1 * this.fRec42[1]) + (fSlow2 * Math.abs((this.fConst170 * (((this.fConst172 * this.fRec43[1]) + (this.fConst187 * this.fRec43[0])) + (this.fConst187 * this.fRec43[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec42[0]))));
			this.fRec49[0] = (fTemp34 - (this.fConst194 * ((this.fConst197 * this.fRec49[2]) + (this.fConst198 * this.fRec49[1]))));
			this.fRec48[0] = ((this.fConst194 * (((this.fConst196 * this.fRec49[1]) + (this.fConst199 * this.fRec49[0])) + (this.fConst199 * this.fRec49[2]))) - (this.fConst191 * ((this.fConst200 * this.fRec48[2]) + (this.fConst201 * this.fRec48[1]))));
			this.fRec47[0] = ((this.fConst191 * (((this.fConst193 * this.fRec48[1]) + (this.fConst202 * this.fRec48[0])) + (this.fConst202 * this.fRec48[2]))) - (this.fConst188 * ((this.fConst203 * this.fRec47[2]) + (this.fConst204 * this.fRec47[1]))));
			this.fRec46[0] = ((fSlow1 * this.fRec46[1]) + (fSlow2 * Math.abs((this.fConst188 * (((this.fConst190 * this.fRec47[1]) + (this.fConst205 * this.fRec47[0])) + (this.fConst205 * this.fRec47[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec46[0]))));
			this.fRec53[0] = (fTemp35 - (this.fConst212 * ((this.fConst215 * this.fRec53[2]) + (this.fConst216 * this.fRec53[1]))));
			this.fRec52[0] = ((this.fConst212 * (((this.fConst214 * this.fRec53[1]) + (this.fConst217 * this.fRec53[0])) + (this.fConst217 * this.fRec53[2]))) - (this.fConst209 * ((this.fConst218 * this.fRec52[2]) + (this.fConst219 * this.fRec52[1]))));
			this.fRec51[0] = ((this.fConst209 * (((this.fConst211 * this.fRec52[1]) + (this.fConst220 * this.fRec52[0])) + (this.fConst220 * this.fRec52[2]))) - (this.fConst206 * ((this.fConst221 * this.fRec51[2]) + (this.fConst222 * this.fRec51[1]))));
			this.fRec50[0] = ((fSlow1 * this.fRec50[1]) + (fSlow2 * Math.abs((this.fConst206 * (((this.fConst208 * this.fRec51[1]) + (this.fConst223 * this.fRec51[0])) + (this.fConst223 * this.fRec51[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec50[0]))));
			this.fRec57[0] = (fTemp36 - (this.fConst230 * ((this.fConst233 * this.fRec57[2]) + (this.fConst234 * this.fRec57[1]))));
			this.fRec56[0] = ((this.fConst230 * (((this.fConst232 * this.fRec57[1]) + (this.fConst235 * this.fRec57[0])) + (this.fConst235 * this.fRec57[2]))) - (this.fConst227 * ((this.fConst236 * this.fRec56[2]) + (this.fConst237 * this.fRec56[1]))));
			this.fRec55[0] = ((this.fConst227 * (((this.fConst229 * this.fRec56[1]) + (this.fConst238 * this.fRec56[0])) + (this.fConst238 * this.fRec56[2]))) - (this.fConst224 * ((this.fConst239 * this.fRec55[2]) + (this.fConst240 * this.fRec55[1]))));
			this.fRec54[0] = ((fSlow1 * this.fRec54[1]) + (fSlow2 * Math.abs((this.fConst224 * (((this.fConst226 * this.fRec55[1]) + (this.fConst241 * this.fRec55[0])) + (this.fConst241 * this.fRec55[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec54[0]))));
			this.fRec61[0] = (fTemp37 - (this.fConst248 * ((this.fConst251 * this.fRec61[2]) + (this.fConst252 * this.fRec61[1]))));
			this.fRec60[0] = ((this.fConst248 * (((this.fConst250 * this.fRec61[1]) + (this.fConst253 * this.fRec61[0])) + (this.fConst253 * this.fRec61[2]))) - (this.fConst245 * ((this.fConst254 * this.fRec60[2]) + (this.fConst255 * this.fRec60[1]))));
			this.fRec59[0] = ((this.fConst245 * (((this.fConst247 * this.fRec60[1]) + (this.fConst256 * this.fRec60[0])) + (this.fConst256 * this.fRec60[2]))) - (this.fConst242 * ((this.fConst257 * this.fRec59[2]) + (this.fConst258 * this.fRec59[1]))));
			this.fRec58[0] = ((fSlow1 * this.fRec58[1]) + (fSlow2 * Math.abs((this.fConst242 * (((this.fConst244 * this.fRec59[1]) + (this.fConst259 * this.fRec59[0])) + (this.fConst259 * this.fRec59[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec58[0]))));
			this.fRec65[0] = (fTemp38 - (this.fConst266 * ((this.fConst269 * this.fRec65[2]) + (this.fConst270 * this.fRec65[1]))));
			this.fRec64[0] = ((this.fConst266 * (((this.fConst268 * this.fRec65[1]) + (this.fConst271 * this.fRec65[0])) + (this.fConst271 * this.fRec65[2]))) - (this.fConst263 * ((this.fConst272 * this.fRec64[2]) + (this.fConst273 * this.fRec64[1]))));
			this.fRec63[0] = ((this.fConst263 * (((this.fConst265 * this.fRec64[1]) + (this.fConst274 * this.fRec64[0])) + (this.fConst274 * this.fRec64[2]))) - (this.fConst260 * ((this.fConst275 * this.fRec63[2]) + (this.fConst276 * this.fRec63[1]))));
			this.fRec62[0] = ((fSlow1 * this.fRec62[1]) + (fSlow2 * Math.abs((this.fConst260 * (((this.fConst262 * this.fRec63[1]) + (this.fConst277 * this.fRec63[0])) + (this.fConst277 * this.fRec63[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec62[0]))));
			this.fRec69[0] = (fTemp39 - (this.fConst284 * ((this.fConst287 * this.fRec69[2]) + (this.fConst288 * this.fRec69[1]))));
			this.fRec68[0] = ((this.fConst284 * (((this.fConst286 * this.fRec69[1]) + (this.fConst289 * this.fRec69[0])) + (this.fConst289 * this.fRec69[2]))) - (this.fConst281 * ((this.fConst290 * this.fRec68[2]) + (this.fConst291 * this.fRec68[1]))));
			this.fRec67[0] = ((this.fConst281 * (((this.fConst283 * this.fRec68[1]) + (this.fConst292 * this.fRec68[0])) + (this.fConst292 * this.fRec68[2]))) - (this.fConst278 * ((this.fConst293 * this.fRec67[2]) + (this.fConst294 * this.fRec67[1]))));
			this.fRec66[0] = ((fSlow1 * this.fRec66[1]) + (fSlow2 * Math.abs((this.fConst278 * (((this.fConst280 * this.fRec67[1]) + (this.fConst295 * this.fRec67[0])) + (this.fConst295 * this.fRec67[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec66[0]))));
			this.fRec76[0] = (fTemp40 - (this.fConst312 * ((this.fConst315 * this.fRec76[2]) + (this.fConst316 * this.fRec76[1]))));
			this.fRec75[0] = ((this.fConst312 * (((this.fConst314 * this.fRec76[1]) + (this.fConst317 * this.fRec76[0])) + (this.fConst317 * this.fRec76[2]))) - (this.fConst310 * ((this.fConst318 * this.fRec75[2]) + (this.fConst319 * this.fRec75[1]))));
			this.fRec74[0] = ((this.fConst310 * (((this.fConst311 * this.fRec75[1]) + (this.fConst320 * this.fRec75[0])) + (this.fConst320 * this.fRec75[2]))) - (this.fConst308 * ((this.fConst321 * this.fRec74[2]) + (this.fConst322 * this.fRec74[1]))));
			var fTemp41 = (this.fConst308 * (((this.fConst309 * this.fRec74[1]) + (this.fConst323 * this.fRec74[0])) + (this.fConst323 * this.fRec74[2])));
			this.fRec73[0] = (fTemp41 - (this.fConst305 * ((this.fConst324 * this.fRec73[2]) + (this.fConst326 * this.fRec73[1]))));
			this.fRec72[0] = ((this.fConst305 * (((this.fConst307 * this.fRec73[1]) + (this.fConst327 * this.fRec73[0])) + (this.fConst327 * this.fRec73[2]))) - (this.fConst302 * ((this.fConst328 * this.fRec72[2]) + (this.fConst329 * this.fRec72[1]))));
			this.fRec71[0] = ((this.fConst302 * (((this.fConst304 * this.fRec72[1]) + (this.fConst330 * this.fRec72[0])) + (this.fConst330 * this.fRec72[2]))) - (this.fConst298 * ((this.fConst331 * this.fRec71[2]) + (this.fConst332 * this.fRec71[1]))));
			this.fRec70[0] = ((fSlow1 * this.fRec70[1]) + (fSlow2 * Math.abs((this.fConst298 * (((this.fConst301 * this.fRec71[1]) + (this.fConst333 * this.fRec71[0])) + (this.fConst333 * this.fRec71[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec70[0]))));
			this.fRec83[0] = (fTemp41 - (this.fConst350 * ((this.fConst353 * this.fRec83[2]) + (this.fConst354 * this.fRec83[1]))));
			this.fRec82[0] = ((this.fConst350 * (((this.fConst352 * this.fRec83[1]) + (this.fConst355 * this.fRec83[0])) + (this.fConst355 * this.fRec83[2]))) - (this.fConst348 * ((this.fConst356 * this.fRec82[2]) + (this.fConst357 * this.fRec82[1]))));
			this.fRec81[0] = ((this.fConst348 * (((this.fConst349 * this.fRec82[1]) + (this.fConst358 * this.fRec82[0])) + (this.fConst358 * this.fRec82[2]))) - (this.fConst346 * ((this.fConst359 * this.fRec81[2]) + (this.fConst360 * this.fRec81[1]))));
			var fTemp42 = (this.fConst346 * (((this.fConst347 * this.fRec81[1]) + (this.fConst361 * this.fRec81[0])) + (this.fConst361 * this.fRec81[2])));
			this.fRec80[0] = (fTemp42 - (this.fConst343 * ((this.fConst362 * this.fRec80[2]) + (this.fConst364 * this.fRec80[1]))));
			this.fRec79[0] = ((this.fConst343 * (((this.fConst345 * this.fRec80[1]) + (this.fConst365 * this.fRec80[0])) + (this.fConst365 * this.fRec80[2]))) - (this.fConst340 * ((this.fConst366 * this.fRec79[2]) + (this.fConst367 * this.fRec79[1]))));
			this.fRec78[0] = ((this.fConst340 * (((this.fConst342 * this.fRec79[1]) + (this.fConst368 * this.fRec79[0])) + (this.fConst368 * this.fRec79[2]))) - (this.fConst336 * ((this.fConst369 * this.fRec78[2]) + (this.fConst370 * this.fRec78[1]))));
			this.fRec77[0] = ((fSlow1 * this.fRec77[1]) + (fSlow2 * Math.abs((this.fConst336 * (((this.fConst339 * this.fRec78[1]) + (this.fConst371 * this.fRec78[0])) + (this.fConst371 * this.fRec78[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec77[0]))));
			this.fRec90[0] = (fTemp42 - (this.fConst388 * ((this.fConst391 * this.fRec90[2]) + (this.fConst392 * this.fRec90[1]))));
			this.fRec89[0] = ((this.fConst388 * (((this.fConst390 * this.fRec90[1]) + (this.fConst393 * this.fRec90[0])) + (this.fConst393 * this.fRec90[2]))) - (this.fConst386 * ((this.fConst394 * this.fRec89[2]) + (this.fConst395 * this.fRec89[1]))));
			this.fRec88[0] = ((this.fConst386 * (((this.fConst387 * this.fRec89[1]) + (this.fConst396 * this.fRec89[0])) + (this.fConst396 * this.fRec89[2]))) - (this.fConst384 * ((this.fConst397 * this.fRec88[2]) + (this.fConst398 * this.fRec88[1]))));
			var fTemp43 = (this.fConst384 * (((this.fConst385 * this.fRec88[1]) + (this.fConst399 * this.fRec88[0])) + (this.fConst399 * this.fRec88[2])));
			this.fRec87[0] = (fTemp43 - (this.fConst381 * ((this.fConst400 * this.fRec87[2]) + (this.fConst402 * this.fRec87[1]))));
			this.fRec86[0] = ((this.fConst381 * (((this.fConst383 * this.fRec87[1]) + (this.fConst403 * this.fRec87[0])) + (this.fConst403 * this.fRec87[2]))) - (this.fConst378 * ((this.fConst404 * this.fRec86[2]) + (this.fConst405 * this.fRec86[1]))));
			this.fRec85[0] = ((this.fConst378 * (((this.fConst380 * this.fRec86[1]) + (this.fConst406 * this.fRec86[0])) + (this.fConst406 * this.fRec86[2]))) - (this.fConst374 * ((this.fConst407 * this.fRec85[2]) + (this.fConst408 * this.fRec85[1]))));
			this.fRec84[0] = ((fSlow1 * this.fRec84[1]) + (fSlow2 * Math.abs((this.fConst374 * (((this.fConst377 * this.fRec85[1]) + (this.fConst409 * this.fRec85[0])) + (this.fConst409 * this.fRec85[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec84[0]))));
			this.fRec97[0] = (fTemp43 - (this.fConst426 * ((this.fConst429 * this.fRec97[2]) + (this.fConst430 * this.fRec97[1]))));
			this.fRec96[0] = ((this.fConst426 * (((this.fConst428 * this.fRec97[1]) + (this.fConst431 * this.fRec97[0])) + (this.fConst431 * this.fRec97[2]))) - (this.fConst424 * ((this.fConst432 * this.fRec96[2]) + (this.fConst433 * this.fRec96[1]))));
			this.fRec95[0] = ((this.fConst424 * (((this.fConst425 * this.fRec96[1]) + (this.fConst434 * this.fRec96[0])) + (this.fConst434 * this.fRec96[2]))) - (this.fConst422 * ((this.fConst435 * this.fRec95[2]) + (this.fConst436 * this.fRec95[1]))));
			var fTemp44 = (this.fConst422 * (((this.fConst423 * this.fRec95[1]) + (this.fConst437 * this.fRec95[0])) + (this.fConst437 * this.fRec95[2])));
			this.fRec94[0] = (fTemp44 - (this.fConst419 * ((this.fConst438 * this.fRec94[2]) + (this.fConst440 * this.fRec94[1]))));
			this.fRec93[0] = ((this.fConst419 * (((this.fConst421 * this.fRec94[1]) + (this.fConst441 * this.fRec94[0])) + (this.fConst441 * this.fRec94[2]))) - (this.fConst416 * ((this.fConst442 * this.fRec93[2]) + (this.fConst443 * this.fRec93[1]))));
			this.fRec92[0] = ((this.fConst416 * (((this.fConst418 * this.fRec93[1]) + (this.fConst444 * this.fRec93[0])) + (this.fConst444 * this.fRec93[2]))) - (this.fConst412 * ((this.fConst445 * this.fRec92[2]) + (this.fConst446 * this.fRec92[1]))));
			this.fRec91[0] = ((fSlow1 * this.fRec91[1]) + (fSlow2 * Math.abs((this.fConst412 * (((this.fConst415 * this.fRec92[1]) + (this.fConst447 * this.fRec92[0])) + (this.fConst447 * this.fRec92[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec91[0]))));
			this.fRec104[0] = (fTemp44 - (this.fConst464 * ((this.fConst467 * this.fRec104[2]) + (this.fConst468 * this.fRec104[1]))));
			this.fRec103[0] = ((this.fConst464 * (((this.fConst466 * this.fRec104[1]) + (this.fConst469 * this.fRec104[0])) + (this.fConst469 * this.fRec104[2]))) - (this.fConst462 * ((this.fConst470 * this.fRec103[2]) + (this.fConst471 * this.fRec103[1]))));
			this.fRec102[0] = ((this.fConst462 * (((this.fConst463 * this.fRec103[1]) + (this.fConst472 * this.fRec103[0])) + (this.fConst472 * this.fRec103[2]))) - (this.fConst460 * ((this.fConst473 * this.fRec102[2]) + (this.fConst474 * this.fRec102[1]))));
			var fTemp45 = (this.fConst460 * (((this.fConst461 * this.fRec102[1]) + (this.fConst475 * this.fRec102[0])) + (this.fConst475 * this.fRec102[2])));
			this.fRec101[0] = (fTemp45 - (this.fConst457 * ((this.fConst476 * this.fRec101[2]) + (this.fConst478 * this.fRec101[1]))));
			this.fRec100[0] = ((this.fConst457 * (((this.fConst459 * this.fRec101[1]) + (this.fConst479 * this.fRec101[0])) + (this.fConst479 * this.fRec101[2]))) - (this.fConst454 * ((this.fConst480 * this.fRec100[2]) + (this.fConst481 * this.fRec100[1]))));
			this.fRec99[0] = ((this.fConst454 * (((this.fConst456 * this.fRec100[1]) + (this.fConst482 * this.fRec100[0])) + (this.fConst482 * this.fRec100[2]))) - (this.fConst450 * ((this.fConst483 * this.fRec99[2]) + (this.fConst484 * this.fRec99[1]))));
			this.fRec98[0] = ((fSlow1 * this.fRec98[1]) + (fSlow2 * Math.abs((this.fConst450 * (((this.fConst453 * this.fRec99[1]) + (this.fConst485 * this.fRec99[0])) + (this.fConst485 * this.fRec99[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec98[0]))));
			this.fRec111[0] = (fTemp45 - (this.fConst502 * ((this.fConst505 * this.fRec111[2]) + (this.fConst506 * this.fRec111[1]))));
			this.fRec110[0] = ((this.fConst502 * (((this.fConst504 * this.fRec111[1]) + (this.fConst507 * this.fRec111[0])) + (this.fConst507 * this.fRec111[2]))) - (this.fConst500 * ((this.fConst508 * this.fRec110[2]) + (this.fConst509 * this.fRec110[1]))));
			this.fRec109[0] = ((this.fConst500 * (((this.fConst501 * this.fRec110[1]) + (this.fConst510 * this.fRec110[0])) + (this.fConst510 * this.fRec110[2]))) - (this.fConst498 * ((this.fConst511 * this.fRec109[2]) + (this.fConst512 * this.fRec109[1]))));
			var fTemp46 = (this.fConst498 * (((this.fConst499 * this.fRec109[1]) + (this.fConst513 * this.fRec109[0])) + (this.fConst513 * this.fRec109[2])));
			this.fRec108[0] = (fTemp46 - (this.fConst495 * ((this.fConst514 * this.fRec108[2]) + (this.fConst516 * this.fRec108[1]))));
			this.fRec107[0] = ((this.fConst495 * (((this.fConst497 * this.fRec108[1]) + (this.fConst517 * this.fRec108[0])) + (this.fConst517 * this.fRec108[2]))) - (this.fConst492 * ((this.fConst518 * this.fRec107[2]) + (this.fConst519 * this.fRec107[1]))));
			this.fRec106[0] = ((this.fConst492 * (((this.fConst494 * this.fRec107[1]) + (this.fConst520 * this.fRec107[0])) + (this.fConst520 * this.fRec107[2]))) - (this.fConst488 * ((this.fConst521 * this.fRec106[2]) + (this.fConst522 * this.fRec106[1]))));
			this.fRec105[0] = ((fSlow1 * this.fRec105[1]) + (fSlow2 * Math.abs((this.fConst488 * (((this.fConst491 * this.fRec106[1]) + (this.fConst523 * this.fRec106[0])) + (this.fConst523 * this.fRec106[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec105[0]))));
			this.fRec115[0] = (fTemp46 - (this.fConst528 * ((this.fConst531 * this.fRec115[2]) + (this.fConst532 * this.fRec115[1]))));
			this.fRec114[0] = ((this.fConst528 * (((this.fConst530 * this.fRec115[1]) + (this.fConst533 * this.fRec115[0])) + (this.fConst533 * this.fRec115[2]))) - (this.fConst526 * ((this.fConst534 * this.fRec114[2]) + (this.fConst535 * this.fRec114[1]))));
			this.fRec113[0] = ((this.fConst526 * (((this.fConst527 * this.fRec114[1]) + (this.fConst536 * this.fRec114[0])) + (this.fConst536 * this.fRec114[2]))) - (this.fConst524 * ((this.fConst537 * this.fRec113[2]) + (this.fConst538 * this.fRec113[1]))));
			this.fRec112[0] = ((fSlow1 * this.fRec112[1]) + (fSlow2 * Math.abs((this.fConst524 * (((this.fConst525 * this.fRec113[1]) + (this.fConst539 * this.fRec113[0])) + (this.fConst539 * this.fRec113[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec112[0]))));
			output0[i] = fTemp33;
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec35[1] = this.fRec35[0];
			this.fRec37[1] = this.fRec37[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec36[1] = this.fRec36[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec38[1] = this.fRec38[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec39[1] = this.fRec39[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.iRec40[1] = this.iRec40[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec41[j1] = this.fRec41[(j1 - 1)];
				
			}
			this.fVec22[1] = this.fVec22[0];
			this.fRec34[1] = this.fRec34[0];
			this.fVec23[1] = this.fVec23[0];
			this.fRec33[1] = this.fRec33[0];
			this.fVec24[1] = this.fVec24[0];
			this.fRec32[1] = this.fRec32[0];
			this.fVec25[1] = this.fVec25[0];
			this.fRec31[1] = this.fRec31[0];
			this.fVec26[1] = this.fVec26[0];
			this.fRec30[1] = this.fRec30[0];
			this.fVec27[1] = this.fVec27[0];
			this.fRec29[1] = this.fRec29[0];
			this.fVec28[1] = this.fVec28[0];
			this.fRec28[1] = this.fRec28[0];
			this.fVec29[1] = this.fVec29[0];
			this.fRec27[1] = this.fRec27[0];
			this.fVec30[1] = this.fVec30[0];
			this.fRec26[1] = this.fRec26[0];
			this.fVec31[1] = this.fVec31[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec24[2] = this.fRec24[1];
			this.fRec24[1] = this.fRec24[0];
			this.fRec23[2] = this.fRec23[1];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[2] = this.fRec22[1];
			this.fRec22[1] = this.fRec22[0];
			this.fRec21[2] = this.fRec21[1];
			this.fRec21[1] = this.fRec21[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fRec19[2] = this.fRec19[1];
			this.fRec19[1] = this.fRec19[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec17[2] = this.fRec17[1];
			this.fRec17[1] = this.fRec17[0];
			this.fRec16[2] = this.fRec16[1];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[2] = this.fRec15[1];
			this.fRec15[1] = this.fRec15[0];
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.fRec13[2] = this.fRec13[1];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.fRec9[2] = this.fRec9[1];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[2] = this.fRec8[1];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[2] = this.fRec7[1];
			this.fRec7[1] = this.fRec7[0];
			this.fRec6[2] = this.fRec6[1];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[2] = this.fRec5[1];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[2] = this.fRec4[1];
			this.fRec4[1] = this.fRec4[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[2] = this.fRec44[1];
			this.fRec44[1] = this.fRec44[0];
			this.fRec43[2] = this.fRec43[1];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[1] = this.fRec42[0];
			this.fRec49[2] = this.fRec49[1];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[2] = this.fRec48[1];
			this.fRec48[1] = this.fRec48[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[1] = this.fRec46[0];
			this.fRec53[2] = this.fRec53[1];
			this.fRec53[1] = this.fRec53[0];
			this.fRec52[2] = this.fRec52[1];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[2] = this.fRec51[1];
			this.fRec51[1] = this.fRec51[0];
			this.fRec50[1] = this.fRec50[0];
			this.fRec57[2] = this.fRec57[1];
			this.fRec57[1] = this.fRec57[0];
			this.fRec56[2] = this.fRec56[1];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[2] = this.fRec55[1];
			this.fRec55[1] = this.fRec55[0];
			this.fRec54[1] = this.fRec54[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fRec60[2] = this.fRec60[1];
			this.fRec60[1] = this.fRec60[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[1] = this.fRec58[0];
			this.fRec65[2] = this.fRec65[1];
			this.fRec65[1] = this.fRec65[0];
			this.fRec64[2] = this.fRec64[1];
			this.fRec64[1] = this.fRec64[0];
			this.fRec63[2] = this.fRec63[1];
			this.fRec63[1] = this.fRec63[0];
			this.fRec62[1] = this.fRec62[0];
			this.fRec69[2] = this.fRec69[1];
			this.fRec69[1] = this.fRec69[0];
			this.fRec68[2] = this.fRec68[1];
			this.fRec68[1] = this.fRec68[0];
			this.fRec67[2] = this.fRec67[1];
			this.fRec67[1] = this.fRec67[0];
			this.fRec66[1] = this.fRec66[0];
			this.fRec76[2] = this.fRec76[1];
			this.fRec76[1] = this.fRec76[0];
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
			this.fRec70[1] = this.fRec70[0];
			this.fRec83[2] = this.fRec83[1];
			this.fRec83[1] = this.fRec83[0];
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
			this.fRec77[1] = this.fRec77[0];
			this.fRec90[2] = this.fRec90[1];
			this.fRec90[1] = this.fRec90[0];
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
			this.fRec84[1] = this.fRec84[0];
			this.fRec97[2] = this.fRec97[1];
			this.fRec97[1] = this.fRec97[0];
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
			this.fRec91[1] = this.fRec91[0];
			this.fRec104[2] = this.fRec104[1];
			this.fRec104[1] = this.fRec104[0];
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
			this.fRec98[1] = this.fRec98[0];
			this.fRec111[2] = this.fRec111[1];
			this.fRec111[1] = this.fRec111[0];
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
			this.fRec105[1] = this.fRec105[0];
			this.fRec115[2] = this.fRec115[1];
			this.fRec115[1] = this.fRec115[0];
			this.fRec114[2] = this.fRec114[1];
			this.fRec114[1] = this.fRec114[0];
			this.fRec113[2] = this.fRec113[1];
			this.fRec113[1] = this.fRec113[0];
			this.fRec112[1] = this.fRec112[0];
			
		}
		
	}
	
}

