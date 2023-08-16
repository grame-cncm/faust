#include <iostream>
#include <cmath>
#include "autodiff.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"

int main(int argc, char *argv[])
{
    if (isopt(argv, "--help")) {
        std::cout << "Usage: " << argv[0] << " --input <file> --gt <file> --diff <file>"
                  << " [-lf|--lossfunction <loss-function>]"
                  << " [-lr|--learningrate <learning-rate>]\n";
        exit(0);
    }
    
    if (!isopt(argv, "--input") || !isopt(argv, "--gt") || !isopt(argv, "--diff")) {
        std::cout << "Please provide input, ground truth, and differentiable Faust files.\n";
        std::cout << argv[0] << " --input <file> --gt <file> --diff <file>\n";
        exit(1);
    }
    
    auto input{lopts(argv, "--input", "")};
    auto gt{lopts(argv, "--gt", "")};
    auto diff{lopts(argv, "--diff", "")};
    
    mldsp::LossFunction lf{mldsp::L2_NORM};
    auto lossFunction{lopts1(argc, argv, "--lossfunction", "-lf", "")};
    if (strcmp(lossFunction, "l1") == 0) {
        lf = mldsp::L1_NORM;
    } else if (strcmp(lossFunction, "l2") == 0) {
        lf = mldsp::L2_NORM;
    }
    
    auto learningRate{strtof(
            lopts1(argc, argv, "--learningrate", "-lr", "0.1"),
            nullptr
    )};
    
    mldsp mldsp{input, gt, diff, lf, learningRate};
    mldsp.initialise();
    mldsp.doGradientDescent();
}

mldsp::mldsp(std::string inputDSPPath,
             std::string groundTruthDSPPath,
             std::string differentiableDSPPath,
             LossFunction lossFunction,
             FAUSTFLOAT learningRate,
             FAUSTFLOAT sensitivity,
             int numIterations) :
        kLossFunction(lossFunction),
        kAlpha(learningRate),
        kEpsilon(sensitivity),
        kNumIterations(numIterations),
        fInputDSPPath(inputDSPPath),
        fGroundTruthDSPPath(groundTruthDSPPath),
        fDifferentiableDSPPath(differentiableDSPPath)
{
    std::cout << "Learning rate: " << kAlpha
              << "\nSensitivity: " << kEpsilon << "\n\n";
}

mldsp::~mldsp()
{
    fFile.close();
    delete fDSP;
}

void mldsp::initialise()
{
    auto inputDSP{createDSPInstanceFromPath(fInputDSPPath)};
    auto fixedDSP{createDSPInstanceFromPath(fGroundTruthDSPPath)};
    auto adjustableDSP{createDSPInstanceFromPath(fDifferentiableDSPPath)};
    const char *argv[] = {"-diff"};
    auto differentiatedDSP{createDSPInstanceFromPath(fDifferentiableDSPPath, 1, argv)};
//    auto differentiatedDSP{createDSPInstanceFromPath("/usr/local/share/faust/examples/autodiff/recursion/target.dsp", 1, argv)};
    
    fDSP = new dsp_parallelizer(
            // Set up the ground truth DSP: s_o(\hat{p})
            new dsp_sequencer(inputDSP->clone(), fixedDSP),
            new dsp_parallelizer(
                    // The adjustable DSP: s_o(p),
                    new dsp_sequencer(inputDSP->clone(), adjustableDSP),
                    // The autodiffed DSP: \nabla s_o(p).
                    // This will have one output channel per differentiable parameter.
                    new dsp_sequencer(inputDSP->clone(), differentiatedDSP)
            )
    );
    
    auto tempUI = new MapUI;
    adjustableDSP->buildUserInterface(tempUI);
    auto numLearnableParams = tempUI->getParamsCount();
    
    fUI = std::make_unique<MapUI>();
    fDSP->buildUserInterface(fUI.get());
    
    // Allocate the audio driver
    fAudio = std::make_unique<dummyaudio>(48000, 1);
    fAudio->init("Dummy audio", fDSP);
    
    // TODO: check that parameter has diff metadata.
    for (auto p{0}; p < numLearnableParams; ++p) {
        auto address{fUI->getParamAddress(p)},
                shortName{address.substr(address.find_last_of('/') + 1)};
        fLearnableParams.insert(std::make_pair(
                address,
                Parameter{shortName, fUI->getParamValue(address), 0.f})
        );
    }
    
    // Set up csv file
    fFile.open("loss.csv");
    fFile << "iteration,loss";
    std::cout << "\n";
    for (auto &p: fLearnableParams) {
        std::cout << "Learnable parameter: " << p.first << ", value: " << p.second.value << "\n";
        fFile << ",gradient_" << p.second.shortName << "," << p.second.shortName;
    }
    std::cout << "\n";
    fFile << "\n";
}

