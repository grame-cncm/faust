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
    var in_chans: List[DeviceBuffer[dfaust]]
    var out_chans: List[DeviceBuffer[dfaust]]
    var buf_size: S32
    var n_ins: S32
    var n_outs: S32
    var grid_dim: Int
    var block_dim: Int

    def enqueue_input(mut device, chan: S32, input: Ptr[FaustFloat, IMM_NOTRK]) -> S32:
        try:
            device.in_chans[Int(chan)].enqueue_copy_from(input)
        except e:
            print(e)
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR

    def enqueue_compute(mut device) -> S32:
        try:
            device.ctx.enqueue_function[Self.Dsp.gpu_compute](
                device.dsp_raw, device.buf_size, device.in_buf, device.out_buf,
                grid_dim=device.grid_dim, block_dim=device.block_dim
            )
        except e:
            print(e)
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR

    def enqueue_output(mut device, chan: S32, output: Ptr[FaustFloat, MUT_NOTRK]) -> S32:
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
    state: Ptr[FaustGpuDevice[Dsp]], dsp: Ptr[Dsp], buf_size: S32, grid_dim: Int, block_dim: Int
) -> S32:
    if buf_size <= 0 or grid_dim <= 0 or block_dim <= 0:
        return FAUST_GPU_INVALID_ARGUMENT

    try:
        var n_ins = dsp[].get_num_inputs()
        var n_outs = dsp[].get_num_outputs()
        var frames = Int(buf_size)
        var in_size = max(Int(n_ins) * frames, 1)
        var out_size = max(Int(n_outs) * frames, 1)

        var ctx = DeviceContext()
        var dsp_raw = ctx.enqueue_create_buffer[u8](size_of[Dsp]())
        var in_buf = ctx.enqueue_create_buffer[dfaust](in_size)
        var out_buf = ctx.enqueue_create_buffer[dfaust](out_size)
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
                ctx, dsp_raw, in_buf, out_buf, in_chans.copy(), out_chans.copy(),
                buf_size, n_ins, n_outs, grid_dim, block_dim
            )
        )
    except e:
        print(e)
        return FAUST_GPU_ERROR

    return FAUST_GPU_NO_ERROR
