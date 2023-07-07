// TODO: add licence

#include <iostream>
#include <cmath>
#include "autodiff.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"

int main(int argc, char *argv[]) {
    // TODO: usage
    auto input{lopts(argv, "--input", "$(faust --archdir)/examples/autodiff/noise.dsp")};
    auto gt{lopts(argv, "--gt", "$(faust --archdir)/examples/autodiff/fixed_gain.dsp")};
    auto diff{lopts(argv, "--diff", "$(faust --archdir)/examples/autodiff/gain.dsp")};

    mldsp mldsp{input, gt, diff};
    mldsp.initialise();
    mldsp.doGradientDescent();
}

mldsp::mldsp(std::string inputDSPPath,
             std::string groundTruthDSPPath,
             std::string differentiableDSPPath,
             FAUSTFLOAT learningRate,
             FAUSTFLOAT sensitivity,
             int numIterations) :
        fAlpha(learningRate),
        fEpsilon(sensitivity),
        fNumIterations(numIterations),
        fInputDSPPath(inputDSPPath),
        fGroundTruthDSPPath(groundTruthDSPPath),
        fDifferentiableDSPPath(differentiableDSPPath) {}

mldsp::~mldsp() {}

void mldsp::initialise() {
    auto input{createDSPInstanceFromPath(fInputDSPPath)};
    auto fixedDSP{createDSPInstanceFromPath(fGroundTruthDSPPath)};
    auto adjustableDSP{createDSPInstanceFromPath(fDifferentiableDSPPath)};
    const char *argv[] = {"-diff"};
    auto differentiatedDSP{createDSPInstanceFromPath(fDifferentiableDSPPath, 1, argv)};

    fDSP = std::make_unique<dsp_parallelizer>(
            // Set up the ground truth DSP: s_o(\hat{p})
            new dsp_sequencer(input->clone(), fixedDSP),
            new dsp_parallelizer(
                    // The adjustable DSP: s_o(p),
                    new dsp_sequencer(input->clone(), adjustableDSP),
                    // The autodiffed DSP: \nabla s_o(p),
                    new dsp_sequencer(input->clone(), differentiatedDSP)
            )
    );

    fUI = std::make_unique<MapUI>();
    fDSP->buildUserInterface(fUI.get());

    // Allocate the audio driver
    fAudio = std::make_unique<dummyaudio>(48000, 1);
    fAudio->init("Dummy audio", fDSP.get());

    // TODO: check that the learnable parameter exists.
    fLearnableParamAddress = fUI->getParamAddress(0);
    fLearnableParamValue = fUI->getParamValue(fLearnableParamAddress);
    std::cout << "Learnable parameter: " << fLearnableParamAddress << ", value: " << fLearnableParamValue << "\n";
}

void mldsp::doGradientDescent() {
    for (auto i{1}; i <= fNumIterations; ++i) {
        fAudio->render();
        auto out{fAudio->getOutput()};

        for (int frame = 0; frame < fAudio->getBufferSize(); frame++) {
            computeLoss(out, frame);

            if (fLoss > fEpsilon) {
                computeGradient(out, frame);

                // Update parameter value.
                fLearnableParamValue -= fAlpha * fGradient;
                fUI->setParamValue(fLearnableParamAddress, fLearnableParamValue);
            }

            printState(i, out, frame);
        }

    }
}

dsp *mldsp::createDSPInstanceFromString(
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

dsp *mldsp::createDSPInstanceFromPath(const std::string &path,
                                      int argc, const char *argv[]) {
    std::string errorMessage;
    auto factory{createDSPFactoryFromFile(path, argc, argv, "", errorMessage)};
    if (!factory) {
        std::cout << errorMessage;
    }
    assert(factory);
    return factory->createDSPInstance();
}

void mldsp::computeLoss(FAUSTFLOAT **output, int frame) {
    fLoss = powf(output[LEARNABLE_CHANNEL][frame] - output[TRUTH_CHANNEL][frame], 2);
}

void mldsp::computeGradient(FAUSTFLOAT **output, int frame) {
    fGradient = 2 * output[DIFFERENTIATED_CHANNEL][frame] *
                (output[LEARNABLE_CHANNEL][frame] - output[TRUTH_CHANNEL][frame]);
}

void mldsp::printState(int iteration, FAUSTFLOAT **output, int frame) {
    std::cout << std::fixed << std::setprecision(10) <<
              std::setw(5) << iteration <<
              std::setw(LABEL_WIDTH) << "Truth: " <<
              std::setw(NUMBER_WIDTH) << output[TRUTH_CHANNEL][frame] <<
              std::setw(LABEL_WIDTH) << "Learnt: " <<
              std::setw(NUMBER_WIDTH) << output[LEARNABLE_CHANNEL][frame] <<
              std::setw(LABEL_WIDTH) << "Loss: " <<
              std::setw(NUMBER_WIDTH) << fLoss;

    if (fLoss > fEpsilon) {
        std::cout << std::setw(LABEL_WIDTH) << "Grad: " <<
                  std::setw(NUMBER_WIDTH) << fGradient <<
                  std::setw(LABEL_WIDTH) << "Set param: " <<
                  std::setw(NUMBER_WIDTH) << fLearnableParamValue;
    }

    std::cout << "\n";
}
/***************************** END autodiff.cpp *******************************/
