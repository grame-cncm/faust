# gpu/__init__.mojo

from max.gpu import global_idx, thread_idx
from std.sys import has_accelerator

from .device import (
    GpuDevice,
    FAUST_GPU_NO_ERROR,
    FAUST_GPU_ERROR,
    FAUST_GPU_ALLOCATION_ERROR,
    FAUST_GPU_INVALID_ARGUMENT
)
