# ==============================================================================
# Faust-to-Mojo inspect architecture for the benchmark framework.
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

comptime dfaust = get_defined_dtype["FAUST_DTYPE", F64.dtype]()
comptime FaustFloat = SIMD[dfaust, 1]

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "carre_volterra"
# Compilation options: 
#   -a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32
# ==============================================================================

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var hslider0: FaustFloat
    var rec4_perm: Arr[F64, 4]
    var hslider1: FaustFloat
    var rec5_perm: Arr[F64, 4]
    var const2: F64
    var hslider2: FaustFloat
    var hslider3: FaustFloat
    var const3: F64
    var i_vec0_perm: Arr[S32, 4]
    var yec0_perm: Arr[F64, 4]
    var yec1_perm: Arr[F64, 4]
    var const4: F64
    var yec2: Arr[F64, 4096]
    var yec2_idx: S32
    var yec2_idx_save: S32
    var yec3: Arr[F64, 4096]
    var yec3_idx: S32
    var yec3_idx_save: S32
    var rec3_perm: Arr[F64, 4]
    var rec2_perm: Arr[F64, 4]
    var rec1_perm: Arr[F64, 4]
    var rec0_perm: Arr[F64, 4]
    var rec9_perm: Arr[F64, 4]
    var rec8_perm: Arr[F64, 4]
    var rec7_perm: Arr[F64, 4]
    var rec6_perm: Arr[F64, 4]
    var checkbox0: FaustFloat

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.hslider0 = 0.0
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider1 = 0.0
        dsp.rec5_perm = Arr[F64, 4](fill=0.0)
        dsp.const2 = 0.0
        dsp.hslider2 = 0.0
        dsp.hslider3 = 0.0
        dsp.const3 = 0.0
        dsp.i_vec0_perm = Arr[S32, 4](fill=0)
        dsp.yec0_perm = Arr[F64, 4](fill=0.0)
        dsp.yec1_perm = Arr[F64, 4](fill=0.0)
        dsp.const4 = 0.0
        dsp.yec2 = Arr[F64, 4096](fill=0.0)
        dsp.yec2_idx = 0
        dsp.yec2_idx_save = 0
        dsp.yec3 = Arr[F64, 4096](fill=0.0)
        dsp.yec3_idx = 0
        dsp.yec3_idx_save = 0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.rec2_perm = Arr[F64, 4](fill=0.0)
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)
        dsp.rec9_perm = Arr[F64, 4](fill=0.0)
        dsp.rec8_perm = Arr[F64, 4](fill=0.0)
        dsp.rec7_perm = Arr[F64, 4](fill=0.0)
        dsp.rec6_perm = Arr[F64, 4](fill=0.0)
        dsp.checkbox0 = 0.0

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
        dsp.const0 = min(F64(1.92e+05), max(F64(1.0), F64(dsp.sample_rate)))
        dsp.const1 = (F64(1.0)) / (dsp.const0)
        dsp.const2 = (F64(6.283185307179586)) / (dsp.const0)
        dsp.const3 = (F64(0.25)) * (dsp.const0)
        dsp.const4 = (F64(0.5)) * (dsp.const0)

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 440.0
        dsp.hslider1 = 2.0
        dsp.hslider2 = 700.0
        dsp.hslider3 = 0.5
        dsp.checkbox0 = 0.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while ((l0) < (S32(4))): 
            dsp.rec4_perm[l0] = F64(0.0)
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while ((l1) < (S32(4))): 
            dsp.rec5_perm[l1] = F64(0.0)
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while ((l2) < (S32(4))): 
            dsp.i_vec0_perm[l2] = S32(0)
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while ((l3) < (S32(4))): 
            dsp.yec0_perm[l3] = F64(0.0)
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while ((l4) < (S32(4))): 
            dsp.yec1_perm[l4] = F64(0.0)
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while ((l5) < (S32(4096))): 
            dsp.yec2[l5] = F64(0.0)
            l5 = (l5) + (S32(1))
        dsp.yec2_idx = S32(0)
        dsp.yec2_idx_save = S32(0)
        var l6 = S32(0)
        while ((l6) < (S32(4096))): 
            dsp.yec3[l6] = F64(0.0)
            l6 = (l6) + (S32(1))
        dsp.yec3_idx = S32(0)
        dsp.yec3_idx_save = S32(0)
        var l7 = S32(0)
        while ((l7) < (S32(4))): 
            dsp.rec3_perm[l7] = F64(0.0)
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while ((l8) < (S32(4))): 
            dsp.rec2_perm[l8] = F64(0.0)
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while ((l9) < (S32(4))): 
            dsp.rec1_perm[l9] = F64(0.0)
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while ((l10) < (S32(4))): 
            dsp.rec0_perm[l10] = F64(0.0)
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while ((l11) < (S32(4))): 
            dsp.rec9_perm[l11] = F64(0.0)
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while ((l12) < (S32(4))): 
            dsp.rec8_perm[l12] = F64(0.0)
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while ((l13) < (S32(4))): 
            dsp.rec7_perm[l13] = F64(0.0)
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while ((l14) < (S32(4))): 
            dsp.rec6_perm[l14] = F64(0.0)
            l14 = (l14) + (S32(1))

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
        return "{\"name\": \"carre_volterra\",\"filename\": \"carre_volterra.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\",\"library_list\": [\"/usr/local/share/faust/effect.lib\",\"/usr/local/share/faust/filter.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/oscillator.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\".\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo\"],\"size\": 66036,\"inputs\": 0,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\" },{ \"effect.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/copyright\": \"Julius O. Smith III\" },{ \"effect.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"effect.lib/exciter_author\": \"Priyanka Shekar (pshekar@ccrma.stanford.edu)\" },{ \"effect.lib/exciter_copyright\": \"Copyright (c) 2013 Priyanka Shekar\" },{ \"effect.lib/exciter_license\": \"MIT License (MIT)\" },{ \"effect.lib/exciter_name\": \"Harmonic Exciter\" },{ \"effect.lib/exciter_version\": \"1.0\" },{ \"effect.lib/license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/version\": \"1.33\" },{ \"filename\": \"carre_volterra.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"carre_volterra\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"carre_volterra\",\"items\": [ {\"type\": \"checkbox\",\"label\": \"NL\",\"varname\": \"fCheckbox0\",\"shortname\": \"NL\",\"address\": \"/carre_volterra/NL\"},{\"type\": \"hslider\",\"label\": \"delta\",\"varname\": \"fHslider1\",\"shortname\": \"delta\",\"address\": \"/carre_volterra/delta\",\"init\": 2,\"min\": 0,\"max\": 6,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"freq carre\",\"varname\": \"fHslider0\",\"shortname\": \"freq_carre\",\"address\": \"/carre_volterra/freq_carre\",\"init\": 440,\"min\": 20,\"max\": 8000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"freq\",\"varname\": \"fHslider2\",\"shortname\": \"freq\",\"address\": \"/carre_volterra/freq\",\"meta\": [{ \"unit\": \"Hz\" }],\"init\": 700,\"min\": 1,\"max\": 20000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"level\",\"varname\": \"fHslider3\",\"shortname\": \"level\",\"address\": \"/carre_volterra/level\",\"init\": 0.5,\"min\": 0,\"max\": 1,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32")
        meta.declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/copyright", "Julius O. Smith III")
        meta.declare("effect.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)")
        meta.declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar")
        meta.declare("effect.lib/exciter_license", "MIT License (MIT)")
        meta.declare("effect.lib/exciter_name", "Harmonic Exciter")
        meta.declare("effect.lib/exciter_version", "1.0")
        meta.declare("effect.lib/license", "STK-4.3")
        meta.declare("effect.lib/name", "Faust Audio Effect Library")
        meta.declare("effect.lib/version", "1.33")
        meta.declare("filename", "carre_volterra.dsp")
        meta.declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("filter.lib/copyright", "Julius O. Smith III")
        meta.declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("filter.lib/license", "STK-4.3")
        meta.declare("filter.lib/name", "Faust Filter Library")
        meta.declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/")
        meta.declare("filter.lib/version", "1.29")
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
        meta.declare("name", "carre_volterra")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("carre_volterra")
        ui.add_check_button("NL", dsp.checkbox0)
        ui.add_horizontal_slider("delta", dsp.hslider1, FaustFloat(2.0), FaustFloat(0.0), FaustFloat(6.0), FaustFloat(0.1))
        ui.add_horizontal_slider("freq carre", dsp.hslider0, FaustFloat(440.0), FaustFloat(20.0), FaustFloat(8000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider2, "unit", "Hz")
        ui.add_horizontal_slider("freq", dsp.hslider2, FaustFloat(700.0), FaustFloat(1.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("level", dsp.hslider3, FaustFloat(0.5), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.close_box()


    @always_inline
    def compute[dreal: DType](
        mut dsp,
        var count:      S32,
        var inputs:     ReadStreams[dreal],
        var outputs:    MutaStreams[dreal]
    ) -> None:
        var output0_ptr = outputs[S32(0)]
        var slow0 = F64(dsp.hslider0)
        var slow1 = max(slow0, F64(23.44894968246214))
        var slow2 = max(F64(2e+01), abs(slow1))
        var slow3 = (dsp.const1) * (slow2)
        var rec4_tmp = Arr[F64, 36](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var slow4 = max((slow0) + (F64(dsp.hslider1)), F64(23.44894968246214))
        var slow5 = max(F64(2e+01), abs(slow4))
        var slow6 = (dsp.const1) * (slow5)
        var rec5_tmp = Arr[F64, 36](uninitialized=True)
        var rec5 = Ptr(to=rec5_tmp[S32(4)])
        var slow7 = F64(dsp.hslider2)
        var slow8 = (dsp.const2) * (slow7)
        var slow9 = (F64(1.0)) / ((slow8) + (F64(1.0)))
        var slow10 = F64(dsp.hslider3)
        var slow11 = (dsp.const2) * ((slow10) * (slow7))
        var i_vec0_tmp = Arr[S32, 36](uninitialized=True)
        var i_vec0 = Ptr(to=i_vec0_tmp[S32(4)])
        var zec0 = Arr[F64, 32](uninitialized=True)
        var slow12 = (F64(1.0)) / (slow2)
        var yec0_tmp = Arr[F64, 36](uninitialized=True)
        var yec0 = Ptr(to=yec0_tmp[S32(4)])
        var zec1 = Arr[F64, 32](uninitialized=True)
        var slow13 = (F64(1.0)) / (slow5)
        var yec1_tmp = Arr[F64, 36](uninitialized=True)
        var yec1 = Ptr(to=yec1_tmp[S32(4)])
        var zec2 = Arr[F64, 32](uninitialized=True)
        var slow14 = max(F64(0.0), min(F64(2047.0), (dsp.const4) / (slow4)))
        var i_slow15 = S32(slow14)
        var slow16 = F64(i_slow15)
        var slow17 = (slow14) - (slow16)
        var slow18 = (dsp.const3) / (slow5)
        var i_slow19 = (i_slow15) + (S32(1))
        var slow20 = max(F64(0.0), min(F64(2047.0), (dsp.const4) / (slow1)))
        var i_slow21 = S32(slow20)
        var slow22 = F64(i_slow21)
        var slow23 = (slow22) + ((F64(1.0)) - (slow20))
        var slow24 = (dsp.const3) / (slow2)
        var slow25 = (slow20) - (slow22)
        var i_slow26 = (i_slow21) + (S32(1))
        var slow27 = (slow16) + ((F64(1.0)) - (slow14))
        var zec3 = Arr[F64, 32](uninitialized=True)
        var rec3_tmp = Arr[F64, 36](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var rec2_tmp = Arr[F64, 36](uninitialized=True)
        var rec2 = Ptr(to=rec2_tmp[S32(4)])
        var rec1_tmp = Arr[F64, 36](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var rec0_tmp = Arr[F64, 36](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var zec4 = Arr[F64, 32](uninitialized=True)
        var rec9_tmp = Arr[F64, 36](uninitialized=True)
        var rec9 = Ptr(to=rec9_tmp[S32(4)])
        var zec5 = Arr[F64, 32](uninitialized=True)
        var rec8_tmp = Arr[F64, 36](uninitialized=True)
        var rec8 = Ptr(to=rec8_tmp[S32(4)])
        var zec6 = Arr[F64, 32](uninitialized=True)
        var rec7_tmp = Arr[F64, 36](uninitialized=True)
        var rec7 = Ptr(to=rec7_tmp[S32(4)])
        var rec6_tmp = Arr[F64, 36](uninitialized=True)
        var rec6 = Ptr(to=rec6_tmp[S32(4)])
        var slow28 = (F64(0.3333333333333333)) * (F64(dsp.checkbox0))
        vindex_re0 = S32(0)
        while ((vindex_re0) <= ((count) - (S32(32)))): 
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re0 = S32(32)
            var j0_re0 = S32(0)
            while ((j0_re0) < (S32(4))): 
                rec4_tmp[j0_re0] = dsp.rec4_perm[j0_re0]
                j0_re0 = (j0_re0) + (S32(1))
            var i_re0 = S32(0)
            while ((i_re0) < (vsize_re0)): 
                rec4[i_re0] = (slow3) + ((rec4[(i_re0) - (S32(1))]) - (floor((slow3) + (rec4[(i_re0) - (S32(1))]))))
                i_re0 = (i_re0) + (S32(1))
            var j1_re0 = S32(0)
            while ((j1_re0) < (S32(4))): 
                dsp.rec4_perm[j1_re0] = rec4_tmp[(vsize_re0) + (j1_re0)]
                j1_re0 = (j1_re0) + (S32(1))
            var j2_re0 = S32(0)
            while ((j2_re0) < (S32(4))): 
                rec5_tmp[j2_re0] = dsp.rec5_perm[j2_re0]
                j2_re0 = (j2_re0) + (S32(1))
            var i_re1 = S32(0)
            while ((i_re1) < (vsize_re0)): 
                rec5[i_re1] = (slow6) + ((rec5[(i_re1) - (S32(1))]) - (floor((slow6) + (rec5[(i_re1) - (S32(1))]))))
                i_re1 = (i_re1) + (S32(1))
            var j3_re0 = S32(0)
            while ((j3_re0) < (S32(4))): 
                dsp.rec5_perm[j3_re0] = rec5_tmp[(vsize_re0) + (j3_re0)]
                j3_re0 = (j3_re0) + (S32(1))
            var j4_re0 = S32(0)
            while ((j4_re0) < (S32(4))): 
                i_vec0_tmp[j4_re0] = dsp.i_vec0_perm[j4_re0]
                j4_re0 = (j4_re0) + (S32(1))
            var i_re2 = S32(0)
            while ((i_re2) < (vsize_re0)): 
                i_vec0[i_re2] = S32(1)
                i_re2 = (i_re2) + (S32(1))
            var j5_re0 = S32(0)
            while ((j5_re0) < (S32(4))): 
                dsp.i_vec0_perm[j5_re0] = i_vec0_tmp[(vsize_re0) + (j5_re0)]
                j5_re0 = (j5_re0) + (S32(1))
            var j6_re0 = S32(0)
            while ((j6_re0) < (S32(4))): 
                yec0_tmp[j6_re0] = dsp.yec0_perm[j6_re0]
                j6_re0 = (j6_re0) + (S32(1))
            var i_re3 = S32(0)
            while ((i_re3) < (vsize_re0)): 
                yec0[i_re3] = pow(((F64(2.0)) * (rec4[i_re3])) + (F64(-1.0)), F64(2.0))
                i_re3 = (i_re3) + (S32(1))
            var j7_re0 = S32(0)
            while ((j7_re0) < (S32(4))): 
                dsp.yec0_perm[j7_re0] = yec0_tmp[(vsize_re0) + (j7_re0)]
                j7_re0 = (j7_re0) + (S32(1))
            var j8_re0 = S32(0)
            while ((j8_re0) < (S32(4))): 
                yec1_tmp[j8_re0] = dsp.yec1_perm[j8_re0]
                j8_re0 = (j8_re0) + (S32(1))
            var i_re4 = S32(0)
            while ((i_re4) < (vsize_re0)): 
                yec1[i_re4] = pow(((F64(2.0)) * (rec5[i_re4])) + (F64(-1.0)), F64(2.0))
                i_re4 = (i_re4) + (S32(1))
            var j9_re0 = S32(0)
            while ((j9_re0) < (S32(4))): 
                dsp.yec1_perm[j9_re0] = yec1_tmp[(vsize_re0) + (j9_re0)]
                j9_re0 = (j9_re0) + (S32(1))
            var i_re5 = S32(0)
            while ((i_re5) < (vsize_re0)): 
                zec0[i_re5] = F64(i_vec0[(i_re5) - (S32(1))])
                i_re5 = (i_re5) + (S32(1))
            var i_re6 = S32(0)
            while ((i_re6) < (vsize_re0)): 
                zec1[i_re6] = (yec0[i_re6]) - (yec0[(i_re6) - (S32(1))])
                i_re6 = (i_re6) + (S32(1))
            var i_re7 = S32(0)
            while ((i_re7) < (vsize_re0)): 
                zec2[i_re7] = (yec1[i_re7]) - (yec1[(i_re7) - (S32(1))])
                i_re7 = (i_re7) + (S32(1))
            dsp.yec2_idx = ((dsp.yec2_idx) + (dsp.yec2_idx_save)) & (S32(4095))
            var i_re8 = S32(0)
            while ((i_re8) < (vsize_re0)): 
                dsp.yec2[((i_re8) + (dsp.yec2_idx)) & (S32(4095))] = (slow18) * ((zec0[i_re8]) * (zec2[i_re8]))
                i_re8 = (i_re8) + (S32(1))
            dsp.yec2_idx_save = vsize_re0
            dsp.yec3_idx = ((dsp.yec3_idx) + (dsp.yec3_idx_save)) & (S32(4095))
            var i_re9 = S32(0)
            while ((i_re9) < (vsize_re0)): 
                dsp.yec3[((i_re9) + (dsp.yec3_idx)) & (S32(4095))] = (slow24) * ((zec0[i_re9]) * (zec1[i_re9]))
                i_re9 = (i_re9) + (S32(1))
            dsp.yec3_idx_save = vsize_re0
            var i_re10 = S32(0)
            while ((i_re10) < (vsize_re0)): 
                zec3[i_re10] = ((dsp.const3) * ((zec0[i_re10]) * (((slow12) * (zec1[i_re10])) + ((slow13) * (zec2[i_re10]))))) - (((slow17) * (dsp.yec2[(((i_re10) + (dsp.yec2_idx)) - (i_slow19)) & (S32(4095))])) + ((((slow23) * (dsp.yec3[(((i_re10) + (dsp.yec3_idx)) - (i_slow21)) & (S32(4095))])) + ((slow25) * (dsp.yec3[(((i_re10) + (dsp.yec3_idx)) - (i_slow26)) & (S32(4095))]))) + ((slow27) * (dsp.yec2[(((i_re10) + (dsp.yec2_idx)) - (i_slow15)) & (S32(4095))]))))
                i_re10 = (i_re10) + (S32(1))
            var j10_re0 = S32(0)
            while ((j10_re0) < (S32(4))): 
                rec3_tmp[j10_re0] = dsp.rec3_perm[j10_re0]
                j10_re0 = (j10_re0) + (S32(1))
            var i_re11 = S32(0)
            while ((i_re11) < (vsize_re0)): 
                rec3[i_re11] = (slow9) * ((rec3[(i_re11) - (S32(1))]) + ((slow11) * (zec3[i_re11])))
                i_re11 = (i_re11) + (S32(1))
            var j11_re0 = S32(0)
            while ((j11_re0) < (S32(4))): 
                dsp.rec3_perm[j11_re0] = rec3_tmp[(vsize_re0) + (j11_re0)]
                j11_re0 = (j11_re0) + (S32(1))
            var j12_re0 = S32(0)
            while ((j12_re0) < (S32(4))): 
                rec2_tmp[j12_re0] = dsp.rec2_perm[j12_re0]
                j12_re0 = (j12_re0) + (S32(1))
            var i_re12 = S32(0)
            while ((i_re12) < (vsize_re0)): 
                rec2[i_re12] = (slow9) * ((rec2[(i_re12) - (S32(1))]) + ((slow8) * (rec3[i_re12])))
                i_re12 = (i_re12) + (S32(1))
            var j13_re0 = S32(0)
            while ((j13_re0) < (S32(4))): 
                dsp.rec2_perm[j13_re0] = rec2_tmp[(vsize_re0) + (j13_re0)]
                j13_re0 = (j13_re0) + (S32(1))
            var i_re13 = S32(0)
            while ((i_re13) < (vsize_re0)): 
                zec4[i_re13] = pow(rec3[i_re13], F64(3.0))
                i_re13 = (i_re13) + (S32(1))
            var j14_re0 = S32(0)
            while ((j14_re0) < (S32(4))): 
                rec1_tmp[j14_re0] = dsp.rec1_perm[j14_re0]
                j14_re0 = (j14_re0) + (S32(1))
            var i_re14 = S32(0)
            while ((i_re14) < (vsize_re0)): 
                rec1[i_re14] = (slow9) * ((rec1[(i_re14) - (S32(1))]) + ((slow8) * (rec2[i_re14])))
                i_re14 = (i_re14) + (S32(1))
            var j15_re0 = S32(0)
            while ((j15_re0) < (S32(4))): 
                dsp.rec1_perm[j15_re0] = rec1_tmp[(vsize_re0) + (j15_re0)]
                j15_re0 = (j15_re0) + (S32(1))
            var j18_re0 = S32(0)
            while ((j18_re0) < (S32(4))): 
                rec9_tmp[j18_re0] = dsp.rec9_perm[j18_re0]
                j18_re0 = (j18_re0) + (S32(1))
            var i_re15 = S32(0)
            while ((i_re15) < (vsize_re0)): 
                rec9[i_re15] = (slow9) * ((rec9[(i_re15) - (S32(1))]) + ((slow8) * ((pow((slow10) * (zec3[i_re15]), F64(3.0))) - (zec4[i_re15]))))
                i_re15 = (i_re15) + (S32(1))
            var j19_re0 = S32(0)
            while ((j19_re0) < (S32(4))): 
                dsp.rec9_perm[j19_re0] = rec9_tmp[(vsize_re0) + (j19_re0)]
                j19_re0 = (j19_re0) + (S32(1))
            var i_re16 = S32(0)
            while ((i_re16) < (vsize_re0)): 
                zec5[i_re16] = pow(rec2[i_re16], F64(3.0))
                i_re16 = (i_re16) + (S32(1))
            var j20_re0 = S32(0)
            while ((j20_re0) < (S32(4))): 
                rec8_tmp[j20_re0] = dsp.rec8_perm[j20_re0]
                j20_re0 = (j20_re0) + (S32(1))
            var i_re17 = S32(0)
            while ((i_re17) < (vsize_re0)): 
                rec8[i_re17] = (slow9) * ((rec8[(i_re17) - (S32(1))]) + ((slow8) * (((rec9[i_re17]) + (zec4[i_re17])) - (zec5[i_re17]))))
                i_re17 = (i_re17) + (S32(1))
            var j21_re0 = S32(0)
            while ((j21_re0) < (S32(4))): 
                dsp.rec8_perm[j21_re0] = rec8_tmp[(vsize_re0) + (j21_re0)]
                j21_re0 = (j21_re0) + (S32(1))
            var i_re18 = S32(0)
            while ((i_re18) < (vsize_re0)): 
                zec6[i_re18] = pow(rec1[i_re18], F64(3.0))
                i_re18 = (i_re18) + (S32(1))
            var j16_re0 = S32(0)
            while ((j16_re0) < (S32(4))): 
                rec0_tmp[j16_re0] = dsp.rec0_perm[j16_re0]
                j16_re0 = (j16_re0) + (S32(1))
            var i_re19 = S32(0)
            while ((i_re19) < (vsize_re0)): 
                rec0[i_re19] = (slow9) * ((rec0[(i_re19) - (S32(1))]) + ((slow8) * (rec1[i_re19])))
                i_re19 = (i_re19) + (S32(1))
            var j17_re0 = S32(0)
            while ((j17_re0) < (S32(4))): 
                dsp.rec0_perm[j17_re0] = rec0_tmp[(vsize_re0) + (j17_re0)]
                j17_re0 = (j17_re0) + (S32(1))
            var j22_re0 = S32(0)
            while ((j22_re0) < (S32(4))): 
                rec7_tmp[j22_re0] = dsp.rec7_perm[j22_re0]
                j22_re0 = (j22_re0) + (S32(1))
            var i_re20 = S32(0)
            while ((i_re20) < (vsize_re0)): 
                rec7[i_re20] = (slow9) * ((rec7[(i_re20) - (S32(1))]) + ((slow8) * (((rec8[i_re20]) + (zec5[i_re20])) - (zec6[i_re20]))))
                i_re20 = (i_re20) + (S32(1))
            var j23_re0 = S32(0)
            while ((j23_re0) < (S32(4))): 
                dsp.rec7_perm[j23_re0] = rec7_tmp[(vsize_re0) + (j23_re0)]
                j23_re0 = (j23_re0) + (S32(1))
            var j24_re0 = S32(0)
            while ((j24_re0) < (S32(4))): 
                rec6_tmp[j24_re0] = dsp.rec6_perm[j24_re0]
                j24_re0 = (j24_re0) + (S32(1))
            var i_re21 = S32(0)
            while ((i_re21) < (vsize_re0)): 
                rec6[i_re21] = (slow9) * ((rec6[(i_re21) - (S32(1))]) + ((slow8) * (((rec7[i_re21]) + (zec6[i_re21])) - (pow(rec0[i_re21], F64(3.0))))))
                i_re21 = (i_re21) + (S32(1))
            var j25_re0 = S32(0)
            while ((j25_re0) < (S32(4))): 
                dsp.rec6_perm[j25_re0] = rec6_tmp[(vsize_re0) + (j25_re0)]
                j25_re0 = (j25_re0) + (S32(1))
            var i_re22 = S32(0)
            while ((i_re22) < (vsize_re0)): 
                output0[i_re22] = SIMD[dreal, 1]((rec0[i_re22]) - ((slow28) * (rec6[i_re22])))
                i_re22 = (i_re22) + (S32(1))
            vindex_re0 = (vindex_re0) + (S32(32))
        if ((vindex_re0) < (count) != 0):
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            var j0_re1 = S32(0)
            while ((j0_re1) < (S32(4))): 
                rec4_tmp[j0_re1] = dsp.rec4_perm[j0_re1]
                j0_re1 = (j0_re1) + (S32(1))
            var i_re23 = S32(0)
            while ((i_re23) < (vsize_re1)): 
                rec4[i_re23] = (slow3) + ((rec4[(i_re23) - (S32(1))]) - (floor((slow3) + (rec4[(i_re23) - (S32(1))]))))
                i_re23 = (i_re23) + (S32(1))
            var j1_re1 = S32(0)
            while ((j1_re1) < (S32(4))): 
                dsp.rec4_perm[j1_re1] = rec4_tmp[(vsize_re1) + (j1_re1)]
                j1_re1 = (j1_re1) + (S32(1))
            var j2_re1 = S32(0)
            while ((j2_re1) < (S32(4))): 
                rec5_tmp[j2_re1] = dsp.rec5_perm[j2_re1]
                j2_re1 = (j2_re1) + (S32(1))
            var i_re24 = S32(0)
            while ((i_re24) < (vsize_re1)): 
                rec5[i_re24] = (slow6) + ((rec5[(i_re24) - (S32(1))]) - (floor((slow6) + (rec5[(i_re24) - (S32(1))]))))
                i_re24 = (i_re24) + (S32(1))
            var j3_re1 = S32(0)
            while ((j3_re1) < (S32(4))): 
                dsp.rec5_perm[j3_re1] = rec5_tmp[(vsize_re1) + (j3_re1)]
                j3_re1 = (j3_re1) + (S32(1))
            var j4_re1 = S32(0)
            while ((j4_re1) < (S32(4))): 
                i_vec0_tmp[j4_re1] = dsp.i_vec0_perm[j4_re1]
                j4_re1 = (j4_re1) + (S32(1))
            var i_re25 = S32(0)
            while ((i_re25) < (vsize_re1)): 
                i_vec0[i_re25] = S32(1)
                i_re25 = (i_re25) + (S32(1))
            var j5_re1 = S32(0)
            while ((j5_re1) < (S32(4))): 
                dsp.i_vec0_perm[j5_re1] = i_vec0_tmp[(vsize_re1) + (j5_re1)]
                j5_re1 = (j5_re1) + (S32(1))
            var j6_re1 = S32(0)
            while ((j6_re1) < (S32(4))): 
                yec0_tmp[j6_re1] = dsp.yec0_perm[j6_re1]
                j6_re1 = (j6_re1) + (S32(1))
            var i_re26 = S32(0)
            while ((i_re26) < (vsize_re1)): 
                yec0[i_re26] = pow(((F64(2.0)) * (rec4[i_re26])) + (F64(-1.0)), F64(2.0))
                i_re26 = (i_re26) + (S32(1))
            var j7_re1 = S32(0)
            while ((j7_re1) < (S32(4))): 
                dsp.yec0_perm[j7_re1] = yec0_tmp[(vsize_re1) + (j7_re1)]
                j7_re1 = (j7_re1) + (S32(1))
            var j8_re1 = S32(0)
            while ((j8_re1) < (S32(4))): 
                yec1_tmp[j8_re1] = dsp.yec1_perm[j8_re1]
                j8_re1 = (j8_re1) + (S32(1))
            var i_re27 = S32(0)
            while ((i_re27) < (vsize_re1)): 
                yec1[i_re27] = pow(((F64(2.0)) * (rec5[i_re27])) + (F64(-1.0)), F64(2.0))
                i_re27 = (i_re27) + (S32(1))
            var j9_re1 = S32(0)
            while ((j9_re1) < (S32(4))): 
                dsp.yec1_perm[j9_re1] = yec1_tmp[(vsize_re1) + (j9_re1)]
                j9_re1 = (j9_re1) + (S32(1))
            var i_re28 = S32(0)
            while ((i_re28) < (vsize_re1)): 
                zec0[i_re28] = F64(i_vec0[(i_re28) - (S32(1))])
                i_re28 = (i_re28) + (S32(1))
            var i_re29 = S32(0)
            while ((i_re29) < (vsize_re1)): 
                zec1[i_re29] = (yec0[i_re29]) - (yec0[(i_re29) - (S32(1))])
                i_re29 = (i_re29) + (S32(1))
            var i_re30 = S32(0)
            while ((i_re30) < (vsize_re1)): 
                zec2[i_re30] = (yec1[i_re30]) - (yec1[(i_re30) - (S32(1))])
                i_re30 = (i_re30) + (S32(1))
            dsp.yec2_idx = ((dsp.yec2_idx) + (dsp.yec2_idx_save)) & (S32(4095))
            var i_re31 = S32(0)
            while ((i_re31) < (vsize_re1)): 
                dsp.yec2[((i_re31) + (dsp.yec2_idx)) & (S32(4095))] = (slow18) * ((zec0[i_re31]) * (zec2[i_re31]))
                i_re31 = (i_re31) + (S32(1))
            dsp.yec2_idx_save = vsize_re1
            dsp.yec3_idx = ((dsp.yec3_idx) + (dsp.yec3_idx_save)) & (S32(4095))
            var i_re32 = S32(0)
            while ((i_re32) < (vsize_re1)): 
                dsp.yec3[((i_re32) + (dsp.yec3_idx)) & (S32(4095))] = (slow24) * ((zec0[i_re32]) * (zec1[i_re32]))
                i_re32 = (i_re32) + (S32(1))
            dsp.yec3_idx_save = vsize_re1
            var i_re33 = S32(0)
            while ((i_re33) < (vsize_re1)): 
                zec3[i_re33] = ((dsp.const3) * ((zec0[i_re33]) * (((slow12) * (zec1[i_re33])) + ((slow13) * (zec2[i_re33]))))) - (((slow17) * (dsp.yec2[(((i_re33) + (dsp.yec2_idx)) - (i_slow19)) & (S32(4095))])) + ((((slow23) * (dsp.yec3[(((i_re33) + (dsp.yec3_idx)) - (i_slow21)) & (S32(4095))])) + ((slow25) * (dsp.yec3[(((i_re33) + (dsp.yec3_idx)) - (i_slow26)) & (S32(4095))]))) + ((slow27) * (dsp.yec2[(((i_re33) + (dsp.yec2_idx)) - (i_slow15)) & (S32(4095))]))))
                i_re33 = (i_re33) + (S32(1))
            var j10_re1 = S32(0)
            while ((j10_re1) < (S32(4))): 
                rec3_tmp[j10_re1] = dsp.rec3_perm[j10_re1]
                j10_re1 = (j10_re1) + (S32(1))
            var i_re34 = S32(0)
            while ((i_re34) < (vsize_re1)): 
                rec3[i_re34] = (slow9) * ((rec3[(i_re34) - (S32(1))]) + ((slow11) * (zec3[i_re34])))
                i_re34 = (i_re34) + (S32(1))
            var j11_re1 = S32(0)
            while ((j11_re1) < (S32(4))): 
                dsp.rec3_perm[j11_re1] = rec3_tmp[(vsize_re1) + (j11_re1)]
                j11_re1 = (j11_re1) + (S32(1))
            var j12_re1 = S32(0)
            while ((j12_re1) < (S32(4))): 
                rec2_tmp[j12_re1] = dsp.rec2_perm[j12_re1]
                j12_re1 = (j12_re1) + (S32(1))
            var i_re35 = S32(0)
            while ((i_re35) < (vsize_re1)): 
                rec2[i_re35] = (slow9) * ((rec2[(i_re35) - (S32(1))]) + ((slow8) * (rec3[i_re35])))
                i_re35 = (i_re35) + (S32(1))
            var j13_re1 = S32(0)
            while ((j13_re1) < (S32(4))): 
                dsp.rec2_perm[j13_re1] = rec2_tmp[(vsize_re1) + (j13_re1)]
                j13_re1 = (j13_re1) + (S32(1))
            var i_re36 = S32(0)
            while ((i_re36) < (vsize_re1)): 
                zec4[i_re36] = pow(rec3[i_re36], F64(3.0))
                i_re36 = (i_re36) + (S32(1))
            var j14_re1 = S32(0)
            while ((j14_re1) < (S32(4))): 
                rec1_tmp[j14_re1] = dsp.rec1_perm[j14_re1]
                j14_re1 = (j14_re1) + (S32(1))
            var i_re37 = S32(0)
            while ((i_re37) < (vsize_re1)): 
                rec1[i_re37] = (slow9) * ((rec1[(i_re37) - (S32(1))]) + ((slow8) * (rec2[i_re37])))
                i_re37 = (i_re37) + (S32(1))
            var j15_re1 = S32(0)
            while ((j15_re1) < (S32(4))): 
                dsp.rec1_perm[j15_re1] = rec1_tmp[(vsize_re1) + (j15_re1)]
                j15_re1 = (j15_re1) + (S32(1))
            var j18_re1 = S32(0)
            while ((j18_re1) < (S32(4))): 
                rec9_tmp[j18_re1] = dsp.rec9_perm[j18_re1]
                j18_re1 = (j18_re1) + (S32(1))
            var i_re38 = S32(0)
            while ((i_re38) < (vsize_re1)): 
                rec9[i_re38] = (slow9) * ((rec9[(i_re38) - (S32(1))]) + ((slow8) * ((pow((slow10) * (zec3[i_re38]), F64(3.0))) - (zec4[i_re38]))))
                i_re38 = (i_re38) + (S32(1))
            var j19_re1 = S32(0)
            while ((j19_re1) < (S32(4))): 
                dsp.rec9_perm[j19_re1] = rec9_tmp[(vsize_re1) + (j19_re1)]
                j19_re1 = (j19_re1) + (S32(1))
            var i_re39 = S32(0)
            while ((i_re39) < (vsize_re1)): 
                zec5[i_re39] = pow(rec2[i_re39], F64(3.0))
                i_re39 = (i_re39) + (S32(1))
            var j20_re1 = S32(0)
            while ((j20_re1) < (S32(4))): 
                rec8_tmp[j20_re1] = dsp.rec8_perm[j20_re1]
                j20_re1 = (j20_re1) + (S32(1))
            var i_re40 = S32(0)
            while ((i_re40) < (vsize_re1)): 
                rec8[i_re40] = (slow9) * ((rec8[(i_re40) - (S32(1))]) + ((slow8) * (((rec9[i_re40]) + (zec4[i_re40])) - (zec5[i_re40]))))
                i_re40 = (i_re40) + (S32(1))
            var j21_re1 = S32(0)
            while ((j21_re1) < (S32(4))): 
                dsp.rec8_perm[j21_re1] = rec8_tmp[(vsize_re1) + (j21_re1)]
                j21_re1 = (j21_re1) + (S32(1))
            var i_re41 = S32(0)
            while ((i_re41) < (vsize_re1)): 
                zec6[i_re41] = pow(rec1[i_re41], F64(3.0))
                i_re41 = (i_re41) + (S32(1))
            var j16_re1 = S32(0)
            while ((j16_re1) < (S32(4))): 
                rec0_tmp[j16_re1] = dsp.rec0_perm[j16_re1]
                j16_re1 = (j16_re1) + (S32(1))
            var i_re42 = S32(0)
            while ((i_re42) < (vsize_re1)): 
                rec0[i_re42] = (slow9) * ((rec0[(i_re42) - (S32(1))]) + ((slow8) * (rec1[i_re42])))
                i_re42 = (i_re42) + (S32(1))
            var j17_re1 = S32(0)
            while ((j17_re1) < (S32(4))): 
                dsp.rec0_perm[j17_re1] = rec0_tmp[(vsize_re1) + (j17_re1)]
                j17_re1 = (j17_re1) + (S32(1))
            var j22_re1 = S32(0)
            while ((j22_re1) < (S32(4))): 
                rec7_tmp[j22_re1] = dsp.rec7_perm[j22_re1]
                j22_re1 = (j22_re1) + (S32(1))
            var i_re43 = S32(0)
            while ((i_re43) < (vsize_re1)): 
                rec7[i_re43] = (slow9) * ((rec7[(i_re43) - (S32(1))]) + ((slow8) * (((rec8[i_re43]) + (zec5[i_re43])) - (zec6[i_re43]))))
                i_re43 = (i_re43) + (S32(1))
            var j23_re1 = S32(0)
            while ((j23_re1) < (S32(4))): 
                dsp.rec7_perm[j23_re1] = rec7_tmp[(vsize_re1) + (j23_re1)]
                j23_re1 = (j23_re1) + (S32(1))
            var j24_re1 = S32(0)
            while ((j24_re1) < (S32(4))): 
                rec6_tmp[j24_re1] = dsp.rec6_perm[j24_re1]
                j24_re1 = (j24_re1) + (S32(1))
            var i_re44 = S32(0)
            while ((i_re44) < (vsize_re1)): 
                rec6[i_re44] = (slow9) * ((rec6[(i_re44) - (S32(1))]) + ((slow8) * (((rec7[i_re44]) + (zec6[i_re44])) - (pow(rec0[i_re44], F64(3.0))))))
                i_re44 = (i_re44) + (S32(1))
            var j25_re1 = S32(0)
            while ((j25_re1) < (S32(4))): 
                dsp.rec6_perm[j25_re1] = rec6_tmp[(vsize_re1) + (j25_re1)]
                j25_re1 = (j25_re1) + (S32(1))
            var i_re45 = S32(0)
            while ((i_re45) < (vsize_re1)): 
                output0[i_re45] = SIMD[dreal, 1]((rec0[i_re45]) - ((slow28) * (rec6[i_re45])))
                i_re45 = (i_re45) + (S32(1))
 
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
    var base, err = make_buffers[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        dsp.free()
        return
    var inputs = base.bitcast[Ptr[Real, READ_EXT]]().as_immutable()
    var outputs = (base + n_ins).bitcast[Ptr[Real, MUTA_EXT]]()
    inspect_compute(dsp[], inputs, outputs)
    base.free()
    dsp.free()

@export("inspect_compute")
@no_inline
def inspect_compute(mut dsp: mydsp, inputs: ReadStreams[dfaust], outputs: MutaStreams[dfaust]) -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute[dfaust](BUFF_SIZE, inputs, outputs)
        clobber_memory()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
