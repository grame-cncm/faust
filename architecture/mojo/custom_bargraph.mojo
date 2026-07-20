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
# name: "custom_bargraph"
# Compilation options: 
#   -a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = Vec[dreal]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var entry0: FaustFloat
    var hslider0: FaustFloat
    var hbargraph0: FaustFloat
    var vslider0: FaustFloat
    var vbargraph0: FaustFloat
    var hbargraph1: FaustFloat
    var checkbox0: FaustFloat
    var button0: FaustFloat
    var vbargraph1: FaustFloat
    var sample_rate: S32

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.entry0 = 0.0
        dsp.hslider0 = 0.0
        dsp.hbargraph0 = 0.0
        dsp.vslider0 = 0.0
        dsp.vbargraph0 = 0.0
        dsp.hbargraph1 = 0.0
        dsp.checkbox0 = 0.0
        dsp.button0 = 0.0
        dsp.vbargraph1 = 0.0
        dsp.sample_rate = 0

    @always_inline
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 8

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 1

    @always_inline
    def class_init(mut dsp, read sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, read sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.entry0 = 0.0
        dsp.hslider0 = 0.5
        dsp.vslider0 = 0.25
        dsp.checkbox0 = 0.0
        dsp.button0 = 0.0

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
        return "{\"name\": \"custom_bargraph\",\"filename\": \"custom_bargraph.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/src\"],\"size\": 76,\"inputs\": 1,\"outputs\": 8,\"meta\": [ { \"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"filename\": \"custom_bargraph.dsp\" },{ \"name\": \"custom_bargraph\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"custom_bargraph\",\"items\": [ {\"type\": \"hslider\",\"label\": \"controls/gain_h\",\"varname\": \"fHslider0\",\"shortname\": \"controls_gain_h\",\"address\": \"/custom_bargraph/controls_gain_h\",\"meta\": [{ \"0\": \"\" }],\"init\": 0.5,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"hbargraph\",\"label\": \"meters/b0_hbar\",\"varname\": \"fHbargraph0\",\"shortname\": \"meters_b0_hbar\",\"address\": \"/custom_bargraph/meters_b0_hbar\",\"meta\": [{ \"10\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"vbargraph\",\"label\": \"meters/b1_vbar\",\"varname\": \"fVbargraph0\",\"shortname\": \"meters_b1_vbar\",\"address\": \"/custom_bargraph/meters_b1_vbar\",\"meta\": [{ \"11\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"hbargraph\",\"label\": \"meters/b2_hbar\",\"varname\": \"fHbargraph1\",\"shortname\": \"meters_b2_hbar\",\"address\": \"/custom_bargraph/meters_b2_hbar\",\"meta\": [{ \"12\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"vbargraph\",\"label\": \"meters/b3_vbar\",\"varname\": \"fVbargraph1\",\"shortname\": \"meters_b3_vbar\",\"address\": \"/custom_bargraph/meters_b3_vbar\",\"meta\": [{ \"13\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"vslider\",\"label\": \"controls/gain_v\",\"varname\": \"fVslider0\",\"shortname\": \"controls_gain_v\",\"address\": \"/custom_bargraph/controls_gain_v\",\"meta\": [{ \"1\": \"\" }],\"init\": 0.25,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"controls/bias_n\",\"varname\": \"fEntry0\",\"shortname\": \"controls_bias_n\",\"address\": \"/custom_bargraph/controls_bias_n\",\"meta\": [{ \"2\": \"\" }],\"init\": 0,\"min\": -1,\"max\": 1,\"step\": 0.001},{\"type\": \"checkbox\",\"label\": \"controls/gate_c\",\"varname\": \"fCheckbox0\",\"shortname\": \"controls_gate_c\",\"address\": \"/custom_bargraph/controls_gate_c\",\"meta\": [{ \"3\": \"\" }]},{\"type\": \"button\",\"label\": \"controls/trig_b\",\"varname\": \"fButton0\",\"shortname\": \"controls_trig_b\",\"address\": \"/custom_bargraph/controls_trig_b\",\"meta\": [{ \"4\": \"\" }]}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("filename", "custom_bargraph.dsp")
        meta.declare("name", "custom_bargraph")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("custom_bargraph")
        ui.declare(dsp.hslider0, "0", "")
        ui.add_horizontal_slider("controls/gain_h", dsp.hslider0, FaustFloat(0.5), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.declare(dsp.hbargraph0, "10", "")
        ui.add_horizontal_bargraph("meters/b0_hbar", dsp.hbargraph0, FaustFloat(-2.0), FaustFloat(2.0))
        ui.declare(dsp.vbargraph0, "11", "")
        ui.add_vertical_bargraph("meters/b1_vbar", dsp.vbargraph0, FaustFloat(-2.0), FaustFloat(2.0))
        ui.declare(dsp.hbargraph1, "12", "")
        ui.add_horizontal_bargraph("meters/b2_hbar", dsp.hbargraph1, FaustFloat(-2.0), FaustFloat(2.0))
        ui.declare(dsp.vbargraph1, "13", "")
        ui.add_vertical_bargraph("meters/b3_vbar", dsp.vbargraph1, FaustFloat(-2.0), FaustFloat(2.0))
        ui.declare(dsp.vslider0, "1", "")
        ui.add_vertical_slider("controls/gain_v", dsp.vslider0, FaustFloat(0.25), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.declare(dsp.entry0, "2", "")
        ui.add_num_entry("controls/bias_n", dsp.entry0, FaustFloat(0.0), FaustFloat(-1.0), FaustFloat(1.0), FaustFloat(0.001))
        ui.declare(dsp.checkbox0, "3", "")
        ui.add_check_button("controls/gate_c", dsp.checkbox0)
        ui.declare(dsp.button0, "4", "")
        ui.add_button("controls/trig_b", dsp.button0)
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        var lo: SIMD[dfaust, simd_width_of[f64]()]
        var hi: SIMD[dfaust, simd_width_of[f64]()]
        var var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var output1_ptr = outputs[S32(1)]
        var output2_ptr = outputs[S32(2)]
        var output3_ptr = outputs[S32(3)]
        var output4_ptr = outputs[S32(4)]
        var output5_ptr = outputs[S32(5)]
        var output6_ptr = outputs[S32(6)]
        var output7_ptr = outputs[S32(7)]
        var slow0 = F64(dsp.entry0)
        var slow1 = F64(dsp.hslider0)
        var slow2 = F64(dsp.vslider0)
        var slow3 = (slow1) + (slow2)
        var slow4 = F64(dsp.checkbox0)
        var slow5 = F64(dsp.button0)
        var slow6 = (slow4) + (slow5)
        var slow7 = (slow1) * (slow2)
        var slow8 = (slow4) + (1.0)
        var slow9 = (slow5) + (0.25)
        var slow10 = (slow5) + ((slow3) + (slow4))
        # Main loop 
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(4))): 
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var output1 = Ptr(to=output1_ptr[vindex_re0])
            var output2 = Ptr(to=output2_ptr[vindex_re0])
            var output3 = Ptr(to=output3_ptr[vindex_re0])
            var output4 = Ptr(to=output4_ptr[vindex_re0])
            var output5 = Ptr(to=output5_ptr[vindex_re0])
            var output6 = Ptr(to=output6_ptr[vindex_re0])
            var output7 = Ptr(to=output7_ptr[vindex_re0])
            comptime vsize_re0 = S32(4)
            # Vectorizable loop 0 
            # Compute code 
            var i_re0 = S32(0)
            var value0 = ((slow0) + ((slow1) * ((vload(input0)).cast[f64]()))).cast[dfaust]()
            dsp.hbargraph0 = value0[wfaust - 1]
            vstore(output0, i_re0, value0)
            # Vectorizable loop 1 
            # Compute code 
            var i_re1 = S32(0)
            var value1 = (((slow2) * ((vload(input0)).cast[f64]())) - (slow0)).cast[dfaust]()
            dsp.vbargraph0 = value1[wfaust - 1]
            vstore(output1, i_re1, value1)
            # Vectorizable loop 2 
            # Compute code 
            var i_re2 = S32(0)
            var value2 = ((slow3) * ((vload(input0)).cast[f64]())).cast[dfaust]()
            dsp.hbargraph1 = value2[wfaust - 1]
            vstore(output2, i_re2, value2)
            # Vectorizable loop 3 
            # Compute code 
            var i_re3 = S32(0)
            var value3 = ((slow6) * ((vload(input0)).cast[f64]())).cast[dfaust]()
            dsp.vbargraph1 = value3[wfaust - 1]
            vstore(output3, i_re3, value3)
            # Vectorizable loop 4 
            # Compute code 
            var i_re4 = S32(0)
            lo = ((slow7) * ((slow0) + ((vload[w64](input0)).cast[f64]()))).cast[dfaust]()
            hi = ((slow7) * ((slow0) + ((vload[w64](input0, S32(w64))).cast[f64]()))).cast[dfaust]()
            var value4 = lo.join(hi)
            vstore(output4, S32(0), value4)
            # Vectorizable loop 5 
            # Compute code 
            var i_re5 = S32(0)
            lo = ((slow8) * (((vload[w64](input0)).cast[f64]()) - (slow0))).cast[dfaust]()
            hi = ((slow8) * (((vload[w64](input0, S32(w64))).cast[f64]()) - (slow0))).cast[dfaust]()
            var value5 = lo.join(hi)
            vstore(output5, S32(0), value5)
            # Vectorizable loop 6 
            # Compute code 
            var i_re6 = S32(0)
            lo = ((slow9) * ((vload[w64](input0)).cast[f64]())).cast[dfaust]()
            hi = ((slow9) * ((vload[w64](input0, S32(w64))).cast[f64]())).cast[dfaust]()
            var value6 = lo.join(hi)
            vstore(output6, S32(0), value6)
            # Vectorizable loop 7 
            # Compute code 
            var i_re7 = S32(0)
            lo = ((slow10) * ((vload[w64](input0)).cast[f64]())).cast[dfaust]()
            hi = ((slow10) * ((vload[w64](input0, S32(w64))).cast[f64]())).cast[dfaust]()
            var value7 = lo.join(hi)
            vstore(output7, S32(0), value7)
            vindex_re0 = (vindex_re0) + (S32(4))

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
