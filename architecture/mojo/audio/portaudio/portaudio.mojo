# audio/portaudio.mojo

from conf import *
from dsp import *
from .ffi import *

comptime OptPtr[T: AnyType, origin: Origin] = Optional[Ptr[T, origin]]

# --------------------------------------------------------------
# PortAudio architecture implementation.
# --------------------------------------------------------------

comptime FaustFloat = SIMD[F32.dtype, 1]
comptime dfaust = FaustFloat.dtype 
comptime NULL_STREAM = PaStream(unsafe_from_address=0)

struct PortAudio(FaustAudio):
    var alive:  Bool
    var stream: PaStream

    @always_inline
    def __init__(out driver):
        driver.alive = False
        driver.stream = NULL_STREAM
        pass

    @always_inline
    def init(mut driver) -> S32:
        err = pa_initialize()
        if err:
            return err
        driver.alive = True
        return PA_NO_ERROR

    @always_inline
    def stop(mut driver) -> S32:
        if not driver.alive:
            return FAUST_STOPPED_NOT_ALIVE
        err = pa_stop_stream(driver.stream)
        if err:
            return err
        err = pa_close_stream(driver.stream)
        if err:
            return err
        return pa_terminate()

    @always_inline
    def start[Dsp: FaustDsp](mut driver, mut dsp: Dsp) -> S32:
        if not driver.alive:
            return PA_NOT_INITIALIZED

        in_device = pa_get_default_input_device()
        if (in_device < 0):
            return FAUST_NO_DEFAULT_IN_DEVICE
        out_device = pa_get_default_output_device()
        if (out_device < 0):
            return FAUST_NO_DEFAULT_OUT_DEVICE

        var in_device_info: OptPtr[PaDeviceInfo, READ_EXT]
        in_device_info = pa_get_device_info(in_device)
        if not in_device_info:
            return PA_INVALID_DEVICE
        in_latency = in_device_info.unsafe_value()[].default_low_input_latency
        var out_device_info: OptPtr[PaDeviceInfo, READ_EXT]
        out_device_info = pa_get_device_info(out_device)
        if not out_device_info:
            return PA_INVALID_DEVICE
        out_latency = out_device_info.unsafe_value()[].default_low_output_latency

        var n_ins = dsp.get_num_inputs()
        var m_outs = dsp.get_num_outputs()

        driver.stream, err = faust_open_stream[Dsp](
            faust_stream_param(in_device, n_ins, in_latency),
            faust_stream_param(out_device, m_outs, out_latency),
            BUFF_SIZE,
            dsp,
        )

        if err:
            return err

        err = pa_start_stream(driver.stream)
        if err:
            return err

        return PA_NO_ERROR

# --------------------------------------------------------------
# Free helpers and comptime constants definitions
# --------------------------------------------------------------

# Faust constants

comptime BUFF_SIZE    = 256
comptime FAUST_FORMAT = PA_FLOAT32 | PA_NON_INTERLEAVED
comptime FAUST_NOFLAG = 0

comptime FAUST_NO_DEFAULT_IN_DEVICE  = PaError(-6999)
comptime FAUST_NO_DEFAULT_OUT_DEVICE = PaError(-6998)
comptime FAUST_STOPPED_NOT_ALIVE     = PaError(-3999)
comptime FAUST_ALREADY_ALIVE         = PaError(-3998)

# Faust callback

@always_inline
def faust_callback[Dsp: FaustDsp](
    input:     AnyPtr[READ_EXT],
    output:    AnyPtr[MUTA_EXT],
    count:     PaULong,
    time:      Ptr[PaStreamCallbackTimeInfo, READ_EXT],
    flags:     PaStreamCallbackFlags,
    data:      AnyPtr[MUTA_EXT],
) -> S32:
    var inputs = input.bitcast[Ptr[FaustFloat, READ_EXT]]()
    var outputs = output.bitcast[Ptr[FaustFloat, MUTA_EXT]]()
    var dsp = data.bitcast[Dsp]()
    dsp[].compute(S32(count), inputs, outputs)
    return PA_CONTINUE

comptime FaustCallbackFunc[Dsp: FaustDsp] = type_of(faust_callback[Dsp])

# Faust open stream

@always_inline
def faust_open_stream[Dsp: FaustDsp](
    var in_param:     PaStreamParameters,
    var out_param:    PaStreamParameters,
    var buff_size:    S32,
    mut dsp:          Dsp
) -> Tuple[PaStream, S32]:
    var stream = NULL_STREAM
    var ptr_in = NULL_PTR[PaStreamParameters, READ_EXT]
    var ptr_out = NULL_PTR[PaStreamParameters, READ_EXT]
    if in_param.channel_count != 0:
        ptr_in = Ptr(to=in_param).unsafe_mut_cast[False]().unsafe_origin_cast[READ_EXT]()
    if out_param.channel_count != 0:
        ptr_out = Ptr(to=out_param).unsafe_mut_cast[False]().unsafe_origin_cast[READ_EXT]()
    err = pa_open_stream(
        Ptr(to=stream).unsafe_origin_cast[MUTA_EXT](),
        ptr_in,
        ptr_out,
        F64(dsp.get_sample_rate()),
        buff_size,
        FAUST_NOFLAG,
        faust_callback[Dsp],
        Ptr(to=dsp).bitcast[NoneType]().unsafe_origin_cast[MUTA_EXT](),
    )
    return stream, err

@always_inline
def faust_stream_param(
    device:     PaDeviceIndex,
    n_chans:    PaInt,
    latency:    PaTime,
) -> PaStreamParameters:
    return PaStreamParameters(
        device,
        n_chans,
        FAUST_FORMAT,
        latency,
        NULL_PTR[NoneType, MUTA_EXT],
    )
