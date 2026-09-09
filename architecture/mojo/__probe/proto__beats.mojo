# probe.mojo

from max.gpu.sync import barrier
from std.sys import has_accelerator

from conf import *
from dsp import *
from gpu import *
from gui import *
from help import *
from meta import *
from audio.portaudio import *
from audio.portaudio.gpu import PortAudioGpu
from gui.proto import ProtoGui


struct ProbeDsp(FaustDspGpu):
    var sample_rate: S32
    var osc_2_freq: FaustFloat
    var phases: Arr[FaustFloat, NUM_OSCS]

    @always_inline
    def __init__(out dsp):
        dsp.sample_rate = 0
        dsp.osc_2_freq = BASE_FREQ
        dsp.phases = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0.0))

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
        dsp.osc_2_freq = BASE_FREQ

    @always_inline
    def instance_clear(mut dsp) -> None:
        dsp.phases = Arr[FaustFloat, NUM_OSCS](fill=FaustFloat(0.0))

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
        ui.open_vertical_box("Oscillators")
        ui.add_horizontal_slider(
            "Oscillator 2 frequency", dsp.osc_2_freq,
            BASE_FREQ, FaustFloat(70.0), FaustFloat(90.0), FaustFloat(0.1)
        )
        ui.close_box()

    @staticmethod
    def gpu_compute(
        dsp_raw: Ptr[U8, MUT_ANY], buf_size: S32, in_buf: ImmStream, out_buf: MutStream
    ) -> None:
        var dsp = dsp_raw.unsafe_bitcast[ProbeDsp]()
        var osc = Int(global_idx.x)

        if osc < NUM_OSCS:
            var output = out_buf.unsafe_offset(osc * Int(buf_size))
            dsp[]._compute_osc(osc, buf_size, output)

        barrier()
        if osc != 0:
            return

        var left = out_buf
        var right = out_buf.unsafe_offset(Int(buf_size))
        for frame in range(Int(buf_size)):
            var sample = left[unsafe_offset=frame] + right[unsafe_offset=frame]
            left[unsafe_offset=frame] = sample
            right[unsafe_offset=frame] = sample

    @always_inline
    def _compute_osc(
        mut dsp, osc: Int, buf_size: S32, output: Ptr[FaustFloat, MUT_NOTRK]
    ) -> None:
        var phase = dsp.phases[osc]
        var frequency = BASE_FREQ
        if osc == 1:
            frequency = dsp.osc_2_freq
        var step = TWO_PI * frequency / FaustFloat(dsp.sample_rate)

        for frame in range(Int(buf_size)):
            output[unsafe_offset=frame] = AMP * sin(phase.cast[f32]()).cast[dfaust]()
            phase += step
            if phase >= TWO_PI:
                phase -= TWO_PI

        dsp.phases[osc] = phase


comptime BASE_FREQ = FaustFloat(80.0)
comptime TWO_PI = FaustFloat(6.283185307179586)
comptime AMP = FaustFloat(0.15)
comptime NUM_OSCS = 2
comptime GPU_GRID_SIZE = 1
comptime GPU_BLOCK_SIZE = NUM_OSCS


def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32 bit float driver precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[ProbeDsp](1)
    dsp.unsafe_write(ProbeDsp())
    dsp[].init(SAMP_RATE)

    var gui = ProtoGui[dfaust]()
    dsp[].build_user_interface(gui)
    var driver = PortAudioGpu[ProbeDsp](GPU_GRID_SIZE, GPU_BLOCK_SIZE)

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
