# test/impulse.mojo

from conf import *
from dsp import *
from mem import *
from gui.control import ControlGui

# Impulse tests API integration.

def run_dsp[Dsp: FaustDsp](
    var dsp: Ptr[Dsp], mut ctrl_ui: ControlGui, var nbsamples: S32
) -> None:
    var linenum: S32 = 0
    var run: S32 = 0
    var i: S32 = 0
    if dsp[].get_sample_rate() != 44_100:
        print("Error in run_dsp in get_sample_rate: ", dsp[].get_sample_rate())

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_streams[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Panic in main - Critical allocation error: ", err)
        return

    var inputs = base.unsafe_value().bitcast[Ptr[FaustFloat, MUTA_NOTRK]]()
    var outputs = inputs + n_ins

    try:
        while nbsamples > 0:
            if run == 0:
                impulse(n_ins, inputs)
                ctrl_ui.set_buttons(True)
            if run >= 1:
                _ = zero_inputs_base(base, BUFF_SIZE, n_ins, n_outs)
                ctrl_ui.set_buttons(False)
            var count = min(BUFF_SIZE, nbsamples)
            dsp[].compute(
                S32(count), inputs.bitcast[Ptr[FaustFloat, READ_NOTRK]](), outputs
            )
            run += 1
            for i in range(count):
                print(String(linenum).ascii_rjust(6), ": ", end="")
                linenum += 1
                for c in range(n_outs):
                    var f = normalize(outputs[c][i])
                    print(" " + format_real(F64(f)), end="")
                print("")
            nbsamples -= count
    except e:
        print("Error in file at line ", i, ": ", e)

    free_streams(base)

def impulse(n_ins: S32, inputs: MutaStreams) -> None:
    for var i in range(n_ins):
        inputs[i][0] = FaustFloat(1.0)

def normalize(real: FaustFloat) raises -> FaustFloat:
    if not real == real:
        print("Error: isnan")
    elif real == inf[dfaust]() or real == -inf[dfaust]():
        print("Error: is inf")
    return FaustFloat(0.0) if abs(real) < FaustFloat(0.000001) else real

# Impulse architecture helpers.

def print_header(dsp: Some[FaustDsp], nbsamples: S32) -> None:
    print("number_of_inputs  :", String(dsp.get_num_inputs()).ascii_rjust(3))
    print("number_of_outputs :", String(dsp.get_num_outputs()).ascii_rjust(3))
    print("number_of_frames  :", String(nbsamples).ascii_rjust(6))

def format_real(real: F64) -> String:
    var neg = real < 0.0
    var x = -real if neg else real
    var y = x * 1000000.0
    var lower = S64(y)
    var frac = y - F64(lower)
    var scaled = lower
    if frac > 0.5:
        scaled += 1
    elif frac == 0.5:
        if (lower & 1) != 0:
            scaled += 1
    var int_part = scaled // 1000000
    var frac_part = scaled % 1000000
    var s = String("-") if neg else String("")
    s += String(int_part)
    s += "."
    var frac_str = String(frac_part)
    for _ in range(6 - frac_str.byte_length()):
        s += "0"
    s += frac_str
    var res = ""
    for _ in range(8 - s.byte_length()):
        res += " "
    res += s
    return res

# Impulse architecture constants and compile flags.

comptime BUFF_SIZE  = S32(get_defined_int["BUFF_SIZE", 64]())
comptime SAMP_RATE  = S32(get_defined_int["SAMP_RATE", 44_100]())

def assert_dfaust() -> None: comptime assert dfaust == F64.dtype
comptime _ = assert_dfaust()
