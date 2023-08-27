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
    buildDSPs();
    setupAudio();
    setupUI();
}

void autodiffVerifier::setupAudio()
{
    assert(fDSPReady);
    
    // Allocate the audio driver
    fAudio = std::make_unique<dummyaudio>(48000, 1);
    fAudio->init("Dummy audio", fDSP);
    fAudioReady = true;
}

void autodiffVerifier::setupUI()
{
    assert(fAudioReady);
    
    std::cout << "\nEpsilon: " << kEpsilon << "\n\n";
    
    fUI = std::make_unique<MapUI>();
    // The only parameters of interest are those that must be increased by
    // epsilon, so only build a UI for the corresponding dsp instance.
    fEpsilonDSP->buildUserInterface(fUI.get());
    
    // Increase one of each group of parameters by epsilon,
    for (auto p{0}; p < fNumParams; ++p) {
        auto address{fUI->getParamAddress(fNumParams * p + p)};
        
        fUI->setParamValue(address, fUI->getParamValue(address) + kEpsilon);
    }
    
    // and report the result to standard out.
    for (auto p{0}, q{0}; p < fUI->getParamsCount(); ++p) {
        if (p % fNumParams == 0) {
            ++q;
            std::cout << "y(" << (q == 1 ? "" : "...,") << "p" << q << " + epsilon"
                      << (q == fNumParams ? "" : ",...") << ")\n";
        }
        std::cout << fUI->getParamAddress(p)
                  << ": "
                  << fUI->getParamValue(fUI->getParamAddress(p))
                  << "\n";
    }
    std::cout << "\n";
}

void autodiffVerifier::buildDSPs()
{
    // Create the input DSP
    auto inputDSP{createDSPInstanceFromPath(fInputDSPPath)};
    
    // Create the DSP for finite difference calculation
    auto undifferentiatedDSP{new dsp_sequencer(
            inputDSP,
            createDSPInstanceFromPath(fDifferentiableDSPPath)
    )};
    
    // Create the autodiffed DSP for comparison
    const char *argv[] = {"-diff"};
    auto differentiatedDSP{new dsp_sequencer(
            inputDSP->clone(),
            createDSPInstanceFromPath(fDifferentiableDSPPath, 1, argv)
            //createDSPInstanceFromPath("/usr/local/share/faust/examples/autodiff/recursion/target.dsp")
    )};
    
    // Count the number of parameters in the undifferentiated DSP
    auto tempUI = new MapUI;
    undifferentiatedDSP->buildUserInterface(tempUI);
    fNumParams = tempUI->getParamsCount();
    
    fEpsilonDSP = createDSPCascade(undifferentiatedDSP, fNumParams);
    
    fDSP = new dsp_parallelizer(
            new dsp_parallelizer(
                    // f(p + \epsilon)
                    fEpsilonDSP,
                    // f(p)
                    undifferentiatedDSP->clone()
            ),
            // f'(p)
            differentiatedDSP
    );
    fDSPReady = true;
}

dsp *autodiffVerifier::createDSPCascade(dsp *dsp, int numInstances)
{
    assert(numInstances > 0);
    if (numInstances <= 1) {
        return dsp->clone();
    } else {
        return new dsp_parallelizer(
                dsp->clone(),
                createDSPCascade(dsp, numInstances - 1)
        );
    }
}

void autodiffVerifier::verify()
{
    std::map<std::string, std::vector<float>> deltas;
    for (int p = 0; p < fNumParams; ++p) {
        auto address{fUI->getParamAddress(p)};
        deltas.insert(std::make_pair(
                address.substr(address.find_last_of('/') + 1),
                std::vector<float>()
        ));
    }
    
    // Index of the undifferentiated, f(p), channel.
    auto undiffedIndex{fNumParams};
    // Index of the first autodiff channel.
    // There are as many autodiff output channels as there are parameters.
    auto autodiffIndex{fNumParams + 1};
    
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
                // Get y'(p)
                auto autodiff{out[autodiffIndex + p][frame]};
                // Compute (y(p + epsilon) - y(p)) / epsilon
                auto finiteDiff{(out[p][frame] - out[undiffedIndex][frame]) / kEpsilon};
                // Get the absolute difference between the above
                auto delta{fabsf(autodiff - finiteDiff)};
                // Compute relative error
                auto relError{autodiff == 0.f ? 0.f : fabsf(100.f * delta / autodiff)};
                
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
    
    // Report mean and standard deviation.
    for (auto &dd: deltas) {
        auto mean{std::accumulate(dd.second.begin(), dd.second.end(), 0.f) / kFloatNumIterations};
        
        // Compute standard deviation
        auto variance{0.f};
        for (auto &d: dd.second) {
            variance += powf(d - mean, 2);
        }
        auto deviation{sqrtf(variance / (kFloatNumIterations - 1.f))};
        
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
