
var fmydspSIG0Wave0 = {1.0f,0.776724994f,0.625723004f,0.855223f,0.760159016f,0.69837302f,0.768010974f,0.64112699f,0.244034007f,0.707754016f,0.634012997f,0.247527003f,0.660848975f,0.450396001f,0.567782998f,0.106361002f,0.716813982f,0.663919985f,0.291207999f,0.310598999f,0.801495016f,0.635291994f,0.307435006f,0.874123991f,0.497667998f,0.487087995f,0.459114999f,0.733455002f,0.541818023f,0.441318005f,0.313919991f,0.40309f,0.685352981f,0.603139997f,0.400552005f,0.453511f,0.634386003f,0.291547f,0.131604999f,0.368506998f,0.839906991f,0.602159977f,0.288296014f,0.579670012f,0.0242493004f,0.262746006f,0.368588001f,0.890284002f,0.408962995f,0.556071997f,0.884427011f,0.832109988f,0.612015009f,0.757175982f,0.919476986f,1.0f,0.827962995f,0.89240998f,0.0357408002f,0.480789006f,0.75287199f,0.0546301007f,0.235936999f,0.362937987f,0.444471985f,0.101751f,0.703418016f,0.453135997f,0.316628993f,0.490393996f,0.982508004f,0.551621974f,0.602008998f,0.666957021f,0.776830018f,0.905662f,0.0987197012f,0.402967989f,0.829451978f,0.307644993f,0.640479982f,0.983971f,0.584204972f,0.650364995f,0.334446996f,0.583570004f,0.540190995f,0.672533989f,0.245711997f,0.687298f,0.883058012f,0.792949975f,0.600619018f,0.572682023f,0.122612f,0.388247997f,0.290657997f,0.380255014f,0.290966988f,0.567818999f,0.0737721026f,0.42098999f,0.0786577985f,0.393994987f,0.268983006f,0.260614008f,0.494085997f,0.238025993f,0.0987823978f,0.277879f,0.440562993f,0.0770211965f,0.450590998f,0.128137007f,0.0368275009f,0.128699005f,0.329605013f,0.374511987f,0.363590002f,0.272594005f,0.379052013f,0.305240989f,0.0741128996f,0.34572801f,0.299349993f,0.221284002f,0.0261390992f,0.293202013f,0.361885011f,0.114330001f,0.239004999f,0.434156001f,0.329582989f,0.219459996f,0.284175009f,0.198554993f,0.431975991f,0.302985013f,1.0f,0.146220997f,0.140700996f,0.264243007f,0.185996994f,0.426322013f,0.304780006f,0.343989998f,0.195429996f,0.386954993f,0.187600002f,0.172812f,0.0434115008f,0.303761005f,0.0694539994f,0.453943014f,0.832450986f,0.317817003f,0.940600991f,1.0f,0.180657998f,0.737921f,0.832297027f,0.402352005f,0.126785994f,0.594398022f,0.485455006f,0.324470013f,0.365101993f,0.777921975f,0.588271976f,0.401353002f,0.610734999f,0.158693001f,0.0746072009f,0.825098991f,0.925459027f,0.65377003f,0.260791987f,0.719384015f,0.559907973f,0.372590005f,0.360035002f,0.622938991f,0.210271001f,0.444595009f,0.311286002f,0.464309007f,0.557231009f,0.524079978f,0.0701055974f,0.320749015f,0.194460005f,0.727608979f,0.522062004f,0.394003987f,0.235035002f,0.395646006f,0.494796008f,0.51731801f,0.109751999f,0.69284898f,0.00632009003f,0.0207582992f,0.00306107011f,0.0637191013f,0.0816610008f,0.0351100005f,0.127813995f,0.202294007f,0.0764145032f,0.263126999f,0.400198996f,0.267277986f,0.633385003f,1.0f,0.73990202f,0.413762987f,0.418110013f,0.612715006f,0.67237401f,0.339673996f,0.211720005f,0.459645003f,0.102499999f,0.325890005f,0.148154005f,0.265442014f,0.0974304974f,0.286437988f,0.275213003f,0.109111004f,0.575088978f,0.370283008f,0.29411f,0.259826005f,0.0648718998f,0.583418012f,0.282662988f,0.182004005f,0.117421001f,0.417726994f,0.169650003f,0.24853f,0.122818999f,0.185486004f,0.0433618017f,0.373849005f,0.25276801f,0.195103005f,0.0927835032f,0.166543007f};

