# parallel_noise_new_05.mojo

from max.gpu.host import DeviceBuffer, DeviceContext
from std.sys import has_accelerator

from conf import *
from dsp import *
from gpu import *
from gui import *
from help import *
from meta import *
from audio.portaudio import *
from audio.portaudio.gpu import PortAudioGpu
from gui.terminal import TerminalGui


@always_inline
def random01(index: Int, salt: F32) -> FaustFloat:
    var value = sin(F32(index) * F32(12.9898) + salt) * F32(43758.5453)
    return FaustFloat(value - floor(value))


struct ProbeDsp(FaustDspGpu):
    var sample_rate: S32
    var freq_shift: FaustFloat
    var phases: Arr[FaustFloat, NUM_OSCS]
    var amplitudes: Arr[FaustFloat, NUM_OSCS]

    @always_inline
    def __init__(out dsp):
        dsp.sample_rate = 0
        dsp.freq_shift = FaustFloat(0.0)
        dsp.phases = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0.0))
        dsp.amplitudes = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0.0))

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 0

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 2

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.freq_shift = FaustFloat(0.0)

    @always_inline
    def instance_clear(mut dsp) -> None:
        for osc in range(NUM_OSCS):
            dsp.phases[osc] = TWO_PI * random01(osc, F32(0.0))
            var variation = FaustFloat(2.0) * random01(osc, F32(78.233)) - FaustFloat(1.0)
            dsp.amplitudes[osc] = GAIN * (FaustFloat(1.0) + AMP_RANDOMNESS * variation)

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
        return ""

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        pass

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("Parallel noise")
        ui.add_horizontal_slider(
            "Global frequency shift", dsp.freq_shift,
            FaustFloat(0.0), FaustFloat(-50.0), FaustFloat(50.0), FaustFloat(0.1)
        )
        ui.close_box()

    @staticmethod
    def gpu_work_size(buf_size: S32) -> Int:
        return NUM_OSCS * Int(buf_size) * size_of[FaustFloat]()

    @staticmethod
    def gpu_compute(
        mut ctx: DeviceContext,
        imm dsp_raw: DeviceBuffer[u8],
        imm in_buf: DeviceBuffer[dfaust],
        imm out_buf: DeviceBuffer[dfaust],
        imm work_buf: DeviceBuffer[u8],
        buf_size: S32
    ) raises -> None:
        ctx.enqueue_function[ProbeDsp.osc_kernel](
            dsp_raw, work_buf, buf_size,
            grid_dim=OSC_GRID_SIZE, block_dim=OSC_BLOCK_SIZE
        )

        var frames = Int(buf_size)
        var mix_grid_size = (frames + MIX_BLOCK_SIZE - 1) // MIX_BLOCK_SIZE
        ctx.enqueue_function[ProbeDsp.mix_kernel](
            work_buf, out_buf, buf_size,
            grid_dim=mix_grid_size, block_dim=MIX_BLOCK_SIZE
        )

    @staticmethod
    def osc_kernel(
        dsp_raw: Ptr[U8, MUT_ANY], work_buf: Ptr[U8, MUT_ANY], buf_size: S32
    ) -> None:
        var osc = Int(global_idx.x)
        if osc >= NUM_OSCS:
            return

        var dsp = dsp_raw.unsafe_bitcast[ProbeDsp]()
        var samples = work_buf.unsafe_bitcast[FaustFloat]()
        dsp[]._compute_osc(osc, buf_size, samples)

    @staticmethod
    def mix_kernel(
        work_buf: Ptr[U8, MUT_ANY], out_buf: MutStream, buf_size: S32
    ) -> None:
        var frame = Int(global_idx.x)
        var frames = Int(buf_size)
        if frame >= frames:
            return

        var samples = work_buf.unsafe_bitcast[FaustFloat]()
        var sample = FaustFloat(0.0)
        for osc in range(NUM_OSCS):
            sample += samples[unsafe_offset=osc * frames + frame]

        out_buf[unsafe_offset=frame] = sample
        out_buf[unsafe_offset=frames + frame] = sample

    @always_inline
    def _compute_osc(
        mut dsp,
        osc: Int,
        buf_size: S32,
        samples: Ptr[FaustFloat, MUT_ANY]
    ) -> None:
        var phase = dsp.phases[osc]
        var amplitude = dsp.amplitudes[osc]
        var frequency = MIN_FREQ + FREQ_STEP * FaustFloat(osc) + dsp.freq_shift
        var step = TWO_PI * frequency / FaustFloat(dsp.sample_rate)
        var offset = osc * Int(buf_size)

        for frame in range(Int(buf_size)):
            samples[unsafe_offset=offset + frame] = (
                amplitude * sin(phase.cast[f32]()).cast[dfaust]()
            )
            phase += step
            if phase >= TWO_PI:
                phase -= TWO_PI

        dsp.phases[osc] = phase


comptime NUM_OSCS = 10_000
comptime MIN_FREQ = FaustFloat(60.0)
comptime MAX_FREQ = FaustFloat(10060.0)
comptime FREQ_STEP = (MAX_FREQ - MIN_FREQ) / FaustFloat(NUM_OSCS - 1)
comptime TWO_PI = FaustFloat(6.283185307179586)
comptime GAIN = FaustFloat(0.00002)
comptime AMP_RANDOMNESS = FaustFloat(0.1)
comptime OSC_BLOCK_SIZE = 256
comptime OSC_GRID_SIZE = (NUM_OSCS + OSC_BLOCK_SIZE - 1) // OSC_BLOCK_SIZE
comptime MIX_BLOCK_SIZE = 256


def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32 bit float driver precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[ProbeDsp](1)
    dsp.unsafe_write(ProbeDsp())
    dsp[].init(SAMP_RATE)

    var gui = TerminalGui[dfaust]()
    dsp[].build_user_interface(gui)
    var driver = PortAudioGpu[ProbeDsp]()

    var err = driver.init()
    if not err:
        err = driver.start(dsp)
    if not err:
        err = gui.run()
    if not err:
        err = driver.stop()
    if not err:
        dsp.unsafe_free()
        print("done")
        return

    print(err)
    _ = driver.stop()
    dsp.unsafe_free()
