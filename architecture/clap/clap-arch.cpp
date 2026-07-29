// Created by Facundo Franchino on 02/06/2025.

// this file implements a CLAP plugin backend by wrapping Faust's mydsp class.
// it acts as a bridge between Faust-generated DSP code and the CLAP plugin API.
<< includeIntrinsic >>
// faust DSP and UI headers
#include <faust/dsp/dsp.h>
#include <faust/dsp/poly-dsp.h>
#include <faust/gui/GUI.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/midi/midi.h>  // faust midi types
#include "plugin_metadata.h"

// Unlocks the FAUST_INPUTS/FAUST_OUTPUTS block that `faust -uim` emits with the
// generated class below. Must precede <<includeclass>>.
#define FAUST_UIMACROS 1

// That block also declares a control-registration macro per widget. Only the
// arity constants are wanted here -- the UI is built through CLAPMapUI -- so
// they are defined empty, as minimal-static.cpp and csound.cpp do.
#define FAUST_ADDBUTTON(l, f)
#define FAUST_ADDCHECKBOX(l, f)
#define FAUST_ADDVERTICALSLIDER(l, f, i, a, b, s)
#define FAUST_ADDHORIZONTALSLIDER(l, f, i, a, b, s)
#define FAUST_ADDNUMENTRY(l, f, i, a, b, s)
#define FAUST_ADDVERTICALBARGRAPH(l, f, a, b)
#define FAUST_ADDHORIZONTALBARGRAPH(l, f, a, b)
#define FAUST_ADDSOUNDFILE(l, f, s)

// cpp logging
#include <iostream>

// CLAP helpers and API headers
#include <clap/events.h>
#include <clap/ext/note-ports.h>  // CLAP note port extension
#include <clap/helpers/host-proxy.hh>
#include <clap/helpers/plugin.hh>

// include user Faust-generated class placeholder
<< includeclass >>

// custom UI class inheriting Faust's MapUI to store parameter metadata
struct CLAPMapUI : public MapUI {
    // One entry per host-visible parameter, in DSP declaration order.
    //
    // MapUI's own index space cannot be reused for this. It walks
    // fPathZoneMap, a std::map, so its indices follow the *alphabetical* order
    // of the paths, and it includes bargraphs. Indexing metadata separately
    // from names therefore mismatches them as soon as the DSP has more than one
    // control, and the host ends up automating one parameter with another
    // one's range.
    //
    // Keeping path, zone and range together in one ordered vector makes that
    // impossible by construction: every accessor below reads a single entry.
    struct ParamMeta {
        std::string path;
        FAUSTFLOAT* zone;
        FAUSTFLOAT  min;
        FAUSTFLOAT  max;
        FAUSTFLOAT  init;
    };

    std::vector<ParamMeta> fParams;

    // The path is read back from MapUI rather than rebuilt, so the two always
    // agree on what a control is called. Called once per control at init.
    void trackParam(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT init)
    {
        fParams.push_back({MapUI::getParamAddress(zone), zone, min, max, init});
    }

    // overridden Faust UI methods to track parameters as they are created
    void addButton(const char* label, FAUSTFLOAT* zone) override
    {
        MapUI::addButton(label, zone);
        trackParam(zone, 0, 1, 0);
    }

