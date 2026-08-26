# gpu_probe.mojo

from conf import *

from max.gpu.host import DeviceContext, DeviceBuffer
from std.gpu import thread_idx
from std.sys import has_accelerator

comptime NUM_SAMPLES = 8

# GPU kernel

def apply_gain(samples: Pointer[F32, MUT_ANY], gain: F32) -> None:
    var i = thread_idx.x
    samples[unsafe_offset=i] *= gain

def main() raises -> None:
    comptime assert has_accelerator()

    var ctx = DeviceContext()
    print("GPU:", ctx.name())

    # Host buffer
    var host_buf = ctx.enqueue_create_host_buffer[f32](NUM_SAMPLES)

    ctx.synchronize()  # creation must finish before the CPU can write host_buf

    for i in range(NUM_SAMPLES):
        host_buf[i] = F32(i - 4)

    print("Input: ", host_buf)

    # GPU buffer and CPU -> GPU copy
    var gpu_buf: DeviceBuffer[f32] = ctx.enqueue_create_buffer[f32](NUM_SAMPLES)
    ctx.enqueue_copy(src_buf=host_buf, dst_buf=gpu_buf)

    # GPU processing
    var gain = F32(0.5)
    ctx.enqueue_function[apply_gain](gpu_buf, gain, grid_dim=1, block_dim=NUM_SAMPLES)

    # GPU -> CPU copy
    ctx.enqueue_copy(src_buf=gpu_buf, dst_buf=host_buf)
    ctx.synchronize()

    print("Output:", host_buf)

    # Verification
    for i in range(NUM_SAMPLES):
        var expected = F32(i - 4) * gain
        if host_buf[i] != expected:
            raise Error("GPU gain verification failed")

    print("pass")
