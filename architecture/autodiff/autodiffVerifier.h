#ifndef faust_autodiffverifier_h
#define faust_autodiffverifier_h

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "dspFactoryOwner.h"
#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/audio/dummy-audio.h"

class autodiffVerifier : private dspFactoryOwner
{
public:
    autodiffVerifier(std::string inputDSPPath,
                     std::string differentiableDSPPath,
                     float epsilon = 1e-3f);
    
    ~autodiffVerifier();
    
    void initialise();
    
    void verify();

private:
    const int kNumIterations{100};
    const float kFloatNumIterations{static_cast<float>(kNumIterations)};
    const float kEpsilon;
    
    void buildDSPs();
    
    void setupUI();
    
    void setupAudio();
    
    /**
     * Create a cascade of parallel `dsp` instances.
     *
     * @param dsp A DSP algorithm to duplicate as part of the cascade.
     * @param numInstances The number (>= 1) of dsp instances to create.
     * @return If numInstances == 1, a clone of the supplied dsp instance.
     * Otherwise a dsp_paralellizer instance containing cascaded dsp
     * instances, e.g.:
     *
     * ```
     * new dsp_paralellizer(
     *     dsp->clone(),
     *     new dsp_paralellizer(
     *         dsp->clone(), dsp->clone()
     *     )
     * )
     * ```
     */
    dsp *createDSPCascade(dsp *dsp, int numInstances);
    
    int fNumParams;
    std::string fInputDSPPath, fDifferentiableDSPPath;
    /**
     * The DSP instance to which to apply epsilon for finite difference
     * calculation.
     * If the algorithm has more than one parameter, this will be a
     * dsp_parallelizer.
     */
    dsp *fEpsilonDSP;
    /**
     * The DSP instance to send to the audio device.
     * This will be a dsp_parallelizer, and one of its parallel instances
     * will be fEpsilonDSP.
     */
    dsp *fDSP;
    bool fDSPReady{false};
    /**
     * A UI instance used to apply epsilon to the DSP instances in
     * fEpsilonDSP.
     */
    std::unique_ptr<MapUI> fUI;
    /**
     * The audio device.
     */
    std::unique_ptr<dummyaudio> fAudio;
    bool fAudioReady{false};
};


#endif //faust_autodiffverifier_h
