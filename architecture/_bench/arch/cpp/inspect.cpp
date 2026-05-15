// architecture/inspect.cpp

#include "common.h"

<<includeIntrinsic>>
<<includeclass>>

no_inline void inspect_compute(mydsp& dsp, Real** inputs, Real** outputs);

int main() {
    mydsp* dsp = new mydsp();
    dsp->init(SAMP_RATE);
    
    s32 n_ins = dsp->getNumInputs();
    s32 n_outs = dsp->getNumOutputs();
    auto [base, err] = make_buffers(n_ins, n_outs);
    if (err) {
        printf("Critical allocation error: %d\n", err);
        exit(err);
    }

    Real** inputs = (Real**)base;
    Real** outputs = inputs + n_ins;
    
    inspect_compute(*dsp, inputs, outputs);
    free_buffers(base);
    delete dsp;
    return 0;
}

no_inline void inspect_compute(mydsp& dsp, Real** inputs, Real** outputs)
{
    for (int i = 0; i < COMPUTE_ITERS; i++) {
        _do_not_optimize(inputs);
        _do_not_optimize(outputs);
        dsp.compute(BUFF_SIZE, inputs, outputs);
        _clobber_memory();
    }
}
