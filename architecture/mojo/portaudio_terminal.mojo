from conf.prelude import *
from dsp import FaustDsp
from audio.portaudio import PortAudio, FaustFloat
from gui import FaustGui
from gui.terminal import TerminalGui


def main() -> None:
    var dsp = alloc[mydspDsp](1)
    dsp[].init(48_000)

    var gui = TerminalGui[FaustFloat.dtype]()
    dsp[].build_ui(gui)

    var driver = PortAudio()

    err = driver.init()
    if err:
        dsp.free()
        print(err)
        return

    err = driver.start(dsp[])
    if err:
        dsp.free()
        print(err)
        return

    err = gui.run()
    if err:
        dsp.free()
        print(err)
        return

    err = driver.stop()
    if err:
        dsp.free()
        print(err)
        return

    dsp.free()


