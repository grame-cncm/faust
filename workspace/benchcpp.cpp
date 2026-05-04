#include "benchcpp.hh"
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

using namespace std;

<<includeIntrinsic>>

<<includeclass>>

int main() {
    auto dsp = new mydsp();
    dsp->init(SAMP_RATE);
    
    s32 n_ins = dsp->getNumInputs();
    s32 n_outs = dsp->getNumOutputs();
    auto [base, err] = bench::make_buffers(n_ins, n_outs);
    if (err) {
        printf("Critical allocation error: %d\n", err);
        exit(err);
    }

    Real** inputs = (Real**)base;
    Real** outputs = inputs + n_ins;

#if FILL_INPUTS
    fill_inputs(inputs, dsp->getNumInputs());
#endif

    bench::warmup(*dsp, inputs, outputs);
    BenchReport report = bench::measure(*dsp, inputs, outputs);
    bench::print_report(report); // the output will be redirected manually

    bench::free_buffers(inputs);
    return 0;
}
