from conf import *
from mem import *
from bench import *
from dsp import *
from gui import *
from meta import *

<<includeIntrinsic>>
<<includeclass>>

def main() raises -> None:
    comptime dreal = dfaust
    comptime Real = SIMD[dreal, 1]

    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_buffers[dreal](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Critical allocation error: ", err)
        dsp.free()
        return

    var inputs = base.bitcast[Ptr[Real, MUTA_EXT]]()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs[dreal](inputs, n_ins)

    warmup[dreal](dsp[], inputs, outputs)
    var report = measure[dreal](dsp[], inputs, outputs)
    report.checksum = checksum_outputs[dreal](outputs, n_outs)
    print_report(report) # the output will be redirected via script
    write_csv(report)

    free_buffers[dreal](base)
    dsp.free()
