/* ------------------------------------------------------------
author: "CICM"
copyright: "(c)CICM 2013"
license: "BSD"
name: "fourSourcesToOcto"
version: "1.0"
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

static float mydsp_faustpower2_f(float value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	FAUSTFLOAT fHslider4;
	float fRec4[2];
	FAUSTFLOAT fHslider5;
	float fRec5[2];
	FAUSTFLOAT fHslider6;
	float fRec6[2];
	FAUSTFLOAT fHslider7;
	float fRec7[2];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "CICM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("copyright", "(c)CICM 2013");
		m->declare("filename", "fourSourcesToOcto.dsp");
		m->declare("hoa.lib/author", "Pierre Guillot");
		m->declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8, 2019 Wargreen, 2022 Bonardi, Goutmann");
		m->declare("hoa.lib/name", "High Order Ambisonics library");
		m->declare("hoa.lib/version", "1.4.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "fourSourcesToOcto");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 4;
	}
	virtual int getNumOutputs() {
		return 8;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::exp(-(5e+01f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)))));
		fConst1 = 1.0f - fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(1.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
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
		ui_interface->openVerticalBox("fourSourcesToOcto");
		ui_interface->addHorizontalSlider("Angle1", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6.2831855f), FAUSTFLOAT(6.2831855f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Angle2", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6.2831855f), FAUSTFLOAT(6.2831855f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Angle3", &fHslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6.2831855f), FAUSTFLOAT(6.2831855f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Angle4", &fHslider7, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6.2831855f), FAUSTFLOAT(6.2831855f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Radius1", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Radius2", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Radius3", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Radius4", &fHslider3, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1);
		float fSlow2 = fConst1 * float(fHslider2);
		float fSlow3 = fConst1 * float(fHslider3);
		float fSlow4 = fConst1 * float(fHslider4);
		float fSlow5 = fConst1 * float(fHslider5);
		float fSlow6 = fConst1 * float(fHslider6);
		float fSlow7 = fConst1 * float(fHslider7);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst0 * fRec0[1];
			float fTemp0 = fRec0[0] * float(fRec0[0] < 1.0f) + float(fRec0[0] >= 1.0f);
			float fTemp1 = float(input0[i0]) * (1.3862944f * (1.0f - fTemp0) + 1.0f);
			float fTemp2 = float(fRec0[0] <= 1.0f) + mydsp_faustpower2_f(fRec0[0]) * float(fRec0[0] > 1.0f);
			fRec1[0] = fSlow1 + fConst0 * fRec1[1];
			float fTemp3 = fRec1[0] * float(fRec1[0] < 1.0f) + float(fRec1[0] >= 1.0f);
			float fTemp4 = float(input1[i0]) * (1.3862944f * (1.0f - fTemp3) + 1.0f);
			float fTemp5 = float(fRec1[0] <= 1.0f) + mydsp_faustpower2_f(fRec1[0]) * float(fRec1[0] > 1.0f);
			fRec2[0] = fSlow2 + fConst0 * fRec2[1];
			float fTemp6 = fRec2[0] * float(fRec2[0] < 1.0f) + float(fRec2[0] >= 1.0f);
			float fTemp7 = float(input2[i0]) * (1.3862944f * (1.0f - fTemp6) + 1.0f);
			float fTemp8 = float(fRec2[0] <= 1.0f) + mydsp_faustpower2_f(fRec2[0]) * float(fRec2[0] > 1.0f);
			fRec3[0] = fSlow3 + fConst0 * fRec3[1];
			float fTemp9 = fRec3[0] * float(fRec3[0] < 1.0f) + float(fRec3[0] >= 1.0f);
			float fTemp10 = float(input3[i0]) * (1.3862944f * (1.0f - fTemp9) + 1.0f);
			float fTemp11 = float(fRec3[0] <= 1.0f) + mydsp_faustpower2_f(fRec3[0]) * float(fRec3[0] > 1.0f);
			float fTemp12 = 0.125f * (fTemp1 / fTemp2 + fTemp4 / fTemp5 + fTemp7 / fTemp8 + fTemp10 / fTemp11);
			float fTemp13 = 2.0f * fTemp0;
			float fTemp14 = 2.0f * fTemp0 * float(fTemp13 > 0.0f) * float(fTemp13 <= 1.0f) + float(fTemp13 > 1.0f);
			fRec4[0] = fSlow4 + fConst0 * fRec4[1];
			float fTemp15 = 2.0f * fTemp3;
			float fTemp16 = 2.0f * fTemp3 * float(fTemp15 > 0.0f) * float(fTemp15 <= 1.0f) + float(fTemp15 > 1.0f);
			fRec5[0] = fSlow5 + fConst0 * fRec5[1];
			float fTemp17 = 2.0f * fTemp6;
			float fTemp18 = 2.0f * fTemp6 * float(fTemp17 > 0.0f) * float(fTemp17 <= 1.0f) + float(fTemp17 > 1.0f);
			fRec6[0] = fSlow6 + fConst0 * fRec6[1];
			float fTemp19 = 2.0f * fTemp9;
			float fTemp20 = 2.0f * fTemp9 * float(fTemp19 > 0.0f) * float(fTemp19 <= 1.0f) + float(fTemp19 > 1.0f);
			fRec7[0] = fSlow7 + fConst0 * fRec7[1];
			float fTemp21 = fTemp1 * fTemp14 * std::cos(fRec4[0]) / fTemp2 + fTemp4 * fTemp16 * std::cos(fRec5[0]) / fTemp5 + fTemp7 * fTemp18 * std::cos(fRec6[0]) / fTemp8 + fTemp10 * fTemp20 * std::cos(fRec7[0]) / fTemp11;
			float fTemp22 = 0.1875f * fTemp21;
			float fTemp23 = 2.0f * fRec4[0];
			float fTemp24 = 1.3862944f * fTemp0;
			float fTemp25 = fTemp24 + -0.6931472f;
			float fTemp26 = 2.4663033f * fTemp25;
			float fTemp27 = 2.4663033f * fTemp25 * float(fTemp26 > 0.0f) * float(fTemp26 <= 1.0f) + float(fTemp26 > 1.0f);
			float fTemp28 = 2.0f * fRec5[0];
			float fTemp29 = 1.3862944f * fTemp3;
			float fTemp30 = fTemp29 + -0.6931472f;
			float fTemp31 = 2.4663033f * fTemp30;
			float fTemp32 = 2.4663033f * fTemp30 * float(fTemp31 > 0.0f) * float(fTemp31 <= 1.0f) + float(fTemp31 > 1.0f);
			float fTemp33 = 2.0f * fRec6[0];
			float fTemp34 = 1.3862944f * fTemp6;
			float fTemp35 = fTemp34 + -0.6931472f;
			float fTemp36 = 2.4663033f * fTemp35;
			float fTemp37 = 2.4663033f * fTemp35 * float(fTemp36 > 0.0f) * float(fTemp36 <= 1.0f) + float(fTemp36 > 1.0f);
			float fTemp38 = 2.0f * fRec7[0];
			float fTemp39 = 1.3862944f * fTemp9;
			float fTemp40 = fTemp39 + -0.6931472f;
			float fTemp41 = 2.4663033f * fTemp40;
			float fTemp42 = 2.4663033f * fTemp40 * float(fTemp41 > 0.0f) * float(fTemp41 <= 1.0f) + float(fTemp41 > 1.0f);
			float fTemp43 = 0.075f * (fTemp1 * std::cos(fTemp23) * fTemp27 / fTemp2 + fTemp4 * std::cos(fTemp28) * fTemp32 / fTemp5 + fTemp7 * std::cos(fTemp33) * fTemp37 / fTemp8 + fTemp10 * std::cos(fTemp38) * fTemp42 / fTemp11);
			float fTemp44 = 3.0f * fRec4[0];
			float fTemp45 = fTemp24 + -1.0986123f;
			float fTemp46 = 3.4760594f * fTemp45;
			float fTemp47 = 3.4760594f * fTemp45 * float(fTemp46 > 0.0f) * float(fTemp46 <= 1.0f) + float(fTemp46 > 1.0f);
			float fTemp48 = 3.0f * fRec5[0];
			float fTemp49 = fTemp29 + -1.0986123f;
			float fTemp50 = 3.4760594f * fTemp49;
			float fTemp51 = 3.4760594f * fTemp49 * float(fTemp50 > 0.0f) * float(fTemp50 <= 1.0f) + float(fTemp50 > 1.0f);
			float fTemp52 = 3.0f * fRec6[0];
			float fTemp53 = fTemp34 + -1.0986123f;
			float fTemp54 = 3.4760594f * fTemp53;
			float fTemp55 = 3.4760594f * fTemp53 * float(fTemp54 > 0.0f) * float(fTemp54 <= 1.0f) + float(fTemp54 > 1.0f);
			float fTemp56 = 3.0f * fRec7[0];
			float fTemp57 = fTemp39 + -1.0986123f;
			float fTemp58 = 3.4760594f * fTemp57;
			float fTemp59 = 3.4760594f * fTemp57 * float(fTemp58 > 0.0f) * float(fTemp58 <= 1.0f) + float(fTemp58 > 1.0f);
			float fTemp60 = fTemp1 * std::cos(fTemp44) * fTemp47 / fTemp2 + fTemp4 * std::cos(fTemp48) * fTemp51 / fTemp5 + fTemp7 * std::cos(fTemp52) * fTemp55 / fTemp8 + fTemp10 * std::cos(fTemp56) * fTemp59 / fTemp11;
			float fTemp61 = 0.0125f * fTemp60;
			output0[i0] = FAUSTFLOAT(fTemp12 + fTemp22 + fTemp43 + fTemp61);
			float fTemp62 = fTemp1 * std::sin(fRec4[0]) * fTemp14 / fTemp2 + fTemp4 * std::sin(fRec5[0]) * fTemp16 / fTemp5 + fTemp7 * std::sin(fRec6[0]) * fTemp18 / fTemp8 + fTemp10 * std::sin(fRec7[0]) * fTemp20 / fTemp11;
			float fTemp63 = 0.13258252f * fTemp62;
			float fTemp64 = 0.13258252f * fTemp21;
			float fTemp65 = 0.075f * (fTemp1 * std::sin(fTemp23) * fTemp27 / fTemp2 + fTemp4 * std::sin(fTemp28) * fTemp32 / fTemp5 + fTemp7 * std::sin(fTemp33) * fTemp37 / fTemp8 + fTemp10 * std::sin(fTemp38) * fTemp42 / fTemp11);
			float fTemp66 = fTemp1 * std::sin(fTemp44) * fTemp47 / fTemp2 + fTemp4 * std::sin(fTemp48) * fTemp51 / fTemp5 + fTemp7 * std::sin(fTemp52) * fTemp55 / fTemp8 + fTemp10 * std::sin(fTemp56) * fTemp59 / fTemp11;
			output1[i0] = FAUSTFLOAT(fTemp12 + fTemp63 + fTemp64 + fTemp65 + 0.008838835f * fTemp66 - 0.008838835f * fTemp60);
			float fTemp67 = 0.1875f * fTemp62;
			float fTemp68 = 0.0125f * fTemp66;
			output2[i0] = FAUSTFLOAT(fTemp12 + fTemp67 - (fTemp43 + fTemp68));
			float fTemp69 = 0.13258252f * fTemp62;
			output3[i0] = FAUSTFLOAT(fTemp12 + fTemp69 + 0.008838835f * fTemp66 + 0.008838835f * fTemp60 - (fTemp65 + 0.13258252f * fTemp21));
			output4[i0] = FAUSTFLOAT(fTemp12 + fTemp43 - (fTemp22 + fTemp61));
			output5[i0] = FAUSTFLOAT(fTemp12 + fTemp65 + 0.008838835f * fTemp60 - (fTemp63 + fTemp64 + 0.008838835f * fTemp66));
			output6[i0] = FAUSTFLOAT(fTemp12 + fTemp68 - (fTemp43 + fTemp67));
			output7[i0] = FAUSTFLOAT(fTemp12 + 0.13258252f * fTemp21 - (fTemp65 + fTemp69 + 0.008838835f * fTemp66 + 0.008838835f * fTemp60));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
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
