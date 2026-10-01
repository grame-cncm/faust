/*
 Checks that a soundfile read with more channels than it actually has reads channel
 'chan % fChannels' (see architecture/faust/gui/Soundfile.h).

 The DSP (wrap.dsp) reads a 3 channels file with 70 outputs, more than the former MAX_CHAN (64)
 limit. The file is loaded with SoundUI and LibsndfileReader, which only allocate the 3 real
 channel buffers: built with AddressSanitizer, any read past them is reported.

 The generated DSP class is included with -DGENERATED="file". EXT_CONTROL has to be defined
 when the DSP is compiled with -ec, SOUND_DOUBLE when it is compiled with -double.
*/

#include <cmath>
#include <cstdio>
#include <vector>

#include <sndfile.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/SoundUI.h"

#include GENERATED

#define FILE_NAME "wrap3.wav"
#define FILE_CHANNELS 3
#define FILE_FRAMES 256
#define OUTPUTS 70
#define COUNT 64

// Channel c holds (c + 1) + frame / 1024, exactly representable in float
static float sampleValue(int chan, int frame)
{
    return float(chan + 1) + float(frame) / 1024.f;
}

static bool writeFile()
{
    SF_INFO info = {};
    info.samplerate = 44100;
    info.channels   = FILE_CHANNELS;
    info.format     = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    SNDFILE* file   = sf_open(FILE_NAME, SFM_WRITE, &info);
    if (!file) return false;
    std::vector<float> frames(FILE_FRAMES * FILE_CHANNELS);
    for (int frame = 0; frame < FILE_FRAMES; frame++) {
        for (int chan = 0; chan < FILE_CHANNELS; chan++) {
            frames[frame * FILE_CHANNELS + chan] = sampleValue(chan, frame);
        }
    }
    sf_writef_float(file, frames.data(), FILE_FRAMES);
    sf_close(file);
    return true;
}

int main()
{
    if (!writeFile()) {
        printf("ERROR : cannot write '%s'\n", FILE_NAME);
        return 1;
    }

#ifdef SOUND_DOUBLE
    bool is_double = true;
#else
    bool is_double = false;
#endif
    mydsp   dsp;
    SoundUI sound_ui(".", -1, nullptr, is_double);
    dsp.buildUserInterface(&sound_ui);
    dsp.init(44100);

    if (dsp.getNumOutputs() != OUTPUTS) {
        printf("ERROR : %d outputs instead of %d\n", dsp.getNumOutputs(), OUTPUTS);
        return 1;
    }

    std::vector<std::vector<FAUSTFLOAT>> buffers(OUTPUTS, std::vector<FAUSTFLOAT>(COUNT));
    std::vector<FAUSTFLOAT*>             outputs(OUTPUTS);
    for (int out = 0; out < OUTPUTS; out++) outputs[out] = buffers[out].data();
#ifdef EXT_CONTROL
    dsp.control();
#endif
    dsp.compute(COUNT, nullptr, outputs.data());

    int errors = 0;
    for (int out = 0; out < OUTPUTS; out++) {
        int chan = out % FILE_CHANNELS;
        for (int i = 0; i < COUNT; i++) {
            FAUSTFLOAT v = buffers[out][i];
            // Output 'out' has the content of channel 'out % 3', and the same samples as it
            if (int(std::floor(v)) != chan + 1 || v != buffers[chan][i]) {
                if (errors++ < 10) {
                    printf("ERROR : output %d sample %d = %g, expected channel %d\n", out, i, double(v), chan);
                }
            }
        }
    }
    printf("%s\n", errors ? "FAILED" : "PASSED");
    return errors ? 1 : 0;
}
