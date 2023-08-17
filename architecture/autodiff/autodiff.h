#ifndef faust_autodiff_h
#define faust_autodiff_h

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <fstream>
#include "dspFactoryOwner.h"
#include "faust/gui/MapUI.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/audio/dummy-audio.h"

class AutodiffUI : public UI, public PathBuilder
{
public:
    struct DifferentiableParameter
    {
        std::string label;
        FAUSTFLOAT *zone;
        FAUSTFLOAT init;
        FAUSTFLOAT min;
        FAUSTFLOAT max;
        FAUSTFLOAT step;
        FAUSTFLOAT gradient{0.f};
        
        void clamp() const
        {
            if (*zone > max) {
                *zone = max;
            } else if (*zone < min) {
                *zone = min;
            }
        }
    };
    
    void openTabBox(const char *label) override
    {
        pushLabel(label);
    }
    
    void openHorizontalBox(const char *label) override
    {
        pushLabel(label);
    }
    
    void openVerticalBox(const char *label) override
    {
        pushLabel(label);
    }
    
    void closeBox() override
    {}
    
    void addHorizontalBargraph(const char *label, float *zone, float min, float max) override
    {}
    
    void addVerticalBargraph(const char *label, float *zone, float min, float max) override
    {}
    
    void addSoundfile(const char *label, const char *filename, Soundfile **sf_zone) override
    {}
    
    void addButton(const char *label, FAUSTFLOAT *zone) override
    {
        registerDifferentiableParameter(label, zone);
    }
    
    void addCheckButton(const char *label, FAUSTFLOAT *zone) override
    {
        registerDifferentiableParameter(label, zone);
    }
    
    void addVerticalSlider(const char *label,
                           FAUSTFLOAT *zone,
                           FAUSTFLOAT init,
                           FAUSTFLOAT min,
                           FAUSTFLOAT max,
                           FAUSTFLOAT step) override
    {
        registerDifferentiableParameter(label, zone, init, min, max, step);
    }
    
    void addHorizontalSlider(const char *label,
                             FAUSTFLOAT *zone,
                             FAUSTFLOAT init,
                             FAUSTFLOAT min,
                             FAUSTFLOAT max,
                             FAUSTFLOAT step) override
    {
        registerDifferentiableParameter(label, zone, init, min, max, step);
    }
    
    void addNumEntry(const char *label,
                     FAUSTFLOAT *zone,
                     FAUSTFLOAT init,
                     FAUSTFLOAT min,
                     FAUSTFLOAT max,
                     FAUSTFLOAT step) override
    {
        registerDifferentiableParameter(label, zone, init, min, max, step);
    }
    
    void declare(FAUSTFLOAT *zone, const char *key, const char *val) override
    {
        if (strcmp(key, "diff") == 0 && (strcmp(val, "on") == 0 || strcmp(val, "1") == 0)) {
            // This parameter zone carries valid autodiff metadata; take a note of the zone.
            fDiffZones.push_back(zone);
        }
    }
    
    /**
     * Get the number of parameters.
     * Only parameters with the `[diff:1]` or `[diff:on]` flag are counted.
     * @return The number of parameters.
     */
    int getParamsCount()
    {
        return static_cast<int>(fPathDiffMap.size());
    }
    
    /**
     * Get the path for the parameter with a given index.
     * @param index
     * @return The parameter path.
     */
    std::string getParamAddress(int index)
    {
        if (index < 0 || index > int(fPathDiffMap.size())) {
            return "";
        } else {
            auto it = fPathDiffMap.begin();
            while (index-- > 0 && it++ != fPathDiffMap.end()) {}
            return it->first;
        }
    }
    
    /**
     * Return the label for the parameter with a given index.
     * @param index
     * @return The parameter label.
     */
    std::string getParamLabel(int index)
    {
        if (index < 0 || index > int(fPathDiffMap.size())) {
            return "";
        } else {
            auto it = fPathDiffMap.begin();
            while (index-- > 0 && it++ != fPathDiffMap.end()) {}
            return it->second.label;
        }
    }
    
    FAUSTFLOAT getParamValue(const std::string &str)
    {
        const auto iter = fPathDiffMap.find(str);
        if (iter != fPathDiffMap.end()) {
            return *iter->second.zone;
        }
        
        fprintf(stderr, "ERROR : getParamValue '%s' not found\n", str.c_str());
        return 0;
    }
    
    void setParamGradient(const std::string &str, FAUSTFLOAT value)
    {
        const auto fPathDiffMapIter = fPathDiffMap.find(str);
        if (fPathDiffMapIter != fPathDiffMap.end()) {
            fPathDiffMapIter->second.gradient = value;
            return;
        }
        
        fprintf(stderr, "ERROR : setParamGradient '%s' not found\n", str.c_str());
    }
    
