/************************** BEGIN JuceParameterUI.h *************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JuceParameterUI_H
#define JuceParameterUI_H

#include <cmath>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/gui/GUI.h"
#include "faust/gui/PathBuilder.h"

/**
 * Zones of other DSPs that declare the same control as a parameter, for instance a
 * tempo read by both the voices and the effect of a plugin built with -effect: the
 * parameter keeps them equal to its own zone.
 *
 * The parameter writes them when the host or an editor sets it, and when its own
 * zone changes (reflectZone). A linked zone changed by other means (a MIDI controller
 * mapped on it only) is not propagated back to the parameter.
 */
struct FaustLinkedZones {
    
    std::vector<FAUSTFLOAT*> fLinkedZones;
    
    void linkZone(FAUSTFLOAT* zone)
    {
        fLinkedZones.push_back(zone);
    }
    
    void writeLinkedZones(FAUSTFLOAT value)
    {
        for (FAUSTFLOAT* zone : fLinkedZones) {
            *zone = value;
        }
    }
    
    virtual ~FaustLinkedZones() {}
};

// Link AudioParameterBool with on/off parameter

struct FaustPlugInAudioParameterBool : public juce::AudioParameterBool, public uiOwnedItem, public FaustLinkedZones {
    
    FaustPlugInAudioParameterBool(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label)
    :juce::AudioParameterBool(juce::ParameterID(path, /* versionHint */ 1), label, false), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterBool() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        writeLinkedZones(v);
        setValueNotifyingHost(float(v));
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(newValue));
        writeLinkedZones(FAUSTFLOAT(newValue));
    }
    
    // The base class value is only updated by its own setValue, so read the zone
    virtual float getValue() const override
    {
        return (*fZone > FAUSTFLOAT(0.5)) ? 1.0f : 0.0f;
    }

};

// Link AudioParameterFloat with range parameters

struct FaustPlugInAudioParameterFloat : public juce::AudioParameterFloat, public uiOwnedItem, public FaustLinkedZones {
    
    /**
     * @param gui the GUI that owns the zone and calls reflectZone() when it changes
     * @param zone the Faust control
     * @param path the parameter ID (the shortname, or the full path with FAUST_JUCE_FULLPATH_IDS)
     * @param label the parameter name, i.e. the widget label without its metadata
     * @param init the default value
     * @param range the host range, built from the widget min, max, step and [scale] metadata;
     *        the (min, max, init) constructor of AudioParameterFloat cannot be used since it
     *        would snap every value to a 0.01 grid
     * @param attributes the unit label and the conversions between values and text
     * @param numSteps 0 for a continuous parameter, otherwise its number of positions,
     *        which makes it discrete for the host (menus and radio buttons whose values
     *        are not 0, 1, 2..., see FaustPlugInAudioParameterChoice for the others)
     */
    FaustPlugInAudioParameterFloat(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label, FAUSTFLOAT init,
                                   const juce::NormalisableRange<float>& range,
                                   const juce::AudioParameterFloatAttributes& attributes = {},
                                   int numSteps = 0)
    :juce::AudioParameterFloat(juce::ParameterID(path, /* versionHint */ 1), label, range, float(init), attributes), uiOwnedItem(gui, zone),
    fNumSteps(numSteps)
    {}
    
    virtual ~FaustPlugInAudioParameterFloat() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        writeLinkedZones(v);
        if (v >= range.start && v <= range.end) {
            setValueNotifyingHost(range.convertTo0to1(float(v)));
        }
    }
    
    virtual void setValue (float newValue) override
    {
        FAUSTFLOAT v = FAUSTFLOAT(range.convertFrom0to1(newValue));
        modifyZone(v);
        writeLinkedZones(v);
    }
    
    // The base class value is only updated by its own setValue, so read the zone
    virtual float getValue() const override
    {
        return range.convertTo0to1(range.getRange().clipValue(float(*fZone)));
    }
    
    // AudioParameterFloat reports a continuous parameter whatever the interval of its
    // range, so menus and radio buttons give their number of positions explicitly
    int getNumSteps() const override
    {
        return (fNumSteps > 0) ? fNumSteps : juce::AudioProcessorParameter::getNumSteps();
    }
    
    bool isDiscrete() const override
    {
        return fNumSteps > 0;
    }
    
    private:
    
        int fNumSteps;  // 0 for a continuous parameter

};

// Link AudioParameterChoice with a menu or radio widget whose values are 0, 1, 2...:
// the value of the zone is the index of the choice. Hosts and GUI builders show a
// list of names, as for any choice parameter, instead of a slider.

struct FaustPlugInAudioParameterChoice : public juce::AudioParameterChoice, public uiOwnedItem, public FaustLinkedZones {

