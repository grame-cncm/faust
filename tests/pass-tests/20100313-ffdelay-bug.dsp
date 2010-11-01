//-------------------------------------------------------------------------------
// bug corrected in version 0.9.14
//-------------------------------------------------------------------------------
// No vector name for : f()
// faust: generator/compile_scal.cpp:1067: 
// virtual std::string ScalarCompiler::generateFixDelay(CTree*, CTree*, CTree*): 
// Assertion `0' failed.
//-------------------------------------------------------------------------------
//
f = ffunction(float f(), <math.h>, "");
process = f : mem;
