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
 
#ifndef __SoundUI_H__
#define __SoundUI_H__

#include <map>
#include <vector>
#include <string>

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/SimpleParser.h"

#ifdef __APPLE__
#include <CoreFoundation/CFBundle.h>
#endif

// Always included otherwise -i mode later on will not always include it (with the conditional includes)
#include "faust/gui/Soundfile.h"

#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
#include "faust/gui/JuceReader.h"
Soundfile* createSoundfile(const std::vector<std::string>& path_name_list, int max_chan)
{
    return JuceReader::createSoundfile(path_name_list, max_chan);
}
#else
#include "faust/gui/LibsndfileReader.h"
Soundfile* createSoundfile(const std::vector<std::string>& path_name_list, int max_chan)
{
    return LibsndfileReader::createSoundfile(path_name_list, max_chan);
}
#endif

// To be used by dsp code if no SoundUI is used
std::vector<std::string> path_name_list;
extern "C" Soundfile* defaultsound = createSoundfile(path_name_list, MAX_CHAN);

class SoundUI : public GenericUI
{
		
    private:
    
        std::vector<std::string> fSoundfileDir;             // The soundfile directories
        std::map<std::string, Soundfile*> fSoundfileMap;    // Map to share loaded soundfiles
    
     public:
            
        SoundUI(const std::string& sound_directory = "")
        {
            fSoundfileDir.push_back(sound_directory);
        }
    
        SoundUI(const std::vector<std::string>& sound_directories):fSoundfileDir(sound_directories)
        {}
    
        virtual ~SoundUI()
        {   
            // Delete all soundfiles
            std::map<std::string, Soundfile*>::iterator it;
            for (it = fSoundfileMap.begin(); it != fSoundfileMap.end(); it++) {
                delete (*it).second;
            }
        }

        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
        {
            std::vector<std::string> file_name_list;
            bool menu = parseMenuList2(url, file_name_list);
            // If not a list, we have as single file
            if (!menu) { file_name_list.push_back(url); }
            
            // Parse the possible list
            if (fSoundfileMap.find(url) == fSoundfileMap.end()) {
                // Check all files and get their complete path
                std::vector<std::string> path_name_list = SoundfileReader::checkFiles(fSoundfileDir, file_name_list);
                // Read them and create the Soundfile
                fSoundfileMap[url] = createSoundfile(path_name_list, MAX_CHAN);
            }
            
            // Get the soundfile
            *sf_zone = fSoundfileMap[url];
        }
    
        static std::string getBinaryPath(std::string folder = "")
        {
            std::string bundle_path_str;
        #ifdef __APPLE__
            CFURLRef bundle_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
            if (bundle_ref) {
                UInt8 bundle_path[512];
                if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 512)) {
                    bundle_path_str = std::string((char*)bundle_path) + folder;
                }
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
        
        static std::string getBinaryPathFrom(const std::string& path)
        {
            std::string bundle_path_str;
        #ifdef __APPLE__
            CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFStringCreateWithCString(kCFAllocatorDefault, path.c_str(), CFStringGetSystemEncoding()));
            CFURLRef bundle_ref = CFBundleCopyBundleURL(bundle);
            if (bundle_ref) {
                UInt8 bundle_path[512];
                if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 512)) {
                    bundle_path_str = std::string((char*)bundle_path);
                }
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
};

// Check if soundfile exists and return the real path_name
std::string SoundfileReader::checkFile(const std::vector<std::string>& sound_directories, const std::string& file_name)
{
#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
    JuceReader reader;
#else
    LibsndfileReader reader;
#endif
    std::string path_name = reader.checkAux(file_name);
    if (path_name != "") {
        return path_name;
    } else {
        for (int i = 0; i < sound_directories.size(); i++) {
            path_name = reader.checkAux(sound_directories[i] + "/" + file_name);
            if (path_name != "") { return path_name; }
        }
        return "";
    }
}

#endif
