// tiered-memory-test.cpp - faust/dsp/tiered-memory-manager.h with a FAUST
// program compiled with -mem (tiers.dsp): where its zones land, the reserve
// of a tier, destroy() and arena reset, the audio unchanged (against the
// same program without -mem), and a failed allocation when no tier fits.
//
// run: make (generates the program with faust)
#include <cmath>
#include <cstdio>
#include <vector>
#define FAUSTFLOAT float
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/tiered-memory-manager.h"
#include "tiersmem.h"
#include "tiersplain.h"

static int failures = 0;
#define CHECK(cond, what) do { bool ok = (cond); printf("%s  %s\n", ok ? "ok  " : "FAIL", what); if (!ok) failures++; } while (0)

// a tier that counts what it holds (a stand-in for a platform's RAM)
struct counting_tier : public memory_tier {
    size_t fCapacity, fHeld = 0;
    int fLive = 0;
    explicit counting_tier(size_t capacity) : fCapacity(capacity) {}
    void* allocate(size_t size) override
    {
        if (fHeld + size > fCapacity) return nullptr;
        size_t* p = (size_t*)::malloc(size + sizeof(size_t));
        *p = size; fHeld += size; fLive++;
        return p + 1;
    }
    void free(void* ptr) override { size_t* p = (size_t*)ptr - 1; fHeld -= *p; fLive--; ::free(p); }
    size_t available() override { return fCapacity - fHeld; }
};

const int SR = 48000, N = 64;

std::vector<float> render(dsp* d, int blocks)
{
    std::vector<float> in(N), out(N), y; float* i[1] = {in.data()}; float* o[1] = {out.data()};
    for (int b = 0; b < blocks; b++) {
        for (int s = 0; s < N; s++) in[s] = (b == 0 && s == 0) ? 1.0f : 0.25f * sinf(0.01f * (b * N + s));
        d->compute(N, i, o);
        y.insert(y.end(), out.begin(), out.end());
    }
    return y;
}

int main()
{
    alignas(32) static uint8_t fast[96 * 1024];
    memory_arena arena(fast, sizeof(fast));
    counting_tier small(1 << 20), mid(512 * 1024), big(4 << 20);
    tiered_memory_manager<4> m;
    m.addTier(small, 0, 1023);
    m.addTier(arena, 1024, 32768);
    m.addTier(mid, 1024, 262144, 64 * 1024);   // keeps 64 kB free
    m.addTier(big);

    tiersmem::fManager = &m;
    tiersmem::classInit(SR);
    tiersmem* d = tiersmem::create();
    d->init(SR);
    printf("zones %d: arena %zu B, mid %zu B, big %zu B, small %zu B\n", m.zones(), arena.used(), mid.fHeld, big.fHeld, small.fHeld);
    CHECK(d != nullptr, "create() through the tiers");
    // delay lines (floats): 4096 -> 16 kB, 16384 -> 64 kB, 65536 -> 256 kB, 262144 -> 1 MB
    CHECK(arena.used() >= 16384 && arena.used() < 32768 + 64, "the 16 kB delay line is in the arena");
    CHECK(mid.fHeld >= 64 * 1024 + 256 * 1024, "64 kB and 256 kB lines in the mid tier (within its reserve)");
    CHECK(big.fHeld >= 1 << 20, "the 1 MB line in the last tier");
    CHECK(small.fLive >= 1, "small zones (the DSP object's fields) in the small tier");

    tiersplain ref; ref.init(SR);
    std::vector<float> a = render(d, 8000), b = render(&ref, 8000);   // 10.7 s: past the longest delay
    double diff = 0; for (size_t i = 0; i < a.size(); i++) diff = fmax(diff, fabs(a[i] - b[i]));
    CHECK(diff == 0.0, "audio identical to the program without -mem");

    tiersmem::destroy(d);
    CHECK(m.zones() == 0 && small.fLive == 0 && mid.fLive == 0 && big.fLive == 0, "destroy() frees every zone in its tier");
    arena.reset();
    CHECK(arena.used() == 0, "arena reset");

    // the reserve: with less room the mid tier refuses, the next tier takes it
    counting_tier tight(300 * 1024), big2(4 << 20);
    tiered_memory_manager<4> m2;
    m2.addTier(small, 0, 1023);
    m2.addTier(arena, 1024, 32768);
    m2.addTier(tight, 1024, 262144, 64 * 1024);
    m2.addTier(big2);
    tiersmem::fManager = &m2;
    tiersmem* d2 = tiersmem::create();
    printf("tight: mid %zu B, big %zu B\n", tight.fHeld, big2.fHeld);
    CHECK(d2 && tight.fHeld == 64 * 1024 && big2.fHeld >= (1 << 20) + 256 * 1024, "a tier keeps its reserve, the next one takes the zone");
    tiersmem::destroy(d2);
    arena.reset();

    // no tier fits: allocate() returns nullptr
    tiered_memory_manager<2> m3;
    counting_tier only(1024 * 1024);
    m3.addTier(only, 0, 65536);
    CHECK(m3.allocate(1 << 20) == nullptr, "a zone no tier accepts: nullptr");
    void* p = m3.allocate(1000);
    CHECK(p && m3.tierOf(p) == 0, "tierOf()");
    m3.destroy(p);
    CHECK(m3.zones() == 0 && only.fLive == 0, "destroy() of a single zone");

    printf("%d failures\n", failures);
    return failures != 0;
}
