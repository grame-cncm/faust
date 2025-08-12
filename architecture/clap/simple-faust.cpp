//Created by Facundo Franchino

/**
 * CLAP architecture for Faust with dynamic DSP compilation.
 * 
 * This architecture allows loading Faust DSP files at runtime using the interpreter,
 * enabling rapid DSP development without recompiling the entire plugin.
 * 
 * Usage:
 * 1. set environment variable: export FAUST_DSP_FILE="/path/to/your.dsp"  
 * 2. launch DAW with the environment variable set
 * 3. load this plugin - it will compile and load your DSP file
 * 
 * the plugin supports up to 16 parameters. If your DSP has fewer parameters,
 * the unused parameter slots will be hidden from the DAW interface.
 * 
 * @author GRAME
 * @version 1.0.0
 */

#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include "interpreter-clap.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <sys/stat.h>
#include <fstream>
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>

// Plugin identification
#define PLUGIN_ID "org.grame.faust.dynamic"
#define PLUGIN_NAME "Faust Dynamic"
#define PLUGIN_VENDOR "GRAME"
#define PLUGIN_VERSION "1.0.0"
#define PLUGIN_DESCRIPTION "Dynamic Faust DSP Compiler for CLAP"
#define PLUGIN_URL "https://faust.grame.fr"
#define MAX_PARAMS 16  // maximum number of parameters supported

/**
 * Enhanced UI class that stores parameter metadata for CLAP parameter interface
 */
struct DynamicUI : public MapUI {
    std::vector<FAUSTFLOAT> fMins, fMaxs, fInits;
    std::vector<std::string> fLabels;

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                             FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        addParamMetadata(label, init, min, max);
    }

    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                           FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        addParamMetadata(label, init, min, max);
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                     FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        addParamMetadata(label, init, min, max);
    }

private:
    void addParamMetadata(const char* label, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max) {
        fMins.push_back(min);
        fMaxs.push_back(max);
        fInits.push_back(init);
        fLabels.push_back(label ? label : "");
    }

public:

    // Parameter access methods
    FAUSTFLOAT getMin(int i) const { return (i < fMins.size()) ? fMins[i] : 0.f; }
    FAUSTFLOAT getMax(int i) const { return (i < fMaxs.size()) ? fMaxs[i] : 1.f; }
    FAUSTFLOAT getInit(int i) const { return (i < fInits.size()) ? fInits[i] : 0.5f; }
    const std::string& getLabel(int i) const { 
        static const std::string empty;
        return (i < fLabels.size()) ? fLabels[i] : empty;
    }
    
    void setValue(int i, FAUSTFLOAT val) {
        if (i >= 0 && i < getParamsCount()) {
            std::string addr = getParamAddress(i);
            setParamValue(addr, val);
        }
    }
    
    FAUSTFLOAT getValue(int i) {
        if (i >= 0 && i < getParamsCount()) {
            std::string addr = getParamAddress(i);
            return getParamValue(addr);
        }
        return 0.f;
    }
};

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

static const char* features[] = { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr };

constexpr static clap_plugin_descriptor_t desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = PLUGIN_ID,
    .name = PLUGIN_NAME,
    .vendor = PLUGIN_VENDOR,
    .url = PLUGIN_URL,
    .manual_url = "",
    .support_url = "",
    .version = PLUGIN_VERSION,
    .description = PLUGIN_DESCRIPTION,
    .features = features
};

/**
 * Main plugin class implementing dynamic Faust DSP compilation
 */
class FaustDynamicPlugin final : public Base {
private:
    InterpreterCLAP fInterpreter;   // faust interpreter for dynamic compilation
    dsp* fDSP = nullptr;            // currently loaded DSP instance
    DynamicUI fUI;                  // UI interface for parameter management
    std::string fCurrentDSPPath;    // path to currently loaded DSP file
    int fActiveDSPParams = 0;       // number of parameters in current DSP
    
    // Hot reload functionality
    std::thread fWatcher;           // file watching thread
    std::atomic<bool> fWatcherRunning{false};  // thread control
    std::atomic<bool> fNeedsReload{false};     // reload flag
    std::atomic<bool> fReloadInProgress{false}; // prevent concurrent reloads
    time_t fLastModTime = 0;        // last file modification time
    time_t fLastConfigModTime = 0;  // last config file modification time
    std::string fConfigPath = "/tmp/faust-current-dsp.txt"; // config file path
    
    // Debug logging
    void logDebug(const std::string& msg) {
        std::ofstream logFile("/tmp/faust-dynamic.log", std::ios::app);
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        logFile << std::ctime(&time_t) << " " << msg << std::endl;
    }
    
