# ==============================================================================
# Faust to Mojo architecture file for the benchmark framework integration.
# Provides the definitons and the main entry point to run the dsp code in
# several batches and print the write the report to `.tab` and `.csv` files 
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from help import *
from mem import *
from bench import *
from dsp import *
from gui import *
from meta import *

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "apf"
# Compilation options: 
#   -a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = Vec[dreal]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var hslider0: FaustFloat
    var hslider1: FaustFloat
    var rec0_perm: Arr[F64, 4]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.hslider0 = 0.0
        dsp.hslider1 = 0.0
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 1

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = (6.283185307179586) / (min(1.92e+05, max(1.0, F64(dsp.sample_rate))))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 1000.0
        dsp.hslider1 = 1.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec0_perm[l0] = 0.0
            l0 = (l0) + (S32(1))

    @always_inline
    def instance_init(mut dsp, imm sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    @always_inline
    def init(mut dsp, imm sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    @always_inline
    def get_json(imm dsp) -> String:
        return "{\"name\": \"apf\",\"filename\": \"apf.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/usr/local/share/faust/maxmsp.lib\",\"/usr/local/share/faust/maths.lib\",\"/usr/local/share/faust/platform.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/_bench/src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/_bench/src\"],\"size\": 60,\"inputs\": 1,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"filename\": \"apf.dsp\" },{ \"maths.lib/author\": \"GRAME\" },{ \"maths.lib/copyright\": \"GRAME\" },{ \"maths.lib/license\": \"LGPL with exception\" },{ \"maths.lib/name\": \"Faust Math Library\" },{ \"maths.lib/version\": \"2.9.0\" },{ \"maxmsp.lib/author\": \"GRAME\" },{ \"maxmsp.lib/copyright\": \"GRAME\" },{ \"maxmsp.lib/license\": \"LGPL with exception\" },{ \"maxmsp.lib/name\": \"MaxMSP compatibility Library\" },{ \"maxmsp.lib/version\": \"1.1.0\" },{ \"name\": \"apf\" },{ \"platform.lib/name\": \"Generic Platform Library\" },{ \"platform.lib/version\": \"1.3.0\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"apf\",\"items\": [ {\"type\": \"hslider\",\"label\": \"Freq\",\"varname\": \"fHslider0\",\"shortname\": \"Freq\",\"address\": \"/apf/Freq\",\"init\": 1000,\"min\": 100,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Q\",\"varname\": \"fHslider1\",\"shortname\": \"Q\",\"address\": \"/apf/Q\",\"init\": 1,\"min\": 0.01,\"max\": 100,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("filename", "apf.dsp")
        meta.declare("maths.lib/author", "GRAME")
        meta.declare("maths.lib/copyright", "GRAME")
        meta.declare("maths.lib/license", "LGPL with exception")
        meta.declare("maths.lib/name", "Faust Math Library")
        meta.declare("maths.lib/version", "2.9.0")
        meta.declare("maxmsp.lib/author", "GRAME")
        meta.declare("maxmsp.lib/copyright", "GRAME")
        meta.declare("maxmsp.lib/license", "LGPL with exception")
        meta.declare("maxmsp.lib/name", "MaxMSP compatibility Library")
        meta.declare("maxmsp.lib/version", "1.1.0")
        meta.declare("name", "apf")
        meta.declare("platform.lib/name", "Generic Platform Library")
        meta.declare("platform.lib/version", "1.3.0")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("apf")
        ui.add_horizontal_slider("Freq", dsp.hslider0, FaustFloat(1000.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("Q", dsp.hslider1, FaustFloat(1.0), FaustFloat(0.01), FaustFloat(100.0), FaustFloat(0.01))
        ui.close_box()

    @always_inline
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        comptime vsize = S32(4)
        comptime hsize = S32(2)
        var vindex = S32(0)
        var end = count - vsize
        var lo: SIMD[dfaust, simd_width_of[f64]()]
        var hi: SIMD[dfaust, simd_width_of[f64]()]
        var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var slow0 = (dsp.const0) * (max(0.0, F64(dsp.hslider0)))
        var slow1 = (0.5) * ((sin(slow0)) / (max(0.001, F64(dsp.hslider1))))
        var slow2 = (1.0) / ((slow1) + (1.0))
        var slow3 = (1.0) - (slow1)
        var slow4 = (2.0) * (cos(slow0))
        var zec0 = Arr[F64, 4](uninitialized=True)
        var rec0_tmp = Arr[F64, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        while vindex <= end:
            var input0 = Ptr(to=input0_ptr[vindex])
            var output0 = Ptr(to=output0_ptr[vindex])
            vstore(rec0_tmp, vload[w64](dsp.rec0_perm))
            vstore(rec0_tmp, vload[w64](dsp.rec0_perm, hsize), hsize)
            comptime for i in range(vsize):
                zec0[i] = (slow4) * (rec0[(i) - (S32(1))])
                rec0[i] = (F64(input0[i])) - ((slow2) * (((slow3) * (rec0[(i) - (S32(2))])) - (zec0[i])))
            vstore(dsp.rec0_perm, vload[w64](rec0_tmp, vsize))
            vstore(dsp.rec0_perm, vload[w64](rec0_tmp, vsize + hsize), hsize)
            lo = ((vload[w64](rec0, - S32(2))) + ((slow2) * (((slow3) * (vload[w64](rec0))) - (vload[w64](zec0))))).cast[dfaust]()
            hi = ((vload[w64](rec0, - S32(2) + hsize)) + ((slow2) * (((slow3) * (vload[w64](rec0, hsize))) - (vload[w64](zec0, hsize))))).cast[dfaust]()
            vstore(output0, lo.join(hi))
            vindex += vsize

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object
# and the user interface, allocates the buffers and runs the benchmark.
# ==============================================================================

def main() raises -> None:
    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_streams[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Panic in main - Critical allocation error: ", err)
        dsp.free()
        return

    var inputs = base.unsafe_value().bitcast[Ptr[FaustFloat, MUT_NOTRK]]()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs(inputs, n_ins)

    warmup(dsp[], inputs, outputs)
    var report = measure(dsp[], inputs, outputs)
    report.checksum = checksum_outputs(outputs, n_outs)
    print_report(report) # the output will be redirected via script

    comptime if WRITE_CSV:
        write_csv(report)

    free_streams[dfaust](base)
    dsp.free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
