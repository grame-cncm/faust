# bench/bench.mojo

from std.pathlib import Path
from std.time import perf_counter
from std.benchmark import keep, clobber_memory

from conf import *
from mem import *
from dsp import FaustDsp

# ==============================================================
# Faust benchmark architecture implementation.
# ==============================================================

# Compiler options.

comptime BENCH_LANG = get_defined_string["BENCH_LANG", "mojo"]()
comptime BENCH_DSP = get_defined_string["BENCH_DSP", "unknown"]()
comptime BENCH_CASE = get_defined_string["BENCH_CASE", "default"]()
comptime BENCH_MODE = get_defined_string["BENCH_MODE", "scalar"]()
comptime BENCH_OPTIM = get_defined_string["BENCH_OPTIM", "O3"]()
comptime BENCH_BARRIERS = get_defined_int["BENCH_BARRIERS", 1]()
comptime WARMUP_ITERS = get_defined_int["WARMUP_ITERS", 50]()
comptime COMPUTE_ITERS = get_defined_int["COMPUTE_ITERS", 1_000_000]()
comptime MIN_RUNTIME_SECS = F64(get_defined_int["MIN_RUNTIME_SECS", 1]())
comptime MAX_RUNTIME_SECS = F64(get_defined_int["MAX_RUNTIME_SECS", 60]())
comptime TARGET_BATCH_SECS = 0.005
comptime MAX_BATCH_SIZE = get_defined_int["MAX_BATCH_SIZE", 10_000]()
comptime MAX_BATCHES = get_defined_int["MAX_BATCHES", 1_000]()
comptime FILL_INPUTS = get_defined_bool["FILL_INPUTS", False]()
comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 128]())
comptime PRECISION = get_defined_string["PRECISION", "single"]()
comptime CSV_PATH = get_defined_string["CSV_PATH", "report/mojo/report.csv"]()
comptime WRITE_CSV = get_defined_bool["WRITE_CSV", False]()

# Comptime dfaust assertion.
def assert_dfaust() -> None: comptime assert dfaust == F32.dtype
comptime _ = assert_dfaust()

# Faust benchmark API.

struct BenchBatch(ImplicitlyCopyable):
    var iterations: S32
    var elapsed_s: F64
    var ns_per_compute: F64
    def __init__(out batch):
        batch.iterations = 0
        batch.elapsed_s = 0.0
        batch.ns_per_compute = 0.0

struct BenchRun(ImplicitlyCopyable):
    var batches: S32
    var iterations: S32
    var elapsed_s: F64
    var ns_per_compute: F64
    var fast_ns_per_compute: F64
    var slow_ns_per_compute: F64
    def __init__(out run):
        run.batches = 0
        run.iterations = 0
        run.elapsed_s = 0.0
        run.ns_per_compute = 0.0
        run.fast_ns_per_compute = 0.0
        run.slow_ns_per_compute = 0.0

