#ifndef DSP_HH
#define DSP_HH
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct mydsp {
    int samp_rate = 0;
    FAUSTFLOAT z0 = 1.0;

    auto get_num_inputs(this auto const&) -> int { return 2; }
    auto get_num_outputs(this auto const&) -> int { return 2; }
    auto get_sample_rate(this auto const& dsp) -> int { return dsp.samp_rate; }
    auto init(this auto& dsp, int samp_rate) -> void { dsp.samp_rate = samp_rate; }
    auto compute(
        this auto& dsp, int const count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs
    ) -> void {

        for (int i = 0; i < count; i++) {
            FAUSTFLOAT const in0 = inputs[0][i];
            FAUSTFLOAT const in1 = inputs[1][i];
            FAUSTFLOAT const mixed = FAUSTFLOAT(0.5) * (in0 + in1);

            dsp.z0 = FAUSTFLOAT(0.99) * dsp.z0 + FAUSTFLOAT(0.01) * mixed;

            outputs[0][i] = dsp.z0;
            outputs[1][i] = mixed - dsp.z0;
        }
    }
};

#endif  // DSP_HH
