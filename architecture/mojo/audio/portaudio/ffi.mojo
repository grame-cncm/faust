#-- audio/portaudio/ffi.mojo


from std.ffi import *


# +----------------------------------------------------------+
# | API                                                      |
# +----------------------------------------------------------+


#-- Query

@always_inline
def pa_get_default_input_device() -> Int32:
    return Int32(
            external_call["Pa_GetDefaultInputDevice", PaDeviceIndex]()
    )

@always_inline
def pa_get_default_output_device() -> Int32:
    return Int32(
            external_call["Pa_GetDefaultOutputDevice", PaDeviceIndex]()
    )

@always_inline
def pa_get_device_info(device: Int32) -> UnsafePointer[PaDeviceInfo, ImmutExternalOrigin]: 
    return (
            external_call[
                "Pa_GetDeviceInfo",
                UnsafePointer[PaDeviceInfo, ImmutExternalOrigin],
                PaDeviceIndex,
            ](
                PaDeviceIndex(device),
            )
    )

@always_inline
def pa_get_stream_info(stream: PaStream[MutExternalOrigin]) -> UnsafePointer[PaStreamInfo, ImmutExternalOrigin]:
    return (
            external_call[
                "Pa_GetStreamInfo",
                UnsafePointer[PaStreamInfo, ImmutExternalOrigin],
                PaStream[MutExternalOrigin],
            ](stream)
    )

@always_inline
def pa_is_format_supported(
    input_parameters:     UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
    output_parameters:    UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
    sample_rate:          Float64,
) -> Int32:
    return Int32(
            external_call[
                "Pa_IsFormatSupported",
                PaError,
                UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
                UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
                PaDouble,
            ](
                input_parameters,
                output_parameters,
                PaDouble(sample_rate),
            )
    )

#-- Lifecycle

@always_inline
def pa_initialize() -> Int32:
    return Int32(
            external_call["Pa_Initialize", PaError]()
    )

@always_inline
def pa_terminate() -> Int32:
    return Int32(
            external_call["Pa_Terminate", PaError]()
    )

#-- Stream creation

@always_inline
def pa_open_default_stream(
    stream:               UnsafePointer[PaStream[MutExternalOrigin], MutExternalOrigin],
    num_inputs:           Int32,
    num_outputs:          Int32,
    sample_format:        UInt64,
    sample_rate:          Int32,
    frames_per_buffer:    Int32,
    stream_callback:      PaStreamCallback,
    user_data:            OpaquePointer[MutExternalOrigin]
) -> Int32:
    return Int32(
            external_call[
                "Pa_OpenDefaultStream",
                PaError,
                UnsafePointer[PaStream[MutExternalOrigin], MutExternalOrigin], # PaStream** aka void**
                PaInt,
                PaInt,
                PaULong,
                PaDouble,
                PaULong,
                PaStreamCallback,
                OpaquePointer[MutExternalOrigin],
            ](
                stream,
                PaInt(num_inputs),
                PaInt(num_outputs),
                PaULong(sample_format),
                PaDouble(Float64(sample_rate)),
                PaULong(UInt64(frames_per_buffer)),
                stream_callback, # OpaquePointer[ImmutExternalOrigin],() | UnsafePointer(to=stream_callback).bitcast[NoneType]()
                user_data # OpaquePointer[MutExternalOrigin]()
            )
    )

@always_inline
def pa_open_stream(
    stream:               UnsafePointer[PaStream[MutExternalOrigin], MutExternalOrigin],
    input_parameters:     UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
    output_parameters:    UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
    sample_rate:          Float64,
    frames_per_buffer:    Int32,
    stream_flags:         UInt64,
    stream_callback:      PaStreamCallback,
    user_data:            OpaquePointer[MutExternalOrigin],
) -> Int32:
    return Int32(
            external_call[
                "Pa_OpenStream",
                PaError,
                UnsafePointer[PaStream[MutExternalOrigin], MutExternalOrigin],
                UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
                UnsafePointer[PaStreamParameters, ImmutExternalOrigin],
                PaDouble,
                PaULong,
                PaStreamFlags,
                PaStreamCallback,
                OpaquePointer[MutExternalOrigin],
            ](
                stream,
                input_parameters,
                output_parameters,
                PaDouble(sample_rate),
                PaULong(UInt64(frames_per_buffer)),
                PaStreamFlags(stream_flags),
                stream_callback,
                user_data,
            )
    )

#-- Stream control

@always_inline
def pa_start_stream(stream: PaStream[MutExternalOrigin]) -> Int32:
    return Int32(
            external_call[
                "Pa_StartStream",
                PaError,
                PaStream[MutExternalOrigin]
            ](stream)
    )

@always_inline
def pa_stop_stream(stream: PaStream[MutExternalOrigin]) -> Int32:
    return Int32(
            external_call[
                "Pa_StopStream",
                PaError,
                PaStream[MutExternalOrigin]
            ](stream)
    )

@always_inline
def pa_close_stream(stream: PaStream[MutExternalOrigin]) -> Int32:
    return Int32(
            external_call[
                "Pa_CloseStream",
                PaError,
                PaStream[MutExternalOrigin]
            ](stream)
    )

