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
# name: "bargraph"
# Compilation options: 
#   
#   -a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo 
#   -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single 
#   -ftz 0
# ==============================================================================

comptime dreal = f32
comptime dreal_width = S32(simd_width_of[dreal]())

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
        return "{\"name\": \"bargraph\",\"filename\": \"bargraph.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0\",\"include_pathnames\": [\"/Users/manuelfarzini/personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/src\",\"/Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/src\"],\"size\": 40,\"inputs\": 1,\"outputs\": 8,\"meta\": [ { \"compile_options\": \"-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0\" },{ \"filename\": \"bargraph.dsp\" },{ \"name\": \"bargraph\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"bargraph\",\"items\": [ {\"type\": \"hslider\",\"label\": \"controls/gain_h\",\"varname\": \"fHslider0\",\"shortname\": \"controls_gain_h\",\"address\": \"/bargraph/controls_gain_h\",\"meta\": [{ \"0\": \"\" }],\"init\": 0.5,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"hbargraph\",\"label\": \"meters/b0_hbar\",\"varname\": \"fHbargraph0\",\"shortname\": \"meters_b0_hbar\",\"address\": \"/bargraph/meters_b0_hbar\",\"meta\": [{ \"10\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"vbargraph\",\"label\": \"meters/b1_vbar\",\"varname\": \"fVbargraph0\",\"shortname\": \"meters_b1_vbar\",\"address\": \"/bargraph/meters_b1_vbar\",\"meta\": [{ \"11\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"hbargraph\",\"label\": \"meters/b2_hbar\",\"varname\": \"fHbargraph1\",\"shortname\": \"meters_b2_hbar\",\"address\": \"/bargraph/meters_b2_hbar\",\"meta\": [{ \"12\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"vbargraph\",\"label\": \"meters/b3_vbar\",\"varname\": \"fVbargraph1\",\"shortname\": \"meters_b3_vbar\",\"address\": \"/bargraph/meters_b3_vbar\",\"meta\": [{ \"13\": \"\" }],\"min\": -2,\"max\": 2},{\"type\": \"vslider\",\"label\": \"controls/gain_v\",\"varname\": \"fVslider0\",\"shortname\": \"controls_gain_v\",\"address\": \"/bargraph/controls_gain_v\",\"meta\": [{ \"1\": \"\" }],\"init\": 0.25,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"controls/bias_n\",\"varname\": \"fEntry0\",\"shortname\": \"controls_bias_n\",\"address\": \"/bargraph/controls_bias_n\",\"meta\": [{ \"2\": \"\" }],\"init\": 0,\"min\": -1,\"max\": 1,\"step\": 0.001},{\"type\": \"checkbox\",\"label\": \"controls/gate_c\",\"varname\": \"fCheckbox0\",\"shortname\": \"controls_gate_c\",\"address\": \"/bargraph/controls_gate_c\",\"meta\": [{ \"3\": \"\" }]},{\"type\": \"button\",\"label\": \"controls/trig_b\",\"varname\": \"fButton0\",\"shortname\": \"controls_trig_b\",\"address\": \"/bargraph/controls_trig_b\",\"meta\": [{ \"4\": \"\" }]}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0")
        meta.declare("filename", "bargraph.dsp")
        meta.declare("name", "bargraph")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("bargraph")
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
        var input0 = inputs[S32(0)]
        var output0 = outputs[S32(0)]
        var output1 = outputs[S32(1)]
        var output2 = outputs[S32(2)]
        var output3 = outputs[S32(3)]
        var output4 = outputs[S32(4)]
        var output5 = outputs[S32(5)]
        var output6 = outputs[S32(6)]
        var output7 = outputs[S32(7)]
        var slow0 = F32(dsp.entry0)
        var slow1 = F32(dsp.hslider0)
        var slow2 = F32(dsp.vslider0)
        var slow3 = (slow1) + (slow2)
        var slow4 = F32(dsp.checkbox0)
        var slow5 = F32(dsp.button0)
        var slow6 = (slow4) + (slow5)
        var slow7 = (slow1) * (slow2)
        var slow8 = (slow4) + (F32(1.0))
        var slow9 = (slow5) + (F32(0.25))
        var slow10 = (slow5) + ((slow3) + (slow4))
        for var i0 in range(S32(0), count):
            var temp0 = F32(input0[i0])
            dsp.hbargraph0 = FaustFloat((slow0) + ((slow1) * (temp0)))
            output0[i0] = FaustFloat(F32(dsp.hbargraph0))
            dsp.vbargraph0 = FaustFloat(((slow2) * (temp0)) - (slow0))
            output1[i0] = FaustFloat(F32(dsp.vbargraph0))
            dsp.hbargraph1 = FaustFloat((slow3) * (temp0))
            output2[i0] = FaustFloat(F32(dsp.hbargraph1))
            dsp.vbargraph1 = FaustFloat((slow6) * (temp0))
            output3[i0] = FaustFloat(F32(dsp.vbargraph1))
            output4[i0] = FaustFloat((slow7) * ((slow0) + (temp0)))
            output5[i0] = FaustFloat((slow8) * ((temp0) - (slow0)))
            output6[i0] = FaustFloat((slow9) * (temp0))
            output7[i0] = FaustFloat((slow10) * (temp0))

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

    var inputs = base.unsafe_value().bitcast[Ptr[FaustFloat, MUTA_NOTRK]]()
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
