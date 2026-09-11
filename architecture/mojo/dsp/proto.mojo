# dsp/probe.mojo

from conf import *
from meta import FaustMeta
from gui import FaustGui
from .gpu import FaustDspGpu

# Used to snooze Mojo LSP/compiler messages while prototyping architectures.

struct ProtoDsp(FaustDspGpu):
    @always_inline
    def __init__(out dsp):
        pass
    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 0
    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 1
    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return 48_000
    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass
    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        pass
    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        pass
    @always_inline
    def instance_clear(mut dsp) -> None:
        pass
    @always_inline
    def instance_init(mut dsp, imm sample_rate: S32) -> None:
        pass
    @always_inline
    def init(mut dsp, imm sample_rate: S32) -> None:
        pass
    @always_inline
    def get_json(imm dsp) -> String:
        return ""
    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        pass
    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        pass
    @staticmethod
    @always_inline
    def gpu_work_size(imm count: S32) -> Int:
        pass

    @staticmethod
    @always_inline
    def gpu_compute(
        mut ctx:       DeviceContext,
        imm dsp_raw:   DeviceBuffer[u8],
        imm in_buf:    DeviceBuffer[dfaust],
        imm out_buf:   DeviceBuffer[dfaust],
        imm work_buf:  DeviceBuffer[u8],
        imm count:     S32
    ) raises -> None: ...