    // read DSP path from config file
    std::string readConfigFile() {
        std::ifstream configFile(fConfigPath);
        if (configFile.is_open()) {
            std::string path;
            std::getline(configFile, path);
            // trim whitespace
            path.erase(0, path.find_first_not_of(" \t\r\n"));
            path.erase(path.find_last_not_of(" \t\r\n") + 1);
            return path;
        }
        return "";
    }

public:
    FaustDynamicPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
        : Base(desc, host) {}
    
    ~FaustDynamicPlugin() {
        // clean shutdown of file watcher
        fWatcherRunning = false;
        if (fWatcher.joinable()) {
            fWatcher.join();
        }
    }
    
    /**
     * Initialize the plugin by loading the DSP file specified in FAUST_DSP_FILE environment variable
     */

    bool init() noexcept override {
        logDebug("Plugin init() called");
        
        // try config file first, then environment variable, then default
        std::string dspPath = readConfigFile();
        if (dspPath.empty()) {
            const char* envDspFile = getenv("FAUST_DSP_FILE");
            if (envDspFile && strlen(envDspFile) > 0) {
                dspPath = envDspFile;
                logDebug("Using FAUST_DSP_FILE environment variable: " + dspPath);
            }
        } else {
            logDebug("Using config file DSP path: " + dspPath);
        }
        
        if (dspPath.empty()) {
            // no DSP file specified - load a simple default DSP
            logDebug("No DSP file specified, using default DSP");
            std::cerr << "[Faust Dynamic] No DSP file specified, using default DSP\n";
            std::string defaultCode = R"(
                import("stdfaust.lib");
                gain = hslider("Gain", 0.5, 0, 1, 0.01);
                process = _ * gain, _ * gain;
            )";
            
            if (!fInterpreter.loadFromString("default", defaultCode, 44100)) {
                std::cerr << "[Faust Dynamic] ERROR: Failed to load default DSP\n";
                return false;
            }
        } else {
            // load DSP file from config file or environment variable
            fCurrentDSPPath = dspPath;
            logDebug("Loading DSP file: " + dspPath);
            std::cerr << "[Faust Dynamic] Loading DSP file: " << dspPath << "\n";
            
            if (!fInterpreter.loadFromFile(dspPath.c_str(), 44100)) {
                std::cerr << "[Faust Dynamic] ERROR: Failed to load DSP file: " << dspPath << "\n";
                std::cerr << "[Faust Dynamic] Falling back to default DSP\n";
                
                // fall back to default DSP on load failure
                std::string defaultCode = R"(
                    import("stdfaust.lib");
                    gain = hslider("Gain", 0.5, 0, 1, 0.01);
                    process = _ * gain, _ * gain;
                )";
                
                if (!fInterpreter.loadFromString("default", defaultCode, 44100)) {
                    std::cerr << "[Faust Dynamic] ERROR: Failed to load default DSP\n";
                    return false;
                }
                fCurrentDSPPath.clear();
            }
        }

        // get the compiled DSP instance
        fDSP = fInterpreter.getDSP();
        if (!fDSP) {
            std::cerr << "[Faust Dynamic] ERROR: No DSP instance available\n";
            return false;
        }

        // build the user interface to discover parameters
        fDSP->buildUserInterface(&fUI);
        fActiveDSPParams = fUI.getParamsCount();
        
        // initialise all parameters to their default values
        for (int i = 0; i < fActiveDSPParams; ++i) {
            fUI.setValue(i, fUI.getInit(i));
        }

        logDebug("Successfully loaded DSP with " + std::to_string(fActiveDSPParams) + " parameters");
        std::cerr << "[Faust Dynamic] Successfully loaded DSP with " << fActiveDSPParams 
                  << " parameters (max " << MAX_PARAMS << " supported)\n";
        
        // start hot reload watching if we have a DSP file
        if (!fCurrentDSPPath.empty()) {
            logDebug("Starting file watcher for: " + fCurrentDSPPath);
            startFileWatching();
        } else {
            // even without a DSP file, watch for config file changes
            logDebug("Starting config file watcher");
            startFileWatching();
        }
        
        return true;
    }

