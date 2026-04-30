#ifndef FAUSTBENCH_HH
#define FAUSTBENCH_HH
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tuple>

#include "dsp.hh"

/*                                         *
* Prelude                                  *
*                                         */

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifndef WARMUP_ITERS
#define WARMUP_ITERS 10'000
#endif

#ifndef RUN_ITERS
#define RUN_ITERS 100'000
#endif

#ifndef fn
#define fn auto
#endif

template<typename... Ts>
using Res = std::tuple<Ts...>;

using u8  = uint8_t;
using s32 = int32_t;
using r32 = float;
using r64 = double;
using usize = size_t;
using ssize = ptrdiff_t;

inline constexpr ssize PTR_SIZE = sizeof(void*);
inline constexpr ssize PTR_ALIGN = alignof(void*); 
inline constexpr ssize STD_ALIGN = sizeof(max_align_t);

inline constexpr s32 SAMP_RATE = 44'100;
inline constexpr s32 BUFF_SIZE = 1024;

inline constexpr fn align_up(ssize num, ssize aln) -> ssize
{
    return (num + aln - 1) & ~(aln - 1);
}

inline constexpr fn align_up(void* ptr, ssize aln) -> void*
{
    return (void*) align_up(ssize(ptr), aln);
}

/*                                         *
* Benchmark utilities                      *
*                                         */

