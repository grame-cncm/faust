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
# name: "volterra_mini_99"
# Compilation options: 
#   -a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0
# ==============================================================================

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var hslider0: FaustFloat
    var i_vec0: Arr[S32, 2]
    var hslider1: FaustFloat
    var const2: F64
    var hslider2: FaustFloat
    var const3: F64
    var rec3: Arr[F64, 2]
    var vec1: Arr[F64, 2]
    var hslider3: FaustFloat
    var rec4: Arr[F64, 2]
    var vec2: Arr[F64, 2]
    var const4: F64
    var iota0: S32
    var vec3: Arr[F64, 4096]
    var vec4: Arr[F64, 4096]
    var rec2: Arr[F64, 2]
    var rec1: Arr[F64, 2]
    var rec0: Arr[F64, 2]
    var rec7: Arr[F64, 2]
    var rec6: Arr[F64, 2]
    var rec5: Arr[F64, 2]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.hslider0 = 0.0
        dsp.i_vec0 = Arr[S32, 2](fill=0)
        dsp.hslider1 = 0.0
        dsp.const2 = 0.0
        dsp.hslider2 = 0.0
        dsp.const3 = 0.0
        dsp.rec3 = Arr[F64, 2](fill=0.0)
        dsp.vec1 = Arr[F64, 2](fill=0.0)
        dsp.hslider3 = 0.0
        dsp.rec4 = Arr[F64, 2](fill=0.0)
        dsp.vec2 = Arr[F64, 2](fill=0.0)
        dsp.const4 = 0.0
        dsp.iota0 = 0
        dsp.vec3 = Arr[F64, 4096](fill=0.0)
        dsp.vec4 = Arr[F64, 4096](fill=0.0)
        dsp.rec2 = Arr[F64, 2](fill=0.0)
        dsp.rec1 = Arr[F64, 2](fill=0.0)
        dsp.rec0 = Arr[F64, 2](fill=0.0)
        dsp.rec7 = Arr[F64, 2](fill=0.0)
        dsp.rec6 = Arr[F64, 2](fill=0.0)
        dsp.rec5 = Arr[F64, 2](fill=0.0)

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(1.92e+05, max(1.0, F64(dsp.sample_rate)))
        dsp.const1 = (6.283185307179586) / (dsp.const0)
        dsp.const2 = (0.25) * (dsp.const0)
        dsp.const3 = (1.0) / (dsp.const0)
        dsp.const4 = (0.5) * (dsp.const0)

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 700.0
        dsp.hslider1 = 0.5
        dsp.hslider2 = 440.0
        dsp.hslider3 = 2.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while ((l0) < (S32(2))): 
            dsp.i_vec0[l0] = S32(0)
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while ((l1) < (S32(2))): 
            dsp.rec3[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while ((l2) < (S32(2))): 
            dsp.vec1[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while ((l3) < (S32(2))): 
            dsp.rec4[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while ((l4) < (S32(2))): 
            dsp.vec2[l4] = 0.0
            l4 = (l4) + (S32(1))
        dsp.iota0 = S32(0)
        var l5 = S32(0)
        while ((l5) < (S32(4096))): 
            dsp.vec3[l5] = 0.0
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while ((l6) < (S32(4096))): 
            dsp.vec4[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while ((l7) < (S32(2))): 
            dsp.rec2[l7] = 0.0
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while ((l8) < (S32(2))): 
            dsp.rec1[l8] = 0.0
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while ((l9) < (S32(2))): 
            dsp.rec0[l9] = 0.0
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while ((l10) < (S32(2))): 
            dsp.rec7[l10] = 0.0
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while ((l11) < (S32(2))): 
            dsp.rec6[l11] = 0.0
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while ((l12) < (S32(2))): 
            dsp.rec5[l12] = 0.0
            l12 = (l12) + (S32(1))

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
        return "{\"name\": \"volterra_mini_99\",\"filename\": \"volterra_mini_99.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/music.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"../_bench/src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/../_bench/src\"],\"size\": 65784,\"inputs\": 0,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0\" },{ \"filename\": \"volterra_mini_99.dsp\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"volterra_mini_99\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"volterra_mini_99\",\"items\": [ {\"type\": \"hslider\",\"label\": \"delta\",\"varname\": \"fHslider3\",\"shortname\": \"delta\",\"address\": \"/volterra_mini_99/delta\",\"init\": 2,\"min\": 0,\"max\": 6,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"freq carre\",\"varname\": \"fHslider2\",\"shortname\": \"freq_carre\",\"address\": \"/volterra_mini_99/freq_carre\",\"init\": 440,\"min\": 20,\"max\": 8000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"freq\",\"varname\": \"fHslider0\",\"shortname\": \"freq\",\"address\": \"/volterra_mini_99/freq\",\"meta\": [{ \"unit\": \"Hz\" }],\"init\": 700,\"min\": 1,\"max\": 20000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"level\",\"varname\": \"fHslider1\",\"shortname\": \"level\",\"address\": \"/volterra_mini_99/level\",\"init\": 0.5,\"min\": 0,\"max\": 1,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0")
        meta.declare("filename", "volterra_mini_99.dsp")
        meta.declare("math.lib/author", "GRAME")
        meta.declare("math.lib/copyright", "GRAME")
        meta.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("math.lib/license", "LGPL with exception")
        meta.declare("math.lib/name", "Math Library")
        meta.declare("math.lib/version", "1.0")
        meta.declare("music.lib/author", "GRAME")
        meta.declare("music.lib/copyright", "GRAME")
        meta.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("music.lib/license", "LGPL with exception")
        meta.declare("music.lib/name", "Music Library")
        meta.declare("music.lib/version", "1.0")
        meta.declare("name", "volterra_mini_99")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("volterra_mini_99")
        ui.add_horizontal_slider("delta", dsp.hslider3, FaustFloat(2.0), FaustFloat(0.0), FaustFloat(6.0), FaustFloat(0.1))
        ui.add_horizontal_slider("freq carre", dsp.hslider2, FaustFloat(440.0), FaustFloat(20.0), FaustFloat(8000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider0, "unit", "Hz")
        ui.add_horizontal_slider("freq", dsp.hslider0, FaustFloat(700.0), FaustFloat(1.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("level", dsp.hslider1, FaustFloat(0.5), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ImmStreams[dfaust], var outputs: MutStreams[dfaust]
    ) -> None:
        var output0 = outputs[S32(0)]
        var slow0 = F64(dsp.hslider0)
        var slow1 = (dsp.const1) * (slow0)
        var slow2 = (1.0) / ((slow1) + (1.0))
        var slow3 = F64(dsp.hslider1)
        var slow4 = (dsp.const1) * ((slow3) * (slow0))
        var slow5 = F64(dsp.hslider2)
        var slow6 = max(slow5, 23.44894968246214)
        var slow7 = max(2e+01, abs(slow6))
        var slow8 = (1.0) / (slow7)
        var slow9 = (dsp.const3) * (slow7)
        var slow10 = max((slow5) + (F64(dsp.hslider3)), 23.44894968246214)
        var slow11 = max(2e+01, abs(slow10))
        var slow12 = (1.0) / (slow11)
        var slow13 = (dsp.const3) * (slow11)
        var slow14 = max(0.0, min(2047.0, (dsp.const4) / (slow10)))
        var i_slow15 = S32(slow14)
        var slow16 = F64(i_slow15)
        var slow17 = (slow14) - (slow16)
        var slow18 = (dsp.const2) / (slow11)
        var i_slow19 = (i_slow15) + (S32(1))
        var slow20 = max(0.0, min(2047.0, (dsp.const4) / (slow6)))
        var i_slow21 = S32(slow20)
        var slow22 = F64(i_slow21)
        var slow23 = (slow22) + ((1.0) - (slow20))
        var slow24 = (dsp.const2) / (slow7)
        var slow25 = (slow20) - (slow22)
        var i_slow26 = (i_slow21) + (S32(1))
        var slow27 = (slow16) + ((1.0) - (slow14))
        var slow28 = pow_unrolled[3](slow3)

        for var i0 in range(S32(0), count):
            dsp.i_vec0[S32(0)] = S32(1)
            var temp0 = F64(dsp.i_vec0[S32(1)])
            dsp.rec3[S32(0)] = (slow9) + ((dsp.rec3[S32(1)]) - (floor((slow9) + (dsp.rec3[S32(1)]))))
            var temp1 = pow_unrolled[2](((2.0) * (dsp.rec3[S32(0)])) + (-1.0))
            dsp.vec1[S32(0)] = temp1
            var temp2 = (temp1) - (dsp.vec1[S32(1)])
            dsp.rec4[S32(0)] = (slow13) + ((dsp.rec4[S32(1)]) - (floor((slow13) + (dsp.rec4[S32(1)]))))
            var temp3 = pow_unrolled[2](((2.0) * (dsp.rec4[S32(0)])) + (-1.0))
            dsp.vec2[S32(0)] = temp3
            var temp4 = (temp3) - (dsp.vec2[S32(1)])
            var temp5 = (slow18) * ((temp0) * (temp4))
            dsp.vec3[(dsp.iota0) & (S32(4095))] = temp5
            var temp6 = (slow24) * ((temp0) * (temp2))
            dsp.vec4[(dsp.iota0) & (S32(4095))] = temp6
            var temp7 = ((dsp.const2) * ((temp0) * (((slow8) * (temp2)) + ((slow12) * (temp4))))) - (((slow17) * (dsp.vec3[((dsp.iota0) - (i_slow19)) & (S32(4095))])) + ((((slow23) * (dsp.vec4[((dsp.iota0) - (i_slow21)) & (S32(4095))])) + ((slow25) * (dsp.vec4[((dsp.iota0) - (i_slow26)) & (S32(4095))]))) + ((slow27) * (dsp.vec3[((dsp.iota0) - (i_slow15)) & (S32(4095))]))))
            dsp.rec2[S32(0)] = (slow2) * ((dsp.rec2[S32(1)]) + ((slow4) * (temp7)))
            dsp.rec1[S32(0)] = (slow2) * ((dsp.rec1[S32(1)]) + ((slow1) * (dsp.rec2[S32(0)])))
            dsp.rec0[S32(0)] = (slow2) * ((dsp.rec0[S32(1)]) + ((slow1) * (dsp.rec1[S32(0)])))
            var temp8 = pow_unrolled[3](dsp.rec2[S32(0)])
            dsp.rec7[S32(0)] = (slow2) * ((dsp.rec7[S32(1)]) + ((slow1) * (((slow28) * (pow_unrolled[3](temp7))) - (temp8))))
            var temp9 = pow_unrolled[3](dsp.rec1[S32(0)])
            dsp.rec6[S32(0)] = (slow2) * ((dsp.rec6[S32(1)]) + ((slow1) * (((dsp.rec7[S32(0)]) + (temp8)) - (temp9))))
            dsp.rec5[S32(0)] = (slow2) * ((dsp.rec5[S32(1)]) + ((slow1) * (((dsp.rec6[S32(0)]) + (temp9)) - (pow_unrolled[3](dsp.rec0[S32(0)])))))
            output0[i0] = FaustFloat((dsp.rec0[S32(0)]) - ((0.3333333333333333) * (dsp.rec5[S32(0)])))
            dsp.i_vec0[S32(1)] = dsp.i_vec0[S32(0)]
            dsp.rec3[S32(1)] = dsp.rec3[S32(0)]
            dsp.vec1[S32(1)] = dsp.vec1[S32(0)]
            dsp.rec4[S32(1)] = dsp.rec4[S32(0)]
            dsp.vec2[S32(1)] = dsp.vec2[S32(0)]
            dsp.iota0 = (dsp.iota0) + (S32(1))
            dsp.rec2[S32(1)] = dsp.rec2[S32(0)]
            dsp.rec1[S32(1)] = dsp.rec1[S32(0)]
            dsp.rec0[S32(1)] = dsp.rec0[S32(0)]
            dsp.rec7[S32(1)] = dsp.rec7[S32(0)]
            dsp.rec6[S32(1)] = dsp.rec6[S32(0)]
            dsp.rec5[S32(1)] = dsp.rec5[S32(0)]

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application.
# Initializes the dsp object, allocates and intializes the audio buffers and
# calls the inspect function to run the dsp code.
# ==============================================================================

def main() -> None:
    comptime Real = SIMD[dfaust, 1]
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
    var inputs = ptr.bitcast[Ptr[Real, IMM_NOTRK]]().as_immutable()
    var outputs = (ptr + n_ins).bitcast[Ptr[Real, MUT_NOTRK]]()
    inspect_compute(dsp[], inputs, outputs)
    ptr.free()
    dsp.free()

@no_inline
@export("inspect_compute")
def inspect_compute(
    mut dsp: mydsp, inputs: ImmStreams[dfaust], outputs: MutStreams[dfaust]
) abi("Mojo") -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute(BUFF_SIZE, inputs, outputs)
        clobber_memory()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