void mldsp::doGradientDescent()
{
    auto lowLossCount{0};
    
    for (auto i{1}; i <= kNumIterations; ++i) {
        fAudio->render();
        auto out{fAudio->getOutput()};
        
        for (int frame = 0; frame < fAudio->getBufferSize(); frame++) {
            computeLoss(out, frame);
            
            if (fLoss > kEpsilon) {
                lowLossCount = 0;
                computeGradient(out, frame);
                
                // Update parameter values.
                for (auto &p: fLearnableParams) {
                    p.second.value -= kAlpha * p.second.gradient;
                    fUI->setParamValue(p.first, p.second.value);
                }
            } else {
                ++lowLossCount;
            }
            
            reportState(i, out, frame);
            
            if (lowLossCount > 20) {
                std::cout << "\n";
                return;
            }
        }
    }
    std::cout << "\nReached maximum number of iterations.\n\n";
}

void mldsp::computeLoss(FAUSTFLOAT **output, int frame)
{
    auto delta{output[OutputChannel::LEARNABLE][frame] - output[OutputChannel::GROUND_TRUTH][frame]};
    
    switch (kLossFunction) {
        case L1_NORM:
            fLoss = fabsf(delta);
            break;
        case L2_NORM:
            fLoss = powf(delta, 2);
            break;
        default:
            break;
    }
}

void mldsp::computeGradient(FAUSTFLOAT **output, int frame)
{
    auto delta{output[OutputChannel::LEARNABLE][frame] - output[OutputChannel::GROUND_TRUTH][frame]};
    
    // Set up an index to target the appropriate output channel to use for gradient descent for a
    // given differentiable parameter.
    auto k{0};
    for (auto &p: fLearnableParams) {
        switch (kLossFunction) {
            case L1_NORM:
                p.second.gradient = iszero(delta) ?
                                    0.f :
                                    output[OutputChannel::DIFFERENTIATED + k][frame] * delta / fabsf(delta);
                break;
            case L2_NORM:
                p.second.gradient = 2 * output[OutputChannel::DIFFERENTIATED + k][frame] * delta;
                break;
            default:
                break;
        }
        
        ++k;
    }
}

void mldsp::reportState(int iteration, FAUSTFLOAT **output, int frame)
{
    auto lineWidth{5 + (3 + fLearnableParams.size()) * COLUMN_WIDTH};
    if ((iteration - 1) % 20 == 0) {
        std::cout << std::string(lineWidth, '-') << "\n"
                  << std::setw(5) << "Iter"
                  << std::setw(COLUMN_WIDTH) << "Ground truth"
                  << std::setw(COLUMN_WIDTH) << "Learnable"
                  << std::setw(COLUMN_WIDTH) << "Loss";
        
        for (auto &p: fLearnableParams) {
            std::cout << std::setw(COLUMN_WIDTH) << p.second.shortName;
        }
        
        std::cout << "\n" << std::string(lineWidth, '-') << "\n";
    }
    
    std::cout << std::fixed << std::setprecision(10)
              << std::setw(5) << iteration
              << std::setw(COLUMN_WIDTH) << output[OutputChannel::GROUND_TRUTH][frame]
              << std::setw(COLUMN_WIDTH) << output[OutputChannel::LEARNABLE][frame];
    if (fLoss < 1e-3) {
        std::cout << std::setprecision(3) << std::scientific;
    }
    std::cout << std::setw(COLUMN_WIDTH) << fLoss
              << std::setprecision(10) << std::fixed;
    
    fFile << iteration << "," << fLoss;
    
    for (auto &p: fLearnableParams) {
        std::cout << std::setw(COLUMN_WIDTH);
        if (fLoss > kEpsilon) {
            std::cout << p.second.value;
        } else {
            std::cout << "-";
        }
        
        fFile << "," << p.second.gradient << "," << p.second.value;
    }
    
    std::cout << "\n";
    fFile << "\n";
}
/***************************** END autodiff.cpp *******************************/
