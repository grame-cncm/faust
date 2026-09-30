#pragma once

#include "signals.hh"

/// Exact integer conversions (-ifp) : a conversion to int of a product whose
/// coefficient c is the rounding of a small rational p/q, computed outside the
/// sample loop, int(c*Y), is emitted as int((p*Y)/q). When p*Y is exact, the
/// division is the only rounding : an exact integer quotient is found exactly,
/// where c*Y may land one ulp below it and be truncated one unit short (a delay
/// of 1617 samples scaled from 44.1 to 48 kHz : 1759 instead of 1760). The input
/// must be type-annotated. See exactIntCasts.cpp for the conditions.
Tree exactIntCasts(Tree lsig);
