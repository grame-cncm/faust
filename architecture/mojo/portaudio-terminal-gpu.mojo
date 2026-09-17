# ==============================================================================
# Faust to Mojo architecture file for PortAudio, GPU processing, and TerminalGui.
# Provides the definitions and the main entry point to run a GPU-capable DSP
# with PortAudio and control it through the native C terminal GUI.
# Link gui/terminal/native/build/libtermgui.a and PortAudio.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from dsp import *
from gui import FaustGui, TerminalGui, GpuControlMap, build_gpu_control_map, error_str
from gpu import *
from help import *
from meta import *
from audio import *

# ==============================================================================
# First section of architecture provided code end.
<<includeIntrinsic>>
<<includeclass>>
# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point and composes the DSP, terminal GUI, GPU device,
# GPU adapter, and PortAudio driver.
# ==============================================================================

def main() -> None:
    comptime assert dfaust == F32.dtype, "Expected 32-bit audio precision."
    comptime assert has_accelerator(), "Expected a supported GPU device."

    var dsp = unsafe_alloc[mydsp](1)
    dsp.unsafe_write(mydsp())
    dsp[].init(SAMP_RATE)
    var ui = unsafe_alloc[TerminalGui](1)
    ui.unsafe_write(TerminalGui())
    dsp[].build_user_interface(ui[])
    var map = unsafe_alloc[GpuControlMap](1)
    map.unsafe_write(GpuControlMap())
    var gpu = unsafe_alloc[GpuDevice[mydsp]](1)
    gpu.unsafe_write(GpuDevice[mydsp]())
    var driver = unsafe_alloc[PortAudio](1)
    driver.unsafe_write(PortAudio())
    var err = ui[].check()
    if not err:
        err = build_gpu_control_map(dsp, map[])
    if not err:
        err = gpu[].prepare(dsp, map[], BUFF_SIZE)

    var adapter = unsafe_alloc[AdapterDsp[mydsp]](1)
    adapter.unsafe_write(AdapterDsp[mydsp](dsp, gpu))
    if not err:
        err = driver[].init()
    if not err:
        err = driver[].start(adapter)
    if not err:
        err = ui[].run()

    var term = ui[].stop()
    var end = driver[].stop()
    if driver[].stream != None:
        print("PortAudio close failed:", end)
        return
    var gpu_err = gpu[].get_error()
    var released = gpu[].release()
    if gpu[].state != None:
        print("GPU release failed:", released)
        return
    ui[].close()
    adapter.unsafe_free()
    driver.unsafe_free()
    gpu.unsafe_free()
    map.unsafe_free()
    ui.unsafe_deinit_pointee()
    ui.unsafe_free()
    dsp.unsafe_free()
    if not err:
        err = term
    if not err:
        err = gpu_err
    if not err:
        err = released
    if not err:
        err = end
    if err:
        if err > 0:
            print(error_str(err))
        else:
            print("GPU audio error:", err)
        return
    print("done")

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
