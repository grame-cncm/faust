/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <unordered_map>

#include "signals.hh"

/**
 * The long sums of a program in interleaved partial sums (by default ; -nosl keeps the
 * chains). The code generators compute a Sum node as the chain ((t0 + t1) + ...) + tn,
 * the association its interval follows : each addition waits for the previous one, and
 * the C++ compiler, which may not reassociate without -ffast-math, can neither vectorize
 * nor overlap them. sumLanes rewrites a real Sum with at least 8 terms computed at the
 * sample rate : its slower terms first, as the normal form orders them, then the
 * sample-rate terms t0, ..., tm in 4 partial sums added as a balanced tree.
 *
 * A sum first takes in its nested sums (step 3f.1 of the computation form) : a term that
 * is a real sum at the sample rate, or its negation, that no other signal reads, is
 * replaced by its terms, at its place, when the sum thus gathered has at least 8
 * sample-rate terms and its partial sums are less deep, in additions, than the sum as the
 * code would compute it. The normal form and the sharing of the sums leave staircases of
 * nested sums computed one after the other (the decoder of oneSourceToStereo : 8 nested
 * sums, about 40 additions in a chain), which are gathered ; a balanced tree of nested
 * sums stays. A sum read elsewhere stays one term, computed once. The numbers of the
 * gathered sum are added into one, first, and its slower terms follow by rate.
 *
 * A partial sum whose terms are all subtracted is the opposite of the sum of their
 * opposites, its sign carried up the balanced tree and the sum that reads it : a - b
 * instead of a + -(b), the same value bit for bit, no negation computed.
 *
 * The rounding changes : the pass runs on the computation form, after the certified
 * typing (computeForm.hh), and leaves a sum whose value may reach a delay amount, an index
 * or an integer conversion as the certification bounded it (decisionCone.hh). It reads the
 * attributes in the types and leaves its result typed (typedAttributes.hh) ; image, when
 * given, receives every node of L with its rewriting.
 *
 * How the terms are dealt to the partial sums depends on the code generator :
 * - interleaved, Sum(t0, t4, t8, ...), Sum(t1, t5, ...), ... : each step of the four sums
 *   adds four consecutive terms, one vector for the C++ compiler. The generators of the
 *   instruction compiler (cpp and the others) emit the terms in the same order whatever
 *   the sum ;
 * - contiguous, Sum(t0, ..., t(k-1)), Sum(tk, ...), ... : the ocpp scheduler emits each
 *   computation where it is first read, and interleaved sums would emit the terms in the
 *   order t0, t4, t8, ..., t1, ... : isomorphic computations (the bands of a vocoder) are
 *   no longer adjacent, and the C++ compiler no longer vectorizes them.
 */
enum class LaneOrder { kInterleaved, kContiguous };

Tree sumLanes(Tree L, LaneOrder order, std::unordered_map<Tree, Tree>* image = nullptr);

/**
 * The taps of the filters (step 3f.5 of the computation form ; by default, -nolt keeps the
 * order of the definition). The code of a FIR computes the chain of its taps, and the code
 * of an IIR its input, then its feedback taps : the term computed in the sample (the tap of
 * delay 0, the input) comes first, and every other operation waits for it, while the other
 * terms read delay lines, ready from the start of the sample. In a cascade of filters each
 * section waits for the whole chain of the previous one. markLateTaps marks the real FIR and
 * IIR filters of L outside the cone of the memory decisions (decisionCone.hh) : their code
 * adds the late term last, a FIR its taps from the last delay to the first, an IIR its
 * feedback taps from the last delay to y@1, then its input. The rounding changes ; the
 * recurrence of an IIR keeps two operations from y@1 to y. lateTapsLast tells the code
 * generators whether a filter is marked.
 */
void markLateTaps(Tree L);
bool lateTapsLast(Tree sig);
