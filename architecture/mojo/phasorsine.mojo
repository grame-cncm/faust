# Faust architecture for PortAudio GPU with the native terminal GUI.
# The injected PhasorSine must implement FaustDspGpu (gpu_work_size/gpu_compute).
# Link gui/terminal/native/build/libtermgui.a and PortAudio.

from conf import *
from dsp import *
from gui import *
from gpu import *
from help import *
from meta import *
from audio.portaudio import *
from std.sys import has_accelerator
from dsp.adapter import AdapterDsp
from gui.map import GpuControlMap, build_gpu_control_map
from gui.terminal.terminal import TerminalGui
from gui.terminal.ffi import error_str
from gpu.device import GpuDevice

# ==============================================================================
# Code generated with Faust 2.87.10 (https://faust.grame.fr)
# name: "phasorsine"
# Compilation options: 
#   -a portaudio-terminal-gpu.mojo -lang mojo -fpga-mem-th 4 -ct 1 
#   -cn PhasorSine -es 1 -gpu -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec 
#   -lv 0 -vs 32
# ==============================================================================
struct PhasorSineWork:
    var rec0_tmp: Arr[F64, 36]
    var slow0: F64
    var slow1: F64
    var zec0: Arr[F64, 32]


@fieldwise_init
struct PhasorSine(FaustDspGpu):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var hslider0: FaustFloat
    var rec0_perm: Arr[F64, 4]
    var hslider1: FaustFloat
    var checkbox0: FaustFloat

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = S32(0)
        dsp.const0 = F64(0)
        dsp.hslider0 = FaustFloat(0)
        dsp.rec0_perm = Arr[F64, 4](fill=F64(0))
        dsp.hslider1 = FaustFloat(0)
        dsp.checkbox0 = FaustFloat(0)

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 2

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = (F64(1.0)) / (F64(max(S32(1), dsp.sample_rate)))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 220.0
        dsp.hslider1 = 0.1
        dsp.checkbox0 = 0.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec0_perm[l0] = F64(0.0)
            l0 = (l0) + (S32(1))

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
        return "{\"name\": \"phasorsine\",\"filename\": \"phasorsine.dsp\",\"version\": \"2.87.10\",\"compile_options\": \"-a portaudio-terminal-gpu.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn PhasorSine -es 1 -gpu -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/build/bin//share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/src\"],\"size\": 68,\"inputs\": 0,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a portaudio-terminal-gpu.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn PhasorSine -es 1 -gpu -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32\" },{ \"filename\": \"phasorsine.dsp\" },{ \"name\": \"phasorsine\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"phasorsine\",\"items\": [ {\"type\": \"hslider\",\"label\": \"freq\",\"varname\": \"fHslider0\",\"shortname\": \"freq\",\"address\": \"/phasorsine/freq\",\"meta\": [{ \"unit\": \"Hz\" }],\"init\": 220,\"min\": 20,\"max\": 2000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"gain\",\"varname\": \"fHslider1\",\"shortname\": \"gain\",\"address\": \"/phasorsine/gain\",\"init\": 0.1,\"min\": 0,\"max\": 0.5,\"step\": 0.005},{\"type\": \"checkbox\",\"label\": \"mute\",\"varname\": \"fCheckbox0\",\"shortname\": \"mute\",\"address\": \"/phasorsine/mute\"}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a portaudio-terminal-gpu.mojo -lang mojo -fpga-mem-th 4 -ct 1 -cn PhasorSine -es 1 -gpu -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 32")
        meta.declare("filename", "phasorsine.dsp")
        meta.declare("name", "phasorsine")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("phasorsine")
        ui.declare(dsp.hslider0, "unit", "Hz")
        ui.add_horizontal_slider("freq", dsp.hslider0, FaustFloat(220.0), FaustFloat(20.0), FaustFloat(2000.0), FaustFloat(1.0))
        ui.add_horizontal_slider("gain", dsp.hslider1, FaustFloat(0.1), FaustFloat(0.0), FaustFloat(0.5), FaustFloat(0.005))
        ui.add_check_button("mute", dsp.checkbox0)
        ui.close_box()

    @staticmethod
    def gpu_work_size(imm count: S32) -> Int:
        return size_of[PhasorSineWork]()

    @always_inline
    @staticmethod
    def gpu_compute(
        mut ctx:       DeviceContext,
        imm dsp_raw:   DeviceBuffer[u8],
        imm in_buf:    DeviceBuffer[dfaust],
        imm out_buf:   DeviceBuffer[dfaust],
        imm work_buf:  DeviceBuffer[u8],
        imm count:     S32
    ) raises -> None:
        if count <= 0:
            return
        ctx.enqueue_function[PhasorSine.gpu_controls](
            dsp_raw,
            in_buf,
            out_buf,
            work_buf,
            count,
            count,
            S32(0),
            grid_dim=1,
            block_dim=1
        )
        var offset = S32(0)
        while offset < count:
            var size = min(S32(32), count - offset)
            ctx.enqueue_function[PhasorSine.gpu_stage_0](
                dsp_raw,
                in_buf,
                out_buf,
                work_buf,
                count,
                size,
                offset,
                grid_dim=1,
                block_dim=1
            )
            ctx.enqueue_function[PhasorSine.gpu_stage_1](
                dsp_raw,
                in_buf,
                out_buf,
                work_buf,
                count,
                size,
                offset,
                grid_dim=1,
                block_dim=1
            )
            ctx.enqueue_function[PhasorSine.gpu_stage_2](
                dsp_raw,
                in_buf,
                out_buf,
                work_buf,
                count,
                size,
                offset,
                grid_dim=1,
                block_dim=1
            )
            ctx.enqueue_function[PhasorSine.gpu_stage_3](
                dsp_raw,
                in_buf,
                out_buf,
                work_buf,
                count,
                size,
                offset,
                grid_dim=1,
                block_dim=1
            )
            offset += size

    @staticmethod
    def gpu_controls(
        dsp_raw:    Ptr[U8, MUT_ANY],
        ins:        Ptr[FaustFloat, MUT_ANY],
        outs:       Ptr[FaustFloat, MUT_ANY],
        work_raw:   Ptr[U8, MUT_ANY],
        fullcount:  S32,
        count:      S32,
        offset:     S32
    ) -> None:
        if Int(global_idx.x) != 0:
            return
        var dsp = dsp_raw.unsafe_bitcast[PhasorSine]()
        var work = work_raw.unsafe_bitcast[PhasorSineWork]()
        var rec0 = Ptr(to=work[].rec0_tmp[S32(4)])
        var output0 = Ptr(to=outs[unsafe_offset=0 * Int(fullcount) + Int(offset)])
        var output1 = Ptr(to=outs[unsafe_offset=1 * Int(fullcount) + Int(offset)])
        work[].slow0 = (dsp[].const0) * (F64(dsp[].hslider0))
        work[].slow1 = (F64(dsp[].hslider1)) * ((F64(1.0)) - (F64(dsp[].checkbox0)))
        

    @staticmethod
    def gpu_stage_0(
        dsp_raw:    Ptr[U8, MUT_ANY],
        ins:        Ptr[FaustFloat, MUT_ANY],
        outs:       Ptr[FaustFloat, MUT_ANY],
        work_raw:   Ptr[U8, MUT_ANY],
        fullcount:  S32,
        count:      S32,
        offset:     S32
    ) -> None:
        var dsp = dsp_raw.unsafe_bitcast[PhasorSine]()
        var work = work_raw.unsafe_bitcast[PhasorSineWork]()
        var rec0 = Ptr(to=work[].rec0_tmp[S32(4)])
        var output0 = Ptr(to=outs[unsafe_offset=0 * Int(fullcount) + Int(offset)])
        var output1 = Ptr(to=outs[unsafe_offset=1 * Int(fullcount) + Int(offset)])
        var task = Int(global_idx.x)
        if task == 0:
            var j0_0 = S32(0)
            while (j0_0) < (S32(4)):
                work[].rec0_tmp[j0_0] = dsp[].rec0_perm[j0_0]
                j0_0 = (j0_0) + (S32(1))
            var i_1 = S32(0)
            while (i_1) < (count):
                rec0[unsafe_offset = i_1] = mod((work[].slow0) + (rec0[unsafe_offset = (i_1) - (S32(1))]), F64(1.0))
                i_1 = (i_1) + (S32(1))
            var j1_2 = S32(0)
            while (j1_2) < (S32(4)):
                dsp[].rec0_perm[j1_2] = work[].rec0_tmp[(count) + (j1_2)]
                j1_2 = (j1_2) + (S32(1))
                

    @staticmethod
    def gpu_stage_1(
        dsp_raw:    Ptr[U8, MUT_ANY],
        ins:        Ptr[FaustFloat, MUT_ANY],
        outs:       Ptr[FaustFloat, MUT_ANY],
        work_raw:   Ptr[U8, MUT_ANY],
        fullcount:  S32,
        count:      S32,
        offset:     S32
    ) -> None:
        var dsp = dsp_raw.unsafe_bitcast[PhasorSine]()
        var work = work_raw.unsafe_bitcast[PhasorSineWork]()
        var rec0 = Ptr(to=work[].rec0_tmp[S32(4)])
        var output0 = Ptr(to=outs[unsafe_offset=0 * Int(fullcount) + Int(offset)])
        var output1 = Ptr(to=outs[unsafe_offset=1 * Int(fullcount) + Int(offset)])
        var task = Int(global_idx.x)
        if task == 0:
            var i_0 = S32(0)
            while (i_0) < (count):
                work[].zec0[i_0] = (work[].slow1) * (sin((F64(6.283185307179586)) * (rec0[unsafe_offset = i_0])))
                i_0 = (i_0) + (S32(1))
                

    @staticmethod
    def gpu_stage_2(
        dsp_raw:    Ptr[U8, MUT_ANY],
        ins:        Ptr[FaustFloat, MUT_ANY],
        outs:       Ptr[FaustFloat, MUT_ANY],
        work_raw:   Ptr[U8, MUT_ANY],
        fullcount:  S32,
        count:      S32,
        offset:     S32
    ) -> None:
        var dsp = dsp_raw.unsafe_bitcast[PhasorSine]()
        var work = work_raw.unsafe_bitcast[PhasorSineWork]()
        var rec0 = Ptr(to=work[].rec0_tmp[S32(4)])
        var output0 = Ptr(to=outs[unsafe_offset=0 * Int(fullcount) + Int(offset)])
        var output1 = Ptr(to=outs[unsafe_offset=1 * Int(fullcount) + Int(offset)])
        var task = Int(global_idx.x)
        if task == 0:
            var i_0 = S32(0)
            while (i_0) < (count):
                output0[unsafe_offset=i_0] = FaustFloat(work[].zec0[i_0])
                i_0 = (i_0) + (S32(1))
                

    @staticmethod
    def gpu_stage_3(
        dsp_raw:    Ptr[U8, MUT_ANY],
        ins:        Ptr[FaustFloat, MUT_ANY],
        outs:       Ptr[FaustFloat, MUT_ANY],
        work_raw:   Ptr[U8, MUT_ANY],
        fullcount:  S32,
        count:      S32,
        offset:     S32
    ) -> None:
        var dsp = dsp_raw.unsafe_bitcast[PhasorSine]()
        var work = work_raw.unsafe_bitcast[PhasorSineWork]()
        var rec0 = Ptr(to=work[].rec0_tmp[S32(4)])
        var output0 = Ptr(to=outs[unsafe_offset=0 * Int(fullcount) + Int(offset)])
        var output1 = Ptr(to=outs[unsafe_offset=1 * Int(fullcount) + Int(offset)])
        var task = Int(global_idx.x)
        if task == 0:
            var i_0 = S32(0)
            while (i_0) < (count):
                output1[unsafe_offset=i_0] = FaustFloat(work[].zec0[i_0])
                i_0 = (i_0) + (S32(1))
                


