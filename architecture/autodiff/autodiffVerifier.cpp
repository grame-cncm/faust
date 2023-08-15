#include <iostream>
#include <cmath>
#include <numeric>
#include <map>
#include "autodiffVerifier.h"
#include "faust/misc.h"

int main(int argc, char *argv[])
{
    if (isopt(argv, "--help")) {
        std::cout << "Usage: " << argv[0] << " --input <file> --diff <file> [-e <epsilon>]\n";
        exit(0);
    }
    
    if (!isopt(argv, "--input") || !isopt(argv, "--diff")) {
        std::cout << "Please provide input and differentiable Faust files.\n";
        std::cout << argv[0] << " --input <file> --diff <file>\n";
        exit(1);
    }
    
    auto input{lopts(argv, "--input", "")};
    auto diffable{lopts(argv, "--diff", "")};
    auto epsilon{strtof(
            lopts1(argc, argv, "--epsilon", "-e", "0.001"),
            nullptr
    )};
    
    autodiffVerifier verifier{input, diffable, epsilon};
    verifier.initialise();
    verifier.verify();
}

autodiffVerifier::autodiffVerifier(std::string inputDSPPath,
                                   std::string differentiableDSPPath,
                                   float epsilon) :
        kEpsilon(epsilon),
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
    std::map<std::string, std::vector<float>> deltas;
    for (int p = 0; p < fNumParams; ++p) {
        auto address{fUI->getParamAddress(p)};
        deltas.insert(std::make_pair(
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
        if ((i - 1) % 20 == 0) {
            std::cout << std::string(80, '-') << "\n"
                      << std::setw(5) << "Iter"
                      << std::setw(15) << "Param"
                      << std::setw(15) << "Autodiff"
                      << std::setw(15) << "Finite diff"
                      << std::setw(15) << "|delta|"
                      << std::setw(15) << "Rel. error"
                      << "\n" << std::string(80, '-') << "\n";
        }
        
        fAudio->render();
        auto out{fAudio->getOutput()};
        
        for (int frame = 0; frame < fAudio->getBufferSize(); frame++) {
            std::cout << std::setw(5) << i;
            auto p{0};
            for (auto &d: deltas) {
                auto autodiff{out[autodiffIndex + p][frame]};
                auto finiteDiff{(out[p][frame] - out[undiffedIndex][frame]) / kEpsilon};
                auto delta{fabsf(autodiff - finiteDiff)};
                auto relError{iszero(autodiff) ? 0.f : fabsf(100.f * delta / autodiff)};
                d.second.push_back(delta);
                
                std::cout << std::setw(p == 0 ? 15 : 20) << d.first
                          << std::setprecision(10) << std::fixed
                          << std::setw(15) << autodiff
                          << std::setw(15) << finiteDiff
                          << std::setprecision(3) << (delta < 1e-3 ? std::scientific : std::fixed)
                          << std::setw(15) << delta
                          << std::setprecision(3) << std::fixed
                          << std::setw(13) << relError << " %\n";
                
                ++p;
            }
        }
    }
    
    for (auto &dd: deltas) {
        auto mean{std::accumulate(dd.second.begin(), dd.second.end(), 0.f) / kNumIterations};
        auto variance{0.f};
        for (auto &d: dd.second) {
            variance += powf(d - mean, 2);
        }
        auto deviation{sqrtf(variance / (kNumIterations - 1))};
        std::cout << "\nParameter: " << dd.first << "\n" << std::string(31, '=') << "\n"
                  << std::setw(20) << "Mean delta:"
                  << (mean < 1e-3 ? std::scientific : std::fixed) << std::setw(11) << mean
                  << "\n"
                  << std::setw(20) << "Standard deviation:"
                  << (mean < 1e-3 ? std::scientific : std::fixed) << std::setw(11) << deviation
                  << "\n";
    }
    std::cout << "\n";
}
