// Created by Facundo Franchino on 07/08/2025.
/********************************************************************
                                                                   
                    clap-mapui.h                  
               (c) GRAME & Facundo Franchino, 2025                 
                                                                   
 ********************************************************************/

/*
Shared ui class with parameter metadata
*/

#ifndef CLAP_MAPUI_H
#define CLAP_MAPUI_H

#include <faust/gui/MapUI.h>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

// custom UI class inheriting Faust's MapUI to store parameter metadata
struct CLAPMapUI : public MapUI {

    // metadata struct for parameter limits and default value
    struct ParamMeta {
        FAUSTFLOAT min;
        FAUSTFLOAT max;
        FAUSTFLOAT init;
    };

    // vector holding all parameter information
    std::vector<ParamMeta> fParams;

    // override Faust UI methods to track parameters
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                           FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addVerticalSlider(label, zone, init, min, max, step);
        fParams.push_back({min, max, init});
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                             FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addHorizontalSlider(label, zone, init, min, max, step);
        fParams.push_back({min, max, init});
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                     FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        MapUI::addNumEntry(label, zone, init, min, max, step);
        fParams.push_back({min, max, init});
    }

    // add buttons with default 0-1 range
    void addButton(const char* label, FAUSTFLOAT* zone) override {
        MapUI::addButton(label, zone);
        fParams.push_back({0.0f, 1.0f, 0.0f});
    }

    void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
        MapUI::addCheckButton(label, zone);
        fParams.push_back({0.0f, 1.0f, 0.0f});
    }

    // parameter metadata accessors
    FAUSTFLOAT getParamMin(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.f;
        return fParams[index].min;
    }

    FAUSTFLOAT getParamMax(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 1.f;
        return fParams[index].max;
    }

    FAUSTFLOAT getParamInit(int index) const {
        if (index < 0 || index >= int(fParams.size())) return 0.5f;
        return fParams[index].init;
    }

    // index-based parameter access methods
    void setParamValue(int index, FAUSTFLOAT val) {
        if (index < 0 || index >= getParamsCount()) return;
        std::string addr = getParamAddress(index);
        MapUI::setParamValue(addr, val);
    }

    FAUSTFLOAT getParamValue(int index) const {
        if (index < 0 || index >= const_cast<CLAPMapUI*>(this)->getParamsCount()) return 0.f;
        std::string addr = const_cast<CLAPMapUI*>(this)->getParamAddress(index);
        return const_cast<CLAPMapUI*>(this)->MapUI::getParamValue(addr);
    }

    std::string getParamShortname(int index) const {
        if (index < 0 || index >= const_cast<CLAPMapUI*>(this)->getParamsCount()) return "";
        std::string full = const_cast<CLAPMapUI*>(this)->getParamAddress(index);
        if (full.empty() || full == "/") return "param" + std::to_string(index);
        size_t slash = full.find_last_of('/');
        return (slash != std::string::npos) ? full.substr(slash + 1) : full;
    }
    
    // preset management
    std::vector<std::string> fPresetList;
    int fCurrentPresetIndex = 0;
    FAUSTFLOAT fPresetSelectorValue = 0.0f;
    
    // preset browser callback function pointer
    std::function<void(const std::string&)> fPresetLoadCallback = nullptr;
    
    void setPresetLoadCallback(std::function<void(const std::string&)> callback) {
        fPresetLoadCallback = callback;
    }
    
    void setPresetList(const std::vector<std::string>& presets) {
        fPresetList = presets;
        if (!presets.empty()) {
            fCurrentPresetIndex = 0;
            fPresetSelectorValue = 0.0f;
        }
    }
    
    // add preset browser as a "fake" UI element
    void addPresetBrowser(const char* label = "Presets") {
        // add as a numbered entry that acts as preset selector
        addNumEntry(label, &fPresetSelectorValue, 0.0f, 0.0f, 
                   std::max(1.0f, float(fPresetList.size() - 1)), 1.0f);
    }
    
    // handle preset selection changes
    void handlePresetSelection() {
        int newIndex = static_cast<int>(fPresetSelectorValue + 0.5f); // round to nearest
        if (newIndex >= 0 && newIndex < static_cast<int>(fPresetList.size()) && 
            newIndex != fCurrentPresetIndex) {
            fCurrentPresetIndex = newIndex;
            if (fPresetLoadCallback) {
                fPresetLoadCallback(fPresetList[newIndex]);
            }
        }
    }
    
    // methods for simple-faust.cpp
    void clearParams() {
        fParams.clear();
        // don't clear MapUI's internal params, just our metadata
    }
    
    void beginCapture() {
        // no-op for now, could be used for parameter change tracking
    }
    
    void endCapture() {
        // no-op for now, could be used for parameter change tracking
    }
};

#endif // CLAP_MAPUI_H