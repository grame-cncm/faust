# mem/memory.mojo

from conf import *

comptime ErrorCode                = S32
comptime Error_None               = ErrorCode(0)
comptime Error_InvalidArg         = ErrorCode(1)
comptime Error_InvalidPtr         = ErrorCode(1)
comptime AllocError_ExhaustedMem  = ErrorCode(2)

def align_up(num: SInt, aln: SInt) -> SInt:
    return (num + aln - 1) & ~(aln - 1)

# Allocate memory for input and output streams with the following layout:
#   +--------+---------+-----------------+
#   | header | padding |      data       |
#   +--------+---------+-----------------+
# - `header` is an array of `n_ins + n_outs` pointers into `data`:
#   +---------+---------+-----+----------+----------+-----+
#   | ptr_in0 | ptr_in1 | ... | ptr_out0 | ptr_out1 | ... |
#   +---------+---------+-----+----------+----------+-----+
# - `padding` is needed to ensure `data` has proper alignment.
# - `data` contains `n_ins + n_outs` channel buffers, each with `buff_size` frames:
#   +------+------+-----+-------+-------+-----+
#   | in_0 | in_1 | ... | out_0 | out_1 | ... |
#   +------+------+-----+-------+-------+-----+
def alloc_streams[dreal: DType](
    buff_size: S32, n_ins: S32, m_outs: S32,
) -> Res[Ptr[SIMD[dreal, 1]], ErrorCode]:
    comptime Real = SIMD[dreal, 1]
    if buff_size <= 0 or n_ins < 0 or m_outs < 0:
        return NULL_PTR[Real], Error_InvalidArg,
    var n_chans = n_ins + m_outs
    if n_chans <= 0:
        return NULL_PTR[Real], Error_InvalidArg,

    comptime ALIGN = STD_ALIGN if STD_ALIGN > align_of[Real]() else align_of[Real]()
    var header_size = align_up(PTR_SIZE * SInt(n_chans), align_of[Real]())
    var block_size = size_of[Real]() * SInt(buff_size * n_chans)
    var tot_size = header_size + block_size
    var alloc_size = align_up(tot_size, ALIGN)

    var base = alloc[U8](alloc_size, alignment=ALIGN)
    if base == NULL_PTR[U8]:
        return NULL_PTR[Real], AllocError_ExhaustedMem
    return base.bitcast[Real](), Error_None,
   
# initialize the streams
def init_streams[dreal: DType, size: SInt](
    base: Ptr[SIMD[dreal, size]], buff_size: S32, n_ins: S32, m_outs: S32,
) -> ErrorCode:
    if base == NULL_PTR[SIMD[dreal, size]]:
        return Error_InvalidPtr
    if buff_size <= 0 or n_ins < 0 or m_outs < 0:
        return Error_InvalidArg
    comptime Real = SIMD[dreal, size]
    var n_chans = n_ins + m_outs
    var header_size = align_up(PTR_SIZE * SInt(n_chans), align_of[Real]())
    var block_size = size_of[Real]() * SInt(buff_size) * SInt(n_chans)
    var raw = base.bitcast[U8]()
    var header_beg = raw.bitcast[Ptr[Real]]()
    var data_beg = (raw + header_size).bitcast[Real]()
    for i in range(n_chans):
        (header_beg + i).init_pointee_copy(data_beg + i * buff_size)
    memset_zero(data_beg.bitcast[U8](), block_size)
    return Error_None

# zero all streams given the `base` pointer to the header given by `alloc_streams`
def zero_streams_base[dreal: DType](
    data: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, m_outs: S32,
) -> ErrorCode:
    if data == NULL_PTR[SIMD[dreal, 1]]:
        return Error_InvalidPtr
    if buff_size <= 0 or n_ins < 0 or m_outs < 0:
        return Error_InvalidArg
    comptime Real = SIMD[dreal, 1]
    var n_chans = n_ins + m_outs
    var header_size = align_up(PTR_SIZE * SInt(n_chans), align_of[Real]())
    var block_size = size_of[Real]() * SInt(buff_size) * SInt(n_chans)
    var raw = data.bitcast[U8]()
    var data_beg = (raw + header_size).bitcast[Real]()
    memset_zero(data_beg.bitcast[U8](), block_size)
    return Error_None

# zero all streams given the pointer to the `data` frames
def zero_streams_data[dreal: DType](
    data: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, m_outs: S32,
) -> ErrorCode:
    if data == NULL_PTR[SIMD[dreal, 1]]:
        return Error_InvalidPtr
    if buff_size <= 0 or n_ins < 0 or m_outs < 0:
        return Error_InvalidArg
    comptime Real = SIMD[dreal, 1]
    var block_size = size_of[Real]() * SInt(buff_size) * SInt(n_ins + m_outs)
    memset_zero(data.bitcast[U8](), block_size)
    return Error_None

# zero either inputs or outputs streams given the pointer to the relative `data`
def zero_streams_data[dreal: DType](
    data: Ptr[SIMD[dreal, 1]], buff_size: S32, n_chans: S32
) -> ErrorCode:
    return zero_streams_data[dreal](data, buff_size, n_chans, 0)

def zero_inputs_base[dreal: DType](
    base: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, m_outs: S32
) -> ErrorCode:
    comptime Real = SIMD[dreal, 1]
    header_size = align_up(PTR_SIZE * SInt(n_ins + m_outs), align_of[Real]())
    data_ins = base.bitcast[U8]() + header_size
    return zero_streams_data(data_ins.bitcast[Real](), buff_size, n_ins)

def zero_outputs_base[dreal: DType](
    base: Ptr[SIMD[dreal, 1]], buff_size: S32, n_ins: S32, m_outs: S32
) -> ErrorCode:
    comptime Real = SIMD[dreal, 1]
    header_size = align_up(PTR_SIZE * SInt(n_ins + m_outs), align_of[Real]())
    var data_raw = base.bitcast[U8]() + header_size
    var data_outs = data_raw + SInt(n_ins) * SInt(buff_size) * size_of[Real]()
    return zero_streams_data(data_outs.bitcast[Real](), buff_size, m_outs)

def make_streams[dreal: DType](
    buff_size: S32, n_ins: S32, m_outs: S32
) -> Res[Ptr[SIMD[dreal, 1]], ErrorCode]:
    var base, err = alloc_streams[dreal](buff_size, n_ins, m_outs)
    if err != Error_None:
        return NULL_PTR[SIMD[dreal, 1]], err
    _ = init_streams[dreal](base, buff_size, n_ins, m_outs)
    return base, Error_None,

def free_streams[dreal: DType](base: Ptr[SIMD[dreal, 1]]):
    comptime Real = SIMD[dreal, 1]
    if base == NULL_PTR[Real]:
        return
    base.free()
