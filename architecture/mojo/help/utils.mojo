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
    var  ptr:    UnsafePointer[F64, MUTA_NOTRK],
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
    var  ptr:    UnsafePointer[F32, MUTA_NOTRK],
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
    var  ptr:    UnsafePointer[S32, MUTA_NOTRK],
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
def simd_store[width: Int](
    var  ptr:    UnsafePointer[FaustFloat, MUTA_NOTRK],
    var  idx:    S32,
    read value:  SIMD[dfaust, width],
) -> None:
    ptr.store[width=width](idx, value)
