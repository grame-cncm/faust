/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "global.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "sigNewConstantPropagation.hh"
#include "sigPromotion.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "timing.hh"
#include "tree.hh"

using namespace std;

// Implementation

//----------------------------------------------------------------------------------------
// The normalization fixpoint (experimental, FAUST_NORMALIZE_FIXPOINT).
//
// Interval-driven constant propagation changes the TOPOLOGY of recursions: a
// projection with a singleton interval becomes a constant, edges of the dependency
// graph disappear, groups shrink -- and two distinct recursive expressions can become
// alpha-EQUIVALENT. The symbolic representation cannot fuse them (distinct variables),
// but in de Bruijn form alpha-equivalence IS syntactic equality, so hash-consing
// fuses them for free. Fusion in turn makes pointers equal, the canonical maps of the
// polynomial normal form collect the newly identical terms, intervals tighten, new
// constants appear... hence the loop, iterated until the de Bruijn form is
// POINTER-stable. Termination: (distinct recursive groups, non-constant nodes)
// decreases on every productive iteration.
//----------------------------------------------------------------------------------------

/// Count the distinct recursive groups reachable from t (SYMREC nodes, definitions
/// traversed through their bodies).
static int countRecGroups(Tree t)
{
    std::set<Tree>    seen;
    std::set<Tree>    groups;
    std::vector<Tree> work{t};
    while (!work.empty()) {
        Tree s = work.back();
        work.pop_back();
        if (!seen.insert(s).second) {
            continue;
        }
        Tree var, body;
        if (isRec(s, var, body)) {
            groups.insert(s);
            if (body) {
                work.push_back(body);
            }
            continue;
        }
        for (int i = 0; i < s->arity(); i++) {
            work.push_back(s->branch(i));
        }
    }
    return static_cast<int>(groups.size());
}

