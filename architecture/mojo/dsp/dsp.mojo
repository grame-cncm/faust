#-- dsp/dsp.mojo


from conf.prelude import *


trait FaustDsp:

    @always_inline
    def get_num_inputs(dsp) -> S32: ...

    @always_inline
    def get_num_outputs(dsp) -> S32: ...

    @always_inline
    def get_sample_rate(dsp) -> S32: ...

    @always_inline
    def init(mut dsp, sample_rate: S32) -> None: ...

    @always_inline
    def compute[dtype: DType where is_real[dtype]](
        mut dsp,
        var count:      S32,
        var inputs:     ReadStreams[dtype],
        var outputs:    MutaStreams[dtype]
    ) -> None: ...
