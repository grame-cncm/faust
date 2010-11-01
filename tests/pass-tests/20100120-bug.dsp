// BUG : the compiler reports :
// faust: extended/minprim.cpp:40: virtual CTree* MinPrim::computeSigOutput(const std::vector<CTree*, std::allocator<CTree*> >&): Assertion `args.size() == arity()' failed.
// like it was trying to evaluate 2:min

process = vslider("2:min", 0, 0, 1, 0.01);


