#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "faust/dsp/dsp-adapter.h"

// A bus with a control value and observable DSP lifecycle calls.
struct TestDSP : dsp_bus {
    FAUSTFLOAT gain   = 1;
    int        clears = 0;
    TestDSP() : dsp_bus(2) {}
    void instanceClear() override { ++clears; }
    void instanceResetUserInterface() override { gain = 1; }
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override
    {
        for (int ch = 0; ch < 2; ++ch) {
            for (int i = 0; i < count; ++i) {
                outputs[ch][i] = gain * inputs[ch][i];
            }
        }
    }
};

int main()
{
    int cases = 0, failures = 0;
    for (int down : {0, 1}) {
        for (int factor : {2, 3, 4, 8, 16, 32}) {
            for (int filter = 0; filter <= 4; ++filter) {
                for (int reset = 0; reset < 3; ++reset) {
                    for (int count : {factor, 96}) {
                        std::string          error;
                        TestDSP*             inner = new TestDSP;
                        std::unique_ptr<dsp> adapter(createSRAdapter<FAUSTFLOAT>(
                            inner, error, down ? factor : 0, down ? 0 : factor, filter));
                        adapter->init(48000);
                        for (int round = 0; round < 3; ++round) {
                            inner->gain = 2;
                            FAUSTFLOAT input0[96], input1[96], output0[96], output1[96];
                            std::fill(input0, input0 + 96, FAUSTFLOAT(1));
                            std::fill(input1, input1 + 96, FAUSTFLOAT(-1));
                            FAUSTFLOAT* inputs[]  = {input0, input1};
                            FAUSTFLOAT* outputs[] = {output0, output1};
                            adapter->compute(count, inputs, outputs);
                            int clears = inner->clears;
                            if (reset == 0) {
                                adapter->instanceClear();
                            }
                            if (reset == 1) {
                                adapter->instanceInit(48000);
                            }
                            if (reset == 2) {
                                adapter->init(48000);
                            }
                            bool ok = inner->clears == clears + 1;
                            ok &= inner->gain == (reset == 0 ? 2 : 1);
                            ok &=
                                inner->getSampleRate() == (down ? 48000 / factor : 48000 * factor);
                            bool lifecycle = ok;
                            std::fill(input0, input0 + 96, FAUSTFLOAT(0));
                            std::fill(input1, input1 + 96, FAUSTFLOAT(0));
                            adapter->compute(count, inputs, outputs);
                            // Zero-state linear filters and a bus must produce exact silence.
                            for (int ch = 0; ch < 2; ++ch) {
                                for (int i = 0; i < count; ++i) {
                                    ok &= outputs[ch][i] == 0;
                                }
                            }
                            ++cases;
                            if (!ok) {
                                ++failures;
                                std::cerr << "FAIL down=" << down << " filter=" << filter
                                          << " factor=" << factor << " round=" << round
                                          << " lifecycle=" << lifecycle << " reset=" << reset
                                          << " count=" << count << " first=" << output0[0] << '\n';
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << cases << " cases, " << failures << " failures\n";
    return failures ? 1 : 0;
}
