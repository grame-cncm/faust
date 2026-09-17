#pragma once

#include "signals.hh"

// throughShared : gather through the shared sub-sums (only when lowerSums follows)
Tree revealSum(Tree L, bool throughShared = false);
