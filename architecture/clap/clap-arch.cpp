//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend
<<includeIntrinsic>>

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
            std::cerr << "🚨 GuardedUI blocked write to path=" << path << " with val=" << val << std::endl;
            std::abort(); // Catch unintended writes early
        }

        std::cerr << "✅ GuardedUI write: " << path << " = " << val << std::endl;
        MapUI::setParamValue(path, val);
    }


    void setParamValue(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);
        std::cerr << "🔍 [GuardedUI] setParamValue(index=" << index << ", addr=" << addr
                  << ", val=" << val << ") | allowWrite=" << allowWrite << std::endl;

        if (!allowWrite) {
            std::cerr << "🚫 [GuardedUI] Blocked param write by index!" << std::endl;
            return;
        }
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);
        std::cerr << "🔍 [GuardedUI] guardedSetByIndex(index=" << index << ", addr=" << addr
                  << ", val=" << val << ") | allowWrite=" << allowWrite << std::endl;

        if (!allowWrite) {
            std::cerr << "🚫 [GuardedUI] Blocked param write via guardedSetByIndex!" << std::endl;
            return;
        }
        MapUI::setParamValue(addr, val);
    }
};

struct GuardedScope {
    GuardedUI& ui;
    const char* tag;

    GuardedScope(GuardedUI& ui, const char* src = "unknown") : ui(ui), tag(src) {
        std::cerr << "🟢 Enter GuardedScope from: " << tag << std::endl;
        ui.allowWrite = true;
    }

    ~GuardedScope() {
        ui.allowWrite = false;
        std::cerr << "🔴 Exit GuardedScope from: " << tag << std::endl;
    }
};

<<includeclass>>

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
        return Base::startProcessing();
    }

    void stopProcessing() noexcept override {}

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP.init(sampleRate);
        return true;
    }

    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (!hdr) return false;

        std::cerr << "🔎 Event received: type=" << hdr->type << " space_id=0x" << std::hex << hdr->space_id << std::dec << std::endl;

        if (hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) {
            std::cerr << "❌ Rejected param event with wrong namespace: 0x" << std::hex << hdr->space_id << std::dec << std::endl;
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

        //batch-apply all param events (ignore timestamps)
        if (auto events = process->in_events) {
            uint32_t N = events->size(events);
            for (uint32_t i = 0; i < N; ++i) {
                const clap_event_header_t* hdr = events->get(events, i);
                if (!applyParamEventIfValid(hdr)) {
                    std::cerr << "⚠️ Skipped event with invalid namespace or type\n";
                }

            }
        }

        //run DSP compute once on the full buffer
        GuardedScope guard(fUI, "full-buffer");
        uint32_t frames = process->frames_count;
        auto in = (FAUSTFLOAT**) process->audio_inputs->data32;
        auto out = (FAUSTFLOAT**) process->audio_outputs->data32;
        fDSP.compute(frames, in, out);

        return CLAP_PROCESS_CONTINUE;
    }



    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override { return 1; }
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = 1;
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
                std::cerr << "⚠️ paramsFlush skipped event: type=" << hdr->type << ", space_id=0x" << std::hex << hdr->space_id << std::dec << std::endl;
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