// tiered-memory-test.cpp - faust/dsp/tiered-memory-manager.h with FAUST
// programs compiled with -mem (tiers.dsp, tables.dsp): the tier of every
// zone, the reserve of a tier, the arena emptying itself (no reset()), static
// tables surviving instances that come and go, the audio unchanged (against
// the same programs without -mem) on memory filled with garbage, failures,
// the zone table growing, and the arena's edge cases.
//
// run: make (generates the programs with faust)
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#define FAUSTFLOAT float
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/tiered-memory-manager.h"
#include "tiersmem.h"
#include "tiersplain.h"
#include "tablesmem.h"
#include "tablesplain.h"

static int failures = 0;
#define CHECK(cond, what) do { bool ok = (cond); printf("%s  %s\n", ok ? "ok  " : "FAIL", what); if (!ok) failures++; } while (0)

const unsigned char GARBAGE = 0xbe;

// a tier that counts what it holds (a stand-in for a platform's RAM); its
// memory starts filled with garbage, as recycled memory on a device would
struct counting_tier : public memory_tier {
    size_t fCapacity, fHeld = 0;
    int fLive = 0;
    explicit counting_tier(size_t capacity) : fCapacity(capacity) {}
    void* allocate(size_t size) override
    {
        if (fHeld + size > fCapacity) return nullptr;
        size_t* p = (size_t*)::malloc(size + sizeof(size_t));
        *p = size; fHeld += size; fLive++;
        memset(p + 1, GARBAGE, size);
        return p + 1;
    }
    void free(void* ptr) override { size_t* p = (size_t*)ptr - 1; fHeld -= *p; fLive--; ::free(p); }
    size_t available() override { return fCapacity - fHeld; }
};