@always_inline
def pa_is_stream_active(stream: PaStream[MutExternalOrigin]) -> Int32:
    return Int32(
            external_call[
                "Pa_IsStreamActive",
                PaError,
                PaStream[MutExternalOrigin]
            ](stream)
    )

#-- Blocking I/O

@always_inline
def pa_read_stream(
    stream:    PaStream[MutExternalOrigin],
    buffer:    OpaquePointer[MutExternalOrigin],
    frames:    Int32,
) -> Int32:
    return Int32(
            external_call[
                "Pa_ReadStream",
                PaError,
                PaStream[MutExternalOrigin],
                OpaquePointer[MutExternalOrigin],
                PaULong,
            ](
                stream,
                buffer,
                PaULong(UInt64(frames)),
            )
    )

@always_inline
def pa_write_stream(
    stream:    PaStream[MutExternalOrigin],
    buffer:    OpaquePointer[ImmutExternalOrigin],
    frames:    Int32,
) -> Int32:
    # print("write stream")
    return Int32(
            external_call[
                "Pa_WriteStream",
                PaInt,
                PaStream[MutExternalOrigin],
                OpaquePointer[ImmutExternalOrigin],
                PaULong,
            ](
                stream,
                buffer,
                PaULong(UInt64(frames)),
            )
    )

#-- Utility

@always_inline
def pa_sleep(msec: Int32) -> None:
        external_call[
            "Pa_Sleep",
            NoneType,
            c_long,
        ](c_long(msec))


# +----------------------------------------------------------+
# | Bindings for portaudio types and enums                   |
# +----------------------------------------------------------+


#-- Portaudio C native types

comptime PaInt    = c_int
comptime PaULong  = c_ulong
comptime PaDouble = c_double
comptime PaSLong  = c_long
comptime PaString = CStringSlice[ImmutExternalOrigin]


#-- PaStream
# Portaudio C header defines `PaStream = void`, so `PaStream* = void*`.
# In this module `PaStream = void*`.

comptime PaStream = OpaquePointer


#-- PaError

comptime PaError                                    = PaInt
comptime PA_NO_ERROR                                = PaError(0)
comptime PA_NOT_INITIALIZED                         = PaError(-10000)
comptime PA_UNANTICIPATED_HOST_ERROR                = PaError(-9999)
comptime PA_INVALID_CHANNEL_COUNT                   = PaError(-9998)
comptime PA_INVALID_SAMPLE_RATE                     = PaError(-9997)
comptime PA_INVALID_DEVICE                          = PaError(-9996)
comptime PA_INVALID_FLAG                            = PaError(-9995)
comptime PA_SAMPLE_FORMAT_NOT_SUPPORTED             = PaError(-9994)
comptime PA_BAD_IO_DEVICE_COMBINATION               = PaError(-9993)
comptime PA_INSUFFICIENT_MEMORY                     = PaError(-9992)
comptime PA_BUFFER_TOO_BIG                          = PaError(-9991)
comptime PA_BUFFER_TOO_SMALL                        = PaError(-9990)
comptime PA_NULL_CALLBACK                           = PaError(-9989)
comptime PA_BAD_STREAM_PTR                          = PaError(-9988)
comptime PA_TIMED_OUT                               = PaError(-9987)
comptime PA_INTERNAL_ERROR                          = PaError(-9986)
comptime PA_DEVICE_UNAVAILABLE                      = PaError(-9985)
comptime PA_INCOMPATIBLE_HOST_API                   = PaError(-9984)
comptime PA_STREAM_IS_STOPPED                       = PaError(-9983)
comptime PA_STREAM_IS_NOT_STOPPED                   = PaError(-9982)
comptime PA_INPUT_OVERFLOWED                        = PaError(-9981)
comptime PA_OUTPUT_UNDERFLOWED                      = PaError(-9980)
comptime PA_HOST_API_NOT_FOUND                      = PaError(-9979)
comptime PA_INVALID_HOST_API                        = PaError(-9978)
comptime PA_CAN_NOT_READ_FROM_A_CALLBACK_STREAM     = PaError(-9977)
comptime PA_CAN_NOT_WRITE_TO_A_CALLBACK_STREAM      = PaError(-9976)
comptime PA_CAN_NOT_READ_FROM_AN_OUTPUT_ONLY_STREAM = PaError(-9975)
comptime PA_CAN_NOT_WRITE_TO_AN_INPUT_ONLY_STREAM   = PaError(-9974)
comptime PA_INCOMPATIBLE_STREAM_HOST_API            = PaError(-9973)
comptime PA_BAD_BUFFER_PTR                          = PaError(-9972)


#-- PaHostApiTypeId

