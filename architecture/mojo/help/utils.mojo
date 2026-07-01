# help/utils.mojo

from conf import *

@always_inline
def simd_store[
    dtype: DType, width: Int
](
    var  ptr:    Ptr[Scalar[dtype], _],
    read idx:    S32,
    read value:  SIMD[dtype, width]
) -> None:
    ptr.unsafe_mut_cast[True]().store(idx, value)

@always_inline
def simd_store[
    dtype: DType, width: Int
](
    mut  arr:    Arr[Scalar[dtype], _],
    read idx:    S32,
    read value:  SIMD[dtype, width]
) -> None:
    Ptr(to=arr[S32(0)]).store(idx, value)

@always_inline
def simd_load[
    dtype: DType, width: Int = simd_width_of[dtype]()
](ptr: Ptr[Scalar[dtype], _], idx: S32) -> SIMD[dtype, width]:
    return ptr.load(idx)

@always_inline
def simd_load[
    dtype: DType, width: Int = simd_width_of[dtype]()
](arr: Arr[Scalar[dtype], _], idx: S32) -> SIMD[dtype, width]:
    return Ptr(to=arr[0]).load(idx)
