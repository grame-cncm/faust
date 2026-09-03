/* ------------------------------------------------------------
name: "reverb_designer"
Code generated with Faust 2.87.10 (https://faust.grame.fr)
Compilation options: -a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
#ifndef FAUST_INT_WRAP
#define FAUST_INT_WRAP
inline int faust_wrap_add(int a, int b) { return int((unsigned int)a + (unsigned int)b); }
inline int faust_wrap_sub(int a, int b) { return int((unsigned int)a - (unsigned int)b); }
inline int faust_wrap_mul(int a, int b) { return int((unsigned int)a * (unsigned int)b); }
#endif


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
	
	int iRec17_perm[4];
	double fRec16_perm[4];
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fRec22_perm[4];
	double fRec21_perm[4];
	FAUSTFLOAT fHslider1;
	double fRec20_perm[4];
	FAUSTFLOAT fHslider2;
	double fRec19_perm[4];
	FAUSTFLOAT fHslider3;
	double fRec18_perm[4];
	double fRec28_perm[4];
	double fRec27_perm[4];
	double fYec0_perm[4];
	double fRec26_perm[4];
	double fRec25_perm[4];
	double fRec24_perm[4];
	double fRec23_perm[4];
	double fRec33_perm[4];
	double fRec32_perm[4];
	double fYec1_perm[4];
	double fRec31_perm[4];
	double fRec30_perm[4];
	double fRec29_perm[4];
	double fRec37_perm[4];
	double fRec36_perm[4];
	double fYec2_perm[4];
	double fRec35_perm[4];
	double fRec34_perm[4];
	double fRec39_perm[4];
	double fRec38_perm[4];
	double fRec44_perm[4];
	double fRec43_perm[4];
	double fRec42_perm[4];
	double fRec41_perm[4];
	double fRec40_perm[4];
	double fRec50_perm[4];
	double fRec49_perm[4];
	double fYec3_perm[4];
	double fRec48_perm[4];
	double fRec47_perm[4];
	double fRec46_perm[4];
	double fRec45_perm[4];
	double fRec55_perm[4];
	double fRec54_perm[4];
	double fYec4_perm[4];
	double fRec53_perm[4];
	double fRec52_perm[4];
	double fRec51_perm[4];
	double fRec59_perm[4];
	double fRec58_perm[4];
	double fYec5_perm[4];
	double fRec57_perm[4];
	double fRec56_perm[4];
	double fRec61_perm[4];
	double fRec60_perm[4];
	double fRec66_perm[4];
	double fRec65_perm[4];
	double fRec64_perm[4];
	double fRec63_perm[4];
	double fRec62_perm[4];
	double fRec72_perm[4];
	double fRec71_perm[4];
	double fYec6_perm[4];
	double fRec70_perm[4];
	double fRec69_perm[4];
	double fRec68_perm[4];
	double fRec67_perm[4];
	double fRec77_perm[4];
	double fRec76_perm[4];
	double fYec7_perm[4];
	double fRec75_perm[4];
	double fRec74_perm[4];
	double fRec73_perm[4];
	double fRec81_perm[4];
	double fRec80_perm[4];
	double fYec8_perm[4];
	double fRec79_perm[4];
	double fRec78_perm[4];
	double fRec83_perm[4];
	double fRec82_perm[4];
	double fRec88_perm[4];
	double fRec87_perm[4];
	double fRec86_perm[4];
	double fRec85_perm[4];
	double fRec84_perm[4];
	double fRec94_perm[4];
	double fRec93_perm[4];
	double fYec9_perm[4];
	double fRec92_perm[4];
	double fRec91_perm[4];
	double fRec90_perm[4];
	double fRec89_perm[4];
	double fRec99_perm[4];
	double fRec98_perm[4];
	double fYec10_perm[4];
	double fRec97_perm[4];
	double fRec96_perm[4];
	double fRec95_perm[4];
	double fRec103_perm[4];
	double fRec102_perm[4];
	double fYec11_perm[4];
	double fRec101_perm[4];
	double fRec100_perm[4];
	double fRec105_perm[4];
	double fRec104_perm[4];
	double fRec110_perm[4];
	double fRec109_perm[4];
	double fRec108_perm[4];
	double fRec107_perm[4];
	double fRec106_perm[4];
	double fRec116_perm[4];
	double fRec115_perm[4];
	double fYec12_perm[4];
	double fRec114_perm[4];
	double fRec113_perm[4];
	double fRec112_perm[4];
	double fRec111_perm[4];
	double fRec121_perm[4];
	double fRec120_perm[4];
	double fYec13_perm[4];
	double fRec119_perm[4];
	double fRec118_perm[4];
	double fRec117_perm[4];
	double fRec125_perm[4];
	double fRec124_perm[4];
	double fYec14_perm[4];
	double fRec123_perm[4];
	double fRec122_perm[4];
	double fRec127_perm[4];
	double fRec126_perm[4];
	double fRec132_perm[4];
	double fRec131_perm[4];
	double fRec130_perm[4];
	double fRec129_perm[4];
	double fRec128_perm[4];
	double fRec138_perm[4];
	double fRec137_perm[4];
	double fYec15_perm[4];
	double fRec136_perm[4];
	double fRec135_perm[4];
	double fRec134_perm[4];
	double fRec133_perm[4];
	double fRec143_perm[4];
	double fRec142_perm[4];
	double fYec16_perm[4];
	double fRec141_perm[4];
	double fRec140_perm[4];
	double fRec139_perm[4];
	double fRec147_perm[4];
	double fRec146_perm[4];
	double fYec17_perm[4];
	double fRec145_perm[4];
	double fRec144_perm[4];
	double fRec149_perm[4];
	double fRec148_perm[4];
	double fRec154_perm[4];
	double fRec153_perm[4];
	double fRec152_perm[4];
	double fRec151_perm[4];
	double fRec150_perm[4];
	double fRec160_perm[4];
	double fRec159_perm[4];
	double fYec18_perm[4];
	double fRec158_perm[4];
	double fRec157_perm[4];
	double fRec156_perm[4];
	double fRec155_perm[4];
	double fRec165_perm[4];
	double fRec164_perm[4];
	double fYec19_perm[4];
	double fRec163_perm[4];
	double fRec162_perm[4];
	double fRec161_perm[4];
	double fRec169_perm[4];
	double fRec168_perm[4];
	double fYec20_perm[4];
	double fRec167_perm[4];
	double fRec166_perm[4];
	double fRec171_perm[4];
	double fRec170_perm[4];
	double fRec176_perm[4];
	double fRec175_perm[4];
	double fRec174_perm[4];
	double fRec173_perm[4];
	double fRec172_perm[4];
	double fRec182_perm[4];
	double fRec181_perm[4];
	double fYec21_perm[4];
	double fRec180_perm[4];
	double fRec179_perm[4];
	double fRec178_perm[4];
	double fRec177_perm[4];
	double fRec187_perm[4];
	double fRec186_perm[4];
	double fYec22_perm[4];
	double fRec185_perm[4];
	double fRec184_perm[4];
	double fRec183_perm[4];
	double fRec191_perm[4];
	double fRec190_perm[4];
	double fYec23_perm[4];
	double fRec189_perm[4];
	double fRec188_perm[4];
	double fRec193_perm[4];
	double fRec192_perm[4];
	double fRec198_perm[4];
	double fRec197_perm[4];
	double fRec196_perm[4];
	double fRec195_perm[4];
	double fRec194_perm[4];
	double fRec204_perm[4];
	double fRec203_perm[4];
	double fYec24_perm[4];
	double fRec202_perm[4];
	double fRec201_perm[4];
	double fRec200_perm[4];
	double fRec199_perm[4];
	double fRec209_perm[4];
	double fRec208_perm[4];
	double fYec25_perm[4];
	double fRec207_perm[4];
	double fRec206_perm[4];
	double fRec205_perm[4];
	double fRec213_perm[4];
	double fRec212_perm[4];
	double fYec26_perm[4];
	double fRec211_perm[4];
	double fRec210_perm[4];
	double fRec215_perm[4];
	double fRec214_perm[4];
	double fRec220_perm[4];
	double fRec219_perm[4];
	double fRec218_perm[4];
	double fRec217_perm[4];
	double fRec216_perm[4];
	double fRec226_perm[4];
	double fRec225_perm[4];
	double fYec27_perm[4];
	double fRec224_perm[4];
	double fRec223_perm[4];
	double fRec222_perm[4];
	double fRec221_perm[4];
	double fRec231_perm[4];
	double fRec230_perm[4];
	double fYec28_perm[4];
	double fRec229_perm[4];
	double fRec228_perm[4];
	double fRec227_perm[4];
	double fRec235_perm[4];
	double fRec234_perm[4];
	double fYec29_perm[4];
	double fRec233_perm[4];
	double fRec232_perm[4];
	double fRec237_perm[4];
	double fRec236_perm[4];
	double fRec242_perm[4];
	double fRec241_perm[4];
	double fRec240_perm[4];
	double fRec239_perm[4];
	double fRec238_perm[4];
	double fRec248_perm[4];
	double fRec247_perm[4];
	double fYec30_perm[4];
	double fRec246_perm[4];
	double fRec245_perm[4];
	double fRec244_perm[4];
	double fRec243_perm[4];
	double fRec253_perm[4];
	double fRec252_perm[4];
	double fYec31_perm[4];
	double fRec251_perm[4];
	double fRec250_perm[4];
	double fRec249_perm[4];
	double fRec257_perm[4];
	double fRec256_perm[4];
	double fYec32_perm[4];
	double fRec255_perm[4];
	double fRec254_perm[4];
	double fRec259_perm[4];
	double fRec258_perm[4];
	double fRec264_perm[4];
	double fRec263_perm[4];
	double fRec262_perm[4];
	double fRec261_perm[4];
	double fRec260_perm[4];
	double fRec270_perm[4];
	double fRec269_perm[4];
	double fYec33_perm[4];
	double fRec268_perm[4];
	double fRec267_perm[4];
	double fRec266_perm[4];
	double fRec265_perm[4];
	double fRec275_perm[4];
	double fRec274_perm[4];
	double fYec34_perm[4];
	double fRec273_perm[4];
	double fRec272_perm[4];
	double fRec271_perm[4];
	double fRec279_perm[4];
	double fRec278_perm[4];
	double fYec35_perm[4];
	double fRec277_perm[4];
	double fRec276_perm[4];
	double fRec281_perm[4];
	double fRec280_perm[4];
	double fRec286_perm[4];
	double fRec285_perm[4];
	double fRec284_perm[4];
	double fRec283_perm[4];
	double fRec282_perm[4];
	double fRec292_perm[4];
	double fRec291_perm[4];
	double fYec36_perm[4];
	double fRec290_perm[4];
	double fRec289_perm[4];
	double fRec288_perm[4];
	double fRec287_perm[4];
	double fRec297_perm[4];
	double fRec296_perm[4];
	double fYec37_perm[4];
	double fRec295_perm[4];
	double fRec294_perm[4];
	double fRec293_perm[4];
	double fRec301_perm[4];
	double fRec300_perm[4];
	double fYec38_perm[4];
	double fRec299_perm[4];
	double fRec298_perm[4];
	double fRec303_perm[4];
	double fRec302_perm[4];
	double fRec308_perm[4];
	double fRec307_perm[4];
	double fRec306_perm[4];
	double fRec305_perm[4];
	double fRec304_perm[4];
	double fRec314_perm[4];
	double fRec313_perm[4];
	double fYec39_perm[4];
	double fRec312_perm[4];
	double fRec311_perm[4];
	double fRec310_perm[4];
	double fRec309_perm[4];
	double fRec319_perm[4];
	double fRec318_perm[4];
	double fYec40_perm[4];
	double fRec317_perm[4];
	double fRec316_perm[4];
	double fRec315_perm[4];
	double fRec323_perm[4];
	double fRec322_perm[4];
	double fYec41_perm[4];
	double fRec321_perm[4];
	double fRec320_perm[4];
	double fRec325_perm[4];
	double fRec324_perm[4];
	double fRec330_perm[4];
	double fRec329_perm[4];
	double fRec328_perm[4];
	double fRec327_perm[4];
	double fRec326_perm[4];
	double fRec336_perm[4];
	double fRec335_perm[4];
	double fYec42_perm[4];
	double fRec334_perm[4];
	double fRec333_perm[4];
	double fRec332_perm[4];
	double fRec331_perm[4];
	double fRec341_perm[4];
	double fRec340_perm[4];
	double fYec43_perm[4];
	double fRec339_perm[4];
	double fRec338_perm[4];
	double fRec337_perm[4];
	double fRec345_perm[4];
	double fRec344_perm[4];
	double fYec44_perm[4];
	double fRec343_perm[4];
	double fRec342_perm[4];
	double fRec347_perm[4];
	double fRec346_perm[4];
	double fRec352_perm[4];
	double fRec351_perm[4];
	double fRec350_perm[4];
	double fRec349_perm[4];
	double fRec348_perm[4];
	double fRec358_perm[4];
	double fRec357_perm[4];
	double fYec45_perm[4];
	double fRec356_perm[4];
	double fRec355_perm[4];
	double fRec354_perm[4];
	double fRec353_perm[4];
	double fRec363_perm[4];
	double fRec362_perm[4];
	double fYec46_perm[4];
	double fRec361_perm[4];
	double fRec360_perm[4];
	double fRec359_perm[4];
	double fRec367_perm[4];
	double fRec366_perm[4];
	double fYec47_perm[4];
	double fRec365_perm[4];
	double fRec364_perm[4];
	double fRec369_perm[4];
	double fRec368_perm[4];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fButton0;
	double fVec0_perm[4];
	FAUSTFLOAT fButton1;
	double fVec1_perm[4];
	FAUSTFLOAT fButton2;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fCheckbox1;
	double fYec48[16384];
	int fYec48_idx;
	int fYec48_idx_save;
	double fRec0_perm[4];
	FAUSTFLOAT fButton3;
	double fVec2_perm[4];
	double fYec49[16384];
	int fYec49_idx;
	int fYec49_idx_save;
	double fRec1_perm[4];
	double fYec50[16384];
	int fYec50_idx;
	int fYec50_idx_save;
	double fRec2_perm[4];
	double fYec51[16384];
	int fYec51_idx;
	int fYec51_idx_save;
	double fRec3_perm[4];
	double fYec52[16384];
	int fYec52_idx;
	int fYec52_idx_save;
	double fRec4_perm[4];
	double fYec53[16384];
	int fYec53_idx;
	int fYec53_idx_save;
	double fRec5_perm[4];
	double fYec54[16384];
	int fYec54_idx;
	int fYec54_idx_save;
	double fRec6_perm[4];
	double fYec55[16384];
	int fYec55_idx;
	int fYec55_idx_save;
	double fRec7_perm[4];
	double fYec56[16384];
	int fYec56_idx;
	int fYec56_idx_save;
	double fRec8_perm[4];
	double fYec57[16384];
	int fYec57_idx;
	int fYec57_idx_save;
	double fRec9_perm[4];
	double fYec58[16384];
	int fYec58_idx;
	int fYec58_idx_save;
	double fRec10_perm[4];
	double fYec59[16384];
	int fYec59_idx;
	int fYec59_idx_save;
	double fRec11_perm[4];
	double fYec60[16384];
	int fYec60_idx;
	int fYec60_idx_save;
	double fRec12_perm[4];
	double fYec61[16384];
	int fYec61_idx;
	int fYec61_idx_save;
	double fRec13_perm[4];
	double fYec62[16384];
	int fYec62_idx;
	int fYec62_idx_save;
	double fRec14_perm[4];
	double fYec63[16384];
	int fYec63_idx;
	int fYec63_idx_save;
	double fRec15_perm[4];
	FAUSTFLOAT fHslider6;
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/archs/impulsearch.cpp -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs");
		m->declare("effect.lib/fdnrev0:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/fdnrev0:copyright", "Julius O. Smith III");
		m->declare("effect.lib/fdnrev0:license", "STK-4.3");
		m->declare("effect.lib/fdnrev0_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/fdnrev0_demo:copyright", "Julius O. Smith III");
		m->declare("effect.lib/fdnrev0_demo:license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/prime_power_delays:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/prime_power_delays:copyright", "Julius O. Smith III");
		m->declare("effect.lib/prime_power_delays:license", "STK-4.3");
		m->declare("effect.lib/stereo_reverb_tester:author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/stereo_reverb_tester:copyright", "Julius O. Smith III");
		m->declare("effect.lib/stereo_reverb_tester:license", "STK-4.3");
		m->declare("filename", "reverb_designer.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "reverb_designer");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/license", "STK-4.3");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "1.11");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, static_cast<double>(fSampleRate)));
		fConst1 = 3.141592653589793 / fConst0;
		fConst2 = 6.907755278982138 / fConst0;
		fConst3 = 0.0029154518950437317 * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(4e+03);
		fHslider1 = static_cast<FAUSTFLOAT>(2e+03);
		fHslider2 = static_cast<FAUSTFLOAT>(1e+03);
		fHslider3 = static_cast<FAUSTFLOAT>(5e+02);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0);
		fButton0 = static_cast<FAUSTFLOAT>(0.0);
		fButton1 = static_cast<FAUSTFLOAT>(0.0);
		fButton2 = static_cast<FAUSTFLOAT>(0.0);
		fHslider4 = static_cast<FAUSTFLOAT>(46.0);
		fVslider0 = static_cast<FAUSTFLOAT>(2.7);
		fVslider1 = static_cast<FAUSTFLOAT>(3.8);
		fVslider2 = static_cast<FAUSTFLOAT>(5.0);
		fVslider3 = static_cast<FAUSTFLOAT>(6.5);
		fVslider4 = static_cast<FAUSTFLOAT>(8.4);
		fHslider5 = static_cast<FAUSTFLOAT>(63.0);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0);
		fButton3 = static_cast<FAUSTFLOAT>(0.0);
		fHslider6 = static_cast<FAUSTFLOAT>(-4e+01);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 4; l0 = faust_wrap_add(l0, 1)) {
			iRec17_perm[l0] = 0;
		}
		for (int l1 = 0; l1 < 4; l1 = faust_wrap_add(l1, 1)) {
			fRec16_perm[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 4; l2 = faust_wrap_add(l2, 1)) {
			fRec22_perm[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 4; l3 = faust_wrap_add(l3, 1)) {
			fRec21_perm[l3] = 0.0;
		}
		for (int l4 = 0; l4 < 4; l4 = faust_wrap_add(l4, 1)) {
			fRec20_perm[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 4; l5 = faust_wrap_add(l5, 1)) {
			fRec19_perm[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 4; l6 = faust_wrap_add(l6, 1)) {
			fRec18_perm[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 4; l7 = faust_wrap_add(l7, 1)) {
			fRec28_perm[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 4; l8 = faust_wrap_add(l8, 1)) {
			fRec27_perm[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 4; l9 = faust_wrap_add(l9, 1)) {
			fYec0_perm[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 4; l10 = faust_wrap_add(l10, 1)) {
			fRec26_perm[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 4; l11 = faust_wrap_add(l11, 1)) {
			fRec25_perm[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 4; l12 = faust_wrap_add(l12, 1)) {
			fRec24_perm[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 4; l13 = faust_wrap_add(l13, 1)) {
			fRec23_perm[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 4; l14 = faust_wrap_add(l14, 1)) {
			fRec33_perm[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 4; l15 = faust_wrap_add(l15, 1)) {
			fRec32_perm[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 4; l16 = faust_wrap_add(l16, 1)) {
			fYec1_perm[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 4; l17 = faust_wrap_add(l17, 1)) {
			fRec31_perm[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 4; l18 = faust_wrap_add(l18, 1)) {
			fRec30_perm[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 4; l19 = faust_wrap_add(l19, 1)) {
			fRec29_perm[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 4; l20 = faust_wrap_add(l20, 1)) {
			fRec37_perm[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 4; l21 = faust_wrap_add(l21, 1)) {
			fRec36_perm[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 4; l22 = faust_wrap_add(l22, 1)) {
			fYec2_perm[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 4; l23 = faust_wrap_add(l23, 1)) {
			fRec35_perm[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 4; l24 = faust_wrap_add(l24, 1)) {
			fRec34_perm[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 4; l25 = faust_wrap_add(l25, 1)) {
			fRec39_perm[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 4; l26 = faust_wrap_add(l26, 1)) {
			fRec38_perm[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 4; l27 = faust_wrap_add(l27, 1)) {
			fRec44_perm[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 4; l28 = faust_wrap_add(l28, 1)) {
			fRec43_perm[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 4; l29 = faust_wrap_add(l29, 1)) {
			fRec42_perm[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 4; l30 = faust_wrap_add(l30, 1)) {
			fRec41_perm[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 4; l31 = faust_wrap_add(l31, 1)) {
			fRec40_perm[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 4; l32 = faust_wrap_add(l32, 1)) {
			fRec50_perm[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 4; l33 = faust_wrap_add(l33, 1)) {
			fRec49_perm[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 4; l34 = faust_wrap_add(l34, 1)) {
			fYec3_perm[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 4; l35 = faust_wrap_add(l35, 1)) {
			fRec48_perm[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 4; l36 = faust_wrap_add(l36, 1)) {
			fRec47_perm[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 4; l37 = faust_wrap_add(l37, 1)) {
			fRec46_perm[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 4; l38 = faust_wrap_add(l38, 1)) {
			fRec45_perm[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 4; l39 = faust_wrap_add(l39, 1)) {
			fRec55_perm[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 4; l40 = faust_wrap_add(l40, 1)) {
			fRec54_perm[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 4; l41 = faust_wrap_add(l41, 1)) {
			fYec4_perm[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 4; l42 = faust_wrap_add(l42, 1)) {
			fRec53_perm[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 4; l43 = faust_wrap_add(l43, 1)) {
			fRec52_perm[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 4; l44 = faust_wrap_add(l44, 1)) {
			fRec51_perm[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 4; l45 = faust_wrap_add(l45, 1)) {
			fRec59_perm[l45] = 0.0;
		}
		for (int l46 = 0; l46 < 4; l46 = faust_wrap_add(l46, 1)) {
			fRec58_perm[l46] = 0.0;
		}
		for (int l47 = 0; l47 < 4; l47 = faust_wrap_add(l47, 1)) {
			fYec5_perm[l47] = 0.0;
		}
		for (int l48 = 0; l48 < 4; l48 = faust_wrap_add(l48, 1)) {
			fRec57_perm[l48] = 0.0;
		}
		for (int l49 = 0; l49 < 4; l49 = faust_wrap_add(l49, 1)) {
			fRec56_perm[l49] = 0.0;
		}
		for (int l50 = 0; l50 < 4; l50 = faust_wrap_add(l50, 1)) {
			fRec61_perm[l50] = 0.0;
		}
		for (int l51 = 0; l51 < 4; l51 = faust_wrap_add(l51, 1)) {
			fRec60_perm[l51] = 0.0;
		}
		for (int l52 = 0; l52 < 4; l52 = faust_wrap_add(l52, 1)) {
			fRec66_perm[l52] = 0.0;
		}
		for (int l53 = 0; l53 < 4; l53 = faust_wrap_add(l53, 1)) {
			fRec65_perm[l53] = 0.0;
		}
		for (int l54 = 0; l54 < 4; l54 = faust_wrap_add(l54, 1)) {
			fRec64_perm[l54] = 0.0;
		}
		for (int l55 = 0; l55 < 4; l55 = faust_wrap_add(l55, 1)) {
			fRec63_perm[l55] = 0.0;
		}
		for (int l56 = 0; l56 < 4; l56 = faust_wrap_add(l56, 1)) {
			fRec62_perm[l56] = 0.0;
		}
		for (int l57 = 0; l57 < 4; l57 = faust_wrap_add(l57, 1)) {
			fRec72_perm[l57] = 0.0;
		}
		for (int l58 = 0; l58 < 4; l58 = faust_wrap_add(l58, 1)) {
			fRec71_perm[l58] = 0.0;
		}
		for (int l59 = 0; l59 < 4; l59 = faust_wrap_add(l59, 1)) {
			fYec6_perm[l59] = 0.0;
		}
		for (int l60 = 0; l60 < 4; l60 = faust_wrap_add(l60, 1)) {
			fRec70_perm[l60] = 0.0;
		}
		for (int l61 = 0; l61 < 4; l61 = faust_wrap_add(l61, 1)) {
			fRec69_perm[l61] = 0.0;
		}
		for (int l62 = 0; l62 < 4; l62 = faust_wrap_add(l62, 1)) {
			fRec68_perm[l62] = 0.0;
		}
		for (int l63 = 0; l63 < 4; l63 = faust_wrap_add(l63, 1)) {
			fRec67_perm[l63] = 0.0;
		}
		for (int l64 = 0; l64 < 4; l64 = faust_wrap_add(l64, 1)) {
			fRec77_perm[l64] = 0.0;
		}
		for (int l65 = 0; l65 < 4; l65 = faust_wrap_add(l65, 1)) {
			fRec76_perm[l65] = 0.0;
		}
		for (int l66 = 0; l66 < 4; l66 = faust_wrap_add(l66, 1)) {
			fYec7_perm[l66] = 0.0;
		}
		for (int l67 = 0; l67 < 4; l67 = faust_wrap_add(l67, 1)) {
			fRec75_perm[l67] = 0.0;
		}
		for (int l68 = 0; l68 < 4; l68 = faust_wrap_add(l68, 1)) {
			fRec74_perm[l68] = 0.0;
		}
		for (int l69 = 0; l69 < 4; l69 = faust_wrap_add(l69, 1)) {
			fRec73_perm[l69] = 0.0;
		}
		for (int l70 = 0; l70 < 4; l70 = faust_wrap_add(l70, 1)) {
			fRec81_perm[l70] = 0.0;
		}
		for (int l71 = 0; l71 < 4; l71 = faust_wrap_add(l71, 1)) {
			fRec80_perm[l71] = 0.0;
		}
		for (int l72 = 0; l72 < 4; l72 = faust_wrap_add(l72, 1)) {
			fYec8_perm[l72] = 0.0;
		}
		for (int l73 = 0; l73 < 4; l73 = faust_wrap_add(l73, 1)) {
			fRec79_perm[l73] = 0.0;
		}
		for (int l74 = 0; l74 < 4; l74 = faust_wrap_add(l74, 1)) {
			fRec78_perm[l74] = 0.0;
		}
		for (int l75 = 0; l75 < 4; l75 = faust_wrap_add(l75, 1)) {
			fRec83_perm[l75] = 0.0;
		}
		for (int l76 = 0; l76 < 4; l76 = faust_wrap_add(l76, 1)) {
			fRec82_perm[l76] = 0.0;
		}
		for (int l77 = 0; l77 < 4; l77 = faust_wrap_add(l77, 1)) {
			fRec88_perm[l77] = 0.0;
		}
		for (int l78 = 0; l78 < 4; l78 = faust_wrap_add(l78, 1)) {
			fRec87_perm[l78] = 0.0;
		}
		for (int l79 = 0; l79 < 4; l79 = faust_wrap_add(l79, 1)) {
			fRec86_perm[l79] = 0.0;
		}
		for (int l80 = 0; l80 < 4; l80 = faust_wrap_add(l80, 1)) {
			fRec85_perm[l80] = 0.0;
		}
		for (int l81 = 0; l81 < 4; l81 = faust_wrap_add(l81, 1)) {
			fRec84_perm[l81] = 0.0;
		}
		for (int l82 = 0; l82 < 4; l82 = faust_wrap_add(l82, 1)) {
			fRec94_perm[l82] = 0.0;
		}
		for (int l83 = 0; l83 < 4; l83 = faust_wrap_add(l83, 1)) {
			fRec93_perm[l83] = 0.0;
		}
		for (int l84 = 0; l84 < 4; l84 = faust_wrap_add(l84, 1)) {
			fYec9_perm[l84] = 0.0;
		}
		for (int l85 = 0; l85 < 4; l85 = faust_wrap_add(l85, 1)) {
			fRec92_perm[l85] = 0.0;
		}
		for (int l86 = 0; l86 < 4; l86 = faust_wrap_add(l86, 1)) {
			fRec91_perm[l86] = 0.0;
		}
		for (int l87 = 0; l87 < 4; l87 = faust_wrap_add(l87, 1)) {
			fRec90_perm[l87] = 0.0;
		}
		for (int l88 = 0; l88 < 4; l88 = faust_wrap_add(l88, 1)) {
			fRec89_perm[l88] = 0.0;
		}
		for (int l89 = 0; l89 < 4; l89 = faust_wrap_add(l89, 1)) {
			fRec99_perm[l89] = 0.0;
		}
		for (int l90 = 0; l90 < 4; l90 = faust_wrap_add(l90, 1)) {
			fRec98_perm[l90] = 0.0;
		}
		for (int l91 = 0; l91 < 4; l91 = faust_wrap_add(l91, 1)) {
			fYec10_perm[l91] = 0.0;
		}
		for (int l92 = 0; l92 < 4; l92 = faust_wrap_add(l92, 1)) {
			fRec97_perm[l92] = 0.0;
		}
		for (int l93 = 0; l93 < 4; l93 = faust_wrap_add(l93, 1)) {
			fRec96_perm[l93] = 0.0;
		}
		for (int l94 = 0; l94 < 4; l94 = faust_wrap_add(l94, 1)) {
			fRec95_perm[l94] = 0.0;
		}
		for (int l95 = 0; l95 < 4; l95 = faust_wrap_add(l95, 1)) {
			fRec103_perm[l95] = 0.0;
		}
		for (int l96 = 0; l96 < 4; l96 = faust_wrap_add(l96, 1)) {
			fRec102_perm[l96] = 0.0;
		}
		for (int l97 = 0; l97 < 4; l97 = faust_wrap_add(l97, 1)) {
			fYec11_perm[l97] = 0.0;
		}
		for (int l98 = 0; l98 < 4; l98 = faust_wrap_add(l98, 1)) {
			fRec101_perm[l98] = 0.0;
		}
		for (int l99 = 0; l99 < 4; l99 = faust_wrap_add(l99, 1)) {
			fRec100_perm[l99] = 0.0;
		}
		for (int l100 = 0; l100 < 4; l100 = faust_wrap_add(l100, 1)) {
			fRec105_perm[l100] = 0.0;
		}
		for (int l101 = 0; l101 < 4; l101 = faust_wrap_add(l101, 1)) {
			fRec104_perm[l101] = 0.0;
		}
		for (int l102 = 0; l102 < 4; l102 = faust_wrap_add(l102, 1)) {
			fRec110_perm[l102] = 0.0;
		}
		for (int l103 = 0; l103 < 4; l103 = faust_wrap_add(l103, 1)) {
			fRec109_perm[l103] = 0.0;
		}
		for (int l104 = 0; l104 < 4; l104 = faust_wrap_add(l104, 1)) {
			fRec108_perm[l104] = 0.0;
		}
		for (int l105 = 0; l105 < 4; l105 = faust_wrap_add(l105, 1)) {
			fRec107_perm[l105] = 0.0;
		}
		for (int l106 = 0; l106 < 4; l106 = faust_wrap_add(l106, 1)) {
			fRec106_perm[l106] = 0.0;
		}
		for (int l107 = 0; l107 < 4; l107 = faust_wrap_add(l107, 1)) {
			fRec116_perm[l107] = 0.0;
		}
		for (int l108 = 0; l108 < 4; l108 = faust_wrap_add(l108, 1)) {
			fRec115_perm[l108] = 0.0;
		}
		for (int l109 = 0; l109 < 4; l109 = faust_wrap_add(l109, 1)) {
			fYec12_perm[l109] = 0.0;
		}
		for (int l110 = 0; l110 < 4; l110 = faust_wrap_add(l110, 1)) {
			fRec114_perm[l110] = 0.0;
		}
		for (int l111 = 0; l111 < 4; l111 = faust_wrap_add(l111, 1)) {
			fRec113_perm[l111] = 0.0;
		}
		for (int l112 = 0; l112 < 4; l112 = faust_wrap_add(l112, 1)) {
			fRec112_perm[l112] = 0.0;
		}
		for (int l113 = 0; l113 < 4; l113 = faust_wrap_add(l113, 1)) {
			fRec111_perm[l113] = 0.0;
		}
		for (int l114 = 0; l114 < 4; l114 = faust_wrap_add(l114, 1)) {
			fRec121_perm[l114] = 0.0;
		}
		for (int l115 = 0; l115 < 4; l115 = faust_wrap_add(l115, 1)) {
			fRec120_perm[l115] = 0.0;
		}
		for (int l116 = 0; l116 < 4; l116 = faust_wrap_add(l116, 1)) {
			fYec13_perm[l116] = 0.0;
		}
		for (int l117 = 0; l117 < 4; l117 = faust_wrap_add(l117, 1)) {
			fRec119_perm[l117] = 0.0;
		}
		for (int l118 = 0; l118 < 4; l118 = faust_wrap_add(l118, 1)) {
			fRec118_perm[l118] = 0.0;
		}
		for (int l119 = 0; l119 < 4; l119 = faust_wrap_add(l119, 1)) {
			fRec117_perm[l119] = 0.0;
		}
		for (int l120 = 0; l120 < 4; l120 = faust_wrap_add(l120, 1)) {
			fRec125_perm[l120] = 0.0;
		}
		for (int l121 = 0; l121 < 4; l121 = faust_wrap_add(l121, 1)) {
			fRec124_perm[l121] = 0.0;
		}
		for (int l122 = 0; l122 < 4; l122 = faust_wrap_add(l122, 1)) {
			fYec14_perm[l122] = 0.0;
		}
		for (int l123 = 0; l123 < 4; l123 = faust_wrap_add(l123, 1)) {
			fRec123_perm[l123] = 0.0;
		}
		for (int l124 = 0; l124 < 4; l124 = faust_wrap_add(l124, 1)) {
			fRec122_perm[l124] = 0.0;
		}
		for (int l125 = 0; l125 < 4; l125 = faust_wrap_add(l125, 1)) {
			fRec127_perm[l125] = 0.0;
		}
		for (int l126 = 0; l126 < 4; l126 = faust_wrap_add(l126, 1)) {
			fRec126_perm[l126] = 0.0;
		}
		for (int l127 = 0; l127 < 4; l127 = faust_wrap_add(l127, 1)) {
			fRec132_perm[l127] = 0.0;
		}
		for (int l128 = 0; l128 < 4; l128 = faust_wrap_add(l128, 1)) {
			fRec131_perm[l128] = 0.0;
		}
		for (int l129 = 0; l129 < 4; l129 = faust_wrap_add(l129, 1)) {
			fRec130_perm[l129] = 0.0;
		}
		for (int l130 = 0; l130 < 4; l130 = faust_wrap_add(l130, 1)) {
			fRec129_perm[l130] = 0.0;
		}
		for (int l131 = 0; l131 < 4; l131 = faust_wrap_add(l131, 1)) {
			fRec128_perm[l131] = 0.0;
		}
		for (int l132 = 0; l132 < 4; l132 = faust_wrap_add(l132, 1)) {
			fRec138_perm[l132] = 0.0;
		}
		for (int l133 = 0; l133 < 4; l133 = faust_wrap_add(l133, 1)) {
			fRec137_perm[l133] = 0.0;
		}
		for (int l134 = 0; l134 < 4; l134 = faust_wrap_add(l134, 1)) {
			fYec15_perm[l134] = 0.0;
		}
		for (int l135 = 0; l135 < 4; l135 = faust_wrap_add(l135, 1)) {
			fRec136_perm[l135] = 0.0;
		}
		for (int l136 = 0; l136 < 4; l136 = faust_wrap_add(l136, 1)) {
			fRec135_perm[l136] = 0.0;
		}
		for (int l137 = 0; l137 < 4; l137 = faust_wrap_add(l137, 1)) {
			fRec134_perm[l137] = 0.0;
		}
		for (int l138 = 0; l138 < 4; l138 = faust_wrap_add(l138, 1)) {
			fRec133_perm[l138] = 0.0;
		}
		for (int l139 = 0; l139 < 4; l139 = faust_wrap_add(l139, 1)) {
			fRec143_perm[l139] = 0.0;
		}
		for (int l140 = 0; l140 < 4; l140 = faust_wrap_add(l140, 1)) {
			fRec142_perm[l140] = 0.0;
		}
		for (int l141 = 0; l141 < 4; l141 = faust_wrap_add(l141, 1)) {
			fYec16_perm[l141] = 0.0;
		}
		for (int l142 = 0; l142 < 4; l142 = faust_wrap_add(l142, 1)) {
			fRec141_perm[l142] = 0.0;
		}
		for (int l143 = 0; l143 < 4; l143 = faust_wrap_add(l143, 1)) {
			fRec140_perm[l143] = 0.0;
		}
		for (int l144 = 0; l144 < 4; l144 = faust_wrap_add(l144, 1)) {
			fRec139_perm[l144] = 0.0;
		}
		for (int l145 = 0; l145 < 4; l145 = faust_wrap_add(l145, 1)) {
			fRec147_perm[l145] = 0.0;
		}
		for (int l146 = 0; l146 < 4; l146 = faust_wrap_add(l146, 1)) {
			fRec146_perm[l146] = 0.0;
		}
		for (int l147 = 0; l147 < 4; l147 = faust_wrap_add(l147, 1)) {
			fYec17_perm[l147] = 0.0;
		}
		for (int l148 = 0; l148 < 4; l148 = faust_wrap_add(l148, 1)) {
			fRec145_perm[l148] = 0.0;
		}
		for (int l149 = 0; l149 < 4; l149 = faust_wrap_add(l149, 1)) {
			fRec144_perm[l149] = 0.0;
		}
		for (int l150 = 0; l150 < 4; l150 = faust_wrap_add(l150, 1)) {
			fRec149_perm[l150] = 0.0;
		}
		for (int l151 = 0; l151 < 4; l151 = faust_wrap_add(l151, 1)) {
			fRec148_perm[l151] = 0.0;
		}
		for (int l152 = 0; l152 < 4; l152 = faust_wrap_add(l152, 1)) {
			fRec154_perm[l152] = 0.0;
		}
		for (int l153 = 0; l153 < 4; l153 = faust_wrap_add(l153, 1)) {
			fRec153_perm[l153] = 0.0;
		}
		for (int l154 = 0; l154 < 4; l154 = faust_wrap_add(l154, 1)) {
			fRec152_perm[l154] = 0.0;
		}
		for (int l155 = 0; l155 < 4; l155 = faust_wrap_add(l155, 1)) {
			fRec151_perm[l155] = 0.0;
		}
		for (int l156 = 0; l156 < 4; l156 = faust_wrap_add(l156, 1)) {
			fRec150_perm[l156] = 0.0;
		}
		for (int l157 = 0; l157 < 4; l157 = faust_wrap_add(l157, 1)) {
			fRec160_perm[l157] = 0.0;
		}
		for (int l158 = 0; l158 < 4; l158 = faust_wrap_add(l158, 1)) {
			fRec159_perm[l158] = 0.0;
		}
		for (int l159 = 0; l159 < 4; l159 = faust_wrap_add(l159, 1)) {
			fYec18_perm[l159] = 0.0;
		}
		for (int l160 = 0; l160 < 4; l160 = faust_wrap_add(l160, 1)) {
			fRec158_perm[l160] = 0.0;
		}
		for (int l161 = 0; l161 < 4; l161 = faust_wrap_add(l161, 1)) {
			fRec157_perm[l161] = 0.0;
		}
		for (int l162 = 0; l162 < 4; l162 = faust_wrap_add(l162, 1)) {
			fRec156_perm[l162] = 0.0;
		}
		for (int l163 = 0; l163 < 4; l163 = faust_wrap_add(l163, 1)) {
			fRec155_perm[l163] = 0.0;
		}
		for (int l164 = 0; l164 < 4; l164 = faust_wrap_add(l164, 1)) {
			fRec165_perm[l164] = 0.0;
		}
		for (int l165 = 0; l165 < 4; l165 = faust_wrap_add(l165, 1)) {
			fRec164_perm[l165] = 0.0;
		}
		for (int l166 = 0; l166 < 4; l166 = faust_wrap_add(l166, 1)) {
			fYec19_perm[l166] = 0.0;
		}
		for (int l167 = 0; l167 < 4; l167 = faust_wrap_add(l167, 1)) {
			fRec163_perm[l167] = 0.0;
		}
		for (int l168 = 0; l168 < 4; l168 = faust_wrap_add(l168, 1)) {
			fRec162_perm[l168] = 0.0;
		}
		for (int l169 = 0; l169 < 4; l169 = faust_wrap_add(l169, 1)) {
			fRec161_perm[l169] = 0.0;
		}
		for (int l170 = 0; l170 < 4; l170 = faust_wrap_add(l170, 1)) {
			fRec169_perm[l170] = 0.0;
		}
		for (int l171 = 0; l171 < 4; l171 = faust_wrap_add(l171, 1)) {
			fRec168_perm[l171] = 0.0;
		}
		for (int l172 = 0; l172 < 4; l172 = faust_wrap_add(l172, 1)) {
			fYec20_perm[l172] = 0.0;
		}
		for (int l173 = 0; l173 < 4; l173 = faust_wrap_add(l173, 1)) {
			fRec167_perm[l173] = 0.0;
		}
		for (int l174 = 0; l174 < 4; l174 = faust_wrap_add(l174, 1)) {
			fRec166_perm[l174] = 0.0;
		}
		for (int l175 = 0; l175 < 4; l175 = faust_wrap_add(l175, 1)) {
			fRec171_perm[l175] = 0.0;
		}
		for (int l176 = 0; l176 < 4; l176 = faust_wrap_add(l176, 1)) {
			fRec170_perm[l176] = 0.0;
		}
		for (int l177 = 0; l177 < 4; l177 = faust_wrap_add(l177, 1)) {
			fRec176_perm[l177] = 0.0;
		}
		for (int l178 = 0; l178 < 4; l178 = faust_wrap_add(l178, 1)) {
			fRec175_perm[l178] = 0.0;
		}
		for (int l179 = 0; l179 < 4; l179 = faust_wrap_add(l179, 1)) {
			fRec174_perm[l179] = 0.0;
		}
		for (int l180 = 0; l180 < 4; l180 = faust_wrap_add(l180, 1)) {
			fRec173_perm[l180] = 0.0;
		}
		for (int l181 = 0; l181 < 4; l181 = faust_wrap_add(l181, 1)) {
			fRec172_perm[l181] = 0.0;
		}
		for (int l182 = 0; l182 < 4; l182 = faust_wrap_add(l182, 1)) {
			fRec182_perm[l182] = 0.0;
		}
		for (int l183 = 0; l183 < 4; l183 = faust_wrap_add(l183, 1)) {
			fRec181_perm[l183] = 0.0;
		}
		for (int l184 = 0; l184 < 4; l184 = faust_wrap_add(l184, 1)) {
			fYec21_perm[l184] = 0.0;
		}
		for (int l185 = 0; l185 < 4; l185 = faust_wrap_add(l185, 1)) {
			fRec180_perm[l185] = 0.0;
		}
		for (int l186 = 0; l186 < 4; l186 = faust_wrap_add(l186, 1)) {
			fRec179_perm[l186] = 0.0;
		}
		for (int l187 = 0; l187 < 4; l187 = faust_wrap_add(l187, 1)) {
			fRec178_perm[l187] = 0.0;
		}
		for (int l188 = 0; l188 < 4; l188 = faust_wrap_add(l188, 1)) {
			fRec177_perm[l188] = 0.0;
		}
		for (int l189 = 0; l189 < 4; l189 = faust_wrap_add(l189, 1)) {
			fRec187_perm[l189] = 0.0;
		}
		for (int l190 = 0; l190 < 4; l190 = faust_wrap_add(l190, 1)) {
			fRec186_perm[l190] = 0.0;
		}
		for (int l191 = 0; l191 < 4; l191 = faust_wrap_add(l191, 1)) {
			fYec22_perm[l191] = 0.0;
		}
		for (int l192 = 0; l192 < 4; l192 = faust_wrap_add(l192, 1)) {
			fRec185_perm[l192] = 0.0;
		}
		for (int l193 = 0; l193 < 4; l193 = faust_wrap_add(l193, 1)) {
			fRec184_perm[l193] = 0.0;
		}
		for (int l194 = 0; l194 < 4; l194 = faust_wrap_add(l194, 1)) {
			fRec183_perm[l194] = 0.0;
		}
		for (int l195 = 0; l195 < 4; l195 = faust_wrap_add(l195, 1)) {
			fRec191_perm[l195] = 0.0;
		}
		for (int l196 = 0; l196 < 4; l196 = faust_wrap_add(l196, 1)) {
			fRec190_perm[l196] = 0.0;
		}
		for (int l197 = 0; l197 < 4; l197 = faust_wrap_add(l197, 1)) {
			fYec23_perm[l197] = 0.0;
		}
		for (int l198 = 0; l198 < 4; l198 = faust_wrap_add(l198, 1)) {
			fRec189_perm[l198] = 0.0;
		}
		for (int l199 = 0; l199 < 4; l199 = faust_wrap_add(l199, 1)) {
			fRec188_perm[l199] = 0.0;
		}
		for (int l200 = 0; l200 < 4; l200 = faust_wrap_add(l200, 1)) {
			fRec193_perm[l200] = 0.0;
		}
		for (int l201 = 0; l201 < 4; l201 = faust_wrap_add(l201, 1)) {
			fRec192_perm[l201] = 0.0;
		}
		for (int l202 = 0; l202 < 4; l202 = faust_wrap_add(l202, 1)) {
			fRec198_perm[l202] = 0.0;
		}
		for (int l203 = 0; l203 < 4; l203 = faust_wrap_add(l203, 1)) {
			fRec197_perm[l203] = 0.0;
		}
		for (int l204 = 0; l204 < 4; l204 = faust_wrap_add(l204, 1)) {
			fRec196_perm[l204] = 0.0;
		}
		for (int l205 = 0; l205 < 4; l205 = faust_wrap_add(l205, 1)) {
			fRec195_perm[l205] = 0.0;
		}
		for (int l206 = 0; l206 < 4; l206 = faust_wrap_add(l206, 1)) {
			fRec194_perm[l206] = 0.0;
		}
		for (int l207 = 0; l207 < 4; l207 = faust_wrap_add(l207, 1)) {
			fRec204_perm[l207] = 0.0;
		}
		for (int l208 = 0; l208 < 4; l208 = faust_wrap_add(l208, 1)) {
			fRec203_perm[l208] = 0.0;
		}
		for (int l209 = 0; l209 < 4; l209 = faust_wrap_add(l209, 1)) {
			fYec24_perm[l209] = 0.0;
		}
		for (int l210 = 0; l210 < 4; l210 = faust_wrap_add(l210, 1)) {
			fRec202_perm[l210] = 0.0;
		}
		for (int l211 = 0; l211 < 4; l211 = faust_wrap_add(l211, 1)) {
			fRec201_perm[l211] = 0.0;
		}
		for (int l212 = 0; l212 < 4; l212 = faust_wrap_add(l212, 1)) {
			fRec200_perm[l212] = 0.0;
		}
		for (int l213 = 0; l213 < 4; l213 = faust_wrap_add(l213, 1)) {
			fRec199_perm[l213] = 0.0;
		}
		for (int l214 = 0; l214 < 4; l214 = faust_wrap_add(l214, 1)) {
			fRec209_perm[l214] = 0.0;
		}
		for (int l215 = 0; l215 < 4; l215 = faust_wrap_add(l215, 1)) {
			fRec208_perm[l215] = 0.0;
		}
		for (int l216 = 0; l216 < 4; l216 = faust_wrap_add(l216, 1)) {
			fYec25_perm[l216] = 0.0;
		}
		for (int l217 = 0; l217 < 4; l217 = faust_wrap_add(l217, 1)) {
			fRec207_perm[l217] = 0.0;
		}
		for (int l218 = 0; l218 < 4; l218 = faust_wrap_add(l218, 1)) {
			fRec206_perm[l218] = 0.0;
		}
		for (int l219 = 0; l219 < 4; l219 = faust_wrap_add(l219, 1)) {
			fRec205_perm[l219] = 0.0;
		}
		for (int l220 = 0; l220 < 4; l220 = faust_wrap_add(l220, 1)) {
			fRec213_perm[l220] = 0.0;
		}
		for (int l221 = 0; l221 < 4; l221 = faust_wrap_add(l221, 1)) {
			fRec212_perm[l221] = 0.0;
		}
		for (int l222 = 0; l222 < 4; l222 = faust_wrap_add(l222, 1)) {
			fYec26_perm[l222] = 0.0;
		}
		for (int l223 = 0; l223 < 4; l223 = faust_wrap_add(l223, 1)) {
			fRec211_perm[l223] = 0.0;
		}
		for (int l224 = 0; l224 < 4; l224 = faust_wrap_add(l224, 1)) {
			fRec210_perm[l224] = 0.0;
		}
		for (int l225 = 0; l225 < 4; l225 = faust_wrap_add(l225, 1)) {
			fRec215_perm[l225] = 0.0;
		}
		for (int l226 = 0; l226 < 4; l226 = faust_wrap_add(l226, 1)) {
			fRec214_perm[l226] = 0.0;
		}
		for (int l227 = 0; l227 < 4; l227 = faust_wrap_add(l227, 1)) {
			fRec220_perm[l227] = 0.0;
		}
		for (int l228 = 0; l228 < 4; l228 = faust_wrap_add(l228, 1)) {
			fRec219_perm[l228] = 0.0;
		}
		for (int l229 = 0; l229 < 4; l229 = faust_wrap_add(l229, 1)) {
			fRec218_perm[l229] = 0.0;
		}
		for (int l230 = 0; l230 < 4; l230 = faust_wrap_add(l230, 1)) {
			fRec217_perm[l230] = 0.0;
		}
		for (int l231 = 0; l231 < 4; l231 = faust_wrap_add(l231, 1)) {
			fRec216_perm[l231] = 0.0;
		}
		for (int l232 = 0; l232 < 4; l232 = faust_wrap_add(l232, 1)) {
			fRec226_perm[l232] = 0.0;
		}
		for (int l233 = 0; l233 < 4; l233 = faust_wrap_add(l233, 1)) {
			fRec225_perm[l233] = 0.0;
		}
		for (int l234 = 0; l234 < 4; l234 = faust_wrap_add(l234, 1)) {
			fYec27_perm[l234] = 0.0;
		}
		for (int l235 = 0; l235 < 4; l235 = faust_wrap_add(l235, 1)) {
			fRec224_perm[l235] = 0.0;
		}
		for (int l236 = 0; l236 < 4; l236 = faust_wrap_add(l236, 1)) {
			fRec223_perm[l236] = 0.0;
		}
		for (int l237 = 0; l237 < 4; l237 = faust_wrap_add(l237, 1)) {
			fRec222_perm[l237] = 0.0;
		}
		for (int l238 = 0; l238 < 4; l238 = faust_wrap_add(l238, 1)) {
			fRec221_perm[l238] = 0.0;
		}
		for (int l239 = 0; l239 < 4; l239 = faust_wrap_add(l239, 1)) {
			fRec231_perm[l239] = 0.0;
		}
		for (int l240 = 0; l240 < 4; l240 = faust_wrap_add(l240, 1)) {
			fRec230_perm[l240] = 0.0;
		}
		for (int l241 = 0; l241 < 4; l241 = faust_wrap_add(l241, 1)) {
			fYec28_perm[l241] = 0.0;
		}
		for (int l242 = 0; l242 < 4; l242 = faust_wrap_add(l242, 1)) {
			fRec229_perm[l242] = 0.0;
		}
		for (int l243 = 0; l243 < 4; l243 = faust_wrap_add(l243, 1)) {
			fRec228_perm[l243] = 0.0;
		}
		for (int l244 = 0; l244 < 4; l244 = faust_wrap_add(l244, 1)) {
			fRec227_perm[l244] = 0.0;
		}
		for (int l245 = 0; l245 < 4; l245 = faust_wrap_add(l245, 1)) {
			fRec235_perm[l245] = 0.0;
		}
		for (int l246 = 0; l246 < 4; l246 = faust_wrap_add(l246, 1)) {
			fRec234_perm[l246] = 0.0;
		}
		for (int l247 = 0; l247 < 4; l247 = faust_wrap_add(l247, 1)) {
			fYec29_perm[l247] = 0.0;
		}
		for (int l248 = 0; l248 < 4; l248 = faust_wrap_add(l248, 1)) {
			fRec233_perm[l248] = 0.0;
		}
		for (int l249 = 0; l249 < 4; l249 = faust_wrap_add(l249, 1)) {
			fRec232_perm[l249] = 0.0;
		}
		for (int l250 = 0; l250 < 4; l250 = faust_wrap_add(l250, 1)) {
			fRec237_perm[l250] = 0.0;
		}
		for (int l251 = 0; l251 < 4; l251 = faust_wrap_add(l251, 1)) {
			fRec236_perm[l251] = 0.0;
		}
		for (int l252 = 0; l252 < 4; l252 = faust_wrap_add(l252, 1)) {
			fRec242_perm[l252] = 0.0;
		}
		for (int l253 = 0; l253 < 4; l253 = faust_wrap_add(l253, 1)) {
			fRec241_perm[l253] = 0.0;
		}
		for (int l254 = 0; l254 < 4; l254 = faust_wrap_add(l254, 1)) {
			fRec240_perm[l254] = 0.0;
		}
		for (int l255 = 0; l255 < 4; l255 = faust_wrap_add(l255, 1)) {
			fRec239_perm[l255] = 0.0;
		}
		for (int l256 = 0; l256 < 4; l256 = faust_wrap_add(l256, 1)) {
			fRec238_perm[l256] = 0.0;
		}
		for (int l257 = 0; l257 < 4; l257 = faust_wrap_add(l257, 1)) {
			fRec248_perm[l257] = 0.0;
		}
		for (int l258 = 0; l258 < 4; l258 = faust_wrap_add(l258, 1)) {
			fRec247_perm[l258] = 0.0;
		}
		for (int l259 = 0; l259 < 4; l259 = faust_wrap_add(l259, 1)) {
			fYec30_perm[l259] = 0.0;
		}
		for (int l260 = 0; l260 < 4; l260 = faust_wrap_add(l260, 1)) {
			fRec246_perm[l260] = 0.0;
		}
		for (int l261 = 0; l261 < 4; l261 = faust_wrap_add(l261, 1)) {
			fRec245_perm[l261] = 0.0;
		}
		for (int l262 = 0; l262 < 4; l262 = faust_wrap_add(l262, 1)) {
			fRec244_perm[l262] = 0.0;
		}
		for (int l263 = 0; l263 < 4; l263 = faust_wrap_add(l263, 1)) {
			fRec243_perm[l263] = 0.0;
		}
		for (int l264 = 0; l264 < 4; l264 = faust_wrap_add(l264, 1)) {
			fRec253_perm[l264] = 0.0;
		}
		for (int l265 = 0; l265 < 4; l265 = faust_wrap_add(l265, 1)) {
			fRec252_perm[l265] = 0.0;
		}
		for (int l266 = 0; l266 < 4; l266 = faust_wrap_add(l266, 1)) {
			fYec31_perm[l266] = 0.0;
		}
		for (int l267 = 0; l267 < 4; l267 = faust_wrap_add(l267, 1)) {
			fRec251_perm[l267] = 0.0;
		}
		for (int l268 = 0; l268 < 4; l268 = faust_wrap_add(l268, 1)) {
			fRec250_perm[l268] = 0.0;
		}
		for (int l269 = 0; l269 < 4; l269 = faust_wrap_add(l269, 1)) {
			fRec249_perm[l269] = 0.0;
		}
		for (int l270 = 0; l270 < 4; l270 = faust_wrap_add(l270, 1)) {
			fRec257_perm[l270] = 0.0;
		}
		for (int l271 = 0; l271 < 4; l271 = faust_wrap_add(l271, 1)) {
			fRec256_perm[l271] = 0.0;
		}
		for (int l272 = 0; l272 < 4; l272 = faust_wrap_add(l272, 1)) {
			fYec32_perm[l272] = 0.0;
		}
		for (int l273 = 0; l273 < 4; l273 = faust_wrap_add(l273, 1)) {
			fRec255_perm[l273] = 0.0;
		}
		for (int l274 = 0; l274 < 4; l274 = faust_wrap_add(l274, 1)) {
			fRec254_perm[l274] = 0.0;
		}
		for (int l275 = 0; l275 < 4; l275 = faust_wrap_add(l275, 1)) {
			fRec259_perm[l275] = 0.0;
		}
		for (int l276 = 0; l276 < 4; l276 = faust_wrap_add(l276, 1)) {
			fRec258_perm[l276] = 0.0;
		}
		for (int l277 = 0; l277 < 4; l277 = faust_wrap_add(l277, 1)) {
			fRec264_perm[l277] = 0.0;
		}
		for (int l278 = 0; l278 < 4; l278 = faust_wrap_add(l278, 1)) {
			fRec263_perm[l278] = 0.0;
		}
		for (int l279 = 0; l279 < 4; l279 = faust_wrap_add(l279, 1)) {
			fRec262_perm[l279] = 0.0;
		}
		for (int l280 = 0; l280 < 4; l280 = faust_wrap_add(l280, 1)) {
			fRec261_perm[l280] = 0.0;
		}
		for (int l281 = 0; l281 < 4; l281 = faust_wrap_add(l281, 1)) {
			fRec260_perm[l281] = 0.0;
		}
		for (int l282 = 0; l282 < 4; l282 = faust_wrap_add(l282, 1)) {
			fRec270_perm[l282] = 0.0;
		}
		for (int l283 = 0; l283 < 4; l283 = faust_wrap_add(l283, 1)) {
			fRec269_perm[l283] = 0.0;
		}
		for (int l284 = 0; l284 < 4; l284 = faust_wrap_add(l284, 1)) {
			fYec33_perm[l284] = 0.0;
		}
		for (int l285 = 0; l285 < 4; l285 = faust_wrap_add(l285, 1)) {
			fRec268_perm[l285] = 0.0;
		}
		for (int l286 = 0; l286 < 4; l286 = faust_wrap_add(l286, 1)) {
			fRec267_perm[l286] = 0.0;
		}
		for (int l287 = 0; l287 < 4; l287 = faust_wrap_add(l287, 1)) {
			fRec266_perm[l287] = 0.0;
		}
		for (int l288 = 0; l288 < 4; l288 = faust_wrap_add(l288, 1)) {
			fRec265_perm[l288] = 0.0;
		}
		for (int l289 = 0; l289 < 4; l289 = faust_wrap_add(l289, 1)) {
			fRec275_perm[l289] = 0.0;
		}
		for (int l290 = 0; l290 < 4; l290 = faust_wrap_add(l290, 1)) {
			fRec274_perm[l290] = 0.0;
		}
		for (int l291 = 0; l291 < 4; l291 = faust_wrap_add(l291, 1)) {
			fYec34_perm[l291] = 0.0;
		}
		for (int l292 = 0; l292 < 4; l292 = faust_wrap_add(l292, 1)) {
			fRec273_perm[l292] = 0.0;
		}
		for (int l293 = 0; l293 < 4; l293 = faust_wrap_add(l293, 1)) {
			fRec272_perm[l293] = 0.0;
		}
		for (int l294 = 0; l294 < 4; l294 = faust_wrap_add(l294, 1)) {
			fRec271_perm[l294] = 0.0;
		}
		for (int l295 = 0; l295 < 4; l295 = faust_wrap_add(l295, 1)) {
			fRec279_perm[l295] = 0.0;
		}
		for (int l296 = 0; l296 < 4; l296 = faust_wrap_add(l296, 1)) {
			fRec278_perm[l296] = 0.0;
		}
		for (int l297 = 0; l297 < 4; l297 = faust_wrap_add(l297, 1)) {
			fYec35_perm[l297] = 0.0;
		}
		for (int l298 = 0; l298 < 4; l298 = faust_wrap_add(l298, 1)) {
			fRec277_perm[l298] = 0.0;
		}
		for (int l299 = 0; l299 < 4; l299 = faust_wrap_add(l299, 1)) {
			fRec276_perm[l299] = 0.0;
		}
		for (int l300 = 0; l300 < 4; l300 = faust_wrap_add(l300, 1)) {
			fRec281_perm[l300] = 0.0;
		}
		for (int l301 = 0; l301 < 4; l301 = faust_wrap_add(l301, 1)) {
			fRec280_perm[l301] = 0.0;
		}
		for (int l302 = 0; l302 < 4; l302 = faust_wrap_add(l302, 1)) {
			fRec286_perm[l302] = 0.0;
		}
		for (int l303 = 0; l303 < 4; l303 = faust_wrap_add(l303, 1)) {
			fRec285_perm[l303] = 0.0;
		}
		for (int l304 = 0; l304 < 4; l304 = faust_wrap_add(l304, 1)) {
			fRec284_perm[l304] = 0.0;
		}
		for (int l305 = 0; l305 < 4; l305 = faust_wrap_add(l305, 1)) {
			fRec283_perm[l305] = 0.0;
		}
		for (int l306 = 0; l306 < 4; l306 = faust_wrap_add(l306, 1)) {
			fRec282_perm[l306] = 0.0;
		}
		for (int l307 = 0; l307 < 4; l307 = faust_wrap_add(l307, 1)) {
			fRec292_perm[l307] = 0.0;
		}
		for (int l308 = 0; l308 < 4; l308 = faust_wrap_add(l308, 1)) {
			fRec291_perm[l308] = 0.0;
		}
		for (int l309 = 0; l309 < 4; l309 = faust_wrap_add(l309, 1)) {
			fYec36_perm[l309] = 0.0;
		}
		for (int l310 = 0; l310 < 4; l310 = faust_wrap_add(l310, 1)) {
			fRec290_perm[l310] = 0.0;
		}
		for (int l311 = 0; l311 < 4; l311 = faust_wrap_add(l311, 1)) {
			fRec289_perm[l311] = 0.0;
		}
		for (int l312 = 0; l312 < 4; l312 = faust_wrap_add(l312, 1)) {
			fRec288_perm[l312] = 0.0;
		}
		for (int l313 = 0; l313 < 4; l313 = faust_wrap_add(l313, 1)) {
			fRec287_perm[l313] = 0.0;
		}
		for (int l314 = 0; l314 < 4; l314 = faust_wrap_add(l314, 1)) {
			fRec297_perm[l314] = 0.0;
		}
		for (int l315 = 0; l315 < 4; l315 = faust_wrap_add(l315, 1)) {
			fRec296_perm[l315] = 0.0;
		}
		for (int l316 = 0; l316 < 4; l316 = faust_wrap_add(l316, 1)) {
			fYec37_perm[l316] = 0.0;
		}
		for (int l317 = 0; l317 < 4; l317 = faust_wrap_add(l317, 1)) {
			fRec295_perm[l317] = 0.0;
		}
		for (int l318 = 0; l318 < 4; l318 = faust_wrap_add(l318, 1)) {
			fRec294_perm[l318] = 0.0;
		}
		for (int l319 = 0; l319 < 4; l319 = faust_wrap_add(l319, 1)) {
			fRec293_perm[l319] = 0.0;
		}
		for (int l320 = 0; l320 < 4; l320 = faust_wrap_add(l320, 1)) {
			fRec301_perm[l320] = 0.0;
		}
		for (int l321 = 0; l321 < 4; l321 = faust_wrap_add(l321, 1)) {
			fRec300_perm[l321] = 0.0;
		}
		for (int l322 = 0; l322 < 4; l322 = faust_wrap_add(l322, 1)) {
			fYec38_perm[l322] = 0.0;
		}
		for (int l323 = 0; l323 < 4; l323 = faust_wrap_add(l323, 1)) {
			fRec299_perm[l323] = 0.0;
		}
		for (int l324 = 0; l324 < 4; l324 = faust_wrap_add(l324, 1)) {
			fRec298_perm[l324] = 0.0;
		}
		for (int l325 = 0; l325 < 4; l325 = faust_wrap_add(l325, 1)) {
			fRec303_perm[l325] = 0.0;
		}
		for (int l326 = 0; l326 < 4; l326 = faust_wrap_add(l326, 1)) {
			fRec302_perm[l326] = 0.0;
		}
		for (int l327 = 0; l327 < 4; l327 = faust_wrap_add(l327, 1)) {
			fRec308_perm[l327] = 0.0;
		}
		for (int l328 = 0; l328 < 4; l328 = faust_wrap_add(l328, 1)) {
			fRec307_perm[l328] = 0.0;
		}
		for (int l329 = 0; l329 < 4; l329 = faust_wrap_add(l329, 1)) {
			fRec306_perm[l329] = 0.0;
		}
		for (int l330 = 0; l330 < 4; l330 = faust_wrap_add(l330, 1)) {
			fRec305_perm[l330] = 0.0;
		}
		for (int l331 = 0; l331 < 4; l331 = faust_wrap_add(l331, 1)) {
			fRec304_perm[l331] = 0.0;
		}
		for (int l332 = 0; l332 < 4; l332 = faust_wrap_add(l332, 1)) {
			fRec314_perm[l332] = 0.0;
		}
		for (int l333 = 0; l333 < 4; l333 = faust_wrap_add(l333, 1)) {
			fRec313_perm[l333] = 0.0;
		}
		for (int l334 = 0; l334 < 4; l334 = faust_wrap_add(l334, 1)) {
			fYec39_perm[l334] = 0.0;
		}
		for (int l335 = 0; l335 < 4; l335 = faust_wrap_add(l335, 1)) {
			fRec312_perm[l335] = 0.0;
		}
		for (int l336 = 0; l336 < 4; l336 = faust_wrap_add(l336, 1)) {
			fRec311_perm[l336] = 0.0;
		}
		for (int l337 = 0; l337 < 4; l337 = faust_wrap_add(l337, 1)) {
			fRec310_perm[l337] = 0.0;
		}
		for (int l338 = 0; l338 < 4; l338 = faust_wrap_add(l338, 1)) {
			fRec309_perm[l338] = 0.0;
		}
		for (int l339 = 0; l339 < 4; l339 = faust_wrap_add(l339, 1)) {
			fRec319_perm[l339] = 0.0;
		}
		for (int l340 = 0; l340 < 4; l340 = faust_wrap_add(l340, 1)) {
			fRec318_perm[l340] = 0.0;
		}
		for (int l341 = 0; l341 < 4; l341 = faust_wrap_add(l341, 1)) {
			fYec40_perm[l341] = 0.0;
		}
		for (int l342 = 0; l342 < 4; l342 = faust_wrap_add(l342, 1)) {
			fRec317_perm[l342] = 0.0;
		}
		for (int l343 = 0; l343 < 4; l343 = faust_wrap_add(l343, 1)) {
			fRec316_perm[l343] = 0.0;
		}
		for (int l344 = 0; l344 < 4; l344 = faust_wrap_add(l344, 1)) {
			fRec315_perm[l344] = 0.0;
		}
		for (int l345 = 0; l345 < 4; l345 = faust_wrap_add(l345, 1)) {
			fRec323_perm[l345] = 0.0;
		}
		for (int l346 = 0; l346 < 4; l346 = faust_wrap_add(l346, 1)) {
			fRec322_perm[l346] = 0.0;
		}
		for (int l347 = 0; l347 < 4; l347 = faust_wrap_add(l347, 1)) {
			fYec41_perm[l347] = 0.0;
		}
		for (int l348 = 0; l348 < 4; l348 = faust_wrap_add(l348, 1)) {
			fRec321_perm[l348] = 0.0;
		}
		for (int l349 = 0; l349 < 4; l349 = faust_wrap_add(l349, 1)) {
			fRec320_perm[l349] = 0.0;
		}
		for (int l350 = 0; l350 < 4; l350 = faust_wrap_add(l350, 1)) {
			fRec325_perm[l350] = 0.0;
		}
		for (int l351 = 0; l351 < 4; l351 = faust_wrap_add(l351, 1)) {
			fRec324_perm[l351] = 0.0;
		}
		for (int l352 = 0; l352 < 4; l352 = faust_wrap_add(l352, 1)) {
			fRec330_perm[l352] = 0.0;
		}
		for (int l353 = 0; l353 < 4; l353 = faust_wrap_add(l353, 1)) {
			fRec329_perm[l353] = 0.0;
		}
		for (int l354 = 0; l354 < 4; l354 = faust_wrap_add(l354, 1)) {
			fRec328_perm[l354] = 0.0;
		}
		for (int l355 = 0; l355 < 4; l355 = faust_wrap_add(l355, 1)) {
			fRec327_perm[l355] = 0.0;
		}
		for (int l356 = 0; l356 < 4; l356 = faust_wrap_add(l356, 1)) {
			fRec326_perm[l356] = 0.0;
		}
		for (int l357 = 0; l357 < 4; l357 = faust_wrap_add(l357, 1)) {
			fRec336_perm[l357] = 0.0;
		}
		for (int l358 = 0; l358 < 4; l358 = faust_wrap_add(l358, 1)) {
			fRec335_perm[l358] = 0.0;
		}
		for (int l359 = 0; l359 < 4; l359 = faust_wrap_add(l359, 1)) {
			fYec42_perm[l359] = 0.0;
		}
		for (int l360 = 0; l360 < 4; l360 = faust_wrap_add(l360, 1)) {
			fRec334_perm[l360] = 0.0;
		}
		for (int l361 = 0; l361 < 4; l361 = faust_wrap_add(l361, 1)) {
			fRec333_perm[l361] = 0.0;
		}
		for (int l362 = 0; l362 < 4; l362 = faust_wrap_add(l362, 1)) {
			fRec332_perm[l362] = 0.0;
		}
		for (int l363 = 0; l363 < 4; l363 = faust_wrap_add(l363, 1)) {
			fRec331_perm[l363] = 0.0;
		}
		for (int l364 = 0; l364 < 4; l364 = faust_wrap_add(l364, 1)) {
			fRec341_perm[l364] = 0.0;
		}
		for (int l365 = 0; l365 < 4; l365 = faust_wrap_add(l365, 1)) {
			fRec340_perm[l365] = 0.0;
		}
		for (int l366 = 0; l366 < 4; l366 = faust_wrap_add(l366, 1)) {
			fYec43_perm[l366] = 0.0;
		}
		for (int l367 = 0; l367 < 4; l367 = faust_wrap_add(l367, 1)) {
			fRec339_perm[l367] = 0.0;
		}
		for (int l368 = 0; l368 < 4; l368 = faust_wrap_add(l368, 1)) {
			fRec338_perm[l368] = 0.0;
		}
		for (int l369 = 0; l369 < 4; l369 = faust_wrap_add(l369, 1)) {
			fRec337_perm[l369] = 0.0;
		}
		for (int l370 = 0; l370 < 4; l370 = faust_wrap_add(l370, 1)) {
			fRec345_perm[l370] = 0.0;
		}
		for (int l371 = 0; l371 < 4; l371 = faust_wrap_add(l371, 1)) {
			fRec344_perm[l371] = 0.0;
		}
		for (int l372 = 0; l372 < 4; l372 = faust_wrap_add(l372, 1)) {
			fYec44_perm[l372] = 0.0;
		}
		for (int l373 = 0; l373 < 4; l373 = faust_wrap_add(l373, 1)) {
			fRec343_perm[l373] = 0.0;
		}
		for (int l374 = 0; l374 < 4; l374 = faust_wrap_add(l374, 1)) {
			fRec342_perm[l374] = 0.0;
		}
		for (int l375 = 0; l375 < 4; l375 = faust_wrap_add(l375, 1)) {
			fRec347_perm[l375] = 0.0;
		}
		for (int l376 = 0; l376 < 4; l376 = faust_wrap_add(l376, 1)) {
			fRec346_perm[l376] = 0.0;
		}
		for (int l377 = 0; l377 < 4; l377 = faust_wrap_add(l377, 1)) {
			fRec352_perm[l377] = 0.0;
		}
		for (int l378 = 0; l378 < 4; l378 = faust_wrap_add(l378, 1)) {
			fRec351_perm[l378] = 0.0;
		}
		for (int l379 = 0; l379 < 4; l379 = faust_wrap_add(l379, 1)) {
			fRec350_perm[l379] = 0.0;
		}
		for (int l380 = 0; l380 < 4; l380 = faust_wrap_add(l380, 1)) {
			fRec349_perm[l380] = 0.0;
		}
		for (int l381 = 0; l381 < 4; l381 = faust_wrap_add(l381, 1)) {
			fRec348_perm[l381] = 0.0;
		}
		for (int l382 = 0; l382 < 4; l382 = faust_wrap_add(l382, 1)) {
			fRec358_perm[l382] = 0.0;
		}
		for (int l383 = 0; l383 < 4; l383 = faust_wrap_add(l383, 1)) {
			fRec357_perm[l383] = 0.0;
		}
		for (int l384 = 0; l384 < 4; l384 = faust_wrap_add(l384, 1)) {
			fYec45_perm[l384] = 0.0;
		}
		for (int l385 = 0; l385 < 4; l385 = faust_wrap_add(l385, 1)) {
			fRec356_perm[l385] = 0.0;
		}
		for (int l386 = 0; l386 < 4; l386 = faust_wrap_add(l386, 1)) {
			fRec355_perm[l386] = 0.0;
		}
		for (int l387 = 0; l387 < 4; l387 = faust_wrap_add(l387, 1)) {
			fRec354_perm[l387] = 0.0;
		}
		for (int l388 = 0; l388 < 4; l388 = faust_wrap_add(l388, 1)) {
			fRec353_perm[l388] = 0.0;
		}
		for (int l389 = 0; l389 < 4; l389 = faust_wrap_add(l389, 1)) {
			fRec363_perm[l389] = 0.0;
		}
		for (int l390 = 0; l390 < 4; l390 = faust_wrap_add(l390, 1)) {
			fRec362_perm[l390] = 0.0;
		}
		for (int l391 = 0; l391 < 4; l391 = faust_wrap_add(l391, 1)) {
			fYec46_perm[l391] = 0.0;
		}
		for (int l392 = 0; l392 < 4; l392 = faust_wrap_add(l392, 1)) {
			fRec361_perm[l392] = 0.0;
		}
		for (int l393 = 0; l393 < 4; l393 = faust_wrap_add(l393, 1)) {
			fRec360_perm[l393] = 0.0;
		}
		for (int l394 = 0; l394 < 4; l394 = faust_wrap_add(l394, 1)) {
			fRec359_perm[l394] = 0.0;
		}
		for (int l395 = 0; l395 < 4; l395 = faust_wrap_add(l395, 1)) {
			fRec367_perm[l395] = 0.0;
		}
		for (int l396 = 0; l396 < 4; l396 = faust_wrap_add(l396, 1)) {
			fRec366_perm[l396] = 0.0;
		}
		for (int l397 = 0; l397 < 4; l397 = faust_wrap_add(l397, 1)) {
			fYec47_perm[l397] = 0.0;
		}
		for (int l398 = 0; l398 < 4; l398 = faust_wrap_add(l398, 1)) {
			fRec365_perm[l398] = 0.0;
		}
		for (int l399 = 0; l399 < 4; l399 = faust_wrap_add(l399, 1)) {
			fRec364_perm[l399] = 0.0;
		}
		for (int l400 = 0; l400 < 4; l400 = faust_wrap_add(l400, 1)) {
			fRec369_perm[l400] = 0.0;
		}
		for (int l401 = 0; l401 < 4; l401 = faust_wrap_add(l401, 1)) {
			fRec368_perm[l401] = 0.0;
		}
		for (int l402 = 0; l402 < 4; l402 = faust_wrap_add(l402, 1)) {
			fVec0_perm[l402] = 0.0;
		}
		for (int l403 = 0; l403 < 4; l403 = faust_wrap_add(l403, 1)) {
			fVec1_perm[l403] = 0.0;
		}
		for (int l404 = 0; l404 < 16384; l404 = faust_wrap_add(l404, 1)) {
			fYec48[l404] = 0.0;
		}
		fYec48_idx = 0;
		fYec48_idx_save = 0;
		for (int l405 = 0; l405 < 4; l405 = faust_wrap_add(l405, 1)) {
			fRec0_perm[l405] = 0.0;
		}
		for (int l406 = 0; l406 < 4; l406 = faust_wrap_add(l406, 1)) {
			fVec2_perm[l406] = 0.0;
		}
		for (int l407 = 0; l407 < 16384; l407 = faust_wrap_add(l407, 1)) {
			fYec49[l407] = 0.0;
		}
		fYec49_idx = 0;
		fYec49_idx_save = 0;
		for (int l408 = 0; l408 < 4; l408 = faust_wrap_add(l408, 1)) {
			fRec1_perm[l408] = 0.0;
		}
		for (int l409 = 0; l409 < 16384; l409 = faust_wrap_add(l409, 1)) {
			fYec50[l409] = 0.0;
		}
		fYec50_idx = 0;
		fYec50_idx_save = 0;
		for (int l410 = 0; l410 < 4; l410 = faust_wrap_add(l410, 1)) {
			fRec2_perm[l410] = 0.0;
		}
		for (int l411 = 0; l411 < 16384; l411 = faust_wrap_add(l411, 1)) {
			fYec51[l411] = 0.0;
		}
		fYec51_idx = 0;
		fYec51_idx_save = 0;
		for (int l412 = 0; l412 < 4; l412 = faust_wrap_add(l412, 1)) {
			fRec3_perm[l412] = 0.0;
		}
		for (int l413 = 0; l413 < 16384; l413 = faust_wrap_add(l413, 1)) {
			fYec52[l413] = 0.0;
		}
		fYec52_idx = 0;
		fYec52_idx_save = 0;
		for (int l414 = 0; l414 < 4; l414 = faust_wrap_add(l414, 1)) {
			fRec4_perm[l414] = 0.0;
		}
		for (int l415 = 0; l415 < 16384; l415 = faust_wrap_add(l415, 1)) {
			fYec53[l415] = 0.0;
		}
		fYec53_idx = 0;
		fYec53_idx_save = 0;
		for (int l416 = 0; l416 < 4; l416 = faust_wrap_add(l416, 1)) {
			fRec5_perm[l416] = 0.0;
		}
		for (int l417 = 0; l417 < 16384; l417 = faust_wrap_add(l417, 1)) {
			fYec54[l417] = 0.0;
		}
		fYec54_idx = 0;
		fYec54_idx_save = 0;
		for (int l418 = 0; l418 < 4; l418 = faust_wrap_add(l418, 1)) {
			fRec6_perm[l418] = 0.0;
		}
		for (int l419 = 0; l419 < 16384; l419 = faust_wrap_add(l419, 1)) {
			fYec55[l419] = 0.0;
		}
		fYec55_idx = 0;
		fYec55_idx_save = 0;
		for (int l420 = 0; l420 < 4; l420 = faust_wrap_add(l420, 1)) {
			fRec7_perm[l420] = 0.0;
		}
		for (int l421 = 0; l421 < 16384; l421 = faust_wrap_add(l421, 1)) {
			fYec56[l421] = 0.0;
		}
		fYec56_idx = 0;
		fYec56_idx_save = 0;
		for (int l422 = 0; l422 < 4; l422 = faust_wrap_add(l422, 1)) {
			fRec8_perm[l422] = 0.0;
		}
		for (int l423 = 0; l423 < 16384; l423 = faust_wrap_add(l423, 1)) {
			fYec57[l423] = 0.0;
		}
		fYec57_idx = 0;
		fYec57_idx_save = 0;
		for (int l424 = 0; l424 < 4; l424 = faust_wrap_add(l424, 1)) {
			fRec9_perm[l424] = 0.0;
		}
		for (int l425 = 0; l425 < 16384; l425 = faust_wrap_add(l425, 1)) {
			fYec58[l425] = 0.0;
		}
		fYec58_idx = 0;
		fYec58_idx_save = 0;
		for (int l426 = 0; l426 < 4; l426 = faust_wrap_add(l426, 1)) {
			fRec10_perm[l426] = 0.0;
		}
		for (int l427 = 0; l427 < 16384; l427 = faust_wrap_add(l427, 1)) {
			fYec59[l427] = 0.0;
		}
		fYec59_idx = 0;
		fYec59_idx_save = 0;
		for (int l428 = 0; l428 < 4; l428 = faust_wrap_add(l428, 1)) {
			fRec11_perm[l428] = 0.0;
		}
		for (int l429 = 0; l429 < 16384; l429 = faust_wrap_add(l429, 1)) {
			fYec60[l429] = 0.0;
		}
		fYec60_idx = 0;
		fYec60_idx_save = 0;
		for (int l430 = 0; l430 < 4; l430 = faust_wrap_add(l430, 1)) {
			fRec12_perm[l430] = 0.0;
		}
		for (int l431 = 0; l431 < 16384; l431 = faust_wrap_add(l431, 1)) {
			fYec61[l431] = 0.0;
		}
		fYec61_idx = 0;
		fYec61_idx_save = 0;
		for (int l432 = 0; l432 < 4; l432 = faust_wrap_add(l432, 1)) {
			fRec13_perm[l432] = 0.0;
		}
		for (int l433 = 0; l433 < 16384; l433 = faust_wrap_add(l433, 1)) {
			fYec62[l433] = 0.0;
		}
		fYec62_idx = 0;
		fYec62_idx_save = 0;
		for (int l434 = 0; l434 < 4; l434 = faust_wrap_add(l434, 1)) {
			fRec14_perm[l434] = 0.0;
		}
		for (int l435 = 0; l435 < 16384; l435 = faust_wrap_add(l435, 1)) {
			fYec63[l435] = 0.0;
		}
		fYec63_idx = 0;
		fYec63_idx_save = 0;
		for (int l436 = 0; l436 < 4; l436 = faust_wrap_add(l436, 1)) {
			fRec15_perm[l436] = 0.0;
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
		ui_interface->openVerticalBox("reverb_designer");
		ui_interface->declare(0, "tooltip", "See Faust's effect.lib for documentation and references");
		ui_interface->openVerticalBox("FEEDBACK DELAY NETWORK (FDN) REVERBERATOR, ORDER 16");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Band Crossover Frequencies");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 0 upper edge in Hz", &fHslider3, FAUSTFLOAT(5e+02), FAUSTFLOAT(1e+02), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band");
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 1 upper edge in Hz", &fHslider2, FAUSTFLOAT(1e+03), FAUSTFLOAT(1e+02), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 2 upper edge in Hz", &fHslider1, FAUSTFLOAT(2e+03), FAUSTFLOAT(1e+02), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Band 3 upper edge in Hz", &fHslider0, FAUSTFLOAT(4e+03), FAUSTFLOAT(1e+02), FAUSTFLOAT(1e+04), FAUSTFLOAT(1.0));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Band Decay Times (T60)");
		ui_interface->declare(&fVslider4, "0", "");
		ui_interface->declare(&fVslider4, "scale", "log");
		ui_interface->declare(&fVslider4, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.");
		ui_interface->declare(&fVslider4, "unit", "s");
		ui_interface->addVerticalSlider("0", &fVslider4, FAUSTFLOAT(8.4), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider3, "1", "");
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->declare(&fVslider3, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.");
		ui_interface->declare(&fVslider3, "unit", "s");
		ui_interface->addVerticalSlider("1", &fVslider3, FAUSTFLOAT(6.5), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider2, "2", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.");
		ui_interface->declare(&fVslider2, "unit", "s");
		ui_interface->addVerticalSlider("2", &fVslider2, FAUSTFLOAT(5.0), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider1, "3", "");
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->declare(&fVslider1, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.");
		ui_interface->declare(&fVslider1, "unit", "s");
		ui_interface->addVerticalSlider("3", &fVslider1, FAUSTFLOAT(3.8), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->declare(&fVslider0, "4", "");
		ui_interface->declare(&fVslider0, "scale", "log");
		ui_interface->declare(&fVslider0, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.");
		ui_interface->declare(&fVslider0, "unit", "s");
		ui_interface->addVerticalSlider("4", &fVslider0, FAUSTFLOAT(2.7), FAUSTFLOAT(0.1), FAUSTFLOAT(1e+02), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Room Dimensions");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "scale", "log");
		ui_interface->declare(&fHslider4, "tooltip", "This length (in meters) determines the shortest delay-line used in the FDN reverberator.               Think of it as the shortest wall-to-wall separation in the room.");
		ui_interface->declare(&fHslider4, "unit", "m");
		ui_interface->addHorizontalSlider("min acoustic ray length", &fHslider4, FAUSTFLOAT(46.0), FAUSTFLOAT(0.1), FAUSTFLOAT(63.0), FAUSTFLOAT(0.1));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "tooltip", "This length (in meters) determines the longest delay-line used in the FDN reverberator.               Think of it as the largest wall-to-wall separation in the room.");
		ui_interface->declare(&fHslider5, "unit", "m");
		ui_interface->addHorizontalSlider("max acoustic ray length", &fHslider5, FAUSTFLOAT(63.0), FAUSTFLOAT(0.1), FAUSTFLOAT(63.0), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Input Controls");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Input Config");
		ui_interface->declare(&fCheckbox1, "1", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "When this is checked, the stereo external audio inputs are disabled (good for hearing the impulse response or pink-noise response alone)");
		ui_interface->addCheckButton("Mute Ext Inputs", &fCheckbox1);
		ui_interface->declare(&fCheckbox0, "2", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)");
		ui_interface->addCheckButton("Pink Noise", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Impulse Selection");
		ui_interface->declare(&fButton0, "1", "");
		ui_interface->declare(&fButton0, "tooltip", "Send impulse into LEFT channel");
		ui_interface->addButton("Left", &fButton0);
		ui_interface->declare(&fButton1, "2", "");
		ui_interface->declare(&fButton1, "tooltip", "Send impulse into LEFT and RIGHT channels");
		ui_interface->addButton("Center", &fButton1);
		ui_interface->declare(&fButton3, "3", "");
		ui_interface->declare(&fButton3, "tooltip", "Send impulse into RIGHT channel");
		ui_interface->addButton("Right", &fButton3);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Reverb State");
		ui_interface->declare(&fButton2, "1", "");
		ui_interface->declare(&fButton2, "tooltip", "Hold down 'Quench' to clear the reverberator");
		ui_interface->addButton("Quench", &fButton2);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "tooltip", "Output scale factor");
		ui_interface->declare(&fHslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("Output Level (dB)", &fHslider6, FAUSTFLOAT(-4e+01), FAUSTFLOAT(-7e+01), FAUSTFLOAT(2e+01), FAUSTFLOAT(0.1));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		int iRec17_tmp[8];
		int* iRec17 = &iRec17_tmp[4];
		double fRec16_tmp[8];
		double* fRec16 = &fRec16_tmp[4];
		double fSlow0 = std::tan(fConst1 * static_cast<double>(fHslider0));
		double fSlow1 = 1.0 / fSlow0;
		double fSlow2 = 1.0 / (fSlow1 + 1.0);
		double fSlow3 = 1.0 - fSlow1;
		double fRec22_tmp[8];
		double* fRec22 = &fRec22_tmp[4];
		double fSlow4 = (fSlow1 + 1.0000000000000004) / fSlow0 + 1.0;
		double fSlow5 = 1.0 / fSlow4;
		double fSlow6 = (fSlow1 + -1.0000000000000004) / fSlow0 + 1.0;
		double fSlow7 = mydsp_faustpower2_f(fSlow0);
		double fSlow8 = 2.0 * (1.0 - 1.0 / fSlow7);
		double fRec21_tmp[8];
		double* fRec21 = &fRec21_tmp[4];
		double fSlow9 = 1.0 / (fSlow7 * fSlow4);
		double fSlow10 = std::tan(fConst1 * static_cast<double>(fHslider1));
		double fSlow11 = 1.0 / fSlow10;
		double fSlow12 = fSlow11 + 1.0;
		double fSlow13 = 1.0 / (fSlow12 / fSlow10 + 1.0);
		double fSlow14 = 1.0 - fSlow11;
		double fSlow15 = 1.0 - fSlow14 / fSlow10;
		double fSlow16 = mydsp_faustpower2_f(fSlow10);
		double fSlow17 = 2.0 * (1.0 - 1.0 / fSlow16);
		double fZec0[4];
		double fRec20_tmp[8];
		double* fRec20 = &fRec20_tmp[4];
		double fSlow18 = std::tan(fConst1 * static_cast<double>(fHslider2));
		double fSlow19 = 1.0 / fSlow18;
		double fSlow20 = fSlow19 + 1.0;
		double fSlow21 = 1.0 / (fSlow20 / fSlow18 + 1.0);
		double fSlow22 = 1.0 - fSlow19;
		double fSlow23 = 1.0 - fSlow22 / fSlow18;
		double fSlow24 = mydsp_faustpower2_f(fSlow18);
		double fSlow25 = 2.0 * (1.0 - 1.0 / fSlow24);
		double fZec1[4];
		double fRec19_tmp[8];
		double* fRec19 = &fRec19_tmp[4];
		double fSlow26 = std::tan(fConst1 * static_cast<double>(fHslider3));
		double fSlow27 = 1.0 / fSlow26;
		double fSlow28 = fSlow27 + 1.0;
		double fSlow29 = 1.0 / (fSlow28 / fSlow26 + 1.0);
		double fSlow30 = 1.0 - fSlow27;
		double fSlow31 = 1.0 - fSlow30 / fSlow26;
		double fSlow32 = mydsp_faustpower2_f(fSlow26);
		double fSlow33 = 2.0 * (1.0 - 1.0 / fSlow32);
		double fZec2[4];
		double fRec18_tmp[8];
		double* fRec18 = &fRec18_tmp[4];
		double fRec28_tmp[8];
		double* fRec28 = &fRec28_tmp[4];
		double fRec27_tmp[8];
		double* fRec27 = &fRec27_tmp[4];
		double fSlow34 = 1.0 / fSlow12;
		double fYec0_tmp[8];
		double* fYec0 = &fYec0_tmp[4];
		double fRec26_tmp[8];
		double* fRec26 = &fRec26_tmp[4];
		double fSlow35 = (fSlow11 + 1.0000000000000004) / fSlow10 + 1.0;
		double fSlow36 = 1.0 / fSlow35;
		double fSlow37 = (fSlow11 + -1.0000000000000004) / fSlow10 + 1.0;
		double fRec25_tmp[8];
		double* fRec25 = &fRec25_tmp[4];
		double fSlow38 = 1.0 / (fSlow16 * fSlow35);
		double fZec3[4];
		double fRec24_tmp[8];
		double* fRec24 = &fRec24_tmp[4];
		double fZec4[4];
		double fRec23_tmp[8];
		double* fRec23 = &fRec23_tmp[4];
		double fRec33_tmp[8];
		double* fRec33 = &fRec33_tmp[4];
		double fRec32_tmp[8];
		double* fRec32 = &fRec32_tmp[4];
		double fSlow39 = 1.0 / fSlow20;
		double fYec1_tmp[8];
		double* fYec1 = &fYec1_tmp[4];
		double fRec31_tmp[8];
		double* fRec31 = &fRec31_tmp[4];
		double fSlow40 = (fSlow19 + 1.0000000000000004) / fSlow18 + 1.0;
		double fSlow41 = 1.0 / fSlow40;
		double fSlow42 = (fSlow19 + -1.0000000000000004) / fSlow18 + 1.0;
		double fRec30_tmp[8];
		double* fRec30 = &fRec30_tmp[4];
		double fSlow43 = 1.0 / (fSlow24 * fSlow40);
		double fZec5[4];
		double fRec29_tmp[8];
		double* fRec29 = &fRec29_tmp[4];
		double fRec37_tmp[8];
		double* fRec37 = &fRec37_tmp[4];
		double fRec36_tmp[8];
		double* fRec36 = &fRec36_tmp[4];
		double fSlow44 = 1.0 / fSlow28;
		double fYec2_tmp[8];
		double* fYec2 = &fYec2_tmp[4];
		double fRec35_tmp[8];
		double* fRec35 = &fRec35_tmp[4];
		double fSlow45 = 1.0 / ((fSlow27 + 1.0000000000000004) / fSlow26 + 1.0);
		double fSlow46 = (fSlow27 + -1.0000000000000004) / fSlow26 + 1.0;
		double fRec34_tmp[8];
		double* fRec34 = &fRec34_tmp[4];
		double fRec39_tmp[8];
		double* fRec39 = &fRec39_tmp[4];
		double fRec38_tmp[8];
		double* fRec38 = &fRec38_tmp[4];
		double fRec44_tmp[8];
		double* fRec44 = &fRec44_tmp[4];
		double fRec43_tmp[8];
		double* fRec43 = &fRec43_tmp[4];
		double fZec6[4];
		double fRec42_tmp[8];
		double* fRec42 = &fRec42_tmp[4];
		double fZec7[4];
		double fRec41_tmp[8];
		double* fRec41 = &fRec41_tmp[4];
		double fZec8[4];
		double fRec40_tmp[8];
		double* fRec40 = &fRec40_tmp[4];
		double fRec50_tmp[8];
		double* fRec50 = &fRec50_tmp[4];
		double fRec49_tmp[8];
		double* fRec49 = &fRec49_tmp[4];
		double fYec3_tmp[8];
		double* fYec3 = &fYec3_tmp[4];
		double fRec48_tmp[8];
		double* fRec48 = &fRec48_tmp[4];
		double fRec47_tmp[8];
		double* fRec47 = &fRec47_tmp[4];
		double fZec9[4];
		double fRec46_tmp[8];
		double* fRec46 = &fRec46_tmp[4];
		double fZec10[4];
		double fRec45_tmp[8];
		double* fRec45 = &fRec45_tmp[4];
		double fRec55_tmp[8];
		double* fRec55 = &fRec55_tmp[4];
		double fRec54_tmp[8];
		double* fRec54 = &fRec54_tmp[4];
		double fYec4_tmp[8];
		double* fYec4 = &fYec4_tmp[4];
		double fRec53_tmp[8];
		double* fRec53 = &fRec53_tmp[4];
		double fRec52_tmp[8];
		double* fRec52 = &fRec52_tmp[4];
		double fZec11[4];
		double fRec51_tmp[8];
		double* fRec51 = &fRec51_tmp[4];
		double fRec59_tmp[8];
		double* fRec59 = &fRec59_tmp[4];
		double fRec58_tmp[8];
		double* fRec58 = &fRec58_tmp[4];
		double fYec5_tmp[8];
		double* fYec5 = &fYec5_tmp[4];
		double fRec57_tmp[8];
		double* fRec57 = &fRec57_tmp[4];
		double fRec56_tmp[8];
		double* fRec56 = &fRec56_tmp[4];
		double fRec61_tmp[8];
		double* fRec61 = &fRec61_tmp[4];
		double fRec60_tmp[8];
		double* fRec60 = &fRec60_tmp[4];
		double fRec66_tmp[8];
		double* fRec66 = &fRec66_tmp[4];
		double fRec65_tmp[8];
		double* fRec65 = &fRec65_tmp[4];
		double fZec12[4];
		double fRec64_tmp[8];
		double* fRec64 = &fRec64_tmp[4];
		double fZec13[4];
		double fRec63_tmp[8];
		double* fRec63 = &fRec63_tmp[4];
		double fZec14[4];
		double fRec62_tmp[8];
		double* fRec62 = &fRec62_tmp[4];
		double fRec72_tmp[8];
		double* fRec72 = &fRec72_tmp[4];
		double fRec71_tmp[8];
		double* fRec71 = &fRec71_tmp[4];
		double fYec6_tmp[8];
		double* fYec6 = &fYec6_tmp[4];
		double fRec70_tmp[8];
		double* fRec70 = &fRec70_tmp[4];
		double fRec69_tmp[8];
		double* fRec69 = &fRec69_tmp[4];
		double fZec15[4];
		double fRec68_tmp[8];
		double* fRec68 = &fRec68_tmp[4];
		double fZec16[4];
		double fRec67_tmp[8];
		double* fRec67 = &fRec67_tmp[4];
		double fRec77_tmp[8];
		double* fRec77 = &fRec77_tmp[4];
		double fRec76_tmp[8];
		double* fRec76 = &fRec76_tmp[4];
		double fYec7_tmp[8];
		double* fYec7 = &fYec7_tmp[4];
		double fRec75_tmp[8];
		double* fRec75 = &fRec75_tmp[4];
		double fRec74_tmp[8];
		double* fRec74 = &fRec74_tmp[4];
		double fZec17[4];
		double fRec73_tmp[8];
		double* fRec73 = &fRec73_tmp[4];
		double fRec81_tmp[8];
		double* fRec81 = &fRec81_tmp[4];
		double fRec80_tmp[8];
		double* fRec80 = &fRec80_tmp[4];
		double fYec8_tmp[8];
		double* fYec8 = &fYec8_tmp[4];
		double fRec79_tmp[8];
		double* fRec79 = &fRec79_tmp[4];
		double fRec78_tmp[8];
		double* fRec78 = &fRec78_tmp[4];
		double fRec83_tmp[8];
		double* fRec83 = &fRec83_tmp[4];
		double fRec82_tmp[8];
		double* fRec82 = &fRec82_tmp[4];
		double fRec88_tmp[8];
		double* fRec88 = &fRec88_tmp[4];
		double fRec87_tmp[8];
		double* fRec87 = &fRec87_tmp[4];
		double fZec18[4];
		double fRec86_tmp[8];
		double* fRec86 = &fRec86_tmp[4];
		double fZec19[4];
		double fRec85_tmp[8];
		double* fRec85 = &fRec85_tmp[4];
		double fZec20[4];
		double fRec84_tmp[8];
		double* fRec84 = &fRec84_tmp[4];
		double fRec94_tmp[8];
		double* fRec94 = &fRec94_tmp[4];
		double fRec93_tmp[8];
		double* fRec93 = &fRec93_tmp[4];
		double fYec9_tmp[8];
		double* fYec9 = &fYec9_tmp[4];
		double fRec92_tmp[8];
		double* fRec92 = &fRec92_tmp[4];
		double fRec91_tmp[8];
		double* fRec91 = &fRec91_tmp[4];
		double fZec21[4];
		double fRec90_tmp[8];
		double* fRec90 = &fRec90_tmp[4];
		double fZec22[4];
		double fRec89_tmp[8];
		double* fRec89 = &fRec89_tmp[4];
		double fRec99_tmp[8];
		double* fRec99 = &fRec99_tmp[4];
		double fRec98_tmp[8];
		double* fRec98 = &fRec98_tmp[4];
		double fYec10_tmp[8];
		double* fYec10 = &fYec10_tmp[4];
		double fRec97_tmp[8];
		double* fRec97 = &fRec97_tmp[4];
		double fRec96_tmp[8];
		double* fRec96 = &fRec96_tmp[4];
		double fZec23[4];
		double fRec95_tmp[8];
		double* fRec95 = &fRec95_tmp[4];
		double fRec103_tmp[8];
		double* fRec103 = &fRec103_tmp[4];
		double fRec102_tmp[8];
		double* fRec102 = &fRec102_tmp[4];
		double fYec11_tmp[8];
		double* fYec11 = &fYec11_tmp[4];
		double fRec101_tmp[8];
		double* fRec101 = &fRec101_tmp[4];
		double fRec100_tmp[8];
		double* fRec100 = &fRec100_tmp[4];
		double fRec105_tmp[8];
		double* fRec105 = &fRec105_tmp[4];
		double fRec104_tmp[8];
		double* fRec104 = &fRec104_tmp[4];
		double fRec110_tmp[8];
		double* fRec110 = &fRec110_tmp[4];
		double fRec109_tmp[8];
		double* fRec109 = &fRec109_tmp[4];
		double fZec24[4];
		double fRec108_tmp[8];
		double* fRec108 = &fRec108_tmp[4];
		double fZec25[4];
		double fRec107_tmp[8];
		double* fRec107 = &fRec107_tmp[4];
		double fZec26[4];
		double fRec106_tmp[8];
		double* fRec106 = &fRec106_tmp[4];
		double fRec116_tmp[8];
		double* fRec116 = &fRec116_tmp[4];
		double fRec115_tmp[8];
		double* fRec115 = &fRec115_tmp[4];
		double fYec12_tmp[8];
		double* fYec12 = &fYec12_tmp[4];
		double fRec114_tmp[8];
		double* fRec114 = &fRec114_tmp[4];
		double fRec113_tmp[8];
		double* fRec113 = &fRec113_tmp[4];
		double fZec27[4];
		double fRec112_tmp[8];
		double* fRec112 = &fRec112_tmp[4];
		double fZec28[4];
		double fRec111_tmp[8];
		double* fRec111 = &fRec111_tmp[4];
		double fRec121_tmp[8];
		double* fRec121 = &fRec121_tmp[4];
		double fRec120_tmp[8];
		double* fRec120 = &fRec120_tmp[4];
		double fYec13_tmp[8];
		double* fYec13 = &fYec13_tmp[4];
		double fRec119_tmp[8];
		double* fRec119 = &fRec119_tmp[4];
		double fRec118_tmp[8];
		double* fRec118 = &fRec118_tmp[4];
		double fZec29[4];
		double fRec117_tmp[8];
		double* fRec117 = &fRec117_tmp[4];
		double fRec125_tmp[8];
		double* fRec125 = &fRec125_tmp[4];
		double fRec124_tmp[8];
		double* fRec124 = &fRec124_tmp[4];
		double fYec14_tmp[8];
		double* fYec14 = &fYec14_tmp[4];
		double fRec123_tmp[8];
		double* fRec123 = &fRec123_tmp[4];
		double fRec122_tmp[8];
		double* fRec122 = &fRec122_tmp[4];
		double fRec127_tmp[8];
		double* fRec127 = &fRec127_tmp[4];
		double fRec126_tmp[8];
		double* fRec126 = &fRec126_tmp[4];
		double fRec132_tmp[8];
		double* fRec132 = &fRec132_tmp[4];
		double fRec131_tmp[8];
		double* fRec131 = &fRec131_tmp[4];
		double fZec30[4];
		double fRec130_tmp[8];
		double* fRec130 = &fRec130_tmp[4];
		double fZec31[4];
		double fRec129_tmp[8];
		double* fRec129 = &fRec129_tmp[4];
		double fZec32[4];
		double fRec128_tmp[8];
		double* fRec128 = &fRec128_tmp[4];
		double fRec138_tmp[8];
		double* fRec138 = &fRec138_tmp[4];
		double fRec137_tmp[8];
		double* fRec137 = &fRec137_tmp[4];
		double fYec15_tmp[8];
		double* fYec15 = &fYec15_tmp[4];
		double fRec136_tmp[8];
		double* fRec136 = &fRec136_tmp[4];
		double fRec135_tmp[8];
		double* fRec135 = &fRec135_tmp[4];
		double fZec33[4];
		double fRec134_tmp[8];
		double* fRec134 = &fRec134_tmp[4];
		double fZec34[4];
		double fRec133_tmp[8];
		double* fRec133 = &fRec133_tmp[4];
		double fRec143_tmp[8];
		double* fRec143 = &fRec143_tmp[4];
		double fRec142_tmp[8];
		double* fRec142 = &fRec142_tmp[4];
		double fYec16_tmp[8];
		double* fYec16 = &fYec16_tmp[4];
		double fRec141_tmp[8];
		double* fRec141 = &fRec141_tmp[4];
		double fRec140_tmp[8];
		double* fRec140 = &fRec140_tmp[4];
		double fZec35[4];
		double fRec139_tmp[8];
		double* fRec139 = &fRec139_tmp[4];
		double fRec147_tmp[8];
		double* fRec147 = &fRec147_tmp[4];
		double fRec146_tmp[8];
		double* fRec146 = &fRec146_tmp[4];
		double fYec17_tmp[8];
		double* fYec17 = &fYec17_tmp[4];
		double fRec145_tmp[8];
		double* fRec145 = &fRec145_tmp[4];
		double fRec144_tmp[8];
		double* fRec144 = &fRec144_tmp[4];
		double fRec149_tmp[8];
		double* fRec149 = &fRec149_tmp[4];
		double fRec148_tmp[8];
		double* fRec148 = &fRec148_tmp[4];
		double fRec154_tmp[8];
		double* fRec154 = &fRec154_tmp[4];
		double fRec153_tmp[8];
		double* fRec153 = &fRec153_tmp[4];
		double fZec36[4];
		double fRec152_tmp[8];
		double* fRec152 = &fRec152_tmp[4];
		double fZec37[4];
		double fRec151_tmp[8];
		double* fRec151 = &fRec151_tmp[4];
		double fZec38[4];
		double fRec150_tmp[8];
		double* fRec150 = &fRec150_tmp[4];
		double fRec160_tmp[8];
		double* fRec160 = &fRec160_tmp[4];
		double fRec159_tmp[8];
		double* fRec159 = &fRec159_tmp[4];
		double fYec18_tmp[8];
		double* fYec18 = &fYec18_tmp[4];
		double fRec158_tmp[8];
		double* fRec158 = &fRec158_tmp[4];
		double fRec157_tmp[8];
		double* fRec157 = &fRec157_tmp[4];
		double fZec39[4];
		double fRec156_tmp[8];
		double* fRec156 = &fRec156_tmp[4];
		double fZec40[4];
		double fRec155_tmp[8];
		double* fRec155 = &fRec155_tmp[4];
		double fRec165_tmp[8];
		double* fRec165 = &fRec165_tmp[4];
		double fRec164_tmp[8];
		double* fRec164 = &fRec164_tmp[4];
		double fYec19_tmp[8];
		double* fYec19 = &fYec19_tmp[4];
		double fRec163_tmp[8];
		double* fRec163 = &fRec163_tmp[4];
		double fRec162_tmp[8];
		double* fRec162 = &fRec162_tmp[4];
		double fZec41[4];
		double fRec161_tmp[8];
		double* fRec161 = &fRec161_tmp[4];
		double fRec169_tmp[8];
		double* fRec169 = &fRec169_tmp[4];
		double fRec168_tmp[8];
		double* fRec168 = &fRec168_tmp[4];
		double fYec20_tmp[8];
		double* fYec20 = &fYec20_tmp[4];
		double fRec167_tmp[8];
		double* fRec167 = &fRec167_tmp[4];
		double fRec166_tmp[8];
		double* fRec166 = &fRec166_tmp[4];
		double fRec171_tmp[8];
		double* fRec171 = &fRec171_tmp[4];
		double fRec170_tmp[8];
		double* fRec170 = &fRec170_tmp[4];
		double fRec176_tmp[8];
		double* fRec176 = &fRec176_tmp[4];
		double fRec175_tmp[8];
		double* fRec175 = &fRec175_tmp[4];
		double fZec42[4];
		double fRec174_tmp[8];
		double* fRec174 = &fRec174_tmp[4];
		double fZec43[4];
		double fRec173_tmp[8];
		double* fRec173 = &fRec173_tmp[4];
		double fZec44[4];
		double fRec172_tmp[8];
		double* fRec172 = &fRec172_tmp[4];
		double fRec182_tmp[8];
		double* fRec182 = &fRec182_tmp[4];
		double fRec181_tmp[8];
		double* fRec181 = &fRec181_tmp[4];
		double fYec21_tmp[8];
		double* fYec21 = &fYec21_tmp[4];
		double fRec180_tmp[8];
		double* fRec180 = &fRec180_tmp[4];
		double fRec179_tmp[8];
		double* fRec179 = &fRec179_tmp[4];
		double fZec45[4];
		double fRec178_tmp[8];
		double* fRec178 = &fRec178_tmp[4];
		double fZec46[4];
		double fRec177_tmp[8];
		double* fRec177 = &fRec177_tmp[4];
		double fRec187_tmp[8];
		double* fRec187 = &fRec187_tmp[4];
		double fRec186_tmp[8];
		double* fRec186 = &fRec186_tmp[4];
		double fYec22_tmp[8];
		double* fYec22 = &fYec22_tmp[4];
		double fRec185_tmp[8];
		double* fRec185 = &fRec185_tmp[4];
		double fRec184_tmp[8];
		double* fRec184 = &fRec184_tmp[4];
		double fZec47[4];
		double fRec183_tmp[8];
		double* fRec183 = &fRec183_tmp[4];
		double fRec191_tmp[8];
		double* fRec191 = &fRec191_tmp[4];
		double fRec190_tmp[8];
		double* fRec190 = &fRec190_tmp[4];
		double fYec23_tmp[8];
		double* fYec23 = &fYec23_tmp[4];
		double fRec189_tmp[8];
		double* fRec189 = &fRec189_tmp[4];
		double fRec188_tmp[8];
		double* fRec188 = &fRec188_tmp[4];
		double fRec193_tmp[8];
		double* fRec193 = &fRec193_tmp[4];
		double fRec192_tmp[8];
		double* fRec192 = &fRec192_tmp[4];
		double fRec198_tmp[8];
		double* fRec198 = &fRec198_tmp[4];
		double fRec197_tmp[8];
		double* fRec197 = &fRec197_tmp[4];
		double fZec48[4];
		double fRec196_tmp[8];
		double* fRec196 = &fRec196_tmp[4];
		double fZec49[4];
		double fRec195_tmp[8];
		double* fRec195 = &fRec195_tmp[4];
		double fZec50[4];
		double fRec194_tmp[8];
		double* fRec194 = &fRec194_tmp[4];
		double fRec204_tmp[8];
		double* fRec204 = &fRec204_tmp[4];
		double fRec203_tmp[8];
		double* fRec203 = &fRec203_tmp[4];
		double fYec24_tmp[8];
		double* fYec24 = &fYec24_tmp[4];
		double fRec202_tmp[8];
		double* fRec202 = &fRec202_tmp[4];
		double fRec201_tmp[8];
		double* fRec201 = &fRec201_tmp[4];
		double fZec51[4];
		double fRec200_tmp[8];
		double* fRec200 = &fRec200_tmp[4];
		double fZec52[4];
		double fRec199_tmp[8];
		double* fRec199 = &fRec199_tmp[4];
		double fRec209_tmp[8];
		double* fRec209 = &fRec209_tmp[4];
		double fRec208_tmp[8];
		double* fRec208 = &fRec208_tmp[4];
		double fYec25_tmp[8];
		double* fYec25 = &fYec25_tmp[4];
		double fRec207_tmp[8];
		double* fRec207 = &fRec207_tmp[4];
		double fRec206_tmp[8];
		double* fRec206 = &fRec206_tmp[4];
		double fZec53[4];
		double fRec205_tmp[8];
		double* fRec205 = &fRec205_tmp[4];
		double fRec213_tmp[8];
		double* fRec213 = &fRec213_tmp[4];
		double fRec212_tmp[8];
		double* fRec212 = &fRec212_tmp[4];
		double fYec26_tmp[8];
		double* fYec26 = &fYec26_tmp[4];
		double fRec211_tmp[8];
		double* fRec211 = &fRec211_tmp[4];
		double fRec210_tmp[8];
		double* fRec210 = &fRec210_tmp[4];
		double fRec215_tmp[8];
		double* fRec215 = &fRec215_tmp[4];
		double fRec214_tmp[8];
		double* fRec214 = &fRec214_tmp[4];
		double fRec220_tmp[8];
		double* fRec220 = &fRec220_tmp[4];
		double fRec219_tmp[8];
		double* fRec219 = &fRec219_tmp[4];
		double fZec54[4];
		double fRec218_tmp[8];
		double* fRec218 = &fRec218_tmp[4];
		double fZec55[4];
		double fRec217_tmp[8];
		double* fRec217 = &fRec217_tmp[4];
		double fZec56[4];
		double fRec216_tmp[8];
		double* fRec216 = &fRec216_tmp[4];
		double fRec226_tmp[8];
		double* fRec226 = &fRec226_tmp[4];
		double fRec225_tmp[8];
		double* fRec225 = &fRec225_tmp[4];
		double fYec27_tmp[8];
		double* fYec27 = &fYec27_tmp[4];
		double fRec224_tmp[8];
		double* fRec224 = &fRec224_tmp[4];
		double fRec223_tmp[8];
		double* fRec223 = &fRec223_tmp[4];
		double fZec57[4];
		double fRec222_tmp[8];
		double* fRec222 = &fRec222_tmp[4];
		double fZec58[4];
		double fRec221_tmp[8];
		double* fRec221 = &fRec221_tmp[4];
		double fRec231_tmp[8];
		double* fRec231 = &fRec231_tmp[4];
		double fRec230_tmp[8];
		double* fRec230 = &fRec230_tmp[4];
		double fYec28_tmp[8];
		double* fYec28 = &fYec28_tmp[4];
		double fRec229_tmp[8];
		double* fRec229 = &fRec229_tmp[4];
		double fRec228_tmp[8];
		double* fRec228 = &fRec228_tmp[4];
		double fZec59[4];
		double fRec227_tmp[8];
		double* fRec227 = &fRec227_tmp[4];
		double fRec235_tmp[8];
		double* fRec235 = &fRec235_tmp[4];
		double fRec234_tmp[8];
		double* fRec234 = &fRec234_tmp[4];
		double fYec29_tmp[8];
		double* fYec29 = &fYec29_tmp[4];
		double fRec233_tmp[8];
		double* fRec233 = &fRec233_tmp[4];
		double fRec232_tmp[8];
		double* fRec232 = &fRec232_tmp[4];
		double fRec237_tmp[8];
		double* fRec237 = &fRec237_tmp[4];
		double fRec236_tmp[8];
		double* fRec236 = &fRec236_tmp[4];
		double fRec242_tmp[8];
		double* fRec242 = &fRec242_tmp[4];
		double fRec241_tmp[8];
		double* fRec241 = &fRec241_tmp[4];
		double fZec60[4];
		double fRec240_tmp[8];
		double* fRec240 = &fRec240_tmp[4];
		double fZec61[4];
		double fRec239_tmp[8];
		double* fRec239 = &fRec239_tmp[4];
		double fZec62[4];
		double fRec238_tmp[8];
		double* fRec238 = &fRec238_tmp[4];
		double fRec248_tmp[8];
		double* fRec248 = &fRec248_tmp[4];
		double fRec247_tmp[8];
		double* fRec247 = &fRec247_tmp[4];
		double fYec30_tmp[8];
		double* fYec30 = &fYec30_tmp[4];
		double fRec246_tmp[8];
		double* fRec246 = &fRec246_tmp[4];
		double fRec245_tmp[8];
		double* fRec245 = &fRec245_tmp[4];
		double fZec63[4];
		double fRec244_tmp[8];
		double* fRec244 = &fRec244_tmp[4];
		double fZec64[4];
		double fRec243_tmp[8];
		double* fRec243 = &fRec243_tmp[4];
		double fRec253_tmp[8];
		double* fRec253 = &fRec253_tmp[4];
		double fRec252_tmp[8];
		double* fRec252 = &fRec252_tmp[4];
		double fYec31_tmp[8];
		double* fYec31 = &fYec31_tmp[4];
		double fRec251_tmp[8];
		double* fRec251 = &fRec251_tmp[4];
		double fRec250_tmp[8];
		double* fRec250 = &fRec250_tmp[4];
		double fZec65[4];
		double fRec249_tmp[8];
		double* fRec249 = &fRec249_tmp[4];
		double fRec257_tmp[8];
		double* fRec257 = &fRec257_tmp[4];
		double fRec256_tmp[8];
		double* fRec256 = &fRec256_tmp[4];
		double fYec32_tmp[8];
		double* fYec32 = &fYec32_tmp[4];
		double fRec255_tmp[8];
		double* fRec255 = &fRec255_tmp[4];
		double fRec254_tmp[8];
		double* fRec254 = &fRec254_tmp[4];
		double fRec259_tmp[8];
		double* fRec259 = &fRec259_tmp[4];
		double fRec258_tmp[8];
		double* fRec258 = &fRec258_tmp[4];
		double fRec264_tmp[8];
		double* fRec264 = &fRec264_tmp[4];
		double fRec263_tmp[8];
		double* fRec263 = &fRec263_tmp[4];
		double fZec66[4];
		double fRec262_tmp[8];
		double* fRec262 = &fRec262_tmp[4];
		double fZec67[4];
		double fRec261_tmp[8];
		double* fRec261 = &fRec261_tmp[4];
		double fZec68[4];
		double fRec260_tmp[8];
		double* fRec260 = &fRec260_tmp[4];
		double fRec270_tmp[8];
		double* fRec270 = &fRec270_tmp[4];
		double fRec269_tmp[8];
		double* fRec269 = &fRec269_tmp[4];
		double fYec33_tmp[8];
		double* fYec33 = &fYec33_tmp[4];
		double fRec268_tmp[8];
		double* fRec268 = &fRec268_tmp[4];
		double fRec267_tmp[8];
		double* fRec267 = &fRec267_tmp[4];
		double fZec69[4];
		double fRec266_tmp[8];
		double* fRec266 = &fRec266_tmp[4];
		double fZec70[4];
		double fRec265_tmp[8];
		double* fRec265 = &fRec265_tmp[4];
		double fRec275_tmp[8];
		double* fRec275 = &fRec275_tmp[4];
		double fRec274_tmp[8];
		double* fRec274 = &fRec274_tmp[4];
		double fYec34_tmp[8];
		double* fYec34 = &fYec34_tmp[4];
		double fRec273_tmp[8];
		double* fRec273 = &fRec273_tmp[4];
		double fRec272_tmp[8];
		double* fRec272 = &fRec272_tmp[4];
		double fZec71[4];
		double fRec271_tmp[8];
		double* fRec271 = &fRec271_tmp[4];
		double fRec279_tmp[8];
		double* fRec279 = &fRec279_tmp[4];
		double fRec278_tmp[8];
		double* fRec278 = &fRec278_tmp[4];
		double fYec35_tmp[8];
		double* fYec35 = &fYec35_tmp[4];
		double fRec277_tmp[8];
		double* fRec277 = &fRec277_tmp[4];
		double fRec276_tmp[8];
		double* fRec276 = &fRec276_tmp[4];
		double fRec281_tmp[8];
		double* fRec281 = &fRec281_tmp[4];
		double fRec280_tmp[8];
		double* fRec280 = &fRec280_tmp[4];
		double fRec286_tmp[8];
		double* fRec286 = &fRec286_tmp[4];
		double fRec285_tmp[8];
		double* fRec285 = &fRec285_tmp[4];
		double fZec72[4];
		double fRec284_tmp[8];
		double* fRec284 = &fRec284_tmp[4];
		double fZec73[4];
		double fRec283_tmp[8];
		double* fRec283 = &fRec283_tmp[4];
		double fZec74[4];
		double fRec282_tmp[8];
		double* fRec282 = &fRec282_tmp[4];
		double fRec292_tmp[8];
		double* fRec292 = &fRec292_tmp[4];
		double fRec291_tmp[8];
		double* fRec291 = &fRec291_tmp[4];
		double fYec36_tmp[8];
		double* fYec36 = &fYec36_tmp[4];
		double fRec290_tmp[8];
		double* fRec290 = &fRec290_tmp[4];
		double fRec289_tmp[8];
		double* fRec289 = &fRec289_tmp[4];
		double fZec75[4];
		double fRec288_tmp[8];
		double* fRec288 = &fRec288_tmp[4];
		double fZec76[4];
		double fRec287_tmp[8];
		double* fRec287 = &fRec287_tmp[4];
		double fRec297_tmp[8];
		double* fRec297 = &fRec297_tmp[4];
		double fRec296_tmp[8];
		double* fRec296 = &fRec296_tmp[4];
		double fYec37_tmp[8];
		double* fYec37 = &fYec37_tmp[4];
		double fRec295_tmp[8];
		double* fRec295 = &fRec295_tmp[4];
		double fRec294_tmp[8];
		double* fRec294 = &fRec294_tmp[4];
		double fZec77[4];
		double fRec293_tmp[8];
		double* fRec293 = &fRec293_tmp[4];
		double fRec301_tmp[8];
		double* fRec301 = &fRec301_tmp[4];
		double fRec300_tmp[8];
		double* fRec300 = &fRec300_tmp[4];
		double fYec38_tmp[8];
		double* fYec38 = &fYec38_tmp[4];
		double fRec299_tmp[8];
		double* fRec299 = &fRec299_tmp[4];
		double fRec298_tmp[8];
		double* fRec298 = &fRec298_tmp[4];
		double fRec303_tmp[8];
		double* fRec303 = &fRec303_tmp[4];
		double fRec302_tmp[8];
		double* fRec302 = &fRec302_tmp[4];
		double fRec308_tmp[8];
		double* fRec308 = &fRec308_tmp[4];
		double fRec307_tmp[8];
		double* fRec307 = &fRec307_tmp[4];
		double fZec78[4];
		double fRec306_tmp[8];
		double* fRec306 = &fRec306_tmp[4];
		double fZec79[4];
		double fRec305_tmp[8];
		double* fRec305 = &fRec305_tmp[4];
		double fZec80[4];
		double fRec304_tmp[8];
		double* fRec304 = &fRec304_tmp[4];
		double fRec314_tmp[8];
		double* fRec314 = &fRec314_tmp[4];
		double fRec313_tmp[8];
		double* fRec313 = &fRec313_tmp[4];
		double fYec39_tmp[8];
		double* fYec39 = &fYec39_tmp[4];
		double fRec312_tmp[8];
		double* fRec312 = &fRec312_tmp[4];
		double fRec311_tmp[8];
		double* fRec311 = &fRec311_tmp[4];
		double fZec81[4];
		double fRec310_tmp[8];
		double* fRec310 = &fRec310_tmp[4];
		double fZec82[4];
		double fRec309_tmp[8];
		double* fRec309 = &fRec309_tmp[4];
		double fRec319_tmp[8];
		double* fRec319 = &fRec319_tmp[4];
		double fRec318_tmp[8];
		double* fRec318 = &fRec318_tmp[4];
		double fYec40_tmp[8];
		double* fYec40 = &fYec40_tmp[4];
		double fRec317_tmp[8];
		double* fRec317 = &fRec317_tmp[4];
		double fRec316_tmp[8];
		double* fRec316 = &fRec316_tmp[4];
		double fZec83[4];
		double fRec315_tmp[8];
		double* fRec315 = &fRec315_tmp[4];
		double fRec323_tmp[8];
		double* fRec323 = &fRec323_tmp[4];
		double fRec322_tmp[8];
		double* fRec322 = &fRec322_tmp[4];
		double fYec41_tmp[8];
		double* fYec41 = &fYec41_tmp[4];
		double fRec321_tmp[8];
		double* fRec321 = &fRec321_tmp[4];
		double fRec320_tmp[8];
		double* fRec320 = &fRec320_tmp[4];
		double fRec325_tmp[8];
		double* fRec325 = &fRec325_tmp[4];
		double fRec324_tmp[8];
		double* fRec324 = &fRec324_tmp[4];
		double fRec330_tmp[8];
		double* fRec330 = &fRec330_tmp[4];
		double fRec329_tmp[8];
		double* fRec329 = &fRec329_tmp[4];
		double fZec84[4];
		double fRec328_tmp[8];
		double* fRec328 = &fRec328_tmp[4];
		double fZec85[4];
		double fRec327_tmp[8];
		double* fRec327 = &fRec327_tmp[4];
		double fZec86[4];
		double fRec326_tmp[8];
		double* fRec326 = &fRec326_tmp[4];
		double fRec336_tmp[8];
		double* fRec336 = &fRec336_tmp[4];
		double fRec335_tmp[8];
		double* fRec335 = &fRec335_tmp[4];
		double fYec42_tmp[8];
		double* fYec42 = &fYec42_tmp[4];
		double fRec334_tmp[8];
		double* fRec334 = &fRec334_tmp[4];
		double fRec333_tmp[8];
		double* fRec333 = &fRec333_tmp[4];
		double fZec87[4];
		double fRec332_tmp[8];
		double* fRec332 = &fRec332_tmp[4];
		double fZec88[4];
		double fRec331_tmp[8];
		double* fRec331 = &fRec331_tmp[4];
		double fRec341_tmp[8];
		double* fRec341 = &fRec341_tmp[4];
		double fRec340_tmp[8];
		double* fRec340 = &fRec340_tmp[4];
		double fYec43_tmp[8];
		double* fYec43 = &fYec43_tmp[4];
		double fRec339_tmp[8];
		double* fRec339 = &fRec339_tmp[4];
		double fRec338_tmp[8];
		double* fRec338 = &fRec338_tmp[4];
		double fZec89[4];
		double fRec337_tmp[8];
		double* fRec337 = &fRec337_tmp[4];
		double fRec345_tmp[8];
		double* fRec345 = &fRec345_tmp[4];
		double fRec344_tmp[8];
		double* fRec344 = &fRec344_tmp[4];
		double fYec44_tmp[8];
		double* fYec44 = &fYec44_tmp[4];
		double fRec343_tmp[8];
		double* fRec343 = &fRec343_tmp[4];
		double fRec342_tmp[8];
		double* fRec342 = &fRec342_tmp[4];
		double fRec347_tmp[8];
		double* fRec347 = &fRec347_tmp[4];
		double fRec346_tmp[8];
		double* fRec346 = &fRec346_tmp[4];
		double fRec352_tmp[8];
		double* fRec352 = &fRec352_tmp[4];
		double fRec351_tmp[8];
		double* fRec351 = &fRec351_tmp[4];
		double fZec90[4];
		double fRec350_tmp[8];
		double* fRec350 = &fRec350_tmp[4];
		double fZec91[4];
		double fRec349_tmp[8];
		double* fRec349 = &fRec349_tmp[4];
		double fZec92[4];
		double fRec348_tmp[8];
		double* fRec348 = &fRec348_tmp[4];
		double fRec358_tmp[8];
		double* fRec358 = &fRec358_tmp[4];
		double fRec357_tmp[8];
		double* fRec357 = &fRec357_tmp[4];
		double fYec45_tmp[8];
		double* fYec45 = &fYec45_tmp[4];
		double fRec356_tmp[8];
		double* fRec356 = &fRec356_tmp[4];
		double fRec355_tmp[8];
		double* fRec355 = &fRec355_tmp[4];
		double fZec93[4];
		double fRec354_tmp[8];
		double* fRec354 = &fRec354_tmp[4];
		double fZec94[4];
		double fRec353_tmp[8];
		double* fRec353 = &fRec353_tmp[4];
		double fRec363_tmp[8];
		double* fRec363 = &fRec363_tmp[4];
		double fRec362_tmp[8];
		double* fRec362 = &fRec362_tmp[4];
		double fYec46_tmp[8];
		double* fYec46 = &fYec46_tmp[4];
		double fRec361_tmp[8];
		double* fRec361 = &fRec361_tmp[4];
		double fRec360_tmp[8];
		double* fRec360 = &fRec360_tmp[4];
		double fZec95[4];
		double fRec359_tmp[8];
		double* fRec359 = &fRec359_tmp[4];
		double fRec367_tmp[8];
		double* fRec367 = &fRec367_tmp[4];
		double fRec366_tmp[8];
		double* fRec366 = &fRec366_tmp[4];
		double fYec47_tmp[8];
		double* fYec47 = &fYec47_tmp[4];
		double fRec365_tmp[8];
		double* fRec365 = &fRec365_tmp[4];
		double fRec364_tmp[8];
		double* fRec364 = &fRec364_tmp[4];
		double fRec369_tmp[8];
		double* fRec369 = &fRec369_tmp[4];
		double fRec368_tmp[8];
		double* fRec368 = &fRec368_tmp[4];
		double fSlow47 = 0.1 * static_cast<double>(fCheckbox0);
		double fZec96[4];
		double fSlow48 = static_cast<double>(fButton0);
		double fVec0_tmp[8];
		double* fVec0 = &fVec0_tmp[4];
		double fSlow49 = static_cast<double>(fButton1);
		double fVec1_tmp[8];
		double* fVec1 = &fVec1_tmp[4];
		int iZec97[4];
		double fZec98[4];
		double fSlow50 = 0.25 * (1.0 - 0.5 * static_cast<double>(fButton2));
		double fSlow51 = static_cast<double>(fHslider4);
		double fSlow52 = std::pow(2.0, std::floor(1.4426950408889634 * std::log(fConst3 * fSlow51) + 0.5));
		double fSlow53 = static_cast<double>(fVslider0);
		double fSlow54 = std::exp(-(fConst2 * (fSlow52 / fSlow53)));
		double fSlow55 = static_cast<double>(fVslider1);
		double fSlow56 = std::exp(-(fConst2 * (fSlow52 / fSlow55)));
		double fSlow57 = static_cast<double>(fVslider2);
		double fSlow58 = std::exp(-(fConst2 * (fSlow52 / fSlow57)));
		double fSlow59 = static_cast<double>(fVslider3);
		double fSlow60 = std::exp(-(fConst2 * (fSlow52 / fSlow59))) / fSlow32;
		double fSlow61 = static_cast<double>(fVslider4);
		double fSlow62 = std::exp(-(fConst2 * (fSlow52 / fSlow61)));
		double fZec99[4];
		double fSlow63 = static_cast<double>(fHslider5);
		double fSlow64 = fSlow63 / fSlow51;
		double fSlow65 = std::pow(23.0, std::floor(0.318928988903801 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.5333333333333333)) + 0.5));
		double fSlow66 = std::exp(-(fConst2 * (fSlow65 / fSlow53)));
		double fSlow67 = std::exp(-(fConst2 * (fSlow65 / fSlow55)));
		double fSlow68 = std::exp(-(fConst2 * (fSlow65 / fSlow57)));
		double fSlow69 = std::exp(-(fConst2 * (fSlow65 / fSlow59))) / fSlow32;
		double fSlow70 = std::exp(-(fConst2 * (fSlow65 / fSlow61)));
		double fZec100[4];
		double fZec101[4];
		double fSlow71 = std::pow(11.0, std::floor(0.4170323914242463 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.26666666666666666)) + 0.5));
		double fSlow72 = std::exp(-(fConst2 * (fSlow71 / fSlow53)));
		double fSlow73 = std::exp(-(fConst2 * (fSlow71 / fSlow55)));
		double fSlow74 = std::exp(-(fConst2 * (fSlow71 / fSlow57)));
		double fSlow75 = std::exp(-(fConst2 * (fSlow71 / fSlow59))) / fSlow32;
		double fSlow76 = std::exp(-(fConst2 * (fSlow71 / fSlow61)));
		double fZec102[4];
		double fSlow77 = std::pow(41.0, std::floor(0.269282508064391 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.8)) + 0.5));
		double fSlow78 = std::exp(-(fConst2 * (fSlow77 / fSlow53)));
		double fSlow79 = std::exp(-(fConst2 * (fSlow77 / fSlow55)));
		double fSlow80 = std::exp(-(fConst2 * (fSlow77 / fSlow57)));
		double fSlow81 = std::exp(-(fConst2 * (fSlow77 / fSlow59))) / fSlow32;
		double fSlow82 = std::exp(-(fConst2 * (fSlow77 / fSlow61)));
		double fZec103[4];
		double fZec104[4];
		double fZec105[4];
		double fSlow83 = std::pow(5.0, std::floor(0.6213349345596119 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.13333333333333333)) + 0.5));
		double fSlow84 = std::exp(-(fConst2 * (fSlow83 / fSlow53)));
		double fSlow85 = std::exp(-(fConst2 * (fSlow83 / fSlow55)));
		double fSlow86 = std::exp(-(fConst2 * (fSlow83 / fSlow57)));
		double fSlow87 = std::exp(-(fConst2 * (fSlow83 / fSlow59))) / fSlow32;
		double fSlow88 = std::exp(-(fConst2 * (fSlow83 / fSlow61)));
		double fZec106[4];
		double fSlow89 = std::pow(31.0, std::floor(0.29120667621996243 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.6666666666666666)) + 0.5));
		double fSlow90 = std::exp(-(fConst2 * (fSlow89 / fSlow53)));
		double fSlow91 = std::exp(-(fConst2 * (fSlow89 / fSlow55)));
		double fSlow92 = std::exp(-(fConst2 * (fSlow89 / fSlow57)));
		double fSlow93 = std::exp(-(fConst2 * (fSlow89 / fSlow59))) / fSlow32;
		double fSlow94 = std::exp(-(fConst2 * (fSlow89 / fSlow61)));
		double fZec107[4];
		double fZec108[4];
		double fSlow95 = std::pow(17.0, std::floor(0.35295612386476116 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.4)) + 0.5));
		double fSlow96 = std::exp(-(fConst2 * (fSlow95 / fSlow53)));
		double fSlow97 = std::exp(-(fConst2 * (fSlow95 / fSlow55)));
		double fSlow98 = std::exp(-(fConst2 * (fSlow95 / fSlow57)));
		double fSlow99 = std::exp(-(fConst2 * (fSlow95 / fSlow59))) / fSlow32;
		double fSlow100 = std::exp(-(fConst2 * (fSlow95 / fSlow61)));
		double fZec109[4];
		double fSlow101 = std::pow(47.0, std::floor(0.25973030217227155 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.9333333333333333)) + 0.5));
		double fSlow102 = std::exp(-(fConst2 * (fSlow101 / fSlow53)));
		double fSlow103 = std::exp(-(fConst2 * (fSlow101 / fSlow55)));
		double fSlow104 = std::exp(-(fConst2 * (fSlow101 / fSlow57)));
		double fSlow105 = std::exp(-(fConst2 * (fSlow101 / fSlow59))) / fSlow32;
		double fSlow106 = std::exp(-(fConst2 * (fSlow101 / fSlow61)));
		double fZec110[4];
		double fZec111[4];
		double fZec112[4];
		double fZec113[4];
		double fSlow107 = std::pow(3.0, std::floor(0.9102392266268373 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.06666666666666667)) + 0.5));
		double fSlow108 = std::exp(-(fConst2 * (fSlow107 / fSlow53)));
		double fSlow109 = std::exp(-(fConst2 * (fSlow107 / fSlow55)));
		double fSlow110 = std::exp(-(fConst2 * (fSlow107 / fSlow57)));
		double fSlow111 = std::exp(-(fConst2 * (fSlow107 / fSlow59))) / fSlow32;
		double fSlow112 = std::exp(-(fConst2 * (fSlow107 / fSlow61)));
		double fZec114[4];
		double fSlow113 = std::pow(29.0, std::floor(0.2969742043733701 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.6)) + 0.5));
		double fSlow114 = std::exp(-(fConst2 * (fSlow113 / fSlow53)));
		double fSlow115 = std::exp(-(fConst2 * (fSlow113 / fSlow55)));
		double fSlow116 = std::exp(-(fConst2 * (fSlow113 / fSlow57)));
		double fSlow117 = std::exp(-(fConst2 * (fSlow113 / fSlow59))) / fSlow32;
		double fSlow118 = std::exp(-(fConst2 * (fSlow113 / fSlow61)));
		double fZec115[4];
		double fZec116[4];
		double fSlow119 = std::pow(13.0, std::floor(0.3898712452512801 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.3333333333333333)) + 0.5));
		double fSlow120 = std::exp(-(fConst2 * (fSlow119 / fSlow53)));
		double fSlow121 = std::exp(-(fConst2 * (fSlow119 / fSlow55)));
		double fSlow122 = std::exp(-(fConst2 * (fSlow119 / fSlow57)));
		double fSlow123 = std::exp(-(fConst2 * (fSlow119 / fSlow59))) / fSlow32;
		double fSlow124 = std::exp(-(fConst2 * (fSlow119 / fSlow61)));
		double fZec117[4];
		double fSlow125 = std::pow(43.0, std::floor(0.265872585674852 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.8666666666666667)) + 0.5));
		double fSlow126 = std::exp(-(fConst2 * (fSlow125 / fSlow53)));
		double fSlow127 = std::exp(-(fConst2 * (fSlow125 / fSlow55)));
		double fSlow128 = std::exp(-(fConst2 * (fSlow125 / fSlow57)));
		double fSlow129 = std::exp(-(fConst2 * (fSlow125 / fSlow59))) / fSlow32;
		double fSlow130 = std::exp(-(fConst2 * (fSlow125 / fSlow61)));
		double fZec118[4];
		double fZec119[4];
		double fZec120[4];
		double fSlow131 = std::pow(7.0, std::floor(0.5138983423697507 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.2)) + 0.5));
		double fSlow132 = std::exp(-(fConst2 * (fSlow131 / fSlow53)));
		double fSlow133 = std::exp(-(fConst2 * (fSlow131 / fSlow55)));
		double fSlow134 = std::exp(-(fConst2 * (fSlow131 / fSlow57)));
		double fSlow135 = std::exp(-(fConst2 * (fSlow131 / fSlow59))) / fSlow32;
		double fSlow136 = std::exp(-(fConst2 * (fSlow131 / fSlow61)));
		double fZec121[4];
		double fSlow137 = std::pow(37.0, std::floor(0.2769378934088574 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.7333333333333333)) + 0.5));
		double fSlow138 = std::exp(-(fConst2 * (fSlow137 / fSlow53)));
		double fSlow139 = std::exp(-(fConst2 * (fSlow137 / fSlow55)));
		double fSlow140 = std::exp(-(fConst2 * (fSlow137 / fSlow57)));
		double fSlow141 = std::exp(-(fConst2 * (fSlow137 / fSlow59))) / fSlow32;
		double fSlow142 = std::exp(-(fConst2 * (fSlow137 / fSlow61)));
		double fZec122[4];
		double fZec123[4];
		double fSlow143 = std::pow(19.0, std::floor(0.3396232718951086 * std::log(fConst3 * fSlow51 * std::pow(fSlow64, 0.4666666666666667)) + 0.5));
		double fSlow144 = std::exp(-(fConst2 * (fSlow143 / fSlow53)));
		double fSlow145 = std::exp(-(fConst2 * (fSlow143 / fSlow55)));
		double fSlow146 = std::exp(-(fConst2 * (fSlow143 / fSlow57)));
		double fSlow147 = std::exp(-(fConst2 * (fSlow143 / fSlow59))) / fSlow32;
		double fSlow148 = std::exp(-(fConst2 * (fSlow143 / fSlow61)));
		double fZec124[4];
		double fSlow149 = std::pow(53.0, std::floor(0.2518706487516997 * std::log(fConst3 * fSlow63) + 0.5));
		double fSlow150 = std::exp(-(fConst2 * (fSlow149 / fSlow53)));
		double fSlow151 = std::exp(-(fConst2 * (fSlow149 / fSlow55)));
		double fSlow152 = std::exp(-(fConst2 * (fSlow149 / fSlow57)));
		double fSlow153 = std::exp(-(fConst2 * (fSlow149 / fSlow59))) / fSlow32;
		double fSlow154 = std::exp(-(fConst2 * (fSlow149 / fSlow61)));
		double fZec125[4];
		double fZec126[4];
		double fZec127[4];
		double fZec128[4];
		double fSlow155 = 1.0 - static_cast<double>(fCheckbox1);
		double fZec129[4];
		int iSlow156 = static_cast<int>(fSlow52 + -1.0) & 8191;
		double fRec0_tmp[8];
		double* fRec0 = &fRec0_tmp[4];
		double fSlow157 = static_cast<double>(fButton3);
		double fVec2_tmp[8];
		double* fVec2 = &fVec2_tmp[4];
		double fZec130[4];
		double fZec131[4];
		int iSlow158 = static_cast<int>(fSlow107 + -1.0) & 8191;
		double fRec1_tmp[8];
		double* fRec1 = &fRec1_tmp[4];
		double fZec132[4];
		double fZec133[4];
		double fZec134[4];
		int iSlow159 = static_cast<int>(fSlow83 + -1.0) & 8191;
		double fRec2_tmp[8];
		double* fRec2 = &fRec2_tmp[4];
		double fZec135[4];
		int iSlow160 = static_cast<int>(fSlow131 + -1.0) & 8191;
		double fRec3_tmp[8];
		double* fRec3 = &fRec3_tmp[4];
		double fZec136[4];
		double fZec137[4];
		double fZec138[4];
		double fZec139[4];
		double fZec140[4];
		double fZec141[4];
		int iSlow161 = static_cast<int>(fSlow71 + -1.0) & 8191;
		double fRec4_tmp[8];
		double* fRec4 = &fRec4_tmp[4];
		int iSlow162 = static_cast<int>(fSlow119 + -1.0) & 8191;
		double fRec5_tmp[8];
		double* fRec5 = &fRec5_tmp[4];
		double fZec142[4];
		double fZec143[4];
		int iSlow163 = static_cast<int>(fSlow95 + -1.0) & 8191;
		double fRec6_tmp[8];
		double* fRec6 = &fRec6_tmp[4];
		int iSlow164 = static_cast<int>(fSlow143 + -1.0) & 8191;
		double fRec7_tmp[8];
		double* fRec7 = &fRec7_tmp[4];
		double fZec144[4];
		double fZec145[4];
		double fZec146[4];
		double fZec147[4];
		double fZec148[4];
		double fZec149[4];
		double fZec150[4];
		double fZec151[4];
		double fZec152[4];
		double fZec153[4];
		double fZec154[4];
		double fZec155[4];
		double fZec156[4];
		double fZec157[4];
		int iSlow165 = static_cast<int>(fSlow65 + -1.0) & 8191;
		double fRec8_tmp[8];
		double* fRec8 = &fRec8_tmp[4];
		int iSlow166 = static_cast<int>(fSlow113 + -1.0) & 8191;
		double fRec9_tmp[8];
		double* fRec9 = &fRec9_tmp[4];
		double fZec158[4];
		double fZec159[4];
		int iSlow167 = static_cast<int>(fSlow89 + -1.0) & 8191;
		double fRec10_tmp[8];
		double* fRec10 = &fRec10_tmp[4];
		int iSlow168 = static_cast<int>(fSlow137 + -1.0) & 8191;
		double fRec11_tmp[8];
		double* fRec11 = &fRec11_tmp[4];
		double fZec160[4];
		double fZec161[4];
		double fZec162[4];
		double fZec163[4];
		double fZec164[4];
		double fZec165[4];
		int iSlow169 = static_cast<int>(fSlow77 + -1.0) & 8191;
		double fRec12_tmp[8];
		double* fRec12 = &fRec12_tmp[4];
		int iSlow170 = static_cast<int>(fSlow125 + -1.0) & 8191;
		double fRec13_tmp[8];
		double* fRec13 = &fRec13_tmp[4];
		double fZec166[4];
		double fZec167[4];
		int iSlow171 = static_cast<int>(fSlow101 + -1.0) & 8191;
		double fRec14_tmp[8];
		double* fRec14 = &fRec14_tmp[4];
		int iSlow172 = static_cast<int>(fSlow149 + -1.0) & 8191;
		double fRec15_tmp[8];
		double* fRec15 = &fRec15_tmp[4];
		double fSlow173 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider6));
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; vindex <= (faust_wrap_sub(count, 4)); vindex = faust_wrap_add(vindex, 4)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 4;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec17_tmp[j0] = iRec17_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec17[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec17[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec17_perm[j1] = iRec17_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec16_tmp[j2] = fRec16_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = 0.5221894 * fRec16[faust_wrap_sub(i, 3)] + 4.656612875245797e-10 * static_cast<double>(iRec17[i]) + 2.494956002 * fRec16[faust_wrap_sub(i, 1)] - 2.017265875 * fRec16[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec16_perm[j3] = fRec16_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec96[i] = fSlow47 * (0.049922035 * fRec16[i] + 0.050612699 * fRec16[faust_wrap_sub(i, 2)] - (0.095993537 * fRec16[faust_wrap_sub(i, 1)] + 0.004408786 * fRec16[faust_wrap_sub(i, 3)]));
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j804 = 0; j804 < 4; j804 = faust_wrap_add(j804, 1)) {
				fVec0_tmp[j804] = fVec0_perm[j804];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = fSlow48;
			}
			/* Post code */
			for (int j805 = 0; j805 < 4; j805 = faust_wrap_add(j805, 1)) {
				fVec0_perm[j805] = fVec0_tmp[faust_wrap_add(vsize, j805)];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j806 = 0; j806 < 4; j806 = faust_wrap_add(j806, 1)) {
				fVec1_tmp[j806] = fVec1_perm[j806];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec1[i] = fSlow49;
			}
			/* Post code */
			for (int j807 = 0; j807 < 4; j807 = faust_wrap_add(j807, 1)) {
				fVec1_perm[j807] = fVec1_tmp[faust_wrap_add(vsize, j807)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec97[i] = (fSlow49 - fVec1[faust_wrap_sub(i, 1)]) > 0.0;
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec98[i] = static_cast<double>(((fSlow48 - fVec0[faust_wrap_sub(i, 1)]) > 0.0) + iZec97[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec129[i] = fSlow155 * static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			for (int j810 = 0; j810 < 4; j810 = faust_wrap_add(j810, 1)) {
				fVec2_tmp[j810] = fVec2_perm[j810];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec2[i] = fSlow157;
			}
			/* Post code */
			for (int j811 = 0; j811 < 4; j811 = faust_wrap_add(j811, 1)) {
				fVec2_perm[j811] = fVec2_tmp[faust_wrap_add(vsize, j811)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec130[i] = static_cast<double>(faust_wrap_add(iZec97[i], (fSlow157 - fVec2[faust_wrap_sub(i, 1)]) > 0.0));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec131[i] = fSlow155 * static_cast<double>(input1[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec132[i] = fZec129[i] + fZec98[i] + fZec96[i];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec135[i] = fZec130[i] + fZec96[i] + fZec131[i];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec22_tmp[j4] = fRec22_perm[j4];
			}
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec21_tmp[j6] = fRec21_perm[j6];
			}
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec20_tmp[j8] = fRec20_perm[j8];
			}
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec19_tmp[j10] = fRec19_perm[j10];
			}
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec18_tmp[j12] = fRec18_perm[j12];
			}
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec28_tmp[j14] = fRec28_perm[j14];
			}
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec27_tmp[j16] = fRec27_perm[j16];
			}
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fYec0_tmp[j18] = fYec0_perm[j18];
			}
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec26_tmp[j20] = fRec26_perm[j20];
			}
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec25_tmp[j22] = fRec25_perm[j22];
			}
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec24_tmp[j24] = fRec24_perm[j24];
			}
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec23_tmp[j26] = fRec23_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec33_tmp[j28] = fRec33_perm[j28];
			}
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec32_tmp[j30] = fRec32_perm[j30];
			}
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fYec1_tmp[j32] = fYec1_perm[j32];
			}
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec31_tmp[j34] = fRec31_perm[j34];
			}
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec30_tmp[j36] = fRec30_perm[j36];
			}
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec29_tmp[j38] = fRec29_perm[j38];
			}
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec37_tmp[j40] = fRec37_perm[j40];
			}
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec36_tmp[j42] = fRec36_perm[j42];
			}
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec2_tmp[j44] = fYec2_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec35_tmp[j46] = fRec35_perm[j46];
			}
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec34_tmp[j48] = fRec34_perm[j48];
			}
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec39_tmp[j50] = fRec39_perm[j50];
			}
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec38_tmp[j52] = fRec38_perm[j52];
			}
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec44_tmp[j54] = fRec44_perm[j54];
			}
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec43_tmp[j56] = fRec43_perm[j56];
			}
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec42_tmp[j58] = fRec42_perm[j58];
			}
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec41_tmp[j60] = fRec41_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec40_tmp[j62] = fRec40_perm[j62];
			}
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec50_tmp[j64] = fRec50_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec49_tmp[j66] = fRec49_perm[j66];
			}
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fYec3_tmp[j68] = fYec3_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec48_tmp[j70] = fRec48_perm[j70];
			}
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec47_tmp[j72] = fRec47_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec46_tmp[j74] = fRec46_perm[j74];
			}
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec45_tmp[j76] = fRec45_perm[j76];
			}
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec55_tmp[j78] = fRec55_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec54_tmp[j80] = fRec54_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fYec4_tmp[j82] = fYec4_perm[j82];
			}
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec53_tmp[j84] = fRec53_perm[j84];
			}
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec52_tmp[j86] = fRec52_perm[j86];
			}
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec51_tmp[j88] = fRec51_perm[j88];
			}
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec59_tmp[j90] = fRec59_perm[j90];
			}
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec58_tmp[j92] = fRec58_perm[j92];
			}
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fYec5_tmp[j94] = fYec5_perm[j94];
			}
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec57_tmp[j96] = fRec57_perm[j96];
			}
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec56_tmp[j98] = fRec56_perm[j98];
			}
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec61_tmp[j100] = fRec61_perm[j100];
			}
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec60_tmp[j102] = fRec60_perm[j102];
			}
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec66_tmp[j104] = fRec66_perm[j104];
			}
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec65_tmp[j106] = fRec65_perm[j106];
			}
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec64_tmp[j108] = fRec64_perm[j108];
			}
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec63_tmp[j110] = fRec63_perm[j110];
			}
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec62_tmp[j112] = fRec62_perm[j112];
			}
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec72_tmp[j114] = fRec72_perm[j114];
			}
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec71_tmp[j116] = fRec71_perm[j116];
			}
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fYec6_tmp[j118] = fYec6_perm[j118];
			}
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec70_tmp[j120] = fRec70_perm[j120];
			}
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec69_tmp[j122] = fRec69_perm[j122];
			}
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec68_tmp[j124] = fRec68_perm[j124];
			}
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec67_tmp[j126] = fRec67_perm[j126];
			}
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec77_tmp[j128] = fRec77_perm[j128];
			}
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec76_tmp[j130] = fRec76_perm[j130];
			}
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fYec7_tmp[j132] = fYec7_perm[j132];
			}
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec75_tmp[j134] = fRec75_perm[j134];
			}
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec74_tmp[j136] = fRec74_perm[j136];
			}
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec73_tmp[j138] = fRec73_perm[j138];
			}
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec81_tmp[j140] = fRec81_perm[j140];
			}
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec80_tmp[j142] = fRec80_perm[j142];
			}
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fYec8_tmp[j144] = fYec8_perm[j144];
			}
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec79_tmp[j146] = fRec79_perm[j146];
			}
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec78_tmp[j148] = fRec78_perm[j148];
			}
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec83_tmp[j150] = fRec83_perm[j150];
			}
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec82_tmp[j152] = fRec82_perm[j152];
			}
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec88_tmp[j154] = fRec88_perm[j154];
			}
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec87_tmp[j156] = fRec87_perm[j156];
			}
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec86_tmp[j158] = fRec86_perm[j158];
			}
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec85_tmp[j160] = fRec85_perm[j160];
			}
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec84_tmp[j162] = fRec84_perm[j162];
			}
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec94_tmp[j164] = fRec94_perm[j164];
			}
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec93_tmp[j166] = fRec93_perm[j166];
			}
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fYec9_tmp[j168] = fYec9_perm[j168];
			}
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec92_tmp[j170] = fRec92_perm[j170];
			}
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec91_tmp[j172] = fRec91_perm[j172];
			}
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec90_tmp[j174] = fRec90_perm[j174];
			}
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec89_tmp[j176] = fRec89_perm[j176];
			}
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec99_tmp[j178] = fRec99_perm[j178];
			}
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec98_tmp[j180] = fRec98_perm[j180];
			}
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fYec10_tmp[j182] = fYec10_perm[j182];
			}
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec97_tmp[j184] = fRec97_perm[j184];
			}
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec96_tmp[j186] = fRec96_perm[j186];
			}
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec95_tmp[j188] = fRec95_perm[j188];
			}
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec103_tmp[j190] = fRec103_perm[j190];
			}
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec102_tmp[j192] = fRec102_perm[j192];
			}
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fYec11_tmp[j194] = fYec11_perm[j194];
			}
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec101_tmp[j196] = fRec101_perm[j196];
			}
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec100_tmp[j198] = fRec100_perm[j198];
			}
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec105_tmp[j200] = fRec105_perm[j200];
			}
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec104_tmp[j202] = fRec104_perm[j202];
			}
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec110_tmp[j204] = fRec110_perm[j204];
			}
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec109_tmp[j206] = fRec109_perm[j206];
			}
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec108_tmp[j208] = fRec108_perm[j208];
			}
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec107_tmp[j210] = fRec107_perm[j210];
			}
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec106_tmp[j212] = fRec106_perm[j212];
			}
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec116_tmp[j214] = fRec116_perm[j214];
			}
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec115_tmp[j216] = fRec115_perm[j216];
			}
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fYec12_tmp[j218] = fYec12_perm[j218];
			}
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec114_tmp[j220] = fRec114_perm[j220];
			}
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec113_tmp[j222] = fRec113_perm[j222];
			}
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec112_tmp[j224] = fRec112_perm[j224];
			}
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec111_tmp[j226] = fRec111_perm[j226];
			}
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec121_tmp[j228] = fRec121_perm[j228];
			}
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec120_tmp[j230] = fRec120_perm[j230];
			}
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fYec13_tmp[j232] = fYec13_perm[j232];
			}
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec119_tmp[j234] = fRec119_perm[j234];
			}
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec118_tmp[j236] = fRec118_perm[j236];
			}
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec117_tmp[j238] = fRec117_perm[j238];
			}
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec125_tmp[j240] = fRec125_perm[j240];
			}
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec124_tmp[j242] = fRec124_perm[j242];
			}
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fYec14_tmp[j244] = fYec14_perm[j244];
			}
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec123_tmp[j246] = fRec123_perm[j246];
			}
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec122_tmp[j248] = fRec122_perm[j248];
			}
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec127_tmp[j250] = fRec127_perm[j250];
			}
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec126_tmp[j252] = fRec126_perm[j252];
			}
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec132_tmp[j254] = fRec132_perm[j254];
			}
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec131_tmp[j256] = fRec131_perm[j256];
			}
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec130_tmp[j258] = fRec130_perm[j258];
			}
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec129_tmp[j260] = fRec129_perm[j260];
			}
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec128_tmp[j262] = fRec128_perm[j262];
			}
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec138_tmp[j264] = fRec138_perm[j264];
			}
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec137_tmp[j266] = fRec137_perm[j266];
			}
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fYec15_tmp[j268] = fYec15_perm[j268];
			}
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec136_tmp[j270] = fRec136_perm[j270];
			}
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec135_tmp[j272] = fRec135_perm[j272];
			}
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec134_tmp[j274] = fRec134_perm[j274];
			}
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec133_tmp[j276] = fRec133_perm[j276];
			}
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec143_tmp[j278] = fRec143_perm[j278];
			}
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec142_tmp[j280] = fRec142_perm[j280];
			}
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fYec16_tmp[j282] = fYec16_perm[j282];
			}
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec141_tmp[j284] = fRec141_perm[j284];
			}
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec140_tmp[j286] = fRec140_perm[j286];
			}
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec139_tmp[j288] = fRec139_perm[j288];
			}
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec147_tmp[j290] = fRec147_perm[j290];
			}
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec146_tmp[j292] = fRec146_perm[j292];
			}
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fYec17_tmp[j294] = fYec17_perm[j294];
			}
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec145_tmp[j296] = fRec145_perm[j296];
			}
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec144_tmp[j298] = fRec144_perm[j298];
			}
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec149_tmp[j300] = fRec149_perm[j300];
			}
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec148_tmp[j302] = fRec148_perm[j302];
			}
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec154_tmp[j304] = fRec154_perm[j304];
			}
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec153_tmp[j306] = fRec153_perm[j306];
			}
			for (int j308 = 0; j308 < 4; j308 = faust_wrap_add(j308, 1)) {
				fRec152_tmp[j308] = fRec152_perm[j308];
			}
			for (int j310 = 0; j310 < 4; j310 = faust_wrap_add(j310, 1)) {
				fRec151_tmp[j310] = fRec151_perm[j310];
			}
			for (int j312 = 0; j312 < 4; j312 = faust_wrap_add(j312, 1)) {
				fRec150_tmp[j312] = fRec150_perm[j312];
			}
			for (int j314 = 0; j314 < 4; j314 = faust_wrap_add(j314, 1)) {
				fRec160_tmp[j314] = fRec160_perm[j314];
			}
			for (int j316 = 0; j316 < 4; j316 = faust_wrap_add(j316, 1)) {
				fRec159_tmp[j316] = fRec159_perm[j316];
			}
			for (int j318 = 0; j318 < 4; j318 = faust_wrap_add(j318, 1)) {
				fYec18_tmp[j318] = fYec18_perm[j318];
			}
			for (int j320 = 0; j320 < 4; j320 = faust_wrap_add(j320, 1)) {
				fRec158_tmp[j320] = fRec158_perm[j320];
			}
			for (int j322 = 0; j322 < 4; j322 = faust_wrap_add(j322, 1)) {
				fRec157_tmp[j322] = fRec157_perm[j322];
			}
			for (int j324 = 0; j324 < 4; j324 = faust_wrap_add(j324, 1)) {
				fRec156_tmp[j324] = fRec156_perm[j324];
			}
			for (int j326 = 0; j326 < 4; j326 = faust_wrap_add(j326, 1)) {
				fRec155_tmp[j326] = fRec155_perm[j326];
			}
			for (int j328 = 0; j328 < 4; j328 = faust_wrap_add(j328, 1)) {
				fRec165_tmp[j328] = fRec165_perm[j328];
			}
			for (int j330 = 0; j330 < 4; j330 = faust_wrap_add(j330, 1)) {
				fRec164_tmp[j330] = fRec164_perm[j330];
			}
			for (int j332 = 0; j332 < 4; j332 = faust_wrap_add(j332, 1)) {
				fYec19_tmp[j332] = fYec19_perm[j332];
			}
			for (int j334 = 0; j334 < 4; j334 = faust_wrap_add(j334, 1)) {
				fRec163_tmp[j334] = fRec163_perm[j334];
			}
			for (int j336 = 0; j336 < 4; j336 = faust_wrap_add(j336, 1)) {
				fRec162_tmp[j336] = fRec162_perm[j336];
			}
			for (int j338 = 0; j338 < 4; j338 = faust_wrap_add(j338, 1)) {
				fRec161_tmp[j338] = fRec161_perm[j338];
			}
			for (int j340 = 0; j340 < 4; j340 = faust_wrap_add(j340, 1)) {
				fRec169_tmp[j340] = fRec169_perm[j340];
			}
			for (int j342 = 0; j342 < 4; j342 = faust_wrap_add(j342, 1)) {
				fRec168_tmp[j342] = fRec168_perm[j342];
			}
			for (int j344 = 0; j344 < 4; j344 = faust_wrap_add(j344, 1)) {
				fYec20_tmp[j344] = fYec20_perm[j344];
			}
			for (int j346 = 0; j346 < 4; j346 = faust_wrap_add(j346, 1)) {
				fRec167_tmp[j346] = fRec167_perm[j346];
			}
			for (int j348 = 0; j348 < 4; j348 = faust_wrap_add(j348, 1)) {
				fRec166_tmp[j348] = fRec166_perm[j348];
			}
			for (int j350 = 0; j350 < 4; j350 = faust_wrap_add(j350, 1)) {
				fRec171_tmp[j350] = fRec171_perm[j350];
			}
			for (int j352 = 0; j352 < 4; j352 = faust_wrap_add(j352, 1)) {
				fRec170_tmp[j352] = fRec170_perm[j352];
			}
			for (int j354 = 0; j354 < 4; j354 = faust_wrap_add(j354, 1)) {
				fRec176_tmp[j354] = fRec176_perm[j354];
			}
			for (int j356 = 0; j356 < 4; j356 = faust_wrap_add(j356, 1)) {
				fRec175_tmp[j356] = fRec175_perm[j356];
			}
			for (int j358 = 0; j358 < 4; j358 = faust_wrap_add(j358, 1)) {
				fRec174_tmp[j358] = fRec174_perm[j358];
			}
			for (int j360 = 0; j360 < 4; j360 = faust_wrap_add(j360, 1)) {
				fRec173_tmp[j360] = fRec173_perm[j360];
			}
			for (int j362 = 0; j362 < 4; j362 = faust_wrap_add(j362, 1)) {
				fRec172_tmp[j362] = fRec172_perm[j362];
			}
			for (int j364 = 0; j364 < 4; j364 = faust_wrap_add(j364, 1)) {
				fRec182_tmp[j364] = fRec182_perm[j364];
			}
			for (int j366 = 0; j366 < 4; j366 = faust_wrap_add(j366, 1)) {
				fRec181_tmp[j366] = fRec181_perm[j366];
			}
			for (int j368 = 0; j368 < 4; j368 = faust_wrap_add(j368, 1)) {
				fYec21_tmp[j368] = fYec21_perm[j368];
			}
			for (int j370 = 0; j370 < 4; j370 = faust_wrap_add(j370, 1)) {
				fRec180_tmp[j370] = fRec180_perm[j370];
			}
			for (int j372 = 0; j372 < 4; j372 = faust_wrap_add(j372, 1)) {
				fRec179_tmp[j372] = fRec179_perm[j372];
			}
			for (int j374 = 0; j374 < 4; j374 = faust_wrap_add(j374, 1)) {
				fRec178_tmp[j374] = fRec178_perm[j374];
			}
			for (int j376 = 0; j376 < 4; j376 = faust_wrap_add(j376, 1)) {
				fRec177_tmp[j376] = fRec177_perm[j376];
			}
			for (int j378 = 0; j378 < 4; j378 = faust_wrap_add(j378, 1)) {
				fRec187_tmp[j378] = fRec187_perm[j378];
			}
			for (int j380 = 0; j380 < 4; j380 = faust_wrap_add(j380, 1)) {
				fRec186_tmp[j380] = fRec186_perm[j380];
			}
			for (int j382 = 0; j382 < 4; j382 = faust_wrap_add(j382, 1)) {
				fYec22_tmp[j382] = fYec22_perm[j382];
			}
			for (int j384 = 0; j384 < 4; j384 = faust_wrap_add(j384, 1)) {
				fRec185_tmp[j384] = fRec185_perm[j384];
			}
			for (int j386 = 0; j386 < 4; j386 = faust_wrap_add(j386, 1)) {
				fRec184_tmp[j386] = fRec184_perm[j386];
			}
			for (int j388 = 0; j388 < 4; j388 = faust_wrap_add(j388, 1)) {
				fRec183_tmp[j388] = fRec183_perm[j388];
			}
			for (int j390 = 0; j390 < 4; j390 = faust_wrap_add(j390, 1)) {
				fRec191_tmp[j390] = fRec191_perm[j390];
			}
			for (int j392 = 0; j392 < 4; j392 = faust_wrap_add(j392, 1)) {
				fRec190_tmp[j392] = fRec190_perm[j392];
			}
			for (int j394 = 0; j394 < 4; j394 = faust_wrap_add(j394, 1)) {
				fYec23_tmp[j394] = fYec23_perm[j394];
			}
			for (int j396 = 0; j396 < 4; j396 = faust_wrap_add(j396, 1)) {
				fRec189_tmp[j396] = fRec189_perm[j396];
			}
			for (int j398 = 0; j398 < 4; j398 = faust_wrap_add(j398, 1)) {
				fRec188_tmp[j398] = fRec188_perm[j398];
			}
			for (int j400 = 0; j400 < 4; j400 = faust_wrap_add(j400, 1)) {
				fRec193_tmp[j400] = fRec193_perm[j400];
			}
			for (int j402 = 0; j402 < 4; j402 = faust_wrap_add(j402, 1)) {
				fRec192_tmp[j402] = fRec192_perm[j402];
			}
			for (int j404 = 0; j404 < 4; j404 = faust_wrap_add(j404, 1)) {
				fRec198_tmp[j404] = fRec198_perm[j404];
			}
			for (int j406 = 0; j406 < 4; j406 = faust_wrap_add(j406, 1)) {
				fRec197_tmp[j406] = fRec197_perm[j406];
			}
			for (int j408 = 0; j408 < 4; j408 = faust_wrap_add(j408, 1)) {
				fRec196_tmp[j408] = fRec196_perm[j408];
			}
			for (int j410 = 0; j410 < 4; j410 = faust_wrap_add(j410, 1)) {
				fRec195_tmp[j410] = fRec195_perm[j410];
			}
			for (int j412 = 0; j412 < 4; j412 = faust_wrap_add(j412, 1)) {
				fRec194_tmp[j412] = fRec194_perm[j412];
			}
			for (int j414 = 0; j414 < 4; j414 = faust_wrap_add(j414, 1)) {
				fRec204_tmp[j414] = fRec204_perm[j414];
			}
			for (int j416 = 0; j416 < 4; j416 = faust_wrap_add(j416, 1)) {
				fRec203_tmp[j416] = fRec203_perm[j416];
			}
			for (int j418 = 0; j418 < 4; j418 = faust_wrap_add(j418, 1)) {
				fYec24_tmp[j418] = fYec24_perm[j418];
			}
			for (int j420 = 0; j420 < 4; j420 = faust_wrap_add(j420, 1)) {
				fRec202_tmp[j420] = fRec202_perm[j420];
			}
			for (int j422 = 0; j422 < 4; j422 = faust_wrap_add(j422, 1)) {
				fRec201_tmp[j422] = fRec201_perm[j422];
			}
			for (int j424 = 0; j424 < 4; j424 = faust_wrap_add(j424, 1)) {
				fRec200_tmp[j424] = fRec200_perm[j424];
			}
			for (int j426 = 0; j426 < 4; j426 = faust_wrap_add(j426, 1)) {
				fRec199_tmp[j426] = fRec199_perm[j426];
			}
			for (int j428 = 0; j428 < 4; j428 = faust_wrap_add(j428, 1)) {
				fRec209_tmp[j428] = fRec209_perm[j428];
			}
			for (int j430 = 0; j430 < 4; j430 = faust_wrap_add(j430, 1)) {
				fRec208_tmp[j430] = fRec208_perm[j430];
			}
			for (int j432 = 0; j432 < 4; j432 = faust_wrap_add(j432, 1)) {
				fYec25_tmp[j432] = fYec25_perm[j432];
			}
			for (int j434 = 0; j434 < 4; j434 = faust_wrap_add(j434, 1)) {
				fRec207_tmp[j434] = fRec207_perm[j434];
			}
			for (int j436 = 0; j436 < 4; j436 = faust_wrap_add(j436, 1)) {
				fRec206_tmp[j436] = fRec206_perm[j436];
			}
			for (int j438 = 0; j438 < 4; j438 = faust_wrap_add(j438, 1)) {
				fRec205_tmp[j438] = fRec205_perm[j438];
			}
			for (int j440 = 0; j440 < 4; j440 = faust_wrap_add(j440, 1)) {
				fRec213_tmp[j440] = fRec213_perm[j440];
			}
			for (int j442 = 0; j442 < 4; j442 = faust_wrap_add(j442, 1)) {
				fRec212_tmp[j442] = fRec212_perm[j442];
			}
			for (int j444 = 0; j444 < 4; j444 = faust_wrap_add(j444, 1)) {
				fYec26_tmp[j444] = fYec26_perm[j444];
			}
			for (int j446 = 0; j446 < 4; j446 = faust_wrap_add(j446, 1)) {
				fRec211_tmp[j446] = fRec211_perm[j446];
			}
			for (int j448 = 0; j448 < 4; j448 = faust_wrap_add(j448, 1)) {
				fRec210_tmp[j448] = fRec210_perm[j448];
			}
			for (int j450 = 0; j450 < 4; j450 = faust_wrap_add(j450, 1)) {
				fRec215_tmp[j450] = fRec215_perm[j450];
			}
			for (int j452 = 0; j452 < 4; j452 = faust_wrap_add(j452, 1)) {
				fRec214_tmp[j452] = fRec214_perm[j452];
			}
			for (int j454 = 0; j454 < 4; j454 = faust_wrap_add(j454, 1)) {
				fRec220_tmp[j454] = fRec220_perm[j454];
			}
			for (int j456 = 0; j456 < 4; j456 = faust_wrap_add(j456, 1)) {
				fRec219_tmp[j456] = fRec219_perm[j456];
			}
			for (int j458 = 0; j458 < 4; j458 = faust_wrap_add(j458, 1)) {
				fRec218_tmp[j458] = fRec218_perm[j458];
			}
			for (int j460 = 0; j460 < 4; j460 = faust_wrap_add(j460, 1)) {
				fRec217_tmp[j460] = fRec217_perm[j460];
			}
			for (int j462 = 0; j462 < 4; j462 = faust_wrap_add(j462, 1)) {
				fRec216_tmp[j462] = fRec216_perm[j462];
			}
			for (int j464 = 0; j464 < 4; j464 = faust_wrap_add(j464, 1)) {
				fRec226_tmp[j464] = fRec226_perm[j464];
			}
			for (int j466 = 0; j466 < 4; j466 = faust_wrap_add(j466, 1)) {
				fRec225_tmp[j466] = fRec225_perm[j466];
			}
			for (int j468 = 0; j468 < 4; j468 = faust_wrap_add(j468, 1)) {
				fYec27_tmp[j468] = fYec27_perm[j468];
			}
			for (int j470 = 0; j470 < 4; j470 = faust_wrap_add(j470, 1)) {
				fRec224_tmp[j470] = fRec224_perm[j470];
			}
			for (int j472 = 0; j472 < 4; j472 = faust_wrap_add(j472, 1)) {
				fRec223_tmp[j472] = fRec223_perm[j472];
			}
			for (int j474 = 0; j474 < 4; j474 = faust_wrap_add(j474, 1)) {
				fRec222_tmp[j474] = fRec222_perm[j474];
			}
			for (int j476 = 0; j476 < 4; j476 = faust_wrap_add(j476, 1)) {
				fRec221_tmp[j476] = fRec221_perm[j476];
			}
			for (int j478 = 0; j478 < 4; j478 = faust_wrap_add(j478, 1)) {
				fRec231_tmp[j478] = fRec231_perm[j478];
			}
			for (int j480 = 0; j480 < 4; j480 = faust_wrap_add(j480, 1)) {
				fRec230_tmp[j480] = fRec230_perm[j480];
			}
			for (int j482 = 0; j482 < 4; j482 = faust_wrap_add(j482, 1)) {
				fYec28_tmp[j482] = fYec28_perm[j482];
			}
			for (int j484 = 0; j484 < 4; j484 = faust_wrap_add(j484, 1)) {
				fRec229_tmp[j484] = fRec229_perm[j484];
			}
			for (int j486 = 0; j486 < 4; j486 = faust_wrap_add(j486, 1)) {
				fRec228_tmp[j486] = fRec228_perm[j486];
			}
			for (int j488 = 0; j488 < 4; j488 = faust_wrap_add(j488, 1)) {
				fRec227_tmp[j488] = fRec227_perm[j488];
			}
			for (int j490 = 0; j490 < 4; j490 = faust_wrap_add(j490, 1)) {
				fRec235_tmp[j490] = fRec235_perm[j490];
			}
			for (int j492 = 0; j492 < 4; j492 = faust_wrap_add(j492, 1)) {
				fRec234_tmp[j492] = fRec234_perm[j492];
			}
			for (int j494 = 0; j494 < 4; j494 = faust_wrap_add(j494, 1)) {
				fYec29_tmp[j494] = fYec29_perm[j494];
			}
			for (int j496 = 0; j496 < 4; j496 = faust_wrap_add(j496, 1)) {
				fRec233_tmp[j496] = fRec233_perm[j496];
			}
			for (int j498 = 0; j498 < 4; j498 = faust_wrap_add(j498, 1)) {
				fRec232_tmp[j498] = fRec232_perm[j498];
			}
			for (int j500 = 0; j500 < 4; j500 = faust_wrap_add(j500, 1)) {
				fRec237_tmp[j500] = fRec237_perm[j500];
			}
			for (int j502 = 0; j502 < 4; j502 = faust_wrap_add(j502, 1)) {
				fRec236_tmp[j502] = fRec236_perm[j502];
			}
			for (int j504 = 0; j504 < 4; j504 = faust_wrap_add(j504, 1)) {
				fRec242_tmp[j504] = fRec242_perm[j504];
			}
			for (int j506 = 0; j506 < 4; j506 = faust_wrap_add(j506, 1)) {
				fRec241_tmp[j506] = fRec241_perm[j506];
			}
			for (int j508 = 0; j508 < 4; j508 = faust_wrap_add(j508, 1)) {
				fRec240_tmp[j508] = fRec240_perm[j508];
			}
			for (int j510 = 0; j510 < 4; j510 = faust_wrap_add(j510, 1)) {
				fRec239_tmp[j510] = fRec239_perm[j510];
			}
			for (int j512 = 0; j512 < 4; j512 = faust_wrap_add(j512, 1)) {
				fRec238_tmp[j512] = fRec238_perm[j512];
			}
			for (int j514 = 0; j514 < 4; j514 = faust_wrap_add(j514, 1)) {
				fRec248_tmp[j514] = fRec248_perm[j514];
			}
			for (int j516 = 0; j516 < 4; j516 = faust_wrap_add(j516, 1)) {
				fRec247_tmp[j516] = fRec247_perm[j516];
			}
			for (int j518 = 0; j518 < 4; j518 = faust_wrap_add(j518, 1)) {
				fYec30_tmp[j518] = fYec30_perm[j518];
			}
			for (int j520 = 0; j520 < 4; j520 = faust_wrap_add(j520, 1)) {
				fRec246_tmp[j520] = fRec246_perm[j520];
			}
			for (int j522 = 0; j522 < 4; j522 = faust_wrap_add(j522, 1)) {
				fRec245_tmp[j522] = fRec245_perm[j522];
			}
			for (int j524 = 0; j524 < 4; j524 = faust_wrap_add(j524, 1)) {
				fRec244_tmp[j524] = fRec244_perm[j524];
			}
			for (int j526 = 0; j526 < 4; j526 = faust_wrap_add(j526, 1)) {
				fRec243_tmp[j526] = fRec243_perm[j526];
			}
			for (int j528 = 0; j528 < 4; j528 = faust_wrap_add(j528, 1)) {
				fRec253_tmp[j528] = fRec253_perm[j528];
			}
			for (int j530 = 0; j530 < 4; j530 = faust_wrap_add(j530, 1)) {
				fRec252_tmp[j530] = fRec252_perm[j530];
			}
			for (int j532 = 0; j532 < 4; j532 = faust_wrap_add(j532, 1)) {
				fYec31_tmp[j532] = fYec31_perm[j532];
			}
			for (int j534 = 0; j534 < 4; j534 = faust_wrap_add(j534, 1)) {
				fRec251_tmp[j534] = fRec251_perm[j534];
			}
			for (int j536 = 0; j536 < 4; j536 = faust_wrap_add(j536, 1)) {
				fRec250_tmp[j536] = fRec250_perm[j536];
			}
			for (int j538 = 0; j538 < 4; j538 = faust_wrap_add(j538, 1)) {
				fRec249_tmp[j538] = fRec249_perm[j538];
			}
			for (int j540 = 0; j540 < 4; j540 = faust_wrap_add(j540, 1)) {
				fRec257_tmp[j540] = fRec257_perm[j540];
			}
			for (int j542 = 0; j542 < 4; j542 = faust_wrap_add(j542, 1)) {
				fRec256_tmp[j542] = fRec256_perm[j542];
			}
			for (int j544 = 0; j544 < 4; j544 = faust_wrap_add(j544, 1)) {
				fYec32_tmp[j544] = fYec32_perm[j544];
			}
			for (int j546 = 0; j546 < 4; j546 = faust_wrap_add(j546, 1)) {
				fRec255_tmp[j546] = fRec255_perm[j546];
			}
			for (int j548 = 0; j548 < 4; j548 = faust_wrap_add(j548, 1)) {
				fRec254_tmp[j548] = fRec254_perm[j548];
			}
			for (int j550 = 0; j550 < 4; j550 = faust_wrap_add(j550, 1)) {
				fRec259_tmp[j550] = fRec259_perm[j550];
			}
			for (int j552 = 0; j552 < 4; j552 = faust_wrap_add(j552, 1)) {
				fRec258_tmp[j552] = fRec258_perm[j552];
			}
			for (int j554 = 0; j554 < 4; j554 = faust_wrap_add(j554, 1)) {
				fRec264_tmp[j554] = fRec264_perm[j554];
			}
			for (int j556 = 0; j556 < 4; j556 = faust_wrap_add(j556, 1)) {
				fRec263_tmp[j556] = fRec263_perm[j556];
			}
			for (int j558 = 0; j558 < 4; j558 = faust_wrap_add(j558, 1)) {
				fRec262_tmp[j558] = fRec262_perm[j558];
			}
			for (int j560 = 0; j560 < 4; j560 = faust_wrap_add(j560, 1)) {
				fRec261_tmp[j560] = fRec261_perm[j560];
			}
			for (int j562 = 0; j562 < 4; j562 = faust_wrap_add(j562, 1)) {
				fRec260_tmp[j562] = fRec260_perm[j562];
			}
			for (int j564 = 0; j564 < 4; j564 = faust_wrap_add(j564, 1)) {
				fRec270_tmp[j564] = fRec270_perm[j564];
			}
			for (int j566 = 0; j566 < 4; j566 = faust_wrap_add(j566, 1)) {
				fRec269_tmp[j566] = fRec269_perm[j566];
			}
			for (int j568 = 0; j568 < 4; j568 = faust_wrap_add(j568, 1)) {
				fYec33_tmp[j568] = fYec33_perm[j568];
			}
			for (int j570 = 0; j570 < 4; j570 = faust_wrap_add(j570, 1)) {
				fRec268_tmp[j570] = fRec268_perm[j570];
			}
			for (int j572 = 0; j572 < 4; j572 = faust_wrap_add(j572, 1)) {
				fRec267_tmp[j572] = fRec267_perm[j572];
			}
			for (int j574 = 0; j574 < 4; j574 = faust_wrap_add(j574, 1)) {
				fRec266_tmp[j574] = fRec266_perm[j574];
			}
			for (int j576 = 0; j576 < 4; j576 = faust_wrap_add(j576, 1)) {
				fRec265_tmp[j576] = fRec265_perm[j576];
			}
			for (int j578 = 0; j578 < 4; j578 = faust_wrap_add(j578, 1)) {
				fRec275_tmp[j578] = fRec275_perm[j578];
			}
			for (int j580 = 0; j580 < 4; j580 = faust_wrap_add(j580, 1)) {
				fRec274_tmp[j580] = fRec274_perm[j580];
			}
			for (int j582 = 0; j582 < 4; j582 = faust_wrap_add(j582, 1)) {
				fYec34_tmp[j582] = fYec34_perm[j582];
			}
			for (int j584 = 0; j584 < 4; j584 = faust_wrap_add(j584, 1)) {
				fRec273_tmp[j584] = fRec273_perm[j584];
			}
			for (int j586 = 0; j586 < 4; j586 = faust_wrap_add(j586, 1)) {
				fRec272_tmp[j586] = fRec272_perm[j586];
			}
			for (int j588 = 0; j588 < 4; j588 = faust_wrap_add(j588, 1)) {
				fRec271_tmp[j588] = fRec271_perm[j588];
			}
			for (int j590 = 0; j590 < 4; j590 = faust_wrap_add(j590, 1)) {
				fRec279_tmp[j590] = fRec279_perm[j590];
			}
			for (int j592 = 0; j592 < 4; j592 = faust_wrap_add(j592, 1)) {
				fRec278_tmp[j592] = fRec278_perm[j592];
			}
			for (int j594 = 0; j594 < 4; j594 = faust_wrap_add(j594, 1)) {
				fYec35_tmp[j594] = fYec35_perm[j594];
			}
			for (int j596 = 0; j596 < 4; j596 = faust_wrap_add(j596, 1)) {
				fRec277_tmp[j596] = fRec277_perm[j596];
			}
			for (int j598 = 0; j598 < 4; j598 = faust_wrap_add(j598, 1)) {
				fRec276_tmp[j598] = fRec276_perm[j598];
			}
			for (int j600 = 0; j600 < 4; j600 = faust_wrap_add(j600, 1)) {
				fRec281_tmp[j600] = fRec281_perm[j600];
			}
			for (int j602 = 0; j602 < 4; j602 = faust_wrap_add(j602, 1)) {
				fRec280_tmp[j602] = fRec280_perm[j602];
			}
			for (int j604 = 0; j604 < 4; j604 = faust_wrap_add(j604, 1)) {
				fRec286_tmp[j604] = fRec286_perm[j604];
			}
			for (int j606 = 0; j606 < 4; j606 = faust_wrap_add(j606, 1)) {
				fRec285_tmp[j606] = fRec285_perm[j606];
			}
			for (int j608 = 0; j608 < 4; j608 = faust_wrap_add(j608, 1)) {
				fRec284_tmp[j608] = fRec284_perm[j608];
			}
			for (int j610 = 0; j610 < 4; j610 = faust_wrap_add(j610, 1)) {
				fRec283_tmp[j610] = fRec283_perm[j610];
			}
			for (int j612 = 0; j612 < 4; j612 = faust_wrap_add(j612, 1)) {
				fRec282_tmp[j612] = fRec282_perm[j612];
			}
			for (int j614 = 0; j614 < 4; j614 = faust_wrap_add(j614, 1)) {
				fRec292_tmp[j614] = fRec292_perm[j614];
			}
			for (int j616 = 0; j616 < 4; j616 = faust_wrap_add(j616, 1)) {
				fRec291_tmp[j616] = fRec291_perm[j616];
			}
			for (int j618 = 0; j618 < 4; j618 = faust_wrap_add(j618, 1)) {
				fYec36_tmp[j618] = fYec36_perm[j618];
			}
			for (int j620 = 0; j620 < 4; j620 = faust_wrap_add(j620, 1)) {
				fRec290_tmp[j620] = fRec290_perm[j620];
			}
			for (int j622 = 0; j622 < 4; j622 = faust_wrap_add(j622, 1)) {
				fRec289_tmp[j622] = fRec289_perm[j622];
			}
			for (int j624 = 0; j624 < 4; j624 = faust_wrap_add(j624, 1)) {
				fRec288_tmp[j624] = fRec288_perm[j624];
			}
			for (int j626 = 0; j626 < 4; j626 = faust_wrap_add(j626, 1)) {
				fRec287_tmp[j626] = fRec287_perm[j626];
			}
			for (int j628 = 0; j628 < 4; j628 = faust_wrap_add(j628, 1)) {
				fRec297_tmp[j628] = fRec297_perm[j628];
			}
			for (int j630 = 0; j630 < 4; j630 = faust_wrap_add(j630, 1)) {
				fRec296_tmp[j630] = fRec296_perm[j630];
			}
			for (int j632 = 0; j632 < 4; j632 = faust_wrap_add(j632, 1)) {
				fYec37_tmp[j632] = fYec37_perm[j632];
			}
			for (int j634 = 0; j634 < 4; j634 = faust_wrap_add(j634, 1)) {
				fRec295_tmp[j634] = fRec295_perm[j634];
			}
			for (int j636 = 0; j636 < 4; j636 = faust_wrap_add(j636, 1)) {
				fRec294_tmp[j636] = fRec294_perm[j636];
			}
			for (int j638 = 0; j638 < 4; j638 = faust_wrap_add(j638, 1)) {
				fRec293_tmp[j638] = fRec293_perm[j638];
			}
			for (int j640 = 0; j640 < 4; j640 = faust_wrap_add(j640, 1)) {
				fRec301_tmp[j640] = fRec301_perm[j640];
			}
			for (int j642 = 0; j642 < 4; j642 = faust_wrap_add(j642, 1)) {
				fRec300_tmp[j642] = fRec300_perm[j642];
			}
			for (int j644 = 0; j644 < 4; j644 = faust_wrap_add(j644, 1)) {
				fYec38_tmp[j644] = fYec38_perm[j644];
			}
			for (int j646 = 0; j646 < 4; j646 = faust_wrap_add(j646, 1)) {
				fRec299_tmp[j646] = fRec299_perm[j646];
			}
			for (int j648 = 0; j648 < 4; j648 = faust_wrap_add(j648, 1)) {
				fRec298_tmp[j648] = fRec298_perm[j648];
			}
			for (int j650 = 0; j650 < 4; j650 = faust_wrap_add(j650, 1)) {
				fRec303_tmp[j650] = fRec303_perm[j650];
			}
			for (int j652 = 0; j652 < 4; j652 = faust_wrap_add(j652, 1)) {
				fRec302_tmp[j652] = fRec302_perm[j652];
			}
			for (int j654 = 0; j654 < 4; j654 = faust_wrap_add(j654, 1)) {
				fRec308_tmp[j654] = fRec308_perm[j654];
			}
			for (int j656 = 0; j656 < 4; j656 = faust_wrap_add(j656, 1)) {
				fRec307_tmp[j656] = fRec307_perm[j656];
			}
			for (int j658 = 0; j658 < 4; j658 = faust_wrap_add(j658, 1)) {
				fRec306_tmp[j658] = fRec306_perm[j658];
			}
			for (int j660 = 0; j660 < 4; j660 = faust_wrap_add(j660, 1)) {
				fRec305_tmp[j660] = fRec305_perm[j660];
			}
			for (int j662 = 0; j662 < 4; j662 = faust_wrap_add(j662, 1)) {
				fRec304_tmp[j662] = fRec304_perm[j662];
			}
			for (int j664 = 0; j664 < 4; j664 = faust_wrap_add(j664, 1)) {
				fRec314_tmp[j664] = fRec314_perm[j664];
			}
			for (int j666 = 0; j666 < 4; j666 = faust_wrap_add(j666, 1)) {
				fRec313_tmp[j666] = fRec313_perm[j666];
			}
			for (int j668 = 0; j668 < 4; j668 = faust_wrap_add(j668, 1)) {
				fYec39_tmp[j668] = fYec39_perm[j668];
			}
			for (int j670 = 0; j670 < 4; j670 = faust_wrap_add(j670, 1)) {
				fRec312_tmp[j670] = fRec312_perm[j670];
			}
			for (int j672 = 0; j672 < 4; j672 = faust_wrap_add(j672, 1)) {
				fRec311_tmp[j672] = fRec311_perm[j672];
			}
			for (int j674 = 0; j674 < 4; j674 = faust_wrap_add(j674, 1)) {
				fRec310_tmp[j674] = fRec310_perm[j674];
			}
			for (int j676 = 0; j676 < 4; j676 = faust_wrap_add(j676, 1)) {
				fRec309_tmp[j676] = fRec309_perm[j676];
			}
			for (int j678 = 0; j678 < 4; j678 = faust_wrap_add(j678, 1)) {
				fRec319_tmp[j678] = fRec319_perm[j678];
			}
			for (int j680 = 0; j680 < 4; j680 = faust_wrap_add(j680, 1)) {
				fRec318_tmp[j680] = fRec318_perm[j680];
			}
			for (int j682 = 0; j682 < 4; j682 = faust_wrap_add(j682, 1)) {
				fYec40_tmp[j682] = fYec40_perm[j682];
			}
			for (int j684 = 0; j684 < 4; j684 = faust_wrap_add(j684, 1)) {
				fRec317_tmp[j684] = fRec317_perm[j684];
			}
			for (int j686 = 0; j686 < 4; j686 = faust_wrap_add(j686, 1)) {
				fRec316_tmp[j686] = fRec316_perm[j686];
			}
			for (int j688 = 0; j688 < 4; j688 = faust_wrap_add(j688, 1)) {
				fRec315_tmp[j688] = fRec315_perm[j688];
			}
			for (int j690 = 0; j690 < 4; j690 = faust_wrap_add(j690, 1)) {
				fRec323_tmp[j690] = fRec323_perm[j690];
			}
			for (int j692 = 0; j692 < 4; j692 = faust_wrap_add(j692, 1)) {
				fRec322_tmp[j692] = fRec322_perm[j692];
			}
			for (int j694 = 0; j694 < 4; j694 = faust_wrap_add(j694, 1)) {
				fYec41_tmp[j694] = fYec41_perm[j694];
			}
			for (int j696 = 0; j696 < 4; j696 = faust_wrap_add(j696, 1)) {
				fRec321_tmp[j696] = fRec321_perm[j696];
			}
			for (int j698 = 0; j698 < 4; j698 = faust_wrap_add(j698, 1)) {
				fRec320_tmp[j698] = fRec320_perm[j698];
			}
			for (int j700 = 0; j700 < 4; j700 = faust_wrap_add(j700, 1)) {
				fRec325_tmp[j700] = fRec325_perm[j700];
			}
			for (int j702 = 0; j702 < 4; j702 = faust_wrap_add(j702, 1)) {
				fRec324_tmp[j702] = fRec324_perm[j702];
			}
			for (int j704 = 0; j704 < 4; j704 = faust_wrap_add(j704, 1)) {
				fRec330_tmp[j704] = fRec330_perm[j704];
			}
			for (int j706 = 0; j706 < 4; j706 = faust_wrap_add(j706, 1)) {
				fRec329_tmp[j706] = fRec329_perm[j706];
			}
			for (int j708 = 0; j708 < 4; j708 = faust_wrap_add(j708, 1)) {
				fRec328_tmp[j708] = fRec328_perm[j708];
			}
			for (int j710 = 0; j710 < 4; j710 = faust_wrap_add(j710, 1)) {
				fRec327_tmp[j710] = fRec327_perm[j710];
			}
			for (int j712 = 0; j712 < 4; j712 = faust_wrap_add(j712, 1)) {
				fRec326_tmp[j712] = fRec326_perm[j712];
			}
			for (int j714 = 0; j714 < 4; j714 = faust_wrap_add(j714, 1)) {
				fRec336_tmp[j714] = fRec336_perm[j714];
			}
			for (int j716 = 0; j716 < 4; j716 = faust_wrap_add(j716, 1)) {
				fRec335_tmp[j716] = fRec335_perm[j716];
			}
			for (int j718 = 0; j718 < 4; j718 = faust_wrap_add(j718, 1)) {
				fYec42_tmp[j718] = fYec42_perm[j718];
			}
			for (int j720 = 0; j720 < 4; j720 = faust_wrap_add(j720, 1)) {
				fRec334_tmp[j720] = fRec334_perm[j720];
			}
			for (int j722 = 0; j722 < 4; j722 = faust_wrap_add(j722, 1)) {
				fRec333_tmp[j722] = fRec333_perm[j722];
			}
			for (int j724 = 0; j724 < 4; j724 = faust_wrap_add(j724, 1)) {
				fRec332_tmp[j724] = fRec332_perm[j724];
			}
			for (int j726 = 0; j726 < 4; j726 = faust_wrap_add(j726, 1)) {
				fRec331_tmp[j726] = fRec331_perm[j726];
			}
			for (int j728 = 0; j728 < 4; j728 = faust_wrap_add(j728, 1)) {
				fRec341_tmp[j728] = fRec341_perm[j728];
			}
			for (int j730 = 0; j730 < 4; j730 = faust_wrap_add(j730, 1)) {
				fRec340_tmp[j730] = fRec340_perm[j730];
			}
			for (int j732 = 0; j732 < 4; j732 = faust_wrap_add(j732, 1)) {
				fYec43_tmp[j732] = fYec43_perm[j732];
			}
			for (int j734 = 0; j734 < 4; j734 = faust_wrap_add(j734, 1)) {
				fRec339_tmp[j734] = fRec339_perm[j734];
			}
			for (int j736 = 0; j736 < 4; j736 = faust_wrap_add(j736, 1)) {
				fRec338_tmp[j736] = fRec338_perm[j736];
			}
			for (int j738 = 0; j738 < 4; j738 = faust_wrap_add(j738, 1)) {
				fRec337_tmp[j738] = fRec337_perm[j738];
			}
			for (int j740 = 0; j740 < 4; j740 = faust_wrap_add(j740, 1)) {
				fRec345_tmp[j740] = fRec345_perm[j740];
			}
			for (int j742 = 0; j742 < 4; j742 = faust_wrap_add(j742, 1)) {
				fRec344_tmp[j742] = fRec344_perm[j742];
			}
			for (int j744 = 0; j744 < 4; j744 = faust_wrap_add(j744, 1)) {
				fYec44_tmp[j744] = fYec44_perm[j744];
			}
			for (int j746 = 0; j746 < 4; j746 = faust_wrap_add(j746, 1)) {
				fRec343_tmp[j746] = fRec343_perm[j746];
			}
			for (int j748 = 0; j748 < 4; j748 = faust_wrap_add(j748, 1)) {
				fRec342_tmp[j748] = fRec342_perm[j748];
			}
			for (int j750 = 0; j750 < 4; j750 = faust_wrap_add(j750, 1)) {
				fRec347_tmp[j750] = fRec347_perm[j750];
			}
			for (int j752 = 0; j752 < 4; j752 = faust_wrap_add(j752, 1)) {
				fRec346_tmp[j752] = fRec346_perm[j752];
			}
			for (int j754 = 0; j754 < 4; j754 = faust_wrap_add(j754, 1)) {
				fRec352_tmp[j754] = fRec352_perm[j754];
			}
			for (int j756 = 0; j756 < 4; j756 = faust_wrap_add(j756, 1)) {
				fRec351_tmp[j756] = fRec351_perm[j756];
			}
			for (int j758 = 0; j758 < 4; j758 = faust_wrap_add(j758, 1)) {
				fRec350_tmp[j758] = fRec350_perm[j758];
			}
			for (int j760 = 0; j760 < 4; j760 = faust_wrap_add(j760, 1)) {
				fRec349_tmp[j760] = fRec349_perm[j760];
			}
			for (int j762 = 0; j762 < 4; j762 = faust_wrap_add(j762, 1)) {
				fRec348_tmp[j762] = fRec348_perm[j762];
			}
			for (int j764 = 0; j764 < 4; j764 = faust_wrap_add(j764, 1)) {
				fRec358_tmp[j764] = fRec358_perm[j764];
			}
			for (int j766 = 0; j766 < 4; j766 = faust_wrap_add(j766, 1)) {
				fRec357_tmp[j766] = fRec357_perm[j766];
			}
			for (int j768 = 0; j768 < 4; j768 = faust_wrap_add(j768, 1)) {
				fYec45_tmp[j768] = fYec45_perm[j768];
			}
			for (int j770 = 0; j770 < 4; j770 = faust_wrap_add(j770, 1)) {
				fRec356_tmp[j770] = fRec356_perm[j770];
			}
			for (int j772 = 0; j772 < 4; j772 = faust_wrap_add(j772, 1)) {
				fRec355_tmp[j772] = fRec355_perm[j772];
			}
			for (int j774 = 0; j774 < 4; j774 = faust_wrap_add(j774, 1)) {
				fRec354_tmp[j774] = fRec354_perm[j774];
			}
			for (int j776 = 0; j776 < 4; j776 = faust_wrap_add(j776, 1)) {
				fRec353_tmp[j776] = fRec353_perm[j776];
			}
			for (int j778 = 0; j778 < 4; j778 = faust_wrap_add(j778, 1)) {
				fRec363_tmp[j778] = fRec363_perm[j778];
			}
			for (int j780 = 0; j780 < 4; j780 = faust_wrap_add(j780, 1)) {
				fRec362_tmp[j780] = fRec362_perm[j780];
			}
			for (int j782 = 0; j782 < 4; j782 = faust_wrap_add(j782, 1)) {
				fYec46_tmp[j782] = fYec46_perm[j782];
			}
			for (int j784 = 0; j784 < 4; j784 = faust_wrap_add(j784, 1)) {
				fRec361_tmp[j784] = fRec361_perm[j784];
			}
			for (int j786 = 0; j786 < 4; j786 = faust_wrap_add(j786, 1)) {
				fRec360_tmp[j786] = fRec360_perm[j786];
			}
			for (int j788 = 0; j788 < 4; j788 = faust_wrap_add(j788, 1)) {
				fRec359_tmp[j788] = fRec359_perm[j788];
			}
			for (int j790 = 0; j790 < 4; j790 = faust_wrap_add(j790, 1)) {
				fRec367_tmp[j790] = fRec367_perm[j790];
			}
			for (int j792 = 0; j792 < 4; j792 = faust_wrap_add(j792, 1)) {
				fRec366_tmp[j792] = fRec366_perm[j792];
			}
			for (int j794 = 0; j794 < 4; j794 = faust_wrap_add(j794, 1)) {
				fYec47_tmp[j794] = fYec47_perm[j794];
			}
			for (int j796 = 0; j796 < 4; j796 = faust_wrap_add(j796, 1)) {
				fRec365_tmp[j796] = fRec365_perm[j796];
			}
			for (int j798 = 0; j798 < 4; j798 = faust_wrap_add(j798, 1)) {
				fRec364_tmp[j798] = fRec364_perm[j798];
			}
			for (int j800 = 0; j800 < 4; j800 = faust_wrap_add(j800, 1)) {
				fRec369_tmp[j800] = fRec369_perm[j800];
			}
			for (int j802 = 0; j802 < 4; j802 = faust_wrap_add(j802, 1)) {
				fRec368_tmp[j802] = fRec368_perm[j802];
			}
			fYec48_idx = (faust_wrap_add(fYec48_idx, fYec48_idx_save)) & 16383;
			for (int j808 = 0; j808 < 4; j808 = faust_wrap_add(j808, 1)) {
				fRec0_tmp[j808] = fRec0_perm[j808];
			}
			fYec49_idx = (faust_wrap_add(fYec49_idx, fYec49_idx_save)) & 16383;
			for (int j812 = 0; j812 < 4; j812 = faust_wrap_add(j812, 1)) {
				fRec1_tmp[j812] = fRec1_perm[j812];
			}
			fYec50_idx = (faust_wrap_add(fYec50_idx, fYec50_idx_save)) & 16383;
			for (int j814 = 0; j814 < 4; j814 = faust_wrap_add(j814, 1)) {
				fRec2_tmp[j814] = fRec2_perm[j814];
			}
			fYec51_idx = (faust_wrap_add(fYec51_idx, fYec51_idx_save)) & 16383;
			for (int j816 = 0; j816 < 4; j816 = faust_wrap_add(j816, 1)) {
				fRec3_tmp[j816] = fRec3_perm[j816];
			}
			fYec52_idx = (faust_wrap_add(fYec52_idx, fYec52_idx_save)) & 16383;
			for (int j818 = 0; j818 < 4; j818 = faust_wrap_add(j818, 1)) {
				fRec4_tmp[j818] = fRec4_perm[j818];
			}
			fYec53_idx = (faust_wrap_add(fYec53_idx, fYec53_idx_save)) & 16383;
			for (int j820 = 0; j820 < 4; j820 = faust_wrap_add(j820, 1)) {
				fRec5_tmp[j820] = fRec5_perm[j820];
			}
			fYec54_idx = (faust_wrap_add(fYec54_idx, fYec54_idx_save)) & 16383;
			for (int j822 = 0; j822 < 4; j822 = faust_wrap_add(j822, 1)) {
				fRec6_tmp[j822] = fRec6_perm[j822];
			}
			fYec55_idx = (faust_wrap_add(fYec55_idx, fYec55_idx_save)) & 16383;
			for (int j824 = 0; j824 < 4; j824 = faust_wrap_add(j824, 1)) {
				fRec7_tmp[j824] = fRec7_perm[j824];
			}
			fYec56_idx = (faust_wrap_add(fYec56_idx, fYec56_idx_save)) & 16383;
			for (int j826 = 0; j826 < 4; j826 = faust_wrap_add(j826, 1)) {
				fRec8_tmp[j826] = fRec8_perm[j826];
			}
			fYec57_idx = (faust_wrap_add(fYec57_idx, fYec57_idx_save)) & 16383;
			for (int j828 = 0; j828 < 4; j828 = faust_wrap_add(j828, 1)) {
				fRec9_tmp[j828] = fRec9_perm[j828];
			}
			fYec58_idx = (faust_wrap_add(fYec58_idx, fYec58_idx_save)) & 16383;
			for (int j830 = 0; j830 < 4; j830 = faust_wrap_add(j830, 1)) {
				fRec10_tmp[j830] = fRec10_perm[j830];
			}
			fYec59_idx = (faust_wrap_add(fYec59_idx, fYec59_idx_save)) & 16383;
			for (int j832 = 0; j832 < 4; j832 = faust_wrap_add(j832, 1)) {
				fRec11_tmp[j832] = fRec11_perm[j832];
			}
			fYec60_idx = (faust_wrap_add(fYec60_idx, fYec60_idx_save)) & 16383;
			for (int j834 = 0; j834 < 4; j834 = faust_wrap_add(j834, 1)) {
				fRec12_tmp[j834] = fRec12_perm[j834];
			}
			fYec61_idx = (faust_wrap_add(fYec61_idx, fYec61_idx_save)) & 16383;
			for (int j836 = 0; j836 < 4; j836 = faust_wrap_add(j836, 1)) {
				fRec13_tmp[j836] = fRec13_perm[j836];
			}
			fYec62_idx = (faust_wrap_add(fYec62_idx, fYec62_idx_save)) & 16383;
			for (int j838 = 0; j838 < 4; j838 = faust_wrap_add(j838, 1)) {
				fRec14_tmp[j838] = fRec14_perm[j838];
			}
			fYec63_idx = (faust_wrap_add(fYec63_idx, fYec63_idx_save)) & 16383;
			for (int j840 = 0; j840 < 4; j840 = faust_wrap_add(j840, 1)) {
				fRec15_tmp[j840] = fRec15_perm[j840];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = -(fSlow2 * (fSlow3 * fRec22[faust_wrap_sub(i, 1)] - fSlow1 * (fRec0[faust_wrap_sub(i, 1)] - fRec0[faust_wrap_sub(i, 2)])));
				fRec21[i] = fRec22[i] - fSlow5 * (fSlow6 * fRec21[faust_wrap_sub(i, 2)] + fSlow8 * fRec21[faust_wrap_sub(i, 1)]);
				fZec0[i] = fSlow17 * fRec20[faust_wrap_sub(i, 1)];
				fRec20[i] = fSlow9 * (fRec21[faust_wrap_sub(i, 2)] + (fRec21[i] - 2.0 * fRec21[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec20[faust_wrap_sub(i, 2)] + fZec0[i]);
				fZec1[i] = fSlow25 * fRec19[faust_wrap_sub(i, 1)];
				fRec19[i] = fRec20[faust_wrap_sub(i, 2)] + fSlow13 * (fZec0[i] + fSlow15 * fRec20[i]) - fSlow21 * (fSlow23 * fRec19[faust_wrap_sub(i, 2)] + fZec1[i]);
				fZec2[i] = fSlow33 * fRec18[faust_wrap_sub(i, 1)];
				fRec18[i] = fRec19[faust_wrap_sub(i, 2)] + fSlow21 * (fZec1[i] + fSlow23 * fRec19[i]) - fSlow29 * (fSlow31 * fRec18[faust_wrap_sub(i, 2)] + fZec2[i]);
				fRec28[i] = -(fSlow2 * (fSlow3 * fRec28[faust_wrap_sub(i, 1)] - (fRec0[faust_wrap_sub(i, 1)] + fRec0[faust_wrap_sub(i, 2)])));
				fRec27[i] = fRec28[i] - fSlow5 * (fSlow6 * fRec27[faust_wrap_sub(i, 2)] + fSlow8 * fRec27[faust_wrap_sub(i, 1)]);
				fYec0[i] = fSlow5 * (fRec27[faust_wrap_sub(i, 2)] + fRec27[i] + 2.0 * fRec27[faust_wrap_sub(i, 1)]);
				fRec26[i] = -(fSlow34 * (fSlow14 * fRec26[faust_wrap_sub(i, 1)] - fSlow11 * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)])));
				fRec25[i] = fRec26[i] - fSlow36 * (fSlow37 * fRec25[faust_wrap_sub(i, 2)] + fSlow17 * fRec25[faust_wrap_sub(i, 1)]);
				fZec3[i] = fSlow25 * fRec24[faust_wrap_sub(i, 1)];
				fRec24[i] = fSlow38 * (fRec25[faust_wrap_sub(i, 2)] + (fRec25[i] - 2.0 * fRec25[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec24[faust_wrap_sub(i, 2)] + fZec3[i]);
				fZec4[i] = fSlow33 * fRec23[faust_wrap_sub(i, 1)];
				fRec23[i] = fRec24[faust_wrap_sub(i, 2)] + fSlow21 * (fZec3[i] + fSlow23 * fRec24[i]) - fSlow29 * (fSlow31 * fRec23[faust_wrap_sub(i, 2)] + fZec4[i]);
				fRec33[i] = -(fSlow34 * (fSlow14 * fRec33[faust_wrap_sub(i, 1)] - (fYec0[i] + fYec0[faust_wrap_sub(i, 1)])));
				fRec32[i] = fRec33[i] - fSlow36 * (fSlow37 * fRec32[faust_wrap_sub(i, 2)] + fSlow17 * fRec32[faust_wrap_sub(i, 1)]);
				fYec1[i] = fSlow36 * (fRec32[faust_wrap_sub(i, 2)] + fRec32[i] + 2.0 * fRec32[faust_wrap_sub(i, 1)]);
				fRec31[i] = -(fSlow39 * (fSlow22 * fRec31[faust_wrap_sub(i, 1)] - fSlow19 * (fYec1[i] - fYec1[faust_wrap_sub(i, 1)])));
				fRec30[i] = fRec31[i] - fSlow41 * (fSlow42 * fRec30[faust_wrap_sub(i, 2)] + fSlow25 * fRec30[faust_wrap_sub(i, 1)]);
				fZec5[i] = fSlow33 * fRec29[faust_wrap_sub(i, 1)];
				fRec29[i] = fSlow43 * (fRec30[faust_wrap_sub(i, 2)] + (fRec30[i] - 2.0 * fRec30[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec29[faust_wrap_sub(i, 2)] + fZec5[i]);
				fRec37[i] = -(fSlow39 * (fSlow22 * fRec37[faust_wrap_sub(i, 1)] - (fYec1[i] + fYec1[faust_wrap_sub(i, 1)])));
				fRec36[i] = fRec37[i] - fSlow41 * (fSlow42 * fRec36[faust_wrap_sub(i, 2)] + fSlow25 * fRec36[faust_wrap_sub(i, 1)]);
				fYec2[i] = fSlow41 * (fRec36[faust_wrap_sub(i, 2)] + fRec36[i] + 2.0 * fRec36[faust_wrap_sub(i, 1)]);
				fRec35[i] = -(fSlow44 * (fSlow30 * fRec35[faust_wrap_sub(i, 1)] - fSlow27 * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)])));
				fRec34[i] = fRec35[i] - fSlow45 * (fSlow46 * fRec34[faust_wrap_sub(i, 2)] + fSlow33 * fRec34[faust_wrap_sub(i, 1)]);
				fRec39[i] = -(fSlow44 * (fSlow30 * fRec39[faust_wrap_sub(i, 1)] - (fYec2[i] + fYec2[faust_wrap_sub(i, 1)])));
				fRec38[i] = fRec39[i] - fSlow45 * (fSlow46 * fRec38[faust_wrap_sub(i, 2)] + fSlow33 * fRec38[faust_wrap_sub(i, 1)]);
				fRec44[i] = -(fSlow2 * (fSlow3 * fRec44[faust_wrap_sub(i, 1)] - fSlow1 * (fRec8[faust_wrap_sub(i, 1)] - fRec8[faust_wrap_sub(i, 2)])));
				fRec43[i] = fRec44[i] - fSlow5 * (fSlow6 * fRec43[faust_wrap_sub(i, 2)] + fSlow8 * fRec43[faust_wrap_sub(i, 1)]);
				fZec6[i] = fSlow17 * fRec42[faust_wrap_sub(i, 1)];
				fRec42[i] = fSlow9 * (fRec43[faust_wrap_sub(i, 2)] + (fRec43[i] - 2.0 * fRec43[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec42[faust_wrap_sub(i, 2)] + fZec6[i]);
				fZec7[i] = fSlow25 * fRec41[faust_wrap_sub(i, 1)];
				fRec41[i] = fRec42[faust_wrap_sub(i, 2)] + fSlow13 * (fZec6[i] + fSlow15 * fRec42[i]) - fSlow21 * (fSlow23 * fRec41[faust_wrap_sub(i, 2)] + fZec7[i]);
				fZec8[i] = fSlow33 * fRec40[faust_wrap_sub(i, 1)];
				fRec40[i] = fRec41[faust_wrap_sub(i, 2)] + fSlow21 * (fZec7[i] + fSlow23 * fRec41[i]) - fSlow29 * (fSlow31 * fRec40[faust_wrap_sub(i, 2)] + fZec8[i]);
				fRec50[i] = -(fSlow2 * (fSlow3 * fRec50[faust_wrap_sub(i, 1)] - (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)])));
				fRec49[i] = fRec50[i] - fSlow5 * (fSlow6 * fRec49[faust_wrap_sub(i, 2)] + fSlow8 * fRec49[faust_wrap_sub(i, 1)]);
				fYec3[i] = fSlow5 * (fRec49[faust_wrap_sub(i, 2)] + fRec49[i] + 2.0 * fRec49[faust_wrap_sub(i, 1)]);
				fRec48[i] = -(fSlow34 * (fSlow14 * fRec48[faust_wrap_sub(i, 1)] - fSlow11 * (fYec3[i] - fYec3[faust_wrap_sub(i, 1)])));
				fRec47[i] = fRec48[i] - fSlow36 * (fSlow37 * fRec47[faust_wrap_sub(i, 2)] + fSlow17 * fRec47[faust_wrap_sub(i, 1)]);
				fZec9[i] = fSlow25 * fRec46[faust_wrap_sub(i, 1)];
				fRec46[i] = fSlow38 * (fRec47[faust_wrap_sub(i, 2)] + (fRec47[i] - 2.0 * fRec47[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec46[faust_wrap_sub(i, 2)] + fZec9[i]);
				fZec10[i] = fSlow33 * fRec45[faust_wrap_sub(i, 1)];
				fRec45[i] = fRec46[faust_wrap_sub(i, 2)] + fSlow21 * (fZec9[i] + fSlow23 * fRec46[i]) - fSlow29 * (fSlow31 * fRec45[faust_wrap_sub(i, 2)] + fZec10[i]);
				fRec55[i] = -(fSlow34 * (fSlow14 * fRec55[faust_wrap_sub(i, 1)] - (fYec3[i] + fYec3[faust_wrap_sub(i, 1)])));
				fRec54[i] = fRec55[i] - fSlow36 * (fSlow37 * fRec54[faust_wrap_sub(i, 2)] + fSlow17 * fRec54[faust_wrap_sub(i, 1)]);
				fYec4[i] = fSlow36 * (fRec54[faust_wrap_sub(i, 2)] + fRec54[i] + 2.0 * fRec54[faust_wrap_sub(i, 1)]);
				fRec53[i] = -(fSlow39 * (fSlow22 * fRec53[faust_wrap_sub(i, 1)] - fSlow19 * (fYec4[i] - fYec4[faust_wrap_sub(i, 1)])));
				fRec52[i] = fRec53[i] - fSlow41 * (fSlow42 * fRec52[faust_wrap_sub(i, 2)] + fSlow25 * fRec52[faust_wrap_sub(i, 1)]);
				fZec11[i] = fSlow33 * fRec51[faust_wrap_sub(i, 1)];
				fRec51[i] = fSlow43 * (fRec52[faust_wrap_sub(i, 2)] + (fRec52[i] - 2.0 * fRec52[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec51[faust_wrap_sub(i, 2)] + fZec11[i]);
				fRec59[i] = -(fSlow39 * (fSlow22 * fRec59[faust_wrap_sub(i, 1)] - (fYec4[i] + fYec4[faust_wrap_sub(i, 1)])));
				fRec58[i] = fRec59[i] - fSlow41 * (fSlow42 * fRec58[faust_wrap_sub(i, 2)] + fSlow25 * fRec58[faust_wrap_sub(i, 1)]);
				fYec5[i] = fSlow41 * (fRec58[faust_wrap_sub(i, 2)] + fRec58[i] + 2.0 * fRec58[faust_wrap_sub(i, 1)]);
				fRec57[i] = -(fSlow44 * (fSlow30 * fRec57[faust_wrap_sub(i, 1)] - fSlow27 * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)])));
				fRec56[i] = fRec57[i] - fSlow45 * (fSlow46 * fRec56[faust_wrap_sub(i, 2)] + fSlow33 * fRec56[faust_wrap_sub(i, 1)]);
				fRec61[i] = -(fSlow44 * (fSlow30 * fRec61[faust_wrap_sub(i, 1)] - (fYec5[i] + fYec5[faust_wrap_sub(i, 1)])));
				fRec60[i] = fRec61[i] - fSlow45 * (fSlow46 * fRec60[faust_wrap_sub(i, 2)] + fSlow33 * fRec60[faust_wrap_sub(i, 1)]);
				fRec66[i] = -(fSlow2 * (fSlow3 * fRec66[faust_wrap_sub(i, 1)] - fSlow1 * (fRec4[faust_wrap_sub(i, 1)] - fRec4[faust_wrap_sub(i, 2)])));
				fRec65[i] = fRec66[i] - fSlow5 * (fSlow6 * fRec65[faust_wrap_sub(i, 2)] + fSlow8 * fRec65[faust_wrap_sub(i, 1)]);
				fZec12[i] = fSlow17 * fRec64[faust_wrap_sub(i, 1)];
				fRec64[i] = fSlow9 * (fRec65[faust_wrap_sub(i, 2)] + (fRec65[i] - 2.0 * fRec65[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec64[faust_wrap_sub(i, 2)] + fZec12[i]);
				fZec13[i] = fSlow25 * fRec63[faust_wrap_sub(i, 1)];
				fRec63[i] = fRec64[faust_wrap_sub(i, 2)] + fSlow13 * (fZec12[i] + fSlow15 * fRec64[i]) - fSlow21 * (fSlow23 * fRec63[faust_wrap_sub(i, 2)] + fZec13[i]);
				fZec14[i] = fSlow33 * fRec62[faust_wrap_sub(i, 1)];
				fRec62[i] = fRec63[faust_wrap_sub(i, 2)] + fSlow21 * (fZec13[i] + fSlow23 * fRec63[i]) - fSlow29 * (fSlow31 * fRec62[faust_wrap_sub(i, 2)] + fZec14[i]);
				fRec72[i] = -(fSlow2 * (fSlow3 * fRec72[faust_wrap_sub(i, 1)] - (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)])));
				fRec71[i] = fRec72[i] - fSlow5 * (fSlow6 * fRec71[faust_wrap_sub(i, 2)] + fSlow8 * fRec71[faust_wrap_sub(i, 1)]);
				fYec6[i] = fSlow5 * (fRec71[faust_wrap_sub(i, 2)] + fRec71[i] + 2.0 * fRec71[faust_wrap_sub(i, 1)]);
				fRec70[i] = -(fSlow34 * (fSlow14 * fRec70[faust_wrap_sub(i, 1)] - fSlow11 * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)])));
				fRec69[i] = fRec70[i] - fSlow36 * (fSlow37 * fRec69[faust_wrap_sub(i, 2)] + fSlow17 * fRec69[faust_wrap_sub(i, 1)]);
				fZec15[i] = fSlow25 * fRec68[faust_wrap_sub(i, 1)];
				fRec68[i] = fSlow38 * (fRec69[faust_wrap_sub(i, 2)] + (fRec69[i] - 2.0 * fRec69[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec68[faust_wrap_sub(i, 2)] + fZec15[i]);
				fZec16[i] = fSlow33 * fRec67[faust_wrap_sub(i, 1)];
				fRec67[i] = fRec68[faust_wrap_sub(i, 2)] + fSlow21 * (fZec15[i] + fSlow23 * fRec68[i]) - fSlow29 * (fSlow31 * fRec67[faust_wrap_sub(i, 2)] + fZec16[i]);
				fRec77[i] = -(fSlow34 * (fSlow14 * fRec77[faust_wrap_sub(i, 1)] - (fYec6[i] + fYec6[faust_wrap_sub(i, 1)])));
				fRec76[i] = fRec77[i] - fSlow36 * (fSlow37 * fRec76[faust_wrap_sub(i, 2)] + fSlow17 * fRec76[faust_wrap_sub(i, 1)]);
				fYec7[i] = fSlow36 * (fRec76[faust_wrap_sub(i, 2)] + fRec76[i] + 2.0 * fRec76[faust_wrap_sub(i, 1)]);
				fRec75[i] = -(fSlow39 * (fSlow22 * fRec75[faust_wrap_sub(i, 1)] - fSlow19 * (fYec7[i] - fYec7[faust_wrap_sub(i, 1)])));
				fRec74[i] = fRec75[i] - fSlow41 * (fSlow42 * fRec74[faust_wrap_sub(i, 2)] + fSlow25 * fRec74[faust_wrap_sub(i, 1)]);
				fZec17[i] = fSlow33 * fRec73[faust_wrap_sub(i, 1)];
				fRec73[i] = fSlow43 * (fRec74[faust_wrap_sub(i, 2)] + (fRec74[i] - 2.0 * fRec74[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec73[faust_wrap_sub(i, 2)] + fZec17[i]);
				fRec81[i] = -(fSlow39 * (fSlow22 * fRec81[faust_wrap_sub(i, 1)] - (fYec7[i] + fYec7[faust_wrap_sub(i, 1)])));
				fRec80[i] = fRec81[i] - fSlow41 * (fSlow42 * fRec80[faust_wrap_sub(i, 2)] + fSlow25 * fRec80[faust_wrap_sub(i, 1)]);
				fYec8[i] = fSlow41 * (fRec80[faust_wrap_sub(i, 2)] + fRec80[i] + 2.0 * fRec80[faust_wrap_sub(i, 1)]);
				fRec79[i] = -(fSlow44 * (fSlow30 * fRec79[faust_wrap_sub(i, 1)] - fSlow27 * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)])));
				fRec78[i] = fRec79[i] - fSlow45 * (fSlow46 * fRec78[faust_wrap_sub(i, 2)] + fSlow33 * fRec78[faust_wrap_sub(i, 1)]);
				fRec83[i] = -(fSlow44 * (fSlow30 * fRec83[faust_wrap_sub(i, 1)] - (fYec8[i] + fYec8[faust_wrap_sub(i, 1)])));
				fRec82[i] = fRec83[i] - fSlow45 * (fSlow46 * fRec82[faust_wrap_sub(i, 2)] + fSlow33 * fRec82[faust_wrap_sub(i, 1)]);
				fRec88[i] = -(fSlow2 * (fSlow3 * fRec88[faust_wrap_sub(i, 1)] - fSlow1 * (fRec12[faust_wrap_sub(i, 1)] - fRec12[faust_wrap_sub(i, 2)])));
				fRec87[i] = fRec88[i] - fSlow5 * (fSlow6 * fRec87[faust_wrap_sub(i, 2)] + fSlow8 * fRec87[faust_wrap_sub(i, 1)]);
				fZec18[i] = fSlow17 * fRec86[faust_wrap_sub(i, 1)];
				fRec86[i] = fSlow9 * (fRec87[faust_wrap_sub(i, 2)] + (fRec87[i] - 2.0 * fRec87[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec86[faust_wrap_sub(i, 2)] + fZec18[i]);
				fZec19[i] = fSlow25 * fRec85[faust_wrap_sub(i, 1)];
				fRec85[i] = fRec86[faust_wrap_sub(i, 2)] + fSlow13 * (fZec18[i] + fSlow15 * fRec86[i]) - fSlow21 * (fSlow23 * fRec85[faust_wrap_sub(i, 2)] + fZec19[i]);
				fZec20[i] = fSlow33 * fRec84[faust_wrap_sub(i, 1)];
				fRec84[i] = fRec85[faust_wrap_sub(i, 2)] + fSlow21 * (fZec19[i] + fSlow23 * fRec85[i]) - fSlow29 * (fSlow31 * fRec84[faust_wrap_sub(i, 2)] + fZec20[i]);
				fRec94[i] = -(fSlow2 * (fSlow3 * fRec94[faust_wrap_sub(i, 1)] - (fRec12[faust_wrap_sub(i, 1)] + fRec12[faust_wrap_sub(i, 2)])));
				fRec93[i] = fRec94[i] - fSlow5 * (fSlow6 * fRec93[faust_wrap_sub(i, 2)] + fSlow8 * fRec93[faust_wrap_sub(i, 1)]);
				fYec9[i] = fSlow5 * (fRec93[faust_wrap_sub(i, 2)] + fRec93[i] + 2.0 * fRec93[faust_wrap_sub(i, 1)]);
				fRec92[i] = -(fSlow34 * (fSlow14 * fRec92[faust_wrap_sub(i, 1)] - fSlow11 * (fYec9[i] - fYec9[faust_wrap_sub(i, 1)])));
				fRec91[i] = fRec92[i] - fSlow36 * (fSlow37 * fRec91[faust_wrap_sub(i, 2)] + fSlow17 * fRec91[faust_wrap_sub(i, 1)]);
				fZec21[i] = fSlow25 * fRec90[faust_wrap_sub(i, 1)];
				fRec90[i] = fSlow38 * (fRec91[faust_wrap_sub(i, 2)] + (fRec91[i] - 2.0 * fRec91[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec90[faust_wrap_sub(i, 2)] + fZec21[i]);
				fZec22[i] = fSlow33 * fRec89[faust_wrap_sub(i, 1)];
				fRec89[i] = fRec90[faust_wrap_sub(i, 2)] + fSlow21 * (fZec21[i] + fSlow23 * fRec90[i]) - fSlow29 * (fSlow31 * fRec89[faust_wrap_sub(i, 2)] + fZec22[i]);
				fRec99[i] = -(fSlow34 * (fSlow14 * fRec99[faust_wrap_sub(i, 1)] - (fYec9[i] + fYec9[faust_wrap_sub(i, 1)])));
				fRec98[i] = fRec99[i] - fSlow36 * (fSlow37 * fRec98[faust_wrap_sub(i, 2)] + fSlow17 * fRec98[faust_wrap_sub(i, 1)]);
				fYec10[i] = fSlow36 * (fRec98[faust_wrap_sub(i, 2)] + fRec98[i] + 2.0 * fRec98[faust_wrap_sub(i, 1)]);
				fRec97[i] = -(fSlow39 * (fSlow22 * fRec97[faust_wrap_sub(i, 1)] - fSlow19 * (fYec10[i] - fYec10[faust_wrap_sub(i, 1)])));
				fRec96[i] = fRec97[i] - fSlow41 * (fSlow42 * fRec96[faust_wrap_sub(i, 2)] + fSlow25 * fRec96[faust_wrap_sub(i, 1)]);
				fZec23[i] = fSlow33 * fRec95[faust_wrap_sub(i, 1)];
				fRec95[i] = fSlow43 * (fRec96[faust_wrap_sub(i, 2)] + (fRec96[i] - 2.0 * fRec96[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec95[faust_wrap_sub(i, 2)] + fZec23[i]);
				fRec103[i] = -(fSlow39 * (fSlow22 * fRec103[faust_wrap_sub(i, 1)] - (fYec10[i] + fYec10[faust_wrap_sub(i, 1)])));
				fRec102[i] = fRec103[i] - fSlow41 * (fSlow42 * fRec102[faust_wrap_sub(i, 2)] + fSlow25 * fRec102[faust_wrap_sub(i, 1)]);
				fYec11[i] = fSlow41 * (fRec102[faust_wrap_sub(i, 2)] + fRec102[i] + 2.0 * fRec102[faust_wrap_sub(i, 1)]);
				fRec101[i] = -(fSlow44 * (fSlow30 * fRec101[faust_wrap_sub(i, 1)] - fSlow27 * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)])));
				fRec100[i] = fRec101[i] - fSlow45 * (fSlow46 * fRec100[faust_wrap_sub(i, 2)] + fSlow33 * fRec100[faust_wrap_sub(i, 1)]);
				fRec105[i] = -(fSlow44 * (fSlow30 * fRec105[faust_wrap_sub(i, 1)] - (fYec11[i] + fYec11[faust_wrap_sub(i, 1)])));
				fRec104[i] = fRec105[i] - fSlow45 * (fSlow46 * fRec104[faust_wrap_sub(i, 2)] + fSlow33 * fRec104[faust_wrap_sub(i, 1)]);
				fRec110[i] = -(fSlow2 * (fSlow3 * fRec110[faust_wrap_sub(i, 1)] - fSlow1 * (fRec2[faust_wrap_sub(i, 1)] - fRec2[faust_wrap_sub(i, 2)])));
				fRec109[i] = fRec110[i] - fSlow5 * (fSlow6 * fRec109[faust_wrap_sub(i, 2)] + fSlow8 * fRec109[faust_wrap_sub(i, 1)]);
				fZec24[i] = fSlow17 * fRec108[faust_wrap_sub(i, 1)];
				fRec108[i] = fSlow9 * (fRec109[faust_wrap_sub(i, 2)] + (fRec109[i] - 2.0 * fRec109[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec108[faust_wrap_sub(i, 2)] + fZec24[i]);
				fZec25[i] = fSlow25 * fRec107[faust_wrap_sub(i, 1)];
				fRec107[i] = fRec108[faust_wrap_sub(i, 2)] + fSlow13 * (fZec24[i] + fSlow15 * fRec108[i]) - fSlow21 * (fSlow23 * fRec107[faust_wrap_sub(i, 2)] + fZec25[i]);
				fZec26[i] = fSlow33 * fRec106[faust_wrap_sub(i, 1)];
				fRec106[i] = fRec107[faust_wrap_sub(i, 2)] + fSlow21 * (fZec25[i] + fSlow23 * fRec107[i]) - fSlow29 * (fSlow31 * fRec106[faust_wrap_sub(i, 2)] + fZec26[i]);
				fRec116[i] = -(fSlow2 * (fSlow3 * fRec116[faust_wrap_sub(i, 1)] - (fRec2[faust_wrap_sub(i, 1)] + fRec2[faust_wrap_sub(i, 2)])));
				fRec115[i] = fRec116[i] - fSlow5 * (fSlow6 * fRec115[faust_wrap_sub(i, 2)] + fSlow8 * fRec115[faust_wrap_sub(i, 1)]);
				fYec12[i] = fSlow5 * (fRec115[faust_wrap_sub(i, 2)] + fRec115[i] + 2.0 * fRec115[faust_wrap_sub(i, 1)]);
				fRec114[i] = -(fSlow34 * (fSlow14 * fRec114[faust_wrap_sub(i, 1)] - fSlow11 * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)])));
				fRec113[i] = fRec114[i] - fSlow36 * (fSlow37 * fRec113[faust_wrap_sub(i, 2)] + fSlow17 * fRec113[faust_wrap_sub(i, 1)]);
				fZec27[i] = fSlow25 * fRec112[faust_wrap_sub(i, 1)];
				fRec112[i] = fSlow38 * (fRec113[faust_wrap_sub(i, 2)] + (fRec113[i] - 2.0 * fRec113[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec112[faust_wrap_sub(i, 2)] + fZec27[i]);
				fZec28[i] = fSlow33 * fRec111[faust_wrap_sub(i, 1)];
				fRec111[i] = fRec112[faust_wrap_sub(i, 2)] + fSlow21 * (fZec27[i] + fSlow23 * fRec112[i]) - fSlow29 * (fSlow31 * fRec111[faust_wrap_sub(i, 2)] + fZec28[i]);
				fRec121[i] = -(fSlow34 * (fSlow14 * fRec121[faust_wrap_sub(i, 1)] - (fYec12[i] + fYec12[faust_wrap_sub(i, 1)])));
				fRec120[i] = fRec121[i] - fSlow36 * (fSlow37 * fRec120[faust_wrap_sub(i, 2)] + fSlow17 * fRec120[faust_wrap_sub(i, 1)]);
				fYec13[i] = fSlow36 * (fRec120[faust_wrap_sub(i, 2)] + fRec120[i] + 2.0 * fRec120[faust_wrap_sub(i, 1)]);
				fRec119[i] = -(fSlow39 * (fSlow22 * fRec119[faust_wrap_sub(i, 1)] - fSlow19 * (fYec13[i] - fYec13[faust_wrap_sub(i, 1)])));
				fRec118[i] = fRec119[i] - fSlow41 * (fSlow42 * fRec118[faust_wrap_sub(i, 2)] + fSlow25 * fRec118[faust_wrap_sub(i, 1)]);
				fZec29[i] = fSlow33 * fRec117[faust_wrap_sub(i, 1)];
				fRec117[i] = fSlow43 * (fRec118[faust_wrap_sub(i, 2)] + (fRec118[i] - 2.0 * fRec118[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec117[faust_wrap_sub(i, 2)] + fZec29[i]);
				fRec125[i] = -(fSlow39 * (fSlow22 * fRec125[faust_wrap_sub(i, 1)] - (fYec13[i] + fYec13[faust_wrap_sub(i, 1)])));
				fRec124[i] = fRec125[i] - fSlow41 * (fSlow42 * fRec124[faust_wrap_sub(i, 2)] + fSlow25 * fRec124[faust_wrap_sub(i, 1)]);
				fYec14[i] = fSlow41 * (fRec124[faust_wrap_sub(i, 2)] + fRec124[i] + 2.0 * fRec124[faust_wrap_sub(i, 1)]);
				fRec123[i] = -(fSlow44 * (fSlow30 * fRec123[faust_wrap_sub(i, 1)] - fSlow27 * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)])));
				fRec122[i] = fRec123[i] - fSlow45 * (fSlow46 * fRec122[faust_wrap_sub(i, 2)] + fSlow33 * fRec122[faust_wrap_sub(i, 1)]);
				fRec127[i] = -(fSlow44 * (fSlow30 * fRec127[faust_wrap_sub(i, 1)] - (fYec14[i] + fYec14[faust_wrap_sub(i, 1)])));
				fRec126[i] = fRec127[i] - fSlow45 * (fSlow46 * fRec126[faust_wrap_sub(i, 2)] + fSlow33 * fRec126[faust_wrap_sub(i, 1)]);
				fRec132[i] = -(fSlow2 * (fSlow3 * fRec132[faust_wrap_sub(i, 1)] - fSlow1 * (fRec10[faust_wrap_sub(i, 1)] - fRec10[faust_wrap_sub(i, 2)])));
				fRec131[i] = fRec132[i] - fSlow5 * (fSlow6 * fRec131[faust_wrap_sub(i, 2)] + fSlow8 * fRec131[faust_wrap_sub(i, 1)]);
				fZec30[i] = fSlow17 * fRec130[faust_wrap_sub(i, 1)];
				fRec130[i] = fSlow9 * (fRec131[faust_wrap_sub(i, 2)] + (fRec131[i] - 2.0 * fRec131[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec130[faust_wrap_sub(i, 2)] + fZec30[i]);
				fZec31[i] = fSlow25 * fRec129[faust_wrap_sub(i, 1)];
				fRec129[i] = fRec130[faust_wrap_sub(i, 2)] + fSlow13 * (fZec30[i] + fSlow15 * fRec130[i]) - fSlow21 * (fSlow23 * fRec129[faust_wrap_sub(i, 2)] + fZec31[i]);
				fZec32[i] = fSlow33 * fRec128[faust_wrap_sub(i, 1)];
				fRec128[i] = fRec129[faust_wrap_sub(i, 2)] + fSlow21 * (fZec31[i] + fSlow23 * fRec129[i]) - fSlow29 * (fSlow31 * fRec128[faust_wrap_sub(i, 2)] + fZec32[i]);
				fRec138[i] = -(fSlow2 * (fSlow3 * fRec138[faust_wrap_sub(i, 1)] - (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)])));
				fRec137[i] = fRec138[i] - fSlow5 * (fSlow6 * fRec137[faust_wrap_sub(i, 2)] + fSlow8 * fRec137[faust_wrap_sub(i, 1)]);
				fYec15[i] = fSlow5 * (fRec137[faust_wrap_sub(i, 2)] + fRec137[i] + 2.0 * fRec137[faust_wrap_sub(i, 1)]);
				fRec136[i] = -(fSlow34 * (fSlow14 * fRec136[faust_wrap_sub(i, 1)] - fSlow11 * (fYec15[i] - fYec15[faust_wrap_sub(i, 1)])));
				fRec135[i] = fRec136[i] - fSlow36 * (fSlow37 * fRec135[faust_wrap_sub(i, 2)] + fSlow17 * fRec135[faust_wrap_sub(i, 1)]);
				fZec33[i] = fSlow25 * fRec134[faust_wrap_sub(i, 1)];
				fRec134[i] = fSlow38 * (fRec135[faust_wrap_sub(i, 2)] + (fRec135[i] - 2.0 * fRec135[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec134[faust_wrap_sub(i, 2)] + fZec33[i]);
				fZec34[i] = fSlow33 * fRec133[faust_wrap_sub(i, 1)];
				fRec133[i] = fRec134[faust_wrap_sub(i, 2)] + fSlow21 * (fZec33[i] + fSlow23 * fRec134[i]) - fSlow29 * (fSlow31 * fRec133[faust_wrap_sub(i, 2)] + fZec34[i]);
				fRec143[i] = -(fSlow34 * (fSlow14 * fRec143[faust_wrap_sub(i, 1)] - (fYec15[i] + fYec15[faust_wrap_sub(i, 1)])));
				fRec142[i] = fRec143[i] - fSlow36 * (fSlow37 * fRec142[faust_wrap_sub(i, 2)] + fSlow17 * fRec142[faust_wrap_sub(i, 1)]);
				fYec16[i] = fSlow36 * (fRec142[faust_wrap_sub(i, 2)] + fRec142[i] + 2.0 * fRec142[faust_wrap_sub(i, 1)]);
				fRec141[i] = -(fSlow39 * (fSlow22 * fRec141[faust_wrap_sub(i, 1)] - fSlow19 * (fYec16[i] - fYec16[faust_wrap_sub(i, 1)])));
				fRec140[i] = fRec141[i] - fSlow41 * (fSlow42 * fRec140[faust_wrap_sub(i, 2)] + fSlow25 * fRec140[faust_wrap_sub(i, 1)]);
				fZec35[i] = fSlow33 * fRec139[faust_wrap_sub(i, 1)];
				fRec139[i] = fSlow43 * (fRec140[faust_wrap_sub(i, 2)] + (fRec140[i] - 2.0 * fRec140[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec139[faust_wrap_sub(i, 2)] + fZec35[i]);
				fRec147[i] = -(fSlow39 * (fSlow22 * fRec147[faust_wrap_sub(i, 1)] - (fYec16[i] + fYec16[faust_wrap_sub(i, 1)])));
				fRec146[i] = fRec147[i] - fSlow41 * (fSlow42 * fRec146[faust_wrap_sub(i, 2)] + fSlow25 * fRec146[faust_wrap_sub(i, 1)]);
				fYec17[i] = fSlow41 * (fRec146[faust_wrap_sub(i, 2)] + fRec146[i] + 2.0 * fRec146[faust_wrap_sub(i, 1)]);
				fRec145[i] = -(fSlow44 * (fSlow30 * fRec145[faust_wrap_sub(i, 1)] - fSlow27 * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)])));
				fRec144[i] = fRec145[i] - fSlow45 * (fSlow46 * fRec144[faust_wrap_sub(i, 2)] + fSlow33 * fRec144[faust_wrap_sub(i, 1)]);
				fRec149[i] = -(fSlow44 * (fSlow30 * fRec149[faust_wrap_sub(i, 1)] - (fYec17[i] + fYec17[faust_wrap_sub(i, 1)])));
				fRec148[i] = fRec149[i] - fSlow45 * (fSlow46 * fRec148[faust_wrap_sub(i, 2)] + fSlow33 * fRec148[faust_wrap_sub(i, 1)]);
				fRec154[i] = -(fSlow2 * (fSlow3 * fRec154[faust_wrap_sub(i, 1)] - fSlow1 * (fRec6[faust_wrap_sub(i, 1)] - fRec6[faust_wrap_sub(i, 2)])));
				fRec153[i] = fRec154[i] - fSlow5 * (fSlow6 * fRec153[faust_wrap_sub(i, 2)] + fSlow8 * fRec153[faust_wrap_sub(i, 1)]);
				fZec36[i] = fSlow17 * fRec152[faust_wrap_sub(i, 1)];
				fRec152[i] = fSlow9 * (fRec153[faust_wrap_sub(i, 2)] + (fRec153[i] - 2.0 * fRec153[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec152[faust_wrap_sub(i, 2)] + fZec36[i]);
				fZec37[i] = fSlow25 * fRec151[faust_wrap_sub(i, 1)];
				fRec151[i] = fRec152[faust_wrap_sub(i, 2)] + fSlow13 * (fZec36[i] + fSlow15 * fRec152[i]) - fSlow21 * (fSlow23 * fRec151[faust_wrap_sub(i, 2)] + fZec37[i]);
				fZec38[i] = fSlow33 * fRec150[faust_wrap_sub(i, 1)];
				fRec150[i] = fRec151[faust_wrap_sub(i, 2)] + fSlow21 * (fZec37[i] + fSlow23 * fRec151[i]) - fSlow29 * (fSlow31 * fRec150[faust_wrap_sub(i, 2)] + fZec38[i]);
				fRec160[i] = -(fSlow2 * (fSlow3 * fRec160[faust_wrap_sub(i, 1)] - (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)])));
				fRec159[i] = fRec160[i] - fSlow5 * (fSlow6 * fRec159[faust_wrap_sub(i, 2)] + fSlow8 * fRec159[faust_wrap_sub(i, 1)]);
				fYec18[i] = fSlow5 * (fRec159[faust_wrap_sub(i, 2)] + fRec159[i] + 2.0 * fRec159[faust_wrap_sub(i, 1)]);
				fRec158[i] = -(fSlow34 * (fSlow14 * fRec158[faust_wrap_sub(i, 1)] - fSlow11 * (fYec18[i] - fYec18[faust_wrap_sub(i, 1)])));
				fRec157[i] = fRec158[i] - fSlow36 * (fSlow37 * fRec157[faust_wrap_sub(i, 2)] + fSlow17 * fRec157[faust_wrap_sub(i, 1)]);
				fZec39[i] = fSlow25 * fRec156[faust_wrap_sub(i, 1)];
				fRec156[i] = fSlow38 * (fRec157[faust_wrap_sub(i, 2)] + (fRec157[i] - 2.0 * fRec157[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec156[faust_wrap_sub(i, 2)] + fZec39[i]);
				fZec40[i] = fSlow33 * fRec155[faust_wrap_sub(i, 1)];
				fRec155[i] = fRec156[faust_wrap_sub(i, 2)] + fSlow21 * (fZec39[i] + fSlow23 * fRec156[i]) - fSlow29 * (fSlow31 * fRec155[faust_wrap_sub(i, 2)] + fZec40[i]);
				fRec165[i] = -(fSlow34 * (fSlow14 * fRec165[faust_wrap_sub(i, 1)] - (fYec18[i] + fYec18[faust_wrap_sub(i, 1)])));
				fRec164[i] = fRec165[i] - fSlow36 * (fSlow37 * fRec164[faust_wrap_sub(i, 2)] + fSlow17 * fRec164[faust_wrap_sub(i, 1)]);
				fYec19[i] = fSlow36 * (fRec164[faust_wrap_sub(i, 2)] + fRec164[i] + 2.0 * fRec164[faust_wrap_sub(i, 1)]);
				fRec163[i] = -(fSlow39 * (fSlow22 * fRec163[faust_wrap_sub(i, 1)] - fSlow19 * (fYec19[i] - fYec19[faust_wrap_sub(i, 1)])));
				fRec162[i] = fRec163[i] - fSlow41 * (fSlow42 * fRec162[faust_wrap_sub(i, 2)] + fSlow25 * fRec162[faust_wrap_sub(i, 1)]);
				fZec41[i] = fSlow33 * fRec161[faust_wrap_sub(i, 1)];
				fRec161[i] = fSlow43 * (fRec162[faust_wrap_sub(i, 2)] + (fRec162[i] - 2.0 * fRec162[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec161[faust_wrap_sub(i, 2)] + fZec41[i]);
				fRec169[i] = -(fSlow39 * (fSlow22 * fRec169[faust_wrap_sub(i, 1)] - (fYec19[i] + fYec19[faust_wrap_sub(i, 1)])));
				fRec168[i] = fRec169[i] - fSlow41 * (fSlow42 * fRec168[faust_wrap_sub(i, 2)] + fSlow25 * fRec168[faust_wrap_sub(i, 1)]);
				fYec20[i] = fSlow41 * (fRec168[faust_wrap_sub(i, 2)] + fRec168[i] + 2.0 * fRec168[faust_wrap_sub(i, 1)]);
				fRec167[i] = -(fSlow44 * (fSlow30 * fRec167[faust_wrap_sub(i, 1)] - fSlow27 * (fYec20[i] - fYec20[faust_wrap_sub(i, 1)])));
				fRec166[i] = fRec167[i] - fSlow45 * (fSlow46 * fRec166[faust_wrap_sub(i, 2)] + fSlow33 * fRec166[faust_wrap_sub(i, 1)]);
				fRec171[i] = -(fSlow44 * (fSlow30 * fRec171[faust_wrap_sub(i, 1)] - (fYec20[i] + fYec20[faust_wrap_sub(i, 1)])));
				fRec170[i] = fRec171[i] - fSlow45 * (fSlow46 * fRec170[faust_wrap_sub(i, 2)] + fSlow33 * fRec170[faust_wrap_sub(i, 1)]);
				fRec176[i] = -(fSlow2 * (fSlow3 * fRec176[faust_wrap_sub(i, 1)] - fSlow1 * (fRec14[faust_wrap_sub(i, 1)] - fRec14[faust_wrap_sub(i, 2)])));
				fRec175[i] = fRec176[i] - fSlow5 * (fSlow6 * fRec175[faust_wrap_sub(i, 2)] + fSlow8 * fRec175[faust_wrap_sub(i, 1)]);
				fZec42[i] = fSlow17 * fRec174[faust_wrap_sub(i, 1)];
				fRec174[i] = fSlow9 * (fRec175[faust_wrap_sub(i, 2)] + (fRec175[i] - 2.0 * fRec175[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec174[faust_wrap_sub(i, 2)] + fZec42[i]);
				fZec43[i] = fSlow25 * fRec173[faust_wrap_sub(i, 1)];
				fRec173[i] = fRec174[faust_wrap_sub(i, 2)] + fSlow13 * (fZec42[i] + fSlow15 * fRec174[i]) - fSlow21 * (fSlow23 * fRec173[faust_wrap_sub(i, 2)] + fZec43[i]);
				fZec44[i] = fSlow33 * fRec172[faust_wrap_sub(i, 1)];
				fRec172[i] = fRec173[faust_wrap_sub(i, 2)] + fSlow21 * (fZec43[i] + fSlow23 * fRec173[i]) - fSlow29 * (fSlow31 * fRec172[faust_wrap_sub(i, 2)] + fZec44[i]);
				fRec182[i] = -(fSlow2 * (fSlow3 * fRec182[faust_wrap_sub(i, 1)] - (fRec14[faust_wrap_sub(i, 1)] + fRec14[faust_wrap_sub(i, 2)])));
				fRec181[i] = fRec182[i] - fSlow5 * (fSlow6 * fRec181[faust_wrap_sub(i, 2)] + fSlow8 * fRec181[faust_wrap_sub(i, 1)]);
				fYec21[i] = fSlow5 * (fRec181[faust_wrap_sub(i, 2)] + fRec181[i] + 2.0 * fRec181[faust_wrap_sub(i, 1)]);
				fRec180[i] = -(fSlow34 * (fSlow14 * fRec180[faust_wrap_sub(i, 1)] - fSlow11 * (fYec21[i] - fYec21[faust_wrap_sub(i, 1)])));
				fRec179[i] = fRec180[i] - fSlow36 * (fSlow37 * fRec179[faust_wrap_sub(i, 2)] + fSlow17 * fRec179[faust_wrap_sub(i, 1)]);
				fZec45[i] = fSlow25 * fRec178[faust_wrap_sub(i, 1)];
				fRec178[i] = fSlow38 * (fRec179[faust_wrap_sub(i, 2)] + (fRec179[i] - 2.0 * fRec179[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec178[faust_wrap_sub(i, 2)] + fZec45[i]);
				fZec46[i] = fSlow33 * fRec177[faust_wrap_sub(i, 1)];
				fRec177[i] = fRec178[faust_wrap_sub(i, 2)] + fSlow21 * (fZec45[i] + fSlow23 * fRec178[i]) - fSlow29 * (fSlow31 * fRec177[faust_wrap_sub(i, 2)] + fZec46[i]);
				fRec187[i] = -(fSlow34 * (fSlow14 * fRec187[faust_wrap_sub(i, 1)] - (fYec21[i] + fYec21[faust_wrap_sub(i, 1)])));
				fRec186[i] = fRec187[i] - fSlow36 * (fSlow37 * fRec186[faust_wrap_sub(i, 2)] + fSlow17 * fRec186[faust_wrap_sub(i, 1)]);
				fYec22[i] = fSlow36 * (fRec186[faust_wrap_sub(i, 2)] + fRec186[i] + 2.0 * fRec186[faust_wrap_sub(i, 1)]);
				fRec185[i] = -(fSlow39 * (fSlow22 * fRec185[faust_wrap_sub(i, 1)] - fSlow19 * (fYec22[i] - fYec22[faust_wrap_sub(i, 1)])));
				fRec184[i] = fRec185[i] - fSlow41 * (fSlow42 * fRec184[faust_wrap_sub(i, 2)] + fSlow25 * fRec184[faust_wrap_sub(i, 1)]);
				fZec47[i] = fSlow33 * fRec183[faust_wrap_sub(i, 1)];
				fRec183[i] = fSlow43 * (fRec184[faust_wrap_sub(i, 2)] + (fRec184[i] - 2.0 * fRec184[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec183[faust_wrap_sub(i, 2)] + fZec47[i]);
				fRec191[i] = -(fSlow39 * (fSlow22 * fRec191[faust_wrap_sub(i, 1)] - (fYec22[i] + fYec22[faust_wrap_sub(i, 1)])));
				fRec190[i] = fRec191[i] - fSlow41 * (fSlow42 * fRec190[faust_wrap_sub(i, 2)] + fSlow25 * fRec190[faust_wrap_sub(i, 1)]);
				fYec23[i] = fSlow41 * (fRec190[faust_wrap_sub(i, 2)] + fRec190[i] + 2.0 * fRec190[faust_wrap_sub(i, 1)]);
				fRec189[i] = -(fSlow44 * (fSlow30 * fRec189[faust_wrap_sub(i, 1)] - fSlow27 * (fYec23[i] - fYec23[faust_wrap_sub(i, 1)])));
				fRec188[i] = fRec189[i] - fSlow45 * (fSlow46 * fRec188[faust_wrap_sub(i, 2)] + fSlow33 * fRec188[faust_wrap_sub(i, 1)]);
				fRec193[i] = -(fSlow44 * (fSlow30 * fRec193[faust_wrap_sub(i, 1)] - (fYec23[i] + fYec23[faust_wrap_sub(i, 1)])));
				fRec192[i] = fRec193[i] - fSlow45 * (fSlow46 * fRec192[faust_wrap_sub(i, 2)] + fSlow33 * fRec192[faust_wrap_sub(i, 1)]);
				fRec198[i] = -(fSlow2 * (fSlow3 * fRec198[faust_wrap_sub(i, 1)] - fSlow1 * (fRec1[faust_wrap_sub(i, 1)] - fRec1[faust_wrap_sub(i, 2)])));
				fRec197[i] = fRec198[i] - fSlow5 * (fSlow6 * fRec197[faust_wrap_sub(i, 2)] + fSlow8 * fRec197[faust_wrap_sub(i, 1)]);
				fZec48[i] = fSlow17 * fRec196[faust_wrap_sub(i, 1)];
				fRec196[i] = fSlow9 * (fRec197[faust_wrap_sub(i, 2)] + (fRec197[i] - 2.0 * fRec197[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec196[faust_wrap_sub(i, 2)] + fZec48[i]);
				fZec49[i] = fSlow25 * fRec195[faust_wrap_sub(i, 1)];
				fRec195[i] = fRec196[faust_wrap_sub(i, 2)] + fSlow13 * (fZec48[i] + fSlow15 * fRec196[i]) - fSlow21 * (fSlow23 * fRec195[faust_wrap_sub(i, 2)] + fZec49[i]);
				fZec50[i] = fSlow33 * fRec194[faust_wrap_sub(i, 1)];
				fRec194[i] = fRec195[faust_wrap_sub(i, 2)] + fSlow21 * (fZec49[i] + fSlow23 * fRec195[i]) - fSlow29 * (fSlow31 * fRec194[faust_wrap_sub(i, 2)] + fZec50[i]);
				fRec204[i] = -(fSlow2 * (fSlow3 * fRec204[faust_wrap_sub(i, 1)] - (fRec1[faust_wrap_sub(i, 1)] + fRec1[faust_wrap_sub(i, 2)])));
				fRec203[i] = fRec204[i] - fSlow5 * (fSlow6 * fRec203[faust_wrap_sub(i, 2)] + fSlow8 * fRec203[faust_wrap_sub(i, 1)]);
				fYec24[i] = fSlow5 * (fRec203[faust_wrap_sub(i, 2)] + fRec203[i] + 2.0 * fRec203[faust_wrap_sub(i, 1)]);
				fRec202[i] = -(fSlow34 * (fSlow14 * fRec202[faust_wrap_sub(i, 1)] - fSlow11 * (fYec24[i] - fYec24[faust_wrap_sub(i, 1)])));
				fRec201[i] = fRec202[i] - fSlow36 * (fSlow37 * fRec201[faust_wrap_sub(i, 2)] + fSlow17 * fRec201[faust_wrap_sub(i, 1)]);
				fZec51[i] = fSlow25 * fRec200[faust_wrap_sub(i, 1)];
				fRec200[i] = fSlow38 * (fRec201[faust_wrap_sub(i, 2)] + (fRec201[i] - 2.0 * fRec201[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec200[faust_wrap_sub(i, 2)] + fZec51[i]);
				fZec52[i] = fSlow33 * fRec199[faust_wrap_sub(i, 1)];
				fRec199[i] = fRec200[faust_wrap_sub(i, 2)] + fSlow21 * (fZec51[i] + fSlow23 * fRec200[i]) - fSlow29 * (fSlow31 * fRec199[faust_wrap_sub(i, 2)] + fZec52[i]);
				fRec209[i] = -(fSlow34 * (fSlow14 * fRec209[faust_wrap_sub(i, 1)] - (fYec24[i] + fYec24[faust_wrap_sub(i, 1)])));
				fRec208[i] = fRec209[i] - fSlow36 * (fSlow37 * fRec208[faust_wrap_sub(i, 2)] + fSlow17 * fRec208[faust_wrap_sub(i, 1)]);
				fYec25[i] = fSlow36 * (fRec208[faust_wrap_sub(i, 2)] + fRec208[i] + 2.0 * fRec208[faust_wrap_sub(i, 1)]);
				fRec207[i] = -(fSlow39 * (fSlow22 * fRec207[faust_wrap_sub(i, 1)] - fSlow19 * (fYec25[i] - fYec25[faust_wrap_sub(i, 1)])));
				fRec206[i] = fRec207[i] - fSlow41 * (fSlow42 * fRec206[faust_wrap_sub(i, 2)] + fSlow25 * fRec206[faust_wrap_sub(i, 1)]);
				fZec53[i] = fSlow33 * fRec205[faust_wrap_sub(i, 1)];
				fRec205[i] = fSlow43 * (fRec206[faust_wrap_sub(i, 2)] + (fRec206[i] - 2.0 * fRec206[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec205[faust_wrap_sub(i, 2)] + fZec53[i]);
				fRec213[i] = -(fSlow39 * (fSlow22 * fRec213[faust_wrap_sub(i, 1)] - (fYec25[i] + fYec25[faust_wrap_sub(i, 1)])));
				fRec212[i] = fRec213[i] - fSlow41 * (fSlow42 * fRec212[faust_wrap_sub(i, 2)] + fSlow25 * fRec212[faust_wrap_sub(i, 1)]);
				fYec26[i] = fSlow41 * (fRec212[faust_wrap_sub(i, 2)] + fRec212[i] + 2.0 * fRec212[faust_wrap_sub(i, 1)]);
				fRec211[i] = -(fSlow44 * (fSlow30 * fRec211[faust_wrap_sub(i, 1)] - fSlow27 * (fYec26[i] - fYec26[faust_wrap_sub(i, 1)])));
				fRec210[i] = fRec211[i] - fSlow45 * (fSlow46 * fRec210[faust_wrap_sub(i, 2)] + fSlow33 * fRec210[faust_wrap_sub(i, 1)]);
				fRec215[i] = -(fSlow44 * (fSlow30 * fRec215[faust_wrap_sub(i, 1)] - (fYec26[i] + fYec26[faust_wrap_sub(i, 1)])));
				fRec214[i] = fRec215[i] - fSlow45 * (fSlow46 * fRec214[faust_wrap_sub(i, 2)] + fSlow33 * fRec214[faust_wrap_sub(i, 1)]);
				fRec220[i] = -(fSlow2 * (fSlow3 * fRec220[faust_wrap_sub(i, 1)] - fSlow1 * (fRec9[faust_wrap_sub(i, 1)] - fRec9[faust_wrap_sub(i, 2)])));
				fRec219[i] = fRec220[i] - fSlow5 * (fSlow6 * fRec219[faust_wrap_sub(i, 2)] + fSlow8 * fRec219[faust_wrap_sub(i, 1)]);
				fZec54[i] = fSlow17 * fRec218[faust_wrap_sub(i, 1)];
				fRec218[i] = fSlow9 * (fRec219[faust_wrap_sub(i, 2)] + (fRec219[i] - 2.0 * fRec219[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec218[faust_wrap_sub(i, 2)] + fZec54[i]);
				fZec55[i] = fSlow25 * fRec217[faust_wrap_sub(i, 1)];
				fRec217[i] = fRec218[faust_wrap_sub(i, 2)] + fSlow13 * (fZec54[i] + fSlow15 * fRec218[i]) - fSlow21 * (fSlow23 * fRec217[faust_wrap_sub(i, 2)] + fZec55[i]);
				fZec56[i] = fSlow33 * fRec216[faust_wrap_sub(i, 1)];
				fRec216[i] = fRec217[faust_wrap_sub(i, 2)] + fSlow21 * (fZec55[i] + fSlow23 * fRec217[i]) - fSlow29 * (fSlow31 * fRec216[faust_wrap_sub(i, 2)] + fZec56[i]);
				fRec226[i] = -(fSlow2 * (fSlow3 * fRec226[faust_wrap_sub(i, 1)] - (fRec9[faust_wrap_sub(i, 1)] + fRec9[faust_wrap_sub(i, 2)])));
				fRec225[i] = fRec226[i] - fSlow5 * (fSlow6 * fRec225[faust_wrap_sub(i, 2)] + fSlow8 * fRec225[faust_wrap_sub(i, 1)]);
				fYec27[i] = fSlow5 * (fRec225[faust_wrap_sub(i, 2)] + fRec225[i] + 2.0 * fRec225[faust_wrap_sub(i, 1)]);
				fRec224[i] = -(fSlow34 * (fSlow14 * fRec224[faust_wrap_sub(i, 1)] - fSlow11 * (fYec27[i] - fYec27[faust_wrap_sub(i, 1)])));
				fRec223[i] = fRec224[i] - fSlow36 * (fSlow37 * fRec223[faust_wrap_sub(i, 2)] + fSlow17 * fRec223[faust_wrap_sub(i, 1)]);
				fZec57[i] = fSlow25 * fRec222[faust_wrap_sub(i, 1)];
				fRec222[i] = fSlow38 * (fRec223[faust_wrap_sub(i, 2)] + (fRec223[i] - 2.0 * fRec223[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec222[faust_wrap_sub(i, 2)] + fZec57[i]);
				fZec58[i] = fSlow33 * fRec221[faust_wrap_sub(i, 1)];
				fRec221[i] = fRec222[faust_wrap_sub(i, 2)] + fSlow21 * (fZec57[i] + fSlow23 * fRec222[i]) - fSlow29 * (fSlow31 * fRec221[faust_wrap_sub(i, 2)] + fZec58[i]);
				fRec231[i] = -(fSlow34 * (fSlow14 * fRec231[faust_wrap_sub(i, 1)] - (fYec27[i] + fYec27[faust_wrap_sub(i, 1)])));
				fRec230[i] = fRec231[i] - fSlow36 * (fSlow37 * fRec230[faust_wrap_sub(i, 2)] + fSlow17 * fRec230[faust_wrap_sub(i, 1)]);
				fYec28[i] = fSlow36 * (fRec230[faust_wrap_sub(i, 2)] + fRec230[i] + 2.0 * fRec230[faust_wrap_sub(i, 1)]);
				fRec229[i] = -(fSlow39 * (fSlow22 * fRec229[faust_wrap_sub(i, 1)] - fSlow19 * (fYec28[i] - fYec28[faust_wrap_sub(i, 1)])));
				fRec228[i] = fRec229[i] - fSlow41 * (fSlow42 * fRec228[faust_wrap_sub(i, 2)] + fSlow25 * fRec228[faust_wrap_sub(i, 1)]);
				fZec59[i] = fSlow33 * fRec227[faust_wrap_sub(i, 1)];
				fRec227[i] = fSlow43 * (fRec228[faust_wrap_sub(i, 2)] + (fRec228[i] - 2.0 * fRec228[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec227[faust_wrap_sub(i, 2)] + fZec59[i]);
				fRec235[i] = -(fSlow39 * (fSlow22 * fRec235[faust_wrap_sub(i, 1)] - (fYec28[i] + fYec28[faust_wrap_sub(i, 1)])));
				fRec234[i] = fRec235[i] - fSlow41 * (fSlow42 * fRec234[faust_wrap_sub(i, 2)] + fSlow25 * fRec234[faust_wrap_sub(i, 1)]);
				fYec29[i] = fSlow41 * (fRec234[faust_wrap_sub(i, 2)] + fRec234[i] + 2.0 * fRec234[faust_wrap_sub(i, 1)]);
				fRec233[i] = -(fSlow44 * (fSlow30 * fRec233[faust_wrap_sub(i, 1)] - fSlow27 * (fYec29[i] - fYec29[faust_wrap_sub(i, 1)])));
				fRec232[i] = fRec233[i] - fSlow45 * (fSlow46 * fRec232[faust_wrap_sub(i, 2)] + fSlow33 * fRec232[faust_wrap_sub(i, 1)]);
				fRec237[i] = -(fSlow44 * (fSlow30 * fRec237[faust_wrap_sub(i, 1)] - (fYec29[i] + fYec29[faust_wrap_sub(i, 1)])));
				fRec236[i] = fRec237[i] - fSlow45 * (fSlow46 * fRec236[faust_wrap_sub(i, 2)] + fSlow33 * fRec236[faust_wrap_sub(i, 1)]);
				fRec242[i] = -(fSlow2 * (fSlow3 * fRec242[faust_wrap_sub(i, 1)] - fSlow1 * (fRec5[faust_wrap_sub(i, 1)] - fRec5[faust_wrap_sub(i, 2)])));
				fRec241[i] = fRec242[i] - fSlow5 * (fSlow6 * fRec241[faust_wrap_sub(i, 2)] + fSlow8 * fRec241[faust_wrap_sub(i, 1)]);
				fZec60[i] = fSlow17 * fRec240[faust_wrap_sub(i, 1)];
				fRec240[i] = fSlow9 * (fRec241[faust_wrap_sub(i, 2)] + (fRec241[i] - 2.0 * fRec241[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec240[faust_wrap_sub(i, 2)] + fZec60[i]);
				fZec61[i] = fSlow25 * fRec239[faust_wrap_sub(i, 1)];
				fRec239[i] = fRec240[faust_wrap_sub(i, 2)] + fSlow13 * (fZec60[i] + fSlow15 * fRec240[i]) - fSlow21 * (fSlow23 * fRec239[faust_wrap_sub(i, 2)] + fZec61[i]);
				fZec62[i] = fSlow33 * fRec238[faust_wrap_sub(i, 1)];
				fRec238[i] = fRec239[faust_wrap_sub(i, 2)] + fSlow21 * (fZec61[i] + fSlow23 * fRec239[i]) - fSlow29 * (fSlow31 * fRec238[faust_wrap_sub(i, 2)] + fZec62[i]);
				fRec248[i] = -(fSlow2 * (fSlow3 * fRec248[faust_wrap_sub(i, 1)] - (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)])));
				fRec247[i] = fRec248[i] - fSlow5 * (fSlow6 * fRec247[faust_wrap_sub(i, 2)] + fSlow8 * fRec247[faust_wrap_sub(i, 1)]);
				fYec30[i] = fSlow5 * (fRec247[faust_wrap_sub(i, 2)] + fRec247[i] + 2.0 * fRec247[faust_wrap_sub(i, 1)]);
				fRec246[i] = -(fSlow34 * (fSlow14 * fRec246[faust_wrap_sub(i, 1)] - fSlow11 * (fYec30[i] - fYec30[faust_wrap_sub(i, 1)])));
				fRec245[i] = fRec246[i] - fSlow36 * (fSlow37 * fRec245[faust_wrap_sub(i, 2)] + fSlow17 * fRec245[faust_wrap_sub(i, 1)]);
				fZec63[i] = fSlow25 * fRec244[faust_wrap_sub(i, 1)];
				fRec244[i] = fSlow38 * (fRec245[faust_wrap_sub(i, 2)] + (fRec245[i] - 2.0 * fRec245[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec244[faust_wrap_sub(i, 2)] + fZec63[i]);
				fZec64[i] = fSlow33 * fRec243[faust_wrap_sub(i, 1)];
				fRec243[i] = fRec244[faust_wrap_sub(i, 2)] + fSlow21 * (fZec63[i] + fSlow23 * fRec244[i]) - fSlow29 * (fSlow31 * fRec243[faust_wrap_sub(i, 2)] + fZec64[i]);
				fRec253[i] = -(fSlow34 * (fSlow14 * fRec253[faust_wrap_sub(i, 1)] - (fYec30[i] + fYec30[faust_wrap_sub(i, 1)])));
				fRec252[i] = fRec253[i] - fSlow36 * (fSlow37 * fRec252[faust_wrap_sub(i, 2)] + fSlow17 * fRec252[faust_wrap_sub(i, 1)]);
				fYec31[i] = fSlow36 * (fRec252[faust_wrap_sub(i, 2)] + fRec252[i] + 2.0 * fRec252[faust_wrap_sub(i, 1)]);
				fRec251[i] = -(fSlow39 * (fSlow22 * fRec251[faust_wrap_sub(i, 1)] - fSlow19 * (fYec31[i] - fYec31[faust_wrap_sub(i, 1)])));
				fRec250[i] = fRec251[i] - fSlow41 * (fSlow42 * fRec250[faust_wrap_sub(i, 2)] + fSlow25 * fRec250[faust_wrap_sub(i, 1)]);
				fZec65[i] = fSlow33 * fRec249[faust_wrap_sub(i, 1)];
				fRec249[i] = fSlow43 * (fRec250[faust_wrap_sub(i, 2)] + (fRec250[i] - 2.0 * fRec250[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec249[faust_wrap_sub(i, 2)] + fZec65[i]);
				fRec257[i] = -(fSlow39 * (fSlow22 * fRec257[faust_wrap_sub(i, 1)] - (fYec31[i] + fYec31[faust_wrap_sub(i, 1)])));
				fRec256[i] = fRec257[i] - fSlow41 * (fSlow42 * fRec256[faust_wrap_sub(i, 2)] + fSlow25 * fRec256[faust_wrap_sub(i, 1)]);
				fYec32[i] = fSlow41 * (fRec256[faust_wrap_sub(i, 2)] + fRec256[i] + 2.0 * fRec256[faust_wrap_sub(i, 1)]);
				fRec255[i] = -(fSlow44 * (fSlow30 * fRec255[faust_wrap_sub(i, 1)] - fSlow27 * (fYec32[i] - fYec32[faust_wrap_sub(i, 1)])));
				fRec254[i] = fRec255[i] - fSlow45 * (fSlow46 * fRec254[faust_wrap_sub(i, 2)] + fSlow33 * fRec254[faust_wrap_sub(i, 1)]);
				fRec259[i] = -(fSlow44 * (fSlow30 * fRec259[faust_wrap_sub(i, 1)] - (fYec32[i] + fYec32[faust_wrap_sub(i, 1)])));
				fRec258[i] = fRec259[i] - fSlow45 * (fSlow46 * fRec258[faust_wrap_sub(i, 2)] + fSlow33 * fRec258[faust_wrap_sub(i, 1)]);
				fRec264[i] = -(fSlow2 * (fSlow3 * fRec264[faust_wrap_sub(i, 1)] - fSlow1 * (fRec13[faust_wrap_sub(i, 1)] - fRec13[faust_wrap_sub(i, 2)])));
				fRec263[i] = fRec264[i] - fSlow5 * (fSlow6 * fRec263[faust_wrap_sub(i, 2)] + fSlow8 * fRec263[faust_wrap_sub(i, 1)]);
				fZec66[i] = fSlow17 * fRec262[faust_wrap_sub(i, 1)];
				fRec262[i] = fSlow9 * (fRec263[faust_wrap_sub(i, 2)] + (fRec263[i] - 2.0 * fRec263[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec262[faust_wrap_sub(i, 2)] + fZec66[i]);
				fZec67[i] = fSlow25 * fRec261[faust_wrap_sub(i, 1)];
				fRec261[i] = fRec262[faust_wrap_sub(i, 2)] + fSlow13 * (fZec66[i] + fSlow15 * fRec262[i]) - fSlow21 * (fSlow23 * fRec261[faust_wrap_sub(i, 2)] + fZec67[i]);
				fZec68[i] = fSlow33 * fRec260[faust_wrap_sub(i, 1)];
				fRec260[i] = fRec261[faust_wrap_sub(i, 2)] + fSlow21 * (fZec67[i] + fSlow23 * fRec261[i]) - fSlow29 * (fSlow31 * fRec260[faust_wrap_sub(i, 2)] + fZec68[i]);
				fRec270[i] = -(fSlow2 * (fSlow3 * fRec270[faust_wrap_sub(i, 1)] - (fRec13[faust_wrap_sub(i, 1)] + fRec13[faust_wrap_sub(i, 2)])));
				fRec269[i] = fRec270[i] - fSlow5 * (fSlow6 * fRec269[faust_wrap_sub(i, 2)] + fSlow8 * fRec269[faust_wrap_sub(i, 1)]);
				fYec33[i] = fSlow5 * (fRec269[faust_wrap_sub(i, 2)] + fRec269[i] + 2.0 * fRec269[faust_wrap_sub(i, 1)]);
				fRec268[i] = -(fSlow34 * (fSlow14 * fRec268[faust_wrap_sub(i, 1)] - fSlow11 * (fYec33[i] - fYec33[faust_wrap_sub(i, 1)])));
				fRec267[i] = fRec268[i] - fSlow36 * (fSlow37 * fRec267[faust_wrap_sub(i, 2)] + fSlow17 * fRec267[faust_wrap_sub(i, 1)]);
				fZec69[i] = fSlow25 * fRec266[faust_wrap_sub(i, 1)];
				fRec266[i] = fSlow38 * (fRec267[faust_wrap_sub(i, 2)] + (fRec267[i] - 2.0 * fRec267[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec266[faust_wrap_sub(i, 2)] + fZec69[i]);
				fZec70[i] = fSlow33 * fRec265[faust_wrap_sub(i, 1)];
				fRec265[i] = fRec266[faust_wrap_sub(i, 2)] + fSlow21 * (fZec69[i] + fSlow23 * fRec266[i]) - fSlow29 * (fSlow31 * fRec265[faust_wrap_sub(i, 2)] + fZec70[i]);
				fRec275[i] = -(fSlow34 * (fSlow14 * fRec275[faust_wrap_sub(i, 1)] - (fYec33[i] + fYec33[faust_wrap_sub(i, 1)])));
				fRec274[i] = fRec275[i] - fSlow36 * (fSlow37 * fRec274[faust_wrap_sub(i, 2)] + fSlow17 * fRec274[faust_wrap_sub(i, 1)]);
				fYec34[i] = fSlow36 * (fRec274[faust_wrap_sub(i, 2)] + fRec274[i] + 2.0 * fRec274[faust_wrap_sub(i, 1)]);
				fRec273[i] = -(fSlow39 * (fSlow22 * fRec273[faust_wrap_sub(i, 1)] - fSlow19 * (fYec34[i] - fYec34[faust_wrap_sub(i, 1)])));
				fRec272[i] = fRec273[i] - fSlow41 * (fSlow42 * fRec272[faust_wrap_sub(i, 2)] + fSlow25 * fRec272[faust_wrap_sub(i, 1)]);
				fZec71[i] = fSlow33 * fRec271[faust_wrap_sub(i, 1)];
				fRec271[i] = fSlow43 * (fRec272[faust_wrap_sub(i, 2)] + (fRec272[i] - 2.0 * fRec272[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec271[faust_wrap_sub(i, 2)] + fZec71[i]);
				fRec279[i] = -(fSlow39 * (fSlow22 * fRec279[faust_wrap_sub(i, 1)] - (fYec34[i] + fYec34[faust_wrap_sub(i, 1)])));
				fRec278[i] = fRec279[i] - fSlow41 * (fSlow42 * fRec278[faust_wrap_sub(i, 2)] + fSlow25 * fRec278[faust_wrap_sub(i, 1)]);
				fYec35[i] = fSlow41 * (fRec278[faust_wrap_sub(i, 2)] + fRec278[i] + 2.0 * fRec278[faust_wrap_sub(i, 1)]);
				fRec277[i] = -(fSlow44 * (fSlow30 * fRec277[faust_wrap_sub(i, 1)] - fSlow27 * (fYec35[i] - fYec35[faust_wrap_sub(i, 1)])));
				fRec276[i] = fRec277[i] - fSlow45 * (fSlow46 * fRec276[faust_wrap_sub(i, 2)] + fSlow33 * fRec276[faust_wrap_sub(i, 1)]);
				fRec281[i] = -(fSlow44 * (fSlow30 * fRec281[faust_wrap_sub(i, 1)] - (fYec35[i] + fYec35[faust_wrap_sub(i, 1)])));
				fRec280[i] = fRec281[i] - fSlow45 * (fSlow46 * fRec280[faust_wrap_sub(i, 2)] + fSlow33 * fRec280[faust_wrap_sub(i, 1)]);
				fRec286[i] = -(fSlow2 * (fSlow3 * fRec286[faust_wrap_sub(i, 1)] - fSlow1 * (fRec3[faust_wrap_sub(i, 1)] - fRec3[faust_wrap_sub(i, 2)])));
				fRec285[i] = fRec286[i] - fSlow5 * (fSlow6 * fRec285[faust_wrap_sub(i, 2)] + fSlow8 * fRec285[faust_wrap_sub(i, 1)]);
				fZec72[i] = fSlow17 * fRec284[faust_wrap_sub(i, 1)];
				fRec284[i] = fSlow9 * (fRec285[faust_wrap_sub(i, 2)] + (fRec285[i] - 2.0 * fRec285[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec284[faust_wrap_sub(i, 2)] + fZec72[i]);
				fZec73[i] = fSlow25 * fRec283[faust_wrap_sub(i, 1)];
				fRec283[i] = fRec284[faust_wrap_sub(i, 2)] + fSlow13 * (fZec72[i] + fSlow15 * fRec284[i]) - fSlow21 * (fSlow23 * fRec283[faust_wrap_sub(i, 2)] + fZec73[i]);
				fZec74[i] = fSlow33 * fRec282[faust_wrap_sub(i, 1)];
				fRec282[i] = fRec283[faust_wrap_sub(i, 2)] + fSlow21 * (fZec73[i] + fSlow23 * fRec283[i]) - fSlow29 * (fSlow31 * fRec282[faust_wrap_sub(i, 2)] + fZec74[i]);
				fRec292[i] = -(fSlow2 * (fSlow3 * fRec292[faust_wrap_sub(i, 1)] - (fRec3[faust_wrap_sub(i, 1)] + fRec3[faust_wrap_sub(i, 2)])));
				fRec291[i] = fRec292[i] - fSlow5 * (fSlow6 * fRec291[faust_wrap_sub(i, 2)] + fSlow8 * fRec291[faust_wrap_sub(i, 1)]);
				fYec36[i] = fSlow5 * (fRec291[faust_wrap_sub(i, 2)] + fRec291[i] + 2.0 * fRec291[faust_wrap_sub(i, 1)]);
				fRec290[i] = -(fSlow34 * (fSlow14 * fRec290[faust_wrap_sub(i, 1)] - fSlow11 * (fYec36[i] - fYec36[faust_wrap_sub(i, 1)])));
				fRec289[i] = fRec290[i] - fSlow36 * (fSlow37 * fRec289[faust_wrap_sub(i, 2)] + fSlow17 * fRec289[faust_wrap_sub(i, 1)]);
				fZec75[i] = fSlow25 * fRec288[faust_wrap_sub(i, 1)];
				fRec288[i] = fSlow38 * (fRec289[faust_wrap_sub(i, 2)] + (fRec289[i] - 2.0 * fRec289[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec288[faust_wrap_sub(i, 2)] + fZec75[i]);
				fZec76[i] = fSlow33 * fRec287[faust_wrap_sub(i, 1)];
				fRec287[i] = fRec288[faust_wrap_sub(i, 2)] + fSlow21 * (fZec75[i] + fSlow23 * fRec288[i]) - fSlow29 * (fSlow31 * fRec287[faust_wrap_sub(i, 2)] + fZec76[i]);
				fRec297[i] = -(fSlow34 * (fSlow14 * fRec297[faust_wrap_sub(i, 1)] - (fYec36[i] + fYec36[faust_wrap_sub(i, 1)])));
				fRec296[i] = fRec297[i] - fSlow36 * (fSlow37 * fRec296[faust_wrap_sub(i, 2)] + fSlow17 * fRec296[faust_wrap_sub(i, 1)]);
				fYec37[i] = fSlow36 * (fRec296[faust_wrap_sub(i, 2)] + fRec296[i] + 2.0 * fRec296[faust_wrap_sub(i, 1)]);
				fRec295[i] = -(fSlow39 * (fSlow22 * fRec295[faust_wrap_sub(i, 1)] - fSlow19 * (fYec37[i] - fYec37[faust_wrap_sub(i, 1)])));
				fRec294[i] = fRec295[i] - fSlow41 * (fSlow42 * fRec294[faust_wrap_sub(i, 2)] + fSlow25 * fRec294[faust_wrap_sub(i, 1)]);
				fZec77[i] = fSlow33 * fRec293[faust_wrap_sub(i, 1)];
				fRec293[i] = fSlow43 * (fRec294[faust_wrap_sub(i, 2)] + (fRec294[i] - 2.0 * fRec294[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec293[faust_wrap_sub(i, 2)] + fZec77[i]);
				fRec301[i] = -(fSlow39 * (fSlow22 * fRec301[faust_wrap_sub(i, 1)] - (fYec37[i] + fYec37[faust_wrap_sub(i, 1)])));
				fRec300[i] = fRec301[i] - fSlow41 * (fSlow42 * fRec300[faust_wrap_sub(i, 2)] + fSlow25 * fRec300[faust_wrap_sub(i, 1)]);
				fYec38[i] = fSlow41 * (fRec300[faust_wrap_sub(i, 2)] + fRec300[i] + 2.0 * fRec300[faust_wrap_sub(i, 1)]);
				fRec299[i] = -(fSlow44 * (fSlow30 * fRec299[faust_wrap_sub(i, 1)] - fSlow27 * (fYec38[i] - fYec38[faust_wrap_sub(i, 1)])));
				fRec298[i] = fRec299[i] - fSlow45 * (fSlow46 * fRec298[faust_wrap_sub(i, 2)] + fSlow33 * fRec298[faust_wrap_sub(i, 1)]);
				fRec303[i] = -(fSlow44 * (fSlow30 * fRec303[faust_wrap_sub(i, 1)] - (fYec38[i] + fYec38[faust_wrap_sub(i, 1)])));
				fRec302[i] = fRec303[i] - fSlow45 * (fSlow46 * fRec302[faust_wrap_sub(i, 2)] + fSlow33 * fRec302[faust_wrap_sub(i, 1)]);
				fRec308[i] = -(fSlow2 * (fSlow3 * fRec308[faust_wrap_sub(i, 1)] - fSlow1 * (fRec11[faust_wrap_sub(i, 1)] - fRec11[faust_wrap_sub(i, 2)])));
				fRec307[i] = fRec308[i] - fSlow5 * (fSlow6 * fRec307[faust_wrap_sub(i, 2)] + fSlow8 * fRec307[faust_wrap_sub(i, 1)]);
				fZec78[i] = fSlow17 * fRec306[faust_wrap_sub(i, 1)];
				fRec306[i] = fSlow9 * (fRec307[faust_wrap_sub(i, 2)] + (fRec307[i] - 2.0 * fRec307[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec306[faust_wrap_sub(i, 2)] + fZec78[i]);
				fZec79[i] = fSlow25 * fRec305[faust_wrap_sub(i, 1)];
				fRec305[i] = fRec306[faust_wrap_sub(i, 2)] + fSlow13 * (fZec78[i] + fSlow15 * fRec306[i]) - fSlow21 * (fSlow23 * fRec305[faust_wrap_sub(i, 2)] + fZec79[i]);
				fZec80[i] = fSlow33 * fRec304[faust_wrap_sub(i, 1)];
				fRec304[i] = fRec305[faust_wrap_sub(i, 2)] + fSlow21 * (fZec79[i] + fSlow23 * fRec305[i]) - fSlow29 * (fSlow31 * fRec304[faust_wrap_sub(i, 2)] + fZec80[i]);
				fRec314[i] = -(fSlow2 * (fSlow3 * fRec314[faust_wrap_sub(i, 1)] - (fRec11[faust_wrap_sub(i, 1)] + fRec11[faust_wrap_sub(i, 2)])));
				fRec313[i] = fRec314[i] - fSlow5 * (fSlow6 * fRec313[faust_wrap_sub(i, 2)] + fSlow8 * fRec313[faust_wrap_sub(i, 1)]);
				fYec39[i] = fSlow5 * (fRec313[faust_wrap_sub(i, 2)] + fRec313[i] + 2.0 * fRec313[faust_wrap_sub(i, 1)]);
				fRec312[i] = -(fSlow34 * (fSlow14 * fRec312[faust_wrap_sub(i, 1)] - fSlow11 * (fYec39[i] - fYec39[faust_wrap_sub(i, 1)])));
				fRec311[i] = fRec312[i] - fSlow36 * (fSlow37 * fRec311[faust_wrap_sub(i, 2)] + fSlow17 * fRec311[faust_wrap_sub(i, 1)]);
				fZec81[i] = fSlow25 * fRec310[faust_wrap_sub(i, 1)];
				fRec310[i] = fSlow38 * (fRec311[faust_wrap_sub(i, 2)] + (fRec311[i] - 2.0 * fRec311[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec310[faust_wrap_sub(i, 2)] + fZec81[i]);
				fZec82[i] = fSlow33 * fRec309[faust_wrap_sub(i, 1)];
				fRec309[i] = fRec310[faust_wrap_sub(i, 2)] + fSlow21 * (fZec81[i] + fSlow23 * fRec310[i]) - fSlow29 * (fSlow31 * fRec309[faust_wrap_sub(i, 2)] + fZec82[i]);
				fRec319[i] = -(fSlow34 * (fSlow14 * fRec319[faust_wrap_sub(i, 1)] - (fYec39[i] + fYec39[faust_wrap_sub(i, 1)])));
				fRec318[i] = fRec319[i] - fSlow36 * (fSlow37 * fRec318[faust_wrap_sub(i, 2)] + fSlow17 * fRec318[faust_wrap_sub(i, 1)]);
				fYec40[i] = fSlow36 * (fRec318[faust_wrap_sub(i, 2)] + fRec318[i] + 2.0 * fRec318[faust_wrap_sub(i, 1)]);
				fRec317[i] = -(fSlow39 * (fSlow22 * fRec317[faust_wrap_sub(i, 1)] - fSlow19 * (fYec40[i] - fYec40[faust_wrap_sub(i, 1)])));
				fRec316[i] = fRec317[i] - fSlow41 * (fSlow42 * fRec316[faust_wrap_sub(i, 2)] + fSlow25 * fRec316[faust_wrap_sub(i, 1)]);
				fZec83[i] = fSlow33 * fRec315[faust_wrap_sub(i, 1)];
				fRec315[i] = fSlow43 * (fRec316[faust_wrap_sub(i, 2)] + (fRec316[i] - 2.0 * fRec316[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec315[faust_wrap_sub(i, 2)] + fZec83[i]);
				fRec323[i] = -(fSlow39 * (fSlow22 * fRec323[faust_wrap_sub(i, 1)] - (fYec40[i] + fYec40[faust_wrap_sub(i, 1)])));
				fRec322[i] = fRec323[i] - fSlow41 * (fSlow42 * fRec322[faust_wrap_sub(i, 2)] + fSlow25 * fRec322[faust_wrap_sub(i, 1)]);
				fYec41[i] = fSlow41 * (fRec322[faust_wrap_sub(i, 2)] + fRec322[i] + 2.0 * fRec322[faust_wrap_sub(i, 1)]);
				fRec321[i] = -(fSlow44 * (fSlow30 * fRec321[faust_wrap_sub(i, 1)] - fSlow27 * (fYec41[i] - fYec41[faust_wrap_sub(i, 1)])));
				fRec320[i] = fRec321[i] - fSlow45 * (fSlow46 * fRec320[faust_wrap_sub(i, 2)] + fSlow33 * fRec320[faust_wrap_sub(i, 1)]);
				fRec325[i] = -(fSlow44 * (fSlow30 * fRec325[faust_wrap_sub(i, 1)] - (fYec41[i] + fYec41[faust_wrap_sub(i, 1)])));
				fRec324[i] = fRec325[i] - fSlow45 * (fSlow46 * fRec324[faust_wrap_sub(i, 2)] + fSlow33 * fRec324[faust_wrap_sub(i, 1)]);
				fRec330[i] = -(fSlow2 * (fSlow3 * fRec330[faust_wrap_sub(i, 1)] - fSlow1 * (fRec7[faust_wrap_sub(i, 1)] - fRec7[faust_wrap_sub(i, 2)])));
				fRec329[i] = fRec330[i] - fSlow5 * (fSlow6 * fRec329[faust_wrap_sub(i, 2)] + fSlow8 * fRec329[faust_wrap_sub(i, 1)]);
				fZec84[i] = fSlow17 * fRec328[faust_wrap_sub(i, 1)];
				fRec328[i] = fSlow9 * (fRec329[faust_wrap_sub(i, 2)] + (fRec329[i] - 2.0 * fRec329[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec328[faust_wrap_sub(i, 2)] + fZec84[i]);
				fZec85[i] = fSlow25 * fRec327[faust_wrap_sub(i, 1)];
				fRec327[i] = fRec328[faust_wrap_sub(i, 2)] + fSlow13 * (fZec84[i] + fSlow15 * fRec328[i]) - fSlow21 * (fSlow23 * fRec327[faust_wrap_sub(i, 2)] + fZec85[i]);
				fZec86[i] = fSlow33 * fRec326[faust_wrap_sub(i, 1)];
				fRec326[i] = fRec327[faust_wrap_sub(i, 2)] + fSlow21 * (fZec85[i] + fSlow23 * fRec327[i]) - fSlow29 * (fSlow31 * fRec326[faust_wrap_sub(i, 2)] + fZec86[i]);
				fRec336[i] = -(fSlow2 * (fSlow3 * fRec336[faust_wrap_sub(i, 1)] - (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)])));
				fRec335[i] = fRec336[i] - fSlow5 * (fSlow6 * fRec335[faust_wrap_sub(i, 2)] + fSlow8 * fRec335[faust_wrap_sub(i, 1)]);
				fYec42[i] = fSlow5 * (fRec335[faust_wrap_sub(i, 2)] + fRec335[i] + 2.0 * fRec335[faust_wrap_sub(i, 1)]);
				fRec334[i] = -(fSlow34 * (fSlow14 * fRec334[faust_wrap_sub(i, 1)] - fSlow11 * (fYec42[i] - fYec42[faust_wrap_sub(i, 1)])));
				fRec333[i] = fRec334[i] - fSlow36 * (fSlow37 * fRec333[faust_wrap_sub(i, 2)] + fSlow17 * fRec333[faust_wrap_sub(i, 1)]);
				fZec87[i] = fSlow25 * fRec332[faust_wrap_sub(i, 1)];
				fRec332[i] = fSlow38 * (fRec333[faust_wrap_sub(i, 2)] + (fRec333[i] - 2.0 * fRec333[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec332[faust_wrap_sub(i, 2)] + fZec87[i]);
				fZec88[i] = fSlow33 * fRec331[faust_wrap_sub(i, 1)];
				fRec331[i] = fRec332[faust_wrap_sub(i, 2)] + fSlow21 * (fZec87[i] + fSlow23 * fRec332[i]) - fSlow29 * (fSlow31 * fRec331[faust_wrap_sub(i, 2)] + fZec88[i]);
				fRec341[i] = -(fSlow34 * (fSlow14 * fRec341[faust_wrap_sub(i, 1)] - (fYec42[i] + fYec42[faust_wrap_sub(i, 1)])));
				fRec340[i] = fRec341[i] - fSlow36 * (fSlow37 * fRec340[faust_wrap_sub(i, 2)] + fSlow17 * fRec340[faust_wrap_sub(i, 1)]);
				fYec43[i] = fSlow36 * (fRec340[faust_wrap_sub(i, 2)] + fRec340[i] + 2.0 * fRec340[faust_wrap_sub(i, 1)]);
				fRec339[i] = -(fSlow39 * (fSlow22 * fRec339[faust_wrap_sub(i, 1)] - fSlow19 * (fYec43[i] - fYec43[faust_wrap_sub(i, 1)])));
				fRec338[i] = fRec339[i] - fSlow41 * (fSlow42 * fRec338[faust_wrap_sub(i, 2)] + fSlow25 * fRec338[faust_wrap_sub(i, 1)]);
				fZec89[i] = fSlow33 * fRec337[faust_wrap_sub(i, 1)];
				fRec337[i] = fSlow43 * (fRec338[faust_wrap_sub(i, 2)] + (fRec338[i] - 2.0 * fRec338[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec337[faust_wrap_sub(i, 2)] + fZec89[i]);
				fRec345[i] = -(fSlow39 * (fSlow22 * fRec345[faust_wrap_sub(i, 1)] - (fYec43[i] + fYec43[faust_wrap_sub(i, 1)])));
				fRec344[i] = fRec345[i] - fSlow41 * (fSlow42 * fRec344[faust_wrap_sub(i, 2)] + fSlow25 * fRec344[faust_wrap_sub(i, 1)]);
				fYec44[i] = fSlow41 * (fRec344[faust_wrap_sub(i, 2)] + fRec344[i] + 2.0 * fRec344[faust_wrap_sub(i, 1)]);
				fRec343[i] = -(fSlow44 * (fSlow30 * fRec343[faust_wrap_sub(i, 1)] - fSlow27 * (fYec44[i] - fYec44[faust_wrap_sub(i, 1)])));
				fRec342[i] = fRec343[i] - fSlow45 * (fSlow46 * fRec342[faust_wrap_sub(i, 2)] + fSlow33 * fRec342[faust_wrap_sub(i, 1)]);
				fRec347[i] = -(fSlow44 * (fSlow30 * fRec347[faust_wrap_sub(i, 1)] - (fYec44[i] + fYec44[faust_wrap_sub(i, 1)])));
				fRec346[i] = fRec347[i] - fSlow45 * (fSlow46 * fRec346[faust_wrap_sub(i, 2)] + fSlow33 * fRec346[faust_wrap_sub(i, 1)]);
				fRec352[i] = -(fSlow2 * (fSlow3 * fRec352[faust_wrap_sub(i, 1)] - fSlow1 * (fRec15[faust_wrap_sub(i, 1)] - fRec15[faust_wrap_sub(i, 2)])));
				fRec351[i] = fRec352[i] - fSlow5 * (fSlow6 * fRec351[faust_wrap_sub(i, 2)] + fSlow8 * fRec351[faust_wrap_sub(i, 1)]);
				fZec90[i] = fSlow17 * fRec350[faust_wrap_sub(i, 1)];
				fRec350[i] = fSlow9 * (fRec351[faust_wrap_sub(i, 2)] + (fRec351[i] - 2.0 * fRec351[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec350[faust_wrap_sub(i, 2)] + fZec90[i]);
				fZec91[i] = fSlow25 * fRec349[faust_wrap_sub(i, 1)];
				fRec349[i] = fRec350[faust_wrap_sub(i, 2)] + fSlow13 * (fZec90[i] + fSlow15 * fRec350[i]) - fSlow21 * (fSlow23 * fRec349[faust_wrap_sub(i, 2)] + fZec91[i]);
				fZec92[i] = fSlow33 * fRec348[faust_wrap_sub(i, 1)];
				fRec348[i] = fRec349[faust_wrap_sub(i, 2)] + fSlow21 * (fZec91[i] + fSlow23 * fRec349[i]) - fSlow29 * (fSlow31 * fRec348[faust_wrap_sub(i, 2)] + fZec92[i]);
				fRec358[i] = -(fSlow2 * (fSlow3 * fRec358[faust_wrap_sub(i, 1)] - (fRec15[faust_wrap_sub(i, 1)] + fRec15[faust_wrap_sub(i, 2)])));
				fRec357[i] = fRec358[i] - fSlow5 * (fSlow6 * fRec357[faust_wrap_sub(i, 2)] + fSlow8 * fRec357[faust_wrap_sub(i, 1)]);
				fYec45[i] = fSlow5 * (fRec357[faust_wrap_sub(i, 2)] + fRec357[i] + 2.0 * fRec357[faust_wrap_sub(i, 1)]);
				fRec356[i] = -(fSlow34 * (fSlow14 * fRec356[faust_wrap_sub(i, 1)] - fSlow11 * (fYec45[i] - fYec45[faust_wrap_sub(i, 1)])));
				fRec355[i] = fRec356[i] - fSlow36 * (fSlow37 * fRec355[faust_wrap_sub(i, 2)] + fSlow17 * fRec355[faust_wrap_sub(i, 1)]);
				fZec93[i] = fSlow25 * fRec354[faust_wrap_sub(i, 1)];
				fRec354[i] = fSlow38 * (fRec355[faust_wrap_sub(i, 2)] + (fRec355[i] - 2.0 * fRec355[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec354[faust_wrap_sub(i, 2)] + fZec93[i]);
				fZec94[i] = fSlow33 * fRec353[faust_wrap_sub(i, 1)];
				fRec353[i] = fRec354[faust_wrap_sub(i, 2)] + fSlow21 * (fZec93[i] + fSlow23 * fRec354[i]) - fSlow29 * (fSlow31 * fRec353[faust_wrap_sub(i, 2)] + fZec94[i]);
				fRec363[i] = -(fSlow34 * (fSlow14 * fRec363[faust_wrap_sub(i, 1)] - (fYec45[i] + fYec45[faust_wrap_sub(i, 1)])));
				fRec362[i] = fRec363[i] - fSlow36 * (fSlow37 * fRec362[faust_wrap_sub(i, 2)] + fSlow17 * fRec362[faust_wrap_sub(i, 1)]);
				fYec46[i] = fSlow36 * (fRec362[faust_wrap_sub(i, 2)] + fRec362[i] + 2.0 * fRec362[faust_wrap_sub(i, 1)]);
				fRec361[i] = -(fSlow39 * (fSlow22 * fRec361[faust_wrap_sub(i, 1)] - fSlow19 * (fYec46[i] - fYec46[faust_wrap_sub(i, 1)])));
				fRec360[i] = fRec361[i] - fSlow41 * (fSlow42 * fRec360[faust_wrap_sub(i, 2)] + fSlow25 * fRec360[faust_wrap_sub(i, 1)]);
				fZec95[i] = fSlow33 * fRec359[faust_wrap_sub(i, 1)];
				fRec359[i] = fSlow43 * (fRec360[faust_wrap_sub(i, 2)] + (fRec360[i] - 2.0 * fRec360[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec359[faust_wrap_sub(i, 2)] + fZec95[i]);
				fRec367[i] = -(fSlow39 * (fSlow22 * fRec367[faust_wrap_sub(i, 1)] - (fYec46[i] + fYec46[faust_wrap_sub(i, 1)])));
				fRec366[i] = fRec367[i] - fSlow41 * (fSlow42 * fRec366[faust_wrap_sub(i, 2)] + fSlow25 * fRec366[faust_wrap_sub(i, 1)]);
				fYec47[i] = fSlow41 * (fRec366[faust_wrap_sub(i, 2)] + fRec366[i] + 2.0 * fRec366[faust_wrap_sub(i, 1)]);
				fRec365[i] = -(fSlow44 * (fSlow30 * fRec365[faust_wrap_sub(i, 1)] - fSlow27 * (fYec47[i] - fYec47[faust_wrap_sub(i, 1)])));
				fRec364[i] = fRec365[i] - fSlow45 * (fSlow46 * fRec364[faust_wrap_sub(i, 2)] + fSlow33 * fRec364[faust_wrap_sub(i, 1)]);
				fRec369[i] = -(fSlow44 * (fSlow30 * fRec369[faust_wrap_sub(i, 1)] - (fYec47[i] + fYec47[faust_wrap_sub(i, 1)])));
				fRec368[i] = fRec369[i] - fSlow45 * (fSlow46 * fRec368[faust_wrap_sub(i, 2)] + fSlow33 * fRec368[faust_wrap_sub(i, 1)]);
				fZec99[i] = fSlow54 * (fRec18[faust_wrap_sub(i, 2)] + fSlow29 * (fZec2[i] + fSlow31 * fRec18[i])) + fSlow56 * (fRec23[faust_wrap_sub(i, 2)] + fSlow29 * (fZec4[i] + fSlow31 * fRec23[i])) + fSlow58 * (fRec29[faust_wrap_sub(i, 2)] + fSlow29 * (fZec5[i] + fSlow31 * fRec29[i])) + fSlow45 * (fSlow60 * (fRec34[faust_wrap_sub(i, 2)] + (fRec34[i] - 2.0 * fRec34[faust_wrap_sub(i, 1)])) + fSlow62 * (fRec38[faust_wrap_sub(i, 2)] + fRec38[i] + 2.0 * fRec38[faust_wrap_sub(i, 1)]));
				fZec100[i] = fSlow66 * (fRec40[faust_wrap_sub(i, 2)] + fSlow29 * (fZec8[i] + fSlow31 * fRec40[i])) + fSlow67 * (fRec45[faust_wrap_sub(i, 2)] + fSlow29 * (fZec10[i] + fSlow31 * fRec45[i])) + fSlow68 * (fRec51[faust_wrap_sub(i, 2)] + fSlow29 * (fZec11[i] + fSlow31 * fRec51[i])) + fSlow45 * (fSlow69 * (fRec56[faust_wrap_sub(i, 2)] + (fRec56[i] - 2.0 * fRec56[faust_wrap_sub(i, 1)])) + fSlow70 * (fRec60[faust_wrap_sub(i, 2)] + fRec60[i] + 2.0 * fRec60[faust_wrap_sub(i, 1)]));
				fZec101[i] = fZec99[i] + fZec100[i];
				fZec102[i] = fSlow72 * (fRec62[faust_wrap_sub(i, 2)] + fSlow29 * (fZec14[i] + fSlow31 * fRec62[i])) + fSlow73 * (fRec67[faust_wrap_sub(i, 2)] + fSlow29 * (fZec16[i] + fSlow31 * fRec67[i])) + fSlow74 * (fRec73[faust_wrap_sub(i, 2)] + fSlow29 * (fZec17[i] + fSlow31 * fRec73[i])) + fSlow45 * (fSlow75 * (fRec78[faust_wrap_sub(i, 2)] + (fRec78[i] - 2.0 * fRec78[faust_wrap_sub(i, 1)])) + fSlow76 * (fRec82[faust_wrap_sub(i, 2)] + fRec82[i] + 2.0 * fRec82[faust_wrap_sub(i, 1)]));
				fZec103[i] = fSlow78 * (fRec84[faust_wrap_sub(i, 2)] + fSlow29 * (fZec20[i] + fSlow31 * fRec84[i])) + fSlow79 * (fRec89[faust_wrap_sub(i, 2)] + fSlow29 * (fZec22[i] + fSlow31 * fRec89[i])) + fSlow80 * (fRec95[faust_wrap_sub(i, 2)] + fSlow29 * (fZec23[i] + fSlow31 * fRec95[i])) + fSlow45 * (fSlow81 * (fRec100[faust_wrap_sub(i, 2)] + (fRec100[i] - 2.0 * fRec100[faust_wrap_sub(i, 1)])) + fSlow82 * (fRec104[faust_wrap_sub(i, 2)] + fRec104[i] + 2.0 * fRec104[faust_wrap_sub(i, 1)]));
				fZec104[i] = fZec102[i] + fZec103[i];
				fZec105[i] = fZec101[i] + fZec104[i];
				fZec106[i] = fSlow84 * (fRec106[faust_wrap_sub(i, 2)] + fSlow29 * (fZec26[i] + fSlow31 * fRec106[i])) + fSlow85 * (fRec111[faust_wrap_sub(i, 2)] + fSlow29 * (fZec28[i] + fSlow31 * fRec111[i])) + fSlow86 * (fRec117[faust_wrap_sub(i, 2)] + fSlow29 * (fZec29[i] + fSlow31 * fRec117[i])) + fSlow45 * (fSlow87 * (fRec122[faust_wrap_sub(i, 2)] + (fRec122[i] - 2.0 * fRec122[faust_wrap_sub(i, 1)])) + fSlow88 * (fRec126[faust_wrap_sub(i, 2)] + fRec126[i] + 2.0 * fRec126[faust_wrap_sub(i, 1)]));
				fZec107[i] = fSlow90 * (fRec128[faust_wrap_sub(i, 2)] + fSlow29 * (fZec32[i] + fSlow31 * fRec128[i])) + fSlow91 * (fRec133[faust_wrap_sub(i, 2)] + fSlow29 * (fZec34[i] + fSlow31 * fRec133[i])) + fSlow92 * (fRec139[faust_wrap_sub(i, 2)] + fSlow29 * (fZec35[i] + fSlow31 * fRec139[i])) + fSlow45 * (fSlow93 * (fRec144[faust_wrap_sub(i, 2)] + (fRec144[i] - 2.0 * fRec144[faust_wrap_sub(i, 1)])) + fSlow94 * (fRec148[faust_wrap_sub(i, 2)] + fRec148[i] + 2.0 * fRec148[faust_wrap_sub(i, 1)]));
				fZec108[i] = fZec106[i] + fZec107[i];
				fZec109[i] = fSlow96 * (fRec150[faust_wrap_sub(i, 2)] + fSlow29 * (fZec38[i] + fSlow31 * fRec150[i])) + fSlow97 * (fRec155[faust_wrap_sub(i, 2)] + fSlow29 * (fZec40[i] + fSlow31 * fRec155[i])) + fSlow98 * (fRec161[faust_wrap_sub(i, 2)] + fSlow29 * (fZec41[i] + fSlow31 * fRec161[i])) + fSlow45 * (fSlow99 * (fRec166[faust_wrap_sub(i, 2)] + (fRec166[i] - 2.0 * fRec166[faust_wrap_sub(i, 1)])) + fSlow100 * (fRec170[faust_wrap_sub(i, 2)] + fRec170[i] + 2.0 * fRec170[faust_wrap_sub(i, 1)]));
				fZec110[i] = fSlow102 * (fRec172[faust_wrap_sub(i, 2)] + fSlow29 * (fZec44[i] + fSlow31 * fRec172[i])) + fSlow103 * (fRec177[faust_wrap_sub(i, 2)] + fSlow29 * (fZec46[i] + fSlow31 * fRec177[i])) + fSlow104 * (fRec183[faust_wrap_sub(i, 2)] + fSlow29 * (fZec47[i] + fSlow31 * fRec183[i])) + fSlow45 * (fSlow105 * (fRec188[faust_wrap_sub(i, 2)] + (fRec188[i] - 2.0 * fRec188[faust_wrap_sub(i, 1)])) + fSlow106 * (fRec192[faust_wrap_sub(i, 2)] + fRec192[i] + 2.0 * fRec192[faust_wrap_sub(i, 1)]));
				fZec111[i] = fZec109[i] + fZec110[i];
				fZec112[i] = fZec108[i] + fZec111[i];
				fZec113[i] = fZec105[i] + fZec112[i];
				fZec114[i] = fSlow108 * (fRec194[faust_wrap_sub(i, 2)] + fSlow29 * (fZec50[i] + fSlow31 * fRec194[i])) + fSlow109 * (fRec199[faust_wrap_sub(i, 2)] + fSlow29 * (fZec52[i] + fSlow31 * fRec199[i])) + fSlow110 * (fRec205[faust_wrap_sub(i, 2)] + fSlow29 * (fZec53[i] + fSlow31 * fRec205[i])) + fSlow45 * (fSlow111 * (fRec210[faust_wrap_sub(i, 2)] + (fRec210[i] - 2.0 * fRec210[faust_wrap_sub(i, 1)])) + fSlow112 * (fRec214[faust_wrap_sub(i, 2)] + fRec214[i] + 2.0 * fRec214[faust_wrap_sub(i, 1)]));
				fZec115[i] = fSlow114 * (fRec216[faust_wrap_sub(i, 2)] + fSlow29 * (fZec56[i] + fSlow31 * fRec216[i])) + fSlow115 * (fRec221[faust_wrap_sub(i, 2)] + fSlow29 * (fZec58[i] + fSlow31 * fRec221[i])) + fSlow116 * (fRec227[faust_wrap_sub(i, 2)] + fSlow29 * (fZec59[i] + fSlow31 * fRec227[i])) + fSlow45 * (fSlow117 * (fRec232[faust_wrap_sub(i, 2)] + (fRec232[i] - 2.0 * fRec232[faust_wrap_sub(i, 1)])) + fSlow118 * (fRec236[faust_wrap_sub(i, 2)] + fRec236[i] + 2.0 * fRec236[faust_wrap_sub(i, 1)]));
				fZec116[i] = fZec114[i] + fZec115[i];
				fZec117[i] = fSlow120 * (fRec238[faust_wrap_sub(i, 2)] + fSlow29 * (fZec62[i] + fSlow31 * fRec238[i])) + fSlow121 * (fRec243[faust_wrap_sub(i, 2)] + fSlow29 * (fZec64[i] + fSlow31 * fRec243[i])) + fSlow122 * (fRec249[faust_wrap_sub(i, 2)] + fSlow29 * (fZec65[i] + fSlow31 * fRec249[i])) + fSlow45 * (fSlow123 * (fRec254[faust_wrap_sub(i, 2)] + (fRec254[i] - 2.0 * fRec254[faust_wrap_sub(i, 1)])) + fSlow124 * (fRec258[faust_wrap_sub(i, 2)] + fRec258[i] + 2.0 * fRec258[faust_wrap_sub(i, 1)]));
				fZec118[i] = fSlow126 * (fRec260[faust_wrap_sub(i, 2)] + fSlow29 * (fZec68[i] + fSlow31 * fRec260[i])) + fSlow127 * (fRec265[faust_wrap_sub(i, 2)] + fSlow29 * (fZec70[i] + fSlow31 * fRec265[i])) + fSlow128 * (fRec271[faust_wrap_sub(i, 2)] + fSlow29 * (fZec71[i] + fSlow31 * fRec271[i])) + fSlow45 * (fSlow129 * (fRec276[faust_wrap_sub(i, 2)] + (fRec276[i] - 2.0 * fRec276[faust_wrap_sub(i, 1)])) + fSlow130 * (fRec280[faust_wrap_sub(i, 2)] + fRec280[i] + 2.0 * fRec280[faust_wrap_sub(i, 1)]));
				fZec119[i] = fZec117[i] + fZec118[i];
				fZec120[i] = fZec116[i] + fZec119[i];
				fZec121[i] = fSlow132 * (fRec282[faust_wrap_sub(i, 2)] + fSlow29 * (fZec74[i] + fSlow31 * fRec282[i])) + fSlow133 * (fRec287[faust_wrap_sub(i, 2)] + fSlow29 * (fZec76[i] + fSlow31 * fRec287[i])) + fSlow134 * (fRec293[faust_wrap_sub(i, 2)] + fSlow29 * (fZec77[i] + fSlow31 * fRec293[i])) + fSlow45 * (fSlow135 * (fRec298[faust_wrap_sub(i, 2)] + (fRec298[i] - 2.0 * fRec298[faust_wrap_sub(i, 1)])) + fSlow136 * (fRec302[faust_wrap_sub(i, 2)] + fRec302[i] + 2.0 * fRec302[faust_wrap_sub(i, 1)]));
				fZec122[i] = fSlow138 * (fRec304[faust_wrap_sub(i, 2)] + fSlow29 * (fZec80[i] + fSlow31 * fRec304[i])) + fSlow139 * (fRec309[faust_wrap_sub(i, 2)] + fSlow29 * (fZec82[i] + fSlow31 * fRec309[i])) + fSlow140 * (fRec315[faust_wrap_sub(i, 2)] + fSlow29 * (fZec83[i] + fSlow31 * fRec315[i])) + fSlow45 * (fSlow141 * (fRec320[faust_wrap_sub(i, 2)] + (fRec320[i] - 2.0 * fRec320[faust_wrap_sub(i, 1)])) + fSlow142 * (fRec324[faust_wrap_sub(i, 2)] + fRec324[i] + 2.0 * fRec324[faust_wrap_sub(i, 1)]));
				fZec123[i] = fZec121[i] + fZec122[i];
				fZec124[i] = fSlow144 * (fRec326[faust_wrap_sub(i, 2)] + fSlow29 * (fZec86[i] + fSlow31 * fRec326[i])) + fSlow145 * (fRec331[faust_wrap_sub(i, 2)] + fSlow29 * (fZec88[i] + fSlow31 * fRec331[i])) + fSlow146 * (fRec337[faust_wrap_sub(i, 2)] + fSlow29 * (fZec89[i] + fSlow31 * fRec337[i])) + fSlow45 * (fSlow147 * (fRec342[faust_wrap_sub(i, 2)] + (fRec342[i] - 2.0 * fRec342[faust_wrap_sub(i, 1)])) + fSlow148 * (fRec346[faust_wrap_sub(i, 2)] + fRec346[i] + 2.0 * fRec346[faust_wrap_sub(i, 1)]));
				fZec125[i] = fSlow150 * (fRec348[faust_wrap_sub(i, 2)] + fSlow29 * (fZec92[i] + fSlow31 * fRec348[i])) + fSlow151 * (fRec353[faust_wrap_sub(i, 2)] + fSlow29 * (fZec94[i] + fSlow31 * fRec353[i])) + fSlow152 * (fRec359[faust_wrap_sub(i, 2)] + fSlow29 * (fZec95[i] + fSlow31 * fRec359[i])) + fSlow45 * (fSlow153 * (fRec364[faust_wrap_sub(i, 2)] + (fRec364[i] - 2.0 * fRec364[faust_wrap_sub(i, 1)])) + fSlow154 * (fRec368[faust_wrap_sub(i, 2)] + fRec368[i] + 2.0 * fRec368[faust_wrap_sub(i, 1)]));
				fZec126[i] = fZec124[i] + fZec125[i];
				fZec127[i] = fZec123[i] + fZec126[i];
				fZec128[i] = fZec120[i] + fZec127[i];
				fYec48[(faust_wrap_add(i, fYec48_idx)) & 16383] = fZec96[i] + fZec98[i] + fSlow50 * (fZec113[i] + fZec128[i]) + fZec129[i];
				fRec0[i] = fYec48[(faust_wrap_sub(faust_wrap_add(i, fYec48_idx), iSlow156)) & 16383];
				fYec49[(faust_wrap_add(i, fYec49_idx)) & 16383] = fZec130[i] + fZec131[i] + fZec96[i] + fSlow50 * (fZec113[i] - fZec128[i]);
				fRec1[i] = fYec49[(faust_wrap_sub(faust_wrap_add(i, fYec49_idx), iSlow158)) & 16383];
				fZec133[i] = fZec105[i] - fZec112[i];
				fZec134[i] = fZec120[i] - fZec127[i];
				fYec50[(faust_wrap_add(i, fYec50_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec133[i] + fZec134[i]);
				fRec2[i] = fYec50[(faust_wrap_sub(faust_wrap_add(i, fYec50_idx), iSlow159)) & 16383];
				fYec51[(faust_wrap_add(i, fYec51_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec133[i] - fZec134[i]);
				fRec3[i] = fYec51[(faust_wrap_sub(faust_wrap_add(i, fYec51_idx), iSlow160)) & 16383];
				fZec136[i] = fZec101[i] - fZec104[i];
				fZec137[i] = fZec108[i] - fZec111[i];
				fZec138[i] = fZec136[i] + fZec137[i];
				fZec139[i] = fZec116[i] - fZec119[i];
				fZec140[i] = fZec123[i] - fZec126[i];
				fZec141[i] = fZec139[i] + fZec140[i];
				fYec52[(faust_wrap_add(i, fYec52_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec138[i] + fZec141[i]);
				fRec4[i] = fYec52[(faust_wrap_sub(faust_wrap_add(i, fYec52_idx), iSlow161)) & 16383];
				fYec53[(faust_wrap_add(i, fYec53_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec138[i] - fZec141[i]);
				fRec5[i] = fYec53[(faust_wrap_sub(faust_wrap_add(i, fYec53_idx), iSlow162)) & 16383];
				fZec142[i] = fZec136[i] - fZec137[i];
				fZec143[i] = fZec139[i] - fZec140[i];
				fYec54[(faust_wrap_add(i, fYec54_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec142[i] + fZec143[i]);
				fRec6[i] = fYec54[(faust_wrap_sub(faust_wrap_add(i, fYec54_idx), iSlow163)) & 16383];
				fYec55[(faust_wrap_add(i, fYec55_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec142[i] - fZec143[i]);
				fRec7[i] = fYec55[(faust_wrap_sub(faust_wrap_add(i, fYec55_idx), iSlow164)) & 16383];
				fZec144[i] = fZec99[i] - fZec100[i];
				fZec145[i] = fZec102[i] - fZec103[i];
				fZec146[i] = fZec144[i] + fZec145[i];
				fZec147[i] = fZec106[i] - fZec107[i];
				fZec148[i] = fZec109[i] - fZec110[i];
				fZec149[i] = fZec147[i] + fZec148[i];
				fZec150[i] = fZec146[i] + fZec149[i];
				fZec151[i] = fZec114[i] - fZec115[i];
				fZec152[i] = fZec117[i] - fZec118[i];
				fZec153[i] = fZec151[i] + fZec152[i];
				fZec154[i] = fZec121[i] - fZec122[i];
				fZec155[i] = fZec124[i] - fZec125[i];
				fZec156[i] = fZec154[i] + fZec155[i];
				fZec157[i] = fZec153[i] + fZec156[i];
				fYec56[(faust_wrap_add(i, fYec56_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec150[i] + fZec157[i]);
				fRec8[i] = fYec56[(faust_wrap_sub(faust_wrap_add(i, fYec56_idx), iSlow165)) & 16383];
				fYec57[(faust_wrap_add(i, fYec57_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec150[i] - fZec157[i]);
				fRec9[i] = fYec57[(faust_wrap_sub(faust_wrap_add(i, fYec57_idx), iSlow166)) & 16383];
				fZec158[i] = fZec146[i] - fZec149[i];
				fZec159[i] = fZec153[i] - fZec156[i];
				fYec58[(faust_wrap_add(i, fYec58_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec158[i] + fZec159[i]);
				fRec10[i] = fYec58[(faust_wrap_sub(faust_wrap_add(i, fYec58_idx), iSlow167)) & 16383];
				fYec59[(faust_wrap_add(i, fYec59_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec158[i] - fZec159[i]);
				fRec11[i] = fYec59[(faust_wrap_sub(faust_wrap_add(i, fYec59_idx), iSlow168)) & 16383];
				fZec160[i] = fZec144[i] - fZec145[i];
				fZec161[i] = fZec147[i] - fZec148[i];
				fZec162[i] = fZec160[i] + fZec161[i];
				fZec163[i] = fZec151[i] - fZec152[i];
				fZec164[i] = fZec154[i] - fZec155[i];
				fZec165[i] = fZec163[i] + fZec164[i];
				fYec60[(faust_wrap_add(i, fYec60_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec162[i] + fZec165[i]);
				fRec12[i] = fYec60[(faust_wrap_sub(faust_wrap_add(i, fYec60_idx), iSlow169)) & 16383];
				fYec61[(faust_wrap_add(i, fYec61_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec162[i] - fZec165[i]);
				fRec13[i] = fYec61[(faust_wrap_sub(faust_wrap_add(i, fYec61_idx), iSlow170)) & 16383];
				fZec166[i] = fZec160[i] - fZec161[i];
				fZec167[i] = fZec163[i] - fZec164[i];
				fYec62[(faust_wrap_add(i, fYec62_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec166[i] + fZec167[i]);
				fRec14[i] = fYec62[(faust_wrap_sub(faust_wrap_add(i, fYec62_idx), iSlow171)) & 16383];
				fYec63[(faust_wrap_add(i, fYec63_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec166[i] - fZec167[i]);
				fRec15[i] = fYec63[(faust_wrap_sub(faust_wrap_add(i, fYec63_idx), iSlow172)) & 16383];
			}
			/* Post code */
			fYec63_idx_save = vsize;
			fYec62_idx_save = vsize;
			fYec61_idx_save = vsize;
			fYec60_idx_save = vsize;
			fYec59_idx_save = vsize;
			fYec58_idx_save = vsize;
			fYec57_idx_save = vsize;
			fYec56_idx_save = vsize;
			fYec55_idx_save = vsize;
			fYec54_idx_save = vsize;
			fYec53_idx_save = vsize;
			fYec52_idx_save = vsize;
			fYec51_idx_save = vsize;
			fYec50_idx_save = vsize;
			fYec49_idx_save = vsize;
			fYec48_idx_save = vsize;
			for (int j801 = 0; j801 < 4; j801 = faust_wrap_add(j801, 1)) {
				fRec369_perm[j801] = fRec369_tmp[faust_wrap_add(vsize, j801)];
			}
			for (int j803 = 0; j803 < 4; j803 = faust_wrap_add(j803, 1)) {
				fRec368_perm[j803] = fRec368_tmp[faust_wrap_add(vsize, j803)];
			}
			for (int j795 = 0; j795 < 4; j795 = faust_wrap_add(j795, 1)) {
				fYec47_perm[j795] = fYec47_tmp[faust_wrap_add(vsize, j795)];
			}
			for (int j791 = 0; j791 < 4; j791 = faust_wrap_add(j791, 1)) {
				fRec367_perm[j791] = fRec367_tmp[faust_wrap_add(vsize, j791)];
			}
			for (int j793 = 0; j793 < 4; j793 = faust_wrap_add(j793, 1)) {
				fRec366_perm[j793] = fRec366_tmp[faust_wrap_add(vsize, j793)];
			}
			for (int j797 = 0; j797 < 4; j797 = faust_wrap_add(j797, 1)) {
				fRec365_perm[j797] = fRec365_tmp[faust_wrap_add(vsize, j797)];
			}
			for (int j799 = 0; j799 < 4; j799 = faust_wrap_add(j799, 1)) {
				fRec364_perm[j799] = fRec364_tmp[faust_wrap_add(vsize, j799)];
			}
			for (int j783 = 0; j783 < 4; j783 = faust_wrap_add(j783, 1)) {
				fYec46_perm[j783] = fYec46_tmp[faust_wrap_add(vsize, j783)];
			}
			for (int j779 = 0; j779 < 4; j779 = faust_wrap_add(j779, 1)) {
				fRec363_perm[j779] = fRec363_tmp[faust_wrap_add(vsize, j779)];
			}
			for (int j781 = 0; j781 < 4; j781 = faust_wrap_add(j781, 1)) {
				fRec362_perm[j781] = fRec362_tmp[faust_wrap_add(vsize, j781)];
			}
			for (int j785 = 0; j785 < 4; j785 = faust_wrap_add(j785, 1)) {
				fRec361_perm[j785] = fRec361_tmp[faust_wrap_add(vsize, j785)];
			}
			for (int j787 = 0; j787 < 4; j787 = faust_wrap_add(j787, 1)) {
				fRec360_perm[j787] = fRec360_tmp[faust_wrap_add(vsize, j787)];
			}
			for (int j789 = 0; j789 < 4; j789 = faust_wrap_add(j789, 1)) {
				fRec359_perm[j789] = fRec359_tmp[faust_wrap_add(vsize, j789)];
			}
			for (int j769 = 0; j769 < 4; j769 = faust_wrap_add(j769, 1)) {
				fYec45_perm[j769] = fYec45_tmp[faust_wrap_add(vsize, j769)];
			}
			for (int j765 = 0; j765 < 4; j765 = faust_wrap_add(j765, 1)) {
				fRec358_perm[j765] = fRec358_tmp[faust_wrap_add(vsize, j765)];
			}
			for (int j767 = 0; j767 < 4; j767 = faust_wrap_add(j767, 1)) {
				fRec357_perm[j767] = fRec357_tmp[faust_wrap_add(vsize, j767)];
			}
			for (int j771 = 0; j771 < 4; j771 = faust_wrap_add(j771, 1)) {
				fRec356_perm[j771] = fRec356_tmp[faust_wrap_add(vsize, j771)];
			}
			for (int j773 = 0; j773 < 4; j773 = faust_wrap_add(j773, 1)) {
				fRec355_perm[j773] = fRec355_tmp[faust_wrap_add(vsize, j773)];
			}
			for (int j775 = 0; j775 < 4; j775 = faust_wrap_add(j775, 1)) {
				fRec354_perm[j775] = fRec354_tmp[faust_wrap_add(vsize, j775)];
			}
			for (int j777 = 0; j777 < 4; j777 = faust_wrap_add(j777, 1)) {
				fRec353_perm[j777] = fRec353_tmp[faust_wrap_add(vsize, j777)];
			}
			for (int j755 = 0; j755 < 4; j755 = faust_wrap_add(j755, 1)) {
				fRec352_perm[j755] = fRec352_tmp[faust_wrap_add(vsize, j755)];
			}
			for (int j757 = 0; j757 < 4; j757 = faust_wrap_add(j757, 1)) {
				fRec351_perm[j757] = fRec351_tmp[faust_wrap_add(vsize, j757)];
			}
			for (int j759 = 0; j759 < 4; j759 = faust_wrap_add(j759, 1)) {
				fRec350_perm[j759] = fRec350_tmp[faust_wrap_add(vsize, j759)];
			}
			for (int j761 = 0; j761 < 4; j761 = faust_wrap_add(j761, 1)) {
				fRec349_perm[j761] = fRec349_tmp[faust_wrap_add(vsize, j761)];
			}
			for (int j763 = 0; j763 < 4; j763 = faust_wrap_add(j763, 1)) {
				fRec348_perm[j763] = fRec348_tmp[faust_wrap_add(vsize, j763)];
			}
			for (int j751 = 0; j751 < 4; j751 = faust_wrap_add(j751, 1)) {
				fRec347_perm[j751] = fRec347_tmp[faust_wrap_add(vsize, j751)];
			}
			for (int j753 = 0; j753 < 4; j753 = faust_wrap_add(j753, 1)) {
				fRec346_perm[j753] = fRec346_tmp[faust_wrap_add(vsize, j753)];
			}
			for (int j745 = 0; j745 < 4; j745 = faust_wrap_add(j745, 1)) {
				fYec44_perm[j745] = fYec44_tmp[faust_wrap_add(vsize, j745)];
			}
			for (int j741 = 0; j741 < 4; j741 = faust_wrap_add(j741, 1)) {
				fRec345_perm[j741] = fRec345_tmp[faust_wrap_add(vsize, j741)];
			}
			for (int j743 = 0; j743 < 4; j743 = faust_wrap_add(j743, 1)) {
				fRec344_perm[j743] = fRec344_tmp[faust_wrap_add(vsize, j743)];
			}
			for (int j747 = 0; j747 < 4; j747 = faust_wrap_add(j747, 1)) {
				fRec343_perm[j747] = fRec343_tmp[faust_wrap_add(vsize, j747)];
			}
			for (int j749 = 0; j749 < 4; j749 = faust_wrap_add(j749, 1)) {
				fRec342_perm[j749] = fRec342_tmp[faust_wrap_add(vsize, j749)];
			}
			for (int j733 = 0; j733 < 4; j733 = faust_wrap_add(j733, 1)) {
				fYec43_perm[j733] = fYec43_tmp[faust_wrap_add(vsize, j733)];
			}
			for (int j729 = 0; j729 < 4; j729 = faust_wrap_add(j729, 1)) {
				fRec341_perm[j729] = fRec341_tmp[faust_wrap_add(vsize, j729)];
			}
			for (int j731 = 0; j731 < 4; j731 = faust_wrap_add(j731, 1)) {
				fRec340_perm[j731] = fRec340_tmp[faust_wrap_add(vsize, j731)];
			}
			for (int j735 = 0; j735 < 4; j735 = faust_wrap_add(j735, 1)) {
				fRec339_perm[j735] = fRec339_tmp[faust_wrap_add(vsize, j735)];
			}
			for (int j737 = 0; j737 < 4; j737 = faust_wrap_add(j737, 1)) {
				fRec338_perm[j737] = fRec338_tmp[faust_wrap_add(vsize, j737)];
			}
			for (int j739 = 0; j739 < 4; j739 = faust_wrap_add(j739, 1)) {
				fRec337_perm[j739] = fRec337_tmp[faust_wrap_add(vsize, j739)];
			}
			for (int j719 = 0; j719 < 4; j719 = faust_wrap_add(j719, 1)) {
				fYec42_perm[j719] = fYec42_tmp[faust_wrap_add(vsize, j719)];
			}
			for (int j715 = 0; j715 < 4; j715 = faust_wrap_add(j715, 1)) {
				fRec336_perm[j715] = fRec336_tmp[faust_wrap_add(vsize, j715)];
			}
			for (int j717 = 0; j717 < 4; j717 = faust_wrap_add(j717, 1)) {
				fRec335_perm[j717] = fRec335_tmp[faust_wrap_add(vsize, j717)];
			}
			for (int j721 = 0; j721 < 4; j721 = faust_wrap_add(j721, 1)) {
				fRec334_perm[j721] = fRec334_tmp[faust_wrap_add(vsize, j721)];
			}
			for (int j723 = 0; j723 < 4; j723 = faust_wrap_add(j723, 1)) {
				fRec333_perm[j723] = fRec333_tmp[faust_wrap_add(vsize, j723)];
			}
			for (int j725 = 0; j725 < 4; j725 = faust_wrap_add(j725, 1)) {
				fRec332_perm[j725] = fRec332_tmp[faust_wrap_add(vsize, j725)];
			}
			for (int j727 = 0; j727 < 4; j727 = faust_wrap_add(j727, 1)) {
				fRec331_perm[j727] = fRec331_tmp[faust_wrap_add(vsize, j727)];
			}
			for (int j705 = 0; j705 < 4; j705 = faust_wrap_add(j705, 1)) {
				fRec330_perm[j705] = fRec330_tmp[faust_wrap_add(vsize, j705)];
			}
			for (int j707 = 0; j707 < 4; j707 = faust_wrap_add(j707, 1)) {
				fRec329_perm[j707] = fRec329_tmp[faust_wrap_add(vsize, j707)];
			}
			for (int j709 = 0; j709 < 4; j709 = faust_wrap_add(j709, 1)) {
				fRec328_perm[j709] = fRec328_tmp[faust_wrap_add(vsize, j709)];
			}
			for (int j711 = 0; j711 < 4; j711 = faust_wrap_add(j711, 1)) {
				fRec327_perm[j711] = fRec327_tmp[faust_wrap_add(vsize, j711)];
			}
			for (int j713 = 0; j713 < 4; j713 = faust_wrap_add(j713, 1)) {
				fRec326_perm[j713] = fRec326_tmp[faust_wrap_add(vsize, j713)];
			}
			for (int j701 = 0; j701 < 4; j701 = faust_wrap_add(j701, 1)) {
				fRec325_perm[j701] = fRec325_tmp[faust_wrap_add(vsize, j701)];
			}
			for (int j703 = 0; j703 < 4; j703 = faust_wrap_add(j703, 1)) {
				fRec324_perm[j703] = fRec324_tmp[faust_wrap_add(vsize, j703)];
			}
			for (int j695 = 0; j695 < 4; j695 = faust_wrap_add(j695, 1)) {
				fYec41_perm[j695] = fYec41_tmp[faust_wrap_add(vsize, j695)];
			}
			for (int j691 = 0; j691 < 4; j691 = faust_wrap_add(j691, 1)) {
				fRec323_perm[j691] = fRec323_tmp[faust_wrap_add(vsize, j691)];
			}
			for (int j693 = 0; j693 < 4; j693 = faust_wrap_add(j693, 1)) {
				fRec322_perm[j693] = fRec322_tmp[faust_wrap_add(vsize, j693)];
			}
			for (int j697 = 0; j697 < 4; j697 = faust_wrap_add(j697, 1)) {
				fRec321_perm[j697] = fRec321_tmp[faust_wrap_add(vsize, j697)];
			}
			for (int j699 = 0; j699 < 4; j699 = faust_wrap_add(j699, 1)) {
				fRec320_perm[j699] = fRec320_tmp[faust_wrap_add(vsize, j699)];
			}
			for (int j683 = 0; j683 < 4; j683 = faust_wrap_add(j683, 1)) {
				fYec40_perm[j683] = fYec40_tmp[faust_wrap_add(vsize, j683)];
			}
			for (int j679 = 0; j679 < 4; j679 = faust_wrap_add(j679, 1)) {
				fRec319_perm[j679] = fRec319_tmp[faust_wrap_add(vsize, j679)];
			}
			for (int j681 = 0; j681 < 4; j681 = faust_wrap_add(j681, 1)) {
				fRec318_perm[j681] = fRec318_tmp[faust_wrap_add(vsize, j681)];
			}
			for (int j685 = 0; j685 < 4; j685 = faust_wrap_add(j685, 1)) {
				fRec317_perm[j685] = fRec317_tmp[faust_wrap_add(vsize, j685)];
			}
			for (int j687 = 0; j687 < 4; j687 = faust_wrap_add(j687, 1)) {
				fRec316_perm[j687] = fRec316_tmp[faust_wrap_add(vsize, j687)];
			}
			for (int j689 = 0; j689 < 4; j689 = faust_wrap_add(j689, 1)) {
				fRec315_perm[j689] = fRec315_tmp[faust_wrap_add(vsize, j689)];
			}
			for (int j669 = 0; j669 < 4; j669 = faust_wrap_add(j669, 1)) {
				fYec39_perm[j669] = fYec39_tmp[faust_wrap_add(vsize, j669)];
			}
			for (int j665 = 0; j665 < 4; j665 = faust_wrap_add(j665, 1)) {
				fRec314_perm[j665] = fRec314_tmp[faust_wrap_add(vsize, j665)];
			}
			for (int j667 = 0; j667 < 4; j667 = faust_wrap_add(j667, 1)) {
				fRec313_perm[j667] = fRec313_tmp[faust_wrap_add(vsize, j667)];
			}
			for (int j671 = 0; j671 < 4; j671 = faust_wrap_add(j671, 1)) {
				fRec312_perm[j671] = fRec312_tmp[faust_wrap_add(vsize, j671)];
			}
			for (int j673 = 0; j673 < 4; j673 = faust_wrap_add(j673, 1)) {
				fRec311_perm[j673] = fRec311_tmp[faust_wrap_add(vsize, j673)];
			}
			for (int j675 = 0; j675 < 4; j675 = faust_wrap_add(j675, 1)) {
				fRec310_perm[j675] = fRec310_tmp[faust_wrap_add(vsize, j675)];
			}
			for (int j677 = 0; j677 < 4; j677 = faust_wrap_add(j677, 1)) {
				fRec309_perm[j677] = fRec309_tmp[faust_wrap_add(vsize, j677)];
			}
			for (int j655 = 0; j655 < 4; j655 = faust_wrap_add(j655, 1)) {
				fRec308_perm[j655] = fRec308_tmp[faust_wrap_add(vsize, j655)];
			}
			for (int j657 = 0; j657 < 4; j657 = faust_wrap_add(j657, 1)) {
				fRec307_perm[j657] = fRec307_tmp[faust_wrap_add(vsize, j657)];
			}
			for (int j659 = 0; j659 < 4; j659 = faust_wrap_add(j659, 1)) {
				fRec306_perm[j659] = fRec306_tmp[faust_wrap_add(vsize, j659)];
			}
			for (int j661 = 0; j661 < 4; j661 = faust_wrap_add(j661, 1)) {
				fRec305_perm[j661] = fRec305_tmp[faust_wrap_add(vsize, j661)];
			}
			for (int j663 = 0; j663 < 4; j663 = faust_wrap_add(j663, 1)) {
				fRec304_perm[j663] = fRec304_tmp[faust_wrap_add(vsize, j663)];
			}
			for (int j651 = 0; j651 < 4; j651 = faust_wrap_add(j651, 1)) {
				fRec303_perm[j651] = fRec303_tmp[faust_wrap_add(vsize, j651)];
			}
			for (int j653 = 0; j653 < 4; j653 = faust_wrap_add(j653, 1)) {
				fRec302_perm[j653] = fRec302_tmp[faust_wrap_add(vsize, j653)];
			}
			for (int j645 = 0; j645 < 4; j645 = faust_wrap_add(j645, 1)) {
				fYec38_perm[j645] = fYec38_tmp[faust_wrap_add(vsize, j645)];
			}
			for (int j641 = 0; j641 < 4; j641 = faust_wrap_add(j641, 1)) {
				fRec301_perm[j641] = fRec301_tmp[faust_wrap_add(vsize, j641)];
			}
			for (int j643 = 0; j643 < 4; j643 = faust_wrap_add(j643, 1)) {
				fRec300_perm[j643] = fRec300_tmp[faust_wrap_add(vsize, j643)];
			}
			for (int j647 = 0; j647 < 4; j647 = faust_wrap_add(j647, 1)) {
				fRec299_perm[j647] = fRec299_tmp[faust_wrap_add(vsize, j647)];
			}
			for (int j649 = 0; j649 < 4; j649 = faust_wrap_add(j649, 1)) {
				fRec298_perm[j649] = fRec298_tmp[faust_wrap_add(vsize, j649)];
			}
			for (int j633 = 0; j633 < 4; j633 = faust_wrap_add(j633, 1)) {
				fYec37_perm[j633] = fYec37_tmp[faust_wrap_add(vsize, j633)];
			}
			for (int j629 = 0; j629 < 4; j629 = faust_wrap_add(j629, 1)) {
				fRec297_perm[j629] = fRec297_tmp[faust_wrap_add(vsize, j629)];
			}
			for (int j631 = 0; j631 < 4; j631 = faust_wrap_add(j631, 1)) {
				fRec296_perm[j631] = fRec296_tmp[faust_wrap_add(vsize, j631)];
			}
			for (int j635 = 0; j635 < 4; j635 = faust_wrap_add(j635, 1)) {
				fRec295_perm[j635] = fRec295_tmp[faust_wrap_add(vsize, j635)];
			}
			for (int j637 = 0; j637 < 4; j637 = faust_wrap_add(j637, 1)) {
				fRec294_perm[j637] = fRec294_tmp[faust_wrap_add(vsize, j637)];
			}
			for (int j639 = 0; j639 < 4; j639 = faust_wrap_add(j639, 1)) {
				fRec293_perm[j639] = fRec293_tmp[faust_wrap_add(vsize, j639)];
			}
			for (int j619 = 0; j619 < 4; j619 = faust_wrap_add(j619, 1)) {
				fYec36_perm[j619] = fYec36_tmp[faust_wrap_add(vsize, j619)];
			}
			for (int j615 = 0; j615 < 4; j615 = faust_wrap_add(j615, 1)) {
				fRec292_perm[j615] = fRec292_tmp[faust_wrap_add(vsize, j615)];
			}
			for (int j617 = 0; j617 < 4; j617 = faust_wrap_add(j617, 1)) {
				fRec291_perm[j617] = fRec291_tmp[faust_wrap_add(vsize, j617)];
			}
			for (int j621 = 0; j621 < 4; j621 = faust_wrap_add(j621, 1)) {
				fRec290_perm[j621] = fRec290_tmp[faust_wrap_add(vsize, j621)];
			}
			for (int j623 = 0; j623 < 4; j623 = faust_wrap_add(j623, 1)) {
				fRec289_perm[j623] = fRec289_tmp[faust_wrap_add(vsize, j623)];
			}
			for (int j625 = 0; j625 < 4; j625 = faust_wrap_add(j625, 1)) {
				fRec288_perm[j625] = fRec288_tmp[faust_wrap_add(vsize, j625)];
			}
			for (int j627 = 0; j627 < 4; j627 = faust_wrap_add(j627, 1)) {
				fRec287_perm[j627] = fRec287_tmp[faust_wrap_add(vsize, j627)];
			}
			for (int j605 = 0; j605 < 4; j605 = faust_wrap_add(j605, 1)) {
				fRec286_perm[j605] = fRec286_tmp[faust_wrap_add(vsize, j605)];
			}
			for (int j607 = 0; j607 < 4; j607 = faust_wrap_add(j607, 1)) {
				fRec285_perm[j607] = fRec285_tmp[faust_wrap_add(vsize, j607)];
			}
			for (int j609 = 0; j609 < 4; j609 = faust_wrap_add(j609, 1)) {
				fRec284_perm[j609] = fRec284_tmp[faust_wrap_add(vsize, j609)];
			}
			for (int j611 = 0; j611 < 4; j611 = faust_wrap_add(j611, 1)) {
				fRec283_perm[j611] = fRec283_tmp[faust_wrap_add(vsize, j611)];
			}
			for (int j613 = 0; j613 < 4; j613 = faust_wrap_add(j613, 1)) {
				fRec282_perm[j613] = fRec282_tmp[faust_wrap_add(vsize, j613)];
			}
			for (int j601 = 0; j601 < 4; j601 = faust_wrap_add(j601, 1)) {
				fRec281_perm[j601] = fRec281_tmp[faust_wrap_add(vsize, j601)];
			}
			for (int j603 = 0; j603 < 4; j603 = faust_wrap_add(j603, 1)) {
				fRec280_perm[j603] = fRec280_tmp[faust_wrap_add(vsize, j603)];
			}
			for (int j595 = 0; j595 < 4; j595 = faust_wrap_add(j595, 1)) {
				fYec35_perm[j595] = fYec35_tmp[faust_wrap_add(vsize, j595)];
			}
			for (int j591 = 0; j591 < 4; j591 = faust_wrap_add(j591, 1)) {
				fRec279_perm[j591] = fRec279_tmp[faust_wrap_add(vsize, j591)];
			}
			for (int j593 = 0; j593 < 4; j593 = faust_wrap_add(j593, 1)) {
				fRec278_perm[j593] = fRec278_tmp[faust_wrap_add(vsize, j593)];
			}
			for (int j597 = 0; j597 < 4; j597 = faust_wrap_add(j597, 1)) {
				fRec277_perm[j597] = fRec277_tmp[faust_wrap_add(vsize, j597)];
			}
			for (int j599 = 0; j599 < 4; j599 = faust_wrap_add(j599, 1)) {
				fRec276_perm[j599] = fRec276_tmp[faust_wrap_add(vsize, j599)];
			}
			for (int j583 = 0; j583 < 4; j583 = faust_wrap_add(j583, 1)) {
				fYec34_perm[j583] = fYec34_tmp[faust_wrap_add(vsize, j583)];
			}
			for (int j579 = 0; j579 < 4; j579 = faust_wrap_add(j579, 1)) {
				fRec275_perm[j579] = fRec275_tmp[faust_wrap_add(vsize, j579)];
			}
			for (int j581 = 0; j581 < 4; j581 = faust_wrap_add(j581, 1)) {
				fRec274_perm[j581] = fRec274_tmp[faust_wrap_add(vsize, j581)];
			}
			for (int j585 = 0; j585 < 4; j585 = faust_wrap_add(j585, 1)) {
				fRec273_perm[j585] = fRec273_tmp[faust_wrap_add(vsize, j585)];
			}
			for (int j587 = 0; j587 < 4; j587 = faust_wrap_add(j587, 1)) {
				fRec272_perm[j587] = fRec272_tmp[faust_wrap_add(vsize, j587)];
			}
			for (int j589 = 0; j589 < 4; j589 = faust_wrap_add(j589, 1)) {
				fRec271_perm[j589] = fRec271_tmp[faust_wrap_add(vsize, j589)];
			}
			for (int j569 = 0; j569 < 4; j569 = faust_wrap_add(j569, 1)) {
				fYec33_perm[j569] = fYec33_tmp[faust_wrap_add(vsize, j569)];
			}
			for (int j565 = 0; j565 < 4; j565 = faust_wrap_add(j565, 1)) {
				fRec270_perm[j565] = fRec270_tmp[faust_wrap_add(vsize, j565)];
			}
			for (int j567 = 0; j567 < 4; j567 = faust_wrap_add(j567, 1)) {
				fRec269_perm[j567] = fRec269_tmp[faust_wrap_add(vsize, j567)];
			}
			for (int j571 = 0; j571 < 4; j571 = faust_wrap_add(j571, 1)) {
				fRec268_perm[j571] = fRec268_tmp[faust_wrap_add(vsize, j571)];
			}
			for (int j573 = 0; j573 < 4; j573 = faust_wrap_add(j573, 1)) {
				fRec267_perm[j573] = fRec267_tmp[faust_wrap_add(vsize, j573)];
			}
			for (int j575 = 0; j575 < 4; j575 = faust_wrap_add(j575, 1)) {
				fRec266_perm[j575] = fRec266_tmp[faust_wrap_add(vsize, j575)];
			}
			for (int j577 = 0; j577 < 4; j577 = faust_wrap_add(j577, 1)) {
				fRec265_perm[j577] = fRec265_tmp[faust_wrap_add(vsize, j577)];
			}
			for (int j555 = 0; j555 < 4; j555 = faust_wrap_add(j555, 1)) {
				fRec264_perm[j555] = fRec264_tmp[faust_wrap_add(vsize, j555)];
			}
			for (int j557 = 0; j557 < 4; j557 = faust_wrap_add(j557, 1)) {
				fRec263_perm[j557] = fRec263_tmp[faust_wrap_add(vsize, j557)];
			}
			for (int j559 = 0; j559 < 4; j559 = faust_wrap_add(j559, 1)) {
				fRec262_perm[j559] = fRec262_tmp[faust_wrap_add(vsize, j559)];
			}
			for (int j561 = 0; j561 < 4; j561 = faust_wrap_add(j561, 1)) {
				fRec261_perm[j561] = fRec261_tmp[faust_wrap_add(vsize, j561)];
			}
			for (int j563 = 0; j563 < 4; j563 = faust_wrap_add(j563, 1)) {
				fRec260_perm[j563] = fRec260_tmp[faust_wrap_add(vsize, j563)];
			}
			for (int j551 = 0; j551 < 4; j551 = faust_wrap_add(j551, 1)) {
				fRec259_perm[j551] = fRec259_tmp[faust_wrap_add(vsize, j551)];
			}
			for (int j553 = 0; j553 < 4; j553 = faust_wrap_add(j553, 1)) {
				fRec258_perm[j553] = fRec258_tmp[faust_wrap_add(vsize, j553)];
			}
			for (int j545 = 0; j545 < 4; j545 = faust_wrap_add(j545, 1)) {
				fYec32_perm[j545] = fYec32_tmp[faust_wrap_add(vsize, j545)];
			}
			for (int j541 = 0; j541 < 4; j541 = faust_wrap_add(j541, 1)) {
				fRec257_perm[j541] = fRec257_tmp[faust_wrap_add(vsize, j541)];
			}
			for (int j543 = 0; j543 < 4; j543 = faust_wrap_add(j543, 1)) {
				fRec256_perm[j543] = fRec256_tmp[faust_wrap_add(vsize, j543)];
			}
			for (int j547 = 0; j547 < 4; j547 = faust_wrap_add(j547, 1)) {
				fRec255_perm[j547] = fRec255_tmp[faust_wrap_add(vsize, j547)];
			}
			for (int j549 = 0; j549 < 4; j549 = faust_wrap_add(j549, 1)) {
				fRec254_perm[j549] = fRec254_tmp[faust_wrap_add(vsize, j549)];
			}
			for (int j533 = 0; j533 < 4; j533 = faust_wrap_add(j533, 1)) {
				fYec31_perm[j533] = fYec31_tmp[faust_wrap_add(vsize, j533)];
			}
			for (int j529 = 0; j529 < 4; j529 = faust_wrap_add(j529, 1)) {
				fRec253_perm[j529] = fRec253_tmp[faust_wrap_add(vsize, j529)];
			}
			for (int j531 = 0; j531 < 4; j531 = faust_wrap_add(j531, 1)) {
				fRec252_perm[j531] = fRec252_tmp[faust_wrap_add(vsize, j531)];
			}
			for (int j535 = 0; j535 < 4; j535 = faust_wrap_add(j535, 1)) {
				fRec251_perm[j535] = fRec251_tmp[faust_wrap_add(vsize, j535)];
			}
			for (int j537 = 0; j537 < 4; j537 = faust_wrap_add(j537, 1)) {
				fRec250_perm[j537] = fRec250_tmp[faust_wrap_add(vsize, j537)];
			}
			for (int j539 = 0; j539 < 4; j539 = faust_wrap_add(j539, 1)) {
				fRec249_perm[j539] = fRec249_tmp[faust_wrap_add(vsize, j539)];
			}
			for (int j519 = 0; j519 < 4; j519 = faust_wrap_add(j519, 1)) {
				fYec30_perm[j519] = fYec30_tmp[faust_wrap_add(vsize, j519)];
			}
			for (int j515 = 0; j515 < 4; j515 = faust_wrap_add(j515, 1)) {
				fRec248_perm[j515] = fRec248_tmp[faust_wrap_add(vsize, j515)];
			}
			for (int j517 = 0; j517 < 4; j517 = faust_wrap_add(j517, 1)) {
				fRec247_perm[j517] = fRec247_tmp[faust_wrap_add(vsize, j517)];
			}
			for (int j521 = 0; j521 < 4; j521 = faust_wrap_add(j521, 1)) {
				fRec246_perm[j521] = fRec246_tmp[faust_wrap_add(vsize, j521)];
			}
			for (int j523 = 0; j523 < 4; j523 = faust_wrap_add(j523, 1)) {
				fRec245_perm[j523] = fRec245_tmp[faust_wrap_add(vsize, j523)];
			}
			for (int j525 = 0; j525 < 4; j525 = faust_wrap_add(j525, 1)) {
				fRec244_perm[j525] = fRec244_tmp[faust_wrap_add(vsize, j525)];
			}
			for (int j527 = 0; j527 < 4; j527 = faust_wrap_add(j527, 1)) {
				fRec243_perm[j527] = fRec243_tmp[faust_wrap_add(vsize, j527)];
			}
			for (int j505 = 0; j505 < 4; j505 = faust_wrap_add(j505, 1)) {
				fRec242_perm[j505] = fRec242_tmp[faust_wrap_add(vsize, j505)];
			}
			for (int j507 = 0; j507 < 4; j507 = faust_wrap_add(j507, 1)) {
				fRec241_perm[j507] = fRec241_tmp[faust_wrap_add(vsize, j507)];
			}
			for (int j509 = 0; j509 < 4; j509 = faust_wrap_add(j509, 1)) {
				fRec240_perm[j509] = fRec240_tmp[faust_wrap_add(vsize, j509)];
			}
			for (int j511 = 0; j511 < 4; j511 = faust_wrap_add(j511, 1)) {
				fRec239_perm[j511] = fRec239_tmp[faust_wrap_add(vsize, j511)];
			}
			for (int j513 = 0; j513 < 4; j513 = faust_wrap_add(j513, 1)) {
				fRec238_perm[j513] = fRec238_tmp[faust_wrap_add(vsize, j513)];
			}
			for (int j501 = 0; j501 < 4; j501 = faust_wrap_add(j501, 1)) {
				fRec237_perm[j501] = fRec237_tmp[faust_wrap_add(vsize, j501)];
			}
			for (int j503 = 0; j503 < 4; j503 = faust_wrap_add(j503, 1)) {
				fRec236_perm[j503] = fRec236_tmp[faust_wrap_add(vsize, j503)];
			}
			for (int j495 = 0; j495 < 4; j495 = faust_wrap_add(j495, 1)) {
				fYec29_perm[j495] = fYec29_tmp[faust_wrap_add(vsize, j495)];
			}
			for (int j491 = 0; j491 < 4; j491 = faust_wrap_add(j491, 1)) {
				fRec235_perm[j491] = fRec235_tmp[faust_wrap_add(vsize, j491)];
			}
			for (int j493 = 0; j493 < 4; j493 = faust_wrap_add(j493, 1)) {
				fRec234_perm[j493] = fRec234_tmp[faust_wrap_add(vsize, j493)];
			}
			for (int j497 = 0; j497 < 4; j497 = faust_wrap_add(j497, 1)) {
				fRec233_perm[j497] = fRec233_tmp[faust_wrap_add(vsize, j497)];
			}
			for (int j499 = 0; j499 < 4; j499 = faust_wrap_add(j499, 1)) {
				fRec232_perm[j499] = fRec232_tmp[faust_wrap_add(vsize, j499)];
			}
			for (int j483 = 0; j483 < 4; j483 = faust_wrap_add(j483, 1)) {
				fYec28_perm[j483] = fYec28_tmp[faust_wrap_add(vsize, j483)];
			}
			for (int j479 = 0; j479 < 4; j479 = faust_wrap_add(j479, 1)) {
				fRec231_perm[j479] = fRec231_tmp[faust_wrap_add(vsize, j479)];
			}
			for (int j481 = 0; j481 < 4; j481 = faust_wrap_add(j481, 1)) {
				fRec230_perm[j481] = fRec230_tmp[faust_wrap_add(vsize, j481)];
			}
			for (int j485 = 0; j485 < 4; j485 = faust_wrap_add(j485, 1)) {
				fRec229_perm[j485] = fRec229_tmp[faust_wrap_add(vsize, j485)];
			}
			for (int j487 = 0; j487 < 4; j487 = faust_wrap_add(j487, 1)) {
				fRec228_perm[j487] = fRec228_tmp[faust_wrap_add(vsize, j487)];
			}
			for (int j489 = 0; j489 < 4; j489 = faust_wrap_add(j489, 1)) {
				fRec227_perm[j489] = fRec227_tmp[faust_wrap_add(vsize, j489)];
			}
			for (int j469 = 0; j469 < 4; j469 = faust_wrap_add(j469, 1)) {
				fYec27_perm[j469] = fYec27_tmp[faust_wrap_add(vsize, j469)];
			}
			for (int j465 = 0; j465 < 4; j465 = faust_wrap_add(j465, 1)) {
				fRec226_perm[j465] = fRec226_tmp[faust_wrap_add(vsize, j465)];
			}
			for (int j467 = 0; j467 < 4; j467 = faust_wrap_add(j467, 1)) {
				fRec225_perm[j467] = fRec225_tmp[faust_wrap_add(vsize, j467)];
			}
			for (int j471 = 0; j471 < 4; j471 = faust_wrap_add(j471, 1)) {
				fRec224_perm[j471] = fRec224_tmp[faust_wrap_add(vsize, j471)];
			}
			for (int j473 = 0; j473 < 4; j473 = faust_wrap_add(j473, 1)) {
				fRec223_perm[j473] = fRec223_tmp[faust_wrap_add(vsize, j473)];
			}
			for (int j475 = 0; j475 < 4; j475 = faust_wrap_add(j475, 1)) {
				fRec222_perm[j475] = fRec222_tmp[faust_wrap_add(vsize, j475)];
			}
			for (int j477 = 0; j477 < 4; j477 = faust_wrap_add(j477, 1)) {
				fRec221_perm[j477] = fRec221_tmp[faust_wrap_add(vsize, j477)];
			}
			for (int j455 = 0; j455 < 4; j455 = faust_wrap_add(j455, 1)) {
				fRec220_perm[j455] = fRec220_tmp[faust_wrap_add(vsize, j455)];
			}
			for (int j457 = 0; j457 < 4; j457 = faust_wrap_add(j457, 1)) {
				fRec219_perm[j457] = fRec219_tmp[faust_wrap_add(vsize, j457)];
			}
			for (int j459 = 0; j459 < 4; j459 = faust_wrap_add(j459, 1)) {
				fRec218_perm[j459] = fRec218_tmp[faust_wrap_add(vsize, j459)];
			}
			for (int j461 = 0; j461 < 4; j461 = faust_wrap_add(j461, 1)) {
				fRec217_perm[j461] = fRec217_tmp[faust_wrap_add(vsize, j461)];
			}
			for (int j463 = 0; j463 < 4; j463 = faust_wrap_add(j463, 1)) {
				fRec216_perm[j463] = fRec216_tmp[faust_wrap_add(vsize, j463)];
			}
			for (int j451 = 0; j451 < 4; j451 = faust_wrap_add(j451, 1)) {
				fRec215_perm[j451] = fRec215_tmp[faust_wrap_add(vsize, j451)];
			}
			for (int j453 = 0; j453 < 4; j453 = faust_wrap_add(j453, 1)) {
				fRec214_perm[j453] = fRec214_tmp[faust_wrap_add(vsize, j453)];
			}
			for (int j445 = 0; j445 < 4; j445 = faust_wrap_add(j445, 1)) {
				fYec26_perm[j445] = fYec26_tmp[faust_wrap_add(vsize, j445)];
			}
			for (int j441 = 0; j441 < 4; j441 = faust_wrap_add(j441, 1)) {
				fRec213_perm[j441] = fRec213_tmp[faust_wrap_add(vsize, j441)];
			}
			for (int j443 = 0; j443 < 4; j443 = faust_wrap_add(j443, 1)) {
				fRec212_perm[j443] = fRec212_tmp[faust_wrap_add(vsize, j443)];
			}
			for (int j447 = 0; j447 < 4; j447 = faust_wrap_add(j447, 1)) {
				fRec211_perm[j447] = fRec211_tmp[faust_wrap_add(vsize, j447)];
			}
			for (int j449 = 0; j449 < 4; j449 = faust_wrap_add(j449, 1)) {
				fRec210_perm[j449] = fRec210_tmp[faust_wrap_add(vsize, j449)];
			}
			for (int j433 = 0; j433 < 4; j433 = faust_wrap_add(j433, 1)) {
				fYec25_perm[j433] = fYec25_tmp[faust_wrap_add(vsize, j433)];
			}
			for (int j429 = 0; j429 < 4; j429 = faust_wrap_add(j429, 1)) {
				fRec209_perm[j429] = fRec209_tmp[faust_wrap_add(vsize, j429)];
			}
			for (int j431 = 0; j431 < 4; j431 = faust_wrap_add(j431, 1)) {
				fRec208_perm[j431] = fRec208_tmp[faust_wrap_add(vsize, j431)];
			}
			for (int j435 = 0; j435 < 4; j435 = faust_wrap_add(j435, 1)) {
				fRec207_perm[j435] = fRec207_tmp[faust_wrap_add(vsize, j435)];
			}
			for (int j437 = 0; j437 < 4; j437 = faust_wrap_add(j437, 1)) {
				fRec206_perm[j437] = fRec206_tmp[faust_wrap_add(vsize, j437)];
			}
			for (int j439 = 0; j439 < 4; j439 = faust_wrap_add(j439, 1)) {
				fRec205_perm[j439] = fRec205_tmp[faust_wrap_add(vsize, j439)];
			}
			for (int j419 = 0; j419 < 4; j419 = faust_wrap_add(j419, 1)) {
				fYec24_perm[j419] = fYec24_tmp[faust_wrap_add(vsize, j419)];
			}
			for (int j415 = 0; j415 < 4; j415 = faust_wrap_add(j415, 1)) {
				fRec204_perm[j415] = fRec204_tmp[faust_wrap_add(vsize, j415)];
			}
			for (int j417 = 0; j417 < 4; j417 = faust_wrap_add(j417, 1)) {
				fRec203_perm[j417] = fRec203_tmp[faust_wrap_add(vsize, j417)];
			}
			for (int j421 = 0; j421 < 4; j421 = faust_wrap_add(j421, 1)) {
				fRec202_perm[j421] = fRec202_tmp[faust_wrap_add(vsize, j421)];
			}
			for (int j423 = 0; j423 < 4; j423 = faust_wrap_add(j423, 1)) {
				fRec201_perm[j423] = fRec201_tmp[faust_wrap_add(vsize, j423)];
			}
			for (int j425 = 0; j425 < 4; j425 = faust_wrap_add(j425, 1)) {
				fRec200_perm[j425] = fRec200_tmp[faust_wrap_add(vsize, j425)];
			}
			for (int j427 = 0; j427 < 4; j427 = faust_wrap_add(j427, 1)) {
				fRec199_perm[j427] = fRec199_tmp[faust_wrap_add(vsize, j427)];
			}
			for (int j405 = 0; j405 < 4; j405 = faust_wrap_add(j405, 1)) {
				fRec198_perm[j405] = fRec198_tmp[faust_wrap_add(vsize, j405)];
			}
			for (int j407 = 0; j407 < 4; j407 = faust_wrap_add(j407, 1)) {
				fRec197_perm[j407] = fRec197_tmp[faust_wrap_add(vsize, j407)];
			}
			for (int j409 = 0; j409 < 4; j409 = faust_wrap_add(j409, 1)) {
				fRec196_perm[j409] = fRec196_tmp[faust_wrap_add(vsize, j409)];
			}
			for (int j411 = 0; j411 < 4; j411 = faust_wrap_add(j411, 1)) {
				fRec195_perm[j411] = fRec195_tmp[faust_wrap_add(vsize, j411)];
			}
			for (int j413 = 0; j413 < 4; j413 = faust_wrap_add(j413, 1)) {
				fRec194_perm[j413] = fRec194_tmp[faust_wrap_add(vsize, j413)];
			}
			for (int j401 = 0; j401 < 4; j401 = faust_wrap_add(j401, 1)) {
				fRec193_perm[j401] = fRec193_tmp[faust_wrap_add(vsize, j401)];
			}
			for (int j403 = 0; j403 < 4; j403 = faust_wrap_add(j403, 1)) {
				fRec192_perm[j403] = fRec192_tmp[faust_wrap_add(vsize, j403)];
			}
			for (int j395 = 0; j395 < 4; j395 = faust_wrap_add(j395, 1)) {
				fYec23_perm[j395] = fYec23_tmp[faust_wrap_add(vsize, j395)];
			}
			for (int j391 = 0; j391 < 4; j391 = faust_wrap_add(j391, 1)) {
				fRec191_perm[j391] = fRec191_tmp[faust_wrap_add(vsize, j391)];
			}
			for (int j393 = 0; j393 < 4; j393 = faust_wrap_add(j393, 1)) {
				fRec190_perm[j393] = fRec190_tmp[faust_wrap_add(vsize, j393)];
			}
			for (int j397 = 0; j397 < 4; j397 = faust_wrap_add(j397, 1)) {
				fRec189_perm[j397] = fRec189_tmp[faust_wrap_add(vsize, j397)];
			}
			for (int j399 = 0; j399 < 4; j399 = faust_wrap_add(j399, 1)) {
				fRec188_perm[j399] = fRec188_tmp[faust_wrap_add(vsize, j399)];
			}
			for (int j383 = 0; j383 < 4; j383 = faust_wrap_add(j383, 1)) {
				fYec22_perm[j383] = fYec22_tmp[faust_wrap_add(vsize, j383)];
			}
			for (int j379 = 0; j379 < 4; j379 = faust_wrap_add(j379, 1)) {
				fRec187_perm[j379] = fRec187_tmp[faust_wrap_add(vsize, j379)];
			}
			for (int j381 = 0; j381 < 4; j381 = faust_wrap_add(j381, 1)) {
				fRec186_perm[j381] = fRec186_tmp[faust_wrap_add(vsize, j381)];
			}
			for (int j385 = 0; j385 < 4; j385 = faust_wrap_add(j385, 1)) {
				fRec185_perm[j385] = fRec185_tmp[faust_wrap_add(vsize, j385)];
			}
			for (int j387 = 0; j387 < 4; j387 = faust_wrap_add(j387, 1)) {
				fRec184_perm[j387] = fRec184_tmp[faust_wrap_add(vsize, j387)];
			}
			for (int j389 = 0; j389 < 4; j389 = faust_wrap_add(j389, 1)) {
				fRec183_perm[j389] = fRec183_tmp[faust_wrap_add(vsize, j389)];
			}
			for (int j369 = 0; j369 < 4; j369 = faust_wrap_add(j369, 1)) {
				fYec21_perm[j369] = fYec21_tmp[faust_wrap_add(vsize, j369)];
			}
			for (int j365 = 0; j365 < 4; j365 = faust_wrap_add(j365, 1)) {
				fRec182_perm[j365] = fRec182_tmp[faust_wrap_add(vsize, j365)];
			}
			for (int j367 = 0; j367 < 4; j367 = faust_wrap_add(j367, 1)) {
				fRec181_perm[j367] = fRec181_tmp[faust_wrap_add(vsize, j367)];
			}
			for (int j371 = 0; j371 < 4; j371 = faust_wrap_add(j371, 1)) {
				fRec180_perm[j371] = fRec180_tmp[faust_wrap_add(vsize, j371)];
			}
			for (int j373 = 0; j373 < 4; j373 = faust_wrap_add(j373, 1)) {
				fRec179_perm[j373] = fRec179_tmp[faust_wrap_add(vsize, j373)];
			}
			for (int j375 = 0; j375 < 4; j375 = faust_wrap_add(j375, 1)) {
				fRec178_perm[j375] = fRec178_tmp[faust_wrap_add(vsize, j375)];
			}
			for (int j377 = 0; j377 < 4; j377 = faust_wrap_add(j377, 1)) {
				fRec177_perm[j377] = fRec177_tmp[faust_wrap_add(vsize, j377)];
			}
			for (int j355 = 0; j355 < 4; j355 = faust_wrap_add(j355, 1)) {
				fRec176_perm[j355] = fRec176_tmp[faust_wrap_add(vsize, j355)];
			}
			for (int j357 = 0; j357 < 4; j357 = faust_wrap_add(j357, 1)) {
				fRec175_perm[j357] = fRec175_tmp[faust_wrap_add(vsize, j357)];
			}
			for (int j359 = 0; j359 < 4; j359 = faust_wrap_add(j359, 1)) {
				fRec174_perm[j359] = fRec174_tmp[faust_wrap_add(vsize, j359)];
			}
			for (int j361 = 0; j361 < 4; j361 = faust_wrap_add(j361, 1)) {
				fRec173_perm[j361] = fRec173_tmp[faust_wrap_add(vsize, j361)];
			}
			for (int j363 = 0; j363 < 4; j363 = faust_wrap_add(j363, 1)) {
				fRec172_perm[j363] = fRec172_tmp[faust_wrap_add(vsize, j363)];
			}
			for (int j351 = 0; j351 < 4; j351 = faust_wrap_add(j351, 1)) {
				fRec171_perm[j351] = fRec171_tmp[faust_wrap_add(vsize, j351)];
			}
			for (int j353 = 0; j353 < 4; j353 = faust_wrap_add(j353, 1)) {
				fRec170_perm[j353] = fRec170_tmp[faust_wrap_add(vsize, j353)];
			}
			for (int j345 = 0; j345 < 4; j345 = faust_wrap_add(j345, 1)) {
				fYec20_perm[j345] = fYec20_tmp[faust_wrap_add(vsize, j345)];
			}
			for (int j341 = 0; j341 < 4; j341 = faust_wrap_add(j341, 1)) {
				fRec169_perm[j341] = fRec169_tmp[faust_wrap_add(vsize, j341)];
			}
			for (int j343 = 0; j343 < 4; j343 = faust_wrap_add(j343, 1)) {
				fRec168_perm[j343] = fRec168_tmp[faust_wrap_add(vsize, j343)];
			}
			for (int j347 = 0; j347 < 4; j347 = faust_wrap_add(j347, 1)) {
				fRec167_perm[j347] = fRec167_tmp[faust_wrap_add(vsize, j347)];
			}
			for (int j349 = 0; j349 < 4; j349 = faust_wrap_add(j349, 1)) {
				fRec166_perm[j349] = fRec166_tmp[faust_wrap_add(vsize, j349)];
			}
			for (int j333 = 0; j333 < 4; j333 = faust_wrap_add(j333, 1)) {
				fYec19_perm[j333] = fYec19_tmp[faust_wrap_add(vsize, j333)];
			}
			for (int j329 = 0; j329 < 4; j329 = faust_wrap_add(j329, 1)) {
				fRec165_perm[j329] = fRec165_tmp[faust_wrap_add(vsize, j329)];
			}
			for (int j331 = 0; j331 < 4; j331 = faust_wrap_add(j331, 1)) {
				fRec164_perm[j331] = fRec164_tmp[faust_wrap_add(vsize, j331)];
			}
			for (int j335 = 0; j335 < 4; j335 = faust_wrap_add(j335, 1)) {
				fRec163_perm[j335] = fRec163_tmp[faust_wrap_add(vsize, j335)];
			}
			for (int j337 = 0; j337 < 4; j337 = faust_wrap_add(j337, 1)) {
				fRec162_perm[j337] = fRec162_tmp[faust_wrap_add(vsize, j337)];
			}
			for (int j339 = 0; j339 < 4; j339 = faust_wrap_add(j339, 1)) {
				fRec161_perm[j339] = fRec161_tmp[faust_wrap_add(vsize, j339)];
			}
			for (int j319 = 0; j319 < 4; j319 = faust_wrap_add(j319, 1)) {
				fYec18_perm[j319] = fYec18_tmp[faust_wrap_add(vsize, j319)];
			}
			for (int j315 = 0; j315 < 4; j315 = faust_wrap_add(j315, 1)) {
				fRec160_perm[j315] = fRec160_tmp[faust_wrap_add(vsize, j315)];
			}
			for (int j317 = 0; j317 < 4; j317 = faust_wrap_add(j317, 1)) {
				fRec159_perm[j317] = fRec159_tmp[faust_wrap_add(vsize, j317)];
			}
			for (int j321 = 0; j321 < 4; j321 = faust_wrap_add(j321, 1)) {
				fRec158_perm[j321] = fRec158_tmp[faust_wrap_add(vsize, j321)];
			}
			for (int j323 = 0; j323 < 4; j323 = faust_wrap_add(j323, 1)) {
				fRec157_perm[j323] = fRec157_tmp[faust_wrap_add(vsize, j323)];
			}
			for (int j325 = 0; j325 < 4; j325 = faust_wrap_add(j325, 1)) {
				fRec156_perm[j325] = fRec156_tmp[faust_wrap_add(vsize, j325)];
			}
			for (int j327 = 0; j327 < 4; j327 = faust_wrap_add(j327, 1)) {
				fRec155_perm[j327] = fRec155_tmp[faust_wrap_add(vsize, j327)];
			}
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec154_perm[j305] = fRec154_tmp[faust_wrap_add(vsize, j305)];
			}
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec153_perm[j307] = fRec153_tmp[faust_wrap_add(vsize, j307)];
			}
			for (int j309 = 0; j309 < 4; j309 = faust_wrap_add(j309, 1)) {
				fRec152_perm[j309] = fRec152_tmp[faust_wrap_add(vsize, j309)];
			}
			for (int j311 = 0; j311 < 4; j311 = faust_wrap_add(j311, 1)) {
				fRec151_perm[j311] = fRec151_tmp[faust_wrap_add(vsize, j311)];
			}
			for (int j313 = 0; j313 < 4; j313 = faust_wrap_add(j313, 1)) {
				fRec150_perm[j313] = fRec150_tmp[faust_wrap_add(vsize, j313)];
			}
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec149_perm[j301] = fRec149_tmp[faust_wrap_add(vsize, j301)];
			}
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec148_perm[j303] = fRec148_tmp[faust_wrap_add(vsize, j303)];
			}
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fYec17_perm[j295] = fYec17_tmp[faust_wrap_add(vsize, j295)];
			}
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec147_perm[j291] = fRec147_tmp[faust_wrap_add(vsize, j291)];
			}
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec146_perm[j293] = fRec146_tmp[faust_wrap_add(vsize, j293)];
			}
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec145_perm[j297] = fRec145_tmp[faust_wrap_add(vsize, j297)];
			}
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec144_perm[j299] = fRec144_tmp[faust_wrap_add(vsize, j299)];
			}
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fYec16_perm[j283] = fYec16_tmp[faust_wrap_add(vsize, j283)];
			}
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec143_perm[j279] = fRec143_tmp[faust_wrap_add(vsize, j279)];
			}
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec142_perm[j281] = fRec142_tmp[faust_wrap_add(vsize, j281)];
			}
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec141_perm[j285] = fRec141_tmp[faust_wrap_add(vsize, j285)];
			}
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec140_perm[j287] = fRec140_tmp[faust_wrap_add(vsize, j287)];
			}
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec139_perm[j289] = fRec139_tmp[faust_wrap_add(vsize, j289)];
			}
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fYec15_perm[j269] = fYec15_tmp[faust_wrap_add(vsize, j269)];
			}
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec138_perm[j265] = fRec138_tmp[faust_wrap_add(vsize, j265)];
			}
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec137_perm[j267] = fRec137_tmp[faust_wrap_add(vsize, j267)];
			}
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec136_perm[j271] = fRec136_tmp[faust_wrap_add(vsize, j271)];
			}
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec135_perm[j273] = fRec135_tmp[faust_wrap_add(vsize, j273)];
			}
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec134_perm[j275] = fRec134_tmp[faust_wrap_add(vsize, j275)];
			}
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec133_perm[j277] = fRec133_tmp[faust_wrap_add(vsize, j277)];
			}
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec132_perm[j255] = fRec132_tmp[faust_wrap_add(vsize, j255)];
			}
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec131_perm[j257] = fRec131_tmp[faust_wrap_add(vsize, j257)];
			}
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec130_perm[j259] = fRec130_tmp[faust_wrap_add(vsize, j259)];
			}
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec129_perm[j261] = fRec129_tmp[faust_wrap_add(vsize, j261)];
			}
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec128_perm[j263] = fRec128_tmp[faust_wrap_add(vsize, j263)];
			}
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec127_perm[j251] = fRec127_tmp[faust_wrap_add(vsize, j251)];
			}
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec126_perm[j253] = fRec126_tmp[faust_wrap_add(vsize, j253)];
			}
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fYec14_perm[j245] = fYec14_tmp[faust_wrap_add(vsize, j245)];
			}
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec125_perm[j241] = fRec125_tmp[faust_wrap_add(vsize, j241)];
			}
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec124_perm[j243] = fRec124_tmp[faust_wrap_add(vsize, j243)];
			}
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec123_perm[j247] = fRec123_tmp[faust_wrap_add(vsize, j247)];
			}
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec122_perm[j249] = fRec122_tmp[faust_wrap_add(vsize, j249)];
			}
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fYec13_perm[j233] = fYec13_tmp[faust_wrap_add(vsize, j233)];
			}
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec121_perm[j229] = fRec121_tmp[faust_wrap_add(vsize, j229)];
			}
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec120_perm[j231] = fRec120_tmp[faust_wrap_add(vsize, j231)];
			}
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec119_perm[j235] = fRec119_tmp[faust_wrap_add(vsize, j235)];
			}
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec118_perm[j237] = fRec118_tmp[faust_wrap_add(vsize, j237)];
			}
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec117_perm[j239] = fRec117_tmp[faust_wrap_add(vsize, j239)];
			}
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fYec12_perm[j219] = fYec12_tmp[faust_wrap_add(vsize, j219)];
			}
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec116_perm[j215] = fRec116_tmp[faust_wrap_add(vsize, j215)];
			}
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec115_perm[j217] = fRec115_tmp[faust_wrap_add(vsize, j217)];
			}
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec114_perm[j221] = fRec114_tmp[faust_wrap_add(vsize, j221)];
			}
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec113_perm[j223] = fRec113_tmp[faust_wrap_add(vsize, j223)];
			}
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec112_perm[j225] = fRec112_tmp[faust_wrap_add(vsize, j225)];
			}
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec111_perm[j227] = fRec111_tmp[faust_wrap_add(vsize, j227)];
			}
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec110_perm[j205] = fRec110_tmp[faust_wrap_add(vsize, j205)];
			}
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec109_perm[j207] = fRec109_tmp[faust_wrap_add(vsize, j207)];
			}
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec108_perm[j209] = fRec108_tmp[faust_wrap_add(vsize, j209)];
			}
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec107_perm[j211] = fRec107_tmp[faust_wrap_add(vsize, j211)];
			}
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec106_perm[j213] = fRec106_tmp[faust_wrap_add(vsize, j213)];
			}
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec105_perm[j201] = fRec105_tmp[faust_wrap_add(vsize, j201)];
			}
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec104_perm[j203] = fRec104_tmp[faust_wrap_add(vsize, j203)];
			}
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fYec11_perm[j195] = fYec11_tmp[faust_wrap_add(vsize, j195)];
			}
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec103_perm[j191] = fRec103_tmp[faust_wrap_add(vsize, j191)];
			}
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec102_perm[j193] = fRec102_tmp[faust_wrap_add(vsize, j193)];
			}
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec101_perm[j197] = fRec101_tmp[faust_wrap_add(vsize, j197)];
			}
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec100_perm[j199] = fRec100_tmp[faust_wrap_add(vsize, j199)];
			}
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fYec10_perm[j183] = fYec10_tmp[faust_wrap_add(vsize, j183)];
			}
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec99_perm[j179] = fRec99_tmp[faust_wrap_add(vsize, j179)];
			}
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec98_perm[j181] = fRec98_tmp[faust_wrap_add(vsize, j181)];
			}
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec97_perm[j185] = fRec97_tmp[faust_wrap_add(vsize, j185)];
			}
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec96_perm[j187] = fRec96_tmp[faust_wrap_add(vsize, j187)];
			}
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec95_perm[j189] = fRec95_tmp[faust_wrap_add(vsize, j189)];
			}
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fYec9_perm[j169] = fYec9_tmp[faust_wrap_add(vsize, j169)];
			}
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec94_perm[j165] = fRec94_tmp[faust_wrap_add(vsize, j165)];
			}
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec93_perm[j167] = fRec93_tmp[faust_wrap_add(vsize, j167)];
			}
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec92_perm[j171] = fRec92_tmp[faust_wrap_add(vsize, j171)];
			}
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec91_perm[j173] = fRec91_tmp[faust_wrap_add(vsize, j173)];
			}
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec90_perm[j175] = fRec90_tmp[faust_wrap_add(vsize, j175)];
			}
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec89_perm[j177] = fRec89_tmp[faust_wrap_add(vsize, j177)];
			}
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec88_perm[j155] = fRec88_tmp[faust_wrap_add(vsize, j155)];
			}
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec87_perm[j157] = fRec87_tmp[faust_wrap_add(vsize, j157)];
			}
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec86_perm[j159] = fRec86_tmp[faust_wrap_add(vsize, j159)];
			}
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec85_perm[j161] = fRec85_tmp[faust_wrap_add(vsize, j161)];
			}
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec84_perm[j163] = fRec84_tmp[faust_wrap_add(vsize, j163)];
			}
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec83_perm[j151] = fRec83_tmp[faust_wrap_add(vsize, j151)];
			}
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec82_perm[j153] = fRec82_tmp[faust_wrap_add(vsize, j153)];
			}
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fYec8_perm[j145] = fYec8_tmp[faust_wrap_add(vsize, j145)];
			}
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec81_perm[j141] = fRec81_tmp[faust_wrap_add(vsize, j141)];
			}
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec80_perm[j143] = fRec80_tmp[faust_wrap_add(vsize, j143)];
			}
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec79_perm[j147] = fRec79_tmp[faust_wrap_add(vsize, j147)];
			}
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec78_perm[j149] = fRec78_tmp[faust_wrap_add(vsize, j149)];
			}
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fYec7_perm[j133] = fYec7_tmp[faust_wrap_add(vsize, j133)];
			}
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec77_perm[j129] = fRec77_tmp[faust_wrap_add(vsize, j129)];
			}
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec76_perm[j131] = fRec76_tmp[faust_wrap_add(vsize, j131)];
			}
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec75_perm[j135] = fRec75_tmp[faust_wrap_add(vsize, j135)];
			}
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec74_perm[j137] = fRec74_tmp[faust_wrap_add(vsize, j137)];
			}
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec73_perm[j139] = fRec73_tmp[faust_wrap_add(vsize, j139)];
			}
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fYec6_perm[j119] = fYec6_tmp[faust_wrap_add(vsize, j119)];
			}
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec72_perm[j115] = fRec72_tmp[faust_wrap_add(vsize, j115)];
			}
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec71_perm[j117] = fRec71_tmp[faust_wrap_add(vsize, j117)];
			}
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec70_perm[j121] = fRec70_tmp[faust_wrap_add(vsize, j121)];
			}
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec69_perm[j123] = fRec69_tmp[faust_wrap_add(vsize, j123)];
			}
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec68_perm[j125] = fRec68_tmp[faust_wrap_add(vsize, j125)];
			}
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec67_perm[j127] = fRec67_tmp[faust_wrap_add(vsize, j127)];
			}
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec66_perm[j105] = fRec66_tmp[faust_wrap_add(vsize, j105)];
			}
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec65_perm[j107] = fRec65_tmp[faust_wrap_add(vsize, j107)];
			}
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec64_perm[j109] = fRec64_tmp[faust_wrap_add(vsize, j109)];
			}
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec63_perm[j111] = fRec63_tmp[faust_wrap_add(vsize, j111)];
			}
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec62_perm[j113] = fRec62_tmp[faust_wrap_add(vsize, j113)];
			}
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec61_perm[j101] = fRec61_tmp[faust_wrap_add(vsize, j101)];
			}
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec60_perm[j103] = fRec60_tmp[faust_wrap_add(vsize, j103)];
			}
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fYec5_perm[j95] = fYec5_tmp[faust_wrap_add(vsize, j95)];
			}
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec59_perm[j91] = fRec59_tmp[faust_wrap_add(vsize, j91)];
			}
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec58_perm[j93] = fRec58_tmp[faust_wrap_add(vsize, j93)];
			}
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec57_perm[j97] = fRec57_tmp[faust_wrap_add(vsize, j97)];
			}
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec56_perm[j99] = fRec56_tmp[faust_wrap_add(vsize, j99)];
			}
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fYec4_perm[j83] = fYec4_tmp[faust_wrap_add(vsize, j83)];
			}
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec55_perm[j79] = fRec55_tmp[faust_wrap_add(vsize, j79)];
			}
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec54_perm[j81] = fRec54_tmp[faust_wrap_add(vsize, j81)];
			}
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec53_perm[j85] = fRec53_tmp[faust_wrap_add(vsize, j85)];
			}
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec52_perm[j87] = fRec52_tmp[faust_wrap_add(vsize, j87)];
			}
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec51_perm[j89] = fRec51_tmp[faust_wrap_add(vsize, j89)];
			}
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fYec3_perm[j69] = fYec3_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec50_perm[j65] = fRec50_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec49_perm[j67] = fRec49_tmp[faust_wrap_add(vsize, j67)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec48_perm[j71] = fRec48_tmp[faust_wrap_add(vsize, j71)];
			}
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec47_perm[j73] = fRec47_tmp[faust_wrap_add(vsize, j73)];
			}
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec46_perm[j75] = fRec46_tmp[faust_wrap_add(vsize, j75)];
			}
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec45_perm[j77] = fRec45_tmp[faust_wrap_add(vsize, j77)];
			}
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec44_perm[j55] = fRec44_tmp[faust_wrap_add(vsize, j55)];
			}
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec43_perm[j57] = fRec43_tmp[faust_wrap_add(vsize, j57)];
			}
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec42_perm[j59] = fRec42_tmp[faust_wrap_add(vsize, j59)];
			}
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec41_perm[j61] = fRec41_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec40_perm[j63] = fRec40_tmp[faust_wrap_add(vsize, j63)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec39_perm[j51] = fRec39_tmp[faust_wrap_add(vsize, j51)];
			}
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec38_perm[j53] = fRec38_tmp[faust_wrap_add(vsize, j53)];
			}
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec2_perm[j45] = fYec2_tmp[faust_wrap_add(vsize, j45)];
			}
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec37_perm[j41] = fRec37_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec36_perm[j43] = fRec36_tmp[faust_wrap_add(vsize, j43)];
			}
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec35_perm[j47] = fRec35_tmp[faust_wrap_add(vsize, j47)];
			}
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec34_perm[j49] = fRec34_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fYec1_perm[j33] = fYec1_tmp[faust_wrap_add(vsize, j33)];
			}
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec33_perm[j29] = fRec33_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec32_perm[j31] = fRec32_tmp[faust_wrap_add(vsize, j31)];
			}
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec31_perm[j35] = fRec31_tmp[faust_wrap_add(vsize, j35)];
			}
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec30_perm[j37] = fRec30_tmp[faust_wrap_add(vsize, j37)];
			}
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec29_perm[j39] = fRec29_tmp[faust_wrap_add(vsize, j39)];
			}
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fYec0_perm[j19] = fYec0_tmp[faust_wrap_add(vsize, j19)];
			}
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec28_perm[j15] = fRec28_tmp[faust_wrap_add(vsize, j15)];
			}
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec27_perm[j17] = fRec27_tmp[faust_wrap_add(vsize, j17)];
			}
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec26_perm[j21] = fRec26_tmp[faust_wrap_add(vsize, j21)];
			}
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec25_perm[j23] = fRec25_tmp[faust_wrap_add(vsize, j23)];
			}
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec24_perm[j25] = fRec24_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec23_perm[j27] = fRec23_tmp[faust_wrap_add(vsize, j27)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec22_perm[j5] = fRec22_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec21_perm[j7] = fRec21_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec20_perm[j9] = fRec20_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec19_perm[j11] = fRec19_tmp[faust_wrap_add(vsize, j11)];
			}
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec18_perm[j13] = fRec18_tmp[faust_wrap_add(vsize, j13)];
			}
			for (int j809 = 0; j809 < 4; j809 = faust_wrap_add(j809, 1)) {
				fRec0_perm[j809] = fRec0_tmp[faust_wrap_add(vsize, j809)];
			}
			for (int j813 = 0; j813 < 4; j813 = faust_wrap_add(j813, 1)) {
				fRec1_perm[j813] = fRec1_tmp[faust_wrap_add(vsize, j813)];
			}
			for (int j815 = 0; j815 < 4; j815 = faust_wrap_add(j815, 1)) {
				fRec2_perm[j815] = fRec2_tmp[faust_wrap_add(vsize, j815)];
			}
			for (int j817 = 0; j817 < 4; j817 = faust_wrap_add(j817, 1)) {
				fRec3_perm[j817] = fRec3_tmp[faust_wrap_add(vsize, j817)];
			}
			for (int j819 = 0; j819 < 4; j819 = faust_wrap_add(j819, 1)) {
				fRec4_perm[j819] = fRec4_tmp[faust_wrap_add(vsize, j819)];
			}
			for (int j821 = 0; j821 < 4; j821 = faust_wrap_add(j821, 1)) {
				fRec5_perm[j821] = fRec5_tmp[faust_wrap_add(vsize, j821)];
			}
			for (int j823 = 0; j823 < 4; j823 = faust_wrap_add(j823, 1)) {
				fRec6_perm[j823] = fRec6_tmp[faust_wrap_add(vsize, j823)];
			}
			for (int j825 = 0; j825 < 4; j825 = faust_wrap_add(j825, 1)) {
				fRec7_perm[j825] = fRec7_tmp[faust_wrap_add(vsize, j825)];
			}
			for (int j827 = 0; j827 < 4; j827 = faust_wrap_add(j827, 1)) {
				fRec8_perm[j827] = fRec8_tmp[faust_wrap_add(vsize, j827)];
			}
			for (int j829 = 0; j829 < 4; j829 = faust_wrap_add(j829, 1)) {
				fRec9_perm[j829] = fRec9_tmp[faust_wrap_add(vsize, j829)];
			}
			for (int j831 = 0; j831 < 4; j831 = faust_wrap_add(j831, 1)) {
				fRec10_perm[j831] = fRec10_tmp[faust_wrap_add(vsize, j831)];
			}
			for (int j833 = 0; j833 < 4; j833 = faust_wrap_add(j833, 1)) {
				fRec11_perm[j833] = fRec11_tmp[faust_wrap_add(vsize, j833)];
			}
			for (int j835 = 0; j835 < 4; j835 = faust_wrap_add(j835, 1)) {
				fRec12_perm[j835] = fRec12_tmp[faust_wrap_add(vsize, j835)];
			}
			for (int j837 = 0; j837 < 4; j837 = faust_wrap_add(j837, 1)) {
				fRec13_perm[j837] = fRec13_tmp[faust_wrap_add(vsize, j837)];
			}
			for (int j839 = 0; j839 < 4; j839 = faust_wrap_add(j839, 1)) {
				fRec14_perm[j839] = fRec14_tmp[faust_wrap_add(vsize, j839)];
			}
			for (int j841 = 0; j841 < 4; j841 = faust_wrap_add(j841, 1)) {
				fRec15_perm[j841] = fRec15_tmp[faust_wrap_add(vsize, j841)];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow173 * (fRec0[i] + fRec2[i] + fRec4[i] + fRec6[i] + fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i]));
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow173 * (fRec1[i] + fRec3[i] + fRec5[i] + fRec7[i] + fRec9[i] + fRec11[i] + fRec13[i] + fRec15[i]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = faust_wrap_sub(count, vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; j0 < 4; j0 = faust_wrap_add(j0, 1)) {
				iRec17_tmp[j0] = iRec17_perm[j0];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iRec17[i] = faust_wrap_add(faust_wrap_mul(1103515245, iRec17[faust_wrap_sub(i, 1)]), 12345);
			}
			/* Post code */
			for (int j1 = 0; j1 < 4; j1 = faust_wrap_add(j1, 1)) {
				iRec17_perm[j1] = iRec17_tmp[faust_wrap_add(vsize, j1)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; j2 < 4; j2 = faust_wrap_add(j2, 1)) {
				fRec16_tmp[j2] = fRec16_perm[j2];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec16[i] = 0.5221894 * fRec16[faust_wrap_sub(i, 3)] + 4.656612875245797e-10 * static_cast<double>(iRec17[i]) + 2.494956002 * fRec16[faust_wrap_sub(i, 1)] - 2.017265875 * fRec16[faust_wrap_sub(i, 2)];
			}
			/* Post code */
			for (int j3 = 0; j3 < 4; j3 = faust_wrap_add(j3, 1)) {
				fRec16_perm[j3] = fRec16_tmp[faust_wrap_add(vsize, j3)];
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec96[i] = fSlow47 * (0.049922035 * fRec16[i] + 0.050612699 * fRec16[faust_wrap_sub(i, 2)] - (0.095993537 * fRec16[faust_wrap_sub(i, 1)] + 0.004408786 * fRec16[faust_wrap_sub(i, 3)]));
			}
			/* Vectorizable loop 3 */
			/* Pre code */
			for (int j804 = 0; j804 < 4; j804 = faust_wrap_add(j804, 1)) {
				fVec0_tmp[j804] = fVec0_perm[j804];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec0[i] = fSlow48;
			}
			/* Post code */
			for (int j805 = 0; j805 < 4; j805 = faust_wrap_add(j805, 1)) {
				fVec0_perm[j805] = fVec0_tmp[faust_wrap_add(vsize, j805)];
			}
			/* Vectorizable loop 4 */
			/* Pre code */
			for (int j806 = 0; j806 < 4; j806 = faust_wrap_add(j806, 1)) {
				fVec1_tmp[j806] = fVec1_perm[j806];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec1[i] = fSlow49;
			}
			/* Post code */
			for (int j807 = 0; j807 < 4; j807 = faust_wrap_add(j807, 1)) {
				fVec1_perm[j807] = fVec1_tmp[faust_wrap_add(vsize, j807)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				iZec97[i] = (fSlow49 - fVec1[faust_wrap_sub(i, 1)]) > 0.0;
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec98[i] = static_cast<double>(((fSlow48 - fVec0[faust_wrap_sub(i, 1)]) > 0.0) + iZec97[i]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec129[i] = fSlow155 * static_cast<double>(input0[i]);
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			for (int j810 = 0; j810 < 4; j810 = faust_wrap_add(j810, 1)) {
				fVec2_tmp[j810] = fVec2_perm[j810];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fVec2[i] = fSlow157;
			}
			/* Post code */
			for (int j811 = 0; j811 < 4; j811 = faust_wrap_add(j811, 1)) {
				fVec2_perm[j811] = fVec2_tmp[faust_wrap_add(vsize, j811)];
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec130[i] = static_cast<double>(faust_wrap_add(iZec97[i], (fSlow157 - fVec2[faust_wrap_sub(i, 1)]) > 0.0));
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec131[i] = fSlow155 * static_cast<double>(input1[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec132[i] = fZec129[i] + fZec98[i] + fZec96[i];
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fZec135[i] = fZec130[i] + fZec96[i] + fZec131[i];
			}
			/* Recursive loop 13 */
			/* Pre code */
			for (int j4 = 0; j4 < 4; j4 = faust_wrap_add(j4, 1)) {
				fRec22_tmp[j4] = fRec22_perm[j4];
			}
			for (int j6 = 0; j6 < 4; j6 = faust_wrap_add(j6, 1)) {
				fRec21_tmp[j6] = fRec21_perm[j6];
			}
			for (int j8 = 0; j8 < 4; j8 = faust_wrap_add(j8, 1)) {
				fRec20_tmp[j8] = fRec20_perm[j8];
			}
			for (int j10 = 0; j10 < 4; j10 = faust_wrap_add(j10, 1)) {
				fRec19_tmp[j10] = fRec19_perm[j10];
			}
			for (int j12 = 0; j12 < 4; j12 = faust_wrap_add(j12, 1)) {
				fRec18_tmp[j12] = fRec18_perm[j12];
			}
			for (int j14 = 0; j14 < 4; j14 = faust_wrap_add(j14, 1)) {
				fRec28_tmp[j14] = fRec28_perm[j14];
			}
			for (int j16 = 0; j16 < 4; j16 = faust_wrap_add(j16, 1)) {
				fRec27_tmp[j16] = fRec27_perm[j16];
			}
			for (int j18 = 0; j18 < 4; j18 = faust_wrap_add(j18, 1)) {
				fYec0_tmp[j18] = fYec0_perm[j18];
			}
			for (int j20 = 0; j20 < 4; j20 = faust_wrap_add(j20, 1)) {
				fRec26_tmp[j20] = fRec26_perm[j20];
			}
			for (int j22 = 0; j22 < 4; j22 = faust_wrap_add(j22, 1)) {
				fRec25_tmp[j22] = fRec25_perm[j22];
			}
			for (int j24 = 0; j24 < 4; j24 = faust_wrap_add(j24, 1)) {
				fRec24_tmp[j24] = fRec24_perm[j24];
			}
			for (int j26 = 0; j26 < 4; j26 = faust_wrap_add(j26, 1)) {
				fRec23_tmp[j26] = fRec23_perm[j26];
			}
			for (int j28 = 0; j28 < 4; j28 = faust_wrap_add(j28, 1)) {
				fRec33_tmp[j28] = fRec33_perm[j28];
			}
			for (int j30 = 0; j30 < 4; j30 = faust_wrap_add(j30, 1)) {
				fRec32_tmp[j30] = fRec32_perm[j30];
			}
			for (int j32 = 0; j32 < 4; j32 = faust_wrap_add(j32, 1)) {
				fYec1_tmp[j32] = fYec1_perm[j32];
			}
			for (int j34 = 0; j34 < 4; j34 = faust_wrap_add(j34, 1)) {
				fRec31_tmp[j34] = fRec31_perm[j34];
			}
			for (int j36 = 0; j36 < 4; j36 = faust_wrap_add(j36, 1)) {
				fRec30_tmp[j36] = fRec30_perm[j36];
			}
			for (int j38 = 0; j38 < 4; j38 = faust_wrap_add(j38, 1)) {
				fRec29_tmp[j38] = fRec29_perm[j38];
			}
			for (int j40 = 0; j40 < 4; j40 = faust_wrap_add(j40, 1)) {
				fRec37_tmp[j40] = fRec37_perm[j40];
			}
			for (int j42 = 0; j42 < 4; j42 = faust_wrap_add(j42, 1)) {
				fRec36_tmp[j42] = fRec36_perm[j42];
			}
			for (int j44 = 0; j44 < 4; j44 = faust_wrap_add(j44, 1)) {
				fYec2_tmp[j44] = fYec2_perm[j44];
			}
			for (int j46 = 0; j46 < 4; j46 = faust_wrap_add(j46, 1)) {
				fRec35_tmp[j46] = fRec35_perm[j46];
			}
			for (int j48 = 0; j48 < 4; j48 = faust_wrap_add(j48, 1)) {
				fRec34_tmp[j48] = fRec34_perm[j48];
			}
			for (int j50 = 0; j50 < 4; j50 = faust_wrap_add(j50, 1)) {
				fRec39_tmp[j50] = fRec39_perm[j50];
			}
			for (int j52 = 0; j52 < 4; j52 = faust_wrap_add(j52, 1)) {
				fRec38_tmp[j52] = fRec38_perm[j52];
			}
			for (int j54 = 0; j54 < 4; j54 = faust_wrap_add(j54, 1)) {
				fRec44_tmp[j54] = fRec44_perm[j54];
			}
			for (int j56 = 0; j56 < 4; j56 = faust_wrap_add(j56, 1)) {
				fRec43_tmp[j56] = fRec43_perm[j56];
			}
			for (int j58 = 0; j58 < 4; j58 = faust_wrap_add(j58, 1)) {
				fRec42_tmp[j58] = fRec42_perm[j58];
			}
			for (int j60 = 0; j60 < 4; j60 = faust_wrap_add(j60, 1)) {
				fRec41_tmp[j60] = fRec41_perm[j60];
			}
			for (int j62 = 0; j62 < 4; j62 = faust_wrap_add(j62, 1)) {
				fRec40_tmp[j62] = fRec40_perm[j62];
			}
			for (int j64 = 0; j64 < 4; j64 = faust_wrap_add(j64, 1)) {
				fRec50_tmp[j64] = fRec50_perm[j64];
			}
			for (int j66 = 0; j66 < 4; j66 = faust_wrap_add(j66, 1)) {
				fRec49_tmp[j66] = fRec49_perm[j66];
			}
			for (int j68 = 0; j68 < 4; j68 = faust_wrap_add(j68, 1)) {
				fYec3_tmp[j68] = fYec3_perm[j68];
			}
			for (int j70 = 0; j70 < 4; j70 = faust_wrap_add(j70, 1)) {
				fRec48_tmp[j70] = fRec48_perm[j70];
			}
			for (int j72 = 0; j72 < 4; j72 = faust_wrap_add(j72, 1)) {
				fRec47_tmp[j72] = fRec47_perm[j72];
			}
			for (int j74 = 0; j74 < 4; j74 = faust_wrap_add(j74, 1)) {
				fRec46_tmp[j74] = fRec46_perm[j74];
			}
			for (int j76 = 0; j76 < 4; j76 = faust_wrap_add(j76, 1)) {
				fRec45_tmp[j76] = fRec45_perm[j76];
			}
			for (int j78 = 0; j78 < 4; j78 = faust_wrap_add(j78, 1)) {
				fRec55_tmp[j78] = fRec55_perm[j78];
			}
			for (int j80 = 0; j80 < 4; j80 = faust_wrap_add(j80, 1)) {
				fRec54_tmp[j80] = fRec54_perm[j80];
			}
			for (int j82 = 0; j82 < 4; j82 = faust_wrap_add(j82, 1)) {
				fYec4_tmp[j82] = fYec4_perm[j82];
			}
			for (int j84 = 0; j84 < 4; j84 = faust_wrap_add(j84, 1)) {
				fRec53_tmp[j84] = fRec53_perm[j84];
			}
			for (int j86 = 0; j86 < 4; j86 = faust_wrap_add(j86, 1)) {
				fRec52_tmp[j86] = fRec52_perm[j86];
			}
			for (int j88 = 0; j88 < 4; j88 = faust_wrap_add(j88, 1)) {
				fRec51_tmp[j88] = fRec51_perm[j88];
			}
			for (int j90 = 0; j90 < 4; j90 = faust_wrap_add(j90, 1)) {
				fRec59_tmp[j90] = fRec59_perm[j90];
			}
			for (int j92 = 0; j92 < 4; j92 = faust_wrap_add(j92, 1)) {
				fRec58_tmp[j92] = fRec58_perm[j92];
			}
			for (int j94 = 0; j94 < 4; j94 = faust_wrap_add(j94, 1)) {
				fYec5_tmp[j94] = fYec5_perm[j94];
			}
			for (int j96 = 0; j96 < 4; j96 = faust_wrap_add(j96, 1)) {
				fRec57_tmp[j96] = fRec57_perm[j96];
			}
			for (int j98 = 0; j98 < 4; j98 = faust_wrap_add(j98, 1)) {
				fRec56_tmp[j98] = fRec56_perm[j98];
			}
			for (int j100 = 0; j100 < 4; j100 = faust_wrap_add(j100, 1)) {
				fRec61_tmp[j100] = fRec61_perm[j100];
			}
			for (int j102 = 0; j102 < 4; j102 = faust_wrap_add(j102, 1)) {
				fRec60_tmp[j102] = fRec60_perm[j102];
			}
			for (int j104 = 0; j104 < 4; j104 = faust_wrap_add(j104, 1)) {
				fRec66_tmp[j104] = fRec66_perm[j104];
			}
			for (int j106 = 0; j106 < 4; j106 = faust_wrap_add(j106, 1)) {
				fRec65_tmp[j106] = fRec65_perm[j106];
			}
			for (int j108 = 0; j108 < 4; j108 = faust_wrap_add(j108, 1)) {
				fRec64_tmp[j108] = fRec64_perm[j108];
			}
			for (int j110 = 0; j110 < 4; j110 = faust_wrap_add(j110, 1)) {
				fRec63_tmp[j110] = fRec63_perm[j110];
			}
			for (int j112 = 0; j112 < 4; j112 = faust_wrap_add(j112, 1)) {
				fRec62_tmp[j112] = fRec62_perm[j112];
			}
			for (int j114 = 0; j114 < 4; j114 = faust_wrap_add(j114, 1)) {
				fRec72_tmp[j114] = fRec72_perm[j114];
			}
			for (int j116 = 0; j116 < 4; j116 = faust_wrap_add(j116, 1)) {
				fRec71_tmp[j116] = fRec71_perm[j116];
			}
			for (int j118 = 0; j118 < 4; j118 = faust_wrap_add(j118, 1)) {
				fYec6_tmp[j118] = fYec6_perm[j118];
			}
			for (int j120 = 0; j120 < 4; j120 = faust_wrap_add(j120, 1)) {
				fRec70_tmp[j120] = fRec70_perm[j120];
			}
			for (int j122 = 0; j122 < 4; j122 = faust_wrap_add(j122, 1)) {
				fRec69_tmp[j122] = fRec69_perm[j122];
			}
			for (int j124 = 0; j124 < 4; j124 = faust_wrap_add(j124, 1)) {
				fRec68_tmp[j124] = fRec68_perm[j124];
			}
			for (int j126 = 0; j126 < 4; j126 = faust_wrap_add(j126, 1)) {
				fRec67_tmp[j126] = fRec67_perm[j126];
			}
			for (int j128 = 0; j128 < 4; j128 = faust_wrap_add(j128, 1)) {
				fRec77_tmp[j128] = fRec77_perm[j128];
			}
			for (int j130 = 0; j130 < 4; j130 = faust_wrap_add(j130, 1)) {
				fRec76_tmp[j130] = fRec76_perm[j130];
			}
			for (int j132 = 0; j132 < 4; j132 = faust_wrap_add(j132, 1)) {
				fYec7_tmp[j132] = fYec7_perm[j132];
			}
			for (int j134 = 0; j134 < 4; j134 = faust_wrap_add(j134, 1)) {
				fRec75_tmp[j134] = fRec75_perm[j134];
			}
			for (int j136 = 0; j136 < 4; j136 = faust_wrap_add(j136, 1)) {
				fRec74_tmp[j136] = fRec74_perm[j136];
			}
			for (int j138 = 0; j138 < 4; j138 = faust_wrap_add(j138, 1)) {
				fRec73_tmp[j138] = fRec73_perm[j138];
			}
			for (int j140 = 0; j140 < 4; j140 = faust_wrap_add(j140, 1)) {
				fRec81_tmp[j140] = fRec81_perm[j140];
			}
			for (int j142 = 0; j142 < 4; j142 = faust_wrap_add(j142, 1)) {
				fRec80_tmp[j142] = fRec80_perm[j142];
			}
			for (int j144 = 0; j144 < 4; j144 = faust_wrap_add(j144, 1)) {
				fYec8_tmp[j144] = fYec8_perm[j144];
			}
			for (int j146 = 0; j146 < 4; j146 = faust_wrap_add(j146, 1)) {
				fRec79_tmp[j146] = fRec79_perm[j146];
			}
			for (int j148 = 0; j148 < 4; j148 = faust_wrap_add(j148, 1)) {
				fRec78_tmp[j148] = fRec78_perm[j148];
			}
			for (int j150 = 0; j150 < 4; j150 = faust_wrap_add(j150, 1)) {
				fRec83_tmp[j150] = fRec83_perm[j150];
			}
			for (int j152 = 0; j152 < 4; j152 = faust_wrap_add(j152, 1)) {
				fRec82_tmp[j152] = fRec82_perm[j152];
			}
			for (int j154 = 0; j154 < 4; j154 = faust_wrap_add(j154, 1)) {
				fRec88_tmp[j154] = fRec88_perm[j154];
			}
			for (int j156 = 0; j156 < 4; j156 = faust_wrap_add(j156, 1)) {
				fRec87_tmp[j156] = fRec87_perm[j156];
			}
			for (int j158 = 0; j158 < 4; j158 = faust_wrap_add(j158, 1)) {
				fRec86_tmp[j158] = fRec86_perm[j158];
			}
			for (int j160 = 0; j160 < 4; j160 = faust_wrap_add(j160, 1)) {
				fRec85_tmp[j160] = fRec85_perm[j160];
			}
			for (int j162 = 0; j162 < 4; j162 = faust_wrap_add(j162, 1)) {
				fRec84_tmp[j162] = fRec84_perm[j162];
			}
			for (int j164 = 0; j164 < 4; j164 = faust_wrap_add(j164, 1)) {
				fRec94_tmp[j164] = fRec94_perm[j164];
			}
			for (int j166 = 0; j166 < 4; j166 = faust_wrap_add(j166, 1)) {
				fRec93_tmp[j166] = fRec93_perm[j166];
			}
			for (int j168 = 0; j168 < 4; j168 = faust_wrap_add(j168, 1)) {
				fYec9_tmp[j168] = fYec9_perm[j168];
			}
			for (int j170 = 0; j170 < 4; j170 = faust_wrap_add(j170, 1)) {
				fRec92_tmp[j170] = fRec92_perm[j170];
			}
			for (int j172 = 0; j172 < 4; j172 = faust_wrap_add(j172, 1)) {
				fRec91_tmp[j172] = fRec91_perm[j172];
			}
			for (int j174 = 0; j174 < 4; j174 = faust_wrap_add(j174, 1)) {
				fRec90_tmp[j174] = fRec90_perm[j174];
			}
			for (int j176 = 0; j176 < 4; j176 = faust_wrap_add(j176, 1)) {
				fRec89_tmp[j176] = fRec89_perm[j176];
			}
			for (int j178 = 0; j178 < 4; j178 = faust_wrap_add(j178, 1)) {
				fRec99_tmp[j178] = fRec99_perm[j178];
			}
			for (int j180 = 0; j180 < 4; j180 = faust_wrap_add(j180, 1)) {
				fRec98_tmp[j180] = fRec98_perm[j180];
			}
			for (int j182 = 0; j182 < 4; j182 = faust_wrap_add(j182, 1)) {
				fYec10_tmp[j182] = fYec10_perm[j182];
			}
			for (int j184 = 0; j184 < 4; j184 = faust_wrap_add(j184, 1)) {
				fRec97_tmp[j184] = fRec97_perm[j184];
			}
			for (int j186 = 0; j186 < 4; j186 = faust_wrap_add(j186, 1)) {
				fRec96_tmp[j186] = fRec96_perm[j186];
			}
			for (int j188 = 0; j188 < 4; j188 = faust_wrap_add(j188, 1)) {
				fRec95_tmp[j188] = fRec95_perm[j188];
			}
			for (int j190 = 0; j190 < 4; j190 = faust_wrap_add(j190, 1)) {
				fRec103_tmp[j190] = fRec103_perm[j190];
			}
			for (int j192 = 0; j192 < 4; j192 = faust_wrap_add(j192, 1)) {
				fRec102_tmp[j192] = fRec102_perm[j192];
			}
			for (int j194 = 0; j194 < 4; j194 = faust_wrap_add(j194, 1)) {
				fYec11_tmp[j194] = fYec11_perm[j194];
			}
			for (int j196 = 0; j196 < 4; j196 = faust_wrap_add(j196, 1)) {
				fRec101_tmp[j196] = fRec101_perm[j196];
			}
			for (int j198 = 0; j198 < 4; j198 = faust_wrap_add(j198, 1)) {
				fRec100_tmp[j198] = fRec100_perm[j198];
			}
			for (int j200 = 0; j200 < 4; j200 = faust_wrap_add(j200, 1)) {
				fRec105_tmp[j200] = fRec105_perm[j200];
			}
			for (int j202 = 0; j202 < 4; j202 = faust_wrap_add(j202, 1)) {
				fRec104_tmp[j202] = fRec104_perm[j202];
			}
			for (int j204 = 0; j204 < 4; j204 = faust_wrap_add(j204, 1)) {
				fRec110_tmp[j204] = fRec110_perm[j204];
			}
			for (int j206 = 0; j206 < 4; j206 = faust_wrap_add(j206, 1)) {
				fRec109_tmp[j206] = fRec109_perm[j206];
			}
			for (int j208 = 0; j208 < 4; j208 = faust_wrap_add(j208, 1)) {
				fRec108_tmp[j208] = fRec108_perm[j208];
			}
			for (int j210 = 0; j210 < 4; j210 = faust_wrap_add(j210, 1)) {
				fRec107_tmp[j210] = fRec107_perm[j210];
			}
			for (int j212 = 0; j212 < 4; j212 = faust_wrap_add(j212, 1)) {
				fRec106_tmp[j212] = fRec106_perm[j212];
			}
			for (int j214 = 0; j214 < 4; j214 = faust_wrap_add(j214, 1)) {
				fRec116_tmp[j214] = fRec116_perm[j214];
			}
			for (int j216 = 0; j216 < 4; j216 = faust_wrap_add(j216, 1)) {
				fRec115_tmp[j216] = fRec115_perm[j216];
			}
			for (int j218 = 0; j218 < 4; j218 = faust_wrap_add(j218, 1)) {
				fYec12_tmp[j218] = fYec12_perm[j218];
			}
			for (int j220 = 0; j220 < 4; j220 = faust_wrap_add(j220, 1)) {
				fRec114_tmp[j220] = fRec114_perm[j220];
			}
			for (int j222 = 0; j222 < 4; j222 = faust_wrap_add(j222, 1)) {
				fRec113_tmp[j222] = fRec113_perm[j222];
			}
			for (int j224 = 0; j224 < 4; j224 = faust_wrap_add(j224, 1)) {
				fRec112_tmp[j224] = fRec112_perm[j224];
			}
			for (int j226 = 0; j226 < 4; j226 = faust_wrap_add(j226, 1)) {
				fRec111_tmp[j226] = fRec111_perm[j226];
			}
			for (int j228 = 0; j228 < 4; j228 = faust_wrap_add(j228, 1)) {
				fRec121_tmp[j228] = fRec121_perm[j228];
			}
			for (int j230 = 0; j230 < 4; j230 = faust_wrap_add(j230, 1)) {
				fRec120_tmp[j230] = fRec120_perm[j230];
			}
			for (int j232 = 0; j232 < 4; j232 = faust_wrap_add(j232, 1)) {
				fYec13_tmp[j232] = fYec13_perm[j232];
			}
			for (int j234 = 0; j234 < 4; j234 = faust_wrap_add(j234, 1)) {
				fRec119_tmp[j234] = fRec119_perm[j234];
			}
			for (int j236 = 0; j236 < 4; j236 = faust_wrap_add(j236, 1)) {
				fRec118_tmp[j236] = fRec118_perm[j236];
			}
			for (int j238 = 0; j238 < 4; j238 = faust_wrap_add(j238, 1)) {
				fRec117_tmp[j238] = fRec117_perm[j238];
			}
			for (int j240 = 0; j240 < 4; j240 = faust_wrap_add(j240, 1)) {
				fRec125_tmp[j240] = fRec125_perm[j240];
			}
			for (int j242 = 0; j242 < 4; j242 = faust_wrap_add(j242, 1)) {
				fRec124_tmp[j242] = fRec124_perm[j242];
			}
			for (int j244 = 0; j244 < 4; j244 = faust_wrap_add(j244, 1)) {
				fYec14_tmp[j244] = fYec14_perm[j244];
			}
			for (int j246 = 0; j246 < 4; j246 = faust_wrap_add(j246, 1)) {
				fRec123_tmp[j246] = fRec123_perm[j246];
			}
			for (int j248 = 0; j248 < 4; j248 = faust_wrap_add(j248, 1)) {
				fRec122_tmp[j248] = fRec122_perm[j248];
			}
			for (int j250 = 0; j250 < 4; j250 = faust_wrap_add(j250, 1)) {
				fRec127_tmp[j250] = fRec127_perm[j250];
			}
			for (int j252 = 0; j252 < 4; j252 = faust_wrap_add(j252, 1)) {
				fRec126_tmp[j252] = fRec126_perm[j252];
			}
			for (int j254 = 0; j254 < 4; j254 = faust_wrap_add(j254, 1)) {
				fRec132_tmp[j254] = fRec132_perm[j254];
			}
			for (int j256 = 0; j256 < 4; j256 = faust_wrap_add(j256, 1)) {
				fRec131_tmp[j256] = fRec131_perm[j256];
			}
			for (int j258 = 0; j258 < 4; j258 = faust_wrap_add(j258, 1)) {
				fRec130_tmp[j258] = fRec130_perm[j258];
			}
			for (int j260 = 0; j260 < 4; j260 = faust_wrap_add(j260, 1)) {
				fRec129_tmp[j260] = fRec129_perm[j260];
			}
			for (int j262 = 0; j262 < 4; j262 = faust_wrap_add(j262, 1)) {
				fRec128_tmp[j262] = fRec128_perm[j262];
			}
			for (int j264 = 0; j264 < 4; j264 = faust_wrap_add(j264, 1)) {
				fRec138_tmp[j264] = fRec138_perm[j264];
			}
			for (int j266 = 0; j266 < 4; j266 = faust_wrap_add(j266, 1)) {
				fRec137_tmp[j266] = fRec137_perm[j266];
			}
			for (int j268 = 0; j268 < 4; j268 = faust_wrap_add(j268, 1)) {
				fYec15_tmp[j268] = fYec15_perm[j268];
			}
			for (int j270 = 0; j270 < 4; j270 = faust_wrap_add(j270, 1)) {
				fRec136_tmp[j270] = fRec136_perm[j270];
			}
			for (int j272 = 0; j272 < 4; j272 = faust_wrap_add(j272, 1)) {
				fRec135_tmp[j272] = fRec135_perm[j272];
			}
			for (int j274 = 0; j274 < 4; j274 = faust_wrap_add(j274, 1)) {
				fRec134_tmp[j274] = fRec134_perm[j274];
			}
			for (int j276 = 0; j276 < 4; j276 = faust_wrap_add(j276, 1)) {
				fRec133_tmp[j276] = fRec133_perm[j276];
			}
			for (int j278 = 0; j278 < 4; j278 = faust_wrap_add(j278, 1)) {
				fRec143_tmp[j278] = fRec143_perm[j278];
			}
			for (int j280 = 0; j280 < 4; j280 = faust_wrap_add(j280, 1)) {
				fRec142_tmp[j280] = fRec142_perm[j280];
			}
			for (int j282 = 0; j282 < 4; j282 = faust_wrap_add(j282, 1)) {
				fYec16_tmp[j282] = fYec16_perm[j282];
			}
			for (int j284 = 0; j284 < 4; j284 = faust_wrap_add(j284, 1)) {
				fRec141_tmp[j284] = fRec141_perm[j284];
			}
			for (int j286 = 0; j286 < 4; j286 = faust_wrap_add(j286, 1)) {
				fRec140_tmp[j286] = fRec140_perm[j286];
			}
			for (int j288 = 0; j288 < 4; j288 = faust_wrap_add(j288, 1)) {
				fRec139_tmp[j288] = fRec139_perm[j288];
			}
			for (int j290 = 0; j290 < 4; j290 = faust_wrap_add(j290, 1)) {
				fRec147_tmp[j290] = fRec147_perm[j290];
			}
			for (int j292 = 0; j292 < 4; j292 = faust_wrap_add(j292, 1)) {
				fRec146_tmp[j292] = fRec146_perm[j292];
			}
			for (int j294 = 0; j294 < 4; j294 = faust_wrap_add(j294, 1)) {
				fYec17_tmp[j294] = fYec17_perm[j294];
			}
			for (int j296 = 0; j296 < 4; j296 = faust_wrap_add(j296, 1)) {
				fRec145_tmp[j296] = fRec145_perm[j296];
			}
			for (int j298 = 0; j298 < 4; j298 = faust_wrap_add(j298, 1)) {
				fRec144_tmp[j298] = fRec144_perm[j298];
			}
			for (int j300 = 0; j300 < 4; j300 = faust_wrap_add(j300, 1)) {
				fRec149_tmp[j300] = fRec149_perm[j300];
			}
			for (int j302 = 0; j302 < 4; j302 = faust_wrap_add(j302, 1)) {
				fRec148_tmp[j302] = fRec148_perm[j302];
			}
			for (int j304 = 0; j304 < 4; j304 = faust_wrap_add(j304, 1)) {
				fRec154_tmp[j304] = fRec154_perm[j304];
			}
			for (int j306 = 0; j306 < 4; j306 = faust_wrap_add(j306, 1)) {
				fRec153_tmp[j306] = fRec153_perm[j306];
			}
			for (int j308 = 0; j308 < 4; j308 = faust_wrap_add(j308, 1)) {
				fRec152_tmp[j308] = fRec152_perm[j308];
			}
			for (int j310 = 0; j310 < 4; j310 = faust_wrap_add(j310, 1)) {
				fRec151_tmp[j310] = fRec151_perm[j310];
			}
			for (int j312 = 0; j312 < 4; j312 = faust_wrap_add(j312, 1)) {
				fRec150_tmp[j312] = fRec150_perm[j312];
			}
			for (int j314 = 0; j314 < 4; j314 = faust_wrap_add(j314, 1)) {
				fRec160_tmp[j314] = fRec160_perm[j314];
			}
			for (int j316 = 0; j316 < 4; j316 = faust_wrap_add(j316, 1)) {
				fRec159_tmp[j316] = fRec159_perm[j316];
			}
			for (int j318 = 0; j318 < 4; j318 = faust_wrap_add(j318, 1)) {
				fYec18_tmp[j318] = fYec18_perm[j318];
			}
			for (int j320 = 0; j320 < 4; j320 = faust_wrap_add(j320, 1)) {
				fRec158_tmp[j320] = fRec158_perm[j320];
			}
			for (int j322 = 0; j322 < 4; j322 = faust_wrap_add(j322, 1)) {
				fRec157_tmp[j322] = fRec157_perm[j322];
			}
			for (int j324 = 0; j324 < 4; j324 = faust_wrap_add(j324, 1)) {
				fRec156_tmp[j324] = fRec156_perm[j324];
			}
			for (int j326 = 0; j326 < 4; j326 = faust_wrap_add(j326, 1)) {
				fRec155_tmp[j326] = fRec155_perm[j326];
			}
			for (int j328 = 0; j328 < 4; j328 = faust_wrap_add(j328, 1)) {
				fRec165_tmp[j328] = fRec165_perm[j328];
			}
			for (int j330 = 0; j330 < 4; j330 = faust_wrap_add(j330, 1)) {
				fRec164_tmp[j330] = fRec164_perm[j330];
			}
			for (int j332 = 0; j332 < 4; j332 = faust_wrap_add(j332, 1)) {
				fYec19_tmp[j332] = fYec19_perm[j332];
			}
			for (int j334 = 0; j334 < 4; j334 = faust_wrap_add(j334, 1)) {
				fRec163_tmp[j334] = fRec163_perm[j334];
			}
			for (int j336 = 0; j336 < 4; j336 = faust_wrap_add(j336, 1)) {
				fRec162_tmp[j336] = fRec162_perm[j336];
			}
			for (int j338 = 0; j338 < 4; j338 = faust_wrap_add(j338, 1)) {
				fRec161_tmp[j338] = fRec161_perm[j338];
			}
			for (int j340 = 0; j340 < 4; j340 = faust_wrap_add(j340, 1)) {
				fRec169_tmp[j340] = fRec169_perm[j340];
			}
			for (int j342 = 0; j342 < 4; j342 = faust_wrap_add(j342, 1)) {
				fRec168_tmp[j342] = fRec168_perm[j342];
			}
			for (int j344 = 0; j344 < 4; j344 = faust_wrap_add(j344, 1)) {
				fYec20_tmp[j344] = fYec20_perm[j344];
			}
			for (int j346 = 0; j346 < 4; j346 = faust_wrap_add(j346, 1)) {
				fRec167_tmp[j346] = fRec167_perm[j346];
			}
			for (int j348 = 0; j348 < 4; j348 = faust_wrap_add(j348, 1)) {
				fRec166_tmp[j348] = fRec166_perm[j348];
			}
			for (int j350 = 0; j350 < 4; j350 = faust_wrap_add(j350, 1)) {
				fRec171_tmp[j350] = fRec171_perm[j350];
			}
			for (int j352 = 0; j352 < 4; j352 = faust_wrap_add(j352, 1)) {
				fRec170_tmp[j352] = fRec170_perm[j352];
			}
			for (int j354 = 0; j354 < 4; j354 = faust_wrap_add(j354, 1)) {
				fRec176_tmp[j354] = fRec176_perm[j354];
			}
			for (int j356 = 0; j356 < 4; j356 = faust_wrap_add(j356, 1)) {
				fRec175_tmp[j356] = fRec175_perm[j356];
			}
			for (int j358 = 0; j358 < 4; j358 = faust_wrap_add(j358, 1)) {
				fRec174_tmp[j358] = fRec174_perm[j358];
			}
			for (int j360 = 0; j360 < 4; j360 = faust_wrap_add(j360, 1)) {
				fRec173_tmp[j360] = fRec173_perm[j360];
			}
			for (int j362 = 0; j362 < 4; j362 = faust_wrap_add(j362, 1)) {
				fRec172_tmp[j362] = fRec172_perm[j362];
			}
			for (int j364 = 0; j364 < 4; j364 = faust_wrap_add(j364, 1)) {
				fRec182_tmp[j364] = fRec182_perm[j364];
			}
			for (int j366 = 0; j366 < 4; j366 = faust_wrap_add(j366, 1)) {
				fRec181_tmp[j366] = fRec181_perm[j366];
			}
			for (int j368 = 0; j368 < 4; j368 = faust_wrap_add(j368, 1)) {
				fYec21_tmp[j368] = fYec21_perm[j368];
			}
			for (int j370 = 0; j370 < 4; j370 = faust_wrap_add(j370, 1)) {
				fRec180_tmp[j370] = fRec180_perm[j370];
			}
			for (int j372 = 0; j372 < 4; j372 = faust_wrap_add(j372, 1)) {
				fRec179_tmp[j372] = fRec179_perm[j372];
			}
			for (int j374 = 0; j374 < 4; j374 = faust_wrap_add(j374, 1)) {
				fRec178_tmp[j374] = fRec178_perm[j374];
			}
			for (int j376 = 0; j376 < 4; j376 = faust_wrap_add(j376, 1)) {
				fRec177_tmp[j376] = fRec177_perm[j376];
			}
			for (int j378 = 0; j378 < 4; j378 = faust_wrap_add(j378, 1)) {
				fRec187_tmp[j378] = fRec187_perm[j378];
			}
			for (int j380 = 0; j380 < 4; j380 = faust_wrap_add(j380, 1)) {
				fRec186_tmp[j380] = fRec186_perm[j380];
			}
			for (int j382 = 0; j382 < 4; j382 = faust_wrap_add(j382, 1)) {
				fYec22_tmp[j382] = fYec22_perm[j382];
			}
			for (int j384 = 0; j384 < 4; j384 = faust_wrap_add(j384, 1)) {
				fRec185_tmp[j384] = fRec185_perm[j384];
			}
			for (int j386 = 0; j386 < 4; j386 = faust_wrap_add(j386, 1)) {
				fRec184_tmp[j386] = fRec184_perm[j386];
			}
			for (int j388 = 0; j388 < 4; j388 = faust_wrap_add(j388, 1)) {
				fRec183_tmp[j388] = fRec183_perm[j388];
			}
			for (int j390 = 0; j390 < 4; j390 = faust_wrap_add(j390, 1)) {
				fRec191_tmp[j390] = fRec191_perm[j390];
			}
			for (int j392 = 0; j392 < 4; j392 = faust_wrap_add(j392, 1)) {
				fRec190_tmp[j392] = fRec190_perm[j392];
			}
			for (int j394 = 0; j394 < 4; j394 = faust_wrap_add(j394, 1)) {
				fYec23_tmp[j394] = fYec23_perm[j394];
			}
			for (int j396 = 0; j396 < 4; j396 = faust_wrap_add(j396, 1)) {
				fRec189_tmp[j396] = fRec189_perm[j396];
			}
			for (int j398 = 0; j398 < 4; j398 = faust_wrap_add(j398, 1)) {
				fRec188_tmp[j398] = fRec188_perm[j398];
			}
			for (int j400 = 0; j400 < 4; j400 = faust_wrap_add(j400, 1)) {
				fRec193_tmp[j400] = fRec193_perm[j400];
			}
			for (int j402 = 0; j402 < 4; j402 = faust_wrap_add(j402, 1)) {
				fRec192_tmp[j402] = fRec192_perm[j402];
			}
			for (int j404 = 0; j404 < 4; j404 = faust_wrap_add(j404, 1)) {
				fRec198_tmp[j404] = fRec198_perm[j404];
			}
			for (int j406 = 0; j406 < 4; j406 = faust_wrap_add(j406, 1)) {
				fRec197_tmp[j406] = fRec197_perm[j406];
			}
			for (int j408 = 0; j408 < 4; j408 = faust_wrap_add(j408, 1)) {
				fRec196_tmp[j408] = fRec196_perm[j408];
			}
			for (int j410 = 0; j410 < 4; j410 = faust_wrap_add(j410, 1)) {
				fRec195_tmp[j410] = fRec195_perm[j410];
			}
			for (int j412 = 0; j412 < 4; j412 = faust_wrap_add(j412, 1)) {
				fRec194_tmp[j412] = fRec194_perm[j412];
			}
			for (int j414 = 0; j414 < 4; j414 = faust_wrap_add(j414, 1)) {
				fRec204_tmp[j414] = fRec204_perm[j414];
			}
			for (int j416 = 0; j416 < 4; j416 = faust_wrap_add(j416, 1)) {
				fRec203_tmp[j416] = fRec203_perm[j416];
			}
			for (int j418 = 0; j418 < 4; j418 = faust_wrap_add(j418, 1)) {
				fYec24_tmp[j418] = fYec24_perm[j418];
			}
			for (int j420 = 0; j420 < 4; j420 = faust_wrap_add(j420, 1)) {
				fRec202_tmp[j420] = fRec202_perm[j420];
			}
			for (int j422 = 0; j422 < 4; j422 = faust_wrap_add(j422, 1)) {
				fRec201_tmp[j422] = fRec201_perm[j422];
			}
			for (int j424 = 0; j424 < 4; j424 = faust_wrap_add(j424, 1)) {
				fRec200_tmp[j424] = fRec200_perm[j424];
			}
			for (int j426 = 0; j426 < 4; j426 = faust_wrap_add(j426, 1)) {
				fRec199_tmp[j426] = fRec199_perm[j426];
			}
			for (int j428 = 0; j428 < 4; j428 = faust_wrap_add(j428, 1)) {
				fRec209_tmp[j428] = fRec209_perm[j428];
			}
			for (int j430 = 0; j430 < 4; j430 = faust_wrap_add(j430, 1)) {
				fRec208_tmp[j430] = fRec208_perm[j430];
			}
			for (int j432 = 0; j432 < 4; j432 = faust_wrap_add(j432, 1)) {
				fYec25_tmp[j432] = fYec25_perm[j432];
			}
			for (int j434 = 0; j434 < 4; j434 = faust_wrap_add(j434, 1)) {
				fRec207_tmp[j434] = fRec207_perm[j434];
			}
			for (int j436 = 0; j436 < 4; j436 = faust_wrap_add(j436, 1)) {
				fRec206_tmp[j436] = fRec206_perm[j436];
			}
			for (int j438 = 0; j438 < 4; j438 = faust_wrap_add(j438, 1)) {
				fRec205_tmp[j438] = fRec205_perm[j438];
			}
			for (int j440 = 0; j440 < 4; j440 = faust_wrap_add(j440, 1)) {
				fRec213_tmp[j440] = fRec213_perm[j440];
			}
			for (int j442 = 0; j442 < 4; j442 = faust_wrap_add(j442, 1)) {
				fRec212_tmp[j442] = fRec212_perm[j442];
			}
			for (int j444 = 0; j444 < 4; j444 = faust_wrap_add(j444, 1)) {
				fYec26_tmp[j444] = fYec26_perm[j444];
			}
			for (int j446 = 0; j446 < 4; j446 = faust_wrap_add(j446, 1)) {
				fRec211_tmp[j446] = fRec211_perm[j446];
			}
			for (int j448 = 0; j448 < 4; j448 = faust_wrap_add(j448, 1)) {
				fRec210_tmp[j448] = fRec210_perm[j448];
			}
			for (int j450 = 0; j450 < 4; j450 = faust_wrap_add(j450, 1)) {
				fRec215_tmp[j450] = fRec215_perm[j450];
			}
			for (int j452 = 0; j452 < 4; j452 = faust_wrap_add(j452, 1)) {
				fRec214_tmp[j452] = fRec214_perm[j452];
			}
			for (int j454 = 0; j454 < 4; j454 = faust_wrap_add(j454, 1)) {
				fRec220_tmp[j454] = fRec220_perm[j454];
			}
			for (int j456 = 0; j456 < 4; j456 = faust_wrap_add(j456, 1)) {
				fRec219_tmp[j456] = fRec219_perm[j456];
			}
			for (int j458 = 0; j458 < 4; j458 = faust_wrap_add(j458, 1)) {
				fRec218_tmp[j458] = fRec218_perm[j458];
			}
			for (int j460 = 0; j460 < 4; j460 = faust_wrap_add(j460, 1)) {
				fRec217_tmp[j460] = fRec217_perm[j460];
			}
			for (int j462 = 0; j462 < 4; j462 = faust_wrap_add(j462, 1)) {
				fRec216_tmp[j462] = fRec216_perm[j462];
			}
			for (int j464 = 0; j464 < 4; j464 = faust_wrap_add(j464, 1)) {
				fRec226_tmp[j464] = fRec226_perm[j464];
			}
			for (int j466 = 0; j466 < 4; j466 = faust_wrap_add(j466, 1)) {
				fRec225_tmp[j466] = fRec225_perm[j466];
			}
			for (int j468 = 0; j468 < 4; j468 = faust_wrap_add(j468, 1)) {
				fYec27_tmp[j468] = fYec27_perm[j468];
			}
			for (int j470 = 0; j470 < 4; j470 = faust_wrap_add(j470, 1)) {
				fRec224_tmp[j470] = fRec224_perm[j470];
			}
			for (int j472 = 0; j472 < 4; j472 = faust_wrap_add(j472, 1)) {
				fRec223_tmp[j472] = fRec223_perm[j472];
			}
			for (int j474 = 0; j474 < 4; j474 = faust_wrap_add(j474, 1)) {
				fRec222_tmp[j474] = fRec222_perm[j474];
			}
			for (int j476 = 0; j476 < 4; j476 = faust_wrap_add(j476, 1)) {
				fRec221_tmp[j476] = fRec221_perm[j476];
			}
			for (int j478 = 0; j478 < 4; j478 = faust_wrap_add(j478, 1)) {
				fRec231_tmp[j478] = fRec231_perm[j478];
			}
			for (int j480 = 0; j480 < 4; j480 = faust_wrap_add(j480, 1)) {
				fRec230_tmp[j480] = fRec230_perm[j480];
			}
			for (int j482 = 0; j482 < 4; j482 = faust_wrap_add(j482, 1)) {
				fYec28_tmp[j482] = fYec28_perm[j482];
			}
			for (int j484 = 0; j484 < 4; j484 = faust_wrap_add(j484, 1)) {
				fRec229_tmp[j484] = fRec229_perm[j484];
			}
			for (int j486 = 0; j486 < 4; j486 = faust_wrap_add(j486, 1)) {
				fRec228_tmp[j486] = fRec228_perm[j486];
			}
			for (int j488 = 0; j488 < 4; j488 = faust_wrap_add(j488, 1)) {
				fRec227_tmp[j488] = fRec227_perm[j488];
			}
			for (int j490 = 0; j490 < 4; j490 = faust_wrap_add(j490, 1)) {
				fRec235_tmp[j490] = fRec235_perm[j490];
			}
			for (int j492 = 0; j492 < 4; j492 = faust_wrap_add(j492, 1)) {
				fRec234_tmp[j492] = fRec234_perm[j492];
			}
			for (int j494 = 0; j494 < 4; j494 = faust_wrap_add(j494, 1)) {
				fYec29_tmp[j494] = fYec29_perm[j494];
			}
			for (int j496 = 0; j496 < 4; j496 = faust_wrap_add(j496, 1)) {
				fRec233_tmp[j496] = fRec233_perm[j496];
			}
			for (int j498 = 0; j498 < 4; j498 = faust_wrap_add(j498, 1)) {
				fRec232_tmp[j498] = fRec232_perm[j498];
			}
			for (int j500 = 0; j500 < 4; j500 = faust_wrap_add(j500, 1)) {
				fRec237_tmp[j500] = fRec237_perm[j500];
			}
			for (int j502 = 0; j502 < 4; j502 = faust_wrap_add(j502, 1)) {
				fRec236_tmp[j502] = fRec236_perm[j502];
			}
			for (int j504 = 0; j504 < 4; j504 = faust_wrap_add(j504, 1)) {
				fRec242_tmp[j504] = fRec242_perm[j504];
			}
			for (int j506 = 0; j506 < 4; j506 = faust_wrap_add(j506, 1)) {
				fRec241_tmp[j506] = fRec241_perm[j506];
			}
			for (int j508 = 0; j508 < 4; j508 = faust_wrap_add(j508, 1)) {
				fRec240_tmp[j508] = fRec240_perm[j508];
			}
			for (int j510 = 0; j510 < 4; j510 = faust_wrap_add(j510, 1)) {
				fRec239_tmp[j510] = fRec239_perm[j510];
			}
			for (int j512 = 0; j512 < 4; j512 = faust_wrap_add(j512, 1)) {
				fRec238_tmp[j512] = fRec238_perm[j512];
			}
			for (int j514 = 0; j514 < 4; j514 = faust_wrap_add(j514, 1)) {
				fRec248_tmp[j514] = fRec248_perm[j514];
			}
			for (int j516 = 0; j516 < 4; j516 = faust_wrap_add(j516, 1)) {
				fRec247_tmp[j516] = fRec247_perm[j516];
			}
			for (int j518 = 0; j518 < 4; j518 = faust_wrap_add(j518, 1)) {
				fYec30_tmp[j518] = fYec30_perm[j518];
			}
			for (int j520 = 0; j520 < 4; j520 = faust_wrap_add(j520, 1)) {
				fRec246_tmp[j520] = fRec246_perm[j520];
			}
			for (int j522 = 0; j522 < 4; j522 = faust_wrap_add(j522, 1)) {
				fRec245_tmp[j522] = fRec245_perm[j522];
			}
			for (int j524 = 0; j524 < 4; j524 = faust_wrap_add(j524, 1)) {
				fRec244_tmp[j524] = fRec244_perm[j524];
			}
			for (int j526 = 0; j526 < 4; j526 = faust_wrap_add(j526, 1)) {
				fRec243_tmp[j526] = fRec243_perm[j526];
			}
			for (int j528 = 0; j528 < 4; j528 = faust_wrap_add(j528, 1)) {
				fRec253_tmp[j528] = fRec253_perm[j528];
			}
			for (int j530 = 0; j530 < 4; j530 = faust_wrap_add(j530, 1)) {
				fRec252_tmp[j530] = fRec252_perm[j530];
			}
			for (int j532 = 0; j532 < 4; j532 = faust_wrap_add(j532, 1)) {
				fYec31_tmp[j532] = fYec31_perm[j532];
			}
			for (int j534 = 0; j534 < 4; j534 = faust_wrap_add(j534, 1)) {
				fRec251_tmp[j534] = fRec251_perm[j534];
			}
			for (int j536 = 0; j536 < 4; j536 = faust_wrap_add(j536, 1)) {
				fRec250_tmp[j536] = fRec250_perm[j536];
			}
			for (int j538 = 0; j538 < 4; j538 = faust_wrap_add(j538, 1)) {
				fRec249_tmp[j538] = fRec249_perm[j538];
			}
			for (int j540 = 0; j540 < 4; j540 = faust_wrap_add(j540, 1)) {
				fRec257_tmp[j540] = fRec257_perm[j540];
			}
			for (int j542 = 0; j542 < 4; j542 = faust_wrap_add(j542, 1)) {
				fRec256_tmp[j542] = fRec256_perm[j542];
			}
			for (int j544 = 0; j544 < 4; j544 = faust_wrap_add(j544, 1)) {
				fYec32_tmp[j544] = fYec32_perm[j544];
			}
			for (int j546 = 0; j546 < 4; j546 = faust_wrap_add(j546, 1)) {
				fRec255_tmp[j546] = fRec255_perm[j546];
			}
			for (int j548 = 0; j548 < 4; j548 = faust_wrap_add(j548, 1)) {
				fRec254_tmp[j548] = fRec254_perm[j548];
			}
			for (int j550 = 0; j550 < 4; j550 = faust_wrap_add(j550, 1)) {
				fRec259_tmp[j550] = fRec259_perm[j550];
			}
			for (int j552 = 0; j552 < 4; j552 = faust_wrap_add(j552, 1)) {
				fRec258_tmp[j552] = fRec258_perm[j552];
			}
			for (int j554 = 0; j554 < 4; j554 = faust_wrap_add(j554, 1)) {
				fRec264_tmp[j554] = fRec264_perm[j554];
			}
			for (int j556 = 0; j556 < 4; j556 = faust_wrap_add(j556, 1)) {
				fRec263_tmp[j556] = fRec263_perm[j556];
			}
			for (int j558 = 0; j558 < 4; j558 = faust_wrap_add(j558, 1)) {
				fRec262_tmp[j558] = fRec262_perm[j558];
			}
			for (int j560 = 0; j560 < 4; j560 = faust_wrap_add(j560, 1)) {
				fRec261_tmp[j560] = fRec261_perm[j560];
			}
			for (int j562 = 0; j562 < 4; j562 = faust_wrap_add(j562, 1)) {
				fRec260_tmp[j562] = fRec260_perm[j562];
			}
			for (int j564 = 0; j564 < 4; j564 = faust_wrap_add(j564, 1)) {
				fRec270_tmp[j564] = fRec270_perm[j564];
			}
			for (int j566 = 0; j566 < 4; j566 = faust_wrap_add(j566, 1)) {
				fRec269_tmp[j566] = fRec269_perm[j566];
			}
			for (int j568 = 0; j568 < 4; j568 = faust_wrap_add(j568, 1)) {
				fYec33_tmp[j568] = fYec33_perm[j568];
			}
			for (int j570 = 0; j570 < 4; j570 = faust_wrap_add(j570, 1)) {
				fRec268_tmp[j570] = fRec268_perm[j570];
			}
			for (int j572 = 0; j572 < 4; j572 = faust_wrap_add(j572, 1)) {
				fRec267_tmp[j572] = fRec267_perm[j572];
			}
			for (int j574 = 0; j574 < 4; j574 = faust_wrap_add(j574, 1)) {
				fRec266_tmp[j574] = fRec266_perm[j574];
			}
			for (int j576 = 0; j576 < 4; j576 = faust_wrap_add(j576, 1)) {
				fRec265_tmp[j576] = fRec265_perm[j576];
			}
			for (int j578 = 0; j578 < 4; j578 = faust_wrap_add(j578, 1)) {
				fRec275_tmp[j578] = fRec275_perm[j578];
			}
			for (int j580 = 0; j580 < 4; j580 = faust_wrap_add(j580, 1)) {
				fRec274_tmp[j580] = fRec274_perm[j580];
			}
			for (int j582 = 0; j582 < 4; j582 = faust_wrap_add(j582, 1)) {
				fYec34_tmp[j582] = fYec34_perm[j582];
			}
			for (int j584 = 0; j584 < 4; j584 = faust_wrap_add(j584, 1)) {
				fRec273_tmp[j584] = fRec273_perm[j584];
			}
			for (int j586 = 0; j586 < 4; j586 = faust_wrap_add(j586, 1)) {
				fRec272_tmp[j586] = fRec272_perm[j586];
			}
			for (int j588 = 0; j588 < 4; j588 = faust_wrap_add(j588, 1)) {
				fRec271_tmp[j588] = fRec271_perm[j588];
			}
			for (int j590 = 0; j590 < 4; j590 = faust_wrap_add(j590, 1)) {
				fRec279_tmp[j590] = fRec279_perm[j590];
			}
			for (int j592 = 0; j592 < 4; j592 = faust_wrap_add(j592, 1)) {
				fRec278_tmp[j592] = fRec278_perm[j592];
			}
			for (int j594 = 0; j594 < 4; j594 = faust_wrap_add(j594, 1)) {
				fYec35_tmp[j594] = fYec35_perm[j594];
			}
			for (int j596 = 0; j596 < 4; j596 = faust_wrap_add(j596, 1)) {
				fRec277_tmp[j596] = fRec277_perm[j596];
			}
			for (int j598 = 0; j598 < 4; j598 = faust_wrap_add(j598, 1)) {
				fRec276_tmp[j598] = fRec276_perm[j598];
			}
			for (int j600 = 0; j600 < 4; j600 = faust_wrap_add(j600, 1)) {
				fRec281_tmp[j600] = fRec281_perm[j600];
			}
			for (int j602 = 0; j602 < 4; j602 = faust_wrap_add(j602, 1)) {
				fRec280_tmp[j602] = fRec280_perm[j602];
			}
			for (int j604 = 0; j604 < 4; j604 = faust_wrap_add(j604, 1)) {
				fRec286_tmp[j604] = fRec286_perm[j604];
			}
			for (int j606 = 0; j606 < 4; j606 = faust_wrap_add(j606, 1)) {
				fRec285_tmp[j606] = fRec285_perm[j606];
			}
			for (int j608 = 0; j608 < 4; j608 = faust_wrap_add(j608, 1)) {
				fRec284_tmp[j608] = fRec284_perm[j608];
			}
			for (int j610 = 0; j610 < 4; j610 = faust_wrap_add(j610, 1)) {
				fRec283_tmp[j610] = fRec283_perm[j610];
			}
			for (int j612 = 0; j612 < 4; j612 = faust_wrap_add(j612, 1)) {
				fRec282_tmp[j612] = fRec282_perm[j612];
			}
			for (int j614 = 0; j614 < 4; j614 = faust_wrap_add(j614, 1)) {
				fRec292_tmp[j614] = fRec292_perm[j614];
			}
			for (int j616 = 0; j616 < 4; j616 = faust_wrap_add(j616, 1)) {
				fRec291_tmp[j616] = fRec291_perm[j616];
			}
			for (int j618 = 0; j618 < 4; j618 = faust_wrap_add(j618, 1)) {
				fYec36_tmp[j618] = fYec36_perm[j618];
			}
			for (int j620 = 0; j620 < 4; j620 = faust_wrap_add(j620, 1)) {
				fRec290_tmp[j620] = fRec290_perm[j620];
			}
			for (int j622 = 0; j622 < 4; j622 = faust_wrap_add(j622, 1)) {
				fRec289_tmp[j622] = fRec289_perm[j622];
			}
			for (int j624 = 0; j624 < 4; j624 = faust_wrap_add(j624, 1)) {
				fRec288_tmp[j624] = fRec288_perm[j624];
			}
			for (int j626 = 0; j626 < 4; j626 = faust_wrap_add(j626, 1)) {
				fRec287_tmp[j626] = fRec287_perm[j626];
			}
			for (int j628 = 0; j628 < 4; j628 = faust_wrap_add(j628, 1)) {
				fRec297_tmp[j628] = fRec297_perm[j628];
			}
			for (int j630 = 0; j630 < 4; j630 = faust_wrap_add(j630, 1)) {
				fRec296_tmp[j630] = fRec296_perm[j630];
			}
			for (int j632 = 0; j632 < 4; j632 = faust_wrap_add(j632, 1)) {
				fYec37_tmp[j632] = fYec37_perm[j632];
			}
			for (int j634 = 0; j634 < 4; j634 = faust_wrap_add(j634, 1)) {
				fRec295_tmp[j634] = fRec295_perm[j634];
			}
			for (int j636 = 0; j636 < 4; j636 = faust_wrap_add(j636, 1)) {
				fRec294_tmp[j636] = fRec294_perm[j636];
			}
			for (int j638 = 0; j638 < 4; j638 = faust_wrap_add(j638, 1)) {
				fRec293_tmp[j638] = fRec293_perm[j638];
			}
			for (int j640 = 0; j640 < 4; j640 = faust_wrap_add(j640, 1)) {
				fRec301_tmp[j640] = fRec301_perm[j640];
			}
			for (int j642 = 0; j642 < 4; j642 = faust_wrap_add(j642, 1)) {
				fRec300_tmp[j642] = fRec300_perm[j642];
			}
			for (int j644 = 0; j644 < 4; j644 = faust_wrap_add(j644, 1)) {
				fYec38_tmp[j644] = fYec38_perm[j644];
			}
			for (int j646 = 0; j646 < 4; j646 = faust_wrap_add(j646, 1)) {
				fRec299_tmp[j646] = fRec299_perm[j646];
			}
			for (int j648 = 0; j648 < 4; j648 = faust_wrap_add(j648, 1)) {
				fRec298_tmp[j648] = fRec298_perm[j648];
			}
			for (int j650 = 0; j650 < 4; j650 = faust_wrap_add(j650, 1)) {
				fRec303_tmp[j650] = fRec303_perm[j650];
			}
			for (int j652 = 0; j652 < 4; j652 = faust_wrap_add(j652, 1)) {
				fRec302_tmp[j652] = fRec302_perm[j652];
			}
			for (int j654 = 0; j654 < 4; j654 = faust_wrap_add(j654, 1)) {
				fRec308_tmp[j654] = fRec308_perm[j654];
			}
			for (int j656 = 0; j656 < 4; j656 = faust_wrap_add(j656, 1)) {
				fRec307_tmp[j656] = fRec307_perm[j656];
			}
			for (int j658 = 0; j658 < 4; j658 = faust_wrap_add(j658, 1)) {
				fRec306_tmp[j658] = fRec306_perm[j658];
			}
			for (int j660 = 0; j660 < 4; j660 = faust_wrap_add(j660, 1)) {
				fRec305_tmp[j660] = fRec305_perm[j660];
			}
			for (int j662 = 0; j662 < 4; j662 = faust_wrap_add(j662, 1)) {
				fRec304_tmp[j662] = fRec304_perm[j662];
			}
			for (int j664 = 0; j664 < 4; j664 = faust_wrap_add(j664, 1)) {
				fRec314_tmp[j664] = fRec314_perm[j664];
			}
			for (int j666 = 0; j666 < 4; j666 = faust_wrap_add(j666, 1)) {
				fRec313_tmp[j666] = fRec313_perm[j666];
			}
			for (int j668 = 0; j668 < 4; j668 = faust_wrap_add(j668, 1)) {
				fYec39_tmp[j668] = fYec39_perm[j668];
			}
			for (int j670 = 0; j670 < 4; j670 = faust_wrap_add(j670, 1)) {
				fRec312_tmp[j670] = fRec312_perm[j670];
			}
			for (int j672 = 0; j672 < 4; j672 = faust_wrap_add(j672, 1)) {
				fRec311_tmp[j672] = fRec311_perm[j672];
			}
			for (int j674 = 0; j674 < 4; j674 = faust_wrap_add(j674, 1)) {
				fRec310_tmp[j674] = fRec310_perm[j674];
			}
			for (int j676 = 0; j676 < 4; j676 = faust_wrap_add(j676, 1)) {
				fRec309_tmp[j676] = fRec309_perm[j676];
			}
			for (int j678 = 0; j678 < 4; j678 = faust_wrap_add(j678, 1)) {
				fRec319_tmp[j678] = fRec319_perm[j678];
			}
			for (int j680 = 0; j680 < 4; j680 = faust_wrap_add(j680, 1)) {
				fRec318_tmp[j680] = fRec318_perm[j680];
			}
			for (int j682 = 0; j682 < 4; j682 = faust_wrap_add(j682, 1)) {
				fYec40_tmp[j682] = fYec40_perm[j682];
			}
			for (int j684 = 0; j684 < 4; j684 = faust_wrap_add(j684, 1)) {
				fRec317_tmp[j684] = fRec317_perm[j684];
			}
			for (int j686 = 0; j686 < 4; j686 = faust_wrap_add(j686, 1)) {
				fRec316_tmp[j686] = fRec316_perm[j686];
			}
			for (int j688 = 0; j688 < 4; j688 = faust_wrap_add(j688, 1)) {
				fRec315_tmp[j688] = fRec315_perm[j688];
			}
			for (int j690 = 0; j690 < 4; j690 = faust_wrap_add(j690, 1)) {
				fRec323_tmp[j690] = fRec323_perm[j690];
			}
			for (int j692 = 0; j692 < 4; j692 = faust_wrap_add(j692, 1)) {
				fRec322_tmp[j692] = fRec322_perm[j692];
			}
			for (int j694 = 0; j694 < 4; j694 = faust_wrap_add(j694, 1)) {
				fYec41_tmp[j694] = fYec41_perm[j694];
			}
			for (int j696 = 0; j696 < 4; j696 = faust_wrap_add(j696, 1)) {
				fRec321_tmp[j696] = fRec321_perm[j696];
			}
			for (int j698 = 0; j698 < 4; j698 = faust_wrap_add(j698, 1)) {
				fRec320_tmp[j698] = fRec320_perm[j698];
			}
			for (int j700 = 0; j700 < 4; j700 = faust_wrap_add(j700, 1)) {
				fRec325_tmp[j700] = fRec325_perm[j700];
			}
			for (int j702 = 0; j702 < 4; j702 = faust_wrap_add(j702, 1)) {
				fRec324_tmp[j702] = fRec324_perm[j702];
			}
			for (int j704 = 0; j704 < 4; j704 = faust_wrap_add(j704, 1)) {
				fRec330_tmp[j704] = fRec330_perm[j704];
			}
			for (int j706 = 0; j706 < 4; j706 = faust_wrap_add(j706, 1)) {
				fRec329_tmp[j706] = fRec329_perm[j706];
			}
			for (int j708 = 0; j708 < 4; j708 = faust_wrap_add(j708, 1)) {
				fRec328_tmp[j708] = fRec328_perm[j708];
			}
			for (int j710 = 0; j710 < 4; j710 = faust_wrap_add(j710, 1)) {
				fRec327_tmp[j710] = fRec327_perm[j710];
			}
			for (int j712 = 0; j712 < 4; j712 = faust_wrap_add(j712, 1)) {
				fRec326_tmp[j712] = fRec326_perm[j712];
			}
			for (int j714 = 0; j714 < 4; j714 = faust_wrap_add(j714, 1)) {
				fRec336_tmp[j714] = fRec336_perm[j714];
			}
			for (int j716 = 0; j716 < 4; j716 = faust_wrap_add(j716, 1)) {
				fRec335_tmp[j716] = fRec335_perm[j716];
			}
			for (int j718 = 0; j718 < 4; j718 = faust_wrap_add(j718, 1)) {
				fYec42_tmp[j718] = fYec42_perm[j718];
			}
			for (int j720 = 0; j720 < 4; j720 = faust_wrap_add(j720, 1)) {
				fRec334_tmp[j720] = fRec334_perm[j720];
			}
			for (int j722 = 0; j722 < 4; j722 = faust_wrap_add(j722, 1)) {
				fRec333_tmp[j722] = fRec333_perm[j722];
			}
			for (int j724 = 0; j724 < 4; j724 = faust_wrap_add(j724, 1)) {
				fRec332_tmp[j724] = fRec332_perm[j724];
			}
			for (int j726 = 0; j726 < 4; j726 = faust_wrap_add(j726, 1)) {
				fRec331_tmp[j726] = fRec331_perm[j726];
			}
			for (int j728 = 0; j728 < 4; j728 = faust_wrap_add(j728, 1)) {
				fRec341_tmp[j728] = fRec341_perm[j728];
			}
			for (int j730 = 0; j730 < 4; j730 = faust_wrap_add(j730, 1)) {
				fRec340_tmp[j730] = fRec340_perm[j730];
			}
			for (int j732 = 0; j732 < 4; j732 = faust_wrap_add(j732, 1)) {
				fYec43_tmp[j732] = fYec43_perm[j732];
			}
			for (int j734 = 0; j734 < 4; j734 = faust_wrap_add(j734, 1)) {
				fRec339_tmp[j734] = fRec339_perm[j734];
			}
			for (int j736 = 0; j736 < 4; j736 = faust_wrap_add(j736, 1)) {
				fRec338_tmp[j736] = fRec338_perm[j736];
			}
			for (int j738 = 0; j738 < 4; j738 = faust_wrap_add(j738, 1)) {
				fRec337_tmp[j738] = fRec337_perm[j738];
			}
			for (int j740 = 0; j740 < 4; j740 = faust_wrap_add(j740, 1)) {
				fRec345_tmp[j740] = fRec345_perm[j740];
			}
			for (int j742 = 0; j742 < 4; j742 = faust_wrap_add(j742, 1)) {
				fRec344_tmp[j742] = fRec344_perm[j742];
			}
			for (int j744 = 0; j744 < 4; j744 = faust_wrap_add(j744, 1)) {
				fYec44_tmp[j744] = fYec44_perm[j744];
			}
			for (int j746 = 0; j746 < 4; j746 = faust_wrap_add(j746, 1)) {
				fRec343_tmp[j746] = fRec343_perm[j746];
			}
			for (int j748 = 0; j748 < 4; j748 = faust_wrap_add(j748, 1)) {
				fRec342_tmp[j748] = fRec342_perm[j748];
			}
			for (int j750 = 0; j750 < 4; j750 = faust_wrap_add(j750, 1)) {
				fRec347_tmp[j750] = fRec347_perm[j750];
			}
			for (int j752 = 0; j752 < 4; j752 = faust_wrap_add(j752, 1)) {
				fRec346_tmp[j752] = fRec346_perm[j752];
			}
			for (int j754 = 0; j754 < 4; j754 = faust_wrap_add(j754, 1)) {
				fRec352_tmp[j754] = fRec352_perm[j754];
			}
			for (int j756 = 0; j756 < 4; j756 = faust_wrap_add(j756, 1)) {
				fRec351_tmp[j756] = fRec351_perm[j756];
			}
			for (int j758 = 0; j758 < 4; j758 = faust_wrap_add(j758, 1)) {
				fRec350_tmp[j758] = fRec350_perm[j758];
			}
			for (int j760 = 0; j760 < 4; j760 = faust_wrap_add(j760, 1)) {
				fRec349_tmp[j760] = fRec349_perm[j760];
			}
			for (int j762 = 0; j762 < 4; j762 = faust_wrap_add(j762, 1)) {
				fRec348_tmp[j762] = fRec348_perm[j762];
			}
			for (int j764 = 0; j764 < 4; j764 = faust_wrap_add(j764, 1)) {
				fRec358_tmp[j764] = fRec358_perm[j764];
			}
			for (int j766 = 0; j766 < 4; j766 = faust_wrap_add(j766, 1)) {
				fRec357_tmp[j766] = fRec357_perm[j766];
			}
			for (int j768 = 0; j768 < 4; j768 = faust_wrap_add(j768, 1)) {
				fYec45_tmp[j768] = fYec45_perm[j768];
			}
			for (int j770 = 0; j770 < 4; j770 = faust_wrap_add(j770, 1)) {
				fRec356_tmp[j770] = fRec356_perm[j770];
			}
			for (int j772 = 0; j772 < 4; j772 = faust_wrap_add(j772, 1)) {
				fRec355_tmp[j772] = fRec355_perm[j772];
			}
			for (int j774 = 0; j774 < 4; j774 = faust_wrap_add(j774, 1)) {
				fRec354_tmp[j774] = fRec354_perm[j774];
			}
			for (int j776 = 0; j776 < 4; j776 = faust_wrap_add(j776, 1)) {
				fRec353_tmp[j776] = fRec353_perm[j776];
			}
			for (int j778 = 0; j778 < 4; j778 = faust_wrap_add(j778, 1)) {
				fRec363_tmp[j778] = fRec363_perm[j778];
			}
			for (int j780 = 0; j780 < 4; j780 = faust_wrap_add(j780, 1)) {
				fRec362_tmp[j780] = fRec362_perm[j780];
			}
			for (int j782 = 0; j782 < 4; j782 = faust_wrap_add(j782, 1)) {
				fYec46_tmp[j782] = fYec46_perm[j782];
			}
			for (int j784 = 0; j784 < 4; j784 = faust_wrap_add(j784, 1)) {
				fRec361_tmp[j784] = fRec361_perm[j784];
			}
			for (int j786 = 0; j786 < 4; j786 = faust_wrap_add(j786, 1)) {
				fRec360_tmp[j786] = fRec360_perm[j786];
			}
			for (int j788 = 0; j788 < 4; j788 = faust_wrap_add(j788, 1)) {
				fRec359_tmp[j788] = fRec359_perm[j788];
			}
			for (int j790 = 0; j790 < 4; j790 = faust_wrap_add(j790, 1)) {
				fRec367_tmp[j790] = fRec367_perm[j790];
			}
			for (int j792 = 0; j792 < 4; j792 = faust_wrap_add(j792, 1)) {
				fRec366_tmp[j792] = fRec366_perm[j792];
			}
			for (int j794 = 0; j794 < 4; j794 = faust_wrap_add(j794, 1)) {
				fYec47_tmp[j794] = fYec47_perm[j794];
			}
			for (int j796 = 0; j796 < 4; j796 = faust_wrap_add(j796, 1)) {
				fRec365_tmp[j796] = fRec365_perm[j796];
			}
			for (int j798 = 0; j798 < 4; j798 = faust_wrap_add(j798, 1)) {
				fRec364_tmp[j798] = fRec364_perm[j798];
			}
			for (int j800 = 0; j800 < 4; j800 = faust_wrap_add(j800, 1)) {
				fRec369_tmp[j800] = fRec369_perm[j800];
			}
			for (int j802 = 0; j802 < 4; j802 = faust_wrap_add(j802, 1)) {
				fRec368_tmp[j802] = fRec368_perm[j802];
			}
			fYec48_idx = (faust_wrap_add(fYec48_idx, fYec48_idx_save)) & 16383;
			for (int j808 = 0; j808 < 4; j808 = faust_wrap_add(j808, 1)) {
				fRec0_tmp[j808] = fRec0_perm[j808];
			}
			fYec49_idx = (faust_wrap_add(fYec49_idx, fYec49_idx_save)) & 16383;
			for (int j812 = 0; j812 < 4; j812 = faust_wrap_add(j812, 1)) {
				fRec1_tmp[j812] = fRec1_perm[j812];
			}
			fYec50_idx = (faust_wrap_add(fYec50_idx, fYec50_idx_save)) & 16383;
			for (int j814 = 0; j814 < 4; j814 = faust_wrap_add(j814, 1)) {
				fRec2_tmp[j814] = fRec2_perm[j814];
			}
			fYec51_idx = (faust_wrap_add(fYec51_idx, fYec51_idx_save)) & 16383;
			for (int j816 = 0; j816 < 4; j816 = faust_wrap_add(j816, 1)) {
				fRec3_tmp[j816] = fRec3_perm[j816];
			}
			fYec52_idx = (faust_wrap_add(fYec52_idx, fYec52_idx_save)) & 16383;
			for (int j818 = 0; j818 < 4; j818 = faust_wrap_add(j818, 1)) {
				fRec4_tmp[j818] = fRec4_perm[j818];
			}
			fYec53_idx = (faust_wrap_add(fYec53_idx, fYec53_idx_save)) & 16383;
			for (int j820 = 0; j820 < 4; j820 = faust_wrap_add(j820, 1)) {
				fRec5_tmp[j820] = fRec5_perm[j820];
			}
			fYec54_idx = (faust_wrap_add(fYec54_idx, fYec54_idx_save)) & 16383;
			for (int j822 = 0; j822 < 4; j822 = faust_wrap_add(j822, 1)) {
				fRec6_tmp[j822] = fRec6_perm[j822];
			}
			fYec55_idx = (faust_wrap_add(fYec55_idx, fYec55_idx_save)) & 16383;
			for (int j824 = 0; j824 < 4; j824 = faust_wrap_add(j824, 1)) {
				fRec7_tmp[j824] = fRec7_perm[j824];
			}
			fYec56_idx = (faust_wrap_add(fYec56_idx, fYec56_idx_save)) & 16383;
			for (int j826 = 0; j826 < 4; j826 = faust_wrap_add(j826, 1)) {
				fRec8_tmp[j826] = fRec8_perm[j826];
			}
			fYec57_idx = (faust_wrap_add(fYec57_idx, fYec57_idx_save)) & 16383;
			for (int j828 = 0; j828 < 4; j828 = faust_wrap_add(j828, 1)) {
				fRec9_tmp[j828] = fRec9_perm[j828];
			}
			fYec58_idx = (faust_wrap_add(fYec58_idx, fYec58_idx_save)) & 16383;
			for (int j830 = 0; j830 < 4; j830 = faust_wrap_add(j830, 1)) {
				fRec10_tmp[j830] = fRec10_perm[j830];
			}
			fYec59_idx = (faust_wrap_add(fYec59_idx, fYec59_idx_save)) & 16383;
			for (int j832 = 0; j832 < 4; j832 = faust_wrap_add(j832, 1)) {
				fRec11_tmp[j832] = fRec11_perm[j832];
			}
			fYec60_idx = (faust_wrap_add(fYec60_idx, fYec60_idx_save)) & 16383;
			for (int j834 = 0; j834 < 4; j834 = faust_wrap_add(j834, 1)) {
				fRec12_tmp[j834] = fRec12_perm[j834];
			}
			fYec61_idx = (faust_wrap_add(fYec61_idx, fYec61_idx_save)) & 16383;
			for (int j836 = 0; j836 < 4; j836 = faust_wrap_add(j836, 1)) {
				fRec13_tmp[j836] = fRec13_perm[j836];
			}
			fYec62_idx = (faust_wrap_add(fYec62_idx, fYec62_idx_save)) & 16383;
			for (int j838 = 0; j838 < 4; j838 = faust_wrap_add(j838, 1)) {
				fRec14_tmp[j838] = fRec14_perm[j838];
			}
			fYec63_idx = (faust_wrap_add(fYec63_idx, fYec63_idx_save)) & 16383;
			for (int j840 = 0; j840 < 4; j840 = faust_wrap_add(j840, 1)) {
				fRec15_tmp[j840] = fRec15_perm[j840];
			}
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				fRec22[i] = -(fSlow2 * (fSlow3 * fRec22[faust_wrap_sub(i, 1)] - fSlow1 * (fRec0[faust_wrap_sub(i, 1)] - fRec0[faust_wrap_sub(i, 2)])));
				fRec21[i] = fRec22[i] - fSlow5 * (fSlow6 * fRec21[faust_wrap_sub(i, 2)] + fSlow8 * fRec21[faust_wrap_sub(i, 1)]);
				fZec0[i] = fSlow17 * fRec20[faust_wrap_sub(i, 1)];
				fRec20[i] = fSlow9 * (fRec21[faust_wrap_sub(i, 2)] + (fRec21[i] - 2.0 * fRec21[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec20[faust_wrap_sub(i, 2)] + fZec0[i]);
				fZec1[i] = fSlow25 * fRec19[faust_wrap_sub(i, 1)];
				fRec19[i] = fRec20[faust_wrap_sub(i, 2)] + fSlow13 * (fZec0[i] + fSlow15 * fRec20[i]) - fSlow21 * (fSlow23 * fRec19[faust_wrap_sub(i, 2)] + fZec1[i]);
				fZec2[i] = fSlow33 * fRec18[faust_wrap_sub(i, 1)];
				fRec18[i] = fRec19[faust_wrap_sub(i, 2)] + fSlow21 * (fZec1[i] + fSlow23 * fRec19[i]) - fSlow29 * (fSlow31 * fRec18[faust_wrap_sub(i, 2)] + fZec2[i]);
				fRec28[i] = -(fSlow2 * (fSlow3 * fRec28[faust_wrap_sub(i, 1)] - (fRec0[faust_wrap_sub(i, 1)] + fRec0[faust_wrap_sub(i, 2)])));
				fRec27[i] = fRec28[i] - fSlow5 * (fSlow6 * fRec27[faust_wrap_sub(i, 2)] + fSlow8 * fRec27[faust_wrap_sub(i, 1)]);
				fYec0[i] = fSlow5 * (fRec27[faust_wrap_sub(i, 2)] + fRec27[i] + 2.0 * fRec27[faust_wrap_sub(i, 1)]);
				fRec26[i] = -(fSlow34 * (fSlow14 * fRec26[faust_wrap_sub(i, 1)] - fSlow11 * (fYec0[i] - fYec0[faust_wrap_sub(i, 1)])));
				fRec25[i] = fRec26[i] - fSlow36 * (fSlow37 * fRec25[faust_wrap_sub(i, 2)] + fSlow17 * fRec25[faust_wrap_sub(i, 1)]);
				fZec3[i] = fSlow25 * fRec24[faust_wrap_sub(i, 1)];
				fRec24[i] = fSlow38 * (fRec25[faust_wrap_sub(i, 2)] + (fRec25[i] - 2.0 * fRec25[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec24[faust_wrap_sub(i, 2)] + fZec3[i]);
				fZec4[i] = fSlow33 * fRec23[faust_wrap_sub(i, 1)];
				fRec23[i] = fRec24[faust_wrap_sub(i, 2)] + fSlow21 * (fZec3[i] + fSlow23 * fRec24[i]) - fSlow29 * (fSlow31 * fRec23[faust_wrap_sub(i, 2)] + fZec4[i]);
				fRec33[i] = -(fSlow34 * (fSlow14 * fRec33[faust_wrap_sub(i, 1)] - (fYec0[i] + fYec0[faust_wrap_sub(i, 1)])));
				fRec32[i] = fRec33[i] - fSlow36 * (fSlow37 * fRec32[faust_wrap_sub(i, 2)] + fSlow17 * fRec32[faust_wrap_sub(i, 1)]);
				fYec1[i] = fSlow36 * (fRec32[faust_wrap_sub(i, 2)] + fRec32[i] + 2.0 * fRec32[faust_wrap_sub(i, 1)]);
				fRec31[i] = -(fSlow39 * (fSlow22 * fRec31[faust_wrap_sub(i, 1)] - fSlow19 * (fYec1[i] - fYec1[faust_wrap_sub(i, 1)])));
				fRec30[i] = fRec31[i] - fSlow41 * (fSlow42 * fRec30[faust_wrap_sub(i, 2)] + fSlow25 * fRec30[faust_wrap_sub(i, 1)]);
				fZec5[i] = fSlow33 * fRec29[faust_wrap_sub(i, 1)];
				fRec29[i] = fSlow43 * (fRec30[faust_wrap_sub(i, 2)] + (fRec30[i] - 2.0 * fRec30[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec29[faust_wrap_sub(i, 2)] + fZec5[i]);
				fRec37[i] = -(fSlow39 * (fSlow22 * fRec37[faust_wrap_sub(i, 1)] - (fYec1[i] + fYec1[faust_wrap_sub(i, 1)])));
				fRec36[i] = fRec37[i] - fSlow41 * (fSlow42 * fRec36[faust_wrap_sub(i, 2)] + fSlow25 * fRec36[faust_wrap_sub(i, 1)]);
				fYec2[i] = fSlow41 * (fRec36[faust_wrap_sub(i, 2)] + fRec36[i] + 2.0 * fRec36[faust_wrap_sub(i, 1)]);
				fRec35[i] = -(fSlow44 * (fSlow30 * fRec35[faust_wrap_sub(i, 1)] - fSlow27 * (fYec2[i] - fYec2[faust_wrap_sub(i, 1)])));
				fRec34[i] = fRec35[i] - fSlow45 * (fSlow46 * fRec34[faust_wrap_sub(i, 2)] + fSlow33 * fRec34[faust_wrap_sub(i, 1)]);
				fRec39[i] = -(fSlow44 * (fSlow30 * fRec39[faust_wrap_sub(i, 1)] - (fYec2[i] + fYec2[faust_wrap_sub(i, 1)])));
				fRec38[i] = fRec39[i] - fSlow45 * (fSlow46 * fRec38[faust_wrap_sub(i, 2)] + fSlow33 * fRec38[faust_wrap_sub(i, 1)]);
				fRec44[i] = -(fSlow2 * (fSlow3 * fRec44[faust_wrap_sub(i, 1)] - fSlow1 * (fRec8[faust_wrap_sub(i, 1)] - fRec8[faust_wrap_sub(i, 2)])));
				fRec43[i] = fRec44[i] - fSlow5 * (fSlow6 * fRec43[faust_wrap_sub(i, 2)] + fSlow8 * fRec43[faust_wrap_sub(i, 1)]);
				fZec6[i] = fSlow17 * fRec42[faust_wrap_sub(i, 1)];
				fRec42[i] = fSlow9 * (fRec43[faust_wrap_sub(i, 2)] + (fRec43[i] - 2.0 * fRec43[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec42[faust_wrap_sub(i, 2)] + fZec6[i]);
				fZec7[i] = fSlow25 * fRec41[faust_wrap_sub(i, 1)];
				fRec41[i] = fRec42[faust_wrap_sub(i, 2)] + fSlow13 * (fZec6[i] + fSlow15 * fRec42[i]) - fSlow21 * (fSlow23 * fRec41[faust_wrap_sub(i, 2)] + fZec7[i]);
				fZec8[i] = fSlow33 * fRec40[faust_wrap_sub(i, 1)];
				fRec40[i] = fRec41[faust_wrap_sub(i, 2)] + fSlow21 * (fZec7[i] + fSlow23 * fRec41[i]) - fSlow29 * (fSlow31 * fRec40[faust_wrap_sub(i, 2)] + fZec8[i]);
				fRec50[i] = -(fSlow2 * (fSlow3 * fRec50[faust_wrap_sub(i, 1)] - (fRec8[faust_wrap_sub(i, 1)] + fRec8[faust_wrap_sub(i, 2)])));
				fRec49[i] = fRec50[i] - fSlow5 * (fSlow6 * fRec49[faust_wrap_sub(i, 2)] + fSlow8 * fRec49[faust_wrap_sub(i, 1)]);
				fYec3[i] = fSlow5 * (fRec49[faust_wrap_sub(i, 2)] + fRec49[i] + 2.0 * fRec49[faust_wrap_sub(i, 1)]);
				fRec48[i] = -(fSlow34 * (fSlow14 * fRec48[faust_wrap_sub(i, 1)] - fSlow11 * (fYec3[i] - fYec3[faust_wrap_sub(i, 1)])));
				fRec47[i] = fRec48[i] - fSlow36 * (fSlow37 * fRec47[faust_wrap_sub(i, 2)] + fSlow17 * fRec47[faust_wrap_sub(i, 1)]);
				fZec9[i] = fSlow25 * fRec46[faust_wrap_sub(i, 1)];
				fRec46[i] = fSlow38 * (fRec47[faust_wrap_sub(i, 2)] + (fRec47[i] - 2.0 * fRec47[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec46[faust_wrap_sub(i, 2)] + fZec9[i]);
				fZec10[i] = fSlow33 * fRec45[faust_wrap_sub(i, 1)];
				fRec45[i] = fRec46[faust_wrap_sub(i, 2)] + fSlow21 * (fZec9[i] + fSlow23 * fRec46[i]) - fSlow29 * (fSlow31 * fRec45[faust_wrap_sub(i, 2)] + fZec10[i]);
				fRec55[i] = -(fSlow34 * (fSlow14 * fRec55[faust_wrap_sub(i, 1)] - (fYec3[i] + fYec3[faust_wrap_sub(i, 1)])));
				fRec54[i] = fRec55[i] - fSlow36 * (fSlow37 * fRec54[faust_wrap_sub(i, 2)] + fSlow17 * fRec54[faust_wrap_sub(i, 1)]);
				fYec4[i] = fSlow36 * (fRec54[faust_wrap_sub(i, 2)] + fRec54[i] + 2.0 * fRec54[faust_wrap_sub(i, 1)]);
				fRec53[i] = -(fSlow39 * (fSlow22 * fRec53[faust_wrap_sub(i, 1)] - fSlow19 * (fYec4[i] - fYec4[faust_wrap_sub(i, 1)])));
				fRec52[i] = fRec53[i] - fSlow41 * (fSlow42 * fRec52[faust_wrap_sub(i, 2)] + fSlow25 * fRec52[faust_wrap_sub(i, 1)]);
				fZec11[i] = fSlow33 * fRec51[faust_wrap_sub(i, 1)];
				fRec51[i] = fSlow43 * (fRec52[faust_wrap_sub(i, 2)] + (fRec52[i] - 2.0 * fRec52[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec51[faust_wrap_sub(i, 2)] + fZec11[i]);
				fRec59[i] = -(fSlow39 * (fSlow22 * fRec59[faust_wrap_sub(i, 1)] - (fYec4[i] + fYec4[faust_wrap_sub(i, 1)])));
				fRec58[i] = fRec59[i] - fSlow41 * (fSlow42 * fRec58[faust_wrap_sub(i, 2)] + fSlow25 * fRec58[faust_wrap_sub(i, 1)]);
				fYec5[i] = fSlow41 * (fRec58[faust_wrap_sub(i, 2)] + fRec58[i] + 2.0 * fRec58[faust_wrap_sub(i, 1)]);
				fRec57[i] = -(fSlow44 * (fSlow30 * fRec57[faust_wrap_sub(i, 1)] - fSlow27 * (fYec5[i] - fYec5[faust_wrap_sub(i, 1)])));
				fRec56[i] = fRec57[i] - fSlow45 * (fSlow46 * fRec56[faust_wrap_sub(i, 2)] + fSlow33 * fRec56[faust_wrap_sub(i, 1)]);
				fRec61[i] = -(fSlow44 * (fSlow30 * fRec61[faust_wrap_sub(i, 1)] - (fYec5[i] + fYec5[faust_wrap_sub(i, 1)])));
				fRec60[i] = fRec61[i] - fSlow45 * (fSlow46 * fRec60[faust_wrap_sub(i, 2)] + fSlow33 * fRec60[faust_wrap_sub(i, 1)]);
				fRec66[i] = -(fSlow2 * (fSlow3 * fRec66[faust_wrap_sub(i, 1)] - fSlow1 * (fRec4[faust_wrap_sub(i, 1)] - fRec4[faust_wrap_sub(i, 2)])));
				fRec65[i] = fRec66[i] - fSlow5 * (fSlow6 * fRec65[faust_wrap_sub(i, 2)] + fSlow8 * fRec65[faust_wrap_sub(i, 1)]);
				fZec12[i] = fSlow17 * fRec64[faust_wrap_sub(i, 1)];
				fRec64[i] = fSlow9 * (fRec65[faust_wrap_sub(i, 2)] + (fRec65[i] - 2.0 * fRec65[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec64[faust_wrap_sub(i, 2)] + fZec12[i]);
				fZec13[i] = fSlow25 * fRec63[faust_wrap_sub(i, 1)];
				fRec63[i] = fRec64[faust_wrap_sub(i, 2)] + fSlow13 * (fZec12[i] + fSlow15 * fRec64[i]) - fSlow21 * (fSlow23 * fRec63[faust_wrap_sub(i, 2)] + fZec13[i]);
				fZec14[i] = fSlow33 * fRec62[faust_wrap_sub(i, 1)];
				fRec62[i] = fRec63[faust_wrap_sub(i, 2)] + fSlow21 * (fZec13[i] + fSlow23 * fRec63[i]) - fSlow29 * (fSlow31 * fRec62[faust_wrap_sub(i, 2)] + fZec14[i]);
				fRec72[i] = -(fSlow2 * (fSlow3 * fRec72[faust_wrap_sub(i, 1)] - (fRec4[faust_wrap_sub(i, 1)] + fRec4[faust_wrap_sub(i, 2)])));
				fRec71[i] = fRec72[i] - fSlow5 * (fSlow6 * fRec71[faust_wrap_sub(i, 2)] + fSlow8 * fRec71[faust_wrap_sub(i, 1)]);
				fYec6[i] = fSlow5 * (fRec71[faust_wrap_sub(i, 2)] + fRec71[i] + 2.0 * fRec71[faust_wrap_sub(i, 1)]);
				fRec70[i] = -(fSlow34 * (fSlow14 * fRec70[faust_wrap_sub(i, 1)] - fSlow11 * (fYec6[i] - fYec6[faust_wrap_sub(i, 1)])));
				fRec69[i] = fRec70[i] - fSlow36 * (fSlow37 * fRec69[faust_wrap_sub(i, 2)] + fSlow17 * fRec69[faust_wrap_sub(i, 1)]);
				fZec15[i] = fSlow25 * fRec68[faust_wrap_sub(i, 1)];
				fRec68[i] = fSlow38 * (fRec69[faust_wrap_sub(i, 2)] + (fRec69[i] - 2.0 * fRec69[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec68[faust_wrap_sub(i, 2)] + fZec15[i]);
				fZec16[i] = fSlow33 * fRec67[faust_wrap_sub(i, 1)];
				fRec67[i] = fRec68[faust_wrap_sub(i, 2)] + fSlow21 * (fZec15[i] + fSlow23 * fRec68[i]) - fSlow29 * (fSlow31 * fRec67[faust_wrap_sub(i, 2)] + fZec16[i]);
				fRec77[i] = -(fSlow34 * (fSlow14 * fRec77[faust_wrap_sub(i, 1)] - (fYec6[i] + fYec6[faust_wrap_sub(i, 1)])));
				fRec76[i] = fRec77[i] - fSlow36 * (fSlow37 * fRec76[faust_wrap_sub(i, 2)] + fSlow17 * fRec76[faust_wrap_sub(i, 1)]);
				fYec7[i] = fSlow36 * (fRec76[faust_wrap_sub(i, 2)] + fRec76[i] + 2.0 * fRec76[faust_wrap_sub(i, 1)]);
				fRec75[i] = -(fSlow39 * (fSlow22 * fRec75[faust_wrap_sub(i, 1)] - fSlow19 * (fYec7[i] - fYec7[faust_wrap_sub(i, 1)])));
				fRec74[i] = fRec75[i] - fSlow41 * (fSlow42 * fRec74[faust_wrap_sub(i, 2)] + fSlow25 * fRec74[faust_wrap_sub(i, 1)]);
				fZec17[i] = fSlow33 * fRec73[faust_wrap_sub(i, 1)];
				fRec73[i] = fSlow43 * (fRec74[faust_wrap_sub(i, 2)] + (fRec74[i] - 2.0 * fRec74[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec73[faust_wrap_sub(i, 2)] + fZec17[i]);
				fRec81[i] = -(fSlow39 * (fSlow22 * fRec81[faust_wrap_sub(i, 1)] - (fYec7[i] + fYec7[faust_wrap_sub(i, 1)])));
				fRec80[i] = fRec81[i] - fSlow41 * (fSlow42 * fRec80[faust_wrap_sub(i, 2)] + fSlow25 * fRec80[faust_wrap_sub(i, 1)]);
				fYec8[i] = fSlow41 * (fRec80[faust_wrap_sub(i, 2)] + fRec80[i] + 2.0 * fRec80[faust_wrap_sub(i, 1)]);
				fRec79[i] = -(fSlow44 * (fSlow30 * fRec79[faust_wrap_sub(i, 1)] - fSlow27 * (fYec8[i] - fYec8[faust_wrap_sub(i, 1)])));
				fRec78[i] = fRec79[i] - fSlow45 * (fSlow46 * fRec78[faust_wrap_sub(i, 2)] + fSlow33 * fRec78[faust_wrap_sub(i, 1)]);
				fRec83[i] = -(fSlow44 * (fSlow30 * fRec83[faust_wrap_sub(i, 1)] - (fYec8[i] + fYec8[faust_wrap_sub(i, 1)])));
				fRec82[i] = fRec83[i] - fSlow45 * (fSlow46 * fRec82[faust_wrap_sub(i, 2)] + fSlow33 * fRec82[faust_wrap_sub(i, 1)]);
				fRec88[i] = -(fSlow2 * (fSlow3 * fRec88[faust_wrap_sub(i, 1)] - fSlow1 * (fRec12[faust_wrap_sub(i, 1)] - fRec12[faust_wrap_sub(i, 2)])));
				fRec87[i] = fRec88[i] - fSlow5 * (fSlow6 * fRec87[faust_wrap_sub(i, 2)] + fSlow8 * fRec87[faust_wrap_sub(i, 1)]);
				fZec18[i] = fSlow17 * fRec86[faust_wrap_sub(i, 1)];
				fRec86[i] = fSlow9 * (fRec87[faust_wrap_sub(i, 2)] + (fRec87[i] - 2.0 * fRec87[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec86[faust_wrap_sub(i, 2)] + fZec18[i]);
				fZec19[i] = fSlow25 * fRec85[faust_wrap_sub(i, 1)];
				fRec85[i] = fRec86[faust_wrap_sub(i, 2)] + fSlow13 * (fZec18[i] + fSlow15 * fRec86[i]) - fSlow21 * (fSlow23 * fRec85[faust_wrap_sub(i, 2)] + fZec19[i]);
				fZec20[i] = fSlow33 * fRec84[faust_wrap_sub(i, 1)];
				fRec84[i] = fRec85[faust_wrap_sub(i, 2)] + fSlow21 * (fZec19[i] + fSlow23 * fRec85[i]) - fSlow29 * (fSlow31 * fRec84[faust_wrap_sub(i, 2)] + fZec20[i]);
				fRec94[i] = -(fSlow2 * (fSlow3 * fRec94[faust_wrap_sub(i, 1)] - (fRec12[faust_wrap_sub(i, 1)] + fRec12[faust_wrap_sub(i, 2)])));
				fRec93[i] = fRec94[i] - fSlow5 * (fSlow6 * fRec93[faust_wrap_sub(i, 2)] + fSlow8 * fRec93[faust_wrap_sub(i, 1)]);
				fYec9[i] = fSlow5 * (fRec93[faust_wrap_sub(i, 2)] + fRec93[i] + 2.0 * fRec93[faust_wrap_sub(i, 1)]);
				fRec92[i] = -(fSlow34 * (fSlow14 * fRec92[faust_wrap_sub(i, 1)] - fSlow11 * (fYec9[i] - fYec9[faust_wrap_sub(i, 1)])));
				fRec91[i] = fRec92[i] - fSlow36 * (fSlow37 * fRec91[faust_wrap_sub(i, 2)] + fSlow17 * fRec91[faust_wrap_sub(i, 1)]);
				fZec21[i] = fSlow25 * fRec90[faust_wrap_sub(i, 1)];
				fRec90[i] = fSlow38 * (fRec91[faust_wrap_sub(i, 2)] + (fRec91[i] - 2.0 * fRec91[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec90[faust_wrap_sub(i, 2)] + fZec21[i]);
				fZec22[i] = fSlow33 * fRec89[faust_wrap_sub(i, 1)];
				fRec89[i] = fRec90[faust_wrap_sub(i, 2)] + fSlow21 * (fZec21[i] + fSlow23 * fRec90[i]) - fSlow29 * (fSlow31 * fRec89[faust_wrap_sub(i, 2)] + fZec22[i]);
				fRec99[i] = -(fSlow34 * (fSlow14 * fRec99[faust_wrap_sub(i, 1)] - (fYec9[i] + fYec9[faust_wrap_sub(i, 1)])));
				fRec98[i] = fRec99[i] - fSlow36 * (fSlow37 * fRec98[faust_wrap_sub(i, 2)] + fSlow17 * fRec98[faust_wrap_sub(i, 1)]);
				fYec10[i] = fSlow36 * (fRec98[faust_wrap_sub(i, 2)] + fRec98[i] + 2.0 * fRec98[faust_wrap_sub(i, 1)]);
				fRec97[i] = -(fSlow39 * (fSlow22 * fRec97[faust_wrap_sub(i, 1)] - fSlow19 * (fYec10[i] - fYec10[faust_wrap_sub(i, 1)])));
				fRec96[i] = fRec97[i] - fSlow41 * (fSlow42 * fRec96[faust_wrap_sub(i, 2)] + fSlow25 * fRec96[faust_wrap_sub(i, 1)]);
				fZec23[i] = fSlow33 * fRec95[faust_wrap_sub(i, 1)];
				fRec95[i] = fSlow43 * (fRec96[faust_wrap_sub(i, 2)] + (fRec96[i] - 2.0 * fRec96[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec95[faust_wrap_sub(i, 2)] + fZec23[i]);
				fRec103[i] = -(fSlow39 * (fSlow22 * fRec103[faust_wrap_sub(i, 1)] - (fYec10[i] + fYec10[faust_wrap_sub(i, 1)])));
				fRec102[i] = fRec103[i] - fSlow41 * (fSlow42 * fRec102[faust_wrap_sub(i, 2)] + fSlow25 * fRec102[faust_wrap_sub(i, 1)]);
				fYec11[i] = fSlow41 * (fRec102[faust_wrap_sub(i, 2)] + fRec102[i] + 2.0 * fRec102[faust_wrap_sub(i, 1)]);
				fRec101[i] = -(fSlow44 * (fSlow30 * fRec101[faust_wrap_sub(i, 1)] - fSlow27 * (fYec11[i] - fYec11[faust_wrap_sub(i, 1)])));
				fRec100[i] = fRec101[i] - fSlow45 * (fSlow46 * fRec100[faust_wrap_sub(i, 2)] + fSlow33 * fRec100[faust_wrap_sub(i, 1)]);
				fRec105[i] = -(fSlow44 * (fSlow30 * fRec105[faust_wrap_sub(i, 1)] - (fYec11[i] + fYec11[faust_wrap_sub(i, 1)])));
				fRec104[i] = fRec105[i] - fSlow45 * (fSlow46 * fRec104[faust_wrap_sub(i, 2)] + fSlow33 * fRec104[faust_wrap_sub(i, 1)]);
				fRec110[i] = -(fSlow2 * (fSlow3 * fRec110[faust_wrap_sub(i, 1)] - fSlow1 * (fRec2[faust_wrap_sub(i, 1)] - fRec2[faust_wrap_sub(i, 2)])));
				fRec109[i] = fRec110[i] - fSlow5 * (fSlow6 * fRec109[faust_wrap_sub(i, 2)] + fSlow8 * fRec109[faust_wrap_sub(i, 1)]);
				fZec24[i] = fSlow17 * fRec108[faust_wrap_sub(i, 1)];
				fRec108[i] = fSlow9 * (fRec109[faust_wrap_sub(i, 2)] + (fRec109[i] - 2.0 * fRec109[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec108[faust_wrap_sub(i, 2)] + fZec24[i]);
				fZec25[i] = fSlow25 * fRec107[faust_wrap_sub(i, 1)];
				fRec107[i] = fRec108[faust_wrap_sub(i, 2)] + fSlow13 * (fZec24[i] + fSlow15 * fRec108[i]) - fSlow21 * (fSlow23 * fRec107[faust_wrap_sub(i, 2)] + fZec25[i]);
				fZec26[i] = fSlow33 * fRec106[faust_wrap_sub(i, 1)];
				fRec106[i] = fRec107[faust_wrap_sub(i, 2)] + fSlow21 * (fZec25[i] + fSlow23 * fRec107[i]) - fSlow29 * (fSlow31 * fRec106[faust_wrap_sub(i, 2)] + fZec26[i]);
				fRec116[i] = -(fSlow2 * (fSlow3 * fRec116[faust_wrap_sub(i, 1)] - (fRec2[faust_wrap_sub(i, 1)] + fRec2[faust_wrap_sub(i, 2)])));
				fRec115[i] = fRec116[i] - fSlow5 * (fSlow6 * fRec115[faust_wrap_sub(i, 2)] + fSlow8 * fRec115[faust_wrap_sub(i, 1)]);
				fYec12[i] = fSlow5 * (fRec115[faust_wrap_sub(i, 2)] + fRec115[i] + 2.0 * fRec115[faust_wrap_sub(i, 1)]);
				fRec114[i] = -(fSlow34 * (fSlow14 * fRec114[faust_wrap_sub(i, 1)] - fSlow11 * (fYec12[i] - fYec12[faust_wrap_sub(i, 1)])));
				fRec113[i] = fRec114[i] - fSlow36 * (fSlow37 * fRec113[faust_wrap_sub(i, 2)] + fSlow17 * fRec113[faust_wrap_sub(i, 1)]);
				fZec27[i] = fSlow25 * fRec112[faust_wrap_sub(i, 1)];
				fRec112[i] = fSlow38 * (fRec113[faust_wrap_sub(i, 2)] + (fRec113[i] - 2.0 * fRec113[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec112[faust_wrap_sub(i, 2)] + fZec27[i]);
				fZec28[i] = fSlow33 * fRec111[faust_wrap_sub(i, 1)];
				fRec111[i] = fRec112[faust_wrap_sub(i, 2)] + fSlow21 * (fZec27[i] + fSlow23 * fRec112[i]) - fSlow29 * (fSlow31 * fRec111[faust_wrap_sub(i, 2)] + fZec28[i]);
				fRec121[i] = -(fSlow34 * (fSlow14 * fRec121[faust_wrap_sub(i, 1)] - (fYec12[i] + fYec12[faust_wrap_sub(i, 1)])));
				fRec120[i] = fRec121[i] - fSlow36 * (fSlow37 * fRec120[faust_wrap_sub(i, 2)] + fSlow17 * fRec120[faust_wrap_sub(i, 1)]);
				fYec13[i] = fSlow36 * (fRec120[faust_wrap_sub(i, 2)] + fRec120[i] + 2.0 * fRec120[faust_wrap_sub(i, 1)]);
				fRec119[i] = -(fSlow39 * (fSlow22 * fRec119[faust_wrap_sub(i, 1)] - fSlow19 * (fYec13[i] - fYec13[faust_wrap_sub(i, 1)])));
				fRec118[i] = fRec119[i] - fSlow41 * (fSlow42 * fRec118[faust_wrap_sub(i, 2)] + fSlow25 * fRec118[faust_wrap_sub(i, 1)]);
				fZec29[i] = fSlow33 * fRec117[faust_wrap_sub(i, 1)];
				fRec117[i] = fSlow43 * (fRec118[faust_wrap_sub(i, 2)] + (fRec118[i] - 2.0 * fRec118[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec117[faust_wrap_sub(i, 2)] + fZec29[i]);
				fRec125[i] = -(fSlow39 * (fSlow22 * fRec125[faust_wrap_sub(i, 1)] - (fYec13[i] + fYec13[faust_wrap_sub(i, 1)])));
				fRec124[i] = fRec125[i] - fSlow41 * (fSlow42 * fRec124[faust_wrap_sub(i, 2)] + fSlow25 * fRec124[faust_wrap_sub(i, 1)]);
				fYec14[i] = fSlow41 * (fRec124[faust_wrap_sub(i, 2)] + fRec124[i] + 2.0 * fRec124[faust_wrap_sub(i, 1)]);
				fRec123[i] = -(fSlow44 * (fSlow30 * fRec123[faust_wrap_sub(i, 1)] - fSlow27 * (fYec14[i] - fYec14[faust_wrap_sub(i, 1)])));
				fRec122[i] = fRec123[i] - fSlow45 * (fSlow46 * fRec122[faust_wrap_sub(i, 2)] + fSlow33 * fRec122[faust_wrap_sub(i, 1)]);
				fRec127[i] = -(fSlow44 * (fSlow30 * fRec127[faust_wrap_sub(i, 1)] - (fYec14[i] + fYec14[faust_wrap_sub(i, 1)])));
				fRec126[i] = fRec127[i] - fSlow45 * (fSlow46 * fRec126[faust_wrap_sub(i, 2)] + fSlow33 * fRec126[faust_wrap_sub(i, 1)]);
				fRec132[i] = -(fSlow2 * (fSlow3 * fRec132[faust_wrap_sub(i, 1)] - fSlow1 * (fRec10[faust_wrap_sub(i, 1)] - fRec10[faust_wrap_sub(i, 2)])));
				fRec131[i] = fRec132[i] - fSlow5 * (fSlow6 * fRec131[faust_wrap_sub(i, 2)] + fSlow8 * fRec131[faust_wrap_sub(i, 1)]);
				fZec30[i] = fSlow17 * fRec130[faust_wrap_sub(i, 1)];
				fRec130[i] = fSlow9 * (fRec131[faust_wrap_sub(i, 2)] + (fRec131[i] - 2.0 * fRec131[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec130[faust_wrap_sub(i, 2)] + fZec30[i]);
				fZec31[i] = fSlow25 * fRec129[faust_wrap_sub(i, 1)];
				fRec129[i] = fRec130[faust_wrap_sub(i, 2)] + fSlow13 * (fZec30[i] + fSlow15 * fRec130[i]) - fSlow21 * (fSlow23 * fRec129[faust_wrap_sub(i, 2)] + fZec31[i]);
				fZec32[i] = fSlow33 * fRec128[faust_wrap_sub(i, 1)];
				fRec128[i] = fRec129[faust_wrap_sub(i, 2)] + fSlow21 * (fZec31[i] + fSlow23 * fRec129[i]) - fSlow29 * (fSlow31 * fRec128[faust_wrap_sub(i, 2)] + fZec32[i]);
				fRec138[i] = -(fSlow2 * (fSlow3 * fRec138[faust_wrap_sub(i, 1)] - (fRec10[faust_wrap_sub(i, 1)] + fRec10[faust_wrap_sub(i, 2)])));
				fRec137[i] = fRec138[i] - fSlow5 * (fSlow6 * fRec137[faust_wrap_sub(i, 2)] + fSlow8 * fRec137[faust_wrap_sub(i, 1)]);
				fYec15[i] = fSlow5 * (fRec137[faust_wrap_sub(i, 2)] + fRec137[i] + 2.0 * fRec137[faust_wrap_sub(i, 1)]);
				fRec136[i] = -(fSlow34 * (fSlow14 * fRec136[faust_wrap_sub(i, 1)] - fSlow11 * (fYec15[i] - fYec15[faust_wrap_sub(i, 1)])));
				fRec135[i] = fRec136[i] - fSlow36 * (fSlow37 * fRec135[faust_wrap_sub(i, 2)] + fSlow17 * fRec135[faust_wrap_sub(i, 1)]);
				fZec33[i] = fSlow25 * fRec134[faust_wrap_sub(i, 1)];
				fRec134[i] = fSlow38 * (fRec135[faust_wrap_sub(i, 2)] + (fRec135[i] - 2.0 * fRec135[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec134[faust_wrap_sub(i, 2)] + fZec33[i]);
				fZec34[i] = fSlow33 * fRec133[faust_wrap_sub(i, 1)];
				fRec133[i] = fRec134[faust_wrap_sub(i, 2)] + fSlow21 * (fZec33[i] + fSlow23 * fRec134[i]) - fSlow29 * (fSlow31 * fRec133[faust_wrap_sub(i, 2)] + fZec34[i]);
				fRec143[i] = -(fSlow34 * (fSlow14 * fRec143[faust_wrap_sub(i, 1)] - (fYec15[i] + fYec15[faust_wrap_sub(i, 1)])));
				fRec142[i] = fRec143[i] - fSlow36 * (fSlow37 * fRec142[faust_wrap_sub(i, 2)] + fSlow17 * fRec142[faust_wrap_sub(i, 1)]);
				fYec16[i] = fSlow36 * (fRec142[faust_wrap_sub(i, 2)] + fRec142[i] + 2.0 * fRec142[faust_wrap_sub(i, 1)]);
				fRec141[i] = -(fSlow39 * (fSlow22 * fRec141[faust_wrap_sub(i, 1)] - fSlow19 * (fYec16[i] - fYec16[faust_wrap_sub(i, 1)])));
				fRec140[i] = fRec141[i] - fSlow41 * (fSlow42 * fRec140[faust_wrap_sub(i, 2)] + fSlow25 * fRec140[faust_wrap_sub(i, 1)]);
				fZec35[i] = fSlow33 * fRec139[faust_wrap_sub(i, 1)];
				fRec139[i] = fSlow43 * (fRec140[faust_wrap_sub(i, 2)] + (fRec140[i] - 2.0 * fRec140[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec139[faust_wrap_sub(i, 2)] + fZec35[i]);
				fRec147[i] = -(fSlow39 * (fSlow22 * fRec147[faust_wrap_sub(i, 1)] - (fYec16[i] + fYec16[faust_wrap_sub(i, 1)])));
				fRec146[i] = fRec147[i] - fSlow41 * (fSlow42 * fRec146[faust_wrap_sub(i, 2)] + fSlow25 * fRec146[faust_wrap_sub(i, 1)]);
				fYec17[i] = fSlow41 * (fRec146[faust_wrap_sub(i, 2)] + fRec146[i] + 2.0 * fRec146[faust_wrap_sub(i, 1)]);
				fRec145[i] = -(fSlow44 * (fSlow30 * fRec145[faust_wrap_sub(i, 1)] - fSlow27 * (fYec17[i] - fYec17[faust_wrap_sub(i, 1)])));
				fRec144[i] = fRec145[i] - fSlow45 * (fSlow46 * fRec144[faust_wrap_sub(i, 2)] + fSlow33 * fRec144[faust_wrap_sub(i, 1)]);
				fRec149[i] = -(fSlow44 * (fSlow30 * fRec149[faust_wrap_sub(i, 1)] - (fYec17[i] + fYec17[faust_wrap_sub(i, 1)])));
				fRec148[i] = fRec149[i] - fSlow45 * (fSlow46 * fRec148[faust_wrap_sub(i, 2)] + fSlow33 * fRec148[faust_wrap_sub(i, 1)]);
				fRec154[i] = -(fSlow2 * (fSlow3 * fRec154[faust_wrap_sub(i, 1)] - fSlow1 * (fRec6[faust_wrap_sub(i, 1)] - fRec6[faust_wrap_sub(i, 2)])));
				fRec153[i] = fRec154[i] - fSlow5 * (fSlow6 * fRec153[faust_wrap_sub(i, 2)] + fSlow8 * fRec153[faust_wrap_sub(i, 1)]);
				fZec36[i] = fSlow17 * fRec152[faust_wrap_sub(i, 1)];
				fRec152[i] = fSlow9 * (fRec153[faust_wrap_sub(i, 2)] + (fRec153[i] - 2.0 * fRec153[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec152[faust_wrap_sub(i, 2)] + fZec36[i]);
				fZec37[i] = fSlow25 * fRec151[faust_wrap_sub(i, 1)];
				fRec151[i] = fRec152[faust_wrap_sub(i, 2)] + fSlow13 * (fZec36[i] + fSlow15 * fRec152[i]) - fSlow21 * (fSlow23 * fRec151[faust_wrap_sub(i, 2)] + fZec37[i]);
				fZec38[i] = fSlow33 * fRec150[faust_wrap_sub(i, 1)];
				fRec150[i] = fRec151[faust_wrap_sub(i, 2)] + fSlow21 * (fZec37[i] + fSlow23 * fRec151[i]) - fSlow29 * (fSlow31 * fRec150[faust_wrap_sub(i, 2)] + fZec38[i]);
				fRec160[i] = -(fSlow2 * (fSlow3 * fRec160[faust_wrap_sub(i, 1)] - (fRec6[faust_wrap_sub(i, 1)] + fRec6[faust_wrap_sub(i, 2)])));
				fRec159[i] = fRec160[i] - fSlow5 * (fSlow6 * fRec159[faust_wrap_sub(i, 2)] + fSlow8 * fRec159[faust_wrap_sub(i, 1)]);
				fYec18[i] = fSlow5 * (fRec159[faust_wrap_sub(i, 2)] + fRec159[i] + 2.0 * fRec159[faust_wrap_sub(i, 1)]);
				fRec158[i] = -(fSlow34 * (fSlow14 * fRec158[faust_wrap_sub(i, 1)] - fSlow11 * (fYec18[i] - fYec18[faust_wrap_sub(i, 1)])));
				fRec157[i] = fRec158[i] - fSlow36 * (fSlow37 * fRec157[faust_wrap_sub(i, 2)] + fSlow17 * fRec157[faust_wrap_sub(i, 1)]);
				fZec39[i] = fSlow25 * fRec156[faust_wrap_sub(i, 1)];
				fRec156[i] = fSlow38 * (fRec157[faust_wrap_sub(i, 2)] + (fRec157[i] - 2.0 * fRec157[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec156[faust_wrap_sub(i, 2)] + fZec39[i]);
				fZec40[i] = fSlow33 * fRec155[faust_wrap_sub(i, 1)];
				fRec155[i] = fRec156[faust_wrap_sub(i, 2)] + fSlow21 * (fZec39[i] + fSlow23 * fRec156[i]) - fSlow29 * (fSlow31 * fRec155[faust_wrap_sub(i, 2)] + fZec40[i]);
				fRec165[i] = -(fSlow34 * (fSlow14 * fRec165[faust_wrap_sub(i, 1)] - (fYec18[i] + fYec18[faust_wrap_sub(i, 1)])));
				fRec164[i] = fRec165[i] - fSlow36 * (fSlow37 * fRec164[faust_wrap_sub(i, 2)] + fSlow17 * fRec164[faust_wrap_sub(i, 1)]);
				fYec19[i] = fSlow36 * (fRec164[faust_wrap_sub(i, 2)] + fRec164[i] + 2.0 * fRec164[faust_wrap_sub(i, 1)]);
				fRec163[i] = -(fSlow39 * (fSlow22 * fRec163[faust_wrap_sub(i, 1)] - fSlow19 * (fYec19[i] - fYec19[faust_wrap_sub(i, 1)])));
				fRec162[i] = fRec163[i] - fSlow41 * (fSlow42 * fRec162[faust_wrap_sub(i, 2)] + fSlow25 * fRec162[faust_wrap_sub(i, 1)]);
				fZec41[i] = fSlow33 * fRec161[faust_wrap_sub(i, 1)];
				fRec161[i] = fSlow43 * (fRec162[faust_wrap_sub(i, 2)] + (fRec162[i] - 2.0 * fRec162[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec161[faust_wrap_sub(i, 2)] + fZec41[i]);
				fRec169[i] = -(fSlow39 * (fSlow22 * fRec169[faust_wrap_sub(i, 1)] - (fYec19[i] + fYec19[faust_wrap_sub(i, 1)])));
				fRec168[i] = fRec169[i] - fSlow41 * (fSlow42 * fRec168[faust_wrap_sub(i, 2)] + fSlow25 * fRec168[faust_wrap_sub(i, 1)]);
				fYec20[i] = fSlow41 * (fRec168[faust_wrap_sub(i, 2)] + fRec168[i] + 2.0 * fRec168[faust_wrap_sub(i, 1)]);
				fRec167[i] = -(fSlow44 * (fSlow30 * fRec167[faust_wrap_sub(i, 1)] - fSlow27 * (fYec20[i] - fYec20[faust_wrap_sub(i, 1)])));
				fRec166[i] = fRec167[i] - fSlow45 * (fSlow46 * fRec166[faust_wrap_sub(i, 2)] + fSlow33 * fRec166[faust_wrap_sub(i, 1)]);
				fRec171[i] = -(fSlow44 * (fSlow30 * fRec171[faust_wrap_sub(i, 1)] - (fYec20[i] + fYec20[faust_wrap_sub(i, 1)])));
				fRec170[i] = fRec171[i] - fSlow45 * (fSlow46 * fRec170[faust_wrap_sub(i, 2)] + fSlow33 * fRec170[faust_wrap_sub(i, 1)]);
				fRec176[i] = -(fSlow2 * (fSlow3 * fRec176[faust_wrap_sub(i, 1)] - fSlow1 * (fRec14[faust_wrap_sub(i, 1)] - fRec14[faust_wrap_sub(i, 2)])));
				fRec175[i] = fRec176[i] - fSlow5 * (fSlow6 * fRec175[faust_wrap_sub(i, 2)] + fSlow8 * fRec175[faust_wrap_sub(i, 1)]);
				fZec42[i] = fSlow17 * fRec174[faust_wrap_sub(i, 1)];
				fRec174[i] = fSlow9 * (fRec175[faust_wrap_sub(i, 2)] + (fRec175[i] - 2.0 * fRec175[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec174[faust_wrap_sub(i, 2)] + fZec42[i]);
				fZec43[i] = fSlow25 * fRec173[faust_wrap_sub(i, 1)];
				fRec173[i] = fRec174[faust_wrap_sub(i, 2)] + fSlow13 * (fZec42[i] + fSlow15 * fRec174[i]) - fSlow21 * (fSlow23 * fRec173[faust_wrap_sub(i, 2)] + fZec43[i]);
				fZec44[i] = fSlow33 * fRec172[faust_wrap_sub(i, 1)];
				fRec172[i] = fRec173[faust_wrap_sub(i, 2)] + fSlow21 * (fZec43[i] + fSlow23 * fRec173[i]) - fSlow29 * (fSlow31 * fRec172[faust_wrap_sub(i, 2)] + fZec44[i]);
				fRec182[i] = -(fSlow2 * (fSlow3 * fRec182[faust_wrap_sub(i, 1)] - (fRec14[faust_wrap_sub(i, 1)] + fRec14[faust_wrap_sub(i, 2)])));
				fRec181[i] = fRec182[i] - fSlow5 * (fSlow6 * fRec181[faust_wrap_sub(i, 2)] + fSlow8 * fRec181[faust_wrap_sub(i, 1)]);
				fYec21[i] = fSlow5 * (fRec181[faust_wrap_sub(i, 2)] + fRec181[i] + 2.0 * fRec181[faust_wrap_sub(i, 1)]);
				fRec180[i] = -(fSlow34 * (fSlow14 * fRec180[faust_wrap_sub(i, 1)] - fSlow11 * (fYec21[i] - fYec21[faust_wrap_sub(i, 1)])));
				fRec179[i] = fRec180[i] - fSlow36 * (fSlow37 * fRec179[faust_wrap_sub(i, 2)] + fSlow17 * fRec179[faust_wrap_sub(i, 1)]);
				fZec45[i] = fSlow25 * fRec178[faust_wrap_sub(i, 1)];
				fRec178[i] = fSlow38 * (fRec179[faust_wrap_sub(i, 2)] + (fRec179[i] - 2.0 * fRec179[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec178[faust_wrap_sub(i, 2)] + fZec45[i]);
				fZec46[i] = fSlow33 * fRec177[faust_wrap_sub(i, 1)];
				fRec177[i] = fRec178[faust_wrap_sub(i, 2)] + fSlow21 * (fZec45[i] + fSlow23 * fRec178[i]) - fSlow29 * (fSlow31 * fRec177[faust_wrap_sub(i, 2)] + fZec46[i]);
				fRec187[i] = -(fSlow34 * (fSlow14 * fRec187[faust_wrap_sub(i, 1)] - (fYec21[i] + fYec21[faust_wrap_sub(i, 1)])));
				fRec186[i] = fRec187[i] - fSlow36 * (fSlow37 * fRec186[faust_wrap_sub(i, 2)] + fSlow17 * fRec186[faust_wrap_sub(i, 1)]);
				fYec22[i] = fSlow36 * (fRec186[faust_wrap_sub(i, 2)] + fRec186[i] + 2.0 * fRec186[faust_wrap_sub(i, 1)]);
				fRec185[i] = -(fSlow39 * (fSlow22 * fRec185[faust_wrap_sub(i, 1)] - fSlow19 * (fYec22[i] - fYec22[faust_wrap_sub(i, 1)])));
				fRec184[i] = fRec185[i] - fSlow41 * (fSlow42 * fRec184[faust_wrap_sub(i, 2)] + fSlow25 * fRec184[faust_wrap_sub(i, 1)]);
				fZec47[i] = fSlow33 * fRec183[faust_wrap_sub(i, 1)];
				fRec183[i] = fSlow43 * (fRec184[faust_wrap_sub(i, 2)] + (fRec184[i] - 2.0 * fRec184[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec183[faust_wrap_sub(i, 2)] + fZec47[i]);
				fRec191[i] = -(fSlow39 * (fSlow22 * fRec191[faust_wrap_sub(i, 1)] - (fYec22[i] + fYec22[faust_wrap_sub(i, 1)])));
				fRec190[i] = fRec191[i] - fSlow41 * (fSlow42 * fRec190[faust_wrap_sub(i, 2)] + fSlow25 * fRec190[faust_wrap_sub(i, 1)]);
				fYec23[i] = fSlow41 * (fRec190[faust_wrap_sub(i, 2)] + fRec190[i] + 2.0 * fRec190[faust_wrap_sub(i, 1)]);
				fRec189[i] = -(fSlow44 * (fSlow30 * fRec189[faust_wrap_sub(i, 1)] - fSlow27 * (fYec23[i] - fYec23[faust_wrap_sub(i, 1)])));
				fRec188[i] = fRec189[i] - fSlow45 * (fSlow46 * fRec188[faust_wrap_sub(i, 2)] + fSlow33 * fRec188[faust_wrap_sub(i, 1)]);
				fRec193[i] = -(fSlow44 * (fSlow30 * fRec193[faust_wrap_sub(i, 1)] - (fYec23[i] + fYec23[faust_wrap_sub(i, 1)])));
				fRec192[i] = fRec193[i] - fSlow45 * (fSlow46 * fRec192[faust_wrap_sub(i, 2)] + fSlow33 * fRec192[faust_wrap_sub(i, 1)]);
				fRec198[i] = -(fSlow2 * (fSlow3 * fRec198[faust_wrap_sub(i, 1)] - fSlow1 * (fRec1[faust_wrap_sub(i, 1)] - fRec1[faust_wrap_sub(i, 2)])));
				fRec197[i] = fRec198[i] - fSlow5 * (fSlow6 * fRec197[faust_wrap_sub(i, 2)] + fSlow8 * fRec197[faust_wrap_sub(i, 1)]);
				fZec48[i] = fSlow17 * fRec196[faust_wrap_sub(i, 1)];
				fRec196[i] = fSlow9 * (fRec197[faust_wrap_sub(i, 2)] + (fRec197[i] - 2.0 * fRec197[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec196[faust_wrap_sub(i, 2)] + fZec48[i]);
				fZec49[i] = fSlow25 * fRec195[faust_wrap_sub(i, 1)];
				fRec195[i] = fRec196[faust_wrap_sub(i, 2)] + fSlow13 * (fZec48[i] + fSlow15 * fRec196[i]) - fSlow21 * (fSlow23 * fRec195[faust_wrap_sub(i, 2)] + fZec49[i]);
				fZec50[i] = fSlow33 * fRec194[faust_wrap_sub(i, 1)];
				fRec194[i] = fRec195[faust_wrap_sub(i, 2)] + fSlow21 * (fZec49[i] + fSlow23 * fRec195[i]) - fSlow29 * (fSlow31 * fRec194[faust_wrap_sub(i, 2)] + fZec50[i]);
				fRec204[i] = -(fSlow2 * (fSlow3 * fRec204[faust_wrap_sub(i, 1)] - (fRec1[faust_wrap_sub(i, 1)] + fRec1[faust_wrap_sub(i, 2)])));
				fRec203[i] = fRec204[i] - fSlow5 * (fSlow6 * fRec203[faust_wrap_sub(i, 2)] + fSlow8 * fRec203[faust_wrap_sub(i, 1)]);
				fYec24[i] = fSlow5 * (fRec203[faust_wrap_sub(i, 2)] + fRec203[i] + 2.0 * fRec203[faust_wrap_sub(i, 1)]);
				fRec202[i] = -(fSlow34 * (fSlow14 * fRec202[faust_wrap_sub(i, 1)] - fSlow11 * (fYec24[i] - fYec24[faust_wrap_sub(i, 1)])));
				fRec201[i] = fRec202[i] - fSlow36 * (fSlow37 * fRec201[faust_wrap_sub(i, 2)] + fSlow17 * fRec201[faust_wrap_sub(i, 1)]);
				fZec51[i] = fSlow25 * fRec200[faust_wrap_sub(i, 1)];
				fRec200[i] = fSlow38 * (fRec201[faust_wrap_sub(i, 2)] + (fRec201[i] - 2.0 * fRec201[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec200[faust_wrap_sub(i, 2)] + fZec51[i]);
				fZec52[i] = fSlow33 * fRec199[faust_wrap_sub(i, 1)];
				fRec199[i] = fRec200[faust_wrap_sub(i, 2)] + fSlow21 * (fZec51[i] + fSlow23 * fRec200[i]) - fSlow29 * (fSlow31 * fRec199[faust_wrap_sub(i, 2)] + fZec52[i]);
				fRec209[i] = -(fSlow34 * (fSlow14 * fRec209[faust_wrap_sub(i, 1)] - (fYec24[i] + fYec24[faust_wrap_sub(i, 1)])));
				fRec208[i] = fRec209[i] - fSlow36 * (fSlow37 * fRec208[faust_wrap_sub(i, 2)] + fSlow17 * fRec208[faust_wrap_sub(i, 1)]);
				fYec25[i] = fSlow36 * (fRec208[faust_wrap_sub(i, 2)] + fRec208[i] + 2.0 * fRec208[faust_wrap_sub(i, 1)]);
				fRec207[i] = -(fSlow39 * (fSlow22 * fRec207[faust_wrap_sub(i, 1)] - fSlow19 * (fYec25[i] - fYec25[faust_wrap_sub(i, 1)])));
				fRec206[i] = fRec207[i] - fSlow41 * (fSlow42 * fRec206[faust_wrap_sub(i, 2)] + fSlow25 * fRec206[faust_wrap_sub(i, 1)]);
				fZec53[i] = fSlow33 * fRec205[faust_wrap_sub(i, 1)];
				fRec205[i] = fSlow43 * (fRec206[faust_wrap_sub(i, 2)] + (fRec206[i] - 2.0 * fRec206[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec205[faust_wrap_sub(i, 2)] + fZec53[i]);
				fRec213[i] = -(fSlow39 * (fSlow22 * fRec213[faust_wrap_sub(i, 1)] - (fYec25[i] + fYec25[faust_wrap_sub(i, 1)])));
				fRec212[i] = fRec213[i] - fSlow41 * (fSlow42 * fRec212[faust_wrap_sub(i, 2)] + fSlow25 * fRec212[faust_wrap_sub(i, 1)]);
				fYec26[i] = fSlow41 * (fRec212[faust_wrap_sub(i, 2)] + fRec212[i] + 2.0 * fRec212[faust_wrap_sub(i, 1)]);
				fRec211[i] = -(fSlow44 * (fSlow30 * fRec211[faust_wrap_sub(i, 1)] - fSlow27 * (fYec26[i] - fYec26[faust_wrap_sub(i, 1)])));
				fRec210[i] = fRec211[i] - fSlow45 * (fSlow46 * fRec210[faust_wrap_sub(i, 2)] + fSlow33 * fRec210[faust_wrap_sub(i, 1)]);
				fRec215[i] = -(fSlow44 * (fSlow30 * fRec215[faust_wrap_sub(i, 1)] - (fYec26[i] + fYec26[faust_wrap_sub(i, 1)])));
				fRec214[i] = fRec215[i] - fSlow45 * (fSlow46 * fRec214[faust_wrap_sub(i, 2)] + fSlow33 * fRec214[faust_wrap_sub(i, 1)]);
				fRec220[i] = -(fSlow2 * (fSlow3 * fRec220[faust_wrap_sub(i, 1)] - fSlow1 * (fRec9[faust_wrap_sub(i, 1)] - fRec9[faust_wrap_sub(i, 2)])));
				fRec219[i] = fRec220[i] - fSlow5 * (fSlow6 * fRec219[faust_wrap_sub(i, 2)] + fSlow8 * fRec219[faust_wrap_sub(i, 1)]);
				fZec54[i] = fSlow17 * fRec218[faust_wrap_sub(i, 1)];
				fRec218[i] = fSlow9 * (fRec219[faust_wrap_sub(i, 2)] + (fRec219[i] - 2.0 * fRec219[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec218[faust_wrap_sub(i, 2)] + fZec54[i]);
				fZec55[i] = fSlow25 * fRec217[faust_wrap_sub(i, 1)];
				fRec217[i] = fRec218[faust_wrap_sub(i, 2)] + fSlow13 * (fZec54[i] + fSlow15 * fRec218[i]) - fSlow21 * (fSlow23 * fRec217[faust_wrap_sub(i, 2)] + fZec55[i]);
				fZec56[i] = fSlow33 * fRec216[faust_wrap_sub(i, 1)];
				fRec216[i] = fRec217[faust_wrap_sub(i, 2)] + fSlow21 * (fZec55[i] + fSlow23 * fRec217[i]) - fSlow29 * (fSlow31 * fRec216[faust_wrap_sub(i, 2)] + fZec56[i]);
				fRec226[i] = -(fSlow2 * (fSlow3 * fRec226[faust_wrap_sub(i, 1)] - (fRec9[faust_wrap_sub(i, 1)] + fRec9[faust_wrap_sub(i, 2)])));
				fRec225[i] = fRec226[i] - fSlow5 * (fSlow6 * fRec225[faust_wrap_sub(i, 2)] + fSlow8 * fRec225[faust_wrap_sub(i, 1)]);
				fYec27[i] = fSlow5 * (fRec225[faust_wrap_sub(i, 2)] + fRec225[i] + 2.0 * fRec225[faust_wrap_sub(i, 1)]);
				fRec224[i] = -(fSlow34 * (fSlow14 * fRec224[faust_wrap_sub(i, 1)] - fSlow11 * (fYec27[i] - fYec27[faust_wrap_sub(i, 1)])));
				fRec223[i] = fRec224[i] - fSlow36 * (fSlow37 * fRec223[faust_wrap_sub(i, 2)] + fSlow17 * fRec223[faust_wrap_sub(i, 1)]);
				fZec57[i] = fSlow25 * fRec222[faust_wrap_sub(i, 1)];
				fRec222[i] = fSlow38 * (fRec223[faust_wrap_sub(i, 2)] + (fRec223[i] - 2.0 * fRec223[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec222[faust_wrap_sub(i, 2)] + fZec57[i]);
				fZec58[i] = fSlow33 * fRec221[faust_wrap_sub(i, 1)];
				fRec221[i] = fRec222[faust_wrap_sub(i, 2)] + fSlow21 * (fZec57[i] + fSlow23 * fRec222[i]) - fSlow29 * (fSlow31 * fRec221[faust_wrap_sub(i, 2)] + fZec58[i]);
				fRec231[i] = -(fSlow34 * (fSlow14 * fRec231[faust_wrap_sub(i, 1)] - (fYec27[i] + fYec27[faust_wrap_sub(i, 1)])));
				fRec230[i] = fRec231[i] - fSlow36 * (fSlow37 * fRec230[faust_wrap_sub(i, 2)] + fSlow17 * fRec230[faust_wrap_sub(i, 1)]);
				fYec28[i] = fSlow36 * (fRec230[faust_wrap_sub(i, 2)] + fRec230[i] + 2.0 * fRec230[faust_wrap_sub(i, 1)]);
				fRec229[i] = -(fSlow39 * (fSlow22 * fRec229[faust_wrap_sub(i, 1)] - fSlow19 * (fYec28[i] - fYec28[faust_wrap_sub(i, 1)])));
				fRec228[i] = fRec229[i] - fSlow41 * (fSlow42 * fRec228[faust_wrap_sub(i, 2)] + fSlow25 * fRec228[faust_wrap_sub(i, 1)]);
				fZec59[i] = fSlow33 * fRec227[faust_wrap_sub(i, 1)];
				fRec227[i] = fSlow43 * (fRec228[faust_wrap_sub(i, 2)] + (fRec228[i] - 2.0 * fRec228[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec227[faust_wrap_sub(i, 2)] + fZec59[i]);
				fRec235[i] = -(fSlow39 * (fSlow22 * fRec235[faust_wrap_sub(i, 1)] - (fYec28[i] + fYec28[faust_wrap_sub(i, 1)])));
				fRec234[i] = fRec235[i] - fSlow41 * (fSlow42 * fRec234[faust_wrap_sub(i, 2)] + fSlow25 * fRec234[faust_wrap_sub(i, 1)]);
				fYec29[i] = fSlow41 * (fRec234[faust_wrap_sub(i, 2)] + fRec234[i] + 2.0 * fRec234[faust_wrap_sub(i, 1)]);
				fRec233[i] = -(fSlow44 * (fSlow30 * fRec233[faust_wrap_sub(i, 1)] - fSlow27 * (fYec29[i] - fYec29[faust_wrap_sub(i, 1)])));
				fRec232[i] = fRec233[i] - fSlow45 * (fSlow46 * fRec232[faust_wrap_sub(i, 2)] + fSlow33 * fRec232[faust_wrap_sub(i, 1)]);
				fRec237[i] = -(fSlow44 * (fSlow30 * fRec237[faust_wrap_sub(i, 1)] - (fYec29[i] + fYec29[faust_wrap_sub(i, 1)])));
				fRec236[i] = fRec237[i] - fSlow45 * (fSlow46 * fRec236[faust_wrap_sub(i, 2)] + fSlow33 * fRec236[faust_wrap_sub(i, 1)]);
				fRec242[i] = -(fSlow2 * (fSlow3 * fRec242[faust_wrap_sub(i, 1)] - fSlow1 * (fRec5[faust_wrap_sub(i, 1)] - fRec5[faust_wrap_sub(i, 2)])));
				fRec241[i] = fRec242[i] - fSlow5 * (fSlow6 * fRec241[faust_wrap_sub(i, 2)] + fSlow8 * fRec241[faust_wrap_sub(i, 1)]);
				fZec60[i] = fSlow17 * fRec240[faust_wrap_sub(i, 1)];
				fRec240[i] = fSlow9 * (fRec241[faust_wrap_sub(i, 2)] + (fRec241[i] - 2.0 * fRec241[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec240[faust_wrap_sub(i, 2)] + fZec60[i]);
				fZec61[i] = fSlow25 * fRec239[faust_wrap_sub(i, 1)];
				fRec239[i] = fRec240[faust_wrap_sub(i, 2)] + fSlow13 * (fZec60[i] + fSlow15 * fRec240[i]) - fSlow21 * (fSlow23 * fRec239[faust_wrap_sub(i, 2)] + fZec61[i]);
				fZec62[i] = fSlow33 * fRec238[faust_wrap_sub(i, 1)];
				fRec238[i] = fRec239[faust_wrap_sub(i, 2)] + fSlow21 * (fZec61[i] + fSlow23 * fRec239[i]) - fSlow29 * (fSlow31 * fRec238[faust_wrap_sub(i, 2)] + fZec62[i]);
				fRec248[i] = -(fSlow2 * (fSlow3 * fRec248[faust_wrap_sub(i, 1)] - (fRec5[faust_wrap_sub(i, 1)] + fRec5[faust_wrap_sub(i, 2)])));
				fRec247[i] = fRec248[i] - fSlow5 * (fSlow6 * fRec247[faust_wrap_sub(i, 2)] + fSlow8 * fRec247[faust_wrap_sub(i, 1)]);
				fYec30[i] = fSlow5 * (fRec247[faust_wrap_sub(i, 2)] + fRec247[i] + 2.0 * fRec247[faust_wrap_sub(i, 1)]);
				fRec246[i] = -(fSlow34 * (fSlow14 * fRec246[faust_wrap_sub(i, 1)] - fSlow11 * (fYec30[i] - fYec30[faust_wrap_sub(i, 1)])));
				fRec245[i] = fRec246[i] - fSlow36 * (fSlow37 * fRec245[faust_wrap_sub(i, 2)] + fSlow17 * fRec245[faust_wrap_sub(i, 1)]);
				fZec63[i] = fSlow25 * fRec244[faust_wrap_sub(i, 1)];
				fRec244[i] = fSlow38 * (fRec245[faust_wrap_sub(i, 2)] + (fRec245[i] - 2.0 * fRec245[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec244[faust_wrap_sub(i, 2)] + fZec63[i]);
				fZec64[i] = fSlow33 * fRec243[faust_wrap_sub(i, 1)];
				fRec243[i] = fRec244[faust_wrap_sub(i, 2)] + fSlow21 * (fZec63[i] + fSlow23 * fRec244[i]) - fSlow29 * (fSlow31 * fRec243[faust_wrap_sub(i, 2)] + fZec64[i]);
				fRec253[i] = -(fSlow34 * (fSlow14 * fRec253[faust_wrap_sub(i, 1)] - (fYec30[i] + fYec30[faust_wrap_sub(i, 1)])));
				fRec252[i] = fRec253[i] - fSlow36 * (fSlow37 * fRec252[faust_wrap_sub(i, 2)] + fSlow17 * fRec252[faust_wrap_sub(i, 1)]);
				fYec31[i] = fSlow36 * (fRec252[faust_wrap_sub(i, 2)] + fRec252[i] + 2.0 * fRec252[faust_wrap_sub(i, 1)]);
				fRec251[i] = -(fSlow39 * (fSlow22 * fRec251[faust_wrap_sub(i, 1)] - fSlow19 * (fYec31[i] - fYec31[faust_wrap_sub(i, 1)])));
				fRec250[i] = fRec251[i] - fSlow41 * (fSlow42 * fRec250[faust_wrap_sub(i, 2)] + fSlow25 * fRec250[faust_wrap_sub(i, 1)]);
				fZec65[i] = fSlow33 * fRec249[faust_wrap_sub(i, 1)];
				fRec249[i] = fSlow43 * (fRec250[faust_wrap_sub(i, 2)] + (fRec250[i] - 2.0 * fRec250[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec249[faust_wrap_sub(i, 2)] + fZec65[i]);
				fRec257[i] = -(fSlow39 * (fSlow22 * fRec257[faust_wrap_sub(i, 1)] - (fYec31[i] + fYec31[faust_wrap_sub(i, 1)])));
				fRec256[i] = fRec257[i] - fSlow41 * (fSlow42 * fRec256[faust_wrap_sub(i, 2)] + fSlow25 * fRec256[faust_wrap_sub(i, 1)]);
				fYec32[i] = fSlow41 * (fRec256[faust_wrap_sub(i, 2)] + fRec256[i] + 2.0 * fRec256[faust_wrap_sub(i, 1)]);
				fRec255[i] = -(fSlow44 * (fSlow30 * fRec255[faust_wrap_sub(i, 1)] - fSlow27 * (fYec32[i] - fYec32[faust_wrap_sub(i, 1)])));
				fRec254[i] = fRec255[i] - fSlow45 * (fSlow46 * fRec254[faust_wrap_sub(i, 2)] + fSlow33 * fRec254[faust_wrap_sub(i, 1)]);
				fRec259[i] = -(fSlow44 * (fSlow30 * fRec259[faust_wrap_sub(i, 1)] - (fYec32[i] + fYec32[faust_wrap_sub(i, 1)])));
				fRec258[i] = fRec259[i] - fSlow45 * (fSlow46 * fRec258[faust_wrap_sub(i, 2)] + fSlow33 * fRec258[faust_wrap_sub(i, 1)]);
				fRec264[i] = -(fSlow2 * (fSlow3 * fRec264[faust_wrap_sub(i, 1)] - fSlow1 * (fRec13[faust_wrap_sub(i, 1)] - fRec13[faust_wrap_sub(i, 2)])));
				fRec263[i] = fRec264[i] - fSlow5 * (fSlow6 * fRec263[faust_wrap_sub(i, 2)] + fSlow8 * fRec263[faust_wrap_sub(i, 1)]);
				fZec66[i] = fSlow17 * fRec262[faust_wrap_sub(i, 1)];
				fRec262[i] = fSlow9 * (fRec263[faust_wrap_sub(i, 2)] + (fRec263[i] - 2.0 * fRec263[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec262[faust_wrap_sub(i, 2)] + fZec66[i]);
				fZec67[i] = fSlow25 * fRec261[faust_wrap_sub(i, 1)];
				fRec261[i] = fRec262[faust_wrap_sub(i, 2)] + fSlow13 * (fZec66[i] + fSlow15 * fRec262[i]) - fSlow21 * (fSlow23 * fRec261[faust_wrap_sub(i, 2)] + fZec67[i]);
				fZec68[i] = fSlow33 * fRec260[faust_wrap_sub(i, 1)];
				fRec260[i] = fRec261[faust_wrap_sub(i, 2)] + fSlow21 * (fZec67[i] + fSlow23 * fRec261[i]) - fSlow29 * (fSlow31 * fRec260[faust_wrap_sub(i, 2)] + fZec68[i]);
				fRec270[i] = -(fSlow2 * (fSlow3 * fRec270[faust_wrap_sub(i, 1)] - (fRec13[faust_wrap_sub(i, 1)] + fRec13[faust_wrap_sub(i, 2)])));
				fRec269[i] = fRec270[i] - fSlow5 * (fSlow6 * fRec269[faust_wrap_sub(i, 2)] + fSlow8 * fRec269[faust_wrap_sub(i, 1)]);
				fYec33[i] = fSlow5 * (fRec269[faust_wrap_sub(i, 2)] + fRec269[i] + 2.0 * fRec269[faust_wrap_sub(i, 1)]);
				fRec268[i] = -(fSlow34 * (fSlow14 * fRec268[faust_wrap_sub(i, 1)] - fSlow11 * (fYec33[i] - fYec33[faust_wrap_sub(i, 1)])));
				fRec267[i] = fRec268[i] - fSlow36 * (fSlow37 * fRec267[faust_wrap_sub(i, 2)] + fSlow17 * fRec267[faust_wrap_sub(i, 1)]);
				fZec69[i] = fSlow25 * fRec266[faust_wrap_sub(i, 1)];
				fRec266[i] = fSlow38 * (fRec267[faust_wrap_sub(i, 2)] + (fRec267[i] - 2.0 * fRec267[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec266[faust_wrap_sub(i, 2)] + fZec69[i]);
				fZec70[i] = fSlow33 * fRec265[faust_wrap_sub(i, 1)];
				fRec265[i] = fRec266[faust_wrap_sub(i, 2)] + fSlow21 * (fZec69[i] + fSlow23 * fRec266[i]) - fSlow29 * (fSlow31 * fRec265[faust_wrap_sub(i, 2)] + fZec70[i]);
				fRec275[i] = -(fSlow34 * (fSlow14 * fRec275[faust_wrap_sub(i, 1)] - (fYec33[i] + fYec33[faust_wrap_sub(i, 1)])));
				fRec274[i] = fRec275[i] - fSlow36 * (fSlow37 * fRec274[faust_wrap_sub(i, 2)] + fSlow17 * fRec274[faust_wrap_sub(i, 1)]);
				fYec34[i] = fSlow36 * (fRec274[faust_wrap_sub(i, 2)] + fRec274[i] + 2.0 * fRec274[faust_wrap_sub(i, 1)]);
				fRec273[i] = -(fSlow39 * (fSlow22 * fRec273[faust_wrap_sub(i, 1)] - fSlow19 * (fYec34[i] - fYec34[faust_wrap_sub(i, 1)])));
				fRec272[i] = fRec273[i] - fSlow41 * (fSlow42 * fRec272[faust_wrap_sub(i, 2)] + fSlow25 * fRec272[faust_wrap_sub(i, 1)]);
				fZec71[i] = fSlow33 * fRec271[faust_wrap_sub(i, 1)];
				fRec271[i] = fSlow43 * (fRec272[faust_wrap_sub(i, 2)] + (fRec272[i] - 2.0 * fRec272[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec271[faust_wrap_sub(i, 2)] + fZec71[i]);
				fRec279[i] = -(fSlow39 * (fSlow22 * fRec279[faust_wrap_sub(i, 1)] - (fYec34[i] + fYec34[faust_wrap_sub(i, 1)])));
				fRec278[i] = fRec279[i] - fSlow41 * (fSlow42 * fRec278[faust_wrap_sub(i, 2)] + fSlow25 * fRec278[faust_wrap_sub(i, 1)]);
				fYec35[i] = fSlow41 * (fRec278[faust_wrap_sub(i, 2)] + fRec278[i] + 2.0 * fRec278[faust_wrap_sub(i, 1)]);
				fRec277[i] = -(fSlow44 * (fSlow30 * fRec277[faust_wrap_sub(i, 1)] - fSlow27 * (fYec35[i] - fYec35[faust_wrap_sub(i, 1)])));
				fRec276[i] = fRec277[i] - fSlow45 * (fSlow46 * fRec276[faust_wrap_sub(i, 2)] + fSlow33 * fRec276[faust_wrap_sub(i, 1)]);
				fRec281[i] = -(fSlow44 * (fSlow30 * fRec281[faust_wrap_sub(i, 1)] - (fYec35[i] + fYec35[faust_wrap_sub(i, 1)])));
				fRec280[i] = fRec281[i] - fSlow45 * (fSlow46 * fRec280[faust_wrap_sub(i, 2)] + fSlow33 * fRec280[faust_wrap_sub(i, 1)]);
				fRec286[i] = -(fSlow2 * (fSlow3 * fRec286[faust_wrap_sub(i, 1)] - fSlow1 * (fRec3[faust_wrap_sub(i, 1)] - fRec3[faust_wrap_sub(i, 2)])));
				fRec285[i] = fRec286[i] - fSlow5 * (fSlow6 * fRec285[faust_wrap_sub(i, 2)] + fSlow8 * fRec285[faust_wrap_sub(i, 1)]);
				fZec72[i] = fSlow17 * fRec284[faust_wrap_sub(i, 1)];
				fRec284[i] = fSlow9 * (fRec285[faust_wrap_sub(i, 2)] + (fRec285[i] - 2.0 * fRec285[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec284[faust_wrap_sub(i, 2)] + fZec72[i]);
				fZec73[i] = fSlow25 * fRec283[faust_wrap_sub(i, 1)];
				fRec283[i] = fRec284[faust_wrap_sub(i, 2)] + fSlow13 * (fZec72[i] + fSlow15 * fRec284[i]) - fSlow21 * (fSlow23 * fRec283[faust_wrap_sub(i, 2)] + fZec73[i]);
				fZec74[i] = fSlow33 * fRec282[faust_wrap_sub(i, 1)];
				fRec282[i] = fRec283[faust_wrap_sub(i, 2)] + fSlow21 * (fZec73[i] + fSlow23 * fRec283[i]) - fSlow29 * (fSlow31 * fRec282[faust_wrap_sub(i, 2)] + fZec74[i]);
				fRec292[i] = -(fSlow2 * (fSlow3 * fRec292[faust_wrap_sub(i, 1)] - (fRec3[faust_wrap_sub(i, 1)] + fRec3[faust_wrap_sub(i, 2)])));
				fRec291[i] = fRec292[i] - fSlow5 * (fSlow6 * fRec291[faust_wrap_sub(i, 2)] + fSlow8 * fRec291[faust_wrap_sub(i, 1)]);
				fYec36[i] = fSlow5 * (fRec291[faust_wrap_sub(i, 2)] + fRec291[i] + 2.0 * fRec291[faust_wrap_sub(i, 1)]);
				fRec290[i] = -(fSlow34 * (fSlow14 * fRec290[faust_wrap_sub(i, 1)] - fSlow11 * (fYec36[i] - fYec36[faust_wrap_sub(i, 1)])));
				fRec289[i] = fRec290[i] - fSlow36 * (fSlow37 * fRec289[faust_wrap_sub(i, 2)] + fSlow17 * fRec289[faust_wrap_sub(i, 1)]);
				fZec75[i] = fSlow25 * fRec288[faust_wrap_sub(i, 1)];
				fRec288[i] = fSlow38 * (fRec289[faust_wrap_sub(i, 2)] + (fRec289[i] - 2.0 * fRec289[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec288[faust_wrap_sub(i, 2)] + fZec75[i]);
				fZec76[i] = fSlow33 * fRec287[faust_wrap_sub(i, 1)];
				fRec287[i] = fRec288[faust_wrap_sub(i, 2)] + fSlow21 * (fZec75[i] + fSlow23 * fRec288[i]) - fSlow29 * (fSlow31 * fRec287[faust_wrap_sub(i, 2)] + fZec76[i]);
				fRec297[i] = -(fSlow34 * (fSlow14 * fRec297[faust_wrap_sub(i, 1)] - (fYec36[i] + fYec36[faust_wrap_sub(i, 1)])));
				fRec296[i] = fRec297[i] - fSlow36 * (fSlow37 * fRec296[faust_wrap_sub(i, 2)] + fSlow17 * fRec296[faust_wrap_sub(i, 1)]);
				fYec37[i] = fSlow36 * (fRec296[faust_wrap_sub(i, 2)] + fRec296[i] + 2.0 * fRec296[faust_wrap_sub(i, 1)]);
				fRec295[i] = -(fSlow39 * (fSlow22 * fRec295[faust_wrap_sub(i, 1)] - fSlow19 * (fYec37[i] - fYec37[faust_wrap_sub(i, 1)])));
				fRec294[i] = fRec295[i] - fSlow41 * (fSlow42 * fRec294[faust_wrap_sub(i, 2)] + fSlow25 * fRec294[faust_wrap_sub(i, 1)]);
				fZec77[i] = fSlow33 * fRec293[faust_wrap_sub(i, 1)];
				fRec293[i] = fSlow43 * (fRec294[faust_wrap_sub(i, 2)] + (fRec294[i] - 2.0 * fRec294[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec293[faust_wrap_sub(i, 2)] + fZec77[i]);
				fRec301[i] = -(fSlow39 * (fSlow22 * fRec301[faust_wrap_sub(i, 1)] - (fYec37[i] + fYec37[faust_wrap_sub(i, 1)])));
				fRec300[i] = fRec301[i] - fSlow41 * (fSlow42 * fRec300[faust_wrap_sub(i, 2)] + fSlow25 * fRec300[faust_wrap_sub(i, 1)]);
				fYec38[i] = fSlow41 * (fRec300[faust_wrap_sub(i, 2)] + fRec300[i] + 2.0 * fRec300[faust_wrap_sub(i, 1)]);
				fRec299[i] = -(fSlow44 * (fSlow30 * fRec299[faust_wrap_sub(i, 1)] - fSlow27 * (fYec38[i] - fYec38[faust_wrap_sub(i, 1)])));
				fRec298[i] = fRec299[i] - fSlow45 * (fSlow46 * fRec298[faust_wrap_sub(i, 2)] + fSlow33 * fRec298[faust_wrap_sub(i, 1)]);
				fRec303[i] = -(fSlow44 * (fSlow30 * fRec303[faust_wrap_sub(i, 1)] - (fYec38[i] + fYec38[faust_wrap_sub(i, 1)])));
				fRec302[i] = fRec303[i] - fSlow45 * (fSlow46 * fRec302[faust_wrap_sub(i, 2)] + fSlow33 * fRec302[faust_wrap_sub(i, 1)]);
				fRec308[i] = -(fSlow2 * (fSlow3 * fRec308[faust_wrap_sub(i, 1)] - fSlow1 * (fRec11[faust_wrap_sub(i, 1)] - fRec11[faust_wrap_sub(i, 2)])));
				fRec307[i] = fRec308[i] - fSlow5 * (fSlow6 * fRec307[faust_wrap_sub(i, 2)] + fSlow8 * fRec307[faust_wrap_sub(i, 1)]);
				fZec78[i] = fSlow17 * fRec306[faust_wrap_sub(i, 1)];
				fRec306[i] = fSlow9 * (fRec307[faust_wrap_sub(i, 2)] + (fRec307[i] - 2.0 * fRec307[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec306[faust_wrap_sub(i, 2)] + fZec78[i]);
				fZec79[i] = fSlow25 * fRec305[faust_wrap_sub(i, 1)];
				fRec305[i] = fRec306[faust_wrap_sub(i, 2)] + fSlow13 * (fZec78[i] + fSlow15 * fRec306[i]) - fSlow21 * (fSlow23 * fRec305[faust_wrap_sub(i, 2)] + fZec79[i]);
				fZec80[i] = fSlow33 * fRec304[faust_wrap_sub(i, 1)];
				fRec304[i] = fRec305[faust_wrap_sub(i, 2)] + fSlow21 * (fZec79[i] + fSlow23 * fRec305[i]) - fSlow29 * (fSlow31 * fRec304[faust_wrap_sub(i, 2)] + fZec80[i]);
				fRec314[i] = -(fSlow2 * (fSlow3 * fRec314[faust_wrap_sub(i, 1)] - (fRec11[faust_wrap_sub(i, 1)] + fRec11[faust_wrap_sub(i, 2)])));
				fRec313[i] = fRec314[i] - fSlow5 * (fSlow6 * fRec313[faust_wrap_sub(i, 2)] + fSlow8 * fRec313[faust_wrap_sub(i, 1)]);
				fYec39[i] = fSlow5 * (fRec313[faust_wrap_sub(i, 2)] + fRec313[i] + 2.0 * fRec313[faust_wrap_sub(i, 1)]);
				fRec312[i] = -(fSlow34 * (fSlow14 * fRec312[faust_wrap_sub(i, 1)] - fSlow11 * (fYec39[i] - fYec39[faust_wrap_sub(i, 1)])));
				fRec311[i] = fRec312[i] - fSlow36 * (fSlow37 * fRec311[faust_wrap_sub(i, 2)] + fSlow17 * fRec311[faust_wrap_sub(i, 1)]);
				fZec81[i] = fSlow25 * fRec310[faust_wrap_sub(i, 1)];
				fRec310[i] = fSlow38 * (fRec311[faust_wrap_sub(i, 2)] + (fRec311[i] - 2.0 * fRec311[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec310[faust_wrap_sub(i, 2)] + fZec81[i]);
				fZec82[i] = fSlow33 * fRec309[faust_wrap_sub(i, 1)];
				fRec309[i] = fRec310[faust_wrap_sub(i, 2)] + fSlow21 * (fZec81[i] + fSlow23 * fRec310[i]) - fSlow29 * (fSlow31 * fRec309[faust_wrap_sub(i, 2)] + fZec82[i]);
				fRec319[i] = -(fSlow34 * (fSlow14 * fRec319[faust_wrap_sub(i, 1)] - (fYec39[i] + fYec39[faust_wrap_sub(i, 1)])));
				fRec318[i] = fRec319[i] - fSlow36 * (fSlow37 * fRec318[faust_wrap_sub(i, 2)] + fSlow17 * fRec318[faust_wrap_sub(i, 1)]);
				fYec40[i] = fSlow36 * (fRec318[faust_wrap_sub(i, 2)] + fRec318[i] + 2.0 * fRec318[faust_wrap_sub(i, 1)]);
				fRec317[i] = -(fSlow39 * (fSlow22 * fRec317[faust_wrap_sub(i, 1)] - fSlow19 * (fYec40[i] - fYec40[faust_wrap_sub(i, 1)])));
				fRec316[i] = fRec317[i] - fSlow41 * (fSlow42 * fRec316[faust_wrap_sub(i, 2)] + fSlow25 * fRec316[faust_wrap_sub(i, 1)]);
				fZec83[i] = fSlow33 * fRec315[faust_wrap_sub(i, 1)];
				fRec315[i] = fSlow43 * (fRec316[faust_wrap_sub(i, 2)] + (fRec316[i] - 2.0 * fRec316[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec315[faust_wrap_sub(i, 2)] + fZec83[i]);
				fRec323[i] = -(fSlow39 * (fSlow22 * fRec323[faust_wrap_sub(i, 1)] - (fYec40[i] + fYec40[faust_wrap_sub(i, 1)])));
				fRec322[i] = fRec323[i] - fSlow41 * (fSlow42 * fRec322[faust_wrap_sub(i, 2)] + fSlow25 * fRec322[faust_wrap_sub(i, 1)]);
				fYec41[i] = fSlow41 * (fRec322[faust_wrap_sub(i, 2)] + fRec322[i] + 2.0 * fRec322[faust_wrap_sub(i, 1)]);
				fRec321[i] = -(fSlow44 * (fSlow30 * fRec321[faust_wrap_sub(i, 1)] - fSlow27 * (fYec41[i] - fYec41[faust_wrap_sub(i, 1)])));
				fRec320[i] = fRec321[i] - fSlow45 * (fSlow46 * fRec320[faust_wrap_sub(i, 2)] + fSlow33 * fRec320[faust_wrap_sub(i, 1)]);
				fRec325[i] = -(fSlow44 * (fSlow30 * fRec325[faust_wrap_sub(i, 1)] - (fYec41[i] + fYec41[faust_wrap_sub(i, 1)])));
				fRec324[i] = fRec325[i] - fSlow45 * (fSlow46 * fRec324[faust_wrap_sub(i, 2)] + fSlow33 * fRec324[faust_wrap_sub(i, 1)]);
				fRec330[i] = -(fSlow2 * (fSlow3 * fRec330[faust_wrap_sub(i, 1)] - fSlow1 * (fRec7[faust_wrap_sub(i, 1)] - fRec7[faust_wrap_sub(i, 2)])));
				fRec329[i] = fRec330[i] - fSlow5 * (fSlow6 * fRec329[faust_wrap_sub(i, 2)] + fSlow8 * fRec329[faust_wrap_sub(i, 1)]);
				fZec84[i] = fSlow17 * fRec328[faust_wrap_sub(i, 1)];
				fRec328[i] = fSlow9 * (fRec329[faust_wrap_sub(i, 2)] + (fRec329[i] - 2.0 * fRec329[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec328[faust_wrap_sub(i, 2)] + fZec84[i]);
				fZec85[i] = fSlow25 * fRec327[faust_wrap_sub(i, 1)];
				fRec327[i] = fRec328[faust_wrap_sub(i, 2)] + fSlow13 * (fZec84[i] + fSlow15 * fRec328[i]) - fSlow21 * (fSlow23 * fRec327[faust_wrap_sub(i, 2)] + fZec85[i]);
				fZec86[i] = fSlow33 * fRec326[faust_wrap_sub(i, 1)];
				fRec326[i] = fRec327[faust_wrap_sub(i, 2)] + fSlow21 * (fZec85[i] + fSlow23 * fRec327[i]) - fSlow29 * (fSlow31 * fRec326[faust_wrap_sub(i, 2)] + fZec86[i]);
				fRec336[i] = -(fSlow2 * (fSlow3 * fRec336[faust_wrap_sub(i, 1)] - (fRec7[faust_wrap_sub(i, 1)] + fRec7[faust_wrap_sub(i, 2)])));
				fRec335[i] = fRec336[i] - fSlow5 * (fSlow6 * fRec335[faust_wrap_sub(i, 2)] + fSlow8 * fRec335[faust_wrap_sub(i, 1)]);
				fYec42[i] = fSlow5 * (fRec335[faust_wrap_sub(i, 2)] + fRec335[i] + 2.0 * fRec335[faust_wrap_sub(i, 1)]);
				fRec334[i] = -(fSlow34 * (fSlow14 * fRec334[faust_wrap_sub(i, 1)] - fSlow11 * (fYec42[i] - fYec42[faust_wrap_sub(i, 1)])));
				fRec333[i] = fRec334[i] - fSlow36 * (fSlow37 * fRec333[faust_wrap_sub(i, 2)] + fSlow17 * fRec333[faust_wrap_sub(i, 1)]);
				fZec87[i] = fSlow25 * fRec332[faust_wrap_sub(i, 1)];
				fRec332[i] = fSlow38 * (fRec333[faust_wrap_sub(i, 2)] + (fRec333[i] - 2.0 * fRec333[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec332[faust_wrap_sub(i, 2)] + fZec87[i]);
				fZec88[i] = fSlow33 * fRec331[faust_wrap_sub(i, 1)];
				fRec331[i] = fRec332[faust_wrap_sub(i, 2)] + fSlow21 * (fZec87[i] + fSlow23 * fRec332[i]) - fSlow29 * (fSlow31 * fRec331[faust_wrap_sub(i, 2)] + fZec88[i]);
				fRec341[i] = -(fSlow34 * (fSlow14 * fRec341[faust_wrap_sub(i, 1)] - (fYec42[i] + fYec42[faust_wrap_sub(i, 1)])));
				fRec340[i] = fRec341[i] - fSlow36 * (fSlow37 * fRec340[faust_wrap_sub(i, 2)] + fSlow17 * fRec340[faust_wrap_sub(i, 1)]);
				fYec43[i] = fSlow36 * (fRec340[faust_wrap_sub(i, 2)] + fRec340[i] + 2.0 * fRec340[faust_wrap_sub(i, 1)]);
				fRec339[i] = -(fSlow39 * (fSlow22 * fRec339[faust_wrap_sub(i, 1)] - fSlow19 * (fYec43[i] - fYec43[faust_wrap_sub(i, 1)])));
				fRec338[i] = fRec339[i] - fSlow41 * (fSlow42 * fRec338[faust_wrap_sub(i, 2)] + fSlow25 * fRec338[faust_wrap_sub(i, 1)]);
				fZec89[i] = fSlow33 * fRec337[faust_wrap_sub(i, 1)];
				fRec337[i] = fSlow43 * (fRec338[faust_wrap_sub(i, 2)] + (fRec338[i] - 2.0 * fRec338[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec337[faust_wrap_sub(i, 2)] + fZec89[i]);
				fRec345[i] = -(fSlow39 * (fSlow22 * fRec345[faust_wrap_sub(i, 1)] - (fYec43[i] + fYec43[faust_wrap_sub(i, 1)])));
				fRec344[i] = fRec345[i] - fSlow41 * (fSlow42 * fRec344[faust_wrap_sub(i, 2)] + fSlow25 * fRec344[faust_wrap_sub(i, 1)]);
				fYec44[i] = fSlow41 * (fRec344[faust_wrap_sub(i, 2)] + fRec344[i] + 2.0 * fRec344[faust_wrap_sub(i, 1)]);
				fRec343[i] = -(fSlow44 * (fSlow30 * fRec343[faust_wrap_sub(i, 1)] - fSlow27 * (fYec44[i] - fYec44[faust_wrap_sub(i, 1)])));
				fRec342[i] = fRec343[i] - fSlow45 * (fSlow46 * fRec342[faust_wrap_sub(i, 2)] + fSlow33 * fRec342[faust_wrap_sub(i, 1)]);
				fRec347[i] = -(fSlow44 * (fSlow30 * fRec347[faust_wrap_sub(i, 1)] - (fYec44[i] + fYec44[faust_wrap_sub(i, 1)])));
				fRec346[i] = fRec347[i] - fSlow45 * (fSlow46 * fRec346[faust_wrap_sub(i, 2)] + fSlow33 * fRec346[faust_wrap_sub(i, 1)]);
				fRec352[i] = -(fSlow2 * (fSlow3 * fRec352[faust_wrap_sub(i, 1)] - fSlow1 * (fRec15[faust_wrap_sub(i, 1)] - fRec15[faust_wrap_sub(i, 2)])));
				fRec351[i] = fRec352[i] - fSlow5 * (fSlow6 * fRec351[faust_wrap_sub(i, 2)] + fSlow8 * fRec351[faust_wrap_sub(i, 1)]);
				fZec90[i] = fSlow17 * fRec350[faust_wrap_sub(i, 1)];
				fRec350[i] = fSlow9 * (fRec351[faust_wrap_sub(i, 2)] + (fRec351[i] - 2.0 * fRec351[faust_wrap_sub(i, 1)])) - fSlow13 * (fSlow15 * fRec350[faust_wrap_sub(i, 2)] + fZec90[i]);
				fZec91[i] = fSlow25 * fRec349[faust_wrap_sub(i, 1)];
				fRec349[i] = fRec350[faust_wrap_sub(i, 2)] + fSlow13 * (fZec90[i] + fSlow15 * fRec350[i]) - fSlow21 * (fSlow23 * fRec349[faust_wrap_sub(i, 2)] + fZec91[i]);
				fZec92[i] = fSlow33 * fRec348[faust_wrap_sub(i, 1)];
				fRec348[i] = fRec349[faust_wrap_sub(i, 2)] + fSlow21 * (fZec91[i] + fSlow23 * fRec349[i]) - fSlow29 * (fSlow31 * fRec348[faust_wrap_sub(i, 2)] + fZec92[i]);
				fRec358[i] = -(fSlow2 * (fSlow3 * fRec358[faust_wrap_sub(i, 1)] - (fRec15[faust_wrap_sub(i, 1)] + fRec15[faust_wrap_sub(i, 2)])));
				fRec357[i] = fRec358[i] - fSlow5 * (fSlow6 * fRec357[faust_wrap_sub(i, 2)] + fSlow8 * fRec357[faust_wrap_sub(i, 1)]);
				fYec45[i] = fSlow5 * (fRec357[faust_wrap_sub(i, 2)] + fRec357[i] + 2.0 * fRec357[faust_wrap_sub(i, 1)]);
				fRec356[i] = -(fSlow34 * (fSlow14 * fRec356[faust_wrap_sub(i, 1)] - fSlow11 * (fYec45[i] - fYec45[faust_wrap_sub(i, 1)])));
				fRec355[i] = fRec356[i] - fSlow36 * (fSlow37 * fRec355[faust_wrap_sub(i, 2)] + fSlow17 * fRec355[faust_wrap_sub(i, 1)]);
				fZec93[i] = fSlow25 * fRec354[faust_wrap_sub(i, 1)];
				fRec354[i] = fSlow38 * (fRec355[faust_wrap_sub(i, 2)] + (fRec355[i] - 2.0 * fRec355[faust_wrap_sub(i, 1)])) - fSlow21 * (fSlow23 * fRec354[faust_wrap_sub(i, 2)] + fZec93[i]);
				fZec94[i] = fSlow33 * fRec353[faust_wrap_sub(i, 1)];
				fRec353[i] = fRec354[faust_wrap_sub(i, 2)] + fSlow21 * (fZec93[i] + fSlow23 * fRec354[i]) - fSlow29 * (fSlow31 * fRec353[faust_wrap_sub(i, 2)] + fZec94[i]);
				fRec363[i] = -(fSlow34 * (fSlow14 * fRec363[faust_wrap_sub(i, 1)] - (fYec45[i] + fYec45[faust_wrap_sub(i, 1)])));
				fRec362[i] = fRec363[i] - fSlow36 * (fSlow37 * fRec362[faust_wrap_sub(i, 2)] + fSlow17 * fRec362[faust_wrap_sub(i, 1)]);
				fYec46[i] = fSlow36 * (fRec362[faust_wrap_sub(i, 2)] + fRec362[i] + 2.0 * fRec362[faust_wrap_sub(i, 1)]);
				fRec361[i] = -(fSlow39 * (fSlow22 * fRec361[faust_wrap_sub(i, 1)] - fSlow19 * (fYec46[i] - fYec46[faust_wrap_sub(i, 1)])));
				fRec360[i] = fRec361[i] - fSlow41 * (fSlow42 * fRec360[faust_wrap_sub(i, 2)] + fSlow25 * fRec360[faust_wrap_sub(i, 1)]);
				fZec95[i] = fSlow33 * fRec359[faust_wrap_sub(i, 1)];
				fRec359[i] = fSlow43 * (fRec360[faust_wrap_sub(i, 2)] + (fRec360[i] - 2.0 * fRec360[faust_wrap_sub(i, 1)])) - fSlow29 * (fSlow31 * fRec359[faust_wrap_sub(i, 2)] + fZec95[i]);
				fRec367[i] = -(fSlow39 * (fSlow22 * fRec367[faust_wrap_sub(i, 1)] - (fYec46[i] + fYec46[faust_wrap_sub(i, 1)])));
				fRec366[i] = fRec367[i] - fSlow41 * (fSlow42 * fRec366[faust_wrap_sub(i, 2)] + fSlow25 * fRec366[faust_wrap_sub(i, 1)]);
				fYec47[i] = fSlow41 * (fRec366[faust_wrap_sub(i, 2)] + fRec366[i] + 2.0 * fRec366[faust_wrap_sub(i, 1)]);
				fRec365[i] = -(fSlow44 * (fSlow30 * fRec365[faust_wrap_sub(i, 1)] - fSlow27 * (fYec47[i] - fYec47[faust_wrap_sub(i, 1)])));
				fRec364[i] = fRec365[i] - fSlow45 * (fSlow46 * fRec364[faust_wrap_sub(i, 2)] + fSlow33 * fRec364[faust_wrap_sub(i, 1)]);
				fRec369[i] = -(fSlow44 * (fSlow30 * fRec369[faust_wrap_sub(i, 1)] - (fYec47[i] + fYec47[faust_wrap_sub(i, 1)])));
				fRec368[i] = fRec369[i] - fSlow45 * (fSlow46 * fRec368[faust_wrap_sub(i, 2)] + fSlow33 * fRec368[faust_wrap_sub(i, 1)]);
				fZec99[i] = fSlow54 * (fRec18[faust_wrap_sub(i, 2)] + fSlow29 * (fZec2[i] + fSlow31 * fRec18[i])) + fSlow56 * (fRec23[faust_wrap_sub(i, 2)] + fSlow29 * (fZec4[i] + fSlow31 * fRec23[i])) + fSlow58 * (fRec29[faust_wrap_sub(i, 2)] + fSlow29 * (fZec5[i] + fSlow31 * fRec29[i])) + fSlow45 * (fSlow60 * (fRec34[faust_wrap_sub(i, 2)] + (fRec34[i] - 2.0 * fRec34[faust_wrap_sub(i, 1)])) + fSlow62 * (fRec38[faust_wrap_sub(i, 2)] + fRec38[i] + 2.0 * fRec38[faust_wrap_sub(i, 1)]));
				fZec100[i] = fSlow66 * (fRec40[faust_wrap_sub(i, 2)] + fSlow29 * (fZec8[i] + fSlow31 * fRec40[i])) + fSlow67 * (fRec45[faust_wrap_sub(i, 2)] + fSlow29 * (fZec10[i] + fSlow31 * fRec45[i])) + fSlow68 * (fRec51[faust_wrap_sub(i, 2)] + fSlow29 * (fZec11[i] + fSlow31 * fRec51[i])) + fSlow45 * (fSlow69 * (fRec56[faust_wrap_sub(i, 2)] + (fRec56[i] - 2.0 * fRec56[faust_wrap_sub(i, 1)])) + fSlow70 * (fRec60[faust_wrap_sub(i, 2)] + fRec60[i] + 2.0 * fRec60[faust_wrap_sub(i, 1)]));
				fZec101[i] = fZec99[i] + fZec100[i];
				fZec102[i] = fSlow72 * (fRec62[faust_wrap_sub(i, 2)] + fSlow29 * (fZec14[i] + fSlow31 * fRec62[i])) + fSlow73 * (fRec67[faust_wrap_sub(i, 2)] + fSlow29 * (fZec16[i] + fSlow31 * fRec67[i])) + fSlow74 * (fRec73[faust_wrap_sub(i, 2)] + fSlow29 * (fZec17[i] + fSlow31 * fRec73[i])) + fSlow45 * (fSlow75 * (fRec78[faust_wrap_sub(i, 2)] + (fRec78[i] - 2.0 * fRec78[faust_wrap_sub(i, 1)])) + fSlow76 * (fRec82[faust_wrap_sub(i, 2)] + fRec82[i] + 2.0 * fRec82[faust_wrap_sub(i, 1)]));
				fZec103[i] = fSlow78 * (fRec84[faust_wrap_sub(i, 2)] + fSlow29 * (fZec20[i] + fSlow31 * fRec84[i])) + fSlow79 * (fRec89[faust_wrap_sub(i, 2)] + fSlow29 * (fZec22[i] + fSlow31 * fRec89[i])) + fSlow80 * (fRec95[faust_wrap_sub(i, 2)] + fSlow29 * (fZec23[i] + fSlow31 * fRec95[i])) + fSlow45 * (fSlow81 * (fRec100[faust_wrap_sub(i, 2)] + (fRec100[i] - 2.0 * fRec100[faust_wrap_sub(i, 1)])) + fSlow82 * (fRec104[faust_wrap_sub(i, 2)] + fRec104[i] + 2.0 * fRec104[faust_wrap_sub(i, 1)]));
				fZec104[i] = fZec102[i] + fZec103[i];
				fZec105[i] = fZec101[i] + fZec104[i];
				fZec106[i] = fSlow84 * (fRec106[faust_wrap_sub(i, 2)] + fSlow29 * (fZec26[i] + fSlow31 * fRec106[i])) + fSlow85 * (fRec111[faust_wrap_sub(i, 2)] + fSlow29 * (fZec28[i] + fSlow31 * fRec111[i])) + fSlow86 * (fRec117[faust_wrap_sub(i, 2)] + fSlow29 * (fZec29[i] + fSlow31 * fRec117[i])) + fSlow45 * (fSlow87 * (fRec122[faust_wrap_sub(i, 2)] + (fRec122[i] - 2.0 * fRec122[faust_wrap_sub(i, 1)])) + fSlow88 * (fRec126[faust_wrap_sub(i, 2)] + fRec126[i] + 2.0 * fRec126[faust_wrap_sub(i, 1)]));
				fZec107[i] = fSlow90 * (fRec128[faust_wrap_sub(i, 2)] + fSlow29 * (fZec32[i] + fSlow31 * fRec128[i])) + fSlow91 * (fRec133[faust_wrap_sub(i, 2)] + fSlow29 * (fZec34[i] + fSlow31 * fRec133[i])) + fSlow92 * (fRec139[faust_wrap_sub(i, 2)] + fSlow29 * (fZec35[i] + fSlow31 * fRec139[i])) + fSlow45 * (fSlow93 * (fRec144[faust_wrap_sub(i, 2)] + (fRec144[i] - 2.0 * fRec144[faust_wrap_sub(i, 1)])) + fSlow94 * (fRec148[faust_wrap_sub(i, 2)] + fRec148[i] + 2.0 * fRec148[faust_wrap_sub(i, 1)]));
				fZec108[i] = fZec106[i] + fZec107[i];
				fZec109[i] = fSlow96 * (fRec150[faust_wrap_sub(i, 2)] + fSlow29 * (fZec38[i] + fSlow31 * fRec150[i])) + fSlow97 * (fRec155[faust_wrap_sub(i, 2)] + fSlow29 * (fZec40[i] + fSlow31 * fRec155[i])) + fSlow98 * (fRec161[faust_wrap_sub(i, 2)] + fSlow29 * (fZec41[i] + fSlow31 * fRec161[i])) + fSlow45 * (fSlow99 * (fRec166[faust_wrap_sub(i, 2)] + (fRec166[i] - 2.0 * fRec166[faust_wrap_sub(i, 1)])) + fSlow100 * (fRec170[faust_wrap_sub(i, 2)] + fRec170[i] + 2.0 * fRec170[faust_wrap_sub(i, 1)]));
				fZec110[i] = fSlow102 * (fRec172[faust_wrap_sub(i, 2)] + fSlow29 * (fZec44[i] + fSlow31 * fRec172[i])) + fSlow103 * (fRec177[faust_wrap_sub(i, 2)] + fSlow29 * (fZec46[i] + fSlow31 * fRec177[i])) + fSlow104 * (fRec183[faust_wrap_sub(i, 2)] + fSlow29 * (fZec47[i] + fSlow31 * fRec183[i])) + fSlow45 * (fSlow105 * (fRec188[faust_wrap_sub(i, 2)] + (fRec188[i] - 2.0 * fRec188[faust_wrap_sub(i, 1)])) + fSlow106 * (fRec192[faust_wrap_sub(i, 2)] + fRec192[i] + 2.0 * fRec192[faust_wrap_sub(i, 1)]));
				fZec111[i] = fZec109[i] + fZec110[i];
				fZec112[i] = fZec108[i] + fZec111[i];
				fZec113[i] = fZec105[i] + fZec112[i];
				fZec114[i] = fSlow108 * (fRec194[faust_wrap_sub(i, 2)] + fSlow29 * (fZec50[i] + fSlow31 * fRec194[i])) + fSlow109 * (fRec199[faust_wrap_sub(i, 2)] + fSlow29 * (fZec52[i] + fSlow31 * fRec199[i])) + fSlow110 * (fRec205[faust_wrap_sub(i, 2)] + fSlow29 * (fZec53[i] + fSlow31 * fRec205[i])) + fSlow45 * (fSlow111 * (fRec210[faust_wrap_sub(i, 2)] + (fRec210[i] - 2.0 * fRec210[faust_wrap_sub(i, 1)])) + fSlow112 * (fRec214[faust_wrap_sub(i, 2)] + fRec214[i] + 2.0 * fRec214[faust_wrap_sub(i, 1)]));
				fZec115[i] = fSlow114 * (fRec216[faust_wrap_sub(i, 2)] + fSlow29 * (fZec56[i] + fSlow31 * fRec216[i])) + fSlow115 * (fRec221[faust_wrap_sub(i, 2)] + fSlow29 * (fZec58[i] + fSlow31 * fRec221[i])) + fSlow116 * (fRec227[faust_wrap_sub(i, 2)] + fSlow29 * (fZec59[i] + fSlow31 * fRec227[i])) + fSlow45 * (fSlow117 * (fRec232[faust_wrap_sub(i, 2)] + (fRec232[i] - 2.0 * fRec232[faust_wrap_sub(i, 1)])) + fSlow118 * (fRec236[faust_wrap_sub(i, 2)] + fRec236[i] + 2.0 * fRec236[faust_wrap_sub(i, 1)]));
				fZec116[i] = fZec114[i] + fZec115[i];
				fZec117[i] = fSlow120 * (fRec238[faust_wrap_sub(i, 2)] + fSlow29 * (fZec62[i] + fSlow31 * fRec238[i])) + fSlow121 * (fRec243[faust_wrap_sub(i, 2)] + fSlow29 * (fZec64[i] + fSlow31 * fRec243[i])) + fSlow122 * (fRec249[faust_wrap_sub(i, 2)] + fSlow29 * (fZec65[i] + fSlow31 * fRec249[i])) + fSlow45 * (fSlow123 * (fRec254[faust_wrap_sub(i, 2)] + (fRec254[i] - 2.0 * fRec254[faust_wrap_sub(i, 1)])) + fSlow124 * (fRec258[faust_wrap_sub(i, 2)] + fRec258[i] + 2.0 * fRec258[faust_wrap_sub(i, 1)]));
				fZec118[i] = fSlow126 * (fRec260[faust_wrap_sub(i, 2)] + fSlow29 * (fZec68[i] + fSlow31 * fRec260[i])) + fSlow127 * (fRec265[faust_wrap_sub(i, 2)] + fSlow29 * (fZec70[i] + fSlow31 * fRec265[i])) + fSlow128 * (fRec271[faust_wrap_sub(i, 2)] + fSlow29 * (fZec71[i] + fSlow31 * fRec271[i])) + fSlow45 * (fSlow129 * (fRec276[faust_wrap_sub(i, 2)] + (fRec276[i] - 2.0 * fRec276[faust_wrap_sub(i, 1)])) + fSlow130 * (fRec280[faust_wrap_sub(i, 2)] + fRec280[i] + 2.0 * fRec280[faust_wrap_sub(i, 1)]));
				fZec119[i] = fZec117[i] + fZec118[i];
				fZec120[i] = fZec116[i] + fZec119[i];
				fZec121[i] = fSlow132 * (fRec282[faust_wrap_sub(i, 2)] + fSlow29 * (fZec74[i] + fSlow31 * fRec282[i])) + fSlow133 * (fRec287[faust_wrap_sub(i, 2)] + fSlow29 * (fZec76[i] + fSlow31 * fRec287[i])) + fSlow134 * (fRec293[faust_wrap_sub(i, 2)] + fSlow29 * (fZec77[i] + fSlow31 * fRec293[i])) + fSlow45 * (fSlow135 * (fRec298[faust_wrap_sub(i, 2)] + (fRec298[i] - 2.0 * fRec298[faust_wrap_sub(i, 1)])) + fSlow136 * (fRec302[faust_wrap_sub(i, 2)] + fRec302[i] + 2.0 * fRec302[faust_wrap_sub(i, 1)]));
				fZec122[i] = fSlow138 * (fRec304[faust_wrap_sub(i, 2)] + fSlow29 * (fZec80[i] + fSlow31 * fRec304[i])) + fSlow139 * (fRec309[faust_wrap_sub(i, 2)] + fSlow29 * (fZec82[i] + fSlow31 * fRec309[i])) + fSlow140 * (fRec315[faust_wrap_sub(i, 2)] + fSlow29 * (fZec83[i] + fSlow31 * fRec315[i])) + fSlow45 * (fSlow141 * (fRec320[faust_wrap_sub(i, 2)] + (fRec320[i] - 2.0 * fRec320[faust_wrap_sub(i, 1)])) + fSlow142 * (fRec324[faust_wrap_sub(i, 2)] + fRec324[i] + 2.0 * fRec324[faust_wrap_sub(i, 1)]));
				fZec123[i] = fZec121[i] + fZec122[i];
				fZec124[i] = fSlow144 * (fRec326[faust_wrap_sub(i, 2)] + fSlow29 * (fZec86[i] + fSlow31 * fRec326[i])) + fSlow145 * (fRec331[faust_wrap_sub(i, 2)] + fSlow29 * (fZec88[i] + fSlow31 * fRec331[i])) + fSlow146 * (fRec337[faust_wrap_sub(i, 2)] + fSlow29 * (fZec89[i] + fSlow31 * fRec337[i])) + fSlow45 * (fSlow147 * (fRec342[faust_wrap_sub(i, 2)] + (fRec342[i] - 2.0 * fRec342[faust_wrap_sub(i, 1)])) + fSlow148 * (fRec346[faust_wrap_sub(i, 2)] + fRec346[i] + 2.0 * fRec346[faust_wrap_sub(i, 1)]));
				fZec125[i] = fSlow150 * (fRec348[faust_wrap_sub(i, 2)] + fSlow29 * (fZec92[i] + fSlow31 * fRec348[i])) + fSlow151 * (fRec353[faust_wrap_sub(i, 2)] + fSlow29 * (fZec94[i] + fSlow31 * fRec353[i])) + fSlow152 * (fRec359[faust_wrap_sub(i, 2)] + fSlow29 * (fZec95[i] + fSlow31 * fRec359[i])) + fSlow45 * (fSlow153 * (fRec364[faust_wrap_sub(i, 2)] + (fRec364[i] - 2.0 * fRec364[faust_wrap_sub(i, 1)])) + fSlow154 * (fRec368[faust_wrap_sub(i, 2)] + fRec368[i] + 2.0 * fRec368[faust_wrap_sub(i, 1)]));
				fZec126[i] = fZec124[i] + fZec125[i];
				fZec127[i] = fZec123[i] + fZec126[i];
				fZec128[i] = fZec120[i] + fZec127[i];
				fYec48[(faust_wrap_add(i, fYec48_idx)) & 16383] = fZec96[i] + fZec98[i] + fSlow50 * (fZec113[i] + fZec128[i]) + fZec129[i];
				fRec0[i] = fYec48[(faust_wrap_sub(faust_wrap_add(i, fYec48_idx), iSlow156)) & 16383];
				fYec49[(faust_wrap_add(i, fYec49_idx)) & 16383] = fZec130[i] + fZec131[i] + fZec96[i] + fSlow50 * (fZec113[i] - fZec128[i]);
				fRec1[i] = fYec49[(faust_wrap_sub(faust_wrap_add(i, fYec49_idx), iSlow158)) & 16383];
				fZec133[i] = fZec105[i] - fZec112[i];
				fZec134[i] = fZec120[i] - fZec127[i];
				fYec50[(faust_wrap_add(i, fYec50_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec133[i] + fZec134[i]);
				fRec2[i] = fYec50[(faust_wrap_sub(faust_wrap_add(i, fYec50_idx), iSlow159)) & 16383];
				fYec51[(faust_wrap_add(i, fYec51_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec133[i] - fZec134[i]);
				fRec3[i] = fYec51[(faust_wrap_sub(faust_wrap_add(i, fYec51_idx), iSlow160)) & 16383];
				fZec136[i] = fZec101[i] - fZec104[i];
				fZec137[i] = fZec108[i] - fZec111[i];
				fZec138[i] = fZec136[i] + fZec137[i];
				fZec139[i] = fZec116[i] - fZec119[i];
				fZec140[i] = fZec123[i] - fZec126[i];
				fZec141[i] = fZec139[i] + fZec140[i];
				fYec52[(faust_wrap_add(i, fYec52_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec138[i] + fZec141[i]);
				fRec4[i] = fYec52[(faust_wrap_sub(faust_wrap_add(i, fYec52_idx), iSlow161)) & 16383];
				fYec53[(faust_wrap_add(i, fYec53_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec138[i] - fZec141[i]);
				fRec5[i] = fYec53[(faust_wrap_sub(faust_wrap_add(i, fYec53_idx), iSlow162)) & 16383];
				fZec142[i] = fZec136[i] - fZec137[i];
				fZec143[i] = fZec139[i] - fZec140[i];
				fYec54[(faust_wrap_add(i, fYec54_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec142[i] + fZec143[i]);
				fRec6[i] = fYec54[(faust_wrap_sub(faust_wrap_add(i, fYec54_idx), iSlow163)) & 16383];
				fYec55[(faust_wrap_add(i, fYec55_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec142[i] - fZec143[i]);
				fRec7[i] = fYec55[(faust_wrap_sub(faust_wrap_add(i, fYec55_idx), iSlow164)) & 16383];
				fZec144[i] = fZec99[i] - fZec100[i];
				fZec145[i] = fZec102[i] - fZec103[i];
				fZec146[i] = fZec144[i] + fZec145[i];
				fZec147[i] = fZec106[i] - fZec107[i];
				fZec148[i] = fZec109[i] - fZec110[i];
				fZec149[i] = fZec147[i] + fZec148[i];
				fZec150[i] = fZec146[i] + fZec149[i];
				fZec151[i] = fZec114[i] - fZec115[i];
				fZec152[i] = fZec117[i] - fZec118[i];
				fZec153[i] = fZec151[i] + fZec152[i];
				fZec154[i] = fZec121[i] - fZec122[i];
				fZec155[i] = fZec124[i] - fZec125[i];
				fZec156[i] = fZec154[i] + fZec155[i];
				fZec157[i] = fZec153[i] + fZec156[i];
				fYec56[(faust_wrap_add(i, fYec56_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec150[i] + fZec157[i]);
				fRec8[i] = fYec56[(faust_wrap_sub(faust_wrap_add(i, fYec56_idx), iSlow165)) & 16383];
				fYec57[(faust_wrap_add(i, fYec57_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec150[i] - fZec157[i]);
				fRec9[i] = fYec57[(faust_wrap_sub(faust_wrap_add(i, fYec57_idx), iSlow166)) & 16383];
				fZec158[i] = fZec146[i] - fZec149[i];
				fZec159[i] = fZec153[i] - fZec156[i];
				fYec58[(faust_wrap_add(i, fYec58_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec158[i] + fZec159[i]);
				fRec10[i] = fYec58[(faust_wrap_sub(faust_wrap_add(i, fYec58_idx), iSlow167)) & 16383];
				fYec59[(faust_wrap_add(i, fYec59_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec158[i] - fZec159[i]);
				fRec11[i] = fYec59[(faust_wrap_sub(faust_wrap_add(i, fYec59_idx), iSlow168)) & 16383];
				fZec160[i] = fZec144[i] - fZec145[i];
				fZec161[i] = fZec147[i] - fZec148[i];
				fZec162[i] = fZec160[i] + fZec161[i];
				fZec163[i] = fZec151[i] - fZec152[i];
				fZec164[i] = fZec154[i] - fZec155[i];
				fZec165[i] = fZec163[i] + fZec164[i];
				fYec60[(faust_wrap_add(i, fYec60_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec162[i] + fZec165[i]);
				fRec12[i] = fYec60[(faust_wrap_sub(faust_wrap_add(i, fYec60_idx), iSlow169)) & 16383];
				fYec61[(faust_wrap_add(i, fYec61_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec162[i] - fZec165[i]);
				fRec13[i] = fYec61[(faust_wrap_sub(faust_wrap_add(i, fYec61_idx), iSlow170)) & 16383];
				fZec166[i] = fZec160[i] - fZec161[i];
				fZec167[i] = fZec163[i] - fZec164[i];
				fYec62[(faust_wrap_add(i, fYec62_idx)) & 16383] = fZec132[i] + fSlow50 * (fZec166[i] + fZec167[i]);
				fRec14[i] = fYec62[(faust_wrap_sub(faust_wrap_add(i, fYec62_idx), iSlow171)) & 16383];
				fYec63[(faust_wrap_add(i, fYec63_idx)) & 16383] = fZec135[i] + fSlow50 * (fZec166[i] - fZec167[i]);
				fRec15[i] = fYec63[(faust_wrap_sub(faust_wrap_add(i, fYec63_idx), iSlow172)) & 16383];
			}
			/* Post code */
			fYec63_idx_save = vsize;
			fYec62_idx_save = vsize;
			fYec61_idx_save = vsize;
			fYec60_idx_save = vsize;
			fYec59_idx_save = vsize;
			fYec58_idx_save = vsize;
			fYec57_idx_save = vsize;
			fYec56_idx_save = vsize;
			fYec55_idx_save = vsize;
			fYec54_idx_save = vsize;
			fYec53_idx_save = vsize;
			fYec52_idx_save = vsize;
			fYec51_idx_save = vsize;
			fYec50_idx_save = vsize;
			fYec49_idx_save = vsize;
			fYec48_idx_save = vsize;
			for (int j801 = 0; j801 < 4; j801 = faust_wrap_add(j801, 1)) {
				fRec369_perm[j801] = fRec369_tmp[faust_wrap_add(vsize, j801)];
			}
			for (int j803 = 0; j803 < 4; j803 = faust_wrap_add(j803, 1)) {
				fRec368_perm[j803] = fRec368_tmp[faust_wrap_add(vsize, j803)];
			}
			for (int j795 = 0; j795 < 4; j795 = faust_wrap_add(j795, 1)) {
				fYec47_perm[j795] = fYec47_tmp[faust_wrap_add(vsize, j795)];
			}
			for (int j791 = 0; j791 < 4; j791 = faust_wrap_add(j791, 1)) {
				fRec367_perm[j791] = fRec367_tmp[faust_wrap_add(vsize, j791)];
			}
			for (int j793 = 0; j793 < 4; j793 = faust_wrap_add(j793, 1)) {
				fRec366_perm[j793] = fRec366_tmp[faust_wrap_add(vsize, j793)];
			}
			for (int j797 = 0; j797 < 4; j797 = faust_wrap_add(j797, 1)) {
				fRec365_perm[j797] = fRec365_tmp[faust_wrap_add(vsize, j797)];
			}
			for (int j799 = 0; j799 < 4; j799 = faust_wrap_add(j799, 1)) {
				fRec364_perm[j799] = fRec364_tmp[faust_wrap_add(vsize, j799)];
			}
			for (int j783 = 0; j783 < 4; j783 = faust_wrap_add(j783, 1)) {
				fYec46_perm[j783] = fYec46_tmp[faust_wrap_add(vsize, j783)];
			}
			for (int j779 = 0; j779 < 4; j779 = faust_wrap_add(j779, 1)) {
				fRec363_perm[j779] = fRec363_tmp[faust_wrap_add(vsize, j779)];
			}
			for (int j781 = 0; j781 < 4; j781 = faust_wrap_add(j781, 1)) {
				fRec362_perm[j781] = fRec362_tmp[faust_wrap_add(vsize, j781)];
			}
			for (int j785 = 0; j785 < 4; j785 = faust_wrap_add(j785, 1)) {
				fRec361_perm[j785] = fRec361_tmp[faust_wrap_add(vsize, j785)];
			}
			for (int j787 = 0; j787 < 4; j787 = faust_wrap_add(j787, 1)) {
				fRec360_perm[j787] = fRec360_tmp[faust_wrap_add(vsize, j787)];
			}
			for (int j789 = 0; j789 < 4; j789 = faust_wrap_add(j789, 1)) {
				fRec359_perm[j789] = fRec359_tmp[faust_wrap_add(vsize, j789)];
			}
			for (int j769 = 0; j769 < 4; j769 = faust_wrap_add(j769, 1)) {
				fYec45_perm[j769] = fYec45_tmp[faust_wrap_add(vsize, j769)];
			}
			for (int j765 = 0; j765 < 4; j765 = faust_wrap_add(j765, 1)) {
				fRec358_perm[j765] = fRec358_tmp[faust_wrap_add(vsize, j765)];
			}
			for (int j767 = 0; j767 < 4; j767 = faust_wrap_add(j767, 1)) {
				fRec357_perm[j767] = fRec357_tmp[faust_wrap_add(vsize, j767)];
			}
			for (int j771 = 0; j771 < 4; j771 = faust_wrap_add(j771, 1)) {
				fRec356_perm[j771] = fRec356_tmp[faust_wrap_add(vsize, j771)];
			}
			for (int j773 = 0; j773 < 4; j773 = faust_wrap_add(j773, 1)) {
				fRec355_perm[j773] = fRec355_tmp[faust_wrap_add(vsize, j773)];
			}
			for (int j775 = 0; j775 < 4; j775 = faust_wrap_add(j775, 1)) {
				fRec354_perm[j775] = fRec354_tmp[faust_wrap_add(vsize, j775)];
			}
			for (int j777 = 0; j777 < 4; j777 = faust_wrap_add(j777, 1)) {
				fRec353_perm[j777] = fRec353_tmp[faust_wrap_add(vsize, j777)];
			}
			for (int j755 = 0; j755 < 4; j755 = faust_wrap_add(j755, 1)) {
				fRec352_perm[j755] = fRec352_tmp[faust_wrap_add(vsize, j755)];
			}
			for (int j757 = 0; j757 < 4; j757 = faust_wrap_add(j757, 1)) {
				fRec351_perm[j757] = fRec351_tmp[faust_wrap_add(vsize, j757)];
			}
			for (int j759 = 0; j759 < 4; j759 = faust_wrap_add(j759, 1)) {
				fRec350_perm[j759] = fRec350_tmp[faust_wrap_add(vsize, j759)];
			}
			for (int j761 = 0; j761 < 4; j761 = faust_wrap_add(j761, 1)) {
				fRec349_perm[j761] = fRec349_tmp[faust_wrap_add(vsize, j761)];
			}
			for (int j763 = 0; j763 < 4; j763 = faust_wrap_add(j763, 1)) {
				fRec348_perm[j763] = fRec348_tmp[faust_wrap_add(vsize, j763)];
			}
			for (int j751 = 0; j751 < 4; j751 = faust_wrap_add(j751, 1)) {
				fRec347_perm[j751] = fRec347_tmp[faust_wrap_add(vsize, j751)];
			}
			for (int j753 = 0; j753 < 4; j753 = faust_wrap_add(j753, 1)) {
				fRec346_perm[j753] = fRec346_tmp[faust_wrap_add(vsize, j753)];
			}
			for (int j745 = 0; j745 < 4; j745 = faust_wrap_add(j745, 1)) {
				fYec44_perm[j745] = fYec44_tmp[faust_wrap_add(vsize, j745)];
			}
			for (int j741 = 0; j741 < 4; j741 = faust_wrap_add(j741, 1)) {
				fRec345_perm[j741] = fRec345_tmp[faust_wrap_add(vsize, j741)];
			}
			for (int j743 = 0; j743 < 4; j743 = faust_wrap_add(j743, 1)) {
				fRec344_perm[j743] = fRec344_tmp[faust_wrap_add(vsize, j743)];
			}
			for (int j747 = 0; j747 < 4; j747 = faust_wrap_add(j747, 1)) {
				fRec343_perm[j747] = fRec343_tmp[faust_wrap_add(vsize, j747)];
			}
			for (int j749 = 0; j749 < 4; j749 = faust_wrap_add(j749, 1)) {
				fRec342_perm[j749] = fRec342_tmp[faust_wrap_add(vsize, j749)];
			}
			for (int j733 = 0; j733 < 4; j733 = faust_wrap_add(j733, 1)) {
				fYec43_perm[j733] = fYec43_tmp[faust_wrap_add(vsize, j733)];
			}
			for (int j729 = 0; j729 < 4; j729 = faust_wrap_add(j729, 1)) {
				fRec341_perm[j729] = fRec341_tmp[faust_wrap_add(vsize, j729)];
			}
			for (int j731 = 0; j731 < 4; j731 = faust_wrap_add(j731, 1)) {
				fRec340_perm[j731] = fRec340_tmp[faust_wrap_add(vsize, j731)];
			}
			for (int j735 = 0; j735 < 4; j735 = faust_wrap_add(j735, 1)) {
				fRec339_perm[j735] = fRec339_tmp[faust_wrap_add(vsize, j735)];
			}
			for (int j737 = 0; j737 < 4; j737 = faust_wrap_add(j737, 1)) {
				fRec338_perm[j737] = fRec338_tmp[faust_wrap_add(vsize, j737)];
			}
			for (int j739 = 0; j739 < 4; j739 = faust_wrap_add(j739, 1)) {
				fRec337_perm[j739] = fRec337_tmp[faust_wrap_add(vsize, j739)];
			}
			for (int j719 = 0; j719 < 4; j719 = faust_wrap_add(j719, 1)) {
				fYec42_perm[j719] = fYec42_tmp[faust_wrap_add(vsize, j719)];
			}
			for (int j715 = 0; j715 < 4; j715 = faust_wrap_add(j715, 1)) {
				fRec336_perm[j715] = fRec336_tmp[faust_wrap_add(vsize, j715)];
			}
			for (int j717 = 0; j717 < 4; j717 = faust_wrap_add(j717, 1)) {
				fRec335_perm[j717] = fRec335_tmp[faust_wrap_add(vsize, j717)];
			}
			for (int j721 = 0; j721 < 4; j721 = faust_wrap_add(j721, 1)) {
				fRec334_perm[j721] = fRec334_tmp[faust_wrap_add(vsize, j721)];
			}
			for (int j723 = 0; j723 < 4; j723 = faust_wrap_add(j723, 1)) {
				fRec333_perm[j723] = fRec333_tmp[faust_wrap_add(vsize, j723)];
			}
			for (int j725 = 0; j725 < 4; j725 = faust_wrap_add(j725, 1)) {
				fRec332_perm[j725] = fRec332_tmp[faust_wrap_add(vsize, j725)];
			}
			for (int j727 = 0; j727 < 4; j727 = faust_wrap_add(j727, 1)) {
				fRec331_perm[j727] = fRec331_tmp[faust_wrap_add(vsize, j727)];
			}
			for (int j705 = 0; j705 < 4; j705 = faust_wrap_add(j705, 1)) {
				fRec330_perm[j705] = fRec330_tmp[faust_wrap_add(vsize, j705)];
			}
			for (int j707 = 0; j707 < 4; j707 = faust_wrap_add(j707, 1)) {
				fRec329_perm[j707] = fRec329_tmp[faust_wrap_add(vsize, j707)];
			}
			for (int j709 = 0; j709 < 4; j709 = faust_wrap_add(j709, 1)) {
				fRec328_perm[j709] = fRec328_tmp[faust_wrap_add(vsize, j709)];
			}
			for (int j711 = 0; j711 < 4; j711 = faust_wrap_add(j711, 1)) {
				fRec327_perm[j711] = fRec327_tmp[faust_wrap_add(vsize, j711)];
			}
			for (int j713 = 0; j713 < 4; j713 = faust_wrap_add(j713, 1)) {
				fRec326_perm[j713] = fRec326_tmp[faust_wrap_add(vsize, j713)];
			}
			for (int j701 = 0; j701 < 4; j701 = faust_wrap_add(j701, 1)) {
				fRec325_perm[j701] = fRec325_tmp[faust_wrap_add(vsize, j701)];
			}
			for (int j703 = 0; j703 < 4; j703 = faust_wrap_add(j703, 1)) {
				fRec324_perm[j703] = fRec324_tmp[faust_wrap_add(vsize, j703)];
			}
			for (int j695 = 0; j695 < 4; j695 = faust_wrap_add(j695, 1)) {
				fYec41_perm[j695] = fYec41_tmp[faust_wrap_add(vsize, j695)];
			}
			for (int j691 = 0; j691 < 4; j691 = faust_wrap_add(j691, 1)) {
				fRec323_perm[j691] = fRec323_tmp[faust_wrap_add(vsize, j691)];
			}
			for (int j693 = 0; j693 < 4; j693 = faust_wrap_add(j693, 1)) {
				fRec322_perm[j693] = fRec322_tmp[faust_wrap_add(vsize, j693)];
			}
			for (int j697 = 0; j697 < 4; j697 = faust_wrap_add(j697, 1)) {
				fRec321_perm[j697] = fRec321_tmp[faust_wrap_add(vsize, j697)];
			}
			for (int j699 = 0; j699 < 4; j699 = faust_wrap_add(j699, 1)) {
				fRec320_perm[j699] = fRec320_tmp[faust_wrap_add(vsize, j699)];
			}
			for (int j683 = 0; j683 < 4; j683 = faust_wrap_add(j683, 1)) {
				fYec40_perm[j683] = fYec40_tmp[faust_wrap_add(vsize, j683)];
			}
			for (int j679 = 0; j679 < 4; j679 = faust_wrap_add(j679, 1)) {
				fRec319_perm[j679] = fRec319_tmp[faust_wrap_add(vsize, j679)];
			}
			for (int j681 = 0; j681 < 4; j681 = faust_wrap_add(j681, 1)) {
				fRec318_perm[j681] = fRec318_tmp[faust_wrap_add(vsize, j681)];
			}
			for (int j685 = 0; j685 < 4; j685 = faust_wrap_add(j685, 1)) {
				fRec317_perm[j685] = fRec317_tmp[faust_wrap_add(vsize, j685)];
			}
			for (int j687 = 0; j687 < 4; j687 = faust_wrap_add(j687, 1)) {
				fRec316_perm[j687] = fRec316_tmp[faust_wrap_add(vsize, j687)];
			}
			for (int j689 = 0; j689 < 4; j689 = faust_wrap_add(j689, 1)) {
				fRec315_perm[j689] = fRec315_tmp[faust_wrap_add(vsize, j689)];
			}
			for (int j669 = 0; j669 < 4; j669 = faust_wrap_add(j669, 1)) {
				fYec39_perm[j669] = fYec39_tmp[faust_wrap_add(vsize, j669)];
			}
			for (int j665 = 0; j665 < 4; j665 = faust_wrap_add(j665, 1)) {
				fRec314_perm[j665] = fRec314_tmp[faust_wrap_add(vsize, j665)];
			}
			for (int j667 = 0; j667 < 4; j667 = faust_wrap_add(j667, 1)) {
				fRec313_perm[j667] = fRec313_tmp[faust_wrap_add(vsize, j667)];
			}
			for (int j671 = 0; j671 < 4; j671 = faust_wrap_add(j671, 1)) {
				fRec312_perm[j671] = fRec312_tmp[faust_wrap_add(vsize, j671)];
			}
			for (int j673 = 0; j673 < 4; j673 = faust_wrap_add(j673, 1)) {
				fRec311_perm[j673] = fRec311_tmp[faust_wrap_add(vsize, j673)];
			}
			for (int j675 = 0; j675 < 4; j675 = faust_wrap_add(j675, 1)) {
				fRec310_perm[j675] = fRec310_tmp[faust_wrap_add(vsize, j675)];
			}
			for (int j677 = 0; j677 < 4; j677 = faust_wrap_add(j677, 1)) {
				fRec309_perm[j677] = fRec309_tmp[faust_wrap_add(vsize, j677)];
			}
			for (int j655 = 0; j655 < 4; j655 = faust_wrap_add(j655, 1)) {
				fRec308_perm[j655] = fRec308_tmp[faust_wrap_add(vsize, j655)];
			}
			for (int j657 = 0; j657 < 4; j657 = faust_wrap_add(j657, 1)) {
				fRec307_perm[j657] = fRec307_tmp[faust_wrap_add(vsize, j657)];
			}
			for (int j659 = 0; j659 < 4; j659 = faust_wrap_add(j659, 1)) {
				fRec306_perm[j659] = fRec306_tmp[faust_wrap_add(vsize, j659)];
			}
			for (int j661 = 0; j661 < 4; j661 = faust_wrap_add(j661, 1)) {
				fRec305_perm[j661] = fRec305_tmp[faust_wrap_add(vsize, j661)];
			}
			for (int j663 = 0; j663 < 4; j663 = faust_wrap_add(j663, 1)) {
				fRec304_perm[j663] = fRec304_tmp[faust_wrap_add(vsize, j663)];
			}
			for (int j651 = 0; j651 < 4; j651 = faust_wrap_add(j651, 1)) {
				fRec303_perm[j651] = fRec303_tmp[faust_wrap_add(vsize, j651)];
			}
			for (int j653 = 0; j653 < 4; j653 = faust_wrap_add(j653, 1)) {
				fRec302_perm[j653] = fRec302_tmp[faust_wrap_add(vsize, j653)];
			}
			for (int j645 = 0; j645 < 4; j645 = faust_wrap_add(j645, 1)) {
				fYec38_perm[j645] = fYec38_tmp[faust_wrap_add(vsize, j645)];
			}
			for (int j641 = 0; j641 < 4; j641 = faust_wrap_add(j641, 1)) {
				fRec301_perm[j641] = fRec301_tmp[faust_wrap_add(vsize, j641)];
			}
			for (int j643 = 0; j643 < 4; j643 = faust_wrap_add(j643, 1)) {
				fRec300_perm[j643] = fRec300_tmp[faust_wrap_add(vsize, j643)];
			}
			for (int j647 = 0; j647 < 4; j647 = faust_wrap_add(j647, 1)) {
				fRec299_perm[j647] = fRec299_tmp[faust_wrap_add(vsize, j647)];
			}
			for (int j649 = 0; j649 < 4; j649 = faust_wrap_add(j649, 1)) {
				fRec298_perm[j649] = fRec298_tmp[faust_wrap_add(vsize, j649)];
			}
			for (int j633 = 0; j633 < 4; j633 = faust_wrap_add(j633, 1)) {
				fYec37_perm[j633] = fYec37_tmp[faust_wrap_add(vsize, j633)];
			}
			for (int j629 = 0; j629 < 4; j629 = faust_wrap_add(j629, 1)) {
				fRec297_perm[j629] = fRec297_tmp[faust_wrap_add(vsize, j629)];
			}
			for (int j631 = 0; j631 < 4; j631 = faust_wrap_add(j631, 1)) {
				fRec296_perm[j631] = fRec296_tmp[faust_wrap_add(vsize, j631)];
			}
			for (int j635 = 0; j635 < 4; j635 = faust_wrap_add(j635, 1)) {
				fRec295_perm[j635] = fRec295_tmp[faust_wrap_add(vsize, j635)];
			}
			for (int j637 = 0; j637 < 4; j637 = faust_wrap_add(j637, 1)) {
				fRec294_perm[j637] = fRec294_tmp[faust_wrap_add(vsize, j637)];
			}
			for (int j639 = 0; j639 < 4; j639 = faust_wrap_add(j639, 1)) {
				fRec293_perm[j639] = fRec293_tmp[faust_wrap_add(vsize, j639)];
			}
			for (int j619 = 0; j619 < 4; j619 = faust_wrap_add(j619, 1)) {
				fYec36_perm[j619] = fYec36_tmp[faust_wrap_add(vsize, j619)];
			}
			for (int j615 = 0; j615 < 4; j615 = faust_wrap_add(j615, 1)) {
				fRec292_perm[j615] = fRec292_tmp[faust_wrap_add(vsize, j615)];
			}
			for (int j617 = 0; j617 < 4; j617 = faust_wrap_add(j617, 1)) {
				fRec291_perm[j617] = fRec291_tmp[faust_wrap_add(vsize, j617)];
			}
			for (int j621 = 0; j621 < 4; j621 = faust_wrap_add(j621, 1)) {
				fRec290_perm[j621] = fRec290_tmp[faust_wrap_add(vsize, j621)];
			}
			for (int j623 = 0; j623 < 4; j623 = faust_wrap_add(j623, 1)) {
				fRec289_perm[j623] = fRec289_tmp[faust_wrap_add(vsize, j623)];
			}
			for (int j625 = 0; j625 < 4; j625 = faust_wrap_add(j625, 1)) {
				fRec288_perm[j625] = fRec288_tmp[faust_wrap_add(vsize, j625)];
			}
			for (int j627 = 0; j627 < 4; j627 = faust_wrap_add(j627, 1)) {
				fRec287_perm[j627] = fRec287_tmp[faust_wrap_add(vsize, j627)];
			}
			for (int j605 = 0; j605 < 4; j605 = faust_wrap_add(j605, 1)) {
				fRec286_perm[j605] = fRec286_tmp[faust_wrap_add(vsize, j605)];
			}
			for (int j607 = 0; j607 < 4; j607 = faust_wrap_add(j607, 1)) {
				fRec285_perm[j607] = fRec285_tmp[faust_wrap_add(vsize, j607)];
			}
			for (int j609 = 0; j609 < 4; j609 = faust_wrap_add(j609, 1)) {
				fRec284_perm[j609] = fRec284_tmp[faust_wrap_add(vsize, j609)];
			}
			for (int j611 = 0; j611 < 4; j611 = faust_wrap_add(j611, 1)) {
				fRec283_perm[j611] = fRec283_tmp[faust_wrap_add(vsize, j611)];
			}
			for (int j613 = 0; j613 < 4; j613 = faust_wrap_add(j613, 1)) {
				fRec282_perm[j613] = fRec282_tmp[faust_wrap_add(vsize, j613)];
			}
			for (int j601 = 0; j601 < 4; j601 = faust_wrap_add(j601, 1)) {
				fRec281_perm[j601] = fRec281_tmp[faust_wrap_add(vsize, j601)];
			}
			for (int j603 = 0; j603 < 4; j603 = faust_wrap_add(j603, 1)) {
				fRec280_perm[j603] = fRec280_tmp[faust_wrap_add(vsize, j603)];
			}
			for (int j595 = 0; j595 < 4; j595 = faust_wrap_add(j595, 1)) {
				fYec35_perm[j595] = fYec35_tmp[faust_wrap_add(vsize, j595)];
			}
			for (int j591 = 0; j591 < 4; j591 = faust_wrap_add(j591, 1)) {
				fRec279_perm[j591] = fRec279_tmp[faust_wrap_add(vsize, j591)];
			}
			for (int j593 = 0; j593 < 4; j593 = faust_wrap_add(j593, 1)) {
				fRec278_perm[j593] = fRec278_tmp[faust_wrap_add(vsize, j593)];
			}
			for (int j597 = 0; j597 < 4; j597 = faust_wrap_add(j597, 1)) {
				fRec277_perm[j597] = fRec277_tmp[faust_wrap_add(vsize, j597)];
			}
			for (int j599 = 0; j599 < 4; j599 = faust_wrap_add(j599, 1)) {
				fRec276_perm[j599] = fRec276_tmp[faust_wrap_add(vsize, j599)];
			}
			for (int j583 = 0; j583 < 4; j583 = faust_wrap_add(j583, 1)) {
				fYec34_perm[j583] = fYec34_tmp[faust_wrap_add(vsize, j583)];
			}
			for (int j579 = 0; j579 < 4; j579 = faust_wrap_add(j579, 1)) {
				fRec275_perm[j579] = fRec275_tmp[faust_wrap_add(vsize, j579)];
			}
			for (int j581 = 0; j581 < 4; j581 = faust_wrap_add(j581, 1)) {
				fRec274_perm[j581] = fRec274_tmp[faust_wrap_add(vsize, j581)];
			}
			for (int j585 = 0; j585 < 4; j585 = faust_wrap_add(j585, 1)) {
				fRec273_perm[j585] = fRec273_tmp[faust_wrap_add(vsize, j585)];
			}
			for (int j587 = 0; j587 < 4; j587 = faust_wrap_add(j587, 1)) {
				fRec272_perm[j587] = fRec272_tmp[faust_wrap_add(vsize, j587)];
			}
			for (int j589 = 0; j589 < 4; j589 = faust_wrap_add(j589, 1)) {
				fRec271_perm[j589] = fRec271_tmp[faust_wrap_add(vsize, j589)];
			}
			for (int j569 = 0; j569 < 4; j569 = faust_wrap_add(j569, 1)) {
				fYec33_perm[j569] = fYec33_tmp[faust_wrap_add(vsize, j569)];
			}
			for (int j565 = 0; j565 < 4; j565 = faust_wrap_add(j565, 1)) {
				fRec270_perm[j565] = fRec270_tmp[faust_wrap_add(vsize, j565)];
			}
			for (int j567 = 0; j567 < 4; j567 = faust_wrap_add(j567, 1)) {
				fRec269_perm[j567] = fRec269_tmp[faust_wrap_add(vsize, j567)];
			}
			for (int j571 = 0; j571 < 4; j571 = faust_wrap_add(j571, 1)) {
				fRec268_perm[j571] = fRec268_tmp[faust_wrap_add(vsize, j571)];
			}
			for (int j573 = 0; j573 < 4; j573 = faust_wrap_add(j573, 1)) {
				fRec267_perm[j573] = fRec267_tmp[faust_wrap_add(vsize, j573)];
			}
			for (int j575 = 0; j575 < 4; j575 = faust_wrap_add(j575, 1)) {
				fRec266_perm[j575] = fRec266_tmp[faust_wrap_add(vsize, j575)];
			}
			for (int j577 = 0; j577 < 4; j577 = faust_wrap_add(j577, 1)) {
				fRec265_perm[j577] = fRec265_tmp[faust_wrap_add(vsize, j577)];
			}
			for (int j555 = 0; j555 < 4; j555 = faust_wrap_add(j555, 1)) {
				fRec264_perm[j555] = fRec264_tmp[faust_wrap_add(vsize, j555)];
			}
			for (int j557 = 0; j557 < 4; j557 = faust_wrap_add(j557, 1)) {
				fRec263_perm[j557] = fRec263_tmp[faust_wrap_add(vsize, j557)];
			}
			for (int j559 = 0; j559 < 4; j559 = faust_wrap_add(j559, 1)) {
				fRec262_perm[j559] = fRec262_tmp[faust_wrap_add(vsize, j559)];
			}
			for (int j561 = 0; j561 < 4; j561 = faust_wrap_add(j561, 1)) {
				fRec261_perm[j561] = fRec261_tmp[faust_wrap_add(vsize, j561)];
			}
			for (int j563 = 0; j563 < 4; j563 = faust_wrap_add(j563, 1)) {
				fRec260_perm[j563] = fRec260_tmp[faust_wrap_add(vsize, j563)];
			}
			for (int j551 = 0; j551 < 4; j551 = faust_wrap_add(j551, 1)) {
				fRec259_perm[j551] = fRec259_tmp[faust_wrap_add(vsize, j551)];
			}
			for (int j553 = 0; j553 < 4; j553 = faust_wrap_add(j553, 1)) {
				fRec258_perm[j553] = fRec258_tmp[faust_wrap_add(vsize, j553)];
			}
			for (int j545 = 0; j545 < 4; j545 = faust_wrap_add(j545, 1)) {
				fYec32_perm[j545] = fYec32_tmp[faust_wrap_add(vsize, j545)];
			}
			for (int j541 = 0; j541 < 4; j541 = faust_wrap_add(j541, 1)) {
				fRec257_perm[j541] = fRec257_tmp[faust_wrap_add(vsize, j541)];
			}
			for (int j543 = 0; j543 < 4; j543 = faust_wrap_add(j543, 1)) {
				fRec256_perm[j543] = fRec256_tmp[faust_wrap_add(vsize, j543)];
			}
			for (int j547 = 0; j547 < 4; j547 = faust_wrap_add(j547, 1)) {
				fRec255_perm[j547] = fRec255_tmp[faust_wrap_add(vsize, j547)];
			}
			for (int j549 = 0; j549 < 4; j549 = faust_wrap_add(j549, 1)) {
				fRec254_perm[j549] = fRec254_tmp[faust_wrap_add(vsize, j549)];
			}
			for (int j533 = 0; j533 < 4; j533 = faust_wrap_add(j533, 1)) {
				fYec31_perm[j533] = fYec31_tmp[faust_wrap_add(vsize, j533)];
			}
			for (int j529 = 0; j529 < 4; j529 = faust_wrap_add(j529, 1)) {
				fRec253_perm[j529] = fRec253_tmp[faust_wrap_add(vsize, j529)];
			}
			for (int j531 = 0; j531 < 4; j531 = faust_wrap_add(j531, 1)) {
				fRec252_perm[j531] = fRec252_tmp[faust_wrap_add(vsize, j531)];
			}
			for (int j535 = 0; j535 < 4; j535 = faust_wrap_add(j535, 1)) {
				fRec251_perm[j535] = fRec251_tmp[faust_wrap_add(vsize, j535)];
			}
			for (int j537 = 0; j537 < 4; j537 = faust_wrap_add(j537, 1)) {
				fRec250_perm[j537] = fRec250_tmp[faust_wrap_add(vsize, j537)];
			}
			for (int j539 = 0; j539 < 4; j539 = faust_wrap_add(j539, 1)) {
				fRec249_perm[j539] = fRec249_tmp[faust_wrap_add(vsize, j539)];
			}
			for (int j519 = 0; j519 < 4; j519 = faust_wrap_add(j519, 1)) {
				fYec30_perm[j519] = fYec30_tmp[faust_wrap_add(vsize, j519)];
			}
			for (int j515 = 0; j515 < 4; j515 = faust_wrap_add(j515, 1)) {
				fRec248_perm[j515] = fRec248_tmp[faust_wrap_add(vsize, j515)];
			}
			for (int j517 = 0; j517 < 4; j517 = faust_wrap_add(j517, 1)) {
				fRec247_perm[j517] = fRec247_tmp[faust_wrap_add(vsize, j517)];
			}
			for (int j521 = 0; j521 < 4; j521 = faust_wrap_add(j521, 1)) {
				fRec246_perm[j521] = fRec246_tmp[faust_wrap_add(vsize, j521)];
			}
			for (int j523 = 0; j523 < 4; j523 = faust_wrap_add(j523, 1)) {
				fRec245_perm[j523] = fRec245_tmp[faust_wrap_add(vsize, j523)];
			}
			for (int j525 = 0; j525 < 4; j525 = faust_wrap_add(j525, 1)) {
				fRec244_perm[j525] = fRec244_tmp[faust_wrap_add(vsize, j525)];
			}
			for (int j527 = 0; j527 < 4; j527 = faust_wrap_add(j527, 1)) {
				fRec243_perm[j527] = fRec243_tmp[faust_wrap_add(vsize, j527)];
			}
			for (int j505 = 0; j505 < 4; j505 = faust_wrap_add(j505, 1)) {
				fRec242_perm[j505] = fRec242_tmp[faust_wrap_add(vsize, j505)];
			}
			for (int j507 = 0; j507 < 4; j507 = faust_wrap_add(j507, 1)) {
				fRec241_perm[j507] = fRec241_tmp[faust_wrap_add(vsize, j507)];
			}
			for (int j509 = 0; j509 < 4; j509 = faust_wrap_add(j509, 1)) {
				fRec240_perm[j509] = fRec240_tmp[faust_wrap_add(vsize, j509)];
			}
			for (int j511 = 0; j511 < 4; j511 = faust_wrap_add(j511, 1)) {
				fRec239_perm[j511] = fRec239_tmp[faust_wrap_add(vsize, j511)];
			}
			for (int j513 = 0; j513 < 4; j513 = faust_wrap_add(j513, 1)) {
				fRec238_perm[j513] = fRec238_tmp[faust_wrap_add(vsize, j513)];
			}
			for (int j501 = 0; j501 < 4; j501 = faust_wrap_add(j501, 1)) {
				fRec237_perm[j501] = fRec237_tmp[faust_wrap_add(vsize, j501)];
			}
			for (int j503 = 0; j503 < 4; j503 = faust_wrap_add(j503, 1)) {
				fRec236_perm[j503] = fRec236_tmp[faust_wrap_add(vsize, j503)];
			}
			for (int j495 = 0; j495 < 4; j495 = faust_wrap_add(j495, 1)) {
				fYec29_perm[j495] = fYec29_tmp[faust_wrap_add(vsize, j495)];
			}
			for (int j491 = 0; j491 < 4; j491 = faust_wrap_add(j491, 1)) {
				fRec235_perm[j491] = fRec235_tmp[faust_wrap_add(vsize, j491)];
			}
			for (int j493 = 0; j493 < 4; j493 = faust_wrap_add(j493, 1)) {
				fRec234_perm[j493] = fRec234_tmp[faust_wrap_add(vsize, j493)];
			}
			for (int j497 = 0; j497 < 4; j497 = faust_wrap_add(j497, 1)) {
				fRec233_perm[j497] = fRec233_tmp[faust_wrap_add(vsize, j497)];
			}
			for (int j499 = 0; j499 < 4; j499 = faust_wrap_add(j499, 1)) {
				fRec232_perm[j499] = fRec232_tmp[faust_wrap_add(vsize, j499)];
			}
			for (int j483 = 0; j483 < 4; j483 = faust_wrap_add(j483, 1)) {
				fYec28_perm[j483] = fYec28_tmp[faust_wrap_add(vsize, j483)];
			}
			for (int j479 = 0; j479 < 4; j479 = faust_wrap_add(j479, 1)) {
				fRec231_perm[j479] = fRec231_tmp[faust_wrap_add(vsize, j479)];
			}
			for (int j481 = 0; j481 < 4; j481 = faust_wrap_add(j481, 1)) {
				fRec230_perm[j481] = fRec230_tmp[faust_wrap_add(vsize, j481)];
			}
			for (int j485 = 0; j485 < 4; j485 = faust_wrap_add(j485, 1)) {
				fRec229_perm[j485] = fRec229_tmp[faust_wrap_add(vsize, j485)];
			}
			for (int j487 = 0; j487 < 4; j487 = faust_wrap_add(j487, 1)) {
				fRec228_perm[j487] = fRec228_tmp[faust_wrap_add(vsize, j487)];
			}
			for (int j489 = 0; j489 < 4; j489 = faust_wrap_add(j489, 1)) {
				fRec227_perm[j489] = fRec227_tmp[faust_wrap_add(vsize, j489)];
			}
			for (int j469 = 0; j469 < 4; j469 = faust_wrap_add(j469, 1)) {
				fYec27_perm[j469] = fYec27_tmp[faust_wrap_add(vsize, j469)];
			}
			for (int j465 = 0; j465 < 4; j465 = faust_wrap_add(j465, 1)) {
				fRec226_perm[j465] = fRec226_tmp[faust_wrap_add(vsize, j465)];
			}
			for (int j467 = 0; j467 < 4; j467 = faust_wrap_add(j467, 1)) {
				fRec225_perm[j467] = fRec225_tmp[faust_wrap_add(vsize, j467)];
			}
			for (int j471 = 0; j471 < 4; j471 = faust_wrap_add(j471, 1)) {
				fRec224_perm[j471] = fRec224_tmp[faust_wrap_add(vsize, j471)];
			}
			for (int j473 = 0; j473 < 4; j473 = faust_wrap_add(j473, 1)) {
				fRec223_perm[j473] = fRec223_tmp[faust_wrap_add(vsize, j473)];
			}
			for (int j475 = 0; j475 < 4; j475 = faust_wrap_add(j475, 1)) {
				fRec222_perm[j475] = fRec222_tmp[faust_wrap_add(vsize, j475)];
			}
			for (int j477 = 0; j477 < 4; j477 = faust_wrap_add(j477, 1)) {
				fRec221_perm[j477] = fRec221_tmp[faust_wrap_add(vsize, j477)];
			}
			for (int j455 = 0; j455 < 4; j455 = faust_wrap_add(j455, 1)) {
				fRec220_perm[j455] = fRec220_tmp[faust_wrap_add(vsize, j455)];
			}
			for (int j457 = 0; j457 < 4; j457 = faust_wrap_add(j457, 1)) {
				fRec219_perm[j457] = fRec219_tmp[faust_wrap_add(vsize, j457)];
			}
			for (int j459 = 0; j459 < 4; j459 = faust_wrap_add(j459, 1)) {
				fRec218_perm[j459] = fRec218_tmp[faust_wrap_add(vsize, j459)];
			}
			for (int j461 = 0; j461 < 4; j461 = faust_wrap_add(j461, 1)) {
				fRec217_perm[j461] = fRec217_tmp[faust_wrap_add(vsize, j461)];
			}
			for (int j463 = 0; j463 < 4; j463 = faust_wrap_add(j463, 1)) {
				fRec216_perm[j463] = fRec216_tmp[faust_wrap_add(vsize, j463)];
			}
			for (int j451 = 0; j451 < 4; j451 = faust_wrap_add(j451, 1)) {
				fRec215_perm[j451] = fRec215_tmp[faust_wrap_add(vsize, j451)];
			}
			for (int j453 = 0; j453 < 4; j453 = faust_wrap_add(j453, 1)) {
				fRec214_perm[j453] = fRec214_tmp[faust_wrap_add(vsize, j453)];
			}
			for (int j445 = 0; j445 < 4; j445 = faust_wrap_add(j445, 1)) {
				fYec26_perm[j445] = fYec26_tmp[faust_wrap_add(vsize, j445)];
			}
			for (int j441 = 0; j441 < 4; j441 = faust_wrap_add(j441, 1)) {
				fRec213_perm[j441] = fRec213_tmp[faust_wrap_add(vsize, j441)];
			}
			for (int j443 = 0; j443 < 4; j443 = faust_wrap_add(j443, 1)) {
				fRec212_perm[j443] = fRec212_tmp[faust_wrap_add(vsize, j443)];
			}
			for (int j447 = 0; j447 < 4; j447 = faust_wrap_add(j447, 1)) {
				fRec211_perm[j447] = fRec211_tmp[faust_wrap_add(vsize, j447)];
			}
			for (int j449 = 0; j449 < 4; j449 = faust_wrap_add(j449, 1)) {
				fRec210_perm[j449] = fRec210_tmp[faust_wrap_add(vsize, j449)];
			}
			for (int j433 = 0; j433 < 4; j433 = faust_wrap_add(j433, 1)) {
				fYec25_perm[j433] = fYec25_tmp[faust_wrap_add(vsize, j433)];
			}
			for (int j429 = 0; j429 < 4; j429 = faust_wrap_add(j429, 1)) {
				fRec209_perm[j429] = fRec209_tmp[faust_wrap_add(vsize, j429)];
			}
			for (int j431 = 0; j431 < 4; j431 = faust_wrap_add(j431, 1)) {
				fRec208_perm[j431] = fRec208_tmp[faust_wrap_add(vsize, j431)];
			}
			for (int j435 = 0; j435 < 4; j435 = faust_wrap_add(j435, 1)) {
				fRec207_perm[j435] = fRec207_tmp[faust_wrap_add(vsize, j435)];
			}
			for (int j437 = 0; j437 < 4; j437 = faust_wrap_add(j437, 1)) {
				fRec206_perm[j437] = fRec206_tmp[faust_wrap_add(vsize, j437)];
			}
			for (int j439 = 0; j439 < 4; j439 = faust_wrap_add(j439, 1)) {
				fRec205_perm[j439] = fRec205_tmp[faust_wrap_add(vsize, j439)];
			}
			for (int j419 = 0; j419 < 4; j419 = faust_wrap_add(j419, 1)) {
				fYec24_perm[j419] = fYec24_tmp[faust_wrap_add(vsize, j419)];
			}
			for (int j415 = 0; j415 < 4; j415 = faust_wrap_add(j415, 1)) {
				fRec204_perm[j415] = fRec204_tmp[faust_wrap_add(vsize, j415)];
			}
			for (int j417 = 0; j417 < 4; j417 = faust_wrap_add(j417, 1)) {
				fRec203_perm[j417] = fRec203_tmp[faust_wrap_add(vsize, j417)];
			}
			for (int j421 = 0; j421 < 4; j421 = faust_wrap_add(j421, 1)) {
				fRec202_perm[j421] = fRec202_tmp[faust_wrap_add(vsize, j421)];
			}
			for (int j423 = 0; j423 < 4; j423 = faust_wrap_add(j423, 1)) {
				fRec201_perm[j423] = fRec201_tmp[faust_wrap_add(vsize, j423)];
			}
			for (int j425 = 0; j425 < 4; j425 = faust_wrap_add(j425, 1)) {
				fRec200_perm[j425] = fRec200_tmp[faust_wrap_add(vsize, j425)];
			}
			for (int j427 = 0; j427 < 4; j427 = faust_wrap_add(j427, 1)) {
				fRec199_perm[j427] = fRec199_tmp[faust_wrap_add(vsize, j427)];
			}
			for (int j405 = 0; j405 < 4; j405 = faust_wrap_add(j405, 1)) {
				fRec198_perm[j405] = fRec198_tmp[faust_wrap_add(vsize, j405)];
			}
			for (int j407 = 0; j407 < 4; j407 = faust_wrap_add(j407, 1)) {
				fRec197_perm[j407] = fRec197_tmp[faust_wrap_add(vsize, j407)];
			}
			for (int j409 = 0; j409 < 4; j409 = faust_wrap_add(j409, 1)) {
				fRec196_perm[j409] = fRec196_tmp[faust_wrap_add(vsize, j409)];
			}
			for (int j411 = 0; j411 < 4; j411 = faust_wrap_add(j411, 1)) {
				fRec195_perm[j411] = fRec195_tmp[faust_wrap_add(vsize, j411)];
			}
			for (int j413 = 0; j413 < 4; j413 = faust_wrap_add(j413, 1)) {
				fRec194_perm[j413] = fRec194_tmp[faust_wrap_add(vsize, j413)];
			}
			for (int j401 = 0; j401 < 4; j401 = faust_wrap_add(j401, 1)) {
				fRec193_perm[j401] = fRec193_tmp[faust_wrap_add(vsize, j401)];
			}
			for (int j403 = 0; j403 < 4; j403 = faust_wrap_add(j403, 1)) {
				fRec192_perm[j403] = fRec192_tmp[faust_wrap_add(vsize, j403)];
			}
			for (int j395 = 0; j395 < 4; j395 = faust_wrap_add(j395, 1)) {
				fYec23_perm[j395] = fYec23_tmp[faust_wrap_add(vsize, j395)];
			}
			for (int j391 = 0; j391 < 4; j391 = faust_wrap_add(j391, 1)) {
				fRec191_perm[j391] = fRec191_tmp[faust_wrap_add(vsize, j391)];
			}
			for (int j393 = 0; j393 < 4; j393 = faust_wrap_add(j393, 1)) {
				fRec190_perm[j393] = fRec190_tmp[faust_wrap_add(vsize, j393)];
			}
			for (int j397 = 0; j397 < 4; j397 = faust_wrap_add(j397, 1)) {
				fRec189_perm[j397] = fRec189_tmp[faust_wrap_add(vsize, j397)];
			}
			for (int j399 = 0; j399 < 4; j399 = faust_wrap_add(j399, 1)) {
				fRec188_perm[j399] = fRec188_tmp[faust_wrap_add(vsize, j399)];
			}
			for (int j383 = 0; j383 < 4; j383 = faust_wrap_add(j383, 1)) {
				fYec22_perm[j383] = fYec22_tmp[faust_wrap_add(vsize, j383)];
			}
			for (int j379 = 0; j379 < 4; j379 = faust_wrap_add(j379, 1)) {
				fRec187_perm[j379] = fRec187_tmp[faust_wrap_add(vsize, j379)];
			}
			for (int j381 = 0; j381 < 4; j381 = faust_wrap_add(j381, 1)) {
				fRec186_perm[j381] = fRec186_tmp[faust_wrap_add(vsize, j381)];
			}
			for (int j385 = 0; j385 < 4; j385 = faust_wrap_add(j385, 1)) {
				fRec185_perm[j385] = fRec185_tmp[faust_wrap_add(vsize, j385)];
			}
			for (int j387 = 0; j387 < 4; j387 = faust_wrap_add(j387, 1)) {
				fRec184_perm[j387] = fRec184_tmp[faust_wrap_add(vsize, j387)];
			}
			for (int j389 = 0; j389 < 4; j389 = faust_wrap_add(j389, 1)) {
				fRec183_perm[j389] = fRec183_tmp[faust_wrap_add(vsize, j389)];
			}
			for (int j369 = 0; j369 < 4; j369 = faust_wrap_add(j369, 1)) {
				fYec21_perm[j369] = fYec21_tmp[faust_wrap_add(vsize, j369)];
			}
			for (int j365 = 0; j365 < 4; j365 = faust_wrap_add(j365, 1)) {
				fRec182_perm[j365] = fRec182_tmp[faust_wrap_add(vsize, j365)];
			}
			for (int j367 = 0; j367 < 4; j367 = faust_wrap_add(j367, 1)) {
				fRec181_perm[j367] = fRec181_tmp[faust_wrap_add(vsize, j367)];
			}
			for (int j371 = 0; j371 < 4; j371 = faust_wrap_add(j371, 1)) {
				fRec180_perm[j371] = fRec180_tmp[faust_wrap_add(vsize, j371)];
			}
			for (int j373 = 0; j373 < 4; j373 = faust_wrap_add(j373, 1)) {
				fRec179_perm[j373] = fRec179_tmp[faust_wrap_add(vsize, j373)];
			}
			for (int j375 = 0; j375 < 4; j375 = faust_wrap_add(j375, 1)) {
				fRec178_perm[j375] = fRec178_tmp[faust_wrap_add(vsize, j375)];
			}
			for (int j377 = 0; j377 < 4; j377 = faust_wrap_add(j377, 1)) {
				fRec177_perm[j377] = fRec177_tmp[faust_wrap_add(vsize, j377)];
			}
			for (int j355 = 0; j355 < 4; j355 = faust_wrap_add(j355, 1)) {
				fRec176_perm[j355] = fRec176_tmp[faust_wrap_add(vsize, j355)];
			}
			for (int j357 = 0; j357 < 4; j357 = faust_wrap_add(j357, 1)) {
				fRec175_perm[j357] = fRec175_tmp[faust_wrap_add(vsize, j357)];
			}
			for (int j359 = 0; j359 < 4; j359 = faust_wrap_add(j359, 1)) {
				fRec174_perm[j359] = fRec174_tmp[faust_wrap_add(vsize, j359)];
			}
			for (int j361 = 0; j361 < 4; j361 = faust_wrap_add(j361, 1)) {
				fRec173_perm[j361] = fRec173_tmp[faust_wrap_add(vsize, j361)];
			}
			for (int j363 = 0; j363 < 4; j363 = faust_wrap_add(j363, 1)) {
				fRec172_perm[j363] = fRec172_tmp[faust_wrap_add(vsize, j363)];
			}
			for (int j351 = 0; j351 < 4; j351 = faust_wrap_add(j351, 1)) {
				fRec171_perm[j351] = fRec171_tmp[faust_wrap_add(vsize, j351)];
			}
			for (int j353 = 0; j353 < 4; j353 = faust_wrap_add(j353, 1)) {
				fRec170_perm[j353] = fRec170_tmp[faust_wrap_add(vsize, j353)];
			}
			for (int j345 = 0; j345 < 4; j345 = faust_wrap_add(j345, 1)) {
				fYec20_perm[j345] = fYec20_tmp[faust_wrap_add(vsize, j345)];
			}
			for (int j341 = 0; j341 < 4; j341 = faust_wrap_add(j341, 1)) {
				fRec169_perm[j341] = fRec169_tmp[faust_wrap_add(vsize, j341)];
			}
			for (int j343 = 0; j343 < 4; j343 = faust_wrap_add(j343, 1)) {
				fRec168_perm[j343] = fRec168_tmp[faust_wrap_add(vsize, j343)];
			}
			for (int j347 = 0; j347 < 4; j347 = faust_wrap_add(j347, 1)) {
				fRec167_perm[j347] = fRec167_tmp[faust_wrap_add(vsize, j347)];
			}
			for (int j349 = 0; j349 < 4; j349 = faust_wrap_add(j349, 1)) {
				fRec166_perm[j349] = fRec166_tmp[faust_wrap_add(vsize, j349)];
			}
			for (int j333 = 0; j333 < 4; j333 = faust_wrap_add(j333, 1)) {
				fYec19_perm[j333] = fYec19_tmp[faust_wrap_add(vsize, j333)];
			}
			for (int j329 = 0; j329 < 4; j329 = faust_wrap_add(j329, 1)) {
				fRec165_perm[j329] = fRec165_tmp[faust_wrap_add(vsize, j329)];
			}
			for (int j331 = 0; j331 < 4; j331 = faust_wrap_add(j331, 1)) {
				fRec164_perm[j331] = fRec164_tmp[faust_wrap_add(vsize, j331)];
			}
			for (int j335 = 0; j335 < 4; j335 = faust_wrap_add(j335, 1)) {
				fRec163_perm[j335] = fRec163_tmp[faust_wrap_add(vsize, j335)];
			}
			for (int j337 = 0; j337 < 4; j337 = faust_wrap_add(j337, 1)) {
				fRec162_perm[j337] = fRec162_tmp[faust_wrap_add(vsize, j337)];
			}
			for (int j339 = 0; j339 < 4; j339 = faust_wrap_add(j339, 1)) {
				fRec161_perm[j339] = fRec161_tmp[faust_wrap_add(vsize, j339)];
			}
			for (int j319 = 0; j319 < 4; j319 = faust_wrap_add(j319, 1)) {
				fYec18_perm[j319] = fYec18_tmp[faust_wrap_add(vsize, j319)];
			}
			for (int j315 = 0; j315 < 4; j315 = faust_wrap_add(j315, 1)) {
				fRec160_perm[j315] = fRec160_tmp[faust_wrap_add(vsize, j315)];
			}
			for (int j317 = 0; j317 < 4; j317 = faust_wrap_add(j317, 1)) {
				fRec159_perm[j317] = fRec159_tmp[faust_wrap_add(vsize, j317)];
			}
			for (int j321 = 0; j321 < 4; j321 = faust_wrap_add(j321, 1)) {
				fRec158_perm[j321] = fRec158_tmp[faust_wrap_add(vsize, j321)];
			}
			for (int j323 = 0; j323 < 4; j323 = faust_wrap_add(j323, 1)) {
				fRec157_perm[j323] = fRec157_tmp[faust_wrap_add(vsize, j323)];
			}
			for (int j325 = 0; j325 < 4; j325 = faust_wrap_add(j325, 1)) {
				fRec156_perm[j325] = fRec156_tmp[faust_wrap_add(vsize, j325)];
			}
			for (int j327 = 0; j327 < 4; j327 = faust_wrap_add(j327, 1)) {
				fRec155_perm[j327] = fRec155_tmp[faust_wrap_add(vsize, j327)];
			}
			for (int j305 = 0; j305 < 4; j305 = faust_wrap_add(j305, 1)) {
				fRec154_perm[j305] = fRec154_tmp[faust_wrap_add(vsize, j305)];
			}
			for (int j307 = 0; j307 < 4; j307 = faust_wrap_add(j307, 1)) {
				fRec153_perm[j307] = fRec153_tmp[faust_wrap_add(vsize, j307)];
			}
			for (int j309 = 0; j309 < 4; j309 = faust_wrap_add(j309, 1)) {
				fRec152_perm[j309] = fRec152_tmp[faust_wrap_add(vsize, j309)];
			}
			for (int j311 = 0; j311 < 4; j311 = faust_wrap_add(j311, 1)) {
				fRec151_perm[j311] = fRec151_tmp[faust_wrap_add(vsize, j311)];
			}
			for (int j313 = 0; j313 < 4; j313 = faust_wrap_add(j313, 1)) {
				fRec150_perm[j313] = fRec150_tmp[faust_wrap_add(vsize, j313)];
			}
			for (int j301 = 0; j301 < 4; j301 = faust_wrap_add(j301, 1)) {
				fRec149_perm[j301] = fRec149_tmp[faust_wrap_add(vsize, j301)];
			}
			for (int j303 = 0; j303 < 4; j303 = faust_wrap_add(j303, 1)) {
				fRec148_perm[j303] = fRec148_tmp[faust_wrap_add(vsize, j303)];
			}
			for (int j295 = 0; j295 < 4; j295 = faust_wrap_add(j295, 1)) {
				fYec17_perm[j295] = fYec17_tmp[faust_wrap_add(vsize, j295)];
			}
			for (int j291 = 0; j291 < 4; j291 = faust_wrap_add(j291, 1)) {
				fRec147_perm[j291] = fRec147_tmp[faust_wrap_add(vsize, j291)];
			}
			for (int j293 = 0; j293 < 4; j293 = faust_wrap_add(j293, 1)) {
				fRec146_perm[j293] = fRec146_tmp[faust_wrap_add(vsize, j293)];
			}
			for (int j297 = 0; j297 < 4; j297 = faust_wrap_add(j297, 1)) {
				fRec145_perm[j297] = fRec145_tmp[faust_wrap_add(vsize, j297)];
			}
			for (int j299 = 0; j299 < 4; j299 = faust_wrap_add(j299, 1)) {
				fRec144_perm[j299] = fRec144_tmp[faust_wrap_add(vsize, j299)];
			}
			for (int j283 = 0; j283 < 4; j283 = faust_wrap_add(j283, 1)) {
				fYec16_perm[j283] = fYec16_tmp[faust_wrap_add(vsize, j283)];
			}
			for (int j279 = 0; j279 < 4; j279 = faust_wrap_add(j279, 1)) {
				fRec143_perm[j279] = fRec143_tmp[faust_wrap_add(vsize, j279)];
			}
			for (int j281 = 0; j281 < 4; j281 = faust_wrap_add(j281, 1)) {
				fRec142_perm[j281] = fRec142_tmp[faust_wrap_add(vsize, j281)];
			}
			for (int j285 = 0; j285 < 4; j285 = faust_wrap_add(j285, 1)) {
				fRec141_perm[j285] = fRec141_tmp[faust_wrap_add(vsize, j285)];
			}
			for (int j287 = 0; j287 < 4; j287 = faust_wrap_add(j287, 1)) {
				fRec140_perm[j287] = fRec140_tmp[faust_wrap_add(vsize, j287)];
			}
			for (int j289 = 0; j289 < 4; j289 = faust_wrap_add(j289, 1)) {
				fRec139_perm[j289] = fRec139_tmp[faust_wrap_add(vsize, j289)];
			}
			for (int j269 = 0; j269 < 4; j269 = faust_wrap_add(j269, 1)) {
				fYec15_perm[j269] = fYec15_tmp[faust_wrap_add(vsize, j269)];
			}
			for (int j265 = 0; j265 < 4; j265 = faust_wrap_add(j265, 1)) {
				fRec138_perm[j265] = fRec138_tmp[faust_wrap_add(vsize, j265)];
			}
			for (int j267 = 0; j267 < 4; j267 = faust_wrap_add(j267, 1)) {
				fRec137_perm[j267] = fRec137_tmp[faust_wrap_add(vsize, j267)];
			}
			for (int j271 = 0; j271 < 4; j271 = faust_wrap_add(j271, 1)) {
				fRec136_perm[j271] = fRec136_tmp[faust_wrap_add(vsize, j271)];
			}
			for (int j273 = 0; j273 < 4; j273 = faust_wrap_add(j273, 1)) {
				fRec135_perm[j273] = fRec135_tmp[faust_wrap_add(vsize, j273)];
			}
			for (int j275 = 0; j275 < 4; j275 = faust_wrap_add(j275, 1)) {
				fRec134_perm[j275] = fRec134_tmp[faust_wrap_add(vsize, j275)];
			}
			for (int j277 = 0; j277 < 4; j277 = faust_wrap_add(j277, 1)) {
				fRec133_perm[j277] = fRec133_tmp[faust_wrap_add(vsize, j277)];
			}
			for (int j255 = 0; j255 < 4; j255 = faust_wrap_add(j255, 1)) {
				fRec132_perm[j255] = fRec132_tmp[faust_wrap_add(vsize, j255)];
			}
			for (int j257 = 0; j257 < 4; j257 = faust_wrap_add(j257, 1)) {
				fRec131_perm[j257] = fRec131_tmp[faust_wrap_add(vsize, j257)];
			}
			for (int j259 = 0; j259 < 4; j259 = faust_wrap_add(j259, 1)) {
				fRec130_perm[j259] = fRec130_tmp[faust_wrap_add(vsize, j259)];
			}
			for (int j261 = 0; j261 < 4; j261 = faust_wrap_add(j261, 1)) {
				fRec129_perm[j261] = fRec129_tmp[faust_wrap_add(vsize, j261)];
			}
			for (int j263 = 0; j263 < 4; j263 = faust_wrap_add(j263, 1)) {
				fRec128_perm[j263] = fRec128_tmp[faust_wrap_add(vsize, j263)];
			}
			for (int j251 = 0; j251 < 4; j251 = faust_wrap_add(j251, 1)) {
				fRec127_perm[j251] = fRec127_tmp[faust_wrap_add(vsize, j251)];
			}
			for (int j253 = 0; j253 < 4; j253 = faust_wrap_add(j253, 1)) {
				fRec126_perm[j253] = fRec126_tmp[faust_wrap_add(vsize, j253)];
			}
			for (int j245 = 0; j245 < 4; j245 = faust_wrap_add(j245, 1)) {
				fYec14_perm[j245] = fYec14_tmp[faust_wrap_add(vsize, j245)];
			}
			for (int j241 = 0; j241 < 4; j241 = faust_wrap_add(j241, 1)) {
				fRec125_perm[j241] = fRec125_tmp[faust_wrap_add(vsize, j241)];
			}
			for (int j243 = 0; j243 < 4; j243 = faust_wrap_add(j243, 1)) {
				fRec124_perm[j243] = fRec124_tmp[faust_wrap_add(vsize, j243)];
			}
			for (int j247 = 0; j247 < 4; j247 = faust_wrap_add(j247, 1)) {
				fRec123_perm[j247] = fRec123_tmp[faust_wrap_add(vsize, j247)];
			}
			for (int j249 = 0; j249 < 4; j249 = faust_wrap_add(j249, 1)) {
				fRec122_perm[j249] = fRec122_tmp[faust_wrap_add(vsize, j249)];
			}
			for (int j233 = 0; j233 < 4; j233 = faust_wrap_add(j233, 1)) {
				fYec13_perm[j233] = fYec13_tmp[faust_wrap_add(vsize, j233)];
			}
			for (int j229 = 0; j229 < 4; j229 = faust_wrap_add(j229, 1)) {
				fRec121_perm[j229] = fRec121_tmp[faust_wrap_add(vsize, j229)];
			}
			for (int j231 = 0; j231 < 4; j231 = faust_wrap_add(j231, 1)) {
				fRec120_perm[j231] = fRec120_tmp[faust_wrap_add(vsize, j231)];
			}
			for (int j235 = 0; j235 < 4; j235 = faust_wrap_add(j235, 1)) {
				fRec119_perm[j235] = fRec119_tmp[faust_wrap_add(vsize, j235)];
			}
			for (int j237 = 0; j237 < 4; j237 = faust_wrap_add(j237, 1)) {
				fRec118_perm[j237] = fRec118_tmp[faust_wrap_add(vsize, j237)];
			}
			for (int j239 = 0; j239 < 4; j239 = faust_wrap_add(j239, 1)) {
				fRec117_perm[j239] = fRec117_tmp[faust_wrap_add(vsize, j239)];
			}
			for (int j219 = 0; j219 < 4; j219 = faust_wrap_add(j219, 1)) {
				fYec12_perm[j219] = fYec12_tmp[faust_wrap_add(vsize, j219)];
			}
			for (int j215 = 0; j215 < 4; j215 = faust_wrap_add(j215, 1)) {
				fRec116_perm[j215] = fRec116_tmp[faust_wrap_add(vsize, j215)];
			}
			for (int j217 = 0; j217 < 4; j217 = faust_wrap_add(j217, 1)) {
				fRec115_perm[j217] = fRec115_tmp[faust_wrap_add(vsize, j217)];
			}
			for (int j221 = 0; j221 < 4; j221 = faust_wrap_add(j221, 1)) {
				fRec114_perm[j221] = fRec114_tmp[faust_wrap_add(vsize, j221)];
			}
			for (int j223 = 0; j223 < 4; j223 = faust_wrap_add(j223, 1)) {
				fRec113_perm[j223] = fRec113_tmp[faust_wrap_add(vsize, j223)];
			}
			for (int j225 = 0; j225 < 4; j225 = faust_wrap_add(j225, 1)) {
				fRec112_perm[j225] = fRec112_tmp[faust_wrap_add(vsize, j225)];
			}
			for (int j227 = 0; j227 < 4; j227 = faust_wrap_add(j227, 1)) {
				fRec111_perm[j227] = fRec111_tmp[faust_wrap_add(vsize, j227)];
			}
			for (int j205 = 0; j205 < 4; j205 = faust_wrap_add(j205, 1)) {
				fRec110_perm[j205] = fRec110_tmp[faust_wrap_add(vsize, j205)];
			}
			for (int j207 = 0; j207 < 4; j207 = faust_wrap_add(j207, 1)) {
				fRec109_perm[j207] = fRec109_tmp[faust_wrap_add(vsize, j207)];
			}
			for (int j209 = 0; j209 < 4; j209 = faust_wrap_add(j209, 1)) {
				fRec108_perm[j209] = fRec108_tmp[faust_wrap_add(vsize, j209)];
			}
			for (int j211 = 0; j211 < 4; j211 = faust_wrap_add(j211, 1)) {
				fRec107_perm[j211] = fRec107_tmp[faust_wrap_add(vsize, j211)];
			}
			for (int j213 = 0; j213 < 4; j213 = faust_wrap_add(j213, 1)) {
				fRec106_perm[j213] = fRec106_tmp[faust_wrap_add(vsize, j213)];
			}
			for (int j201 = 0; j201 < 4; j201 = faust_wrap_add(j201, 1)) {
				fRec105_perm[j201] = fRec105_tmp[faust_wrap_add(vsize, j201)];
			}
			for (int j203 = 0; j203 < 4; j203 = faust_wrap_add(j203, 1)) {
				fRec104_perm[j203] = fRec104_tmp[faust_wrap_add(vsize, j203)];
			}
			for (int j195 = 0; j195 < 4; j195 = faust_wrap_add(j195, 1)) {
				fYec11_perm[j195] = fYec11_tmp[faust_wrap_add(vsize, j195)];
			}
			for (int j191 = 0; j191 < 4; j191 = faust_wrap_add(j191, 1)) {
				fRec103_perm[j191] = fRec103_tmp[faust_wrap_add(vsize, j191)];
			}
			for (int j193 = 0; j193 < 4; j193 = faust_wrap_add(j193, 1)) {
				fRec102_perm[j193] = fRec102_tmp[faust_wrap_add(vsize, j193)];
			}
			for (int j197 = 0; j197 < 4; j197 = faust_wrap_add(j197, 1)) {
				fRec101_perm[j197] = fRec101_tmp[faust_wrap_add(vsize, j197)];
			}
			for (int j199 = 0; j199 < 4; j199 = faust_wrap_add(j199, 1)) {
				fRec100_perm[j199] = fRec100_tmp[faust_wrap_add(vsize, j199)];
			}
			for (int j183 = 0; j183 < 4; j183 = faust_wrap_add(j183, 1)) {
				fYec10_perm[j183] = fYec10_tmp[faust_wrap_add(vsize, j183)];
			}
			for (int j179 = 0; j179 < 4; j179 = faust_wrap_add(j179, 1)) {
				fRec99_perm[j179] = fRec99_tmp[faust_wrap_add(vsize, j179)];
			}
			for (int j181 = 0; j181 < 4; j181 = faust_wrap_add(j181, 1)) {
				fRec98_perm[j181] = fRec98_tmp[faust_wrap_add(vsize, j181)];
			}
			for (int j185 = 0; j185 < 4; j185 = faust_wrap_add(j185, 1)) {
				fRec97_perm[j185] = fRec97_tmp[faust_wrap_add(vsize, j185)];
			}
			for (int j187 = 0; j187 < 4; j187 = faust_wrap_add(j187, 1)) {
				fRec96_perm[j187] = fRec96_tmp[faust_wrap_add(vsize, j187)];
			}
			for (int j189 = 0; j189 < 4; j189 = faust_wrap_add(j189, 1)) {
				fRec95_perm[j189] = fRec95_tmp[faust_wrap_add(vsize, j189)];
			}
			for (int j169 = 0; j169 < 4; j169 = faust_wrap_add(j169, 1)) {
				fYec9_perm[j169] = fYec9_tmp[faust_wrap_add(vsize, j169)];
			}
			for (int j165 = 0; j165 < 4; j165 = faust_wrap_add(j165, 1)) {
				fRec94_perm[j165] = fRec94_tmp[faust_wrap_add(vsize, j165)];
			}
			for (int j167 = 0; j167 < 4; j167 = faust_wrap_add(j167, 1)) {
				fRec93_perm[j167] = fRec93_tmp[faust_wrap_add(vsize, j167)];
			}
			for (int j171 = 0; j171 < 4; j171 = faust_wrap_add(j171, 1)) {
				fRec92_perm[j171] = fRec92_tmp[faust_wrap_add(vsize, j171)];
			}
			for (int j173 = 0; j173 < 4; j173 = faust_wrap_add(j173, 1)) {
				fRec91_perm[j173] = fRec91_tmp[faust_wrap_add(vsize, j173)];
			}
			for (int j175 = 0; j175 < 4; j175 = faust_wrap_add(j175, 1)) {
				fRec90_perm[j175] = fRec90_tmp[faust_wrap_add(vsize, j175)];
			}
			for (int j177 = 0; j177 < 4; j177 = faust_wrap_add(j177, 1)) {
				fRec89_perm[j177] = fRec89_tmp[faust_wrap_add(vsize, j177)];
			}
			for (int j155 = 0; j155 < 4; j155 = faust_wrap_add(j155, 1)) {
				fRec88_perm[j155] = fRec88_tmp[faust_wrap_add(vsize, j155)];
			}
			for (int j157 = 0; j157 < 4; j157 = faust_wrap_add(j157, 1)) {
				fRec87_perm[j157] = fRec87_tmp[faust_wrap_add(vsize, j157)];
			}
			for (int j159 = 0; j159 < 4; j159 = faust_wrap_add(j159, 1)) {
				fRec86_perm[j159] = fRec86_tmp[faust_wrap_add(vsize, j159)];
			}
			for (int j161 = 0; j161 < 4; j161 = faust_wrap_add(j161, 1)) {
				fRec85_perm[j161] = fRec85_tmp[faust_wrap_add(vsize, j161)];
			}
			for (int j163 = 0; j163 < 4; j163 = faust_wrap_add(j163, 1)) {
				fRec84_perm[j163] = fRec84_tmp[faust_wrap_add(vsize, j163)];
			}
			for (int j151 = 0; j151 < 4; j151 = faust_wrap_add(j151, 1)) {
				fRec83_perm[j151] = fRec83_tmp[faust_wrap_add(vsize, j151)];
			}
			for (int j153 = 0; j153 < 4; j153 = faust_wrap_add(j153, 1)) {
				fRec82_perm[j153] = fRec82_tmp[faust_wrap_add(vsize, j153)];
			}
			for (int j145 = 0; j145 < 4; j145 = faust_wrap_add(j145, 1)) {
				fYec8_perm[j145] = fYec8_tmp[faust_wrap_add(vsize, j145)];
			}
			for (int j141 = 0; j141 < 4; j141 = faust_wrap_add(j141, 1)) {
				fRec81_perm[j141] = fRec81_tmp[faust_wrap_add(vsize, j141)];
			}
			for (int j143 = 0; j143 < 4; j143 = faust_wrap_add(j143, 1)) {
				fRec80_perm[j143] = fRec80_tmp[faust_wrap_add(vsize, j143)];
			}
			for (int j147 = 0; j147 < 4; j147 = faust_wrap_add(j147, 1)) {
				fRec79_perm[j147] = fRec79_tmp[faust_wrap_add(vsize, j147)];
			}
			for (int j149 = 0; j149 < 4; j149 = faust_wrap_add(j149, 1)) {
				fRec78_perm[j149] = fRec78_tmp[faust_wrap_add(vsize, j149)];
			}
			for (int j133 = 0; j133 < 4; j133 = faust_wrap_add(j133, 1)) {
				fYec7_perm[j133] = fYec7_tmp[faust_wrap_add(vsize, j133)];
			}
			for (int j129 = 0; j129 < 4; j129 = faust_wrap_add(j129, 1)) {
				fRec77_perm[j129] = fRec77_tmp[faust_wrap_add(vsize, j129)];
			}
			for (int j131 = 0; j131 < 4; j131 = faust_wrap_add(j131, 1)) {
				fRec76_perm[j131] = fRec76_tmp[faust_wrap_add(vsize, j131)];
			}
			for (int j135 = 0; j135 < 4; j135 = faust_wrap_add(j135, 1)) {
				fRec75_perm[j135] = fRec75_tmp[faust_wrap_add(vsize, j135)];
			}
			for (int j137 = 0; j137 < 4; j137 = faust_wrap_add(j137, 1)) {
				fRec74_perm[j137] = fRec74_tmp[faust_wrap_add(vsize, j137)];
			}
			for (int j139 = 0; j139 < 4; j139 = faust_wrap_add(j139, 1)) {
				fRec73_perm[j139] = fRec73_tmp[faust_wrap_add(vsize, j139)];
			}
			for (int j119 = 0; j119 < 4; j119 = faust_wrap_add(j119, 1)) {
				fYec6_perm[j119] = fYec6_tmp[faust_wrap_add(vsize, j119)];
			}
			for (int j115 = 0; j115 < 4; j115 = faust_wrap_add(j115, 1)) {
				fRec72_perm[j115] = fRec72_tmp[faust_wrap_add(vsize, j115)];
			}
			for (int j117 = 0; j117 < 4; j117 = faust_wrap_add(j117, 1)) {
				fRec71_perm[j117] = fRec71_tmp[faust_wrap_add(vsize, j117)];
			}
			for (int j121 = 0; j121 < 4; j121 = faust_wrap_add(j121, 1)) {
				fRec70_perm[j121] = fRec70_tmp[faust_wrap_add(vsize, j121)];
			}
			for (int j123 = 0; j123 < 4; j123 = faust_wrap_add(j123, 1)) {
				fRec69_perm[j123] = fRec69_tmp[faust_wrap_add(vsize, j123)];
			}
			for (int j125 = 0; j125 < 4; j125 = faust_wrap_add(j125, 1)) {
				fRec68_perm[j125] = fRec68_tmp[faust_wrap_add(vsize, j125)];
			}
			for (int j127 = 0; j127 < 4; j127 = faust_wrap_add(j127, 1)) {
				fRec67_perm[j127] = fRec67_tmp[faust_wrap_add(vsize, j127)];
			}
			for (int j105 = 0; j105 < 4; j105 = faust_wrap_add(j105, 1)) {
				fRec66_perm[j105] = fRec66_tmp[faust_wrap_add(vsize, j105)];
			}
			for (int j107 = 0; j107 < 4; j107 = faust_wrap_add(j107, 1)) {
				fRec65_perm[j107] = fRec65_tmp[faust_wrap_add(vsize, j107)];
			}
			for (int j109 = 0; j109 < 4; j109 = faust_wrap_add(j109, 1)) {
				fRec64_perm[j109] = fRec64_tmp[faust_wrap_add(vsize, j109)];
			}
			for (int j111 = 0; j111 < 4; j111 = faust_wrap_add(j111, 1)) {
				fRec63_perm[j111] = fRec63_tmp[faust_wrap_add(vsize, j111)];
			}
			for (int j113 = 0; j113 < 4; j113 = faust_wrap_add(j113, 1)) {
				fRec62_perm[j113] = fRec62_tmp[faust_wrap_add(vsize, j113)];
			}
			for (int j101 = 0; j101 < 4; j101 = faust_wrap_add(j101, 1)) {
				fRec61_perm[j101] = fRec61_tmp[faust_wrap_add(vsize, j101)];
			}
			for (int j103 = 0; j103 < 4; j103 = faust_wrap_add(j103, 1)) {
				fRec60_perm[j103] = fRec60_tmp[faust_wrap_add(vsize, j103)];
			}
			for (int j95 = 0; j95 < 4; j95 = faust_wrap_add(j95, 1)) {
				fYec5_perm[j95] = fYec5_tmp[faust_wrap_add(vsize, j95)];
			}
			for (int j91 = 0; j91 < 4; j91 = faust_wrap_add(j91, 1)) {
				fRec59_perm[j91] = fRec59_tmp[faust_wrap_add(vsize, j91)];
			}
			for (int j93 = 0; j93 < 4; j93 = faust_wrap_add(j93, 1)) {
				fRec58_perm[j93] = fRec58_tmp[faust_wrap_add(vsize, j93)];
			}
			for (int j97 = 0; j97 < 4; j97 = faust_wrap_add(j97, 1)) {
				fRec57_perm[j97] = fRec57_tmp[faust_wrap_add(vsize, j97)];
			}
			for (int j99 = 0; j99 < 4; j99 = faust_wrap_add(j99, 1)) {
				fRec56_perm[j99] = fRec56_tmp[faust_wrap_add(vsize, j99)];
			}
			for (int j83 = 0; j83 < 4; j83 = faust_wrap_add(j83, 1)) {
				fYec4_perm[j83] = fYec4_tmp[faust_wrap_add(vsize, j83)];
			}
			for (int j79 = 0; j79 < 4; j79 = faust_wrap_add(j79, 1)) {
				fRec55_perm[j79] = fRec55_tmp[faust_wrap_add(vsize, j79)];
			}
			for (int j81 = 0; j81 < 4; j81 = faust_wrap_add(j81, 1)) {
				fRec54_perm[j81] = fRec54_tmp[faust_wrap_add(vsize, j81)];
			}
			for (int j85 = 0; j85 < 4; j85 = faust_wrap_add(j85, 1)) {
				fRec53_perm[j85] = fRec53_tmp[faust_wrap_add(vsize, j85)];
			}
			for (int j87 = 0; j87 < 4; j87 = faust_wrap_add(j87, 1)) {
				fRec52_perm[j87] = fRec52_tmp[faust_wrap_add(vsize, j87)];
			}
			for (int j89 = 0; j89 < 4; j89 = faust_wrap_add(j89, 1)) {
				fRec51_perm[j89] = fRec51_tmp[faust_wrap_add(vsize, j89)];
			}
			for (int j69 = 0; j69 < 4; j69 = faust_wrap_add(j69, 1)) {
				fYec3_perm[j69] = fYec3_tmp[faust_wrap_add(vsize, j69)];
			}
			for (int j65 = 0; j65 < 4; j65 = faust_wrap_add(j65, 1)) {
				fRec50_perm[j65] = fRec50_tmp[faust_wrap_add(vsize, j65)];
			}
			for (int j67 = 0; j67 < 4; j67 = faust_wrap_add(j67, 1)) {
				fRec49_perm[j67] = fRec49_tmp[faust_wrap_add(vsize, j67)];
			}
			for (int j71 = 0; j71 < 4; j71 = faust_wrap_add(j71, 1)) {
				fRec48_perm[j71] = fRec48_tmp[faust_wrap_add(vsize, j71)];
			}
			for (int j73 = 0; j73 < 4; j73 = faust_wrap_add(j73, 1)) {
				fRec47_perm[j73] = fRec47_tmp[faust_wrap_add(vsize, j73)];
			}
			for (int j75 = 0; j75 < 4; j75 = faust_wrap_add(j75, 1)) {
				fRec46_perm[j75] = fRec46_tmp[faust_wrap_add(vsize, j75)];
			}
			for (int j77 = 0; j77 < 4; j77 = faust_wrap_add(j77, 1)) {
				fRec45_perm[j77] = fRec45_tmp[faust_wrap_add(vsize, j77)];
			}
			for (int j55 = 0; j55 < 4; j55 = faust_wrap_add(j55, 1)) {
				fRec44_perm[j55] = fRec44_tmp[faust_wrap_add(vsize, j55)];
			}
			for (int j57 = 0; j57 < 4; j57 = faust_wrap_add(j57, 1)) {
				fRec43_perm[j57] = fRec43_tmp[faust_wrap_add(vsize, j57)];
			}
			for (int j59 = 0; j59 < 4; j59 = faust_wrap_add(j59, 1)) {
				fRec42_perm[j59] = fRec42_tmp[faust_wrap_add(vsize, j59)];
			}
			for (int j61 = 0; j61 < 4; j61 = faust_wrap_add(j61, 1)) {
				fRec41_perm[j61] = fRec41_tmp[faust_wrap_add(vsize, j61)];
			}
			for (int j63 = 0; j63 < 4; j63 = faust_wrap_add(j63, 1)) {
				fRec40_perm[j63] = fRec40_tmp[faust_wrap_add(vsize, j63)];
			}
			for (int j51 = 0; j51 < 4; j51 = faust_wrap_add(j51, 1)) {
				fRec39_perm[j51] = fRec39_tmp[faust_wrap_add(vsize, j51)];
			}
			for (int j53 = 0; j53 < 4; j53 = faust_wrap_add(j53, 1)) {
				fRec38_perm[j53] = fRec38_tmp[faust_wrap_add(vsize, j53)];
			}
			for (int j45 = 0; j45 < 4; j45 = faust_wrap_add(j45, 1)) {
				fYec2_perm[j45] = fYec2_tmp[faust_wrap_add(vsize, j45)];
			}
			for (int j41 = 0; j41 < 4; j41 = faust_wrap_add(j41, 1)) {
				fRec37_perm[j41] = fRec37_tmp[faust_wrap_add(vsize, j41)];
			}
			for (int j43 = 0; j43 < 4; j43 = faust_wrap_add(j43, 1)) {
				fRec36_perm[j43] = fRec36_tmp[faust_wrap_add(vsize, j43)];
			}
			for (int j47 = 0; j47 < 4; j47 = faust_wrap_add(j47, 1)) {
				fRec35_perm[j47] = fRec35_tmp[faust_wrap_add(vsize, j47)];
			}
			for (int j49 = 0; j49 < 4; j49 = faust_wrap_add(j49, 1)) {
				fRec34_perm[j49] = fRec34_tmp[faust_wrap_add(vsize, j49)];
			}
			for (int j33 = 0; j33 < 4; j33 = faust_wrap_add(j33, 1)) {
				fYec1_perm[j33] = fYec1_tmp[faust_wrap_add(vsize, j33)];
			}
			for (int j29 = 0; j29 < 4; j29 = faust_wrap_add(j29, 1)) {
				fRec33_perm[j29] = fRec33_tmp[faust_wrap_add(vsize, j29)];
			}
			for (int j31 = 0; j31 < 4; j31 = faust_wrap_add(j31, 1)) {
				fRec32_perm[j31] = fRec32_tmp[faust_wrap_add(vsize, j31)];
			}
			for (int j35 = 0; j35 < 4; j35 = faust_wrap_add(j35, 1)) {
				fRec31_perm[j35] = fRec31_tmp[faust_wrap_add(vsize, j35)];
			}
			for (int j37 = 0; j37 < 4; j37 = faust_wrap_add(j37, 1)) {
				fRec30_perm[j37] = fRec30_tmp[faust_wrap_add(vsize, j37)];
			}
			for (int j39 = 0; j39 < 4; j39 = faust_wrap_add(j39, 1)) {
				fRec29_perm[j39] = fRec29_tmp[faust_wrap_add(vsize, j39)];
			}
			for (int j19 = 0; j19 < 4; j19 = faust_wrap_add(j19, 1)) {
				fYec0_perm[j19] = fYec0_tmp[faust_wrap_add(vsize, j19)];
			}
			for (int j15 = 0; j15 < 4; j15 = faust_wrap_add(j15, 1)) {
				fRec28_perm[j15] = fRec28_tmp[faust_wrap_add(vsize, j15)];
			}
			for (int j17 = 0; j17 < 4; j17 = faust_wrap_add(j17, 1)) {
				fRec27_perm[j17] = fRec27_tmp[faust_wrap_add(vsize, j17)];
			}
			for (int j21 = 0; j21 < 4; j21 = faust_wrap_add(j21, 1)) {
				fRec26_perm[j21] = fRec26_tmp[faust_wrap_add(vsize, j21)];
			}
			for (int j23 = 0; j23 < 4; j23 = faust_wrap_add(j23, 1)) {
				fRec25_perm[j23] = fRec25_tmp[faust_wrap_add(vsize, j23)];
			}
			for (int j25 = 0; j25 < 4; j25 = faust_wrap_add(j25, 1)) {
				fRec24_perm[j25] = fRec24_tmp[faust_wrap_add(vsize, j25)];
			}
			for (int j27 = 0; j27 < 4; j27 = faust_wrap_add(j27, 1)) {
				fRec23_perm[j27] = fRec23_tmp[faust_wrap_add(vsize, j27)];
			}
			for (int j5 = 0; j5 < 4; j5 = faust_wrap_add(j5, 1)) {
				fRec22_perm[j5] = fRec22_tmp[faust_wrap_add(vsize, j5)];
			}
			for (int j7 = 0; j7 < 4; j7 = faust_wrap_add(j7, 1)) {
				fRec21_perm[j7] = fRec21_tmp[faust_wrap_add(vsize, j7)];
			}
			for (int j9 = 0; j9 < 4; j9 = faust_wrap_add(j9, 1)) {
				fRec20_perm[j9] = fRec20_tmp[faust_wrap_add(vsize, j9)];
			}
			for (int j11 = 0; j11 < 4; j11 = faust_wrap_add(j11, 1)) {
				fRec19_perm[j11] = fRec19_tmp[faust_wrap_add(vsize, j11)];
			}
			for (int j13 = 0; j13 < 4; j13 = faust_wrap_add(j13, 1)) {
				fRec18_perm[j13] = fRec18_tmp[faust_wrap_add(vsize, j13)];
			}
			for (int j809 = 0; j809 < 4; j809 = faust_wrap_add(j809, 1)) {
				fRec0_perm[j809] = fRec0_tmp[faust_wrap_add(vsize, j809)];
			}
			for (int j813 = 0; j813 < 4; j813 = faust_wrap_add(j813, 1)) {
				fRec1_perm[j813] = fRec1_tmp[faust_wrap_add(vsize, j813)];
			}
			for (int j815 = 0; j815 < 4; j815 = faust_wrap_add(j815, 1)) {
				fRec2_perm[j815] = fRec2_tmp[faust_wrap_add(vsize, j815)];
			}
			for (int j817 = 0; j817 < 4; j817 = faust_wrap_add(j817, 1)) {
				fRec3_perm[j817] = fRec3_tmp[faust_wrap_add(vsize, j817)];
			}
			for (int j819 = 0; j819 < 4; j819 = faust_wrap_add(j819, 1)) {
				fRec4_perm[j819] = fRec4_tmp[faust_wrap_add(vsize, j819)];
			}
			for (int j821 = 0; j821 < 4; j821 = faust_wrap_add(j821, 1)) {
				fRec5_perm[j821] = fRec5_tmp[faust_wrap_add(vsize, j821)];
			}
			for (int j823 = 0; j823 < 4; j823 = faust_wrap_add(j823, 1)) {
				fRec6_perm[j823] = fRec6_tmp[faust_wrap_add(vsize, j823)];
			}
			for (int j825 = 0; j825 < 4; j825 = faust_wrap_add(j825, 1)) {
				fRec7_perm[j825] = fRec7_tmp[faust_wrap_add(vsize, j825)];
			}
			for (int j827 = 0; j827 < 4; j827 = faust_wrap_add(j827, 1)) {
				fRec8_perm[j827] = fRec8_tmp[faust_wrap_add(vsize, j827)];
			}
			for (int j829 = 0; j829 < 4; j829 = faust_wrap_add(j829, 1)) {
				fRec9_perm[j829] = fRec9_tmp[faust_wrap_add(vsize, j829)];
			}
			for (int j831 = 0; j831 < 4; j831 = faust_wrap_add(j831, 1)) {
				fRec10_perm[j831] = fRec10_tmp[faust_wrap_add(vsize, j831)];
			}
			for (int j833 = 0; j833 < 4; j833 = faust_wrap_add(j833, 1)) {
				fRec11_perm[j833] = fRec11_tmp[faust_wrap_add(vsize, j833)];
			}
			for (int j835 = 0; j835 < 4; j835 = faust_wrap_add(j835, 1)) {
				fRec12_perm[j835] = fRec12_tmp[faust_wrap_add(vsize, j835)];
			}
			for (int j837 = 0; j837 < 4; j837 = faust_wrap_add(j837, 1)) {
				fRec13_perm[j837] = fRec13_tmp[faust_wrap_add(vsize, j837)];
			}
			for (int j839 = 0; j839 < 4; j839 = faust_wrap_add(j839, 1)) {
				fRec14_perm[j839] = fRec14_tmp[faust_wrap_add(vsize, j839)];
			}
			for (int j841 = 0; j841 < 4; j841 = faust_wrap_add(j841, 1)) {
				fRec15_perm[j841] = fRec15_tmp[faust_wrap_add(vsize, j841)];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output0[i] = static_cast<FAUSTFLOAT>(fSlow173 * (fRec0[i] + fRec2[i] + fRec4[i] + fRec6[i] + fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i]));
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; i < vsize; i = faust_wrap_add(i, 1)) {
				output1[i] = static_cast<FAUSTFLOAT>(fSlow173 * (fRec1[i] + fRec3[i] + fRec5[i] + fRec7[i] + fRec9[i] + fRec11[i] + fRec13[i] + fRec15[i]));
			}
		}
	}

};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4);
    runDSP(new mydsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new mydsp(), linenum, nbsamples/4, 1);
    
    return 0;
}

#endif
