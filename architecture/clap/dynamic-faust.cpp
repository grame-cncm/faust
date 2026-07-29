// Created by Facundo Franchino

/**
 * CLAP architecture for Faust with dynamic DSP compilation.
 *
 * This plugin compiles Faust programs at runtime with the interpreter backend
 * and reloads them while the host keeps playing, so a DSP can be edited inside
 * a running session without rebuilding a plugin.
 *
 * Threading model. Compiling a Faust program takes milliseconds to seconds; an
 * audio callback has about ten. So nothing is compiled on the audio thread:
 *
 *   - a worker thread watches the control file and the DSP file, compiles, and
 *     builds a complete DspBundle;
 *   - the bundle is published with one atomic store;
 *   - the audio thread loads that pointer once per block and does nothing else
 *     out of the ordinary: no allocation, no lock, no I/O;
 *   - the replaced bundle is retired, and freed only once every reader has
 *     provably left it.
 *
 * A failed compilation is a no-op: the bundle is never published and the
 * running DSP keeps playing. That is the common case while editing, not an
 * edge case.
 *
 * Use:
 *   export FAUST_DSP_FILE=/path/to/your.dsp   then load the plugin, or
 *   run faust-hot-reload.py, which writes the control file for you.
 *
 * Environment:
 *   FAUST_DSP_FILE          DSP loaded at instantiation
 *   FAUST_CLAP_CONTROL      control file to watch (default: a private
 *                           per-user path, see controlFilePath())
 *   FAUST_CLAP_PARAM_SLOTS  number of CLAP parameter slots (default 32)
 */

#include <clap/events.h>
#include <clap/helpers/host-proxy.hh>
#include <clap/helpers/plugin.hh>

#include <sys/stat.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "clap-dsp-bundle.h"

#ifdef _WIN32
#include <direct.h>
#endif

#define PLUGIN_ID "org.grame.faust.dynamic"
#define PLUGIN_NAME "Faust Dynamic"
#define PLUGIN_VENDOR "GRAME"
#define PLUGIN_VERSION "1.0.0"
#define PLUGIN_DESCRIPTION "Dynamic Faust DSP Compiler for CLAP"
#define PLUGIN_URL "https://faust.grame.fr"

using Base = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                   clap::helpers::CheckingLevel::Minimal>;

// The plugin presents fixed stereo ports, because CLAP requires a stable port
// description and the DSP behind them changes. A DSP with a different arity is
// adapted (see gather/scatter in process); one wider than this is refused, so
// that compute() is never handed an array shorter than the arity it expects.
static const int kMaxDspChannels = 8;
static const int kHostChannels   = 2;

// Parameter slots. A host cannot be told the parameter count changed on every
// edit, so slots are allocated once and kept by address across reloads.
static const int kDefaultParamSlots = 32;
static const int kMaxParamSlots     = 512;

static const char* features[] = {CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr};

constexpr static clap_plugin_descriptor_t desc = {.clap_version = CLAP_VERSION_INIT,
                                                  .id           = PLUGIN_ID,
                                                  .name         = PLUGIN_NAME,
                                                  .vendor       = PLUGIN_VENDOR,
                                                  .url          = PLUGIN_URL,
                                                  .manual_url   = "",
                                                  .support_url  = "",
                                                  .version      = PLUGIN_VERSION,
                                                  .description  = PLUGIN_DESCRIPTION,
                                                  .features     = features};

static void logLine(const std::string& message)
{
    std::cerr << "[Faust Dynamic] " << message << "\n";
}

static bool makeDirectory(const std::string& path)
{
#ifdef _WIN32
    return _mkdir(path.c_str()) == 0 || errno == EEXIST;
#else
    // 0700: the control file names a program this plugin will compile and run,
    // so it must not be writable by other users. A world-writable /tmp path let
    // any local user choose what somebody else's DAW loads.
    return mkdir(path.c_str(), 0700) == 0 || errno == EEXIST;
#endif
}

