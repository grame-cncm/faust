
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
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
	this.fRec3 = new Float32Array(3);
	this.fConst17;
	this.fConst18;
	this.fConst19;
	this.fRec2 = new Float32Array(3);
	this.fConst20;
	this.fConst21;
	this.fConst22;
	this.fRec1 = new Float32Array(3);
	this.fConst23;
	this.fRec0 = new Float32Array(2);
	this.fVbargraph0;
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
	this.fRec10 = new Float32Array(3);
	this.fConst45;
	this.fConst46;
	this.fConst47;
	this.fRec9 = new Float32Array(3);
	this.fConst48;
	this.fConst49;
	this.fConst50;
	this.fRec8 = new Float32Array(3);
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fConst54;
	this.fRec7 = new Float32Array(3);
	this.fConst55;
	this.fConst56;
	this.fConst57;
	this.fRec6 = new Float32Array(3);
	this.fConst58;
	this.fConst59;
	this.fConst60;
	this.fRec5 = new Float32Array(3);
	this.fConst61;
	this.fRec4 = new Float32Array(2);
	this.fVbargraph1;
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
	this.fRec17 = new Float32Array(3);
	this.fConst83;
	this.fConst84;
	this.fConst85;
	this.fRec16 = new Float32Array(3);
	this.fConst86;
	this.fConst87;
	this.fConst88;
	this.fRec15 = new Float32Array(3);
	this.fConst89;
	this.fConst90;
	this.fConst91;
	this.fConst92;
	this.fRec14 = new Float32Array(3);
	this.fConst93;
	this.fConst94;
	this.fConst95;
	this.fRec13 = new Float32Array(3);
	this.fConst96;
	this.fConst97;
	this.fConst98;
	this.fRec12 = new Float32Array(3);
	this.fConst99;
	this.fRec11 = new Float32Array(2);
	this.fVbargraph2;
	this.fConst100;
	this.fConst101;
	this.fConst102;
	this.fConst103;
	this.fConst104;
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
	this.fRec24 = new Float32Array(3);
	this.fConst121;
	this.fConst122;
	this.fConst123;
	this.fRec23 = new Float32Array(3);
	this.fConst124;
	this.fConst125;
	this.fConst126;
	this.fRec22 = new Float32Array(3);
	this.fConst127;
	this.fConst128;
	this.fConst129;
	this.fConst130;
	this.fRec21 = new Float32Array(3);
	this.fConst131;
	this.fConst132;
	this.fConst133;
	this.fRec20 = new Float32Array(3);
	this.fConst134;
	this.fConst135;
	this.fConst136;
	this.fRec19 = new Float32Array(3);
	this.fConst137;
	this.fRec18 = new Float32Array(2);
	this.fVbargraph3;
	this.fConst138;
	this.fConst139;
	this.fConst140;
	this.fConst141;
	this.fConst142;
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
	this.fRec31 = new Float32Array(3);
	this.fConst159;
	this.fConst160;
	this.fConst161;
	this.fRec30 = new Float32Array(3);
	this.fConst162;
	this.fConst163;
	this.fConst164;
	this.fRec29 = new Float32Array(3);
	this.fConst165;
	this.fConst166;
	this.fConst167;
	this.fConst168;
	this.fRec28 = new Float32Array(3);
	this.fConst169;
	this.fConst170;
	this.fConst171;
	this.fRec27 = new Float32Array(3);
	this.fConst172;
	this.fConst173;
	this.fConst174;
	this.fRec26 = new Float32Array(3);
	this.fConst175;
	this.fRec25 = new Float32Array(2);
	this.fVbargraph4;
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
	this.fConst190;
	this.fConst191;
	this.fConst192;
	this.fConst193;
	this.fConst194;
	this.fConst195;
	this.fConst196;
	this.fRec38 = new Float32Array(3);
	this.fConst197;
	this.fConst198;
	this.fConst199;
	this.fRec37 = new Float32Array(3);
	this.fConst200;
	this.fConst201;
	this.fConst202;
	this.fRec36 = new Float32Array(3);
	this.fConst203;
	this.fConst204;
	this.fConst205;
	this.fConst206;
	this.fRec35 = new Float32Array(3);
	this.fConst207;
	this.fConst208;
	this.fConst209;
	this.fRec34 = new Float32Array(3);
	this.fConst210;
	this.fConst211;
	this.fConst212;
	this.fRec33 = new Float32Array(3);
	this.fConst213;
	this.fRec32 = new Float32Array(2);
	this.fVbargraph5;
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
	this.fConst228;
	this.fConst229;
	this.fConst230;
	this.fConst231;
	this.fConst232;
	this.fConst233;
	this.fConst234;
	this.fRec45 = new Float32Array(3);
	this.fConst235;
	this.fConst236;
	this.fConst237;
	this.fRec44 = new Float32Array(3);
	this.fConst238;
	this.fConst239;
	this.fConst240;
	this.fRec43 = new Float32Array(3);
	this.fConst241;
	this.fConst242;
	this.fConst243;
	this.fConst244;
	this.fRec42 = new Float32Array(3);
	this.fConst245;
	this.fConst246;
	this.fConst247;
	this.fRec41 = new Float32Array(3);
	this.fConst248;
	this.fConst249;
	this.fConst250;
	this.fRec40 = new Float32Array(3);
	this.fConst251;
	this.fRec39 = new Float32Array(2);
	this.fVbargraph6;
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
	this.fConst266;
	this.fConst267;
	this.fConst268;
	this.fConst269;
	this.fConst270;
	this.fConst271;
	this.fConst272;
	this.fRec52 = new Float32Array(3);
	this.fConst273;
	this.fConst274;
	this.fConst275;
	this.fRec51 = new Float32Array(3);
	this.fConst276;
	this.fConst277;
	this.fConst278;
	this.fRec50 = new Float32Array(3);
	this.fConst279;
	this.fConst280;
	this.fConst281;
	this.fConst282;
	this.fRec49 = new Float32Array(3);
	this.fConst283;
	this.fConst284;
	this.fConst285;
	this.fRec48 = new Float32Array(3);
	this.fConst286;
	this.fConst287;
	this.fConst288;
	this.fRec47 = new Float32Array(3);
	this.fConst289;
	this.fRec46 = new Float32Array(2);
	this.fVbargraph7;
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
	this.fConst304;
	this.fConst305;
	this.fConst306;
	this.fConst307;
	this.fConst308;
	this.fConst309;
	this.fConst310;
	this.fRec59 = new Float32Array(3);
	this.fConst311;
	this.fConst312;
	this.fConst313;
	this.fRec58 = new Float32Array(3);
	this.fConst314;
	this.fConst315;
	this.fConst316;
	this.fRec57 = new Float32Array(3);
	this.fConst317;
	this.fConst318;
	this.fConst319;
	this.fConst320;
	this.fRec56 = new Float32Array(3);
	this.fConst321;
	this.fConst322;
	this.fConst323;
	this.fRec55 = new Float32Array(3);
	this.fConst324;
	this.fConst325;
	this.fConst326;
	this.fRec54 = new Float32Array(3);
	this.fConst327;
	this.fRec53 = new Float32Array(2);
	this.fVbargraph8;
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
	this.fConst342;
	this.fConst343;
	this.fConst344;
	this.fConst345;
	this.fConst346;
	this.fConst347;
	this.fConst348;
	this.fRec66 = new Float32Array(3);
	this.fConst349;
	this.fConst350;
	this.fConst351;
	this.fRec65 = new Float32Array(3);
	this.fConst352;
	this.fConst353;
	this.fConst354;
	this.fRec64 = new Float32Array(3);
	this.fConst355;
	this.fConst356;
	this.fConst357;
	this.fConst358;
	this.fRec63 = new Float32Array(3);
	this.fConst359;
	this.fConst360;
	this.fConst361;
	this.fRec62 = new Float32Array(3);
	this.fConst362;
	this.fConst363;
	this.fConst364;
	this.fRec61 = new Float32Array(3);
	this.fConst365;
	this.fRec60 = new Float32Array(2);
	this.fVbargraph9;
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
	this.fConst380;
	this.fConst381;
	this.fConst382;
	this.fConst383;
	this.fConst384;
	this.fConst385;
	this.fConst386;
	this.fRec73 = new Float32Array(3);
	this.fConst387;
	this.fConst388;
	this.fConst389;
	this.fRec72 = new Float32Array(3);
	this.fConst390;
	this.fConst391;
	this.fConst392;
	this.fRec71 = new Float32Array(3);
	this.fConst393;
	this.fConst394;
	this.fConst395;
	this.fConst396;
	this.fRec70 = new Float32Array(3);
	this.fConst397;
	this.fConst398;
	this.fConst399;
	this.fRec69 = new Float32Array(3);
	this.fConst400;
	this.fConst401;
	this.fConst402;
	this.fRec68 = new Float32Array(3);
	this.fConst403;
	this.fRec67 = new Float32Array(2);
	this.fVbargraph10;
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
	this.fConst418;
	this.fConst419;
	this.fConst420;
	this.fConst421;
	this.fConst422;
	this.fConst423;
	this.fConst424;
	this.fRec80 = new Float32Array(3);
	this.fConst425;
	this.fConst426;
	this.fConst427;
	this.fRec79 = new Float32Array(3);
	this.fConst428;
	this.fConst429;
	this.fConst430;
	this.fRec78 = new Float32Array(3);
	this.fConst431;
	this.fConst432;
	this.fConst433;
	this.fConst434;
	this.fRec77 = new Float32Array(3);
	this.fConst435;
	this.fConst436;
	this.fConst437;
	this.fRec76 = new Float32Array(3);
	this.fConst438;
	this.fConst439;
	this.fConst440;
	this.fRec75 = new Float32Array(3);
	this.fConst441;
	this.fRec74 = new Float32Array(2);
	this.fVbargraph11;
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
	this.fConst456;
	this.fConst457;
	this.fConst458;
	this.fConst459;
	this.fConst460;
	this.fConst461;
	this.fConst462;
	this.fRec87 = new Float32Array(3);
	this.fConst463;
	this.fConst464;
	this.fConst465;
	this.fRec86 = new Float32Array(3);
	this.fConst466;
	this.fConst467;
	this.fConst468;
	this.fRec85 = new Float32Array(3);
	this.fConst469;
	this.fConst470;
	this.fConst471;
	this.fConst472;
	this.fRec84 = new Float32Array(3);
	this.fConst473;
	this.fConst474;
	this.fConst475;
	this.fRec83 = new Float32Array(3);
	this.fConst476;
	this.fConst477;
	this.fConst478;
	this.fRec82 = new Float32Array(3);
	this.fConst479;
	this.fRec81 = new Float32Array(2);
	this.fVbargraph12;
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
	this.fConst494;
	this.fConst495;
	this.fConst496;
	this.fConst497;
	this.fConst498;
	this.fConst499;
	this.fConst500;
	this.fRec94 = new Float32Array(3);
	this.fConst501;
	this.fConst502;
	this.fConst503;
	this.fRec93 = new Float32Array(3);
	this.fConst504;
	this.fConst505;
	this.fConst506;
	this.fRec92 = new Float32Array(3);
	this.fConst507;
	this.fConst508;
	this.fConst509;
	this.fConst510;
	this.fRec91 = new Float32Array(3);
	this.fConst511;
	this.fConst512;
	this.fConst513;
	this.fRec90 = new Float32Array(3);
	this.fConst514;
	this.fConst515;
	this.fConst516;
	this.fRec89 = new Float32Array(3);
	this.fConst517;
	this.fRec88 = new Float32Array(2);
	this.fVbargraph13;
	this.fConst518;
	this.fConst519;
	this.fConst520;
	this.fConst521;
	this.fConst522;
	this.fConst523;
	this.fConst524;
	this.fConst525;
	this.fConst526;
	this.fRec98 = new Float32Array(3);
	this.fConst527;
	this.fConst528;
	this.fConst529;
	this.fRec97 = new Float32Array(3);
	this.fConst530;
	this.fConst531;
	this.fConst532;
	this.fRec96 = new Float32Array(3);
	this.fConst533;
	this.fRec95 = new Float32Array(2);
	this.fVbargraph14;
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "JOS, revised by RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Demonstrates mth_octave_spectral_level in a standalone GUI.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "spectralLevel");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("version", "0.0");
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
		this.fConst14 = (((this.fConst3 + -3.18973) / this.fConst2) + 4.07678);
		this.fConst15 = (1 / this.fConst5);
		this.fConst16 = (2 * (4.07678 - this.fConst15));
		this.fConst17 = (this.fConst12 + 0.000407678);
		this.fConst18 = (((this.fConst3 + -0.74313) / this.fConst2) + 1.45007);
		this.fConst19 = (2 * (1.45007 - this.fConst15));
		this.fConst20 = (this.fConst9 + 1.45007);
		this.fConst21 = (((this.fConst3 + -0.157482) / this.fConst2) + 0.93514);
		this.fConst22 = (2 * (0.93514 - this.fConst15));
		this.fConst23 = (this.fConst6 + 0.93514);
		this.fConst24 = Math.tan((31665.3 / this.fConst0));
		this.fConst25 = (1 / this.fConst24);
		this.fConst26 = (1 / (((this.fConst25 + 0.157482) / this.fConst24) + 0.93514));
		this.fConst27 = mydsp_faustpower2_f(this.fConst24);
		this.fConst28 = (50.0638 / this.fConst27);
		this.fConst29 = (2 * (0.93514 - this.fConst28));
		this.fConst30 = (1 / (((this.fConst25 + 0.74313) / this.fConst24) + 1.45007));
		this.fConst31 = (11.0521 / this.fConst27);
		this.fConst32 = (2 * (1.45007 - this.fConst31));
		this.fConst33 = (1 / (((this.fConst25 + 3.18973) / this.fConst24) + 4.07678));
		this.fConst34 = (0.00176617 / this.fConst27);
		this.fConst35 = (2 * (0.000407678 - this.fConst34));
		this.fConst36 = (1 / (((this.fConst3 + 0.168405) / this.fConst2) + 1.06936));
		this.fConst37 = (2 * (53.5362 - this.fConst15));
		this.fConst38 = (1 / (((this.fConst3 + 0.512479) / this.fConst2) + 0.689621));
		this.fConst39 = (2 * (7.62173 - this.fConst15));
		this.fConst40 = (1 / (((this.fConst3 + 0.782413) / this.fConst2) + 0.245292));
		this.fConst41 = (0.0001 / this.fConst5);
		this.fConst42 = (2 * (0.000433227 - this.fConst41));
		this.fConst43 = (((this.fConst3 + -0.782413) / this.fConst2) + 0.245292);
		this.fConst44 = (2 * (0.245292 - this.fConst15));
		this.fConst45 = (this.fConst41 + 0.000433227);
		this.fConst46 = (((this.fConst3 + -0.512479) / this.fConst2) + 0.689621);
		this.fConst47 = (2 * (0.689621 - this.fConst15));
		this.fConst48 = (this.fConst15 + 7.62173);
		this.fConst49 = (((this.fConst3 + -0.168405) / this.fConst2) + 1.06936);
		this.fConst50 = (2 * (1.06936 - this.fConst15));
		this.fConst51 = (this.fConst15 + 53.5362);
		this.fConst52 = (((this.fConst25 + -3.18973) / this.fConst24) + 4.07678);
		this.fConst53 = (1 / this.fConst27);
		this.fConst54 = (2 * (4.07678 - this.fConst53));
		this.fConst55 = (this.fConst34 + 0.000407678);
		this.fConst56 = (((this.fConst25 + -0.74313) / this.fConst24) + 1.45007);
		this.fConst57 = (2 * (1.45007 - this.fConst53));
		this.fConst58 = (this.fConst31 + 1.45007);
		this.fConst59 = (((this.fConst25 + -0.157482) / this.fConst24) + 0.93514);
		this.fConst60 = (2 * (0.93514 - this.fConst53));
		this.fConst61 = (this.fConst28 + 0.93514);
		this.fConst62 = Math.tan((19947.9 / this.fConst0));
		this.fConst63 = (1 / this.fConst62);
		this.fConst64 = (1 / (((this.fConst63 + 0.157482) / this.fConst62) + 0.93514));
		this.fConst65 = mydsp_faustpower2_f(this.fConst62);
		this.fConst66 = (50.0638 / this.fConst65);
		this.fConst67 = (2 * (0.93514 - this.fConst66));
		this.fConst68 = (1 / (((this.fConst63 + 0.74313) / this.fConst62) + 1.45007));
		this.fConst69 = (11.0521 / this.fConst65);
		this.fConst70 = (2 * (1.45007 - this.fConst69));
		this.fConst71 = (1 / (((this.fConst63 + 3.18973) / this.fConst62) + 4.07678));
		this.fConst72 = (0.00176617 / this.fConst65);
		this.fConst73 = (2 * (0.000407678 - this.fConst72));
		this.fConst74 = (1 / (((this.fConst25 + 0.168405) / this.fConst24) + 1.06936));
		this.fConst75 = (2 * (53.5362 - this.fConst53));
		this.fConst76 = (1 / (((this.fConst25 + 0.512479) / this.fConst24) + 0.689621));
		this.fConst77 = (2 * (7.62173 - this.fConst53));
		this.fConst78 = (1 / (((this.fConst25 + 0.782413) / this.fConst24) + 0.245292));
		this.fConst79 = (0.0001 / this.fConst27);
		this.fConst80 = (2 * (0.000433227 - this.fConst79));
		this.fConst81 = (((this.fConst25 + -0.782413) / this.fConst24) + 0.245292);
		this.fConst82 = (2 * (0.245292 - this.fConst53));
		this.fConst83 = (this.fConst79 + 0.000433227);
		this.fConst84 = (((this.fConst25 + -0.512479) / this.fConst24) + 0.689621);
		this.fConst85 = (2 * (0.689621 - this.fConst53));
		this.fConst86 = (this.fConst53 + 7.62173);
		this.fConst87 = (((this.fConst25 + -0.168405) / this.fConst24) + 1.06936);
		this.fConst88 = (2 * (1.06936 - this.fConst53));
		this.fConst89 = (this.fConst53 + 53.5362);
		this.fConst90 = (((this.fConst63 + -3.18973) / this.fConst62) + 4.07678);
		this.fConst91 = (1 / this.fConst65);
		this.fConst92 = (2 * (4.07678 - this.fConst91));
		this.fConst93 = (this.fConst72 + 0.000407678);
		this.fConst94 = (((this.fConst63 + -0.74313) / this.fConst62) + 1.45007);
		this.fConst95 = (2 * (1.45007 - this.fConst91));
		this.fConst96 = (this.fConst69 + 1.45007);
		this.fConst97 = (((this.fConst63 + -0.157482) / this.fConst62) + 0.93514);
		this.fConst98 = (2 * (0.93514 - this.fConst91));
		this.fConst99 = (this.fConst66 + 0.93514);
		this.fConst100 = Math.tan((12566.4 / this.fConst0));
		this.fConst101 = (1 / this.fConst100);
		this.fConst102 = (1 / (((this.fConst101 + 0.157482) / this.fConst100) + 0.93514));
		this.fConst103 = mydsp_faustpower2_f(this.fConst100);
		this.fConst104 = (50.0638 / this.fConst103);
		this.fConst105 = (2 * (0.93514 - this.fConst104));
		this.fConst106 = (1 / (((this.fConst101 + 0.74313) / this.fConst100) + 1.45007));
		this.fConst107 = (11.0521 / this.fConst103);
		this.fConst108 = (2 * (1.45007 - this.fConst107));
		this.fConst109 = (1 / (((this.fConst101 + 3.18973) / this.fConst100) + 4.07678));
		this.fConst110 = (0.00176617 / this.fConst103);
		this.fConst111 = (2 * (0.000407678 - this.fConst110));
		this.fConst112 = (1 / (((this.fConst63 + 0.168405) / this.fConst62) + 1.06936));
		this.fConst113 = (2 * (53.5362 - this.fConst91));
		this.fConst114 = (1 / (((this.fConst63 + 0.512479) / this.fConst62) + 0.689621));
		this.fConst115 = (2 * (7.62173 - this.fConst91));
		this.fConst116 = (1 / (((this.fConst63 + 0.782413) / this.fConst62) + 0.245292));
		this.fConst117 = (0.0001 / this.fConst65);
		this.fConst118 = (2 * (0.000433227 - this.fConst117));
		this.fConst119 = (((this.fConst63 + -0.782413) / this.fConst62) + 0.245292);
		this.fConst120 = (2 * (0.245292 - this.fConst91));
		this.fConst121 = (this.fConst117 + 0.000433227);
		this.fConst122 = (((this.fConst63 + -0.512479) / this.fConst62) + 0.689621);
		this.fConst123 = (2 * (0.689621 - this.fConst91));
		this.fConst124 = (this.fConst91 + 7.62173);
		this.fConst125 = (((this.fConst63 + -0.168405) / this.fConst62) + 1.06936);
		this.fConst126 = (2 * (1.06936 - this.fConst91));
		this.fConst127 = (this.fConst91 + 53.5362);
		this.fConst128 = (((this.fConst101 + -3.18973) / this.fConst100) + 4.07678);
		this.fConst129 = (1 / this.fConst103);
		this.fConst130 = (2 * (4.07678 - this.fConst129));
		this.fConst131 = (this.fConst110 + 0.000407678);
		this.fConst132 = (((this.fConst101 + -0.74313) / this.fConst100) + 1.45007);
		this.fConst133 = (2 * (1.45007 - this.fConst129));
		this.fConst134 = (this.fConst107 + 1.45007);
		this.fConst135 = (((this.fConst101 + -0.157482) / this.fConst100) + 0.93514);
		this.fConst136 = (2 * (0.93514 - this.fConst129));
		this.fConst137 = (this.fConst104 + 0.93514);
		this.fConst138 = Math.tan((7916.32 / this.fConst0));
		this.fConst139 = (1 / this.fConst138);
		this.fConst140 = (1 / (((this.fConst139 + 0.157482) / this.fConst138) + 0.93514));
		this.fConst141 = mydsp_faustpower2_f(this.fConst138);
		this.fConst142 = (50.0638 / this.fConst141);
		this.fConst143 = (2 * (0.93514 - this.fConst142));
		this.fConst144 = (1 / (((this.fConst139 + 0.74313) / this.fConst138) + 1.45007));
		this.fConst145 = (11.0521 / this.fConst141);
		this.fConst146 = (2 * (1.45007 - this.fConst145));
		this.fConst147 = (1 / (((this.fConst139 + 3.18973) / this.fConst138) + 4.07678));
		this.fConst148 = (0.00176617 / this.fConst141);
		this.fConst149 = (2 * (0.000407678 - this.fConst148));
		this.fConst150 = (1 / (((this.fConst101 + 0.168405) / this.fConst100) + 1.06936));
		this.fConst151 = (2 * (53.5362 - this.fConst129));
		this.fConst152 = (1 / (((this.fConst101 + 0.512479) / this.fConst100) + 0.689621));
		this.fConst153 = (2 * (7.62173 - this.fConst129));
		this.fConst154 = (1 / (((this.fConst101 + 0.782413) / this.fConst100) + 0.245292));
		this.fConst155 = (0.0001 / this.fConst103);
		this.fConst156 = (2 * (0.000433227 - this.fConst155));
		this.fConst157 = (((this.fConst101 + -0.782413) / this.fConst100) + 0.245292);
		this.fConst158 = (2 * (0.245292 - this.fConst129));
		this.fConst159 = (this.fConst155 + 0.000433227);
		this.fConst160 = (((this.fConst101 + -0.512479) / this.fConst100) + 0.689621);
		this.fConst161 = (2 * (0.689621 - this.fConst129));
		this.fConst162 = (this.fConst129 + 7.62173);
		this.fConst163 = (((this.fConst101 + -0.168405) / this.fConst100) + 1.06936);
		this.fConst164 = (2 * (1.06936 - this.fConst129));
		this.fConst165 = (this.fConst129 + 53.5362);
		this.fConst166 = (((this.fConst139 + -3.18973) / this.fConst138) + 4.07678);
		this.fConst167 = (1 / this.fConst141);
		this.fConst168 = (2 * (4.07678 - this.fConst167));
		this.fConst169 = (this.fConst148 + 0.000407678);
		this.fConst170 = (((this.fConst139 + -0.74313) / this.fConst138) + 1.45007);
		this.fConst171 = (2 * (1.45007 - this.fConst167));
		this.fConst172 = (this.fConst145 + 1.45007);
		this.fConst173 = (((this.fConst139 + -0.157482) / this.fConst138) + 0.93514);
		this.fConst174 = (2 * (0.93514 - this.fConst167));
		this.fConst175 = (this.fConst142 + 0.93514);
		this.fConst176 = Math.tan((4986.97 / this.fConst0));
		this.fConst177 = (1 / this.fConst176);
		this.fConst178 = (1 / (((this.fConst177 + 0.157482) / this.fConst176) + 0.93514));
		this.fConst179 = mydsp_faustpower2_f(this.fConst176);
		this.fConst180 = (50.0638 / this.fConst179);
		this.fConst181 = (2 * (0.93514 - this.fConst180));
		this.fConst182 = (1 / (((this.fConst177 + 0.74313) / this.fConst176) + 1.45007));
		this.fConst183 = (11.0521 / this.fConst179);
		this.fConst184 = (2 * (1.45007 - this.fConst183));
		this.fConst185 = (1 / (((this.fConst177 + 3.18973) / this.fConst176) + 4.07678));
		this.fConst186 = (0.00176617 / this.fConst179);
		this.fConst187 = (2 * (0.000407678 - this.fConst186));
		this.fConst188 = (1 / (((this.fConst139 + 0.168405) / this.fConst138) + 1.06936));
		this.fConst189 = (2 * (53.5362 - this.fConst167));
		this.fConst190 = (1 / (((this.fConst139 + 0.512479) / this.fConst138) + 0.689621));
		this.fConst191 = (2 * (7.62173 - this.fConst167));
		this.fConst192 = (1 / (((this.fConst139 + 0.782413) / this.fConst138) + 0.245292));
		this.fConst193 = (0.0001 / this.fConst141);
		this.fConst194 = (2 * (0.000433227 - this.fConst193));
		this.fConst195 = (((this.fConst139 + -0.782413) / this.fConst138) + 0.245292);
		this.fConst196 = (2 * (0.245292 - this.fConst167));
		this.fConst197 = (this.fConst193 + 0.000433227);
		this.fConst198 = (((this.fConst139 + -0.512479) / this.fConst138) + 0.689621);
		this.fConst199 = (2 * (0.689621 - this.fConst167));
		this.fConst200 = (this.fConst167 + 7.62173);
		this.fConst201 = (((this.fConst139 + -0.168405) / this.fConst138) + 1.06936);
		this.fConst202 = (2 * (1.06936 - this.fConst167));
		this.fConst203 = (this.fConst167 + 53.5362);
		this.fConst204 = (((this.fConst177 + -3.18973) / this.fConst176) + 4.07678);
		this.fConst205 = (1 / this.fConst179);
		this.fConst206 = (2 * (4.07678 - this.fConst205));
		this.fConst207 = (this.fConst186 + 0.000407678);
		this.fConst208 = (((this.fConst177 + -0.74313) / this.fConst176) + 1.45007);
		this.fConst209 = (2 * (1.45007 - this.fConst205));
		this.fConst210 = (this.fConst183 + 1.45007);
		this.fConst211 = (((this.fConst177 + -0.157482) / this.fConst176) + 0.93514);
		this.fConst212 = (2 * (0.93514 - this.fConst205));
		this.fConst213 = (this.fConst180 + 0.93514);
		this.fConst214 = Math.tan((3141.59 / this.fConst0));
		this.fConst215 = (1 / this.fConst214);
		this.fConst216 = (1 / (((this.fConst215 + 0.157482) / this.fConst214) + 0.93514));
		this.fConst217 = mydsp_faustpower2_f(this.fConst214);
		this.fConst218 = (50.0638 / this.fConst217);
		this.fConst219 = (2 * (0.93514 - this.fConst218));
		this.fConst220 = (1 / (((this.fConst215 + 0.74313) / this.fConst214) + 1.45007));
		this.fConst221 = (11.0521 / this.fConst217);
		this.fConst222 = (2 * (1.45007 - this.fConst221));
		this.fConst223 = (1 / (((this.fConst215 + 3.18973) / this.fConst214) + 4.07678));
		this.fConst224 = (0.00176617 / this.fConst217);
		this.fConst225 = (2 * (0.000407678 - this.fConst224));
		this.fConst226 = (1 / (((this.fConst177 + 0.168405) / this.fConst176) + 1.06936));
		this.fConst227 = (2 * (53.5362 - this.fConst205));
		this.fConst228 = (1 / (((this.fConst177 + 0.512479) / this.fConst176) + 0.689621));
		this.fConst229 = (2 * (7.62173 - this.fConst205));
		this.fConst230 = (1 / (((this.fConst177 + 0.782413) / this.fConst176) + 0.245292));
		this.fConst231 = (0.0001 / this.fConst179);
		this.fConst232 = (2 * (0.000433227 - this.fConst231));
		this.fConst233 = (((this.fConst177 + -0.782413) / this.fConst176) + 0.245292);
		this.fConst234 = (2 * (0.245292 - this.fConst205));
		this.fConst235 = (this.fConst231 + 0.000433227);
		this.fConst236 = (((this.fConst177 + -0.512479) / this.fConst176) + 0.689621);
		this.fConst237 = (2 * (0.689621 - this.fConst205));
		this.fConst238 = (this.fConst205 + 7.62173);
		this.fConst239 = (((this.fConst177 + -0.168405) / this.fConst176) + 1.06936);
		this.fConst240 = (2 * (1.06936 - this.fConst205));
		this.fConst241 = (this.fConst205 + 53.5362);
		this.fConst242 = (((this.fConst215 + -3.18973) / this.fConst214) + 4.07678);
		this.fConst243 = (1 / this.fConst217);
		this.fConst244 = (2 * (4.07678 - this.fConst243));
		this.fConst245 = (this.fConst224 + 0.000407678);
		this.fConst246 = (((this.fConst215 + -0.74313) / this.fConst214) + 1.45007);
		this.fConst247 = (2 * (1.45007 - this.fConst243));
		this.fConst248 = (this.fConst221 + 1.45007);
		this.fConst249 = (((this.fConst215 + -0.157482) / this.fConst214) + 0.93514);
		this.fConst250 = (2 * (0.93514 - this.fConst243));
		this.fConst251 = (this.fConst218 + 0.93514);
		this.fConst252 = Math.tan((1979.08 / this.fConst0));
		this.fConst253 = (1 / this.fConst252);
		this.fConst254 = (1 / (((this.fConst253 + 0.157482) / this.fConst252) + 0.93514));
		this.fConst255 = mydsp_faustpower2_f(this.fConst252);
		this.fConst256 = (50.0638 / this.fConst255);
		this.fConst257 = (2 * (0.93514 - this.fConst256));
		this.fConst258 = (1 / (((this.fConst253 + 0.74313) / this.fConst252) + 1.45007));
		this.fConst259 = (11.0521 / this.fConst255);
		this.fConst260 = (2 * (1.45007 - this.fConst259));
		this.fConst261 = (1 / (((this.fConst253 + 3.18973) / this.fConst252) + 4.07678));
		this.fConst262 = (0.00176617 / this.fConst255);
		this.fConst263 = (2 * (0.000407678 - this.fConst262));
		this.fConst264 = (1 / (((this.fConst215 + 0.168405) / this.fConst214) + 1.06936));
		this.fConst265 = (2 * (53.5362 - this.fConst243));
		this.fConst266 = (1 / (((this.fConst215 + 0.512479) / this.fConst214) + 0.689621));
		this.fConst267 = (2 * (7.62173 - this.fConst243));
		this.fConst268 = (1 / (((this.fConst215 + 0.782413) / this.fConst214) + 0.245292));
		this.fConst269 = (0.0001 / this.fConst217);
		this.fConst270 = (2 * (0.000433227 - this.fConst269));
		this.fConst271 = (((this.fConst215 + -0.782413) / this.fConst214) + 0.245292);
		this.fConst272 = (2 * (0.245292 - this.fConst243));
		this.fConst273 = (this.fConst269 + 0.000433227);
		this.fConst274 = (((this.fConst215 + -0.512479) / this.fConst214) + 0.689621);
		this.fConst275 = (2 * (0.689621 - this.fConst243));
		this.fConst276 = (this.fConst243 + 7.62173);
		this.fConst277 = (((this.fConst215 + -0.168405) / this.fConst214) + 1.06936);
		this.fConst278 = (2 * (1.06936 - this.fConst243));
		this.fConst279 = (this.fConst243 + 53.5362);
		this.fConst280 = (((this.fConst253 + -3.18973) / this.fConst252) + 4.07678);
		this.fConst281 = (1 / this.fConst255);
		this.fConst282 = (2 * (4.07678 - this.fConst281));
		this.fConst283 = (this.fConst262 + 0.000407678);
		this.fConst284 = (((this.fConst253 + -0.74313) / this.fConst252) + 1.45007);
		this.fConst285 = (2 * (1.45007 - this.fConst281));
		this.fConst286 = (this.fConst259 + 1.45007);
		this.fConst287 = (((this.fConst253 + -0.157482) / this.fConst252) + 0.93514);
		this.fConst288 = (2 * (0.93514 - this.fConst281));
		this.fConst289 = (this.fConst256 + 0.93514);
		this.fConst290 = Math.tan((1246.74 / this.fConst0));
		this.fConst291 = (1 / this.fConst290);
		this.fConst292 = (1 / (((this.fConst291 + 0.157482) / this.fConst290) + 0.93514));
		this.fConst293 = mydsp_faustpower2_f(this.fConst290);
		this.fConst294 = (50.0638 / this.fConst293);
		this.fConst295 = (2 * (0.93514 - this.fConst294));
		this.fConst296 = (1 / (((this.fConst291 + 0.74313) / this.fConst290) + 1.45007));
		this.fConst297 = (11.0521 / this.fConst293);
		this.fConst298 = (2 * (1.45007 - this.fConst297));
		this.fConst299 = (1 / (((this.fConst291 + 3.18973) / this.fConst290) + 4.07678));
		this.fConst300 = (0.00176617 / this.fConst293);
		this.fConst301 = (2 * (0.000407678 - this.fConst300));
		this.fConst302 = (1 / (((this.fConst253 + 0.168405) / this.fConst252) + 1.06936));
		this.fConst303 = (2 * (53.5362 - this.fConst281));
		this.fConst304 = (1 / (((this.fConst253 + 0.512479) / this.fConst252) + 0.689621));
		this.fConst305 = (2 * (7.62173 - this.fConst281));
		this.fConst306 = (1 / (((this.fConst253 + 0.782413) / this.fConst252) + 0.245292));
		this.fConst307 = (0.0001 / this.fConst255);
		this.fConst308 = (2 * (0.000433227 - this.fConst307));
		this.fConst309 = (((this.fConst253 + -0.782413) / this.fConst252) + 0.245292);
		this.fConst310 = (2 * (0.245292 - this.fConst281));
		this.fConst311 = (this.fConst307 + 0.000433227);
		this.fConst312 = (((this.fConst253 + -0.512479) / this.fConst252) + 0.689621);
		this.fConst313 = (2 * (0.689621 - this.fConst281));
		this.fConst314 = (this.fConst281 + 7.62173);
		this.fConst315 = (((this.fConst253 + -0.168405) / this.fConst252) + 1.06936);
		this.fConst316 = (2 * (1.06936 - this.fConst281));
		this.fConst317 = (this.fConst281 + 53.5362);
		this.fConst318 = (((this.fConst291 + -3.18973) / this.fConst290) + 4.07678);
		this.fConst319 = (1 / this.fConst293);
		this.fConst320 = (2 * (4.07678 - this.fConst319));
		this.fConst321 = (this.fConst300 + 0.000407678);
		this.fConst322 = (((this.fConst291 + -0.74313) / this.fConst290) + 1.45007);
		this.fConst323 = (2 * (1.45007 - this.fConst319));
		this.fConst324 = (this.fConst297 + 1.45007);
		this.fConst325 = (((this.fConst291 + -0.157482) / this.fConst290) + 0.93514);
		this.fConst326 = (2 * (0.93514 - this.fConst319));
		this.fConst327 = (this.fConst294 + 0.93514);
		this.fConst328 = Math.tan((785.398 / this.fConst0));
		this.fConst329 = (1 / this.fConst328);
		this.fConst330 = (1 / (((this.fConst329 + 0.157482) / this.fConst328) + 0.93514));
		this.fConst331 = mydsp_faustpower2_f(this.fConst328);
		this.fConst332 = (50.0638 / this.fConst331);
		this.fConst333 = (2 * (0.93514 - this.fConst332));
		this.fConst334 = (1 / (((this.fConst329 + 0.74313) / this.fConst328) + 1.45007));
		this.fConst335 = (11.0521 / this.fConst331);
		this.fConst336 = (2 * (1.45007 - this.fConst335));
		this.fConst337 = (1 / (((this.fConst329 + 3.18973) / this.fConst328) + 4.07678));
		this.fConst338 = (0.00176617 / this.fConst331);
		this.fConst339 = (2 * (0.000407678 - this.fConst338));
		this.fConst340 = (1 / (((this.fConst291 + 0.168405) / this.fConst290) + 1.06936));
		this.fConst341 = (2 * (53.5362 - this.fConst319));
		this.fConst342 = (1 / (((this.fConst291 + 0.512479) / this.fConst290) + 0.689621));
		this.fConst343 = (2 * (7.62173 - this.fConst319));
		this.fConst344 = (1 / (((this.fConst291 + 0.782413) / this.fConst290) + 0.245292));
		this.fConst345 = (0.0001 / this.fConst293);
		this.fConst346 = (2 * (0.000433227 - this.fConst345));
		this.fConst347 = (((this.fConst291 + -0.782413) / this.fConst290) + 0.245292);
		this.fConst348 = (2 * (0.245292 - this.fConst319));
		this.fConst349 = (this.fConst345 + 0.000433227);
		this.fConst350 = (((this.fConst291 + -0.512479) / this.fConst290) + 0.689621);
		this.fConst351 = (2 * (0.689621 - this.fConst319));
		this.fConst352 = (this.fConst319 + 7.62173);
		this.fConst353 = (((this.fConst291 + -0.168405) / this.fConst290) + 1.06936);
		this.fConst354 = (2 * (1.06936 - this.fConst319));
		this.fConst355 = (this.fConst319 + 53.5362);
		this.fConst356 = (((this.fConst329 + -3.18973) / this.fConst328) + 4.07678);
		this.fConst357 = (1 / this.fConst331);
		this.fConst358 = (2 * (4.07678 - this.fConst357));
		this.fConst359 = (this.fConst338 + 0.000407678);
		this.fConst360 = (((this.fConst329 + -0.74313) / this.fConst328) + 1.45007);
		this.fConst361 = (2 * (1.45007 - this.fConst357));
		this.fConst362 = (this.fConst335 + 1.45007);
		this.fConst363 = (((this.fConst329 + -0.157482) / this.fConst328) + 0.93514);
		this.fConst364 = (2 * (0.93514 - this.fConst357));
		this.fConst365 = (this.fConst332 + 0.93514);
		this.fConst366 = Math.tan((494.77 / this.fConst0));
		this.fConst367 = (1 / this.fConst366);
		this.fConst368 = (1 / (((this.fConst367 + 0.157482) / this.fConst366) + 0.93514));
		this.fConst369 = mydsp_faustpower2_f(this.fConst366);
		this.fConst370 = (50.0638 / this.fConst369);
		this.fConst371 = (2 * (0.93514 - this.fConst370));
		this.fConst372 = (1 / (((this.fConst367 + 0.74313) / this.fConst366) + 1.45007));
		this.fConst373 = (11.0521 / this.fConst369);
		this.fConst374 = (2 * (1.45007 - this.fConst373));
		this.fConst375 = (1 / (((this.fConst367 + 3.18973) / this.fConst366) + 4.07678));
		this.fConst376 = (0.00176617 / this.fConst369);
		this.fConst377 = (2 * (0.000407678 - this.fConst376));
		this.fConst378 = (1 / (((this.fConst329 + 0.168405) / this.fConst328) + 1.06936));
		this.fConst379 = (2 * (53.5362 - this.fConst357));
		this.fConst380 = (1 / (((this.fConst329 + 0.512479) / this.fConst328) + 0.689621));
		this.fConst381 = (2 * (7.62173 - this.fConst357));
		this.fConst382 = (1 / (((this.fConst329 + 0.782413) / this.fConst328) + 0.245292));
		this.fConst383 = (0.0001 / this.fConst331);
		this.fConst384 = (2 * (0.000433227 - this.fConst383));
		this.fConst385 = (((this.fConst329 + -0.782413) / this.fConst328) + 0.245292);
		this.fConst386 = (2 * (0.245292 - this.fConst357));
		this.fConst387 = (this.fConst383 + 0.000433227);
		this.fConst388 = (((this.fConst329 + -0.512479) / this.fConst328) + 0.689621);
		this.fConst389 = (2 * (0.689621 - this.fConst357));
		this.fConst390 = (this.fConst357 + 7.62173);
		this.fConst391 = (((this.fConst329 + -0.168405) / this.fConst328) + 1.06936);
		this.fConst392 = (2 * (1.06936 - this.fConst357));
		this.fConst393 = (this.fConst357 + 53.5362);
		this.fConst394 = (((this.fConst367 + -3.18973) / this.fConst366) + 4.07678);
		this.fConst395 = (1 / this.fConst369);
		this.fConst396 = (2 * (4.07678 - this.fConst395));
		this.fConst397 = (this.fConst376 + 0.000407678);
		this.fConst398 = (((this.fConst367 + -0.74313) / this.fConst366) + 1.45007);
		this.fConst399 = (2 * (1.45007 - this.fConst395));
		this.fConst400 = (this.fConst373 + 1.45007);
		this.fConst401 = (((this.fConst367 + -0.157482) / this.fConst366) + 0.93514);
		this.fConst402 = (2 * (0.93514 - this.fConst395));
		this.fConst403 = (this.fConst370 + 0.93514);
		this.fConst404 = Math.tan((311.685 / this.fConst0));
		this.fConst405 = (1 / this.fConst404);
		this.fConst406 = (1 / (((this.fConst405 + 0.157482) / this.fConst404) + 0.93514));
		this.fConst407 = mydsp_faustpower2_f(this.fConst404);
		this.fConst408 = (50.0638 / this.fConst407);
		this.fConst409 = (2 * (0.93514 - this.fConst408));
		this.fConst410 = (1 / (((this.fConst405 + 0.74313) / this.fConst404) + 1.45007));
		this.fConst411 = (11.0521 / this.fConst407);
		this.fConst412 = (2 * (1.45007 - this.fConst411));
		this.fConst413 = (1 / (((this.fConst405 + 3.18973) / this.fConst404) + 4.07678));
		this.fConst414 = (0.00176617 / this.fConst407);
		this.fConst415 = (2 * (0.000407678 - this.fConst414));
		this.fConst416 = (1 / (((this.fConst367 + 0.168405) / this.fConst366) + 1.06936));
		this.fConst417 = (2 * (53.5362 - this.fConst395));
		this.fConst418 = (1 / (((this.fConst367 + 0.512479) / this.fConst366) + 0.689621));
		this.fConst419 = (2 * (7.62173 - this.fConst395));
		this.fConst420 = (1 / (((this.fConst367 + 0.782413) / this.fConst366) + 0.245292));
		this.fConst421 = (0.0001 / this.fConst369);
		this.fConst422 = (2 * (0.000433227 - this.fConst421));
		this.fConst423 = (((this.fConst367 + -0.782413) / this.fConst366) + 0.245292);
		this.fConst424 = (2 * (0.245292 - this.fConst395));
		this.fConst425 = (this.fConst421 + 0.000433227);
		this.fConst426 = (((this.fConst367 + -0.512479) / this.fConst366) + 0.689621);
		this.fConst427 = (2 * (0.689621 - this.fConst395));
		this.fConst428 = (this.fConst395 + 7.62173);
		this.fConst429 = (((this.fConst367 + -0.168405) / this.fConst366) + 1.06936);
		this.fConst430 = (2 * (1.06936 - this.fConst395));
		this.fConst431 = (this.fConst395 + 53.5362);
		this.fConst432 = (((this.fConst405 + -3.18973) / this.fConst404) + 4.07678);
		this.fConst433 = (1 / this.fConst407);
		this.fConst434 = (2 * (4.07678 - this.fConst433));
		this.fConst435 = (this.fConst414 + 0.000407678);
		this.fConst436 = (((this.fConst405 + -0.74313) / this.fConst404) + 1.45007);
		this.fConst437 = (2 * (1.45007 - this.fConst433));
		this.fConst438 = (this.fConst411 + 1.45007);
		this.fConst439 = (((this.fConst405 + -0.157482) / this.fConst404) + 0.93514);
		this.fConst440 = (2 * (0.93514 - this.fConst433));
		this.fConst441 = (this.fConst408 + 0.93514);
		this.fConst442 = Math.tan((196.35 / this.fConst0));
		this.fConst443 = (1 / this.fConst442);
		this.fConst444 = (1 / (((this.fConst443 + 0.157482) / this.fConst442) + 0.93514));
		this.fConst445 = mydsp_faustpower2_f(this.fConst442);
		this.fConst446 = (50.0638 / this.fConst445);
		this.fConst447 = (2 * (0.93514 - this.fConst446));
		this.fConst448 = (1 / (((this.fConst443 + 0.74313) / this.fConst442) + 1.45007));
		this.fConst449 = (11.0521 / this.fConst445);
		this.fConst450 = (2 * (1.45007 - this.fConst449));
		this.fConst451 = (1 / (((this.fConst443 + 3.18973) / this.fConst442) + 4.07678));
		this.fConst452 = (0.00176617 / this.fConst445);
		this.fConst453 = (2 * (0.000407678 - this.fConst452));
		this.fConst454 = (1 / (((this.fConst405 + 0.168405) / this.fConst404) + 1.06936));
		this.fConst455 = (2 * (53.5362 - this.fConst433));
		this.fConst456 = (1 / (((this.fConst405 + 0.512479) / this.fConst404) + 0.689621));
		this.fConst457 = (2 * (7.62173 - this.fConst433));
		this.fConst458 = (1 / (((this.fConst405 + 0.782413) / this.fConst404) + 0.245292));
		this.fConst459 = (0.0001 / this.fConst407);
		this.fConst460 = (2 * (0.000433227 - this.fConst459));
		this.fConst461 = (((this.fConst405 + -0.782413) / this.fConst404) + 0.245292);
		this.fConst462 = (2 * (0.245292 - this.fConst433));
		this.fConst463 = (this.fConst459 + 0.000433227);
		this.fConst464 = (((this.fConst405 + -0.512479) / this.fConst404) + 0.689621);
		this.fConst465 = (2 * (0.689621 - this.fConst433));
		this.fConst466 = (this.fConst433 + 7.62173);
		this.fConst467 = (((this.fConst405 + -0.168405) / this.fConst404) + 1.06936);
		this.fConst468 = (2 * (1.06936 - this.fConst433));
		this.fConst469 = (this.fConst433 + 53.5362);
		this.fConst470 = (((this.fConst443 + -3.18973) / this.fConst442) + 4.07678);
		this.fConst471 = (1 / this.fConst445);
		this.fConst472 = (2 * (4.07678 - this.fConst471));
		this.fConst473 = (this.fConst452 + 0.000407678);
		this.fConst474 = (((this.fConst443 + -0.74313) / this.fConst442) + 1.45007);
		this.fConst475 = (2 * (1.45007 - this.fConst471));
		this.fConst476 = (this.fConst449 + 1.45007);
		this.fConst477 = (((this.fConst443 + -0.157482) / this.fConst442) + 0.93514);
		this.fConst478 = (2 * (0.93514 - this.fConst471));
		this.fConst479 = (this.fConst446 + 0.93514);
		this.fConst480 = Math.tan((123.692 / this.fConst0));
		this.fConst481 = (1 / this.fConst480);
		this.fConst482 = (1 / (((this.fConst481 + 0.157482) / this.fConst480) + 0.93514));
		this.fConst483 = mydsp_faustpower2_f(this.fConst480);
		this.fConst484 = (50.0638 / this.fConst483);
		this.fConst485 = (2 * (0.93514 - this.fConst484));
		this.fConst486 = (1 / (((this.fConst481 + 0.74313) / this.fConst480) + 1.45007));
		this.fConst487 = (11.0521 / this.fConst483);
		this.fConst488 = (2 * (1.45007 - this.fConst487));
		this.fConst489 = (1 / (((this.fConst481 + 3.18973) / this.fConst480) + 4.07678));
		this.fConst490 = (0.00176617 / this.fConst483);
		this.fConst491 = (2 * (0.000407678 - this.fConst490));
		this.fConst492 = (1 / (((this.fConst443 + 0.168405) / this.fConst442) + 1.06936));
		this.fConst493 = (2 * (53.5362 - this.fConst471));
		this.fConst494 = (1 / (((this.fConst443 + 0.512479) / this.fConst442) + 0.689621));
		this.fConst495 = (2 * (7.62173 - this.fConst471));
		this.fConst496 = (1 / (((this.fConst443 + 0.782413) / this.fConst442) + 0.245292));
		this.fConst497 = (0.0001 / this.fConst445);
		this.fConst498 = (2 * (0.000433227 - this.fConst497));
		this.fConst499 = (((this.fConst443 + -0.782413) / this.fConst442) + 0.245292);
		this.fConst500 = (2 * (0.245292 - this.fConst471));
		this.fConst501 = (this.fConst497 + 0.000433227);
		this.fConst502 = (((this.fConst443 + -0.512479) / this.fConst442) + 0.689621);
		this.fConst503 = (2 * (0.689621 - this.fConst471));
		this.fConst504 = (this.fConst471 + 7.62173);
		this.fConst505 = (((this.fConst443 + -0.168405) / this.fConst442) + 1.06936);
		this.fConst506 = (2 * (1.06936 - this.fConst471));
		this.fConst507 = (this.fConst471 + 53.5362);
		this.fConst508 = (((this.fConst481 + -3.18973) / this.fConst480) + 4.07678);
		this.fConst509 = (1 / this.fConst483);
		this.fConst510 = (2 * (4.07678 - this.fConst509));
		this.fConst511 = (this.fConst490 + 0.000407678);
		this.fConst512 = (((this.fConst481 + -0.74313) / this.fConst480) + 1.45007);
		this.fConst513 = (2 * (1.45007 - this.fConst509));
		this.fConst514 = (this.fConst487 + 1.45007);
		this.fConst515 = (((this.fConst481 + -0.157482) / this.fConst480) + 0.93514);
		this.fConst516 = (2 * (0.93514 - this.fConst509));
		this.fConst517 = (this.fConst484 + 0.93514);
		this.fConst518 = (1 / (((this.fConst481 + 0.168405) / this.fConst480) + 1.06936));
		this.fConst519 = (2 * (53.5362 - this.fConst509));
		this.fConst520 = (1 / (((this.fConst481 + 0.512479) / this.fConst480) + 0.689621));
		this.fConst521 = (2 * (7.62173 - this.fConst509));
		this.fConst522 = (1 / (((this.fConst481 + 0.782413) / this.fConst480) + 0.245292));
		this.fConst523 = (0.0001 / this.fConst483);
		this.fConst524 = (2 * (0.000433227 - this.fConst523));
		this.fConst525 = (((this.fConst481 + -0.782413) / this.fConst480) + 0.245292);
		this.fConst526 = (2 * (0.245292 - this.fConst509));
		this.fConst527 = (this.fConst523 + 0.000433227);
		this.fConst528 = (((this.fConst481 + -0.512479) / this.fConst480) + 0.689621);
		this.fConst529 = (2 * (0.689621 - this.fConst509));
		this.fConst530 = (this.fConst509 + 7.62173);
		this.fConst531 = (((this.fConst481 + -0.168405) / this.fConst480) + 1.06936);
		this.fConst532 = (2 * (1.06936 - this.fConst509));
		this.fConst533 = (this.fConst509 + 53.5362);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 50;
		this.fHslider1 = 100;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			this.fRec3[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			this.fRec2[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			this.fRec1[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec0[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.fRec10[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			this.fRec9[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec8[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec7[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec6[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec5[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec4[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec17[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec16[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			this.fRec15[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec14[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			this.fRec13[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			this.fRec12[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec11[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			this.fRec24[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			this.fRec23[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			this.fRec22[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			this.fRec21[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			this.fRec20[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			this.fRec19[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			this.fRec18[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			this.fRec31[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			this.fRec30[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			this.fRec29[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			this.fRec28[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			this.fRec27[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			this.fRec26[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fRec25[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			this.fRec38[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			this.fRec37[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			this.fRec36[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			this.fRec35[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			this.fRec34[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			this.fRec33[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec32[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			this.fRec45[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec44[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			this.fRec43[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			this.fRec42[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec41[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec40[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fRec39[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			this.fRec52[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec51[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec50[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec49[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec48[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec47[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			this.fRec46[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec59[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec58[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec57[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec56[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			this.fRec55[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			this.fRec54[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fRec53[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec66[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec65[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec64[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec63[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			this.fRec62[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			this.fRec61[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			this.fRec60[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec73[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec72[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			this.fRec71[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			this.fRec70[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			this.fRec69[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec68[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			this.fRec67[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec80[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec79[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec78[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			this.fRec77[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			this.fRec76[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec75[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			this.fRec74[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			this.fRec87[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			this.fRec86[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec85[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec84[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			this.fRec83[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec82[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			this.fRec81[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec94[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec93[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec92[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			this.fRec91[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			this.fRec90[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec89[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			this.fRec88[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec98[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec97[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			this.fRec96[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			this.fRec95[l98] = 0;
			
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
		ui_interface.openVerticalBox("spectralLevel");
		ui_interface.declare("0", "0", "");
		ui_interface.declare("0", "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface.openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface.declare("fVbargraph14", "0", "");
		ui_interface.declare("fVbargraph14", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph14", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69c2a370", function handler(obj) { function setval(val) { obj.fVbargraph14 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph13", "1", "");
		ui_interface.declare("fVbargraph13", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph13", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69c18d80", function handler(obj) { function setval(val) { obj.fVbargraph13 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph12", "2", "");
		ui_interface.declare("fVbargraph12", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph12", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69bf3020", function handler(obj) { function setval(val) { obj.fVbargraph12 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph11", "3", "");
		ui_interface.declare("fVbargraph11", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph11", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69bd1240", function handler(obj) { function setval(val) { obj.fVbargraph11 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph10", "4", "");
		ui_interface.declare("fVbargraph10", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph10", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69baf460", function handler(obj) { function setval(val) { obj.fVbargraph10 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph9", "5", "");
		ui_interface.declare("fVbargraph9", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph9", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69b8d680", function handler(obj) { function setval(val) { obj.fVbargraph9 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph8", "6", "");
		ui_interface.declare("fVbargraph8", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph8", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69b6b8a0", function handler(obj) { function setval(val) { obj.fVbargraph8 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph7", "7", "");
		ui_interface.declare("fVbargraph7", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph7", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69b49ac0", function handler(obj) { function setval(val) { obj.fVbargraph7 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph6", "8", "");
		ui_interface.declare("fVbargraph6", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph6", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69b27ce0", function handler(obj) { function setval(val) { obj.fVbargraph6 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph5", "9", "");
		ui_interface.declare("fVbargraph5", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph5", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69b05f00", function handler(obj) { function setval(val) { obj.fVbargraph5 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph4", "10", "");
		ui_interface.declare("fVbargraph4", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph4", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69ae01a0", function handler(obj) { function setval(val) { obj.fVbargraph4 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph3", "11", "");
		ui_interface.declare("fVbargraph3", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph3", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69abe3c0", function handler(obj) { function setval(val) { obj.fVbargraph3 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph2", "12", "");
		ui_interface.declare("fVbargraph2", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph2", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69a9c5e0", function handler(obj) { function setval(val) { obj.fVbargraph2 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph1", "13", "");
		ui_interface.declare("fVbargraph1", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph1", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69a7a800", function handler(obj) { function setval(val) { obj.fVbargraph1 = val; } return setval; }(this), -50, 10);
		ui_interface.declare("fVbargraph0", "14", "");
		ui_interface.declare("fVbargraph0", "tooltip", "Spectral Band Level in dB");
		ui_interface.declare("fVbargraph0", "unit", "dB");
		ui_interface.addVerticalBargraph("0x7ffd69a57850", function handler(obj) { function setval(val) { obj.fVbargraph0 = val; } return setval; }(this), -50, 10);
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
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var fSlow0 = this.fHslider0;
		var fSlow1 = Math.exp((0 - (this.fConst1 / this.fHslider1)));
		var fSlow2 = (1 - fSlow1);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec3[0] = (fTemp0 - (this.fConst11 * ((this.fConst14 * this.fRec3[2]) + (this.fConst16 * this.fRec3[1]))));
			this.fRec2[0] = ((this.fConst11 * (((this.fConst13 * this.fRec3[1]) + (this.fConst17 * this.fRec3[0])) + (this.fConst17 * this.fRec3[2]))) - (this.fConst8 * ((this.fConst18 * this.fRec2[2]) + (this.fConst19 * this.fRec2[1]))));
			this.fRec1[0] = ((this.fConst8 * (((this.fConst10 * this.fRec2[1]) + (this.fConst20 * this.fRec2[0])) + (this.fConst20 * this.fRec2[2]))) - (this.fConst4 * ((this.fConst21 * this.fRec1[2]) + (this.fConst22 * this.fRec1[1]))));
			this.fRec0[0] = ((fSlow1 * this.fRec0[1]) + (fSlow2 * Math.abs((this.fConst4 * (((this.fConst7 * this.fRec1[1]) + (this.fConst23 * this.fRec1[0])) + (this.fConst23 * this.fRec1[2]))))));
			this.fVbargraph0 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec0[0]))));
			this.fRec10[0] = (fTemp0 - (this.fConst40 * ((this.fConst43 * this.fRec10[2]) + (this.fConst44 * this.fRec10[1]))));
			this.fRec9[0] = ((this.fConst40 * (((this.fConst42 * this.fRec10[1]) + (this.fConst45 * this.fRec10[0])) + (this.fConst45 * this.fRec10[2]))) - (this.fConst38 * ((this.fConst46 * this.fRec9[2]) + (this.fConst47 * this.fRec9[1]))));
			this.fRec8[0] = ((this.fConst38 * (((this.fConst39 * this.fRec9[1]) + (this.fConst48 * this.fRec9[0])) + (this.fConst48 * this.fRec9[2]))) - (this.fConst36 * ((this.fConst49 * this.fRec8[2]) + (this.fConst50 * this.fRec8[1]))));
			var fTemp1 = (this.fConst36 * (((this.fConst37 * this.fRec8[1]) + (this.fConst51 * this.fRec8[0])) + (this.fConst51 * this.fRec8[2])));
			this.fRec7[0] = (fTemp1 - (this.fConst33 * ((this.fConst52 * this.fRec7[2]) + (this.fConst54 * this.fRec7[1]))));
			this.fRec6[0] = ((this.fConst33 * (((this.fConst35 * this.fRec7[1]) + (this.fConst55 * this.fRec7[0])) + (this.fConst55 * this.fRec7[2]))) - (this.fConst30 * ((this.fConst56 * this.fRec6[2]) + (this.fConst57 * this.fRec6[1]))));
			this.fRec5[0] = ((this.fConst30 * (((this.fConst32 * this.fRec6[1]) + (this.fConst58 * this.fRec6[0])) + (this.fConst58 * this.fRec6[2]))) - (this.fConst26 * ((this.fConst59 * this.fRec5[2]) + (this.fConst60 * this.fRec5[1]))));
			this.fRec4[0] = ((fSlow1 * this.fRec4[1]) + (fSlow2 * Math.abs((this.fConst26 * (((this.fConst29 * this.fRec5[1]) + (this.fConst61 * this.fRec5[0])) + (this.fConst61 * this.fRec5[2]))))));
			this.fVbargraph1 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec4[0]))));
			this.fRec17[0] = (fTemp1 - (this.fConst78 * ((this.fConst81 * this.fRec17[2]) + (this.fConst82 * this.fRec17[1]))));
			this.fRec16[0] = ((this.fConst78 * (((this.fConst80 * this.fRec17[1]) + (this.fConst83 * this.fRec17[0])) + (this.fConst83 * this.fRec17[2]))) - (this.fConst76 * ((this.fConst84 * this.fRec16[2]) + (this.fConst85 * this.fRec16[1]))));
			this.fRec15[0] = ((this.fConst76 * (((this.fConst77 * this.fRec16[1]) + (this.fConst86 * this.fRec16[0])) + (this.fConst86 * this.fRec16[2]))) - (this.fConst74 * ((this.fConst87 * this.fRec15[2]) + (this.fConst88 * this.fRec15[1]))));
			var fTemp2 = (this.fConst74 * (((this.fConst75 * this.fRec15[1]) + (this.fConst89 * this.fRec15[0])) + (this.fConst89 * this.fRec15[2])));
			this.fRec14[0] = (fTemp2 - (this.fConst71 * ((this.fConst90 * this.fRec14[2]) + (this.fConst92 * this.fRec14[1]))));
			this.fRec13[0] = ((this.fConst71 * (((this.fConst73 * this.fRec14[1]) + (this.fConst93 * this.fRec14[0])) + (this.fConst93 * this.fRec14[2]))) - (this.fConst68 * ((this.fConst94 * this.fRec13[2]) + (this.fConst95 * this.fRec13[1]))));
			this.fRec12[0] = ((this.fConst68 * (((this.fConst70 * this.fRec13[1]) + (this.fConst96 * this.fRec13[0])) + (this.fConst96 * this.fRec13[2]))) - (this.fConst64 * ((this.fConst97 * this.fRec12[2]) + (this.fConst98 * this.fRec12[1]))));
			this.fRec11[0] = ((fSlow1 * this.fRec11[1]) + (fSlow2 * Math.abs((this.fConst64 * (((this.fConst67 * this.fRec12[1]) + (this.fConst99 * this.fRec12[0])) + (this.fConst99 * this.fRec12[2]))))));
			this.fVbargraph2 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec11[0]))));
			this.fRec24[0] = (fTemp2 - (this.fConst116 * ((this.fConst119 * this.fRec24[2]) + (this.fConst120 * this.fRec24[1]))));
			this.fRec23[0] = ((this.fConst116 * (((this.fConst118 * this.fRec24[1]) + (this.fConst121 * this.fRec24[0])) + (this.fConst121 * this.fRec24[2]))) - (this.fConst114 * ((this.fConst122 * this.fRec23[2]) + (this.fConst123 * this.fRec23[1]))));
			this.fRec22[0] = ((this.fConst114 * (((this.fConst115 * this.fRec23[1]) + (this.fConst124 * this.fRec23[0])) + (this.fConst124 * this.fRec23[2]))) - (this.fConst112 * ((this.fConst125 * this.fRec22[2]) + (this.fConst126 * this.fRec22[1]))));
			var fTemp3 = (this.fConst112 * (((this.fConst113 * this.fRec22[1]) + (this.fConst127 * this.fRec22[0])) + (this.fConst127 * this.fRec22[2])));
			this.fRec21[0] = (fTemp3 - (this.fConst109 * ((this.fConst128 * this.fRec21[2]) + (this.fConst130 * this.fRec21[1]))));
			this.fRec20[0] = ((this.fConst109 * (((this.fConst111 * this.fRec21[1]) + (this.fConst131 * this.fRec21[0])) + (this.fConst131 * this.fRec21[2]))) - (this.fConst106 * ((this.fConst132 * this.fRec20[2]) + (this.fConst133 * this.fRec20[1]))));
			this.fRec19[0] = ((this.fConst106 * (((this.fConst108 * this.fRec20[1]) + (this.fConst134 * this.fRec20[0])) + (this.fConst134 * this.fRec20[2]))) - (this.fConst102 * ((this.fConst135 * this.fRec19[2]) + (this.fConst136 * this.fRec19[1]))));
			this.fRec18[0] = ((fSlow1 * this.fRec18[1]) + (fSlow2 * Math.abs((this.fConst102 * (((this.fConst105 * this.fRec19[1]) + (this.fConst137 * this.fRec19[0])) + (this.fConst137 * this.fRec19[2]))))));
			this.fVbargraph3 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec18[0]))));
			this.fRec31[0] = (fTemp3 - (this.fConst154 * ((this.fConst157 * this.fRec31[2]) + (this.fConst158 * this.fRec31[1]))));
			this.fRec30[0] = ((this.fConst154 * (((this.fConst156 * this.fRec31[1]) + (this.fConst159 * this.fRec31[0])) + (this.fConst159 * this.fRec31[2]))) - (this.fConst152 * ((this.fConst160 * this.fRec30[2]) + (this.fConst161 * this.fRec30[1]))));
			this.fRec29[0] = ((this.fConst152 * (((this.fConst153 * this.fRec30[1]) + (this.fConst162 * this.fRec30[0])) + (this.fConst162 * this.fRec30[2]))) - (this.fConst150 * ((this.fConst163 * this.fRec29[2]) + (this.fConst164 * this.fRec29[1]))));
			var fTemp4 = (this.fConst150 * (((this.fConst151 * this.fRec29[1]) + (this.fConst165 * this.fRec29[0])) + (this.fConst165 * this.fRec29[2])));
			this.fRec28[0] = (fTemp4 - (this.fConst147 * ((this.fConst166 * this.fRec28[2]) + (this.fConst168 * this.fRec28[1]))));
			this.fRec27[0] = ((this.fConst147 * (((this.fConst149 * this.fRec28[1]) + (this.fConst169 * this.fRec28[0])) + (this.fConst169 * this.fRec28[2]))) - (this.fConst144 * ((this.fConst170 * this.fRec27[2]) + (this.fConst171 * this.fRec27[1]))));
			this.fRec26[0] = ((this.fConst144 * (((this.fConst146 * this.fRec27[1]) + (this.fConst172 * this.fRec27[0])) + (this.fConst172 * this.fRec27[2]))) - (this.fConst140 * ((this.fConst173 * this.fRec26[2]) + (this.fConst174 * this.fRec26[1]))));
			this.fRec25[0] = ((fSlow1 * this.fRec25[1]) + (fSlow2 * Math.abs((this.fConst140 * (((this.fConst143 * this.fRec26[1]) + (this.fConst175 * this.fRec26[0])) + (this.fConst175 * this.fRec26[2]))))));
			this.fVbargraph4 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec25[0]))));
			this.fRec38[0] = (fTemp4 - (this.fConst192 * ((this.fConst195 * this.fRec38[2]) + (this.fConst196 * this.fRec38[1]))));
			this.fRec37[0] = ((this.fConst192 * (((this.fConst194 * this.fRec38[1]) + (this.fConst197 * this.fRec38[0])) + (this.fConst197 * this.fRec38[2]))) - (this.fConst190 * ((this.fConst198 * this.fRec37[2]) + (this.fConst199 * this.fRec37[1]))));
			this.fRec36[0] = ((this.fConst190 * (((this.fConst191 * this.fRec37[1]) + (this.fConst200 * this.fRec37[0])) + (this.fConst200 * this.fRec37[2]))) - (this.fConst188 * ((this.fConst201 * this.fRec36[2]) + (this.fConst202 * this.fRec36[1]))));
			var fTemp5 = (this.fConst188 * (((this.fConst189 * this.fRec36[1]) + (this.fConst203 * this.fRec36[0])) + (this.fConst203 * this.fRec36[2])));
			this.fRec35[0] = (fTemp5 - (this.fConst185 * ((this.fConst204 * this.fRec35[2]) + (this.fConst206 * this.fRec35[1]))));
			this.fRec34[0] = ((this.fConst185 * (((this.fConst187 * this.fRec35[1]) + (this.fConst207 * this.fRec35[0])) + (this.fConst207 * this.fRec35[2]))) - (this.fConst182 * ((this.fConst208 * this.fRec34[2]) + (this.fConst209 * this.fRec34[1]))));
			this.fRec33[0] = ((this.fConst182 * (((this.fConst184 * this.fRec34[1]) + (this.fConst210 * this.fRec34[0])) + (this.fConst210 * this.fRec34[2]))) - (this.fConst178 * ((this.fConst211 * this.fRec33[2]) + (this.fConst212 * this.fRec33[1]))));
			this.fRec32[0] = ((fSlow1 * this.fRec32[1]) + (fSlow2 * Math.abs((this.fConst178 * (((this.fConst181 * this.fRec33[1]) + (this.fConst213 * this.fRec33[0])) + (this.fConst213 * this.fRec33[2]))))));
			this.fVbargraph5 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec32[0]))));
			this.fRec45[0] = (fTemp5 - (this.fConst230 * ((this.fConst233 * this.fRec45[2]) + (this.fConst234 * this.fRec45[1]))));
			this.fRec44[0] = ((this.fConst230 * (((this.fConst232 * this.fRec45[1]) + (this.fConst235 * this.fRec45[0])) + (this.fConst235 * this.fRec45[2]))) - (this.fConst228 * ((this.fConst236 * this.fRec44[2]) + (this.fConst237 * this.fRec44[1]))));
			this.fRec43[0] = ((this.fConst228 * (((this.fConst229 * this.fRec44[1]) + (this.fConst238 * this.fRec44[0])) + (this.fConst238 * this.fRec44[2]))) - (this.fConst226 * ((this.fConst239 * this.fRec43[2]) + (this.fConst240 * this.fRec43[1]))));
			var fTemp6 = (this.fConst226 * (((this.fConst227 * this.fRec43[1]) + (this.fConst241 * this.fRec43[0])) + (this.fConst241 * this.fRec43[2])));
			this.fRec42[0] = (fTemp6 - (this.fConst223 * ((this.fConst242 * this.fRec42[2]) + (this.fConst244 * this.fRec42[1]))));
			this.fRec41[0] = ((this.fConst223 * (((this.fConst225 * this.fRec42[1]) + (this.fConst245 * this.fRec42[0])) + (this.fConst245 * this.fRec42[2]))) - (this.fConst220 * ((this.fConst246 * this.fRec41[2]) + (this.fConst247 * this.fRec41[1]))));
			this.fRec40[0] = ((this.fConst220 * (((this.fConst222 * this.fRec41[1]) + (this.fConst248 * this.fRec41[0])) + (this.fConst248 * this.fRec41[2]))) - (this.fConst216 * ((this.fConst249 * this.fRec40[2]) + (this.fConst250 * this.fRec40[1]))));
			this.fRec39[0] = ((fSlow1 * this.fRec39[1]) + (fSlow2 * Math.abs((this.fConst216 * (((this.fConst219 * this.fRec40[1]) + (this.fConst251 * this.fRec40[0])) + (this.fConst251 * this.fRec40[2]))))));
			this.fVbargraph6 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec39[0]))));
			this.fRec52[0] = (fTemp6 - (this.fConst268 * ((this.fConst271 * this.fRec52[2]) + (this.fConst272 * this.fRec52[1]))));
			this.fRec51[0] = ((this.fConst268 * (((this.fConst270 * this.fRec52[1]) + (this.fConst273 * this.fRec52[0])) + (this.fConst273 * this.fRec52[2]))) - (this.fConst266 * ((this.fConst274 * this.fRec51[2]) + (this.fConst275 * this.fRec51[1]))));
			this.fRec50[0] = ((this.fConst266 * (((this.fConst267 * this.fRec51[1]) + (this.fConst276 * this.fRec51[0])) + (this.fConst276 * this.fRec51[2]))) - (this.fConst264 * ((this.fConst277 * this.fRec50[2]) + (this.fConst278 * this.fRec50[1]))));
			var fTemp7 = (this.fConst264 * (((this.fConst265 * this.fRec50[1]) + (this.fConst279 * this.fRec50[0])) + (this.fConst279 * this.fRec50[2])));
			this.fRec49[0] = (fTemp7 - (this.fConst261 * ((this.fConst280 * this.fRec49[2]) + (this.fConst282 * this.fRec49[1]))));
			this.fRec48[0] = ((this.fConst261 * (((this.fConst263 * this.fRec49[1]) + (this.fConst283 * this.fRec49[0])) + (this.fConst283 * this.fRec49[2]))) - (this.fConst258 * ((this.fConst284 * this.fRec48[2]) + (this.fConst285 * this.fRec48[1]))));
			this.fRec47[0] = ((this.fConst258 * (((this.fConst260 * this.fRec48[1]) + (this.fConst286 * this.fRec48[0])) + (this.fConst286 * this.fRec48[2]))) - (this.fConst254 * ((this.fConst287 * this.fRec47[2]) + (this.fConst288 * this.fRec47[1]))));
			this.fRec46[0] = ((fSlow1 * this.fRec46[1]) + (fSlow2 * Math.abs((this.fConst254 * (((this.fConst257 * this.fRec47[1]) + (this.fConst289 * this.fRec47[0])) + (this.fConst289 * this.fRec47[2]))))));
			this.fVbargraph7 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec46[0]))));
			this.fRec59[0] = (fTemp7 - (this.fConst306 * ((this.fConst309 * this.fRec59[2]) + (this.fConst310 * this.fRec59[1]))));
			this.fRec58[0] = ((this.fConst306 * (((this.fConst308 * this.fRec59[1]) + (this.fConst311 * this.fRec59[0])) + (this.fConst311 * this.fRec59[2]))) - (this.fConst304 * ((this.fConst312 * this.fRec58[2]) + (this.fConst313 * this.fRec58[1]))));
			this.fRec57[0] = ((this.fConst304 * (((this.fConst305 * this.fRec58[1]) + (this.fConst314 * this.fRec58[0])) + (this.fConst314 * this.fRec58[2]))) - (this.fConst302 * ((this.fConst315 * this.fRec57[2]) + (this.fConst316 * this.fRec57[1]))));
			var fTemp8 = (this.fConst302 * (((this.fConst303 * this.fRec57[1]) + (this.fConst317 * this.fRec57[0])) + (this.fConst317 * this.fRec57[2])));
			this.fRec56[0] = (fTemp8 - (this.fConst299 * ((this.fConst318 * this.fRec56[2]) + (this.fConst320 * this.fRec56[1]))));
			this.fRec55[0] = ((this.fConst299 * (((this.fConst301 * this.fRec56[1]) + (this.fConst321 * this.fRec56[0])) + (this.fConst321 * this.fRec56[2]))) - (this.fConst296 * ((this.fConst322 * this.fRec55[2]) + (this.fConst323 * this.fRec55[1]))));
			this.fRec54[0] = ((this.fConst296 * (((this.fConst298 * this.fRec55[1]) + (this.fConst324 * this.fRec55[0])) + (this.fConst324 * this.fRec55[2]))) - (this.fConst292 * ((this.fConst325 * this.fRec54[2]) + (this.fConst326 * this.fRec54[1]))));
			this.fRec53[0] = ((fSlow1 * this.fRec53[1]) + (fSlow2 * Math.abs((this.fConst292 * (((this.fConst295 * this.fRec54[1]) + (this.fConst327 * this.fRec54[0])) + (this.fConst327 * this.fRec54[2]))))));
			this.fVbargraph8 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec53[0]))));
			this.fRec66[0] = (fTemp8 - (this.fConst344 * ((this.fConst347 * this.fRec66[2]) + (this.fConst348 * this.fRec66[1]))));
			this.fRec65[0] = ((this.fConst344 * (((this.fConst346 * this.fRec66[1]) + (this.fConst349 * this.fRec66[0])) + (this.fConst349 * this.fRec66[2]))) - (this.fConst342 * ((this.fConst350 * this.fRec65[2]) + (this.fConst351 * this.fRec65[1]))));
			this.fRec64[0] = ((this.fConst342 * (((this.fConst343 * this.fRec65[1]) + (this.fConst352 * this.fRec65[0])) + (this.fConst352 * this.fRec65[2]))) - (this.fConst340 * ((this.fConst353 * this.fRec64[2]) + (this.fConst354 * this.fRec64[1]))));
			var fTemp9 = (this.fConst340 * (((this.fConst341 * this.fRec64[1]) + (this.fConst355 * this.fRec64[0])) + (this.fConst355 * this.fRec64[2])));
			this.fRec63[0] = (fTemp9 - (this.fConst337 * ((this.fConst356 * this.fRec63[2]) + (this.fConst358 * this.fRec63[1]))));
			this.fRec62[0] = ((this.fConst337 * (((this.fConst339 * this.fRec63[1]) + (this.fConst359 * this.fRec63[0])) + (this.fConst359 * this.fRec63[2]))) - (this.fConst334 * ((this.fConst360 * this.fRec62[2]) + (this.fConst361 * this.fRec62[1]))));
			this.fRec61[0] = ((this.fConst334 * (((this.fConst336 * this.fRec62[1]) + (this.fConst362 * this.fRec62[0])) + (this.fConst362 * this.fRec62[2]))) - (this.fConst330 * ((this.fConst363 * this.fRec61[2]) + (this.fConst364 * this.fRec61[1]))));
			this.fRec60[0] = ((fSlow1 * this.fRec60[1]) + (fSlow2 * Math.abs((this.fConst330 * (((this.fConst333 * this.fRec61[1]) + (this.fConst365 * this.fRec61[0])) + (this.fConst365 * this.fRec61[2]))))));
			this.fVbargraph9 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec60[0]))));
			this.fRec73[0] = (fTemp9 - (this.fConst382 * ((this.fConst385 * this.fRec73[2]) + (this.fConst386 * this.fRec73[1]))));
			this.fRec72[0] = ((this.fConst382 * (((this.fConst384 * this.fRec73[1]) + (this.fConst387 * this.fRec73[0])) + (this.fConst387 * this.fRec73[2]))) - (this.fConst380 * ((this.fConst388 * this.fRec72[2]) + (this.fConst389 * this.fRec72[1]))));
			this.fRec71[0] = ((this.fConst380 * (((this.fConst381 * this.fRec72[1]) + (this.fConst390 * this.fRec72[0])) + (this.fConst390 * this.fRec72[2]))) - (this.fConst378 * ((this.fConst391 * this.fRec71[2]) + (this.fConst392 * this.fRec71[1]))));
			var fTemp10 = (this.fConst378 * (((this.fConst379 * this.fRec71[1]) + (this.fConst393 * this.fRec71[0])) + (this.fConst393 * this.fRec71[2])));
			this.fRec70[0] = (fTemp10 - (this.fConst375 * ((this.fConst394 * this.fRec70[2]) + (this.fConst396 * this.fRec70[1]))));
			this.fRec69[0] = ((this.fConst375 * (((this.fConst377 * this.fRec70[1]) + (this.fConst397 * this.fRec70[0])) + (this.fConst397 * this.fRec70[2]))) - (this.fConst372 * ((this.fConst398 * this.fRec69[2]) + (this.fConst399 * this.fRec69[1]))));
			this.fRec68[0] = ((this.fConst372 * (((this.fConst374 * this.fRec69[1]) + (this.fConst400 * this.fRec69[0])) + (this.fConst400 * this.fRec69[2]))) - (this.fConst368 * ((this.fConst401 * this.fRec68[2]) + (this.fConst402 * this.fRec68[1]))));
			this.fRec67[0] = ((fSlow1 * this.fRec67[1]) + (fSlow2 * Math.abs((this.fConst368 * (((this.fConst371 * this.fRec68[1]) + (this.fConst403 * this.fRec68[0])) + (this.fConst403 * this.fRec68[2]))))));
			this.fVbargraph10 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec67[0]))));
			this.fRec80[0] = (fTemp10 - (this.fConst420 * ((this.fConst423 * this.fRec80[2]) + (this.fConst424 * this.fRec80[1]))));
			this.fRec79[0] = ((this.fConst420 * (((this.fConst422 * this.fRec80[1]) + (this.fConst425 * this.fRec80[0])) + (this.fConst425 * this.fRec80[2]))) - (this.fConst418 * ((this.fConst426 * this.fRec79[2]) + (this.fConst427 * this.fRec79[1]))));
			this.fRec78[0] = ((this.fConst418 * (((this.fConst419 * this.fRec79[1]) + (this.fConst428 * this.fRec79[0])) + (this.fConst428 * this.fRec79[2]))) - (this.fConst416 * ((this.fConst429 * this.fRec78[2]) + (this.fConst430 * this.fRec78[1]))));
			var fTemp11 = (this.fConst416 * (((this.fConst417 * this.fRec78[1]) + (this.fConst431 * this.fRec78[0])) + (this.fConst431 * this.fRec78[2])));
			this.fRec77[0] = (fTemp11 - (this.fConst413 * ((this.fConst432 * this.fRec77[2]) + (this.fConst434 * this.fRec77[1]))));
			this.fRec76[0] = ((this.fConst413 * (((this.fConst415 * this.fRec77[1]) + (this.fConst435 * this.fRec77[0])) + (this.fConst435 * this.fRec77[2]))) - (this.fConst410 * ((this.fConst436 * this.fRec76[2]) + (this.fConst437 * this.fRec76[1]))));
			this.fRec75[0] = ((this.fConst410 * (((this.fConst412 * this.fRec76[1]) + (this.fConst438 * this.fRec76[0])) + (this.fConst438 * this.fRec76[2]))) - (this.fConst406 * ((this.fConst439 * this.fRec75[2]) + (this.fConst440 * this.fRec75[1]))));
			this.fRec74[0] = ((fSlow1 * this.fRec74[1]) + (fSlow2 * Math.abs((this.fConst406 * (((this.fConst409 * this.fRec75[1]) + (this.fConst441 * this.fRec75[0])) + (this.fConst441 * this.fRec75[2]))))));
			this.fVbargraph11 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec74[0]))));
			this.fRec87[0] = (fTemp11 - (this.fConst458 * ((this.fConst461 * this.fRec87[2]) + (this.fConst462 * this.fRec87[1]))));
			this.fRec86[0] = ((this.fConst458 * (((this.fConst460 * this.fRec87[1]) + (this.fConst463 * this.fRec87[0])) + (this.fConst463 * this.fRec87[2]))) - (this.fConst456 * ((this.fConst464 * this.fRec86[2]) + (this.fConst465 * this.fRec86[1]))));
			this.fRec85[0] = ((this.fConst456 * (((this.fConst457 * this.fRec86[1]) + (this.fConst466 * this.fRec86[0])) + (this.fConst466 * this.fRec86[2]))) - (this.fConst454 * ((this.fConst467 * this.fRec85[2]) + (this.fConst468 * this.fRec85[1]))));
			var fTemp12 = (this.fConst454 * (((this.fConst455 * this.fRec85[1]) + (this.fConst469 * this.fRec85[0])) + (this.fConst469 * this.fRec85[2])));
			this.fRec84[0] = (fTemp12 - (this.fConst451 * ((this.fConst470 * this.fRec84[2]) + (this.fConst472 * this.fRec84[1]))));
			this.fRec83[0] = ((this.fConst451 * (((this.fConst453 * this.fRec84[1]) + (this.fConst473 * this.fRec84[0])) + (this.fConst473 * this.fRec84[2]))) - (this.fConst448 * ((this.fConst474 * this.fRec83[2]) + (this.fConst475 * this.fRec83[1]))));
			this.fRec82[0] = ((this.fConst448 * (((this.fConst450 * this.fRec83[1]) + (this.fConst476 * this.fRec83[0])) + (this.fConst476 * this.fRec83[2]))) - (this.fConst444 * ((this.fConst477 * this.fRec82[2]) + (this.fConst478 * this.fRec82[1]))));
			this.fRec81[0] = ((fSlow1 * this.fRec81[1]) + (fSlow2 * Math.abs((this.fConst444 * (((this.fConst447 * this.fRec82[1]) + (this.fConst479 * this.fRec82[0])) + (this.fConst479 * this.fRec82[2]))))));
			this.fVbargraph12 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec81[0]))));
			this.fRec94[0] = (fTemp12 - (this.fConst496 * ((this.fConst499 * this.fRec94[2]) + (this.fConst500 * this.fRec94[1]))));
			this.fRec93[0] = ((this.fConst496 * (((this.fConst498 * this.fRec94[1]) + (this.fConst501 * this.fRec94[0])) + (this.fConst501 * this.fRec94[2]))) - (this.fConst494 * ((this.fConst502 * this.fRec93[2]) + (this.fConst503 * this.fRec93[1]))));
			this.fRec92[0] = ((this.fConst494 * (((this.fConst495 * this.fRec93[1]) + (this.fConst504 * this.fRec93[0])) + (this.fConst504 * this.fRec93[2]))) - (this.fConst492 * ((this.fConst505 * this.fRec92[2]) + (this.fConst506 * this.fRec92[1]))));
			var fTemp13 = (this.fConst492 * (((this.fConst493 * this.fRec92[1]) + (this.fConst507 * this.fRec92[0])) + (this.fConst507 * this.fRec92[2])));
			this.fRec91[0] = (fTemp13 - (this.fConst489 * ((this.fConst508 * this.fRec91[2]) + (this.fConst510 * this.fRec91[1]))));
			this.fRec90[0] = ((this.fConst489 * (((this.fConst491 * this.fRec91[1]) + (this.fConst511 * this.fRec91[0])) + (this.fConst511 * this.fRec91[2]))) - (this.fConst486 * ((this.fConst512 * this.fRec90[2]) + (this.fConst513 * this.fRec90[1]))));
			this.fRec89[0] = ((this.fConst486 * (((this.fConst488 * this.fRec90[1]) + (this.fConst514 * this.fRec90[0])) + (this.fConst514 * this.fRec90[2]))) - (this.fConst482 * ((this.fConst515 * this.fRec89[2]) + (this.fConst516 * this.fRec89[1]))));
			this.fRec88[0] = ((fSlow1 * this.fRec88[1]) + (fSlow2 * Math.abs((this.fConst482 * (((this.fConst485 * this.fRec89[1]) + (this.fConst517 * this.fRec89[0])) + (this.fConst517 * this.fRec89[2]))))));
			this.fVbargraph13 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec88[0]))));
			this.fRec98[0] = (fTemp13 - (this.fConst522 * ((this.fConst525 * this.fRec98[2]) + (this.fConst526 * this.fRec98[1]))));
			this.fRec97[0] = ((this.fConst522 * (((this.fConst524 * this.fRec98[1]) + (this.fConst527 * this.fRec98[0])) + (this.fConst527 * this.fRec98[2]))) - (this.fConst520 * ((this.fConst528 * this.fRec97[2]) + (this.fConst529 * this.fRec97[1]))));
			this.fRec96[0] = ((this.fConst520 * (((this.fConst521 * this.fRec97[1]) + (this.fConst530 * this.fRec97[0])) + (this.fConst530 * this.fRec97[2]))) - (this.fConst518 * ((this.fConst531 * this.fRec96[2]) + (this.fConst532 * this.fRec96[1]))));
			this.fRec95[0] = ((fSlow1 * this.fRec95[1]) + (fSlow2 * Math.abs((this.fConst518 * (((this.fConst519 * this.fRec96[1]) + (this.fConst533 * this.fRec96[0])) + (this.fConst533 * this.fRec96[2]))))));
			this.fVbargraph14 = (fSlow0 + (20 * function log10(a) { return Math.log(a)/Math.log(10); }(max_f(1e-07, this.fRec95[0]))));
			output0[i] = fTemp0;
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[2] = this.fRec1[1];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
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
			this.fRec4[1] = this.fRec4[0];
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
			this.fRec11[1] = this.fRec11[0];
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
			this.fRec18[1] = this.fRec18[0];
			this.fRec31[2] = this.fRec31[1];
			this.fRec31[1] = this.fRec31[0];
			this.fRec30[2] = this.fRec30[1];
			this.fRec30[1] = this.fRec30[0];
			this.fRec29[2] = this.fRec29[1];
			this.fRec29[1] = this.fRec29[0];
			this.fRec28[2] = this.fRec28[1];
			this.fRec28[1] = this.fRec28[0];
			this.fRec27[2] = this.fRec27[1];
			this.fRec27[1] = this.fRec27[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec25[1] = this.fRec25[0];
			this.fRec38[2] = this.fRec38[1];
			this.fRec38[1] = this.fRec38[0];
			this.fRec37[2] = this.fRec37[1];
			this.fRec37[1] = this.fRec37[0];
			this.fRec36[2] = this.fRec36[1];
			this.fRec36[1] = this.fRec36[0];
			this.fRec35[2] = this.fRec35[1];
			this.fRec35[1] = this.fRec35[0];
			this.fRec34[2] = this.fRec34[1];
			this.fRec34[1] = this.fRec34[0];
			this.fRec33[2] = this.fRec33[1];
			this.fRec33[1] = this.fRec33[0];
			this.fRec32[1] = this.fRec32[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[2] = this.fRec44[1];
			this.fRec44[1] = this.fRec44[0];
			this.fRec43[2] = this.fRec43[1];
			this.fRec43[1] = this.fRec43[0];
			this.fRec42[2] = this.fRec42[1];
			this.fRec42[1] = this.fRec42[0];
			this.fRec41[2] = this.fRec41[1];
			this.fRec41[1] = this.fRec41[0];
			this.fRec40[2] = this.fRec40[1];
			this.fRec40[1] = this.fRec40[0];
			this.fRec39[1] = this.fRec39[0];
			this.fRec52[2] = this.fRec52[1];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[2] = this.fRec51[1];
			this.fRec51[1] = this.fRec51[0];
			this.fRec50[2] = this.fRec50[1];
			this.fRec50[1] = this.fRec50[0];
			this.fRec49[2] = this.fRec49[1];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[2] = this.fRec48[1];
			this.fRec48[1] = this.fRec48[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fRec46[1] = this.fRec46[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[2] = this.fRec58[1];
			this.fRec58[1] = this.fRec58[0];
			this.fRec57[2] = this.fRec57[1];
			this.fRec57[1] = this.fRec57[0];
			this.fRec56[2] = this.fRec56[1];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[2] = this.fRec55[1];
			this.fRec55[1] = this.fRec55[0];
			this.fRec54[2] = this.fRec54[1];
			this.fRec54[1] = this.fRec54[0];
			this.fRec53[1] = this.fRec53[0];
			this.fRec66[2] = this.fRec66[1];
			this.fRec66[1] = this.fRec66[0];
			this.fRec65[2] = this.fRec65[1];
			this.fRec65[1] = this.fRec65[0];
			this.fRec64[2] = this.fRec64[1];
			this.fRec64[1] = this.fRec64[0];
			this.fRec63[2] = this.fRec63[1];
			this.fRec63[1] = this.fRec63[0];
			this.fRec62[2] = this.fRec62[1];
			this.fRec62[1] = this.fRec62[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fRec60[1] = this.fRec60[0];
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
			this.fRec68[2] = this.fRec68[1];
			this.fRec68[1] = this.fRec68[0];
			this.fRec67[1] = this.fRec67[0];
			this.fRec80[2] = this.fRec80[1];
			this.fRec80[1] = this.fRec80[0];
			this.fRec79[2] = this.fRec79[1];
			this.fRec79[1] = this.fRec79[0];
			this.fRec78[2] = this.fRec78[1];
			this.fRec78[1] = this.fRec78[0];
			this.fRec77[2] = this.fRec77[1];
			this.fRec77[1] = this.fRec77[0];
			this.fRec76[2] = this.fRec76[1];
			this.fRec76[1] = this.fRec76[0];
			this.fRec75[2] = this.fRec75[1];
			this.fRec75[1] = this.fRec75[0];
			this.fRec74[1] = this.fRec74[0];
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
			this.fRec81[1] = this.fRec81[0];
			this.fRec94[2] = this.fRec94[1];
			this.fRec94[1] = this.fRec94[0];
			this.fRec93[2] = this.fRec93[1];
			this.fRec93[1] = this.fRec93[0];
			this.fRec92[2] = this.fRec92[1];
			this.fRec92[1] = this.fRec92[0];
			this.fRec91[2] = this.fRec91[1];
			this.fRec91[1] = this.fRec91[0];
			this.fRec90[2] = this.fRec90[1];
			this.fRec90[1] = this.fRec90[0];
			this.fRec89[2] = this.fRec89[1];
			this.fRec89[1] = this.fRec89[0];
			this.fRec88[1] = this.fRec88[0];
			this.fRec98[2] = this.fRec98[1];
			this.fRec98[1] = this.fRec98[0];
			this.fRec97[2] = this.fRec97[1];
			this.fRec97[1] = this.fRec97[0];
			this.fRec96[2] = this.fRec96[1];
			this.fRec96[1] = this.fRec96[0];
			this.fRec95[1] = this.fRec95[0];
			
		}
		
	}
	
}

