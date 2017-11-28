----------------------------------------------------------------
  How to compile using cmake
----------------------------------------------------------------

The cmake setup currently supports 3 types of output:
- the faust compiler as exec
- the faust compiler as static library
- the faust compiler as shared library

You can select any set of backends using options e.g.
> cmake -DWASM_BACKEND=ON .
By default only the CPP backend is included.

The 'backends.txt' file can be used to populate the cmake cache and/or to customize your setup. 
To use it, call:
> cmake -C backends.txt .



----------------------------------------------------------------
  Notes regarding backends support
----------------------------------------------------------------
- the LLVM backend has not been tested on all platforms
  It currently works on MacOS with a recompiled version of LLVM including RTTI 
  (addressing the RTTI issue is currently in progress)
- the 'interpreter' backend is not supported on windows using MSVC compilers
  This is due to label dereferencing operator && that is only supported by gcc.



