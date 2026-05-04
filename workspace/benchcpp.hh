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

/*                                         *
* Compile options                          *
*                                         */

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifndef WARMUP_ITERS
#define WARMUP_ITERS 1'000
#endif

#ifndef COMPUTE_ITERS
#define COMPUTE_ITERS 1'000'000
#endif

#ifndef FILL_INPUTS
#define FILL_INPUTS 0
#endif

#ifndef SAMP_RATE
#define SAMP_RATE s32(44'100)
#endif

#ifndef BUFF_SIZE
#define BUFF_SIZE s32(1024)
#endif

/*                                         *
* Prelude                                  *
*                                         */

#ifndef fn
#define fn inline auto
#endif

using u8  = uint8_t;
using s32 = int32_t;
using r32 = float;
using r64 = double;
using usize = size_t;
using ssize = ptrdiff_t;
using Real = FAUSTFLOAT;

template<typename... Ts>
using Res = std::tuple<Ts...>;

template<typename Tp>
inline constexpr ssize align_of = alignof(Tp); 

template<typename Tp>
inline constexpr ssize size_of = sizeof(Tp);

inline constexpr ssize PTR_SIZE = size_of<void*>;
inline constexpr ssize PTR_ALIGN = align_of<void*>; 
inline constexpr ssize STD_ALIGN = size_of<max_align_t>;

inline constexpr std::string const PRECISIONS[] = {"single", "double"};

constexpr fn align_up(ssize num, ssize aln) -> ssize
{
    return (num + aln - 1) & ~(aln - 1);
}

constexpr fn align_up(void* ptr, ssize aln) -> void*
{
    return (void*) align_up(ssize(ptr), aln);
}

/*                                         *
* Benchmark utilities                      *
*                                         */

