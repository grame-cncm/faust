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

#ifndef __MemoryReader__
#define __MemoryReader__

#include "faust/gui/Soundfile.h"

/*
 A 'MemoryReader' object can be used to prepare a set of sound resources in memory, to be used by SoundUI::addSoundfile.
 */

struct MemoryReader : public SoundfileReader {
    
    // To implement
    virtual bool check(const std::string& path_name) { return false; }
    
    virtual void getParams(const std::string& path_name, int& channels, int& length) {}
    
    virtual void read(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan) {}
    
};

#endif
