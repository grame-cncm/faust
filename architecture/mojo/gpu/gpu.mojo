# A host runtime that processes audio blocks on the GPU.
# @desc
# - Prepares resources for an initialized DSP.
# - Processes a block and publishes the first error.
# - Releases resources after the audio driver stops.
# @note
# - The callback calls `process`; `get_error` follows `stop`.
from conf import *
from dsp import FaustDspGpu
from gui.map import GpuControlMap

trait FaustGpu:
    def prepare[Dsp: FaustDspGpu](
        mut gpu, var dsp: Ptr[Dsp], imm map: GpuControlMap, imm block_size: S32
    ) -> S32:
        ...

    def process(
        mut gpu, imm count: S32, var ins: ImmStreams, var outs: MutStreams
    ) -> None:
        ...

    def get_error(imm gpu) -> S32:
        ...

    def release(mut gpu) -> S32:
        ...
