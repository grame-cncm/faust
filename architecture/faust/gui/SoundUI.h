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

#ifdef __APPLE__
#include <CoreFoundation/CFBundle.h>
#endif

#include "faust/gui/DecoratorUI.h"

// Always included otherwise -i mode later on will not always include it (with the conditional includes)
#include "faust/gui/Soundfile.h"

#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
#include "faust/gui/JuceReader.h"
Soundfile* createSoundfile(const std::string& path_name_str, int max_chan)
{
    Soundfile* sf = new Soundfile();
    JuceReader reader(sf, path_name_str, max_chan);
    return sf;
}
#else
#include "faust/gui/LibsndfileReader.h"
Soundfile* createSoundfile(const std::string& path_name_str, int max_chan)
{
    Soundfile* sf = new Soundfile();
    LibsndfileReader reader(sf, path_name_str, max_chan);
    return sf;
}
#endif

// To be used by dsp code if no SoundUI is used or when soundfile is not found
extern "C" Soundfile* defaultsound = createSoundfile("", MAX_CHAN);

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
            std::string sha_key;
            std::string path_name_str = SoundfileReader::Check(fSoundfileDir, url, sha_key);
            if (path_name_str != "") {
                std::string file_key = (sha_key == "") ? path_name_str : sha_key;
                // Check if 'file_key' is already loaded
                if (fSoundfileMap.find(file_key) == fSoundfileMap.end()) {
                    fSoundfileMap[file_key] = createSoundfile(path_name_str, 64);
                }
                // Get the soundfile
                *sf_zone = fSoundfileMap[file_key];
            } else {
                // Take the defaultsound
                std::cout << "addSoundfile : defaultsound\n";
                *sf_zone = defaultsound;
            }
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
            return bundle_path_str;
        }
};

// Check if soundfile exists and return the real path_name
std::string SoundfileReader::Check(const std::vector<std::string>& sound_directories, const std::string& file_name_str, std::string& sha_key)
{
#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
    JuceReader reader;
#else
    LibsndfileReader reader;
#endif
    std::string path_name_str = reader.CheckAux(file_name_str, sha_key);
    if (path_name_str != "") {
        return path_name_str;
    } else {
        for (int i = 0; i < sound_directories.size(); i++) {
            std::string res = reader.CheckAux(sound_directories[i] + "/" + file_name_str, sha_key);
            if (res != "") { return res; }
        }
        return "";
    }
}

#endif
