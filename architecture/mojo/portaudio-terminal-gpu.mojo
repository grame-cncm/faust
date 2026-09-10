# Faust architecture for PortAudio GPU with the native terminal GUI.
# The injected mydsp must implement FaustDspGpu (gpu_work_size/gpu_compute).
# Link gui/terminal/native/build/libtermgui.a and PortAudio.

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import *
from gpu import *
from gui import *
from help import *
from meta import *
from audio.portaudio import *
from gui.terminal.gpu import run_terminal_gpu

<<includeIntrinsic>>
<<includeclass>>


def main() raises -> None:
    var dsp = unsafe_alloc[mydsp](1)
    dsp.unsafe_write(mydsp())
    dsp[].init(SAMP_RATE)
    run_terminal_gpu(dsp)