    void addCheckButton(const char* label, FAUSTFLOAT* zone) override
    {
        MapUI::addCheckButton(label, zone);
        trackParam(zone, 0, 1, 0);
    }

    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                           FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        trackParam(zone, min, max, init);
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        trackParam(zone, min, max, init);
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                     FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        trackParam(zone, min, max, init);
    }

    // Bargraphs are deliberately not tracked: they are DSP outputs, which a
    // host must not be offered as automatable parameters. They stay in MapUI
    // so that value queries by path keep working.

    // box-related methods simply forward to base class (no extra handling)
    void openTabBox(const char* label) override { MapUI::openTabBox(label); }
    void openHorizontalBox(const char* label) override { MapUI::openHorizontalBox(label); }
    void openVerticalBox(const char* label) override { MapUI::openVerticalBox(label); }
    void closeBox() override { MapUI::closeBox(); }

    // accessors for parameters count and metadata. These hide the MapUI
    // versions on purpose: the plugin holds a CLAPMapUI and must see this
    // index space, not MapUI's.
    int getParamsCount() const { return int(fParams.size()); }

    bool validIndex(int index) const { return index >= 0 && index < int(fParams.size()); }

    std::string getParamShortname(int index) const
    {
        if (!validIndex(index)) {
            return "";
        }
        const std::string& full = fParams[index].path;
        if (full.empty() || full == "/") {
            return "param" + std::to_string(index);
        }
        size_t slash = full.find_last_of('/');
        return (slash != std::string::npos) ? full.substr(slash + 1) : full;
    }

    FAUSTFLOAT getParamMin(int index) const { return validIndex(index) ? fParams[index].min : 0.f; }

    FAUSTFLOAT getParamMax(int index) const { return validIndex(index) ? fParams[index].max : 1.f; }

    // access initial/default parameter value and the zone pointer
    FAUSTFLOAT getParamInit(int index) const
    {
        return validIndex(index) ? fParams[index].init : 0.5f;
    }

    FAUSTFLOAT* getParamZone(int index) const
    {
        return validIndex(index) ? fParams[index].zone : nullptr;
    }

    // set or get parameter value by index directly via zone pointer
    void setParamValue(int index, FAUSTFLOAT val)
    {
        auto zone = getParamZone(index);
        if (zone) {
            *zone = val;
        }
    }

    FAUSTFLOAT getParamValue(int index) const
    {
        auto zone = getParamZone(index);
        return zone ? *zone : 0.f;
    }

    // return the unique parameter address (path)
    std::string getParamAddress(int index) const
    {
        return validIndex(index) ? fParams[index].path : "";
    }
};

// forward declaration for Plugin class
class APlugin;

// base class alias for simplified CLAP plugin inheritance
using Base = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                   clap::helpers::CheckingLevel::Minimal>;

// What kind of plugin this is, from the host's point of view.
//
// A DSP with no audio input is an instrument. Announcing audio-effect for
// everything, as this did, files a synthesiser away with the reverbs: REAPER
// records the kind in its plugin cache, so the instrument never shows up where
// a musician looks for one.
//
// FAUST_INPUTS comes from the `-uim` macros, which faust2clap asks for; the
// #ifdef keeps the file usable with a hand-written faust command line that
// omits it, falling back to the conservative answer.
#if defined(FAUST_INPUTS) && FAUST_INPUTS == 0
#if defined(FAUST_IS_POLYPHONIC) && FAUST_IS_POLYPHONIC == 1
static const char* gain_features[] = {CLAP_PLUGIN_FEATURE_INSTRUMENT,
                                      CLAP_PLUGIN_FEATURE_SYNTHESIZER, nullptr};
#else
static const char* gain_features[] = {CLAP_PLUGIN_FEATURE_INSTRUMENT, nullptr};
#endif
#else
static const char* gain_features[] = {CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr};
#endif

// plugin descriptor structure describing metadata to the host
constexpr static clap_plugin_descriptor_t gain_desc = {.clap_version = CLAP_VERSION_INIT,
                                                       .id           = FAUST_PLUGIN_ID,
                                                       .name         = FAUST_PLUGIN_NAME,
                                                       .vendor       = FAUST_PLUGIN_VENDOR,
                                                       .url          = "https://faust.grame.fr",
                                                       .manual_url   = "",
                                                       .support_url  = "",
                                                       .version      = FAUST_PLUGIN_VERSION,
                                                       .description  = FAUST_PLUGIN_DESCRIPTION,
                                                       .features     = gain_features};