// Directory for this user's private plugin state, created if needed.
static std::string userPrivateDir()
{
    const char* home = getenv("HOME");
#ifdef _WIN32
    const char* base = getenv("LOCALAPPDATA");
    std::string dir  = base ? std::string(base) + "\\faust-clap" : std::string("faust-clap");
#elif defined(__APPLE__)
    std::string dir =
        home ? std::string(home) + "/Library/Application Support/faust-clap" : std::string();
#else
    const char* runtime = getenv("XDG_RUNTIME_DIR");
    const char* config  = getenv("XDG_CONFIG_HOME");
    std::string dir;
    if (runtime) {
        dir = std::string(runtime) + "/faust-clap";
    } else if (config) {
        dir = std::string(config) + "/faust-clap";
    } else if (home) {
        dir = std::string(home) + "/.config/faust-clap";
    }
#endif
    if (dir.empty()) {
        return "";
    }
    makeDirectory(dir);
    return dir;
}

// The file an external tool writes to tell this plugin what to load.
//
// FAUST_CLAP_CONTROL overrides it, which is what makes two instances able to
// follow two different programs: the old build hardcoded one /tmp path, so
// every instance in the session was tied to the same DSP.
static std::string controlFilePath()
{
    const char* explicitPath = getenv("FAUST_CLAP_CONTROL");
    if (explicitPath && *explicitPath) {
        return explicitPath;
    }

    const std::string dir = userPrivateDir();
    if (dir.empty()) {
        return "";
    }
#ifdef _WIN32
    return dir + "\\current-dsp.txt";
#else
    return dir + "/current-dsp.txt";
#endif
}

static bool isRegularFile(const std::string& path)
{
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return S_ISREG(info.st_mode);
}

// Identity of a file for change detection.
//
// Deliberately the content and not the metadata. Size plus mtime misses an
// edit that keeps the length inside one timestamp tick -- swapping between two
// DSP paths of equal length is exactly that case, and HFS+ still has one-second
// mtime granularity. These files are a few kilobytes and are read five times a
// second, so hashing them costs nothing measurable and cannot be fooled.
struct FileState {
    bool               exists = false;
    unsigned long long hash   = 0;

    bool operator!=(const FileState& other) const
    {
        return exists != other.exists || hash != other.hash;
    }
};

static FileState stateOf(const std::string& path)
{
    FileState state;
    if (path.empty()) {
        return state;
    }
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return state;
    }

    // FNV-1a: we need "did this change", not cryptographic strength.
    unsigned long long hash = 1469598103934665603ULL;
    char               buffer[4096];
    while (file.read(buffer, sizeof buffer) || file.gcount() > 0) {
        const std::streamsize got = file.gcount();
        for (std::streamsize i = 0; i < got; ++i) {
            hash ^= (unsigned char)buffer[i];
            hash *= 1099511628211ULL;
        }
    }
    state.exists = true;
    state.hash   = hash;
    return state;
}

// Readers announce themselves so the worker can tell when a retired bundle has
// become unreachable. Two atomic increments: no allocation and no lock, so the
// audio thread can use it.
struct ReadGuard {
    std::atomic<int>& fCount;
    explicit ReadGuard(std::atomic<int>& count) : fCount(count)
    {
        fCount.fetch_add(1, std::memory_order_acquire);
    }
    ~ReadGuard() { fCount.fetch_sub(1, std::memory_order_release); }
    ReadGuard(const ReadGuard&)            = delete;
    ReadGuard& operator=(const ReadGuard&) = delete;
};

class FaustDynamicPlugin final : public Base {
   public:
    using Base::clapPlugin;

    FaustDynamicPlugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
        : Base(descriptor, host)
    {
        fSlotCount   = readSlotCount();
        fControlPath = controlFilePath();
    }

