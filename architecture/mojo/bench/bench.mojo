# bench/bench.mojo

from std.pathlib import Path
from std.benchmark import Report, Unit, run, clobber_memory

from conf import *
from mem import *
from dsp import FaustDsp

# --------------------------------------------------------------
# Faust benchmark architecture implementation.
# --------------------------------------------------------------

# Compile time flags.

comptime BENCH_LANG = get_defined_string["BENCH_LANG", "mojo"]()
comptime BENCH_OPTIM = get_defined_string["BENCH_OPTIM", "O3"]()
comptime WARMUP_ITERS = get_defined_int["WARMUP_ITERS", 1_000]()
comptime COMPUTE_ITERS = get_defined_int["COMPUTE_ITERS", 1_000_000]()
comptime FILL_INPUTS = get_defined_bool["FILL_INPUTS", False]()
comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 128]())
comptime FAUST_DTYPE = get_defined_dtype["FAUST_DTYPE", F64.dtype]()
comptime CSV_PATH = get_defined_string["CSV_PATH", "report/mojo/report.csv"]()

# Comptime constants and type definitions.

comptime dfaust = FAUST_DTYPE
comptime FaustFloat = SIMD[dfaust, 1]

comptime MIN_RUNTIME_SECS: F64 = 0.1
comptime MAX_RUNTIME_SECS: F64 = 60.0

comptime PRECISION_STRINGS: InlineArray[String, 2] = ["single", "double"]
comptime PRECISION = PRECISION_STRINGS[size_of[FaustFloat]() // 4 - 1]
comptime CSV_HEADER = "language,precision,opt,samp_rate,buff_size,inputs,outputs,"
                      "warmup_iters,run_iters,elapsed_s,ns_per_compute,ns_per_frame,"
                      "ns_per_out_samp,frames_per_s,out_samp_per_s,checksum\n"

# Faust benchmark API.

struct FaustReport(ImplicitlyCopyable):
    var precision: String
    var samp_rate: S32
    var buff_size: S32
    var n_ins: S32
    var n_outs: S32
    var warmup_iters: S32
    var compute_iters: S32
    var elapsed_s: F64
    var ns_per_compute: F64
    var ns_per_frame: F64
    var ns_per_out_samp: F64
    var frames_per_s: F64
    var output_samples_per_sec: F64
    var checksum: F64
    def __init__(out report):
        report.precision = PRECISION
        report.samp_rate = SAMP_RATE
        report.buff_size = BUFF_SIZE
        report.n_ins = 0
        report.n_outs = 0
        report.warmup_iters = S32(WARMUP_ITERS)
        report.compute_iters = S32(COMPUTE_ITERS)
        report.elapsed_s = 0.0
        report.ns_per_compute = 0.0
        report.ns_per_frame = 0.0
        report.ns_per_out_samp = 0.0
        report.frames_per_s = 0.0
        report.output_samples_per_sec = 0.0
        report.checksum = 0.0

def fill_inputs[dreal: DType](inputs: MutaStreams[dreal], n_ins: S32) -> None:
    comptime Real = SIMD[dreal, 1]
    for chan in range(n_ins):
        for frame in range(BUFF_SIZE):
            var value = 0.001 * F64(frame + 1) + F64(chan)
            inputs[chan][frame] = Real(value)

def warmup[dreal: DType](
    mut dsp: Some[FaustDsp], inputs: MutaStreams[dreal], outputs: MutaStreams[dreal]
) -> None: pass

def measure[dreal: DType, Dsp: FaustDsp](
    mut dsp: Dsp, inputs: MutaStreams[dreal], outputs: MutaStreams[dreal]
) raises -> FaustReport:
    comptime Real = SIMD[dreal, 1]
    @parameter
    def bench_compute() capturing:
        var read_inputs = inputs.bitcast[Ptr[Real, READ_EXT]]().as_immutable()
        dsp.compute[dreal](BUFF_SIZE, read_inputs, outputs)
    var raw_report = run[func4=bench_compute](
        WARMUP_ITERS, COMPUTE_ITERS, MIN_RUNTIME_SECS, MAX_RUNTIME_SECS
    )
    clobber_memory()

    var n_ins = dsp.get_num_inputs()
    var n_outs = dsp.get_num_outputs()
    var run_iters = raw_report.iters()
    var total_frames = F64(run_iters) * F64(BUFF_SIZE)
    var total_output_samples = total_frames * F64(n_outs)

    var report = FaustReport()
    report.n_ins = n_ins
    report.n_outs = n_outs
    report.compute_iters = S32(run_iters)
    report.elapsed_s = raw_report.duration(Unit.s)
    report.ns_per_compute = raw_report.mean(Unit.ns)
    report.ns_per_frame = report.ns_per_compute / F64(BUFF_SIZE)

    if n_outs > 0:
        report.ns_per_out_samp = report.ns_per_frame / F64(n_outs)
        report.output_samples_per_sec = total_output_samples / report.elapsed_s
    else:
        report.ns_per_out_samp = 0.0
        report.output_samples_per_sec = 0.0

    report.frames_per_s = total_frames / report.elapsed_s
    return report

def checksum_outputs[dreal: DType](outputs: MutaStreams[dreal], n_outs: S32) -> F64:
    comptime Real = SIMD[dreal, 1]
    var sum = 0.0
    for chan in range(n_outs):
        for frame in range(BUFF_SIZE):
            sum += F64(outputs[chan][frame])
    return sum

def print_report(report: FaustReport) -> None:
    print("Faust compute benchmark")
    print("Precision:      ", report.precision)
    print("sample rate:    ", report.samp_rate)
    print("buffer size:    ", report.buff_size)
    print("inputs:         ", report.n_ins)
    print("outputs:        ", report.n_outs)
    print("warm-up iters:  ", WARMUP_ITERS)
    print("compute iters:  ", report.compute_iters)
    print("------------------------------------")
    print("elapsed:        ", report.elapsed_s, " s")
    print("ns/compute:     ", report.ns_per_compute)
    print("ns/frame:       ", report.ns_per_frame)
    print("ns/out_sample:  ", report.ns_per_out_samp)
    print("frames/s:       ", report.frames_per_s)
    print("out_samples/s:  ", report.output_samples_per_sec)
    print("checksum:       ", report.checksum)

def write_csv(report: FaustReport) raises -> None:
    var path = Path(CSV_PATH)
    var csv = get_csv(report)
    if path.exists():
        var content = path.read_text()
        path.write_text(content + csv)
    else:
        path.write_text(CSV_HEADER + csv)

def get_csv(report: FaustReport) -> String:
    csv: String
        = BENCH_LANG + "," + String(PRECISION) + "," + BENCH_OPTIM                    + ","
        + String(report.samp_rate)      + "," + String(report.buff_size)              + ","
        + String(report.n_ins)          + "," + String(report.n_outs)                 + ","
        + String(report.warmup_iters)   + "," + String(report.compute_iters)          + ","
        + String(report.elapsed_s)      + "," + String(report.ns_per_compute)         + ","
        + String(report.ns_per_frame)   + "," + String(report.ns_per_out_samp)   + ","
        + String(report.frames_per_s) + "," + String(report.output_samples_per_sec) + ","
        + String(report.checksum) + "\n"
    return csv

