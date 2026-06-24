# conf/prelude.mojo

from std.math import *
from std.memory import memset_zero
from std.sys.info import size_of, align_of, simd_width_of
from std.sys.defines import (
    is_defined, get_defined_int, get_defined_bool, get_defined_string, get_defined_dtype
)

# Base types aliases.

comptime U8 = UInt8
comptime U32 = UInt32
comptime U64 = UInt64
comptime S32 = Int32
comptime S64 = Int64
comptime SInt = Int
comptime F32 = Float32
comptime F64 = Float64
comptime Void = NoneType

comptime u8 = U8.dtype
comptime u32 = U32.dtype
comptime u64 = U64.dtype
comptime s32 = S32.dtype
comptime s64 = S64.dtype
comptime sint = SInt.dtype
comptime f32 = F32.dtype
comptime f64 = F64.dtype

comptime Res = Tuple
comptime Arr = InlineArray

# FaustFloat architecture precison alias.

comptime dfaust = get_defined_dtype["DFAUST", DType.float32]()
comptime FaustFloat = SIMD[dfaust, 1]

# Pointer types aliases.

comptime Ptr[T: AnyType = Void, ori: Origin = MUTA_NOTRK]    = UnsafePointer[T, ori]
comptime AnyPtr[ori: Origin = MUTA_NOTRK]                    = Ptr[Void, ori]
comptime OptPtr[T: AnyType = Void, ori: Origin = MUTA_NOTRK] = Optional[Ptr[T, ori]]

comptime ReadStreams = Ptr[Ptr[FaustFloat, READ_NOTRK], READ_NOTRK]
comptime MutaStreams = Ptr[Ptr[FaustFloat, MUTA_NOTRK], MUTA_NOTRK]

# Memory constants definitions.

comptime PTR_SIZE = size_of[AnyPtr[MUTA_NOTRK]]()
comptime PTR_ALIGN = align_of[AnyPtr[MUTA_NOTRK]]()
comptime STD_ALIGN = 2 * PTR_ALIGN
comptime NULL_PTR[T: AnyType = Void, ori: Origin = MUTA_NOTRK]: OptPtr[T, ori] = None

# Origin values aliases.

comptime READ_NOTRK = ImmutUntrackedOrigin 
comptime MUTA_NOTRK = MutUntrackedOrigin
