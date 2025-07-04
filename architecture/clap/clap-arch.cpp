// Created by Cucu on 02/06/2025.
//this file translates faust's mydsp c++ class into the clap plugin interface
//core of the plugin backend

<<includeIntrinsic>>

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/dsp/poly-dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>
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
<<includeclass>>

struct CLAPMapUI : public MapUI {
    struct ParamMeta {
        FAUSTFLOAT min;
        FAUSTFLOAT max;
        FAUSTFLOAT init;
    };

    struct ParamData {
        std::string shortname;
        FAUSTFLOAT* zone;
        ParamMeta meta;
    };

    std::vector<ParamData> fParams;

    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        std::string shortname = buildPath(label);
        fParams.push_back({shortname, zone, {min, max, init}});
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        std::string shortname = buildPath(label);
        fParams.push_back({shortname, zone, {min, max, init}});
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        std::string shortname = buildPath(label);
        fParams.push_back({shortname, zone, {min, max, init}});
    }


    void openTabBox(const char* label) override { MapUI::openTabBox(label); }
    void openHorizontalBox(const char* label) override { MapUI::openHorizontalBox(label); }
    void openVerticalBox(const char* label) override { MapUI::openVerticalBox(label); }
    void closeBox() override { MapUI::closeBox(); }


    int getParamsCount() const { return int(fParams.size()); }

    std::string getParamShortname(int index) const {
        if (index < 0 || index >= int(fParams.size())) return "";
        return fParams[index].shortname;
    }

    FAUSTFLOAT getParamMin(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.f;
        return fParams[index].meta.min;
    }

    FAUSTFLOAT getParamMax(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 1.f;
        return fParams[index].meta.max;
    }


    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        MapUI::setParamValue(path, val);
    }

    FAUSTFLOAT getParamValue(const std::string& path) {
        return MapUI::getParamValue(path);
    }


    FAUSTFLOAT getParamInit(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.5f;
        return fParams[index].meta.init;
    }

    FAUSTFLOAT* getParamZone(int index) const {
        if (index < 0 || index >= int(fParams.size())) return nullptr;
        return fParams[index].zone;
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        if (index < 0 || index >= int(fParams.size())) return;
        *fParams[index].zone = val;
    }

    FAUSTFLOAT getParamValue(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.f;
        return *fParams[index].zone;
    }

    std::string getParamAddress(int index) const {
        if (index < 0 || index >= int(fParams.size())) return "";
        return fParams[index].shortname;
    }
};

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
    int fNumInputs = 2; //defautl to stereo??
    int fNumOutputs = 2;
    mydsp* fBaseDSP = nullptr; //original Faust DSP
    mydsp_poly* fDSP = nullptr; //midi-aware wrapper

    CLAPMapUI fUI;
    bool fIsPolyphonic = false; //determines if midi/note handling is enabled
    MidiUI* fMidiUI = nullptr;
    midi_handler* fMidiHandler = nullptr;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
        : Base(desc, host) {}

    bool init() noexcept override {
        fBaseDSP = new mydsp();
        fIsPolyphonic = true;
        if (fIsPolyphonic) {
            fDSP = new mydsp_poly(fBaseDSP, 16, true, true);
            fDSP->buildUserInterface(&fUI);
            GUI::updateAllGuis();

        } else {
            fMidiHandler = new midi_handler();
            fMidiUI = new MidiUI(fMidiHandler);
            fBaseDSP->buildUserInterface(fMidiUI); // MIDI support
            fBaseDSP->buildUserInterface(&fUI); // regular UI
            GUI::updateAllGuis();
        }
        return true;
    }
    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        if (fIsPolyphonic) {
            fDSP->init(sampleRate);
            fNumInputs = fDSP->getNumInputs();
            fNumOutputs = fDSP->getNumOutputs();
        } else {
            fBaseDSP->init(sampleRate);
            fNumInputs = fBaseDSP->getNumInputs();
            fNumOutputs = fBaseDSP->getNumOutputs();
        }
        return true;
    }

    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID || hdr->type != CLAP_EVENT_PARAM_VALUE)
            return false;

        const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        int paramCount = fUI.getParamsCount();
        if (!ev || ev->param_id < 0 || ev->param_id >= paramCount)
            return false;

        fUI.setParamValue(ev->param_id, ev->value);
        return true;
    }


    void handlePolyMIDIEvent(const clap_event_header_t* hdr){
        switch (hdr->type) {
            case CLAP_EVENT_NOTE_ON: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fDSP->keyOn(ev->channel, ev->key, ev->velocity);
                break;
            }
            case CLAP_EVENT_NOTE_OFF: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                fDSP->keyOff(ev->channel, ev->key, ev->velocity);
                break;
            }
            case CLAP_EVENT_MIDI: {
                auto* ev = reinterpret_cast<const clap_event_midi_t*>(hdr);
                uint8_t status = ev->data[0] & 0xF0;
                uint8_t channel = ev->data[0] & 0x0F;
                uint8_t data1 = ev->data[1];
                uint8_t data2 = ev->data[2];

                switch (status) {
                    case 0x90: fDSP->keyOn(channel, data1, data2); break;
                    case 0x80: fDSP->keyOff(channel, data1, data2); break;
                    case 0xB0: fDSP->ctrlChange(channel, data1, data2); break;
                    case 0xE0: fDSP->pitchWheel(channel, (data2 << 7) | data1); break;
                }
                break;
            }
        }
    }

    void handleDSPMIDIEvent(const clap_event_header_t* hdr) {
        if (!fBaseDSP || !fMidiHandler || !hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) return;

        switch (hdr->type) {
            case CLAP_EVENT_MIDI: {
                auto* ev = reinterpret_cast<const clap_event_midi_t*>(hdr);
                int type = ev->data[0] & 0xF0;
                int channel = ev->data[0] & 0x0F;
                int data1 = ev->data[1];
                int data2 = ev->data[2];
                fMidiHandler->handleData2(0.0, type, channel, data1, data2);

                break;
            }
            default: break;
        }
    }


    const void* get_extension(const char* id) noexcept {
        if (std::strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) return (const clap_plugin_note_ports_t*)this;
        if (std::strcmp(id, CLAP_EXT_STATE) == 0) return (const clap_plugin_state_t*)this;
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) return (const clap_plugin_params_t*)this;
        return nullptr;
    }

    clap_process_status process(const clap_process_t* process) noexcept override {
        if (process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
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
                if (fIsPolyphonic) {
                    handlePolyMIDIEvent(hdr);
                } else {
                    handleDSPMIDIEvent(hdr);
                }
            }
        }

        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        if (fIsPolyphonic) {
            fDSP->compute(process->frames_count, inputs, outputs);
        } else {
            fBaseDSP->compute(process->frames_count, inputs, outputs);
        }

        return CLAP_PROCESS_CONTINUE;
    }

    bool implementsNotePorts() const noexcept override { return true; }
    uint32_t notePortsCount(bool isInput) const noexcept override { return isInput ? 1 : 0; }

    bool notePortsInfo(uint32_t index, bool isInput, clap_note_port_info_t* info) const noexcept override {
        if (!isInput || index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, CLAP_NAME_SIZE, "MIDI In");
        info->supported_dialects = CLAP_NOTE_DIALECT_CLAP | CLAP_NOTE_DIALECT_MIDI;
        info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }

    bool implementsState() const noexcept override { return true; }

    bool stateSave(const clap_ostream_t* stream) noexcept override {
        if (!stream || !stream->write) return false;
        int paramCount = fUI.getParamsCount();
        if (!stream->write(stream, &paramCount, sizeof(paramCount))) return false;
        for (int i = 0; i < paramCount; ++i) {
            float v = fUI.getParamValue(i);
            if (!stream->write(stream, &v, sizeof(v))) return false;
        }
        return true;
    }

    bool stateLoad(const clap_istream_t* stream) noexcept override {
        if (!stream || !stream->read) return false;
        uint32_t paramCount = 0;
        if (!stream->read(stream, &paramCount, sizeof(paramCount))) return false;
        if (paramCount != (uint32_t)fUI.getParamsCount())
            return false;
        for (uint32_t i = 0; i < paramCount; ++i) {
            float v;
            if (!stream->read(stream, &v, sizeof(v))) return false;
            fUI.setParamValue(i, v);
        }

        if (_host.canUseParams()) {
            _host.paramsRescan(CLAP_PARAM_RESCAN_VALUES | CLAP_PARAM_RESCAN_ALL);
            _host.paramsRequestFlush();
        }

        return true;
    }

    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override {
        return static_cast<uint32_t>(fUI.getParamsCount());
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        int paramCount = fUI.getParamsCount();
        if (index >= paramCount) return false;

        std::memset(info, 0, sizeof(*info));
        info->id = index;

        std::string paramName = fUI.getParamShortname(index);
        const char* name = paramName.c_str();
        if (name[0] == '/') ++name;
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", name);

        FAUSTFLOAT min = fUI.getParamMin(index);
        FAUSTFLOAT max = fUI.getParamMax(index);
        FAUSTFLOAT init = fUI.getParamInit(index);

        info->min_value = min;
        info->max_value = max;
        info->default_value = init;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;

        std::strncpy(info->module, "Main", sizeof(info->module));
        info->module[sizeof(info->module) - 1] = '\0'; //make sure of null-termination

        return true;
    }


bool paramsValue(clap_id id, double* value) noexcept override {
    if (!value || id >= (clap_id)fUI.getParamsCount())
        return false;
    *value = fUI.getParamValue(id);
    return true;
}


    bool paramsTextToValue(clap_id id, const char* text, double* outValue) noexcept override {
        if (!text || !outValue || id >= (clap_id)fUI.getParamsCount())
            return false;
        try {
            *outValue = std::stod(text);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool paramsValueToText(clap_id id, double value, char* outBuffer, uint32_t bufferSize) noexcept override {
        if (!outBuffer || bufferSize == 0 || id >= (clap_id)fUI.getParamsCount())
            return false;
        std::snprintf(outBuffer, bufferSize, "%.3f", value);
        return true;
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!hdr) continue;
            applyParamEventIfValid(hdr);
            if (fIsPolyphonic) {
                handlePolyMIDIEvent(hdr);
            } else {
                handleDSPMIDIEvent(hdr);
            }
        }
    }


    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override { return 1; }

    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0 || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? std::max(1, fNumInputs) : std::max(1, fNumOutputs);
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->in_place_pair = 0;  //port for in-place processing
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