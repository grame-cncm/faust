#include <iostream>
#include <cmath>
#include <numeric>
#include <map>
#include "autodiffVerifier.h"
#include "faust/misc.h"

int main(int argc, char *argv[])
{
    if (isopt(argv, "--help")) {
        std::cout << "Usage: " << argv[0] << " --input <file> --diff <file>\n";
        exit(0);
    }
    
    if (!isopt(argv, "--input") || !isopt(argv, "--diff")) {
        std::cout << "Please provide input and differentiable Faust files.\n";
        std::cout << argv[0] << " --input <file> --diff <file>\n";
        exit(1);
    }
    
    auto input{lopts(argv, "--input", "")};
    auto diffable{lopts(argv, "--diff", "")};
    
    autodiffVerifier verifier{input, diffable};
    verifier.initialise();
    verifier.verify();
}

autodiffVerifier::autodiffVerifier(std::string inputDSPPath,
                                   std::string differentiableDSPPath) :
        fInputDSPPath(inputDSPPath),
        fDifferentiableDSPPath(differentiableDSPPath)
{}

autodiffVerifier::~autodiffVerifier()
{
    delete fDSP;
}

void autodiffVerifier::initialise()
{
    // Create the DSP for finite difference calculation
    auto inputDSP{createDSPInstanceFromPath(fInputDSPPath)};
    auto undifferentiatedDSP{createDSPInstanceFromPath(fDifferentiableDSPPath)};
    const char *argv[] = {"-diff"};
    auto differentiatedDSP{createDSPInstanceFromPath(fDifferentiableDSPPath, 1, argv)};
    
    auto tempUI = new MapUI;
    // Count the number of parameters
    undifferentiatedDSP->buildUserInterface(tempUI);
    fNumParams = tempUI->getParamsCount();
    
    fDSP = new dsp_parallelizer(
            new dsp_parallelizer(
                    // f(p + \epsilon)
                    createDSPCascade(inputDSP, undifferentiatedDSP, fNumParams),
                    // f(p)
                    new dsp_sequencer(inputDSP, undifferentiatedDSP)
            ),
            // f'(p)
            new dsp_sequencer(inputDSP->clone(), differentiatedDSP)
    );
    
    // Allocate the audio driver
    fAudio = std::make_unique<dummyaudio>(48000, 1);
    fAudio->init("Dummy audio", fDSP);
    
    fUI = std::make_unique<MapUI>();
    fDSP->buildUserInterface(fUI.get());
    
    // Increase one of each pair of parameters by epsilon.
    std::cout << "\nEpsilon: " << kEpsilon << "\n";
    for (auto p{0}; p < fNumParams; ++p) {
        auto address1{fUI->getParamAddress(2 * p + p)},
                address2{fUI->getParamAddress(fNumParams + p)};
        
        fUI->setParamValue(address1, fUI->getParamValue(address2) + kEpsilon);
    }
    
    std::cout << "Parameters:\n";
    for (int p = 0; p < fUI->getParamsCount(); ++p) {
        std::cout << fUI->getParamAddress(p)
                  << ": "
                  << fUI->getParamValue(fUI->getParamAddress(p))
                  << "\n";
    }
    std::cout << "\n";
}

dsp *autodiffVerifier::createDSPCascade(dsp *input, dsp *process, int numParams)
{
    if (numParams <= 1) {
        return new dsp_sequencer(input->clone(), process->clone());
    } else {
        return new dsp_parallelizer(
                new dsp_sequencer(input->clone(), process->clone()),
                createDSPCascade(input, process, numParams - 1)
        );
    }
}

void autodiffVerifier::verify()
{
    std::map<std::string, std::vector<float>> errors;
    for (int p = 0; p < fNumParams; ++p) {
        auto address{fUI->getParamAddress(p)};
        errors.insert(std::make_pair(
                address.substr(address.find_last_of("/") + 1),
                std::vector<float>()
        ));
    }
    
    // Index of the first autodiff channel.
    // There are as many autodiff output channels as there are parameters.
    auto autodiffIndex{fNumParams + 1};
    // Index of the undifferentiated, f(p), channel.
    auto undiffedIndex{fNumParams};
    
    for (auto i{1}; i <= kNumIterations; ++i) {
        fAudio->render();
        auto out{fAudio->getOutput()};
        
        for (int frame = 0; frame < fAudio->getBufferSize(); frame++) {
            std::cout << std::setw(5) << i;
            auto p{0};
            for (auto &e: errors) {
                auto autodiff{out[autodiffIndex + p][frame]};
                auto finiteDiff{(out[p][frame] - out[undiffedIndex][frame]) / kEpsilon};
                auto error{fabsf(autodiff - finiteDiff)};
                e.second.push_back(error);
                
                std::cout << std::setw(p == 0 ? 10 : 15) << e.first
                          << std::setprecision(10) << std::fixed
                          << std::setw(15) << "autodiff:" << std::setw(15) << autodiff
                          << std::setw(15) << "finite diff:" << std::setw(15) << finiteDiff
                          << std::setprecision(3) << (error < 1e-3 ? std::scientific : std::fixed)
                          << std::setw(10) << "|error|:" << std::setw(12) << error << "\n";
                
                ++p;
            }
        }
    }
    
    for (auto &errs: errors) {
        auto mean{std::accumulate(errs.second.begin(), errs.second.end(), 0.f) / kNumIterations};
        auto variance{0.f};
        for (auto &e: errs.second) {
            variance += powf(e - mean, 2);
        }
        auto deviation{sqrtf(variance / (kNumIterations - 1))};
        std::cout << "\nParameter: " << errs.first << "\n" << std::string(31, '=') << "\n"
                  << std::setw(20) << "Mean error:"
                  << (mean < 1e-3 ? std::scientific : std::fixed) << std::setw(11) << mean
                  << "\n"
                  << std::setw(20) << "Standard deviation:"
                  << (mean < 1e-3 ? std::scientific : std::fixed) << std::setw(11) << deviation
                  << "\n";
    }
    std::cout << "\n";
}
