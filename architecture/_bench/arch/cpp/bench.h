// architecture/bench/arch/cpp/bench.h

#ifndef FAUSTBENCH_HH
#define FAUSTBENCH_HH

#include <chrono>

#include "common.h"

// Benchmark compiler options.

#ifndef BENCH_LANG
#define BENCH_LANG "cpp"
#endif
#ifndef BENCH_DSP
#define BENCH_DSP "unknown"
#endif
#ifndef BENCH_CASE
#define BENCH_CASE "default"
#endif
#ifndef BENCH_MODE
#define BENCH_MODE "scalar"
#endif
#ifndef BENCH_OPTIM
#define BENCH_OPTIM "O3"
#endif
#ifndef WARMUP_ITERS
#define WARMUP_ITERS 50
#endif
#ifndef BENCH_BARRIERS
#define BENCH_BARRIERS 1
#endif
#ifndef MIN_RUNTIME_SECS
#define MIN_RUNTIME_SECS 1.0
#endif
#ifndef MAX_RUNTIME_SECS
#define MAX_RUNTIME_SECS 60.0
#endif
#ifndef TARGET_BATCH_SECS
#define TARGET_BATCH_SECS 0.005
#endif
#ifndef MAX_BATCH_SIZE
#define MAX_BATCH_SIZE 10'000
#endif
#ifndef MAX_BATCHES
#define MAX_BATCHES 1'000
#endif
#ifndef FILL_INPUTS
#define FILL_INPUTS 0
#endif
#ifndef CSV_PATH
#define CSV_PATH "report/cpp/report.csv"
#endif
#ifndef WRITE_CSV
#define WRITE_CSV 0
#endif

