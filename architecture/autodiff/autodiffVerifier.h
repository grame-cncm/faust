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
    const float kEpsilon;
    
    dsp *createDSPCascade(dsp *, dsp*, int);
    
    int fNumParams;
    std::string fInputDSPPath, fDifferentiableDSPPath;
    dsp *fDSP;
    std::unique_ptr<MapUI> fUI;
    std::unique_ptr<dummyaudio> fAudio;
};


#endif //faust_autodiffverifier_h