    ~FaustDynamicPlugin()
    {
        stopWorker();
        // The host has destroyed the plugin, so no audio thread can be inside
        // process() any more: whatever is still retired is now unreachable.
        delete fActive.load(std::memory_order_relaxed);
        for (DspBundle* bundle : fRetired) {
            delete bundle;
        }
    }

    bool init() noexcept override
    {
        if (fControlPath.empty()) {
            logLine("warning: no private directory available, hot reload disabled");
        }

        std::string path = readControlFile();
        if (path.empty()) {
            const char* fromEnv = getenv("FAUST_DSP_FILE");
            if (fromEnv && *fromEnv) {
                path = fromEnv;
            }
        }

        std::string error;
        DspBundle*  bundle = nullptr;
        if (!path.empty()) {
            bundle = DspBundle::fromFile(path, fSampleRate, fSlotCount, nullptr, error);
            if (!bundle) {
                logLine("cannot load " + path + ": " + error);
            }
        }
        if (!bundle) {
            // A plugin that failed to instantiate is a plugin the host drops.
            // Passing audio through is a far better answer to "no DSP yet" than
            // disappearing from the session.
            bundle = DspBundle::fromString("default", defaultDSP(), fSampleRate, fSlotCount,
                                           nullptr, error);
            if (!bundle) {
                logLine("cannot compile the built-in default DSP: " + error);
                return false;
            }
            logLine(path.empty() ? "no DSP specified, passing audio through"
                                 : "passing audio through until " + path + " compiles");
        }

        publish(bundle);
        // Watch what was *asked* for, not what ended up loaded. A DSP that
        // failed to compile is the case where watching matters most: the fix is
        // one edit away, and pointing the watcher at the fallback instead would
        // leave the plugin deaf to it.
        fWatchedPath  = path;
        fControlState = stateOf(fControlPath);
        fDSPState     = stateOf(fWatchedPath);
        reportBundle(*bundle);

        startWorker();
        return true;
    }

    bool activate(double sampleRate, uint32_t, uint32_t maxFrames) noexcept override
    {
        fSampleRate = int(sampleRate);
        fMaxFrames  = maxFrames;

        // The only allocation in the audio path, and it happens here, where
        // allocation is allowed.
        fInScratch.assign(size_t(kMaxDspChannels) * maxFrames, 0);
        fOutScratch.assign(size_t(kMaxDspChannels) * maxFrames, 0);

        // No audio thread is running yet, so re-initialising in place is safe.
        DspBundle* bundle = fActive.load(std::memory_order_acquire);
        if (!bundle) {
            return false;
        }
        bundle->getDSP()->init(fSampleRate);
        return true;
    }

