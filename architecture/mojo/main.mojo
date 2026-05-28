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

def main() -> None:
    comptime e: SIMD[F32.dtype, 2] = 0

