
#pragma once

#include "signals.hh"

/**
 * @brief Do constant propagation using the interval library. If the interval of an expression is
 * reduced to a single number, then this expression can be replaced by this single number.
 *
 * @param sig
 * @param trace
 * @return Tree
 */
Tree newConstantPropagation(Tree sig, bool trace = false);