    clap_process_status process(const clap_process_t* process) noexcept override
    {
        ReadGuard  guard(fReaders);
        DspBundle* bundle = fActive.load(std::memory_order_acquire);
        if (!bundle) {
            return CLAP_PROCESS_ERROR;
        }

        if (process->audio_outputs_count < 1) {
            return CLAP_PROCESS_ERROR;
        }
        const clap_audio_buffer_t& out = process->audio_outputs[0];
        if (!out.data32) {
            return CLAP_PROCESS_ERROR;
        }

        const clap_audio_buffer_t* in =
            (process->audio_inputs_count > 0) ? &process->audio_inputs[0] : nullptr;

        applyEvents(process->in_events, *bundle);

        // A reload changes the plugin's own parameter values: controls that did
        // not survive the edit are back at their defaults. The host has no way
        // to learn that by itself -- it keeps showing, and automating, the
        // values it cached, until something else makes it re-read them. So the
        // new values are pushed out once, right after the swap.
        if (fAnnounceValues.exchange(false, std::memory_order_acq_rel)) {
            announceValues(process->out_events, *bundle);
        }

        const uint32_t frames = process->frames_count;
        if (frames > fMaxFrames) {
            return CLAP_PROCESS_ERROR;
        }

        const int numInputs  = bundle->getNumInputs();
        const int numOutputs = bundle->getNumOutputs();

        FAUSTFLOAT* inputs[kMaxDspChannels];
        FAUSTFLOAT* outputs[kMaxDspChannels];

        // Gather: give the DSP exactly the channel count it was compiled for,
        // silence-filling anything the host does not provide.
        for (int c = 0; c < numInputs; ++c) {
            FAUSTFLOAT* channel = &fInScratch[size_t(c) * fMaxFrames];
            inputs[c]           = channel;
            if (in && in->data32 && c < int(in->channel_count)) {
                for (uint32_t i = 0; i < frames; ++i) {
                    channel[i] = FAUSTFLOAT(in->data32[c][i]);
                }
            } else {
                std::memset(channel, 0, frames * sizeof(FAUSTFLOAT));
            }
        }
        for (int c = 0; c < numOutputs; ++c) {
            outputs[c] = &fOutScratch[size_t(c) * fMaxFrames];
        }

        bundle->getDSP()->compute(int(frames), inputs, outputs);

        // Scatter: a mono DSP feeds both host channels, a wider one is
        // truncated to the stereo port the plugin declares.
        for (uint32_t c = 0; c < out.channel_count; ++c) {
            float* target = out.data32[c];
            if (numOutputs == 0) {
                std::memset(target, 0, frames * sizeof(float));
                continue;
            }
            const FAUSTFLOAT* source = outputs[std::min(int(c), numOutputs - 1)];
            for (uint32_t i = 0; i < frames; ++i) {
                target[i] = float(source[i]);
            }
        }

        return CLAP_PROCESS_CONTINUE;
    }

    // --- parameters --------------------------------------------------------