def main() -> None:
    comptime assert dfaust == FaustFloat.dtype, "Expected 32-bit audio precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[PhasorSine](1)
    dsp.unsafe_write(PhasorSine())
    dsp[].init(SAMP_RATE)
    var ui = unsafe_alloc[TerminalGui](1)
    ui.unsafe_write(TerminalGui())
    dsp[].build_user_interface(ui[])
    var map = unsafe_alloc[GpuControlMap](1)
    map.unsafe_write(GpuControlMap())
    var gpu = unsafe_alloc[GpuDevice[PhasorSine]](1)
    gpu.unsafe_write(GpuDevice[PhasorSine]())
    var driver = unsafe_alloc[PortAudio](1)
    driver.unsafe_write(PortAudio())
    var err = ui[].check()
    if not err:
        err = build_gpu_control_map(dsp, map[])
    if not err:
        err = gpu[].prepare(dsp, map[], BUFF_SIZE)

    var adapter = unsafe_alloc[AdapterDsp[PhasorSine]](1)
    adapter.unsafe_write(AdapterDsp[PhasorSine](dsp, gpu))
    if not err:
        err = driver[].init()
    if not err:
        err = driver[].start(adapter)
    if not err:
        err = ui[].run()

    # Restore the terminal before verifying that the callback stopped.
    var term = ui[].stop()
    var end = driver[].stop()
    if driver[].stream != None:
        # Leave callback-reachable allocations intact if stream close failed.
        print("PortAudio close failed:", end)
        return
    var gpu_err = gpu[].get_error()
    var released = gpu[].release()
    if gpu[].state != None:
        # Leave device and host buffers intact if DMA completion is unknown.
        print("GPU release failed:", released)
        return
    ui[].close()
    adapter.unsafe_free()
    driver.unsafe_free()
    gpu.unsafe_free()
    map.unsafe_free()
    ui.unsafe_deinit_pointee()
    ui.unsafe_free()
    dsp.unsafe_free()
    if not err:
        err = term
    if not err:
        err = gpu_err
    if not err:
        err = released
    if not err:
        err = end
    if err:
        if err > 0:
            print(error_str(err))
        else:
            print("GPU audio error:", err)
        return
    print("done")
