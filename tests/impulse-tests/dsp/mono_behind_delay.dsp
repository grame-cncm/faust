// A recursion whose definition starts with a delay : y = (x + 0.5*y')@4, read as y' by the
// definition and by the output (out = 0.5*x + 0.5*y'). The read of y' feeds the delay line,
// not the write of y : one variable for y would be overwritten before its read.
process = _ <: (_, ((+ : @(4)) ~ *(0.5) : mem : *(0.5))) : (*(0.5), _) :> _;
