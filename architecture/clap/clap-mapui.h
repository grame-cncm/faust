//
// Created by Facundo Franchino on 07/08/2025.
//

// clap-mapui.h
// Faust UI adapter for the dynamic CLAP plugin: keeps, for every host-visible
// control, the path/zone/range the CLAP parameter extension has to report.
#ifndef CLAP_MAPUI_H
#define CLAP_MAPUI_H

#include <faust/gui/MapUI.h>

#include <string>
#include <vector>

struct CLAPMapUI : public MapUI {
    // One entry per host-visible parameter, in DSP declaration order.
    //
    // MapUI's own index space cannot be reused. It walks fPathZoneMap, a
    // std::map, so its indices follow the *alphabetical* order of the paths,
    // and it includes bargraphs. Storing ranges in a separate vector indexed by
    // declaration order therefore pairs one control's name with another one's
    // range as soon as the DSP has more than one control.
    //
    // Keeping path, zone and range in a single ordered entry makes that
    // impossible by construction: every accessor below reads one entry.
    struct ParamMeta {
        std::string path;
        FAUSTFLOAT* zone;
        FAUSTFLOAT  min;
        FAUSTFLOAT  max;
        FAUSTFLOAT  init;
    };

    std::vector<ParamMeta> fParams;

    // The path is read back from MapUI rather than rebuilt, so the two always
    // agree on what a control is called.
    void trackParam(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT init)
    {
        fParams.push_back({MapUI::getParamAddress(zone), zone, min, max, init});
    }

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
    // host must not be offered as automatable parameters. They stay in MapUI so
    // that lookups by path keep working.

    // Accessors over our own index space. They hide the MapUI versions on
    // purpose: the plugin holds a CLAPMapUI and must see this index space.
    int getParamsCount() const { return int(fParams.size()); }

    bool validIndex(int index) const { return index >= 0 && index < int(fParams.size()); }

    FAUSTFLOAT getParamMin(int index) const { return validIndex(index) ? fParams[index].min : 0.f; }

    FAUSTFLOAT getParamMax(int index) const { return validIndex(index) ? fParams[index].max : 1.f; }

    FAUSTFLOAT getParamInit(int index) const
    {
        return validIndex(index) ? fParams[index].init : 0.f;
    }

    FAUSTFLOAT* getParamZone(int index) const
    {
        return validIndex(index) ? fParams[index].zone : nullptr;
    }

    std::string getParamAddress(int index) const
    {
        return validIndex(index) ? fParams[index].path : "";
    }

    void setParamValue(int index, FAUSTFLOAT value)
    {
        FAUSTFLOAT* zone = getParamZone(index);
        if (zone) {
            *zone = value;
        }
    }

    FAUSTFLOAT getParamValue(int index) const
    {
        FAUSTFLOAT* zone = getParamZone(index);
        return zone ? *zone : 0.f;
    }

    // Value clamped into the control's own range, which is what a host event
    // has to go through before it reaches a DSP zone.
    FAUSTFLOAT clampToRange(int index, FAUSTFLOAT value) const
    {
        if (!validIndex(index)) {
            return value;
        }
        const ParamMeta& p = fParams[index];
        return (value < p.min) ? p.min : ((value > p.max) ? p.max : value);
    }

    // A CLAP slot is described to the host as a plain 0..1 range, and the
    // control's real range lives behind these two. That is not cosmetic: the
    // DSP behind a slot changes on every reload, and CLAP only lets a plugin
    // announce a new min/max with CLAP_PARAM_RESCAN_ALL, which is illegal while
    // the plugin is active. Keeping the announced range fixed is what makes a
    // reload visible in the host's UI without deactivating the plugin.
    FAUSTFLOAT normalize(int index, FAUSTFLOAT value) const
    {
        if (!validIndex(index)) {
            return 0;
        }
        const ParamMeta& p    = fParams[index];
        const FAUSTFLOAT span = p.max - p.min;
        if (span <= 0) {
            return 0;
        }
        return (clampToRange(index, value) - p.min) / span;
    }

    FAUSTFLOAT denormalize(int index, double normalized) const
    {
        if (!validIndex(index)) {
            return 0;
        }
        const ParamMeta& p = fParams[index];
        const double     t = (normalized < 0) ? 0 : ((normalized > 1) ? 1 : normalized);
        return FAUSTFLOAT(p.min + t * (p.max - p.min));
    }

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
};

#endif  // CLAP_MAPUI_H
