/* ------------------------------------------------------------
author: "CICM"
copyright: "(c)CICM 2013"
license: "BSD"
name: "oneSourceToStereo"
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
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "CICM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("copyright", "(c)CICM 2013");
		m->declare("filename", "oneSourceToStereo.dsp");
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
		m->declare("name", "oneSourceToStereo");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 2;
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
		fHslider1 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
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
		ui_interface->openVerticalBox("oneSourceToStereo");
		ui_interface->addHorizontalSlider("Angle", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6.2831855f), FAUSTFLOAT(6.2831855f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Radius", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst0 * fRec0[1];
			float fTemp0 = fRec0[0] * float(fRec0[0] < 1.0f) + float(fRec0[0] >= 1.0f);
			float fTemp1 = float(input0[i0]) * (2.0794415f * (1.0f - fTemp0) + 1.0f);
			float fTemp2 = 3.0f * fTemp0;
			float fTemp3 = 3.0f * fTemp0 * float(fTemp2 > 0.0f) * float(fTemp2 <= 1.0f) + float(fTemp2 > 1.0f);
			fRec1[0] = fSlow1 + fConst0 * fRec1[1];
			float fTemp4 = fTemp3 * std::cos(fRec1[0]);
			float fTemp5 = 2.0f * fRec1[0];
			float fTemp6 = 2.0794415f * fTemp0;
			float fTemp7 = fTemp6 + -0.6931472f;
			float fTemp8 = 2.4663033f * fTemp7;
			float fTemp9 = 2.4663033f * fTemp7 * float(fTemp8 > 0.0f) * float(fTemp8 <= 1.0f) + float(fTemp8 > 1.0f);
			float fTemp10 = std::cos(fTemp5) * fTemp9;
			float fTemp11 = 0.072916664f * fTemp10;
			float fTemp12 = 3.0f * fRec1[0];
			float fTemp13 = fTemp6 + -1.0986123f;
			float fTemp14 = 3.4760594f * fTemp13;
			float fTemp15 = 3.4760594f * fTemp13 * float(fTemp14 > 0.0f) * float(fTemp14 <= 1.0f) + float(fTemp14 > 1.0f);
			float fTemp16 = std::cos(fTemp12) * fTemp15;
			float fTemp17 = 4.0f * fRec1[0];
			float fTemp18 = fTemp6 + -1.3862944f;
			float fTemp19 = 4.48142f * fTemp18;
			float fTemp20 = 4.48142f * fTemp18 * float(fTemp19 > 0.0f) * float(fTemp19 <= 1.0f) + float(fTemp19 > 1.0f);
			float fTemp21 = 0.013257576f * std::cos(fTemp17) * fTemp20;
			float fTemp22 = 5.0f * fRec1[0];
			float fTemp23 = fTemp6 + -1.609438f;
			float fTemp24 = 5.484815f * fTemp23;
			float fTemp25 = 5.484815f * fTemp23 * float(fTemp24 > 0.0f) * float(fTemp24 <= 1.0f) + float(fTemp24 > 1.0f);
			float fTemp26 = std::cos(fTemp22) * fTemp25;
			float fTemp27 = 6.0f * fRec1[0];
			float fTemp28 = fTemp6 + -1.7917595f;
			float fTemp29 = 6.4871593f * fTemp28;
			float fTemp30 = 6.4871593f * fTemp28 * float(fTemp29 > 0.0f) * float(fTemp29 <= 1.0f) + float(fTemp29 > 1.0f);
			float fTemp31 = std::cos(fTemp27) * fTemp30;
			float fTemp32 = 0.0016434328f * fTemp31;
			float fTemp33 = 7.0f * fRec1[0];
			float fTemp34 = fTemp6 + -1.9459101f;
			float fTemp35 = 7.488876f * fTemp34;
			float fTemp36 = 7.488876f * fTemp34 * float(fTemp35 > 0.0f) * float(fTemp35 <= 1.0f) + float(fTemp35 > 1.0f);
			float fTemp37 = std::cos(fTemp33) * fTemp36;
			float fTemp38 = 0.70710677f * (0.109375f * fTemp4 + 0.0625f + fTemp11 + 0.036458332f * fTemp16 + fTemp21 + 0.003314394f * fTemp26 + fTemp32 + 0.0024826708f * fTemp37);
			float fTemp39 = std::sin(fRec1[0]) * fTemp3;
			float fTemp40 = 0.10104933f * fTemp4;
			float fTemp41 = std::sin(fTemp5) * fTemp9;
			float fTemp42 = 0.05155987f * fTemp41;
			float fTemp43 = 0.05155987f * fTemp10;
			float fTemp44 = std::sin(fTemp12) * fTemp15;
			float fTemp45 = 0.033683106f * fTemp44;
			float fTemp46 = 0.013257576f * std::sin(fTemp17) * fTemp20;
			float fTemp47 = std::sin(fTemp22) * fTemp25;
			float fTemp48 = std::sin(fTemp27) * fTemp30;
			float fTemp49 = std::sin(fTemp33) * fTemp36;
			float fTemp50 = 0.041856002f * fTemp39 + 0.0625f + fTemp40 + fTemp42 + fTemp43 + fTemp45 + 0.013952f * fTemp16 + fTemp46 + 0.0030621006f * fTemp47 - 0.0012683637f * fTemp26 + 0.0011620824f * fTemp48 - 0.0011620824f * fTemp31 + 0.00095007697f * fTemp49 - 0.0022936887f * fTemp37;
			float fTemp51 = 0.077339806f * fTemp39;
			float fTemp52 = 0.072916664f * fTemp41;
			float fTemp53 = 0.0016434328f * fTemp48;
			float fTemp54 = 0.10104933f * fTemp39 + 0.0625f;
			float fTemp55 = 0.0030621006f * fTemp26;
			float fTemp56 = 0.0022936887f * fTemp49;
			float fTemp57 = 0.109375f * fTemp39;
			float fTemp58 = 0.036458332f * fTemp44;
			float fTemp59 = 0.003314394f * fTemp47;
			float fTemp60 = 0.0024826708f * fTemp49;
			float fTemp61 = 0.0011620824f * fTemp31;
			float fTemp62 = 0.077339806f * fTemp4;
			float fTemp63 = 0.0023436304f * fTemp47;
			float fTemp64 = 0.0023436304f * fTemp26;
			float fTemp65 = 0.0030621006f * fTemp47;
			float fTemp66 = 0.05155987f * fTemp10;
			float fTemp67 = fTemp66 + (0.0625f - 0.041856002f * fTemp39 + 0.10104933f * fTemp4 - 0.05155987f * fTemp41) - 0.033683106f * fTemp44 + 0.013952f * fTemp16 - fTemp46 - fTemp65 - 0.0012683637f * fTemp26 - 0.0011620824f * fTemp48 - 0.0011620824f * fTemp31 - 0.00095007697f * fTemp49 - 0.0022936887f * fTemp37;
			float fTemp68 = float(fRec0[0] <= 1.0f) + mydsp_faustpower2_f(fRec0[0]) * float(fRec0[0] > 1.0f);
			output0[i0] = FAUSTFLOAT(fTemp1 * (fTemp38 + 0.98078525f * fTemp50 + 0.98768836f * (fTemp51 + 0.0625f + 0.077339806f * fTemp4 + fTemp52 + 0.025779935f * fTemp44 - 0.025779935f * fTemp16 - fTemp21 - 0.0023436304f * fTemp47 - 0.0023436304f * fTemp26 - fTemp53 - 0.0017555133f * fTemp49 + 0.0017555133f * fTemp37) + 0.9238795f * (fTemp54 + 0.041856002f * fTemp4 + 0.05155987f * fTemp41 - 0.05155987f * fTemp10 - 0.013952f * fTemp44 - 0.033683106f * fTemp16 - fTemp46 - 0.0012683637f * fTemp47 + fTemp55 + 0.0011620824f * fTemp48 + 0.0011620824f * fTemp31 + fTemp56 - 0.00095007697f * fTemp37) + 0.809017f * (fTemp21 + (fTemp57 + 0.0625f - fTemp11 - fTemp58) + fTemp59 - fTemp32 - fTemp60) + 0.64944804f * (fTemp56 + fTemp46 + fTemp54 - 0.041856002f * fTemp4 - fTemp42 - 0.05155987f * fTemp10 - 0.013952f * fTemp44 + 0.033683106f * fTemp16 - 0.0012683637f * fTemp47 - fTemp55 - 0.0011620824f * fTemp48 + fTemp61 + 0.00095007697f * fTemp37) + 0.4539905f * (fTemp53 + 0.077339806f * fTemp39 + 0.0625f - fTemp62 - fTemp52 + 0.025779935f * fTemp44 + 0.025779935f * fTemp16 - fTemp21 - fTemp63 + fTemp64 - 0.0017555133f * fTemp49 - 0.0017555133f * fTemp37) + 0.23344536f * (fTemp45 + 0.041856002f * fTemp39 + 0.0625f - fTemp40 - 0.05155987f * fTemp41 + 0.05155987f * fTemp10 - 0.013952f * fTemp16 - fTemp46 + fTemp65 + 0.0012683637f * fTemp26 - 0.0011620824f * fTemp48 - 0.0011620824f * fTemp31 + 0.00095007697f * fTemp49 + 0.0022936887f * fTemp37) + 0.19509032f * fTemp67) / fTemp68);
			float fTemp69 = 0.0625f - 0.10104933f * fTemp39;
			float fTemp70 = 0.0030621006f * fTemp26;
			output1[i0] = FAUSTFLOAT(fTemp1 * (fTemp38 + 0.19509032f * fTemp50 + 0.23344536f * (fTemp46 + (fTemp43 + fTemp42 + (0.0625f - 0.041856002f * fTemp39 - 0.10104933f * fTemp4) - 0.033683106f * fTemp44 - 0.013952f * fTemp16) - fTemp65 + 0.0012683637f * fTemp26 + 0.0011620824f * fTemp48 - fTemp61 - 0.00095007697f * fTemp49 + 0.0022936887f * fTemp37) + 0.4539905f * (fTemp64 + fTemp52 + (0.0625f - fTemp51 - 0.077339806f * fTemp4) - 0.025779935f * fTemp44 + 0.025779935f * fTemp16 - fTemp21 + 0.0023436304f * fTemp47 - fTemp53 + 0.0017555133f * fTemp49 - 0.0017555133f * fTemp37) + 0.64944804f * (fTemp69 - 0.041856002f * fTemp4 + 0.05155987f * fTemp41 - fTemp66 + 0.013952f * fTemp44 + 0.033683106f * fTemp16 - fTemp46 + 0.0012683637f * fTemp47 - fTemp70 + 0.0011620824f * fTemp48 + 0.0011620824f * fTemp31 - 0.0022936887f * fTemp49 + 0.00095007697f * fTemp37) + 0.809017f * (fTemp60 + (fTemp21 + fTemp58 + (0.0625f - fTemp57 - fTemp11) - fTemp59 - fTemp32)) + 0.9238795f * (fTemp70 + fTemp46 + (fTemp69 + 0.041856002f * fTemp4 - 0.05155987f * fTemp41 - 0.05155987f * fTemp10 + 0.013952f * fTemp44 - 0.033683106f * fTemp16) + 0.0012683637f * fTemp47 - 0.0011620824f * fTemp48 + 0.0011620824f * fTemp31 - 0.0022936887f * fTemp49 - 0.00095007697f * fTemp37) + 0.98768836f * (fTemp53 + (fTemp63 + (fTemp62 + (0.0625f - 0.077339806f * fTemp39) - fTemp52 - 0.025779935f * fTemp44 - 0.025779935f * fTemp16 - fTemp21) - fTemp64) + 0.0017555133f * fTemp49 + 0.0017555133f * fTemp37) + 0.98078525f * fTemp67) / fTemp68);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
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
