from std.memory import *
from std.sys import exit
from std.sys.info import *
from std.sys.defines import is_defined, get_defined_int, get_defined_bool, get_defined_dtype
from std.benchmark import Report, Unit, run, clobber_memory

# ------------------------------------------
# Faust benchmark architecture for Mojo
# ------------------------------------------

def measure[dreal: DType](
    mut dsp: mydsp,
    buff_size: S32,
    inputs: MutaStreams[dreal],
    outputs: MutaStreams[dreal],
) raises -> Report:
    comptime Real = SIMD[dreal, 1]
    @parameter
    def bench_compute() capturing:
        var read_inputs = inputs.bitcast[Ptr[Real, READ_EXT]]().as_immutable()
        dsp.compute[dreal](buff_size, read_inputs, outputs)
    return run[func4=bench_compute](
        WARMUP_ITERS,
        COMPUTE_ITERS,
        MIN_RUNTIME_SECS,
        MAX_RUNTIME_SECS,
    )

def print_report(report: Report, n_ins: S32, n_outs: S32, checksum: F64) -> None:
    var elapsed_s = report.duration(Unit.s)
    var ns_per_compute = report.mean(Unit.ns)
    var ns_per_frame = ns_per_compute / F64(BUFF_SIZE)
    var ns_per_output_sample = 0.0
    var output_samples_per_sec = 0.0
    if n_outs > 0:
        ns_per_output_sample = ns_per_frame / F64(n_outs)
        output_samples_per_sec = (
            F64(report.iters()) * F64(BUFF_SIZE) * F64(n_outs) / elapsed_s
        )
    print("Faust compute benchmark")
    print("sample rate:    ", SAMP_RATE)
    print("buffer size:    ", BUFF_SIZE)
    print("inputs:         ", n_ins)
    print("outputs:        ", n_outs)
    print("warm-up iters:  ", WARMUP_ITERS)
    print("run iters:      ", report.iters())
    print("------------------------------------")
    print("elapsed:        ", elapsed_s, " s")
    print("ns/compute:     ", ns_per_compute)
    print("ns/frame:       ", ns_per_frame)
    print("ns/out_sample:  ", ns_per_output_sample)
    print("frames/s:       ", F64(report.iters()) * F64(BUFF_SIZE) / elapsed_s)
    print("out_samples/s:  ", output_samples_per_sec)
    print("checksum:       ", checksum)

# Measure helpers and utilities.

def fill_inputs[dtype: DType](
    buff_size: S32,
    inputs: Ptr[
        Ptr[SIMD[dtype, 1], MUTA_EXT],
        MUTA_EXT,
    ],
    n_ins: S32,
):
    comptime Real = SIMD[dtype, 1]
    for chan in range(n_ins):
        for frame in range(buff_size):
            var value = 0.001 * Float64(frame + 1) + Float64(chan)
            inputs[chan][frame] = Real(value)


def checksum_outputs[dtype: DType](
    outputs: Ptr[
        Ptr[SIMD[dtype, 1], MUTA_EXT],
        MUTA_EXT,
    ],
    buff_size: S32,
    n_outs: S32,
) -> Float64:
    comptime Real = SIMD[dtype, 1]
    var sum = 0.0
    for chan in range(n_outs):
        for frame in range(buff_size):
            sum += Float64(outputs[chan][frame])
    return sum

# Memory allocation helpers and utilities.

comptime AllocErr = S32
comptime AllocErr_None = S32(0)
comptime AllocErr_IllegalArg = S32(1)
comptime AllocErr_Exhausted  = S32(2)

comptime PTR_SIZE = size_of[OpaqPtr[MUTA_EXT]]()
comptime PTR_ALIGN = align_of[OpaqPtr[MUTA_EXT]]()
comptime NULL_PTR[T: AnyType, origin: Origin] = Ptr[T, origin](unsafe_from_address=0)

comptime PRECISION_STRINGS: InlineArray[String, 2] = ["single", "double"]

def align_up(num: SInt, aln: SInt) -> SInt:
    return (num + aln - 1) & ~(aln - 1)

def alloc_buffers[dreal: DType](
    buff_size: S32, n_ins: S32, n_outs: S32,
) -> Res[Ptr[SIMD[dreal, 1], MUTA_EXT], AllocErr]:
    comptime Real = SIMD[dreal, 1]
    if buff_size <= 0 or n_ins < 0 or n_outs < 0:
        return NULL_PTR[Real, MUTA_EXT], AllocErr_IllegalArg,
    var n_chans = n_ins + n_outs
    if n_chans <= 0:
        return NULL_PTR[Real, MUTA_EXT], AllocErr_IllegalArg,

    comptime REAL_SIZE = size_of[Real]()
    comptime REAL_ALIGN = align_of[Real]()
    comptime ALIGN = PTR_ALIGN if PTR_ALIGN > REAL_ALIGN else REAL_ALIGN

    var header_size = align_up(PTR_SIZE * SInt(n_chans), REAL_ALIGN)
    var block_size = REAL_SIZE * SInt(buff_size * n_chans)
    var tot_size = header_size + block_size
    var alloc_size = align_up(tot_size, ALIGN)

    var base = alloc[UInt8](alloc_size, alignment=ALIGN)
    if base == NULL_PTR[UInt8, MUTA_EXT]:
        return NULL_PTR[Real, MUTA_EXT], AllocErr_Exhausted

    return base.bitcast[Real](), AllocErr_None,
   
