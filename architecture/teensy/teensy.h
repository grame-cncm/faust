/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
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

#ifndef faust_teensy_h_
#define faust_teensy_h_

#include <string>

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

class dsp;
class MapUI;
class MidiUI;
#if MIDICTRL
class teensy_midi;
#endif

class AudioFaust : public AudioStream
{
    public:
    
        AudioFaust();
        ~AudioFaust();
    
        virtual void update(void);
    
        void setParamValue(const std::string& path, float value);
        float getParamValue(const std::string& path);
    
    private:
    
        template <int INPUTS, int OUTPUTS>
        void updateImp(void);
    
        float** fInChannel;
        float** fOutChannel;
        MapUI* fUI;
    #if MIDICTRL
        teensy_midi* fMIDIHandler;
        MidiUI* fMIDIInterface;
    #endif
        dsp* fDSP;
};

#endif
