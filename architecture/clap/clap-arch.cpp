//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend
<<includeIntrinsic>>

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

//includes for the clap spec
#include <clap/clap.h>
#include <cstring>
#include <vector>
#include <string>

//user defined dsp will be insrted here!
<<includeclass>>


//static isntances shared across plugin lifecycle
static std::vector<std::string> paramAddresses;
static mydsp DSP;
static MapUI UI;


//init dsp and extract parameter addresses from faust UI
static bool plugin_init(const clap_plugin_t* plugin) {
    DSP.init(48000);
    DSP.buildUserInterface(&UI);

    paramAddresses.clear();
    for (int i = 0; i < UI.getParamsCount(); ++i) {
        paramAddresses.push_back(UI.getParamAddress(i));
    }
    return true;
}

//no dynamic allocation performed; nothing to clean up
static void plugin_destroy(const clap_plugin_t* plugin) {}

//activation callback; accepted unconditionally
static bool plugin_activate(const clap_plugin_t* plugin, double sample_rate, uint32_t min, uint32_t max) {
    return true;
}

static void plugin_deactivate(const clap_plugin_t* plugin) {}

static bool plugin_start_processing(const clap_plugin_t* plugin) { return true; }

static void plugin_stop_processing(const clap_plugin_t* plugin) {}


//perform audio computation using faust dsp instance
static clap_process_status plugin_process(const clap_plugin_t* plugin, const clap_process_t* process) {
    if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
        return CLAP_PROCESS_ERROR;

    auto in = (FAUSTFLOAT**)process->audio_inputs->data32;
    auto out = (FAUSTFLOAT**)process->audio_outputs->data32;
    DSP.compute(process->frames_count, in, out);
    return CLAP_PROCESS_CONTINUE;
}


//expose faust parameters to host via clap
static uint32_t plugin_param_count(const clap_plugin_t* plugin) {
    return static_cast<uint32_t>(paramAddresses.size());
}

static bool plugin_param_info(const clap_plugin_t*, uint32_t index, clap_param_info_t* info) {
    if (index >= paramAddresses.size()) return false;

    std::memset(info, 0, sizeof(*info));
    info->id = index;
    snprintf(info->name, sizeof(info->name), "%s", paramAddresses[index].c_str());
    info->min_value = 0.f;
    info->max_value = 1.f;
    info->default_value = 0.5f;
    info->flags = CLAP_PARAM_IS_AUTOMATABLE;

    return true;
}

static bool plugin_param_value(const clap_plugin_t*, clap_id id, double* value) {
    if (id >= paramAddresses.size()) return false;
    *value = UI.getParamValue(paramAddresses[id]);
    return true;
}

static bool plugin_param_set_value(const clap_plugin_t*, clap_id id, double value) {
    if (id >= paramAddresses.size()) return false;
    UI.setParamValue(paramAddresses[id], value);
    return true;
}


//no additional extensions exposed at present
static const void* plugin_get_extension(const clap_plugin_t* plugin, const char* id) {
    return nullptr;
}

static void plugin_on_main_thread(const clap_plugin_t* plugin) {}


//plugin instance definition, with descriptor linked at runtime
static clap_plugin_t gain_plugin = {
    .desc = nullptr,
    .init = plugin_init,
    .destroy = plugin_destroy,
    .activate = plugin_activate,
    .deactivate = plugin_deactivate,
    .start_processing = plugin_start_processing,
    .stop_processing = plugin_stop_processing,
    .process = plugin_process,
    .get_extension = plugin_get_extension,
    .on_main_thread = plugin_on_main_thread
};


//metadata describing the plugin for host discovery
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


//factory logic for plugin instantiation
static const clap_plugin_t* plugin_factory_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        gain_plugin.desc = &gain_desc;
        return &gain_plugin;
    }
    return nullptr;
}

static uint32_t plugin_factory_count(const clap_plugin_factory_t*) {
    return 1;
}

static const clap_plugin_descriptor_t* plugin_factory_get_descriptor(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}

static const clap_plugin_factory_t plugin_factory = {
    .get_plugin_count = plugin_factory_count,
    .get_plugin_descriptor = plugin_factory_get_descriptor,
    .create_plugin = plugin_factory_create
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
        return &plugin_factory;
    return nullptr;
}
//plugin entrypoint exported for host discovery
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION,
    entry_init,
    entry_deinit,
    clap_get_factory
};

}
