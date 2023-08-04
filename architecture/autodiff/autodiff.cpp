// TODO: add licence

#include <iostream>
#include <cmath>
#include "autodiff.h"
#include "faust/misc.h"
#include "faust/dsp/llvm-dsp.h"

int main(int argc, char *argv[])
{
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
        fDifferentiableDSPPath(differentiableDSPPath)
{}

mldsp::~mldsp()
{
    fFile.close();
    delete fDSP;
    for (auto &factory: fDSPFactories) {
        deleteDSPFactory(factory.second);
    }
}

void mldsp::initialise()
{
    auto inputDSP{createDSPInstanceFromPath(fInputDSPPath)};
    auto fixedDSP{createDSPInstanceFromPath(fGroundTruthDSPPath)};
    auto adjustableDSP{createDSPInstanceFromPath(fDifferentiableDSPPath)};
    const char *argv[] = {"-diff"};
    auto differentiatedDSP{createDSPInstanceFromPath(fDifferentiableDSPPath, 1, argv)};
    
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
    
    fUI = std::make_unique<MapUI>();
    fDSP->buildUserInterface(fUI.get());
    
    // Allocate the audio driver
    fAudio = std::make_unique<dummyaudio>(48000, 1);
    fAudio->init("Dummy audio", fDSP);
    
    // TODO: check that parameter has diff metadata.
    for (auto p{0}; p < fUI->getParamsCount(); ++p) {
        auto address{fUI->getParamAddress(p)};
        fLearnableParams.insert(std::make_pair(address, Parameter{fUI->getParamValue(address), 0.f}));
    }
    fFile.open("loss.csv");
    fFile << "iteration,loss";
    for (auto &p: fLearnableParams) {
        std::cout << "Learnable parameter: " << p.first << ", value: " << p.second.value << "\n";
        fFile << ",gradient,param";
    }
    fFile << "\n";
}

void mldsp::doGradientDescent()
{
    for (auto i{1}; i <= kNumIterations; ++i) {
        fAudio->render();
        auto out{fAudio->getOutput()};
        
        for (int frame = 0; frame < fAudio->getBufferSize(); frame++) {
            computeLoss(out, frame);
            
            if (fLoss > kEpsilon) {
                computeGradient(out, frame);
                
                // Update parameter values.
                for (auto &p: fLearnableParams) {
                    p.second.value -= kAlpha * p.second.gradient;
                    fUI->setParamValue(p.first, p.second.value);
                }
            }
            
            reportState(i, out, frame);
        }
    }
}

dsp *mldsp::createDSPInstanceFromString(
        const std::string &appName,
        const std::string &dspContent
)
{
    auto factory{fDSPFactories.find(appName)};
    
    if (factory == fDSPFactories.end()) {
        std::string errorMessage;
        
        fDSPFactories.insert(std::make_pair(
                appName,
                createDSPFactoryFromString(appName, dspContent, 0, nullptr, "", errorMessage)
        ));
        
        factory = fDSPFactories.find(appName);
        
        if (!factory->second) {
            std::cout << errorMessage;
        }
        assert(factory->second);
    }
    
    return factory->second->createDSPInstance();
}

dsp *mldsp::createDSPInstanceFromPath(const std::string &path,
                                      int argc, const char *argv[])
{
    auto key{path};
    for (int i{0}; i < argc; ++i) {
        key.append(argv[i]);
    }
    auto factory{fDSPFactories.find(key)};
    
    if (factory == fDSPFactories.end()) {
        std::string errorMessage;
        std::cout << "Creating DSP from file with key " << key << "\n";
        
        fDSPFactories.insert(std::make_pair(
                key,
                createDSPFactoryFromFile(path, argc, argv, "", errorMessage)
        ));
        
        factory = fDSPFactories.find(key);
        
        std::cout << "factory: " << factory->second << "\n";
        if (!factory->second) {
            std::cout << "Error: " << errorMessage;
        }
        assert(factory->second);
    }
    
    return factory->second->createDSPInstance();
}

void mldsp::computeLoss(FAUSTFLOAT **output, int frame)
{
    switch (fLossFunction) {
        case L1_NORM:
            fLoss = fabsf(output[OutputChannel::LEARNABLE][frame] - output[OutputChannel::GROUND_TRUTH][frame]);
            break;
        case L2_NORM:
            fLoss = powf(output[OutputChannel::LEARNABLE][frame] - output[OutputChannel::GROUND_TRUTH][frame], 2);
            break;
        default:
            break;
    }
}

void mldsp::computeGradient(FAUSTFLOAT **output, int frame)
{
    // Set up an index to target the appropriate output channel to use for gradient descent for a
    // given differentiable parameter.
    auto k{0};
    for (auto &p: fLearnableParams) {
        p.second.gradient = 2 * output[OutputChannel::DIFFERENTIATED + k][frame] *
                            (output[OutputChannel::LEARNABLE][frame] - output[OutputChannel::GROUND_TRUTH][frame]);
        ++k;
    }
}

void mldsp::reportState(int iteration, FAUSTFLOAT **output, int frame)
{
    std::cout << std::fixed << std::setprecision(10) <<
              std::setw(5) << iteration <<
              std::setw(LABEL_WIDTH) << "Sig GT: " <<
              std::setw(NUMBER_WIDTH) << output[OutputChannel::GROUND_TRUTH][frame] <<
              std::setw(LABEL_WIDTH) << "Sig Learn: " <<
              std::setw(NUMBER_WIDTH) << output[OutputChannel::LEARNABLE][frame] <<
              std::setw(LABEL_WIDTH) << "Loss: " <<
              std::setw(NUMBER_WIDTH) << fLoss;
    
    fFile << iteration << "," << fLoss;
    
    if (fLoss > kEpsilon) {
        auto k{0};
        for (auto &p: fLearnableParams) {
            std::cout << "\n" << std::setw(5) << "." <<
                      std::setw(PARAM_WIDTH) << fUI->getParamShortname(k) << ":" <<
                      std::setw(LABEL_WIDTH) << "ds/dp: " <<
                      std::setw(NUMBER_WIDTH) << output[OutputChannel::DIFFERENTIATED + k][frame] <<
                      std::setw(LABEL_WIDTH) << "Grad: " <<
                      std::setw(NUMBER_WIDTH) << p.second.gradient <<
                      std::setw(LABEL_WIDTH) << "Value: " <<
                      std::setw(NUMBER_WIDTH) << p.second.value;
            
            fFile << "," << p.second.gradient << "," << p.second.value;
            
            ++k;
        }
    } else {
        for (auto &p: fLearnableParams) {
//            fFile << ",,";
            fFile << "," << p.second.gradient << "," << p.second.value;
        }
    }
    
    std::cout << "\n";
    fFile << "\n";
}
/***************************** END autodiff.cpp *******************************/
