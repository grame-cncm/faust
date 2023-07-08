// TODO: add licence

#include <iostream>
#include <cmath>
#include "autodiff.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"

int main(int argc, char *argv[]) {
    if (!isopt(argv, "--input") || !isopt(argv, "--gt") || !isopt(argv, "--diff")) {
        std::cout << "Please provide input, ground truth, and differentiable Faust files.\n";
        std::cout << argv[0] << " --input <file> --gt <file> --diff <file>\n";
        exit(1);
    }
    auto input{lopts(argv, "--input", "")};
    auto gt{lopts(argv, "--gt", "")};
    auto diff{lopts(argv, "--diff", "")};

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
        kAlpha(learningRate),
        kEpsilon(sensitivity),
        kNumIterations(numIterations),
        fInputDSPPath(inputDSPPath),
        fGroundTruthDSPPath(groundTruthDSPPath),
        fDifferentiableDSPPath(differentiableDSPPath) {}

mldsp::~mldsp() {}

void mldsp::initialise() {
    auto inputDSP{createDSPInstanceFromPath(fInputDSPPath)};
    auto fixedDSP{createDSPInstanceFromPath(fGroundTruthDSPPath)};
    auto adjustableDSP{createDSPInstanceFromPath(fDifferentiableDSPPath)};
    const char *argv[] = {"-diff"};
    auto differentiatedDSP{createDSPInstanceFromPath(fDifferentiableDSPPath, 1, argv)};

    fDSP = std::make_unique<dsp_parallelizer>(
            // Set up the ground truth DSP: s_o(\hat{p})
            new dsp_sequencer(inputDSP->clone(), fixedDSP),
            new dsp_parallelizer(
                    // The adjustable DSP: s_o(p),
                    new dsp_sequencer(inputDSP->clone(), adjustableDSP),
                    // The autodiffed DSP: \nabla s_o(p),
                    new dsp_sequencer(inputDSP->clone(), differentiatedDSP)
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
    for (auto i{1}; i <= kNumIterations; ++i) {
        fAudio->render();
        auto out{fAudio->getOutput()};

        for (int frame = 0; frame < fAudio->getBufferSize(); frame++) {
            computeLoss(out, frame);

            if (fLoss > kEpsilon) {
                computeGradient(out, frame);

                // Update parameter value.
                fLearnableParamValue -= kAlpha * fGradient;
                fUI->setParamValue(fLearnableParamAddress, fLearnableParamValue);
            }

            reportState(i, out, frame);
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
    fLoss = powf(output[Channels::LEARNABLE][frame] - output[Channels::GROUND_TRUTH][frame], 2);
}

void mldsp::computeGradient(FAUSTFLOAT **output, int frame) {
    fGradient = 2 * output[Channels::DIFFERENTIATED][frame] *
                (output[Channels::LEARNABLE][frame] - output[Channels::GROUND_TRUTH][frame]);
}

void mldsp::reportState(int iteration, FAUSTFLOAT **output, int frame) {
    std::cout << std::fixed << std::setprecision(10) <<
              std::setw(5) << iteration <<
              std::setw(LABEL_WIDTH) << "Sig GT: " <<
              std::setw(NUMBER_WIDTH) << output[Channels::GROUND_TRUTH][frame] <<
              std::setw(LABEL_WIDTH) << "Sig Learn: " <<
              std::setw(NUMBER_WIDTH) << output[Channels::LEARNABLE][frame] <<
              std::setw(LABEL_WIDTH) << "Loss: " <<
              std::setw(NUMBER_WIDTH) << fLoss;

    if (fLoss > kEpsilon) {
        std::cout << std::setw(LABEL_WIDTH) << "Grad: " <<
                  std::setw(NUMBER_WIDTH) << fGradient <<
                  std::setw(LABEL_WIDTH) << "Set param: " <<
                  std::setw(NUMBER_WIDTH) << fLearnableParamValue;
    }

    std::cout << "\n";
}
/***************************** END autodiff.cpp *******************************/
