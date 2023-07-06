// TODO: add licence

#include <iostream>
#include <cmath>
#include "autodiff.h"
#include "faust/gui/MapUI.h"
#include "faust/audio/dummy-audio.h"
#include "faust/dsp/one-sample-dsp.h"
#include "faust/dsp/llvm-dsp.h"

<<includeIntrinsic>>
<<includeclass>>

int main(int argc, char *argv[]) {
    mydsp differentiableDSP;

    autodiff autodiff;
    auto autodiffDSP{autodiff.init(&differentiableDSP)};

    std::cout << "DSP size: " << sizeof(*autodiffDSP) << " bytes\n";
    std::cout << "Inputs: " << autodiffDSP->getNumInputs() << " Outputs: " << autodiffDSP->getNumOutputs() << "\n";

    auto ui{new MapUI};
    autodiffDSP->buildUserInterface(ui);

    // Allocate the audio driver
    dummyaudio audio(48000, 1);
    audio.init("Test", static_cast<dsp *>(autodiffDSP));

//    auto autodiffedParamAddress{ui->getParamAddress(0)};
    auto numParams{ui->getParamsCount()};
    std::cout << "Num params: " << numParams << "\n";
    auto paramAddress{numParams > 0 ? ui->getParamAddress(0) : std::string{""}};
    auto paramValue{ui->getParamValue(paramAddress)};
//    std::cout << autodiffedParamAddress << " value: " << gain << "\n";
    std::cout << "Param " << paramAddress << ", value: " << paramValue << "\n";

    // Sensitivity
    auto epsilon{1e-7f};
    // Learning rate/stepsize
    auto alpha{.1f};
    auto loss{0.f}, gradient{0.f};
    auto numIter{1000};

    for (auto i{0}; i < numIter; ++i) {
        audio.render();
        auto out{audio.getOutput()};

        for (int frame = 0; frame < audio.getBufferSize(); frame++) {
            auto groundTruth{out[0][frame]},
                    current{out[1][frame]},
                    differentiated{out[2][frame]};

            std::cout << std::fixed << std::setprecision(10) << i <<
                      "\tTruth: " << groundTruth <<
                      "\tGuess: " << current;

            // Calculate loss
            loss = powf(current - groundTruth, 2);

            std::cout << "\tLoss: " << loss;

            if (loss > epsilon) {
                // Update gradient
                gradient = 2 * differentiated * (current - groundTruth);
                std::cout << "\t Grad: " << gradient;

                // Update parameter value.
                paramValue -= alpha * gradient;
                std::cout << "\tSetting param: " << paramValue;
                ui->setParamValue(paramAddress, paramValue);
            }

            std::cout << "\n";
        }
    }
}

dsp *autodiff::init(dsp *differentiatedDSP) {
    auto noiseGenerator{createDSPInstanceFromString(
            "Noise Generator",
            "import(\"stdfaust.lib\");"
            "process = no.noise;"
//            "process = 1;"
    )};

    auto fixedDSP{createDSPInstanceFromString(
            "Fixed Gain",
            "import(\"stdfaust.lib\");"
            "process = _*.75;"
    )};

    // TODO: replace this with something derived from the input .dsp file.
    auto adjustableDSP{createDSPInstanceFromString(
            "Adjustable Gain",
            "import(\"stdfaust.lib\");"
            "gain = hslider(\"gain\", .5, 0, 1, .001);"
            "process = _*gain;"
    )};

//    parallelizer = new dsp_parallelizer(
//            // Set up the ground truth DSP: s_o(\hat{p})
//            new dsp_sequencer(noiseGenerator, fixedDSP),
//            // Set up a pair of DSPs...
//            new dsp_parallelizer(
//                    // The adjustable version: s_o(p),
//                    new dsp_sequencer(noiseGenerator, adjustableDSP),
//                    // and the autodiffed version: \nabla s_o(p),
//                    new dsp_sequencer(noiseGenerator, differentiatedDSP)
//            )
//    );

    parallelizer = new dsp_parallelizer(
            // Set up the ground truth DSP: s_o(\hat{p})
            new dsp_sequencer(noiseGenerator->clone(), fixedDSP),
            // Set up a pair of DSPs...
            new dsp_parallelizer(
                    // The adjustable version: s_o(p),
                    new dsp_sequencer(noiseGenerator->clone(), adjustableDSP),
                    // and the autodiffed version: \nabla s_o(p),
                    new dsp_sequencer(noiseGenerator->clone(), differentiatedDSP)
            )
    );

    return parallelizer;
}

dsp *autodiff::createDSPInstanceFromString(
        const std::string &appName,
        const std::string &dspContent
) {
    std::string errorMessage;
    auto factory{createDSPFactoryFromString(appName, dspContent, 0, nullptr, "", errorMessage)};
    if (!factory) {
        std::cout << errorMessage;
    }
    assert(factory);
    return factory->createDSPInstance();
}
