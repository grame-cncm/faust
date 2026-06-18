#ifndef SOUNDFILE 
#define SOUNDFILE 

#pragma once
#include <cstdint>
#include <cstring>
#include "daisy.h"  // for DaisySeed / SDRAM_DSP_MEM

// ─── WAV format constants ──────────────────────────────────────────────
static constexpr uint16_t kWavFmtPcm   = 0x0001;
static constexpr uint16_t kWavFmtFloat = 0x0003;
static constexpr uint16_t kWavFmtExt   = 0xFFFE;  // extensible, check subformat

// ─── Result codes ─────────────────────────────────────────────────────
enum class WavResult : uint8_t {
    ok = 0,
    err_open,
    err_not_riff,
    err_not_wave,
    err_no_fmt,
    err_no_data,
    err_unsupported_format,
    err_alloc,
};

// ─── Parsed header ────────────────────────────────────────────────────
struct wav_header {
    uint16_t format_tag;    // 0x0001 PCM, 0x0003 float, 0xFFFE extensible
    uint16_t num_channels;
    uint32_t sample_rate;
    uint16_t bits_per_sample;
    uint32_t num_frames;    // total sample frames (samples / channels)
    uint32_t data_offset;   // byte offset of raw PCM in file
    uint32_t data_size;     // byte length of data chunk
};

// ─── Main struct ──────────────────────────────────────────────────────
struct wav_player {
    wav_header  header;
    uint8_t*    data     = nullptr;  // SDRAM pointer
    uint32_t    position = 0;        // current read frame
    bool        loaded   = false;

    // Load from FatFS path into SDRAM.  Pass your SdmmcHandler + FatFsInterface.
    WavResult load(const char* path) {
        FIL     fil;
        FRESULT fr = f_open(&fil, path, FA_READ);
        if (fr != FR_OK) return WavResult::err_open;

        WavResult res = _parse_header(fil);
        if (res != WavResult::ok) { f_close(&fil); return res; }

        // Allocate in SDRAM – caller must have called DSY_SDRAM_BSS or similar
        data = reinterpret_cast<uint8_t*>(
            DSY_SDRAM_BSS + _sdram_alloc(header.data_size)
        );
        if (!data) { f_close(&fil); return WavResult::err_alloc; }

        UINT bytes_read = 0;
        f_lseek(&fil, header.data_offset);
        f_read(&fil, data, header.data_size, &bytes_read);
        f_close(&fil);

        position = 0;
        loaded   = (bytes_read == header.data_size);
        return loaded ? WavResult::ok : WavResult::err_alloc;
    }

    // Read next stereo float frame (mono sources are duplicated).
    // Returns false when EOF.
    bool read_frame(float& left, float& right) {
        if (!loaded || position >= header.num_frames) return false;

        const uint32_t bytes_per_sample = header.bits_per_sample / 8u;
        const uint32_t frame_bytes      = bytes_per_sample * header.num_channels;
        const uint8_t* p                = data + position * frame_bytes;

        float ch[2] = { 0.f, 0.f };
        const uint32_t read_ch = (header.num_channels < 2u) ? 1u : 2u;

        for (uint32_t c = 0; c < read_ch; ++c) {
            ch[c] = _decode_sample(p + c * bytes_per_sample);
        }

        left  = ch[0];
        right = (header.num_channels > 1) ? ch[1] : ch[0];
        ++position;
        return true;
    }

    void rewind()  { position = 0; }
    bool at_end()  const { return position >= header.num_frames; }

