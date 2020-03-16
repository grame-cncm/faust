/************************** BEGIN WaveReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef __WaveReader__
#define __WaveReader__

#include <string.h>
#include <assert.h>
#include <iostream>

#include "faust/gui/Soundfile.h"

typedef struct {
    
    // The canonical WAVE format starts with the RIFF header
    
    /**
     Variable: chunk_id
     Contains the letters "RIFF" in ASCII form (0x52494646 big-endian form).
     **/
    int chunk_id;
    
    /**
     Variable: chunk_size
     36 + SubChunk2Size, or more precisely: 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
     This is the size of the rest of the chunk following this number.
     This is the size of the entire file in bytes minus 8 bytes for the
     two fields not included in this count: ChunkID and ChunkSize.
     **/
    int chunk_size;
    
    /**
     Variable: format
     Contains the letters "WAVE" (0x57415645 big-endian form).
     **/
    int format;
    
    // The "WAVE" format consists of two subchunks: "fmt " and "data":
    // The "fmt " subchunk describes the sound data's format:
    
    /**
     Variable: subchunk_1_id
     Contains the letters "fmt " (0x666d7420 big-endian form).
     **/
    int subchunk_1_id;
    
    /**
     Variable: subchunk_1_size
     16 for PCM. This is the size of the rest of the Subchunk which follows this number.
     **/
    int subchunk_1_size;
    
    /**
     Variable: audio_format
     PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.
     **/
    short audio_format;
    
    /**
     Variable: num_channels
     Mono = 1, Stereo = 2, etc.
     **/
    short num_channels;
    
    /**
     Variable: sample_rate
     8000, 44100, etc.
     **/
    int sample_rate;
    
    /**
     Variable: byte_rate
     == SampleRate * NumChannels * BitsPerSample/8
     **/
    int byte_rate;
    
    /**
     Variable: block_align
     == NumChannels * BitsPerSample/8
     The number of bytes for one sample including all channels. I wonder what happens
     when this number isn't an integer?
     **/
    short block_align;
    
    /**
     Variable: bits_per_sample
     8 bits = 8, 16 bits = 16, etc.
     **/
    short bits_per_sample;
    
    /**
     Here should come some extra parameters which i will avoid.
     **/
    
    // The "data" subchunk contains the size of the data and the actual sound:
    
    /**
     Variable: subchunk_2_id
     Contains the letters "data" (0x64617461 big-endian form).
     **/
    int subchunk_2_id;
    
    /**
     Variable: subchunk_2_size
     == NumSamples * NumChannels * BitsPerSample/8
     This is the number of bytes in the data. You can also think of this as the size
     of the read of the subchunk following this number.
     **/
    int subchunk_2_size;
    
    /**
     Variable: data
     The actual sound data.
     **/
    char* data;
    
} wave_t;

inline int is_big_endian()
{
    int a = 1;
    return !((char*)&a)[0];
}

inline int convert_to_int(char* buffer, int len)
{
    int a = 0;
    if (!is_big_endian()) {
        for(int i = 0; i < len; i++) {
            ((char*)&a)[i] = buffer[i];
        }
    } else {
        for(int i = 0; i < len; i++) {
            ((char*)&a)[3-i] = buffer[i];
        }
    }
    return a;
}

inline void read_file(char* buffer, unsigned int size, FILE* file)
{
    fread(buffer, 1, size, file);
}

void close_wave_file(wave_t* wave_file);