inline namespace bench {

using AllocErr = s32;
inline constexpr s32 AllocErr_None = 0;
inline constexpr s32 AllocErr_BadAlloc = 1;
inline constexpr s32 AllocErr_IllegalArg = 2;

struct BenchReport {
    s32 samp_rate = 0;
    s32 buff_size = 0;
    s32 n_ins = 0;
    s32 n_outs = 0;
    s32 warmup_iters = 0;
    s32 run_iters = 0;
    r64 elapsed_sec = 0.0;
    r64 ns_per_compute = 0.0;
    r64 ns_per_frame = 0.0;
    r64 ns_per_output_sample = 0.0;
    r64 frames_per_sec = 0.0;
    r64 output_samples_per_sec = 0.0;
    r64 checksum = 0.0;
};

template<typename Real>
fn alloc_buffers(
    s32 const buff_size, s32 const n_ins, s32 const n_outs
) -> Res<void*, AllocErr> {
    if (n_ins < 0 || n_outs < 0) {
        return {nullptr, AllocErr_IllegalArg};
    }

    constexpr ssize REAL_SIZE = sizeof(Real);
    constexpr ssize REAL_ALIGN = alignof(Real);
    constexpr ssize ALIGN = STD_ALIGN > REAL_ALIGN ? STD_ALIGN : REAL_ALIGN;

    s32 header_size = align_up(PTR_SIZE * (n_ins + n_outs), REAL_ALIGN);
    s32 block_size = REAL_SIZE * buff_size * (n_ins + n_outs);
    s32 tot_size = header_size + block_size;
    // aligned alloc requries size to be a multiple of alignment
    s32 alloc_size = align_up(tot_size, ALIGN);

    void* base = aligned_alloc(ALIGN, alloc_size);
    if (!base) {
        return {nullptr, AllocErr_BadAlloc};
    }
    
    return {base, AllocErr_None};
}

template<typename Real>
fn init_buffers(
    void* base, s32 const buff_size, s32 const n_ins, s32 const n_outs
) -> void {
    constexpr ssize REAL_ALIGN = alignof(Real);
    constexpr ssize REAL_SIZE = sizeof(Real);

    s32 n_chans =  n_ins + n_outs;
    ssize header_size = align_up(n_chans * PTR_SIZE, REAL_ALIGN);

    u8* raw = (u8*) base;
    Real** header_beg = (Real**) raw;
    Real* data_beg = (Real*) (raw + header_size);

    for (ssize i = 0; i < n_ins + n_outs; i++) {
        header_beg[i] = data_beg + i * buff_size;
    }
    memset(data_beg, 0, REAL_SIZE * buff_size * n_chans);
}

template<typename Real>
fn make_buffers(s32 const buff_size, s32 const n_ins, s32 const n_outs) -> Res<void*, AllocErr>
{
    auto [base, err] = alloc_buffers<Real>(buff_size, n_ins, n_outs);
    if (err) {
        return {nullptr, err};
    }
    init_buffers<Real>(base, buff_size, n_ins, n_outs);
    return {base, AllocErr_None};
}

inline fn free_buffers(void* base) -> void
{
    free(base);
}

template<typename Real>
inline fn fill_inputs(s32 const buff_size, Real** inputs, s32 const n_ins) -> void
{
    for (s32 chan = 0; chan < n_ins; chan++) {
        for (s32 frame = 0; frame < buff_size; frame++) {
            inputs[chan][frame] = 0.001 * (frame + 1) + chan;
        }
    }
}

template<typename Real>
inline fn checksum_outputs(
    Real** outputs, s32 const buff_size, s32 const n_outs
) -> r64 {
    r64 sum = 0.0;
    for (s32 chan = 0; chan < n_outs; chan++) {
        for (s32 frame = 0; frame < buff_size; frame++) {
            sum += r64(outputs[chan][frame]);
        }
    }
    return sum;
}

template<typename Real>
inline fn warmup(mydsp& dsp, s32 buff_size, Real** inputs, Real** outputs) -> void
{
    for (int i = 0; i < WARMUP_ITERS; i++) {
        dsp.compute(buff_size, inputs, outputs);
    }
}

template<typename Real>
inline fn measure(
    mydsp& dsp, s32 buff_size, Real** inputs, Real** outputs
) -> BenchReport {
    using Clock = std::chrono::steady_clock;

    auto beg = Clock::now();

    for (s32 i = 0; i < RUN_ITERS; i++) {
        dsp.compute(buff_size, inputs, outputs);
    }

    auto end = Clock::now();

    s32 n_ins = dsp.get_num_inputs();
    s32 n_outs = dsp.get_num_outputs();
    r64 elapsed_sec = std::chrono::duration<r64>(end - beg).count();
    r64 total_computes = r64(RUN_ITERS);
    r64 total_frames = r64(RUN_ITERS) * r64(buff_size);
    r64 total_output_samples = total_frames * r64(n_outs);

    BenchReport report;
    report.samp_rate = SAMP_RATE;
    report.buff_size = buff_size;
    report.n_ins = n_ins;
    report.n_outs = n_outs;
    report.warmup_iters = WARMUP_ITERS;
    report.run_iters = RUN_ITERS;

    report.elapsed_sec = elapsed_sec;
    report.ns_per_compute = elapsed_sec * 1.0e9 / total_computes;
    report.ns_per_frame = elapsed_sec * 1.0e9 / total_frames;
    report.ns_per_output_sample = elapsed_sec * 1.0e9 / total_output_samples;
    report.frames_per_sec = total_frames / elapsed_sec;
    report.output_samples_per_sec = total_output_samples / elapsed_sec;

    report.checksum = checksum_outputs(outputs, buff_size, n_outs);

    return report;
}

inline fn print_report(BenchReport const& report) -> void
{
    printf("Faust compute benchmark\n");
    printf("sample rate:        %d\n", report.samp_rate);
    printf("buffer size:        %d\n", report.buff_size);
    printf("inputs:             %d\n", report.n_ins);
    printf("outputs:            %d\n", report.n_outs);
    printf("warm-up iterations: %d\n", report.warmup_iters);
    printf("run iterations:     %d\n", report.run_iters);
    printf("\n");
    printf("elapsed:            %.9f s\n", report.elapsed_sec);
    printf("ns / compute:       %.3f\n", report.ns_per_compute);
    printf("ns / frame:         %.3f\n", report.ns_per_frame);
    printf("ns / output sample: %.3f\n", report.ns_per_output_sample);
    printf("frames / sec:       %.3f\n", report.frames_per_sec);
    printf("output samples/sec: %.3f\n", report.output_samples_per_sec);
    printf("checksum:           %.17g\n", report.checksum);
}

}      // namespace bench
#endif // FAUSTBENCH_HH

/*                                         *
* Testing                                  *
*                                         */

// #define FAUST_TEST 1
#if FAUST_TEST

inline fn bench__test_allocation_and_basic_usage() -> s32
{
    mydsp dsp;
    dsp.init(SAMP_RATE);
    
    s32 n_ins = dsp.get_num_inputs();
    s32 n_outs = dsp.get_num_outputs();
    auto [base, err] = bench::make_buffers<FAUSTFLOAT>(
        BUFF_SIZE, n_ins, n_outs
    );
    if (err) {
        printf("Critical alloc error: %d\n", err);
        exit(err);
    }

    FAUSTFLOAT** inputs = (FAUSTFLOAT**)base;
    FAUSTFLOAT** outputs = inputs + n_ins;

#ifdef FILL_INPUTS
    fill_inputs(BUFF_SIZE, inputs, dsp.get_num_inputs());
#endif

    bench::warmup(dsp, BUFF_SIZE, inputs, outputs);
    BenchReport report = bench::measure(dsp, BUFF_SIZE, inputs, outputs);
    bench::print_report(report); // the output will be redirected manually

    bench::free_buffers(inputs);
    return 0;
}

#undef fn
#endif // FAUST_TEST
