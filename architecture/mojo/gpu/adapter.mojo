# gpu/adapter.mojo

from conf import *
from dsp import FaustDsp, FaustDspGpu
from gui import FaustGui
from meta import FaustMeta
from .gpu import FaustGpu


# A `FaustDsp` that adapts GPU processing to the regular audio path.
# @desc
# - Delegates metadata, initialization, and UI building to the DSP.
# - Delegates each audio block to the GPU runtime.
# @rep
# - dsp: generated instance kept alive by the frontend.
# - gpu: prepared GPU runtime kept alive by the frontend.
# @note
# - `compute` cannot return errors; the device records them.
@fieldwise_init
struct GpuAdapter[Dsp: FaustDspGpu, Gpu: FaustGpu](FaustDsp):
    var dsp:  Ptr[Self.Dsp]
    var gpu:  Ptr[Self.Gpu]

    @always_inline
    def get_num_inputs(imm adapter) -> S32:
        return adapter.dsp[].get_num_inputs()

    @always_inline
    def get_num_outputs(imm adapter) -> S32:
        return adapter.dsp[].get_num_outputs()

    @always_inline
    def get_sample_rate(imm adapter) -> S32:
        return adapter.dsp[].get_sample_rate()

    @always_inline
    def class_init(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].class_init(sample_rate)

    @always_inline
    def instance_constants(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].instance_constants(sample_rate)

    @always_inline
    def instance_reset_user_interface(mut adapter) -> None:
        adapter.dsp[].instance_reset_user_interface()

    @always_inline
    def instance_clear(mut adapter) -> None:
        adapter.dsp[].instance_clear()

    @always_inline
    def instance_init(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].instance_init(sample_rate)

    @always_inline
    def init(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].init(sample_rate)

    @always_inline
    def get_json(imm adapter) -> String:
        return adapter.dsp[].get_json()

    @always_inline
    def metadata(imm adapter, mut meta: Some[FaustMeta]) -> None:
        adapter.dsp[].metadata(meta)

    @always_inline
    def build_user_interface(mut adapter, mut ui: Some[FaustGui]) -> None:
        adapter.dsp[].build_user_interface(ui)

    @always_inline
    def compute(
        mut adapter, var count: S32, var ins: ImmStreams, var outs: MutStreams
    ) -> None:
        adapter.gpu[].process(count, ins, outs)
