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
# name: "recosc_mini"
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
    var const1: F64
    var rec1_perm: Arr[F64, 4]
    var const2: F64
    var i_vec0_perm: Arr[S32, 4]
    var yec0_perm: Arr[F64, 4]
    var yec1: Arr[F64, 256]
    var yec1_idx: S32
    var yec1_idx_save: S32
    var const3: F64
    var i_const4: S32
    var const5: F64
    var const6: F64
    var const7: F64
    var i_const8: S32
    var rec0_perm: Arr[F64, 4]
    var rec2_perm: Arr[F64, 4]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.const2 = 0.0
        dsp.i_vec0_perm = Arr[S32, 4](fill=0)
        dsp.yec0_perm = Arr[F64, 4](fill=0.0)
        dsp.yec1 = Arr[F64, 256](fill=0.0)
        dsp.yec1_idx = 0
        dsp.yec1_idx_save = 0
        dsp.const3 = 0.0
        dsp.i_const4 = 0
        dsp.const5 = 0.0
        dsp.const6 = 0.0
        dsp.const7 = 0.0
        dsp.i_const8 = 0
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)
        dsp.rec2_perm = Arr[F64, 4](fill=0.0)

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
    def class_init(mut dsp, read sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, read sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(1.92e+05, max(1.0, F64(dsp.sample_rate)))
        dsp.const1 = (4.4e+02) / (dsp.const0)
        dsp.const2 = (4.545454545454545e-05) * (dsp.const0)
        dsp.const3 = max(0.0, min(2047.0, (0.0011363636363636363) * (dsp.const0)))
        dsp.i_const4 = S32(dsp.const3)
        dsp.const5 = F64(dsp.i_const4)
        dsp.const6 = (dsp.const5) + ((1.0) - (dsp.const3))
        dsp.const7 = (dsp.const3) - (dsp.const5)
        dsp.i_const8 = (dsp.i_const4) + (S32(1))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        pass

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec1_perm[l0] = 0.0
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.i_vec0_perm[l1] = S32(0)
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.yec0_perm[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(256)): 
            dsp.yec1[l3] = 0.0
            l3 = (l3) + (S32(1))
        dsp.yec1_idx = S32(0)
        dsp.yec1_idx_save = S32(0)
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.rec0_perm[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(4)): 
            dsp.rec2_perm[l5] = 0.0
            l5 = (l5) + (S32(1))

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
        return "{\"name\": \"recosc_mini\",\"filename\": \"recosc_mini.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"../_bench/src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/../_bench/src\"],\"size\": 2268,\"inputs\": 0,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\" },{ \"filename\": \"recosc_mini.dsp\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"recosc_mini\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"recosc_mini\",\"items\": []}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32")
        meta.declare("filename", "recosc_mini.dsp")
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
        meta.declare("name", "recosc_mini")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("recosc_mini")
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var output0_ptr = outputs[S32(0)]
        var rec1_tmp = Arr[F64, 36](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var i_vec0_tmp = Arr[S32, 36](uninitialized=True)
        var i_vec0 = Ptr(to=i_vec0_tmp[S32(4)])
        var yec0_tmp = Arr[F64, 36](uninitialized=True)
        var yec0 = Ptr(to=yec0_tmp[S32(4)])
        var rec0_tmp = Arr[F64, 36](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var rec2_tmp = Arr[F64, 36](uninitialized=True)
        var rec2 = Ptr(to=rec2_tmp[S32(4)])
        # Main loop 
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(32))): 
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re0 = S32(32)
            # Recursive loop 0 
            # Pre code 
            var j0_re0 = S32(0)
            comptime dtype0 = f64
            comptime width0 = S32(simd_width_of[dtype0]())
            while j0_re0 <= S32(4) - width0:
                var values = SIMD[dtype0, SIMDSize(width0)](dsp.rec1_perm[j0_re0])
                Ptr(to=rec1_tmp[0]).store(j0_re0, values)
                j0_re0 = j0_re0 + width0
            # Compute code 
            var i_re0 = S32(0)
            while (i_re0) < (vsize_re0): 
                rec1[i_re0] = (dsp.const1) + ((rec1[(i_re0) - (S32(1))]) - (floor((dsp.const1) + (rec1[(i_re0) - (S32(1))]))))
                i_re0 = (i_re0) + (S32(1))
            # Post code 
            var j1_re0 = S32(0)
            comptime dtype1 = f64
            comptime width1 = S32(simd_width_of[dtype1]())
            while j1_re0 <= S32(4) - width1:
                var values = SIMD[dtype1, SIMDSize(width1)](rec1_tmp[(vsize_re0) + (j1_re0)])
                Ptr(to=dsp.rec1_perm[0]).store(j1_re0, values)
                j1_re0 = j1_re0 + width1
            # Vectorizable loop 1 
            # Pre code 
            var j2_re0 = S32(0)
            comptime dtype2 = s32
            comptime width2 = S32(simd_width_of[dtype2]())
            while j2_re0 <= S32(4) - width2:
                var values = SIMD[dtype2, SIMDSize(width2)](dsp.i_vec0_perm[j2_re0])
                Ptr(to=i_vec0_tmp[0]).store(j2_re0, values)
                j2_re0 = j2_re0 + width2
            # Compute code 
            var i_re1 = S32(0)
            comptime dtype3 = s32
            comptime width3 = S32(simd_width_of[dtype3]())
            while i_re1 <= vsize_re0 - width3:
                var values = SIMD[dtype3, SIMDSize(width3)](S32(1))
                i_vec0.store(i_re1, values)
                i_re1 = i_re1 + width3
            # Post code 
            var j3_re0 = S32(0)
            comptime dtype4 = s32
            comptime width4 = S32(simd_width_of[dtype4]())
            while j3_re0 <= S32(4) - width4:
                var values = SIMD[dtype4, SIMDSize(width4)](i_vec0_tmp[(vsize_re0) + (j3_re0)])
                Ptr(to=dsp.i_vec0_perm[0]).store(j3_re0, values)
                j3_re0 = j3_re0 + width4
            # Vectorizable loop 2 
            # Pre code 
            var j4_re0 = S32(0)
            comptime dtype5 = f64
            comptime width5 = S32(simd_width_of[dtype5]())
            while j4_re0 <= S32(4) - width5:
                var values = SIMD[dtype5, SIMDSize(width5)](dsp.yec0_perm[j4_re0])
                Ptr(to=yec0_tmp[0]).store(j4_re0, values)
                j4_re0 = j4_re0 + width5
            # Compute code 
            var i_re2 = S32(0)
            comptime dtype6 = f64
            comptime width6 = S32(simd_width_of[dtype6]())
            while i_re2 <= vsize_re0 - width6:
                var values = SIMD[dtype6, SIMDSize(width6)](pow_unrolled[2](((2.0) * (rec1[i_re2])) + (-1.0)))
                Ptr(to=yec0[0]).store(i_re2, values)
                i_re2 = i_re2 + width6
            # Post code 
            var j5_re0 = S32(0)
            comptime dtype7 = f64
            comptime width7 = S32(simd_width_of[dtype7]())
            while j5_re0 <= S32(4) - width7:
                var values = SIMD[dtype7, SIMDSize(width7)](yec0_tmp[(vsize_re0) + (j5_re0)])
                Ptr(to=dsp.yec0_perm[0]).store(j5_re0, values)
                j5_re0 = j5_re0 + width7
            # Vectorizable loop 3 
            # Pre code 
            dsp.yec1_idx = ((dsp.yec1_idx) + (dsp.yec1_idx_save)) & (S32(255))
            # Compute code 
            var i_re3 = S32(0)
            comptime dtype8 = f64
            comptime width8 = S32(simd_width_of[dtype8]())
            while i_re3 <= vsize_re0 - width8:
                var values = SIMD[dtype8, SIMDSize(width8)]((F64(i_vec0[(i_re3) - (S32(1))])) * ((yec0[i_re3]) - (yec0[(i_re3) - (S32(1))])))
                Ptr(to=dsp.yec1[0]).store(i_re3, values)
                i_re3 = i_re3 + width8
            # Post code 
            dsp.yec1_idx_save = vsize_re0
            # Recursive loop 4 
            # Pre code 
            var j6_re0 = S32(0)
            comptime dtype9 = f64
            comptime width9 = S32(simd_width_of[dtype9]())
            while j6_re0 <= S32(4) - width9:
                var values = SIMD[dtype9, SIMDSize(width9)](dsp.rec0_perm[j6_re0])
                Ptr(to=rec0_tmp[0]).store(j6_re0, values)
                j6_re0 = j6_re0 + width9
            # Compute code 
            var i_re4 = S32(0)
            while (i_re4) < (vsize_re0): 
                rec0[i_re4] = ((0.92) * (rec0[(i_re4) - (S32(1))])) + ((dsp.const2) * (((dsp.yec1[((i_re4) + (dsp.yec1_idx)) & (S32(255))]) - ((dsp.const6) * (dsp.yec1[(((i_re4) + (dsp.yec1_idx)) - (dsp.i_const4)) & (S32(255))]))) - ((dsp.const7) * (dsp.yec1[(((i_re4) + (dsp.yec1_idx)) - (dsp.i_const8)) & (S32(255))]))))
                i_re4 = (i_re4) + (S32(1))
            # Post code 
            var j7_re0 = S32(0)
            comptime dtype10 = f64
            comptime width10 = S32(simd_width_of[dtype10]())
            while j7_re0 <= S32(4) - width10:
                var values = SIMD[dtype10, SIMDSize(width10)](rec0_tmp[(vsize_re0) + (j7_re0)])
                Ptr(to=dsp.rec0_perm[0]).store(j7_re0, values)
                j7_re0 = j7_re0 + width10
            # Recursive loop 5 
            # Pre code 
            var j8_re0 = S32(0)
            comptime dtype11 = f64
            comptime width11 = S32(simd_width_of[dtype11]())
            while j8_re0 <= S32(4) - width11:
                var values = SIMD[dtype11, SIMDSize(width11)](dsp.rec2_perm[j8_re0])
                Ptr(to=rec2_tmp[0]).store(j8_re0, values)
                j8_re0 = j8_re0 + width11
            # Compute code 
            var i_re5 = S32(0)
            while (i_re5) < (vsize_re0): 
                rec2[i_re5] = ((0.92) * (rec2[(i_re5) - (S32(1))])) + ((0.08) * (rec0[i_re5]))
                i_re5 = (i_re5) + (S32(1))
            # Post code 
            var j9_re0 = S32(0)
            comptime dtype12 = f64
            comptime width12 = S32(simd_width_of[dtype12]())
            while j9_re0 <= S32(4) - width12:
                var values = SIMD[dtype12, SIMDSize(width12)](rec2_tmp[(vsize_re0) + (j9_re0)])
                Ptr(to=dsp.rec2_perm[0]).store(j9_re0, values)
                j9_re0 = j9_re0 + width12
            # Vectorizable loop 6 
            # Compute code 
            var i_re6 = S32(0)
            comptime dtype13 = dfaust
            comptime width13 = S32(simd_width_of[dtype13]())
            while i_re6 <= vsize_re0 - width13:
                var values = SIMD[dtype13, SIMDSize(width13)](FaustFloat((rec0[i_re6]) - ((0.3333333333333333) * (rec2[i_re6]))))
                output0.store(i_re6, values)
                i_re6 = i_re6 + width13
            vindex_re0 = (vindex_re0) + (S32(32))
        # Remaining frames 
        if ((vindex_re0) < (count) != 0):
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            # Recursive loop 0 
            # Pre code 
            var j0_re1 = S32(0)
            comptime dtype14 = f64
            comptime width14 = S32(simd_width_of[dtype14]())
            while j0_re1 <= S32(4) - width14:
                var values = SIMD[dtype14, SIMDSize(width14)](dsp.rec1_perm[j0_re1])
                Ptr(to=rec1_tmp[0]).store(j0_re1, values)
                j0_re1 = j0_re1 + width14
            # Compute code 
            var i_re7 = S32(0)
            while (i_re7) < (vsize_re1): 
                rec1[i_re7] = (dsp.const1) + ((rec1[(i_re7) - (S32(1))]) - (floor((dsp.const1) + (rec1[(i_re7) - (S32(1))]))))
                i_re7 = (i_re7) + (S32(1))
            # Post code 
            var j1_re1 = S32(0)
            comptime dtype15 = f64
            comptime width15 = S32(simd_width_of[dtype15]())
            while j1_re1 <= S32(4) - width15:
                var values = SIMD[dtype15, SIMDSize(width15)](rec1_tmp[(vsize_re1) + (j1_re1)])
                Ptr(to=dsp.rec1_perm[0]).store(j1_re1, values)
                j1_re1 = j1_re1 + width15
            # Vectorizable loop 1 
            # Pre code 
            var j2_re1 = S32(0)
            comptime dtype16 = s32
            comptime width16 = S32(simd_width_of[dtype16]())
            while j2_re1 <= S32(4) - width16:
                var values = SIMD[dtype16, SIMDSize(width16)](dsp.i_vec0_perm[j2_re1])
                Ptr(to=i_vec0_tmp[0]).store(j2_re1, values)
                j2_re1 = j2_re1 + width16
            # Compute code 
            var i_re8 = S32(0)
            comptime dtype17 = s32
            comptime width17 = S32(simd_width_of[dtype17]())
            while i_re8 <= vsize_re1 - width17:
                var values = SIMD[dtype17, SIMDSize(width17)](S32(1))
                i_vec0.store(i_re8, values)
                i_re8 = i_re8 + width17
            # Post code 
            var j3_re1 = S32(0)
            comptime dtype18 = s32
            comptime width18 = S32(simd_width_of[dtype18]())
            while j3_re1 <= S32(4) - width18:
                var values = SIMD[dtype18, SIMDSize(width18)](i_vec0_tmp[(vsize_re1) + (j3_re1)])
                Ptr(to=dsp.i_vec0_perm[0]).store(j3_re1, values)
                j3_re1 = j3_re1 + width18
            # Vectorizable loop 2 
            # Pre code 
            var j4_re1 = S32(0)
            comptime dtype19 = f64
            comptime width19 = S32(simd_width_of[dtype19]())
            while j4_re1 <= S32(4) - width19:
                var values = SIMD[dtype19, SIMDSize(width19)](dsp.yec0_perm[j4_re1])
                Ptr(to=yec0_tmp[0]).store(j4_re1, values)
                j4_re1 = j4_re1 + width19
            # Compute code 
            var i_re9 = S32(0)
            comptime dtype20 = f64
            comptime width20 = S32(simd_width_of[dtype20]())
            while i_re9 <= vsize_re1 - width20:
                var values = SIMD[dtype20, SIMDSize(width20)](pow_unrolled[2](((2.0) * (rec1[i_re9])) + (-1.0)))
                Ptr(to=yec0[0]).store(i_re9, values)
                i_re9 = i_re9 + width20
            # Post code 
            var j5_re1 = S32(0)
            comptime dtype21 = f64
            comptime width21 = S32(simd_width_of[dtype21]())
            while j5_re1 <= S32(4) - width21:
                var values = SIMD[dtype21, SIMDSize(width21)](yec0_tmp[(vsize_re1) + (j5_re1)])
                Ptr(to=dsp.yec0_perm[0]).store(j5_re1, values)
                j5_re1 = j5_re1 + width21
            # Vectorizable loop 3 
            # Pre code 
            dsp.yec1_idx = ((dsp.yec1_idx) + (dsp.yec1_idx_save)) & (S32(255))
            # Compute code 
            var i_re10 = S32(0)
            comptime dtype22 = f64
            comptime width22 = S32(simd_width_of[dtype22]())
            while i_re10 <= vsize_re1 - width22:
                var values = SIMD[dtype22, SIMDSize(width22)]((F64(i_vec0[(i_re10) - (S32(1))])) * ((yec0[i_re10]) - (yec0[(i_re10) - (S32(1))])))
                Ptr(to=dsp.yec1[0]).store(i_re10, values)
                i_re10 = i_re10 + width22
            # Post code 
            dsp.yec1_idx_save = vsize_re1
            # Recursive loop 4 
            # Pre code 
            var j6_re1 = S32(0)
            comptime dtype23 = f64
            comptime width23 = S32(simd_width_of[dtype23]())
            while j6_re1 <= S32(4) - width23:
                var values = SIMD[dtype23, SIMDSize(width23)](dsp.rec0_perm[j6_re1])
                Ptr(to=rec0_tmp[0]).store(j6_re1, values)
                j6_re1 = j6_re1 + width23
            # Compute code 
            var i_re11 = S32(0)
            while (i_re11) < (vsize_re1): 
                rec0[i_re11] = ((0.92) * (rec0[(i_re11) - (S32(1))])) + ((dsp.const2) * (((dsp.yec1[((i_re11) + (dsp.yec1_idx)) & (S32(255))]) - ((dsp.const6) * (dsp.yec1[(((i_re11) + (dsp.yec1_idx)) - (dsp.i_const4)) & (S32(255))]))) - ((dsp.const7) * (dsp.yec1[(((i_re11) + (dsp.yec1_idx)) - (dsp.i_const8)) & (S32(255))]))))
                i_re11 = (i_re11) + (S32(1))
            # Post code 
            var j7_re1 = S32(0)
            comptime dtype24 = f64
            comptime width24 = S32(simd_width_of[dtype24]())
            while j7_re1 <= S32(4) - width24:
                var values = SIMD[dtype24, SIMDSize(width24)](rec0_tmp[(vsize_re1) + (j7_re1)])
                Ptr(to=dsp.rec0_perm[0]).store(j7_re1, values)
                j7_re1 = j7_re1 + width24
            # Recursive loop 5 
            # Pre code 
            var j8_re1 = S32(0)
            comptime dtype25 = f64
            comptime width25 = S32(simd_width_of[dtype25]())
            while j8_re1 <= S32(4) - width25:
                var values = SIMD[dtype25, SIMDSize(width25)](dsp.rec2_perm[j8_re1])
                Ptr(to=rec2_tmp[0]).store(j8_re1, values)
                j8_re1 = j8_re1 + width25
            # Compute code 
            var i_re12 = S32(0)
            while (i_re12) < (vsize_re1): 
                rec2[i_re12] = ((0.92) * (rec2[(i_re12) - (S32(1))])) + ((0.08) * (rec0[i_re12]))
                i_re12 = (i_re12) + (S32(1))
            # Post code 
            var j9_re1 = S32(0)
            comptime dtype26 = f64
            comptime width26 = S32(simd_width_of[dtype26]())
            while j9_re1 <= S32(4) - width26:
                var values = SIMD[dtype26, SIMDSize(width26)](rec2_tmp[(vsize_re1) + (j9_re1)])
                Ptr(to=dsp.rec2_perm[0]).store(j9_re1, values)
                j9_re1 = j9_re1 + width26
            # Vectorizable loop 6 
            # Compute code 
            var i_re13 = S32(0)
            comptime dtype27 = dfaust
            comptime width27 = S32(simd_width_of[dtype27]())
            while i_re13 <= vsize_re1 - width27:
                var values = SIMD[dtype27, SIMDSize(width27)](FaustFloat((rec0[i_re13]) - ((0.3333333333333333) * (rec2[i_re13]))))
                output0.store(i_re13, values)
                i_re13 = i_re13 + width27

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
