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
# name: "bargraph"
# Compilation options: 
#   -a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = S32(simd_width_of[dreal]())
comptime Real = Scalar[dreal]
comptime RVec = Vec[dreal]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var vbargraph0: FaustFloat
    var vbargraph1: FaustFloat
    var vbargraph2: FaustFloat
    var vbargraph3: FaustFloat
    var vbargraph4: FaustFloat
    var vbargraph5: FaustFloat
    var vbargraph6: FaustFloat
    var vbargraph7: FaustFloat
    var vbargraph8: FaustFloat
    var vbargraph9: FaustFloat
    var sample_rate: S32

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.vbargraph0 = 0.0
        dsp.vbargraph1 = 0.0
        dsp.vbargraph2 = 0.0
        dsp.vbargraph3 = 0.0
        dsp.vbargraph4 = 0.0
        dsp.vbargraph5 = 0.0
        dsp.vbargraph6 = 0.0
        dsp.vbargraph7 = 0.0
        dsp.vbargraph8 = 0.0
        dsp.vbargraph9 = 0.0
        dsp.sample_rate = 0

    @always_inline
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 10

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, read sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, read sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        pass

    @always_inline
    def instance_clear(mut dsp) -> None:
        pass

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
        return "{\"name\": \"bargraph\",\"filename\": \"bargraph.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 84,\"inputs\": 0,\"outputs\": 10,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"filename\": \"bargraph.dsp\" },{ \"name\": \"bargraph\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"bargraph\",\"items\": [ {\"type\": \"vbargraph\",\"label\": \"bar0\",\"varname\": \"fVbargraph5\",\"shortname\": \"bar0\",\"address\": \"/bargraph/bar0\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar1\",\"varname\": \"fVbargraph6\",\"shortname\": \"bar1\",\"address\": \"/bargraph/bar1\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar2\",\"varname\": \"fVbargraph7\",\"shortname\": \"bar2\",\"address\": \"/bargraph/bar2\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar3\",\"varname\": \"fVbargraph8\",\"shortname\": \"bar3\",\"address\": \"/bargraph/bar3\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar4\",\"varname\": \"fVbargraph9\",\"shortname\": \"bar4\",\"address\": \"/bargraph/bar4\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo0\",\"varname\": \"fVbargraph0\",\"shortname\": \"foo0\",\"address\": \"/bargraph/foo0\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo1\",\"varname\": \"fVbargraph1\",\"shortname\": \"foo1\",\"address\": \"/bargraph/foo1\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo2\",\"varname\": \"fVbargraph2\",\"shortname\": \"foo2\",\"address\": \"/bargraph/foo2\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo3\",\"varname\": \"fVbargraph3\",\"shortname\": \"foo3\",\"address\": \"/bargraph/foo3\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo4\",\"varname\": \"fVbargraph4\",\"shortname\": \"foo4\",\"address\": \"/bargraph/foo4\",\"min\": 0,\"max\": 10}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("filename", "bargraph.dsp")
        meta.declare("name", "bargraph")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("bargraph")
        ui.add_vertical_bargraph("bar0", dsp.vbargraph5, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("bar1", dsp.vbargraph6, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("bar2", dsp.vbargraph7, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("bar3", dsp.vbargraph8, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("bar4", dsp.vbargraph9, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("foo0", dsp.vbargraph0, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("foo1", dsp.vbargraph1, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("foo2", dsp.vbargraph2, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("foo3", dsp.vbargraph3, FaustFloat(0.0), FaustFloat(10.0))
        ui.add_vertical_bargraph("foo4", dsp.vbargraph4, FaustFloat(0.0), FaustFloat(10.0))
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var output0_ptr = outputs[S32(0)]
        var output1_ptr = outputs[S32(1)]
        var output2_ptr = outputs[S32(2)]
        var output3_ptr = outputs[S32(3)]
        var output4_ptr = outputs[S32(4)]
        var output5_ptr = outputs[S32(5)]
        var output6_ptr = outputs[S32(6)]
        var output7_ptr = outputs[S32(7)]
        var output8_ptr = outputs[S32(8)]
        var output9_ptr = outputs[S32(9)]
        dsp.vbargraph0 = FaustFloat(0.0)
        var slow0 = F64(dsp.vbargraph0)
        dsp.vbargraph1 = FaustFloat(10.0)
        var slow1 = F64(dsp.vbargraph1)
        dsp.vbargraph2 = FaustFloat(20.0)
        var slow2 = F64(dsp.vbargraph2)
        dsp.vbargraph3 = FaustFloat(30.0)
        var slow3 = F64(dsp.vbargraph3)
        dsp.vbargraph4 = FaustFloat(40.0)
        var slow4 = F64(dsp.vbargraph4)
        dsp.vbargraph5 = FaustFloat(0.0)
        var slow5 = F64(dsp.vbargraph5)
        dsp.vbargraph6 = FaustFloat(10.5)
        var slow6 = F64(dsp.vbargraph6)
        dsp.vbargraph7 = FaustFloat(21.0)
        var slow7 = F64(dsp.vbargraph7)
        dsp.vbargraph8 = FaustFloat(31.5)
        var slow8 = F64(dsp.vbargraph8)
        dsp.vbargraph9 = FaustFloat(42.0)
        var slow9 = F64(dsp.vbargraph9)
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(4))): 
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var output1 = Ptr(to=output1_ptr[vindex_re0])
            var output2 = Ptr(to=output2_ptr[vindex_re0])
            var output3 = Ptr(to=output3_ptr[vindex_re0])
            var output4 = Ptr(to=output4_ptr[vindex_re0])
            var output5 = Ptr(to=output5_ptr[vindex_re0])
            var output6 = Ptr(to=output6_ptr[vindex_re0])
            var output7 = Ptr(to=output7_ptr[vindex_re0])
            var output8 = Ptr(to=output8_ptr[vindex_re0])
            var output9 = Ptr(to=output9_ptr[vindex_re0])
            var vsize_re0 = S32(4)
            var i_re0 = S32(0)
            while i_re0 <= vsize_re0 - wfaust:
                var values0 = (slow0).cast[dfaust]()
                simd_store[SInt(wfaust)](output0, i_re0, values0)
                i_re0 = i_re0 + wfaust
            var i_re1 = S32(0)
            while i_re1 <= vsize_re0 - wfaust:
                var values1 = (slow1).cast[dfaust]()
                simd_store[SInt(wfaust)](output1, i_re1, values1)
                i_re1 = i_re1 + wfaust
            var i_re2 = S32(0)
            while i_re2 <= vsize_re0 - wfaust:
                var values2 = (slow2).cast[dfaust]()
                simd_store[SInt(wfaust)](output2, i_re2, values2)
                i_re2 = i_re2 + wfaust
            var i_re3 = S32(0)
            while i_re3 <= vsize_re0 - wfaust:
                var values3 = (slow3).cast[dfaust]()
                simd_store[SInt(wfaust)](output3, i_re3, values3)
                i_re3 = i_re3 + wfaust
            var i_re4 = S32(0)
            while i_re4 <= vsize_re0 - wfaust:
                var values4 = (slow4).cast[dfaust]()
                simd_store[SInt(wfaust)](output4, i_re4, values4)
                i_re4 = i_re4 + wfaust
            var i_re5 = S32(0)
            while i_re5 <= vsize_re0 - wfaust:
                var values5 = (slow5).cast[dfaust]()
                simd_store[SInt(wfaust)](output5, i_re5, values5)
                i_re5 = i_re5 + wfaust
            var i_re6 = S32(0)
            while i_re6 <= vsize_re0 - wfaust:
                var values6 = (slow6).cast[dfaust]()
                simd_store[SInt(wfaust)](output6, i_re6, values6)
                i_re6 = i_re6 + wfaust
            var i_re7 = S32(0)
            while i_re7 <= vsize_re0 - wfaust:
                var values7 = (slow7).cast[dfaust]()
                simd_store[SInt(wfaust)](output7, i_re7, values7)
                i_re7 = i_re7 + wfaust
            var i_re8 = S32(0)
            while i_re8 <= vsize_re0 - wfaust:
                var values8 = (slow8).cast[dfaust]()
                simd_store[SInt(wfaust)](output8, i_re8, values8)
                i_re8 = i_re8 + wfaust
            var i_re9 = S32(0)
            while i_re9 <= vsize_re0 - wfaust:
                var values9 = (slow9).cast[dfaust]()
                simd_store[SInt(wfaust)](output9, i_re9, values9)
                i_re9 = i_re9 + wfaust
            vindex_re0 = (vindex_re0) + (S32(4))

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
