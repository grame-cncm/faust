
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
	this.fVslider0;
	this.fHslider3;
	this.fRec10 = new Float32Array(2);
	this.fVslider1;
	this.fEntry0;
	this.fConst14;
	this.fHslider4;
	this.fVslider2;
	this.fRec12 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fConst15;
	this.fVec2 = new Float32Array(2);
	this.fConst16;
	this.fVec3 = new Float32Array(2);
	this.fVec4 = new Float32Array(2);
	this.fConst17;
	this.fVec5 = new Float32Array(2);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2);
	this.fVslider3;
	this.fVec8 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec14 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fConst18;
	this.fVslider5;
	this.fVec22 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fVec23 = new Float32Array(2);
	this.IOTA;
	this.fVec24 = new Float32Array(4096);
	this.fConst19;
	this.fVec25 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fVec26 = new Float32Array(2);
	this.fVec27 = new Float32Array(4096);
	this.fVec28 = new Float32Array(2);
	this.fRec17 = new Float32Array(2);
	this.fVec29 = new Float32Array(2);
	this.fVec30 = new Float32Array(4096);
	this.fConst20;
	this.fVslider6;
	this.fRec18 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fRec20 = new Float32Array(2);
	this.fVslider7;
	this.fCheckbox2;
	this.fVslider8;
	this.fRec21 = new Float32Array(2);
	this.fConst21;
	this.fVec31 = new Float32Array(2);
	this.fVec32 = new Float32Array(2);
	this.fVec33 = new Float32Array(4096);
	this.fVec34 = new Float32Array(2);
	this.fVec35 = new Float32Array(2);
	this.fVec36 = new Float32Array(4096);
	this.fVec37 = new Float32Array(2);
	this.fVec38 = new Float32Array(2);
	this.fVec39 = new Float32Array(4096);
	this.fVslider9;
	this.iRec23 = new Int32Array(2);
	this.fRec22 = new Float32Array(4);
	this.fConst22;
	this.fHslider5;
	this.fRec24 = new Float32Array(2);
	this.fHslider6;
	this.fRec9 = new Float32Array(2);
	this.fRec8 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fRec6 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fCheckbox3;
	this.fConst23;
	this.fRec27 = new Float32Array(2);
	this.fRec26 = new Float32Array(3);
	this.fRec25 = new Float32Array(3);
	this.fRec30 = new Float32Array(2);
	this.fRec28 = new Float32Array(2);
	this.fRec33 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fConst24;
	this.fConst25;
	this.fConst26;
	this.fRec3 = new Float32Array(3);
	this.fConst27;
	this.fConst28;
	this.fConst29;
	this.fRec2 = new Float32Array(3);
	this.fConst30;
	this.fConst31;
	this.fConst32;
	this.fRec1 = new Float32Array(3);
	this.fConst33;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
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
	this.fRec40 = new Float32Array(3);
	this.fConst55;
	this.fConst56;
	this.fConst57;
	this.fRec39 = new Float32Array(3);
	this.fConst58;
	this.fConst59;
	this.fConst60;
	this.fRec38 = new Float32Array(3);
	this.fConst61;
	this.fConst62;
	this.fConst63;
	this.fConst64;
	this.fRec37 = new Float32Array(3);
	this.fConst65;
	this.fConst66;
	this.fConst67;
	this.fRec36 = new Float32Array(3);
	this.fConst68;
	this.fConst69;
	this.fConst70;
	this.fRec35 = new Float32Array(3);
	this.fConst71;
	this.fRec34 = new Float32Array(2);
	this.fVbargraph1;
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
	this.fConst91;
	this.fConst92;
	this.fRec47 = new Float32Array(3);
	this.fConst93;
	this.fConst94;
	this.fConst95;
	this.fRec46 = new Float32Array(3);
	this.fConst96;
	this.fConst97;
	this.fConst98;
	this.fRec45 = new Float32Array(3);
	this.fConst99;
	this.fConst100;
	this.fConst101;
	this.fConst102;
	this.fRec44 = new Float32Array(3);
	this.fConst103;
	this.fConst104;
	this.fConst105;
	this.fRec43 = new Float32Array(3);
	this.fConst106;
	this.fConst107;
	this.fConst108;
	this.fRec42 = new Float32Array(3);
	this.fConst109;
	this.fRec41 = new Float32Array(2);
	this.fVbargraph2;
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
	this.fConst129;
	this.fConst130;
	this.fRec54 = new Float32Array(3);
	this.fConst131;
	this.fConst132;
	this.fConst133;
	this.fRec53 = new Float32Array(3);
	this.fConst134;
	this.fConst135;
	this.fConst136;
	this.fRec52 = new Float32Array(3);
	this.fConst137;
	this.fConst138;
	this.fConst139;
	this.fConst140;
	this.fRec51 = new Float32Array(3);
	this.fConst141;
	this.fConst142;
	this.fConst143;
	this.fRec50 = new Float32Array(3);
	this.fConst144;
	this.fConst145;
	this.fConst146;
	this.fRec49 = new Float32Array(3);
	this.fConst147;
	this.fRec48 = new Float32Array(2);
	this.fVbargraph3;
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
	this.fConst167;
	this.fConst168;
	this.fRec61 = new Float32Array(3);
	this.fConst169;
	this.fConst170;
	this.fConst171;
	this.fRec60 = new Float32Array(3);
	this.fConst172;
	this.fConst173;
	this.fConst174;
	this.fRec59 = new Float32Array(3);
	this.fConst175;
	this.fConst176;
	this.fConst177;
	this.fConst178;
	this.fRec58 = new Float32Array(3);
	this.fConst179;
	this.fConst180;
	this.fConst181;
	this.fRec57 = new Float32Array(3);
	this.fConst182;
	this.fConst183;
	this.fConst184;
	this.fRec56 = new Float32Array(3);
	this.fConst185;
	this.fRec55 = new Float32Array(2);
	this.fVbargraph4;
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
	this.fConst205;
	this.fConst206;
	this.fRec68 = new Float32Array(3);
	this.fConst207;
	this.fConst208;
	this.fConst209;
	this.fRec67 = new Float32Array(3);
	this.fConst210;
	this.fConst211;
	this.fConst212;
	this.fRec66 = new Float32Array(3);
	this.fConst213;
	this.fConst214;
	this.fConst215;
	this.fConst216;
	this.fRec65 = new Float32Array(3);
	this.fConst217;
	this.fConst218;
	this.fConst219;
	this.fRec64 = new Float32Array(3);
	this.fConst220;
	this.fConst221;
	this.fConst222;
	this.fRec63 = new Float32Array(3);
	this.fConst223;
	this.fRec62 = new Float32Array(2);
	this.fVbargraph5;
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
	this.fConst243;
	this.fConst244;
	this.fRec75 = new Float32Array(3);
	this.fConst245;
	this.fConst246;
	this.fConst247;
	this.fRec74 = new Float32Array(3);
	this.fConst248;
	this.fConst249;
	this.fConst250;
	this.fRec73 = new Float32Array(3);
	this.fConst251;
	this.fConst252;
	this.fConst253;
	this.fConst254;
	this.fRec72 = new Float32Array(3);
	this.fConst255;
	this.fConst256;
	this.fConst257;
	this.fRec71 = new Float32Array(3);
	this.fConst258;
	this.fConst259;
	this.fConst260;
	this.fRec70 = new Float32Array(3);
	this.fConst261;
	this.fRec69 = new Float32Array(2);
	this.fVbargraph6;
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
	this.fConst281;
	this.fConst282;
	this.fRec82 = new Float32Array(3);
	this.fConst283;
	this.fConst284;
	this.fConst285;
	this.fRec81 = new Float32Array(3);
	this.fConst286;
	this.fConst287;
	this.fConst288;
	this.fRec80 = new Float32Array(3);
	this.fConst289;
	this.fConst290;
	this.fConst291;
	this.fConst292;
	this.fRec79 = new Float32Array(3);
	this.fConst293;
	this.fConst294;
	this.fConst295;
	this.fRec78 = new Float32Array(3);
	this.fConst296;
	this.fConst297;
	this.fConst298;
	this.fRec77 = new Float32Array(3);
	this.fConst299;
	this.fRec76 = new Float32Array(2);
	this.fVbargraph7;
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
	this.fConst319;
	this.fConst320;
	this.fRec89 = new Float32Array(3);
	this.fConst321;
	this.fConst322;
	this.fConst323;
	this.fRec88 = new Float32Array(3);
	this.fConst324;
	this.fConst325;
	this.fConst326;
	this.fRec87 = new Float32Array(3);
	this.fConst327;
	this.fConst328;
	this.fConst329;
	this.fConst330;
	this.fRec86 = new Float32Array(3);
	this.fConst331;
	this.fConst332;
	this.fConst333;
	this.fRec85 = new Float32Array(3);
	this.fConst334;
	this.fConst335;
	this.fConst336;
	this.fRec84 = new Float32Array(3);
	this.fConst337;
	this.fRec83 = new Float32Array(2);
	this.fVbargraph8;
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
	this.fConst357;
	this.fConst358;
	this.fRec96 = new Float32Array(3);
	this.fConst359;
	this.fConst360;
	this.fConst361;
	this.fRec95 = new Float32Array(3);
	this.fConst362;
	this.fConst363;
	this.fConst364;
	this.fRec94 = new Float32Array(3);
	this.fConst365;
	this.fConst366;
	this.fConst367;
	this.fConst368;
	this.fRec93 = new Float32Array(3);
	this.fConst369;
	this.fConst370;
	this.fConst371;
	this.fRec92 = new Float32Array(3);
	this.fConst372;
	this.fConst373;
	this.fConst374;
	this.fRec91 = new Float32Array(3);
	this.fConst375;
	this.fRec90 = new Float32Array(2);
	this.fVbargraph9;
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
	this.fConst395;
	this.fConst396;
	this.fRec103 = new Float32Array(3);
	this.fConst397;
	this.fConst398;
	this.fConst399;
	this.fRec102 = new Float32Array(3);
	this.fConst400;
	this.fConst401;
	this.fConst402;
	this.fRec101 = new Float32Array(3);
	this.fConst403;
	this.fConst404;
	this.fConst405;
	this.fConst406;
	this.fRec100 = new Float32Array(3);
	this.fConst407;
	this.fConst408;
	this.fConst409;
	this.fRec99 = new Float32Array(3);
	this.fConst410;
	this.fConst411;
	this.fConst412;
	this.fRec98 = new Float32Array(3);
	this.fConst413;
	this.fRec97 = new Float32Array(2);
	this.fVbargraph10;
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
	this.fConst433;
	this.fConst434;
	this.fRec110 = new Float32Array(3);
	this.fConst435;
	this.fConst436;
	this.fConst437;
	this.fRec109 = new Float32Array(3);
	this.fConst438;
	this.fConst439;
	this.fConst440;
	this.fRec108 = new Float32Array(3);
	this.fConst441;
	this.fConst442;
	this.fConst443;
	this.fConst444;
	this.fRec107 = new Float32Array(3);
	this.fConst445;
	this.fConst446;
	this.fConst447;
	this.fRec106 = new Float32Array(3);
	this.fConst448;
	this.fConst449;
	this.fConst450;
	this.fRec105 = new Float32Array(3);
	this.fConst451;
	this.fRec104 = new Float32Array(2);
	this.fVbargraph11;
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
	this.fConst471;
	this.fConst472;
	this.fRec117 = new Float32Array(3);
	this.fConst473;
	this.fConst474;
	this.fConst475;
	this.fRec116 = new Float32Array(3);
	this.fConst476;
	this.fConst477;
	this.fConst478;
	this.fRec115 = new Float32Array(3);
	this.fConst479;
	this.fConst480;
	this.fConst481;
	this.fConst482;
	this.fRec114 = new Float32Array(3);
	this.fConst483;
	this.fConst484;
	this.fConst485;
	this.fRec113 = new Float32Array(3);
	this.fConst486;
	this.fConst487;
	this.fConst488;
	this.fRec112 = new Float32Array(3);
	this.fConst489;
	this.fRec111 = new Float32Array(2);
	this.fVbargraph12;
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
	this.fConst509;
	this.fConst510;
	this.fRec124 = new Float32Array(3);
	this.fConst511;
	this.fConst512;
	this.fConst513;
	this.fRec123 = new Float32Array(3);
	this.fConst514;
	this.fConst515;
	this.fConst516;
	this.fRec122 = new Float32Array(3);
	this.fConst517;
	this.fConst518;
	this.fConst519;
	this.fConst520;
	this.fRec121 = new Float32Array(3);
	this.fConst521;
	this.fConst522;
	this.fConst523;
	this.fRec120 = new Float32Array(3);
	this.fConst524;
	this.fConst525;
	this.fConst526;
	this.fRec119 = new Float32Array(3);
	this.fConst527;
	this.fRec118 = new Float32Array(2);
	this.fVbargraph13;
	this.fConst528;
	this.fConst529;
	this.fConst530;
	this.fConst531;
	this.fConst532;
	this.fConst533;
	this.fConst534;
	this.fConst535;
	this.fConst536;
	this.fRec128 = new Float32Array(3);
	this.fConst537;
	this.fConst538;
	this.fConst539;
	this.fRec127 = new Float32Array(3);
	this.fConst540;
	this.fConst541;
	this.fConst542;
	this.fRec126 = new Float32Array(3);
	this.fConst543;
	this.fRec125 = new Float32Array(2);
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
		this.fConst14 = (1 / this.fConst0);
		this.fConst15 = (0.25 * this.fConst0);
		this.fConst16 = (0.0416667 * mydsp_faustpower2_f(this.fConst0));
		this.fConst17 = (0.00520833 * mydsp_faustpower3_f(this.fConst0));
		this.fConst18 = (0.0833333 * this.fConst0);
		this.fConst19 = (0.5 * this.fConst0);
		this.fConst20 = (1.33333 / this.fConst0);
		this.fConst21 = (0.0138889 * this.fConst0);
		this.fConst22 = (6.28319 / this.fConst0);
		this.fConst23 = (3.14159 / this.fConst0);
		this.fConst24 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst25 = (1 / this.fConst5);
		this.fConst26 = (2 * (4.07678 - this.fConst25));
		this.fConst27 = (this.fConst12 + 0.000407678);
		this.fConst28 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst29 = (2 * (1.45007 - this.fConst25));
		this.fConst30 = (this.fConst9 + 1.45007);
		this.fConst31 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst32 = (2 * (0.93514 - this.fConst25));
		this.fConst33 = (this.fConst6 + 0.93514);
		this.fConst34 = Math.tan((31665.3 / this.fConst0));
		this.fConst35 = (1 / this.fConst34);
		this.fConst36 = (1 / (((this.fConst35 + 0.157482) / this.fConst34) + 0.93514));
		this.fConst37 = mydsp_faustpower2_f(this.fConst34);
		this.fConst38 = (50.0638 / this.fConst37);
		this.fConst39 = (2 * (0.93514 - this.fConst38));
		this.fConst40 = (1 / (((this.fConst35 + 0.74313) / this.fConst34) + 1.45007));
		this.fConst41 = (11.0521 / this.fConst37);
		this.fConst42 = (2 * (1.45007 - this.fConst41));
		this.fConst43 = (1 / (((this.fConst35 + 3.18973) / this.fConst34) + 4.07678));
		this.fConst44 = (0.00176617 / this.fConst37);
		this.fConst45 = (2 * (0.000407678 - this.fConst44));
		this.fConst46 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst47 = (2 * (53.5362 - this.fConst25));
		this.fConst48 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst49 = (2 * (7.62173 - this.fConst25));
		this.fConst50 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst51 = (0.0001 / this.fConst5);
		this.fConst52 = (2 * (0.000433227 - this.fConst51));
		this.fConst53 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst54 = (2 * (0.245292 - this.fConst25));
		this.fConst55 = (this.fConst51 + 0.000433227);
		this.fConst56 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst57 = (2 * (0.689621 - this.fConst25));
		this.fConst58 = (this.fConst25 + 7.62173);
		this.fConst59 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst60 = (2 * (1.06936 - this.fConst25));
		this.fConst61 = (this.fConst25 + 53.5362);
		this.fConst62 = (((this.fConst35 + -3.18973) / this.fConst34) + 4.07678);
		this.fConst63 = (1 / this.fConst37);
		this.fConst64 = (2 * (4.07678 - this.fConst63));
		this.fConst65 = (this.fConst44 + 0.000407678);
		this.fConst66 = (((this.fConst35 + -0.74313) / this.fConst34) + 1.45007);
		this.fConst67 = (2 * (1.45007 - this.fConst63));
		this.fConst68 = (this.fConst41 + 1.45007);
		this.fConst69 = (((this.fConst35 + -0.157482) / this.fConst34) + 0.93514);
		this.fConst70 = (2 * (0.93514 - this.fConst63));
		this.fConst71 = (this.fConst38 + 0.93514);
		this.fConst72 = Math.tan((19947.9 / this.fConst0));
		this.fConst73 = (1 / this.fConst72);
		this.fConst74 = (1 / (((this.fConst73 + 0.157482) / this.fConst72) + 0.93514));
		this.fConst75 = mydsp_faustpower2_f(this.fConst72);
		this.fConst76 = (50.0638 / this.fConst75);
		this.fConst77 = (2 * (0.93514 - this.fConst76));
		this.fConst78 = (1 / (((this.fConst73 + 0.74313) / this.fConst72) + 1.45007));
		this.fConst79 = (11.0521 / this.fConst75);
		this.fConst80 = (2 * (1.45007 - this.fConst79));
		this.fConst81 = (1 / (((this.fConst73 + 3.18973) / this.fConst72) + 4.07678));
		this.fConst82 = (0.00176617 / this.fConst75);
		this.fConst83 = (2 * (0.000407678 - this.fConst82));
		this.fConst84 = (1 / (((this.fConst35 + 0.168405) / this.fConst34) + 1.06936));
		this.fConst85 = (2 * (53.5362 - this.fConst63));
		this.fConst86 = (1 / (((this.fConst35 + 0.512479) / this.fConst34) + 0.689621));
		this.fConst87 = (2 * (7.62173 - this.fConst63));
		this.fConst88 = (1 / (((this.fConst35 + 0.782413) / this.fConst34) + 0.245292));
		this.fConst89 = (0.0001 / this.fConst37);
		this.fConst90 = (2 * (0.000433227 - this.fConst89));
		this.fConst91 = (((this.fConst35 + -0.782413) / this.fConst34) + 0.245292);
		this.fConst92 = (2 * (0.245292 - this.fConst63));
		this.fConst93 = (this.fConst89 + 0.000433227);
		this.fConst94 = (((this.fConst35 + -0.512479) / this.fConst34) + 0.689621);
		this.fConst95 = (2 * (0.689621 - this.fConst63));
		this.fConst96 = (this.fConst63 + 7.62173);
		this.fConst97 = (((this.fConst35 + -0.168405) / this.fConst34) + 1.06936);
		this.fConst98 = (2 * (1.06936 - this.fConst63));
		this.fConst99 = (this.fConst63 + 53.5362);
		this.fConst100 = (((this.fConst73 + -3.18973) / this.fConst72) + 4.07678);
		this.fConst101 = (1 / this.fConst75);
		this.fConst102 = (2 * (4.07678 - this.fConst101));
		this.fConst103 = (this.fConst82 + 0.000407678);
		this.fConst104 = (((this.fConst73 + -0.74313) / this.fConst72) + 1.45007);
		this.fConst105 = (2 * (1.45007 - this.fConst101));
		this.fConst106 = (this.fConst79 + 1.45007);
		this.fConst107 = (((this.fConst73 + -0.157482) / this.fConst72) + 0.93514);
		this.fConst108 = (2 * (0.93514 - this.fConst101));
		this.fConst109 = (this.fConst76 + 0.93514);
		this.fConst110 = Math.tan((12566.4 / this.fConst0));
		this.fConst111 = (1 / this.fConst110);
		this.fConst112 = (1 / (((this.fConst111 + 0.157482) / this.fConst110) + 0.93514));
		this.fConst113 = mydsp_faustpower2_f(this.fConst110);
		this.fConst114 = (50.0638 / this.fConst113);
		this.fConst115 = (2 * (0.93514 - this.fConst114));
		this.fConst116 = (1 / (((this.fConst111 + 0.74313) / this.fConst110) + 1.45007));
		this.fConst117 = (11.0521 / this.fConst113);
		this.fConst118 = (2 * (1.45007 - this.fConst117));
		this.fConst119 = (1 / (((this.fConst111 + 3.18973) / this.fConst110) + 4.07678));
		this.fConst120 = (0.00176617 / this.fConst113);
		this.fConst121 = (this.fConst120 + 0.000407678);
		this.fConst122 = (1 / (((this.fConst73 + 0.168405) / this.fConst72) + 1.06936));
		this.fConst123 = (2 * (53.5362 - this.fConst101));
		this.fConst124 = (1 / (((this.fConst73 + 0.512479) / this.fConst72) + 0.689621));
		this.fConst125 = (2 * (7.62173 - this.fConst101));
		this.fConst126 = (1 / (((this.fConst73 + 0.782413) / this.fConst72) + 0.245292));
		this.fConst127 = (0.0001 / this.fConst75);
		this.fConst128 = (2 * (0.000433227 - this.fConst127));
		this.fConst129 = (((this.fConst73 + -0.782413) / this.fConst72) + 0.245292);
		this.fConst130 = (2 * (0.245292 - this.fConst101));
		this.fConst131 = (this.fConst127 + 0.000433227);
		this.fConst132 = (((this.fConst73 + -0.512479) / this.fConst72) + 0.689621);
		this.fConst133 = (2 * (0.689621 - this.fConst101));
		this.fConst134 = (this.fConst101 + 7.62173);
		this.fConst135 = (((this.fConst73 + -0.168405) / this.fConst72) + 1.06936);
		this.fConst136 = (2 * (1.06936 - this.fConst101));
		this.fConst137 = (this.fConst101 + 53.5362);
		this.fConst138 = (((this.fConst111 + -3.18973) / this.fConst110) + 4.07678);
		this.fConst139 = (1 / this.fConst113);
		this.fConst140 = (2 * (4.07678 - this.fConst139));
		this.fConst141 = (2 * (0.000407678 - this.fConst120));
		this.fConst142 = (((this.fConst111 + -0.74313) / this.fConst110) + 1.45007);
		this.fConst143 = (2 * (1.45007 - this.fConst139));
		this.fConst144 = (this.fConst117 + 1.45007);
		this.fConst145 = (((this.fConst111 + -0.157482) / this.fConst110) + 0.93514);
		this.fConst146 = (2 * (0.93514 - this.fConst139));
		this.fConst147 = (this.fConst114 + 0.93514);
		this.fConst148 = Math.tan((7916.32 / this.fConst0));
		this.fConst149 = (1 / this.fConst148);
		this.fConst150 = (1 / (((this.fConst149 + 0.157482) / this.fConst148) + 0.93514));
		this.fConst151 = mydsp_faustpower2_f(this.fConst148);
		this.fConst152 = (50.0638 / this.fConst151);
		this.fConst153 = (2 * (0.93514 - this.fConst152));
		this.fConst154 = (1 / (((this.fConst149 + 0.74313) / this.fConst148) + 1.45007));
		this.fConst155 = (11.0521 / this.fConst151);
		this.fConst156 = (2 * (1.45007 - this.fConst155));
		this.fConst157 = (1 / (((this.fConst149 + 3.18973) / this.fConst148) + 4.07678));
		this.fConst158 = (0.00176617 / this.fConst151);
		this.fConst159 = (2 * (0.000407678 - this.fConst158));
		this.fConst160 = (1 / (((this.fConst111 + 0.168405) / this.fConst110) + 1.06936));
		this.fConst161 = (2 * (53.5362 - this.fConst139));
		this.fConst162 = (1 / (((this.fConst111 + 0.512479) / this.fConst110) + 0.689621));
		this.fConst163 = (2 * (7.62173 - this.fConst139));
		this.fConst164 = (1 / (((this.fConst111 + 0.782413) / this.fConst110) + 0.245292));
		this.fConst165 = (0.0001 / this.fConst113);
		this.fConst166 = (2 * (0.000433227 - this.fConst165));
		this.fConst167 = (((this.fConst111 + -0.782413) / this.fConst110) + 0.245292);
		this.fConst168 = (2 * (0.245292 - this.fConst139));
		this.fConst169 = (this.fConst165 + 0.000433227);
		this.fConst170 = (((this.fConst111 + -0.512479) / this.fConst110) + 0.689621);
		this.fConst171 = (2 * (0.689621 - this.fConst139));
		this.fConst172 = (this.fConst139 + 7.62173);
		this.fConst173 = (((this.fConst111 + -0.168405) / this.fConst110) + 1.06936);
		this.fConst174 = (2 * (1.06936 - this.fConst139));
		this.fConst175 = (this.fConst139 + 53.5362);
		this.fConst176 = (((this.fConst149 + -3.18973) / this.fConst148) + 4.07678);
		this.fConst177 = (1 / this.fConst151);
		this.fConst178 = (2 * (4.07678 - this.fConst177));
		this.fConst179 = (this.fConst158 + 0.000407678);
		this.fConst180 = (((this.fConst149 + -0.74313) / this.fConst148) + 1.45007);
		this.fConst181 = (2 * (1.45007 - this.fConst177));
		this.fConst182 = (this.fConst155 + 1.45007);
		this.fConst183 = (((this.fConst149 + -0.157482) / this.fConst148) + 0.93514);
		this.fConst184 = (2 * (0.93514 - this.fConst177));
		this.fConst185 = (this.fConst152 + 0.93514);
		this.fConst186 = Math.tan((4986.97 / this.fConst0));
		this.fConst187 = (1 / this.fConst186);
		this.fConst188 = (1 / (((this.fConst187 + 0.157482) / this.fConst186) + 0.93514));
		this.fConst189 = mydsp_faustpower2_f(this.fConst186);
		this.fConst190 = (50.0638 / this.fConst189);
		this.fConst191 = (2 * (0.93514 - this.fConst190));
		this.fConst192 = (1 / (((this.fConst187 + 0.74313) / this.fConst186) + 1.45007));
		this.fConst193 = (11.0521 / this.fConst189);
		this.fConst194 = (2 * (1.45007 - this.fConst193));
		this.fConst195 = (1 / (((this.fConst187 + 3.18973) / this.fConst186) + 4.07678));
		this.fConst196 = (0.00176617 / this.fConst189);
		this.fConst197 = (2 * (0.000407678 - this.fConst196));
		this.fConst198 = (1 / (((this.fConst149 + 0.168405) / this.fConst148) + 1.06936));
		this.fConst199 = (2 * (53.5362 - this.fConst177));
		this.fConst200 = (1 / (((this.fConst149 + 0.512479) / this.fConst148) + 0.689621));
		this.fConst201 = (2 * (7.62173 - this.fConst177));
		this.fConst202 = (1 / (((this.fConst149 + 0.782413) / this.fConst148) + 0.245292));
		this.fConst203 = (0.0001 / this.fConst151);
		this.fConst204 = (2 * (0.000433227 - this.fConst203));
		this.fConst205 = (((this.fConst149 + -0.782413) / this.fConst148) + 0.245292);
		this.fConst206 = (2 * (0.245292 - this.fConst177));
		this.fConst207 = (this.fConst203 + 0.000433227);
		this.fConst208 = (((this.fConst149 + -0.512479) / this.fConst148) + 0.689621);
		this.fConst209 = (2 * (0.689621 - this.fConst177));
		this.fConst210 = (this.fConst177 + 7.62173);
		this.fConst211 = (((this.fConst149 + -0.168405) / this.fConst148) + 1.06936);
		this.fConst212 = (2 * (1.06936 - this.fConst177));
		this.fConst213 = (this.fConst177 + 53.5362);
		this.fConst214 = (((this.fConst187 + -3.18973) / this.fConst186) + 4.07678);
		this.fConst215 = (1 / this.fConst189);
		this.fConst216 = (2 * (4.07678 - this.fConst215));
		this.fConst217 = (this.fConst196 + 0.000407678);
		this.fConst218 = (((this.fConst187 + -0.74313) / this.fConst186) + 1.45007);
		this.fConst219 = (2 * (1.45007 - this.fConst215));
		this.fConst220 = (this.fConst193 + 1.45007);
		this.fConst221 = (((this.fConst187 + -0.157482) / this.fConst186) + 0.93514);
		this.fConst222 = (2 * (0.93514 - this.fConst215));
		this.fConst223 = (this.fConst190 + 0.93514);
		this.fConst224 = Math.tan((3141.59 / this.fConst0));
		this.fConst225 = (1 / this.fConst224);
		this.fConst226 = (1 / (((this.fConst225 + 0.157482) / this.fConst224) + 0.93514));
		this.fConst227 = mydsp_faustpower2_f(this.fConst224);
		this.fConst228 = (50.0638 / this.fConst227);
		this.fConst229 = (2 * (0.93514 - this.fConst228));
		this.fConst230 = (1 / (((this.fConst225 + 0.74313) / this.fConst224) + 1.45007));
		this.fConst231 = (11.0521 / this.fConst227);
		this.fConst232 = (2 * (1.45007 - this.fConst231));
		this.fConst233 = (1 / (((this.fConst225 + 3.18973) / this.fConst224) + 4.07678));
		this.fConst234 = (0.00176617 / this.fConst227);
		this.fConst235 = (2 * (0.000407678 - this.fConst234));
		this.fConst236 = (1 / (((this.fConst187 + 0.168405) / this.fConst186) + 1.06936));
		this.fConst237 = (2 * (53.5362 - this.fConst215));
		this.fConst238 = (1 / (((this.fConst187 + 0.512479) / this.fConst186) + 0.689621));
		this.fConst239 = (2 * (7.62173 - this.fConst215));
		this.fConst240 = (1 / (((this.fConst187 + 0.782413) / this.fConst186) + 0.245292));
		this.fConst241 = (0.0001 / this.fConst189);
		this.fConst242 = (2 * (0.000433227 - this.fConst241));
		this.fConst243 = (((this.fConst187 + -0.782413) / this.fConst186) + 0.245292);
		this.fConst244 = (2 * (0.245292 - this.fConst215));
		this.fConst245 = (this.fConst241 + 0.000433227);
		this.fConst246 = (((this.fConst187 + -0.512479) / this.fConst186) + 0.689621);
		this.fConst247 = (2 * (0.689621 - this.fConst215));
		this.fConst248 = (this.fConst215 + 7.62173);
		this.fConst249 = (((this.fConst187 + -0.168405) / this.fConst186) + 1.06936);
		this.fConst250 = (2 * (1.06936 - this.fConst215));
		this.fConst251 = (this.fConst215 + 53.5362);
		this.fConst252 = (((this.fConst225 + -3.18973) / this.fConst224) + 4.07678);
		this.fConst253 = (1 / this.fConst227);
		this.fConst254 = (2 * (4.07678 - this.fConst253));
		this.fConst255 = (this.fConst234 + 0.000407678);
		this.fConst256 = (((this.fConst225 + -0.74313) / this.fConst224) + 1.45007);
		this.fConst257 = (2 * (1.45007 - this.fConst253));
		this.fConst258 = (this.fConst231 + 1.45007);
		this.fConst259 = (((this.fConst225 + -0.157482) / this.fConst224) + 0.93514);
		this.fConst260 = (2 * (0.93514 - this.fConst253));
		this.fConst261 = (this.fConst228 + 0.93514);
		this.fConst262 = Math.tan((1979.08 / this.fConst0));
		this.fConst263 = (1 / this.fConst262);
		this.fConst264 = (1 / (((this.fConst263 + 0.157482) / this.fConst262) + 0.93514));
		this.fConst265 = mydsp_faustpower2_f(this.fConst262);
		this.fConst266 = (50.0638 / this.fConst265);
		this.fConst267 = (2 * (0.93514 - this.fConst266));
		this.fConst268 = (1 / (((this.fConst263 + 0.74313) / this.fConst262) + 1.45007));
		this.fConst269 = (11.0521 / this.fConst265);
		this.fConst270 = (2 * (1.45007 - this.fConst269));
		this.fConst271 = (1 / (((this.fConst263 + 3.18973) / this.fConst262) + 4.07678));
		this.fConst272 = (0.00176617 / this.fConst265);
		this.fConst273 = (2 * (0.000407678 - this.fConst272));
		this.fConst274 = (1 / (((this.fConst225 + 0.168405) / this.fConst224) + 1.06936));
		this.fConst275 = (2 * (53.5362 - this.fConst253));
		this.fConst276 = (1 / (((this.fConst225 + 0.512479) / this.fConst224) + 0.689621));
		this.fConst277 = (2 * (7.62173 - this.fConst253));
		this.fConst278 = (1 / (((this.fConst225 + 0.782413) / this.fConst224) + 0.245292));
		this.fConst279 = (0.0001 / this.fConst227);
		this.fConst280 = (2 * (0.000433227 - this.fConst279));
		this.fConst281 = (((this.fConst225 + -0.782413) / this.fConst224) + 0.245292);
		this.fConst282 = (2 * (0.245292 - this.fConst253));
		this.fConst283 = (this.fConst279 + 0.000433227);
		this.fConst284 = (((this.fConst225 + -0.512479) / this.fConst224) + 0.689621);
		this.fConst285 = (2 * (0.689621 - this.fConst253));
		this.fConst286 = (this.fConst253 + 7.62173);
		this.fConst287 = (((this.fConst225 + -0.168405) / this.fConst224) + 1.06936);
		this.fConst288 = (2 * (1.06936 - this.fConst253));
		this.fConst289 = (this.fConst253 + 53.5362);
		this.fConst290 = (((this.fConst263 + -3.18973) / this.fConst262) + 4.07678);
		this.fConst291 = (1 / this.fConst265);
		this.fConst292 = (2 * (4.07678 - this.fConst291));
		this.fConst293 = (this.fConst272 + 0.000407678);
		this.fConst294 = (((this.fConst263 + -0.74313) / this.fConst262) + 1.45007);
		this.fConst295 = (2 * (1.45007 - this.fConst291));
		this.fConst296 = (this.fConst269 + 1.45007);
		this.fConst297 = (((this.fConst263 + -0.157482) / this.fConst262) + 0.93514);
		this.fConst298 = (2 * (0.93514 - this.fConst291));
		this.fConst299 = (this.fConst266 + 0.93514);
		this.fConst300 = Math.tan((1246.74 / this.fConst0));
		this.fConst301 = (1 / this.fConst300);
		this.fConst302 = (1 / (((this.fConst301 + 0.157482) / this.fConst300) + 0.93514));
		this.fConst303 = mydsp_faustpower2_f(this.fConst300);
		this.fConst304 = (50.0638 / this.fConst303);
		this.fConst305 = (2 * (0.93514 - this.fConst304));
		this.fConst306 = (1 / (((this.fConst301 + 0.74313) / this.fConst300) + 1.45007));
		this.fConst307 = (11.0521 / this.fConst303);
		this.fConst308 = (2 * (1.45007 - this.fConst307));
		this.fConst309 = (1 / (((this.fConst301 + 3.18973) / this.fConst300) + 4.07678));
		this.fConst310 = (0.00176617 / this.fConst303);
		this.fConst311 = (2 * (0.000407678 - this.fConst310));
		this.fConst312 = (1 / (((this.fConst263 + 0.168405) / this.fConst262) + 1.06936));
		this.fConst313 = (2 * (53.5362 - this.fConst291));
		this.fConst314 = (1 / (((this.fConst263 + 0.512479) / this.fConst262) + 0.689621));
		this.fConst315 = (2 * (7.62173 - this.fConst291));
		this.fConst316 = (1 / (((this.fConst263 + 0.782413) / this.fConst262) + 0.245292));
		this.fConst317 = (0.0001 / this.fConst265);
		this.fConst318 = (2 * (0.000433227 - this.fConst317));
		this.fConst319 = (((this.fConst263 + -0.782413) / this.fConst262) + 0.245292);
		this.fConst320 = (2 * (0.245292 - this.fConst291));
		this.fConst321 = (this.fConst317 + 0.000433227);
		this.fConst322 = (((this.fConst263 + -0.512479) / this.fConst262) + 0.689621);
		this.fConst323 = (2 * (0.689621 - this.fConst291));
		this.fConst324 = (this.fConst291 + 7.62173);
		this.fConst325 = (((this.fConst263 + -0.168405) / this.fConst262) + 1.06936);
		this.fConst326 = (2 * (1.06936 - this.fConst291));
		this.fConst327 = (this.fConst291 + 53.5362);
		this.fConst328 = (((this.fConst301 + -3.18973) / this.fConst300) + 4.07678);
		this.fConst329 = (1 / this.fConst303);
		this.fConst330 = (2 * (4.07678 - this.fConst329));
		this.fConst331 = (this.fConst310 + 0.000407678);
		this.fConst332 = (((this.fConst301 + -0.74313) / this.fConst300) + 1.45007);
		this.fConst333 = (2 * (1.45007 - this.fConst329));
		this.fConst334 = (this.fConst307 + 1.45007);
		this.fConst335 = (((this.fConst301 + -0.157482) / this.fConst300) + 0.93514);
		this.fConst336 = (2 * (0.93514 - this.fConst329));
		this.fConst337 = (this.fConst304 + 0.93514);
		this.fConst338 = Math.tan((785.398 / this.fConst0));
		this.fConst339 = (1 / this.fConst338);
		this.fConst340 = (1 / (((this.fConst339 + 0.157482) / this.fConst338) + 0.93514));
		this.fConst341 = mydsp_faustpower2_f(this.fConst338);
		this.fConst342 = (50.0638 / this.fConst341);
		this.fConst343 = (2 * (0.93514 - this.fConst342));
		this.fConst344 = (1 / (((this.fConst339 + 0.74313) / this.fConst338) + 1.45007));
		this.fConst345 = (11.0521 / this.fConst341);
		this.fConst346 = (2 * (1.45007 - this.fConst345));
		this.fConst347 = (1 / (((this.fConst339 + 3.18973) / this.fConst338) + 4.07678));
		this.fConst348 = (0.00176617 / this.fConst341);
		this.fConst349 = (2 * (0.000407678 - this.fConst348));
		this.fConst350 = (1 / (((this.fConst301 + 0.168405) / this.fConst300) + 1.06936));
		this.fConst351 = (2 * (53.5362 - this.fConst329));
		this.fConst352 = (1 / (((this.fConst301 + 0.512479) / this.fConst300) + 0.689621));
		this.fConst353 = (2 * (7.62173 - this.fConst329));
		this.fConst354 = (1 / (((this.fConst301 + 0.782413) / this.fConst300) + 0.245292));
		this.fConst355 = (0.0001 / this.fConst303);
		this.fConst356 = (2 * (0.000433227 - this.fConst355));
		this.fConst357 = (((this.fConst301 + -0.782413) / this.fConst300) + 0.245292);
		this.fConst358 = (2 * (0.245292 - this.fConst329));
		this.fConst359 = (this.fConst355 + 0.000433227);
		this.fConst360 = (((this.fConst301 + -0.512479) / this.fConst300) + 0.689621);
		this.fConst361 = (2 * (0.689621 - this.fConst329));
		this.fConst362 = (this.fConst329 + 7.62173);
		this.fConst363 = (((this.fConst301 + -0.168405) / this.fConst300) + 1.06936);
		this.fConst364 = (2 * (1.06936 - this.fConst329));
		this.fConst365 = (this.fConst329 + 53.5362);
		this.fConst366 = (((this.fConst339 + -3.18973) / this.fConst338) + 4.07678);
		this.fConst367 = (1 / this.fConst341);
		this.fConst368 = (2 * (4.07678 - this.fConst367));
		this.fConst369 = (this.fConst348 + 0.000407678);
		this.fConst370 = (((this.fConst339 + -0.74313) / this.fConst338) + 1.45007);
		this.fConst371 = (2 * (1.45007 - this.fConst367));
		this.fConst372 = (this.fConst345 + 1.45007);
		this.fConst373 = (((this.fConst339 + -0.157482) / this.fConst338) + 0.93514);
		this.fConst374 = (2 * (0.93514 - this.fConst367));
		this.fConst375 = (this.fConst342 + 0.93514);
		this.fConst376 = Math.tan((494.77 / this.fConst0));
		this.fConst377 = (1 / this.fConst376);
		this.fConst378 = (1 / (((this.fConst377 + 0.157482) / this.fConst376) + 0.93514));
		this.fConst379 = mydsp_faustpower2_f(this.fConst376);
		this.fConst380 = (50.0638 / this.fConst379);
		this.fConst381 = (2 * (0.93514 - this.fConst380));
		this.fConst382 = (1 / (((this.fConst377 + 0.74313) / this.fConst376) + 1.45007));
		this.fConst383 = (11.0521 / this.fConst379);
		this.fConst384 = (2 * (1.45007 - this.fConst383));
		this.fConst385 = (1 / (((this.fConst377 + 3.18973) / this.fConst376) + 4.07678));
		this.fConst386 = (0.00176617 / this.fConst379);
		this.fConst387 = (2 * (0.000407678 - this.fConst386));
		this.fConst388 = (1 / (((this.fConst339 + 0.168405) / this.fConst338) + 1.06936));
		this.fConst389 = (2 * (53.5362 - this.fConst367));
		this.fConst390 = (1 / (((this.fConst339 + 0.512479) / this.fConst338) + 0.689621));
		this.fConst391 = (2 * (7.62173 - this.fConst367));
		this.fConst392 = (1 / (((this.fConst339 + 0.782413) / this.fConst338) + 0.245292));
		this.fConst393 = (0.0001 / this.fConst341);
		this.fConst394 = (2 * (0.000433227 - this.fConst393));
		this.fConst395 = (((this.fConst339 + -0.782413) / this.fConst338) + 0.245292);
		this.fConst396 = (2 * (0.245292 - this.fConst367));
		this.fConst397 = (this.fConst393 + 0.000433227);
		this.fConst398 = (((this.fConst339 + -0.512479) / this.fConst338) + 0.689621);
		this.fConst399 = (2 * (0.689621 - this.fConst367));
		this.fConst400 = (this.fConst367 + 7.62173);
		this.fConst401 = (((this.fConst339 + -0.168405) / this.fConst338) + 1.06936);
		this.fConst402 = (2 * (1.06936 - this.fConst367));
		this.fConst403 = (this.fConst367 + 53.5362);
		this.fConst404 = (((this.fConst377 + -3.18973) / this.fConst376) + 4.07678);
		this.fConst405 = (1 / this.fConst379);
		this.fConst406 = (2 * (4.07678 - this.fConst405));
		this.fConst407 = (this.fConst386 + 0.000407678);
		this.fConst408 = (((this.fConst377 + -0.74313) / this.fConst376) + 1.45007);
		this.fConst409 = (2 * (1.45007 - this.fConst405));
		this.fConst410 = (this.fConst383 + 1.45007);
		this.fConst411 = (((this.fConst377 + -0.157482) / this.fConst376) + 0.93514);
		this.fConst412 = (2 * (0.93514 - this.fConst405));
		this.fConst413 = (this.fConst380 + 0.93514);
		this.fConst414 = Math.tan((311.685 / this.fConst0));
		this.fConst415 = (1 / this.fConst414);
		this.fConst416 = (1 / (((this.fConst415 + 0.157482) / this.fConst414) + 0.93514));
		this.fConst417 = mydsp_faustpower2_f(this.fConst414);
		this.fConst418 = (50.0638 / this.fConst417);
		this.fConst419 = (2 * (0.93514 - this.fConst418));
		this.fConst420 = (1 / (((this.fConst415 + 0.74313) / this.fConst414) + 1.45007));
		this.fConst421 = (11.0521 / this.fConst417);
		this.fConst422 = (2 * (1.45007 - this.fConst421));
		this.fConst423 = (1 / (((this.fConst415 + 3.18973) / this.fConst414) + 4.07678));
		this.fConst424 = (0.00176617 / this.fConst417);
		this.fConst425 = (2 * (0.000407678 - this.fConst424));
		this.fConst426 = (1 / (((this.fConst377 + 0.168405) / this.fConst376) + 1.06936));
		this.fConst427 = (2 * (53.5362 - this.fConst405));
		this.fConst428 = (1 / (((this.fConst377 + 0.512479) / this.fConst376) + 0.689621));
		this.fConst429 = (2 * (7.62173 - this.fConst405));
		this.fConst430 = (1 / (((this.fConst377 + 0.782413) / this.fConst376) + 0.245292));
		this.fConst431 = (0.0001 / this.fConst379);
		this.fConst432 = (2 * (0.000433227 - this.fConst431));
		this.fConst433 = (((this.fConst377 + -0.782413) / this.fConst376) + 0.245292);
		this.fConst434 = (2 * (0.245292 - this.fConst405));
		this.fConst435 = (this.fConst431 + 0.000433227);
		this.fConst436 = (((this.fConst377 + -0.512479) / this.fConst376) + 0.689621);
		this.fConst437 = (2 * (0.689621 - this.fConst405));
		this.fConst438 = (this.fConst405 + 7.62173);
		this.fConst439 = (((this.fConst377 + -0.168405) / this.fConst376) + 1.06936);
		this.fConst440 = (2 * (1.06936 - this.fConst405));
		this.fConst441 = (this.fConst405 + 53.5362);
		this.fConst442 = (((this.fConst415 + -3.18973) / this.fConst414) + 4.07678);
		this.fConst443 = (1 / this.fConst417);
		this.fConst444 = (2 * (4.07678 - this.fConst443));
		this.fConst445 = (this.fConst424 + 0.000407678);
		this.fConst446 = (((this.fConst415 + -0.74313) / this.fConst414) + 1.45007);
		this.fConst447 = (2 * (1.45007 - this.fConst443));
		this.fConst448 = (this.fConst421 + 1.45007);
		this.fConst449 = (((this.fConst415 + -0.157482) / this.fConst414) + 0.93514);
		this.fConst450 = (2 * (0.93514 - this.fConst443));
		this.fConst451 = (this.fConst418 + 0.93514);
		this.fConst452 = Math.tan((196.35 / this.fConst0));
		this.fConst453 = (1 / this.fConst452);
		this.fConst454 = (1 / (((this.fConst453 + 0.157482) / this.fConst452) + 0.93514));
		this.fConst455 = mydsp_faustpower2_f(this.fConst452);
		this.fConst456 = (50.0638 / this.fConst455);
		this.fConst457 = (2 * (0.93514 - this.fConst456));
		this.fConst458 = (1 / (((this.fConst453 + 0.74313) / this.fConst452) + 1.45007));
		this.fConst459 = (11.0521 / this.fConst455);
		this.fConst460 = (2 * (1.45007 - this.fConst459));
		this.fConst461 = (1 / (((this.fConst453 + 3.18973) / this.fConst452) + 4.07678));
		this.fConst462 = (0.00176617 / this.fConst455);
		this.fConst463 = (2 * (0.000407678 - this.fConst462));
		this.fConst464 = (1 / (((this.fConst415 + 0.168405) / this.fConst414) + 1.06936));
		this.fConst465 = (2 * (53.5362 - this.fConst443));
		this.fConst466 = (1 / (((this.fConst415 + 0.512479) / this.fConst414) + 0.689621));
		this.fConst467 = (2 * (7.62173 - this.fConst443));
		this.fConst468 = (1 / (((this.fConst415 + 0.782413) / this.fConst414) + 0.245292));
		this.fConst469 = (0.0001 / this.fConst417);
		this.fConst470 = (2 * (0.000433227 - this.fConst469));
		this.fConst471 = (((this.fConst415 + -0.782413) / this.fConst414) + 0.245292);
		this.fConst472 = (2 * (0.245292 - this.fConst443));
		this.fConst473 = (this.fConst469 + 0.000433227);
		this.fConst474 = (((this.fConst415 + -0.512479) / this.fConst414) + 0.689621);
		this.fConst475 = (2 * (0.689621 - this.fConst443));
		this.fConst476 = (this.fConst443 + 7.62173);
		this.fConst477 = (((this.fConst415 + -0.168405) / this.fConst414) + 1.06936);
		this.fConst478 = (2 * (1.06936 - this.fConst443));
		this.fConst479 = (this.fConst443 + 53.5362);
		this.fConst480 = (((this.fConst453 + -3.18973) / this.fConst452) + 4.07678);
		this.fConst481 = (1 / this.fConst455);
		this.fConst482 = (2 * (4.07678 - this.fConst481));
		this.fConst483 = (this.fConst462 + 0.000407678);
		this.fConst484 = (((this.fConst453 + -0.74313) / this.fConst452) + 1.45007);
		this.fConst485 = (2 * (1.45007 - this.fConst481));
		this.fConst486 = (this.fConst459 + 1.45007);
		this.fConst487 = (((this.fConst453 + -0.157482) / this.fConst452) + 0.93514);
		this.fConst488 = (2 * (0.93514 - this.fConst481));
		this.fConst489 = (this.fConst456 + 0.93514);
		this.fConst490 = Math.tan((123.692 / this.fConst0));
		this.fConst491 = (1 / this.fConst490);
		this.fConst492 = (1 / (((this.fConst491 + 0.157482) / this.fConst490) + 0.93514));
		this.fConst493 = mydsp_faustpower2_f(this.fConst490);
		this.fConst494 = (50.0638 / this.fConst493);
		this.fConst495 = (2 * (0.93514 - this.fConst494));
		this.fConst496 = (1 / (((this.fConst491 + 0.74313) / this.fConst490) + 1.45007));
		this.fConst497 = (11.0521 / this.fConst493);
		this.fConst498 = (2 * (1.45007 - this.fConst497));
		this.fConst499 = (1 / (((this.fConst491 + 3.18973) / this.fConst490) + 4.07678));
		this.fConst500 = (0.00176617 / this.fConst493);
		this.fConst501 = (2 * (0.000407678 - this.fConst500));
		this.fConst502 = (1 / (((this.fConst453 + 0.168405) / this.fConst452) + 1.06936));
		this.fConst503 = (2 * (53.5362 - this.fConst481));
		this.fConst504 = (1 / (((this.fConst453 + 0.512479) / this.fConst452) + 0.689621));
		this.fConst505 = (2 * (7.62173 - this.fConst481));
		this.fConst506 = (1 / (((this.fConst453 + 0.782413) / this.fConst452) + 0.245292));
		this.fConst507 = (0.0001 / this.fConst455);
		this.fConst508 = (2 * (0.000433227 - this.fConst507));
		this.fConst509 = (((this.fConst453 + -0.782413) / this.fConst452) + 0.245292);
		this.fConst510 = (2 * (0.245292 - this.fConst481));
		this.fConst511 = (this.fConst507 + 0.000433227);
		this.fConst512 = (((this.fConst453 + -0.512479) / this.fConst452) + 0.689621);
		this.fConst513 = (2 * (0.689621 - this.fConst481));
		this.fConst514 = (this.fConst481 + 7.62173);
		this.fConst515 = (((this.fConst453 + -0.168405) / this.fConst452) + 1.06936);
		this.fConst516 = (2 * (1.06936 - this.fConst481));
		this.fConst517 = (this.fConst481 + 53.5362);
		this.fConst518 = (((this.fConst491 + -3.18973) / this.fConst490) + 4.07678);
		this.fConst519 = (1 / this.fConst493);
		this.fConst520 = (2 * (4.07678 - this.fConst519));
		this.fConst521 = (this.fConst500 + 0.000407678);
		this.fConst522 = (((this.fConst491 + -0.74313) / this.fConst490) + 1.45007);
		this.fConst523 = (2 * (1.45007 - this.fConst519));
		this.fConst524 = (this.fConst497 + 1.45007);
		this.fConst525 = (((this.fConst491 + -0.157482) / this.fConst490) + 0.93514);
		this.fConst526 = (2 * (0.93514 - this.fConst519));
		this.fConst527 = (this.fConst494 + 0.93514);
		this.fConst528 = (1 / (((this.fConst491 + 0.168405) / this.fConst490) + 1.06936));
		this.fConst529 = (2 * (53.5362 - this.fConst519));
		this.fConst530 = (1 / (((this.fConst491 + 0.512479) / this.fConst490) + 0.689621));
		this.fConst531 = (2 * (7.62173 - this.fConst519));
		this.fConst532 = (1 / (((this.fConst491 + 0.782413) / this.fConst490) + 0.245292));
		this.fConst533 = (0.0001 / this.fConst493);
		this.fConst534 = (2 * (0.000433227 - this.fConst533));
		this.fConst535 = (((this.fConst491 + -0.782413) / this.fConst490) + 0.245292);
		this.fConst536 = (2 * (0.245292 - this.fConst519));
		this.fConst537 = (this.fConst533 + 0.000433227);
		this.fConst538 = (((this.fConst491 + -0.512479) / this.fConst490) + 0.689621);
		this.fConst539 = (2 * (0.689621 - this.fConst519));
		this.fConst540 = (this.fConst519 + 7.62173);
		this.fConst541 = (((this.fConst491 + -0.168405) / this.fConst490) + 1.06936);
		this.fConst542 = (2 * (1.06936 - this.fConst519));
		this.fConst543 = (this.fConst519 + 53.5362);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		this.fCheckbox0 = 0;
		this.fHslider2 = 5;
		this.fCheckbox1 = 0;
		this.fVslider0 = 0;
		this.fHslider3 = -20;
		this.fVslider1 = 1;
		this.fEntry0 = 2;
		this.fHslider4 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fVslider5 = 0;
		this.fVslider6 = 0;
		this.fVslider7 = 0;
		this.fCheckbox2 = 0;
		this.fVslider8 = 0.5;
		this.fVslider9 = 0;
		this.fHslider5 = 25;
		this.fHslider6 = 0.9;
		this.fCheckbox3 = 0;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec4[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec10[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec12[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fVec1[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec11[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this.fVec2[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this.fVec3[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fVec4[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec5[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fVec6[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this.fVec7[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fVec8[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec13[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fVec9[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			this.fVec10[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fVec11[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fVec12[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fVec13[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this.fVec14[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this.fVec15[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec14[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fVec16[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this.fVec17[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fVec18[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fVec19[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fVec20[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fVec21[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fVec22[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec15[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fVec23[l30] = 0;
			
		}
		this.IOTA = 0;
		for (var l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			this.fVec24[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fVec25[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec16[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fVec26[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 4096); l35 = (l35 + 1)) {
			this.fVec27[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			this.fVec28[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec17[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fVec29[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			this.fVec30[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this.fRec18[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec19[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec20[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this.fRec21[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			this.fVec31[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fVec32[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 4096); l46 = (l46 + 1)) {
			this.fVec33[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			this.fVec34[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			this.fVec35[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 4096); l49 = (l49 + 1)) {
			this.fVec36[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fVec37[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			this.fVec38[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 4096); l52 = (l52 + 1)) {
			this.fVec39[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.iRec23[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			this.fRec22[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec24[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			this.fRec9[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec8[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			this.fRec7[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fRec6[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			this.fRec5[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			this.fRec27[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec26[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec25[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			this.fRec30[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			this.fRec28[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			this.fRec33[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			this.fRec31[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec3[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			this.fRec2[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			this.fRec1[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			this.fRec0[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec40[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			this.fRec39[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec38[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec37[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec36[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			this.fRec35[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			this.fRec34[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec47[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec46[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			this.fRec45[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec44[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec43[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec42[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			this.fRec41[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec54[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			this.fRec53[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec52[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec51[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec50[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			this.fRec49[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			this.fRec48[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec61[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec60[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec59[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec58[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			this.fRec57[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			this.fRec56[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			this.fRec55[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec68[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			this.fRec67[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec66[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec65[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			this.fRec64[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			this.fRec63[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			this.fRec62[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec75[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			this.fRec74[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			this.fRec73[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			this.fRec72[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			this.fRec71[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			this.fRec70[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			this.fRec69[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			this.fRec82[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			this.fRec81[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec80[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			this.fRec79[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			this.fRec78[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			this.fRec77[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			this.fRec76[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			this.fRec89[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			this.fRec88[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec87[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec86[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			this.fRec85[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			this.fRec84[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			this.fRec83[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			this.fRec96[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			this.fRec95[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			this.fRec94[l130] = 0;
			
		}
		for (var l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			this.fRec93[l131] = 0;
			
		}
		for (var l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			this.fRec92[l132] = 0;
			
		}
		for (var l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			this.fRec91[l133] = 0;
			
		}
		for (var l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			this.fRec90[l134] = 0;
			
		}
		for (var l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			this.fRec103[l135] = 0;
			
		}
		for (var l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			this.fRec102[l136] = 0;
			
		}
		for (var l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			this.fRec101[l137] = 0;
			
		}
		for (var l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			this.fRec100[l138] = 0;
			
		}
		for (var l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			this.fRec99[l139] = 0;
			
		}
		for (var l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			this.fRec98[l140] = 0;
			
		}
		for (var l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			this.fRec97[l141] = 0;
			
		}
		for (var l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			this.fRec110[l142] = 0;
			
		}
		for (var l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			this.fRec109[l143] = 0;
			
		}
		for (var l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			this.fRec108[l144] = 0;
			
		}
		for (var l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			this.fRec107[l145] = 0;
			
		}
		for (var l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			this.fRec106[l146] = 0;
			
		}
		for (var l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			this.fRec105[l147] = 0;
			
		}
		for (var l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			this.fRec104[l148] = 0;
			
		}
		for (var l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			this.fRec117[l149] = 0;
			
		}
		for (var l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			this.fRec116[l150] = 0;
			
		}
		for (var l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			this.fRec115[l151] = 0;
			
		}
		for (var l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			this.fRec114[l152] = 0;
			
		}
		for (var l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			this.fRec113[l153] = 0;
			
		}
		for (var l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			this.fRec112[l154] = 0;
			
		}
		for (var l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			this.fRec111[l155] = 0;
			
		}
		for (var l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			this.fRec124[l156] = 0;
			
		}
		for (var l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			this.fRec123[l157] = 0;
			
		}
		for (var l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			this.fRec122[l158] = 0;
			
		}
		for (var l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			this.fRec121[l159] = 0;
			
		}
		for (var l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			this.fRec120[l160] = 0;
			
		}
		for (var l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			this.fRec119[l161] = 0;
			
		}
		for (var l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			this.fRec118[l162] = 0;
			
		}
		for (var l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			this.fRec128[l163] = 0;
			
		}
		for (var l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			this.fRec127[l164] = 0;
			
		}
		for (var l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			this.fRec126[l165] = 0;
			
		}
		for (var l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			this.fRec125[l166] = 0;
			
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
		ui_interface.addVerticalSlider("Sawtooth", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.declare("0", "1", "");
		ui_interface.openVerticalBox("Pulse Train");
		ui_interface.declare("fCheckbox2", "0", "");
		ui_interface.declare("fCheckbox2", "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface.addCheckButton("Order 3", function handler(obj) { function setval(val) { obj.fCheckbox2 = val; } return setval; }(this));
		ui_interface.declare("fVslider7", "1", "");
		ui_interface.declare("fVslider7", "style", "vslider");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "style", "knob");
		ui_interface.addVerticalSlider("Duty Cycle", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fVslider5", "2", "");
		ui_interface.declare("fVslider5", "style", "vslider");
		ui_interface.addVerticalSlider("Square", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider6", "3", "");
		ui_interface.declare("fVslider6", "style", "vslider");
		ui_interface.addVerticalSlider("Triangle", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider9", "4", "");
		ui_interface.declare("fVslider9", "style", "vslider");
		ui_interface.declare("fVslider9", "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface.addVerticalSlider("Pink Noise", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.declare("fVslider0", "5", "");
		ui_interface.declare("fVslider0", "style", "vslider");
		ui_interface.addVerticalSlider("Ext Input", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("Signal Parameters");
		ui_interface.declare("0", "0", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "style", "hslider");
		ui_interface.declare("fHslider3", "tooltip", "Sawtooth waveform amplitude");
		ui_interface.declare("fHslider3", "unit", "dB");
		ui_interface.addHorizontalSlider("Mix Amplitude", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), -20, -120, 10, 0.1);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "hslider");
		ui_interface.declare("fHslider4", "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface.declare("fHslider4", "unit", "PK");
		ui_interface.addHorizontalSlider("Frequency", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 49, 1, 88, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fVslider3", "3", "");
		ui_interface.declare("fVslider3", "style", "knob");
		ui_interface.declare("fVslider3", "tooltip", "Percentange frequency-shift up or down for second oscillator");
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
		ui_interface.declare("fEntry0", "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface.addNumEntry("Saw Order", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 2, 1, 4, 1);
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
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox1", "1", "");
		ui_interface.declare("fCheckbox1", "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface.addCheckButton("Use Biquads", function handler(obj) { function setval(val) { obj.fCheckbox1 = val; } return setval; }(this));
		ui_interface.declare("fCheckbox3", "2", "");
		ui_interface.declare("fCheckbox3", "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)");
		ui_interface.addCheckButton("Normalized Ladders", function handler(obj) { function setval(val) { obj.fCheckbox3 = val; } return setval; }(this));
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
		ui_interface.declare("0", "3", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph14", "0", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7c2b730", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7c19dd0", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7bf3d00", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7bd1bb0", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7bafa60", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7b8d910", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7b6b7c0", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7b49670", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7b27520", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7b053d0", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7adf300", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7abd1b0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7a9b180", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7a79030", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fcea7a55e50", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
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
		var fSlow6 = this.fVslider0;
		var fSlow7 = (0.001 * Math.pow(10, (0.05 * this.fHslider3)));
		var fSlow8 = (0.333333 * this.fVslider1);
		var iSlow9 = (this.fEntry0 + -1);
		var iSlow10 = (iSlow9 >= 2);
		var iSlow11 = (iSlow9 >= 1);
		var fSlow12 = Math.exp((0 - (this.fConst14 / this.fVslider2)));
		var fSlow13 = (440 * (Math.pow(2, (0.0833333 * (this.fHslider4 + -49))) * (1 - fSlow12)));
		var iSlow14 = (iSlow9 >= 3);
		var fSlow15 = (1 - (0.01 * this.fVslider3));
		var fSlow16 = ((0.01 * this.fVslider4) + 1);
		var fSlow17 = (this.fConst18 * this.fVslider5);
		var fSlow18 = (this.fConst20 * this.fVslider6);
		var fSlow19 = (this.fConst0 * this.fVslider7);
		var fSlow20 = this.fCheckbox2;
		var fSlow21 = (0.0833333 * (1 - fSlow20));
		var fSlow22 = (0.01 * this.fVslider8);
		var fSlow23 = (this.fConst21 * fSlow20);
		var fSlow24 = this.fVslider9;
		var fSlow25 = (0.44 * Math.pow(2, (0.0833333 * (this.fHslider5 + -49))));
		var fSlow26 = this.fHslider6;
		var fSlow27 = (0 - (4 * max_f(0, min_f(mydsp_faustpower4_f(fSlow26), 0.999999))));
		var iSlow28 = this.fCheckbox3;
		var fSlow29 = min_f(1.4142, (1.41421 * fSlow26));
		var fSlow30 = (fSlow29 * (fSlow29 + 1.41421));
		var fSlow31 = (1.41421 * fSlow29);
		var fSlow32 = (fSlow31 + 2);
		var fSlow33 = (fSlow29 * (fSlow29 + -1.41421));
		var fSlow34 = (2 - fSlow31);
		var fSlow35 = mydsp_faustpower2_f((1.4142 * fSlow26));
		var fSlow36 = (1.99998 * fSlow26);
		var fSlow37 = (fSlow35 + fSlow36);
		var fSlow38 = (fSlow36 + 2);
		var fSlow39 = (2 - fSlow36);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec4[0] = (fSlow4 + (0.999 * this.fRec4[1]));
			this.fRec10[0] = (fSlow7 + (0.999 * this.fRec10[1]));
			this.fRec12[0] = (fSlow13 + (fSlow12 * this.fRec12[1]));
			var fTemp0 = max_f(20, Math.abs(this.fRec12[0]));
			this.fVec1[0] = fTemp0;
			var fTemp1 = (this.fRec11[1] + (this.fConst14 * this.fVec1[1]));
			this.fRec11[0] = (fTemp1 - Math.floor(fTemp1));
			var fTemp2 = (2 * this.fRec11[0]);
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
			var fTemp10 = (fSlow15 * this.fRec12[0]);
			var fTemp11 = max_f(20, Math.abs(fTemp10));
			this.fVec8[0] = fTemp11;
			var fTemp12 = (this.fRec13[1] + (this.fConst14 * this.fVec8[1]));
			this.fRec13[0] = (fTemp12 - Math.floor(fTemp12));
			var fTemp13 = (2 * this.fRec13[0]);
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
			var fTemp21 = (fSlow16 * this.fRec12[0]);
			var fTemp22 = max_f(20, Math.abs(fTemp21));
			this.fVec15[0] = fTemp22;
			var fTemp23 = (this.fRec14[1] + (this.fConst14 * this.fVec15[1]));
			this.fRec14[0] = (fTemp23 - Math.floor(fTemp23));
			var fTemp24 = (2 * this.fRec14[0]);
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
			var fTemp32 = max_f(this.fRec12[0], 23.4489);
			var fTemp33 = max_f(20, Math.abs(fTemp32));
			this.fVec22[0] = fTemp33;
			var fTemp34 = (this.fRec15[1] + (this.fConst14 * this.fVec22[1]));
			this.fRec15[0] = (fTemp34 - Math.floor(fTemp34));
			var fTemp35 = (2 * this.fRec15[0]);
			var fTemp36 = (fTemp35 + -1);
			var fTemp37 = mydsp_faustpower2_f(fTemp36);
			this.fVec23[0] = fTemp37;
			var fTemp38 = ((this.iVec0[1] * (fTemp37 - this.fVec23[1])) / fTemp33);
			this.fVec24[(this.IOTA & 4095)] = fTemp38;
			var fTemp39 = max_f(0, min_f(2047, (this.fConst19 / fTemp32)));
			var iTemp40 = fTemp39;
			var fTemp41 = Math.floor(fTemp39);
			var fTemp42 = ((fTemp38 - (this.fVec24[((this.IOTA - iTemp40) & 4095)] * (fTemp41 + (1 - fTemp39)))) - ((fTemp39 - fTemp41) * this.fVec24[((this.IOTA - (iTemp40 + 1)) & 4095)]));
			var fTemp43 = max_f(fTemp10, 23.4489);
			var fTemp44 = max_f(20, Math.abs(fTemp43));
			this.fVec25[0] = fTemp44;
			var fTemp45 = (this.fRec16[1] + (this.fConst14 * this.fVec25[1]));
			this.fRec16[0] = (fTemp45 - Math.floor(fTemp45));
			var fTemp46 = (2 * this.fRec16[0]);
			var fTemp47 = (fTemp46 + -1);
			var fTemp48 = mydsp_faustpower2_f(fTemp47);
			this.fVec26[0] = fTemp48;
			var fTemp49 = ((this.iVec0[1] * (fTemp48 - this.fVec26[1])) / fTemp44);
			this.fVec27[(this.IOTA & 4095)] = fTemp49;
			var fTemp50 = max_f(0, min_f(2047, (this.fConst19 / fTemp43)));
			var iTemp51 = fTemp50;
			var fTemp52 = Math.floor(fTemp50);
			var fTemp53 = ((fTemp49 - (this.fVec27[((this.IOTA - iTemp51) & 4095)] * (fTemp52 + (1 - fTemp50)))) - ((fTemp50 - fTemp52) * this.fVec27[((this.IOTA - (iTemp51 + 1)) & 4095)]));
			var fTemp54 = max_f(fTemp21, 23.4489);
			var fTemp55 = max_f(20, Math.abs(fTemp54));
			this.fVec28[0] = fTemp55;
			var fTemp56 = (this.fRec17[1] + (this.fConst14 * this.fVec28[1]));
			this.fRec17[0] = (fTemp56 - Math.floor(fTemp56));
			var fTemp57 = (2 * this.fRec17[0]);
			var fTemp58 = (fTemp57 + -1);
			var fTemp59 = mydsp_faustpower2_f(fTemp58);
			this.fVec29[0] = fTemp59;
			var fTemp60 = ((this.iVec0[1] * (fTemp59 - this.fVec29[1])) / fTemp55);
			this.fVec30[(this.IOTA & 4095)] = fTemp60;
			var fTemp61 = max_f(0, min_f(2047, (this.fConst19 / fTemp54)));
			var iTemp62 = fTemp61;
			var fTemp63 = Math.floor(fTemp61);
			var fTemp64 = ((fTemp60 - (this.fVec30[((this.IOTA - iTemp62) & 4095)] * (fTemp63 + (1 - fTemp61)))) - ((fTemp61 - fTemp63) * this.fVec30[((this.IOTA - (iTemp62 + 1)) & 4095)]));
			this.fRec18[0] = ((this.fConst15 * fTemp42) + (0.999 * this.fRec18[1]));
			this.fRec19[0] = ((this.fConst15 * fTemp53) + (0.999 * this.fRec19[1]));
			this.fRec20[0] = ((this.fConst15 * fTemp64) + (0.999 * this.fRec20[1]));
			this.fRec21[0] = (fSlow22 + (0.99 * this.fRec21[1]));
			var fTemp65 = max_f(0, min_f(2047, (this.fConst0 * (this.fRec21[0] / fTemp32))));
			var fTemp66 = Math.floor(fTemp65);
			var fTemp67 = (fTemp66 + (1 - fTemp65));
			var iTemp68 = fTemp65;
			var fTemp69 = (fTemp65 - fTemp66);
			var iTemp70 = (iTemp68 + 1);
			var fTemp71 = max_f(0, min_f(2047, (this.fConst0 * (this.fRec21[0] / fTemp43))));
			var fTemp72 = Math.floor(fTemp71);
			var fTemp73 = (fTemp72 + (1 - fTemp71));
			var iTemp74 = fTemp71;
			var fTemp75 = (fTemp71 - fTemp72);
			var iTemp76 = (iTemp74 + 1);
			var fTemp77 = max_f(0, min_f(2047, (this.fConst0 * (this.fRec21[0] / fTemp54))));
			var fTemp78 = Math.floor(fTemp77);
			var fTemp79 = (fTemp78 + (1 - fTemp77));
			var iTemp80 = fTemp77;
			var fTemp81 = (fTemp77 - fTemp78);
			var iTemp82 = (iTemp80 + 1);
			var fTemp83 = mydsp_faustpower3_f(fTemp36);
			this.fVec31[0] = (fTemp83 + (1 - fTemp35));
			var fTemp84 = ((fTemp83 + (1 - (fTemp35 + this.fVec31[1]))) / fTemp33);
			this.fVec32[0] = fTemp84;
			var fTemp85 = ((this.iVec0[2] * (fTemp84 - this.fVec32[1])) / fTemp33);
			this.fVec33[(this.IOTA & 4095)] = fTemp85;
			var fTemp86 = mydsp_faustpower3_f(fTemp47);
			this.fVec34[0] = (fTemp86 + (1 - fTemp46));
			var fTemp87 = ((fTemp86 + (1 - (fTemp46 + this.fVec34[1]))) / fTemp44);
			this.fVec35[0] = fTemp87;
			var fTemp88 = ((this.iVec0[2] * (fTemp87 - this.fVec35[1])) / fTemp44);
			this.fVec36[(this.IOTA & 4095)] = fTemp88;
			var fTemp89 = mydsp_faustpower3_f(fTemp58);
			this.fVec37[0] = (fTemp89 + (1 - fTemp57));
			var fTemp90 = ((fTemp89 + (1 - (fTemp57 + this.fVec37[1]))) / fTemp55);
			this.fVec38[0] = fTemp90;
			var fTemp91 = ((this.iVec0[2] * (fTemp90 - this.fVec38[1])) / fTemp55);
			this.fVec39[(this.IOTA & 4095)] = fTemp91;
			this.iRec23[0] = ((1103515245 * this.iRec23[1]) + 12345);
			this.fRec22[0] = (((0.522189 * this.fRec22[3]) + ((4.65661e-10 * this.iRec23[0]) + (2.49496 * this.fRec22[1]))) - (2.01727 * this.fRec22[2]));
			var fTemp92 = ((fSlow6 * input0[i]) + (this.fRec10[0] * (((((fSlow8 * (((iSlow10?(iSlow14?(this.fConst17 * ((this.iVec0[3] * (fTemp9 - this.fVec7[1])) / fTemp0)):(this.fConst16 * ((this.iVec0[2] * (fTemp6 - this.fVec4[1])) / fTemp0))):(iSlow11?(this.fConst15 * ((this.iVec0[1] * (fTemp4 - this.fVec2[1])) / fTemp0)):fTemp3)) + (iSlow10?(iSlow14?(this.fConst17 * ((this.iVec0[3] * (fTemp20 - this.fVec14[1])) / fTemp11)):(this.fConst16 * ((this.iVec0[2] * (fTemp17 - this.fVec11[1])) / fTemp11))):(iSlow11?(this.fConst15 * ((this.iVec0[1] * (fTemp15 - this.fVec9[1])) / fTemp11)):fTemp14))) + (iSlow10?(iSlow14?(this.fConst17 * ((this.iVec0[3] * (fTemp31 - this.fVec21[1])) / fTemp22)):(this.fConst16 * ((this.iVec0[2] * (fTemp28 - this.fVec18[1])) / fTemp22))):(iSlow11?(this.fConst15 * ((this.iVec0[1] * (fTemp26 - this.fVec16[1])) / fTemp22)):fTemp25)))) + (fSlow17 * ((fTemp42 + fTemp53) + fTemp64))) + (fSlow18 * (this.fRec12[0] * ((this.fRec18[0] + (fSlow15 * this.fRec19[0])) + (fSlow16 * this.fRec20[0]))))) + (fSlow19 * ((fSlow21 * ((((fTemp38 - (fTemp67 * this.fVec24[((this.IOTA - iTemp68) & 4095)])) - (fTemp69 * this.fVec24[((this.IOTA - iTemp70) & 4095)])) + ((fTemp49 - (fTemp73 * this.fVec27[((this.IOTA - iTemp74) & 4095)])) - (fTemp75 * this.fVec27[((this.IOTA - iTemp76) & 4095)]))) + ((fTemp60 - (fTemp79 * this.fVec30[((this.IOTA - iTemp80) & 4095)])) - (fTemp81 * this.fVec30[((this.IOTA - iTemp82) & 4095)])))) + (fSlow23 * ((((fTemp85 - (this.fVec33[((this.IOTA - iTemp68) & 4095)] * fTemp67)) - (fTemp69 * this.fVec33[((this.IOTA - iTemp70) & 4095)])) + ((fTemp88 - (this.fVec36[((this.IOTA - iTemp74) & 4095)] * fTemp73)) - (fTemp75 * this.fVec36[((this.IOTA - iTemp76) & 4095)]))) + ((fTemp91 - (this.fVec39[((this.IOTA - iTemp80) & 4095)] * fTemp79)) - (fTemp81 * this.fVec39[((this.IOTA - iTemp82) & 4095)]))))))) + (fSlow24 * (((0.049922 * this.fRec22[0]) + (0.0506127 * this.fRec22[2])) - ((0.0959935 * this.fRec22[1]) + (0.00440879 * this.fRec22[3])))))));
			var fTemp93 = (iSlow3?0:fTemp92);
			this.fRec24[0] = (fSlow25 + (0.999 * this.fRec24[1]));
			var fTemp94 = (this.fConst22 * this.fRec24[0]);
			var fTemp95 = (1 - fTemp94);
			this.fRec9[0] = (fTemp93 + ((fTemp95 * this.fRec9[1]) + (fSlow27 * this.fRec5[1])));
			this.fRec8[0] = (this.fRec9[0] + (fTemp95 * this.fRec8[1]));
			this.fRec7[0] = (this.fRec8[0] + (fTemp95 * this.fRec7[1]));
			this.fRec6[0] = (this.fRec7[0] + (this.fRec6[1] * fTemp95));
			this.fRec5[0] = (this.fRec6[0] * Math.pow(fTemp94, 4));
			this.fRec27[0] = (fSlow25 + (0.999 * this.fRec27[1]));
			var fTemp96 = Math.tan((this.fConst23 * max_f(20, min_f(10000, this.fRec27[0]))));
			var fTemp97 = (1 / fTemp96);
			var fTemp98 = (1 - (1 / mydsp_faustpower2_f(fTemp96)));
			var fTemp99 = (fSlow30 + (((fSlow32 + fTemp97) / fTemp96) + 1));
			this.fRec26[0] = (fTemp93 - (((this.fRec26[2] * (fSlow30 + (((fTemp97 - fSlow32) / fTemp96) + 1))) + (2 * (this.fRec26[1] * (fSlow30 + fTemp98)))) / fTemp99));
			var fTemp100 = (fSlow33 + (((fSlow34 + fTemp97) / fTemp96) + 1));
			this.fRec25[0] = (((this.fRec26[2] + (this.fRec26[0] + (2 * this.fRec26[1]))) / fTemp99) - (((this.fRec25[2] * (fSlow33 + (((fTemp97 - fSlow34) / fTemp96) + 1))) + (2 * (this.fRec25[1] * (fSlow33 + fTemp98)))) / fTemp100));
			var fTemp101 = Math.tan((this.fConst23 * max_f(this.fRec27[0], 20)));
			var fTemp102 = (1 / fTemp101);
			var fTemp103 = (fSlow37 + (((fSlow38 + fTemp102) / fTemp101) + 1));
			var fTemp104 = ((fSlow37 + (1 - ((fSlow38 - fTemp102) / fTemp101))) / fTemp103);
			var fTemp105 = max_f(-0.9999, min_f(0.9999, fTemp104));
			var fTemp106 = (1 - mydsp_faustpower2_f(fTemp105));
			var fTemp107 = Math.sqrt(max_f(0, fTemp106));
			var fTemp108 = ((this.fRec28[1] * (0 - fTemp105)) + (fTemp93 * fTemp107));
			var fTemp109 = (1 - (1 / mydsp_faustpower2_f(fTemp101)));
			var fTemp110 = (fSlow37 + fTemp109);
			var fTemp111 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp110 / (fTemp103 * (fTemp104 + 1))))));
			var fTemp112 = (1 - mydsp_faustpower2_f(fTemp111));
			var fTemp113 = Math.sqrt(max_f(0, fTemp112));
			this.fRec30[0] = ((this.fRec30[1] * (0 - fTemp111)) + (fTemp108 * fTemp113));
			this.fRec28[0] = ((fTemp108 * fTemp111) + (this.fRec30[1] * fTemp113));
			var fRec29 = this.fRec30[0];
			var fTemp114 = (1 - (fTemp110 / fTemp103));
			var fTemp115 = Math.sqrt(fTemp106);
			var fTemp116 = ((((fTemp93 * fTemp105) + (this.fRec28[1] * fTemp107)) + (2 * ((this.fRec28[0] * fTemp114) / fTemp115))) + ((fRec29 * ((1 - fTemp104) - (2 * (fTemp111 * fTemp114)))) / (fTemp115 * Math.sqrt(fTemp112))));
			var fTemp117 = (fSlow35 + ((((fSlow39 + fTemp102) / fTemp101) + 1) - fSlow36));
			var fTemp118 = ((fSlow35 + ((((fTemp102 - fSlow39) / fTemp101) + 1) - fSlow36)) / fTemp117);
			var fTemp119 = max_f(-0.9999, min_f(0.9999, fTemp118));
			var fTemp120 = (1 - mydsp_faustpower2_f(fTemp119));
			var fTemp121 = Math.sqrt(max_f(0, fTemp120));
			var fTemp122 = ((this.fRec31[1] * (0 - fTemp119)) + ((fTemp116 * fTemp121) / fTemp103));
			var fTemp123 = (fSlow35 + (fTemp109 - fSlow36));
			var fTemp124 = max_f(-0.9999, min_f(0.9999, (2 * (fTemp123 / (fTemp117 * (fTemp118 + 1))))));
			var fTemp125 = (1 - mydsp_faustpower2_f(fTemp124));
			var fTemp126 = Math.sqrt(max_f(0, fTemp125));
			this.fRec33[0] = ((this.fRec33[1] * (0 - fTemp124)) + (fTemp122 * fTemp126));
			this.fRec31[0] = ((fTemp122 * fTemp124) + (this.fRec33[1] * fTemp126));
			var fRec32 = this.fRec33[0];
			var fTemp127 = (1 - (fTemp123 / fTemp117));
			var fTemp128 = Math.sqrt(fTemp120);
			var fTemp129 = (iSlow3?fTemp92:(this.fRec4[0] * (iSlow5?(iSlow28?((((((fTemp116 * fTemp119) / fTemp103) + (this.fRec31[1] * fTemp121)) + (2 * ((this.fRec31[0] * fTemp127) / fTemp128))) + ((fRec32 * ((1 - fTemp118) - (2 * (fTemp124 * fTemp127)))) / (fTemp128 * Math.sqrt(fTemp125)))) / fTemp117):((this.fRec25[2] + (this.fRec25[0] + (2 * this.fRec25[1]))) / fTemp100)):this.fRec5[0])));
			this.fRec3[0] = (fTemp129 - (this.fConst11 * ((this.fConst24 * this.fRec3[2]) + (this.fConst26 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[1]) + (this.fConst27 * this.fRec3[0])) + (this.fConst27 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst28 * this.fRec2[2]) + (this.fConst29 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst30 * this.fRec2[0])) + (this.fConst30 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst31 * this.fRec1[2]) + (this.fConst32 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst33 * this.fRec1[0])) + (this.fConst33 * this.fRec1[2]))))));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec40[0] = (fTemp129 - (this.fConst50 * ((this.fConst53 * this.fRec40[2]) + (this.fConst54 * this.fRec40[1]))));
			this.fRec39[0] = ((this.fConst50 * (((this.fConst52 * this.fRec40[1]) + (this.fConst55 * this.fRec40[0])) + (this.fConst55 * this.fRec40[2]))) - (this.fConst48 * ((this.fConst56 * this.fRec39[2]) + (this.fConst57 * this.fRec39[1]))));
			this.fRec38[0] = ((this.fConst48 * (((this.fConst49 * this.fRec39[1]) + (this.fConst58 * this.fRec39[0])) + (this.fConst58 * this.fRec39[2]))) - (this.fConst46 * ((this.fConst59 * this.fRec38[2]) + (this.fConst60 * this.fRec38[1]))));
			var fTemp130 = (this.fConst46 * (((this.fConst47 * this.fRec38[1]) + (this.fConst61 * this.fRec38[0])) + (this.fConst61 * this.fRec38[2])));
			this.fRec37[0] = (fTemp130 - (this.fConst43 * ((this.fConst62 * this.fRec37[2]) + (this.fConst64 * this.fRec37[1]))));
			this.fRec36[0] = ((this.fConst43 * (((this.fConst45 * this.fRec37[1]) + (this.fConst65 * this.fRec37[0])) + (this.fConst65 * this.fRec37[2]))) - (this.fConst40 * ((this.fConst66 * this.fRec36[2]) + (this.fConst67 * this.fRec36[1]))));
			this.fRec35[0] = ((this.fConst40 * (((this.fConst42 * this.fRec36[1]) + (this.fConst68 * this.fRec36[0])) + (this.fConst68 * this.fRec36[2]))) - (this.fConst36 * ((this.fConst69 * this.fRec35[2]) + (this.fConst70 * this.fRec35[1]))));
			this.fRec34[0] = ((fSlow1 * this.fRec34[1]) + (fSlow2 * Math.abs((this.fConst36 * (((this.fConst39 * this.fRec35[1]) + (this.fConst71 * this.fRec35[0])) + (this.fConst71 * this.fRec35[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec34[0]))));
			this.fRec47[0] = (fTemp130 - (this.fConst88 * ((this.fConst91 * this.fRec47[2]) + (this.fConst92 * this.fRec47[1]))));
			this.fRec46[0] = ((this.fConst88 * (((this.fConst90 * this.fRec47[1]) + (this.fConst93 * this.fRec47[0])) + (this.fConst93 * this.fRec47[2]))) - (this.fConst86 * ((this.fConst94 * this.fRec46[2]) + (this.fConst95 * this.fRec46[1]))));
			this.fRec45[0] = ((this.fConst86 * (((this.fConst87 * this.fRec46[1]) + (this.fConst96 * this.fRec46[0])) + (this.fConst96 * this.fRec46[2]))) - (this.fConst84 * ((this.fConst97 * this.fRec45[2]) + (this.fConst98 * this.fRec45[1]))));
			var fTemp131 = (this.fConst84 * (((this.fConst85 * this.fRec45[1]) + (this.fConst99 * this.fRec45[0])) + (this.fConst99 * this.fRec45[2])));
			this.fRec44[0] = (fTemp131 - (this.fConst81 * ((this.fConst100 * this.fRec44[2]) + (this.fConst102 * this.fRec44[1]))));
			this.fRec43[0] = ((this.fConst81 * (((this.fConst83 * this.fRec44[1]) + (this.fConst103 * this.fRec44[0])) + (this.fConst103 * this.fRec44[2]))) - (this.fConst78 * ((this.fConst104 * this.fRec43[2]) + (this.fConst105 * this.fRec43[1]))));
			this.fRec42[0] = ((this.fConst78 * (((this.fConst80 * this.fRec43[1]) + (this.fConst106 * this.fRec43[0])) + (this.fConst106 * this.fRec43[2]))) - (this.fConst74 * ((this.fConst107 * this.fRec42[2]) + (this.fConst108 * this.fRec42[1]))));
			this.fRec41[0] = ((fSlow1 * this.fRec41[1]) + (fSlow2 * Math.abs((this.fConst74 * (((this.fConst77 * this.fRec42[1]) + (this.fConst109 * this.fRec42[0])) + (this.fConst109 * this.fRec42[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec41[0]))));
			this.fRec54[0] = (fTemp131 - (this.fConst126 * ((this.fConst129 * this.fRec54[2]) + (this.fConst130 * this.fRec54[1]))));
			this.fRec53[0] = ((this.fConst126 * (((this.fConst128 * this.fRec54[1]) + (this.fConst131 * this.fRec54[0])) + (this.fConst131 * this.fRec54[2]))) - (this.fConst124 * ((this.fConst132 * this.fRec53[2]) + (this.fConst133 * this.fRec53[1]))));
			this.fRec52[0] = ((this.fConst124 * (((this.fConst125 * this.fRec53[1]) + (this.fConst134 * this.fRec53[0])) + (this.fConst134 * this.fRec53[2]))) - (this.fConst122 * ((this.fConst135 * this.fRec52[2]) + (this.fConst136 * this.fRec52[1]))));
			var fTemp132 = (this.fConst122 * (((this.fConst123 * this.fRec52[1]) + (this.fConst137 * this.fRec52[0])) + (this.fConst137 * this.fRec52[2])));
			this.fRec51[0] = (fTemp132 - (this.fConst119 * ((this.fConst138 * this.fRec51[2]) + (this.fConst140 * this.fRec51[1]))));
			this.fRec50[0] = ((this.fConst119 * (((this.fConst121 * this.fRec51[0]) + (this.fConst141 * this.fRec51[1])) + (this.fConst121 * this.fRec51[2]))) - (this.fConst116 * ((this.fConst142 * this.fRec50[2]) + (this.fConst143 * this.fRec50[1]))));
			this.fRec49[0] = ((this.fConst116 * (((this.fConst118 * this.fRec50[1]) + (this.fConst144 * this.fRec50[0])) + (this.fConst144 * this.fRec50[2]))) - (this.fConst112 * ((this.fConst145 * this.fRec49[2]) + (this.fConst146 * this.fRec49[1]))));
			this.fRec48[0] = ((fSlow1 * this.fRec48[1]) + (fSlow2 * Math.abs((this.fConst112 * (((this.fConst115 * this.fRec49[1]) + (this.fConst147 * this.fRec49[0])) + (this.fConst147 * this.fRec49[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec48[0]))));
			this.fRec61[0] = (fTemp132 - (this.fConst164 * ((this.fConst167 * this.fRec61[2]) + (this.fConst168 * this.fRec61[1]))));
			this.fRec60[0] = ((this.fConst164 * (((this.fConst166 * this.fRec61[1]) + (this.fConst169 * this.fRec61[0])) + (this.fConst169 * this.fRec61[2]))) - (this.fConst162 * ((this.fConst170 * this.fRec60[2]) + (this.fConst171 * this.fRec60[1]))));
			this.fRec59[0] = ((this.fConst162 * (((this.fConst163 * this.fRec60[1]) + (this.fConst172 * this.fRec60[0])) + (this.fConst172 * this.fRec60[2]))) - (this.fConst160 * ((this.fConst173 * this.fRec59[2]) + (this.fConst174 * this.fRec59[1]))));
			var fTemp133 = (this.fConst160 * (((this.fConst161 * this.fRec59[1]) + (this.fConst175 * this.fRec59[0])) + (this.fConst175 * this.fRec59[2])));
			this.fRec58[0] = (fTemp133 - (this.fConst157 * ((this.fConst176 * this.fRec58[2]) + (this.fConst178 * this.fRec58[1]))));
			this.fRec57[0] = ((this.fConst157 * (((this.fConst159 * this.fRec58[1]) + (this.fConst179 * this.fRec58[0])) + (this.fConst179 * this.fRec58[2]))) - (this.fConst154 * ((this.fConst180 * this.fRec57[2]) + (this.fConst181 * this.fRec57[1]))));
			this.fRec56[0] = ((this.fConst154 * (((this.fConst156 * this.fRec57[1]) + (this.fConst182 * this.fRec57[0])) + (this.fConst182 * this.fRec57[2]))) - (this.fConst150 * ((this.fConst183 * this.fRec56[2]) + (this.fConst184 * this.fRec56[1]))));
			this.fRec55[0] = ((fSlow1 * this.fRec55[1]) + (fSlow2 * Math.abs((this.fConst150 * (((this.fConst153 * this.fRec56[1]) + (this.fConst185 * this.fRec56[0])) + (this.fConst185 * this.fRec56[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec55[0]))));
			this.fRec68[0] = (fTemp133 - (this.fConst202 * ((this.fConst205 * this.fRec68[2]) + (this.fConst206 * this.fRec68[1]))));
			this.fRec67[0] = ((this.fConst202 * (((this.fConst204 * this.fRec68[1]) + (this.fConst207 * this.fRec68[0])) + (this.fConst207 * this.fRec68[2]))) - (this.fConst200 * ((this.fConst208 * this.fRec67[2]) + (this.fConst209 * this.fRec67[1]))));
			this.fRec66[0] = ((this.fConst200 * (((this.fConst201 * this.fRec67[1]) + (this.fConst210 * this.fRec67[0])) + (this.fConst210 * this.fRec67[2]))) - (this.fConst198 * ((this.fConst211 * this.fRec66[2]) + (this.fConst212 * this.fRec66[1]))));
			var fTemp134 = (this.fConst198 * (((this.fConst199 * this.fRec66[1]) + (this.fConst213 * this.fRec66[0])) + (this.fConst213 * this.fRec66[2])));
			this.fRec65[0] = (fTemp134 - (this.fConst195 * ((this.fConst214 * this.fRec65[2]) + (this.fConst216 * this.fRec65[1]))));
			this.fRec64[0] = ((this.fConst195 * (((this.fConst197 * this.fRec65[1]) + (this.fConst217 * this.fRec65[0])) + (this.fConst217 * this.fRec65[2]))) - (this.fConst192 * ((this.fConst218 * this.fRec64[2]) + (this.fConst219 * this.fRec64[1]))));
			this.fRec63[0] = ((this.fConst192 * (((this.fConst194 * this.fRec64[1]) + (this.fConst220 * this.fRec64[0])) + (this.fConst220 * this.fRec64[2]))) - (this.fConst188 * ((this.fConst221 * this.fRec63[2]) + (this.fConst222 * this.fRec63[1]))));
			this.fRec62[0] = ((fSlow1 * this.fRec62[1]) + (fSlow2 * Math.abs((this.fConst188 * (((this.fConst191 * this.fRec63[1]) + (this.fConst223 * this.fRec63[0])) + (this.fConst223 * this.fRec63[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec62[0]))));
			this.fRec75[0] = (fTemp134 - (this.fConst240 * ((this.fConst243 * this.fRec75[2]) + (this.fConst244 * this.fRec75[1]))));
			this.fRec74[0] = ((this.fConst240 * (((this.fConst242 * this.fRec75[1]) + (this.fConst245 * this.fRec75[0])) + (this.fConst245 * this.fRec75[2]))) - (this.fConst238 * ((this.fConst246 * this.fRec74[2]) + (this.fConst247 * this.fRec74[1]))));
			this.fRec73[0] = ((this.fConst238 * (((this.fConst239 * this.fRec74[1]) + (this.fConst248 * this.fRec74[0])) + (this.fConst248 * this.fRec74[2]))) - (this.fConst236 * ((this.fConst249 * this.fRec73[2]) + (this.fConst250 * this.fRec73[1]))));
			var fTemp135 = (this.fConst236 * (((this.fConst237 * this.fRec73[1]) + (this.fConst251 * this.fRec73[0])) + (this.fConst251 * this.fRec73[2])));
			this.fRec72[0] = (fTemp135 - (this.fConst233 * ((this.fConst252 * this.fRec72[2]) + (this.fConst254 * this.fRec72[1]))));
			this.fRec71[0] = ((this.fConst233 * (((this.fConst235 * this.fRec72[1]) + (this.fConst255 * this.fRec72[0])) + (this.fConst255 * this.fRec72[2]))) - (this.fConst230 * ((this.fConst256 * this.fRec71[2]) + (this.fConst257 * this.fRec71[1]))));
			this.fRec70[0] = ((this.fConst230 * (((this.fConst232 * this.fRec71[1]) + (this.fConst258 * this.fRec71[0])) + (this.fConst258 * this.fRec71[2]))) - (this.fConst226 * ((this.fConst259 * this.fRec70[2]) + (this.fConst260 * this.fRec70[1]))));
			this.fRec69[0] = ((fSlow1 * this.fRec69[1]) + (fSlow2 * Math.abs((this.fConst226 * (((this.fConst229 * this.fRec70[1]) + (this.fConst261 * this.fRec70[0])) + (this.fConst261 * this.fRec70[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec69[0]))));
			this.fRec82[0] = (fTemp135 - (this.fConst278 * ((this.fConst281 * this.fRec82[2]) + (this.fConst282 * this.fRec82[1]))));
			this.fRec81[0] = ((this.fConst278 * (((this.fConst280 * this.fRec82[1]) + (this.fConst283 * this.fRec82[0])) + (this.fConst283 * this.fRec82[2]))) - (this.fConst276 * ((this.fConst284 * this.fRec81[2]) + (this.fConst285 * this.fRec81[1]))));
			this.fRec80[0] = ((this.fConst276 * (((this.fConst277 * this.fRec81[1]) + (this.fConst286 * this.fRec81[0])) + (this.fConst286 * this.fRec81[2]))) - (this.fConst274 * ((this.fConst287 * this.fRec80[2]) + (this.fConst288 * this.fRec80[1]))));
			var fTemp136 = (this.fConst274 * (((this.fConst275 * this.fRec80[1]) + (this.fConst289 * this.fRec80[0])) + (this.fConst289 * this.fRec80[2])));
			this.fRec79[0] = (fTemp136 - (this.fConst271 * ((this.fConst290 * this.fRec79[2]) + (this.fConst292 * this.fRec79[1]))));
			this.fRec78[0] = ((this.fConst271 * (((this.fConst273 * this.fRec79[1]) + (this.fConst293 * this.fRec79[0])) + (this.fConst293 * this.fRec79[2]))) - (this.fConst268 * ((this.fConst294 * this.fRec78[2]) + (this.fConst295 * this.fRec78[1]))));
			this.fRec77[0] = ((this.fConst268 * (((this.fConst270 * this.fRec78[1]) + (this.fConst296 * this.fRec78[0])) + (this.fConst296 * this.fRec78[2]))) - (this.fConst264 * ((this.fConst297 * this.fRec77[2]) + (this.fConst298 * this.fRec77[1]))));
			this.fRec76[0] = ((fSlow1 * this.fRec76[1]) + (fSlow2 * Math.abs((this.fConst264 * (((this.fConst267 * this.fRec77[1]) + (this.fConst299 * this.fRec77[0])) + (this.fConst299 * this.fRec77[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec76[0]))));
			this.fRec89[0] = (fTemp136 - (this.fConst316 * ((this.fConst319 * this.fRec89[2]) + (this.fConst320 * this.fRec89[1]))));
			this.fRec88[0] = ((this.fConst316 * (((this.fConst318 * this.fRec89[1]) + (this.fConst321 * this.fRec89[0])) + (this.fConst321 * this.fRec89[2]))) - (this.fConst314 * ((this.fConst322 * this.fRec88[2]) + (this.fConst323 * this.fRec88[1]))));
			this.fRec87[0] = ((this.fConst314 * (((this.fConst315 * this.fRec88[1]) + (this.fConst324 * this.fRec88[0])) + (this.fConst324 * this.fRec88[2]))) - (this.fConst312 * ((this.fConst325 * this.fRec87[2]) + (this.fConst326 * this.fRec87[1]))));
			var fTemp137 = (this.fConst312 * (((this.fConst313 * this.fRec87[1]) + (this.fConst327 * this.fRec87[0])) + (this.fConst327 * this.fRec87[2])));
			this.fRec86[0] = (fTemp137 - (this.fConst309 * ((this.fConst328 * this.fRec86[2]) + (this.fConst330 * this.fRec86[1]))));
			this.fRec85[0] = ((this.fConst309 * (((this.fConst311 * this.fRec86[1]) + (this.fConst331 * this.fRec86[0])) + (this.fConst331 * this.fRec86[2]))) - (this.fConst306 * ((this.fConst332 * this.fRec85[2]) + (this.fConst333 * this.fRec85[1]))));
			this.fRec84[0] = ((this.fConst306 * (((this.fConst308 * this.fRec85[1]) + (this.fConst334 * this.fRec85[0])) + (this.fConst334 * this.fRec85[2]))) - (this.fConst302 * ((this.fConst335 * this.fRec84[2]) + (this.fConst336 * this.fRec84[1]))));
			this.fRec83[0] = ((fSlow1 * this.fRec83[1]) + (fSlow2 * Math.abs((this.fConst302 * (((this.fConst305 * this.fRec84[1]) + (this.fConst337 * this.fRec84[0])) + (this.fConst337 * this.fRec84[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec83[0]))));
			this.fRec96[0] = (fTemp137 - (this.fConst354 * ((this.fConst357 * this.fRec96[2]) + (this.fConst358 * this.fRec96[1]))));
			this.fRec95[0] = ((this.fConst354 * (((this.fConst356 * this.fRec96[1]) + (this.fConst359 * this.fRec96[0])) + (this.fConst359 * this.fRec96[2]))) - (this.fConst352 * ((this.fConst360 * this.fRec95[2]) + (this.fConst361 * this.fRec95[1]))));
			this.fRec94[0] = ((this.fConst352 * (((this.fConst353 * this.fRec95[1]) + (this.fConst362 * this.fRec95[0])) + (this.fConst362 * this.fRec95[2]))) - (this.fConst350 * ((this.fConst363 * this.fRec94[2]) + (this.fConst364 * this.fRec94[1]))));
			var fTemp138 = (this.fConst350 * (((this.fConst351 * this.fRec94[1]) + (this.fConst365 * this.fRec94[0])) + (this.fConst365 * this.fRec94[2])));
			this.fRec93[0] = (fTemp138 - (this.fConst347 * ((this.fConst366 * this.fRec93[2]) + (this.fConst368 * this.fRec93[1]))));
			this.fRec92[0] = ((this.fConst347 * (((this.fConst349 * this.fRec93[1]) + (this.fConst369 * this.fRec93[0])) + (this.fConst369 * this.fRec93[2]))) - (this.fConst344 * ((this.fConst370 * this.fRec92[2]) + (this.fConst371 * this.fRec92[1]))));
			this.fRec91[0] = ((this.fConst344 * (((this.fConst346 * this.fRec92[1]) + (this.fConst372 * this.fRec92[0])) + (this.fConst372 * this.fRec92[2]))) - (this.fConst340 * ((this.fConst373 * this.fRec91[2]) + (this.fConst374 * this.fRec91[1]))));
			this.fRec90[0] = ((fSlow1 * this.fRec90[1]) + (fSlow2 * Math.abs((this.fConst340 * (((this.fConst343 * this.fRec91[1]) + (this.fConst375 * this.fRec91[0])) + (this.fConst375 * this.fRec91[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec90[0]))));
			this.fRec103[0] = (fTemp138 - (this.fConst392 * ((this.fConst395 * this.fRec103[2]) + (this.fConst396 * this.fRec103[1]))));
			this.fRec102[0] = ((this.fConst392 * (((this.fConst394 * this.fRec103[1]) + (this.fConst397 * this.fRec103[0])) + (this.fConst397 * this.fRec103[2]))) - (this.fConst390 * ((this.fConst398 * this.fRec102[2]) + (this.fConst399 * this.fRec102[1]))));
			this.fRec101[0] = ((this.fConst390 * (((this.fConst391 * this.fRec102[1]) + (this.fConst400 * this.fRec102[0])) + (this.fConst400 * this.fRec102[2]))) - (this.fConst388 * ((this.fConst401 * this.fRec101[2]) + (this.fConst402 * this.fRec101[1]))));
			var fTemp139 = (this.fConst388 * (((this.fConst389 * this.fRec101[1]) + (this.fConst403 * this.fRec101[0])) + (this.fConst403 * this.fRec101[2])));
			this.fRec100[0] = (fTemp139 - (this.fConst385 * ((this.fConst404 * this.fRec100[2]) + (this.fConst406 * this.fRec100[1]))));
			this.fRec99[0] = ((this.fConst385 * (((this.fConst387 * this.fRec100[1]) + (this.fConst407 * this.fRec100[0])) + (this.fConst407 * this.fRec100[2]))) - (this.fConst382 * ((this.fConst408 * this.fRec99[2]) + (this.fConst409 * this.fRec99[1]))));
			this.fRec98[0] = ((this.fConst382 * (((this.fConst384 * this.fRec99[1]) + (this.fConst410 * this.fRec99[0])) + (this.fConst410 * this.fRec99[2]))) - (this.fConst378 * ((this.fConst411 * this.fRec98[2]) + (this.fConst412 * this.fRec98[1]))));
			this.fRec97[0] = ((fSlow1 * this.fRec97[1]) + (fSlow2 * Math.abs((this.fConst378 * (((this.fConst381 * this.fRec98[1]) + (this.fConst413 * this.fRec98[0])) + (this.fConst413 * this.fRec98[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec97[0]))));
			this.fRec110[0] = (fTemp139 - (this.fConst430 * ((this.fConst433 * this.fRec110[2]) + (this.fConst434 * this.fRec110[1]))));
			this.fRec109[0] = ((this.fConst430 * (((this.fConst432 * this.fRec110[1]) + (this.fConst435 * this.fRec110[0])) + (this.fConst435 * this.fRec110[2]))) - (this.fConst428 * ((this.fConst436 * this.fRec109[2]) + (this.fConst437 * this.fRec109[1]))));
			this.fRec108[0] = ((this.fConst428 * (((this.fConst429 * this.fRec109[1]) + (this.fConst438 * this.fRec109[0])) + (this.fConst438 * this.fRec109[2]))) - (this.fConst426 * ((this.fConst439 * this.fRec108[2]) + (this.fConst440 * this.fRec108[1]))));
			var fTemp140 = (this.fConst426 * (((this.fConst427 * this.fRec108[1]) + (this.fConst441 * this.fRec108[0])) + (this.fConst441 * this.fRec108[2])));
			this.fRec107[0] = (fTemp140 - (this.fConst423 * ((this.fConst442 * this.fRec107[2]) + (this.fConst444 * this.fRec107[1]))));
			this.fRec106[0] = ((this.fConst423 * (((this.fConst425 * this.fRec107[1]) + (this.fConst445 * this.fRec107[0])) + (this.fConst445 * this.fRec107[2]))) - (this.fConst420 * ((this.fConst446 * this.fRec106[2]) + (this.fConst447 * this.fRec106[1]))));
			this.fRec105[0] = ((this.fConst420 * (((this.fConst422 * this.fRec106[1]) + (this.fConst448 * this.fRec106[0])) + (this.fConst448 * this.fRec106[2]))) - (this.fConst416 * ((this.fConst449 * this.fRec105[2]) + (this.fConst450 * this.fRec105[1]))));
			this.fRec104[0] = ((fSlow1 * this.fRec104[1]) + (fSlow2 * Math.abs((this.fConst416 * (((this.fConst419 * this.fRec105[1]) + (this.fConst451 * this.fRec105[0])) + (this.fConst451 * this.fRec105[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec104[0]))));
			this.fRec117[0] = (fTemp140 - (this.fConst468 * ((this.fConst471 * this.fRec117[2]) + (this.fConst472 * this.fRec117[1]))));
			this.fRec116[0] = ((this.fConst468 * (((this.fConst470 * this.fRec117[1]) + (this.fConst473 * this.fRec117[0])) + (this.fConst473 * this.fRec117[2]))) - (this.fConst466 * ((this.fConst474 * this.fRec116[2]) + (this.fConst475 * this.fRec116[1]))));
			this.fRec115[0] = ((this.fConst466 * (((this.fConst467 * this.fRec116[1]) + (this.fConst476 * this.fRec116[0])) + (this.fConst476 * this.fRec116[2]))) - (this.fConst464 * ((this.fConst477 * this.fRec115[2]) + (this.fConst478 * this.fRec115[1]))));
			var fTemp141 = (this.fConst464 * (((this.fConst465 * this.fRec115[1]) + (this.fConst479 * this.fRec115[0])) + (this.fConst479 * this.fRec115[2])));
			this.fRec114[0] = (fTemp141 - (this.fConst461 * ((this.fConst480 * this.fRec114[2]) + (this.fConst482 * this.fRec114[1]))));
			this.fRec113[0] = ((this.fConst461 * (((this.fConst463 * this.fRec114[1]) + (this.fConst483 * this.fRec114[0])) + (this.fConst483 * this.fRec114[2]))) - (this.fConst458 * ((this.fConst484 * this.fRec113[2]) + (this.fConst485 * this.fRec113[1]))));
			this.fRec112[0] = ((this.fConst458 * (((this.fConst460 * this.fRec113[1]) + (this.fConst486 * this.fRec113[0])) + (this.fConst486 * this.fRec113[2]))) - (this.fConst454 * ((this.fConst487 * this.fRec112[2]) + (this.fConst488 * this.fRec112[1]))));
			this.fRec111[0] = ((fSlow1 * this.fRec111[1]) + (fSlow2 * Math.abs((this.fConst454 * (((this.fConst457 * this.fRec112[1]) + (this.fConst489 * this.fRec112[0])) + (this.fConst489 * this.fRec112[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec111[0]))));
			this.fRec124[0] = (fTemp141 - (this.fConst506 * ((this.fConst509 * this.fRec124[2]) + (this.fConst510 * this.fRec124[1]))));
			this.fRec123[0] = ((this.fConst506 * (((this.fConst508 * this.fRec124[1]) + (this.fConst511 * this.fRec124[0])) + (this.fConst511 * this.fRec124[2]))) - (this.fConst504 * ((this.fConst512 * this.fRec123[2]) + (this.fConst513 * this.fRec123[1]))));
			this.fRec122[0] = ((this.fConst504 * (((this.fConst505 * this.fRec123[1]) + (this.fConst514 * this.fRec123[0])) + (this.fConst514 * this.fRec123[2]))) - (this.fConst502 * ((this.fConst515 * this.fRec122[2]) + (this.fConst516 * this.fRec122[1]))));
			var fTemp142 = (this.fConst502 * (((this.fConst503 * this.fRec122[1]) + (this.fConst517 * this.fRec122[0])) + (this.fConst517 * this.fRec122[2])));
			this.fRec121[0] = (fTemp142 - (this.fConst499 * ((this.fConst518 * this.fRec121[2]) + (this.fConst520 * this.fRec121[1]))));
			this.fRec120[0] = ((this.fConst499 * (((this.fConst501 * this.fRec121[1]) + (this.fConst521 * this.fRec121[0])) + (this.fConst521 * this.fRec121[2]))) - (this.fConst496 * ((this.fConst522 * this.fRec120[2]) + (this.fConst523 * this.fRec120[1]))));
			this.fRec119[0] = ((this.fConst496 * (((this.fConst498 * this.fRec120[1]) + (this.fConst524 * this.fRec120[0])) + (this.fConst524 * this.fRec120[2]))) - (this.fConst492 * ((this.fConst525 * this.fRec119[2]) + (this.fConst526 * this.fRec119[1]))));
			this.fRec118[0] = ((fSlow1 * this.fRec118[1]) + (fSlow2 * Math.abs((this.fConst492 * (((this.fConst495 * this.fRec119[1]) + (this.fConst527 * this.fRec119[0])) + (this.fConst527 * this.fRec119[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec118[0]))));
			this.fRec128[0] = (fTemp142 - (this.fConst532 * ((this.fConst535 * this.fRec128[2]) + (this.fConst536 * this.fRec128[1]))));
			this.fRec127[0] = ((this.fConst532 * (((this.fConst534 * this.fRec128[1]) + (this.fConst537 * this.fRec128[0])) + (this.fConst537 * this.fRec128[2]))) - (this.fConst530 * ((this.fConst538 * this.fRec127[2]) + (this.fConst539 * this.fRec127[1]))));
			this.fRec126[0] = ((this.fConst530 * (((this.fConst531 * this.fRec127[1]) + (this.fConst540 * this.fRec127[0])) + (this.fConst540 * this.fRec127[2]))) - (this.fConst528 * ((this.fConst541 * this.fRec126[2]) + (this.fConst542 * this.fRec126[1]))));
			this.fRec125[0] = ((fSlow1 * this.fRec125[1]) + (fSlow2 * Math.abs((this.fConst528 * (((this.fConst529 * this.fRec126[1]) + (this.fConst543 * this.fRec126[0])) + (this.fConst543 * this.fRec126[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec125[0]))));
			output0[i] = fTemp129;
			output1[i] = fTemp129;
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec4[1] = this.fRec4[0];
			this.fRec10[1] = this.fRec10[0];
			this.fRec12[1] = this.fRec12[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec11[1] = this.fRec11[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec13[1] = this.fRec13[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec14[1] = this.fRec14[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.fVec22[1] = this.fVec22[0];
			this.fRec15[1] = this.fRec15[0];
			this.fVec23[1] = this.fVec23[0];
			this.IOTA = (this.IOTA + 1);
			this.fVec25[1] = this.fVec25[0];
			this.fRec16[1] = this.fRec16[0];
			this.fVec26[1] = this.fVec26[0];
			this.fVec28[1] = this.fVec28[0];
			this.fRec17[1] = this.fRec17[0];
			this.fVec29[1] = this.fVec29[0];
			this.fRec18[1] = this.fRec18[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec21[1] = this.fRec21[0];
			this.fVec31[1] = this.fVec31[0];
			this.fVec32[1] = this.fVec32[0];
			this.fVec34[1] = this.fVec34[0];
			this.fVec35[1] = this.fVec35[0];
			this.fVec37[1] = this.fVec37[0];
			this.fVec38[1] = this.fVec38[0];
			this.iRec23[1] = this.iRec23[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec22[j1] = this.fRec22[(j1 - 1)];
				
			}
			this.fRec24[1] = this.fRec24[0];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec6[1] = this.fRec6[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec25[2] = this.fRec25[1];
			this.fRec25[1] = this.fRec25[0];
			this.fRec30[1] = this.fRec30[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec33[1] = this.fRec33[0];
			this.fRec31[1] = this.fRec31[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
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
			this.fRec124[2] = this.fRec124[1];
			this.fRec124[1] = this.fRec124[0];
			this.fRec123[2] = this.fRec123[1];
			this.fRec123[1] = this.fRec123[0];
			this.fRec122[2] = this.fRec122[1];
			this.fRec122[1] = this.fRec122[0];
			this.fRec121[2] = this.fRec121[1];
			this.fRec121[1] = this.fRec121[0];
			this.fRec120[2] = this.fRec120[1];
			this.fRec120[1] = this.fRec120[0];
			this.fRec119[2] = this.fRec119[1];
			this.fRec119[1] = this.fRec119[0];
			this.fRec118[1] = this.fRec118[0];
			this.fRec128[2] = this.fRec128[1];
			this.fRec128[1] = this.fRec128[0];
			this.fRec127[2] = this.fRec127[1];
			this.fRec127[1] = this.fRec127[0];
			this.fRec126[2] = this.fRec126[1];
			this.fRec126[1] = this.fRec126[0];
			this.fRec125[1] = this.fRec125[0];
			
		}
		
	}
	
}

