# conf/prelude.mojo

from std.math import *
from std.memory import memset_zero
from std.sys.info import size_of, align_of
from std.sys.defines import (
    is_defined, get_defined_int, get_defined_bool, get_defined_string, get_defined_dtype
)

# Base types' aliases.

comptime U8 = UInt8
comptime U32 = UInt32
comptime U64 = UInt64
comptime S32 = Int32
comptime S64 = Int64
comptime SInt = Int
comptime F32 = Float32
comptime F64 = Float64

comptime Res = Tuple

# Pointer types' aliases.

comptime Ptr    = UnsafePointer
comptime AnyPtr = OpaquePointer
comptime Arr    = InlineArray

comptime ReadStreams[dtype: DType] = Ptr[Ptr[SIMD[dtype, 1], READ_EXT], READ_EXT]
comptime MutaStreams[dtype: DType] = Ptr[Ptr[SIMD[dtype, 1], MUTA_EXT], MUTA_EXT]

# Memory constants definitions.

comptime PTR_SIZE = size_of[AnyPtr[MUTA_EXT]]()
comptime PTR_ALIGN = align_of[AnyPtr[MUTA_EXT]]()
comptime STD_ALIGN = 2 * PTR_ALIGN
comptime NULL_PTR[T: AnyType, ori: Origin = MUTA_EXT] = Ptr[T, ori](unsafe_from_address=0)

# Origin values' aliases.

comptime READ_EXT = ImmutExternalOrigin
comptime MUTA_EXT = MutExternalOrigin

# Miscellaneous helpers ad utilities.

comptime is_real[dtype: DType]: Bool = dtype.is_floating_point()

