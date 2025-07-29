/* ------------------------------------------------------------
name: "gain"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend

#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

#include <clap/clap.h>
#include <cstring>
#include <vector>
#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

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
	
	FAUSTFLOAT fVslider0;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "gain.dsp");
		m->declare("name", "gain");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
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
		ui_interface->openVerticalBox("gain");
		ui_interface->addVerticalSlider("gain", &fVslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fVslider0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			output0[i0] = FAUSTFLOAT(fSlow0 * float(input0[i0]));
		}
	}

};

static std::vector<std::string> paramAddresses;
static mydsp DSP;
static MapUI UI;

static bool plugin_init(const clap_plugin_t* plugin) {
    DSP.init(48000);
    DSP.buildUserInterface(&UI);

    paramAddresses.clear();
    for (int i = 0; i < UI.getParamsCount(); ++i) {
        paramAddresses.push_back(UI.getParamAddress(i));
    }
    return true;
}

static void plugin_destroy(const clap_plugin_t* plugin) {}

static bool plugin_activate(const clap_plugin_t* plugin, double sample_rate, uint32_t min, uint32_t max) {
    return true;
}

static void plugin_deactivate(const clap_plugin_t* plugin) {}

static bool plugin_start_processing(const clap_plugin_t* plugin) { return true; }

static void plugin_stop_processing(const clap_plugin_t* plugin) {}

static clap_process_status plugin_process(const clap_plugin_t* plugin, const clap_process_t* process) {
    if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
        return CLAP_PROCESS_ERROR;

    auto in = (FAUSTFLOAT**)process->audio_inputs->data32;
    auto out = (FAUSTFLOAT**)process->audio_outputs->data32;
    DSP.compute(process->frames_count, in, out);
    return CLAP_PROCESS_CONTINUE;
}

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

static const void* plugin_get_extension(const clap_plugin_t* plugin, const char* id) {
    return nullptr;
}

static void plugin_on_main_thread(const clap_plugin_t* plugin) {}

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

static bool entry_init(const char* path) {
    return true;
}

static void entry_deinit() {}

extern "C" {

CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &plugin_factory;
    return nullptr;
}

CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION,
    entry_init,
    entry_deinit,
    clap_get_factory
};

}

#endif
