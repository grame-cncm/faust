from conf import *
from mem import *

def is_sint[dtype: DType, //, n: SIMD[dtype, _]]() -> Bool:
    comptime assert dtype.is_numeric()
    comptime if dtype.is_integral():
        return True
    else:
        return n == trunc(n)

def is_uint[dtype: DType, //, n: SIMD[dtype, _]]() -> Bool:
    return n >= 0 and is_sint[n]()

comptime POW_DISPATCH[dtype: DType, //, e: SIMD[dtype, _]]  = is_uint[e]()

def pow[dtype: DType, size: SInt, //,  e: UInt](x: SIMD[dtype, size]) -> SIMD[dtype, size]:
    var res: SIMD[dtype, size] = 1
    comptime for _ in range(e):
        res = res * x
    return res

def main() -> None:
    comptime e: SIMD[F32.dtype, 2] = 0
    print(e, ":", Bool(POW_DISPATCH[e]))

