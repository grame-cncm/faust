# audio/portaudio/gpu.mojo

from conf import *
from dsp import FaustDspGpu
from gpu import *
from gui import BridgeGui

from .ffi import *
from .portaudio import *


# Optional audio-thread hooks: no allocation, rendering or access from main.
# Their context must outlive stop(). The driver has no native GUI dependency.
comptime GpuSync = def(data: OptPtr[Void, MUT_NOTRK]) thin -> None


def gpu_no_sync(data: OptPtr[Void, MUT_NOTRK]) -> None:
    pass


struct PortAudioGpu[Dsp: FaustDspGpu]:
    var alive: Bool
    var stream: PaStream
    var state: OptPtr[FaustGpuDevice[Self.Dsp], MUT_NOTRK]
    var bridge: BridgeGui
    var params: List[DeviceBuffer[u8]]
    var pull: GpuSync
    var push: GpuSync
    var data: OptPtr[Void, MUT_NOTRK]
    var err: S32  # Callback-owned; read only after the stream has closed.

    def __init__(out driver):
        driver.alive = False
        driver.stream = NULL_STREAM
        driver.state = None
        driver.bridge = BridgeGui()
        driver.params = List[DeviceBuffer[u8]]()
        driver.pull = gpu_no_sync
        driver.push = gpu_no_sync
        driver.data = None
        driver.err = FAUST_GPU_NO_ERROR

    def init(mut driver) -> S32:
        if driver.alive:
            return FAUST_ALREADY_ALIVE

        var err = pa_initialize()
        if err:
            return err

        driver.alive = True
        return PA_NO_ERROR

    def start(
        mut driver,
        dsp: Ptr[Self.Dsp],
        pull: GpuSync = gpu_no_sync,
        push: GpuSync = gpu_no_sync,
        data: OptPtr[Void, MUT_NOTRK] = None
    ) -> S32:
        if not driver.alive:
            return PA_NOT_INITIALIZED
        if driver.stream != None or driver.state != None:
            return FAUST_ALREADY_ALIVE

        var n_ins = dsp[].get_num_inputs()
        var n_outs = dsp[].get_num_outputs()
        if n_ins < 0 or n_outs < 0 or n_ins + n_outs == 0:
            return PA_INVALID_CHANNEL_COUNT
        var in_device = PA_NO_DEVICE
        var out_device = PA_NO_DEVICE
        var in_latency = PaTime(0)
        var out_latency = PaTime(0)
        var err: PaError

        if n_ins != 0:
            in_device = pa_get_default_input_device()
            if in_device < 0:
                return FAUST_NO_DEFAULT_IN_DEVICE

            var in_info, in_info_err = faust_get_device_info(in_device)
            if in_info_err:
                return in_info_err
            in_latency = in_info.unsafe_value()[].default_low_input_latency

        if n_outs != 0:
            out_device = pa_get_default_output_device()
            if out_device < 0:
                return FAUST_NO_DEFAULT_OUT_DEVICE

            var out_info, out_info_err = faust_get_device_info(out_device)
            if out_info_err:
                return out_info_err
            out_latency = out_info.unsafe_value()[].default_low_output_latency

        driver.bridge.reset(dsp.unsafe_bitcast[U8]())
        dsp[].build_user_interface(driver.bridge)
        if not driver.bridge.valid:
            return FAUST_GPU_INVALID_ARGUMENT
        for zone in driver.bridge.zones:
            if zone.offset < 0 or zone.offset > size_of[Self.Dsp]() - size_of[FaustFloat]():
                return FAUST_GPU_INVALID_ARGUMENT

        driver.pull = pull
        driver.push = push
        driver.data = data
        driver.err = FAUST_GPU_NO_ERROR

        driver.state = unsafe_alloc[FaustGpuDevice[Self.Dsp]](1)
        if driver.state == None:
            return FAUST_GPU_ALLOCATION_ERROR

        var state = driver.state.unsafe_value()
        err = gpu_create_runtime[Self.Dsp](state, dsp, BUFF_SIZE)
        if err:
            state.unsafe_free()
            driver.state = None
            return err

        try:
            for zone in driver.bridge.zones:
                driver.params.append(
                    state[].dsp_raw.create_sub_buffer[u8](
                        zone.offset, size_of[FaustFloat]()
                    )
                )
        except:
            _ = driver._release_state()
            return FAUST_GPU_ERROR

        var driver_ptr = Ptr(to=driver).unsafe_origin_cast[MUT_NOTRK]()
        driver.stream, err = gpu_open_stream[Self.Dsp](
            faust_stream_param(in_device, n_ins, in_latency),
            faust_stream_param(out_device, n_outs, out_latency),
            dsp[].get_sample_rate(), driver_ptr
        )
        if err:
            if driver.stream == None:
                _ = driver._release_state()
            return err
        if driver.stream == None:
            _ = driver._release_state()
            return PA_BAD_STREAM_PTR

        err = pa_start_stream(driver.stream)
        if err:
            # stop() must prove callback quiescence before releasing anything.
            return err

        return PA_NO_ERROR

    def is_active(imm driver) -> S32:
        if not driver.alive or driver.stream == None:
            return S32(0)
        return pa_is_stream_active(driver.stream)

    def stop(mut driver) -> S32:
        if not driver.alive:
            return PA_NO_ERROR

        var err = PA_NO_ERROR
        if driver.stream != None:
            err = pa_stop_stream(driver.stream)
            if err == PA_STREAM_IS_STOPPED:
                err = PA_NO_ERROR
            var end = pa_close_stream(driver.stream)
            if end:
                return end
            driver.stream = NULL_STREAM

        var end = driver._release_state()
        if end:
            return end
        driver.alive = False
        end = pa_terminate()
        if driver.err:
            return driver.err
        return err if err else end

    @always_inline
    def _enqueue_params(mut driver) -> S32:
        try:
            for i in range(len(driver.bridge.zones)):
                if driver.bridge.zones[i].passive:
                    continue
                var value = driver.bridge.zones[i].host[]
                if value == driver.bridge.zones[i].cached:
                    continue
                driver.params[i].enqueue_copy_from(
                    driver.bridge.zones[i].host.unsafe_bitcast[U8]().unsafe_mut_cast[False]()
                )
                driver.bridge.zones[i].cached = value
        except:
            return FAUST_GPU_ERROR

        return FAUST_GPU_NO_ERROR

    @always_inline
    def _enqueue_meters(mut driver) -> S32:
        try:
            for i in range(len(driver.bridge.zones)):
                if driver.bridge.zones[i].passive:
                    driver.params[i].enqueue_copy_to(
                        driver.bridge.zones[i].host.unsafe_bitcast[U8]()
                    )
        except:
            return FAUST_GPU_ERROR
        return FAUST_GPU_NO_ERROR

    def _abort(mut driver, err: S32) -> S32:
        driver.err = err
        # Even a partially enqueued block may still reference PortAudio memory.
        if driver.state != None:
            if driver.state.unsafe_value()[].synchronize():
                # Unrecoverable device failure: do not hand live DMA buffers
                # back to PortAudio. No destructors may free in-flight storage.
                external_call["_Exit", Void](S32(1))
        return PA_ABORT

    def _release_state(mut driver) -> S32:
        if driver.state == None:
            return FAUST_GPU_NO_ERROR
        var state = driver.state.unsafe_value()
        var err = state[].synchronize()
        if err:
            # Keep all storage alive when completion cannot be established.
            return err
        driver.params = List[DeviceBuffer[u8]]()
        state.unsafe_deinit_pointee()
        state.unsafe_free()
        driver.state = None
        return FAUST_GPU_NO_ERROR


