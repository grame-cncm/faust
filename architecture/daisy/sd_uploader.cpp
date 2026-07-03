/************************************************************************
 FAUST Architecture File - Daisy SD card soundfile uploader
 Copyright (C) 2020-2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

/*
 * A small firmware that turns the Daisy into a USB-serial (CDC) endpoint for
 * uploading soundfiles to the SD card. It is flashed temporarily by
 * `faust2daisy -upload-sd`, which then streams the WAV files referenced by a
 * DSP into the "/soundfiles" folder. It never touches anything else on the card.
 *
 * Protocol (host -> device, line terminated by '\n'; device replies one line):
 *   PING               -> "OK"
 *   CLEAR              -> delete every file in /soundfiles (create it if needed), "OK"
 *   FILE <size> <name> -> open /soundfiles/<name> for writing, "OK"
 *                         then the host streams <size> raw bytes, in chunks of
 *                         CHUNK; the device replies "OK" after every CHUNK (and
 *                         after the final remainder) for flow control.
 *   DONE               -> "OK"
 *   on any failure the device replies "ERR <reason>".
 */

#include "daisy_seed.h"
#include "fatfs.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace daisy;

static DaisySeed      hw;
static SdmmcHandler   sdmmc;
static FatFSInterface fsi;
static FIL            file;
static FRESULT        mount_res = FR_NOT_READY; // last f_mount result (for diagnostics)

// Flow-control chunk size: the host waits for an "OK" after each CHUNK bytes.
static constexpr uint32_t CHUNK = 32768;

// USB RX ring buffer (filled in the USB IRQ callback, drained in main()).
// Must comfortably hold one in-flight chunk plus USB buffering.
static constexpr uint32_t RING_SIZE = 1 << 16; // 64 KB, power of two
static uint8_t            ring[RING_SIZE];
static volatile uint32_t  ring_head = 0; // written by IRQ
static volatile uint32_t  ring_tail = 0; // read by main

static void UsbRx(uint8_t* buf, uint32_t* len)
{
    uint32_t n = *len;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t next = (ring_head + 1) & (RING_SIZE - 1);
        if (next == ring_tail) break; // overflow (should not happen with flow control)
        ring[ring_head] = buf[i];
        ring_head       = next;
    }
}

static inline bool ring_empty()
{
    return ring_head == ring_tail;
}

static inline uint8_t ring_pop()
{
    uint8_t b = ring[ring_tail];
    ring_tail = (ring_tail + 1) & (RING_SIZE - 1);
    return b;
}

static void reply(const char* s)
{
    hw.usb_handle.TransmitInternal((uint8_t*)s, strlen(s));
}

// Block until a full '\n'-terminated line is received. '\r' is ignored.
static void read_line(char* out, size_t maxlen)
{
    size_t i = 0;
    while (true) {
        while (ring_empty()) {}
        uint8_t b = ring_pop();
        if (b == '\n') {
            out[i] = 0;
            return;
        }
        if (b == '\r') continue;
        if (i < maxlen - 1) out[i++] = b;
    }
}

// Delete every regular file in /soundfiles, creating the folder if absent.
static FRESULT clear_soundfiles()
{
    FRESULT fr = f_mkdir("soundfiles");
    if (fr != FR_OK && fr != FR_EXIST) return fr;

    DIR     dir;
    FILINFO fno;
    fr = f_opendir(&dir, "soundfiles");
    if (fr != FR_OK) return fr;

    while (true) {
        fr = f_readdir(&dir, &fno);
        if (fr != FR_OK || fno.fname[0] == 0) break; // error or end of dir
        if (fno.fattrib & AM_DIR) continue;          // keep sub-directories
        char path[300];
        snprintf(path, sizeof(path), "soundfiles/%s", fno.fname);
        f_unlink(path);
    }
    f_closedir(&dir);
    return FR_OK;
}

// Receive 'size' bytes from the host and write them to the open file, replying
// "OK" after every CHUNK (and after the final remainder). Returns true on success.
// SD write buffer. MUST be static (AXI SRAM), not on the stack: on the STM32H7
// the stack is in DTCMRAM, which the SDMMC IDMA cannot access -> writes fail.
// 32-byte aligned so the D-cache clean/invalidate in sd_diskio.c does not touch
// neighbouring data.
static uint8_t __attribute__((aligned(32))) sd_write_buf[512];

