/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// Samples in files: an excitation or a reference read (--in file:, --ref),
// a render written (--out). Formats are told apart by the extension: .wav,
// .npy, and raw little-endian .f64 / .f32 of one channel.

#ifndef __faustprobe_audio__
#define __faustprobe_audio__

#include <cstdio>
#include <string>
#include <vector>

#include "text.h"

typedef std::vector<std::vector<double>> Channels;

struct AudioFile {
    Channels      channels;
    Optional<int> sampleRate;  // when the format records one
};

AudioFile readChannels(const std::string& path);

// A file receiving the frames of one render, in order, at the width the
// program was compiled in.
class SampleWriter {
   public:
    SampleWriter(const std::string& path, size_t channels, size_t frames, bool isDouble, int sampleRate);
    ~SampleWriter();
    SampleWriter(const SampleWriter&) = delete;
    SampleWriter& operator=(const SampleWriter&) = delete;

    void push(const std::vector<double>& samples);
    // Flushes, and checks that the announced frames were written: the headers
    // carry the count, and a short file with a long header reads as garbage.
    void finish();

   private:
    std::string fPath;
    FILE*       fFile;
    bool        fWide;
    size_t      fExpected;
    size_t      fWritten = 0;
    std::string fError;
};

#endif
