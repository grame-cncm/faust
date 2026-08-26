# ==============================================================================
# ... General description
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from help import *
from dsp import *
from gui import *
from meta import *
from audio.portaudio import *

from dsp.gpu import FaustGpuDsp

from dsp.proto import ProtoDsp

# ==============================================================================
# First section of architecture provided code end.
# <<includeIntrinsic>>  # to be uncommented
# <<includeclass>>      # to be uncommented
# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the DSP object,
# wraps the DSP in a GPU device, initialized the audio driver, starts the audio
# thread and blocks the main thread to allow the driver to run the GPU device.
# ==============================================================================

def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32 bit float driver precision."

    var dsp = unsafe_alloc[ProtoDsp](1)
    var gpu = unsafe_alloc[FaustGpuDsp[ProtoDsp]](1)
    dsp.unsafe_write(ProtoDsp())
    gpu.unsafe_write(FaustGpuDsp(dsp))

    gpu[].init(SAMP_RATE)

    var driver = PortAudio()
    var err = driver.init()
    if err:
        print(err)
        gpu.unsafe_free()
        dsp.unsafe_free()
        return

    err = driver.start(gpu)
    if err:
        print(err)
        gpu.unsafe_free()
        dsp.unsafe_free()
        return

    err = wait_stdin()
    if err:
        gpu.unsafe_free()
        dsp.unsafe_free()
        return

    err = driver.stop()
    if err:
        print(err)
        gpu.unsafe_free()
        return

    gpu.unsafe_free()
    print("done")

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
