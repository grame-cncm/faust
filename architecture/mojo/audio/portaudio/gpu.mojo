# audio/portaudio/gpu.mojo

from conf import *
from dsp import FaustDsp
from gpu.device import (
    FaustGpuDevice,
    create_gpu_runtime,
    FAUST_GPU_ALLOCATION_ERROR
)
from .ffi import *
from .portaudio import *


struct PortAudioGpu[Dsp: FaustDsp]:
    var alive: Bool
    var stream: PaStream
    var state: OptPtr[FaustGpuDevice[Self.Dsp], MUT_NOTRK]
    var grid_dim: Int
    var block_dim: Int

    def __init__(
        out driver,
        grid_dim: Int = 1,
        block_dim: Int = 1
    ):
        driver.alive = False
        driver.stream = NULL_STREAM
        driver.state = None
        driver.grid_dim = grid_dim
        driver.block_dim = block_dim

    def init(mut driver) -> S32:
        if driver.alive:
            return FAUST_ALREADY_ALIVE

        var err = pa_initialize()
        if err:
            return err

        driver.alive = True
        return PA_NO_ERROR

    def start(mut driver, dsp: Ptr[Self.Dsp]) -> S32:
        if not driver.alive:
            return PA_NOT_INITIALIZED
        if driver.stream != None:
            return FAUST_ALREADY_ALIVE

        var n_ins = dsp[].get_num_inputs()
        var n_outs = dsp[].get_num_outputs()
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

        var state: OptPtr[FaustGpuDevice[Self.Dsp], MUT_NOTRK] = unsafe_alloc[
            FaustGpuDevice[Self.Dsp]
        ](1)
        if state == None:
            return FAUST_GPU_ALLOCATION_ERROR

        var state_ptr = state.unsafe_value()
        err = create_gpu_runtime[Self.Dsp](
            state_ptr,
            dsp,
            BUFF_SIZE,
            driver.grid_dim,
            driver.block_dim
        )
        if err:
            state_ptr.unsafe_free()
            return err

        driver.state = state_ptr
        driver.stream, err = gpu_open_stream[Self.Dsp](
            faust_stream_param(in_device, n_ins, in_latency),
            faust_stream_param(out_device, n_outs, out_latency),
            dsp[].get_sample_rate(),
            state_ptr
        )

        if err:
            driver._release_state()
            return err
        if driver.stream == None:
            driver._release_state()
            return PA_BAD_STREAM_PTR

        err = pa_start_stream(driver.stream)
        if err:
            _ = pa_close_stream(driver.stream)
            driver.stream = NULL_STREAM
            driver._release_state()
            return err

        return PA_NO_ERROR

    def stop(mut driver) -> S32:
        if not driver.alive:
            return FAUST_STOPPED_NOT_ALIVE

        if driver.stream != None:
            var err = pa_stop_stream(driver.stream)
            if err:
                return err

            err = pa_close_stream(driver.stream)
            if err:
                return err

            driver.stream = NULL_STREAM

        driver._release_state()
        driver.alive = False
        return pa_terminate()

    def _release_state(mut driver) -> None:
        if driver.state == None:
            return

        var state = driver.state.unsafe_value()
        state.unsafe_deinit_pointee()
        state.unsafe_free()
        driver.state = None


def gpu_open_stream[Dsp: FaustDsp](
    var in_param: PaStreamParameters,
    var out_param: PaStreamParameters,
    sample_rate: S32,
    state: Ptr[FaustGpuDevice[Dsp]]
) -> Tuple[PaStream, S32]:
    var stream = NULL_STREAM
    var ptr_in = NULL_PTR[PaStreamParameters, IMM_NOTRK]
    var ptr_out = NULL_PTR[PaStreamParameters, IMM_NOTRK]
    var data: OptPtr[Void, MUT_NOTRK] = state.unsafe_bitcast[Void]()

    if in_param.channel_count != 0:
        ptr_in = Ptr(to=in_param).unsafe_mut_cast[False]().unsafe_origin_cast[
            IMM_NOTRK
        ]()
    if out_param.channel_count != 0:
        ptr_out = Ptr(to=out_param).unsafe_mut_cast[False]().unsafe_origin_cast[
            IMM_NOTRK
        ]()

    var err = pa_open_stream(
        Ptr(to=stream).unsafe_origin_cast[MUT_NOTRK](),
        ptr_in,
        ptr_out,
        PaTime(sample_rate),
        BUFF_SIZE,
        FAUST_NOFLAG,
        gpu_callback[Dsp],
        data
    )

    return stream, err


def gpu_callback[Dsp: FaustDsp](
    input: OptPtr[Void, IMM_NOTRK],
    output: OptPtr[Void, MUT_NOTRK],
    count: PaULong,
    time: OptPtr[PaStreamCallbackTimeInfo, IMM_NOTRK],
    flags: PaStreamCallbackFlags,
    data: OptPtr[Void, MUT_NOTRK]
) -> S32:
    if data == None:
        return PA_ABORT

    var state = data.unsafe_value().unsafe_bitcast[FaustGpuDevice[Dsp]]()
    if S32(count) != state[].count:
        return PA_ABORT

    if state[].n_ins != 0:
        if input == None:
            return PA_ABORT

        var inputs = input.unsafe_value().unsafe_bitcast[
            Ptr[FaustFloat, IMM_NOTRK]
        ]()
        for channel in range(state[].n_ins):
            if state[].enqueue_input(
                channel, inputs[unsafe_offset=channel]
            ):
                return PA_ABORT

    if state[].enqueue_compute():
        return PA_ABORT

    if state[].n_outs != 0:
        if output == None:
            return PA_ABORT

        var outputs = output.unsafe_value().unsafe_bitcast[
            Ptr[FaustFloat, MUT_NOTRK]
        ]()
        for channel in range(state[].n_outs):
            if state[].enqueue_output(
                channel, outputs[unsafe_offset=channel]
            ):
                return PA_ABORT

    if state[].synchronize():
        return PA_ABORT

    return PA_CONTINUE
