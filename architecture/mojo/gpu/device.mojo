# gpu/device.mojo

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp.gpu import FaustDspGpu
from gui.map import GpuControlMap, GPU_ZONE_CAP

comptime FAUST_GPU_NO_ERROR = S32(0)
comptime FAUST_GPU_ERROR = S32(-2999)
comptime FAUST_GPU_ALLOCATION_ERROR = S32(-2997)
comptime FAUST_GPU_INVALID_ARGUMENT = S32(-2996)

# ==============================================================
# Faust GPU device implementation.
# ==============================================================

# Resources allocated by `GpuDevice.prepare` for a concrete DSP.
# @rep
# - `ctx`: context that owns GPU operations.
# - `dsp`: persistent DSP state on the device.
# - `ins`: contiguous buffer for input channels.
# - `outs`: contiguous buffer for output channels.
# - `work`: temporary memory required by the DSP.
# - `in_chans`: channel views into `ins`.
# - `out_chans`: channel views into `outs`.
# - `active_zones`: host addresses of control zones.
# - `active_bufs`: views into device-side DSP control zones.
# - `cached`: last control values sent to the device.
# - `passive_zones`: host addresses of bargraph zones.
# - `passive_bufs`: views into device-side DSP bargraph zones.
# - `block_size`: frames in each prepared block.
# - `n_ins`: number of input channels.
# - `n_outs`: number of output channels.
@fieldwise_init
struct GpuStorage[Dsp: FaustDspGpu](Movable):
    var ctx:            DeviceContext
    var dsp:            DeviceBuffer[u8]
    var ins:            DeviceBuffer[dfaust]
    var outs:           DeviceBuffer[dfaust]
    var work:           DeviceBuffer[u8]
    var in_chans:       List[DeviceBuffer[dfaust]]
    var out_chans:      List[DeviceBuffer[dfaust]]
    var active_zones:   Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var active_bufs:    List[DeviceBuffer[u8]]
    var cached:         Arr[FaustFloat, GPU_ZONE_CAP]
    var passive_zones:  Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var passive_bufs:   List[DeviceBuffer[u8]]
    var block_size:     S32
    var n_ins:          S32
    var n_outs:         S32

# Creates GPU storage and converts library exceptions into error codes.
def gpu_create_storage[Dsp: FaustDspGpu](
    var dsp:        Ptr[Dsp],
    imm map:        GpuControlMap,
    imm block_size: S32,
    imm n_ins:      S32,
    imm n_outs:     S32,
    imm work_size:  Int
) -> Tuple[OptPtr[GpuStorage[Dsp], MUT_NOTRK], S32]:
    try:
        var frames = Int(block_size)
        var ctx = DeviceContext()
        var dsp_buf = ctx.enqueue_create_buffer[u8](size_of[Dsp]())
        var ins_buf = ctx.enqueue_create_buffer[dfaust](max(Int(n_ins) * frames, 1))
        var outs_buf = ctx.enqueue_create_buffer[dfaust](max(Int(n_outs) * frames, 1))
        var work_buf = ctx.enqueue_create_buffer[u8](max(work_size, 1))
        ctx.enqueue_copy(dst_buf=dsp_buf, src_ptr=dsp.unsafe_bitcast[U8]())
        ctx.synchronize()

        var in_chans = List[DeviceBuffer[dfaust]]()
        for chan in range(Int(n_ins)):
            in_chans.append(
                ins_buf.create_sub_buffer[dfaust](chan * frames, frames)
            )
        var out_chans = List[DeviceBuffer[dfaust]]()
        for chan in range(Int(n_outs)):
            out_chans.append(
                outs_buf.create_sub_buffer[dfaust](chan * frames, frames)
            )

        var active = Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP](
            fill=Ptr[FaustFloat, MUT_NOTRK].unsafe_dangling()
        )
        var cached = Arr[FaustFloat, GPU_ZONE_CAP](fill=FaustFloat(0))
        var active_bufs = List[DeviceBuffer[u8]]()
        for i in range(Int(map.active_len)):
            active[i] = map.active[i].host
            cached[i] = active[i][]
            active_bufs.append(
                dsp_buf.create_sub_buffer[u8](map.active[i].offset, size_of[FaustFloat]())
            )

        var passive = Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP](
            fill=Ptr[FaustFloat, MUT_NOTRK].unsafe_dangling()
        )
        var passive_bufs = List[DeviceBuffer[u8]]()
        for i in range(Int(map.passive_len)):
            passive[i] = map.passive[i].host
            passive_bufs.append(
                dsp_buf.create_sub_buffer[u8](map.passive[i].offset, size_of[FaustFloat]())
            )

        var storage = GpuStorage[Dsp](
            ctx, dsp_buf, ins_buf, outs_buf, work_buf,
            in_chans^, out_chans^, active^, active_bufs^,
            cached^, passive^, passive_bufs^, block_size, n_ins, n_outs
        )
        var ptr = unsafe_alloc[GpuStorage[Dsp]](1)
        ptr.unsafe_write(storage^)
        return ptr, FAUST_GPU_NO_ERROR
    except:
        return None, FAUST_GPU_ERROR


