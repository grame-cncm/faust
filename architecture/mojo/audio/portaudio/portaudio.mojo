# audio/portaudio.mojo

from conf import *
from dsp import *
from audio import FaustAudio
from .ffi import *

# ==============================================================
# PortAudio architecture implementation.
# Provides the FaustAudio API for PortAudio mainly through
# direct FFI calls. Defines additional helpers using the `faust`
# prefix, with proper casing, for Faust-domain operations.
# ==============================================================

# Faust Portaudio public API.

struct PortAudio(FaustAudio):
    var alive:  Bool
    var stream: PaStream

    @always_inline
    def __init__(out driver):
        driver.alive = False
        driver.stream = NULL_STREAM

    @always_inline
    def init(mut driver) -> S32:
        var err = pa_initialize()
        if err:
            return err
        driver.alive = True
        return PA_NO_ERROR

    @always_inline
    def stop(mut driver) -> S32:
        if not driver.alive:
            return FAUST_STOPPED_NOT_ALIVE
        if driver.stream == None:
            return FAUST_STOPPED_NOT_ALIVE

        var err = pa_stop_stream(driver.stream)
        if err:
            return err
        err = pa_close_stream(driver.stream)
        if err:
            return err

        driver.stream = NULL_STREAM
        driver.alive = False

        return pa_terminate()

    @always_inline
    def start[Dsp: FaustDsp](mut driver, var dsp: Ptr[Dsp]) -> S32:
        if not driver.alive:
            return PA_NOT_INITIALIZED

        var in_device = pa_get_default_input_device()
        if (in_device < 0):
            return FAUST_NO_DEFAULT_IN_DEVICE
        var out_device = pa_get_default_output_device()
        if (out_device < 0):
            return FAUST_NO_DEFAULT_OUT_DEVICE

        var err: S32
        var in_device_info: OptPtr[PaDeviceInfo, IMM_NOTRK]
        var out_device_info: OptPtr[PaDeviceInfo, IMM_NOTRK]

        in_device_info, err = faust_get_device_info(in_device)
        if err:
            return err
        var in_latency = in_device_info.unsafe_value()[].default_low_input_latency

        out_device_info, err = faust_get_device_info(out_device)
        if err:
            return err
        var out_latency = out_device_info.unsafe_value()[].default_low_output_latency

        var n_ins = dsp[].get_num_inputs()
        var m_outs = dsp[].get_num_outputs()

        driver.stream, err = faust_open_stream[Dsp](
            faust_stream_param(in_device, n_ins, in_latency),
            faust_stream_param(out_device, m_outs, out_latency),
            BUFF_SIZE,
            dsp,
        )

        if err:
            return err
        if driver.stream == None:
            return PA_BAD_STREAM_PTR

        err = pa_start_stream(driver.stream)
        if err:
            return err

        return PA_NO_ERROR

# Faust PortAudio constant definitions.

comptime BUFF_SIZE    = S32(get_defined_int["BUFF_SIZE", 256]())
comptime SAMP_RATE    = S32(get_defined_int["SAMP_RATE", 96]()) * 1000

comptime NULL_STREAM: PaStream = None

comptime FAUST_FORMAT = PA_FLOAT32 | PA_NON_INTERLEAVED
comptime FAUST_NOFLAG = 0

comptime FAUST_NO_DEFAULT_IN_DEVICE  = PaError(-6999)
comptime FAUST_NO_DEFAULT_OUT_DEVICE = PaError(-6998)
comptime FAUST_STOPPED_NOT_ALIVE     = PaError(-3999)
comptime FAUST_ALREADY_ALIVE         = PaError(-3998)

# Faust PortAudio callback wrapper.

@always_inline
def faust_callback[Dsp: FaustDsp](
    input:     OptPtr[Void, IMM_NOTRK],
    output:    OptPtr[Void, MUT_NOTRK],
    count:     PaULong,
    time:      OptPtr[PaStreamCallbackTimeInfo, IMM_NOTRK],
    flags:     PaStreamCallbackFlags,
    data:      OptPtr[Void, MUT_NOTRK],
) -> S32:
    if data == None:
        return PA_ABORT

    var input_ptr = input.unsafe_value()
    var output_ptr = output.unsafe_value()

    var inputs = input_ptr.unsafe_bitcast[Ptr[FaustFloat, IMM_NOTRK]]()
    var outputs = output_ptr.unsafe_bitcast[Ptr[FaustFloat, MUT_NOTRK]]()
    var dsp = data.unsafe_value().unsafe_bitcast[Dsp]()

    dsp[].compute(S32(count), inputs, outputs)

    return PA_CONTINUE

comptime FaustCallbackFunc[Dsp: FaustDsp] = type_of(faust_callback[Dsp])

# Faust PortAudio stream helpers.

@always_inline
def faust_get_device_info(
    device: PaDeviceIndex
) -> Tuple[OptPtr[PaDeviceInfo, IMM_NOTRK], PaError]:
    var info: OptPtr[PaDeviceInfo, IMM_NOTRK] = pa_get_device_info(device)
    if info == None:
        return None, PA_INVALID_DEVICE
    return info, PA_NO_ERROR

@always_inline
def faust_open_stream[Dsp: FaustDsp](
    var in_param:     PaStreamParameters,
    var out_param:    PaStreamParameters,
    var buff_size:    S32,
    var dsp:          Ptr[Dsp]
) -> Tuple[PaStream, S32]:
    var stream = NULL_STREAM
    var ptr_in = NULL_PTR[PaStreamParameters, IMM_NOTRK]
    var ptr_out = NULL_PTR[PaStreamParameters, IMM_NOTRK]
    var data: OptPtr[Void, MUT_NOTRK] = dsp.unsafe_bitcast[NoneType]()

    if in_param.channel_count != 0:
        ptr_in = Ptr(to=in_param).unsafe_mut_cast[False]().unsafe_origin_cast[IMM_NOTRK]()
    if out_param.channel_count != 0:
        ptr_out = Ptr(to=out_param).unsafe_mut_cast[False]().unsafe_origin_cast[IMM_NOTRK]()

    var err = pa_open_stream(
        Ptr(to=stream).unsafe_origin_cast[MUT_NOTRK](),
        ptr_in,
        ptr_out,
        F64(dsp[].get_sample_rate()),
        buff_size,
        FAUST_NOFLAG,
        faust_callback[Dsp],
        data,
    )

    return stream, err

@always_inline
def faust_stream_param(
    device: PaDeviceIndex, n_chans: PaInt, latency: PaTime
) -> PaStreamParameters:
    return PaStreamParameters(
        device,
        n_chans,
        FAUST_FORMAT,
        latency,
        NULL_PTR[Void, MUT_NOTRK],
    )
