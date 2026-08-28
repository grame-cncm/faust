# pa-gpu.mojo

# ==============================================================================
# Reference architecture for PortAudio GPU.
# ==============================================================================

from std.sys import has_accelerator

from conf import *
from dsp import *
from gui import *
from help import *
from meta import *
from audio.portaudio import *
from audio.portaudio.gpu import PortAudioGpu

from dsp.proto import ProtoDsp

# <<includeIntrinsic>>
# <<includeclass>>

comptime GPU_GRID_SIZE = 1
comptime GPU_BLOCK_SIZE = 1


def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32 bit float driver precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[ProtoDsp](1)
    dsp.unsafe_write(ProtoDsp())
    dsp[].init(SAMP_RATE)

    var driver = PortAudioGpu[ProtoDsp](GPU_GRID_SIZE, GPU_BLOCK_SIZE)
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
