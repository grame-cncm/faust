# audio/audio.mojo

from conf import *
from dsp import FaustDsp

# --------------------------------------------------------------
# FaustAudio interface declaration.
# General contract for Audio architectures.
# --------------------------------------------------------------

trait FaustAudio:
    @always_inline
    def init(mut driver) -> S32: ...
    @always_inline
    def start[Dsp: FaustDsp](mut driver, mut dsp: Dsp) -> S32: ...
    @always_inline
    def stop(mut driver) -> S32: ...