inline namespace bench {

using AllocErr = s32;
inline constexpr s32 AllocErr_None = 0;
inline constexpr s32 AllocErr_Exhausted = 1;
inline constexpr s32 AllocErr_IllegalArg = 2;

struct BenchReport {
    std::string precis          = PRECISIONS[size_of<FAUSTFLOAT>/4 - 1];
    s32 samp_rate               = SAMP_RATE;
    s32 buff_size               = BUFF_SIZE;
    s32 n_ins                   = 0;
    s32 n_outs                  = 0;
    s32 warmup_iters            = WARMUP_ITERS;
    s32 run_iters               = COMPUTE_ITERS;
    r64 elapsed_sec             = 0.0;
    r64 ns_per_compute          = 0.0;
    r64 ns_per_frame            = 0.0;
    r64 ns_per_output_sample    = 0.0;
    r64 frames_per_sec          = 0.0;
    r64 output_samples_per_sec  = 0.0;
    r64 checksum                = 0.0;
};

fn alloc_buffers(s32 const n_ins, s32 const n_outs) -> Res<void*, AllocErr>
{
    if (n_ins < 0 || n_outs < 0) {
        return {nullptr, AllocErr_IllegalArg};
    }

    constexpr ssize REAL_SIZE = size_of<Real>;
    constexpr ssize REAL_ALIGN = align_of<Real>;
    constexpr ssize ALIGN = STD_ALIGN > REAL_ALIGN ? STD_ALIGN : REAL_ALIGN;

    s32 header_size = align_up(PTR_SIZE * (n_ins + n_outs), REAL_ALIGN);
    s32 block_size = REAL_SIZE * BUFF_SIZE * (n_ins + n_outs);
    s32 tot_size = header_size + block_size;
    // aligned alloc requries size to be a multiple of alignment
    s32 alloc_size = align_up(tot_size, ALIGN);

    void* base = aligned_alloc(ALIGN, alloc_size);
    if (!base) {
        return {nullptr, AllocErr_Exhausted};
    }
    
    return {base, AllocErr_None};
}

fn init_buffers(void* base, s32 const n_ins, s32 const n_outs) -> void
{
    constexpr ssize REAL_ALIGN = align_of<Real>;
    constexpr ssize REAL_SIZE = size_of<Real>;

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

fn make_buffers(s32 const n_ins, s32 const n_outs) -> Res<void*, AllocErr>
{
    auto [base, err] = alloc_buffers(n_ins, n_outs);
    if (err) {
        return {nullptr, err};
    }
    init_buffers(base, n_ins, n_outs);
    return {base, AllocErr_None};
}

fn free_buffers(void* base) -> void
{
    free(base);
}

fn fill_inputs(Real** inputs, s32 const n_ins) -> void
{
    for (s32 chan = 0; chan < n_ins; chan++) {
        for (s32 frame = 0; frame < BUFF_SIZE; frame++) {
            inputs[chan][frame] = 0.001 * (frame + 1) + chan;
        }
    }
}

fn checksum_outputs(Real** outputs, s32 const n_outs) -> r64
{
    r64 sum = 0.0;
    for (s32 chan = 0; chan < n_outs; chan++) {
        for (s32 frame = 0; frame < BUFF_SIZE; frame++) {
            sum += r64(outputs[chan][frame]);
        }
    }
    return sum;
}

fn warmup(auto& dsp, Real** inputs, Real** outputs) -> void
{
    for (int i = 0; i < WARMUP_ITERS; i++) {
        dsp.compute(BUFF_SIZE, inputs, outputs);
    }
}

fn measure(auto& dsp, Real** inputs, Real** outputs) -> BenchReport
{
    using Clock = std::chrono::steady_clock;

    auto beg = Clock::now();

    for (s32 i = 0; i < COMPUTE_ITERS; i++) {
        dsp.compute(BUFF_SIZE, inputs, outputs);
    }

    auto end = Clock::now();

    s32 n_ins = dsp.getNumInputs();
    s32 n_outs = dsp.getNumOutputs();
    r64 elapsed_sec = std::chrono::duration<r64>(end - beg).count();
    r64 total_computes = r64(COMPUTE_ITERS);
    r64 total_frames = r64(COMPUTE_ITERS) * r64(BUFF_SIZE);
    r64 total_output_samples = total_frames * r64(n_outs);

    BenchReport report{};
    report.n_ins = n_ins;
    report.n_outs = n_outs;
    report.elapsed_sec = elapsed_sec;
    report.ns_per_compute = elapsed_sec * 1.0e9 / total_computes;
    report.ns_per_frame = elapsed_sec * 1.0e9 / total_frames;
    report.ns_per_output_sample = elapsed_sec * 1.0e9 / total_output_samples;
    report.frames_per_sec = total_frames / elapsed_sec;
    report.output_samples_per_sec = total_output_samples / elapsed_sec;

    report.checksum = checksum_outputs(outputs, n_outs);

    return report;
}

fn print_report(BenchReport const& report) -> void
{
    printf("Faust compute benchmark\n");
    printf("precision:      %s\n", report.precis.data());
    printf("sample rate:    %d\n", report.samp_rate);
    printf("buffer size:    %d\n", report.buff_size);
    printf("inputs:         %d\n", report.n_ins);
    printf("outputs:        %d\n", report.n_outs);
    printf("warm-up iters:  %d\n", report.warmup_iters);
    printf("run iters:      %d\n", report.run_iters);
    puts("------------------------------------");
    printf("elapsed:        %.9f s\n", report.elapsed_sec);
    printf("ns/compute:     %.3f\n", report.ns_per_compute);
    printf("ns/frame:       %.3f\n", report.ns_per_frame);
    printf("ns/out_sample:  %.3f\n", report.ns_per_output_sample);
    printf("frames/s:       %.3f\n", report.frames_per_sec);
    printf("out_samples/s:  %.3f\n", report.output_samples_per_sec);
    printf("checksum:       %.17g\n", report.checksum);
}

}      // namespace bench
#endif // FAUSTBENCH_HH

/*                                         *
* Testing                                  *
*                                         */

// #define FAUST_TEST 1
#if FAUST_TEST

fn test_bench__allocation_and_basic_usage() -> s32
{
    mydsp dsp;
    dsp.init(SAMP_RATE);
    
    s32 n_ins = dsp.getNumInputs();
    s32 n_outs = dsp.getNumOutputs();
    auto [base, err] = bench::make_buffers(n_ins, n_outs);
    if (err) {
        printf("Critical allocation error: %d\n", err);
        exit(err);
    }

    Real** inputs = (Real**)base;
    Real** outputs = inputs + n_ins;

#if FILL_INPUTS
    fill_inputs(inputs, dsp.getNumInputs());
#endif

    bench::warmup(dsp, inputs, outputs);
    BenchReport report = bench::measure(dsp, inputs, outputs);
    bench::print_report(report); // the output will be redirected manually

    bench::free_buffers(inputs);
    return 0;
}

#undef fn
#endif // FAUST_TEST
