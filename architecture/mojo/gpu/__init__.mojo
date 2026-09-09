# gpu/__init__.mojo

from max.gpu import global_idx, thread_idx

from .device import (
    FaustGpuDevice,
    gpu_create_runtime,
    FAUST_GPU_NO_ERROR,
    FAUST_GPU_ERROR,
    FAUST_GPU_ALLOCATION_ERROR,
    FAUST_GPU_INVALID_ARGUMENT
)
