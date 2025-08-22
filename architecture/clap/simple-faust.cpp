//Created by Facundo Franchino

/**
 * CLAP architecture for Faust with dynamic DSP compilation.
 * 
 * This architecture allows loading Faust DSP files at runtime using the interpreter,
 * enabling rapid DSP development without recompiling the entire plugin.
 * 
 * use:
 * -set environment variable: export FAUST_DSP_FILE="/path/to/your.dsp"  
 * -launch DAW with the environment variable set
 * -load this plugin - it will compile and load your DSP file
 * 
 * alternatively, you could just run the script faust-hot-reload.py and you'll get a "nicer than command line" GUI to load your favourite dsp files
 * 
 * the plugin supports up to 12 parameters. If your DSP has fewer parameters,
 * the unused parameter slots will be hidden from the DAW interface.
 * 
 * @author Facundo Franchino under the mentorship of Stèphane Letz and Jatin Chowdhury for GSoC 2025
 * @version 1.0.0
 */

#include <faust/dsp/dsp.h>
#include "interpreter-clap.h"
#include "clap-mapui.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <map>
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>
#include <efsw/efsw.h>

// Plugin identification
#define PLUGIN_ID "org.grame.faust.dynamic"
#define PLUGIN_NAME "Faust Dynamic"
#define PLUGIN_VENDOR "GRAME"
#define PLUGIN_VERSION "1.0.0"
#define PLUGIN_DESCRIPTION "Dynamic Faust DSP Compiler for CLAP"
#define PLUGIN_URL "https://faust.grame.fr"
#define MAX_PARAMS 12  // fixed parameter slots for stable hot reloading

// DynamicUI completely removed - using only CLAPMapUI from interpreter

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
    CLAPMapUI* fUI = nullptr;       // UI interface from interpreter (single source of truth)
    std::string fCurrentDSPPath;    // path to currently loaded DSP file
    int fActiveDSPParams = 0;       // number of parameters in current DSP
    int fCurrentSampleRate = 44100; // current session sample rate (updated in activate())
    std::map<std::string, FAUSTFLOAT> fOldParamValues; // for address-based restore
    // --- Stable 12-slot mapping by FAUST address ---
    std::array<std::string, MAX_PARAMS> fSlotAddress{}; // "" means unused slot
    std::array<int, MAX_PARAMS>         fSlotToParam{}; // -1 means unmapped

    // Work buffers to bridge host 32f/64f <-> FAUSTFLOAT
    std::vector<FAUSTFLOAT> fTmpIn[2];
    std::vector<FAUSTFLOAT> fTmpOut[2];
    
    // Hot reload functionality
    efsw_watcher fConfigWatcher = nullptr;      // efsw watcher for config file
    efsw_watcher fDSPWatcher = nullptr;         // efsw watcher for DSP file
    efsw_watchid fConfigWatchID;                // config file watch ID
    efsw_watchid fDSPWatchID;                   // DSP file watch ID
    std::atomic<bool> fNeedsReload{false};      // reload flag
    std::atomic<bool> fReloadInProgress{false}; // prevent concurrent reloads
    std::string fConfigPath = "/tmp/faust-current-dsp.txt"; // config file path
    

    // Rebuild slot<->param mapping using addresses, preserving existing slots when possible.
    void rebuildSlotMapping()
    {
        // reset mapping
        for (int s = 0; s < MAX_PARAMS; ++s) fSlotToParam[s] = -1;

        if (!fUI) return;

        const int newN = fUI->getParamsCount();
        std::vector<int> paramTaken(newN, 0);

        // 1) First pass: keep existing slots if the address still exists
        for (int s = 0; s < MAX_PARAMS; ++s) {
            if (fSlotAddress[s].empty()) continue;
            for (int j = 0; j < newN; ++j) {
                if (!paramTaken[j] && fUI->getParamAddress(j) == fSlotAddress[s]) {
                    fSlotToParam[s] = j;
                    paramTaken[j] = 1;
                    break;
                }
            }
        }

        // 2) Second pass: assign any new (unassigned) params to empty slots
        for (int j = 0; j < newN; ++j) {
            if (paramTaken[j]) continue;
            // find an empty slot
            for (int s = 0; s < MAX_PARAMS; ++s) {
                if (fSlotAddress[s].empty()) {
                    fSlotAddress[s] = fUI->getParamAddress(j);
                    fSlotToParam[s] = j;
                    paramTaken[j] = 1;
                    break;
                }
            }
        }

        // 3) Any slots whose address no longer exists become unused
        for (int s = 0; s < MAX_PARAMS; ++s) {
            if (fSlotToParam[s] == -1) {
                // keep fSlotAddress[s] if you want it to “linger”, or clear it:
                // clearing prevents stale labels/min/max
                fSlotAddress[s].clear();
            }
        }
    }

    // Map CLAP slot id (0..MAX_PARAMS-1) -> current Faust param index (or -1)
    inline int idToParam(clap_id id) const noexcept {
        if (id >= MAX_PARAMS) return -1;
        return fSlotToParam[id];
    }

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

    // Static callback function for config file changes
    static void configFileCallback(efsw_watcher watcher, efsw_watchid watchid, 
                                 const char* dir, const char* filename, 
                                 enum efsw_action action, const char* old_filename, 
                                 void* param) {
        FaustDynamicPlugin* plugin = (FaustDynamicPlugin*) param;
        if (action == EFSW_ADD || action == EFSW_DELETE || action == EFSW_MODIFIED || action == EFSW_MOVED) {
            std::string configFilename = "faust-current-dsp.txt";
            if (configFilename == filename) {
                plugin->logDebug("Config file changed, triggering reload");
                plugin->fNeedsReload = true;
            }
        }
    }

    // Static callback function for DSP file changes  
    static void dspFileCallback(efsw_watcher watcher, efsw_watchid watchid,
                               const char* dir, const char* filename,
                               enum efsw_action action, const char* old_filename,
                               void* param) {
        FaustDynamicPlugin* plugin = (FaustDynamicPlugin*) param;
        if (action == EFSW_ADD || action == EFSW_DELETE || action == EFSW_MODIFIED || action == EFSW_MOVED) {
            // Extract just filename from current DSP path
            std::string currentFilename;
            size_t pos = plugin->fCurrentDSPPath.find_last_of("/\\");
            if (pos != std::string::npos) {
                currentFilename = plugin->fCurrentDSPPath.substr(pos + 1);
            } else {
                currentFilename = plugin->fCurrentDSPPath;
            }
            
            if (currentFilename == filename) {
                plugin->logDebug("DSP file changed, triggering reload");
                plugin->fNeedsReload = true;
            }
        }
    }

