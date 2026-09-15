# 10k persistent GPU oscillators, each rendering three harmonic partials.
# Compile from architecture/mojo with PortAudio and native libtermgui.a.

from max.gpu.host import DeviceBuffer, DeviceContext
from std.sys import has_accelerator

from conf import *
from dsp import FaustDspGpu
from dsp.adapter import AdapterDsp
from gpu import global_idx
from gui import FaustGui
from meta import FaustMeta
from audio.portaudio import PortAudio, SAMP_RATE, BUFF_SIZE
from gui.map import GpuControlMap, build_gpu_control_map
from gui.terminal.terminal import TerminalGui
from gui.terminal.ffi import error_str
from gpu.device import GpuDevice


comptime NUM_OSCS = 10_000
comptime NUM_PARTIALS = 3
comptime BASE_FREQ = FaustFloat(220)
comptime TWO_PI = FaustFloat(6.283185307179586)
comptime GAIN = FaustFloat(0.00001)
comptime OSC_BLOCK_SIZE = 256
comptime OSC_GRID_SIZE = (NUM_OSCS + OSC_BLOCK_SIZE - 1) // OSC_BLOCK_SIZE
comptime MIX_BLOCK_SIZE = 256


struct ProbeDsp(FaustDspGpu):
    var rate:   S32
    var freq:   FaustFloat
    var phase:  Arr[FaustFloat, NUM_OSCS]

    def __init__(out dsp):
        dsp.rate = 48_000
        dsp.freq = BASE_FREQ
        dsp.phase = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0))

    def get_num_inputs(imm dsp) -> S32:
        return 0

    def get_num_outputs(imm dsp) -> S32:
        return 2

    def get_sample_rate(imm dsp) -> S32:
        return dsp.rate

    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.rate = sample_rate

    def instance_reset_user_interface(mut dsp) -> None:
        dsp.freq = BASE_FREQ

    def instance_clear(mut dsp) -> None:
        dsp.phase = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0))

    def instance_init(mut dsp, imm sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    def init(mut dsp, imm sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    def get_json(imm dsp) -> String:
        return ""

    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        pass

    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("10k stress")
        ui.declare(dsp.freq, "unit", "Hz")
        ui.add_horizontal_slider(
            "freq", dsp.freq,
            BASE_FREQ, FaustFloat(60), FaustFloat(1000), FaustFloat(1)
        )
        ui.close_box()

    @staticmethod
    def gpu_work_size(imm count: S32) -> Int:
        return NUM_OSCS * Int(count) * size_of[FaustFloat]()

    @staticmethod
    def gpu_compute(
        mut ctx:       DeviceContext,
        imm dsp_raw:   DeviceBuffer[u8],
        imm in_buf:    DeviceBuffer[dfaust],
        imm out_buf:   DeviceBuffer[dfaust],
        imm work_buf:  DeviceBuffer[u8],
        imm count:     S32
    ) raises -> None:
        ctx.enqueue_function[ProbeDsp.osc_kernel](
            dsp_raw, work_buf, count,
            grid_dim=OSC_GRID_SIZE, block_dim=OSC_BLOCK_SIZE
        )

        var mix_grid = (Int(count) + MIX_BLOCK_SIZE - 1) // MIX_BLOCK_SIZE
        ctx.enqueue_function[ProbeDsp.mix_kernel](
            work_buf, out_buf, count,
            grid_dim=mix_grid, block_dim=MIX_BLOCK_SIZE
        )

    @staticmethod
    def osc_kernel(
        dsp_raw: Ptr[U8, MUT_ANY], work_buf: Ptr[U8, MUT_ANY], count: S32
    ) -> None:
        comptime assert dfaust.is_floating_point(), "Expected float DSP precision."

        var osc = Int(global_idx.x)
        if osc >= NUM_OSCS:
            return

        var dsp = dsp_raw.unsafe_bitcast[ProbeDsp]()
        var samples = work_buf.unsafe_bitcast[FaustFloat]()
        var phase = dsp[].phase[osc]
        var step = TWO_PI * dsp[].freq / FaustFloat(dsp[].rate)
        var offset = osc * Int(count)

        for frame in range(Int(count)):
            var sample = FaustFloat(0)
            for partial in range(1, NUM_PARTIALS + 1):
                sample += sin(FaustFloat(partial) * phase) / FaustFloat(partial)
            samples[unsafe_offset=offset + frame] = GAIN * sample
            phase += step
            phase -= TWO_PI * floor(phase / TWO_PI)

        dsp[].phase[osc] = phase

    @staticmethod
    def mix_kernel(
        work_buf: Ptr[U8, MUT_ANY], output: MutStream, count: S32
    ) -> None:
        var frame = Int(global_idx.x)
        var frames = Int(count)
        if frame >= frames:
            return

        var samples = work_buf.unsafe_bitcast[FaustFloat]()
        var mix = FaustFloat(0)
        for osc in range(NUM_OSCS):
            mix += samples[unsafe_offset=osc * frames + frame]

        output[unsafe_offset=frame] = mix
        output[unsafe_offset=frames + frame] = mix


def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32-bit audio precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[ProbeDsp](1)
    dsp.unsafe_write(ProbeDsp())
    dsp[].init(SAMP_RATE)
    var ui = unsafe_alloc[TerminalGui](1)
    ui.unsafe_write(TerminalGui())
    dsp[].build_user_interface(ui[])
    var map = unsafe_alloc[GpuControlMap](1)
    map.unsafe_write(GpuControlMap())
    var gpu = unsafe_alloc[GpuDevice[ProbeDsp]](1)
    gpu.unsafe_write(GpuDevice[ProbeDsp]())
    var driver = unsafe_alloc[PortAudio](1)
    driver.unsafe_write(PortAudio())
    var err = ui[].check()
    if not err:
        err = build_gpu_control_map(dsp, map[])
    if not err:
        err = gpu[].prepare(dsp, map[], BUFF_SIZE)

    var adapter = unsafe_alloc[AdapterDsp[ProbeDsp]](1)
    adapter.unsafe_write(AdapterDsp[ProbeDsp](dsp, gpu))
    if not err:
        err = driver[].init()
    if not err:
        err = driver[].start(adapter)
    if not err:
        err = ui[].run()

    var term = ui[].stop()
    var end = driver[].stop()
    if driver[].stream != None:
        # A failed close may leave the callback accessing host memory.
        print("PortAudio close failed:", end)
        return
    var gpu_err = gpu[].get_error()
    var released = gpu[].release()
    if gpu[].state != None:
        # DMA completion is unknown; leave host and device memory intact.
        print("GPU release failed:", released)
        return
    ui[].close()
    adapter.unsafe_free()
    driver.unsafe_free()
    gpu.unsafe_free()
    map.unsafe_free()
    comptime assert conforms_to(TerminalGui, Deinitable), (
        "Terminal GUI owns widget strings."
    )
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
