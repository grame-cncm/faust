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

/**
 * Consumer-side view of a kernel read. For any sigFIR node, rebuilds the
 * WORKING coefficient vector [x, c0..cn] with the source's literal delay
 * re-spelled as leading zeros : FIR[x@d, C] -> [x, 0 x d, C]. Returns
 * false for non-kernel nodes. Every consumer (occurrences, dependency
 * graph, supernodes, emission, oracle, probes) reads kernels through
 * this one lens, so a site's spelling and its accounting always agree.
 */
bool kernelWorkVec(Tree t, tvec& V);