    bool     implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return uint32_t(fSlotCount); }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override
    {
        if (int(index) >= fSlotCount || !info) {
            return false;
        }

        ReadGuard  guard(fReaders);
        DspBundle* bundle = fActive.load(std::memory_order_acquire);

        std::memset(info, 0, sizeof(*info));
        info->id = index;

        // Everything here except the name and the default is the same for every
        // slot, for the lifetime of the plugin. Announcing a real min/max would
        // mean re-announcing it on every reload, which CLAP only allows with
        // CLAP_PARAM_RESCAN_ALL while the plugin is deactivated -- a running
        // host is right to ignore that, and the UI then never updates. The real
        // range is reported through paramsValueToText() instead.
        info->min_value = 0.0;
        info->max_value = 1.0;
        info->flags     = CLAP_PARAM_IS_AUTOMATABLE;

        const int param = bundle ? bundle->slotToParam(index) : -1;
        if (param < 0) {
            std::snprintf(info->name, CLAP_NAME_SIZE, "Unused %u", index + 1);
            info->default_value = 0.0;
            return true;
        }

        const CLAPMapUI& ui   = bundle->getUI();
        std::string      name = ui.getParamShortname(param);
        if (name.empty()) {
            name = "param" + std::to_string(index);
        }
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", name.c_str());
        info->default_value = ui.normalize(param, ui.getParamInit(param));
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override
    {
        if (!value || int(id) >= fSlotCount) {
            return false;
        }

        ReadGuard  guard(fReaders);
        DspBundle* bundle = fActive.load(std::memory_order_acquire);
        const int  param  = bundle ? bundle->slotToParam(id) : -1;
        if (param < 0) {
            *value = 0.0;
            return true;
        }
        const CLAPMapUI& ui = bundle->getUI();
        *value              = ui.normalize(param, ui.getParamValue(param));
        return true;
    }

    // The host shows 0..1; this is where the user sees what the control really
    // holds, in the DSP's own units.
    bool paramsValueToText(clap_id id, double value, char* display, uint32_t size) noexcept override
    {
        if (!display || size == 0 || int(id) >= fSlotCount) {
            return false;
        }
        ReadGuard  guard(fReaders);
        DspBundle* bundle = fActive.load(std::memory_order_acquire);
        const int  param  = bundle ? bundle->slotToParam(id) : -1;
        if (param < 0) {
            std::snprintf(display, size, "-");
            return true;
        }
        std::snprintf(display, size, "%.4g", double(bundle->getUI().denormalize(param, value)));
        return true;
    }

    bool paramsTextToValue(clap_id id, const char* display, double* value) noexcept override
    {
        if (!display || !value || int(id) >= fSlotCount) {
            return false;
        }
        ReadGuard  guard(fReaders);
        DspBundle* bundle = fActive.load(std::memory_order_acquire);
        const int  param  = bundle ? bundle->slotToParam(id) : -1;
        if (param < 0) {
            return false;
        }
        char*        end   = nullptr;
        const double typed = std::strtod(display, &end);
        if (end == display) {
            return false;
        }
        *value = bundle->getUI().normalize(param, FAUSTFLOAT(typed));
        return true;
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override
    {
        ReadGuard  guard(fReaders);
        DspBundle* bundle = fActive.load(std::memory_order_acquire);
        if (bundle) {
            applyEvents(in, *bundle);
        }
    }

    // --- audio ports -------------------------------------------------------

    bool     implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool) const noexcept override { return 1; }

    bool audioPortsInfo(uint32_t index, bool isInput,
                        clap_audio_port_info_t* info) const noexcept override
    {
        if (index != 0 || !info) {
            return false;
        }
        std::memset(info, 0, sizeof(*info));
        info->id = 0;
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", isInput ? "Input" : "Output");
        info->channel_count = kHostChannels;
        info->flags         = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type     = CLAP_PORT_STEREO;
        // Never in place: the DSP behind the port changes, and a reload can
        // turn a program that reads its input before writing into one that does
        // not. Sharing the buffer would make that difference audible.
        info->in_place_pair = CLAP_INVALID_ID;
        return true;
    }

    const void* get_extension(const char* id) noexcept
    {
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) {
            return (const clap_plugin_params_t*)this;
        }
        if (std::strcmp(id, CLAP_EXT_AUDIO_PORTS) == 0) {
            return (const clap_plugin_audio_ports_t*)this;
        }
        return nullptr;
    }

    static const clap_plugin_t* create(const clap_host_t* host)
    {
        return (new FaustDynamicPlugin(&desc, host))->clapPlugin();
    }

   private:
    static std::string defaultDSP() { return "process = _, _;"; }

    static int readSlotCount()
    {
        const char* text = getenv("FAUST_CLAP_PARAM_SLOTS");
        if (!text || !*text) {
            return kDefaultParamSlots;
        }
        const int value = std::atoi(text);
        if (value < 1 || value > kMaxParamSlots) {
            logLine("FAUST_CLAP_PARAM_SLOTS out of range, using " +
                    std::to_string(kDefaultParamSlots));
            return kDefaultParamSlots;
        }
        return value;
    }

    // Translate host parameter events through the slot table. Runs on the audio
    // thread: no allocation, no logging.
    void applyEvents(const clap_input_events_t* events, DspBundle& bundle) const noexcept
    {
        if (!events) {
            return;
        }
        CLAPMapUI& ui = bundle.getUI();
        for (uint32_t i = 0, count = events->size(events); i < count; ++i) {
            const clap_event_header_t* header = events->get(events, i);
            if (!header || header->space_id != CLAP_CORE_EVENT_SPACE_ID) {
                continue;
            }
            if (header->type != CLAP_EVENT_PARAM_VALUE) {
                continue;
            }

            const auto* event = reinterpret_cast<const clap_event_param_value_t*>(header);
            const int   param = bundle.slotToParam(event->param_id);
            if (param < 0) {
                continue;
            }
            ui.setParamValue(param, ui.denormalize(param, event->value));
        }
    }

    // Tell the host every slot's current value. Bounded by the slot count and
    // allocation-free, so it is safe from the audio thread; try_push may refuse,
    // in which case the host simply keeps what it had.
    void announceValues(const clap_output_events_t* out, DspBundle& bundle) const noexcept
    {
        if (!out) {
            return;
        }
        const CLAPMapUI& ui = bundle.getUI();
        for (int slot = 0; slot < fSlotCount; ++slot) {
            const int param = bundle.slotToParam(uint32_t(slot));

            clap_event_param_value_t event;
            std::memset(&event, 0, sizeof(event));
            event.header.size     = sizeof(event);
            event.header.time     = 0;
            event.header.space_id = CLAP_CORE_EVENT_SPACE_ID;
            event.header.type     = CLAP_EVENT_PARAM_VALUE;
            event.param_id        = clap_id(slot);
            event.note_id         = -1;
            event.port_index      = -1;
            event.channel         = -1;
            event.key             = -1;
            event.value = (param >= 0) ? ui.normalize(param, ui.getParamValue(param)) : 0.0;

            out->try_push(out, &event.header);
        }
    }

    // Read the control file and validate what it names. Anything unusable is
    // reported and ignored: the plugin keeps playing whatever it already has.
    std::string readControlFile() const
    {
        if (fControlPath.empty()) {
            return "";
        }
        std::ifstream file(fControlPath);
        if (!file.is_open()) {
            return "";
        }

        std::string path;
        std::getline(file, path);
        const size_t first = path.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) {
            return "";
        }
        const size_t last = path.find_last_not_of(" \t\r\n");
        path              = path.substr(first, last - first + 1);

        if (path.find('\0') != std::string::npos) {
            return "";
        }
        if (!isRegularFile(path)) {
            logLine("control file names " + path + ", which is not a readable file");
            return "";
        }
        return path;
    }

    void publish(DspBundle* bundle) noexcept
    {
        DspBundle* previous = fActive.exchange(bundle, std::memory_order_acq_rel);
        if (previous) {
            fRetired.push_back(previous);
        }
        fAnnounceValues.store(true, std::memory_order_release);
    }

    // Free retired bundles once no reader can hold one. A reader increments
    // fReaders before loading the pointer, so observing zero *after* the swap
    // proves every in-flight reader has left, and any reader starting later
    // sees the new bundle.
    void reclaim()
    {
        if (fRetired.empty()) {
            return;
        }
        if (fReaders.load(std::memory_order_acquire) != 0) {
            return;
        }
        for (DspBundle* bundle : fRetired) {
            delete bundle;
        }
        fRetired.clear();
    }

    void reportBundle(const DspBundle& bundle) const
    {
        logLine("loaded " +
                (bundle.getPath().empty() ? std::string("default DSP") : bundle.getPath()) + ": " +
                std::to_string(bundle.getNumInputs()) + " in, " +
                std::to_string(bundle.getNumOutputs()) + " out, " +
                std::to_string(bundle.getParamsCount()) + " parameters");

        for (const std::string& address : bundle.getUnreachableParams()) {
            logLine("warning: no free slot for " + address +
                    " -- raise FAUST_CLAP_PARAM_SLOTS (currently " + std::to_string(fSlotCount) +
                    ")");
        }
        if (bundle.getNumOutputs() > kHostChannels) {
            logLine("warning: DSP has " + std::to_string(bundle.getNumOutputs()) +
                    " outputs, the plugin port carries " + std::to_string(kHostChannels));
        }
    }

    void startWorker()
    {
        fRunning.store(true, std::memory_order_release);
        fWorker = std::thread([this] { workerLoop(); });
    }

    void stopWorker()
    {
        fRunning.store(false, std::memory_order_release);
        if (fWorker.joinable()) {
            fWorker.join();
        }
    }

    // Everything expensive happens here: file polling, compilation, allocation
    // and reclamation. Never on the audio thread.
    void workerLoop()
    {
        while (fRunning.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if (!fRunning.load(std::memory_order_acquire)) {
                break;
            }

            reclaim();

            // A filesystem watcher would report the same events; polling two
            // paths five times a second costs nothing measurable and removes a
            // third-party dependency the build could not satisfy.
            const FileState control = stateOf(fControlPath);
            const FileState dsp     = stateOf(fWatchedPath);

            std::string wanted = fWatchedPath;
            bool        reload = false;

            if (control != fControlState) {
                fControlState          = control;
                const std::string next = readControlFile();
                if (!next.empty() && next != fWatchedPath) {
                    wanted = next;
                    reload = true;
                }
            }
            if (!reload && dsp != fDSPState) {
                fDSPState = dsp;
                if (dsp.exists && !fWatchedPath.empty()) {
                    reload = true;
                }
            }
            if (!reload) {
                continue;
            }

            reloadFrom(wanted);
        }
    }

    void reloadFrom(const std::string& path)
    {
        DspBundle*  current = fActive.load(std::memory_order_acquire);
        std::string error;
        DspBundle*  bundle = DspBundle::fromFile(path, fSampleRate, fSlotCount, current, error);

        if (!bundle) {
            // The running DSP is untouched. This is the whole reason a bundle
            // is built before anything is replaced.
            logLine("reload failed, keeping the current DSP: " + error);
            return;
        }
        if (bundle->getNumInputs() > kMaxDspChannels || bundle->getNumOutputs() > kMaxDspChannels) {
            logLine("reload refused: " + path + " has more than " +
                    std::to_string(kMaxDspChannels) + " channels");
            delete bundle;
            return;
        }

        publish(bundle);
        fWatchedPath = path;
        fDSPState    = stateOf(path);
        reportBundle(*bundle);

        // Tell the host to re-read the slots. Deliberately not
        // CLAP_PARAM_RESCAN_ALL: that one is only legal while the plugin is
        // deactivated, so a running host ignores it and the UI keeps showing the
        // previous DSP's controls. These three take effect immediately, which is
        // why paramsInfo() keeps its ranges invariant. Requested from the main
        // thread, and only if the host implements the parameters extension: the
        // helpers assert rather than no-op.
        runOnMainThread([this] {
            if (_host.canUseParams()) {
                _host.paramsRescan(CLAP_PARAM_RESCAN_INFO | CLAP_PARAM_RESCAN_VALUES |
                                   CLAP_PARAM_RESCAN_TEXT);
            }
        });
    }

    std::atomic<DspBundle*>  fActive{nullptr};
    std::atomic<bool>        fAnnounceValues{false};
    mutable std::atomic<int> fReaders{0};
    std::vector<DspBundle*>  fRetired;  // worker thread only

    std::thread       fWorker;
    std::atomic<bool> fRunning{false};

    std::string fControlPath;
    std::string fWatchedPath;
    FileState   fControlState;
    FileState   fDSPState;

    int      fSlotCount  = kDefaultParamSlots;
    int      fSampleRate = 44100;
    uint32_t fMaxFrames  = 0;

    std::vector<FAUSTFLOAT> fInScratch;
    std::vector<FAUSTFLOAT> fOutScratch;
};

// --- factory ---------------------------------------------------------------

static uint32_t plugin_count(const clap_plugin_factory_t*)
{
    return 1;
}

static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index)
{
    return (index == 0) ? &desc : nullptr;
}

static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host,
                                          const char* plugin_id)
{
    if (std::strcmp(plugin_id, desc.id) == 0) {
        return FaustDynamicPlugin::create(host);
    }
    return nullptr;
}

constexpr static clap_plugin_factory_t factory = {.get_plugin_count      = plugin_count,
                                                  .get_plugin_descriptor = plugin_desc,
                                                  .create_plugin         = plugin_create};

static bool entry_init(const char*)
{
    return true;
}

static void entry_deinit()
{
}

extern "C" {
CLAP_EXPORT const void* clap_get_factory(const char* factory_id)
{
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) {
        return &factory;
    }
    return nullptr;
}

CLAP_EXPORT const clap_plugin_entry_t clap_entry = {CLAP_VERSION_INIT, entry_init, entry_deinit,
                                                    clap_get_factory};
}
