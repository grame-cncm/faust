
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
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
	this.fVslider0;
	this.fRec23 = new Float32Array(2);
	this.fCheckbox1;
	this.fCheckbox2;
	this.fEntry0;
	this.fConst51;
	this.fVslider1;
	this.fVslider2;
	this.fRec25 = new Float32Array(2);
	this.fVec1 = new Float32Array(2);
	this.fRec24 = new Float32Array(2);
	this.fConst52;
	this.fVec2 = new Float32Array(2);
	this.fConst53;
	this.fVec3 = new Float32Array(2);
	this.fVec4 = new Float32Array(2);
	this.fConst54;
	this.fVec5 = new Float32Array(2);
	this.fVec6 = new Float32Array(2);
	this.fVec7 = new Float32Array(2);
	this.fVslider3;
	this.fVec8 = new Float32Array(2);
	this.fRec26 = new Float32Array(2);
	this.fVec9 = new Float32Array(2);
	this.fVec10 = new Float32Array(2);
	this.fVec11 = new Float32Array(2);
	this.fVec12 = new Float32Array(2);
	this.fVec13 = new Float32Array(2);
	this.fVec14 = new Float32Array(2);
	this.fVslider4;
	this.fVec15 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fVec16 = new Float32Array(2);
	this.fVec17 = new Float32Array(2);
	this.fVec18 = new Float32Array(2);
	this.fVec19 = new Float32Array(2);
	this.fVec20 = new Float32Array(2);
	this.fVec21 = new Float32Array(2);
	this.fCheckbox3;
	this.iRec28 = new Int32Array(2);
	this.fRec29 = new Float32Array(4);
	this.fVec22 = new Float32Array(2);
	this.fRec22 = new Float32Array(2);
	this.fConst55;
	this.fConst56;
	this.fConst57;
	this.fRec21 = new Float32Array(3);
	this.fConst58;
	this.fConst59;
	this.fRec20 = new Float32Array(3);
	this.fVec23 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fRec18 = new Float32Array(3);
	this.fConst63;
	this.fConst64;
	this.fRec17 = new Float32Array(3);
	this.fVec24 = new Float32Array(2);
	this.fRec16 = new Float32Array(2);
	this.fConst65;
	this.fConst66;
	this.fConst67;
	this.fRec15 = new Float32Array(3);
	this.fConst68;
	this.fConst69;
	this.fRec14 = new Float32Array(3);
	this.fVec25 = new Float32Array(2);
	this.fRec13 = new Float32Array(2);
	this.fConst70;
	this.fConst71;
	this.fConst72;
	this.fRec12 = new Float32Array(3);
	this.fConst73;
	this.fConst74;
	this.fRec11 = new Float32Array(3);
	this.fVec26 = new Float32Array(2);
	this.fConst75;
	this.fConst76;
	this.fRec10 = new Float32Array(2);
	this.fConst77;
	this.fConst78;
	this.fRec9 = new Float32Array(3);
	this.fConst79;
	this.fRec8 = new Float32Array(3);
	this.fConst80;
	this.fConst81;
	this.fConst82;
	this.fConst83;
	this.fConst84;
	this.fConst85;
	this.fRec7 = new Float32Array(3);
	this.fConst86;
	this.fConst87;
	this.fConst88;
	this.fConst89;
	this.fConst90;
	this.fConst91;
	this.fRec6 = new Float32Array(3);
	this.fConst92;
	this.fConst93;
	this.fConst94;
	this.fConst95;
	this.fConst96;
	this.fConst97;
	this.fRec5 = new Float32Array(3);
	this.fConst98;
	this.fConst99;
	this.fConst100;
	this.fConst101;
	this.fConst102;
	this.fConst103;
	this.fRec4 = new Float32Array(3);
	this.fVslider5;
	this.fRec30 = new Float32Array(2);
	this.fConst104;
	this.fConst105;
	this.fConst106;
	this.fConst107;
	this.fConst108;
	this.fConst109;
	this.fConst110;
	this.fRec39 = new Float32Array(2);
	this.fRec38 = new Float32Array(3);
	this.fRec37 = new Float32Array(3);
	this.fVec27 = new Float32Array(2);
	this.fConst111;
	this.fRec36 = new Float32Array(2);
	this.fConst112;
	this.fRec35 = new Float32Array(3);
	this.fConst113;
	this.fRec34 = new Float32Array(3);
	this.fRec33 = new Float32Array(3);
	this.fRec32 = new Float32Array(3);
	this.fRec31 = new Float32Array(3);
	this.fVslider6;
	this.fRec40 = new Float32Array(2);
	this.fConst114;
	this.fConst115;
	this.fConst116;
	this.fConst117;
	this.fConst118;
	this.fConst119;
	this.fConst120;
	this.fRec48 = new Float32Array(2);
	this.fRec47 = new Float32Array(3);
	this.fRec46 = new Float32Array(3);
	this.fVec28 = new Float32Array(2);
	this.fConst121;
	this.fRec45 = new Float32Array(2);
	this.fConst122;
	this.fRec44 = new Float32Array(3);
	this.fConst123;
	this.fRec43 = new Float32Array(3);
	this.fRec42 = new Float32Array(3);
	this.fRec41 = new Float32Array(3);
	this.fVslider7;
	this.fRec49 = new Float32Array(2);
	this.fConst124;
	this.fConst125;
	this.fConst126;
	this.fConst127;
	this.fConst128;
	this.fConst129;
	this.fConst130;
	this.fRec56 = new Float32Array(2);
	this.fRec55 = new Float32Array(3);
	this.fRec54 = new Float32Array(3);
	this.fVec29 = new Float32Array(2);
	this.fConst131;
	this.fRec53 = new Float32Array(2);
	this.fConst132;
	this.fRec52 = new Float32Array(3);
	this.fConst133;
	this.fRec51 = new Float32Array(3);
	this.fRec50 = new Float32Array(3);
	this.fVslider8;
	this.fRec57 = new Float32Array(2);
	this.fConst134;
	this.fConst135;
	this.fConst136;
	this.fConst137;
	this.fConst138;
	this.fConst139;
	this.fRec63 = new Float32Array(2);
	this.fRec62 = new Float32Array(3);
	this.fRec61 = new Float32Array(3);
	this.fVec30 = new Float32Array(2);
	this.fConst140;
	this.fRec60 = new Float32Array(2);
	this.fConst141;
	this.fRec59 = new Float32Array(3);
	this.fConst142;
	this.fRec58 = new Float32Array(3);
	this.fVslider9;
	this.fRec64 = new Float32Array(2);
	this.fRec67 = new Float32Array(2);
	this.fRec66 = new Float32Array(3);
	this.fRec65 = new Float32Array(3);
	this.fVslider10;
	this.fRec68 = new Float32Array(2);
	this.fConst143;
	this.fConst144;
	this.fRec79 = new Float32Array(2);
	this.fRec78 = new Float32Array(3);
	this.fRec77 = new Float32Array(3);
	this.fRec76 = new Float32Array(3);
	this.fRec75 = new Float32Array(3);
	this.fRec74 = new Float32Array(3);
	this.fRec73 = new Float32Array(3);
	this.fConst145;
	this.fConst146;
	this.fRec72 = new Float32Array(3);
	this.fConst147;
	this.fConst148;
	this.fRec71 = new Float32Array(3);
	this.fConst149;
	this.fConst150;
	this.fRec70 = new Float32Array(3);
	this.fConst151;
	this.fConst152;
	this.fRec69 = new Float32Array(3);
	this.fVslider11;
	this.fRec80 = new Float32Array(2);
	this.fConst153;
	this.fConst154;
	this.fRec90 = new Float32Array(2);
	this.fRec89 = new Float32Array(3);
	this.fRec88 = new Float32Array(3);
	this.fRec87 = new Float32Array(3);
	this.fRec86 = new Float32Array(3);
	this.fRec85 = new Float32Array(3);
	this.fRec84 = new Float32Array(3);
	this.fRec83 = new Float32Array(3);
	this.fRec82 = new Float32Array(3);
	this.fRec81 = new Float32Array(3);
	this.fVslider12;
	this.fRec91 = new Float32Array(2);
	this.fConst155;
	this.fConst156;
	this.fRec100 = new Float32Array(2);
	this.fRec99 = new Float32Array(3);
	this.fRec98 = new Float32Array(3);
	this.fRec97 = new Float32Array(3);
	this.fRec96 = new Float32Array(3);
	this.fRec95 = new Float32Array(3);
	this.fRec94 = new Float32Array(3);
	this.fRec93 = new Float32Array(3);
	this.fRec92 = new Float32Array(3);
	this.fVslider13;
	this.fRec101 = new Float32Array(2);
	this.fConst157;
	this.fConst158;
	this.fRec109 = new Float32Array(2);
	this.fRec108 = new Float32Array(3);
	this.fRec107 = new Float32Array(3);
	this.fRec106 = new Float32Array(3);
	this.fRec105 = new Float32Array(3);
	this.fRec104 = new Float32Array(3);
	this.fRec103 = new Float32Array(3);
	this.fRec102 = new Float32Array(3);
	this.fVslider14;
	this.fRec110 = new Float32Array(2);
	this.fConst159;
	this.fConst160;
	this.fConst161;
	this.fRec3 = new Float32Array(3);
	this.fConst162;
	this.fConst163;
	this.fConst164;
	this.fRec2 = new Float32Array(3);
	this.fConst165;
	this.fConst166;
	this.fConst167;
	this.fRec1 = new Float32Array(3);
	this.fConst168;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
	this.fConst169;
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
	this.fConst181;
	this.fConst182;
	this.fConst183;
	this.fConst184;
	this.fConst185;
	this.fConst186;
	this.fConst187;
	this.fConst188;
	this.fConst189;
	this.fRec117 = new Float32Array(3);
	this.fConst190;
	this.fConst191;
	this.fConst192;
	this.fRec116 = new Float32Array(3);
	this.fConst193;
	this.fConst194;
	this.fConst195;
	this.fRec115 = new Float32Array(3);
	this.fConst196;
	this.fConst197;
	this.fConst198;
	this.fConst199;
	this.fRec114 = new Float32Array(3);
	this.fConst200;
	this.fConst201;
	this.fConst202;
	this.fRec113 = new Float32Array(3);
	this.fConst203;
	this.fConst204;
	this.fConst205;
	this.fRec112 = new Float32Array(3);
	this.fConst206;
	this.fRec111 = new Float32Array(2);
	this.fVbargraph1;
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
	this.fConst217;
	this.fConst218;
	this.fConst219;
	this.fConst220;
	this.fConst221;
	this.fConst222;
	this.fConst223;
	this.fConst224;
	this.fConst225;
	this.fConst226;
	this.fConst227;
	this.fRec124 = new Float32Array(3);
	this.fConst228;
	this.fConst229;
	this.fConst230;
	this.fRec123 = new Float32Array(3);
	this.fConst231;
	this.fConst232;
	this.fConst233;
	this.fRec122 = new Float32Array(3);
	this.fConst234;
	this.fConst235;
	this.fConst236;
	this.fConst237;
	this.fRec121 = new Float32Array(3);
	this.fConst238;
	this.fConst239;
	this.fConst240;
	this.fRec120 = new Float32Array(3);
	this.fConst241;
	this.fConst242;
	this.fConst243;
	this.fRec119 = new Float32Array(3);
	this.fConst244;
	this.fRec118 = new Float32Array(2);
	this.fVbargraph2;
	this.fConst245;
	this.fConst246;
	this.fConst247;
	this.fConst248;
	this.fConst249;
	this.fConst250;
	this.fConst251;
	this.fConst252;
	this.fConst253;
	this.fConst254;
	this.fConst255;
	this.fConst256;
	this.fConst257;
	this.fConst258;
	this.fConst259;
	this.fConst260;
	this.fConst261;
	this.fConst262;
	this.fConst263;
	this.fConst264;
	this.fConst265;
	this.fRec131 = new Float32Array(3);
	this.fConst266;
	this.fConst267;
	this.fConst268;
	this.fRec130 = new Float32Array(3);
	this.fConst269;
	this.fConst270;
	this.fConst271;
	this.fRec129 = new Float32Array(3);
	this.fConst272;
	this.fConst273;
	this.fConst274;
	this.fConst275;
	this.fRec128 = new Float32Array(3);
	this.fConst276;
	this.fConst277;
	this.fConst278;
	this.fRec127 = new Float32Array(3);
	this.fConst279;
	this.fConst280;
	this.fConst281;
	this.fRec126 = new Float32Array(3);
	this.fConst282;
	this.fRec125 = new Float32Array(2);
	this.fVbargraph3;
	this.fConst283;
	this.fConst284;
	this.fConst285;
	this.fConst286;
	this.fConst287;
	this.fConst288;
	this.fConst289;
	this.fConst290;
	this.fConst291;
	this.fConst292;
	this.fConst293;
	this.fConst294;
	this.fConst295;
	this.fConst296;
	this.fConst297;
	this.fConst298;
	this.fConst299;
	this.fConst300;
	this.fConst301;
	this.fConst302;
	this.fConst303;
	this.fRec138 = new Float32Array(3);
	this.fConst304;
	this.fConst305;
	this.fConst306;
	this.fRec137 = new Float32Array(3);
	this.fConst307;
	this.fConst308;
	this.fConst309;
	this.fRec136 = new Float32Array(3);
	this.fConst310;
	this.fConst311;
	this.fConst312;
	this.fConst313;
	this.fRec135 = new Float32Array(3);
	this.fConst314;
	this.fConst315;
	this.fConst316;
	this.fRec134 = new Float32Array(3);
	this.fConst317;
	this.fConst318;
	this.fConst319;
	this.fRec133 = new Float32Array(3);
	this.fConst320;
	this.fRec132 = new Float32Array(2);
	this.fVbargraph4;
	this.fConst321;
	this.fConst322;
	this.fConst323;
	this.fConst324;
	this.fConst325;
	this.fConst326;
	this.fConst327;
	this.fConst328;
	this.fConst329;
	this.fConst330;
	this.fConst331;
	this.fConst332;
	this.fConst333;
	this.fConst334;
	this.fConst335;
	this.fConst336;
	this.fConst337;
	this.fConst338;
	this.fConst339;
	this.fConst340;
	this.fConst341;
	this.fRec145 = new Float32Array(3);
	this.fConst342;
	this.fConst343;
	this.fConst344;
	this.fRec144 = new Float32Array(3);
	this.fConst345;
	this.fConst346;
	this.fConst347;
	this.fRec143 = new Float32Array(3);
	this.fConst348;
	this.fConst349;
	this.fConst350;
	this.fConst351;
	this.fRec142 = new Float32Array(3);
	this.fConst352;
	this.fConst353;
	this.fConst354;
	this.fRec141 = new Float32Array(3);
	this.fConst355;
	this.fConst356;
	this.fConst357;
	this.fRec140 = new Float32Array(3);
	this.fConst358;
	this.fRec139 = new Float32Array(2);
	this.fVbargraph5;
	this.fConst359;
	this.fConst360;
	this.fConst361;
	this.fConst362;
	this.fConst363;
	this.fConst364;
	this.fConst365;
	this.fConst366;
	this.fConst367;
	this.fConst368;
	this.fConst369;
	this.fConst370;
	this.fConst371;
	this.fConst372;
	this.fConst373;
	this.fConst374;
	this.fConst375;
	this.fConst376;
	this.fConst377;
	this.fConst378;
	this.fConst379;
	this.fRec152 = new Float32Array(3);
	this.fConst380;
	this.fConst381;
	this.fConst382;
	this.fRec151 = new Float32Array(3);
	this.fConst383;
	this.fConst384;
	this.fConst385;
	this.fRec150 = new Float32Array(3);
	this.fConst386;
	this.fConst387;
	this.fConst388;
	this.fConst389;
	this.fRec149 = new Float32Array(3);
	this.fConst390;
	this.fConst391;
	this.fConst392;
	this.fRec148 = new Float32Array(3);
	this.fConst393;
	this.fConst394;
	this.fConst395;
	this.fRec147 = new Float32Array(3);
	this.fConst396;
	this.fRec146 = new Float32Array(2);
	this.fVbargraph6;
	this.fConst397;
	this.fConst398;
	this.fConst399;
	this.fConst400;
	this.fConst401;
	this.fConst402;
	this.fConst403;
	this.fConst404;
	this.fConst405;
	this.fConst406;
	this.fConst407;
	this.fConst408;
	this.fConst409;
	this.fConst410;
	this.fConst411;
	this.fConst412;
	this.fConst413;
	this.fConst414;
	this.fConst415;
	this.fConst416;
	this.fConst417;
	this.fRec159 = new Float32Array(3);
	this.fConst418;
	this.fConst419;
	this.fConst420;
	this.fRec158 = new Float32Array(3);
	this.fConst421;
	this.fConst422;
	this.fConst423;
	this.fRec157 = new Float32Array(3);
	this.fConst424;
	this.fConst425;
	this.fConst426;
	this.fConst427;
	this.fRec156 = new Float32Array(3);
	this.fConst428;
	this.fConst429;
	this.fConst430;
	this.fRec155 = new Float32Array(3);
	this.fConst431;
	this.fConst432;
	this.fConst433;
	this.fRec154 = new Float32Array(3);
	this.fConst434;
	this.fRec153 = new Float32Array(2);
	this.fVbargraph7;
	this.fConst435;
	this.fConst436;
	this.fConst437;
	this.fConst438;
	this.fConst439;
	this.fConst440;
	this.fConst441;
	this.fConst442;
	this.fConst443;
	this.fConst444;
	this.fConst445;
	this.fConst446;
	this.fConst447;
	this.fConst448;
	this.fConst449;
	this.fConst450;
	this.fConst451;
	this.fConst452;
	this.fConst453;
	this.fConst454;
	this.fConst455;
	this.fRec166 = new Float32Array(3);
	this.fConst456;
	this.fConst457;
	this.fConst458;
	this.fRec165 = new Float32Array(3);
	this.fConst459;
	this.fConst460;
	this.fConst461;
	this.fRec164 = new Float32Array(3);
	this.fConst462;
	this.fConst463;
	this.fConst464;
	this.fConst465;
	this.fRec163 = new Float32Array(3);
	this.fConst466;
	this.fConst467;
	this.fConst468;
	this.fRec162 = new Float32Array(3);
	this.fConst469;
	this.fConst470;
	this.fConst471;
	this.fRec161 = new Float32Array(3);
	this.fConst472;
	this.fRec160 = new Float32Array(2);
	this.fVbargraph8;
	this.fConst473;
	this.fConst474;
	this.fConst475;
	this.fConst476;
	this.fConst477;
	this.fConst478;
	this.fConst479;
	this.fConst480;
	this.fConst481;
	this.fConst482;
	this.fConst483;
	this.fConst484;
	this.fConst485;
	this.fConst486;
	this.fConst487;
	this.fConst488;
	this.fConst489;
	this.fConst490;
	this.fConst491;
	this.fConst492;
	this.fConst493;
	this.fRec173 = new Float32Array(3);
	this.fConst494;
	this.fConst495;
	this.fConst496;
	this.fRec172 = new Float32Array(3);
	this.fConst497;
	this.fConst498;
	this.fConst499;
	this.fRec171 = new Float32Array(3);
	this.fConst500;
	this.fConst501;
	this.fConst502;
	this.fConst503;
	this.fRec170 = new Float32Array(3);
	this.fConst504;
	this.fConst505;
	this.fConst506;
	this.fRec169 = new Float32Array(3);
	this.fConst507;
	this.fConst508;
	this.fConst509;
	this.fRec168 = new Float32Array(3);
	this.fConst510;
	this.fRec167 = new Float32Array(2);
	this.fVbargraph9;
	this.fConst511;
	this.fConst512;
	this.fConst513;
	this.fConst514;
	this.fConst515;
	this.fConst516;
	this.fConst517;
	this.fConst518;
	this.fConst519;
	this.fConst520;
	this.fConst521;
	this.fConst522;
	this.fConst523;
	this.fConst524;
	this.fConst525;
	this.fConst526;
	this.fConst527;
	this.fConst528;
	this.fConst529;
	this.fConst530;
	this.fConst531;
	this.fRec180 = new Float32Array(3);
	this.fConst532;
	this.fConst533;
	this.fConst534;
	this.fRec179 = new Float32Array(3);
	this.fConst535;
	this.fConst536;
	this.fConst537;
	this.fRec178 = new Float32Array(3);
	this.fConst538;
	this.fConst539;
	this.fConst540;
	this.fConst541;
	this.fRec177 = new Float32Array(3);
	this.fConst542;
	this.fConst543;
	this.fConst544;
	this.fRec176 = new Float32Array(3);
	this.fConst545;
	this.fConst546;
	this.fConst547;
	this.fRec175 = new Float32Array(3);
	this.fConst548;
	this.fRec174 = new Float32Array(2);
	this.fVbargraph10;
	this.fConst549;
	this.fConst550;
	this.fConst551;
	this.fConst552;
	this.fConst553;
	this.fConst554;
	this.fConst555;
	this.fConst556;
	this.fConst557;
	this.fConst558;
	this.fConst559;
	this.fConst560;
	this.fConst561;
	this.fConst562;
	this.fConst563;
	this.fConst564;
	this.fConst565;
	this.fConst566;
	this.fConst567;
	this.fConst568;
	this.fConst569;
	this.fRec187 = new Float32Array(3);
	this.fConst570;
	this.fConst571;
	this.fConst572;
	this.fRec186 = new Float32Array(3);
	this.fConst573;
	this.fConst574;
	this.fConst575;
	this.fRec185 = new Float32Array(3);
	this.fConst576;
	this.fConst577;
	this.fConst578;
	this.fConst579;
	this.fRec184 = new Float32Array(3);
	this.fConst580;
	this.fConst581;
	this.fConst582;
	this.fRec183 = new Float32Array(3);
	this.fConst583;
	this.fConst584;
	this.fConst585;
	this.fRec182 = new Float32Array(3);
	this.fConst586;
	this.fRec181 = new Float32Array(2);
	this.fVbargraph11;
	this.fConst587;
	this.fConst588;
	this.fConst589;
	this.fConst590;
	this.fConst591;
	this.fConst592;
	this.fConst593;
	this.fConst594;
	this.fConst595;
	this.fConst596;
	this.fConst597;
	this.fConst598;
	this.fConst599;
	this.fConst600;
	this.fConst601;
	this.fConst602;
	this.fConst603;
	this.fConst604;
	this.fConst605;
	this.fConst606;
	this.fConst607;
	this.fRec194 = new Float32Array(3);
	this.fConst608;
	this.fConst609;
	this.fConst610;
	this.fRec193 = new Float32Array(3);
	this.fConst611;
	this.fConst612;
	this.fConst613;
	this.fRec192 = new Float32Array(3);
	this.fConst614;
	this.fConst615;
	this.fConst616;
	this.fConst617;
	this.fRec191 = new Float32Array(3);
	this.fConst618;
	this.fConst619;
	this.fConst620;
	this.fRec190 = new Float32Array(3);
	this.fConst621;
	this.fConst622;
	this.fConst623;
	this.fRec189 = new Float32Array(3);
	this.fConst624;
	this.fRec188 = new Float32Array(2);
	this.fVbargraph12;
	this.fConst625;
	this.fConst626;
	this.fConst627;
	this.fConst628;
	this.fConst629;
	this.fConst630;
	this.fConst631;
	this.fConst632;
	this.fConst633;
	this.fConst634;
	this.fConst635;
	this.fConst636;
	this.fConst637;
	this.fConst638;
	this.fConst639;
	this.fConst640;
	this.fConst641;
	this.fConst642;
	this.fConst643;
	this.fConst644;
	this.fConst645;
	this.fRec201 = new Float32Array(3);
	this.fConst646;
	this.fConst647;
	this.fConst648;
	this.fRec200 = new Float32Array(3);
	this.fConst649;
	this.fConst650;
	this.fConst651;
	this.fRec199 = new Float32Array(3);
	this.fConst652;
	this.fConst653;
	this.fConst654;
	this.fConst655;
	this.fRec198 = new Float32Array(3);
	this.fConst656;
	this.fConst657;
	this.fConst658;
	this.fRec197 = new Float32Array(3);
	this.fConst659;
	this.fConst660;
	this.fConst661;
	this.fRec196 = new Float32Array(3);
	this.fConst662;
	this.fRec195 = new Float32Array(2);
	this.fVbargraph13;
	this.fConst663;
	this.fConst664;
	this.fConst665;
	this.fConst666;
	this.fConst667;
	this.fConst668;
	this.fConst669;
	this.fConst670;
	this.fConst671;
	this.fRec205 = new Float32Array(3);
	this.fConst672;
	this.fConst673;
	this.fConst674;
	this.fRec204 = new Float32Array(3);
	this.fConst675;
	this.fConst676;
	this.fConst677;
	this.fRec203 = new Float32Array(3);
	this.fConst678;
	this.fRec202 = new Float32Array(2);
	this.fVbargraph14;
	
	this.metadata = function(m) { 
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
		this.fConst14 = Math.tan((1963.5 / this.fConst0));
		this.fConst15 = (1 / this.fConst14);
		this.fConst16 = (((this.fConst15 + 0.618034) / this.fConst14) + 1);
		this.fConst17 = (1 / this.fConst16);
		this.fConst18 = (1 / mydsp_faustpower2_f(this.fConst14));
		this.fConst19 = (2 * (0 - this.fConst18));
		this.fConst20 = (1 / (((this.fConst15 + 1.61803) / this.fConst14) + 1));
		this.fConst21 = Math.tan((3926.99 / this.fConst0));
		this.fConst22 = (1 / this.fConst21);
		this.fConst23 = (((this.fConst22 + 0.618034) / this.fConst21) + 1);
		this.fConst24 = (this.fConst15 + 1);
		this.fConst25 = (1 / (this.fConst23 * this.fConst24));
		this.fConst26 = (1 / (((this.fConst22 + 1.61803) / this.fConst21) + 1));
		this.fConst27 = (this.fConst22 + 1);
		this.fConst28 = (0 - ((1 - this.fConst22) / this.fConst27));
		this.fConst29 = Math.tan((7853.98 / this.fConst0));
		this.fConst30 = (1 / this.fConst29);
		this.fConst31 = (((this.fConst30 + 0.618034) / this.fConst29) + 1);
		this.fConst32 = (1 / (this.fConst31 * this.fConst27));
		this.fConst33 = (1 / (((this.fConst30 + 1.61803) / this.fConst29) + 1));
		this.fConst34 = (this.fConst30 + 1);
		this.fConst35 = (0 - ((1 - this.fConst30) / this.fConst34));
		this.fConst36 = Math.tan((15708 / this.fConst0));
		this.fConst37 = (1 / this.fConst36);
		this.fConst38 = (((this.fConst37 + 0.618034) / this.fConst36) + 1);
		this.fConst39 = (1 / (this.fConst38 * this.fConst34));
		this.fConst40 = (1 / (((this.fConst37 + 1.61803) / this.fConst36) + 1));
		this.fConst41 = (this.fConst37 + 1);
		this.fConst42 = (0 - ((1 - this.fConst37) / this.fConst41));
		this.fConst43 = Math.tan((31415.9 / this.fConst0));
		this.fConst44 = (1 / this.fConst43);
		this.fConst45 = (((this.fConst44 + 0.618034) / this.fConst43) + 1);
		this.fConst46 = (1 / (this.fConst45 * this.fConst41));
		this.fConst47 = (1 / (((this.fConst44 + 1.61803) / this.fConst43) + 1));
		this.fConst48 = (this.fConst44 + 1);
		this.fConst49 = (0 - ((1 - this.fConst44) / this.fConst48));
		this.fConst50 = (1 / this.fConst48);
		this.fConst51 = (1 / this.fConst0);
		this.fConst52 = (0.25 * this.fConst0);
		this.fConst53 = (0.0416667 * mydsp_faustpower2_f(this.fConst0));
		this.fConst54 = (0.00520833 * mydsp_faustpower3_f(this.fConst0));
		this.fConst55 = (1 / mydsp_faustpower2_f(this.fConst43));
		this.fConst56 = (2 * (1 - this.fConst55));
		this.fConst57 = (((this.fConst44 + -1.61803) / this.fConst43) + 1);
		this.fConst58 = (1 / this.fConst45);
		this.fConst59 = (((this.fConst44 + -0.618034) / this.fConst43) + 1);
		this.fConst60 = (1 / mydsp_faustpower2_f(this.fConst36));
		this.fConst61 = (2 * (1 - this.fConst60));
		this.fConst62 = (((this.fConst37 + -1.61803) / this.fConst36) + 1);
		this.fConst63 = (1 / this.fConst38);
		this.fConst64 = (((this.fConst37 + -0.618034) / this.fConst36) + 1);
		this.fConst65 = (1 / mydsp_faustpower2_f(this.fConst29));
		this.fConst66 = (2 * (1 - this.fConst65));
		this.fConst67 = (((this.fConst30 + -1.61803) / this.fConst29) + 1);
		this.fConst68 = (1 / this.fConst31);
		this.fConst69 = (((this.fConst30 + -0.618034) / this.fConst29) + 1);
		this.fConst70 = (1 / mydsp_faustpower2_f(this.fConst21));
		this.fConst71 = (2 * (1 - this.fConst70));
		this.fConst72 = (((this.fConst22 + -1.61803) / this.fConst21) + 1);
		this.fConst73 = (1 / this.fConst23);
		this.fConst74 = (((this.fConst22 + -0.618034) / this.fConst21) + 1);
		this.fConst75 = (0 - this.fConst15);
		this.fConst76 = (0 - ((1 - this.fConst15) / this.fConst24));
		this.fConst77 = (2 * (1 - this.fConst18));
		this.fConst78 = (((this.fConst15 + -1.61803) / this.fConst14) + 1);
		this.fConst79 = (((this.fConst15 + -0.618034) / this.fConst14) + 1);
		this.fConst80 = Math.tan((122.718 / this.fConst0));
		this.fConst81 = (1 / this.fConst80);
		this.fConst82 = (1 / (((this.fConst81 + 1.61803) / this.fConst80) + 1));
		this.fConst83 = (1 / mydsp_faustpower2_f(this.fConst80));
		this.fConst84 = (2 * (1 - this.fConst83));
		this.fConst85 = (((this.fConst81 + -1.61803) / this.fConst80) + 1);
		this.fConst86 = Math.tan((245.437 / this.fConst0));
		this.fConst87 = (1 / this.fConst86);
		this.fConst88 = (1 / (((this.fConst87 + 1.61803) / this.fConst86) + 1));
		this.fConst89 = (1 / mydsp_faustpower2_f(this.fConst86));
		this.fConst90 = (2 * (1 - this.fConst89));
		this.fConst91 = (((this.fConst87 + -1.61803) / this.fConst86) + 1);
		this.fConst92 = Math.tan((490.874 / this.fConst0));
		this.fConst93 = (1 / this.fConst92);
		this.fConst94 = (1 / (((this.fConst93 + 1.61803) / this.fConst92) + 1));
		this.fConst95 = (1 / mydsp_faustpower2_f(this.fConst92));
		this.fConst96 = (2 * (1 - this.fConst95));
		this.fConst97 = (((this.fConst93 + -1.61803) / this.fConst92) + 1);
		this.fConst98 = Math.tan((981.748 / this.fConst0));
		this.fConst99 = (1 / this.fConst98);
		this.fConst100 = (1 / (((this.fConst99 + 1.61803) / this.fConst98) + 1));
		this.fConst101 = (1 / mydsp_faustpower2_f(this.fConst98));
		this.fConst102 = (2 * (1 - this.fConst101));
		this.fConst103 = (((this.fConst99 + -1.61803) / this.fConst98) + 1);
		this.fConst104 = (((this.fConst99 + 0.618034) / this.fConst98) + 1);
		this.fConst105 = (1 / this.fConst104);
		this.fConst106 = (2 * (0 - this.fConst101));
		this.fConst107 = (1 / (((this.fConst99 + 1.61803) / this.fConst98) + 1));
		this.fConst108 = (this.fConst99 + 1);
		this.fConst109 = (0 - ((1 - this.fConst99) / this.fConst108));
		this.fConst110 = (1 / (this.fConst16 * this.fConst108));
		this.fConst111 = (0 - this.fConst99);
		this.fConst112 = (((this.fConst99 + -1.61803) / this.fConst98) + 1);
		this.fConst113 = (((this.fConst99 + -0.618034) / this.fConst98) + 1);
		this.fConst114 = (((this.fConst93 + 0.618034) / this.fConst92) + 1);
		this.fConst115 = (1 / this.fConst114);
		this.fConst116 = (2 * (0 - this.fConst95));
		this.fConst117 = (1 / (((this.fConst93 + 1.61803) / this.fConst92) + 1));
		this.fConst118 = (this.fConst93 + 1);
		this.fConst119 = (0 - ((1 - this.fConst93) / this.fConst118));
		this.fConst120 = (1 / (this.fConst104 * this.fConst118));
		this.fConst121 = (0 - this.fConst93);
		this.fConst122 = (((this.fConst93 + -1.61803) / this.fConst92) + 1);
		this.fConst123 = (((this.fConst93 + -0.618034) / this.fConst92) + 1);
		this.fConst124 = (((this.fConst87 + 0.618034) / this.fConst86) + 1);
		this.fConst125 = (1 / this.fConst124);
		this.fConst126 = (2 * (0 - this.fConst89));
		this.fConst127 = (1 / (((this.fConst87 + 1.61803) / this.fConst86) + 1));
		this.fConst128 = (this.fConst87 + 1);
		this.fConst129 = (0 - ((1 - this.fConst87) / this.fConst128));
		this.fConst130 = (1 / (this.fConst114 * this.fConst128));
		this.fConst131 = (0 - this.fConst87);
		this.fConst132 = (((this.fConst87 + -1.61803) / this.fConst86) + 1);
		this.fConst133 = (((this.fConst87 + -0.618034) / this.fConst86) + 1);
		this.fConst134 = (1 / (((this.fConst81 + 0.618034) / this.fConst80) + 1));
		this.fConst135 = (2 * (0 - this.fConst83));
		this.fConst136 = (1 / (((this.fConst81 + 1.61803) / this.fConst80) + 1));
		this.fConst137 = (this.fConst81 + 1);
		this.fConst138 = (0 - ((1 - this.fConst81) / this.fConst137));
		this.fConst139 = (1 / (this.fConst124 * this.fConst137));
		this.fConst140 = (0 - this.fConst81);
		this.fConst141 = (((this.fConst81 + -1.61803) / this.fConst80) + 1);
		this.fConst142 = (((this.fConst81 + -0.618034) / this.fConst80) + 1);
		this.fConst143 = (2 * (0 - this.fConst55));
		this.fConst144 = (0 - this.fConst44);
		this.fConst145 = (1 / (((this.fConst15 + 1.61803) / this.fConst14) + 1));
		this.fConst146 = (((this.fConst15 + -1.61803) / this.fConst14) + 1);
		this.fConst147 = (1 / (((this.fConst22 + 1.61803) / this.fConst21) + 1));
		this.fConst148 = (((this.fConst22 + -1.61803) / this.fConst21) + 1);
		this.fConst149 = (1 / (((this.fConst30 + 1.61803) / this.fConst29) + 1));
		this.fConst150 = (((this.fConst30 + -1.61803) / this.fConst29) + 1);
		this.fConst151 = (1 / (((this.fConst37 + 1.61803) / this.fConst36) + 1));
		this.fConst152 = (((this.fConst37 + -1.61803) / this.fConst36) + 1);
		this.fConst153 = (2 * (0 - this.fConst60));
		this.fConst154 = (0 - this.fConst37);
		this.fConst155 = (2 * (0 - this.fConst65));
		this.fConst156 = (0 - this.fConst30);
		this.fConst157 = (2 * (0 - this.fConst70));
		this.fConst158 = (0 - this.fConst22);
		this.fConst159 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst160 = (1 / this.fConst5);
		this.fConst161 = (2 * (4.07678 - this.fConst160));
		this.fConst162 = (this.fConst12 + 0.000407678);
		this.fConst163 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst164 = (2 * (1.45007 - this.fConst160));
		this.fConst165 = (this.fConst9 + 1.45007);
		this.fConst166 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst167 = (2 * (0.93514 - this.fConst160));
		this.fConst168 = (this.fConst6 + 0.93514);
		this.fConst169 = Math.tan((31665.3 / this.fConst0));
		this.fConst170 = (1 / this.fConst169);
		this.fConst171 = (1 / (((this.fConst170 + 0.157482) / this.fConst169) + 0.93514));
		this.fConst172 = mydsp_faustpower2_f(this.fConst169);
		this.fConst173 = (50.0638 / this.fConst172);
		this.fConst174 = (2 * (0.93514 - this.fConst173));
		this.fConst175 = (1 / (((this.fConst170 + 0.74313) / this.fConst169) + 1.45007));
		this.fConst176 = (11.0521 / this.fConst172);
		this.fConst177 = (2 * (1.45007 - this.fConst176));
		this.fConst178 = (1 / (((this.fConst170 + 3.18973) / this.fConst169) + 4.07678));
		this.fConst179 = (0.00176617 / this.fConst172);
		this.fConst180 = (2 * (0.000407678 - this.fConst179));
		this.fConst181 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst182 = (2 * (53.5362 - this.fConst160));
		this.fConst183 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst184 = (2 * (7.62173 - this.fConst160));
		this.fConst185 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst186 = (0.0001 / this.fConst5);
		this.fConst187 = (2 * (0.000433227 - this.fConst186));
		this.fConst188 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst189 = (2 * (0.245292 - this.fConst160));
		this.fConst190 = (this.fConst186 + 0.000433227);
		this.fConst191 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst192 = (2 * (0.689621 - this.fConst160));
		this.fConst193 = (this.fConst160 + 7.62173);
		this.fConst194 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst195 = (2 * (1.06936 - this.fConst160));
		this.fConst196 = (this.fConst160 + 53.5362);
		this.fConst197 = (((this.fConst170 + -3.18973) / this.fConst169) + 4.07678);
		this.fConst198 = (1 / this.fConst172);
		this.fConst199 = (2 * (4.07678 - this.fConst198));
		this.fConst200 = (this.fConst179 + 0.000407678);
		this.fConst201 = (((this.fConst170 + -0.74313) / this.fConst169) + 1.45007);
		this.fConst202 = (2 * (1.45007 - this.fConst198));
		this.fConst203 = (this.fConst176 + 1.45007);
		this.fConst204 = (((this.fConst170 + -0.157482) / this.fConst169) + 0.93514);
		this.fConst205 = (2 * (0.93514 - this.fConst198));
		this.fConst206 = (this.fConst173 + 0.93514);
		this.fConst207 = Math.tan((19947.9 / this.fConst0));
		this.fConst208 = (1 / this.fConst207);
		this.fConst209 = (1 / (((this.fConst208 + 0.157482) / this.fConst207) + 0.93514));
		this.fConst210 = mydsp_faustpower2_f(this.fConst207);
		this.fConst211 = (50.0638 / this.fConst210);
		this.fConst212 = (2 * (0.93514 - this.fConst211));
		this.fConst213 = (1 / (((this.fConst208 + 0.74313) / this.fConst207) + 1.45007));
		this.fConst214 = (11.0521 / this.fConst210);
		this.fConst215 = (2 * (1.45007 - this.fConst214));
		this.fConst216 = (1 / (((this.fConst208 + 3.18973) / this.fConst207) + 4.07678));
		this.fConst217 = (0.00176617 / this.fConst210);
		this.fConst218 = (2 * (0.000407678 - this.fConst217));
		this.fConst219 = (1 / (((this.fConst170 + 0.168405) / this.fConst169) + 1.06936));
		this.fConst220 = (2 * (53.5362 - this.fConst198));
		this.fConst221 = (1 / (((this.fConst170 + 0.512479) / this.fConst169) + 0.689621));
		this.fConst222 = (2 * (7.62173 - this.fConst198));
		this.fConst223 = (1 / (((this.fConst170 + 0.782413) / this.fConst169) + 0.245292));
		this.fConst224 = (0.0001 / this.fConst172);
		this.fConst225 = (2 * (0.000433227 - this.fConst224));
		this.fConst226 = (((this.fConst170 + -0.782413) / this.fConst169) + 0.245292);
		this.fConst227 = (2 * (0.245292 - this.fConst198));
		this.fConst228 = (this.fConst224 + 0.000433227);
		this.fConst229 = (((this.fConst170 + -0.512479) / this.fConst169) + 0.689621);
		this.fConst230 = (2 * (0.689621 - this.fConst198));
		this.fConst231 = (this.fConst198 + 7.62173);
		this.fConst232 = (((this.fConst170 + -0.168405) / this.fConst169) + 1.06936);
		this.fConst233 = (2 * (1.06936 - this.fConst198));
		this.fConst234 = (this.fConst198 + 53.5362);
		this.fConst235 = (((this.fConst208 + -3.18973) / this.fConst207) + 4.07678);
		this.fConst236 = (1 / this.fConst210);
		this.fConst237 = (2 * (4.07678 - this.fConst236));
		this.fConst238 = (this.fConst217 + 0.000407678);
		this.fConst239 = (((this.fConst208 + -0.74313) / this.fConst207) + 1.45007);
		this.fConst240 = (2 * (1.45007 - this.fConst236));
		this.fConst241 = (this.fConst214 + 1.45007);
		this.fConst242 = (((this.fConst208 + -0.157482) / this.fConst207) + 0.93514);
		this.fConst243 = (2 * (0.93514 - this.fConst236));
		this.fConst244 = (this.fConst211 + 0.93514);
		this.fConst245 = Math.tan((12566.4 / this.fConst0));
		this.fConst246 = (1 / this.fConst245);
		this.fConst247 = (1 / (((this.fConst246 + 0.157482) / this.fConst245) + 0.93514));
		this.fConst248 = mydsp_faustpower2_f(this.fConst245);
		this.fConst249 = (50.0638 / this.fConst248);
		this.fConst250 = (2 * (0.93514 - this.fConst249));
		this.fConst251 = (1 / (((this.fConst246 + 0.74313) / this.fConst245) + 1.45007));
		this.fConst252 = (11.0521 / this.fConst248);
		this.fConst253 = (2 * (1.45007 - this.fConst252));
		this.fConst254 = (1 / (((this.fConst246 + 3.18973) / this.fConst245) + 4.07678));
		this.fConst255 = (0.00176617 / this.fConst248);
		this.fConst256 = (2 * (0.000407678 - this.fConst255));
		this.fConst257 = (1 / (((this.fConst208 + 0.168405) / this.fConst207) + 1.06936));
		this.fConst258 = (2 * (53.5362 - this.fConst236));
		this.fConst259 = (1 / (((this.fConst208 + 0.512479) / this.fConst207) + 0.689621));
		this.fConst260 = (2 * (7.62173 - this.fConst236));
		this.fConst261 = (1 / (((this.fConst208 + 0.782413) / this.fConst207) + 0.245292));
		this.fConst262 = (0.0001 / this.fConst210);
		this.fConst263 = (2 * (0.000433227 - this.fConst262));
		this.fConst264 = (((this.fConst208 + -0.782413) / this.fConst207) + 0.245292);
		this.fConst265 = (2 * (0.245292 - this.fConst236));
		this.fConst266 = (this.fConst262 + 0.000433227);
		this.fConst267 = (((this.fConst208 + -0.512479) / this.fConst207) + 0.689621);
		this.fConst268 = (2 * (0.689621 - this.fConst236));
		this.fConst269 = (this.fConst236 + 7.62173);
		this.fConst270 = (((this.fConst208 + -0.168405) / this.fConst207) + 1.06936);
		this.fConst271 = (2 * (1.06936 - this.fConst236));
		this.fConst272 = (this.fConst236 + 53.5362);
		this.fConst273 = (((this.fConst246 + -3.18973) / this.fConst245) + 4.07678);
		this.fConst274 = (1 / this.fConst248);
		this.fConst275 = (2 * (4.07678 - this.fConst274));
		this.fConst276 = (this.fConst255 + 0.000407678);
		this.fConst277 = (((this.fConst246 + -0.74313) / this.fConst245) + 1.45007);
		this.fConst278 = (2 * (1.45007 - this.fConst274));
		this.fConst279 = (this.fConst252 + 1.45007);
		this.fConst280 = (((this.fConst246 + -0.157482) / this.fConst245) + 0.93514);
		this.fConst281 = (2 * (0.93514 - this.fConst274));
		this.fConst282 = (this.fConst249 + 0.93514);
		this.fConst283 = Math.tan((7916.32 / this.fConst0));
		this.fConst284 = (1 / this.fConst283);
		this.fConst285 = (1 / (((this.fConst284 + 0.157482) / this.fConst283) + 0.93514));
		this.fConst286 = mydsp_faustpower2_f(this.fConst283);
		this.fConst287 = (50.0638 / this.fConst286);
		this.fConst288 = (2 * (0.93514 - this.fConst287));
		this.fConst289 = (1 / (((this.fConst284 + 0.74313) / this.fConst283) + 1.45007));
		this.fConst290 = (11.0521 / this.fConst286);
		this.fConst291 = (2 * (1.45007 - this.fConst290));
		this.fConst292 = (1 / (((this.fConst284 + 3.18973) / this.fConst283) + 4.07678));
		this.fConst293 = (0.00176617 / this.fConst286);
		this.fConst294 = (2 * (0.000407678 - this.fConst293));
		this.fConst295 = (1 / (((this.fConst246 + 0.168405) / this.fConst245) + 1.06936));
		this.fConst296 = (2 * (53.5362 - this.fConst274));
		this.fConst297 = (1 / (((this.fConst246 + 0.512479) / this.fConst245) + 0.689621));
		this.fConst298 = (2 * (7.62173 - this.fConst274));
		this.fConst299 = (1 / (((this.fConst246 + 0.782413) / this.fConst245) + 0.245292));
		this.fConst300 = (0.0001 / this.fConst248);
		this.fConst301 = (2 * (0.000433227 - this.fConst300));
		this.fConst302 = (((this.fConst246 + -0.782413) / this.fConst245) + 0.245292);
		this.fConst303 = (2 * (0.245292 - this.fConst274));
		this.fConst304 = (this.fConst300 + 0.000433227);
		this.fConst305 = (((this.fConst246 + -0.512479) / this.fConst245) + 0.689621);
		this.fConst306 = (2 * (0.689621 - this.fConst274));
		this.fConst307 = (this.fConst274 + 7.62173);
		this.fConst308 = (((this.fConst246 + -0.168405) / this.fConst245) + 1.06936);
		this.fConst309 = (2 * (1.06936 - this.fConst274));
		this.fConst310 = (this.fConst274 + 53.5362);
		this.fConst311 = (((this.fConst284 + -3.18973) / this.fConst283) + 4.07678);
		this.fConst312 = (1 / this.fConst286);
		this.fConst313 = (2 * (4.07678 - this.fConst312));
		this.fConst314 = (this.fConst293 + 0.000407678);
		this.fConst315 = (((this.fConst284 + -0.74313) / this.fConst283) + 1.45007);
		this.fConst316 = (2 * (1.45007 - this.fConst312));
		this.fConst317 = (this.fConst290 + 1.45007);
		this.fConst318 = (((this.fConst284 + -0.157482) / this.fConst283) + 0.93514);
		this.fConst319 = (2 * (0.93514 - this.fConst312));
		this.fConst320 = (this.fConst287 + 0.93514);
		this.fConst321 = Math.tan((4986.97 / this.fConst0));
		this.fConst322 = (1 / this.fConst321);
		this.fConst323 = (1 / (((this.fConst322 + 0.157482) / this.fConst321) + 0.93514));
		this.fConst324 = mydsp_faustpower2_f(this.fConst321);
		this.fConst325 = (50.0638 / this.fConst324);
		this.fConst326 = (2 * (0.93514 - this.fConst325));
		this.fConst327 = (1 / (((this.fConst322 + 0.74313) / this.fConst321) + 1.45007));
		this.fConst328 = (11.0521 / this.fConst324);
		this.fConst329 = (2 * (1.45007 - this.fConst328));
		this.fConst330 = (1 / (((this.fConst322 + 3.18973) / this.fConst321) + 4.07678));
		this.fConst331 = (0.00176617 / this.fConst324);
		this.fConst332 = (2 * (0.000407678 - this.fConst331));
		this.fConst333 = (1 / (((this.fConst284 + 0.168405) / this.fConst283) + 1.06936));
		this.fConst334 = (2 * (53.5362 - this.fConst312));
		this.fConst335 = (1 / (((this.fConst284 + 0.512479) / this.fConst283) + 0.689621));
		this.fConst336 = (2 * (7.62173 - this.fConst312));
		this.fConst337 = (1 / (((this.fConst284 + 0.782413) / this.fConst283) + 0.245292));
		this.fConst338 = (0.0001 / this.fConst286);
		this.fConst339 = (2 * (0.000433227 - this.fConst338));
		this.fConst340 = (((this.fConst284 + -0.782413) / this.fConst283) + 0.245292);
		this.fConst341 = (2 * (0.245292 - this.fConst312));
		this.fConst342 = (this.fConst338 + 0.000433227);
		this.fConst343 = (((this.fConst284 + -0.512479) / this.fConst283) + 0.689621);
		this.fConst344 = (2 * (0.689621 - this.fConst312));
		this.fConst345 = (this.fConst312 + 7.62173);
		this.fConst346 = (((this.fConst284 + -0.168405) / this.fConst283) + 1.06936);
		this.fConst347 = (2 * (1.06936 - this.fConst312));
		this.fConst348 = (this.fConst312 + 53.5362);
		this.fConst349 = (((this.fConst322 + -3.18973) / this.fConst321) + 4.07678);
		this.fConst350 = (1 / this.fConst324);
		this.fConst351 = (2 * (4.07678 - this.fConst350));
		this.fConst352 = (this.fConst331 + 0.000407678);
		this.fConst353 = (((this.fConst322 + -0.74313) / this.fConst321) + 1.45007);
		this.fConst354 = (2 * (1.45007 - this.fConst350));
		this.fConst355 = (this.fConst328 + 1.45007);
		this.fConst356 = (((this.fConst322 + -0.157482) / this.fConst321) + 0.93514);
		this.fConst357 = (2 * (0.93514 - this.fConst350));
		this.fConst358 = (this.fConst325 + 0.93514);
		this.fConst359 = Math.tan((3141.59 / this.fConst0));
		this.fConst360 = (1 / this.fConst359);
		this.fConst361 = (1 / (((this.fConst360 + 0.157482) / this.fConst359) + 0.93514));
		this.fConst362 = mydsp_faustpower2_f(this.fConst359);
		this.fConst363 = (50.0638 / this.fConst362);
		this.fConst364 = (2 * (0.93514 - this.fConst363));
		this.fConst365 = (1 / (((this.fConst360 + 0.74313) / this.fConst359) + 1.45007));
		this.fConst366 = (11.0521 / this.fConst362);
		this.fConst367 = (2 * (1.45007 - this.fConst366));
		this.fConst368 = (1 / (((this.fConst360 + 3.18973) / this.fConst359) + 4.07678));
		this.fConst369 = (0.00176617 / this.fConst362);
		this.fConst370 = (2 * (0.000407678 - this.fConst369));
		this.fConst371 = (1 / (((this.fConst322 + 0.168405) / this.fConst321) + 1.06936));
		this.fConst372 = (2 * (53.5362 - this.fConst350));
		this.fConst373 = (1 / (((this.fConst322 + 0.512479) / this.fConst321) + 0.689621));
		this.fConst374 = (2 * (7.62173 - this.fConst350));
		this.fConst375 = (1 / (((this.fConst322 + 0.782413) / this.fConst321) + 0.245292));
		this.fConst376 = (0.0001 / this.fConst324);
		this.fConst377 = (2 * (0.000433227 - this.fConst376));
		this.fConst378 = (((this.fConst322 + -0.782413) / this.fConst321) + 0.245292);
		this.fConst379 = (2 * (0.245292 - this.fConst350));
		this.fConst380 = (this.fConst376 + 0.000433227);
		this.fConst381 = (((this.fConst322 + -0.512479) / this.fConst321) + 0.689621);
		this.fConst382 = (2 * (0.689621 - this.fConst350));
		this.fConst383 = (this.fConst350 + 7.62173);
		this.fConst384 = (((this.fConst322 + -0.168405) / this.fConst321) + 1.06936);
		this.fConst385 = (2 * (1.06936 - this.fConst350));
		this.fConst386 = (this.fConst350 + 53.5362);
		this.fConst387 = (((this.fConst360 + -3.18973) / this.fConst359) + 4.07678);
		this.fConst388 = (1 / this.fConst362);
		this.fConst389 = (2 * (4.07678 - this.fConst388));
		this.fConst390 = (this.fConst369 + 0.000407678);
		this.fConst391 = (((this.fConst360 + -0.74313) / this.fConst359) + 1.45007);
		this.fConst392 = (2 * (1.45007 - this.fConst388));
		this.fConst393 = (this.fConst366 + 1.45007);
		this.fConst394 = (((this.fConst360 + -0.157482) / this.fConst359) + 0.93514);
		this.fConst395 = (2 * (0.93514 - this.fConst388));
		this.fConst396 = (this.fConst363 + 0.93514);
		this.fConst397 = Math.tan((1979.08 / this.fConst0));
		this.fConst398 = (1 / this.fConst397);
		this.fConst399 = (1 / (((this.fConst398 + 0.157482) / this.fConst397) + 0.93514));
		this.fConst400 = mydsp_faustpower2_f(this.fConst397);
		this.fConst401 = (50.0638 / this.fConst400);
		this.fConst402 = (2 * (0.93514 - this.fConst401));
		this.fConst403 = (1 / (((this.fConst398 + 0.74313) / this.fConst397) + 1.45007));
		this.fConst404 = (11.0521 / this.fConst400);
		this.fConst405 = (2 * (1.45007 - this.fConst404));
		this.fConst406 = (1 / (((this.fConst398 + 3.18973) / this.fConst397) + 4.07678));
		this.fConst407 = (0.00176617 / this.fConst400);
		this.fConst408 = (2 * (0.000407678 - this.fConst407));
		this.fConst409 = (1 / (((this.fConst360 + 0.168405) / this.fConst359) + 1.06936));
		this.fConst410 = (2 * (53.5362 - this.fConst388));
		this.fConst411 = (1 / (((this.fConst360 + 0.512479) / this.fConst359) + 0.689621));
		this.fConst412 = (2 * (7.62173 - this.fConst388));
		this.fConst413 = (1 / (((this.fConst360 + 0.782413) / this.fConst359) + 0.245292));
		this.fConst414 = (0.0001 / this.fConst362);
		this.fConst415 = (2 * (0.000433227 - this.fConst414));
		this.fConst416 = (((this.fConst360 + -0.782413) / this.fConst359) + 0.245292);
		this.fConst417 = (2 * (0.245292 - this.fConst388));
		this.fConst418 = (this.fConst414 + 0.000433227);
		this.fConst419 = (((this.fConst360 + -0.512479) / this.fConst359) + 0.689621);
		this.fConst420 = (2 * (0.689621 - this.fConst388));
		this.fConst421 = (this.fConst388 + 7.62173);
		this.fConst422 = (((this.fConst360 + -0.168405) / this.fConst359) + 1.06936);
		this.fConst423 = (2 * (1.06936 - this.fConst388));
		this.fConst424 = (this.fConst388 + 53.5362);
		this.fConst425 = (((this.fConst398 + -3.18973) / this.fConst397) + 4.07678);
		this.fConst426 = (1 / this.fConst400);
		this.fConst427 = (2 * (4.07678 - this.fConst426));
		this.fConst428 = (this.fConst407 + 0.000407678);
		this.fConst429 = (((this.fConst398 + -0.74313) / this.fConst397) + 1.45007);
		this.fConst430 = (2 * (1.45007 - this.fConst426));
		this.fConst431 = (this.fConst404 + 1.45007);
		this.fConst432 = (((this.fConst398 + -0.157482) / this.fConst397) + 0.93514);
		this.fConst433 = (2 * (0.93514 - this.fConst426));
		this.fConst434 = (this.fConst401 + 0.93514);
		this.fConst435 = Math.tan((1246.74 / this.fConst0));
		this.fConst436 = (1 / this.fConst435);
		this.fConst437 = (1 / (((this.fConst436 + 0.157482) / this.fConst435) + 0.93514));
		this.fConst438 = mydsp_faustpower2_f(this.fConst435);
		this.fConst439 = (50.0638 / this.fConst438);
		this.fConst440 = (2 * (0.93514 - this.fConst439));
		this.fConst441 = (1 / (((this.fConst436 + 0.74313) / this.fConst435) + 1.45007));
		this.fConst442 = (11.0521 / this.fConst438);
		this.fConst443 = (2 * (1.45007 - this.fConst442));
		this.fConst444 = (1 / (((this.fConst436 + 3.18973) / this.fConst435) + 4.07678));
		this.fConst445 = (0.00176617 / this.fConst438);
		this.fConst446 = (2 * (0.000407678 - this.fConst445));
		this.fConst447 = (1 / (((this.fConst398 + 0.168405) / this.fConst397) + 1.06936));
		this.fConst448 = (2 * (53.5362 - this.fConst426));
		this.fConst449 = (1 / (((this.fConst398 + 0.512479) / this.fConst397) + 0.689621));
		this.fConst450 = (2 * (7.62173 - this.fConst426));
		this.fConst451 = (1 / (((this.fConst398 + 0.782413) / this.fConst397) + 0.245292));
		this.fConst452 = (0.0001 / this.fConst400);
		this.fConst453 = (2 * (0.000433227 - this.fConst452));
		this.fConst454 = (((this.fConst398 + -0.782413) / this.fConst397) + 0.245292);
		this.fConst455 = (2 * (0.245292 - this.fConst426));
		this.fConst456 = (this.fConst452 + 0.000433227);
		this.fConst457 = (((this.fConst398 + -0.512479) / this.fConst397) + 0.689621);
		this.fConst458 = (2 * (0.689621 - this.fConst426));
		this.fConst459 = (this.fConst426 + 7.62173);
		this.fConst460 = (((this.fConst398 + -0.168405) / this.fConst397) + 1.06936);
		this.fConst461 = (2 * (1.06936 - this.fConst426));
		this.fConst462 = (this.fConst426 + 53.5362);
		this.fConst463 = (((this.fConst436 + -3.18973) / this.fConst435) + 4.07678);
		this.fConst464 = (1 / this.fConst438);
		this.fConst465 = (2 * (4.07678 - this.fConst464));
		this.fConst466 = (this.fConst445 + 0.000407678);
		this.fConst467 = (((this.fConst436 + -0.74313) / this.fConst435) + 1.45007);
		this.fConst468 = (2 * (1.45007 - this.fConst464));
		this.fConst469 = (this.fConst442 + 1.45007);
		this.fConst470 = (((this.fConst436 + -0.157482) / this.fConst435) + 0.93514);
		this.fConst471 = (2 * (0.93514 - this.fConst464));
		this.fConst472 = (this.fConst439 + 0.93514);
		this.fConst473 = Math.tan((785.398 / this.fConst0));
		this.fConst474 = (1 / this.fConst473);
		this.fConst475 = (1 / (((this.fConst474 + 0.157482) / this.fConst473) + 0.93514));
		this.fConst476 = mydsp_faustpower2_f(this.fConst473);
		this.fConst477 = (50.0638 / this.fConst476);
		this.fConst478 = (2 * (0.93514 - this.fConst477));
		this.fConst479 = (1 / (((this.fConst474 + 0.74313) / this.fConst473) + 1.45007));
		this.fConst480 = (11.0521 / this.fConst476);
		this.fConst481 = (2 * (1.45007 - this.fConst480));
		this.fConst482 = (1 / (((this.fConst474 + 3.18973) / this.fConst473) + 4.07678));
		this.fConst483 = (0.00176617 / this.fConst476);
		this.fConst484 = (2 * (0.000407678 - this.fConst483));
		this.fConst485 = (1 / (((this.fConst436 + 0.168405) / this.fConst435) + 1.06936));
		this.fConst486 = (2 * (53.5362 - this.fConst464));
		this.fConst487 = (1 / (((this.fConst436 + 0.512479) / this.fConst435) + 0.689621));
		this.fConst488 = (2 * (7.62173 - this.fConst464));
		this.fConst489 = (1 / (((this.fConst436 + 0.782413) / this.fConst435) + 0.245292));
		this.fConst490 = (0.0001 / this.fConst438);
		this.fConst491 = (2 * (0.000433227 - this.fConst490));
		this.fConst492 = (((this.fConst436 + -0.782413) / this.fConst435) + 0.245292);
		this.fConst493 = (2 * (0.245292 - this.fConst464));
		this.fConst494 = (this.fConst490 + 0.000433227);
		this.fConst495 = (((this.fConst436 + -0.512479) / this.fConst435) + 0.689621);
		this.fConst496 = (2 * (0.689621 - this.fConst464));
		this.fConst497 = (this.fConst464 + 7.62173);
		this.fConst498 = (((this.fConst436 + -0.168405) / this.fConst435) + 1.06936);
		this.fConst499 = (2 * (1.06936 - this.fConst464));
		this.fConst500 = (this.fConst464 + 53.5362);
		this.fConst501 = (((this.fConst474 + -3.18973) / this.fConst473) + 4.07678);
		this.fConst502 = (1 / this.fConst476);
		this.fConst503 = (2 * (4.07678 - this.fConst502));
		this.fConst504 = (this.fConst483 + 0.000407678);
		this.fConst505 = (((this.fConst474 + -0.74313) / this.fConst473) + 1.45007);
		this.fConst506 = (2 * (1.45007 - this.fConst502));
		this.fConst507 = (this.fConst480 + 1.45007);
		this.fConst508 = (((this.fConst474 + -0.157482) / this.fConst473) + 0.93514);
		this.fConst509 = (2 * (0.93514 - this.fConst502));
		this.fConst510 = (this.fConst477 + 0.93514);
		this.fConst511 = Math.tan((494.77 / this.fConst0));
		this.fConst512 = (1 / this.fConst511);
		this.fConst513 = (1 / (((this.fConst512 + 0.157482) / this.fConst511) + 0.93514));
		this.fConst514 = mydsp_faustpower2_f(this.fConst511);
		this.fConst515 = (50.0638 / this.fConst514);
		this.fConst516 = (2 * (0.93514 - this.fConst515));
		this.fConst517 = (1 / (((this.fConst512 + 0.74313) / this.fConst511) + 1.45007));
		this.fConst518 = (11.0521 / this.fConst514);
		this.fConst519 = (2 * (1.45007 - this.fConst518));
		this.fConst520 = (1 / (((this.fConst512 + 3.18973) / this.fConst511) + 4.07678));
		this.fConst521 = (0.00176617 / this.fConst514);
		this.fConst522 = (2 * (0.000407678 - this.fConst521));
		this.fConst523 = (1 / (((this.fConst474 + 0.168405) / this.fConst473) + 1.06936));
		this.fConst524 = (2 * (53.5362 - this.fConst502));
		this.fConst525 = (1 / (((this.fConst474 + 0.512479) / this.fConst473) + 0.689621));
		this.fConst526 = (2 * (7.62173 - this.fConst502));
		this.fConst527 = (1 / (((this.fConst474 + 0.782413) / this.fConst473) + 0.245292));
		this.fConst528 = (0.0001 / this.fConst476);
		this.fConst529 = (2 * (0.000433227 - this.fConst528));
		this.fConst530 = (((this.fConst474 + -0.782413) / this.fConst473) + 0.245292);
		this.fConst531 = (2 * (0.245292 - this.fConst502));
		this.fConst532 = (this.fConst528 + 0.000433227);
		this.fConst533 = (((this.fConst474 + -0.512479) / this.fConst473) + 0.689621);
		this.fConst534 = (2 * (0.689621 - this.fConst502));
		this.fConst535 = (this.fConst502 + 7.62173);
		this.fConst536 = (((this.fConst474 + -0.168405) / this.fConst473) + 1.06936);
		this.fConst537 = (2 * (1.06936 - this.fConst502));
		this.fConst538 = (this.fConst502 + 53.5362);
		this.fConst539 = (((this.fConst512 + -3.18973) / this.fConst511) + 4.07678);
		this.fConst540 = (1 / this.fConst514);
		this.fConst541 = (2 * (4.07678 - this.fConst540));
		this.fConst542 = (this.fConst521 + 0.000407678);
		this.fConst543 = (((this.fConst512 + -0.74313) / this.fConst511) + 1.45007);
		this.fConst544 = (2 * (1.45007 - this.fConst540));
		this.fConst545 = (this.fConst518 + 1.45007);
		this.fConst546 = (((this.fConst512 + -0.157482) / this.fConst511) + 0.93514);
		this.fConst547 = (2 * (0.93514 - this.fConst540));
		this.fConst548 = (this.fConst515 + 0.93514);
		this.fConst549 = Math.tan((311.685 / this.fConst0));
		this.fConst550 = (1 / this.fConst549);
		this.fConst551 = (1 / (((this.fConst550 + 0.157482) / this.fConst549) + 0.93514));
		this.fConst552 = mydsp_faustpower2_f(this.fConst549);
		this.fConst553 = (50.0638 / this.fConst552);
		this.fConst554 = (2 * (0.93514 - this.fConst553));
		this.fConst555 = (1 / (((this.fConst550 + 0.74313) / this.fConst549) + 1.45007));
		this.fConst556 = (11.0521 / this.fConst552);
		this.fConst557 = (2 * (1.45007 - this.fConst556));
		this.fConst558 = (1 / (((this.fConst550 + 3.18973) / this.fConst549) + 4.07678));
		this.fConst559 = (0.00176617 / this.fConst552);
		this.fConst560 = (2 * (0.000407678 - this.fConst559));
		this.fConst561 = (1 / (((this.fConst512 + 0.168405) / this.fConst511) + 1.06936));
		this.fConst562 = (2 * (53.5362 - this.fConst540));
		this.fConst563 = (1 / (((this.fConst512 + 0.512479) / this.fConst511) + 0.689621));
		this.fConst564 = (2 * (7.62173 - this.fConst540));
		this.fConst565 = (1 / (((this.fConst512 + 0.782413) / this.fConst511) + 0.245292));
		this.fConst566 = (0.0001 / this.fConst514);
		this.fConst567 = (2 * (0.000433227 - this.fConst566));
		this.fConst568 = (((this.fConst512 + -0.782413) / this.fConst511) + 0.245292);
		this.fConst569 = (2 * (0.245292 - this.fConst540));
		this.fConst570 = (this.fConst566 + 0.000433227);
		this.fConst571 = (((this.fConst512 + -0.512479) / this.fConst511) + 0.689621);
		this.fConst572 = (2 * (0.689621 - this.fConst540));
		this.fConst573 = (this.fConst540 + 7.62173);
		this.fConst574 = (((this.fConst512 + -0.168405) / this.fConst511) + 1.06936);
		this.fConst575 = (2 * (1.06936 - this.fConst540));
		this.fConst576 = (this.fConst540 + 53.5362);
		this.fConst577 = (((this.fConst550 + -3.18973) / this.fConst549) + 4.07678);
		this.fConst578 = (1 / this.fConst552);
		this.fConst579 = (2 * (4.07678 - this.fConst578));
		this.fConst580 = (this.fConst559 + 0.000407678);
		this.fConst581 = (((this.fConst550 + -0.74313) / this.fConst549) + 1.45007);
		this.fConst582 = (2 * (1.45007 - this.fConst578));
		this.fConst583 = (this.fConst556 + 1.45007);
		this.fConst584 = (((this.fConst550 + -0.157482) / this.fConst549) + 0.93514);
		this.fConst585 = (2 * (0.93514 - this.fConst578));
		this.fConst586 = (this.fConst553 + 0.93514);
		this.fConst587 = Math.tan((196.35 / this.fConst0));
		this.fConst588 = (1 / this.fConst587);
		this.fConst589 = (1 / (((this.fConst588 + 0.157482) / this.fConst587) + 0.93514));
		this.fConst590 = mydsp_faustpower2_f(this.fConst587);
		this.fConst591 = (50.0638 / this.fConst590);
		this.fConst592 = (2 * (0.93514 - this.fConst591));
		this.fConst593 = (1 / (((this.fConst588 + 0.74313) / this.fConst587) + 1.45007));
		this.fConst594 = (11.0521 / this.fConst590);
		this.fConst595 = (2 * (1.45007 - this.fConst594));
		this.fConst596 = (1 / (((this.fConst588 + 3.18973) / this.fConst587) + 4.07678));
		this.fConst597 = (0.00176617 / this.fConst590);
		this.fConst598 = (2 * (0.000407678 - this.fConst597));
		this.fConst599 = (1 / (((this.fConst550 + 0.168405) / this.fConst549) + 1.06936));
		this.fConst600 = (2 * (53.5362 - this.fConst578));
		this.fConst601 = (1 / (((this.fConst550 + 0.512479) / this.fConst549) + 0.689621));
		this.fConst602 = (2 * (7.62173 - this.fConst578));
		this.fConst603 = (1 / (((this.fConst550 + 0.782413) / this.fConst549) + 0.245292));
		this.fConst604 = (0.0001 / this.fConst552);
		this.fConst605 = (2 * (0.000433227 - this.fConst604));
		this.fConst606 = (((this.fConst550 + -0.782413) / this.fConst549) + 0.245292);
		this.fConst607 = (2 * (0.245292 - this.fConst578));
		this.fConst608 = (this.fConst604 + 0.000433227);
		this.fConst609 = (((this.fConst550 + -0.512479) / this.fConst549) + 0.689621);
		this.fConst610 = (2 * (0.689621 - this.fConst578));
		this.fConst611 = (this.fConst578 + 7.62173);
		this.fConst612 = (((this.fConst550 + -0.168405) / this.fConst549) + 1.06936);
		this.fConst613 = (2 * (1.06936 - this.fConst578));
		this.fConst614 = (this.fConst578 + 53.5362);
		this.fConst615 = (((this.fConst588 + -3.18973) / this.fConst587) + 4.07678);
		this.fConst616 = (1 / this.fConst590);
		this.fConst617 = (2 * (4.07678 - this.fConst616));
		this.fConst618 = (this.fConst597 + 0.000407678);
		this.fConst619 = (((this.fConst588 + -0.74313) / this.fConst587) + 1.45007);
		this.fConst620 = (2 * (1.45007 - this.fConst616));
		this.fConst621 = (this.fConst594 + 1.45007);
		this.fConst622 = (((this.fConst588 + -0.157482) / this.fConst587) + 0.93514);
		this.fConst623 = (2 * (0.93514 - this.fConst616));
		this.fConst624 = (this.fConst591 + 0.93514);
		this.fConst625 = Math.tan((123.692 / this.fConst0));
		this.fConst626 = (1 / this.fConst625);
		this.fConst627 = (1 / (((this.fConst626 + 0.157482) / this.fConst625) + 0.93514));
		this.fConst628 = mydsp_faustpower2_f(this.fConst625);
		this.fConst629 = (50.0638 / this.fConst628);
		this.fConst630 = (2 * (0.93514 - this.fConst629));
		this.fConst631 = (1 / (((this.fConst626 + 0.74313) / this.fConst625) + 1.45007));
		this.fConst632 = (11.0521 / this.fConst628);
		this.fConst633 = (2 * (1.45007 - this.fConst632));
		this.fConst634 = (1 / (((this.fConst626 + 3.18973) / this.fConst625) + 4.07678));
		this.fConst635 = (0.00176617 / this.fConst628);
		this.fConst636 = (2 * (0.000407678 - this.fConst635));
		this.fConst637 = (1 / (((this.fConst588 + 0.168405) / this.fConst587) + 1.06936));
		this.fConst638 = (2 * (53.5362 - this.fConst616));
		this.fConst639 = (1 / (((this.fConst588 + 0.512479) / this.fConst587) + 0.689621));
		this.fConst640 = (2 * (7.62173 - this.fConst616));
		this.fConst641 = (1 / (((this.fConst588 + 0.782413) / this.fConst587) + 0.245292));
		this.fConst642 = (0.0001 / this.fConst590);
		this.fConst643 = (2 * (0.000433227 - this.fConst642));
		this.fConst644 = (((this.fConst588 + -0.782413) / this.fConst587) + 0.245292);
		this.fConst645 = (2 * (0.245292 - this.fConst616));
		this.fConst646 = (this.fConst642 + 0.000433227);
		this.fConst647 = (((this.fConst588 + -0.512479) / this.fConst587) + 0.689621);
		this.fConst648 = (2 * (0.689621 - this.fConst616));
		this.fConst649 = (this.fConst616 + 7.62173);
		this.fConst650 = (((this.fConst588 + -0.168405) / this.fConst587) + 1.06936);
		this.fConst651 = (2 * (1.06936 - this.fConst616));
		this.fConst652 = (this.fConst616 + 53.5362);
		this.fConst653 = (((this.fConst626 + -3.18973) / this.fConst625) + 4.07678);
		this.fConst654 = (1 / this.fConst628);
		this.fConst655 = (2 * (4.07678 - this.fConst654));
		this.fConst656 = (this.fConst635 + 0.000407678);
		this.fConst657 = (((this.fConst626 + -0.74313) / this.fConst625) + 1.45007);
		this.fConst658 = (2 * (1.45007 - this.fConst654));
		this.fConst659 = (this.fConst632 + 1.45007);
		this.fConst660 = (((this.fConst626 + -0.157482) / this.fConst625) + 0.93514);
		this.fConst661 = (2 * (0.93514 - this.fConst654));
		this.fConst662 = (this.fConst629 + 0.93514);
		this.fConst663 = (1 / (((this.fConst626 + 0.168405) / this.fConst625) + 1.06936));
		this.fConst664 = (2 * (53.5362 - this.fConst654));
		this.fConst665 = (1 / (((this.fConst626 + 0.512479) / this.fConst625) + 0.689621));
		this.fConst666 = (2 * (7.62173 - this.fConst654));
		this.fConst667 = (1 / (((this.fConst626 + 0.782413) / this.fConst625) + 0.245292));
		this.fConst668 = (0.0001 / this.fConst628);
		this.fConst669 = (2 * (0.000433227 - this.fConst668));
		this.fConst670 = (((this.fConst626 + -0.782413) / this.fConst625) + 0.245292);
		this.fConst671 = (2 * (0.245292 - this.fConst654));
		this.fConst672 = (this.fConst668 + 0.000433227);
		this.fConst673 = (((this.fConst626 + -0.512479) / this.fConst625) + 0.689621);
		this.fConst674 = (2 * (0.689621 - this.fConst654));
		this.fConst675 = (this.fConst654 + 7.62173);
		this.fConst676 = (((this.fConst626 + -0.168405) / this.fConst625) + 1.06936);
		this.fConst677 = (2 * (1.06936 - this.fConst654));
		this.fConst678 = (this.fConst654 + 53.5362);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		this.fCheckbox0 = 0;
		this.fVslider0 = -20;
		this.fCheckbox1 = 0;
		this.fCheckbox2 = 0;
		this.fEntry0 = 2;
		this.fVslider1 = 49;
		this.fVslider2 = 0.1;
		this.fVslider3 = -0.1;
		this.fVslider4 = 0.1;
		this.fCheckbox3 = 0;
		this.fVslider5 = -10;
		this.fVslider6 = -10;
		this.fVslider7 = -10;
		this.fVslider8 = -10;
		this.fVslider9 = -10;
		this.fVslider10 = -10;
		this.fVslider11 = -10;
		this.fVslider12 = -10;
		this.fVslider13 = -10;
		this.fVslider14 = -10;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			this.iVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec23[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec25[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fVec1[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec24[l4] = 0;
			
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
			this.fRec26[l12] = 0;
			
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
			this.fRec27[l20] = 0;
			
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
			this.iRec28[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			this.fRec29[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fVec22[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec22[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			this.fRec21[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			this.fRec20[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fVec23[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec19[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			this.fRec18[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			this.fRec17[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fVec24[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec16[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			this.fRec15[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec14[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fVec25[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec13[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec12[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec11[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fVec26[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec10[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec9[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec8[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec7[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec6[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec5[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec4[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec30[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			this.fRec39[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec38[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec37[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fVec27[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			this.fRec36[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec35[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec34[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec33[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec32[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec31[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			this.fRec40[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			this.fRec48[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			this.fRec47[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec46[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			this.fVec28[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			this.fRec45[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			this.fRec44[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			this.fRec43[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec42[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			this.fRec41[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			this.fRec49[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			this.fRec56[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec55[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			this.fRec54[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			this.fVec29[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			this.fRec53[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec52[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			this.fRec51[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec50[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			this.fRec57[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			this.fRec63[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			this.fRec62[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec61[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			this.fVec30[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			this.fRec60[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec59[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec58[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			this.fRec64[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			this.fRec67[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec66[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec65[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			this.fRec68[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			this.fRec79[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			this.fRec78[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			this.fRec77[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			this.fRec76[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec75[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			this.fRec74[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec73[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec72[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			this.fRec71[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			this.fRec70[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			this.fRec69[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			this.fRec80[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
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
		for (var l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			this.fRec86[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			this.fRec85[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			this.fRec84[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			this.fRec83[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec82[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			this.fRec81[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			this.fRec91[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			this.fRec100[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			this.fRec99[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			this.fRec98[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			this.fRec97[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec96[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec95[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			this.fRec94[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			this.fRec93[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			this.fRec92[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			this.fRec101[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
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
		for (var l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			this.fRec104[l134] = 0;
			
		}
		for (var l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			this.fRec103[l135] = 0;
			
		}
		for (var l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			this.fRec102[l136] = 0;
			
		}
		for (var l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			this.fRec110[l137] = 0;
			
		}
		for (var l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			this.fRec3[l138] = 0;
			
		}
		for (var l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			this.fRec2[l139] = 0;
			
		}
		for (var l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			this.fRec1[l140] = 0;
			
		}
		for (var l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			this.fRec0[l141] = 0;
			
		}
		for (var l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			this.fRec117[l142] = 0;
			
		}
		for (var l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			this.fRec116[l143] = 0;
			
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
		for (var l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			this.fRec112[l147] = 0;
			
		}
		for (var l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			this.fRec111[l148] = 0;
			
		}
		for (var l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			this.fRec124[l149] = 0;
			
		}
		for (var l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			this.fRec123[l150] = 0;
			
		}
		for (var l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			this.fRec122[l151] = 0;
			
		}
		for (var l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			this.fRec121[l152] = 0;
			
		}
		for (var l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			this.fRec120[l153] = 0;
			
		}
		for (var l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			this.fRec119[l154] = 0;
			
		}
		for (var l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			this.fRec118[l155] = 0;
			
		}
		for (var l156 = 0; (l156 < 3); l156 = (l156 + 1)) {
			this.fRec131[l156] = 0;
			
		}
		for (var l157 = 0; (l157 < 3); l157 = (l157 + 1)) {
			this.fRec130[l157] = 0;
			
		}
		for (var l158 = 0; (l158 < 3); l158 = (l158 + 1)) {
			this.fRec129[l158] = 0;
			
		}
		for (var l159 = 0; (l159 < 3); l159 = (l159 + 1)) {
			this.fRec128[l159] = 0;
			
		}
		for (var l160 = 0; (l160 < 3); l160 = (l160 + 1)) {
			this.fRec127[l160] = 0;
			
		}
		for (var l161 = 0; (l161 < 3); l161 = (l161 + 1)) {
			this.fRec126[l161] = 0;
			
		}
		for (var l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			this.fRec125[l162] = 0;
			
		}
		for (var l163 = 0; (l163 < 3); l163 = (l163 + 1)) {
			this.fRec138[l163] = 0;
			
		}
		for (var l164 = 0; (l164 < 3); l164 = (l164 + 1)) {
			this.fRec137[l164] = 0;
			
		}
		for (var l165 = 0; (l165 < 3); l165 = (l165 + 1)) {
			this.fRec136[l165] = 0;
			
		}
		for (var l166 = 0; (l166 < 3); l166 = (l166 + 1)) {
			this.fRec135[l166] = 0;
			
		}
		for (var l167 = 0; (l167 < 3); l167 = (l167 + 1)) {
			this.fRec134[l167] = 0;
			
		}
		for (var l168 = 0; (l168 < 3); l168 = (l168 + 1)) {
			this.fRec133[l168] = 0;
			
		}
		for (var l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			this.fRec132[l169] = 0;
			
		}
		for (var l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			this.fRec145[l170] = 0;
			
		}
		for (var l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			this.fRec144[l171] = 0;
			
		}
		for (var l172 = 0; (l172 < 3); l172 = (l172 + 1)) {
			this.fRec143[l172] = 0;
			
		}
		for (var l173 = 0; (l173 < 3); l173 = (l173 + 1)) {
			this.fRec142[l173] = 0;
			
		}
		for (var l174 = 0; (l174 < 3); l174 = (l174 + 1)) {
			this.fRec141[l174] = 0;
			
		}
		for (var l175 = 0; (l175 < 3); l175 = (l175 + 1)) {
			this.fRec140[l175] = 0;
			
		}
		for (var l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			this.fRec139[l176] = 0;
			
		}
		for (var l177 = 0; (l177 < 3); l177 = (l177 + 1)) {
			this.fRec152[l177] = 0;
			
		}
		for (var l178 = 0; (l178 < 3); l178 = (l178 + 1)) {
			this.fRec151[l178] = 0;
			
		}
		for (var l179 = 0; (l179 < 3); l179 = (l179 + 1)) {
			this.fRec150[l179] = 0;
			
		}
		for (var l180 = 0; (l180 < 3); l180 = (l180 + 1)) {
			this.fRec149[l180] = 0;
			
		}
		for (var l181 = 0; (l181 < 3); l181 = (l181 + 1)) {
			this.fRec148[l181] = 0;
			
		}
		for (var l182 = 0; (l182 < 3); l182 = (l182 + 1)) {
			this.fRec147[l182] = 0;
			
		}
		for (var l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			this.fRec146[l183] = 0;
			
		}
		for (var l184 = 0; (l184 < 3); l184 = (l184 + 1)) {
			this.fRec159[l184] = 0;
			
		}
		for (var l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			this.fRec158[l185] = 0;
			
		}
		for (var l186 = 0; (l186 < 3); l186 = (l186 + 1)) {
			this.fRec157[l186] = 0;
			
		}
		for (var l187 = 0; (l187 < 3); l187 = (l187 + 1)) {
			this.fRec156[l187] = 0;
			
		}
		for (var l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			this.fRec155[l188] = 0;
			
		}
		for (var l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			this.fRec154[l189] = 0;
			
		}
		for (var l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			this.fRec153[l190] = 0;
			
		}
		for (var l191 = 0; (l191 < 3); l191 = (l191 + 1)) {
			this.fRec166[l191] = 0;
			
		}
		for (var l192 = 0; (l192 < 3); l192 = (l192 + 1)) {
			this.fRec165[l192] = 0;
			
		}
		for (var l193 = 0; (l193 < 3); l193 = (l193 + 1)) {
			this.fRec164[l193] = 0;
			
		}
		for (var l194 = 0; (l194 < 3); l194 = (l194 + 1)) {
			this.fRec163[l194] = 0;
			
		}
		for (var l195 = 0; (l195 < 3); l195 = (l195 + 1)) {
			this.fRec162[l195] = 0;
			
		}
		for (var l196 = 0; (l196 < 3); l196 = (l196 + 1)) {
			this.fRec161[l196] = 0;
			
		}
		for (var l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			this.fRec160[l197] = 0;
			
		}
		for (var l198 = 0; (l198 < 3); l198 = (l198 + 1)) {
			this.fRec173[l198] = 0;
			
		}
		for (var l199 = 0; (l199 < 3); l199 = (l199 + 1)) {
			this.fRec172[l199] = 0;
			
		}
		for (var l200 = 0; (l200 < 3); l200 = (l200 + 1)) {
			this.fRec171[l200] = 0;
			
		}
		for (var l201 = 0; (l201 < 3); l201 = (l201 + 1)) {
			this.fRec170[l201] = 0;
			
		}
		for (var l202 = 0; (l202 < 3); l202 = (l202 + 1)) {
			this.fRec169[l202] = 0;
			
		}
		for (var l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			this.fRec168[l203] = 0;
			
		}
		for (var l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			this.fRec167[l204] = 0;
			
		}
		for (var l205 = 0; (l205 < 3); l205 = (l205 + 1)) {
			this.fRec180[l205] = 0;
			
		}
		for (var l206 = 0; (l206 < 3); l206 = (l206 + 1)) {
			this.fRec179[l206] = 0;
			
		}
		for (var l207 = 0; (l207 < 3); l207 = (l207 + 1)) {
			this.fRec178[l207] = 0;
			
		}
		for (var l208 = 0; (l208 < 3); l208 = (l208 + 1)) {
			this.fRec177[l208] = 0;
			
		}
		for (var l209 = 0; (l209 < 3); l209 = (l209 + 1)) {
			this.fRec176[l209] = 0;
			
		}
		for (var l210 = 0; (l210 < 3); l210 = (l210 + 1)) {
			this.fRec175[l210] = 0;
			
		}
		for (var l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			this.fRec174[l211] = 0;
			
		}
		for (var l212 = 0; (l212 < 3); l212 = (l212 + 1)) {
			this.fRec187[l212] = 0;
			
		}
		for (var l213 = 0; (l213 < 3); l213 = (l213 + 1)) {
			this.fRec186[l213] = 0;
			
		}
		for (var l214 = 0; (l214 < 3); l214 = (l214 + 1)) {
			this.fRec185[l214] = 0;
			
		}
		for (var l215 = 0; (l215 < 3); l215 = (l215 + 1)) {
			this.fRec184[l215] = 0;
			
		}
		for (var l216 = 0; (l216 < 3); l216 = (l216 + 1)) {
			this.fRec183[l216] = 0;
			
		}
		for (var l217 = 0; (l217 < 3); l217 = (l217 + 1)) {
			this.fRec182[l217] = 0;
			
		}
		for (var l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			this.fRec181[l218] = 0;
			
		}
		for (var l219 = 0; (l219 < 3); l219 = (l219 + 1)) {
			this.fRec194[l219] = 0;
			
		}
		for (var l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			this.fRec193[l220] = 0;
			
		}
		for (var l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			this.fRec192[l221] = 0;
			
		}
		for (var l222 = 0; (l222 < 3); l222 = (l222 + 1)) {
			this.fRec191[l222] = 0;
			
		}
		for (var l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			this.fRec190[l223] = 0;
			
		}
		for (var l224 = 0; (l224 < 3); l224 = (l224 + 1)) {
			this.fRec189[l224] = 0;
			
		}
		for (var l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			this.fRec188[l225] = 0;
			
		}
		for (var l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			this.fRec201[l226] = 0;
			
		}
		for (var l227 = 0; (l227 < 3); l227 = (l227 + 1)) {
			this.fRec200[l227] = 0;
			
		}
		for (var l228 = 0; (l228 < 3); l228 = (l228 + 1)) {
			this.fRec199[l228] = 0;
			
		}
		for (var l229 = 0; (l229 < 3); l229 = (l229 + 1)) {
			this.fRec198[l229] = 0;
			
		}
		for (var l230 = 0; (l230 < 3); l230 = (l230 + 1)) {
			this.fRec197[l230] = 0;
			
		}
		for (var l231 = 0; (l231 < 3); l231 = (l231 + 1)) {
			this.fRec196[l231] = 0;
			
		}
		for (var l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			this.fRec195[l232] = 0;
			
		}
		for (var l233 = 0; (l233 < 3); l233 = (l233 + 1)) {
			this.fRec205[l233] = 0;
			
		}
		for (var l234 = 0; (l234 < 3); l234 = (l234 + 1)) {
			this.fRec204[l234] = 0;
			
		}
		for (var l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			this.fRec203[l235] = 0;
			
		}
		for (var l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			this.fRec202[l236] = 0;
			
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
		ui_interface.declare("0", "2", "");
		ui_interface.openVerticalBox("0x00");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openVerticalBox("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fCheckbox0", "0", "");
		ui_interface.declare("fCheckbox0", "tooltip", "When this is checked, the filter-bank has no effect");
		ui_interface.addCheckButton("Bypass", function handler(obj) { function setval(val) { obj.fCheckbox0 = val; } return setval; }(this));
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("0x00");
		ui_interface.declare("fVslider10", "1", "");
		ui_interface.declare("fVslider10", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider10", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider10 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider9", "2", "");
		ui_interface.declare("fVslider9", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider9", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider8", "3", "");
		ui_interface.declare("fVslider8", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider8", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider7", "4", "");
		ui_interface.declare("fVslider7", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider7", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider6", "5", "");
		ui_interface.declare("fVslider6", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider6", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider5", "6", "");
		ui_interface.declare("fVslider5", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider14", "7", "");
		ui_interface.declare("fVslider14", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider14", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider14 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider13", "8", "");
		ui_interface.declare("fVslider13", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider13", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider13 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider12", "9", "");
		ui_interface.declare("fVslider12", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider12", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider12 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider11", "10", "");
		ui_interface.declare("fVslider11", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider11", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider11 = val; } return setval; }(this), -10, -70, 10, 0.1);
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
		ui_interface.addVerticalBargraph("0x7fe1a9312650", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a9300cf0", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a92dac20", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a92b8ad0", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a9296980", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a9274830", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a92526e0", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a9230590", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a920e440", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a91e8370", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a91c6220", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a91a40d0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a9181f80", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a915fe30", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7fe1a913cc50", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
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
		var fSlow4 = (0.001 * Math.pow(10, (0.05 * this.fVslider0)));
		var iSlow5 = this.fCheckbox1;
		var iSlow6 = this.fCheckbox2;
		var iSlow7 = (this.fEntry0 + -1);
		var iSlow8 = (iSlow7 >= 2);
		var iSlow9 = (iSlow7 >= 1);
		var fSlow10 = Math.exp((0 - (this.fConst51 / this.fVslider2)));
		var fSlow11 = (440 * (Math.pow(2, (0.0833333 * (this.fVslider1 + -49))) * (1 - fSlow10)));
		var iSlow12 = (iSlow7 >= 3);
		var fSlow13 = ((0.01 * this.fVslider3) + 1);
		var fSlow14 = ((0.01 * this.fVslider4) + 1);
		var iSlow15 = this.fCheckbox3;
		var fSlow16 = (0.001 * this.fVslider5);
		var fSlow17 = (0.001 * this.fVslider6);
		var fSlow18 = (0.001 * this.fVslider7);
		var fSlow19 = (0.001 * this.fVslider8);
		var fSlow20 = (0.001 * this.fVslider9);
		var fSlow21 = (0.001 * this.fVslider10);
		var fSlow22 = (0.001 * this.fVslider11);
		var fSlow23 = (0.001 * this.fVslider12);
		var fSlow24 = (0.001 * this.fVslider13);
		var fSlow25 = (0.001 * this.fVslider14);
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iVec0[0] = 1;
			this.fRec23[0] = (fSlow4 + (0.999 * this.fRec23[1]));
			this.fRec25[0] = (fSlow11 + (fSlow10 * this.fRec25[1]));
			var fTemp0 = max_f(20, Math.abs(this.fRec25[0]));
			this.fVec1[0] = fTemp0;
			var fTemp1 = (this.fRec24[1] + (this.fConst51 * this.fVec1[1]));
			this.fRec24[0] = (fTemp1 - Math.floor(fTemp1));
			var fTemp2 = (2 * this.fRec24[0]);
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
			var fTemp10 = max_f(20, Math.abs((fSlow13 * this.fRec25[0])));
			this.fVec8[0] = fTemp10;
			var fTemp11 = (this.fRec26[1] + (this.fConst51 * this.fVec8[1]));
			this.fRec26[0] = (fTemp11 - Math.floor(fTemp11));
			var fTemp12 = (2 * this.fRec26[0]);
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
			var fTemp20 = max_f(20, Math.abs((fSlow14 * this.fRec25[0])));
			this.fVec15[0] = fTemp20;
			var fTemp21 = (this.fRec27[1] + (this.fConst51 * this.fVec15[1]));
			this.fRec27[0] = (fTemp21 - Math.floor(fTemp21));
			var fTemp22 = (2 * this.fRec27[0]);
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
			this.iRec28[0] = ((1103515245 * this.iRec28[1]) + 12345);
			var fTemp30 = (4.65661e-10 * this.iRec28[0]);
			this.fRec29[0] = (((0.522189 * this.fRec29[3]) + (fTemp30 + (2.49496 * this.fRec29[1]))) - (2.01727 * this.fRec29[2]));
			var fTemp31 = (this.fRec23[0] * (iSlow5?input0[i]:(iSlow6?(iSlow15?(((0.049922 * this.fRec29[0]) + (0.0506127 * this.fRec29[2])) - ((0.0959935 * this.fRec29[1]) + (0.00440879 * this.fRec29[3]))):fTemp30):(0.333333 * (this.fRec23[0] * (((iSlow8?(iSlow12?(this.fConst54 * ((this.iVec0[3] * (fTemp9 - this.fVec7[1])) / fTemp0)):(this.fConst53 * ((this.iVec0[2] * (fTemp6 - this.fVec4[1])) / fTemp0))):(iSlow9?(this.fConst52 * ((this.iVec0[1] * (fTemp4 - this.fVec2[1])) / fTemp0)):fTemp3)) + (iSlow8?(iSlow12?(this.fConst54 * ((this.iVec0[3] * (fTemp19 - this.fVec14[1])) / fTemp10)):(this.fConst53 * ((this.iVec0[2] * (fTemp16 - this.fVec11[1])) / fTemp10))):(iSlow9?(this.fConst52 * ((this.iVec0[1] * (fTemp14 - this.fVec9[1])) / fTemp10)):fTemp13))) + (iSlow8?(iSlow12?(this.fConst54 * ((this.iVec0[3] * (fTemp29 - this.fVec21[1])) / fTemp20)):(this.fConst53 * ((this.iVec0[2] * (fTemp26 - this.fVec18[1])) / fTemp20))):(iSlow9?(this.fConst52 * ((this.iVec0[1] * (fTemp24 - this.fVec16[1])) / fTemp20)):fTemp23))))))));
			var fTemp32 = (iSlow3?0:fTemp31);
			this.fVec22[0] = fTemp32;
			this.fRec22[0] = ((this.fConst49 * this.fRec22[1]) + (this.fConst50 * (fTemp32 + this.fVec22[1])));
			this.fRec21[0] = (this.fRec22[0] - (this.fConst47 * ((this.fConst56 * this.fRec21[1]) + (this.fConst57 * this.fRec21[2]))));
			this.fRec20[0] = ((this.fConst47 * (this.fRec21[2] + (this.fRec21[0] + (2 * this.fRec21[1])))) - (this.fConst58 * ((this.fConst56 * this.fRec20[1]) + (this.fConst59 * this.fRec20[2]))));
			var fTemp33 = (this.fRec20[2] + (this.fRec20[0] + (2 * this.fRec20[1])));
			this.fVec23[0] = fTemp33;
			this.fRec19[0] = ((this.fConst42 * this.fRec19[1]) + (this.fConst46 * (fTemp33 + this.fVec23[1])));
			this.fRec18[0] = (this.fRec19[0] - (this.fConst40 * ((this.fConst61 * this.fRec18[1]) + (this.fConst62 * this.fRec18[2]))));
			this.fRec17[0] = ((this.fConst40 * (this.fRec18[2] + (this.fRec18[0] + (2 * this.fRec18[1])))) - (this.fConst63 * ((this.fConst61 * this.fRec17[1]) + (this.fConst64 * this.fRec17[2]))));
			var fTemp34 = (this.fRec17[2] + (this.fRec17[0] + (2 * this.fRec17[1])));
			this.fVec24[0] = fTemp34;
			this.fRec16[0] = ((this.fConst35 * this.fRec16[1]) + (this.fConst39 * (fTemp34 + this.fVec24[1])));
			this.fRec15[0] = (this.fRec16[0] - (this.fConst33 * ((this.fConst66 * this.fRec15[1]) + (this.fConst67 * this.fRec15[2]))));
			this.fRec14[0] = ((this.fConst33 * (this.fRec15[2] + (this.fRec15[0] + (2 * this.fRec15[1])))) - (this.fConst68 * ((this.fConst66 * this.fRec14[1]) + (this.fConst69 * this.fRec14[2]))));
			var fTemp35 = (this.fRec14[2] + (this.fRec14[0] + (2 * this.fRec14[1])));
			this.fVec25[0] = fTemp35;
			this.fRec13[0] = ((this.fConst28 * this.fRec13[1]) + (this.fConst32 * (fTemp35 + this.fVec25[1])));
			this.fRec12[0] = (this.fRec13[0] - (this.fConst26 * ((this.fConst71 * this.fRec12[1]) + (this.fConst72 * this.fRec12[2]))));
			this.fRec11[0] = ((this.fConst26 * (((2 * this.fRec12[1]) + this.fRec12[0]) + this.fRec12[2])) - (this.fConst73 * ((this.fConst71 * this.fRec11[1]) + (this.fConst74 * this.fRec11[2]))));
			var fTemp36 = (this.fRec11[2] + ((2 * this.fRec11[1]) + this.fRec11[0]));
			this.fVec26[0] = fTemp36;
			this.fRec10[0] = ((this.fConst25 * ((this.fConst15 * fTemp36) + (this.fConst75 * this.fVec26[1]))) + (this.fConst76 * this.fRec10[1]));
			this.fRec9[0] = (this.fRec10[0] - (this.fConst20 * ((this.fConst77 * this.fRec9[1]) + (this.fConst78 * this.fRec9[2]))));
			this.fRec8[0] = ((this.fConst20 * (((this.fConst18 * this.fRec9[0]) + (this.fConst19 * this.fRec9[1])) + (this.fConst18 * this.fRec9[2]))) - (this.fConst17 * ((this.fConst77 * this.fRec8[1]) + (this.fConst79 * this.fRec8[2]))));
			var fTemp37 = (this.fConst84 * this.fRec7[1]);
			this.fRec7[0] = ((this.fConst17 * (((this.fConst19 * this.fRec8[1]) + (this.fConst18 * this.fRec8[0])) + (this.fConst18 * this.fRec8[2]))) - (this.fConst82 * (fTemp37 + (this.fConst85 * this.fRec7[2]))));
			var fTemp38 = (this.fConst90 * this.fRec6[1]);
			this.fRec6[0] = ((this.fRec7[2] + (this.fConst82 * (fTemp37 + (this.fConst85 * this.fRec7[0])))) - (this.fConst88 * (fTemp38 + (this.fConst91 * this.fRec6[2]))));
			var fTemp39 = (this.fConst96 * this.fRec5[1]);
			this.fRec5[0] = ((this.fRec6[2] + (this.fConst88 * (fTemp38 + (this.fConst91 * this.fRec6[0])))) - (this.fConst94 * (fTemp39 + (this.fConst97 * this.fRec5[2]))));
			var fTemp40 = (this.fConst102 * this.fRec4[1]);
			this.fRec4[0] = ((this.fRec5[2] + (this.fConst94 * (fTemp39 + (this.fConst97 * this.fRec5[0])))) - (this.fConst100 * (fTemp40 + (this.fConst103 * this.fRec4[2]))));
			this.fRec30[0] = (fSlow16 + (0.999 * this.fRec30[1]));
			this.fRec39[0] = ((this.fConst76 * this.fRec39[1]) + (this.fConst25 * (fTemp36 + this.fVec26[1])));
			this.fRec38[0] = (this.fRec39[0] - (this.fConst20 * ((this.fConst77 * this.fRec38[1]) + (this.fConst78 * this.fRec38[2]))));
			this.fRec37[0] = ((this.fConst20 * (this.fRec38[2] + ((2 * this.fRec38[1]) + this.fRec38[0]))) - (this.fConst17 * ((this.fConst77 * this.fRec37[1]) + (this.fConst79 * this.fRec37[2]))));
			var fTemp41 = (this.fRec37[2] + ((2 * this.fRec37[1]) + this.fRec37[0]));
			this.fVec27[0] = fTemp41;
			this.fRec36[0] = ((this.fConst109 * this.fRec36[1]) + (this.fConst110 * ((this.fConst99 * fTemp41) + (this.fConst111 * this.fVec27[1]))));
			this.fRec35[0] = (this.fRec36[0] - (this.fConst107 * ((this.fConst102 * this.fRec35[1]) + (this.fConst112 * this.fRec35[2]))));
			this.fRec34[0] = ((this.fConst107 * (((this.fConst101 * this.fRec35[0]) + (this.fConst106 * this.fRec35[1])) + (this.fConst101 * this.fRec35[2]))) - (this.fConst105 * ((this.fConst102 * this.fRec34[1]) + (this.fConst113 * this.fRec34[2]))));
			var fTemp42 = (this.fConst84 * this.fRec33[1]);
			this.fRec33[0] = ((this.fConst105 * (((this.fConst106 * this.fRec34[1]) + (this.fConst101 * this.fRec34[0])) + (this.fConst101 * this.fRec34[2]))) - (this.fConst82 * (fTemp42 + (this.fConst85 * this.fRec33[2]))));
			var fTemp43 = (this.fConst90 * this.fRec32[1]);
			this.fRec32[0] = ((this.fRec33[2] + (this.fConst82 * (fTemp42 + (this.fConst85 * this.fRec33[0])))) - (this.fConst88 * (fTemp43 + (this.fConst91 * this.fRec32[2]))));
			var fTemp44 = (this.fConst96 * this.fRec31[1]);
			this.fRec31[0] = ((this.fRec32[2] + (this.fConst88 * (fTemp43 + (this.fConst91 * this.fRec32[0])))) - (this.fConst94 * (fTemp44 + (this.fConst97 * this.fRec31[2]))));
			this.fRec40[0] = (fSlow17 + (0.999 * this.fRec40[1]));
			this.fRec48[0] = ((this.fConst109 * this.fRec48[1]) + (this.fConst110 * (fTemp41 + this.fVec27[1])));
			this.fRec47[0] = (this.fRec48[0] - (this.fConst107 * ((this.fConst102 * this.fRec47[1]) + (this.fConst112 * this.fRec47[2]))));
			this.fRec46[0] = ((this.fConst107 * (this.fRec47[2] + ((2 * this.fRec47[1]) + this.fRec47[0]))) - (this.fConst105 * ((this.fConst102 * this.fRec46[1]) + (this.fConst113 * this.fRec46[2]))));
			var fTemp45 = (this.fRec46[2] + ((2 * this.fRec46[1]) + this.fRec46[0]));
			this.fVec28[0] = fTemp45;
			this.fRec45[0] = ((this.fConst119 * this.fRec45[1]) + (this.fConst120 * ((this.fConst93 * fTemp45) + (this.fConst121 * this.fVec28[1]))));
			this.fRec44[0] = (this.fRec45[0] - (this.fConst117 * ((this.fConst96 * this.fRec44[1]) + (this.fConst122 * this.fRec44[2]))));
			this.fRec43[0] = ((this.fConst117 * (((this.fConst95 * this.fRec44[0]) + (this.fConst116 * this.fRec44[1])) + (this.fConst95 * this.fRec44[2]))) - (this.fConst115 * ((this.fConst96 * this.fRec43[1]) + (this.fConst123 * this.fRec43[2]))));
			var fTemp46 = (this.fConst84 * this.fRec42[1]);
			this.fRec42[0] = ((this.fConst115 * (((this.fConst116 * this.fRec43[1]) + (this.fConst95 * this.fRec43[0])) + (this.fConst95 * this.fRec43[2]))) - (this.fConst82 * (fTemp46 + (this.fConst85 * this.fRec42[2]))));
			var fTemp47 = (this.fConst90 * this.fRec41[1]);
			this.fRec41[0] = ((this.fRec42[2] + (this.fConst82 * (fTemp46 + (this.fConst85 * this.fRec42[0])))) - (this.fConst88 * (fTemp47 + (this.fConst91 * this.fRec41[2]))));
			this.fRec49[0] = (fSlow18 + (0.999 * this.fRec49[1]));
			this.fRec56[0] = ((this.fConst119 * this.fRec56[1]) + (this.fConst120 * (fTemp45 + this.fVec28[1])));
			this.fRec55[0] = (this.fRec56[0] - (this.fConst117 * ((this.fConst96 * this.fRec55[1]) + (this.fConst122 * this.fRec55[2]))));
			this.fRec54[0] = ((this.fConst117 * (this.fRec55[2] + ((2 * this.fRec55[1]) + this.fRec55[0]))) - (this.fConst115 * ((this.fConst96 * this.fRec54[1]) + (this.fConst123 * this.fRec54[2]))));
			var fTemp48 = (this.fRec54[2] + ((2 * this.fRec54[1]) + this.fRec54[0]));
			this.fVec29[0] = fTemp48;
			this.fRec53[0] = ((this.fConst129 * this.fRec53[1]) + (this.fConst130 * ((this.fConst87 * fTemp48) + (this.fConst131 * this.fVec29[1]))));
			this.fRec52[0] = (this.fRec53[0] - (this.fConst127 * ((this.fConst90 * this.fRec52[1]) + (this.fConst132 * this.fRec52[2]))));
			this.fRec51[0] = ((this.fConst127 * (((this.fConst89 * this.fRec52[0]) + (this.fConst126 * this.fRec52[1])) + (this.fConst89 * this.fRec52[2]))) - (this.fConst125 * ((this.fConst90 * this.fRec51[1]) + (this.fConst133 * this.fRec51[2]))));
			var fTemp49 = (this.fConst84 * this.fRec50[1]);
			this.fRec50[0] = ((this.fConst125 * (((this.fConst126 * this.fRec51[1]) + (this.fConst89 * this.fRec51[0])) + (this.fConst89 * this.fRec51[2]))) - (this.fConst82 * (fTemp49 + (this.fConst85 * this.fRec50[2]))));
			this.fRec57[0] = (fSlow19 + (0.999 * this.fRec57[1]));
			this.fRec63[0] = ((this.fConst129 * this.fRec63[1]) + (this.fConst130 * (fTemp48 + this.fVec29[1])));
			this.fRec62[0] = (this.fRec63[0] - (this.fConst127 * ((this.fConst90 * this.fRec62[1]) + (this.fConst132 * this.fRec62[2]))));
			this.fRec61[0] = ((this.fConst127 * (this.fRec62[2] + ((2 * this.fRec62[1]) + this.fRec62[0]))) - (this.fConst125 * ((this.fConst90 * this.fRec61[1]) + (this.fConst133 * this.fRec61[2]))));
			var fTemp50 = (this.fRec61[2] + ((2 * this.fRec61[1]) + this.fRec61[0]));
			this.fVec30[0] = fTemp50;
			this.fRec60[0] = ((this.fConst138 * this.fRec60[1]) + (this.fConst139 * ((this.fConst81 * fTemp50) + (this.fConst140 * this.fVec30[1]))));
			this.fRec59[0] = (this.fRec60[0] - (this.fConst136 * ((this.fConst84 * this.fRec59[1]) + (this.fConst141 * this.fRec59[2]))));
			this.fRec58[0] = ((this.fConst136 * (((this.fConst83 * this.fRec59[0]) + (this.fConst135 * this.fRec59[1])) + (this.fConst83 * this.fRec59[2]))) - (this.fConst134 * ((this.fConst84 * this.fRec58[1]) + (this.fConst142 * this.fRec58[2]))));
			this.fRec64[0] = (fSlow20 + (0.999 * this.fRec64[1]));
			this.fRec67[0] = ((this.fConst138 * this.fRec67[1]) + (this.fConst139 * (fTemp50 + this.fVec30[1])));
			this.fRec66[0] = (this.fRec67[0] - (this.fConst136 * ((this.fConst84 * this.fRec66[1]) + (this.fConst141 * this.fRec66[2]))));
			this.fRec65[0] = ((this.fConst136 * (this.fRec66[2] + ((2 * this.fRec66[1]) + this.fRec66[0]))) - (this.fConst134 * ((this.fConst84 * this.fRec65[1]) + (this.fConst142 * this.fRec65[2]))));
			this.fRec68[0] = (fSlow21 + (0.999 * this.fRec68[1]));
			this.fRec79[0] = ((this.fConst49 * this.fRec79[1]) + (this.fConst50 * ((this.fConst44 * fTemp32) + (this.fConst144 * this.fVec22[1]))));
			this.fRec78[0] = (this.fRec79[0] - (this.fConst47 * ((this.fConst56 * this.fRec78[1]) + (this.fConst57 * this.fRec78[2]))));
			this.fRec77[0] = ((this.fConst47 * (((this.fConst143 * this.fRec78[1]) + (this.fConst55 * this.fRec78[0])) + (this.fConst55 * this.fRec78[2]))) - (this.fConst58 * ((this.fConst56 * this.fRec77[1]) + (this.fConst59 * this.fRec77[2]))));
			var fTemp51 = (this.fConst84 * this.fRec76[1]);
			this.fRec76[0] = ((this.fConst58 * (((this.fConst143 * this.fRec77[1]) + (this.fConst55 * this.fRec77[0])) + (this.fConst55 * this.fRec77[2]))) - (this.fConst82 * ((this.fConst85 * this.fRec76[2]) + fTemp51)));
			var fTemp52 = (this.fConst90 * this.fRec75[1]);
			this.fRec75[0] = ((this.fRec76[2] + (this.fConst82 * (fTemp51 + (this.fConst85 * this.fRec76[0])))) - (this.fConst88 * ((this.fConst91 * this.fRec75[2]) + fTemp52)));
			var fTemp53 = (this.fConst96 * this.fRec74[1]);
			this.fRec74[0] = ((this.fRec75[2] + (this.fConst88 * (fTemp52 + (this.fConst91 * this.fRec75[0])))) - (this.fConst94 * ((this.fConst97 * this.fRec74[2]) + fTemp53)));
			var fTemp54 = (this.fConst102 * this.fRec73[1]);
			this.fRec73[0] = ((this.fRec74[2] + (this.fConst94 * (fTemp53 + (this.fConst97 * this.fRec74[0])))) - (this.fConst100 * ((this.fConst103 * this.fRec73[2]) + fTemp54)));
			var fTemp55 = (this.fConst77 * this.fRec72[1]);
			this.fRec72[0] = ((this.fRec73[2] + (this.fConst100 * (fTemp54 + (this.fConst103 * this.fRec73[0])))) - (this.fConst145 * ((this.fConst146 * this.fRec72[2]) + fTemp55)));
			var fTemp56 = (this.fConst71 * this.fRec71[1]);
			this.fRec71[0] = ((this.fRec72[2] + (this.fConst145 * (fTemp55 + (this.fConst146 * this.fRec72[0])))) - (this.fConst147 * ((this.fConst148 * this.fRec71[2]) + fTemp56)));
			var fTemp57 = (this.fConst66 * this.fRec70[1]);
			this.fRec70[0] = ((this.fRec71[2] + (this.fConst147 * (fTemp56 + (this.fConst148 * this.fRec71[0])))) - (this.fConst149 * ((this.fConst150 * this.fRec70[2]) + fTemp57)));
			var fTemp58 = (this.fConst61 * this.fRec69[1]);
			this.fRec69[0] = ((this.fRec70[2] + (this.fConst149 * (fTemp57 + (this.fConst150 * this.fRec70[0])))) - (this.fConst151 * ((this.fConst152 * this.fRec69[2]) + fTemp58)));
			this.fRec80[0] = (fSlow22 + (0.999 * this.fRec80[1]));
			this.fRec90[0] = ((this.fConst42 * this.fRec90[1]) + (this.fConst46 * ((this.fConst37 * fTemp33) + (this.fConst154 * this.fVec23[1]))));
			this.fRec89[0] = (this.fRec90[0] - (this.fConst40 * ((this.fConst61 * this.fRec89[1]) + (this.fConst62 * this.fRec89[2]))));
			this.fRec88[0] = ((this.fConst40 * (((this.fConst60 * this.fRec89[0]) + (this.fConst153 * this.fRec89[1])) + (this.fConst60 * this.fRec89[2]))) - (this.fConst63 * ((this.fConst61 * this.fRec88[1]) + (this.fConst64 * this.fRec88[2]))));
			var fTemp59 = (this.fConst84 * this.fRec87[1]);
			this.fRec87[0] = ((this.fConst63 * (((this.fConst153 * this.fRec88[1]) + (this.fConst60 * this.fRec88[0])) + (this.fConst60 * this.fRec88[2]))) - (this.fConst82 * (fTemp59 + (this.fConst85 * this.fRec87[2]))));
			var fTemp60 = (this.fConst90 * this.fRec86[1]);
			this.fRec86[0] = ((this.fRec87[2] + (this.fConst82 * (fTemp59 + (this.fConst85 * this.fRec87[0])))) - (this.fConst88 * (fTemp60 + (this.fConst91 * this.fRec86[2]))));
			var fTemp61 = (this.fConst96 * this.fRec85[1]);
			this.fRec85[0] = ((this.fRec86[2] + (this.fConst88 * (fTemp60 + (this.fConst91 * this.fRec86[0])))) - (this.fConst94 * (fTemp61 + (this.fConst97 * this.fRec85[2]))));
			var fTemp62 = (this.fConst102 * this.fRec84[1]);
			this.fRec84[0] = ((this.fRec85[2] + (this.fConst94 * (fTemp61 + (this.fConst97 * this.fRec85[0])))) - (this.fConst100 * (fTemp62 + (this.fConst103 * this.fRec84[2]))));
			var fTemp63 = (this.fConst77 * this.fRec83[1]);
			this.fRec83[0] = ((this.fRec84[2] + (this.fConst100 * (fTemp62 + (this.fConst103 * this.fRec84[0])))) - (this.fConst145 * (fTemp63 + (this.fConst146 * this.fRec83[2]))));
			var fTemp64 = (this.fConst71 * this.fRec82[1]);
			this.fRec82[0] = ((this.fRec83[2] + (this.fConst145 * (fTemp63 + (this.fConst146 * this.fRec83[0])))) - (this.fConst147 * (fTemp64 + (this.fConst148 * this.fRec82[2]))));
			var fTemp65 = (this.fConst66 * this.fRec81[1]);
			this.fRec81[0] = ((this.fRec82[2] + (this.fConst147 * (fTemp64 + (this.fConst148 * this.fRec82[0])))) - (this.fConst149 * (fTemp65 + (this.fConst150 * this.fRec81[2]))));
			this.fRec91[0] = (fSlow23 + (0.999 * this.fRec91[1]));
			this.fRec100[0] = ((this.fConst35 * this.fRec100[1]) + (this.fConst39 * ((this.fConst30 * fTemp34) + (this.fConst156 * this.fVec24[1]))));
			this.fRec99[0] = (this.fRec100[0] - (this.fConst33 * ((this.fConst66 * this.fRec99[1]) + (this.fConst67 * this.fRec99[2]))));
			this.fRec98[0] = ((this.fConst33 * (((this.fConst65 * this.fRec99[0]) + (this.fConst155 * this.fRec99[1])) + (this.fConst65 * this.fRec99[2]))) - (this.fConst68 * ((this.fConst66 * this.fRec98[1]) + (this.fConst69 * this.fRec98[2]))));
			var fTemp66 = (this.fConst84 * this.fRec97[1]);
			this.fRec97[0] = ((this.fConst68 * (((this.fConst155 * this.fRec98[1]) + (this.fConst65 * this.fRec98[0])) + (this.fConst65 * this.fRec98[2]))) - (this.fConst82 * (fTemp66 + (this.fConst85 * this.fRec97[2]))));
			var fTemp67 = (this.fConst90 * this.fRec96[1]);
			this.fRec96[0] = ((this.fRec97[2] + (this.fConst82 * (fTemp66 + (this.fConst85 * this.fRec97[0])))) - (this.fConst88 * (fTemp67 + (this.fConst91 * this.fRec96[2]))));
			var fTemp68 = (this.fConst96 * this.fRec95[1]);
			this.fRec95[0] = ((this.fRec96[2] + (this.fConst88 * (fTemp67 + (this.fConst91 * this.fRec96[0])))) - (this.fConst94 * (fTemp68 + (this.fConst97 * this.fRec95[2]))));
			var fTemp69 = (this.fConst102 * this.fRec94[1]);
			this.fRec94[0] = ((this.fRec95[2] + (this.fConst94 * (fTemp68 + (this.fConst97 * this.fRec95[0])))) - (this.fConst100 * (fTemp69 + (this.fConst103 * this.fRec94[2]))));
			var fTemp70 = (this.fConst77 * this.fRec93[1]);
			this.fRec93[0] = ((this.fRec94[2] + (this.fConst100 * (fTemp69 + (this.fConst103 * this.fRec94[0])))) - (this.fConst145 * (fTemp70 + (this.fConst146 * this.fRec93[2]))));
			var fTemp71 = (this.fConst71 * this.fRec92[1]);
			this.fRec92[0] = ((this.fRec93[2] + (this.fConst145 * (fTemp70 + (this.fConst146 * this.fRec93[0])))) - (this.fConst147 * (fTemp71 + (this.fConst148 * this.fRec92[2]))));
			this.fRec101[0] = (fSlow24 + (0.999 * this.fRec101[1]));
			this.fRec109[0] = ((this.fConst28 * this.fRec109[1]) + (this.fConst32 * ((this.fConst22 * fTemp35) + (this.fConst158 * this.fVec25[1]))));
			this.fRec108[0] = (this.fRec109[0] - (this.fConst26 * ((this.fConst71 * this.fRec108[1]) + (this.fConst72 * this.fRec108[2]))));
			this.fRec107[0] = ((this.fConst26 * (((this.fConst70 * this.fRec108[0]) + (this.fConst157 * this.fRec108[1])) + (this.fConst70 * this.fRec108[2]))) - (this.fConst73 * ((this.fConst71 * this.fRec107[1]) + (this.fConst74 * this.fRec107[2]))));
			var fTemp72 = (this.fConst84 * this.fRec106[1]);
			this.fRec106[0] = ((this.fConst73 * (((this.fConst157 * this.fRec107[1]) + (this.fConst70 * this.fRec107[0])) + (this.fConst70 * this.fRec107[2]))) - (this.fConst82 * (fTemp72 + (this.fConst85 * this.fRec106[2]))));
			var fTemp73 = (this.fConst90 * this.fRec105[1]);
			this.fRec105[0] = ((this.fRec106[2] + (this.fConst82 * (fTemp72 + (this.fConst85 * this.fRec106[0])))) - (this.fConst88 * (fTemp73 + (this.fConst91 * this.fRec105[2]))));
			var fTemp74 = (this.fConst96 * this.fRec104[1]);
			this.fRec104[0] = ((this.fRec105[2] + (this.fConst88 * (fTemp73 + (this.fConst91 * this.fRec105[0])))) - (this.fConst94 * (fTemp74 + (this.fConst97 * this.fRec104[2]))));
			var fTemp75 = (this.fConst102 * this.fRec103[1]);
			this.fRec103[0] = ((this.fRec104[2] + (this.fConst94 * (fTemp74 + (this.fConst97 * this.fRec104[0])))) - (this.fConst100 * (fTemp75 + (this.fConst103 * this.fRec103[2]))));
			var fTemp76 = (this.fConst77 * this.fRec102[1]);
			this.fRec102[0] = ((this.fRec103[2] + (this.fConst100 * (fTemp75 + (this.fConst103 * this.fRec103[0])))) - (this.fConst145 * (fTemp76 + (this.fConst146 * this.fRec102[2]))));
			this.fRec110[0] = (fSlow25 + (0.999 * this.fRec110[1]));
			var fTemp77 = (iSlow3?fTemp31:((((((((((this.fRec4[2] + (this.fConst100 * (fTemp40 + (this.fConst103 * this.fRec4[0])))) * Math.pow(10, (0.05 * this.fRec30[0]))) + ((this.fRec31[2] + (this.fConst94 * (fTemp44 + (this.fConst97 * this.fRec31[0])))) * Math.pow(10, (0.05 * this.fRec40[0])))) + ((this.fRec41[2] + (this.fConst88 * (fTemp47 + (this.fConst91 * this.fRec41[0])))) * Math.pow(10, (0.05 * this.fRec49[0])))) + ((this.fRec50[2] + (this.fConst82 * (fTemp49 + (this.fConst85 * this.fRec50[0])))) * Math.pow(10, (0.05 * this.fRec57[0])))) + (this.fConst134 * (((((this.fConst135 * this.fRec58[1]) + (this.fConst83 * this.fRec58[0])) + (this.fConst83 * this.fRec58[2])) * Math.pow(10, (0.05 * this.fRec64[0]))) + ((this.fRec65[2] + ((2 * this.fRec65[1]) + this.fRec65[0])) * Math.pow(10, (0.05 * this.fRec68[0])))))) + ((this.fRec69[2] + (this.fConst151 * (fTemp58 + (this.fConst152 * this.fRec69[0])))) * Math.pow(10, (0.05 * this.fRec80[0])))) + ((this.fRec81[2] + (this.fConst149 * (fTemp65 + (this.fConst150 * this.fRec81[0])))) * Math.pow(10, (0.05 * this.fRec91[0])))) + ((this.fRec92[2] + (this.fConst147 * (fTemp71 + (this.fConst148 * this.fRec92[0])))) * Math.pow(10, (0.05 * this.fRec101[0])))) + ((this.fRec102[2] + (this.fConst145 * (fTemp76 + (this.fConst146 * this.fRec102[0])))) * Math.pow(10, (0.05 * this.fRec110[0])))));
			this.fRec3[0] = (fTemp77 - (this.fConst11 * ((this.fConst159 * this.fRec3[2]) + (this.fConst161 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[1]) + (this.fConst162 * this.fRec3[0])) + (this.fConst162 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst163 * this.fRec2[2]) + (this.fConst164 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst165 * this.fRec2[0])) + (this.fConst165 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst166 * this.fRec1[2]) + (this.fConst167 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst168 * this.fRec1[0])) + (this.fConst168 * this.fRec1[2]))))));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec117[0] = (fTemp77 - (this.fConst185 * ((this.fConst188 * this.fRec117[2]) + (this.fConst189 * this.fRec117[1]))));
			this.fRec116[0] = ((this.fConst185 * (((this.fConst187 * this.fRec117[1]) + (this.fConst190 * this.fRec117[0])) + (this.fConst190 * this.fRec117[2]))) - (this.fConst183 * ((this.fConst191 * this.fRec116[2]) + (this.fConst192 * this.fRec116[1]))));
			this.fRec115[0] = ((this.fConst183 * (((this.fConst184 * this.fRec116[1]) + (this.fConst193 * this.fRec116[0])) + (this.fConst193 * this.fRec116[2]))) - (this.fConst181 * ((this.fConst194 * this.fRec115[2]) + (this.fConst195 * this.fRec115[1]))));
			var fTemp78 = (this.fConst181 * (((this.fConst182 * this.fRec115[1]) + (this.fConst196 * this.fRec115[0])) + (this.fConst196 * this.fRec115[2])));
			this.fRec114[0] = (fTemp78 - (this.fConst178 * ((this.fConst197 * this.fRec114[2]) + (this.fConst199 * this.fRec114[1]))));
			this.fRec113[0] = ((this.fConst178 * (((this.fConst180 * this.fRec114[1]) + (this.fConst200 * this.fRec114[0])) + (this.fConst200 * this.fRec114[2]))) - (this.fConst175 * ((this.fConst201 * this.fRec113[2]) + (this.fConst202 * this.fRec113[1]))));
			this.fRec112[0] = ((this.fConst175 * (((this.fConst177 * this.fRec113[1]) + (this.fConst203 * this.fRec113[0])) + (this.fConst203 * this.fRec113[2]))) - (this.fConst171 * ((this.fConst204 * this.fRec112[2]) + (this.fConst205 * this.fRec112[1]))));
			this.fRec111[0] = ((fSlow1 * this.fRec111[1]) + (fSlow2 * Math.abs((this.fConst171 * (((this.fConst174 * this.fRec112[1]) + (this.fConst206 * this.fRec112[0])) + (this.fConst206 * this.fRec112[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec111[0]))));
			this.fRec124[0] = (fTemp78 - (this.fConst223 * ((this.fConst226 * this.fRec124[2]) + (this.fConst227 * this.fRec124[1]))));
			this.fRec123[0] = ((this.fConst223 * (((this.fConst225 * this.fRec124[1]) + (this.fConst228 * this.fRec124[0])) + (this.fConst228 * this.fRec124[2]))) - (this.fConst221 * ((this.fConst229 * this.fRec123[2]) + (this.fConst230 * this.fRec123[1]))));
			this.fRec122[0] = ((this.fConst221 * (((this.fConst222 * this.fRec123[1]) + (this.fConst231 * this.fRec123[0])) + (this.fConst231 * this.fRec123[2]))) - (this.fConst219 * ((this.fConst232 * this.fRec122[2]) + (this.fConst233 * this.fRec122[1]))));
			var fTemp79 = (this.fConst219 * (((this.fConst220 * this.fRec122[1]) + (this.fConst234 * this.fRec122[0])) + (this.fConst234 * this.fRec122[2])));
			this.fRec121[0] = (fTemp79 - (this.fConst216 * ((this.fConst235 * this.fRec121[2]) + (this.fConst237 * this.fRec121[1]))));
			this.fRec120[0] = ((this.fConst216 * (((this.fConst218 * this.fRec121[1]) + (this.fConst238 * this.fRec121[0])) + (this.fConst238 * this.fRec121[2]))) - (this.fConst213 * ((this.fConst239 * this.fRec120[2]) + (this.fConst240 * this.fRec120[1]))));
			this.fRec119[0] = ((this.fConst213 * (((this.fConst215 * this.fRec120[1]) + (this.fConst241 * this.fRec120[0])) + (this.fConst241 * this.fRec120[2]))) - (this.fConst209 * ((this.fConst242 * this.fRec119[2]) + (this.fConst243 * this.fRec119[1]))));
			this.fRec118[0] = ((fSlow1 * this.fRec118[1]) + (fSlow2 * Math.abs((this.fConst209 * (((this.fConst212 * this.fRec119[1]) + (this.fConst244 * this.fRec119[0])) + (this.fConst244 * this.fRec119[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec118[0]))));
			this.fRec131[0] = (fTemp79 - (this.fConst261 * ((this.fConst264 * this.fRec131[2]) + (this.fConst265 * this.fRec131[1]))));
			this.fRec130[0] = ((this.fConst261 * (((this.fConst263 * this.fRec131[1]) + (this.fConst266 * this.fRec131[0])) + (this.fConst266 * this.fRec131[2]))) - (this.fConst259 * ((this.fConst267 * this.fRec130[2]) + (this.fConst268 * this.fRec130[1]))));
			this.fRec129[0] = ((this.fConst259 * (((this.fConst260 * this.fRec130[1]) + (this.fConst269 * this.fRec130[0])) + (this.fConst269 * this.fRec130[2]))) - (this.fConst257 * ((this.fConst270 * this.fRec129[2]) + (this.fConst271 * this.fRec129[1]))));
			var fTemp80 = (this.fConst257 * (((this.fConst258 * this.fRec129[1]) + (this.fConst272 * this.fRec129[0])) + (this.fConst272 * this.fRec129[2])));
			this.fRec128[0] = (fTemp80 - (this.fConst254 * ((this.fConst273 * this.fRec128[2]) + (this.fConst275 * this.fRec128[1]))));
			this.fRec127[0] = ((this.fConst254 * (((this.fConst256 * this.fRec128[1]) + (this.fConst276 * this.fRec128[0])) + (this.fConst276 * this.fRec128[2]))) - (this.fConst251 * ((this.fConst277 * this.fRec127[2]) + (this.fConst278 * this.fRec127[1]))));
			this.fRec126[0] = ((this.fConst251 * (((this.fConst253 * this.fRec127[1]) + (this.fConst279 * this.fRec127[0])) + (this.fConst279 * this.fRec127[2]))) - (this.fConst247 * ((this.fConst280 * this.fRec126[2]) + (this.fConst281 * this.fRec126[1]))));
			this.fRec125[0] = ((fSlow1 * this.fRec125[1]) + (fSlow2 * Math.abs((this.fConst247 * (((this.fConst250 * this.fRec126[1]) + (this.fConst282 * this.fRec126[0])) + (this.fConst282 * this.fRec126[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec125[0]))));
			this.fRec138[0] = (fTemp80 - (this.fConst299 * ((this.fConst302 * this.fRec138[2]) + (this.fConst303 * this.fRec138[1]))));
			this.fRec137[0] = ((this.fConst299 * (((this.fConst301 * this.fRec138[1]) + (this.fConst304 * this.fRec138[0])) + (this.fConst304 * this.fRec138[2]))) - (this.fConst297 * ((this.fConst305 * this.fRec137[2]) + (this.fConst306 * this.fRec137[1]))));
			this.fRec136[0] = ((this.fConst297 * (((this.fConst298 * this.fRec137[1]) + (this.fConst307 * this.fRec137[0])) + (this.fConst307 * this.fRec137[2]))) - (this.fConst295 * ((this.fConst308 * this.fRec136[2]) + (this.fConst309 * this.fRec136[1]))));
			var fTemp81 = (this.fConst295 * (((this.fConst296 * this.fRec136[1]) + (this.fConst310 * this.fRec136[0])) + (this.fConst310 * this.fRec136[2])));
			this.fRec135[0] = (fTemp81 - (this.fConst292 * ((this.fConst311 * this.fRec135[2]) + (this.fConst313 * this.fRec135[1]))));
			this.fRec134[0] = ((this.fConst292 * (((this.fConst294 * this.fRec135[1]) + (this.fConst314 * this.fRec135[0])) + (this.fConst314 * this.fRec135[2]))) - (this.fConst289 * ((this.fConst315 * this.fRec134[2]) + (this.fConst316 * this.fRec134[1]))));
			this.fRec133[0] = ((this.fConst289 * (((this.fConst291 * this.fRec134[1]) + (this.fConst317 * this.fRec134[0])) + (this.fConst317 * this.fRec134[2]))) - (this.fConst285 * ((this.fConst318 * this.fRec133[2]) + (this.fConst319 * this.fRec133[1]))));
			this.fRec132[0] = ((fSlow1 * this.fRec132[1]) + (fSlow2 * Math.abs((this.fConst285 * (((this.fConst288 * this.fRec133[1]) + (this.fConst320 * this.fRec133[0])) + (this.fConst320 * this.fRec133[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec132[0]))));
			this.fRec145[0] = (fTemp81 - (this.fConst337 * ((this.fConst340 * this.fRec145[2]) + (this.fConst341 * this.fRec145[1]))));
			this.fRec144[0] = ((this.fConst337 * (((this.fConst339 * this.fRec145[1]) + (this.fConst342 * this.fRec145[0])) + (this.fConst342 * this.fRec145[2]))) - (this.fConst335 * ((this.fConst343 * this.fRec144[2]) + (this.fConst344 * this.fRec144[1]))));
			this.fRec143[0] = ((this.fConst335 * (((this.fConst336 * this.fRec144[1]) + (this.fConst345 * this.fRec144[0])) + (this.fConst345 * this.fRec144[2]))) - (this.fConst333 * ((this.fConst346 * this.fRec143[2]) + (this.fConst347 * this.fRec143[1]))));
			var fTemp82 = (this.fConst333 * (((this.fConst334 * this.fRec143[1]) + (this.fConst348 * this.fRec143[0])) + (this.fConst348 * this.fRec143[2])));
			this.fRec142[0] = (fTemp82 - (this.fConst330 * ((this.fConst349 * this.fRec142[2]) + (this.fConst351 * this.fRec142[1]))));
			this.fRec141[0] = ((this.fConst330 * (((this.fConst332 * this.fRec142[1]) + (this.fConst352 * this.fRec142[0])) + (this.fConst352 * this.fRec142[2]))) - (this.fConst327 * ((this.fConst353 * this.fRec141[2]) + (this.fConst354 * this.fRec141[1]))));
			this.fRec140[0] = ((this.fConst327 * (((this.fConst329 * this.fRec141[1]) + (this.fConst355 * this.fRec141[0])) + (this.fConst355 * this.fRec141[2]))) - (this.fConst323 * ((this.fConst356 * this.fRec140[2]) + (this.fConst357 * this.fRec140[1]))));
			this.fRec139[0] = ((fSlow1 * this.fRec139[1]) + (fSlow2 * Math.abs((this.fConst323 * (((this.fConst326 * this.fRec140[1]) + (this.fConst358 * this.fRec140[0])) + (this.fConst358 * this.fRec140[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec139[0]))));
			this.fRec152[0] = (fTemp82 - (this.fConst375 * ((this.fConst378 * this.fRec152[2]) + (this.fConst379 * this.fRec152[1]))));
			this.fRec151[0] = ((this.fConst375 * (((this.fConst377 * this.fRec152[1]) + (this.fConst380 * this.fRec152[0])) + (this.fConst380 * this.fRec152[2]))) - (this.fConst373 * ((this.fConst381 * this.fRec151[2]) + (this.fConst382 * this.fRec151[1]))));
			this.fRec150[0] = ((this.fConst373 * (((this.fConst374 * this.fRec151[1]) + (this.fConst383 * this.fRec151[0])) + (this.fConst383 * this.fRec151[2]))) - (this.fConst371 * ((this.fConst384 * this.fRec150[2]) + (this.fConst385 * this.fRec150[1]))));
			var fTemp83 = (this.fConst371 * (((this.fConst372 * this.fRec150[1]) + (this.fConst386 * this.fRec150[0])) + (this.fConst386 * this.fRec150[2])));
			this.fRec149[0] = (fTemp83 - (this.fConst368 * ((this.fConst387 * this.fRec149[2]) + (this.fConst389 * this.fRec149[1]))));
			this.fRec148[0] = ((this.fConst368 * (((this.fConst370 * this.fRec149[1]) + (this.fConst390 * this.fRec149[0])) + (this.fConst390 * this.fRec149[2]))) - (this.fConst365 * ((this.fConst391 * this.fRec148[2]) + (this.fConst392 * this.fRec148[1]))));
			this.fRec147[0] = ((this.fConst365 * (((this.fConst367 * this.fRec148[1]) + (this.fConst393 * this.fRec148[0])) + (this.fConst393 * this.fRec148[2]))) - (this.fConst361 * ((this.fConst394 * this.fRec147[2]) + (this.fConst395 * this.fRec147[1]))));
			this.fRec146[0] = ((fSlow1 * this.fRec146[1]) + (fSlow2 * Math.abs((this.fConst361 * (((this.fConst364 * this.fRec147[1]) + (this.fConst396 * this.fRec147[0])) + (this.fConst396 * this.fRec147[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec146[0]))));
			this.fRec159[0] = (fTemp83 - (this.fConst413 * ((this.fConst416 * this.fRec159[2]) + (this.fConst417 * this.fRec159[1]))));
			this.fRec158[0] = ((this.fConst413 * (((this.fConst415 * this.fRec159[1]) + (this.fConst418 * this.fRec159[0])) + (this.fConst418 * this.fRec159[2]))) - (this.fConst411 * ((this.fConst419 * this.fRec158[2]) + (this.fConst420 * this.fRec158[1]))));
			this.fRec157[0] = ((this.fConst411 * (((this.fConst412 * this.fRec158[1]) + (this.fConst421 * this.fRec158[0])) + (this.fConst421 * this.fRec158[2]))) - (this.fConst409 * ((this.fConst422 * this.fRec157[2]) + (this.fConst423 * this.fRec157[1]))));
			var fTemp84 = (this.fConst409 * (((this.fConst410 * this.fRec157[1]) + (this.fConst424 * this.fRec157[0])) + (this.fConst424 * this.fRec157[2])));
			this.fRec156[0] = (fTemp84 - (this.fConst406 * ((this.fConst425 * this.fRec156[2]) + (this.fConst427 * this.fRec156[1]))));
			this.fRec155[0] = ((this.fConst406 * (((this.fConst408 * this.fRec156[1]) + (this.fConst428 * this.fRec156[0])) + (this.fConst428 * this.fRec156[2]))) - (this.fConst403 * ((this.fConst429 * this.fRec155[2]) + (this.fConst430 * this.fRec155[1]))));
			this.fRec154[0] = ((this.fConst403 * (((this.fConst405 * this.fRec155[1]) + (this.fConst431 * this.fRec155[0])) + (this.fConst431 * this.fRec155[2]))) - (this.fConst399 * ((this.fConst432 * this.fRec154[2]) + (this.fConst433 * this.fRec154[1]))));
			this.fRec153[0] = ((fSlow1 * this.fRec153[1]) + (fSlow2 * Math.abs((this.fConst399 * (((this.fConst402 * this.fRec154[1]) + (this.fConst434 * this.fRec154[0])) + (this.fConst434 * this.fRec154[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec153[0]))));
			this.fRec166[0] = (fTemp84 - (this.fConst451 * ((this.fConst454 * this.fRec166[2]) + (this.fConst455 * this.fRec166[1]))));
			this.fRec165[0] = ((this.fConst451 * (((this.fConst453 * this.fRec166[1]) + (this.fConst456 * this.fRec166[0])) + (this.fConst456 * this.fRec166[2]))) - (this.fConst449 * ((this.fConst457 * this.fRec165[2]) + (this.fConst458 * this.fRec165[1]))));
			this.fRec164[0] = ((this.fConst449 * (((this.fConst450 * this.fRec165[1]) + (this.fConst459 * this.fRec165[0])) + (this.fConst459 * this.fRec165[2]))) - (this.fConst447 * ((this.fConst460 * this.fRec164[2]) + (this.fConst461 * this.fRec164[1]))));
			var fTemp85 = (this.fConst447 * (((this.fConst448 * this.fRec164[1]) + (this.fConst462 * this.fRec164[0])) + (this.fConst462 * this.fRec164[2])));
			this.fRec163[0] = (fTemp85 - (this.fConst444 * ((this.fConst463 * this.fRec163[2]) + (this.fConst465 * this.fRec163[1]))));
			this.fRec162[0] = ((this.fConst444 * (((this.fConst446 * this.fRec163[1]) + (this.fConst466 * this.fRec163[0])) + (this.fConst466 * this.fRec163[2]))) - (this.fConst441 * ((this.fConst467 * this.fRec162[2]) + (this.fConst468 * this.fRec162[1]))));
			this.fRec161[0] = ((this.fConst441 * (((this.fConst443 * this.fRec162[1]) + (this.fConst469 * this.fRec162[0])) + (this.fConst469 * this.fRec162[2]))) - (this.fConst437 * ((this.fConst470 * this.fRec161[2]) + (this.fConst471 * this.fRec161[1]))));
			this.fRec160[0] = ((fSlow1 * this.fRec160[1]) + (fSlow2 * Math.abs((this.fConst437 * (((this.fConst440 * this.fRec161[1]) + (this.fConst472 * this.fRec161[0])) + (this.fConst472 * this.fRec161[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec160[0]))));
			this.fRec173[0] = (fTemp85 - (this.fConst489 * ((this.fConst492 * this.fRec173[2]) + (this.fConst493 * this.fRec173[1]))));
			this.fRec172[0] = ((this.fConst489 * (((this.fConst491 * this.fRec173[1]) + (this.fConst494 * this.fRec173[0])) + (this.fConst494 * this.fRec173[2]))) - (this.fConst487 * ((this.fConst495 * this.fRec172[2]) + (this.fConst496 * this.fRec172[1]))));
			this.fRec171[0] = ((this.fConst487 * (((this.fConst488 * this.fRec172[1]) + (this.fConst497 * this.fRec172[0])) + (this.fConst497 * this.fRec172[2]))) - (this.fConst485 * ((this.fConst498 * this.fRec171[2]) + (this.fConst499 * this.fRec171[1]))));
			var fTemp86 = (this.fConst485 * (((this.fConst486 * this.fRec171[1]) + (this.fConst500 * this.fRec171[0])) + (this.fConst500 * this.fRec171[2])));
			this.fRec170[0] = (fTemp86 - (this.fConst482 * ((this.fConst501 * this.fRec170[2]) + (this.fConst503 * this.fRec170[1]))));
			this.fRec169[0] = ((this.fConst482 * (((this.fConst484 * this.fRec170[1]) + (this.fConst504 * this.fRec170[0])) + (this.fConst504 * this.fRec170[2]))) - (this.fConst479 * ((this.fConst505 * this.fRec169[2]) + (this.fConst506 * this.fRec169[1]))));
			this.fRec168[0] = ((this.fConst479 * (((this.fConst481 * this.fRec169[1]) + (this.fConst507 * this.fRec169[0])) + (this.fConst507 * this.fRec169[2]))) - (this.fConst475 * ((this.fConst508 * this.fRec168[2]) + (this.fConst509 * this.fRec168[1]))));
			this.fRec167[0] = ((fSlow1 * this.fRec167[1]) + (fSlow2 * Math.abs((this.fConst475 * (((this.fConst478 * this.fRec168[1]) + (this.fConst510 * this.fRec168[0])) + (this.fConst510 * this.fRec168[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec167[0]))));
			this.fRec180[0] = (fTemp86 - (this.fConst527 * ((this.fConst530 * this.fRec180[2]) + (this.fConst531 * this.fRec180[1]))));
			this.fRec179[0] = ((this.fConst527 * (((this.fConst529 * this.fRec180[1]) + (this.fConst532 * this.fRec180[0])) + (this.fConst532 * this.fRec180[2]))) - (this.fConst525 * ((this.fConst533 * this.fRec179[2]) + (this.fConst534 * this.fRec179[1]))));
			this.fRec178[0] = ((this.fConst525 * (((this.fConst526 * this.fRec179[1]) + (this.fConst535 * this.fRec179[0])) + (this.fConst535 * this.fRec179[2]))) - (this.fConst523 * ((this.fConst536 * this.fRec178[2]) + (this.fConst537 * this.fRec178[1]))));
			var fTemp87 = (this.fConst523 * (((this.fConst524 * this.fRec178[1]) + (this.fConst538 * this.fRec178[0])) + (this.fConst538 * this.fRec178[2])));
			this.fRec177[0] = (fTemp87 - (this.fConst520 * ((this.fConst539 * this.fRec177[2]) + (this.fConst541 * this.fRec177[1]))));
			this.fRec176[0] = ((this.fConst520 * (((this.fConst522 * this.fRec177[1]) + (this.fConst542 * this.fRec177[0])) + (this.fConst542 * this.fRec177[2]))) - (this.fConst517 * ((this.fConst543 * this.fRec176[2]) + (this.fConst544 * this.fRec176[1]))));
			this.fRec175[0] = ((this.fConst517 * (((this.fConst519 * this.fRec176[1]) + (this.fConst545 * this.fRec176[0])) + (this.fConst545 * this.fRec176[2]))) - (this.fConst513 * ((this.fConst546 * this.fRec175[2]) + (this.fConst547 * this.fRec175[1]))));
			this.fRec174[0] = ((fSlow1 * this.fRec174[1]) + (fSlow2 * Math.abs((this.fConst513 * (((this.fConst516 * this.fRec175[1]) + (this.fConst548 * this.fRec175[0])) + (this.fConst548 * this.fRec175[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec174[0]))));
			this.fRec187[0] = (fTemp87 - (this.fConst565 * ((this.fConst568 * this.fRec187[2]) + (this.fConst569 * this.fRec187[1]))));
			this.fRec186[0] = ((this.fConst565 * (((this.fConst567 * this.fRec187[1]) + (this.fConst570 * this.fRec187[0])) + (this.fConst570 * this.fRec187[2]))) - (this.fConst563 * ((this.fConst571 * this.fRec186[2]) + (this.fConst572 * this.fRec186[1]))));
			this.fRec185[0] = ((this.fConst563 * (((this.fConst564 * this.fRec186[1]) + (this.fConst573 * this.fRec186[0])) + (this.fConst573 * this.fRec186[2]))) - (this.fConst561 * ((this.fConst574 * this.fRec185[2]) + (this.fConst575 * this.fRec185[1]))));
			var fTemp88 = (this.fConst561 * (((this.fConst562 * this.fRec185[1]) + (this.fConst576 * this.fRec185[0])) + (this.fConst576 * this.fRec185[2])));
			this.fRec184[0] = (fTemp88 - (this.fConst558 * ((this.fConst577 * this.fRec184[2]) + (this.fConst579 * this.fRec184[1]))));
			this.fRec183[0] = ((this.fConst558 * (((this.fConst560 * this.fRec184[1]) + (this.fConst580 * this.fRec184[0])) + (this.fConst580 * this.fRec184[2]))) - (this.fConst555 * ((this.fConst581 * this.fRec183[2]) + (this.fConst582 * this.fRec183[1]))));
			this.fRec182[0] = ((this.fConst555 * (((this.fConst557 * this.fRec183[1]) + (this.fConst583 * this.fRec183[0])) + (this.fConst583 * this.fRec183[2]))) - (this.fConst551 * ((this.fConst584 * this.fRec182[2]) + (this.fConst585 * this.fRec182[1]))));
			this.fRec181[0] = ((fSlow1 * this.fRec181[1]) + (fSlow2 * Math.abs((this.fConst551 * (((this.fConst554 * this.fRec182[1]) + (this.fConst586 * this.fRec182[0])) + (this.fConst586 * this.fRec182[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec181[0]))));
			this.fRec194[0] = (fTemp88 - (this.fConst603 * ((this.fConst606 * this.fRec194[2]) + (this.fConst607 * this.fRec194[1]))));
			this.fRec193[0] = ((this.fConst603 * (((this.fConst605 * this.fRec194[1]) + (this.fConst608 * this.fRec194[0])) + (this.fConst608 * this.fRec194[2]))) - (this.fConst601 * ((this.fConst609 * this.fRec193[2]) + (this.fConst610 * this.fRec193[1]))));
			this.fRec192[0] = ((this.fConst601 * (((this.fConst602 * this.fRec193[1]) + (this.fConst611 * this.fRec193[0])) + (this.fConst611 * this.fRec193[2]))) - (this.fConst599 * ((this.fConst612 * this.fRec192[2]) + (this.fConst613 * this.fRec192[1]))));
			var fTemp89 = (this.fConst599 * (((this.fConst600 * this.fRec192[1]) + (this.fConst614 * this.fRec192[0])) + (this.fConst614 * this.fRec192[2])));
			this.fRec191[0] = (fTemp89 - (this.fConst596 * ((this.fConst615 * this.fRec191[2]) + (this.fConst617 * this.fRec191[1]))));
			this.fRec190[0] = ((this.fConst596 * (((this.fConst598 * this.fRec191[1]) + (this.fConst618 * this.fRec191[0])) + (this.fConst618 * this.fRec191[2]))) - (this.fConst593 * ((this.fConst619 * this.fRec190[2]) + (this.fConst620 * this.fRec190[1]))));
			this.fRec189[0] = ((this.fConst593 * (((this.fConst595 * this.fRec190[1]) + (this.fConst621 * this.fRec190[0])) + (this.fConst621 * this.fRec190[2]))) - (this.fConst589 * ((this.fConst622 * this.fRec189[2]) + (this.fConst623 * this.fRec189[1]))));
			this.fRec188[0] = ((fSlow1 * this.fRec188[1]) + (fSlow2 * Math.abs((this.fConst589 * (((this.fConst592 * this.fRec189[1]) + (this.fConst624 * this.fRec189[0])) + (this.fConst624 * this.fRec189[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec188[0]))));
			this.fRec201[0] = (fTemp89 - (this.fConst641 * ((this.fConst644 * this.fRec201[2]) + (this.fConst645 * this.fRec201[1]))));
			this.fRec200[0] = ((this.fConst641 * (((this.fConst643 * this.fRec201[1]) + (this.fConst646 * this.fRec201[0])) + (this.fConst646 * this.fRec201[2]))) - (this.fConst639 * ((this.fConst647 * this.fRec200[2]) + (this.fConst648 * this.fRec200[1]))));
			this.fRec199[0] = ((this.fConst639 * (((this.fConst640 * this.fRec200[1]) + (this.fConst649 * this.fRec200[0])) + (this.fConst649 * this.fRec200[2]))) - (this.fConst637 * ((this.fConst650 * this.fRec199[2]) + (this.fConst651 * this.fRec199[1]))));
			var fTemp90 = (this.fConst637 * (((this.fConst638 * this.fRec199[1]) + (this.fConst652 * this.fRec199[0])) + (this.fConst652 * this.fRec199[2])));
			this.fRec198[0] = (fTemp90 - (this.fConst634 * ((this.fConst653 * this.fRec198[2]) + (this.fConst655 * this.fRec198[1]))));
			this.fRec197[0] = ((this.fConst634 * (((this.fConst636 * this.fRec198[1]) + (this.fConst656 * this.fRec198[0])) + (this.fConst656 * this.fRec198[2]))) - (this.fConst631 * ((this.fConst657 * this.fRec197[2]) + (this.fConst658 * this.fRec197[1]))));
			this.fRec196[0] = ((this.fConst631 * (((this.fConst633 * this.fRec197[1]) + (this.fConst659 * this.fRec197[0])) + (this.fConst659 * this.fRec197[2]))) - (this.fConst627 * ((this.fConst660 * this.fRec196[2]) + (this.fConst661 * this.fRec196[1]))));
			this.fRec195[0] = ((fSlow1 * this.fRec195[1]) + (fSlow2 * Math.abs((this.fConst627 * (((this.fConst630 * this.fRec196[1]) + (this.fConst662 * this.fRec196[0])) + (this.fConst662 * this.fRec196[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec195[0]))));
			this.fRec205[0] = (fTemp90 - (this.fConst667 * ((this.fConst670 * this.fRec205[2]) + (this.fConst671 * this.fRec205[1]))));
			this.fRec204[0] = ((this.fConst667 * (((this.fConst669 * this.fRec205[1]) + (this.fConst672 * this.fRec205[0])) + (this.fConst672 * this.fRec205[2]))) - (this.fConst665 * ((this.fConst673 * this.fRec204[2]) + (this.fConst674 * this.fRec204[1]))));
			this.fRec203[0] = ((this.fConst665 * (((this.fConst666 * this.fRec204[1]) + (this.fConst675 * this.fRec204[0])) + (this.fConst675 * this.fRec204[2]))) - (this.fConst663 * ((this.fConst676 * this.fRec203[2]) + (this.fConst677 * this.fRec203[1]))));
			this.fRec202[0] = ((fSlow1 * this.fRec202[1]) + (fSlow2 * Math.abs((this.fConst663 * (((this.fConst664 * this.fRec203[1]) + (this.fConst678 * this.fRec203[0])) + (this.fConst678 * this.fRec203[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec202[0]))));
			output0[i] = fTemp77;
			output1[i] = fTemp77;
			for (var j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				this.iVec0[j0] = this.iVec0[(j0 - 1)];
				
			}
			this.fRec23[1] = this.fRec23[0];
			this.fRec25[1] = this.fRec25[0];
			this.fVec1[1] = this.fVec1[0];
			this.fRec24[1] = this.fRec24[0];
			this.fVec2[1] = this.fVec2[0];
			this.fVec3[1] = this.fVec3[0];
			this.fVec4[1] = this.fVec4[0];
			this.fVec5[1] = this.fVec5[0];
			this.fVec6[1] = this.fVec6[0];
			this.fVec7[1] = this.fVec7[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec26[1] = this.fRec26[0];
			this.fVec9[1] = this.fVec9[0];
			this.fVec10[1] = this.fVec10[0];
			this.fVec11[1] = this.fVec11[0];
			this.fVec12[1] = this.fVec12[0];
			this.fVec13[1] = this.fVec13[0];
			this.fVec14[1] = this.fVec14[0];
			this.fVec15[1] = this.fVec15[0];
			this.fRec27[1] = this.fRec27[0];
			this.fVec16[1] = this.fVec16[0];
			this.fVec17[1] = this.fVec17[0];
			this.fVec18[1] = this.fVec18[0];
			this.fVec19[1] = this.fVec19[0];
			this.fVec20[1] = this.fVec20[0];
			this.fVec21[1] = this.fVec21[0];
			this.iRec28[1] = this.iRec28[0];
			for (var j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				this.fRec29[j1] = this.fRec29[(j1 - 1)];
				
			}
			this.fVec22[1] = this.fVec22[0];
			this.fRec22[1] = this.fRec22[0];
			this.fRec21[2] = this.fRec21[1];
			this.fRec21[1] = this.fRec21[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fVec23[1] = this.fVec23[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec17[2] = this.fRec17[1];
			this.fRec17[1] = this.fRec17[0];
			this.fVec24[1] = this.fVec24[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[2] = this.fRec15[1];
			this.fRec15[1] = this.fRec15[0];
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.fVec25[1] = this.fVec25[0];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fVec26[1] = this.fVec26[0];
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
			this.fRec30[1] = this.fRec30[0];
			this.fRec39[1] = this.fRec39[0];
			this.fRec38[2] = this.fRec38[1];
			this.fRec38[1] = this.fRec38[0];
			this.fRec37[2] = this.fRec37[1];
			this.fRec37[1] = this.fRec37[0];
			this.fVec27[1] = this.fVec27[0];
			this.fRec36[1] = this.fRec36[0];
			this.fRec35[2] = this.fRec35[1];
			this.fRec35[1] = this.fRec35[0];
			this.fRec34[2] = this.fRec34[1];
			this.fRec34[1] = this.fRec34[0];
			this.fRec33[2] = this.fRec33[1];
			this.fRec33[1] = this.fRec33[0];
			this.fRec32[2] = this.fRec32[1];
			this.fRec32[1] = this.fRec32[0];
			this.fRec31[2] = this.fRec31[1];
			this.fRec31[1] = this.fRec31[0];
			this.fRec40[1] = this.fRec40[0];
			this.fRec48[1] = this.fRec48[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[2] = this.fRec46[1];
			this.fRec46[1] = this.fRec46[0];
			this.fVec28[1] = this.fVec28[0];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[2] = this.fRec44[1];
			this.fRec44[1] = this.fRec44[0];
			this.fRec43[2] = this.fRec43[1];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[2] = this.fRec42[1];
			this.fRec42[1] = this.fRec42[0];
			this.fRec41[2] = this.fRec41[1];
			this.fRec41[1] = this.fRec41[0];
			this.fRec49[1] = this.fRec49[0];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[2] = this.fRec55[1];
			this.fRec55[1] = this.fRec55[0];
			this.fRec54[2] = this.fRec54[1];
			this.fRec54[1] = this.fRec54[0];
			this.fVec29[1] = this.fVec29[0];
			this.fRec53[1] = this.fRec53[0];
			this.fRec52[2] = this.fRec52[1];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[2] = this.fRec51[1];
			this.fRec51[1] = this.fRec51[0];
			this.fRec50[2] = this.fRec50[1];
			this.fRec50[1] = this.fRec50[0];
			this.fRec57[1] = this.fRec57[0];
			this.fRec63[1] = this.fRec63[0];
			this.fRec62[2] = this.fRec62[1];
			this.fRec62[1] = this.fRec62[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fVec30[1] = this.fVec30[0];
			this.fRec60[1] = this.fRec60[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[2] = this.fRec58[1];
			this.fRec58[1] = this.fRec58[0];
			this.fRec64[1] = this.fRec64[0];
			this.fRec67[1] = this.fRec67[0];
			this.fRec66[2] = this.fRec66[1];
			this.fRec66[1] = this.fRec66[0];
			this.fRec65[2] = this.fRec65[1];
			this.fRec65[1] = this.fRec65[0];
			this.fRec68[1] = this.fRec68[0];
			this.fRec79[1] = this.fRec79[0];
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
			this.fRec72[2] = this.fRec72[1];
			this.fRec72[1] = this.fRec72[0];
			this.fRec71[2] = this.fRec71[1];
			this.fRec71[1] = this.fRec71[0];
			this.fRec70[2] = this.fRec70[1];
			this.fRec70[1] = this.fRec70[0];
			this.fRec69[2] = this.fRec69[1];
			this.fRec69[1] = this.fRec69[0];
			this.fRec80[1] = this.fRec80[0];
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
			this.fRec84[2] = this.fRec84[1];
			this.fRec84[1] = this.fRec84[0];
			this.fRec83[2] = this.fRec83[1];
			this.fRec83[1] = this.fRec83[0];
			this.fRec82[2] = this.fRec82[1];
			this.fRec82[1] = this.fRec82[0];
			this.fRec81[2] = this.fRec81[1];
			this.fRec81[1] = this.fRec81[0];
			this.fRec91[1] = this.fRec91[0];
			this.fRec100[1] = this.fRec100[0];
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
			this.fRec93[2] = this.fRec93[1];
			this.fRec93[1] = this.fRec93[0];
			this.fRec92[2] = this.fRec92[1];
			this.fRec92[1] = this.fRec92[0];
			this.fRec101[1] = this.fRec101[0];
			this.fRec109[1] = this.fRec109[0];
			this.fRec108[2] = this.fRec108[1];
			this.fRec108[1] = this.fRec108[0];
			this.fRec107[2] = this.fRec107[1];
			this.fRec107[1] = this.fRec107[0];
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
			this.fRec110[1] = this.fRec110[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
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
			this.fRec131[2] = this.fRec131[1];
			this.fRec131[1] = this.fRec131[0];
			this.fRec130[2] = this.fRec130[1];
			this.fRec130[1] = this.fRec130[0];
			this.fRec129[2] = this.fRec129[1];
			this.fRec129[1] = this.fRec129[0];
			this.fRec128[2] = this.fRec128[1];
			this.fRec128[1] = this.fRec128[0];
			this.fRec127[2] = this.fRec127[1];
			this.fRec127[1] = this.fRec127[0];
			this.fRec126[2] = this.fRec126[1];
			this.fRec126[1] = this.fRec126[0];
			this.fRec125[1] = this.fRec125[0];
			this.fRec138[2] = this.fRec138[1];
			this.fRec138[1] = this.fRec138[0];
			this.fRec137[2] = this.fRec137[1];
			this.fRec137[1] = this.fRec137[0];
			this.fRec136[2] = this.fRec136[1];
			this.fRec136[1] = this.fRec136[0];
			this.fRec135[2] = this.fRec135[1];
			this.fRec135[1] = this.fRec135[0];
			this.fRec134[2] = this.fRec134[1];
			this.fRec134[1] = this.fRec134[0];
			this.fRec133[2] = this.fRec133[1];
			this.fRec133[1] = this.fRec133[0];
			this.fRec132[1] = this.fRec132[0];
			this.fRec145[2] = this.fRec145[1];
			this.fRec145[1] = this.fRec145[0];
			this.fRec144[2] = this.fRec144[1];
			this.fRec144[1] = this.fRec144[0];
			this.fRec143[2] = this.fRec143[1];
			this.fRec143[1] = this.fRec143[0];
			this.fRec142[2] = this.fRec142[1];
			this.fRec142[1] = this.fRec142[0];
			this.fRec141[2] = this.fRec141[1];
			this.fRec141[1] = this.fRec141[0];
			this.fRec140[2] = this.fRec140[1];
			this.fRec140[1] = this.fRec140[0];
			this.fRec139[1] = this.fRec139[0];
			this.fRec152[2] = this.fRec152[1];
			this.fRec152[1] = this.fRec152[0];
			this.fRec151[2] = this.fRec151[1];
			this.fRec151[1] = this.fRec151[0];
			this.fRec150[2] = this.fRec150[1];
			this.fRec150[1] = this.fRec150[0];
			this.fRec149[2] = this.fRec149[1];
			this.fRec149[1] = this.fRec149[0];
			this.fRec148[2] = this.fRec148[1];
			this.fRec148[1] = this.fRec148[0];
			this.fRec147[2] = this.fRec147[1];
			this.fRec147[1] = this.fRec147[0];
			this.fRec146[1] = this.fRec146[0];
			this.fRec159[2] = this.fRec159[1];
			this.fRec159[1] = this.fRec159[0];
			this.fRec158[2] = this.fRec158[1];
			this.fRec158[1] = this.fRec158[0];
			this.fRec157[2] = this.fRec157[1];
			this.fRec157[1] = this.fRec157[0];
			this.fRec156[2] = this.fRec156[1];
			this.fRec156[1] = this.fRec156[0];
			this.fRec155[2] = this.fRec155[1];
			this.fRec155[1] = this.fRec155[0];
			this.fRec154[2] = this.fRec154[1];
			this.fRec154[1] = this.fRec154[0];
			this.fRec153[1] = this.fRec153[0];
			this.fRec166[2] = this.fRec166[1];
			this.fRec166[1] = this.fRec166[0];
			this.fRec165[2] = this.fRec165[1];
			this.fRec165[1] = this.fRec165[0];
			this.fRec164[2] = this.fRec164[1];
			this.fRec164[1] = this.fRec164[0];
			this.fRec163[2] = this.fRec163[1];
			this.fRec163[1] = this.fRec163[0];
			this.fRec162[2] = this.fRec162[1];
			this.fRec162[1] = this.fRec162[0];
			this.fRec161[2] = this.fRec161[1];
			this.fRec161[1] = this.fRec161[0];
			this.fRec160[1] = this.fRec160[0];
			this.fRec173[2] = this.fRec173[1];
			this.fRec173[1] = this.fRec173[0];
			this.fRec172[2] = this.fRec172[1];
			this.fRec172[1] = this.fRec172[0];
			this.fRec171[2] = this.fRec171[1];
			this.fRec171[1] = this.fRec171[0];
			this.fRec170[2] = this.fRec170[1];
			this.fRec170[1] = this.fRec170[0];
			this.fRec169[2] = this.fRec169[1];
			this.fRec169[1] = this.fRec169[0];
			this.fRec168[2] = this.fRec168[1];
			this.fRec168[1] = this.fRec168[0];
			this.fRec167[1] = this.fRec167[0];
			this.fRec180[2] = this.fRec180[1];
			this.fRec180[1] = this.fRec180[0];
			this.fRec179[2] = this.fRec179[1];
			this.fRec179[1] = this.fRec179[0];
			this.fRec178[2] = this.fRec178[1];
			this.fRec178[1] = this.fRec178[0];
			this.fRec177[2] = this.fRec177[1];
			this.fRec177[1] = this.fRec177[0];
			this.fRec176[2] = this.fRec176[1];
			this.fRec176[1] = this.fRec176[0];
			this.fRec175[2] = this.fRec175[1];
			this.fRec175[1] = this.fRec175[0];
			this.fRec174[1] = this.fRec174[0];
			this.fRec187[2] = this.fRec187[1];
			this.fRec187[1] = this.fRec187[0];
			this.fRec186[2] = this.fRec186[1];
			this.fRec186[1] = this.fRec186[0];
			this.fRec185[2] = this.fRec185[1];
			this.fRec185[1] = this.fRec185[0];
			this.fRec184[2] = this.fRec184[1];
			this.fRec184[1] = this.fRec184[0];
			this.fRec183[2] = this.fRec183[1];
			this.fRec183[1] = this.fRec183[0];
			this.fRec182[2] = this.fRec182[1];
			this.fRec182[1] = this.fRec182[0];
			this.fRec181[1] = this.fRec181[0];
			this.fRec194[2] = this.fRec194[1];
			this.fRec194[1] = this.fRec194[0];
			this.fRec193[2] = this.fRec193[1];
			this.fRec193[1] = this.fRec193[0];
			this.fRec192[2] = this.fRec192[1];
			this.fRec192[1] = this.fRec192[0];
			this.fRec191[2] = this.fRec191[1];
			this.fRec191[1] = this.fRec191[0];
			this.fRec190[2] = this.fRec190[1];
			this.fRec190[1] = this.fRec190[0];
			this.fRec189[2] = this.fRec189[1];
			this.fRec189[1] = this.fRec189[0];
			this.fRec188[1] = this.fRec188[0];
			this.fRec201[2] = this.fRec201[1];
			this.fRec201[1] = this.fRec201[0];
			this.fRec200[2] = this.fRec200[1];
			this.fRec200[1] = this.fRec200[0];
			this.fRec199[2] = this.fRec199[1];
			this.fRec199[1] = this.fRec199[0];
			this.fRec198[2] = this.fRec198[1];
			this.fRec198[1] = this.fRec198[0];
			this.fRec197[2] = this.fRec197[1];
			this.fRec197[1] = this.fRec197[0];
			this.fRec196[2] = this.fRec196[1];
			this.fRec196[1] = this.fRec196[0];
			this.fRec195[1] = this.fRec195[0];
			this.fRec205[2] = this.fRec205[1];
			this.fRec205[1] = this.fRec205[0];
			this.fRec204[2] = this.fRec204[1];
			this.fRec204[1] = this.fRec204[0];
			this.fRec203[2] = this.fRec203[1];
			this.fRec203[1] = this.fRec203[0];
			this.fRec202[1] = this.fRec202[0];
			
		}
		
	}
	
}

