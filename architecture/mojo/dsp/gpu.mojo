# gpu/dsp.mojo

from conf import *
from .dsp import FaustDsp


trait FaustDspGpu(FaustDsp):
    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> None:
        pass

    @staticmethod
    @always_inline
    def gpu_work_size(imm count: S32) -> Int:
        ...

    @staticmethod
    @always_inline
    def gpu_compute(
        mut ctx: DeviceContext,
        imm dsp_raw: DeviceBuffer[u8],
        imm in_buf: DeviceBuffer[dfaust],
        imm out_buf: DeviceBuffer[dfaust],
        imm work_buf: DeviceBuffer[u8],
        imm count: S32
    ) raises -> None:
        ...
