# gpu/device.mojo

from conf import *
from dsp import FaustDsp
from std.gpu import thread_idx
from max.gpu.host import DeviceBuffer, DeviceContext


comptime FAUST_GPU_NO_ERROR = S32(0)
comptime FAUST_GPU_ERROR = S32(-2999)
comptime FAUST_GPU_ALLOCATION_ERROR = S32(-2997)
comptime FAUST_GPU_INVALID_ARGUMENT = S32(-2996)


@fieldwise_init
struct FaustGpuDevice[Dsp: FaustDsp](Movable):
    var ctx: DeviceContext
    var dsp_buf: DeviceBuffer[u8]
    var input_buf: DeviceBuffer[dfaust]
    var output_buf: DeviceBuffer[dfaust]
    var input_streams: DeviceBuffer[u64]
    var output_streams: DeviceBuffer[u64]
    var input_channels: List[DeviceBuffer[dfaust]]
    var output_channels: List[DeviceBuffer[dfaust]]
    var count: S32
    var n_ins: S32
    var n_outs: S32
    var grid_dim: Int
    var block_dim: Int

    def enqueue_input(
        mut device,
        channel: S32,
        input: Ptr[FaustFloat, IMM_NOTRK]
    ) -> S32:
        try:
            device.input_channels[Int(channel)].enqueue_copy_from(input)
        except e:
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR

    def enqueue_compute(mut device) -> S32:
        try:
            device.ctx.enqueue_function[compute_gpu[Self.Dsp]](
                device.dsp_buf,
                device.count,
                device.input_streams,
                device.output_streams,
                grid_dim=device.grid_dim,
                block_dim=device.block_dim
            )
        except e:
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR

    def enqueue_output(
        mut device,
        channel: S32,
        output: Ptr[FaustFloat, MUT_NOTRK]
    ) -> S32:
        try:
            device.output_channels[Int(channel)].enqueue_copy_to(output)
        except e:
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR

    def synchronize(mut device) -> S32:
        try:
            device.ctx.synchronize()
        except e:
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR


def create_gpu_runtime[Dsp: FaustDsp](
    state: Ptr[FaustGpuDevice[Dsp]],
    dsp: Ptr[Dsp],
    count: S32,
    grid_dim: Int,
    block_dim: Int
) -> S32:
    comptime assert PTR_SIZE == size_of[U64](), "Expected 64 bit pointers."

    if count <= 0 or grid_dim <= 0 or block_dim <= 0:
        return FAUST_GPU_INVALID_ARGUMENT

    try:
        var n_ins = dsp[].get_num_inputs()
        var n_outs = dsp[].get_num_outputs()
        var frames = Int(count)
        var input_size = max(Int(n_ins) * frames, 1)
        var output_size = max(Int(n_outs) * frames, 1)
        var input_streams_size = max(Int(n_ins), 1)
        var output_streams_size = max(Int(n_outs), 1)

        var ctx = DeviceContext()
        var dsp_buf = ctx.enqueue_create_buffer[u8](size_of[Dsp]())
        var input_buf = ctx.enqueue_create_buffer[dfaust](input_size)
        var output_buf = ctx.enqueue_create_buffer[dfaust](output_size)
        var input_streams = ctx.enqueue_create_buffer[u64](input_streams_size)
        var output_streams = ctx.enqueue_create_buffer[u64](
            output_streams_size
        )

        ctx.enqueue_copy(dst_buf=dsp_buf, src_ptr=dsp.unsafe_bitcast[U8]())
        ctx.enqueue_function[init_streams](
            input_buf,
            output_buf,
            input_streams,
            output_streams,
            count,
            n_ins,
            n_outs,
            grid_dim=1,
            block_dim=max(input_streams_size, output_streams_size)
        )
        ctx.synchronize()

        var input_channels = List[DeviceBuffer[dfaust]]()
        for channel in range(Int(n_ins)):
            input_channels.append(
                input_buf.create_sub_buffer[dfaust](
                    channel * frames, frames
                )
            )

        var output_channels = List[DeviceBuffer[dfaust]]()
        for channel in range(Int(n_outs)):
            output_channels.append(
                output_buf.create_sub_buffer[dfaust](
                    channel * frames, frames
                )
            )

        state.unsafe_write(
            FaustGpuDevice[Dsp](
                ctx,
                dsp_buf,
                input_buf,
                output_buf,
                input_streams,
                output_streams,
                input_channels.copy(),
                output_channels.copy(),
                count,
                n_ins,
                n_outs,
                grid_dim,
                block_dim
            )
        )
    except e:
        return FAUST_GPU_ERROR

    return FAUST_GPU_NO_ERROR


def init_streams(
    input_buf: Pointer[FaustFloat, MUT_ANY],
    output_buf: Pointer[FaustFloat, MUT_ANY],
    input_streams: Pointer[U64, MUT_ANY],
    output_streams: Pointer[U64, MUT_ANY],
    count: S32,
    n_ins: S32,
    n_outs: S32
) -> None:
    var channel = Int(thread_idx.x)

    if channel < Int(n_ins):
        var inputs = input_streams.unsafe_bitcast[
            Ptr[FaustFloat, IMM_NOTRK]
        ]()
        inputs[unsafe_offset=channel] = input_buf.unsafe_offset(
            channel * Int(count)
        ).unsafe_mut_cast[False]().unsafe_origin_cast[IMM_NOTRK]()

    if channel < Int(n_outs):
        var outputs = output_streams.unsafe_bitcast[
            Ptr[FaustFloat, MUT_NOTRK]
        ]()
        outputs[unsafe_offset=channel] = output_buf.unsafe_offset(
            channel * Int(count)
        ).unsafe_origin_cast[MUT_NOTRK]()


def compute_gpu[Dsp: FaustDsp](
    dsp_buf: Pointer[U8, MUT_ANY],
    count: S32,
    input_streams: Pointer[U64, MUT_ANY],
    output_streams: Pointer[U64, MUT_ANY]
) -> None:
    var dsp = dsp_buf.unsafe_bitcast[Dsp]()
    var inputs = input_streams.unsafe_bitcast[
        Ptr[FaustFloat, IMM_NOTRK]
    ]().unsafe_mut_cast[False]().unsafe_origin_cast[IMM_NOTRK]()
    var outputs = output_streams.unsafe_bitcast[
        Ptr[FaustFloat, MUT_NOTRK]
    ]().unsafe_origin_cast[MUT_NOTRK]()

    dsp[].compute(count, inputs, outputs)
