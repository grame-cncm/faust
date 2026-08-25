# probe.mojo

from std.memory.alloc import unsafe_alloc
from std.memory import bitcast

from conf import *
from help import * 

# vstore(zec22, abs(max(unsafe_load[2](i_yec18)).cast[f64](), (S32Wec( Int( vload[W](i_rec15).gt(S32Wec(0)) ))).cast[f64]())))


def main() -> None:

    comptime W = simd_width_of[f64]()
    var i: S32 = 0
    var ptr = unsafe_alloc[S32](2)
    var vec = vload[W](ptr)
    var pred = vec.gt(S32Wec(0))

    print(reflect[type_of(vec)].name())
    print(reflect[type_of(pred)].name())

    ptr.unsafe_free()
