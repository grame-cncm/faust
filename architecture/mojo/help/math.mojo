# help/math.mojo

from std.ffi import c_double, c_float, external_call

from conf import *

@always_inline
def mod[dtype: DType](num: SIMD[dtype, 1], den: SIMD[dtype, 1]) -> SIMD[dtype, 1]:
    return num % den

@always_inline
def rint(var x: SIMD[F64.dtype, 1]) -> SIMD[F64.dtype, 1]:
    return external_call["rint", c_double, c_double](c_double(x))

@always_inline
def rint(var x: SIMD[F32.dtype, 1]) -> SIMD[F32.dtype, 1]:
    return external_call["rint", c_float, c_float](c_float(x))

@always_inline
def pow_unrolled[dtype: DType, size: SInt, //,  e: UInt](x: SIMD[dtype, size]) -> SIMD[dtype, size]:
    var res: SIMD[dtype, size] = 1
    comptime for _ in range(e):
        res *= x
    return res