struct FaustReport(ImplicitlyCopyable):
    var language: String
    var dsp: String
    var bench_case: String
    var mode: String
    var precision: String
    var opt: String
    var samp_rate: S32
    var buff_size: S32
    var inputs: S32
    var outputs: S32
    var warmup_iters: S32
    var run_iters: S32
    var batches: S32
    var elapsed_s: F64
    var ns_per_compute: F64
    var fast_ns_per_compute: F64
    var slow_ns_per_compute: F64
    var spread_ns_per_compute: F64
    var spread_percent: F64
    var ns_per_frame: F64
    var ns_per_out_samp: F64
    var frames_per_s: F64
    var fast_frames_per_s: F64
    var slow_frames_per_s: F64
    var out_samp_per_s: F64
    var fast_out_samp_per_s: F64
    var slow_out_samp_per_s: F64
    var checksum: F64
    def __init__(out report):
        report.language = BENCH_LANG
        report.dsp = BENCH_DSP
        report.bench_case = BENCH_CASE
        report.precision = PRECISION
        report.mode = BENCH_MODE
        report.opt = BENCH_OPTIM
        report.samp_rate = SAMP_RATE
        report.buff_size = BUFF_SIZE
        report.inputs = 0
        report.outputs = 0
        report.warmup_iters = S32(WARMUP_ITERS)
        report.run_iters = S32(COMPUTE_ITERS)
        report.batches = 0
        report.elapsed_s = 0.0
        report.ns_per_compute = 0.0
        report.fast_ns_per_compute = 0.0
        report.slow_ns_per_compute = 0.0
        report.spread_ns_per_compute = 0.0
        report.spread_percent = 0.0
        report.ns_per_frame = 0.0
        report.ns_per_out_samp = 0.0
        report.frames_per_s = 0.0
        report.fast_frames_per_s = 0.0
        report.slow_frames_per_s = 0.0
        report.out_samp_per_s = 0.0
        report.fast_out_samp_per_s = 0.0
        report.slow_out_samp_per_s = 0.0
        report.checksum = 0.0

def fill_inputs(inputs: MutaStreams, n_ins: S32) -> None:
    for chan in range(n_ins):
        for frame in range(BUFF_SIZE):
            var value = 0.001 * F64(frame + 1) + F64(chan)
            inputs[chan][frame] = FaustFloat(value)

def warmup(
    mut dsp: Some[FaustDsp], inputs: MutaStreams, outputs: MutaStreams
) -> None:
    var read_inputs = inputs.bitcast[Ptr[FaustFloat, READ_NOTRK]]().as_immutable()
    for _ in range(S32(WARMUP_ITERS)):
        dsp.compute(BUFF_SIZE, read_inputs, outputs)

def _measure_adaptive(
    mut dsp: Some[FaustDsp], inputs: MutaStreams, outputs: MutaStreams
) -> BenchRun:
    var read_inputs = inputs.bitcast[Ptr[FaustFloat, READ_NOTRK]]().as_immutable()

    var batches = Arr[BenchBatch, MAX_BATCHES](fill=BenchBatch())

    var batch_count = S32(0)
    var total_iters = S32(0)
    var total_elapsed_s = 0.0

    var batch_iters = S32(1)

    while True:
        if batch_count >= S32(MAX_BATCHES):
            break
        if total_iters >= S32(COMPUTE_ITERS) and total_elapsed_s >= MIN_RUNTIME_SECS:
            break
        if total_elapsed_s >= MAX_RUNTIME_SECS:
            break
        if batch_iters < 1:
            batch_iters = 1
        if batch_iters > S32(MAX_BATCH_SIZE):
            batch_iters = S32(MAX_BATCH_SIZE)
        var remaining_iters = S32(COMPUTE_ITERS) - total_iters
        if remaining_iters > 0 and batch_iters > remaining_iters:
            batch_iters = remaining_iters

        var beg = perf_counter()

        for _ in range(batch_iters):
            comptime if BENCH_BARRIERS:
                keep(read_inputs) 
                keep(outputs)
            dsp.compute(BUFF_SIZE, read_inputs, outputs)
            comptime if BENCH_BARRIERS:
                clobber_memory()

        var end = perf_counter()

        var elapsed_s = end - beg
        var ns_per_compute = elapsed_s * 1.0e9 / F64(batch_iters)

        batches[Int(batch_count)].iterations = batch_iters
        batches[Int(batch_count)].elapsed_s = elapsed_s
        batches[Int(batch_count)].ns_per_compute = ns_per_compute

        batch_count += 1
        total_iters += batch_iters
        total_elapsed_s += elapsed_s

        if elapsed_s > 0.0:
            var scale = TARGET_BATCH_SECS / elapsed_s
            var next_batch_iters = S32(F64(batch_iters) * scale)

            if next_batch_iters <= batch_iters:
                next_batch_iters = batch_iters + 1
            if next_batch_iters > batch_iters * 10:
                next_batch_iters = batch_iters * 10
            if next_batch_iters > S32(MAX_BATCH_SIZE):
                next_batch_iters = S32(MAX_BATCH_SIZE)

            batch_iters = next_batch_iters
        else:
            batch_iters *= 10

            if batch_iters > S32(MAX_BATCH_SIZE):
                batch_iters = S32(MAX_BATCH_SIZE)

    if batch_count == 0 or total_iters == 0:
        return BenchRun()

    var significant_count = batch_count // 10
    if significant_count < 1:
        significant_count = 1
    var significant_start = batch_count - significant_count
    var significant_iters = S32(0)
    var significant_elapsed_s = 0.0
    var weighted_ns_sum = 0.0
    var fastest_ns = batches[Int(significant_start)].ns_per_compute
    var slowest_ns = batches[Int(significant_start)].ns_per_compute

    for i in range(significant_start, batch_count):
        var batch = batches[i]

        significant_iters += batch.iterations
        significant_elapsed_s += batch.elapsed_s
        weighted_ns_sum += batch.ns_per_compute * F64(batch.iterations)

        if batch.ns_per_compute < fastest_ns:
            fastest_ns = batch.ns_per_compute
        if batch.ns_per_compute > slowest_ns:
            slowest_ns = batch.ns_per_compute

    if significant_iters == 0:
        return BenchRun()

    var run = BenchRun()
    run.batches = batch_count
    run.iterations = significant_iters
    run.elapsed_s = significant_elapsed_s
    run.ns_per_compute = weighted_ns_sum / F64(significant_iters)
    run.fast_ns_per_compute = fastest_ns
    run.slow_ns_per_compute = slowest_ns
    return run