    /**
     * @param gui the GUI that owns the zone and calls reflectZone() when it changes
     * @param zone the Faust control
     * @param path the parameter ID (the shortname, or the full path with FAUST_JUCE_FULLPATH_IDS)
     * @param label the parameter name, i.e. the widget label without its metadata
     * @param choices the names of the values 0, 1, 2..., in this order
     * @param init the default value, i.e. the index of the default choice
     * @param unit the [unit:...] metadata, shown by hosts next to the value
     */
    FaustPlugInAudioParameterChoice(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label,
                                    const juce::StringArray& choices, FAUSTFLOAT init, const juce::String& unit)
    :juce::AudioParameterChoice(juce::ParameterID(path, /* versionHint */ 1), label, choices,
                                juce::jlimit(0, choices.size() - 1, juce::roundToInt(init)),
                                juce::AudioParameterChoiceAttributes().withLabel(unit)), uiOwnedItem(gui, zone)
    {}

    virtual ~FaustPlugInAudioParameterChoice() {}

    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        writeLinkedZones(v);
        setValueNotifyingHost(getValue());
    }

    virtual void setValue (float newValue) override
    {
        FAUSTFLOAT v = FAUSTFLOAT(juce::roundToInt(convertFrom0to1(newValue)));
        modifyZone(v);
        writeLinkedZones(v);
    }

    // The base class value (and getIndex()) is only updated by its own setValue, so read
    // the zone, which can also hold a value between two choices: the closest one is used
    virtual float getValue() const override
    {
        return convertTo0to1(float(juce::jlimit(0, choices.size() - 1, juce::roundToInt(*fZone))));
    }

};

// A class to create AudioProcessorParameter objects for each zone.
//
// Parameter IDs are the Faust shortnames (e.g. "cutoff", or "Route_0_depth"
// when a label is repeated), which do not depend on the groups added by
// architecture wrappers (polyphony, effect sequencing...). Shortnames are only
// known once all paths have been seen, so controls are collected while the UI
// is built and parameters are created when the top-level box is closed.
// Define FAUST_JUCE_FULLPATH_IDS to keep the full path as ID, as in previous
// versions, so that automation saved with older exports still applies.
//
// Several DSPs can be visited in turn with the same JuceParameterUI, as the JUCE
// architecture does with the voices and the effect of a plugin built with -effect.
// Shortnames are then computed for each DSP (each top-level box), and a control
// declared by several DSPs with the same shortname, kind and range gets a single
// parameter that drives all their zones. A control with the same shortname but
// another kind or range keeps its own parameter, with a numbered ID ("bpm_2").
//
// The Faust groups (vgroup, hgroup, tgroup) become juce::AudioProcessorParameterGroup:
// hosts and GUI builders such as PluginGuiMagic can show the parameters the way the DSP
// organises them. Parameter IDs and order do not depend on them.
//
// Widget metadata is passed on to the host: [scale:log] and [scale:exp] shape the
// parameter range with the same conversions as the other Faust interfaces, [unit:...]
// becomes the parameter label, and [style:menu{...}] or [style:radio{...}] give the
// value names shown and accepted by the host. A menu or radio widget whose values are
// 0, 1, 2... becomes a juce::AudioParameterChoice, which hosts and GUI builders show
// as a list; the others become discrete float parameters.

class JuceParameterUI : public GUI, public PathBuilder, public MetaDataUI {
    
    private:
        
        // A widget seen while the UI is built, turned into a parameter by createParameters()
        struct Control {
            FAUSTFLOAT* fZone;
            std::string fPath;      // full path, also the key of fFull2Short
            std::string fLabel;     // label without its metadata
            bool fIsBool;           // button or checkbox
            FAUSTFLOAT fInit, fMin, fMax, fStep;
            std::vector<std::string> fGroups;  // labels of the enclosing groups, outermost first
        };
        
        // A parameter already created, which a control of a later DSP can join
        struct Created {
            FaustLinkedZones* fParameter;
            bool fIsBool;
            FAUSTFLOAT fMin, fMax;
        };
        
        juce::AudioProcessor* fProcessor;
        std::vector<Control> fControls;            // widgets of the top-level box being built
        std::map<std::string, Created> fCreated;   // parameters created so far, by ID
        std::set<juce::String> fGroupIDs;          // group IDs used so far: JUCE wants them unique
        
