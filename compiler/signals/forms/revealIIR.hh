#pragma once
#include "signals.hh"

Tree revealIIR(Tree lsig);

// The common numerator (-fir-hoist) : FIR_K(IIR_D(x)) -> IIR_D(FIR_K(x)) for
// the groups of at least two constant-coefficient filters sharing x and K
Tree hoistCommonNumerators(Tree lsig);

