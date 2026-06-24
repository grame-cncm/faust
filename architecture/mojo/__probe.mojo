from std.sys.info import simd_width_of

from conf import *

comptime Array[dtype: DType, size: SInt] = InlineArray[SIMD[dtype, 1], size]
comptime f64 = F64.dtype



def main():
    var x = Array[f64, 36](uninitialized=True)
    comptime dtype = get_dtype[type_of(x)]()
