/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __PresetUI_H__
#define __PresetUI_H__

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/FUI.h"
#include "faust/gui/GUI.h"

class PresetUI;

struct LoaderUI : public GUI
{
    PresetUI* fPresetUI;
    
    LoaderUI(PresetUI* presetui);
        
};

class PresetUI : public DecoratorUI
{
    friend LoaderUI;
		
    private:
    
        int fGroupCount;
        FAUSTFLOAT fPreset;
        FAUSTFLOAT fLoad;
        FAUSTFLOAT fSave;
        FUI fFileUI;
        LoaderUI fLoaderUI;
        std::string fRootFolder;
    
        static void load(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<PresetUI*>(arg)->loadState();
            }
        }
    
        static void save(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<PresetUI*>(arg)->saveState();
            }
        }
    
        void checkOpenFirstBox(const char* label)
        {
            if (fGroupCount++ == 0) {
                fUI->openHorizontalBox("Preset manager");
                fUI->addButton("Save", &fSave);
                fUI->addNumEntry("Number", &fPreset, FAUSTFLOAT(0),FAUSTFLOAT(0), FAUSTFLOAT(100), FAUSTFLOAT(1));
                fUI->addButton("Load", &fLoad);
                fUI->closeBox();
            }
        }
    
    public:
    
        PresetUI(UI* ui, const std::string& root_folfer):
            DecoratorUI(ui),
            fGroupCount(0),
            fPreset(FAUSTFLOAT(0)),
            fSave(FAUSTFLOAT(0)),
            fLoad(FAUSTFLOAT(0)),
            fLoaderUI(this),
            fRootFolder(root_folfer)
        {}
    
        virtual ~PresetUI()
        {}
    
        virtual void saveState()
        {
            std::stringstream str;
            str << fRootFolder << "_preset" << int(fPreset);
            fFileUI.saveState(str.str().c_str());
        }
    
        virtual void loadState()
        {
            std::stringstream str;
            str << fRootFolder << "_preset" << int(fPreset);
            fFileUI.recallState(str.str().c_str());
        }
    
        // -- widget's layouts
        virtual void openTabBox(const char* label)
        {
            checkOpenFirstBox(label);
            fUI->openTabBox(label);
            fFileUI.openTabBox(label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            checkOpenFirstBox(label);
            fUI->openHorizontalBox(label);
            fFileUI.openHorizontalBox(label);
        }
        virtual void openVerticalBox(const char* label)
        {
            checkOpenFirstBox(label);
            fUI->openVerticalBox(label);
            fFileUI.openVerticalBox(label);
        }
        virtual void closeBox()
        {
            fGroupCount--;
            fUI->closeBox();
            fFileUI.closeBox();
        }
    
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fUI->addButton(label, zone);
            fFileUI.addButton(label, zone);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fUI->addCheckButton(label, zone);
            fFileUI.addCheckButton(label, zone);
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUI->addVerticalSlider(label, zone, init, min, max, step);
            fFileUI.addVerticalSlider(label, zone, init, min, max, step);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUI->addHorizontalSlider(label, zone, init, min, max, step);
            fFileUI.addHorizontalSlider(label, zone, init, min, max, step);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUI->addNumEntry(label, zone, init, min, max, step);
            fFileUI.addNumEntry(label, zone, init, min, max, step);
        }
        
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fUI->addHorizontalBargraph(label, zone, min, max);
            fFileUI.addHorizontalBargraph(label, zone, min, max);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fUI->addVerticalBargraph(label, zone, min, max);
            fFileUI.addVerticalBargraph(label, zone, min, max);
        }
        
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
        {
            fUI->addSoundfile(label, filename, sf_zone);
            fFileUI.addSoundfile(label, filename, sf_zone);
        }
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fUI->declare(zone, key, val);
            fFileUI.declare(zone, key, val);
        }

};

LoaderUI::LoaderUI(PresetUI* presetui)
{
    new uiCallbackItem(this, &presetui->fLoad, PresetUI::load, presetui);
    new uiCallbackItem(this, &presetui->fSave, PresetUI::save, presetui);
}

#endif
