/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "RussianChurchBell"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

//include for cpp logging
#include <iostream>

//includes for the clap helpers glue
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>

//guarded MapUI subclass to prevent accidental param writes
struct GuardedUI : public MapUI {
    bool allowWrite = false;
    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        if (!allowWrite) {
            std::abort(); //catch unintended writes early
        }
        MapUI::setParamValue(path, val);
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }
};


struct GuardedScope {
    GuardedUI& ui;
    const char* tag;

    GuardedScope(GuardedUI& ui, const char* src = "unknown") : ui(ui), tag(src) {
        ui.allowWrite = true;
    }

    ~GuardedScope() {
        ui.allowWrite = false;
    }
};

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

const static float fmydspSIG0Wave0[350] = {0.925507f,0.59752f,0.0965671f,0.45412f,0.989773f,0.593498f,0.512541f,0.124241f,0.705411f,0.292396f,0.673399f,0.302181f,0.026234f,0.286249f,0.556267f,1.0f,0.250426f,0.107711f,0.427299f,0.336295f,0.616257f,0.21442f,0.0845294f,0.231363f,0.522724f,0.559114f,0.34847f,0.854197f,0.835576f,0.735036f,0.288494f,0.117122f,0.409686f,0.363575f,0.484943f,0.170862f,0.420531f,0.164793f,0.233847f,0.861232f,0.214037f,0.283462f,0.173153f,0.876122f,0.607809f,0.294745f,0.143142f,0.332009f,0.491878f,0.626104f,0.962027f,0.584298f,0.213653f,0.420452f,0.812329f,0.545172f,0.380744f,0.331536f,0.386801f,0.248909f,0.688756f,0.313904f,0.377894f,0.595846f,0.412274f,0.739626f,0.541148f,0.393005f,0.656637f,0.847672f,0.930653f,0.288289f,0.404938f,0.657989f,0.763949f,0.574085f,0.282241f,1.0f,0.429131f,0.572049f,0.734868f,0.577477f,0.520789f,0.355593f,0.890067f,0.272391f,0.448223f,0.423969f,0.392237f,0.856091f,0.0583794f,0.784967f,0.359527f,0.576567f,0.201513f,0.642013f,0.419308f,0.340667f,0.42319f,0.860812f,0.69402f,0.423568f,0.376987f,0.568453f,0.502302f,0.280716f,0.464041f,0.395601f,0.19985f,0.0950398f,0.64279f,0.228326f,0.484911f,0.842353f,0.161404f,0.403432f,0.655549f,0.409098f,0.699392f,0.87605f,1.0f,0.185606f,0.414255f,0.695205f,0.732612f,0.478298f,0.24947f,0.927739f,0.213135f,0.227382f,0.976352f,0.642745f,0.376311f,0.260674f,0.811034f,0.264631f,0.239979f,0.261897f,0.191642f,0.78167f,0.390679f,0.382437f,0.206714f,0.22472f,0.0676332f,0.502611f,0.301455f,0.241029f,0.224505f,0.721193f,0.436348f,0.254062f,0.480496f,0.772371f,0.210681f,0.103415f,0.485338f,0.378334f,0.228484f,0.114877f,0.68676f,0.296942f,0.50742f,0.99747f,0.0377103f,0.132212f,0.319547f,0.192032f,0.520574f,0.585844f,0.419362f,0.0847317f,0.134544f,0.194762f,0.616689f,0.39736f,0.298809f,0.914746f,0.0513371f,0.0543569f,0.989159f,0.602892f,0.145582f,0.102149f,0.129022f,0.116485f,0.279988f,0.39427f,0.290139f,1.0f,0.708655f,0.780555f,0.387526f,0.0395217f,0.00964067f,0.24368f,0.0740625f,0.619315f,0.447395f,0.292497f,0.295458f,0.163748f,0.521375f,0.864533f,0.0773408f,0.0334231f,0.345121f,0.27886f,0.223876f,0.307756f,0.763106f,0.424707f,0.487201f,0.968962f,0.00911747f,0.0324653f,0.334275f,0.166787f,0.312498f,0.264262f,0.35488f,0.37559f,0.261094f,0.565006f,0.474935f,0.31352f,0.251249f,0.735352f,0.0189072f,0.0153634f,0.786225f,0.503299f,0.369038f,0.250765f,0.673019f,0.387573f,0.742025f,0.749056f,0.261714f,0.751868f,0.771816f,1.0f,0.459484f,0.0124402f,0.0105394f,0.964109f,0.457052f,0.532316f,0.407128f,0.697241f,0.1522f,0.0895893f,0.406175f,0.65104f,0.0233951f,0.010107f,0.0722347f,0.066634f,0.195489f,0.41674f,0.654451f,0.382782f,0.305396f,0.631501f,0.00162802f,0.0140906f,0.762915f,0.410245f,0.189436f,0.0604462f,0.624941f,0.439781f,0.516273f,0.896678f,0.273298f,0.202868f,0.0996022f,0.257657f,0.0174508f,0.0157859f,0.429433f,0.202184f,0.443111f,0.343811f,0.447562f,0.268694f,0.753551f,0.529426f,0.0772973f,0.097696f,0.446414f,0.261678f,0.169035f,0.0116219f,0.0207399f,1.0f,0.488856f,0.413029f,0.252661f,0.148369f,0.0919644f,0.0330634f,0.268764f,0.441849f,0.0139873f,0.0108584f,0.657799f,0.488248f,0.375433f,0.958179f,0.761492f,0.40949f,0.151709f,0.314931f,0.0036118f,0.013307f,1.0f,0.605343f,0.550506f,0.363516f,0.255278f,0.137537f,0.448881f,0.867615f,0.483247f,0.308622f,0.348444f,0.534835f,0.0157716f,0.0128965f,0.147608f,0.0762611f,0.762224f,0.511585f,0.985863f,0.540227f,0.691691f,0.905296f,0.397521f,0.69794f,0.423289f,0.924613f,0.491559f,0.00567911f,0.0106002f,0.647916f,0.324182f,0.579449f,0.451936f,0.877897f};
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
	
	void instanceInitmydspSIG0(int sample_rate) {
		fmydspSIG0Wave0_idx = 0;
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			table[i1] = fmydspSIG0Wave0[fmydspSIG0Wave0_idx];
			fmydspSIG0Wave0_idx = (1 + fmydspSIG0Wave0_idx) % 350;
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float mydsp_faustpower2_f(float value) {
	return value * value;
}
static float ftbl0mydspSIG0[350];

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	int iRec3[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec2[3];
	float fRec1[3];
	float fConst10;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	int iRec4[2];
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec0[3];
	FAUSTFLOAT fEntry0;
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec5[3];
	float fConst17;
	float fConst18;
	float fConst19;
	float fRec6[3];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec7[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec8[3];
	float fConst26;
	float fConst27;
	float fConst28;
	float fRec9[3];
	float fConst29;
	float fConst30;
	float fConst31;
	float fRec10[3];
	float fConst32;
	float fConst33;
	float fConst34;
	float fRec11[3];
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec12[3];
	float fConst38;
	float fConst39;
	float fConst40;
	float fRec13[3];
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec14[3];
	float fConst44;
	float fConst45;
	float fConst46;
	float fRec15[3];
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec16[3];
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec17[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec18[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec19[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec20[3];
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec21[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec22[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec23[3];
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec24[3];
	float fConst74;
	float fConst75;
	float fConst76;
	float fRec25[3];
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec26[3];
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec27[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec28[3];
	float fConst86;
	float fConst87;
	float fConst88;
	float fRec29[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec30[3];
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec31[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec32[3];
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec33[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec34[3];
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec35[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec36[3];
	float fConst110;
	float fConst111;
	float fConst112;
	float fRec37[3];
	float fConst113;
	float fConst114;
	float fConst115;
	float fRec38[3];
	float fConst116;
	float fConst117;
	float fConst118;
	float fRec39[3];
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec40[3];
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec41[3];
	float fConst125;
	float fConst126;
	float fConst127;
	float fRec42[3];
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec43[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec44[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec45[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec46[3];
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec47[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec48[3];
	float fConst146;
	float fConst147;
	float fConst148;
	float fRec49[3];
	float fConst149;
	float fConst150;
	float fConst151;
	float fRec50[3];
	float fConst152;
	float fConst153;
	float fConst154;
	float fRec51[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fRec52[3];
	float fConst158;
	float fConst159;
	float fConst160;
	float fRec53[3];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
		m->declare("description", "Russian church bell physical model.");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "russianBell.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "RussianChurchBell");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("physmodels.lib/name", "Faust Physical Models Library");
		m->declare("physmodels.lib/version", "1.2.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(350, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.1415927f / fConst0;
		fConst2 = std::tan(31.415926f / fConst0);
		fConst3 = mydsp_faustpower2_f(fConst2);
		fConst4 = 1.0f / fConst2;
		fConst5 = (fConst4 + 1.4142135f) / fConst2 + 1.0f;
		fConst6 = 1.0f / (fConst3 * fConst5);
		fConst7 = 1.0f / fConst5;
		fConst8 = (fConst4 + -1.4142135f) / fConst2 + 1.0f;
		fConst9 = 2.0f * (1.0f - 1.0f / fConst3);
		fConst10 = 0.002f * fConst0;
		fConst11 = std::pow(0.001f, 0.04786944f / fConst0);
		fConst12 = 2.0f * std::cos(857.59827f / fConst0) * fConst11;
		fConst13 = mydsp_faustpower2_f(fConst11);
		fConst14 = std::pow(0.001f, 0.04793709f / fConst0);
		fConst15 = 2.0f * std::cos(860.7461f / fConst0) * fConst14;
		fConst16 = mydsp_faustpower2_f(fConst14);
		fConst17 = std::pow(0.001f, 0.06907072f / fConst0);
		fConst18 = 2.0f * std::cos(1627.081f / fConst0) * fConst17;
		fConst19 = mydsp_faustpower2_f(fConst17);
		fConst20 = std::pow(0.001f, 0.069393076f / fConst0);
		fConst21 = 2.0f * std::cos(1636.2609f / fConst0) * fConst20;
		fConst22 = mydsp_faustpower2_f(fConst20);
		fConst23 = std::pow(0.001f, 0.08344382f / fConst0);
		fConst24 = 2.0f * std::cos(1988.5591f / fConst0) * fConst23;
		fConst25 = mydsp_faustpower2_f(fConst23);
		fConst26 = std::pow(0.001f, 0.08399014f / fConst0);
		fConst27 = 2.0f * std::cos(2000.6354f / fConst0) * fConst26;
		fConst28 = mydsp_faustpower2_f(fConst26);
		fConst29 = std::pow(0.001f, 0.10981027f / fConst0);
		fConst30 = 2.0f * std::cos(2474.645f / fConst0) * fConst29;
		fConst31 = mydsp_faustpower2_f(fConst29);
		fConst32 = std::pow(0.001f, 0.10984986f / fConst0);
		fConst33 = 2.0f * std::cos(2475.2546f / fConst0) * fConst32;
		fConst34 = mydsp_faustpower2_f(fConst32);
		fConst35 = std::pow(0.001f, 0.1389059f / fConst0);
		fConst36 = 2.0f * std::cos(2856.8198f / fConst0) * fConst35;
		fConst37 = mydsp_faustpower2_f(fConst35);
		fConst38 = std::pow(0.001f, 0.14631474f / fConst0);
		fConst39 = 2.0f * std::cos(2937.3452f / fConst0) * fConst38;
		fConst40 = mydsp_faustpower2_f(fConst38);
		fConst41 = std::pow(0.001f, 0.17023267f / fConst0);
		fConst42 = 2.0f * std::cos(3164.1743f / fConst0) * fConst41;
		fConst43 = mydsp_faustpower2_f(fConst41);
		fConst44 = std::pow(0.001f, 0.17026415f / fConst0);
		fConst45 = 2.0f * std::cos(3164.4446f / fConst0) * fConst44;
		fConst46 = mydsp_faustpower2_f(fConst44);
		fConst47 = std::pow(0.001f, 0.19152485f / fConst0);
		fConst48 = 2.0f * std::cos(3332.9785f / fConst0) * fConst47;
		fConst49 = mydsp_faustpower2_f(fConst47);
		fConst50 = std::pow(0.001f, 0.19202785f / fConst0);
		fConst51 = 2.0f * std::cos(3336.6604f / fConst0) * fConst50;
		fConst52 = mydsp_faustpower2_f(fConst50);
		fConst53 = std::pow(0.001f, 0.20099394f / fConst0);
		fConst54 = 2.0f * std::cos(3400.2085f / fConst0) * fConst53;
		fConst55 = mydsp_faustpower2_f(fConst53);
		fConst56 = std::pow(0.001f, 0.20563126f / fConst0);
		fConst57 = 2.0f * std::cos(3431.6118f / fConst0) * fConst56;
		fConst58 = mydsp_faustpower2_f(fConst56);
		fConst59 = std::pow(0.001f, 0.23918521f / fConst0);
		fConst60 = 2.0f * std::cos(3633.786f / fConst0) * fConst59;
		fConst61 = mydsp_faustpower2_f(fConst59);
		fConst62 = std::pow(0.001f, 0.24095473f / fConst0);
		fConst63 = 2.0f * std::cos(3643.3867f / fConst0) * fConst62;
		fConst64 = mydsp_faustpower2_f(fConst62);
		fConst65 = std::pow(0.001f, 0.36472484f / fConst0);
		fConst66 = 2.0f * std::cos(4147.0654f / fConst0) * fConst65;
		fConst67 = mydsp_faustpower2_f(fConst65);
		fConst68 = std::pow(0.001f, 0.48289227f / fConst0);
		fConst69 = 2.0f * std::cos(4450.6313f / fConst0) * fConst68;
		fConst70 = mydsp_faustpower2_f(fConst68);
		fConst71 = std::pow(0.001f, 0.5090106f / fConst0);
		fConst72 = 2.0f * std::cos(4504.51f / fConst0) * fConst71;
		fConst73 = mydsp_faustpower2_f(fConst71);
		fConst74 = std::pow(0.001f, 0.51000553f / fConst0);
		fConst75 = 2.0f * std::cos(4506.489f / fConst0) * fConst74;
		fConst76 = mydsp_faustpower2_f(fConst74);
		fConst77 = std::pow(0.001f, 0.7513248f / fConst0);
		fConst78 = 2.0f * std::cos(4874.74f / fConst0) * fConst77;
		fConst79 = mydsp_faustpower2_f(fConst77);
		fConst80 = std::pow(0.001f, 0.75252944f / fConst0);
		fConst81 = 2.0f * std::cos(4876.1665f / fConst0) * fConst80;
		fConst82 = mydsp_faustpower2_f(fConst80);
		fConst83 = std::pow(0.001f, 0.7926267f / fConst0);
		fConst84 = 2.0f * std::cos(4921.9707f / fConst0) * fConst83;
		fConst85 = mydsp_faustpower2_f(fConst83);
		fConst86 = std::pow(0.001f, 0.79324186f / fConst0);
		fConst87 = 2.0f * std::cos(4922.6494f / fConst0) * fConst86;
		fConst88 = mydsp_faustpower2_f(fConst86);
		fConst89 = std::pow(0.001f, 0.8246036f / fConst0);
		fConst90 = 2.0f * std::cos(4956.34f / fConst0) * fConst89;
		fConst91 = mydsp_faustpower2_f(fConst89);
		fConst92 = std::pow(0.001f, 0.8284385f / fConst0);
		fConst93 = 2.0f * std::cos(4960.3423f / fConst0) * fConst92;
		fConst94 = mydsp_faustpower2_f(fConst92);
		fConst95 = std::pow(0.001f, 0.8978094f / fConst0);
		fConst96 = 2.0f * std::cos(5028.735f / fConst0) * fConst95;
		fConst97 = mydsp_faustpower2_f(fConst95);
		fConst98 = std::pow(0.001f, 0.9423167f / fConst0);
		fConst99 = 2.0f * std::cos(5069.0103f / fConst0) * fConst98;
		fConst100 = mydsp_faustpower2_f(fConst98);
		fConst101 = std::pow(0.001f, 1.6943034f / fConst0);
		fConst102 = 2.0f * std::cos(5509.0215f / fConst0) * fConst101;
		fConst103 = mydsp_faustpower2_f(fConst101);
		fConst104 = std::pow(0.001f, 1.7524446f / fConst0);
		fConst105 = 2.0f * std::cos(5531.804f / fConst0) * fConst104;
		fConst106 = mydsp_faustpower2_f(fConst104);
		fConst107 = std::pow(0.001f, 1.8703421f / fConst0);
		fConst108 = 2.0f * std::cos(5575.0513f / fConst0) * fConst107;
		fConst109 = mydsp_faustpower2_f(fConst107);
		fConst110 = std::pow(0.001f, 1.8869846f / fConst0);
		fConst111 = 2.0f * std::cos(5580.8633f / fConst0) * fConst110;
		fConst112 = mydsp_faustpower2_f(fConst110);
		fConst113 = std::pow(0.001f, 2.5157607f / fConst0);
		fConst114 = 2.0f * std::cos(5760.5186f / fConst0) * fConst113;
		fConst115 = mydsp_faustpower2_f(fConst113);
		fConst116 = std::pow(0.001f, 2.5942633f / fConst0);
		fConst117 = 2.0f * std::cos(5778.715f / fConst0) * fConst116;
		fConst118 = mydsp_faustpower2_f(fConst116);
		fConst119 = std::pow(0.001f, 3.162622f / fConst0);
		fConst120 = 2.0f * std::cos(5891.655f / fConst0) * fConst119;
		fConst121 = mydsp_faustpower2_f(fConst119);
		fConst122 = std::pow(0.001f, 5.6980042f / fConst0);
		fConst123 = 2.0f * std::cos(6186.462f / fConst0) * fConst122;
		fConst124 = mydsp_faustpower2_f(fConst122);
		fConst125 = std::pow(0.001f, 19.415625f / fConst0);
		fConst126 = 2.0f * std::cos(6642.5835f / fConst0) * fConst125;
		fConst127 = mydsp_faustpower2_f(fConst125);
		fConst128 = std::pow(0.001f, 19.930838f / fConst0);
		fConst129 = 2.0f * std::cos(6650.4375f / fConst0) * fConst128;
		fConst130 = mydsp_faustpower2_f(fConst128);
		fConst131 = std::pow(0.001f, 23.195957f / fConst0);
		fConst132 = 2.0f * std::cos(6694.6084f / fConst0) * fConst131;
		fConst133 = mydsp_faustpower2_f(fConst131);
		fConst134 = std::pow(0.001f, 34.49272f / fConst0);
		fConst135 = 2.0f * std::cos(6800.103f / fConst0) * fConst134;
		fConst136 = mydsp_faustpower2_f(fConst134);
		fConst137 = std::pow(0.001f, 35.98077f / fConst0);
		fConst138 = 2.0f * std::cos(6810.533f / fConst0) * fConst137;
		fConst139 = mydsp_faustpower2_f(fConst137);
		fConst140 = std::pow(0.001f, 38.50857f / fConst0);
		fConst141 = 2.0f * std::cos(6826.995f / fConst0) * fConst140;
		fConst142 = mydsp_faustpower2_f(fConst140);
		fConst143 = std::pow(0.001f, 38.731476f / fConst0);
		fConst144 = 2.0f * std::cos(6828.3774f / fConst0) * fConst143;
		fConst145 = mydsp_faustpower2_f(fConst143);
		fConst146 = std::pow(0.001f, 72.23277f / fConst0);
		fConst147 = 2.0f * std::cos(6963.026f / fConst0) * fConst146;
		fConst148 = mydsp_faustpower2_f(fConst146);
		fConst149 = std::pow(0.001f, 94.562f / fConst0);
		fConst150 = 2.0f * std::cos(7013.103f / fConst0) * fConst149;
		fConst151 = mydsp_faustpower2_f(fConst149);
		fConst152 = std::pow(0.001f, 410.4479f / fConst0);
		fConst153 = 2.0f * std::cos(7219.38f / fConst0) * fConst152;
		fConst154 = mydsp_faustpower2_f(fConst152);
		fConst155 = std::pow(0.001f, 449.17822f / fConst0);
		fConst156 = 2.0f * std::cos(7229.056f / fConst0) * fConst155;
		fConst157 = mydsp_faustpower2_f(fConst155);
		fConst158 = std::pow(0.001f, 18178858.0f / fConst0);
		fConst159 = 2.0f * std::cos(7536.932f / fConst0) * fConst158;
		fConst160 = mydsp_faustpower2_f(fConst158);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(6.5e+03f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec3[l0] = 0;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec4[l4] = 0;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec6[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec8[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec11[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec13[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec14[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec15[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec17[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec18[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec19[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec20[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec21[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec22[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec23[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec24[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec25[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec26[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec27[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec28[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec29[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec30[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec31[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec32[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec33[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec34[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec35[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec36[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec37[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec38[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec39[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec40[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec41[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 3; l43 = l43 + 1) {
			fRec42[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec43[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec44[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec45[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec46[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec47[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec48[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec49[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec50[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec51[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec52[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec53[l54] = 0.0f;
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
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("russianBell");
		ui_interface->declare(&fEntry0, "0", "");
		ui_interface->addNumEntry("strikePosition", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->addHorizontalSlider("strikeCutOff", &fHslider1, FAUSTFLOAT(6.5e+03f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->addHorizontalSlider("strikeSharpness", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.01f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fButton0, "4", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::tan(fConst1 * float(fHslider1));
		float fSlow1 = 1.0f / fSlow0;
		float fSlow2 = (fSlow1 + 1.4142135f) / fSlow0 + 1.0f;
		float fSlow3 = float(fHslider0) / fSlow2;
		float fSlow4 = 1.0f / fSlow2;
		float fSlow5 = (fSlow1 + -1.4142135f) / fSlow0 + 1.0f;
		float fSlow6 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow0));
		float fSlow7 = 1.0f / std::max<float>(1.0f, fConst10 * float(fHslider2));
		float fSlow8 = float(fButton0);
		int iSlow9 = 50 * int(float(fEntry0));
		float fSlow10 = ftbl0mydspSIG0[iSlow9];
		float fSlow11 = ftbl0mydspSIG0[iSlow9 + 1];
		float fSlow12 = ftbl0mydspSIG0[iSlow9 + 2];
		float fSlow13 = ftbl0mydspSIG0[iSlow9 + 3];
		float fSlow14 = ftbl0mydspSIG0[iSlow9 + 4];
		float fSlow15 = ftbl0mydspSIG0[iSlow9 + 5];
		float fSlow16 = ftbl0mydspSIG0[iSlow9 + 6];
		float fSlow17 = ftbl0mydspSIG0[iSlow9 + 7];
		float fSlow18 = ftbl0mydspSIG0[iSlow9 + 8];
		float fSlow19 = ftbl0mydspSIG0[iSlow9 + 9];
		float fSlow20 = ftbl0mydspSIG0[iSlow9 + 10];
		float fSlow21 = ftbl0mydspSIG0[iSlow9 + 11];
		float fSlow22 = ftbl0mydspSIG0[iSlow9 + 12];
		float fSlow23 = ftbl0mydspSIG0[iSlow9 + 13];
		float fSlow24 = ftbl0mydspSIG0[iSlow9 + 14];
		float fSlow25 = ftbl0mydspSIG0[iSlow9 + 15];
		float fSlow26 = ftbl0mydspSIG0[iSlow9 + 16];
		float fSlow27 = ftbl0mydspSIG0[iSlow9 + 17];
		float fSlow28 = ftbl0mydspSIG0[iSlow9 + 18];
		float fSlow29 = ftbl0mydspSIG0[iSlow9 + 19];
		float fSlow30 = ftbl0mydspSIG0[iSlow9 + 20];
		float fSlow31 = ftbl0mydspSIG0[iSlow9 + 21];
		float fSlow32 = ftbl0mydspSIG0[iSlow9 + 22];
		float fSlow33 = ftbl0mydspSIG0[iSlow9 + 23];
		float fSlow34 = ftbl0mydspSIG0[iSlow9 + 24];
		float fSlow35 = ftbl0mydspSIG0[iSlow9 + 25];
		float fSlow36 = ftbl0mydspSIG0[iSlow9 + 26];
		float fSlow37 = ftbl0mydspSIG0[iSlow9 + 27];
		float fSlow38 = ftbl0mydspSIG0[iSlow9 + 28];
		float fSlow39 = ftbl0mydspSIG0[iSlow9 + 29];
		float fSlow40 = ftbl0mydspSIG0[iSlow9 + 30];
		float fSlow41 = ftbl0mydspSIG0[iSlow9 + 31];
		float fSlow42 = ftbl0mydspSIG0[iSlow9 + 32];
		float fSlow43 = ftbl0mydspSIG0[iSlow9 + 33];
		float fSlow44 = ftbl0mydspSIG0[iSlow9 + 34];
		float fSlow45 = ftbl0mydspSIG0[iSlow9 + 35];
		float fSlow46 = ftbl0mydspSIG0[iSlow9 + 36];
		float fSlow47 = ftbl0mydspSIG0[iSlow9 + 37];
		float fSlow48 = ftbl0mydspSIG0[iSlow9 + 38];
		float fSlow49 = ftbl0mydspSIG0[iSlow9 + 39];
		float fSlow50 = ftbl0mydspSIG0[iSlow9 + 40];
		float fSlow51 = ftbl0mydspSIG0[iSlow9 + 41];
		float fSlow52 = ftbl0mydspSIG0[iSlow9 + 42];
		float fSlow53 = ftbl0mydspSIG0[iSlow9 + 43];
		float fSlow54 = ftbl0mydspSIG0[iSlow9 + 44];
		float fSlow55 = ftbl0mydspSIG0[iSlow9 + 45];
		float fSlow56 = ftbl0mydspSIG0[iSlow9 + 46];
		float fSlow57 = ftbl0mydspSIG0[iSlow9 + 47];
		float fSlow58 = ftbl0mydspSIG0[iSlow9 + 48];
		float fSlow59 = ftbl0mydspSIG0[iSlow9 + 49];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec3[0] = 1103515245 * iRec3[1] + 12345;
			fRec2[0] = 4.656613e-10f * float(iRec3[0]) - fConst7 * (fConst8 * fRec2[2] + fConst9 * fRec2[1]);
			fRec1[0] = fConst6 * (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) - fSlow4 * (fSlow5 * fRec1[2] + fSlow6 * fRec1[1]);
			fVec0[0] = fSlow8;
			iRec4[0] = (iRec4[1] + (iRec4[1] > 0)) * (fSlow8 <= fVec0[1]) + (fSlow8 > fVec0[1]);
			float fTemp0 = fSlow7 * float(iRec4[0]);
			float fTemp1 = fSlow3 * (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) * std::max<float>(0.0f, std::min<float>(fTemp0, 2.0f - fTemp0));
			fRec0[0] = fTemp1 + fConst12 * fRec0[1] - fConst13 * fRec0[2];
			fRec5[0] = fTemp1 + fConst15 * fRec5[1] - fConst16 * fRec5[2];
			fRec6[0] = fTemp1 + fConst18 * fRec6[1] - fConst19 * fRec6[2];
			fRec7[0] = fTemp1 + fConst21 * fRec7[1] - fConst22 * fRec7[2];
			fRec8[0] = fTemp1 + fConst24 * fRec8[1] - fConst25 * fRec8[2];
			fRec9[0] = fTemp1 + fConst27 * fRec9[1] - fConst28 * fRec9[2];
			fRec10[0] = fTemp1 + fConst30 * fRec10[1] - fConst31 * fRec10[2];
			fRec11[0] = fTemp1 + fConst33 * fRec11[1] - fConst34 * fRec11[2];
			fRec12[0] = fTemp1 + fConst36 * fRec12[1] - fConst37 * fRec12[2];
			fRec13[0] = fTemp1 + fConst39 * fRec13[1] - fConst40 * fRec13[2];
			fRec14[0] = fTemp1 + fConst42 * fRec14[1] - fConst43 * fRec14[2];
			fRec15[0] = fTemp1 + fConst45 * fRec15[1] - fConst46 * fRec15[2];
			fRec16[0] = fTemp1 + fConst48 * fRec16[1] - fConst49 * fRec16[2];
			fRec17[0] = fTemp1 + fConst51 * fRec17[1] - fConst52 * fRec17[2];
			fRec18[0] = fTemp1 + fConst54 * fRec18[1] - fConst55 * fRec18[2];
			fRec19[0] = fTemp1 + fConst57 * fRec19[1] - fConst58 * fRec19[2];
			fRec20[0] = fTemp1 + fConst60 * fRec20[1] - fConst61 * fRec20[2];
			fRec21[0] = fTemp1 + fConst63 * fRec21[1] - fConst64 * fRec21[2];
			fRec22[0] = fTemp1 + fConst66 * fRec22[1] - fConst67 * fRec22[2];
			fRec23[0] = fTemp1 + fConst69 * fRec23[1] - fConst70 * fRec23[2];
			fRec24[0] = fTemp1 + fConst72 * fRec24[1] - fConst73 * fRec24[2];
			fRec25[0] = fTemp1 + fConst75 * fRec25[1] - fConst76 * fRec25[2];
			fRec26[0] = fTemp1 + fConst78 * fRec26[1] - fConst79 * fRec26[2];
			fRec27[0] = fTemp1 + fConst81 * fRec27[1] - fConst82 * fRec27[2];
			fRec28[0] = fTemp1 + fConst84 * fRec28[1] - fConst85 * fRec28[2];
			fRec29[0] = fTemp1 + fConst87 * fRec29[1] - fConst88 * fRec29[2];
			fRec30[0] = fTemp1 + fConst90 * fRec30[1] - fConst91 * fRec30[2];
			fRec31[0] = fTemp1 + fConst93 * fRec31[1] - fConst94 * fRec31[2];
			fRec32[0] = fTemp1 + fConst96 * fRec32[1] - fConst97 * fRec32[2];
			fRec33[0] = fTemp1 + fConst99 * fRec33[1] - fConst100 * fRec33[2];
			fRec34[0] = fTemp1 + fConst102 * fRec34[1] - fConst103 * fRec34[2];
			fRec35[0] = fTemp1 + fConst105 * fRec35[1] - fConst106 * fRec35[2];
			fRec36[0] = fTemp1 + fConst108 * fRec36[1] - fConst109 * fRec36[2];
			fRec37[0] = fTemp1 + fConst111 * fRec37[1] - fConst112 * fRec37[2];
			fRec38[0] = fTemp1 + fConst114 * fRec38[1] - fConst115 * fRec38[2];
			fRec39[0] = fTemp1 + fConst117 * fRec39[1] - fConst118 * fRec39[2];
			fRec40[0] = fTemp1 + fConst120 * fRec40[1] - fConst121 * fRec40[2];
			fRec41[0] = fTemp1 + fConst123 * fRec41[1] - fConst124 * fRec41[2];
			fRec42[0] = fTemp1 + fConst126 * fRec42[1] - fConst127 * fRec42[2];
			fRec43[0] = fTemp1 + fConst129 * fRec43[1] - fConst130 * fRec43[2];
			fRec44[0] = fTemp1 + fConst132 * fRec44[1] - fConst133 * fRec44[2];
			fRec45[0] = fTemp1 + fConst135 * fRec45[1] - fConst136 * fRec45[2];
			fRec46[0] = fTemp1 + fConst138 * fRec46[1] - fConst139 * fRec46[2];
			fRec47[0] = fTemp1 + fConst141 * fRec47[1] - fConst142 * fRec47[2];
			fRec48[0] = fTemp1 + fConst144 * fRec48[1] - fConst145 * fRec48[2];
			fRec49[0] = fTemp1 + fConst147 * fRec49[1] - fConst148 * fRec49[2];
			fRec50[0] = fTemp1 + fConst150 * fRec50[1] - fConst151 * fRec50[2];
			fRec51[0] = fTemp1 + fConst153 * fRec51[1] - fConst154 * fRec51[2];
			fRec52[0] = fTemp1 + fConst156 * fRec52[1] - fConst157 * fRec52[2];
			fRec53[0] = fTemp1 + fConst159 * fRec53[1] - fConst160 * fRec53[2];
			float fTemp2 = 0.02f * ((fRec0[0] - fRec0[2]) * fSlow10 + (fRec5[0] - fRec5[2]) * fSlow11 + (fRec6[0] - fRec6[2]) * fSlow12 + (fRec7[0] - fRec7[2]) * fSlow13 + (fRec8[0] - fRec8[2]) * fSlow14 + (fRec9[0] - fRec9[2]) * fSlow15 + (fRec10[0] - fRec10[2]) * fSlow16 + (fRec11[0] - fRec11[2]) * fSlow17 + (fRec12[0] - fRec12[2]) * fSlow18 + (fRec13[0] - fRec13[2]) * fSlow19 + (fRec14[0] - fRec14[2]) * fSlow20 + (fRec15[0] - fRec15[2]) * fSlow21 + (fRec16[0] - fRec16[2]) * fSlow22 + (fRec17[0] - fRec17[2]) * fSlow23 + (fRec18[0] - fRec18[2]) * fSlow24 + (fRec19[0] - fRec19[2]) * fSlow25 + (fRec20[0] - fRec20[2]) * fSlow26 + (fRec21[0] - fRec21[2]) * fSlow27 + (fRec22[0] - fRec22[2]) * fSlow28 + (fRec23[0] - fRec23[2]) * fSlow29 + (fRec24[0] - fRec24[2]) * fSlow30 + (fRec25[0] - fRec25[2]) * fSlow31 + (fRec26[0] - fRec26[2]) * fSlow32 + (fRec27[0] - fRec27[2]) * fSlow33 + (fRec28[0] - fRec28[2]) * fSlow34 + (fRec29[0] - fRec29[2]) * fSlow35 + (fRec30[0] - fRec30[2]) * fSlow36 + (fRec31[0] - fRec31[2]) * fSlow37 + (fRec32[0] - fRec32[2]) * fSlow38 + (fRec33[0] - fRec33[2]) * fSlow39 + (fRec34[0] - fRec34[2]) * fSlow40 + (fRec35[0] - fRec35[2]) * fSlow41 + (fRec36[0] - fRec36[2]) * fSlow42 + (fRec37[0] - fRec37[2]) * fSlow43 + (fRec38[0] - fRec38[2]) * fSlow44 + (fRec39[0] - fRec39[2]) * fSlow45 + (fRec40[0] - fRec40[2]) * fSlow46 + (fRec41[0] - fRec41[2]) * fSlow47 + (fRec42[0] - fRec42[2]) * fSlow48 + (fRec43[0] - fRec43[2]) * fSlow49 + (fRec44[0] - fRec44[2]) * fSlow50 + (fRec45[0] - fRec45[2]) * fSlow51 + (fRec46[0] - fRec46[2]) * fSlow52 + (fRec47[0] - fRec47[2]) * fSlow53 + (fRec48[0] - fRec48[2]) * fSlow54 + (fRec49[0] - fRec49[2]) * fSlow55 + (fRec50[0] - fRec50[2]) * fSlow56 + (fRec51[0] - fRec51[2]) * fSlow57 + (fRec52[0] - fRec52[2]) * fSlow58 + (fRec53[0] - fRec53[2]) * fSlow59);
			output0[i0] = FAUSTFLOAT(fTemp2);
			output1[i0] = FAUSTFLOAT(fTemp2);
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			iRec4[1] = iRec4[0];
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

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

static const clap_plugin_descriptor_t gain_desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "org.faust.gain",
    .name = "Faust Gain",
    .vendor = "faust",
    .url = "https://faust.grame.fr",
    .manual_url = "",
    .support_url = "",
    .version = "1.0.0",
    .description = "Simple gain plugin generated from Faust",
    .features = (const char*[]) { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr }
};

class GainPlugin final : public Base {
public:
    int fNumInputs = 0;
    int fNumOutputs = 0;
    mydsp fDSP;
    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    bool fHasFlushed = false;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
    : Base(desc, host) {}

    bool init() noexcept override {
        fDSP.buildUserInterface(&fUI);
        fParamAddresses.clear();
        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            auto shortname = fUI.getParamShortname(i);
            fParamAddresses.push_back(shortname);
            float actual = fUI.getParamValue(shortname);
            fExpectedValues.push_back(actual);
        }
        return true;
    }

    bool startProcessing() noexcept override {
        return Base::startProcessing(); //set status to processing
    }

    void stopProcessing() noexcept override {
        Base::stopProcessing(); //resets status to activated
    }

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP.init(sampleRate);
        fNumInputs = fDSP.getNumInputs();
        fNumOutputs = fDSP.getNumOutputs();
        std::cerr << "[activate] Sample rate: " << sampleRate << std::endl;
        std::cerr << "[activate] Input channels: " << fNumInputs << ", Output channels: " << fNumOutputs << std::endl;
        return true;
    }


    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) {
            return false;
        }

        if (hdr->type != CLAP_EVENT_PARAM_VALUE) return false;

        const auto* evParam = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        if (evParam->param_id >= fParamAddresses.size()) return false;

        GuardedScope guard(fUI, "applyParamEventIfValid");
        fUI.setParamValue(fParamAddresses[evParam->param_id], evParam->value);
        fExpectedValues[evParam->param_id] = evParam->value;

        return true;
    }



    clap_process_status process(const clap_process_t* process) noexcept override {
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        const auto& inBuffer  = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];

        //skip processing gracefully if no audio channels are connected
        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        if (inBuffer.channel_count < fNumInputs ||
            outBuffer.channel_count < fNumOutputs) {
            std::cerr << "[error] Channel count mismatch: in="
                      << inBuffer.channel_count << ", expected="
                      << fNumInputs << " / out=" << outBuffer.channel_count
                      << ", expected=" << fNumOutputs << "\n";
            return CLAP_PROCESS_ERROR;
            }

        //apply param events
        if (auto events = process->in_events) {
            for (uint32_t i = 0, N = events->size(events); i < N; ++i) {
                applyParamEventIfValid(events->get(events, i));
            }
        }

        //prepare pointers
        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        //process audio
        GuardedScope guard(fUI, "full-buffer");
        fDSP.compute(process->frames_count, inputs, outputs);

        return CLAP_PROCESS_CONTINUE;
    }


    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override {
        return 1; //still 1 port, but could change if faust generates multiple ports
    }
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? fNumInputs : fNumOutputs;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type = nullptr;
        return true;
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= fParamAddresses.size()) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        const char* addr = fParamAddresses[index].c_str();
        if (addr[0] == '/') addr += 1;
        snprintf(info->name, sizeof(info->name), "%s", addr);
        info->min_value = 0.f;
        info->max_value = 1.f;
        info->default_value = 0.5f;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (id >= fExpectedValues.size()) return false;
        *value = fExpectedValues[id];
        return true;
    }

    bool paramsTextToValue(clap_id, const char*, double*) noexcept override { return false; }
    bool paramsValueToText(clap_id, double, char*, uint32_t) noexcept override { return false; }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;

        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!applyParamEventIfValid(hdr)) {
            }
        }
    }
    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        return GainPlugin::create(host);
    }
    return nullptr;
}
static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};
static bool entry_init(const char* path) { return true; }
static void entry_deinit() {}

extern "C" {
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}

#endif