        // Record a widget and its full path; its metadata has already been received by
        // declare(), which Faust calls before the widget itself
        void addControl(const char* label, FAUSTFLOAT* zone, bool is_bool,
                        FAUSTFLOAT init = 0, FAUSTFLOAT min = 0, FAUSTFLOAT max = 1, FAUSTFLOAT step = 0)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fControls.push_back({ zone, path, label, is_bool, init, min, max, step, fControlsLevel });
        }
        
        /**
         * Build the host range of a slider or numerical entry.
         *
         * A linear range keeps the Faust step as its interval. A [scale:log] or [scale:exp]
         * range maps the normalised host value with the LogValueConverter or ExpValueConverter
         * used by the other Faust interfaces, so the middle of a log 30..18000 Hz control is
         * about 735 Hz; values are then snapped to the Faust step, counted from min.
         */
        static juce::NormalisableRange<float> makeRange(Scale scale, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            if (scale == kLin || !(min < max)) {
                return juce::NormalisableRange<float>(float(min), float(max), float(step));
            }
            std::shared_ptr<ValueConverter> converter;
            if (scale == kLog) {
                converter = std::make_shared<LogValueConverter>(0., 1., min, max);
            } else {
                converter = std::make_shared<ExpValueConverter>(0., 1., min, max);
            }
            float interval = float(step);
            return juce::NormalisableRange<float>(float(min), float(max),
                [converter](float, float, float proportion) { return float(converter->ui2faust(proportion)); },
                [converter](float, float, float value) { return float(converter->faust2ui(value)); },
                [interval](float start, float end, float value) {
                    if (interval > 0.f) value = start + interval * std::round((value - start) / interval);
                    return juce::jlimit(start, end, value);
                });
        }
        
        /**
         * Build the attributes of a slider, numerical entry or bargraph: [unit:...] becomes
         * the parameter label, which hosts display next to the value.
         *
         * The value is shown with as many decimals as the Faust step needs, since a range
         * defined by conversion functions has no interval for JUCE to derive them from.
         * With [style:menu{...}] or [style:radio{...}], the host shows the name of the
         * closest declared value instead, and accepts a name typed back.
         */
        juce::AudioParameterFloatAttributes makeAttributes(FAUSTFLOAT* zone, FAUSTFLOAT step)
        {
            int decimals = (step >= 1) ? 0 : (step >= 0.1) ? 1 : (step >= 0.01) ? 2 : 3;
            auto attributes = juce::AudioParameterFloatAttributes()
                .withLabel(getUnit(zone))
                .withStringFromValueFunction([decimals](float value, int) { return juce::String(value, decimals); });
            auto options = getOptions(zone);
            if (!options.empty()) {
                attributes = attributes
                    .withStringFromValueFunction([options](float value, int) {
                        // The name of the closest declared value
                        size_t best = 0;
                        for (size_t i = 1; i < options.size(); i++) {
                            if (std::abs(options[i].second - value) < std::abs(options[best].second - value)) best = i;
                        }
                        return juce::String(options[best].first);
                    })
                    .withValueFromStringFunction([options](const juce::String& text) {
                        for (const auto& option : options) {
                            if (text == juce::String(option.first)) return float(option.second);
                        }
                        return text.getFloatValue();
                    });
            }
            return attributes;
        }
        
        // The (name, value) pairs of a menu or radio widget, empty for other widgets
        std::vector<std::pair<std::string, double> > getOptions(FAUSTFLOAT* zone)
        {
            return isMenu(zone) ? getMenuDescription(zone) : getRadioDescription(zone);
        }
        
        /**
         * The names of a menu or radio widget whose values are 0, 1, 2... up to its max, ordered
         * by value, which an AudioParameterChoice represents exactly. Empty for the other widgets,
         * and for menus with other values (-1, 0.5, a gap...), which stay discrete float parameters.
         * The normalised host value is the same with both classes (value / max), so automation
         * recorded with a discrete float parameter still applies.
         */
        juce::StringArray getChoices(const Control& control)
        {
            auto options = getOptions(control.fZone);
            const size_t count = options.size();
            if (count < 2 || control.fMin != 0 || control.fMax != FAUSTFLOAT(count - 1)) return {};
            std::vector<std::string> names(count);
            std::vector<bool> seen(count, false);
            for (const auto& option : options) {
                const double value = option.second;
                if (value < 0 || value >= double(count) || value != std::floor(value) || seen[size_t(value)]) return {};
                seen[size_t(value)] = true;
                names[size_t(value)] = option.first;
            }
            juce::StringArray choices;
            for (const auto& name : names) {
                choices.add(juce::String(name));
            }
            return choices;
        }

        // A widget outside any group (none in Faust-generated code) goes to the processor directly
        void addToGroup(juce::AudioProcessorParameterGroup* group, std::unique_ptr<juce::AudioProcessorParameter> parameter)
        {
            if (group) {
                group->addChild(std::move(parameter));
            } else {
                fProcessor->addParameter(parameter.release());
            }
        }
        
        // Return id, or id followed by the first free number ("bpm_2") if it is taken
        std::string freeID(const std::string& id)
        {
            std::string candidate = id;
            for (int n = 2; fCreated.count(candidate) > 0; n++) {
                candidate = id + "_" + std::to_string(n);
            }
            return candidate;
        }
        
        // Return the group of a widget, creating the missing groups along its path under root.
        // Group IDs are the group paths, numbered if the same path comes back (a second DSP).
        juce::AudioProcessorParameterGroup* getGroup(const std::vector<std::string>& labels,
                                                     std::unique_ptr<juce::AudioProcessorParameterGroup>& root,
                                                     std::map<std::string, juce::AudioProcessorParameterGroup*>& groups)
        {
            juce::AudioProcessorParameterGroup* parent = nullptr;
            std::string path;
            for (const auto& label : labels) {
                path += "/" + label;
                auto it = groups.find(path);
                if (it != groups.end()) {
                    parent = it->second;
                    continue;
                }
                juce::String id(path);
                for (int n = 2; fGroupIDs.count(id) > 0; n++) {
                    id = juce::String(path) + "_" + juce::String(n);
                }
                fGroupIDs.insert(id);
                // Faust names an unlabelled group "0x00"
                auto group = std::make_unique<juce::AudioProcessorParameterGroup>(id, (label == "0x00") ? "" : label, "|");
                auto* raw = group.get();
                if (parent) {
                    parent->addChild(std::move(group));
                } else {
                    root = std::move(group);
                }
                groups[path] = raw;
                parent = raw;
            }
            return parent;
        }
        
        // Create the parameters of the widgets of the top-level box just closed, in their
        // declaration order, once its full paths are known and the shortnames can be
        // computed. A widget whose ID is already taken by a parameter of the same kind and
        // range, created for a previous DSP, is linked to it instead.
        void createParameters()
        {
            // Shortnames of this DSP only, independent of the DSPs visited before
            fFull2Short.clear();
            computeShortNames();
            // The groups of this top-level box, handed to the processor at the end
            std::unique_ptr<juce::AudioProcessorParameterGroup> root;
            std::map<std::string, juce::AudioProcessorParameterGroup*> groups;
            for (const auto& control : fControls) {
            #ifdef FAUST_JUCE_FULLPATH_IDS
                std::string id = control.fPath;
            #else
                std::string id = fFull2Short[control.fPath];
            #endif
                auto it = fCreated.find(id);
                if (it != fCreated.end()) {
                    const Created& created = it->second;
                    if (created.fIsBool == control.fIsBool && created.fMin == control.fMin && created.fMax == control.fMax) {
                        created.fParameter->linkZone(control.fZone);
                        continue;
                    }
                    id = freeID(id);
                }
                juce::AudioProcessorParameterGroup* group = getGroup(control.fGroups, root, groups);
                juce::StringArray choices = control.fIsBool ? juce::StringArray() : getChoices(control);
                if (!choices.isEmpty()) {
                    auto parameter = std::make_unique<FaustPlugInAudioParameterChoice>(this, control.fZone, id, control.fLabel,
                                                                                       choices, control.fInit, getUnit(control.fZone));
                    fCreated[id] = { parameter.get(), false, control.fMin, control.fMax };
                    addToGroup(group, std::move(parameter));
                } else if (control.fIsBool) {
                    auto parameter = std::make_unique<FaustPlugInAudioParameterBool>(this, control.fZone, id, control.fLabel);
                    fCreated[id] = { parameter.get(), true, control.fMin, control.fMax };
                    addToGroup(group, std::move(parameter));
                } else {
                    auto parameter = std::make_unique<FaustPlugInAudioParameterFloat>(this, control.fZone, id, control.fLabel, control.fInit,
                                                                         makeRange(getScale(control.fZone), control.fMin, control.fMax, control.fStep),
                                                                         makeAttributes(control.fZone, control.fStep),
                                                                         int(getOptions(control.fZone).size()));
                    fCreated[id] = { parameter.get(), false, control.fMin, control.fMax };
                    addToGroup(group, std::move(parameter));
                }
            }
            if (root) {
                fProcessor->addParameterGroup(std::move(root));
            }
            fControls.clear();
            fFullPaths.clear();
        }
        
    public:
        
        JuceParameterUI(juce::AudioProcessor* processor):fProcessor(processor)
        {}
    
        virtual ~JuceParameterUI() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void closeBox()
        {
            if (popLabel()) {
                // All paths are known: shortnames can be computed
                createParameters();
            }
        }
        
        // -- metadata declarations
        
        // Keep the widget metadata ([scale], [unit], [style]...) for createParameters()
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            MetaDataUI::declare(zone, key, val);
        }
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addControl(label, zone, true);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addControl(label, zone, true);
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addControl(label, zone, false, init, min, max, step);
        }
        
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addControl(label, zone, false, init, min, max, step);
        }
        
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addControl(label, zone, false, init, min, max, step);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addControl(label, zone, false, 0, min, max, 0);
        }
        
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addControl(label, zone, false, 0, min, max, 0);
        }
    
};

#endif
/**************************  END  JuceParameterUI.h **************************/
