// TODO: add licence

#ifndef faust_autodiff_h
#define faust_autodiff_h

#include "faust/dsp/dsp-combiner.h"


class autodiff {
public:
    dsp *init(dsp *differentiatedDSP);

private:
    dsp *createDSPInstanceFromString(const std::string &appName,
                                     const std::string &dspContent);

    dsp_parallelizer *parallelizer;
};


#endif //faust_autodiff_h
