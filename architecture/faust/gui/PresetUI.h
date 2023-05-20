/************************** BEGIN PresetUI.h **************************
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
 
#ifndef __PresetUI_H__
#define __PresetUI_H__

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>

#if __cplusplus < 201703L // If the version of C++ is less than 17
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/FUI.h"
#include "faust/gui/GUI.h"

/*
 Decorates an UI to add preset management:
 - a 'preset' num entry allows to select a given preset
 - a 'load' button restores the state of the currently selected preset
 - a 'save' button saves the state of the currently selected preset
 - a 'reset' button restores te UI default state
 Presets are saved in separated text files using the FUI model.
*/

class PresetUI : public DecoratorUI {
    
    private:
    const char* append_slash_if_missing(const char* path) {
        size_t len = strlen(path);
        if (path[len - 1] != '/') {
            static char buf[PATH_MAX];
            snprintf(buf, sizeof(buf), "%s/", path);
            return buf;
        }
        return path;
    }

    bool try_create_subdirectory(const char* base_dir, const char* sub_dir, char* out_dir, size_t out_dir_size) {
        if (base_dir && (strlen(base_dir) > 0) && sub_dir && (strlen(sub_dir) > 0)) {
            snprintf(out_dir, out_dir_size, "%s%s/", base_dir, sub_dir);
            if (try_create_directory(out_dir)) {
                std::cout << "Using " << base_dir << "/" << sub_dir << ": " << out_dir << std::endl;
                return true;
            } else {
                std::cout << "Cannot use " << base_dir << "/" << sub_dir << std::endl;
            }
        }
        return false;
    }

    bool try_create_dir_from_env(const char* env_var_name, const char** out_dir) {
        const char* dir = getenv(env_var_name);
        if (try_create_directory(dir)) {
            std::cout << "Using " << env_var_name << ": " << dir << "." << std::endl;
            *out_dir = append_slash_if_missing(dir);
            return true;
        } else {
            std::cout << "Cannot use " << env_var_name <<  "." << std::endl;
            return false;
        }
    }

    struct LoaderUI : public GUI
    {
        LoaderUI(PresetUI* presetui)
        {
            // uiCallbackItem(s) are deleted in GUI
            new uiCallbackItem(this, &presetui->fLoad, PresetUI::load, presetui);
            new uiCallbackItem(this, &presetui->fSave, PresetUI::save, presetui);
            new uiCallbackItem(this, &presetui->fReset, PresetUI::reset, presetui);
        }
    };
    
    int fGroupCount;
    FAUSTFLOAT fPreset;
    FAUSTFLOAT fLoad;
    FAUSTFLOAT fSave;
    FAUSTFLOAT fReset;
    FUI fFileUI;
    LoaderUI fLoaderUI;
    const std::string fRootPath;

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

    static void reset(FAUSTFLOAT val, void* arg)
    {
        if (val == FAUSTFLOAT(1)) {
            static_cast<PresetUI*>(arg)->loadDefault();
        }
    }

    void checkOpenFirstBox(const char* label)
    {
        if (fGroupCount++ == 0) {
            // Start of top-level group
            fUI->openHorizontalBox("Preset manager");
            fUI->addButton("Save", &fSave);
            fUI->addNumEntry("Preset", &fPreset, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(100), FAUSTFLOAT(1));
            fUI->addButton("Load", &fLoad);
            fUI->addButton("Reset", &fReset);
            fUI->closeBox();
        }
    }
    
    public:

