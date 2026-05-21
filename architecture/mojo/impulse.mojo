from conf import *
from mem import *
from dsp import *
from gui import *
from meta import *
from help import *

# --------------------------------------------------------------
# Impulse architecture implementation.
# --------------------------------------------------------------

def main() raises -> None:
    nbsamples = S32(60_000)
    dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    ctrl_ui = ControlGui()
    dsp[].init(SAMP_RATE)
    dsp[].build_user_interface(ctrl_ui)
    print_header(dsp[], nbsamples)
    run_dsp(dsp, ctrl_ui, nbsamples//4)
    dsp.free()

# Impulse tests API integration.

def run_dsp(
    var dsp: Ptr[mydsp], mut ctrl_ui: ControlGui, var nbsamples: S32
) -> None:
    var linenum: S32 = 0
    var run: S32 = 0
    var i: S32 = 0
    if dsp[].get_sample_rate() != 44_100:
        print("Error in run_dsp in get_sample_rate: ", dsp[].get_sample_rate())

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_buffers[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Panic in main - Critical allocation error: ", err)
        return

    var inputs = base.bitcast[Ptr[FaustFloat, MUTA_EXT]]()
    var outputs = inputs + n_ins

    try:
        while nbsamples > 0:
            if run == 0:
                impulse(n_ins, inputs)
                ctrl_ui.set_buttons(True)
            if run >= 1:
                # TODO: zero only the inputs
                init_buffers(base, BUFF_SIZE, n_ins, n_outs)
                ctrl_ui.set_buttons(False)
            var count = min(BUFF_SIZE, nbsamples)
            dsp[].compute(
                S32(count), inputs.bitcast[Ptr[FaustFloat, READ_EXT]](), outputs
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

    free_buffers(base)

def impulse(n_ins: S32, inputs: MutaStreams[dfaust]) -> None:
    for var i in range(n_ins):
        ref input_i = inputs[i]
        input_i[0] = FaustFloat(1.0)

def normalize(real: FaustFloat) raises -> FaustFloat:
    if not real == real:
        print("Error: isnan")
    elif real == inf[dfaust]() or real == -inf[dfaust]():
        print("Error: is inf")
    return FaustFloat(0.0) if abs(real) < FaustFloat(0.000001) else real

# Impulse architecture helpers.

def print_header(dsp: mydsp, nbsamples: S32) -> None:
    print("number_of_inputs  :", String(dsp.get_num_inputs()).ascii_rjust(3))
    print("number_of_outputs :", String(dsp.get_num_outputs()).ascii_rjust(3))
    print("number_of_frames  :", String(nbsamples).ascii_rjust(6))

def format_real(real: Float64) -> String:
    var neg = real < 0.0
    var x = -real if neg else real
    var y = x * 1000000.0
    var lower = S32(y)
    var frac = y - Float64(lower)
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

# ControlGui architecture implementation.

struct ControlGui(FaustGui):
    var buttons: List[Ptr[FaustFloat, MUTA_EXT]]

    def __init__(out ui):
        ui.buttons = List[Ptr[FaustFloat, MUTA_EXT]]()

    def add_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None:
        ui.buttons.append(
            Ptr(to=zone).bitcast[FaustFloat]().unsafe_origin_cast[MUTA_EXT]()
        )

    def set_buttons(mut ui, var state: Bool) -> None:
        var value = FaustFloat(1.0) if state else FaustFloat(0.0)
        for button in ui.buttons:
            button[] = value

    def run(mut ui) -> S32: return 0

# Impulse architecture constants and compile flags.

comptime FaustFloat = Float64 
comptime dfaust     = FaustFloat.dtype
comptime BUFF_SIZE  = S32(get_defined_int["BUFF_SIZE", 64]())
comptime SAMP_RATE  = S32(get_defined_int["SAMP_RATE", 44_100]())

# # FaustDsp
# trait FaustDsp:
#     def __init__(out dsp): return
#     def get_num_inputs(dsp) -> S32: return 0
#     def get_num_outputs(dsp) -> S32: return 1
#     def get_sample_rate(dsp) -> S32: return 44_100
#     def init(mut dsp, sample_rate: S32) -> None: pass
#     def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None: pass 
#     def compute[dreal: DType](
#         mut dsp,
#         var count: S32, var inputs: ReadStreams[dreal], var outputs: MutaStreams[dreal]
#     ) -> None: pass
#
# struct mydsp(FaustDsp):
#     pass



######################################################################################
# EndEndEndEndEnd 
##
