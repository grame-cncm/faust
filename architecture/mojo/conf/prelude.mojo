# conf/prelude.mojo

from std.math import *
from std.memory import memset_zero
from std.sys.info import size_of, align_of, simd_width_of
from std.sys.defines import (
    is_defined, get_defined_int, get_defined_bool, get_defined_string, get_defined_dtype
)

# Base arithmetic types aliases
comptime U8 = UInt8
comptime U32 = UInt32
comptime U64 = UInt64
comptime S32 = Int32
comptime S64 = Int64
comptime SInt = Int
comptime F32 = Float32
comptime F64 = Float64

# Base arithmetic dtype constants
comptime u8 = U8.dtype
comptime u32 = U32.dtype
comptime u64 = U64.dtype
comptime s32 = S32.dtype
comptime s64 = S64.dtype
comptime sint = SInt.dtype
comptime uint = UInt.dtype
comptime f32 = F32.dtype
comptime f64 = F64.dtype

# SIMD width constants
comptime w32 = simd_width_of[f32]()
comptime w64 = simd_width_of[f64]()

# Builtin types aliases
comptime Res = Tuple
comptime Arr = InlineArray
comptime Void = NoneType

# SIMD types aliases
comptime Vec[dtype: DType] = SIMD[dtype, simd_width_of[dtype]()]
comptime S32Vec = Vec[s32]
comptime F32Vec = Vec[f32]
comptime F64Vec = Vec[f64]

# FaustFloat architecture constants and type aliases
comptime dfaust = get_defined_dtype["DFAUST", DType.float32]()
comptime wfaust = simd_width_of[dfaust]()
comptime FaustFloat = Scalar[dfaust]
comptime FVec = Vec[dfaust]

# Origin values constants
comptime IMM_NOTRK = ImmUntrackedOrigin 
comptime MUT_NOTRK = MutUntrackedOrigin

# Pointer types aliases
comptime Ptr[T: AnyType = Void, ori: Origin = MUT_NOTRK]    = UnsafePointer[T, ori]
comptime AnyPtr[ori: Origin = MUT_NOTRK]                    = Ptr[Void, ori]
comptime OptPtr[T: AnyType = Void, ori: Origin = MUT_NOTRK] = Optional[Ptr[T, ori]]

# FaustFloat streams
comptime ImmStreams = Ptr[Ptr[FaustFloat, IMM_NOTRK], IMM_NOTRK]
comptime MutStreams = Ptr[Ptr[FaustFloat, MUT_NOTRK], MUT_NOTRK]

# Memory constants definitions
comptime PTR_SIZE = size_of[AnyPtr[MUT_NOTRK]]()
comptime PTR_ALIGN = align_of[AnyPtr[MUT_NOTRK]]()
comptime STD_ALIGN = 2 * PTR_ALIGN
comptime NULL_PTR[T: AnyType = Void, ori: Origin = MUT_NOTRK]: OptPtr[T, ori] = None
