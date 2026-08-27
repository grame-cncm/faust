# gpu_osc_portaudio.mojo

from conf import *
from std.gpu import thread_idx
from std.sys import has_accelerator
from max.gpu.host import DeviceBuffer, DeviceContext
from audio.portaudio.ffi import *

comptime NUM_OSCS = 4
comptime BUFF_SIZE = S32(256)
comptime SAMP_RATE = S32(48000)
comptime PLAY_MS = S32(5000)

comptime TWO_PI = F32(6.283185307179586)
comptime AMP = F32(0.15)

# Oscillator state

@fieldwise_init
struct GpuOscState:
    var ctx:       DeviceContext
    var osc_buf:   DeviceBuffer[f32]
    var out_buf:   DeviceBuffer[f32]
    var phase_buf: DeviceBuffer[f32]

# Main entry point

def main() raises -> None:
    comptime assert has_accelerator()

    # GPU state.
    var ctx = DeviceContext()
    print("GPU:", ctx.name())

    var osc_buf = ctx.enqueue_create_buffer[f32](NUM_OSCS * Int(BUFF_SIZE))
    var out_buf = ctx.enqueue_create_buffer[f32](Int(BUFF_SIZE))
    var phase_buf = ctx.enqueue_create_buffer[f32](NUM_OSCS)

    ctx.enqueue_memset(phase_buf, F32(0))
    ctx.synchronize()

    var state = unsafe_alloc[GpuOscState](1)
    state.unsafe_write(GpuOscState(ctx, osc_buf, out_buf, phase_buf))

    # PortAudio output.
    var err = pa_initialize()
    if err:
        raise Error("PortAudio initialization failed")

    var stream: PaStream = None

    err = pa_open_default_stream(
        Ptr(to=stream).unsafe_origin_cast[MUT_NOTRK](),
        0, 1,
        PA_FLOAT32, SAMP_RATE, BUFF_SIZE,
        gpu_callback,
        state.unsafe_bitcast[Void]()
    )

    if err:
        _ = pa_terminate()
        raise Error("PortAudio stream creation failed")

    err = pa_start_stream(stream)
    if err:
        _ = pa_close_stream(stream)
        _ = pa_terminate()
        raise Error("PortAudio stream start failed")

    print("Playing 4 GPU oscillators...")
    pa_sleep(PLAY_MS)

    _ = pa_stop_stream(stream)
    _ = pa_close_stream(stream)
    _ = pa_terminate()

    state.unsafe_deinit_pointee()
    state.unsafe_free()

# GPU oscillator kernel

def osc_kernel(
    osc_buf: Pointer[F32, MUT_ANY], phase_buf: Pointer[F32, MUT_ANY]
) -> None:
    var osc = thread_idx.x
    var phase = phase_buf[unsafe_offset=osc]
    var freq = F32(220 + 110 * osc)
    var step = TWO_PI * freq / F32(SAMP_RATE)
    var offset = osc * Int(BUFF_SIZE)

    for i in range(Int(BUFF_SIZE)):
        osc_buf[unsafe_offset=offset + i] = AMP * sin(phase)
        phase += step

        if phase >= TWO_PI:
            phase -= TWO_PI

    phase_buf[unsafe_offset=osc] = phase

# GPU mix kernel

def mix_kernel(
    osc_buf: Pointer[F32, MUT_ANY], out_buf: Pointer[F32, MUT_ANY]
) -> None:
    var i = thread_idx.x
    var sample = F32(0)

    for osc in range(NUM_OSCS):
        sample += osc_buf[unsafe_offset=osc * Int(BUFF_SIZE) + i]

    out_buf[unsafe_offset=i] = sample

# PortAudio callback

def gpu_callback(
    input:  OptPtr[Void, IMM_NOTRK],
    output: OptPtr[Void, MUT_NOTRK],
    count:  PaULong,
    time:   OptPtr[PaStreamCallbackTimeInfo, IMM_NOTRK],
    flags:  PaStreamCallbackFlags,
    data:   OptPtr[Void, MUT_NOTRK]
) -> S32:
    if output == None or data == None:
        return PA_ABORT

    if count != PaULong(UInt64(BUFF_SIZE)):
        return PA_ABORT

    var out_buf = output.unsafe_value().unsafe_bitcast[F32]()
    var state = data.unsafe_value().unsafe_bitcast[GpuOscState]()

    try:
        # Generate 4 oscillators in parallel.
        state[].ctx.enqueue_function[osc_kernel](
            state[].osc_buf, state[].phase_buf, grid_dim=1, block_dim=NUM_OSCS
        )

        # Mix the oscillators to mono.
        state[].ctx.enqueue_function[mix_kernel](
            state[].osc_buf, state[].out_buf, grid_dim=1, block_dim=Int(BUFF_SIZE)
        )

        # GPU -> PortAudio output.
        state[].ctx.enqueue_copy(dst_ptr=out_buf, src_buf=state[].out_buf)

        state[].ctx.synchronize()

    except e:
        return PA_ABORT

    return PA_CONTINUE