private:
    /**
     * gget file modification time for hot reload detection
     */
    time_t getFileModTime(const std::string& path) {
        struct stat st;
        if (stat(path.c_str(), &st) == 0) {
            return st.st_mtime;
        }
        return 0;
    }
    
    /**
     * dtart file watching thread for hot reload
     */
    void startFileWatching() {
        if (fWatcherRunning.load()) {
            logDebug("File watcher already running");
            return;
        }
        
        fLastModTime = fCurrentDSPPath.empty() ? 0 : getFileModTime(fCurrentDSPPath);
        fLastConfigModTime = getFileModTime(fConfigPath);
        fWatcherRunning = true;
        logDebug("File watcher thread starting");
        
        fWatcher = std::thread([this]() {
            logDebug("File watcher thread running - watching config and DSP files");
            std::cerr << "[Faust Dynamic] 🔍 Watching config: " << fConfigPath;
            if (!fCurrentDSPPath.empty()) {
                std::cerr << " and DSP: " << fCurrentDSPPath;
            }
            std::cerr << "\n";
            
            while (fWatcherRunning.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                
                // check config file changes
                time_t currentConfigModTime = getFileModTime(fConfigPath);
                if (currentConfigModTime > fLastConfigModTime && currentConfigModTime != 0) {
                    fLastConfigModTime = currentConfigModTime;
                    logDebug("Config file changed, triggering reload");
                    std::cerr << "[Faust Dynamic] 🔥 Config file changed, triggering reload...\n";
                    fNeedsReload = true;
                }
                
                // check DSP file changes (if we have one)
                if (!fCurrentDSPPath.empty()) {
                    time_t currentModTime = getFileModTime(fCurrentDSPPath);
                    if (currentModTime > fLastModTime && currentModTime != 0) {
                        fLastModTime = currentModTime;
                        logDebug("DSP file changed, triggering reload");
                        std::cerr << "[Faust Dynamic] 🔥 DSP file changed, triggering reload...\n";
                        fNeedsReload = true;
                    }
                }
            }
        });
    }
    
    /**
     * perform hot reload of DSP file - called from audio thread
     */
    void performHotReload() {
        fNeedsReload = false;
        
        // check if we need to switch to a new DSP file from config
        std::string newDSPPath = readConfigFile();
        if (!newDSPPath.empty() && newDSPPath != fCurrentDSPPath) {
            // config file changed to point to a different DSP file
            fCurrentDSPPath = newDSPPath;
            fLastModTime = getFileModTime(fCurrentDSPPath);
            logDebug("Switching to new DSP file from config: " + fCurrentDSPPath);
            std::cerr << "[Faust Dynamic] 🔄 Switching to: " << fCurrentDSPPath << "\n";
        } else if (fCurrentDSPPath.empty()) {
            logDebug("No DSP file to reload");
            return;
        } else {
            std::cerr << "[Faust Dynamic] 🔄 Hot reloading: " << fCurrentDSPPath << "\n";
        }
        
        try {
            // store current parameter values
            std::vector<FAUSTFLOAT> oldValues;
            for (int i = 0; i < fActiveDSPParams; ++i) {
                oldValues.push_back(fUI.getValue(i));
            }
            
            // attempt to reload the DSP
            if (fInterpreter.loadFromFile(fCurrentDSPPath.c_str(), 44100)) {
                dsp* newDSP = fInterpreter.getDSP();
                if (newDSP) {
                    // initialise new DSP
                    newDSP->init(44100);
                    
                    // reset UI and rebuild with new DSP
                    fUI = DynamicUI();
                    newDSP->buildUserInterface(&fUI);
                    int newParamCount = fUI.getParamsCount();
                    
                    // restore parameter values for parameters that still exist
                    int minParams = std::min((int)oldValues.size(), newParamCount);
                    for (int i = 0; i < minParams; ++i) {
                        fUI.setValue(i, oldValues[i]);
                    }
                    
                    // initialise any new parameters to defaults
                    for (int i = minParams; i < newParamCount; ++i) {
                        fUI.setValue(i, fUI.getInit(i));
                    }
                    
                    // atomically switch to new DSP
                    fDSP = newDSP;
                    fActiveDSPParams = newParamCount;
                    
                    std::cerr << "[Faust Dynamic] ✅ Hot reload successful: " 
                              << fActiveDSPParams << " parameters\n";
                } else {
                    std::cerr << "[Faust Dynamic] ❌ Hot reload failed: No DSP instance\n";
                }
            } else {
                std::cerr << "[Faust Dynamic] ❌ Hot reload failed: Compilation error\n";
            }
        } catch (...) {
            std::cerr << "[Faust Dynamic] ❌ Hot reload crashed - keeping current DSP\n";
        }
    }

