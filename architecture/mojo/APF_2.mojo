# ==============================================================================
# Faust to Mojo inspect architecture for the benchmark framework.
# Provides the minimal definitions and entry point needed to generate
# low-level code with clear symbols for inspecting the generated compute code.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from help import *
from mem import *
from dsp import *
from gui import *
from meta import *

from std.benchmark import keep, clobber_memory

comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 512]())
comptime COMPUTE_ITERS = S32(get_defined_int["COMPUTE_ITERS", 100]())

def assert_dfaust() -> None: comptime assert dfaust == F32.dtype
comptime _ = assert_dfaust()

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "APF"
# Compilation options: 
#   -a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
# ==============================================================================

comptime dreal: DType = F64.dtype

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
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 1

    @always_inline
    def class_init(mut dsp, read sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, read sample_rate: S32) -> None:
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
    def instance_init(mut dsp, read sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    @always_inline
    def init(mut dsp, read sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    @always_inline
    def get_json(read dsp) -> String:
        return "{\"name\": \"APF\",\"filename\": \"APF.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\",\"library_list\": [\"/usr/local/share/faust/maxmsp.lib\",\"/usr/local/share/faust/maths.lib\",\"/usr/local/share/faust/platform.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"../../tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/../../tests/impulse-tests/dsp\"],\"size\": 60,\"inputs\": 1,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\" },{ \"filename\": \"APF.dsp\" },{ \"maths.lib/author\": \"GRAME\" },{ \"maths.lib/copyright\": \"GRAME\" },{ \"maths.lib/license\": \"LGPL with exception\" },{ \"maths.lib/name\": \"Faust Math Library\" },{ \"maths.lib/version\": \"2.9.0\" },{ \"maxmsp.lib/author\": \"GRAME\" },{ \"maxmsp.lib/copyright\": \"GRAME\" },{ \"maxmsp.lib/license\": \"LGPL with exception\" },{ \"maxmsp.lib/name\": \"MaxMSP compatibility Library\" },{ \"maxmsp.lib/version\": \"1.1.0\" },{ \"name\": \"APF\" },{ \"platform.lib/name\": \"Generic Platform Library\" },{ \"platform.lib/version\": \"1.3.0\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"APF\",\"items\": [ {\"type\": \"hslider\",\"label\": \"Freq\",\"varname\": \"fHslider0\",\"shortname\": \"Freq\",\"address\": \"/APF/Freq\",\"init\": 1000,\"min\": 100,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Q\",\"varname\": \"fHslider1\",\"shortname\": \"Q\",\"address\": \"/APF/Q\",\"init\": 1,\"min\": 0.01,\"max\": 100,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32")
        meta.declare("filename", "APF.dsp")
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
        meta.declare("name", "APF")
        meta.declare("platform.lib/name", "Generic Platform Library")
        meta.declare("platform.lib/version", "1.3.0")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("APF")
        ui.add_horizontal_slider("Freq", dsp.hslider0, FaustFloat(1000.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("Q", dsp.hslider1, FaustFloat(1.0), FaustFloat(0.01), FaustFloat(100.0), FaustFloat(0.01))
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var slow0 = (dsp.const0) * (max(0.0, F64(dsp.hslider0)))
        var slow1 = (0.5) * ((sin(slow0)) / (max(0.001, F64(dsp.hslider1))))
        var slow2 = (1.0) / ((slow1) + (1.0))
        var slow3 = (1.0) - (slow1)
        var slow4 = (2.0) * (cos(slow0))
        var zec0 = Arr[F64, 32](uninitialized=True)
        var rec0_tmp = Arr[F64, 36](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        # Main loop 
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(32))): 
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re0 = S32(32)
            # Recursive loop 0 
            # Pre code 
            var j0_re0 = S32(0)
            comptime dtype0 = f64
            comptime width0 = S32(simd_width_of[dtype0]())
            while j0_re0 <= S32(4) - width0:
                var values = SIMD[dtype0, Int(width0)](dsp.rec0_perm[j0_re0])
                simd_store(rec0_tmp, j0_re0, values)
                j0_re0 = j0_re0 + width0
            # Compute code 
            var i_re0 = S32(0)
            while (i_re0) < (vsize_re0): 
                zec0[i_re0] = (slow4) * (rec0[(i_re0) - (S32(1))])
                rec0[i_re0] = (F64(input0[i_re0])) - ((slow2) * (((slow3) * (rec0[(i_re0) - (S32(2))])) - (zec0[i_re0])))
                i_re0 = (i_re0) + (S32(1))
            # Post code 
            var j1_re0 = S32(0)
            comptime dtype1 = f64
            comptime width1 = S32(simd_width_of[dtype1]())
            while j1_re0 <= S32(4) - width1:
                var values = SIMD[dtype1, Int(width1)](rec0_tmp[(vsize_re0) + (j1_re0)])
                simd_store(dsp.rec0_perm, j1_re0, values)
                j1_re0 = j1_re0 + width1
            # Vectorizable loop 1 
            # Compute code 
            var i_re1 = S32(0)
            comptime dtype2 = dfaust
            comptime width2 = S32(simd_width_of[dtype2]())
            while i_re1 <= vsize_re0 - width2:
                var values = SIMD[dtype2, Int(width2)](FaustFloat((rec0[(i_re1) - (S32(2))]) + ((slow2) * (((slow3) * (rec0[i_re1])) - (zec0[i_re1])))))
                simd_store(output0, i_re1, values)
                i_re1 = i_re1 + width2
            vindex_re0 = (vindex_re0) + (S32(32))
        # Remaining frames 
        if ((vindex_re0) < (count) != 0):
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            # Recursive loop 0 
            # Pre code 
            var j0_re1 = S32(0)
            comptime dtype3 = f64
            comptime width3 = S32(simd_width_of[dtype3]())
            while j0_re1 <= S32(4) - width3:
                var values = SIMD[dtype3, Int(width3)](dsp.rec0_perm[j0_re1])
                simd_store(rec0_tmp, j0_re1, values)
                j0_re1 = j0_re1 + width3
            # Compute code 
            var i_re2 = S32(0)
            while (i_re2) < (vsize_re1): 
                zec0[i_re2] = (slow4) * (rec0[(i_re2) - (S32(1))])
                rec0[i_re2] = (F64(input0[i_re2])) - ((slow2) * (((slow3) * (rec0[(i_re2) - (S32(2))])) - (zec0[i_re2])))
                i_re2 = (i_re2) + (S32(1))
            # Post code 
            var j1_re1 = S32(0)
            comptime dtype4 = f64
            comptime width4 = S32(simd_width_of[dtype4]())
            while j1_re1 <= S32(4) - width4:
                var values = SIMD[dtype4, Int(width4)](rec0_tmp[(vsize_re1) + (j1_re1)])
                simd_store(dsp.rec0_perm, j1_re1, values)
                j1_re1 = j1_re1 + width4
            # Vectorizable loop 1 
            # Compute code 
            var i_re3 = S32(0)
            comptime dtype5 = dfaust
            comptime width5 = S32(simd_width_of[dtype5]())
            while i_re3 <= vsize_re1 - width5:
                var values = SIMD[dtype5, Int(width5)](FaustFloat((rec0[(i_re3) - (S32(2))]) + ((slow2) * (((slow3) * (rec0[i_re3])) - (zec0[i_re3])))))
                simd_store(output0, i_re3, values)
                i_re3 = i_re3 + width5

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application.
# Initializes the dsp object, allocates and intializes the audio buffers and
# calls the inspect function to run the dsp code.
# ==============================================================================

def main() -> None:
    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)
    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()
    var base, err = make_streams[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        dsp.free()
        return
    var ptr = base.unsafe_value()
    var inputs = ptr.bitcast[Ptr[FaustFloat, READ_NOTRK]]().as_immutable()
    var outputs = (ptr + n_ins).bitcast[Ptr[FaustFloat, MUTA_NOTRK]]()
    inspect_compute(dsp[], inputs, outputs)
    ptr.free()
    dsp.free()

@no_inline
@export("inspect_compute")
def inspect_compute(
    mut dsp: mydsp, inputs: ReadStreams, outputs: MutaStreams
) abi("Mojo") -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute(BUFF_SIZE, inputs, outputs)
        clobber_memory()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
