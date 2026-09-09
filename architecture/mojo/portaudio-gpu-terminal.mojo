# portaudio-gpu-terminal.mojo

from std.sys import has_accelerator

from conf import *
from dsp import *
from gui import *
from help import *
from meta import *
from audio.portaudio import *
from audio.portaudio.gpu import PortAudioGpu
from gui.terminal import TerminalGui

# <<includeIntrinsic>>
# <<includeclass>>

def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32 bit float driver precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[mydsp](1)
    dsp.unsafe_write(mydsp())
    dsp[].init(SAMP_RATE)

    var gui = TerminalGui[dfaust]()
    dsp[].build_user_interface(gui)
    var driver = PortAudioGpu[mydsp]()

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
