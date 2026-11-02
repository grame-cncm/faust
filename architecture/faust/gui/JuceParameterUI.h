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

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/gui/GUI.h"
#include "faust/gui/PathBuilder.h"

// Link AudioParameterBool with on/off parameter

struct FaustPlugInAudioParameterBool : public juce::AudioParameterBool, public uiOwnedItem {
    
    FaustPlugInAudioParameterBool(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label)
    :juce::AudioParameterBool(juce::ParameterID(path, /* versionHint */ 1), label, false), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterBool() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        setValueNotifyingHost(float(v));
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(newValue));
    }
    
    // The base class value is only updated by its own setValue, so read the zone
    virtual float getValue() const override
    {
        return (*fZone > FAUSTFLOAT(0.5)) ? 1.0f : 0.0f;
    }

};

// Link AudioParameterFloat with range parameters

struct FaustPlugInAudioParameterFloat : public juce::AudioParameterFloat, public uiOwnedItem {
    
    FaustPlugInAudioParameterFloat(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    // Pass the Faust step: the (min, max, init) constructor snaps every value to a 0.01 grid
    :juce::AudioParameterFloat(juce::ParameterID(path, /* versionHint */ 1), label, juce::NormalisableRange<float>(float(min), float(max), float(step)), float(init)), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterFloat() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        if (v >= range.start && v <= range.end) {
            setValueNotifyingHost(range.convertTo0to1(float(v)));
        }
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(range.convertFrom0to1(newValue)));
    }
    
    // The base class value is only updated by its own setValue, so read the zone
    virtual float getValue() const override
    {
        return range.convertTo0to1(range.getRange().clipValue(float(*fZone)));
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

class JuceParameterUI : public GUI, public PathBuilder {
    
    private:
        
        struct Control {
            FAUSTFLOAT* fZone;
            std::string fPath;
            std::string fLabel;
            bool fIsBool;
            FAUSTFLOAT fInit, fMin, fMax, fStep;
        };
        
        juce::AudioProcessor* fProcessor;
        std::vector<Control> fControls;
        
        void addControl(const char* label, FAUSTFLOAT* zone, bool is_bool,
                        FAUSTFLOAT init = 0, FAUSTFLOAT min = 0, FAUSTFLOAT max = 1, FAUSTFLOAT step = 0)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fControls.push_back({ zone, path, label, is_bool, init, min, max, step });
        }
        
        void createParameters()
        {
            computeShortNames();
            for (const auto& control : fControls) {
            #ifdef FAUST_JUCE_FULLPATH_IDS
                const std::string& id = control.fPath;
            #else
                const std::string& id = fFull2Short[control.fPath];
            #endif
                if (control.fIsBool) {
                    fProcessor->addParameter(new FaustPlugInAudioParameterBool(this, control.fZone, id, control.fLabel));
                } else {
                    fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, control.fZone, id, control.fLabel,
                                                                                control.fInit, control.fMin, control.fMax, control.fStep));
                }
            }
            fControls.clear();
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
