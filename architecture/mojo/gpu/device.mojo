# gpu/device.mojo

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import FaustDspGpu

comptime FAUST_GPU_NO_ERROR = S32(0)
comptime FAUST_GPU_ERROR = S32(-2999)
comptime FAUST_GPU_ALLOCATION_ERROR = S32(-2997)
comptime FAUST_GPU_INVALID_ARGUMENT = S32(-2996)

@fieldwise_init
struct FaustGpuDevice[Dsp: FaustDspGpu](Movable):
    var ctx: DeviceContext
    var dsp_raw: DeviceBuffer[u8]
    var in_buf: DeviceBuffer[dfaust]
    var out_buf: DeviceBuffer[dfaust]
    var work_buf: DeviceBuffer[u8]
    var in_chans: List[DeviceBuffer[dfaust]]
    var out_chans: List[DeviceBuffer[dfaust]]
    var buf_size: S32
    var n_ins: S32
    var n_outs: S32

    def enqueue_input(mut device, chan: S32, input: ImmStream) -> S32:
        try:
            device.in_chans[Int(chan)].enqueue_copy_from(input)
        except e:
            print(e)
            return FAUST_GPU_ERROR
        return FAUST_GPU_NO_ERROR

    def enqueue_compute(mut device) -> S32:
        try:
            Self.Dsp.gpu_compute(
                device.ctx,
                device.dsp_raw,
                device.in_buf,
                device.out_buf,
                device.work_buf,
                device.buf_size
            )
        except e:
            print(e)
            return FAUST_GPU_ERROR
        return FAUST_GPU_NO_ERROR

    def enqueue_output(mut device, chan: S32, output: MutStream) -> S32:
        try:
            device.out_chans[Int(chan)].enqueue_copy_to(output)
        except e:
            print(e)
            return FAUST_GPU_ERROR
        return FAUST_GPU_NO_ERROR

    def synchronize(mut device) -> S32:
        try:
            device.ctx.synchronize()
        except e:
            print(e)
            return FAUST_GPU_ERROR
        return FAUST_GPU_NO_ERROR

def gpu_create_runtime[Dsp: FaustDspGpu](
    state: Ptr[FaustGpuDevice[Dsp]], dsp: Ptr[Dsp], buf_size: S32
) -> S32:
    if buf_size <= 0:
        return FAUST_GPU_INVALID_ARGUMENT

    try:
        var n_ins = dsp[].get_num_inputs()
        var n_outs = dsp[].get_num_outputs()
        var frames = Int(buf_size)
        var in_size = max(Int(n_ins) * frames, 1)
        var out_size = max(Int(n_outs) * frames, 1)
        var work_size = max(Dsp.gpu_work_size(buf_size), 1)

        var ctx = DeviceContext()
        var dsp_raw = ctx.enqueue_create_buffer[u8](size_of[Dsp]())
        var in_buf = ctx.enqueue_create_buffer[dfaust](in_size)
        var out_buf = ctx.enqueue_create_buffer[dfaust](out_size)
        var work_buf = ctx.enqueue_create_buffer[u8](work_size)
        ctx.enqueue_copy(dst_buf=dsp_raw, src_ptr=dsp.unsafe_bitcast[U8]())
        ctx.synchronize()

        var in_chans = List[DeviceBuffer[dfaust]]()
        for chan in range(Int(n_ins)):
            in_chans.append(in_buf.create_sub_buffer[dfaust](chan * frames, frames))

        var out_chans = List[DeviceBuffer[dfaust]]()
        for chan in range(Int(n_outs)):
            out_chans.append(out_buf.create_sub_buffer[dfaust](chan * frames, frames))

        state.unsafe_write(
            FaustGpuDevice[Dsp](
                ctx, dsp_raw, in_buf, out_buf, work_buf,
                in_chans.copy(), out_chans.copy(),
                buf_size, n_ins, n_outs
            )
        )
    except e:
        print(e)
        return FAUST_GPU_ERROR
    return FAUST_GPU_NO_ERROR