    FAUSTFLOAT getParamGradient(const std::string &str)
    {
        const auto fPathDiffMapIter = fPathDiffMap.find(str);
        if (fPathDiffMapIter != fPathDiffMap.end()) {
            return fPathDiffMapIter->second.gradient;
        }
        
        fprintf(stderr, "ERROR : getParamGradient '%s' not found\n", str.c_str());
        return 0;
    }
    
    /**
     * Update the value of a parameter based on its current gradient and the provided
     * learning rate. `setParamGradient` should be called before each call to this
     * method.
     *
     * @param path The parameter path/address
     * @param alpha The learning rate
     */
    void updateParamValue(const std::string &path, const FAUSTFLOAT alpha)
    {
        const auto fPathDiffMapIter{fPathDiffMap.find(path)};
        if (fPathDiffMapIter != fPathDiffMap.end()) {
            *fPathDiffMapIter->second.zone -= alpha * fPathDiffMapIter->second.gradient;
            if (respectLimits) {
                fPathDiffMapIter->second.clamp();
            }
            return;
        }
        
        fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
    }

private:
    void registerDifferentiableParameter(const char *label,
                                         FAUSTFLOAT *zone,
                                         FAUSTFLOAT init = 0.f,
                                         FAUSTFLOAT min = 0.f,
                                         FAUSTFLOAT max = 0.f,
                                         FAUSTFLOAT step = 0.f)
    {
        if (std::find(fDiffZones.begin(), fDiffZones.end(), zone) != fDiffZones.end()) {
            // This parameter zone is in the list of zones with autodiff metadata;
            // add it to the map.
            std::string path = buildPath(label);
            fPathDiffMap[path] = DifferentiableParameter{label, zone, init, min, max, step};
        }
    }
    
    std::map<std::string, DifferentiableParameter> fPathDiffMap;
    std::vector<FAUSTFLOAT *> fDiffZones;
    bool respectLimits{false};
};

class mldsp : private dspFactoryOwner
{
public:
    enum LossFunction
    {
        L1_NORM,
        L2_NORM
    };
    
    mldsp(std::string inputDSPPath,
          std::string groundTruthDSPPath,
          std::string differentiableDSPPath,
          LossFunction lossFunction = L2_NORM,
          FAUSTFLOAT learningRate = 0.1f,
          FAUSTFLOAT sensitivity = 1e-7f,
          int numIterations = 10000);
    
    ~mldsp();
    
    void initialise();
    
    void doGradientDescent();

private:
    enum OutputChannel
    {
        GROUND_TRUTH = 0,
        LEARNABLE = 1,
        DIFFERENTIATED = 2
    };
    
    static constexpr int COLUMN_WIDTH{15};
    const LossFunction kLossFunction;
    const FAUSTFLOAT kAlpha, kEpsilon;
    const int kNumIterations;
    
    void buildDSP();
    
    void setupAudio();
    
    void setupReporting();
    
    void setupUI();
    
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
     * Update the gradient value for each learnable parameter with the gradient
     * of the loss function.
     *
     * @param output Audio signals representing ground truth, learnable and
     *               differentiated dsp output.
     * @param frame The output frame with which to compute the gradient.
     */
    void computeGradient(FAUSTFLOAT **output, int frame);
    
    /**
     * Write information about the gradient descent process to standard output
     * and to a csv file.
     *
     * @param iteration
     * @param output
     * @param frame
     */
    void reportState(int iteration, FAUSTFLOAT **output, int frame);
    
    std::string fInputDSPPath, fGroundTruthDSPPath, fDifferentiableDSPPath;
    /**
     * This will hold the parallelized ground truth, differentiated, and learnable
     * versions of the DSP algorithm.
     *
     * NB. Using a unique_ptr causes fDSP to be deleted *after* the factories,
     * so use a regular pointer.
     */
    dsp *fDSP;
    dsp *fLearnableDSP;
    bool fDSPReady{false};
    
    std::unique_ptr<AutodiffUI> fUI;
    bool fUIReady{false};
    
    FAUSTFLOAT fLoss{0.f};
    /**
     * The audio device.
     */
    std::unique_ptr<dummyaudio> fAudio;
    bool fAudioReady{false};
    /**
     * A csv file to write to.
     */
    std::ofstream fFile;
    
    /**
     * A map of learnable parameter addresses and their indices in the UI.
     */
    std::map<std::string, int> fLearnableParams;
};

#endif //faust_autodiff_h