inline bool read_wave_file_header(wave_t* wav_file, FILE* file)
{
    char buffer[4];
    
    read_file(buffer, 4, file);
    if (strncmp(buffer, "RIFF", 4) != 0) {
        std::cerr << "This is not valid WAV file!\n";
        return false;
    }
    wav_file->chunk_id = convert_to_int(buffer, 4);
    
    read_file(buffer, 4, file);
    wav_file->chunk_size = convert_to_int(buffer, 4);
    
    read_file(buffer, 4, file);
    wav_file->format = convert_to_int(buffer, 4);
    
    read_file(buffer, 4, file);
    wav_file->subchunk_1_id = convert_to_int(buffer, 4);
    
    read_file(buffer, 4, file);
    wav_file->subchunk_1_size = convert_to_int(buffer, 4);
    
    read_file(buffer, 2, file);
    wav_file->audio_format = convert_to_int(buffer, 2);
    
    read_file(buffer, 2, file);
    wav_file->num_channels = convert_to_int(buffer, 2);
    
    read_file(buffer, 4, file);
    wav_file->sample_rate = convert_to_int(buffer, 4);
    
    read_file(buffer, 4, file);
    wav_file->byte_rate = convert_to_int(buffer, 4);
    
    read_file(buffer, 2, file);
    wav_file->block_align = convert_to_int(buffer, 2);
    
    read_file(buffer, 2, file);
    wav_file->bits_per_sample = convert_to_int(buffer, 2);
    
    read_file(buffer, 4, file);
    if (strncmp(buffer, "data", 4) != 0) {
        read_file(buffer, 4, file);
        int _extra_size = convert_to_int(buffer, 4);
        char _extra_data[_extra_size];
        read_file(_extra_data, _extra_size, file);
        read_file(buffer, 4, file);
        wav_file->subchunk_2_id = convert_to_int(buffer, 4);
    } else {
        wav_file->subchunk_2_id = convert_to_int(buffer, 4);
    }
    
    read_file(buffer, 4, file);
    wav_file->subchunk_2_size = convert_to_int(buffer, 4);
    return true;
}

// Public API

wave_t* load_wave_file_header(const char* file_path)
{
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        std::cerr << "Cannot open file!\n";
        return nullptr;
    }
    
    wave_t* wav_file = (wave_t*)calloc(1, sizeof(wave_t));
    bool res = read_wave_file_header(wav_file, file);
    fclose(file);
    
    if (res) {
        return wav_file;
    } else {
        close_wave_file(wav_file);
        return nullptr;
    }
}

wave_t* load_wave_file(const char* file_path)
{
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        std::cerr << "Cannot open file!\n";
        return nullptr;
    }
    
    wave_t* wav_file = (wave_t*)calloc(1, sizeof(wave_t));
    bool res = read_wave_file_header(wav_file, file);
    assert(res);
    
    // Read sound data
    wav_file->data = (char*)malloc(wav_file->subchunk_2_size);
    read_file(wav_file->data, wav_file->subchunk_2_size, file);
    
    std::cout << "load_wave_file " << wav_file->subchunk_2_size << "\n";
    
    fclose(file);
    return wav_file;
}

void close_wave_file(wave_t* wave_file)
{
    free(wave_file->data);
    free(wave_file);
}

struct WaveReader : public SoundfileReader {
    
    WaveReader() {}
    
    bool checkFile(const std::string& path_name)
    {
        FILE* file = fopen(path_name.c_str(), "rb");
        if (!file) {
            std::cerr << "Cannot open file!\n";
            return false;
        } else {
            wave_t* wav_file = load_wave_file_header(path_name.c_str());
            fclose(file);
            return (wav_file != nullptr);
        }
    }
    
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        wave_t* wav_file = load_wave_file_header(path_name.c_str());
        channels = wav_file->num_channels;
        length = (wav_file->subchunk_2_size * 8) / (wav_file->num_channels * wav_file->bits_per_sample);
        close_wave_file(wav_file);
    }
    
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        wave_t* wav_file = load_wave_file(path_name.c_str());
        assert(wav_file);
        
        soundfile->fLength[part] = (wav_file->subchunk_2_size * 8) / (wav_file->num_channels * wav_file->bits_per_sample);
        soundfile->fSR[part] = wav_file->sample_rate;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        if (wav_file->bits_per_sample == 16) {
            float factor = 1.f/32767.f;
            for (int sample = 0; sample < soundfile->fLength[part]; sample++) {
                short* frame = (short*)&wav_file->data[wav_file->block_align * sample];
                for (int chan = 0; chan < wav_file->num_channels; chan++) {
                    soundfile->fBuffers[chan][offset + sample] = frame[chan] * factor;
                }
            }
        } else if (wav_file->bits_per_sample == 32) {
            std::cerr << "readFile: not implemented \n";
        }
        
        // Update offset
        offset += soundfile->fLength[part];
        close_wave_file(wav_file);
    }
};

#endif
/**************************  END  WaveReader.h **************************/
