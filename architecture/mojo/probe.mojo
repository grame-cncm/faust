# pa-gpu.mojo

# ==============================================================================
# Probe file to prototype hardcoded Dsp shapes
# ==============================================================================

from std.sys import has_accelerator

from conf import *
from dsp import *
from gpu import *
from gui import *
from help import *
from meta import *
from audio.portaudio import *
from audio.portaudio.gpu import PortAudioGpu

struct ProbeDsp(FaustDsp):
    var sample_rate: S32
    var phases: Arr[FaustFloat, NUM_OSCS]

    @always_inline
    def __init__(out dsp):
        dsp.sample_rate = 0
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
        pass

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
        pass

    @always_inline
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        var osc = Int(global_idx.x)
        if osc >= NUM_OSCS:
            return

        var output = outputs[unsafe_offset=osc]
        var phase = dsp.phases[osc]
        var frequency = FaustFloat(55 * (osc + 1))
        var step = TWO_PI * frequency / FaustFloat(dsp.sample_rate)

        for frame in range(Int(count)):
            output[unsafe_offset=frame] = AMP * sin(phase.cast[f32]()).cast[dfaust]()
            phase += step

            if phase >= TWO_PI:
                phase -= TWO_PI

        dsp.phases[osc] = phase


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

    var driver = PortAudioGpu[ProbeDsp](GPU_GRID_SIZE, GPU_BLOCK_SIZE)
    var err = driver.init()
    if err:
        dsp.unsafe_free()
        print(err)
        return

    err = driver.start(dsp)
    if err:
        _ = driver.stop()
        dsp.unsafe_free()
        print(e)
        return

    err = wait_stdin()
    if err:
        _ = driver.stop()
        dsp.unsafe_free()
        print(err)
        return

    err = driver.stop()
    if err:
        dsp.unsafe_free()
        print(err)
        return

    dsp.unsafe_free()
    print("done")
