# help/math.mojo

from std.ffi import c_double, c_float, external_call

from conf import *

@always_inline
def mod[dtype: DType](num: SIMD[dtype, 1], den: SIMD[dtype, 1]) -> SIMD[dtype, 1]:
    return num % den

def mod[
    dtype: DType, width: SInt
](num: SIMD[dtype, width], den: SIMD[dtype, width]) -> SIMD[dtype, width]:
    return num % den

@always_inline
def rint(var x: SIMD[F64.dtype, 1]) -> SIMD[F64.dtype, 1]:
    return external_call["rint", c_double, c_double](c_double(x))

@always_inline
def rint(var x: SIMD[F32.dtype, 1]) -> SIMD[F32.dtype, 1]:
    return external_call["rint", c_float, c_float](c_float(x))

@always_inline
def pow_unrolled[dtype: DType, width: SInt = 1, //,  e: UInt](x: SIMD[dtype, width]) -> SIMD[dtype, width]:
    var res: SIMD[dtype, width] = 1
    comptime for _ in range(e):
        res *= x
    return res

