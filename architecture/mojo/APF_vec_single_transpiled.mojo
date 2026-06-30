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
# name: "APF"
# Compilation options: 
#   
#   -a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo 
#   -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single 
#   -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f32
comptime dreal_width = S32(simd_width_of[dreal]())

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F32
    var hslider0: FaustFloat
    var hslider1: FaustFloat
    var rec0_perm: Arr[F32, 4]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.hslider0 = 0.0
        dsp.hslider1 = 0.0
        dsp.rec0_perm = Arr[F32, 4](fill=0.0)

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
        dsp.const0 = (F32(6.2831855)) / (min(F32(1.92e+05), max(F32(1.0), F32(dsp.sample_rate))))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 1000.0
        dsp.hslider1 = 1.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec0_perm[l0] = F32(0.0)
            l0 = (l0) + (S32(1))

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
        return "{\"name\": \"APF\",\"filename\": \"APF.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/usr/local/share/faust/maxmsp.lib\",\"/usr/local/share/faust/maths.lib\",\"/usr/local/share/faust/platform.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/src\",\"/Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/src\"],\"size\": 32,\"inputs\": 1,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"filename\": \"APF.dsp\" },{ \"maths.lib/author\": \"GRAME\" },{ \"maths.lib/copyright\": \"GRAME\" },{ \"maths.lib/license\": \"LGPL with exception\" },{ \"maths.lib/name\": \"Faust Math Library\" },{ \"maths.lib/version\": \"2.9.0\" },{ \"maxmsp.lib/author\": \"GRAME\" },{ \"maxmsp.lib/copyright\": \"GRAME\" },{ \"maxmsp.lib/license\": \"LGPL with exception\" },{ \"maxmsp.lib/name\": \"MaxMSP compatibility Library\" },{ \"maxmsp.lib/version\": \"1.1.0\" },{ \"name\": \"APF\" },{ \"platform.lib/name\": \"Generic Platform Library\" },{ \"platform.lib/version\": \"1.3.0\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"APF\",\"items\": [ {\"type\": \"hslider\",\"label\": \"Freq\",\"varname\": \"fHslider0\",\"shortname\": \"Freq\",\"address\": \"/APF/Freq\",\"init\": 1000,\"min\": 100,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Q\",\"varname\": \"fHslider1\",\"shortname\": \"Q\",\"address\": \"/APF/Q\",\"init\": 1,\"min\": 0.01,\"max\": 100,\"step\": 0.01}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a /Users/manuelfarzini/personal/dev/repo/faust/architecture/_bench/arch/mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("filename", "APF.dsp")
        meta.declare("maths.lib/author", "GRAME")
        meta.declare("maths.lib/copyright", "GRAME")
        meta.declare("maths.lib/license", "LGPL with exception")
        meta.declare("maths.lib/name", "Faust Math Library")
        meta.declare("maths.lib/version", "2.9.0")
        meta.declare("maxmsp.lib/author", "GRAME")
        meta.declare("maxmsp.lib/copyright", "GRAME")
        meta.declare("maxmsp.lib/license", "LGPL with exception")
        meta.declare("maxmsp.lib/name", "MaxMSP compatibility Library")
        meta.declare("maxmsp.lib/version", "1.1.0")
        meta.declare("name", "APF")
        meta.declare("platform.lib/name", "Generic Platform Library")
        meta.declare("platform.lib/version", "1.3.0")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("APF")
        ui.add_horizontal_slider("Freq", dsp.hslider0, FaustFloat(1000.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("Q", dsp.hslider1, FaustFloat(1.0), FaustFloat(0.01), FaustFloat(100.0), FaustFloat(0.01))
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var slow0 = (dsp.const0) * (max(F32(0.0), F32(dsp.hslider0)))
        var slow1 = (F32(0.5)) * ((sin(slow0)) / (max(F32(0.001), F32(dsp.hslider1))))
        var slow2 = (F32(1.0)) / ((slow1) + (F32(1.0)))
        var slow3 = (F32(1.0)) - (slow1)
        var slow4 = (F32(2.0)) * (cos(slow0))
        var zec0 = Arr[F32, 4](uninitialized=True)
        var rec0_tmp = Arr[F32, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        # Main loop 
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(4))): 
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re0 = S32(4)
            # Recursive loop 0 
            # Pre code 
            var j0_re0 = S32(0)
            comptime dtype0 = f32
            comptime width0 = S32(simd_width_of[dtype0]())
            while j0_re0 <= S32(4) - width0:
                var values = simd_load(dsp.rec0_perm, j0_re0)
                simd_store(rec0_tmp, j0_re0, values)
                j0_re0 = j0_re0 + S32(width0)
            # Compute code 
            var i_re0 = S32(0)
            while (i_re0) < (vsize_re0): 
                zec0[i_re0] = (slow4) * (rec0[(i_re0) - (S32(1))])
                rec0[i_re0] = (F32(input0[i_re0])) - ((slow2) * (((slow3) * (rec0[(i_re0) - (S32(2))])) - (zec0[i_re0])))
                i_re0 = (i_re0) + (S32(1))
            # Post code 
            var j1_re0 = S32(0)
            while (j1_re0) < (S32(4)): 
                dsp.rec0_perm[j1_re0] = rec0_tmp[(vsize_re0) + (j1_re0)]
                j1_re0 = (j1_re0) + (S32(1))
            # Vectorizable loop 1 
            # Compute code 
            var i_re1 = S32(0)
            comptime dtype1 = dfaust
            comptime width1 = S32(simd_width_of[dtype1]())
            while i_re1 <= vsize_re0 - width1:
                var values = ((simd_load(rec0, i_re1 - S32(2))) + ((slow2) * (((slow3) * (simd_load(rec0, i_re1))) - (simd_load(zec0, i_re1))))).cast[dfaust]()
                simd_store(output0, i_re1, values)
                i_re1 = i_re1 + S32(width1)
            vindex_re0 = (vindex_re0) + (S32(4))
        # Remaining frames 
        if ((vindex_re0) < (count) != 0):
            var input0 = Ptr(to=input0_ptr[vindex_re0])
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            # Recursive loop 0 
            # Pre code 
            var j0_re1 = S32(0)
            comptime dtype2 = f32
            comptime width2 = S32(simd_width_of[dtype2]())
            while j0_re1 <= S32(4) - width2:
                var values = simd_load(dsp.rec0_perm, j0_re1)
                simd_store(rec0_tmp, j0_re1, values)
                j0_re1 = j0_re1 + S32(width2)
            # Compute code 
            var i_re2 = S32(0)
            while (i_re2) < (vsize_re1): 
                zec0[i_re2] = (slow4) * (rec0[(i_re2) - (S32(1))])
                rec0[i_re2] = (F32(input0[i_re2])) - ((slow2) * (((slow3) * (rec0[(i_re2) - (S32(2))])) - (zec0[i_re2])))
                i_re2 = (i_re2) + (S32(1))
            # Post code 
            var j1_re1 = S32(0)
            while (j1_re1) < (S32(4)): 
                dsp.rec0_perm[j1_re1] = rec0_tmp[(vsize_re1) + (j1_re1)]
                j1_re1 = (j1_re1) + (S32(1))
            # Vectorizable loop 1 
            # Compute code 
            var i_re3 = S32(0)
            comptime dtype3 = dfaust
            comptime width3 = S32(simd_width_of[dtype3]())
            while i_re3 <= vsize_re1 - width3:
                var values = ((simd_load(rec0, i_re3 - S32(2))) + ((slow2) * (((slow3) * (simd_load(rec0, i_re3))) - (simd_load(zec0, i_re3))))).cast[dfaust]()
                simd_store(output0, i_re3, values)
                i_re3 = i_re3 + S32(width3)

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