# A `FaustGpu` that prepares and processes a DSP on the device.
# @desc
# - Prepares the DSP, channels, and required UI zones.
# - Copies controls and inputs, runs kernels, and publishes outputs and meters.
# - Records the first error and releases resources after audio stops.
# @rep
# - state: resources built during `prepare`, or `None`.
# - err: first callback error; `process` returns `None`.
# @note
# - Failed GPU synchronization leaves device storage allocated.
struct GpuDevice[Dsp: FaustDspGpu]:
    var state:  OptPtr[GpuStorage[Self.Dsp], MUT_NOTRK]
    var err:    S32

    def __init__(out gpu):
        gpu.state = None
        gpu.err = FAUST_GPU_NO_ERROR

    def prepare[SourceDsp: FaustDspGpu](
        mut gpu, var dsp: Ptr[SourceDsp], imm map: GpuControlMap,
        imm block_size: S32
    ) -> S32:
        comptime assert SourceDsp == Self.Dsp, "GpuDevice requires its concrete DSP."
        if gpu.state != None or block_size <= 0:
            return FAUST_GPU_INVALID_ARGUMENT
        var err = map.check[Self.Dsp]()
        if err:
            return err
        if map.base != dsp.unsafe_bitcast[U8]():
            return FAUST_GPU_INVALID_ARGUMENT
        var n_ins = dsp[].get_num_inputs()
        var n_outs = dsp[].get_num_outputs()
        if n_ins < 0 or n_outs < 0 or n_ins + n_outs == 0:
            return FAUST_GPU_INVALID_ARGUMENT
        var work_size = Self.Dsp.gpu_work_size(block_size)
        if work_size < 0:
            return FAUST_GPU_INVALID_ARGUMENT
        var storage, code = gpu_create_storage(
            dsp, map, block_size, n_ins, n_outs, work_size
        )
        if code:
            return code
        if storage == None:
            return FAUST_GPU_ALLOCATION_ERROR
        gpu.state = storage.unsafe_value().unsafe_bitcast[GpuStorage[Self.Dsp]]()
        gpu.err = FAUST_GPU_NO_ERROR
        return FAUST_GPU_NO_ERROR

    @always_inline
    def _block(mut gpu, var ins: ImmStreams, var outs: MutStreams) -> S32:
        var state = gpu.state.unsafe_value()
        try:
            for i in range(len(state[].active_bufs)):
                var val = state[].active_zones[i][]
                if val == state[].cached[i]:
                    continue
                state[].cached[i] = val
                # Keep a stable snapshot if the GUI changes a zone during DMA.
                var src = Ptr(to=state[].cached[i]).unsafe_origin_cast[MUT_NOTRK]()
                state[].active_bufs[i].enqueue_copy_from(
                    src.unsafe_bitcast[U8]().unsafe_mut_cast[False]()
                )

            for chan in range(Int(state[].n_ins)):
                state[].in_chans[chan].enqueue_copy_from(ins[unsafe_offset=chan])

            Self.Dsp.gpu_compute(
                state[].ctx, state[].dsp, state[].ins, state[].outs,
                state[].work, state[].block_size
            )

            for chan in range(Int(state[].n_outs)):
                state[].out_chans[chan].enqueue_copy_to(outs[unsafe_offset=chan])
            for i in range(len(state[].passive_bufs)):
                state[].passive_bufs[i].enqueue_copy_to(
                    state[].passive_zones[i].unsafe_bitcast[U8]()
                )
            state[].ctx.synchronize()
        except:
            # An enqueued copy may still access PortAudio's buffers.
            try:
                state[].ctx.synchronize()
            except:
                return FAUST_GPU_ERROR
            return FAUST_GPU_ERROR
        return FAUST_GPU_NO_ERROR

    @always_inline
    def process(
        mut gpu, imm count: S32, var ins: ImmStreams, var outs: MutStreams
    ) -> None:
        if gpu.state == None:
            if not gpu.err:
                gpu.err = FAUST_GPU_INVALID_ARGUMENT
            return
        var state = gpu.state.unsafe_value()
        var err = FAUST_GPU_NO_ERROR
        if count != state[].block_size:
            err = FAUST_GPU_INVALID_ARGUMENT
        elif not gpu.err:
            err = gpu._block(ins, outs)
        if err and not gpu.err:
            gpu.err = err
        if gpu.err:
            for chan in range(Int(state[].n_outs)):
                var out = outs[unsafe_offset=chan]
                for frame in range(Int(count)):
                    out[unsafe_offset=frame] = FaustFloat(0)

    @always_inline
    def get_error(imm gpu) -> S32:
        return gpu.err

    def release(mut gpu) -> S32:
        if gpu.state == None:
            return FAUST_GPU_NO_ERROR
        var state = gpu.state.unsafe_value()
        try:
            state[].ctx.synchronize()
        except:
            return FAUST_GPU_ERROR
        comptime assert conforms_to(GpuStorage[Self.Dsp], Deinitable), (
            "GPU storage must own deinitializable buffers."
        )
        state.unsafe_deinit_pointee()
        state.unsafe_free()
        gpu.state = None
        return FAUST_GPU_NO_ERROR

