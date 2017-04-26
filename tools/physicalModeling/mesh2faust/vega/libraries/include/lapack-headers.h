#if defined(WIN32) || defined(_WIN32) || defined(linux)
  #include "mkl_cblas.h"
  #include "mkl_types.h"
  #include "mkl_lapack.h"
  #include "mkl_blas.h"
#elif defined(__APPLE__)
  #include <Accelerate/Accelerate.h>
  #ifdef __GNUC__
    #ifndef __clang__
    // The following below applies to Mac OS X, when using the gcc compiler as opposed to clang.
    // On our MacBooks with recent OS X versions, the following headers are required to find CBLAS routines when using gcc (as opposed to clang).
      #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_9
        #include </System/Library/Frameworks/Accelerate.framework/Frameworks/vecLib.framework/Headers/cblas.h>
        #include </System/Library/Frameworks/Accelerate.framework/Frameworks/vecLib.framework/Headers/clapack.h>
      #endif
    #endif
  #endif
#endif

