#pragma once

#include "signals.hh"

/// Structural staging : place sigTemp barriers on the single-use expressions
/// of at least K operations (K=1 : every operation, the SSA form). See
/// placeTemps.cpp for the policy and its rationale.
Tree placeTemps(Tree lsig, int K);
