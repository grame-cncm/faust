// TODO: add licence

#ifndef faust_autodiff_h
#define faust_autodiff_h

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <memory>
#include <fstream>
#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/audio/dummy-audio.h"

class mldsp {
public:
    mldsp(std::string inputDSPPath,
          std::string groundTruthDSPPath,
          std::string differentiableDSPPath,
          FAUSTFLOAT learningRate = 0.1f,
          FAUSTFLOAT sensitivity = 1e-7f,
          int numIterations = 150);

    ~mldsp();

    void initialise();

    void doGradientDescent();

private:
    struct Parameter {
        FAUSTFLOAT value;
        FAUSTFLOAT gradient;
    };

    enum LossFunction {
        L1_NORM,
        L2_NORM
    };

    enum OutputChannel {
        GROUND_TRUTH = 0,
        LEARNABLE = 1,
        DIFFERENTIATED = 2
    };

    static constexpr int NUMBER_WIDTH{15}, LABEL_WIDTH{13}, PARAM_WIDTH{11};
    const FAUSTFLOAT kAlpha, kEpsilon;
    const int kNumIterations;

    dsp *createDSPInstanceFromString(const std::string &appName,
                                     const std::string &dspContent);

    dsp *createDSPInstanceFromPath(const std::string &path,
                                   int argc = 0,
                                   const char *argv[] = nullptr);

    /**
     * Update the loss value with the squared L-2 norm between the learnable
     * and ground truth signals.
     *
     * @param output Audio signals representing ground truth, learnable and
     *               differentiated dsp output.
     * @param frame The output frame with which to compute the loss.
     */
    void computeLoss(FAUSTFLOAT **output, int frame);

    /**
     * Update the gradient value with the gradient of the loss function.
     *
     * @param output Audio signals representing ground truth, learnable and
     *               differentiated dsp output.
     * @param frame The output frame with which to compute the gradient.
     */
    void computeGradient(FAUSTFLOAT **output, int frame);

    void reportState(int iteration, FAUSTFLOAT **output, int frame);

    std::string fInputDSPPath, fGroundTruthDSPPath, fDifferentiableDSPPath;
    std::unique_ptr<dsp> fDSP;
    std::unique_ptr<MapUI> fUI;
    std::map<std::string, Parameter> fLearnableParams;
    LossFunction fLossFunction{L2_NORM};
    FAUSTFLOAT fLoss{0.f};
    std::unique_ptr<dummyaudio> fAudio;
    std::ofstream fFile;
};


#endif //faust_autodiff_h