def init_buffers[dreal: DType](
    base: Ptr[SIMD[dreal, 1], MUTA_EXT],
    buff_size: S32,
    n_ins: S32,
    n_outs: S32,
) -> None:
    comptime Real = SIMD[dreal, 1]
    comptime RealPtr = Ptr[Real, MUTA_EXT]

    comptime REAL_SIZE = size_of[Real]()
    comptime REAL_ALIGN = align_of[Real]()

    var n_chans = n_ins + n_outs
    var header_size = align_up(PTR_SIZE * SInt(n_chans), REAL_ALIGN)
    var block_size = REAL_SIZE * SInt(buff_size * n_chans)

    var raw = base.bitcast[UInt8]()

    var header_beg = raw.bitcast[RealPtr]()
    var data_beg = (raw + header_size).bitcast[Real]()

    for i in range(n_chans):
        (header_beg + i).init_pointee_copy(data_beg + i * buff_size)

    memset(data_beg.bitcast[UInt8](), 0, block_size)

def make_buffers[dreal: DType](
    buff_size: S32, n_ins: S32, n_outs: S32
) -> Res[Ptr[SIMD[dreal, 1], MUTA_EXT], AllocErr]:
    var base, err = alloc_buffers[dreal](buff_size, n_ins, n_outs)
    if err != AllocErr_None:
        return NULL_PTR[SIMD[dreal, 1], MUTA_EXT], err
    init_buffers[dreal](base, buff_size, n_ins, n_outs)
    return base, AllocErr_None,

def free_buffers[dreal: DType](base: Ptr[SIMD[dreal, 1], MUTA_EXT]):
    comptime Real = SIMD[dreal, 1]
    if base == NULL_PTR[Real, MUTA_EXT]:
        return
    base.free()

# ------------------------------------------
# Prelude
# ------------------------------------------

comptime S32 = Int32
comptime F32 = Float32
comptime F64 = Float64
comptime Res = Tuple
comptime SInt = Int
comptime Ptr = UnsafePointer
comptime OpaqPtr = OpaquePointer
comptime ReadStreams[dreal: DType] = Ptr[Ptr[SIMD[dreal, 1], READ_EXT], READ_EXT]
comptime MutaStreams[dreal: DType] = Ptr[Ptr[SIMD[dreal, 1], MUTA_EXT], MUTA_EXT]
comptime READ_EXT = ImmutExternalOrigin
comptime MUTA_EXT = MutExternalOrigin

comptime dfaust = get_defined_dtype["FAUST_DTYPE", F32.dtype]()
comptime FaustFloat = SIMD[dfaust, 1]

comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 44_100]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 1024]())

comptime WARMUP_ITERS  = get_defined_int["WARMUP_ITERS", 10_000]()
comptime COMPUTE_ITERS = get_defined_int["COMPUTE_ITERS", 10_000]()
comptime FILL_INPUTS   = get_defined_bool["FILL_INPUTS", False]()

comptime MIN_RUNTIME_SECS: F64 = 0.1
comptime MAX_RUNTIME_SECS: F64 = 60.0

comptime BIT[bit: SInt] = 1 << bit

# ------------------------------------------
# Faust DSP code
# ------------------------------------------

struct mydsp:
    var sample_rate: S32
    var z0: FaustFloat
    def __init__(out dsp):
        dsp.sample_rate = 0
        dsp.z0 = 1.0
    def get_num_inputs(read dsp) -> S32: return 2
    def get_num_outputs(read dsp) -> S32: return 2
    def get_sample_rate(mut dsp) -> S32: return dsp.sample_rate
    def init(mut dsp, sample_rate: S32) -> None: dsp.sample_rate = sample_rate
    def compute[dreal: DType](
        mut dsp, count: S32, inputs: ReadStreams[dreal], outputs: MutaStreams[dreal]
    ) -> None:
        for var i in range(count):
            in0 = SIMD[dreal, 1](inputs[0][i])
            in1 = SIMD[dreal, 1](inputs[1][i])
            mixed: FaustFloat = FaustFloat(0.5) * FaustFloat(in0 + in1)
            dsp.z0 = FaustFloat(0.99) * dsp.z0 + FaustFloat(0.01) * mixed
            outputs[0][i] = SIMD[dreal, 1](dsp.z0)
            outputs[1][i] = SIMD[dreal, 1](mixed - dsp.z0)

# ------------------------------------------
# Testing
# ------------------------------------------

def test_bench__allocation_and_basic_usage() -> None:
    comptime dreal = dfaust
    comptime Real = SIMD[dreal, 1]

    var dsp = mydsp()
    dsp.init(SAMP_RATE)

    var n_ins = dsp.get_num_inputs()
    var n_outs = dsp.get_num_outputs()

    var base, err = make_buffers[dreal](BUFF_SIZE, n_ins, n_outs)
    if err != AllocErr_None:
        print("Critical allocation error! Failed to allocate buffers with code: ", err)
        exit(err)

    var inputs = base.bitcast[Ptr[Real, MUTA_EXT]]()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs[dreal](BUFF_SIZE, inputs, n_ins)

    var report: Report
    try:
        report = measure[dreal](dsp, BUFF_SIZE, inputs, outputs)
    except e:
        free_buffers[dreal](base)
        print("Error in benchmojo.measure[dtype](mydsp)!: ", e)
        exit(1)
        return

    clobber_memory()

    var checksum = checksum_outputs[dreal](outputs, BUFF_SIZE, n_outs)

    print("Display precision to verify correctness:", PRECISION_STRINGS[size_of[dfaust]()/4 - 1])
    print_report(report, n_ins, n_outs, checksum)

    free_buffers[dreal](base)
 
