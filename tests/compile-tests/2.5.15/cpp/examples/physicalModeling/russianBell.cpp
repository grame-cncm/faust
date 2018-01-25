/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "RussianChurchBell"
Code generated with Faust 2.5.15 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


// algorithm is required for min and max
#include <algorithm>
#include "gui/UI.h"

using namespace std;

// the struct below are not defined in UI.h
struct dsp {
};

struct Meta {
	void declare(const char*, const char*) {}
};
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <cmath>
#include <math.h>

static float fmydspSIG0Wave0[350] = {0.925507009f,0.597519994f,0.0965671018f,0.45412001f,0.989772975f,0.593497992f,0.512540996f,0.124241002f,0.705411017f,0.292396009f,0.673398972f,0.302181005f,0.0262340009f,0.286249012f,0.556267023f,1.0f,0.250425994f,0.107711002f,0.427298993f,0.336295009f,0.616257012f,0.214420006f,0.0845293999f,0.231362998f,0.522723973f,0.559113979f,0.348470002f,0.854197025f,0.835575998f,0.735036016f,0.288493991f,0.117122002f,0.409685999f,0.363575011f,0.484943002f,0.170862004f,0.420531005f,0.164793f,0.233847007f,0.861231983f,0.214037001f,0.283461988f,0.173152998f,0.876121998f,0.607809007f,0.294744998f,0.143142f,0.332008988f,0.491878003f,0.626103997f,0.962027013f,0.584298015f,0.213652998f,0.420451999f,0.812328994f,0.545171976f,0.38074401f,0.331535995f,0.386801004f,0.248908997f,0.688755989f,0.313903987f,0.377894014f,0.595845997f,0.412274003f,0.73962599f,0.541148007f,0.393005013f,0.656637013f,0.847671986f,0.930652976f,0.288289011f,0.404938012f,0.657989025f,0.763948977f,0.574084997f,0.282240987f,1.0f,0.429131001f,0.572049022f,0.73486799f,0.577476978f,0.520789027f,0.355592996f,0.890066981f,0.272390991f,0.448222995f,0.423969001f,0.392237008f,0.856091022f,0.0583794005f,0.784967005f,0.359526992f,0.576566994f,0.201513007f,0.642013013f,0.419308007f,0.340667009f,0.423189998f,0.860812008f,0.694019973f,0.42356801f,0.37698701f,0.568453014f,0.502301991f,0.280716002f,0.464040995f,0.395601004f,0.199849993f,0.0950397998f,0.64279002f,0.228325993f,0.484910995f,0.842352986f,0.161403999f,0.403432012f,0.65554899f,0.409097999f,0.699392021f,0.876049995f,1.0f,0.185606003f,0.414254993f,0.695204973f,0.732612014f,0.478298008f,0.249469995f,0.927739024f,0.213135004f,0.227382004f,0.976351976f,0.642745018f,0.376311004f,0.260674f,0.811034024f,0.264631003f,0.239978999f,0.261896998f,0.191642001f,0.781669974f,0.390679002f,0.382436991f,0.206714004f,0.224720001f,0.0676331967f,0.502610981f,0.301454991f,0.241028994f,0.224505007f,0.721193016f,0.436347991f,0.254061997f,0.480495989f,0.772370994f,0.210681006f,0.103414997f,0.485338002f,0.378333986f,0.228484005f,0.114877f,0.686760008f,0.296941996f,0.507420003f,0.997470021f,0.0377103016f,0.132211998f,0.319546998f,0.192031994f,0.520573974f,0.58584398f,0.419362009f,0.084731698f,0.134544f,0.194762006f,0.616689026f,0.397359997f,0.298808992f,0.914745986f,0.0513371006f,0.0543568991f,0.989158988f,0.602891982f,0.145582005f,0.102149002f,0.129022002f,0.116485f,0.279987991f,0.394270003f,0.29013899f,1.0f,0.708655f,0.78055501f,0.387526006f,0.0395217016f,0.00964067038f,0.24368f,0.0740624964f,0.619315028f,0.447394997f,0.292497009f,0.295457989f,0.163747996f,0.521375f,0.864533007f,0.0773407966f,0.0334230997f,0.345120996f,0.278860003f,0.223875999f,0.307756007f,0.763105989f,0.424706995f,0.487201005f,0.968962014f,0.00911747012f,0.0324653015f,0.334275007f,0.166786999f,0.312498003f,0.264261991f,0.354880005f,0.375589997f,0.261094004f,0.565006018f,0.474934995f,0.313520014f,0.251248986f,0.73535198f,0.0189072005f,0.0153633999f,0.786225021f,0.503298998f,0.369037986f,0.250764996f,0.673018992f,0.387573004f,0.742025018f,0.749055982f,0.261714011f,0.75186801f,0.771816015f,1.0f,0.459484011f,0.0124402f,0.0105394004f,0.964109004f,0.457051992f,0.532316029f,0.407128006f,0.697241008f,0.152199998f,0.0895892978f,0.406174988f,0.651040018f,0.0233951006f,0.0101070004f,0.0722346976f,0.0666339993f,0.195489004f,0.41674f,0.654451013f,0.382782012f,0.305395991f,0.631501019f,0.00162801996f,0.0140906004f,0.762915015f,0.410245001f,0.189436004f,0.060446199f,0.624940991f,0.43978101f,0.516273022f,0.896677971f,0.273297995f,0.202868f,0.0996022001f,0.257656991f,0.0174508002f,0.0157859009f,0.429432988f,0.202184007f,0.443111002f,0.343811005f,0.447562009f,0.268694013f,0.753551006f,0.529425979f,0.0772973001f,0.0976959988f,0.446413994f,0.26167801f,0.169035003f,0.0116218999f,0.0207398999f,1.0f,0.488855988f,0.413028985f,0.25266099f,0.148368999f,0.0919644013f,0.0330634005f,0.268763989f,0.441848993f,0.0139873f,0.0108583998f,0.657799006f,0.488247991f,0.375432998f,0.958178997f,0.761492014f,0.409489989f,0.151709005f,0.314931005f,0.00361180003f,0.0133069996f,1.0f,0.605342984f,0.550505996f,0.363516003f,0.255277991f,0.137537003f,0.448881f,0.867614985f,0.483247012f,0.308622003f,0.348444015f,0.534834981f,0.0157715995f,0.0128964996f,0.147607997f,0.0762611032f,0.762224019f,0.511584997f,0.98586297f,0.540226996f,0.691690981f,0.905296028f,0.397520989f,0.697939992f,0.423289001f,0.924612999f,0.491558999f,0.00567911007f,0.0106001999f,0.647916019f,0.324182004f,0.579448998f,0.451936007f,0.877897024f};

