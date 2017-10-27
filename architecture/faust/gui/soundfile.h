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

#ifndef __soundfile__
#define __soundfile__

#include <sndfile.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define BUFFER_SIZE     1024
#define SAMPLE_RATE     44100
#define MAX_CHAN        64

#define MIN_CHAN(a,b) ((a) < (b) ? (a) : (b))

struct Soundfile {
    
    int length;
    int rate;
    int chans;
    FAUSTFLOAT** channels;
    
    Soundfile(const std::string& name, int max_chan)
    {
        channels = new FAUSTFLOAT*[max_chan];
        if (!channels) {
            throw std::bad_alloc();
        }
     
        // Open sndfile
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(name.c_str(), SFM_READ, &snd_info);
        
        if (snd_file) {
            
            chans = MIN_CHAN(max_chan, snd_info.channels);
            length = int(snd_info.frames);
            rate = snd_info.samplerate;
            
            for (int chan = 0; chan < chans; chan++) {
                channels[chan] = new FAUSTFLOAT[snd_info.frames];
                if (!channels[chan]) {
                    throw std::bad_alloc();
                }
            }
            
            // Read and fill snd_info.channels number of channels
            int nbf, index = 0;
            double buffer[BUFFER_SIZE * snd_info.channels];
            do {
                nbf = int(sf_readf_double(snd_file, buffer, BUFFER_SIZE));
                for (int sample = 0; sample < nbf; sample++) {
                    for (int chan = 0; chan < chans; chan++) {
                        channels[chan][index + sample] = (FAUSTFLOAT)buffer[sample * snd_info.channels + chan];
                    }
                }
                index += nbf;
            } while (nbf == BUFFER_SIZE);
            
            // Share the same buffers for all other channels so that we have max_chan channels available
            for (int chan = chans; chan < max_chan; chan++) {
                channels[chan] = channels[chan % snd_info.channels];
            }
      
            sf_close(snd_file);
            
        } else {
            
            if (name != "") {
                std::cerr << "Error opening the file : " << name << std::endl;
            }
            
            chans = 1;
            length = BUFFER_SIZE;
            rate = SAMPLE_RATE;
            
            // Allocate 1 channel
            channels[0] = new FAUSTFLOAT[BUFFER_SIZE];
            if (!channels[0]) {
                throw std::bad_alloc();
            }
            memset(channels[0], 0, BUFFER_SIZE * sizeof(FAUSTFLOAT));
            
            // Share the same buffer for all other channels so that we have max_chan channels available
            for (int chan = chans; chan < max_chan; chan++) {
                channels[chan] = channels[0];
            }
        }
    }
    
    ~Soundfile()
    {
        for (int chan = 0; chan < chans; chan++) {
            delete channels[chan];
        }
        delete [] channels;
    }
    
};

#endif
