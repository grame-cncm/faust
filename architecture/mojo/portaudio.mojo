from conf.prelude import *
from dsp import FaustDsp
from audio.portaudio import PortAudio, FaustFloat


def main() -> None:
    var dsp = alloc[mydspDsp](1)
    dsp[].init(48_000)

    var driver = PortAudio()

    err = driver.init()

    if not err:
        err = driver.start(dsp[])

    if not err:
        err = driver.stop()

    if err:
        dsp.free()
        print(err)
        return

    dsp.free()
    print("done")


