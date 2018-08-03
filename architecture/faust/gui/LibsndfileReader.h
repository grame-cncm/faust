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

#ifndef __LibsndfileReader__
#define __LibsndfileReader__

#include <sndfile.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "faust/gui/Soundfile.h"

struct LibsndfileReader : public SoundfileReader {
    
    LibsndfileReader() {}
    
    typedef sf_count_t (* sample_read)(SNDFILE* sndfile, FAUSTFLOAT* ptr, sf_count_t frames);
    
    std::string checkAux(const std::string& path_name)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        if (snd_file) {
            sf_close(snd_file);
            return path_name;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "' (" << sf_strerror(NULL) << ")" << std::endl;
            return "";
        }
    }
    
    // Open the file and returns its length and channels
    void open(const std::string& path_name, int& channels, int& length)
    {
        std::cout << "open " << path_name << std::endl;
        
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        assert(snd_file);
        channels = int(snd_info.channels);
        length = int(snd_info.frames);
        sf_close(snd_file);
        std::cout << "channels " << channels << std::endl;
        std::cout << "length " << length << std::endl;
    }
    
    // Will be called to fill all parts from 0 to MAX_PART-1
    void readOne(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        // Open sndfile
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        assert(snd_file);
        
        std::cout << "readOne " <<  path_name << std::endl;
        
        int channels = std::min(max_chan, snd_info.channels);
        
        soundfile->fLength[part] = int(snd_info.frames);
        soundfile->fOffset[part] = offset;
        soundfile->fSampleRate[part] = snd_info.samplerate;
        
        // Read and fill snd_info.channels number of channels
        sf_count_t nbf, index = offset;
        FAUSTFLOAT buffer[BUFFER_SIZE * snd_info.channels];
        sample_read reader;
        
        if (sizeof(FAUSTFLOAT) == 4) {
            reader = reinterpret_cast<sample_read>(sf_readf_float);
        } else {
            reader = reinterpret_cast<sample_read>(sf_readf_double);
        }
        do {
            nbf = reader(snd_file, buffer, BUFFER_SIZE);
            for (int sample = 0; sample < nbf; sample++) {
                for (int chan = 0; chan < channels; chan++) {
                    soundfile->fBuffers[chan][index + sample] = buffer[sample * snd_info.channels + chan];
                }
            }
            index += nbf;
        } while (nbf == BUFFER_SIZE);
        
        // Copy the read buffer up to soundfile->fChannels is necessary
        for (int chan = 0; chan < (soundfile->fChannels - channels); chan++) {
            memcpy(&soundfile->fBuffers[chan + channels][offset], &soundfile->fBuffers[chan][offset], sizeof(FAUSTFLOAT) * int(snd_info.frames));
        }
        
        std::cout << "readOne soundfile->fLength[part] " <<  soundfile->fLength[part] << std::endl;
        std::cout << "readOne soundfile->fOffset[part] " <<  soundfile->fOffset[part] << std::endl;
        std::cout << "readOne soundfile->fSampleRate[part] " <<  soundfile->fSampleRate[part] << std::endl;
        
        // Update offset
        offset += soundfile->fLength[part];
        
        sf_close(snd_file);
    }
    
    static Soundfile* createSoundfile(const std::vector<std::string>& path_name_list, int max_chan)
    {
        LibsndfileReader reader;
        return reader.read(path_name_list, max_chan);
    }
};

#endif