// the main plugin class implementing CLAP plugin behaviour
class APlugin final : public Base {
   public:
    // Set in init(), before the host queries any extension. They must not be
    // guessed: audioPortsInfo() runs at instantiation, and announcing a channel
    // count the DSP does not have makes the host allocate buffers process()
    // then rejects.
    int fNumInputs  = 0;
    int fNumOutputs = 0;
    // The DSP being played, whatever its shape: a bare mydsp, or a mydsp_poly
    // wrapping one. init/compute/getNumInputs are virtual, so everything except
    // note handling works through this pointer alone.
    dsp* fDSP = nullptr;

    CLAPMapUI     fUI;
    bool          fIsPolyphonic = false;  // determines if midi/note handling is enabled
    MidiUI*       fMidiUI       = nullptr;
    midi_handler* fMidiHandler  = nullptr;

    // constructor initialises base class with descriptor and host pointers
    APlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host) : Base(desc, host) {}

    bool init() noexcept override
    {
// Check if FAUST_IS_POLYPHONIC is defined and set to 1
#ifdef FAUST_IS_POLYPHONIC
        fIsPolyphonic = (FAUST_IS_POLYPHONIC == 1);
#else
        fIsPolyphonic = false;  // Default to mono for effects
#endif

        if (fIsPolyphonic) {
            // create polyphonic wrapper and build UI linked to CLAPMapUI.
            // Voice count comes from plugin_metadata.h, which faust2clap
            // generates from -nvoices or the DSP's own `declare nvoices`.
            // mydsp_poly takes ownership of the voice it is given.
            fDSP = new mydsp_poly(new mydsp(), FAUST_NVOICES, true, true);
        } else {
            // A monophonic DSP gets raw MIDI instead: notes are meaningless
            // without voices, but controllers still map to its parameters.
            fDSP         = new mydsp();
            fMidiHandler = new midi_handler();
            fMidiUI      = new MidiUI(fMidiHandler);
            fDSP->buildUserInterface(fMidiUI);
        }
        // Common to both: the parameter map the host drives through. In the
        // monophonic case it must come after MidiUI, so that a control the DSP
        // declares for MIDI is registered there first.
        fDSP->buildUserInterface(&fUI);
        GUI::updateAllGuis();

        // Read the arity now: the host asks audioPortsInfo() before activate().
        fNumInputs  = fDSP->getNumInputs();
        fNumOutputs = fDSP->getNumOutputs();
        return true;
    }

    // activate plugin and initialise DSP with sample rate
    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override
    {
        fDSP->init(sampleRate);
        return true;
    }

    // apply parameter event if valid and within range
    bool applyParamEventIfValid(const clap_event_header_t* hdr)
    {
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID ||
            hdr->type != CLAP_EVENT_PARAM_VALUE) {
            return false;
        }

        const auto* ev         = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        int         paramCount = fUI.getParamsCount();
        if (ev->param_id >= uint32_t(paramCount)) {
            return false;
        }

        fUI.setParamValue(ev->param_id, ev->value);
        return true;
    }

    // CLAP gives note velocity as a double in 0..1; dsp_poly speaks MIDI and
    // wants an integer in 0..127. Passing the double through truncates every
    // velocity below 1.0 to zero, which silences the voice.
    static int midiVelocity(double velocity)
    {
        int value = int(velocity * 127.0 + 0.5);
        return (value < 0) ? 0 : ((value > 127) ? 127 : value);
    }

    // handle MIDI events in polyphonic mode by forwarding to Faust DSP
    void handlePolyMIDIEvent(const clap_event_header_t* hdr)
    {
        // Only reached when fIsPolyphonic, so fDSP is a mydsp_poly. This is the
        // one place needing more than the dsp interface: note handling comes
        // from dsp_poly, not dsp.
        dsp_poly* poly = static_cast<dsp_poly*>(fDSP);
        switch (hdr->type) {
            case CLAP_EVENT_NOTE_ON: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                poly->keyOn(ev->channel, ev->key, midiVelocity(ev->velocity));
                break;
            }
            case CLAP_EVENT_NOTE_OFF: {
                auto* ev = reinterpret_cast<const clap_event_note_t*>(hdr);
                poly->keyOff(ev->channel, ev->key, midiVelocity(ev->velocity));
                break;
            }
            case CLAP_EVENT_MIDI: {
                auto*   ev      = reinterpret_cast<const clap_event_midi_t*>(hdr);
                uint8_t status  = ev->data[0] & 0xF0;
                uint8_t channel = ev->data[0] & 0x0F;
                uint8_t data1   = ev->data[1];
                uint8_t data2   = ev->data[2];

                switch (status) {
                    case 0x90:
                        poly->keyOn(channel, data1, data2);
                        break;
                    case 0x80:
                        poly->keyOff(channel, data1, data2);
                        break;
                    case 0xB0:
                        poly->ctrlChange(channel, data1, data2);
                        break;
                    case 0xE0:
                        poly->pitchWheel(channel, (data2 << 7) | data1);
                        break;
                }
                break;
            }
        }
    }

    // handle MIDI events in non-polyphonic DSP mode.
    // Assumes fMidiHandler and hdr are valid and hdr->space_id == CLAP_CORE_EVENT_SPACE_ID
    void handleDSPMIDIEvent(const clap_event_header_t* hdr)
    {
        switch (hdr->type) {
            case CLAP_EVENT_MIDI: {
                auto* ev      = reinterpret_cast<const clap_event_midi_t*>(hdr);
                int   type    = ev->data[0] & 0xF0;
                int   channel = ev->data[0] & 0x0F;
                int   data1   = ev->data[1];
                int   data2   = ev->data[2];
                fMidiHandler->handleData2(0.0, type, channel, data1, data2);
                break;
            }
            default:
                break;
        }
    }

    // provide CLAP extensions this plugin supports
    const void* get_extension(const char* id) noexcept
    {
        if (std::strcmp(id, CLAP_EXT_NOTE_PORTS) == 0) {
            return (const clap_plugin_note_ports_t*)this;
        }
        if (std::strcmp(id, CLAP_EXT_STATE) == 0) {
            return (const clap_plugin_state_t*)this;
        }
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) {
            return (const clap_plugin_params_t*)this;
        }
        return nullptr;
    }

    // main processing method called by host each audio block
    clap_process_status process(const clap_process_t* process) noexcept override
    {
        // Sanity checks on the audio buffers. Only the output side is required:
        // a synthesiser has no audio input, so a host is right to pass it no
        // input port at all, and demanding one silences every instrument.
        if (process->audio_outputs_count < 1) {
            return CLAP_PROCESS_ERROR;
        }
        const auto& outBuffer = process->audio_outputs[0];
        if (outBuffer.channel_count < fNumOutputs) {
            return CLAP_PROCESS_ERROR;
        }

        const clap_audio_buffer_t* inBuffer =
            (process->audio_inputs_count > 0) ? &process->audio_inputs[0] : nullptr;
        if (fNumInputs > 0 && (!inBuffer || inBuffer->channel_count < fNumInputs)) {
            return CLAP_PROCESS_ERROR;
        }

        // process incoming parameter and MIDI events
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

        // CLAP fills exactly one of data32/data64 and leaves the other null.
        // Only 32-bit is claimed (no CLAP_AUDIO_PORT_SUPPORTS_64BITS flag), so
        // a null data32 means the host ignored that and the block cannot be
        // processed — better a silent block than a null dereference.
        if ((fNumInputs > 0 && !inBuffer->data32) || (fNumOutputs > 0 && !outBuffer.data32)) {
            return CLAP_PROCESS_ERROR;
        }

        // Sized for at least one element: a zero-length array is undefined, and
        // fNumInputs is legitimately 0 for a synthesiser.
        FAUSTFLOAT* inputs[fNumInputs > 0 ? fNumInputs : 1];
        FAUSTFLOAT* outputs[fNumOutputs > 0 ? fNumOutputs : 1];
        for (int i = 0; i < fNumInputs; ++i) {
            inputs[i] = inBuffer->data32[i];
        }
        for (int i = 0; i < fNumOutputs; ++i) {
            outputs[i] = outBuffer.data32[i];
        }

        // compute audio block
        fDSP->compute(process->frames_count, inputs, outputs);

        return CLAP_PROCESS_CONTINUE;
    }

    // implement note ports extension, always 1 input port
    bool     implementsNotePorts() const noexcept override { return true; }
    uint32_t notePortsCount(bool isInput) const noexcept override { return isInput ? 1 : 0; }

    bool notePortsInfo(uint32_t index, bool isInput,
                       clap_note_port_info_t* info) const noexcept override
    {
        if (!isInput || index != 0) {
            return false;
        }
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, CLAP_NAME_SIZE, "MIDI In");
        info->supported_dialects = CLAP_NOTE_DIALECT_CLAP | CLAP_NOTE_DIALECT_MIDI;
        info->preferred_dialect  = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }

    // implement state extension to save and restore parameter values
    bool implementsState() const noexcept override { return true; }

    bool stateSave(const clap_ostream_t* stream) noexcept override
    {
        if (!stream || !stream->write) {
            return false;
        }
        int paramCount = fUI.getParamsCount();

        // write number of parameters
        if (!stream->write(stream, &paramCount, sizeof(paramCount))) {
            return false;
        }

        // write each parameter value
        for (int i = 0; i < paramCount; ++i) {
            float v = fUI.getParamValue(i);
            if (!stream->write(stream, &v, sizeof(v))) {
                return false;
            }
        }
        return true;
    }

    bool stateLoad(const clap_istream_t* stream) noexcept override
    {
        if (!stream || !stream->read) {
            return false;
        }
        uint32_t paramCount = 0;

        // read number of parameters
        if (!stream->read(stream, &paramCount, sizeof(paramCount))) {
            return false;
        }

        if (paramCount != (uint32_t)fUI.getParamsCount()) {
            return false;
        }

        // read each parameter and set value
        for (uint32_t i = 0; i < paramCount; ++i) {
            float v;
            if (!stream->read(stream, &v, sizeof(v))) {
                return false;
            }
            fUI.setParamValue(i, v);
        }

        // notify host to update parameter display and processing
        if (_host.canUseParams()) {
            _host.paramsRescan(CLAP_PARAM_RESCAN_VALUES | CLAP_PARAM_RESCAN_ALL);
            _host.paramsRequestFlush();
        }

        return true;
    }

    // implement parameter extension methods
    bool     implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override
    {
        return static_cast<uint32_t>(fUI.getParamsCount());
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override
    {
        int paramCount = fUI.getParamsCount();
        if (index >= paramCount) {
            return false;
        }

        std::memset(info, 0, sizeof(*info));
        info->id = index;

        std::string paramName = fUI.getParamShortname(index);
        if (paramName.empty() || paramName == "/") {
            paramName = "param" + std::to_string(index);
        }

        // strip leading slash
        if (!paramName.empty() && paramName[0] == '/') {
            paramName = paramName.substr(1);
        }

        // only show last path segment
        size_t lastSlash = paramName.find_last_of('/');
        if (lastSlash != std::string::npos) {
            paramName = paramName.substr(lastSlash + 1);
        }

        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", paramName.c_str());

        FAUSTFLOAT min  = fUI.getParamMin(index);
        FAUSTFLOAT max  = fUI.getParamMax(index);
        FAUSTFLOAT init = fUI.getParamInit(index);

        info->min_value     = min;
        info->max_value     = max;
        info->default_value = init;
        info->flags         = CLAP_PARAM_IS_AUTOMATABLE;

        std::strncpy(info->module, "Main", sizeof(info->module));
        info->module[sizeof(info->module) - 1] = '\0';

        return true;
    }

    // return parameter value by ID
    bool paramsValue(clap_id id, double* value) noexcept override
    {
        if (!value || id >= (clap_id)fUI.getParamsCount()) {
            return false;
        }
        *value = fUI.getParamValue(id);
        return true;
    }

    // convert text to parameter value (string to double)
    bool paramsTextToValue(clap_id id, const char* text, double* outValue) noexcept override
    {
        if (!text || !outValue || id >= (clap_id)fUI.getParamsCount()) {
            return false;
        }
        try {
            *outValue = std::stod(text);
            return true;
        } catch (...) {
            return false;
        }
    }

    // convert parameter value to text representation
    bool paramsValueToText(clap_id id, double value, char* outBuffer,
                           uint32_t bufferSize) noexcept override
    {
        if (!outBuffer || bufferSize == 0 || id >= (clap_id)fUI.getParamsCount()) {
            return false;
        }
        std::snprintf(outBuffer, bufferSize, "%.3f", value);
        return true;
    }

    // flush pending parameter and MIDI events in the event queue
    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override
    {
        if (!in) {
            return;
        }

        // iterate over all incoming events
        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!hdr) {
                continue;
            }

            // apply parameter changes if the event is valid
            applyParamEventIfValid(hdr);

            // route MIDI events according to polyphony mode
            if (fIsPolyphonic) {
                handlePolyMIDIEvent(hdr);
            } else {
                handleDSPMIDIEvent(hdr);
            }
        }
    }

    // indicate support for audio ports
    bool implementsAudioPorts() const noexcept override { return true; }

    // A DSP with no audio inputs is an instrument and has no input port. The
    // alternative, a port padded to one channel, describes an input the DSP
    // never reads; CLAP has no valid way to spell a zero-channel port, so the
    // port itself has to go.
    uint32_t audioPortsCount(bool isInput) const noexcept override
    {
        if (isInput) {
            return fNumInputs > 0 ? 1 : 0;
        }
        return fNumOutputs > 0 ? 1 : 0;
    }

    // provide information about audio ports to host
    bool audioPortsInfo(uint32_t index, bool isInput,
                        clap_audio_port_info_t* info) const noexcept override
    {
        if (index != 0 || !info) {
            return false;
        }
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", isInput ? "Input" : "Output");

        // No padding: audioPortsCount() already hid the port when the DSP has
        // no channels on that side, so the count here is the real arity.
        info->channel_count = isInput ? fNumInputs : fNumOutputs;

        info->flags = CLAP_AUDIO_PORT_IS_MAIN;

        // In-place processing means the host may hand the same memory as input
        // and output. That is only sound when both ports are the same width;
        // pairing a 4-in port with an 8-out one (fourSourcesToOcto) would let
        // the host alias buffers of different sizes.
        info->in_place_pair = (fNumInputs == fNumOutputs) ? 0 : CLAP_INVALID_ID;
        return true;
    }

    // expose base class method to retrieve underlying CLAP plugin pointer
    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host)
    {
        return (new APlugin(&gain_desc, host))->clapPlugin();
    }
};

// return total number of plugins provided by this factory
static uint32_t plugin_count(const clap_plugin_factory_t*)
{
    return 1;
}

// return plugin descriptor for given index; only one plugin here
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index)
{
    return (index == 0) ? &gain_desc : nullptr;
}

// factory method to create new plugin instance
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host,
                                          const char* plugin_id)
{
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        return APlugin::create(host);
    }
    return nullptr;
}

// single plugin factory structure describing factory callbacks
constexpr static clap_plugin_factory_t gain_factory = {.get_plugin_count      = plugin_count,
                                                       .get_plugin_descriptor = plugin_desc,
                                                       .create_plugin         = plugin_create};

// entry point initialisation and deinitialisation
static bool entry_init(const char* path)
{
    return true;
}
static void entry_deinit()
{
}

// C linkage block exporting the CLAP factory to the host
extern "C" {

// retrieve the requested factory by its ID string
CLAP_EXPORT const void* clap_get_factory(const char* factory_id)
{
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) {
        return &gain_factory;
    }
    return nullptr;
}

// define the CLAP plugin entry point structure
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {CLAP_VERSION_INIT, entry_init, entry_deinit,
                                                    clap_get_factory};
}
