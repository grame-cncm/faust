# ==============================================================================
# Faust to Mojo inspect architecture for the benchmark framework.
# Provides the minimal definitions and entry point needed to generate
# low-level code with clear symbols for inspecting the generated compute code.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from std.benchmark import keep, clobber_memory

from conf import *
from help import *
from mem import *
from dsp import *
from gui import *
from meta import *

comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 512]())
comptime COMPUTE_ITERS = S32(get_defined_int["COMPUTE_ITERS", 100]())

def assert_dfaust() -> None: comptime assert dfaust == F32.dtype
comptime _ = assert_dfaust()

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "cubic_mini_01"
# Compilation options: 
#   -a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
# ==============================================================================

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var hslider0: FaustFloat
    var sample_rate: S32

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.hslider0 = 0.0
        dsp.sample_rate = 0

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 2

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 1

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 0.5

    @always_inline
    def instance_clear(mut dsp) -> None:
        pass

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
        return "{\"name\": \"cubic_mini_01\",\"filename\": \"cubic_mini_01.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"../_bench/src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/../_bench/src\"],\"size\": 12,\"inputs\": 1,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\" },{ \"filename\": \"cubic_mini_01.dsp\" },{ \"name\": \"cubic_mini_01\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"cubic_mini_01\",\"items\": [ {\"type\": \"hslider\",\"label\": \"drive\",\"varname\": \"fHslider0\",\"shortname\": \"drive\",\"address\": \"/cubic_mini_01/drive\",\"init\": 0.5,\"min\": 0,\"max\": 2,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32")
        meta.declare("filename", "cubic_mini_01.dsp")
        meta.declare("name", "cubic_mini_01")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("cubic_mini_01")
        ui.add_horizontal_slider("drive", dsp.hslider0, FaustFloat(0.5), FaustFloat(0.0), FaustFloat(2.0), FaustFloat(0.01))
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> None:
        var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var output1_ptr = outputs[S32(1)]
        var slow0 = F64(dsp.hslider0)
        var zec0 = Arr[F64, 32](uninitialized=True)
        # Main loop 
        vindex_re0 = S32(0)
        while ((vindex_re0) <= ((count) - (S32(32)))): 
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var output1 = Ptr(to=output1_ptr[vindex_re0])
            var vsize_re0 = S32(32)
            # Vectorizable loop 0 
            # Compute code 
            var i_re0 = S32(0)
            while ((i_re0) < (vsize_re0)): 
                zec0[i_re0] = (F64(input0[i_re0])) * ((1.0) - ((slow0) * (pow_unrolled[2](F64(input0[i_re0])))))
                i_re0 = (i_re0) + (S32(1))
            # Vectorizable loop 1 
            # Compute code 
            var i_re1 = S32(0)
            while ((i_re1) < (vsize_re0)): 
                output0[i_re1] = FaustFloat(zec0[i_re1])
                i_re1 = (i_re1) + (S32(1))
            # Vectorizable loop 2 
            # Compute code 
            var i_re2 = S32(0)
            while ((i_re2) < (vsize_re0)): 
                output1[i_re2] = FaustFloat(zec0[i_re2])
                i_re2 = (i_re2) + (S32(1))
            vindex_re0 = (vindex_re0) + (S32(32))
        # Remaining frames 
        if ((vindex_re0) < (count) != 0):
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var output1 = Ptr(to=output1_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            # Vectorizable loop 0 
            # Compute code 
            var i_re3 = S32(0)
            while ((i_re3) < (vsize_re1)): 
                zec0[i_re3] = (F64(input0[i_re3])) * ((1.0) - ((slow0) * (pow_unrolled[2](F64(input0[i_re3])))))
                i_re3 = (i_re3) + (S32(1))
            # Vectorizable loop 1 
            # Compute code 
            var i_re4 = S32(0)
            while ((i_re4) < (vsize_re1)): 
                output0[i_re4] = FaustFloat(zec0[i_re4])
                i_re4 = (i_re4) + (S32(1))
            # Vectorizable loop 2 
            # Compute code 
            var i_re5 = S32(0)
            while ((i_re5) < (vsize_re1)): 
                output1[i_re5] = FaustFloat(zec0[i_re5])
                i_re5 = (i_re5) + (S32(1))
 
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
    var inputs = ptr.bitcast[Ptr[FaustFloat, IMM_NOTRK]]().as_immutable()
    var outputs = (ptr + n_ins).bitcast[Ptr[FaustFloat, MUT_NOTRK]]()
    inspect_compute(dsp[], inputs, outputs)
    ptr.free()
    dsp.free()

@no_inline
@export("inspect_compute")
def inspect_compute(
    mut dsp: mydsp, inputs: ImmStreams, outputs: MutStreams
) abi("Mojo") -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute(BUFF_SIZE, inputs, outputs)
        clobber_memory()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
