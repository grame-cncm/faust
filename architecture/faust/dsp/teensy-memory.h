/************************** BEGIN teensy-memory.h ***********************
 FAUST Architecture File
 Copyright (C) 2026 Arev Imer
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

// Memory for FAUST programs on a Teensy 4.0/4.1 (compiled with -mem),
// fastest first (faust/dsp/tiered-memory-manager.h):
//
//  1. zones below FAUST_TEENSY_SMALL bytes: the heap (malloc)
//  2. zones up to FAUST_TEENSY_ARENA_MAX: an arena in DTCM (RAM1, tightly
//     coupled: no wait states, not cached), FAUST_TEENSY_ARENA bytes
//  3. zones up to FAUST_TEENSY_RAM2_MAX: the heap in RAM2 (on chip,
//     cached), while FAUST_TEENSY_HEAP_RESERVE bytes stay free for the rest
//     of the firmware
//  4. the rest: the optional PSRAM of a Teensy 4.1 (extmem_malloc(), which
//     falls back to the heap without PSRAM)
//
// Measured on a Teensy 4.1 at 816 MHz, 48 kHz: a plate reverb whose tank
// and late taps (5 delay lines of 65-106 kB) moved from PSRAM to RAM2 went
// from 74 to 63 % CPU (peaks 89 -> 75 %). PSRAM reads cost most when a
// program reads many places of a buffer per sample; reading in order (a
// long loop, a granular buffer) is cheap.
//
// The arena empties itself when the program's zones are freed. Usage:
//
//   mydsp::fManager = &teensy_memory::manager();
//   mydsp::classInit(AUDIO_SAMPLE_RATE_EXACT);
//   mydsp* dsp = mydsp::create();
//   if (teensy_memory::manager().failures()) { ... }   // no memory for a zone
//   dsp->instanceInit(AUDIO_SAMPLE_RATE_EXACT);       // with -mem init() is empty
//   ...
//   mydsp::destroy(dsp);
//   mydsp::classDestroy();
//
// FAUST_TEENSY_ARENA 0 leaves the arena out (zones up to
// FAUST_TEENSY_RAM2_MAX then go to the heap).

#ifndef __teensy_memory__
#define __teensy_memory__

#include <Arduino.h>
#include <malloc.h>

#include "faust/dsp/tiered-memory-manager.h"

// zones the manager tracks before its table grows (8 bytes each): a large
// reverb can have ~200, more than tiered_memory_manager's default 128
#ifndef FAUST_TEENSY_ZONES
#define FAUST_TEENSY_ZONES 256
#endif
#ifndef FAUST_TEENSY_SMALL
#define FAUST_TEENSY_SMALL 1024
#endif
#ifndef FAUST_TEENSY_ARENA
#define FAUST_TEENSY_ARENA 65536
#endif
#ifndef FAUST_TEENSY_ARENA_MAX
#define FAUST_TEENSY_ARENA_MAX 32768
#endif
#ifndef FAUST_TEENSY_RAM2_MAX
#define FAUST_TEENSY_RAM2_MAX 131072
#endif
#ifndef FAUST_TEENSY_HEAP_RESERVE
#define FAUST_TEENSY_HEAP_RESERVE 65536
#endif

extern "C" char* __brkval;            // Teensy 4 startup code and sbrk()
extern "C" unsigned long _heap_end;

namespace teensy_memory {

    // the heap (RAM2): never used memory above the break plus free blocks
    inline size_t heapFree()
    {
        return size_t((char*)&_heap_end - __brkval) + mallinfo().fordblks;
    }

    // PSRAM (Teensy 4.1); extmem_free() also frees heap blocks
    struct extmem_tier : public memory_tier {
        void* allocate(size_t size) override { return extmem_malloc(size); }
        void free(void* ptr) override { extmem_free(ptr); }
    };

#if FAUST_TEENSY_ARENA > 0
    // the arena in DTCM: zero initialized static data is in RAM1 on a Teensy 4
    inline memory_arena& arena()
    {
        alignas(32) static uint8_t buffer[FAUST_TEENSY_ARENA];
        static memory_arena a(buffer, sizeof(buffer));
        return a;
    }
#endif

    inline tiered_memory_manager<4, FAUST_TEENSY_ZONES>& manager()
    {
        static malloc_tier heap(heapFree);
        static extmem_tier psram;
        static tiered_memory_manager<4, FAUST_TEENSY_ZONES> m;
        static bool ready = false;
        if (!ready) {
            m.addTier(heap, 0, FAUST_TEENSY_SMALL - 1);
#if FAUST_TEENSY_ARENA > 0
            m.addTier(arena(), FAUST_TEENSY_SMALL, FAUST_TEENSY_ARENA_MAX);
#endif
            m.addTier(heap, FAUST_TEENSY_SMALL, FAUST_TEENSY_RAM2_MAX, FAUST_TEENSY_HEAP_RESERVE);
            m.addTier(psram);
            ready = true;
        }
        return m;
    }

} // namespace teensy_memory

#endif
/************************** END teensy-memory.h **************************/
