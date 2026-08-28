# gpu/__init__.mojo

from std.gpu import thread_idx, global_idx
from .device import FaustGpuDevice, create_gpu_runtime, FAUST_GPU_ALLOCATION_ERROR
