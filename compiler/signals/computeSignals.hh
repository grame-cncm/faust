/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
    SPDX-License-Identifier: LGPL-2.1-or-later
 ************************************************************************
 ************************************************************************/

#pragma once

#include "ComputeAlgebra.hh"
#include "sigs-export.hh"
#include "signals.hh"

/**
 * The constructors of the computation form (FaustAlgebra/ComputeAlgebra.hh) as trees.
 *
 * The computation form is the program as the code computes it, translated from the
 * certified normal form : its nodes carry the decisions the certification took, as DATA
 * children (numbers, never signals), so that a rebuild of a node rebuilds its data and the
 * code generation reads them instead of an interval. Its constructors belong to their own
 * signature, "Faust.Compute" : a normal-form algebra (SignalDispatch) never mistakes them
 * for its own operations, and a traversal that does not know them fails loudly
 * (getSubSignals) rather than dropping their data.
 *
 * Every constructor has its normal-form source : the operands are the same signals, the
 * value is the same, only the decision is added.
 */

namespace sigs {

/// The signature of the computation form's constructors
SIGS_API Signature computeSignature();

/// Registers the constructors of the computation form (initSignalSymbols calls it)
void initComputeSymbols();

}  // namespace sigs

/// a tree of the computation form
SIGS_API bool isComputeSignal(Tree t);

/// phase(x, p) = (x % p) / p, the division a product by 1 / p computed at the rate of p
/// when byInverse
SIGS_API Tree cfPhase(Tree x, Tree p, bool byInverse);
SIGS_API bool isCfPhase(Tree s, Tree& x, Tree& p, bool& byInverse);

/// mix(c, a, b) = (1 - c) * a + c * b, computed in the given form
SIGS_API Tree cfMix(Tree c, Tree a, Tree b, MixForm form);
SIGS_API bool isCfMix(Tree s, Tree& c, Tree& a, Tree& b, MixForm& form);

/// IRM(x; c) = y, y = mix(c, x, y@1), computed in the given form
SIGS_API Tree cfIrm(Tree x, Tree c, IrmForm form);
SIGS_API bool isCfIrm(Tree s, Tree& x, Tree& c, IrmForm& form);

/// frac(x) = x - floor(x), its floor approximated when approx (-mapp, the certified x in the
/// int32 range) ; floor and ceil themselves are approximated by their own primitives
/// (FloorApproxPrim, CeilApproxPrim)
SIGS_API Tree cfFrac(Tree x, bool approx);
SIGS_API bool isCfFrac(Tree s, Tree& x, bool& approx);

/// The operands of a node, in either form : for a traversal that needs the structure of
/// the program, not the decision (an occurrence, a dependency, a schedule)
SIGS_API bool isPhaseNode(Tree s, Tree& x, Tree& p);
SIGS_API bool isMixNode(Tree s, Tree& c, Tree& a, Tree& b);
SIGS_API bool isIrmNode(Tree s, Tree& x, Tree& c);
SIGS_API bool isIrmNode(Tree s);
SIGS_API bool isFracNode(Tree s, Tree& x);
