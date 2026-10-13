#pragma once
#include "signals.hh"

/// Reorders the terms of every Sum by their intervals (experimental, FAUST_SUMORDER=1) :
/// within each class of rate, the partial sums of the chain kept as small as possible.
/// Needs typed signals ; the result must be typed again.
Tree orderSumsByIntervals(Tree L);
