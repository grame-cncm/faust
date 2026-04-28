# help/math.mojo

from std.ffi import c_double, c_float, external_call


@always_inline
def mod[dtype: DType](num: SIMD[dtype, 1], den: SIMD[dtype, 1]) -> SIMD[dtype, 1]:
    return num % den

@always_inline
def rint(var x: SIMD[Float64.dtype, 1]) -> SIMD[Float64.dtype, 1]:
    return external_call["rint", c_double, c_double](c_double(x))

@always_inline
def rint(var x: SIMD[Float32.dtype, 1]) -> SIMD[Float32.dtype, 1]:
    return external_call["rint", c_float, c_float](c_float(x))
