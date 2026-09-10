# Two persistent GPU oscillators with atomic terminal controls and peak meters.
# Compile from architecture/mojo with -I . and link PortAudio + libtermgui.a.

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import FaustDspGpu
from gpu import global_idx
from gui import FaustGui
from meta import FaustMeta
from audio.portaudio import SAMP_RATE
from gui.terminal.gpu import run_terminal_gpu


comptime TWO_PI = FaustFloat(6.283185307179586)


struct ToneDsp(FaustDspGpu):
    var rate: S32
    var freq: FaustFloat
    var gain: FaustFloat
    var mute: FaustFloat
    var phase: Arr[FaustFloat, 2]
    var peak: Arr[FaustFloat, 2]

    def __init__(out dsp):
        dsp.rate = 48_000
        dsp.freq = 220
        dsp.gain = -24
        dsp.mute = 0
        dsp.phase = Arr[FaustFloat, 2](fill=FaustFloat(0))
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
        dsp.gain = -24
        dsp.mute = 0

    def instance_clear(mut dsp) -> None:
        dsp.phase = Arr[FaustFloat, 2](fill=FaustFloat(0))
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
        ui.open_vertical_box("Oscillator")
        ui.declare(dsp.freq, "unit", "Hz")
        ui.add_horizontal_slider(
            "freq", dsp.freq, FaustFloat(220), FaustFloat(40), FaustFloat(2000), FaustFloat(1)
        )
        ui.declare(dsp.gain, "unit", "dB")
        ui.add_horizontal_slider(
            "gain", dsp.gain, FaustFloat(-24), FaustFloat(-60), FaustFloat(-6), FaustFloat(0.5)
        )
        ui.add_check_button("mute", dsp.mute)
        ui.close_box()
        ui.close_box()
        ui.open_vertical_box("Outputs")
        ui.declare(dsp.peak[0], "unit", "dB")
        ui.add_horizontal_bargraph("out1", dsp.peak[0], FaustFloat(-90), FaustFloat(0))
        ui.declare(dsp.peak[1], "unit", "dB")
        ui.add_horizontal_bargraph("out2", dsp.peak[1], FaustFloat(-90), FaustFloat(0))
        ui.close_box()
        ui.close_box()

    @staticmethod
    def gpu_work_size(buf_size: S32) -> Int:
        return 0

    @staticmethod
    def gpu_compute(
        mut ctx: DeviceContext,
        imm dsp_raw: DeviceBuffer[u8],
        imm in_buf: DeviceBuffer[dfaust],
        imm out_buf: DeviceBuffer[dfaust],
        imm work_buf: DeviceBuffer[u8],
        buf_size: S32
    ) raises -> None:
        ctx.enqueue_function[ToneDsp.compute_kernel](
            dsp_raw, out_buf, buf_size, grid_dim=1, block_dim=2
        )

    @staticmethod
    def compute_kernel(
        dsp_raw: Ptr[U8, MUT_ANY], output: MutStream, count: S32
    ) -> None:
        comptime assert dfaust.is_floating_point(), "Expected floating-point DSP precision."
        var chan = Int(global_idx.x)
        if chan >= 2:
            return

        var dsp = dsp_raw.unsafe_bitcast[ToneDsp]()
        var phase = dsp[].phase[chan]
        # A fifth apart makes the stereo channels easy to distinguish.
        var ratio = FaustFloat(1) if chan == 0 else FaustFloat(1.5)
        var step = TWO_PI * dsp[].freq * ratio / FaustFloat(dsp[].rate)
        var gain = pow(FaustFloat(10), dsp[].gain / FaustFloat(20))
        if dsp[].mute != 0:
            gain = 0

        var peak = FaustFloat(0)
        var offset = chan * Int(count)
        for frame in range(Int(count)):
            var sample = gain * sin(phase)
            output[unsafe_offset=offset + frame] = sample
            peak = max(peak, abs(sample))
            phase += step
            phase -= TWO_PI * floor(phase / TWO_PI)

        # Each thread writes only its channel's state and meter.
        dsp[].phase[chan] = phase
        dsp[].peak[chan] = max(FaustFloat(-90), FaustFloat(20) * log10(max(peak, FaustFloat(1e-9))))


def main() raises -> None:
    var dsp = unsafe_alloc[ToneDsp](1)
    dsp.unsafe_write(ToneDsp())
    dsp[].init(SAMP_RATE)
    run_terminal_gpu(dsp)
