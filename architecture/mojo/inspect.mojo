from std.benchmark import keep, clobber_memory

from conf import *
from help import *
from mem import *
from dsp import *
from gui import *
from meta import *

comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 512]())
comptime COMPUTE_ITERS = S32(get_defined_int["COMPUTE_ITERS", 100]())

comptime dfaust = get_defined_dtype["FAUST_DTYPE", F64.dtype]()
comptime FaustFloat = SIMD[dfaust, 1]

<<includeIntrinsic>>
<<includeclass>>

def main() -> None:
    comptime Real = SIMD[dfaust, 1]
    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)
    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()
    var base, err = make_buffers[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        dsp.free()
        return
    var inputs = base.bitcast[Ptr[Real, READ_EXT]]().as_immutable()
    var outputs = (base + n_ins).bitcast[Ptr[Real, MUTA_EXT]]()
    inspect_compute(dsp[], inputs, outputs)
    base.free()
    dsp.free()

@export("inspect_compute")
@no_inline
def inspect_compute(mut dsp: mydsp, inputs: ReadStreams[dfaust], outputs: MutaStreams[dfaust]) -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute[dfaust](BUFF_SIZE, inputs, outputs)
        clobber_memory()
