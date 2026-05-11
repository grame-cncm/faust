from conf import *
from help import *
from mem import *
from bench import *
from dsp import *
from gui import *
from meta import *

# ------------------------------------------------------------------------------
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "hello_sine"
# Compilation options: 
#   -a ./arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn HelloSine 
#   -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
# ------------------------------------------------------------------------------

@fieldwise_init
struct HelloSine(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F32
    var hslider0: FaustFloat
    var rec0: Arr[F32, 2]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.hslider0 = 0.0
        dsp.rec0 = Arr[F32, 2](fill=0.0)

    @always_inline
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = (1.0) / (min(1.92e+05, max(1.0, F32(dsp.sample_rate))))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 440.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while ((l0) < (S32(2))): 
            dsp.rec0[l0] = 0.0
            l0 = (l0) + (S32(1))

    @always_inline
    def instance_init(mut dsp, sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    @always_inline
    def init(mut dsp, sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    @always_inline
    def get_json(read dsp) -> String:
        return "{\"name\": \"hello_sine\",\"filename\": \"hello_sine.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a ./arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn HelloSine -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0\",\"library_list\": [\"/usr/local/share/faust/stdfaust.lib\",\"/usr/local/share/faust/maths.lib\",\"/usr/local/share/faust/platform.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/_bench/src\"],\"size\": 20,\"inputs\": 0,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a ./arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn HelloSine -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0\" },{ \"filename\": \"hello_sine.dsp\" },{ \"maths.lib/author\": \"GRAME\" },{ \"maths.lib/copyright\": \"GRAME\" },{ \"maths.lib/license\": \"LGPL with exception\" },{ \"maths.lib/name\": \"Faust Math Library\" },{ \"maths.lib/version\": \"2.9.0\" },{ \"name\": \"hello_sine\" },{ \"platform.lib/name\": \"Generic Platform Library\" },{ \"platform.lib/version\": \"1.3.0\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"hello_sine\",\"items\": [ {\"type\": \"hslider\",\"label\": \"freq\",\"varname\": \"fHslider0\",\"shortname\": \"freq\",\"address\": \"/hello_sine/freq\",\"init\": 440,\"min\": 20,\"max\": 2000,\"step\": 1}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a ./arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn HelloSine -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0")
        meta.declare("filename", "hello_sine.dsp")
        meta.declare("maths.lib/author", "GRAME")
        meta.declare("maths.lib/copyright", "GRAME")
        meta.declare("maths.lib/license", "LGPL with exception")
        meta.declare("maths.lib/name", "Faust Math Library")
        meta.declare("maths.lib/version", "2.9.0")
        meta.declare("name", "hello_sine")
        meta.declare("platform.lib/name", "Generic Platform Library")
        meta.declare("platform.lib/version", "1.3.0")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("hello_sine")
        ui.add_horizontal_slider("freq", dsp.hslider0, FaustFloat(440.0), FaustFloat(20.0), FaustFloat(2000.0), FaustFloat(1.0))
        ui.close_box()

    @always_inline
    def compute[dreal: DType](
        mut dsp,
        var count:      S32,
        var inputs:     ReadStreams[dreal],
        var outputs:    MutaStreams[dreal]
    ) -> None:
        var output0 = outputs[S32(0)]
        var slow0 = (dsp.const0) * (F32(dsp.hslider0))
        for var i0 in range(S32(0), count):
            dsp.rec0[S32(0)] = (slow0) + ((dsp.rec0[S32(1)]) - (F32(S32((slow0) + (dsp.rec0[S32(1)])))))
            output0[i0] = SIMD[dreal, 1](sin((6.2831855) * (dsp.rec0[S32(0)])))
            dsp.rec0[S32(1)] = dsp.rec0[S32(0)]


def main() raises -> None:
    comptime dreal = dfaust
    comptime Real = SIMD[dreal, 1]

    var dsp = alloc[HelloSine](1)
    dsp[] = HelloSine()
    dsp[].init(SAMP_RATE)

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_buffers[dreal](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Critical allocation error: ", err)
        dsp.free()
        return

    var inputs = base.bitcast[Ptr[Real, MUTA_EXT]]()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs[dreal](inputs, n_ins)

    warmup[dreal](dsp[], inputs, outputs)
    var report = measure[dreal](dsp[], inputs, outputs)
    report.checksum = checksum_outputs[dreal](outputs, n_outs)
    print_report(report) # the output will be redirected via script
    write_csv(report)

    free_buffers[dreal](base)
    dsp.free()
