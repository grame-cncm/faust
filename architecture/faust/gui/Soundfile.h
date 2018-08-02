/************************************************************************
 FAUST Architecture File
 Copyright (C) 2017 GRAME, Centre National de Creation Musicale
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

#ifndef __Soundfile__
#define __Soundfile__

#include <iostream>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define BUFFER_SIZE 1024
#define SAMPLE_RATE 44100
#define MAX_CHAN 64

#ifdef _MSC_VER
#define PRE_PACKED_STRUCTURE __pragma(pack(push, 1))
#define POST_PACKED_STRUCTURE \
    ;                         \
    __pragma(pack(pop))
#else
#define PRE_PACKED_STRUCTURE
#define POST_PACKED_STRUCTURE __attribute__((__packed__))
#endif

/*
 The soundfile structure to be used by the DSP code.
 It has to be 'packed' to that the LLVM backend can correctly access it.
*/

/*
    New index computation:
    - P is the number of part P>0
    - p is the current part number [0..P-1]
    - i is the current position in the part [0..length]
    - maxidx(p) = fPartBegin[p+1] - fPartBegin[p] - 1;
    - idx(p,i)  = min(fPartBegin[p] + i, fPartBegin[p+1] - 1);
*/

PRE_PACKED_STRUCTURE
struct Soundfile {
    FAUSTFLOAT** fBuffers;
    int          fLength;
    int          fSampleRate;
    int          fChannels;
    int          fNumParts;
    int          fPartBegin[256];

    Soundfile()
    {
        fBuffers    = NULL;
        fLength     = -1;
        fSampleRate = -1;
        fChannels   = -1;
    }

    ~Soundfile()
    {
        // Free the real channels only
        for (int chan = 0; chan < fChannels; chan++) {
            delete fBuffers[chan];
        }
        delete[] fBuffers;
    }

} POST_PACKED_STRUCTURE;

/*
 The generic soundfile reader.
 */

class SoundfileReader {
   protected:
    void FillDefault(Soundfile* soundfile, const std::string& path_name_str, int max_chan)
    {
        if (path_name_str != "") {
            std::cerr << "Error opening the file : " << path_name_str << std::endl;
        }

        soundfile->fChannels   = 1;
        soundfile->fLength     = BUFFER_SIZE;
        soundfile->fSampleRate = SAMPLE_RATE;

        // Allocate 1 channel
        soundfile->fBuffers[0] = new FAUSTFLOAT[BUFFER_SIZE];
        if (!soundfile->fBuffers[0]) {
            throw std::bad_alloc();
        }
        memset(soundfile->fBuffers[0], 0, BUFFER_SIZE * sizeof(FAUSTFLOAT));

        // Share the same buffer for all other channels so that we have max_chan channels available
        for (int chan = soundfile->fChannels; chan < max_chan; chan++) {
            soundfile->fBuffers[chan] = soundfile->fBuffers[0];
        }
    }

    Soundfile* Create(int max_chan)
    {
        Soundfile* soundfile = new Soundfile();
        if (!soundfile) {
            throw std::bad_alloc();
        }
        soundfile->fBuffers = new FAUSTFLOAT*[max_chan];
        if (!soundfile->fBuffers) {
            throw std::bad_alloc();
        }
        return soundfile;
    }

   public:
    virtual ~SoundfileReader() {}

    virtual Soundfile* Read(const std::string& path_name_str, int max_chan) = 0;

    virtual std::string CheckAux(const std::string& path_name_str) = 0;

    // Check if soundfile exists and return the real path_name
    static std::string Check(const std::vector<std::string>& sound_directories, const std::string& file_name_str);
};

#endif
