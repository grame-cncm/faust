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
#include <sys/stat.h>

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

    static std::string appendSlashIfMissing(const std::string& path)
    {
        return (path[path.size() - 1] != '/') ? (path + "/") : path;
    }
  
    static bool tryCreateSubdirectory(const std::string& base_dir, const std::string& sub_dir, std::string& out_dir)
    {
        if ((base_dir.size() > 0) && (sub_dir.size() > 0)) {
            out_dir = base_dir + sub_dir;
            if (tryCreateDirectory(out_dir)) {
                std::cout << "Using " << base_dir << "/" << sub_dir << ": " << out_dir << std::endl;
                return true;
            } else {
                std::cout << "Cannot use " << base_dir << "/" << sub_dir << std::endl;
            }
        }
        return false;
    }
    
    static bool tryCreateDirFromEnv(const std::string& env_var_name, std::string& out_dir)
    {
        const char* dir = getenv(env_var_name.c_str());
        if (dir && tryCreateDirectory(dir)) {
            std::cout << "Using " << env_var_name << ": " << dir << "." << std::endl;
            out_dir = appendSlashIfMissing(dir);
            return true;
        } else {
            std::cout << "Cannot use " << env_var_name <<  "." << std::endl;
            return false;
        }
    }

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
      
    static bool tryCreateDirectory(const std::string& out_dir)
    {
        if (out_dir.size() > 0) {
            struct stat stat_buffer;
            if (stat(out_dir.c_str(), &stat_buffer) != 0) {
                if (mkdir(out_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
                    std::cout << "Directory created: " << out_dir << std::endl;
                    return true;
                } else {
                    std::cerr << "Error creating directory: " << strerror(errno) << std::endl;
                }
            } else {
                return true;
            }
        }
        return false;
    }
    
    /*
     getPresetDir attempts to determine a suitable preset directory using the following logic:
     
     1) If PRESETDIR is "auto", it tries to create a directory using the XDG_DOCUMENTS_DIR environment variable.
     2) If PRESETDIR is a valid existing directory, it returns the path with a trailing slash.
     3) If PRESETDIR is an environment variable, it tries to create a directory using its value.
     4) If HOME is set, it tries to create a directory at HOME/Documents or HOME/PRESETDIR.
     5) If all else fails, it falls back to /var/tmp/.
     */
    
    static std::string getPresetDir()
    {
        std::string preset_dir;
        
        std::cout << "Attempting to find or create a suitable directory for preset files." << std::endl;
        // If the user passes -preset auto
        if (std::string(PRESETDIR) == "auto") {
            std::cout << "Attempting to create directory using XDG_DOCUMENTS_DIR environment variable." << std::endl;
            if (tryCreateDirFromEnv("XDG_DOCUMENTS_DIR", preset_dir)) {
                return preset_dir;
            }
        }
        
        // Interpret what the user gave us as a path
        struct stat stat_buffer;
        // See if that path exists and is a directory
        if (stat(PRESETDIR, &stat_buffer) == 0 && S_ISDIR(stat_buffer.st_mode)) {
            std::cout << "Directory " << PRESETDIR << " exists and is a valid directory." << std::endl;
            // We are done
            return appendSlashIfMissing(PRESETDIR);
        }
        
        // PRESETDIR doesn't exists or is not a directory
        std::cout << "Directory " << PRESETDIR << " doesn't exist or is not a valid directory." << std::endl;
        
        // Interpret PRESETDIR as an environment variable
        std::cout << "Attempting to create directory using PRESETDIR environment variable." << std::endl;
        if (tryCreateDirFromEnv(PRESETDIR, preset_dir)) {
            return preset_dir;
        }
        
        std::cout << "No usable XDG_DOCUMENTS_DIR, " << PRESETDIR << " is not a valid directory nor a usable environment variable.\n";
        preset_dir = appendSlashIfMissing(getenv("HOME"));
    
        // Try HOME/Documents
        std::string home_preset_dir1;
        if (tryCreateSubdirectory(preset_dir, "Documents", home_preset_dir1)) {
            return home_preset_dir1;
        }
        
        // Try HOME/PRESETDIR
        std::string home_preset_dir2;
        if (tryCreateSubdirectory(preset_dir, PRESETDIR, home_preset_dir2)) {
            return home_preset_dir2;
        }
        
        // Fallback to /var/tmp/
        std::cout << "No suitable directory found, falling back to /var/tmp/" << std::endl;
        preset_dir = "/var/tmp/";
        return preset_dir;
    }
    
};

#endif
/**************************  END  PresetUI.h **************************/