class mydspSIG0 {
	
  private:
	
	int fmydspSIG0Wave0_idx;
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
		
	}
	int getNumOutputsmydspSIG0() {
		return 1;
		
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
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
	
	void instanceInitmydspSIG0(int samplingFreq) {
		fmydspSIG0Wave0_idx = 0;
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			output[i] = fmydspSIG0Wave0[fmydspSIG0Wave0_idx];
			fmydspSIG0Wave0_idx = ((1 + fmydspSIG0Wave0_idx) % 350);
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}
static float ftbl0mydspSIG0[350];

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	int iRec3[2];
	float fConst6;
	float fConst7;
	float fRec2[3];
	float fConst8;
	float fRec1[3];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fConst9;
	FAUSTFLOAT fHslider2;
	float fVec1[2];
	float fRec4[2];
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec0[3];
	FAUSTFLOAT fEntry0;
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec5[3];
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec6[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec7[3];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec8[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec9[3];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec10[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec11[3];
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec12[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec13[3];
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec14[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec15[3];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec16[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec17[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec18[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec19[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec20[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec21[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec22[3];
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec23[3];
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec24[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec25[3];
	float fConst78;
	float fConst79;
	float fConst80;
	float fRec26[3];
	float fConst81;
	float fConst82;
	float fConst83;
	float fRec27[3];
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec28[3];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec29[3];
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec30[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec31[3];
	float fConst96;
	float fConst97;
	float fConst98;
	float fRec32[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec33[3];
	float fConst102;
	float fConst103;
	float fConst104;
	float fRec34[3];
	float fConst105;
	float fConst106;
	float fConst107;
	float fRec35[3];
	float fConst108;
	float fConst109;
	float fConst110;
	float fRec36[3];
	float fConst111;
	float fConst112;
	float fConst113;
	float fRec37[3];
	float fConst114;
	float fConst115;
	float fConst116;
	float fRec38[3];
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec39[3];
	float fConst120;
	float fConst121;
	float fConst122;
	float fRec40[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fRec41[3];
	float fConst126;
	float fConst127;
	float fConst128;
	float fRec42[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec43[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec44[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec45[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec46[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec47[3];
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec48[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec49[3];
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec50[3];
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec51[3];
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec52[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec53[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("description", "Russian church bell physical model.");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "RussianChurchBell");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
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
	
	static void classInit(int samplingFreq) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(350, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = tanf((31.415926f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 1.41421354f) / fConst2) + 1.0f));
		fConst5 = (1.0f / mydsp_faustpower2_f(fConst2));
		fConst6 = (((fConst3 + -1.41421354f) / fConst2) + 1.0f);
		fConst7 = (2.0f * (1.0f - fConst5));
		fConst8 = (2.0f * (0.0f - fConst5));
		fConst9 = (0.00400000019f * fConst0);
		fConst10 = (0.00200000009f * fConst0);
		fConst11 = (500.0f / fConst0);
		fConst12 = powf(0.00100000005f, (1.0f / (0.025818795f * fConst0)));
		fConst13 = ((0.0f - (2.0f * fConst12)) * cosf((6828.37744f / fConst0)));
		fConst14 = mydsp_faustpower2_f(fConst12);
		fConst15 = powf(0.00100000005f, (1.0f / (0.0138441315f * fConst0)));
		fConst16 = ((0.0f - (2.0f * fConst15)) * cosf((6963.02588f / fConst0)));
		fConst17 = mydsp_faustpower2_f(fConst15);
		fConst18 = powf(0.00100000005f, (1.0f / (0.0105750728f * fConst0)));
		fConst19 = ((0.0f - (2.0f * fConst18)) * cosf((7013.10303f / fConst0)));
		fConst20 = mydsp_faustpower2_f(fConst18);
		fConst21 = powf(0.00100000005f, (1.0f / (0.00243636267f * fConst0)));
		fConst22 = ((0.0f - (2.0f * fConst21)) * cosf((7219.37988f / fConst0)));
		fConst23 = mydsp_faustpower2_f(fConst21);
		fConst24 = powf(0.00100000005f, (1.0f / (0.00222628773f * fConst0)));
		fConst25 = ((0.0f - (2.0f * fConst24)) * cosf((7229.05615f / fConst0)));
		fConst26 = mydsp_faustpower2_f(fConst24);
		fConst27 = powf(0.00100000005f, (1.0f / (5.50089538e-08f * fConst0)));
		fConst28 = ((0.0f - (2.0f * fConst27)) * cosf((7536.93213f / fConst0)));
		fConst29 = mydsp_faustpower2_f(fConst27);
		fConst30 = powf(0.00100000005f, (1.0f / (20.8901539f * fConst0)));
		fConst31 = ((0.0f - (2.0f * fConst30)) * cosf((857.598267f / fConst0)));
		fConst32 = mydsp_faustpower2_f(fConst30);
		fConst33 = powf(0.00100000005f, (1.0f / (20.860672f * fConst0)));
		fConst34 = ((0.0f - (2.0f * fConst33)) * cosf((860.746094f / fConst0)));
		fConst35 = mydsp_faustpower2_f(fConst33);
		fConst36 = powf(0.00100000005f, (1.0f / (14.4779148f * fConst0)));
		fConst37 = ((0.0f - (2.0f * fConst36)) * cosf((1627.08105f / fConst0)));
		fConst38 = mydsp_faustpower2_f(fConst36);
		fConst39 = powf(0.00100000005f, (1.0f / (14.4106588f * fConst0)));
		fConst40 = ((0.0f - (2.0f * fConst39)) * cosf((1636.26086f / fConst0)));
		fConst41 = mydsp_faustpower2_f(fConst39);
		fConst42 = powf(0.00100000005f, (1.0f / (11.9841108f * fConst0)));
		fConst43 = ((0.0f - (2.0f * fConst42)) * cosf((1988.55908f / fConst0)));
		fConst44 = mydsp_faustpower2_f(fConst42);
		fConst45 = powf(0.00100000005f, (1.0f / (11.9061594f * fConst0)));
		fConst46 = ((0.0f - (2.0f * fConst45)) * cosf((2000.63538f / fConst0)));
		fConst47 = mydsp_faustpower2_f(fConst45);
		fConst48 = powf(0.00100000005f, (1.0f / (9.10661697f * fConst0)));
		fConst49 = ((0.0f - (2.0f * fConst48)) * cosf((2474.64502f / fConst0)));
		fConst50 = mydsp_faustpower2_f(fConst48);
		fConst51 = powf(0.00100000005f, (1.0f / (9.10333347f * fConst0)));
		fConst52 = ((0.0f - (2.0f * fConst51)) * cosf((2475.25464f / fConst0)));
		fConst53 = mydsp_faustpower2_f(fConst51);
		fConst54 = powf(0.00100000005f, (1.0f / (7.19911861f * fConst0)));
		fConst55 = ((0.0f - (2.0f * fConst54)) * cosf((2856.81982f / fConst0)));
		fConst56 = mydsp_faustpower2_f(fConst54);
		fConst57 = powf(0.00100000005f, (1.0f / (6.83458185f * fConst0)));
		fConst58 = ((0.0f - (2.0f * fConst57)) * cosf((2937.34521f / fConst0)));
		fConst59 = mydsp_faustpower2_f(fConst57);
		fConst60 = powf(0.00100000005f, (1.0f / (5.87431335f * fConst0)));
		fConst61 = ((0.0f - (2.0f * fConst60)) * cosf((3164.17432f / fConst0)));
		fConst62 = mydsp_faustpower2_f(fConst60);
		fConst63 = powf(0.00100000005f, (1.0f / (5.87322664f * fConst0)));
		fConst64 = ((0.0f - (2.0f * fConst63)) * cosf((3164.44458f / fConst0)));
		fConst65 = mydsp_faustpower2_f(fConst63);
		fConst66 = powf(0.00100000005f, (1.0f / (5.22125483f * fConst0)));
		fConst67 = ((0.0f - (2.0f * fConst66)) * cosf((3332.97852f / fConst0)));
		fConst68 = mydsp_faustpower2_f(fConst66);
		fConst69 = powf(0.00100000005f, (1.0f / (5.20757818f * fConst0)));
		fConst70 = ((0.0f - (2.0f * fConst69)) * cosf((3336.6604f / fConst0)));
		fConst71 = mydsp_faustpower2_f(fConst69);
		fConst72 = powf(0.00100000005f, (1.0f / (4.97527456f * fConst0)));
		fConst73 = ((0.0f - (2.0f * fConst72)) * cosf((3400.2085f / fConst0)));
		fConst74 = mydsp_faustpower2_f(fConst72);
		fConst75 = powf(0.00100000005f, (1.0f / (4.86307383f * fConst0)));
		fConst76 = ((0.0f - (2.0f * fConst75)) * cosf((3431.61182f / fConst0)));
		fConst77 = mydsp_faustpower2_f(fConst75);
		fConst78 = powf(0.00100000005f, (1.0f / (4.18086052f * fConst0)));
		fConst79 = ((0.0f - (2.0f * fConst78)) * cosf((3633.78589f / fConst0)));
		fConst80 = mydsp_faustpower2_f(fConst78);
		fConst81 = powf(0.00100000005f, (1.0f / (4.15015745f * fConst0)));
		fConst82 = ((0.0f - (2.0f * fConst81)) * cosf((3643.38672f / fConst0)));
		fConst83 = mydsp_faustpower2_f(fConst81);
		fConst84 = powf(0.00100000005f, (1.0f / (2.74179292f * fConst0)));
		fConst85 = ((0.0f - (2.0f * fConst84)) * cosf((4147.06543f / fConst0)));
		fConst86 = mydsp_faustpower2_f(fConst84);
		fConst87 = powf(0.00100000005f, (1.0f / (2.07085514f * fConst0)));
		fConst88 = ((0.0f - (2.0f * fConst87)) * cosf((4450.63135f / fConst0)));
		fConst89 = mydsp_faustpower2_f(fConst87);
		fConst90 = powf(0.00100000005f, (1.0f / (1.96459568f * fConst0)));
		fConst91 = ((0.0f - (2.0f * fConst90)) * cosf((4504.50977f / fConst0)));
		fConst92 = mydsp_faustpower2_f(fConst90);
		fConst93 = powf(0.00100000005f, (1.0f / (1.9607631f * fConst0)));
		fConst94 = ((0.0f - (2.0f * fConst93)) * cosf((4506.48877f / fConst0)));
		fConst95 = mydsp_faustpower2_f(fConst93);
		fConst96 = powf(0.00100000005f, (1.0f / (1.33098233f * fConst0)));
		fConst97 = ((0.0f - (2.0f * fConst96)) * cosf((4874.74023f / fConst0)));
		fConst98 = mydsp_faustpower2_f(fConst96);
		fConst99 = powf(0.00100000005f, (1.0f / (1.32885158f * fConst0)));
		fConst100 = ((0.0f - (2.0f * fConst99)) * cosf((4876.1665f / fConst0)));
		fConst101 = mydsp_faustpower2_f(fConst99);
		fConst102 = powf(0.00100000005f, (1.0f / (1.26162803f * fConst0)));
		fConst103 = ((0.0f - (2.0f * fConst102)) * cosf((4921.9707f / fConst0)));
		fConst104 = mydsp_faustpower2_f(fConst102);
		fConst105 = powf(0.00100000005f, (1.0f / (1.26064956f * fConst0)));
		fConst106 = ((0.0f - (2.0f * fConst105)) * cosf((4922.64941f / fConst0)));
		fConst107 = mydsp_faustpower2_f(fConst105);
		fConst108 = powf(0.00100000005f, (1.0f / (1.21270394f * fConst0)));
		fConst109 = ((0.0f - (2.0f * fConst108)) * cosf((4956.33984f / fConst0)));
		fConst110 = mydsp_faustpower2_f(fConst108);
		fConst111 = powf(0.00100000005f, (1.0f / (1.20709014f * fConst0)));
		fConst112 = ((0.0f - (2.0f * fConst111)) * cosf((4960.34229f / fConst0)));
		fConst113 = mydsp_faustpower2_f(fConst111);
		fConst114 = powf(0.00100000005f, (1.0f / (1.1138221f * fConst0)));
		fConst115 = ((0.0f - (2.0f * fConst114)) * cosf((5028.73486f / fConst0)));
		fConst116 = mydsp_faustpower2_f(fConst114);
		fConst117 = powf(0.00100000005f, (1.0f / (1.06121433f * fConst0)));
		fConst118 = ((0.0f - (2.0f * fConst117)) * cosf((5069.01025f / fConst0)));
		fConst119 = mydsp_faustpower2_f(fConst117);
		fConst120 = powf(0.00100000005f, (1.0f / (0.59021306f * fConst0)));
		fConst121 = ((0.0f - (2.0f * fConst120)) * cosf((5509.02148f / fConst0)));
		fConst122 = mydsp_faustpower2_f(fConst120);
		fConst123 = powf(0.00100000005f, (1.0f / (0.570631444f * fConst0)));
		fConst124 = ((0.0f - (2.0f * fConst123)) * cosf((5531.8042f / fConst0)));
		fConst125 = mydsp_faustpower2_f(fConst123);
		fConst126 = powf(0.00100000005f, (1.0f / (0.534661531f * fConst0)));
		fConst127 = ((0.0f - (2.0f * fConst126)) * cosf((5575.05127f / fConst0)));
		fConst128 = mydsp_faustpower2_f(fConst126);
		fConst129 = powf(0.00100000005f, (1.0f / (0.529946029f * fConst0)));
		fConst130 = ((0.0f - (2.0f * fConst129)) * cosf((5580.86328f / fConst0)));
		fConst131 = mydsp_faustpower2_f(fConst129);
		fConst132 = powf(0.00100000005f, (1.0f / (0.397494107f * fConst0)));
		fConst133 = ((0.0f - (2.0f * fConst132)) * cosf((5760.51855f / fConst0)));
		fConst134 = mydsp_faustpower2_f(fConst132);
		fConst135 = powf(0.00100000005f, (1.0f / (0.38546589f * fConst0)));
		fConst136 = ((0.0f - (2.0f * fConst135)) * cosf((5778.71484f / fConst0)));
		fConst137 = mydsp_faustpower2_f(fConst135);
		fConst138 = powf(0.00100000005f, (1.0f / (0.316193342f * fConst0)));
		fConst139 = ((0.0f - (2.0f * fConst138)) * cosf((5891.65479f / fConst0)));
		fConst140 = mydsp_faustpower2_f(fConst138);
		fConst141 = powf(0.00100000005f, (1.0f / (0.17550005f * fConst0)));
		fConst142 = ((0.0f - (2.0f * fConst141)) * cosf((6186.46191f / fConst0)));
		fConst143 = mydsp_faustpower2_f(fConst141);
		fConst144 = powf(0.00100000005f, (1.0f / (0.05150491f * fConst0)));
		fConst145 = ((0.0f - (2.0f * fConst144)) * cosf((6642.5835f / fConst0)));
		fConst146 = mydsp_faustpower2_f(fConst144);
		fConst147 = powf(0.00100000005f, (1.0f / (0.0501735061f * fConst0)));
		fConst148 = ((0.0f - (2.0f * fConst147)) * cosf((6650.4375f / fConst0)));
		fConst149 = mydsp_faustpower2_f(fConst147);
		fConst150 = powf(0.00100000005f, (1.0f / (0.0431109592f * fConst0)));
		fConst151 = ((0.0f - (2.0f * fConst150)) * cosf((6694.6084f / fConst0)));
		fConst152 = mydsp_faustpower2_f(fConst150);
		fConst153 = powf(0.00100000005f, (1.0f / (0.0289916229f * fConst0)));
		fConst154 = ((0.0f - (2.0f * fConst153)) * cosf((6800.10303f / fConst0)));
		fConst155 = mydsp_faustpower2_f(fConst153);
		fConst156 = powf(0.00100000005f, (1.0f / (0.0277926214f * fConst0)));
		fConst157 = ((0.0f - (2.0f * fConst156)) * cosf((6810.5332f / fConst0)));
		fConst158 = mydsp_faustpower2_f(fConst156);
		fConst159 = powf(0.00100000005f, (1.0f / (0.0259682462f * fConst0)));
		fConst160 = ((0.0f - (2.0f * fConst159)) * cosf((6826.99512f / fConst0)));
		fConst161 = mydsp_faustpower2_f(fConst159);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(6500.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fEntry0 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec3[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec0[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec5[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec9[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec10[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec12[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec13[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec15[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec16[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec17[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec22[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec23[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec24[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec25[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec26[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec27[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec28[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec29[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec30[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec31[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec32[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec33[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec34[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec35[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec36[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec37[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec38[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec39[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec40[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec41[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec42[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec43[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec44[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec45[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec46[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec47[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec48[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec49[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec50[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec51[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec52[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec53[l55] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("russianBell");
		ui_interface->declare(&fEntry0, "0", "");
		ui_interface->addNumEntry("strikePosition", &fEntry0, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->addHorizontalSlider("strikeCutOff", &fHslider1, 6500.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->addHorizontalSlider("strikeSharpness", &fHslider2, 0.5f, 0.00999999978f, 5.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->addHorizontalSlider("gain", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fButton0, "4", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = tanf((fConst1 * float(fHslider1)));
		float fSlow1 = (1.0f / fSlow0);
		float fSlow2 = (((fSlow1 + 1.41421354f) / fSlow0) + 1.0f);
		float fSlow3 = (float(fHslider0) / fSlow2);
		float fSlow4 = (1.0f / fSlow2);
		float fSlow5 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow0))));
		float fSlow6 = (((fSlow1 + -1.41421354f) / fSlow0) + 1.0f);
		float fSlow7 = float(fButton0);
		float fSlow8 = float(fHslider2);
		float fSlow9 = (fConst9 * fSlow8);
		float fSlow10 = (fConst10 * fSlow8);
		float fSlow11 = (fConst11 / fSlow8);
		int iSlow12 = (50 * int(float(fEntry0)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = ((4.65661287e-10f * float(iRec3[0])) - (fConst4 * ((fConst6 * fRec2[2]) + (fConst7 * fRec2[1]))));
			fRec1[0] = ((fConst4 * (((fConst5 * fRec2[0]) + (fConst8 * fRec2[1])) + (fConst5 * fRec2[2]))) - (fSlow4 * ((fSlow5 * fRec1[1]) + (fSlow6 * fRec1[2]))));
			fVec0[0] = fSlow7;
			fVec1[0] = fSlow8;
			fRec4[0] = ((((fSlow7 - fVec0[1]) > 0.0f) > 0)?0.0f:min(fSlow9, ((fRec4[1] + (fConst9 * (fSlow8 - fVec1[1]))) + 1.0f)));
			int iTemp0 = (fRec4[0] < fSlow10);
			float fTemp1 = (fSlow3 * ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) * (iTemp0?((fRec4[0] < 0.0f)?0.0f:(iTemp0?(fSlow11 * fRec4[0]):1.0f)):((fRec4[0] < fSlow9)?((fSlow11 * (0.0f - (fRec4[0] - fSlow10))) + 1.0f):0.0f))));
			fRec0[0] = (fTemp1 - ((fConst13 * fRec0[1]) + (fConst14 * fRec0[2])));
			fRec5[0] = (fTemp1 - ((fConst16 * fRec5[1]) + (fConst17 * fRec5[2])));
			fRec6[0] = (fTemp1 - ((fConst19 * fRec6[1]) + (fConst20 * fRec6[2])));
			fRec7[0] = (fTemp1 - ((fConst22 * fRec7[1]) + (fConst23 * fRec7[2])));
			fRec8[0] = (fTemp1 - ((fConst25 * fRec8[1]) + (fConst26 * fRec8[2])));
			fRec9[0] = (fTemp1 - ((fConst28 * fRec9[1]) + (fConst29 * fRec9[2])));
			fRec10[0] = (fTemp1 - ((fConst31 * fRec10[1]) + (fConst32 * fRec10[2])));
			fRec11[0] = (fTemp1 - ((fConst34 * fRec11[1]) + (fConst35 * fRec11[2])));
			fRec12[0] = (fTemp1 - ((fConst37 * fRec12[1]) + (fConst38 * fRec12[2])));
			fRec13[0] = (fTemp1 - ((fConst40 * fRec13[1]) + (fConst41 * fRec13[2])));
			fRec14[0] = (fTemp1 - ((fConst43 * fRec14[1]) + (fConst44 * fRec14[2])));
			fRec15[0] = (fTemp1 - ((fConst46 * fRec15[1]) + (fConst47 * fRec15[2])));
			fRec16[0] = (fTemp1 - ((fConst49 * fRec16[1]) + (fConst50 * fRec16[2])));
			fRec17[0] = (fTemp1 - ((fConst52 * fRec17[1]) + (fConst53 * fRec17[2])));
			fRec18[0] = (fTemp1 - ((fConst55 * fRec18[1]) + (fConst56 * fRec18[2])));
			fRec19[0] = (fTemp1 - ((fConst58 * fRec19[1]) + (fConst59 * fRec19[2])));
			fRec20[0] = (fTemp1 - ((fConst61 * fRec20[1]) + (fConst62 * fRec20[2])));
			fRec21[0] = (fTemp1 - ((fConst64 * fRec21[1]) + (fConst65 * fRec21[2])));
			fRec22[0] = (fTemp1 - ((fConst67 * fRec22[1]) + (fConst68 * fRec22[2])));
			fRec23[0] = (fTemp1 - ((fConst70 * fRec23[1]) + (fConst71 * fRec23[2])));
			fRec24[0] = (fTemp1 - ((fConst73 * fRec24[1]) + (fConst74 * fRec24[2])));
			fRec25[0] = (fTemp1 - ((fConst76 * fRec25[1]) + (fConst77 * fRec25[2])));
			fRec26[0] = (fTemp1 - ((fConst79 * fRec26[1]) + (fConst80 * fRec26[2])));
			fRec27[0] = (fTemp1 - ((fConst82 * fRec27[1]) + (fConst83 * fRec27[2])));
			fRec28[0] = (fTemp1 - ((fConst85 * fRec28[1]) + (fConst86 * fRec28[2])));
			fRec29[0] = (fTemp1 - ((fConst88 * fRec29[1]) + (fConst89 * fRec29[2])));
			fRec30[0] = (fTemp1 - ((fConst91 * fRec30[1]) + (fConst92 * fRec30[2])));
			fRec31[0] = (fTemp1 - ((fConst94 * fRec31[1]) + (fConst95 * fRec31[2])));
			fRec32[0] = (fTemp1 - ((fConst97 * fRec32[1]) + (fConst98 * fRec32[2])));
			fRec33[0] = (fTemp1 - ((fConst100 * fRec33[1]) + (fConst101 * fRec33[2])));
			fRec34[0] = (fTemp1 - ((fConst103 * fRec34[1]) + (fConst104 * fRec34[2])));
			fRec35[0] = (fTemp1 - ((fConst106 * fRec35[1]) + (fConst107 * fRec35[2])));
			fRec36[0] = (fTemp1 - ((fConst109 * fRec36[1]) + (fConst110 * fRec36[2])));
			fRec37[0] = (fTemp1 - ((fConst112 * fRec37[1]) + (fConst113 * fRec37[2])));
			fRec38[0] = (fTemp1 - ((fConst115 * fRec38[1]) + (fConst116 * fRec38[2])));
			fRec39[0] = (fTemp1 - ((fConst118 * fRec39[1]) + (fConst119 * fRec39[2])));
			fRec40[0] = (fTemp1 - ((fConst121 * fRec40[1]) + (fConst122 * fRec40[2])));
			fRec41[0] = (fTemp1 - ((fConst124 * fRec41[1]) + (fConst125 * fRec41[2])));
			fRec42[0] = (fTemp1 - ((fConst127 * fRec42[1]) + (fConst128 * fRec42[2])));
			fRec43[0] = (fTemp1 - ((fConst130 * fRec43[1]) + (fConst131 * fRec43[2])));
			fRec44[0] = (fTemp1 - ((fConst133 * fRec44[1]) + (fConst134 * fRec44[2])));
			fRec45[0] = (fTemp1 - ((fConst136 * fRec45[1]) + (fConst137 * fRec45[2])));
			fRec46[0] = (fTemp1 - ((fConst139 * fRec46[1]) + (fConst140 * fRec46[2])));
			fRec47[0] = (fTemp1 - ((fConst142 * fRec47[1]) + (fConst143 * fRec47[2])));
			fRec48[0] = (fTemp1 - ((fConst145 * fRec48[1]) + (fConst146 * fRec48[2])));
			fRec49[0] = (fTemp1 - ((fConst148 * fRec49[1]) + (fConst149 * fRec49[2])));
			fRec50[0] = (fTemp1 - ((fConst151 * fRec50[1]) + (fConst152 * fRec50[2])));
			fRec51[0] = (fTemp1 - ((fConst154 * fRec51[1]) + (fConst155 * fRec51[2])));
			fRec52[0] = (fTemp1 - ((fConst157 * fRec52[1]) + (fConst158 * fRec52[2])));
			fRec53[0] = (fTemp1 - ((fConst160 * fRec53[1]) + (fConst161 * fRec53[2])));
			float fTemp2 = (0.0199999996f * (((((((((((((((((((((((((((((((((((((((((((((((((((fRec0[0] - fRec0[2]) * ftbl0mydspSIG0[(iSlow12 + 44)]) + ((fRec5[0] - fRec5[2]) * ftbl0mydspSIG0[(iSlow12 + 45)])) + ((fRec6[0] - fRec6[2]) * ftbl0mydspSIG0[(iSlow12 + 46)])) + ((fRec7[0] - fRec7[2]) * ftbl0mydspSIG0[(iSlow12 + 47)])) + ((fRec8[0] - fRec8[2]) * ftbl0mydspSIG0[(iSlow12 + 48)])) + ((fRec9[0] - fRec9[2]) * ftbl0mydspSIG0[(iSlow12 + 49)])) + (ftbl0mydspSIG0[iSlow12] * (fRec10[0] - fRec10[2]))) + (ftbl0mydspSIG0[(iSlow12 + 1)] * (fRec11[0] - fRec11[2]))) + (ftbl0mydspSIG0[(iSlow12 + 2)] * (fRec12[0] - fRec12[2]))) + (ftbl0mydspSIG0[(iSlow12 + 3)] * (fRec13[0] - fRec13[2]))) + (ftbl0mydspSIG0[(iSlow12 + 4)] * (fRec14[0] - fRec14[2]))) + (ftbl0mydspSIG0[(iSlow12 + 5)] * (fRec15[0] - fRec15[2]))) + (ftbl0mydspSIG0[(iSlow12 + 6)] * (fRec16[0] - fRec16[2]))) + (ftbl0mydspSIG0[(iSlow12 + 7)] * (fRec17[0] - fRec17[2]))) + (ftbl0mydspSIG0[(iSlow12 + 8)] * (fRec18[0] - fRec18[2]))) + (ftbl0mydspSIG0[(iSlow12 + 9)] * (fRec19[0] - fRec19[2]))) + (ftbl0mydspSIG0[(iSlow12 + 10)] * (fRec20[0] - fRec20[2]))) + (ftbl0mydspSIG0[(iSlow12 + 11)] * (fRec21[0] - fRec21[2]))) + (ftbl0mydspSIG0[(iSlow12 + 12)] * (fRec22[0] - fRec22[2]))) + (ftbl0mydspSIG0[(iSlow12 + 13)] * (fRec23[0] - fRec23[2]))) + (ftbl0mydspSIG0[(iSlow12 + 14)] * (fRec24[0] - fRec24[2]))) + (ftbl0mydspSIG0[(iSlow12 + 15)] * (fRec25[0] - fRec25[2]))) + (ftbl0mydspSIG0[(iSlow12 + 16)] * (fRec26[0] - fRec26[2]))) + (ftbl0mydspSIG0[(iSlow12 + 17)] * (fRec27[0] - fRec27[2]))) + (ftbl0mydspSIG0[(iSlow12 + 18)] * (fRec28[0] - fRec28[2]))) + (ftbl0mydspSIG0[(iSlow12 + 19)] * (fRec29[0] - fRec29[2]))) + (ftbl0mydspSIG0[(iSlow12 + 20)] * (fRec30[0] - fRec30[2]))) + (ftbl0mydspSIG0[(iSlow12 + 21)] * (fRec31[0] - fRec31[2]))) + (ftbl0mydspSIG0[(iSlow12 + 22)] * (fRec32[0] - fRec32[2]))) + (ftbl0mydspSIG0[(iSlow12 + 23)] * (fRec33[0] - fRec33[2]))) + (ftbl0mydspSIG0[(iSlow12 + 24)] * (fRec34[0] - fRec34[2]))) + (ftbl0mydspSIG0[(iSlow12 + 25)] * (fRec35[0] - fRec35[2]))) + (ftbl0mydspSIG0[(iSlow12 + 26)] * (fRec36[0] - fRec36[2]))) + (ftbl0mydspSIG0[(iSlow12 + 27)] * (fRec37[0] - fRec37[2]))) + (ftbl0mydspSIG0[(iSlow12 + 28)] * (fRec38[0] - fRec38[2]))) + (ftbl0mydspSIG0[(iSlow12 + 29)] * (fRec39[0] - fRec39[2]))) + (ftbl0mydspSIG0[(iSlow12 + 30)] * (fRec40[0] - fRec40[2]))) + (ftbl0mydspSIG0[(iSlow12 + 31)] * (fRec41[0] - fRec41[2]))) + (ftbl0mydspSIG0[(iSlow12 + 32)] * (fRec42[0] - fRec42[2]))) + (ftbl0mydspSIG0[(iSlow12 + 33)] * (fRec43[0] - fRec43[2]))) + (ftbl0mydspSIG0[(iSlow12 + 34)] * (fRec44[0] - fRec44[2]))) + (ftbl0mydspSIG0[(iSlow12 + 35)] * (fRec45[0] - fRec45[2]))) + (ftbl0mydspSIG0[(iSlow12 + 36)] * (fRec46[0] - fRec46[2]))) + (ftbl0mydspSIG0[(iSlow12 + 37)] * (fRec47[0] - fRec47[2]))) + (ftbl0mydspSIG0[(iSlow12 + 38)] * (fRec48[0] - fRec48[2]))) + (ftbl0mydspSIG0[(iSlow12 + 39)] * (fRec49[0] - fRec49[2]))) + (ftbl0mydspSIG0[(iSlow12 + 40)] * (fRec50[0] - fRec50[2]))) + (ftbl0mydspSIG0[(iSlow12 + 41)] * (fRec51[0] - fRec51[2]))) + (ftbl0mydspSIG0[(iSlow12 + 42)] * (fRec52[0] - fRec52[2]))) + (ftbl0mydspSIG0[(iSlow12 + 43)] * (fRec53[0] - fRec53[2]))));
			output0[i] = FAUSTFLOAT(fTemp2);
			output1[i] = FAUSTFLOAT(fTemp2);
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			
		}
		
	}

	
};

#endif
