# gpu/__init__.mojo

from max.gpu import thread_idx, global_idx
from .device import FaustGpuDevice, gpu_create_runtime, FAUST_GPU_ALLOCATION_ERROR
