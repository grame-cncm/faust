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

#ifndef __JuceReader__
#define __JuceReader__

#include "faust/gui/Soundfile.h"

struct JuceReader : public SoundfileReader {
    
    std::string CheckAux(const std::string& path_name_str)
    {
        File file(path_name_str);
        if (file.existsAsFile()) {
            return path_name_str;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name_str << std::endl;
            return "";
        }
    }
    
    JuceReader() {}
    
    Soundfile* Read(const std::string& path_name_str, int max_chan)
    {
        Soundfile* soundfile = Create(max_chan);
        
        AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        
        ScopedPointer<AudioFormatReader> formatReader = formatManager.createReaderFor(File(path_name_str));
        if (formatReader) {
            
            soundfile->fChannels = int(formatReader->numChannels);
            soundfile->fSampleRate = int(formatReader->sampleRate);
            soundfile->fLength = int(formatReader->lengthInSamples);
            
            for (int chan = 0; chan < soundfile->fChannels; chan++) {
                soundfile->fBuffers[chan] = new FAUSTFLOAT[soundfile->fLength];
                if (!soundfile->fBuffers[chan]) {
                    throw std::bad_alloc();
                }
            }
            
            if (formatReader->read(reinterpret_cast<int *const *>(soundfile->fBuffers), soundfile->fChannels, 0, soundfile->fLength, false)) {
                // Possibly concert samples
                if (!formatReader->usesFloatingPointData) {
                    for (int chan = 0; chan < soundfile->fChannels; ++chan) {
                        FAUSTFLOAT* buffer = soundfile->fBuffers[chan];
                        FloatVectorOperations::convertFixedToFloat(buffer, reinterpret_cast<const int*>(buffer), 1.0f/0x7fffffff, soundfile->fLength);
                    }
                }
                // Share the same buffers for all other channels so that we have max_chan channels available
                for (int chan = soundfile->fChannels; chan < max_chan; chan++) {
                    soundfile->fBuffers[chan] = soundfile->fBuffers[chan % soundfile->fChannels];
                }
            } else {
                std::cerr << "Error opening the file : " << path_name_str << std::endl;
            }
            
        } else {
            FillDefault(soundfile, path_name_str, max_chan);
        }
        
        return soundfile;
    }
    
    static Soundfile* createSoundfile(const std::string& path_name_str, int max_chan)
    {
        JuceReader reader;
        return reader.Read(path_name_str, max_chan);
    }
    
};

#endif