// forwards to a manager and records each zone's size
struct recording_manager : public dsp_memory_manager {
    dsp_memory_manager& fTo;
    std::vector<std::pair<void*, size_t>> fZones;
    explicit recording_manager(dsp_memory_manager& to) : fTo(to) {}
    void* allocate(size_t size) override
    {
        void* p = fTo.allocate(size);
        fZones.push_back({p, size});
        return p;
    }
    void destroy(void* ptr) override { fTo.destroy(ptr); }
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

bool same(dsp* a, dsp* b, int blocks)
{
    std::vector<float> x = render(a, blocks), y = render(b, blocks);
    return memcmp(x.data(), y.data(), x.size() * sizeof(float)) == 0;
}

alignas(32) static uint8_t fast[96 * 1024];

int main()
{
    memset(fast, GARBAGE, sizeof(fast));
    memory_arena arena(fast, sizeof(fast));
    counting_tier small(1 << 20), mid(512 * 1024), big(4 << 20);
    tiered_memory_manager<4> m;
    m.addTier(small, 0, 1023);
    m.addTier(arena, 1024, 32768);
    m.addTier(mid, 1024, 262144, 64 * 1024);   // keeps 64 kB free
    m.addTier(big);
    recording_manager rec(m);

    // 1. placement: every zone in the tier its size asks for
    tiersmem::fManager = &rec;
    tiersmem::classInit(SR);
    tiersmem* d = tiersmem::create();
    d->instanceInit(SR);
    printf("zones %d: arena %zu B, mid %zu B, big %zu B, small %zu B\n", m.zones(), arena.used(), mid.fHeld, big.fHeld, small.fHeld);
    CHECK(d != nullptr && m.failures() == 0, "create() through the tiers");
    // delay lines (floats): 64 -> 256 B, 4096 -> 16 kB, 16384 -> 64 kB, 65536 -> 256 kB, 262144 -> 1 MB
    bool placed = true;
    int seen[4] = {0, 0, 0, 0};
    for (auto& z : rec.fZones) {
        int want = z.second < 1024 ? 0 : z.second <= 32768 ? 1 : z.second <= 262144 ? 2 : 3;
        int got = m.tierOf(z.first);
        if (got != want) { printf("      zone of %zu B in tier %d, not %d\n", z.second, got, want); placed = false; }
        if (got >= 0) seen[got]++;
    }
    CHECK(placed && seen[1] == 1 && seen[2] == 2 && seen[3] == 1 && seen[0] >= 2, "each zone in its tier (16 kB arena, 64 + 256 kB mid, 1 MB last)");

    // 2. audio on garbage-filled memory, initialised by instanceInit()
    tiersplain ref; ref.init(SR);
    CHECK(same(d, &ref, 8000), "audio identical to the program without -mem (10.7 s, past the longest delay)");

    tiersmem::destroy(d);
    CHECK(m.zones() == 0 && small.fLive == 0 && mid.fLive == 0 && big.fLive == 0, "destroy() frees every zone in its tier");
    CHECK(arena.used() == 0 && arena.zones() == 0, "the arena is empty after destroy() (no reset())");

    // 3. the arena is reused: create/destroy again and again
    size_t first = 0;
    bool reused = true;
    for (int i = 0; i < 6; i++) {
        tiersmem* e = tiersmem::create();
        if (i == 0) first = arena.used();
        if (arena.used() != first || m.tierOf(e) < 0) reused = false;
        tiersmem::destroy(e);
        if (arena.used() != 0) reused = false;
    }
    CHECK(reused && first > 0 && m.failures() == 0, "six create()/destroy() use the same arena room");
    tiersmem::classDestroy();

    // 4. static tables survive instances that come and go (classInit() puts the
    //    8 kB table in the arena, below the instances' 16 kB delay lines)
    rec.fZones.clear();
    tablesmem::fManager = &rec;
    tablesmem::classInit(SR);
    CHECK(rec.fZones.size() >= 1 && m.tierOf(rec.fZones.back().first) == 1, "the 8 kB table is in the arena");
    tablesplain::classInit(SR);
    tablesmem* t1 = tablesmem::create(); t1->instanceInit(SR);
    tablesplain r1; r1.init(SR);
    CHECK(same(t1, &r1, 400), "table program: first instance identical");
    tablesmem::destroy(t1);
    tablesmem* t2 = tablesmem::create(); t2->instanceInit(SR);
    tablesplain r2; r2.init(SR);
    CHECK(same(t2, &r2, 400), "after destroy() + create() + instanceInit(): still identical (table kept)");
    tablesmem* t3 = tablesmem::create(); t3->instanceInit(SR);
    tablesmem::destroy(t2);
    tablesmem* t4 = tablesmem::create(); t4->instanceInit(SR);
    tablesplain r3, r4; r3.init(SR); r4.init(SR);
    CHECK(same(t3, &r3, 400) && same(t4, &r4, 400), "two instances, one destroyed and replaced: both identical");
    tablesmem::destroy(t3);
    tablesmem::destroy(t4);
    CHECK(arena.zones() == 1, "the table stays in the arena while the class lives");
    tablesmem::classDestroy();
    CHECK(arena.used() == 0 && m.zones() == 0, "classDestroy() empties the arena");

    // 5. the reserve: with less room the mid tier refuses, the next tier takes it
    counting_tier tight(300 * 1024), big2(4 << 20);
    tiered_memory_manager<4> m2;
    m2.addTier(small, 0, 1023);
    m2.addTier(arena, 1024, 32768);
    m2.addTier(tight, 1024, 262144, 64 * 1024);
    m2.addTier(big2);
    tiersmem::fManager = &m2;
    tiersmem* d2 = tiersmem::create();
    printf("tight: mid %zu B, big %zu B\n", tight.fHeld, big2.fHeld);
    CHECK(d2 && tight.fHeld == 64 * 1024 && big2.fHeld == (1 << 20) + 256 * 1024, "a tier keeps its reserve, the next one takes the zone");
    tiersmem::destroy(d2);

    // 6. failures: a zone no tier accepts
    tiered_memory_manager<2> m3;
    counting_tier only(1024 * 1024);
    m3.addTier(only, 0, 65536);
    CHECK(m3.allocate(1 << 20) == nullptr && m3.failures() == 1, "a zone no tier accepts: nullptr, counted");
    void* p = m3.allocate(1000);
    CHECK(p && m3.tierOf(p) == 0 && m3.failures() == 1, "tierOf(); a zone that fits is not a failure");
    m3.destroy(p);
    CHECK(m3.zones() == 0 && only.fLive == 0, "destroy() of a single zone");
    m3.clearFailures();
    tiersmem::fManager = &m3;
    tiersmem* d3 = tiersmem::create();
    CHECK(m3.failures() == 2, "create() without room for the 256 kB and 1 MB lines: 2 failures to check");
    tiersmem::destroy(d3);
    CHECK(m3.zones() == 0 && only.fLive == 0, "destroy() after a failed create() frees what was allocated");

    // 7. the zone table grows past its initial size
    counting_tier many(1 << 20);
    tiered_memory_manager<1, 4> m4;
    m4.addTier(many);
    std::vector<void*> ptrs;
    for (int i = 0; i < 100; i++) ptrs.push_back(m4.allocate(64));
    bool all = m4.failures() == 0 && m4.zones() == 100;
    for (void* q : ptrs) all = all && m4.tierOf(q) == 0;
    for (void* q : ptrs) m4.destroy(q);
    CHECK(all && m4.zones() == 0 && many.fLive == 0, "100 zones with a table for 4: it grows");

    // 8. the arena's edge cases
    memory_arena a(fast, 4096);
    void* z1 = a.allocate(0);
    void* z2 = a.allocate(0);
    CHECK(z1 && z2 && z1 != z2, "size 0: distinct pointers");
    size_t before = a.used();
    CHECK(a.allocate(SIZE_MAX - 8) == nullptr && a.used() == before, "a huge size: nullptr, nothing used");
    CHECK(a.allocate(4096) == nullptr && a.used() == before, "more than is left: nullptr");
    void* z3 = a.allocate(1000);
    size_t with = a.used();
    a.free(z3);
    CHECK(a.used() < with && a.used() <= 1000 && a.zones() == 2, "freeing the topmost zone gives its room back");
    a.free(z1);
    CHECK(a.used() > 0 && a.zones() == 1, "a zone below another stays used");
    a.free(z2);
    CHECK(a.used() == 0 && a.zones() == 0, "the last zone freed: empty");

    printf("%d failures\n", failures);
    return failures != 0;
}
