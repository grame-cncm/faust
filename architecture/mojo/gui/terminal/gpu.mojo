"""Terminal presentation on main; host zones and GPU transfers on audio."""

from std.ffi import external_call
from std.sys import has_accelerator

from conf import *
from dsp import FaustDspGpu
from audio.portaudio.gpu import PortAudioGpu
from audio.portaudio.ffi import PA_STREAM_IS_STOPPED
from .terminal import TerminalGui
from .ffi import error_str


def terminal_pull(data: OptPtr[Void, MUT_NOTRK]) -> None:
    data.unsafe_value().unsafe_bitcast[TerminalGui[dfaust]]()[].pull()


def terminal_push(data: OptPtr[Void, MUT_NOTRK]) -> None:
    data.unsafe_value().unsafe_bitcast[TerminalGui[dfaust]]()[].push()


def run_terminal_gpu[Dsp: FaustDspGpu](dsp: Ptr[Dsp]) raises -> None:
    # Takes ownership of an initialized unsafe_alloc[Dsp](1) allocation.
    comptime assert dfaust == F32.dtype, "Expected 32 bit float driver precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."
    # NOTE:(manu) currently no need for custom destructor in mydsp
    # comptime assert conforms_to(Dsp, Deinitable), "Expected a deinitializable DSP."


    var gui = TerminalGui[dfaust]()
    dsp[].build_user_interface(gui)
    var driver = PortAudioGpu[Dsp]()
    var data: OptPtr[Void, MUT_NOTRK] = (
        Ptr(to=gui).unsafe_origin_cast[MUT_NOTRK]().unsafe_bitcast[Void]()
    )

    var err = gui.check()
    if not err:
        err = driver.init()
    if not err:
        err = driver.start(dsp, terminal_pull, terminal_push, data)
    if not err:
        err = gui.start()
    if not err:
        while gui.tick():
            var state = driver.is_active()
            if state != 1:
                err = state if state < 0 else PA_STREAM_IS_STOPPED
                break
        if not err:
            err = gui.err

    # Keep GUI slots, host zones and device storage alive until audio is closed.
    var term = gui.stop()
    var end = driver.stop()
    if driver.stream != None or driver.state != None:
        print("GPU audio close failed:", end)
        external_call["_Exit", Void](S32(1))

    # Callback errors are read only after stop(), never concurrently with audio.
    if err == PA_STREAM_IS_STOPPED and driver.err:
        err = driver.err
    gui.close()
    #NOTE:(manu) currently no need for custom destructor in mydsp
    # dsp.unsafe_deinit_pointee() 
    dsp.unsafe_free()

    if not err:
        err = term if term else end
    if err > 0:
        raise Error(error_str(err))
    if err:
        raise Error(String("GPU audio error: ", err))