comptime PaHostApiTypeId    = PaInt
comptime PA_IN_DEVELOPMENT  = PaHostApiTypeId(0)
comptime PA_DIRECT_SOUND    = PaHostApiTypeId(1)
comptime PA_MME             = PaHostApiTypeId(2)
comptime PA_ASIO            = PaHostApiTypeId(3)
comptime PA_SOUNDMANAGER    = PaHostApiTypeId(4)
comptime PA_COREAUDIO       = PaHostApiTypeId(5)
comptime PA_OSS             = PaHostApiTypeId(6)
comptime PA_ALSA            = PaHostApiTypeId(7)
comptime PA_ASIO2           = PaHostApiTypeId(8)
comptime PA_MACCOREAUDIO    = PaHostApiTypeId(9)
comptime PA_WDMKS           = PaHostApiTypeId(10)
comptime PA_JACK            = PaHostApiTypeId(11)
comptime PA_WASAPI          = PaHostApiTypeId(12)
comptime PA_AUDIOTRACK      = PaHostApiTypeId(13)
comptime PA_OSS4            = PaHostApiTypeId(14)


#-- PaSampleFormat

comptime PaSampleFormat     = PaULong
comptime PA_FLOAT32         = PaULong(0x00000001)
comptime PA_INT32           = PaULong(0x00000002)
comptime PA_INT24           = PaULong(0x00000004)
comptime PA_INT16           = PaULong(0x00000008)
comptime PA_INT8            = PaULong(0x00000010)
comptime PA_UINT8           = PaULong(0x00000020)
comptime PA_CUSTOM_FORMAT   = PaULong(0x00010000)
comptime PA_NON_INTERLEAVED = PaULong(0x80000000)


#-- PaDeviceIndex

comptime PaDeviceIndex                                 = PaInt
comptime PA_NO_DEVICE                                  = PaDeviceIndex(-1)
comptime PA_USE_HOST_API_SPECIFIC_DEVICE_SPECIFICATION = PaDeviceIndex(-2)


#-- PaStreamFlags

comptime PaStreamFlags                                 = PaULong
comptime PA_NO_FLAG                                    = PaULong(0)
comptime PA_CLIP_OFF                                   = PaULong(0x00000001)
comptime PA_DITHER_OFF                                 = PaULong(0x00000002)
comptime PA_NEVER_DROP_INPUT                           = PaULong(0x00000004)
comptime PA_PRIME_OUTPUT_BUFFERS_USING_STREAM_CALLBACK = PaULong(0x00000008)
comptime PA_PLATFORM_SPECIFIC_FLAGS                    = PaULong(0xFFFF0000)


#-- PaStreamCallbackResult

comptime PaStreamCallbackResult = PaInt
comptime PA_CONTINUE            = PaStreamCallbackResult(0)
comptime PA_COMPLETE            = PaStreamCallbackResult(1)
comptime PA_ABORT               = PaStreamCallbackResult(2)


#-- PaStreamCallbackFlags

comptime PaStreamCallbackFlags = PaULong
comptime PA_INPUT_UNDERFLOW    = PaStreamCallbackFlags(0x00000001)
comptime PA_INPUT_OVERFLOW     = PaStreamCallbackFlags(0x00000002)
comptime PA_OUTPUT_UNDERFLOW   = PaStreamCallbackFlags(0x00000004)
comptime PA_OUTPUT_OVERFLOW    = PaStreamCallbackFlags(0x00000008)
comptime PA_PRIMING_OUTPUT     = PaStreamCallbackFlags(0x00000010)


#-- Misc

comptime PaHostApiIndex                   = PaInt
comptime PA_FORMAT_IS_SUPPORTED           = PaError(0)
comptime PA_FRAMES_PER_BUFFER_UNSPECIFIED = PaULong(0)


#-- PaStreamCallbackTimeInfo

comptime PaTime = PaDouble

@fieldwise_init
struct PaStreamCallbackTimeInfo:
    var current_time:              PaTime
    var input_buffer_adc_time:     PaTime
    var output_buffer_dac_time:    PaTime


#-- PaDeviceInfo

@fieldwise_init
struct PaDeviceInfo:
    var struct_version:                 PaInt
    var name:                           PaString
    var host_api:                       PaHostApiIndex
    var max_input_channels:             PaInt
    var max_output_channels:            PaInt
    var default_low_input_latency:      PaTime
    var default_low_output_latency:     PaTime
    var default_high_input_latency:     PaTime
    var default_high_output_latency:    PaTime
    var default_sample_rate:            PaDouble


#-- PaStreamParameters

@fieldwise_init
struct PaStreamParameters(Movable):
    var device:                           PaDeviceIndex
    var channel_count:                    PaInt
    var sample_format:                    PaSampleFormat
    var suggested_latency:                PaTime
    var host_api_specific_stream_info:    OpaquePointer[MutExternalOrigin]


#-- PaStreamInfo

@fieldwise_init
struct PaStreamInfo:
    var struct_version:    PaInt
    var input_latency:     PaTime
    var output_latency:    PaTime
    var sample_rate:       PaDouble


#-- PaStreamCallback

comptime PaStreamCallback = def(
    input:           OpaquePointer[ImmutExternalOrigin],
    output:          OpaquePointer[MutExternalOrigin],
    frame_count:     PaULong,
    time_info:       UnsafePointer[PaStreamCallbackTimeInfo, ImmutExternalOrigin],
    status_flags:    PaStreamCallbackFlags,
    user_data:       OpaquePointer[MutExternalOrigin],
) thin -> PaStreamCallbackResult


