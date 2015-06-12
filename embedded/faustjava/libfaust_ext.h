
#include "faust/dsp/llvm-c-dsp.h"

llvm_dsp_factory* createCDSPFactoryFromFileAux(const char* filename, const char* argv,
                                                const char* target, int opt_level);
      
llvm_dsp_factory* createCDSPFactoryFromStringAux(const char* name_app, const char* dsp_content,
                                                const char* argv, const char* target, int opt_level);
                                                
const char* getCDSPLastError();
    