    bool try_create_directory(const char* dir_option) {
        if (dir_option && (strlen(dir_option) > 0)) {
            // std::cout << "Trying to create: " << dir_option << std::endl;
            fs::path path_option(dir_option);
            if (!fs::exists(path_option)) {
                try {
                    fs::create_directories(path_option);
                    std::cout << "Directory created: " << path_option << std::endl;
                    return true;
                } catch(const fs::filesystem_error& e) {
                    std::cerr << "Error creating directory: " << e.what() << std::endl;
                }
            } else {
                // std::cout << "Directory already exists: " << path_option << std::endl;
                return true;
            }
        }
        return false;
    }
/*
  get_preset_dir attempts to determine a suitable preset directory using the following logic:

  1) If PRESETDIR is "auto", it tries to create a directory using the XDG_DOCUMENTS_DIR environment variable.
  2) If PRESETDIR is a valid existing directory, it returns the path with a trailing slash.
  3) If PRESETDIR is an environment variable, it tries to create a directory using its value.
  4) If HOME is set, it tries to create a directory at HOME/Documents or HOME/PRESETDIR.
  5) If all else fails, it falls back to /var/tmp/.
*/

    const char* get_preset_dir() {
        const char* preset_dir = nullptr;

        std::cout << "Attempting to find or create a suitable directory for preset files." << std::endl;
        // if the user passes -preset auto
        if (std::string(PRESETDIR) == "auto") {
            std::cout << "Attempting to create directory using XDG_DOCUMENTS_DIR environment variable." << std::endl;
            if (try_create_dir_from_env("XDG_DOCUMENTS_DIR", &preset_dir)) {
                return preset_dir;
            }
        }

        // interpret what the user gave us as a path
        fs::path preset_path(PRESETDIR);
        // see if that path exists and is a directory
        if (fs::exists(preset_path) && fs::is_directory(preset_path)) {
            std::cout << "Directory " << PRESETDIR << " exists and is a valid directory." << std::endl;
            // we are done
            return append_slash_if_missing(PRESETDIR);
        }
        // PRESETDIR doesn't exists or is not a directory
        std::cout << "Directory " << PRESETDIR << " doesn't exist or is not a valid directory." << std::endl;

        // interpret PRESETDIR as an environment variable
        std::cout << "Attempting to create directory using PRESETDIR environment variable." << std::endl;
        if (try_create_dir_from_env(PRESETDIR, &preset_dir)) {
            return preset_dir;
        }

        std::cout << "No usable XDG_DOCUMENTS_DIR, " << PRESETDIR << " is not a valid directory nor a usable environment variable." << std::endl;

        preset_dir = append_slash_if_missing(getenv("HOME"));
        // Declare buffers for storing the paths
        static char buf[PATH_MAX];
        static char home_preset_dir_buf[PATH_MAX];
        // Try HOME/Documents
        if (try_create_subdirectory(preset_dir, "Documents", buf, sizeof(buf))) {
            return buf;
        }

        // Try HOME/PRESETDIR
        if (try_create_subdirectory(preset_dir, PRESETDIR, home_preset_dir_buf, sizeof(home_preset_dir_buf))) {
            return home_preset_dir_buf;
        }

        // Fallback to /var/tmp/
        std::cout << "No suitable directory found, falling back to /var/tmp/" << std::endl;
        preset_dir = "/var/tmp/";
        return preset_dir;
    }

    PresetUI(UI* ui, const std::string& path):
        DecoratorUI(ui),
        fGroupCount(0),
        fPreset(FAUSTFLOAT(0)),
        fSave(FAUSTFLOAT(0)),
        fLoad(FAUSTFLOAT(0)),
        fReset(FAUSTFLOAT(0)),
        fLoaderUI(this),
        fRootPath(path)
        {}
    
        virtual ~PresetUI()
        {}
    
        void saveDefault()
        {
            fFileUI.saveState((fRootPath + "default").c_str());
        }
        
        void loadDefault()
        {
            fFileUI.recallState((fRootPath + "default").c_str());
        }
    
        void saveState()
        {
            fFileUI.saveState((fRootPath + "preset" + std::to_string(fPreset)).c_str());
        }
    
        void loadState()
        {
            fFileUI.recallState((fRootPath + "preset" + std::to_string(fPreset)).c_str());
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
            fUI->closeBox();
            if (--fGroupCount == 0) {
                // End of top-level group
                saveDefault();
            }
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

#endif
/**************************  END  PresetUI.h **************************/
