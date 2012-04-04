
#ifndef __LIB_FAUST__
#define __LIB_FAUST__

#include <llvm/Module.h>

#ifdef __cplusplus
extern "C"
{
#endif

int compile_faust(int argc, char* argv[], const char* input);
llvm::Module* compile_faust_llvm(int argc, char* argv[], const char* input);

#ifdef __cplusplus
}
#endif

#endif