public:

    /**
     * activate the plugin with the given sample rate
     */

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        if (fDSP) {
            fDSP->init(sampleRate);
            return true;
        }
        return false;
    }

    /**
     * process audio and handle parameter events
     */
    clap_process_status process(const clap_process_t* process) noexcept override {
        // handle hot reload if needed
        if (fNeedsReload.load() && !fReloadInProgress.exchange(true)) {
            performHotReload();
            fReloadInProgress = false;
        }
        
        // store local copy to avoid race condition
        dsp* currentDSP = fDSP;
        if (!currentDSP || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        const auto& in = process->audio_inputs[0];
        const auto& out = process->audio_outputs[0];

        // process incoming parameter events
        if (process->in_events) {
            for (uint32_t i = 0; i < process->in_events->size(process->in_events); ++i) {
                const clap_event_header_t* hdr = process->in_events->get(process->in_events, i);
                if (hdr && hdr->space_id == CLAP_CORE_EVENT_SPACE_ID && 
                    hdr->type == CLAP_EVENT_PARAM_VALUE) {
                    const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
                    if (ev->param_id < fActiveDSPParams) {
                        fUI.setValue(ev->param_id, ev->value);
                    }
                }
            }
        }

        // process audio through the DSP
        FAUSTFLOAT* inputs[2] = { in.data32[0], in.data32[1] };
        FAUSTFLOAT* outputs[2] = { out.data32[0], out.data32[1] };
        currentDSP->compute(process->frames_count, inputs, outputs);

        return CLAP_PROCESS_CONTINUE;
    }

    // parameter interface implementation
    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return MAX_PARAMS; }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= MAX_PARAMS) return false;
        
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        
        if (index < fActiveDSPParams) {
            // active DSP parameter
            std::string name = fUI.getParamAddress(index);
            if (name.empty()) name = "param" + std::to_string(index);
            if (name[0] == '/') name = name.substr(1);
            size_t slash = name.find_last_of('/');
            if (slash != std::string::npos) name = name.substr(slash + 1);
            
            std::snprintf(info->name, CLAP_NAME_SIZE, "%s", name.c_str());
            info->min_value = fUI.getMin(index);
            info->max_value = fUI.getMax(index);
            info->default_value = fUI.getInit(index);
            info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        } else {
            // unused parameter slot
            std::snprintf(info->name, CLAP_NAME_SIZE, "Unused_%d", index);
            info->min_value = 0.0;
            info->max_value = 1.0;
            info->default_value = 0.0;
            info->flags = CLAP_PARAM_IS_HIDDEN;
        }
        
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (!value || id >= MAX_PARAMS) return false;
        if (id < fActiveDSPParams) {
            *value = fUI.getValue(id);
        } else {
            *value = 0.0;  // unused slots return 0
        }
        return true;
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        
        // process parameter events
        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (hdr && hdr->space_id == CLAP_CORE_EVENT_SPACE_ID && 
                hdr->type == CLAP_EVENT_PARAM_VALUE) {
                const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
                if (ev->param_id < fActiveDSPParams) {
                    fUI.setValue(ev->param_id, ev->value);
                }
            }
        }
    }

    // audio ports interface
    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool) const noexcept override { return 1; }
    
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0) return false;
        
        std::memset(info, 0, sizeof(*info));
        info->id = 0;
        std::snprintf(info->name, CLAP_NAME_SIZE, "%s", isInput ? "Input" : "Output");
        info->channel_count = 2;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type = CLAP_PORT_STEREO;
        info->in_place_pair = isInput ? CLAP_INVALID_ID : 0;
        
        return true;
    }

    // extension sypport
    const void* get_extension(const char* id) noexcept {
        if (std::strcmp(id, CLAP_EXT_PARAMS) == 0) {
            return (const clap_plugin_params_t*)this;
        }
        if (std::strcmp(id, CLAP_EXT_AUDIO_PORTS) == 0) {
            return (const clap_plugin_audio_ports_t*)this;
        }
        return nullptr;
    }

    // plugin factory method
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new FaustDynamicPlugin(&desc, host))->Base::clapPlugin();
    }
};

// plugin factory implementation
static uint32_t plugin_count(const clap_plugin_factory_t*) { 
    return 1; 
}

static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &desc : nullptr;
}

static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, 
                                          const clap_host_t* host, 
                                          const char* plugin_id) {
    if (std::strcmp(plugin_id, desc.id) == 0) {
        return FaustDynamicPlugin::create(host);
    }
    return nullptr;
}

constexpr static clap_plugin_factory_t factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};

// entry point functions
static bool entry_init(const char*) { return true; }
static void entry_deinit() {}

extern "C" {
    CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
        if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) {
            return &factory;
        }
        return nullptr;
    }

    CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
        CLAP_VERSION_INIT, entry_init, entry_deinit, clap_get_factory
    };
}