inline namespace bench {

#if BENCH_BARRIERS
    #define _bench_do_not_optimize(x) _do_not_optimize(x)
    #define _bench_clobber_memory() _clobber_memory()
#else
    #define _bench_do_not_optimize(x)
    #define _bench_clobber_memory()
#endif

// Faust Benchmark helpers.

inline constexpr vstring PRECISION_STRINGS[] = {"single", "double", "quad"};
inline constexpr vstring PRECISION = PRECISION_STRINGS[sizeof(FAUSTFLOAT)/4 - 1];

struct BenchBatch {
    s32 iterations     = 0;
    f64 elapsed_s      = 0.0;
    f64 ns_per_compute = 0.0;
};

struct BenchRun {
    s32 batches             = 0;
    s32 iterations          = 0;
    f64 elapsed_s           = 0.0;
    f64 ns_per_compute      = 0.0;
    f64 slow_ns_per_compute = 0.0;
    f64 fast_ns_per_compute = 0.0;
};

template<typename Func>
fn _measure_adaptive(Func&& function) -> BenchRun
{
    using Clock = std::chrono::steady_clock;

    BenchBatch batches[MAX_BATCHES]{};

    s32 batch_count = 0;
    s32 total_iters = 0;
    f64 total_elapsed_s = 0.0;

    s32 batch_iters = 1;

    while (true) {
        if (batch_count >= MAX_BATCHES) {
            break;
        }
        if (total_iters >= COMPUTE_ITERS && total_elapsed_s >= f64(MIN_RUNTIME_SECS)) {
            break;
        }
        if (total_elapsed_s >= f64(MAX_RUNTIME_SECS)) {
            break;
        }
        if (batch_iters < 1) {
            batch_iters = 1;
        }
        if (batch_iters > MAX_BATCH_SIZE) {
            batch_iters = MAX_BATCH_SIZE;
        }
        s32 remaining_iters = COMPUTE_ITERS - total_iters;
        if (remaining_iters > 0 && batch_iters > remaining_iters) {
            batch_iters = remaining_iters;
        }

        auto beg = Clock::now();

        for (s32 i = 0; i < batch_iters; i++) {
            function();
        }

        auto end = Clock::now();

        f64 elapsed_s = std::chrono::duration<f64>(end - beg).count();
        f64 ns_per_compute = elapsed_s * 1.0e9 / f64(batch_iters);

        batches[batch_count].iterations = batch_iters;
        batches[batch_count].elapsed_s = elapsed_s;
        batches[batch_count].ns_per_compute = ns_per_compute;

        batch_count++;
        total_iters += batch_iters;
        total_elapsed_s += elapsed_s;

        if (elapsed_s > 0.0) {
            f64 scale = f64(TARGET_BATCH_SECS) / elapsed_s;
            s32 next_batch_iters = s32(f64(batch_iters) * scale);

            if (next_batch_iters <= batch_iters) {
                next_batch_iters = batch_iters + 1;
            }
            if (next_batch_iters > batch_iters * 10) {
                next_batch_iters = batch_iters * 10;
            }
            if (next_batch_iters > MAX_BATCH_SIZE) {
                next_batch_iters = MAX_BATCH_SIZE;
            }

            batch_iters = next_batch_iters;
        } else {
            batch_iters *= 10;

            if (batch_iters > MAX_BATCH_SIZE) {
                batch_iters = MAX_BATCH_SIZE;
            }
        }
    }

    if (batch_count == 0 || total_iters == 0) {
        return {};
    }

    s32 significant_count = batch_count / 10;
    if (significant_count < 1) {
        significant_count = 1;
    }
    s32 significant_start = batch_count - significant_count;
    s32 significant_iters = 0;
    f64 significant_elapsed_s = 0.0;
    f64 weighted_ns_sum = 0.0;
    f64 fastest_ns = batches[significant_start].ns_per_compute;
    f64 slowest_ns = batches[significant_start].ns_per_compute;

    for (s32 i = significant_start; i < batch_count; i++) {
        significant_iters += batches[i].iterations;
        significant_elapsed_s += batches[i].elapsed_s;
        weighted_ns_sum += batches[i].ns_per_compute * f64(batches[i].iterations);
        if (batches[i].ns_per_compute < fastest_ns) {
            fastest_ns = batches[i].ns_per_compute;
        }
        if (batches[i].ns_per_compute > slowest_ns) {
            slowest_ns = batches[i].ns_per_compute;
        }
    }

    if (significant_iters == 0) {
        return {};
    }

    BenchRun run{};
    run.batches = batch_count;
    run.iterations = significant_iters;
    run.elapsed_s = significant_elapsed_s;
    run.ns_per_compute = weighted_ns_sum / f64(significant_iters);
    run.fast_ns_per_compute = fastest_ns;
    run.slow_ns_per_compute = slowest_ns;
    return run;
}

// Faust Benchmark public API.

struct FaustReport {
    vstring language          = BENCH_LANG;
    vstring dsp               = BENCH_DSP;
    vstring bench_case        = BENCH_CASE;
    vstring mode              = BENCH_MODE;
    vstring precision         = PRECISION;
    vstring opt               = BENCH_OPTIM;
    s32 samp_rate             = SAMP_RATE;
    s32 buff_size             = BUFF_SIZE;
    s32 inputs                = 0;
    s32 outputs               = 0;
    s32 warmup_iters          = WARMUP_ITERS;
    s32 run_iters             = COMPUTE_ITERS;
    s32 batches               = 0;
    f64 elapsed_s             = 0.0;
    f64 ns_per_compute        = 0.0;
    f64 fast_ns_per_compute   = 0.0;
    f64 slow_ns_per_compute   = 0.0;
    f64 spread_ns_per_compute = 0.0;
    f64 spread_percent        = 0.0;
    f64 ns_per_frame          = 0.0;
    f64 ns_per_out_samp       = 0.0;
    f64 frames_per_s          = 0.0;
    f64 fast_frames_per_s     = 0.0;
    f64 slow_frames_per_s     = 0.0;
    f64 out_samp_per_s        = 0.0;
    f64 fast_out_samp_per_s   = 0.0;
    f64 slow_out_samp_per_s   = 0.0;
    f64 checksum              = 0.0;
};

fn fill_inputs(Real** inputs, s32 const n_ins) -> void
{
    for (s32 chan = 0; chan < n_ins; chan++) {
        for (s32 frame = 0; frame < BUFF_SIZE; frame++) {
            inputs[chan][frame] = 0.001 * (frame + 1) + chan;
        }
    }
}

fn warmup(auto& dsp, Real** inputs, Real** outputs) -> void
{
    for (int i = 0; i < WARMUP_ITERS; i++) {
        dsp.compute(BUFF_SIZE, inputs, outputs);
    }
}

fn measure(auto& dsp, Real** inputs, Real** outputs) -> FaustReport
{
    BenchRun run = _measure_adaptive([&]() {
        _bench_do_not_optimize(inputs);
        _bench_do_not_optimize(outputs);
        dsp.compute(BUFF_SIZE, inputs, outputs);
        _bench_clobber_memory();
    });

    s32 dsp_inputs = dsp.getNumInputs();
    s32 dsp_outputs = dsp.getNumOutputs();

    f64 total_computes = f64(run.iterations);
    f64 total_frames = total_computes * f64(BUFF_SIZE);
    f64 total_output_samples = total_frames * f64(dsp_outputs);

    FaustReport report{};
    report.inputs = dsp_inputs;
    report.outputs = dsp_outputs;
    report.run_iters = run.iterations;
    report.batches = run.batches;
    report.elapsed_s = run.elapsed_s;
    report.ns_per_compute = run.ns_per_compute;
    report.slow_ns_per_compute = run.slow_ns_per_compute;
    report.fast_ns_per_compute = run.fast_ns_per_compute;
    report.spread_ns_per_compute = report.slow_ns_per_compute - report.fast_ns_per_compute;

    if (report.ns_per_compute > 0.0) {
        report.spread_percent = report.spread_ns_per_compute / report.ns_per_compute * 100.0;
    } else {
        report.spread_percent = 0.0;
    }

    report.ns_per_frame = report.ns_per_compute / f64(BUFF_SIZE);

    if (dsp_outputs > 0 && report.elapsed_s > 0.0) {
        report.ns_per_out_samp = report.ns_per_frame / f64(dsp_outputs);
        report.out_samp_per_s = total_output_samples / report.elapsed_s;
    } else {
        report.ns_per_out_samp = 0.0;
        report.out_samp_per_s = 0.0;
    }

    if (report.elapsed_s > 0.0) {
        report.frames_per_s = total_frames / report.elapsed_s;
    }
    if (report.fast_ns_per_compute > 0.0) {
        report.fast_frames_per_s = 1.0e9 / report.fast_ns_per_compute * f64(BUFF_SIZE);
        report.fast_out_samp_per_s = report.fast_frames_per_s * f64(dsp_outputs);
    }
    if (report.slow_ns_per_compute > 0.0) {
        report.slow_frames_per_s = 1.0e9 / report.slow_ns_per_compute * f64(BUFF_SIZE);
        report.slow_out_samp_per_s = report.slow_frames_per_s * f64(dsp_outputs);
    }

    return report;
}

fn checksum_outputs(Real** outputs, s32 const n_outs) -> f64
{
    f64 sum = 0.0;
    for (s32 chan = 0; chan < n_outs; chan++) {
        for (s32 frame = 0; frame < BUFF_SIZE; frame++) {
            sum += f64(outputs[chan][frame]);
        }
    }
    return sum;
}

fn print_report(FaustReport const& report) -> void
{
    printf("Faust compute benchmark\n");
    puts("------------------------------------");
    printf("Identity\n");
    printf("  language:       %s\n",     report.language.data());
    printf("  dsp:            %s\n",     report.dsp.data());
    printf("  bench case:     %s\n",     report.bench_case.data());
    printf("  mode:           %s\n",     report.mode.data());
    printf("  precision:      %s\n",     report.precision.data());
    printf("  optimization:   %s\n",     report.opt.data());
    puts("------------------------------------");
    printf("Configuration\n");
    printf("  sample rate:    %d\n",     report.samp_rate);
    printf("  buffer size:    %d\n",     report.buff_size);
    printf("  inputs:         %d\n",     report.inputs);
    printf("  outputs:        %d\n",     report.outputs);
    printf("  warm-up iters:  %d\n",     report.warmup_iters);
    printf("  run iters:      %d\n",     report.run_iters);
    printf("  batches:        %d\n",     report.batches);
    puts("------------------------------------");
    printf("Timing\n");
    printf("  elapsed:        %.9f s\n", report.elapsed_s);
    printf("  ns/compute:     %.3f\n",   report.ns_per_compute);
    printf("  fast ns/cmp:    %.3f\n",   report.fast_ns_per_compute);
    printf("  slow ns/cmp:    %.3f\n",   report.slow_ns_per_compute);
    printf("  spread ns/cmp:  %.3f\n",   report.spread_ns_per_compute);
    printf("  spread %%:       %.3f\n",  report.spread_percent);
    printf("  ns/frame:       %.3f\n",   report.ns_per_frame);
    printf("  ns/out_samp:    %.3f\n",   report.ns_per_out_samp);
    puts("------------------------------------");
    printf("Throughput\n");
    printf("  frames/s:       %.3f\n",   report.frames_per_s);
    printf("  fast frames/s:  %.3f\n",   report.fast_frames_per_s);
    printf("  slow frames/s:  %.3f\n",   report.slow_frames_per_s);
    printf("  out_samp/s: %.3f\n",   report.out_samp_per_s);
    printf("  fast out_samp/s: %.3f\n",   report.fast_out_samp_per_s);
    printf("  slow out_samp/s: %.3f\n",   report.slow_out_samp_per_s);
    puts("------------------------------------");
    printf("Validation\n");
    printf("  checksum:       %.17g\n", report.checksum);
}

// Appends one headerless benchmark row to CSV_PATH.
// Assumes CSV_PATH and its parent directory are provided by the build system.
// Does not write headers or manage existing CSV data.
// Called only for structured runs when WRITE_CSV is enabled.
fn write_csv(FaustReport const& report) -> void
{
    FILE* fp = fopen(CSV_PATH, "a");
    if (!fp) {
        printf("Failed to open CSV file: %s\n", CSV_PATH);
        return;
    }

    fprintf(
        fp,
        "%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%.17g,%.17g,%.17g,%.17g,%.17g,"
        "%.17g,%.17g,%.17g,%.17g,%.17g,%.17g,%.17g,%.17g,%.17g,%.17g\n",
        report.language.data(), report.bench_case.data(), report.mode.data(),
        report.precision.data(), report.opt.data(),
        report.samp_rate, report.buff_size,
        report.inputs, report.outputs,
        report.warmup_iters, report.run_iters, report.batches,
        report.elapsed_s,
        report.ns_per_compute,
        report.fast_ns_per_compute,
        report.slow_ns_per_compute,
        report.spread_ns_per_compute,
        report.spread_percent,
        report.ns_per_frame,
        report.ns_per_out_samp,
        report.frames_per_s,
        report.fast_frames_per_s,
        report.slow_frames_per_s,
        report.out_samp_per_s,
        report.fast_out_samp_per_s,
        report.slow_out_samp_per_s,
        report.checksum
    );

    fclose(fp);
}

}       // namespace bench
#undef  fn
#endif  // FAUSTBENCH_HH
