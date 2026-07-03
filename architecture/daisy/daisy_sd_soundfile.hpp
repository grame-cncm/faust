/************************************************************************
 FAUST Architecture File - Daisy runtime SD card soundfile loader
 Copyright (C) 2020-2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

/*
 * Runtime soundfile support reading WAV files from the SD card (folder
 * "/soundfiles") into SDRAM at startup, used with `faust2daisy -sd`. This is
 * the alternative to the compile-time QSPI inlining (daisy_soundfile.hpp) :
 * the WAVs are uploaded once with `faust2daisy -upload-sd`, then loaded here.
 *
 * Samples are decoded to float and stored non-interleaved in a fixed SDRAM
 * arena (bump-allocated, no heap). Supported WAV formats : PCM 16/24/32 bit
 * and IEEE float 32 bit.
 */

#ifndef __daisy_sd_soundfile__
#define __daisy_sd_soundfile__

#include <cstdint>
#include <cstring>
#include <cstdio>

#include "fatfs.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

// Size of the SDRAM arena holding all decoded samples + metadata. Override
// with -DFAUST_SD_SOUNDFILE_BYTES if you need more/less (SDRAM is 64 MB).
#ifndef FAUST_SD_SOUNDFILE_BYTES
#define FAUST_SD_SOUNDFILE_BYTES (32 * 1024 * 1024)
#endif

// These mirror the constants in architecture/faust/gui/Soundfile.h and only
// describe the *empty/unloaded* parts of a Soundfile. They are NOT the audio
// driver settings: the DSP sample rate and block size come from MY_SAMPLE_RATE
// and MY_BUFFER_SIZE (set by faust2daisy -sr / -bs) and are used in main().
#define MAX_SOUNDFILE_PARTS 256  // a Soundfile always has 256 part slots
#define MAX_CHAN 64              // max channels addressable by the DSP
#define BUFFER_SIZE 1024         // frame count reported for an empty/silent part
#define SAMPLE_RATE 44100        // sample rate reported for an empty/silent part
#define SD_MAX_SOUNDFILES 16  // distinct soundfile URLs cached
#define SD_MAX_PARTS 8        // files per soundfile URL

// Same field layout as architecture/faust/gui/Soundfile.h.
struct Soundfile {
    void* fBuffers;
    int* fLength;
    int* fSR;
    int* fOffset;
    int fChannels;
    int fParts;
    bool fIsDouble;
} __attribute__((packed));

// ─── SDRAM bump arena (no heap) ───────────────────────────────────────
static uint8_t DSY_SDRAM_BSS faust_sd_arena[FAUST_SD_SOUNDFILE_BYTES];
static size_t faust_sd_arena_off = 0;

// Diagnostics : total frames successfully loaded across all soundfiles, and a
// pointer to the most recently built soundfile (for the optional serial dump).
static uint32_t  sd_total_frames = 0;
static Soundfile* sd_debug_last  = nullptr;

static void* sd_alloc(size_t bytes)
{
    faust_sd_arena_off = (faust_sd_arena_off + 3u) & ~size_t(3);
    if (faust_sd_arena_off + bytes > sizeof(faust_sd_arena)) return nullptr;
    void* p = faust_sd_arena + faust_sd_arena_off;
    faust_sd_arena_off += bytes;
    return p;
}

// ─── FatFS / SD state ─────────────────────────────────────────────────
static daisy::SdmmcHandler   faust_sdmmc;
static daisy::FatFSInterface faust_fsi;
static bool                  faust_sd_mounted = false;

// ─── default (silent) soundfile ───────────────────────────────────────
static float     sd_empty_zero[BUFFER_SIZE];
static float*    sd_empty_bufs[MAX_CHAN];
static int       sd_empty_len[MAX_SOUNDFILE_PARTS];
static int       sd_empty_sr[MAX_SOUNDFILE_PARTS];
static int       sd_empty_off[MAX_SOUNDFILE_PARTS];
static Soundfile sd_empty_soundfile;
static Soundfile* defaultsound = nullptr;