def gpu_open_stream[Dsp: FaustDspGpu](
    var in_param:    PaStreamParameters,
    var out_param:   PaStreamParameters,
    var sample_rate: S32,
    var driver:      Ptr[PortAudioGpu[Dsp]]
) -> Tuple[PaStream, S32]:
    var stream = NULL_STREAM
    var ptr_in = NULL_PTR[PaStreamParameters, IMM_NOTRK]
    var ptr_out = NULL_PTR[PaStreamParameters, IMM_NOTRK]
    var data: OptPtr[Void, MUT_NOTRK] = driver.unsafe_bitcast[Void]()

    if in_param.channel_count != 0:
        ptr_in = Ptr(to=in_param).unsafe_mut_cast[False]().unsafe_origin_cast[IMM_NOTRK]()
    if out_param.channel_count != 0:
        ptr_out = Ptr(to=out_param).unsafe_mut_cast[False]().unsafe_origin_cast[IMM_NOTRK]()

    var err = pa_open_stream(
        Ptr(to=stream).unsafe_origin_cast[MUT_NOTRK](), ptr_in, ptr_out,
        PaTime(sample_rate), BUFF_SIZE, FAUST_NOFLAG,
        gpu_callback[Dsp], data
    )
    return stream, err


def gpu_callback[Dsp: FaustDspGpu](
    input: OptPtr[Void, IMM_NOTRK],
    output: OptPtr[Void, MUT_NOTRK],
    count: PaULong,
    time: OptPtr[PaStreamCallbackTimeInfo, IMM_NOTRK],
    flags: PaStreamCallbackFlags,
    data: OptPtr[Void, MUT_NOTRK]
) -> S32:
    if data == None:
        return PA_ABORT

    var driver = data.unsafe_value().unsafe_bitcast[PortAudioGpu[Dsp]]()
    if driver[].state == None:
        return PA_ABORT
    var state = driver[].state.unsafe_value()
    if count != PaULong(state[].buf_size):
        return driver[]._abort(FAUST_GPU_INVALID_ARGUMENT)

    if (state[].n_ins != 0 and input == None) or (state[].n_outs != 0 and output == None):
        return driver[]._abort(FAUST_GPU_INVALID_ARGUMENT)

    # Stable host zones belong to this callback until the final synchronize.
    driver[].pull(driver[].data)

    if state[].n_ins != 0:
        var inputs = input.unsafe_value().unsafe_bitcast[Ptr[FaustFloat, IMM_NOTRK]]()
        for chan in range(state[].n_ins):
            var err = state[].enqueue_input(chan, inputs[unsafe_offset=chan])
            if err:
                return driver[]._abort(err)

    var err = driver[]._enqueue_params()
    if not err:
        err = state[].enqueue_compute()
    if not err:
        err = driver[]._enqueue_meters()
    if err:
        return driver[]._abort(err)

    if state[].n_outs != 0:
        var outputs = output.unsafe_value().unsafe_bitcast[Ptr[FaustFloat, MUT_NOTRK]]()
        for chan in range(state[].n_outs):
            err = state[].enqueue_output(chan, outputs[unsafe_offset=chan])
            if err:
                return driver[]._abort(err)

    err = state[].synchronize()
    if err:
        return driver[]._abort(err)
    driver[].push(driver[].data)
    return PA_CONTINUE
