# audio/audio.mojo

from conf import *
from dsp.dsp import FaustDsp

# ==============================================================
# FaustAudio interface declaration.
# General contract for Audio architectures.
# ==============================================================

trait FaustAudio:

    @always_inline
    def init(mut driver) -> S32:
        ...

    @always_inline
    def start[Dsp: FaustDsp](mut driver, var dsp: Ptr[Dsp]) -> S32:
        ...

    @always_inline
    def stop(mut driver) -> S32:
        ...

    # Returns 1 while processing, 0 while inactive, or a negative error code.
    @always_inline
    def is_alive(imm driver) -> S32:
        ...
