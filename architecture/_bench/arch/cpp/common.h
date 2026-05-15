// architecture/_bench/arch/cpp/common.h

#ifndef BENCH_COMMON_H
#define BENCH_COMMON_H

// Common benchmark headers inclusion.

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

// Common benchmark macro definitions.

#ifndef fn
#define fn inline auto
#endif

#ifndef no_inline
#if defined(_MSC_VER)
    #define no_inline __declspec(noinline)
#elif defined(__clang__) || defined(__GNUC__)
    #define no_inline __attribute__((noinline))
#else
    #define no_inline
#endif
#endif

// Common benchmark compiler options.

#ifndef SAMP_RATE
#define SAMP_RATE 96'000
#endif
#ifndef BUFF_SIZE
#define BUFF_SIZE 128
#endif
#ifndef COMPUTE_ITERS
#define COMPUTE_ITERS 1'000'000
#endif
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

// Common benchmark type aliases.

using u8  = uint8_t;
using s32 = int32_t;
using f32 = float;
using f64 = double;
using usize = size_t;
using ssize = ptrdiff_t;
using string = std::string;
using vstring = std::string_view;

template<typename... Ts> using Res = std::tuple<Ts...>;

using Real = FAUSTFLOAT;

// Common benchmark memory helpers.

inline namespace bench {

inline constexpr ssize PTR_SIZE = sizeof(void*);
inline constexpr ssize PTR_ALIGN = alignof(void*); 
inline constexpr ssize STD_ALIGN = alignof(max_align_t);

using AllocError = s32;
inline constexpr s32 AllocError_None       = 0;
inline constexpr s32 AllocError_Exhausted  = 1;
inline constexpr s32 AllocError_IllegalArg = 2;

constexpr fn align_up(ssize num, ssize aln) -> ssize
{
    return (num + aln - 1) & ~(aln - 1);
}

constexpr fn align_up(void* ptr, ssize aln) -> void*
{
    return (void*) align_up(ssize(ptr), aln);
}

fn alloc_buffers(s32 const n_ins, s32 const n_outs) -> Res<void*, AllocError>
{
    if (n_ins < 0 || n_outs < 0) {
        return {nullptr, AllocError_IllegalArg};
    }

    constexpr ssize REAL_SIZE = sizeof(Real);
    constexpr ssize REAL_ALIGN = alignof(Real);
    constexpr ssize ALIGN = STD_ALIGN > REAL_ALIGN ? STD_ALIGN : REAL_ALIGN;

    s32 header_size = align_up(PTR_SIZE * (n_ins + n_outs), REAL_ALIGN);
    s32 block_size = REAL_SIZE * BUFF_SIZE * (n_ins + n_outs);
    s32 tot_size = header_size + block_size;
    // aligned alloc requries size to be a multiple of alignment
    s32 alloc_size = align_up(tot_size, ALIGN);

    void* base = ::aligned_alloc(ALIGN, alloc_size);
    if (!base) {
        return {nullptr, AllocError_Exhausted};
    }
    
    return {base, AllocError_None};
}

fn init_buffers(void* base, s32 const n_ins, s32 const n_outs) -> void
{
    constexpr ssize REAL_ALIGN = alignof(Real);
    constexpr ssize REAL_SIZE = sizeof(Real);

    s32 n_chans =  n_ins + n_outs;
    ssize header_size = align_up(n_chans * PTR_SIZE, REAL_ALIGN);

    u8* raw = (u8*) base;
    Real** header_beg = (Real**) raw;
    Real* data_beg = (Real*) (raw + header_size);

    for (ssize i = 0; i < n_ins + n_outs; i++) {
        header_beg[i] = data_beg + i * BUFF_SIZE;
    }
    memset(data_beg, 0, REAL_SIZE * BUFF_SIZE * n_chans);
}

fn make_buffers(s32 const n_ins, s32 const n_outs) -> Res<void*, AllocError>
{
    auto [base, err] = alloc_buffers(n_ins, n_outs);
    if (err) {
        return {nullptr, err};
    }
    init_buffers(base, n_ins, n_outs);
    return {base, AllocError_None};
}

fn free_buffers(void* base) -> void
{
    free(base);
}

// Common benchmark compiler optimizations avoidance.

fn _do_not_optimize(FAUSTFLOAT** value) noexcept -> void
{
    #if defined(__clang__) || defined(__GNUC__)
        asm volatile("" : :  "g"(value) : "memory");
    #elif defined(_MSC_VER)
        (void) value;
        _ReadWriteBarrier();
    #else
        (void) value;
    #endif
}

fn _clobber_memory() noexcept -> void
{
    #if defined (__clang__) || defined(__GNUC__)
        asm volatile("" : : : "memory");
    #elif defined(_MSC_VER)
        _ReadWriteBarrier();
    #endif
}

}       // namespace bench
#endif  // BENCH_COMMON_H 
