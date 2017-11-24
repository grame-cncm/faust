/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
#include <string>

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/soundfile.h"

class SoundUI : public GenericUI
{
		
    private:
     
        std::map<std::string, Soundfile*> fSFMap;
    
     public:
            
        SoundUI(){}
    
        virtual ~SoundUI()
        {   
            // delete all soundfiles
            std::map<std::string, Soundfile*>::iterator it;
            for (it = fSFMap.begin(); it != fSFMap.end(); it++) {
                delete (*it).second;
            }
        }

        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
        {
            // If no filename was given, assume label is the filename
            if (strlen(filename) == 0) filename = label;
            
        #if TARGET_OS_IPHONE
            string filename_path_str = string([[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSUTF8StringEncoding]) + "/" + string(filename);
            const char* filename_path = filename_path_str.c_str();
        #else
            const char* filename_path = filename;
        #endif
            // Check if 'label' is already loaded
            if (fSFMap.find(filename) == fSFMap.end()) {
                fSFMap[filename] = new Soundfile(filename_path, 64);
            }
            *sf_zone = fSFMap[filename];
        }
  
};

// To be used by dsp code if no SoundUI is used
static Soundfile* defaultsound = new Soundfile("", MAX_CHAN);

#endif
