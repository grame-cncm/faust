
this.max_f = function(dummy0, dummy1);
this.min_f = function(dummy0, dummy1);
this.mydsp_faustpower2_f = function(value) {
	return (value * value);
	
}

function mydsp() {
	
	this.fCheckbox0;
	this.fSamplingFreq;
	this.fConst0;
	this.fConst1;
	this.fConst2;
	this.fConst3;
	this.fConst4;
	this.fConst5;
	this.fConst6;
	this.fConst7;
	this.fConst8;
	this.fConst9;
	this.fConst10;
	this.fVec0 = new Float32Array(2);
	this.fConst11;
	this.fRec10 = new Float32Array(2);
	this.fConst12;
	this.fConst13;
	this.fRec9 = new Float32Array(3);
	this.fConst14;
	this.fRec8 = new Float32Array(3);
	this.fConst15;
	this.fConst16;
	this.fConst17;
	this.fConst18;
	this.fConst19;
	this.fConst20;
	this.fRec7 = new Float32Array(3);
	this.fConst21;
	this.fConst22;
	this.fConst23;
	this.fConst24;
	this.fConst25;
	this.fConst26;
	this.fRec6 = new Float32Array(3);
	this.fConst27;
	this.fConst28;
	this.fConst29;
	this.fConst30;
	this.fConst31;
	this.fConst32;
	this.fRec5 = new Float32Array(3);
	this.fConst33;
	this.fConst34;
	this.fConst35;
	this.fConst36;
	this.fConst37;
	this.fConst38;
	this.fRec4 = new Float32Array(3);
	this.fConst39;
	this.fConst40;
	this.fConst41;
	this.fConst42;
	this.fConst43;
	this.fConst44;
	this.fRec3 = new Float32Array(3);
	this.fConst45;
	this.fConst46;
	this.fConst47;
	this.fConst48;
	this.fConst49;
	this.fConst50;
	this.fRec2 = new Float32Array(3);
	this.fConst51;
	this.fConst52;
	this.fConst53;
	this.fConst54;
	this.fConst55;
	this.fConst56;
	this.fRec1 = new Float32Array(3);
	this.fConst57;
	this.fConst58;
	this.fConst59;
	this.fConst60;
	this.fConst61;
	this.fConst62;
	this.fRec0 = new Float32Array(3);
	this.fVslider0;
	this.fRec11 = new Float32Array(2);
	this.fConst63;
	this.fConst64;
	this.fConst65;
	this.fConst66;
	this.fConst67;
	this.fConst68;
	this.fConst69;
	this.fRec24 = new Float32Array(2);
	this.fRec23 = new Float32Array(3);
	this.fRec22 = new Float32Array(3);
	this.fVec1 = new Float32Array(2);
	this.fConst70;
	this.fRec21 = new Float32Array(2);
	this.fConst71;
	this.fRec20 = new Float32Array(3);
	this.fConst72;
	this.fRec19 = new Float32Array(3);
	this.fRec18 = new Float32Array(3);
	this.fRec17 = new Float32Array(3);
	this.fRec16 = new Float32Array(3);
	this.fRec15 = new Float32Array(3);
	this.fRec14 = new Float32Array(3);
	this.fRec13 = new Float32Array(3);
	this.fRec12 = new Float32Array(3);
	this.fVslider1;
	this.fRec25 = new Float32Array(2);
	this.fConst73;
	this.fConst74;
	this.fConst75;
	this.fConst76;
	this.fConst77;
	this.fConst78;
	this.fConst79;
	this.fRec37 = new Float32Array(2);
	this.fRec36 = new Float32Array(3);
	this.fRec35 = new Float32Array(3);
	this.fVec2 = new Float32Array(2);
	this.fConst80;
	this.fRec34 = new Float32Array(2);
	this.fConst81;
	this.fRec33 = new Float32Array(3);
	this.fConst82;
	this.fRec32 = new Float32Array(3);
	this.fRec31 = new Float32Array(3);
	this.fRec30 = new Float32Array(3);
	this.fRec29 = new Float32Array(3);
	this.fRec28 = new Float32Array(3);
	this.fRec27 = new Float32Array(3);
	this.fRec26 = new Float32Array(3);
	this.fVslider2;
	this.fRec38 = new Float32Array(2);
	this.fConst83;
	this.fConst84;
	this.fConst85;
	this.fConst86;
	this.fConst87;
	this.fConst88;
	this.fConst89;
	this.fRec49 = new Float32Array(2);
	this.fRec48 = new Float32Array(3);
	this.fRec47 = new Float32Array(3);
	this.fVec3 = new Float32Array(2);
	this.fConst90;
	this.fRec46 = new Float32Array(2);
	this.fConst91;
	this.fRec45 = new Float32Array(3);
	this.fConst92;
	this.fRec44 = new Float32Array(3);
	this.fRec43 = new Float32Array(3);
	this.fRec42 = new Float32Array(3);
	this.fRec41 = new Float32Array(3);
	this.fRec40 = new Float32Array(3);
	this.fRec39 = new Float32Array(3);
	this.fVslider3;
	this.fRec50 = new Float32Array(2);
	this.fConst93;
	this.fConst94;
	this.fConst95;
	this.fConst96;
	this.fConst97;
	this.fConst98;
	this.fConst99;
	this.fRec60 = new Float32Array(2);
	this.fRec59 = new Float32Array(3);
	this.fRec58 = new Float32Array(3);
	this.fVec4 = new Float32Array(2);
	this.fConst100;
	this.fRec57 = new Float32Array(2);
	this.fConst101;
	this.fRec56 = new Float32Array(3);
	this.fConst102;
	this.fRec55 = new Float32Array(3);
	this.fRec54 = new Float32Array(3);
	this.fRec53 = new Float32Array(3);
	this.fRec52 = new Float32Array(3);
	this.fRec51 = new Float32Array(3);
	this.fVslider4;
	this.fRec61 = new Float32Array(2);
	this.fConst103;
	this.fConst104;
	this.fConst105;
	this.fConst106;
	this.fConst107;
	this.fConst108;
	this.fConst109;
	this.fRec70 = new Float32Array(2);
	this.fRec69 = new Float32Array(3);
	this.fRec68 = new Float32Array(3);
	this.fVec5 = new Float32Array(2);
	this.fConst110;
	this.fRec67 = new Float32Array(2);
	this.fConst111;
	this.fRec66 = new Float32Array(3);
	this.fConst112;
	this.fRec65 = new Float32Array(3);
	this.fRec64 = new Float32Array(3);
	this.fRec63 = new Float32Array(3);
	this.fRec62 = new Float32Array(3);
	this.fVslider5;
	this.fRec71 = new Float32Array(2);
	this.fConst113;
	this.fConst114;
	this.fConst115;
	this.fConst116;
	this.fConst117;
	this.fConst118;
	this.fConst119;
	this.fRec79 = new Float32Array(2);
	this.fRec78 = new Float32Array(3);
	this.fRec77 = new Float32Array(3);
	this.fVec6 = new Float32Array(2);
	this.fConst120;
	this.fRec76 = new Float32Array(2);
	this.fConst121;
	this.fRec75 = new Float32Array(3);
	this.fConst122;
	this.fRec74 = new Float32Array(3);
	this.fRec73 = new Float32Array(3);
	this.fRec72 = new Float32Array(3);
	this.fVslider6;
	this.fRec80 = new Float32Array(2);
	this.fConst123;
	this.fConst124;
	this.fConst125;
	this.fConst126;
	this.fConst127;
	this.fConst128;
	this.fConst129;
	this.fRec87 = new Float32Array(2);
	this.fRec86 = new Float32Array(3);
	this.fRec85 = new Float32Array(3);
	this.fVec7 = new Float32Array(2);
	this.fConst130;
	this.fRec84 = new Float32Array(2);
	this.fConst131;
	this.fRec83 = new Float32Array(3);
	this.fConst132;
	this.fRec82 = new Float32Array(3);
	this.fRec81 = new Float32Array(3);
	this.fVslider7;
	this.fRec88 = new Float32Array(2);
	this.fConst133;
	this.fConst134;
	this.fConst135;
	this.fConst136;
	this.fConst137;
	this.fConst138;
	this.fRec94 = new Float32Array(2);
	this.fRec93 = new Float32Array(3);
	this.fRec92 = new Float32Array(3);
	this.fVec8 = new Float32Array(2);
	this.fConst139;
	this.fRec91 = new Float32Array(2);
	this.fConst140;
	this.fRec90 = new Float32Array(3);
	this.fConst141;
	this.fRec89 = new Float32Array(3);
	this.fVslider8;
	this.fRec95 = new Float32Array(2);
	this.fRec98 = new Float32Array(2);
	this.fRec97 = new Float32Array(3);
	this.fRec96 = new Float32Array(3);
	this.fVslider9;
	this.fRec99 = new Float32Array(2);
	
	this.metadata = function(m) { 
		m.declare("analyzers.lib/name", "Faust Analyzer Library");
		m.declare("analyzers.lib/version", "0.0");
		m.declare("basics.lib/name", "Faust Basic Element Library");
		m.declare("basics.lib/version", "0.0");
		m.declare("description", "Graphic Equalizer consisting of a filter-bank driving a bank of faders");
		m.declare("filters.lib/name", "Faust Filters Library");
		m.declare("filters.lib/version", "0.0");
		m.declare("maths.lib/author", "GRAME");
		m.declare("maths.lib/copyright", "GRAME");
		m.declare("maths.lib/license", "LGPL with exception");
		m.declare("maths.lib/name", "Faust Math Library");
		m.declare("maths.lib/version", "2.1");
		m.declare("name", "filterBank");
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
		this.fConst1 = Math.tan((31415.9 / this.fConst0));
		this.fConst2 = (1 / this.fConst1);
		this.fConst3 = (((this.fConst2 + 0.618034) / this.fConst1) + 1);
		this.fConst4 = (1 / this.fConst3);
		this.fConst5 = (1 / mydsp_faustpower2_f(this.fConst1));
		this.fConst6 = (2 * (0 - this.fConst5));
		this.fConst7 = (1 / (((this.fConst2 + 1.61803) / this.fConst1) + 1));
		this.fConst8 = (this.fConst2 + 1);
		this.fConst9 = (0 - ((1 - this.fConst2) / this.fConst8));
		this.fConst10 = (1 / this.fConst8);
		this.fConst11 = (0 - this.fConst2);
		this.fConst12 = (2 * (1 - this.fConst5));
		this.fConst13 = (((this.fConst2 + -1.61803) / this.fConst1) + 1);
		this.fConst14 = (((this.fConst2 + -0.618034) / this.fConst1) + 1);
		this.fConst15 = Math.tan((122.718 / this.fConst0));
		this.fConst16 = (1 / this.fConst15);
		this.fConst17 = (1 / (((this.fConst16 + 1.61803) / this.fConst15) + 1));
		this.fConst18 = (((this.fConst16 + -1.61803) / this.fConst15) + 1);
		this.fConst19 = (1 / mydsp_faustpower2_f(this.fConst15));
		this.fConst20 = (2 * (1 - this.fConst19));
		this.fConst21 = Math.tan((245.437 / this.fConst0));
		this.fConst22 = (1 / this.fConst21);
		this.fConst23 = (1 / (((this.fConst22 + 1.61803) / this.fConst21) + 1));
		this.fConst24 = (((this.fConst22 + -1.61803) / this.fConst21) + 1);
		this.fConst25 = (1 / mydsp_faustpower2_f(this.fConst21));
		this.fConst26 = (2 * (1 - this.fConst25));
		this.fConst27 = Math.tan((490.874 / this.fConst0));
		this.fConst28 = (1 / this.fConst27);
		this.fConst29 = (1 / (((this.fConst28 + 1.61803) / this.fConst27) + 1));
		this.fConst30 = (((this.fConst28 + -1.61803) / this.fConst27) + 1);
		this.fConst31 = (1 / mydsp_faustpower2_f(this.fConst27));
		this.fConst32 = (2 * (1 - this.fConst31));
		this.fConst33 = Math.tan((981.748 / this.fConst0));
		this.fConst34 = (1 / this.fConst33);
		this.fConst35 = (1 / (((this.fConst34 + 1.61803) / this.fConst33) + 1));
		this.fConst36 = (((this.fConst34 + -1.61803) / this.fConst33) + 1);
		this.fConst37 = (1 / mydsp_faustpower2_f(this.fConst33));
		this.fConst38 = (2 * (1 - this.fConst37));
		this.fConst39 = Math.tan((1963.5 / this.fConst0));
		this.fConst40 = (1 / this.fConst39);
		this.fConst41 = (1 / (((this.fConst40 + 1.61803) / this.fConst39) + 1));
		this.fConst42 = (((this.fConst40 + -1.61803) / this.fConst39) + 1);
		this.fConst43 = (1 / mydsp_faustpower2_f(this.fConst39));
		this.fConst44 = (2 * (1 - this.fConst43));
		this.fConst45 = Math.tan((3926.99 / this.fConst0));
		this.fConst46 = (1 / this.fConst45);
		this.fConst47 = (1 / (((this.fConst46 + 1.61803) / this.fConst45) + 1));
		this.fConst48 = (((this.fConst46 + -1.61803) / this.fConst45) + 1);
		this.fConst49 = (1 / mydsp_faustpower2_f(this.fConst45));
		this.fConst50 = (2 * (1 - this.fConst49));
		this.fConst51 = Math.tan((7853.98 / this.fConst0));
		this.fConst52 = (1 / this.fConst51);
		this.fConst53 = (1 / (((this.fConst52 + 1.61803) / this.fConst51) + 1));
		this.fConst54 = (((this.fConst52 + -1.61803) / this.fConst51) + 1);
		this.fConst55 = (1 / mydsp_faustpower2_f(this.fConst51));
		this.fConst56 = (2 * (1 - this.fConst55));
		this.fConst57 = Math.tan((15708 / this.fConst0));
		this.fConst58 = (1 / this.fConst57);
		this.fConst59 = (1 / (((this.fConst58 + 1.61803) / this.fConst57) + 1));
		this.fConst60 = (((this.fConst58 + -1.61803) / this.fConst57) + 1);
		this.fConst61 = (1 / mydsp_faustpower2_f(this.fConst57));
		this.fConst62 = (2 * (1 - this.fConst61));
		this.fConst63 = (((this.fConst58 + 0.618034) / this.fConst57) + 1);
		this.fConst64 = (1 / this.fConst63);
		this.fConst65 = (2 * (0 - this.fConst61));
		this.fConst66 = (1 / (((this.fConst58 + 1.61803) / this.fConst57) + 1));
		this.fConst67 = (this.fConst58 + 1);
		this.fConst68 = (0 - ((1 - this.fConst58) / this.fConst67));
		this.fConst69 = (1 / (this.fConst3 * this.fConst67));
		this.fConst70 = (0 - this.fConst58);
		this.fConst71 = (((this.fConst58 + -1.61803) / this.fConst57) + 1);
		this.fConst72 = (((this.fConst58 + -0.618034) / this.fConst57) + 1);
		this.fConst73 = (((this.fConst52 + 0.618034) / this.fConst51) + 1);
		this.fConst74 = (1 / this.fConst73);
		this.fConst75 = (2 * (0 - this.fConst55));
		this.fConst76 = (1 / (((this.fConst52 + 1.61803) / this.fConst51) + 1));
		this.fConst77 = (this.fConst52 + 1);
		this.fConst78 = (0 - ((1 - this.fConst52) / this.fConst77));
		this.fConst79 = (1 / (this.fConst77 * this.fConst63));
		this.fConst80 = (0 - this.fConst52);
		this.fConst81 = (((this.fConst52 + -1.61803) / this.fConst51) + 1);
		this.fConst82 = (((this.fConst52 + -0.618034) / this.fConst51) + 1);
		this.fConst83 = (((this.fConst46 + 0.618034) / this.fConst45) + 1);
		this.fConst84 = (1 / this.fConst83);
		this.fConst85 = (2 * (0 - this.fConst49));
		this.fConst86 = (1 / (((this.fConst46 + 1.61803) / this.fConst45) + 1));
		this.fConst87 = (this.fConst46 + 1);
		this.fConst88 = (0 - ((1 - this.fConst46) / this.fConst87));
		this.fConst89 = (1 / (this.fConst73 * this.fConst87));
		this.fConst90 = (0 - this.fConst46);
		this.fConst91 = (((this.fConst46 + -1.61803) / this.fConst45) + 1);
		this.fConst92 = (((this.fConst46 + -0.618034) / this.fConst45) + 1);
		this.fConst93 = (((this.fConst40 + 0.618034) / this.fConst39) + 1);
		this.fConst94 = (1 / this.fConst93);
		this.fConst95 = (2 * (0 - this.fConst43));
		this.fConst96 = (1 / (((this.fConst40 + 1.61803) / this.fConst39) + 1));
		this.fConst97 = (this.fConst40 + 1);
		this.fConst98 = (0 - ((1 - this.fConst40) / this.fConst97));
		this.fConst99 = (1 / (this.fConst83 * this.fConst97));
		this.fConst100 = (0 - this.fConst40);
		this.fConst101 = (((this.fConst40 + -1.61803) / this.fConst39) + 1);
		this.fConst102 = (((this.fConst40 + -0.618034) / this.fConst39) + 1);
		this.fConst103 = (((this.fConst34 + 0.618034) / this.fConst33) + 1);
		this.fConst104 = (1 / this.fConst103);
		this.fConst105 = (2 * (0 - this.fConst37));
		this.fConst106 = (1 / (((this.fConst34 + 1.61803) / this.fConst33) + 1));
		this.fConst107 = (this.fConst34 + 1);
		this.fConst108 = (0 - ((1 - this.fConst34) / this.fConst107));
		this.fConst109 = (1 / (this.fConst93 * this.fConst107));
		this.fConst110 = (0 - this.fConst34);
		this.fConst111 = (((this.fConst34 + -1.61803) / this.fConst33) + 1);
		this.fConst112 = (((this.fConst34 + -0.618034) / this.fConst33) + 1);
		this.fConst113 = (((this.fConst28 + 0.618034) / this.fConst27) + 1);
		this.fConst114 = (1 / this.fConst113);
		this.fConst115 = (2 * (0 - this.fConst31));
		this.fConst116 = (1 / (((this.fConst28 + 1.61803) / this.fConst27) + 1));
		this.fConst117 = (this.fConst28 + 1);
		this.fConst118 = (0 - ((1 - this.fConst28) / this.fConst117));
		this.fConst119 = (1 / (this.fConst103 * this.fConst117));
		this.fConst120 = (0 - this.fConst28);
		this.fConst121 = (((this.fConst28 + -1.61803) / this.fConst27) + 1);
		this.fConst122 = (((this.fConst28 + -0.618034) / this.fConst27) + 1);
		this.fConst123 = (((this.fConst22 + 0.618034) / this.fConst21) + 1);
		this.fConst124 = (1 / this.fConst123);
		this.fConst125 = (2 * (0 - this.fConst25));
		this.fConst126 = (1 / (((this.fConst22 + 1.61803) / this.fConst21) + 1));
		this.fConst127 = (this.fConst22 + 1);
		this.fConst128 = (0 - ((1 - this.fConst22) / this.fConst127));
		this.fConst129 = (1 / (this.fConst113 * this.fConst127));
		this.fConst130 = (0 - this.fConst22);
		this.fConst131 = (((this.fConst22 + -1.61803) / this.fConst21) + 1);
		this.fConst132 = (((this.fConst22 + -0.618034) / this.fConst21) + 1);
		this.fConst133 = (1 / (((this.fConst16 + 0.618034) / this.fConst15) + 1));
		this.fConst134 = (2 * (0 - this.fConst19));
		this.fConst135 = (1 / (((this.fConst16 + 1.61803) / this.fConst15) + 1));
		this.fConst136 = (this.fConst16 + 1);
		this.fConst137 = (0 - ((1 - this.fConst16) / this.fConst136));
		this.fConst138 = (1 / (this.fConst123 * this.fConst136));
		this.fConst139 = (0 - this.fConst16);
		this.fConst140 = (((this.fConst16 + -1.61803) / this.fConst15) + 1);
		this.fConst141 = (((this.fConst16 + -0.618034) / this.fConst15) + 1);
		this.instanceClear();
	}
	
	instanceResetUserInterface = function() {
		this.fCheckbox0 = 0;
		this.fVslider0 = -10;
		this.fVslider1 = -10;
		this.fVslider2 = -10;
		this.fVslider3 = -10;
		this.fVslider4 = -10;
		this.fVslider5 = -10;
		this.fVslider6 = -10;
		this.fVslider7 = -10;
		this.fVslider8 = -10;
		this.fVslider9 = -10;
		
	}
	
	this.instanceClear = function() {
		for (var l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this.fVec0[l0] = 0;
			
		}
		for (var l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this.fRec10[l1] = 0;
			
		}
		for (var l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			this.fRec9[l2] = 0;
			
		}
		for (var l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			this.fRec8[l3] = 0;
			
		}
		for (var l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			this.fRec7[l4] = 0;
			
		}
		for (var l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			this.fRec6[l5] = 0;
			
		}
		for (var l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			this.fRec5[l6] = 0;
			
		}
		for (var l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			this.fRec4[l7] = 0;
			
		}
		for (var l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			this.fRec3[l8] = 0;
			
		}
		for (var l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			this.fRec2[l9] = 0;
			
		}
		for (var l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			this.fRec1[l10] = 0;
			
		}
		for (var l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			this.fRec0[l11] = 0;
			
		}
		for (var l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			this.fRec11[l12] = 0;
			
		}
		for (var l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this.fRec24[l13] = 0;
			
		}
		for (var l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			this.fRec23[l14] = 0;
			
		}
		for (var l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			this.fRec22[l15] = 0;
			
		}
		for (var l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this.fVec1[l16] = 0;
			
		}
		for (var l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this.fRec21[l17] = 0;
			
		}
		for (var l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			this.fRec20[l18] = 0;
			
		}
		for (var l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			this.fRec19[l19] = 0;
			
		}
		for (var l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			this.fRec18[l20] = 0;
			
		}
		for (var l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			this.fRec17[l21] = 0;
			
		}
		for (var l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			this.fRec16[l22] = 0;
			
		}
		for (var l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			this.fRec15[l23] = 0;
			
		}
		for (var l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			this.fRec14[l24] = 0;
			
		}
		for (var l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			this.fRec13[l25] = 0;
			
		}
		for (var l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			this.fRec12[l26] = 0;
			
		}
		for (var l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			this.fRec25[l27] = 0;
			
		}
		for (var l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this.fRec37[l28] = 0;
			
		}
		for (var l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			this.fRec36[l29] = 0;
			
		}
		for (var l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			this.fRec35[l30] = 0;
			
		}
		for (var l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this.fVec2[l31] = 0;
			
		}
		for (var l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this.fRec34[l32] = 0;
			
		}
		for (var l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			this.fRec33[l33] = 0;
			
		}
		for (var l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			this.fRec32[l34] = 0;
			
		}
		for (var l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			this.fRec31[l35] = 0;
			
		}
		for (var l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			this.fRec30[l36] = 0;
			
		}
		for (var l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			this.fRec29[l37] = 0;
			
		}
		for (var l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			this.fRec28[l38] = 0;
			
		}
		for (var l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			this.fRec27[l39] = 0;
			
		}
		for (var l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			this.fRec26[l40] = 0;
			
		}
		for (var l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this.fRec38[l41] = 0;
			
		}
		for (var l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			this.fRec49[l42] = 0;
			
		}
		for (var l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			this.fRec48[l43] = 0;
			
		}
		for (var l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			this.fRec47[l44] = 0;
			
		}
		for (var l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			this.fVec3[l45] = 0;
			
		}
		for (var l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			this.fRec46[l46] = 0;
			
		}
		for (var l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			this.fRec45[l47] = 0;
			
		}
		for (var l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			this.fRec44[l48] = 0;
			
		}
		for (var l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			this.fRec43[l49] = 0;
			
		}
		for (var l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			this.fRec42[l50] = 0;
			
		}
		for (var l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			this.fRec41[l51] = 0;
			
		}
		for (var l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			this.fRec40[l52] = 0;
			
		}
		for (var l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			this.fRec39[l53] = 0;
			
		}
		for (var l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			this.fRec50[l54] = 0;
			
		}
		for (var l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			this.fRec60[l55] = 0;
			
		}
		for (var l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			this.fRec59[l56] = 0;
			
		}
		for (var l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			this.fRec58[l57] = 0;
			
		}
		for (var l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			this.fVec4[l58] = 0;
			
		}
		for (var l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			this.fRec57[l59] = 0;
			
		}
		for (var l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			this.fRec56[l60] = 0;
			
		}
		for (var l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			this.fRec55[l61] = 0;
			
		}
		for (var l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			this.fRec54[l62] = 0;
			
		}
		for (var l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			this.fRec53[l63] = 0;
			
		}
		for (var l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			this.fRec52[l64] = 0;
			
		}
		for (var l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			this.fRec51[l65] = 0;
			
		}
		for (var l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			this.fRec61[l66] = 0;
			
		}
		for (var l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			this.fRec70[l67] = 0;
			
		}
		for (var l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			this.fRec69[l68] = 0;
			
		}
		for (var l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			this.fRec68[l69] = 0;
			
		}
		for (var l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			this.fVec5[l70] = 0;
			
		}
		for (var l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			this.fRec67[l71] = 0;
			
		}
		for (var l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			this.fRec66[l72] = 0;
			
		}
		for (var l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			this.fRec65[l73] = 0;
			
		}
		for (var l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			this.fRec64[l74] = 0;
			
		}
		for (var l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			this.fRec63[l75] = 0;
			
		}
		for (var l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			this.fRec62[l76] = 0;
			
		}
		for (var l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			this.fRec71[l77] = 0;
			
		}
		for (var l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			this.fRec79[l78] = 0;
			
		}
		for (var l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			this.fRec78[l79] = 0;
			
		}
		for (var l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			this.fRec77[l80] = 0;
			
		}
		for (var l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			this.fVec6[l81] = 0;
			
		}
		for (var l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			this.fRec76[l82] = 0;
			
		}
		for (var l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			this.fRec75[l83] = 0;
			
		}
		for (var l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			this.fRec74[l84] = 0;
			
		}
		for (var l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			this.fRec73[l85] = 0;
			
		}
		for (var l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			this.fRec72[l86] = 0;
			
		}
		for (var l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			this.fRec80[l87] = 0;
			
		}
		for (var l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			this.fRec87[l88] = 0;
			
		}
		for (var l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			this.fRec86[l89] = 0;
			
		}
		for (var l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			this.fRec85[l90] = 0;
			
		}
		for (var l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			this.fVec7[l91] = 0;
			
		}
		for (var l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			this.fRec84[l92] = 0;
			
		}
		for (var l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			this.fRec83[l93] = 0;
			
		}
		for (var l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			this.fRec82[l94] = 0;
			
		}
		for (var l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			this.fRec81[l95] = 0;
			
		}
		for (var l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			this.fRec88[l96] = 0;
			
		}
		for (var l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			this.fRec94[l97] = 0;
			
		}
		for (var l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			this.fRec93[l98] = 0;
			
		}
		for (var l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			this.fRec92[l99] = 0;
			
		}
		for (var l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			this.fVec8[l100] = 0;
			
		}
		for (var l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			this.fRec91[l101] = 0;
			
		}
		for (var l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			this.fRec90[l102] = 0;
			
		}
		for (var l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			this.fRec89[l103] = 0;
			
		}
		for (var l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			this.fRec95[l104] = 0;
			
		}
		for (var l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			this.fRec98[l105] = 0;
			
		}
		for (var l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			this.fRec97[l106] = 0;
			
		}
		for (var l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			this.fRec96[l107] = 0;
			
		}
		for (var l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			this.fRec99[l108] = 0;
			
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
		ui_interface.declare("fVslider9", "1", "");
		ui_interface.declare("fVslider9", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider9", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider9 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider8", "2", "");
		ui_interface.declare("fVslider8", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider8", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider8 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider7", "3", "");
		ui_interface.declare("fVslider7", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider7", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider7 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider6", "4", "");
		ui_interface.declare("fVslider6", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider6", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider6 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider5", "5", "");
		ui_interface.declare("fVslider5", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider5", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider5 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider4", "6", "");
		ui_interface.declare("fVslider4", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider4", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider4 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider3", "7", "");
		ui_interface.declare("fVslider3", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider3", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider3 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider2", "8", "");
		ui_interface.declare("fVslider2", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider2", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider2 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider1", "9", "");
		ui_interface.declare("fVslider1", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider1", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider1 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.declare("fVslider0", "10", "");
		ui_interface.declare("fVslider0", "tooltip", "Bandpass filter   gain in dB");
		ui_interface.declare("fVslider0", "unit", "dB");
		ui_interface.addVerticalSlider("0x00", function handler(obj) { function setval(val) { obj.fVslider0 = val; } return setval; }(this), -10, -70, 10, 0.1);
		ui_interface.closeBox();
		ui_interface.closeBox();
		
	}
	
	this.compute = function(count, inputs, outputs) {
		var input0 = inputs[0];
		var output0 = outputs[0];
		var iSlow0 = this.fCheckbox0;
		var fSlow1 = (0.001 * this.fVslider0);
		var fSlow2 = (0.001 * this.fVslider1);
		var fSlow3 = (0.001 * this.fVslider2);
		var fSlow4 = (0.001 * this.fVslider3);
		var fSlow5 = (0.001 * this.fVslider4);
		var fSlow6 = (0.001 * this.fVslider5);
		var fSlow7 = (0.001 * this.fVslider6);
		var fSlow8 = (0.001 * this.fVslider7);
		var fSlow9 = (0.001 * this.fVslider8);
		var fSlow10 = (0.001 * this.fVslider9);
		for (var i = 0; (i < count); i = (i + 1)) {
			var fTemp0 = input0[i];
			var fTemp1 = (iSlow0?0:fTemp0);
			this.fVec0[0] = fTemp1;
			this.fRec10[0] = ((this.fConst9 * this.fRec10[1]) + (this.fConst10 * ((this.fConst2 * fTemp1) + (this.fConst11 * this.fVec0[1]))));
			this.fRec9[0] = (this.fRec10[0] - (this.fConst7 * ((this.fConst12 * this.fRec9[1]) + (this.fConst13 * this.fRec9[2]))));
			this.fRec8[0] = ((this.fConst7 * (((this.fConst5 * this.fRec9[0]) + (this.fConst6 * this.fRec9[1])) + (this.fConst5 * this.fRec9[2]))) - (this.fConst4 * ((this.fConst12 * this.fRec8[1]) + (this.fConst14 * this.fRec8[2]))));
			var fTemp2 = (this.fConst20 * this.fRec7[1]);
			this.fRec7[0] = ((this.fConst4 * (((this.fConst6 * this.fRec8[1]) + (this.fConst5 * this.fRec8[0])) + (this.fConst5 * this.fRec8[2]))) - (this.fConst17 * ((this.fConst18 * this.fRec7[2]) + fTemp2)));
			var fTemp3 = (this.fConst26 * this.fRec6[1]);
			this.fRec6[0] = ((this.fRec7[2] + (this.fConst17 * (fTemp2 + (this.fConst18 * this.fRec7[0])))) - (this.fConst23 * ((this.fConst24 * this.fRec6[2]) + fTemp3)));
			var fTemp4 = (this.fConst32 * this.fRec5[1]);
			this.fRec5[0] = ((this.fRec6[2] + (this.fConst23 * (fTemp3 + (this.fConst24 * this.fRec6[0])))) - (this.fConst29 * ((this.fConst30 * this.fRec5[2]) + fTemp4)));
			var fTemp5 = (this.fConst38 * this.fRec4[1]);
			this.fRec4[0] = ((this.fRec5[2] + (this.fConst29 * (fTemp4 + (this.fConst30 * this.fRec5[0])))) - (this.fConst35 * ((this.fConst36 * this.fRec4[2]) + fTemp5)));
			var fTemp6 = (this.fConst44 * this.fRec3[1]);
			this.fRec3[0] = ((this.fRec4[2] + (this.fConst35 * (fTemp5 + (this.fConst36 * this.fRec4[0])))) - (this.fConst41 * ((this.fConst42 * this.fRec3[2]) + fTemp6)));
			var fTemp7 = (this.fConst50 * this.fRec2[1]);
			this.fRec2[0] = ((this.fRec3[2] + (this.fConst41 * (fTemp6 + (this.fConst42 * this.fRec3[0])))) - (this.fConst47 * ((this.fConst48 * this.fRec2[2]) + fTemp7)));
			var fTemp8 = (this.fConst56 * this.fRec1[1]);
			this.fRec1[0] = ((this.fRec2[2] + (this.fConst47 * (fTemp7 + (this.fConst48 * this.fRec2[0])))) - (this.fConst53 * ((this.fConst54 * this.fRec1[2]) + fTemp8)));
			var fTemp9 = (this.fConst62 * this.fRec0[1]);
			this.fRec0[0] = ((this.fRec1[2] + (this.fConst53 * (fTemp8 + (this.fConst54 * this.fRec1[0])))) - (this.fConst59 * ((this.fConst60 * this.fRec0[2]) + fTemp9)));
			this.fRec11[0] = (fSlow1 + (0.999 * this.fRec11[1]));
			this.fRec24[0] = ((this.fConst9 * this.fRec24[1]) + (this.fConst10 * (fTemp1 + this.fVec0[1])));
			this.fRec23[0] = (this.fRec24[0] - (this.fConst7 * ((this.fConst12 * this.fRec23[1]) + (this.fConst13 * this.fRec23[2]))));
			this.fRec22[0] = ((this.fConst7 * (this.fRec23[2] + (this.fRec23[0] + (2 * this.fRec23[1])))) - (this.fConst4 * ((this.fConst12 * this.fRec22[1]) + (this.fConst14 * this.fRec22[2]))));
			var fTemp10 = (this.fRec22[2] + (this.fRec22[0] + (2 * this.fRec22[1])));
			this.fVec1[0] = fTemp10;
			this.fRec21[0] = ((this.fConst68 * this.fRec21[1]) + (this.fConst69 * ((this.fConst58 * fTemp10) + (this.fConst70 * this.fVec1[1]))));
			this.fRec20[0] = (this.fRec21[0] - (this.fConst66 * ((this.fConst62 * this.fRec20[1]) + (this.fConst71 * this.fRec20[2]))));
			this.fRec19[0] = ((this.fConst66 * (((this.fConst65 * this.fRec20[1]) + (this.fConst61 * this.fRec20[0])) + (this.fConst61 * this.fRec20[2]))) - (this.fConst64 * ((this.fConst62 * this.fRec19[1]) + (this.fConst72 * this.fRec19[2]))));
			var fTemp11 = (this.fConst20 * this.fRec18[1]);
			this.fRec18[0] = ((this.fConst64 * (((this.fConst65 * this.fRec19[1]) + (this.fConst61 * this.fRec19[0])) + (this.fConst61 * this.fRec19[2]))) - (this.fConst17 * (fTemp11 + (this.fConst18 * this.fRec18[2]))));
			var fTemp12 = (this.fConst26 * this.fRec17[1]);
			this.fRec17[0] = ((this.fRec18[2] + (this.fConst17 * (fTemp11 + (this.fConst18 * this.fRec18[0])))) - (this.fConst23 * (fTemp12 + (this.fConst24 * this.fRec17[2]))));
			var fTemp13 = (this.fConst32 * this.fRec16[1]);
			this.fRec16[0] = ((this.fRec17[2] + (this.fConst23 * (fTemp12 + (this.fConst24 * this.fRec17[0])))) - (this.fConst29 * (fTemp13 + (this.fConst30 * this.fRec16[2]))));
			var fTemp14 = (this.fConst38 * this.fRec15[1]);
			this.fRec15[0] = ((this.fRec16[2] + (this.fConst29 * (fTemp13 + (this.fConst30 * this.fRec16[0])))) - (this.fConst35 * (fTemp14 + (this.fConst36 * this.fRec15[2]))));
			var fTemp15 = (this.fConst44 * this.fRec14[1]);
			this.fRec14[0] = ((this.fRec15[2] + (this.fConst35 * (fTemp14 + (this.fConst36 * this.fRec15[0])))) - (this.fConst41 * (fTemp15 + (this.fConst42 * this.fRec14[2]))));
			var fTemp16 = (this.fConst50 * this.fRec13[1]);
			this.fRec13[0] = ((this.fRec14[2] + (this.fConst41 * (fTemp15 + (this.fConst42 * this.fRec14[0])))) - (this.fConst47 * (fTemp16 + (this.fConst48 * this.fRec13[2]))));
			var fTemp17 = (this.fConst56 * this.fRec12[1]);
			this.fRec12[0] = ((this.fRec13[2] + (this.fConst47 * (fTemp16 + (this.fConst48 * this.fRec13[0])))) - (this.fConst53 * (fTemp17 + (this.fConst54 * this.fRec12[2]))));
			this.fRec25[0] = (fSlow2 + (0.999 * this.fRec25[1]));
			this.fRec37[0] = ((this.fConst68 * this.fRec37[1]) + (this.fConst69 * (fTemp10 + this.fVec1[1])));
			this.fRec36[0] = (this.fRec37[0] - (this.fConst66 * ((this.fConst62 * this.fRec36[1]) + (this.fConst71 * this.fRec36[2]))));
			this.fRec35[0] = ((this.fConst66 * (this.fRec36[2] + (this.fRec36[0] + (2 * this.fRec36[1])))) - (this.fConst64 * ((this.fConst62 * this.fRec35[1]) + (this.fConst72 * this.fRec35[2]))));
			var fTemp18 = (this.fRec35[2] + (this.fRec35[0] + (2 * this.fRec35[1])));
			this.fVec2[0] = fTemp18;
			this.fRec34[0] = ((this.fConst78 * this.fRec34[1]) + (this.fConst79 * ((this.fConst52 * fTemp18) + (this.fConst80 * this.fVec2[1]))));
			this.fRec33[0] = (this.fRec34[0] - (this.fConst76 * ((this.fConst56 * this.fRec33[1]) + (this.fConst81 * this.fRec33[2]))));
			this.fRec32[0] = ((this.fConst76 * (((this.fConst55 * this.fRec33[0]) + (this.fConst75 * this.fRec33[1])) + (this.fConst55 * this.fRec33[2]))) - (this.fConst74 * ((this.fConst56 * this.fRec32[1]) + (this.fConst82 * this.fRec32[2]))));
			var fTemp19 = (this.fConst20 * this.fRec31[1]);
			this.fRec31[0] = ((this.fConst74 * (((this.fConst75 * this.fRec32[1]) + (this.fConst55 * this.fRec32[0])) + (this.fConst55 * this.fRec32[2]))) - (this.fConst17 * (fTemp19 + (this.fConst18 * this.fRec31[2]))));
			var fTemp20 = (this.fConst26 * this.fRec30[1]);
			this.fRec30[0] = ((this.fRec31[2] + (this.fConst17 * (fTemp19 + (this.fConst18 * this.fRec31[0])))) - (this.fConst23 * (fTemp20 + (this.fConst24 * this.fRec30[2]))));
			var fTemp21 = (this.fConst32 * this.fRec29[1]);
			this.fRec29[0] = ((this.fRec30[2] + (this.fConst23 * (fTemp20 + (this.fConst24 * this.fRec30[0])))) - (this.fConst29 * (fTemp21 + (this.fConst30 * this.fRec29[2]))));
			var fTemp22 = (this.fConst38 * this.fRec28[1]);
			this.fRec28[0] = ((this.fRec29[2] + (this.fConst29 * (fTemp21 + (this.fConst30 * this.fRec29[0])))) - (this.fConst35 * (fTemp22 + (this.fConst36 * this.fRec28[2]))));
			var fTemp23 = (this.fConst44 * this.fRec27[1]);
			this.fRec27[0] = ((this.fRec28[2] + (this.fConst35 * (fTemp22 + (this.fConst36 * this.fRec28[0])))) - (this.fConst41 * (fTemp23 + (this.fConst42 * this.fRec27[2]))));
			var fTemp24 = (this.fConst50 * this.fRec26[1]);
			this.fRec26[0] = ((this.fRec27[2] + (this.fConst41 * (fTemp23 + (this.fConst42 * this.fRec27[0])))) - (this.fConst47 * (fTemp24 + (this.fConst48 * this.fRec26[2]))));
			this.fRec38[0] = (fSlow3 + (0.999 * this.fRec38[1]));
			this.fRec49[0] = ((this.fConst78 * this.fRec49[1]) + (this.fConst79 * (fTemp18 + this.fVec2[1])));
			this.fRec48[0] = (this.fRec49[0] - (this.fConst76 * ((this.fConst56 * this.fRec48[1]) + (this.fConst81 * this.fRec48[2]))));
			this.fRec47[0] = ((this.fConst76 * (this.fRec48[2] + (this.fRec48[0] + (2 * this.fRec48[1])))) - (this.fConst74 * ((this.fConst56 * this.fRec47[1]) + (this.fConst82 * this.fRec47[2]))));
			var fTemp25 = (this.fRec47[2] + (this.fRec47[0] + (2 * this.fRec47[1])));
			this.fVec3[0] = fTemp25;
			this.fRec46[0] = ((this.fConst88 * this.fRec46[1]) + (this.fConst89 * ((this.fConst46 * fTemp25) + (this.fConst90 * this.fVec3[1]))));
			this.fRec45[0] = (this.fRec46[0] - (this.fConst86 * ((this.fConst50 * this.fRec45[1]) + (this.fConst91 * this.fRec45[2]))));
			this.fRec44[0] = ((this.fConst86 * (((this.fConst49 * this.fRec45[0]) + (this.fConst85 * this.fRec45[1])) + (this.fConst49 * this.fRec45[2]))) - (this.fConst84 * ((this.fConst50 * this.fRec44[1]) + (this.fConst92 * this.fRec44[2]))));
			var fTemp26 = (this.fConst20 * this.fRec43[1]);
			this.fRec43[0] = ((this.fConst84 * (((this.fConst85 * this.fRec44[1]) + (this.fConst49 * this.fRec44[0])) + (this.fConst49 * this.fRec44[2]))) - (this.fConst17 * (fTemp26 + (this.fConst18 * this.fRec43[2]))));
			var fTemp27 = (this.fConst26 * this.fRec42[1]);
			this.fRec42[0] = ((this.fRec43[2] + (this.fConst17 * (fTemp26 + (this.fConst18 * this.fRec43[0])))) - (this.fConst23 * (fTemp27 + (this.fConst24 * this.fRec42[2]))));
			var fTemp28 = (this.fConst32 * this.fRec41[1]);
			this.fRec41[0] = ((this.fRec42[2] + (this.fConst23 * (fTemp27 + (this.fConst24 * this.fRec42[0])))) - (this.fConst29 * (fTemp28 + (this.fConst30 * this.fRec41[2]))));
			var fTemp29 = (this.fConst38 * this.fRec40[1]);
			this.fRec40[0] = ((this.fRec41[2] + (this.fConst29 * (fTemp28 + (this.fConst30 * this.fRec41[0])))) - (this.fConst35 * (fTemp29 + (this.fConst36 * this.fRec40[2]))));
			var fTemp30 = (this.fConst44 * this.fRec39[1]);
			this.fRec39[0] = ((this.fRec40[2] + (this.fConst35 * (fTemp29 + (this.fConst36 * this.fRec40[0])))) - (this.fConst41 * (fTemp30 + (this.fConst42 * this.fRec39[2]))));
			this.fRec50[0] = (fSlow4 + (0.999 * this.fRec50[1]));
			this.fRec60[0] = ((this.fConst88 * this.fRec60[1]) + (this.fConst89 * (fTemp25 + this.fVec3[1])));
			this.fRec59[0] = (this.fRec60[0] - (this.fConst86 * ((this.fConst50 * this.fRec59[1]) + (this.fConst91 * this.fRec59[2]))));
			this.fRec58[0] = ((this.fConst86 * (this.fRec59[2] + (this.fRec59[0] + (2 * this.fRec59[1])))) - (this.fConst84 * ((this.fConst50 * this.fRec58[1]) + (this.fConst92 * this.fRec58[2]))));
			var fTemp31 = (this.fRec58[2] + (this.fRec58[0] + (2 * this.fRec58[1])));
			this.fVec4[0] = fTemp31;
			this.fRec57[0] = ((this.fConst98 * this.fRec57[1]) + (this.fConst99 * ((this.fConst40 * fTemp31) + (this.fConst100 * this.fVec4[1]))));
			this.fRec56[0] = (this.fRec57[0] - (this.fConst96 * ((this.fConst44 * this.fRec56[1]) + (this.fConst101 * this.fRec56[2]))));
			this.fRec55[0] = ((this.fConst96 * (((this.fConst43 * this.fRec56[0]) + (this.fConst95 * this.fRec56[1])) + (this.fConst43 * this.fRec56[2]))) - (this.fConst94 * ((this.fConst44 * this.fRec55[1]) + (this.fConst102 * this.fRec55[2]))));
			var fTemp32 = (this.fConst20 * this.fRec54[1]);
			this.fRec54[0] = ((this.fConst94 * (((this.fConst95 * this.fRec55[1]) + (this.fConst43 * this.fRec55[0])) + (this.fConst43 * this.fRec55[2]))) - (this.fConst17 * (fTemp32 + (this.fConst18 * this.fRec54[2]))));
			var fTemp33 = (this.fConst26 * this.fRec53[1]);
			this.fRec53[0] = ((this.fRec54[2] + (this.fConst17 * (fTemp32 + (this.fConst18 * this.fRec54[0])))) - (this.fConst23 * (fTemp33 + (this.fConst24 * this.fRec53[2]))));
			var fTemp34 = (this.fConst32 * this.fRec52[1]);
			this.fRec52[0] = ((this.fRec53[2] + (this.fConst23 * (fTemp33 + (this.fConst24 * this.fRec53[0])))) - (this.fConst29 * (fTemp34 + (this.fConst30 * this.fRec52[2]))));
			var fTemp35 = (this.fConst38 * this.fRec51[1]);
			this.fRec51[0] = ((this.fRec52[2] + (this.fConst29 * (fTemp34 + (this.fConst30 * this.fRec52[0])))) - (this.fConst35 * (fTemp35 + (this.fConst36 * this.fRec51[2]))));
			this.fRec61[0] = (fSlow5 + (0.999 * this.fRec61[1]));
			this.fRec70[0] = ((this.fConst98 * this.fRec70[1]) + (this.fConst99 * (fTemp31 + this.fVec4[1])));
			this.fRec69[0] = (this.fRec70[0] - (this.fConst96 * ((this.fConst44 * this.fRec69[1]) + (this.fConst101 * this.fRec69[2]))));
			this.fRec68[0] = ((this.fConst96 * (this.fRec69[2] + (this.fRec69[0] + (2 * this.fRec69[1])))) - (this.fConst94 * ((this.fConst44 * this.fRec68[1]) + (this.fConst102 * this.fRec68[2]))));
			var fTemp36 = (this.fRec68[2] + (this.fRec68[0] + (2 * this.fRec68[1])));
			this.fVec5[0] = fTemp36;
			this.fRec67[0] = ((this.fConst108 * this.fRec67[1]) + (this.fConst109 * ((this.fConst34 * fTemp36) + (this.fConst110 * this.fVec5[1]))));
			this.fRec66[0] = (this.fRec67[0] - (this.fConst106 * ((this.fConst38 * this.fRec66[1]) + (this.fConst111 * this.fRec66[2]))));
			this.fRec65[0] = ((this.fConst106 * (((this.fConst37 * this.fRec66[0]) + (this.fConst105 * this.fRec66[1])) + (this.fConst37 * this.fRec66[2]))) - (this.fConst104 * ((this.fConst38 * this.fRec65[1]) + (this.fConst112 * this.fRec65[2]))));
			var fTemp37 = (this.fConst20 * this.fRec64[1]);
			this.fRec64[0] = ((this.fConst104 * (((this.fConst105 * this.fRec65[1]) + (this.fConst37 * this.fRec65[0])) + (this.fConst37 * this.fRec65[2]))) - (this.fConst17 * (fTemp37 + (this.fConst18 * this.fRec64[2]))));
			var fTemp38 = (this.fConst26 * this.fRec63[1]);
			this.fRec63[0] = ((this.fRec64[2] + (this.fConst17 * (fTemp37 + (this.fConst18 * this.fRec64[0])))) - (this.fConst23 * (fTemp38 + (this.fConst24 * this.fRec63[2]))));
			var fTemp39 = (this.fConst32 * this.fRec62[1]);
			this.fRec62[0] = ((this.fRec63[2] + (this.fConst23 * (fTemp38 + (this.fConst24 * this.fRec63[0])))) - (this.fConst29 * (fTemp39 + (this.fConst30 * this.fRec62[2]))));
			this.fRec71[0] = (fSlow6 + (0.999 * this.fRec71[1]));
			this.fRec79[0] = ((this.fConst108 * this.fRec79[1]) + (this.fConst109 * (fTemp36 + this.fVec5[1])));
			this.fRec78[0] = (this.fRec79[0] - (this.fConst106 * ((this.fConst38 * this.fRec78[1]) + (this.fConst111 * this.fRec78[2]))));
			this.fRec77[0] = ((this.fConst106 * (this.fRec78[2] + (this.fRec78[0] + (2 * this.fRec78[1])))) - (this.fConst104 * ((this.fConst38 * this.fRec77[1]) + (this.fConst112 * this.fRec77[2]))));
			var fTemp40 = (this.fRec77[2] + (this.fRec77[0] + (2 * this.fRec77[1])));
			this.fVec6[0] = fTemp40;
			this.fRec76[0] = ((this.fConst118 * this.fRec76[1]) + (this.fConst119 * ((this.fConst28 * fTemp40) + (this.fConst120 * this.fVec6[1]))));
			this.fRec75[0] = (this.fRec76[0] - (this.fConst116 * ((this.fConst32 * this.fRec75[1]) + (this.fConst121 * this.fRec75[2]))));
			this.fRec74[0] = ((this.fConst116 * (((this.fConst31 * this.fRec75[0]) + (this.fConst115 * this.fRec75[1])) + (this.fConst31 * this.fRec75[2]))) - (this.fConst114 * ((this.fConst32 * this.fRec74[1]) + (this.fConst122 * this.fRec74[2]))));
			var fTemp41 = (this.fConst20 * this.fRec73[1]);
			this.fRec73[0] = ((this.fConst114 * (((this.fConst115 * this.fRec74[1]) + (this.fConst31 * this.fRec74[0])) + (this.fConst31 * this.fRec74[2]))) - (this.fConst17 * (fTemp41 + (this.fConst18 * this.fRec73[2]))));
			var fTemp42 = (this.fConst26 * this.fRec72[1]);
			this.fRec72[0] = ((this.fRec73[2] + (this.fConst17 * (fTemp41 + (this.fConst18 * this.fRec73[0])))) - (this.fConst23 * (fTemp42 + (this.fConst24 * this.fRec72[2]))));
			this.fRec80[0] = (fSlow7 + (0.999 * this.fRec80[1]));
			this.fRec87[0] = ((this.fConst118 * this.fRec87[1]) + (this.fConst119 * (fTemp40 + this.fVec6[1])));
			this.fRec86[0] = (this.fRec87[0] - (this.fConst116 * ((this.fConst32 * this.fRec86[1]) + (this.fConst121 * this.fRec86[2]))));
			this.fRec85[0] = ((this.fConst116 * (this.fRec86[2] + (this.fRec86[0] + (2 * this.fRec86[1])))) - (this.fConst114 * ((this.fConst32 * this.fRec85[1]) + (this.fConst122 * this.fRec85[2]))));
			var fTemp43 = (this.fRec85[2] + (this.fRec85[0] + (2 * this.fRec85[1])));
			this.fVec7[0] = fTemp43;
			this.fRec84[0] = ((this.fConst128 * this.fRec84[1]) + (this.fConst129 * ((this.fConst22 * fTemp43) + (this.fConst130 * this.fVec7[1]))));
			this.fRec83[0] = (this.fRec84[0] - (this.fConst126 * ((this.fConst26 * this.fRec83[1]) + (this.fConst131 * this.fRec83[2]))));
			this.fRec82[0] = ((this.fConst126 * (((this.fConst25 * this.fRec83[0]) + (this.fConst125 * this.fRec83[1])) + (this.fConst25 * this.fRec83[2]))) - (this.fConst124 * ((this.fConst26 * this.fRec82[1]) + (this.fConst132 * this.fRec82[2]))));
			var fTemp44 = (this.fConst20 * this.fRec81[1]);
			this.fRec81[0] = ((this.fConst124 * (((this.fConst125 * this.fRec82[1]) + (this.fConst25 * this.fRec82[0])) + (this.fConst25 * this.fRec82[2]))) - (this.fConst17 * (fTemp44 + (this.fConst18 * this.fRec81[2]))));
			this.fRec88[0] = (fSlow8 + (0.999 * this.fRec88[1]));
			this.fRec94[0] = ((this.fConst128 * this.fRec94[1]) + (this.fConst129 * (fTemp43 + this.fVec7[1])));
			this.fRec93[0] = (this.fRec94[0] - (this.fConst126 * ((this.fConst26 * this.fRec93[1]) + (this.fConst131 * this.fRec93[2]))));
			this.fRec92[0] = ((this.fConst126 * (this.fRec93[2] + (this.fRec93[0] + (2 * this.fRec93[1])))) - (this.fConst124 * ((this.fConst26 * this.fRec92[1]) + (this.fConst132 * this.fRec92[2]))));
			var fTemp45 = (this.fRec92[2] + (this.fRec92[0] + (2 * this.fRec92[1])));
			this.fVec8[0] = fTemp45;
			this.fRec91[0] = ((this.fConst137 * this.fRec91[1]) + (this.fConst138 * ((this.fConst16 * fTemp45) + (this.fConst139 * this.fVec8[1]))));
			this.fRec90[0] = (this.fRec91[0] - (this.fConst135 * ((this.fConst20 * this.fRec90[1]) + (this.fConst140 * this.fRec90[2]))));
			this.fRec89[0] = ((this.fConst135 * (((this.fConst19 * this.fRec90[0]) + (this.fConst134 * this.fRec90[1])) + (this.fConst19 * this.fRec90[2]))) - (this.fConst133 * ((this.fConst20 * this.fRec89[1]) + (this.fConst141 * this.fRec89[2]))));
			this.fRec95[0] = (fSlow9 + (0.999 * this.fRec95[1]));
			this.fRec98[0] = ((this.fConst137 * this.fRec98[1]) + (this.fConst138 * (fTemp45 + this.fVec8[1])));
			this.fRec97[0] = (this.fRec98[0] - (this.fConst135 * ((this.fConst20 * this.fRec97[1]) + (this.fConst140 * this.fRec97[2]))));
			this.fRec96[0] = ((this.fConst135 * (this.fRec97[2] + (this.fRec97[0] + (2 * this.fRec97[1])))) - (this.fConst133 * ((this.fConst20 * this.fRec96[1]) + (this.fConst141 * this.fRec96[2]))));
			this.fRec99[0] = (fSlow10 + (0.999 * this.fRec99[1]));
			output0[i] = (iSlow0?fTemp0:((((((((((this.fRec0[2] + (this.fConst59 * (fTemp9 + (this.fConst60 * this.fRec0[0])))) * Math.pow(10, (0.05 * this.fRec11[0]))) + ((this.fRec12[2] + (this.fConst53 * (fTemp17 + (this.fConst54 * this.fRec12[0])))) * Math.pow(10, (0.05 * this.fRec25[0])))) + ((this.fRec26[2] + (this.fConst47 * (fTemp24 + (this.fConst48 * this.fRec26[0])))) * Math.pow(10, (0.05 * this.fRec38[0])))) + ((this.fRec39[2] + (this.fConst41 * (fTemp30 + (this.fConst42 * this.fRec39[0])))) * Math.pow(10, (0.05 * this.fRec50[0])))) + ((this.fRec51[2] + (this.fConst35 * (fTemp35 + (this.fConst36 * this.fRec51[0])))) * Math.pow(10, (0.05 * this.fRec61[0])))) + ((this.fRec62[2] + (this.fConst29 * (fTemp39 + (this.fConst30 * this.fRec62[0])))) * Math.pow(10, (0.05 * this.fRec71[0])))) + ((this.fRec72[2] + (this.fConst23 * (fTemp42 + (this.fConst24 * this.fRec72[0])))) * Math.pow(10, (0.05 * this.fRec80[0])))) + ((this.fRec81[2] + (this.fConst17 * (fTemp44 + (this.fConst18 * this.fRec81[0])))) * Math.pow(10, (0.05 * this.fRec88[0])))) + (this.fConst133 * (((((this.fConst134 * this.fRec89[1]) + (this.fConst19 * this.fRec89[0])) + (this.fConst19 * this.fRec89[2])) * Math.pow(10, (0.05 * this.fRec95[0]))) + ((this.fRec96[2] + (this.fRec96[0] + (2 * this.fRec96[1]))) * Math.pow(10, (0.05 * this.fRec99[0])))))));
			this.fVec0[1] = this.fVec0[0];
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
			this.fRec0[2] = this.fRec0[1];
			this.fRec0[1] = this.fRec0[0];
			this.fRec11[1] = this.fRec11[0];
			this.fRec24[1] = this.fRec24[0];
			this.fRec23[2] = this.fRec23[1];
			this.fRec23[1] = this.fRec23[0];
			this.fRec22[2] = this.fRec22[1];
			this.fRec22[1] = this.fRec22[0];
			this.fVec1[1] = this.fVec1[0];
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
			this.fRec25[1] = this.fRec25[0];
			this.fRec37[1] = this.fRec37[0];
			this.fRec36[2] = this.fRec36[1];
			this.fRec36[1] = this.fRec36[0];
			this.fRec35[2] = this.fRec35[1];
			this.fRec35[1] = this.fRec35[0];
			this.fVec2[1] = this.fVec2[0];
			this.fRec34[1] = this.fRec34[0];
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
			this.fRec27[2] = this.fRec27[1];
			this.fRec27[1] = this.fRec27[0];
			this.fRec26[2] = this.fRec26[1];
			this.fRec26[1] = this.fRec26[0];
			this.fRec38[1] = this.fRec38[0];
			this.fRec49[1] = this.fRec49[0];
			this.fRec48[2] = this.fRec48[1];
			this.fRec48[1] = this.fRec48[0];
			this.fRec47[2] = this.fRec47[1];
			this.fRec47[1] = this.fRec47[0];
			this.fVec3[1] = this.fVec3[0];
			this.fRec46[1] = this.fRec46[0];
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
			this.fRec39[2] = this.fRec39[1];
			this.fRec39[1] = this.fRec39[0];
			this.fRec50[1] = this.fRec50[0];
			this.fRec60[1] = this.fRec60[0];
			this.fRec59[2] = this.fRec59[1];
			this.fRec59[1] = this.fRec59[0];
			this.fRec58[2] = this.fRec58[1];
			this.fRec58[1] = this.fRec58[0];
			this.fVec4[1] = this.fVec4[0];
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
			this.fRec51[2] = this.fRec51[1];
			this.fRec51[1] = this.fRec51[0];
			this.fRec61[1] = this.fRec61[0];
			this.fRec70[1] = this.fRec70[0];
			this.fRec69[2] = this.fRec69[1];
			this.fRec69[1] = this.fRec69[0];
			this.fRec68[2] = this.fRec68[1];
			this.fRec68[1] = this.fRec68[0];
			this.fVec5[1] = this.fVec5[0];
			this.fRec67[1] = this.fRec67[0];
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
			this.fRec71[1] = this.fRec71[0];
			this.fRec79[1] = this.fRec79[0];
			this.fRec78[2] = this.fRec78[1];
			this.fRec78[1] = this.fRec78[0];
			this.fRec77[2] = this.fRec77[1];
			this.fRec77[1] = this.fRec77[0];
			this.fVec6[1] = this.fVec6[0];
			this.fRec76[1] = this.fRec76[0];
			this.fRec75[2] = this.fRec75[1];
			this.fRec75[1] = this.fRec75[0];
			this.fRec74[2] = this.fRec74[1];
			this.fRec74[1] = this.fRec74[0];
			this.fRec73[2] = this.fRec73[1];
			this.fRec73[1] = this.fRec73[0];
			this.fRec72[2] = this.fRec72[1];
			this.fRec72[1] = this.fRec72[0];
			this.fRec80[1] = this.fRec80[0];
			this.fRec87[1] = this.fRec87[0];
			this.fRec86[2] = this.fRec86[1];
			this.fRec86[1] = this.fRec86[0];
			this.fRec85[2] = this.fRec85[1];
			this.fRec85[1] = this.fRec85[0];
			this.fVec7[1] = this.fVec7[0];
			this.fRec84[1] = this.fRec84[0];
			this.fRec83[2] = this.fRec83[1];
			this.fRec83[1] = this.fRec83[0];
			this.fRec82[2] = this.fRec82[1];
			this.fRec82[1] = this.fRec82[0];
			this.fRec81[2] = this.fRec81[1];
			this.fRec81[1] = this.fRec81[0];
			this.fRec88[1] = this.fRec88[0];
			this.fRec94[1] = this.fRec94[0];
			this.fRec93[2] = this.fRec93[1];
			this.fRec93[1] = this.fRec93[0];
			this.fRec92[2] = this.fRec92[1];
			this.fRec92[1] = this.fRec92[0];
			this.fVec8[1] = this.fVec8[0];
			this.fRec91[1] = this.fRec91[0];
			this.fRec90[2] = this.fRec90[1];
			this.fRec90[1] = this.fRec90[0];
			this.fRec89[2] = this.fRec89[1];
			this.fRec89[1] = this.fRec89[0];
			this.fRec95[1] = this.fRec95[0];
			this.fRec98[1] = this.fRec98[0];
			this.fRec97[2] = this.fRec97[1];
			this.fRec97[1] = this.fRec97[0];
			this.fRec96[2] = this.fRec96[1];
			this.fRec96[1] = this.fRec96[0];
			this.fRec99[1] = this.fRec99[0];
			
		}
		
	}
	
}

