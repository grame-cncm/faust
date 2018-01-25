
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fHslider0;
	this.fConst3;
	this.fRec2 = new Float32Array(3);
	this.fConst4;
	this.fConst5;
	this.fHslider1;
	this.fHslider2;
	this.fRec1 = new Float32Array(2);
	this.fRec0 = new Float32Array(2);
	this.fVslider0;
	this.fRec4 = new Float32Array(2);
	this.fConst6;
	this.fHslider3;
	this.fVec0 = new Float32Array(2);
	this.fRec5 = new Float32Array(2);
	this.fRec3 = new Float32Array(3);
	this.fConst7;
	this.fConst8;
	this.fConst9;
	this.fRec6 = new Float32Array(3);
	this.fRec9 = new Float32Array(3);
	this.fConst10;
	this.fRec8 = new Float32Array(2);
	this.fRec7 = new Float32Array(2);
	this.fConst11;
	this.fConst12;
	this.fConst13;
	this.fRec10 = new Float32Array(3);
	this.fRec13 = new Float32Array(3);
	this.fConst14;
	this.fRec12 = new Float32Array(2);
	this.fRec11 = new Float32Array(2);
	this.fConst15;
	this.fConst16;
	this.fConst17;
	this.fRec14 = new Float32Array(3);
	this.fRec17 = new Float32Array(3);
	this.fConst18;
	this.fRec16 = new Float32Array(2);
	this.fRec15 = new Float32Array(2);
	this.fConst19;
	this.fConst20;
	this.fConst21;
	this.fRec18 = new Float32Array(3);
	this.fRec21 = new Float32Array(3);
	this.fConst22;
	this.fRec20 = new Float32Array(2);
	this.fRec19 = new Float32Array(2);
	this.fConst23;
	this.fConst24;
	this.fConst25;
	this.fRec22 = new Float32Array(3);
	this.fRec25 = new Float32Array(3);
	this.fConst26;
	this.fRec24 = new Float32Array(2);
	this.fRec23 = new Float32Array(2);
	this.fConst27;
	this.fConst28;
	this.fConst29;
	this.fRec26 = new Float32Array(3);
	this.fRec29 = new Float32Array(3);
	this.fConst30;
	this.fRec28 = new Float32Array(2);
	this.fRec27 = new Float32Array(2);
	this.fConst31;
	this.fConst32;
	this.fConst33;
	this.fRec30 = new Float32Array(3);
	this.fRec33 = new Float32Array(3);
	this.fConst34;
	this.fRec32 = new Float32Array(2);
	this.fRec31 = new Float32Array(2);
	this.fConst35;
	this.fConst36;
	this.fConst37;
	this.fRec34 = new Float32Array(3);
	this.fRec37 = new Float32Array(3);
	this.fConst38;
	this.fRec36 = new Float32Array(2);
	this.fRec35 = new Float32Array(2);
	this.fConst39;
	this.fConst40;
	this.fConst41;
	this.fRec38 = new Float32Array(3);
	this.fRec41 = new Float32Array(3);
	this.fConst42;
	this.fRec40 = new Float32Array(2);
	this.fRec39 = new Float32Array(2);
	this.fConst43;
	this.fConst44;
	this.fConst45;
	this.fRec42 = new Float32Array(3);
	this.fRec45 = new Float32Array(3);
	this.fConst46;
	this.fRec44 = new Float32Array(2);
	this.fRec43 = new Float32Array(2);
	this.fConst47;
	this.fConst48;
	this.fConst49;
	this.fRec46 = new Float32Array(3);
	this.fRec49 = new Float32Array(3);
	this.fConst50;
	this.fRec48 = new Float32Array(2);
	this.fRec47 = new Float32Array(2);
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fRec50 = new Float32Array(3);
	this.fRec53 = new Float32Array(3);
	this.fConst54;
	this.fRec52 = new Float32Array(2);
	this.fRec51 = new Float32Array(2);
	this.fConst55;
	this.fConst56;
	this.fConst57;
	this.fRec54 = new Float32Array(3);
	this.fRec57 = new Float32Array(3);
	this.fConst58;
	this.fRec56 = new Float32Array(2);
	this.fRec55 = new Float32Array(2);
	this.fConst59;
	this.fConst60;
	this.fConst61;
	this.fRec58 = new Float32Array(3);
	this.fRec61 = new Float32Array(3);
	this.fConst62;
	this.fRec60 = new Float32Array(2);
	this.fRec59 = new Float32Array(2);
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fRec62 = new Float32Array(3);
	this.fRec65 = new Float32Array(3);
	this.fConst66;
	this.fRec64 = new Float32Array(2);
	this.fRec63 = new Float32Array(2);
	this.fConst67;
	this.fConst68;
	this.fConst69;
	this.fRec66 = new Float32Array(3);
	this.fRec69 = new Float32Array(3);
	this.fConst70;
	this.fRec68 = new Float32Array(2);
	this.fRec67 = new Float32Array(2);
	this.fConst71;
	this.fConst72;
	this.fConst73;
	this.fRec70 = new Float32Array(3);
	this.fRec73 = new Float32Array(3);
	this.fConst74;
	this.fRec72 = new Float32Array(2);
	this.fRec71 = new Float32Array(2);
	this.fConst75;
	this.fConst76;
	this.fConst77;
	this.fRec74 = new Float32Array(3);
	this.fRec77 = new Float32Array(3);
	this.fConst78;
	this.fRec76 = new Float32Array(2);
	this.fRec75 = new Float32Array(2);
	this.fConst79;
	this.fConst80;
	this.fConst81;
	this.fRec78 = new Float32Array(3);
	this.fRec81 = new Float32Array(3);
	this.fConst82;
	this.fRec80 = new Float32Array(2);
	this.fRec79 = new Float32Array(2);
	this.fConst83;
	this.fConst84;
	this.fConst85;
	this.fRec82 = new Float32Array(3);
	this.fRec85 = new Float32Array(3);
	this.fConst86;
	this.fRec84 = new Float32Array(2);
	this.fRec83 = new Float32Array(2);
	this.fConst87;
	this.fConst88;
	this.fConst89;
	this.fRec86 = new Float32Array(3);
	this.fRec89 = new Float32Array(3);
	this.fConst90;
	this.fRec88 = new Float32Array(2);
	this.fRec87 = new Float32Array(2);
	this.fConst91;
	this.fConst92;
	this.fConst93;
	this.fRec90 = new Float32Array(3);
	this.fRec93 = new Float32Array(3);
	this.fConst94;
	this.fRec92 = new Float32Array(2);
	this.fRec91 = new Float32Array(2);
	this.fConst95;
	this.fConst96;
	this.fConst97;
	this.fRec94 = new Float32Array(3);
	this.fRec97 = new Float32Array(3);
	this.fConst98;
	this.fRec96 = new Float32Array(2);
	this.fRec95 = new Float32Array(2);
	this.fConst99;
	this.fConst100;
	this.fConst101;
	this.fRec98 = new Float32Array(3);
	this.fRec101 = new Float32Array(3);
	this.fConst102;
	this.fRec100 = new Float32Array(2);
	this.fRec99 = new Float32Array(2);
	this.fConst103;
	this.fConst104;
	this.fConst105;
	this.fRec102 = new Float32Array(3);
	this.fRec105 = new Float32Array(3);
	this.fConst106;
	this.fRec104 = new Float32Array(2);
	this.fRec103 = new Float32Array(2);
	this.fConst107;
	this.fConst108;
	this.fConst109;
	this.fRec106 = new Float32Array(3);
	this.fRec109 = new Float32Array(3);
	this.fConst110;
	this.fRec108 = new Float32Array(2);
	this.fRec107 = new Float32Array(2);
	this.fConst111;
	this.fConst112;
	this.fConst113;
	this.fRec110 = new Float32Array(3);
	this.fRec113 = new Float32Array(3);
	this.fConst114;
	this.fRec112 = new Float32Array(2);
	this.fRec111 = new Float32Array(2);
	this.fConst115;
	this.fConst116;
	this.fConst117;
	this.fRec114 = new Float32Array(3);
	this.fRec117 = new Float32Array(3);
	this.fConst118;
	this.fRec116 = new Float32Array(2);
	this.fRec115 = new Float32Array(2);
	this.fConst119;
	this.fConst120;
	this.fConst121;
	this.fRec118 = new Float32Array(3);
	this.fRec121 = new Float32Array(3);
	this.fConst122;
	this.fRec120 = new Float32Array(2);
	this.fRec119 = new Float32Array(2);
	this.fConst123;
	this.fConst124;
	this.fConst125;
	this.fRec122 = new Float32Array(3);
	this.fRec125 = new Float32Array(3);
	this.fConst126;
	this.fRec124 = new Float32Array(2);
	this.fRec123 = new Float32Array(2);
	this.fConst127;
	this.fConst128;
	this.fConst129;
	this.fRec126 = new Float32Array(3);
	this.fRec129 = new Float32Array(3);
	this.fConst130;
	this.fRec128 = new Float32Array(2);
	this.fRec127 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("author", "RM");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Use example of the vocoder function where an impulse train is used as excitation.");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "Vocoder");
		m.declare("oscillators.lib/name", "Faust Oscillator Library");
		m.declare("oscillators.lib/version", "0.0");
		m.declare("signals.lib/name", "Faust Signal Routing Library");
		m.declare("signals.lib/version", "0.0");
		m.declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m.declare("vaeffects.lib/version", "0.0");
		m.declare("version", "0.0");
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
		this.fConst1 = Math.tan((3189.47 / this.fConst0));
		this.fConst2 = (1 / this.fConst1);
		this.fConst3 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst1))));
		this.fConst4 = (0 - this.fConst2);
		this.fConst5 = (1000 / this.fConst0);
		this.fConst6 = (1 / this.fConst0);
		this.fConst7 = Math.tan((3876 / this.fConst0));
		this.fConst8 = (1 / this.fConst7);
		this.fConst9 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst7))));
		this.fConst10 = (0 - this.fConst8);
		this.fConst11 = Math.tan((4710.3 / this.fConst0));
		this.fConst12 = (1 / this.fConst11);
		this.fConst13 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst11))));
		this.fConst14 = (0 - this.fConst12);
		this.fConst15 = Math.tan((5724.18 / this.fConst0));
		this.fConst16 = (1 / this.fConst15);
		this.fConst17 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst15))));
		this.fConst18 = (0 - this.fConst16);
		this.fConst19 = Math.tan((6956.29 / this.fConst0));
		this.fConst20 = (1 / this.fConst19);
		this.fConst21 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst19))));
		this.fConst22 = (0 - this.fConst20);
		this.fConst23 = Math.tan((8453.61 / this.fConst0));
		this.fConst24 = (1 / this.fConst23);
		this.fConst25 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst23))));
		this.fConst26 = (0 - this.fConst24);
		this.fConst27 = Math.tan((10273.2 / this.fConst0));
		this.fConst28 = (1 / this.fConst27);
		this.fConst29 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst27))));
		this.fConst30 = (0 - this.fConst28);
		this.fConst31 = Math.tan((12484.5 / this.fConst0));
		this.fConst32 = (1 / this.fConst31);
		this.fConst33 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst31))));
		this.fConst34 = (0 - this.fConst32);
		this.fConst35 = Math.tan((15171.8 / this.fConst0));
		this.fConst36 = (1 / this.fConst35);
		this.fConst37 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst35))));
		this.fConst38 = (0 - this.fConst36);
		this.fConst39 = Math.tan((18437.5 / this.fConst0));
		this.fConst40 = (1 / this.fConst39);
		this.fConst41 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst39))));
		this.fConst42 = (0 - this.fConst40);
		this.fConst43 = Math.tan((22406.1 / this.fConst0));
		this.fConst44 = (1 / this.fConst43);
		this.fConst45 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst43))));
		this.fConst46 = (0 - this.fConst44);
		this.fConst47 = Math.tan((27228.9 / this.fConst0));
		this.fConst48 = (1 / this.fConst47);
		this.fConst49 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst47))));
		this.fConst50 = (0 - this.fConst48);
		this.fConst51 = Math.tan((33089.9 / this.fConst0));
		this.fConst52 = (1 / this.fConst51);
		this.fConst53 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst51))));
		this.fConst54 = (0 - this.fConst52);
		this.fConst55 = Math.tan((40212.4 / this.fConst0));
		this.fConst56 = (1 / this.fConst55);
		this.fConst57 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst55))));
		this.fConst58 = (0 - this.fConst56);
		this.fConst59 = Math.tan((95.4453 / this.fConst0));
		this.fConst60 = (1 / this.fConst59);
		this.fConst61 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst59))));
		this.fConst62 = (0 - this.fConst60);
		this.fConst63 = Math.tan((115.99 / this.fConst0));
		this.fConst64 = (1 / this.fConst63);
		this.fConst65 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst63))));
		this.fConst66 = (0 - this.fConst64);
		this.fConst67 = Math.tan((140.956 / this.fConst0));
		this.fConst68 = (1 / this.fConst67);
		this.fConst69 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst67))));
		this.fConst70 = (0 - this.fConst68);
		this.fConst71 = Math.tan((171.297 / this.fConst0));
		this.fConst72 = (1 / this.fConst71);
		this.fConst73 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst71))));
		this.fConst74 = (0 - this.fConst72);
		this.fConst75 = Math.tan((208.168 / this.fConst0));
		this.fConst76 = (1 / this.fConst75);
		this.fConst77 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst75))));
		this.fConst78 = (0 - this.fConst76);
		this.fConst79 = Math.tan((252.975 / this.fConst0));
		this.fConst80 = (1 / this.fConst79);
		this.fConst81 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst79))));
		this.fConst82 = (0 - this.fConst80);
		this.fConst83 = Math.tan((307.427 / this.fConst0));
		this.fConst84 = (1 / this.fConst83);
		this.fConst85 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst83))));
		this.fConst86 = (0 - this.fConst84);
		this.fConst87 = Math.tan((373.6 / this.fConst0));
		this.fConst88 = (1 / this.fConst87);
		this.fConst89 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst87))));
		this.fConst90 = (0 - this.fConst88);
		this.fConst91 = Math.tan((454.017 / this.fConst0));
		this.fConst92 = (1 / this.fConst91);
		this.fConst93 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst91))));
		this.fConst94 = (0 - this.fConst92);
		this.fConst95 = Math.tan((551.743 / this.fConst0));
		this.fConst96 = (1 / this.fConst95);
		this.fConst97 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst95))));
		this.fConst98 = (0 - this.fConst96);
		this.fConst99 = Math.tan((670.504 / this.fConst0));
		this.fConst100 = (1 / this.fConst99);
		this.fConst101 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst99))));
		this.fConst102 = (0 - this.fConst100);
		this.fConst103 = Math.tan((814.828 / this.fConst0));
		this.fConst104 = (1 / this.fConst103);
		this.fConst105 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst103))));
		this.fConst106 = (0 - this.fConst104);
		this.fConst107 = Math.tan((990.218 / this.fConst0));
		this.fConst108 = (1 / this.fConst107);
		this.fConst109 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst107))));
		this.fConst110 = (0 - this.fConst108);
		this.fConst111 = Math.tan((1203.36 / this.fConst0));
		this.fConst112 = (1 / this.fConst111);
		this.fConst113 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst111))));
		this.fConst114 = (0 - this.fConst112);
		this.fConst115 = Math.tan((1462.38 / this.fConst0));
		this.fConst116 = (1 / this.fConst115);
		this.fConst117 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst115))));
		this.fConst118 = (0 - this.fConst116);
		this.fConst119 = Math.tan((1777.15 / this.fConst0));
		this.fConst120 = (1 / this.fConst119);
		this.fConst121 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst119))));
		this.fConst122 = (0 - this.fConst120);
		this.fConst123 = Math.tan((2159.68 / this.fConst0));
		this.fConst124 = (1 / this.fConst123);
		this.fConst125 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst123))));
		this.fConst126 = (0 - this.fConst124);
		this.fConst127 = Math.tan((2624.55 / this.fConst0));
		this.fConst128 = (1 / this.fConst127);
		this.fConst129 = (2 * (1 - (1 / mydsp_faustpower2_f(this.fConst127))));
		this.fConst130 = (0 - this.fConst128);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fHslider0 = 0.5;
		this.fHslider1 = 5;
		this.fHslider2 = 5;
		this.fVslider0 = 0.5;
		this.fHslider3 = 330;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			this.fRec2[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec1[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this.fRec0[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this.fRec4[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this.fVec0[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this.fRec5[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec3[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec6[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec9[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			this.fRec8[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this.fRec7[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec10[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			this.fRec13[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec12[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this.fRec11[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			this.fRec14[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			this.fRec17[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec16[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			this.fRec15[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			this.fRec18[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			this.fRec21[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			this.fRec20[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this.fRec19[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			this.fRec22[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			this.fRec25[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this.fRec24[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this.fRec23[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			this.fRec26[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			this.fRec29[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this.fRec28[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			this.fRec27[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			this.fRec30[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			this.fRec33[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			this.fRec32[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this.fRec31[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			this.fRec34[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			this.fRec37[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this.fRec36[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this.fRec35[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			this.fRec38[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec41[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec40[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec39[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec42[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec45[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fRec44[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec43[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec46[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec49[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			this.fRec48[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			this.fRec47[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec50[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec53[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			this.fRec52[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			this.fRec51[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			this.fRec54[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec57[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			this.fRec56[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			this.fRec55[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			this.fRec58[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec61[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			this.fRec60[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			this.fRec59[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec62[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			this.fRec65[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			this.fRec64[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			this.fRec63[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			this.fRec66[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec69[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			this.fRec68[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			this.fRec67[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			this.fRec70[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec73[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			this.fRec72[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			this.fRec71[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec74[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec77[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			this.fRec76[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			this.fRec75[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec78[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec81[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			this.fRec80[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			this.fRec79[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec82[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec85[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			this.fRec84[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			this.fRec83[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			this.fRec86[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			this.fRec89[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			this.fRec88[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			this.fRec87[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			this.fRec90[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			this.fRec93[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			this.fRec92[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			this.fRec91[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec94[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			this.fRec97[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			this.fRec96[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			this.fRec95[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			this.fRec98[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			this.fRec101[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			this.fRec100[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			this.fRec99[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec102[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			this.fRec105[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			this.fRec104[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			this.fRec103[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec106[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			this.fRec109[l108] = 0;
			
		}
		for (var l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			this.fRec108[l109] = 0;
			
		}
		for (var l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			this.fRec107[l110] = 0;
			
		}
		for (var l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			this.fRec110[l111] = 0;
			
		}
		for (var l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			this.fRec113[l112] = 0;
			
		}
		for (var l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			this.fRec112[l113] = 0;
			
		}
		for (var l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			this.fRec111[l114] = 0;
			
		}
		for (var l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			this.fRec114[l115] = 0;
			
		}
		for (var l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			this.fRec117[l116] = 0;
			
		}
		for (var l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			this.fRec116[l117] = 0;
			
		}
		for (var l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			this.fRec115[l118] = 0;
			
		}
		for (var l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			this.fRec118[l119] = 0;
			
		}
		for (var l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			this.fRec121[l120] = 0;
			
		}
		for (var l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			this.fRec120[l121] = 0;
			
		}
		for (var l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			this.fRec119[l122] = 0;
			
		}
		for (var l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			this.fRec122[l123] = 0;
			
		}
		for (var l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			this.fRec125[l124] = 0;
			
		}
		for (var l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			this.fRec124[l125] = 0;
			
		}
		for (var l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			this.fRec123[l126] = 0;
			
		}
		for (var l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			this.fRec126[l127] = 0;
			
		}
		for (var l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			this.fRec129[l128] = 0;
			
		}
		for (var l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			this.fRec128[l129] = 0;
			
		}
		for (var l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			this.fRec127[l130] = 0;
			
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
		ui_interface.openHorizontalBox("My Vocoder");
		ui_interface.openVerticalBox("Excitation");
		ui_interface.declare("fHslider3", "0", "");
		ui_interface.declare("fHslider3", "style", "knob");
		ui_interface.addHorizontalSlider("Freq", function handler(obj) { function setval(val) { obj.fHslider3 = val; } return setval; }(this), 330, 50, 2000, 0.1);
		ui_interface.declare("fVslider0", "1", "");
		ui_interface.addVerticalSlider("Gain", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), 0.5, 0, 1, 0.01);
		ui_interface.closeBox();
		ui_interface.openVerticalBox("Vocoder");
		ui_interface.declare("fHslider1", "0", "");
		ui_interface.declare("fHslider1", "style", "knob");
		ui_interface.declare("fHslider1", "tooltip", "Attack time in seconds");
		ui_interface.addHorizontalSlider("Attack", function handler(obj) { function setval(val) { obj.fHslider1 = val; } return setval; }(this), 5, 0.1, 100, 0.1);
		ui_interface.declare("fHslider2", "1", "");
		ui_interface.declare("fHslider2", "style", "knob");
		ui_interface.declare("fHslider2", "tooltip", "Release time in seconds");
		ui_interface.addHorizontalSlider("Release", function handler(obj) { function setval(val) { obj.fHslider2 = val; } return setval; }(this), 5, 0.1, 100, 0.1);
		ui_interface.declare("fHslider0", "2", "");
		ui_interface.declare("fHslider0", "style", "knob");
		ui_interface.declare("fHslider0", "tooltip", "Coefficient to adjust the   bandwidth of each band");
		ui_interface.addHorizontalSlider("BW", function handler(obj) { function setval(val) { obj.fHslider0 = val; } return setval; }(this), 0.5, 0.1, 2, 0.001);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var output1 = outputs[1];
		var fSlow0 = this.fHslider0;
		var fSlow1 = (0.177122 * fSlow0);
		var fSlow2 = (1 / ((this.fConst2 * (this.fConst2 + fSlow1)) + 1));
		var fSlow3 = ((this.fConst2 * (this.fConst2 - fSlow1)) + 1);
		var fSlow4 = Math.exp((0 - (this.fConst5 / this.fHslider1)));
		var fSlow5 = Math.exp((0 - (this.fConst5 / this.fHslider2)));
		var fSlow6 = (0.001 * this.fVslider0);
		var fSlow7 = this.fHslider3;
		var fSlow8 = (0.177122 * fSlow0);
		var fSlow9 = (1 / ((this.fConst8 * (this.fConst8 + fSlow8)) + 1));
		var fSlow10 = ((this.fConst8 * (this.fConst8 - fSlow8)) + 1);
		var fSlow11 = (0.177122 * fSlow0);
		var fSlow12 = (1 / ((this.fConst12 * (this.fConst12 + fSlow11)) + 1));
		var fSlow13 = ((this.fConst12 * (this.fConst12 - fSlow11)) + 1);
		var fSlow14 = (1 / ((this.fConst16 * (this.fConst16 + fSlow8)) + 1));
		var fSlow15 = ((this.fConst16 * (this.fConst16 - fSlow8)) + 1);
		var fSlow16 = (1 / ((this.fConst20 * (this.fConst20 + fSlow11)) + 1));
		var fSlow17 = ((this.fConst20 * (this.fConst20 - fSlow11)) + 1);
		var fSlow18 = (0.177122 * fSlow0);
		var fSlow19 = (1 / ((this.fConst24 * (this.fConst24 + fSlow18)) + 1));
		var fSlow20 = ((this.fConst24 * (this.fConst24 - fSlow18)) + 1);
		var fSlow21 = (0.177122 * fSlow0);
		var fSlow22 = (1 / ((this.fConst28 * (this.fConst28 + fSlow21)) + 1));
		var fSlow23 = ((this.fConst28 * (this.fConst28 - fSlow21)) + 1);
		var fSlow24 = (0.177122 * fSlow0);
		var fSlow25 = (1 / ((this.fConst32 * (this.fConst32 + fSlow24)) + 1));
		var fSlow26 = ((this.fConst32 * (this.fConst32 - fSlow24)) + 1);
		var fSlow27 = (0.177122 * fSlow0);
		var fSlow28 = (1 / ((this.fConst36 * (this.fConst36 + fSlow27)) + 1));
		var fSlow29 = ((this.fConst36 * (this.fConst36 - fSlow27)) + 1);
		var fSlow30 = (0.177122 * fSlow0);
		var fSlow31 = (1 / ((this.fConst40 * (this.fConst40 + fSlow30)) + 1));
		var fSlow32 = ((this.fConst40 * (this.fConst40 - fSlow30)) + 1);
		var fSlow33 = (1 / ((this.fConst44 * (this.fConst44 + fSlow24)) + 1));
		var fSlow34 = ((this.fConst44 * (this.fConst44 - fSlow24)) + 1);
		var fSlow35 = (1 / ((this.fConst48 * (this.fConst48 + fSlow8)) + 1));
		var fSlow36 = ((this.fConst48 * (this.fConst48 - fSlow8)) + 1);
		var fSlow37 = (0.177122 * fSlow0);
		var fSlow38 = (1 / ((this.fConst52 * (this.fConst52 + fSlow37)) + 1));
		var fSlow39 = ((this.fConst52 * (this.fConst52 - fSlow37)) + 1);
		var fSlow40 = (1 / ((this.fConst56 * (this.fConst56 + fSlow18)) + 1));
		var fSlow41 = ((this.fConst56 * (this.fConst56 - fSlow18)) + 1);
		var fSlow42 = (1 / ((this.fConst60 * (this.fConst60 + fSlow24)) + 1));
		var fSlow43 = ((this.fConst60 * (this.fConst60 - fSlow24)) + 1);
		var fSlow44 = (0.177122 * fSlow0);
		var fSlow45 = (1 / ((this.fConst64 * (this.fConst64 + fSlow44)) + 1));
		var fSlow46 = ((this.fConst64 * (this.fConst64 - fSlow44)) + 1);
		var fSlow47 = (1 / ((this.fConst68 * (this.fConst68 + fSlow24)) + 1));
		var fSlow48 = ((this.fConst68 * (this.fConst68 - fSlow24)) + 1);
		var fSlow49 = (1 / ((this.fConst72 * (this.fConst72 + fSlow21)) + 1));
		var fSlow50 = ((this.fConst72 * (this.fConst72 - fSlow21)) + 1);
		var fSlow51 = (1 / ((this.fConst76 * (this.fConst76 + fSlow1)) + 1));
		var fSlow52 = ((this.fConst76 * (this.fConst76 - fSlow1)) + 1);
		var fSlow53 = (0.177122 * fSlow0);
		var fSlow54 = (1 / ((this.fConst80 * (this.fConst80 + fSlow53)) + 1));
		var fSlow55 = ((this.fConst80 * (this.fConst80 - fSlow53)) + 1);
		var fSlow56 = (1 / ((this.fConst84 * (this.fConst84 + fSlow11)) + 1));
		var fSlow57 = ((this.fConst84 * (this.fConst84 - fSlow11)) + 1);
		var fSlow58 = (1 / ((this.fConst88 * (this.fConst88 + fSlow24)) + 1));
		var fSlow59 = ((this.fConst88 * (this.fConst88 - fSlow24)) + 1);
		var fSlow60 = (1 / ((this.fConst92 * (this.fConst92 + fSlow1)) + 1));
		var fSlow61 = ((this.fConst92 * (this.fConst92 - fSlow1)) + 1);
		var fSlow62 = (1 / ((this.fConst96 * (this.fConst96 + fSlow44)) + 1));
		var fSlow63 = ((this.fConst96 * (this.fConst96 - fSlow44)) + 1);
		var fSlow64 = (1 / ((this.fConst100 * (this.fConst100 + fSlow27)) + 1));
		var fSlow65 = ((this.fConst100 * (this.fConst100 - fSlow27)) + 1);
		var fSlow66 = (0.177122 * fSlow0);
		var fSlow67 = (1 / ((this.fConst104 * (this.fConst104 + fSlow66)) + 1));
		var fSlow68 = ((this.fConst104 * (this.fConst104 - fSlow66)) + 1);
		var fSlow69 = (1 / ((this.fConst108 * (this.fConst108 + fSlow27)) + 1));
		var fSlow70 = ((this.fConst108 * (this.fConst108 - fSlow27)) + 1);
		var fSlow71 = (1 / ((this.fConst112 * (this.fConst112 + fSlow8)) + 1));
		var fSlow72 = ((this.fConst112 * (this.fConst112 - fSlow8)) + 1);
		var fSlow73 = (1 / ((this.fConst116 * (this.fConst116 + fSlow21)) + 1));
		var fSlow74 = ((this.fConst116 * (this.fConst116 - fSlow21)) + 1);
		var fSlow75 = (1 / ((this.fConst120 * (this.fConst120 + fSlow21)) + 1));
		var fSlow76 = ((this.fConst120 * (this.fConst120 - fSlow21)) + 1);
		var fSlow77 = (1 / ((this.fConst124 * (this.fConst124 + fSlow44)) + 1));
		var fSlow78 = ((this.fConst124 * (this.fConst124 - fSlow44)) + 1);
		var fSlow79 = (0.177122 * fSlow0);
		var fSlow80 = (1 / ((this.fConst128 * (this.fConst128 + fSlow79)) + 1));
		var fSlow81 = ((this.fConst128 * (this.fConst128 - fSlow79)) + 1);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			this.fRec2[0] = (fTemp0 - (fSlow2 * ((this.fConst3 * this.fRec2[1]) + (fSlow3 * this.fRec2[2]))));
			var fTemp1 = Math.abs((fSlow2 * ((this.fConst2 * this.fRec2[0]) + (this.fConst4 * this.fRec2[2]))));
			var fTemp2 = ((this.fRec0[1] > fTemp1)?fSlow5:fSlow4);
			this.fRec1[0] = ((fTemp2 * this.fRec1[1]) + ((1 - fTemp2) * fTemp1));
			this.fRec0[0] = this.fRec1[0];
			this.fRec4[0] = (fSlow6 + (0.999 * this.fRec4[1]));
			this.fVec0[0] = fSlow7;
			var fTemp3 = (this.fRec5[1] + (this.fConst6 * this.fVec0[1]));
			this.fRec5[0] = (fTemp3 - Math.floor(fTemp3));
			var fTemp4 = (this.fRec4[0] * ((this.fRec5[0] - this.fRec5[1]) < 0));
			this.fRec3[0] = (fTemp4 - (fSlow2 * ((fSlow3 * this.fRec3[2]) + (this.fConst3 * this.fRec3[1]))));
			this.fRec6[0] = (fTemp4 - (fSlow9 * ((fSlow10 * this.fRec6[2]) + (this.fConst9 * this.fRec6[1]))));
			this.fRec9[0] = (fTemp0 - (fSlow9 * ((this.fConst9 * this.fRec9[1]) + (fSlow10 * this.fRec9[2]))));
			var fTemp5 = Math.abs((fSlow9 * ((this.fConst8 * this.fRec9[0]) + (this.fConst10 * this.fRec9[2]))));
			var fTemp6 = ((this.fRec7[1] > fTemp5)?fSlow5:fSlow4);
			this.fRec8[0] = ((this.fRec8[1] * fTemp6) + (fTemp5 * (1 - fTemp6)));
			this.fRec7[0] = this.fRec8[0];
			this.fRec10[0] = (fTemp4 - (fSlow12 * ((fSlow13 * this.fRec10[2]) + (this.fConst13 * this.fRec10[1]))));
			this.fRec13[0] = (fTemp0 - (fSlow12 * ((this.fConst13 * this.fRec13[1]) + (fSlow13 * this.fRec13[2]))));
			var fTemp7 = Math.abs((fSlow12 * ((this.fConst12 * this.fRec13[0]) + (this.fConst14 * this.fRec13[2]))));
			var fTemp8 = ((this.fRec11[1] > fTemp7)?fSlow5:fSlow4);
			this.fRec12[0] = ((this.fRec12[1] * fTemp8) + (fTemp7 * (1 - fTemp8)));
			this.fRec11[0] = this.fRec12[0];
			this.fRec14[0] = (fTemp4 - (fSlow14 * ((fSlow15 * this.fRec14[2]) + (this.fConst17 * this.fRec14[1]))));
			this.fRec17[0] = (fTemp0 - (fSlow14 * ((this.fConst17 * this.fRec17[1]) + (fSlow15 * this.fRec17[2]))));
			var fTemp9 = Math.abs((fSlow14 * ((this.fConst16 * this.fRec17[0]) + (this.fConst18 * this.fRec17[2]))));
			var fTemp10 = ((this.fRec15[1] > fTemp9)?fSlow5:fSlow4);
			this.fRec16[0] = ((this.fRec16[1] * fTemp10) + (fTemp9 * (1 - fTemp10)));
			this.fRec15[0] = this.fRec16[0];
			this.fRec18[0] = (fTemp4 - (fSlow16 * ((fSlow17 * this.fRec18[2]) + (this.fConst21 * this.fRec18[1]))));
			this.fRec21[0] = (fTemp0 - (fSlow16 * ((this.fConst21 * this.fRec21[1]) + (fSlow17 * this.fRec21[2]))));
			var fTemp11 = Math.abs((fSlow16 * ((this.fConst20 * this.fRec21[0]) + (this.fConst22 * this.fRec21[2]))));
			var fTemp12 = ((this.fRec19[1] > fTemp11)?fSlow5:fSlow4);
			this.fRec20[0] = ((this.fRec20[1] * fTemp12) + (fTemp11 * (1 - fTemp12)));
			this.fRec19[0] = this.fRec20[0];
			this.fRec22[0] = (fTemp4 - (fSlow19 * ((fSlow20 * this.fRec22[2]) + (this.fConst25 * this.fRec22[1]))));
			this.fRec25[0] = (fTemp0 - (fSlow19 * ((this.fConst25 * this.fRec25[1]) + (fSlow20 * this.fRec25[2]))));
			var fTemp13 = Math.abs((fSlow19 * ((this.fConst24 * this.fRec25[0]) + (this.fConst26 * this.fRec25[2]))));
			var fTemp14 = ((this.fRec23[1] > fTemp13)?fSlow5:fSlow4);
			this.fRec24[0] = ((this.fRec24[1] * fTemp14) + (fTemp13 * (1 - fTemp14)));
			this.fRec23[0] = this.fRec24[0];
			this.fRec26[0] = (fTemp4 - (fSlow22 * ((fSlow23 * this.fRec26[2]) + (this.fConst29 * this.fRec26[1]))));
			this.fRec29[0] = (fTemp0 - (fSlow22 * ((this.fConst29 * this.fRec29[1]) + (fSlow23 * this.fRec29[2]))));
			var fTemp15 = Math.abs((fSlow22 * ((this.fConst28 * this.fRec29[0]) + (this.fConst30 * this.fRec29[2]))));
			var fTemp16 = ((this.fRec27[1] > fTemp15)?fSlow5:fSlow4);
			this.fRec28[0] = ((this.fRec28[1] * fTemp16) + (fTemp15 * (1 - fTemp16)));
			this.fRec27[0] = this.fRec28[0];
			this.fRec30[0] = (fTemp4 - (fSlow25 * ((fSlow26 * this.fRec30[2]) + (this.fConst33 * this.fRec30[1]))));
			this.fRec33[0] = (fTemp0 - (fSlow25 * ((this.fConst33 * this.fRec33[1]) + (fSlow26 * this.fRec33[2]))));
			var fTemp17 = Math.abs((fSlow25 * ((this.fConst32 * this.fRec33[0]) + (this.fConst34 * this.fRec33[2]))));
			var fTemp18 = ((this.fRec31[1] > fTemp17)?fSlow5:fSlow4);
			this.fRec32[0] = ((this.fRec32[1] * fTemp18) + (fTemp17 * (1 - fTemp18)));
			this.fRec31[0] = this.fRec32[0];
			this.fRec34[0] = (fTemp4 - (fSlow28 * ((fSlow29 * this.fRec34[2]) + (this.fConst37 * this.fRec34[1]))));
			this.fRec37[0] = (fTemp0 - (fSlow28 * ((this.fConst37 * this.fRec37[1]) + (fSlow29 * this.fRec37[2]))));
			var fTemp19 = Math.abs((fSlow28 * ((this.fConst36 * this.fRec37[0]) + (this.fConst38 * this.fRec37[2]))));
			var fTemp20 = ((this.fRec35[1] > fTemp19)?fSlow5:fSlow4);
			this.fRec36[0] = ((this.fRec36[1] * fTemp20) + (fTemp19 * (1 - fTemp20)));
			this.fRec35[0] = this.fRec36[0];
			this.fRec38[0] = (fTemp4 - (fSlow31 * ((fSlow32 * this.fRec38[2]) + (this.fConst41 * this.fRec38[1]))));
			this.fRec41[0] = (fTemp0 - (fSlow31 * ((this.fConst41 * this.fRec41[1]) + (fSlow32 * this.fRec41[2]))));
			var fTemp21 = Math.abs((fSlow31 * ((this.fConst40 * this.fRec41[0]) + (this.fConst42 * this.fRec41[2]))));
			var fTemp22 = ((this.fRec39[1] > fTemp21)?fSlow5:fSlow4);
			this.fRec40[0] = ((this.fRec40[1] * fTemp22) + (fTemp21 * (1 - fTemp22)));
			this.fRec39[0] = this.fRec40[0];
			this.fRec42[0] = (fTemp4 - (fSlow33 * ((fSlow34 * this.fRec42[2]) + (this.fConst45 * this.fRec42[1]))));
			this.fRec45[0] = (fTemp0 - (fSlow33 * ((this.fConst45 * this.fRec45[1]) + (fSlow34 * this.fRec45[2]))));
			var fTemp23 = Math.abs((fSlow33 * ((this.fConst44 * this.fRec45[0]) + (this.fConst46 * this.fRec45[2]))));
			var fTemp24 = ((this.fRec43[1] > fTemp23)?fSlow5:fSlow4);
			this.fRec44[0] = ((this.fRec44[1] * fTemp24) + (fTemp23 * (1 - fTemp24)));
			this.fRec43[0] = this.fRec44[0];
			this.fRec46[0] = (fTemp4 - (fSlow35 * ((fSlow36 * this.fRec46[2]) + (this.fConst49 * this.fRec46[1]))));
			this.fRec49[0] = (fTemp0 - (fSlow35 * ((this.fConst49 * this.fRec49[1]) + (fSlow36 * this.fRec49[2]))));
			var fTemp25 = Math.abs((fSlow35 * ((this.fConst48 * this.fRec49[0]) + (this.fConst50 * this.fRec49[2]))));
			var fTemp26 = ((this.fRec47[1] > fTemp25)?fSlow5:fSlow4);
			this.fRec48[0] = ((this.fRec48[1] * fTemp26) + (fTemp25 * (1 - fTemp26)));
			this.fRec47[0] = this.fRec48[0];
			this.fRec50[0] = (fTemp4 - (fSlow38 * ((fSlow39 * this.fRec50[2]) + (this.fConst53 * this.fRec50[1]))));
			this.fRec53[0] = (fTemp0 - (fSlow38 * ((this.fConst53 * this.fRec53[1]) + (fSlow39 * this.fRec53[2]))));
			var fTemp27 = Math.abs((fSlow38 * ((this.fConst52 * this.fRec53[0]) + (this.fConst54 * this.fRec53[2]))));
			var fTemp28 = ((this.fRec51[1] > fTemp27)?fSlow5:fSlow4);
			this.fRec52[0] = ((this.fRec52[1] * fTemp28) + (fTemp27 * (1 - fTemp28)));
			this.fRec51[0] = this.fRec52[0];
			this.fRec54[0] = (fTemp4 - (fSlow40 * ((fSlow41 * this.fRec54[2]) + (this.fConst57 * this.fRec54[1]))));
			this.fRec57[0] = (fTemp0 - (fSlow40 * ((this.fConst57 * this.fRec57[1]) + (fSlow41 * this.fRec57[2]))));
			var fTemp29 = Math.abs((fSlow40 * ((this.fConst56 * this.fRec57[0]) + (this.fConst58 * this.fRec57[2]))));
			var fTemp30 = ((this.fRec55[1] > fTemp29)?fSlow5:fSlow4);
			this.fRec56[0] = ((this.fRec56[1] * fTemp30) + (fTemp29 * (1 - fTemp30)));
			this.fRec55[0] = this.fRec56[0];
			this.fRec58[0] = (fTemp4 - (fSlow42 * ((fSlow43 * this.fRec58[2]) + (this.fConst61 * this.fRec58[1]))));
			this.fRec61[0] = (fTemp0 - (fSlow42 * ((this.fConst61 * this.fRec61[1]) + (fSlow43 * this.fRec61[2]))));
			var fTemp31 = Math.abs((fSlow42 * ((this.fConst60 * this.fRec61[0]) + (this.fConst62 * this.fRec61[2]))));
			var fTemp32 = ((this.fRec59[1] > fTemp31)?fSlow5:fSlow4);
			this.fRec60[0] = ((this.fRec60[1] * fTemp32) + (fTemp31 * (1 - fTemp32)));
			this.fRec59[0] = this.fRec60[0];
			this.fRec62[0] = (fTemp4 - (fSlow45 * ((fSlow46 * this.fRec62[2]) + (this.fConst65 * this.fRec62[1]))));
			this.fRec65[0] = (fTemp0 - (fSlow45 * ((this.fConst65 * this.fRec65[1]) + (fSlow46 * this.fRec65[2]))));
			var fTemp33 = Math.abs((fSlow45 * ((this.fConst64 * this.fRec65[0]) + (this.fConst66 * this.fRec65[2]))));
			var fTemp34 = ((this.fRec63[1] > fTemp33)?fSlow5:fSlow4);
			this.fRec64[0] = ((this.fRec64[1] * fTemp34) + (fTemp33 * (1 - fTemp34)));
			this.fRec63[0] = this.fRec64[0];
			this.fRec66[0] = (fTemp4 - (fSlow47 * ((fSlow48 * this.fRec66[2]) + (this.fConst69 * this.fRec66[1]))));
			this.fRec69[0] = (fTemp0 - (fSlow47 * ((this.fConst69 * this.fRec69[1]) + (fSlow48 * this.fRec69[2]))));
			var fTemp35 = Math.abs((fSlow47 * ((this.fConst68 * this.fRec69[0]) + (this.fConst70 * this.fRec69[2]))));
			var fTemp36 = ((this.fRec67[1] > fTemp35)?fSlow5:fSlow4);
			this.fRec68[0] = ((this.fRec68[1] * fTemp36) + (fTemp35 * (1 - fTemp36)));
			this.fRec67[0] = this.fRec68[0];
			this.fRec70[0] = (fTemp4 - (fSlow49 * ((fSlow50 * this.fRec70[2]) + (this.fConst73 * this.fRec70[1]))));
			this.fRec73[0] = (fTemp0 - (fSlow49 * ((this.fConst73 * this.fRec73[1]) + (fSlow50 * this.fRec73[2]))));
			var fTemp37 = Math.abs((fSlow49 * ((this.fConst72 * this.fRec73[0]) + (this.fConst74 * this.fRec73[2]))));
			var fTemp38 = ((this.fRec71[1] > fTemp37)?fSlow5:fSlow4);
			this.fRec72[0] = ((this.fRec72[1] * fTemp38) + (fTemp37 * (1 - fTemp38)));
			this.fRec71[0] = this.fRec72[0];
			this.fRec74[0] = (fTemp4 - (fSlow51 * ((fSlow52 * this.fRec74[2]) + (this.fConst77 * this.fRec74[1]))));
			this.fRec77[0] = (fTemp0 - (fSlow51 * ((this.fConst77 * this.fRec77[1]) + (fSlow52 * this.fRec77[2]))));
			var fTemp39 = Math.abs((fSlow51 * ((this.fConst76 * this.fRec77[0]) + (this.fConst78 * this.fRec77[2]))));
			var fTemp40 = ((this.fRec75[1] > fTemp39)?fSlow5:fSlow4);
			this.fRec76[0] = ((this.fRec76[1] * fTemp40) + (fTemp39 * (1 - fTemp40)));
			this.fRec75[0] = this.fRec76[0];
			this.fRec78[0] = (fTemp4 - (fSlow54 * ((fSlow55 * this.fRec78[2]) + (this.fConst81 * this.fRec78[1]))));
			this.fRec81[0] = (fTemp0 - (fSlow54 * ((this.fConst81 * this.fRec81[1]) + (fSlow55 * this.fRec81[2]))));
			var fTemp41 = Math.abs((fSlow54 * ((this.fConst80 * this.fRec81[0]) + (this.fConst82 * this.fRec81[2]))));
			var fTemp42 = ((this.fRec79[1] > fTemp41)?fSlow5:fSlow4);
			this.fRec80[0] = ((this.fRec80[1] * fTemp42) + (fTemp41 * (1 - fTemp42)));
			this.fRec79[0] = this.fRec80[0];
			this.fRec82[0] = (fTemp4 - (fSlow56 * ((fSlow57 * this.fRec82[2]) + (this.fConst85 * this.fRec82[1]))));
			this.fRec85[0] = (fTemp0 - (fSlow56 * ((this.fConst85 * this.fRec85[1]) + (fSlow57 * this.fRec85[2]))));
			var fTemp43 = Math.abs((fSlow56 * ((this.fConst84 * this.fRec85[0]) + (this.fConst86 * this.fRec85[2]))));
			var fTemp44 = ((this.fRec83[1] > fTemp43)?fSlow5:fSlow4);
			this.fRec84[0] = ((this.fRec84[1] * fTemp44) + (fTemp43 * (1 - fTemp44)));
			this.fRec83[0] = this.fRec84[0];
			this.fRec86[0] = (fTemp4 - (fSlow58 * ((fSlow59 * this.fRec86[2]) + (this.fConst89 * this.fRec86[1]))));
			this.fRec89[0] = (fTemp0 - (fSlow58 * ((this.fConst89 * this.fRec89[1]) + (fSlow59 * this.fRec89[2]))));
			var fTemp45 = Math.abs((fSlow58 * ((this.fConst88 * this.fRec89[0]) + (this.fConst90 * this.fRec89[2]))));
			var fTemp46 = ((this.fRec87[1] > fTemp45)?fSlow5:fSlow4);
			this.fRec88[0] = ((this.fRec88[1] * fTemp46) + (fTemp45 * (1 - fTemp46)));
			this.fRec87[0] = this.fRec88[0];
			this.fRec90[0] = (fTemp4 - (fSlow60 * ((fSlow61 * this.fRec90[2]) + (this.fConst93 * this.fRec90[1]))));
			this.fRec93[0] = (fTemp0 - (fSlow60 * ((this.fConst93 * this.fRec93[1]) + (fSlow61 * this.fRec93[2]))));
			var fTemp47 = Math.abs((fSlow60 * ((this.fConst92 * this.fRec93[0]) + (this.fConst94 * this.fRec93[2]))));
			var fTemp48 = ((this.fRec91[1] > fTemp47)?fSlow5:fSlow4);
			this.fRec92[0] = ((this.fRec92[1] * fTemp48) + (fTemp47 * (1 - fTemp48)));
			this.fRec91[0] = this.fRec92[0];
			this.fRec94[0] = (fTemp4 - (fSlow62 * ((fSlow63 * this.fRec94[2]) + (this.fConst97 * this.fRec94[1]))));
			this.fRec97[0] = (fTemp0 - (fSlow62 * ((this.fConst97 * this.fRec97[1]) + (fSlow63 * this.fRec97[2]))));
			var fTemp49 = Math.abs((fSlow62 * ((this.fConst96 * this.fRec97[0]) + (this.fConst98 * this.fRec97[2]))));
			var fTemp50 = ((this.fRec95[1] > fTemp49)?fSlow5:fSlow4);
			this.fRec96[0] = ((this.fRec96[1] * fTemp50) + (fTemp49 * (1 - fTemp50)));
			this.fRec95[0] = this.fRec96[0];
			this.fRec98[0] = (fTemp4 - (fSlow64 * ((fSlow65 * this.fRec98[2]) + (this.fConst101 * this.fRec98[1]))));
			this.fRec101[0] = (fTemp0 - (fSlow64 * ((this.fConst101 * this.fRec101[1]) + (fSlow65 * this.fRec101[2]))));
			var fTemp51 = Math.abs((fSlow64 * ((this.fConst100 * this.fRec101[0]) + (this.fConst102 * this.fRec101[2]))));
			var fTemp52 = ((this.fRec99[1] > fTemp51)?fSlow5:fSlow4);
			this.fRec100[0] = ((this.fRec100[1] * fTemp52) + (fTemp51 * (1 - fTemp52)));
			this.fRec99[0] = this.fRec100[0];
			this.fRec102[0] = (fTemp4 - (fSlow67 * ((fSlow68 * this.fRec102[2]) + (this.fConst105 * this.fRec102[1]))));
			this.fRec105[0] = (fTemp0 - (fSlow67 * ((this.fConst105 * this.fRec105[1]) + (fSlow68 * this.fRec105[2]))));
			var fTemp53 = Math.abs((fSlow67 * ((this.fConst104 * this.fRec105[0]) + (this.fConst106 * this.fRec105[2]))));
			var fTemp54 = ((this.fRec103[1] > fTemp53)?fSlow5:fSlow4);
			this.fRec104[0] = ((this.fRec104[1] * fTemp54) + (fTemp53 * (1 - fTemp54)));
			this.fRec103[0] = this.fRec104[0];
			this.fRec106[0] = (fTemp4 - (fSlow69 * ((fSlow70 * this.fRec106[2]) + (this.fConst109 * this.fRec106[1]))));
			this.fRec109[0] = (fTemp0 - (fSlow69 * ((this.fConst109 * this.fRec109[1]) + (fSlow70 * this.fRec109[2]))));
			var fTemp55 = Math.abs((fSlow69 * ((this.fConst108 * this.fRec109[0]) + (this.fConst110 * this.fRec109[2]))));
			var fTemp56 = ((this.fRec107[1] > fTemp55)?fSlow5:fSlow4);
			this.fRec108[0] = ((this.fRec108[1] * fTemp56) + (fTemp55 * (1 - fTemp56)));
			this.fRec107[0] = this.fRec108[0];
			this.fRec110[0] = (fTemp4 - (fSlow71 * ((fSlow72 * this.fRec110[2]) + (this.fConst113 * this.fRec110[1]))));
			this.fRec113[0] = (fTemp0 - (fSlow71 * ((this.fConst113 * this.fRec113[1]) + (fSlow72 * this.fRec113[2]))));
			var fTemp57 = Math.abs((fSlow71 * ((this.fConst112 * this.fRec113[0]) + (this.fConst114 * this.fRec113[2]))));
			var fTemp58 = ((this.fRec111[1] > fTemp57)?fSlow5:fSlow4);
			this.fRec112[0] = ((this.fRec112[1] * fTemp58) + (fTemp57 * (1 - fTemp58)));
			this.fRec111[0] = this.fRec112[0];
			this.fRec114[0] = (fTemp4 - (fSlow73 * ((fSlow74 * this.fRec114[2]) + (this.fConst117 * this.fRec114[1]))));
			this.fRec117[0] = (fTemp0 - (fSlow73 * ((this.fConst117 * this.fRec117[1]) + (fSlow74 * this.fRec117[2]))));
			var fTemp59 = Math.abs((fSlow73 * ((this.fConst116 * this.fRec117[0]) + (this.fConst118 * this.fRec117[2]))));
			var fTemp60 = ((this.fRec115[1] > fTemp59)?fSlow5:fSlow4);
			this.fRec116[0] = ((this.fRec116[1] * fTemp60) + (fTemp59 * (1 - fTemp60)));
			this.fRec115[0] = this.fRec116[0];
			this.fRec118[0] = (fTemp4 - (fSlow75 * ((fSlow76 * this.fRec118[2]) + (this.fConst121 * this.fRec118[1]))));
			this.fRec121[0] = (fTemp0 - (fSlow75 * ((this.fConst121 * this.fRec121[1]) + (fSlow76 * this.fRec121[2]))));
			var fTemp61 = Math.abs((fSlow75 * ((this.fConst120 * this.fRec121[0]) + (this.fConst122 * this.fRec121[2]))));
			var fTemp62 = ((this.fRec119[1] > fTemp61)?fSlow5:fSlow4);
			this.fRec120[0] = ((this.fRec120[1] * fTemp62) + (fTemp61 * (1 - fTemp62)));
			this.fRec119[0] = this.fRec120[0];
			this.fRec122[0] = (fTemp4 - (fSlow77 * ((fSlow78 * this.fRec122[2]) + (this.fConst125 * this.fRec122[1]))));
			this.fRec125[0] = (fTemp0 - (fSlow77 * ((this.fConst125 * this.fRec125[1]) + (fSlow78 * this.fRec125[2]))));
			var fTemp63 = Math.abs((fSlow77 * ((this.fConst124 * this.fRec125[0]) + (this.fConst126 * this.fRec125[2]))));
			var fTemp64 = ((this.fRec123[1] > fTemp63)?fSlow5:fSlow4);
			this.fRec124[0] = ((this.fRec124[1] * fTemp64) + (fTemp63 * (1 - fTemp64)));
			this.fRec123[0] = this.fRec124[0];
			this.fRec126[0] = (fTemp4 - (fSlow80 * ((fSlow81 * this.fRec126[2]) + (this.fConst129 * this.fRec126[1]))));
			this.fRec129[0] = (fTemp0 - (fSlow80 * ((this.fConst129 * this.fRec129[1]) + (fSlow81 * this.fRec129[2]))));
			var fTemp65 = Math.abs((fSlow80 * ((this.fConst128 * this.fRec129[0]) + (this.fConst130 * this.fRec129[2]))));
			var fTemp66 = ((this.fRec127[1] > fTemp65)?fSlow5:fSlow4);
			this.fRec128[0] = ((this.fRec128[1] * fTemp66) + (fTemp65 * (1 - fTemp66)));
			this.fRec127[0] = this.fRec128[0];
			var fTemp67 = ((((((((((((((((((((((((((((((((fSlow2 * (((0 - (this.fConst2 * this.fRec0[0])) * this.fRec3[2]) + (this.fConst2 * (this.fRec3[0] * this.fRec0[0])))) + (fSlow9 * ((this.fRec6[2] * (0 - (this.fConst8 * this.fRec7[0]))) + (this.fConst8 * (this.fRec6[0] * this.fRec7[0]))))) + (fSlow12 * ((this.fRec10[2] * (0 - (this.fConst12 * this.fRec11[0]))) + (this.fConst12 * (this.fRec10[0] * this.fRec11[0]))))) + (fSlow14 * ((this.fRec14[2] * (0 - (this.fConst16 * this.fRec15[0]))) + (this.fConst16 * (this.fRec14[0] * this.fRec15[0]))))) + (fSlow16 * ((this.fRec18[2] * (0 - (this.fConst20 * this.fRec19[0]))) + (this.fConst20 * (this.fRec18[0] * this.fRec19[0]))))) + (fSlow19 * ((this.fRec22[2] * (0 - (this.fConst24 * this.fRec23[0]))) + (this.fConst24 * (this.fRec22[0] * this.fRec23[0]))))) + (fSlow22 * ((this.fRec26[2] * (0 - (this.fConst28 * this.fRec27[0]))) + (this.fConst28 * (this.fRec26[0] * this.fRec27[0]))))) + (fSlow25 * ((this.fRec30[2] * (0 - (this.fConst32 * this.fRec31[0]))) + (this.fConst32 * (this.fRec30[0] * this.fRec31[0]))))) + (fSlow28 * ((this.fRec34[2] * (0 - (this.fConst36 * this.fRec35[0]))) + (this.fConst36 * (this.fRec34[0] * this.fRec35[0]))))) + (fSlow31 * ((this.fRec38[2] * (0 - (this.fConst40 * this.fRec39[0]))) + (this.fConst40 * (this.fRec38[0] * this.fRec39[0]))))) + (fSlow33 * ((this.fRec42[2] * (0 - (this.fConst44 * this.fRec43[0]))) + (this.fConst44 * (this.fRec42[0] * this.fRec43[0]))))) + (fSlow35 * ((this.fRec46[2] * (0 - (this.fConst48 * this.fRec47[0]))) + (this.fConst48 * (this.fRec46[0] * this.fRec47[0]))))) + (fSlow38 * ((this.fRec50[2] * (0 - (this.fConst52 * this.fRec51[0]))) + (this.fConst52 * (this.fRec50[0] * this.fRec51[0]))))) + (fSlow40 * ((this.fRec54[2] * (0 - (this.fConst56 * this.fRec55[0]))) + (this.fConst56 * (this.fRec54[0] * this.fRec55[0]))))) + (fSlow42 * ((this.fRec58[2] * (0 - (this.fConst60 * this.fRec59[0]))) + (this.fConst60 * (this.fRec58[0] * this.fRec59[0]))))) + (fSlow45 * ((this.fRec62[2] * (0 - (this.fConst64 * this.fRec63[0]))) + (this.fConst64 * (this.fRec62[0] * this.fRec63[0]))))) + (fSlow47 * ((this.fRec66[2] * (0 - (this.fConst68 * this.fRec67[0]))) + (this.fConst68 * (this.fRec66[0] * this.fRec67[0]))))) + (fSlow49 * ((this.fRec70[2] * (0 - (this.fConst72 * this.fRec71[0]))) + (this.fConst72 * (this.fRec70[0] * this.fRec71[0]))))) + (fSlow51 * ((this.fRec74[2] * (0 - (this.fConst76 * this.fRec75[0]))) + (this.fConst76 * (this.fRec74[0] * this.fRec75[0]))))) + (fSlow54 * ((this.fRec78[2] * (0 - (this.fConst80 * this.fRec79[0]))) + (this.fConst80 * (this.fRec78[0] * this.fRec79[0]))))) + (fSlow56 * ((this.fRec82[2] * (0 - (this.fConst84 * this.fRec83[0]))) + (this.fConst84 * (this.fRec82[0] * this.fRec83[0]))))) + (fSlow58 * ((this.fRec86[2] * (0 - (this.fConst88 * this.fRec87[0]))) + (this.fConst88 * (this.fRec86[0] * this.fRec87[0]))))) + (fSlow60 * ((this.fRec90[2] * (0 - (this.fConst92 * this.fRec91[0]))) + (this.fConst92 * (this.fRec90[0] * this.fRec91[0]))))) + (fSlow62 * ((this.fRec94[2] * (0 - (this.fConst96 * this.fRec95[0]))) + (this.fConst96 * (this.fRec94[0] * this.fRec95[0]))))) + (fSlow64 * ((this.fRec98[2] * (0 - (this.fConst100 * this.fRec99[0]))) + (this.fConst100 * (this.fRec98[0] * this.fRec99[0]))))) + (fSlow67 * ((this.fRec102[2] * (0 - (this.fConst104 * this.fRec103[0]))) + (this.fConst104 * (this.fRec102[0] * this.fRec103[0]))))) + (fSlow69 * ((this.fRec106[2] * (0 - (this.fConst108 * this.fRec107[0]))) + (this.fConst108 * (this.fRec106[0] * this.fRec107[0]))))) + (fSlow71 * ((this.fRec110[2] * (0 - (this.fConst112 * this.fRec111[0]))) + (this.fConst112 * (this.fRec110[0] * this.fRec111[0]))))) + (fSlow73 * ((this.fRec114[2] * (0 - (this.fConst116 * this.fRec115[0]))) + (this.fConst116 * (this.fRec114[0] * this.fRec115[0]))))) + (fSlow75 * ((this.fRec118[2] * (0 - (this.fConst120 * this.fRec119[0]))) + (this.fConst120 * (this.fRec118[0] * this.fRec119[0]))))) + (fSlow77 * ((this.fRec122[2] * (0 - (this.fConst124 * this.fRec123[0]))) + (this.fConst124 * (this.fRec122[0] * this.fRec123[0]))))) + (fSlow80 * ((this.fRec126[2] * (0 - (this.fConst128 * this.fRec127[0]))) + (this.fConst128 * (this.fRec126[0] * this.fRec127[0])))));
			output0[i] = fTemp67;
			output1[i] = fTemp67;
			this.fRec2[2] = this.fRec2[1];
			this.fRec2[1] = this.fRec2[0];
			this.fRec1[1] = this.fRec1[0];
			this.fRec0[1] = this.fRec0[0];
			this.fRec4[1] = this.fRec4[0];
			this.fVec0[1] = this.fVec0[0];
			this.fRec5[1] = this.fRec5[0];
			this.fRec3[2] = this.fRec3[1];
			this.fRec3[1] = this.fRec3[0];
			this.fRec6[2] = this.fRec6[1];
			this.fRec6[1] = this.fRec6[0];
			this.fRec9[2] = this.fRec9[1];
			this.fRec9[1] = this.fRec9[0];
			this.fRec8[1] = this.fRec8[0];
			this.fRec7[1] = this.fRec7[0];
			this.fRec10[2] = this.fRec10[1];
			this.fRec10[1] = this.fRec10[0];
			this.fRec13[2] = this.fRec13[1];
			this.fRec13[1] = this.fRec13[0];
			this.fRec12[1] = this.fRec12[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec14[2] = this.fRec14[1];
			this.fRec14[1] = this.fRec14[0];
			this.fRec17[2] = this.fRec17[1];
			this.fRec17[1] = this.fRec17[0];
			this.fRec16[1] = this.fRec16[0];
			this.fRec15[1] = this.fRec15[0];
			this.fRec18[2] = this.fRec18[1];
			this.fRec18[1] = this.fRec18[0];
			this.fRec21[2] = this.fRec21[1];
			this.fRec21[1] = this.fRec21[0];
			this.fRec20[1] = this.fRec20[0];
			this.fRec19[1] = this.fRec19[0];
			this.fRec22[2] = this.fRec22[1];
			this.fRec22[1] = this.fRec22[0];
			this.fRec25[2] = this.fRec25[1];
			this.fRec25[1] = this.fRec25[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec23[1] = this.fRec23[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec29[2] = this.fRec29[1];
			this.fRec29[1] = this.fRec29[0];
			this.fRec28[1] = this.fRec28[0];
			this.fRec27[1] = this.fRec27[0];
			this.fRec30[2] = this.fRec30[1];
			this.fRec30[1] = this.fRec30[0];
			this.fRec33[2] = this.fRec33[1];
			this.fRec33[1] = this.fRec33[0];
			this.fRec32[1] = this.fRec32[0];
			this.fRec31[1] = this.fRec31[0];
			this.fRec34[2] = this.fRec34[1];
			this.fRec34[1] = this.fRec34[0];
			this.fRec37[2] = this.fRec37[1];
			this.fRec37[1] = this.fRec37[0];
			this.fRec36[1] = this.fRec36[0];
			this.fRec35[1] = this.fRec35[0];
			this.fRec38[2] = this.fRec38[1];
			this.fRec38[1] = this.fRec38[0];
			this.fRec41[2] = this.fRec41[1];
			this.fRec41[1] = this.fRec41[0];
			this.fRec40[1] = this.fRec40[0];
			this.fRec39[1] = this.fRec39[0];
			this.fRec42[2] = this.fRec42[1];
			this.fRec42[1] = this.fRec42[0];
			this.fRec45[2] = this.fRec45[1];
			this.fRec45[1] = this.fRec45[0];
			this.fRec44[1] = this.fRec44[0];
			this.fRec43[1] = this.fRec43[0];
			this.fRec46[2] = this.fRec46[1];
			this.fRec46[1] = this.fRec46[0];
			this.fRec49[2] = this.fRec49[1];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[1] = this.fRec48[0];
			this.fRec47[1] = this.fRec47[0];
			this.fRec50[2] = this.fRec50[1];
			this.fRec50[1] = this.fRec50[0];
			this.fRec53[2] = this.fRec53[1];
			this.fRec53[1] = this.fRec53[0];
			this.fRec52[1] = this.fRec52[0];
			this.fRec51[1] = this.fRec51[0];
			this.fRec54[2] = this.fRec54[1];
			this.fRec54[1] = this.fRec54[0];
			this.fRec57[2] = this.fRec57[1];
			this.fRec57[1] = this.fRec57[0];
			this.fRec56[1] = this.fRec56[0];
			this.fRec55[1] = this.fRec55[0];
			this.fRec58[2] = this.fRec58[1];
			this.fRec58[1] = this.fRec58[0];
			this.fRec61[2] = this.fRec61[1];
			this.fRec61[1] = this.fRec61[0];
			this.fRec60[1] = this.fRec60[0];
			this.fRec59[1] = this.fRec59[0];
			this.fRec62[2] = this.fRec62[1];
			this.fRec62[1] = this.fRec62[0];
			this.fRec65[2] = this.fRec65[1];
			this.fRec65[1] = this.fRec65[0];
			this.fRec64[1] = this.fRec64[0];
			this.fRec63[1] = this.fRec63[0];
			this.fRec66[2] = this.fRec66[1];
			this.fRec66[1] = this.fRec66[0];
			this.fRec69[2] = this.fRec69[1];
			this.fRec69[1] = this.fRec69[0];
			this.fRec68[1] = this.fRec68[0];
			this.fRec67[1] = this.fRec67[0];
			this.fRec70[2] = this.fRec70[1];
			this.fRec70[1] = this.fRec70[0];
			this.fRec73[2] = this.fRec73[1];
			this.fRec73[1] = this.fRec73[0];
			this.fRec72[1] = this.fRec72[0];
			this.fRec71[1] = this.fRec71[0];
			this.fRec74[2] = this.fRec74[1];
			this.fRec74[1] = this.fRec74[0];
			this.fRec77[2] = this.fRec77[1];
			this.fRec77[1] = this.fRec77[0];
			this.fRec76[1] = this.fRec76[0];
			this.fRec75[1] = this.fRec75[0];
			this.fRec78[2] = this.fRec78[1];
			this.fRec78[1] = this.fRec78[0];
			this.fRec81[2] = this.fRec81[1];
			this.fRec81[1] = this.fRec81[0];
			this.fRec80[1] = this.fRec80[0];
			this.fRec79[1] = this.fRec79[0];
			this.fRec82[2] = this.fRec82[1];
			this.fRec82[1] = this.fRec82[0];
			this.fRec85[2] = this.fRec85[1];
			this.fRec85[1] = this.fRec85[0];
			this.fRec84[1] = this.fRec84[0];
			this.fRec83[1] = this.fRec83[0];
			this.fRec86[2] = this.fRec86[1];
			this.fRec86[1] = this.fRec86[0];
			this.fRec89[2] = this.fRec89[1];
			this.fRec89[1] = this.fRec89[0];
			this.fRec88[1] = this.fRec88[0];
			this.fRec87[1] = this.fRec87[0];
			this.fRec90[2] = this.fRec90[1];
			this.fRec90[1] = this.fRec90[0];
			this.fRec93[2] = this.fRec93[1];
			this.fRec93[1] = this.fRec93[0];
			this.fRec92[1] = this.fRec92[0];
			this.fRec91[1] = this.fRec91[0];
			this.fRec94[2] = this.fRec94[1];
			this.fRec94[1] = this.fRec94[0];
			this.fRec97[2] = this.fRec97[1];
			this.fRec97[1] = this.fRec97[0];
			this.fRec96[1] = this.fRec96[0];
			this.fRec95[1] = this.fRec95[0];
			this.fRec98[2] = this.fRec98[1];
			this.fRec98[1] = this.fRec98[0];
			this.fRec101[2] = this.fRec101[1];
			this.fRec101[1] = this.fRec101[0];
			this.fRec100[1] = this.fRec100[0];
			this.fRec99[1] = this.fRec99[0];
			this.fRec102[2] = this.fRec102[1];
			this.fRec102[1] = this.fRec102[0];
			this.fRec105[2] = this.fRec105[1];
			this.fRec105[1] = this.fRec105[0];
			this.fRec104[1] = this.fRec104[0];
			this.fRec103[1] = this.fRec103[0];
			this.fRec106[2] = this.fRec106[1];
			this.fRec106[1] = this.fRec106[0];
			this.fRec109[2] = this.fRec109[1];
			this.fRec109[1] = this.fRec109[0];
			this.fRec108[1] = this.fRec108[0];
			this.fRec107[1] = this.fRec107[0];
			this.fRec110[2] = this.fRec110[1];
			this.fRec110[1] = this.fRec110[0];
			this.fRec113[2] = this.fRec113[1];
			this.fRec113[1] = this.fRec113[0];
			this.fRec112[1] = this.fRec112[0];
			this.fRec111[1] = this.fRec111[0];
			this.fRec114[2] = this.fRec114[1];
			this.fRec114[1] = this.fRec114[0];
			this.fRec117[2] = this.fRec117[1];
			this.fRec117[1] = this.fRec117[0];
			this.fRec116[1] = this.fRec116[0];
			this.fRec115[1] = this.fRec115[0];
			this.fRec118[2] = this.fRec118[1];
			this.fRec118[1] = this.fRec118[0];
			this.fRec121[2] = this.fRec121[1];
			this.fRec121[1] = this.fRec121[0];
			this.fRec120[1] = this.fRec120[0];
			this.fRec119[1] = this.fRec119[0];
			this.fRec122[2] = this.fRec122[1];
			this.fRec122[1] = this.fRec122[0];
			this.fRec125[2] = this.fRec125[1];
			this.fRec125[1] = this.fRec125[0];
			this.fRec124[1] = this.fRec124[0];
			this.fRec123[1] = this.fRec123[0];
			this.fRec126[2] = this.fRec126[1];
			this.fRec126[1] = this.fRec126[0];
			this.fRec129[2] = this.fRec129[1];
			this.fRec129[1] = this.fRec129[0];
			this.fRec128[1] = this.fRec128[0];
			this.fRec127[1] = this.fRec127[0];
			
		}
		
	}
	
}

