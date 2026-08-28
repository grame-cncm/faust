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
# Code generated with Faust 2.87.10 (https://faust.grame.fr)
# name: "grain3"
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
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var hslider0: FaustFloat
    var rec1_perm: Arr[F64, 4]
    var i_rec2_perm: Arr[S32, 4]
    var hslider1: FaustFloat
    var i_rec0_perm: Arr[S32, 4]
    var const2: F64
    var hslider2: FaustFloat
    var rec3_perm: Arr[F64, 4]
    var rec4_perm: Arr[F64, 4]
    var yec0: Arr[F64, 1048576]
    var yec0_idx: S32
    var yec0_idx_save: S32
    var i_rec5: Arr[S32, 2]
    var i_rec6: Arr[S32, 2]
    var ftbl0_mydsp_sig0: Arr[F64, 65536]
    var ftbl1_mydsp_sig1: Arr[F64, 65536]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.hslider0 = 0.0
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.i_rec2_perm = Arr[S32, 4](fill=0)
        dsp.hslider1 = 0.0
        dsp.i_rec0_perm = Arr[S32, 4](fill=0)
        dsp.const2 = 0.0
        dsp.hslider2 = 0.0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.yec0 = Arr[F64, 1048576](fill=0.0)
        dsp.yec0_idx = 0
        dsp.yec0_idx_save = 0
        dsp.i_rec5 = Arr[S32, 2](fill=0)
        dsp.i_rec6 = Arr[S32, 2](fill=0)
        dsp.ftbl0_mydsp_sig0 = Arr[F64, 65536](fill=0.0)
        dsp.ftbl1_mydsp_sig1 = Arr[F64, 65536](fill=0.0)

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 1

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        for var l6 in range(S32(0), 2):
            dsp.i_rec5[l6] = S32(0)
        for var i1 in range(S32(0), 65536):
            dsp.i_rec5[S32(0)] = (dsp.i_rec5[S32(1)]) + (S32(1))
            dsp.ftbl0_mydsp_sig0[i1] = sin((9.587379924285257e-05) * (F64((dsp.i_rec5[S32(0)]) + (S32(-1)))))
            dsp.i_rec5[S32(1)] = dsp.i_rec5[S32(0)]
        for var l7 in range(S32(0), 2):
            dsp.i_rec6[l7] = S32(0)
        for var i2 in range(S32(0), 65536):
            dsp.i_rec6[S32(0)] = (dsp.i_rec6[S32(1)]) + (S32(1))
            dsp.ftbl1_mydsp_sig1[i2] = cos((9.587379924285257e-05) * (F64((dsp.i_rec6[S32(0)]) + (S32(-1)))))
            dsp.i_rec6[S32(1)] = dsp.i_rec6[S32(0)]

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(1.92e+05, max(1.0, F64(dsp.sample_rate)))
        dsp.const1 = (1e+03) / (dsp.const0)
        dsp.const2 = (0.0005) * (dsp.const0)

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 100.0
        dsp.hslider1 = 0.2
        dsp.hslider2 = 1000.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec1_perm[l0] = 0.0
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.i_rec2_perm[l1] = S32(0)
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.i_rec0_perm[l2] = S32(0)
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(4)): 
            dsp.rec3_perm[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.rec4_perm[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(1048576)): 
            dsp.yec0[l5] = 0.0
            l5 = (l5) + (S32(1))
        dsp.yec0_idx = S32(0)
        dsp.yec0_idx_save = S32(0)

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
        return "{\"name\": \"grain3\",\"filename\": \"grain3.dsp\",\"version\": \"2.87.10\",\"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/build/bin//share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 8388812,\"inputs\": 1,\"outputs\": 1,\"meta\": [ { \"basics_lib_name\": \"Faust Basic Element Library\" },{ \"basics_lib_version\": \"0.1\" },{ \"compilation_options\": \"-single -scal -e grain3.dsp -o grain3.dsp\" },{ \"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"delays_lib_name\": \"Faust Delay Library\" },{ \"delays_lib_version\": \"0.1\" },{ \"filename\": \"grain3.dsp\" },{ \"library_path\": \"/usr/local/share/faust/stdfaust.lib\" },{ \"maths_lib_author\": \"GRAME\" },{ \"maths_lib_copyright\": \"GRAME\" },{ \"maths_lib_license\": \"LGPL with exception\" },{ \"maths_lib_name\": \"Faust Math Library\" },{ \"maths_lib_version\": \"2.3\" },{ \"name\": \"grain3\" },{ \"noises_lib_name\": \"Faust Noise Generator Library\" },{ \"noises_lib_version\": \"0.0\" },{ \"oscillators_lib_name\": \"Faust Oscillator Library\" },{ \"oscillators_lib_version\": \"0.1\" },{ \"platform_lib_name\": \"Generic Platform Library\" },{ \"platform_lib_version\": \"0.1\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"grain3\",\"items\": [ {\"type\": \"hslider\",\"label\": \"delaymax\",\"varname\": \"fHslider2\",\"shortname\": \"delaymax\",\"address\": \"/grain3/delaymax\",\"init\": 1000,\"min\": 10,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"grainsize\",\"varname\": \"fHslider0\",\"shortname\": \"grainsize\",\"address\": \"/grain3/grainsize\",\"meta\": [{ \"unit\": \"msec\" }],\"init\": 100,\"min\": 1,\"max\": 1000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"rarefaction\",\"varname\": \"fHslider1\",\"shortname\": \"rarefaction\",\"address\": \"/grain3/rarefaction\",\"init\": 0.2,\"min\": 0,\"max\": 1,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("basics_lib_name", "Faust Basic Element Library")
        meta.declare("basics_lib_version", "0.1")
        meta.declare("compilation_options", "-single -scal -e grain3.dsp -o grain3.dsp")
        meta.declare("compile_options", "-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("delays_lib_name", "Faust Delay Library")
        meta.declare("delays_lib_version", "0.1")
        meta.declare("filename", "grain3.dsp")
        meta.declare("library_path", "/usr/local/share/faust/stdfaust.lib")
        meta.declare("maths_lib_author", "GRAME")
        meta.declare("maths_lib_copyright", "GRAME")
        meta.declare("maths_lib_license", "LGPL with exception")
        meta.declare("maths_lib_name", "Faust Math Library")
        meta.declare("maths_lib_version", "2.3")
        meta.declare("name", "grain3")
        meta.declare("noises_lib_name", "Faust Noise Generator Library")
        meta.declare("noises_lib_version", "0.0")
        meta.declare("oscillators_lib_name", "Faust Oscillator Library")
        meta.declare("oscillators_lib_version", "0.1")
        meta.declare("platform_lib_name", "Generic Platform Library")
        meta.declare("platform_lib_version", "0.1")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("grain3")
        ui.add_horizontal_slider("delaymax", dsp.hslider2, FaustFloat(1000.0), FaustFloat(10.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider0, "unit", "msec")
        ui.add_horizontal_slider("grainsize", dsp.hslider0, FaustFloat(100.0), FaustFloat(1.0), FaustFloat(1000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("rarefaction", dsp.hslider1, FaustFloat(0.2), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.close_box()

    @always_inline
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        comptime vsize = S32(simd_width_of[f32]())
        comptime wsize = S32(simd_width_of[f64]())
        comptime W = simd_width_of[f64]()
        var vindex = S32(0)
        var end = count - vsize
        var input0_ptr = inputs[unsafe_offset = S32(0)]
        var output0_ptr = outputs[unsafe_offset = S32(0)]
        var slow0 = (dsp.const1) / (F64(dsp.hslider0))
        var rec1_tmp = Arr[F64, 8](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var i_rec2_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec2 = Ptr(to=i_rec2_tmp[S32(4)])
        var i_zec0 = Arr[S32, 4](uninitialized=True)
        var zec1 = Arr[F64, 4](uninitialized=True)
        var slow1 = F64(dsp.hslider1)
        var i_rec0_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec0 = Ptr(to=i_rec0_tmp[S32(4)])
        var slow2 = (dsp.const2) * (F64(dsp.hslider2))
        var rec3_tmp = Arr[F64, 8](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var rec4_tmp = Arr[F64, 8](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var i_zec2 = Arr[S32, 4](uninitialized=True)
        var zec3 = Arr[F64, 4](uninitialized=True)
        var i_zec4 = Arr[S32, 4](uninitialized=True)
        var zec5 = Arr[F64, 4](uninitialized=True)
        while vindex <= end:
            var input0 = Ptr(to=input0_ptr[unsafe_offset = vindex])
            var output0 = Ptr(to=output0_ptr[unsafe_offset = vindex])
            vstore(rec1_tmp, vload(dsp.rec1_perm))
            vstore(rec1_tmp, vload(dsp.rec1_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec1[unsafe_offset = i] = (slow0) + ((rec1[unsafe_offset = (i) - (S32(1))]) - (floor((slow0) + (rec1[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec1_perm, vload(rec1_tmp, vsize))
            vstore(dsp.rec1_perm, vload[W](rec1_tmp, vsize + wsize), wsize)
            vstore(i_rec2_tmp, vload(dsp.i_rec2_perm))
            comptime for i in range(vsize):
                i_rec2[unsafe_offset = i] = ((S32(1103515245)) * (i_rec2[unsafe_offset = (i) - (S32(1))])) + (S32(12345))
            vstore(dsp.i_rec2_perm, vload(i_rec2_tmp, vsize))
            vstore(i_zec0, ((vload(rec1).gt(F64Vec(0.0001)).cast[s32]())) * ((vload(rec1, - S32(1)).le(F64Vec(0.0001)).cast[s32]())))
            vstore(zec1, ((F64Vec(4.656612875245797e-10)) * ((vload[W](i_rec2)).cast[f64]())) + (F64Vec(1.0)))
            vstore(zec1, ((F64Vec(4.656612875245797e-10)) * ((vload[W](i_rec2, wsize)).cast[f64]())) + (F64Vec(1.0)), wsize)
            vstore(i_rec0_tmp, vload(dsp.i_rec0_perm))
            comptime for i in range(vsize):
                i_rec0[unsafe_offset = i] = S32(((0.5) * (zec1[i])) > (slow1)) if i_zec0[i] else i_rec0[unsafe_offset = (i) - (S32(1))]
            vstore(dsp.i_rec0_perm, vload(i_rec0_tmp, vsize))
            vstore(rec3_tmp, vload(dsp.rec3_perm))
            vstore(rec3_tmp, vload(dsp.rec3_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec3[unsafe_offset = i] = (slow2) * (zec1[i]) if i_zec0[i] else rec3[unsafe_offset = (i) - (S32(1))]
            vstore(dsp.rec3_perm, vload(rec3_tmp, vsize))
            vstore(dsp.rec3_perm, vload[W](rec3_tmp, vsize + wsize), wsize)
            vstore(rec4_tmp, vload(dsp.rec4_perm))
            vstore(rec4_tmp, vload(dsp.rec4_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec4[unsafe_offset = i] = (rec4[unsafe_offset = (i) - (S32(1))]) - (floor(rec4[unsafe_offset = (i) - (S32(1))]))
            vstore(dsp.rec4_perm, vload(rec4_tmp, vsize))
            vstore(dsp.rec4_perm, vload[W](rec4_tmp, vsize + wsize), wsize)
            dsp.yec0_idx = ((dsp.yec0_idx) + (dsp.yec0_idx_save)) & (S32(1048575))
            comptime for i in range(vsize):
                dsp.yec0[((i) + (dsp.yec0_idx)) & (S32(1048575))] = F64(input0[unsafe_offset = i])
            
            dsp.yec0_idx_save = vsize
            vstore(i_zec2, ((vload(rec3)).cast[s32]()).join((vload(rec3, wsize)).cast[s32]()))
            vstore(zec3, floor(vload(rec3)))
            vstore(zec3, floor(vload(rec3, wsize)), wsize)
            vstore(i_zec4, (((F64Vec(65536.0)) * (vload(rec4))).cast[s32]()).join(((F64Vec(65536.0)) * (vload(rec4, wsize))).cast[s32]()))
            vstore(zec5, (F64Vec(3.141592653589793)) * (vload(rec1)))
            vstore(zec5, (F64Vec(3.141592653589793)) * (vload(rec1, wsize)), wsize)
            comptime for i in range(vsize):
                output0[unsafe_offset = i] = FaustFloat(((F64(i_rec0[unsafe_offset = i])) * (((dsp.yec0[(((i) + (dsp.yec0_idx)) - (min(S32(524289), max(S32(0), i_zec2[i])))) & (S32(1048575))]) * ((zec3[i]) + ((1.0) - (rec3[unsafe_offset = i])))) + (((rec3[unsafe_offset = i]) - (zec3[i])) * (dsp.yec0[(((i) + (dsp.yec0_idx)) - (min(S32(524289), max(S32(0), (i_zec2[i]) + (S32(1)))))) & (S32(1048575))])))) * (((dsp.ftbl0_mydsp_sig0[i_zec4[i]]) * (cos(zec5[i]))) + ((dsp.ftbl1_mydsp_sig1[i_zec4[i]]) * (sin(zec5[i])))))
            
            vindex += vsize

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object,
# initializes the user interface and calls the dsp runner.
# ==============================================================================

def main() raises -> None:
    var nbsamples = S32(60_000)
    var dsp = unsafe_alloc[mydsp](1)
    dsp[] = mydsp()
    var ctrl_gui = ControlGui()
    dsp[].init(SAMP_RATE)
    dsp[].build_user_interface(ctrl_gui)
    print_header(dsp[], nbsamples)
    run_dsp(dsp, ctrl_gui, nbsamples//4)
    dsp.unsafe_free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
