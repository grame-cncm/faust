# conf/prelude.mojo

from std.math import *
from std.sys.intrinsics import _type_is_eq, _type_is_eq_parse_time

comptime U32 = UInt32
comptime U64 = UInt64
comptime S32 = Int32
comptime S64 = Int64
comptime SInt = Int
comptime F32 = Float32
comptime F64 = Float64

comptime Ptr    = UnsafePointer
comptime AnyPtr = OpaquePointer
comptime OptPtr[T: AnyType, ori: Origin] = Optional[Ptr[T, ori]]
comptime Arr    = InlineArray

comptime READ_EXT = ImmutExternalOrigin
comptime MUTA_EXT = MutExternalOrigin

comptime ReadStreams[dtype: DType] = Ptr[Ptr[SIMD[dtype, 1], READ_EXT], READ_EXT]
comptime MutaStreams[dtype: DType] = Ptr[Ptr[SIMD[dtype, 1], MUTA_EXT], MUTA_EXT]

comptime is_real[dtype: DType]: Bool = dtype.is_floating_point()
