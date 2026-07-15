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
# author: "Grame"
# copyright: "(c)GRAME 2006"
# license: "BSD"
# name: "multibandfilter"
# version: "1.0"
# Compilation options: 
#   
#   -a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo 
#   -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double 
#   -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = S32(simd_width_of[dreal]())
comptime Real = Scalar[dreal]
comptime RVec = Vec[dreal]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var entry0: FaustFloat
    var vslider0: FaustFloat
    var entry1: FaustFloat
    var rec9_perm: Arr[F64, 4]
    var entry2: FaustFloat
    var vslider1: FaustFloat
    var entry3: FaustFloat
    var rec8_perm: Arr[F64, 4]
    var entry4: FaustFloat
    var vslider2: FaustFloat
    var entry5: FaustFloat
    var rec7_perm: Arr[F64, 4]
    var entry6: FaustFloat
    var vslider3: FaustFloat
    var entry7: FaustFloat
    var rec6_perm: Arr[F64, 4]
    var entry8: FaustFloat
    var vslider4: FaustFloat
    var entry9: FaustFloat
    var rec5_perm: Arr[F64, 4]
    var entry10: FaustFloat
    var vslider5: FaustFloat
    var entry11: FaustFloat
    var rec4_perm: Arr[F64, 4]
    var entry12: FaustFloat
    var vslider6: FaustFloat
    var entry13: FaustFloat
    var rec3_perm: Arr[F64, 4]
    var entry14: FaustFloat
    var vslider7: FaustFloat
    var entry15: FaustFloat
    var rec2_perm: Arr[F64, 4]
    var entry16: FaustFloat
    var vslider8: FaustFloat
    var entry17: FaustFloat
    var rec1_perm: Arr[F64, 4]
    var entry18: FaustFloat
    var vslider9: FaustFloat
    var entry19: FaustFloat
    var rec0_perm: Arr[F64, 4]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.entry0 = 0.0
        dsp.vslider0 = 0.0
        dsp.entry1 = 0.0
        dsp.rec9_perm = Arr[F64, 4](fill=0.0)
        dsp.entry2 = 0.0
        dsp.vslider1 = 0.0
        dsp.entry3 = 0.0
        dsp.rec8_perm = Arr[F64, 4](fill=0.0)
        dsp.entry4 = 0.0
        dsp.vslider2 = 0.0
        dsp.entry5 = 0.0
        dsp.rec7_perm = Arr[F64, 4](fill=0.0)
        dsp.entry6 = 0.0
        dsp.vslider3 = 0.0
        dsp.entry7 = 0.0
        dsp.rec6_perm = Arr[F64, 4](fill=0.0)
        dsp.entry8 = 0.0
        dsp.vslider4 = 0.0
        dsp.entry9 = 0.0
        dsp.rec5_perm = Arr[F64, 4](fill=0.0)
        dsp.entry10 = 0.0
        dsp.vslider5 = 0.0
        dsp.entry11 = 0.0
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.entry12 = 0.0
        dsp.vslider6 = 0.0
        dsp.entry13 = 0.0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.entry14 = 0.0
        dsp.vslider7 = 0.0
        dsp.entry15 = 0.0
        dsp.rec2_perm = Arr[F64, 4](fill=0.0)
        dsp.entry16 = 0.0
        dsp.vslider8 = 0.0
        dsp.entry17 = 0.0
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.entry18 = 0.0
        dsp.vslider9 = 0.0
        dsp.entry19 = 0.0
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)

    @always_inline
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 1

    @always_inline
    def class_init(mut dsp, read sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, read sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = (3.141592653589793) / (min(1.92e+05, max(1.0, F64(dsp.sample_rate))))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.entry0 = 1000.0
        dsp.vslider0 = 0.0
        dsp.entry1 = 50.0
        dsp.entry2 = 2000.0
        dsp.vslider1 = 0.0
        dsp.entry3 = 50.0
        dsp.entry4 = 3000.0
        dsp.vslider2 = 0.0
        dsp.entry5 = 50.0
        dsp.entry6 = 4000.0
        dsp.vslider3 = 0.0
        dsp.entry7 = 50.0
        dsp.entry8 = 5000.0
        dsp.vslider4 = 0.0
        dsp.entry9 = 50.0
        dsp.entry10 = 6000.0
        dsp.vslider5 = 0.0
        dsp.entry11 = 50.0
        dsp.entry12 = 7000.0
        dsp.vslider6 = 0.0
        dsp.entry13 = 50.0
        dsp.entry14 = 8000.0
        dsp.vslider7 = 0.0
        dsp.entry15 = 50.0
        dsp.entry16 = 9000.0
        dsp.vslider8 = 0.0
        dsp.entry17 = 50.0
        dsp.entry18 = 10000.0
        dsp.vslider9 = 0.0
        dsp.entry19 = 50.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec9_perm[l0] = 0.0
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.rec8_perm[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.rec7_perm[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(4)): 
            dsp.rec6_perm[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.rec5_perm[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(4)): 
            dsp.rec4_perm[l5] = 0.0
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while (l6) < (S32(4)): 
            dsp.rec3_perm[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while (l7) < (S32(4)): 
            dsp.rec2_perm[l7] = 0.0
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while (l8) < (S32(4)): 
            dsp.rec1_perm[l8] = 0.0
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while (l9) < (S32(4)): 
            dsp.rec0_perm[l9] = 0.0
            l9 = (l9) + (S32(1))

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
        return "{\"name\": \"multibandfilter\",\"filename\": \"multibandfilter.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/bandfilter.dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/music.lib\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/math.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 572,\"inputs\": 1,\"outputs\": 1,\"meta\": [ { \"author\": \"Grame\" },{ \"bandfilter.dsp/author\": \"Grame\" },{ \"bandfilter.dsp/copyright\": \"(c)GRAME 2006\" },{ \"bandfilter.dsp/license\": \"BSD\" },{ \"bandfilter.dsp/name\": \"bandfilter\" },{ \"bandfilter.dsp/version\": \"1.0\" },{ \"compile_options\": \"-a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"copyright\": \"(c)GRAME 2006\" },{ \"filename\": \"multibandfilter.dsp\" },{ \"license\": \"BSD\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"multibandfilter\" },{ \"version\": \"1.0\" }],\"ui\": [ {\"type\": \"hgroup\",\"label\": \"Multi Band Filter\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"peak 0\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry1\",\"shortname\": \"peak_0_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_0/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry0\",\"shortname\": \"peak_0_freq\",\"address\": \"/Multi_Band_Filter/peak_0/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 1000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider0\",\"shortname\": \"peak_0_gain\",\"address\": \"/Multi_Band_Filter/peak_0/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 1\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry3\",\"shortname\": \"peak_1_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_1/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry2\",\"shortname\": \"peak_1_freq\",\"address\": \"/Multi_Band_Filter/peak_1/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 2000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider1\",\"shortname\": \"peak_1_gain\",\"address\": \"/Multi_Band_Filter/peak_1/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 2\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry5\",\"shortname\": \"peak_2_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_2/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry4\",\"shortname\": \"peak_2_freq\",\"address\": \"/Multi_Band_Filter/peak_2/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 3000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider2\",\"shortname\": \"peak_2_gain\",\"address\": \"/Multi_Band_Filter/peak_2/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 3\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry7\",\"shortname\": \"peak_3_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_3/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry6\",\"shortname\": \"peak_3_freq\",\"address\": \"/Multi_Band_Filter/peak_3/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 4000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider3\",\"shortname\": \"peak_3_gain\",\"address\": \"/Multi_Band_Filter/peak_3/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 4\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry9\",\"shortname\": \"peak_4_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_4/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry8\",\"shortname\": \"peak_4_freq\",\"address\": \"/Multi_Band_Filter/peak_4/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 5000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider4\",\"shortname\": \"peak_4_gain\",\"address\": \"/Multi_Band_Filter/peak_4/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 5\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry11\",\"shortname\": \"peak_5_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_5/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry10\",\"shortname\": \"peak_5_freq\",\"address\": \"/Multi_Band_Filter/peak_5/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 6000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider5\",\"shortname\": \"peak_5_gain\",\"address\": \"/Multi_Band_Filter/peak_5/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 6\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry13\",\"shortname\": \"peak_6_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_6/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry12\",\"shortname\": \"peak_6_freq\",\"address\": \"/Multi_Band_Filter/peak_6/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 7000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider6\",\"shortname\": \"peak_6_gain\",\"address\": \"/Multi_Band_Filter/peak_6/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 7\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry15\",\"shortname\": \"peak_7_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_7/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry14\",\"shortname\": \"peak_7_freq\",\"address\": \"/Multi_Band_Filter/peak_7/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 8000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider7\",\"shortname\": \"peak_7_gain\",\"address\": \"/Multi_Band_Filter/peak_7/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 8\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry17\",\"shortname\": \"peak_8_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_8/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry16\",\"shortname\": \"peak_8_freq\",\"address\": \"/Multi_Band_Filter/peak_8/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 9000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider8\",\"shortname\": \"peak_8_gain\",\"address\": \"/Multi_Band_Filter/peak_8/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 9\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry19\",\"shortname\": \"peak_9_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_9/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry18\",\"shortname\": \"peak_9_freq\",\"address\": \"/Multi_Band_Filter/peak_9/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 10000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider9\",\"shortname\": \"peak_9_gain\",\"address\": \"/Multi_Band_Filter/peak_9/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("author", "Grame")
        meta.declare("bandfilter.dsp/author", "Grame")
        meta.declare("bandfilter.dsp/copyright", "(c)GRAME 2006")
        meta.declare("bandfilter.dsp/license", "BSD")
        meta.declare("bandfilter.dsp/name", "bandfilter")
        meta.declare("bandfilter.dsp/version", "1.0")
        meta.declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("copyright", "(c)GRAME 2006")
        meta.declare("filename", "multibandfilter.dsp")
        meta.declare("license", "BSD")
        meta.declare("math.lib/author", "GRAME")
        meta.declare("math.lib/copyright", "GRAME")
        meta.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("math.lib/license", "LGPL with exception")
        meta.declare("math.lib/name", "Math Library")
        meta.declare("math.lib/version", "1.0")
        meta.declare("music.lib/author", "GRAME")
        meta.declare("music.lib/copyright", "GRAME")
        meta.declare("music.lib/license", "LGPL with exception")
        meta.declare("music.lib/name", "Music Library")
        meta.declare("music.lib/version", "1.0")
        meta.declare("name", "multibandfilter")
        meta.declare("version", "1.0")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_horizontal_box("Multi Band Filter")
        ui.open_vertical_box("peak 0")
        ui.declare(dsp.entry1, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry1, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry0, "style", "knob")
        ui.declare(dsp.entry0, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry0, FaustFloat(1000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider0, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider0, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 1")
        ui.declare(dsp.entry3, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry3, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry2, "style", "knob")
        ui.declare(dsp.entry2, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry2, FaustFloat(2000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider1, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider1, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 2")
        ui.declare(dsp.entry5, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry5, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry4, "style", "knob")
        ui.declare(dsp.entry4, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry4, FaustFloat(3000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider2, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider2, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 3")
        ui.declare(dsp.entry7, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry7, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry6, "style", "knob")
        ui.declare(dsp.entry6, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry6, FaustFloat(4000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider3, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider3, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 4")
        ui.declare(dsp.entry9, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry9, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry8, "style", "knob")
        ui.declare(dsp.entry8, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry8, FaustFloat(5000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider4, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider4, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 5")
        ui.declare(dsp.entry11, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry11, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry10, "style", "knob")
        ui.declare(dsp.entry10, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry10, FaustFloat(6000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider5, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider5, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 6")
        ui.declare(dsp.entry13, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry13, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry12, "style", "knob")
        ui.declare(dsp.entry12, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry12, FaustFloat(7000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider6, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider6, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 7")
        ui.declare(dsp.entry15, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry15, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry14, "style", "knob")
        ui.declare(dsp.entry14, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry14, FaustFloat(8000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider7, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider7, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 8")
        ui.declare(dsp.entry17, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry17, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry16, "style", "knob")
        ui.declare(dsp.entry16, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry16, FaustFloat(9000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider8, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider8, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 9")
        ui.declare(dsp.entry19, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry19, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry18, "style", "knob")
        ui.declare(dsp.entry18, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry18, FaustFloat(10000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider9, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider9, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var slow0 = tan((dsp.const0) * (F64(dsp.entry0)))
        var slow1 = F64(dsp.entry1)
        var slow2 = (pow(1e+01, -((0.05) * (F64(dsp.vslider0))))) / (slow1)
        var slow3 = (1.0) / (((slow0) * ((slow0) + (slow2))) + (1.0))
        var slow4 = ((slow0) * ((slow0) - (slow2))) + (1.0)
        var slow5 = (2.0) * ((pow_unrolled[2](slow0)) + (-1.0))
        var zec0 = Arr[F64, 4](uninitialized=True)
        var rec9_tmp = Arr[F64, 8](uninitialized=True)
        var rec9 = Ptr(to=rec9_tmp[S32(4)])
        var slow6 = (1.0) / (slow1)
        var slow7 = ((slow0) * ((slow0) + (slow6))) + (1.0)
        var slow8 = (1.0) - ((slow0) * ((slow6) - (slow0)))
        var slow9 = tan((dsp.const0) * (F64(dsp.entry2)))
        var slow10 = F64(dsp.entry3)
        var slow11 = (pow(1e+01, -((0.05) * (F64(dsp.vslider1))))) / (slow10)
        var slow12 = (1.0) / (((slow9) * ((slow9) + (slow11))) + (1.0))
        var slow13 = ((slow9) * ((slow9) - (slow11))) + (1.0)
        var slow14 = (2.0) * ((pow_unrolled[2](slow9)) + (-1.0))
        var zec1 = Arr[F64, 4](uninitialized=True)
        var rec8_tmp = Arr[F64, 8](uninitialized=True)
        var rec8 = Ptr(to=rec8_tmp[S32(4)])
        var slow15 = (1.0) / (slow10)
        var slow16 = ((slow9) * ((slow9) + (slow15))) + (1.0)
        var slow17 = (1.0) - ((slow9) * ((slow15) - (slow9)))
        var slow18 = tan((dsp.const0) * (F64(dsp.entry4)))
        var slow19 = F64(dsp.entry5)
        var slow20 = (pow(1e+01, -((0.05) * (F64(dsp.vslider2))))) / (slow19)
        var slow21 = (1.0) / (((slow18) * ((slow18) + (slow20))) + (1.0))
        var slow22 = ((slow18) * ((slow18) - (slow20))) + (1.0)
        var slow23 = (2.0) * ((pow_unrolled[2](slow18)) + (-1.0))
        var zec2 = Arr[F64, 4](uninitialized=True)
        var rec7_tmp = Arr[F64, 8](uninitialized=True)
        var rec7 = Ptr(to=rec7_tmp[S32(4)])
        var slow24 = (1.0) / (slow19)
        var slow25 = ((slow18) * ((slow18) + (slow24))) + (1.0)
        var slow26 = (1.0) - ((slow18) * ((slow24) - (slow18)))
        var slow27 = tan((dsp.const0) * (F64(dsp.entry6)))
        var slow28 = F64(dsp.entry7)
        var slow29 = (pow(1e+01, -((0.05) * (F64(dsp.vslider3))))) / (slow28)
        var slow30 = (1.0) / (((slow27) * ((slow27) + (slow29))) + (1.0))
        var slow31 = ((slow27) * ((slow27) - (slow29))) + (1.0)
        var slow32 = (2.0) * ((pow_unrolled[2](slow27)) + (-1.0))
        var zec3 = Arr[F64, 4](uninitialized=True)
        var rec6_tmp = Arr[F64, 8](uninitialized=True)
        var rec6 = Ptr(to=rec6_tmp[S32(4)])
        var slow33 = (1.0) / (slow28)
        var slow34 = ((slow27) * ((slow27) + (slow33))) + (1.0)
        var slow35 = (1.0) - ((slow27) * ((slow33) - (slow27)))
        var slow36 = tan((dsp.const0) * (F64(dsp.entry8)))
        var slow37 = F64(dsp.entry9)
        var slow38 = (pow(1e+01, -((0.05) * (F64(dsp.vslider4))))) / (slow37)
        var slow39 = (1.0) / (((slow36) * ((slow36) + (slow38))) + (1.0))
        var slow40 = ((slow36) * ((slow36) - (slow38))) + (1.0)
        var slow41 = (2.0) * ((pow_unrolled[2](slow36)) + (-1.0))
        var zec4 = Arr[F64, 4](uninitialized=True)
        var rec5_tmp = Arr[F64, 8](uninitialized=True)
        var rec5 = Ptr(to=rec5_tmp[S32(4)])
        var slow42 = (1.0) / (slow37)
        var slow43 = ((slow36) * ((slow36) + (slow42))) + (1.0)
        var slow44 = (1.0) - ((slow36) * ((slow42) - (slow36)))
        var slow45 = tan((dsp.const0) * (F64(dsp.entry10)))
        var slow46 = F64(dsp.entry11)
        var slow47 = (pow(1e+01, -((0.05) * (F64(dsp.vslider5))))) / (slow46)
        var slow48 = (1.0) / (((slow45) * ((slow45) + (slow47))) + (1.0))
        var slow49 = ((slow45) * ((slow45) - (slow47))) + (1.0)
        var slow50 = (2.0) * ((pow_unrolled[2](slow45)) + (-1.0))
        var zec5 = Arr[F64, 4](uninitialized=True)
        var rec4_tmp = Arr[F64, 8](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var slow51 = (1.0) / (slow46)
        var slow52 = ((slow45) * ((slow45) + (slow51))) + (1.0)
        var slow53 = (1.0) - ((slow45) * ((slow51) - (slow45)))
        var slow54 = tan((dsp.const0) * (F64(dsp.entry12)))
        var slow55 = F64(dsp.entry13)
        var slow56 = (pow(1e+01, -((0.05) * (F64(dsp.vslider6))))) / (slow55)
        var slow57 = (1.0) / (((slow54) * ((slow54) + (slow56))) + (1.0))
        var slow58 = ((slow54) * ((slow54) - (slow56))) + (1.0)
        var slow59 = (2.0) * ((pow_unrolled[2](slow54)) + (-1.0))
        var zec6 = Arr[F64, 4](uninitialized=True)
        var rec3_tmp = Arr[F64, 8](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var slow60 = (1.0) / (slow55)
        var slow61 = ((slow54) * ((slow54) + (slow60))) + (1.0)
        var slow62 = (1.0) - ((slow54) * ((slow60) - (slow54)))
        var slow63 = tan((dsp.const0) * (F64(dsp.entry14)))
        var slow64 = F64(dsp.entry15)
        var slow65 = (pow(1e+01, -((0.05) * (F64(dsp.vslider7))))) / (slow64)
        var slow66 = (1.0) / (((slow63) * ((slow63) + (slow65))) + (1.0))
        var slow67 = ((slow63) * ((slow63) - (slow65))) + (1.0)
        var slow68 = (2.0) * ((pow_unrolled[2](slow63)) + (-1.0))
        var zec7 = Arr[F64, 4](uninitialized=True)
        var rec2_tmp = Arr[F64, 8](uninitialized=True)
        var rec2 = Ptr(to=rec2_tmp[S32(4)])
        var slow69 = (1.0) / (slow64)
        var slow70 = ((slow63) * ((slow63) + (slow69))) + (1.0)
        var slow71 = (1.0) - ((slow63) * ((slow69) - (slow63)))
        var slow72 = tan((dsp.const0) * (F64(dsp.entry16)))
        var slow73 = F64(dsp.entry17)
        var slow74 = (pow(1e+01, -((0.05) * (F64(dsp.vslider8))))) / (slow73)
        var slow75 = (1.0) / (((slow72) * ((slow72) + (slow74))) + (1.0))
        var slow76 = ((slow72) * ((slow72) - (slow74))) + (1.0)
        var slow77 = (2.0) * ((pow_unrolled[2](slow72)) + (-1.0))
        var zec8 = Arr[F64, 4](uninitialized=True)
        var rec1_tmp = Arr[F64, 8](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var slow78 = (1.0) / (slow73)
        var slow79 = ((slow72) * ((slow72) + (slow78))) + (1.0)
        var slow80 = (1.0) - ((slow72) * ((slow78) - (slow72)))
        var slow81 = tan((dsp.const0) * (F64(dsp.entry18)))
        var slow82 = F64(dsp.entry19)
        var slow83 = (pow(1e+01, -((0.05) * (F64(dsp.vslider9))))) / (slow82)
        var slow84 = (1.0) / (((slow81) * ((slow81) + (slow83))) + (1.0))
        var slow85 = ((slow81) * ((slow81) - (slow83))) + (1.0)
        var slow86 = (2.0) * ((pow_unrolled[2](slow81)) + (-1.0))
        var zec9 = Arr[F64, 4](uninitialized=True)
        var rec0_tmp = Arr[F64, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var slow87 = (1.0) / (slow82)
        var slow88 = ((slow81) * ((slow81) + (slow87))) + (1.0)
        var slow89 = (1.0) - ((slow81) * ((slow87) - (slow81)))
        # Main loop 
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(4))): 
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re0 = S32(4)
            # Recursive loop 0 
            # Pre code 
            var j0_re0 = S32(0)
            while j0_re0 <= S32(4) - w64:
                var values0 = simd_load(dsp.rec9_perm, j0_re0)
                simd_store(rec9_tmp, j0_re0, values0)
                j0_re0 = j0_re0 + w64
            # Compute code 
            var i_re0 = S32(0)
            while (i_re0) < (vsize_re0): 
                zec0[i_re0] = (slow5) * (rec9[(i_re0) - (S32(1))])
                rec9[i_re0] = (F64(input0[i_re0])) - ((slow3) * (((slow4) * (rec9[(i_re0) - (S32(2))])) + (zec0[i_re0])))
                i_re0 = (i_re0) + (S32(1))
            # Post code 
            var j1_re0 = S32(0)
            while j1_re0 <= S32(4) - w64:
                var values1 = simd_load(rec9_tmp, vsize_re0 + j1_re0)
                simd_store(dsp.rec9_perm, j1_re0, values1)
                j1_re0 = j1_re0 + w64
            # Recursive loop 1 
            # Pre code 
            var j2_re0 = S32(0)
            while j2_re0 <= S32(4) - w64:
                var values2 = simd_load(dsp.rec8_perm, j2_re0)
                simd_store(rec8_tmp, j2_re0, values2)
                j2_re0 = j2_re0 + w64
            # Compute code 
            var i_re1 = S32(0)
            while (i_re1) < (vsize_re0): 
                zec1[i_re1] = (slow14) * (rec8[(i_re1) - (S32(1))])
                rec8[i_re1] = ((slow3) * (((zec0[i_re1]) + ((slow7) * (rec9[i_re1]))) + ((slow8) * (rec9[(i_re1) - (S32(2))])))) - ((slow12) * (((slow13) * (rec8[(i_re1) - (S32(2))])) + (zec1[i_re1])))
                i_re1 = (i_re1) + (S32(1))
            # Post code 
            var j3_re0 = S32(0)
            while j3_re0 <= S32(4) - w64:
                var values3 = simd_load(rec8_tmp, vsize_re0 + j3_re0)
                simd_store(dsp.rec8_perm, j3_re0, values3)
                j3_re0 = j3_re0 + w64
            # Recursive loop 2 
            # Pre code 
            var j4_re0 = S32(0)
            while j4_re0 <= S32(4) - w64:
                var values4 = simd_load(dsp.rec7_perm, j4_re0)
                simd_store(rec7_tmp, j4_re0, values4)
                j4_re0 = j4_re0 + w64
            # Compute code 
            var i_re2 = S32(0)
            while (i_re2) < (vsize_re0): 
                zec2[i_re2] = (slow23) * (rec7[(i_re2) - (S32(1))])
                rec7[i_re2] = ((slow12) * (((zec1[i_re2]) + ((slow16) * (rec8[i_re2]))) + ((slow17) * (rec8[(i_re2) - (S32(2))])))) - ((slow21) * (((slow22) * (rec7[(i_re2) - (S32(2))])) + (zec2[i_re2])))
                i_re2 = (i_re2) + (S32(1))
            # Post code 
            var j5_re0 = S32(0)
            while j5_re0 <= S32(4) - w64:
                var values5 = simd_load(rec7_tmp, vsize_re0 + j5_re0)
                simd_store(dsp.rec7_perm, j5_re0, values5)
                j5_re0 = j5_re0 + w64
            # Recursive loop 3 
            # Pre code 
            var j6_re0 = S32(0)
            while j6_re0 <= S32(4) - w64:
                var values6 = simd_load(dsp.rec6_perm, j6_re0)
                simd_store(rec6_tmp, j6_re0, values6)
                j6_re0 = j6_re0 + w64
            # Compute code 
            var i_re3 = S32(0)
            while (i_re3) < (vsize_re0): 
                zec3[i_re3] = (slow32) * (rec6[(i_re3) - (S32(1))])
                rec6[i_re3] = ((slow21) * (((zec2[i_re3]) + ((slow25) * (rec7[i_re3]))) + ((slow26) * (rec7[(i_re3) - (S32(2))])))) - ((slow30) * (((slow31) * (rec6[(i_re3) - (S32(2))])) + (zec3[i_re3])))
                i_re3 = (i_re3) + (S32(1))
            # Post code 
            var j7_re0 = S32(0)
            while j7_re0 <= S32(4) - w64:
                var values7 = simd_load(rec6_tmp, vsize_re0 + j7_re0)
                simd_store(dsp.rec6_perm, j7_re0, values7)
                j7_re0 = j7_re0 + w64
            # Recursive loop 4 
            # Pre code 
            var j8_re0 = S32(0)
            while j8_re0 <= S32(4) - w64:
                var values8 = simd_load(dsp.rec5_perm, j8_re0)
                simd_store(rec5_tmp, j8_re0, values8)
                j8_re0 = j8_re0 + w64
            # Compute code 
            var i_re4 = S32(0)
            while (i_re4) < (vsize_re0): 
                zec4[i_re4] = (slow41) * (rec5[(i_re4) - (S32(1))])
                rec5[i_re4] = ((slow30) * (((zec3[i_re4]) + ((slow34) * (rec6[i_re4]))) + ((slow35) * (rec6[(i_re4) - (S32(2))])))) - ((slow39) * (((slow40) * (rec5[(i_re4) - (S32(2))])) + (zec4[i_re4])))
                i_re4 = (i_re4) + (S32(1))
            # Post code 
            var j9_re0 = S32(0)
            while j9_re0 <= S32(4) - w64:
                var values9 = simd_load(rec5_tmp, vsize_re0 + j9_re0)
                simd_store(dsp.rec5_perm, j9_re0, values9)
                j9_re0 = j9_re0 + w64
            # Recursive loop 5 
            # Pre code 
            var j10_re0 = S32(0)
            while j10_re0 <= S32(4) - w64:
                var values10 = simd_load(dsp.rec4_perm, j10_re0)
                simd_store(rec4_tmp, j10_re0, values10)
                j10_re0 = j10_re0 + w64
            # Compute code 
            var i_re5 = S32(0)
            while (i_re5) < (vsize_re0): 
                zec5[i_re5] = (slow50) * (rec4[(i_re5) - (S32(1))])
                rec4[i_re5] = ((slow39) * (((zec4[i_re5]) + ((slow43) * (rec5[i_re5]))) + ((slow44) * (rec5[(i_re5) - (S32(2))])))) - ((slow48) * (((slow49) * (rec4[(i_re5) - (S32(2))])) + (zec5[i_re5])))
                i_re5 = (i_re5) + (S32(1))
            # Post code 
            var j11_re0 = S32(0)
            while j11_re0 <= S32(4) - w64:
                var values11 = simd_load(rec4_tmp, vsize_re0 + j11_re0)
                simd_store(dsp.rec4_perm, j11_re0, values11)
                j11_re0 = j11_re0 + w64
            # Recursive loop 6 
            # Pre code 
            var j12_re0 = S32(0)
            while j12_re0 <= S32(4) - w64:
                var values12 = simd_load(dsp.rec3_perm, j12_re0)
                simd_store(rec3_tmp, j12_re0, values12)
                j12_re0 = j12_re0 + w64
            # Compute code 
            var i_re6 = S32(0)
            while (i_re6) < (vsize_re0): 
                zec6[i_re6] = (slow59) * (rec3[(i_re6) - (S32(1))])
                rec3[i_re6] = ((slow48) * (((zec5[i_re6]) + ((slow52) * (rec4[i_re6]))) + ((slow53) * (rec4[(i_re6) - (S32(2))])))) - ((slow57) * (((slow58) * (rec3[(i_re6) - (S32(2))])) + (zec6[i_re6])))
                i_re6 = (i_re6) + (S32(1))
            # Post code 
            var j13_re0 = S32(0)
            while j13_re0 <= S32(4) - w64:
                var values13 = simd_load(rec3_tmp, vsize_re0 + j13_re0)
                simd_store(dsp.rec3_perm, j13_re0, values13)
                j13_re0 = j13_re0 + w64
            # Recursive loop 7 
            # Pre code 
            var j14_re0 = S32(0)
            while j14_re0 <= S32(4) - w64:
                var values14 = simd_load(dsp.rec2_perm, j14_re0)
                simd_store(rec2_tmp, j14_re0, values14)
                j14_re0 = j14_re0 + w64
            # Compute code 
            var i_re7 = S32(0)
            while (i_re7) < (vsize_re0): 
                zec7[i_re7] = (slow68) * (rec2[(i_re7) - (S32(1))])
                rec2[i_re7] = ((slow57) * (((zec6[i_re7]) + ((slow61) * (rec3[i_re7]))) + ((slow62) * (rec3[(i_re7) - (S32(2))])))) - ((slow66) * (((slow67) * (rec2[(i_re7) - (S32(2))])) + (zec7[i_re7])))
                i_re7 = (i_re7) + (S32(1))
            # Post code 
            var j15_re0 = S32(0)
            while j15_re0 <= S32(4) - w64:
                var values15 = simd_load(rec2_tmp, vsize_re0 + j15_re0)
                simd_store(dsp.rec2_perm, j15_re0, values15)
                j15_re0 = j15_re0 + w64
            # Recursive loop 8 
            # Pre code 
            var j16_re0 = S32(0)
            while j16_re0 <= S32(4) - w64:
                var values16 = simd_load(dsp.rec1_perm, j16_re0)
                simd_store(rec1_tmp, j16_re0, values16)
                j16_re0 = j16_re0 + w64
            # Compute code 
            var i_re8 = S32(0)
            while (i_re8) < (vsize_re0): 
                zec8[i_re8] = (slow77) * (rec1[(i_re8) - (S32(1))])
                rec1[i_re8] = ((slow66) * (((zec7[i_re8]) + ((slow70) * (rec2[i_re8]))) + ((slow71) * (rec2[(i_re8) - (S32(2))])))) - ((slow75) * (((slow76) * (rec1[(i_re8) - (S32(2))])) + (zec8[i_re8])))
                i_re8 = (i_re8) + (S32(1))
            # Post code 
            var j17_re0 = S32(0)
            while j17_re0 <= S32(4) - w64:
                var values17 = simd_load(rec1_tmp, vsize_re0 + j17_re0)
                simd_store(dsp.rec1_perm, j17_re0, values17)
                j17_re0 = j17_re0 + w64
            # Recursive loop 9 
            # Pre code 
            var j18_re0 = S32(0)
            while j18_re0 <= S32(4) - w64:
                var values18 = simd_load(dsp.rec0_perm, j18_re0)
                simd_store(rec0_tmp, j18_re0, values18)
                j18_re0 = j18_re0 + w64
            # Compute code 
            var i_re9 = S32(0)
            while (i_re9) < (vsize_re0): 
                zec9[i_re9] = (slow86) * (rec0[(i_re9) - (S32(1))])
                rec0[i_re9] = ((slow75) * (((zec8[i_re9]) + ((slow79) * (rec1[i_re9]))) + ((slow80) * (rec1[(i_re9) - (S32(2))])))) - ((slow84) * (((slow85) * (rec0[(i_re9) - (S32(2))])) + (zec9[i_re9])))
                i_re9 = (i_re9) + (S32(1))
            # Post code 
            var j19_re0 = S32(0)
            while j19_re0 <= S32(4) - w64:
                var values19 = simd_load(rec0_tmp, vsize_re0 + j19_re0)
                simd_store(dsp.rec0_perm, j19_re0, values19)
                j19_re0 = j19_re0 + w64
            # Vectorizable loop 10 
            # Compute code 
            var i_re10 = S32(0)
            while i_re10 <= vsize_re0 - wfaust:
                var lo = ((slow84) * (((simd_load(zec9, i_re10)) + ((slow88) * (simd_load(rec0, i_re10)))) + ((slow89) * (simd_load(rec0, i_re10 - S32(2)))))).cast[dfaust]()
                var hi = ((slow84) * (((simd_load(zec9, i_re10 + S32(wreal))) + ((slow88) * (simd_load(rec0, i_re10 + S32(wreal))))) + ((slow89) * (simd_load(rec0, i_re10 + S32(wreal) - S32(2)))))).cast[dfaust]()
                var values20  = lo.join(hi)
                simd_store(output0, i_re10, values20)
                i_re10 = i_re10 + wfaust
            vindex_re0 = (vindex_re0) + (S32(4))
        # Remaining frames 

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
