# help/utils.mojo

from conf import *


@always_inline
def simd_store[
    dtype: DType, //, width: SInt
](
    var  ptr:    Ptr[Scalar[dtype], _],
    read idx:    S32,
    read value:  SIMD[dtype, SInt(width)]
) -> None:
    ptr.unsafe_mut_cast[True]().store[width=width](idx, value)


@always_inline
def simd_store[
    dtype: DType, //,  width: SInt
](
    mut  arr:    Arr[Scalar[dtype], _],
    read idx:    S32,
    read value:  SIMD[dtype, width]
) -> None:
    Ptr(to=arr[S32(0)]).store[width=width](idx, value)


@always_inline
def simd_store[
    dtype: DType, //, width: SInt
](
    var  ptr:    Ptr[Scalar[dtype], _],
    read idx:    S32,
    read value:  Scalar[dtype]
) -> None:
    # broadcast
    ptr.unsafe_mut_cast[True]().store[width=width](idx, SIMD[dtype, width](value))


@always_inline
def simd_load[
    dtype: DType, //, width: SInt = simd_width_of[dtype]()
](ptr: Ptr[Scalar[dtype], _], idx: S32) -> SIMD[dtype, width]:
    return ptr.load[width=width](idx)


@always_inline
def simd_load[
    dtype: DType, //, width: SInt = simd_width_of[dtype]()
](arr: Arr[Scalar[dtype], _], idx: S32) -> SIMD[dtype, width]:
    return Ptr(to=arr[S32(0)]).load[width=width](idx)
