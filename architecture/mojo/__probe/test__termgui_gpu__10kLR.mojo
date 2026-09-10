# 10k persistent GPU oscillators: even indices left, odd indices right.
# Compile from architecture/mojo with -I . and link PortAudio + libtermgui.a.

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import FaustDspGpu
from gpu import global_idx
from gui import FaustGui
from meta import FaustMeta
from audio.portaudio import SAMP_RATE
from gui.terminal.gpu import run_terminal_gpu


comptime NUM_OSCS = 10_000
comptime NUM_CHAN_OSCS = NUM_OSCS // 2
comptime TWO_PI = FaustFloat(6.283185307179586)
comptime OSC_BLOCK_SIZE = 256
comptime OSC_GRID_SIZE = (NUM_OSCS + OSC_BLOCK_SIZE - 1) // OSC_BLOCK_SIZE
comptime MIX_BLOCK_SIZE = 256


struct ToneDsp(FaustDspGpu):
    var rate: S32
    var freq: FaustFloat
    var shft: FaustFloat
    var rshf: FaustFloat
    var gain: FaustFloat
    var mute: FaustFloat
    var phase: Arr[FaustFloat, NUM_OSCS]
    var peak: Arr[FaustFloat, 2]

    def __init__(out dsp):
        dsp.rate = 48_000
        dsp.freq = 220
        dsp.shft = 0
        dsp.rshf = 0
        dsp.gain = -24
        dsp.mute = 0
        dsp.phase = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0))
        dsp.peak = Arr[FaustFloat, 2](fill=FaustFloat(-90))

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
        dsp.freq = 220
        dsp.shft = 0
        dsp.rshf = 0
        dsp.gain = -24
        dsp.mute = 0

    def instance_clear(mut dsp) -> None:
        dsp.phase = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0))
        dsp.peak = Arr[FaustFloat, 2](fill=FaustFloat(-90))

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
        ui.open_vertical_box("DSP")
        ui.open_vertical_box("Controls")
        ui.open_vertical_box("Oscillators")

        ui.declare(dsp.freq, "unit", "Hz")
        ui.add_horizontal_slider(
            "freq",
            dsp.freq,
            FaustFloat(220),
            FaustFloat(40),
            FaustFloat(2000),
            FaustFloat(1)
        )
        ui.declare(dsp.shft, "unit", "Hz")
        ui.add_horizontal_slider(
            "shft",
            dsp.shft,
            FaustFloat(0),
            FaustFloat(-200),
            FaustFloat(200),
            FaustFloat(1)
        )
        ui.declare(dsp.rshf, "unit", "Hz")
        ui.add_horizontal_slider(
            "rshf",
            dsp.rshf,
            FaustFloat(0),
            FaustFloat(-200),
            FaustFloat(200),
            FaustFloat(1)
        )
        ui.declare(dsp.gain, "unit", "dB")
        ui.add_horizontal_slider(
            "gain",
            dsp.gain,
            FaustFloat(-24),
            FaustFloat(-60),
            FaustFloat(0),
            FaustFloat(0.5)
        )
        ui.add_check_button("mute", dsp.mute)

        ui.close_box()
        ui.close_box()

        ui.open_vertical_box("Outputs")
        ui.declare(dsp.peak[0], "unit", "dB")
        ui.add_horizontal_bargraph(
            "out1",
            dsp.peak[0],
            FaustFloat(-90),
            FaustFloat(0)
        )
        ui.declare(dsp.peak[1], "unit", "dB")
        ui.add_horizontal_bargraph(
            "out2",
            dsp.peak[1],
            FaustFloat(-90),
            FaustFloat(0)
        )
        ui.close_box()
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
        ctx.enqueue_function[ToneDsp.osc_kernel](
            dsp_raw,
            work_buf,
            buf_size,
            grid_dim=OSC_GRID_SIZE,
            block_dim=OSC_BLOCK_SIZE
        )

        var mix_grid_size = (
            Int(buf_size) + MIX_BLOCK_SIZE - 1
        ) // MIX_BLOCK_SIZE

        ctx.enqueue_function[ToneDsp.mix_kernel](
            work_buf,
            out_buf,
            buf_size,
            grid_dim=mix_grid_size,
            block_dim=MIX_BLOCK_SIZE
        )

        ctx.enqueue_function[ToneDsp.meter_kernel](
            dsp_raw,
            out_buf,
            buf_size,
            grid_dim=1,
            block_dim=2
        )

    @staticmethod
    def osc_kernel(
        dsp_raw: Ptr[U8, MUT_ANY],
        work_buf: Ptr[U8, MUT_ANY],
        count: S32
    ) -> None:
        comptime assert dfaust == f32, "Expected 32-bit audio precision."
        comptime assert (
            dfaust.is_floating_point()
        ), "Expected floating-point audio precision."

        var osc = Int(global_idx.x)
        if osc >= NUM_OSCS:
            return

        var dsp = dsp_raw.unsafe_bitcast[ToneDsp]()
        var output = work_buf.unsafe_bitcast[FaustFloat]()
        var phase = dsp[].phase[osc]
        var freq = max(FaustFloat(1), dsp[].freq + dsp[].shft)

        if osc % 2 != 0:
            freq = max(FaustFloat(1), freq + dsp[].rshf)

        var step = TWO_PI * freq / FaustFloat(dsp[].rate)
        var gain = pow(
            FaustFloat(10),
            dsp[].gain / FaustFloat(20)
        )

        if dsp[].mute != 0:
            gain = 0

        var offset = osc * Int(count)

        for frame in range(Int(count)):
            output[unsafe_offset=offset + frame] = (
                gain * sin(phase)
            )
            phase += step
            phase -= TWO_PI * floor(phase / TWO_PI)

        dsp[].phase[osc] = phase

    @staticmethod
    def mix_kernel(
        work_buf: Ptr[U8, MUT_ANY],
        output: MutStream,
        count: S32
    ) -> None:
        var frame = Int(global_idx.x)
        var frames = Int(count)

        if frame >= frames:
            return

        var input = work_buf.unsafe_bitcast[FaustFloat]()
        var left = FaustFloat(0)
        var right = FaustFloat(0)

        for osc in range(0, NUM_OSCS, 2):
            left += input[
                unsafe_offset=osc * frames + frame
            ]
            right += input[
                unsafe_offset=(osc + 1) * frames + frame
            ]

        var norm = FaustFloat(NUM_CHAN_OSCS)
        output[unsafe_offset=frame] = left / norm
        output[unsafe_offset=frames + frame] = right / norm

    @staticmethod
    def meter_kernel(
        dsp_raw: Ptr[U8, MUT_ANY],
        output: MutStream,
        count: S32
    ) -> None:
        comptime assert dfaust == f32, "Expected 32-bit audio precision."
        comptime assert (
            dfaust.is_floating_point()
        ), "Expected floating-point audio precision."

        var chan = Int(global_idx.x)

        if chan >= 2:
            return

        var dsp = dsp_raw.unsafe_bitcast[ToneDsp]()
        var peak = FaustFloat(0)
        var offset = chan * Int(count)

        for frame in range(Int(count)):
            peak = max(
                peak,
                abs(output[unsafe_offset=offset + frame])
            )

        dsp[].peak[chan] = max(
            FaustFloat(-90),
            FaustFloat(20) * log10(
                max(peak, FaustFloat(1e-9))
            )
        )


def main() raises -> None:
    var dsp = unsafe_alloc[ToneDsp](1)
    dsp.unsafe_write(ToneDsp())
    dsp[].init(SAMP_RATE)
    run_terminal_gpu(dsp)
