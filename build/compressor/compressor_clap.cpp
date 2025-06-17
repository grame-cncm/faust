/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "compressor"
version: "0.0"
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


class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec1[2];
	FAUSTFLOAT fHslider4;
	float fRec0[2];
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fHbargraph0;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.2.0");
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/bypass2:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_stereo:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_stereo:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_stereo:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("demos.lib/compressor_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/compressor_demo:licence", "MIT");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.2.0");
		m->declare("description", "Compressor demo application");
		m->declare("filename", "compressor.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "compressor");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.0");
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
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(4e+01f);
		fHslider1 = FAUSTFLOAT(5.0f);
		fHslider2 = FAUSTFLOAT(5e+02f);
		fHslider3 = FAUSTFLOAT(5e+01f);
		fHslider4 = FAUSTFLOAT(-3e+01f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
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
		ui_interface->declare(0, "tooltip", "Reference:         http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the compressor         has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHbargraph0, "1", "");
		ui_interface->declare(&fHbargraph0, "tooltip", "Current gain of     the compressor in dB");
		ui_interface->declare(&fHbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain Before Makeup", &fHbargraph0, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "A compression Ratio of N means that for each N dB increase in input     signal level above Threshold, the output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fHslider1, FAUSTFLOAT(5.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "When the signal level exceeds the Threshold (in dB), its level     is compressed according to the Ratio");
		ui_interface->declare(&fHslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider4, FAUSTFLOAT(-3e+01f), FAUSTFLOAT(-1e+02f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain     to approach (exponentially) a new lower target level (the compression     `kicking in')");
		ui_interface->declare(&fHslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack", &fHslider3, FAUSTFLOAT(5e+01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain     to approach (exponentially) a new higher target level (the compression     'releasing')");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider2, FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "5", "");
		ui_interface->declare(&fHslider0, "tooltip", "The compressed-signal output level is increased by this amount     (in dB) to make up for the level lost due to compression");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Makeup Gain", &fHslider0, FAUSTFLOAT(4e+01f), FAUSTFLOAT(-96.0f), FAUSTFLOAT(96.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fCheckbox0));
		float fSlow1 = std::pow(1e+01f, 0.05f * float(fHslider0));
		float fSlow2 = 1.0f / std::max<float>(1.1920929e-07f, float(fHslider1)) + -1.0f;
		float fSlow3 = std::max<float>(fConst0, 0.001f * float(fHslider2));
		int iSlow4 = std::fabs(fSlow3) < 1.1920929e-07f;
		float fSlow5 = ((iSlow4) ? 0.0f : std::exp(-(fConst0 / ((iSlow4) ? 1.0f : fSlow3))));
		float fSlow6 = std::max<float>(fConst0, 0.001f * float(fHslider3));
		int iSlow7 = std::fabs(fSlow6) < 1.1920929e-07f;
		float fSlow8 = ((iSlow7) ? 0.0f : std::exp(-(fConst0 / ((iSlow7) ? 1.0f : fSlow6))));
		float fSlow9 = float(fHslider4);
		float fSlow10 = 0.5f * fSlow6;
		int iSlow11 = std::fabs(fSlow10) < 1.1920929e-07f;
		float fSlow12 = ((iSlow11) ? 0.0f : std::exp(-(fConst0 / ((iSlow11) ? 1.0f : fSlow10))));
		float fSlow13 = 1.0f - fSlow12;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			float fTemp1 = ((iSlow0) ? 0.0f : fTemp0);
			float fTemp2 = float(input1[i0]);
			float fTemp3 = ((iSlow0) ? 0.0f : fTemp2);
			float fTemp4 = std::fabs(std::fabs(fTemp1) + std::fabs(fTemp3));
			float fTemp5 = ((fTemp4 > fRec1[1]) ? fSlow8 : fSlow5);
			fRec1[0] = fTemp4 * (1.0f - fTemp5) + fRec1[1] * fTemp5;
			fRec0[0] = fSlow2 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec1[0])) - fSlow9, 0.0f) * fSlow13 + fSlow12 * fRec0[1];
			float fTemp6 = std::pow(1e+01f, 0.05f * fRec0[0]);
			float fTemp7 = fTemp1 * fTemp6;
			output0[i0] = FAUSTFLOAT(((iSlow0) ? fTemp0 : fSlow1 * fTemp7));
			float fTemp8 = fTemp3 * fTemp6;
			float fTemp9 = std::fabs(std::fabs(fTemp7) + std::fabs(fTemp8));
			float fTemp10 = ((fTemp9 > fRec3[1]) ? fSlow8 : fSlow5);
			fRec3[0] = fTemp9 * (1.0f - fTemp10) + fRec3[1] * fTemp10;
			fRec2[0] = fSlow2 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec3[0])) - fSlow9, 0.0f) * fSlow13 + fSlow12 * fRec2[1];
			fHbargraph0 = FAUSTFLOAT(2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::pow(1e+01f, 0.05f * fRec2[0]))));
			output1[i0] = FAUSTFLOAT(((iSlow0) ? fTemp2 : fSlow1 * fTemp8));
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
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
