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
#include <clap/helpers/host-proxy.hh> //required for clap::helpers base class
#include <clap/events.h>

//guarded MapUI subclass to prevent accidental param writes
struct GuardedUI : public MapUI {
    bool allowWrite = false;

    //log and guard set by path
    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        std::cerr << "🔍 [GuardedUI] setParamValue(path=" << path << ", val=" << val
                  << ") | allowWrite=" << allowWrite << std::endl;

        if (!allowWrite) {
            std::cerr << "🚨 ILLEGAL param write detected! path=" << path << " val=" << val << std::endl;
            std::abort(); //immediate crash
        }

        MapUI::setParamValue(path, val);
    }

    //log and guard set by index (could be used by other FAUST layers)
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

//scoped guard to enable/disable writes safely
struct GuardedScope {
    GuardedUI& ui;
    GuardedScope(GuardedUI& ui) : ui(ui) {
        ui.allowWrite = true;
    }
    ~GuardedScope() {
         ui.allowWrite = false;
    }
};



//user defined dsp will be inserted here!
<<includeclass>>

//plugin class specialisation using clap helpers
using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;


//plugin descriptor metadata
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
    //faust dsp and UI objects
    mydsp fDSP;
    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    bool fHasFlushed= false; //new flag to track if flush() was called

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
    : Base(desc, host) {
        //std::cout << "[faust2clap] GainPlugin constructor" << std::endl;
        //std::cout << "[faust2clap] implementsAudioPorts: " << std::boolalpha << implementsAudioPorts() << std::endl;
    }


    //plugin lifecycle: init, activate, process, etc.
    bool init() noexcept override {
        //fDSP.init(48000);
        fDSP.buildUserInterface(&fUI);

        fParamAddresses.clear();
        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            auto shortname = fUI.getParamShortname(i);
            fParamAddresses.push_back(shortname);
            float actual = fUI.getParamValue(shortname);
            fExpectedValues.push_back(actual); //capture whatever the DSP sets
            std::cout <<"[init] param" << i << "=" <<actual <<std::endl;

            //std::cout << "[faust2clap] Param " << i << ": " << shortname << std::endl;
        }
        return true;
    }

    bool startProcessing() noexcept override {
        //std::cout << "[faust2clap] startProcessing() CALLED" << std::endl;
        bool ok = Base::startProcessing();
        //std::cout << "[faust2clap] Base::startProcessing() returned: " << std::boolalpha << ok << std::endl;
        return ok;
    }



    void stopProcessing() noexcept override {
        // no-op
    }

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP.init(sampleRate);
        return true;
    }

    clap_process_status process(const clap_process_t* process) noexcept override {
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        if (fHasFlushed) {
            for (size_t i = 0; i < fExpectedValues.size(); ++i) {
                float actual = fUI.getParamValue(fParamAddresses[i]);
                float expected = fExpectedValues[i];
                if (actual != expected) {
                    fExpectedValues[i] = actual;
                }
            }
        }

        auto in = (FAUSTFLOAT**)process->audio_inputs->data32;
        auto out = (FAUSTFLOAT**)process->audio_outputs->data32;

        {
            GuardedScope guard(fUI);
            fDSP.compute(process->frames_count, in, out);
        }

        return CLAP_PROCESS_CONTINUE;
    }



    //expose parameter count
    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }


    //audio port declaration for validator compatibility
    bool implementsAudioPorts() const noexcept override {
        //std::cout << "[faust2clap] implementsAudioPorts() CALLED" << std::endl;
        return true;
    }

    uint32_t audioPortsCount(bool isInput) const noexcept override {
        return 1;
    }

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
        if (addr[0] == '/')
            addr += 1;

        snprintf(info->name, sizeof(info->name), "%s", addr);
        info->min_value = 0.f;
        info->max_value = 1.f;
        info->default_value = 0.5f;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;

        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        *value = fUI.getParamValue(fParamAddresses[id]);
        std::cout << "[param value read] id=" << id << " val=" << *value << std::endl;
        return true;
    }


    bool paramsTextToValue(clap_id, const char*, double*) noexcept override {
        return false; //not implemented
    }

    bool paramsValueToText(clap_id, double, char*, uint32_t) noexcept override {
        return false; //not implemented
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;

        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!hdr) continue;

            std::cout << "[flush] got event: type=" << hdr->type
                      << " space_id=0x" << std::hex << hdr->space_id << std::dec << std::endl;



            if (hdr->type != CLAP_EVENT_PARAM_VALUE)
                continue;


            if (hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) {
                std::cerr << "❌ Rejected param event with wrong namespace: 0x"
                          << std::hex << hdr->space_id << std::dec << std::endl;
                continue;
            }

            const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);


            if (ev->param_id >= fParamAddresses.size()) {
                std::cout << "[faust2clap] skipping event with out-of-range param_id " << ev->param_id << std::endl;
                continue;
            }

            std::cout << "[faust2clap] ➤ applying value to param " << ev->param_id << std::endl;

            {
                GuardedScope guard(fUI);
                fUI.setParamValue(fParamAddresses[ev->param_id], ev->value);
            }


            fExpectedValues[ev->param_id] = ev->value;
        }
    }



    using Base::clapPlugin;

    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }

};


//factory logic for plugin instantiation
static uint32_t plugin_count(const clap_plugin_factory_t*) {
    return 1;
}

static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}

static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        return GainPlugin::create(host); //use static helper method?
    }
    return nullptr;
}



static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};

//entry point init and teardown
static bool entry_init(const char* path) {
    return true;
}

static void entry_deinit() {}

extern "C" {
//factory dispatcher, as required by clap spec
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}
//plugin entrypoint exported for host discovery
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}