def measure(
    mut dsp: Some[FaustDsp], inputs: MutaStreams, outputs: MutaStreams
) raises -> FaustReport:
    var raw_report = _measure_adaptive(dsp, inputs, outputs)
    var dsp_inputs = dsp.get_num_inputs()
    var dsp_outputs = dsp.get_num_outputs()
    var run_iters = raw_report.iterations
    var total_frames = F64(run_iters) * F64(BUFF_SIZE)
    var total_output_samples = total_frames * F64(dsp_outputs)
    var report = FaustReport()
    report.inputs = dsp_inputs
    report.outputs = dsp_outputs
    report.run_iters = S32(run_iters)
    report.batches = raw_report.batches
    report.elapsed_s = raw_report.elapsed_s
    report.ns_per_compute = raw_report.ns_per_compute
    report.fast_ns_per_compute = raw_report.fast_ns_per_compute
    report.slow_ns_per_compute = raw_report.slow_ns_per_compute
    report.spread_ns_per_compute = report.slow_ns_per_compute - report.fast_ns_per_compute
    if report.ns_per_compute > 0.0:
        report.spread_percent = report.spread_ns_per_compute / report.ns_per_compute * 100.0
    else:
        report.spread_percent = 0.0
    report.ns_per_frame = report.ns_per_compute / F64(BUFF_SIZE)
    if dsp_outputs > 0 and report.elapsed_s > 0.0:
        report.ns_per_out_samp = report.ns_per_frame / F64(dsp_outputs)
        report.out_samp_per_s = total_output_samples / report.elapsed_s
    else:
        report.ns_per_out_samp = 0.0
        report.out_samp_per_s = 0.0
    if report.elapsed_s > 0.0:
        report.frames_per_s = total_frames / report.elapsed_s
    if report.fast_ns_per_compute > 0.0:
        report.fast_frames_per_s = 1.0e9 / report.fast_ns_per_compute * F64(BUFF_SIZE)
        report.fast_out_samp_per_s = report.fast_frames_per_s * F64(dsp_outputs)
    if report.slow_ns_per_compute > 0.0:
        report.slow_frames_per_s = 1.0e9 / report.slow_ns_per_compute * F64(BUFF_SIZE)
        report.slow_out_samp_per_s = report.slow_frames_per_s * F64(dsp_outputs)
    report.checksum = checksum_outputs(outputs, dsp_outputs)
    return report