static Tree normalizeFixpoint(Tree L)
{
    const int groupsBefore = countRecGroups(L);
    Tree      prev         = nullptr;
    int       iter         = 0;

    const bool verbose  = getenv("FAUST_NORMALIZE_FIXPOINT_TRACE") != nullptr;
    Tree       prevPrev = nullptr;
    while (iter < 10) {
        Tree d = sym2deBruijn(L);
        if (d == prev) {
            break;  // the de Bruijn form is pointer-stable: fixpoint reached
        }
        if (verbose) {
            static Tree prevL = nullptr;
            std::cerr << "NORMFIX iter " << iter << " : groups=" << countRecGroups(L)
                      << " dbj=" << static_cast<const void*>(d)
                      << (d == prevPrev ? "  CYCLE-2" : "")
                      << (prevL ? (alphaEquiv(L, prevL) ? "  ALPHA-EQ" : "  ALPHA-DIFF")
                                : "")
                      << std::endl;
            prevL = L;
            if (getenv("FAUST_NORMALIZE_FIXPOINT_DUMP") != nullptr && iter < 4) {
                std::string fn = std::string(getenv("FAUST_NORMALIZE_FIXPOINT_DUMP")) +
                                 "/normfix-iter" + std::to_string(iter) + ".txt";
                FILE* out = fopen(fn.c_str(), "w");
                if (out) {
                    std::ostringstream oss;
                    oss << ppsig(L, 100000000);
                    fputs(oss.str().c_str(), out);
                    fclose(out);
                }
            }
        }
        prevPrev = prev;
        prev     = d;
        // the merge: alpha-equivalent groups are now shared, back to symbolic
        L = deBruijn2Sym(d);
        // canonical names before the sums are rebuilt: term orders hash the
        // INSTANCE-STRIPPED canonical keys, so they are stable across iterations
        L = canonicalizeRecNames(L);
        typeAnnotation(L, gGlobal->gLocalCausalityCheck);
        L = newConstantPropagation(L);
        L = simplify(L);
        typeAnnotation(L, gGlobal->gLocalCausalityCheck);
        L = signalPromote(L);
        iter++;
    }

    const int groupsAfter = countRecGroups(L);
    std::cerr << "NORMFIX : " << iter << " iteration(s), " << groupsBefore << " -> "
              << groupsAfter << " recursive group(s)" << std::endl;
    return L;
}
static Tree simplifyToNormalFormAux(Tree LS)
{
    // Convert deBruijn recursion into symbolic recursion
    startTiming("deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LS);
    endTiming("deBruijn2Sym");
/*
    // PROBE: cost of the symbolic -> deBruijn -> symbolic round-trip on the
    // recursive-group representation (scalarization abandoned: n-ary groups
    // are the right canonical form for dense mutual recursion, see
    // SCALARIZE-CARTOGRAPHY.md). The round-trip is the identity on the
    // already-canonical L0; it measures the benefit of the invariance
    // predicate on real programs.
    startTiming("sharing-roundtrip-1/2 sym2deBruijn");
    Tree LD = sym2deBruijn(L0);
    endTiming("sharing-roundtrip-1/2 sym2deBruijn");

    startTiming("sharing-roundtrip-2/2 deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LD);
    endTiming("sharing-roundtrip-2/2 deBruijn2Sym");
*/
    // Annotate L1 with type information
    startTiming("L1 typeAnnotation");
    typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
    endTiming("L1 typeAnnotation");

    if (gGlobal->gRangeUI) {
        // Generate safe values for range UI items (sliders and nentry)
        startTiming("Safe values for range UI items");
        L1 = signalUIPromote(L1);
        endTiming("Safe values for range UI items");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    if (gGlobal->gFreezeUI) {
        // Freeze range UI items (sliders and nentry) to their init value
        startTiming("Freeze values for range UI items");
        L1 = signalUIFreezePromote(L1);
        endTiming("Freeze values for range UI items");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    if (gGlobal->gFTZMode > 0) {
        // Wrap real signals with FTZ
        startTiming("FTZ on recursive signals");
        L1 = signalFTZPromote(L1);
        endTiming("FTZ on recursive signals");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    // Auto differentiation
    if (gGlobal->gAutoDifferentiate) {
        L1 = signalAutoDifferentiate(L1);
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
    }

    // Needed before 'simplify' (see sigPromotion.hh)
    startTiming("Cast and Promotion");
    Tree L2 = signalPromote(L1);
    endTiming("Cast and Promotion");

    // Canonical names BEFORE the normal form : the term orders of the normalized
    // sums and products hash the recursive variables by NAME, so the names must
    // already be history-independent here (simplify also reads types : re-annotate).
    startTiming("canonicalizeRecNames");
    L2 = canonicalizeRecNames(L2);
    endTiming("canonicalizeRecNames");

    startTiming("L2 typeAnnotation");
    typeAnnotation(L2, gGlobal->gLocalCausalityCheck);
    endTiming("L2 typeAnnotation");

    // Simplify by executing every computable operation
    startTiming("L2 simplification");
    Tree L3 = simplify(L2);
    endTiming("L2 simplification");

    // Annotate L3 with type information
    startTiming("L3 typeAnnotation");
    typeAnnotation(L3, gGlobal->gLocalCausalityCheck);
    endTiming("L3 typeAnnotation");

    startTiming("Cast and Promotion");
    Tree L4 = signalPromote(L3);
    endTiming("Cast and Promotion");

    startTiming("L4 typeAnnotation");
    typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
    endTiming("L4 typeAnnotation");

    // Must be done after simplification so that 'size' signal is properly simplified to a constant
    if (gGlobal->gCheckTable) {
        // Check and generate safe access to rdtable/rwtable
        startTiming("Safe access to rdtable/rwtable");
        L4 = signalTablePromote(L4);
        endTiming("Safe access to rdtable/rwtable");

        // Annotate L4 with type information
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    if (gGlobal->gCheckIntRange) {
        // Check and generate safe float to integer range conversion
        startTiming("Safe float to integer conversion");
        L4 = signalIntCastPromote(L4);
        endTiming("Safe float to integer conversion");

        // Annotate L4 with type information
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    if (getenv("FAUST_NORMALIZE_FIXPOINT") != nullptr) {
        startTiming("normalizeFixpoint");
        L4 = normalizeFixpoint(L4);
        endTiming("normalizeFixpoint");
    }

    // Canonical recursive-variable naming : names AND node serials in plan order, so
    // the downstream serial-ordered consumers (symbol sets, loop scheduling) become
    // independent of the transformation history -- the generated code is the same for
    // alpha-equivalent trees.
    startTiming("canonicalizeRecNames");
    L4 = canonicalizeRecNames(L4);
    endTiming("canonicalizeRecNames");

    startTiming("L4 typeAnnotation");
    typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
    endTiming("L4 typeAnnotation");

    // Check signal tree
    startTiming("L4 signalChecker");
    SignalChecker checker(L4);
    endTiming("L4 signalChecker");
    return L4;
}

// Public API
LIBFAUST_API Tree simplifyToNormalForm(Tree sig)
{
    if (isList(sig)) {
        startTiming("simplifyToNormalForm");
        Tree t2 = sig->getProperty(gGlobal->NORMALFORM);
        if (!t2) {
            t2 = simplifyToNormalFormAux(sig);
            sig->setProperty(gGlobal->NORMALFORM, t2);
        }
        endTiming("simplifyToNormalForm");
        return t2;
    } else {
        return simplifyToNormalForm(cons(sig, gGlobal->nil));
    }
}

LIBFAUST_API tvec simplifyToNormalForm2(tvec siglist)
{
    tvec res;
    for (const auto& it : siglist) {
        res.push_back(simplifyToNormalForm(it));
    }
    return res;
}

LIBFAUST_API string printSignal(Tree sig, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        ppsigShared(sig, str, max_size);
    } else {
        str << ppsig(sig, max_size) << endl;
    }
    return str.str();
}

LIBFAUST_API string printBox(Tree box, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        boxppShared(box, str);
    } else {
        str << mBox(box, max_size) << endl;
    }
    return str.str();
}
