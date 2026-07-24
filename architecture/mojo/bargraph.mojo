# ==============================================================================
# Faust to Mojo impulse architecture for the impulse-tests integration.
# Provides the definitions and the main entry point to run the dsp, and print
# the samples to stdout. The impulse-tests framework will generate the impulse
# responses redirecting the output to the `.ir` files.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from mem import *
from dsp import *
from gui import *
from meta import *
from help import *
from test.impulse import *
from gui.control import ControlGui

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "bargraph"
# Compilation options: 
#   -a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = SIMD[dreal, simd_width_of[dreal]()]

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
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 10

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        pass

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
        return "{\"name\": \"bargraph\",\"filename\": \"bargraph.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/src\"],\"size\": 84,\"inputs\": 0,\"outputs\": 10,\"meta\": [ { \"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"filename\": \"bargraph.dsp\" },{ \"name\": \"bargraph\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"bargraph\",\"items\": [ {\"type\": \"vbargraph\",\"label\": \"bar0\",\"varname\": \"fVbargraph5\",\"shortname\": \"bar0\",\"address\": \"/bargraph/bar0\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar1\",\"varname\": \"fVbargraph6\",\"shortname\": \"bar1\",\"address\": \"/bargraph/bar1\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar2\",\"varname\": \"fVbargraph7\",\"shortname\": \"bar2\",\"address\": \"/bargraph/bar2\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar3\",\"varname\": \"fVbargraph8\",\"shortname\": \"bar3\",\"address\": \"/bargraph/bar3\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"bar4\",\"varname\": \"fVbargraph9\",\"shortname\": \"bar4\",\"address\": \"/bargraph/bar4\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo0\",\"varname\": \"fVbargraph0\",\"shortname\": \"foo0\",\"address\": \"/bargraph/foo0\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo1\",\"varname\": \"fVbargraph1\",\"shortname\": \"foo1\",\"address\": \"/bargraph/foo1\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo2\",\"varname\": \"fVbargraph2\",\"shortname\": \"foo2\",\"address\": \"/bargraph/foo2\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo3\",\"varname\": \"fVbargraph3\",\"shortname\": \"foo3\",\"address\": \"/bargraph/foo3\",\"min\": 0,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"foo4\",\"varname\": \"fVbargraph4\",\"shortname\": \"foo4\",\"address\": \"/bargraph/foo4\",\"min\": 0,\"max\": 10}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
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
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        comptime vsize = S32(simd_width_of[f32]())
        comptime wsize = S32(simd_width_of[f64]())
        comptime W = simd_width_of[f64]()
        var vindex = S32(0)
        var end = count - vsize
        var lo: SIMD[dfaust, simd_width_of[f64]()]
        var hi: SIMD[dfaust, simd_width_of[f64]()]
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
        while vindex <= end:
            var output0 = Ptr(to=output0_ptr[vindex])
            var output1 = Ptr(to=output1_ptr[vindex])
            var output2 = Ptr(to=output2_ptr[vindex])
            var output3 = Ptr(to=output3_ptr[vindex])
            var output4 = Ptr(to=output4_ptr[vindex])
            var output5 = Ptr(to=output5_ptr[vindex])
            var output6 = Ptr(to=output6_ptr[vindex])
            var output7 = Ptr(to=output7_ptr[vindex])
            var output8 = Ptr(to=output8_ptr[vindex])
            var output9 = Ptr(to=output9_ptr[vindex])
            vstore[wfaust](output0, (slow0).cast[dfaust]())
            vstore[wfaust](output1, (slow1).cast[dfaust]())
            vstore[wfaust](output2, (slow2).cast[dfaust]())
            vstore[wfaust](output3, (slow3).cast[dfaust]())
            vstore[wfaust](output4, (slow4).cast[dfaust]())
            vstore[wfaust](output5, (slow5).cast[dfaust]())
            vstore[wfaust](output6, (slow6).cast[dfaust]())
            vstore[wfaust](output7, (slow7).cast[dfaust]())
            vstore[wfaust](output8, (slow8).cast[dfaust]())
            vstore[wfaust](output9, (slow9).cast[dfaust]())
            vindex += vsize

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object,
# initializes the user interface and calls the dsp runner.
# ==============================================================================

def main() raises -> None:
    nbsamples = S32(60_000)
    dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    ctrl_gui = ControlGui()
    dsp[].init(SAMP_RATE)
    dsp[].build_user_interface(ctrl_gui)
    print_header(dsp[], nbsamples)
    run_dsp(dsp, ctrl_gui, nbsamples//4)
    dsp.free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
