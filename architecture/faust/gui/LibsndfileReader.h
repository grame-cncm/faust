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
#include <iostream>
#include <sstream>
#include <fstream>

#include "faust/gui/Soundfile.h"

struct LibsndfileReader : public SoundfileReader {
    
    typedef sf_count_t (* sample_read)(SNDFILE* sndfile, FAUSTFLOAT* ptr, sf_count_t frames);
    
    std::string CheckAux(const std::string& path_name_str, std::string& sha_key)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name_str.c_str(), SFM_READ, &snd_info);
        if (snd_file) {
            sf_close(snd_file);
            // Possibly read associated SHA_KEY file
            std::string sha_key_path_name_str = path_name_str + "_sha_key";
            std::ifstream reader(sha_key_path_name_str.c_str());
            if (reader.is_open()) {
                std::string sha_key_line;
                getline(reader, sha_key_line);
                std::stringstream line_reader(sha_key_line);
                line_reader >> sha_key;
            }
            return path_name_str;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name_str << "' (" << sf_strerror(NULL) << ")" << std::endl;
            return "";
        }
    }
    
    LibsndfileReader() {}
    
    LibsndfileReader(Soundfile* soundfile, const std::string& path_name_str, int max_chan)
    {
        soundfile->fBuffers = new FAUSTFLOAT*[max_chan];
        if (!soundfile->fBuffers) {
            throw std::bad_alloc();
        }
     
        // Open sndfile
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name_str.c_str(), SFM_READ, &snd_info);
        
        if (snd_file) {
            
            soundfile->fChannels = std::min(max_chan, snd_info.channels);
            soundfile->fLength = int(snd_info.frames);
            soundfile->fSampleRate = snd_info.samplerate;
            
            for (int chan = 0; chan < soundfile->fChannels; chan++) {
                soundfile->fBuffers[chan] = new FAUSTFLOAT[snd_info.frames];
                if (!soundfile->fBuffers[chan]) {
                    throw std::bad_alloc();
                }
            }
            
            // Read and fill snd_info.channels number of channels
            sf_count_t nbf, index = 0;
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
                    for (int chan = 0; chan < soundfile->fChannels; chan++) {
                        soundfile->fBuffers[chan][index + sample] = buffer[sample * snd_info.channels + chan];
                    }
                }
                index += nbf;
            } while (nbf == BUFFER_SIZE);
            
            // Share the same buffers for all other channels so that we have max_chan channels available
            for (int chan = soundfile->fChannels; chan < max_chan; chan++) {
                soundfile->fBuffers[chan] = soundfile->fBuffers[chan % snd_info.channels];
            }
       
            sf_close(snd_file);
            
        } else {
            
            if (path_name_str != "") {
                std::cerr << "Error opening the file : " << path_name_str << std::endl;
            }
            
            soundfile->fChannels = 1;
            soundfile->fLength = BUFFER_SIZE;
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
    }
};

#endif
