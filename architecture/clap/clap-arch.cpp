//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend
<<includeIntrinsic>>

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/dsp/poly-dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
#include <faust/gui/MidiUI.h> //midi ui mapping
#include <faust/midi/midi.h> //faust midi types
#include <faust/gui/UI.h>
#include <faust/gui/GUI.h>
//include for cpp logging
#include <iostream>

//includes for the clap helpers glue
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>
#include <clap/ext/note-ports.h> //clap note port api

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
        if (!allowWrite) return;
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);
        if (!allowWrite) return;
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

<<includeclass>>

class GainPlugin;

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

static const char* gain_features[] = { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr };

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
    .features = gain_features
};



class GainPlugin final : public Base {
public:
    int fNumInputs = 0;
    int fNumOutputs = 0;
    mydsp* fBaseDSP = nullptr; //original Faust DSP
    mydsp_poly* fDSP = nullptr; //midi-aware wrapper
    MidiUI fMIDI;

    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    bool fHasFlushed = false;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
        : Base(desc, host), fMIDI(nullptr) {}

    bool init() noexcept override {
        fBaseDSP = new mydsp();
        fDSP = new mydsp_poly(fBaseDSP, 16, true, true);
        fDSP->buildUserInterface(&fUI);
        fMIDI.addMidiIn(fDSP);
        fDSP->buildUserInterface(&fMIDI);

        fParamAddresses.clear();
        fExpectedValues.clear();

        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            std::string shortname = fUI.getParamShortname(i);
            if (shortname.empty()) continue;
            fParamAddresses.emplace_back(shortname);
            float val = fUI.getParamValue(shortname);

            fExpectedValues.push_back(val);
        }
        return true;
    }

    bool startProcessing() noexcept override {
        return Base::startProcessing();
    }

    void stopProcessing() noexcept override {
        Base::stopProcessing();
    }

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP->init(sampleRate);
        fNumInputs = fDSP->getNumInputs();
        fNumOutputs = fDSP->getNumOutputs();
        std::cerr << "[activate] Sample rate: " << sampleRate << "\n";
        std::cerr << "[activate] Inputs: " << fNumInputs << ", Outputs: " << fNumOutputs << "\n";
        return true;
    }

    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID || hdr->type != CLAP_EVENT_PARAM_VALUE)
            return false;

        const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        if (ev->param_id >= fParamAddresses.size()) return false;
        if (fParamAddresses[ev->param_id].empty()) return false;

        GuardedScope guard(fUI, "applyParamEvent");
        fUI.setParamValue(fParamAddresses[ev->param_id], ev->value);
        fExpectedValues[ev->param_id] = ev->value;
        return true;
    }

    void handleNoteEvent(const clap_event_header_t* hdr) {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) return;

        switch (hdr->type) {
            case CLAP_EVENT_NOTE_ON: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fMIDI.keyOn(ev->channel, ev->key, ev->velocity, 0);
                break;
            }
            case CLAP_EVENT_NOTE_OFF: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fMIDI.keyOff(ev->channel, ev->key, ev->velocity, 0);
                break;
            }
        }
    }

    const void* get_extension(const char* id) noexcept {
        if (std::strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) return (const clap_plugin_note_ports_t*)this;
        if (std::strcmp(id, CLAP_EXT_STATE) == 0) return (const clap_plugin_state_t*)this;
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) return (const clap_plugin_params_t*)this;
        return nullptr;
    }

        clap_process_status process(const clap_process_t* process) noexcept override {
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        const auto& inBuffer = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];

        if (inBuffer.channel_count < fNumInputs || outBuffer.channel_count < fNumOutputs)
            return CLAP_PROCESS_ERROR;

        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        if (process->in_events) {
            for (uint32_t i = 0, N = process->in_events->size(process->in_events); i < N; ++i) {
                const clap_event_header_t* hdr = process->in_events->get(process->in_events, i);
                applyParamEventIfValid(hdr);
                handleNoteEvent(hdr);
            }
        }

        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        GuardedScope guard(fUI, "compute");
        fDSP->compute(process->frames_count, inputs, outputs);
        return CLAP_PROCESS_CONTINUE;
    }

    bool implementsNotePorts() const noexcept override { return true; }
    uint32_t notePortsCount(bool isInput) const noexcept override { return isInput ? 1 : 0; }

    bool notePortsInfo(uint32_t index, bool isInput, clap_note_port_info_t* info) const noexcept override {
        if (!isInput || index != 0 || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, sizeof(info->name), "MIDI In");
        info->supported_dialects = CLAP_NOTE_DIALECT_CLAP;
        info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }

    bool implementsState() const noexcept override { return true; }

    bool stateSave(const clap_ostream_t* stream) noexcept override {
        if (!stream || !stream->write) return false;
        uint32_t paramCount = fExpectedValues.size();
        if (!stream->write(stream, &paramCount, sizeof(paramCount))) return false;
        for (float v : fExpectedValues)
            if (!stream->write(stream, &v, sizeof(v))) return false;
        return true;
    }

    bool stateLoad(const clap_istream_t* stream) noexcept override {
        if (!stream || !stream->read) return false;
        uint32_t paramCount = 0;
        if (!stream->read(stream, &paramCount, sizeof(paramCount))) return false;
        if (paramCount != fExpectedValues.size()) return false;

        for (uint32_t i = 0; i < paramCount; ++i) {
            float v;
            if (!stream->read(stream, &v, sizeof(v))) return false;
            GuardedScope guard(fUI, "stateLoad");
            fUI.setParamValue(fParamAddresses[i], v);
            fExpectedValues[i] = v;
        }
        return true;
    }

    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= fParamAddresses.size()) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        const char* name = fParamAddresses[index].c_str();
        if (name[0] == '/') ++name;
        std::snprintf(info->name, sizeof(info->name), "%s", name);
        info->min_value = 0.f;
        info->max_value = 1.f;
        info->default_value = 0.5f;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (id >= fExpectedValues.size() || !value) return false;
        *value = fExpectedValues[id];
        return true;
    }

    bool paramsTextToValue(clap_id id, const char* text, double* outValue) noexcept override {
        if (!text || id >= fExpectedValues.size()) return false;
        try {
            *outValue = std::stod(text);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool paramsValueToText(clap_id id, double value, char* outBuffer, uint32_t bufferSize) noexcept override {
        if (!outBuffer || bufferSize < 1 || id >= fExpectedValues.size()) return false;
        std::snprintf(outBuffer, bufferSize, "%.3f", value);
        return true;
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;
        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            applyParamEventIfValid(hdr);
        }
    }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override { return 1; }

    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0 || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? fNumInputs : fNumOutputs;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        return true;
    }

    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};

// Factory glue
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0)
        return GainPlugin::create(host);
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