// SD read buffer. MUST be static (AXI SRAM), not on the stack: on the STM32H7
// the stack is in DTCMRAM, which the SDMMC IDMA cannot access -> reads fail.
// 32-byte aligned for the D-cache invalidate in sd_diskio.c.
static uint8_t __attribute__((aligned(32))) sd_read_buf[4096];

// File object. Also MUST be static (AXI SRAM): with _FS_TINY=0 each FIL holds
// its own sector buffer, into which f_read DMAs partial-sector data; on the
// stack (DTCMRAM) that DMA fails. Used sequentially (open/close one at a time).
static FIL sd_fil;

// ─── WAV parsing ──────────────────────────────────────────────────────
struct sd_wav_info {
    uint16_t fmt;
    uint16_t channels;
    uint32_t sr;
    uint16_t bits;
    uint32_t data_off;
    uint32_t data_bytes;
    uint32_t frames;
};

static inline uint32_t sd_u32(const uint8_t* p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}
static inline uint16_t sd_u16(const uint8_t* p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static bool sd_parse_header(FIL* fil, sd_wav_info* w)
{
    uint8_t hdr[12];
    UINT    br = 0;
    if (f_read(fil, hdr, 12, &br) != FR_OK || br != 12) return false;
    if (memcmp(hdr, "RIFF", 4) != 0 || memcmp(hdr + 8, "WAVE", 4) != 0) return false;

    bool got_fmt = false, got_data = false;
    while (!got_data) {
        uint8_t chunk[8];
        if (f_read(fil, chunk, 8, &br) != FR_OK || br != 8) break;
        uint32_t csize = sd_u32(chunk + 4);

        if (memcmp(chunk, "fmt ", 4) == 0) {
            uint8_t fmt[40] = {0};
            UINT    toread  = (csize < 40) ? csize : 40;
            f_read(fil, fmt, toread, &br);
            if (csize > toread) f_lseek(fil, f_tell(fil) + (csize - toread));
            w->fmt      = sd_u16(fmt);
            w->channels = sd_u16(fmt + 2);
            w->sr       = sd_u32(fmt + 4);
            w->bits     = sd_u16(fmt + 14);
            if (w->fmt == 0xFFFE && csize >= 26) w->fmt = sd_u16(fmt + 24); // extensible subformat
            got_fmt = true;
        } else if (memcmp(chunk, "data", 4) == 0) {
            if (!got_fmt) return false;
            w->data_off   = f_tell(fil);
            w->data_bytes = csize;
            got_data      = true;
        } else {
            f_lseek(fil, f_tell(fil) + csize + (csize & 1)); // skip (word-aligned)
        }
    }
    if (!got_data || w->channels == 0 || w->bits == 0) return false;
    // Only PCM 16/24/32 and float32 are supported.
    if (w->fmt == 0x0003) {
        if (w->bits != 32) return false;
    } else if (w->fmt == 0x0001) {
        if (w->bits != 16 && w->bits != 24 && w->bits != 32) return false;
    } else {
        return false;
    }
    w->frames = w->data_bytes / (w->channels * (w->bits / 8u));
    return true;
}

static float sd_decode(const uint8_t* p, uint16_t fmt, uint16_t bits)
{
    if (fmt == 0x0003) {
        float v;
        memcpy(&v, p, 4);
        return v;
    }
    if (bits == 16) {
        int16_t s;
        memcpy(&s, p, 2);
        return (float)s * (1.0f / 32768.0f);
    }
    if (bits == 24) {
        int32_t s = (int32_t)p[0] | ((int32_t)p[1] << 8) | ((int32_t)p[2] << 16);
        if (s & 0x00800000) s |= 0xFF000000;
        return (float)s * (1.0f / 8388608.0f);
    }
    if (bits == 32) {
        int32_t s;
        memcpy(&s, p, 4);
        return (float)s * (1.0f / 2147483648.0f);
    }
    return 0.0f;
}

// Return the file name without any directory part. The URL may hold an
// absolute host path (e.g. "/home/me/sounds/son.wav"), but the uploader stores
// files in /soundfiles by their base name only.
static const char* sd_basename(const char* p)
{
    const char* base = p;
    for (const char* c = p; *c; c++) {
        if (*c == '/' || *c == '\\') base = c + 1;
    }
    return base;
}

// Extract file names from a Faust soundfile URL like "{'a.wav';'b.wav'}".
static int sd_parse_url(const char* url, char names[][128], int maxn)
{
    int         count = 0;
    const char* p     = url;
    while (*p && count < maxn) {
        if (*p == '\'') {
            p++;
            int k = 0;
            while (*p && *p != '\'' && k < 127) names[count][k++] = *p++;
            names[count][k] = 0;
            if (*p == '\'') p++;
            count++;
        } else {
            p++;
        }
    }
    if (count == 0) {
        // No quotes : split on ';' (the soundfile list separator), trimming
        // any surrounding braces/spaces.
        const char* s = url;
        while (*s && count < maxn) {
            while (*s == '{' || *s == '}' || *s == ' ') s++;
            int k = 0;
            while (*s && *s != ';' && *s != '}' && k < 127) names[count][k++] = *s++;
            while (k > 0 && names[count][k - 1] == ' ') k--; // trim trailing spaces
            names[count][k] = 0;
            if (k > 0) count++;
            while (*s && *s != ';') s++;
            if (*s == ';') s++;
        }
    }
    return count;
}

// Load all parts of a soundfile from /soundfiles into the SDRAM arena.
static Soundfile* sd_build(char names[][128], int nfiles)
{
    sd_wav_info infos[SD_MAX_PARTS];
    int         cur_chan   = 1;
    uint32_t    total_real = 0;
    int         nparts     = 0;

    for (int i = 0; i < nfiles && i < SD_MAX_PARTS; i++) {
        FIL& fil = sd_fil; // shared static FIL (AXI SRAM)
        char path[160];
        snprintf(path, sizeof(path), "soundfiles/%s", sd_basename(names[i]));
        if (f_open(&fil, path, FA_READ) != FR_OK) return nullptr;
        bool ok = sd_parse_header(&fil, &infos[i]);
        f_close(&fil);
        if (!ok) return nullptr;
        if ((int)infos[i].channels > cur_chan) cur_chan = infos[i].channels;
        total_real += infos[i].frames;
        nparts++;
    }
    if (nparts == 0) return nullptr;
    if (cur_chan > MAX_CHAN) cur_chan = MAX_CHAN;

    // Concatenated per-channel buffers + one trailing silent block (for the
    // empty parts). Zeroed so gaps / mono-in-stereo read as silence.
    uint32_t total = total_real + BUFFER_SIZE;
    float**  bufs  = (float**)sd_alloc(sizeof(float*) * MAX_CHAN);
    if (!bufs) return nullptr;
    for (int c = 0; c < cur_chan; c++) {
        bufs[c] = (float*)sd_alloc(sizeof(float) * total);
        if (!bufs[c]) return nullptr;
        memset(bufs[c], 0, sizeof(float) * total);
    }

    int* length = (int*)sd_alloc(sizeof(int) * MAX_SOUNDFILE_PARTS);
    int* sr     = (int*)sd_alloc(sizeof(int) * MAX_SOUNDFILE_PARTS);
    int* offset = (int*)sd_alloc(sizeof(int) * MAX_SOUNDFILE_PARTS);
    if (!length || !sr || !offset) return nullptr;

    uint32_t off = 0;
    for (int i = 0; i < nparts; i++) {
        FIL& fil = sd_fil; // shared static FIL (AXI SRAM)
        char path[160];
        snprintf(path, sizeof(path), "soundfiles/%s", sd_basename(names[i]));
        if (f_open(&fil, path, FA_READ) != FR_OK) return nullptr;
        uint16_t fc          = infos[i].channels;
        uint16_t bits        = infos[i].bits;
        uint32_t bps         = bits / 8u;
        uint32_t frame_bytes = bps * fc;

        // Read SECTOR-ALIGNED full windows. The WAV data rarely starts on a
        // sector boundary (header chunks before 'data'), and handing FatFS an
        // unaligned file position makes it DMA into the read buffer at an
        // unaligned offset -> libDaisy's 32-byte-rounded cache maintenance then
        // corrupts samples. By seeking to the sector boundary and reading whole
        // windows, the DMA target is always the 32-byte-aligned buffer start.
        // 'skip' drops the head bytes of the first window; 'carry' rebuilds a
        // frame split across two windows.
        uint32_t fpos      = infos[i].data_off & ~((uint32_t)511);
        uint32_t skip      = infos[i].data_off - fpos;
        uint32_t data_left = infos[i].frames * frame_bytes;
        f_lseek(&fil, fpos);

        uint8_t  carry[256]; // one frame max (MAX_CHAN * 4 bytes)
        uint32_t carry_n = 0;
        uint32_t fidx    = 0;
        while (data_left > 0) {
            UINT br = 0;
            f_read(&fil, sd_read_buf, sizeof(sd_read_buf), &br);
            if (br == 0) break; // unexpected EOF
            const uint8_t* p     = sd_read_buf + skip;
            uint32_t       avail = (br > skip) ? (br - skip) : 0;
            if (avail > data_left) avail = data_left; // ignore bytes past the data chunk
            data_left -= avail;
            skip = 0;

            uint32_t pi = 0;
            // Finish a frame carried over from the previous window.
            if (carry_n > 0) {
                while (carry_n < frame_bytes && pi < avail) carry[carry_n++] = p[pi++];
                if (carry_n == frame_bytes) {
                    for (uint16_t c = 0; c < fc && c < cur_chan; c++)
                        bufs[c][off + fidx] = sd_decode(carry + c * bps, infos[i].fmt, bits);
                    fidx++;
                    carry_n = 0;
                }
            }
            // Whole frames in this window.
            uint32_t full = (avail - pi) / frame_bytes;
            for (uint32_t f = 0; f < full; f++) {
                const uint8_t* fp = p + pi + f * frame_bytes;
                for (uint16_t c = 0; c < fc && c < cur_chan; c++)
                    bufs[c][off + fidx + f] = sd_decode(fp + c * bps, infos[i].fmt, bits);
            }
            fidx += full;
            pi += full * frame_bytes;
            // Carry the trailing partial frame to the next window.
            while (pi < avail && carry_n < frame_bytes) carry[carry_n++] = p[pi++];
        }
        f_close(&fil);

        length[i] = (int)infos[i].frames;
        sr[i]     = (int)infos[i].sr;
        offset[i] = (int)off;
        off += infos[i].frames;
    }

    // Empty parts all point to the shared trailing silent block.
    for (int p = nparts; p < MAX_SOUNDFILE_PARTS; p++) {
        length[p] = BUFFER_SIZE;
        sr[p]     = SAMPLE_RATE;
        offset[p] = (int)total_real;
    }
    // Alias channels up to MAX_CHAN (mirrors Soundfile::shareBuffers).
    for (int c = cur_chan; c < MAX_CHAN; c++) bufs[c] = bufs[c % cur_chan];

    Soundfile* sf = (Soundfile*)sd_alloc(sizeof(Soundfile));
    if (!sf) return nullptr;
    sf->fBuffers  = (void*)bufs;
    sf->fLength   = length;
    sf->fSR       = sr;
    sf->fOffset   = offset;
    sf->fChannels = cur_chan;
    sf->fParts    = nparts;
    sf->fIsDouble = false;
    sd_total_frames += total_real;
    sd_debug_last = sf;
    return sf;
}

// ─── URL -> Soundfile cache ───────────────────────────────────────────
struct sd_cache_entry {
    char       url[160];
    Soundfile* sf;
};
static sd_cache_entry sd_cache[SD_MAX_SOUNDFILES];
static int            sd_cache_n = 0;

// Called by DaisyControlUI::addSoundfile (once per soundfile widget).
Soundfile* sd_load_soundfile(const char* url)
{
    if (!faust_sd_mounted) return defaultsound;
    for (int i = 0; i < sd_cache_n; i++) {
        if (strcmp(sd_cache[i].url, url) == 0) return sd_cache[i].sf;
    }
    char names[SD_MAX_PARTS][128];
    int  n  = sd_parse_url(url, names, SD_MAX_PARTS);
    Soundfile* sf = sd_build(names, n);
    if (!sf) sf = defaultsound;
    if (sd_cache_n < SD_MAX_SOUNDFILES) {
        strncpy(sd_cache[sd_cache_n].url, url, 159);
        sd_cache[sd_cache_n].url[159] = 0;
        sd_cache[sd_cache_n].sf       = sf;
        sd_cache_n++;
    }
    return sf;
}

// Mount the SD card and prepare the default soundfile. Call once from main()
// before DSP.init()/buildUserInterface().
void sd_soundfile_init()
{
    memset(sd_empty_zero, 0, sizeof(sd_empty_zero));
    for (int c = 0; c < MAX_CHAN; c++) sd_empty_bufs[c] = sd_empty_zero;
    for (int p = 0; p < MAX_SOUNDFILE_PARTS; p++) {
        sd_empty_len[p] = BUFFER_SIZE;
        sd_empty_sr[p]  = SAMPLE_RATE;
        sd_empty_off[p] = 0;
    }
    sd_empty_soundfile.fBuffers  = (void*)sd_empty_bufs;
    sd_empty_soundfile.fLength   = sd_empty_len;
    sd_empty_soundfile.fSR       = sd_empty_sr;
    sd_empty_soundfile.fOffset   = sd_empty_off;
    sd_empty_soundfile.fChannels = 1;
    sd_empty_soundfile.fParts    = 0;
    sd_empty_soundfile.fIsDouble = false;
    defaultsound                 = &sd_empty_soundfile;

    faust_sd_arena_off = 0;

    // Mount the SD card, trying a ladder of clock speeds and bus widths
    // (fastest first). Boards with longer SD traces, e.g. the Daisy Patch, often
    // need a slower clock and/or 1-bit mode (FR_DISK_ERR at 25 MHz). The card
    // must be formatted FAT32 (libDaisy's FatFS has exFAT disabled).
    daisy::FatFSInterface::Config fcfg;
    fcfg.media = daisy::FatFSInterface::Config::MEDIA_SD;
    const daisy::SdmmcHandler::Speed speeds[] = {
        daisy::SdmmcHandler::Speed::STANDARD,
        daisy::SdmmcHandler::Speed::MEDIUM_SLOW,
        daisy::SdmmcHandler::Speed::SLOW};
    const daisy::SdmmcHandler::BusWidth widths[] = {
        daisy::SdmmcHandler::BusWidth::BITS_4,
        daisy::SdmmcHandler::BusWidth::BITS_1};
    FRESULT res = FR_NOT_READY;
    bool done = false;
    for (unsigned si = 0; si < 3 && !done; si++) {
        for (unsigned wi = 0; wi < 2 && !done; wi++) {
            daisy::SdmmcHandler::Config cfg;
            cfg.Defaults();
            cfg.speed           = speeds[si];
            cfg.width           = widths[wi];
            cfg.clock_powersave = false;
            faust_sdmmc.Init(cfg);
            faust_fsi.Init(fcfg);
            res = f_mount(&faust_fsi.GetSDFileSystem(), "/", 1);
            if (res == FR_OK) done = true;
        }
    }
    faust_sd_mounted = (res == FR_OK);
}

#endif // __daisy_sd_soundfile__
