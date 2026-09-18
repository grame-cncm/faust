# help/utils.mojo

from conf import *


@always_inline
def vstore[
    dtype: DType, //, width: SInt
](
    var ptr:    Ptr[Scalar[dtype], _],
    imm value:  SIMD[dtype, SInt(width)],
    imm idx:    S32                       =  0
) -> None:
    ptr.unsafe_mut_cast[True]().unsafe_store[width=width](idx, value)


@always_inline
def vstore[
    dtype: DType, //,  width: SInt
](
    mut arr:    Arr[Scalar[dtype], _],
    imm value:  SIMD[dtype, width],
    imm idx:    S32                    =  0
) -> None:
    Ptr(to=arr[S32(0)]).unsafe_store[width=width](idx, value)


# broadcast
@always_inline
def vstore[
    dtype: DType, //, width: SInt
](
    var ptr:    Ptr[Scalar[dtype], _],
    imm value:  Scalar[dtype],
    imm idx:    S32                    =  0
) -> None:
    ptr.unsafe_mut_cast[True]().unsafe_store[width=width](idx, SIMD[dtype, width](value))


@always_inline
def vload[
    dtype: DType, //, width: SInt = simd_width_of[dtype]()
](var ptr: Ptr[Scalar[dtype], _], imm idx: S32 = 0) -> SIMD[dtype, width]:
    return ptr.unsafe_load[width=width](idx)


@always_inline
def vload[
    dtype: DType, //, width: SInt = simd_width_of[dtype]()
](imm arr: Arr[Scalar[dtype], _], imm idx: S32 = 0) -> SIMD[dtype, width]:
    return Ptr(to=arr[S32(0)]).unsafe_load[width=width](idx)
