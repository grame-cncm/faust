# mem/memory.mojo

from conf import *

comptime AllocErr            = S32
comptime AllocErr_None       = AllocErr(0)
comptime AllocErr_IllegalArg = AllocErr(1)
comptime AllocErr_Exhausted  = AllocErr(2)

def align_up(num: SInt, aln: SInt) -> SInt:
    return (num + aln - 1) & ~(aln - 1)

def alloc_buffers[dreal: DType](
    buff_size: S32, n_ins: S32, n_outs: S32,
) -> Res[Ptr[SIMD[dreal, 1], MUTA_EXT], AllocErr]:
    comptime Real = SIMD[dreal, 1]
    if buff_size <= 0 or n_ins < 0 or n_outs < 0:
        return NULL_PTR[Real, MUTA_EXT], AllocErr_IllegalArg,
    var n_chans = n_ins + n_outs
    if n_chans <= 0:
        return NULL_PTR[Real, MUTA_EXT], AllocErr_IllegalArg,

    comptime REAL_SIZE = size_of[Real]()
    comptime REAL_ALIGN = align_of[Real]()
    comptime ALIGN = STD_ALIGN if STD_ALIGN > REAL_ALIGN else REAL_ALIGN

    var header_size = align_up(PTR_SIZE * SInt(n_chans), REAL_ALIGN)
    var block_size = REAL_SIZE * SInt(buff_size * n_chans)
    var tot_size = header_size + block_size
    var alloc_size = align_up(tot_size, ALIGN)

    var base = alloc[U8](alloc_size, alignment=ALIGN)
    if base == NULL_PTR[U8, MUTA_EXT]:
        return NULL_PTR[Real, MUTA_EXT], AllocErr_Exhausted

    return base.bitcast[Real](), AllocErr_None,
   
def init_buffers[dreal: DType](
    base: Ptr[SIMD[dreal, 1], MUTA_EXT], buff_size: S32, n_ins: S32, n_outs: S32,
) -> None:
    comptime Real = SIMD[dreal, 1]
    comptime RealPtr = Ptr[Real, MUTA_EXT]
    comptime REAL_SIZE = size_of[Real]()
    comptime REAL_ALIGN = align_of[Real]()

    var n_chans = n_ins + n_outs
    var header_size = align_up(PTR_SIZE * SInt(n_chans), REAL_ALIGN)
    var block_size = REAL_SIZE * SInt(buff_size * n_chans)

    var raw = base.bitcast[U8]()
    var header_beg = raw.bitcast[RealPtr]()
    var data_beg = (raw + header_size).bitcast[Real]()

    for i in range(n_chans):
        (header_beg + i).init_pointee_copy(data_beg + i * buff_size)
    memset_zero(data_beg.bitcast[U8](), block_size)

def make_buffers[dreal: DType](
    buff_size: S32, n_ins: S32, n_outs: S32
) -> Res[Ptr[SIMD[dreal, 1], MUTA_EXT], AllocErr]:
    var base, err = alloc_buffers[dreal](buff_size, n_ins, n_outs)
    if err != AllocErr_None:
        return NULL_PTR[SIMD[dreal, 1], MUTA_EXT], err
    init_buffers[dreal](base, buff_size, n_ins, n_outs)
    return base, AllocErr_None,

def free_buffers[dreal: DType](base: Ptr[SIMD[dreal, 1], MUTA_EXT]):
    comptime Real = SIMD[dreal, 1]
    if base == NULL_PTR[Real, MUTA_EXT]:
        return
    base.free()


