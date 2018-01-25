
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}
this.mydsp_faustpower3_f = function(value) {
	return ((value * value) * value);
	
}
this.max_i = function(dummy0, dummy1);

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
	this.fConst14;
	this.fConst15;
	this.fHslider3;
	this.fHslider4;
	this.fVslider0;
	this.fRec8 = new Float32Array(2);
	this.fCheckbox2;
	this.fCheckbox3;
	this.fEntry0;
	this.fVslider1;
	this.fVslider2;
	this.fRec10 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec9 = new Float32Array(2);
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
	this.fRec11 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec12 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fCheckbox4;
	this.iRec13 = new Int32Array(2);
	this.fRec14 = new Float32Array(4);
	this.fRec18 = new Float32Array(2);
	this.fHslider5;
	this.iVec22 = new Int32Array(2);
	this.fHslider6;
	this.iRec19 = new Int32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fHbargraph0;
	this.fRec7 = new Float32Array(2);
	this.iVec23 = new Int32Array(2);
	this.iRec20 = new Int32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fRec4 = new Float32Array(2);
	this.fConst19;
	this.fHslider7;
	this.fHslider8;
	this.fHslider9;
	this.fRec23 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fHslider10;
	this.fRec21 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fRec25 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.fHbargraph1;
	this.fConst20;
	this.fConst21;
	this.fConst22;
	this.fRec3 = new Float32Array(3);
	this.fConst23;
	this.fConst24;
	this.fConst25;
	this.fRec2 = new Float32Array(3);
	this.fConst26;
	this.fConst27;
	this.fConst28;
	this.fRec1 = new Float32Array(3);
	this.fConst29;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
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
	this.fRec33 = new Float32Array(3);
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fRec32 = new Float32Array(3);
	this.fConst54;
	this.fConst55;
	this.fConst56;
	this.fRec31 = new Float32Array(3);
	this.fConst57;
	this.fConst58;
	this.fConst59;
	this.fConst60;
	this.fRec30 = new Float32Array(3);
	this.fConst61;
	this.fConst62;
	this.fConst63;
	this.fRec29 = new Float32Array(3);
	this.fConst64;
	this.fConst65;
	this.fConst66;
	this.fRec28 = new Float32Array(3);
	this.fConst67;
	this.fRec27 = new Float32Array(2);
	this.fVbargraph1;
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
	this.fRec40 = new Float32Array(3);
	this.fConst89;
	this.fConst90;
	this.fConst91;
	this.fRec39 = new Float32Array(3);
	this.fConst92;
	this.fConst93;
	this.fConst94;
	this.fRec38 = new Float32Array(3);
	this.fConst95;
	this.fConst96;
	this.fConst97;
	this.fConst98;
	this.fRec37 = new Float32Array(3);
	this.fConst99;
	this.fConst100;
	this.fConst101;
	this.fRec36 = new Float32Array(3);
	this.fConst102;
	this.fConst103;
	this.fConst104;
	this.fRec35 = new Float32Array(3);
	this.fConst105;
	this.fRec34 = new Float32Array(2);
	this.fVbargraph2;
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
	this.fConst126;
	this.fRec47 = new Float32Array(3);
	this.fConst127;
	this.fConst128;
	this.fConst129;
	this.fRec46 = new Float32Array(3);
	this.fConst130;
	this.fConst131;
	this.fConst132;
	this.fRec45 = new Float32Array(3);
	this.fConst133;
	this.fConst134;
	this.fConst135;
	this.fConst136;
	this.fRec44 = new Float32Array(3);
	this.fConst137;
	this.fConst138;
	this.fConst139;
	this.fRec43 = new Float32Array(3);
	this.fConst140;
	this.fConst141;
	this.fConst142;
	this.fRec42 = new Float32Array(3);
	this.fConst143;
	this.fRec41 = new Float32Array(2);
	this.fVbargraph3;
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
	this.fConst164;
	this.fRec54 = new Float32Array(3);
	this.fConst165;
	this.fConst166;
	this.fConst167;
	this.fRec53 = new Float32Array(3);
	this.fConst168;
	this.fConst169;
	this.fConst170;
	this.fRec52 = new Float32Array(3);
	this.fConst171;
	this.fConst172;
	this.fConst173;
	this.fConst174;
	this.fRec51 = new Float32Array(3);
	this.fConst175;
	this.fConst176;
	this.fConst177;
	this.fRec50 = new Float32Array(3);
	this.fConst178;
	this.fConst179;
	this.fConst180;
	this.fRec49 = new Float32Array(3);
	this.fConst181;
	this.fRec48 = new Float32Array(2);
	this.fVbargraph4;
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
	this.fConst202;
	this.fRec61 = new Float32Array(3);
	this.fConst203;
	this.fConst204;
	this.fConst205;
	this.fRec60 = new Float32Array(3);
	this.fConst206;
	this.fConst207;
	this.fConst208;
	this.fRec59 = new Float32Array(3);
	this.fConst209;
	this.fConst210;
	this.fConst211;
	this.fConst212;
	this.fRec58 = new Float32Array(3);
	this.fConst213;
	this.fConst214;
	this.fConst215;
	this.fRec57 = new Float32Array(3);
	this.fConst216;
	this.fConst217;
	this.fConst218;
	this.fRec56 = new Float32Array(3);
	this.fConst219;
	this.fRec55 = new Float32Array(2);
	this.fVbargraph5;
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
	this.fConst240;
	this.fRec68 = new Float32Array(3);
	this.fConst241;
	this.fConst242;
	this.fConst243;
	this.fRec67 = new Float32Array(3);
	this.fConst244;
	this.fConst245;
	this.fConst246;
	this.fRec66 = new Float32Array(3);
	this.fConst247;
	this.fConst248;
	this.fConst249;
	this.fConst250;
	this.fRec65 = new Float32Array(3);
	this.fConst251;
	this.fConst252;
	this.fConst253;
	this.fRec64 = new Float32Array(3);
	this.fConst254;
	this.fConst255;
	this.fConst256;
	this.fRec63 = new Float32Array(3);
	this.fConst257;
	this.fRec62 = new Float32Array(2);
	this.fVbargraph6;
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
	this.fConst278;
	this.fRec75 = new Float32Array(3);
	this.fConst279;
	this.fConst280;
	this.fConst281;
	this.fRec74 = new Float32Array(3);
	this.fConst282;
	this.fConst283;
	this.fConst284;
	this.fRec73 = new Float32Array(3);
	this.fConst285;
	this.fConst286;
	this.fConst287;
	this.fConst288;
	this.fRec72 = new Float32Array(3);
	this.fConst289;
	this.fConst290;
	this.fConst291;
	this.fRec71 = new Float32Array(3);
	this.fConst292;
	this.fConst293;
	this.fConst294;
	this.fRec70 = new Float32Array(3);
	this.fConst295;
	this.fRec69 = new Float32Array(2);
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
	this.fRec82 = new Float32Array(3);
	this.fConst317;
	this.fConst318;
	this.fConst319;
	this.fRec81 = new Float32Array(3);
	this.fConst320;
	this.fConst321;
	this.fConst322;
	this.fRec80 = new Float32Array(3);
	this.fConst323;
	this.fConst324;
	this.fConst325;
	this.fConst326;
	this.fRec79 = new Float32Array(3);
	this.fConst327;
	this.fConst328;
	this.fConst329;
	this.fRec78 = new Float32Array(3);
	this.fConst330;
	this.fConst331;
	this.fConst332;
	this.fRec77 = new Float32Array(3);
	this.fConst333;
	this.fRec76 = new Float32Array(2);
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
	this.fRec89 = new Float32Array(3);
	this.fConst355;
	this.fConst356;
	this.fConst357;
	this.fRec88 = new Float32Array(3);
	this.fConst358;
	this.fConst359;
	this.fConst360;
	this.fRec87 = new Float32Array(3);
	this.fConst361;
	this.fConst362;
	this.fConst363;
	this.fConst364;
	this.fRec86 = new Float32Array(3);
	this.fConst365;
	this.fConst366;
	this.fConst367;
	this.fRec85 = new Float32Array(3);
	this.fConst368;
	this.fConst369;
	this.fConst370;
	this.fRec84 = new Float32Array(3);
	this.fConst371;
	this.fRec83 = new Float32Array(2);
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
	this.fRec96 = new Float32Array(3);
	this.fConst393;
	this.fConst394;
	this.fConst395;
	this.fRec95 = new Float32Array(3);
	this.fConst396;
	this.fConst397;
	this.fConst398;
	this.fRec94 = new Float32Array(3);
	this.fConst399;
	this.fConst400;
	this.fConst401;
	this.fConst402;
	this.fRec93 = new Float32Array(3);
	this.fConst403;
	this.fConst404;
	this.fConst405;
	this.fRec92 = new Float32Array(3);
	this.fConst406;
	this.fConst407;
	this.fConst408;
	this.fRec91 = new Float32Array(3);
	this.fConst409;
	this.fRec90 = new Float32Array(2);
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
	this.fRec103 = new Float32Array(3);
	this.fConst431;
	this.fConst432;
	this.fConst433;
	this.fRec102 = new Float32Array(3);
	this.fConst434;
	this.fConst435;
	this.fConst436;
	this.fRec101 = new Float32Array(3);
	this.fConst437;
	this.fConst438;
	this.fConst439;
	this.fConst440;
	this.fRec100 = new Float32Array(3);
	this.fConst441;
	this.fConst442;
	this.fConst443;
	this.fRec99 = new Float32Array(3);
	this.fConst444;
	this.fConst445;
	this.fConst446;
	this.fRec98 = new Float32Array(3);
	this.fConst447;
	this.fRec97 = new Float32Array(2);
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
	this.fRec110 = new Float32Array(3);
	this.fConst469;
	this.fConst470;
	this.fConst471;
	this.fRec109 = new Float32Array(3);
	this.fConst472;
	this.fConst473;
	this.fConst474;
	this.fRec108 = new Float32Array(3);
	this.fConst475;
	this.fConst476;
	this.fConst477;
	this.fConst478;
	this.fRec107 = new Float32Array(3);
	this.fConst479;
	this.fConst480;
	this.fConst481;
	this.fRec106 = new Float32Array(3);
	this.fConst482;
	this.fConst483;
	this.fConst484;
	this.fRec105 = new Float32Array(3);
	this.fConst485;
	this.fRec104 = new Float32Array(2);
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
	this.fRec117 = new Float32Array(3);
	this.fConst507;
	this.fConst508;
	this.fConst509;
	this.fRec116 = new Float32Array(3);
	this.fConst510;
	this.fConst511;
	this.fConst512;
	this.fRec115 = new Float32Array(3);
	this.fConst513;
	this.fConst514;
	this.fConst515;
	this.fConst516;
	this.fRec114 = new Float32Array(3);
	this.fConst517;
	this.fConst518;
	this.fConst519;
	this.fRec113 = new Float32Array(3);
	this.fConst520;
	this.fConst521;
	this.fConst522;
	this.fRec112 = new Float32Array(3);
	this.fConst523;
	this.fRec111 = new Float32Array(2);
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
	this.fRec121 = new Float32Array(3);
	this.fConst533;
	this.fConst534;
	this.fConst535;
	this.fRec120 = new Float32Array(3);
	this.fConst536;
	this.fConst537;
	this.fConst538;
	this.fRec119 = new Float32Array(3);
	this.fConst539;
	this.fRec118 = new Float32Array(2);
	this.fVbargraph14;
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("compressors.lib/name", "Faust Compressor Effect Library");
		m.declare("compressors.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("misceffects.lib/name", "Faust Math Library");
		m.declare("misceffects.lib/version", "2.0");
		m.declare("name", "gateCompressor");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
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
		this.fConst13 = (this.fConst12 + 0.000407678);
		this.fConst14 = (1 / this.fConst0);
		this.fConst15 = (1 / this.fConst0);
		this.fConst16 = (0.25 * this.fConst0);
		this.fConst17 = (0.0416667 * mydsp_faustpower2_f(this.fConst0));
		this.fConst18 = (0.00520833 * mydsp_faustpower3_f(this.fConst0));
		this.fConst19 = (2 / this.fConst0);
		this.fConst20 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst21 = (1 / this.fConst5);
		this.fConst22 = (2 * (4.07678 - this.fConst21));
		this.fConst23 = (2 * (0.000407678 - this.fConst12));
		this.fConst24 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst25 = (2 * (1.45007 - this.fConst21));
		this.fConst26 = (this.fConst9 + 1.45007);
		this.fConst27 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst28 = (2 * (0.93514 - this.fConst21));
		this.fConst29 = (this.fConst6 + 0.93514);
		this.fConst30 = Math.tan((31665.3 / this.fConst0));
		this.fConst31 = (1 / this.fConst30);
		this.fConst32 = (1 / (((this.fConst31 + 0.157482) / this.fConst30) + 0.93514));
		this.fConst33 = mydsp_faustpower2_f(this.fConst30);
		this.fConst34 = (50.0638 / this.fConst33);
		this.fConst35 = (2 * (0.93514 - this.fConst34));
		this.fConst36 = (1 / (((this.fConst31 + 0.74313) / this.fConst30) + 1.45007));
		this.fConst37 = (11.0521 / this.fConst33);
		this.fConst38 = (2 * (1.45007 - this.fConst37));
		this.fConst39 = (1 / (((this.fConst31 + 3.18973) / this.fConst30) + 4.07678));
		this.fConst40 = (0.00176617 / this.fConst33);
		this.fConst41 = (2 * (0.000407678 - this.fConst40));
		this.fConst42 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst43 = (2 * (53.5362 - this.fConst21));
		this.fConst44 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst45 = (2 * (7.62173 - this.fConst21));
		this.fConst46 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst47 = (0.0001 / this.fConst5);
		this.fConst48 = (2 * (0.000433227 - this.fConst47));
		this.fConst49 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst50 = (2 * (0.245292 - this.fConst21));
		this.fConst51 = (this.fConst47 + 0.000433227);
		this.fConst52 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst53 = (2 * (0.689621 - this.fConst21));
		this.fConst54 = (this.fConst21 + 7.62173);
		this.fConst55 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst56 = (2 * (1.06936 - this.fConst21));
		this.fConst57 = (this.fConst21 + 53.5362);
		this.fConst58 = (((this.fConst31 + -3.18973) / this.fConst30) + 4.07678);
		this.fConst59 = (1 / this.fConst33);
		this.fConst60 = (2 * (4.07678 - this.fConst59));
		this.fConst61 = (this.fConst40 + 0.000407678);
		this.fConst62 = (((this.fConst31 + -0.74313) / this.fConst30) + 1.45007);
		this.fConst63 = (2 * (1.45007 - this.fConst59));
		this.fConst64 = (this.fConst37 + 1.45007);
		this.fConst65 = (((this.fConst31 + -0.157482) / this.fConst30) + 0.93514);
		this.fConst66 = (2 * (0.93514 - this.fConst59));
		this.fConst67 = (this.fConst34 + 0.93514);
		this.fConst68 = Math.tan((19947.9 / this.fConst0));
		this.fConst69 = (1 / this.fConst68);
		this.fConst70 = (1 / (((this.fConst69 + 0.157482) / this.fConst68) + 0.93514));
		this.fConst71 = mydsp_faustpower2_f(this.fConst68);
		this.fConst72 = (50.0638 / this.fConst71);
		this.fConst73 = (2 * (0.93514 - this.fConst72));
		this.fConst74 = (1 / (((this.fConst69 + 0.74313) / this.fConst68) + 1.45007));
		this.fConst75 = (11.0521 / this.fConst71);
		this.fConst76 = (2 * (1.45007 - this.fConst75));
		this.fConst77 = (1 / (((this.fConst69 + 3.18973) / this.fConst68) + 4.07678));
		this.fConst78 = (0.00176617 / this.fConst71);
		this.fConst79 = (2 * (0.000407678 - this.fConst78));
		this.fConst80 = (1 / (((this.fConst31 + 0.168405) / this.fConst30) + 1.06936));
		this.fConst81 = (2 * (53.5362 - this.fConst59));
		this.fConst82 = (1 / (((this.fConst31 + 0.512479) / this.fConst30) + 0.689621));
		this.fConst83 = (2 * (7.62173 - this.fConst59));
		this.fConst84 = (1 / (((this.fConst31 + 0.782413) / this.fConst30) + 0.245292));
		this.fConst85 = (0.0001 / this.fConst33);
		this.fConst86 = (2 * (0.000433227 - this.fConst85));
		this.fConst87 = (((this.fConst31 + -0.782413) / this.fConst30) + 0.245292);
		this.fConst88 = (2 * (0.245292 - this.fConst59));
		this.fConst89 = (this.fConst85 + 0.000433227);
		this.fConst90 = (((this.fConst31 + -0.512479) / this.fConst30) + 0.689621);
		this.fConst91 = (2 * (0.689621 - this.fConst59));
		this.fConst92 = (this.fConst59 + 7.62173);
		this.fConst93 = (((this.fConst31 + -0.168405) / this.fConst30) + 1.06936);
		this.fConst94 = (2 * (1.06936 - this.fConst59));
		this.fConst95 = (this.fConst59 + 53.5362);
		this.fConst96 = (((this.fConst69 + -3.18973) / this.fConst68) + 4.07678);
		this.fConst97 = (1 / this.fConst71);
		this.fConst98 = (2 * (4.07678 - this.fConst97));
		this.fConst99 = (this.fConst78 + 0.000407678);
		this.fConst100 = (((this.fConst69 + -0.74313) / this.fConst68) + 1.45007);
		this.fConst101 = (2 * (1.45007 - this.fConst97));
		this.fConst102 = (this.fConst75 + 1.45007);
		this.fConst103 = (((this.fConst69 + -0.157482) / this.fConst68) + 0.93514);
		this.fConst104 = (2 * (0.93514 - this.fConst97));
		this.fConst105 = (this.fConst72 + 0.93514);
		this.fConst106 = Math.tan((12566.4 / this.fConst0));
		this.fConst107 = (1 / this.fConst106);
		this.fConst108 = (1 / (((this.fConst107 + 0.157482) / this.fConst106) + 0.93514));
		this.fConst109 = mydsp_faustpower2_f(this.fConst106);
		this.fConst110 = (50.0638 / this.fConst109);
		this.fConst111 = (2 * (0.93514 - this.fConst110));
		this.fConst112 = (1 / (((this.fConst107 + 0.74313) / this.fConst106) + 1.45007));
		this.fConst113 = (11.0521 / this.fConst109);
		this.fConst114 = (2 * (1.45007 - this.fConst113));
		this.fConst115 = (1 / (((this.fConst107 + 3.18973) / this.fConst106) + 4.07678));
		this.fConst116 = (0.00176617 / this.fConst109);
		this.fConst117 = (2 * (0.000407678 - this.fConst116));
		this.fConst118 = (1 / (((this.fConst69 + 0.168405) / this.fConst68) + 1.06936));
		this.fConst119 = (2 * (53.5362 - this.fConst97));
		this.fConst120 = (1 / (((this.fConst69 + 0.512479) / this.fConst68) + 0.689621));
		this.fConst121 = (2 * (7.62173 - this.fConst97));
		this.fConst122 = (1 / (((this.fConst69 + 0.782413) / this.fConst68) + 0.245292));
		this.fConst123 = (0.0001 / this.fConst71);
		this.fConst124 = (2 * (0.000433227 - this.fConst123));
		this.fConst125 = (((this.fConst69 + -0.782413) / this.fConst68) + 0.245292);
		this.fConst126 = (2 * (0.245292 - this.fConst97));
		this.fConst127 = (this.fConst123 + 0.000433227);
		this.fConst128 = (((this.fConst69 + -0.512479) / this.fConst68) + 0.689621);
		this.fConst129 = (2 * (0.689621 - this.fConst97));
		this.fConst130 = (this.fConst97 + 7.62173);
		this.fConst131 = (((this.fConst69 + -0.168405) / this.fConst68) + 1.06936);
		this.fConst132 = (2 * (1.06936 - this.fConst97));
		this.fConst133 = (this.fConst97 + 53.5362);
		this.fConst134 = (((this.fConst107 + -3.18973) / this.fConst106) + 4.07678);
		this.fConst135 = (1 / this.fConst109);
		this.fConst136 = (2 * (4.07678 - this.fConst135));
		this.fConst137 = (this.fConst116 + 0.000407678);
		this.fConst138 = (((this.fConst107 + -0.74313) / this.fConst106) + 1.45007);
		this.fConst139 = (2 * (1.45007 - this.fConst135));
		this.fConst140 = (this.fConst113 + 1.45007);
		this.fConst141 = (((this.fConst107 + -0.157482) / this.fConst106) + 0.93514);
		this.fConst142 = (2 * (0.93514 - this.fConst135));
		this.fConst143 = (this.fConst110 + 0.93514);
		this.fConst144 = Math.tan((7916.32 / this.fConst0));
		this.fConst145 = (1 / this.fConst144);
		this.fConst146 = (1 / (((this.fConst145 + 0.157482) / this.fConst144) + 0.93514));
		this.fConst147 = mydsp_faustpower2_f(this.fConst144);
		this.fConst148 = (50.0638 / this.fConst147);
		this.fConst149 = (2 * (0.93514 - this.fConst148));
		this.fConst150 = (1 / (((this.fConst145 + 0.74313) / this.fConst144) + 1.45007));
		this.fConst151 = (11.0521 / this.fConst147);
		this.fConst152 = (2 * (1.45007 - this.fConst151));
		this.fConst153 = (1 / (((this.fConst145 + 3.18973) / this.fConst144) + 4.07678));
		this.fConst154 = (0.00176617 / this.fConst147);
		this.fConst155 = (2 * (0.000407678 - this.fConst154));
		this.fConst156 = (1 / (((this.fConst107 + 0.168405) / this.fConst106) + 1.06936));
		this.fConst157 = (2 * (53.5362 - this.fConst135));
		this.fConst158 = (1 / (((this.fConst107 + 0.512479) / this.fConst106) + 0.689621));
		this.fConst159 = (2 * (7.62173 - this.fConst135));
		this.fConst160 = (1 / (((this.fConst107 + 0.782413) / this.fConst106) + 0.245292));
		this.fConst161 = (0.0001 / this.fConst109);
		this.fConst162 = (2 * (0.000433227 - this.fConst161));
		this.fConst163 = (((this.fConst107 + -0.782413) / this.fConst106) + 0.245292);
		this.fConst164 = (2 * (0.245292 - this.fConst135));
		this.fConst165 = (this.fConst161 + 0.000433227);
		this.fConst166 = (((this.fConst107 + -0.512479) / this.fConst106) + 0.689621);
		this.fConst167 = (2 * (0.689621 - this.fConst135));
		this.fConst168 = (this.fConst135 + 7.62173);
		this.fConst169 = (((this.fConst107 + -0.168405) / this.fConst106) + 1.06936);
		this.fConst170 = (2 * (1.06936 - this.fConst135));
		this.fConst171 = (this.fConst135 + 53.5362);
		this.fConst172 = (((this.fConst145 + -3.18973) / this.fConst144) + 4.07678);
		this.fConst173 = (1 / this.fConst147);
		this.fConst174 = (2 * (4.07678 - this.fConst173));
		this.fConst175 = (this.fConst154 + 0.000407678);
		this.fConst176 = (((this.fConst145 + -0.74313) / this.fConst144) + 1.45007);
		this.fConst177 = (2 * (1.45007 - this.fConst173));
		this.fConst178 = (this.fConst151 + 1.45007);
		this.fConst179 = (((this.fConst145 + -0.157482) / this.fConst144) + 0.93514);
		this.fConst180 = (2 * (0.93514 - this.fConst173));
		this.fConst181 = (this.fConst148 + 0.93514);
		this.fConst182 = Math.tan((4986.97 / this.fConst0));
		this.fConst183 = (1 / this.fConst182);
		this.fConst184 = (1 / (((this.fConst183 + 0.157482) / this.fConst182) + 0.93514));
		this.fConst185 = mydsp_faustpower2_f(this.fConst182);
		this.fConst186 = (50.0638 / this.fConst185);
		this.fConst187 = (2 * (0.93514 - this.fConst186));
		this.fConst188 = (1 / (((this.fConst183 + 0.74313) / this.fConst182) + 1.45007));
		this.fConst189 = (11.0521 / this.fConst185);
		this.fConst190 = (2 * (1.45007 - this.fConst189));
		this.fConst191 = (1 / (((this.fConst183 + 3.18973) / this.fConst182) + 4.07678));
		this.fConst192 = (0.00176617 / this.fConst185);
		this.fConst193 = (2 * (0.000407678 - this.fConst192));
		this.fConst194 = (1 / (((this.fConst145 + 0.168405) / this.fConst144) + 1.06936));
		this.fConst195 = (2 * (53.5362 - this.fConst173));
		this.fConst196 = (1 / (((this.fConst145 + 0.512479) / this.fConst144) + 0.689621));
		this.fConst197 = (2 * (7.62173 - this.fConst173));
		this.fConst198 = (1 / (((this.fConst145 + 0.782413) / this.fConst144) + 0.245292));
		this.fConst199 = (0.0001 / this.fConst147);
		this.fConst200 = (2 * (0.000433227 - this.fConst199));
		this.fConst201 = (((this.fConst145 + -0.782413) / this.fConst144) + 0.245292);
		this.fConst202 = (2 * (0.245292 - this.fConst173));
		this.fConst203 = (this.fConst199 + 0.000433227);
		this.fConst204 = (((this.fConst145 + -0.512479) / this.fConst144) + 0.689621);
		this.fConst205 = (2 * (0.689621 - this.fConst173));
		this.fConst206 = (this.fConst173 + 7.62173);
		this.fConst207 = (((this.fConst145 + -0.168405) / this.fConst144) + 1.06936);
		this.fConst208 = (2 * (1.06936 - this.fConst173));
		this.fConst209 = (this.fConst173 + 53.5362);
		this.fConst210 = (((this.fConst183 + -3.18973) / this.fConst182) + 4.07678);
		this.fConst211 = (1 / this.fConst185);
		this.fConst212 = (2 * (4.07678 - this.fConst211));
		this.fConst213 = (this.fConst192 + 0.000407678);
		this.fConst214 = (((this.fConst183 + -0.74313) / this.fConst182) + 1.45007);
		this.fConst215 = (2 * (1.45007 - this.fConst211));
		this.fConst216 = (this.fConst189 + 1.45007);
		this.fConst217 = (((this.fConst183 + -0.157482) / this.fConst182) + 0.93514);
		this.fConst218 = (2 * (0.93514 - this.fConst211));
		this.fConst219 = (this.fConst186 + 0.93514);
		this.fConst220 = Math.tan((3141.59 / this.fConst0));
		this.fConst221 = (1 / this.fConst220);
		this.fConst222 = (1 / (((this.fConst221 + 0.157482) / this.fConst220) + 0.93514));
		this.fConst223 = mydsp_faustpower2_f(this.fConst220);
		this.fConst224 = (50.0638 / this.fConst223);
		this.fConst225 = (2 * (0.93514 - this.fConst224));
		this.fConst226 = (1 / (((this.fConst221 + 0.74313) / this.fConst220) + 1.45007));
		this.fConst227 = (11.0521 / this.fConst223);
		this.fConst228 = (2 * (1.45007 - this.fConst227));
		this.fConst229 = (1 / (((this.fConst221 + 3.18973) / this.fConst220) + 4.07678));
		this.fConst230 = (0.00176617 / this.fConst223);
		this.fConst231 = (2 * (0.000407678 - this.fConst230));
		this.fConst232 = (1 / (((this.fConst183 + 0.168405) / this.fConst182) + 1.06936));
		this.fConst233 = (2 * (53.5362 - this.fConst211));
		this.fConst234 = (1 / (((this.fConst183 + 0.512479) / this.fConst182) + 0.689621));
		this.fConst235 = (2 * (7.62173 - this.fConst211));
		this.fConst236 = (1 / (((this.fConst183 + 0.782413) / this.fConst182) + 0.245292));
		this.fConst237 = (0.0001 / this.fConst185);
		this.fConst238 = (2 * (0.000433227 - this.fConst237));
		this.fConst239 = (((this.fConst183 + -0.782413) / this.fConst182) + 0.245292);
		this.fConst240 = (2 * (0.245292 - this.fConst211));
		this.fConst241 = (this.fConst237 + 0.000433227);
		this.fConst242 = (((this.fConst183 + -0.512479) / this.fConst182) + 0.689621);
		this.fConst243 = (2 * (0.689621 - this.fConst211));
		this.fConst244 = (this.fConst211 + 7.62173);
		this.fConst245 = (((this.fConst183 + -0.168405) / this.fConst182) + 1.06936);
		this.fConst246 = (2 * (1.06936 - this.fConst211));
		this.fConst247 = (this.fConst211 + 53.5362);
		this.fConst248 = (((this.fConst221 + -3.18973) / this.fConst220) + 4.07678);
		this.fConst249 = (1 / this.fConst223);
		this.fConst250 = (2 * (4.07678 - this.fConst249));
		this.fConst251 = (this.fConst230 + 0.000407678);
		this.fConst252 = (((this.fConst221 + -0.74313) / this.fConst220) + 1.45007);
		this.fConst253 = (2 * (1.45007 - this.fConst249));
		this.fConst254 = (this.fConst227 + 1.45007);
		this.fConst255 = (((this.fConst221 + -0.157482) / this.fConst220) + 0.93514);
		this.fConst256 = (2 * (0.93514 - this.fConst249));
		this.fConst257 = (this.fConst224 + 0.93514);
		this.fConst258 = Math.tan((1979.08 / this.fConst0));
		this.fConst259 = (1 / this.fConst258);
		this.fConst260 = (1 / (((this.fConst259 + 0.157482) / this.fConst258) + 0.93514));
		this.fConst261 = mydsp_faustpower2_f(this.fConst258);
		this.fConst262 = (50.0638 / this.fConst261);
		this.fConst263 = (2 * (0.93514 - this.fConst262));
		this.fConst264 = (1 / (((this.fConst259 + 0.74313) / this.fConst258) + 1.45007));
		this.fConst265 = (11.0521 / this.fConst261);
		this.fConst266 = (2 * (1.45007 - this.fConst265));
		this.fConst267 = (1 / (((this.fConst259 + 3.18973) / this.fConst258) + 4.07678));
		this.fConst268 = (0.00176617 / this.fConst261);
		this.fConst269 = (2 * (0.000407678 - this.fConst268));
		this.fConst270 = (1 / (((this.fConst221 + 0.168405) / this.fConst220) + 1.06936));
		this.fConst271 = (2 * (53.5362 - this.fConst249));
		this.fConst272 = (1 / (((this.fConst221 + 0.512479) / this.fConst220) + 0.689621));
		this.fConst273 = (2 * (7.62173 - this.fConst249));
		this.fConst274 = (1 / (((this.fConst221 + 0.782413) / this.fConst220) + 0.245292));
		this.fConst275 = (0.0001 / this.fConst223);
		this.fConst276 = (2 * (0.000433227 - this.fConst275));
		this.fConst277 = (((this.fConst221 + -0.782413) / this.fConst220) + 0.245292);
		this.fConst278 = (2 * (0.245292 - this.fConst249));
		this.fConst279 = (this.fConst275 + 0.000433227);
		this.fConst280 = (((this.fConst221 + -0.512479) / this.fConst220) + 0.689621);
		this.fConst281 = (2 * (0.689621 - this.fConst249));
		this.fConst282 = (this.fConst249 + 7.62173);
		this.fConst283 = (((this.fConst221 + -0.168405) / this.fConst220) + 1.06936);
		this.fConst284 = (2 * (1.06936 - this.fConst249));
		this.fConst285 = (this.fConst249 + 53.5362);
		this.fConst286 = (((this.fConst259 + -3.18973) / this.fConst258) + 4.07678);
		this.fConst287 = (1 / this.fConst261);
		this.fConst288 = (2 * (4.07678 - this.fConst287));
		this.fConst289 = (this.fConst268 + 0.000407678);
		this.fConst290 = (((this.fConst259 + -0.74313) / this.fConst258) + 1.45007);
		this.fConst291 = (2 * (1.45007 - this.fConst287));
		this.fConst292 = (this.fConst265 + 1.45007);
		this.fConst293 = (((this.fConst259 + -0.157482) / this.fConst258) + 0.93514);
		this.fConst294 = (2 * (0.93514 - this.fConst287));
		this.fConst295 = (this.fConst262 + 0.93514);
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
		this.fConst308 = (1 / (((this.fConst259 + 0.168405) / this.fConst258) + 1.06936));
		this.fConst309 = (2 * (53.5362 - this.fConst287));
		this.fConst310 = (1 / (((this.fConst259 + 0.512479) / this.fConst258) + 0.689621));
		this.fConst311 = (2 * (7.62173 - this.fConst287));
		this.fConst312 = (1 / (((this.fConst259 + 0.782413) / this.fConst258) + 0.245292));
		this.fConst313 = (0.0001 / this.fConst261);
		this.fConst314 = (2 * (0.000433227 - this.fConst313));
		this.fConst315 = (((this.fConst259 + -0.782413) / this.fConst258) + 0.245292);
		this.fConst316 = (2 * (0.245292 - this.fConst287));
		this.fConst317 = (this.fConst313 + 0.000433227);
		this.fConst318 = (((this.fConst259 + -0.512479) / this.fConst258) + 0.689621);
		this.fConst319 = (2 * (0.689621 - this.fConst287));
		this.fConst320 = (this.fConst287 + 7.62173);
		this.fConst321 = (((this.fConst259 + -0.168405) / this.fConst258) + 1.06936);
		this.fConst322 = (2 * (1.06936 - this.fConst287));
		this.fConst323 = (this.fConst287 + 53.5362);
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
		this.fHslider2 = 40;
		this.fCheckbox1 = 0;
		this.fHslider3 = 10;
		this.fHslider4 = 100;
		this.fVslider0 = -20;
		this.fCheckbox2 = 0;
		this.fCheckbox3 = 0;
		this.fEntry0 = 2;
		this.fVslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fCheckbox4 = 0;
		this.fHslider5 = -30;
		this.fHslider6 = 200;
		this.fHslider7 = 50;
		this.fHslider8 = 5;
		this.fHslider9 = 500;
		this.fHslider10 = -30;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec8[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec10[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec9[l4] = 0;
			
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
			this.fRec11[l12] = 0;
			
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
			this.fRec12[l20] = 0;
			
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
			this.iRec13[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			this.fRec14[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec18[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.iVec22[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.iRec19[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec16[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec15[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec7[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this.iVec23[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.iRec20[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec5[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec4[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			this.fRec23[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec22[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec21[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec26[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec25[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fRec24[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			this.fRec3[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			this.fRec2[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec1[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			this.fRec0[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec33[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec32[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec31[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec30[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec29[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec28[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec27[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec40[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			this.fRec39[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			this.fRec38[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec37[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec36[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec35[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			this.fRec34[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec47[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			this.fRec46[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			this.fRec45[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			this.fRec44[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec43[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec42[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			this.fRec41[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			this.fRec54[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			this.fRec53[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec52[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			this.fRec51[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec50[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec49[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			this.fRec48[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			this.fRec61[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			this.fRec60[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec59[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec58[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			this.fRec57[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec56[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			this.fRec55[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec68[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			this.fRec67[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec66[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			this.fRec65[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec64[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec63[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			this.fRec62[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			this.fRec75[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			this.fRec74[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec73[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec72[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec71[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec70[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			this.fRec69[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			this.fRec82[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			this.fRec81[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec80[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			this.fRec79[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec78[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec77[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			this.fRec76[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			this.fRec89[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			this.fRec88[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec87[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			this.fRec86[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			this.fRec85[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			this.fRec84[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			this.fRec83[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			this.fRec96[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			this.fRec95[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			this.fRec94[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			this.fRec93[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec92[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			this.fRec91[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			this.fRec90[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			this.fRec103[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			this.fRec102[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			this.fRec101[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			this.fRec100[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec99[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec98[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			this.fRec97[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			this.fRec110[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			this.fRec109[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			this.fRec108[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			this.fRec107[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			this.fRec106[l130] = 0;
			
		}
		for (var l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			this.fRec105[l131] = 0;
			
		}
		for (var l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			this.fRec104[l132] = 0;
			
		}
		for (var l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			this.fRec117[l133] = 0;
			
		}
		for (var l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			this.fRec116[l134] = 0;
			
		}
		for (var l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			this.fRec115[l135] = 0;
			
		}
		for (var l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			this.fRec114[l136] = 0;
			
		}
		for (var l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			this.fRec113[l137] = 0;
			
		}
		for (var l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			this.fRec112[l138] = 0;
			
		}
		for (var l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			this.fRec111[l139] = 0;
			
		}
		for (var l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			this.fRec121[l140] = 0;
			
		}
		for (var l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			this.fRec120[l141] = 0;
			
		}
		for (var l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			this.fRec119[l142] = 0;
			
		}
		for (var l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			this.fRec118[l143] = 0;
			
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
		ui_interface.openVerticalBox("gateCompressor");
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
		ui_interface.declare("0", "tooltip", "Reference:   http://en.wikipedia.org/wiki/Noise_gate");
		ui_interface.openVerticalBox("GATE");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox1", "0", "");
		ui_interface.declare("fCheckbox1", "tooltip", "When this is checked,   the gate has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph0", "1", "");
		ui_interface.declare("fHbargraph0", "tooltip", "Current gain of the  gate in dB");
		ui_interface.declare("fHbargraph0", "unit", "dB");
		ui_interface.addHorizontalBargraph("Gate Gain", function handler(obj) { function setval(val) { obj.fHbargraph0 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fHslider5", "1", "");
		ui_interface.declare("fHslider5", "style", "knob");
		ui_interface.declare("fHslider5", "tooltip", "When   the signal level falls below the Threshold (expressed in dB), the signal is   muted");
		ui_interface.declare("fHslider5", "unit", "dB");
		ui_interface.addHorizontalSlider("Threshold", function handler(obj) { function setval(val) { obj.fHslider5 = val; } return setval; }(this), -30, -120, 0, 0.1);
		ui_interface.declare("fHslider3", "2", "");
		ui_interface.declare("fHslider3", "scale", "log");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.declare("fHslider3", "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate  gain to go (exponentially) from 0 (muted) to 1 (unmuted)");
		ui_interface.declare("fHslider3", "unit", "us");
		ui_interface.addHorizontalSlider("Attack", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 10, 10, 10000, 1);
		ui_interface.declare("fHslider6", "3", "");
		ui_interface.declare("fHslider6", "scale", "log");
		ui_interface.declare("fHslider6", "style", "knob");
		ui_interface.declare("fHslider6", "tooltip", "Time in ms to keep the gate open (no muting) after the signal  level falls below the Threshold");
		ui_interface.declare("fHslider6", "unit", "ms");
		ui_interface.addHorizontalSlider("Hold", function handler(obj) { function setval(val) { obj.fHslider6 = val; } return setval; }(this), 200, 1, 1000, 1);
		ui_interface.declare("fHslider4", "4", "");
		ui_interface.declare("fHslider4", "scale", "log");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.declare("fHslider4", "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go  (exponentially) from 1 (unmuted) to 0 (muted)");
		ui_interface.declare("fHslider4", "unit", "ms");
		ui_interface.addHorizontalSlider("Release", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 100, 1, 1000, 1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "Reference:   http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface.openVerticalBox("COMPRESSOR");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the compressor   has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fHbargraph1", "1", "");
		ui_interface.declare("fHbargraph1", "tooltip", "Current gain of  the compressor in dB");
		ui_interface.declare("fHbargraph1", "unit", "dB");
		ui_interface.addHorizontalBargraph("Compressor Gain", function handler(obj) { function setval(val) { obj.fHbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("0", "3", "");
		ui_interface.openHorizontalBox("Compression Control");
		ui_interface.declare("fHslider8", "0", "");
		ui_interface.declare("fHslider8", "style", "knob");
		ui_interface.declare("fHslider8", "tooltip", "A compression Ratio of N means that for each N dB increase in input  signal level above Threshold, the output level goes up 1 dB");
		ui_interface.addHorizontalSlider("Ratio", function handler(obj) { function setval(val) { obj.fHslider8 = val; } return setval; }(this), 5, 1, 20, 0.1);
		ui_interface.declare("fHslider10", "1", "");
		ui_interface.declare("fHslider10", "style", "knob");
		ui_interface.declare("fHslider10", "tooltip", "When the signal level exceeds the Threshold (in dB), its level  is compressed according to the Ratio");
		ui_interface.declare("fHslider10", "unit", "dB");
		ui_interface.addHorizontalSlider("Threshold", function handler(obj) { function setval(val) { obj.fHslider10 = val; } return setval; }(this), -30, -100, 10, 0.1);
		ui_interface.closeBox();
		ui_interface.declare("0", "4", "");
		ui_interface.openHorizontalBox("Compression Response");
		ui_interface.declare("fHslider7", "1", "");
		ui_interface.declare("fHslider7", "scale", "log");
		ui_interface.declare("fHslider7", "style", "knob");
		ui_interface.declare("fHslider7", "unit", "ms");
		ui_interface.addHorizontalSlider("Attack     tooltip: Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new lower target level (the compression  `kicking in')]", function handler(obj) { function setval(val) { obj.fHslider7 = val; } return setval; }(this), 50, 1, 1000, 0.1);
		ui_interface.declare("fHslider9", "2", "");
		ui_interface.declare("fHslider9", "scale", "log");
		ui_interface.declare("fHslider9", "style", "knob");
		ui_interface.declare("fHslider9", "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain  to approach (exponentially) a new higher target level (the compression  'releasing')");
		ui_interface.declare("fHslider9", "unit", "ms");
		ui_interface.addHorizontalSlider("Release", function handler(obj) { function setval(val) { obj.fHslider9 = val; } return setval; }(this), 500, 1, 1000, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		ui_interface.declare("fHslider2", "5", "");
		ui_interface.declare("fHslider2", "tooltip", "The compressed-signal output level is increased by this amount  (in dB) to make up for the level lost due to compression");
		ui_interface.declare("fHslider2", "unit", "dB");
		ui_interface.addHorizontalSlider("Makeup Gain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 40, -96, 96, 0.1);
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
		ui_interface.addVerticalBargraph("0x7ff0160ba460", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff0160a8a50", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff016086850", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff016064650", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff016042450", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff016020250", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015ffa0d0", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015fd7ed0", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015fb5cd0", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015f93ad0", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015f718d0", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015f4f6d0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015f2d4d0", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015f0b2d0", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ff015ee40c0", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
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
		var fSlow6 = max_f(this.fConst15, (1e-06 * this.fHslider3));
		var fSlow7 = max_f(this.fConst15, (0.001 * this.fHslider4));
		var fSlow8 = Math.exp((0 - (this.fConst14 / min_f(fSlow6, fSlow7))));
		var fSlow9 = (1 - fSlow8);
		var fSlow10 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var iSlow11 = this.fCheckbox2;
		var iSlow12 = this.fCheckbox3;
		var iSlow13 = (this.fEntry0 + -1);
		var iSlow14 = (iSlow13 >= 2);
		var iSlow15 = (iSlow13 >= 1);
		var fSlow16 = Math.exp((0 - (this.fConst14 / this.fVslider2)));
		var fSlow17 = (440 * (Math.pow(2, (0.0833333 * (this.fVslider1 + -49))) * (1 - fSlow16)));
		var iSlow18 = (iSlow13 >= 3);
		var fSlow19 = ((0.01 * this.fVslider3) + 1);
		var fSlow20 = ((0.01 * this.fVslider4) + 1);
		var iSlow21 = this.fCheckbox4;
		var fSlow22 = Math.pow(10, (0.05 * this.fHslider5));
		var iSlow23 = (this.fConst0 * max_f(this.fConst15, (0.001 * this.fHslider6)));
		var fSlow24 = Math.exp((0 - (this.fConst14 / fSlow6)));
		var fSlow25 = Math.exp((0 - (this.fConst14 / fSlow7)));
		var fSlow26 = max_f(this.fConst14, (0.001 * this.fHslider7));
		var fSlow27 = Math.exp((0 - (this.fConst19 / fSlow26)));
		var fSlow28 = (((1 / this.fHslider8) + -1) * (1 - fSlow27));
		var fSlow29 = Math.exp((0 - (this.fConst14 / fSlow26)));
		var fSlow30 = Math.exp((0 - (this.fConst14 / max_f(this.fConst14, (0.001 * this.fHslider9)))));
		var fSlow31 = this.fHslider10;
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec8[0] = (fSlow10 + (0.999 * this.fRec8[1]));
			this.fRec10[0] = (fSlow17 + (fSlow16 * this.fRec10[1]));
			var fTemp0 = max_f(20, Math.abs(this.fRec10[0]));
			this.fVec1[0] = fTemp0;
			var fTemp1 = (this.fRec9[1] + (this.fConst14 * this.fVec1[1]));
			this.fRec9[0] = (fTemp1 - Math.floor(fTemp1));
			var fTemp2 = (2 * this.fRec9[0]);
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
			var fTemp10 = max_f(20, Math.abs((fSlow19 * this.fRec10[0])));
			this.fVec8[0] = fTemp10;
			var fTemp11 = (this.fRec11[1] + (this.fConst14 * this.fVec8[1]));
			this.fRec11[0] = (fTemp11 - Math.floor(fTemp11));
			var fTemp12 = (2 * this.fRec11[0]);
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
			var fTemp20 = max_f(20, Math.abs((fSlow20 * this.fRec10[0])));
			this.fVec15[0] = fTemp20;
			var fTemp21 = (this.fRec12[1] + (this.fConst14 * this.fVec15[1]));
			this.fRec12[0] = (fTemp21 - Math.floor(fTemp21));
			var fTemp22 = (2 * this.fRec12[0]);
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
			this.iRec13[0] = ((1103515245 * this.iRec13[1]) + 12345);
			var fTemp30 = (4.65661e-10 * this.iRec13[0]);
			this.fRec14[0] = (((0.522189 * this.fRec14[3]) + (fTemp30 + (2.49496 * this.fRec14[1]))) - (2.01727 * this.fRec14[2]));
			var fTemp31 = (this.fRec8[0] * (iSlow11?input0[i]:(iSlow12?(iSlow21?(((0.049922 * this.fRec14[0]) + (0.0506127 * this.fRec14[2])) - ((0.0959935 * this.fRec14[1]) + (0.00440879 * this.fRec14[3]))):fTemp30):(0.333333 * (this.fRec8[0] * (((iSlow14?(iSlow18?(this.fConst18 * ((this.iVec0[3] * (fTemp9 - this.fVec7[1])) / fTemp0)):(this.fConst17 * ((this.iVec0[2] * (fTemp6 - this.fVec4[1])) / fTemp0))):(iSlow15?(this.fConst16 * ((this.iVec0[1] * (fTemp4 - this.fVec2[1])) / fTemp0)):fTemp3)) + (iSlow14?(iSlow18?(this.fConst18 * ((this.iVec0[3] * (fTemp19 - this.fVec14[1])) / fTemp10)):(this.fConst17 * ((this.iVec0[2] * (fTemp16 - this.fVec11[1])) / fTemp10))):(iSlow15?(this.fConst16 * ((this.iVec0[1] * (fTemp14 - this.fVec9[1])) / fTemp10)):fTemp13))) + (iSlow14?(iSlow18?(this.fConst18 * ((this.iVec0[3] * (fTemp29 - this.fVec21[1])) / fTemp20)):(this.fConst17 * ((this.iVec0[2] * (fTemp26 - this.fVec18[1])) / fTemp20))):(iSlow15?(this.fConst16 * ((this.iVec0[1] * (fTemp24 - this.fVec16[1])) / fTemp20)):fTemp23))))))));
			var fTemp32 = (iSlow5?0:fTemp31);
			var fTemp33 = Math.abs(fTemp32);
			this.fRec18[0] = ((fSlow8 * this.fRec18[1]) + (fSlow9 * Math.abs((2 * fTemp33))));
			var fRec17 = this.fRec18[0];
			var iTemp34 = (fRec17 > fSlow22);
			this.iVec22[0] = iTemp34;
			this.iRec19[0] = max_i((iSlow23 * (iTemp34 < this.iVec22[1])), (this.iRec19[1] + -1));
			var fTemp35 = Math.abs(max_f(iTemp34, (this.iRec19[0] > 0)));
			var fTemp36 = ((this.fRec15[1] > fTemp35)?fSlow25:fSlow24);
			this.fRec16[0] = ((this.fRec16[1] * fTemp36) + (fTemp35 * (1 - fTemp36)));
			this.fRec15[0] = this.fRec16[0];
			this.fHbargraph0 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec15[0]));
			this.fRec7[0] = ((fSlow8 * this.fRec7[1]) + (fSlow9 * Math.abs((fTemp33 + Math.abs(fTemp32)))));
			var fRec6 = this.fRec7[0];
			var iTemp37 = (fRec6 > fSlow22);
			this.iVec23[0] = iTemp37;
			this.iRec20[0] = max_i((iSlow23 * (iTemp37 < this.iVec23[1])), (this.iRec20[1] + -1));
			var fTemp38 = Math.abs(max_f(iTemp37, (this.iRec20[0] > 0)));
			var fTemp39 = ((this.fRec4[1] > fTemp38)?fSlow25:fSlow24);
			this.fRec5[0] = ((this.fRec5[1] * fTemp39) + (fTemp38 * (1 - fTemp39)));
			this.fRec4[0] = this.fRec5[0];
			var fTemp40 = (iSlow5?fTemp31:(this.fRec4[0] * fTemp32));
			var fTemp41 = (iSlow3?0:fTemp40);
			var fTemp42 = (iSlow5?fTemp31:(this.fRec4[0] * fTemp32));
			var fTemp43 = (iSlow3?0:fTemp42);
			var fTemp44 = Math.abs((Math.abs(fTemp41) + Math.abs(fTemp43)));
			var fTemp45 = ((this.fRec22[1] > fTemp44)?fSlow30:fSlow29);
			this.fRec23[0] = ((this.fRec23[1] * fTemp45) + (fTemp44 * (1 - fTemp45)));
			this.fRec22[0] = this.fRec23[0];
			this.fRec21[0] = ((fSlow27 * this.fRec21[1]) + (fSlow28 * max_f(((20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec22[0])) - fSlow31), 0)));
			var fTemp46 = Math.pow(10, (0.05 * this.fRec21[0]));
			var fTemp47 = (fTemp41 * fTemp46);
			var fTemp48 = (fTemp43 * fTemp46);
			var fTemp49 = Math.abs((Math.abs(fTemp47) + Math.abs(fTemp48)));
			var fTemp50 = ((this.fRec25[1] > fTemp49)?fSlow30:fSlow29);
			this.fRec26[0] = ((this.fRec26[1] * fTemp50) + (fTemp49 * (1 - fTemp50)));
			this.fRec25[0] = this.fRec26[0];
			this.fRec24[0] = ((fSlow27 * this.fRec24[1]) + (fSlow28 * max_f(((20 * function log10(a) { return Math.log(a)/Math.log(10); }(this.fRec25[0])) - fSlow31), 0)));
			this.fHbargraph1 = (20 * function log10(a) { return Math.log(a)/Math.log(10); }(Math.pow(10, (0.05 * this.fRec24[0]))));
			var fTemp51 = ((iSlow3?fTemp40:(fSlow4 * fTemp47)) + (iSlow3?fTemp42:(fSlow4 * fTemp48)));
			this.fRec3[0] = (fTemp51 - (this.fConst11 * ((this.fConst20 * this.fRec3[2]) + (this.fConst22 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[0]) + (this.fConst23 * this.fRec3[1])) + (this.fConst13 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst24 * this.fRec2[2]) + (this.fConst25 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst26 * this.fRec2[0])) + (this.fConst26 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst27 * this.fRec1[2]) + (this.fConst28 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst29 * this.fRec1[0])) + (this.fConst29 * this.fRec1[2]))))));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec33[0] = (fTemp51 - (this.fConst46 * ((this.fConst49 * this.fRec33[2]) + (this.fConst50 * this.fRec33[1]))));
			this.fRec32[0] = ((this.fConst46 * (((this.fConst48 * this.fRec33[1]) + (this.fConst51 * this.fRec33[0])) + (this.fConst51 * this.fRec33[2]))) - (this.fConst44 * ((this.fConst52 * this.fRec32[2]) + (this.fConst53 * this.fRec32[1]))));
			this.fRec31[0] = ((this.fConst44 * (((this.fConst45 * this.fRec32[1]) + (this.fConst54 * this.fRec32[0])) + (this.fConst54 * this.fRec32[2]))) - (this.fConst42 * ((this.fConst55 * this.fRec31[2]) + (this.fConst56 * this.fRec31[1]))));
			var fTemp52 = (this.fConst42 * (((this.fConst43 * this.fRec31[1]) + (this.fConst57 * this.fRec31[0])) + (this.fConst57 * this.fRec31[2])));
			this.fRec30[0] = (fTemp52 - (this.fConst39 * ((this.fConst58 * this.fRec30[2]) + (this.fConst60 * this.fRec30[1]))));
			this.fRec29[0] = ((this.fConst39 * (((this.fConst41 * this.fRec30[1]) + (this.fConst61 * this.fRec30[0])) + (this.fConst61 * this.fRec30[2]))) - (this.fConst36 * ((this.fConst62 * this.fRec29[2]) + (this.fConst63 * this.fRec29[1]))));
			this.fRec28[0] = ((this.fConst36 * (((this.fConst38 * this.fRec29[1]) + (this.fConst64 * this.fRec29[0])) + (this.fConst64 * this.fRec29[2]))) - (this.fConst32 * ((this.fConst65 * this.fRec28[2]) + (this.fConst66 * this.fRec28[1]))));
			this.fRec27[0] = ((fSlow1 * this.fRec27[1]) + (fSlow2 * Math.abs((this.fConst32 * (((this.fConst35 * this.fRec28[1]) + (this.fConst67 * this.fRec28[0])) + (this.fConst67 * this.fRec28[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec27[0]))));
			this.fRec40[0] = (fTemp52 - (this.fConst84 * ((this.fConst87 * this.fRec40[2]) + (this.fConst88 * this.fRec40[1]))));
			this.fRec39[0] = ((this.fConst84 * (((this.fConst86 * this.fRec40[1]) + (this.fConst89 * this.fRec40[0])) + (this.fConst89 * this.fRec40[2]))) - (this.fConst82 * ((this.fConst90 * this.fRec39[2]) + (this.fConst91 * this.fRec39[1]))));
			this.fRec38[0] = ((this.fConst82 * (((this.fConst83 * this.fRec39[1]) + (this.fConst92 * this.fRec39[0])) + (this.fConst92 * this.fRec39[2]))) - (this.fConst80 * ((this.fConst93 * this.fRec38[2]) + (this.fConst94 * this.fRec38[1]))));
			var fTemp53 = (this.fConst80 * (((this.fConst81 * this.fRec38[1]) + (this.fConst95 * this.fRec38[0])) + (this.fConst95 * this.fRec38[2])));
			this.fRec37[0] = (fTemp53 - (this.fConst77 * ((this.fConst96 * this.fRec37[2]) + (this.fConst98 * this.fRec37[1]))));
			this.fRec36[0] = ((this.fConst77 * (((this.fConst79 * this.fRec37[1]) + (this.fConst99 * this.fRec37[0])) + (this.fConst99 * this.fRec37[2]))) - (this.fConst74 * ((this.fConst100 * this.fRec36[2]) + (this.fConst101 * this.fRec36[1]))));
			this.fRec35[0] = ((this.fConst74 * (((this.fConst76 * this.fRec36[1]) + (this.fConst102 * this.fRec36[0])) + (this.fConst102 * this.fRec36[2]))) - (this.fConst70 * ((this.fConst103 * this.fRec35[2]) + (this.fConst104 * this.fRec35[1]))));
			this.fRec34[0] = ((fSlow1 * this.fRec34[1]) + (fSlow2 * Math.abs((this.fConst70 * (((this.fConst73 * this.fRec35[1]) + (this.fConst105 * this.fRec35[0])) + (this.fConst105 * this.fRec35[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec34[0]))));
			this.fRec47[0] = (fTemp53 - (this.fConst122 * ((this.fConst125 * this.fRec47[2]) + (this.fConst126 * this.fRec47[1]))));
			this.fRec46[0] = ((this.fConst122 * (((this.fConst124 * this.fRec47[1]) + (this.fConst127 * this.fRec47[0])) + (this.fConst127 * this.fRec47[2]))) - (this.fConst120 * ((this.fConst128 * this.fRec46[2]) + (this.fConst129 * this.fRec46[1]))));
			this.fRec45[0] = ((this.fConst120 * (((this.fConst121 * this.fRec46[1]) + (this.fConst130 * this.fRec46[0])) + (this.fConst130 * this.fRec46[2]))) - (this.fConst118 * ((this.fConst131 * this.fRec45[2]) + (this.fConst132 * this.fRec45[1]))));
			var fTemp54 = (this.fConst118 * (((this.fConst119 * this.fRec45[1]) + (this.fConst133 * this.fRec45[0])) + (this.fConst133 * this.fRec45[2])));
			this.fRec44[0] = (fTemp54 - (this.fConst115 * ((this.fConst134 * this.fRec44[2]) + (this.fConst136 * this.fRec44[1]))));
			this.fRec43[0] = ((this.fConst115 * (((this.fConst117 * this.fRec44[1]) + (this.fConst137 * this.fRec44[0])) + (this.fConst137 * this.fRec44[2]))) - (this.fConst112 * ((this.fConst138 * this.fRec43[2]) + (this.fConst139 * this.fRec43[1]))));
			this.fRec42[0] = ((this.fConst112 * (((this.fConst114 * this.fRec43[1]) + (this.fConst140 * this.fRec43[0])) + (this.fConst140 * this.fRec43[2]))) - (this.fConst108 * ((this.fConst141 * this.fRec42[2]) + (this.fConst142 * this.fRec42[1]))));
			this.fRec41[0] = ((fSlow1 * this.fRec41[1]) + (fSlow2 * Math.abs((this.fConst108 * (((this.fConst111 * this.fRec42[1]) + (this.fConst143 * this.fRec42[0])) + (this.fConst143 * this.fRec42[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec41[0]))));
			this.fRec54[0] = (fTemp54 - (this.fConst160 * ((this.fConst163 * this.fRec54[2]) + (this.fConst164 * this.fRec54[1]))));
			this.fRec53[0] = ((this.fConst160 * (((this.fConst162 * this.fRec54[1]) + (this.fConst165 * this.fRec54[0])) + (this.fConst165 * this.fRec54[2]))) - (this.fConst158 * ((this.fConst166 * this.fRec53[2]) + (this.fConst167 * this.fRec53[1]))));
			this.fRec52[0] = ((this.fConst158 * (((this.fConst159 * this.fRec53[1]) + (this.fConst168 * this.fRec53[0])) + (this.fConst168 * this.fRec53[2]))) - (this.fConst156 * ((this.fConst169 * this.fRec52[2]) + (this.fConst170 * this.fRec52[1]))));
			var fTemp55 = (this.fConst156 * (((this.fConst157 * this.fRec52[1]) + (this.fConst171 * this.fRec52[0])) + (this.fConst171 * this.fRec52[2])));
			this.fRec51[0] = (fTemp55 - (this.fConst153 * ((this.fConst172 * this.fRec51[2]) + (this.fConst174 * this.fRec51[1]))));
			this.fRec50[0] = ((this.fConst153 * (((this.fConst155 * this.fRec51[1]) + (this.fConst175 * this.fRec51[0])) + (this.fConst175 * this.fRec51[2]))) - (this.fConst150 * ((this.fConst176 * this.fRec50[2]) + (this.fConst177 * this.fRec50[1]))));
			this.fRec49[0] = ((this.fConst150 * (((this.fConst152 * this.fRec50[1]) + (this.fConst178 * this.fRec50[0])) + (this.fConst178 * this.fRec50[2]))) - (this.fConst146 * ((this.fConst179 * this.fRec49[2]) + (this.fConst180 * this.fRec49[1]))));
			this.fRec48[0] = ((fSlow1 * this.fRec48[1]) + (fSlow2 * Math.abs((this.fConst146 * (((this.fConst149 * this.fRec49[1]) + (this.fConst181 * this.fRec49[0])) + (this.fConst181 * this.fRec49[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec48[0]))));
			this.fRec61[0] = (fTemp55 - (this.fConst198 * ((this.fConst201 * this.fRec61[2]) + (this.fConst202 * this.fRec61[1]))));
			this.fRec60[0] = ((this.fConst198 * (((this.fConst200 * this.fRec61[1]) + (this.fConst203 * this.fRec61[0])) + (this.fConst203 * this.fRec61[2]))) - (this.fConst196 * ((this.fConst204 * this.fRec60[2]) + (this.fConst205 * this.fRec60[1]))));
			this.fRec59[0] = ((this.fConst196 * (((this.fConst197 * this.fRec60[1]) + (this.fConst206 * this.fRec60[0])) + (this.fConst206 * this.fRec60[2]))) - (this.fConst194 * ((this.fConst207 * this.fRec59[2]) + (this.fConst208 * this.fRec59[1]))));
			var fTemp56 = (this.fConst194 * (((this.fConst195 * this.fRec59[1]) + (this.fConst209 * this.fRec59[0])) + (this.fConst209 * this.fRec59[2])));
			this.fRec58[0] = (fTemp56 - (this.fConst191 * ((this.fConst210 * this.fRec58[2]) + (this.fConst212 * this.fRec58[1]))));
			this.fRec57[0] = ((this.fConst191 * (((this.fConst193 * this.fRec58[1]) + (this.fConst213 * this.fRec58[0])) + (this.fConst213 * this.fRec58[2]))) - (this.fConst188 * ((this.fConst214 * this.fRec57[2]) + (this.fConst215 * this.fRec57[1]))));
			this.fRec56[0] = ((this.fConst188 * (((this.fConst190 * this.fRec57[1]) + (this.fConst216 * this.fRec57[0])) + (this.fConst216 * this.fRec57[2]))) - (this.fConst184 * ((this.fConst217 * this.fRec56[2]) + (this.fConst218 * this.fRec56[1]))));
			this.fRec55[0] = ((fSlow1 * this.fRec55[1]) + (fSlow2 * Math.abs((this.fConst184 * (((this.fConst187 * this.fRec56[1]) + (this.fConst219 * this.fRec56[0])) + (this.fConst219 * this.fRec56[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec55[0]))));
			this.fRec68[0] = (fTemp56 - (this.fConst236 * ((this.fConst239 * this.fRec68[2]) + (this.fConst240 * this.fRec68[1]))));
			this.fRec67[0] = ((this.fConst236 * (((this.fConst238 * this.fRec68[1]) + (this.fConst241 * this.fRec68[0])) + (this.fConst241 * this.fRec68[2]))) - (this.fConst234 * ((this.fConst242 * this.fRec67[2]) + (this.fConst243 * this.fRec67[1]))));
			this.fRec66[0] = ((this.fConst234 * (((this.fConst235 * this.fRec67[1]) + (this.fConst244 * this.fRec67[0])) + (this.fConst244 * this.fRec67[2]))) - (this.fConst232 * ((this.fConst245 * this.fRec66[2]) + (this.fConst246 * this.fRec66[1]))));
			var fTemp57 = (this.fConst232 * (((this.fConst233 * this.fRec66[1]) + (this.fConst247 * this.fRec66[0])) + (this.fConst247 * this.fRec66[2])));
			this.fRec65[0] = (fTemp57 - (this.fConst229 * ((this.fConst248 * this.fRec65[2]) + (this.fConst250 * this.fRec65[1]))));
			this.fRec64[0] = ((this.fConst229 * (((this.fConst231 * this.fRec65[1]) + (this.fConst251 * this.fRec65[0])) + (this.fConst251 * this.fRec65[2]))) - (this.fConst226 * ((this.fConst252 * this.fRec64[2]) + (this.fConst253 * this.fRec64[1]))));
			this.fRec63[0] = ((this.fConst226 * (((this.fConst228 * this.fRec64[1]) + (this.fConst254 * this.fRec64[0])) + (this.fConst254 * this.fRec64[2]))) - (this.fConst222 * ((this.fConst255 * this.fRec63[2]) + (this.fConst256 * this.fRec63[1]))));
			this.fRec62[0] = ((fSlow1 * this.fRec62[1]) + (fSlow2 * Math.abs((this.fConst222 * (((this.fConst225 * this.fRec63[1]) + (this.fConst257 * this.fRec63[0])) + (this.fConst257 * this.fRec63[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec62[0]))));
			this.fRec75[0] = (fTemp57 - (this.fConst274 * ((this.fConst277 * this.fRec75[2]) + (this.fConst278 * this.fRec75[1]))));
			this.fRec74[0] = ((this.fConst274 * (((this.fConst276 * this.fRec75[1]) + (this.fConst279 * this.fRec75[0])) + (this.fConst279 * this.fRec75[2]))) - (this.fConst272 * ((this.fConst280 * this.fRec74[2]) + (this.fConst281 * this.fRec74[1]))));
			this.fRec73[0] = ((this.fConst272 * (((this.fConst273 * this.fRec74[1]) + (this.fConst282 * this.fRec74[0])) + (this.fConst282 * this.fRec74[2]))) - (this.fConst270 * ((this.fConst283 * this.fRec73[2]) + (this.fConst284 * this.fRec73[1]))));
			var fTemp58 = (this.fConst270 * (((this.fConst271 * this.fRec73[1]) + (this.fConst285 * this.fRec73[0])) + (this.fConst285 * this.fRec73[2])));
			this.fRec72[0] = (fTemp58 - (this.fConst267 * ((this.fConst286 * this.fRec72[2]) + (this.fConst288 * this.fRec72[1]))));
			this.fRec71[0] = ((this.fConst267 * (((this.fConst269 * this.fRec72[1]) + (this.fConst289 * this.fRec72[0])) + (this.fConst289 * this.fRec72[2]))) - (this.fConst264 * ((this.fConst290 * this.fRec71[2]) + (this.fConst291 * this.fRec71[1]))));
			this.fRec70[0] = ((this.fConst264 * (((this.fConst266 * this.fRec71[1]) + (this.fConst292 * this.fRec71[0])) + (this.fConst292 * this.fRec71[2]))) - (this.fConst260 * ((this.fConst293 * this.fRec70[2]) + (this.fConst294 * this.fRec70[1]))));
			this.fRec69[0] = ((fSlow1 * this.fRec69[1]) + (fSlow2 * Math.abs((this.fConst260 * (((this.fConst263 * this.fRec70[1]) + (this.fConst295 * this.fRec70[0])) + (this.fConst295 * this.fRec70[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec69[0]))));
			this.fRec82[0] = (fTemp58 - (this.fConst312 * ((this.fConst315 * this.fRec82[2]) + (this.fConst316 * this.fRec82[1]))));
			this.fRec81[0] = ((this.fConst312 * (((this.fConst314 * this.fRec82[1]) + (this.fConst317 * this.fRec82[0])) + (this.fConst317 * this.fRec82[2]))) - (this.fConst310 * ((this.fConst318 * this.fRec81[2]) + (this.fConst319 * this.fRec81[1]))));
			this.fRec80[0] = ((this.fConst310 * (((this.fConst311 * this.fRec81[1]) + (this.fConst320 * this.fRec81[0])) + (this.fConst320 * this.fRec81[2]))) - (this.fConst308 * ((this.fConst321 * this.fRec80[2]) + (this.fConst322 * this.fRec80[1]))));
			var fTemp59 = (this.fConst308 * (((this.fConst309 * this.fRec80[1]) + (this.fConst323 * this.fRec80[0])) + (this.fConst323 * this.fRec80[2])));
			this.fRec79[0] = (fTemp59 - (this.fConst305 * ((this.fConst324 * this.fRec79[2]) + (this.fConst326 * this.fRec79[1]))));
			this.fRec78[0] = ((this.fConst305 * (((this.fConst307 * this.fRec79[1]) + (this.fConst327 * this.fRec79[0])) + (this.fConst327 * this.fRec79[2]))) - (this.fConst302 * ((this.fConst328 * this.fRec78[2]) + (this.fConst329 * this.fRec78[1]))));
			this.fRec77[0] = ((this.fConst302 * (((this.fConst304 * this.fRec78[1]) + (this.fConst330 * this.fRec78[0])) + (this.fConst330 * this.fRec78[2]))) - (this.fConst298 * ((this.fConst331 * this.fRec77[2]) + (this.fConst332 * this.fRec77[1]))));
			this.fRec76[0] = ((fSlow1 * this.fRec76[1]) + (fSlow2 * Math.abs((this.fConst298 * (((this.fConst301 * this.fRec77[1]) + (this.fConst333 * this.fRec77[0])) + (this.fConst333 * this.fRec77[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec76[0]))));
			this.fRec89[0] = (fTemp59 - (this.fConst350 * ((this.fConst353 * this.fRec89[2]) + (this.fConst354 * this.fRec89[1]))));
			this.fRec88[0] = ((this.fConst350 * (((this.fConst352 * this.fRec89[1]) + (this.fConst355 * this.fRec89[0])) + (this.fConst355 * this.fRec89[2]))) - (this.fConst348 * ((this.fConst356 * this.fRec88[2]) + (this.fConst357 * this.fRec88[1]))));
			this.fRec87[0] = ((this.fConst348 * (((this.fConst349 * this.fRec88[1]) + (this.fConst358 * this.fRec88[0])) + (this.fConst358 * this.fRec88[2]))) - (this.fConst346 * ((this.fConst359 * this.fRec87[2]) + (this.fConst360 * this.fRec87[1]))));
			var fTemp60 = (this.fConst346 * (((this.fConst347 * this.fRec87[1]) + (this.fConst361 * this.fRec87[0])) + (this.fConst361 * this.fRec87[2])));
			this.fRec86[0] = (fTemp60 - (this.fConst343 * ((this.fConst362 * this.fRec86[2]) + (this.fConst364 * this.fRec86[1]))));
			this.fRec85[0] = ((this.fConst343 * (((this.fConst345 * this.fRec86[1]) + (this.fConst365 * this.fRec86[0])) + (this.fConst365 * this.fRec86[2]))) - (this.fConst340 * ((this.fConst366 * this.fRec85[2]) + (this.fConst367 * this.fRec85[1]))));
			this.fRec84[0] = ((this.fConst340 * (((this.fConst342 * this.fRec85[1]) + (this.fConst368 * this.fRec85[0])) + (this.fConst368 * this.fRec85[2]))) - (this.fConst336 * ((this.fConst369 * this.fRec84[2]) + (this.fConst370 * this.fRec84[1]))));
			this.fRec83[0] = ((fSlow1 * this.fRec83[1]) + (fSlow2 * Math.abs((this.fConst336 * (((this.fConst339 * this.fRec84[1]) + (this.fConst371 * this.fRec84[0])) + (this.fConst371 * this.fRec84[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec83[0]))));
			this.fRec96[0] = (fTemp60 - (this.fConst388 * ((this.fConst391 * this.fRec96[2]) + (this.fConst392 * this.fRec96[1]))));
			this.fRec95[0] = ((this.fConst388 * (((this.fConst390 * this.fRec96[1]) + (this.fConst393 * this.fRec96[0])) + (this.fConst393 * this.fRec96[2]))) - (this.fConst386 * ((this.fConst394 * this.fRec95[2]) + (this.fConst395 * this.fRec95[1]))));
			this.fRec94[0] = ((this.fConst386 * (((this.fConst387 * this.fRec95[1]) + (this.fConst396 * this.fRec95[0])) + (this.fConst396 * this.fRec95[2]))) - (this.fConst384 * ((this.fConst397 * this.fRec94[2]) + (this.fConst398 * this.fRec94[1]))));
			var fTemp61 = (this.fConst384 * (((this.fConst385 * this.fRec94[1]) + (this.fConst399 * this.fRec94[0])) + (this.fConst399 * this.fRec94[2])));
			this.fRec93[0] = (fTemp61 - (this.fConst381 * ((this.fConst400 * this.fRec93[2]) + (this.fConst402 * this.fRec93[1]))));
			this.fRec92[0] = ((this.fConst381 * (((this.fConst383 * this.fRec93[1]) + (this.fConst403 * this.fRec93[0])) + (this.fConst403 * this.fRec93[2]))) - (this.fConst378 * ((this.fConst404 * this.fRec92[2]) + (this.fConst405 * this.fRec92[1]))));
			this.fRec91[0] = ((this.fConst378 * (((this.fConst380 * this.fRec92[1]) + (this.fConst406 * this.fRec92[0])) + (this.fConst406 * this.fRec92[2]))) - (this.fConst374 * ((this.fConst407 * this.fRec91[2]) + (this.fConst408 * this.fRec91[1]))));
			this.fRec90[0] = ((fSlow1 * this.fRec90[1]) + (fSlow2 * Math.abs((this.fConst374 * (((this.fConst377 * this.fRec91[1]) + (this.fConst409 * this.fRec91[0])) + (this.fConst409 * this.fRec91[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec90[0]))));
			this.fRec103[0] = (fTemp61 - (this.fConst426 * ((this.fConst429 * this.fRec103[2]) + (this.fConst430 * this.fRec103[1]))));
			this.fRec102[0] = ((this.fConst426 * (((this.fConst428 * this.fRec103[1]) + (this.fConst431 * this.fRec103[0])) + (this.fConst431 * this.fRec103[2]))) - (this.fConst424 * ((this.fConst432 * this.fRec102[2]) + (this.fConst433 * this.fRec102[1]))));
			this.fRec101[0] = ((this.fConst424 * (((this.fConst425 * this.fRec102[1]) + (this.fConst434 * this.fRec102[0])) + (this.fConst434 * this.fRec102[2]))) - (this.fConst422 * ((this.fConst435 * this.fRec101[2]) + (this.fConst436 * this.fRec101[1]))));
			var fTemp62 = (this.fConst422 * (((this.fConst423 * this.fRec101[1]) + (this.fConst437 * this.fRec101[0])) + (this.fConst437 * this.fRec101[2])));
			this.fRec100[0] = (fTemp62 - (this.fConst419 * ((this.fConst438 * this.fRec100[2]) + (this.fConst440 * this.fRec100[1]))));
			this.fRec99[0] = ((this.fConst419 * (((this.fConst421 * this.fRec100[1]) + (this.fConst441 * this.fRec100[0])) + (this.fConst441 * this.fRec100[2]))) - (this.fConst416 * ((this.fConst442 * this.fRec99[2]) + (this.fConst443 * this.fRec99[1]))));
			this.fRec98[0] = ((this.fConst416 * (((this.fConst418 * this.fRec99[1]) + (this.fConst444 * this.fRec99[0])) + (this.fConst444 * this.fRec99[2]))) - (this.fConst412 * ((this.fConst445 * this.fRec98[2]) + (this.fConst446 * this.fRec98[1]))));
			this.fRec97[0] = ((fSlow1 * this.fRec97[1]) + (fSlow2 * Math.abs((this.fConst412 * (((this.fConst415 * this.fRec98[1]) + (this.fConst447 * this.fRec98[0])) + (this.fConst447 * this.fRec98[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec97[0]))));
			this.fRec110[0] = (fTemp62 - (this.fConst464 * ((this.fConst467 * this.fRec110[2]) + (this.fConst468 * this.fRec110[1]))));
			this.fRec109[0] = ((this.fConst464 * (((this.fConst466 * this.fRec110[1]) + (this.fConst469 * this.fRec110[0])) + (this.fConst469 * this.fRec110[2]))) - (this.fConst462 * ((this.fConst470 * this.fRec109[2]) + (this.fConst471 * this.fRec109[1]))));
			this.fRec108[0] = ((this.fConst462 * (((this.fConst463 * this.fRec109[1]) + (this.fConst472 * this.fRec109[0])) + (this.fConst472 * this.fRec109[2]))) - (this.fConst460 * ((this.fConst473 * this.fRec108[2]) + (this.fConst474 * this.fRec108[1]))));
			var fTemp63 = (this.fConst460 * (((this.fConst461 * this.fRec108[1]) + (this.fConst475 * this.fRec108[0])) + (this.fConst475 * this.fRec108[2])));
			this.fRec107[0] = (fTemp63 - (this.fConst457 * ((this.fConst476 * this.fRec107[2]) + (this.fConst478 * this.fRec107[1]))));
			this.fRec106[0] = ((this.fConst457 * (((this.fConst459 * this.fRec107[1]) + (this.fConst479 * this.fRec107[0])) + (this.fConst479 * this.fRec107[2]))) - (this.fConst454 * ((this.fConst480 * this.fRec106[2]) + (this.fConst481 * this.fRec106[1]))));
			this.fRec105[0] = ((this.fConst454 * (((this.fConst456 * this.fRec106[1]) + (this.fConst482 * this.fRec106[0])) + (this.fConst482 * this.fRec106[2]))) - (this.fConst450 * ((this.fConst483 * this.fRec105[2]) + (this.fConst484 * this.fRec105[1]))));
			this.fRec104[0] = ((fSlow1 * this.fRec104[1]) + (fSlow2 * Math.abs((this.fConst450 * (((this.fConst453 * this.fRec105[1]) + (this.fConst485 * this.fRec105[0])) + (this.fConst485 * this.fRec105[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec104[0]))));
			this.fRec117[0] = (fTemp63 - (this.fConst502 * ((this.fConst505 * this.fRec117[2]) + (this.fConst506 * this.fRec117[1]))));
			this.fRec116[0] = ((this.fConst502 * (((this.fConst504 * this.fRec117[1]) + (this.fConst507 * this.fRec117[0])) + (this.fConst507 * this.fRec117[2]))) - (this.fConst500 * ((this.fConst508 * this.fRec116[2]) + (this.fConst509 * this.fRec116[1]))));
			this.fRec115[0] = ((this.fConst500 * (((this.fConst501 * this.fRec116[1]) + (this.fConst510 * this.fRec116[0])) + (this.fConst510 * this.fRec116[2]))) - (this.fConst498 * ((this.fConst511 * this.fRec115[2]) + (this.fConst512 * this.fRec115[1]))));
			var fTemp64 = (this.fConst498 * (((this.fConst499 * this.fRec115[1]) + (this.fConst513 * this.fRec115[0])) + (this.fConst513 * this.fRec115[2])));
			this.fRec114[0] = (fTemp64 - (this.fConst495 * ((this.fConst514 * this.fRec114[2]) + (this.fConst516 * this.fRec114[1]))));
			this.fRec113[0] = ((this.fConst495 * (((this.fConst497 * this.fRec114[1]) + (this.fConst517 * this.fRec114[0])) + (this.fConst517 * this.fRec114[2]))) - (this.fConst492 * ((this.fConst518 * this.fRec113[2]) + (this.fConst519 * this.fRec113[1]))));
			this.fRec112[0] = ((this.fConst492 * (((this.fConst494 * this.fRec113[1]) + (this.fConst520 * this.fRec113[0])) + (this.fConst520 * this.fRec113[2]))) - (this.fConst488 * ((this.fConst521 * this.fRec112[2]) + (this.fConst522 * this.fRec112[1]))));
			this.fRec111[0] = ((fSlow1 * this.fRec111[1]) + (fSlow2 * Math.abs((this.fConst488 * (((this.fConst491 * this.fRec112[1]) + (this.fConst523 * this.fRec112[0])) + (this.fConst523 * this.fRec112[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec111[0]))));
			this.fRec121[0] = (fTemp64 - (this.fConst528 * ((this.fConst531 * this.fRec121[2]) + (this.fConst532 * this.fRec121[1]))));
			this.fRec120[0] = ((this.fConst528 * (((this.fConst530 * this.fRec121[1]) + (this.fConst533 * this.fRec121[0])) + (this.fConst533 * this.fRec121[2]))) - (this.fConst526 * ((this.fConst534 * this.fRec120[2]) + (this.fConst535 * this.fRec120[1]))));
			this.fRec119[0] = ((this.fConst526 * (((this.fConst527 * this.fRec120[1]) + (this.fConst536 * this.fRec120[0])) + (this.fConst536 * this.fRec120[2]))) - (this.fConst524 * ((this.fConst537 * this.fRec119[2]) + (this.fConst538 * this.fRec119[1]))));
			this.fRec118[0] = ((fSlow1 * this.fRec118[1]) + (fSlow2 * Math.abs((this.fConst524 * (((this.fConst525 * this.fRec119[1]) + (this.fConst539 * this.fRec119[0])) + (this.fConst539 * this.fRec119[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec118[0]))));
			output0[i] = fTemp51;
			output1[i] = fTemp51;
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec8[1] = this.fRec8[0];
			this.fRec10[1] = this.fRec10[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec9[1] = this.fRec9[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec11[1] = this.fRec11[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec12[1] = this.fRec12[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.iRec13[1] = this.iRec13[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec14[j1] = this.fRec14[(j1 - 1)];
				
			}
			this.fRec18[1] = this.fRec18[0];
			this.iVec22[1] = this.iVec22[0];
			this.iRec19[1] = this.iRec19[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec7[1] = this.fRec7[0];
			this.iVec23[1] = this.iVec23[0];
			this.iRec20[1] = this.iRec20[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec4[1] = this.fRec4[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec21[1] = this.fRec21[0];
			this.fRec26[1] = this.fRec26[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec24[1] = this.fRec24[0];
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

