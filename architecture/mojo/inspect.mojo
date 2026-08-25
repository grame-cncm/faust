# ==============================================================================
# Faust to Mojo inspect architecture for the benchmark framework.
# Provides the minimal definitions and entry point needed to generate
# low-level code with clear symbols for inspecting the generated compute code.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from help import *
from mem import *
from dsp import *
from gui import *
from meta import *

from std.benchmark import keep, clobber_memory

comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 512]())
comptime COMPUTE_ITERS = S32(get_defined_int["COMPUTE_ITERS", 100]())

# ==============================================================================
# First section of architecture provided code end.
<<includeIntrinsic>>
<<includeclass>>
# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application.
# Initializes the dsp object, allocates and intializes the audio buffers and
# calls the inspect function to run the dsp code.
# ==============================================================================

def main() -> None:
    var dsp = unsafe_alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)
    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()
    var base, err = make_streams[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        dsp.unsafe_free()
        return
    var ptr = base.unsafe_value()
    var inputs = ptr.bitcast[Ptr[FaustFloat, IMM_NOTRK]]().as_immutable()
    var outputs = (ptr + n_ins).bitcast[Ptr[FaustFloat, MUT_NOTRK]]()
    inspect_compute(dsp[], inputs, outputs)
    ptr.unsafe_free()
    dsp.unsafe_free()

@no_inline
@export("inspect_compute")
def inspect_compute(
    mut dsp: mydsp, inputs: ImmStreams, outputs: MutStreams
) abi("Mojo") -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute(BUFF_SIZE, inputs, outputs)
        clobber_memory()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
