/************************** BEGIN MiniaudioReader.h *********************
 FAUST Architecture File
 Copyright (C) 2024 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __MiniaudioReader__
#define __MiniaudioReader__

#include <assert.h>
#include <string.h>
#include <fstream>
#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DEVICE_IO        // Disable audio devices
#define MA_NO_ENGINE           // Disable audio engine
#define MA_NO_ENCODING         // Disable encoding
#define MA_NO_RESOURCE_MANAGER // Disable resource manager
#define MA_NO_GENERATION       // Disable audio generation utilities
#define MA_NO_THREADING        // Disables the `ma_thread`, `ma_mutex`, `ma_semaphore` and `ma_event` APIs.
#define MA_NO_NODE_GRAPH

#include "faust/miniaudio.h"
#include "faust/gui/Soundfile.h"

struct MiniaudioReader : public SoundfileReader {
    MiniaudioReader() {}

    bool checkFile(const std::string& path_name) override
    {
        std::ifstream ifs(path_name);
        if (!ifs.is_open()) {
            return false;
        } else {
            // Use miniaudio to open the file and check its properties
            ma_decoder decoder;
            ma_result  result = ma_decoder_init_file(path_name.c_str(), NULL, &decoder);
            if (result != MA_SUCCESS) {
                return false;
            }
            ma_decoder_uninit(&decoder);
            return true;
        }
    }

    void getParamsFile(const std::string& path_name, int& channels, int& length) override
    {
        ma_decoder decoder;
        ma_result  result = ma_decoder_init_file(path_name.c_str(), NULL, &decoder);
        assert(result == MA_SUCCESS);
        channels = decoder.outputChannels;
        ma_uint64 length_aux;
        result = ma_decoder_get_length_in_pcm_frames(&decoder, &length_aux);
        length = (result == MA_SUCCESS) ? length_aux : -1;
        ma_decoder_uninit(&decoder);
    }

    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset,
                  int max_chan) override
    {
        ma_decoder decoder;
        ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 0, 0);
        ma_result  result        = ma_decoder_init_file(path_name.c_str(), &config, &decoder);
        assert(result == MA_SUCCESS);
        readFileAux(soundfile, decoder, part, offset, max_chan);
        ma_decoder_uninit(&decoder);
    }

    void readFileAux(Soundfile* soundfile, ma_decoder& decoder, int part, int& offset, int max_chan)
    {
        assert(&decoder);
        int channels = std::min<int>(max_chan, decoder.outputChannels);
        ma_uint64 length_aux;
        ma_result result = ma_decoder_get_length_in_pcm_frames(&decoder, &length_aux);
        assert(result == MA_SUCCESS);
        soundfile->fLength[part] = length_aux;
        soundfile->fSR[part]     = decoder.outputSampleRate;
        soundfile->fOffset[part] = offset;

        // Read and fill channels
        float* buffer_in = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * channels));
        ma_uint64 frames;
    
        if (soundfile->fIsDouble) {
            // Convert in double
            double* buffer_out = static_cast<double*>(alloca(BUFFER_SIZE * sizeof(double) * channels));
            do {
                result = ma_decoder_read_pcm_frames(&decoder, buffer_in, BUFFER_SIZE, &frames);
                for (int frame = 0; frame < (BUFFER_SIZE * channels); frame++) {
                    static_cast<double*>(buffer_out)[frame] = double(buffer_in[frame]);
                }
                soundfile->copyToOut(frames, channels, decoder.outputChannels, offset, buffer_out);
                offset += frames;
            } while (result == MA_SUCCESS);
        } else {
            do {
                result = ma_decoder_read_pcm_frames(&decoder, buffer_in, BUFFER_SIZE, &frames);
                soundfile->copyToOut(frames, channels, decoder.outputChannels, offset, buffer_in);
                offset += frames;
            } while (result == MA_SUCCESS);
        }
    }
};

#endif

/**************************  END  MiniaudioReader.h **************************/
