# help/utils.mojo

from conf import *

@always_inline
def simd_store[width: Int, size: Int](
    mut  arr:    Arr[F64, size],
    var  idx:    S32,
    read value:  SIMD[f64, width],
) -> None:
    Ptr(to=arr[S32(0)]).store[width=width](idx, value)

@always_inline
def simd_store[width: Int](
    var  ptr:    Ptr[F64, MUTA_NOTRK],
    var  idx:    S32,
    read value:  SIMD[f64, width],
) -> None:
    ptr.store[width=width](idx, value)

@always_inline
def simd_store[width: Int, size: Int](
    mut  arr:    Arr[F32, size],
    var  idx:    S32,
    read value:  SIMD[f32, width],
) -> None:
    Ptr(to=arr[S32(0)]).store[width=width](idx, value)

@always_inline
def simd_store[width: Int](
    var  ptr:    Ptr[F32, MUTA_NOTRK],
    var  idx:    S32,
    read value:  SIMD[f32, width],
) -> None:
    ptr.store[width=width](idx, value)

@always_inline
def simd_store[width: Int, size: Int](
    mut  arr:    Arr[S32, size],
    var  idx:    S32,
    read value:  SIMD[s32, width],
) -> None:
    Ptr(to=arr[S32(0)]).store[width=width](idx, value)

@always_inline
def simd_store[width: Int](
    var  ptr:    Ptr[S32, MUTA_NOTRK],
    var  idx:    S32,
    read value:  SIMD[s32, width],
) -> None:
    ptr.store[width=width](idx, value)

@always_inline
def simd_store[width: Int, size: Int](
    mut  arr:    Arr[FaustFloat, size],
    var  idx:    S32,
    read value:  SIMD[dfaust, width],
) -> None:
    Ptr(to=arr[S32(0)]).store[width=width](idx, value)

@always_inline
def simd_store(
    var  ptr:    Ptr[FaustFloat, MUTA_NOTRK],
    var  idx:    S32,
    read value:  SIMD[dfaust, Int(dfaust_width)],
) -> None:
    ptr.store[width=Int(dfaust_width)](idx, value)

@always_inline
def simd_load[
    dtype: DType, width: Int = simd_width_of[dtype]()
](ptr: Ptr[Scalar[dtype], READ_NOTRK], idx: S32) -> SIMD[dtype, width]:
    return ptr.load[width=width](idx)