def checksum_outputs(outputs: MutaStreams, n_outs: S32) -> F64:
    var sum = 0.0
    for chan in range(n_outs):
        for frame in range(BUFF_SIZE):
            sum += F64(outputs[chan][frame])
    return sum

def print_report(report: FaustReport) -> None:
    print("Faust compute benchmark")
    print("------------------------------------")
    print("Identity")
    print("  language:       ", report.language)
    print("  dsp:            ", report.dsp)
    print("  bench case:     ", report.bench_case)
    print("  mode:           ", report.mode)
    print("  precision:      ", report.precision)
    print("  optimization:   ", report.opt)
    print("------------------------------------")
    print("Configuration")
    print("  sample rate:    ", report.samp_rate)
    print("  buffer size:    ", report.buff_size)
    print("  inputs:         ", report.inputs)
    print("  outputs:        ", report.outputs)
    print("  warm-up iters:  ", report.warmup_iters)
    print("  run iters:      ", report.run_iters)
    print("  batches:        ", report.batches)
    print("------------------------------------")
    print("Timing")
    print("  elapsed:        ", report.elapsed_s, "s")
    print("  ns/compute:     ", report.ns_per_compute)
    print("  fast ns/cmp:    ", report.fast_ns_per_compute)
    print("  slow ns/cmp:    ", report.slow_ns_per_compute)
    print("  spread ns/cmp:  ", report.spread_ns_per_compute)
    print("  spread %:       ", report.spread_percent)
    print("  ns/frame:       ", report.ns_per_frame)
    print("  ns/out_samp:    ", report.ns_per_out_samp)
    print("------------------------------------")
    print("Throughput")
    print("  frames/s:       ", report.frames_per_s)
    print("  fast frames/s:  ", report.fast_frames_per_s)
    print("  slow frames/s:  ", report.slow_frames_per_s)
    print("  out_samp/s:     ", report.out_samp_per_s)
    print("  fast out_samp/s:", report.fast_out_samp_per_s)
    print("  slow out_samp/s:", report.slow_out_samp_per_s)
    print("------------------------------------")
    print("Validation")
    print("  checksum:       ", report.checksum)

def write_csv(report: FaustReport) raises -> None:
    # Appends one headerless benchmark row to CSV_PATH.
    # Assumes CSV_PATH and its parent directory are provided by the build system.
    # Does not write headers or manage existing CSV data.
    # Called only for structured runs when WRITE_CSV is enabled.
    var csv = String(
        report.language + "," + report.bench_case + "," + report.mode + ","
        + report.precision + "," + report.opt + ","
        + String(report.samp_rate) + "," + String(report.buff_size) + ","
        + String(report.inputs) + "," + String(report.outputs) + ","
        + String(report.warmup_iters) + "," + String(report.run_iters) + ","
        + String(report.batches) + ","
        + String(report.elapsed_s) + ","
        + String(report.ns_per_compute) + ","
        + String(report.fast_ns_per_compute) + ","
        + String(report.slow_ns_per_compute) + ","
        + String(report.spread_ns_per_compute) + ","
        + String(report.spread_percent) + ","
        + String(report.ns_per_frame) + ","
        + String(report.ns_per_out_samp) + ","
        + String(report.frames_per_s) + ","
        + String(report.fast_frames_per_s) + ","
        + String(report.slow_frames_per_s) + ","
        + String(report.out_samp_per_s) + ","
        + String(report.fast_out_samp_per_s) + ","
        + String(report.slow_out_samp_per_s) + ","
        + String(report.checksum) + "\n"
    )
    var path = Path(CSV_PATH)
    if path.exists():
        var content = path.read_text()
        path.write_text(content + csv)
    else:
        path.write_text(csv)
