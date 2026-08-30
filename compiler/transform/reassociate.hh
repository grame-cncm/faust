#pragma once

#include "signals.hh"

/// Late state-join reassociation : inside every single-definition recursive
/// group, the sum terms that depend on the state (contain the group's own
/// projection) are joined LAST -- the recurrence chain shrinks to one add
/// plus the term's own depth. Off-path terms stay a flat comb : measured,
/// both clang (-ffast-math) and the out-of-order hardware handle flat
/// reductions as well as balanced trees, and WITHOUT fast-math the join
/// placement is worth x4 (see exp-reassoc micro-benchmarks).
Tree reassociate(Tree lsig);
