/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "audio.h"

#include <cerrno>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <sstream>

// Every format here is little-endian, whatever the machine.
static uint16_t u16At(const std::string& b, size_t at)
{
    if (at + 2 > b.size()) {
        throw Failure("truncated WAV header");
    }
    return static_cast<uint16_t>(static_cast<unsigned char>(b[at]) |
                                 (static_cast<unsigned char>(b[at + 1]) << 8));
}

// Two 16-bit reads: the bounds are checked in one place.
static uint32_t u32At(const std::string& b, size_t at)
{
    if (at + 4 > b.size()) {
        throw Failure("truncated WAV header");
    }
    return u16At(b, at) | (static_cast<uint32_t>(u16At(b, at + 2)) << 16);
}

// Assembled byte by byte, then given the bits of a float: the file is little-endian
// and p may be misaligned.
static float f32At(const char* p)
{
    uint32_t bits = 0;
    for (int i = 3; i >= 0; i--) {
        bits = (bits << 8) | static_cast<unsigned char>(p[i]);
    }
    float value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

// The same for a double.
static double f64At(const char* p)
{
    uint64_t bits = 0;
    for (int i = 7; i >= 0; i--) {
        bits = (bits << 8) | static_cast<unsigned char>(p[i]);
    }
    double value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

// One sample of a WAV file, as a double in [-1, 1] for the integer formats.
static double decodeWav(int format, int bits, const char* p)
{
    const unsigned char* b = reinterpret_cast<const unsigned char*>(p);
    // format 3 is IEEE float, stored as it is; format 1 is PCM
    if (format == 3) {
        return bits == 32 ? static_cast<double>(f32At(p)) : f64At(p);
    }
    switch (bits) {
        // 8-bit WAV is unsigned, around 128
        case 8:
            return (double(b[0]) - 128.0) / 128.0;
        case 16:
            return double(int16_t(b[0] | (b[1] << 8))) / 32768.0;
        // in the top of an int32, so that the arithmetic shift extends the sign
        case 24:
            return double(int32_t(uint32_t(b[0]) << 8 | uint32_t(b[1]) << 16 | uint32_t(b[2]) << 24) >> 8) /
                   8388608.0;
        default:
            return double(int32_t(uint32_t(b[0]) | uint32_t(b[1]) << 8 | uint32_t(b[2]) << 16 |
                                  uint32_t(b[3]) << 24)) /
                   2147483648.0;
    }
}

// A RIFF/WAVE file: the 'fmt ' chunk (PCM, IEEE float, or the extensible header
// wrapping either), then the 'data' chunk.
static AudioFile readWav(const std::string& bytes)
{
    if (bytes.size() < 12 || bytes.compare(0, 4, "RIFF") != 0 || bytes.compare(8, 4, "WAVE") != 0) {
        throw Failure("not a RIFF/WAVE file");
    }
    // the fields of the fmt chunk
    int      format = 0, channels = 0, bits = 0;
    uint32_t rate = 0;
    const char* data = nullptr;
    size_t   dataSize = 0;
    size_t   at = 12;
    // Chunks are an id, a size, and a body padded to an even length; a truncated last
    // chunk keeps what the file holds.
    while (at + 8 <= bytes.size()) {
        std::string id   = bytes.substr(at, 4);
        size_t      size = u32At(bytes, at + 4);
        size_t      body = at + 8;
        size_t      kept = std::min(size, bytes.size() - std::min(body, bytes.size()));
        if (id == "fmt ") {
            std::string fmt = bytes.substr(body, kept);
            format          = u16At(fmt, 0);
            channels        = u16At(fmt, 2);
            rate            = u32At(fmt, 4);
            bits            = u16At(fmt, 14);
            if (format == 0xFFFE && fmt.size() >= 26) {
                // WAVE_FORMAT_EXTENSIBLE: the real format is the sub-format's first field
                format = u16At(fmt, 24);
            }
        } else if (id == "data") {
            data     = bytes.data() + body;
            dataSize = kept;
            break;
        }
        at += 8 + size + (size & 1);
    }
    if (data == nullptr) {
        throw Failure("no data chunk");
    }
    if (channels == 0) {
        throw Failure("no fmt chunk, or zero channels");
    }
    size_t bytesPerSample = bits / 8;
    size_t frame          = channels * bytesPerSample;
    if (frame == 0) {
        throw Failure("unsupported bit depth " + std::to_string(bits));
    }
    bool supported = (format == 1 && (bits == 8 || bits == 16 || bits == 24 || bits == 32)) ||
                     (format == 3 && (bits == 32 || bits == 64));
    if (!supported) {
        throw Failure("unsupported WAV format " + std::to_string(format) + " at " + std::to_string(bits) +
                      " bits");
    }
    // interleaved in the file, one vector per channel here
    size_t    frames = dataSize / frame;
    AudioFile file;
    file.channels.assign(channels, std::vector<double>(frames));
    for (size_t f = 0; f < frames; f++) {
        for (int ch = 0; ch < channels; ch++) {
            file.channels[ch][f] = decodeWav(format, bits, data + f * frame + ch * bytesPerSample);
        }
    }
    if (rate != 0) {
        file.sampleRate = static_cast<int>(rate);
    }
    return file;
}

// A NumPy .npy file, format 1.0 to 3.0: the float arrays --out and numpy.save
// write, little-endian, C order, one or two dimensions; anything else is
// refused by name rather than misread.
static Channels readNpy(const std::string& bytes)
{
    if (bytes.size() < 10 || bytes.compare(0, 6, "\x93NUMPY") != 0) {
        throw Failure("not a NumPy .npy file");
    }
    size_t headerLength, headerAt;
    int    version = static_cast<unsigned char>(bytes[6]);
    // version 1 has a 16-bit header length, versions 2 and 3 a 32-bit one
    if (version == 1) {
        headerLength = u16At(bytes, 8), headerAt = 10;
    } else if (version == 2 || version == 3) {
        if (bytes.size() < 12) {
            throw Failure("truncated .npy header");
        }
        headerLength = u32At(bytes, 8), headerAt = 12;
    } else {
        throw Failure("unsupported .npy format version " + std::to_string(version));
    }
    if (headerAt + headerLength > bytes.size()) {
        throw Failure("truncated .npy header");
    }
    std::string header = bytes.substr(headerAt, headerLength);
    const char* data   = bytes.data() + headerAt + headerLength;
    size_t      size   = bytes.size() - headerAt - headerLength;

    // What follows a key of the dict literal of the header.
    auto field = [&header](const std::string& key) {
        size_t at = header.find(key);
        if (at == std::string::npos) {
            throw Failure("no " + key + " in the .npy header");
        }
        size_t from = header.find_first_not_of(": ", at + key.size());
        return from == std::string::npos ? std::string() : header.substr(from);
    };
    std::string descr = field("'descr'");
    size_t      width;
    if (startsWith(descr, "'<f8'")) {
        width = 8;
    } else if (startsWith(descr, "'<f4'")) {
        width = 4;
    } else {
        throw Failure("unsupported .npy element type " + descr.substr(0, descr.find(',')) +
                      " (expected '<f8' or '<f4')");
    }
    if (startsWith(field("'fortran_order'"), "True")) {
        throw Failure("a Fortran-order .npy array is not supported (save it in C order)");
    }
    std::string shape = field("'shape'");
    if (shape.empty() || shape[0] != '(' || shape.find(')') == std::string::npos) {
        throw Failure("malformed shape in the .npy header");
    }
    std::string         inside = shape.substr(1, shape.find(')') - 1);
    std::vector<size_t> dims;
    for (const std::string& part : split(inside, ',')) {
        std::string dim = trim(part);
        if (dim.empty()) {
            continue;
        }
        size_t value;
        if (!parseSize(dim, value)) {
            throw Failure("malformed shape `(" + inside + ")`");
        }
        dims.push_back(value);
    }
    if (dims.size() != 1 && dims.size() != 2) {
        throw Failure("a .npy array of shape (" + inside + ") is not frames x channels");
    }
    size_t frames   = dims[0];
    size_t channels = dims.size() == 2 ? dims[1] : 1;
    if (size != frames * channels * width) {
        throw Failure("the .npy data holds " + str(size) + " bytes, its shape (" + inside + ") announces " +
                      str(frames * channels * width));
    }
    // row-major: frame by frame
    Channels out(channels, std::vector<double>(frames));
    for (size_t f = 0; f < frames; f++) {
        for (size_t ch = 0; ch < channels; ch++) {
            const char* p = data + (f * channels + ch) * width;
            out[ch][f]    = width == 8 ? f64At(p) : static_cast<double>(f32At(p));
        }
    }
    return out;
}

// The format is told by the extension, checked before the file is read.
AudioFile readChannels(const std::string& path)
{
    std::string extension = extensionOf(path);
    if (extension != "wav" && extension != "wave" && extension != "f64" && extension != "f32" &&
        extension != "npy") {
        throw Failure(path + ": unknown audio extension `" + extension +
                      "` (expected .wav, .npy, .f64 or .f32)");
    }
    std::ifstream stream(path, std::ios::binary);
    if (!stream) {
        throw Failure("cannot read " + path + ": " + strerror(errno));
    }
    std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string bytes = buffer.str();
    try {
        if (extension == "wav" || extension == "wave") {
            return readWav(bytes);
        }
        AudioFile file;
        if (extension == "npy") {
            file.channels = readNpy(bytes);
        } else {
            size_t              width = extension == "f64" ? 8 : 4;
            std::vector<double> samples(bytes.size() / width);
            for (size_t i = 0; i < samples.size(); i++) {
                const char* p = bytes.data() + i * width;
                samples[i]    = width == 8 ? f64At(p) : static_cast<double>(f32At(p));
            }
            file.channels.push_back(samples);
        }
        return file;
    } catch (const Failure& failure) {
        throw Failure(path + ": " + failure.what());
    }
}

// Header fields, little-endian.
static void putU16(std::string& out, uint32_t value)
{
    out += static_cast<char>(value & 0xFF);
    out += static_cast<char>((value >> 8) & 0xFF);
}

// Low half first.
static void putU32(std::string& out, uint32_t value)
{
    putU16(out, value & 0xFFFF);
    putU16(out, value >> 16);
}

// NumPy format 1.0: magic, version, header length, then a Python dict literal
// padded so that the data starts on a multiple of 64 bytes.
static std::string npyHeader(size_t frames, size_t channels, bool wide)
{
    std::string dict = std::string("{'descr': '") + (wide ? "<f8" : "<f4") +
                       "', 'fortran_order': False, 'shape': (" + str(frames) + ", " + str(channels) + "), }";
    size_t unpadded = 10 + dict.size() + 1;
    dict += std::string((64 - unpadded % 64) % 64, ' ');
    dict += '\n';
    std::string header("\x93NUMPY\x01\x00", 8);
    putU16(header, static_cast<uint32_t>(dict.size()));
    return header + dict;
}

// RIFF/WAVE, WAVE_FORMAT_IEEE_FLOAT: an 18-byte 'fmt ' chunk, the 'fact' chunk
// such a format requires, then 'data'.
static std::string wavHeader(size_t frames, size_t channels, size_t bytesPerSample, int sampleRate)
{
    size_t blockAlign = channels * bytesPerSample;
    size_t dataLength = frames * blockAlign;
    size_t riffLength = 4 + (8 + 18) + (8 + 4) + (8 + dataLength);
    if (riffLength > 0xFFFFFFFFull) {
        throw Failure("the render is larger than a WAV file can hold (4 GiB); use .npy");
    }
    if (channels > 0xFFFF) {
        throw Failure("too many channels for WAV");
    }
    if (sampleRate < 0) {
        throw Failure("negative sample rate");
    }
    std::string header("RIFF");
    putU32(header, static_cast<uint32_t>(riffLength));
    header += "WAVEfmt ";
    putU32(header, 18);
    putU16(header, 3);
    putU16(header, static_cast<uint32_t>(channels));
    putU32(header, static_cast<uint32_t>(sampleRate));
    putU32(header, static_cast<uint32_t>(sampleRate * blockAlign));
    putU16(header, static_cast<uint32_t>(blockAlign));
    putU16(header, static_cast<uint32_t>(bytesPerSample * 8));
    putU16(header, 0);
    header += "fact";
    putU32(header, 4);
    putU32(header, static_cast<uint32_t>(frames));
    header += "data";
    putU32(header, static_cast<uint32_t>(dataLength));
    return header;
}

// Everything is refused before the file is created, so that a refused command
// leaves no file behind. .f64 stores doubles and .f32 floats, whatever the program.
SampleWriter::SampleWriter(const std::string& path, size_t channels, size_t frames, bool isDouble,
                           int sampleRate)
    : fPath(path), fFile(nullptr), fWide(isDouble), fExpected(frames)
{
    enum Container { Npy, Wav, Raw } container;
    std::string extension = extensionOf(path);
    if (extension == "npy") {
        container = Npy;
    } else if (extension == "wav" || extension == "wave") {
        container = Wav;
    } else if (extension == "f64") {
        container = Raw, fWide = true;
    } else if (extension == "f32" && isDouble) {
        throw Failure(path +
                      ": a .f32 file would drop digits of a double-precision render; use .f64, .npy or .wav");
    } else if (extension == "f32") {
        container = Raw, fWide = false;
    } else {
        throw Failure(path + ": unknown output extension `" + extension +
                      "` (expected .npy, .wav, .f64 or .f32)");
    }
    if (container == Raw && channels != 1) {
        throw Failure(path + ": a raw file holds one channel and the program has " + str(channels) +
                      " outputs; use .npy or .wav");
    }
    std::string header;
    if (container == Npy) {
        header = npyHeader(frames, channels, fWide);
    } else if (container == Wav) {
        try {
            header = wavHeader(frames, channels, fWide ? 8 : 4, sampleRate);
        } catch (const Failure& failure) {
            throw Failure(path + ": " + failure.what());
        }
    }
    fFile = fopen(path.c_str(), "wb");
    if (fFile == nullptr) {
        throw Failure("cannot create " + path + ": " + strerror(errno));
    }
    if (fwrite(header.data(), 1, header.size(), fFile) != header.size()) {
        throw Failure("cannot write " + path + ": " + strerror(errno));
    }
}

// Closes the file: finish() is what reports errors.
SampleWriter::~SampleWriter()
{
    if (fFile != nullptr) {
        fclose(fFile);
    }
}

// Each sample as its bytes, little-endian whatever the machine.
void SampleWriter::push(const std::vector<double>& samples)
{
    if (!fError.empty()) {
        return;
    }
    for (double value : samples) {
        unsigned char bytes[8];
        size_t        width;
        if (fWide) {
            uint64_t bits;
            memcpy(&bits, &value, sizeof(bits));
            for (int i = 0; i < 8; i++) {
                bytes[i] = static_cast<unsigned char>(bits >> (8 * i));
            }
            width = 8;
        } else {
            // exact: a single-precision program's samples are floats
            float    narrow = static_cast<float>(value);
            uint32_t bits;
            memcpy(&bits, &narrow, sizeof(bits));
            for (int i = 0; i < 4; i++) {
                bytes[i] = static_cast<unsigned char>(bits >> (8 * i));
            }
            width = 4;
        }
        if (fwrite(bytes, 1, width, fFile) != width) {
            fError = "cannot write " + fPath + ": " + strerror(errno);
            return;
        }
    }
    fWritten++;
}

// See audio.h.
void SampleWriter::finish()
{
    if (!fError.empty()) {
        throw Failure(fError);
    }
    if (fflush(fFile) != 0) {
        throw Failure("cannot write " + fPath + ": " + strerror(errno));
    }
    if (fWritten != fExpected) {
        throw Failure(fPath + ": " + str(fWritten) + " frames written, " + str(fExpected) + " announced");
    }
}
