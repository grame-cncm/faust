/************************** BEGIN tiered-memory-manager.h ***************
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

// A dsp_memory_manager for microcontrollers with several kinds of memory
// (a program compiled with -mem, see faust/dsp/dsp.h):
//
// Small chips have fast memory that is small (tightly coupled RAM: DTCM on
// a Teensy 4 or a Daisy) and large memory that is slow (external PSRAM or
// SDRAM, read through a cache). Where a FAUST program's delay lines and
// tables land decides much of its CPU load: a delay line read on every
// sample from external RAM can cost more than the rest of the program. This
// manager puts every memory zone into the first tier that accepts it:
//
//   tiered_memory_manager<4> manager;
//   manager.addTier(heap, 0, 1023);                  // small zones: heap
//   manager.addTier(arena, 1024, 32768);             // fast RAM, up to 32 kB each
//   manager.addTier(heap, 1024, 131072, 65536);      // heap, keeping 64 kB free
//   manager.addTier(external);                       // the rest: external RAM
//   mydsp::fManager = &manager;
//   mydsp::classInit(sample_rate);                   // static tables
//   mydsp* dsp = mydsp::create();                    // allocates through the tiers
//   if (manager.failures()) { ... }                  // a zone found no memory
//   dsp->instanceInit(sample_rate);                  // with -mem init() is empty
//   ...
//   mydsp::destroy(dsp);                             // frees through the tiers
//   mydsp::classDestroy();                           // the tables, when no instance is left
//
// A tier is a memory_tier: allocate(), free() and, for a reserve, the bytes
// still free. memory_arena (a bump allocator on a static buffer) and
// malloc_tier (malloc/free with an optional function that tells the free
// heap) are below; a platform adds its own, e.g. one for extmem_malloc() on
// a Teensy 4.1 (faust/dsp/teensy-memory.h). destroy() gives a zone back to
// the tier that allocated it (each zone is recorded).
//
// The tiers are tried in order. A zone that no tier takes gets nullptr and
// counts as a failure: the generated create() and classInit() do not test
// the pointers they get, so the architecture checks failures() after them
// and must not use the program if it is not 0 (destroy() it: freeing the
// zones that were allocated is safe).

#ifndef __tiered_memory_manager__
#define __tiered_memory_manager__

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "faust/dsp/dsp.h"

// A kind of memory
struct memory_tier {
    virtual ~memory_tier() = default;
    virtual void* allocate(size_t size) = 0;
    virtual void free(void* ptr) = 0;
    // bytes still available (for a reserve), SIZE_MAX if not known
    virtual size_t available() { return SIZE_MAX; }
};

// A bump allocator on a buffer (e.g. a static array in fast RAM): zones are
// aligned to 'align' bytes (a cache line). It counts the zones it holds and
// starts again from the bottom when the last one is freed; freeing the
// topmost zone also gives its room back. A zone freed below others stays
// used until they are freed too (FAUST programs allocate and free their
// zones all at once, so the arena empties when the program is destroyed).
class memory_arena : public memory_tier {
    private:
        uint8_t* fBase;
        size_t fSize;
        size_t fUsed = 0;
        size_t fAlign;
        size_t fTop = SIZE_MAX;   // offset of the topmost zone, SIZE_MAX if unknown
        int fLive = 0;

    public:
        memory_arena(void* base, size_t size, size_t align = 32)
            : fBase(static_cast<uint8_t*>(base)), fSize(size), fAlign(align ? align : 1) {}

        void* allocate(size_t size) override
        {
            if (size == 0) size = 1;   // distinct pointers
            size_t start = (reinterpret_cast<uintptr_t>(fBase) + fUsed + fAlign - 1) / fAlign * fAlign
                - reinterpret_cast<uintptr_t>(fBase);
            if (start > fSize || size > fSize - start) return nullptr;
            fTop = start;
            fUsed = start + size;
            fLive++;
            return fBase + start;
        }
        void free(void* ptr) override
        {
            if (!ptr || !owns(ptr) || fLive == 0) return;
            if (--fLive == 0) {
                fUsed = 0;
                fTop = SIZE_MAX;
            } else if (size_t(static_cast<uint8_t*>(ptr) - fBase) == fTop) {
                fUsed = fTop;
                fTop = SIZE_MAX;
            }
        }
        size_t available() override { return fSize - fUsed; }

        bool owns(const void* ptr) const
        {
            return ptr >= static_cast<const void*>(fBase) && ptr < static_cast<const void*>(fBase + fSize);
        }
        size_t used() const { return fUsed; }
        size_t size() const { return fSize; }
        int zones() const { return fLive; }
};

// malloc() and free(); 'available' (optional) tells the free heap, so a
// tier with a reserve leaves room for the rest of the firmware
class malloc_tier : public memory_tier {
    private:
        size_t (*fAvailable)();

    public:
        explicit malloc_tier(size_t (*available)() = nullptr) : fAvailable(available) {}

        void* allocate(size_t size) override { return ::malloc(size); }
        void free(void* ptr) override { ::free(ptr); }
        size_t available() override { return fAvailable ? fAvailable() : SIZE_MAX; }
};

// MAX_TIERS tiers; the table of allocated zones starts with room for ZONES
// and grows (with malloc) when more are allocated at a time
template <int MAX_TIERS = 4, int ZONES = 128>
class tiered_memory_manager : public dsp_memory_manager {
    private:
        struct Tier {
            memory_tier* fTier;
            size_t fMin;
            size_t fMax;
            size_t fReserve;
            size_t fUsed;
        };
        struct Zone {
            void* fPtr;
            int fTier;
        };

        Tier fTiers[MAX_TIERS];
        int fTierCount = 0;
        Zone fFixed[ZONES];
        Zone* fZones = fFixed;
        int fCapacity = ZONES;
        int fZoneCount = 0;
        int fFailures = 0;

        bool grow()
        {
            int capacity = fCapacity * 2;
            Zone* zones = static_cast<Zone*>(::malloc(sizeof(Zone) * size_t(capacity)));
            if (!zones) return false;
            for (int z = 0; z < fZoneCount; z++) zones[z] = fZones[z];
            if (fZones != fFixed) ::free(fZones);
            fZones = zones;
            fCapacity = capacity;
            return true;
        }

    public:
        tiered_memory_manager() = default;
        tiered_memory_manager(const tiered_memory_manager&) = delete;
        tiered_memory_manager& operator=(const tiered_memory_manager&) = delete;
        virtual ~tiered_memory_manager()
        {
            if (fZones != fFixed) ::free(fZones);
        }

        // zones of min..max bytes go to this tier while it keeps 'reserve'
        // bytes available; tiers are tried in the order they were added
        bool addTier(memory_tier& tier, size_t min = 0, size_t max = SIZE_MAX, size_t reserve = 0)
        {
            if (fTierCount >= MAX_TIERS) return false;
            fTiers[fTierCount++] = {&tier, min, max, reserve, 0};
            return true;
        }

        void* allocate(size_t size) override
        {
            if (fZoneCount >= fCapacity && !grow()) {
                fFailures++;
                return nullptr;
            }
            for (int i = 0; i < fTierCount; i++) {
                Tier& t = fTiers[i];
                if (size < t.fMin || size > t.fMax) continue;
                if (t.fReserve) {
                    size_t free = t.fTier->available();
                    if (free < size || free - size < t.fReserve) continue;
                }
                if (void* ptr = t.fTier->allocate(size)) {
                    fZones[fZoneCount++] = {ptr, i};
                    t.fUsed += size;
                    return ptr;
                }
            }
            fFailures++;
            return nullptr;
        }

        void destroy(void* ptr) override
        {
            if (!ptr) return;
            for (int z = 0; z < fZoneCount; z++) {
                if (fZones[z].fPtr != ptr) continue;
                fTiers[fZones[z].fTier].fTier->free(ptr);
                fZones[z] = fZones[--fZoneCount];
                return;
            }
            assert(!"tiered_memory_manager::destroy(): not allocated by this manager");
        }

        // allocations that found no memory since the start or clearFailures()
        int failures() const { return fFailures; }
        void clearFailures() { fFailures = 0; }

        // the tier of an allocated zone (its index in the order added), -1 if this manager did not allocate it
        int tierOf(const void* ptr) const
        {
            for (int z = 0; z < fZoneCount; z++)
                if (fZones[z].fPtr == ptr) return fZones[z].fTier;
            return -1;
        }
        // bytes allocated in a tier since the start (zones freed included: a
        // footprint per program when it is reset with resetStats())
        size_t used(int tier) const { return tier >= 0 && tier < fTierCount ? fTiers[tier].fUsed : 0; }
        void resetStats() { for (int i = 0; i < fTierCount; i++) fTiers[i].fUsed = 0; }
        int zones() const { return fZoneCount; }
};

#endif
/************************** END tiered-memory-manager.h **************************/