    // ── Internals ────────────────────────────────────────────────────
    WavResult _parse_header(FIL& fil) {
        uint8_t buf[44];
        UINT    br = 0;
        f_read(&fil, buf, 12, &br);

        if (memcmp(buf,     "RIFF", 4) != 0) return WavResult::err_not_riff;
        if (memcmp(buf + 8, "WAVE", 4) != 0) return WavResult::err_not_wave;

        bool got_fmt  = false;
        bool got_data = false;

        while (!got_data) {
            uint8_t  chunk_id[4];
            uint32_t chunk_size = 0;
            if (f_read(&fil, chunk_id,    4, &br) != FR_OK || br != 4) break;
            if (f_read(&fil, &chunk_size, 4, &br) != FR_OK || br != 4) break;

            if (memcmp(chunk_id, "fmt ", 4) == 0) {
                uint8_t fmt[40] = {};
                UINT to_read    = chunk_size < 40u ? chunk_size : 40u;
                f_read(&fil, fmt, to_read, &br);
                if (chunk_size > 40u) f_lseek(&fil, f_tell(&fil) + (chunk_size - 40u));

                header.format_tag     = _u16le(fmt);
                header.num_channels   = _u16le(fmt + 2);
                header.sample_rate    = _u32le(fmt + 4);
                header.bits_per_sample= _u16le(fmt + 14);

                // Validate format
                const uint16_t tag = header.format_tag;
                const uint16_t bps = header.bits_per_sample;

                if (tag == kWavFmtFloat && bps != 32) return WavResult::err_unsupported_format;
                if (tag == kWavFmtPcm  && bps != 16 && bps != 24 && bps != 32)
                    return WavResult::err_unsupported_format;
                if (tag != kWavFmtPcm && tag != kWavFmtFloat && tag != kWavFmtExt)
                    return WavResult::err_unsupported_format;

                got_fmt = true;

            } else if (memcmp(chunk_id, "data", 4) == 0) {
                if (!got_fmt) return WavResult::err_no_fmt;

                header.data_offset = f_tell(&fil);
                header.data_size   = chunk_size;
                header.num_frames  = chunk_size /
                    (header.num_channels * (header.bits_per_sample / 8u));
                got_data = true;

            } else {
                // Skip unknown chunk (LIST, bext, etc.)
                f_lseek(&fil, f_tell(&fil) + chunk_size);
            }
        }
        return got_data ? WavResult::ok : WavResult::err_no_data;
    }

    float _decode_sample(const uint8_t* p) const {
        const uint16_t tag = header.format_tag;
        const uint16_t bps = header.bits_per_sample;

        if (tag == kWavFmtFloat) {
            float v; memcpy(&v, p, 4); return v;
        }
        // PCM integer → float [-1, 1)
        if (bps == 16) {
            int16_t s; memcpy(&s, p, 2);
            return static_cast<float>(s) * (1.f / 32768.f);
        }
        if (bps == 24) {
            // Little-endian sign-extend from 3 bytes
            int32_t s = static_cast<int32_t>(p[0])
                      | static_cast<int32_t>(p[1]) <<  8
                      | static_cast<int32_t>(p[2]) << 16;
            if (s & 0x00800000) s |= 0xFF000000;  // sign extend
            return static_cast<float>(s) * (1.f / 8388608.f);
        }
        if (bps == 32) {
            int32_t s; memcpy(&s, p, 4);
            return static_cast<float>(s) * (1.f / 2147483648.f);
        }
        return 0.f;
    }

    // Tiny little-endian readers
    static uint16_t _u16le(const uint8_t* p) {
        return static_cast<uint16_t>(p[0]) | (static_cast<uint16_t>(p[1]) << 8);
    }
    static uint32_t _u32le(const uint8_t* p) {
        return static_cast<uint32_t>(p[0])
             | static_cast<uint32_t>(p[1]) <<  8
             | static_cast<uint32_t>(p[2]) << 16
             | static_cast<uint32_t>(p[3]) << 24;
    }

    // Simple bump allocator offset into DSY SDRAM region.
    // In real use, replace with your own SDRAM arena / pool.
    static uint32_t _sdram_alloc(uint32_t size) {
        static uint32_t cursor = 0;
        uint32_t offset = cursor;
        cursor += (size + 3u) & ~3u;  // 4-byte align
        return offset;
    }
};

#endif 
