# dsp/gpu.mojo

from conf import *
from meta import FaustMeta
from gui import FaustGui
from .dsp import FaustDsp

@fieldwise_init
struct FaustGpuDsp[Dsp: FaustDsp](FaustDsp, TrivialRegisterPassable):

    var dsp: Ptr[Self.Dsp]

    @always_inline
    def get_num_inputs(imm gpu) -> S32:
        return gpu.dsp[].get_num_inputs()

    @always_inline
    def get_num_outputs(imm gpu) -> S32:
        return gpu.dsp[].get_num_outputs()

    @always_inline
    def get_sample_rate(imm gpu) -> S32:
        return gpu.dsp[].get_sample_rate()

    @always_inline
    def class_init(mut gpu, imm sample_rate: S32) -> None:
        gpu.dsp[].class_init(sample_rate)
        
    @always_inline
    def instance_constants(mut gpu, imm sample_rate: S32) -> None:
        gpu.dsp[].instance_constants(sample_rate)

    @always_inline
    def instance_reset_user_interface(mut gpu) -> None:
        gpu.dsp[].instance_reset_user_interface()

    @always_inline
    def instance_clear(mut gpu) -> None:
        gpu.dsp[].instance_clear()

    @always_inline
    def instance_init(mut gpu, imm sample_rate: S32) -> None:
        gpu.dsp[].instance_init(sample_rate)

    @always_inline
    def init(mut gpu, imm sample_rate: S32) -> None:
        gpu.dsp[].init(sample_rate)

    @always_inline
    def get_json(imm gpu) -> String:
        return gpu.dsp[].get_json()

    @always_inline
    def metadata(imm gpu, mut meta: Some[FaustMeta]) -> None:
        gpu.dsp[].metadata(meta)

    @always_inline
    def build_user_interface(mut gpu, mut ui: Some[FaustGui]) -> None:
        gpu.dsp[].build_user_interface(ui)

    @always_inline
    def compute(
        mut gpu,
        var count:    S32,
        var inputs:   ImmStreams,
        var outputs:  MutStreams
    )  -> None:
        gpu.dsp[].compute(count, inputs, outputs)
