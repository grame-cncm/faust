//-------------------------------------------------
// bug découvert le 24 juillet 2008 en voulant
// compiler sonik-cube
// faust: generator/compile_scal.cpp:1095:
// virtual std::string ScalarCompiler::generateFixDelay(CTree*, CTree*, CTree*):
// Assertion `getVectorNameProperty(exp, vecname)' failed.
//-------------------------------------------------

process   = vbargraph("dB", -96, 1) : @(10);

