/* ------------------------------------------------------------
name: "bells"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static double mydsp_faustpower2_f(double value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fButton0;
	double fVec0_perm[4];
	double fYec0[256];
	int fYec0_idx;
	int fYec0_idx_save;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fRec1_perm[4];
	double fConst7;
	double fRec0_perm[4];
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fButton1;
	double fVec1_perm[4];
	double fYec1[256];
	int fYec1_idx;
	int fYec1_idx_save;
	double fRec3_perm[4];
	double fRec2_perm[4];
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fButton2;
	double fVec2_perm[4];
	double fYec2[256];
	int fYec2_idx;
	int fYec2_idx_save;
	double fRec5_perm[4];
	double fRec4_perm[4];
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fButton3;
	double fVec3_perm[4];
	double fYec3[256];
	int fYec3_idx;
	int fYec3_idx_save;
	double fRec7_perm[4];
	double fRec6_perm[4];
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fButton4;
	double fVec4_perm[4];
	double fYec4[256];
	int fYec4_idx;
	int fYec4_idx_save;
	double fRec9_perm[4];
	double fRec8_perm[4];
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fButton5;
	double fVec5_perm[4];
	double fYec5[256];
	int fYec5_idx;
	int fYec5_idx_save;
	double fRec11_perm[4];
	double fRec10_perm[4];
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fButton6;
	double fVec6_perm[4];
	double fYec6[256];
	int fYec6_idx;
	int fYec6_idx_save;
	double fRec13_perm[4];
	double fRec12_perm[4];
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fButton7;
	double fVec7_perm[4];
	double fYec7[256];
	int fYec7_idx;
	int fYec7_idx_save;
	double fRec15_perm[4];
	double fRec14_perm[4];
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fButton8;
	double fVec8_perm[4];
	double fYec8[256];
	int fYec8_idx;
	int fYec8_idx_save;
	double fRec17_perm[4];
	double fRec16_perm[4];
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fButton9;
	double fVec9_perm[4];
	double fYec9[256];
	int fYec9_idx;
	int fYec9_idx_save;
	double fRec19_perm[4];
	double fRec18_perm[4];
	double fYec10[128];
	int fYec10_idx;
	int fYec10_idx_save;
	double fConst8;
	double fConst9;
	double fRec21_perm[4];
	double fRec20_perm[4];
	double fYec11[128];
	int fYec11_idx;
	int fYec11_idx_save;
	double fConst10;
	double fConst11;
	double fRec23_perm[4];
	double fRec22_perm[4];
	double fYec12[128];
	int fYec12_idx;
	int fYec12_idx_save;
	double fConst12;
	double fConst13;
	double fRec25_perm[4];
	double fRec24_perm[4];
	double fYec13[128];
	int fYec13_idx;
	int fYec13_idx_save;
	double fConst14;
	double fConst15;
	double fRec27_perm[4];
	double fRec26_perm[4];
	double fYec14[128];
	int fYec14_idx;
	int fYec14_idx_save;
	double fConst16;
	double fConst17;
	double fRec29_perm[4];
	double fRec28_perm[4];
	double fYec15[128];
	int fYec15_idx;
	int fYec15_idx_save;
	double fConst18;
	double fConst19;
	double fRec31_perm[4];
	double fRec30_perm[4];
	double fYec16[512];
	int fYec16_idx;
	int fYec16_idx_save;
	double fConst20;
	double fConst21;
	double fRec33_perm[4];
	double fRec32_perm[4];
	double fYec17[512];
	int fYec17_idx;
	int fYec17_idx_save;
	double fConst22;
	double fConst23;
	double fRec35_perm[4];
	double fRec34_perm[4];
	double fYec18[1024];
	int fYec18_idx;
	int fYec18_idx_save;
	double fConst24;
	double fConst25;
	double fRec37_perm[4];
	double fRec36_perm[4];
	double fYec19[1024];
	int fYec19_idx;
	int fYec19_idx_save;
	double fConst26;
	double fConst27;
	double fRec39_perm[4];
	double fRec38_perm[4];
	double fYec20[128];
	int fYec20_idx;
	int fYec20_idx_save;
	double fRec41_perm[4];
	double fRec40_perm[4];
	double fYec21[128];
	int fYec21_idx;
	int fYec21_idx_save;
	double fRec43_perm[4];
	double fRec42_perm[4];
	double fYec22[128];
	int fYec22_idx;
	int fYec22_idx_save;
	double fRec45_perm[4];
	double fRec44_perm[4];
	double fYec23[128];
	int fYec23_idx;
	int fYec23_idx_save;
	double fRec47_perm[4];
	double fRec46_perm[4];
	double fYec24[128];
	int fYec24_idx;
	int fYec24_idx_save;
	double fRec49_perm[4];
	double fRec48_perm[4];
	double fYec25[128];
	int fYec25_idx;
	int fYec25_idx_save;
	double fRec51_perm[4];
	double fRec50_perm[4];
	double fYec26[512];
	int fYec26_idx;
	int fYec26_idx_save;
	double fRec53_perm[4];
	double fRec52_perm[4];
	double fYec27[512];
	int fYec27_idx;
	int fYec27_idx_save;
	double fRec55_perm[4];
	double fRec54_perm[4];
	double fYec28[1024];
	int fYec28_idx;
	int fYec28_idx_save;
	double fRec57_perm[4];
	double fRec56_perm[4];
	double fYec29[1024];
	int fYec29_idx;
	int fYec29_idx_save;
	double fRec59_perm[4];
	double fRec58_perm[4];
	double fYec30[128];
	int fYec30_idx;
	int fYec30_idx_save;
	double fRec61_perm[4];
	double fRec60_perm[4];
	double fYec31[128];
	int fYec31_idx;
	int fYec31_idx_save;
	double fRec63_perm[4];
	double fRec62_perm[4];
	double fYec32[128];
	int fYec32_idx;
	int fYec32_idx_save;
	double fRec65_perm[4];
	double fRec64_perm[4];
	double fYec33[128];
	int fYec33_idx;
	int fYec33_idx_save;
	double fRec67_perm[4];
	double fRec66_perm[4];
	double fYec34[128];
	int fYec34_idx;
	int fYec34_idx_save;
	double fRec69_perm[4];
	double fRec68_perm[4];
	double fYec35[128];
	int fYec35_idx;
	int fYec35_idx_save;
	double fRec71_perm[4];
	double fRec70_perm[4];
	double fYec36[512];
	int fYec36_idx;
	int fYec36_idx_save;
	double fRec73_perm[4];
	double fRec72_perm[4];
	double fYec37[512];
	int fYec37_idx;
	int fYec37_idx_save;
	double fRec75_perm[4];
	double fRec74_perm[4];
	double fYec38[1024];
	int fYec38_idx;
	int fYec38_idx_save;
	double fRec77_perm[4];
	double fRec76_perm[4];
	double fYec39[1024];
	int fYec39_idx;
	int fYec39_idx_save;
	double fRec79_perm[4];
	double fRec78_perm[4];
	double fYec40[128];
	int fYec40_idx;
	int fYec40_idx_save;
	double fRec81_perm[4];
	double fRec80_perm[4];
	double fYec41[128];
	int fYec41_idx;
	int fYec41_idx_save;
	double fRec83_perm[4];
	double fRec82_perm[4];
	double fYec42[128];
	int fYec42_idx;
	int fYec42_idx_save;
	double fRec85_perm[4];
	double fRec84_perm[4];
	double fYec43[128];
	int fYec43_idx;
	int fYec43_idx_save;
	double fRec87_perm[4];
	double fRec86_perm[4];
	double fYec44[128];
	int fYec44_idx;
	int fYec44_idx_save;
	double fRec89_perm[4];
	double fRec88_perm[4];
	double fYec45[128];
	int fYec45_idx;
	int fYec45_idx_save;
	double fRec91_perm[4];
	double fRec90_perm[4];
	double fYec46[512];
	int fYec46_idx;
	int fYec46_idx_save;
	double fRec93_perm[4];
	double fRec92_perm[4];
	double fYec47[512];
	int fYec47_idx;
	int fYec47_idx_save;
	double fRec95_perm[4];
	double fRec94_perm[4];
	double fYec48[1024];
	int fYec48_idx;
	int fYec48_idx_save;
	double fRec97_perm[4];
	double fRec96_perm[4];
	double fYec49[1024];
	int fYec49_idx;
	int fYec49_idx_save;
	double fRec99_perm[4];
	double fRec98_perm[4];
	double fYec50[128];
	int fYec50_idx;
	int fYec50_idx_save;
	double fRec101_perm[4];
	double fRec100_perm[4];
	double fYec51[128];
	int fYec51_idx;
	int fYec51_idx_save;
	double fRec103_perm[4];
	double fRec102_perm[4];
	double fYec52[128];
	int fYec52_idx;
	int fYec52_idx_save;
	double fRec105_perm[4];
	double fRec104_perm[4];
	double fYec53[128];
	int fYec53_idx;
	int fYec53_idx_save;
	double fRec107_perm[4];
	double fRec106_perm[4];
	double fYec54[128];
	int fYec54_idx;
	int fYec54_idx_save;
	double fRec109_perm[4];
	double fRec108_perm[4];
	double fYec55[128];
	int fYec55_idx;
	int fYec55_idx_save;
	double fRec111_perm[4];
	double fRec110_perm[4];
	double fYec56[512];
	int fYec56_idx;
	int fYec56_idx_save;
	double fRec113_perm[4];
	double fRec112_perm[4];
	double fYec57[512];
	int fYec57_idx;
	int fYec57_idx_save;
	double fRec115_perm[4];
	double fRec114_perm[4];
	double fYec58[1024];
	int fYec58_idx;
	int fYec58_idx_save;
	double fRec117_perm[4];
	double fRec116_perm[4];
	double fYec59[1024];
	int fYec59_idx;
	int fYec59_idx_save;
	double fRec119_perm[4];
	double fRec118_perm[4];
	double fYec60[128];
	int fYec60_idx;
	int fYec60_idx_save;
	double fRec121_perm[4];
	double fRec120_perm[4];
	double fYec61[128];
	int fYec61_idx;
	int fYec61_idx_save;
	double fRec123_perm[4];
	double fRec122_perm[4];
	double fYec62[128];
	int fYec62_idx;
	int fYec62_idx_save;
	double fRec125_perm[4];
	double fRec124_perm[4];
	double fYec63[128];
	int fYec63_idx;
	int fYec63_idx_save;
	double fRec127_perm[4];
	double fRec126_perm[4];
	double fYec64[128];
	int fYec64_idx;
	int fYec64_idx_save;
	double fRec129_perm[4];
	double fRec128_perm[4];
	double fYec65[128];
	int fYec65_idx;
	int fYec65_idx_save;
	double fRec131_perm[4];
	double fRec130_perm[4];
	double fYec66[512];
	int fYec66_idx;
	int fYec66_idx_save;
	double fRec133_perm[4];
	double fRec132_perm[4];
	double fYec67[512];
	int fYec67_idx;
	int fYec67_idx_save;
	double fRec135_perm[4];
	double fRec134_perm[4];
	double fYec68[1024];
	int fYec68_idx;
	int fYec68_idx_save;
	double fRec137_perm[4];
	double fRec136_perm[4];
	double fYec69[1024];
	int fYec69_idx;
	int fYec69_idx_save;
	double fRec139_perm[4];
	double fRec138_perm[4];
	double fYec70[128];
	int fYec70_idx;
	int fYec70_idx_save;
	double fRec141_perm[4];
	double fRec140_perm[4];
	double fYec71[128];
	int fYec71_idx;
	int fYec71_idx_save;
	double fRec143_perm[4];
	double fRec142_perm[4];
	double fYec72[128];
	int fYec72_idx;
	int fYec72_idx_save;
	double fRec145_perm[4];
	double fRec144_perm[4];
	double fYec73[128];
	int fYec73_idx;
	int fYec73_idx_save;
	double fRec147_perm[4];
	double fRec146_perm[4];
	double fYec74[128];
	int fYec74_idx;
	int fYec74_idx_save;
	double fRec149_perm[4];
	double fRec148_perm[4];
	double fYec75[128];
	int fYec75_idx;
	int fYec75_idx_save;
	double fRec151_perm[4];
	double fRec150_perm[4];
	double fYec76[512];
	int fYec76_idx;
	int fYec76_idx_save;
	double fRec153_perm[4];
	double fRec152_perm[4];
	double fYec77[512];
	int fYec77_idx;
	int fYec77_idx_save;
	double fRec155_perm[4];
	double fRec154_perm[4];
	double fYec78[1024];
	int fYec78_idx;
	int fYec78_idx_save;
	double fRec157_perm[4];
	double fRec156_perm[4];
	double fYec79[1024];
	int fYec79_idx;
	int fYec79_idx_save;
	double fRec159_perm[4];
	double fRec158_perm[4];
	double fYec80[128];
	int fYec80_idx;
	int fYec80_idx_save;
	double fRec161_perm[4];
	double fRec160_perm[4];
	double fYec81[128];
	int fYec81_idx;
	int fYec81_idx_save;
	double fRec163_perm[4];
	double fRec162_perm[4];
	double fYec82[128];
	int fYec82_idx;
	int fYec82_idx_save;
	double fRec165_perm[4];
	double fRec164_perm[4];
	double fYec83[128];
	int fYec83_idx;
	int fYec83_idx_save;
	double fRec167_perm[4];
	double fRec166_perm[4];
	double fYec84[128];
	int fYec84_idx;
	int fYec84_idx_save;
	double fRec169_perm[4];
	double fRec168_perm[4];
	double fYec85[128];
	int fYec85_idx;
	int fYec85_idx_save;
	double fRec171_perm[4];
	double fRec170_perm[4];
	double fYec86[512];
	int fYec86_idx;
	int fYec86_idx_save;
	double fRec173_perm[4];
	double fRec172_perm[4];
	double fYec87[512];
	int fYec87_idx;
	int fYec87_idx_save;
	double fRec175_perm[4];
	double fRec174_perm[4];
	double fYec88[1024];
	int fYec88_idx;
	int fYec88_idx_save;
	double fRec177_perm[4];
	double fRec176_perm[4];
	double fYec89[1024];
	int fYec89_idx;
	int fYec89_idx_save;
	double fRec179_perm[4];
	double fRec178_perm[4];
	double fYec90[128];
	int fYec90_idx;
	int fYec90_idx_save;
	double fRec181_perm[4];
	double fRec180_perm[4];
	double fYec91[128];
	int fYec91_idx;
	int fYec91_idx_save;
	double fRec183_perm[4];
	double fRec182_perm[4];
	double fYec92[128];
	int fYec92_idx;
	int fYec92_idx_save;
	double fRec185_perm[4];
	double fRec184_perm[4];
	double fYec93[128];
	int fYec93_idx;
	int fYec93_idx_save;
	double fRec187_perm[4];
	double fRec186_perm[4];
	double fYec94[128];
	int fYec94_idx;
	int fYec94_idx_save;
	double fRec189_perm[4];
	double fRec188_perm[4];
	double fYec95[128];
	int fYec95_idx;
	int fYec95_idx_save;
	double fRec191_perm[4];
	double fRec190_perm[4];
	double fYec96[512];
	int fYec96_idx;
	int fYec96_idx_save;
	double fRec193_perm[4];
	double fRec192_perm[4];
	double fYec97[512];
	int fYec97_idx;
	int fYec97_idx_save;
	double fRec195_perm[4];
	double fRec194_perm[4];
	double fYec98[1024];
	int fYec98_idx;
	int fYec98_idx_save;
	double fRec197_perm[4];
	double fRec196_perm[4];
	double fYec99[1024];
	int fYec99_idx;
	int fYec99_idx_save;
	double fRec199_perm[4];
	double fRec198_perm[4];
	double fYec100[128];
	int fYec100_idx;
	int fYec100_idx_save;
	double fRec201_perm[4];
	double fRec200_perm[4];
	double fYec101[128];
	int fYec101_idx;
	int fYec101_idx_save;
	double fRec203_perm[4];
	double fRec202_perm[4];
	double fYec102[128];
	int fYec102_idx;
	int fYec102_idx_save;
	double fRec205_perm[4];
	double fRec204_perm[4];
	double fYec103[128];
	int fYec103_idx;
	int fYec103_idx_save;
	double fRec207_perm[4];
	double fRec206_perm[4];
	double fYec104[128];
	int fYec104_idx;
	int fYec104_idx_save;
	double fRec209_perm[4];
	double fRec208_perm[4];
	double fYec105[1024];
	int fYec105_idx;
	int fYec105_idx_save;
	double fRec211_perm[4];
	double fRec210_perm[4];
	double fYec106[1024];
	int fYec106_idx;
	int fYec106_idx_save;
	double fRec213_perm[4];
	double fRec212_perm[4];
	double fYec107[512];
	int fYec107_idx;
	int fYec107_idx_save;
	double fRec215_perm[4];
	double fRec214_perm[4];
	double fYec108[512];
	int fYec108_idx;
	int fYec108_idx_save;
	double fRec217_perm[4];
	double fRec216_perm[4];
	double fYec109[128];
	int fYec109_idx;
	int fYec109_idx_save;
	double fRec219_perm[4];
	double fRec218_perm[4];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32");
		m->declare("filename", "bells.dsp");
		m->declare("name", "bells");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 0.5 * fConst0;
		fConst2 = 0.0003984129014894459 * fConst0;
		fConst3 = 100.53097 / fConst0;
		fConst4 = 2.0 * (fConst3 - 1.0);
		fConst5 = 15770.53724041224 / fConst0;
		fConst6 = mydsp_faustpower2_f(1.0 - fConst3);
		fConst7 = 0.5 * (1.0 - fConst6);
		fConst8 = 0.00010341847835949931 * fConst0;
		fConst9 = 60754.95984536373 / fConst0;
		fConst10 = 0.0001315173052074703 * fConst0;
		fConst11 = 47774.591260733265 / fConst0;
		fConst12 = 0.00017745447685774287 * fConst0;
		fConst13 = 35407.309025158844 / fConst0;
		fConst14 = 0.00017709981763677576 * fConst0;
		fConst15 = 35478.215527508604 / fConst0;
		fConst16 = 0.0002520911795242428 * fConst0;
		fConst17 = 24924.25761130514 / fConst0;
		fConst18 = 0.00025257576767878827 * fConst0;
		fConst19 = 24876.438297084 / fConst0;
		fConst20 = 0.0007592720726222721 * fConst0;
		fConst21 = 8275.275394102113 / fConst0;
		fConst22 = 0.0007628705880371271 * fConst0;
		fConst23 = 8236.24032506836 / fConst0;
		fConst24 = 0.0022639167877643303 * fConst0;
		fConst25 = 2775.3606201245543 / fConst0;
		fConst26 = 0.002281606486610892 * fConst0;
		fConst27 = 2753.842758105527 / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = static_cast<FAUSTFLOAT>(69.0);
		fEntry1 = static_cast<FAUSTFLOAT>(0.989);
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
		fEntry2 = static_cast<FAUSTFLOAT>(68.0);
		fButton1 = static_cast<FAUSTFLOAT>(0.0);
		fEntry3 = static_cast<FAUSTFLOAT>(67.0);
		fButton2 = static_cast<FAUSTFLOAT>(0.0);
		fEntry4 = static_cast<FAUSTFLOAT>(66.0);
		fButton3 = static_cast<FAUSTFLOAT>(0.0);
		fEntry5 = static_cast<FAUSTFLOAT>(65.0);
		fButton4 = static_cast<FAUSTFLOAT>(0.0);
		fEntry6 = static_cast<FAUSTFLOAT>(64.0);
		fButton5 = static_cast<FAUSTFLOAT>(0.0);
		fEntry7 = static_cast<FAUSTFLOAT>(63.0);
		fButton6 = static_cast<FAUSTFLOAT>(0.0);
		fEntry8 = static_cast<FAUSTFLOAT>(62.0);
		fButton7 = static_cast<FAUSTFLOAT>(0.0);
		fEntry9 = static_cast<FAUSTFLOAT>(6e+01);
		fButton8 = static_cast<FAUSTFLOAT>(0.0);
		fEntry10 = static_cast<FAUSTFLOAT>(61.0);
		fButton9 = static_cast<FAUSTFLOAT>(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = l0 + 1) {
			fVec0_perm[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 256; l1 = l1 + 1) {
			fYec0[l1] = 0.0;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l2 = 0; l2 < 4; l2 = l2 + 1) {
			fRec1_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = l3 + 1) {
			fRec0_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = l4 + 1) {
			fVec1_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 256; l5 = l5 + 1) {
			fYec1[l5] = 0.0;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l6 = 0; l6 < 4; l6 = l6 + 1) {
			fRec3_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = l7 + 1) {
			fRec2_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = l8 + 1) {
			fVec2_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 256; l9 = l9 + 1) {
			fYec2[l9] = 0.0;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l10 = 0; l10 < 4; l10 = l10 + 1) {
			fRec5_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = l11 + 1) {
			fRec4_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = l12 + 1) {
			fVec3_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 256; l13 = l13 + 1) {
			fYec3[l13] = 0.0;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l14 = 0; l14 < 4; l14 = l14 + 1) {
			fRec7_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = l15 + 1) {
			fRec6_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = l16 + 1) {
			fVec4_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 256; l17 = l17 + 1) {
			fYec4[l17] = 0.0;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l18 = 0; l18 < 4; l18 = l18 + 1) {
			fRec9_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = l19 + 1) {
			fRec8_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = l20 + 1) {
			fVec5_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 256; l21 = l21 + 1) {
			fYec5[l21] = 0.0;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l22 = 0; l22 < 4; l22 = l22 + 1) {
			fRec11_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = l23 + 1) {
			fRec10_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = l24 + 1) {
			fVec6_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 256; l25 = l25 + 1) {
			fYec6[l25] = 0.0;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l26 = 0; l26 < 4; l26 = l26 + 1) {
			fRec13_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = l27 + 1) {
			fRec12_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = l28 + 1) {
			fVec7_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 256; l29 = l29 + 1) {
			fYec7[l29] = 0.0;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l30 = 0; l30 < 4; l30 = l30 + 1) {
			fRec15_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = l31 + 1) {
			fRec14_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = l32 + 1) {
			fVec8_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 256; l33 = l33 + 1) {
			fYec8[l33] = 0.0;
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l34 = 0; l34 < 4; l34 = l34 + 1) {
			fRec17_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = l35 + 1) {
			fRec16_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = l36 + 1) {
			fVec9_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 256; l37 = l37 + 1) {
			fYec9[l37] = 0.0;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l38 = 0; l38 < 4; l38 = l38 + 1) {
			fRec19_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = l39 + 1) {
			fRec18_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 128; l40 = l40 + 1) {
			fYec10[l40] = 0.0;
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l41 = 0; l41 < 4; l41 = l41 + 1) {
			fRec21_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = l42 + 1) {
			fRec20_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 128; l43 = l43 + 1) {
			fYec11[l43] = 0.0;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l44 = 0; l44 < 4; l44 = l44 + 1) {
			fRec23_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = l45 + 1) {
			fRec22_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 128; l46 = l46 + 1) {
			fYec12[l46] = 0.0;
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l47 = 0; l47 < 4; l47 = l47 + 1) {
			fRec25_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = l48 + 1) {
			fRec24_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 128; l49 = l49 + 1) {
			fYec13[l49] = 0.0;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l50 = 0; l50 < 4; l50 = l50 + 1) {
			fRec27_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = l51 + 1) {
			fRec26_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 128; l52 = l52 + 1) {
			fYec14[l52] = 0.0;
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l53 = 0; l53 < 4; l53 = l53 + 1) {
			fRec29_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = l54 + 1) {
			fRec28_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 128; l55 = l55 + 1) {
			fYec15[l55] = 0.0;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l56 = 0; l56 < 4; l56 = l56 + 1) {
			fRec31_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = l57 + 1) {
			fRec30_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 512; l58 = l58 + 1) {
			fYec16[l58] = 0.0;
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l59 = 0; l59 < 4; l59 = l59 + 1) {
			fRec33_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = l60 + 1) {
			fRec32_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 512; l61 = l61 + 1) {
			fYec17[l61] = 0.0;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l62 = 0; l62 < 4; l62 = l62 + 1) {
			fRec35_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = l63 + 1) {
			fRec34_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 1024; l64 = l64 + 1) {
			fYec18[l64] = 0.0;
		}
		fYec18_idx = 0;
		fYec18_idx_save = 0;
		for (int l65 = 0; l65 < 4; l65 = l65 + 1) {
			fRec37_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = l66 + 1) {
			fRec36_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 1024; l67 = l67 + 1) {
			fYec19[l67] = 0.0;
		}
		fYec19_idx = 0;
		fYec19_idx_save = 0;
		for (int l68 = 0; l68 < 4; l68 = l68 + 1) {
			fRec39_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = l69 + 1) {
			fRec38_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 128; l70 = l70 + 1) {
			fYec20[l70] = 0.0;
		}
		fYec20_idx = 0;
		fYec20_idx_save = 0;
		for (int l71 = 0; l71 < 4; l71 = l71 + 1) {
			fRec41_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = l72 + 1) {
			fRec40_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 128; l73 = l73 + 1) {
			fYec21[l73] = 0.0;
		}
		fYec21_idx = 0;
		fYec21_idx_save = 0;
		for (int l74 = 0; l74 < 4; l74 = l74 + 1) {
			fRec43_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = l75 + 1) {
			fRec42_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 128; l76 = l76 + 1) {
			fYec22[l76] = 0.0;
		}
		fYec22_idx = 0;
		fYec22_idx_save = 0;
		for (int l77 = 0; l77 < 4; l77 = l77 + 1) {
			fRec45_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = l78 + 1) {
			fRec44_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 128; l79 = l79 + 1) {
			fYec23[l79] = 0.0;
		}
		fYec23_idx = 0;
		fYec23_idx_save = 0;
		for (int l80 = 0; l80 < 4; l80 = l80 + 1) {
			fRec47_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = l81 + 1) {
			fRec46_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 128; l82 = l82 + 1) {
			fYec24[l82] = 0.0;
		}
		fYec24_idx = 0;
		fYec24_idx_save = 0;
		for (int l83 = 0; l83 < 4; l83 = l83 + 1) {
			fRec49_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = l84 + 1) {
			fRec48_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 128; l85 = l85 + 1) {
			fYec25[l85] = 0.0;
		}
		fYec25_idx = 0;
		fYec25_idx_save = 0;
		for (int l86 = 0; l86 < 4; l86 = l86 + 1) {
			fRec51_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = l87 + 1) {
			fRec50_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 512; l88 = l88 + 1) {
			fYec26[l88] = 0.0;
		}
		fYec26_idx = 0;
		fYec26_idx_save = 0;
		for (int l89 = 0; l89 < 4; l89 = l89 + 1) {
			fRec53_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = l90 + 1) {
			fRec52_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 512; l91 = l91 + 1) {
			fYec27[l91] = 0.0;
		}
		fYec27_idx = 0;
		fYec27_idx_save = 0;
		for (int l92 = 0; l92 < 4; l92 = l92 + 1) {
			fRec55_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = l93 + 1) {
			fRec54_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 1024; l94 = l94 + 1) {
			fYec28[l94] = 0.0;
		}
		fYec28_idx = 0;
		fYec28_idx_save = 0;
		for (int l95 = 0; l95 < 4; l95 = l95 + 1) {
			fRec57_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = l96 + 1) {
			fRec56_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 1024; l97 = l97 + 1) {
			fYec29[l97] = 0.0;
		}
		fYec29_idx = 0;
		fYec29_idx_save = 0;
		for (int l98 = 0; l98 < 4; l98 = l98 + 1) {
			fRec59_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = l99 + 1) {
			fRec58_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 128; l100 = l100 + 1) {
			fYec30[l100] = 0.0;
		}
		fYec30_idx = 0;
		fYec30_idx_save = 0;
		for (int l101 = 0; l101 < 4; l101 = l101 + 1) {
			fRec61_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = l102 + 1) {
			fRec60_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 128; l103 = l103 + 1) {
			fYec31[l103] = 0.0;
		}
		fYec31_idx = 0;
		fYec31_idx_save = 0;
		for (int l104 = 0; l104 < 4; l104 = l104 + 1) {
			fRec63_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = l105 + 1) {
			fRec62_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 128; l106 = l106 + 1) {
			fYec32[l106] = 0.0;
		}
		fYec32_idx = 0;
		fYec32_idx_save = 0;
		for (int l107 = 0; l107 < 4; l107 = l107 + 1) {
			fRec65_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = l108 + 1) {
			fRec64_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 128; l109 = l109 + 1) {
			fYec33[l109] = 0.0;
		}
		fYec33_idx = 0;
		fYec33_idx_save = 0;
		for (int l110 = 0; l110 < 4; l110 = l110 + 1) {
			fRec67_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = l111 + 1) {
			fRec66_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 128; l112 = l112 + 1) {
			fYec34[l112] = 0.0;
		}
		fYec34_idx = 0;
		fYec34_idx_save = 0;
		for (int l113 = 0; l113 < 4; l113 = l113 + 1) {
			fRec69_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = l114 + 1) {
			fRec68_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 128; l115 = l115 + 1) {
			fYec35[l115] = 0.0;
		}
		fYec35_idx = 0;
		fYec35_idx_save = 0;
		for (int l116 = 0; l116 < 4; l116 = l116 + 1) {
			fRec71_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = l117 + 1) {
			fRec70_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 512; l118 = l118 + 1) {
			fYec36[l118] = 0.0;
		}
		fYec36_idx = 0;
		fYec36_idx_save = 0;
		for (int l119 = 0; l119 < 4; l119 = l119 + 1) {
			fRec73_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = l120 + 1) {
			fRec72_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 512; l121 = l121 + 1) {
			fYec37[l121] = 0.0;
		}
		fYec37_idx = 0;
		fYec37_idx_save = 0;
		for (int l122 = 0; l122 < 4; l122 = l122 + 1) {
			fRec75_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = l123 + 1) {
			fRec74_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 1024; l124 = l124 + 1) {
			fYec38[l124] = 0.0;
		}
		fYec38_idx = 0;
		fYec38_idx_save = 0;
		for (int l125 = 0; l125 < 4; l125 = l125 + 1) {
			fRec77_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = l126 + 1) {
			fRec76_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 1024; l127 = l127 + 1) {
			fYec39[l127] = 0.0;
		}
		fYec39_idx = 0;
		fYec39_idx_save = 0;
		for (int l128 = 0; l128 < 4; l128 = l128 + 1) {
			fRec79_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = l129 + 1) {
			fRec78_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 128; l130 = l130 + 1) {
			fYec40[l130] = 0.0;
		}
		fYec40_idx = 0;
		fYec40_idx_save = 0;
		for (int l131 = 0; l131 < 4; l131 = l131 + 1) {
			fRec81_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = l132 + 1) {
			fRec80_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 128; l133 = l133 + 1) {
			fYec41[l133] = 0.0;
		}
		fYec41_idx = 0;
		fYec41_idx_save = 0;
		for (int l134 = 0; l134 < 4; l134 = l134 + 1) {
			fRec83_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = l135 + 1) {
			fRec82_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 128; l136 = l136 + 1) {
			fYec42[l136] = 0.0;
		}
		fYec42_idx = 0;
		fYec42_idx_save = 0;
		for (int l137 = 0; l137 < 4; l137 = l137 + 1) {
			fRec85_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = l138 + 1) {
			fRec84_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 128; l139 = l139 + 1) {
			fYec43[l139] = 0.0;
		}
		fYec43_idx = 0;
		fYec43_idx_save = 0;
		for (int l140 = 0; l140 < 4; l140 = l140 + 1) {
			fRec87_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = l141 + 1) {
			fRec86_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 128; l142 = l142 + 1) {
			fYec44[l142] = 0.0;
		}
		fYec44_idx = 0;
		fYec44_idx_save = 0;
		for (int l143 = 0; l143 < 4; l143 = l143 + 1) {
			fRec89_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = l144 + 1) {
			fRec88_perm[l144] = 0.0;
		}
		for (int l145 = 0; l145 < 128; l145 = l145 + 1) {
			fYec45[l145] = 0.0;
		}
		fYec45_idx = 0;
		fYec45_idx_save = 0;
		for (int l146 = 0; l146 < 4; l146 = l146 + 1) {
			fRec91_perm[l146] = 0.0;
		}
		for (int l147 = 0; l147 < 4; l147 = l147 + 1) {
			fRec90_perm[l147] = 0.0;
		}
		for (int l148 = 0; l148 < 512; l148 = l148 + 1) {
			fYec46[l148] = 0.0;
		}
		fYec46_idx = 0;
		fYec46_idx_save = 0;
		for (int l149 = 0; l149 < 4; l149 = l149 + 1) {
			fRec93_perm[l149] = 0.0;
		}
		for (int l150 = 0; l150 < 4; l150 = l150 + 1) {
			fRec92_perm[l150] = 0.0;
		}
		for (int l151 = 0; l151 < 512; l151 = l151 + 1) {
			fYec47[l151] = 0.0;
		}
		fYec47_idx = 0;
		fYec47_idx_save = 0;
		for (int l152 = 0; l152 < 4; l152 = l152 + 1) {
			fRec95_perm[l152] = 0.0;
		}
		for (int l153 = 0; l153 < 4; l153 = l153 + 1) {
			fRec94_perm[l153] = 0.0;
		}
		for (int l154 = 0; l154 < 1024; l154 = l154 + 1) {
			fYec48[l154] = 0.0;
		}
		fYec48_idx = 0;
		fYec48_idx_save = 0;
		for (int l155 = 0; l155 < 4; l155 = l155 + 1) {
			fRec97_perm[l155] = 0.0;
		}
		for (int l156 = 0; l156 < 4; l156 = l156 + 1) {
			fRec96_perm[l156] = 0.0;
		}
		for (int l157 = 0; l157 < 1024; l157 = l157 + 1) {
			fYec49[l157] = 0.0;
		}
		fYec49_idx = 0;
		fYec49_idx_save = 0;
		for (int l158 = 0; l158 < 4; l158 = l158 + 1) {
			fRec99_perm[l158] = 0.0;
		}
		for (int l159 = 0; l159 < 4; l159 = l159 + 1) {
			fRec98_perm[l159] = 0.0;
		}
		for (int l160 = 0; l160 < 128; l160 = l160 + 1) {
			fYec50[l160] = 0.0;
		}
		fYec50_idx = 0;
		fYec50_idx_save = 0;
		for (int l161 = 0; l161 < 4; l161 = l161 + 1) {
			fRec101_perm[l161] = 0.0;
		}
		for (int l162 = 0; l162 < 4; l162 = l162 + 1) {
			fRec100_perm[l162] = 0.0;
		}
		for (int l163 = 0; l163 < 128; l163 = l163 + 1) {
			fYec51[l163] = 0.0;
		}
		fYec51_idx = 0;
		fYec51_idx_save = 0;
		for (int l164 = 0; l164 < 4; l164 = l164 + 1) {
			fRec103_perm[l164] = 0.0;
		}
		for (int l165 = 0; l165 < 4; l165 = l165 + 1) {
			fRec102_perm[l165] = 0.0;
		}
		for (int l166 = 0; l166 < 128; l166 = l166 + 1) {
			fYec52[l166] = 0.0;
		}
		fYec52_idx = 0;
		fYec52_idx_save = 0;
		for (int l167 = 0; l167 < 4; l167 = l167 + 1) {
			fRec105_perm[l167] = 0.0;
		}
		for (int l168 = 0; l168 < 4; l168 = l168 + 1) {
			fRec104_perm[l168] = 0.0;
		}
		for (int l169 = 0; l169 < 128; l169 = l169 + 1) {
			fYec53[l169] = 0.0;
		}
		fYec53_idx = 0;
		fYec53_idx_save = 0;
		for (int l170 = 0; l170 < 4; l170 = l170 + 1) {
			fRec107_perm[l170] = 0.0;
		}
		for (int l171 = 0; l171 < 4; l171 = l171 + 1) {
			fRec106_perm[l171] = 0.0;
		}
		for (int l172 = 0; l172 < 128; l172 = l172 + 1) {
			fYec54[l172] = 0.0;
		}
		fYec54_idx = 0;
		fYec54_idx_save = 0;
		for (int l173 = 0; l173 < 4; l173 = l173 + 1) {
			fRec109_perm[l173] = 0.0;
		}
		for (int l174 = 0; l174 < 4; l174 = l174 + 1) {
			fRec108_perm[l174] = 0.0;
		}
		for (int l175 = 0; l175 < 128; l175 = l175 + 1) {
			fYec55[l175] = 0.0;
		}
		fYec55_idx = 0;
		fYec55_idx_save = 0;
		for (int l176 = 0; l176 < 4; l176 = l176 + 1) {
			fRec111_perm[l176] = 0.0;
		}
		for (int l177 = 0; l177 < 4; l177 = l177 + 1) {
			fRec110_perm[l177] = 0.0;
		}
		for (int l178 = 0; l178 < 512; l178 = l178 + 1) {
			fYec56[l178] = 0.0;
		}
		fYec56_idx = 0;
		fYec56_idx_save = 0;
		for (int l179 = 0; l179 < 4; l179 = l179 + 1) {
			fRec113_perm[l179] = 0.0;
		}
		for (int l180 = 0; l180 < 4; l180 = l180 + 1) {
			fRec112_perm[l180] = 0.0;
		}
		for (int l181 = 0; l181 < 512; l181 = l181 + 1) {
			fYec57[l181] = 0.0;
		}
		fYec57_idx = 0;
		fYec57_idx_save = 0;
		for (int l182 = 0; l182 < 4; l182 = l182 + 1) {
			fRec115_perm[l182] = 0.0;
		}
		for (int l183 = 0; l183 < 4; l183 = l183 + 1) {
			fRec114_perm[l183] = 0.0;
		}
		for (int l184 = 0; l184 < 1024; l184 = l184 + 1) {
			fYec58[l184] = 0.0;
		}
		fYec58_idx = 0;
		fYec58_idx_save = 0;
		for (int l185 = 0; l185 < 4; l185 = l185 + 1) {
			fRec117_perm[l185] = 0.0;
		}
		for (int l186 = 0; l186 < 4; l186 = l186 + 1) {
			fRec116_perm[l186] = 0.0;
		}
		for (int l187 = 0; l187 < 1024; l187 = l187 + 1) {
			fYec59[l187] = 0.0;
		}
		fYec59_idx = 0;
		fYec59_idx_save = 0;
		for (int l188 = 0; l188 < 4; l188 = l188 + 1) {
			fRec119_perm[l188] = 0.0;
		}
		for (int l189 = 0; l189 < 4; l189 = l189 + 1) {
			fRec118_perm[l189] = 0.0;
		}
		for (int l190 = 0; l190 < 128; l190 = l190 + 1) {
			fYec60[l190] = 0.0;
		}
		fYec60_idx = 0;
		fYec60_idx_save = 0;
		for (int l191 = 0; l191 < 4; l191 = l191 + 1) {
			fRec121_perm[l191] = 0.0;
		}
		for (int l192 = 0; l192 < 4; l192 = l192 + 1) {
			fRec120_perm[l192] = 0.0;
		}
		for (int l193 = 0; l193 < 128; l193 = l193 + 1) {
			fYec61[l193] = 0.0;
		}
		fYec61_idx = 0;
		fYec61_idx_save = 0;
		for (int l194 = 0; l194 < 4; l194 = l194 + 1) {
			fRec123_perm[l194] = 0.0;
		}
		for (int l195 = 0; l195 < 4; l195 = l195 + 1) {
			fRec122_perm[l195] = 0.0;
		}
		for (int l196 = 0; l196 < 128; l196 = l196 + 1) {
			fYec62[l196] = 0.0;
		}
		fYec62_idx = 0;
		fYec62_idx_save = 0;
		for (int l197 = 0; l197 < 4; l197 = l197 + 1) {
			fRec125_perm[l197] = 0.0;
		}
		for (int l198 = 0; l198 < 4; l198 = l198 + 1) {
			fRec124_perm[l198] = 0.0;
		}
		for (int l199 = 0; l199 < 128; l199 = l199 + 1) {
			fYec63[l199] = 0.0;
		}
		fYec63_idx = 0;
		fYec63_idx_save = 0;
		for (int l200 = 0; l200 < 4; l200 = l200 + 1) {
			fRec127_perm[l200] = 0.0;
		}
		for (int l201 = 0; l201 < 4; l201 = l201 + 1) {
			fRec126_perm[l201] = 0.0;
		}
		for (int l202 = 0; l202 < 128; l202 = l202 + 1) {
			fYec64[l202] = 0.0;
		}
		fYec64_idx = 0;
		fYec64_idx_save = 0;
		for (int l203 = 0; l203 < 4; l203 = l203 + 1) {
			fRec129_perm[l203] = 0.0;
		}
		for (int l204 = 0; l204 < 4; l204 = l204 + 1) {
			fRec128_perm[l204] = 0.0;
		}
		for (int l205 = 0; l205 < 128; l205 = l205 + 1) {
			fYec65[l205] = 0.0;
		}
		fYec65_idx = 0;
		fYec65_idx_save = 0;
		for (int l206 = 0; l206 < 4; l206 = l206 + 1) {
			fRec131_perm[l206] = 0.0;
		}
		for (int l207 = 0; l207 < 4; l207 = l207 + 1) {
			fRec130_perm[l207] = 0.0;
		}
		for (int l208 = 0; l208 < 512; l208 = l208 + 1) {
			fYec66[l208] = 0.0;
		}
		fYec66_idx = 0;
		fYec66_idx_save = 0;
		for (int l209 = 0; l209 < 4; l209 = l209 + 1) {
			fRec133_perm[l209] = 0.0;
		}
		for (int l210 = 0; l210 < 4; l210 = l210 + 1) {
			fRec132_perm[l210] = 0.0;
		}
		for (int l211 = 0; l211 < 512; l211 = l211 + 1) {
			fYec67[l211] = 0.0;
		}
		fYec67_idx = 0;
		fYec67_idx_save = 0;
		for (int l212 = 0; l212 < 4; l212 = l212 + 1) {
			fRec135_perm[l212] = 0.0;
		}
		for (int l213 = 0; l213 < 4; l213 = l213 + 1) {
			fRec134_perm[l213] = 0.0;
		}
		for (int l214 = 0; l214 < 1024; l214 = l214 + 1) {
			fYec68[l214] = 0.0;
		}
		fYec68_idx = 0;
		fYec68_idx_save = 0;
		for (int l215 = 0; l215 < 4; l215 = l215 + 1) {
			fRec137_perm[l215] = 0.0;
		}
		for (int l216 = 0; l216 < 4; l216 = l216 + 1) {
			fRec136_perm[l216] = 0.0;
		}
		for (int l217 = 0; l217 < 1024; l217 = l217 + 1) {
			fYec69[l217] = 0.0;
		}
		fYec69_idx = 0;
		fYec69_idx_save = 0;
		for (int l218 = 0; l218 < 4; l218 = l218 + 1) {
			fRec139_perm[l218] = 0.0;
		}
		for (int l219 = 0; l219 < 4; l219 = l219 + 1) {
			fRec138_perm[l219] = 0.0;
		}
		for (int l220 = 0; l220 < 128; l220 = l220 + 1) {
			fYec70[l220] = 0.0;
		}
		fYec70_idx = 0;
		fYec70_idx_save = 0;
		for (int l221 = 0; l221 < 4; l221 = l221 + 1) {
			fRec141_perm[l221] = 0.0;
		}
		for (int l222 = 0; l222 < 4; l222 = l222 + 1) {
			fRec140_perm[l222] = 0.0;
		}
		for (int l223 = 0; l223 < 128; l223 = l223 + 1) {
			fYec71[l223] = 0.0;
		}
		fYec71_idx = 0;
		fYec71_idx_save = 0;
		for (int l224 = 0; l224 < 4; l224 = l224 + 1) {
			fRec143_perm[l224] = 0.0;
		}
		for (int l225 = 0; l225 < 4; l225 = l225 + 1) {
			fRec142_perm[l225] = 0.0;
		}
		for (int l226 = 0; l226 < 128; l226 = l226 + 1) {
			fYec72[l226] = 0.0;
		}
		fYec72_idx = 0;
		fYec72_idx_save = 0;
		for (int l227 = 0; l227 < 4; l227 = l227 + 1) {
			fRec145_perm[l227] = 0.0;
		}
		for (int l228 = 0; l228 < 4; l228 = l228 + 1) {
			fRec144_perm[l228] = 0.0;
		}
		for (int l229 = 0; l229 < 128; l229 = l229 + 1) {
			fYec73[l229] = 0.0;
		}
		fYec73_idx = 0;
		fYec73_idx_save = 0;
		for (int l230 = 0; l230 < 4; l230 = l230 + 1) {
			fRec147_perm[l230] = 0.0;
		}
		for (int l231 = 0; l231 < 4; l231 = l231 + 1) {
			fRec146_perm[l231] = 0.0;
		}
		for (int l232 = 0; l232 < 128; l232 = l232 + 1) {
			fYec74[l232] = 0.0;
		}
		fYec74_idx = 0;
		fYec74_idx_save = 0;
		for (int l233 = 0; l233 < 4; l233 = l233 + 1) {
			fRec149_perm[l233] = 0.0;
		}
		for (int l234 = 0; l234 < 4; l234 = l234 + 1) {
			fRec148_perm[l234] = 0.0;
		}
		for (int l235 = 0; l235 < 128; l235 = l235 + 1) {
			fYec75[l235] = 0.0;
		}
		fYec75_idx = 0;
		fYec75_idx_save = 0;
		for (int l236 = 0; l236 < 4; l236 = l236 + 1) {
			fRec151_perm[l236] = 0.0;
		}
		for (int l237 = 0; l237 < 4; l237 = l237 + 1) {
			fRec150_perm[l237] = 0.0;
		}
		for (int l238 = 0; l238 < 512; l238 = l238 + 1) {
			fYec76[l238] = 0.0;
		}
		fYec76_idx = 0;
		fYec76_idx_save = 0;
		for (int l239 = 0; l239 < 4; l239 = l239 + 1) {
			fRec153_perm[l239] = 0.0;
		}
		for (int l240 = 0; l240 < 4; l240 = l240 + 1) {
			fRec152_perm[l240] = 0.0;
		}
		for (int l241 = 0; l241 < 512; l241 = l241 + 1) {
			fYec77[l241] = 0.0;
		}
		fYec77_idx = 0;
		fYec77_idx_save = 0;
		for (int l242 = 0; l242 < 4; l242 = l242 + 1) {
			fRec155_perm[l242] = 0.0;
		}
		for (int l243 = 0; l243 < 4; l243 = l243 + 1) {
			fRec154_perm[l243] = 0.0;
		}
		for (int l244 = 0; l244 < 1024; l244 = l244 + 1) {
			fYec78[l244] = 0.0;
		}
		fYec78_idx = 0;
		fYec78_idx_save = 0;
		for (int l245 = 0; l245 < 4; l245 = l245 + 1) {
			fRec157_perm[l245] = 0.0;
		}
		for (int l246 = 0; l246 < 4; l246 = l246 + 1) {
			fRec156_perm[l246] = 0.0;
		}
		for (int l247 = 0; l247 < 1024; l247 = l247 + 1) {
			fYec79[l247] = 0.0;
		}
		fYec79_idx = 0;
		fYec79_idx_save = 0;
		for (int l248 = 0; l248 < 4; l248 = l248 + 1) {
			fRec159_perm[l248] = 0.0;
		}
		for (int l249 = 0; l249 < 4; l249 = l249 + 1) {
			fRec158_perm[l249] = 0.0;
		}
		for (int l250 = 0; l250 < 128; l250 = l250 + 1) {
			fYec80[l250] = 0.0;
		}
		fYec80_idx = 0;
		fYec80_idx_save = 0;
		for (int l251 = 0; l251 < 4; l251 = l251 + 1) {
			fRec161_perm[l251] = 0.0;
		}
		for (int l252 = 0; l252 < 4; l252 = l252 + 1) {
			fRec160_perm[l252] = 0.0;
		}
		for (int l253 = 0; l253 < 128; l253 = l253 + 1) {
			fYec81[l253] = 0.0;
		}
		fYec81_idx = 0;
		fYec81_idx_save = 0;
		for (int l254 = 0; l254 < 4; l254 = l254 + 1) {
			fRec163_perm[l254] = 0.0;
		}
		for (int l255 = 0; l255 < 4; l255 = l255 + 1) {
			fRec162_perm[l255] = 0.0;
		}
		for (int l256 = 0; l256 < 128; l256 = l256 + 1) {
			fYec82[l256] = 0.0;
		}
		fYec82_idx = 0;
		fYec82_idx_save = 0;
		for (int l257 = 0; l257 < 4; l257 = l257 + 1) {
			fRec165_perm[l257] = 0.0;
		}
		for (int l258 = 0; l258 < 4; l258 = l258 + 1) {
			fRec164_perm[l258] = 0.0;
		}
		for (int l259 = 0; l259 < 128; l259 = l259 + 1) {
			fYec83[l259] = 0.0;
		}
		fYec83_idx = 0;
		fYec83_idx_save = 0;
		for (int l260 = 0; l260 < 4; l260 = l260 + 1) {
			fRec167_perm[l260] = 0.0;
		}
		for (int l261 = 0; l261 < 4; l261 = l261 + 1) {
			fRec166_perm[l261] = 0.0;
		}
		for (int l262 = 0; l262 < 128; l262 = l262 + 1) {
			fYec84[l262] = 0.0;
		}
		fYec84_idx = 0;
		fYec84_idx_save = 0;
		for (int l263 = 0; l263 < 4; l263 = l263 + 1) {
			fRec169_perm[l263] = 0.0;
		}
		for (int l264 = 0; l264 < 4; l264 = l264 + 1) {
			fRec168_perm[l264] = 0.0;
		}
		for (int l265 = 0; l265 < 128; l265 = l265 + 1) {
			fYec85[l265] = 0.0;
		}
		fYec85_idx = 0;
		fYec85_idx_save = 0;
		for (int l266 = 0; l266 < 4; l266 = l266 + 1) {
			fRec171_perm[l266] = 0.0;
		}
		for (int l267 = 0; l267 < 4; l267 = l267 + 1) {
			fRec170_perm[l267] = 0.0;
		}
		for (int l268 = 0; l268 < 512; l268 = l268 + 1) {
			fYec86[l268] = 0.0;
		}
		fYec86_idx = 0;
		fYec86_idx_save = 0;
		for (int l269 = 0; l269 < 4; l269 = l269 + 1) {
			fRec173_perm[l269] = 0.0;
		}
		for (int l270 = 0; l270 < 4; l270 = l270 + 1) {
			fRec172_perm[l270] = 0.0;
		}
		for (int l271 = 0; l271 < 512; l271 = l271 + 1) {
			fYec87[l271] = 0.0;
		}
		fYec87_idx = 0;
		fYec87_idx_save = 0;
		for (int l272 = 0; l272 < 4; l272 = l272 + 1) {
			fRec175_perm[l272] = 0.0;
		}
		for (int l273 = 0; l273 < 4; l273 = l273 + 1) {
			fRec174_perm[l273] = 0.0;
		}
		for (int l274 = 0; l274 < 1024; l274 = l274 + 1) {
			fYec88[l274] = 0.0;
		}
		fYec88_idx = 0;
		fYec88_idx_save = 0;
		for (int l275 = 0; l275 < 4; l275 = l275 + 1) {
			fRec177_perm[l275] = 0.0;
		}
		for (int l276 = 0; l276 < 4; l276 = l276 + 1) {
			fRec176_perm[l276] = 0.0;
		}
		for (int l277 = 0; l277 < 1024; l277 = l277 + 1) {
			fYec89[l277] = 0.0;
		}
		fYec89_idx = 0;
		fYec89_idx_save = 0;
		for (int l278 = 0; l278 < 4; l278 = l278 + 1) {
			fRec179_perm[l278] = 0.0;
		}
		for (int l279 = 0; l279 < 4; l279 = l279 + 1) {
			fRec178_perm[l279] = 0.0;
		}
		for (int l280 = 0; l280 < 128; l280 = l280 + 1) {
			fYec90[l280] = 0.0;
		}
		fYec90_idx = 0;
		fYec90_idx_save = 0;
		for (int l281 = 0; l281 < 4; l281 = l281 + 1) {
			fRec181_perm[l281] = 0.0;
		}
		for (int l282 = 0; l282 < 4; l282 = l282 + 1) {
			fRec180_perm[l282] = 0.0;
		}
		for (int l283 = 0; l283 < 128; l283 = l283 + 1) {
			fYec91[l283] = 0.0;
		}
		fYec91_idx = 0;
		fYec91_idx_save = 0;
		for (int l284 = 0; l284 < 4; l284 = l284 + 1) {
			fRec183_perm[l284] = 0.0;
		}
		for (int l285 = 0; l285 < 4; l285 = l285 + 1) {
			fRec182_perm[l285] = 0.0;
		}
		for (int l286 = 0; l286 < 128; l286 = l286 + 1) {
			fYec92[l286] = 0.0;
		}
		fYec92_idx = 0;
		fYec92_idx_save = 0;
		for (int l287 = 0; l287 < 4; l287 = l287 + 1) {
			fRec185_perm[l287] = 0.0;
		}
		for (int l288 = 0; l288 < 4; l288 = l288 + 1) {
			fRec184_perm[l288] = 0.0;
		}
		for (int l289 = 0; l289 < 128; l289 = l289 + 1) {
			fYec93[l289] = 0.0;
		}
		fYec93_idx = 0;
		fYec93_idx_save = 0;
		for (int l290 = 0; l290 < 4; l290 = l290 + 1) {
			fRec187_perm[l290] = 0.0;
		}
		for (int l291 = 0; l291 < 4; l291 = l291 + 1) {
			fRec186_perm[l291] = 0.0;
		}
		for (int l292 = 0; l292 < 128; l292 = l292 + 1) {
			fYec94[l292] = 0.0;
		}
		fYec94_idx = 0;
		fYec94_idx_save = 0;
		for (int l293 = 0; l293 < 4; l293 = l293 + 1) {
			fRec189_perm[l293] = 0.0;
		}
		for (int l294 = 0; l294 < 4; l294 = l294 + 1) {
			fRec188_perm[l294] = 0.0;
		}
		for (int l295 = 0; l295 < 128; l295 = l295 + 1) {
			fYec95[l295] = 0.0;
		}
		fYec95_idx = 0;
		fYec95_idx_save = 0;
		for (int l296 = 0; l296 < 4; l296 = l296 + 1) {
			fRec191_perm[l296] = 0.0;
		}
		for (int l297 = 0; l297 < 4; l297 = l297 + 1) {
			fRec190_perm[l297] = 0.0;
		}
		for (int l298 = 0; l298 < 512; l298 = l298 + 1) {
			fYec96[l298] = 0.0;
		}
		fYec96_idx = 0;
		fYec96_idx_save = 0;
		for (int l299 = 0; l299 < 4; l299 = l299 + 1) {
			fRec193_perm[l299] = 0.0;
		}
		for (int l300 = 0; l300 < 4; l300 = l300 + 1) {
			fRec192_perm[l300] = 0.0;
		}
		for (int l301 = 0; l301 < 512; l301 = l301 + 1) {
			fYec97[l301] = 0.0;
		}
		fYec97_idx = 0;
		fYec97_idx_save = 0;
		for (int l302 = 0; l302 < 4; l302 = l302 + 1) {
			fRec195_perm[l302] = 0.0;
		}
		for (int l303 = 0; l303 < 4; l303 = l303 + 1) {
			fRec194_perm[l303] = 0.0;
		}
		for (int l304 = 0; l304 < 1024; l304 = l304 + 1) {
			fYec98[l304] = 0.0;
		}
		fYec98_idx = 0;
		fYec98_idx_save = 0;
		for (int l305 = 0; l305 < 4; l305 = l305 + 1) {
			fRec197_perm[l305] = 0.0;
		}
		for (int l306 = 0; l306 < 4; l306 = l306 + 1) {
			fRec196_perm[l306] = 0.0;
		}
		for (int l307 = 0; l307 < 1024; l307 = l307 + 1) {
			fYec99[l307] = 0.0;
		}
		fYec99_idx = 0;
		fYec99_idx_save = 0;
		for (int l308 = 0; l308 < 4; l308 = l308 + 1) {
			fRec199_perm[l308] = 0.0;
		}
		for (int l309 = 0; l309 < 4; l309 = l309 + 1) {
			fRec198_perm[l309] = 0.0;
		}
		for (int l310 = 0; l310 < 128; l310 = l310 + 1) {
			fYec100[l310] = 0.0;
		}
		fYec100_idx = 0;
		fYec100_idx_save = 0;
		for (int l311 = 0; l311 < 4; l311 = l311 + 1) {
			fRec201_perm[l311] = 0.0;
		}
		for (int l312 = 0; l312 < 4; l312 = l312 + 1) {
			fRec200_perm[l312] = 0.0;
		}
		for (int l313 = 0; l313 < 128; l313 = l313 + 1) {
			fYec101[l313] = 0.0;
		}
		fYec101_idx = 0;
		fYec101_idx_save = 0;
		for (int l314 = 0; l314 < 4; l314 = l314 + 1) {
			fRec203_perm[l314] = 0.0;
		}
		for (int l315 = 0; l315 < 4; l315 = l315 + 1) {
			fRec202_perm[l315] = 0.0;
		}
		for (int l316 = 0; l316 < 128; l316 = l316 + 1) {
			fYec102[l316] = 0.0;
		}
		fYec102_idx = 0;
		fYec102_idx_save = 0;
		for (int l317 = 0; l317 < 4; l317 = l317 + 1) {
			fRec205_perm[l317] = 0.0;
		}
		for (int l318 = 0; l318 < 4; l318 = l318 + 1) {
			fRec204_perm[l318] = 0.0;
		}
		for (int l319 = 0; l319 < 128; l319 = l319 + 1) {
			fYec103[l319] = 0.0;
		}
		fYec103_idx = 0;
		fYec103_idx_save = 0;
		for (int l320 = 0; l320 < 4; l320 = l320 + 1) {
			fRec207_perm[l320] = 0.0;
		}
		for (int l321 = 0; l321 < 4; l321 = l321 + 1) {
			fRec206_perm[l321] = 0.0;
		}
		for (int l322 = 0; l322 < 128; l322 = l322 + 1) {
			fYec104[l322] = 0.0;
		}
		fYec104_idx = 0;
		fYec104_idx_save = 0;
		for (int l323 = 0; l323 < 4; l323 = l323 + 1) {
			fRec209_perm[l323] = 0.0;
		}
		for (int l324 = 0; l324 < 4; l324 = l324 + 1) {
			fRec208_perm[l324] = 0.0;
		}
		for (int l325 = 0; l325 < 1024; l325 = l325 + 1) {
			fYec105[l325] = 0.0;
		}
		fYec105_idx = 0;
		fYec105_idx_save = 0;
		for (int l326 = 0; l326 < 4; l326 = l326 + 1) {
			fRec211_perm[l326] = 0.0;
		}
		for (int l327 = 0; l327 < 4; l327 = l327 + 1) {
			fRec210_perm[l327] = 0.0;
		}
		for (int l328 = 0; l328 < 1024; l328 = l328 + 1) {
			fYec106[l328] = 0.0;
		}
		fYec106_idx = 0;
		fYec106_idx_save = 0;
		for (int l329 = 0; l329 < 4; l329 = l329 + 1) {
			fRec213_perm[l329] = 0.0;
		}
		for (int l330 = 0; l330 < 4; l330 = l330 + 1) {
			fRec212_perm[l330] = 0.0;
		}
		for (int l331 = 0; l331 < 512; l331 = l331 + 1) {
			fYec107[l331] = 0.0;
		}
		fYec107_idx = 0;
		fYec107_idx_save = 0;
		for (int l332 = 0; l332 < 4; l332 = l332 + 1) {
			fRec215_perm[l332] = 0.0;
		}
		for (int l333 = 0; l333 < 4; l333 = l333 + 1) {
			fRec214_perm[l333] = 0.0;
		}
		for (int l334 = 0; l334 < 512; l334 = l334 + 1) {
			fYec108[l334] = 0.0;
		}
		fYec108_idx = 0;
		fYec108_idx_save = 0;
		for (int l335 = 0; l335 < 4; l335 = l335 + 1) {
			fRec217_perm[l335] = 0.0;
		}
		for (int l336 = 0; l336 < 4; l336 = l336 + 1) {
			fRec216_perm[l336] = 0.0;
		}
		for (int l337 = 0; l337 < 128; l337 = l337 + 1) {
			fYec109[l337] = 0.0;
		}
		fYec109_idx = 0;
		fYec109_idx_save = 0;
		for (int l338 = 0; l338 < 4; l338 = l338 + 1) {
			fRec219_perm[l338] = 0.0;
		}
		for (int l339 = 0; l339 < 4; l339 = l339 + 1) {
			fRec218_perm[l339] = 0.0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("bells");
		ui_interface->addNumEntry("feedback", &fEntry1, FAUSTFLOAT(0.989), FAUSTFLOAT(0.0), FAUSTFLOAT(1.0), FAUSTFLOAT(0.001));
		ui_interface->addNumEntry("pitch0", &fEntry9, FAUSTFLOAT(6e+01), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch1", &fEntry10, FAUSTFLOAT(61.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch2", &fEntry8, FAUSTFLOAT(62.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch3", &fEntry7, FAUSTFLOAT(63.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch4", &fEntry6, FAUSTFLOAT(64.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch5", &fEntry5, FAUSTFLOAT(65.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch6", &fEntry4, FAUSTFLOAT(66.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch7", &fEntry3, FAUSTFLOAT(67.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch8", &fEntry2, FAUSTFLOAT(68.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addNumEntry("pitch9", &fEntry0, FAUSTFLOAT(69.0), FAUSTFLOAT(6e+01), FAUSTFLOAT(1.6e+02), FAUSTFLOAT(0.01));
		ui_interface->addButton("play0", &fButton8);
		ui_interface->addButton("play1", &fButton9);
		ui_interface->addButton("play2", &fButton7);
		ui_interface->addButton("play3", &fButton6);
		ui_interface->addButton("play4", &fButton5);
		ui_interface->addButton("play5", &fButton4);
		ui_interface->addButton("play6", &fButton3);
		ui_interface->addButton("play7", &fButton2);
		ui_interface->addButton("play8", &fButton1);
		ui_interface->addButton("play9", &fButton0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		double fSlow0 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry0) + -69.0));
		double fSlow1 = static_cast<double>((2509.95888 * fSlow0) < fConst1);
		double fSlow2 = static_cast<double>(fEntry1);
		double fSlow3 = static_cast<double>(fButton0);
		double fVec0_tmp[36];
		double* fVec0 = &fVec0_tmp[4];
		double fZec0[32];
		int iSlow4 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow0)));
		double fSlow5 = fConst4 * std::cos(fConst5 * fSlow0);
		double fRec1_tmp[36];
		double* fRec1 = &fRec1_tmp[4];
		double fRec0_tmp[36];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow6 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry2) + -69.0));
		double fSlow7 = static_cast<double>((2509.95888 * fSlow6) < fConst1);
		double fSlow8 = static_cast<double>(fButton1);
		double fVec1_tmp[36];
		double* fVec1 = &fVec1_tmp[4];
		double fZec1[32];
		int iSlow9 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow6)));
		double fSlow10 = fConst4 * std::cos(fConst5 * fSlow6);
		double fRec3_tmp[36];
		double* fRec3 = &fRec3_tmp[4];
		double fRec2_tmp[36];
		double* fRec2 = &fRec2_tmp[4];
		double fSlow11 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry3) + -69.0));
		double fSlow12 = static_cast<double>((2509.95888 * fSlow11) < fConst1);
		double fSlow13 = static_cast<double>(fButton2);
		double fVec2_tmp[36];
		double* fVec2 = &fVec2_tmp[4];
		double fZec2[32];
		int iSlow14 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow11)));
		double fSlow15 = fConst4 * std::cos(fConst5 * fSlow11);
		double fRec5_tmp[36];
		double* fRec5 = &fRec5_tmp[4];
		double fRec4_tmp[36];
		double* fRec4 = &fRec4_tmp[4];
		double fSlow16 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry4) + -69.0));
		double fSlow17 = static_cast<double>((2509.95888 * fSlow16) < fConst1);
		double fSlow18 = static_cast<double>(fButton3);
		double fVec3_tmp[36];
		double* fVec3 = &fVec3_tmp[4];
		double fZec3[32];
		int iSlow19 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow16)));
		double fSlow20 = fConst4 * std::cos(fConst5 * fSlow16);
		double fRec7_tmp[36];
		double* fRec7 = &fRec7_tmp[4];
		double fRec6_tmp[36];
		double* fRec6 = &fRec6_tmp[4];
		double fSlow21 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry5) + -69.0));
		double fSlow22 = static_cast<double>((2509.95888 * fSlow21) < fConst1);
		double fSlow23 = static_cast<double>(fButton4);
		double fVec4_tmp[36];
		double* fVec4 = &fVec4_tmp[4];
		double fZec4[32];
		int iSlow24 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow21)));
		double fSlow25 = fConst4 * std::cos(fConst5 * fSlow21);
		double fRec9_tmp[36];
		double* fRec9 = &fRec9_tmp[4];
		double fRec8_tmp[36];
		double* fRec8 = &fRec8_tmp[4];
		double fSlow26 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry6) + -69.0));
		double fSlow27 = static_cast<double>((2509.95888 * fSlow26) < fConst1);
		double fSlow28 = static_cast<double>(fButton5);
		double fVec5_tmp[36];
		double* fVec5 = &fVec5_tmp[4];
		double fZec5[32];
		int iSlow29 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow26)));
		double fSlow30 = fConst4 * std::cos(fConst5 * fSlow26);
		double fRec11_tmp[36];
		double* fRec11 = &fRec11_tmp[4];
		double fRec10_tmp[36];
		double* fRec10 = &fRec10_tmp[4];
		double fSlow31 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry7) + -69.0));
		double fSlow32 = static_cast<double>((2509.95888 * fSlow31) < fConst1);
		double fSlow33 = static_cast<double>(fButton6);
		double fVec6_tmp[36];
		double* fVec6 = &fVec6_tmp[4];
		double fZec6[32];
		int iSlow34 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow31)));
		double fSlow35 = fConst4 * std::cos(fConst5 * fSlow31);
		double fRec13_tmp[36];
		double* fRec13 = &fRec13_tmp[4];
		double fRec12_tmp[36];
		double* fRec12 = &fRec12_tmp[4];
		double fSlow36 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry8) + -69.0));
		double fSlow37 = static_cast<double>((2509.95888 * fSlow36) < fConst1);
		double fSlow38 = static_cast<double>(fButton7);
		double fVec7_tmp[36];
		double* fVec7 = &fVec7_tmp[4];
		double fZec7[32];
		int iSlow39 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow36)));
		double fSlow40 = fConst4 * std::cos(fConst5 * fSlow36);
		double fRec15_tmp[36];
		double* fRec15 = &fRec15_tmp[4];
		double fRec14_tmp[36];
		double* fRec14 = &fRec14_tmp[4];
		double fSlow41 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry9) + -69.0));
		double fSlow42 = static_cast<double>((2509.95888 * fSlow41) < fConst1);
		double fSlow43 = static_cast<double>(fButton8);
		double fVec8_tmp[36];
		double* fVec8 = &fVec8_tmp[4];
		double fZec8[32];
		int iSlow44 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow41)));
		double fSlow45 = fConst4 * std::cos(fConst5 * fSlow41);
		double fRec17_tmp[36];
		double* fRec17 = &fRec17_tmp[4];
		double fRec16_tmp[36];
		double* fRec16 = &fRec16_tmp[4];
		double fSlow46 = std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fEntry10) + -69.0));
		double fSlow47 = static_cast<double>((2509.95888 * fSlow46) < fConst1);
		double fSlow48 = static_cast<double>(fButton9);
		double fVec9_tmp[36];
		double* fVec9 = &fVec9_tmp[4];
		double fZec9[32];
		int iSlow49 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst2 / fSlow46)));
		double fSlow50 = fConst4 * std::cos(fConst5 * fSlow46);
		double fRec19_tmp[36];
		double* fRec19 = &fRec19_tmp[4];
		double fRec18_tmp[36];
		double* fRec18 = &fRec18_tmp[4];
		double fSlow51 = static_cast<double>((9669.451879999999 * fSlow0) < fConst1);
		double fZec10[32];
		int iSlow52 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow0)));
		double fSlow53 = fConst4 * std::cos(fConst9 * fSlow0);
		double fRec21_tmp[36];
		double* fRec21 = &fRec21_tmp[4];
		double fRec20_tmp[36];
		double* fRec20 = &fRec20_tmp[4];
		double fSlow54 = static_cast<double>((7603.5621200000005 * fSlow0) < fConst1);
		int iSlow55 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow0)));
		double fSlow56 = fConst4 * std::cos(fConst11 * fSlow0);
		double fRec23_tmp[36];
		double* fRec23 = &fRec23_tmp[4];
		double fRec22_tmp[36];
		double* fRec22 = &fRec22_tmp[4];
		double fSlow57 = 0.9999655 * static_cast<double>((5635.24808 * fSlow0) < fConst1);
		double fZec11[32];
		int iSlow58 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow0)));
		double fSlow59 = fConst4 * std::cos(fConst13 * fSlow0);
		double fRec25_tmp[36];
		double* fRec25 = &fRec25_tmp[4];
		double fRec24_tmp[36];
		double* fRec24 = &fRec24_tmp[4];
		double fSlow60 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow0) < fConst1);
		int iSlow61 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow0)));
		double fSlow62 = fConst4 * std::cos(fConst15 * fSlow0);
		double fRec27_tmp[36];
		double* fRec27 = &fRec27_tmp[4];
		double fRec26_tmp[36];
		double* fRec26 = &fRec26_tmp[4];
		double fSlow63 = static_cast<double>((3966.81868 * fSlow0) < fConst1);
		double fZec12[32];
		int iSlow64 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow0)));
		double fSlow65 = fConst4 * std::cos(fConst17 * fSlow0);
		double fRec29_tmp[36];
		double* fRec29 = &fRec29_tmp[4];
		double fRec28_tmp[36];
		double* fRec28 = &fRec28_tmp[4];
		double fSlow66 = static_cast<double>((3959.208 * fSlow0) < fConst1);
		int iSlow67 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow0)));
		double fSlow68 = fConst4 * std::cos(fConst19 * fSlow0);
		double fRec31_tmp[36];
		double* fRec31 = &fRec31_tmp[4];
		double fRec30_tmp[36];
		double* fRec30 = &fRec30_tmp[4];
		double fSlow69 = 0.9999828 * static_cast<double>((1317.050944 * fSlow0) < fConst1);
		double fZec13[32];
		int iSlow70 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow0)));
		double fSlow71 = fConst4 * std::cos(fConst21 * fSlow0);
		double fRec33_tmp[36];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[36];
		double* fRec32 = &fRec32_tmp[4];
		double fSlow72 = 0.9999828 * static_cast<double>((1310.83832 * fSlow0) < fConst1);
		int iSlow73 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow0)));
		double fSlow74 = fConst4 * std::cos(fConst23 * fSlow0);
		double fRec35_tmp[36];
		double* fRec35 = &fRec35_tmp[4];
		double fRec34_tmp[36];
		double* fRec34 = &fRec34_tmp[4];
		double fSlow75 = 0.999926 * static_cast<double>((441.712348 * fSlow0) < fConst1);
		double fZec14[32];
		int iSlow76 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow0)));
		double fSlow77 = fConst4 * std::cos(fConst25 * fSlow0);
		double fRec37_tmp[36];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[36];
		double* fRec36 = &fRec36_tmp[4];
		double fSlow78 = 0.999926 * static_cast<double>((438.287674 * fSlow0) < fConst1);
		int iSlow79 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow0)));
		double fSlow80 = fConst4 * std::cos(fConst27 * fSlow0);
		double fRec39_tmp[36];
		double* fRec39 = &fRec39_tmp[4];
		double fRec38_tmp[36];
		double* fRec38 = &fRec38_tmp[4];
		double fSlow81 = static_cast<double>((9669.451879999999 * fSlow6) < fConst1);
		double fZec15[32];
		int iSlow82 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow6)));
		double fSlow83 = fConst4 * std::cos(fConst9 * fSlow6);
		double fRec41_tmp[36];
		double* fRec41 = &fRec41_tmp[4];
		double fRec40_tmp[36];
		double* fRec40 = &fRec40_tmp[4];
		double fSlow84 = static_cast<double>((7603.5621200000005 * fSlow6) < fConst1);
		int iSlow85 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow6)));
		double fSlow86 = fConst4 * std::cos(fConst11 * fSlow6);
		double fRec43_tmp[36];
		double* fRec43 = &fRec43_tmp[4];
		double fRec42_tmp[36];
		double* fRec42 = &fRec42_tmp[4];
		double fSlow87 = 0.9999655 * static_cast<double>((5635.24808 * fSlow6) < fConst1);
		double fZec16[32];
		int iSlow88 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow6)));
		double fSlow89 = fConst4 * std::cos(fConst13 * fSlow6);
		double fRec45_tmp[36];
		double* fRec45 = &fRec45_tmp[4];
		double fRec44_tmp[36];
		double* fRec44 = &fRec44_tmp[4];
		double fSlow90 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow6) < fConst1);
		int iSlow91 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow6)));
		double fSlow92 = fConst4 * std::cos(fConst15 * fSlow6);
		double fRec47_tmp[36];
		double* fRec47 = &fRec47_tmp[4];
		double fRec46_tmp[36];
		double* fRec46 = &fRec46_tmp[4];
		double fSlow93 = static_cast<double>((3966.81868 * fSlow6) < fConst1);
		double fZec17[32];
		int iSlow94 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow6)));
		double fSlow95 = fConst4 * std::cos(fConst17 * fSlow6);
		double fRec49_tmp[36];
		double* fRec49 = &fRec49_tmp[4];
		double fRec48_tmp[36];
		double* fRec48 = &fRec48_tmp[4];
		double fSlow96 = static_cast<double>((3959.208 * fSlow6) < fConst1);
		int iSlow97 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow6)));
		double fSlow98 = fConst4 * std::cos(fConst19 * fSlow6);
		double fRec51_tmp[36];
		double* fRec51 = &fRec51_tmp[4];
		double fRec50_tmp[36];
		double* fRec50 = &fRec50_tmp[4];
		double fSlow99 = 0.9999828 * static_cast<double>((1317.050944 * fSlow6) < fConst1);
		double fZec18[32];
		int iSlow100 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow6)));
		double fSlow101 = fConst4 * std::cos(fConst21 * fSlow6);
		double fRec53_tmp[36];
		double* fRec53 = &fRec53_tmp[4];
		double fRec52_tmp[36];
		double* fRec52 = &fRec52_tmp[4];
		double fSlow102 = 0.9999828 * static_cast<double>((1310.83832 * fSlow6) < fConst1);
		int iSlow103 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow6)));
		double fSlow104 = fConst4 * std::cos(fConst23 * fSlow6);
		double fRec55_tmp[36];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[36];
		double* fRec54 = &fRec54_tmp[4];
		double fSlow105 = 0.999926 * static_cast<double>((441.712348 * fSlow6) < fConst1);
		double fZec19[32];
		int iSlow106 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow6)));
		double fSlow107 = fConst4 * std::cos(fConst25 * fSlow6);
		double fRec57_tmp[36];
		double* fRec57 = &fRec57_tmp[4];
		double fRec56_tmp[36];
		double* fRec56 = &fRec56_tmp[4];
		double fSlow108 = 0.999926 * static_cast<double>((438.287674 * fSlow6) < fConst1);
		int iSlow109 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow6)));
		double fSlow110 = fConst4 * std::cos(fConst27 * fSlow6);
		double fRec59_tmp[36];
		double* fRec59 = &fRec59_tmp[4];
		double fRec58_tmp[36];
		double* fRec58 = &fRec58_tmp[4];
		double fSlow111 = static_cast<double>((9669.451879999999 * fSlow11) < fConst1);
		double fZec20[32];
		int iSlow112 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow11)));
		double fSlow113 = fConst4 * std::cos(fConst9 * fSlow11);
		double fRec61_tmp[36];
		double* fRec61 = &fRec61_tmp[4];
		double fRec60_tmp[36];
		double* fRec60 = &fRec60_tmp[4];
		double fSlow114 = static_cast<double>((7603.5621200000005 * fSlow11) < fConst1);
		int iSlow115 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow11)));
		double fSlow116 = fConst4 * std::cos(fConst11 * fSlow11);
		double fRec63_tmp[36];
		double* fRec63 = &fRec63_tmp[4];
		double fRec62_tmp[36];
		double* fRec62 = &fRec62_tmp[4];
		double fSlow117 = 0.9999655 * static_cast<double>((5635.24808 * fSlow11) < fConst1);
		double fZec21[32];
		int iSlow118 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow11)));
		double fSlow119 = fConst4 * std::cos(fConst13 * fSlow11);
		double fRec65_tmp[36];
		double* fRec65 = &fRec65_tmp[4];
		double fRec64_tmp[36];
		double* fRec64 = &fRec64_tmp[4];
		double fSlow120 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow11) < fConst1);
		int iSlow121 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow11)));
		double fSlow122 = fConst4 * std::cos(fConst15 * fSlow11);
		double fRec67_tmp[36];
		double* fRec67 = &fRec67_tmp[4];
		double fRec66_tmp[36];
		double* fRec66 = &fRec66_tmp[4];
		double fSlow123 = static_cast<double>((3966.81868 * fSlow11) < fConst1);
		double fZec22[32];
		int iSlow124 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow11)));
		double fSlow125 = fConst4 * std::cos(fConst17 * fSlow11);
		double fRec69_tmp[36];
		double* fRec69 = &fRec69_tmp[4];
		double fRec68_tmp[36];
		double* fRec68 = &fRec68_tmp[4];
		double fSlow126 = static_cast<double>((3959.208 * fSlow11) < fConst1);
		int iSlow127 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow11)));
		double fSlow128 = fConst4 * std::cos(fConst19 * fSlow11);
		double fRec71_tmp[36];
		double* fRec71 = &fRec71_tmp[4];
		double fRec70_tmp[36];
		double* fRec70 = &fRec70_tmp[4];
		double fSlow129 = 0.9999828 * static_cast<double>((1317.050944 * fSlow11) < fConst1);
		double fZec23[32];
		int iSlow130 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow11)));
		double fSlow131 = fConst4 * std::cos(fConst21 * fSlow11);
		double fRec73_tmp[36];
		double* fRec73 = &fRec73_tmp[4];
		double fRec72_tmp[36];
		double* fRec72 = &fRec72_tmp[4];
		double fSlow132 = 0.9999828 * static_cast<double>((1310.83832 * fSlow11) < fConst1);
		int iSlow133 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow11)));
		double fSlow134 = fConst4 * std::cos(fConst23 * fSlow11);
		double fRec75_tmp[36];
		double* fRec75 = &fRec75_tmp[4];
		double fRec74_tmp[36];
		double* fRec74 = &fRec74_tmp[4];
		double fSlow135 = 0.999926 * static_cast<double>((441.712348 * fSlow11) < fConst1);
		double fZec24[32];
		int iSlow136 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow11)));
		double fSlow137 = fConst4 * std::cos(fConst25 * fSlow11);
		double fRec77_tmp[36];
		double* fRec77 = &fRec77_tmp[4];
		double fRec76_tmp[36];
		double* fRec76 = &fRec76_tmp[4];
		double fSlow138 = 0.999926 * static_cast<double>((438.287674 * fSlow11) < fConst1);
		int iSlow139 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow11)));
		double fSlow140 = fConst4 * std::cos(fConst27 * fSlow11);
		double fRec79_tmp[36];
		double* fRec79 = &fRec79_tmp[4];
		double fRec78_tmp[36];
		double* fRec78 = &fRec78_tmp[4];
		double fSlow141 = static_cast<double>((9669.451879999999 * fSlow16) < fConst1);
		double fZec25[32];
		int iSlow142 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow16)));
		double fSlow143 = fConst4 * std::cos(fConst9 * fSlow16);
		double fRec81_tmp[36];
		double* fRec81 = &fRec81_tmp[4];
		double fRec80_tmp[36];
		double* fRec80 = &fRec80_tmp[4];
		double fSlow144 = static_cast<double>((7603.5621200000005 * fSlow16) < fConst1);
		int iSlow145 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow16)));
		double fSlow146 = fConst4 * std::cos(fConst11 * fSlow16);
		double fRec83_tmp[36];
		double* fRec83 = &fRec83_tmp[4];
		double fRec82_tmp[36];
		double* fRec82 = &fRec82_tmp[4];
		double fSlow147 = 0.9999655 * static_cast<double>((5635.24808 * fSlow16) < fConst1);
		double fZec26[32];
		int iSlow148 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow16)));
		double fSlow149 = fConst4 * std::cos(fConst13 * fSlow16);
		double fRec85_tmp[36];
		double* fRec85 = &fRec85_tmp[4];
		double fRec84_tmp[36];
		double* fRec84 = &fRec84_tmp[4];
		double fSlow150 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow16) < fConst1);
		int iSlow151 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow16)));
		double fSlow152 = fConst4 * std::cos(fConst15 * fSlow16);
		double fRec87_tmp[36];
		double* fRec87 = &fRec87_tmp[4];
		double fRec86_tmp[36];
		double* fRec86 = &fRec86_tmp[4];
		double fSlow153 = static_cast<double>((3966.81868 * fSlow16) < fConst1);
		double fZec27[32];
		int iSlow154 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow16)));
		double fSlow155 = fConst4 * std::cos(fConst17 * fSlow16);
		double fRec89_tmp[36];
		double* fRec89 = &fRec89_tmp[4];
		double fRec88_tmp[36];
		double* fRec88 = &fRec88_tmp[4];
		double fSlow156 = static_cast<double>((3959.208 * fSlow16) < fConst1);
		int iSlow157 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow16)));
		double fSlow158 = fConst4 * std::cos(fConst19 * fSlow16);
		double fRec91_tmp[36];
		double* fRec91 = &fRec91_tmp[4];
		double fRec90_tmp[36];
		double* fRec90 = &fRec90_tmp[4];
		double fSlow159 = 0.9999828 * static_cast<double>((1317.050944 * fSlow16) < fConst1);
		double fZec28[32];
		int iSlow160 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow16)));
		double fSlow161 = fConst4 * std::cos(fConst21 * fSlow16);
		double fRec93_tmp[36];
		double* fRec93 = &fRec93_tmp[4];
		double fRec92_tmp[36];
		double* fRec92 = &fRec92_tmp[4];
		double fSlow162 = 0.9999828 * static_cast<double>((1310.83832 * fSlow16) < fConst1);
		int iSlow163 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow16)));
		double fSlow164 = fConst4 * std::cos(fConst23 * fSlow16);
		double fRec95_tmp[36];
		double* fRec95 = &fRec95_tmp[4];
		double fRec94_tmp[36];
		double* fRec94 = &fRec94_tmp[4];
		double fSlow165 = 0.999926 * static_cast<double>((441.712348 * fSlow16) < fConst1);
		double fZec29[32];
		int iSlow166 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow16)));
		double fSlow167 = fConst4 * std::cos(fConst25 * fSlow16);
		double fRec97_tmp[36];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[36];
		double* fRec96 = &fRec96_tmp[4];
		double fSlow168 = 0.999926 * static_cast<double>((438.287674 * fSlow16) < fConst1);
		int iSlow169 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow16)));
		double fSlow170 = fConst4 * std::cos(fConst27 * fSlow16);
		double fRec99_tmp[36];
		double* fRec99 = &fRec99_tmp[4];
		double fRec98_tmp[36];
		double* fRec98 = &fRec98_tmp[4];
		double fSlow171 = static_cast<double>((9669.451879999999 * fSlow21) < fConst1);
		double fZec30[32];
		int iSlow172 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow21)));
		double fSlow173 = fConst4 * std::cos(fConst9 * fSlow21);
		double fRec101_tmp[36];
		double* fRec101 = &fRec101_tmp[4];
		double fRec100_tmp[36];
		double* fRec100 = &fRec100_tmp[4];
		double fSlow174 = static_cast<double>((7603.5621200000005 * fSlow21) < fConst1);
		int iSlow175 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow21)));
		double fSlow176 = fConst4 * std::cos(fConst11 * fSlow21);
		double fRec103_tmp[36];
		double* fRec103 = &fRec103_tmp[4];
		double fRec102_tmp[36];
		double* fRec102 = &fRec102_tmp[4];
		double fSlow177 = 0.9999655 * static_cast<double>((5635.24808 * fSlow21) < fConst1);
		double fZec31[32];
		int iSlow178 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow21)));
		double fSlow179 = fConst4 * std::cos(fConst13 * fSlow21);
		double fRec105_tmp[36];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[36];
		double* fRec104 = &fRec104_tmp[4];
		double fSlow180 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow21) < fConst1);
		int iSlow181 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow21)));
		double fSlow182 = fConst4 * std::cos(fConst15 * fSlow21);
		double fRec107_tmp[36];
		double* fRec107 = &fRec107_tmp[4];
		double fRec106_tmp[36];
		double* fRec106 = &fRec106_tmp[4];
		double fSlow183 = static_cast<double>((3966.81868 * fSlow21) < fConst1);
		double fZec32[32];
		int iSlow184 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow21)));
		double fSlow185 = fConst4 * std::cos(fConst17 * fSlow21);
		double fRec109_tmp[36];
		double* fRec109 = &fRec109_tmp[4];
		double fRec108_tmp[36];
		double* fRec108 = &fRec108_tmp[4];
		double fSlow186 = static_cast<double>((3959.208 * fSlow21) < fConst1);
		int iSlow187 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow21)));
		double fSlow188 = fConst4 * std::cos(fConst19 * fSlow21);
		double fRec111_tmp[36];
		double* fRec111 = &fRec111_tmp[4];
		double fRec110_tmp[36];
		double* fRec110 = &fRec110_tmp[4];
		double fSlow189 = 0.9999828 * static_cast<double>((1317.050944 * fSlow21) < fConst1);
		double fZec33[32];
		int iSlow190 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow21)));
		double fSlow191 = fConst4 * std::cos(fConst21 * fSlow21);
		double fRec113_tmp[36];
		double* fRec113 = &fRec113_tmp[4];
		double fRec112_tmp[36];
		double* fRec112 = &fRec112_tmp[4];
		double fSlow192 = 0.9999828 * static_cast<double>((1310.83832 * fSlow21) < fConst1);
		int iSlow193 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow21)));
		double fSlow194 = fConst4 * std::cos(fConst23 * fSlow21);
		double fRec115_tmp[36];
		double* fRec115 = &fRec115_tmp[4];
		double fRec114_tmp[36];
		double* fRec114 = &fRec114_tmp[4];
		double fSlow195 = 0.999926 * static_cast<double>((441.712348 * fSlow21) < fConst1);
		double fZec34[32];
		int iSlow196 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow21)));
		double fSlow197 = fConst4 * std::cos(fConst25 * fSlow21);
		double fRec117_tmp[36];
		double* fRec117 = &fRec117_tmp[4];
		double fRec116_tmp[36];
		double* fRec116 = &fRec116_tmp[4];
		double fSlow198 = 0.999926 * static_cast<double>((438.287674 * fSlow21) < fConst1);
		int iSlow199 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow21)));
		double fSlow200 = fConst4 * std::cos(fConst27 * fSlow21);
		double fRec119_tmp[36];
		double* fRec119 = &fRec119_tmp[4];
		double fRec118_tmp[36];
		double* fRec118 = &fRec118_tmp[4];
		double fSlow201 = static_cast<double>((9669.451879999999 * fSlow26) < fConst1);
		double fZec35[32];
		int iSlow202 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow26)));
		double fSlow203 = fConst4 * std::cos(fConst9 * fSlow26);
		double fRec121_tmp[36];
		double* fRec121 = &fRec121_tmp[4];
		double fRec120_tmp[36];
		double* fRec120 = &fRec120_tmp[4];
		double fSlow204 = static_cast<double>((7603.5621200000005 * fSlow26) < fConst1);
		int iSlow205 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow26)));
		double fSlow206 = fConst4 * std::cos(fConst11 * fSlow26);
		double fRec123_tmp[36];
		double* fRec123 = &fRec123_tmp[4];
		double fRec122_tmp[36];
		double* fRec122 = &fRec122_tmp[4];
		double fSlow207 = 0.9999655 * static_cast<double>((5635.24808 * fSlow26) < fConst1);
		double fZec36[32];
		int iSlow208 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow26)));
		double fSlow209 = fConst4 * std::cos(fConst13 * fSlow26);
		double fRec125_tmp[36];
		double* fRec125 = &fRec125_tmp[4];
		double fRec124_tmp[36];
		double* fRec124 = &fRec124_tmp[4];
		double fSlow210 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow26) < fConst1);
		int iSlow211 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow26)));
		double fSlow212 = fConst4 * std::cos(fConst15 * fSlow26);
		double fRec127_tmp[36];
		double* fRec127 = &fRec127_tmp[4];
		double fRec126_tmp[36];
		double* fRec126 = &fRec126_tmp[4];
		double fSlow213 = static_cast<double>((3966.81868 * fSlow26) < fConst1);
		double fZec37[32];
		int iSlow214 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow26)));
		double fSlow215 = fConst4 * std::cos(fConst17 * fSlow26);
		double fRec129_tmp[36];
		double* fRec129 = &fRec129_tmp[4];
		double fRec128_tmp[36];
		double* fRec128 = &fRec128_tmp[4];
		double fSlow216 = static_cast<double>((3959.208 * fSlow26) < fConst1);
		int iSlow217 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow26)));
		double fSlow218 = fConst4 * std::cos(fConst19 * fSlow26);
		double fRec131_tmp[36];
		double* fRec131 = &fRec131_tmp[4];
		double fRec130_tmp[36];
		double* fRec130 = &fRec130_tmp[4];
		double fSlow219 = 0.9999828 * static_cast<double>((1317.050944 * fSlow26) < fConst1);
		double fZec38[32];
		int iSlow220 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow26)));
		double fSlow221 = fConst4 * std::cos(fConst21 * fSlow26);
		double fRec133_tmp[36];
		double* fRec133 = &fRec133_tmp[4];
		double fRec132_tmp[36];
		double* fRec132 = &fRec132_tmp[4];
		double fSlow222 = 0.9999828 * static_cast<double>((1310.83832 * fSlow26) < fConst1);
		int iSlow223 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow26)));
		double fSlow224 = fConst4 * std::cos(fConst23 * fSlow26);
		double fRec135_tmp[36];
		double* fRec135 = &fRec135_tmp[4];
		double fRec134_tmp[36];
		double* fRec134 = &fRec134_tmp[4];
		double fSlow225 = 0.999926 * static_cast<double>((441.712348 * fSlow26) < fConst1);
		double fZec39[32];
		int iSlow226 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow26)));
		double fSlow227 = fConst4 * std::cos(fConst25 * fSlow26);
		double fRec137_tmp[36];
		double* fRec137 = &fRec137_tmp[4];
		double fRec136_tmp[36];
		double* fRec136 = &fRec136_tmp[4];
		double fSlow228 = 0.999926 * static_cast<double>((438.287674 * fSlow26) < fConst1);
		int iSlow229 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow26)));
		double fSlow230 = fConst4 * std::cos(fConst27 * fSlow26);
		double fRec139_tmp[36];
		double* fRec139 = &fRec139_tmp[4];
		double fRec138_tmp[36];
		double* fRec138 = &fRec138_tmp[4];
		double fSlow231 = static_cast<double>((9669.451879999999 * fSlow31) < fConst1);
		double fZec40[32];
		int iSlow232 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow31)));
		double fSlow233 = fConst4 * std::cos(fConst9 * fSlow31);
		double fRec141_tmp[36];
		double* fRec141 = &fRec141_tmp[4];
		double fRec140_tmp[36];
		double* fRec140 = &fRec140_tmp[4];
		double fSlow234 = static_cast<double>((7603.5621200000005 * fSlow31) < fConst1);
		int iSlow235 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow31)));
		double fSlow236 = fConst4 * std::cos(fConst11 * fSlow31);
		double fRec143_tmp[36];
		double* fRec143 = &fRec143_tmp[4];
		double fRec142_tmp[36];
		double* fRec142 = &fRec142_tmp[4];
		double fSlow237 = 0.9999655 * static_cast<double>((5635.24808 * fSlow31) < fConst1);
		double fZec41[32];
		int iSlow238 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow31)));
		double fSlow239 = fConst4 * std::cos(fConst13 * fSlow31);
		double fRec145_tmp[36];
		double* fRec145 = &fRec145_tmp[4];
		double fRec144_tmp[36];
		double* fRec144 = &fRec144_tmp[4];
		double fSlow240 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow31) < fConst1);
		int iSlow241 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow31)));
		double fSlow242 = fConst4 * std::cos(fConst15 * fSlow31);
		double fRec147_tmp[36];
		double* fRec147 = &fRec147_tmp[4];
		double fRec146_tmp[36];
		double* fRec146 = &fRec146_tmp[4];
		double fSlow243 = static_cast<double>((3966.81868 * fSlow31) < fConst1);
		double fZec42[32];
		int iSlow244 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow31)));
		double fSlow245 = fConst4 * std::cos(fConst17 * fSlow31);
		double fRec149_tmp[36];
		double* fRec149 = &fRec149_tmp[4];
		double fRec148_tmp[36];
		double* fRec148 = &fRec148_tmp[4];
		double fSlow246 = static_cast<double>((3959.208 * fSlow31) < fConst1);
		int iSlow247 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow31)));
		double fSlow248 = fConst4 * std::cos(fConst19 * fSlow31);
		double fRec151_tmp[36];
		double* fRec151 = &fRec151_tmp[4];
		double fRec150_tmp[36];
		double* fRec150 = &fRec150_tmp[4];
		double fSlow249 = 0.9999828 * static_cast<double>((1317.050944 * fSlow31) < fConst1);
		double fZec43[32];
		int iSlow250 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow31)));
		double fSlow251 = fConst4 * std::cos(fConst21 * fSlow31);
		double fRec153_tmp[36];
		double* fRec153 = &fRec153_tmp[4];
		double fRec152_tmp[36];
		double* fRec152 = &fRec152_tmp[4];
		double fSlow252 = 0.9999828 * static_cast<double>((1310.83832 * fSlow31) < fConst1);
		int iSlow253 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow31)));
		double fSlow254 = fConst4 * std::cos(fConst23 * fSlow31);
		double fRec155_tmp[36];
		double* fRec155 = &fRec155_tmp[4];
		double fRec154_tmp[36];
		double* fRec154 = &fRec154_tmp[4];
		double fSlow255 = 0.999926 * static_cast<double>((441.712348 * fSlow31) < fConst1);
		double fZec44[32];
		int iSlow256 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow31)));
		double fSlow257 = fConst4 * std::cos(fConst25 * fSlow31);
		double fRec157_tmp[36];
		double* fRec157 = &fRec157_tmp[4];
		double fRec156_tmp[36];
		double* fRec156 = &fRec156_tmp[4];
		double fSlow258 = 0.999926 * static_cast<double>((438.287674 * fSlow31) < fConst1);
		int iSlow259 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow31)));
		double fSlow260 = fConst4 * std::cos(fConst27 * fSlow31);
		double fRec159_tmp[36];
		double* fRec159 = &fRec159_tmp[4];
		double fRec158_tmp[36];
		double* fRec158 = &fRec158_tmp[4];
		double fSlow261 = static_cast<double>((9669.451879999999 * fSlow36) < fConst1);
		double fZec45[32];
		int iSlow262 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow36)));
		double fSlow263 = fConst4 * std::cos(fConst9 * fSlow36);
		double fRec161_tmp[36];
		double* fRec161 = &fRec161_tmp[4];
		double fRec160_tmp[36];
		double* fRec160 = &fRec160_tmp[4];
		double fSlow264 = static_cast<double>((7603.5621200000005 * fSlow36) < fConst1);
		int iSlow265 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow36)));
		double fSlow266 = fConst4 * std::cos(fConst11 * fSlow36);
		double fRec163_tmp[36];
		double* fRec163 = &fRec163_tmp[4];
		double fRec162_tmp[36];
		double* fRec162 = &fRec162_tmp[4];
		double fSlow267 = 0.9999655 * static_cast<double>((5635.24808 * fSlow36) < fConst1);
		double fZec46[32];
		int iSlow268 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow36)));
		double fSlow269 = fConst4 * std::cos(fConst13 * fSlow36);
		double fRec165_tmp[36];
		double* fRec165 = &fRec165_tmp[4];
		double fRec164_tmp[36];
		double* fRec164 = &fRec164_tmp[4];
		double fSlow270 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow36) < fConst1);
		int iSlow271 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow36)));
		double fSlow272 = fConst4 * std::cos(fConst15 * fSlow36);
		double fRec167_tmp[36];
		double* fRec167 = &fRec167_tmp[4];
		double fRec166_tmp[36];
		double* fRec166 = &fRec166_tmp[4];
		double fSlow273 = static_cast<double>((3966.81868 * fSlow36) < fConst1);
		double fZec47[32];
		int iSlow274 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow36)));
		double fSlow275 = fConst4 * std::cos(fConst17 * fSlow36);
		double fRec169_tmp[36];
		double* fRec169 = &fRec169_tmp[4];
		double fRec168_tmp[36];
		double* fRec168 = &fRec168_tmp[4];
		double fSlow276 = static_cast<double>((3959.208 * fSlow36) < fConst1);
		int iSlow277 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow36)));
		double fSlow278 = fConst4 * std::cos(fConst19 * fSlow36);
		double fRec171_tmp[36];
		double* fRec171 = &fRec171_tmp[4];
		double fRec170_tmp[36];
		double* fRec170 = &fRec170_tmp[4];
		double fSlow279 = 0.9999828 * static_cast<double>((1317.050944 * fSlow36) < fConst1);
		double fZec48[32];
		int iSlow280 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow36)));
		double fSlow281 = fConst4 * std::cos(fConst21 * fSlow36);
		double fRec173_tmp[36];
		double* fRec173 = &fRec173_tmp[4];
		double fRec172_tmp[36];
		double* fRec172 = &fRec172_tmp[4];
		double fSlow282 = 0.9999828 * static_cast<double>((1310.83832 * fSlow36) < fConst1);
		int iSlow283 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow36)));
		double fSlow284 = fConst4 * std::cos(fConst23 * fSlow36);
		double fRec175_tmp[36];
		double* fRec175 = &fRec175_tmp[4];
		double fRec174_tmp[36];
		double* fRec174 = &fRec174_tmp[4];
		double fSlow285 = 0.999926 * static_cast<double>((441.712348 * fSlow36) < fConst1);
		double fZec49[32];
		int iSlow286 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow36)));
		double fSlow287 = fConst4 * std::cos(fConst25 * fSlow36);
		double fRec177_tmp[36];
		double* fRec177 = &fRec177_tmp[4];
		double fRec176_tmp[36];
		double* fRec176 = &fRec176_tmp[4];
		double fSlow288 = 0.999926 * static_cast<double>((438.287674 * fSlow36) < fConst1);
		int iSlow289 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow36)));
		double fSlow290 = fConst4 * std::cos(fConst27 * fSlow36);
		double fRec179_tmp[36];
		double* fRec179 = &fRec179_tmp[4];
		double fRec178_tmp[36];
		double* fRec178 = &fRec178_tmp[4];
		double fSlow291 = static_cast<double>((9669.451879999999 * fSlow46) < fConst1);
		double fZec50[32];
		int iSlow292 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow46)));
		double fSlow293 = fConst4 * std::cos(fConst9 * fSlow46);
		double fRec181_tmp[36];
		double* fRec181 = &fRec181_tmp[4];
		double fRec180_tmp[36];
		double* fRec180 = &fRec180_tmp[4];
		double fSlow294 = static_cast<double>((7603.5621200000005 * fSlow46) < fConst1);
		int iSlow295 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow46)));
		double fSlow296 = fConst4 * std::cos(fConst11 * fSlow46);
		double fRec183_tmp[36];
		double* fRec183 = &fRec183_tmp[4];
		double fRec182_tmp[36];
		double* fRec182 = &fRec182_tmp[4];
		double fSlow297 = 0.9999655 * static_cast<double>((5635.24808 * fSlow46) < fConst1);
		double fZec51[32];
		int iSlow298 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow46)));
		double fSlow299 = fConst4 * std::cos(fConst13 * fSlow46);
		double fRec185_tmp[36];
		double* fRec185 = &fRec185_tmp[4];
		double fRec184_tmp[36];
		double* fRec184 = &fRec184_tmp[4];
		double fSlow300 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow46) < fConst1);
		int iSlow301 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow46)));
		double fSlow302 = fConst4 * std::cos(fConst15 * fSlow46);
		double fRec187_tmp[36];
		double* fRec187 = &fRec187_tmp[4];
		double fRec186_tmp[36];
		double* fRec186 = &fRec186_tmp[4];
		double fSlow303 = static_cast<double>((3966.81868 * fSlow46) < fConst1);
		double fZec52[32];
		int iSlow304 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow46)));
		double fSlow305 = fConst4 * std::cos(fConst17 * fSlow46);
		double fRec189_tmp[36];
		double* fRec189 = &fRec189_tmp[4];
		double fRec188_tmp[36];
		double* fRec188 = &fRec188_tmp[4];
		double fSlow306 = static_cast<double>((3959.208 * fSlow46) < fConst1);
		int iSlow307 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow46)));
		double fSlow308 = fConst4 * std::cos(fConst19 * fSlow46);
		double fRec191_tmp[36];
		double* fRec191 = &fRec191_tmp[4];
		double fRec190_tmp[36];
		double* fRec190 = &fRec190_tmp[4];
		double fSlow309 = 0.9999828 * static_cast<double>((1317.050944 * fSlow46) < fConst1);
		double fZec53[32];
		int iSlow310 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow46)));
		double fSlow311 = fConst4 * std::cos(fConst21 * fSlow46);
		double fRec193_tmp[36];
		double* fRec193 = &fRec193_tmp[4];
		double fRec192_tmp[36];
		double* fRec192 = &fRec192_tmp[4];
		double fSlow312 = 0.9999828 * static_cast<double>((1310.83832 * fSlow46) < fConst1);
		int iSlow313 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow46)));
		double fSlow314 = fConst4 * std::cos(fConst23 * fSlow46);
		double fRec195_tmp[36];
		double* fRec195 = &fRec195_tmp[4];
		double fRec194_tmp[36];
		double* fRec194 = &fRec194_tmp[4];
		double fSlow315 = 0.999926 * static_cast<double>((441.712348 * fSlow46) < fConst1);
		double fZec54[32];
		int iSlow316 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow46)));
		double fSlow317 = fConst4 * std::cos(fConst25 * fSlow46);
		double fRec197_tmp[36];
		double* fRec197 = &fRec197_tmp[4];
		double fRec196_tmp[36];
		double* fRec196 = &fRec196_tmp[4];
		double fSlow318 = 0.999926 * static_cast<double>((438.287674 * fSlow46) < fConst1);
		int iSlow319 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow46)));
		double fSlow320 = fConst4 * std::cos(fConst27 * fSlow46);
		double fRec199_tmp[36];
		double* fRec199 = &fRec199_tmp[4];
		double fRec198_tmp[36];
		double* fRec198 = &fRec198_tmp[4];
		double fSlow321 = static_cast<double>((9669.451879999999 * fSlow41) < fConst1);
		double fZec55[32];
		int iSlow322 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst8 / fSlow41)));
		double fSlow323 = fConst4 * std::cos(fConst9 * fSlow41);
		double fRec201_tmp[36];
		double* fRec201 = &fRec201_tmp[4];
		double fRec200_tmp[36];
		double* fRec200 = &fRec200_tmp[4];
		double fSlow324 = static_cast<double>((7603.5621200000005 * fSlow41) < fConst1);
		int iSlow325 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst10 / fSlow41)));
		double fSlow326 = fConst4 * std::cos(fConst11 * fSlow41);
		double fRec203_tmp[36];
		double* fRec203 = &fRec203_tmp[4];
		double fRec202_tmp[36];
		double* fRec202 = &fRec202_tmp[4];
		double fSlow327 = 0.9999655 * static_cast<double>((5635.24808 * fSlow41) < fConst1);
		double fZec56[32];
		int iSlow328 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst12 / fSlow41)));
		double fSlow329 = fConst4 * std::cos(fConst13 * fSlow41);
		double fRec205_tmp[36];
		double* fRec205 = &fRec205_tmp[4];
		double fRec204_tmp[36];
		double* fRec204 = &fRec204_tmp[4];
		double fSlow330 = 0.9999655 * static_cast<double>((5646.533200000001 * fSlow41) < fConst1);
		int iSlow331 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst14 / fSlow41)));
		double fSlow332 = fConst4 * std::cos(fConst15 * fSlow41);
		double fRec207_tmp[36];
		double* fRec207 = &fRec207_tmp[4];
		double fRec206_tmp[36];
		double* fRec206 = &fRec206_tmp[4];
		double fSlow333 = static_cast<double>((3966.81868 * fSlow41) < fConst1);
		double fZec57[32];
		int iSlow334 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst16 / fSlow41)));
		double fSlow335 = fConst4 * std::cos(fConst17 * fSlow41);
		double fRec209_tmp[36];
		double* fRec209 = &fRec209_tmp[4];
		double fRec208_tmp[36];
		double* fRec208 = &fRec208_tmp[4];
		double fSlow336 = 0.999926 * static_cast<double>((438.287674 * fSlow41) < fConst1);
		double fZec58[32];
		int iSlow337 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst26 / fSlow41)));
		double fSlow338 = fConst4 * std::cos(fConst27 * fSlow41);
		double fRec211_tmp[36];
		double* fRec211 = &fRec211_tmp[4];
		double fRec210_tmp[36];
		double* fRec210 = &fRec210_tmp[4];
		double fSlow339 = 0.999926 * static_cast<double>((441.712348 * fSlow41) < fConst1);
		int iSlow340 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst24 / fSlow41)));
		double fSlow341 = fConst4 * std::cos(fConst25 * fSlow41);
		double fRec213_tmp[36];
		double* fRec213 = &fRec213_tmp[4];
		double fRec212_tmp[36];
		double* fRec212 = &fRec212_tmp[4];
		double fSlow342 = 0.9999828 * static_cast<double>((1310.83832 * fSlow41) < fConst1);
		double fZec59[32];
		int iSlow343 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst22 / fSlow41)));
		double fSlow344 = fConst4 * std::cos(fConst23 * fSlow41);
		double fRec215_tmp[36];
		double* fRec215 = &fRec215_tmp[4];
		double fRec214_tmp[36];
		double* fRec214 = &fRec214_tmp[4];
		double fSlow345 = 0.9999828 * static_cast<double>((1317.050944 * fSlow41) < fConst1);
		int iSlow346 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst20 / fSlow41)));
		double fSlow347 = fConst4 * std::cos(fConst21 * fSlow41);
		double fRec217_tmp[36];
		double* fRec217 = &fRec217_tmp[4];
		double fRec216_tmp[36];
		double* fRec216 = &fRec216_tmp[4];
		double fSlow348 = static_cast<double>((3959.208 * fSlow41) < fConst1);
		int iSlow349 = static_cast<int>(std::min<double>(4096.0, std::max<double>(0.0, fConst18 / fSlow41)));
		double fSlow350 = fConst4 * std::cos(fConst19 * fSlow41);
		double fRec219_tmp[36];
		double* fRec219 = &fRec219_tmp[4];
		double fRec218_tmp[36];
		double* fRec218 = &fRec218_tmp[4];
		int vindex = 0;

		/* Main loop */
		for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 32;
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fVec0_tmp[j0] = fVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec0[i] = fSlow3;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fVec0_perm[j1] = fVec0_tmp[vsize + j1];
			}
			/* Vectorizable loop 1 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fVec1_tmp[j6] = fVec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec1[i] = fSlow8;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fVec1_perm[j7] = fVec1_tmp[vsize + j7];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fVec2_tmp[j12] = fVec2_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec2[i] = fSlow13;
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fVec2_perm[j13] = fVec2_tmp[vsize + j13];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fVec3_tmp[j18] = fVec3_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec3[i] = fSlow18;
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fVec3_perm[j19] = fVec3_tmp[vsize + j19];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
				fVec4_tmp[j24] = fVec4_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec4[i] = fSlow23;
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
				fVec4_perm[j25] = fVec4_tmp[vsize + j25];
			}
			/* Vectorizable loop 5 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
				fVec5_tmp[j30] = fVec5_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec5[i] = fSlow28;
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
				fVec5_perm[j31] = fVec5_tmp[vsize + j31];
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
				fVec6_tmp[j36] = fVec6_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec6[i] = fSlow33;
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
				fVec6_perm[j37] = fVec6_tmp[vsize + j37];
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
				fVec7_tmp[j42] = fVec7_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec7[i] = fSlow38;
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
				fVec7_perm[j43] = fVec7_tmp[vsize + j43];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
				fVec8_tmp[j48] = fVec8_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec8[i] = fSlow43;
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
				fVec8_perm[j49] = fVec8_tmp[vsize + j49];
			}
			/* Vectorizable loop 9 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
				fVec9_tmp[j54] = fVec9_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec9[i] = fSlow48;
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
				fVec9_perm[j55] = fVec9_tmp[vsize + j55];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = static_cast<double>(fSlow3 > fVec0[i - 1]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = static_cast<double>(fSlow8 > fVec1[i - 1]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = static_cast<double>(fSlow13 > fVec2[i - 1]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = static_cast<double>(fSlow18 > fVec3[i - 1]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = static_cast<double>(fSlow23 > fVec4[i - 1]);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = static_cast<double>(fSlow28 > fVec5[i - 1]);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = static_cast<double>(fSlow33 > fVec6[i - 1]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = static_cast<double>(fSlow38 > fVec7[i - 1]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = static_cast<double>(fSlow43 > fVec8[i - 1]);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = static_cast<double>(fSlow48 > fVec9[i - 1]);
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec25[i] = 6.7063036 * fZec3[i];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec26[i] = 1.7063034 * fZec3[i];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec27[i] = 5.0063033 * fZec3[i];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec28[i] = 2.0914886 * fZec3[i];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec29[i] = 2.1900357 * fZec3[i];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec30[i] = 6.7063036 * fZec4[i];
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec31[i] = 1.7063034 * fZec4[i];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec32[i] = 5.0063033 * fZec4[i];
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec33[i] = 2.0914886 * fZec4[i];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec34[i] = 2.1900357 * fZec4[i];
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec35[i] = 6.7063036 * fZec5[i];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec36[i] = 1.7063034 * fZec5[i];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec37[i] = 5.0063033 * fZec5[i];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec38[i] = 2.0914886 * fZec5[i];
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec39[i] = 2.1900357 * fZec5[i];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec40[i] = 6.7063036 * fZec6[i];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec41[i] = 1.7063034 * fZec6[i];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec42[i] = 5.0063033 * fZec6[i];
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec43[i] = 2.0914886 * fZec6[i];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec44[i] = 2.1900357 * fZec6[i];
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec45[i] = 6.7063036 * fZec7[i];
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec46[i] = 1.7063034 * fZec7[i];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec47[i] = 5.0063033 * fZec7[i];
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec48[i] = 2.0914886 * fZec7[i];
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec49[i] = 2.1900357 * fZec7[i];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec50[i] = 6.7063036 * fZec9[i];
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec51[i] = 1.7063034 * fZec9[i];
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec52[i] = 5.0063033 * fZec9[i];
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec53[i] = 2.0914886 * fZec9[i];
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec54[i] = 2.1900357 * fZec9[i];
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec55[i] = 6.7063036 * fZec8[i];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec56[i] = 1.7063034 * fZec8[i];
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec57[i] = 5.0063033 * fZec8[i];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec58[i] = 2.1900357 * fZec8[i];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec59[i] = 2.0914886 * fZec8[i];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec10[i] = 6.7063036 * fZec0[i];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec11[i] = 1.7063034 * fZec0[i];
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec12[i] = 5.0063033 * fZec0[i];
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec13[i] = 2.0914886 * fZec0[i];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec14[i] = 2.1900357 * fZec0[i];
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec15[i] = 6.7063036 * fZec1[i];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec16[i] = 1.7063034 * fZec1[i];
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec17[i] = 5.0063033 * fZec1[i];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec18[i] = 2.0914886 * fZec1[i];
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec19[i] = 2.1900357 * fZec1[i];
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec20[i] = 6.7063036 * fZec2[i];
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec21[i] = 1.7063034 * fZec2[i];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec22[i] = 5.0063033 * fZec2[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec23[i] = 2.0914886 * fZec2[i];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec24[i] = 2.1900357 * fZec2[i];
			}
			/* Recursive loop 70 */
			/* Pre code */
			fYec0_idx = (fYec0_idx + fYec0_idx_save) & 255;
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				fRec0_tmp[j4] = fRec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[(i + fYec0_idx) & 255] = fSlow2 * fRec0[i - 1] + 5.2995043 * fZec0[i];
				fRec1[i] = fSlow1 * fYec0[(i + fYec0_idx - iSlow4) & 255] - (fSlow5 * fRec1[i - 1] + fConst6 * fRec1[i - 2]);
				fRec0[i] = fConst7 * (fRec1[i] - fRec1[i - 2]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec1_perm[j3] = fRec1_tmp[vsize + j3];
			}
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				fRec0_perm[j5] = fRec0_tmp[vsize + j5];
			}
			/* Recursive loop 71 */
			/* Pre code */
			fYec1_idx = (fYec1_idx + fYec1_idx_save) & 255;
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fRec3_tmp[j8] = fRec3_perm[j8];
			}
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				fRec2_tmp[j10] = fRec2_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[(i + fYec1_idx) & 255] = fSlow2 * fRec2[i - 1] + 5.2995043 * fZec1[i];
				fRec3[i] = fSlow7 * fYec1[(i + fYec1_idx - iSlow9) & 255] - (fSlow10 * fRec3[i - 1] + fConst6 * fRec3[i - 2]);
				fRec2[i] = fConst7 * (fRec3[i] - fRec3[i - 2]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fRec3_perm[j9] = fRec3_tmp[vsize + j9];
			}
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				fRec2_perm[j11] = fRec2_tmp[vsize + j11];
			}
			/* Recursive loop 72 */
			/* Pre code */
			fYec39_idx = (fYec39_idx + fYec39_idx_save) & 1023;
			for (int j176 = 0; j176 < 4; j176 = j176 + 1) {
				fRec79_tmp[j176] = fRec79_perm[j176];
			}
			for (int j178 = 0; j178 < 4; j178 = j178 + 1) {
				fRec78_tmp[j178] = fRec78_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec39[(i + fYec39_idx) & 1023] = fSlow2 * fRec78[i - 1] + fZec24[i];
				fRec79[i] = fSlow138 * fYec39[(i + fYec39_idx - iSlow139) & 1023] - (fSlow140 * fRec79[i - 1] + fConst6 * fRec79[i - 2]);
				fRec78[i] = fConst7 * (fRec79[i] - fRec79[i - 2]);
			}
			/* Post code */
			fYec39_idx_save = vsize;
			for (int j177 = 0; j177 < 4; j177 = j177 + 1) {
				fRec79_perm[j177] = fRec79_tmp[vsize + j177];
			}
			for (int j179 = 0; j179 < 4; j179 = j179 + 1) {
				fRec78_perm[j179] = fRec78_tmp[vsize + j179];
			}
			/* Recursive loop 73 */
			/* Pre code */
			fYec40_idx = (fYec40_idx + fYec40_idx_save) & 127;
			for (int j180 = 0; j180 < 4; j180 = j180 + 1) {
				fRec81_tmp[j180] = fRec81_perm[j180];
			}
			for (int j182 = 0; j182 < 4; j182 = j182 + 1) {
				fRec80_tmp[j182] = fRec80_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec40[(i + fYec40_idx) & 127] = fZec25[i] + fSlow2 * fRec80[i - 1];
				fRec81[i] = fSlow141 * fYec40[(i + fYec40_idx - iSlow142) & 127] - (fSlow143 * fRec81[i - 1] + fConst6 * fRec81[i - 2]);
				fRec80[i] = fConst7 * (fRec81[i] - fRec81[i - 2]);
			}
			/* Post code */
			fYec40_idx_save = vsize;
			for (int j181 = 0; j181 < 4; j181 = j181 + 1) {
				fRec81_perm[j181] = fRec81_tmp[vsize + j181];
			}
			for (int j183 = 0; j183 < 4; j183 = j183 + 1) {
				fRec80_perm[j183] = fRec80_tmp[vsize + j183];
			}
			/* Recursive loop 74 */
			/* Pre code */
			fYec41_idx = (fYec41_idx + fYec41_idx_save) & 127;
			for (int j184 = 0; j184 < 4; j184 = j184 + 1) {
				fRec83_tmp[j184] = fRec83_perm[j184];
			}
			for (int j186 = 0; j186 < 4; j186 = j186 + 1) {
				fRec82_tmp[j186] = fRec82_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec41[(i + fYec41_idx) & 127] = fSlow2 * fRec82[i - 1] + fZec25[i];
				fRec83[i] = fSlow144 * fYec41[(i + fYec41_idx - iSlow145) & 127] - (fSlow146 * fRec83[i - 1] + fConst6 * fRec83[i - 2]);
				fRec82[i] = fConst7 * (fRec83[i] - fRec83[i - 2]);
			}
			/* Post code */
			fYec41_idx_save = vsize;
			for (int j185 = 0; j185 < 4; j185 = j185 + 1) {
				fRec83_perm[j185] = fRec83_tmp[vsize + j185];
			}
			for (int j187 = 0; j187 < 4; j187 = j187 + 1) {
				fRec82_perm[j187] = fRec82_tmp[vsize + j187];
			}
			/* Recursive loop 75 */
			/* Pre code */
			fYec42_idx = (fYec42_idx + fYec42_idx_save) & 127;
			for (int j188 = 0; j188 < 4; j188 = j188 + 1) {
				fRec85_tmp[j188] = fRec85_perm[j188];
			}
			for (int j190 = 0; j190 < 4; j190 = j190 + 1) {
				fRec84_tmp[j190] = fRec84_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec42[(i + fYec42_idx) & 127] = fZec26[i] + fSlow2 * fRec84[i - 1];
				fRec85[i] = fSlow147 * fYec42[(i + fYec42_idx - iSlow148) & 127] - (fSlow149 * fRec85[i - 1] + fConst6 * fRec85[i - 2]);
				fRec84[i] = fConst7 * (fRec85[i] - fRec85[i - 2]);
			}
			/* Post code */
			fYec42_idx_save = vsize;
			for (int j189 = 0; j189 < 4; j189 = j189 + 1) {
				fRec85_perm[j189] = fRec85_tmp[vsize + j189];
			}
			for (int j191 = 0; j191 < 4; j191 = j191 + 1) {
				fRec84_perm[j191] = fRec84_tmp[vsize + j191];
			}
			/* Recursive loop 76 */
			/* Pre code */
			fYec43_idx = (fYec43_idx + fYec43_idx_save) & 127;
			for (int j192 = 0; j192 < 4; j192 = j192 + 1) {
				fRec87_tmp[j192] = fRec87_perm[j192];
			}
			for (int j194 = 0; j194 < 4; j194 = j194 + 1) {
				fRec86_tmp[j194] = fRec86_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec43[(i + fYec43_idx) & 127] = fSlow2 * fRec86[i - 1] + fZec26[i];
				fRec87[i] = fSlow150 * fYec43[(i + fYec43_idx - iSlow151) & 127] - (fSlow152 * fRec87[i - 1] + fConst6 * fRec87[i - 2]);
				fRec86[i] = fConst7 * (fRec87[i] - fRec87[i - 2]);
			}
			/* Post code */
			fYec43_idx_save = vsize;
			for (int j193 = 0; j193 < 4; j193 = j193 + 1) {
				fRec87_perm[j193] = fRec87_tmp[vsize + j193];
			}
			for (int j195 = 0; j195 < 4; j195 = j195 + 1) {
				fRec86_perm[j195] = fRec86_tmp[vsize + j195];
			}
			/* Recursive loop 77 */
			/* Pre code */
			fYec44_idx = (fYec44_idx + fYec44_idx_save) & 127;
			for (int j196 = 0; j196 < 4; j196 = j196 + 1) {
				fRec89_tmp[j196] = fRec89_perm[j196];
			}
			for (int j198 = 0; j198 < 4; j198 = j198 + 1) {
				fRec88_tmp[j198] = fRec88_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec44[(i + fYec44_idx) & 127] = fZec27[i] + fSlow2 * fRec88[i - 1];
				fRec89[i] = fSlow153 * fYec44[(i + fYec44_idx - iSlow154) & 127] - (fSlow155 * fRec89[i - 1] + fConst6 * fRec89[i - 2]);
				fRec88[i] = fConst7 * (fRec89[i] - fRec89[i - 2]);
			}
			/* Post code */
			fYec44_idx_save = vsize;
			for (int j197 = 0; j197 < 4; j197 = j197 + 1) {
				fRec89_perm[j197] = fRec89_tmp[vsize + j197];
			}
			for (int j199 = 0; j199 < 4; j199 = j199 + 1) {
				fRec88_perm[j199] = fRec88_tmp[vsize + j199];
			}
			/* Recursive loop 78 */
			/* Pre code */
			fYec45_idx = (fYec45_idx + fYec45_idx_save) & 127;
			for (int j200 = 0; j200 < 4; j200 = j200 + 1) {
				fRec91_tmp[j200] = fRec91_perm[j200];
			}
			for (int j202 = 0; j202 < 4; j202 = j202 + 1) {
				fRec90_tmp[j202] = fRec90_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec45[(i + fYec45_idx) & 127] = fSlow2 * fRec90[i - 1] + fZec27[i];
				fRec91[i] = fSlow156 * fYec45[(i + fYec45_idx - iSlow157) & 127] - (fSlow158 * fRec91[i - 1] + fConst6 * fRec91[i - 2]);
				fRec90[i] = fConst7 * (fRec91[i] - fRec91[i - 2]);
			}
			/* Post code */
			fYec45_idx_save = vsize;
			for (int j201 = 0; j201 < 4; j201 = j201 + 1) {
				fRec91_perm[j201] = fRec91_tmp[vsize + j201];
			}
			for (int j203 = 0; j203 < 4; j203 = j203 + 1) {
				fRec90_perm[j203] = fRec90_tmp[vsize + j203];
			}
			/* Recursive loop 79 */
			/* Pre code */
			fYec46_idx = (fYec46_idx + fYec46_idx_save) & 511;
			for (int j204 = 0; j204 < 4; j204 = j204 + 1) {
				fRec93_tmp[j204] = fRec93_perm[j204];
			}
			for (int j206 = 0; j206 < 4; j206 = j206 + 1) {
				fRec92_tmp[j206] = fRec92_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec46[(i + fYec46_idx) & 511] = fZec28[i] + fSlow2 * fRec92[i - 1];
				fRec93[i] = fSlow159 * fYec46[(i + fYec46_idx - iSlow160) & 511] - (fSlow161 * fRec93[i - 1] + fConst6 * fRec93[i - 2]);
				fRec92[i] = fConst7 * (fRec93[i] - fRec93[i - 2]);
			}
			/* Post code */
			fYec46_idx_save = vsize;
			for (int j205 = 0; j205 < 4; j205 = j205 + 1) {
				fRec93_perm[j205] = fRec93_tmp[vsize + j205];
			}
			for (int j207 = 0; j207 < 4; j207 = j207 + 1) {
				fRec92_perm[j207] = fRec92_tmp[vsize + j207];
			}
			/* Recursive loop 80 */
			/* Pre code */
			fYec47_idx = (fYec47_idx + fYec47_idx_save) & 511;
			for (int j208 = 0; j208 < 4; j208 = j208 + 1) {
				fRec95_tmp[j208] = fRec95_perm[j208];
			}
			for (int j210 = 0; j210 < 4; j210 = j210 + 1) {
				fRec94_tmp[j210] = fRec94_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec47[(i + fYec47_idx) & 511] = fSlow2 * fRec94[i - 1] + fZec28[i];
				fRec95[i] = fSlow162 * fYec47[(i + fYec47_idx - iSlow163) & 511] - (fSlow164 * fRec95[i - 1] + fConst6 * fRec95[i - 2]);
				fRec94[i] = fConst7 * (fRec95[i] - fRec95[i - 2]);
			}
			/* Post code */
			fYec47_idx_save = vsize;
			for (int j209 = 0; j209 < 4; j209 = j209 + 1) {
				fRec95_perm[j209] = fRec95_tmp[vsize + j209];
			}
			for (int j211 = 0; j211 < 4; j211 = j211 + 1) {
				fRec94_perm[j211] = fRec94_tmp[vsize + j211];
			}
			/* Recursive loop 81 */
			/* Pre code */
			fYec48_idx = (fYec48_idx + fYec48_idx_save) & 1023;
			for (int j212 = 0; j212 < 4; j212 = j212 + 1) {
				fRec97_tmp[j212] = fRec97_perm[j212];
			}
			for (int j214 = 0; j214 < 4; j214 = j214 + 1) {
				fRec96_tmp[j214] = fRec96_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec48[(i + fYec48_idx) & 1023] = fZec29[i] + fSlow2 * fRec96[i - 1];
				fRec97[i] = fSlow165 * fYec48[(i + fYec48_idx - iSlow166) & 1023] - (fSlow167 * fRec97[i - 1] + fConst6 * fRec97[i - 2]);
				fRec96[i] = fConst7 * (fRec97[i] - fRec97[i - 2]);
			}
			/* Post code */
			fYec48_idx_save = vsize;
			for (int j213 = 0; j213 < 4; j213 = j213 + 1) {
				fRec97_perm[j213] = fRec97_tmp[vsize + j213];
			}
			for (int j215 = 0; j215 < 4; j215 = j215 + 1) {
				fRec96_perm[j215] = fRec96_tmp[vsize + j215];
			}
			/* Recursive loop 82 */
			/* Pre code */
			fYec49_idx = (fYec49_idx + fYec49_idx_save) & 1023;
			for (int j216 = 0; j216 < 4; j216 = j216 + 1) {
				fRec99_tmp[j216] = fRec99_perm[j216];
			}
			for (int j218 = 0; j218 < 4; j218 = j218 + 1) {
				fRec98_tmp[j218] = fRec98_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec49[(i + fYec49_idx) & 1023] = fSlow2 * fRec98[i - 1] + fZec29[i];
				fRec99[i] = fSlow168 * fYec49[(i + fYec49_idx - iSlow169) & 1023] - (fSlow170 * fRec99[i - 1] + fConst6 * fRec99[i - 2]);
				fRec98[i] = fConst7 * (fRec99[i] - fRec99[i - 2]);
			}
			/* Post code */
			fYec49_idx_save = vsize;
			for (int j217 = 0; j217 < 4; j217 = j217 + 1) {
				fRec99_perm[j217] = fRec99_tmp[vsize + j217];
			}
			for (int j219 = 0; j219 < 4; j219 = j219 + 1) {
				fRec98_perm[j219] = fRec98_tmp[vsize + j219];
			}
			/* Recursive loop 83 */
			/* Pre code */
			fYec50_idx = (fYec50_idx + fYec50_idx_save) & 127;
			for (int j220 = 0; j220 < 4; j220 = j220 + 1) {
				fRec101_tmp[j220] = fRec101_perm[j220];
			}
			for (int j222 = 0; j222 < 4; j222 = j222 + 1) {
				fRec100_tmp[j222] = fRec100_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec50[(i + fYec50_idx) & 127] = fZec30[i] + fSlow2 * fRec100[i - 1];
				fRec101[i] = fSlow171 * fYec50[(i + fYec50_idx - iSlow172) & 127] - (fSlow173 * fRec101[i - 1] + fConst6 * fRec101[i - 2]);
				fRec100[i] = fConst7 * (fRec101[i] - fRec101[i - 2]);
			}
			/* Post code */
			fYec50_idx_save = vsize;
			for (int j221 = 0; j221 < 4; j221 = j221 + 1) {
				fRec101_perm[j221] = fRec101_tmp[vsize + j221];
			}
			for (int j223 = 0; j223 < 4; j223 = j223 + 1) {
				fRec100_perm[j223] = fRec100_tmp[vsize + j223];
			}
			/* Recursive loop 84 */
			/* Pre code */
			fYec51_idx = (fYec51_idx + fYec51_idx_save) & 127;
			for (int j224 = 0; j224 < 4; j224 = j224 + 1) {
				fRec103_tmp[j224] = fRec103_perm[j224];
			}
			for (int j226 = 0; j226 < 4; j226 = j226 + 1) {
				fRec102_tmp[j226] = fRec102_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec51[(i + fYec51_idx) & 127] = fSlow2 * fRec102[i - 1] + fZec30[i];
				fRec103[i] = fSlow174 * fYec51[(i + fYec51_idx - iSlow175) & 127] - (fSlow176 * fRec103[i - 1] + fConst6 * fRec103[i - 2]);
				fRec102[i] = fConst7 * (fRec103[i] - fRec103[i - 2]);
			}
			/* Post code */
			fYec51_idx_save = vsize;
			for (int j225 = 0; j225 < 4; j225 = j225 + 1) {
				fRec103_perm[j225] = fRec103_tmp[vsize + j225];
			}
			for (int j227 = 0; j227 < 4; j227 = j227 + 1) {
				fRec102_perm[j227] = fRec102_tmp[vsize + j227];
			}
			/* Recursive loop 85 */
			/* Pre code */
			fYec52_idx = (fYec52_idx + fYec52_idx_save) & 127;
			for (int j228 = 0; j228 < 4; j228 = j228 + 1) {
				fRec105_tmp[j228] = fRec105_perm[j228];
			}
			for (int j230 = 0; j230 < 4; j230 = j230 + 1) {
				fRec104_tmp[j230] = fRec104_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec52[(i + fYec52_idx) & 127] = fZec31[i] + fSlow2 * fRec104[i - 1];
				fRec105[i] = fSlow177 * fYec52[(i + fYec52_idx - iSlow178) & 127] - (fSlow179 * fRec105[i - 1] + fConst6 * fRec105[i - 2]);
				fRec104[i] = fConst7 * (fRec105[i] - fRec105[i - 2]);
			}
			/* Post code */
			fYec52_idx_save = vsize;
			for (int j229 = 0; j229 < 4; j229 = j229 + 1) {
				fRec105_perm[j229] = fRec105_tmp[vsize + j229];
			}
			for (int j231 = 0; j231 < 4; j231 = j231 + 1) {
				fRec104_perm[j231] = fRec104_tmp[vsize + j231];
			}
			/* Recursive loop 86 */
			/* Pre code */
			fYec53_idx = (fYec53_idx + fYec53_idx_save) & 127;
			for (int j232 = 0; j232 < 4; j232 = j232 + 1) {
				fRec107_tmp[j232] = fRec107_perm[j232];
			}
			for (int j234 = 0; j234 < 4; j234 = j234 + 1) {
				fRec106_tmp[j234] = fRec106_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec53[(i + fYec53_idx) & 127] = fSlow2 * fRec106[i - 1] + fZec31[i];
				fRec107[i] = fSlow180 * fYec53[(i + fYec53_idx - iSlow181) & 127] - (fSlow182 * fRec107[i - 1] + fConst6 * fRec107[i - 2]);
				fRec106[i] = fConst7 * (fRec107[i] - fRec107[i - 2]);
			}
			/* Post code */
			fYec53_idx_save = vsize;
			for (int j233 = 0; j233 < 4; j233 = j233 + 1) {
				fRec107_perm[j233] = fRec107_tmp[vsize + j233];
			}
			for (int j235 = 0; j235 < 4; j235 = j235 + 1) {
				fRec106_perm[j235] = fRec106_tmp[vsize + j235];
			}
			/* Recursive loop 87 */
			/* Pre code */
			fYec54_idx = (fYec54_idx + fYec54_idx_save) & 127;
			for (int j236 = 0; j236 < 4; j236 = j236 + 1) {
				fRec109_tmp[j236] = fRec109_perm[j236];
			}
			for (int j238 = 0; j238 < 4; j238 = j238 + 1) {
				fRec108_tmp[j238] = fRec108_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec54[(i + fYec54_idx) & 127] = fZec32[i] + fSlow2 * fRec108[i - 1];
				fRec109[i] = fSlow183 * fYec54[(i + fYec54_idx - iSlow184) & 127] - (fSlow185 * fRec109[i - 1] + fConst6 * fRec109[i - 2]);
				fRec108[i] = fConst7 * (fRec109[i] - fRec109[i - 2]);
			}
			/* Post code */
			fYec54_idx_save = vsize;
			for (int j237 = 0; j237 < 4; j237 = j237 + 1) {
				fRec109_perm[j237] = fRec109_tmp[vsize + j237];
			}
			for (int j239 = 0; j239 < 4; j239 = j239 + 1) {
				fRec108_perm[j239] = fRec108_tmp[vsize + j239];
			}
			/* Recursive loop 88 */
			/* Pre code */
			fYec55_idx = (fYec55_idx + fYec55_idx_save) & 127;
			for (int j240 = 0; j240 < 4; j240 = j240 + 1) {
				fRec111_tmp[j240] = fRec111_perm[j240];
			}
			for (int j242 = 0; j242 < 4; j242 = j242 + 1) {
				fRec110_tmp[j242] = fRec110_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec55[(i + fYec55_idx) & 127] = fSlow2 * fRec110[i - 1] + fZec32[i];
				fRec111[i] = fSlow186 * fYec55[(i + fYec55_idx - iSlow187) & 127] - (fSlow188 * fRec111[i - 1] + fConst6 * fRec111[i - 2]);
				fRec110[i] = fConst7 * (fRec111[i] - fRec111[i - 2]);
			}
			/* Post code */
			fYec55_idx_save = vsize;
			for (int j241 = 0; j241 < 4; j241 = j241 + 1) {
				fRec111_perm[j241] = fRec111_tmp[vsize + j241];
			}
			for (int j243 = 0; j243 < 4; j243 = j243 + 1) {
				fRec110_perm[j243] = fRec110_tmp[vsize + j243];
			}
			/* Recursive loop 89 */
			/* Pre code */
			fYec56_idx = (fYec56_idx + fYec56_idx_save) & 511;
			for (int j244 = 0; j244 < 4; j244 = j244 + 1) {
				fRec113_tmp[j244] = fRec113_perm[j244];
			}
			for (int j246 = 0; j246 < 4; j246 = j246 + 1) {
				fRec112_tmp[j246] = fRec112_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec56[(i + fYec56_idx) & 511] = fZec33[i] + fSlow2 * fRec112[i - 1];
				fRec113[i] = fSlow189 * fYec56[(i + fYec56_idx - iSlow190) & 511] - (fSlow191 * fRec113[i - 1] + fConst6 * fRec113[i - 2]);
				fRec112[i] = fConst7 * (fRec113[i] - fRec113[i - 2]);
			}
			/* Post code */
			fYec56_idx_save = vsize;
			for (int j245 = 0; j245 < 4; j245 = j245 + 1) {
				fRec113_perm[j245] = fRec113_tmp[vsize + j245];
			}
			for (int j247 = 0; j247 < 4; j247 = j247 + 1) {
				fRec112_perm[j247] = fRec112_tmp[vsize + j247];
			}
			/* Recursive loop 90 */
			/* Pre code */
			fYec57_idx = (fYec57_idx + fYec57_idx_save) & 511;
			for (int j248 = 0; j248 < 4; j248 = j248 + 1) {
				fRec115_tmp[j248] = fRec115_perm[j248];
			}
			for (int j250 = 0; j250 < 4; j250 = j250 + 1) {
				fRec114_tmp[j250] = fRec114_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec57[(i + fYec57_idx) & 511] = fSlow2 * fRec114[i - 1] + fZec33[i];
				fRec115[i] = fSlow192 * fYec57[(i + fYec57_idx - iSlow193) & 511] - (fSlow194 * fRec115[i - 1] + fConst6 * fRec115[i - 2]);
				fRec114[i] = fConst7 * (fRec115[i] - fRec115[i - 2]);
			}
			/* Post code */
			fYec57_idx_save = vsize;
			for (int j249 = 0; j249 < 4; j249 = j249 + 1) {
				fRec115_perm[j249] = fRec115_tmp[vsize + j249];
			}
			for (int j251 = 0; j251 < 4; j251 = j251 + 1) {
				fRec114_perm[j251] = fRec114_tmp[vsize + j251];
			}
			/* Recursive loop 91 */
			/* Pre code */
			fYec58_idx = (fYec58_idx + fYec58_idx_save) & 1023;
			for (int j252 = 0; j252 < 4; j252 = j252 + 1) {
				fRec117_tmp[j252] = fRec117_perm[j252];
			}
			for (int j254 = 0; j254 < 4; j254 = j254 + 1) {
				fRec116_tmp[j254] = fRec116_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec58[(i + fYec58_idx) & 1023] = fZec34[i] + fSlow2 * fRec116[i - 1];
				fRec117[i] = fSlow195 * fYec58[(i + fYec58_idx - iSlow196) & 1023] - (fSlow197 * fRec117[i - 1] + fConst6 * fRec117[i - 2]);
				fRec116[i] = fConst7 * (fRec117[i] - fRec117[i - 2]);
			}
			/* Post code */
			fYec58_idx_save = vsize;
			for (int j253 = 0; j253 < 4; j253 = j253 + 1) {
				fRec117_perm[j253] = fRec117_tmp[vsize + j253];
			}
			for (int j255 = 0; j255 < 4; j255 = j255 + 1) {
				fRec116_perm[j255] = fRec116_tmp[vsize + j255];
			}
			/* Recursive loop 92 */
			/* Pre code */
			fYec59_idx = (fYec59_idx + fYec59_idx_save) & 1023;
			for (int j256 = 0; j256 < 4; j256 = j256 + 1) {
				fRec119_tmp[j256] = fRec119_perm[j256];
			}
			for (int j258 = 0; j258 < 4; j258 = j258 + 1) {
				fRec118_tmp[j258] = fRec118_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec59[(i + fYec59_idx) & 1023] = fSlow2 * fRec118[i - 1] + fZec34[i];
				fRec119[i] = fSlow198 * fYec59[(i + fYec59_idx - iSlow199) & 1023] - (fSlow200 * fRec119[i - 1] + fConst6 * fRec119[i - 2]);
				fRec118[i] = fConst7 * (fRec119[i] - fRec119[i - 2]);
			}
			/* Post code */
			fYec59_idx_save = vsize;
			for (int j257 = 0; j257 < 4; j257 = j257 + 1) {
				fRec119_perm[j257] = fRec119_tmp[vsize + j257];
			}
			for (int j259 = 0; j259 < 4; j259 = j259 + 1) {
				fRec118_perm[j259] = fRec118_tmp[vsize + j259];
			}
			/* Recursive loop 93 */
			/* Pre code */
			fYec60_idx = (fYec60_idx + fYec60_idx_save) & 127;
			for (int j260 = 0; j260 < 4; j260 = j260 + 1) {
				fRec121_tmp[j260] = fRec121_perm[j260];
			}
			for (int j262 = 0; j262 < 4; j262 = j262 + 1) {
				fRec120_tmp[j262] = fRec120_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec60[(i + fYec60_idx) & 127] = fZec35[i] + fSlow2 * fRec120[i - 1];
				fRec121[i] = fSlow201 * fYec60[(i + fYec60_idx - iSlow202) & 127] - (fSlow203 * fRec121[i - 1] + fConst6 * fRec121[i - 2]);
				fRec120[i] = fConst7 * (fRec121[i] - fRec121[i - 2]);
			}
			/* Post code */
			fYec60_idx_save = vsize;
			for (int j261 = 0; j261 < 4; j261 = j261 + 1) {
				fRec121_perm[j261] = fRec121_tmp[vsize + j261];
			}
			for (int j263 = 0; j263 < 4; j263 = j263 + 1) {
				fRec120_perm[j263] = fRec120_tmp[vsize + j263];
			}
			/* Recursive loop 94 */
			/* Pre code */
			fYec61_idx = (fYec61_idx + fYec61_idx_save) & 127;
			for (int j264 = 0; j264 < 4; j264 = j264 + 1) {
				fRec123_tmp[j264] = fRec123_perm[j264];
			}
			for (int j266 = 0; j266 < 4; j266 = j266 + 1) {
				fRec122_tmp[j266] = fRec122_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec61[(i + fYec61_idx) & 127] = fSlow2 * fRec122[i - 1] + fZec35[i];
				fRec123[i] = fSlow204 * fYec61[(i + fYec61_idx - iSlow205) & 127] - (fSlow206 * fRec123[i - 1] + fConst6 * fRec123[i - 2]);
				fRec122[i] = fConst7 * (fRec123[i] - fRec123[i - 2]);
			}
			/* Post code */
			fYec61_idx_save = vsize;
			for (int j265 = 0; j265 < 4; j265 = j265 + 1) {
				fRec123_perm[j265] = fRec123_tmp[vsize + j265];
			}
			for (int j267 = 0; j267 < 4; j267 = j267 + 1) {
				fRec122_perm[j267] = fRec122_tmp[vsize + j267];
			}
			/* Recursive loop 95 */
			/* Pre code */
			fYec62_idx = (fYec62_idx + fYec62_idx_save) & 127;
			for (int j268 = 0; j268 < 4; j268 = j268 + 1) {
				fRec125_tmp[j268] = fRec125_perm[j268];
			}
			for (int j270 = 0; j270 < 4; j270 = j270 + 1) {
				fRec124_tmp[j270] = fRec124_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec62[(i + fYec62_idx) & 127] = fZec36[i] + fSlow2 * fRec124[i - 1];
				fRec125[i] = fSlow207 * fYec62[(i + fYec62_idx - iSlow208) & 127] - (fSlow209 * fRec125[i - 1] + fConst6 * fRec125[i - 2]);
				fRec124[i] = fConst7 * (fRec125[i] - fRec125[i - 2]);
			}
			/* Post code */
			fYec62_idx_save = vsize;
			for (int j269 = 0; j269 < 4; j269 = j269 + 1) {
				fRec125_perm[j269] = fRec125_tmp[vsize + j269];
			}
			for (int j271 = 0; j271 < 4; j271 = j271 + 1) {
				fRec124_perm[j271] = fRec124_tmp[vsize + j271];
			}
			/* Recursive loop 96 */
			/* Pre code */
			fYec63_idx = (fYec63_idx + fYec63_idx_save) & 127;
			for (int j272 = 0; j272 < 4; j272 = j272 + 1) {
				fRec127_tmp[j272] = fRec127_perm[j272];
			}
			for (int j274 = 0; j274 < 4; j274 = j274 + 1) {
				fRec126_tmp[j274] = fRec126_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec63[(i + fYec63_idx) & 127] = fSlow2 * fRec126[i - 1] + fZec36[i];
				fRec127[i] = fSlow210 * fYec63[(i + fYec63_idx - iSlow211) & 127] - (fSlow212 * fRec127[i - 1] + fConst6 * fRec127[i - 2]);
				fRec126[i] = fConst7 * (fRec127[i] - fRec127[i - 2]);
			}
			/* Post code */
			fYec63_idx_save = vsize;
			for (int j273 = 0; j273 < 4; j273 = j273 + 1) {
				fRec127_perm[j273] = fRec127_tmp[vsize + j273];
			}
			for (int j275 = 0; j275 < 4; j275 = j275 + 1) {
				fRec126_perm[j275] = fRec126_tmp[vsize + j275];
			}
			/* Recursive loop 97 */
			/* Pre code */
			fYec64_idx = (fYec64_idx + fYec64_idx_save) & 127;
			for (int j276 = 0; j276 < 4; j276 = j276 + 1) {
				fRec129_tmp[j276] = fRec129_perm[j276];
			}
			for (int j278 = 0; j278 < 4; j278 = j278 + 1) {
				fRec128_tmp[j278] = fRec128_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec64[(i + fYec64_idx) & 127] = fZec37[i] + fSlow2 * fRec128[i - 1];
				fRec129[i] = fSlow213 * fYec64[(i + fYec64_idx - iSlow214) & 127] - (fSlow215 * fRec129[i - 1] + fConst6 * fRec129[i - 2]);
				fRec128[i] = fConst7 * (fRec129[i] - fRec129[i - 2]);
			}
			/* Post code */
			fYec64_idx_save = vsize;
			for (int j277 = 0; j277 < 4; j277 = j277 + 1) {
				fRec129_perm[j277] = fRec129_tmp[vsize + j277];
			}
			for (int j279 = 0; j279 < 4; j279 = j279 + 1) {
				fRec128_perm[j279] = fRec128_tmp[vsize + j279];
			}
			/* Recursive loop 98 */
			/* Pre code */
			fYec65_idx = (fYec65_idx + fYec65_idx_save) & 127;
			for (int j280 = 0; j280 < 4; j280 = j280 + 1) {
				fRec131_tmp[j280] = fRec131_perm[j280];
			}
			for (int j282 = 0; j282 < 4; j282 = j282 + 1) {
				fRec130_tmp[j282] = fRec130_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec65[(i + fYec65_idx) & 127] = fSlow2 * fRec130[i - 1] + fZec37[i];
				fRec131[i] = fSlow216 * fYec65[(i + fYec65_idx - iSlow217) & 127] - (fSlow218 * fRec131[i - 1] + fConst6 * fRec131[i - 2]);
				fRec130[i] = fConst7 * (fRec131[i] - fRec131[i - 2]);
			}
			/* Post code */
			fYec65_idx_save = vsize;
			for (int j281 = 0; j281 < 4; j281 = j281 + 1) {
				fRec131_perm[j281] = fRec131_tmp[vsize + j281];
			}
			for (int j283 = 0; j283 < 4; j283 = j283 + 1) {
				fRec130_perm[j283] = fRec130_tmp[vsize + j283];
			}
			/* Recursive loop 99 */
			/* Pre code */
			fYec66_idx = (fYec66_idx + fYec66_idx_save) & 511;
			for (int j284 = 0; j284 < 4; j284 = j284 + 1) {
				fRec133_tmp[j284] = fRec133_perm[j284];
			}
			for (int j286 = 0; j286 < 4; j286 = j286 + 1) {
				fRec132_tmp[j286] = fRec132_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec66[(i + fYec66_idx) & 511] = fZec38[i] + fSlow2 * fRec132[i - 1];
				fRec133[i] = fSlow219 * fYec66[(i + fYec66_idx - iSlow220) & 511] - (fSlow221 * fRec133[i - 1] + fConst6 * fRec133[i - 2]);
				fRec132[i] = fConst7 * (fRec133[i] - fRec133[i - 2]);
			}
			/* Post code */
			fYec66_idx_save = vsize;
			for (int j285 = 0; j285 < 4; j285 = j285 + 1) {
				fRec133_perm[j285] = fRec133_tmp[vsize + j285];
			}
			for (int j287 = 0; j287 < 4; j287 = j287 + 1) {
				fRec132_perm[j287] = fRec132_tmp[vsize + j287];
			}
			/* Recursive loop 100 */
			/* Pre code */
			fYec67_idx = (fYec67_idx + fYec67_idx_save) & 511;
			for (int j288 = 0; j288 < 4; j288 = j288 + 1) {
				fRec135_tmp[j288] = fRec135_perm[j288];
			}
			for (int j290 = 0; j290 < 4; j290 = j290 + 1) {
				fRec134_tmp[j290] = fRec134_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec67[(i + fYec67_idx) & 511] = fSlow2 * fRec134[i - 1] + fZec38[i];
				fRec135[i] = fSlow222 * fYec67[(i + fYec67_idx - iSlow223) & 511] - (fSlow224 * fRec135[i - 1] + fConst6 * fRec135[i - 2]);
				fRec134[i] = fConst7 * (fRec135[i] - fRec135[i - 2]);
			}
			/* Post code */
			fYec67_idx_save = vsize;
			for (int j289 = 0; j289 < 4; j289 = j289 + 1) {
				fRec135_perm[j289] = fRec135_tmp[vsize + j289];
			}
			for (int j291 = 0; j291 < 4; j291 = j291 + 1) {
				fRec134_perm[j291] = fRec134_tmp[vsize + j291];
			}
			/* Recursive loop 101 */
			/* Pre code */
			fYec68_idx = (fYec68_idx + fYec68_idx_save) & 1023;
			for (int j292 = 0; j292 < 4; j292 = j292 + 1) {
				fRec137_tmp[j292] = fRec137_perm[j292];
			}
			for (int j294 = 0; j294 < 4; j294 = j294 + 1) {
				fRec136_tmp[j294] = fRec136_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec68[(i + fYec68_idx) & 1023] = fZec39[i] + fSlow2 * fRec136[i - 1];
				fRec137[i] = fSlow225 * fYec68[(i + fYec68_idx - iSlow226) & 1023] - (fSlow227 * fRec137[i - 1] + fConst6 * fRec137[i - 2]);
				fRec136[i] = fConst7 * (fRec137[i] - fRec137[i - 2]);
			}
			/* Post code */
			fYec68_idx_save = vsize;
			for (int j293 = 0; j293 < 4; j293 = j293 + 1) {
				fRec137_perm[j293] = fRec137_tmp[vsize + j293];
			}
			for (int j295 = 0; j295 < 4; j295 = j295 + 1) {
				fRec136_perm[j295] = fRec136_tmp[vsize + j295];
			}
			/* Recursive loop 102 */
			/* Pre code */
			fYec69_idx = (fYec69_idx + fYec69_idx_save) & 1023;
			for (int j296 = 0; j296 < 4; j296 = j296 + 1) {
				fRec139_tmp[j296] = fRec139_perm[j296];
			}
			for (int j298 = 0; j298 < 4; j298 = j298 + 1) {
				fRec138_tmp[j298] = fRec138_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec69[(i + fYec69_idx) & 1023] = fSlow2 * fRec138[i - 1] + fZec39[i];
				fRec139[i] = fSlow228 * fYec69[(i + fYec69_idx - iSlow229) & 1023] - (fSlow230 * fRec139[i - 1] + fConst6 * fRec139[i - 2]);
				fRec138[i] = fConst7 * (fRec139[i] - fRec139[i - 2]);
			}
			/* Post code */
			fYec69_idx_save = vsize;
			for (int j297 = 0; j297 < 4; j297 = j297 + 1) {
				fRec139_perm[j297] = fRec139_tmp[vsize + j297];
			}
			for (int j299 = 0; j299 < 4; j299 = j299 + 1) {
				fRec138_perm[j299] = fRec138_tmp[vsize + j299];
			}
			/* Recursive loop 103 */
			/* Pre code */
			fYec70_idx = (fYec70_idx + fYec70_idx_save) & 127;
			for (int j300 = 0; j300 < 4; j300 = j300 + 1) {
				fRec141_tmp[j300] = fRec141_perm[j300];
			}
			for (int j302 = 0; j302 < 4; j302 = j302 + 1) {
				fRec140_tmp[j302] = fRec140_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec70[(i + fYec70_idx) & 127] = fZec40[i] + fSlow2 * fRec140[i - 1];
				fRec141[i] = fSlow231 * fYec70[(i + fYec70_idx - iSlow232) & 127] - (fSlow233 * fRec141[i - 1] + fConst6 * fRec141[i - 2]);
				fRec140[i] = fConst7 * (fRec141[i] - fRec141[i - 2]);
			}
			/* Post code */
			fYec70_idx_save = vsize;
			for (int j301 = 0; j301 < 4; j301 = j301 + 1) {
				fRec141_perm[j301] = fRec141_tmp[vsize + j301];
			}
			for (int j303 = 0; j303 < 4; j303 = j303 + 1) {
				fRec140_perm[j303] = fRec140_tmp[vsize + j303];
			}
			/* Recursive loop 104 */
			/* Pre code */
			fYec71_idx = (fYec71_idx + fYec71_idx_save) & 127;
			for (int j304 = 0; j304 < 4; j304 = j304 + 1) {
				fRec143_tmp[j304] = fRec143_perm[j304];
			}
			for (int j306 = 0; j306 < 4; j306 = j306 + 1) {
				fRec142_tmp[j306] = fRec142_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec71[(i + fYec71_idx) & 127] = fSlow2 * fRec142[i - 1] + fZec40[i];
				fRec143[i] = fSlow234 * fYec71[(i + fYec71_idx - iSlow235) & 127] - (fSlow236 * fRec143[i - 1] + fConst6 * fRec143[i - 2]);
				fRec142[i] = fConst7 * (fRec143[i] - fRec143[i - 2]);
			}
			/* Post code */
			fYec71_idx_save = vsize;
			for (int j305 = 0; j305 < 4; j305 = j305 + 1) {
				fRec143_perm[j305] = fRec143_tmp[vsize + j305];
			}
			for (int j307 = 0; j307 < 4; j307 = j307 + 1) {
				fRec142_perm[j307] = fRec142_tmp[vsize + j307];
			}
			/* Recursive loop 105 */
			/* Pre code */
			fYec72_idx = (fYec72_idx + fYec72_idx_save) & 127;
			for (int j308 = 0; j308 < 4; j308 = j308 + 1) {
				fRec145_tmp[j308] = fRec145_perm[j308];
			}
			for (int j310 = 0; j310 < 4; j310 = j310 + 1) {
				fRec144_tmp[j310] = fRec144_perm[j310];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec72[(i + fYec72_idx) & 127] = fZec41[i] + fSlow2 * fRec144[i - 1];
				fRec145[i] = fSlow237 * fYec72[(i + fYec72_idx - iSlow238) & 127] - (fSlow239 * fRec145[i - 1] + fConst6 * fRec145[i - 2]);
				fRec144[i] = fConst7 * (fRec145[i] - fRec145[i - 2]);
			}
			/* Post code */
			fYec72_idx_save = vsize;
			for (int j309 = 0; j309 < 4; j309 = j309 + 1) {
				fRec145_perm[j309] = fRec145_tmp[vsize + j309];
			}
			for (int j311 = 0; j311 < 4; j311 = j311 + 1) {
				fRec144_perm[j311] = fRec144_tmp[vsize + j311];
			}
			/* Recursive loop 106 */
			/* Pre code */
			fYec73_idx = (fYec73_idx + fYec73_idx_save) & 127;
			for (int j312 = 0; j312 < 4; j312 = j312 + 1) {
				fRec147_tmp[j312] = fRec147_perm[j312];
			}
			for (int j314 = 0; j314 < 4; j314 = j314 + 1) {
				fRec146_tmp[j314] = fRec146_perm[j314];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec73[(i + fYec73_idx) & 127] = fSlow2 * fRec146[i - 1] + fZec41[i];
				fRec147[i] = fSlow240 * fYec73[(i + fYec73_idx - iSlow241) & 127] - (fSlow242 * fRec147[i - 1] + fConst6 * fRec147[i - 2]);
				fRec146[i] = fConst7 * (fRec147[i] - fRec147[i - 2]);
			}
			/* Post code */
			fYec73_idx_save = vsize;
			for (int j313 = 0; j313 < 4; j313 = j313 + 1) {
				fRec147_perm[j313] = fRec147_tmp[vsize + j313];
			}
			for (int j315 = 0; j315 < 4; j315 = j315 + 1) {
				fRec146_perm[j315] = fRec146_tmp[vsize + j315];
			}
			/* Recursive loop 107 */
			/* Pre code */
			fYec74_idx = (fYec74_idx + fYec74_idx_save) & 127;
			for (int j316 = 0; j316 < 4; j316 = j316 + 1) {
				fRec149_tmp[j316] = fRec149_perm[j316];
			}
			for (int j318 = 0; j318 < 4; j318 = j318 + 1) {
				fRec148_tmp[j318] = fRec148_perm[j318];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec74[(i + fYec74_idx) & 127] = fZec42[i] + fSlow2 * fRec148[i - 1];
				fRec149[i] = fSlow243 * fYec74[(i + fYec74_idx - iSlow244) & 127] - (fSlow245 * fRec149[i - 1] + fConst6 * fRec149[i - 2]);
				fRec148[i] = fConst7 * (fRec149[i] - fRec149[i - 2]);
			}
			/* Post code */
			fYec74_idx_save = vsize;
			for (int j317 = 0; j317 < 4; j317 = j317 + 1) {
				fRec149_perm[j317] = fRec149_tmp[vsize + j317];
			}
			for (int j319 = 0; j319 < 4; j319 = j319 + 1) {
				fRec148_perm[j319] = fRec148_tmp[vsize + j319];
			}
			/* Recursive loop 108 */
			/* Pre code */
			fYec75_idx = (fYec75_idx + fYec75_idx_save) & 127;
			for (int j320 = 0; j320 < 4; j320 = j320 + 1) {
				fRec151_tmp[j320] = fRec151_perm[j320];
			}
			for (int j322 = 0; j322 < 4; j322 = j322 + 1) {
				fRec150_tmp[j322] = fRec150_perm[j322];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec75[(i + fYec75_idx) & 127] = fSlow2 * fRec150[i - 1] + fZec42[i];
				fRec151[i] = fSlow246 * fYec75[(i + fYec75_idx - iSlow247) & 127] - (fSlow248 * fRec151[i - 1] + fConst6 * fRec151[i - 2]);
				fRec150[i] = fConst7 * (fRec151[i] - fRec151[i - 2]);
			}
			/* Post code */
			fYec75_idx_save = vsize;
			for (int j321 = 0; j321 < 4; j321 = j321 + 1) {
				fRec151_perm[j321] = fRec151_tmp[vsize + j321];
			}
			for (int j323 = 0; j323 < 4; j323 = j323 + 1) {
				fRec150_perm[j323] = fRec150_tmp[vsize + j323];
			}
			/* Recursive loop 109 */
			/* Pre code */
			fYec76_idx = (fYec76_idx + fYec76_idx_save) & 511;
			for (int j324 = 0; j324 < 4; j324 = j324 + 1) {
				fRec153_tmp[j324] = fRec153_perm[j324];
			}
			for (int j326 = 0; j326 < 4; j326 = j326 + 1) {
				fRec152_tmp[j326] = fRec152_perm[j326];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec76[(i + fYec76_idx) & 511] = fZec43[i] + fSlow2 * fRec152[i - 1];
				fRec153[i] = fSlow249 * fYec76[(i + fYec76_idx - iSlow250) & 511] - (fSlow251 * fRec153[i - 1] + fConst6 * fRec153[i - 2]);
				fRec152[i] = fConst7 * (fRec153[i] - fRec153[i - 2]);
			}
			/* Post code */
			fYec76_idx_save = vsize;
			for (int j325 = 0; j325 < 4; j325 = j325 + 1) {
				fRec153_perm[j325] = fRec153_tmp[vsize + j325];
			}
			for (int j327 = 0; j327 < 4; j327 = j327 + 1) {
				fRec152_perm[j327] = fRec152_tmp[vsize + j327];
			}
			/* Recursive loop 110 */
			/* Pre code */
			fYec77_idx = (fYec77_idx + fYec77_idx_save) & 511;
			for (int j328 = 0; j328 < 4; j328 = j328 + 1) {
				fRec155_tmp[j328] = fRec155_perm[j328];
			}
			for (int j330 = 0; j330 < 4; j330 = j330 + 1) {
				fRec154_tmp[j330] = fRec154_perm[j330];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec77[(i + fYec77_idx) & 511] = fSlow2 * fRec154[i - 1] + fZec43[i];
				fRec155[i] = fSlow252 * fYec77[(i + fYec77_idx - iSlow253) & 511] - (fSlow254 * fRec155[i - 1] + fConst6 * fRec155[i - 2]);
				fRec154[i] = fConst7 * (fRec155[i] - fRec155[i - 2]);
			}
			/* Post code */
			fYec77_idx_save = vsize;
			for (int j329 = 0; j329 < 4; j329 = j329 + 1) {
				fRec155_perm[j329] = fRec155_tmp[vsize + j329];
			}
			for (int j331 = 0; j331 < 4; j331 = j331 + 1) {
				fRec154_perm[j331] = fRec154_tmp[vsize + j331];
			}
			/* Recursive loop 111 */
			/* Pre code */
			fYec78_idx = (fYec78_idx + fYec78_idx_save) & 1023;
			for (int j332 = 0; j332 < 4; j332 = j332 + 1) {
				fRec157_tmp[j332] = fRec157_perm[j332];
			}
			for (int j334 = 0; j334 < 4; j334 = j334 + 1) {
				fRec156_tmp[j334] = fRec156_perm[j334];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec78[(i + fYec78_idx) & 1023] = fZec44[i] + fSlow2 * fRec156[i - 1];
				fRec157[i] = fSlow255 * fYec78[(i + fYec78_idx - iSlow256) & 1023] - (fSlow257 * fRec157[i - 1] + fConst6 * fRec157[i - 2]);
				fRec156[i] = fConst7 * (fRec157[i] - fRec157[i - 2]);
			}
			/* Post code */
			fYec78_idx_save = vsize;
			for (int j333 = 0; j333 < 4; j333 = j333 + 1) {
				fRec157_perm[j333] = fRec157_tmp[vsize + j333];
			}
			for (int j335 = 0; j335 < 4; j335 = j335 + 1) {
				fRec156_perm[j335] = fRec156_tmp[vsize + j335];
			}
			/* Recursive loop 112 */
			/* Pre code */
			fYec79_idx = (fYec79_idx + fYec79_idx_save) & 1023;
			for (int j336 = 0; j336 < 4; j336 = j336 + 1) {
				fRec159_tmp[j336] = fRec159_perm[j336];
			}
			for (int j338 = 0; j338 < 4; j338 = j338 + 1) {
				fRec158_tmp[j338] = fRec158_perm[j338];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec79[(i + fYec79_idx) & 1023] = fSlow2 * fRec158[i - 1] + fZec44[i];
				fRec159[i] = fSlow258 * fYec79[(i + fYec79_idx - iSlow259) & 1023] - (fSlow260 * fRec159[i - 1] + fConst6 * fRec159[i - 2]);
				fRec158[i] = fConst7 * (fRec159[i] - fRec159[i - 2]);
			}
			/* Post code */
			fYec79_idx_save = vsize;
			for (int j337 = 0; j337 < 4; j337 = j337 + 1) {
				fRec159_perm[j337] = fRec159_tmp[vsize + j337];
			}
			for (int j339 = 0; j339 < 4; j339 = j339 + 1) {
				fRec158_perm[j339] = fRec158_tmp[vsize + j339];
			}
			/* Recursive loop 113 */
			/* Pre code */
			fYec80_idx = (fYec80_idx + fYec80_idx_save) & 127;
			for (int j340 = 0; j340 < 4; j340 = j340 + 1) {
				fRec161_tmp[j340] = fRec161_perm[j340];
			}
			for (int j342 = 0; j342 < 4; j342 = j342 + 1) {
				fRec160_tmp[j342] = fRec160_perm[j342];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec80[(i + fYec80_idx) & 127] = fZec45[i] + fSlow2 * fRec160[i - 1];
				fRec161[i] = fSlow261 * fYec80[(i + fYec80_idx - iSlow262) & 127] - (fSlow263 * fRec161[i - 1] + fConst6 * fRec161[i - 2]);
				fRec160[i] = fConst7 * (fRec161[i] - fRec161[i - 2]);
			}
			/* Post code */
			fYec80_idx_save = vsize;
			for (int j341 = 0; j341 < 4; j341 = j341 + 1) {
				fRec161_perm[j341] = fRec161_tmp[vsize + j341];
			}
			for (int j343 = 0; j343 < 4; j343 = j343 + 1) {
				fRec160_perm[j343] = fRec160_tmp[vsize + j343];
			}
			/* Recursive loop 114 */
			/* Pre code */
			fYec81_idx = (fYec81_idx + fYec81_idx_save) & 127;
			for (int j344 = 0; j344 < 4; j344 = j344 + 1) {
				fRec163_tmp[j344] = fRec163_perm[j344];
			}
			for (int j346 = 0; j346 < 4; j346 = j346 + 1) {
				fRec162_tmp[j346] = fRec162_perm[j346];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec81[(i + fYec81_idx) & 127] = fSlow2 * fRec162[i - 1] + fZec45[i];
				fRec163[i] = fSlow264 * fYec81[(i + fYec81_idx - iSlow265) & 127] - (fSlow266 * fRec163[i - 1] + fConst6 * fRec163[i - 2]);
				fRec162[i] = fConst7 * (fRec163[i] - fRec163[i - 2]);
			}
			/* Post code */
			fYec81_idx_save = vsize;
			for (int j345 = 0; j345 < 4; j345 = j345 + 1) {
				fRec163_perm[j345] = fRec163_tmp[vsize + j345];
			}
			for (int j347 = 0; j347 < 4; j347 = j347 + 1) {
				fRec162_perm[j347] = fRec162_tmp[vsize + j347];
			}
			/* Recursive loop 115 */
			/* Pre code */
			fYec82_idx = (fYec82_idx + fYec82_idx_save) & 127;
			for (int j348 = 0; j348 < 4; j348 = j348 + 1) {
				fRec165_tmp[j348] = fRec165_perm[j348];
			}
			for (int j350 = 0; j350 < 4; j350 = j350 + 1) {
				fRec164_tmp[j350] = fRec164_perm[j350];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec82[(i + fYec82_idx) & 127] = fZec46[i] + fSlow2 * fRec164[i - 1];
				fRec165[i] = fSlow267 * fYec82[(i + fYec82_idx - iSlow268) & 127] - (fSlow269 * fRec165[i - 1] + fConst6 * fRec165[i - 2]);
				fRec164[i] = fConst7 * (fRec165[i] - fRec165[i - 2]);
			}
			/* Post code */
			fYec82_idx_save = vsize;
			for (int j349 = 0; j349 < 4; j349 = j349 + 1) {
				fRec165_perm[j349] = fRec165_tmp[vsize + j349];
			}
			for (int j351 = 0; j351 < 4; j351 = j351 + 1) {
				fRec164_perm[j351] = fRec164_tmp[vsize + j351];
			}
			/* Recursive loop 116 */
			/* Pre code */
			fYec83_idx = (fYec83_idx + fYec83_idx_save) & 127;
			for (int j352 = 0; j352 < 4; j352 = j352 + 1) {
				fRec167_tmp[j352] = fRec167_perm[j352];
			}
			for (int j354 = 0; j354 < 4; j354 = j354 + 1) {
				fRec166_tmp[j354] = fRec166_perm[j354];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec83[(i + fYec83_idx) & 127] = fSlow2 * fRec166[i - 1] + fZec46[i];
				fRec167[i] = fSlow270 * fYec83[(i + fYec83_idx - iSlow271) & 127] - (fSlow272 * fRec167[i - 1] + fConst6 * fRec167[i - 2]);
				fRec166[i] = fConst7 * (fRec167[i] - fRec167[i - 2]);
			}
			/* Post code */
			fYec83_idx_save = vsize;
			for (int j353 = 0; j353 < 4; j353 = j353 + 1) {
				fRec167_perm[j353] = fRec167_tmp[vsize + j353];
			}
			for (int j355 = 0; j355 < 4; j355 = j355 + 1) {
				fRec166_perm[j355] = fRec166_tmp[vsize + j355];
			}
			/* Recursive loop 117 */
			/* Pre code */
			fYec84_idx = (fYec84_idx + fYec84_idx_save) & 127;
			for (int j356 = 0; j356 < 4; j356 = j356 + 1) {
				fRec169_tmp[j356] = fRec169_perm[j356];
			}
			for (int j358 = 0; j358 < 4; j358 = j358 + 1) {
				fRec168_tmp[j358] = fRec168_perm[j358];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec84[(i + fYec84_idx) & 127] = fZec47[i] + fSlow2 * fRec168[i - 1];
				fRec169[i] = fSlow273 * fYec84[(i + fYec84_idx - iSlow274) & 127] - (fSlow275 * fRec169[i - 1] + fConst6 * fRec169[i - 2]);
				fRec168[i] = fConst7 * (fRec169[i] - fRec169[i - 2]);
			}
			/* Post code */
			fYec84_idx_save = vsize;
			for (int j357 = 0; j357 < 4; j357 = j357 + 1) {
				fRec169_perm[j357] = fRec169_tmp[vsize + j357];
			}
			for (int j359 = 0; j359 < 4; j359 = j359 + 1) {
				fRec168_perm[j359] = fRec168_tmp[vsize + j359];
			}
			/* Recursive loop 118 */
			/* Pre code */
			fYec85_idx = (fYec85_idx + fYec85_idx_save) & 127;
			for (int j360 = 0; j360 < 4; j360 = j360 + 1) {
				fRec171_tmp[j360] = fRec171_perm[j360];
			}
			for (int j362 = 0; j362 < 4; j362 = j362 + 1) {
				fRec170_tmp[j362] = fRec170_perm[j362];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec85[(i + fYec85_idx) & 127] = fSlow2 * fRec170[i - 1] + fZec47[i];
				fRec171[i] = fSlow276 * fYec85[(i + fYec85_idx - iSlow277) & 127] - (fSlow278 * fRec171[i - 1] + fConst6 * fRec171[i - 2]);
				fRec170[i] = fConst7 * (fRec171[i] - fRec171[i - 2]);
			}
			/* Post code */
			fYec85_idx_save = vsize;
			for (int j361 = 0; j361 < 4; j361 = j361 + 1) {
				fRec171_perm[j361] = fRec171_tmp[vsize + j361];
			}
			for (int j363 = 0; j363 < 4; j363 = j363 + 1) {
				fRec170_perm[j363] = fRec170_tmp[vsize + j363];
			}
			/* Recursive loop 119 */
			/* Pre code */
			fYec86_idx = (fYec86_idx + fYec86_idx_save) & 511;
			for (int j364 = 0; j364 < 4; j364 = j364 + 1) {
				fRec173_tmp[j364] = fRec173_perm[j364];
			}
			for (int j366 = 0; j366 < 4; j366 = j366 + 1) {
				fRec172_tmp[j366] = fRec172_perm[j366];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec86[(i + fYec86_idx) & 511] = fZec48[i] + fSlow2 * fRec172[i - 1];
				fRec173[i] = fSlow279 * fYec86[(i + fYec86_idx - iSlow280) & 511] - (fSlow281 * fRec173[i - 1] + fConst6 * fRec173[i - 2]);
				fRec172[i] = fConst7 * (fRec173[i] - fRec173[i - 2]);
			}
			/* Post code */
			fYec86_idx_save = vsize;
			for (int j365 = 0; j365 < 4; j365 = j365 + 1) {
				fRec173_perm[j365] = fRec173_tmp[vsize + j365];
			}
			for (int j367 = 0; j367 < 4; j367 = j367 + 1) {
				fRec172_perm[j367] = fRec172_tmp[vsize + j367];
			}
			/* Recursive loop 120 */
			/* Pre code */
			fYec87_idx = (fYec87_idx + fYec87_idx_save) & 511;
			for (int j368 = 0; j368 < 4; j368 = j368 + 1) {
				fRec175_tmp[j368] = fRec175_perm[j368];
			}
			for (int j370 = 0; j370 < 4; j370 = j370 + 1) {
				fRec174_tmp[j370] = fRec174_perm[j370];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec87[(i + fYec87_idx) & 511] = fSlow2 * fRec174[i - 1] + fZec48[i];
				fRec175[i] = fSlow282 * fYec87[(i + fYec87_idx - iSlow283) & 511] - (fSlow284 * fRec175[i - 1] + fConst6 * fRec175[i - 2]);
				fRec174[i] = fConst7 * (fRec175[i] - fRec175[i - 2]);
			}
			/* Post code */
			fYec87_idx_save = vsize;
			for (int j369 = 0; j369 < 4; j369 = j369 + 1) {
				fRec175_perm[j369] = fRec175_tmp[vsize + j369];
			}
			for (int j371 = 0; j371 < 4; j371 = j371 + 1) {
				fRec174_perm[j371] = fRec174_tmp[vsize + j371];
			}
			/* Recursive loop 121 */
			/* Pre code */
			fYec88_idx = (fYec88_idx + fYec88_idx_save) & 1023;
			for (int j372 = 0; j372 < 4; j372 = j372 + 1) {
				fRec177_tmp[j372] = fRec177_perm[j372];
			}
			for (int j374 = 0; j374 < 4; j374 = j374 + 1) {
				fRec176_tmp[j374] = fRec176_perm[j374];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec88[(i + fYec88_idx) & 1023] = fZec49[i] + fSlow2 * fRec176[i - 1];
				fRec177[i] = fSlow285 * fYec88[(i + fYec88_idx - iSlow286) & 1023] - (fSlow287 * fRec177[i - 1] + fConst6 * fRec177[i - 2]);
				fRec176[i] = fConst7 * (fRec177[i] - fRec177[i - 2]);
			}
			/* Post code */
			fYec88_idx_save = vsize;
			for (int j373 = 0; j373 < 4; j373 = j373 + 1) {
				fRec177_perm[j373] = fRec177_tmp[vsize + j373];
			}
			for (int j375 = 0; j375 < 4; j375 = j375 + 1) {
				fRec176_perm[j375] = fRec176_tmp[vsize + j375];
			}
			/* Recursive loop 122 */
			/* Pre code */
			fYec89_idx = (fYec89_idx + fYec89_idx_save) & 1023;
			for (int j376 = 0; j376 < 4; j376 = j376 + 1) {
				fRec179_tmp[j376] = fRec179_perm[j376];
			}
			for (int j378 = 0; j378 < 4; j378 = j378 + 1) {
				fRec178_tmp[j378] = fRec178_perm[j378];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec89[(i + fYec89_idx) & 1023] = fSlow2 * fRec178[i - 1] + fZec49[i];
				fRec179[i] = fSlow288 * fYec89[(i + fYec89_idx - iSlow289) & 1023] - (fSlow290 * fRec179[i - 1] + fConst6 * fRec179[i - 2]);
				fRec178[i] = fConst7 * (fRec179[i] - fRec179[i - 2]);
			}
			/* Post code */
			fYec89_idx_save = vsize;
			for (int j377 = 0; j377 < 4; j377 = j377 + 1) {
				fRec179_perm[j377] = fRec179_tmp[vsize + j377];
			}
			for (int j379 = 0; j379 < 4; j379 = j379 + 1) {
				fRec178_perm[j379] = fRec178_tmp[vsize + j379];
			}
			/* Recursive loop 123 */
			/* Pre code */
			fYec90_idx = (fYec90_idx + fYec90_idx_save) & 127;
			for (int j380 = 0; j380 < 4; j380 = j380 + 1) {
				fRec181_tmp[j380] = fRec181_perm[j380];
			}
			for (int j382 = 0; j382 < 4; j382 = j382 + 1) {
				fRec180_tmp[j382] = fRec180_perm[j382];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec90[(i + fYec90_idx) & 127] = fZec50[i] + fSlow2 * fRec180[i - 1];
				fRec181[i] = fSlow291 * fYec90[(i + fYec90_idx - iSlow292) & 127] - (fSlow293 * fRec181[i - 1] + fConst6 * fRec181[i - 2]);
				fRec180[i] = fConst7 * (fRec181[i] - fRec181[i - 2]);
			}
			/* Post code */
			fYec90_idx_save = vsize;
			for (int j381 = 0; j381 < 4; j381 = j381 + 1) {
				fRec181_perm[j381] = fRec181_tmp[vsize + j381];
			}
			for (int j383 = 0; j383 < 4; j383 = j383 + 1) {
				fRec180_perm[j383] = fRec180_tmp[vsize + j383];
			}
			/* Recursive loop 124 */
			/* Pre code */
			fYec91_idx = (fYec91_idx + fYec91_idx_save) & 127;
			for (int j384 = 0; j384 < 4; j384 = j384 + 1) {
				fRec183_tmp[j384] = fRec183_perm[j384];
			}
			for (int j386 = 0; j386 < 4; j386 = j386 + 1) {
				fRec182_tmp[j386] = fRec182_perm[j386];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec91[(i + fYec91_idx) & 127] = fSlow2 * fRec182[i - 1] + fZec50[i];
				fRec183[i] = fSlow294 * fYec91[(i + fYec91_idx - iSlow295) & 127] - (fSlow296 * fRec183[i - 1] + fConst6 * fRec183[i - 2]);
				fRec182[i] = fConst7 * (fRec183[i] - fRec183[i - 2]);
			}
			/* Post code */
			fYec91_idx_save = vsize;
			for (int j385 = 0; j385 < 4; j385 = j385 + 1) {
				fRec183_perm[j385] = fRec183_tmp[vsize + j385];
			}
			for (int j387 = 0; j387 < 4; j387 = j387 + 1) {
				fRec182_perm[j387] = fRec182_tmp[vsize + j387];
			}
			/* Recursive loop 125 */
			/* Pre code */
			fYec92_idx = (fYec92_idx + fYec92_idx_save) & 127;
			for (int j388 = 0; j388 < 4; j388 = j388 + 1) {
				fRec185_tmp[j388] = fRec185_perm[j388];
			}
			for (int j390 = 0; j390 < 4; j390 = j390 + 1) {
				fRec184_tmp[j390] = fRec184_perm[j390];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec92[(i + fYec92_idx) & 127] = fZec51[i] + fSlow2 * fRec184[i - 1];
				fRec185[i] = fSlow297 * fYec92[(i + fYec92_idx - iSlow298) & 127] - (fSlow299 * fRec185[i - 1] + fConst6 * fRec185[i - 2]);
				fRec184[i] = fConst7 * (fRec185[i] - fRec185[i - 2]);
			}
			/* Post code */
			fYec92_idx_save = vsize;
			for (int j389 = 0; j389 < 4; j389 = j389 + 1) {
				fRec185_perm[j389] = fRec185_tmp[vsize + j389];
			}
			for (int j391 = 0; j391 < 4; j391 = j391 + 1) {
				fRec184_perm[j391] = fRec184_tmp[vsize + j391];
			}
			/* Recursive loop 126 */
			/* Pre code */
			fYec93_idx = (fYec93_idx + fYec93_idx_save) & 127;
			for (int j392 = 0; j392 < 4; j392 = j392 + 1) {
				fRec187_tmp[j392] = fRec187_perm[j392];
			}
			for (int j394 = 0; j394 < 4; j394 = j394 + 1) {
				fRec186_tmp[j394] = fRec186_perm[j394];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec93[(i + fYec93_idx) & 127] = fSlow2 * fRec186[i - 1] + fZec51[i];
				fRec187[i] = fSlow300 * fYec93[(i + fYec93_idx - iSlow301) & 127] - (fSlow302 * fRec187[i - 1] + fConst6 * fRec187[i - 2]);
				fRec186[i] = fConst7 * (fRec187[i] - fRec187[i - 2]);
			}
			/* Post code */
			fYec93_idx_save = vsize;
			for (int j393 = 0; j393 < 4; j393 = j393 + 1) {
				fRec187_perm[j393] = fRec187_tmp[vsize + j393];
			}
			for (int j395 = 0; j395 < 4; j395 = j395 + 1) {
				fRec186_perm[j395] = fRec186_tmp[vsize + j395];
			}
			/* Recursive loop 127 */
			/* Pre code */
			fYec94_idx = (fYec94_idx + fYec94_idx_save) & 127;
			for (int j396 = 0; j396 < 4; j396 = j396 + 1) {
				fRec189_tmp[j396] = fRec189_perm[j396];
			}
			for (int j398 = 0; j398 < 4; j398 = j398 + 1) {
				fRec188_tmp[j398] = fRec188_perm[j398];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec94[(i + fYec94_idx) & 127] = fZec52[i] + fSlow2 * fRec188[i - 1];
				fRec189[i] = fSlow303 * fYec94[(i + fYec94_idx - iSlow304) & 127] - (fSlow305 * fRec189[i - 1] + fConst6 * fRec189[i - 2]);
				fRec188[i] = fConst7 * (fRec189[i] - fRec189[i - 2]);
			}
			/* Post code */
			fYec94_idx_save = vsize;
			for (int j397 = 0; j397 < 4; j397 = j397 + 1) {
				fRec189_perm[j397] = fRec189_tmp[vsize + j397];
			}
			for (int j399 = 0; j399 < 4; j399 = j399 + 1) {
				fRec188_perm[j399] = fRec188_tmp[vsize + j399];
			}
			/* Recursive loop 128 */
			/* Pre code */
			fYec95_idx = (fYec95_idx + fYec95_idx_save) & 127;
			for (int j400 = 0; j400 < 4; j400 = j400 + 1) {
				fRec191_tmp[j400] = fRec191_perm[j400];
			}
			for (int j402 = 0; j402 < 4; j402 = j402 + 1) {
				fRec190_tmp[j402] = fRec190_perm[j402];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec95[(i + fYec95_idx) & 127] = fSlow2 * fRec190[i - 1] + fZec52[i];
				fRec191[i] = fSlow306 * fYec95[(i + fYec95_idx - iSlow307) & 127] - (fSlow308 * fRec191[i - 1] + fConst6 * fRec191[i - 2]);
				fRec190[i] = fConst7 * (fRec191[i] - fRec191[i - 2]);
			}
			/* Post code */
			fYec95_idx_save = vsize;
			for (int j401 = 0; j401 < 4; j401 = j401 + 1) {
				fRec191_perm[j401] = fRec191_tmp[vsize + j401];
			}
			for (int j403 = 0; j403 < 4; j403 = j403 + 1) {
				fRec190_perm[j403] = fRec190_tmp[vsize + j403];
			}
			/* Recursive loop 129 */
			/* Pre code */
			fYec96_idx = (fYec96_idx + fYec96_idx_save) & 511;
			for (int j404 = 0; j404 < 4; j404 = j404 + 1) {
				fRec193_tmp[j404] = fRec193_perm[j404];
			}
			for (int j406 = 0; j406 < 4; j406 = j406 + 1) {
				fRec192_tmp[j406] = fRec192_perm[j406];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec96[(i + fYec96_idx) & 511] = fZec53[i] + fSlow2 * fRec192[i - 1];
				fRec193[i] = fSlow309 * fYec96[(i + fYec96_idx - iSlow310) & 511] - (fSlow311 * fRec193[i - 1] + fConst6 * fRec193[i - 2]);
				fRec192[i] = fConst7 * (fRec193[i] - fRec193[i - 2]);
			}
			/* Post code */
			fYec96_idx_save = vsize;
			for (int j405 = 0; j405 < 4; j405 = j405 + 1) {
				fRec193_perm[j405] = fRec193_tmp[vsize + j405];
			}
			for (int j407 = 0; j407 < 4; j407 = j407 + 1) {
				fRec192_perm[j407] = fRec192_tmp[vsize + j407];
			}
			/* Recursive loop 130 */
			/* Pre code */
			fYec97_idx = (fYec97_idx + fYec97_idx_save) & 511;
			for (int j408 = 0; j408 < 4; j408 = j408 + 1) {
				fRec195_tmp[j408] = fRec195_perm[j408];
			}
			for (int j410 = 0; j410 < 4; j410 = j410 + 1) {
				fRec194_tmp[j410] = fRec194_perm[j410];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec97[(i + fYec97_idx) & 511] = fSlow2 * fRec194[i - 1] + fZec53[i];
				fRec195[i] = fSlow312 * fYec97[(i + fYec97_idx - iSlow313) & 511] - (fSlow314 * fRec195[i - 1] + fConst6 * fRec195[i - 2]);
				fRec194[i] = fConst7 * (fRec195[i] - fRec195[i - 2]);
			}
			/* Post code */
			fYec97_idx_save = vsize;
			for (int j409 = 0; j409 < 4; j409 = j409 + 1) {
				fRec195_perm[j409] = fRec195_tmp[vsize + j409];
			}
			for (int j411 = 0; j411 < 4; j411 = j411 + 1) {
				fRec194_perm[j411] = fRec194_tmp[vsize + j411];
			}
			/* Recursive loop 131 */
			/* Pre code */
			fYec98_idx = (fYec98_idx + fYec98_idx_save) & 1023;
			for (int j412 = 0; j412 < 4; j412 = j412 + 1) {
				fRec197_tmp[j412] = fRec197_perm[j412];
			}
			for (int j414 = 0; j414 < 4; j414 = j414 + 1) {
				fRec196_tmp[j414] = fRec196_perm[j414];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec98[(i + fYec98_idx) & 1023] = fZec54[i] + fSlow2 * fRec196[i - 1];
				fRec197[i] = fSlow315 * fYec98[(i + fYec98_idx - iSlow316) & 1023] - (fSlow317 * fRec197[i - 1] + fConst6 * fRec197[i - 2]);
				fRec196[i] = fConst7 * (fRec197[i] - fRec197[i - 2]);
			}
			/* Post code */
			fYec98_idx_save = vsize;
			for (int j413 = 0; j413 < 4; j413 = j413 + 1) {
				fRec197_perm[j413] = fRec197_tmp[vsize + j413];
			}
			for (int j415 = 0; j415 < 4; j415 = j415 + 1) {
				fRec196_perm[j415] = fRec196_tmp[vsize + j415];
			}
			/* Recursive loop 132 */
			/* Pre code */
			fYec99_idx = (fYec99_idx + fYec99_idx_save) & 1023;
			for (int j416 = 0; j416 < 4; j416 = j416 + 1) {
				fRec199_tmp[j416] = fRec199_perm[j416];
			}
			for (int j418 = 0; j418 < 4; j418 = j418 + 1) {
				fRec198_tmp[j418] = fRec198_perm[j418];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec99[(i + fYec99_idx) & 1023] = fSlow2 * fRec198[i - 1] + fZec54[i];
				fRec199[i] = fSlow318 * fYec99[(i + fYec99_idx - iSlow319) & 1023] - (fSlow320 * fRec199[i - 1] + fConst6 * fRec199[i - 2]);
				fRec198[i] = fConst7 * (fRec199[i] - fRec199[i - 2]);
			}
			/* Post code */
			fYec99_idx_save = vsize;
			for (int j417 = 0; j417 < 4; j417 = j417 + 1) {
				fRec199_perm[j417] = fRec199_tmp[vsize + j417];
			}
			for (int j419 = 0; j419 < 4; j419 = j419 + 1) {
				fRec198_perm[j419] = fRec198_tmp[vsize + j419];
			}
			/* Recursive loop 133 */
			/* Pre code */
			fYec100_idx = (fYec100_idx + fYec100_idx_save) & 127;
			for (int j420 = 0; j420 < 4; j420 = j420 + 1) {
				fRec201_tmp[j420] = fRec201_perm[j420];
			}
			for (int j422 = 0; j422 < 4; j422 = j422 + 1) {
				fRec200_tmp[j422] = fRec200_perm[j422];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec100[(i + fYec100_idx) & 127] = fZec55[i] + fSlow2 * fRec200[i - 1];
				fRec201[i] = fSlow321 * fYec100[(i + fYec100_idx - iSlow322) & 127] - (fSlow323 * fRec201[i - 1] + fConst6 * fRec201[i - 2]);
				fRec200[i] = fConst7 * (fRec201[i] - fRec201[i - 2]);
			}
			/* Post code */
			fYec100_idx_save = vsize;
			for (int j421 = 0; j421 < 4; j421 = j421 + 1) {
				fRec201_perm[j421] = fRec201_tmp[vsize + j421];
			}
			for (int j423 = 0; j423 < 4; j423 = j423 + 1) {
				fRec200_perm[j423] = fRec200_tmp[vsize + j423];
			}
			/* Recursive loop 134 */
			/* Pre code */
			fYec101_idx = (fYec101_idx + fYec101_idx_save) & 127;
			for (int j424 = 0; j424 < 4; j424 = j424 + 1) {
				fRec203_tmp[j424] = fRec203_perm[j424];
			}
			for (int j426 = 0; j426 < 4; j426 = j426 + 1) {
				fRec202_tmp[j426] = fRec202_perm[j426];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec101[(i + fYec101_idx) & 127] = fSlow2 * fRec202[i - 1] + fZec55[i];
				fRec203[i] = fSlow324 * fYec101[(i + fYec101_idx - iSlow325) & 127] - (fSlow326 * fRec203[i - 1] + fConst6 * fRec203[i - 2]);
				fRec202[i] = fConst7 * (fRec203[i] - fRec203[i - 2]);
			}
			/* Post code */
			fYec101_idx_save = vsize;
			for (int j425 = 0; j425 < 4; j425 = j425 + 1) {
				fRec203_perm[j425] = fRec203_tmp[vsize + j425];
			}
			for (int j427 = 0; j427 < 4; j427 = j427 + 1) {
				fRec202_perm[j427] = fRec202_tmp[vsize + j427];
			}
			/* Recursive loop 135 */
			/* Pre code */
			fYec102_idx = (fYec102_idx + fYec102_idx_save) & 127;
			for (int j428 = 0; j428 < 4; j428 = j428 + 1) {
				fRec205_tmp[j428] = fRec205_perm[j428];
			}
			for (int j430 = 0; j430 < 4; j430 = j430 + 1) {
				fRec204_tmp[j430] = fRec204_perm[j430];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec102[(i + fYec102_idx) & 127] = fZec56[i] + fSlow2 * fRec204[i - 1];
				fRec205[i] = fSlow327 * fYec102[(i + fYec102_idx - iSlow328) & 127] - (fSlow329 * fRec205[i - 1] + fConst6 * fRec205[i - 2]);
				fRec204[i] = fConst7 * (fRec205[i] - fRec205[i - 2]);
			}
			/* Post code */
			fYec102_idx_save = vsize;
			for (int j429 = 0; j429 < 4; j429 = j429 + 1) {
				fRec205_perm[j429] = fRec205_tmp[vsize + j429];
			}
			for (int j431 = 0; j431 < 4; j431 = j431 + 1) {
				fRec204_perm[j431] = fRec204_tmp[vsize + j431];
			}
			/* Recursive loop 136 */
			/* Pre code */
			fYec103_idx = (fYec103_idx + fYec103_idx_save) & 127;
			for (int j432 = 0; j432 < 4; j432 = j432 + 1) {
				fRec207_tmp[j432] = fRec207_perm[j432];
			}
			for (int j434 = 0; j434 < 4; j434 = j434 + 1) {
				fRec206_tmp[j434] = fRec206_perm[j434];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec103[(i + fYec103_idx) & 127] = fSlow2 * fRec206[i - 1] + fZec56[i];
				fRec207[i] = fSlow330 * fYec103[(i + fYec103_idx - iSlow331) & 127] - (fSlow332 * fRec207[i - 1] + fConst6 * fRec207[i - 2]);
				fRec206[i] = fConst7 * (fRec207[i] - fRec207[i - 2]);
			}
			/* Post code */
			fYec103_idx_save = vsize;
			for (int j433 = 0; j433 < 4; j433 = j433 + 1) {
				fRec207_perm[j433] = fRec207_tmp[vsize + j433];
			}
			for (int j435 = 0; j435 < 4; j435 = j435 + 1) {
				fRec206_perm[j435] = fRec206_tmp[vsize + j435];
			}
			/* Recursive loop 137 */
			/* Pre code */
			fYec104_idx = (fYec104_idx + fYec104_idx_save) & 127;
			for (int j436 = 0; j436 < 4; j436 = j436 + 1) {
				fRec209_tmp[j436] = fRec209_perm[j436];
			}
			for (int j438 = 0; j438 < 4; j438 = j438 + 1) {
				fRec208_tmp[j438] = fRec208_perm[j438];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec104[(i + fYec104_idx) & 127] = fZec57[i] + fSlow2 * fRec208[i - 1];
				fRec209[i] = fSlow333 * fYec104[(i + fYec104_idx - iSlow334) & 127] - (fSlow335 * fRec209[i - 1] + fConst6 * fRec209[i - 2]);
				fRec208[i] = fConst7 * (fRec209[i] - fRec209[i - 2]);
			}
			/* Post code */
			fYec104_idx_save = vsize;
			for (int j437 = 0; j437 < 4; j437 = j437 + 1) {
				fRec209_perm[j437] = fRec209_tmp[vsize + j437];
			}
			for (int j439 = 0; j439 < 4; j439 = j439 + 1) {
				fRec208_perm[j439] = fRec208_tmp[vsize + j439];
			}
			/* Recursive loop 138 */
			/* Pre code */
			fYec105_idx = (fYec105_idx + fYec105_idx_save) & 1023;
			for (int j440 = 0; j440 < 4; j440 = j440 + 1) {
				fRec211_tmp[j440] = fRec211_perm[j440];
			}
			for (int j442 = 0; j442 < 4; j442 = j442 + 1) {
				fRec210_tmp[j442] = fRec210_perm[j442];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec105[(i + fYec105_idx) & 1023] = fSlow2 * fRec210[i - 1] + fZec58[i];
				fRec211[i] = fSlow336 * fYec105[(i + fYec105_idx - iSlow337) & 1023] - (fSlow338 * fRec211[i - 1] + fConst6 * fRec211[i - 2]);
				fRec210[i] = fConst7 * (fRec211[i] - fRec211[i - 2]);
			}
			/* Post code */
			fYec105_idx_save = vsize;
			for (int j441 = 0; j441 < 4; j441 = j441 + 1) {
				fRec211_perm[j441] = fRec211_tmp[vsize + j441];
			}
			for (int j443 = 0; j443 < 4; j443 = j443 + 1) {
				fRec210_perm[j443] = fRec210_tmp[vsize + j443];
			}
			/* Recursive loop 139 */
			/* Pre code */
			fYec106_idx = (fYec106_idx + fYec106_idx_save) & 1023;
			for (int j444 = 0; j444 < 4; j444 = j444 + 1) {
				fRec213_tmp[j444] = fRec213_perm[j444];
			}
			for (int j446 = 0; j446 < 4; j446 = j446 + 1) {
				fRec212_tmp[j446] = fRec212_perm[j446];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec106[(i + fYec106_idx) & 1023] = fZec58[i] + fSlow2 * fRec212[i - 1];
				fRec213[i] = fSlow339 * fYec106[(i + fYec106_idx - iSlow340) & 1023] - (fSlow341 * fRec213[i - 1] + fConst6 * fRec213[i - 2]);
				fRec212[i] = fConst7 * (fRec213[i] - fRec213[i - 2]);
			}
			/* Post code */
			fYec106_idx_save = vsize;
			for (int j445 = 0; j445 < 4; j445 = j445 + 1) {
				fRec213_perm[j445] = fRec213_tmp[vsize + j445];
			}
			for (int j447 = 0; j447 < 4; j447 = j447 + 1) {
				fRec212_perm[j447] = fRec212_tmp[vsize + j447];
			}
			/* Recursive loop 140 */
			/* Pre code */
			fYec107_idx = (fYec107_idx + fYec107_idx_save) & 511;
			for (int j448 = 0; j448 < 4; j448 = j448 + 1) {
				fRec215_tmp[j448] = fRec215_perm[j448];
			}
			for (int j450 = 0; j450 < 4; j450 = j450 + 1) {
				fRec214_tmp[j450] = fRec214_perm[j450];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec107[(i + fYec107_idx) & 511] = fSlow2 * fRec214[i - 1] + fZec59[i];
				fRec215[i] = fSlow342 * fYec107[(i + fYec107_idx - iSlow343) & 511] - (fSlow344 * fRec215[i - 1] + fConst6 * fRec215[i - 2]);
				fRec214[i] = fConst7 * (fRec215[i] - fRec215[i - 2]);
			}
			/* Post code */
			fYec107_idx_save = vsize;
			for (int j449 = 0; j449 < 4; j449 = j449 + 1) {
				fRec215_perm[j449] = fRec215_tmp[vsize + j449];
			}
			for (int j451 = 0; j451 < 4; j451 = j451 + 1) {
				fRec214_perm[j451] = fRec214_tmp[vsize + j451];
			}
			/* Recursive loop 141 */
			/* Pre code */
			fYec108_idx = (fYec108_idx + fYec108_idx_save) & 511;
			for (int j452 = 0; j452 < 4; j452 = j452 + 1) {
				fRec217_tmp[j452] = fRec217_perm[j452];
			}
			for (int j454 = 0; j454 < 4; j454 = j454 + 1) {
				fRec216_tmp[j454] = fRec216_perm[j454];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec108[(i + fYec108_idx) & 511] = fZec59[i] + fSlow2 * fRec216[i - 1];
				fRec217[i] = fSlow345 * fYec108[(i + fYec108_idx - iSlow346) & 511] - (fSlow347 * fRec217[i - 1] + fConst6 * fRec217[i - 2]);
				fRec216[i] = fConst7 * (fRec217[i] - fRec217[i - 2]);
			}
			/* Post code */
			fYec108_idx_save = vsize;
			for (int j453 = 0; j453 < 4; j453 = j453 + 1) {
				fRec217_perm[j453] = fRec217_tmp[vsize + j453];
			}
			for (int j455 = 0; j455 < 4; j455 = j455 + 1) {
				fRec216_perm[j455] = fRec216_tmp[vsize + j455];
			}
			/* Recursive loop 142 */
			/* Pre code */
			fYec109_idx = (fYec109_idx + fYec109_idx_save) & 127;
			for (int j456 = 0; j456 < 4; j456 = j456 + 1) {
				fRec219_tmp[j456] = fRec219_perm[j456];
			}
			for (int j458 = 0; j458 < 4; j458 = j458 + 1) {
				fRec218_tmp[j458] = fRec218_perm[j458];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec109[(i + fYec109_idx) & 127] = fSlow2 * fRec218[i - 1] + fZec57[i];
				fRec219[i] = fSlow348 * fYec109[(i + fYec109_idx - iSlow349) & 127] - (fSlow350 * fRec219[i - 1] + fConst6 * fRec219[i - 2]);
				fRec218[i] = fConst7 * (fRec219[i] - fRec219[i - 2]);
			}
			/* Post code */
			fYec109_idx_save = vsize;
			for (int j457 = 0; j457 < 4; j457 = j457 + 1) {
				fRec219_perm[j457] = fRec219_tmp[vsize + j457];
			}
			for (int j459 = 0; j459 < 4; j459 = j459 + 1) {
				fRec218_perm[j459] = fRec218_tmp[vsize + j459];
			}
			/* Recursive loop 143 */
			/* Pre code */
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 255;
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				fRec5_tmp[j14] = fRec5_perm[j14];
			}
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fRec4_tmp[j16] = fRec4_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[(i + fYec2_idx) & 255] = fSlow2 * fRec4[i - 1] + 5.2995043 * fZec2[i];
				fRec5[i] = fSlow12 * fYec2[(i + fYec2_idx - iSlow14) & 255] - (fSlow15 * fRec5[i - 1] + fConst6 * fRec5[i - 2]);
				fRec4[i] = fConst7 * (fRec5[i] - fRec5[i - 2]);
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				fRec5_perm[j15] = fRec5_tmp[vsize + j15];
			}
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fRec4_perm[j17] = fRec4_tmp[vsize + j17];
			}
			/* Recursive loop 144 */
			/* Pre code */
			fYec3_idx = (fYec3_idx + fYec3_idx_save) & 255;
			for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
				fRec7_tmp[j20] = fRec7_perm[j20];
			}
			for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
				fRec6_tmp[j22] = fRec6_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[(i + fYec3_idx) & 255] = fSlow2 * fRec6[i - 1] + 5.2995043 * fZec3[i];
				fRec7[i] = fSlow17 * fYec3[(i + fYec3_idx - iSlow19) & 255] - (fSlow20 * fRec7[i - 1] + fConst6 * fRec7[i - 2]);
				fRec6[i] = fConst7 * (fRec7[i] - fRec7[i - 2]);
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
				fRec7_perm[j21] = fRec7_tmp[vsize + j21];
			}
			for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
				fRec6_perm[j23] = fRec6_tmp[vsize + j23];
			}
			/* Recursive loop 145 */
			/* Pre code */
			fYec4_idx = (fYec4_idx + fYec4_idx_save) & 255;
			for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
				fRec9_tmp[j26] = fRec9_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
				fRec8_tmp[j28] = fRec8_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec4[(i + fYec4_idx) & 255] = fSlow2 * fRec8[i - 1] + 5.2995043 * fZec4[i];
				fRec9[i] = fSlow22 * fYec4[(i + fYec4_idx - iSlow24) & 255] - (fSlow25 * fRec9[i - 1] + fConst6 * fRec9[i - 2]);
				fRec8[i] = fConst7 * (fRec9[i] - fRec9[i - 2]);
			}
			/* Post code */
			fYec4_idx_save = vsize;
			for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
				fRec9_perm[j27] = fRec9_tmp[vsize + j27];
			}
			for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
				fRec8_perm[j29] = fRec8_tmp[vsize + j29];
			}
			/* Recursive loop 146 */
			/* Pre code */
			fYec5_idx = (fYec5_idx + fYec5_idx_save) & 255;
			for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
				fRec11_tmp[j32] = fRec11_perm[j32];
			}
			for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
				fRec10_tmp[j34] = fRec10_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec5[(i + fYec5_idx) & 255] = fSlow2 * fRec10[i - 1] + 5.2995043 * fZec5[i];
				fRec11[i] = fSlow27 * fYec5[(i + fYec5_idx - iSlow29) & 255] - (fSlow30 * fRec11[i - 1] + fConst6 * fRec11[i - 2]);
				fRec10[i] = fConst7 * (fRec11[i] - fRec11[i - 2]);
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
				fRec11_perm[j33] = fRec11_tmp[vsize + j33];
			}
			for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
				fRec10_perm[j35] = fRec10_tmp[vsize + j35];
			}
			/* Recursive loop 147 */
			/* Pre code */
			fYec6_idx = (fYec6_idx + fYec6_idx_save) & 255;
			for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
				fRec13_tmp[j38] = fRec13_perm[j38];
			}
			for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
				fRec12_tmp[j40] = fRec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec6[(i + fYec6_idx) & 255] = fSlow2 * fRec12[i - 1] + 5.2995043 * fZec6[i];
				fRec13[i] = fSlow32 * fYec6[(i + fYec6_idx - iSlow34) & 255] - (fSlow35 * fRec13[i - 1] + fConst6 * fRec13[i - 2]);
				fRec12[i] = fConst7 * (fRec13[i] - fRec13[i - 2]);
			}
			/* Post code */
			fYec6_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
				fRec13_perm[j39] = fRec13_tmp[vsize + j39];
			}
			for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
				fRec12_perm[j41] = fRec12_tmp[vsize + j41];
			}
			/* Recursive loop 148 */
			/* Pre code */
			fYec7_idx = (fYec7_idx + fYec7_idx_save) & 255;
			for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
				fRec15_tmp[j44] = fRec15_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
				fRec14_tmp[j46] = fRec14_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec7[(i + fYec7_idx) & 255] = fSlow2 * fRec14[i - 1] + 5.2995043 * fZec7[i];
				fRec15[i] = fSlow37 * fYec7[(i + fYec7_idx - iSlow39) & 255] - (fSlow40 * fRec15[i - 1] + fConst6 * fRec15[i - 2]);
				fRec14[i] = fConst7 * (fRec15[i] - fRec15[i - 2]);
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
				fRec15_perm[j45] = fRec15_tmp[vsize + j45];
			}
			for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
				fRec14_perm[j47] = fRec14_tmp[vsize + j47];
			}
			/* Recursive loop 149 */
			/* Pre code */
			fYec8_idx = (fYec8_idx + fYec8_idx_save) & 255;
			for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
				fRec17_tmp[j50] = fRec17_perm[j50];
			}
			for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
				fRec16_tmp[j52] = fRec16_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec8[(i + fYec8_idx) & 255] = fSlow2 * fRec16[i - 1] + 5.2995043 * fZec8[i];
				fRec17[i] = fSlow42 * fYec8[(i + fYec8_idx - iSlow44) & 255] - (fSlow45 * fRec17[i - 1] + fConst6 * fRec17[i - 2]);
				fRec16[i] = fConst7 * (fRec17[i] - fRec17[i - 2]);
			}
			/* Post code */
			fYec8_idx_save = vsize;
			for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
				fRec17_perm[j51] = fRec17_tmp[vsize + j51];
			}
			for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
				fRec16_perm[j53] = fRec16_tmp[vsize + j53];
			}
			/* Recursive loop 150 */
			/* Pre code */
			fYec9_idx = (fYec9_idx + fYec9_idx_save) & 255;
			for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
				fRec19_tmp[j56] = fRec19_perm[j56];
			}
			for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
				fRec18_tmp[j58] = fRec18_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec9[(i + fYec9_idx) & 255] = fSlow2 * fRec18[i - 1] + 5.2995043 * fZec9[i];
				fRec19[i] = fSlow47 * fYec9[(i + fYec9_idx - iSlow49) & 255] - (fSlow50 * fRec19[i - 1] + fConst6 * fRec19[i - 2]);
				fRec18[i] = fConst7 * (fRec19[i] - fRec19[i - 2]);
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
				fRec19_perm[j57] = fRec19_tmp[vsize + j57];
			}
			for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
				fRec18_perm[j59] = fRec18_tmp[vsize + j59];
			}
			/* Recursive loop 151 */
			/* Pre code */
			fYec10_idx = (fYec10_idx + fYec10_idx_save) & 127;
			for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
				fRec21_tmp[j60] = fRec21_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
				fRec20_tmp[j62] = fRec20_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec10[(i + fYec10_idx) & 127] = fZec10[i] + fSlow2 * fRec20[i - 1];
				fRec21[i] = fSlow51 * fYec10[(i + fYec10_idx - iSlow52) & 127] - (fSlow53 * fRec21[i - 1] + fConst6 * fRec21[i - 2]);
				fRec20[i] = fConst7 * (fRec21[i] - fRec21[i - 2]);
			}
			/* Post code */
			fYec10_idx_save = vsize;
			for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
				fRec21_perm[j61] = fRec21_tmp[vsize + j61];
			}
			for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
				fRec20_perm[j63] = fRec20_tmp[vsize + j63];
			}
			/* Recursive loop 152 */
			/* Pre code */
			fYec11_idx = (fYec11_idx + fYec11_idx_save) & 127;
			for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
				fRec23_tmp[j64] = fRec23_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
				fRec22_tmp[j66] = fRec22_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec11[(i + fYec11_idx) & 127] = fSlow2 * fRec22[i - 1] + fZec10[i];
				fRec23[i] = fSlow54 * fYec11[(i + fYec11_idx - iSlow55) & 127] - (fSlow56 * fRec23[i - 1] + fConst6 * fRec23[i - 2]);
				fRec22[i] = fConst7 * (fRec23[i] - fRec23[i - 2]);
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
				fRec23_perm[j65] = fRec23_tmp[vsize + j65];
			}
			for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
				fRec22_perm[j67] = fRec22_tmp[vsize + j67];
			}
			/* Recursive loop 153 */
			/* Pre code */
			fYec12_idx = (fYec12_idx + fYec12_idx_save) & 127;
			for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
				fRec25_tmp[j68] = fRec25_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
				fRec24_tmp[j70] = fRec24_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec12[(i + fYec12_idx) & 127] = fZec11[i] + fSlow2 * fRec24[i - 1];
				fRec25[i] = fSlow57 * fYec12[(i + fYec12_idx - iSlow58) & 127] - (fSlow59 * fRec25[i - 1] + fConst6 * fRec25[i - 2]);
				fRec24[i] = fConst7 * (fRec25[i] - fRec25[i - 2]);
			}
			/* Post code */
			fYec12_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
				fRec25_perm[j69] = fRec25_tmp[vsize + j69];
			}
			for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
				fRec24_perm[j71] = fRec24_tmp[vsize + j71];
			}
			/* Recursive loop 154 */
			/* Pre code */
			fYec13_idx = (fYec13_idx + fYec13_idx_save) & 127;
			for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
				fRec27_tmp[j72] = fRec27_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
				fRec26_tmp[j74] = fRec26_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec13[(i + fYec13_idx) & 127] = fSlow2 * fRec26[i - 1] + fZec11[i];
				fRec27[i] = fSlow60 * fYec13[(i + fYec13_idx - iSlow61) & 127] - (fSlow62 * fRec27[i - 1] + fConst6 * fRec27[i - 2]);
				fRec26[i] = fConst7 * (fRec27[i] - fRec27[i - 2]);
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
				fRec27_perm[j73] = fRec27_tmp[vsize + j73];
			}
			for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
				fRec26_perm[j75] = fRec26_tmp[vsize + j75];
			}
			/* Recursive loop 155 */
			/* Pre code */
			fYec14_idx = (fYec14_idx + fYec14_idx_save) & 127;
			for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
				fRec29_tmp[j76] = fRec29_perm[j76];
			}
			for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
				fRec28_tmp[j78] = fRec28_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec14[(i + fYec14_idx) & 127] = fZec12[i] + fSlow2 * fRec28[i - 1];
				fRec29[i] = fSlow63 * fYec14[(i + fYec14_idx - iSlow64) & 127] - (fSlow65 * fRec29[i - 1] + fConst6 * fRec29[i - 2]);
				fRec28[i] = fConst7 * (fRec29[i] - fRec29[i - 2]);
			}
			/* Post code */
			fYec14_idx_save = vsize;
			for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
				fRec29_perm[j77] = fRec29_tmp[vsize + j77];
			}
			for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
				fRec28_perm[j79] = fRec28_tmp[vsize + j79];
			}
			/* Recursive loop 156 */
			/* Pre code */
			fYec15_idx = (fYec15_idx + fYec15_idx_save) & 127;
			for (int j80 = 0; j80 < 4; j80 = j80 + 1) {
				fRec31_tmp[j80] = fRec31_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = j82 + 1) {
				fRec30_tmp[j82] = fRec30_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec15[(i + fYec15_idx) & 127] = fSlow2 * fRec30[i - 1] + fZec12[i];
				fRec31[i] = fSlow66 * fYec15[(i + fYec15_idx - iSlow67) & 127] - (fSlow68 * fRec31[i - 1] + fConst6 * fRec31[i - 2]);
				fRec30[i] = fConst7 * (fRec31[i] - fRec31[i - 2]);
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j81 = 0; j81 < 4; j81 = j81 + 1) {
				fRec31_perm[j81] = fRec31_tmp[vsize + j81];
			}
			for (int j83 = 0; j83 < 4; j83 = j83 + 1) {
				fRec30_perm[j83] = fRec30_tmp[vsize + j83];
			}
			/* Recursive loop 157 */
			/* Pre code */
			fYec16_idx = (fYec16_idx + fYec16_idx_save) & 511;
			for (int j84 = 0; j84 < 4; j84 = j84 + 1) {
				fRec33_tmp[j84] = fRec33_perm[j84];
			}
			for (int j86 = 0; j86 < 4; j86 = j86 + 1) {
				fRec32_tmp[j86] = fRec32_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec16[(i + fYec16_idx) & 511] = fZec13[i] + fSlow2 * fRec32[i - 1];
				fRec33[i] = fSlow69 * fYec16[(i + fYec16_idx - iSlow70) & 511] - (fSlow71 * fRec33[i - 1] + fConst6 * fRec33[i - 2]);
				fRec32[i] = fConst7 * (fRec33[i] - fRec33[i - 2]);
			}
			/* Post code */
			fYec16_idx_save = vsize;
			for (int j85 = 0; j85 < 4; j85 = j85 + 1) {
				fRec33_perm[j85] = fRec33_tmp[vsize + j85];
			}
			for (int j87 = 0; j87 < 4; j87 = j87 + 1) {
				fRec32_perm[j87] = fRec32_tmp[vsize + j87];
			}
			/* Recursive loop 158 */
			/* Pre code */
			fYec17_idx = (fYec17_idx + fYec17_idx_save) & 511;
			for (int j88 = 0; j88 < 4; j88 = j88 + 1) {
				fRec35_tmp[j88] = fRec35_perm[j88];
			}
			for (int j90 = 0; j90 < 4; j90 = j90 + 1) {
				fRec34_tmp[j90] = fRec34_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec17[(i + fYec17_idx) & 511] = fSlow2 * fRec34[i - 1] + fZec13[i];
				fRec35[i] = fSlow72 * fYec17[(i + fYec17_idx - iSlow73) & 511] - (fSlow74 * fRec35[i - 1] + fConst6 * fRec35[i - 2]);
				fRec34[i] = fConst7 * (fRec35[i] - fRec35[i - 2]);
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j89 = 0; j89 < 4; j89 = j89 + 1) {
				fRec35_perm[j89] = fRec35_tmp[vsize + j89];
			}
			for (int j91 = 0; j91 < 4; j91 = j91 + 1) {
				fRec34_perm[j91] = fRec34_tmp[vsize + j91];
			}
			/* Recursive loop 159 */
			/* Pre code */
			fYec18_idx = (fYec18_idx + fYec18_idx_save) & 1023;
			for (int j92 = 0; j92 < 4; j92 = j92 + 1) {
				fRec37_tmp[j92] = fRec37_perm[j92];
			}
			for (int j94 = 0; j94 < 4; j94 = j94 + 1) {
				fRec36_tmp[j94] = fRec36_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec18[(i + fYec18_idx) & 1023] = fZec14[i] + fSlow2 * fRec36[i - 1];
				fRec37[i] = fSlow75 * fYec18[(i + fYec18_idx - iSlow76) & 1023] - (fSlow77 * fRec37[i - 1] + fConst6 * fRec37[i - 2]);
				fRec36[i] = fConst7 * (fRec37[i] - fRec37[i - 2]);
			}
			/* Post code */
			fYec18_idx_save = vsize;
			for (int j93 = 0; j93 < 4; j93 = j93 + 1) {
				fRec37_perm[j93] = fRec37_tmp[vsize + j93];
			}
			for (int j95 = 0; j95 < 4; j95 = j95 + 1) {
				fRec36_perm[j95] = fRec36_tmp[vsize + j95];
			}
			/* Recursive loop 160 */
			/* Pre code */
			fYec19_idx = (fYec19_idx + fYec19_idx_save) & 1023;
			for (int j96 = 0; j96 < 4; j96 = j96 + 1) {
				fRec39_tmp[j96] = fRec39_perm[j96];
			}
			for (int j98 = 0; j98 < 4; j98 = j98 + 1) {
				fRec38_tmp[j98] = fRec38_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec19[(i + fYec19_idx) & 1023] = fSlow2 * fRec38[i - 1] + fZec14[i];
				fRec39[i] = fSlow78 * fYec19[(i + fYec19_idx - iSlow79) & 1023] - (fSlow80 * fRec39[i - 1] + fConst6 * fRec39[i - 2]);
				fRec38[i] = fConst7 * (fRec39[i] - fRec39[i - 2]);
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j97 = 0; j97 < 4; j97 = j97 + 1) {
				fRec39_perm[j97] = fRec39_tmp[vsize + j97];
			}
			for (int j99 = 0; j99 < 4; j99 = j99 + 1) {
				fRec38_perm[j99] = fRec38_tmp[vsize + j99];
			}
			/* Recursive loop 161 */
			/* Pre code */
			fYec20_idx = (fYec20_idx + fYec20_idx_save) & 127;
			for (int j100 = 0; j100 < 4; j100 = j100 + 1) {
				fRec41_tmp[j100] = fRec41_perm[j100];
			}
			for (int j102 = 0; j102 < 4; j102 = j102 + 1) {
				fRec40_tmp[j102] = fRec40_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec20[(i + fYec20_idx) & 127] = fZec15[i] + fSlow2 * fRec40[i - 1];
				fRec41[i] = fSlow81 * fYec20[(i + fYec20_idx - iSlow82) & 127] - (fSlow83 * fRec41[i - 1] + fConst6 * fRec41[i - 2]);
				fRec40[i] = fConst7 * (fRec41[i] - fRec41[i - 2]);
			}
			/* Post code */
			fYec20_idx_save = vsize;
			for (int j101 = 0; j101 < 4; j101 = j101 + 1) {
				fRec41_perm[j101] = fRec41_tmp[vsize + j101];
			}
			for (int j103 = 0; j103 < 4; j103 = j103 + 1) {
				fRec40_perm[j103] = fRec40_tmp[vsize + j103];
			}
			/* Recursive loop 162 */
			/* Pre code */
			fYec21_idx = (fYec21_idx + fYec21_idx_save) & 127;
			for (int j104 = 0; j104 < 4; j104 = j104 + 1) {
				fRec43_tmp[j104] = fRec43_perm[j104];
			}
			for (int j106 = 0; j106 < 4; j106 = j106 + 1) {
				fRec42_tmp[j106] = fRec42_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec21[(i + fYec21_idx) & 127] = fSlow2 * fRec42[i - 1] + fZec15[i];
				fRec43[i] = fSlow84 * fYec21[(i + fYec21_idx - iSlow85) & 127] - (fSlow86 * fRec43[i - 1] + fConst6 * fRec43[i - 2]);
				fRec42[i] = fConst7 * (fRec43[i] - fRec43[i - 2]);
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j105 = 0; j105 < 4; j105 = j105 + 1) {
				fRec43_perm[j105] = fRec43_tmp[vsize + j105];
			}
			for (int j107 = 0; j107 < 4; j107 = j107 + 1) {
				fRec42_perm[j107] = fRec42_tmp[vsize + j107];
			}
			/* Recursive loop 163 */
			/* Pre code */
			fYec22_idx = (fYec22_idx + fYec22_idx_save) & 127;
			for (int j108 = 0; j108 < 4; j108 = j108 + 1) {
				fRec45_tmp[j108] = fRec45_perm[j108];
			}
			for (int j110 = 0; j110 < 4; j110 = j110 + 1) {
				fRec44_tmp[j110] = fRec44_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec22[(i + fYec22_idx) & 127] = fZec16[i] + fSlow2 * fRec44[i - 1];
				fRec45[i] = fSlow87 * fYec22[(i + fYec22_idx - iSlow88) & 127] - (fSlow89 * fRec45[i - 1] + fConst6 * fRec45[i - 2]);
				fRec44[i] = fConst7 * (fRec45[i] - fRec45[i - 2]);
			}
			/* Post code */
			fYec22_idx_save = vsize;
			for (int j109 = 0; j109 < 4; j109 = j109 + 1) {
				fRec45_perm[j109] = fRec45_tmp[vsize + j109];
			}
			for (int j111 = 0; j111 < 4; j111 = j111 + 1) {
				fRec44_perm[j111] = fRec44_tmp[vsize + j111];
			}
			/* Recursive loop 164 */
			/* Pre code */
			fYec23_idx = (fYec23_idx + fYec23_idx_save) & 127;
			for (int j112 = 0; j112 < 4; j112 = j112 + 1) {
				fRec47_tmp[j112] = fRec47_perm[j112];
			}
			for (int j114 = 0; j114 < 4; j114 = j114 + 1) {
				fRec46_tmp[j114] = fRec46_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec23[(i + fYec23_idx) & 127] = fSlow2 * fRec46[i - 1] + fZec16[i];
				fRec47[i] = fSlow90 * fYec23[(i + fYec23_idx - iSlow91) & 127] - (fSlow92 * fRec47[i - 1] + fConst6 * fRec47[i - 2]);
				fRec46[i] = fConst7 * (fRec47[i] - fRec47[i - 2]);
			}
			/* Post code */
			fYec23_idx_save = vsize;
			for (int j113 = 0; j113 < 4; j113 = j113 + 1) {
				fRec47_perm[j113] = fRec47_tmp[vsize + j113];
			}
			for (int j115 = 0; j115 < 4; j115 = j115 + 1) {
				fRec46_perm[j115] = fRec46_tmp[vsize + j115];
			}
			/* Recursive loop 165 */
			/* Pre code */
			fYec24_idx = (fYec24_idx + fYec24_idx_save) & 127;
			for (int j116 = 0; j116 < 4; j116 = j116 + 1) {
				fRec49_tmp[j116] = fRec49_perm[j116];
			}
			for (int j118 = 0; j118 < 4; j118 = j118 + 1) {
				fRec48_tmp[j118] = fRec48_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec24[(i + fYec24_idx) & 127] = fZec17[i] + fSlow2 * fRec48[i - 1];
				fRec49[i] = fSlow93 * fYec24[(i + fYec24_idx - iSlow94) & 127] - (fSlow95 * fRec49[i - 1] + fConst6 * fRec49[i - 2]);
				fRec48[i] = fConst7 * (fRec49[i] - fRec49[i - 2]);
			}
			/* Post code */
			fYec24_idx_save = vsize;
			for (int j117 = 0; j117 < 4; j117 = j117 + 1) {
				fRec49_perm[j117] = fRec49_tmp[vsize + j117];
			}
			for (int j119 = 0; j119 < 4; j119 = j119 + 1) {
				fRec48_perm[j119] = fRec48_tmp[vsize + j119];
			}
			/* Recursive loop 166 */
			/* Pre code */
			fYec25_idx = (fYec25_idx + fYec25_idx_save) & 127;
			for (int j120 = 0; j120 < 4; j120 = j120 + 1) {
				fRec51_tmp[j120] = fRec51_perm[j120];
			}
			for (int j122 = 0; j122 < 4; j122 = j122 + 1) {
				fRec50_tmp[j122] = fRec50_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec25[(i + fYec25_idx) & 127] = fSlow2 * fRec50[i - 1] + fZec17[i];
				fRec51[i] = fSlow96 * fYec25[(i + fYec25_idx - iSlow97) & 127] - (fSlow98 * fRec51[i - 1] + fConst6 * fRec51[i - 2]);
				fRec50[i] = fConst7 * (fRec51[i] - fRec51[i - 2]);
			}
			/* Post code */
			fYec25_idx_save = vsize;
			for (int j121 = 0; j121 < 4; j121 = j121 + 1) {
				fRec51_perm[j121] = fRec51_tmp[vsize + j121];
			}
			for (int j123 = 0; j123 < 4; j123 = j123 + 1) {
				fRec50_perm[j123] = fRec50_tmp[vsize + j123];
			}
			/* Recursive loop 167 */
			/* Pre code */
			fYec26_idx = (fYec26_idx + fYec26_idx_save) & 511;
			for (int j124 = 0; j124 < 4; j124 = j124 + 1) {
				fRec53_tmp[j124] = fRec53_perm[j124];
			}
			for (int j126 = 0; j126 < 4; j126 = j126 + 1) {
				fRec52_tmp[j126] = fRec52_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec26[(i + fYec26_idx) & 511] = fZec18[i] + fSlow2 * fRec52[i - 1];
				fRec53[i] = fSlow99 * fYec26[(i + fYec26_idx - iSlow100) & 511] - (fSlow101 * fRec53[i - 1] + fConst6 * fRec53[i - 2]);
				fRec52[i] = fConst7 * (fRec53[i] - fRec53[i - 2]);
			}
			/* Post code */
			fYec26_idx_save = vsize;
			for (int j125 = 0; j125 < 4; j125 = j125 + 1) {
				fRec53_perm[j125] = fRec53_tmp[vsize + j125];
			}
			for (int j127 = 0; j127 < 4; j127 = j127 + 1) {
				fRec52_perm[j127] = fRec52_tmp[vsize + j127];
			}
			/* Recursive loop 168 */
			/* Pre code */
			fYec27_idx = (fYec27_idx + fYec27_idx_save) & 511;
			for (int j128 = 0; j128 < 4; j128 = j128 + 1) {
				fRec55_tmp[j128] = fRec55_perm[j128];
			}
			for (int j130 = 0; j130 < 4; j130 = j130 + 1) {
				fRec54_tmp[j130] = fRec54_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec27[(i + fYec27_idx) & 511] = fSlow2 * fRec54[i - 1] + fZec18[i];
				fRec55[i] = fSlow102 * fYec27[(i + fYec27_idx - iSlow103) & 511] - (fSlow104 * fRec55[i - 1] + fConst6 * fRec55[i - 2]);
				fRec54[i] = fConst7 * (fRec55[i] - fRec55[i - 2]);
			}
			/* Post code */
			fYec27_idx_save = vsize;
			for (int j129 = 0; j129 < 4; j129 = j129 + 1) {
				fRec55_perm[j129] = fRec55_tmp[vsize + j129];
			}
			for (int j131 = 0; j131 < 4; j131 = j131 + 1) {
				fRec54_perm[j131] = fRec54_tmp[vsize + j131];
			}
			/* Recursive loop 169 */
			/* Pre code */
			fYec28_idx = (fYec28_idx + fYec28_idx_save) & 1023;
			for (int j132 = 0; j132 < 4; j132 = j132 + 1) {
				fRec57_tmp[j132] = fRec57_perm[j132];
			}
			for (int j134 = 0; j134 < 4; j134 = j134 + 1) {
				fRec56_tmp[j134] = fRec56_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec28[(i + fYec28_idx) & 1023] = fZec19[i] + fSlow2 * fRec56[i - 1];
				fRec57[i] = fSlow105 * fYec28[(i + fYec28_idx - iSlow106) & 1023] - (fSlow107 * fRec57[i - 1] + fConst6 * fRec57[i - 2]);
				fRec56[i] = fConst7 * (fRec57[i] - fRec57[i - 2]);
			}
			/* Post code */
			fYec28_idx_save = vsize;
			for (int j133 = 0; j133 < 4; j133 = j133 + 1) {
				fRec57_perm[j133] = fRec57_tmp[vsize + j133];
			}
			for (int j135 = 0; j135 < 4; j135 = j135 + 1) {
				fRec56_perm[j135] = fRec56_tmp[vsize + j135];
			}
			/* Recursive loop 170 */
			/* Pre code */
			fYec29_idx = (fYec29_idx + fYec29_idx_save) & 1023;
			for (int j136 = 0; j136 < 4; j136 = j136 + 1) {
				fRec59_tmp[j136] = fRec59_perm[j136];
			}
			for (int j138 = 0; j138 < 4; j138 = j138 + 1) {
				fRec58_tmp[j138] = fRec58_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec29[(i + fYec29_idx) & 1023] = fSlow2 * fRec58[i - 1] + fZec19[i];
				fRec59[i] = fSlow108 * fYec29[(i + fYec29_idx - iSlow109) & 1023] - (fSlow110 * fRec59[i - 1] + fConst6 * fRec59[i - 2]);
				fRec58[i] = fConst7 * (fRec59[i] - fRec59[i - 2]);
			}
			/* Post code */
			fYec29_idx_save = vsize;
			for (int j137 = 0; j137 < 4; j137 = j137 + 1) {
				fRec59_perm[j137] = fRec59_tmp[vsize + j137];
			}
			for (int j139 = 0; j139 < 4; j139 = j139 + 1) {
				fRec58_perm[j139] = fRec58_tmp[vsize + j139];
			}
			/* Recursive loop 171 */
			/* Pre code */
			fYec30_idx = (fYec30_idx + fYec30_idx_save) & 127;
			for (int j140 = 0; j140 < 4; j140 = j140 + 1) {
				fRec61_tmp[j140] = fRec61_perm[j140];
			}
			for (int j142 = 0; j142 < 4; j142 = j142 + 1) {
				fRec60_tmp[j142] = fRec60_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec30[(i + fYec30_idx) & 127] = fZec20[i] + fSlow2 * fRec60[i - 1];
				fRec61[i] = fSlow111 * fYec30[(i + fYec30_idx - iSlow112) & 127] - (fSlow113 * fRec61[i - 1] + fConst6 * fRec61[i - 2]);
				fRec60[i] = fConst7 * (fRec61[i] - fRec61[i - 2]);
			}
			/* Post code */
			fYec30_idx_save = vsize;
			for (int j141 = 0; j141 < 4; j141 = j141 + 1) {
				fRec61_perm[j141] = fRec61_tmp[vsize + j141];
			}
			for (int j143 = 0; j143 < 4; j143 = j143 + 1) {
				fRec60_perm[j143] = fRec60_tmp[vsize + j143];
			}
			/* Recursive loop 172 */
			/* Pre code */
			fYec31_idx = (fYec31_idx + fYec31_idx_save) & 127;
			for (int j144 = 0; j144 < 4; j144 = j144 + 1) {
				fRec63_tmp[j144] = fRec63_perm[j144];
			}
			for (int j146 = 0; j146 < 4; j146 = j146 + 1) {
				fRec62_tmp[j146] = fRec62_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec31[(i + fYec31_idx) & 127] = fSlow2 * fRec62[i - 1] + fZec20[i];
				fRec63[i] = fSlow114 * fYec31[(i + fYec31_idx - iSlow115) & 127] - (fSlow116 * fRec63[i - 1] + fConst6 * fRec63[i - 2]);
				fRec62[i] = fConst7 * (fRec63[i] - fRec63[i - 2]);
			}
			/* Post code */
			fYec31_idx_save = vsize;
			for (int j145 = 0; j145 < 4; j145 = j145 + 1) {
				fRec63_perm[j145] = fRec63_tmp[vsize + j145];
			}
			for (int j147 = 0; j147 < 4; j147 = j147 + 1) {
				fRec62_perm[j147] = fRec62_tmp[vsize + j147];
			}
			/* Recursive loop 173 */
			/* Pre code */
			fYec32_idx = (fYec32_idx + fYec32_idx_save) & 127;
			for (int j148 = 0; j148 < 4; j148 = j148 + 1) {
				fRec65_tmp[j148] = fRec65_perm[j148];
			}
			for (int j150 = 0; j150 < 4; j150 = j150 + 1) {
				fRec64_tmp[j150] = fRec64_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec32[(i + fYec32_idx) & 127] = fZec21[i] + fSlow2 * fRec64[i - 1];
				fRec65[i] = fSlow117 * fYec32[(i + fYec32_idx - iSlow118) & 127] - (fSlow119 * fRec65[i - 1] + fConst6 * fRec65[i - 2]);
				fRec64[i] = fConst7 * (fRec65[i] - fRec65[i - 2]);
			}
			/* Post code */
			fYec32_idx_save = vsize;
			for (int j149 = 0; j149 < 4; j149 = j149 + 1) {
				fRec65_perm[j149] = fRec65_tmp[vsize + j149];
			}
			for (int j151 = 0; j151 < 4; j151 = j151 + 1) {
				fRec64_perm[j151] = fRec64_tmp[vsize + j151];
			}
			/* Recursive loop 174 */
			/* Pre code */
			fYec33_idx = (fYec33_idx + fYec33_idx_save) & 127;
			for (int j152 = 0; j152 < 4; j152 = j152 + 1) {
				fRec67_tmp[j152] = fRec67_perm[j152];
			}
			for (int j154 = 0; j154 < 4; j154 = j154 + 1) {
				fRec66_tmp[j154] = fRec66_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec33[(i + fYec33_idx) & 127] = fSlow2 * fRec66[i - 1] + fZec21[i];
				fRec67[i] = fSlow120 * fYec33[(i + fYec33_idx - iSlow121) & 127] - (fSlow122 * fRec67[i - 1] + fConst6 * fRec67[i - 2]);
				fRec66[i] = fConst7 * (fRec67[i] - fRec67[i - 2]);
			}
			/* Post code */
			fYec33_idx_save = vsize;
			for (int j153 = 0; j153 < 4; j153 = j153 + 1) {
				fRec67_perm[j153] = fRec67_tmp[vsize + j153];
			}
			for (int j155 = 0; j155 < 4; j155 = j155 + 1) {
				fRec66_perm[j155] = fRec66_tmp[vsize + j155];
			}
			/* Recursive loop 175 */
			/* Pre code */
			fYec34_idx = (fYec34_idx + fYec34_idx_save) & 127;
			for (int j156 = 0; j156 < 4; j156 = j156 + 1) {
				fRec69_tmp[j156] = fRec69_perm[j156];
			}
			for (int j158 = 0; j158 < 4; j158 = j158 + 1) {
				fRec68_tmp[j158] = fRec68_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec34[(i + fYec34_idx) & 127] = fZec22[i] + fSlow2 * fRec68[i - 1];
				fRec69[i] = fSlow123 * fYec34[(i + fYec34_idx - iSlow124) & 127] - (fSlow125 * fRec69[i - 1] + fConst6 * fRec69[i - 2]);
				fRec68[i] = fConst7 * (fRec69[i] - fRec69[i - 2]);
			}
			/* Post code */
			fYec34_idx_save = vsize;
			for (int j157 = 0; j157 < 4; j157 = j157 + 1) {
				fRec69_perm[j157] = fRec69_tmp[vsize + j157];
			}
			for (int j159 = 0; j159 < 4; j159 = j159 + 1) {
				fRec68_perm[j159] = fRec68_tmp[vsize + j159];
			}
			/* Recursive loop 176 */
			/* Pre code */
			fYec35_idx = (fYec35_idx + fYec35_idx_save) & 127;
			for (int j160 = 0; j160 < 4; j160 = j160 + 1) {
				fRec71_tmp[j160] = fRec71_perm[j160];
			}
			for (int j162 = 0; j162 < 4; j162 = j162 + 1) {
				fRec70_tmp[j162] = fRec70_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec35[(i + fYec35_idx) & 127] = fSlow2 * fRec70[i - 1] + fZec22[i];
				fRec71[i] = fSlow126 * fYec35[(i + fYec35_idx - iSlow127) & 127] - (fSlow128 * fRec71[i - 1] + fConst6 * fRec71[i - 2]);
				fRec70[i] = fConst7 * (fRec71[i] - fRec71[i - 2]);
			}
			/* Post code */
			fYec35_idx_save = vsize;
			for (int j161 = 0; j161 < 4; j161 = j161 + 1) {
				fRec71_perm[j161] = fRec71_tmp[vsize + j161];
			}
			for (int j163 = 0; j163 < 4; j163 = j163 + 1) {
				fRec70_perm[j163] = fRec70_tmp[vsize + j163];
			}
			/* Recursive loop 177 */
			/* Pre code */
			fYec36_idx = (fYec36_idx + fYec36_idx_save) & 511;
			for (int j164 = 0; j164 < 4; j164 = j164 + 1) {
				fRec73_tmp[j164] = fRec73_perm[j164];
			}
			for (int j166 = 0; j166 < 4; j166 = j166 + 1) {
				fRec72_tmp[j166] = fRec72_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec36[(i + fYec36_idx) & 511] = fZec23[i] + fSlow2 * fRec72[i - 1];
				fRec73[i] = fSlow129 * fYec36[(i + fYec36_idx - iSlow130) & 511] - (fSlow131 * fRec73[i - 1] + fConst6 * fRec73[i - 2]);
				fRec72[i] = fConst7 * (fRec73[i] - fRec73[i - 2]);
			}
			/* Post code */
			fYec36_idx_save = vsize;
			for (int j165 = 0; j165 < 4; j165 = j165 + 1) {
				fRec73_perm[j165] = fRec73_tmp[vsize + j165];
			}
			for (int j167 = 0; j167 < 4; j167 = j167 + 1) {
				fRec72_perm[j167] = fRec72_tmp[vsize + j167];
			}
			/* Recursive loop 178 */
			/* Pre code */
			fYec37_idx = (fYec37_idx + fYec37_idx_save) & 511;
			for (int j168 = 0; j168 < 4; j168 = j168 + 1) {
				fRec75_tmp[j168] = fRec75_perm[j168];
			}
			for (int j170 = 0; j170 < 4; j170 = j170 + 1) {
				fRec74_tmp[j170] = fRec74_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec37[(i + fYec37_idx) & 511] = fSlow2 * fRec74[i - 1] + fZec23[i];
				fRec75[i] = fSlow132 * fYec37[(i + fYec37_idx - iSlow133) & 511] - (fSlow134 * fRec75[i - 1] + fConst6 * fRec75[i - 2]);
				fRec74[i] = fConst7 * (fRec75[i] - fRec75[i - 2]);
			}
			/* Post code */
			fYec37_idx_save = vsize;
			for (int j169 = 0; j169 < 4; j169 = j169 + 1) {
				fRec75_perm[j169] = fRec75_tmp[vsize + j169];
			}
			for (int j171 = 0; j171 < 4; j171 = j171 + 1) {
				fRec74_perm[j171] = fRec74_tmp[vsize + j171];
			}
			/* Recursive loop 179 */
			/* Pre code */
			fYec38_idx = (fYec38_idx + fYec38_idx_save) & 1023;
			for (int j172 = 0; j172 < 4; j172 = j172 + 1) {
				fRec77_tmp[j172] = fRec77_perm[j172];
			}
			for (int j174 = 0; j174 < 4; j174 = j174 + 1) {
				fRec76_tmp[j174] = fRec76_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec38[(i + fYec38_idx) & 1023] = fZec24[i] + fSlow2 * fRec76[i - 1];
				fRec77[i] = fSlow135 * fYec38[(i + fYec38_idx - iSlow136) & 1023] - (fSlow137 * fRec77[i - 1] + fConst6 * fRec77[i - 2]);
				fRec76[i] = fConst7 * (fRec77[i] - fRec77[i - 2]);
			}
			/* Post code */
			fYec38_idx_save = vsize;
			for (int j173 = 0; j173 < 4; j173 = j173 + 1) {
				fRec77_perm[j173] = fRec77_tmp[vsize + j173];
			}
			for (int j175 = 0; j175 < 4; j175 = j175 + 1) {
				fRec76_perm[j175] = fRec76_tmp[vsize + j175];
			}
			/* Vectorizable loop 180 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(2.0 * (fRec0[i] + fRec2[i] + fRec4[i] + fRec6[i] + fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i] + fRec16[i] + fRec18[i]) + fRec20[i] + fRec22[i] + fRec24[i] + fRec26[i] + fRec28[i] + fRec30[i] + fRec32[i] + fRec34[i] + fRec36[i] + fRec38[i] + fRec40[i] + fRec42[i] + fRec44[i] + fRec46[i] + fRec48[i] + fRec50[i] + fRec52[i] + fRec54[i] + fRec56[i] + fRec58[i] + fRec60[i] + fRec62[i] + fRec64[i] + fRec66[i] + fRec68[i] + fRec70[i] + fRec72[i] + fRec74[i] + fRec76[i] + fRec78[i] + fRec80[i] + fRec82[i] + fRec84[i] + fRec86[i] + fRec88[i] + fRec90[i] + fRec92[i] + fRec94[i] + fRec96[i] + fRec98[i] + fRec100[i] + fRec102[i] + fRec104[i] + fRec106[i] + fRec108[i] + fRec110[i] + fRec112[i] + fRec114[i] + fRec116[i] + fRec118[i] + fRec120[i] + fRec122[i] + fRec124[i] + fRec126[i] + fRec128[i] + fRec130[i] + fRec132[i] + fRec134[i] + fRec136[i] + fRec138[i] + fRec140[i] + fRec142[i] + fRec144[i] + fRec146[i] + fRec148[i] + fRec150[i] + fRec152[i] + fRec154[i] + fRec156[i] + fRec158[i] + fRec160[i] + fRec162[i] + fRec164[i] + fRec166[i] + fRec168[i] + fRec170[i] + fRec172[i] + fRec174[i] + fRec176[i] + fRec178[i] + fRec180[i] + fRec182[i] + fRec184[i] + fRec186[i] + fRec188[i] + fRec190[i] + fRec192[i] + fRec194[i] + fRec196[i] + fRec198[i] + fRec200[i] + fRec202[i] + fRec204[i] + fRec206[i] + fRec208[i] + fRec210[i] + fRec212[i] + fRec214[i] + fRec216[i] + fRec218[i]);
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = count - vindex;
			/* Vectorizable loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
				fVec0_tmp[j0] = fVec0_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec0[i] = fSlow3;
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
				fVec0_perm[j1] = fVec0_tmp[vsize + j1];
			}
			/* Vectorizable loop 1 */
			/* Pre code */
			for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
				fVec1_tmp[j6] = fVec1_perm[j6];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec1[i] = fSlow8;
			}
			/* Post code */
			for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
				fVec1_perm[j7] = fVec1_tmp[vsize + j7];
			}
			/* Vectorizable loop 2 */
			/* Pre code */
			for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
				fVec2_tmp[j12] = fVec2_perm[j12];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec2[i] = fSlow13;
			}
			/* Post code */
			for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
				fVec2_perm[j13] = fVec2_tmp[vsize + j13];
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
				fVec3_tmp[j18] = fVec3_perm[j18];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec3[i] = fSlow18;
			}
			/* Post code */
			for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
				fVec3_perm[j19] = fVec3_tmp[vsize + j19];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
				fVec4_tmp[j24] = fVec4_perm[j24];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec4[i] = fSlow23;
			}
			/* Post code */
			for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
				fVec4_perm[j25] = fVec4_tmp[vsize + j25];
			}
			/* Vectorizable loop 5 */
			/* Pre code */
			for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
				fVec5_tmp[j30] = fVec5_perm[j30];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec5[i] = fSlow28;
			}
			/* Post code */
			for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
				fVec5_perm[j31] = fVec5_tmp[vsize + j31];
			}
			/* Vectorizable loop 6 */
			/* Pre code */
			for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
				fVec6_tmp[j36] = fVec6_perm[j36];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec6[i] = fSlow33;
			}
			/* Post code */
			for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
				fVec6_perm[j37] = fVec6_tmp[vsize + j37];
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
				fVec7_tmp[j42] = fVec7_perm[j42];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec7[i] = fSlow38;
			}
			/* Post code */
			for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
				fVec7_perm[j43] = fVec7_tmp[vsize + j43];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
				fVec8_tmp[j48] = fVec8_perm[j48];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec8[i] = fSlow43;
			}
			/* Post code */
			for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
				fVec8_perm[j49] = fVec8_tmp[vsize + j49];
			}
			/* Vectorizable loop 9 */
			/* Pre code */
			for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
				fVec9_tmp[j54] = fVec9_perm[j54];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fVec9[i] = fSlow48;
			}
			/* Post code */
			for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
				fVec9_perm[j55] = fVec9_tmp[vsize + j55];
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = static_cast<double>(fSlow3 > fVec0[i - 1]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = static_cast<double>(fSlow8 > fVec1[i - 1]);
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = static_cast<double>(fSlow13 > fVec2[i - 1]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = static_cast<double>(fSlow18 > fVec3[i - 1]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = static_cast<double>(fSlow23 > fVec4[i - 1]);
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = static_cast<double>(fSlow28 > fVec5[i - 1]);
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = static_cast<double>(fSlow33 > fVec6[i - 1]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = static_cast<double>(fSlow38 > fVec7[i - 1]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = static_cast<double>(fSlow43 > fVec8[i - 1]);
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = static_cast<double>(fSlow48 > fVec9[i - 1]);
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec25[i] = 6.7063036 * fZec3[i];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec26[i] = 1.7063034 * fZec3[i];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec27[i] = 5.0063033 * fZec3[i];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec28[i] = 2.0914886 * fZec3[i];
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec29[i] = 2.1900357 * fZec3[i];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec30[i] = 6.7063036 * fZec4[i];
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec31[i] = 1.7063034 * fZec4[i];
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec32[i] = 5.0063033 * fZec4[i];
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec33[i] = 2.0914886 * fZec4[i];
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec34[i] = 2.1900357 * fZec4[i];
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec35[i] = 6.7063036 * fZec5[i];
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec36[i] = 1.7063034 * fZec5[i];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec37[i] = 5.0063033 * fZec5[i];
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec38[i] = 2.0914886 * fZec5[i];
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec39[i] = 2.1900357 * fZec5[i];
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec40[i] = 6.7063036 * fZec6[i];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec41[i] = 1.7063034 * fZec6[i];
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec42[i] = 5.0063033 * fZec6[i];
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec43[i] = 2.0914886 * fZec6[i];
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec44[i] = 2.1900357 * fZec6[i];
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec45[i] = 6.7063036 * fZec7[i];
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec46[i] = 1.7063034 * fZec7[i];
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec47[i] = 5.0063033 * fZec7[i];
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec48[i] = 2.0914886 * fZec7[i];
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec49[i] = 2.1900357 * fZec7[i];
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec50[i] = 6.7063036 * fZec9[i];
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec51[i] = 1.7063034 * fZec9[i];
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec52[i] = 5.0063033 * fZec9[i];
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec53[i] = 2.0914886 * fZec9[i];
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec54[i] = 2.1900357 * fZec9[i];
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec55[i] = 6.7063036 * fZec8[i];
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec56[i] = 1.7063034 * fZec8[i];
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec57[i] = 5.0063033 * fZec8[i];
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec58[i] = 2.1900357 * fZec8[i];
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec59[i] = 2.0914886 * fZec8[i];
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec10[i] = 6.7063036 * fZec0[i];
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec11[i] = 1.7063034 * fZec0[i];
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec12[i] = 5.0063033 * fZec0[i];
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec13[i] = 2.0914886 * fZec0[i];
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec14[i] = 2.1900357 * fZec0[i];
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec15[i] = 6.7063036 * fZec1[i];
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec16[i] = 1.7063034 * fZec1[i];
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec17[i] = 5.0063033 * fZec1[i];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec18[i] = 2.0914886 * fZec1[i];
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec19[i] = 2.1900357 * fZec1[i];
			}
			/* Vectorizable loop 65 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec20[i] = 6.7063036 * fZec2[i];
			}
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec21[i] = 1.7063034 * fZec2[i];
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec22[i] = 5.0063033 * fZec2[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec23[i] = 2.0914886 * fZec2[i];
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec24[i] = 2.1900357 * fZec2[i];
			}
			/* Recursive loop 70 */
			/* Pre code */
			fYec0_idx = (fYec0_idx + fYec0_idx_save) & 255;
			for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
				fRec1_tmp[j2] = fRec1_perm[j2];
			}
			for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
				fRec0_tmp[j4] = fRec0_perm[j4];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[(i + fYec0_idx) & 255] = fSlow2 * fRec0[i - 1] + 5.2995043 * fZec0[i];
				fRec1[i] = fSlow1 * fYec0[(i + fYec0_idx - iSlow4) & 255] - (fSlow5 * fRec1[i - 1] + fConst6 * fRec1[i - 2]);
				fRec0[i] = fConst7 * (fRec1[i] - fRec1[i - 2]);
			}
			/* Post code */
			fYec0_idx_save = vsize;
			for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
				fRec1_perm[j3] = fRec1_tmp[vsize + j3];
			}
			for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
				fRec0_perm[j5] = fRec0_tmp[vsize + j5];
			}
			/* Recursive loop 71 */
			/* Pre code */
			fYec1_idx = (fYec1_idx + fYec1_idx_save) & 255;
			for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
				fRec3_tmp[j8] = fRec3_perm[j8];
			}
			for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
				fRec2_tmp[j10] = fRec2_perm[j10];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[(i + fYec1_idx) & 255] = fSlow2 * fRec2[i - 1] + 5.2995043 * fZec1[i];
				fRec3[i] = fSlow7 * fYec1[(i + fYec1_idx - iSlow9) & 255] - (fSlow10 * fRec3[i - 1] + fConst6 * fRec3[i - 2]);
				fRec2[i] = fConst7 * (fRec3[i] - fRec3[i - 2]);
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
				fRec3_perm[j9] = fRec3_tmp[vsize + j9];
			}
			for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
				fRec2_perm[j11] = fRec2_tmp[vsize + j11];
			}
			/* Recursive loop 72 */
			/* Pre code */
			fYec39_idx = (fYec39_idx + fYec39_idx_save) & 1023;
			for (int j176 = 0; j176 < 4; j176 = j176 + 1) {
				fRec79_tmp[j176] = fRec79_perm[j176];
			}
			for (int j178 = 0; j178 < 4; j178 = j178 + 1) {
				fRec78_tmp[j178] = fRec78_perm[j178];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec39[(i + fYec39_idx) & 1023] = fSlow2 * fRec78[i - 1] + fZec24[i];
				fRec79[i] = fSlow138 * fYec39[(i + fYec39_idx - iSlow139) & 1023] - (fSlow140 * fRec79[i - 1] + fConst6 * fRec79[i - 2]);
				fRec78[i] = fConst7 * (fRec79[i] - fRec79[i - 2]);
			}
			/* Post code */
			fYec39_idx_save = vsize;
			for (int j177 = 0; j177 < 4; j177 = j177 + 1) {
				fRec79_perm[j177] = fRec79_tmp[vsize + j177];
			}
			for (int j179 = 0; j179 < 4; j179 = j179 + 1) {
				fRec78_perm[j179] = fRec78_tmp[vsize + j179];
			}
			/* Recursive loop 73 */
			/* Pre code */
			fYec40_idx = (fYec40_idx + fYec40_idx_save) & 127;
			for (int j180 = 0; j180 < 4; j180 = j180 + 1) {
				fRec81_tmp[j180] = fRec81_perm[j180];
			}
			for (int j182 = 0; j182 < 4; j182 = j182 + 1) {
				fRec80_tmp[j182] = fRec80_perm[j182];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec40[(i + fYec40_idx) & 127] = fZec25[i] + fSlow2 * fRec80[i - 1];
				fRec81[i] = fSlow141 * fYec40[(i + fYec40_idx - iSlow142) & 127] - (fSlow143 * fRec81[i - 1] + fConst6 * fRec81[i - 2]);
				fRec80[i] = fConst7 * (fRec81[i] - fRec81[i - 2]);
			}
			/* Post code */
			fYec40_idx_save = vsize;
			for (int j181 = 0; j181 < 4; j181 = j181 + 1) {
				fRec81_perm[j181] = fRec81_tmp[vsize + j181];
			}
			for (int j183 = 0; j183 < 4; j183 = j183 + 1) {
				fRec80_perm[j183] = fRec80_tmp[vsize + j183];
			}
			/* Recursive loop 74 */
			/* Pre code */
			fYec41_idx = (fYec41_idx + fYec41_idx_save) & 127;
			for (int j184 = 0; j184 < 4; j184 = j184 + 1) {
				fRec83_tmp[j184] = fRec83_perm[j184];
			}
			for (int j186 = 0; j186 < 4; j186 = j186 + 1) {
				fRec82_tmp[j186] = fRec82_perm[j186];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec41[(i + fYec41_idx) & 127] = fSlow2 * fRec82[i - 1] + fZec25[i];
				fRec83[i] = fSlow144 * fYec41[(i + fYec41_idx - iSlow145) & 127] - (fSlow146 * fRec83[i - 1] + fConst6 * fRec83[i - 2]);
				fRec82[i] = fConst7 * (fRec83[i] - fRec83[i - 2]);
			}
			/* Post code */
			fYec41_idx_save = vsize;
			for (int j185 = 0; j185 < 4; j185 = j185 + 1) {
				fRec83_perm[j185] = fRec83_tmp[vsize + j185];
			}
			for (int j187 = 0; j187 < 4; j187 = j187 + 1) {
				fRec82_perm[j187] = fRec82_tmp[vsize + j187];
			}
			/* Recursive loop 75 */
			/* Pre code */
			fYec42_idx = (fYec42_idx + fYec42_idx_save) & 127;
			for (int j188 = 0; j188 < 4; j188 = j188 + 1) {
				fRec85_tmp[j188] = fRec85_perm[j188];
			}
			for (int j190 = 0; j190 < 4; j190 = j190 + 1) {
				fRec84_tmp[j190] = fRec84_perm[j190];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec42[(i + fYec42_idx) & 127] = fZec26[i] + fSlow2 * fRec84[i - 1];
				fRec85[i] = fSlow147 * fYec42[(i + fYec42_idx - iSlow148) & 127] - (fSlow149 * fRec85[i - 1] + fConst6 * fRec85[i - 2]);
				fRec84[i] = fConst7 * (fRec85[i] - fRec85[i - 2]);
			}
			/* Post code */
			fYec42_idx_save = vsize;
			for (int j189 = 0; j189 < 4; j189 = j189 + 1) {
				fRec85_perm[j189] = fRec85_tmp[vsize + j189];
			}
			for (int j191 = 0; j191 < 4; j191 = j191 + 1) {
				fRec84_perm[j191] = fRec84_tmp[vsize + j191];
			}
			/* Recursive loop 76 */
			/* Pre code */
			fYec43_idx = (fYec43_idx + fYec43_idx_save) & 127;
			for (int j192 = 0; j192 < 4; j192 = j192 + 1) {
				fRec87_tmp[j192] = fRec87_perm[j192];
			}
			for (int j194 = 0; j194 < 4; j194 = j194 + 1) {
				fRec86_tmp[j194] = fRec86_perm[j194];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec43[(i + fYec43_idx) & 127] = fSlow2 * fRec86[i - 1] + fZec26[i];
				fRec87[i] = fSlow150 * fYec43[(i + fYec43_idx - iSlow151) & 127] - (fSlow152 * fRec87[i - 1] + fConst6 * fRec87[i - 2]);
				fRec86[i] = fConst7 * (fRec87[i] - fRec87[i - 2]);
			}
			/* Post code */
			fYec43_idx_save = vsize;
			for (int j193 = 0; j193 < 4; j193 = j193 + 1) {
				fRec87_perm[j193] = fRec87_tmp[vsize + j193];
			}
			for (int j195 = 0; j195 < 4; j195 = j195 + 1) {
				fRec86_perm[j195] = fRec86_tmp[vsize + j195];
			}
			/* Recursive loop 77 */
			/* Pre code */
			fYec44_idx = (fYec44_idx + fYec44_idx_save) & 127;
			for (int j196 = 0; j196 < 4; j196 = j196 + 1) {
				fRec89_tmp[j196] = fRec89_perm[j196];
			}
			for (int j198 = 0; j198 < 4; j198 = j198 + 1) {
				fRec88_tmp[j198] = fRec88_perm[j198];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec44[(i + fYec44_idx) & 127] = fZec27[i] + fSlow2 * fRec88[i - 1];
				fRec89[i] = fSlow153 * fYec44[(i + fYec44_idx - iSlow154) & 127] - (fSlow155 * fRec89[i - 1] + fConst6 * fRec89[i - 2]);
				fRec88[i] = fConst7 * (fRec89[i] - fRec89[i - 2]);
			}
			/* Post code */
			fYec44_idx_save = vsize;
			for (int j197 = 0; j197 < 4; j197 = j197 + 1) {
				fRec89_perm[j197] = fRec89_tmp[vsize + j197];
			}
			for (int j199 = 0; j199 < 4; j199 = j199 + 1) {
				fRec88_perm[j199] = fRec88_tmp[vsize + j199];
			}
			/* Recursive loop 78 */
			/* Pre code */
			fYec45_idx = (fYec45_idx + fYec45_idx_save) & 127;
			for (int j200 = 0; j200 < 4; j200 = j200 + 1) {
				fRec91_tmp[j200] = fRec91_perm[j200];
			}
			for (int j202 = 0; j202 < 4; j202 = j202 + 1) {
				fRec90_tmp[j202] = fRec90_perm[j202];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec45[(i + fYec45_idx) & 127] = fSlow2 * fRec90[i - 1] + fZec27[i];
				fRec91[i] = fSlow156 * fYec45[(i + fYec45_idx - iSlow157) & 127] - (fSlow158 * fRec91[i - 1] + fConst6 * fRec91[i - 2]);
				fRec90[i] = fConst7 * (fRec91[i] - fRec91[i - 2]);
			}
			/* Post code */
			fYec45_idx_save = vsize;
			for (int j201 = 0; j201 < 4; j201 = j201 + 1) {
				fRec91_perm[j201] = fRec91_tmp[vsize + j201];
			}
			for (int j203 = 0; j203 < 4; j203 = j203 + 1) {
				fRec90_perm[j203] = fRec90_tmp[vsize + j203];
			}
			/* Recursive loop 79 */
			/* Pre code */
			fYec46_idx = (fYec46_idx + fYec46_idx_save) & 511;
			for (int j204 = 0; j204 < 4; j204 = j204 + 1) {
				fRec93_tmp[j204] = fRec93_perm[j204];
			}
			for (int j206 = 0; j206 < 4; j206 = j206 + 1) {
				fRec92_tmp[j206] = fRec92_perm[j206];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec46[(i + fYec46_idx) & 511] = fZec28[i] + fSlow2 * fRec92[i - 1];
				fRec93[i] = fSlow159 * fYec46[(i + fYec46_idx - iSlow160) & 511] - (fSlow161 * fRec93[i - 1] + fConst6 * fRec93[i - 2]);
				fRec92[i] = fConst7 * (fRec93[i] - fRec93[i - 2]);
			}
			/* Post code */
			fYec46_idx_save = vsize;
			for (int j205 = 0; j205 < 4; j205 = j205 + 1) {
				fRec93_perm[j205] = fRec93_tmp[vsize + j205];
			}
			for (int j207 = 0; j207 < 4; j207 = j207 + 1) {
				fRec92_perm[j207] = fRec92_tmp[vsize + j207];
			}
			/* Recursive loop 80 */
			/* Pre code */
			fYec47_idx = (fYec47_idx + fYec47_idx_save) & 511;
			for (int j208 = 0; j208 < 4; j208 = j208 + 1) {
				fRec95_tmp[j208] = fRec95_perm[j208];
			}
			for (int j210 = 0; j210 < 4; j210 = j210 + 1) {
				fRec94_tmp[j210] = fRec94_perm[j210];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec47[(i + fYec47_idx) & 511] = fSlow2 * fRec94[i - 1] + fZec28[i];
				fRec95[i] = fSlow162 * fYec47[(i + fYec47_idx - iSlow163) & 511] - (fSlow164 * fRec95[i - 1] + fConst6 * fRec95[i - 2]);
				fRec94[i] = fConst7 * (fRec95[i] - fRec95[i - 2]);
			}
			/* Post code */
			fYec47_idx_save = vsize;
			for (int j209 = 0; j209 < 4; j209 = j209 + 1) {
				fRec95_perm[j209] = fRec95_tmp[vsize + j209];
			}
			for (int j211 = 0; j211 < 4; j211 = j211 + 1) {
				fRec94_perm[j211] = fRec94_tmp[vsize + j211];
			}
			/* Recursive loop 81 */
			/* Pre code */
			fYec48_idx = (fYec48_idx + fYec48_idx_save) & 1023;
			for (int j212 = 0; j212 < 4; j212 = j212 + 1) {
				fRec97_tmp[j212] = fRec97_perm[j212];
			}
			for (int j214 = 0; j214 < 4; j214 = j214 + 1) {
				fRec96_tmp[j214] = fRec96_perm[j214];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec48[(i + fYec48_idx) & 1023] = fZec29[i] + fSlow2 * fRec96[i - 1];
				fRec97[i] = fSlow165 * fYec48[(i + fYec48_idx - iSlow166) & 1023] - (fSlow167 * fRec97[i - 1] + fConst6 * fRec97[i - 2]);
				fRec96[i] = fConst7 * (fRec97[i] - fRec97[i - 2]);
			}
			/* Post code */
			fYec48_idx_save = vsize;
			for (int j213 = 0; j213 < 4; j213 = j213 + 1) {
				fRec97_perm[j213] = fRec97_tmp[vsize + j213];
			}
			for (int j215 = 0; j215 < 4; j215 = j215 + 1) {
				fRec96_perm[j215] = fRec96_tmp[vsize + j215];
			}
			/* Recursive loop 82 */
			/* Pre code */
			fYec49_idx = (fYec49_idx + fYec49_idx_save) & 1023;
			for (int j216 = 0; j216 < 4; j216 = j216 + 1) {
				fRec99_tmp[j216] = fRec99_perm[j216];
			}
			for (int j218 = 0; j218 < 4; j218 = j218 + 1) {
				fRec98_tmp[j218] = fRec98_perm[j218];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec49[(i + fYec49_idx) & 1023] = fSlow2 * fRec98[i - 1] + fZec29[i];
				fRec99[i] = fSlow168 * fYec49[(i + fYec49_idx - iSlow169) & 1023] - (fSlow170 * fRec99[i - 1] + fConst6 * fRec99[i - 2]);
				fRec98[i] = fConst7 * (fRec99[i] - fRec99[i - 2]);
			}
			/* Post code */
			fYec49_idx_save = vsize;
			for (int j217 = 0; j217 < 4; j217 = j217 + 1) {
				fRec99_perm[j217] = fRec99_tmp[vsize + j217];
			}
			for (int j219 = 0; j219 < 4; j219 = j219 + 1) {
				fRec98_perm[j219] = fRec98_tmp[vsize + j219];
			}
			/* Recursive loop 83 */
			/* Pre code */
			fYec50_idx = (fYec50_idx + fYec50_idx_save) & 127;
			for (int j220 = 0; j220 < 4; j220 = j220 + 1) {
				fRec101_tmp[j220] = fRec101_perm[j220];
			}
			for (int j222 = 0; j222 < 4; j222 = j222 + 1) {
				fRec100_tmp[j222] = fRec100_perm[j222];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec50[(i + fYec50_idx) & 127] = fZec30[i] + fSlow2 * fRec100[i - 1];
				fRec101[i] = fSlow171 * fYec50[(i + fYec50_idx - iSlow172) & 127] - (fSlow173 * fRec101[i - 1] + fConst6 * fRec101[i - 2]);
				fRec100[i] = fConst7 * (fRec101[i] - fRec101[i - 2]);
			}
			/* Post code */
			fYec50_idx_save = vsize;
			for (int j221 = 0; j221 < 4; j221 = j221 + 1) {
				fRec101_perm[j221] = fRec101_tmp[vsize + j221];
			}
			for (int j223 = 0; j223 < 4; j223 = j223 + 1) {
				fRec100_perm[j223] = fRec100_tmp[vsize + j223];
			}
			/* Recursive loop 84 */
			/* Pre code */
			fYec51_idx = (fYec51_idx + fYec51_idx_save) & 127;
			for (int j224 = 0; j224 < 4; j224 = j224 + 1) {
				fRec103_tmp[j224] = fRec103_perm[j224];
			}
			for (int j226 = 0; j226 < 4; j226 = j226 + 1) {
				fRec102_tmp[j226] = fRec102_perm[j226];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec51[(i + fYec51_idx) & 127] = fSlow2 * fRec102[i - 1] + fZec30[i];
				fRec103[i] = fSlow174 * fYec51[(i + fYec51_idx - iSlow175) & 127] - (fSlow176 * fRec103[i - 1] + fConst6 * fRec103[i - 2]);
				fRec102[i] = fConst7 * (fRec103[i] - fRec103[i - 2]);
			}
			/* Post code */
			fYec51_idx_save = vsize;
			for (int j225 = 0; j225 < 4; j225 = j225 + 1) {
				fRec103_perm[j225] = fRec103_tmp[vsize + j225];
			}
			for (int j227 = 0; j227 < 4; j227 = j227 + 1) {
				fRec102_perm[j227] = fRec102_tmp[vsize + j227];
			}
			/* Recursive loop 85 */
			/* Pre code */
			fYec52_idx = (fYec52_idx + fYec52_idx_save) & 127;
			for (int j228 = 0; j228 < 4; j228 = j228 + 1) {
				fRec105_tmp[j228] = fRec105_perm[j228];
			}
			for (int j230 = 0; j230 < 4; j230 = j230 + 1) {
				fRec104_tmp[j230] = fRec104_perm[j230];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec52[(i + fYec52_idx) & 127] = fZec31[i] + fSlow2 * fRec104[i - 1];
				fRec105[i] = fSlow177 * fYec52[(i + fYec52_idx - iSlow178) & 127] - (fSlow179 * fRec105[i - 1] + fConst6 * fRec105[i - 2]);
				fRec104[i] = fConst7 * (fRec105[i] - fRec105[i - 2]);
			}
			/* Post code */
			fYec52_idx_save = vsize;
			for (int j229 = 0; j229 < 4; j229 = j229 + 1) {
				fRec105_perm[j229] = fRec105_tmp[vsize + j229];
			}
			for (int j231 = 0; j231 < 4; j231 = j231 + 1) {
				fRec104_perm[j231] = fRec104_tmp[vsize + j231];
			}
			/* Recursive loop 86 */
			/* Pre code */
			fYec53_idx = (fYec53_idx + fYec53_idx_save) & 127;
			for (int j232 = 0; j232 < 4; j232 = j232 + 1) {
				fRec107_tmp[j232] = fRec107_perm[j232];
			}
			for (int j234 = 0; j234 < 4; j234 = j234 + 1) {
				fRec106_tmp[j234] = fRec106_perm[j234];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec53[(i + fYec53_idx) & 127] = fSlow2 * fRec106[i - 1] + fZec31[i];
				fRec107[i] = fSlow180 * fYec53[(i + fYec53_idx - iSlow181) & 127] - (fSlow182 * fRec107[i - 1] + fConst6 * fRec107[i - 2]);
				fRec106[i] = fConst7 * (fRec107[i] - fRec107[i - 2]);
			}
			/* Post code */
			fYec53_idx_save = vsize;
			for (int j233 = 0; j233 < 4; j233 = j233 + 1) {
				fRec107_perm[j233] = fRec107_tmp[vsize + j233];
			}
			for (int j235 = 0; j235 < 4; j235 = j235 + 1) {
				fRec106_perm[j235] = fRec106_tmp[vsize + j235];
			}
			/* Recursive loop 87 */
			/* Pre code */
			fYec54_idx = (fYec54_idx + fYec54_idx_save) & 127;
			for (int j236 = 0; j236 < 4; j236 = j236 + 1) {
				fRec109_tmp[j236] = fRec109_perm[j236];
			}
			for (int j238 = 0; j238 < 4; j238 = j238 + 1) {
				fRec108_tmp[j238] = fRec108_perm[j238];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec54[(i + fYec54_idx) & 127] = fZec32[i] + fSlow2 * fRec108[i - 1];
				fRec109[i] = fSlow183 * fYec54[(i + fYec54_idx - iSlow184) & 127] - (fSlow185 * fRec109[i - 1] + fConst6 * fRec109[i - 2]);
				fRec108[i] = fConst7 * (fRec109[i] - fRec109[i - 2]);
			}
			/* Post code */
			fYec54_idx_save = vsize;
			for (int j237 = 0; j237 < 4; j237 = j237 + 1) {
				fRec109_perm[j237] = fRec109_tmp[vsize + j237];
			}
			for (int j239 = 0; j239 < 4; j239 = j239 + 1) {
				fRec108_perm[j239] = fRec108_tmp[vsize + j239];
			}
			/* Recursive loop 88 */
			/* Pre code */
			fYec55_idx = (fYec55_idx + fYec55_idx_save) & 127;
			for (int j240 = 0; j240 < 4; j240 = j240 + 1) {
				fRec111_tmp[j240] = fRec111_perm[j240];
			}
			for (int j242 = 0; j242 < 4; j242 = j242 + 1) {
				fRec110_tmp[j242] = fRec110_perm[j242];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec55[(i + fYec55_idx) & 127] = fSlow2 * fRec110[i - 1] + fZec32[i];
				fRec111[i] = fSlow186 * fYec55[(i + fYec55_idx - iSlow187) & 127] - (fSlow188 * fRec111[i - 1] + fConst6 * fRec111[i - 2]);
				fRec110[i] = fConst7 * (fRec111[i] - fRec111[i - 2]);
			}
			/* Post code */
			fYec55_idx_save = vsize;
			for (int j241 = 0; j241 < 4; j241 = j241 + 1) {
				fRec111_perm[j241] = fRec111_tmp[vsize + j241];
			}
			for (int j243 = 0; j243 < 4; j243 = j243 + 1) {
				fRec110_perm[j243] = fRec110_tmp[vsize + j243];
			}
			/* Recursive loop 89 */
			/* Pre code */
			fYec56_idx = (fYec56_idx + fYec56_idx_save) & 511;
			for (int j244 = 0; j244 < 4; j244 = j244 + 1) {
				fRec113_tmp[j244] = fRec113_perm[j244];
			}
			for (int j246 = 0; j246 < 4; j246 = j246 + 1) {
				fRec112_tmp[j246] = fRec112_perm[j246];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec56[(i + fYec56_idx) & 511] = fZec33[i] + fSlow2 * fRec112[i - 1];
				fRec113[i] = fSlow189 * fYec56[(i + fYec56_idx - iSlow190) & 511] - (fSlow191 * fRec113[i - 1] + fConst6 * fRec113[i - 2]);
				fRec112[i] = fConst7 * (fRec113[i] - fRec113[i - 2]);
			}
			/* Post code */
			fYec56_idx_save = vsize;
			for (int j245 = 0; j245 < 4; j245 = j245 + 1) {
				fRec113_perm[j245] = fRec113_tmp[vsize + j245];
			}
			for (int j247 = 0; j247 < 4; j247 = j247 + 1) {
				fRec112_perm[j247] = fRec112_tmp[vsize + j247];
			}
			/* Recursive loop 90 */
			/* Pre code */
			fYec57_idx = (fYec57_idx + fYec57_idx_save) & 511;
			for (int j248 = 0; j248 < 4; j248 = j248 + 1) {
				fRec115_tmp[j248] = fRec115_perm[j248];
			}
			for (int j250 = 0; j250 < 4; j250 = j250 + 1) {
				fRec114_tmp[j250] = fRec114_perm[j250];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec57[(i + fYec57_idx) & 511] = fSlow2 * fRec114[i - 1] + fZec33[i];
				fRec115[i] = fSlow192 * fYec57[(i + fYec57_idx - iSlow193) & 511] - (fSlow194 * fRec115[i - 1] + fConst6 * fRec115[i - 2]);
				fRec114[i] = fConst7 * (fRec115[i] - fRec115[i - 2]);
			}
			/* Post code */
			fYec57_idx_save = vsize;
			for (int j249 = 0; j249 < 4; j249 = j249 + 1) {
				fRec115_perm[j249] = fRec115_tmp[vsize + j249];
			}
			for (int j251 = 0; j251 < 4; j251 = j251 + 1) {
				fRec114_perm[j251] = fRec114_tmp[vsize + j251];
			}
			/* Recursive loop 91 */
			/* Pre code */
			fYec58_idx = (fYec58_idx + fYec58_idx_save) & 1023;
			for (int j252 = 0; j252 < 4; j252 = j252 + 1) {
				fRec117_tmp[j252] = fRec117_perm[j252];
			}
			for (int j254 = 0; j254 < 4; j254 = j254 + 1) {
				fRec116_tmp[j254] = fRec116_perm[j254];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec58[(i + fYec58_idx) & 1023] = fZec34[i] + fSlow2 * fRec116[i - 1];
				fRec117[i] = fSlow195 * fYec58[(i + fYec58_idx - iSlow196) & 1023] - (fSlow197 * fRec117[i - 1] + fConst6 * fRec117[i - 2]);
				fRec116[i] = fConst7 * (fRec117[i] - fRec117[i - 2]);
			}
			/* Post code */
			fYec58_idx_save = vsize;
			for (int j253 = 0; j253 < 4; j253 = j253 + 1) {
				fRec117_perm[j253] = fRec117_tmp[vsize + j253];
			}
			for (int j255 = 0; j255 < 4; j255 = j255 + 1) {
				fRec116_perm[j255] = fRec116_tmp[vsize + j255];
			}
			/* Recursive loop 92 */
			/* Pre code */
			fYec59_idx = (fYec59_idx + fYec59_idx_save) & 1023;
			for (int j256 = 0; j256 < 4; j256 = j256 + 1) {
				fRec119_tmp[j256] = fRec119_perm[j256];
			}
			for (int j258 = 0; j258 < 4; j258 = j258 + 1) {
				fRec118_tmp[j258] = fRec118_perm[j258];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec59[(i + fYec59_idx) & 1023] = fSlow2 * fRec118[i - 1] + fZec34[i];
				fRec119[i] = fSlow198 * fYec59[(i + fYec59_idx - iSlow199) & 1023] - (fSlow200 * fRec119[i - 1] + fConst6 * fRec119[i - 2]);
				fRec118[i] = fConst7 * (fRec119[i] - fRec119[i - 2]);
			}
			/* Post code */
			fYec59_idx_save = vsize;
			for (int j257 = 0; j257 < 4; j257 = j257 + 1) {
				fRec119_perm[j257] = fRec119_tmp[vsize + j257];
			}
			for (int j259 = 0; j259 < 4; j259 = j259 + 1) {
				fRec118_perm[j259] = fRec118_tmp[vsize + j259];
			}
			/* Recursive loop 93 */
			/* Pre code */
			fYec60_idx = (fYec60_idx + fYec60_idx_save) & 127;
			for (int j260 = 0; j260 < 4; j260 = j260 + 1) {
				fRec121_tmp[j260] = fRec121_perm[j260];
			}
			for (int j262 = 0; j262 < 4; j262 = j262 + 1) {
				fRec120_tmp[j262] = fRec120_perm[j262];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec60[(i + fYec60_idx) & 127] = fZec35[i] + fSlow2 * fRec120[i - 1];
				fRec121[i] = fSlow201 * fYec60[(i + fYec60_idx - iSlow202) & 127] - (fSlow203 * fRec121[i - 1] + fConst6 * fRec121[i - 2]);
				fRec120[i] = fConst7 * (fRec121[i] - fRec121[i - 2]);
			}
			/* Post code */
			fYec60_idx_save = vsize;
			for (int j261 = 0; j261 < 4; j261 = j261 + 1) {
				fRec121_perm[j261] = fRec121_tmp[vsize + j261];
			}
			for (int j263 = 0; j263 < 4; j263 = j263 + 1) {
				fRec120_perm[j263] = fRec120_tmp[vsize + j263];
			}
			/* Recursive loop 94 */
			/* Pre code */
			fYec61_idx = (fYec61_idx + fYec61_idx_save) & 127;
			for (int j264 = 0; j264 < 4; j264 = j264 + 1) {
				fRec123_tmp[j264] = fRec123_perm[j264];
			}
			for (int j266 = 0; j266 < 4; j266 = j266 + 1) {
				fRec122_tmp[j266] = fRec122_perm[j266];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec61[(i + fYec61_idx) & 127] = fSlow2 * fRec122[i - 1] + fZec35[i];
				fRec123[i] = fSlow204 * fYec61[(i + fYec61_idx - iSlow205) & 127] - (fSlow206 * fRec123[i - 1] + fConst6 * fRec123[i - 2]);
				fRec122[i] = fConst7 * (fRec123[i] - fRec123[i - 2]);
			}
			/* Post code */
			fYec61_idx_save = vsize;
			for (int j265 = 0; j265 < 4; j265 = j265 + 1) {
				fRec123_perm[j265] = fRec123_tmp[vsize + j265];
			}
			for (int j267 = 0; j267 < 4; j267 = j267 + 1) {
				fRec122_perm[j267] = fRec122_tmp[vsize + j267];
			}
			/* Recursive loop 95 */
			/* Pre code */
			fYec62_idx = (fYec62_idx + fYec62_idx_save) & 127;
			for (int j268 = 0; j268 < 4; j268 = j268 + 1) {
				fRec125_tmp[j268] = fRec125_perm[j268];
			}
			for (int j270 = 0; j270 < 4; j270 = j270 + 1) {
				fRec124_tmp[j270] = fRec124_perm[j270];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec62[(i + fYec62_idx) & 127] = fZec36[i] + fSlow2 * fRec124[i - 1];
				fRec125[i] = fSlow207 * fYec62[(i + fYec62_idx - iSlow208) & 127] - (fSlow209 * fRec125[i - 1] + fConst6 * fRec125[i - 2]);
				fRec124[i] = fConst7 * (fRec125[i] - fRec125[i - 2]);
			}
			/* Post code */
			fYec62_idx_save = vsize;
			for (int j269 = 0; j269 < 4; j269 = j269 + 1) {
				fRec125_perm[j269] = fRec125_tmp[vsize + j269];
			}
			for (int j271 = 0; j271 < 4; j271 = j271 + 1) {
				fRec124_perm[j271] = fRec124_tmp[vsize + j271];
			}
			/* Recursive loop 96 */
			/* Pre code */
			fYec63_idx = (fYec63_idx + fYec63_idx_save) & 127;
			for (int j272 = 0; j272 < 4; j272 = j272 + 1) {
				fRec127_tmp[j272] = fRec127_perm[j272];
			}
			for (int j274 = 0; j274 < 4; j274 = j274 + 1) {
				fRec126_tmp[j274] = fRec126_perm[j274];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec63[(i + fYec63_idx) & 127] = fSlow2 * fRec126[i - 1] + fZec36[i];
				fRec127[i] = fSlow210 * fYec63[(i + fYec63_idx - iSlow211) & 127] - (fSlow212 * fRec127[i - 1] + fConst6 * fRec127[i - 2]);
				fRec126[i] = fConst7 * (fRec127[i] - fRec127[i - 2]);
			}
			/* Post code */
			fYec63_idx_save = vsize;
			for (int j273 = 0; j273 < 4; j273 = j273 + 1) {
				fRec127_perm[j273] = fRec127_tmp[vsize + j273];
			}
			for (int j275 = 0; j275 < 4; j275 = j275 + 1) {
				fRec126_perm[j275] = fRec126_tmp[vsize + j275];
			}
			/* Recursive loop 97 */
			/* Pre code */
			fYec64_idx = (fYec64_idx + fYec64_idx_save) & 127;
			for (int j276 = 0; j276 < 4; j276 = j276 + 1) {
				fRec129_tmp[j276] = fRec129_perm[j276];
			}
			for (int j278 = 0; j278 < 4; j278 = j278 + 1) {
				fRec128_tmp[j278] = fRec128_perm[j278];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec64[(i + fYec64_idx) & 127] = fZec37[i] + fSlow2 * fRec128[i - 1];
				fRec129[i] = fSlow213 * fYec64[(i + fYec64_idx - iSlow214) & 127] - (fSlow215 * fRec129[i - 1] + fConst6 * fRec129[i - 2]);
				fRec128[i] = fConst7 * (fRec129[i] - fRec129[i - 2]);
			}
			/* Post code */
			fYec64_idx_save = vsize;
			for (int j277 = 0; j277 < 4; j277 = j277 + 1) {
				fRec129_perm[j277] = fRec129_tmp[vsize + j277];
			}
			for (int j279 = 0; j279 < 4; j279 = j279 + 1) {
				fRec128_perm[j279] = fRec128_tmp[vsize + j279];
			}
			/* Recursive loop 98 */
			/* Pre code */
			fYec65_idx = (fYec65_idx + fYec65_idx_save) & 127;
			for (int j280 = 0; j280 < 4; j280 = j280 + 1) {
				fRec131_tmp[j280] = fRec131_perm[j280];
			}
			for (int j282 = 0; j282 < 4; j282 = j282 + 1) {
				fRec130_tmp[j282] = fRec130_perm[j282];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec65[(i + fYec65_idx) & 127] = fSlow2 * fRec130[i - 1] + fZec37[i];
				fRec131[i] = fSlow216 * fYec65[(i + fYec65_idx - iSlow217) & 127] - (fSlow218 * fRec131[i - 1] + fConst6 * fRec131[i - 2]);
				fRec130[i] = fConst7 * (fRec131[i] - fRec131[i - 2]);
			}
			/* Post code */
			fYec65_idx_save = vsize;
			for (int j281 = 0; j281 < 4; j281 = j281 + 1) {
				fRec131_perm[j281] = fRec131_tmp[vsize + j281];
			}
			for (int j283 = 0; j283 < 4; j283 = j283 + 1) {
				fRec130_perm[j283] = fRec130_tmp[vsize + j283];
			}
			/* Recursive loop 99 */
			/* Pre code */
			fYec66_idx = (fYec66_idx + fYec66_idx_save) & 511;
			for (int j284 = 0; j284 < 4; j284 = j284 + 1) {
				fRec133_tmp[j284] = fRec133_perm[j284];
			}
			for (int j286 = 0; j286 < 4; j286 = j286 + 1) {
				fRec132_tmp[j286] = fRec132_perm[j286];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec66[(i + fYec66_idx) & 511] = fZec38[i] + fSlow2 * fRec132[i - 1];
				fRec133[i] = fSlow219 * fYec66[(i + fYec66_idx - iSlow220) & 511] - (fSlow221 * fRec133[i - 1] + fConst6 * fRec133[i - 2]);
				fRec132[i] = fConst7 * (fRec133[i] - fRec133[i - 2]);
			}
			/* Post code */
			fYec66_idx_save = vsize;
			for (int j285 = 0; j285 < 4; j285 = j285 + 1) {
				fRec133_perm[j285] = fRec133_tmp[vsize + j285];
			}
			for (int j287 = 0; j287 < 4; j287 = j287 + 1) {
				fRec132_perm[j287] = fRec132_tmp[vsize + j287];
			}
			/* Recursive loop 100 */
			/* Pre code */
			fYec67_idx = (fYec67_idx + fYec67_idx_save) & 511;
			for (int j288 = 0; j288 < 4; j288 = j288 + 1) {
				fRec135_tmp[j288] = fRec135_perm[j288];
			}
			for (int j290 = 0; j290 < 4; j290 = j290 + 1) {
				fRec134_tmp[j290] = fRec134_perm[j290];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec67[(i + fYec67_idx) & 511] = fSlow2 * fRec134[i - 1] + fZec38[i];
				fRec135[i] = fSlow222 * fYec67[(i + fYec67_idx - iSlow223) & 511] - (fSlow224 * fRec135[i - 1] + fConst6 * fRec135[i - 2]);
				fRec134[i] = fConst7 * (fRec135[i] - fRec135[i - 2]);
			}
			/* Post code */
			fYec67_idx_save = vsize;
			for (int j289 = 0; j289 < 4; j289 = j289 + 1) {
				fRec135_perm[j289] = fRec135_tmp[vsize + j289];
			}
			for (int j291 = 0; j291 < 4; j291 = j291 + 1) {
				fRec134_perm[j291] = fRec134_tmp[vsize + j291];
			}
			/* Recursive loop 101 */
			/* Pre code */
			fYec68_idx = (fYec68_idx + fYec68_idx_save) & 1023;
			for (int j292 = 0; j292 < 4; j292 = j292 + 1) {
				fRec137_tmp[j292] = fRec137_perm[j292];
			}
			for (int j294 = 0; j294 < 4; j294 = j294 + 1) {
				fRec136_tmp[j294] = fRec136_perm[j294];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec68[(i + fYec68_idx) & 1023] = fZec39[i] + fSlow2 * fRec136[i - 1];
				fRec137[i] = fSlow225 * fYec68[(i + fYec68_idx - iSlow226) & 1023] - (fSlow227 * fRec137[i - 1] + fConst6 * fRec137[i - 2]);
				fRec136[i] = fConst7 * (fRec137[i] - fRec137[i - 2]);
			}
			/* Post code */
			fYec68_idx_save = vsize;
			for (int j293 = 0; j293 < 4; j293 = j293 + 1) {
				fRec137_perm[j293] = fRec137_tmp[vsize + j293];
			}
			for (int j295 = 0; j295 < 4; j295 = j295 + 1) {
				fRec136_perm[j295] = fRec136_tmp[vsize + j295];
			}
			/* Recursive loop 102 */
			/* Pre code */
			fYec69_idx = (fYec69_idx + fYec69_idx_save) & 1023;
			for (int j296 = 0; j296 < 4; j296 = j296 + 1) {
				fRec139_tmp[j296] = fRec139_perm[j296];
			}
			for (int j298 = 0; j298 < 4; j298 = j298 + 1) {
				fRec138_tmp[j298] = fRec138_perm[j298];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec69[(i + fYec69_idx) & 1023] = fSlow2 * fRec138[i - 1] + fZec39[i];
				fRec139[i] = fSlow228 * fYec69[(i + fYec69_idx - iSlow229) & 1023] - (fSlow230 * fRec139[i - 1] + fConst6 * fRec139[i - 2]);
				fRec138[i] = fConst7 * (fRec139[i] - fRec139[i - 2]);
			}
			/* Post code */
			fYec69_idx_save = vsize;
			for (int j297 = 0; j297 < 4; j297 = j297 + 1) {
				fRec139_perm[j297] = fRec139_tmp[vsize + j297];
			}
			for (int j299 = 0; j299 < 4; j299 = j299 + 1) {
				fRec138_perm[j299] = fRec138_tmp[vsize + j299];
			}
			/* Recursive loop 103 */
			/* Pre code */
			fYec70_idx = (fYec70_idx + fYec70_idx_save) & 127;
			for (int j300 = 0; j300 < 4; j300 = j300 + 1) {
				fRec141_tmp[j300] = fRec141_perm[j300];
			}
			for (int j302 = 0; j302 < 4; j302 = j302 + 1) {
				fRec140_tmp[j302] = fRec140_perm[j302];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec70[(i + fYec70_idx) & 127] = fZec40[i] + fSlow2 * fRec140[i - 1];
				fRec141[i] = fSlow231 * fYec70[(i + fYec70_idx - iSlow232) & 127] - (fSlow233 * fRec141[i - 1] + fConst6 * fRec141[i - 2]);
				fRec140[i] = fConst7 * (fRec141[i] - fRec141[i - 2]);
			}
			/* Post code */
			fYec70_idx_save = vsize;
			for (int j301 = 0; j301 < 4; j301 = j301 + 1) {
				fRec141_perm[j301] = fRec141_tmp[vsize + j301];
			}
			for (int j303 = 0; j303 < 4; j303 = j303 + 1) {
				fRec140_perm[j303] = fRec140_tmp[vsize + j303];
			}
			/* Recursive loop 104 */
			/* Pre code */
			fYec71_idx = (fYec71_idx + fYec71_idx_save) & 127;
			for (int j304 = 0; j304 < 4; j304 = j304 + 1) {
				fRec143_tmp[j304] = fRec143_perm[j304];
			}
			for (int j306 = 0; j306 < 4; j306 = j306 + 1) {
				fRec142_tmp[j306] = fRec142_perm[j306];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec71[(i + fYec71_idx) & 127] = fSlow2 * fRec142[i - 1] + fZec40[i];
				fRec143[i] = fSlow234 * fYec71[(i + fYec71_idx - iSlow235) & 127] - (fSlow236 * fRec143[i - 1] + fConst6 * fRec143[i - 2]);
				fRec142[i] = fConst7 * (fRec143[i] - fRec143[i - 2]);
			}
			/* Post code */
			fYec71_idx_save = vsize;
			for (int j305 = 0; j305 < 4; j305 = j305 + 1) {
				fRec143_perm[j305] = fRec143_tmp[vsize + j305];
			}
			for (int j307 = 0; j307 < 4; j307 = j307 + 1) {
				fRec142_perm[j307] = fRec142_tmp[vsize + j307];
			}
			/* Recursive loop 105 */
			/* Pre code */
			fYec72_idx = (fYec72_idx + fYec72_idx_save) & 127;
			for (int j308 = 0; j308 < 4; j308 = j308 + 1) {
				fRec145_tmp[j308] = fRec145_perm[j308];
			}
			for (int j310 = 0; j310 < 4; j310 = j310 + 1) {
				fRec144_tmp[j310] = fRec144_perm[j310];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec72[(i + fYec72_idx) & 127] = fZec41[i] + fSlow2 * fRec144[i - 1];
				fRec145[i] = fSlow237 * fYec72[(i + fYec72_idx - iSlow238) & 127] - (fSlow239 * fRec145[i - 1] + fConst6 * fRec145[i - 2]);
				fRec144[i] = fConst7 * (fRec145[i] - fRec145[i - 2]);
			}
			/* Post code */
			fYec72_idx_save = vsize;
			for (int j309 = 0; j309 < 4; j309 = j309 + 1) {
				fRec145_perm[j309] = fRec145_tmp[vsize + j309];
			}
			for (int j311 = 0; j311 < 4; j311 = j311 + 1) {
				fRec144_perm[j311] = fRec144_tmp[vsize + j311];
			}
			/* Recursive loop 106 */
			/* Pre code */
			fYec73_idx = (fYec73_idx + fYec73_idx_save) & 127;
			for (int j312 = 0; j312 < 4; j312 = j312 + 1) {
				fRec147_tmp[j312] = fRec147_perm[j312];
			}
			for (int j314 = 0; j314 < 4; j314 = j314 + 1) {
				fRec146_tmp[j314] = fRec146_perm[j314];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec73[(i + fYec73_idx) & 127] = fSlow2 * fRec146[i - 1] + fZec41[i];
				fRec147[i] = fSlow240 * fYec73[(i + fYec73_idx - iSlow241) & 127] - (fSlow242 * fRec147[i - 1] + fConst6 * fRec147[i - 2]);
				fRec146[i] = fConst7 * (fRec147[i] - fRec147[i - 2]);
			}
			/* Post code */
			fYec73_idx_save = vsize;
			for (int j313 = 0; j313 < 4; j313 = j313 + 1) {
				fRec147_perm[j313] = fRec147_tmp[vsize + j313];
			}
			for (int j315 = 0; j315 < 4; j315 = j315 + 1) {
				fRec146_perm[j315] = fRec146_tmp[vsize + j315];
			}
			/* Recursive loop 107 */
			/* Pre code */
			fYec74_idx = (fYec74_idx + fYec74_idx_save) & 127;
			for (int j316 = 0; j316 < 4; j316 = j316 + 1) {
				fRec149_tmp[j316] = fRec149_perm[j316];
			}
			for (int j318 = 0; j318 < 4; j318 = j318 + 1) {
				fRec148_tmp[j318] = fRec148_perm[j318];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec74[(i + fYec74_idx) & 127] = fZec42[i] + fSlow2 * fRec148[i - 1];
				fRec149[i] = fSlow243 * fYec74[(i + fYec74_idx - iSlow244) & 127] - (fSlow245 * fRec149[i - 1] + fConst6 * fRec149[i - 2]);
				fRec148[i] = fConst7 * (fRec149[i] - fRec149[i - 2]);
			}
			/* Post code */
			fYec74_idx_save = vsize;
			for (int j317 = 0; j317 < 4; j317 = j317 + 1) {
				fRec149_perm[j317] = fRec149_tmp[vsize + j317];
			}
			for (int j319 = 0; j319 < 4; j319 = j319 + 1) {
				fRec148_perm[j319] = fRec148_tmp[vsize + j319];
			}
			/* Recursive loop 108 */
			/* Pre code */
			fYec75_idx = (fYec75_idx + fYec75_idx_save) & 127;
			for (int j320 = 0; j320 < 4; j320 = j320 + 1) {
				fRec151_tmp[j320] = fRec151_perm[j320];
			}
			for (int j322 = 0; j322 < 4; j322 = j322 + 1) {
				fRec150_tmp[j322] = fRec150_perm[j322];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec75[(i + fYec75_idx) & 127] = fSlow2 * fRec150[i - 1] + fZec42[i];
				fRec151[i] = fSlow246 * fYec75[(i + fYec75_idx - iSlow247) & 127] - (fSlow248 * fRec151[i - 1] + fConst6 * fRec151[i - 2]);
				fRec150[i] = fConst7 * (fRec151[i] - fRec151[i - 2]);
			}
			/* Post code */
			fYec75_idx_save = vsize;
			for (int j321 = 0; j321 < 4; j321 = j321 + 1) {
				fRec151_perm[j321] = fRec151_tmp[vsize + j321];
			}
			for (int j323 = 0; j323 < 4; j323 = j323 + 1) {
				fRec150_perm[j323] = fRec150_tmp[vsize + j323];
			}
			/* Recursive loop 109 */
			/* Pre code */
			fYec76_idx = (fYec76_idx + fYec76_idx_save) & 511;
			for (int j324 = 0; j324 < 4; j324 = j324 + 1) {
				fRec153_tmp[j324] = fRec153_perm[j324];
			}
			for (int j326 = 0; j326 < 4; j326 = j326 + 1) {
				fRec152_tmp[j326] = fRec152_perm[j326];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec76[(i + fYec76_idx) & 511] = fZec43[i] + fSlow2 * fRec152[i - 1];
				fRec153[i] = fSlow249 * fYec76[(i + fYec76_idx - iSlow250) & 511] - (fSlow251 * fRec153[i - 1] + fConst6 * fRec153[i - 2]);
				fRec152[i] = fConst7 * (fRec153[i] - fRec153[i - 2]);
			}
			/* Post code */
			fYec76_idx_save = vsize;
			for (int j325 = 0; j325 < 4; j325 = j325 + 1) {
				fRec153_perm[j325] = fRec153_tmp[vsize + j325];
			}
			for (int j327 = 0; j327 < 4; j327 = j327 + 1) {
				fRec152_perm[j327] = fRec152_tmp[vsize + j327];
			}
			/* Recursive loop 110 */
			/* Pre code */
			fYec77_idx = (fYec77_idx + fYec77_idx_save) & 511;
			for (int j328 = 0; j328 < 4; j328 = j328 + 1) {
				fRec155_tmp[j328] = fRec155_perm[j328];
			}
			for (int j330 = 0; j330 < 4; j330 = j330 + 1) {
				fRec154_tmp[j330] = fRec154_perm[j330];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec77[(i + fYec77_idx) & 511] = fSlow2 * fRec154[i - 1] + fZec43[i];
				fRec155[i] = fSlow252 * fYec77[(i + fYec77_idx - iSlow253) & 511] - (fSlow254 * fRec155[i - 1] + fConst6 * fRec155[i - 2]);
				fRec154[i] = fConst7 * (fRec155[i] - fRec155[i - 2]);
			}
			/* Post code */
			fYec77_idx_save = vsize;
			for (int j329 = 0; j329 < 4; j329 = j329 + 1) {
				fRec155_perm[j329] = fRec155_tmp[vsize + j329];
			}
			for (int j331 = 0; j331 < 4; j331 = j331 + 1) {
				fRec154_perm[j331] = fRec154_tmp[vsize + j331];
			}
			/* Recursive loop 111 */
			/* Pre code */
			fYec78_idx = (fYec78_idx + fYec78_idx_save) & 1023;
			for (int j332 = 0; j332 < 4; j332 = j332 + 1) {
				fRec157_tmp[j332] = fRec157_perm[j332];
			}
			for (int j334 = 0; j334 < 4; j334 = j334 + 1) {
				fRec156_tmp[j334] = fRec156_perm[j334];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec78[(i + fYec78_idx) & 1023] = fZec44[i] + fSlow2 * fRec156[i - 1];
				fRec157[i] = fSlow255 * fYec78[(i + fYec78_idx - iSlow256) & 1023] - (fSlow257 * fRec157[i - 1] + fConst6 * fRec157[i - 2]);
				fRec156[i] = fConst7 * (fRec157[i] - fRec157[i - 2]);
			}
			/* Post code */
			fYec78_idx_save = vsize;
			for (int j333 = 0; j333 < 4; j333 = j333 + 1) {
				fRec157_perm[j333] = fRec157_tmp[vsize + j333];
			}
			for (int j335 = 0; j335 < 4; j335 = j335 + 1) {
				fRec156_perm[j335] = fRec156_tmp[vsize + j335];
			}
			/* Recursive loop 112 */
			/* Pre code */
			fYec79_idx = (fYec79_idx + fYec79_idx_save) & 1023;
			for (int j336 = 0; j336 < 4; j336 = j336 + 1) {
				fRec159_tmp[j336] = fRec159_perm[j336];
			}
			for (int j338 = 0; j338 < 4; j338 = j338 + 1) {
				fRec158_tmp[j338] = fRec158_perm[j338];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec79[(i + fYec79_idx) & 1023] = fSlow2 * fRec158[i - 1] + fZec44[i];
				fRec159[i] = fSlow258 * fYec79[(i + fYec79_idx - iSlow259) & 1023] - (fSlow260 * fRec159[i - 1] + fConst6 * fRec159[i - 2]);
				fRec158[i] = fConst7 * (fRec159[i] - fRec159[i - 2]);
			}
			/* Post code */
			fYec79_idx_save = vsize;
			for (int j337 = 0; j337 < 4; j337 = j337 + 1) {
				fRec159_perm[j337] = fRec159_tmp[vsize + j337];
			}
			for (int j339 = 0; j339 < 4; j339 = j339 + 1) {
				fRec158_perm[j339] = fRec158_tmp[vsize + j339];
			}
			/* Recursive loop 113 */
			/* Pre code */
			fYec80_idx = (fYec80_idx + fYec80_idx_save) & 127;
			for (int j340 = 0; j340 < 4; j340 = j340 + 1) {
				fRec161_tmp[j340] = fRec161_perm[j340];
			}
			for (int j342 = 0; j342 < 4; j342 = j342 + 1) {
				fRec160_tmp[j342] = fRec160_perm[j342];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec80[(i + fYec80_idx) & 127] = fZec45[i] + fSlow2 * fRec160[i - 1];
				fRec161[i] = fSlow261 * fYec80[(i + fYec80_idx - iSlow262) & 127] - (fSlow263 * fRec161[i - 1] + fConst6 * fRec161[i - 2]);
				fRec160[i] = fConst7 * (fRec161[i] - fRec161[i - 2]);
			}
			/* Post code */
			fYec80_idx_save = vsize;
			for (int j341 = 0; j341 < 4; j341 = j341 + 1) {
				fRec161_perm[j341] = fRec161_tmp[vsize + j341];
			}
			for (int j343 = 0; j343 < 4; j343 = j343 + 1) {
				fRec160_perm[j343] = fRec160_tmp[vsize + j343];
			}
			/* Recursive loop 114 */
			/* Pre code */
			fYec81_idx = (fYec81_idx + fYec81_idx_save) & 127;
			for (int j344 = 0; j344 < 4; j344 = j344 + 1) {
				fRec163_tmp[j344] = fRec163_perm[j344];
			}
			for (int j346 = 0; j346 < 4; j346 = j346 + 1) {
				fRec162_tmp[j346] = fRec162_perm[j346];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec81[(i + fYec81_idx) & 127] = fSlow2 * fRec162[i - 1] + fZec45[i];
				fRec163[i] = fSlow264 * fYec81[(i + fYec81_idx - iSlow265) & 127] - (fSlow266 * fRec163[i - 1] + fConst6 * fRec163[i - 2]);
				fRec162[i] = fConst7 * (fRec163[i] - fRec163[i - 2]);
			}
			/* Post code */
			fYec81_idx_save = vsize;
			for (int j345 = 0; j345 < 4; j345 = j345 + 1) {
				fRec163_perm[j345] = fRec163_tmp[vsize + j345];
			}
			for (int j347 = 0; j347 < 4; j347 = j347 + 1) {
				fRec162_perm[j347] = fRec162_tmp[vsize + j347];
			}
			/* Recursive loop 115 */
			/* Pre code */
			fYec82_idx = (fYec82_idx + fYec82_idx_save) & 127;
			for (int j348 = 0; j348 < 4; j348 = j348 + 1) {
				fRec165_tmp[j348] = fRec165_perm[j348];
			}
			for (int j350 = 0; j350 < 4; j350 = j350 + 1) {
				fRec164_tmp[j350] = fRec164_perm[j350];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec82[(i + fYec82_idx) & 127] = fZec46[i] + fSlow2 * fRec164[i - 1];
				fRec165[i] = fSlow267 * fYec82[(i + fYec82_idx - iSlow268) & 127] - (fSlow269 * fRec165[i - 1] + fConst6 * fRec165[i - 2]);
				fRec164[i] = fConst7 * (fRec165[i] - fRec165[i - 2]);
			}
			/* Post code */
			fYec82_idx_save = vsize;
			for (int j349 = 0; j349 < 4; j349 = j349 + 1) {
				fRec165_perm[j349] = fRec165_tmp[vsize + j349];
			}
			for (int j351 = 0; j351 < 4; j351 = j351 + 1) {
				fRec164_perm[j351] = fRec164_tmp[vsize + j351];
			}
			/* Recursive loop 116 */
			/* Pre code */
			fYec83_idx = (fYec83_idx + fYec83_idx_save) & 127;
			for (int j352 = 0; j352 < 4; j352 = j352 + 1) {
				fRec167_tmp[j352] = fRec167_perm[j352];
			}
			for (int j354 = 0; j354 < 4; j354 = j354 + 1) {
				fRec166_tmp[j354] = fRec166_perm[j354];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec83[(i + fYec83_idx) & 127] = fSlow2 * fRec166[i - 1] + fZec46[i];
				fRec167[i] = fSlow270 * fYec83[(i + fYec83_idx - iSlow271) & 127] - (fSlow272 * fRec167[i - 1] + fConst6 * fRec167[i - 2]);
				fRec166[i] = fConst7 * (fRec167[i] - fRec167[i - 2]);
			}
			/* Post code */
			fYec83_idx_save = vsize;
			for (int j353 = 0; j353 < 4; j353 = j353 + 1) {
				fRec167_perm[j353] = fRec167_tmp[vsize + j353];
			}
			for (int j355 = 0; j355 < 4; j355 = j355 + 1) {
				fRec166_perm[j355] = fRec166_tmp[vsize + j355];
			}
			/* Recursive loop 117 */
			/* Pre code */
			fYec84_idx = (fYec84_idx + fYec84_idx_save) & 127;
			for (int j356 = 0; j356 < 4; j356 = j356 + 1) {
				fRec169_tmp[j356] = fRec169_perm[j356];
			}
			for (int j358 = 0; j358 < 4; j358 = j358 + 1) {
				fRec168_tmp[j358] = fRec168_perm[j358];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec84[(i + fYec84_idx) & 127] = fZec47[i] + fSlow2 * fRec168[i - 1];
				fRec169[i] = fSlow273 * fYec84[(i + fYec84_idx - iSlow274) & 127] - (fSlow275 * fRec169[i - 1] + fConst6 * fRec169[i - 2]);
				fRec168[i] = fConst7 * (fRec169[i] - fRec169[i - 2]);
			}
			/* Post code */
			fYec84_idx_save = vsize;
			for (int j357 = 0; j357 < 4; j357 = j357 + 1) {
				fRec169_perm[j357] = fRec169_tmp[vsize + j357];
			}
			for (int j359 = 0; j359 < 4; j359 = j359 + 1) {
				fRec168_perm[j359] = fRec168_tmp[vsize + j359];
			}
			/* Recursive loop 118 */
			/* Pre code */
			fYec85_idx = (fYec85_idx + fYec85_idx_save) & 127;
			for (int j360 = 0; j360 < 4; j360 = j360 + 1) {
				fRec171_tmp[j360] = fRec171_perm[j360];
			}
			for (int j362 = 0; j362 < 4; j362 = j362 + 1) {
				fRec170_tmp[j362] = fRec170_perm[j362];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec85[(i + fYec85_idx) & 127] = fSlow2 * fRec170[i - 1] + fZec47[i];
				fRec171[i] = fSlow276 * fYec85[(i + fYec85_idx - iSlow277) & 127] - (fSlow278 * fRec171[i - 1] + fConst6 * fRec171[i - 2]);
				fRec170[i] = fConst7 * (fRec171[i] - fRec171[i - 2]);
			}
			/* Post code */
			fYec85_idx_save = vsize;
			for (int j361 = 0; j361 < 4; j361 = j361 + 1) {
				fRec171_perm[j361] = fRec171_tmp[vsize + j361];
			}
			for (int j363 = 0; j363 < 4; j363 = j363 + 1) {
				fRec170_perm[j363] = fRec170_tmp[vsize + j363];
			}
			/* Recursive loop 119 */
			/* Pre code */
			fYec86_idx = (fYec86_idx + fYec86_idx_save) & 511;
			for (int j364 = 0; j364 < 4; j364 = j364 + 1) {
				fRec173_tmp[j364] = fRec173_perm[j364];
			}
			for (int j366 = 0; j366 < 4; j366 = j366 + 1) {
				fRec172_tmp[j366] = fRec172_perm[j366];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec86[(i + fYec86_idx) & 511] = fZec48[i] + fSlow2 * fRec172[i - 1];
				fRec173[i] = fSlow279 * fYec86[(i + fYec86_idx - iSlow280) & 511] - (fSlow281 * fRec173[i - 1] + fConst6 * fRec173[i - 2]);
				fRec172[i] = fConst7 * (fRec173[i] - fRec173[i - 2]);
			}
			/* Post code */
			fYec86_idx_save = vsize;
			for (int j365 = 0; j365 < 4; j365 = j365 + 1) {
				fRec173_perm[j365] = fRec173_tmp[vsize + j365];
			}
			for (int j367 = 0; j367 < 4; j367 = j367 + 1) {
				fRec172_perm[j367] = fRec172_tmp[vsize + j367];
			}
			/* Recursive loop 120 */
			/* Pre code */
			fYec87_idx = (fYec87_idx + fYec87_idx_save) & 511;
			for (int j368 = 0; j368 < 4; j368 = j368 + 1) {
				fRec175_tmp[j368] = fRec175_perm[j368];
			}
			for (int j370 = 0; j370 < 4; j370 = j370 + 1) {
				fRec174_tmp[j370] = fRec174_perm[j370];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec87[(i + fYec87_idx) & 511] = fSlow2 * fRec174[i - 1] + fZec48[i];
				fRec175[i] = fSlow282 * fYec87[(i + fYec87_idx - iSlow283) & 511] - (fSlow284 * fRec175[i - 1] + fConst6 * fRec175[i - 2]);
				fRec174[i] = fConst7 * (fRec175[i] - fRec175[i - 2]);
			}
			/* Post code */
			fYec87_idx_save = vsize;
			for (int j369 = 0; j369 < 4; j369 = j369 + 1) {
				fRec175_perm[j369] = fRec175_tmp[vsize + j369];
			}
			for (int j371 = 0; j371 < 4; j371 = j371 + 1) {
				fRec174_perm[j371] = fRec174_tmp[vsize + j371];
			}
			/* Recursive loop 121 */
			/* Pre code */
			fYec88_idx = (fYec88_idx + fYec88_idx_save) & 1023;
			for (int j372 = 0; j372 < 4; j372 = j372 + 1) {
				fRec177_tmp[j372] = fRec177_perm[j372];
			}
			for (int j374 = 0; j374 < 4; j374 = j374 + 1) {
				fRec176_tmp[j374] = fRec176_perm[j374];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec88[(i + fYec88_idx) & 1023] = fZec49[i] + fSlow2 * fRec176[i - 1];
				fRec177[i] = fSlow285 * fYec88[(i + fYec88_idx - iSlow286) & 1023] - (fSlow287 * fRec177[i - 1] + fConst6 * fRec177[i - 2]);
				fRec176[i] = fConst7 * (fRec177[i] - fRec177[i - 2]);
			}
			/* Post code */
			fYec88_idx_save = vsize;
			for (int j373 = 0; j373 < 4; j373 = j373 + 1) {
				fRec177_perm[j373] = fRec177_tmp[vsize + j373];
			}
			for (int j375 = 0; j375 < 4; j375 = j375 + 1) {
				fRec176_perm[j375] = fRec176_tmp[vsize + j375];
			}
			/* Recursive loop 122 */
			/* Pre code */
			fYec89_idx = (fYec89_idx + fYec89_idx_save) & 1023;
			for (int j376 = 0; j376 < 4; j376 = j376 + 1) {
				fRec179_tmp[j376] = fRec179_perm[j376];
			}
			for (int j378 = 0; j378 < 4; j378 = j378 + 1) {
				fRec178_tmp[j378] = fRec178_perm[j378];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec89[(i + fYec89_idx) & 1023] = fSlow2 * fRec178[i - 1] + fZec49[i];
				fRec179[i] = fSlow288 * fYec89[(i + fYec89_idx - iSlow289) & 1023] - (fSlow290 * fRec179[i - 1] + fConst6 * fRec179[i - 2]);
				fRec178[i] = fConst7 * (fRec179[i] - fRec179[i - 2]);
			}
			/* Post code */
			fYec89_idx_save = vsize;
			for (int j377 = 0; j377 < 4; j377 = j377 + 1) {
				fRec179_perm[j377] = fRec179_tmp[vsize + j377];
			}
			for (int j379 = 0; j379 < 4; j379 = j379 + 1) {
				fRec178_perm[j379] = fRec178_tmp[vsize + j379];
			}
			/* Recursive loop 123 */
			/* Pre code */
			fYec90_idx = (fYec90_idx + fYec90_idx_save) & 127;
			for (int j380 = 0; j380 < 4; j380 = j380 + 1) {
				fRec181_tmp[j380] = fRec181_perm[j380];
			}
			for (int j382 = 0; j382 < 4; j382 = j382 + 1) {
				fRec180_tmp[j382] = fRec180_perm[j382];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec90[(i + fYec90_idx) & 127] = fZec50[i] + fSlow2 * fRec180[i - 1];
				fRec181[i] = fSlow291 * fYec90[(i + fYec90_idx - iSlow292) & 127] - (fSlow293 * fRec181[i - 1] + fConst6 * fRec181[i - 2]);
				fRec180[i] = fConst7 * (fRec181[i] - fRec181[i - 2]);
			}
			/* Post code */
			fYec90_idx_save = vsize;
			for (int j381 = 0; j381 < 4; j381 = j381 + 1) {
				fRec181_perm[j381] = fRec181_tmp[vsize + j381];
			}
			for (int j383 = 0; j383 < 4; j383 = j383 + 1) {
				fRec180_perm[j383] = fRec180_tmp[vsize + j383];
			}
			/* Recursive loop 124 */
			/* Pre code */
			fYec91_idx = (fYec91_idx + fYec91_idx_save) & 127;
			for (int j384 = 0; j384 < 4; j384 = j384 + 1) {
				fRec183_tmp[j384] = fRec183_perm[j384];
			}
			for (int j386 = 0; j386 < 4; j386 = j386 + 1) {
				fRec182_tmp[j386] = fRec182_perm[j386];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec91[(i + fYec91_idx) & 127] = fSlow2 * fRec182[i - 1] + fZec50[i];
				fRec183[i] = fSlow294 * fYec91[(i + fYec91_idx - iSlow295) & 127] - (fSlow296 * fRec183[i - 1] + fConst6 * fRec183[i - 2]);
				fRec182[i] = fConst7 * (fRec183[i] - fRec183[i - 2]);
			}
			/* Post code */
			fYec91_idx_save = vsize;
			for (int j385 = 0; j385 < 4; j385 = j385 + 1) {
				fRec183_perm[j385] = fRec183_tmp[vsize + j385];
			}
			for (int j387 = 0; j387 < 4; j387 = j387 + 1) {
				fRec182_perm[j387] = fRec182_tmp[vsize + j387];
			}
			/* Recursive loop 125 */
			/* Pre code */
			fYec92_idx = (fYec92_idx + fYec92_idx_save) & 127;
			for (int j388 = 0; j388 < 4; j388 = j388 + 1) {
				fRec185_tmp[j388] = fRec185_perm[j388];
			}
			for (int j390 = 0; j390 < 4; j390 = j390 + 1) {
				fRec184_tmp[j390] = fRec184_perm[j390];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec92[(i + fYec92_idx) & 127] = fZec51[i] + fSlow2 * fRec184[i - 1];
				fRec185[i] = fSlow297 * fYec92[(i + fYec92_idx - iSlow298) & 127] - (fSlow299 * fRec185[i - 1] + fConst6 * fRec185[i - 2]);
				fRec184[i] = fConst7 * (fRec185[i] - fRec185[i - 2]);
			}
			/* Post code */
			fYec92_idx_save = vsize;
			for (int j389 = 0; j389 < 4; j389 = j389 + 1) {
				fRec185_perm[j389] = fRec185_tmp[vsize + j389];
			}
			for (int j391 = 0; j391 < 4; j391 = j391 + 1) {
				fRec184_perm[j391] = fRec184_tmp[vsize + j391];
			}
			/* Recursive loop 126 */
			/* Pre code */
			fYec93_idx = (fYec93_idx + fYec93_idx_save) & 127;
			for (int j392 = 0; j392 < 4; j392 = j392 + 1) {
				fRec187_tmp[j392] = fRec187_perm[j392];
			}
			for (int j394 = 0; j394 < 4; j394 = j394 + 1) {
				fRec186_tmp[j394] = fRec186_perm[j394];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec93[(i + fYec93_idx) & 127] = fSlow2 * fRec186[i - 1] + fZec51[i];
				fRec187[i] = fSlow300 * fYec93[(i + fYec93_idx - iSlow301) & 127] - (fSlow302 * fRec187[i - 1] + fConst6 * fRec187[i - 2]);
				fRec186[i] = fConst7 * (fRec187[i] - fRec187[i - 2]);
			}
			/* Post code */
			fYec93_idx_save = vsize;
			for (int j393 = 0; j393 < 4; j393 = j393 + 1) {
				fRec187_perm[j393] = fRec187_tmp[vsize + j393];
			}
			for (int j395 = 0; j395 < 4; j395 = j395 + 1) {
				fRec186_perm[j395] = fRec186_tmp[vsize + j395];
			}
			/* Recursive loop 127 */
			/* Pre code */
			fYec94_idx = (fYec94_idx + fYec94_idx_save) & 127;
			for (int j396 = 0; j396 < 4; j396 = j396 + 1) {
				fRec189_tmp[j396] = fRec189_perm[j396];
			}
			for (int j398 = 0; j398 < 4; j398 = j398 + 1) {
				fRec188_tmp[j398] = fRec188_perm[j398];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec94[(i + fYec94_idx) & 127] = fZec52[i] + fSlow2 * fRec188[i - 1];
				fRec189[i] = fSlow303 * fYec94[(i + fYec94_idx - iSlow304) & 127] - (fSlow305 * fRec189[i - 1] + fConst6 * fRec189[i - 2]);
				fRec188[i] = fConst7 * (fRec189[i] - fRec189[i - 2]);
			}
			/* Post code */
			fYec94_idx_save = vsize;
			for (int j397 = 0; j397 < 4; j397 = j397 + 1) {
				fRec189_perm[j397] = fRec189_tmp[vsize + j397];
			}
			for (int j399 = 0; j399 < 4; j399 = j399 + 1) {
				fRec188_perm[j399] = fRec188_tmp[vsize + j399];
			}
			/* Recursive loop 128 */
			/* Pre code */
			fYec95_idx = (fYec95_idx + fYec95_idx_save) & 127;
			for (int j400 = 0; j400 < 4; j400 = j400 + 1) {
				fRec191_tmp[j400] = fRec191_perm[j400];
			}
			for (int j402 = 0; j402 < 4; j402 = j402 + 1) {
				fRec190_tmp[j402] = fRec190_perm[j402];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec95[(i + fYec95_idx) & 127] = fSlow2 * fRec190[i - 1] + fZec52[i];
				fRec191[i] = fSlow306 * fYec95[(i + fYec95_idx - iSlow307) & 127] - (fSlow308 * fRec191[i - 1] + fConst6 * fRec191[i - 2]);
				fRec190[i] = fConst7 * (fRec191[i] - fRec191[i - 2]);
			}
			/* Post code */
			fYec95_idx_save = vsize;
			for (int j401 = 0; j401 < 4; j401 = j401 + 1) {
				fRec191_perm[j401] = fRec191_tmp[vsize + j401];
			}
			for (int j403 = 0; j403 < 4; j403 = j403 + 1) {
				fRec190_perm[j403] = fRec190_tmp[vsize + j403];
			}
			/* Recursive loop 129 */
			/* Pre code */
			fYec96_idx = (fYec96_idx + fYec96_idx_save) & 511;
			for (int j404 = 0; j404 < 4; j404 = j404 + 1) {
				fRec193_tmp[j404] = fRec193_perm[j404];
			}
			for (int j406 = 0; j406 < 4; j406 = j406 + 1) {
				fRec192_tmp[j406] = fRec192_perm[j406];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec96[(i + fYec96_idx) & 511] = fZec53[i] + fSlow2 * fRec192[i - 1];
				fRec193[i] = fSlow309 * fYec96[(i + fYec96_idx - iSlow310) & 511] - (fSlow311 * fRec193[i - 1] + fConst6 * fRec193[i - 2]);
				fRec192[i] = fConst7 * (fRec193[i] - fRec193[i - 2]);
			}
			/* Post code */
			fYec96_idx_save = vsize;
			for (int j405 = 0; j405 < 4; j405 = j405 + 1) {
				fRec193_perm[j405] = fRec193_tmp[vsize + j405];
			}
			for (int j407 = 0; j407 < 4; j407 = j407 + 1) {
				fRec192_perm[j407] = fRec192_tmp[vsize + j407];
			}
			/* Recursive loop 130 */
			/* Pre code */
			fYec97_idx = (fYec97_idx + fYec97_idx_save) & 511;
			for (int j408 = 0; j408 < 4; j408 = j408 + 1) {
				fRec195_tmp[j408] = fRec195_perm[j408];
			}
			for (int j410 = 0; j410 < 4; j410 = j410 + 1) {
				fRec194_tmp[j410] = fRec194_perm[j410];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec97[(i + fYec97_idx) & 511] = fSlow2 * fRec194[i - 1] + fZec53[i];
				fRec195[i] = fSlow312 * fYec97[(i + fYec97_idx - iSlow313) & 511] - (fSlow314 * fRec195[i - 1] + fConst6 * fRec195[i - 2]);
				fRec194[i] = fConst7 * (fRec195[i] - fRec195[i - 2]);
			}
			/* Post code */
			fYec97_idx_save = vsize;
			for (int j409 = 0; j409 < 4; j409 = j409 + 1) {
				fRec195_perm[j409] = fRec195_tmp[vsize + j409];
			}
			for (int j411 = 0; j411 < 4; j411 = j411 + 1) {
				fRec194_perm[j411] = fRec194_tmp[vsize + j411];
			}
			/* Recursive loop 131 */
			/* Pre code */
			fYec98_idx = (fYec98_idx + fYec98_idx_save) & 1023;
			for (int j412 = 0; j412 < 4; j412 = j412 + 1) {
				fRec197_tmp[j412] = fRec197_perm[j412];
			}
			for (int j414 = 0; j414 < 4; j414 = j414 + 1) {
				fRec196_tmp[j414] = fRec196_perm[j414];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec98[(i + fYec98_idx) & 1023] = fZec54[i] + fSlow2 * fRec196[i - 1];
				fRec197[i] = fSlow315 * fYec98[(i + fYec98_idx - iSlow316) & 1023] - (fSlow317 * fRec197[i - 1] + fConst6 * fRec197[i - 2]);
				fRec196[i] = fConst7 * (fRec197[i] - fRec197[i - 2]);
			}
			/* Post code */
			fYec98_idx_save = vsize;
			for (int j413 = 0; j413 < 4; j413 = j413 + 1) {
				fRec197_perm[j413] = fRec197_tmp[vsize + j413];
			}
			for (int j415 = 0; j415 < 4; j415 = j415 + 1) {
				fRec196_perm[j415] = fRec196_tmp[vsize + j415];
			}
			/* Recursive loop 132 */
			/* Pre code */
			fYec99_idx = (fYec99_idx + fYec99_idx_save) & 1023;
			for (int j416 = 0; j416 < 4; j416 = j416 + 1) {
				fRec199_tmp[j416] = fRec199_perm[j416];
			}
			for (int j418 = 0; j418 < 4; j418 = j418 + 1) {
				fRec198_tmp[j418] = fRec198_perm[j418];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec99[(i + fYec99_idx) & 1023] = fSlow2 * fRec198[i - 1] + fZec54[i];
				fRec199[i] = fSlow318 * fYec99[(i + fYec99_idx - iSlow319) & 1023] - (fSlow320 * fRec199[i - 1] + fConst6 * fRec199[i - 2]);
				fRec198[i] = fConst7 * (fRec199[i] - fRec199[i - 2]);
			}
			/* Post code */
			fYec99_idx_save = vsize;
			for (int j417 = 0; j417 < 4; j417 = j417 + 1) {
				fRec199_perm[j417] = fRec199_tmp[vsize + j417];
			}
			for (int j419 = 0; j419 < 4; j419 = j419 + 1) {
				fRec198_perm[j419] = fRec198_tmp[vsize + j419];
			}
			/* Recursive loop 133 */
			/* Pre code */
			fYec100_idx = (fYec100_idx + fYec100_idx_save) & 127;
			for (int j420 = 0; j420 < 4; j420 = j420 + 1) {
				fRec201_tmp[j420] = fRec201_perm[j420];
			}
			for (int j422 = 0; j422 < 4; j422 = j422 + 1) {
				fRec200_tmp[j422] = fRec200_perm[j422];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec100[(i + fYec100_idx) & 127] = fZec55[i] + fSlow2 * fRec200[i - 1];
				fRec201[i] = fSlow321 * fYec100[(i + fYec100_idx - iSlow322) & 127] - (fSlow323 * fRec201[i - 1] + fConst6 * fRec201[i - 2]);
				fRec200[i] = fConst7 * (fRec201[i] - fRec201[i - 2]);
			}
			/* Post code */
			fYec100_idx_save = vsize;
			for (int j421 = 0; j421 < 4; j421 = j421 + 1) {
				fRec201_perm[j421] = fRec201_tmp[vsize + j421];
			}
			for (int j423 = 0; j423 < 4; j423 = j423 + 1) {
				fRec200_perm[j423] = fRec200_tmp[vsize + j423];
			}
			/* Recursive loop 134 */
			/* Pre code */
			fYec101_idx = (fYec101_idx + fYec101_idx_save) & 127;
			for (int j424 = 0; j424 < 4; j424 = j424 + 1) {
				fRec203_tmp[j424] = fRec203_perm[j424];
			}
			for (int j426 = 0; j426 < 4; j426 = j426 + 1) {
				fRec202_tmp[j426] = fRec202_perm[j426];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec101[(i + fYec101_idx) & 127] = fSlow2 * fRec202[i - 1] + fZec55[i];
				fRec203[i] = fSlow324 * fYec101[(i + fYec101_idx - iSlow325) & 127] - (fSlow326 * fRec203[i - 1] + fConst6 * fRec203[i - 2]);
				fRec202[i] = fConst7 * (fRec203[i] - fRec203[i - 2]);
			}
			/* Post code */
			fYec101_idx_save = vsize;
			for (int j425 = 0; j425 < 4; j425 = j425 + 1) {
				fRec203_perm[j425] = fRec203_tmp[vsize + j425];
			}
			for (int j427 = 0; j427 < 4; j427 = j427 + 1) {
				fRec202_perm[j427] = fRec202_tmp[vsize + j427];
			}
			/* Recursive loop 135 */
			/* Pre code */
			fYec102_idx = (fYec102_idx + fYec102_idx_save) & 127;
			for (int j428 = 0; j428 < 4; j428 = j428 + 1) {
				fRec205_tmp[j428] = fRec205_perm[j428];
			}
			for (int j430 = 0; j430 < 4; j430 = j430 + 1) {
				fRec204_tmp[j430] = fRec204_perm[j430];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec102[(i + fYec102_idx) & 127] = fZec56[i] + fSlow2 * fRec204[i - 1];
				fRec205[i] = fSlow327 * fYec102[(i + fYec102_idx - iSlow328) & 127] - (fSlow329 * fRec205[i - 1] + fConst6 * fRec205[i - 2]);
				fRec204[i] = fConst7 * (fRec205[i] - fRec205[i - 2]);
			}
			/* Post code */
			fYec102_idx_save = vsize;
			for (int j429 = 0; j429 < 4; j429 = j429 + 1) {
				fRec205_perm[j429] = fRec205_tmp[vsize + j429];
			}
			for (int j431 = 0; j431 < 4; j431 = j431 + 1) {
				fRec204_perm[j431] = fRec204_tmp[vsize + j431];
			}
			/* Recursive loop 136 */
			/* Pre code */
			fYec103_idx = (fYec103_idx + fYec103_idx_save) & 127;
			for (int j432 = 0; j432 < 4; j432 = j432 + 1) {
				fRec207_tmp[j432] = fRec207_perm[j432];
			}
			for (int j434 = 0; j434 < 4; j434 = j434 + 1) {
				fRec206_tmp[j434] = fRec206_perm[j434];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec103[(i + fYec103_idx) & 127] = fSlow2 * fRec206[i - 1] + fZec56[i];
				fRec207[i] = fSlow330 * fYec103[(i + fYec103_idx - iSlow331) & 127] - (fSlow332 * fRec207[i - 1] + fConst6 * fRec207[i - 2]);
				fRec206[i] = fConst7 * (fRec207[i] - fRec207[i - 2]);
			}
			/* Post code */
			fYec103_idx_save = vsize;
			for (int j433 = 0; j433 < 4; j433 = j433 + 1) {
				fRec207_perm[j433] = fRec207_tmp[vsize + j433];
			}
			for (int j435 = 0; j435 < 4; j435 = j435 + 1) {
				fRec206_perm[j435] = fRec206_tmp[vsize + j435];
			}
			/* Recursive loop 137 */
			/* Pre code */
			fYec104_idx = (fYec104_idx + fYec104_idx_save) & 127;
			for (int j436 = 0; j436 < 4; j436 = j436 + 1) {
				fRec209_tmp[j436] = fRec209_perm[j436];
			}
			for (int j438 = 0; j438 < 4; j438 = j438 + 1) {
				fRec208_tmp[j438] = fRec208_perm[j438];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec104[(i + fYec104_idx) & 127] = fZec57[i] + fSlow2 * fRec208[i - 1];
				fRec209[i] = fSlow333 * fYec104[(i + fYec104_idx - iSlow334) & 127] - (fSlow335 * fRec209[i - 1] + fConst6 * fRec209[i - 2]);
				fRec208[i] = fConst7 * (fRec209[i] - fRec209[i - 2]);
			}
			/* Post code */
			fYec104_idx_save = vsize;
			for (int j437 = 0; j437 < 4; j437 = j437 + 1) {
				fRec209_perm[j437] = fRec209_tmp[vsize + j437];
			}
			for (int j439 = 0; j439 < 4; j439 = j439 + 1) {
				fRec208_perm[j439] = fRec208_tmp[vsize + j439];
			}
			/* Recursive loop 138 */
			/* Pre code */
			fYec105_idx = (fYec105_idx + fYec105_idx_save) & 1023;
			for (int j440 = 0; j440 < 4; j440 = j440 + 1) {
				fRec211_tmp[j440] = fRec211_perm[j440];
			}
			for (int j442 = 0; j442 < 4; j442 = j442 + 1) {
				fRec210_tmp[j442] = fRec210_perm[j442];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec105[(i + fYec105_idx) & 1023] = fSlow2 * fRec210[i - 1] + fZec58[i];
				fRec211[i] = fSlow336 * fYec105[(i + fYec105_idx - iSlow337) & 1023] - (fSlow338 * fRec211[i - 1] + fConst6 * fRec211[i - 2]);
				fRec210[i] = fConst7 * (fRec211[i] - fRec211[i - 2]);
			}
			/* Post code */
			fYec105_idx_save = vsize;
			for (int j441 = 0; j441 < 4; j441 = j441 + 1) {
				fRec211_perm[j441] = fRec211_tmp[vsize + j441];
			}
			for (int j443 = 0; j443 < 4; j443 = j443 + 1) {
				fRec210_perm[j443] = fRec210_tmp[vsize + j443];
			}
			/* Recursive loop 139 */
			/* Pre code */
			fYec106_idx = (fYec106_idx + fYec106_idx_save) & 1023;
			for (int j444 = 0; j444 < 4; j444 = j444 + 1) {
				fRec213_tmp[j444] = fRec213_perm[j444];
			}
			for (int j446 = 0; j446 < 4; j446 = j446 + 1) {
				fRec212_tmp[j446] = fRec212_perm[j446];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec106[(i + fYec106_idx) & 1023] = fZec58[i] + fSlow2 * fRec212[i - 1];
				fRec213[i] = fSlow339 * fYec106[(i + fYec106_idx - iSlow340) & 1023] - (fSlow341 * fRec213[i - 1] + fConst6 * fRec213[i - 2]);
				fRec212[i] = fConst7 * (fRec213[i] - fRec213[i - 2]);
			}
			/* Post code */
			fYec106_idx_save = vsize;
			for (int j445 = 0; j445 < 4; j445 = j445 + 1) {
				fRec213_perm[j445] = fRec213_tmp[vsize + j445];
			}
			for (int j447 = 0; j447 < 4; j447 = j447 + 1) {
				fRec212_perm[j447] = fRec212_tmp[vsize + j447];
			}
			/* Recursive loop 140 */
			/* Pre code */
			fYec107_idx = (fYec107_idx + fYec107_idx_save) & 511;
			for (int j448 = 0; j448 < 4; j448 = j448 + 1) {
				fRec215_tmp[j448] = fRec215_perm[j448];
			}
			for (int j450 = 0; j450 < 4; j450 = j450 + 1) {
				fRec214_tmp[j450] = fRec214_perm[j450];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec107[(i + fYec107_idx) & 511] = fSlow2 * fRec214[i - 1] + fZec59[i];
				fRec215[i] = fSlow342 * fYec107[(i + fYec107_idx - iSlow343) & 511] - (fSlow344 * fRec215[i - 1] + fConst6 * fRec215[i - 2]);
				fRec214[i] = fConst7 * (fRec215[i] - fRec215[i - 2]);
			}
			/* Post code */
			fYec107_idx_save = vsize;
			for (int j449 = 0; j449 < 4; j449 = j449 + 1) {
				fRec215_perm[j449] = fRec215_tmp[vsize + j449];
			}
			for (int j451 = 0; j451 < 4; j451 = j451 + 1) {
				fRec214_perm[j451] = fRec214_tmp[vsize + j451];
			}
			/* Recursive loop 141 */
			/* Pre code */
			fYec108_idx = (fYec108_idx + fYec108_idx_save) & 511;
			for (int j452 = 0; j452 < 4; j452 = j452 + 1) {
				fRec217_tmp[j452] = fRec217_perm[j452];
			}
			for (int j454 = 0; j454 < 4; j454 = j454 + 1) {
				fRec216_tmp[j454] = fRec216_perm[j454];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec108[(i + fYec108_idx) & 511] = fZec59[i] + fSlow2 * fRec216[i - 1];
				fRec217[i] = fSlow345 * fYec108[(i + fYec108_idx - iSlow346) & 511] - (fSlow347 * fRec217[i - 1] + fConst6 * fRec217[i - 2]);
				fRec216[i] = fConst7 * (fRec217[i] - fRec217[i - 2]);
			}
			/* Post code */
			fYec108_idx_save = vsize;
			for (int j453 = 0; j453 < 4; j453 = j453 + 1) {
				fRec217_perm[j453] = fRec217_tmp[vsize + j453];
			}
			for (int j455 = 0; j455 < 4; j455 = j455 + 1) {
				fRec216_perm[j455] = fRec216_tmp[vsize + j455];
			}
			/* Recursive loop 142 */
			/* Pre code */
			fYec109_idx = (fYec109_idx + fYec109_idx_save) & 127;
			for (int j456 = 0; j456 < 4; j456 = j456 + 1) {
				fRec219_tmp[j456] = fRec219_perm[j456];
			}
			for (int j458 = 0; j458 < 4; j458 = j458 + 1) {
				fRec218_tmp[j458] = fRec218_perm[j458];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec109[(i + fYec109_idx) & 127] = fSlow2 * fRec218[i - 1] + fZec57[i];
				fRec219[i] = fSlow348 * fYec109[(i + fYec109_idx - iSlow349) & 127] - (fSlow350 * fRec219[i - 1] + fConst6 * fRec219[i - 2]);
				fRec218[i] = fConst7 * (fRec219[i] - fRec219[i - 2]);
			}
			/* Post code */
			fYec109_idx_save = vsize;
			for (int j457 = 0; j457 < 4; j457 = j457 + 1) {
				fRec219_perm[j457] = fRec219_tmp[vsize + j457];
			}
			for (int j459 = 0; j459 < 4; j459 = j459 + 1) {
				fRec218_perm[j459] = fRec218_tmp[vsize + j459];
			}
			/* Recursive loop 143 */
			/* Pre code */
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 255;
			for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
				fRec5_tmp[j14] = fRec5_perm[j14];
			}
			for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
				fRec4_tmp[j16] = fRec4_perm[j16];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[(i + fYec2_idx) & 255] = fSlow2 * fRec4[i - 1] + 5.2995043 * fZec2[i];
				fRec5[i] = fSlow12 * fYec2[(i + fYec2_idx - iSlow14) & 255] - (fSlow15 * fRec5[i - 1] + fConst6 * fRec5[i - 2]);
				fRec4[i] = fConst7 * (fRec5[i] - fRec5[i - 2]);
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
				fRec5_perm[j15] = fRec5_tmp[vsize + j15];
			}
			for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
				fRec4_perm[j17] = fRec4_tmp[vsize + j17];
			}
			/* Recursive loop 144 */
			/* Pre code */
			fYec3_idx = (fYec3_idx + fYec3_idx_save) & 255;
			for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
				fRec7_tmp[j20] = fRec7_perm[j20];
			}
			for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
				fRec6_tmp[j22] = fRec6_perm[j22];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[(i + fYec3_idx) & 255] = fSlow2 * fRec6[i - 1] + 5.2995043 * fZec3[i];
				fRec7[i] = fSlow17 * fYec3[(i + fYec3_idx - iSlow19) & 255] - (fSlow20 * fRec7[i - 1] + fConst6 * fRec7[i - 2]);
				fRec6[i] = fConst7 * (fRec7[i] - fRec7[i - 2]);
			}
			/* Post code */
			fYec3_idx_save = vsize;
			for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
				fRec7_perm[j21] = fRec7_tmp[vsize + j21];
			}
			for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
				fRec6_perm[j23] = fRec6_tmp[vsize + j23];
			}
			/* Recursive loop 145 */
			/* Pre code */
			fYec4_idx = (fYec4_idx + fYec4_idx_save) & 255;
			for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
				fRec9_tmp[j26] = fRec9_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
				fRec8_tmp[j28] = fRec8_perm[j28];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec4[(i + fYec4_idx) & 255] = fSlow2 * fRec8[i - 1] + 5.2995043 * fZec4[i];
				fRec9[i] = fSlow22 * fYec4[(i + fYec4_idx - iSlow24) & 255] - (fSlow25 * fRec9[i - 1] + fConst6 * fRec9[i - 2]);
				fRec8[i] = fConst7 * (fRec9[i] - fRec9[i - 2]);
			}
			/* Post code */
			fYec4_idx_save = vsize;
			for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
				fRec9_perm[j27] = fRec9_tmp[vsize + j27];
			}
			for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
				fRec8_perm[j29] = fRec8_tmp[vsize + j29];
			}
			/* Recursive loop 146 */
			/* Pre code */
			fYec5_idx = (fYec5_idx + fYec5_idx_save) & 255;
			for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
				fRec11_tmp[j32] = fRec11_perm[j32];
			}
			for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
				fRec10_tmp[j34] = fRec10_perm[j34];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec5[(i + fYec5_idx) & 255] = fSlow2 * fRec10[i - 1] + 5.2995043 * fZec5[i];
				fRec11[i] = fSlow27 * fYec5[(i + fYec5_idx - iSlow29) & 255] - (fSlow30 * fRec11[i - 1] + fConst6 * fRec11[i - 2]);
				fRec10[i] = fConst7 * (fRec11[i] - fRec11[i - 2]);
			}
			/* Post code */
			fYec5_idx_save = vsize;
			for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
				fRec11_perm[j33] = fRec11_tmp[vsize + j33];
			}
			for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
				fRec10_perm[j35] = fRec10_tmp[vsize + j35];
			}
			/* Recursive loop 147 */
			/* Pre code */
			fYec6_idx = (fYec6_idx + fYec6_idx_save) & 255;
			for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
				fRec13_tmp[j38] = fRec13_perm[j38];
			}
			for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
				fRec12_tmp[j40] = fRec12_perm[j40];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec6[(i + fYec6_idx) & 255] = fSlow2 * fRec12[i - 1] + 5.2995043 * fZec6[i];
				fRec13[i] = fSlow32 * fYec6[(i + fYec6_idx - iSlow34) & 255] - (fSlow35 * fRec13[i - 1] + fConst6 * fRec13[i - 2]);
				fRec12[i] = fConst7 * (fRec13[i] - fRec13[i - 2]);
			}
			/* Post code */
			fYec6_idx_save = vsize;
			for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
				fRec13_perm[j39] = fRec13_tmp[vsize + j39];
			}
			for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
				fRec12_perm[j41] = fRec12_tmp[vsize + j41];
			}
			/* Recursive loop 148 */
			/* Pre code */
			fYec7_idx = (fYec7_idx + fYec7_idx_save) & 255;
			for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
				fRec15_tmp[j44] = fRec15_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
				fRec14_tmp[j46] = fRec14_perm[j46];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec7[(i + fYec7_idx) & 255] = fSlow2 * fRec14[i - 1] + 5.2995043 * fZec7[i];
				fRec15[i] = fSlow37 * fYec7[(i + fYec7_idx - iSlow39) & 255] - (fSlow40 * fRec15[i - 1] + fConst6 * fRec15[i - 2]);
				fRec14[i] = fConst7 * (fRec15[i] - fRec15[i - 2]);
			}
			/* Post code */
			fYec7_idx_save = vsize;
			for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
				fRec15_perm[j45] = fRec15_tmp[vsize + j45];
			}
			for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
				fRec14_perm[j47] = fRec14_tmp[vsize + j47];
			}
			/* Recursive loop 149 */
			/* Pre code */
			fYec8_idx = (fYec8_idx + fYec8_idx_save) & 255;
			for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
				fRec17_tmp[j50] = fRec17_perm[j50];
			}
			for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
				fRec16_tmp[j52] = fRec16_perm[j52];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec8[(i + fYec8_idx) & 255] = fSlow2 * fRec16[i - 1] + 5.2995043 * fZec8[i];
				fRec17[i] = fSlow42 * fYec8[(i + fYec8_idx - iSlow44) & 255] - (fSlow45 * fRec17[i - 1] + fConst6 * fRec17[i - 2]);
				fRec16[i] = fConst7 * (fRec17[i] - fRec17[i - 2]);
			}
			/* Post code */
			fYec8_idx_save = vsize;
			for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
				fRec17_perm[j51] = fRec17_tmp[vsize + j51];
			}
			for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
				fRec16_perm[j53] = fRec16_tmp[vsize + j53];
			}
			/* Recursive loop 150 */
			/* Pre code */
			fYec9_idx = (fYec9_idx + fYec9_idx_save) & 255;
			for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
				fRec19_tmp[j56] = fRec19_perm[j56];
			}
			for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
				fRec18_tmp[j58] = fRec18_perm[j58];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec9[(i + fYec9_idx) & 255] = fSlow2 * fRec18[i - 1] + 5.2995043 * fZec9[i];
				fRec19[i] = fSlow47 * fYec9[(i + fYec9_idx - iSlow49) & 255] - (fSlow50 * fRec19[i - 1] + fConst6 * fRec19[i - 2]);
				fRec18[i] = fConst7 * (fRec19[i] - fRec19[i - 2]);
			}
			/* Post code */
			fYec9_idx_save = vsize;
			for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
				fRec19_perm[j57] = fRec19_tmp[vsize + j57];
			}
			for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
				fRec18_perm[j59] = fRec18_tmp[vsize + j59];
			}
			/* Recursive loop 151 */
			/* Pre code */
			fYec10_idx = (fYec10_idx + fYec10_idx_save) & 127;
			for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
				fRec21_tmp[j60] = fRec21_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
				fRec20_tmp[j62] = fRec20_perm[j62];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec10[(i + fYec10_idx) & 127] = fZec10[i] + fSlow2 * fRec20[i - 1];
				fRec21[i] = fSlow51 * fYec10[(i + fYec10_idx - iSlow52) & 127] - (fSlow53 * fRec21[i - 1] + fConst6 * fRec21[i - 2]);
				fRec20[i] = fConst7 * (fRec21[i] - fRec21[i - 2]);
			}
			/* Post code */
			fYec10_idx_save = vsize;
			for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
				fRec21_perm[j61] = fRec21_tmp[vsize + j61];
			}
			for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
				fRec20_perm[j63] = fRec20_tmp[vsize + j63];
			}
			/* Recursive loop 152 */
			/* Pre code */
			fYec11_idx = (fYec11_idx + fYec11_idx_save) & 127;
			for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
				fRec23_tmp[j64] = fRec23_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
				fRec22_tmp[j66] = fRec22_perm[j66];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec11[(i + fYec11_idx) & 127] = fSlow2 * fRec22[i - 1] + fZec10[i];
				fRec23[i] = fSlow54 * fYec11[(i + fYec11_idx - iSlow55) & 127] - (fSlow56 * fRec23[i - 1] + fConst6 * fRec23[i - 2]);
				fRec22[i] = fConst7 * (fRec23[i] - fRec23[i - 2]);
			}
			/* Post code */
			fYec11_idx_save = vsize;
			for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
				fRec23_perm[j65] = fRec23_tmp[vsize + j65];
			}
			for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
				fRec22_perm[j67] = fRec22_tmp[vsize + j67];
			}
			/* Recursive loop 153 */
			/* Pre code */
			fYec12_idx = (fYec12_idx + fYec12_idx_save) & 127;
			for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
				fRec25_tmp[j68] = fRec25_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
				fRec24_tmp[j70] = fRec24_perm[j70];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec12[(i + fYec12_idx) & 127] = fZec11[i] + fSlow2 * fRec24[i - 1];
				fRec25[i] = fSlow57 * fYec12[(i + fYec12_idx - iSlow58) & 127] - (fSlow59 * fRec25[i - 1] + fConst6 * fRec25[i - 2]);
				fRec24[i] = fConst7 * (fRec25[i] - fRec25[i - 2]);
			}
			/* Post code */
			fYec12_idx_save = vsize;
			for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
				fRec25_perm[j69] = fRec25_tmp[vsize + j69];
			}
			for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
				fRec24_perm[j71] = fRec24_tmp[vsize + j71];
			}
			/* Recursive loop 154 */
			/* Pre code */
			fYec13_idx = (fYec13_idx + fYec13_idx_save) & 127;
			for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
				fRec27_tmp[j72] = fRec27_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
				fRec26_tmp[j74] = fRec26_perm[j74];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec13[(i + fYec13_idx) & 127] = fSlow2 * fRec26[i - 1] + fZec11[i];
				fRec27[i] = fSlow60 * fYec13[(i + fYec13_idx - iSlow61) & 127] - (fSlow62 * fRec27[i - 1] + fConst6 * fRec27[i - 2]);
				fRec26[i] = fConst7 * (fRec27[i] - fRec27[i - 2]);
			}
			/* Post code */
			fYec13_idx_save = vsize;
			for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
				fRec27_perm[j73] = fRec27_tmp[vsize + j73];
			}
			for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
				fRec26_perm[j75] = fRec26_tmp[vsize + j75];
			}
			/* Recursive loop 155 */
			/* Pre code */
			fYec14_idx = (fYec14_idx + fYec14_idx_save) & 127;
			for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
				fRec29_tmp[j76] = fRec29_perm[j76];
			}
			for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
				fRec28_tmp[j78] = fRec28_perm[j78];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec14[(i + fYec14_idx) & 127] = fZec12[i] + fSlow2 * fRec28[i - 1];
				fRec29[i] = fSlow63 * fYec14[(i + fYec14_idx - iSlow64) & 127] - (fSlow65 * fRec29[i - 1] + fConst6 * fRec29[i - 2]);
				fRec28[i] = fConst7 * (fRec29[i] - fRec29[i - 2]);
			}
			/* Post code */
			fYec14_idx_save = vsize;
			for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
				fRec29_perm[j77] = fRec29_tmp[vsize + j77];
			}
			for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
				fRec28_perm[j79] = fRec28_tmp[vsize + j79];
			}
			/* Recursive loop 156 */
			/* Pre code */
			fYec15_idx = (fYec15_idx + fYec15_idx_save) & 127;
			for (int j80 = 0; j80 < 4; j80 = j80 + 1) {
				fRec31_tmp[j80] = fRec31_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = j82 + 1) {
				fRec30_tmp[j82] = fRec30_perm[j82];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec15[(i + fYec15_idx) & 127] = fSlow2 * fRec30[i - 1] + fZec12[i];
				fRec31[i] = fSlow66 * fYec15[(i + fYec15_idx - iSlow67) & 127] - (fSlow68 * fRec31[i - 1] + fConst6 * fRec31[i - 2]);
				fRec30[i] = fConst7 * (fRec31[i] - fRec31[i - 2]);
			}
			/* Post code */
			fYec15_idx_save = vsize;
			for (int j81 = 0; j81 < 4; j81 = j81 + 1) {
				fRec31_perm[j81] = fRec31_tmp[vsize + j81];
			}
			for (int j83 = 0; j83 < 4; j83 = j83 + 1) {
				fRec30_perm[j83] = fRec30_tmp[vsize + j83];
			}
			/* Recursive loop 157 */
			/* Pre code */
			fYec16_idx = (fYec16_idx + fYec16_idx_save) & 511;
			for (int j84 = 0; j84 < 4; j84 = j84 + 1) {
				fRec33_tmp[j84] = fRec33_perm[j84];
			}
			for (int j86 = 0; j86 < 4; j86 = j86 + 1) {
				fRec32_tmp[j86] = fRec32_perm[j86];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec16[(i + fYec16_idx) & 511] = fZec13[i] + fSlow2 * fRec32[i - 1];
				fRec33[i] = fSlow69 * fYec16[(i + fYec16_idx - iSlow70) & 511] - (fSlow71 * fRec33[i - 1] + fConst6 * fRec33[i - 2]);
				fRec32[i] = fConst7 * (fRec33[i] - fRec33[i - 2]);
			}
			/* Post code */
			fYec16_idx_save = vsize;
			for (int j85 = 0; j85 < 4; j85 = j85 + 1) {
				fRec33_perm[j85] = fRec33_tmp[vsize + j85];
			}
			for (int j87 = 0; j87 < 4; j87 = j87 + 1) {
				fRec32_perm[j87] = fRec32_tmp[vsize + j87];
			}
			/* Recursive loop 158 */
			/* Pre code */
			fYec17_idx = (fYec17_idx + fYec17_idx_save) & 511;
			for (int j88 = 0; j88 < 4; j88 = j88 + 1) {
				fRec35_tmp[j88] = fRec35_perm[j88];
			}
			for (int j90 = 0; j90 < 4; j90 = j90 + 1) {
				fRec34_tmp[j90] = fRec34_perm[j90];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec17[(i + fYec17_idx) & 511] = fSlow2 * fRec34[i - 1] + fZec13[i];
				fRec35[i] = fSlow72 * fYec17[(i + fYec17_idx - iSlow73) & 511] - (fSlow74 * fRec35[i - 1] + fConst6 * fRec35[i - 2]);
				fRec34[i] = fConst7 * (fRec35[i] - fRec35[i - 2]);
			}
			/* Post code */
			fYec17_idx_save = vsize;
			for (int j89 = 0; j89 < 4; j89 = j89 + 1) {
				fRec35_perm[j89] = fRec35_tmp[vsize + j89];
			}
			for (int j91 = 0; j91 < 4; j91 = j91 + 1) {
				fRec34_perm[j91] = fRec34_tmp[vsize + j91];
			}
			/* Recursive loop 159 */
			/* Pre code */
			fYec18_idx = (fYec18_idx + fYec18_idx_save) & 1023;
			for (int j92 = 0; j92 < 4; j92 = j92 + 1) {
				fRec37_tmp[j92] = fRec37_perm[j92];
			}
			for (int j94 = 0; j94 < 4; j94 = j94 + 1) {
				fRec36_tmp[j94] = fRec36_perm[j94];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec18[(i + fYec18_idx) & 1023] = fZec14[i] + fSlow2 * fRec36[i - 1];
				fRec37[i] = fSlow75 * fYec18[(i + fYec18_idx - iSlow76) & 1023] - (fSlow77 * fRec37[i - 1] + fConst6 * fRec37[i - 2]);
				fRec36[i] = fConst7 * (fRec37[i] - fRec37[i - 2]);
			}
			/* Post code */
			fYec18_idx_save = vsize;
			for (int j93 = 0; j93 < 4; j93 = j93 + 1) {
				fRec37_perm[j93] = fRec37_tmp[vsize + j93];
			}
			for (int j95 = 0; j95 < 4; j95 = j95 + 1) {
				fRec36_perm[j95] = fRec36_tmp[vsize + j95];
			}
			/* Recursive loop 160 */
			/* Pre code */
			fYec19_idx = (fYec19_idx + fYec19_idx_save) & 1023;
			for (int j96 = 0; j96 < 4; j96 = j96 + 1) {
				fRec39_tmp[j96] = fRec39_perm[j96];
			}
			for (int j98 = 0; j98 < 4; j98 = j98 + 1) {
				fRec38_tmp[j98] = fRec38_perm[j98];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec19[(i + fYec19_idx) & 1023] = fSlow2 * fRec38[i - 1] + fZec14[i];
				fRec39[i] = fSlow78 * fYec19[(i + fYec19_idx - iSlow79) & 1023] - (fSlow80 * fRec39[i - 1] + fConst6 * fRec39[i - 2]);
				fRec38[i] = fConst7 * (fRec39[i] - fRec39[i - 2]);
			}
			/* Post code */
			fYec19_idx_save = vsize;
			for (int j97 = 0; j97 < 4; j97 = j97 + 1) {
				fRec39_perm[j97] = fRec39_tmp[vsize + j97];
			}
			for (int j99 = 0; j99 < 4; j99 = j99 + 1) {
				fRec38_perm[j99] = fRec38_tmp[vsize + j99];
			}
			/* Recursive loop 161 */
			/* Pre code */
			fYec20_idx = (fYec20_idx + fYec20_idx_save) & 127;
			for (int j100 = 0; j100 < 4; j100 = j100 + 1) {
				fRec41_tmp[j100] = fRec41_perm[j100];
			}
			for (int j102 = 0; j102 < 4; j102 = j102 + 1) {
				fRec40_tmp[j102] = fRec40_perm[j102];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec20[(i + fYec20_idx) & 127] = fZec15[i] + fSlow2 * fRec40[i - 1];
				fRec41[i] = fSlow81 * fYec20[(i + fYec20_idx - iSlow82) & 127] - (fSlow83 * fRec41[i - 1] + fConst6 * fRec41[i - 2]);
				fRec40[i] = fConst7 * (fRec41[i] - fRec41[i - 2]);
			}
			/* Post code */
			fYec20_idx_save = vsize;
			for (int j101 = 0; j101 < 4; j101 = j101 + 1) {
				fRec41_perm[j101] = fRec41_tmp[vsize + j101];
			}
			for (int j103 = 0; j103 < 4; j103 = j103 + 1) {
				fRec40_perm[j103] = fRec40_tmp[vsize + j103];
			}
			/* Recursive loop 162 */
			/* Pre code */
			fYec21_idx = (fYec21_idx + fYec21_idx_save) & 127;
			for (int j104 = 0; j104 < 4; j104 = j104 + 1) {
				fRec43_tmp[j104] = fRec43_perm[j104];
			}
			for (int j106 = 0; j106 < 4; j106 = j106 + 1) {
				fRec42_tmp[j106] = fRec42_perm[j106];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec21[(i + fYec21_idx) & 127] = fSlow2 * fRec42[i - 1] + fZec15[i];
				fRec43[i] = fSlow84 * fYec21[(i + fYec21_idx - iSlow85) & 127] - (fSlow86 * fRec43[i - 1] + fConst6 * fRec43[i - 2]);
				fRec42[i] = fConst7 * (fRec43[i] - fRec43[i - 2]);
			}
			/* Post code */
			fYec21_idx_save = vsize;
			for (int j105 = 0; j105 < 4; j105 = j105 + 1) {
				fRec43_perm[j105] = fRec43_tmp[vsize + j105];
			}
			for (int j107 = 0; j107 < 4; j107 = j107 + 1) {
				fRec42_perm[j107] = fRec42_tmp[vsize + j107];
			}
			/* Recursive loop 163 */
			/* Pre code */
			fYec22_idx = (fYec22_idx + fYec22_idx_save) & 127;
			for (int j108 = 0; j108 < 4; j108 = j108 + 1) {
				fRec45_tmp[j108] = fRec45_perm[j108];
			}
			for (int j110 = 0; j110 < 4; j110 = j110 + 1) {
				fRec44_tmp[j110] = fRec44_perm[j110];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec22[(i + fYec22_idx) & 127] = fZec16[i] + fSlow2 * fRec44[i - 1];
				fRec45[i] = fSlow87 * fYec22[(i + fYec22_idx - iSlow88) & 127] - (fSlow89 * fRec45[i - 1] + fConst6 * fRec45[i - 2]);
				fRec44[i] = fConst7 * (fRec45[i] - fRec45[i - 2]);
			}
			/* Post code */
			fYec22_idx_save = vsize;
			for (int j109 = 0; j109 < 4; j109 = j109 + 1) {
				fRec45_perm[j109] = fRec45_tmp[vsize + j109];
			}
			for (int j111 = 0; j111 < 4; j111 = j111 + 1) {
				fRec44_perm[j111] = fRec44_tmp[vsize + j111];
			}
			/* Recursive loop 164 */
			/* Pre code */
			fYec23_idx = (fYec23_idx + fYec23_idx_save) & 127;
			for (int j112 = 0; j112 < 4; j112 = j112 + 1) {
				fRec47_tmp[j112] = fRec47_perm[j112];
			}
			for (int j114 = 0; j114 < 4; j114 = j114 + 1) {
				fRec46_tmp[j114] = fRec46_perm[j114];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec23[(i + fYec23_idx) & 127] = fSlow2 * fRec46[i - 1] + fZec16[i];
				fRec47[i] = fSlow90 * fYec23[(i + fYec23_idx - iSlow91) & 127] - (fSlow92 * fRec47[i - 1] + fConst6 * fRec47[i - 2]);
				fRec46[i] = fConst7 * (fRec47[i] - fRec47[i - 2]);
			}
			/* Post code */
			fYec23_idx_save = vsize;
			for (int j113 = 0; j113 < 4; j113 = j113 + 1) {
				fRec47_perm[j113] = fRec47_tmp[vsize + j113];
			}
			for (int j115 = 0; j115 < 4; j115 = j115 + 1) {
				fRec46_perm[j115] = fRec46_tmp[vsize + j115];
			}
			/* Recursive loop 165 */
			/* Pre code */
			fYec24_idx = (fYec24_idx + fYec24_idx_save) & 127;
			for (int j116 = 0; j116 < 4; j116 = j116 + 1) {
				fRec49_tmp[j116] = fRec49_perm[j116];
			}
			for (int j118 = 0; j118 < 4; j118 = j118 + 1) {
				fRec48_tmp[j118] = fRec48_perm[j118];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec24[(i + fYec24_idx) & 127] = fZec17[i] + fSlow2 * fRec48[i - 1];
				fRec49[i] = fSlow93 * fYec24[(i + fYec24_idx - iSlow94) & 127] - (fSlow95 * fRec49[i - 1] + fConst6 * fRec49[i - 2]);
				fRec48[i] = fConst7 * (fRec49[i] - fRec49[i - 2]);
			}
			/* Post code */
			fYec24_idx_save = vsize;
			for (int j117 = 0; j117 < 4; j117 = j117 + 1) {
				fRec49_perm[j117] = fRec49_tmp[vsize + j117];
			}
			for (int j119 = 0; j119 < 4; j119 = j119 + 1) {
				fRec48_perm[j119] = fRec48_tmp[vsize + j119];
			}
			/* Recursive loop 166 */
			/* Pre code */
			fYec25_idx = (fYec25_idx + fYec25_idx_save) & 127;
			for (int j120 = 0; j120 < 4; j120 = j120 + 1) {
				fRec51_tmp[j120] = fRec51_perm[j120];
			}
			for (int j122 = 0; j122 < 4; j122 = j122 + 1) {
				fRec50_tmp[j122] = fRec50_perm[j122];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec25[(i + fYec25_idx) & 127] = fSlow2 * fRec50[i - 1] + fZec17[i];
				fRec51[i] = fSlow96 * fYec25[(i + fYec25_idx - iSlow97) & 127] - (fSlow98 * fRec51[i - 1] + fConst6 * fRec51[i - 2]);
				fRec50[i] = fConst7 * (fRec51[i] - fRec51[i - 2]);
			}
			/* Post code */
			fYec25_idx_save = vsize;
			for (int j121 = 0; j121 < 4; j121 = j121 + 1) {
				fRec51_perm[j121] = fRec51_tmp[vsize + j121];
			}
			for (int j123 = 0; j123 < 4; j123 = j123 + 1) {
				fRec50_perm[j123] = fRec50_tmp[vsize + j123];
			}
			/* Recursive loop 167 */
			/* Pre code */
			fYec26_idx = (fYec26_idx + fYec26_idx_save) & 511;
			for (int j124 = 0; j124 < 4; j124 = j124 + 1) {
				fRec53_tmp[j124] = fRec53_perm[j124];
			}
			for (int j126 = 0; j126 < 4; j126 = j126 + 1) {
				fRec52_tmp[j126] = fRec52_perm[j126];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec26[(i + fYec26_idx) & 511] = fZec18[i] + fSlow2 * fRec52[i - 1];
				fRec53[i] = fSlow99 * fYec26[(i + fYec26_idx - iSlow100) & 511] - (fSlow101 * fRec53[i - 1] + fConst6 * fRec53[i - 2]);
				fRec52[i] = fConst7 * (fRec53[i] - fRec53[i - 2]);
			}
			/* Post code */
			fYec26_idx_save = vsize;
			for (int j125 = 0; j125 < 4; j125 = j125 + 1) {
				fRec53_perm[j125] = fRec53_tmp[vsize + j125];
			}
			for (int j127 = 0; j127 < 4; j127 = j127 + 1) {
				fRec52_perm[j127] = fRec52_tmp[vsize + j127];
			}
			/* Recursive loop 168 */
			/* Pre code */
			fYec27_idx = (fYec27_idx + fYec27_idx_save) & 511;
			for (int j128 = 0; j128 < 4; j128 = j128 + 1) {
				fRec55_tmp[j128] = fRec55_perm[j128];
			}
			for (int j130 = 0; j130 < 4; j130 = j130 + 1) {
				fRec54_tmp[j130] = fRec54_perm[j130];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec27[(i + fYec27_idx) & 511] = fSlow2 * fRec54[i - 1] + fZec18[i];
				fRec55[i] = fSlow102 * fYec27[(i + fYec27_idx - iSlow103) & 511] - (fSlow104 * fRec55[i - 1] + fConst6 * fRec55[i - 2]);
				fRec54[i] = fConst7 * (fRec55[i] - fRec55[i - 2]);
			}
			/* Post code */
			fYec27_idx_save = vsize;
			for (int j129 = 0; j129 < 4; j129 = j129 + 1) {
				fRec55_perm[j129] = fRec55_tmp[vsize + j129];
			}
			for (int j131 = 0; j131 < 4; j131 = j131 + 1) {
				fRec54_perm[j131] = fRec54_tmp[vsize + j131];
			}
			/* Recursive loop 169 */
			/* Pre code */
			fYec28_idx = (fYec28_idx + fYec28_idx_save) & 1023;
			for (int j132 = 0; j132 < 4; j132 = j132 + 1) {
				fRec57_tmp[j132] = fRec57_perm[j132];
			}
			for (int j134 = 0; j134 < 4; j134 = j134 + 1) {
				fRec56_tmp[j134] = fRec56_perm[j134];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec28[(i + fYec28_idx) & 1023] = fZec19[i] + fSlow2 * fRec56[i - 1];
				fRec57[i] = fSlow105 * fYec28[(i + fYec28_idx - iSlow106) & 1023] - (fSlow107 * fRec57[i - 1] + fConst6 * fRec57[i - 2]);
				fRec56[i] = fConst7 * (fRec57[i] - fRec57[i - 2]);
			}
			/* Post code */
			fYec28_idx_save = vsize;
			for (int j133 = 0; j133 < 4; j133 = j133 + 1) {
				fRec57_perm[j133] = fRec57_tmp[vsize + j133];
			}
			for (int j135 = 0; j135 < 4; j135 = j135 + 1) {
				fRec56_perm[j135] = fRec56_tmp[vsize + j135];
			}
			/* Recursive loop 170 */
			/* Pre code */
			fYec29_idx = (fYec29_idx + fYec29_idx_save) & 1023;
			for (int j136 = 0; j136 < 4; j136 = j136 + 1) {
				fRec59_tmp[j136] = fRec59_perm[j136];
			}
			for (int j138 = 0; j138 < 4; j138 = j138 + 1) {
				fRec58_tmp[j138] = fRec58_perm[j138];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec29[(i + fYec29_idx) & 1023] = fSlow2 * fRec58[i - 1] + fZec19[i];
				fRec59[i] = fSlow108 * fYec29[(i + fYec29_idx - iSlow109) & 1023] - (fSlow110 * fRec59[i - 1] + fConst6 * fRec59[i - 2]);
				fRec58[i] = fConst7 * (fRec59[i] - fRec59[i - 2]);
			}
			/* Post code */
			fYec29_idx_save = vsize;
			for (int j137 = 0; j137 < 4; j137 = j137 + 1) {
				fRec59_perm[j137] = fRec59_tmp[vsize + j137];
			}
			for (int j139 = 0; j139 < 4; j139 = j139 + 1) {
				fRec58_perm[j139] = fRec58_tmp[vsize + j139];
			}
			/* Recursive loop 171 */
			/* Pre code */
			fYec30_idx = (fYec30_idx + fYec30_idx_save) & 127;
			for (int j140 = 0; j140 < 4; j140 = j140 + 1) {
				fRec61_tmp[j140] = fRec61_perm[j140];
			}
			for (int j142 = 0; j142 < 4; j142 = j142 + 1) {
				fRec60_tmp[j142] = fRec60_perm[j142];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec30[(i + fYec30_idx) & 127] = fZec20[i] + fSlow2 * fRec60[i - 1];
				fRec61[i] = fSlow111 * fYec30[(i + fYec30_idx - iSlow112) & 127] - (fSlow113 * fRec61[i - 1] + fConst6 * fRec61[i - 2]);
				fRec60[i] = fConst7 * (fRec61[i] - fRec61[i - 2]);
			}
			/* Post code */
			fYec30_idx_save = vsize;
			for (int j141 = 0; j141 < 4; j141 = j141 + 1) {
				fRec61_perm[j141] = fRec61_tmp[vsize + j141];
			}
			for (int j143 = 0; j143 < 4; j143 = j143 + 1) {
				fRec60_perm[j143] = fRec60_tmp[vsize + j143];
			}
			/* Recursive loop 172 */
			/* Pre code */
			fYec31_idx = (fYec31_idx + fYec31_idx_save) & 127;
			for (int j144 = 0; j144 < 4; j144 = j144 + 1) {
				fRec63_tmp[j144] = fRec63_perm[j144];
			}
			for (int j146 = 0; j146 < 4; j146 = j146 + 1) {
				fRec62_tmp[j146] = fRec62_perm[j146];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec31[(i + fYec31_idx) & 127] = fSlow2 * fRec62[i - 1] + fZec20[i];
				fRec63[i] = fSlow114 * fYec31[(i + fYec31_idx - iSlow115) & 127] - (fSlow116 * fRec63[i - 1] + fConst6 * fRec63[i - 2]);
				fRec62[i] = fConst7 * (fRec63[i] - fRec63[i - 2]);
			}
			/* Post code */
			fYec31_idx_save = vsize;
			for (int j145 = 0; j145 < 4; j145 = j145 + 1) {
				fRec63_perm[j145] = fRec63_tmp[vsize + j145];
			}
			for (int j147 = 0; j147 < 4; j147 = j147 + 1) {
				fRec62_perm[j147] = fRec62_tmp[vsize + j147];
			}
			/* Recursive loop 173 */
			/* Pre code */
			fYec32_idx = (fYec32_idx + fYec32_idx_save) & 127;
			for (int j148 = 0; j148 < 4; j148 = j148 + 1) {
				fRec65_tmp[j148] = fRec65_perm[j148];
			}
			for (int j150 = 0; j150 < 4; j150 = j150 + 1) {
				fRec64_tmp[j150] = fRec64_perm[j150];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec32[(i + fYec32_idx) & 127] = fZec21[i] + fSlow2 * fRec64[i - 1];
				fRec65[i] = fSlow117 * fYec32[(i + fYec32_idx - iSlow118) & 127] - (fSlow119 * fRec65[i - 1] + fConst6 * fRec65[i - 2]);
				fRec64[i] = fConst7 * (fRec65[i] - fRec65[i - 2]);
			}
			/* Post code */
			fYec32_idx_save = vsize;
			for (int j149 = 0; j149 < 4; j149 = j149 + 1) {
				fRec65_perm[j149] = fRec65_tmp[vsize + j149];
			}
			for (int j151 = 0; j151 < 4; j151 = j151 + 1) {
				fRec64_perm[j151] = fRec64_tmp[vsize + j151];
			}
			/* Recursive loop 174 */
			/* Pre code */
			fYec33_idx = (fYec33_idx + fYec33_idx_save) & 127;
			for (int j152 = 0; j152 < 4; j152 = j152 + 1) {
				fRec67_tmp[j152] = fRec67_perm[j152];
			}
			for (int j154 = 0; j154 < 4; j154 = j154 + 1) {
				fRec66_tmp[j154] = fRec66_perm[j154];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec33[(i + fYec33_idx) & 127] = fSlow2 * fRec66[i - 1] + fZec21[i];
				fRec67[i] = fSlow120 * fYec33[(i + fYec33_idx - iSlow121) & 127] - (fSlow122 * fRec67[i - 1] + fConst6 * fRec67[i - 2]);
				fRec66[i] = fConst7 * (fRec67[i] - fRec67[i - 2]);
			}
			/* Post code */
			fYec33_idx_save = vsize;
			for (int j153 = 0; j153 < 4; j153 = j153 + 1) {
				fRec67_perm[j153] = fRec67_tmp[vsize + j153];
			}
			for (int j155 = 0; j155 < 4; j155 = j155 + 1) {
				fRec66_perm[j155] = fRec66_tmp[vsize + j155];
			}
			/* Recursive loop 175 */
			/* Pre code */
			fYec34_idx = (fYec34_idx + fYec34_idx_save) & 127;
			for (int j156 = 0; j156 < 4; j156 = j156 + 1) {
				fRec69_tmp[j156] = fRec69_perm[j156];
			}
			for (int j158 = 0; j158 < 4; j158 = j158 + 1) {
				fRec68_tmp[j158] = fRec68_perm[j158];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec34[(i + fYec34_idx) & 127] = fZec22[i] + fSlow2 * fRec68[i - 1];
				fRec69[i] = fSlow123 * fYec34[(i + fYec34_idx - iSlow124) & 127] - (fSlow125 * fRec69[i - 1] + fConst6 * fRec69[i - 2]);
				fRec68[i] = fConst7 * (fRec69[i] - fRec69[i - 2]);
			}
			/* Post code */
			fYec34_idx_save = vsize;
			for (int j157 = 0; j157 < 4; j157 = j157 + 1) {
				fRec69_perm[j157] = fRec69_tmp[vsize + j157];
			}
			for (int j159 = 0; j159 < 4; j159 = j159 + 1) {
				fRec68_perm[j159] = fRec68_tmp[vsize + j159];
			}
			/* Recursive loop 176 */
			/* Pre code */
			fYec35_idx = (fYec35_idx + fYec35_idx_save) & 127;
			for (int j160 = 0; j160 < 4; j160 = j160 + 1) {
				fRec71_tmp[j160] = fRec71_perm[j160];
			}
			for (int j162 = 0; j162 < 4; j162 = j162 + 1) {
				fRec70_tmp[j162] = fRec70_perm[j162];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec35[(i + fYec35_idx) & 127] = fSlow2 * fRec70[i - 1] + fZec22[i];
				fRec71[i] = fSlow126 * fYec35[(i + fYec35_idx - iSlow127) & 127] - (fSlow128 * fRec71[i - 1] + fConst6 * fRec71[i - 2]);
				fRec70[i] = fConst7 * (fRec71[i] - fRec71[i - 2]);
			}
			/* Post code */
			fYec35_idx_save = vsize;
			for (int j161 = 0; j161 < 4; j161 = j161 + 1) {
				fRec71_perm[j161] = fRec71_tmp[vsize + j161];
			}
			for (int j163 = 0; j163 < 4; j163 = j163 + 1) {
				fRec70_perm[j163] = fRec70_tmp[vsize + j163];
			}
			/* Recursive loop 177 */
			/* Pre code */
			fYec36_idx = (fYec36_idx + fYec36_idx_save) & 511;
			for (int j164 = 0; j164 < 4; j164 = j164 + 1) {
				fRec73_tmp[j164] = fRec73_perm[j164];
			}
			for (int j166 = 0; j166 < 4; j166 = j166 + 1) {
				fRec72_tmp[j166] = fRec72_perm[j166];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec36[(i + fYec36_idx) & 511] = fZec23[i] + fSlow2 * fRec72[i - 1];
				fRec73[i] = fSlow129 * fYec36[(i + fYec36_idx - iSlow130) & 511] - (fSlow131 * fRec73[i - 1] + fConst6 * fRec73[i - 2]);
				fRec72[i] = fConst7 * (fRec73[i] - fRec73[i - 2]);
			}
			/* Post code */
			fYec36_idx_save = vsize;
			for (int j165 = 0; j165 < 4; j165 = j165 + 1) {
				fRec73_perm[j165] = fRec73_tmp[vsize + j165];
			}
			for (int j167 = 0; j167 < 4; j167 = j167 + 1) {
				fRec72_perm[j167] = fRec72_tmp[vsize + j167];
			}
			/* Recursive loop 178 */
			/* Pre code */
			fYec37_idx = (fYec37_idx + fYec37_idx_save) & 511;
			for (int j168 = 0; j168 < 4; j168 = j168 + 1) {
				fRec75_tmp[j168] = fRec75_perm[j168];
			}
			for (int j170 = 0; j170 < 4; j170 = j170 + 1) {
				fRec74_tmp[j170] = fRec74_perm[j170];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec37[(i + fYec37_idx) & 511] = fSlow2 * fRec74[i - 1] + fZec23[i];
				fRec75[i] = fSlow132 * fYec37[(i + fYec37_idx - iSlow133) & 511] - (fSlow134 * fRec75[i - 1] + fConst6 * fRec75[i - 2]);
				fRec74[i] = fConst7 * (fRec75[i] - fRec75[i - 2]);
			}
			/* Post code */
			fYec37_idx_save = vsize;
			for (int j169 = 0; j169 < 4; j169 = j169 + 1) {
				fRec75_perm[j169] = fRec75_tmp[vsize + j169];
			}
			for (int j171 = 0; j171 < 4; j171 = j171 + 1) {
				fRec74_perm[j171] = fRec74_tmp[vsize + j171];
			}
			/* Recursive loop 179 */
			/* Pre code */
			fYec38_idx = (fYec38_idx + fYec38_idx_save) & 1023;
			for (int j172 = 0; j172 < 4; j172 = j172 + 1) {
				fRec77_tmp[j172] = fRec77_perm[j172];
			}
			for (int j174 = 0; j174 < 4; j174 = j174 + 1) {
				fRec76_tmp[j174] = fRec76_perm[j174];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec38[(i + fYec38_idx) & 1023] = fZec24[i] + fSlow2 * fRec76[i - 1];
				fRec77[i] = fSlow135 * fYec38[(i + fYec38_idx - iSlow136) & 1023] - (fSlow137 * fRec77[i - 1] + fConst6 * fRec77[i - 2]);
				fRec76[i] = fConst7 * (fRec77[i] - fRec77[i - 2]);
			}
			/* Post code */
			fYec38_idx_save = vsize;
			for (int j173 = 0; j173 < 4; j173 = j173 + 1) {
				fRec77_perm[j173] = fRec77_tmp[vsize + j173];
			}
			for (int j175 = 0; j175 < 4; j175 = j175 + 1) {
				fRec76_perm[j175] = fRec76_tmp[vsize + j175];
			}
			/* Vectorizable loop 180 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = static_cast<FAUSTFLOAT>(2.0 * (fRec0[i] + fRec2[i] + fRec4[i] + fRec6[i] + fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i] + fRec16[i] + fRec18[i]) + fRec20[i] + fRec22[i] + fRec24[i] + fRec26[i] + fRec28[i] + fRec30[i] + fRec32[i] + fRec34[i] + fRec36[i] + fRec38[i] + fRec40[i] + fRec42[i] + fRec44[i] + fRec46[i] + fRec48[i] + fRec50[i] + fRec52[i] + fRec54[i] + fRec56[i] + fRec58[i] + fRec60[i] + fRec62[i] + fRec64[i] + fRec66[i] + fRec68[i] + fRec70[i] + fRec72[i] + fRec74[i] + fRec76[i] + fRec78[i] + fRec80[i] + fRec82[i] + fRec84[i] + fRec86[i] + fRec88[i] + fRec90[i] + fRec92[i] + fRec94[i] + fRec96[i] + fRec98[i] + fRec100[i] + fRec102[i] + fRec104[i] + fRec106[i] + fRec108[i] + fRec110[i] + fRec112[i] + fRec114[i] + fRec116[i] + fRec118[i] + fRec120[i] + fRec122[i] + fRec124[i] + fRec126[i] + fRec128[i] + fRec130[i] + fRec132[i] + fRec134[i] + fRec136[i] + fRec138[i] + fRec140[i] + fRec142[i] + fRec144[i] + fRec146[i] + fRec148[i] + fRec150[i] + fRec152[i] + fRec154[i] + fRec156[i] + fRec158[i] + fRec160[i] + fRec162[i] + fRec164[i] + fRec166[i] + fRec168[i] + fRec170[i] + fRec172[i] + fRec174[i] + fRec176[i] + fRec178[i] + fRec180[i] + fRec182[i] + fRec184[i] + fRec186[i] + fRec188[i] + fRec190[i] + fRec192[i] + fRec194[i] + fRec196[i] + fRec198[i] + fRec200[i] + fRec202[i] + fRec204[i] + fRec206[i] + fRec208[i] + fRec210[i] + fRec212[i] + fRec214[i] + fRec216[i] + fRec218[i]);
			}
		}
	}

};

#endif
