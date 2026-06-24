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
# name: "recosc_mini"
# Compilation options: 
#   -a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
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
        return "{\"name\": \"recosc_mini\",\"filename\": \"recosc_mini.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"../_bench/src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/../_bench/src\"],\"size\": 2268,\"inputs\": 0,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\" },{ \"filename\": \"recosc_mini.dsp\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"recosc_mini\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"recosc_mini\",\"items\": []}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32")
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
        comptime width = simd_width_of[dreal]()
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
            while (j0_re0) < (S32(4)): 
                rec1_tmp[j0_re0] = dsp.rec1_perm[j0_re0]
                j0_re0 = (j0_re0) + (S32(1))
            # Compute code 
            var i_re0 = S32(0)
            while (i_re0) < (vsize_re0): 
                rec1[i_re0] = (dsp.const1) + ((rec1[(i_re0) - (S32(1))]) - (floor((dsp.const1) + (rec1[(i_re0) - (S32(1))]))))
                i_re0 = (i_re0) + (S32(1))
            # Post code 
            var j1_re0 = S32(0)
            while (j1_re0) < (S32(4)): 
                dsp.rec1_perm[j1_re0] = rec1_tmp[(vsize_re0) + (j1_re0)]
                j1_re0 = (j1_re0) + (S32(1))

            # Vectorizable loop 1 
            # Pre code 
            var j2_re0 = S32(0)
            while (j2_re0) < (S32(4)): 
                i_vec0_tmp[j2_re0] = dsp.i_vec0_perm[j2_re0]
                j2_re0 = (j2_re0) + (S32(1))
            # Compute code 
            # XXX: old
            # var i_re1 = S32(0)
            # while (i_re1) < (vsize_re0): 
            #     i_vec0[i_re1] = S32(1)
            #     i_re1 = (i_re1) + (S32(1))
            var i_re1 = S32(0)
            while i_re1 <= vsize_re0 - S32(width):
                var ones = SIMD[DType.int32, width](1)
                i_vec0.store(i_re1, ones)
                i_re1 = i_re1 + S32(width)
            while i_re1 < vsize_re0:
                i_vec0[i_re1] = S32(1)
                i_re1 = i_re1 + S32(1)
            # Post code 
            var j3_re0 = S32(0)
            while (j3_re0) < (S32(4)): 
                dsp.i_vec0_perm[j3_re0] = i_vec0_tmp[(vsize_re0) + (j3_re0)]
                j3_re0 = (j3_re0) + (S32(1))

            # Vectorizable loop 2 
            # Pre code 
            var j4_re0 = S32(0)
            while (j4_re0) < (S32(4)): 
                yec0_tmp[j4_re0] = dsp.yec0_perm[j4_re0]
                j4_re0 = (j4_re0) + (S32(1))
            # Compute code 
            # XXX: old
            # var i_re2 = S32(0)
            # while (i_re2) < (vsize_re0): 
            #     yec0[i_re2] = pow_unrolled[2](((2.0) * (rec1[i_re2])) + (-1.0))
            #     i_re2 = (i_re2) + (S32(1))
            var i_re2 = S32(0)
            while i_re2 <= vsize_re0 - S32(width):
                var r = rec1.load[width=width](i_re2)
                var x = (F64(2.0) * r) + F64(-1.0)
                yec0.store(i_re2, x * x)
                i_re2 = i_re2 + S32(width)
            while i_re2 < vsize_re0:
                yec0[i_re2] = pow_unrolled[2](((2.0) * (rec1[i_re2])) + (-1.0))
                i_re2 = i_re2 + S32(1)
            # Post code 
            var j5_re0 = S32(0)
            while (j5_re0) < (S32(4)): 
                dsp.yec0_perm[j5_re0] = yec0_tmp[(vsize_re0) + (j5_re0)]
                j5_re0 = (j5_re0) + (S32(1))
            # Vectorizable loop 3 
            # Pre code 
            dsp.yec1_idx = ((dsp.yec1_idx) + (dsp.yec1_idx_save)) & (S32(255))
            # Compute code 
            var i_re3 = S32(0)
            while (i_re3) < (vsize_re0): 
                dsp.yec1[((i_re3) + (dsp.yec1_idx)) & (S32(255))] = (F64(i_vec0[(i_re3) - (S32(1))])) * ((yec0[i_re3]) - (yec0[(i_re3) - (S32(1))]))
                i_re3 = (i_re3) + (S32(1))
            # Post code 
            dsp.yec1_idx_save = vsize_re0
            # Recursive loop 4 
            # Pre code 
            var j6_re0 = S32(0)
            while (j6_re0) < (S32(4)): 
                rec0_tmp[j6_re0] = dsp.rec0_perm[j6_re0]
                j6_re0 = (j6_re0) + (S32(1))
            # Compute code 
            var i_re4 = S32(0)
            while (i_re4) < (vsize_re0): 
                rec0[i_re4] = ((0.92) * (rec0[(i_re4) - (S32(1))])) + ((dsp.const2) * (((dsp.yec1[((i_re4) + (dsp.yec1_idx)) & (S32(255))]) - ((dsp.const6) * (dsp.yec1[(((i_re4) + (dsp.yec1_idx)) - (dsp.i_const4)) & (S32(255))]))) - ((dsp.const7) * (dsp.yec1[(((i_re4) + (dsp.yec1_idx)) - (dsp.i_const8)) & (S32(255))]))))
                i_re4 = (i_re4) + (S32(1))
            # Post code 
            var j7_re0 = S32(0)
            while (j7_re0) < (S32(4)): 
                dsp.rec0_perm[j7_re0] = rec0_tmp[(vsize_re0) + (j7_re0)]
                j7_re0 = (j7_re0) + (S32(1))
            # Recursive loop 5 
            # Pre code 
            var j8_re0 = S32(0)
            while (j8_re0) < (S32(4)): 
                rec2_tmp[j8_re0] = dsp.rec2_perm[j8_re0]
                j8_re0 = (j8_re0) + (S32(1))
            # Compute code 
            var i_re5 = S32(0)
            while (i_re5) < (vsize_re0): 
                rec2[i_re5] = ((0.92) * (rec2[(i_re5) - (S32(1))])) + ((0.08) * (rec0[i_re5]))
                i_re5 = (i_re5) + (S32(1))
            # Post code 
            var j9_re0 = S32(0)
            while (j9_re0) < (S32(4)): 
                dsp.rec2_perm[j9_re0] = rec2_tmp[(vsize_re0) + (j9_re0)]
                j9_re0 = (j9_re0) + (S32(1))
            # Vectorizable loop 6 
            # Compute code 
            var i_re6 = S32(0)
            while (i_re6) < (vsize_re0): 
                output0[i_re6] = FaustFloat((rec0[i_re6]) - ((0.3333333333333333) * (rec2[i_re6])))
                i_re6 = (i_re6) + (S32(1))
            vindex_re0 = (vindex_re0) + (S32(32))
        # Remaining frames 
        if ((vindex_re0) < (count) != 0):
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            # Recursive loop 0 
            # Pre code 
            var j0_re1 = S32(0)
            while (j0_re1) < (S32(4)): 
                rec1_tmp[j0_re1] = dsp.rec1_perm[j0_re1]
                j0_re1 = (j0_re1) + (S32(1))
            # Compute code 
            var i_re7 = S32(0)
            while (i_re7) < (vsize_re1): 
                rec1[i_re7] = (dsp.const1) + ((rec1[(i_re7) - (S32(1))]) - (floor((dsp.const1) + (rec1[(i_re7) - (S32(1))]))))
                i_re7 = (i_re7) + (S32(1))
            # Post code 
            var j1_re1 = S32(0)
            while (j1_re1) < (S32(4)): 
                dsp.rec1_perm[j1_re1] = rec1_tmp[(vsize_re1) + (j1_re1)]
                j1_re1 = (j1_re1) + (S32(1))
            # Vectorizable loop 1 
            # Pre code 
            var j2_re1 = S32(0)
            while (j2_re1) < (S32(4)): 
                i_vec0_tmp[j2_re1] = dsp.i_vec0_perm[j2_re1]
                j2_re1 = (j2_re1) + (S32(1))
            # Compute code 
            var i_re8 = S32(0)
            while (i_re8) < (vsize_re1): 
                i_vec0[i_re8] = S32(1)
                i_re8 = (i_re8) + (S32(1))
            # Post code 
            var j3_re1 = S32(0)
            while (j3_re1) < (S32(4)): 
                dsp.i_vec0_perm[j3_re1] = i_vec0_tmp[(vsize_re1) + (j3_re1)]
                j3_re1 = (j3_re1) + (S32(1))
            # Vectorizable loop 2 
            # Pre code 
            var j4_re1 = S32(0)
            while (j4_re1) < (S32(4)): 
                yec0_tmp[j4_re1] = dsp.yec0_perm[j4_re1]
                j4_re1 = (j4_re1) + (S32(1))
            # Compute code 
            var i_re9 = S32(0)
            while (i_re9) < (vsize_re1): 
                yec0[i_re9] = pow_unrolled[2](((2.0) * (rec1[i_re9])) + (-1.0))
                i_re9 = (i_re9) + (S32(1))
            # Post code 
            var j5_re1 = S32(0)
            while (j5_re1) < (S32(4)): 
                dsp.yec0_perm[j5_re1] = yec0_tmp[(vsize_re1) + (j5_re1)]
                j5_re1 = (j5_re1) + (S32(1))
            # Vectorizable loop 3 
            # Pre code 
            dsp.yec1_idx = ((dsp.yec1_idx) + (dsp.yec1_idx_save)) & (S32(255))
            # Compute code 
            var i_re10 = S32(0)
            while (i_re10) < (vsize_re1): 
                dsp.yec1[((i_re10) + (dsp.yec1_idx)) & (S32(255))] = (F64(i_vec0[(i_re10) - (S32(1))])) * ((yec0[i_re10]) - (yec0[(i_re10) - (S32(1))]))
                i_re10 = (i_re10) + (S32(1))
            # Post code 
            dsp.yec1_idx_save = vsize_re1
            # Recursive loop 4 
            # Pre code 
            var j6_re1 = S32(0)
            while (j6_re1) < (S32(4)): 
                rec0_tmp[j6_re1] = dsp.rec0_perm[j6_re1]
                j6_re1 = (j6_re1) + (S32(1))
            # Compute code 
            var i_re11 = S32(0)
            while (i_re11) < (vsize_re1): 
                rec0[i_re11] = ((0.92) * (rec0[(i_re11) - (S32(1))])) + ((dsp.const2) * (((dsp.yec1[((i_re11) + (dsp.yec1_idx)) & (S32(255))]) - ((dsp.const6) * (dsp.yec1[(((i_re11) + (dsp.yec1_idx)) - (dsp.i_const4)) & (S32(255))]))) - ((dsp.const7) * (dsp.yec1[(((i_re11) + (dsp.yec1_idx)) - (dsp.i_const8)) & (S32(255))]))))
                i_re11 = (i_re11) + (S32(1))
            # Post code 
            var j7_re1 = S32(0)
            while (j7_re1) < (S32(4)): 
                dsp.rec0_perm[j7_re1] = rec0_tmp[(vsize_re1) + (j7_re1)]
                j7_re1 = (j7_re1) + (S32(1))
            # Recursive loop 5 
            # Pre code 
            var j8_re1 = S32(0)
            while (j8_re1) < (S32(4)): 
                rec2_tmp[j8_re1] = dsp.rec2_perm[j8_re1]
                j8_re1 = (j8_re1) + (S32(1))
            # Compute code 
            var i_re12 = S32(0)
            while (i_re12) < (vsize_re1): 
                rec2[i_re12] = ((0.92) * (rec2[(i_re12) - (S32(1))])) + ((0.08) * (rec0[i_re12]))
                i_re12 = (i_re12) + (S32(1))
            # Post code 
            var j9_re1 = S32(0)
            while (j9_re1) < (S32(4)): 
                dsp.rec2_perm[j9_re1] = rec2_tmp[(vsize_re1) + (j9_re1)]
                j9_re1 = (j9_re1) + (S32(1))
            # Vectorizable loop 6 
            # Compute code 
            var i_re13 = S32(0)
            while (i_re13) < (vsize_re1): 
                output0[i_re13] = FaustFloat((rec0[i_re13]) - ((0.3333333333333333) * (rec2[i_re13])))
                i_re13 = (i_re13) + (S32(1))

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
