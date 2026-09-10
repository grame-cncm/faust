# audio/portaudio/portaudio.mojo

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
        if driver.alive:
            return FAUST_ALREADY_ALIVE
        var err = pa_initialize()
        if err:
            return err
        driver.alive = True
        return PA_NO_ERROR

    @always_inline
    def is_active(imm driver) -> S32:
        # Main-thread query: 1 = processing, 0 = inactive, negative = error.
        if not driver.alive or driver.stream == None:
            return S32(0)
        return pa_is_stream_active(driver.stream)

    @always_inline
    def stop(mut driver) -> S32:
        if not driver.alive:
            return PA_NO_ERROR
        var err = PA_NO_ERROR
        if driver.stream != None:
            err = pa_stop_stream(driver.stream)
            if err == PA_STREAM_IS_STOPPED:
                err = PA_NO_ERROR
            # Close also aborts an active stream when graceful stop failed.
            var end = pa_close_stream(driver.stream)
            if end:
                # A non-null stream means callback quiescence is NOT proven.
                return end
            driver.stream = NULL_STREAM
        driver.alive = False
        var end = pa_terminate()
        return err if err else end

    @always_inline
    def start[Dsp: FaustDsp](mut driver, var dsp: Ptr[Dsp]) -> S32:
        if not driver.alive:
            return PA_NOT_INITIALIZED
        if driver.stream != None:
            return FAUST_ALREADY_ALIVE
        var n_ins = dsp[].get_num_inputs()
        var m_outs = dsp[].get_num_outputs()
        if n_ins < 0 or m_outs < 0 or n_ins + m_outs == 0:
            return PA_INVALID_CHANNEL_COUNT
        var in_device = PaDeviceIndex(-1)
        var out_device = PaDeviceIndex(-1)
        var in_latency = F64(0)
        var out_latency = F64(0)
        var err = PA_NO_ERROR
        var info: OptPtr[PaDeviceInfo, IMM_NOTRK]
        if n_ins:
            in_device = pa_get_default_input_device()
            if in_device < 0:
                return FAUST_NO_DEFAULT_IN_DEVICE
            info, err = faust_get_device_info(in_device)
            if err:
                return err
            in_latency = info.unsafe_value()[].default_low_input_latency
        if m_outs:
            out_device = pa_get_default_output_device()
            if out_device < 0:
                return FAUST_NO_DEFAULT_OUT_DEVICE
            var info: OptPtr[PaDeviceInfo, IMM_NOTRK]
            info, err = faust_get_device_info(out_device)
            if err:
                return err
            out_latency = info.unsafe_value()[].default_low_output_latency

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

# Faust PortAudio callback wrapper.

@always_inline
def faust_callback[Dsp: FaustDsp](
    input:   OptPtr[Void, IMM_NOTRK],
    output:  OptPtr[Void, MUT_NOTRK],
    count:   PaULong,
    time:    OptPtr[PaStreamCallbackTimeInfo, IMM_NOTRK],
    flags:   PaStreamCallbackFlags,
    data:    OptPtr[Void, MUT_NOTRK],
) -> S32:
    if data == None:
        return PA_ABORT

    var dsp = data.unsafe_value().unsafe_bitcast[Dsp]()
    # Pointer is non-nullable in Mojo. Zero-channel arrays are never read by
    # generated DSP code; use aligned dangling placeholders, not a null unwrap.
    var inputs = ImmStreams.unsafe_dangling()
    var outputs = MutStreams.unsafe_dangling()
    if input != None:
        inputs = input.unsafe_value().unsafe_bitcast[ImmStream]()
    elif dsp[].get_num_inputs():
        return PA_ABORT
    if output != None:
        outputs = output.unsafe_value().unsafe_bitcast[MutStream]()
    elif dsp[].get_num_outputs():
        return PA_ABORT

    dsp[].compute(S32(count), inputs, outputs)

    return PA_CONTINUE

comptime FaustCallbackFunc[Dsp: FaustDsp] = type_of(faust_callback[Dsp])

# Faust PortAudio stream helpers.

@always_inline
def faust_get_device_info(device: PaDeviceIndex) -> Tuple[OptPtr[PaDeviceInfo, IMM_NOTRK], PaError]:
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
        data
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
        NULL_PTR[Void, MUT_NOTRK]
    )


# Faust PortAudio constant definitions.

comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 256]())
comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96]()) * 1000

comptime NULL_STREAM: PaStream = None

comptime FAUST_FORMAT = PA_FLOAT32 | PA_NON_INTERLEAVED
comptime FAUST_NOFLAG = 0

comptime FAUST_NO_DEFAULT_IN_DEVICE  = PaError(-6999)
comptime FAUST_NO_DEFAULT_OUT_DEVICE = PaError(-6998)
comptime FAUST_STOPPED_NOT_ALIVE     = PaError(-3999)
comptime FAUST_ALREADY_ALIVE         = PaError(-3998)
