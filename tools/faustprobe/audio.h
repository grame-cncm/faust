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

// channels[ch][frame]: samples are carried in doubles, whatever the width of the program.
typedef std::vector<std::vector<double>> Channels;

// What a file holds.
struct AudioFile {
    Channels      channels;
    Optional<int> sampleRate;  // when the format records one
};

// The channels of a .wav, .npy, .f64 or .f32 file, or a Failure naming the file.
AudioFile readChannels(const std::string& path);

// A file receiving the frames of one render, in order, at the width the
// program was compiled in.
class SampleWriter {
   public:
    // Creates the file for that many frames: the headers carry the count, so it is
    // known before the first sample. Refuses what would lose information.
    SampleWriter(const std::string& path, size_t channels, size_t frames, bool isDouble, int sampleRate);
    ~SampleWriter();
    SampleWriter(const SampleWriter&) = delete;
    SampleWriter& operator=(const SampleWriter&) = delete;

    // Appends one frame. A write error is kept for finish(), so that the callback of
    // the render loop has nothing to report.
    void push(const std::vector<double>& samples);
    // Flushes, and checks that the announced frames were written: the headers
    // carry the count, and a short file with a long header reads as garbage.
    void finish();

   private:
    std::string fPath;  // for the messages
    FILE*       fFile;  // null until the header is ready
    bool        fWide;  // stored as doubles, else as floats
    size_t      fExpected;  // the frames the header announces
    size_t      fWritten = 0;  // the frames pushed
    std::string fError;  // the first write error
};

#endif
