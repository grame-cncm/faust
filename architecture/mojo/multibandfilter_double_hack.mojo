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
# author: "Grame"
# copyright: "(c)GRAME 2006"
# license: "BSD"
# name: "multibandfilter"
# version: "1.0"
# Compilation options: 
#   -a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -single -ftz 0
# ==============================================================================

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var entry0: FaustFloat
    var vslider0: FaustFloat
    var entry1: FaustFloat
    var entry2: FaustFloat
    var vslider1: FaustFloat
    var entry3: FaustFloat
    var entry4: FaustFloat
    var vslider2: FaustFloat
    var entry5: FaustFloat
    var entry6: FaustFloat
    var vslider3: FaustFloat
    var entry7: FaustFloat
    var entry8: FaustFloat
    var vslider4: FaustFloat
    var entry9: FaustFloat
    var entry10: FaustFloat
    var vslider5: FaustFloat
    var entry11: FaustFloat
    var entry12: FaustFloat
    var vslider6: FaustFloat
    var entry13: FaustFloat
    var entry14: FaustFloat
    var vslider7: FaustFloat
    var entry15: FaustFloat
    var entry16: FaustFloat
    var vslider8: FaustFloat
    var entry17: FaustFloat
    var entry18: FaustFloat
    var vslider9: FaustFloat
    var entry19: FaustFloat
    var rec9: Arr[F64, 3]
    var rec8: Arr[F64, 3]
    var rec7: Arr[F64, 3]
    var rec6: Arr[F64, 3]
    var rec5: Arr[F64, 3]
    var rec4: Arr[F64, 3]
    var rec3: Arr[F64, 3]
    var rec2: Arr[F64, 3]
    var rec1: Arr[F64, 3]
    var rec0: Arr[F64, 3]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.entry0 = 0.0
        dsp.vslider0 = 0.0
        dsp.entry1 = 0.0
        dsp.entry2 = 0.0
        dsp.vslider1 = 0.0
        dsp.entry3 = 0.0
        dsp.entry4 = 0.0
        dsp.vslider2 = 0.0
        dsp.entry5 = 0.0
        dsp.entry6 = 0.0
        dsp.vslider3 = 0.0
        dsp.entry7 = 0.0
        dsp.entry8 = 0.0
        dsp.vslider4 = 0.0
        dsp.entry9 = 0.0
        dsp.entry10 = 0.0
        dsp.vslider5 = 0.0
        dsp.entry11 = 0.0
        dsp.entry12 = 0.0
        dsp.vslider6 = 0.0
        dsp.entry13 = 0.0
        dsp.entry14 = 0.0
        dsp.vslider7 = 0.0
        dsp.entry15 = 0.0
        dsp.entry16 = 0.0
        dsp.vslider8 = 0.0
        dsp.entry17 = 0.0
        dsp.entry18 = 0.0
        dsp.vslider9 = 0.0
        dsp.entry19 = 0.0
        dsp.rec9 = Arr[F64, 3](fill=0.0)
        dsp.rec8 = Arr[F64, 3](fill=0.0)
        dsp.rec7 = Arr[F64, 3](fill=0.0)
        dsp.rec6 = Arr[F64, 3](fill=0.0)
        dsp.rec5 = Arr[F64, 3](fill=0.0)
        dsp.rec4 = Arr[F64, 3](fill=0.0)
        dsp.rec3 = Arr[F64, 3](fill=0.0)
        dsp.rec2 = Arr[F64, 3](fill=0.0)
        dsp.rec1 = Arr[F64, 3](fill=0.0)
        dsp.rec0 = Arr[F64, 3](fill=0.0)

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
        dsp.const0 = (F64(3.1415927)) / (min(F64(1.92e+05), max(F64(1.0), F64(dsp.sample_rate))))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.entry0 = 10000.0
        dsp.vslider0 = 0.0
        dsp.entry1 = 50.0
        dsp.entry2 = 9000.0
        dsp.vslider1 = 0.0
        dsp.entry3 = 50.0
        dsp.entry4 = 8000.0
        dsp.vslider2 = 0.0
        dsp.entry5 = 50.0
        dsp.entry6 = 7000.0
        dsp.vslider3 = 0.0
        dsp.entry7 = 50.0
        dsp.entry8 = 6000.0
        dsp.vslider4 = 0.0
        dsp.entry9 = 50.0
        dsp.entry10 = 5000.0
        dsp.vslider5 = 0.0
        dsp.entry11 = 50.0
        dsp.entry12 = 4000.0
        dsp.vslider6 = 0.0
        dsp.entry13 = 50.0
        dsp.entry14 = 3000.0
        dsp.vslider7 = 0.0
        dsp.entry15 = 50.0
        dsp.entry16 = 2000.0
        dsp.vslider8 = 0.0
        dsp.entry17 = 50.0
        dsp.entry18 = 1000.0
        dsp.vslider9 = 0.0
        dsp.entry19 = 50.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while ((l0) < (S32(3))): 
            dsp.rec9[l0] = F64(0.0)
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while ((l1) < (S32(3))): 
            dsp.rec8[l1] = F64(0.0)
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while ((l2) < (S32(3))): 
            dsp.rec7[l2] = F64(0.0)
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while ((l3) < (S32(3))): 
            dsp.rec6[l3] = F64(0.0)
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while ((l4) < (S32(3))): 
            dsp.rec5[l4] = F64(0.0)
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while ((l5) < (S32(3))): 
            dsp.rec4[l5] = F64(0.0)
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while ((l6) < (S32(3))): 
            dsp.rec3[l6] = F64(0.0)
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while ((l7) < (S32(3))): 
            dsp.rec2[l7] = F64(0.0)
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while ((l8) < (S32(3))): 
            dsp.rec1[l8] = F64(0.0)
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while ((l9) < (S32(3))): 
            dsp.rec0[l9] = F64(0.0)
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
        return "{\"name\": \"multibandfilter\",\"filename\": \"multibandfilter.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0\",\"library_list\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/bandfilter.dsp\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"../../tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/../../tests/impulse-tests/dsp\"],\"size\": 248,\"inputs\": 1,\"outputs\": 1,\"meta\": [ { \"author\": \"Grame\" },{ \"bandfilter.dsp/author\": \"Grame\" },{ \"bandfilter.dsp/copyright\": \"(c)GRAME 2006\" },{ \"bandfilter.dsp/license\": \"BSD\" },{ \"bandfilter.dsp/name\": \"bandfilter\" },{ \"bandfilter.dsp/version\": \"1.0\" },{ \"compile_options\": \"-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0\" },{ \"copyright\": \"(c)GRAME 2006\" },{ \"filename\": \"multibandfilter.dsp\" },{ \"license\": \"BSD\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"multibandfilter\" },{ \"version\": \"1.0\" }],\"ui\": [ {\"type\": \"hgroup\",\"label\": \"Multi Band Filter\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"peak 0\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry19\",\"shortname\": \"peak_0_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_0/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry18\",\"shortname\": \"peak_0_freq\",\"address\": \"/Multi_Band_Filter/peak_0/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 1000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider9\",\"shortname\": \"peak_0_gain\",\"address\": \"/Multi_Band_Filter/peak_0/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 1\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry17\",\"shortname\": \"peak_1_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_1/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry16\",\"shortname\": \"peak_1_freq\",\"address\": \"/Multi_Band_Filter/peak_1/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 2000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider8\",\"shortname\": \"peak_1_gain\",\"address\": \"/Multi_Band_Filter/peak_1/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 2\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry15\",\"shortname\": \"peak_2_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_2/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry14\",\"shortname\": \"peak_2_freq\",\"address\": \"/Multi_Band_Filter/peak_2/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 3000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider7\",\"shortname\": \"peak_2_gain\",\"address\": \"/Multi_Band_Filter/peak_2/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 3\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry13\",\"shortname\": \"peak_3_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_3/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry12\",\"shortname\": \"peak_3_freq\",\"address\": \"/Multi_Band_Filter/peak_3/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 4000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider6\",\"shortname\": \"peak_3_gain\",\"address\": \"/Multi_Band_Filter/peak_3/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 4\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry11\",\"shortname\": \"peak_4_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_4/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry10\",\"shortname\": \"peak_4_freq\",\"address\": \"/Multi_Band_Filter/peak_4/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 5000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider5\",\"shortname\": \"peak_4_gain\",\"address\": \"/Multi_Band_Filter/peak_4/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 5\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry9\",\"shortname\": \"peak_5_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_5/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry8\",\"shortname\": \"peak_5_freq\",\"address\": \"/Multi_Band_Filter/peak_5/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 6000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider4\",\"shortname\": \"peak_5_gain\",\"address\": \"/Multi_Band_Filter/peak_5/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 6\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry7\",\"shortname\": \"peak_6_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_6/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry6\",\"shortname\": \"peak_6_freq\",\"address\": \"/Multi_Band_Filter/peak_6/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 7000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider3\",\"shortname\": \"peak_6_gain\",\"address\": \"/Multi_Band_Filter/peak_6/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 7\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry5\",\"shortname\": \"peak_7_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_7/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry4\",\"shortname\": \"peak_7_freq\",\"address\": \"/Multi_Band_Filter/peak_7/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 8000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider2\",\"shortname\": \"peak_7_gain\",\"address\": \"/Multi_Band_Filter/peak_7/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 8\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry3\",\"shortname\": \"peak_8_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_8/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry2\",\"shortname\": \"peak_8_freq\",\"address\": \"/Multi_Band_Filter/peak_8/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 9000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider1\",\"shortname\": \"peak_8_gain\",\"address\": \"/Multi_Band_Filter/peak_8/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"peak 9\",\"items\": [ {\"type\": \"nentry\",\"label\": \"Q factor\",\"varname\": \"fEntry1\",\"shortname\": \"peak_9_Q_factor\",\"address\": \"/Multi_Band_Filter/peak_9/Q_factor\",\"meta\": [{ \"style\": \"knob\" }],\"init\": 50,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"nentry\",\"label\": \"freq\",\"varname\": \"fEntry0\",\"shortname\": \"peak_9_freq\",\"address\": \"/Multi_Band_Filter/peak_9/freq\",\"meta\": [{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 10000,\"min\": 20,\"max\": 20000,\"step\": 1},{\"type\": \"vslider\",\"label\": \"gain\",\"varname\": \"fVslider0\",\"shortname\": \"peak_9_gain\",\"address\": \"/Multi_Band_Filter/peak_9/gain\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -50,\"max\": 50,\"step\": 0.1}]}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("author", "Grame")
        meta.declare("bandfilter.dsp/author", "Grame")
        meta.declare("bandfilter.dsp/copyright", "(c)GRAME 2006")
        meta.declare("bandfilter.dsp/license", "BSD")
        meta.declare("bandfilter.dsp/name", "bandfilter")
        meta.declare("bandfilter.dsp/version", "1.0")
        meta.declare("compile_options", "-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0")
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
        meta.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("music.lib/license", "LGPL with exception")
        meta.declare("music.lib/name", "Music Library")
        meta.declare("music.lib/version", "1.0")
        meta.declare("name", "multibandfilter")
        meta.declare("version", "1.0")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_horizontal_box("Multi Band Filter")
        ui.open_vertical_box("peak 0")
        ui.declare(dsp.entry19, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry19, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry18, "style", "knob")
        ui.declare(dsp.entry18, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry18, FaustFloat(1000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider9, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider9, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 1")
        ui.declare(dsp.entry17, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry17, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry16, "style", "knob")
        ui.declare(dsp.entry16, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry16, FaustFloat(2000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider8, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider8, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 2")
        ui.declare(dsp.entry15, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry15, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry14, "style", "knob")
        ui.declare(dsp.entry14, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry14, FaustFloat(3000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider7, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider7, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 3")
        ui.declare(dsp.entry13, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry13, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry12, "style", "knob")
        ui.declare(dsp.entry12, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry12, FaustFloat(4000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider6, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider6, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 4")
        ui.declare(dsp.entry11, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry11, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry10, "style", "knob")
        ui.declare(dsp.entry10, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry10, FaustFloat(5000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider5, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider5, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 5")
        ui.declare(dsp.entry9, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry9, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry8, "style", "knob")
        ui.declare(dsp.entry8, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry8, FaustFloat(6000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider4, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider4, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 6")
        ui.declare(dsp.entry7, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry7, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry6, "style", "knob")
        ui.declare(dsp.entry6, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry6, FaustFloat(7000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider3, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider3, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 7")
        ui.declare(dsp.entry5, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry5, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry4, "style", "knob")
        ui.declare(dsp.entry4, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry4, FaustFloat(8000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider2, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider2, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 8")
        ui.declare(dsp.entry3, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry3, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry2, "style", "knob")
        ui.declare(dsp.entry2, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry2, FaustFloat(9000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider1, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider1, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.open_vertical_box("peak 9")
        ui.declare(dsp.entry1, "style", "knob")
        ui.add_num_entry("Q factor", dsp.entry1, FaustFloat(50.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.entry0, "style", "knob")
        ui.declare(dsp.entry0, "unit", "Hz")
        ui.add_num_entry("freq", dsp.entry0, FaustFloat(10000.0), FaustFloat(20.0), FaustFloat(20000.0), FaustFloat(1.0))
        ui.declare(dsp.vslider0, "unit", "dB")
        ui.add_vertical_slider("gain", dsp.vslider0, FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1))
        ui.close_box()
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, read inputs: Ptr[FaustFloat, READ_EXT], mut outputs: Ptr[FaustFloat, MUTA_EXT]
    ) -> None:
        var input0 = Ptr(to=inputs[S32(0)]).as_noalias_ptr()
        var output0 = Ptr(to=outputs[S32(0)]).as_noalias_ptr()
        var slow0 = tan((dsp.const0) * (F64(dsp.entry0)))
        var slow1 = F64(dsp.entry1)
        var slow2 = (pow(1e+01, -((0.05) * (F64(dsp.vslider0))))) / (slow1)
        var slow3 = (1.0) / (((slow0) * ((slow0) + (slow2))) + (1.0))
        var slow4 = (2.0) * ((pow_unrolled[2](slow0)) + (-1.0))
        var slow5 = tan((dsp.const0) * (F64(dsp.entry2)))
        var slow6 = F64(dsp.entry3)
        var slow7 = (pow(1e+01, -((0.05) * (F64(dsp.vslider1))))) / (slow6)
        var slow8 = (1.0) / (((slow5) * ((slow5) + (slow7))) + (1.0))
        var slow9 = (2.0) * ((pow_unrolled[2](slow5)) + (-1.0))

        var slow10 = tan((dsp.const0) * (F64(dsp.entry4)))
        var slow11 = F64(dsp.entry5)
        var slow12 = (pow(1e+01, -((0.05) * (F64(dsp.vslider2))))) / (slow11)
        var slow13 = (1.0) / (((slow10) * ((slow10) + (slow12))) + (1.0))
        var slow14 = (2.0) * ((pow_unrolled[2](slow10)) + (-1.0))
        var slow15 = tan((dsp.const0) * (F64(dsp.entry6)))
        var slow16 = F64(dsp.entry7)
        var slow17 = (pow(1e+01, -((0.05) * (F64(dsp.vslider3))))) / (slow16)
        var slow18 = (1.0) / (((slow15) * ((slow15) + (slow17))) + (1.0))
        var slow19 = (2.0) * ((pow_unrolled[2](slow15)) + (-1.0))

        var slow20 = tan((dsp.const0) * (F64(dsp.entry8)))
        var slow21 = F64(dsp.entry9)
        var slow22 = (pow(1e+01, -((0.05) * (F64(dsp.vslider4))))) / (slow21)
        var slow23 = (1.0) / (((slow20) * ((slow20) + (slow22))) + (1.0))
        var slow24 = (2.0) * ((pow_unrolled[2](slow20)) + (-1.0))
        var slow25 = tan((dsp.const0) * (F64(dsp.entry10)))
        var slow26 = F64(dsp.entry11)
        var slow27 = (pow(1e+01, -((0.05) * (F64(dsp.vslider5))))) / (slow26)
        var slow28 = (1.0) / (((slow25) * ((slow25) + (slow27))) + (1.0))
        var slow29 = (2.0) * ((pow_unrolled[2](slow25)) + (-1.0))

        var slow30 = tan((dsp.const0) * (F64(dsp.entry12)))
        var slow31 = F64(dsp.entry13)
        var slow32 = (pow(1e+01, -((0.05) * (F64(dsp.vslider6))))) / (slow31)
        var slow33 = (1.0) / (((slow30) * ((slow30) + (slow32))) + (1.0))
        var slow34 = (2.0) * ((pow_unrolled[2](slow30)) + (-1.0))
        var slow35 = tan((dsp.const0) * (F64(dsp.entry14)))
        var slow36 = F64(dsp.entry15)
        var slow37 = (pow(1e+01, -((0.05) * (F64(dsp.vslider7))))) / (slow36)
        var slow38 = (1.0) / (((slow35) * ((slow35) + (slow37))) + (1.0))
        var slow39 = (2.0) * ((pow_unrolled[2](slow35)) + (-1.0))

        var slow40 = tan((dsp.const0) * (F64(dsp.entry16)))
        var slow41 = F64(dsp.entry17)
        var slow42 = (pow(1e+01, -((0.05) * (F64(dsp.vslider8))))) / (slow41)
        var slow43 = (1.0) / (((slow40) * ((slow40) + (slow42))) + (1.0))
        var slow44 = (2.0) * ((pow_unrolled[2](slow40)) + (-1.0))
        var slow45 = tan((dsp.const0) * (F64(dsp.entry18)))
        var slow46 = F64(dsp.entry19)
        var slow47 = (pow(1e+01, -((0.05) * (F64(dsp.vslider9))))) / (slow46)
        var slow48 = (1.0) / (((slow45) * ((slow45) + (slow47))) + (1.0))
        var slow49 = (2.0) * ((pow_unrolled[2](slow45)) + (-1.0))

        var slow50 = ((slow45) * ((slow45) - (slow47))) + (1.0)
        var slow51 = (1.0) / (slow46)
        var slow52 = ((slow45) * ((slow45) + (slow51))) + (1.0)
        var slow53 = (1.0) - ((slow45) * ((slow51) - (slow45)))
        var slow54 = ((slow40) * ((slow40) - (slow42))) + (1.0)
        var slow55 = (1.0) / (slow41)
        var slow56 = ((slow40) * ((slow40) + (slow55))) + (1.0)
        var slow57 = (1.0) - ((slow40) * ((slow55) - (slow40)))
        var slow58 = ((slow35) * ((slow35) - (slow37))) + (1.0)
        var slow59 = (1.0) / (slow36)

        var slow60 = ((slow35) * ((slow35) + (slow59))) + (1.0)
        var slow61 = (1.0) - ((slow35) * ((slow59) - (slow35)))
        var slow62 = ((slow30) * ((slow30) - (slow32))) + (1.0)
        var slow63 = (1.0) / (slow31)
        var slow64 = ((slow30) * ((slow30) + (slow63))) + (1.0)
        var slow65 = (1.0) - ((slow30) * ((slow63) - (slow30)))
        var slow66 = ((slow25) * ((slow25) - (slow27))) + (1.0)
        var slow67 = (1.0) / (slow26)
        var slow68 = ((slow25) * ((slow25) + (slow67))) + (1.0)
        var slow69 = (1.0) - ((slow25) * ((slow67) - (slow25)))

        var slow70 = ((slow20) * ((slow20) - (slow22))) + (1.0)
        var slow71 = (1.0) / (slow21)
        var slow72 = ((slow20) * ((slow20) + (slow71))) + (1.0)
        var slow73 = (1.0) - ((slow20) * ((slow71) - (slow20)))
        var slow74 = ((slow15) * ((slow15) - (slow17))) + (1.0)
        var slow75 = (1.0) / (slow16)
        var slow76 = ((slow15) * ((slow15) + (slow75))) + (1.0)
        var slow77 = (1.0) - ((slow15) * ((slow75) - (slow15)))
        var slow78 = ((slow10) * ((slow10) - (slow12))) + (1.0)
        var slow79 = (1.0) / (slow11)

        var slow80 = ((slow10) * ((slow10) + (slow79))) + (1.0)
        var slow81 = (1.0) - ((slow10) * ((slow79) - (slow10)))
        var slow82 = ((slow5) * ((slow5) - (slow7))) + (1.0)
        var slow83 = (1.0) / (slow6)
        var slow84 = ((slow5) * ((slow5) + (slow83))) + (1.0)
        var slow85 = (1.0) - ((slow5) * ((slow83) - (slow5)))
        var slow86 = ((slow0) * ((slow0) - (slow2))) + (1.0)
        var slow87 = (1.0) / (slow1)
        var slow88 = ((slow0) * ((slow0) + (slow87))) + (1.0)
        var slow89 = (1.0) - ((slow0) * ((slow87) - (slow0)))

        var rec9_0 = dsp.rec9[S32(0)]
        var rec9_1 = dsp.rec9[S32(1)]
        var rec9_2 = dsp.rec9[S32(2)]
        var rec8_0 = dsp.rec8[S32(0)]
        var rec8_1 = dsp.rec8[S32(1)]
        var rec8_2 = dsp.rec8[S32(2)]
        var rec7_0 = dsp.rec7[S32(0)]
        var rec7_1 = dsp.rec7[S32(1)]
        var rec7_2 = dsp.rec7[S32(2)]
        var rec6_0 = dsp.rec6[S32(0)]
        var rec6_1 = dsp.rec6[S32(1)]
        var rec6_2 = dsp.rec6[S32(2)]
        var rec5_0 = dsp.rec5[S32(0)]
        var rec5_1 = dsp.rec5[S32(1)]
        var rec5_2 = dsp.rec5[S32(2)]
        var rec4_0 = dsp.rec4[S32(0)]
        var rec4_1 = dsp.rec4[S32(1)]
        var rec4_2 = dsp.rec4[S32(2)]
        var rec3_0 = dsp.rec3[S32(0)]
        var rec3_1 = dsp.rec3[S32(1)]
        var rec3_2 = dsp.rec3[S32(2)]
        var rec2_0 = dsp.rec2[S32(0)]
        var rec2_1 = dsp.rec2[S32(1)]
        var rec2_2 = dsp.rec2[S32(2)]
        var rec1_0 = dsp.rec1[S32(0)]
        var rec1_1 = dsp.rec1[S32(1)]
        var rec1_2 = dsp.rec1[S32(2)]
        var rec0_0 = dsp.rec0[S32(0)]
        var rec0_1 = dsp.rec0[S32(1)]
        var rec0_2 = dsp.rec0[S32(2)]

        for var i0 in range(S32(0), count):
            var temp0 = (slow49) * (rec9_1)
            rec9_0 = (F64(input0[i0])) - ((slow48) * (((slow50) * (rec9_2)) + (temp0)))
            var temp1 = (slow44) * (rec8_1)
            rec8_0 = ((slow48) * (((temp0) + ((slow52) * (rec9_0))) + ((slow53) * (rec9_2)))) - ((slow43) * (((slow54) * (rec8_2)) + (temp1)))
            var temp2 = (slow39) * (rec7_1)
            rec7_0 = ((slow43) * (((temp1) + ((slow56) * (rec8_0))) + ((slow57) * (rec8_2)))) - ((slow38) * (((slow58) * (rec7_2)) + (temp2)))
            var temp3 = (slow34) * (rec6_1)
            rec6_0 = ((slow38) * (((temp2) + ((slow60) * (rec7_0))) + ((slow61) * (rec7_2)))) - ((slow33) * (((slow62) * (rec6_2)) + (temp3)))
            var temp4 = (slow29) * (rec5_1)
            rec5_0 = ((slow33) * (((temp3) + ((slow64) * (rec6_0))) + ((slow65) * (rec6_2)))) - ((slow28) * (((slow66) * (rec5_2)) + (temp4)))
            var temp5 = (slow24) * (rec4_1)
            rec4_0 = ((slow28) * (((temp4) + ((slow68) * (rec5_0))) + ((slow69) * (rec5_2)))) - ((slow23) * (((slow70) * (rec4_2)) + (temp5)))
            var temp6 = (slow19) * (rec3_1)
            rec3_0 = ((slow23) * (((temp5) + ((slow72) * (rec4_0))) + ((slow73) * (rec4_2)))) - ((slow18) * (((slow74) * (rec3_2)) + (temp6)))
            var temp7 = (slow14) * (rec2_1)
            rec2_0 = ((slow18) * (((temp6) + ((slow76) * (rec3_0))) + ((slow77) * (rec3_2)))) - ((slow13) * (((slow78) * (rec2_2)) + (temp7)))
            var temp8 = (slow9) * (rec1_1)
            rec1_0 = ((slow13) * (((temp7) + ((slow80) * (rec2_0))) + ((slow81) * (rec2_2)))) - ((slow8) * (((slow82) * (rec1_2)) + (temp8)))
            var temp9 = (slow4) * (rec0_1)
            rec0_0 = ((slow8) * (((temp8) + ((slow84) * (rec1_0))) + ((slow85) * (rec1_2)))) - ((slow3) * (((slow86) * (rec0_2)) + (temp9)))
            output0[i0] = FaustFloat((slow3) * (((temp9) + ((slow88) * (rec0_0))) + ((slow89) * (rec0_2))))
            rec9_2 = rec9_1
            rec9_1 = rec9_0
            rec8_2 = rec8_1
            rec8_1 = rec8_0
            rec7_2 = rec7_1
            rec7_1 = rec7_0
            rec6_2 = rec6_1
            rec6_1 = rec6_0
            rec5_2 = rec5_1
            rec5_1 = rec5_0
            rec4_2 = rec4_1
            rec4_1 = rec4_0
            rec3_2 = rec3_1
            rec3_1 = rec3_0
            rec2_2 = rec2_1
            rec2_1 = rec2_0
            rec1_2 = rec1_1
            rec1_1 = rec1_0
            rec0_2 = rec0_1
            rec0_1 = rec0_0

        dsp.rec9[S32(0)] = rec9_0
        dsp.rec9[S32(1)] = rec9_1
        dsp.rec9[S32(2)] = rec9_2
        dsp.rec8[S32(0)] = rec8_0
        dsp.rec8[S32(1)] = rec8_1
        dsp.rec8[S32(2)] = rec8_2
        dsp.rec7[S32(0)] = rec7_0
        dsp.rec7[S32(1)] = rec7_1
        dsp.rec7[S32(2)] = rec7_2
        dsp.rec6[S32(0)] = rec6_0
        dsp.rec6[S32(1)] = rec6_1
        dsp.rec6[S32(2)] = rec6_2
        dsp.rec5[S32(0)] = rec5_0
        dsp.rec5[S32(1)] = rec5_1
        dsp.rec5[S32(2)] = rec5_2
        dsp.rec4[S32(0)] = rec4_0
        dsp.rec4[S32(1)] = rec4_1
        dsp.rec4[S32(2)] = rec4_2
        dsp.rec3[S32(0)] = rec3_0
        dsp.rec3[S32(1)] = rec3_1
        dsp.rec3[S32(2)] = rec3_2
        dsp.rec2[S32(0)] = rec2_0
        dsp.rec2[S32(1)] = rec2_1
        dsp.rec2[S32(2)] = rec2_2
        dsp.rec1[S32(0)] = rec1_0
        dsp.rec1[S32(1)] = rec1_1
        dsp.rec1[S32(2)] = rec1_2
        dsp.rec0[S32(0)] = rec0_0
        dsp.rec0[S32(1)] = rec0_1
        dsp.rec0[S32(2)] = rec0_2

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object
# and the user interface, allocates the buffers and runs the benchmark.
# ==============================================================================

def main() raises -> None:
    comptime dreal = dfaust
    comptime Real = SIMD[dreal, 1]

    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_streams[dreal](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Panic in main - Critical allocation error: ", err)
        dsp.free()
        return

    var inputs = base.unsafe_value()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs[dreal](inputs, n_ins)

    warmup[dreal](dsp[], inputs, outputs)
    var report = measure[dreal](dsp[], inputs, outputs)
    report.checksum = checksum_outputs[dreal](outputs, n_outs)
    print_report(report) # the output will be redirected via script

    comptime if WRITE_CSV:
        write_csv(report)

    free_streams[dreal](base)
    dsp.free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