static bool receive_file(uint32_t size)
{
    uint32_t remaining = size;
    uint32_t chunk_acc = 0;
    uint8_t* tmp       = sd_write_buf;

    // Empty file: nothing to stream, but acknowledge the (single) chunk.
    if (size == 0) {
        reply("OK\n");
        return true;
    }

    while (remaining > 0) {
        uint32_t want = (remaining < sizeof(sd_write_buf)) ? remaining : sizeof(sd_write_buf);
        uint32_t k    = 0;
        while (k < want) {
            if (ring_empty()) continue; // wait for more USB data
            tmp[k++] = ring_pop();
        }
        UINT    bw = 0;
        FRESULT wr = f_write(&file, tmp, k, &bw);
        if (wr != FR_OK || bw != k) {
            char msg[48];
            snprintf(msg, sizeof(msg), "ERR write=%d bw=%u/%u\n", (int)wr,
                     (unsigned)bw, (unsigned)k);
            reply(msg);
            return false;
        }
        remaining -= k;
        chunk_acc += k;
        if (remaining == 0 || chunk_acc >= CHUNK) {
            f_sync(&file);
            reply("OK\n");
            chunk_acc = 0;
        }
    }
    return true;
}

int main(void)
{
    hw.Init();

    // Mount the SD card, trying a ladder of clock speeds and bus widths
    // (fastest first). Boards with longer SD traces, e.g. the Daisy Patch,
    // often need a slower clock and/or 1-bit mode (FR_DISK_ERR at 25 MHz).
    FatFSInterface::Config fsi_cfg;
    fsi_cfg.media = FatFSInterface::Config::MEDIA_SD;
    const SdmmcHandler::Speed speeds[] = {SdmmcHandler::Speed::STANDARD,
                                          SdmmcHandler::Speed::MEDIUM_SLOW,
                                          SdmmcHandler::Speed::SLOW};
    const SdmmcHandler::BusWidth widths[] = {SdmmcHandler::BusWidth::BITS_4,
                                             SdmmcHandler::BusWidth::BITS_1};
    bool done = false;
    for (unsigned si = 0; si < 3 && !done; si++) {
        for (unsigned wi = 0; wi < 2 && !done; wi++) {
            SdmmcHandler::Config sd_cfg;
            sd_cfg.Defaults();
            sd_cfg.speed           = speeds[si];
            sd_cfg.width           = widths[wi];
            sd_cfg.clock_powersave = false;
            sdmmc.Init(sd_cfg);
            fsi.Init(fsi_cfg);
            mount_res = f_mount(&fsi.GetSDFileSystem(), "/", 1);
            if (mount_res == FR_OK) done = true;
        }
    }
    bool mounted = (mount_res == FR_OK);

    hw.usb_handle.Init(UsbHandle::FS_INTERNAL);
    System::Delay(500);
    hw.usb_handle.SetReceiveCallback(UsbRx, UsbHandle::FS_INTERNAL);

    char line[300];
    while (1) {
        read_line(line, sizeof(line));

        if (strncmp(line, "PING", 4) == 0) {
            // The "ladder" tag confirms this is the speed/width-ladder uploader
            // (so a stale firmware can be told apart from the current one).
            if (mounted) {
                reply("OK ladder\n");
            } else {
                char msg[48];
                snprintf(msg, sizeof(msg), "ERR nomount=%d ladder\n", (int)mount_res);
                reply(msg);
            }
        } else if (strncmp(line, "CLEAR", 5) == 0) {
            if (!mounted) {
                char msg[40];
                snprintf(msg, sizeof(msg), "ERR nomount=%d\n", (int)mount_res);
                reply(msg);
            } else {
                reply(clear_soundfiles() == FR_OK ? "OK\n" : "ERR clear\n");
            }
        } else if (strncmp(line, "FILE ", 5) == 0) {
            if (!mounted) {
                reply("ERR nomount\n");
                continue;
            }
            // Parse "FILE <size> <name>".
            char*    p    = line + 5;
            uint32_t size = strtoul(p, &p, 10);
            while (*p == ' ') p++;
            if (*p == 0) {
                reply("ERR name\n");
                continue;
            }
            char path[300];
            snprintf(path, sizeof(path), "soundfiles/%s", p);
            if (f_open(&file, path, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
                reply("ERR open\n");
                continue;
            }
            reply("OK\n");
            bool ok = receive_file(size);
            f_close(&file);
            (void)ok; // receive_file already replied on error
        } else if (strncmp(line, "DONE", 4) == 0) {
            reply("OK\n");
        } else if (line[0] != 0) {
            reply("ERR cmd\n");
        }
    }
}
