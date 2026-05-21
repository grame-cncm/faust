# mem/memory.mojo
# TODO:(manu) error handling and checks

from conf import *

comptime AllocError            = S32
comptime AllocError_None       = AllocError(0)
comptime AllocError_IllegalArg = AllocError(1)
comptime AllocError_Exhausted  = AllocError(2)

def align_up(num: SInt, aln: SInt) -> SInt:
    return (num + aln - 1) & ~(aln - 1)

def alloc_streams[dreal: DType](
    buff_size: S32, n_ins: S32, n_outs: S32,
) -> Res[Ptr[SIMD[dreal, 1]], AllocError]:
    comptime Real = SIMD[dreal, 1]
    if buff_size <= 0 or n_ins < 0 or n_outs < 0:
        return NULL_PTR[Real], AllocError_IllegalArg,
    var n_chans = n_ins + n_outs
    if n_chans <= 0:
        return NULL_PTR[Real], AllocError_IllegalArg,

    comptime ALIGN = STD_ALIGN if STD_ALIGN > align_of[Real]() else align_of[Real]()
    var header_size = align_up(PTR_SIZE * SInt(n_chans), align_of[Real]())
    var block_size = size_of[Real]() * SInt(buff_size * n_chans)
    var tot_size = header_size + block_size
    var alloc_size = align_up(tot_size, ALIGN)

    var base = alloc[U8](alloc_size, alignment=ALIGN)
    if base == NULL_PTR[U8]:
        return NULL_PTR[Real], AllocError_Exhausted
    return base.bitcast[Real](), AllocError_None,
   
# initialize the streams
def init_streams[dreal: DType](
    base: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, n_outs: S32,
) -> None:
    comptime Real = SIMD[dreal, 1]
    var n_chans = n_ins + n_outs
    var header_size = align_up(PTR_SIZE * SInt(n_chans), align_of[Real]())
    var block_size = size_of[Real]() * SInt(buff_size) * SInt(n_chans)
    var raw = base.bitcast[U8]()
    var header_beg = raw.bitcast[Ptr[Real]]()
    var data_beg = (raw + header_size).bitcast[Real]()
    for i in range(n_chans):
        (header_beg + i).init_pointee_copy(data_beg + i * buff_size)
    memset_zero(data_beg.bitcast[U8](), block_size)

# zero all streams given the `base` pointer to the header given by `alloc_streams`
def zero_streams_base[dreal: DType](
    data: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, n_outs: S32,
) -> None:
    comptime Real = SIMD[dreal, 1]
    var n_chans = n_ins + n_outs
    var header_size = align_up(PTR_SIZE * SInt(n_chans), align_of[Real]())
    var block_size = size_of[Real]() * SInt(buff_size) * SInt(n_chans)
    var raw = data.bitcast[U8]()
    var data_beg = (raw + header_size).bitcast[Real]()
    memset_zero(data_beg.bitcast[U8](), block_size)

# zero all streams given the pointer to the `data` frames
def zero_streams_data[dreal: DType](
    data: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, n_outs: S32,
) -> None:
    comptime Real = SIMD[dreal, 1]
    var block_size = size_of[Real]() * SInt(buff_size) * SInt(n_ins + n_outs)
    memset_zero(data.bitcast[U8](), block_size)

# zero either inputs or outputs streams given the pointer to the relative `data`
def zero_streams_data[dreal: DType](data: Ptr[SIMD[dreal, 1]], buff_size: S32, n_chans: S32) -> None:
    zero_streams_data[dreal](data, buff_size, n_chans, 0)

def zero_inputs_base[dreal: DType](
    base: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, n_outs: S32
) -> None:
    comptime Real = SIMD[dreal, 1]
    header_size = align_up(PTR_SIZE * SInt(n_ins + n_outs), align_of[Real]())
    data_ins = base.bitcast[U8]() + header_size
    return zero_streams_data(data_ins.bitcast[Real](), buff_size, n_ins)

def zero_outputs_base[dreal: DType](
    base: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, n_outs: S32
) -> None:
    comptime Real = SIMD[dreal, 1]
    header_size = align_up(PTR_SIZE * SInt(n_ins + n_outs), align_of[Real]())
    var data_raw = base.bitcast[U8]() + header_size
    var data_outs = data_raw + SInt(n_ins) * SInt(buff_size) * size_of[Real]()
    return zero_streams_data(data_outs.bitcast[Real](), buff_size, n_outs)

def make_streams[dreal: DType](
    buff_size: S32, n_ins: S32, n_outs: S32
) -> Res[Ptr[SIMD[dreal, 1]], AllocError]:
    var base, err = alloc_streams[dreal](buff_size, n_ins, n_outs)
    if err != AllocError_None:
        return NULL_PTR[SIMD[dreal, 1]], err
    init_streams[dreal](base, buff_size, n_ins, n_outs)
    return base, AllocError_None,

def free_streams[dreal: DType](base: Ptr[SIMD[dreal, 1]]):
    comptime Real = SIMD[dreal, 1]
    if base == NULL_PTR[Real]:
        return
    base.free()

# ==============================================================
# Unused
# ==============================================================

# XXX: Does not work as expected
def addr_of[Type: AnyType](ref x: Type) -> Int:
    var y = Ptr(to=x)
    return y.__int__()