function mydspSIG0() {
	
	this.fmydspSIG0Wave0_idx;
	
	this.getNumInputsmydspSIG0 = function() {
		return 0;
		
	}
	this.getNumOutputsmydspSIG0 = function() {
		return 1;
		
	}
	this.getInputRatemydspSIG0 = function(channel) {
		var rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	this.getOutputRatemydspSIG0 = function(channel) {
		var rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	this.instanceInitmydspSIG0 = function(samplingFreq) {
		this.fmydspSIG0Wave0_idx = 0;
		
	}
	
	this.fillmydspSIG0 = function(count, output) {
		for (var i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG0Wave0[this.fmydspSIG0Wave0_idx];
			this.fmydspSIG0Wave0_idx = ((1 + this.fmydspSIG0Wave0_idx) % 250);
			
		}
		
	}
}

newmydspSIG0 = function() { return new mydspSIG0(); }
deletemydspSIG0= function(dsp) {}

this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.max_i = function(dummy0, dummy1);
var ftbl0mydspSIG0 = new Float32Array(250);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fHslider0;
	this.iRec2 = new Int32Array(2);
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fHslider1;
	this.fRec9 = new Float32Array(2);
	this.IOTA;
	this.fVec0 = new Float32Array(2048);
	this.fConst2;
	this.fRec6 = new Float32Array(2);
	this.fRec10 = new Float32Array(2);
	this.fConst3;
	this.fEntry0;
	this.fHslider2;
	this.fConst4;
	this.fHslider3;
	this.fConst5;
	this.fConst6;
	this.fConst7;
	this.fConst8;
	this.iRec14 = new Int32Array(2);
	this.fConst9;
	this.fConst10;
	this.fRec13 = new Float32Array(3);
	this.fConst11;
	this.fRec12 = new Float32Array(3);
	this.fButton0;
	this.fVec1 = new Float32Array(2);
	this.fConst12;
	this.fHslider4;
	this.fVec2 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fConst13;
	this.fConst14;
	this.fConst15;
	this.fConst16;
	this.fConst17;
	this.fConst18;
	this.fRec11 = new Float32Array(3);
	this.fConst19;
	this.fConst20;
	this.fConst21;
	this.fConst22;
	this.fRec16 = new Float32Array(3);
	this.fConst23;
	this.fConst24;
	this.fConst25;
	this.fConst26;
	this.fRec17 = new Float32Array(3);
	this.fConst27;
	this.fConst28;
	this.fConst29;
	this.fConst30;
	this.fRec18 = new Float32Array(3);
	this.fConst31;
	this.fConst32;
	this.fConst33;
	this.fConst34;
	this.fRec19 = new Float32Array(3);
	this.fConst35;
	this.fConst36;
	this.fConst37;
	this.fConst38;
	this.fRec20 = new Float32Array(3);
	this.fConst39;
	this.fConst40;
	this.fConst41;
	this.fConst42;
	this.fRec21 = new Float32Array(3);
	this.fConst43;
	this.fConst44;
	this.fConst45;
	this.fConst46;
	this.fRec22 = new Float32Array(3);
	this.fConst47;
	this.fConst48;
	this.fConst49;
	this.fConst50;
	this.fRec23 = new Float32Array(3);
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fConst54;
	this.fRec24 = new Float32Array(3);
	this.fConst55;
	this.fConst56;
	this.fConst57;
	this.fConst58;
	this.fRec25 = new Float32Array(3);
	this.fConst59;
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fRec26 = new Float32Array(3);
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fConst66;
	this.fRec27 = new Float32Array(3);
	this.fConst67;
	this.fConst68;
	this.fConst69;
	this.fConst70;
	this.fRec28 = new Float32Array(3);
	this.fConst71;
	this.fConst72;
	this.fConst73;
	this.fConst74;
	this.fRec29 = new Float32Array(3);
	this.fConst75;
	this.fConst76;
	this.fConst77;
	this.fConst78;
	this.fRec30 = new Float32Array(3);
	this.fConst79;
	this.fConst80;
	this.fConst81;
	this.fConst82;
	this.fRec31 = new Float32Array(3);
	this.fConst83;
	this.fConst84;
	this.fConst85;
	this.fConst86;
	this.fRec32 = new Float32Array(3);
	this.fConst87;
	this.fConst88;
	this.fConst89;
	this.fConst90;
	this.fRec33 = new Float32Array(3);
	this.fConst91;
	this.fConst92;
	this.fConst93;
	this.fConst94;
	this.fRec34 = new Float32Array(3);
	this.fConst95;
	this.fConst96;
	this.fConst97;
	this.fConst98;
	this.fRec35 = new Float32Array(3);
	this.fConst99;
	this.fConst100;
	this.fConst101;
	this.fConst102;
	this.fRec36 = new Float32Array(3);
	this.fConst103;
	this.fConst104;
	this.fConst105;
	this.fConst106;
	this.fRec37 = new Float32Array(3);
	this.fConst107;
	this.fConst108;
	this.fConst109;
	this.fConst110;
	this.fRec38 = new Float32Array(3);
	this.fConst111;
	this.fConst112;
	this.fConst113;
	this.fConst114;
	this.fRec39 = new Float32Array(3);
	this.fConst115;
	this.fConst116;
	this.fConst117;
	this.fConst118;
	this.fRec40 = new Float32Array(3);
	this.fConst119;
	this.fConst120;
	this.fConst121;
	this.fConst122;
	this.fRec41 = new Float32Array(3);
	this.fConst123;
	this.fConst124;
	this.fConst125;
	this.fConst126;
	this.fRec42 = new Float32Array(3);
	this.fConst127;
	this.fConst128;
	this.fConst129;
	this.fConst130;
	this.fRec43 = new Float32Array(3);
	this.fConst131;
	this.fConst132;
	this.fConst133;
	this.fConst134;
	this.fRec44 = new Float32Array(3);
	this.fConst135;
	this.fConst136;
	this.fConst137;
	this.fConst138;
	this.fRec45 = new Float32Array(3);
	this.fConst139;
	this.fConst140;
	this.fConst141;
	this.fConst142;
	this.fRec46 = new Float32Array(3);
	this.fConst143;
	this.fConst144;
	this.fConst145;
	this.fConst146;
	this.fRec47 = new Float32Array(3);
	this.fConst147;
	this.fConst148;
	this.fConst149;
	this.fConst150;
	this.fRec48 = new Float32Array(3);
	this.fConst151;
	this.fConst152;
	this.fConst153;
	this.fConst154;
	this.fRec49 = new Float32Array(3);
	this.fConst155;
	this.fConst156;
	this.fConst157;
	this.fConst158;
	this.fRec50 = new Float32Array(3);
	this.fConst159;
	this.fConst160;
	this.fConst161;
	this.fConst162;
	this.fRec51 = new Float32Array(3);
	this.fConst163;
	this.fConst164;
	this.fConst165;
	this.fConst166;
	this.fRec52 = new Float32Array(3);
	this.fConst167;
	this.fConst168;
	this.fConst169;
	this.fConst170;
	this.fRec53 = new Float32Array(3);
	this.fConst171;
	this.fConst172;
	this.fConst173;
	this.fConst174;
	this.fRec54 = new Float32Array(3);
	this.fConst175;
	this.fConst176;
	this.fConst177;
	this.fConst178;
	this.fRec55 = new Float32Array(3);
	this.fConst179;
	this.fConst180;
	this.fConst181;
	this.fConst182;
	this.fRec56 = new Float32Array(3);
	this.fConst183;
	this.fConst184;
	this.fConst185;
	this.fConst186;
	this.fRec57 = new Float32Array(3);
	this.fConst187;
	this.fConst188;
	this.fConst189;
	this.fConst190;
	this.fRec58 = new Float32Array(3);
	this.fConst191;
	this.fConst192;
	this.fConst193;
	this.fConst194;
	this.fRec59 = new Float32Array(3);
	this.fConst195;
	this.fConst196;
	this.fConst197;
	this.fConst198;
	this.fRec60 = new Float32Array(3);
	this.fConst199;
	this.fConst200;
	this.fConst201;
	this.fConst202;
	this.fRec61 = new Float32Array(3);
	this.fConst203;
	this.fConst204;
	this.fConst205;
	this.fConst206;
	this.fRec62 = new Float32Array(3);
	this.fConst207;
	this.fConst208;
	this.fConst209;
	this.fConst210;
	this.fRec63 = new Float32Array(3);
	this.fConst211;
	this.fConst212;
	this.fConst213;
	this.fConst214;
	this.fRec64 = new Float32Array(3);
	this.fVec3 = new Float32Array(2);
	this.fVec4 = new Float32Array(2048);
	this.fRec7 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m.declare("delays.lib/name", "Faust Delay Library");
		m.declare("delays.lib/version", "0.0");
		m.declare("description", "Simple MIDI-controllable marimba physical model.");
		m.declare("envelopes.lib/author", "GRAME");
		m.declare("envelopes.lib/copyright", "GRAME");
		m.declare("envelopes.lib/license", "LGPL with exception");
		m.declare("envelopes.lib/name", "Faust Envelope Library");
		m.declare("envelopes.lib/version", "0.0");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("license", "MIT");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "MarimbaMIDI");
		m.declare("noises.lib/name", "Faust Noise Generator Library");
		m.declare("noises.lib/version", "0.0");
		m.declare("routes.lib/name", "Faust Signal Routing Library");
		m.declare("routes.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
	}

	this.getNumInputs = function() {
		return 0;
		
	}
	this.getNumOutputs = function() {
		return 2;
		
	}
	this.getInputRate = function(channel) {
		var rate;
		switch (channel) {
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
		var sig0 = newmydspSIG0();
		sig0.instanceInitmydspSIG0(samplingFreq);
		sig0.fillmydspSIG0(250, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	this.instanceConstants = function(samplingFreq) {
		this.fSamplingFreq = samplingFreq;
		this.fConst0 = min_f(192000, max_f(1, this.fSamplingFreq));
		this.fConst1 = (0.00147059 * this.fConst0);
		this.fConst2 = (0.00882353 * this.fConst0);
		this.fConst3 = ((0.5 * this.fConst0) + -1);
		this.fConst4 = (3.14159 / this.fConst0);
		this.fConst5 = Math.tan((31.4159 / this.fConst0));
		this.fConst6 = (1 / this.fConst5);
		this.fConst7 = (1 / (((this.fConst6 + 1.41421) / this.fConst5) + 1));
		this.fConst8 = (1 / mydsp_faustpower2_f(this.fConst5));
		this.fConst9 = (((this.fConst6 + -1.41421) / this.fConst5) + 1);
		this.fConst10 = (2 * (1 - this.fConst8));
		this.fConst11 = (2 * (0 - this.fConst8));
		this.fConst12 = (0.004 * this.fConst0);
		this.fConst13 = (0.002 * this.fConst0);
		this.fConst14 = (500 / this.fConst0);
		this.fConst15 = Math.pow(0.001, (1 / (0.0974743 * this.fConst0)));
		this.fConst16 = (0 - (2 * this.fConst15));
		this.fConst17 = (6.28319 / this.fConst0);
		this.fConst18 = mydsp_faustpower2_f(this.fConst15);
		this.fConst19 = Math.pow(0.001, (1 / (0.0918262 * this.fConst0)));
		this.fConst20 = (0 - (2 * this.fConst19));
		this.fConst21 = (20.8197 / this.fConst0);
		this.fConst22 = mydsp_faustpower2_f(this.fConst19);
		this.fConst23 = Math.pow(0.001, (1 / (0.0905909 * this.fConst0)));
		this.fConst24 = (0 - (2 * this.fConst23));
		this.fConst25 = (24.0941 / this.fConst0);
		this.fConst26 = mydsp_faustpower2_f(this.fConst23);
		this.fConst27 = Math.pow(0.001, (1 / (0.081051 * this.fConst0)));
		this.fConst28 = (0 - (2 * this.fConst27));
		this.fConst29 = (50.6621 / this.fConst0);
		this.fConst30 = mydsp_faustpower2_f(this.fConst27);
		this.fConst31 = Math.pow(0.001, (1 / (0.0781082 * this.fConst0)));
		this.fConst32 = (0 - (2 * this.fConst31));
		this.fConst33 = (59.3622 / this.fConst0);
		this.fConst34 = mydsp_faustpower2_f(this.fConst31);
		this.fConst35 = Math.pow(0.001, (1 / (0.0688086 * this.fConst0)));
		this.fConst36 = (0 - (2 * this.fConst35));
		this.fConst37 = (88.6991 / this.fConst0);
		this.fConst38 = mydsp_faustpower2_f(this.fConst35);
		this.fConst39 = Math.pow(0.001, (1 / (0.0611052 * this.fConst0)));
		this.fConst40 = (0 - (2 * this.fConst39));
		this.fConst41 = (115.51 / this.fConst0);
		this.fConst42 = mydsp_faustpower2_f(this.fConst39);
		this.fConst43 = Math.pow(0.001, (1 / (0.0567183 * this.fConst0)));
		this.fConst44 = (0 - (2 * this.fConst43));
		this.fConst45 = (132.011 / this.fConst0);
		this.fConst46 = mydsp_faustpower2_f(this.fConst43);
		this.fConst47 = Math.pow(0.001, (1 / (0.0488224 * this.fConst0)));
		this.fConst48 = (0 - (2 * this.fConst47));
		this.fConst49 = (164.478 / this.fConst0);
		this.fConst50 = mydsp_faustpower2_f(this.fConst47);
		this.fConst51 = Math.pow(0.001, (1 / (0.0449043 * this.fConst0)));
		this.fConst52 = (0 - (2 * this.fConst51));
		this.fConst53 = (182.177 / this.fConst0);
		this.fConst54 = mydsp_faustpower2_f(this.fConst51);
		this.fConst55 = Math.pow(0.001, (1 / (0.0350424 * this.fConst0)));
		this.fConst56 = (0 - (2 * this.fConst55));
		this.fConst57 = (232.935 / this.fConst0);
		this.fConst58 = mydsp_faustpower2_f(this.fConst55);
		this.fConst59 = Math.pow(0.001, (1 / (0.0341718 * this.fConst0)));
		this.fConst60 = (0 - (2 * this.fConst59));
		this.fConst61 = (237.946 / this.fConst0);
		this.fConst62 = mydsp_faustpower2_f(this.fConst59);
		this.fConst63 = Math.pow(0.001, (1 / (0.0318663 * this.fConst0)));
		this.fConst64 = (0 - (2 * this.fConst63));
		this.fConst65 = (251.726 / this.fConst0);
		this.fConst66 = mydsp_faustpower2_f(this.fConst63);
		this.fConst67 = Math.pow(0.001, (1 / (0.0248363 * this.fConst0)));
		this.fConst68 = (0 - (2 * this.fConst67));
		this.fConst69 = (299.355 / this.fConst0);
		this.fConst70 = mydsp_faustpower2_f(this.fConst67);
		this.fConst71 = Math.pow(0.001, (1 / (0.022136 * this.fConst0)));
		this.fConst72 = (0 - (2 * this.fConst71));
		this.fConst73 = (320.562 / this.fConst0);
		this.fConst74 = mydsp_faustpower2_f(this.fConst71);
		this.fConst75 = Math.pow(0.001, (1 / (0.0210793 * this.fConst0)));
		this.fConst76 = (0 - (2 * this.fConst75));
		this.fConst77 = (329.427 / this.fConst0);
		this.fConst78 = mydsp_faustpower2_f(this.fConst75);
		this.fConst79 = Math.pow(0.001, (1 / (0.0171159 * this.fConst0)));
		this.fConst80 = (0 - (2 * this.fConst79));
		this.fConst81 = (366.222 / this.fConst0);
		this.fConst82 = mydsp_faustpower2_f(this.fConst79);
		this.fConst83 = Math.pow(0.001, (1 / (0.0140852 * this.fConst0)));
		this.fConst84 = (0 - (2 * this.fConst83));
		this.fConst85 = (399.288 / this.fConst0);
		this.fConst86 = mydsp_faustpower2_f(this.fConst83);
		this.fConst87 = Math.pow(0.001, (1 / (0.0131463 * this.fConst0)));
		this.fConst88 = (0 - (2 * this.fConst87));
		this.fConst89 = (410.687 / this.fConst0);
		this.fConst90 = mydsp_faustpower2_f(this.fConst87);
		this.fConst91 = Math.pow(0.001, (1 / (0.0123624 * this.fConst0)));
		this.fConst92 = (0 - (2 * this.fConst91));
		this.fConst93 = (420.714 / this.fConst0);
		this.fConst94 = mydsp_faustpower2_f(this.fConst91);
		this.fConst95 = Math.pow(0.001, (1 / (0.00913602 * this.fConst0)));
		this.fConst96 = (0 - (2 * this.fConst95));
		this.fConst97 = (468.286 / this.fConst0);
		this.fConst98 = mydsp_faustpower2_f(this.fConst95);
		this.fConst99 = Math.pow(0.001, (1 / (0.00767403 * this.fConst0)));
		this.fConst100 = (0 - (2 * this.fConst99));
		this.fConst101 = (494.436 / this.fConst0);
		this.fConst102 = mydsp_faustpower2_f(this.fConst99);
		this.fConst103 = Math.pow(0.001, (1 / (0.00699721 * this.fConst0)));
		this.fConst104 = (0 - (2 * this.fConst103));
		this.fConst105 = (507.917 / this.fConst0);
		this.fConst106 = mydsp_faustpower2_f(this.fConst103);
		this.fConst107 = Math.pow(0.001, (1 / (0.00462675 * this.fConst0)));
		this.fConst108 = (0 - (2 * this.fConst107));
		this.fConst109 = (565.348 / this.fConst0);
		this.fConst110 = mydsp_faustpower2_f(this.fConst107);
		this.fConst111 = Math.pow(0.001, (1 / (0.00401024 * this.fConst0)));
		this.fConst112 = (0 - (2 * this.fConst111));
		this.fConst113 = (584.123 / this.fConst0);
		this.fConst114 = mydsp_faustpower2_f(this.fConst111);
		this.fConst115 = Math.pow(0.001, (1 / (0.00359531 * this.fConst0)));
		this.fConst116 = (0 - (2 * this.fConst115));
		this.fConst117 = (598.105 / this.fConst0);
		this.fConst118 = mydsp_faustpower2_f(this.fConst115);
		this.fConst119 = Math.pow(0.001, (1 / (0.00320503 * this.fConst0)));
		this.fConst120 = (0 - (2 * this.fConst119));
		this.fConst121 = (612.489 / this.fConst0);
		this.fConst122 = mydsp_faustpower2_f(this.fConst119);
		this.fConst123 = Math.pow(0.001, (1 / (0.00156623 * this.fConst0)));
		this.fConst124 = (0 - (2 * this.fConst123));
		this.fConst125 = (695.046 / this.fConst0);
		this.fConst126 = mydsp_faustpower2_f(this.fConst123);
		this.fConst127 = Math.pow(0.001, (1 / (0.00143769 * this.fConst0)));
		this.fConst128 = (0 - (2 * this.fConst127));
		this.fConst129 = (704.15 / this.fConst0);
		this.fConst130 = mydsp_faustpower2_f(this.fConst127);
		this.fConst131 = Math.pow(0.001, (1 / (0.0012933 * this.fConst0)));
		this.fConst132 = (0 - (2 * this.fConst131));
		this.fConst133 = (715.19 / this.fConst0);
		this.fConst134 = mydsp_faustpower2_f(this.fConst131);
		this.fConst135 = Math.pow(0.001, (1 / (0.000912712 * this.fConst0)));
		this.fConst136 = (0 - (2 * this.fConst135));
		this.fConst137 = (749.936 / this.fConst0);
		this.fConst138 = mydsp_faustpower2_f(this.fConst135);
		this.fConst139 = Math.pow(0.001, (1 / (0.000537811 * this.fConst0)));
		this.fConst140 = (0 - (2 * this.fConst139));
		this.fConst141 = (798.247 / this.fConst0);
		this.fConst142 = mydsp_faustpower2_f(this.fConst139);
		this.fConst143 = Math.pow(0.001, (1 / (0.000432563 * this.fConst0)));
		this.fConst144 = (0 - (2 * this.fConst143));
		this.fConst145 = (816.701 / this.fConst0);
		this.fConst146 = mydsp_faustpower2_f(this.fConst143);
		this.fConst147 = Math.pow(0.001, (1 / (0.000362893 * this.fConst0)));
		this.fConst148 = (0 - (2 * this.fConst147));
		this.fConst149 = (831.008 / this.fConst0);
		this.fConst150 = mydsp_faustpower2_f(this.fConst147);
		this.fConst151 = Math.pow(0.001, (1 / (0.000329499 * this.fConst0)));
		this.fConst152 = (0 - (2 * this.fConst151));
		this.fConst153 = (838.661 / this.fConst0);
		this.fConst154 = mydsp_faustpower2_f(this.fConst151);
		this.fConst155 = Math.pow(0.001, (1 / (0.000124247 * this.fConst0)));
		this.fConst156 = (0 - (2 * this.fConst155));
		this.fConst157 = (908.228 / this.fConst0);
		this.fConst158 = mydsp_faustpower2_f(this.fConst155);
		this.fConst159 = Math.pow(0.001, (1 / (7.53836e-05 * this.fConst0)));
		this.fConst160 = (0 - (2 * this.fConst159));
		this.fConst161 = (938.947 / this.fConst0);
		this.fConst162 = mydsp_faustpower2_f(this.fConst159);
		this.fConst163 = Math.pow(0.001, (1 / (5.65756e-05 * this.fConst0)));
		this.fConst164 = (0 - (2 * this.fConst163));
		this.fConst165 = (955.252 / this.fConst0);
		this.fConst166 = mydsp_faustpower2_f(this.fConst163);
		this.fConst167 = Math.pow(0.001, (1 / (4.96454e-05 * this.fConst0)));
		this.fConst168 = (0 - (2 * this.fConst167));
		this.fConst169 = (962.37 / this.fConst0);
		this.fConst170 = mydsp_faustpower2_f(this.fConst167);
		this.fConst171 = Math.pow(0.001, (1 / (3.70567e-05 * this.fConst0)));
		this.fConst172 = (0 - (2 * this.fConst171));
		this.fConst173 = (977.645 / this.fConst0);
		this.fConst174 = mydsp_faustpower2_f(this.fConst171);
		this.fConst175 = Math.pow(0.001, (1 / (2.66114e-05 * this.fConst0)));
		this.fConst176 = (0 - (2 * this.fConst175));
		this.fConst177 = (993.893 / this.fConst0);
		this.fConst178 = mydsp_faustpower2_f(this.fConst175);
		this.fConst179 = Math.pow(0.001, (1 / (5.79888e-06 * this.fConst0)));
		this.fConst180 = (0 - (2 * this.fConst179));
		this.fConst181 = (1056.23 / this.fConst0);
		this.fConst182 = mydsp_faustpower2_f(this.fConst179);
		this.fConst183 = Math.pow(0.001, (1 / (2.8092e-06 * this.fConst0)));
		this.fConst184 = (0 - (2 * this.fConst183));
		this.fConst185 = (1079.85 / this.fConst0);
		this.fConst186 = mydsp_faustpower2_f(this.fConst183);
		this.fConst187 = Math.pow(0.001, (1 / (1.58672e-06 * this.fConst0)));
		this.fConst188 = (0 - (2 * this.fConst187));
		this.fConst189 = (1096.19 / this.fConst0);
		this.fConst190 = mydsp_faustpower2_f(this.fConst187);
		this.fConst191 = Math.pow(0.001, (1 / (4.94039e-07 * this.fConst0)));
		this.fConst192 = (0 - (2 * this.fConst191));
		this.fConst193 = (1124.29 / this.fConst0);
		this.fConst194 = mydsp_faustpower2_f(this.fConst191);
		this.fConst195 = Math.pow(0.001, (1 / (2.19792e-07 * this.fConst0)));
		this.fConst196 = (0 - (2 * this.fConst195));
		this.fConst197 = (1140.29 / this.fConst0);
		this.fConst198 = mydsp_faustpower2_f(this.fConst195);
		this.fConst199 = Math.pow(0.001, (1 / (4.53859e-08 * this.fConst0)));
		this.fConst200 = (0 - (2 * this.fConst199));
		this.fConst201 = (1164.89 / this.fConst0);
		this.fConst202 = mydsp_faustpower2_f(this.fConst199);
		this.fConst203 = Math.pow(0.001, (1 / (1.88245e-09 * this.fConst0)));
		this.fConst204 = (0 - (2 * this.fConst203));
		this.fConst205 = (1196.12 / this.fConst0);
		this.fConst206 = mydsp_faustpower2_f(this.fConst203);
		this.fConst207 = Math.pow(0.001, (1 / (2.61844e-10 * this.fConst0)));
		this.fConst208 = (0 - (2 * this.fConst207));
		this.fConst209 = (1207.57 / this.fConst0);
		this.fConst210 = mydsp_faustpower2_f(this.fConst207);
		this.fConst211 = Math.pow(0.001, (1 / (6.38676e-15 * this.fConst0)));
		this.fConst212 = (0 - (2 * this.fConst211));
		this.fConst213 = (1228.39 / this.fConst0);
		this.fConst214 = mydsp_faustpower2_f(this.fConst211);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.8;
		this.fHslider1 = 440;
		this.fEntry0 = 0;
		this.fHslider2 = 1;
		this.fHslider3 = 6500;
		this.fButton0 = 0;
		this.fHslider4 = 0.5;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.iRec2[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec9[l1] = 0;
			
		}
		this.IOTA = 0;
		for (var l2 = 0; (l2 < 2048); l2 = (l2 + 1)) {
			this.fVec0[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec6[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fRec10[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.iRec14[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec13[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec12[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this.fVec1[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fVec2[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec15[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec11[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec16[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			this.fRec17[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec18[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			this.fRec19[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			this.fRec20[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			this.fRec21[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			this.fRec22[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			this.fRec23[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			this.fRec24[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			this.fRec25[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			this.fRec26[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			this.fRec27[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			this.fRec28[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			this.fRec29[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			this.fRec30[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			this.fRec31[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			this.fRec32[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			this.fRec33[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			this.fRec34[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			this.fRec35[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			this.fRec36[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			this.fRec37[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			this.fRec38[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			this.fRec39[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			this.fRec40[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			this.fRec41[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			this.fRec42[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			this.fRec43[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec44[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			this.fRec45[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			this.fRec46[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec47[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec48[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			this.fRec49[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			this.fRec50[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec51[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec52[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec53[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec54[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec55[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec56[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec57[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			this.fRec58[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec59[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec60[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			this.fRec61[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			this.fRec62[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec63[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec64[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			this.fVec3[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			this.fVec4[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			this.fRec7[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			this.fRec0[l64] = 0;
			
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
		ui_interface.openVerticalBox("marimba");
		ui_interface.declare("0", "0", "");
		ui_interface.openHorizontalBox("midi");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.addHorizontalSlider("freq", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 440, 50, 1000, 0.01);
		ui_interface.declare("fHslider2", "2", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.addHorizontalSlider("gain", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 1, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("0", "1", "");
		ui_interface.openHorizontalBox("otherParams");
		ui_interface.declare("fEntry0", "0", "");
		ui_interface.declare("fEntry0", "midi", "ctrl 1");
		ui_interface.addNumEntry("strikePosition", function handler(obj) { function setval(val) { obj.fEntry0 = val; } return setval; }(this), 0, 0, 4, 1);
		ui_interface.declare("fHslider3", "1", "");
		ui_interface.declare("fHslider3", "midi", "ctrl 1");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("strikeCutOff", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 6500, 20, 20000, 1);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.addHorizontalSlider("outGain", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.8, 0, 1, 0.01);
		ui_interface.declare("fHslider4", "2", "");
		ui_interface.declare("fHslider4", "style", "knob");
		ui_interface.addHorizontalSlider("strikeSharpness", function handler(obj) { function setval(val) { obj.fHslider4 = val; } return setval; }(this), 0.5, 0.01, 5, 0.01);
		ui_interface.closeBox();
		ui_interface.declare("fButton0", "3", "");
		ui_interface.addButton("gate", function handler(obj) { function setval(val) { obj.fButton0 = val; } return setval; }(this));
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = this.fHslider1;
		var fSlow2 = (this.fConst1 * ((340 / fSlow1) + -0.04));
		var fSlow3 = (fSlow2 + -1.49999);
		var fSlow4 = Math.floor(fSlow3);
		var fSlow5 = (fSlow2 + (-1 - fSlow4));
		var fSlow6 = (fSlow2 + (-2 - fSlow4));
		var fSlow7 = (fSlow2 + (-3 - fSlow4));
		var fSlow8 = (fSlow2 + (-4 - fSlow4));
		var fSlow9 = ((((0 - fSlow5) * (0 - (0.5 * fSlow6))) * (0 - (0.333333 * fSlow7))) * (0 - (0.25 * fSlow8)));
		var iSlow10 = fSlow3;
		var iSlow11 = min_f(this.fConst2, max_i(0, iSlow10));
		var fSlow12 = (fSlow2 - fSlow4);
		var fSlow13 = (((0 - fSlow6) * (0 - (0.5 * fSlow7))) * (0 - (0.333333 * fSlow8)));
		var iSlow14 = min_f(this.fConst2, max_i(0, (iSlow10 + 1)));
		var fSlow15 = (0.5 * ((fSlow5 * (0 - fSlow7)) * (0 - (0.5 * fSlow8))));
		var iSlow16 = min_f(this.fConst2, max_i(0, (iSlow10 + 2)));
		var fSlow17 = (fSlow5 * fSlow6);
		var fSlow18 = (0.166667 * (fSlow17 * (0 - fSlow8)));
		var iSlow19 = min_f(this.fConst2, max_i(0, (iSlow10 + 3)));
		var fSlow20 = (0.0416667 * (fSlow17 * fSlow7));
		var iSlow21 = min_f(this.fConst2, max_i(0, (iSlow10 + 4)));
		var iSlow22 = (50 * this.fEntry0);
		var fSlow23 = ((fSlow1 < this.fConst3)?ftbl0mydspSIG0[iSlow22]:0);
		var fSlow24 = Math.tan((this.fConst4 * this.fHslider3));
		var fSlow25 = (1 / fSlow24);
		var fSlow26 = (((fSlow25 + 1.41421) / fSlow24) + 1);
		var fSlow27 = (this.fHslider2 / fSlow26);
		var fSlow28 = (1 / fSlow26);
		var fSlow29 = (2 * (1 - (1 / mydsp_faustpower2_f(fSlow24))));
		var fSlow30 = (((fSlow25 + -1.41421) / fSlow24) + 1);
		var fSlow31 = this.fButton0;
		var fSlow32 = this.fHslider4;
		var fSlow33 = (this.fConst12 * fSlow32);
		var fSlow34 = (this.fConst13 * fSlow32);
		var fSlow35 = (this.fConst14 / fSlow32);
		var fSlow36 = (this.fConst16 * Math.cos((this.fConst17 * fSlow1)));
		var fSlow37 = (((3.31356 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 1)]:0);
		var fSlow38 = (this.fConst20 * Math.cos((this.fConst21 * fSlow1)));
		var fSlow39 = (((3.83469 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 2)]:0);
		var fSlow40 = (this.fConst24 * Math.cos((this.fConst25 * fSlow1)));
		var fSlow41 = (((8.06313 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 3)]:0);
		var fSlow42 = (this.fConst28 * Math.cos((this.fConst29 * fSlow1)));
		var fSlow43 = (((9.44778 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 4)]:0);
		var fSlow44 = (this.fConst32 * Math.cos((this.fConst33 * fSlow1)));
		var fSlow45 = (((14.1169 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 5)]:0);
		var fSlow46 = (this.fConst36 * Math.cos((this.fConst37 * fSlow1)));
		var fSlow47 = (((18.384 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 6)]:0);
		var fSlow48 = (this.fConst40 * Math.cos((this.fConst41 * fSlow1)));
		var fSlow49 = (((21.0102 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 7)]:0);
		var fSlow50 = (this.fConst44 * Math.cos((this.fConst45 * fSlow1)));
		var fSlow51 = (((26.1775 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 8)]:0);
		var fSlow52 = (this.fConst48 * Math.cos((this.fConst49 * fSlow1)));
		var fSlow53 = (((28.9944 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 9)]:0);
		var fSlow54 = (this.fConst52 * Math.cos((this.fConst53 * fSlow1)));
		var fSlow55 = (((37.0728 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 10)]:0);
		var fSlow56 = (this.fConst56 * Math.cos((this.fConst57 * fSlow1)));
		var fSlow57 = (((37.8703 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 11)]:0);
		var fSlow58 = (this.fConst60 * Math.cos((this.fConst61 * fSlow1)));
		var fSlow59 = (((40.0634 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 12)]:0);
		var fSlow60 = (this.fConst64 * Math.cos((this.fConst65 * fSlow1)));
		var fSlow61 = (((47.6439 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 13)]:0);
		var fSlow62 = (this.fConst68 * Math.cos((this.fConst69 * fSlow1)));
		var fSlow63 = (((51.019 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 14)]:0);
		var fSlow64 = (this.fConst72 * Math.cos((this.fConst73 * fSlow1)));
		var fSlow65 = (((52.43 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 15)]:0);
		var fSlow66 = (this.fConst76 * Math.cos((this.fConst77 * fSlow1)));
		var fSlow67 = (((58.286 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 16)]:0);
		var fSlow68 = (this.fConst80 * Math.cos((this.fConst81 * fSlow1)));
		var fSlow69 = (((63.5486 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 17)]:0);
		var fSlow70 = (this.fConst84 * Math.cos((this.fConst85 * fSlow1)));
		var fSlow71 = (((65.3628 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 18)]:0);
		var fSlow72 = (this.fConst88 * Math.cos((this.fConst89 * fSlow1)));
		var fSlow73 = (((66.9587 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 19)]:0);
		var fSlow74 = (this.fConst92 * Math.cos((this.fConst93 * fSlow1)));
		var fSlow75 = (((74.5301 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 20)]:0);
		var fSlow76 = (this.fConst96 * Math.cos((this.fConst97 * fSlow1)));
		var fSlow77 = (((78.692 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 21)]:0);
		var fSlow78 = (this.fConst100 * Math.cos((this.fConst101 * fSlow1)));
		var fSlow79 = (((80.8375 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 22)]:0);
		var fSlow80 = (this.fConst104 * Math.cos((this.fConst105 * fSlow1)));
		var fSlow81 = (((89.978 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 23)]:0);
		var fSlow82 = (this.fConst108 * Math.cos((this.fConst109 * fSlow1)));
		var fSlow83 = (((92.9661 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 24)]:0);
		var fSlow84 = (this.fConst112 * Math.cos((this.fConst113 * fSlow1)));
		var fSlow85 = (((95.1914 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 25)]:0);
		var fSlow86 = (this.fConst116 * Math.cos((this.fConst117 * fSlow1)));
		var fSlow87 = (((97.4807 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 26)]:0);
		var fSlow88 = (this.fConst120 * Math.cos((this.fConst121 * fSlow1)));
		var fSlow89 = (((110.62 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 27)]:0);
		var fSlow90 = (this.fConst124 * Math.cos((this.fConst125 * fSlow1)));
		var fSlow91 = (((112.069 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 28)]:0);
		var fSlow92 = (this.fConst128 * Math.cos((this.fConst129 * fSlow1)));
		var fSlow93 = (((113.826 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 29)]:0);
		var fSlow94 = (this.fConst132 * Math.cos((this.fConst133 * fSlow1)));
		var fSlow95 = (((119.356 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 30)]:0);
		var fSlow96 = (this.fConst136 * Math.cos((this.fConst137 * fSlow1)));
		var fSlow97 = (((127.045 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 31)]:0);
		var fSlow98 = (this.fConst140 * Math.cos((this.fConst141 * fSlow1)));
		var fSlow99 = (((129.982 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 32)]:0);
		var fSlow100 = (this.fConst144 * Math.cos((this.fConst145 * fSlow1)));
		var fSlow101 = (((132.259 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 33)]:0);
		var fSlow102 = (this.fConst148 * Math.cos((this.fConst149 * fSlow1)));
		var fSlow103 = (((133.477 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 34)]:0);
		var fSlow104 = (this.fConst152 * Math.cos((this.fConst153 * fSlow1)));
		var fSlow105 = (((144.549 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 35)]:0);
		var fSlow106 = (this.fConst156 * Math.cos((this.fConst157 * fSlow1)));
		var fSlow107 = (((149.438 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 36)]:0);
		var fSlow108 = (this.fConst160 * Math.cos((this.fConst161 * fSlow1)));
		var fSlow109 = (((152.033 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 37)]:0);
		var fSlow110 = (this.fConst164 * Math.cos((this.fConst165 * fSlow1)));
		var fSlow111 = (((153.166 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 38)]:0);
		var fSlow112 = (this.fConst168 * Math.cos((this.fConst169 * fSlow1)));
		var fSlow113 = (((155.597 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 39)]:0);
		var fSlow114 = (this.fConst172 * Math.cos((this.fConst173 * fSlow1)));
		var fSlow115 = (((158.183 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 40)]:0);
		var fSlow116 = (this.fConst176 * Math.cos((this.fConst177 * fSlow1)));
		var fSlow117 = (((168.105 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 41)]:0);
		var fSlow118 = (this.fConst180 * Math.cos((this.fConst181 * fSlow1)));
		var fSlow119 = (((171.863 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 42)]:0);
		var fSlow120 = (this.fConst184 * Math.cos((this.fConst185 * fSlow1)));
		var fSlow121 = (((174.464 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 43)]:0);
		var fSlow122 = (this.fConst188 * Math.cos((this.fConst189 * fSlow1)));
		var fSlow123 = (((178.937 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 44)]:0);
		var fSlow124 = (this.fConst192 * Math.cos((this.fConst193 * fSlow1)));
		var fSlow125 = (((181.482 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 45)]:0);
		var fSlow126 = (this.fConst196 * Math.cos((this.fConst197 * fSlow1)));
		var fSlow127 = (((185.398 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 46)]:0);
		var fSlow128 = (this.fConst200 * Math.cos((this.fConst201 * fSlow1)));
		var fSlow129 = (((190.369 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 47)]:0);
		var fSlow130 = (this.fConst204 * Math.cos((this.fConst205 * fSlow1)));
		var fSlow131 = (((192.19 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 48)]:0);
		var fSlow132 = (this.fConst208 * Math.cos((this.fConst209 * fSlow1)));
		var fSlow133 = (((195.505 * fSlow1) < this.fConst3)?ftbl0mydspSIG0[(iSlow22 + 49)]:0);
		var fSlow134 = (this.fConst212 * Math.cos((this.fConst213 * fSlow1)));
		for (var i = 0; (i < count); i = (i + 1)) {
			this.iRec2[0] = 0;
			this.fRec9[0] = ((0.95 * this.fRec9[1]) + (0.05 * this.fRec7[1]));
			var fTemp0 = ((0.99 * this.fRec9[0]) + this.iRec2[1]);
			this.fVec0[(this.IOTA & 2047)] = fTemp0;
			this.fRec6[0] = ((fSlow9 * this.fVec0[((this.IOTA - iSlow11) & 2047)]) + (fSlow12 * ((((fSlow13 * this.fVec0[((this.IOTA - iSlow14) & 2047)]) + (fSlow15 * this.fVec0[((this.IOTA - iSlow16) & 2047)])) + (fSlow18 * this.fVec0[((this.IOTA - iSlow19) & 2047)])) + (fSlow20 * this.fVec0[((this.IOTA - iSlow21) & 2047)]))));
			this.fRec10[0] = ((0.95 * this.fRec10[1]) + (0.05 * this.fRec6[1]));
			this.iRec14[0] = ((1103515245 * this.iRec14[1]) + 12345);
			this.fRec13[0] = ((4.65661e-10 * this.iRec14[0]) - (this.fConst7 * ((this.fConst9 * this.fRec13[2]) + (this.fConst10 * this.fRec13[1]))));
			this.fRec12[0] = ((this.fConst7 * (((this.fConst8 * this.fRec13[0]) + (this.fConst11 * this.fRec13[1])) + (this.fConst8 * this.fRec13[2]))) - (fSlow28 * ((fSlow29 * this.fRec12[1]) + (fSlow30 * this.fRec12[2]))));
			this.fVec1[0] = fSlow31;
			this.fVec2[0] = fSlow32;
			this.fRec15[0] = ((((fSlow31 - this.fVec1[1]) > 0) > 0)?0:min_f(fSlow33, ((this.fRec15[1] + (this.fConst12 * (fSlow32 - this.fVec2[1]))) + 1)));
			var iTemp1 = (this.fRec15[0] < fSlow34);
			var fTemp2 = (fSlow27 * ((this.fRec12[2] + (this.fRec12[0] + (2 * this.fRec12[1]))) * (iTemp1?((this.fRec15[0] < 0)?0:(iTemp1?(fSlow35 * this.fRec15[0]):1)):((this.fRec15[0] < fSlow33)?((fSlow35 * (0 - (this.fRec15[0] - fSlow34))) + 1):0))));
			this.fRec11[0] = (fTemp2 - ((fSlow36 * this.fRec11[1]) + (this.fConst18 * this.fRec11[2])));
			this.fRec16[0] = (fTemp2 - ((fSlow38 * this.fRec16[1]) + (this.fConst22 * this.fRec16[2])));
			this.fRec17[0] = (fTemp2 - ((fSlow40 * this.fRec17[1]) + (this.fConst26 * this.fRec17[2])));
			this.fRec18[0] = (fTemp2 - ((fSlow42 * this.fRec18[1]) + (this.fConst30 * this.fRec18[2])));
			this.fRec19[0] = (fTemp2 - ((fSlow44 * this.fRec19[1]) + (this.fConst34 * this.fRec19[2])));
			this.fRec20[0] = (fTemp2 - ((fSlow46 * this.fRec20[1]) + (this.fConst38 * this.fRec20[2])));
			this.fRec21[0] = (fTemp2 - ((fSlow48 * this.fRec21[1]) + (this.fConst42 * this.fRec21[2])));
			this.fRec22[0] = (fTemp2 - ((fSlow50 * this.fRec22[1]) + (this.fConst46 * this.fRec22[2])));
			this.fRec23[0] = (fTemp2 - ((fSlow52 * this.fRec23[1]) + (this.fConst50 * this.fRec23[2])));
			this.fRec24[0] = (fTemp2 - ((fSlow54 * this.fRec24[1]) + (this.fConst54 * this.fRec24[2])));
			this.fRec25[0] = (fTemp2 - ((fSlow56 * this.fRec25[1]) + (this.fConst58 * this.fRec25[2])));
			this.fRec26[0] = (fTemp2 - ((fSlow58 * this.fRec26[1]) + (this.fConst62 * this.fRec26[2])));
			this.fRec27[0] = (fTemp2 - ((fSlow60 * this.fRec27[1]) + (this.fConst66 * this.fRec27[2])));
			this.fRec28[0] = (fTemp2 - ((fSlow62 * this.fRec28[1]) + (this.fConst70 * this.fRec28[2])));
			this.fRec29[0] = (fTemp2 - ((fSlow64 * this.fRec29[1]) + (this.fConst74 * this.fRec29[2])));
			this.fRec30[0] = (fTemp2 - ((fSlow66 * this.fRec30[1]) + (this.fConst78 * this.fRec30[2])));
			this.fRec31[0] = (fTemp2 - ((fSlow68 * this.fRec31[1]) + (this.fConst82 * this.fRec31[2])));
			this.fRec32[0] = (fTemp2 - ((fSlow70 * this.fRec32[1]) + (this.fConst86 * this.fRec32[2])));
			this.fRec33[0] = (fTemp2 - ((fSlow72 * this.fRec33[1]) + (this.fConst90 * this.fRec33[2])));
			this.fRec34[0] = (fTemp2 - ((fSlow74 * this.fRec34[1]) + (this.fConst94 * this.fRec34[2])));
			this.fRec35[0] = (fTemp2 - ((fSlow76 * this.fRec35[1]) + (this.fConst98 * this.fRec35[2])));
			this.fRec36[0] = (fTemp2 - ((fSlow78 * this.fRec36[1]) + (this.fConst102 * this.fRec36[2])));
			this.fRec37[0] = (fTemp2 - ((fSlow80 * this.fRec37[1]) + (this.fConst106 * this.fRec37[2])));
			this.fRec38[0] = (fTemp2 - ((fSlow82 * this.fRec38[1]) + (this.fConst110 * this.fRec38[2])));
			this.fRec39[0] = (fTemp2 - ((fSlow84 * this.fRec39[1]) + (this.fConst114 * this.fRec39[2])));
			this.fRec40[0] = (fTemp2 - ((fSlow86 * this.fRec40[1]) + (this.fConst118 * this.fRec40[2])));
			this.fRec41[0] = (fTemp2 - ((fSlow88 * this.fRec41[1]) + (this.fConst122 * this.fRec41[2])));
			this.fRec42[0] = (fTemp2 - ((fSlow90 * this.fRec42[1]) + (this.fConst126 * this.fRec42[2])));
			this.fRec43[0] = (fTemp2 - ((fSlow92 * this.fRec43[1]) + (this.fConst130 * this.fRec43[2])));
			this.fRec44[0] = (fTemp2 - ((fSlow94 * this.fRec44[1]) + (this.fConst134 * this.fRec44[2])));
			this.fRec45[0] = (fTemp2 - ((fSlow96 * this.fRec45[1]) + (this.fConst138 * this.fRec45[2])));
			this.fRec46[0] = (fTemp2 - ((fSlow98 * this.fRec46[1]) + (this.fConst142 * this.fRec46[2])));
			this.fRec47[0] = (fTemp2 - ((fSlow100 * this.fRec47[1]) + (this.fConst146 * this.fRec47[2])));
			this.fRec48[0] = (fTemp2 - ((fSlow102 * this.fRec48[1]) + (this.fConst150 * this.fRec48[2])));
			this.fRec49[0] = (fTemp2 - ((fSlow104 * this.fRec49[1]) + (this.fConst154 * this.fRec49[2])));
			this.fRec50[0] = (fTemp2 - ((fSlow106 * this.fRec50[1]) + (this.fConst158 * this.fRec50[2])));
			this.fRec51[0] = (fTemp2 - ((fSlow108 * this.fRec51[1]) + (this.fConst162 * this.fRec51[2])));
			this.fRec52[0] = (fTemp2 - ((fSlow110 * this.fRec52[1]) + (this.fConst166 * this.fRec52[2])));
			this.fRec53[0] = (fTemp2 - ((fSlow112 * this.fRec53[1]) + (this.fConst170 * this.fRec53[2])));
			this.fRec54[0] = (fTemp2 - ((fSlow114 * this.fRec54[1]) + (this.fConst174 * this.fRec54[2])));
			this.fRec55[0] = (fTemp2 - ((fSlow116 * this.fRec55[1]) + (this.fConst178 * this.fRec55[2])));
			this.fRec56[0] = (fTemp2 - ((fSlow118 * this.fRec56[1]) + (this.fConst182 * this.fRec56[2])));
			this.fRec57[0] = (fTemp2 - ((fSlow120 * this.fRec57[1]) + (this.fConst186 * this.fRec57[2])));
			this.fRec58[0] = (fTemp2 - ((fSlow122 * this.fRec58[1]) + (this.fConst190 * this.fRec58[2])));
			this.fRec59[0] = (fTemp2 - ((fSlow124 * this.fRec59[1]) + (this.fConst194 * this.fRec59[2])));
			this.fRec60[0] = (fTemp2 - ((fSlow126 * this.fRec60[1]) + (this.fConst198 * this.fRec60[2])));
			this.fRec61[0] = (fTemp2 - ((fSlow128 * this.fRec61[1]) + (this.fConst202 * this.fRec61[2])));
			this.fRec62[0] = (fTemp2 - ((fSlow130 * this.fRec62[1]) + (this.fConst206 * this.fRec62[2])));
			this.fRec63[0] = (fTemp2 - ((fSlow132 * this.fRec63[1]) + (this.fConst210 * this.fRec63[2])));
			this.fRec64[0] = (fTemp2 - ((fSlow134 * this.fRec64[1]) + (this.fConst214 * this.fRec64[2])));
			var fTemp3 = ((((((((((((((((((((((((((((((((((((((((((((((((((fSlow23 * (this.fRec11[0] - this.fRec11[2])) + (fSlow37 * (this.fRec16[0] - this.fRec16[2]))) + (fSlow39 * (this.fRec17[0] - this.fRec17[2]))) + (fSlow41 * (this.fRec18[0] - this.fRec18[2]))) + (fSlow43 * (this.fRec19[0] - this.fRec19[2]))) + (fSlow45 * (this.fRec20[0] - this.fRec20[2]))) + (fSlow47 * (this.fRec21[0] - this.fRec21[2]))) + (fSlow49 * (this.fRec22[0] - this.fRec22[2]))) + (fSlow51 * (this.fRec23[0] - this.fRec23[2]))) + (fSlow53 * (this.fRec24[0] - this.fRec24[2]))) + (fSlow55 * (this.fRec25[0] - this.fRec25[2]))) + (fSlow57 * (this.fRec26[0] - this.fRec26[2]))) + (fSlow59 * (this.fRec27[0] - this.fRec27[2]))) + (fSlow61 * (this.fRec28[0] - this.fRec28[2]))) + (fSlow63 * (this.fRec29[0] - this.fRec29[2]))) + (fSlow65 * (this.fRec30[0] - this.fRec30[2]))) + (fSlow67 * (this.fRec31[0] - this.fRec31[2]))) + (fSlow69 * (this.fRec32[0] - this.fRec32[2]))) + (fSlow71 * (this.fRec33[0] - this.fRec33[2]))) + (fSlow73 * (this.fRec34[0] - this.fRec34[2]))) + (fSlow75 * (this.fRec35[0] - this.fRec35[2]))) + (fSlow77 * (this.fRec36[0] - this.fRec36[2]))) + (fSlow79 * (this.fRec37[0] - this.fRec37[2]))) + (fSlow81 * (this.fRec38[0] - this.fRec38[2]))) + (fSlow83 * (this.fRec39[0] - this.fRec39[2]))) + (fSlow85 * (this.fRec40[0] - this.fRec40[2]))) + (fSlow87 * (this.fRec41[0] - this.fRec41[2]))) + (fSlow89 * (this.fRec42[0] - this.fRec42[2]))) + (fSlow91 * (this.fRec43[0] - this.fRec43[2]))) + (fSlow93 * (this.fRec44[0] - this.fRec44[2]))) + (fSlow95 * (this.fRec45[0] - this.fRec45[2]))) + (fSlow97 * (this.fRec46[0] - this.fRec46[2]))) + (fSlow99 * (this.fRec47[0] - this.fRec47[2]))) + (fSlow101 * (this.fRec48[0] - this.fRec48[2]))) + (fSlow103 * (this.fRec49[0] - this.fRec49[2]))) + (fSlow105 * (this.fRec50[0] - this.fRec50[2]))) + (fSlow107 * (this.fRec51[0] - this.fRec51[2]))) + (fSlow109 * (this.fRec52[0] - this.fRec52[2]))) + (fSlow111 * (this.fRec53[0] - this.fRec53[2]))) + (fSlow113 * (this.fRec54[0] - this.fRec54[2]))) + (fSlow115 * (this.fRec55[0] - this.fRec55[2]))) + (fSlow117 * (this.fRec56[0] - this.fRec56[2]))) + (fSlow119 * (this.fRec57[0] - this.fRec57[2]))) + (fSlow121 * (this.fRec58[0] - this.fRec58[2]))) + (fSlow123 * (this.fRec59[0] - this.fRec59[2]))) + (fSlow125 * (this.fRec60[0] - this.fRec60[2]))) + (fSlow127 * (this.fRec61[0] - this.fRec61[2]))) + (fSlow129 * (this.fRec62[0] - this.fRec62[2]))) + (fSlow131 * (this.fRec63[0] - this.fRec63[2]))) + (fSlow133 * (this.fRec64[0] - this.fRec64[2])));
			this.fVec3[0] = fTemp3;
			var fTemp4 = ((0.99 * this.fRec10[0]) + (0.02 * this.fVec3[1]));
			this.fVec4[(this.IOTA & 2047)] = fTemp4;
			this.fRec7[0] = ((fSlow9 * this.fVec4[((this.IOTA - iSlow11) & 2047)]) + (fSlow12 * ((((fSlow13 * this.fVec4[((this.IOTA - iSlow14) & 2047)]) + (fSlow15 * this.fVec4[((this.IOTA - iSlow16) & 2047)])) + (fSlow18 * this.fVec4[((this.IOTA - iSlow19) & 2047)])) + (fSlow20 * this.fVec4[((this.IOTA - iSlow21) & 2047)]))));
			var iRec8 = 0;
			var fRec3 = this.fRec6[0];
			var fRec4 = this.fRec7[0];
			var fRec5 = (this.fRec7[0] + iRec8);
			this.fRec0[0] = fRec3;
			var fRec1 = fRec5;
			var fTemp5 = (fSlow0 * fRec1);
			output0[i] = fTemp5;
			output1[i] = fTemp5;
			this.iRec2[1] = this.iRec2[0];
			this.fRec9[1] = this.fRec9[0];
			this.IOTA = (this.IOTA + 1);
			this.fRec6[1] = this.fRec6[0];
			this.fRec10[1] = this.fRec10[0];
			this.iRec14[1] = this.iRec14[0];
			this.fRec13[2] = this.fRec13[1];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[2] = this.fRec12[1];
			this.fRec12[1] = this.fRec12[0];
			this.fVec1[1] = this.fVec1[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec11[2] = this.fRec11[1];
			this.fRec11[1] = this.fRec11[0];
			this.fRec16[2] = this.fRec16[1];
			this.fRec16[1] = this.fRec16[0];
			this.fRec17[2] = this.fRec17[1];
			this.fRec17[1] = this.fRec17[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec19[2] = this.fRec19[1];
			this.fRec19[1] = this.fRec19[0];
			this.fRec20[2] = this.fRec20[1];
			this.fRec20[1] = this.fRec20[0];
			this.fRec21[2] = this.fRec21[1];
			this.fRec21[1] = this.fRec21[0];
			this.fRec22[2] = this.fRec22[1];
			this.fRec22[1] = this.fRec22[0];
			this.fRec23[2] = this.fRec23[1];
			this.fRec23[1] = this.fRec23[0];
			this.fRec24[2] = this.fRec24[1];
			this.fRec24[1] = this.fRec24[0];
			this.fRec25[2] = this.fRec25[1];
			this.fRec25[1] = this.fRec25[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec27[2] = this.fRec27[1];
			this.fRec27[1] = this.fRec27[0];
			this.fRec28[2] = this.fRec28[1];
			this.fRec28[1] = this.fRec28[0];
			this.fRec29[2] = this.fRec29[1];
			this.fRec29[1] = this.fRec29[0];
			this.fRec30[2] = this.fRec30[1];
			this.fRec30[1] = this.fRec30[0];
			this.fRec31[2] = this.fRec31[1];
			this.fRec31[1] = this.fRec31[0];
			this.fRec32[2] = this.fRec32[1];
			this.fRec32[1] = this.fRec32[0];
			this.fRec33[2] = this.fRec33[1];
			this.fRec33[1] = this.fRec33[0];
			this.fRec34[2] = this.fRec34[1];
			this.fRec34[1] = this.fRec34[0];
			this.fRec35[2] = this.fRec35[1];
			this.fRec35[1] = this.fRec35[0];
			this.fRec36[2] = this.fRec36[1];
			this.fRec36[1] = this.fRec36[0];
			this.fRec37[2] = this.fRec37[1];
			this.fRec37[1] = this.fRec37[0];
			this.fRec38[2] = this.fRec38[1];
			this.fRec38[1] = this.fRec38[0];
			this.fRec39[2] = this.fRec39[1];
			this.fRec39[1] = this.fRec39[0];
			this.fRec40[2] = this.fRec40[1];
			this.fRec40[1] = this.fRec40[0];
			this.fRec41[2] = this.fRec41[1];
			this.fRec41[1] = this.fRec41[0];
			this.fRec42[2] = this.fRec42[1];
			this.fRec42[1] = this.fRec42[0];
			this.fRec43[2] = this.fRec43[1];
			this.fRec43[1] = this.fRec43[0];
			this.fRec44[2] = this.fRec44[1];
			this.fRec44[1] = this.fRec44[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec46[2] = this.fRec46[1];
			this.fRec46[1] = this.fRec46[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fRec48[2] = this.fRec48[1];
			this.fRec48[1] = this.fRec48[0];
			this.fRec49[2] = this.fRec49[1];
			this.fRec49[1] = this.fRec49[0];
			this.fRec50[2] = this.fRec50[1];
			this.fRec50[1] = this.fRec50[0];
			this.fRec51[2] = this.fRec51[1];
			this.fRec51[1] = this.fRec51[0];
			this.fRec52[2] = this.fRec52[1];
			this.fRec52[1] = this.fRec52[0];
			this.fRec53[2] = this.fRec53[1];
			this.fRec53[1] = this.fRec53[0];
			this.fRec54[2] = this.fRec54[1];
			this.fRec54[1] = this.fRec54[0];
			this.fRec55[2] = this.fRec55[1];
			this.fRec55[1] = this.fRec55[0];
			this.fRec56[2] = this.fRec56[1];
			this.fRec56[1] = this.fRec56[0];
			this.fRec57[2] = this.fRec57[1];
			this.fRec57[1] = this.fRec57[0];
			this.fRec58[2] = this.fRec58[1];
			this.fRec58[1] = this.fRec58[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec60[2] = this.fRec60[1];
			this.fRec60[1] = this.fRec60[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fRec62[2] = this.fRec62[1];
			this.fRec62[1] = this.fRec62[0];
			this.fRec63[2] = this.fRec63[1];
			this.fRec63[1] = this.fRec63[0];
			this.fRec64[2] = this.fRec64[1];
			this.fRec64[1] = this.fRec64[0];
			this.fVec3[1] = this.fVec3[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec0[1] = this.fRec0[0];
			
		}
		
	}
	
}

