#pragma once

#include "signals.hh"

/// Intra-kernel FIR factorization (the first floor of "optimal FIR
/// sharing") : a kernel whose non-zero coefficients are all EQUAL loses
/// its gain -- FIR[x, c,c,0,c] becomes c * FIR[x, 1,1,0,1]. This both
/// removes redundant multiplications and NORMALIZES the all-ones kernels,
/// which unlocks their sliding-sum emission (see generateFIR : an
/// all-ones contiguous FIR is a moving sum, computable in O(1) whatever
/// its length). The content stays a FIR -- typed tightly by the
/// compositional expansion -- and the emission chooses the form.
Tree factorizeFIRs(Tree L);