public:
    FaustDynamicPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
        : Base(desc, host) {}
    
    ~FaustDynamicPlugin() {
        // clean shutdown of file watchers
        if (fConfigWatcher) {
            efsw_release(fConfigWatcher);
            fConfigWatcher = nullptr;
        }
        if (fDSPWatcher) {
            efsw_release(fDSPWatcher);
            fDSPWatcher = nullptr;
        }
    }
    
    /**
     * Initialise the plugin by loading the DSP file specified in FAUST_DSP_FILE environment variable
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
            
            if (!fInterpreter.loadFromString("default", defaultCode, fCurrentSampleRate)) {
                std::cerr << "[Faust Dynamic] ERROR: Failed to load default DSP\n";
                return false;
            }
        } else {
            // load DSP file from config file or environment variable
            fCurrentDSPPath = dspPath;
            logDebug("Loading DSP file: " + dspPath);
            std::cerr << "[Faust Dynamic] Loading DSP file: " << dspPath << "\n";
            
            if (!fInterpreter.loadFromFile(dspPath.c_str(), fCurrentSampleRate)) {
                std::cerr << "[Faust Dynamic] ERROR: Failed to load DSP file: " << dspPath << "\n";
                std::cerr << "[Faust Dynamic] Falling back to default DSP\n";
                
                // fall back to default DSP on load failure
                std::string defaultCode = R"(
                    import("stdfaust.lib");
                    gain = hslider("Gain", 0.5, 0, 1, 0.01);
                    process = _ * gain, _ * gain;
                )";
                
                if (!fInterpreter.loadFromString("default", defaultCode, fCurrentSampleRate)) {
                    std::cerr << "[Faust Dynamic] ERROR: Failed to load default DSP\n";
                    return false;
                }
                fCurrentDSPPath.clear();
            }
        }

        // get the compiled DSP instance and UI from interpreter
        fDSP = fInterpreter.getDSP();
        fUI = fInterpreter.getUI();
        if (!fDSP || !fUI) {
            std::cerr << "[Faust Dynamic] ERROR: No DSP instance or UI available\n";
            return false;
        }

        // Rebuild UI -> bind zones -> init -> then read param counts
        fUI->clearParams();
        fUI->beginCapture();
        fDSP->buildUserInterface(fUI);
        fUI->endCapture();
        fDSP->init(fCurrentSampleRate);

        // Keep MapUI and our metadata perfectly in sync
        fActiveDSPParams = std::min((int)fUI->getParamsCount(), (int)fUI->fParams.size());
        for (int i = 0; i < fActiveDSPParams; ++i) {
            fUI->setParamValue(i, fUI->getParamInit(i));
        }

        // Seed slots 0..N-1 on first load
        for (int i = 0; i < std::min(fActiveDSPParams, MAX_PARAMS); ++i)
            fSlotAddress[i] = fUI->getParamAddress(i);
        rebuildSlotMapping();

        logDebug("Successfully loaded DSP with " + std::to_string(fActiveDSPParams) + " active parameters");
        std::cerr << "[Faust Dynamic] Successfully loaded DSP with " << fActiveDSPParams 
                  << " active parameters (fixed " << MAX_PARAMS << " slots)\n";
        
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
     * Start file watching using efsw for hot reload
     */
    void startFileWatching() {
        // Setup config file watcher
        if (!fConfigWatcher) {
            fConfigWatcher = efsw_create(false);
            if (fConfigWatcher) {
                std::string configDir = "/tmp";  // directory of config file
                fConfigWatchID = efsw_addwatch(fConfigWatcher, configDir.c_str(), 
                                             configFileCallback, false, this);
                if (fConfigWatchID > 0) {
                    efsw_watch(fConfigWatcher);
                    logDebug("Started config file watcher for: " + fConfigPath);
                } else {
                    logDebug("Failed to add config file watch");
                    efsw_release(fConfigWatcher);
                    fConfigWatcher = nullptr;
                }
            }
        }
        
        // Setup DSP file watcher if we have a DSP file
        if (!fCurrentDSPPath.empty()) {
            setupDSPFileWatcher();
        }
    }

    /**
     * Setup watcher for current DSP file
     */
    void setupDSPFileWatcher() {
        // Clean up existing DSP watcher
        if (fDSPWatcher) {
            efsw_release(fDSPWatcher);
            fDSPWatcher = nullptr;
        }
        
        if (fCurrentDSPPath.empty()) {
            return;
        }
        
        // Extract directory from DSP path
        std::string dspDir;
        size_t pos = fCurrentDSPPath.find_last_of("/\\");
        if (pos != std::string::npos) {
            dspDir = fCurrentDSPPath.substr(0, pos);
        } else {
            dspDir = ".";  // current directory
        }
        
        fDSPWatcher = efsw_create(false);
        if (fDSPWatcher) {
            fDSPWatchID = efsw_addwatch(fDSPWatcher, dspDir.c_str(), 
                                       dspFileCallback, false, this);
            if (fDSPWatchID > 0) {
                efsw_watch(fDSPWatcher);
                logDebug("Started DSP file watcher for: " + fCurrentDSPPath);
                std::cerr << "[Faust Dynamic] 🔍 Watching DSP: " << fCurrentDSPPath << "\n";
            } else {
                logDebug("Failed to add DSP file watch");
                efsw_release(fDSPWatcher);
                fDSPWatcher = nullptr;
            }
        }
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
            logDebug("Switching to new DSP file from config: " + fCurrentDSPPath);
            std::cerr << "[Faust Dynamic] 🔄 Switching to: " << fCurrentDSPPath << "\n";
            // Setup watcher for the new DSP file
            setupDSPFileWatcher();
        } else if (fCurrentDSPPath.empty()) {
            logDebug("No DSP file to reload");
            return;
        } else {
            std::cerr << "[Faust Dynamic] 🔄 Hot reloading: " << fCurrentDSPPath << "\n";
        }
        
        try {
            // store current parameter values BY ADDRESS (not index!)
            fOldParamValues.clear();
            if (fUI) {
                for (int i = 0; i < fActiveDSPParams; ++i) {
                    std::string address = fUI->getParamAddress(i);
                    FAUSTFLOAT value = fUI->getParamValue(i);
                    fOldParamValues[address] = value;
                    logDebug("Stored param: " + address + " = " + std::to_string(value));
                }
            }
            
            // attempt to reload the DSP with correct sequencing
            if (fInterpreter.loadFromFile(fCurrentDSPPath.c_str(), fCurrentSampleRate)) {
                dsp* newDSP = fInterpreter.getDSP();
                CLAPMapUI* newUI = fInterpreter.getUI();
                if (newDSP && newUI) {
                    // CRITICAL: init DSP at correct sample rate BEFORE restoring values
                    // Rebuild new UI, bind zones, then init at the correct SR
                    newUI->clearParams();
                    newUI->beginCapture();
                    newDSP->buildUserInterface(newUI);
                    newUI->endCapture();
                    newDSP->init(fCurrentSampleRate);
                    
                    int newParamCount = std::min((int)newUI->getParamsCount(), (int)newUI->fParams.size());
                    
                    // restore parameter values BY ADDRESS for parameters that still exist
                    for (int i = 0; i < newParamCount; ++i) {
                        std::string address = newUI->getParamAddress(i);
                        auto it = fOldParamValues.find(address);
                        if (it != fOldParamValues.end()) {
                            // Found old value - clamp to new range and restore
                            FAUSTFLOAT oldValue = it->second;
                            FAUSTFLOAT minVal = newUI->getParamMin(i);
                            FAUSTFLOAT maxVal = newUI->getParamMax(i);
                            FAUSTFLOAT clampedValue = std::max(minVal, std::min(maxVal, oldValue));
                            newUI->setParamValue(i, clampedValue);
                            logDebug("Restored param: " + address + " = " + std::to_string(clampedValue) + 
                                   " (was " + std::to_string(oldValue) + ", range " + 
                                   std::to_string(minVal) + "-" + std::to_string(maxVal) + ")");
                        } else {
                            // New parameter - use default
                            newUI->setParamValue(i, newUI->getParamInit(i));
                            logDebug("New param: " + address + " = " + std::to_string(newUI->getParamInit(i)));
                        }
                    }
                    
                    // atomically switch to new DSP and UI
                    fDSP = newDSP;
                    fUI = newUI;
                    int oldParamCount = fActiveDSPParams;
                    fActiveDSPParams = newParamCount;
                    rebuildSlotMapping();
                    
                    
                    // Always notify host about parameter info changes
                    logDebug("Active parameters changed: " + std::to_string(oldParamCount) + 
                            " -> " + std::to_string(newParamCount));
                    
                    // Use runOnMainThread to safely notify host about parameter changes
                    runOnMainThread([this]() {
                        logDebug("Requesting host parameter info update from main thread");
                        _host.paramsRescan(CLAP_PARAM_RESCAN_ALL);
                        std::cerr << "[Faust Dynamic] 🔄 Updated parameter info (fixed 12 slots)\n";
                    });
                    
                    std::cerr << "[Faust Dynamic] ✅ Hot reload successful: " 
                              << fActiveDSPParams << " parameters\n";
                } else {
                    std::cerr << "[Faust Dynamic] ❌ Hot reload failed: No DSP instance or UI\n";
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
    fCurrentSampleRate = (int)sampleRate;  // Store actual session sample rate
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

        // process incoming parameter events (translate slot -> Faust param index)
        // process incoming parameter events (translate slot -> Faust param index)
        if (process->in_events && fUI) {
            for (uint32_t i = 0; i < process->in_events->size(process->in_events); ++i) {
                const clap_event_header_t* hdr = process->in_events->get(process->in_events, i);
                if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) continue;

                if (hdr->type == CLAP_EVENT_PARAM_VALUE) {
                    const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
                    const uint32_t slot = ev->param_id;
                    if (slot >= MAX_PARAMS) continue;

                    const int j = fSlotToParam[slot];   // map slot -> current Faust param
                    if (j < 0) continue;                // ignore unmapped slots

                    const FAUSTFLOAT mn = fUI->getParamMin(j);
                    const FAUSTFLOAT mx = fUI->getParamMax(j);
                    const FAUSTFLOAT v  = std::max(mn, std::min(mx, (FAUSTFLOAT)ev->value));
                    fUI->setParamValue(j, v);
                }
            }
        }

                // 32f/64f-safe I/O hookup + on-the-fly conversion if needed
        const bool faustIsFloat = (sizeof(FAUSTFLOAT) == sizeof(float));
        const bool inIs64  = (in.data64  && !in.data32);
        const bool outIs64 = (out.data64 && !out.data32);
        const bool inIs32  = (in.data32  != nullptr);
        const bool outIs32 = (out.data32 != nullptr);

        FAUSTFLOAT* inputs[2]  = { nullptr, nullptr };
        FAUSTFLOAT* outputs[2] = { nullptr, nullptr };

        auto ensureSize = [&](std::vector<FAUSTFLOAT>& v, uint32_t n) {
            if (v.size() < n) v.resize(n);
        };

        const uint32_t n = process->frames_count;

        // -------- Inputs --------
        if (faustIsFloat) {
            if (inIs32) {
                inputs[0] = (in.channel_count > 0) ? reinterpret_cast<FAUSTFLOAT*>(in.data32[0]) : nullptr;
                inputs[1] = (in.channel_count > 1) ? reinterpret_cast<FAUSTFLOAT*>(in.data32[1]) : inputs[0];
            } else if (inIs64) {
                // Host is 64f, DSP is 32f -> convert
                if (in.channel_count > 0) { ensureSize(fTmpIn[0], n); for (uint32_t i=0;i<n;++i) fTmpIn[0][i] = (FAUSTFLOAT)in.data64[0][i]; inputs[0] = fTmpIn[0].data(); }
                if (in.channel_count > 1) { ensureSize(fTmpIn[1], n); for (uint32_t i=0;i<n;++i) fTmpIn[1][i] = (FAUSTFLOAT)in.data64[1][i]; inputs[1] = fTmpIn[1].data(); }
                if (!inputs[1]) inputs[1] = inputs[0];
            }
        } else { // FAUSTFLOAT == double
            if (inIs64) {
                inputs[0] = (in.channel_count > 0) ? reinterpret_cast<FAUSTFLOAT*>(in.data64[0]) : nullptr;
                inputs[1] = (in.channel_count > 1) ? reinterpret_cast<FAUSTFLOAT*>(in.data64[1]) : inputs[0];
            } else if (inIs32) {
                // Host is 32f, DSP is 64f -> convert
                if (in.channel_count > 0) { ensureSize(fTmpIn[0], n); for (uint32_t i=0;i<n;++i) fTmpIn[0][i] = (FAUSTFLOAT)in.data32[0][i]; inputs[0] = fTmpIn[0].data(); }
                if (in.channel_count > 1) { ensureSize(fTmpIn[1], n); for (uint32_t i=0;i<n;++i) fTmpIn[1][i] = (FAUSTFLOAT)in.data32[1][i]; inputs[1] = fTmpIn[1].data(); }
                if (!inputs[1]) inputs[1] = inputs[0];
            }
        }

        // -------- Outputs --------
        bool outNeedsBackConvert = false;

        if (faustIsFloat) {
            if (outIs32) {
                outputs[0] = (out.channel_count > 0) ? reinterpret_cast<FAUSTFLOAT*>(out.data32[0]) : nullptr;
                outputs[1] = (out.channel_count > 1) ? reinterpret_cast<FAUSTFLOAT*>(out.data32[1]) : outputs[0];
            } else if (outIs64) {
                // DSP 32f -> Host 64f : render to temp, then convert back
                outNeedsBackConvert = true;
                if (out.channel_count > 0) { ensureSize(fTmpOut[0], n); outputs[0] = fTmpOut[0].data(); }
                if (out.channel_count > 1) { ensureSize(fTmpOut[1], n); outputs[1] = fTmpOut[1].data(); }
                if (!outputs[1]) outputs[1] = outputs[0];
            }
        } else { // FAUSTFLOAT == double
            if (outIs64) {
                outputs[0] = (out.channel_count > 0) ? reinterpret_cast<FAUSTFLOAT*>(out.data64[0]) : nullptr;
                outputs[1] = (out.channel_count > 1) ? reinterpret_cast<FAUSTFLOAT*>(out.data64[1]) : outputs[0];
            } else if (outIs32) {
                // DSP 64f -> Host 32f : render to temp, then convert back
                outNeedsBackConvert = true;
                if (out.channel_count > 0) { ensureSize(fTmpOut[0], n); outputs[0] = fTmpOut[0].data(); }
                if (out.channel_count > 1) { ensureSize(fTmpOut[1], n); outputs[1] = fTmpOut[1].data(); }
                if (!outputs[1]) outputs[1] = outputs[0];
            }
        }

        // Only process if we have valid buffers
        if (inputs[0] && outputs[0]) {
            currentDSP->compute(n, inputs, outputs);

            // Back‑convert if needed
            if (outNeedsBackConvert) {
                if (faustIsFloat && outIs64) {
                    if (out.channel_count > 0) for (uint32_t i=0;i<n;++i) out.data64[0][i] = (double)outputs[0][i];
                    if (out.channel_count > 1) for (uint32_t i=0;i<n;++i) out.data64[1][i] = (double)outputs[1][i];
                    if (out.channel_count == 1 && outputs[1] == outputs[0]) {
                        // mono out: nothing extra to do
                    }
                } else if (!faustIsFloat && outIs32) {
                    if (out.channel_count > 0) for (uint32_t i=0;i<n;++i) out.data32[0][i] = (float)outputs[0][i];
                    if (out.channel_count > 1) for (uint32_t i=0;i<n;++i) out.data32[1][i] = (float)outputs[1][i];
                }
            }
        }

        return CLAP_PROCESS_CONTINUE;
    }

    // parameter interface implementation
    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return MAX_PARAMS; }  // Always report fixed count

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= MAX_PARAMS || !info) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;

        int j = (index < MAX_PARAMS) ? fSlotToParam[index] : -1;
        if (j != -1 && fUI) {
            std::string name = fUI->getParamShortname(j);
            if (name.empty()) name = "param" + std::to_string(index);
            std::snprintf(info->name, CLAP_NAME_SIZE, "%s", name.c_str());
            info->min_value     = fUI->getParamMin(j);
            info->max_value     = fUI->getParamMax(j);
            info->default_value = fUI->getParamInit(j);
            info->flags         = CLAP_PARAM_IS_AUTOMATABLE;
        } else {
            std::snprintf(info->name, CLAP_NAME_SIZE, "Unused %u", index + 1);
            info->min_value     = 0.0;
            info->max_value     = 1.0;
            info->default_value = 0.0;
            info->flags         = CLAP_PARAM_IS_AUTOMATABLE | CLAP_PARAM_IS_READONLY;
        }
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (!value || id >= MAX_PARAMS) return false;
        int j = fSlotToParam[id];
        if (j != -1 && fUI) { *value = fUI->getParamValue(j); }
        else                { *value = 0.0; }
        return true;
    }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
    if (!in || !fUI) return;

    for (uint32_t i = 0; i < in->size(in); ++i) {
        const clap_event_header_t* hdr = in->get(in, i);
        if (!hdr || hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) continue;

        if (hdr->type == CLAP_EVENT_PARAM_VALUE) {
            const auto* ev = reinterpret_cast<const clap_event_param_value_t*>(hdr);
            const uint32_t slot = ev->param_id;
            if (slot >= MAX_PARAMS) continue;

            const int j = fSlotToParam[slot];
            if (j < 0) continue;

            const FAUSTFLOAT mn = fUI->getParamMin(j);
            const FAUSTFLOAT mx = fUI->getParamMax(j);
            const FAUSTFLOAT v  = std::max(mn, std::min(mx, (FAUSTFLOAT)ev->value));
            fUI->setParamValue(j, v);
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
        info->in_place_pair = CLAP_INVALID_ID;  // CRITICAL: Disable in-place processing!
        
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