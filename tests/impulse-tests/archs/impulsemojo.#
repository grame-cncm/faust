from std.math import *
from std.memory import *
from std.ffi import external_call, c_int, CStringSlice, c_double, c_float

# --------------------------------------------------------------
# Main operations to integrate the impulse tests.
# --------------------------------------------------------------

def main() raises -> None:
    nbsamples = 60_000
    dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    ctrl_ui = ControlGui()
    dsp[].init(44_100)
    dsp[].build_user_interface(ctrl_ui)
    print_header(dsp[], nbsamples)
    run_dsp(dsp[], ctrl_ui, nbsamples//4)
    dsp.free()

def run_dsp(
    mut dsp:          mydsp,
    mut ctrl_ui:      ControlGui,
    var nbsamples:    SInt,
) -> None:
    var linenum: S32 = 0
    var run: S32 = 0
    var i: SInt = 0
    if dsp.get_sample_rate() != 44_100:
        print("Error in run_dsp in get_sample_rate: ", dsp.get_sample_rate())

    var n_ins =  SInt(dsp.get_num_inputs())
    var m_outs = SInt(dsp.get_num_outputs())
    var in_base, inputs = alloc_streams(n_ins, COUNT)
    var out_base, outputs = alloc_streams(m_outs, COUNT)

    try:
        while nbsamples > 0:
            if run == 0:
                impulse(n_ins, Span(ptr=inputs, length=n_ins))
                ctrl_ui.set_buttons(True)
            if run >= 1:
                zero_streams(n_ins, inputs, COUNT)
                ctrl_ui.set_buttons(False)
            var count = min(COUNT, nbsamples)
            dsp.compute(
                S32(count),
                inputs.bitcast[Ptr[FaustFloat, READ_EXT]](),
                outputs
            )
            run += 1
            for i in range(count):
                print(String(linenum).ascii_rjust(6), ": ", end="")
                linenum += 1
                for c in range(m_outs):
                    var f = normalize(outputs[c][i])
                    print(" " + format_real(f), end="")
                print("")
            nbsamples -= count

    except e:
        print("Error in file at line ", i, ": ", e)
    free_streams(in_base, inputs)
    free_streams(out_base, outputs)

# --------------------------------------------------------------
# ControlGui architecture implementation.
# --------------------------------------------------------------

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
        for button in ui.buttons:
            button[] = FaustFloat(state)

# --------------------------------------------------------------
# Free helpers to allocate streams, 
# --------------------------------------------------------------

def alloc_streams(
    var chans:    SInt,
    var count:    SInt,
) -> Tuple[Ptr[FaustFloat, MUTA_EXT], MutaStreams[dfaust]]:
    var owner = alloc[FaustFloat](chans * count)
    memset_zero(owner, chans * count)
    var streams = alloc[Ptr[FaustFloat, MUTA_EXT]](chans)
    for i in range(chans):
        streams[i] = owner + i * count
    return owner, streams

def free_streams(
    var owner:      Ptr[FaustFloat, MUTA_EXT],
    var streams:    Ptr[Ptr[FaustFloat, MUTA_EXT], MUTA_EXT],
) -> None:
    streams.free()
    owner.free()

def zero_streams(
    var chans:      SInt,
    var streams:    Ptr[Ptr[FaustFloat, MUTA_EXT], MUTA_EXT],
    var count:     SInt,
) -> None:
    for i in range(chans):
        memset_zero(streams[i], count)

def impulse[ori: MutOrigin](
    nins:     SInt,
    inputs:   Span[Ptr[FaustFloat, ori], ori]
) -> None:
    for input in inputs:
        input[0] = FaustFloat(1.0)

def print_header(dsp: mydsp, nbsamples: SInt) -> None:
    print("number_of_inputs  :", String(dsp.get_num_inputs()).ascii_rjust(3))
    print("number_of_outputs :", String(dsp.get_num_outputs()).ascii_rjust(3))
    print("number_of_frames  :", String(nbsamples).ascii_rjust(6))

def format_real(real: Float64) -> String:
    var neg = real < 0.0
    var x = -real if neg else real
    var y = x * 1000000.0
    var lower = SInt(y)
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
    var out = ""
    for _ in range(8 - s.byte_length()):
        out += " "
    out += s
    return out

def normalize(real: FaustFloat) raises -> FaustFloat:
    if not real == real:
        print("Error: isnan")
    elif real == inf[dfaust]() or real == -inf[dfaust]():
        print("Error: is inf")
    return FaustFloat(0.0) if abs(real) < FaustFloat(0.000001) else real

# --------------------------------------------------------------
# Comptime types, constants and predicates definitions.
# --------------------------------------------------------------
comptime FaustFloat = Float64
comptime dfaust = Float64.dtype
comptime COUNT = 64
comptime U32 = UInt32
comptime U64 = UInt64
comptime S32 = Int32
comptime S64 = Int64
comptime SInt = Int
comptime F32 = Float32
comptime F64 = Float64
comptime Ptr = UnsafePointer
comptime AnyPtr = OpaquePointer
comptime Arr = InlineArray
comptime READ_EXT = ImmutExternalOrigin
comptime MUTA_EXT = MutExternalOrigin
comptime ReadStreams[dreal: DType] = Ptr[Ptr[SIMD[dreal, 1], READ_EXT], READ_EXT]
comptime MutaStreams[dreal: DType] = Ptr[Ptr[SIMD[dreal, 1], MUTA_EXT], MUTA_EXT]
comptime is_real[dreal: DType]: Bool = dreal.is_floating_point()

# --------------------------------------------------------------
# Adapted Faust interfaces to be enough for the impulse tests.
# --------------------------------------------------------------
# FaustDsp
trait FaustDsp:
    def get_num_inputs(dsp) -> S32: ...
    def get_num_outputs(dsp) -> S32: ...
    def get_sample_rate(dsp) -> S32: ...
    def init(mut dsp, sample_rate: S32) -> None: ...
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None: pass 
    def compute[dreal: DType where is_real[dreal]](
        mut dsp,
        var count: S32, var inputs: ReadStreams[dreal], var outputs: MutaStreams[dreal]
    ) -> None: ...
# FaustGui
trait FaustGui:
    def open_tab_box(mut ui, var label: String) -> None: pass
    def open_horizontal_box(mut ui, var label: String) -> None: pass
    def open_vertical_box(mut ui, var label: String) -> None: pass
    def close_box(mut ui) -> None: pass
    def add_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None: pass
    def add_check_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None: pass
    def add_vertical_slider[dreal: DType](
        mut ui,
        var label: String,          mut zone: SIMD[dreal, 1],  var init: SIMD[dreal, 1],
        var min:   SIMD[dreal, 1],  var max:  SIMD[dreal, 1],  var step: SIMD[dreal, 1],
    ) -> None: pass
    def add_horizontal_slider[dreal: DType](
        mut ui,
        var label: String,          mut zone: SIMD[dreal, 1],  var init: SIMD[dreal, 1],
        var min:   SIMD[dreal, 1],  var max:  SIMD[dreal, 1],  var step: SIMD[dreal, 1],
    ) -> None: pass
    def add_num_entry[dreal: DType](
        mut ui,
        var label: String,          mut zone: SIMD[dreal, 1],  var init: SIMD[dreal, 1],
        var min:   SIMD[dreal, 1],  var max:  SIMD[dreal, 1],  var step: SIMD[dreal, 1],
    ) -> None: pass
    def add_horizontal_bargraph[dreal: DType](
        mut ui,
        var label: String,          mut zone: SIMD[dreal, 1],
        var min: SIMD[dreal, 1],    var max: SIMD[dreal, 1]
    ) -> None: pass
    def add_vertical_bargraph[dreal: DType](
        mut ui,
        var label: String,          mut zone: SIMD[dreal, 1],
        var min: SIMD[dreal, 1],    var max: SIMD[dreal, 1]
    ) -> None: pass
    def declare[dreal: DType](
        mut ui, mut zone: SIMD[dreal, 1], var key: String, var val: String
    ) -> None: pass
# FaustMeta
trait FaustMeta:
    def declare(mut meta, var key: String, var val: String) -> None: pass

