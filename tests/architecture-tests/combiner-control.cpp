// Run: make -f Makefile.combiner-control check -k -j2
#include <iostream>
#include <memory>
#include "faust/dsp/dsp-tools.h"
#include "faust/dsp/dsp-combiner.h"

// A DSP with separate control and sample processing, as produced by -ec.
struct Gain : default_dsp {
    FAUSTFLOAT requested = 1;
    FAUSTFLOAT gain = 1;
    int calls = 0;
    void control() override { gain = requested; ++calls; }
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override
    {
        for (int i = 0; i < count; ++i) outputs[0][i] = inputs[0][i] * gain;
    }
    Gain* clone() override { return new Gain; }
};

int main()
{
    int failures = 0;
    int cases = 0;
    for (int kind = 0; kind < 6; ++kind) {
        auto* a = new Gain;
        auto* b = new Gain;
        std::unique_ptr<dsp> combined;
        switch (kind) {
            case 0: combined.reset(new dsp_sequencer(a, b)); break;
            case 1: combined.reset(new dsp_parallelizer(a, b)); break;
            case 2: combined.reset(new dsp_splitter(a, b)); break;
            case 3: combined.reset(new dsp_merger(a, b)); break;
            case 4: combined.reset(new dsp_recursiver(a, b)); break;
            case 5: combined.reset(new dsp_crossfader(a, b)); break;
        }
        combined->init(48000);
        for (int iteration = 1; iteration <= 3; ++iteration) {
            a->requested = iteration + 1;
            b->requested = iteration + 2;
            combined->control();
            const bool passed = a->gain == a->requested && b->gain == b->requested
                             && a->calls == iteration && b->calls == iteration;
            ++cases;
            failures += !passed;
        }
    }
    // Nested composition must forward transitively and expose updated audio.
    auto* a = new Gain;
    auto* b = new Gain;
    auto* c = new Gain;
    std::unique_ptr<dsp> combined(new dsp_sequencer(new dsp_sequencer(a, b), c));
    combined->init(48000);
    a->requested = 2;
    b->requested = 3;
    c->requested = 4;
    combined->control();
    FAUSTFLOAT input[] = {1, -1, 0, 2};
    FAUSTFLOAT output[4] = {};
    FAUSTFLOAT* inputs[] = {input};
    FAUSTFLOAT* outputs[] = {output};
    combined->compute(4, inputs, outputs);
    for (int i = 0; i < 4; ++i) {
        ++cases;
        failures += output[i] != input[i] * 24;
    }
    std::cout << "audio:";
    for (auto value : output) std::cout << ' ' << value;
    std::cout << '\n' << cases << " cases, " << failures << " failures\n";
    return failures ? 1 : 0;
}
