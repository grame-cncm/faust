# conf/prelude.mojo

from std.math import *
from std.memory import memset_zero
from std.sys.info import size_of, align_of
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

comptime Res = Tuple
comptime Arr = InlineArray

# FaustFloat architecture precison alias.

comptime dfaust = get_defined_dtype["dfaust", DType.float32]()
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
