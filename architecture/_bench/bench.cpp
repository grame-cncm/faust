#include "../faust/_bench/bench.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

<<includeIntrinsic>>
<<includeclass>>

int main() {
    auto dsp = new mydsp();
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

#if FILL_INPUTS
    fill_inputs(inputs, dsp->getNumInputs());
#endif

    warmup(*dsp, inputs, outputs);
    FaustReport report = measure(*dsp, inputs, outputs);
    report.checksum = checksum_outputs(outputs, n_outs);
    print_report(report); // the output will be redirected via script
    write_csv(report);

    free_buffers(inputs);
    return 0;
}
